/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions and global data for
higher-level functions using MDIO access to control and read 
status of the energy efficient ethernet (EEE) functions of the 
Marvell 88X32X0, 88X33X0, 88E20X0 and 88E21X0 ethernet PHYs.
********************************************************************/
#include "mtdApiRegs.h"
#include "mtdApiTypes.h"
#include "mtdHwCntl.h"
#include "mtdHwMsecPtpCntl.h"
#include "mtdAPI.h"
#include "mtdEEE.h"


MTD_STATUS mtdGetLPIStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *latchedValue,
    OUT MTD_U16 *currentValue
)
{
    /* reads it once to get the latched value */
    ATTEMPT(mtdHwXmdioRead(devPtr,port,3,1,latchedValue));    
    /* reads it again to get the current value */
    ATTEMPT(mtdHwXmdioRead(devPtr,port,3,1,currentValue));    

    return MTD_OK;
}

MTD_STATUS mtdGetTxLPIReceived
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 latchedValue,
    OUT MTD_BOOL *txlpiReceived
)
{
    MTD_U16 result;
    /*Bit 11 in reg 3.1 gives Tx LPI received status.
    1 - received
    0 - not received*/
    ATTEMPT(mtdHwGetRegFieldFromWord(latchedValue,11,1,&result));
    
    result ? (*txlpiReceived = MTD_TRUE) : (*txlpiReceived = MTD_FALSE);

    return MTD_OK;
}

MTD_STATUS mtdGetRxLPIReceived
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 latchedValue,
    OUT MTD_BOOL *rxlpiReceived
)
{
    MTD_U16 result;
    /*Bit 10 in reg 3.1 gives Rx LPI received status.
    1 - received
    0 - not received*/
    ATTEMPT(mtdHwGetRegFieldFromWord(latchedValue,10,1,&result));
    
    result ? (*rxlpiReceived = MTD_TRUE) : (*rxlpiReceived = MTD_FALSE);
    
    return MTD_OK;
}

MTD_STATUS mtdGetTxLPIIndication
(
 IN MTD_DEV_PTR devPtr,
 IN MTD_U16 currentValue,
 OUT MTD_BOOL *txlpiIndication
)
{
    MTD_U16 result;
    /*Bit 9 in reg 3.1 gives Tx LPI currently receiving status.
    1 - receiving
    0 - not receiving*/
    ATTEMPT(mtdHwGetRegFieldFromWord(currentValue,9,1,&result));
    
    result ? (*txlpiIndication = MTD_TRUE) : (*txlpiIndication = MTD_FALSE);
    
    return MTD_OK;
}

MTD_STATUS mtdGetRxLPIIndication
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 currentValue,
    OUT MTD_BOOL *rxlpiIndication
)
{
    MTD_U16 result;
    /*Bit 8 in reg 3.1 gives Rx LPI currently receiving status.
    1 - receiving
    0 - not receiving*/
    ATTEMPT(mtdHwGetRegFieldFromWord(currentValue,8,1,&result));
    
    result ? (*rxlpiIndication = MTD_TRUE) : (*rxlpiIndication = MTD_FALSE);
    
    return MTD_OK;
}

MTD_STATUS mtdWakeErrorCount
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *wakeErrCount
)
{
    return (mtdHwXmdioRead(devPtr,port,3,22,wakeErrCount));
}

MTD_STATUS mtdGetEEESupported
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *EEE_support_bits
)
{
    MTD_U16 temp;
    
    ATTEMPT(mtdHwXmdioRead(devPtr,port,3,20,EEE_support_bits));
    ATTEMPT(mtdHwXmdioRead(devPtr,port,3,21,&temp));

    *EEE_support_bits |= ((temp & 0x3)<<4); /* get bits 1,0 and OR in with bits from 3.20 */

    return MTD_OK;
}


