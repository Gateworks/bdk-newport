/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions, data structures and definitions for All
levels, interrupt functions, Real-time Status and I/O pin mode
configurations for the Marvell X7120/X6181/X6141 PHY.
********************************************************************/
#include "mydApiTypes.h"
#include "mydApiRegs.h"
#include "mydAPI.h"
#include "mydHwCntl.h"
#include "mydUtils.h"
#include "mydIntrIOConfig.h"
#include "mydAPIInternal.h"

/*******************************************************************
 MYD_STATUS mydGetIntrSrcStatus
     Poll all level interrupt status.
     See the mydIntrIOConfig.h for structure and bits definition.
*******************************************************************/
MYD_STATUS mydGetIntrSrcStatus
(
    IN MYD_DEV_PTR pDev,
    OUT MYD_PORT_INTR *portsIntrStatusArray
)
{
    MYD_OP_MODE opMode;
    MYD_BOOL portForceIntr;
    MYD_BOOL laneToCheck;
    MYD_U16 mdioPort, mdioPortIndex;
    MYD_U16 host_or_line;
    MYD_U16 intrPinControl;
    MYD_U16 portIntrStatus;
    MYD_U16 laneOffset, laneCount;
    MYD_U16 latchedStatusFlags1, latchedStatusFlags2;
    MYD_U16 currentStatusFlags1, currentStatusFlags2;

    /* clear portsIntrStatusArray structure */
    mydMemSet(portsIntrStatusArray, 0, pDev->portCount*sizeof(MYD_PORT_INTR));
    if (!pDev->devEnabled)
    {
        MYD_DBG_ERROR("mydGetIntrSrcStatus: device not initialized\n");
        return MYD_FAIL;
    }

    for (mdioPort = pDev->mdioPort; mdioPort < (pDev->mdioPort + pDev->portCount); mdioPort++)
    {
        mdioPortIndex = MYD_GET_PORT_IDX(pDev, mdioPort);
        ATTEMPT(mydGetGlobalInterruptCntl(pDev, mdioPort, &intrPinControl, &portForceIntr));
        portsIntrStatusArray[mdioPortIndex].forceInterrupt = portForceIntr;

        ATTEMPT(mydGetPerPortGlobalIntrStatus(pDev, mdioPort, &portIntrStatus));
        portsIntrStatusArray[mdioPortIndex].chainedIntr = (portIntrStatus & MYD_DAISY_CHAIN_INTR_BIT)!=0 ? MYD_TRUE : MYD_FALSE;
        portsIntrStatusArray[mdioPortIndex].gpioIntr = (portIntrStatus & MYD_GPIO_INTR_BIT)!=0 ? 1 : 0;
        portsIntrStatusArray[mdioPortIndex].rmFIFOIntr = (portIntrStatus & MYD_RM_FIFO_INTR_BIT)!=0 ? MYD_TRUE : MYD_FALSE;
        portsIntrStatusArray[mdioPortIndex].onChipProcIntr = (portIntrStatus & MYD_ON_CHIP_PROC_INTR_BIT)!=0 ? MYD_TRUE : MYD_FALSE;

        for (host_or_line = MYD_LINE_SIDE; host_or_line <= MYD_HOST_SIDE; host_or_line++)
        {
            for (laneOffset = 0; laneOffset < MYD_NUM_LANES; laneOffset++)
            {
                ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode));
                laneCount = opModeTable[opMode][MYD_OP_TABLE_LANE_COUNT];
                laneToCheck = MYD_FALSE;
                switch(laneCount)
                {
                    case MYD_1_LANE_MODE:
                        if (laneOffset < MYD_NUM_LANES)
                        {
                            laneToCheck = MYD_TRUE;
                        }
                        break;

                    case MYD_2_LANE_MODE:
                        if ((laneOffset == 0) || (laneOffset == 2))
                        {
                            laneToCheck = MYD_TRUE;
                        }
                        break;

                    case MYD_4_LANE_MODE:
                        if (laneOffset == 0)
                        {
                            laneToCheck = MYD_TRUE;
                        }
                        break;

                    case MYD_8_LANE_MODE:
                        if ((laneOffset == 0) && (pDev->portCount > 1))
                        {
                            if ((mdioPortIndex == 0) || (mdioPortIndex == 2))
                            {
                                laneToCheck = MYD_TRUE;
                            }
                        }
                        break;

                    default:
                        /* not possible, but if it happens won't check this lane */
                        break;
                }

                if (laneToCheck != MYD_TRUE)
                {
                    continue;
                }
                else
                {
                    ATTEMPT(mydGetPCSInterruptStatus(pDev, mdioPort, host_or_line, laneOffset, &latchedStatusFlags1, &currentStatusFlags1, &latchedStatusFlags2, &currentStatusFlags2));
                    if (host_or_line == MYD_HOST_SIDE)
                    {
                        portsIntrStatusArray[mdioPortIndex].hostIntr.srcGroup1[laneOffset] = latchedStatusFlags1;
                        portsIntrStatusArray[mdioPortIndex].hostIntr.srcGroup2[laneOffset] = latchedStatusFlags2;
                    }
                    else
                    {
                        portsIntrStatusArray[mdioPortIndex].lineIntr.srcGroup1[laneOffset] = latchedStatusFlags1;
                        portsIntrStatusArray[mdioPortIndex].lineIntr.srcGroup2[laneOffset] = latchedStatusFlags2;
                    }
                }
            }
        }
    }

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydGetEnabledIntrSrcISR
     Read all enabled interrupts.
     See the mydIntrIOConfig.h for structure and bits definition
