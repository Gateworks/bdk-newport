/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
*******************************************************************************/

/********************************************************************************
* mcdInitialization.c
*
* DESCRIPTION:
*       Functions to access platform layer by MCD 100G control program.
*
* DEPENDENCIES:
*       None.
*
* FILE REVISION NUMBER:
*       $Revision: 1 $
*
*******************************************************************************/
#include "mcdApiTypes.h"
#include "mcdApiRegs.h"
#include "mcdUtils.h"
#include "mcdInitialization.h"
#include "mcdHwCntl.h"
#include "mcdAPI.h"
#include "mcdDiagnostics.h"
#include "mcdFwDownload.h"
#include "mcdAPIInternal.h"
#include "mcdHwSerdesCntl.h"
#include "mcdInternalIpcApis.h"

#ifdef MV_HWS_REDUCED_BUILD_EXT_CM3
extern MCD_SER_DEV  aaplSerdesDbDef[];
extern MCD_SER_DEV_PTR aaplSerdesDb[];
#endif
static MCD_STATUS mcdAutoNegParametersDefaultInit (IN MCD_DEV_PTR pDev);
MCD_BOOT_MODE bootMode = MCD_REGULAR_BOOT_MODE;
MCD_BOOL mcdDriverInitialized = MCD_FALSE;

