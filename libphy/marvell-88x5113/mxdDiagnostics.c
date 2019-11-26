/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions and global data for higher-level functions 
using MDIO access to enable test modes, loopbacks, and other diagnostic 
functions of the Marvell X5113 PHY.
********************************************************************/
#include "mxdApiTypes.h"
#include "mxdUtils.h"
#include "mxdHwCntl.h"
#include "mxdAPI.h"
#include "mxdApiRegs.h"
#include "mxdDiagnostics.h"
#include "mxdAPIInternal.h"
#include "mxdHwSerdesCntl.h"

#define MXD_MARVELL_OUI  0x2B02
#define MXD_MODEL_X5113  0x3F
#define MAX_RESET_WAIT   1000

#define MXD_CHIP_X5113     0x0 
#define MXD_CHIP_EC055_25G 0x1
#define MXD_CHIP_EC055_10G 0x2

/*******************************************************************************
 MXD_STATUS mxdGetChipRevision
*******************************************************************************/
MXD_STATUS mxdGetChipRevision
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    OUT MXD_DEVICE_ID *deviceId
)
{
    MXD_U16 oui;
    MXD_U16 deviceModel;
    MXD_U16 chipData1, chipData2;

    MXD_STATUS retVal = MXD_OK;
    
    ATTEMPT(mxdHwGetPhyRegField(pDev, pDev->mdioPort, MXD_CHIP_REG, 0xF411, 4, 2, &deviceModel));

    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_LINE_SIDE, MXD_PCS_40G_DEV_ID1, &chipData1));
    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_LINE_SIDE, MXD_PCS_40G_DEV_ID2, &chipData2));

    oui = ((chipData1<<8 & 0xFF00) | ((chipData2 & 0xFC00)>>10)) ;
    if (oui != MXD_MARVELL_OUI)
    {
        MXD_DBG_ERROR("mxdGetChipRevision: incorrect OUI: 0x%x\n", oui);
        return MXD_FAIL;
    }

    switch(deviceModel)
    {
        case MXD_CHIP_X5113:
            pDev->deviceId = MXD_DEV_X5113;
            *deviceId = MXD_DEV_X5113;
            break;

        case MXD_CHIP_EC055_10G:
        case MXD_CHIP_EC055_25G:
            pDev->deviceId = MXD_DEV_EC055;
            *deviceId = MXD_DEV_EC055;
            break;

        default:
            pDev->deviceId = MXD_DEV_UNKNOWN;
            *deviceId = MXD_DEV_UNKNOWN;
            MXD_DBG_ERROR("mxdGetChipRevision: incorrect device model: 0x%x\n", deviceModel);
            return MXD_FAIL;
    }

    switch(chipData2 & 0x0007)
    {
        case MXD_REV_A0:
            pDev->chipRevision = MXD_REV_A0;
            break;

        case MXD_REV_A1:
            pDev->chipRevision = MXD_REV_A1;
            break;

         default:
            pDev->chipRevision = MXD_REV_UNKNOWN;
            MXD_DBG_ERROR("mxdGetChipRevision: incorrect device revision model: 0x%x\n", (chipData2 & 0x0007));
            return MXD_FAIL;
            break;
   }

    return retVal;
}

/*******************************************************************************
 MXD_STATUS mxdGetChipFWRevision
   Revision in <major>.<minor> format
*******************************************************************************/
MXD_STATUS mxdGetChipFWRevision
(
    IN MXD_DEV_PTR pDev,
    OUT MXD_U16 *major,
    OUT MXD_U16 *minor
)
{
    ATTEMPT(mxdHwGetPhyRegField(pDev, pDev->mdioPort, MXD_CHIP_REG, 0xF408, 8, 7, major));
    ATTEMPT(mxdHwGetPhyRegField(pDev, pDev->mdioPort, MXD_CHIP_REG, 0xF408, 0, 8, minor));

    if ((*major == 0) && (*minor == 0))
    {
        MXD_DBG_ERROR("mxdGetChipFWRevision: Chip firmware revision number not available\n");
        return MXD_FAIL;
    }

    MXD_DBG_INFO("mxdGetChipFWRevision: v%u.%u\n", *major, *minor);

    return MXD_OK;
}


/*******************************************************************************
 MXD_STATUS mxdGetSerdesSignalDetectAndDspLock
    Return value of signal detect and DSP lock for corresponding lane.
*******************************************************************************/
MXD_STATUS mxdGetSerdesSignalDetectAndDspLock
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,    
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U16 *signalDetect,
    OUT MXD_U16 *dspLock
)
{
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdGetSerdesSignalDetectAndDspLock: device not initialized\n");
        return MXD_FAIL;
    }

     ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    if (!(host_or_line == MXD_HOST_SIDE || host_or_line == MXD_LINE_SIDE))
    {
        MXD_DBG_ERROR("mxdGetSerdesSignalDetectAndDspLock: host_or_line is invalid\n");
        return MXD_FAIL;
    }
        
    ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0+(0x80*laneOffset), 5, 1, dspLock));
    ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0+(0x80*laneOffset), 7, 1, signalDetect));

    return MXD_OK;    
}

