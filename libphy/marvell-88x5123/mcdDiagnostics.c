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
* @mcdDiagnostics.c
*
* @brief This file contains functions and global data for
* higher-level functions using MDIO access to enable test modes,
* loopbacks, and other diagnostic functions of the Marvell PHY MCD driver
********************************************************************/

#include "mcdApiTypes.h"
#include "mcdUtils.h"
#include "mcdHwCntl.h"
#include "mcdAPI.h"
#include "mcdApiRegs.h"
#include "mcdDiagnostics.h"
#include "mcdAPIInternal.h"
#include "mcdHwSerdesCntl.h"
#include "mcdInternalIpcApis.h"

#define MCD_MARVELL_OUI       0x3
#define MCD_MODEL_X5121       0x2F
#define PACKET_GEN_40G_OFFSET 0xF10
#define MAX_RESET_WAIT        1000

MCD_STATUS mcdGetChipRevision
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    OUT MCD_DEVICE_ID *deviceId
)
{
    MCD_STATUS rc;
    MCD_U32    data32, dev_id;

    rc = mcdHwXmdioRead32bit(
        pDev, 0/*mdioPort*/, REG_ADDR_MG_DEV_ID, &data32);
    if (rc != MCD_OK) return rc;

    dev_id = ((data32 >> 4) & 0xFFFF);

    switch (dev_id)
    {
        case 0x1404:
        case 0x1403:
            *deviceId = MCD_REV_X5123;
            break;
        case 0x0328:
            *deviceId = MCD_REV_EC808;
            break;
        default:
            *deviceId = MCD_REV_UNKNOWN;
            break;
    }

    return MCD_OK;
}
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************************
 MCD_STATUS mcdGetChipFWRevision
   Revision in <major>.<minor> format
*******************************************************************************/
MCD_STATUS mcdGetChipFWRevision
(
    IN MCD_DEV_PTR pDev,
    OUT MCD_U16 *major,
    OUT MCD_U16 *minor
)
{
    return MCD_NOT_IMPLEMENTED;
}

/*******************************************************************************
 MCD_STATUS mcdCheckChipCapablities
*******************************************************************************/
MCD_STATUS mcdCheckChipCapablities
(
    IN MCD_DEV_PTR pDev,
    IN MCD_OP_MODE portMode
)
{
    switch (pDev->deviceId)
    {
        case MCD_REV_X5123:
        case MCD_REV_EC808:
            break;
        default:
            MCD_DBG_ERROR("mcdCheckChipCapablities: invalid device ID\n");
            return MCD_FAIL;
    }

    switch (portMode)
    {
        /* modes for channel 0 only */
        case MCD_MODE_P100L:
        case MCD_MODE_P100S:
        case MCD_MODE_G21L:
        case MCD_MODE_G21SK:
        case MCD_MODE_R100L:
        case MCD_MODE_R100C:
        /* modes for channel 0 or 2 */
        case MCD_MODE_P50R2L:
        case MCD_MODE_P50R2S:
        case MCD_MODE_P40R2L:
        case MCD_MODE_P40R2S:
        case MCD_MODE_R40L:
        case MCD_MODE_R40C:
        /* modes for any channel */
        case MCD_MODE_P25L:
        case MCD_MODE_P25S:
        case MCD_MODE_P10L:
        case MCD_MODE_P10S:
        case MCD_MODE_R25L:
        case MCD_MODE_R25C:
        case MCD_MODE_R10L:
        case MCD_MODE_R10K:
        case MCD_MODE_P2_5:
        case MCD_MODE_P1:
        case MCD_MODE_R1L:
        case MCD_MODE_R1C:
            break;
        default:
            return MCD_FAIL;
    }
    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdGetSerdesSignalDetectAndDspLock
    Return value of signal detect and DSP lock for corresponding lane.
    Signal_detect is idle detect from SERDES.
    Dsp_lock is signal ok from SERDES.
*******************************************************************************/
MCD_STATUS mcdGetSerdesSignalDetectAndDspLock
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_U16 laneOffset,
    OUT MCD_U16 *signalDetect,
    OUT MCD_U16 *dspLock
)
{
    MCD_U32 regAddr, regAddr1;
    MCD_U32 slice;
    MCD_U32 readData;
    MCD_U32 serdesNum, phySerdesNum;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdGetSerdesSignalDetectAndDspLock: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdGetSerdesSignalDetectAndDspLock: incorrect port selection: %uh\n", mdioPort);
        return MCD_FAIL;
    }

    /* because this is a diagnostic function, minimal error checking is done */
    if (laneOffset > 3)
    {
        MCD_DBG_ERROR("mcdGetSerdesSignalDetectAndDspLock: lane offset is out of range\n");
        return MCD_FAIL;
    }

    if (!(host_or_line == MCD_HOST_SIDE || host_or_line == MCD_LINE_SIDE))
    {
        MCD_DBG_ERROR("mcdGetSerdesSignalDetectAndDspLock: host_or_line is invalid\n");
        return MCD_FAIL;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    if (host_or_line == MCD_HOST_SIDE)
    {
        serdesNum = MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + laneOffset), slice);
        /* convert logic serdes number to physical serdes number */
        MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);
        regAddr = MCD_SERDES_External_Status(phySerdesNum);
        regAddr1 = MCD_SERDES_Core_Status(phySerdesNum);
    }
    else
    {
        serdesNum = MCD_SERDES_NUM(laneOffset, slice);
        /* convert logic serdes number to physical serdes number */
        MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);
        regAddr = MCD_SERDES_External_Status(phySerdesNum); /*line*/
        regAddr1 = MCD_SERDES_Core_Status(phySerdesNum);
    }


    ATTEMPT(mcdHwGetPhyRegField32bit(pDev, mdioPort, regAddr, 2, 1, &readData));
    *signalDetect = (MCD_U16)((~readData) & 1);
    ATTEMPT(mcdHwGetPhyRegField32bit(pDev, mdioPort, regAddr1, 4, 1, &readData));
    *dspLock = (MCD_U16)(readData);
    return MCD_OK;
}


