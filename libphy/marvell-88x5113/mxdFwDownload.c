/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions prototypes and global defines/data for
higher-level functions using MDIO access to download firmware into 
the internal RAM and programming the EEPROM of the Marvell X5113 PHY.
********************************************************************/
#include "mxdApiTypes.h"
#include "mxdApiRegs.h"
#include "mxdUtils.h"
#include "mxdHwCntl.h"
#include "mxdAPI.h"
#include "mxdFwDownload.h"
#include "mxdAPIInternal.h"
#include "mxdInitialization.h"
#include "mxdHwSerdesCntl.h"
#include "mxdZ80L64kB.h"

MXD_STATUS mxdIndirectSBusFwImageWrite
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 sBusReceiverAddr, 
    IN MXD_U16 regAddr, 
    IN MXD_U16 *image, 
    IN MXD_U16 imageSize
);


/******************************************************************************
 MXD_STATUS mxdLoadSBusSerdesFW
*******************************************************************************/
MXD_STATUS mxdLoadSBusSerdesFW
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 imageSize,
    IN MXD_U16 image[],
    OUT MXD_U16 *errCode
)
{
    MXD_U16 serdesID;
    MXD_U16 resultCode = 0;
    MXD_U16 interruptResult = 0;
    MXD_STATUS status;

    *errCode = MXD_OK;

    /* SBUS SPICO into Reset and Enable off */
    /* Place SerDes in Reset & disable SPICO */
    ATTEMPT(mxdIndirectSBusWrite(pDev, mdioPort, MXD_SBUS_SBUS_SERDES, 0x07, 0x0, 0x11, &resultCode));
    if ((resultCode & 0x7) != MXD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MXD_FW_FAIL_WRITE_REG;
        return MXD_FAIL;
    }

    /* Remove Serdes Reset */
    ATTEMPT(mxdIndirectSBusWrite(pDev, mdioPort, MXD_SBUS_SBUS_SERDES, 0x07, 0x0, 0x10, &resultCode));
    if ((resultCode & 0x7) != MXD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MXD_FW_FAIL_WRITE_REG;
        return MXD_FAIL;
    }
    
    /* Assert IMEM override */
    ATTEMPT(mxdIndirectSBusWrite(pDev, mdioPort, MXD_SBUS_SBUS_SERDES, 0x00, 0xC000, 0x0000, &resultCode));
    if ((resultCode & 0x7) != MXD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MXD_FW_FAIL_WRITE_REG;
        return MXD_FAIL;
    }
    
    /* Burst write FW into IMEM */
    status = mxdIndirectSBusFwImageWrite(pDev, mdioPort, MXD_SBUS_SBUS_SERDES, 0x0A, image, imageSize);
    if (status != MXD_OK) /* failed */
    {
        MXD_DBG_ERROR("mxdLoadSBusMasterFW: write to register failed imageSize: %d\n", imageSize);
        *errCode = MXD_FW_FAIL_WRITE_REG;
        return MXD_FAIL;
    }

    /* Reset System  IMEM override off */
    ATTEMPT(mxdIndirectSBusWrite(pDev, mdioPort, MXD_SBUS_SBUS_SERDES, 0x00, 0x0000, 0x0000, &resultCode));
    if ((resultCode & 0x7) != MXD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MXD_FW_FAIL_WRITE_REG;
        return MXD_FAIL;
    }
    
    /* Turn ECC on */
    ATTEMPT(mxdIndirectSBusWrite(pDev, mdioPort, MXD_SBUS_SBUS_SERDES, 0x0B, 0xC, 0x0000, &resultCode));
    if ((resultCode & 0x7) != MXD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MXD_FW_FAIL_WRITE_REG;
        return MXD_FAIL;
    }
    
    /* Turn SPICO Enable on */
    ATTEMPT(mxdIndirectSBusWrite(pDev, mdioPort, MXD_SBUS_SBUS_SERDES, 0x07, 0x0, 0x0002, &resultCode));
    if ((resultCode & 0x7) != MXD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MXD_FW_FAIL_WRITE_REG;
        return MXD_FAIL;
    }
    
    /* Enable core and hardware interrupts */
    ATTEMPT(mxdIndirectSBusWrite(pDev, mdioPort, MXD_SBUS_SBUS_SERDES, 0x08, 0x0, 0x0, &resultCode));
    if ((resultCode & 0x7) != MXD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MXD_FW_FAIL_WRITE_REG;
        return MXD_FAIL;
    }
    
    /* check IMEM swap CRC for each serdes */
    for (serdesID = 0; serdesID < MXD_SERDES_LANE_COUNT; serdesID++)
    {
        mxdSerdesInterrupt(pDev, mdioPort, (serdesID + 1), 0x3C, 0x00, &interruptResult);
        if (interruptResult != 0x00) /* not passed */
        {
            *errCode = (MXD_U16)MXD_FW_CRC_CHECKSUM_ERROR;
            MXD_DBG_ERROR("mxdLoadSBusSerdesFW: mxdSerdesInterrupt failed interruptResult: 0x%x\n", interruptResult);
            return MXD_FAIL;
        }
    }

    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdLoadSBusMasterFW
*******************************************************************************/
MXD_STATUS mxdLoadSBusMasterFW
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 imageSize,
    IN MXD_U16 image[],
    OUT MXD_U16 *errCode
)
{
    MXD_U16 resultCode = 0;
    MXD_U16 interruptResult = 0;
    MXD_U16 interruptStatus = 0;
    MXD_STATUS status;

    *errCode = MXD_OK;

    /* SBUS SPICO into Reset and Enable off */
    ATTEMPT(mxdIndirectSBusWrite(pDev, mdioPort, MXD_SBUS_SBUS_MASTER, 0x01, 0x00, 0xc0, &resultCode));
    if ((resultCode & 0x7) != MXD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MXD_FW_FAIL_WRITE_REG;
        return MXD_FAIL;
    }

    /* Remove Reset, Enable off, IMEM_CNTL_EN on */
    ATTEMPT(mxdIndirectSBusWrite(pDev, mdioPort, MXD_SBUS_SBUS_MASTER, 0x01, 0x0, 0x0240, &resultCode));
    if ((resultCode & 0x7) != MXD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MXD_FW_FAIL_WRITE_REG;
        return MXD_FAIL;
    }
    
    /* Set starting IMEM address for burst download */
    ATTEMPT(mxdIndirectSBusWrite(pDev, mdioPort, MXD_SBUS_SBUS_MASTER, 0x03, 0x8000, 0x0000, &resultCode));
    if ((resultCode & 0x7) != MXD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MXD_FW_FAIL_WRITE_REG;
        return MXD_FAIL;
    }
    
    /* Burst write FW into IMEM */
    status = mxdIndirectSBusFwImageWrite(pDev, mdioPort, MXD_SBUS_SBUS_MASTER, 0x14, image, imageSize);
    if (status != MXD_OK) /* failed */
    {
        MXD_DBG_ERROR("mxdLoadSBusMasterFW: write to register failed imageSize: %d\n", imageSize);
        *errCode = MXD_FW_FAIL_WRITE_REG;
        return MXD_FAIL;
    }

    /* Reset System - Set IMEM_CNTL_EN off */
    ATTEMPT(mxdIndirectSBusWrite(pDev, mdioPort, MXD_SBUS_SBUS_MASTER, 0x01, 0x00, 0x40, &resultCode));
    if ((resultCode & 0x7) != MXD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MXD_FW_FAIL_WRITE_REG;
        return MXD_FAIL;
    }
    
    /* Turn ECC on */
    ATTEMPT(mxdIndirectSBusWrite(pDev, mdioPort, MXD_SBUS_SBUS_MASTER, 0x16, 0xC, 0x0000, &resultCode));
    if ((resultCode & 0x7) != MXD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MXD_FW_FAIL_WRITE_REG;
        return MXD_FAIL;
    }
    
    /* Set SPICO_ENABLE on */
    ATTEMPT(mxdIndirectSBusWrite(pDev, mdioPort, MXD_SBUS_SBUS_MASTER, 0x01, 0x00, 0x140, &resultCode));
    if ((resultCode & 0x7) != MXD_SBUS_WRITE_COMPLETE)
    {
        *errCode = MXD_FW_FAIL_WRITE_REG;
        return MXD_FAIL;
    }
    
    /* check XDMEM CRC */
    mxdSbusInterrupt(pDev, mdioPort, 0x02, 0x00, &interruptResult, &interruptStatus);
    if (interruptResult != 0x01) 
    {
        MXD_DBG_ERROR("mxdLoadSBusMasterFW: check XDMEM CRC failed: 0x%x\n", interruptResult);
        *errCode = (MXD_U16)MXD_FW_CRC_CHECKSUM_ERROR;
        return MXD_FAIL;
    }

    /* check IMEM swap CRC */
    mxdSbusInterrupt(pDev, mdioPort, 0x1A, 0x0, &interruptResult, &interruptStatus);
    if (interruptResult != 0x01) 
    {
        MXD_DBG_ERROR("mxdLoadSBusMasterFW: check IMEM swap CRC failed: 0%x\n", interruptResult);
        *errCode = (MXD_U16)MXD_FW_CRC_CHECKSUM_ERROR;
        return MXD_FAIL;
    }

    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdLoadZ80FWImage
*******************************************************************************/
MXD_STATUS mxdLoadZ80FWImage
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 imageSize,
    IN MXD_U16 image[],
    IN MXD_BOOL reset,
    OUT MXD_U16 *errCode
)
{
    MXD_U16 i;
    MXD_U16 readValue;
    MXD_U16 regNIMB = MXD_CHIP_REG;

    *errCode = MXD_OK;

    if (reset)
    {
        /* chip reset and put Z80 into reset leaving it in reset */
        ATTEMPT(mxdChipAndZ80ResetControl(pDev, (MXD_CHIP_HW_RESET|MXD_Z80_RESET), MXD_FALSE)); 
    }

    if (pDev->chipRevision == MXD_REV_A1)
    {
        regNIMB = MXD_A1_NIMB_REG;
    }

    /* disabled copying image to RAM */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, 0xF418, 0x1)); 

    /* set start address to 0x0 */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF840, 0x0000)); 
    /* set mem access to write increment */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF844, 0x0002)); 

    for (i=0; i<imageSize; i++)
    {
        /* write data */
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, image[i])); 
        /* write command */
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));   
    }
    
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF840, 0x0000)); 
    /* set mem access to read increment */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF844, 0x0001)); 

    for (i=0; i<imageSize; i++)
    {
        /* read command */
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x1));    
        /* read data */
        ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, regNIMB, 0xF842, &readValue)); 

        if (readValue != image[i])
        {
            MXD_DBG_ERROR("mxdLoadZ80FWImage: Image mismatched at location:%u, readValue:0X%04X imageValue:0X%04X\n", i, readValue, image[i]);
            *errCode = MXD_FW_IMAGE_MISMATCHED;
            return MXD_FAIL;
        }
    }
    
    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdIndirectSBusFwImageWrite
*******************************************************************************/
MXD_STATUS mxdIndirectSBusFwImageWrite
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 sBusReceiverAddr, 
    IN MXD_U16 regAddr, 
    IN MXD_U16 *image, 
    IN MXD_U16 imageSize
)
{
    MXD_U16 tempData[3];
    MXD_U16 DataH, DataL;
    MXD_U16 i, remainder;
    MXD_U32 packedData;

    /* Set Sbus command receive data valid selection mode to level */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_RX_DATA_VALID, 0x00));

    /* Store the command, SBus receiver address, and register address */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_COMMAND_REG, MXD_SBUS_WRITE));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_ADDR_REG,
                            (MXD_U16)((sBusReceiverAddr & 0xFF) << 8 | (regAddr & 0xFF))));

    /* Set [31:30] 3,Set [29:20] equal to 3rd data_word, 
       Set [19:10] equal to 2nd data word, Set [9:0] equal to 1st data word */
    for(i=0; i<(imageSize/3); i++)
    {
        tempData[0] = image[(i*3)];   
        tempData[1] = image[(i*3)+1];
        tempData[2] = image[(i*3)+2];

        packedData = (MXD_U32)(((0x3 & 0x3) << 30) + ((tempData[2] & 0x3FF) << 20) + 
                               ((tempData[1] & 0x3FF) << 10) + (tempData[0] & 0x3FF));

        DataH = (MXD_U16)((packedData >> 16) & 0xFFFF);
        DataL = (MXD_U16)(packedData & 0xFFFF);

        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_INPUT_DATA_H, DataH));
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_INPUT_DATA_L, DataL));

        if (mxdExecuteIndirectSBusCmd(pDev, mdioPort))
        {
            MXD_DBG_ERROR("mxdIndirectSBusFwImageWrite: mxdExecuteIndirectSBusCmd1 failed index: %d\n", i);
            return MXD_FAIL;
        }
    }

    remainder = (imageSize % 3);
    if (remainder)
    {
        tempData[1] = tempData[2] = 0;

        tempData[0] = image[(i*3)];

        if (remainder == 2)
            tempData[1] = image[(i*3)+1];;
            
        packedData = (MXD_U32)(((remainder & 0x3) << 30) + ((tempData[2] & 0x3FF) << 20) + 
                               ((tempData[1] & 0x3FF) << 10) + (tempData[0] & 0x3FF));

        DataH = (MXD_U16)((packedData >> 16) & 0xFFFF);
        DataL = (MXD_U16)(packedData & 0xFFFF);

        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_INPUT_DATA_H, DataH));
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_INPUT_DATA_L, DataL));

        if (mxdExecuteIndirectSBusCmd(pDev, mdioPort))
        {
            MXD_DBG_ERROR("mxdIndirectSBusFwImageWrite: mxdExecuteIndirectSBusCmd2 failed index: %d\n", i);
            return MXD_FAIL;
        }
    }
        
    /* clean execution bit */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_EXECUTION, 0x00));

    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdLoadEEPROMImageToRAM
*******************************************************************************/
MXD_STATUS mxdLoadEEPROMImageToRAM
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort
)
{
    MXD_U16 i, j;
    MXD_U16 temp = 0;
    MXD_U16 regNIMB = MXD_CHIP_REG;

    if (pDev->chipRevision == MXD_REV_A1)
    {
        regNIMB = MXD_A1_NIMB_REG;
    }

    for (j=0; j<3; j++) /* retry if needed */
    {
        /* do chip reset and put Z80 into reset leaving it in reset */
        ATTEMPT(mxdChipAndZ80ResetControl(pDev, MXD_CHIP_HW_RESET, MXD_FALSE));
    
        /* Disable MROM & AROM Loading */
        ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_CHIP_REG, 0xF419, 1, 2, 0)); 

        /* EEPROM is copied into RAM after chip comes out of reset. */
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, 0xF418, 0)); 

        /* increase 1 sec on each addition retry */
        ATTEMPT(mxdWait(pDev, 2000+(j*1000)));

        ATTEMPT(mxdChipAndZ80ResetControl(pDev, (MXD_CHIP_HW_RESET|MXD_Z80_RESET), MXD_FALSE)); 

        ATTEMPT(mxdWait(pDev, 1000));

        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_GLOBAL_RESET, 0)); 

        for (i=0; i<10; i++) /* poll max 5 sec */
        {
            ATTEMPT(mxdWait(pDev, 500)); /* 0.5 sec */

            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, regNIMB, 0xF845, &temp)); 

            if ((temp == 0x003d) || (temp == 0x002d)) 
            {
                MXD_DBG_INFO("mxdLoadEEPROMImageToRAM: Load to RAM completed successfully in %u sec. Return val:0x%X\n", i/2, temp);
                return MXD_OK;
            }
        }

        MXD_DBG_ERROR("mxdLoadEEPROMImageToRAM: Retry loading to RAM\n");
    }    

    MXD_DBG_ERROR("mxdLoadEEPROMImageToRAM: Load to RAM failed:0x%X.\n", temp);
    
    return MXD_FAIL;
}