/*******************************************************************************
 MXD_STATUS mxdSetLineLoopback
    Enable/Disable line side loopbacks
*******************************************************************************/
MXD_STATUS mxdSetLineLoopback
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 laneOffset,
    IN MXD_U16 loopback_type,
    IN MXD_U16 enable
)
{
    MXD_U16 regAddrPCS,regAddrPMA;
    MXD_SPEED lineSpeed;
    MXD_PCS_TYPE pcsType;
    MXD_U16 autoNeg, gearboxMode=0;
    MXD_OP_CONFIG hostMode;

    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdSetLineLoopback: device not initialized\n");
        return MXD_FAIL;
    }
    
    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    ATTEMPT(mxdGetModeSpeed(pDev, mdioPort, MXD_LINE_SIDE, laneOffset, &lineSpeed, &pcsType));

    if (pcsType != MXD_PCS)
    {
        MXD_DBG_ERROR("mxdSetLineLoopback: not a PCS mode\n");
        return MXD_FAIL;
    }

    if (pDev->devInfo & MXD_GEARBOX_MODE)
    {
        gearboxMode = 1;
    }

    hostMode = pDev->hostConfig[laneOffset].opConfig;
    autoNeg = portConfigTbl[hostMode][AUTONEG_IDX];

    switch (lineSpeed)
    {
        case MXD_1GB:
        case MXD_2_5GB:
            regAddrPCS = MXD_PCS_1G_CNTL_LANE(laneOffset);
            regAddrPMA = MXD_PMA_HOST_100G_CNTL_LANE(laneOffset);
            break;

        case MXD_5GB:
        case MXD_10GB:
        case MXD_25GB:
            regAddrPCS = MXD_PCS_25G_CNTL_LANE(laneOffset);
            regAddrPMA = MXD_PMA_HOST_100G_CNTL_LANE(laneOffset);            
            break;

        case MXD_40GB:
        case MXD_50GB:
            regAddrPCS = MXD_PCS_40G_CNTL;
            regAddrPMA = MXD_PMA_HOST_100G_CNTL;
            laneOffset = 0;
            break;

        case MXD_100GB:
            regAddrPCS = MXD_PCS_100G_CNTL;
            regAddrPMA = MXD_PMA_HOST_100G_CNTL;
            laneOffset = 0;
            break;

        default:
            MXD_DBG_ERROR("mxdSetLineLoopback: incorrect speed selection: %d\n", (int)lineSpeed);
            return MXD_FAIL;                            
            break;
    }

    if (enable > 1)
    {
        enable = 1;
    }

    switch(loopback_type)
    {
        case MXD_SHALLOW_PCS_LB:

            /* BEFORE */

            /* Enable/Disable loopback */
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort,MXD_LINE_SIDE,MXD_PORT_PCS_CNTL,(MXD_U8)(12+laneOffset),1,enable));
            
            /* AFTER */
            if (gearboxMode == 1)
            {
                if (enable == 1)
                {
                    /* Disable Resetting FIFO based on other side PCS RX reset*/
                    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort,MXD_LINE_SIDE,0xF0C0,12,4,0xE));
                }
                else
                {
                    /* Enable Resetting FIFO based on other side PCS RX reset*/
                    ATTEMPT(mxdHwSetPhyRegField(pDev,mdioPort,MXD_LINE_SIDE,0xF0C0,12,4,0x7));
                    /*Reset RMFIFO */
                    ATTEMPT(mxdHwSetPhyRegField(pDev,mdioPort,MXD_PORT_REG,0xF602,0,2,0x3));
                    /*Release RMFIFO Reset*/
                    ATTEMPT(mxdHwSetPhyRegField(pDev,mdioPort,MXD_PORT_REG,0xF602,0,2,0x0));
                }
            }
            break;

        case MXD_DEEP_PCS_LB:
            ATTEMPT(mxdSetDeepPCSLoopback(pDev, mdioPort, laneOffset, MXD_HOST_SIDE, 
                                          gearboxMode, autoNeg, lineSpeed, regAddrPCS, enable));
            break;

        case MXD_DEEP_PMA_LB:
            /* Line side deep loopback happens at the Host side, vice versa */
            if (lineSpeed != MXD_100GB)
            {
                /* Enable/Disable PMA loopback */
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, regAddrPMA, 0, 1, enable));
                if (gearboxMode == 1)
                {
                    /* Disable(1)/Enable(0) FIFO reset when other side's rx is not ready */
                    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_HOST_SIDE, 0x904D, 15, 1, enable));
                }
                if (autoNeg == 1)
                {
                    /* Enable/Disable overridding nonce match to Disable/Enable nonce match */
                    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, 0x9001+(laneOffset*0x200), 10, 1, enable));
                }
            }
            else if (lineSpeed == MXD_100GB)
            {
                ATTEMPT(mxdSetDeepPMALoopback100G(pDev, mdioPort, MXD_HOST_SIDE, autoNeg, enable));
            }
            break;
        default:
            MXD_DBG_ERROR("mxdSetLineLoopback: incorrect loopback selection: %u\n", loopback_type);
            return MXD_FAIL;
            break;
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdSetHostLoopback
    Enable/Disable host side loopbacks
*******************************************************************************/
MXD_STATUS mxdSetHostLoopback
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 laneOffset,
    IN MXD_U16 loopback_type,
    IN MXD_U16 enable
)
{
    MXD_U16 regAddrPCS,regAddrPMA;
    MXD_SPEED hostSpeed;
    MXD_PCS_TYPE pcsType;
    MXD_U16 autoNeg, gearboxMode=0;
    MXD_OP_CONFIG lineMode;

    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdSetHostLoopback: device not initialized\n");
        return MXD_FAIL;
    }
    
    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    ATTEMPT(mxdGetModeSpeed(pDev, mdioPort, MXD_HOST_SIDE, laneOffset, &hostSpeed, &pcsType));
    
    if (pcsType != MXD_PCS)
    {
        MXD_DBG_ERROR("mxdSetHostLoopback: not a PCS mode\n");
        return MXD_FAIL;
    }

    if (pDev->devInfo & MXD_GEARBOX_MODE)
    {
        gearboxMode = 1;
    }

    lineMode = pDev->lineConfig[laneOffset].opConfig;
    autoNeg = portConfigTbl[lineMode][AUTONEG_IDX];

    switch (hostSpeed)
    {
        case MXD_1GB:
        case MXD_2_5GB:
            regAddrPCS = MXD_PCS_1G_CNTL_LANE(laneOffset);
            regAddrPMA = MXD_PMA_100G_CNTL_LANE(laneOffset);
            break;

        case MXD_5GB:
        case MXD_10GB:
        case MXD_25GB:
            regAddrPCS = MXD_PCS_25G_CNTL_LANE(laneOffset);
            regAddrPMA = MXD_PMA_100G_CNTL_LANE(laneOffset);
            break;

        case MXD_40GB:
        case MXD_50GB:
            regAddrPCS = MXD_PCS_40G_CNTL;
            regAddrPMA = MXD_PMA_100G_CNTL;
            laneOffset = 0;
            break;

        case MXD_100GB:
            regAddrPCS = MXD_PCS_100G_CNTL;
            regAddrPMA = MXD_PMA_100G_CNTL;
            laneOffset = 0;
            break;

        default:
            MXD_DBG_ERROR("mxdSetHostLoopback: incorrect speed selection: %d\n", (int)hostSpeed);
            return MXD_FAIL;                            
            break;
    }

    if (enable > 1)
    {
        enable = 1;
    }

    switch(loopback_type)
    {
        case MXD_SHALLOW_PCS_LB:

            /* BEFORE */

            ATTEMPT(mxdHwSetPhyRegField(pDev,mdioPort,MXD_HOST_SIDE,MXD_PORT_PCS_CNTL,(MXD_U8)(12+laneOffset),1,enable));
            
            /* AFTER */
            if ((gearboxMode == 1) && (enable == 0))
            {
                /*Reset RMFIFO */
                ATTEMPT(mxdHwSetPhyRegField(pDev,mdioPort,MXD_PORT_REG,0xF602,0,2,0x3));
                /*Release RMFIFO Reset*/
                ATTEMPT(mxdHwSetPhyRegField(pDev,mdioPort,MXD_PORT_REG,0xF602,0,2,0x0));
            }
            break;

        case MXD_DEEP_PCS_LB:
            ATTEMPT(mxdSetDeepPCSLoopback(pDev, mdioPort, laneOffset, MXD_LINE_SIDE, 
                                          gearboxMode, autoNeg, hostSpeed, regAddrPCS, enable));
            break;

        case MXD_DEEP_PMA_LB:
            /* Host side deep loopback happens at the Line side, vice versa */
            if (hostSpeed != MXD_100GB)
            {
                /* Enable/Disable PMA loopback */
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, regAddrPMA, 0, 1, enable));
                if (gearboxMode == 1)
                {
                    if (enable)
                    {
                        /* Change TX FIFO Clock select to 25G Line Loopback */
                        ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_LINE_SIDE, 0xF0C0, 12, 4, 0xE));
                    }
                    else
                    {
                        /* Change TX FIFO Clock select to 25G pktgen or rmfifo */
                        ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_LINE_SIDE, 0xF0C0, 12, 4, 0x7));
                    }
                }
                if (autoNeg == 1)
                {
                    /* Enable/Disable overridding nonce match to Disable/Enable nonce match */
                    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, 0x8001+(laneOffset*0x200), 10, 1, enable));
                }
            }
            else if (hostSpeed == MXD_100GB)
            {
                ATTEMPT(mxdSetDeepPMALoopback100G(pDev, mdioPort, MXD_LINE_SIDE, autoNeg, enable));
            }
            break;
        default:
            MXD_DBG_ERROR("mxdSetHostLoopback: incorrect loopback selection: %u\n", loopback_type);
            return MXD_FAIL;
            break;
    }

    return MXD_OK;
}