/*******************************************************************************
 MCD_STATUS mcdSetLoopback
    Enable/Disable line side loopbacks
*******************************************************************************/
MCD_STATUS mcdSetLoopback
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 loopback_type,
    IN MCD_U16 enable
)
{
    MCD_U32        regAddr;
    MCD_U32        hwData;
    MCD_U32        slice, chan;
    MCD_U16        bits2set,numbBits;


    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("%s: device not initialized\n", __func__);
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("%s: incorrect port selection: %uh\n", __func__, mdioPort);
        return MCD_FAIL;
    }

    switch(pDev->portConfig[mdioPort].portMode)
    {
       case MCD_MODE_P100L:
       case MCD_MODE_P100S:
       case MCD_MODE_P100C:
       case MCD_MODE_P100K:
       case MCD_MODE_P40L:
       case MCD_MODE_P40S:
       case MCD_MODE_P40C:
       case MCD_MODE_P40K:
           bits2set = 0xF;
           numbBits = 4;
           break;
       case MCD_MODE_P50R2L:
       case MCD_MODE_P50R2S:
       case MCD_MODE_P40R2L:
       case MCD_MODE_P40R2S:
           bits2set = 0x3;
           numbBits = 2;
           break;
       case MCD_MODE_G21L:
       case MCD_MODE_G21SK:
            if (host_or_line == MCD_LINE_SIDE)
            {
                bits2set = 0xF;
                numbBits = 4;
            }
            else
            {
                bits2set = 0x3;
                numbBits =2;
            }
            break;
        default:
            bits2set = 1;
            numbBits = 1;
            break;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);

    switch(loopback_type)
    {
        case MCD_DEEP_PCS_LB:
            /*each channel TX data into the SERDES looped back into the RX data from the SERDES
            (allow testing the entire data path excluding the SERDES).
            Loopback is performed at the SERDES interface level in Async mode*/
            {
                regAddr = UMAC_SERDES_MUX_SerDes_Loopback_Enable(slice,chan);
                if (host_or_line == MCD_LINE_SIDE)
                {
                    regAddr = UMAC_SERDES_MUX_SerDes_Loopback_Enable(slice, chan +4);
                }
                else
                {
                    regAddr = UMAC_SERDES_MUX_SerDes_Loopback_Enable(slice,chan);
                }

                hwData = (enable ? bits2set : 0);
                ATTEMPT(mcdHwSetPhyRegField32bit(
                                    pDev, mdioPort, regAddr, chan, numbBits, hwData));
            }
            return MCD_OK;

        default:
            MCD_DBG_ERROR("%s: incorrect loopback selection: %u\n", __func__, loopback_type);
            return MCD_FAIL;
    }
}

/*******************************************************************************
 MCD_STATUS mcdSetLineLoopback
    Enable/Disable line side loopbacks
*******************************************************************************/
MCD_STATUS mcdSetLineLoopback
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 loopback_type,
    IN MCD_U16 enable
)
{
    return mcdSetLoopback(
        pDev, mdioPort, MCD_LINE_SIDE, loopback_type, enable);
}

/*******************************************************************************
 MCD_STATUS mcdSetHostLoopback
    Enable/Disable host side loopbacks
*******************************************************************************/
MCD_STATUS mcdSetHostLoopback
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 loopback_type,
    IN MCD_U16 enable
)
{
    return mcdSetLoopback(
        pDev, mdioPort, MCD_HOST_SIDE, loopback_type, enable);
}

#endif
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************************
 MCD_STATUS mcdConfigurePktGeneratorChecker
    Configure packet generator checker function
*******************************************************************************/
MCD_STATUS mcdConfigurePktGeneratorChecker
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_BOOL readToClear,
    IN MCD_BOOL dontuseSFDinChecker,
    IN MCD_U16  pktPatternControl,
    IN MCD_BOOL generateCRCoff,
    IN MCD_U32  initialPayload,
    IN MCD_U16  frameLengthControl,
    IN MCD_U16  numPktsToSend,
    IN MCD_BOOL randomIPG,
    IN MCD_U16  ipgDuration
)
{
    return MCD_STATUS_NOT_SUPPORTED;
}

/*******************************************************************************
 MCD_STATUS mcdEnablePktGeneratorChecker
    Enable/Disable packet generator and checker function
*******************************************************************************/
MCD_STATUS mcdEnablePktGeneratorChecker
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_BOOL enableGenerator,
    IN MCD_BOOL enableChecker
)
{
    return MCD_STATUS_NOT_SUPPORTED;
}

/*******************************************************************************
 MCD_STATUS mcdPktGeneratorCounterReset
    Reset packet generator counter
*******************************************************************************/
MCD_STATUS mcdPktGeneratorCounterReset
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line
)
{
    return MCD_STATUS_NOT_SUPPORTED;
}

/*******************************************************************************
 MCD_STATUS mcdPktGeneratorGetCounter
    Get 64 bit packet generator counters
*******************************************************************************/
MCD_STATUS mcdPktGeneratorGetCounter
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_U16  whichCounter,
    OUT MCD_U64 *packetCount,
    OUT MCD_U64 *byteCount
)
{
    return MCD_STATUS_NOT_SUPPORTED;
}

/***************************** PRBS Control/Status/Counters *******************/

/* Bit Positions for PRBS Control/Status */
#define PRBS_READ_CLEAR_BIT 13
#define PRBS_LOCKED_BIT      8
#define PRBS_WAIT_LOCK_BIT   7
#define PRBS_CTR_RESET_BIT   6
#define PRBS_TX_EN_BIT       5
#define PRBS_RX_EN_BIT       4
#define PRBS_PATTERN_SEL_BIT 0 /* 4-bit field */

#define LINE_PRBS_LANE_OFFSET 0x10 /* offset between PRBS control registers by lane */

#define LINE_JP03A_PATT       0x0303 /* defines for PRBS 0 Test Pattern A/B */
#define LINE_JP03B_PATT       0x3030
#define LINE_LOWF_A_PATT      0xFFF0
#define LINE_LOWF_B_PATT      0x000F
#define LINE_SQ_A_PATT        0xFFFF
#define LINE_SQ_B_PATT        0x0000
#define LINE_MF_A_PATT        0xFCCF
#define LINE_MF_B_PATT        0x0330

