/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/**********************************************************************
This file contains function prototypes for mode selections, interrupts
and real-time controls, configurations and status for the Marvell
X7120/X6181/X6141 PHYs.
**********************************************************************/
#include "mydApiTypes.h"
#include "mydApiRegs.h"
#include "mydUtils.h"
#include "mydHwCntl.h"
#include "mydDiagnostics.h"
#include "mydAPI.h"
#include "mydIntrIOConfig.h"
#include "mydAPIInternal.h"
#include "mydInitialization.h"

/*******************************************************************************
 MYD_VOID mydGetAPIVersion
*******************************************************************************/
MYD_VOID mydGetAPIVersion
(
    OUT MYD_U8 *major,
    OUT MYD_U8 *minor,
    OUT MYD_U8 *buildID
)
{
    *major = MYD_API_MAJOR_VERSION;
    *minor = MYD_API_MINOR_VERSION;
    *buildID = MYD_API_BUILD_ID;

   return;
}

/*******************************************************************************
 MYD_STATUS mydSetModeSelection
*******************************************************************************/
MYD_STATUS mydSetModeSelection
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16     mdioPort,
    IN MYD_U16     laneOffset,
    IN MYD_OP_MODE hostMode,
    IN MYD_OP_MODE lineMode,
    IN MYD_U32     modeOption,
    OUT MYD_U16    *result
)
{
    MYD_U16 lineSpeed, hostSpeed;
    MYD_U16 mdioPortIndex = MYD_GET_PORT_IDX(pDev, mdioPort);
    MYD_U16 hostLaneCount, lineLaneCount, maxLaneUsed;
    *result = MYD_STATUS_MODE_GENERAL_ERROR;

    MYD_CHECK_DEV(pDev, mdioPort, laneOffset);

    if (mydIsOpModeValid(pDev, hostMode, lineMode) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydSetModeSelection: incorrect OP mode hostMode:%u; lineMode:%u\n", 
                       hostMode, lineMode);
        *result = MYD_STATUS_MODE_HOST_LINE_ERROR;
        return MYD_FAIL;
    }

    if ((mydCheckOpModeLaneOffset(pDev, mdioPort, laneOffset, hostMode) == MYD_FAIL) ||
        (mydCheckOpModeLaneOffset(pDev, mdioPort, laneOffset, lineMode) == MYD_FAIL))
    {
        MYD_DBG_ERROR("mydSetModeSelection: lane offset is invalid for OP mode hostMode:%u; lineMode:%u\n", 
                       hostMode, lineMode);
        *result = MYD_STATUS_MODE_HOST_LINE_ERROR;
        return MYD_FAIL;
    }

    hostSpeed = opModeTable[hostMode][MYD_OP_TABLE_SPEED];
    lineSpeed = opModeTable[lineMode][MYD_OP_TABLE_SPEED];

    hostLaneCount = opModeTable[hostMode][MYD_OP_TABLE_LANE_COUNT];
    lineLaneCount = opModeTable[lineMode][MYD_OP_TABLE_LANE_COUNT];
    maxLaneUsed = (hostLaneCount >= lineLaneCount) ? hostLaneCount:lineLaneCount;

    /* check lane offset is valid */
    if (laneOffset >= MYD_NUM_LANES)
    {
        MYD_DBG_ERROR("mydSetModeSelection: incorrect lane selection: %u\n", laneOffset);
        *result = MYD_STATUS_MODE_GENERAL_ERROR;
        return MYD_FAIL;
    }

    /* Calls mydCheckNeedReConfig if MYD_MODE_FORCE_RECONFIG is not set. This call will check if
       a previously set mode has a different lane count on the same port and lane. */
    if (!(modeOption & MYD_MODE_FORCE_RECONFIG))
    {
        if ((mydCheckNeedReConfig(pDev, mdioPort, MYD_HOST_SIDE, laneOffset, hostMode) == MYD_FAIL) ||
            (mydCheckNeedReConfig(pDev, mdioPort, MYD_LINE_SIDE, laneOffset, lineMode) == MYD_FAIL))
        {
            MYD_DBG_ERROR("mydSetModeSelection: MYD_MODE_FORCE_RECONFIG option required\n");
            *result = MYD_STATUS_MODE_GROUP_ERROR;
            return MYD_FAIL;
        }
    }

    if (maxLaneUsed == MYD_8_LANE_MODE)
    {
        /* initial config and mode structures */
        mydMemSet(&pDev->hostConfig[mdioPortIndex], 0, (sizeof(MYD_MODE_CONFIG)*MYD_NUM_LANES));
        mydMemSet(&pDev->lineConfig[mdioPortIndex], 0, (sizeof(MYD_MODE_CONFIG)*MYD_NUM_LANES));

        mydMemSet(&pDev->hostConfig[mdioPortIndex+1], 0, (sizeof(MYD_MODE_CONFIG)*MYD_NUM_LANES));
        mydMemSet(&pDev->lineConfig[mdioPortIndex+1], 0, (sizeof(MYD_MODE_CONFIG)*MYD_NUM_LANES));
    }
    else
    {
        /* initial config and mode structures */
        mydMemSet(&pDev->hostConfig[mdioPortIndex][laneOffset], 0, (sizeof(MYD_MODE_CONFIG)*maxLaneUsed));
        mydMemSet(&pDev->lineConfig[mdioPortIndex][laneOffset], 0, (sizeof(MYD_MODE_CONFIG)*maxLaneUsed));
    }

    if ((hostLaneCount > MYD_1_LANE_MODE) || (lineLaneCount > MYD_1_LANE_MODE))
    {
        pDev->devInfo[mdioPortIndex] |= MYD_LANES_GROUPED;
    }

    if (mydCheckMixedOpModeSupport(pDev, mdioPort, laneOffset, hostMode, lineMode) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydSetModeSelection: Mixed OP mode is not supported on the device\n");
        *result = MYD_STATUS_MODE_HOST_LINE_ERROR;
        return MYD_FAIL;
    }

    if ((hostMode == MYD_R400U) && (lineMode == MYD_R400U))
    {
        if (mydSetRepeater400U(pDev, mdioPort, laneOffset, modeOption) == MYD_FAIL)
        {
            *result = MYD_STATUS_MODE_GENERAL_ERROR;
            return MYD_FAIL;
        }

        *result = MYD_STATUS_MODE_SUCCESS;
        return MYD_OK;
    }

    if ((hostMode == MYD_R200L) && (lineMode == MYD_R200L))
    {
        if (mydSetRepeater200L(pDev, mdioPort, laneOffset, modeOption) == MYD_FAIL)
        {
            *result = MYD_STATUS_MODE_GENERAL_ERROR;
            return MYD_FAIL;
        }

        *result = MYD_STATUS_MODE_SUCCESS;
        return MYD_OK;
    }

    pDev->hostConfig[mdioPortIndex][laneOffset].opMode = hostMode;
    pDev->lineConfig[mdioPortIndex][laneOffset].opMode = lineMode;

    /* ATTEMPT(mydExtendDeviceAutoNegTimer(pDev));  */ /* not require to extend AN timer */

    if (mydSetFixedMode(pDev, mdioPort, MYD_LINE_SIDE, laneOffset, modeOption, lineMode) == MYD_FAIL)
    {
        pDev->lineConfig[mdioPortIndex][laneOffset].opMode = MYD_OP_MODE_UNKNOWN;
        pDev->hostConfig[mdioPortIndex][laneOffset].opMode = MYD_OP_MODE_UNKNOWN;

        MYD_DBG_ERROR("mydSetModeSelection: mydSetFixedMode line side failed\n");
        *result = MYD_STATUS_MODE_GENERAL_ERROR;
        return MYD_FAIL;
    }

    if (hostMode != MYD_OP_MODE_UNKNOWN)
    {
        if (mydSetFixedMode(pDev, mdioPort, MYD_HOST_SIDE, laneOffset, modeOption, hostMode) == MYD_FAIL)
        {
            pDev->lineConfig[mdioPortIndex][laneOffset].opMode = MYD_OP_MODE_UNKNOWN;
            pDev->hostConfig[mdioPortIndex][laneOffset].opMode = MYD_OP_MODE_UNKNOWN;

            MYD_DBG_ERROR("mydSetModeSelection: mydSetFixedMode host side failed\n");
            *result = MYD_STATUS_MODE_GENERAL_ERROR;
            return MYD_FAIL;
        }
    }

    if ((hostSpeed != lineSpeed) || (hostLaneCount != lineLaneCount))
    {
        pDev->devInfo[mdioPortIndex]  |= MYD_GEARBOX_MODE;
    }
    else
    {
        pDev->devInfo[mdioPortIndex]  &= ~MYD_GEARBOX_MODE;
    }

    *result = MYD_STATUS_MODE_SUCCESS;

    return MYD_OK;
}


