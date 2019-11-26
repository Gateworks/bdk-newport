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
#include "mydApiTypes.h"
#include "mydApiRegs.h"
#include "mydUtils.h"
#include "mydInitialization.h"
#include "mydHwCntl.h"
#include "mydAPI.h"
#include "mydDiagnostics.h"
#include "mydFwDownload.h"
#include "mydIntrIOConfig.h"
#include "mydAPIInternal.h"
#include "mydHwSerdesCntl.h"

/*******************************************************************
 MYD_STATUS mydInitDriver
    This is the first routine that needs be called by system software.
    The following is the job performed by this routine:
       1. store MDIO read/write function into the given MYD_DEV structure
       2. run any device specific initialization routine (chip hardware reset,
          firmware download, etc.)
       3. retrieve the deviceId and revision information
*******************************************************************/
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
)
{
    MYD_U16 data;
    MYD_BOOL loadImage = MYD_FALSE;
    MYD_U16 portCount;

    /* MYD_DBG_INFO("mydInitDriver Called.\n"); */

#if 0
    /* Check for parameters validity */
    /* allow to be called with NULL for IO functions, in case host wants to */
    /* implement their own and not use the ones inside the MYD_DEV struct   */
    if(readMdio == NULL || writeMdio == NULL )
    {
        MYD_DBG_ERROR("mydInitDriver: MDIO read or write pointers are NULL.\n");
        return MYD_STATUS_ERR_INIT;
    }
#endif

    /* Check for parameters validity        */
    if(pDev == NULL)
    {
        MYD_DBG_ERROR("mydInitDriver: MYD_DEV pointer is NULL.\n");
        return MYD_STATUS_ERR_DEV;
    }

    /* The initialization was already done. */
    if(pDev->devEnabled)
    {
        MYD_DBG_ERROR("mydInitDriver: Device Driver already loaded.\n");
        return MYD_STATUS_ERR_INIT;
    }

    pDev->mdioPort = mdioPort;

    /* check MDIO port within range and even number since this is Port 0 */
    if(mdioPort >= MYD_MAX_MDIO_NUM)
    {
        MYD_DBG_ERROR("mydInitDriver: Invalid MDIO port number : %u\n", mdioPort);
        return MYD_STATUS_ERR_DEV;
    }

    pDev->hostContext = pHostContext;
    pDev->fmydReadMdio = readMdio;
    pDev->fmydWriteMdio = writeMdio;

    if((mydHwXmdioRead(pDev, mdioPort, 1, 0 ,&data))!= MYD_OK) /* try to read 1.0 */
    {
        MYD_DBG_ERROR("mydInitDriver: Reading dev:1 reg:0x0000 failed.\n");
        return MYD_STATUS_FAIL_READ_REG;
    }

    if(data == 0x0000 || data == 0xFFFF ) /* try to read 1.0 */
    {
        MYD_DBG_ERROR("mydInitDriver: Invalid dev:1 reg:0x0000 data: 0x%X\n", data);
        return MYD_STATUS_FAIL_READ_REG;
    }    

    /* Check if mydWait() is implemented */ 
    if (mydWait(pDev, 0) != MYD_OK)
    {
        MYD_DBG_ERROR("mydInitDriver: mydWait() platform dependent function required to be implemented.\n");
        return MYD_STATUS_ERR_INIT;
    }
    
    /* After everything else is done, can fill in the device id */
    if ((mydGetChipRevision(pDev, mdioPort, &(pDev->deviceId))) != MYD_OK)
    {
        MYD_DBG_ERROR("mydInitDriver: mydGetChipRevision Failed.\n");
        return MYD_STATUS_ERR_DEV_ID;
    }

    if ((mydDevicePortCount(pDev, mdioPort, &portCount)) != MYD_OK)
    {
        MYD_DBG_ERROR("mydInitDriver: mydDevicePortCount Failed.\n");
        return MYD_STATUS_INVALID_PORT;
    }
    else
    {
        pDev->portCount = portCount;
    }

    /*  Init driver with or without downloading firmware images */
    if (pBusMasterImage && pSerdesImage && busMasterSize && serdesSize)
    {
        MYD_STATUS status;
        MYD_BOOL broadcastMode;

        /* The broadcast write mode will speed up the firmware download.
           Broadcast write mode can only work when write verify is disabled.
           To disable the broadcast mode with write verify disabled, set the 
           broadcastMode = MYD_FALSE */
        broadcastMode = (MYD_FW_WRITE_VERIFIED)? MYD_FALSE:MYD_TRUE;

        /* broadcast mode can be disabled with write verify disabled */
        /* broadcastMode = MYD_FALSE; */

        status = mydFirmwareDownload(pDev, mdioPort, pZ80Image, z80Size, 
                                     pBusMasterImage, busMasterSize, 
                                     pSerdesImage, serdesSize, 
                                     MYD_TRUE, broadcastMode);

        if (status != MYD_OK)
        {
            MYD_DBG_ERROR("mydInitDriver: mydFirmwareDownload failed errCode:0x%x.\n", 
                            status);
            return status;
        }

        loadImage = MYD_TRUE;
    } 
    else 
    {
        /* software reset if no image loaded */
        ATTEMPT(mydChipAndZ80ResetControl(pDev, MYD_CHIP_SW_RESET, MYD_FALSE)); 

        ATTEMPT(mydWait(pDev, 500));
        MYD_DBG_INFO("mydInitDriver: Driver init without firmware download.\n");
    }

    /* initial config and mode structures */
    mydMemSet(pDev->devInfo, 0, (sizeof(MYD_U32)*MYD_MAX_PORTS));
    mydMemSet(pDev->hostConfig, 0, (sizeof(MYD_MODE_CONFIG)*MYD_MAX_PORTS*MYD_NUM_LANES));
    mydMemSet(pDev->lineConfig, 0, (sizeof(MYD_MODE_CONFIG)*MYD_MAX_PORTS*MYD_NUM_LANES));

#if MYD_ENABLE_SERDES_API
    if (mydInitSerdesDev(pDev) != MYD_OK)
    {
        MYD_DBG_ERROR("mydInitDriver: mydInitSerdesDev failed.\n");
        return MYD_STATUS_SERDES_INIT_ERR;
    }
#endif     

    /* Releases Z80 reset */
    ATTEMPT(mydChipAndZ80ResetControl(pDev, MYD_Z80_RESET_RELEASE, MYD_FALSE)); 

    if (loadImage == MYD_FALSE)
    {  /* if EEPROM is available, sets the appropriate registers to use the EEPROM on hardware reset */
        MYD_U16 i, loadEEPROM; 
        MYD_U16 waitTime = MYD_HW_RESET_WAITTIME;

        for (i=0; i<(waitTime/100); i++) 
        {
            ATTEMPT(mydWait(pDev, 100)); /*  */

            /* check the last port(if multi-ports) for EERPOM availability */
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort+(pDev->portCount-1), MYD_NIMB_REG, 0xF845, &loadEEPROM)); 
            
            /* MYD_DBG_INFO("mydInitDriver: EEPROM port:%d load in %u msec. Return val:0x%X\n", mdioPort+(pDev->portCount-1), i*100, loadEEPROM); */

            if ((loadEEPROM & 0x0001) == 1) 
            {
                if (i && (i*100 < waitTime)) 
                {                                /* if EEPROM is reloaded,  */
                    ATTEMPT(mydWait(pDev, 300)); /* add another 300ms for SerDes to settle */
                }
                pDev->devEEPROM = MYD_TRUE;
                break;
            }
        }
    }

    pDev->devEnabled = MYD_TRUE;

    MYD_DBG_INFO("mydInitDriver successful.\n");
    return MYD_OK;
}