/* macros for grabbing PRBS register addresses  on line side */
#define GET_LINE_PRBS_REG_ADDR(xyzBaseAddr,xyzLaneOffset) (xyzBaseAddr + xyzLaneOffset * LINE_PRBS_LANE_OFFSET)
#define GET_LINE_PRBS_CONTROL_ADDR(xyzLaneOffset) GET_LINE_PRBS_REG_ADDR(MCD_LINE_PRBS_CONTROL,xyzLaneOffset)
#define GET_LINE_PRBS_TXCNT1_ADDR(xyzLaneOffset) GET_LINE_PRBS_REG_ADDR(MCD_LINE_PRBS_SYM_TXCTR1,xyzLaneOffset)
#define GET_LINE_PRBS_RXCNT1_ADDR(xyzLaneOffset) GET_LINE_PRBS_REG_ADDR(MCD_LINE_PRBS_SYM_RXCTR1,xyzLaneOffset)
#define GET_LINE_PRBS_ERRCNT1_ADDR(xyzLaneOffset) GET_LINE_PRBS_REG_ADDR(MCD_LINE_PRBS_SYM_ERRCTR1,xyzLaneOffset)

/* calculate Width field by port mode */
static MCD_U32 mcdGetPRBSSerdesDataWidth
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line
)
{
    MCD_MODE_SPEED speed;
    MCD_MODE       mode;
    MCD_U32        speedTotal, speedPerLane, lanesNum;

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdGetPRBSWidth: incorrect port selection: %uh\n", mdioPort);
        return 0;
    }

    if(mcdGetModeSpeed(pDev, mdioPort, host_or_line, &speed, &mode) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdGetPRBSWidth: incorrect port mode/spid: %uh\n", mdioPort);
        return 0;
    }

    lanesNum = mcdPortGetLanesNum(pDev, mdioPort, host_or_line);
    if (lanesNum == 0)
    {
        MCD_DBG_ERROR("mcdGetPRBSWidth: not supported lanesNum: %uh\n", mdioPort);
        return 0;
    }

    switch (speed)
    {
        case MCD_10GB:
            speedTotal = 10000;
            break;
        case MCD_20GB:
            speedTotal = 20000;
            break;
        case MCD_25GB:
            speedTotal = 25000;
            break;
        case MCD_40GB:
            speedTotal = 40000;
            break;
        case MCD_100GB:
            speedTotal = 100000;
            break;
        case MCD_2_5GB:
            speedTotal = 2500;
            break;
        case MCD_1GB:
            speedTotal = 1000;
            break;
        case MCD_50GB:
            speedTotal = 50000;
            break;
        default: return 0;
    }
    speedPerLane = (speedTotal / lanesNum);
    MCD_DBG_INFO(
        "mcdGetPRBSWidth: port %d speedTotal %d lanesNum %d speedPerLane %d \n",
        mdioPort, speedTotal, lanesNum, speedPerLane);
    if (speedPerLane <= 2500)  return 10;
    if (speedPerLane <= 10000) return 20;
    if (speedPerLane <= 25000) return 40;
    return 0; /* error case */
}

/*******************************************************************************
 MCD_STATUS mcdSetLineSidePRBSPattern
    Selects the line-side PRBS pattern
*******************************************************************************/
MCD_STATUS mcdSetLineSidePRBSPattern
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  laneOffset,
    IN MCD_PRBS_LINE_SELECTOR_TYPE pattSel,
    IN MCD_PATTERN_LINE_AB_SELECTOR_TYPE pattSubSel
)
{
    MCD_U32 regAddr;
    MCD_U32 slice, chan, lane;
    MCD_U32 serdesDataWidth;
    MCD_U32 hwPattern, hwInverted;
    MCD_U32 pattern, mask;

    pattSubSel = pattSubSel; /* parameter ignored */

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdSetLineSidePRBSPattern: device not initialized\n");
        return MCD_FAIL;
    }

    serdesDataWidth = mcdGetPRBSSerdesDataWidth(pDev, mdioPort, MCD_LINE_SIDE);
    if (serdesDataWidth == 0)
    {
        MCD_DBG_ERROR("mcdSetLineSidePRBSPattern: speed/mode not supported\n");
        return MCD_FAIL;
    }

    switch (pattSel)
    {
        case MCD_LINE_PRBS7:
            hwPattern = 7;
            hwInverted = 0;
            break;
        case MCD_LINE_PRBS9:
            hwPattern = 9;
            hwInverted = 0;
            break;
        case MCD_LINE_PRBS11:
            hwPattern = 11;
            hwInverted = 0;
            break;
        case MCD_LINE_PRBS15:
            hwPattern = 15;
            hwInverted = 0;
            break;
        case MCD_LINE_PRBS23:
            hwPattern = 23;
            hwInverted = 0;
            break;
        case MCD_LINE_PRBS31:
            hwPattern = 31;
            hwInverted = 0;
            break;
        case MCD_LINE_IPRBS7:
            hwPattern = 7;
            hwInverted = 1;
            break;
        case MCD_LINE_IPRBS9:
            hwPattern = 9;
            hwInverted = 1;
            break;
        case MCD_LINE_IPRBS11:
            hwPattern = 11;
            hwInverted = 1;
            break;
        case MCD_LINE_IPRBS15:
            hwPattern = 15;
            hwInverted = 1;
            break;
        case MCD_LINE_IPRBS23:
            hwPattern = 23;
            hwInverted = 1;
            break;
        case MCD_LINE_IPRBS31:
            hwPattern = 31;
            hwInverted = 1;
            break;
        default:
            MCD_DBG_ERROR("mcdSetLineSidePRBSPattern: incorrect pattern selection: %uh\n", pattSel);
            return MCD_FAIL;
    }
    mask    = ((0x3F << 9) | (0x1F << 2) | (1 << 1));
    pattern = ((serdesDataWidth << 9) | (hwPattern << 2) | (hwInverted << 1));

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);
    lane  = (chan + laneOffset);
    if (lane > MCD_NUM_LANES)
    {
        MCD_DBG_ERROR("mcdSetLineSidePRBSPattern: incorrect laneOffset: %uh\n", laneOffset);
        return MCD_FAIL;
    }

    /* configure transmit */
    /*<UMAC> UMAC/Slice %m/umac3gbsx4/serdesmux0/txprbscfg0-3*/
    regAddr  = UMAC_SERDES_MUX_txprbscfg(slice, lane);
    regAddr  = UMAC_SERDES_MUX_LINE_REG_ADDR(regAddr);
    ATTEMPT(mcdHwSetPhyRegMask32bit(
        pDev, mdioPort, regAddr, mask, pattern));

    /* configure receive */
    /*<UMAC> UMAC/Slice %m/umac3gbsx4/serdesmux0/rxprbscfg0-3*/
    regAddr  = UMAC_SERDES_MUX_rxprbscfg(slice, lane);
    regAddr  = UMAC_SERDES_MUX_LINE_REG_ADDR(regAddr);
    ATTEMPT(mcdHwSetPhyRegMask32bit(
        pDev, mdioPort, regAddr, mask, pattern));

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdSetHostSidePRBSPattern
    Selects the host-side PRBS pattern