*******************************************************************/
MYD_STATUS mydGetEnabledIntrSrcISR
(
    IN MYD_DEV_PTR pDev,
    OUT MYD_PORT_INTR *portsIntrSrcArray
)
{
    MYD_OP_MODE opMode;
    MYD_BOOL portForceIntr;
    MYD_BOOL laneToCheck;
    MYD_U16 mdioPort, mdioPortIndex;
    MYD_U16 intrPinControl;
    MYD_U16 portIntrStatus;
    MYD_U16 host_or_line;
    MYD_U16 indexStart;
    MYD_U16 indexEndEx;
    MYD_U16 laneOffset, laneCount;
    MYD_U16 intrEnableFlags1, intrEnableFlags2;
    MYD_U16 latchedStatusFlags1, latchedStatusFlags2;
    MYD_U16 currentStatusFlags1, currentStatusFlags2;

    /* clear portsIntrSrcArray structure */
    mydMemSet(portsIntrSrcArray, 0, pDev->portCount*sizeof(MYD_PORT_INTR));
    if (!pDev->devEnabled)
    {
        MYD_DBG_ERROR("mydGetEnabledIntrSrcISR: device not initialized\n");
        return MYD_FAIL;
    }

    for (mdioPort = pDev->mdioPort; mdioPort < (pDev->mdioPort + pDev->portCount); mdioPort++)
    {
        indexStart = MYD_LINE_SIDE;
        indexEndEx = MYD_HOST_SIDE+1;

        mdioPortIndex = MYD_GET_PORT_IDX(pDev, mdioPort);
        ATTEMPT(mydGetGlobalInterruptCntl(pDev, mdioPort, &intrPinControl, &portForceIntr));
        portsIntrSrcArray[mdioPortIndex].forceInterrupt = portForceIntr;

        ATTEMPT(mydGetPerPortGlobalIntrStatus(pDev, mdioPort, &portIntrStatus));
        portsIntrSrcArray[mdioPortIndex].chainedIntr = (portIntrStatus & MYD_DAISY_CHAIN_INTR_BIT)!=0 ? MYD_TRUE : MYD_FALSE;
        portsIntrSrcArray[mdioPortIndex].gpioIntr = (portIntrStatus & MYD_GPIO_INTR_BIT)!=0 ? 1 : 0;
        portsIntrSrcArray[mdioPortIndex].rmFIFOIntr = (portIntrStatus & MYD_RM_FIFO_INTR_BIT)!=0 ? MYD_TRUE : MYD_FALSE;
        portsIntrSrcArray[mdioPortIndex].onChipProcIntr = (portIntrStatus & MYD_ON_CHIP_PROC_INTR_BIT)!=0 ? MYD_TRUE : MYD_FALSE;

        if ((portIntrStatus & MYD_HOST_SIDE_INTR_BIT) == 0)
        {
            indexEndEx = MYD_HOST_SIDE;
        }
        if ((portIntrStatus & MYD_LINE_SIDE_INTR_BIT) == 0)
        {
            indexStart = MYD_HOST_SIDE;
        }
        for (host_or_line = indexStart; host_or_line < indexEndEx; host_or_line++)
        {
            for (laneOffset = 0; laneOffset < MYD_NUM_LANES; laneOffset++)
            {
                ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode));
                laneCount = opModeTable[opMode][MYD_OP_TABLE_LANE_COUNT];
                laneToCheck = MYD_FALSE;
                switch(laneCount)
                {
                    case MYD_1_LANE_MODE:
                        if (laneOffset < MYD_NUM_LANES)
                        {
                            laneToCheck = MYD_TRUE;
                        }
                        break;

                    case MYD_2_LANE_MODE:
                        if ((laneOffset == 0) || (laneOffset == 2))
                        {
                            laneToCheck = MYD_TRUE;
                        }
                        break;

                    case MYD_4_LANE_MODE:
                        if (laneOffset == 0)
                        {
                            laneToCheck = MYD_TRUE;
                        }
                        break;

                    case MYD_8_LANE_MODE:
                        if ((laneOffset == 0) && (pDev->portCount > 1))
                        {
                            if ((mdioPortIndex == 0) || (mdioPortIndex == 2))
                            {
                                laneToCheck = MYD_TRUE;
                            }
                        }
                        break;

                    default:
                        /* not possible, but if it happens won't check this lane */
                        break;
                }

                if (laneToCheck != MYD_TRUE)
                {
                    continue;
                }
                else
                {
                    ATTEMPT(mydGetPCSInterruptEnable(pDev, mdioPort, host_or_line, laneOffset, &intrEnableFlags1, &intrEnableFlags2));
                    ATTEMPT(mydGetPCSInterruptStatus(pDev, mdioPort, host_or_line, laneOffset, &latchedStatusFlags1, &currentStatusFlags1, &latchedStatusFlags2, &currentStatusFlags2));
                    if (host_or_line == MYD_HOST_SIDE)
                    {
                        portsIntrSrcArray[mdioPortIndex].hostIntr.srcGroup1[laneOffset] = intrEnableFlags1 & latchedStatusFlags1;
                        portsIntrSrcArray[mdioPortIndex].hostIntr.srcGroup2[laneOffset] = intrEnableFlags2 & latchedStatusFlags2;
                    }
                    else
                    {
                        portsIntrSrcArray[mdioPortIndex].lineIntr.srcGroup1[laneOffset] = intrEnableFlags1 & latchedStatusFlags1;
                        portsIntrSrcArray[mdioPortIndex].lineIntr.srcGroup2[laneOffset] = intrEnableFlags2 & latchedStatusFlags2;
                    }
                }
            }
        }
    }

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydSetGlobalInterruptCntl
     Set the interrupt pin control and/or force an interrupt
     on any port.
*******************************************************************/
MYD_STATUS mydSetGlobalInterruptCntl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 interruptPinControl, /* ignored unless this is the first port of multi-port device */
    IN MYD_BOOL forceInterrupt
)
{
    MYD_U16 temp=0;

    MYD_CHECK_DEV(pDev, mdioPort, 0);

    if (mdioPort == pDev->mdioPort)
    {
        temp |= (interruptPinControl<<1); /* on first port use what they've passed as the setting */
    }
    else
    {
        /* on other ports on multi-port PHY, read interruptPinControl and leave it as-is */
        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_GLOBAL_INTR_CNTL, 1, 2, &temp));
    }

    if (forceInterrupt)
    {
        temp |= 1;
    }
    else
    {
        temp &= 0;
    }

    /* now write the control */

    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_GLOBAL_INTR_CNTL, 0, 3, temp));

    return MYD_OK;

}

/*******************************************************************
 MYD_STATUS mydGetGlobalInterruptCntl
     Read the interrupt pin control and check if port interrupt is forced
*******************************************************************/
MYD_STATUS mydGetGlobalInterruptCntl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    OUT MYD_U16 *interruptPinControl,
    OUT MYD_BOOL *forceInterrupt
)
{
    MYD_U16 globalIntrCtrl;
    *interruptPinControl = 0;
    *forceInterrupt = 0;

    if (!pDev->devEnabled)
    {
        MYD_DBG_ERROR("mydGetGlobalInterruptCntl: device not initialized\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydIsPortValid(pDev, mdioPort));

    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PORT_REG, MYD_GLOBAL_INTR_CNTL, &globalIntrCtrl));
    globalIntrCtrl &= 0x07;
    *interruptPinControl = (globalIntrCtrl >> 1);
    *forceInterrupt = globalIntrCtrl & 0x01;

    return MYD_OK;
}

/*******************************************************************************
MYD_STATUS mydGetPerPortGlobalIntrStatus
    Get Per Port Global Interrupt Status
*******************************************************************************/
MYD_STATUS mydGetPerPortGlobalIntrStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    OUT MYD_U16 *perPortIntrStatus
)
{
    if (!pDev->devEnabled)
    {
        MYD_DBG_ERROR("mydGetPerPortGlobalIntrStatus: device not initialized\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydIsPortValid(pDev, mdioPort));

    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_CHIP_REG, MYD_GLOBAL_INTR_STAT, perPortIntrStatus));

    return MYD_OK;
}

