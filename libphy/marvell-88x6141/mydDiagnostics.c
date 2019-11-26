/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions and global data for higher-level functions 
using MDIO access to enable test modes, loopbacks, and other diagnostic 
functions of the Marvell X7120/X6181/X6141 PHY.
********************************************************************/
#include "mydApiTypes.h"
#include "mydUtils.h"
#include "mydHwCntl.h"
#include "mydAPI.h"
#include "mydApiRegs.h"
#include "mydDiagnostics.h"
#include "mydIntrIOConfig.h"
#include "mydAPIInternal.h"
#include "mydHwSerdesCntl.h"

#define MYD_MARVELL_OUI  0x2B02
#define MAX_RESET_WAIT   1000

/*******************************************************************************
 MYD_STATUS mydGetChipRevision
*******************************************************************************/
MYD_STATUS mydGetChipRevision
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    OUT MYD_DEVICE_ID *deviceId
)
{
    MYD_U16 oui;
    MYD_U16 chipData1, chipData2;

    MYD_STATUS retVal = MYD_OK;
    
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_LINE_SIDE, 0x1002, &chipData1));
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_LINE_SIDE, 0x1003, &chipData2));

    oui = ((chipData1<<8 & 0xFF00) | ((chipData2 & 0xFC00)>>10)) ;
    if (oui != MYD_MARVELL_OUI)
    {
        MYD_DBG_ERROR("mydGetChipRevision: incorrect OUI: 0x%x\n", oui);
        return MYD_FAIL;
    }

    switch((chipData2 & 0x000C)>>2)
    {
        case MYD_DEV_X6181:
            pDev->deviceId = MYD_DEV_X6181;
            *deviceId = MYD_DEV_X6181;
            break;

        case MYD_DEV_X7120:
            pDev->deviceId = MYD_DEV_X7120;
            *deviceId = MYD_DEV_X7120;
            break;

        case MYD_DEV_X6141:
            pDev->deviceId = MYD_DEV_X6141;
            *deviceId = MYD_DEV_X6141;
            break;

        default:
            pDev->deviceId = MYD_DEV_UNKNOWN;
            *deviceId = MYD_DEV_UNKNOWN;
            MYD_DBG_ERROR("mydGetChipRevision: incorrect device model: 0x%x\n", ((chipData2 & 0x000C)>>2));
            return MYD_FAIL;
    }

    switch(chipData2 & 0x0003)
    {
        case MYD_REV_A0:
            pDev->chipRevision = MYD_REV_A0;
            break;

        case MYD_REV_A1:
            pDev->chipRevision = MYD_REV_A1;
            break;

         default:
            pDev->chipRevision = MYD_REV_UNKNOWN;
            MYD_DBG_ERROR("mydGetChipRevision: incorrect device revision model: 0x%x\n", (chipData2 & 0x0003));
            return MYD_FAIL;
            break;
   }

    return retVal;
}

/*******************************************************************************
 MYD_STATUS mydDevicePortCount
*******************************************************************************/
MYD_STATUS mydDevicePortCount
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    OUT MYD_U16 *portCount
)
{
    switch(pDev->deviceId)
    {
        case MYD_DEV_X6181:
            *portCount = MYD_X6181_PORT_COUNT;
            break;

        case MYD_DEV_X7120:
            *portCount = MYD_X7120_PORT_COUNT;
            break;

        case MYD_DEV_X6141:
            *portCount = MYD_X6141_PORT_COUNT;
            break;

        default:
            *portCount = 0;
            MYD_DBG_ERROR("mydDevicePortCount: invalid device model: 0x%x\n", pDev->deviceId);
            return MYD_FAIL;
    }

    return MYD_OK;
}


/*******************************************************************************
 MYD_STATUS mydGetChipFWRevision
   Revision in <major>.<minor> format
*******************************************************************************/
MYD_STATUS mydGetChipFWRevision
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    OUT MYD_U16 *major,
    OUT MYD_U16 *minor
)
{
    MYD_U16 temp;

    *major = *minor = 0;

    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, 0xD8F4, &temp));

    *major = (temp & 0xFF00)>>8;
    *minor = temp & 0x00FF;

    return MYD_OK;
}


/*******************************************************************************
 MYD_STATUS mydGetSerdesSignalDetectAndDspLock
    Return value of signal detect and DSP lock for corresponding lane.
*******************************************************************************/
MYD_STATUS mydGetSerdesSignalDetectAndDspLock
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,    
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *signalDetect,
    OUT MYD_U16 *dspLock
)
{
    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);
        
    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, MYD_SERDES_LANE0+(0x80*laneOffset), 5, 1, dspLock));
    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, MYD_SERDES_LANE0+(0x80*laneOffset), 7, 1, signalDetect));

    return MYD_OK;    
}