*******************************************************************************/
MCD_STATUS mcdSetHostSidePRBSPattern
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  laneOffset,
    IN MCD_PRBS_HOST_SELECTOR_TYPE pattSel
)
{
    MCD_U32 regAddr;
    MCD_U32 slice, chan, lane;
    MCD_U32 serdesDataWidth;
    MCD_U32 hwPattern, hwInverted;
    MCD_U32 pattern, mask;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdSetHostSidePRBSPattern: device not initialized\n");
        return MCD_FAIL;
    }

    serdesDataWidth = mcdGetPRBSSerdesDataWidth(pDev, mdioPort, MCD_HOST_SIDE);
    if (serdesDataWidth == 0)
    {
        MCD_DBG_ERROR("mcdSetLineSidePRBSPattern: speed/mode not supported\n");
        return MCD_FAIL;
    }

    switch (pattSel)
    {
        case MCD_HOST_PRBS7:
            hwPattern = 7;
            hwInverted = 0;
            break;
        case MCD_HOST_PRBS9:
            hwPattern = 9;
            hwInverted = 0;
            break;
        case MCD_HOST_PRBS11:
            hwPattern = 11;
            hwInverted = 0;
            break;
        case MCD_HOST_PRBS15:
            hwPattern = 15;
            hwInverted = 0;
            break;
        case MCD_HOST_PRBS23:
            hwPattern = 23;
            hwInverted = 0;
            break;
        case MCD_HOST_PRBS31:
            hwPattern = 31;
            hwInverted = 0;
            break;
        case MCD_HOST_IPRBS7:
            hwPattern = 7;
            hwInverted = 1;
            break;
        case MCD_HOST_IPRBS9:
            hwPattern = 9;
            hwInverted = 1;
            break;
        case MCD_HOST_IPRBS11:
            hwPattern = 11;
            hwInverted = 1;
            break;
        case MCD_HOST_IPRBS15:
            hwPattern = 15;
            hwInverted = 1;
            break;
        case MCD_HOST_IPRBS23:
            hwPattern = 23;
            hwInverted = 1;
            break;
        case MCD_HOST_IPRBS31:
            hwPattern = 31;
            hwInverted = 1;
            break;
        default:
            MCD_DBG_ERROR("mcdSetHostSidePRBSPattern: incorrect pattern selection: %uh\n", pattSel);
            return MCD_FAIL;
    }
    mask    = ((0x3F << 9) | (0x1F << 2) | (1 << 1));
    pattern = ((serdesDataWidth << 9) | (hwPattern << 2) | (hwInverted << 1));

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);
    lane  = (chan + laneOffset);
    if (lane > MCD_NUM_LANES)
    {
        MCD_DBG_ERROR("mcdSetHostSidePRBSPattern: incorrect laneOffset: %uh\n", laneOffset);
        return MCD_FAIL;
    }

    /* configure transmit */
    /*<UMAC> UMAC/Slice %m/umac3gbsx4/serdesmux0/txprbscfg0-3*/
    regAddr  = UMAC_SERDES_MUX_txprbscfg(slice, lane);
    ATTEMPT(mcdHwSetPhyRegMask32bit(
        pDev, mdioPort, regAddr, mask, pattern));

    /* configure receive */
    /*<UMAC> UMAC/Slice %m/umac3gbsx4/serdesmux0/rxprbscfg0-3*/
    regAddr  = UMAC_SERDES_MUX_rxprbscfg(slice, lane);
    ATTEMPT(mcdHwSetPhyRegMask32bit(
        pDev, mdioPort, regAddr, mask, pattern));

    return MCD_OK;
}

/************** COMMON PRBS FUNCTIONS ****************************************/
/*************** Used for both host and line side ****************************/

/*******************************************************************************
 MCD_STATUS mcdSetPRBSEnableTxRx
    Controls the transmit and receive
*******************************************************************************/
MCD_STATUS mcdSetPRBSEnableTxRx
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_U16  laneOffset,
    IN MCD_U16  txEnable,
    IN MCD_U16  rxEnable
)
{
    MCD_U32 regAddr;
    MCD_U32 slice, chan, lane;
    MCD_U32 pattern, mask;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdSetPRBSEnableTxRx: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSetPRBSEnableTxRx: incorrect port selection: %uh\n", mdioPort);
        return MCD_FAIL;
    }

    if ((host_or_line != MCD_HOST_SIDE) && (host_or_line != MCD_LINE_SIDE))
    {
        MCD_DBG_ERROR("mcdSetPRBSEnableTxRx: host_or_line is invalid\n");
        return MCD_FAIL;
    }

    if (txEnable || rxEnable)
    {
        /* stop CM3 polling on PCS link */
        ATTEMPT(mcdPortPollingLinkStatusStop(pDev, mdioPort));
    }
    else
        ATTEMPT(mcdPortPollingLinkStatusStart(pDev, mdioPort));

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);
    lane  = (chan + laneOffset);
    if (lane > MCD_NUM_LANES)
    {
        MCD_DBG_ERROR("mcdSetPRBSEnableTxRx: incorrect laneOffset: %uh\n", laneOffset);
        return MCD_FAIL;
    }

    /* configure transmit */
    /*<UMAC> UMAC/Slice %m/umac3gbsx4/serdesmux0/txprbscfg0-3*/
    regAddr  = UMAC_SERDES_MUX_txprbscfg(slice, lane);
    if (host_or_line == MCD_LINE_SIDE)
    {
        regAddr  = UMAC_SERDES_MUX_LINE_REG_ADDR(regAddr);
    }
    mask    = 1;
    pattern = txEnable;
    ATTEMPT(mcdHwSetPhyRegMask32bit(
        pDev, mdioPort, regAddr, mask, pattern));

    /* configure receive */
    /*<UMAC> UMAC/Slice %m/umac3gbsx4/serdesmux0/rxprbscfg0-3*/
    regAddr  = UMAC_SERDES_MUX_rxprbscfg(slice, lane);
    if (host_or_line == MCD_LINE_SIDE)
    {
        regAddr  = UMAC_SERDES_MUX_LINE_REG_ADDR(regAddr);
    }
    mask    = 1;
    pattern = rxEnable;
    ATTEMPT(mcdHwSetPhyRegMask32bit(
        pDev, mdioPort, regAddr, mask, pattern));

    return MCD_OK;
}