/*******************************************************************
 MYD_STATUS mydReloadDriver
*******************************************************************/
MYD_STATUS mydReloadDriver
(
    IN FMYD_READ_MDIO  readMdio,
    IN FMYD_WRITE_MDIO writeMdio,
    IN MYD_U16         mdioPort,
    IN MYD_PVOID       pHostContext,
    IN MYD_U16         optionFlag,
    OUT MYD_DEV_PTR    pDev
)
{
    MYD_U16 data;
    MYD_U16 portCount;

    /* Check for parameters validity */
    if(pDev == NULL)
    {
        MYD_DBG_ERROR("mydReloadDriver: MYD_DEV pointer is NULL.\n");
        return MYD_STATUS_ERR_DEV;
    }

    /* The initialization was already done. */
    if(pDev->devEnabled)
    {
        MYD_DBG_ERROR("mydReloadDriver: Device Driver already loaded.\n");
        return MYD_STATUS_ERR_INIT;
    }

    pDev->mdioPort = mdioPort;

    /* check MDIO port within range and even number since this is Port 0 */
    if(mdioPort >= MYD_MAX_MDIO_NUM)
    {
        MYD_DBG_ERROR("mydReloadDriver: Invalid MDIO port number : %u\n", mdioPort);
        return MYD_STATUS_ERR_DEV;
    }

    pDev->hostContext = pHostContext;
    pDev->fmydReadMdio = readMdio;
    pDev->fmydWriteMdio = writeMdio;

    if((mydHwXmdioRead(pDev, mdioPort, 1, 0 ,&data))!= MYD_OK) /* try to read 1.0 */
    {
        MYD_DBG_ERROR("mydReloadDriver: Reading dev:1 reg:0x0000 failed.\n");
        return MYD_STATUS_FAIL_READ_REG;
    }

    /* Check if mydWait() is implemented */ 
    if (mydWait(pDev, 0) != MYD_OK)
    {
        MYD_DBG_ERROR("mydReloadDriver: mydWait() platform dependent function required to be implemented.\n");
        return MYD_STATUS_ERR_INIT;
    }
    
    /* After everything else is done, can fill in the device id */
    if ((mydGetChipRevision(pDev, mdioPort, &(pDev->deviceId))) != MYD_OK)
    {
        MYD_DBG_ERROR("mydReloadDriver: mydGetChipRevision Failed.\n");
        return MYD_STATUS_ERR_DEV_ID;
    }

    if ((mydDevicePortCount(pDev, mdioPort, &portCount)) != MYD_OK)
    {
        MYD_DBG_ERROR("mydReloadDriver: mydDevicePortCount Failed.\n");
        return MYD_STATUS_INVALID_PORT;
    }
    else
    {
        pDev->portCount = portCount;
    }

    if (optionFlag & MYD_RELOAD_CONFIG)
    {
        /* initial config and mode structures */
        mydMemSet(pDev->devInfo, 0, (sizeof(MYD_U32)*MYD_MAX_PORTS));
        mydMemSet(pDev->hostConfig, 0, (sizeof(MYD_MODE_CONFIG)*MYD_MAX_PORTS*MYD_NUM_LANES));
        mydMemSet(pDev->lineConfig, 0, (sizeof(MYD_MODE_CONFIG)*MYD_MAX_PORTS*MYD_NUM_LANES));

        ATTEMPT(mydReloadConfigInfo(pDev, mdioPort)); 
    }

#if MYD_ENABLE_SERDES_API
    if (mydInitSerdesDev(pDev) != MYD_OK)
    {
        MYD_DBG_ERROR("mydReloadDriver: mydInitSerdesDev failed.\n");
        return MYD_STATUS_SERDES_INIT_ERR;
    }
#endif     

    pDev->devEnabled = MYD_TRUE;

    MYD_DBG_INFO("mydReloadDriver successful.\n");
    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydUnloadDriver
*******************************************************************/
MYD_STATUS mydUnloadDriver
(
    IN MYD_DEV_PTR pDev
)
{
    if (!pDev)
    {
        MYD_DBG_ERROR("mydUnloadDriver: device in NULL\n");
        return MYD_FAIL;
    }

#if MYD_ENABLE_SERDES_API
    if (mydFreeSerdesDev(pDev) != MYD_OK)
    {
        MYD_DBG_ERROR("mydUnloadDriver: mydFreeSerdesDev failed.\n");
        return MYD_FAIL;
    }
#endif     

    mydMemSet(pDev, 0, (sizeof(MYD_DEV)));

    MYD_DBG_INFO("mydUnloadDriver: Clean-up completed.\n");

    return MYD_OK;
 }


/*******************************************************************
 MYD_STATUS mydLanePowerdown
 Perform a lane powerdown on the given lane(s).
*******************************************************************/
MYD_STATUS mydLanePowerdown
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset
)
{
    MYD_U16 sideCtr, powerBitReg, laneCtr;
    MYD_U8 bitPosition;
    
    if (host_or_line == MYD_BOTH_SIDE)
    {
        sideCtr = MYD_LINE_SIDE; /* both sides go from MYD_LINE_SIDE to MYD_BOTH_SIDE */
    }
    else
    {
        if (!(host_or_line == MYD_LINE_SIDE || host_or_line == MYD_HOST_SIDE))
        {
            MYD_DBG_ERROR("mydLanePowerdown: invalid host or line selection\n");
            return MYD_FAIL;
        }

        sideCtr = host_or_line++; /* single side goes from side to side+1 */
    }

    if (laneOffset == MYD_ALL_LANES)
    {
        laneCtr = 0; /* all lanes go from 0 to MYD_ALL_LANES */
    }
    else
    {
        laneCtr = laneOffset++; /* single lane goes from lane to lane+1 */
    }

    while(sideCtr < host_or_line) /* host, line or both sides */
    {
        while(laneCtr < laneOffset) /* one lane or all lanes */
        {            
            MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneCtr, sideCtr); /* do range checking on everything */
            
            powerBitReg = 0xF0EF; /* powerdown and reset overwrite register */
            bitPosition = laneCtr*2;

            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, sideCtr, powerBitReg, bitPosition, 2, 0x3));
            
            laneCtr++;
        }
        
        sideCtr++;
    }

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydLanePowerup
 Perform a lane powered up on the given lane(s).
