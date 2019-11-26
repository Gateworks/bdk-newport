/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions prototypes and global defines/data for
higher-level functions using MDIO access to download firmware into 
the internal RAM and programming the EEPROM of the 
Marvell X7120/X6181/X6141 PHY.
********************************************************************/
#include "mydApiTypes.h"
#include "mydApiRegs.h"
#include "mydUtils.h"
#include "mydHwCntl.h"
#include "mydAPI.h"
#include "mydFwDownload.h"
#include "mydIntrIOConfig.h"
#include "mydAPIInternal.h"
#include "mydInitialization.h"
#include "mydHwSerdesCntl.h"
#include "mydZ80L64kB.h"

#if DB_TEST_ENVIRONMENT
#include "tstSMIInterface.h" 
#endif

MYD_STATUS mydIndirectSBusFwImageWrite
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 sBusReceiverAddr, 
    IN MYD_U16 regAddr, 
    IN MYD_U16 *image, 
    IN MYD_U16 imageSize
);

#if MYD_FW_WRITE_VERIFIED
    #define MYD_INDIRECT_SBUS_WRITE mydIndirectSBusWrite
#else
    #define MYD_INDIRECT_SBUS_WRITE mydIndirectSBusWriteNoVerify
#endif

/******************************************************************************
 MYD_STATUS mydLoadSBusSerdesFW
*******************************************************************************/
MYD_STATUS mydLoadSBusSerdesFW
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 imageSize,
    IN MYD_U16 image[],
    OUT MYD_U16 *errCode
)
{
    MYD_U16 serdesID;
    MYD_U16 resultCode = 0;
    MYD_U16 interruptResult = 0;

    *errCode = MYD_OK;

    /* SBUS SPICO into Reset and Enable off */
    /* Place SerDes in Reset & disable SPICO */
    ATTEMPT(MYD_INDIRECT_SBUS_WRITE(pDev, mdioPort, MYD_SBUS_SBUS_SERDES, 0x07, 0x0, 0x11, &resultCode));
    if ((resultCode & 0x7) != MYD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MYD_FW_FAIL_WRITE_REG;
        return MYD_FAIL;
    }

    /* Remove Serdes Reset */
    ATTEMPT(MYD_INDIRECT_SBUS_WRITE(pDev, mdioPort, MYD_SBUS_SBUS_SERDES, 0x07, 0x0, 0x10, &resultCode));
    if ((resultCode & 0x7) != MYD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MYD_FW_FAIL_WRITE_REG;
        return MYD_FAIL;
    }
    
    /* Assert IMEM override */
    ATTEMPT(MYD_INDIRECT_SBUS_WRITE(pDev, mdioPort, MYD_SBUS_SBUS_SERDES, 0x00, 0x4000, 0x0000, &resultCode));
    if ((resultCode & 0x7) != MYD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MYD_FW_FAIL_WRITE_REG;
        return MYD_FAIL;
    }
    
    /* Burst write FW into IMEM */
#if (MYD_FW_MDIO_BURST_MODE && !MYD_FW_WRITE_VERIFIED)
    if (mydFwImageBurstWrite(pDev, mdioPort, MYD_SBUS_SBUS_SERDES, 0x0A, image, imageSize) < S_OK)
    {
        MYD_DBG_ERROR("mydLoadSBusMasterFW: write to register failed imageSize: %d\n", imageSize);
        *errCode = MYD_FW_FAIL_WRITE_REG;
        return MYD_FAIL;
    }
#else
    if (mydIndirectSBusFwImageWrite(pDev, mdioPort, MYD_SBUS_SBUS_SERDES, 0x0A, image, imageSize) != MYD_OK) /* failed */
    {
        MYD_DBG_ERROR("mydLoadSBusMasterFW: write to register failed imageSize: %d\n", imageSize);
        *errCode = MYD_FW_FAIL_WRITE_REG;
        return MYD_FAIL;
    }
#endif

    /* Reset System  IMEM override off */
    ATTEMPT(MYD_INDIRECT_SBUS_WRITE(pDev, mdioPort, MYD_SBUS_SBUS_SERDES, 0x00, 0x0000, 0x0000, &resultCode));
    if ((resultCode & 0x7) != MYD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MYD_FW_FAIL_WRITE_REG;
        return MYD_FAIL;
    }
    
    /* Turn ECC on */
    ATTEMPT(MYD_INDIRECT_SBUS_WRITE(pDev, mdioPort, MYD_SBUS_SBUS_SERDES, 0x0B, 0xC, 0x0000, &resultCode));
    if ((resultCode & 0x7) != MYD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MYD_FW_FAIL_WRITE_REG;
        return MYD_FAIL;
    }
    
    /* Turn SPICO Enable on */
    ATTEMPT(MYD_INDIRECT_SBUS_WRITE(pDev, mdioPort, MYD_SBUS_SBUS_SERDES, 0x07, 0x0, 0x0002, &resultCode));
    if ((resultCode & 0x7) != MYD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MYD_FW_FAIL_WRITE_REG;
        return MYD_FAIL;
    }
    
    /* Enable core and hardware interrupts */
    ATTEMPT(MYD_INDIRECT_SBUS_WRITE(pDev, mdioPort, MYD_SBUS_SBUS_SERDES, 0x08, 0x0, 0x0, &resultCode));
    if ((resultCode & 0x7) != MYD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MYD_FW_FAIL_WRITE_REG;
        return MYD_FAIL;
    }
    
    /* check IMEM swap CRC for each serdes */
    for (serdesID = 0; serdesID < MYD_SERDES_LANE_COUNT; serdesID++)
    {
        mydSerdesInterrupt(pDev, mdioPort, (serdesID + 1), 0x3C, 0x00, &interruptResult);
        if (interruptResult != 0x00) /* not passed */
        {
            *errCode = (MYD_U16)MYD_FW_CRC_CHECKSUM_ERROR;
            MYD_DBG_ERROR("mydLoadSBusSerdesFW: mydSerdesInterrupt failed interruptResult: 0x%x\n", interruptResult);
            return MYD_FAIL;
        }
    }

    return MYD_OK;
}