MTD_STATUS mtdAdvert_EEE
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 EEE_advertise_bits, 
    IN MTD_BOOL anRestart
)
{
    /* check to make sure only bits supported are set */
    if ((MTD_IS_X32X0_BASE(devPtr->deviceId)) && (EEE_advertise_bits & (~(MTD_EEE_ALL))))
    {
        return MTD_FAIL; /* any extra bits set to 1, return error including 2.5/5G bits on X32X0 devices */
    }

    if ((MTD_IS_E21X0_BASE(devPtr->deviceId) || MTD_IS_E20X0_DEVICE(devPtr->deviceId)) && (EEE_advertise_bits & (~(MTD_EEE_ALL_20X0_21X0))))
    {
        return MTD_FAIL; /* any extra bits set to 1, return error including 10G on E20X0/E21X0 devices */
    }

    if ((MTD_IS_X33X0_BASE(devPtr->deviceId)) && (EEE_advertise_bits & (~(MTD_EEE_ALL_33X0))))
    {
        return MTD_FAIL; /* any extra bits set to 1, return error */
    }
    
    ATTEMPT(mtdHwXmdioWrite(devPtr,port,7,0x003C,(EEE_advertise_bits & (MTD_EEE_ALL))));

    if (MTD_IS_E21X0_BASE(devPtr->deviceId) || MTD_IS_E20X0_DEVICE(devPtr->deviceId))
    {
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,7,0x003E,((EEE_advertise_bits & (MTD_EEE_ALL_20X0_21X0)))>>4));                
    }
    else if (MTD_IS_X33X0_BASE(devPtr->deviceId))
    {
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,7,0x003E,((EEE_advertise_bits & (MTD_EEE_ALL_33X0)))>>4));        
    } 

    if (anRestart == MTD_TRUE)
    {
        ATTEMPT(mtdAutonegRestart(devPtr,port));
    }

    return MTD_OK;
}

MTD_STATUS mtdGetAdvert_EEE
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *EEE_advertise_bits     
)
{
    MTD_U16 temp;    
    
    ATTEMPT(mtdHwXmdioRead(devPtr,port,7,0x3C,EEE_advertise_bits));
    ATTEMPT(mtdHwXmdioRead(devPtr,port,7,0x3E,&temp));

    *EEE_advertise_bits |= ((temp & 3)<<4);

    return MTD_OK;
}

MTD_STATUS mtdGetLP_Advert_EEE
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *LP_EEE_advertise_bits     
)
{
    MTD_U16 temp;
    
    ATTEMPT(mtdHwXmdioRead(devPtr,port,7,0x3D,LP_EEE_advertise_bits));
    ATTEMPT(mtdHwXmdioRead(devPtr,port,7,0x3F,&temp));

    *LP_EEE_advertise_bits |= ((temp & 3)<<4);

    return MTD_OK;    
}

MTD_STATUS mtdGetEEEResolution
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *EEE_resolved_bits     
)
{
    MTD_U16 localAdvert, LPAdvert;

    *EEE_resolved_bits = 0;

    ATTEMPT(mtdGetAdvert_EEE(devPtr,port,&localAdvert));
    ATTEMPT(mtdGetLP_Advert_EEE(devPtr,port,&LPAdvert));

    *EEE_resolved_bits = (localAdvert & LPAdvert);

    return MTD_OK;
}

MTD_STATUS mtdEeeBufferConfig
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U8 EEE_Mode_Control, 
    IN MTD_U8 XGMII_Enter_Timeout, 
    IN MTD_U8 GMII_Enter_Timeout, 
    IN MTD_U8 MII_Enter_Timeout, 
    IN MTD_U8 XGMII_Exit_Timeout, 
    IN MTD_U8 GMII_Exit_Timeout, 
    IN MTD_U8 MII_Exit_Timeout, 
    IN MTD_U8 IPG_Length 
)
{
#if MTD_EEE_LL_EXIT_TIMER
    const MTD_BOOL USE_0P5USEC_RESOLUTION = MTD_TRUE;  /* will use lower exit timer values on 10G/2.5G on 33X0 and later PHYs */
#else
    const MTD_BOOL USE_0P5USEC_RESOLUTION = MTD_FALSE; /* old behavior, 1 usec resolution */
#endif

    return mtdEeeBufferConfigLL(devPtr,port,EEE_Mode_Control,XGMII_Enter_Timeout,GMII_Enter_Timeout,
                                            MII_Enter_Timeout,XGMII_Exit_Timeout,GMII_Exit_Timeout,
                                            MII_Exit_Timeout,IPG_Length,USE_0P5USEC_RESOLUTION);
}