*******************************************************************/
MYD_STATUS mydLanePowerup
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset
)
{
    MYD_U16 sideCtr, powerBitReg, laneCtr, laneCount;
    MYD_U8 bitPosition;
    MYD_OP_MODE opMode;
    MYD_BOOL laneToPowerUp;
    MYD_U16 mdioPortIndex = MYD_GET_PORT_IDX(pDev, mdioPort);    
    
    if (host_or_line == MYD_BOTH_SIDE)
    {
        sideCtr = MYD_LINE_SIDE; /* both sides go from MYD_LINE_SIDE to MYD_BOTH_SIDE */
    }
    else
    {
        if (!(host_or_line == MYD_LINE_SIDE || host_or_line == MYD_HOST_SIDE))
        {
            MYD_DBG_ERROR("mydLanePowerdown: invalid host or line selection\n");
            return MYD_FAIL;
        }

        sideCtr = host_or_line++; /* single side goes from side to side+1 */
    }

    if (laneOffset == MYD_ALL_LANES)
    {
        laneCtr = 0; /* all lanes go from 0 to MYD_ALL_LANES */
    }
    else
    {
        laneCtr = laneOffset++; /* single lane goes from lane to lane+1 */
    }

    while(sideCtr < host_or_line) /* host, line or both sides */
    {
        while(laneCtr < laneOffset) /* one lane or all lanes */
        {

            MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneCtr, sideCtr); /* do range checking on everything */
            
            /* Range check on the laneCtr, if this is the lane of a single lane mode */
            /* or the first lane of a multi-lane mode, then it's ok to power it up */
            /* If a specific lane was passed in and it's not the first lane of a multi-lane mode */
            /* or it's not the lane assigned to a single lane mode, then return an error */
            
            ATTEMPT(mydGetOpMode(pDev, mdioPort, sideCtr, laneCtr, &opMode));

            if (laneOffset != MYD_ALL_LANES)
            {
                /* this is case where host passed a specific lane, make sure it's the first lane or */
                /* the only lane of a configured single lane mode */
                if (mydCheckOpModeLaneOffset(pDev, mdioPort, laneCtr, opMode) == MYD_FAIL)
                {
                    MYD_DBG_ERROR("mydLanePowerup: incorrect lane offset: %u\n", laneCtr);
                    return MYD_FAIL;
                }

                laneToPowerUp = MYD_TRUE;
            }
            else
            {
                /* this is the case where MYD_ALL_LANES were passed, skip unassigned lanes or lanes */
                /* that are not the first lane of a multi-lane mode */
                laneCount = opModeTable[opMode][MYD_OP_TABLE_LANE_COUNT];

                laneToPowerUp = MYD_FALSE;
                switch(laneCount)
                {
                    case MYD_1_LANE_MODE:
                        if (laneCtr < MYD_NUM_LANES)
                        {
                            laneToPowerUp = MYD_TRUE;
                        }
                        break;
                
                    case MYD_2_LANE_MODE:
                        if ((laneCtr == 0) || (laneCtr == 2))
                        {
                            laneToPowerUp = MYD_TRUE;
                        }
                        break;
                
                    case MYD_4_LANE_MODE:
                        if (laneCtr == 0)
                        {
                            laneToPowerUp = MYD_TRUE;
                        }
                        break;
                
                    case MYD_8_LANE_MODE:
                        if ((laneCtr == 0) && (pDev->portCount > 1))
                        {
                            if ((mdioPortIndex == 0) || (mdioPortIndex == 2)) 
                            {
                                laneToPowerUp = MYD_TRUE;
                            }
                        }
                        break;
                        
                    default:
                        /* not possible, but if it happens won't power up this lane */
                        break;
                }

            }

            if (laneToPowerUp == MYD_TRUE)
            {
                powerBitReg = 0xF0EF; /* powerdown and reset overwrite register */
                bitPosition = laneCtr*2;

                ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, sideCtr, powerBitReg, bitPosition, 2, 0)); /* set back to power-on default (no overwrite) */
            }
            
            laneCtr++;
        }
        
        sideCtr++;
    }

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydPortReset
 Perform a port hardware Soft or Hard reset on either line or host