/*******************************************************************************
 MYD_STATUS mydSetPCSLineLoopback
    Enable/Disable line side loopbacks
*******************************************************************************/
MYD_STATUS mydSetPCSLineLoopback
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    IN MYD_U16 loopback_type,
    IN MYD_U16 enable
)
{
    MYD_U16 regAddrPCS,regAddrPMA;
    MYD_SPEED lineSpeed;
    MYD_U16 modeType, autoNeg, i;
    MYD_U16 gearboxMode = 0;
    MYD_U16 mdioPortIndex = MYD_GET_PORT_IDX(pDev, mdioPort);

    MYD_CHECK_DEV(pDev, mdioPort, laneOffset);

    modeType = pDev->lineConfig[mdioPortIndex][laneOffset].opModeType;
    lineSpeed = pDev->lineConfig[mdioPortIndex][laneOffset].speed;
    autoNeg = pDev->lineConfig[mdioPortIndex][laneOffset].autoNeg;

    if (modeType != MYD_PCS)
    {
        MYD_DBG_ERROR("mydSetPCSLineLoopback: not a PCS mode\n");
        return MYD_FAIL;
    }

    switch (lineSpeed)
    {
        case MYD_1GB:
        case MYD_2P5GB:
            regAddrPCS = MYD_PCS_1G_CNTL_LANE(laneOffset);
            regAddrPMA = MYD_PMA_HOST_100G_CNTL_LANE(laneOffset);
            break;

        case MYD_5GB:
        case MYD_10GB:
        case MYD_25GB:
            regAddrPCS = MYD_PCS_25G_CNTL_LANE(laneOffset);
            regAddrPMA = MYD_PMA_HOST_100G_CNTL_LANE(laneOffset);            
            break;

        case MYD_40GB:
        case MYD_50GB:
            regAddrPCS = MYD_PCS_40G_CNTL_LANE(laneOffset);
            regAddrPMA = MYD_PMA_HOST_100G_CNTL_LANE(laneOffset);
            break;

        case MYD_100GB:
            regAddrPCS = MYD_PCS_100G_CNTL_LANE(laneOffset);
            regAddrPMA = MYD_PMA_HOST_100G_CNTL_LANE(laneOffset);
            break;

        case MYD_200GB:
            regAddrPCS = MYD_PCS_200G_CNTL;
            regAddrPMA = MYD_PMA_HOST_200G_CNTL;
            laneOffset = 0;
            break;

        default:
            MYD_DBG_ERROR("mydSetPCSLineLoopback: incorrect speed selection: %d\n", (int)lineSpeed);
            return MYD_FAIL;                            
            break;
    }

    enable = (enable > 0)? 1:0;

    switch(loopback_type)
    {
        case MYD_SHALLOW_PCS_LB:

            /* BEFORE */

            if (lineSpeed == MYD_200GB)
            {
                for (i=0; i<MYD_NUM_LANES; i++)
                {
                    /* Enable/Disable loopback */
                    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_LINE_SIDE, MYD_PORT_PCS_CNTL,
                                                (MYD_U8)(12+i), 1, enable));
                }
            }
            else
            {
                /* Enable/Disable loopback */
                ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort,MYD_LINE_SIDE,MYD_PORT_PCS_CNTL,(MYD_U8)(12+laneOffset),1,enable));
            }

            /* AFTER */
            if (gearboxMode == 1)
            {
                if (enable == 1)
                {
                    /* Disable Resetting FIFO based on other side PCS RX reset*/
                    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort,MYD_LINE_SIDE,0xF0C0,12,4,0xE));
                }
                else
                {
                    /* Enable Resetting FIFO based on other side PCS RX reset*/
                    ATTEMPT(mydHwSetPhyRegField(pDev,mdioPort,MYD_LINE_SIDE,0xF0C0,12,4,0x7));
                    /*Reset RMFIFO */
                    ATTEMPT(mydHwSetPhyRegField(pDev,mdioPort,MYD_PORT_REG,0xF602,0,2,0x3));
                    /*Release RMFIFO Reset*/
                    ATTEMPT(mydHwSetPhyRegField(pDev,mdioPort,MYD_PORT_REG,0xF602,0,2,0x0));
                }
            }
            break;

        case MYD_DEEP_PCS_LB:
            ATTEMPT(mydSetDeepPCSLoopback(pDev, mdioPort, laneOffset, MYD_HOST_SIDE, 
                                          gearboxMode, autoNeg, lineSpeed, regAddrPCS, enable));
            break;

        case MYD_DEEP_PMA_LB:
            /* BEFORE */
            /* Enable/Disable loopback */
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, regAddrPMA, 0, 1, enable));
            
            /* AFTER */
            if (gearboxMode == 1)
            {
                /*Disable/Enable Resetting FIFO based on other side PCS RX reset*/
                ATTEMPT(mydHwSetPhyRegField(pDev,mdioPort,MYD_HOST_SIDE,0x904D,15,1,enable));
            }

            if (autoNeg)
            {
                /*Enable/Disable nonce match */
                ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, (0x9001+(laneOffset*0x200)), 7, 1, enable));
            }
            break;

        default:
            MYD_DBG_ERROR("mydSetPCSLineLoopback: incorrect loopback selection: %u\n", loopback_type);
            return MYD_FAIL;
            break;
    }

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydSetPCSHostLoopback
    Enable/Disable host side loopbacks
