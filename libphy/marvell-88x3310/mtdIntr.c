/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions and global defines/data for
high and low level interrupt functions of the Marvell 88X32X0, 
88X33X0, 88E20X0 and 88E21X0 ethernet PHYs.
********************************************************************/
#include "mtdApiRegs.h"
#include "mtdApiTypes.h"
#include "mtdHwCntl.h"
#include "mtdAPI.h"
#include "mtdIntr.h"
#include "mtdUtils.h"

/*******************************************************************
  mtdGetPortIntrStatus
 
 *******************************************************************/
MTD_STATUS mtdGetPortIntrStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16     port,
    OUT MTD_BOOL   *interruptTrig,
    OUT MTD_INTR_STATUS *interruptStatus
)
{
    mtdMemSet(interruptStatus, 0, sizeof(MTD_INTR_STATUS));

    /* C-unit */
    ATTEMPT(mtdGetTopInterruptStatus(devPtr,port,&(interruptStatus->cunitIntr)));

    /* T-unit */
    ATTEMPT(mtdGetTunitInterruptStatus(devPtr,port,&(interruptStatus->tunitIntr)));

    /* H-unit */
    ATTEMPT(mtdGetBaseRInterruptStatus(devPtr,port,MTD_H_UNIT,&(interruptStatus->hunitIntr.baseRIntr)));

    if (!MTD_IS_E21X0_BASE(devPtr->deviceId))
    {    
        ATTEMPT(mtdGetX2X4InterruptStatus(devPtr,port,&(interruptStatus->hunitIntr.x2x4Intr)));
    }

    ATTEMPT(mtdGetBaseXInterruptStatus(devPtr,port,MTD_H_UNIT,&(interruptStatus->hunitIntr.baseXIntr)));
    ATTEMPT(mtdGetMiscInterruptStatus(devPtr,port,MTD_H_UNIT,&(interruptStatus->hunitIntr.miscIntr)));

    /* X-unit */
    if (MTD_HAS_X_UNIT(devPtr))
    {
        ATTEMPT(mtdGetBaseRInterruptStatus(devPtr,port,MTD_X_UNIT,&(interruptStatus->xunitIntr.baseRIntr)));
        ATTEMPT(mtdGetBaseXInterruptStatus(devPtr,port,MTD_X_UNIT,&(interruptStatus->xunitIntr.baseXIntr)));
        ATTEMPT(mtdGetMiscInterruptStatus(devPtr,port,MTD_X_UNIT,&(interruptStatus->xunitIntr.miscIntr)));
    }

    if (mtdIsZero(interruptStatus, sizeof(MTD_INTR_STATUS)))
    {
       *interruptTrig = MTD_FALSE;
    }
    else
    {
       *interruptTrig = MTD_TRUE;
    }

    return MTD_OK;
}

/*******************************************************************
  mtdGetPortIntrStatusISR
 
 *******************************************************************/