/*******************************************************************************
 MCD_STATUS mcdPRBSCounterReset
    Resets the PRBS counter when it's been set to manual reset and not clear-on-
    read
*******************************************************************************/
MCD_STATUS mcdPRBSCounterReset
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_U16  laneOffset
)
{
    /* counters are always clear on read */
    return MCD_STATUS_NOT_SUPPORTED;
}

/*******************************************************************************
 MCD_STATUS mcdSetPRBSWaitForLock
    Makes the receiver start counting right away, even before it's locked
    on the pattern
*******************************************************************************/
MCD_STATUS mcdSetPRBSWaitForLock
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_U16  laneOffset,
    IN MCD_U16  disableWaitforLock
)
{
    /* locking not confugurable                                */
    /* unlocked by reading PRBS errors counter up to getting 0 */
    return MCD_STATUS_NOT_SUPPORTED;
}

/*******************************************************************************
 MCD_STATUS mcdGetPRBSWaitForLock
    Gets the value of the control bit that sets whether the counters start
    right away, or wait until the receiver is locked.
*******************************************************************************/
MCD_STATUS mcdGetPRBSWaitForLock
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_U16  laneOffset,
    OUT MCD_U16 *disableWaitforLock
)
{
    /* locking not confugurable                                */
    /* unlocked by reading PRBS errors counter up to getting 0 */
    return MCD_STATUS_NOT_SUPPORTED;
}

/*******************************************************************************
 MCD_STATUS mcdSetPRBSClearOnRead
    Sets the bit that controls whether the counters clear when read or
    clear manually by setting a bit.
*******************************************************************************/
MCD_STATUS mcdSetPRBSClearOnRead
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_U16  laneOffset,
    IN MCD_U16  enableReadClear
)
{
    /* counters are always clear on read */
    return MCD_STATUS_NOT_SUPPORTED;
}


/*******************************************************************************
 MCD_STATUS mcdGetPRBSClearOnRead
    Reads the bit setting that controls whether the counters clear when read or
    clear manually by setting a bit.
*******************************************************************************/
MCD_STATUS mcdGetPRBSClearOnRead
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_U16  laneOffset,
    OUT MCD_U16  *enableReadClear
)
{
    /* counters are always clear on read */
    return MCD_STATUS_NOT_SUPPORTED;
}


/*******************************************************************************
 MCD_STATUS mcdGetPRBSLocked
    Reads the status bit that indicates if the receiver is locked onto the
    PRBS pattern or not.
*******************************************************************************/
MCD_STATUS mcdGetPRBSLocked
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_U16  laneOffset,
    OUT MCD_BOOL *prbsLocked
)
{
    /* locking not confugurable                                */
    /* unlocked by reading PRBS errors counter up to getting 0 */
    return MCD_STATUS_NOT_SUPPORTED;
}


/*******************************************************************************
 MCD_STATUS mcdGetPRBSCounts
    Reads the counters. Will clear the counters if they've been setup to
    clear-on-read.
*******************************************************************************/
MCD_STATUS mcdGetPRBSCounts
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_U16  laneOffset,
    OUT MCD_U64 *txBitCount,
    OUT MCD_U64 *rxBitCount,
    OUT MCD_U64 *rxBitErrorCount
)
{
    MCD_U32 regAddr;
    MCD_U32 slice, chan, lane;
    MCD_U32 data;

    /* not used parameters */
    txBitCount = txBitCount;
    rxBitCount = rxBitCount;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdGetPRBSCounts: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdGetPRBSCounts: incorrect port selection: %uh\n", mdioPort);
        return MCD_FAIL;
    }

    if ((host_or_line != MCD_HOST_SIDE) && (host_or_line != MCD_LINE_SIDE))
    {
        MCD_DBG_ERROR("mcdGetPRBSCounts: host_or_line is invalid\n");
        return MCD_FAIL;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);
    lane  = (chan + laneOffset);
    if (lane > MCD_NUM_LANES)
    {
        MCD_DBG_ERROR("mcdGetPRBSCounts: incorrect laneOffset: %uh\n", laneOffset);
        return MCD_FAIL;
    }

    /* configure transmit */
    /*<UMAC> UMAC/Slice %m/umac3gbsx4/serdesmux0/rxprbserrcnt0-3*/
    regAddr  = UMAC_SERDES_MUX_rxprbserrcnt(slice, lane);
    if (host_or_line == MCD_LINE_SIDE)
    {
        regAddr  = UMAC_SERDES_MUX_LINE_REG_ADDR(regAddr);
    }

    ATTEMPT(mcdHwXmdioRead32bit(
        pDev, mdioPort, regAddr, &data));

    *rxBitErrorCount = (MCD_U64)(data & 0xFFFF);

    return MCD_OK;
}
#endif

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************************
 MCD_STATUS mcdSetTxPolarity