*******************************************************************************/
MYD_STATUS mydSetPCSHostLoopback
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    IN MYD_U16 loopback_type,
    IN MYD_U16 enable
)
{
    MYD_U16 regAddrPCS,regAddrPMA;
    MYD_U16 autoNeg, gearboxMode=0;
    MYD_SPEED hostSpeed;
    MYD_U16 modeType;
    MYD_U16 mdioPortIndex = MYD_GET_PORT_IDX(pDev, mdioPort);

    MYD_CHECK_DEV(pDev, mdioPort, laneOffset);

    modeType = pDev->hostConfig[mdioPortIndex][laneOffset].opModeType;
    hostSpeed = pDev->hostConfig[mdioPortIndex][laneOffset].speed;
    autoNeg = pDev->hostConfig[mdioPortIndex][laneOffset].autoNeg;

    if (modeType != MYD_PCS)
    {
        MYD_DBG_ERROR("mydSetPCSHostLoopback: not a PCS mode\n");
        return MYD_FAIL;
    }

    if (pDev->devInfo[mdioPortIndex] & MYD_GEARBOX_MODE)
    {
        gearboxMode = 1;
    }

    switch (hostSpeed)
    {
        case MYD_1GB:
        case MYD_2P5GB:
            regAddrPCS = MYD_PCS_1G_CNTL_LANE(laneOffset);
            regAddrPMA = MYD_PMA_100G_CNTL_LANE(laneOffset);
            break;

        case MYD_5GB:
        case MYD_10GB:
        case MYD_25GB:
            regAddrPCS = MYD_PCS_25G_CNTL_LANE(laneOffset);
            regAddrPMA = MYD_PMA_100G_CNTL_LANE(laneOffset);
            break;

        case MYD_40GB:
        case MYD_50GB:
            regAddrPCS = MYD_PCS_40G_CNTL_LANE(laneOffset);
            regAddrPMA = MYD_PMA_100G_CNTL_LANE(laneOffset);
            break;

        case MYD_100GB:
            regAddrPCS = MYD_PCS_100G_CNTL_LANE(laneOffset);
            regAddrPMA = MYD_PMA_100G_CNTL_LANE(laneOffset);
            break;

        case MYD_200GB:
            regAddrPCS = MYD_PCS_200G_CNTL;
            regAddrPMA = MYD_PMA_100G_CNTL;
            laneOffset = 0;
            break;

        default:
            MYD_DBG_ERROR("mydSetPCSHostLoopback: incorrect speed selection: %d\n", (int)hostSpeed);
            return MYD_FAIL;                            
            break;
    }

    enable = (enable > 0)? 1:0;

    switch(loopback_type)
    {
        case MYD_SHALLOW_PCS_LB:

            /* BEFORE */
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_HOST_SIDE, MYD_PORT_PCS_CNTL,
                                        (MYD_U8)(12+laneOffset), 1, enable));
            
            /* AFTER */
            if ((gearboxMode == 1) && (enable == 0))
            {
                /*Reset RMFIFO */
                ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, 0xF602, 0, 2, 0x3));
                /*Release RMFIFO Reset*/
                ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, 0xF602, 0, 2, 0x0));
            }
            break;

        case MYD_DEEP_PCS_LB:
            ATTEMPT(mydSetDeepPCSLoopback(pDev, mdioPort, laneOffset, MYD_LINE_SIDE, 
                                          gearboxMode, autoNeg, hostSpeed, regAddrPCS, enable));
            break;

        case MYD_DEEP_PMA_LB:
            /* BEFORE */
            /* Enable/Disable loopback */
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, regAddrPMA, 0, 1, enable));
            
            /* AFTER */
            if (gearboxMode == 1)
            {
                if (enable)
                {
                    /* Disable Resetting FIFO based on other side PCS RX reset*/
                    ATTEMPT(mydHwSetPhyRegField(pDev,mdioPort,MYD_LINE_SIDE,0xF0C0,12,4,0xE));
                }
                else
                {
                    /* Enable Resetting FIFO based on other side PCS RX reset*/
                    ATTEMPT(mydHwSetPhyRegField(pDev,mdioPort,MYD_LINE_SIDE,0xF0C0,12,4,0x7));
                }
            }

            if (autoNeg)
            {
                /*Enable/Disable nonce match */
                ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, 0x8001+((laneOffset*0x200)), 7, 1, enable));
            }

            break;

        default:
            MYD_DBG_ERROR("mydSetPCSHostLoopback: incorrect loopback selection: %u\n", loopback_type);
            return MYD_FAIL;
            break;
    }

    return MYD_OK;
}


/*******************************************************************************
 MYD_STATUS mydConfigurePktGeneratorChecker
    Configure packet generator checker function
*******************************************************************************/
MYD_STATUS mydConfigurePktGeneratorChecker
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    IN MYD_BOOL readToClear,
    IN MYD_BOOL dontuseSFDinChecker,
    IN MYD_U16  pktPatternControl,
    IN MYD_BOOL generateCRCoff,
    IN MYD_U32  initialPayload,
    IN MYD_U16  frameLengthControl,
    IN MYD_U16  numPktsToSend,
    IN MYD_BOOL randomIPG,
    IN MYD_U16  ipgDuration
)
{
    MYD_U16 regAddrOffset=0;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydGetPktGenRegOffset(pDev, mdioPort, host_or_line, laneOffset, &regAddrOffset));

    if (pktPatternControl > MYD_PKT_RANDOM_WORD || pktPatternControl == 1)
    {
        return MYD_FAIL;
    }

    if (frameLengthControl == 6 || frameLengthControl == 7)
    {
        return MYD_FAIL;
    }

    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, MYD_PKT_GEN_CONTROL1+regAddrOffset, 
                                15, 1, MYD_GET_BOOL_AS_BIT(readToClear)));
    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, MYD_PKT_GEN_CONTROL1+regAddrOffset, 
                                2, 1, MYD_GET_BOOL_AS_BIT(dontuseSFDinChecker)));
    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, MYD_PKT_GEN_CONTROL2+regAddrOffset, 
                                4, 4, pktPatternControl));
    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, MYD_PKT_GEN_CONTROL2+regAddrOffset, 
                                3, 1, MYD_GET_BOOL_AS_BIT(generateCRCoff)));

    /* load up initial payload */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_PKT_GEN_PAYLOAD1+regAddrOffset, (MYD_U16)initialPayload));
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_PKT_GEN_PAYLOAD2+regAddrOffset, (MYD_U16)(initialPayload>>16)));

    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_PKT_GEN_LENGTH+regAddrOffset, frameLengthControl));

    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_PKT_GEN_BURSTSEQ+regAddrOffset, numPktsToSend));

    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, MYD_PKT_GEN_IPG+regAddrOffset, 
                                15, 1, MYD_GET_BOOL_AS_BIT(randomIPG)));

    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, MYD_PKT_GEN_IPG+regAddrOffset, 0, 15, ipgDuration));

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydEnablePktGeneratorChecker
    Enable/Disable packet generator and checker function
*******************************************************************************/
MYD_STATUS mydEnablePktGeneratorChecker
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    IN MYD_BOOL enableGenerator,
    IN MYD_BOOL enableChecker
)
{
    MYD_U16 temp=0;
    MYD_U16 regAddrOffset=0;
    MYD_U16 mdioPortIndex = MYD_GET_PORT_IDX(pDev, mdioPort);

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    if ((pDev->devInfo[mdioPortIndex] & MYD_GEARBOX_MODE) && (enableGenerator == MYD_TRUE))
    {
        if (host_or_line == MYD_HOST_SIDE)
        {
           ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0x904D, 15, 1, 1));
        }
        else
        {
           ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xA04D, 15, 1, 1));
        }
    }

    ATTEMPT(mydGetPktGenRegOffset(pDev, mdioPort, host_or_line, laneOffset, &regAddrOffset));

    /* better to start/stop at the same time if possible, use a single write to limit delays between them */
    temp = ((MYD_GET_BOOL_AS_BIT(enableGenerator))<<1) | (MYD_GET_BOOL_AS_BIT(enableChecker));

    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, MYD_PKT_GEN_CONTROL1+regAddrOffset, 0, 2, temp));

    if ((pDev->devInfo[mdioPortIndex] & MYD_GEARBOX_MODE) && (enableGenerator == MYD_FALSE))
    {
        if (host_or_line == MYD_HOST_SIDE)
        {
           ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0x904D, 15, 1, 0));
        }
        else
        {
           ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xA04D, 15, 1, 0));
        }
    }

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydPktGeneratorCounterReset
    Reset packet generator counter