/******************************************************************************
 MYD_STATUS mydLoadSBusMasterFW
*******************************************************************************/
MYD_STATUS mydLoadSBusMasterFW
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 imageSize,
    IN MYD_U16 image[],
    OUT MYD_U16 *errCode
)
{
    MYD_U16 resultCode = 0;
    MYD_U16 interruptResult = 0;
    MYD_U16 interruptStatus = 0;

    *errCode = MYD_OK;
    
    /* Halt Processor */
    ATTEMPT(MYD_INDIRECT_SBUS_WRITE(pDev, mdioPort, MYD_SBUS_SBUS_MASTER, 0x05, 0x00, 0x01, &resultCode));
    if ((resultCode & 0x7) != MYD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MYD_FW_FAIL_WRITE_REG;
        return MYD_FAIL;
    }

    /* SBUS SPICO into Reset and Enable off */
    ATTEMPT(MYD_INDIRECT_SBUS_WRITE(pDev, mdioPort, MYD_SBUS_SBUS_MASTER, 0x01, 0x00, 0xc0, &resultCode));
    if ((resultCode & 0x7) != MYD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MYD_FW_FAIL_WRITE_REG;
        return MYD_FAIL;
    }

    /* Remove Reset, Enable off, IMEM_CNTL_EN on */
    ATTEMPT(MYD_INDIRECT_SBUS_WRITE(pDev, mdioPort, MYD_SBUS_SBUS_MASTER, 0x01, 0x0, 0x0240, &resultCode));
    if ((resultCode & 0x7) != MYD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MYD_FW_FAIL_WRITE_REG;
        return MYD_FAIL;
    }

    /* Remove Halt */
    ATTEMPT(MYD_INDIRECT_SBUS_WRITE(pDev, mdioPort, MYD_SBUS_SBUS_MASTER, 0x05, 0x8000, 0x0000, &resultCode));
    if ((resultCode & 0x7) != MYD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MYD_FW_FAIL_WRITE_REG;
        return MYD_FAIL;
    }

    /* Set starting IMEM address for burst download */
    ATTEMPT(MYD_INDIRECT_SBUS_WRITE(pDev, mdioPort, MYD_SBUS_SBUS_MASTER, 0x03, 0x8000, 0x0000, &resultCode));
    if ((resultCode & 0x7) != MYD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MYD_FW_FAIL_WRITE_REG;
        return MYD_FAIL;
    }
    
    /* Burst write FW into IMEM */
#if (MYD_FW_MDIO_BURST_MODE && !MYD_FW_WRITE_VERIFIED)
    if(mydFwImageBurstWrite(pDev, mdioPort, MYD_SBUS_SBUS_MASTER, 0x14, image, imageSize) < 0)
    {
        MYD_DBG_ERROR("mydLoadSBusMasterFW: write to register failed imageSize: %d\n", imageSize);
        *errCode = MYD_FW_FAIL_WRITE_REG;
        return MYD_FAIL;
    }
#else
    if (mydIndirectSBusFwImageWrite(pDev, mdioPort, MYD_SBUS_SBUS_MASTER, 0x14, image, imageSize) != MYD_OK) /* failed */
    {
        MYD_DBG_ERROR("mydLoadSBusMasterFW: write to register failed imageSize: %d\n", imageSize);
        *errCode = MYD_FW_FAIL_WRITE_REG;
        return MYD_FAIL;
    }
#endif

    /* Reset System - Set IMEM_CNTL_EN off */
    ATTEMPT(MYD_INDIRECT_SBUS_WRITE(pDev, mdioPort, MYD_SBUS_SBUS_MASTER, 0x01, 0x00, 0x40, &resultCode));
    if ((resultCode & 0x7) != MYD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MYD_FW_FAIL_WRITE_REG;
        return MYD_FAIL;
    }
    
    /* Turn ECC on */
    ATTEMPT(MYD_INDIRECT_SBUS_WRITE(pDev, mdioPort, MYD_SBUS_SBUS_MASTER, 0x16, 0xC, 0x0000, &resultCode));
    if ((resultCode & 0x7) != MYD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MYD_FW_FAIL_WRITE_REG;
        return MYD_FAIL;
    }
    
    /* Set SPICO_ENABLE on */
    ATTEMPT(MYD_INDIRECT_SBUS_WRITE(pDev, mdioPort, MYD_SBUS_SBUS_MASTER, 0x01, 0x00, 0x140, &resultCode));
    if ((resultCode & 0x7) != MYD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MYD_FW_FAIL_WRITE_REG;
        return MYD_FAIL;
    }


    /* SBUS interrupt Code, CRC check no data */
    ATTEMPT(MYD_INDIRECT_SBUS_WRITE(pDev, mdioPort, MYD_SBUS_SBUS_MASTER, 0x02, 0x00, 0x02, &resultCode));
    if ((resultCode & 0x7) != MYD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MYD_FW_FAIL_WRITE_REG;
        return MYD_FAIL;
    }


    /* Set SBUS interrupt */
    ATTEMPT(MYD_INDIRECT_SBUS_WRITE(pDev, mdioPort, MYD_SBUS_SBUS_MASTER, 0x07, 0x00, 0x01, &resultCode));
    if ((resultCode & 0x7) != MYD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MYD_FW_FAIL_WRITE_REG;
        return MYD_FAIL;
    }

    /* Read CRC results */
    ATTEMPT(mydSbusInterrupt(pDev, mdioPort, 0x08, 0x01, &interruptResult, &interruptStatus));
    if (interruptStatus != 0x01) 
    {
        MYD_DBG_ERROR("mydLoadSBusMasterFW: SBUS CRC failed: 0%x\n", interruptStatus);
        *errCode = (MYD_U16)MYD_FW_CRC_CHECKSUM_ERROR;
        return MYD_FAIL;
    }

    return MYD_OK;
}