/*******************************************************************************
 MXD_STATUS mxdConfigurePktGeneratorChecker
    Configure packet generator checker function
*******************************************************************************/
MXD_STATUS mxdConfigurePktGeneratorChecker
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    IN MXD_BOOL readToClear,
    IN MXD_BOOL dontuseSFDinChecker,
    IN MXD_U16  pktPatternControl,
    IN MXD_BOOL generateCRCoff,
    IN MXD_U32  initialPayload,
    IN MXD_U16  frameLengthControl,
    IN MXD_U16  numPktsToSend,
    IN MXD_BOOL randomIPG,
    IN MXD_U16  ipgDuration
)
{
    MXD_U16 regAddrOffset=0;

    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdConfigurePktGeneratorChecker: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    ATTEMPT(mxdGetPktGenRegOffset(pDev, mdioPort, host_or_line, laneOffset, &regAddrOffset));

    if (pktPatternControl > MXD_PKT_RANDOM_WORD || pktPatternControl == 1)
    {
        return MXD_FAIL;
    }

    if (frameLengthControl == 6 || frameLengthControl == 7)
    {
        return MXD_FAIL;
    }

    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, MXD_PKT_GEN_CONTROL1+regAddrOffset, 
                                15, 1, MXD_GET_BOOL_AS_BIT(readToClear)));
    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, MXD_PKT_GEN_CONTROL1+regAddrOffset, 
                                2, 1, MXD_GET_BOOL_AS_BIT(dontuseSFDinChecker)));
    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, MXD_PKT_GEN_CONTROL2+regAddrOffset, 
                                4, 4, pktPatternControl));
    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, MXD_PKT_GEN_CONTROL2+regAddrOffset, 
                                3, 1, MXD_GET_BOOL_AS_BIT(generateCRCoff)));

    /* load up initial payload */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, MXD_PKT_GEN_PAYLOAD1+regAddrOffset, (MXD_U16)initialPayload));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, MXD_PKT_GEN_PAYLOAD2+regAddrOffset, (MXD_U16)(initialPayload>>16)));

    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, MXD_PKT_GEN_LENGTH+regAddrOffset, frameLengthControl));

    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, MXD_PKT_GEN_BURSTSEQ+regAddrOffset, numPktsToSend));

    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, MXD_PKT_GEN_IPG+regAddrOffset, 
                                15, 1, MXD_GET_BOOL_AS_BIT(randomIPG)));

    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, MXD_PKT_GEN_IPG+regAddrOffset, 0, 15, ipgDuration));

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdEnablePktGeneratorChecker
    Enable/Disable packet generator and checker function
*******************************************************************************/
MXD_STATUS mxdEnablePktGeneratorChecker
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    IN MXD_BOOL enableGenerator,
    IN MXD_BOOL enableChecker
)
{
    MXD_U16 temp=0;
    MXD_U16 regAddrOffset=0;

    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdEnablePktGeneratorChecker: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    if ((pDev->devInfo & MXD_GEARBOX_MODE) && (enableGenerator == MXD_TRUE))
    {
        if (host_or_line == MXD_HOST_SIDE)
        {
           ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0x904D, 15, 1, 1));
        }
        else
        {
           ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xA04D, 15, 1, 1));
        }
    }

    ATTEMPT(mxdGetPktGenRegOffset(pDev, mdioPort, host_or_line, laneOffset, &regAddrOffset));

    /* better to start/stop at the same time if possible, use a single write to limit delays between them */
    temp = ((MXD_GET_BOOL_AS_BIT(enableGenerator))<<1) | (MXD_GET_BOOL_AS_BIT(enableChecker));

    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, MXD_PKT_GEN_CONTROL1+regAddrOffset, 0, 2, temp));

    if ((pDev->devInfo & MXD_GEARBOX_MODE) && (enableGenerator == MXD_FALSE))
    {
        if (host_or_line == MXD_HOST_SIDE)
        {
           ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0x904D, 15, 1, 0));
        }
        else
        {
           ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xA04D, 15, 1, 0));
        }
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdPktGeneratorCounterReset
    Reset packet generator counter
*******************************************************************************/
MXD_STATUS mxdPktGeneratorCounterReset
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset
)
{
    MXD_U16 regAddrOffset=0;
    MXD_SPEED speed;
    MXD_PCS_TYPE pcsType;

    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdPktGeneratorCounterReset: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    ATTEMPT(mxdGetModeSpeed(pDev, mdioPort, host_or_line, laneOffset, &speed, &pcsType));
    if (pcsType != MXD_PCS)
    {
        MXD_DBG_ERROR("mxdPktGeneratorCounterReset: not a PCS mode\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdGetPktGenRegOffset(pDev, mdioPort, host_or_line, laneOffset, &regAddrOffset));

    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, MXD_PKT_GEN_CONTROL1+regAddrOffset, 6, 1, 1));
    /* assumes delay is long enough to clear counters, this makes an assumption about the speed */
    /* of the MDIO as being relatively slow compared to the number of cycles it takes to clear the */
    /* clear the counters, relatively fast. may need a delay here for F2R, or really fast MDIO */
    /* speeds */
    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, MXD_PKT_GEN_CONTROL1+regAddrOffset, 6, 1, 0));

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdPktGeneratorGetCounter
    Get 64 bit packet generator counters