*******************************************************************************/
MYD_STATUS mydPktGeneratorCounterReset
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset
)
{
    MYD_U16 regAddrOffset=0;
    MYD_U16 modeType;
    MYD_U16 mdioPortIndex = MYD_GET_PORT_IDX(pDev, mdioPort);

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    if (host_or_line == MYD_HOST_SIDE)
    {
        modeType = pDev->hostConfig[mdioPortIndex][laneOffset].opModeType;
    }
    else 
    {
        modeType = pDev->lineConfig[mdioPortIndex][laneOffset].opModeType;
    }

    if (modeType != MYD_PCS)
    {
        MYD_DBG_ERROR("mydPktGeneratorCounterReset: not a PCS mode\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydGetPktGenRegOffset(pDev, mdioPort, host_or_line, laneOffset, &regAddrOffset));

    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, MYD_PKT_GEN_CONTROL1+regAddrOffset, 6, 1, 1));
    /* assumes delay is long enough to clear counters, this makes an assumption about the speed */
    /* of the MDIO as being relatively slow compared to the number of cycles it takes to clear the */
    /* clear the counters, relatively fast. may need a delay here for F2R, or really fast MDIO */
    /* speeds */
    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, MYD_PKT_GEN_CONTROL1+regAddrOffset, 6, 1, 0));

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydPktGeneratorGetCounter
    Get 64 bit packet generator counters
*******************************************************************************/
MYD_STATUS mydPktGeneratorGetCounter
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    IN MYD_U16  whichCounter,
    OUT MYD_U64 *packetCount,
    OUT MYD_U64 *byteCount
)
{
    MYD_U16 temp;
    MYD_U16 regAddrOffset=0;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydGetPktGenRegOffset(pDev, mdioPort, host_or_line, laneOffset, &regAddrOffset));

    *packetCount = *byteCount = 0;

    switch (whichCounter)
    {
        case MYD_PKT_GET_TX:
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PKT_GEN_TXPKTCTR1+regAddrOffset, &temp));
            *packetCount = temp;
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PKT_GEN_TXPKTCTR2+regAddrOffset, &temp));
            *packetCount |= (((MYD_U64)(temp))<<16);
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PKT_GEN_TXPKTCTR3+regAddrOffset, &temp));
            *packetCount |= (((MYD_U64)(temp))<<32);

            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PKT_GEN_TXBYTCTR1+regAddrOffset, &temp));
            *byteCount = temp;
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PKT_GEN_TXBYTCTR2+regAddrOffset, &temp));
            *byteCount |= (((MYD_U64)(temp))<<16);
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PKT_GEN_TXBYTCTR3+regAddrOffset, &temp));
            *byteCount |= (((MYD_U64)(temp))<<32);
            break;

        case MYD_PKT_GET_RX:
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PKT_GEN_RXPKTCTR1+regAddrOffset, &temp));
            *packetCount = temp;
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PKT_GEN_RXPKTCTR2+regAddrOffset, &temp));
            *packetCount |= (((MYD_U64)(temp))<<16);
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PKT_GEN_RXPKTCTR3+regAddrOffset, &temp));
            *packetCount |= (((MYD_U64)(temp))<<32);

            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PKT_GEN_RXBYTCTR1+regAddrOffset, &temp));
            *byteCount = temp;
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PKT_GEN_RXBYTCTR2+regAddrOffset, &temp));
            *byteCount |= (((MYD_U64)(temp))<<16);
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PKT_GEN_RXBYTCTR3+regAddrOffset, &temp));
            *byteCount |= (((MYD_U64)(temp))<<32);
            break;

        case MYD_PKT_GET_ERR:
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PKT_GEN_ERRPKTCTR1+regAddrOffset, &temp));
            *packetCount = temp;
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PKT_GEN_ERRPKTCTR2+regAddrOffset, &temp));
            *packetCount |= (((MYD_U64)(temp))<<16);
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_PKT_GEN_ERRPKTCTR3+regAddrOffset, &temp));
            *packetCount |= (((MYD_U64)(temp))<<32);
            break;

        default:
            MYD_DBG_ERROR("mydPktGeneratorGetCounter: incorrect counter selection: %u\n", whichCounter);
            return MYD_FAIL;
            break;
    }

    return MYD_OK;
}
/***************************** PRBS Control/Status/Counters *******************/

/* Bit Positions for PRBS Control/Status */
#define PRBS_READ_CLEAR_BIT  13
#define PRBS_LOCKED_BIT       8
#define PRBS_WAIT_LOCK_BIT    7
#define PRBS_CTR_RESET_BIT    6
#define PRBS_TX_EN_BIT        5
#define PRBS_RX_EN_BIT        4
#define PRBS_PATTERN_SEL_BIT  0 /* 4-bit field */

#define PRBS_LANE_OFFSET       0x10 /* offset between PRBS control registers by lane */ 
#define PRBS_PAM4_LANE_OFFSET  0x2000 /* offset between PAM4 PRBS control registers by lane */ 

#define JP03A_PATT       0x0303 /* defines for PRBS 0 Test Pattern A/B */
#define JP03B_PATT       0x3030
#define LOWF_A_PATT      0xFFF0
#define LOWF_B_PATT      0x000F
#define SQ_A_PATT        0xFFFF
#define SQ_B_PATT        0x0000
#define MF_A_PATT        0xFCCF
#define MF_B_PATT        0x0330