/*******************************************************************************
MYD_STATUS mydSetGPIOInterruptEnable
    Set the Level 3 GPIO Interrupt Configurations (Enable/Disable)
*******************************************************************************/
MYD_STATUS mydSetGPIOInterruptEnable
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    IN MYD_U16 gpioIntrEnable
)
{
    MYD_U16 GPIOCtrlReg;
    MYD_U16 GPIOPort;
    MYD_PIN_MODE pinMode;
    MYD_U16 gpioDirection;

    ATTEMPT(mydGetPinMode(pDev, gpioPinId, &pinMode));
    if (pinMode != MYD_PIN_MODE_GPIO)
    {
        MYD_DBG_ERROR("mydSetGPIOInterruptEnable: The given Pin is not configured to the MYD_PIN_MODE_GPIO.\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydGetGPIOPinDirection(pDev, gpioPinId, &gpioDirection));
    if (gpioDirection != MYD_GPIO_INPUT_MODE)
    {
        MYD_DBG_ERROR("mydSetGPIOInterruptEnable: The GPIO interrupt only works when the Pin is set to MYD_GPIO_INPUT_MODE.\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydGPIOPinGetPortAndReg(pDev, gpioPinId, &GPIOPort, &GPIOCtrlReg));
    ATTEMPT(mydHwSetPhyRegField(pDev, GPIOPort, MYD_PORT_REG, GPIOCtrlReg, 12, 1, gpioIntrEnable));

    return MYD_OK;
}

/*******************************************************************************
MYD_STATUS mydGetGPIOInterruptEnable
    Get the Level 3 GPIO Interrupt Configurations (Enable/Disable)
*******************************************************************************/
MYD_STATUS mydGetGPIOInterruptEnable
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    OUT MYD_U16 *gpioIntrEnable
)
{
    MYD_U16 GPIOCtrlReg;
    MYD_U16 GPIOPort;

    ATTEMPT(mydGPIOPinGetPortAndReg(pDev, gpioPinId, &GPIOPort, &GPIOCtrlReg));
    ATTEMPT(mydHwGetPhyRegField(pDev, GPIOPort, MYD_PORT_REG, GPIOCtrlReg, 12, 1, gpioIntrEnable));

    return MYD_OK;
}

/*******************************************************************************
MYD_STATUS mydSetGPIOInterruptType
    Set the Level 3 GPIO Interrupt Type
*******************************************************************************/
MYD_STATUS mydSetGPIOInterruptType
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    IN MYD_U16 gpioIntrType
)
{
    MYD_U16 GPIOCtrlReg;
    MYD_U16 GPIOPort;
    MYD_PIN_MODE pinMode;
    MYD_U16 gpioDirection;

    ATTEMPT(mydGetPinMode(pDev, gpioPinId, &pinMode));
    if (pinMode != MYD_PIN_MODE_GPIO)
    {
        MYD_DBG_ERROR("mydSetGPIOInterruptType: The given Pin is not configured to the MYD_PIN_MODE_GPIO.\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydGetGPIOPinDirection(pDev, gpioPinId, &gpioDirection));
    if (gpioDirection != MYD_GPIO_INPUT_MODE)
    {
        MYD_DBG_ERROR("mydSetGPIOInterruptType: The GPIO interrupt only works when the Pin is set to MYD_GPIO_INPUT_MODE.\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydGPIOPinGetPortAndReg(pDev, gpioPinId, &GPIOPort, &GPIOCtrlReg));
    ATTEMPT(mydHwSetPhyRegField(pDev, GPIOPort, MYD_PORT_REG, GPIOCtrlReg, 8, 3, gpioIntrType));

    return MYD_OK;
}

/*******************************************************************************
MYD_STATUS mydGetGPIOInterruptType
    Get the Level 3 GPIO Interrupt Type
*******************************************************************************/
MYD_STATUS mydGetGPIOInterruptType
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    OUT MYD_U16 *gpioIntrType
)
{
    MYD_U16 GPIOCtrlReg;
    MYD_U16 GPIOPort;

    ATTEMPT(mydGPIOPinGetPortAndReg(pDev, gpioPinId, &GPIOPort, &GPIOCtrlReg));
    ATTEMPT(mydHwGetPhyRegField(pDev, GPIOPort, MYD_PORT_REG, GPIOCtrlReg, 8, 3, gpioIntrType));

    return MYD_OK;
}

/*******************************************************************************
MYD_STATUS mydGetGPIOInterruptStatus
    Get the Level 3 GPIO Interrupt Status
*******************************************************************************/
MYD_STATUS mydGetGPIOInterruptStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    OUT MYD_U16 *gpioIntrLatchedStatus,
    OUT MYD_U16 *gpioIntrCurrentStatus
)
{
    MYD_U16 GPIOCtrlReg;
    MYD_U16 GPIOPort;

    ATTEMPT(mydGPIOPinGetPortAndReg(pDev, gpioPinId, &GPIOPort, &GPIOCtrlReg));

    ATTEMPT(mydHwGetPhyRegField(pDev, GPIOPort, MYD_PORT_REG, GPIOCtrlReg, 11, 1, gpioIntrLatchedStatus));
    ATTEMPT(mydHwGetPhyRegField(pDev, GPIOPort, MYD_PORT_REG, GPIOCtrlReg, 11, 1, gpioIntrCurrentStatus));

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydSetPCSInterruptEnable
    Set interrupt enable for various modes
*******************************************************************************/
MYD_STATUS mydSetPCSInterruptEnable
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 intrEnableFlags1,
    IN MYD_U16 intrEnableFlags2 /* only valid for 40GBR/50GBR and 100GBR */
)
{
    MYD_SPEED speed;
    MYD_OP_MODE opMode;
    MYD_U16 modeType;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode));
    speed = opModeTable[opMode][MYD_OP_TABLE_SPEED];
    modeType = opModeTable[opMode][MYD_OP_TABLE_MODE_TYPE];

    /* Check if the lane offset is valid for the operational mode */
    ATTEMPT(mydCheckOpModeLaneOffset(pDev, mdioPort, laneOffset, opMode));

    if (modeType != MYD_PCS)
    {
        MYD_DBG_ERROR("mydSetPCSInterruptEnable: not in PCS mode\n");
        return MYD_FAIL;
    }

    switch (speed)
    {
        case MYD_1GB:
        case MYD_2P5GB:
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_PCS_1G_INTR_EN_LANE(laneOffset), intrEnableFlags1));
            break;

        case MYD_5GB:
        case MYD_10GB:
        case MYD_25GB:
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_PCS_25G_INTR_EN_LANE(laneOffset), intrEnableFlags1));
            break;

        case MYD_40GB:
        case MYD_50GB:
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_PCS_40G_INTR_EN1_LANE(laneOffset), intrEnableFlags1));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_PCS_40G_INTR_EN2_LANE(laneOffset), intrEnableFlags2));
            break;

        case MYD_100GB:
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_PCS_100G_INTR_EN1_LANE(laneOffset), intrEnableFlags1));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_PCS_100G_INTR_EN2_LANE(laneOffset), intrEnableFlags2));
            break;

        case MYD_200GB:
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_PCS_200G_INTR_EN, intrEnableFlags1));
            break;

        default:
            MYD_DBG_ERROR("mydSetPCSInterruptEnable: unsupported speed or speed unknown\n");
            return MYD_FAIL;
            break;
    }

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydGetPCSInterruptEnable
    Get interrupt enable for various modes
*******************************************************************************/
MYD_STATUS mydGetPCSInterruptEnable
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *intrEnableFlags1,
    OUT MYD_U16 *intrEnableFlags2 /* only valid for 40GBR/50GBR and 100GBR */
)
{
    MYD_SPEED speed;
    MYD_OP_MODE opMode;
    MYD_U16 modeType;

    /* in case it fails, init return value */
    *intrEnableFlags1 = *intrEnableFlags2 = 0;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode));
    speed = opModeTable[opMode][MYD_OP_TABLE_SPEED];
    modeType = opModeTable[opMode][MYD_OP_TABLE_MODE_TYPE];

    /* Check if the lane offset is valid for the operational mode */
    ATTEMPT(mydCheckOpModeLaneOffset(pDev, mdioPort, laneOffset, opMode));

    if (modeType != MYD_PCS)
    {
        MYD_DBG_ERROR("mydGetPCSInterruptEnable: not in PCS mode\n");
        return MYD_FAIL;
    }

    switch (speed)
    {
        case MYD_1GB:
        case MYD_2P5GB:
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_1G_INTR_EN_LANE(laneOffset), intrEnableFlags1));
            break;

        case MYD_5GB:
        case MYD_10GB:
        case MYD_25GB:
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_25G_INTR_EN_LANE(laneOffset), intrEnableFlags1));
            break;

        case MYD_40GB:
        case MYD_50GB:
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_40G_INTR_EN1_LANE(laneOffset), intrEnableFlags1));
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_40G_INTR_EN2_LANE(laneOffset), intrEnableFlags2));
            break;

        case MYD_100GB:
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_100G_INTR_EN1_LANE(laneOffset), intrEnableFlags1));
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_100G_INTR_EN2_LANE(laneOffset), intrEnableFlags2));
            break;

        case MYD_200GB:
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_200G_INTR_EN, intrEnableFlags1));
            break;

        default:
            MYD_DBG_ERROR("mydGetPCSInterruptEnable: unsupported speed or speed unknown\n");
            return MYD_FAIL;
            break;
    }

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydGetPCSInterruptStatus
    Get interrupt status for various modes
