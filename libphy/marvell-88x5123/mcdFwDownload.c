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
into the internal RAM of the Marvell X5123/EC808 PHY.
********************************************************************/
#include "mcdApiTypes.h"
#include "mcdApiRegs.h"
#include "mcdUtils.h"
#include "mcdHwCntl.h"
#include "mcdAPI.h"
#include "mcdFwDownload.h"
#include "mcdAPIInternal.h"
#include "mcdInitialization.h"
#include "mcdHwSerdesCntl.h"

#ifndef ASIC_SIMULATION
#include "mcdInternalSerdesFwLoad.h"
#endif /*ASIC_SIMULATION*/

#define MCD_FW_CRC_CHECKSUM_ERROR 0xA0
#define MCD_FW_FAIL_WRITE_REG     0xA1

/******************************************************************************
 MCD_STATUS mcdLoadSBusSerdesFW
*******************************************************************************/
MCD_STATUS mcdLoadSBusSerdesFW
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 imageSize,
    IN MCD_U16 const image[],
    OUT MCD_U16 *errCode
)
{
    MCD_SER_DEV_PTR pSerdesDev;

    if (pDev == 0)
    {
        MCD_DBG_ERROR("mcdLoadSBusSerdesFW: device not initialized\n");
        return MCD_FAIL;
    }

    *errCode  = 0;
    pSerdesDev = pDev->serdesDev;

    if ((imageSize == 0) || (image == NULL))
    {
        /* nothing to do */
        return MCD_OK;
    }

    /* broadcast on sbus */
    ATTEMPT(mcdLoadSBusSerdesFromCpuMemory(
        pDev, AVAGO_SERDES_BROADCAST_ADDRESS, imageSize, image));
    if (pSerdesDev->return_code < 0)
    {
        *errCode  = pSerdesDev->return_code;
        MCD_DBG_ERROR("Avago FW Load Failed (return code 0x%x)\n", pSerdesDev->return_code);
        return MCD_STATUS_ERR_INIT;
    }

    return MCD_OK;
}

/******************************************************************************
 MCD_STATUS mcdLoadSBusMasterFW
*******************************************************************************/
MCD_STATUS mcdLoadSBusMasterFW
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 imageSize, /* 0 if skipped */
    IN MCD_U16 const image[],
    IN MCD_U16 swapImageSize, /* 0 if skipped */
    IN MCD_U16 const swapImage[],
    OUT MCD_U16 *errCode
)
{
    MCD_SER_DEV_PTR pSerdesDev;

    /* The image included at the compilation time in related H-file */
    /* Part of mcdInitSerdesDev implementation copied to here       */
    /* not used parameters                                          */
    mdioPort  = mdioPort;

    if (pDev == 0)
    {
        MCD_DBG_ERROR("mcdLoadSBusSerdesFW: device not initialized\n");
        return MCD_FAIL;
    }

    *errCode  = 0;
    pSerdesDev = pDev->serdesDev;

    /* Download SBus_Master Firmware */
    /* ============================= */
    ATTEMPT(mcdLoadSBusMasterFromCpuMemory(
        pDev, imageSize, image, swapImageSize, swapImage));
    if (pSerdesDev->return_code < 0)
    {
        *errCode  = pSerdesDev->return_code;
        MCD_DBG_ERROR("Avago FW Load Failed (return code 0x%x)\n", pSerdesDev->return_code);
        return MCD_STATUS_ERR_INIT;
    }

    return MCD_OK;
}


/******************************************************************************
 MCD_STATUS mcdLoadZ80FWImage
*******************************************************************************/
MCD_STATUS mcdLoadZ80FWImage
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 imageSize,
    IN MCD_U16 image[],
    IN MCD_BOOL reset,
    OUT MCD_U16 *errCode
)
{
    return MCD_NOT_IMPLEMENTED;
}