/*******************************************************************************
 MYD_STATUS mydSetPRBSPattern
    Selects the host or line side PRBS pattern
*******************************************************************************/
MYD_STATUS mydSetPRBSPattern
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,    
    IN MYD_U16  laneOffset,
    IN MYD_PRBS_SELECTOR_TYPE pattSel,
    IN MYD_PATTERN_AB_SELECTOR_TYPE pattSubSel
)
{
    MYD_U16 prbsControlRegAddr;
    MYD_U16 prbsTestPattARegAddr;
    MYD_U16 prbsTestPattBRegAddr;
    MYD_U16 tempRegVal;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    if (pattSel <= MYD_GEN_TX)  /* NRZ PRBS settings */
    {
        prbsControlRegAddr   = (MYD_PRBS_CONTROL+laneOffset*PRBS_LANE_OFFSET);
        prbsTestPattARegAddr = (MYD_PRBS0_TEST_PATTA+laneOffset*PRBS_LANE_OFFSET);
        prbsTestPattBRegAddr = (MYD_PRBS0_TEST_PATTB+laneOffset*PRBS_LANE_OFFSET);

        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, prbsControlRegAddr, PRBS_PATTERN_SEL_BIT, 4, (MYD_U16)pattSel));

        switch (pattSel)
        {
            case MYD_JP03AB:
                switch (pattSubSel)
                {
                    case MYD_JP03A:
                        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, prbsTestPattARegAddr, JP03A_PATT));
                        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, prbsTestPattBRegAddr, JP03A_PATT));
                        break;

                    case MYD_JP03B:
                        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, prbsTestPattARegAddr, JP03B_PATT));
                        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, prbsTestPattBRegAddr, JP03B_PATT));
                        break;

                    default:
                        MYD_DBG_ERROR("mydSetPRBSPattern: incorrect pattSubSel: %u\n", pattSubSel);
                        return MYD_FAIL;
                        break;
                }
                break;

            case MYD_GEN_TX:
                switch (pattSubSel)
                {
                    case MYD_LOW_FREQ:
                        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, prbsTestPattARegAddr, LOWF_A_PATT));
                        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, prbsTestPattBRegAddr, LOWF_B_PATT));
                        break;

                    case MYD_SQUARE_WAV:
                        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, prbsTestPattARegAddr, SQ_A_PATT));
                        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, prbsTestPattBRegAddr, SQ_B_PATT));
                        break;

                    case MYD_MIXED_FREQ:
                        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, prbsTestPattARegAddr, MF_A_PATT));
                        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, prbsTestPattBRegAddr, MF_B_PATT));                    
                        break;

                    default:
                        MYD_DBG_ERROR("mydSetPRBSPattern: incorrect pattSubSel: %u\n", pattSubSel);
                        return MYD_FAIL;
                        break;
                }
                break;

            default:
                /* all other cases do nothing, 3.F1XA and 3.F1XB don't matter, pattSubSel is ignored */
                break;
        }
    }
    else
    {
        /* PAM-4 PRBS settings */
        if (host_or_line == MYD_HOST_SIDE)
        {
            prbsControlRegAddr   = (MYD_IEEE_HOST_PRBS_CONTROL + laneOffset*PRBS_PAM4_LANE_OFFSET);
        }
        else
        {
            prbsControlRegAddr   = (MYD_IEEE_LINE_PRBS_CONTROL + laneOffset*PRBS_PAM4_LANE_OFFSET);
        }

        switch(pattSel)
        {
            case MYD_PAM4_PRBS31Q:
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, prbsControlRegAddr, &tempRegVal));
                tempRegVal &= 0x9C3F;
                tempRegVal |= 0x2000; /* bit 13 */;
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_PMA_DEV, prbsControlRegAddr, tempRegVal));
                break;

            case MYD_PAM4_JP03A:
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, prbsControlRegAddr, &tempRegVal));
                tempRegVal &= 0x9C3F;
                tempRegVal |= 0x100; /* bit 8 */;
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_PMA_DEV, prbsControlRegAddr, tempRegVal));
                break;

            case MYD_PAM4_JP03B:
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, prbsControlRegAddr, &tempRegVal));
                tempRegVal &= 0x9C3F;
                tempRegVal |= 0x200; /* bit 9 */;
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_PMA_DEV, prbsControlRegAddr, tempRegVal));
                break;

            case MYD_PAM4_SSPRQ:
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, prbsControlRegAddr, &tempRegVal));
                tempRegVal &= 0x9C3F;
                tempRegVal |= 0x4000; /* bit 14 */;
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_PMA_DEV, prbsControlRegAddr, tempRegVal));
                break;

            case MYD_PAM4_PRBS13Q:
            {
                MYD_U16 prbs13QReg = (host_or_line == MYD_HOST_SIDE)? 0x15E8:0x05E8;

                ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, prbs13QReg, (MYD_U8)laneOffset, 1, 1));
                break;
            }
            case MYD_PAM4_PRBS15Q:
                /* No action needed; MYD_PAM4_PRBS15Q start/stop transmission on mydSetPRBSEnableTxRx */
                break;

            default:
                MYD_DBG_ERROR("mydSetPRBSPattern: incorrect pattSel: %u\n", pattSel);
                return MYD_FAIL;
                break;
        }
    }

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydSetPRBSEnableTxRx
    Controls the transmit and receive