/*******************************************************************************
 MYD_STATUS mydGetOpMode
    Access the operating mode from the device structure
*******************************************************************************/
MYD_STATUS mydGetOpMode
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,   
    OUT MYD_OP_MODE *opMode
)
{
    MYD_U16 mdioPortIndex = MYD_GET_PORT_IDX(pDev, mdioPort);

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    /* get the operating mode for this lane */
    if (host_or_line == MYD_HOST_SIDE)
    {
        *opMode = pDev->hostConfig[mdioPortIndex][laneOffset].opMode;
    }
    else
    {
        *opMode = pDev->lineConfig[mdioPortIndex][laneOffset].opMode;        
    }
    
    return MYD_OK;
}

#define MAX_SWRESET_WAIT 1000
/*******************************************************************************
 MYD_STATUS mydAutoNegControl
    Enable/disable and restart auto-neg
*******************************************************************************/
MYD_STATUS mydAutoNegControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,   
    IN MYD_U16 enableAutoNeg,    
    IN MYD_BOOL swReset
)
{
    MYD_OP_MODE opMode;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    /* see what mode this lane is operating in, needed to figure out what registers to access */
    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode));

    /* Enable/disable auto-neg */
    ATTEMPT(mydConfigAutoNeg(pDev, mdioPort, host_or_line, laneOffset, opMode, enableAutoNeg));

    /* handle software reset */
    if (swReset)
    {
        ATTEMPT(mydLaneSoftReset(pDev, mdioPort, host_or_line, laneOffset, MAX_SWRESET_WAIT));        
    }
    
    return MYD_OK;
}