*******************************************************************************/
MCD_STATUS mcdSetTxPolarity
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 laneOffset,
    IN MCD_U16 polarity,
    IN MCD_U16 swReset
)
{
    MCD_U32 slice, chan;
    MCD_U16 sAddr, linesNum;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdSetTxPolarity: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    linesNum = mcdPortGetLanesNum(
        pDev, mdioPort, host_or_line);
    if (linesNum == 0)
    {
        MCD_DBG_ERROR("mcdSetTxPolarity: incorrect port selection: %uh\n", mdioPort);
        return MCD_FAIL;
    }
    if (laneOffset >= linesNum)
    {
        MCD_DBG_ERROR("mcdSetTxPolarity: incorrect laneOffset: %uh\n", laneOffset);
        return MCD_FAIL;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);
    sAddr = (MCD_U16)MCD_SERDES_LANE_SBUS_ADDR(host_or_line, slice, (chan + laneOffset));
    ATTEMPT(mcdSerdesSetTxPolarity(pDev, sAddr, polarity));
    if (swReset)
    {
        ATTEMPT(mcdSerdesReset(pDev, sAddr));
    }

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdGetTxPolarity
*******************************************************************************/
MCD_STATUS mcdGetTxPolarity
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 laneOffset,
    OUT MCD_U16 *polarity
)
{
    MCD_U32 slice, chan;
    MCD_U16 sAddr, linesNum;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdGetTxPolarity: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    linesNum = mcdPortGetLanesNum(
        pDev, mdioPort, host_or_line);
    if (linesNum == 0)
    {
        MCD_DBG_ERROR("mcdGetTxPolarity: incorrect port selection: %uh\n", mdioPort);
        return MCD_FAIL;
    }
    if (laneOffset >= linesNum)
    {
        MCD_DBG_ERROR("mcdGetTxPolarity: incorrect laneOffset: %uh\n", laneOffset);
        return MCD_FAIL;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);
    sAddr = (MCD_U16)MCD_SERDES_LANE_SBUS_ADDR(host_or_line, slice, (chan + laneOffset));
    ATTEMPT(mcdSerdesGetTxPolarity(pDev, sAddr, polarity));

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdSetRxPolarity
*******************************************************************************/
MCD_STATUS mcdSetRxPolarity
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 laneOffset,
    IN MCD_U16 polarity,
    IN MCD_U16 swReset
)
{
    MCD_U32 slice, chan;
    MCD_U16 sAddr, linesNum;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdSetRxPolarity: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    linesNum = mcdPortGetLanesNum(
        pDev, mdioPort, host_or_line);
    if (linesNum == 0)
    {
        MCD_DBG_ERROR("mcdSetRxPolarity: incorrect port selection: %uh\n", mdioPort);
        return MCD_FAIL;
    }
    if (laneOffset >= linesNum)
    {
        MCD_DBG_ERROR("mcdSetRxPolarity: incorrect laneOffset: %uh\n", laneOffset);
        return MCD_FAIL;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);
    sAddr = (MCD_U16)MCD_SERDES_LANE_SBUS_ADDR(host_or_line, slice, (chan + laneOffset));
    ATTEMPT(mcdSerdesSetRxPolarity(pDev, sAddr, polarity));
    if (swReset)
    {
        ATTEMPT(mcdSerdesReset(pDev, sAddr));
    }

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdGetRxPolarity
*******************************************************************************/
MCD_STATUS mcdGetRxPolarity
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 laneOffset,
    OUT MCD_U16 *polarity
)
{
    MCD_U32 slice, chan;
    MCD_U16 sAddr, linesNum;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdGetRxPolarity: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    linesNum = mcdPortGetLanesNum(
        pDev, mdioPort, host_or_line);
    if (linesNum == 0)
    {
        MCD_DBG_ERROR("mcdGetRxPolarity: incorrect port selection: %uh\n", mdioPort);
        return MCD_FAIL;
    }
    if (laneOffset >= linesNum)
    {
        MCD_DBG_ERROR("mcdGetRxPolarity: incorrect laneOffset: %uh\n", laneOffset);
        return MCD_FAIL;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);
    sAddr = (MCD_U16)MCD_SERDES_LANE_SBUS_ADDR(host_or_line, slice, (chan + laneOffset));
    ATTEMPT(mcdSerdesGetRxPolarity(pDev, sAddr, polarity));

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdSetTxFFE
*******************************************************************************/
MCD_STATUS mcdSetTxFFE
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 laneOffset,
    IN MCD_16 preCursor,
    IN MCD_16 attenuation,
    IN MCD_16 postCursor,
    IN MCD_U16 swReset
)
{
    MCD_U32 slice, chan;
    MCD_U16 sAddr, linesNum;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdSetTxFFE: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    linesNum = mcdPortGetLanesNum(
        pDev, mdioPort, host_or_line);
    if (linesNum == 0)
    {
        MCD_DBG_ERROR("mcdSetTxFFE: incorrect port selection: %uh\n", mdioPort);
        return MCD_FAIL;
    }
    if (laneOffset >= linesNum)
    {
        MCD_DBG_ERROR("mcdSetTxFFE: incorrect laneOffset: %uh\n", laneOffset);
        return MCD_FAIL;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);
    sAddr = (MCD_U16)MCD_SERDES_LANE_SBUS_ADDR(host_or_line, slice, (chan + laneOffset));
    /* slew parameter not passed to this function and not supported by called function */
    ATTEMPT(mcdSerdesSetTxFFE(
        pDev, sAddr, preCursor, attenuation, postCursor, 0/*slew*/));
    if (swReset)
    {
        ATTEMPT(mcdSerdesReset(pDev, sAddr));
    }

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdGetTxFFE
*******************************************************************************/
MCD_STATUS mcdGetTxFFE
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 laneOffset,
    OUT MCD_16 *preCursor,
    OUT MCD_16 *attenuation,
    OUT MCD_16 *postCursor
)
{
    MCD_16 slew;
    MCD_U32 slice, chan;
    MCD_U16 sAddr, linesNum;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdGetTxFFE: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    linesNum = mcdPortGetLanesNum(
        pDev, mdioPort, host_or_line);
    if (linesNum == 0)
    {
        MCD_DBG_ERROR("mcdGetTxFFE: incorrect port selection: %uh\n", mdioPort);
        return MCD_FAIL;
    }
    if (laneOffset >= linesNum)
    {
        MCD_DBG_ERROR("mcdGetTxFFE: incorrect laneOffset: %uh\n", laneOffset);
        return MCD_FAIL;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);
    sAddr = (MCD_U16)MCD_SERDES_LANE_SBUS_ADDR(host_or_line, slice, (chan + laneOffset));
    /* slew parameter not passed to this function and not supported by called function */
    ATTEMPT(mcdSerdesGetTxFFE(
        pDev, sAddr, preCursor, attenuation, postCursor, &slew));

    return MCD_OK;
}



/* register : rdctrl */
static MCD_U32 rdctrl_regs[MCD_SIDE_BOTH][MCD_MAX_SLICE_NUM] =
{
    { UMAC_Statistics_Read_Control(0,0), /* host */
    UMAC_Statistics_Read_Control(1,0)},
    { UMAC_Statistics_Read_Control(0,1), /* line */
    UMAC_Statistics_Read_Control(1,1)}
};

/* register : rdata0 */
/* 15:0 rdata    RO 0x0         This contains the bits [15:0] of the Statistics Counter that is read. */
static MCD_U32 rdata0_regs[MCD_SIDE_BOTH][MCD_MAX_SLICE_NUM] =
{
    {UMAC_Statistics_Read_Data0(0,0),
    UMAC_Statistics_Read_Data0(1,0)},
    {UMAC_Statistics_Read_Data0(0,1),
    UMAC_Statistics_Read_Data0(1,1)}
};