MTD_STATUS mtdEeeBufferConfigLL
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U8 EEE_Mode_Control, 
    IN MTD_U8 XGMII_Enter_Timeout, 
    IN MTD_U8 GMII_Enter_Timeout, 
    IN MTD_U8 MII_Enter_Timeout, 
    IN MTD_U8 XGMII_Exit_Timeout, 
    IN MTD_U8 GMII_Exit_Timeout, 
    IN MTD_U8 MII_Exit_Timeout, 
    IN MTD_U8 IPG_Length,
    IN MTD_BOOL Use0p5usecResolution     
)
{
    MTD_U16 temp, multiplier=1;
    MTD_BOOL lowResSupported = MTD_FALSE;

    if (MTD_IS_X32X0_BASE(devPtr->deviceId) || Use0p5usecResolution == MTD_FALSE)
    {
        lowResSupported = MTD_FALSE;
    }
    else
    {
        /* check if this feature is supported */
        ATTEMPT(mtdHwGetPhyRegField(devPtr,port,1,0xC033,2,1,&temp));

        if (temp)
        {
            lowResSupported = MTD_TRUE;
            mtdHwSetPhyRegField(devPtr,port,1,0xC033,3,1,1); /* enable the feature*/            
            multiplier = 2;            
        }
        
    }

    if (lowResSupported)
    {
        /* do range checking on all the input parameters to make sure none are too large/will overflow */
        if (XGMII_Enter_Timeout > 127 ||
            GMII_Enter_Timeout > 127 || 
            MII_Enter_Timeout > 127 || 
            XGMII_Exit_Timeout > 127 || 
            GMII_Exit_Timeout > 127 || 
            MII_Exit_Timeout > 127)
        {
            /* the timer value is going to overflow, need to return an error. caller must use 1 usec resolution */
            /* for timer values bigger than 127 */
            return MTD_FAIL;
        }
    }
    
    if (XGMII_Enter_Timeout)
    {
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,1,0xC033,8,8,((MTD_U16)XGMII_Enter_Timeout)*multiplier));
    }
    else
    {
        /* it was 0, so set it to default */
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,1,0xC033,8,8,((MTD_U16)0x1A)*multiplier));
    }

    if (MTD_IS_X32X0_BASE(devPtr->deviceId))
    {
        /* this value is not adjustable on X33x0/E20x0/E21x0 PHYs */
        if (XGMII_Exit_Timeout)
        {
            ATTEMPT(mtdHwSetPhyRegField(devPtr,port,31,0xF005,8,8,(MTD_U16)XGMII_Exit_Timeout));
        }
        else
        {
            /* it was 0, so set it to default */
            ATTEMPT(mtdHwSetPhyRegField(devPtr,port,31,0xF005,8,8,(MTD_U16)0x8));
        }
    }

    if (GMII_Enter_Timeout)
    {
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,31,0xF004,0,8,((MTD_U16)GMII_Enter_Timeout)*multiplier));
    }
    else
    {
        /* it was 0, so set it to default */
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,31,0xF004,0,8,((MTD_U16)0x12)*multiplier));
    }

    if (GMII_Exit_Timeout)
    {
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,31,0xF006,0,8,((MTD_U16)GMII_Exit_Timeout)*multiplier));
    }
    else
    {
        /* it was 0, so set it to default */
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,31,0xF006,0,8,((MTD_U16)0x12)*multiplier));
    }
    
    if (MII_Enter_Timeout)
    {
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,31,0xF004,8,8,((MTD_U16)MII_Enter_Timeout)*multiplier));
    }
    else
    {
        /* it was 0, so set it to default */
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,31,0xF004,8,8,((MTD_U16)0x20)*multiplier));
    }

    if (MII_Exit_Timeout)
    {
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,31,0xF006,8,8,((MTD_U16)MII_Exit_Timeout)*multiplier));
    }
    else
    {
        /* it was 0, so set it to default */
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,31,0xF006,8,8,((MTD_U16)0x20)*multiplier));
    }

    if (IPG_Length)
    {
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,31,0xF005,0,8,(MTD_U16)IPG_Length));
    }
    else
    {
        /* it was 0, so set it to default */
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,31,0xF005,0,8,(MTD_U16)0x0C));
    }

    switch (EEE_Mode_Control)
    {
        case MTD_EEE_MODE_DISABLE:
            ATTEMPT(mtdHwSetPhyRegField(devPtr,port,1,0xC033,0,2,(MTD_U16)0));
            break;

        case MTD_EEE_MODE_ENABLE_NO_LEGACY:
            ATTEMPT(mtdHwSetPhyRegField(devPtr,port,1,0xC033,0,2,(MTD_U16)2));
            break;

        case MTD_EEE_MODE_ENABLE_WITH_LEGACY:
            ATTEMPT(mtdHwSetPhyRegField(devPtr,port,1,0xC033,0,2,(MTD_U16)3));
            break;

        default:
            return MTD_FAIL;
            break;
    }

    return MTD_OK;
}