*******************************************************************/
MYD_STATUS mydPortReset
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_RESET_TYPE resetType,
    IN MYD_U16 timeoutMs
)
{
    if (resetType == MYD_SOFT_RESET)
    {
        if (host_or_line == MYD_LINE_SIDE)
        {
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_PWD_RESET, 15, 1, 1));
        }
        else if (host_or_line == MYD_HOST_SIDE)
        {
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_PWD_RESET, 7, 1, 1));
        }
        else
        {
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_PWD_RESET, 15, 1, 1));
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_PWD_RESET, 7, 1, 1));
        }
    }
    else if (resetType == MYD_HARD_RESET)
    {
        if (host_or_line == MYD_LINE_SIDE)
        {
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_PWD_RESET, 14, 1, 1));
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_PWD_RESET, 14, 1, 0));
        }
        else if (host_or_line == MYD_HOST_SIDE)
        {
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_PWD_RESET, 6, 1, 1));
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_PWD_RESET, 6, 1, 0));
        }
        else
        {
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_PWD_RESET, 14, 1, 1));
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_PWD_RESET, 6, 1, 1));
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_PWD_RESET, 14, 1, 0));
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_PWD_RESET, 6, 1, 0));
        }
    }
    else
    {
        MYD_DBG_ERROR("mydPortReset incorrect resetType: 0x%x\n", resetType);
        return MYD_FAIL;
    }

    mydPortResetTimeout(pDev, mdioPort, timeoutMs);

    return MYD_OK;
}