/*******************************************************************
 MCD_STATUS mcdInitDriver

 init read/write pointers
 read chip id/rev
 load CM3, then serdes
 initialize LED/GPIO
*******************************************************************/
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
MCD_STATUS mcdInitDriver
(
    IN FMCD_READ_MDIO  readMdio,
    IN FMCD_WRITE_MDIO writeMdio,
    IN MCD_U16         firstMDIOPort,
    IN MCD_U8          const *pCm3Image,
    IN MCD_U32         cm3ImageSize,
    IN MCD_U16         const *pBusMasterImage,
    IN MCD_U16         busMasterImageSize,
    IN MCD_U16         const *pBusMasterSwappedImage,
    IN MCD_U16         busMasterSwappedImageSize,
    IN MCD_U16         const *pSerdesImage,
    IN MCD_U16         serdesImageSize,
    IN MCD_PVOID       pHostContext,
    OUT MCD_DEV_PTR    pDev
)
{
    MCD_STATUS rc;
    MCD_U32    port;
    MCD_U8     major, minor, patch;

    MCD_DBG_INFO("mcdInitDriver Called.\n");
    /* Check for parameters validity */

    /* allow to be called with NULL for IO functions, in case host wants to */
    /* implement their own and not use the ones inside the MCD_DEV struct   */
    if(readMdio == NULL || writeMdio == NULL )
    {
        MCD_DBG_ERROR("mcdInitDriver: MDIO read or write pointers are NULL.\n");
        return MCD_STATUS_ERR_DEV;
    }

    /* Check for parameters validity        */
    if(pDev == NULL)
    {
        MCD_DBG_ERROR("mcdInitDriver: MCD_DEV pointer is NULL.\n");
        return MCD_STATUS_ERR_DEV;
    }

    /* The initialization was already done. */
    if(pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdInitDriver: Device Driver already loaded.\n");
        return MCD_STATUS_ERR_INIT;
    }

    pDev->firstMdioPort = firstMDIOPort;

    /* check MDIO port within range and even number since this is Port 0 */
    if((firstMDIOPort >= MCD_MAX_MDIO_NUM) || (firstMDIOPort % 2))
    {
        MCD_DBG_ERROR("mcdInitDriver: Invalid MDIO port number : %u\n", firstMDIOPort);
        return MCD_STATUS_ERR_DEV;
    }

    pDev->fmcdReadMdio   = readMdio;
    pDev->fmcdWriteMdio  = writeMdio;
    pDev->shadowValidBmp = 0;
    pDev->hostContext = pHostContext;

    /* Get MCD software release version  */
    rc = mcdGetAPIVersion(&major,&minor,&patch);
    if (rc != MCD_OK)
    {
        MCD_DBG_ERROR("mcdInitDriver: mcdGetAPIVersion Failed.\n");
        return rc;
    }
    MCD_DBG_INFO("MCD version %d.%d.%d\n",major,minor,patch);

    /* After everything else is done, can fill in the device id */
    rc = mcdCheckIsDeviceSupported(pDev, firstMDIOPort);
    if (rc != MCD_OK)
    {
        MCD_DBG_ERROR("mcdInitDriver: mcdCheckIsDeviceSupported Failed.\n");
        return MCD_STATUS_ERR_DEV_ID;
    }

    rc = mcdHwXmdioAccessInit32bit(pDev);
    if (rc != MCD_OK)
    {
        MCD_DBG_ERROR("mcdInitDriver: AccessInit32bit failed.\n");
        return rc;
    }

    /* This function cannot be called before mcdHwXmdioAccessInit32bit */
    /* Access to relevant regiters yet not be initialized              */
    rc = mcdGetChipRevision(pDev, firstMDIOPort, &(pDev->deviceId));
    if (rc != MCD_OK)
    {
        MCD_DBG_ERROR("mcdInitDriver: mcdGetChipRevision Failed.\n");
        return rc;
    }
    switch (pDev->deviceId)
    {
        case MCD_REV_X5123:
        case MCD_REV_EC808:
            break;
        default:
            MCD_DBG_ERROR("mcdInitDriver: mcdGetChipDeviceId - not supported device Id =%x \n",pDev->deviceId);
            return MCD_STATUS_ERR_DEV_ID;
    }

    rc = mcdHwXmdioWaitStatus32Bit(
        pDev, pDev->firstMdioPort/*mdioPort*/,
        0x800F8010/*reg*/,  /* Server status register of DFX Server */
        0x30/*mask*/,       /* bits 4:5 initialization stage of the device */
        0x30/*pattern*/,    /* initialization stage of the device to become 1 */
        10000/*timeout*/);
    if (rc != MCD_OK)
    {
        MCD_DBG_ERROR("mcdInitDriver: wait for HW Init Device Done failed.\n");
        return rc;
    }

    rc = mcdPowerConsumptionReduce(pDev, MCD_TRUE);
    if (rc != MCD_OK)
    {
        MCD_DBG_ERROR("mcdInitDriver: PowerConsumptionReduce failed.\n");
        return rc;
    }

#if MCD_ENABLE_SERDES_API
    if (mcdInitSerdesDev(
        pDev, pBusMasterImage, busMasterImageSize,
        pBusMasterSwappedImage, busMasterSwappedImageSize,
        pSerdesImage, serdesImageSize) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdInitDriver: mcdInitSerdesDev failed.\n");
        return MCD_STATUS_SERDES_INIT_ERR;
    }
#endif

    pDev->devEnabled = MCD_TRUE;
    for (port = 0; port < MCD_MAX_PORT_NUM; port++)
    {
        pDev->portConfig[port].portMode = MCD_MODE_UNKNOWN;
    }
    /* All UMAC interrupts are enabled after reset by default ,
       the function mcdDisableAllUmacInterrupts  disable them*/
    mcdDisableAllUmacInterrupts (pDev);

    pDev->portCount = 0;
    /* configure access window CM3 to DFX */

    /* CM3 External Base Address %n */
    rc = mcdHwXmdioWrite32bit(
        pDev, 0/*mdioPort*/, 0x30000480/*reg*/, 0x00000008/*data*/);
    if (rc != MCD_OK)
    {
        MCD_DBG_ERROR("mcdInitDriver: write CM3 External Base Address failed.\n");
        return rc;
    }

    /* CM3 External Size (S) %n */
    rc = mcdHwXmdioWrite32bit(
        pDev, 0/*mdioPort*/, 0x30000484/*reg*/, 0x000f0000/*data*/);
    if (rc != MCD_OK)
    {
        MCD_DBG_ERROR("mcdInitDriver: write CM3 External Size failed.\n");
        return rc;
    }

    /* CM3 External Window Control Register %n */
    rc = mcdHwXmdioWrite32bit(
        pDev, 0/*mdioPort*/, 0x3000048C/*reg*/, 0x0000000e/*data*/);
    if (rc != MCD_OK)
    {
        MCD_DBG_ERROR("mcdInitDriver: write CM3 External Window Control failed.\n");
        return rc;
    }
    /*CM3 Uart enable*/
    MCD_DBG_INFO("mcdInitDriver: CM3 uart enabled.\n");
    rc = mcdHwSetPhyRegField32bit(pDev, 0, RUNIT_RFU_MPP_Control_0_1_REGISTER, 0, 8, 0x33);
    if (rc != MCD_OK)
    {
        MCD_DBG_ERROR("mcdInitDriver: CM3 uart enable failed.\n");
        return rc;
    }

    /* CM3 TX Internal Window Configuration */
    rc = mcdHwXmdioWrite32bit(
        pDev, 0/*mdioPort*/, 0x30000334/*reg*/, 0x00102000/*data*/);
    if (rc != MCD_OK)
    {
        MCD_DBG_ERROR("mcdInitDriver: write CM3 TX Internal Window Configuration  failed.\n");
        return rc;
    }

    rc = mcdInternalIpcDbInit(pDev);
    if (rc != MCD_OK)
    {
        MCD_DBG_ERROR("mcdInitDriver: mcdInternalIpcDbInit failed.\n");
        return rc;
    }


    if (pCm3Image != NULL)
    {
        if (bootMode == MCD_REGULAR_BOOT_MODE)
        {
            if (mcdLoadCm3FWImage(pDev, 0, cm3ImageSize, pCm3Image) != MCD_OK)
            {
                MCD_DBG_ERROR("mcdInitDriver: mcdLoadCm3FWImage failed.\n");
                return MCD_STATUS_SERDES_INIT_ERR;
            }
        }
        rc = mcdServiceCpuFwPostInit(pDev);
        if (rc != MCD_OK)
        {
            MCD_DBG_ERROR("mcdInitDriver: mcdServiceCpuFwPostInit failed.\n");
            return rc;
        }
    }

    mcdAutoNegParametersDefaultInit(pDev);
    /*Init registers to support RS FEC 1.6 consortium*/
    if (bootMode == MCD_REGULAR_BOOT_MODE /* RS FEC registers are already initilaized @ HA Mode */)
    {
        rc = mcd25gRsFecInit(pDev);
        if (rc != MCD_OK)
        {
           MCD_DBG_ERROR("mcdInitDriver: RS FEC 1.6 consortium init failed.\n");
           return rc;
        }
    }

    if (bootMode == MCD_HIGH_AVAILABILITY_BOOT_MODE)
    {
        pDev->highAvailabilityMode = MCD_TRUE;
    }

    mcdDriverInitialized = MCD_TRUE;

    MCD_DBG_INFO("mcdInitDriver successful.\n");
    return MCD_OK;
}
#else /*#infdef MV_HWS_REDUCED_BUILD_EXT_CM3*/
MCD_STATUS mcdInitDriverCm3
(
    OUT MCD_DEV_PTR    pDev
)
{
    MCD_U32    port;

    MCD_DBG_INFO("mcdInitDriverCM3 Called.\n");

    /* Check for parameters validity        */
    if(pDev == NULL)
    {
        MCD_DBG_ERROR("mcdInitDriver: MCD_DEV pointer is NULL.\n");
        return MCD_STATUS_ERR_DEV;
    }

    /* The initialization was already done. */
    if(pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdInitDriver: Device Driver already loaded.\n");
        return MCD_STATUS_ERR_INIT;
    }


    pDev->firstMdioPort = 0;

    pDev->fmcdReadMdio   = NULL;
    pDev->fmcdWriteMdio  = NULL;
    pDev->shadowValidBmp = 0;

    /* Initialize AAPL structure in CM3 */
    aaplSerdesDb[0] = &(aaplSerdesDbDef[0]);
    pDev->serdesDev = aaplSerdesDb[0];


    pDev->hostContext = NULL;
    pDev->devEnabled = MCD_TRUE;
    pDev->highAvailabilityMode = MCD_FALSE;
    pDev->haAccessDisable = MCD_FALSE;
    for (port = 0; port < MCD_MAX_PORT_NUM; port++)
    {
        pDev->portConfig[port].portMode = MCD_MODE_UNKNOWN;
    }
    pDev->portCount = 0; /* until port mode selection applied, no idea how many ports */

    mcdAutoNegParametersDefaultInit(pDev);

    MCD_DBG_INFO("mcdInitDriver successful.\n");

    return MCD_OK;
}