MTD_STATUS mtdGetEeeBufferConfig
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U8 *EEE_Mode_Control, 
    OUT MTD_U8 *XGMII_Enter_Timeout, 
    OUT MTD_U8 *GMII_Enter_Timeout, 
    OUT MTD_U8 *MII_Enter_Timeout, 
    OUT MTD_U8 *XGMII_Exit_Timeout, 
    OUT MTD_U8 *GMII_Exit_Timeout, 
    OUT MTD_U8 *MII_Exit_Timeout, 
    OUT MTD_U8 *IPG_Length 
)
{
    MTD_U16 U16EEE_Mode_Control,
         U16XGMII_Enter_Timeout,
         U16GMII_Enter_Timeout,
         U16MII_Enter_Timeout,
         U16XGMII_Exit_Timeout,
         U16GMII_Exit_Timeout,
         U16MII_Exit_Timeout,
         U16IPG_Length;

    MTD_U16 temp, divider=1;
    MTD_BOOL lowResSupported;

    if (MTD_IS_X32X0_BASE(devPtr->deviceId))
    {
        lowResSupported = MTD_FALSE;
    }
    else
    {
        /* check if this feature is supported and enabled */
        ATTEMPT(mtdHwGetPhyRegField(devPtr,port,1,0xC033,2,2,&temp));

        if (temp == 3) /* bits 3:2 are 11b */
        {
            lowResSupported = MTD_TRUE;
            divider = 2;            
        }
        
    }

    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,1,0xC033,8,8,&U16XGMII_Enter_Timeout));
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,31,0xF005,8,8,&U16XGMII_Exit_Timeout));
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,31,0xF004,0,8,&U16GMII_Enter_Timeout));
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,31,0xF006,0,8,&U16GMII_Exit_Timeout));
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,31,0xF004,8,8,&U16MII_Enter_Timeout));
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,31,0xF006,8,8,&U16MII_Exit_Timeout));
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,31,0xF005,0,8,&U16IPG_Length));
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,1,0xC033,0,2,&U16EEE_Mode_Control));

    *EEE_Mode_Control = (MTD_U8)U16EEE_Mode_Control;
    
    *XGMII_Enter_Timeout = ((MTD_U8)U16XGMII_Enter_Timeout)/divider;
    *GMII_Enter_Timeout = ((MTD_U8)U16GMII_Enter_Timeout)/divider;
    *MII_Enter_Timeout = ((MTD_U8)U16MII_Enter_Timeout)/divider;
    *XGMII_Exit_Timeout = ((MTD_U8)U16XGMII_Exit_Timeout)/divider; /* NOTE: on 33X0 and later PHYs 10G/2.5G are internally set to 7.5 and 29.5 usec XGMII exit timers if */
                                                                   /* the firmware supports it and it's enabled. translating it to 1 usec resoluition will cause the 0.5 usec */
                                                                   /* to be rounded down. read the register directly to see the actual value if this 0.5 usec is important */
    *GMII_Exit_Timeout = ((MTD_U8)U16GMII_Exit_Timeout)/divider;
    *MII_Exit_Timeout = ((MTD_U8)U16MII_Exit_Timeout)/divider;

    *IPG_Length = (MTD_U8)U16IPG_Length;

    if (*EEE_Mode_Control == 1)
    {
        return MTD_FAIL; /* This doesn't make sense, it means EEE is disabled with legacy buffer enabled */
    }
    else if (*EEE_Mode_Control == 2 || *EEE_Mode_Control == 3)
    {
        *EEE_Mode_Control -= 1;
    }
    /* else it's 0, disabled, don't do anything to it, returns MTD_EEE_MODE_DISABLE */

    return MTD_OK;  
}