*******************************************************************************/
MXD_STATUS mxdPktGeneratorGetCounter
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    IN MXD_U16  whichCounter,
    OUT MXD_U64 *packetCount,
    OUT MXD_U64 *byteCount
)
{
    MXD_U16 temp;
    MXD_U16 regAddrOffset=0;

    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdPktGeneratorGetCounter: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    ATTEMPT(mxdGetPktGenRegOffset(pDev, mdioPort, host_or_line, laneOffset, &regAddrOffset));

    *packetCount = *byteCount = 0;

    switch (whichCounter)
    {
        case MXD_PKT_GET_TX:
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PKT_GEN_TXPKTCTR1+regAddrOffset, &temp));
            *packetCount = temp;
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PKT_GEN_TXPKTCTR2+regAddrOffset, &temp));
            *packetCount |= (((MXD_U64)(temp))<<16);
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PKT_GEN_TXPKTCTR3+regAddrOffset, &temp));
            *packetCount |= (((MXD_U64)(temp))<<32);

            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PKT_GEN_TXBYTCTR1+regAddrOffset, &temp));
            *byteCount = temp;
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PKT_GEN_TXBYTCTR2+regAddrOffset, &temp));
            *byteCount |= (((MXD_U64)(temp))<<16);
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PKT_GEN_TXBYTCTR3+regAddrOffset, &temp));
            *byteCount |= (((MXD_U64)(temp))<<32);
            break;

        case MXD_PKT_GET_RX:
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PKT_GEN_RXPKTCTR1+regAddrOffset, &temp));
            *packetCount = temp;
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PKT_GEN_RXPKTCTR2+regAddrOffset, &temp));
            *packetCount |= (((MXD_U64)(temp))<<16);
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PKT_GEN_RXPKTCTR3+regAddrOffset, &temp));
            *packetCount |= (((MXD_U64)(temp))<<32);

            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PKT_GEN_RXBYTCTR1+regAddrOffset, &temp));
            *byteCount = temp;
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PKT_GEN_RXBYTCTR2+regAddrOffset, &temp));
            *byteCount |= (((MXD_U64)(temp))<<16);
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PKT_GEN_RXBYTCTR3+regAddrOffset, &temp));
            *byteCount |= (((MXD_U64)(temp))<<32);
            break;

        case MXD_PKT_GET_ERR:
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PKT_GEN_ERRPKTCTR1+regAddrOffset, &temp));
            *packetCount = temp;
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PKT_GEN_ERRPKTCTR2+regAddrOffset, &temp));
            *packetCount |= (((MXD_U64)(temp))<<16);
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PKT_GEN_ERRPKTCTR3+regAddrOffset, &temp));
            *packetCount |= (((MXD_U64)(temp))<<32);
            break;

        default:
            MXD_DBG_ERROR("mxdPktGeneratorGetCounter: incorrect counter selection: %u\n", whichCounter);
            return MXD_FAIL;
            break;
    }

    return MXD_OK;
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

#define PRBS_LANE_OFFSET      0x10 /* offset between PRBS control registers by lane */ 

#define JP03A_PATT       0x0303 /* defines for PRBS 0 Test Pattern A/B */
#define JP03B_PATT       0x3030
#define LOWF_A_PATT      0xFFF0
#define LOWF_B_PATT      0x000F
#define SQ_A_PATT        0xFFFF
#define SQ_B_PATT        0x0000
#define MF_A_PATT        0xFCCF
#define MF_B_PATT        0x0330

/*******************************************************************************
 MXD_STATUS mxdSetLineSidePRBSPattern
    Selects the line side PRBS pattern
*******************************************************************************/
MXD_STATUS mxdSetLineSidePRBSPattern
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  laneOffset,
    IN MXD_PRBS_SELECTOR_TYPE pattSel,
    IN MXD_PATTERN_AB_SELECTOR_TYPE pattSubSel,
    IN MXD_SQUARE_WAV_PATTERN_TYPE squarePattern
)
{
    const MXD_U16 prbsControlRegAddr   = (MXD_PRBS_CONTROL+laneOffset*PRBS_LANE_OFFSET),
                  prbsTestPattARegAddr = (MXD_PRBS0_TEST_PATTA+laneOffset*PRBS_LANE_OFFSET),
                  prbsTestPattBRegAddr = (MXD_PRBS0_TEST_PATTB+laneOffset*PRBS_LANE_OFFSET);

    /* this is a diagnostic function. limited error checking is done. */

    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdSetLineSidePRBSPattern: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    if (laneOffset >= MXD_NUM_LANES)
    {
        MXD_DBG_ERROR("mxdSetLineSidePRBSPattern: incorrect lane offset: %u\n", (unsigned)laneOffset);
        return MXD_FAIL;
    }

    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_LINE_SIDE, prbsControlRegAddr, PRBS_PATTERN_SEL_BIT, 4, (MXD_U16)pattSel));

    switch (pattSel)
    {
        case MXD_JP03AB:
            switch (pattSubSel)
            {
                case MXD_JP03A:
                    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, prbsTestPattARegAddr, JP03A_PATT));
                    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, prbsTestPattBRegAddr, JP03A_PATT));
                    break;

                case MXD_JP03B:
                    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, prbsTestPattARegAddr, JP03B_PATT));
                    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, prbsTestPattBRegAddr, JP03B_PATT));
                    break;

                default:
                    MXD_DBG_ERROR("mxdSetLineSidePRBSPattern: incorrect pattSubSel: %u\n", (unsigned)pattSubSel);
                    return MXD_FAIL;
                    break;
            }
            break;

        case MXD_GEN_TX:
            switch (pattSubSel)
            {
                case MXD_LOW_FREQ:
                    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, prbsTestPattARegAddr, LOWF_A_PATT));
                    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, prbsTestPattBRegAddr, LOWF_B_PATT));
                    break;

                case MXD_SQUARE_WAV:
                    if (mxdSetSquareWave(pDev, mdioPort, MXD_LINE_SIDE, laneOffset, squarePattern) == MXD_FAIL)
                    {
                        MXD_DBG_ERROR("mxdSetLineSidePRBSPattern: mxdSetSquareWave line side failed\n");
                        return MXD_FAIL;
                    }
                    break;

                case MXD_MIXED_FREQ:
                    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, prbsTestPattARegAddr, MF_A_PATT));
                    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, prbsTestPattBRegAddr, MF_B_PATT));                    
                    break;

                default:
                    MXD_DBG_ERROR("mxdSetLineSidePRBSPattern: incorrect pattSubSel: %u\n", (unsigned)pattSubSel);
                    return MXD_FAIL;
                    break;
            }
            break;

        default:
            /* all other cases do nothing, 3.F1XA and 3.F1XB don't matter, pattSubSel is ignored */
            break;
    }
    
    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdSetHostSidePRBSPattern
    Selects the Host side PRBS pattern