/******************************************************************************
 MYD_STATUS mydLoadZ80FWImage
*******************************************************************************/
MYD_STATUS mydLoadZ80FWImage
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 imageSize,
    IN MYD_U16 image[],
    IN MYD_BOOL reset,
    OUT MYD_U16 *errCode
)
{
    MYD_U16 i;
    MYD_U16 readValue;
    MYD_U16 regNIMB = MYD_NIMB_REG;
    MYD_U8 checksum = 0;

    *errCode = MYD_OK;

    if (reset)
    {
        /* chip reset and put Z80 into reset leaving it in reset */
        ATTEMPT(mydPortAndZ80ResetControl(pDev, mdioPort, MYD_Z80_RESET, MYD_FALSE)); 
    }

    /* set start address to 0x0 */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF840, 0x0000)); 
    /* set mem access to write increment */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF844, 0x0002)); 

    for (i=0; i<imageSize; i++)
    {
        /* write data */
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, image[i])); 

        checksum += (MYD_U8)((image[i]&0xFF) + ((image[i]&0xFF00)>>8));
        /* write command */
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));   
    }
    
    /* read checksum */
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, regNIMB, 0xF847, &readValue)); 

    if ((readValue & 0xFF) != checksum)
    {
        MYD_DBG_ERROR("mydLoadZ80FWImage: Z80 checksum mismatched - read checksum:0X%04X; calculated checksum:0X%04X\n", 
                      readValue, checksum);
        *errCode = MYD_FW_CRC_CHECKSUM_ERROR;
        return MYD_FAIL;
    }

#if MYD_FW_WRITE_VERIFIED
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF840, 0x0000)); 
    /* set mem access to read increment */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF844, 0x0001)); 

    for (i=0; i<imageSize; i++)
    {
        /* read command */
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0001));    
        /* read data */
        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, regNIMB, 0xF842, &readValue)); 

        if (readValue != image[i])
        {
            MYD_DBG_ERROR("mydLoadZ80FWImage: Image mismatched at location:%u, readValue:0X%04X imageValue:0X%04X\n", i, readValue, image[i]);
            *errCode = MYD_FW_IMAGE_MISMATCHED;
            return MYD_FAIL;
        }
    }
#endif    
    return MYD_OK;
}


/******************************************************************************
 MYD_STATUS mydIndirectSBusFwImageWrite (internal used)
*******************************************************************************/
MYD_STATUS mydIndirectSBusFwImageWrite
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 sBusReceiverAddr, 
    IN MYD_U16 regAddr, 
    IN MYD_U16 *image, 
    IN MYD_U16 imageSize
)
{
    MYD_U16 tempData[3];
    MYD_U16 dataH, dataL;
    MYD_U16 i, remainder;
    MYD_U32 packedData;

    /* Set Sbus command receive data valid selection mode to level */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_RX_DATA_VALID, 0x00));

    /* Store the command, SBus receiver address, and register address */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_COMMAND_REG, MYD_SBUS_WRITE));
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_ADDR_REG,
                            (MYD_U16)((sBusReceiverAddr & 0xFF) << 8 | (regAddr & 0xFF))));

    /* Set [31:30] 3,Set [29:20] equal to 3rd data_word, 
       Set [19:10] equal to 2nd data word, Set [9:0] equal to 1st data word */
    for(i=0; i<(imageSize/3); i++)
    {
        tempData[0] = image[(i*3)];   
        tempData[1] = image[(i*3)+1];
        tempData[2] = image[(i*3)+2];

        packedData = (MYD_U32)(((0x3 & 0x3) << 30) + ((tempData[2] & 0x3FF) << 20) + 
                               ((tempData[1] & 0x3FF) << 10) + (tempData[0] & 0x3FF));

        dataH = (MYD_U16)((packedData >> 16) & 0xFFFF);
        dataL = (MYD_U16)(packedData & 0xFFFF);

        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_INPUT_DATA_H, dataH));
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_INPUT_DATA_L, dataL));

        if (MYD_FW_WRITE_VERIFIED)
        {
            if (mydExecuteIndirectSBusCmd(pDev, mdioPort))
            {
                MYD_DBG_ERROR("mydIndirectSBusFwImageWrite: mydExecuteIndirectSBusCmd failed index: %d\n", i);
                return MYD_FAIL;
            }
        }
        else
        {
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_EXECUTION, 0x1));
        }
    }

    remainder = (imageSize % 3);
    if (remainder)
    {
        tempData[1] = tempData[2] = 0;

        tempData[0] = image[(i*3)];

        if (remainder == 2)
            tempData[1] = image[(i*3)+1];;
            
        packedData = (MYD_U32)(((remainder & 0x3) << 30) + ((tempData[2] & 0x3FF) << 20) + 
                               ((tempData[1] & 0x3FF) << 10) + (tempData[0] & 0x3FF));

        dataH = (MYD_U16)((packedData >> 16) & 0xFFFF);
        dataL = (MYD_U16)(packedData & 0xFFFF);

        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_INPUT_DATA_H, dataH));
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_INPUT_DATA_L, dataL));

        if (MYD_FW_WRITE_VERIFIED)
        {
            if (mydExecuteIndirectSBusCmd(pDev, mdioPort))
            {
                MYD_DBG_ERROR("mydIndirectSBusFwImageWrite: mydExecuteIndirectSBusCmd remainder failed index: %d\n", i);
                return MYD_FAIL;
            }
        }
        else
        {
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_EXECUTION, 0x1));
        }
    }
        
    /* clean execution bit */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_EXECUTION, 0x00));

    return MYD_OK;
}