MTD_STATUS mtdMACSECEeeBufferConfig
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U8 EEE_Mode_Control, 
    IN MTD_U8 XGMII_Enter_Timeout, 
    IN MTD_U8 GMII_Enter_Timeout, 
    IN MTD_U8 MII_Enter_Timeout, 
    IN MTD_U8 XGMII_Exit_Timeout, 
    IN MTD_U8 GMII_Exit_Timeout, 
    IN MTD_U8 MII_Exit_Timeout, 
    IN MTD_BOOL Force_Sys_LPI, 
    IN MTD_BOOL Force_Wre_LPI 
)
{
    MTD_U16 macSecEnable;

    /* make sure macsec was already turned on */
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,MTD_CUNIT_MODE_CONFIG,12,2,&macSecEnable));

    if (macSecEnable != 3)
    {
        return MTD_FAIL;
    }

    if (XGMII_Enter_Timeout)
    {
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x809C,4,8,(MTD_U32)XGMII_Enter_Timeout));
    }
    else
    {
        /* it was 0, so set it to default */
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x809C,4,8,(MTD_U32)0xFF));
    }

    if (XGMII_Exit_Timeout)
    {
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x809E,0,8,(MTD_U32)XGMII_Exit_Timeout));
    }
    else
    {
        /* it was 0, so set it to default */
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x809E,0,8,(MTD_U32)0x4B));
    }

    if (GMII_Enter_Timeout)
    {
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x809C,12,8,(MTD_U32)GMII_Enter_Timeout));
    }
    else
    {
        /* it was 0, so set it to default */
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x809C,12,8,(MTD_U32)0x12));
    }

    if (GMII_Exit_Timeout)
    {
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x809E,8,8,(MTD_U32)GMII_Exit_Timeout));
    }
    else
    {
        /* it was 0, so set it to default */
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x809E,8,8,(MTD_U32)0x12));
    }
    
    if (MII_Enter_Timeout)
    {
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x809C,20,8,(MTD_U32)MII_Enter_Timeout));
    }
    else
    {
        /* it was 0, so set it to default */
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x809C,20,8,(MTD_U32)0x20));
    }

    if (MII_Exit_Timeout)
    {
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x809E,16,8,(MTD_U32)MII_Exit_Timeout));
    }
    else
    {
        /* it was 0, so set it to default */
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x809E,16,8,(MTD_U32)0x20));
    }

    if (Force_Sys_LPI == MTD_TRUE)
    {
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x809C,3,1,(MTD_U32)1));
    }
    else
    {
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x809C,3,1,(MTD_U32)0));
    }

    if (Force_Wre_LPI == MTD_TRUE)
    {
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x809C,2,1,(MTD_U32)1));
    }
    else
    {
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x809C,2,1,(MTD_U32)0));
    }

    switch (EEE_Mode_Control)
    {
        case MTD_EEE_MODE_DISABLE:
            ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x809C,0,2,(MTD_U32)0));
            break;

        case MTD_EEE_MODE_ENABLE_NO_LEGACY:
            ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x809C,0,2,(MTD_U32)2));
            break;

        case MTD_EEE_MODE_ENABLE_WITH_LEGACY:
            ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x809C,0,2,(MTD_U32)1));
            break;

        default:
            return MTD_FAIL;
            break;
    }

    return MTD_OK;
    
}