/*******************************************************************
 MYD_STATUS mydChipAndZ80ResetControl

 Perform a Chip hardware Soft or Hard reset and/or a Z80 reset; 
 save any registers we might need if we need power-on default of 
 registers to restore later
*******************************************************************/
MYD_STATUS mydChipAndZ80ResetControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 resetType,
    IN MYD_BOOL bRestore
)
{
    MYD_U16 needRestore = 0;
    MYD_U16 portIndex;
    MYD_U16 mdioPortIndex = MYD_GET_PORT_IDX(pDev, pDev->mdioPort);

    if (!pDev)
    {
        MYD_DBG_ERROR("mydChipAndZ80ResetControl: device in NULL\n");
        return MYD_FAIL;
    }

    if (bRestore && (resetType & MYD_CHIP_HW_RESET))
    {
        /* TBD: save any registers we might need if
           we need power-on default of registers to restore later */
        needRestore = 1;
    }

    switch (resetType)
    {
        MYD_U16 eepromWaitTime; 

        case MYD_CHIP_SW_RESET:
            for (portIndex=0; portIndex<pDev->portCount; portIndex++)
            {
                ATTEMPT(mydPortAndZ80ResetControl(pDev, pDev->mdioPort+portIndex, MYD_CHIP_SW_RESET, bRestore)); 
            }
            break;

        case MYD_CHIP_HW_RESET:
            for (portIndex=0; portIndex<pDev->portCount; portIndex++)
            {
                /* Marvell ROM load disabled */
                ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort+portIndex, MYD_CHIP_REG, 0xF416, 0, 1, 0)); 
                /* EEPROM is copied into RAM after chip comes out of reset. */
                ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort+portIndex, MYD_CHIP_REG, 0xF418, 0, 1, 0)); 
            }
            for (portIndex=0; portIndex<pDev->portCount; portIndex++)
            {
                ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort+portIndex, MYD_CHIP_REG, MYD_GLOBAL_RESET, 13, 2, 0x3));
                mydMemSet(pDev->hostConfig[mdioPortIndex], 0, (sizeof(MYD_MODE_CONFIG)*MYD_NUM_LANES));
                mydMemSet(pDev->lineConfig[mdioPortIndex], 0, (sizeof(MYD_MODE_CONFIG)*MYD_NUM_LANES));
                pDev->devInfo[mdioPortIndex] &= ~MYD_LANES_GROUPED;
            }

            ATTEMPT(mydLoadEEPROMSerdesWaitTime(pDev, pDev->mdioPort+(pDev->portCount-1), 
                                                MYD_HW_RESET_WAITTIME*pDev->portCount, &eepromWaitTime));

            for (portIndex=0; portIndex<pDev->portCount; portIndex++)
            {
                ATTEMPT(mydPortAndZ80ResetControl(pDev, pDev->mdioPort+portIndex, MYD_Z80_RESET_RELEASE, bRestore)); 
            }
            break;

        case (MYD_CHIP_HW_RESET | MYD_Z80_RESET):
            for (portIndex=0; portIndex<pDev->portCount; portIndex++)
            {
                ATTEMPT(mydPortAndZ80ResetControl(pDev, pDev->mdioPort+portIndex, (MYD_CHIP_HW_RESET|MYD_Z80_RESET), bRestore)); 
            }

            ATTEMPT(mydLoadEEPROMSerdesWaitTime(pDev, pDev->mdioPort+(pDev->portCount-1) , 
                                                MYD_HW_RESET_WAITTIME*pDev->portCount, &eepromWaitTime));
            break;

        case MYD_Z80_RESET:
            for (portIndex=0; portIndex<pDev->portCount; portIndex++)
            {
                ATTEMPT(mydPortAndZ80ResetControl(pDev, pDev->mdioPort+portIndex, MYD_Z80_RESET, bRestore)); 
            }
            break;

        case MYD_Z80_RESET_RELEASE:
            for (portIndex=0; portIndex<pDev->portCount; portIndex++)
            {
                ATTEMPT(mydPortAndZ80ResetControl(pDev, pDev->mdioPort+portIndex, MYD_Z80_RESET_RELEASE, bRestore)); 
            }
            break;

        default:
            MYD_DBG_ERROR("mydChipAndZ80ResetControl incorrect resetType: 0x%04X\n", (MYD_U16)resetType);
            return MYD_FAIL;
    }

    if (needRestore)
    {
        /* TBD: restore registers saved above */
    }

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydPortAndZ80ResetControl

 Perform a Port hardware Soft or Hard reset and/or a Z80 reset; 
 save any registers we might need if we need power-on default of 
 registers to restore later