*******************************************************************************/
MYD_STATUS mydSetPRBSEnableTxRx
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,    
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    IN MYD_U16  txEnable,
    IN MYD_U16  rxEnable,
    IN MYD_PRBS_SELECTOR_TYPE pattSel
)
{
    MYD_U16 temp;
    MYD_U16 prbsControlRegAddr=(MYD_PRBS_CONTROL+laneOffset*PRBS_LANE_OFFSET);
    
    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    if (pattSel <= MYD_GEN_TX)
    {
        prbsControlRegAddr = (MYD_PRBS_CONTROL+laneOffset*PRBS_LANE_OFFSET);

        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, prbsControlRegAddr, &temp));
        ATTEMPT(mydHwSetRegFieldToWord(temp, txEnable, PRBS_TX_EN_BIT, 1, &temp));
        ATTEMPT(mydHwSetRegFieldToWord(temp, rxEnable, PRBS_RX_EN_BIT, 1, &temp));
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, prbsControlRegAddr, temp));
    }
    else if(pattSel == MYD_PAM4_PRBS15Q)
    {
        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, (0xF142+(laneOffset*0x10)), 1, 1, txEnable));

        if (rxEnable) /* lane reset to disable Rx */
        {
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, (0xF142+(laneOffset*0x10)), 0, 1, 1));
        }
    }
    else
    {
        if (host_or_line == MYD_HOST_SIDE)
        {
            prbsControlRegAddr   = (MYD_IEEE_HOST_PRBS_CONTROL + laneOffset*PRBS_PAM4_LANE_OFFSET);
        }
        else
        {
            prbsControlRegAddr   = (MYD_IEEE_LINE_PRBS_CONTROL + laneOffset*PRBS_PAM4_LANE_OFFSET);
        }

        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, prbsControlRegAddr, 3, 1, txEnable));
        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, prbsControlRegAddr, 0, 1, rxEnable));
    }
        
    return MYD_OK;
}


/*******************************************************************************
 MYD_STATUS mydPRBSCounterReset
    Resets the PRBS counter when it's been set to manual reset and not clear-on-
    read
*******************************************************************************/
MYD_STATUS mydPRBSCounterReset
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,    
    IN MYD_U16  host_or_line,    
    IN MYD_U16  laneOffset
)
{
    MYD_U16 prbsControlRegAddr=(MYD_PRBS_CONTROL+laneOffset*PRBS_LANE_OFFSET);

    /* this is a diagnostic function. limited error checking is done. */
    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, prbsControlRegAddr, PRBS_CTR_RESET_BIT, 1, 1));
        
    return MYD_OK;
}


/*******************************************************************************
 MYD_STATUS mydSetPRBSWaitForLock
    Makes the receiver start counting right away, even before it's locked 
    on the pattern
*******************************************************************************/
MYD_STATUS mydSetPRBSWaitForLock
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,    
    IN MYD_U16  host_or_line,    
    IN MYD_U16  laneOffset,
    IN MYD_U16  disableWaitforLock
)
{
    MYD_U16 prbsControlRegAddr=(MYD_PRBS_CONTROL+laneOffset*PRBS_LANE_OFFSET);

    /* this is a diagnostic function. limited error checking is done. */
    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, prbsControlRegAddr, PRBS_WAIT_LOCK_BIT, 1, disableWaitforLock));
        
    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydGetPRBSWaitForLock
    Gets the value of the control bit that sets whether the counters start
    right away, or wait until the receiver is locked.
*******************************************************************************/
MYD_STATUS mydGetPRBSWaitForLock
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,    
    IN MYD_U16  host_or_line,    
    IN MYD_U16  laneOffset,
    OUT MYD_U16 *disableWaitforLock
)
{
    MYD_U16 prbsControlRegAddr=(MYD_PRBS_CONTROL+laneOffset*PRBS_LANE_OFFSET);

    /* this is a diagnostic function. limited error checking is done. */
    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, prbsControlRegAddr, PRBS_WAIT_LOCK_BIT, 1, disableWaitforLock));
        
    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydSetPRBSClearOnRead
    Sets the bit that controls whether the counters clear when read or
    clear manually by setting a bit.
*******************************************************************************/
MYD_STATUS mydSetPRBSClearOnRead
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,    
    IN MYD_U16  host_or_line,    
    IN MYD_U16  laneOffset,
    IN MYD_U16  enableReadClear
)
{
    MYD_U16 prbsControlRegAddr=(MYD_PRBS_CONTROL+laneOffset*PRBS_LANE_OFFSET);

    /* this is a diagnostic function. limited error checking is done. */
    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, prbsControlRegAddr, PRBS_READ_CLEAR_BIT, 1, enableReadClear));
        
    return MYD_OK;
}


/*******************************************************************************
 MYD_STATUS mydGetPRBSClearOnRead
    Reads the bit setting that controls whether the counters clear when read or
    clear manually by setting a bit.
*******************************************************************************/
MYD_STATUS mydGetPRBSClearOnRead
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,    
    IN MYD_U16  host_or_line,    
    IN MYD_U16  laneOffset,
    OUT MYD_U16  *enableReadClear
)
{
    MYD_U16 prbsControlRegAddr=(MYD_PRBS_CONTROL+laneOffset*PRBS_LANE_OFFSET);

    /* this is a diagnostic function. limited error checking is done. */
    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, prbsControlRegAddr, PRBS_READ_CLEAR_BIT, 1, enableReadClear));
        
    return MYD_OK;
}


/*******************************************************************************
 MYD_STATUS mydGetPRBSLocked
    Reads the status bit that indicates if the receiver is locked onto the
    PRBS pattern or not.
*******************************************************************************/
MYD_STATUS mydGetPRBSLocked
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    OUT MYD_BOOL *prbsLocked
)
{
    MYD_U16 prbsControlRegAddr=(MYD_PRBS_CONTROL+laneOffset*PRBS_LANE_OFFSET);
    MYD_U16 temp = 0;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, prbsControlRegAddr, 
            PRBS_LOCKED_BIT, 1, &temp));
    
    *prbsLocked = (temp == 0) ? MYD_FALSE:MYD_TRUE;

    return MYD_OK;
}