MTD_STATUS mtdMACSECEeeBufferConfig5G_2P5G
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U8 FiveG_Enter_Timeout, 
    IN MTD_U8 TwoP5G_Enter_Timeout, 
    IN MTD_U8 FiveG_Exit_Timeout, 
    IN MTD_U8 TwoP5G_Exit_Timeout
)
{
    MTD_U16 macSecEnable;

    /* make sure macsec was already turned on */
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,MTD_CUNIT_MODE_CONFIG,12,2,&macSecEnable));

    if (macSecEnable != 3)
    {
        return MTD_FAIL;
    }

    if (FiveG_Enter_Timeout)
    {
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x80A0,0,8,(MTD_U32)FiveG_Enter_Timeout));
    }
    else
    {
        /* it was 0, so set it to default */
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x80A0,0,8,(MTD_U32)0xB4));
    }

    if (FiveG_Exit_Timeout)
    {
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x80A0,8,8,(MTD_U32)FiveG_Exit_Timeout));
    }
    else
    {
        /* it was 0, so set it to default */
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x80A0,8,8,(MTD_U32)0x96));
    }    


    if (TwoP5G_Enter_Timeout)
    {
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x80A0,16,8,(MTD_U32)TwoP5G_Enter_Timeout));
    }
    else
    {
        /* it was 0, so set it to default */
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x80A0,16,8,(MTD_U32)0x12));
    }

    if (TwoP5G_Exit_Timeout)
    {
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x809E,24,8,(MTD_U32)TwoP5G_Exit_Timeout));
    }
    else
    {
        /* it was 0, so set it to default */
        ATTEMPT(mtdHwSetMsecPhyRegField(devPtr,port,31,0x809E,24,8,(MTD_U32)0x1E));
    }    

    return MTD_OK;
    
}


MTD_STATUS mtdGetMACSECEeeBufferConfig
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U8 *EEE_Mode_Control, 
    OUT MTD_U8 *XGMII_Enter_Timeout, 
    OUT MTD_U8 *GMII_Enter_Timeout, 
    OUT MTD_U8 *MII_Enter_Timeout, 
    OUT MTD_U8 *XGMII_Exit_Timeout, 
    OUT MTD_U8 *GMII_Exit_Timeout, 
    OUT MTD_U8 *MII_Exit_Timeout, 
    OUT MTD_BOOL *Force_Sys_LPI, 
    OUT MTD_BOOL *Force_Wre_LPI 
)
{
    MTD_U32 U32EEE_Mode_Control,
        U32XGMII_Enter_Timeout,
        U32GMII_Enter_Timeout,
        U32MII_Enter_Timeout,
        U32XGMII_Exit_Timeout,
        U32GMII_Exit_Timeout,
        U32MII_Exit_Timeout,
        U32Force_Sys_LPI,
        U32Force_Wre_LPI;
    MTD_U16 macSecEnable;

    /* make sure macsec was already turned on */
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,MTD_CUNIT_MODE_CONFIG,12,2,&macSecEnable));

    if (macSecEnable != 3)
    {
        return MTD_FAIL;
    }
    
    ATTEMPT(mtdHwGetMsecPhyRegField(devPtr,port,31,0x809C,4,8,&U32XGMII_Enter_Timeout));
    ATTEMPT(mtdHwGetMsecPhyRegField(devPtr,port,31,0x809E,0,8,&U32XGMII_Exit_Timeout));
    *XGMII_Enter_Timeout = (MTD_U8)U32XGMII_Enter_Timeout;
    *XGMII_Exit_Timeout = (MTD_U8)U32XGMII_Exit_Timeout;

    ATTEMPT(mtdHwGetMsecPhyRegField(devPtr,port,31,0x809C,12,8,&U32GMII_Enter_Timeout));
    *GMII_Enter_Timeout = (MTD_U8)U32GMII_Enter_Timeout;

    ATTEMPT(mtdHwGetMsecPhyRegField(devPtr,port,31,0x809E,8,8,&U32GMII_Exit_Timeout));
    ATTEMPT(mtdHwGetMsecPhyRegField(devPtr,port,31,0x809C,20,8,&U32MII_Enter_Timeout));
    ATTEMPT(mtdHwGetMsecPhyRegField(devPtr,port,31,0x809E,16,8,&U32MII_Exit_Timeout));
    *GMII_Exit_Timeout = (MTD_U8)U32GMII_Exit_Timeout;
    *MII_Enter_Timeout = (MTD_U8)U32MII_Enter_Timeout;
    *MII_Exit_Timeout = (MTD_U8)U32MII_Exit_Timeout;

    ATTEMPT(mtdHwGetMsecPhyRegField(devPtr,port,31,0x809C,2,1,&U32Force_Wre_LPI));
    ATTEMPT(mtdHwGetMsecPhyRegField(devPtr,port,31,0x809C,3,1,&U32Force_Sys_LPI));
    *Force_Sys_LPI = (MTD_BOOL)U32Force_Sys_LPI;
    *Force_Wre_LPI = (MTD_BOOL)U32Force_Wre_LPI;

    ATTEMPT(mtdHwGetMsecPhyRegField(devPtr,port,31,0x809C,0,2,&U32EEE_Mode_Control));
    *EEE_Mode_Control = (MTD_U8)U32EEE_Mode_Control;
    if (*EEE_Mode_Control == 3)
    {
        return MTD_FAIL; /* This setting doesn't make sense */
    }
    else if (*EEE_Mode_Control == 2)
    {
        *EEE_Mode_Control = MTD_EEE_MODE_ENABLE_NO_LEGACY;
    }
    else if (*EEE_Mode_Control == 1)
    {
        *EEE_Mode_Control = MTD_EEE_MODE_ENABLE_WITH_LEGACY;
    }
    /* else it's 0, disabled, don't do anything to it, returns MTD_EEE_MODE_DISABLE */

    return MTD_OK;  
    
}