/* register : rdata1 */
/* 15:0 rdata    RO 0x0         This contains the bits [31:16] of the Statistics Counter that is read. */
static MCD_U32 rdata1_regs[MCD_SIDE_BOTH][MCD_MAX_SLICE_NUM] =
{
    {UMAC_Statistics_Read_Data1(0,0),
    UMAC_Statistics_Read_Data1(1,0)},
    {UMAC_Statistics_Read_Data1(0,1),
    UMAC_Statistics_Read_Data1(1,1)}
};

/* register : rdata2 */
/* 15:0 rdata    RO 0x0         This contains the bits [47:32] of the Statistics Counter that is read. */
static MCD_U32 rdata2_regs[MCD_SIDE_BOTH][MCD_MAX_SLICE_NUM] =
{
    {UMAC_Statistics_Read_Data2(0,0),
    UMAC_Statistics_Read_Data2(1,0)},
    {UMAC_Statistics_Read_Data2(0,1),
    UMAC_Statistics_Read_Data2(1,1)}
};

/* register : rdata3 */
/* 15:0 rdata    RO 0x0         This contains the bits [63:48] of the Statistics Counter that is read. */
static MCD_U32 rdata3_regs[MCD_SIDE_BOTH][MCD_MAX_SLICE_NUM] =
{
    {UMAC_Statistics_Read_Data3(0,0),
    UMAC_Statistics_Read_Data3(1,0)},
    {UMAC_Statistics_Read_Data3(0,1),
    UMAC_Statistics_Read_Data3(1,1)}
};