MTD_STATUS mtdGetPortIntrStatusISR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16     port,
    OUT MTD_BOOL   *interruptTrig,
    OUT MTD_INTR_STATUS *interruptStatus
)
{
    MTD_U16 status16,topIntrMask,intrMask16;
    MTD_U32 status32,intrMask32;

    /* clear interruptStatus */
    mtdMemSet(interruptStatus, 0, sizeof(MTD_INTR_STATUS));

    ATTEMPT(mtdGetTopInterruptsEnabled(devPtr,port,&topIntrMask));

    /* C-unit */
    ATTEMPT(mtdGetTopInterruptStatus(devPtr,port,&status16));
    interruptStatus->cunitIntr = (status16 & topIntrMask);

    if (interruptStatus->cunitIntr)
    {
        *interruptTrig = MTD_TRUE;
    }
    else
    {
        *interruptTrig = MTD_FALSE;
    }

    /* T-unit */
    ATTEMPT(mtdGetTunitInterruptsEnabled(devPtr,port,&intrMask32));
    ATTEMPT(mtdGetTunitInterruptStatus(devPtr,port,&status32));
    interruptStatus->tunitIntr = (status32 & intrMask32);

    /* H-unit */
    ATTEMPT(mtdGetBaseRInterruptsEnabled(devPtr,port,MTD_H_UNIT,&intrMask16));
    ATTEMPT(mtdGetBaseRInterruptStatus(devPtr,port,MTD_H_UNIT,&status16));
    interruptStatus->hunitIntr.baseRIntr = (status16 & intrMask16);

    if (!MTD_IS_E21X0_BASE(devPtr->deviceId))
    { 
        ATTEMPT(mtdGetX2X4InterruptsEnabled(devPtr,port,&intrMask32));
        ATTEMPT(mtdGetX2X4InterruptStatus(devPtr,port,&status32));
        interruptStatus->hunitIntr.x2x4Intr = (status32 & intrMask32);
    }

    ATTEMPT(mtdGetBaseXInterruptsEnabled(devPtr,port,MTD_H_UNIT,&intrMask16));
    ATTEMPT(mtdGetBaseXInterruptStatus(devPtr,port,MTD_H_UNIT,&status16));
    interruptStatus->hunitIntr.baseXIntr = (status16 & intrMask16);

    ATTEMPT(mtdGetMiscInterruptsEnabled(devPtr,port,MTD_H_UNIT,&intrMask16));
    ATTEMPT(mtdGetMiscInterruptStatus(devPtr,port,MTD_H_UNIT,&status16));
    interruptStatus->hunitIntr.miscIntr = (status16 & intrMask16);
    
    /* X-unit */
    if (MTD_HAS_X_UNIT(devPtr))
    {
        ATTEMPT(mtdGetBaseRInterruptsEnabled(devPtr,port,MTD_X_UNIT,&intrMask16));
        ATTEMPT(mtdGetBaseRInterruptStatus(devPtr,port,MTD_X_UNIT,&status16));
        interruptStatus->xunitIntr.baseRIntr = (status16 & intrMask16);

        ATTEMPT(mtdGetBaseXInterruptsEnabled(devPtr,port,MTD_X_UNIT,&intrMask16));
        ATTEMPT(mtdGetBaseXInterruptStatus(devPtr,port,MTD_X_UNIT,&status16));
        interruptStatus->xunitIntr.baseXIntr = (status16 & intrMask16);

        ATTEMPT(mtdGetMiscInterruptsEnabled(devPtr,port,MTD_X_UNIT,&intrMask16));
        ATTEMPT(mtdGetMiscInterruptStatus(devPtr,port,MTD_X_UNIT,&status16));
        interruptStatus->xunitIntr.miscIntr = (status16 & intrMask16);
    }

    return MTD_OK;
}

/* C-unit */
/*******************************************************************
  mtdEnableDisableTopInterrupts
 
 *******************************************************************/
MTD_STATUS mtdEnableDisableTopInterrupts
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  interrupt_sel,
    IN MTD_BOOL enable
)
{
    MTD_U16 regValue;

    if (!MTD_HAS_X_UNIT(devPtr))
    {
        if ((interrupt_sel & MTD_X_UNIT_INTR) && (enable == MTD_TRUE))
        {
            MTD_DBG_ERROR("mtdEnableDisableTopInterrupts() - No X-unit on this device.\n");
            return MTD_FAIL;
        }
    }

    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_CUNIT_INTERRUPT_CTRL,&regValue));

    if (enable)
    {
        regValue |= interrupt_sel;
    }
    else
    {
        regValue &= ~interrupt_sel;
    }

    ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_CUNIT_INTERRUPT_CTRL,regValue));

    return MTD_OK;
}

/*******************************************************************
  mtdInterruptPinControl
 
 *******************************************************************/
MTD_STATUS mtdInterruptPinControl
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  polarity,
    IN MTD_BOOL force
)
{
    MTD_U16 regValue;

    regValue = polarity;
    if (force == MTD_TRUE)
    {
        regValue |= 0x01;
    }

    ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_CUNIT_INTERRUPT_CTRL1,regValue));

    return MTD_OK;
}

/*******************************************************************
  mtdGetTopInterruptsEnabled
 
 *******************************************************************/
MTD_STATUS mtdGetTopInterruptsEnabled
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    OUT MTD_U16 *interruptEnabled
)
{
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_CUNIT_INTERRUPT_CTRL,interruptEnabled));

    return MTD_OK;
}

/*******************************************************************
  mtdGetTopInterruptStatus
 
 *******************************************************************/
MTD_STATUS mtdGetTopInterruptStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    OUT MTD_U16 *interruptStatus
)
{

    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_CUNIT_INTERRUPT_STATUS,interruptStatus));

    return MTD_OK;
}

/* H-unit */
/*******************************************************************
  mtdEnableDisableX2X4Interrupts
 
 *******************************************************************/