MTD_STATUS mtdGetMACSECEeeBufferConfig5G_2P5G
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U8 *FiveG_Enter_Timeout, 
    OUT MTD_U8 *TwoP5G_Enter_Timeout, 
    OUT MTD_U8 *FiveG_Exit_Timeout, 
    OUT MTD_U8 *TwoP5G_Exit_Timeout
)
{
    MTD_U32 U32FiveG_Enter_Timeout, U32TwoP5G_Enter_Timeout, U32FiveG_Exit_Timeout, 
            U32TwoP5G_Exit_Timeout, tempVal;
    MTD_U16 macSecEnable;

    /* make sure macsec was already turned on */
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,MTD_CUNIT_MODE_CONFIG,12,2,&macSecEnable));

    if (macSecEnable != 3)
    {
        return MTD_FAIL;
    }  

    ATTEMPT(mtdHwMsecRead(devPtr,port,31,0x80A0,&tempVal));
    
    ATTEMPT(mtdHwGetRegFieldFromLongWord(tempVal,0,8,&U32FiveG_Enter_Timeout));
    *FiveG_Enter_Timeout = (MTD_U8)U32FiveG_Enter_Timeout;
    
    ATTEMPT(mtdHwGetRegFieldFromLongWord(tempVal,8,8,&U32FiveG_Exit_Timeout));
    *FiveG_Exit_Timeout = (MTD_U8)U32FiveG_Exit_Timeout;
    
    ATTEMPT(mtdHwGetRegFieldFromLongWord(tempVal,16,8,&U32TwoP5G_Enter_Timeout));
    *TwoP5G_Enter_Timeout = (MTD_U8)U32TwoP5G_Enter_Timeout;

    ATTEMPT(mtdHwMsecRead(devPtr,port,31,0x809E,&tempVal));
    
    ATTEMPT(mtdHwGetRegFieldFromLongWord(tempVal,24,8,&U32TwoP5G_Exit_Timeout));
    *TwoP5G_Exit_Timeout = (MTD_U8)U32TwoP5G_Exit_Timeout;

    return MTD_OK;
    
}


MTD_STATUS mtdEeeEnableOverrideMode 
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port  
)
{
    devPtr = devPtr;
    port = port;

    return MTD_FAIL; /* not implemented yet */
}

MTD_STATUS mtdEeeDisableOverrideMode 
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port  
)
{
    devPtr = devPtr;
    port = port;

    return MTD_FAIL; /* not implemented yet */
}