/*******************************************************************************
 MYD_STATUS mydAutoNegCheckComplete
    Check if auto-neg is completed
*******************************************************************************/
MYD_STATUS mydAutoNegCheckComplete
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_BOOL *autoNegComplete
)
{
    MYD_U16 anStatusReg = MYD_AUTONEG_STATUS_LINE + laneOffset*0x200;
    MYD_U16 temp = 0;

    *autoNegComplete = MYD_FALSE;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    if (host_or_line == MYD_HOST_SIDE)
    {
        anStatusReg = MYD_AUTONEG_STATUS_HOST + laneOffset*0x200;
    }

    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_AUTONEG, anStatusReg, 5, 1, &temp));

    if (temp)
    {
        *autoNegComplete = MYD_TRUE;
    }
    
    return MYD_OK;
}


/*******************************************************************************
 MYD_STATUS mydGetAutoNegResolution
    Get the speed/protocol and RS-FEC resolution from auto-neg
*******************************************************************************/
MYD_STATUS mydGetAutoNegResolution
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *speed_bits
)
{
    MYD_U16 anEthStatReg = MYD_AUTONEG_ETH_STATUS_LINE + laneOffset*0x200;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);
    *speed_bits = 0;

    if (host_or_line == MYD_HOST_SIDE)
    {
        anEthStatReg = MYD_AUTONEG_ETH_STATUS_HOST + laneOffset*0x200;
    }
    
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_AUTONEG, anEthStatReg, speed_bits));

    /* clear off ability bit which is always true, so result coming back is only speed and FEC */
    *speed_bits &= 0xFFFE;

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydCL37AutoNegControl
    Enable/disable Clause 37 auto-neg (changing from enable to disable 
    automatically restarts auto-neg)
*******************************************************************************/
MYD_STATUS mydCL37AutoNegControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 enableAutoNeg
)
{
    MYD_OP_MODE opMode, opModeHost, opModeLine;

    MYD_CHECK_DEV(pDev, mdioPort, laneOffset);

    if (!((host_or_line == MYD_LINE_SIDE) || (host_or_line == MYD_HOST_SIDE) ||
        (host_or_line == MYD_BOTH_SIDE)))
    {
        MYD_DBG_ERROR("mydCL37AutoNegControl: Incorrect host or line interface\n");
        return MYD_FAIL;
    }

    /* see what mode the lane(s) are operating in, it must be MYD_P1X */
    if (host_or_line == MYD_BOTH_SIDE)
    {
        ATTEMPT(mydGetOpMode(pDev, mdioPort, MYD_HOST_SIDE, laneOffset, &opModeHost));        
        ATTEMPT(mydGetOpMode(pDev, mdioPort, MYD_LINE_SIDE, laneOffset, &opModeLine));
        opMode = MYD_P1X;
    }
    else
    {
        ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode));
    }

    if (!(host_or_line == MYD_BOTH_SIDE && opModeHost == MYD_P1X && opModeLine == MYD_P1X) ||
         (opMode != MYD_P1X))
    {
        MYD_DBG_ERROR("mydCL37AutoNegControl: Incorrect mode. CL-37 AutoNeg applies only to MYD_P1X\n");
        return MYD_FAIL;
    }

    if (enableAutoNeg == MYD_ENABLE)
    {
        if ((host_or_line == MYD_LINE_SIDE) || (host_or_line == MYD_BOTH_SIDE))
        {
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_LINE_SIDE, MYD_PCS_1G_AN_ADV_LANE(laneOffset), 0x0020));            
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_LINE_SIDE, MYD_PCS_1G_CNTL_LANE(laneOffset), 0x1140));
        }

        if ((host_or_line == MYD_HOST_SIDE) || (host_or_line == MYD_BOTH_SIDE))
        {
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_HOST_SIDE, MYD_PCS_1G_AN_ADV_LANE(laneOffset), 0x0020));            
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_HOST_SIDE, MYD_PCS_1G_CNTL_LANE(laneOffset), 0x1140));
        }
    }
    else if (enableAutoNeg == MYD_DISABLE)
    {
        if ((host_or_line == MYD_LINE_SIDE) || (host_or_line == MYD_BOTH_SIDE))
        {
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_LINE_SIDE, MYD_PCS_1G_CNTL_LANE(laneOffset), 0x0140));
        }

        if ((host_or_line == MYD_HOST_SIDE) || (host_or_line == MYD_BOTH_SIDE))
        {
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_HOST_SIDE, MYD_PCS_1G_CNTL_LANE(laneOffset), 0x0140));
        }
    }
    else
    {
        MYD_DBG_ERROR("mydCL37AutoNegControl: Error - invalid enableAutoNeg input:0x%04X\n", enableAutoNeg);
        return MYD_FAIL;
    }

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydSetPauseAdvertisement
    Set the pause advertisement options for the near-end