/******************************************************************************
 MCD_STATUS mcdLoadCm3FWImage
*******************************************************************************/
MCD_STATUS mcdLoadCm3FWImage
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U32 imageSize,
    IN const MCD_U8 image[]
)
{
    MCD_STATUS rc;

    if ((imageSize == 0) || (image == NULL))
    {
        return MCD_OK;
    }

    rc = mcdLoadCm3FWImageStartOrEnd(pDev, mdioPort, MCD_TRUE);
    if (rc != MCD_OK)
    {
        MCD_DBG_ERROR("mcdLoadCm3FWImage: mcdLoadCm3FWImageStartOrEnd start failed\n");
        return rc;
    }

    rc = mcdLoadCm3FWImageLoad(pDev, mdioPort, imageSize, image);
    if (rc != MCD_OK)
    {
        MCD_DBG_ERROR("mcdLoadCm3FWImage: mcdLoadCm3FWImageLoad failed\n");
        return rc;
    }

    rc = mcdLoadCm3FWImageStartOrEnd(pDev, mdioPort, MCD_FALSE);
    if (rc != MCD_OK)
    {
        MCD_DBG_ERROR("mcdLoadCm3FWImage: mcdLoadCm3FWImageStartOrEnd ens\n");
        return rc;
    }

    return MCD_OK;
}

/******************************************************************************
 MCD_STATUS mcdIndirectSBusFwImageWrite
*******************************************************************************/
MCD_STATUS mcdIndirectSBusFwImageWrite
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 sBusReceiverAddr,
    IN MCD_U16 regAddr,
    IN MCD_U16 *image,
    IN MCD_U16 imageSize
)
{
    return MCD_NOT_IMPLEMENTED;
}

/******************************************************************************
 MCD_STATUS mcdLoadROMImageToRAM
*******************************************************************************/
 MCD_STATUS mcdLoadROMImageToRAM
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort
)
{
    return MCD_NOT_IMPLEMENTED;
}

/******************************************************************************
 MCD_STATUS mcdLoadEEPROMImageToRAM
*******************************************************************************/
MCD_STATUS mcdLoadEEPROMImageToRAM
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort
)
{
    return MCD_NOT_IMPLEMENTED;
}

/******************************************************************************
 MCD_STATUS mcdUpdateEEPROMImage
*******************************************************************************/
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
)
{
    *errCode = MCD_FW_UNKNOWN_DOWNLOAD_EEPROM_ERR;
    return MCD_NOT_IMPLEMENTED;
}

#ifdef MCD_INCLUDE_STUBS
/******************************************************************************
 MCD_STATUS mcdUpdateFlashImage
*******************************************************************************/
MCD_STATUS mcdUpdateFlashImage(
    IN MCD_DEV_PTR devPtr,
    IN MCD_U16 mdioPort,
    IN MCD_U8 imageData[],
    IN MCD_U32 imageSize,
    IN MCD_U8 ramCodeData[],
    IN MCD_U32 ramCodeSize,
    OUT MCD_U16 *errCode
)
{
    /* Not implemented yet */
    *errCode = MCD_UNKNOWN_DOWNLOAD_TO_FLASH_FAIL;
    return MCD_FAIL;
}
#endif

/* Broadcast dowload */