/*******************************************************************************
 MYD_STATUS mydGetPRBSCounts
    Reads the counters. Will clear the counters if they've been setup to
    clear-on-read.
*******************************************************************************/
MYD_STATUS mydGetPRBSCounts
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,    
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    IN MYD_PRBS_SELECTOR_TYPE pattSel,
    OUT MYD_U64 *txBitCount,
    OUT MYD_U64 *rxBitCount,
    OUT MYD_U64 *rxBitErrorCount
)
{
    MYD_U16 prbsTxCountReg, prbsRxCountReg, prbsErrCountReg,
            lowTxWord, lowRxWord, lowErrWord,
            midWord, hiWord;

    /* initialize values, in case of error return 0 */
    *txBitCount = *rxBitCount = *rxBitErrorCount = 0;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    prbsTxCountReg  = MYD_PRBS_SYM_TXCTR1  + laneOffset*PRBS_LANE_OFFSET;
    prbsRxCountReg  = MYD_PRBS_SYM_RXCTR1  + laneOffset*PRBS_LANE_OFFSET;
    prbsErrCountReg = MYD_PRBS_SYM_ERRCTR1 + laneOffset*PRBS_LANE_OFFSET;

    /* must read low words first to latch the upper two words */

    /* read tx count lower/mid/upper */
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, prbsTxCountReg, &lowTxWord));
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, prbsTxCountReg+1, &midWord));
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, prbsTxCountReg+2, &hiWord));
    *txBitCount = lowTxWord + (((MYD_U64)(midWord))<<16) + (((MYD_U64)(hiWord))<<32);

    /* read rx count lower/mid/upper */
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, prbsRxCountReg, &lowRxWord));
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, prbsRxCountReg+1, &midWord));
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, prbsRxCountReg+2, &hiWord));
    *rxBitCount = lowRxWord + (((MYD_U64)(midWord))<<16) + (((MYD_U64)(hiWord))<<32);

    /* read err count lower/mid/upper */
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, prbsErrCountReg, &lowErrWord));
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, prbsErrCountReg+1, &midWord));
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, prbsErrCountReg+2, &hiWord));
    *rxBitErrorCount = lowErrWord + (((MYD_U64)(midWord))<<16) + (((MYD_U64)(hiWord))<<32);

    return MYD_OK;
}


/*******************************************************************************
 MYD_STATUS mydSetTxPolarity
*******************************************************************************/
MYD_STATUS mydSetTxPolarity
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,     
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 polarity,
    IN MYD_U16 swReset
)
{
    MYD_U16 temp;

    /* this is a diagnostic function. limited error checking is done. */
    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    if (polarity > 1)
    {
        MYD_DBG_ERROR("mydSetTxPolarity: polarity:%u is invalid (1-inverted; 0-non-inverted)\n", polarity);
        return MYD_FAIL;
    }

    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_SERDES_LANE0_REG_B+(0x80*laneOffset), &temp));
    temp &= ~0x5000; 
    temp |= polarity ? 0x5200: 0x0000;
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_SERDES_LANE0_REG_B+(0x80*laneOffset), temp));

    if (swReset)
    {
        ATTEMPT(mydLaneSoftReset(pDev, mdioPort, host_or_line, laneOffset, MAX_RESET_WAIT));
    }

    MYD_DBG_INFO("mydSetTxPolarity: polarity:%u\n", polarity);

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydGetTxPolarity
*******************************************************************************/
MYD_STATUS mydGetTxPolarity
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,     
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *polarity
)
{
    /* this is a diagnostic function. limited error checking is done. */
    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, MYD_SERDES_LANE0_REG_B+(0x80*laneOffset),
                                12, 1, polarity));  

    MYD_DBG_INFO("mydGetTxPolarity: polarity:%u\n", *polarity);

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydSetRxPolarity
*******************************************************************************/
MYD_STATUS mydSetRxPolarity
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,     
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 polarity,
    IN MYD_U16 swReset
)
{
    MYD_U16 temp;

    /* this is a diagnostic function. limited error checking is done. */
    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    if (polarity > 1)
    {
        MYD_DBG_ERROR("mydSetRxPolarity: polarity:%u is invalid (1-inverted; 0-non-inverted)\n", polarity);
        return MYD_FAIL;
    }

    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_SERDES_LANE0_REG_B+(0x80*laneOffset), &temp));
    temp &= ~0xA000; 
    temp |= polarity ? 0xA200: 0x0000;
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_SERDES_LANE0_REG_B+(0x80*laneOffset), temp));

    if (swReset)
    {
        ATTEMPT(mydLaneSoftReset(pDev, mdioPort, host_or_line, laneOffset, MAX_RESET_WAIT));
    }

    MYD_DBG_INFO("mydSetRxPolarity: polarity:%u\n", polarity);

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydGetRxPolarity
*******************************************************************************/
MYD_STATUS mydGetRxPolarity
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,     
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *polarity
)
{
    /* this is a diagnostic function. limited error checking is done. */
    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, MYD_SERDES_LANE0_REG_B+(0x80*laneOffset),
                                13, 1, polarity));  

    MYD_DBG_INFO("mydGetRxPolarity: polarity:%u\n", *polarity);

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydDiagStateDump
*******************************************************************************/
MYD_STATUS mydDiagStateDump
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort, 
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U32 stateDumpOptions,
    OUT PMYD_STATE_DUMP pStateDumpInfo
)
{
    MYD_SPEED speed;
    MYD_U16 mdioPortIndex = MYD_GET_PORT_IDX(pDev, mdioPort);
    MYD_U16 sAddr, regCntlPCS, regStatusPCS, controlANEGReg;     
    MYD_BOOL speedSet = MYD_TRUE;

    /* this is a diagnostic function. limited error checking is done. */
    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    mydMemCpy(&pStateDumpInfo->devStuct, &pDev, (sizeof(MYD_DEV))); 
    ATTEMPT(mydSerdesGetRevision(pDev, mdioPort, &pStateDumpInfo->serdesRevision, &pStateDumpInfo->sbmRevision));
    ATTEMPT(mydSerdesGetTemperature(pDev, mdioPort, &pStateDumpInfo->coreTemperature));
    ATTEMPT(mydSerdesGetVoltage(pDev, mdioPort, &pStateDumpInfo->voltageCore, &pStateDumpInfo->voltageDVDD, \
                                &pStateDumpInfo->voltageAVDD));

    speed = pDev->lineConfig[mdioPortIndex][laneOffset].speed;

    if (host_or_line == MYD_HOST_SIDE)
    {
        speed = pDev->hostConfig[mdioPortIndex][laneOffset].speed;
    }
    else
    {
        speed = pDev->lineConfig[mdioPortIndex][laneOffset].speed;
    }

    switch (speed)
    {
        case MYD_1GB:
        case MYD_2P5GB:
            regCntlPCS = MYD_PCS_1G_CNTL_LANE(laneOffset);
            regStatusPCS = MYD_PCS_1G_STATUS+(0x200*laneOffset);
            break;

        case MYD_5GB:
        case MYD_10GB:
        case MYD_25GB:
            regCntlPCS = MYD_PCS_25G_CNTL_LANE(laneOffset);
            regStatusPCS = MYD_PCS_25G_STATUS+(0x200*laneOffset);
            break;

        case MYD_40GB:
        case MYD_50GB:
            regCntlPCS = MYD_PCS_40G_CNTL_LANE(laneOffset);
            regStatusPCS = MYD_PCS_40G_STATUS1+(0x200*laneOffset);
            break;

        case MYD_100GB:
            regCntlPCS = MYD_PCS_100G_CNTL_LANE(laneOffset);
            regStatusPCS = MYD_PCS_100G_STATUS1+(0x200*laneOffset);
            break;

        case MYD_200GB:
        case MYD_400GB:
            regCntlPCS = MYD_PCS_200G_CNTL;
            regStatusPCS = MYD_PCS_200G_STATUS1;
            break;

        default:
            MYD_DBG_INFO("mydDiagStateDump: incorrect speed selection: %d\n", (MYD_U16)speed);
            speedSet = MYD_FALSE;
            break;
    }

    if (speedSet)
    {
        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, regCntlPCS, &pStateDumpInfo->cntlPCSReg));
        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, regStatusPCS, &pStateDumpInfo->statusPCSReg));
    }

    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, (MYD_MODE_SELECTION+laneOffset), \
                           &pStateDumpInfo->modeSelectReg));

    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF050+(laneOffset*0x3), &pStateDumpInfo->powerMgmtStateReg));
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF204+(laneOffset*0x80), &pStateDumpInfo->serdesStateReg));

    if (host_or_line == MYD_HOST_SIDE)
    {
        sAddr = MYD_MAPPED_SERDES_ID(mdioPortIndex, MYD_HOST_MODE_IDX, laneOffset);
        controlANEGReg = MYD_AUTONEG_CTRL_REG_HOST+(0x0200*laneOffset);
    }
    else
    {
        sAddr = MYD_MAPPED_SERDES_ID(mdioPortIndex, MYD_LINE_MODE_IDX, laneOffset);
        controlANEGReg = MYD_AUTONEG_CTRL_REG_LINE+(0x0200*laneOffset);
    }

    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_AUTONEG, controlANEGReg, &pStateDumpInfo->controlANEGReg));

    MYD_DBG_INFO("PCS Control Register    :0x%04X:0x%04X\n", regCntlPCS, pStateDumpInfo->cntlPCSReg);
    MYD_DBG_INFO("PCS Status Register     :0x%04X:0x%04X\n", regStatusPCS, pStateDumpInfo->statusPCSReg);
    MYD_DBG_INFO("Mode Selection Register :0x%04X:0x%04X\n", (MYD_MODE_SELECTION+laneOffset), pStateDumpInfo->modeSelectReg);
    MYD_DBG_INFO("AutoNeg Control Register:0x%04X:0x%04X\n", controlANEGReg, pStateDumpInfo->controlANEGReg);
    MYD_DBG_INFO("PowerMgmt State Register:0x%04X:0x%04X\n", 0xF050+(laneOffset*0x3), pStateDumpInfo->powerMgmtStateReg);
    MYD_DBG_INFO("Serdes State Register   :0x%04X:0x%04X\n", 0xF204+(laneOffset*0x80), pStateDumpInfo->serdesStateReg);