*******************************************************************************/
MYD_STATUS mydSetPauseAdvertisement
(
     IN MYD_DEV_PTR pDev,
     IN MYD_U16  mdioPort,
     IN MYD_U16  host_or_line,
     IN MYD_U16  laneOffset,
     IN MYD_U16  pauseType,
     IN MYD_BOOL swReset
)
{
    MYD_U16 anBasePageReg = MYD_AUTONEG_ADV1_LINE + laneOffset*0x200;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    if (host_or_line == MYD_HOST_SIDE)
    {
        anBasePageReg = MYD_AUTONEG_ADV1_HOST + laneOffset*0x200;
    }

    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, anBasePageReg, 10, 2, pauseType));
    
    /* handle software reset */
    if (swReset)
    {
        ATTEMPT(mydLaneSoftReset(pDev, mdioPort, host_or_line, laneOffset, MAX_SWRESET_WAIT));        
    }
    
    return MYD_OK;

}

/*******************************************************************************
 MYD_STATUS mydGetPauseAdvertisement
    Read the pause advertisement options that were set for the near-end
*******************************************************************************/
MYD_STATUS mydGetPauseAdvertisement
(
     IN MYD_DEV_PTR pDev,
     IN MYD_U16 mdioPort,
     IN MYD_U16 host_or_line,
     IN MYD_U16 laneOffset,
     OUT MYD_U16 *pauseType
)
{
    MYD_U16 anBasePageReg = MYD_AUTONEG_ADV1_LINE + laneOffset*0x200;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    if (host_or_line == MYD_HOST_SIDE)
    {
        anBasePageReg = MYD_AUTONEG_ADV1_HOST + laneOffset*0x200;
    }

    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_AUTONEG, anBasePageReg, 10, 2, pauseType));
    
    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydGetLPAdvertisedPause
    Read the LP pause advertisement options received during auto-neg
*******************************************************************************/
MYD_STATUS mydGetLPAdvertisedPause
(
     IN MYD_DEV_PTR pDev,
     IN MYD_U16 mdioPort,
     IN MYD_U16 host_or_line,
     IN MYD_U16 laneOffset,
     OUT MYD_U16 *pauseType
)
{
    MYD_U16 anLPBasePageReg = MYD_AUTONEG_LP_ABILITY_LINE+ laneOffset*0x200;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    if (host_or_line == MYD_HOST_SIDE)
    {
        anLPBasePageReg = MYD_AUTONEG_LP_ABILITY_HOST + laneOffset*0x200;
    }

    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_AUTONEG, anLPBasePageReg, 10, 2, pauseType));
    
    return MYD_OK;

}

/*******************************************************************************
 MYD_STATUS mydGetTxRxPauseResolution
    Look at the advertised and LP received pause bits and determine the pause
    resolution (call after auto-neg is completed).
*******************************************************************************/
MYD_STATUS mydGetTxRxPauseResolution
(
     IN MYD_DEV_PTR pDev,
     IN MYD_U16 mdioPort,
     IN MYD_U16 host_or_line,
     IN MYD_U16 laneOffset,
     OUT MYD_BOOL *pauseResolved,
     OUT MYD_BOOL *tx_pause_enabled,
     OUT MYD_BOOL *rx_pause_enabled
)
{
    MYD_U16 advPause, lpPause, combinedPause;
    
    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);
    *pauseResolved = MYD_FALSE;

    ATTEMPT(mydGetPauseAdvertisement(pDev, mdioPort, host_or_line, laneOffset, &advPause));
    ATTEMPT(mydGetLPAdvertisedPause(pDev, mdioPort, host_or_line, laneOffset, &lpPause));

    *pauseResolved = MYD_TRUE;

    combinedPause = advPause | (lpPause<<2); /* LP: ASM_DIR:PAUSE NE: ASM_DIR:PAUSE */

    if ((combinedPause & 0x5) == 0x5)
    {
        *tx_pause_enabled = MYD_TRUE;
        *rx_pause_enabled = MYD_TRUE;

    }
    else if ((combinedPause & 0xE) == 0xE)
    {
        *tx_pause_enabled = MYD_TRUE;
        *rx_pause_enabled = MYD_FALSE;       
    }
    else if (combinedPause == 0xB)
    {
        *tx_pause_enabled = MYD_FALSE;
        *rx_pause_enabled = MYD_TRUE;  
    }
    else
    {
        *tx_pause_enabled = MYD_FALSE;  
        *rx_pause_enabled = MYD_FALSE;  
    }
    
    return MYD_OK;
}