*******************************************************************************/
MXD_STATUS mxdSetHostSidePRBSPattern
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  laneOffset,
    IN MXD_PRBS_SELECTOR_TYPE pattSel,
    IN MXD_PATTERN_AB_SELECTOR_TYPE pattSubSel,
    IN MXD_SQUARE_WAV_PATTERN_TYPE squarePattern
)
{
    const MXD_U16 prbsControlRegAddr   = (MXD_PRBS_CONTROL+laneOffset*PRBS_LANE_OFFSET),
                  prbsTestPattARegAddr = (MXD_PRBS0_TEST_PATTA+laneOffset*PRBS_LANE_OFFSET),
                  prbsTestPattBRegAddr = (MXD_PRBS0_TEST_PATTB+laneOffset*PRBS_LANE_OFFSET);

    /* this is a diagnostic function. limited error checking is done. */
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdSetHostSidePRBSPattern: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    if (laneOffset >= MXD_NUM_LANES)
    {
        MXD_DBG_ERROR("mxdSetHostSidePRBSPattern: incorrect lane offset: %u\n", (unsigned)laneOffset);
        return MXD_FAIL;
    }
    
    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_HOST_SIDE, prbsControlRegAddr, PRBS_PATTERN_SEL_BIT, 4, (MXD_U16)pattSel));

    switch (pattSel)
    {
        case MXD_JP03AB:
            switch (pattSubSel)
            {
                case MXD_JP03A:
                    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, prbsTestPattARegAddr, JP03A_PATT));
                    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, prbsTestPattBRegAddr, JP03A_PATT));
                    break;

                case MXD_JP03B:
                    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, prbsTestPattARegAddr, JP03B_PATT));
                    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, prbsTestPattBRegAddr, JP03B_PATT));
                    break;

                default:
                    MXD_DBG_ERROR("mxdSetHostSidePRBSPattern: incorrect pattSubSel: %u\n", (unsigned)pattSubSel);
                    return MXD_FAIL;
                    break;
            }
            break;

        case MXD_GEN_TX:
            switch (pattSubSel)
            {
                case MXD_LOW_FREQ:
                    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, prbsTestPattARegAddr, LOWF_A_PATT));
                    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, prbsTestPattBRegAddr, LOWF_B_PATT));
                    break;

                case MXD_SQUARE_WAV:
                    if (mxdSetSquareWave(pDev, mdioPort, MXD_HOST_SIDE, laneOffset, squarePattern) == MXD_FAIL)
                    {
                        MXD_DBG_ERROR("mxdSetHostSidePRBSPattern: mxdSetSquareWave host side failed\n");
                        return MXD_FAIL;
                    }
                    break;

                case MXD_MIXED_FREQ:
                    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, prbsTestPattARegAddr, MF_A_PATT));
                    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, prbsTestPattBRegAddr, MF_B_PATT));                    
                    break;

                default:
                    MXD_DBG_ERROR("mxdSetHostSidePRBSPattern: incorrect pattSubSel: %u\n", (unsigned)pattSubSel);
                    return MXD_FAIL;
                    break;
            }
            break;

        default:
            /* all other cases do nothing, 3.F1XA and 3.F1XB don't matter, pattSubSel is ignored */
            break;
    }
    
    return MXD_OK;
}

/************** COMMON PRBS FUNCTIONS ****************************************/
/*************** Used for both host and line side ****************************/

static MXD_U16 squareWave[5][20] = 
                {{0x0018,0x0000,0x0019,0x0000,0x0019,0x0000,0x0019,0x0000,0x0019,0x0000,
                  0x0019,0x0000,0x0019,0x0000,0x0019,0x0000,0x0019,0x0000,0x0002,0x0107},
                 {0x0018,0x0000,0x0019,0x03FF,0x0019,0x03FF,0x0019,0x03FF,0x0019,0x03FF,
                  0x0019,0x03FF,0x0019,0x03FF,0x0019,0x03FF,0x0019,0x03FF,0x0002,0x0107},
                 {0x0018,0x0000,0x0019,0x02AA,0x0019,0x02AA,0x0019,0x02AA,0x0019,0x02AA,
                  0x0019,0x02AA,0x0019,0x02AA,0x0019,0x02AA,0x0019,0x02AA,0x0002,0x0107},
                 {0x0018,0x0000,0x0019,0x03E0,0x0019,0x03E0,0x0019,0x03E0,0x0019,0x03E0,
                  0x0019,0x03E0,0x0019,0x03E0,0x0019,0x03E0,0x0019,0x03E0,0x0002,0x0107},
                 {0x0018,0x0000,0x0019,0x00FF,0x0019,0x03C0,0x0019,0x000F,0x0019,0x03FC,
                  0x0019,0x0300,0x0019,0x003F,0x0019,0x03F0,0x0019,0x0003,0x0002,0x0107}
                }; 

/*******************************************************************************
 MXD_STATUS mxdSetSquareWave
    Generates all 0's pattern, all 1's pattern, Square Wave pattern 1, 5 or 8
*******************************************************************************/
MXD_STATUS mxdSetSquareWave
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    IN MXD_SQUARE_WAV_PATTERN_TYPE  pattern
)
{
    MXD_U16 i;

    if (pattern > MXD_SQUARE_WAV_8)
    {
        MXD_DBG_ERROR("mxdSetSquareWave: Square wave pattern not supported!\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_COMMAND_REG, 0x0021));

    if (host_or_line == MXD_HOST_SIDE)
    {
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_ADDR_REG, (0x0103+laneOffset*0x100)));
    }
    else
    {
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_ADDR_REG, (0x0503+laneOffset*0x100)));
    }

    for (i=0; i<20; i+=2)
    {    
        /* Write to sBus */
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_INPUT_DATA_H, squareWave[pattern][i]));
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_INPUT_DATA_L, squareWave[pattern][i+1]));

        /* set Sbus command receive data valid selection mode to level */
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_RX_DATA_VALID, 0x00));

        if ((mxdExecuteIndirectSBusCmd(pDev, mdioPort)) != MXD_OK)
        {
            MXD_DBG_ERROR("mxdSetSquareWave: sBus command execution error!\n");
            return MXD_FAIL;
        }
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdSetPRBSEnableTxRx
    Controls the transmit and receive