MTD_STATUS mtdEnableDisableX2X4Interrupts
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U32  interrupt_sel,
    IN MTD_BOOL enable
)
{
    MTD_U16 regValue1,regValue2;

    if (MTD_IS_E21X0_BASE(devPtr->deviceId))
    {
        MTD_DBG_ERROR("mtdEnableDisableX2X4Interrupts() - X2/X4 is not supported on E21X0 PHYs.\n");
        return MTD_FAIL;
    }

    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_X2_X4_INTERRUPT_CTRL1,&regValue1));
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_X2_X4_INTERRUPT_CTRL2,&regValue2));

    if (enable)
    {
        regValue1 |= ((interrupt_sel>>16) & 0xFFFF);
        regValue2 |= (interrupt_sel & 0xFFFF);
    }
    else
    {
        regValue1 &= ~((interrupt_sel>>16) & 0xFFFF);
        regValue2 &= ~(interrupt_sel & 0xFFFF);
    }

    ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_X2_X4_INTERRUPT_CTRL1,regValue1));
    ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_X2_X4_INTERRUPT_CTRL2,regValue2));

    return MTD_OK;
}

/*******************************************************************
  mtdGetX2X4InterruptsEnabled
 
 *******************************************************************/
MTD_STATUS mtdGetX2X4InterruptsEnabled
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    OUT MTD_U32 *interruptEnabled
)
{
    MTD_U16 regValue1,regValue2;
    MTD_U32 temp;

    if (MTD_IS_E21X0_BASE(devPtr->deviceId))
    {
        MTD_DBG_ERROR("mtdGetX2X4InterruptsEnabled() - X2/X4 is not supported on E21X0 PHYs.\n");
        return MTD_FAIL;
    }

    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_X2_X4_INTERRUPT_CTRL1,&regValue1));
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_X2_X4_INTERRUPT_CTRL2,&regValue2));

    temp = (((MTD_U32)regValue1 << 16) & 0xFFFF0000)|((MTD_U32)regValue2 & 0x0000FFFF);
    *interruptEnabled = temp;

    return MTD_OK;
}

/*******************************************************************
  mtdGetX2X4InterruptStatus
 
 *******************************************************************/
MTD_STATUS mtdGetX2X4InterruptStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    OUT MTD_U32 *interruptStatus
)
{
    MTD_U16 regValue1,regValue2;
    MTD_U32 temp;

    if (MTD_IS_E21X0_BASE(devPtr->deviceId))
    {
        MTD_DBG_ERROR("mtdGetX2X4InterruptStatus() - X2/X4 is not supported on E21X0 PHYs.\n");
        return MTD_FAIL;
    }

    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_X2_X4_INTERRUPT_STATUS1,&regValue1));
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_X2_X4_INTERRUPT_STATUS2,&regValue2));

    temp = (((MTD_U32)regValue1 << 16) & 0xFFFF0000)|((MTD_U32)regValue2 & 0x0000FFFF);
    *interruptStatus = temp;

    return MTD_OK;
}

/*******************************************************************
  mtdGetX2X4RealTimeStatus
 
 *******************************************************************/
MTD_STATUS mtdGetX2X4RealTimeStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    OUT MTD_U16 *realTimeStatus
)
{

    if (MTD_IS_E21X0_BASE(devPtr->deviceId))
    {
        MTD_DBG_ERROR("mtdGetX2X4RealTimeStatus() - X2/X4 is not supported on E21X0 PHYs.\n");
        return MTD_FAIL;
    }

    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_X2_X4_REALTIME_STATUS,realTimeStatus));

    return MTD_OK;
}


/* H and X-unit */
/*******************************************************************
  mtdEnableDisableBaseRInterrupts
 
 *******************************************************************/
MTD_STATUS mtdEnableDisableBaseRInterrupts
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  HorXunit,
    IN MTD_U16  interrupt_sel,
    IN MTD_BOOL enable
)
{
    MTD_U16 regValue;
    
    if ((HorXunit==MTD_X_UNIT)&&(!MTD_HAS_X_UNIT(devPtr)))
    {
        MTD_DBG_ERROR("mtdEnableDisableBaseRInterrupts() - No X-unit on this device.\n");
        return MTD_FAIL;
    }

    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_10GBR_INTERRUPT_CTRL,&regValue));

    if (enable)
    {
        regValue |= interrupt_sel;
    }
    else
    {
        regValue &= ~interrupt_sel;
    }

    ATTEMPT(mtdHwXmdioWrite(devPtr,port,HorXunit,MTD_10GBR_INTERRUPT_CTRL,regValue));

    return MTD_OK;
}