/*******************************************************************************
 MYD_STATUS mydCheckPCSLinkStatus
    Check PCS modes link status on a lane
*******************************************************************************/
MYD_STATUS mydCheckPCSLinkStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  laneOffset,
    OUT MYD_U16 *currentStatus,
    OUT MYD_U16 *latchedStatus,
    OUT MYD_PCS_LINK_STATUS *statusDetail
)
{
    MYD_OP_MODE hostOpMode;
    MYD_OP_MODE lineOpMode;
    MYD_U16 modeType;

    MYD_CHECK_DEV(pDev, mdioPort, laneOffset);

    hostOpMode = pDev->hostConfig[MYD_GET_PORT_IDX(pDev, mdioPort)][laneOffset].opMode;
    lineOpMode = pDev->lineConfig[MYD_GET_PORT_IDX(pDev, mdioPort)][laneOffset].opMode;

    /* check lane offset is valid and lane is configured */
    if ((mydCheckOpModeLaneOffset(pDev, mdioPort, laneOffset, hostOpMode) == MYD_FAIL) ||
        (mydCheckOpModeLaneOffset(pDev, mdioPort, laneOffset, lineOpMode) == MYD_FAIL))
    {
        MYD_DBG_ERROR("mydCheckPCSLinkStatus: incorrect lane Offset: %u\n", laneOffset);
        return MYD_FAIL;
    }

    modeType = opModeTable[hostOpMode][MYD_OP_TABLE_MODE_TYPE];

    if (modeType != MYD_PCS)
    {
        MYD_DBG_ERROR("mydCheckPCSLinkStatus: Error. Incorrect mode type.\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydReadPCSLinkStatus(pDev, mdioPort, laneOffset, currentStatus, latchedStatus, statusDetail));

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydCheckRepeaterLinkStatus
    Checks Repeater modes link status on a lane or port
*******************************************************************************/
MYD_STATUS mydCheckRepeaterLinkStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    IN MYD_BOOL perLaneStatus,
    OUT MYD_U16 *currentStatus,
    OUT MYD_REPEATER_LINK_STATUS *statusDetail
)
{
    MYD_OP_MODE hostOpMode;
    MYD_OP_MODE lineOpMode;
    MYD_U16 modeType;

    MYD_CHECK_DEV(pDev, mdioPort, laneOffset);

    hostOpMode = pDev->hostConfig[MYD_GET_PORT_IDX(pDev, mdioPort)][laneOffset].opMode;
    lineOpMode = pDev->lineConfig[MYD_GET_PORT_IDX(pDev, mdioPort)][laneOffset].opMode;

    /* check lane offset is valid and lane is configured */
    /* if perLaneStatus is MYD_FALSE, checks if the provided laneOffset is the 1st lane of 
       the repeater mode */
   if (perLaneStatus  == MYD_FALSE) 
    {
    if ((mydCheckOpModeLaneOffset(pDev, mdioPort, laneOffset, hostOpMode) == MYD_FAIL) ||
        (mydCheckOpModeLaneOffset(pDev, mdioPort, laneOffset, lineOpMode) == MYD_FAIL))
        {
            MYD_DBG_ERROR("mydCheckRepeaterLinkStatus: incorrect lane Offset: %u\n", laneOffset);
            return MYD_FAIL;
        }
    }

    modeType = opModeTable[hostOpMode][MYD_OP_TABLE_MODE_TYPE];

    if (modeType != MYD_TRANSPARENT)
    {
        MYD_DBG_ERROR("mydCheckRepeaterLinkStatus: Error. Incorrect mode type.\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydReadRepeaterLinkStatus(pDev, mdioPort, laneOffset, perLaneStatus, currentStatus, statusDetail));

    return MYD_OK;
}


/*******************************************************************************
MYD_STATUS mydSetRmFifoCntl

*******************************************************************************/
MYD_STATUS mydSetRmFifoCntl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 txThresholdHigh,
    IN MYD_U16 txThresholdLow,
    IN MYD_U16 rxThreshold,
    IN MYD_U16 txSatThreshold
)
{
    if (!pDev->devEnabled)
    {
        MYD_DBG_ERROR("mydSetRmFifoCntl: device not initialized\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydIsPortValid(pDev, mdioPort));

    if ((txThresholdHigh > 0x7FF) || (txThresholdLow > 0x7FF) ||
        (rxThreshold > 0x7FF) || (txSatThreshold > 0x7FF))
    {
        MYD_DBG_ERROR("mydSetRmFifoCntl: Out of range; values must be < 0x7FF.\n");
        return MYD_FAIL;
    }

    if (txThresholdLow > txThresholdHigh)
    {
        MYD_DBG_ERROR("mydSetRmFifoCntl: txThresholdLow cannot be more than txThresholdHigh.\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_CHIP_REG, MYD_RM_FIFO_TX_THR_H, 0, 11, txThresholdHigh));
    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_CHIP_REG, MYD_RM_FIFO_TX_THR_L, 0, 11, txThresholdLow));
    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_CHIP_REG, MYD_RM_FIFO_RX_THR, 0, 11, rxThreshold));
    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_CHIP_REG, MYD_RM_FIFO_TX_SAT_THR, 0, 11, txSatThreshold));

    return MYD_OK;
}

/*******************************************************************************
MYD_STATUS mydGetRmFifoCntl

*******************************************************************************/
MYD_STATUS mydGetRmFifoCntl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    OUT MYD_U16 *txThresholdHigh,
    OUT MYD_U16 *txThresholdLow,
    OUT MYD_U16 *rxThreshold,
    OUT MYD_U16 *txSatThreshold
)
{
    if (!pDev->devEnabled)
    {
        MYD_DBG_ERROR("mydGetRmFifoCntl: device not initialized\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydIsPortValid(pDev, mdioPort));

    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_CHIP_REG, MYD_RM_FIFO_TX_THR_H, 0, 11, txThresholdHigh));
    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_CHIP_REG, MYD_RM_FIFO_TX_THR_L, 0, 11, txThresholdLow));
    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_CHIP_REG, MYD_RM_FIFO_RX_THR, 0, 11, rxThreshold));
    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_CHIP_REG, MYD_RM_FIFO_TX_SAT_THR, 0, 11, txSatThreshold));

    return MYD_OK;
}