*******************************************************************************/
MXD_STATUS mxdSetPRBSEnableTxRx
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,    
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    IN MXD_U16  txEnable,
    IN MXD_U16  rxEnable
)
{
    MXD_U16 temp;
    MXD_U16 prbsControlRegAddr=(MXD_PRBS_CONTROL+laneOffset*PRBS_LANE_OFFSET);
    
    /* this is a diagnostic function. limited error checking is done. */
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdSetPRBSEnableTxRx: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));
    
    if (laneOffset >= MXD_NUM_LANES)
    {
        MXD_DBG_ERROR("mxdSetPRBSEnableTxRx: incorrect lane offset: %u\n", (unsigned)laneOffset);
        return MXD_FAIL;
    }

    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, prbsControlRegAddr, &temp));
    ATTEMPT(mxdHwSetRegFieldToWord(temp, txEnable, PRBS_TX_EN_BIT, 1, &temp));
    ATTEMPT(mxdHwSetRegFieldToWord(temp, rxEnable, PRBS_RX_EN_BIT, 1, &temp));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, prbsControlRegAddr, temp));
        
    return MXD_OK;
}


/*******************************************************************************
 MXD_STATUS mxdPRBSCounterReset
    Resets the PRBS counter when it's been set to manual reset and not clear-on-
    read
*******************************************************************************/
MXD_STATUS mxdPRBSCounterReset
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,    
    IN MXD_U16  host_or_line,    
    IN MXD_U16  laneOffset
)
{
    MXD_U16 prbsControlRegAddr=(MXD_PRBS_CONTROL+laneOffset*PRBS_LANE_OFFSET);

    /* this is a diagnostic function. limited error checking is done. */
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdPRBSCounterReset: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    if (laneOffset >= MXD_NUM_LANES)
    {
        MXD_DBG_ERROR("mxdPRBSCounterReset: incorrect lane offset: %u\n", (unsigned)laneOffset);
        return MXD_FAIL;
    }

    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, prbsControlRegAddr, PRBS_CTR_RESET_BIT, 1, (MXD_U16)1));
        
    return MXD_OK;
}



/*******************************************************************************
 MXD_STATUS mxdSetPRBSWaitForLock
    Makes the receiver start counting right away, even before it's locked 
    on the pattern
*******************************************************************************/
MXD_STATUS mxdSetPRBSWaitForLock
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,    
    IN MXD_U16  host_or_line,    
    IN MXD_U16  laneOffset,
    IN MXD_U16  disableWaitforLock
)
{
    MXD_U16 prbsControlRegAddr=(MXD_PRBS_CONTROL+laneOffset*PRBS_LANE_OFFSET);

    /* this is a diagnostic function. limited error checking is done. */
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdSetPRBSWaitForLock: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    if (laneOffset >= MXD_NUM_LANES)
    {
        MXD_DBG_ERROR("mxdSetPRBSWaitForLock: incorrect lane offset: %u\n", (unsigned)laneOffset);
        return MXD_FAIL;
    }

    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, prbsControlRegAddr, PRBS_WAIT_LOCK_BIT, 1, disableWaitforLock));
        
    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetPRBSWaitForLock
    Gets the value of the control bit that sets whether the counters start
    right away, or wait until the receiver is locked.
*******************************************************************************/
MXD_STATUS mxdGetPRBSWaitForLock
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,    
    IN MXD_U16  host_or_line,    
    IN MXD_U16  laneOffset,
    OUT MXD_U16 *disableWaitforLock
)
{
    MXD_U16 prbsControlRegAddr=(MXD_PRBS_CONTROL+laneOffset*PRBS_LANE_OFFSET);

    /* this is a diagnostic function. limited error checking is done. */
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdGetPRBSWaitForLock: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    if (laneOffset >= MXD_NUM_LANES)
    {
        MXD_DBG_ERROR("mxdGetPRBSWaitForLock: incorrect lane offset: %u\n", (unsigned)laneOffset);
        return MXD_FAIL;
    }

    ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, host_or_line, prbsControlRegAddr, PRBS_WAIT_LOCK_BIT, 1, disableWaitforLock));
        
    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdSetPRBSClearOnRead
    Sets the bit that controls whether the counters clear when read or
    clear manually by setting a bit.
*******************************************************************************/
MXD_STATUS mxdSetPRBSClearOnRead
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,    
    IN MXD_U16  host_or_line,    
    IN MXD_U16  laneOffset,
    IN MXD_U16  enableReadClear
)
{
    MXD_U16 prbsControlRegAddr=(MXD_PRBS_CONTROL+laneOffset*PRBS_LANE_OFFSET);

    /* this is a diagnostic function. limited error checking is done. */
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdSetPRBSClearOnRead: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    if (laneOffset >= MXD_NUM_LANES)
    {
        MXD_DBG_ERROR("mxdSetPRBSClearOnRead: incorrect lane offset: %u\n", (unsigned)laneOffset);
        return MXD_FAIL;
    }

    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, prbsControlRegAddr, PRBS_READ_CLEAR_BIT, 1, enableReadClear));
        
    return MXD_OK;
}


/*******************************************************************************
 MXD_STATUS mxdGetPRBSClearOnRead
    Reads the bit setting that controls whether the counters clear when read or
    clear manually by setting a bit.
*******************************************************************************/
MXD_STATUS mxdGetPRBSClearOnRead
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,    
    IN MXD_U16  host_or_line,    
    IN MXD_U16  laneOffset,
    OUT MXD_U16  *enableReadClear
)
{
    MXD_U16 prbsControlRegAddr=(MXD_PRBS_CONTROL+laneOffset*PRBS_LANE_OFFSET);

    /* this is a diagnostic function. limited error checking is done. */
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdGetPRBSClearOnRead: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    if (laneOffset >= MXD_NUM_LANES)
    {
        MXD_DBG_ERROR("mxdGetPRBSClearOnRead: incorrect lane offset: %u\n", (unsigned)laneOffset);
        return MXD_FAIL;
    }

    ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, host_or_line, prbsControlRegAddr, PRBS_READ_CLEAR_BIT, 1, enableReadClear));
        
    return MXD_OK;
}


/*******************************************************************************
 MXD_STATUS mxdGetPRBSLocked
    Reads the status bit that indicates if the receiver is locked onto the
    PRBS pattern or not.
*******************************************************************************/
MXD_STATUS mxdGetPRBSLocked
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_BOOL *prbsLocked
)
{
    MXD_U16 prbsControlRegAddr=(MXD_PRBS_CONTROL+laneOffset*PRBS_LANE_OFFSET);

    /* this is a diagnostic function. limited error checking is done. */
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdGetPRBSLocked: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    if (laneOffset >= MXD_NUM_LANES)
    {
        MXD_DBG_ERROR("mxdGetPRBSLocked: incorrect lane offset: %u\n", (unsigned)laneOffset);
        return MXD_FAIL;
    }

    ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, host_or_line, prbsControlRegAddr, PRBS_LOCKED_BIT, 1, (MXD_U16 *)prbsLocked));
        
    return MXD_OK;
}