*******************************************************************************/
MYD_STATUS mydGetPCSInterruptStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *latchedStatusFlags1,
    OUT MYD_U16 *currentStatusFlags1,
    OUT MYD_U16 *latchedStatusFlags2, /* only valid for 40GBR/50GBR and 100GBR */
    OUT MYD_U16 *currentStatusFlags2  /* only valid for 40GBR/50GBR and 100GBR */
)
{
    MYD_SPEED speed;
    MYD_OP_MODE opMode;
    MYD_U16 modeType;

    /* in case it fails, init return value */
    *latchedStatusFlags1 = *latchedStatusFlags2 = 0;
    *currentStatusFlags1 = *currentStatusFlags2 = 0;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode));
    speed = opModeTable[opMode][MYD_OP_TABLE_SPEED];
    modeType = opModeTable[opMode][MYD_OP_TABLE_MODE_TYPE];

    /* Check if the lane offset is valid for the operational mode */
    ATTEMPT(mydCheckOpModeLaneOffset(pDev, mdioPort, laneOffset, opMode));

    if (modeType != MYD_PCS)
    {
        MYD_DBG_ERROR("mydGetPCSInterruptStatus: not in PCS mode\n");
        return MYD_FAIL;
    }

    switch (speed)
    {
        case MYD_1GB:
        case MYD_2P5GB:
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_1G_INTR_STAT_LANE(laneOffset), latchedStatusFlags1));
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_1G_INTR_STAT_LANE(laneOffset), currentStatusFlags1));
            break;

        case MYD_5GB:
        case MYD_10GB:
        case MYD_25GB:
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_25G_INTR_STAT_LANE(laneOffset), latchedStatusFlags1));
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_25G_INTR_STAT_LANE(laneOffset), currentStatusFlags1));
            break;

        case MYD_40GB:
        case MYD_50GB:
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_40G_INTR_STAT1_LANE(laneOffset), latchedStatusFlags1));
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_40G_INTR_STAT1_LANE(laneOffset), currentStatusFlags1));
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_40G_INTR_STAT2_LANE(laneOffset), latchedStatusFlags2));
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_40G_INTR_STAT2_LANE(laneOffset), currentStatusFlags2));
            break;

        case MYD_100GB:
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_100G_INTR_STAT1_LANE(laneOffset), latchedStatusFlags1));
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_100G_INTR_STAT1_LANE(laneOffset), currentStatusFlags1));
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_100G_INTR_STAT2_LANE(laneOffset), latchedStatusFlags2));
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_100G_INTR_STAT2_LANE(laneOffset), currentStatusFlags2));
            break;

        case MYD_200GB:
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_200G_INTR_STAT, latchedStatusFlags1));
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_200G_INTR_STAT, currentStatusFlags1));
            break;

        default:
            MYD_DBG_ERROR("mydGetPCSInterruptStatus: unsupported speed or speed unknown\n");
            return MYD_FAIL;
            break;
    }

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydGetPCSRealtimeStatus
    Get real-time status for various modes
*******************************************************************************/
MYD_STATUS mydGetPCSRealtimeStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *rtStatusFlags1,
    OUT MYD_U16 *rtStatusFlags2 /* only valid for 40/50GBR and 100GBR */
)
{
    MYD_U16 speed;
    MYD_OP_MODE opMode;
    MYD_U16 modeType;

    /* in case it fails, init return value */
    *rtStatusFlags1 = *rtStatusFlags2 = 0;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode));
    speed = opModeTable[opMode][MYD_OP_TABLE_SPEED];
    modeType = opModeTable[opMode][MYD_OP_TABLE_MODE_TYPE];

    /* Check if the lane offset is valid for the operational mode */
    ATTEMPT(mydCheckOpModeLaneOffset(pDev, mdioPort, laneOffset, opMode));

    if (modeType != MYD_PCS)
    {
        MYD_DBG_ERROR("mydGetPCSRealtimeStatus: not in PCS mode\n");
        return MYD_FAIL;
    }

    switch (speed)
    {
        case MYD_1GB:
        case MYD_2P5GB:
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_1G_RT_STAT_LANE(laneOffset), rtStatusFlags1));
            break;

        case MYD_5GB:
        case MYD_10GB:
        case MYD_25GB:
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_25G_RT_STAT_LANE(laneOffset), rtStatusFlags1));
            break;

        case MYD_40GB:
        case MYD_50GB:
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_40G_RT_STAT1_LANE(laneOffset), rtStatusFlags1));
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_40G_RT_STAT2_LANE(laneOffset), rtStatusFlags2));
            break;

        case MYD_100GB:
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_100G_RT_STAT1_LANE(laneOffset), rtStatusFlags1));
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_100G_RT_STAT2_LANE(laneOffset), rtStatusFlags2));
            break;

        case MYD_200GB:
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PCS_200G_RT_STAT, rtStatusFlags1));
            break;

        default:
            MYD_DBG_ERROR("mydGetPCSRealtimeStatus: Unknown or unsupported speed\n");
            return MYD_FAIL;
            break;
    }

    return MYD_OK;

}

/*******************************************************************************
 MYD_STATUS mydSetPinMode
    Configure multi-purpose pin to different modes
*******************************************************************************/
MYD_STATUS mydSetPinMode
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID pinId,
    IN MYD_PIN_MODE pinMode
)
{
    MYD_U16 mdioPort;
    MYD_U16 portInLoop;
    MYD_U16 modeVal = (MYD_U16)pinMode;
    MYD_U16 regVal;

    if (!pDev)
    {
        MYD_DBG_ERROR("mydSetPinMode: pDev is NULL\n");
        return MYD_FAIL;
    }

    if (!pDev->devEnabled)
    {
        MYD_DBG_ERROR("mydSetPinMode: device is not initialized\n");
        return MYD_FAIL;
    }

    mdioPort = pDev->mdioPort;
    ATTEMPT(mydCheckSupportedPinMode(pDev, pinId, pinMode));

    switch(pDev->deviceId)
    {
        case MYD_DEV_X7120:
            switch(pinId)
            {
                case MYD_PIN_GPIO1:
                    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_GPIO0_CTRL, 14, 2, modeVal));
                    break;

                case MYD_PIN_GPIO2:
                    if(modeVal == MYD_PIN_MODE_RCLK)
                    {
                        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort+1, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 7, 1, 0x1));
                    }
                    else
                    {
                        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort+1, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 7, 1, 0x0));
                        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort+1, MYD_PORT_REG, MYD_GPIO4_CTRL, 14, 2, modeVal));
                    }
                    break;

                case MYD_PIN_GPIO3:
                    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort+2, MYD_PORT_REG, MYD_GPIO0_CTRL, 14, 2, modeVal));
                    break;

                case MYD_PIN_GPIO4:
                    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort+3, MYD_PORT_REG, MYD_GPIO2_CTRL, 14, 2, modeVal));
                    break;

                case MYD_PIN_INTn:
                    if (modeVal == MYD_PIN_MODE_RCLK)
                    {
                        /* By Default the RCLK on INTn is coming from Port0 */
                        ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 3, 1, 1));
                    }
                    else
                    {
                        /* Disable RCLK mode by selecting MUX on all port */
                        for (portInLoop = pDev->mdioPort; portInLoop < (pDev->mdioPort + pDev->portCount); portInLoop++)
                        {
                            ATTEMPT(mydHwSetPhyRegField(pDev, portInLoop, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 3, 1, 0));
                        }
                    }
                    break;

                case MYD_PIN_CLK_OUT_SE1:
                    if(modeVal == MYD_PIN_MODE_RCLK)
                    {
                        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort+3, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 7, 1, 0x1));
                    }
                    else
                    {
                        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort+3, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 7, 1, 0x0));
                        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort+3, MYD_PORT_REG, MYD_GPIO4_CTRL, 14, 2, modeVal));
                    }
                    break;

                case MYD_PIN_CLK_OUT_SE2:
                    if(modeVal == MYD_PIN_MODE_RCLK)
                    {
                        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort+3, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 11, 1, 0x1));
                    }
                    else
                    {
                        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort+3, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 11, 1, 0x0));
                        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort+3, MYD_PORT_REG, MYD_GPIO5_CTRL, 14, 2, modeVal));
                    }
                    break;

                case MYD_PIN_CLK_OUT_DIFF_N:
                    if (pinMode != MYD_PIN_MODE_RCLK)
                    {
                        MYD_DBG_ERROR("mydSetPinMode: MYD_PIN_CLK_OUT_DIFF_N only supports RCLK mode.\n");
                        return MYD_FAIL;
                    }
                    else
                    {
                        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort+3, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL2, 3, 1, 0x1));
                    }
                    break;

                case MYD_PIN_CLK_OUT_DIFF_P:
                    if (pinMode != MYD_PIN_MODE_RCLK)
                    {
                        MYD_DBG_ERROR("mydSetPinMode: MYD_PIN_CLK_OUT_DIFF_P only supports RCLK mode.\n");
                        return MYD_FAIL;
                    }
                    else
                    {
                        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort+3, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL2, 11, 1, 0x1));
                    }
                    break;

                default:
                    MYD_DBG_ERROR("mydSetPinMode: invalid Pin selected: %d\n", pinId);
                    return MYD_FAIL;
                    break;
            }
            break;

        case MYD_DEV_X6141:
            switch(pinId)
            {
                case MYD_PIN_GPIO0:
                    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_GPIO0_CTRL, 14, 2, modeVal));
                    break;

                case MYD_PIN_GPIO1:
                    modeVal = (MYD_U16)pinMode - 1;
                    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_GPIO1_CTRL, 15, 1, modeVal));
                    break;

                case MYD_PIN_GPIO2:
                    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_GPIO2_CTRL, 14, 2, modeVal));
                    break;

                case MYD_PIN_GPIO3:
                    modeVal = (MYD_U16)pinMode - 1;
                    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_GPIO3_CTRL, 15, 1, modeVal));
                    break;

                case MYD_PIN_INTn:
                    if (modeVal == MYD_PIN_MODE_RCLK)
                    {
                        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 3, 1, 0x1));
                    }
                    else
                    {
                        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 3, 1, 0x0));
                    }
                    break;

                case MYD_PIN_CLK_OUT_SE1:
                    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, &regVal));
                    if(modeVal == MYD_PIN_MODE_RCLK)
                    {
                        ATTEMPT(mydHwSetRegFieldToWord(regVal, 0x0, 12, 1, &regVal));
                        ATTEMPT(mydHwSetRegFieldToWord(regVal, 0x1, 7, 1, &regVal));
                    }
                    else
                    {
                        ATTEMPT(mydHwSetRegFieldToWord(regVal, 0x1, 12, 1, &regVal));
                        ATTEMPT(mydHwSetRegFieldToWord(regVal, 0x0, 7, 1, &regVal));
                        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_GPIO4_CTRL, 14, 2, modeVal));
                    }
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, regVal));
                    break;

                case MYD_PIN_CLK_OUT_SE2:
                    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, &regVal));
                    if(modeVal == MYD_PIN_MODE_RCLK)
                    {
                        ATTEMPT(mydHwSetRegFieldToWord(regVal, 0x0, 13, 1, &regVal));
                        ATTEMPT(mydHwSetRegFieldToWord(regVal, 0x1, 11, 1, &regVal));
                    }
                    else
                    {
                        ATTEMPT(mydHwSetRegFieldToWord(regVal, 0x1, 13, 1, &regVal));
                        ATTEMPT(mydHwSetRegFieldToWord(regVal, 0x0, 11, 1, &regVal));
                        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_GPIO5_CTRL, 14, 2, modeVal));
                    }
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, regVal));
                    break;

                default:
                    MYD_DBG_ERROR("mydSetPinMode: Invalid Pin selected: %d\n", pinId);
                    return MYD_FAIL;
            }
            break;
        default:
            MYD_DBG_ERROR("mydSetPinMode: Unknown or Unsupported device model: 0x%x\n", pDev->deviceId);
            return MYD_FAIL;
    }

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydGetPinMode
    Read multi-purpose pin mode