/*******************************************************************
  mtdGetBaseRInterruptsEnabled
 
 *******************************************************************/
MTD_STATUS mtdGetBaseRInterruptsEnabled
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *interruptEnabled
)
{

    if ((HorXunit==MTD_X_UNIT)&&(!MTD_HAS_X_UNIT(devPtr)))
    {
        MTD_DBG_ERROR("mtdGetBaseRInterruptsEnabled() - No X-unit on this PHY.\n");
        return MTD_FAIL;
    }

    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_10GBR_INTERRUPT_CTRL,interruptEnabled));

    return MTD_OK;
}

/*******************************************************************
  mtdGetBaseRInterruptStatus
 
 *******************************************************************/
MTD_STATUS mtdGetBaseRInterruptStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *interruptStatus
)
{

    if ((HorXunit==MTD_X_UNIT)&&(!MTD_HAS_X_UNIT(devPtr)))
    {
        MTD_DBG_ERROR("mtdGetBaseRInterruptStatus() - No X-unit on this PHY.\n");
        return MTD_FAIL;
    }

    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_10GBR_INTERRUPT_STATUS,interruptStatus));

    return MTD_OK;
}

/*******************************************************************
  mtdGetBaseRrealTimeStatus
 
 *******************************************************************/
MTD_STATUS mtdGetBaseRrealTimeStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *realTimeStatus
)
{

    if ((HorXunit==MTD_X_UNIT)&&(!MTD_HAS_X_UNIT(devPtr)))
    {
        MTD_DBG_ERROR("mtdGetBaseRrealTimeStatus() - No X-unit on this PHY.\n");
        return MTD_FAIL;
    }

    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_10GBR_REALTIME_STATUS,realTimeStatus));

    return MTD_OK;
}

/*******************************************************************
  mtdEnableDisableBaseXInterrupts
 
 *******************************************************************/
MTD_STATUS mtdEnableDisableBaseXInterrupts
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  HorXunit,
    IN MTD_U16  interrupt_sel,
    IN MTD_BOOL enable
)
{
    MTD_U16 regValue;

    if ((HorXunit==MTD_X_UNIT)&&(!MTD_HAS_X_UNIT(devPtr)))
    {
        MTD_DBG_ERROR("mtdEnableDisableBaseXInterrupts() - No X-unit on this PHY.\n");
        return MTD_FAIL;
    }

    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_1GBX_INTERRUPT_CTRL,&regValue));

    if (enable)
    {
        regValue |= interrupt_sel;
    }
    else
    {
        regValue &= ~interrupt_sel;
    }

    ATTEMPT(mtdHwXmdioWrite(devPtr,port,HorXunit,MTD_1GBX_INTERRUPT_CTRL,regValue));

    return MTD_OK;
}

/*******************************************************************
  mtdGetBaseXInterruptsEnabled
 
 *******************************************************************/
MTD_STATUS mtdGetBaseXInterruptsEnabled
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *interruptEnabled
)
{

    if ((HorXunit==MTD_X_UNIT)&&(!MTD_HAS_X_UNIT(devPtr)))
    {
        MTD_DBG_ERROR("mtdGetBaseXInterruptsEnabled() - No X-unit on this PHY.\n");
        return MTD_FAIL;
    }

    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_1GBX_INTERRUPT_CTRL,interruptEnabled));

    return MTD_OK;
}

/*******************************************************************
  mtdGetBaseXInterruptStatus
 
 *******************************************************************/
MTD_STATUS mtdGetBaseXInterruptStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *interruptStatus
)
{

    if ((HorXunit==MTD_X_UNIT)&&(!MTD_HAS_X_UNIT(devPtr)))
    {
        MTD_DBG_ERROR("mtdGetBaseXInterruptStatus() - No X-unit on this PHY.\n");
        return MTD_FAIL;
    }

    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_1GBX_INTERRUPT_STATUS,interruptStatus));

    return MTD_OK;
}

/*******************************************************************
  mtdGetBaseXrealTimeStatus
 
 *******************************************************************/
MTD_STATUS mtdGetBaseXrealTimeStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *realTimeStatus
)
{
    if ((HorXunit==MTD_X_UNIT)&&(!MTD_HAS_X_UNIT(devPtr)))
    {
        MTD_DBG_ERROR("mtdGetBaseXrealTimeStatus() - No X-unit on this PHY.\n");
        return MTD_FAIL;
    }

    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_1GBX_REALTIME_STATUS,realTimeStatus));

    return MTD_OK;
}