/******************************************************************************
 MYD_STATUS mydLoadEEPROMImageToRAM
*******************************************************************************/
MYD_STATUS mydLoadEEPROMImageToRAM
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_BOOL loadAllPorts
)
{
    MYD_U16 i, j;
    MYD_U16 temp = 0;
    MYD_U16 successLoadCount = 0;
    MYD_U16 loadPortCount, portIndex;

    loadPortCount = (loadAllPorts == MYD_TRUE)? pDev->portCount:1;
    mdioPort = (loadAllPorts == MYD_TRUE)? pDev->mdioPort:mdioPort;

    for (j=0; j<3; j++) /* retry if needed */
    {
        for (portIndex = mdioPort; portIndex < mdioPort+loadPortCount; portIndex++)
        {
            /* Marvell ROM load disabled */
            ATTEMPT(mydHwSetPhyRegField(pDev, portIndex, MYD_CHIP_REG, 0xF416, 0, 1, 0)); 

            /* EEPROM is copied into RAM after chip comes out of reset. */
            ATTEMPT(mydHwSetPhyRegField(pDev, portIndex, MYD_CHIP_REG, 0xF418, 0, 1, 0)); 

            ATTEMPT(mydPortAndZ80ResetControl(pDev, portIndex, (MYD_PORT_HW_RESET|MYD_Z80_RESET), MYD_FALSE)); 

            for (i=0; i<5; i++) /* poll max 2.5 sec */
            {
                ATTEMPT(mydWait(pDev, 500)); /*  */

                ATTEMPT(mydHwXmdioRead(pDev, portIndex, MYD_NIMB_REG, 0xF845, &temp)); 

                if ((temp & 0x0001) == 1) 
                {
                    /* MYD_DBG_INFO("mydLoadEEPROMImageToRAM: Load to RAM successfully in %u sec. Return val:0x%X\n", i, temp); */
                    successLoadCount++;
                    pDev->devEEPROM = MYD_TRUE;
                    break; 
                }
            }

            ATTEMPT(mydPortAndZ80ResetControl(pDev, portIndex, MYD_Z80_RESET_RELEASE, MYD_FALSE)); 

            if (successLoadCount == loadPortCount)
            {
                return MYD_OK;
            }

            if (i >= 5) /* retry if any port take more than 2.5s to load */
            {
                /* MYD_DBG_INFO("mydLoadEEPROMImageToRAM: Retry loading EEPROM to RAM\n"); */
                break;
            }
        }

        successLoadCount = 0;  /* reset counter fro retry */
    }    

    MYD_DBG_ERROR("mydLoadEEPROMImageToRAM: Load to RAM failed:0x%X.\n", temp);
    
    return MYD_FAIL;
}

