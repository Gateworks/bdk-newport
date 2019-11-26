/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions for initializing the driver, setting up 
the user-provide MDIO access functions, chip reset and various driver
initialization operations for the Marvell X5113 Device.
********************************************************************/
#include "mxdApiTypes.h"
#include "mxdApiRegs.h"
#include "mxdUtils.h"
#include "mxdInitialization.h"
#include "mxdHwCntl.h"
#include "mxdAPI.h"
#include "mxdDiagnostics.h"
#include "mxdFwDownload.h"
#include "mxdAPIInternal.h"
#include "mxdHwSerdesCntl.h"

/*******************************************************************
 MXD_STATUS mxdInitDriver
    This is the first routine that needs be called by system software.
    The following is the job performed by this routine:
       1. store MDIO read/write function into the given MXD_DEV structure
       2. run any device specific initialization routine (chip hardware reset,
          firmware download, etc.)
       3. Initialize the deviceId and revision information
*******************************************************************/
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
)
{
    MXD_U16 data;
    MXD_BOOL loadImage = MXD_FALSE;
    MXD_U16 errCode;

    MXD_DBG_INFO("mxdInitDriver Called.\n");

#if 0
    /* Check for parameters validity */
    /* allow to be called with NULL for IO functions, in case host wants to */
    /* implement their own and not use the ones inside the MXD_DEV struct   */
    if(readMdio == NULL || writeMdio == NULL )
    {
        MXD_DBG_ERROR("mxdInitDriver: MDIO read or write pointers are NULL.\n");
        return MXD_STATUS_ERR_INIT;
    }
#endif

    /* Check for parameters validity        */
    if(pDev == NULL)
    {
        MXD_DBG_ERROR("mxdInitDriver: MXD_DEV pointer is NULL.\n");
        return MXD_STATUS_ERR_DEV;
    }

    /* The initialization was already done. */
    if(pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdInitDriver: Device Driver already loaded.\n");
        return MXD_STATUS_ERR_INIT;
    }

    pDev->mdioPort = mdioPort;

    /* check MDIO port within range and even number since this is Port 0 */
    if(mdioPort >= MXD_MAX_MDIO_NUM)
    {
        MXD_DBG_ERROR("mxdInitDriver: Invalid MDIO port number : %u\n", mdioPort);
        return MXD_STATUS_ERR_DEV;
    }

    pDev->hostContext = pHostContext;
    pDev->fmxdReadMdio = readMdio;
    pDev->fmxdWriteMdio = writeMdio;

    if((mxdHwXmdioRead(pDev, mdioPort, 1, 0 ,&data))!= MXD_OK) /* try to read 1.0 */
    {
        MXD_DBG_ERROR("mxdInitDriver: Reading dev:1 reg:0x0000 failed.\n");
        return MXD_STATUS_FAIL_READ_REG;
    }

    if (data == 0x0000 || data == 0xFFFF)
    {
        MXD_DBG_ERROR("Reading to reg %x failed.\n",0);
        return MXD_STATUS_FAIL_READ_REG;
    }

    /* Check if mxdWait() is implemented */ 
    if (mxdWait(pDev, 0) != MXD_OK)
    {
        MXD_DBG_ERROR("mxdInitDriver: mxdWait() platform dependent function required to be implemented.\n");
        return MXD_STATUS_ERR_INIT;
    }
    
    /* After everything else is done, can fill in the device id */
    if ((mxdGetChipRevision(pDev, mdioPort,
                            &(pDev->deviceId))) != MXD_OK)
    {
        MXD_DBG_ERROR("mxdInitDriver: mxdGetChipRevision Failed.\n");
        return MXD_STATUS_ERR_DEV_ID;
    }

    /*  Init driver with or without downloading firmware images */
    if (pBusMasterImage && pSerdesImage && busMasterSize && serdesSize)
    {
        /* optional to download Z80 image */
        if (pZ80Image && z80Size)
        {
            /* Firmware download for Z80, does a chip and Z80 reset and leaves Z80 in reset */
            if ((mxdLoadZ80FWImage(pDev, mdioPort, z80Size, pZ80Image,
                                   MXD_TRUE, &errCode)) != MXD_OK)
            {
                MXD_DBG_ERROR("mxdInitDriver: Z80 Firmware download errCode: 0x%x.\n", errCode);
                return MXD_STATUS_FIRMWARE_ERR;
            }
        }
        else
        {
            /* disabled loading EEPROM image to RAM */
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, 0xF418, 0x1)); 

            /* chip reset and put Z80 into reset leaving it in reset */
            ATTEMPT(mxdChipAndZ80ResetControl(pDev, (MXD_CHIP_HW_RESET|MXD_Z80_RESET), MXD_FALSE)); 

            /* reset MROM & AROM Loading */
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_CHIP_REG, 0xF419, 1, 1, 0)); 
        }

        /* SBusMaster image download */
        if ((mxdLoadSBusMasterFW(pDev, mdioPort, busMasterSize,
                                 pBusMasterImage, &errCode)) != MXD_OK)
        {
            MXD_DBG_ERROR("mxdInitDriver: SBusMaster image download errCode: 0x%x.\n", errCode);
            return MXD_STATUS_FIRMWARE_ERR;
        }

        /* SBus Serdes image download */
        if ((mxdLoadSBusSerdesFW(pDev, mdioPort, serdesSize,
                                 pSerdesImage, &errCode)) != MXD_OK)
        {
            MXD_DBG_ERROR("mxdInitDriver: SBus Serdes image download errCode: 0x%x.\n", errCode);
            return MXD_STATUS_FIRMWARE_ERR;
        }

        loadImage = MXD_TRUE;
    } 
    else 
    {
        /* software reset if no image loaded */
        ATTEMPT(mxdChipAndZ80ResetControl(pDev, MXD_CHIP_SW_RESET, MXD_FALSE)); 

        ATTEMPT(mxdWait(pDev, 500));

        /* Releases Z80 reset */
        ATTEMPT(mxdChipAndZ80ResetControl(pDev, MXD_Z80_RESET_RELEASE, MXD_FALSE)); 

        MXD_DBG_INFO("mxdInitDriver: Driver init without firmware download.\n");
    }

    pDev->devInfo = 0;

    /* initial config and mode structures */
    mxdMemSet(pDev->opMode, 0, (sizeof(MXD_FIXED_OP_MODE)*MXD_NUM_LANES));
    mxdMemSet(pDev->hostConfig, 0, (sizeof(MXD_MODE_CONFIG)*MXD_NUM_LANES));
    mxdMemSet(pDev->lineConfig, 0, (sizeof(MXD_MODE_CONFIG)*MXD_NUM_LANES));

    pDev->portCount = 1;  /* X5113 supports only 1 port */

    ATTEMPT(mxdMappedSerdesIDs(pDev));