/*******************************************************************************
 MXD_STATUS mxdGetPRBSCounts
    Reads the counters. Will clear the counters if they've been setup to
    clear-on-read.
*******************************************************************************/
MXD_STATUS mxdGetPRBSCounts
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,    
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U64 *txBitCount,
    OUT MXD_U64 *rxBitCount,
    OUT MXD_U64 *rxBitErrorCount
)
{
    MXD_U16 prbsTxCountReg, prbsRxCountReg, prbsErrCountReg,
            lowTxWord, lowRxWord, lowErrWord,
            midWord, hiWord;

    /* initialize values, in case of error return 0 */
    *txBitCount = *rxBitCount = *rxBitErrorCount = 0;

    /* this is a diagnostic function. limited error checking is done. */
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdGetPRBSCounts: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    if (laneOffset >= MXD_NUM_LANES)
    {
        MXD_DBG_ERROR("mxdGetPRBSCounts: incorrect lane offset: %u\n", (unsigned)laneOffset);
        return MXD_FAIL;
    }

    prbsTxCountReg  = MXD_PRBS_SYM_TXCTR1  + laneOffset*PRBS_LANE_OFFSET;
    prbsRxCountReg  = MXD_PRBS_SYM_RXCTR1  + laneOffset*PRBS_LANE_OFFSET;
    prbsErrCountReg = MXD_PRBS_SYM_ERRCTR1 + laneOffset*PRBS_LANE_OFFSET;

    /* must read low words first to latch the upper two words */

    /* read tx count lower/mid/upper */
    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, prbsTxCountReg, &lowTxWord));
    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, prbsTxCountReg+1, &midWord));
    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, prbsTxCountReg+2, &hiWord));
    *txBitCount = lowTxWord + (((MXD_U64)(midWord))<<16) + (((MXD_U64)(hiWord))<<32);

    /* read rx count lower/mid/upper */
    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, prbsRxCountReg, &lowRxWord));
    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, prbsRxCountReg+1, &midWord));
    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, prbsRxCountReg+2, &hiWord));
    *rxBitCount = lowRxWord + (((MXD_U64)(midWord))<<16) + (((MXD_U64)(hiWord))<<32);

    /* read err count lower/mid/upper */
    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, prbsErrCountReg, &lowErrWord));
    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, prbsErrCountReg+1, &midWord));
    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, prbsErrCountReg+2, &hiWord));
    *rxBitErrorCount = lowErrWord + (((MXD_U64)(midWord))<<16) + (((MXD_U64)(hiWord))<<32);

    return MXD_OK;
}