/* this function used as callback from load broadcast functions              */
/* it invalidates shadows of regular device handlers after broadcast writing */
void mcdLoadBroadcastDropDevShadow(MCD_SER_DEV_PTR pSerdesDev)
{
    MCD_DEV_PTR pDev = (MCD_DEV_PTR)pSerdesDev->client_data;
    pDev->shadowValidBmp = 0;
}

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
)
{
#ifndef ASIC_SIMULATION
    Aapl_t_ptr   aapl_ptr_arr[32];
    unsigned int i, rc, totalRc;
    MCD_SER_DEV_PTR pSerdesDev;
    unsigned int sbus_addr = 0xFF /*AVAGO_SERDES_BROADCAST_ADDRESS*/;

    if ((imageSize == 0) || (image == NULL))
    {
        return MCD_OK;
    }

    if ((num_of_devs == 0) || (num_of_devs > 32))
    {
        MCD_DBG_ERROR(
            "mcdLoadSBusSerdesFromCpuMemoryBroadcast: num_of_devs %d should be <= 32\n",
            num_of_devs);
        return MCD_FAIL;
    }

    /* build aapl handlers array */
    for (i = 0; (i < num_of_devs); i++)
    {
        aapl_ptr_arr[i] = pDevArr[i]->serdesDev;
    }

    MCD_DBG_INFO(
        "Loading Dev-broadcast to SBus address %x data[0]=%x size(dec) %d\n",
        sbus_addr, image[0], imageSize);
    rc = mcd_avago_spico_upload_broacast(
        mcdLoadBroadcastDropDevShadow,
        num_of_devs, aapl_ptr_arr, broadcastDevPtr->serdesDev,
        sbus_addr, MCD_FALSE /*ram_bist*/, imageSize, (const short *)image);
    broadcastDevPtr->shadowValidBmp = 0;
    totalRc = 0;
    if (rc != 0)
    {
        totalRc = rc;
        MCD_DBG_ERROR("mcd_avago_spico_upload_broacast: failed\n");
    }
    pSerdesDev = (MCD_SER_DEV_PTR)(broadcastDevPtr->serdesDev);
    if ((totalRc == 0) && (pSerdesDev->return_code != 0))
    {
        totalRc = pSerdesDev->return_code;
        MCD_DBG_ERROR("mcd_avago_spico_upload_broacast: zon-zero rc in broacast handler\n");
    }
    if (totalRc == 0)
    {
        for (i = 0; (i < num_of_devs); i++)
        {
            pSerdesDev = (MCD_SER_DEV_PTR)(pDevArr[i]->serdesDev);
            if (pSerdesDev->return_code != 0)
            {
                totalRc = pSerdesDev->return_code;
                MCD_DBG_ERROR("mcd_avago_spico_upload_broacast: zon-zero rc in regular handler\n");
                break;
            }
        }
    }
    return ((totalRc == 0) ? MCD_OK : MCD_FAIL);
#else
    return MCD_OK;
#endif /* ASIC_SIMULATION*/
}

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
)
{
#ifndef ASIC_SIMULATION
    Aapl_t_ptr   aapl_ptr_arr[32];
    unsigned int i, rc, totalRc;
    unsigned int sbus_addr = AVAGO_SBUS_MASTER_ADDRESS;
    MCD_SER_DEV_PTR pSerdesDev;

    if ((num_of_devs == 0) || (num_of_devs > 32))
    {
        MCD_DBG_ERROR(
            "mcdLoadSBusMasterFromCpuMemoryBroadcast: num_of_devs %d should be <= 32\n",
            num_of_devs);
        return MCD_FAIL;
    }

    /* build aapl handlers array */
    for (i = 0; (i < num_of_devs); i++)
    {
        aapl_ptr_arr[i] = pDevArr[i]->serdesDev;
    }

    totalRc = 0;
    if ((imageSize != 0) && (image != NULL))
    {
        MCD_DBG_INFO(
            "Loading Dev-broadcast to SBus address %x data[0]=%x size(dec) %d\n",
            sbus_addr, image[0], imageSize);
        rc = mcd_avago_spico_upload_broacast(
            mcdLoadBroadcastDropDevShadow,
            num_of_devs, aapl_ptr_arr, broadcastDevPtr->serdesDev,
            sbus_addr, MCD_FALSE /*ram_bist*/, imageSize, (const short *)image);
        broadcastDevPtr->shadowValidBmp = 0;
        if (rc != 0)
        {
            totalRc = rc;
            MCD_DBG_ERROR("mcd_avago_spico_upload_broacast: failed\n");
        }
        pSerdesDev = (MCD_SER_DEV_PTR)(broadcastDevPtr->serdesDev);
        if ((totalRc == 0) && (pSerdesDev->return_code != 0))
        {
            totalRc = pSerdesDev->return_code;
            MCD_DBG_ERROR("mcd_avago_spico_upload_broacast: zon-zero rc in broacast handler\n");
        }
        if (totalRc == 0)
        {
            for (i = 0; (i < num_of_devs); i++)
            {
                pSerdesDev = (MCD_SER_DEV_PTR)(pDevArr[i]->serdesDev);
                if (pSerdesDev->return_code != 0)
                {
                    totalRc = pSerdesDev->return_code;
                    MCD_DBG_ERROR("mcd_avago_spico_upload_broacast: zon-zero rc in regular handler\n");
                    break;
                }
            }
        }
    }
    if ((totalRc == 0) && (swapImageSize != 0) && (swapImage != NULL))
    {
        MCD_DBG_INFO(
            "Loading Dev-broadcast SWAP to SBus address %x  data[0]=%x\n",
            sbus_addr, swapImage[0]);
        rc = mcd_avago_spico_upload_swap_image_broadcast(
            mcdLoadBroadcastDropDevShadow,
            num_of_devs, aapl_ptr_arr, broadcastDevPtr->serdesDev,
            sbus_addr, swapImageSize, (const short*)swapImage);
        broadcastDevPtr->shadowValidBmp = 0;
        if (rc != 0)
        {
            totalRc = rc;
            MCD_DBG_ERROR("mcd_avago_spico_upload_swap_image_broadcast: failed\n");
        }
        pSerdesDev = (MCD_SER_DEV_PTR)(broadcastDevPtr->serdesDev);
        if ((totalRc == 0) && (pSerdesDev->return_code != 0))
        {
            totalRc = pSerdesDev->return_code;
            MCD_DBG_ERROR("mcd_avago_spico_upload_broacast: zon-zero rc in broacast handler\n");
        }
        if (totalRc == 0)
        {
            for (i = 0; (i < num_of_devs); i++)
            {
                pSerdesDev = (MCD_SER_DEV_PTR)(pDevArr[i]->serdesDev);
                if (pSerdesDev->return_code != 0)
                {
                    totalRc = pSerdesDev->return_code;
                    MCD_DBG_ERROR("mcd_avago_spico_upload_broacast: zon-zero rc in regular handler\n");
                    break;
                }
            }
        }
    }
    return ((totalRc == 0) ? MCD_OK : MCD_FAIL);
#else
    return MCD_OK;
#endif /* ASIC_SIMULATION*/
}