/*******************************************************************************
MYD_STATUS mydGetRmFifoPktDropCntr

*******************************************************************************/
MYD_STATUS mydGetRmFifoPktDropCntr
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 readClear,
    OUT MYD_U16 *txPktDropCntr
)
{
    if (!pDev->devEnabled)
    {
        MYD_DBG_ERROR("mydGetRmFifoPktDropCntr: device not initialized\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydIsPortValid(pDev, mdioPort));

    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_CHIP_REG, MYD_RM_FIFO_TX_DROP_CNTR, txPktDropCntr));

    if (readClear)
    {
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_RM_FIFO_TX_DROP_CNTR, 0));
    }

    return MYD_OK;
}

/*******************************************************************************
MYD_STATUS mydSetRmFifoInterruptEnable

*******************************************************************************/
MYD_STATUS mydSetRmFifoInterruptEnable
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 intrEnableFlags
)
{
    if (!pDev->devEnabled)
    {
        MYD_DBG_ERROR("mydSetRmFifoInterruptEnable: device not initialized\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydIsPortValid(pDev, mdioPort));

    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_CHIP_REG, MYD_RM_FIFO_INTR_MASK, 0, 13, intrEnableFlags));

    return MYD_OK;
}

/*******************************************************************************
MYD_STATUS mydGetRmFifoInterruptStatus
Get rate matching FIFO interrupt status
*******************************************************************************/
MYD_STATUS mydGetRmFifoInterruptStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    OUT MYD_U16 *rmFifoIntrStatus
)
{
    if (!pDev->devEnabled)
    {
        MYD_DBG_ERROR("mydGetRmFifoInterruptStatus: device not initialized\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydIsPortValid(pDev, mdioPort));

    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_CHIP_REG, MYD_RM_FIFO_INTR_STAT, 0, 13, rmFifoIntrStatus));

    return MYD_OK;
}

/*******************************************************************************
MYD_STATUS mydSetIPGMode
*******************************************************************************/
MYD_STATUS mydSetIPGMode
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 rxIPGMode,
    IN MYD_U16 txIPGMode,
    IN MYD_U16 avgDIC
)
{
    if (!pDev->devEnabled)
    {
        MYD_DBG_ERROR("mydSetIPGMode: device not initialized\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydIsPortValid(pDev, mdioPort));
    /*
    rxIPGMode - Rx direction (25Gb/s to 40Gb/s) IPG control between packets
    00/01: minimum 8 bytes IPG
    10: minimum 16 bytes IPG
    */
    if (rxIPGMode <= 2)
    {
        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_CHIP_REG, MYD_IPG_CFG_CNTL, 6, 2, rxIPGMode));
    }
    else
    {
        MYD_DBG_ERROR("mydSetIPGMode: incorrect rxIPGMode value:%u\n", rxIPGMode);
        return MYD_FAIL;
    }

    /*
    txIPGMode - Tx direction (40Gb/s to 25Gb/s) IPG control between packets
    00: DIC
    01: minimum 8 bytes IPG
    10: minimum 12 bytes IPG
    11: minimum 16 bytes IPG
    */
    if (txIPGMode <= 3)
    {
        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_CHIP_REG, MYD_IPG_CFG_CNTL, 4, 2, txIPGMode));
    }
    else
    {
        MYD_DBG_ERROR("mydSetIPGMode: incorrect txIPGMode value:%u\n", rxIPGMode);
        return MYD_FAIL;
    }

    /* only set DIC value if txIPGMode is set to DIC mode(DIC=0) */
    if (txIPGMode == 0)
    {
        /*
        avgDIC - Tx direction (40Gb/s to 25Gb/s) average IPG setting in DIC mode
        (in unit of bytes) valid setting is 8 to 15 (default=12)
        */
        if (avgDIC >= 8 && avgDIC <= 15)
        {
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_CHIP_REG, MYD_IPG_CFG_CNTL, 0, 4, avgDIC));
        }
        else
        {
            MYD_DBG_ERROR("mydSetIPGMode: incorrect avgDIC value:%u\n", avgDIC);
            return MYD_FAIL;
        }
    }

    return MYD_OK;
}