/******************************************************************************
 MXD_STATUS mxdUpdateEEPROMImage
*******************************************************************************/
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
)
{
    MXD_U8  eepromImageHeader[11]; 
    MXD_U16 tempData[3];
    MXD_U16 sbusImageCntr=0,serdesImageCntr=0,z80ImageCntr=0;
    MXD_U16 i, checksum=0, headerChecksum=0;
    MXD_U32 packedData;
    MXD_U16 remainder;
    MXD_U16 totalImageSize=0;
    MXD_U16 temp=0;
    MXD_U8  eepromImageData[4];
    MXD_U8  carryOver=0;
    MXD_U16 regNIMB = MXD_CHIP_REG;

    *errCode = MXD_OK;

    if (!pDev || !(pDev->devEnabled))
    {
        MXD_DBG_ERROR("mxdUpdateEEPROMImage: Driver device is not initialized.\n");
        *errCode = MXD_STATUS_ERR_DEV;
        return MXD_FAIL;
    }

    /* If only one is provided, returns error */
    if (((sbusImageSize && serdesImageSize) == 0) && ((sbusImageSize + serdesImageSize) > 0))
    {
        MXD_DBG_ERROR("mxdUpdateEEPROMImage: Both Serdes and SBus images must be provided.\n");
        *errCode = MXD_FW_INVALID_IMAGE_SIZE;
        return MXD_FAIL;
    }

    /* either Z80 or SBus/Serdes pair must be provided  */
    if (!((sbusImageSize && serdesImageSize) || z80ImageSize))
    {
        MXD_DBG_ERROR("mxdUpdateEEPROMImage: Invalid image - either Z80 or SBus/Serdes pair must be provided\n");
        *errCode = MXD_FW_INVALID_IMAGE_SIZE;
        return MXD_FAIL;
    }

    if (pDev->chipRevision == MXD_REV_A1)
    {
        regNIMB = MXD_A1_NIMB_REG;
    }

    /* setting the EEPROM to reload state */
    ATTEMPT(mxdChipAndZ80ResetControl(pDev, (MXD_CHIP_HW_RESET|MXD_Z80_RESET), MXD_FALSE));

    /* disabled copying image to RAM */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, 0xF418, 1)); 

    /* compute Z80 checksum */
    for (i=0; i<z80ImageSize; i++)
    {
        checksum += (z80ImageData[i] & 0xFF);
        checksum += ((z80ImageData[i]>>8) & 0xFF);
    }

    /* compute chip image EEPROM size */
    z80ImageCntr = z80ImageSize;

    /* compute SBus EEPROM size */
    sbusImageCntr = (sbusImageSize/3)*4;
    if (sbusImageSize % 3) 
    {
        sbusImageCntr +=4;
    }

    /* compute Serdes EEPROM size */
    serdesImageCntr = (serdesImageSize/3)*4;
    if (serdesImageSize % 3) 
    {
        serdesImageCntr +=4;
    }

    /* create the header table */
    if (z80ImageSize) 
    {
        eepromImageHeader[0] = 0xE;    /* High 64KB enabled; Prog checksum enabled; set I2C speed to 1MHz */
        eepromImageHeader[3] = 0x10;   /* The Prog Dest Addr is set to 0x1000 at the z80 makefile */               
    } else
    {
        eepromImageHeader[0] = 0x2;    /* Disable Prog checksum, set I2C speed to 1MHz */
        eepromImageHeader[3] = 0;      /* No Z80 image */            
    }
    
    eepromImageHeader[1] = ((z80ImageCntr>>8) & 0xFF);
    eepromImageHeader[2] = (z80ImageCntr & 0xFF);
    eepromImageHeader[4] = 0x0;    
    eepromImageHeader[5] = ((sbusImageCntr>>8) & 0xFF);
    eepromImageHeader[6] = (sbusImageCntr & 0xFF);
    eepromImageHeader[7] = ((serdesImageCntr>>8) & 0xFF);
    eepromImageHeader[8] = (serdesImageCntr & 0xFF);

    headerChecksum = 0;
    for (i=0; i<9; i++)
    {
        headerChecksum += eepromImageHeader[i];
    }

    eepromImageHeader[9] = ((headerChecksum>>8) & 0xFF);
    eepromImageHeader[10]= (headerChecksum & 0xFF);

    /* Z80 image will be loaded to upper EEPROM 64k; not needed for total size in lower 64k */
    totalImageSize = sbusImageCntr + serdesImageCntr + 11; /* eepromImageHeader=11 */ 

    /* write 31.F856.1:0 to 2'b01; set I2C speed to 400k */
    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, regNIMB, 0xF856, 0, 2, 0x1)); 

    /* EEPROM Image byte length */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF860, ((totalImageSize & 0xFF00) >> 8)));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF861, (totalImageSize & 0xFF))); 

    /* EEPROM Dest Addr default 0x0000 */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF863, 0));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF862, 0)); 

    /* RAM Source Addr default 0x1000 */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF864, 0x10));  
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF865, 0));

    /* starting address for loader image */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF840, 0x0000));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF844, 0x0002));

    for (i=0; i<(sizeof(z80LoaderArray)/sizeof(MXD_U16)); i++)
    {
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, z80LoaderArray[i])); 
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));            
    }

    /* starting address for RAM image */
    /* word address; set start address to 2048 word size(2048*2-bytes) 0x1000 */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF840, 2048)); 
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF844, 0x0002)); 

    for (i=0; i<10; i+=2)
    {
        temp = ((eepromImageHeader[i+1]<<8)|eepromImageHeader[i]);
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, temp));         
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));      
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

        packedData = (MXD_U32)(((0x3 & 0x3) << 30) + ((tempData[2] & 0x3FF) << 20) + 
                               ((tempData[1] & 0x3FF) << 10) + (tempData[0] & 0x3FF));

        eepromImageData[0] = (MXD_U8)(packedData & 0xff);
        eepromImageData[1] = (MXD_U8)((packedData>>8) & 0xff);
        eepromImageData[2] = (MXD_U8)((packedData>>16) & 0xff);

        temp = ((eepromImageData[0]<<8)|carryOver);
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, temp));        
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));      
        
        temp = ((eepromImageData[2]<<8)|eepromImageData[1]);
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, temp));   
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002)); 

        eepromImageData[3] = (MXD_U8)((packedData>>24) & 0xff);
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
            
        packedData = (MXD_U32)(((remainder & 0x3) << 30) + ((tempData[2] & 0x3FF) << 20) + 
                               ((tempData[1] & 0x3FF) << 10) + (tempData[0] & 0x3FF));

        /* Adjusting remainder padding not needed */
        /*
        if (remainder == 1) 
        {
            packedData |= 0x80000000;
        }
        else if (remainder == 2)
        {
            packedData |= 0x40000000;
        }
        */

        eepromImageData[0] = (MXD_U8)(packedData & 0xff);
        eepromImageData[1] = (MXD_U8)((packedData>>8) & 0xff);
        eepromImageData[2] = (MXD_U8)((packedData>>16) & 0xff);

        temp = ((eepromImageData[0]<<8)|carryOver);
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, temp));      
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));    

        temp = ((eepromImageData[2]<<8)|eepromImageData[1]);
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, temp));     
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));   

        eepromImageData[3] = (MXD_U8)((packedData>>24) & 0xff);
        carryOver = eepromImageData[3];
    }

    /* Convert sbus FW from 10bits to 8 bits */
    /* Set [31:30] Set [29:20] equal to 3rd data_word, 
       Set [19:10] equal to 2nd data word, Set [9:0] equal to 1st data word */
    for(i=0; i<(serdesImageSize/3); i++)
    {
        tempData[0] = serdesImageData[(i*3)];   
        tempData[1] = serdesImageData[(i*3)+1];
        tempData[2] = serdesImageData[(i*3)+2];

        packedData = (MXD_U32)(((0x3 & 0x3) << 30) + ((tempData[2] & 0x3FF) << 20) + 
                               ((tempData[1] & 0x3FF) << 10) + (tempData[0] & 0x3FF));

        eepromImageData[0] = (MXD_U8)(packedData & 0xff);
        eepromImageData[1] = (MXD_U8)((packedData>>8) & 0xff);
        eepromImageData[2] = (MXD_U8)((packedData>>16) & 0xff);

        temp = ((eepromImageData[0]<<8)|carryOver);
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, temp));      
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));    
    
        temp = ((eepromImageData[2]<<8)|eepromImageData[1]);
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, temp));      
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));    

        eepromImageData[3] = (MXD_U8)((packedData>>24) & 0xff);
        carryOver = eepromImageData[3];
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
            
        packedData = (MXD_U32)(((remainder & 0x3) << 30) + ((tempData[2] & 0x3FF) << 20) + 
                               ((tempData[1] & 0x3FF) << 10) + (tempData[0] & 0x3FF));

        /* Adjusting remainder padding not needed */
        /*
        if (remainder == 1) 
        {
            packedData |= 0x80000000;
        }
        else if (remainder == 2)
        {
            packedData |= 0x40000000;
        } 
        */

        eepromImageData[0] = (MXD_U8)(packedData & 0xff);
        eepromImageData[1] = (MXD_U8)((packedData>>8) & 0xff);
        eepromImageData[2] = (MXD_U8)((packedData>>16) & 0xff);

        temp = ((eepromImageData[0]<<8)|carryOver);
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, temp));      
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));    

        temp = ((eepromImageData[2]<<8)|eepromImageData[1]);
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, temp));       
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));     

        eepromImageData[3] = (MXD_U8)((packedData>>24) & 0xff);
        carryOver = eepromImageData[3];
    
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, carryOver));       
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002));     
    }

    /* handle Z80 image if needed. Z80 image will load to the upper 64k */
    if (z80ImageSize)
    {
        /* 2-bytes Z80 checksum at end of buffer */
        z80ImageSize += 2; 

        MXD_DBG_INFO("mxdUpdateEEPROMImage: Loading Z80 image to EEPROM.\n");
        /* clear reset */
        ATTEMPT(mxdChipAndZ80ResetControl(pDev, MXD_Z80_RESET_RELEASE, MXD_FALSE)); 

        for (i=0; i<100; i++)
        {
            ATTEMPT(mxdWait(pDev, 100));

            /* check EEPROM Write Done flag */
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, regNIMB, 0xF846, 0, 1, &temp)); 

            if (temp == 1)
            {
                MXD_DBG_INFO("mxdUpdateEEPROMImage: SerDes/SBUS images successfully written to EEPROM.\n");

                /* give it a 0.5 sec pause before write to upper 64K EEPROM */
                ATTEMPT(mxdWait(pDev, 500));
                break;
            }
        }

        /* Write to the upper 64K; setting the EEPROM to reload state */
        ATTEMPT(mxdChipAndZ80ResetControl(pDev, (MXD_CHIP_HW_RESET|MXD_Z80_RESET), MXD_FALSE));
        
        /* disabled copying image to RAM */
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, 0xF418, 1)); 

        /* write 31.F856.1:0 to 2'b01; set I2C speed to 400k */
        ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, regNIMB, 0xF856, 0, 2, 0x1)); 

        /* EEPROM Image byte length */
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF860, ((z80ImageSize & 0xFF00) >> 8)));
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF861, (z80ImageSize & 0xFF))); 

        /* EEPROM Dest Addr default */
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF862, 0)); 
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF863, 0));

        /* RAM Source Addr default 0x1000 */
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF864, 0x10));  
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF865, 0));

        /* write data to high 64k of EEPROM */
        ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, regNIMB, 0xF866, 0, 1, 0x1)); 

        /* NIMB RAM access mode select */
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF844, 0x0002));

        /* Address to access NIMB RAM */
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF840, 0x0800));

        /* adds the 2 bytes checksum to the end */
        z80ImageData[z80ImageSize-2] = (MXD_U16)(checksum & 0xFF00)>>8;
        z80ImageData[z80ImageSize-1] = (MXD_U16)(checksum & 0x00FF);

        for (i=0; i<z80ImageSize; i+=2)
        {
            temp = ((z80ImageData[i+1]<<8) | z80ImageData[i]); 
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF841, temp));   
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, regNIMB, 0xF843, 0x0002)); 
        }
    } 

    /* clear reset */
    ATTEMPT(mxdChipAndZ80ResetControl(pDev, MXD_Z80_RESET_RELEASE, MXD_FALSE)); 

    for (i=0; i<100; i++)
    {
        ATTEMPT(mxdWait(pDev, 100));

        /* check EEPROM Write Done flag */
        ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, regNIMB, 0xF846, 0, 1, &temp)); 

        if (temp == 1)
        {
            MXD_DBG_INFO("mxdUpdateEEPROMImage: Images successfully written to EEPROM.\n");

            /* give it a sec pause before loading the EEPROM to the RAM */
            ATTEMPT(mxdWait(pDev, 1000));
            if (mxdLoadEEPROMImageToRAM(pDev, mdioPort) == MXD_OK)
            {
                MXD_DBG_INFO("mxdUpdateEEPROMImage: mxdLoadEEPROMImageToRAM Completed\n");
                return MXD_OK;
            }
        }
    }

    MXD_DBG_INFO("mxdUpdateEEPROMImage: Failed\n");

    *errCode = MXD_FW_UNKNOWN_DOWNLOAD_EEPROM_ERR;
    return MXD_FAIL;
}