/**
* @internal mcdSampleGetPortStatistics function
* @endinternal
*
* @brief  Print Statistics (MIB) counters of a port.
*
* @param[in] pDev       - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] portNum  - represents port  (0..8) number
* @param[in] host_or_line     - host or lane side of a port, values MCD_LINE_SIDE or MCD_HOST_SIDE.
* @param[in] reducedPrint     - if true prints only non-zero counters
*
* @retval MCD_OK                    - on success.
* @retval MCD_FAIL                  - on failure
*
* @note use like mcdSampleGetPortStatistics 0,0,3,0
* statistics can be read from 4 registers - one per side and per slice.  IN each register we can specify from which channel to read a statistics and
* which type of counter.  In this function we dump all counters of a certain port, specific for a defined side.  The port is a "channel", meaning we don't
* relate to ports speed in case of multi-lane ports
*/
MCD_STATUS mcdGetPortStatistics
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_BOOL   reducedPrint
)
{
    MCD_U32 slice, chan;
    MCD_U16 linesNum;
    MCD_U32 regAddr, value, i, j;
    MCD_SIDE_ENT side;
    MCD_STATUS rc;
    MCD_U16 data0, data1, data2, data3;
    MCD_U64  counter64 = 0;
    char     *aline;

    static char *statistics[] = {
        "00: Frames Received O.K",
        "01: Frames Received All (Good/Bad Frames)",
        "02: Frames Received with FCS Error",
        "03: Frames with any Error (CRC, Length, Alignment Error).",
        "04: Octets Received in Good Frames.",
        "05: Octets Received (Good/Bad Frames)",
        "06: Frames Received with Unicast Addresses.",
        "07: Frames Received with Multicast Addresses.",
        "08: Frames Received with Broadcast Addresses.",
        "09: Frames Received of type PAUSE.",
        "10: Frames Received with Length Error.",
        "11: Frames Received Undersized (No Error)",
        "12: Frames Received Oversized (No Error)",
        "13: Fragments Received",
        "14: Jabber Received",
        "15: Priority Pause Frames.",
        "16: CRC Error (Stomped)",
        "17: Frame Too Long.",
        "18: Rx VLAN Frames (Good).",
        "19: Frames Dropped (Buffer Full)",
        "20: Frames Received Length<64",
        "21: Frames Received Length=64.",
        "22: Frames Received Length=65-127.",
        "23: Frames Received Length=128-255.",
        "24: Frames Received Length=256-511.",
        "25: Frames Received Length=512-1023.",
        "26: Frames Received Length=1024-1518.",
        "27: Frames Received Length=1519-2047.",
        "28: Frames Received Length=2048-4095.",
        "29: Frames Received Length=4096-8191.",
        "30: Frames Received Length=8192-9215.",
        "31: Frames Received Length>=9216.",
        "32: Frames Transmitted O.K",
        "33: Frames Transmitted All (Good/Bad Frames)",
        "34: Frames Transmitted with Error",
        "35: Octets Transmitted with out error",
        "36: Octets Transmitted Total (Good/Error)",
        "37: Frames Transmitted Unicast",
        "38: Frames Transmitted Multicast",
        "39: Frames Transmitted Broadcast",
        "40: Frames Transmitted Pause",
        "41: Frames Transmitted PriPause",
        "42: Frames Transmitted VLAN.",
        "43: Frames Transmitted Length<64",
        "44: Frames Transmitted Length=64.",
        "45: Frames Transmitted Length=65-127.",
        "46: Frames Transmitted Length=128-255.",
        "47: Frames Transmitted Length=256-511.",
        "48: Frames Transmitted Length=512-1023.",
        "49: Frames Transmitted Length=1024-1518.",
        "50: Frames Transmitted Length=1519-2047.",
        "51: Frames Transmitted Length=2048-4095.",
        "52: Frames Transmitted Length=4096-8191.",
        "53: Frames Transmitted Length=8192-9215.",
        "54: Frames Transmitted Length>=9216.",
        "55: Pri#0 Frames Transmitted.",
        "56: Pri#1 Frames Transmitted.",
        "57: Pri#2 Frames Transmitted.",
        "58: Pri#3 Frames Transmitted.",
        "59: Pri#4 Frames Transmitted.",
        "60: Pri#5 Frames Transmitted.",
        "61: Pri#6 Frames Transmitted.",
        "62: Pri#7 Frames Transmitted.",
        "63: Pri#0 Frames Received.",
        "64: Pri#1 Frames Received.",
        "65: Pri#2 Frames Received.",
        "66: Pri#3 Frames Received.",
        "67: Pri#4 Frames Received.",
        "68: Pri#5 Frames Received.",
        "69: Pri#6 Frames Received.",
        "70: Pri#7 Frames Received.",
        "71: Transmit Pri#0 Pause 1US Count.",
        "72: Transmit Pri#1 Pause 1US Count.",
        "73: Transmit Pri#2 Pause 1US Count.",
        "74: Transmit Pri#3 Pause 1US Count.",
        "75: Transmit Pri#4 Pause 1US Count.",
        "76: Transmit Pri#5 Pause 1US Count.",
        "77: Transmit Pri#6 Pause 1US Count.",
        "78: Transmit Pri#7 Pause 1US Count.",
        "79: Receive Pri#00 Pause 1US Count.",
        "80: Receive Pri#1 Pause 1US Count.",
        "81: Receive Pri#2 Pause 1US Count.",
        "82: Receive Pri#3 Pause 1US Count.",
        "83: Receive Pri#4 Pause 1US Count.",
        "84: Receive Pri#5 Pause 1US Count.",
        "85: Receive Pri#6 Pause 1US Count.",
        "86: Receive Pri#7 Pause 1US Count.",
        "87: Receive Standard Pause 1US Count.",
        "88: Frames Truncated.",
        "89: FSIG CRC Error",
        NULL
    };

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdPortStatisticsGet: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    linesNum = mcdPortGetLanesNum(
        pDev, mdioPort, host_or_line);
    if (linesNum == 0)
    {
        MCD_DBG_ERROR("mcdPortStatisticsGet: incorrect port selection: %uh\n", mdioPort);
        return MCD_FAIL;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);

    if(host_or_line == MCD_LINE_SIDE)
        side = MCD_SIDE_LINE;
    else
        side = MCD_SIDE_HOST;

    regAddr = rdctrl_regs[side][slice];

    /* set channel num  */
    rc = mcdHwSetPhyRegField32bit(pDev, mdioPort, regAddr, 7, 2, chan);
    if(rc != MCD_OK)
    {
        MCD_DBG_ERROR("mcdPortStatisticsGet: failed in set register: 0x%X\n", regAddr);
        return MCD_FAIL;
    }

    /* set clear-on-read flag */
    rc = mcdHwSetPhyRegField32bit(pDev, mdioPort, regAddr, 13, 1, 1);
    if(rc != MCD_OK)
    {
        MCD_DBG_ERROR("mcdPortStatisticsGet: failed in set register: 0x%X\n", regAddr);
        return MCD_FAIL;
    }

    i=0;
    aline = statistics[0];
    while(aline != NULL)
    {
        /* polling until bit15 is cleared*/
        value = 1;
        j=0;
        do
        {
            rc = mcdHwGetPhyRegField32bit(pDev, mdioPort, regAddr, 15, 1, &value);
            if(rc != MCD_OK)
            {
                MCD_DBG_ERROR("mcdPortStatisticsGet: failed in read register: 0x%X\n", regAddr);
                return MCD_FAIL;
            }
            if(j>0)
                printf("%d, %d, waiting for clear value = %d\n", i, j, value);
            j++;
        }while(value!=0);

        /* i sets what type of counter to read */
        rc = mcdHwSetPhyRegField32bit(pDev, mdioPort, regAddr, 0, 7, i);
        if(rc != MCD_OK)
        {
            MCD_DBG_ERROR("mcdPortStatisticsGet: failed in set register: 0x%X\n", regAddr);
            return MCD_FAIL;
        }

        /* trigger the reading */
        rc = mcdHwSetPhyRegField32bit(pDev, mdioPort, regAddr, 15, 1, 1);
        if(rc != MCD_OK)
        {
            MCD_DBG_ERROR("mcdPortStatisticsGet: failed in set register: 0x%X\n", regAddr);
            return MCD_FAIL;
        }

        /* polling until bit15 is cleared*/
        value = 1;
        j=0;
        do
        {
            rc = mcdHwGetPhyRegField32bit(pDev, mdioPort, regAddr, 15, 1, &value);
            if(rc != MCD_OK)
            {
                MCD_DBG_ERROR("mcdPortStatisticsGet: failed in read register: 0x%X\n", regAddr);
                return MCD_FAIL;
            }
            if(j>0)
                MCD_DBG_INFO("%d, %j, waiting for clear value = %d\n", i, j, value);
            j++;
        }while(value!=0);

        /* read the counter */
        rc = mcdHwGetPhyRegField32bit(pDev, mdioPort, rdata3_regs[side][slice], 0, 16, (MCD_U32 *)&data3);
        if(rc != MCD_OK)
        {
            MCD_DBG_ERROR("mcdPortStatisticsGet: failed in get register: 0x%X\n", rdata3_regs[side][slice]);
            return MCD_FAIL;
        }
        rc = mcdHwGetPhyRegField32bit(pDev, mdioPort, rdata2_regs[side][slice], 0, 16, (MCD_U32 *)&data2);
        if(rc != MCD_OK)
        {
            MCD_DBG_ERROR("mcdPortStatisticsGet: failed in get register: 0x%X\n", rdata2_regs[side][slice]);
            return MCD_FAIL;
        }
        rc = mcdHwGetPhyRegField32bit(pDev, mdioPort, rdata1_regs[side][slice], 0, 16, (MCD_U32 *)&data1);
        if(rc != MCD_OK)
        {
            MCD_DBG_ERROR("mcdPortStatisticsGet: failed in get register: 0x%X\n", rdata1_regs[side][slice]);
            return MCD_FAIL;
        }
        rc = mcdHwGetPhyRegField32bit(pDev, mdioPort, rdata0_regs[side][slice], 0, 16, (MCD_U32 *)&data0);
        if(rc != MCD_OK)
        {
            MCD_DBG_ERROR("mcdPortStatisticsGet: failed in get register: 0x%X\n", rdata0_regs[side][slice]);
            return MCD_FAIL;
        }

        counter64 = ((MCD_U64)data3<<48) | ((MCD_U64)data2<<32) | ((MCD_U64)data1<<16) | (MCD_U64)data0;
        if(reducedPrint)
        {
            if(counter64 > 0)
                 printf("%-60s : %llx\n", statistics[i], counter64);
        }
        else
           printf("%-60s : %llx\n", statistics[i], counter64);
        i++;
        /* go to the next counter */
        aline = statistics[i];
    }

    return 0;
}

#endif /*#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3*/