/*******************************************************************************
 MXD_STATUS mxdSetTxPolarity
*******************************************************************************/
MXD_STATUS mxdSetTxPolarity
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,     
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_U16 polarity,
    IN MXD_U16 swReset
)
{
    MXD_U16 temp;

    /* minimal error checking is done in diagnostic function */
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdSetTxPolarity: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    if (laneOffset > 3)
    {
        MXD_DBG_ERROR("mxdSetTxPolarity: lane offset is out of range\n");
        return MXD_FAIL;
    }

    if (!(host_or_line == MXD_HOST_SIDE || host_or_line == MXD_LINE_SIDE))
    {
        MXD_DBG_ERROR("mxdSetTxPolarity: host_or_line is invalid\n");
        return MXD_FAIL;
    }

    if (polarity > 1)
    {
        MXD_DBG_ERROR("mxdSetTxPolarity: polarity:%u is invalid (1-inverted; 0-non-inverted)\n", polarity);
        return MXD_FAIL;
    }


    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_B+(0x80*laneOffset), &temp));
    temp &= ~0x5000; 
    temp |= polarity ? 0x5800: 0x4800;
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_B+(0x80*laneOffset), temp));

    if (swReset)
    {
        ATTEMPT(mxdLaneSoftReset(pDev, mdioPort, host_or_line, laneOffset, MAX_RESET_WAIT));
    }

    MXD_DBG_INFO("mxdSetTxPolarity: \n");

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetTxPolarity
*******************************************************************************/
MXD_STATUS mxdGetTxPolarity
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,     
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U16 *polarity
)
{
    /* minimal error checking is done in diagnostic function */
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdGetTxPolarity: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    if (laneOffset > 3)
    {
        MXD_DBG_ERROR("mxdGetTxPolarity: lane offset is out of range\n");
        return MXD_FAIL;
    }

    if (!(host_or_line == MXD_HOST_SIDE || host_or_line == MXD_LINE_SIDE))
    {
        MXD_DBG_ERROR("mxdGetTxPolarity: host_or_line is invalid\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_B+(0x80*laneOffset),
                                12, 1, polarity));  

    MXD_DBG_INFO("mxdGetTxPolarity: polarity:%u\n", *polarity);

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdSetRxPolarity
*******************************************************************************/
MXD_STATUS mxdSetRxPolarity
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,     
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_U16 polarity,
    IN MXD_U16 swReset
)
{
    MXD_U16 temp;

    /* minimal error checking is done in diagnostic function */
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdSetRxPolarity: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    if (laneOffset > 3)
    {
        MXD_DBG_ERROR("mxdSetRxPolarity: lane offset is out of range\n");
        return MXD_FAIL;
    }

    if (!(host_or_line == MXD_HOST_SIDE || host_or_line == MXD_LINE_SIDE))
    {
        MXD_DBG_ERROR("mxdSetRxPolarity: host_or_line is invalid\n");
        return MXD_FAIL;
    }

    if (polarity > 1)
    {
        MXD_DBG_ERROR("mxdSetRxPolarity: polarity:%u is invalid (1-inverted; 0-non-inverted)\n", polarity);
        return MXD_FAIL;
    }

    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_B+(0x80*laneOffset), &temp));
    temp &= ~0xA000; 
    temp |= polarity ? 0xA800: 0x8800;
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_B+(0x80*laneOffset), temp));

    if (swReset)
    {
        ATTEMPT(mxdLaneSoftReset(pDev, mdioPort, host_or_line, laneOffset, MAX_RESET_WAIT));
    }

    MXD_DBG_INFO("mxdSetRxPolarity: \n");

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetRxPolarity
*******************************************************************************/
MXD_STATUS mxdGetRxPolarity
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,     
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U16 *polarity
)
{
    /* minimal error checking is done in diagnostic function */
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdGetRxPolarity: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    if (laneOffset > 3)
    {
        MXD_DBG_ERROR("mxdGetRxPolarity: lane offset is out of range\n");
        return MXD_FAIL;
    }

    if (!(host_or_line == MXD_HOST_SIDE || host_or_line == MXD_LINE_SIDE))
    {
        MXD_DBG_ERROR("mxdGetRxPolarity: host_or_line is invalid\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_B+(0x80*laneOffset),
                                13, 1, polarity));  

    MXD_DBG_INFO("mxdGetRxPolarity: polarity:%u\n", *polarity);

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdSetTxFFE
*******************************************************************************/
MXD_STATUS mxdSetTxFFE
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,     
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_16 preCursor,
    IN MXD_16 attenuation,
    IN MXD_16 postCursor,
    IN MXD_U16 swReset
)
{
    MXD_SPEED speed;
    MXD_PCS_TYPE pcsType;
    MXD_STATUS status;

    /* minimal error checking is done in diagnostic function */
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdSetTxFFE: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    if (laneOffset > 3)
    {
        MXD_DBG_ERROR("mxdSetTxFFE: lane offset is out of range\n");
        return MXD_FAIL;
    }

    if (!(host_or_line == MXD_HOST_SIDE || host_or_line == MXD_LINE_SIDE))
    {
        MXD_DBG_ERROR("mxdSetTxFFE: host_or_line is invalid\n");
        return MXD_FAIL;
    }

    /* sanity check for inputs within ranges */
    if ((preCursor < -7) || (preCursor > 15) ||
        (postCursor < -31) || (postCursor > 31) ||
        (attenuation < 0) || (attenuation > 31))
    {
        MXD_DBG_ERROR("mxdSetTxFFE: invalid FFE values - preCursor:%d; attenuation:%d; postCursor:%d\n",
                      preCursor, attenuation, postCursor);
        return MXD_FAIL;
    }

    status = mxdGetModeSpeed(pDev, mdioPort, host_or_line, laneOffset, &speed, &pcsType);
    if (status != MXD_OK)
    {
        MXD_DBG_ERROR("mxdSetTxFFE: Calling mxdGetModeSpeed failed\n");
        return MXD_FAIL;
    }

    switch (speed)
    {
        case MXD_1GB:
        case MXD_2_5GB:
        case MXD_5GB:
            /* set preCursor */
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_14+(0x80*laneOffset), 0, 8, preCursor));

            /* set attenuation */
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_15+(0x80*laneOffset), 0, 8, attenuation));

            /* set postCursor */
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_16+(0x80*laneOffset), 0, 8, postCursor));
            break;

        case MXD_10GB:
        case MXD_40GB:
            /* set preCursor */
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_14+(0x80*laneOffset), 8, 8, preCursor));

            /* set attenuation */
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_15+(0x80*laneOffset), 8, 8, attenuation));

            /* set postCursor */
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_16+(0x80*laneOffset), 8, 8, postCursor));
            break;

        case MXD_25GB:
        case MXD_50GB:
        case MXD_100GB:
        {
            int field_offset = (pDev->use20G) ? 0 : 8;
            /* set preCursor */
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_17+(0x80*laneOffset), field_offset, 8, preCursor));

            /* set attenuation */
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_18+(0x80*laneOffset), field_offset, 8, attenuation));

            /* set postCursor */
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_19+(0x80*laneOffset), field_offset, 8, postCursor));
            break;
        }

        default:
            MXD_DBG_ERROR("mxdSetTxFFE: speed not supported\n");
            return MXD_FAIL;
            break;
    }

    /* enable Tx initial taps command to serdes */
    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF26F+(0x80*laneOffset), 0, 1, 1));

    if (swReset)
    {
        ATTEMPT(mxdLaneSoftReset(pDev, mdioPort, host_or_line, laneOffset, MAX_RESET_WAIT));
    }

    MXD_DBG_INFO("mxdSetTxFFE: Completed\n");

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetTxFFE
*******************************************************************************/
MXD_STATUS mxdGetTxFFE
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,     
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_16 *preCursor,
    OUT MXD_16 *attenuation,
    OUT MXD_16 *postCursor
)
{
    MXD_SPEED speed;
    MXD_PCS_TYPE mode;
    MXD_STATUS status;

    /* minimal error checking is done in diagnostic function */
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdGetTxFFE: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    if (laneOffset > 3)
    {
        MXD_DBG_ERROR("mxdGetTxFFE: lane offset is out of range\n");
        return MXD_FAIL;
    }

    if (!(host_or_line == MXD_HOST_SIDE || host_or_line == MXD_LINE_SIDE))
    {
        MXD_DBG_ERROR("mxdGetTxFFE: host_or_line is invalid\n");
        return MXD_FAIL;
    }

    status = mxdGetModeSpeed(pDev, mdioPort, host_or_line, laneOffset, &speed, &mode);
    if (status != MXD_OK)
    {
        MXD_DBG_ERROR("mxdGetTxFFE: Calling mxdGetModeSpeed failed\n");
        return MXD_FAIL;
    }

    switch (speed)
    {
        case MXD_1GB:
        case MXD_2_5GB:
        case MXD_5GB:
            /* set preCursor */
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_14+(0x80*laneOffset), 0, 8, (MXD_U16*)preCursor));
    
            /* set attenuation */
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_15+(0x80*laneOffset), 0, 8, (MXD_U16*)attenuation));

            /* set postCursor */
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_16+(0x80*laneOffset), 0, 8, (MXD_U16*)postCursor));
            break;

        case MXD_10GB:
        case MXD_40GB:
            /* set preCursor */
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_14+(0x80*laneOffset), 8, 8, (MXD_U16*)preCursor));

            /* set attenuation */
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_15+(0x80*laneOffset), 8, 8, (MXD_U16*)attenuation));

            /* set postCursor */
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_16+(0x80*laneOffset), 8, 8, (MXD_U16*)postCursor));
            break;

        case MXD_25GB:
        case MXD_100GB:
            /* set preCursor */
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_17+(0x80*laneOffset), 8, 8, (MXD_U16*)preCursor));

            /* set attenuation */
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_18+(0x80*laneOffset), 8, 8, (MXD_U16*)attenuation));

            /* set postCursor */
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, host_or_line, MXD_SERDES_LANE0_REG_19+(0x80*laneOffset), 8, 8, (MXD_U16*)postCursor));
            break;

        default:
            MXD_DBG_ERROR("mxdGetTxFFE: speed not supported\n");
            return MXD_FAIL;
            break;
    }

    *preCursor = (*preCursor & 0x80) ? (*preCursor | 0xFF00):*preCursor;
    *postCursor = (*postCursor & 0x80) ? (*postCursor | 0xFF00):*postCursor;

    MXD_DBG_INFO("mxdGetTxFFE: preCursor:%d, attenuation:%d, postCursor:%d\n", *preCursor, *attenuation, *postCursor);

    return MXD_OK;
}