#endif

/*******************************************************************************
 MCD_STATUS mmcdSetApParameters
    Set Auto-neg parameters
*******************************************************************************/
static MCD_STATUS mcdAutoNegParametersDefaultInit
(
    IN MCD_DEV_PTR pDev
)
{
    MCD_U16 port;
    for (port = 0; port < MCD_MAX_PORT_NUM; port++)
    {
        pDev->apCfg[port].apLaneNum = 0xFF;
        pDev->apCfg[port].fecReq = 0xFF;
        pDev->apCfg[port].fcPause =  MCD_FALSE;
        pDev->apCfg[port].fcAsmDir = MCD_FALSE;
        pDev->apCfg[port].nonceDis = MCD_FALSE;
    }
    return MCD_OK;
}
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************
 MCD_STATUS mcdInitDriverAllDevices
 init read/write pointers
 read chip id/rev
 load serdes, then CM3,
 initialize LED/GPIO
*******************************************************************/
MCD_STATUS mcdInitDriverAllDevices
(
    IN FMCD_READ_MDIO  readMdio,
    IN FMCD_WRITE_MDIO writeMdio,
    IN MCD_U16         numOfDevs,
    IN MCD_U16         firstMDIOPortArr[],
    IN MCD_U8          const *pCm3Image,
    IN MCD_U32         cm3ImageSize,
    IN MCD_U16         const *pBusMasterImage,
    IN MCD_U16         busMasterImageSize,
    IN MCD_U16         const *pBusMasterSwappedImage,
    IN MCD_U16         busMasterSwappedImageSize,
    IN MCD_U16         const *pSerdesImage,
    IN MCD_U16         serdesImageSize,
    IN MCD_PVOID       pHostContextArr[],
    OUT MCD_DEV_PTR    pDevArr[]
)
{
#ifndef ASIC_SIMULATION
    MCD_DEV      broadcastDev;
    MCD_STATUS   rc;
    MCD_U16      i;

    for (i = 0; (i < numOfDevs); i++)
    {
        rc = mcdInitDriver(
            readMdio, writeMdio, firstMDIOPortArr[i],
            NULL, 0,/*pCm3Image, cm3ImageSize,                            */
            NULL, 0,/*pBusMasterImage, busMasterImageSize,                */
            NULL, 0,/*pBusMasterSwappedImage, busMasterSwappedImageSize,  */
            NULL, 0,/*pSerdesImage, serdesImageSize,                      */
            pHostContextArr[i],
            pDevArr[i]);
        if (rc != MCD_OK)
        {
            MCD_DBG_ERROR("mcdInitDriverAllDevices: failed in mcdInitDriver.\n");
            return rc;
        }
    }


    if (MCD_OK != mcdInitBroadcastDev(
        pDevArr[0], &broadcastDev))
    {
        MCD_DBG_ERROR("mcdInitBroadcastDev: failed\n");
        return MCD_FAIL;
    }

    rc = mcdLoadSBusSerdesFromCpuMemoryAllDevices(
        &broadcastDev, numOfDevs, pDevArr,  /* all devices on XSMI Bus */
        serdesImageSize, pSerdesImage);
    if (rc != MCD_OK)
    {
        mcdUnloadDriver(&broadcastDev);
        MCD_DBG_ERROR(
            "mcdInitDriverAllDevices: failed in mcdLoadSBusSerdesFromCpuMemoryAllDevices.\n");
        return rc;
    }

    rc = mcdLoadSBusMasterFromCpuMemoryAllDevices(&broadcastDev, numOfDevs, pDevArr,  /* all devices on XSMI Bus */
                                                  busMasterImageSize, pBusMasterImage,
                                                  busMasterSwappedImageSize, pBusMasterSwappedImage);
    if (rc != MCD_OK)
    {
        mcdUnloadDriver(&broadcastDev);
        MCD_DBG_ERROR(
            "mcdInitDriverAllDevices: failed in mcdLoadSBusMasterFromCpuMemoryAllDevices.\n");
        return rc;
    }

    rc = mcdLoadCm3FWImageAllDevices(&broadcastDev, numOfDevs, pDevArr,  /* all devices on XSMI Bus */
                                     cm3ImageSize, pCm3Image);
    if (rc != MCD_OK)
    {
        mcdUnloadDriver(&broadcastDev);
        MCD_DBG_ERROR(
            "mcdInitDriverAllDevices: failed in mcdLoadCm3FWImageAllDevices.\n");
        return rc;
    }
    for (i = 0; (i < numOfDevs); i++)
    {
        rc = mcdServiceCpuFwPostInit(pDevArr[i]);
        if (rc != MCD_OK)
        {
            mcdUnloadDriver(&broadcastDev);
            MCD_DBG_ERROR("mcdInitDriver: mcdServiceCpuFwPostInit failed.\n");
            return rc;
        }
    }

    mcdUnloadDriver(&broadcastDev);

#endif /*ASIC_SIMULATION*/
    return MCD_OK;
}
#endif

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************
 MCD_STATUS mcdUnloadDriver