#define MYD_NIMB_CHECKSUM 1
/******************************************************************************
 MYD_STATUS mydUpdateEEPROMImage
*******************************************************************************/
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
)
{
    MYD_U8  eepromImageHeader[11]; 
    MYD_U16 tempData[3];
    MYD_U16 sbusImageByteSize=0,serdesImageByteSize=0,z80ImageByteSize=0;
    MYD_U16 i, checksum=0, headerChecksum=0;
    MYD_U32 packedData;
    MYD_U16 remainder;
    MYD_U16 totalImageSize=0;
    MYD_U16 temp=0;
    MYD_U8  eepromImageData[4];
    MYD_U8  carryOver=0;
    MYD_U16 regNIMB = MYD_NIMB_REG;
    MYD_U16 portIndex = pDev->mdioPort;

    *errCode = MYD_OK;

    if (!pDev || !(pDev->devEnabled))
    {
        MYD_DBG_ERROR("mydUpdateEEPROMImage: Driver device is not initialized.\n");
        *errCode = MYD_STATUS_ERR_DEV;
        return MYD_FAIL;
    }

    /* If only one is provided, returns error */
    if (((sbusImageSize && serdesImageSize) == 0) && ((sbusImageSize + serdesImageSize) > 0))
    {
        MYD_DBG_ERROR("mydUpdateEEPROMImage: Both Serdes and SBus images must be provided.\n");
        *errCode = MYD_FW_INVALID_IMAGE_SIZE;
        return MYD_FAIL;
    }

    /* either Z80 or SBus/Serdes pair must be provided  */
    if (!((sbusImageSize && serdesImageSize) || z80ImageSize))
    {
        MYD_DBG_ERROR("mydUpdateEEPROMImage: Invalid image - either Z80 or SBus/Serdes pair must be provided\n");
        *errCode = MYD_FW_INVALID_IMAGE_SIZE;
        return MYD_FAIL;
    }

    for (portIndex = pDev->mdioPort; portIndex < pDev->portCount; portIndex++)
    {
        /* disabled copying ROM image to RAM */
        ATTEMPT(mydHwXmdioWrite(pDev, portIndex, MYD_CHIP_REG, 0xF418, 0x1)); 
    }

    /* setting the EEPROM to reload state */
    ATTEMPT(mydPortAndZ80ResetControl(pDev, mdioPort, (MYD_PORT_HW_RESET|MYD_Z80_RESET), MYD_FALSE));
    /* ATTEMPT(mydChipAndZ80ResetControl(pDev, MYD_Z80_RESET, MYD_FALSE)); */

    /* disabled copying ROM image to RAM */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, 0xF418, 1)); 

    /* compute Z80 checksum */
    for (i=0; i<z80ImageSize; i++)
    {
        checksum += (z80ImageData[i] & 0xFF);
        checksum += ((z80ImageData[i]>>8) & 0xFF);
    }

    /* compute chip image EEPROM size */
    z80ImageByteSize = z80ImageSize;

    /* compute SBus EEPROM size */
    sbusImageByteSize = (sbusImageSize/3)*4;
    if (sbusImageSize % 3) 
    {
        sbusImageByteSize +=4;
    }

    /* compute Serdes EEPROM size */
    serdesImageByteSize = (serdesImageSize/3)*4;
    if (serdesImageSize % 3) 
    {
        serdesImageByteSize +=4;
    }

    /* create the header table */
    if (z80ImageSize) 
    {
#if MYD_NIMB_CHECKSUM
        eepromImageHeader[0] = 0x6;    /* Prog checksum enabled:2; set I2C speed to 1MHz:1-0 */
#else
        eepromImageHeader[0] = 0x2;    /* Prog checksum enabled:2; set I2C speed to 1MHz:1-0 */
#endif
        eepromImageHeader[3] = 0x10;   /* The Prog Dest Addr is set to 0x1000 at the z80 makefile */               
    } else
    {
        eepromImageHeader[0] = 0x2;    /* Disable Prog checksum, set I2C speed to 1MHz */
        eepromImageHeader[3] = 0;      /* No Z80 image */            
    }
    
    eepromImageHeader[1] = ((z80ImageByteSize>>8) & 0xFF);
    eepromImageHeader[2] = (z80ImageByteSize & 0xFF);
    eepromImageHeader[4] = 0x0;    
    eepromImageHeader[5] = ((sbusImageByteSize>>8) & 0xFF);
    eepromImageHeader[6] = (sbusImageByteSize & 0xFF);
    eepromImageHeader[7] = ((serdesImageByteSize>>8) & 0xFF);
    eepromImageHeader[8] = (serdesImageByteSize & 0xFF);

    headerChecksum = 0;
    for (i=0; i<9; i++)
    {
        headerChecksum += eepromImageHeader[i];
    }

    eepromImageHeader[9] = ((headerChecksum>>8) & 0xFF);
    eepromImageHeader[10]= (headerChecksum & 0xFF);

    /* SerDes image will be loaded to upper EEPROM 64k; not needed for total size in lower 64k */
    if (z80ImageByteSize)
    {
#if MYD_NIMB_CHECKSUM
        totalImageSize = sbusImageByteSize + z80ImageByteSize + 11 + 2; /* eepromImageHeader=11 */ 
                                                                        /* 2-bytes Z80 checksum at end of buffer */
#else
        totalImageSize = sbusImageByteSize + z80ImageByteSize + 11; /* eepromImageHeader=11 */ 
#endif
    }
    else
    {
        totalImageSize = sbusImageByteSize + 11; /* eepromImageHeader=11 */ 
    }

    /* write 31.F856.1:0 to 2'b01; set I2C speed to 1Mbit/s */
    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, regNIMB, 0xF856, 1, 1, 0x1)); 

    /* EEPROM Image byte length */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF860, ((totalImageSize & 0xFF00) >> 8)));
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF861, (totalImageSize & 0xFF))); 

    /* EEPROM Dest Addr default 0x0000 */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF863, 0));
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF862, 0)); 

    /* RAM Source Addr default 0x1000 */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF864, 0x10));  
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF865, 0));

    /* starting address for loader image */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF840, 0x0000));
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF844, 0x0002));

    for (i=0; i<(sizeof(z80LoaderArray)/sizeof(MYD_U16)); i++)
    {
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, z80LoaderArray[i])); 
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));            
    }

    /* starting address for RAM image */
    /* word address; set start address to 2048 word size(2048*2-bytes) 0x1000 */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF840, 2048)); 
    /* ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF840, 0)); */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF844, 0x0002)); 

    for (i=0; i<10; i+=2)
    {
        temp = ((eepromImageHeader[i+1]<<8)|eepromImageHeader[i]);
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, temp));         
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));      
    }

    /* 1 byte remainder in header*/
    carryOver = eepromImageHeader[10];

    /* Convert sbus FW from 10bits to 8 bits */
    /* Set [31:30] Set [29:20] equal to 3rd data_word, 
       Set [19:10] equal to 2nd data word, Set [9:0] equal to 1st data word */
    for(i=0; i<(sbusImageSize/3); i++)
    {
        tempData[0] = sbusImageData[(i*3)];   
        tempData[1] = sbusImageData[(i*3)+1];
        tempData[2] = sbusImageData[(i*3)+2];

        packedData = (MYD_U32)(((0x3 & 0x3) << 30) + ((tempData[2] & 0x3FF) << 20) + 
                               ((tempData[1] & 0x3FF) << 10) + (tempData[0] & 0x3FF));

        eepromImageData[0] = (MYD_U8)(packedData & 0xff);
        eepromImageData[1] = (MYD_U8)((packedData>>8) & 0xff);
        eepromImageData[2] = (MYD_U8)((packedData>>16) & 0xff);

        temp = ((eepromImageData[0]<<8)|carryOver);
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, temp));        
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));      
        
        temp = ((eepromImageData[2]<<8)|eepromImageData[1]);
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, temp));   
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002)); 

        eepromImageData[3] = (MYD_U8)((packedData>>24) & 0xff);
        carryOver = eepromImageData[3];
    }

    remainder = (sbusImageSize % 3);
    if (remainder)
    {
        tempData[1] = sbusImageData[((i*3)-2)];
        tempData[2] = sbusImageData[((i*3)-1)];

        tempData[0] = sbusImageData[(i*3)];

        if (remainder == 2)
        {
            tempData[1] = sbusImageData[(i*3)+1];;
        }
            
        packedData = (MYD_U32)(((remainder & 0x3) << 30) + ((tempData[2] & 0x3FF) << 20) + 
                               ((tempData[1] & 0x3FF) << 10) + (tempData[0] & 0x3FF));

        eepromImageData[0] = (MYD_U8)(packedData & 0xff);
        eepromImageData[1] = (MYD_U8)((packedData>>8) & 0xff);
        eepromImageData[2] = (MYD_U8)((packedData>>16) & 0xff);

        temp = ((eepromImageData[0]<<8)|carryOver);
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, temp));      
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));    

        temp = ((eepromImageData[2]<<8)|eepromImageData[1]);
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, temp));     
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));   

        eepromImageData[3] = (MYD_U8)((packedData>>24) & 0xff);
        carryOver = eepromImageData[3];
    }

    /* write the 1 byte carryover */
    if (!z80ImageSize)
    {
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, carryOver));      
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));    
    }


    if (z80ImageSize)
    {
#if MYD_NIMB_CHECKSUM
        /* 2-bytes Z80 checksum at end of buffer */
        z80ImageSize += 2; 

        /* adds the 2 bytes checksum to the end */
        z80ImageData[z80ImageSize-2] = (MYD_U16)(checksum & 0xFF00)>>8;
        z80ImageData[z80ImageSize-1] = (MYD_U16)(checksum & 0x00FF);
        z80ImageData[z80ImageSize] = (MYD_U16)(0);
#endif

        temp = ((z80ImageData[0]<<8)|carryOver);
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, temp));      
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));    

        for (i=1; i<z80ImageSize; i+=2)
        {
            temp = ((z80ImageData[i+1]<<8) | z80ImageData[i]); 
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, temp));   
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002)); 
        }


    }

    /* SerDes image will load to the upper 64k */
    if (serdesImageSize)
    {
        MYD_BOOL writeComplete = MYD_FALSE;

        /* clear reset */
        ATTEMPT(mydPortAndZ80ResetControl(pDev, mdioPort, MYD_Z80_RESET_RELEASE, MYD_FALSE)); 

        for (i=0; i<200; i++)
        {
            ATTEMPT(mydWait(pDev, 100));

            /* check EEPROM Write Done flag */
            ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, regNIMB, 0xF846, 0, 1, &temp)); 

            if (temp == 1)
            {
                MYD_DBG_INFO("mydUpdateEEPROMImage: SBUS/Z80 images successfully written to EEPROM.\n");

                /* give it a 0.5 sec pause before write to upper 64K EEPROM */
                ATTEMPT(mydWait(pDev, 500));
                writeComplete = MYD_TRUE;
                break;
            }
        }

        if (writeComplete == MYD_FALSE)
        {
            MYD_DBG_ERROR("mydUpdateEEPROMImage: SBUS/Z80 image FAILED writing to EEPROM.\n");
            *errCode = MYD_FW_UNKNOWN_DOWNLOAD_EEPROM_ERR;
            return MYD_FAIL;
        }

        /* Write to the upper 64K; setting the EEPROM to reload state */
        ATTEMPT(mydPortAndZ80ResetControl(pDev, mdioPort, (MYD_PORT_HW_RESET|MYD_Z80_RESET), MYD_FALSE));
        
        /* disabled copying ROM image to RAM */
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, 0xF418, 1)); 

        /* write 31.F856.1:0 to 2'b01; set I2C speed to 1Mbit/s */
        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, regNIMB, 0xF856, 1, 1, 0x1)); 

        /* EEPROM Image byte length */
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF860, ((serdesImageByteSize & 0xFF00) >> 8)));
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF861, (serdesImageByteSize & 0xFF))); 

        /* EEPROM Dest Addr default */
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF862, 0)); 
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF863, 0));

        /* RAM Source Addr default 0x1000 */
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF864, 0x10));  
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF865, 0));

        /* write data to high 64k of EEPROM */
        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, regNIMB, 0xF866, 0, 1, 0x1)); 

        /* NIMB RAM access mode select write increment*/
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF844, 0x0002));

        /* Address to access NIMB RAM */
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF840, 0x0800));

        /* Convert sbus FW from 10bits to 8 bits */
        /* Set [31:30] Set [29:20] equal to 3rd data_word, 
           Set [19:10] equal to 2nd data word, Set [9:0] equal to 1st data word */
        for(i=0; i<(serdesImageSize/3); i++)
        {
            tempData[0] = serdesImageData[(i*3)];   
            tempData[1] = serdesImageData[(i*3)+1];
            tempData[2] = serdesImageData[(i*3)+2];

            packedData = (MYD_U32)(((0x3 & 0x3) << 30) + ((tempData[2] & 0x3FF) << 20) + 
                                   ((tempData[1] & 0x3FF) << 10) + (tempData[0] & 0x3FF));

            eepromImageData[0] = (MYD_U8)(packedData & 0xff);
            eepromImageData[1] = (MYD_U8)((packedData>>8) & 0xff);
            eepromImageData[2] = (MYD_U8)((packedData>>16) & 0xff);
            eepromImageData[3] = (MYD_U8)((packedData>>24) & 0xff);

            temp = ((eepromImageData[1]<<8)|eepromImageData[0]);
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, temp));      
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));    

            temp = ((eepromImageData[3]<<8)|eepromImageData[2]);
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, temp));      
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));    
        }

        remainder = (serdesImageSize % 3);
        if (remainder)
        {
            tempData[1] = serdesImageData[((i*3)-2)];
            tempData[2] = serdesImageData[((i*3)-1)];

            tempData[0] = serdesImageData[(i*3)];

            if (remainder == 2)
            {
                tempData[1] = serdesImageData[(i*3)+1];;
            }
            
            packedData = (MYD_U32)(((remainder & 0x3) << 30) + ((tempData[2] & 0x3FF) << 20) + 
                                   ((tempData[1] & 0x3FF) << 10) + (tempData[0] & 0x3FF));

            eepromImageData[0] = (MYD_U8)(packedData & 0xff);
            eepromImageData[1] = (MYD_U8)((packedData>>8) & 0xff);
            eepromImageData[2] = (MYD_U8)((packedData>>16) & 0xff);
            eepromImageData[3] = (MYD_U8)((packedData>>24) & 0xff);

            temp = ((eepromImageData[1]<<8)|eepromImageData[0]);
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, temp));      
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));    

            temp = ((eepromImageData[3]<<8)|eepromImageData[2]);
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, temp));      
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));    
        }
    } 

    /* clear reset */
    ATTEMPT(mydPortAndZ80ResetControl(pDev, mdioPort, MYD_Z80_RESET_RELEASE, MYD_FALSE)); 

    for (i=0; i<100; i++)
    {
        ATTEMPT(mydWait(pDev, 100));

        /* check EEPROM Write Done flag */
        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, regNIMB, 0xF846, 0, 1, &temp)); 

        if (temp == 1)
        {
            MYD_DBG_INFO("mydUpdateEEPROMImage: Images successfully written to EEPROM.\n");

            /* give it a sec pause before loading the EEPROM to the RAM */
            ATTEMPT(mydWait(pDev, 1000));
            if (mydLoadEEPROMImageToRAM(pDev, mdioPort, MYD_TRUE) == MYD_OK)
            {
                MYD_DBG_INFO("mydUpdateEEPROMImage: mydLoadEEPROMImageToRAM Completed\n");
                return MYD_OK;
            }
        }
    }

    MYD_DBG_ERROR("mydUpdateEEPROMImage: Failed\n");

    *errCode = MYD_FW_UNKNOWN_DOWNLOAD_EEPROM_ERR;
    return MYD_FAIL;
}