#if MYD_ENABLE_SERDES_API
    {
        MYD_SER_DEV_PTR pSerdesDev;
        MYD_U16 index;     

        pSerdesDev = (MYD_SER_DEV_PTR)pDev->serdesDev[MYD_MAPPED_PORT_IDX(sAddr)];

        for (index = 8; index < 11; index++)
        {
            pStateDumpInfo->params[index-8] = (MYD_U16)mydWrapperSerdesInt(pSerdesDev, sAddr, 0x2C | (0x0 << 6), 
                                                                                ((0x1 & 0xFF) <<8) | (index & 0xFF));

            MYD_DBG_INFO("Param[%u]:0x%04X\n", index-8, pStateDumpInfo->params[index-8]);
        }
        pStateDumpInfo->params[3] = (MYD_U16)mydWrapperSerdesInt(pSerdesDev, sAddr, 0x2C | (0x0 << 6), 
                                                                      ((0x1 & 0xFF) <<8) | (0xD & 0xFF));
        MYD_DBG_INFO("Param[3]:0x%04X\n", pStateDumpInfo->params[3]);
    
        for (index = 5; index < 15; index++)
        {
            pStateDumpInfo->clkList[index-5] = (MYD_U16)mydWrapperSerdesInt(pSerdesDev, sAddr, 0x2C | (0x0 << 6), 
                                                                           ((0x3 & 0xFF) <<8) | (index & 0xFF));
            MYD_DBG_INFO("clkList[%u]:0x%04X\n", index-5, pStateDumpInfo->clkList[index-5]);
        }

        ATTEMPT(mydSerdesGetTxFFE(pDev, sAddr,  &pStateDumpInfo->txFFE.preCursor, &pStateDumpInfo->txFFE.pre2Cursor, \
                                  &pStateDumpInfo->txFFE.pre3Cursor, &pStateDumpInfo->txFFE.attenuation, \
                                  &pStateDumpInfo->txFFE.postCursor));

        ATTEMPT(mydSerdesGetStateDump(pDev, sAddr));
    }
#endif

    return MYD_OK;
}