*******************************************************************/
MCD_STATUS mcdUnloadDriver
(
    IN MCD_DEV_PTR pDev
)
{
    if (!pDev)
    {
        MCD_DBG_ERROR("mcdUnloadDriver: device in NULL\n");
        return MCD_FAIL;
    }

#if MCD_ENABLE_SERDES_API
    if (mcdFreeSerdesDev(pDev) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdUnloadDriver: mcdFreeSerdesDev failed.\n");
        return MCD_FAIL;
    }
#endif

    mcdMemSet(pDev, 0, (sizeof(MCD_DEV)));

    MCD_DBG_INFO("mcdUnloadDriver: Clean-up completed.\n");

    return MCD_OK;
 }
/*******************************************************************
 MCD_STATUS mcdLedControl
    Sets LED parameters
*******************************************************************/
MCD_STATUS mcdLedControl
(
    IN MCD_DEV_PTR                  pDev,
    IN MCD_U16                      ledNum,
    IN MCD_U16                      portNum,
    IN MCD_U16                      host_or_line,
    IN MCD_LED_PULSE_STRETCH_TYPE   pulseStretch,
    IN MCD_LED_BEHAVIOR_TYPE        ledBehavior,
    IN MCD_LED_FUNC_TYPE            ledFunction,
    IN MCD_LED_BLINK_RATE_TYPE      blinkRate,
    IN MCD_LED_POLARITY_TYPE        ledPolarity,
    IN MCD_LED_MIX_PERCENTAGE_TYPE  ledMixPercentage

 )
{
    MCD_U32         slice,chan;
    MCD_U32         fieldOffset;
    MCD_U32         data2Write;

    if(ledNum > 1)
    {
        MCD_DBG_ERROR("mcdLedControl: Invalid LED number : %d\n", ledNum);
        return MCD_STATUS_BAD_PARAM;
    }
        /* check port is valid */
    if (mcdIsPortValid(pDev, portNum) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdLedControl: Invalid port number: %d\n", portNum);
        return MCD_STATUS_BAD_PARAM;
    }

    slice = portNum / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan = CHAN_IN_SLICE_NUM(portNum);
    fieldOffset = ledNum*4;
    /*define in  MPP_Control_0_1 resgister relevant bits to function as the LEDx output*/
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, RUNIT_RFU_MPP_Control_0_1_REGISTER, fieldOffset, 4, 2));

    /* set blink rate*/
    data2Write = (blinkRate & 7) << ((ledNum + 1)*4) ;
    /*set pulse stretch*/
    data2Write |= (pulseStretch & 7) << 12;
    /* set LED interface port selection */
    if (host_or_line == MCD_HOST_SIDE)
    {
        data2Write |= 1 << (16 + ledNum * 4);
    }
    data2Write |= slice << (17 + ledNum * 4);
    data2Write |= chan << (18 + ledNum * 4);

    ATTEMPT(mcdHwSetPhyRegMask32bit(pDev, DONT_CARE, RUNIT_SOC_MISC_LED_PULSE_STRETCH_AND_BLINK_REGISTER, 0x00FF7770, data2Write));
    /*define LED0 Display Register data*/
    /*set polarity*/
    data2Write = ledPolarity & 3 ;
    /*set blink rate */
    data2Write |= (ledNum & 1) << 2;
    /*set display function*/
    data2Write |= (ledFunction & 7) << (4 + ledBehavior * 4);

    ATTEMPT(mcdHwSetPhyRegMask32bit(pDev, DONT_CARE, (RUNIT_SOC_MISC_LED0_DISPLAY_REGISTER + ledNum * 4),0x00000FF7, data2Write));

    /* set LED Mix Register - bicolor LEDs*/
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, RUNIT_SOC_MISC_LED_MIX_REGISTER , fieldOffset, 4, ledMixPercentage));
    return MCD_OK;
}
#endif /*#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3*/
/*******************************************************************
 MCD_STATUS mcdPortReset
 Perform a port hardware Soft or Hard reset
*******************************************************************/
MCD_STATUS mcdPortReset
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_RESET_TYPE resetType,
    IN MCD_U16 timeoutMs
)
{
    MCD_STATUS rc;

    /* parameter host_or_line not relevant to X5123 and EC808  */
    /* required to specify the alone supported value           */
    if (host_or_line  != MCD_BOTH_SIDE)
    {
        MCD_DBG_ERROR("mcdPortReset: wrong host_or_line, must be MCD_BOTH_SIDE.\n");
        return MCD_FAIL;
    }

    if (resetType == MCD_HARD_RESET)
    {
        MCD_DBG_ERROR("mcdPortReset: hard reset not supported.\n");
        return MCD_FAIL;

    }

    if (resetType == MCD_SOFT_RESET)
    {
        rc = mcdChannelSwReset(pDev, mdioPort/*chan*/, 1 /*reset*/);
        if (rc != MCD_OK) return rc;
        rc = mcdChannelSwReset(pDev, mdioPort/*chan*/, 0 /*clear*/);
        if (rc != MCD_OK) return rc;

        return MCD_OK;
    }
    MCD_DBG_ERROR("mcdPortReset: wrong resetType.\n");
    return MCD_FAIL;
}
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************
 MCD_STATUS mcdChipAndZ80ResetControl

 Perform a chip hardware Soft or Hard reset and/or a Z80 reset;
 save any registers we might need if we need power-on default of
 registers to restore later