/******************************************************************************
 MYD_STATUS mydFirmwareDownload 
*******************************************************************************/
MYD_STATUS mydFirmwareDownload
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  *pZ80Image,
    IN MYD_U16  z80Size,
    IN MYD_U16  *pBusMasterImage,
    IN MYD_U16  busMasterSize,
    IN MYD_U16  *pSerdesImage,
    IN MYD_U16  serdesSize,
    IN MYD_BOOL loadAllPorts,
    IN MYD_BOOL broadcastMode
)
{
    MYD_U16 errCode;
    MYD_U16 portIndex = pDev->mdioPort;
    MYD_U16 loadPortCount;
    MYD_BOOL writeVerified;

    if (!(pBusMasterImage && pSerdesImage && busMasterSize && serdesSize))
    {
        MYD_DBG_ERROR("mydFirmwareDownload: Invalid image.\n");
        return MYD_STATUS_FIRMWARE_ERR;
    }

    loadPortCount = (loadAllPorts == MYD_TRUE)? pDev->portCount:1;
    writeVerified = (MYD_FW_WRITE_VERIFIED)? MYD_TRUE:MYD_FALSE;
    mdioPort = (loadAllPorts == MYD_TRUE)? pDev->mdioPort:mdioPort;

    if (((writeVerified == MYD_TRUE) && (broadcastMode == MYD_FALSE)) ||
        ((writeVerified == MYD_FALSE) && (broadcastMode == MYD_FALSE)))
    {
        for (portIndex = mdioPort; portIndex < mdioPort+loadPortCount; portIndex++)
        {
            /* optional to download Z80 image */
            if (pZ80Image && z80Size)
            {
                /* disabled copying EEPROM image to RAM */
                ATTEMPT(mydHwXmdioWrite(pDev, portIndex, MYD_CHIP_REG, 0xF418, 0x1)); 

                /* Firmware download for Z80, does a chip and Z80 reset and leaves Z80 in reset */
                if ((mydLoadZ80FWImage(pDev, portIndex, z80Size, pZ80Image,
                                        MYD_TRUE, &errCode)) != MYD_OK)
                {
                    MYD_DBG_ERROR("mydFirmwareDownload: portIndex: 0x%x, Z80 Firmware download errCode: 0x%x.\n", 
                                    portIndex, errCode);
                    return MYD_STATUS_FIRMWARE_ERR;
                }
            }
            else
            {
                /* disabled loading EEPROM image to RAM */
                ATTEMPT(mydHwXmdioWrite(pDev, portIndex, MYD_CHIP_REG, 0xF418, 0x1)); 

                /* reset MROM & AROM Loading */
                ATTEMPT(mydHwSetPhyRegField(pDev, portIndex, MYD_CHIP_REG, 0xF419, 1, 1, 0)); 
                /* chip reset and put Z80 into reset leaving it in reset */
                ATTEMPT(mydPortAndZ80ResetControl(pDev, portIndex, (MYD_PORT_HW_RESET|MYD_Z80_RESET), MYD_FALSE)); 

            }

            /* SBusMaster image download */
            if ((mydLoadSBusMasterFW(pDev, portIndex, busMasterSize,
                                     pBusMasterImage, &errCode)) != MYD_OK)
            {
                MYD_DBG_ERROR("mydFirmwareDownload: portIndex: 0x%x, SBusMaster image download errCode: 0x%x.\n", 
                                portIndex, errCode);
                return MYD_STATUS_FIRMWARE_ERR;
            }

            /* SBus Serdes image download */
            if ((mydLoadSBusSerdesFW(pDev, portIndex, serdesSize,
                                     pSerdesImage, &errCode)) != MYD_OK)
            {
                MYD_DBG_ERROR("mydFirmwareDownload: portIndex: 0x%x, SBus Serdes image download errCode: 0x%x.\n", 
                                portIndex, errCode);
                return MYD_STATUS_FIRMWARE_ERR;
            }
        }
    }
    else if ((writeVerified == MYD_FALSE) && (broadcastMode == MYD_TRUE))
    {  /* writeVerified off; use broadcast mode */ 
        for (portIndex = pDev->mdioPort; portIndex < mdioPort+loadPortCount; portIndex++)
        {
            /* disabled copying EEPROM image to RAM */
            ATTEMPT(mydHwXmdioWrite(pDev, portIndex, MYD_CHIP_REG, 0xF418, 0x1)); 
        }

        ATTEMPT(mydChipAndZ80ResetControl(pDev, (MYD_CHIP_HW_RESET|MYD_Z80_RESET), MYD_FALSE)); 

        /* optional to download Z80 image */
        if (pZ80Image && z80Size)
        {
            for (portIndex = pDev->mdioPort; portIndex < mdioPort+loadPortCount; portIndex++)
            {
                /* set broadcast */
                ATTEMPT(mydHwXmdioWrite(pDev, portIndex, MYD_CHIP_REG, 0xF403, 0x1)); 
            }

            if ((mydLoadZ80FWImage(pDev, pDev->mdioPort, z80Size, pZ80Image,
                                   MYD_FALSE, &errCode)) != MYD_OK)
            {
                MYD_DBG_ERROR("mydFirmwareDownload: portIndex: 0x%x, Z80 Firmware download errCode: 0x%x.\n", 
                                portIndex, errCode);
                return MYD_STATUS_FIRMWARE_ERR;
            }
        }

        for (portIndex = pDev->mdioPort; portIndex < mdioPort+loadPortCount; portIndex++)
        {
            /* set broadcast */
            ATTEMPT(mydHwXmdioWrite(pDev, portIndex, MYD_CHIP_REG, 0xF403, 0x1)); 
        }

        /* SBusMaster image download */
        if ((mydLoadSBusMasterFW(pDev, pDev->mdioPort, busMasterSize,
                                 pBusMasterImage, &errCode)) != MYD_OK)
        {
            MYD_DBG_ERROR("mydFirmwareDownload: portIndex: 0x%x, SBusMaster image download errCode: 0x%x.\n", 
                            pDev->mdioPort, errCode);
            return MYD_STATUS_FIRMWARE_ERR;
        }

        for (portIndex = pDev->mdioPort; portIndex < mdioPort+loadPortCount; portIndex++)
        {
            /* reset broadcast */
            ATTEMPT(mydHwXmdioWrite(pDev, portIndex, MYD_CHIP_REG, 0xF403, 0x1)); 
        }

        /* SBus Serdes image download */
        if ((mydLoadSBusSerdesFW(pDev, pDev->mdioPort, serdesSize,
                                 pSerdesImage, &errCode)) != MYD_OK)
        {
            MYD_DBG_ERROR("mydFirmwareDownload: portIndex: 0x%x, SBus Serdes image download errCode: 0x%x.\n", 
                            pDev->mdioPort, errCode);
            return MYD_STATUS_FIRMWARE_ERR;
        }

        for (portIndex = pDev->mdioPort; portIndex < mdioPort+loadPortCount; portIndex++)
        {
            /* disable broadcast */
            ATTEMPT(mydHwXmdioWrite(pDev, portIndex, MYD_CHIP_REG, 0xF403, 0x0)); 
        }
    }
    else
    {
        MYD_DBG_ERROR("mydFirmwareDownload: invalid writeVerified:%x and broadcastMode combinations:%x\n", 
                       writeVerified, broadcastMode);
        return MYD_FAIL;
    }

    return MYD_OK;
}