#if MXD_ENABLE_SERDES_API
    if (mxdInitSerdesDev(pDev) != MXD_OK)
    {
        MXD_DBG_ERROR("mxdInitDriver: mxdInitSerdesDev failed.\n");
        return MXD_STATUS_SERDES_INIT_ERR;
    }
#endif     

    /* initialize Z80 chip, release Z80 reset needed if image is loaded*/
    if (loadImage == MXD_TRUE)
    {
        /* Releases Z80 reset */
        ATTEMPT(mxdChipAndZ80ResetControl(pDev, MXD_Z80_RESET_RELEASE, MXD_FALSE)); 

        /* re-enable loading EEPROM image to RAM in case a chip reset after driver
           initialized */
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, 0xF418, 0x0)); 
    }

    pDev->devEnabled = MXD_TRUE;

    MXD_DBG_INFO("mxdInitDriver successful.\n");
    return MXD_OK;
}

/*******************************************************************
 MXD_STATUS mxdUnloadDriver
*******************************************************************/
MXD_STATUS mxdUnloadDriver
(
    IN MXD_DEV_PTR pDev
)
{
    if (!pDev)
    {
        MXD_DBG_ERROR("mxdUnloadDriver: device in NULL\n");
        return MXD_FAIL;
    }

#if MXD_ENABLE_SERDES_API
    if (mxdFreeSerdesDev(pDev) != MXD_OK)
    {
        MXD_DBG_ERROR("mxdUnloadDriver: mxdFreeSerdesDev failed.\n");
        return MXD_FAIL;
    }
#endif     

    mxdMemSet(pDev, 0, (sizeof(MXD_DEV)));

    MXD_DBG_INFO("mxdUnloadDriver: Clean-up completed.\n");

    return MXD_OK;
 }