*******************************************************************************/
MYD_STATUS mydGetPinMode
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID pinId,
    OUT MYD_PIN_MODE *pinMode
)
{
    MYD_U16 mdioPort;
    MYD_U16 modeVal;
    MYD_U16 p0MuxVal, p1MuxVal, p2MuxVal, p3MuxVal;

    if (!pDev)
    {
        MYD_DBG_ERROR("mydGetPinMode: pDev is NULL\n");
        return MYD_FAIL;
    }

    if (!pDev->devEnabled)
    {
        MYD_DBG_ERROR("mydGetPinMode: device is not initialized\n");
        return MYD_FAIL;
    }

    mdioPort = pDev->mdioPort;
    switch(pDev->deviceId)
    {
        case MYD_DEV_X7120:
            switch(pinId)
            {
                case MYD_PIN_GPIO1:
                    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_GPIO0_CTRL, 14, 2, &modeVal));
                    break;

                case MYD_PIN_GPIO2:
                    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort+1, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 7, 1, &p0MuxVal));
                    if (p0MuxVal == 0x1)
                    {
                        modeVal = (MYD_U16)MYD_PIN_MODE_RCLK;
                    }
                    else
                    {
                        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort+1, MYD_PORT_REG, MYD_GPIO4_CTRL, 14, 2, &modeVal));
                    }
                    break;

                case MYD_PIN_GPIO3:
                    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort+2, MYD_PORT_REG, MYD_GPIO0_CTRL, 14, 2, &modeVal));
                    break;

                case MYD_PIN_GPIO4:
                    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort+3, MYD_PORT_REG, MYD_GPIO2_CTRL, 14, 2, &modeVal));
                    break;

                case MYD_PIN_INTn:
                    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 3, 1, &p0MuxVal));

                    if (p0MuxVal == 0x1)
                    {
                        modeVal = (MYD_U16)MYD_PIN_MODE_RCLK;
                    }
                    else
                    {
                        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort+1, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 3, 1, &p1MuxVal));
                        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort+2, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 3, 1, &p2MuxVal));
                        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort+3, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 3, 1, &p3MuxVal));
                        if (p1MuxVal == 0x0 && p2MuxVal == 0x0 && p3MuxVal == 0x0)
                        {
                            modeVal = (MYD_U16)MYD_PIN_MODE_INTR;
                        }
                        else
                        {
                            MYD_DBG_ERROR("mydGetPinMode: Invalid Pin Mode read on INTn, please reset the mode of this Pin\n");
                            return MYD_FAIL;
                        }
                    }
                    break;

                case MYD_PIN_CLK_OUT_SE1:
                    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort+3, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 7, 1, &modeVal));
                    if(modeVal == 0x1)
                    {
                        modeVal = (MYD_U16)MYD_PIN_MODE_RCLK;
                    }
                    else
                    {
                        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort+3, MYD_PORT_REG, MYD_GPIO4_CTRL, 14, 2, &modeVal));
                    }
                    break;

                case MYD_PIN_CLK_OUT_SE2:
                    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort+3, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 11, 1, &modeVal));
                    if(modeVal == 0x1)
                    {
                        modeVal = (MYD_U16)MYD_PIN_MODE_RCLK;
                    }
                    else
                    {
                        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort+3, MYD_PORT_REG, MYD_GPIO5_CTRL, 14, 2, &modeVal));
                    }
                    break;

                case MYD_PIN_CLK_OUT_DIFF_N:
                    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort+3, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL2, 3, 1, &modeVal));
                    if (modeVal != 0x1)
                    {
                        MYD_DBG_ERROR("mydGetPinMode: Invalid Pin Mode read on CLK_DIFF_N, please reset the mode of this Pin\n");
                        return MYD_FAIL;
                    }
                    else
                    {
                        modeVal = (MYD_U16)MYD_PIN_MODE_RCLK;
                    }
                    break;

                case MYD_PIN_CLK_OUT_DIFF_P:
                    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort+3, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL2, 11, 1, &modeVal));
                    if (modeVal != 0x1)
                    {
                        MYD_DBG_ERROR("mydGetPinMode: Invalid Pin Mode read on CLK_DIFF_P, please reset the mode of this Pin\n");
                        return MYD_FAIL;
                    }
                    else
                    {
                        modeVal = (MYD_U16)MYD_PIN_MODE_RCLK;
                    }
                    break;

                default:
                    MYD_DBG_ERROR("mydGetPinMode: Invalid Pin selected: %d\n", pinId);
                    return MYD_FAIL;
                    break;
            }
            break;

        case MYD_DEV_X6141:
            switch(pinId)
            {
                case MYD_PIN_GPIO0:
                    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_GPIO0_CTRL, 14, 2, &modeVal));
                    break;

                case MYD_PIN_GPIO1:
                    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_GPIO1_CTRL, 15, 1, &modeVal));
                    modeVal += 1;
                    if (modeVal != MYD_PIN_MODE_GPIO || modeVal != MYD_PIN_MODE_LED)
                    {
                        MYD_DBG_ERROR("mydGetPinMode: Read invalid Pin mode %d on GPIO%d, please reset the mode of this Pin.\n", modeVal-1, pinId);
                        return MYD_FAIL;
                    }
                    break;

                case MYD_PIN_GPIO2:
                    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_GPIO2_CTRL, 14, 2, &modeVal));
                    break;

                case MYD_PIN_GPIO3:
                    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_GPIO3_CTRL, 15, 1, &modeVal));
                    modeVal += 1;
                    if (modeVal != MYD_PIN_MODE_GPIO || modeVal != MYD_PIN_MODE_LED)
                    {
                        MYD_DBG_ERROR("mydGetPinMode: Read invalid Pin mode %d on GPIO%d, please reset the mode of this Pin.\n", modeVal-1, pinId);
                        return MYD_FAIL;
                    }
                    break;

                case MYD_PIN_INTn:
                    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 3, 1, &modeVal));

                    if (modeVal == 0x1)
                    {
                        modeVal = (MYD_U16)MYD_PIN_MODE_RCLK;
                    }
                    else
                    {
                        modeVal = (MYD_U16)MYD_PIN_MODE_INTR;
                    }
                    break;

                case MYD_PIN_CLK_OUT_SE1:
                    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 7, 1, &modeVal));
                    if (modeVal == 0x1)
                    {
                        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 12, 1, &modeVal));
                        if (modeVal == 0x1)
                        {
                            MYD_DBG_ERROR("mydGetPinMode: Invalid Pin Mode read on CLK_OUT_SE1, please reset the mode of this Pin\n");
                            return MYD_FAIL;
                        }
                        else
                        {
                            modeVal = (MYD_U16)MYD_PIN_MODE_RCLK;
                        }
                    }
                    else
                    {
                        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_GPIO4_CTRL, 14, 2, &modeVal));
                    }
                    break;

                case MYD_PIN_CLK_OUT_SE2:
                    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 11, 1, &modeVal));
                    if (modeVal == 0x1)
                    {
                        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 13, 1, &modeVal));
                        if (modeVal == 0x1)
                        {
                            MYD_DBG_ERROR("mydGetPinMode: Invalid Pin Mode read on CLK_OUT_SE2, please reset the mode of this Pin\n");
                            return MYD_FAIL;
                        }
                        else
                        {
                            modeVal = (MYD_U16)MYD_PIN_MODE_RCLK;
                        }
                    }
                    else
                    {
                        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_GPIO5_CTRL, 14, 2, &modeVal));
                    }
                    break;

                default:
                    MYD_DBG_ERROR("mydGetPinMode: Invalid Pin selected: %d\n", pinId);
                    return MYD_FAIL;
            }
            break;
        default:
            MYD_DBG_ERROR("mydGetPinMode: Unknown or Unsupported device model: 0x%x\n", pDev->deviceId);
            return MYD_FAIL;
    }

    if (modeVal < MYD_PIN_MODE_NUMS)
    {
        *pinMode = (MYD_PIN_MODE)modeVal;
    }
    else
    {
        MYD_DBG_ERROR("mydGetPinMode: Read invalid Pin mode %d on GPIO%d, please reset the mode of this Pin.\n", modeVal, pinId);
        return MYD_FAIL;
    }

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydSetGPIOPinDirection
    Configure GPIO Pin Data Direction