/*******************************************************************
  mtdEnableDisableMiscInterrupts
 
********************************************************************/
MTD_STATUS mtdEnableDisableMiscInterrupts
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  HorXunit,
    IN MTD_U16  interrupt_sel,
    IN MTD_BOOL enable
)
{
    MTD_U16 regValue;

    if ((HorXunit==MTD_X_UNIT)&&(!MTD_HAS_X_UNIT(devPtr)))
    {
        MTD_DBG_ERROR("mtdEnableDisableMiscInterrupts() - No X-unit on this PHY.\n");
        return MTD_FAIL;
    }

    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_FIFO_CRC_INTR_ENABLE,&regValue));

    if (enable)
    {
        regValue |= interrupt_sel;
    }
    else
    {
        regValue &= ~interrupt_sel;
    }

    ATTEMPT(mtdHwXmdioWrite(devPtr,port,HorXunit,MTD_FIFO_CRC_INTR_ENABLE,regValue));

    return MTD_OK;
}

/*******************************************************************
  mtdGetMiscInterruptsEnabled
 
********************************************************************/
MTD_STATUS mtdGetMiscInterruptsEnabled
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *interruptEnabled
)
{

    if ((HorXunit==MTD_X_UNIT)&&(!MTD_HAS_X_UNIT(devPtr)))
    {
        MTD_DBG_ERROR("mtdGetMiscInterruptsEnabled() - No X-unit on this PHY.\n");
        return MTD_FAIL;
    }

    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_FIFO_CRC_INTR_ENABLE,interruptEnabled));

    return MTD_OK;
}

/*******************************************************************
  mtdGetMiscInterruptStatus
 
********************************************************************/
MTD_STATUS mtdGetMiscInterruptStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *interruptStatus
)
{

    if ((HorXunit==MTD_X_UNIT)&&(!MTD_HAS_X_UNIT(devPtr)))
    {
        MTD_DBG_ERROR("mtdGetMiscInterruptStatus() - No X-unit on this PHY.\n");
        return MTD_FAIL;
    }

    ATTEMPT(mtdHwXmdioRead(devPtr,port,HorXunit,MTD_FIFO_CRC_INTR_STATUS,interruptStatus));

    return MTD_OK;
}


/* T-unit */
/*******************************************************************
  mtdEnableDisableTunitInterrupts
 
 *******************************************************************/
MTD_STATUS mtdEnableDisableTunitInterrupts
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U32  interrupt_sel,
    IN MTD_BOOL enable
)
{
    MTD_U16 regValue1,regValue2;

    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_INTERRUPT_CTRL1,&regValue1));
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_INTERRUPT_CTRL2,&regValue2));

    if (enable)
    {
        regValue1 |= (interrupt_sel & 0xFFFF);
        regValue2 |= ((interrupt_sel>>16) & 0xFFFF);
    }
    else
    {
        regValue1 &= ~(interrupt_sel & 0xFFFF);
        regValue2 &= ~((interrupt_sel>>16) & 0xFFFF);
    }

    ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_TUNIT_INTERRUPT_CTRL1,regValue1));
    ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_TUNIT_INTERRUPT_CTRL2,regValue2));

    return MTD_OK;
}

/*******************************************************************
  mtdGetTunitInterruptsEnabled
 
 *******************************************************************/
MTD_STATUS mtdGetTunitInterruptsEnabled
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    OUT MTD_U32 *interruptEnabled
)
{
    MTD_U16 regValue1,regValue2;
    MTD_U32 temp;

    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_INTERRUPT_CTRL1,&regValue1));
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_INTERRUPT_CTRL2,&regValue2));

    temp = (((MTD_U32)regValue2 << 16) & 0xFFFF0000)|((MTD_U32)regValue1 & 0x0000FFFF);
    *interruptEnabled = temp;

    return MTD_OK;
}

/*******************************************************************
  mtdGetTunitInterruptStatus
 
 *******************************************************************/
MTD_STATUS mtdGetTunitInterruptStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    OUT MTD_U32 *interruptStatus
)
{
    MTD_U16 regValue1,regValue2;
    MTD_U32 temp;

    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_INTERRUPT_STATUS1,&regValue1));
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_INTERRUPT_STATUS2,&regValue2));

    temp = (((MTD_U32)regValue2 << 16) & 0xFFFF0000)|((MTD_U32)regValue1 & 0x0000FFFF);
    *interruptStatus = temp;

    return MTD_OK;
}