/*******************************************************************
 MXD_STATUS mxdPortReset
 Perform a port hardware Soft or Hard reset
*******************************************************************/
MXD_STATUS mxdPortReset
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_RESET_TYPE resetType,
    IN MXD_U16 timeoutMs
)
{
    if (resetType == MXD_SOFT_RESET)
    {
        if (host_or_line == MXD_LINE_SIDE)
        {
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_PORT_REG, MXD_PORT_PWD_RESET, 15, 1, 1));
        }
        else if (host_or_line == MXD_HOST_SIDE)
        {
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_PORT_REG, MXD_PORT_PWD_RESET, 7, 1, 1));
        }
        else
        {
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_PORT_REG, MXD_PORT_PWD_RESET, 15, 1, 1));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_PORT_REG, MXD_PORT_PWD_RESET, 7, 1, 1));
        }
    }
    else if (resetType == MXD_HARD_RESET)
    {
        if (host_or_line == MXD_LINE_SIDE)
        {
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_PORT_REG, MXD_PORT_PWD_RESET, 14, 1, 1));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_PORT_REG, MXD_PORT_PWD_RESET, 14, 1, 0));
        }
        else if (host_or_line == MXD_HOST_SIDE)
        {
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_PORT_REG, MXD_PORT_PWD_RESET, 6, 1, 1));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_PORT_REG, MXD_PORT_PWD_RESET, 6, 1, 0));
        }
        else
        {
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_PORT_REG, MXD_PORT_PWD_RESET, 14, 1, 1));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_PORT_REG, MXD_PORT_PWD_RESET, 14, 1, 0));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_PORT_REG, MXD_PORT_PWD_RESET, 6, 1, 1));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_PORT_REG, MXD_PORT_PWD_RESET, 6, 1, 0));
        }
    }
    else
    {
        MXD_DBG_INFO("mxdPortReset incorrect resetType: 0x%x\n", resetType);
        return MXD_FAIL;
    }

    mxdPortResetTimeout(pDev, mdioPort, timeoutMs);

    return MXD_OK;
}


/*******************************************************************
 MXD_STATUS mxdChipAndZ80ResetControl

 Perform a chip hardware Soft or Hard reset and/or a Z80 reset; 
 save any registers we might need if we need power-on default of 
 registers to restore later
*******************************************************************/
MXD_STATUS mxdChipAndZ80ResetControl
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 resetType,
    IN MXD_BOOL bRestore
)
{
    MXD_U16 needRestore = 0;

    if (!pDev)
    {
        MXD_DBG_INFO("mxdChipAndZ80ResetControl: device in NULL\n");
        return MXD_FAIL;
    }


    if (bRestore && (resetType & MXD_CHIP_HW_RESET))
    {
        /* TBD: save any registers we might need if
           we need power-on default of registers to restore later */

        needRestore = 1;
    }

    switch (resetType)
    {
        case MXD_CHIP_SW_RESET:
            ATTEMPT(mxdHwSetPhyRegField(pDev, pDev->mdioPort, MXD_CHIP_REG, MXD_GLOBAL_RESET, 15, 1, 1));
            break;

        case MXD_CHIP_HW_RESET:
            ATTEMPT(mxdHwSetPhyRegField(pDev, pDev->mdioPort, MXD_CHIP_REG, MXD_GLOBAL_RESET, 14, 1, 1));
            break;

        case (MXD_CHIP_HW_RESET | MXD_Z80_RESET):
            ATTEMPT(mxdHwSetPhyRegField(pDev, pDev->mdioPort, MXD_CHIP_REG, MXD_GLOBAL_RESET, 13, 2, 3));
            break;

        case MXD_Z80_RESET:
            ATTEMPT(mxdHwSetPhyRegField(pDev, pDev->mdioPort, MXD_CHIP_REG, MXD_GLOBAL_RESET, 13, 1, 1));
            break;

        case MXD_Z80_RESET_RELEASE:
            ATTEMPT(mxdHwSetPhyRegField(pDev, pDev->mdioPort, MXD_CHIP_REG, MXD_GLOBAL_RESET, 13, 1, 0));
            break;

        default:
            MXD_DBG_INFO("mxdChipAndZ80ResetControl incorrect resetType: 0x%04X\n", (MXD_U16)resetType);
            return MXD_FAIL;
    }

    if (needRestore)
    {
        /* TBD: restore registers saved above */
    }

    return MXD_OK;
}