/*******************************************************************************
MYD_STATUS mydGetIPGMode
*******************************************************************************/
MYD_STATUS mydGetIPGMode
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    OUT MYD_U16 *rxIPGMode,
    OUT MYD_U16 *txIPGMode,
    OUT MYD_U16 *avgDIC
)
{
    if (!pDev->devEnabled)
    {
        MYD_DBG_ERROR("mydGetIPGMode: device not initialized\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydIsPortValid(pDev, mdioPort));

    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_CHIP_REG, MYD_IPG_CFG_CNTL, 6, 2, rxIPGMode));
    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_CHIP_REG, MYD_IPG_CFG_CNTL, 4, 2, txIPGMode));
    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_CHIP_REG, MYD_IPG_CFG_CNTL, 0, 4, avgDIC));

    return MYD_OK;
}


/*******************************************************************
 MYD_STATUS mydGetPcsFaultStatus
     Read the PCS status register and return the latched and 
     current value of the Tx/Rx fault bits
*******************************************************************/
MYD_STATUS mydGetPcsFaultStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *currentTxFaultStatus,
    OUT MYD_U16 *currentRxFaultStatus,
    OUT MYD_U16 *latchedTxFaultStatus,
    OUT MYD_U16 *latchedRxFaultStatus
)
{
    MYD_OP_MODE opMode;    
    MYD_U16 lineSpeed, modeType, regAddr, tmp1, tmp2;

    MYD_CHECK_DEV(pDev, mdioPort, laneOffset);
    
    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode)); 
    
    if (mydIsLaneOffsetValid(pDev, mdioPort, host_or_line, laneOffset) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydGetPcsFaultStatus: Invalid lane used:%u \n", laneOffset);
        return MYD_FAIL;
    }

    modeType = opModeTable[opMode][MYD_OP_TABLE_MODE_TYPE];

    if (modeType != MYD_PCS)
    {
        MYD_DBG_ERROR("mydGetPcsFaultStatus: Not a PCS mode!\n");
        return MYD_FAIL;
    }

    lineSpeed = opModeTable[opMode][MYD_OP_TABLE_SPEED];

    switch (lineSpeed)
    {
        case MYD_5GB:
        case MYD_10GB:
        case MYD_25GB:
            regAddr = MYD_PCS_25G_PCS_STATUS2(laneOffset);
            break;

        case MYD_40GB:
        case MYD_50GB:
            regAddr = MYD_PCS_40G_PCS_STATUS2(laneOffset);
            break;

        case MYD_100GB:
            regAddr = MYD_PCS_100G_PCS_STATUS2(laneOffset);
            break;
            
        case MYD_200GB:
            regAddr = MYD_PCS_200G_PCS_STATUS2;
            break;

        default:
            MYD_DBG_ERROR("mydGetPcsFaultStatus: unsupported speed or speed unknown\n");
            return MYD_FAIL;
            break;        
    }

    /* must read it in a single read because it clears the latch bits */
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, regAddr, &tmp1));
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, regAddr, &tmp2));

    ATTEMPT(mydHwGetRegFieldFromWord(tmp1, 11, 1, latchedTxFaultStatus));
    ATTEMPT(mydHwGetRegFieldFromWord(tmp2, 11, 1, currentTxFaultStatus));    
    ATTEMPT(mydHwGetRegFieldFromWord(tmp1, 10, 1, latchedRxFaultStatus));    
    ATTEMPT(mydHwGetRegFieldFromWord(tmp2, 10, 1, currentRxFaultStatus));   

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydLaneReset
     Check timeout after the Lane soft reset
*******************************************************************/
MYD_STATUS mydLaneSoftReset
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 timeoutMs
)
{
    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, (MYD_MODE_SELECTION+laneOffset), 15, 1, 1));
    ATTEMPT(mydLaneResetTimeout(pDev, mdioPort, host_or_line, laneOffset, timeoutMs));

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydSetDPFaultConfig
 Configure this side Data Path Mode when link is down at the other side