/******************************************************************************
 MCD_STATUS mcdLoadCm3FWImageAllDevices
*******************************************************************************/
MCD_STATUS mcdLoadCm3FWImageAllDevices
(
    IN MCD_DEV_PTR   broadcastDevPtr,
    IN MCD_U16       num_of_devs,
    MCD_DEV_PTR      pDevArr[],  /* all devices on XSMI Bus */
    IN MCD_U32       imageSize,   /* size in bytes         */
    IN const MCD_U8 image[]
)
{
#ifndef ASIC_SIMULATION
    MCD_U16      i;
    MCD_STATUS   rc;

    if (num_of_devs == 0)
    {
        MCD_DBG_ERROR(
            "mcdLoadCm3FWImageAllDevices: num_of_devs is 0\n");
        return MCD_FAIL;
    }

    if ((imageSize == 0) || (image == NULL))
    {
        return MCD_OK;
    }

    for (i = 0; (i < num_of_devs); i++)
    {
        rc = mcdLoadCm3FWImageStartOrEnd(pDevArr[i], 0/*mdioPort*/, MCD_TRUE);
        pDevArr[i]->shadowValidBmp = 0;
        if (rc != MCD_OK)
        {
            MCD_DBG_ERROR("mcdLoadCm3FWImageAllDevices: mcdLoadCm3FWImageStartOrEnd start failed\n");
            return rc;
        }
    }

    rc = mcdLoadCm3FWImageLoad(broadcastDevPtr, 0/*mdioPort*/, imageSize, image);
    broadcastDevPtr->shadowValidBmp = 0;
    if (rc != MCD_OK)
    {
        MCD_DBG_ERROR("mcdLoadCm3FWImageAllDevices: mcdLoadCm3FWImageLoad failed\n");
        return rc;
    }

    for (i = 0; (i < num_of_devs); i++)
    {
        rc = mcdLoadCm3FWImageStartOrEnd(pDevArr[i], 0/*mdioPort*/, MCD_FALSE);
        pDevArr[i]->shadowValidBmp = 0;
        if (rc != MCD_OK)
        {
            MCD_DBG_ERROR("mcdLoadCm3FWImageAllDevices: mcdLoadCm3FWImageStartOrEnd end failed\n");
            return rc;
        }
    }

#endif /* ASIC_SIMULATION*/
    return MCD_OK;
}