*******************************************************************/
MYD_STATUS mydPortAndZ80ResetControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 resetType,
    IN MYD_BOOL bRestore
)
{
    MYD_U16 needRestore = 0;
    MYD_U16 mdioPortIndex = MYD_GET_PORT_IDX(pDev, mdioPort);

    if (!pDev)
    {
        MYD_DBG_ERROR("mydPortAndZ80ResetControl: device in NULL\n");
        return MYD_FAIL;
    }

    if (bRestore && (resetType & MYD_PORT_HW_RESET))
    {
        /* TBD: save any registers we might need if
           we need power-on default of registers to restore later */

        needRestore = 1;
    }

    switch (resetType)
    {
        case MYD_PORT_SW_RESET:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_CHIP_REG, MYD_GLOBAL_RESET, 15, 1, 1));
            break;

        case MYD_PORT_HW_RESET:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_CHIP_REG, MYD_GLOBAL_RESET, 14, 1, 1));

            /* reset config and mode structures */
            mydMemSet(pDev->hostConfig[mdioPortIndex], 0, (sizeof(MYD_MODE_CONFIG)*MYD_NUM_LANES));
            mydMemSet(pDev->lineConfig[mdioPortIndex], 0, (sizeof(MYD_MODE_CONFIG)*MYD_NUM_LANES));
            pDev->devInfo[mdioPortIndex] &= ~MYD_LANES_GROUPED;
            break;

        case (MYD_PORT_HW_RESET | MYD_Z80_RESET):
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_CHIP_REG, MYD_GLOBAL_RESET, 13, 2, 3));

            /* reset config and mode structures */
            mydMemSet(pDev->hostConfig[mdioPortIndex], 0, (sizeof(MYD_MODE_CONFIG)*MYD_NUM_LANES));
            mydMemSet(pDev->lineConfig[mdioPortIndex], 0, (sizeof(MYD_MODE_CONFIG)*MYD_NUM_LANES));
            pDev->devInfo[mdioPortIndex] &= ~MYD_LANES_GROUPED;
            break;

        case MYD_Z80_RESET:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_CHIP_REG, MYD_GLOBAL_RESET, 13, 1, 1));
            break;

        case MYD_Z80_RESET_RELEASE:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_CHIP_REG, MYD_GLOBAL_RESET, 13, 1, 0));
            break;

        default:
            MYD_DBG_ERROR("mydPortAndZ80ResetControl incorrect resetType: 0x%04X\n", (MYD_U16)resetType);
            return MYD_FAIL;
    }

    if (needRestore)
    {
        /* TBD: restore registers saved above */
    }

    return MYD_OK;
}