*******************************************************************/
MYD_STATUS mydSetDPFaultConfig
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 datapathMode,
    IN MYD_U16 txType,
    IN MYD_U16 rxType
)
{
    MYD_OP_MODE opMode;
    MYD_BOOL laneToConfigure;
    MYD_U8 fieldOffset;
    MYD_U16 laneCtr, laneCount;
    MYD_U16 mdioPortIndex = MYD_GET_PORT_IDX(pDev, mdioPort);

    if (laneOffset == MYD_ALL_LANES)
    {
        laneCtr = 0; /* all lanes go from 0 to MYD_ALL_LANES */
    }
    else
    {
        laneCtr = laneOffset++; /* single lane goes from lane to lane+1 */
    }

    while(laneCtr < laneOffset) /* one lane or all lanes */
    {
        MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneCtr, host_or_line);
        ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneCtr, &opMode));
        laneCount = opModeTable[opMode][MYD_OP_TABLE_LANE_COUNT];

        /* this is case where host passed a specific lane, make sure it's the first lane of */
        /* a multi-lane mode or the only lane of a configured single lane mode */
        if (laneOffset != MYD_ALL_LANES)
        {
            ATTEMPT(mydCheckOpModeLaneOffset(pDev, mdioPort, laneCtr, opMode));
            laneToConfigure = MYD_TRUE;
        }
        /* this is the case where MYD_ALL_LANES were passed, skip unassigned lanes or lanes */
        /* that are not the first lane of a multi-lane mode */
        else
        {
            laneToConfigure = MYD_FALSE;
            switch(laneCount)
            {
                case MYD_1_LANE_MODE:
                    if (laneCtr < MYD_NUM_LANES)
                    {
                        laneToConfigure = MYD_TRUE;
                    }
                    break;

                case MYD_2_LANE_MODE:
                    if ((laneCtr == 0) || (laneCtr == 2))
                    {
                        laneToConfigure = MYD_TRUE;
                    }
                    break;

                case MYD_4_LANE_MODE:
                    if (laneCtr == 0)
                    {
                        laneToConfigure = MYD_TRUE;
                    }
                    break;
            
                case MYD_8_LANE_MODE:
                    if ((laneCtr == 0) && (pDev->portCount > 1))
                    {
                        if ((mdioPortIndex == 0) || (mdioPortIndex == 2)) 
                        {
                            laneToConfigure = MYD_TRUE;
                        }
                    }
                    break;
                    
                default:
                    /* not possible, but if it happens won't configure this lane */
                    break;
            }
        }

        if (laneToConfigure == MYD_TRUE)
        {
            MYD_U16 tmpData;
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, MYD_DATAPATH_CNTL, 14, 2, datapathMode));

            if (datapathMode == MYD_DP_DISENGAGE_MODE)
            {
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_DISENGAGE_TYPE, &tmpData));

                fieldOffset = laneCtr*2; /* Tx Disengage Type Bits */
                ATTEMPT(mydHwSetRegFieldToWord(tmpData, txType, fieldOffset, 2, &tmpData));
                fieldOffset += 8; /* Rx Disengage Type Bits */
                ATTEMPT(mydHwSetRegFieldToWord(tmpData, rxType, fieldOffset, 2, &tmpData));

                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_DISENGAGE_TYPE, tmpData));
            }
        }

        laneCtr++;
    }
    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydGetDPFaultConfig
 Read this side Data Path Mode when link is down at the other side
*******************************************************************/
MYD_STATUS mydGetDPFaultConfig
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *datapathMode,
    OUT MYD_U16 *txType,
    OUT MYD_U16 *rxType
)
{
    MYD_OP_MODE opMode;
    MYD_U8 fieldOffset;
    MYD_U16 tmpData;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);
    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode));

    /* Make sure it's the first lane of a multi-lane mode or the only lane of */
    /* a configured single lane mode */
    ATTEMPT(mydCheckOpModeLaneOffset(pDev, mdioPort, laneOffset, opMode));

    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_DATAPATH_CNTL, &tmpData));
    ATTEMPT(mydHwGetRegFieldFromWord(tmpData, 14, 2, datapathMode));

    if ((*datapathMode == MYD_DP_DISENGAGE_MODE) ||
        (*datapathMode == MYD_DP_DEFAULT_MODE) ||
        (*datapathMode == MYD_DP_RESET_MODE))
    {
        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_DISENGAGE_TYPE, &tmpData));
        fieldOffset = laneOffset*2; /* Tx Disengage Type Bits */
        ATTEMPT(mydHwGetRegFieldFromWord(tmpData, fieldOffset, 2, txType));
        fieldOffset += 8; /* Rx Disengage Type Bits */
        ATTEMPT(mydHwGetRegFieldFromWord(tmpData, fieldOffset, 2, rxType));
    }
    else
    {
        MYD_DBG_ERROR("mydGetDPFaultConfig: Read Invalid Data Path Mode\n");
        return MYD_FAIL;
    }

    return MYD_OK;
}