*******************************************************************/
MCD_STATUS mcdChipAndZ80ResetControl
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 resetType,
    IN MCD_BOOL bRestore
)
{
    return MCD_NOT_IMPLEMENTED;
}
#endif

/**
* @internal mcdPreInitSetBootMode function
* @endinternal
*
* @brief   set boot mode before driver initalization
*
* @param[in] phyId
* @param[in] mode                 -  Boot Mode
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdPreInitSetBootMode(MCD_BOOT_MODE mode)
{
    if (!mcdDriverInitialized)
    {
        bootMode = mode;
        return MCD_OK;
    }
    else
    {
        MCD_DBG_ERROR("mcd Driver already initialized\n");
        return MCD_FAIL;
    }
}

/**
* @internal mcdPostInitSetBootMode function
* @endinternal
*
* @brief   set boot mode after Driver was initalized
*
* @param[in] phyId
* @param[in] mode                 -  Boot Mode
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdPostInitSetBootMode
(
    IN MCD_DEV_PTR pDev,
    IN MCD_BOOT_MODE mode
)
{
    if (pDev == NULL)
    {
        MCD_DBG_ERROR("Device Pointer is NULL\n");
        return MCD_FAIL;
    }
    bootMode = mode;
    if (bootMode == MCD_REGULAR_BOOT_MODE)
    {
        pDev->highAvailabilityMode = MCD_FALSE;
    }
    else
    {
        pDev->highAvailabilityMode = MCD_TRUE;
    }
    return MCD_OK;
}

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/**
* @internal mcdGetBootModeState function
* @endinternal
*
* @brief   get the current boot mode
*
* @param[in] phyId
* @param[in] mode - pointer of boot mode
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdGetBootModeState(MCD_DEV_PTR pDev, MCD_BOOT_MODE *mode)
{
    if (pDev == NULL)
    {
        MCD_DBG_ERROR("Device Pointer is NULL\n");
        return MCD_FAIL;
    }

    *mode = (MCD_BOOT_MODE)pDev->highAvailabilityMode;

    return MCD_OK;
}
#endif