*******************************************************************************/
MYD_STATUS mydSetGPIOPinDirection
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    IN MYD_U16 gpioPinDirection
)
{
    MYD_U16 GPIOCtrlReg;
    MYD_U16 GPIOPort;

    ATTEMPT(mydGPIOPinGetPortAndReg(pDev, gpioPinId, &GPIOPort, &GPIOCtrlReg));

    ATTEMPT(mydHwSetPhyRegField(pDev, GPIOPort, MYD_PORT_REG, GPIOCtrlReg, 13, 1, gpioPinDirection));

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydGetGPIOPinDirection
    Reads GPIO Pin Data Direction
*******************************************************************************/
MYD_STATUS mydGetGPIOPinDirection
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    OUT MYD_U16 *gpioPinDirection
)
{
    MYD_U16 GPIOCtrlReg;
    MYD_U16 GPIOPort;

    ATTEMPT(mydGPIOPinGetPortAndReg(pDev, gpioPinId, &GPIOPort, &GPIOCtrlReg));

    ATTEMPT(mydHwGetPhyRegField(pDev, GPIOPort, MYD_PORT_REG, GPIOCtrlReg, 13, 1, gpioPinDirection));

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydSetGPIOPinData
    Writes data to the given GPIO Pin
*******************************************************************************/
MYD_STATUS mydSetGPIOPinData
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    IN MYD_U16 gpioData         /* 0 or 1 */
)
{
    MYD_U16 GPIOCtrlReg;
    MYD_U16 GPIOPort;
    MYD_PIN_MODE pinMode;

    ATTEMPT(mydGetPinMode(pDev, gpioPinId, &pinMode));
    if (pinMode != MYD_PIN_MODE_GPIO)
    {
        MYD_DBG_ERROR("mydSetGPIOPinData: The given Pin is not configured to the MYD_PIN_MODE_GPIO.\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydGPIOPinGetPortAndReg(pDev, gpioPinId, &GPIOPort, &GPIOCtrlReg));

    ATTEMPT(mydHwSetPhyRegField(pDev, GPIOPort, MYD_PORT_REG, GPIOCtrlReg, 7, 1, gpioData));

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydGetGPIOPinData
    Reads data from the given GPIO Pin
*******************************************************************************/
MYD_STATUS mydGetGPIOPinData
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    OUT MYD_U16 *gpioData
)
{
    MYD_U16 GPIOCtrlReg;
    MYD_U16 GPIOPort;
    MYD_PIN_MODE pinMode;

    ATTEMPT(mydGetPinMode(pDev, gpioPinId, &pinMode));
    if (pinMode != MYD_PIN_MODE_GPIO)
    {
        MYD_DBG_ERROR("mydGetGPIOPinData: The given Pin is not configured to the MYD_PIN_MODE_GPIO.\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydGPIOPinGetPortAndReg(pDev, gpioPinId, &GPIOPort, &GPIOCtrlReg));

    ATTEMPT(mydHwGetPhyRegField(pDev, GPIOPort, MYD_PORT_REG, GPIOCtrlReg, 7, 1, gpioData));

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydConfigLEDPin
    Configure LED activities
*******************************************************************************/
MYD_STATUS mydConfigLEDPin
(
    IN MYD_DEV_PTR pDev,
    IN MYD_LED_ID ledId,
    IN MYD_LED_CTRL ledCtrl,
    IN MYD_LED_TIMER_CONFIG ledTimerConfig
)
{
    MYD_U8 LEDMixOffset;
    MYD_U16 LEDPort, LEDCtrlReg, LEDMixReg;
    MYD_U16 LEDTimerReg = MYD_LED_TIMER_CTRL;
    MYD_U16 regVal;

    if (!pDev)
    {
        MYD_DBG_ERROR("mydConfigLEDPin: pDev is NULL\n");
        return MYD_FAIL;
    }

    if (!pDev->devEnabled)
    {
        MYD_DBG_ERROR("mydConfigLEDPin: device is not initialized\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydLEDConfigInputCheck(ledId, ledCtrl, ledTimerConfig));

    if (pDev->deviceId == MYD_DEV_X7120)
    {
        switch(ledId)
        {
            case MYD_LED0:
                LEDPort = pDev->mdioPort;
                LEDCtrlReg = MYD_LED0_CTRL_STATUS;
                LEDMixReg = MYD_LED_MIXING_CTRL1;
                LEDMixOffset = 0;
                break;
            case MYD_LED1:
                LEDPort = pDev->mdioPort + 1;
                LEDCtrlReg = MYD_LED4_CTRL_STATUS;
                LEDMixReg = MYD_LED_MIXING_CTRL2;
                LEDMixOffset = 0;
                break;
            case MYD_LED2:
                LEDPort = pDev->mdioPort + 2;
                LEDCtrlReg = MYD_LED0_CTRL_STATUS;
                LEDMixReg = MYD_LED_MIXING_CTRL1;
                LEDMixOffset = 0;
                break;
            case MYD_LED3:
                LEDPort = pDev->mdioPort + 3;
                LEDCtrlReg = MYD_LED2_CTRL_STATUS;
                LEDMixReg = MYD_LED_MIXING_CTRL1;
                LEDMixOffset = 8;
                break;
            case MYD_LED4:
                LEDPort = pDev->mdioPort + 3;
                LEDCtrlReg = MYD_LED4_CTRL_STATUS;
                LEDMixReg = MYD_LED_MIXING_CTRL2;
                LEDMixOffset = 0;
                break;
            case MYD_LED5:
                LEDPort = pDev->mdioPort + 3;
                LEDCtrlReg = MYD_LED5_CTRL_STATUS;
                LEDMixReg = MYD_LED_MIXING_CTRL2;
                LEDMixOffset = 4;
                break;
            default:
                MYD_DBG_ERROR("mydConfigLEDPin: Invalid LED ID:%d selected on device model: 0x%x\n", ledId, pDev->deviceId);
                return MYD_FAIL;
        }
    }
    else if (pDev->deviceId == MYD_DEV_X6141)
    {
        LEDPort = pDev->mdioPort;
        switch(ledId)
        {
            case MYD_LED0:
                LEDCtrlReg = MYD_LED0_CTRL_STATUS;
                LEDMixReg = MYD_LED_MIXING_CTRL1;
                LEDMixOffset = 0;
                break;
            case MYD_LED1:
                LEDCtrlReg = MYD_LED1_CTRL_STATUS;
                LEDMixReg = MYD_LED_MIXING_CTRL1;
                LEDMixOffset = 4;
                break;
            case MYD_LED2:
                LEDCtrlReg = MYD_LED2_CTRL_STATUS;
                LEDMixReg = MYD_LED_MIXING_CTRL1;
                LEDMixOffset = 8;
                break;
            case MYD_LED3:
                LEDCtrlReg = MYD_LED3_CTRL_STATUS;
                LEDMixReg = MYD_LED_MIXING_CTRL1;
                LEDMixOffset = 12;
                break;
            case MYD_LED4:
                LEDCtrlReg = MYD_LED4_CTRL_STATUS;
                LEDMixReg = MYD_LED_MIXING_CTRL2;
                LEDMixOffset = 0;
                break;
            case MYD_LED5:
                LEDCtrlReg = MYD_LED5_CTRL_STATUS;
                LEDMixReg = MYD_LED_MIXING_CTRL2;
                LEDMixOffset = 4;
                break;
            default:
                MYD_DBG_ERROR("mydConfigLEDPin: Invalid LED ID:%d selected on device model: 0x%x\n", ledId, pDev->deviceId);
                return MYD_FAIL;
        }
    }
    else
    {
        MYD_DBG_ERROR("mydConfigLEDPin: Unknown or unsupported device: 0x%x.\n", pDev->deviceId);
        return MYD_FAIL;
    }

    /* LED Control */
    ATTEMPT(mydHwXmdioRead(pDev, LEDPort, MYD_PORT_REG, LEDCtrlReg, &regVal));
    if (ledCtrl.laneSelect != MYD_LED_CONFIG_UNCHANGED)
    {
        ATTEMPT(mydHwSetRegFieldToWord(regVal, ledCtrl.laneSelect, 14, 2, &regVal));
    }

    if (ledCtrl.interfaceSelect != MYD_LED_CONFIG_UNCHANGED)
    {
        ATTEMPT(mydHwSetRegFieldToWord(regVal, (ledCtrl.interfaceSelect==MYD_LINE_SIDE)?0:1, 12, 1, &regVal));
    }

    if (ledCtrl.blinkActivity != MYD_LED_CONFIG_UNCHANGED)
    {
        ATTEMPT(mydHwSetRegFieldToWord(regVal, ledCtrl.blinkActivity, 8, 4, &regVal));
    }

    if (ledCtrl.solidActivity != MYD_LED_CONFIG_UNCHANGED)
    {
        ATTEMPT(mydHwSetRegFieldToWord(regVal, ledCtrl.solidActivity, 4, 4, &regVal));
    }

    if (ledCtrl.blinkRateSelect != MYD_LED_CONFIG_UNCHANGED)
    {
        ATTEMPT(mydHwSetRegFieldToWord(regVal, (ledCtrl.blinkRateSelect==1)?0:1, 2, 1, &regVal));
    }

    if (ledCtrl.polarity != MYD_LED_CONFIG_UNCHANGED)
    {
        ATTEMPT(mydHwSetRegFieldToWord(regVal, ledCtrl.polarity, 0, 2, &regVal));
    }
    ATTEMPT(mydHwXmdioWrite(pDev, LEDPort, MYD_PORT_REG, LEDCtrlReg, regVal));

    /* LED Timer Config */
    ATTEMPT(mydHwXmdioRead(pDev, LEDPort, MYD_PORT_REG, LEDTimerReg, &regVal));
    if (ledTimerConfig.pulseStretchDuration != MYD_LED_CONFIG_UNCHANGED)
    {
        ATTEMPT(mydHwSetRegFieldToWord(regVal, ledTimerConfig.pulseStretchDuration, 12, 3, &regVal));
    }

    if (ledTimerConfig.blinkRate2 != MYD_LED_CONFIG_UNCHANGED)
    {
        ATTEMPT(mydHwSetRegFieldToWord(regVal, ledTimerConfig.blinkRate2, 8, 3, &regVal));
    }

    if (ledTimerConfig.blinkRate1 != MYD_LED_CONFIG_UNCHANGED)
    {
        ATTEMPT(mydHwSetRegFieldToWord(regVal, ledTimerConfig.blinkRate1, 4, 3, &regVal));
    }
    ATTEMPT(mydHwXmdioWrite(pDev, LEDPort, MYD_PORT_REG, LEDTimerReg, regVal));

    /* LED Mix Rate Config */
    if (ledCtrl.mixRateLevel != MYD_LED_CONFIG_UNCHANGED)
    {
        ATTEMPT(mydHwSetPhyRegField(pDev, LEDPort, MYD_PORT_REG, LEDMixReg, LEDMixOffset, 2, ledCtrl.mixRateLevel));
    }

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydConfigRClkPin
    Configure Recovered Clock settings on the given Pin.
    Including Port, Interface and MUX Option select
*******************************************************************************/
MYD_STATUS mydConfigRClkPin
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID rClkPinId,
    IN MYD_U16 portSelect,
    IN MYD_U16 interfaceSelect,
    IN MYD_U16 muxOptionSelect
)
{
    MYD_PIN_MODE pinMode;

    if (!pDev)
    {
        MYD_DBG_ERROR("mydConfigRClkPin: pDev is NULL\n");
        return MYD_FAIL;
    }

    if (!pDev->devEnabled)
    {
        MYD_DBG_ERROR("mydConfigRClkPin: device is not initialized\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydRClkConfigInputCheck(pDev, rClkPinId, portSelect, interfaceSelect, muxOptionSelect));

    ATTEMPT(mydGetPinMode(pDev, rClkPinId, &pinMode));
    if (pinMode != MYD_PIN_MODE_RCLK)
    {
        MYD_DBG_ERROR("mydConfigRClkPin: The given Pin:%d is not in the MYD_PIN_MODE_RCLK mode.\n");
        return MYD_FAIL;
    }

    /* Select RCLK Source */
    ATTEMPT(mydRClkSelectSource(pDev, rClkPinId, portSelect, interfaceSelect, muxOptionSelect));

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydConfigRClkMux
    Configure Recovered Clock MUX Options on all ports and interfaces.
    Option includes source selection, lane selection, divide ratio and divider config
*******************************************************************************/
MYD_STATUS mydConfigRClkMux
(
    IN MYD_DEV_PTR pDev,
    IN MYD_RCLK_MUX *pRClkMux
)
{
    MYD_U16 portInLoop, portIndex, interfaceIndex, muxOptionIdx;
    MYD_U16 rcvClkCtrlReg;
    MYD_U16 regVal;
    MYD_RCLK_MUX_OPTION *rClkMuxOptionPtr;

    if (!pDev)
    {
        MYD_DBG_ERROR("mydConfigRClkMux: pDev is NULL\n");
        return MYD_FAIL;
    }

    if (!pDev->devEnabled)
    {
        MYD_DBG_ERROR("mydConfigRClkMux: device is not initialized\n");
        return MYD_FAIL;
    }

    /* Set Top-Level MUX */
    for (portInLoop = pDev->mdioPort; portInLoop < (pDev->mdioPort + pDev->portCount); portInLoop++)
    {
        ATTEMPT(mydHwXmdioRead(pDev, portInLoop, MYD_PORT_REG, MYD_PORT_RCVCLK_SRC_MUX, &regVal));
        ATTEMPT(mydHwSetRegFieldToWord(regVal, 0x0, 0, 2, &regVal));
        ATTEMPT(mydHwSetRegFieldToWord(regVal, 0x1, 2, 2, &regVal));
        ATTEMPT(mydHwSetRegFieldToWord(regVal, 0x0, 4, 2, &regVal));
        ATTEMPT(mydHwSetRegFieldToWord(regVal, 0x1, 6, 2, &regVal));
        ATTEMPT(mydHwXmdioWrite(pDev, portInLoop, MYD_PORT_REG, MYD_PORT_RCVCLK_SRC_MUX, regVal));
    }

    if (pDev->deviceId == MYD_DEV_X7120)
    {
        for (portIndex = 0; portIndex < pDev->portCount; portIndex++)
        {
            portInLoop = pDev->mdioPort + portIndex;
            for (interfaceIndex = MYD_HOST_MODE_IDX; interfaceIndex <= MYD_LINE_MODE_IDX; interfaceIndex++)
            {
                ATTEMPT(mydRClkMuxInputCheck(portIndex, interfaceIndex, 1, pRClkMux->x7120.mux1[portIndex][interfaceIndex]));
                ATTEMPT(mydRClkMuxInputCheck(portIndex, interfaceIndex, 2, pRClkMux->x7120.mux2[portIndex][interfaceIndex]));

                for (muxOptionIdx = 1; muxOptionIdx <= 2; muxOptionIdx++)
                {
                    if (muxOptionIdx == 1) /* Option 1 */
                    {
                        rcvClkCtrlReg = (interfaceIndex==MYD_HOST_MODE_IDX) ? MYD_HOST_RCVCLK_CTRL1 : MYD_LINE_RCVCLK_CTRL1;
                        rClkMuxOptionPtr = &(pRClkMux->x7120.mux1[portIndex][interfaceIndex]);
                    }
                    else /* Option 2 */
                    {
                        rcvClkCtrlReg = (interfaceIndex==MYD_HOST_MODE_IDX) ? MYD_HOST_RCVCLK_CTRL2 : MYD_LINE_RCVCLK_CTRL2;
                        rClkMuxOptionPtr = &(pRClkMux->x7120.mux2[portIndex][interfaceIndex]);
                    }

                    ATTEMPT(mydHwXmdioRead(pDev, portInLoop, MYD_PORT_REG, rcvClkCtrlReg, &regVal));
                    /* Source Clock MUX */
                    ATTEMPT(mydHwSetRegFieldToWord(regVal, rClkMuxOptionPtr->srcClockSelect, 0, 1, &regVal));
                    /* Lane MUX */
                    ATTEMPT(mydHwSetRegFieldToWord(regVal, rClkMuxOptionPtr->laneSelect, 1, 2, &regVal));
                    /* Divide Ratio MUX */
                    ATTEMPT(mydHwSetRegFieldToWord(regVal, rClkMuxOptionPtr->divideRatio, 8, 8, &regVal));
                    /* Divider Enable MUX */
                    if (rClkMuxOptionPtr->dividerConfig == 0x0)
                    {
                        ATTEMPT(mydHwSetRegFieldToWord(regVal, 0x0, 4, 2, &regVal));
                    }
                    else if (rClkMuxOptionPtr->dividerConfig == 0x1)
                    {
                        ATTEMPT(mydHwSetRegFieldToWord(regVal, 0x0, 4, 1, &regVal));
                        ATTEMPT(mydHwSetRegFieldToWord(regVal, 0x1, 5, 1, &regVal));
                    }
                    else if (rClkMuxOptionPtr->dividerConfig == 0x2)
                    {
                        ATTEMPT(mydHwSetRegFieldToWord(regVal, 0x0, 5, 1, &regVal));
                        ATTEMPT(mydHwSetRegFieldToWord(regVal, 0x1, 4, 1, &regVal));
                    }
                    ATTEMPT(mydHwXmdioWrite(pDev, portInLoop, MYD_PORT_REG, rcvClkCtrlReg, regVal));
                }
            }
        }
    }
    else if (pDev->deviceId == MYD_DEV_X6141)
    {
        for (interfaceIndex = MYD_HOST_MODE_IDX; interfaceIndex <= MYD_LINE_MODE_IDX; interfaceIndex++)
        {
            ATTEMPT(mydRClkMuxInputCheck(0, interfaceIndex, 1, pRClkMux->x6141.mux1[interfaceIndex]));
            ATTEMPT(mydRClkMuxInputCheck(0, interfaceIndex, 2, pRClkMux->x6141.mux2[interfaceIndex]));

            for (muxOptionIdx = 1; muxOptionIdx <= 2; muxOptionIdx++)
            {
                if (muxOptionIdx == 1) /* Option 1 */
                {
                    rcvClkCtrlReg = (interfaceIndex==MYD_HOST_MODE_IDX) ? MYD_HOST_RCVCLK_CTRL1 : MYD_LINE_RCVCLK_CTRL1;
                    rClkMuxOptionPtr = &(pRClkMux->x6141.mux1[interfaceIndex]);
                }
                else /* Option 2 */
                {
                    rcvClkCtrlReg = (interfaceIndex==MYD_HOST_MODE_IDX) ? MYD_HOST_RCVCLK_CTRL2 : MYD_LINE_RCVCLK_CTRL2;
                    rClkMuxOptionPtr = &(pRClkMux->x6141.mux2[interfaceIndex]);
                }

                ATTEMPT(mydHwXmdioRead(pDev, pDev->mdioPort, MYD_PORT_REG, rcvClkCtrlReg, &regVal));
                /* Source Clock MUX */
                ATTEMPT(mydHwSetRegFieldToWord(regVal, rClkMuxOptionPtr->srcClockSelect, 0, 1, &regVal));
                /* Lane MUX */
                ATTEMPT(mydHwSetRegFieldToWord(regVal, rClkMuxOptionPtr->laneSelect, 1, 2, &regVal));
                /* Divide Ratio MUX */
                ATTEMPT(mydHwSetRegFieldToWord(regVal, rClkMuxOptionPtr->divideRatio, 8, 8, &regVal));
                /* Divider Enable MUX */
                if (rClkMuxOptionPtr->dividerConfig == 0x0)
                {
                    ATTEMPT(mydHwSetRegFieldToWord(regVal, 0x0, 4, 2, &regVal));
                }
                else if (rClkMuxOptionPtr->dividerConfig == 0x1)
                {
                    ATTEMPT(mydHwSetRegFieldToWord(regVal, 0x0, 4, 1, &regVal));
                    ATTEMPT(mydHwSetRegFieldToWord(regVal, 0x1, 5, 1, &regVal));
                }
                else if (rClkMuxOptionPtr->dividerConfig == 0x2)
                {
                    ATTEMPT(mydHwSetRegFieldToWord(regVal, 0x0, 5, 1, &regVal));
                    ATTEMPT(mydHwSetRegFieldToWord(regVal, 0x1, 4, 1, &regVal));
                }
                ATTEMPT(mydHwXmdioWrite(pDev, pDev->mdioPort, MYD_PORT_REG, rcvClkCtrlReg, regVal));
            }
        }
    }
    else
    {
        MYD_DBG_ERROR("mydConfigRClkMux: Unknown or unsupported device: 0x%x.\n", pDev->deviceId);
        return MYD_FAIL;
    }

    return MYD_OK;
}
