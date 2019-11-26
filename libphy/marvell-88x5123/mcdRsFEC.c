/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
*******************************************************************************/

/************************************************************************
This file contains functions to configure RS-FEC and read RS-FEC status
************************************************************************/
#include "mcdApiRegs.h"
#include "mcdApiTypes.h"
#include "mcdAPI.h"
#include "mcdHwCntl.h"
#include "mcdRsFEC.h"
#include "mcdUtils.h"
#include "mcdAPIInternal.h"

/*******************************************************************************
 MCD_STATUS mcdSetRsFecControl
*******************************************************************************/
MCD_STATUS mcdSetRsFecControl
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 bypassIndicationEnable,
    IN MCD_U16 bypassCorrectionEnable
)
{
    MCD_U32        regAddr;
    MCD_U32        hwBypassIndicationEnable;
    MCD_U32        hwBypassCorrectionEnable;
    MCD_U32        hwPattern, hwMask;
    MCD_U32        slice, chan;
    MCD_MODE_SPEED speed;
    MCD_MODE       mode;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdSetRsFecControl: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSetRsFecControl: incorrect port selection: %uh\n", mdioPort);
        return MCD_FAIL;
    }

    ATTEMPT(mcdGetModeSpeed(pDev, mdioPort, MCD_LINE_SIDE, &speed, &mode));

    if (mcdIsPortModePcsControlled(mode) == 0)
    {
        MCD_DBG_ERROR("mcdSetRsFecControl: not in PCS mode\n");
        return MCD_FAIL;
    }

    if (speed == MCD_1GB)
    {
        MCD_DBG_ERROR("mcdSetRsFecControl: speed is 1 GB, FEC not supported\n");
        return MCD_FAIL;
    }

    switch (bypassIndicationEnable)
    {
        case MCD_ENABLE:
            hwBypassIndicationEnable = 1;
            break;
        case MCD_DISABLE:
            hwBypassIndicationEnable = 0;
            break;
        default:
            MCD_DBG_ERROR("mcdSetRsFecControl: bypassIndicationEnable is invalid\n");
            return MCD_FAIL;
    }

    switch (bypassCorrectionEnable)
    {
        case MCD_ENABLE:
            hwBypassCorrectionEnable = 1;
            break;
        case MCD_DISABLE:
            hwBypassCorrectionEnable = 0;
            break;
        default:
            MCD_DBG_ERROR("mcdSetRsFecControl: bypassCorrectionEnable is invalid\n");
            return MCD_FAIL;
    }

    /*<UMAC> UMAC/Slice %m/umac3gbsx4/fecrs0/ctrl*/
    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);
    regAddr = UMAC_FECRS_ctrl(slice,chan);
    regAddr = UMAC_FECRS_LINE_REG_ADDR(regAddr); /* API for line side only */
    hwPattern = ((hwBypassIndicationEnable << 1) | hwBypassCorrectionEnable);
    hwMask    = 3;

    ATTEMPT(mcdHwSetPhyRegMask32bit(
        pDev, mdioPort, regAddr, hwMask, hwPattern));

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdGetRsFecStatus
*******************************************************************************/
MCD_STATUS mcdGetRsFecStatus
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    OUT MCD_U16 *pcsLaneAlignment,
    OUT MCD_U16 *fecLaneAlignment,
    OUT MCD_U16 *latchedRsFecHighErr,
    OUT MCD_U16 *currRsFecHighErr
)
{
    MCD_U32        regAddr;
    MCD_U32        hwData;
    MCD_U32        slice, chan;
    MCD_MODE_SPEED speed;
    MCD_MODE       mode;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdGetRsFecStatus: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdGetRsFecStatus: incorrect port selection: %uh\n", mdioPort);
        return MCD_FAIL;
    }

    ATTEMPT(mcdGetModeSpeed(pDev, mdioPort, MCD_LINE_SIDE, &speed, &mode));

    if (mcdIsPortModePcsControlled(mode) == 0)
    {
        MCD_DBG_ERROR("mcdGetRsFecStatus: not in PCS mode\n");
        return MCD_FAIL;
    }

    if (speed == MCD_1GB)
    {
        MCD_DBG_ERROR("mcdGetRsFecStatus: speed is 1 GB, FEC not supported\n");
        return MCD_FAIL;
    }

    /*<UMAC> UMAC/Slice %m/umac3gbsx4/fecrs0/sts*/
    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);
    regAddr = UMAC_FECRS_sts(slice,chan);
    regAddr = UMAC_FECRS_LINE_REG_ADDR(regAddr); /* API for line side only */

    ATTEMPT(mcdHwXmdioRead32bit(
        pDev, mdioPort, regAddr, &hwData));

    *pcsLaneAlignment     = 1; /* not supported */
    *fecLaneAlignment     = (MCD_U16)((hwData >> 14) & 1);
    *latchedRsFecHighErr  = (MCD_U16)((hwData >> 2) & 1);

    ATTEMPT(mcdHwXmdioRead32bit(
        pDev, mdioPort, regAddr, &hwData));
    *currRsFecHighErr     = (MCD_U16)((hwData >> 2) & 1);

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdGetRsFecPCSAlignmentStatus
*******************************************************************************/
MCD_STATUS mcdGetRsFecPCSAlignmentStatus
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16  pcs_lane,
    OUT MCD_U16 *blockLocked,
    OUT MCD_U16 *laneAligned
)
{
    MCD_U32        regAddr;
    MCD_U32        hwData;
    MCD_U32        slice, chan;
    MCD_MODE_SPEED speed;
    MCD_MODE       mode;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdGetRsFecPCSAlignmentStatus: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdGetRsFecPCSAlignmentStatus: incorrect port selection: %uh\n", mdioPort);
        return MCD_FAIL;
    }

    ATTEMPT(mcdGetModeSpeed(pDev, mdioPort, MCD_LINE_SIDE, &speed, &mode));

    if (mcdIsPortModePcsControlled(mode) == 0)
    {
        MCD_DBG_ERROR("mcdGetRsFecPCSAlignmentStatus: not in PCS mode\n");
        return MCD_FAIL;
    }

    if (speed == MCD_1GB)
    {
        MCD_DBG_ERROR("mcdGetRsFecPCSAlignmentStatus: speed is 1 GB, FEC not supported\n");
        return MCD_FAIL;
    }

    if (pcs_lane > 19)
    {
        MCD_DBG_ERROR("mcdGetRsFecPCSAlignmentStatus: pcs_lane number is wrong\n");
        return MCD_FAIL;
    }

    /*<UMAC> UMAC/Slice %m/umac3gbsx4/hsmcpcs0/algnstat1*/
    /*<UMAC> UMAC/Slice %m/umac3gbsx4/hsmcpcs0/algnstat2*/
    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);

    regAddr = UMAC_MCPCS_Multi_lane_BASE_R_PCS_Alignment_Status1(slice,chan);
    regAddr = UMAC_MCPCS_LINE_REG_ADDR(regAddr); /* API for line side only */
    ATTEMPT(mcdHwXmdioRead32bit(
        pDev, mdioPort, regAddr, &hwData));
    /* bit12 - alignstatus - common for all lines */
    *laneAligned = (MCD_U16)((hwData >> 12) & 1);
    if (pcs_lane < 8)
    {
        *blockLocked = (MCD_U16)((hwData >> pcs_lane) & 1); /*bits0-7 - blocklock*/
    }
    else
    {
        regAddr = UMAC_MCPCS_Multi_lane_BASE_R_PCS_Alignment_Status2(slice,chan);
        regAddr = UMAC_MCPCS_LINE_REG_ADDR(regAddr); /* API for line side only */
        ATTEMPT(mcdHwXmdioRead32bit(
            pDev, mdioPort, regAddr, &hwData));
        *blockLocked = (MCD_U16)((hwData >> (pcs_lane - 8)) & 1); /*bits0-11 - blocklock*/
    }

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdGetRsFecPMALaneMapping
*******************************************************************************/
MCD_STATUS mcdGetRsFecPMALaneMapping
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    OUT MCD_U16 mapping[MCD_NUM_LANES]
)
{
    MCD_U32        regAddr;
    MCD_U32        hwData;
    MCD_U32        slice, chan, lane;
    MCD_MODE_SPEED speed;
    MCD_MODE       mode;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdGetRsFecPMALaneMapping: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdGetRsFecPMALaneMapping: incorrect port selection: %uh\n", mdioPort);
        return MCD_FAIL;
    }

    ATTEMPT(mcdGetModeSpeed(pDev, mdioPort, MCD_LINE_SIDE, &speed, &mode));

    if (mcdIsPortModePcsControlled(mode) == 0)
    {
        MCD_DBG_ERROR("mcdGetRsFecPMALaneMapping: not in PCS mode\n");
        return MCD_FAIL;
    }

    if (speed == MCD_1GB)
    {
        MCD_DBG_ERROR("mcdGetRsFecPMALaneMapping: speed is 1 GB, FEC not supported\n");
        return MCD_FAIL;
    }

    /*<UMAC> UMAC/Slice %m/umac3gbsx4/fecrs0/lanemapping*/
    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);
    regAddr = UMAC_FECRS_lanemapping(slice,chan);
    regAddr = UMAC_FECRS_LINE_REG_ADDR(regAddr); /* API for line side only */

    ATTEMPT(mcdHwXmdioRead32bit(
        pDev, mdioPort, regAddr, &hwData));

    for (lane = 0; (lane < MCD_NUM_LANES); lane++)
    {
        mapping[lane] = (MCD_U16)((hwData >> (8 + (lane * 2))) & 3);
    }

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdGetRsFecPCSLaneMapping
*******************************************************************************/
MCD_STATUS mcdGetRsFecPCSLaneMapping
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 pcs_lane,
    OUT MCD_U16 *interface_lane
)
{
    MCD_U32        regAddr;
    MCD_U32        hwData;
    MCD_U32        slice, chan;
    MCD_MODE_SPEED speed;
    MCD_MODE       mode;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdGetRsFecPCSLaneMapping: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdGetRsFecPCSLaneMapping: incorrect port selection: %uh\n", mdioPort);
        return MCD_FAIL;
    }

    ATTEMPT(mcdGetModeSpeed(pDev, mdioPort, MCD_LINE_SIDE, &speed, &mode));

    if (mcdIsPortModePcsControlled(mode) == 0)
    {
        MCD_DBG_ERROR("mcdGetRsFecPCSLaneMapping: not in PCS mode\n");
        return MCD_FAIL;
    }

    if (speed == MCD_1GB)
    {
        MCD_DBG_ERROR("mcdGetRsFecPCSLaneMapping: speed is 1 GB, FEC not supported\n");
        return MCD_FAIL;
    }

    if (pcs_lane > 19)
    {
        MCD_DBG_ERROR("mcdGetRsFecPCSLaneMapping: pcs_lane number is wrong\n");
        return MCD_FAIL;
    }

    /*<UMAC> UMAC/Slice %m/umac3gbsx4/hsmcpcs0/lanemapping0-19*/
    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);
    regAddr = (UMAC_MCPCS_Lane0_Mapping(slice,chan) + (pcs_lane * 4));
    regAddr = UMAC_MCPCS_LINE_REG_ADDR(regAddr); /* API for line side only */

    ATTEMPT(mcdHwXmdioRead32bit(
        pDev, mdioPort, regAddr, &hwData));

    *interface_lane = (MCD_U16)(hwData & 0x1F);

    return MCD_OK;
}

/**
* @internal mcdGetFecCorrectedCwCntr function
* @endinternal
*
* @brief   Reading the FEC corrected counter
*
* @param[in] devNum
* @param[in] mdio_port - port number
* @param[in] host_or_line
* @param[in] fecCorrect type, FC or RS
* @param[out] codeWordCounter - the return value
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdGetFecCorrectedCwCntr
(
    IN MCD_DEV_PTR  pDev,
    IN MCD_U16      mdioPort,
    IN MCD_U16      host_or_line,
    IN MCD_FEC_TYPE fecCorrect,
    OUT MCD_U32     *codeWordCounter
)
{
    MCD_U32        regAddr;
    MCD_U32        hwDataLow = 0, hwDataHigh = 0;
    MCD_U32        slice, chan;
    MCD_MODE_SPEED speed;
    MCD_MODE       mode;

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

    ATTEMPT(mcdGetModeSpeed(pDev, mdioPort, host_or_line, &speed, &mode));

    if (mcdIsPortModePcsControlled(mode) == 0)
    {
        MCD_DBG_ERROR("%s: not in PCS mode\n", __func__);
        return MCD_FAIL;
    }

    if (speed == MCD_1GB)
    {
        MCD_DBG_ERROR("$s: speed is 1 GB, FEC not supported\n", __func__);
        return MCD_FAIL;
    }

    /*<UMAC> UMAC/Slice %m/umac3gbsx4/fecrs0/corrcntlo*/
    /*<UMAC> UMAC/Slice %m/umac3gbsx4/fecrs0/corrcnthi*/
    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);

    if (fecCorrect & (MCD_RS_FEC | MCD_RS_FEC_HOST | MCD_RS_FEC_LINE))
    {
        regAddr = UMAC_FECRS_corrcntlo(slice,chan);
        if (host_or_line == MCD_LINE_SIDE) {
            regAddr = UMAC_FECRS_LINE_REG_ADDR(regAddr); /* API for line side only */
        }
        ATTEMPT(mcdHwXmdioRead32bit(
            pDev, mdioPort, regAddr, &hwDataLow));

        regAddr = UMAC_FECRS_corrcnthi(slice,chan);
        if (host_or_line == MCD_LINE_SIDE) {
            regAddr = UMAC_FECRS_LINE_REG_ADDR(regAddr); /* API for line side only */
        }
        ATTEMPT(mcdHwXmdioRead32bit(
            pDev, mdioPort, regAddr, &hwDataHigh));
    }

    if (fecCorrect & (MCD_FC_FEC | MCD_FC_FEC_HOST | MCD_FC_FEC_LINE))
    {
        MCD_DBG_ERROR("%s: FC_FEC counter read not supported.\n", __func__);
    }

    *codeWordCounter = (((hwDataHigh & 0xFFFF) << 16) | (hwDataLow & 0xFFFF));

    return MCD_OK;
}

/**
* @internal mcdGetFecUnCorrectedCwCntr function
* @endinternal
*
* @brief   Reading the FEC un-corrected counter
*
* @param[in] devNum
* @param[in] mdio_port - port number
* @param[in] host_or_line
* @param[in] fecCorrect type, FC or RS
* @param[out] codeWordCounter - the return value
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdGetFecUnCorrectedCwCntr
(
    IN MCD_DEV_PTR  pDev,
    IN MCD_U16      mdioPort,
    IN MCD_U16      host_or_line,
    IN MCD_FEC_TYPE fecCorrect,
    OUT MCD_U32     *codeWordCounter
)
{
    MCD_U32        regAddr;
    MCD_U32        hwDataLow = 0, hwDataHigh = 0;
    MCD_U32        slice, chan;
    MCD_MODE_SPEED speed;
    MCD_MODE       mode;

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

    ATTEMPT(mcdGetModeSpeed(pDev, mdioPort, MCD_LINE_SIDE, &speed, &mode));

    if (mcdIsPortModePcsControlled(mode) == 0)
    {
        MCD_DBG_ERROR("%s: not in PCS mode\n", __func__);
        return MCD_FAIL;
    }

    if (speed == MCD_1GB)
    {
        MCD_DBG_ERROR("%s: speed is 1 GB, FEC not supported\n", __func__);
        return MCD_FAIL;
    }

    /*<UMAC> UMAC/Slice %m/umac3gbsx4/fecrs0/uncorrcntlo*/
    /*<UMAC> UMAC/Slice %m/umac3gbsx4/fecrs0/uncorrcnthi*/
    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);

    if (fecCorrect & (MCD_RS_FEC | MCD_RS_FEC_HOST | MCD_RS_FEC_LINE))
    {
        regAddr = UMAC_FECRS_uncorrcntlo(slice,chan);
        if (host_or_line == MCD_LINE_SIDE) {
            regAddr = UMAC_FECRS_LINE_REG_ADDR(regAddr); /* API for line side only */
        }
        ATTEMPT(mcdHwXmdioRead32bit(
            pDev, mdioPort, regAddr, &hwDataLow));

        regAddr = UMAC_FECRS_uncorrcnthi(slice,chan);
        if (host_or_line == MCD_LINE_SIDE) {
            regAddr = UMAC_FECRS_LINE_REG_ADDR(regAddr); /* API for line side only */
        }
        ATTEMPT(mcdHwXmdioRead32bit(
        pDev, mdioPort, regAddr, &hwDataHigh));
    }

    if (fecCorrect & (MCD_FC_FEC | MCD_FC_FEC_HOST | MCD_FC_FEC_LINE))
    {
        MCD_DBG_ERROR("%s: FC_FEC counter read not supported.\n", __func__);
    }

    *codeWordCounter = (((hwDataHigh & 0xFFFF) << 16) | (hwDataLow & 0xFFFF));

    return MCD_OK;
}

/**
* @internal mcdGetFecSymbolErrorCntr function
* @endinternal
*
* @brief   Reading the FEC symbol error counter
*
* @param[in] devNum
* @param[in] mdio_port - port number
* @param[in] lane - within the port #
* @param[in] host_or_line
* @param[in] fecCorrect type, FC or RS
* @param[out] errorCounter - the return value
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdGetFecSymbolErrorCntr
(
    IN MCD_DEV_PTR  pDev,
    IN MCD_U16      mdioPort,
    IN MCD_U16      lane,
    IN MCD_U16      host_or_line,
    IN MCD_FEC_TYPE fecCorrect,
    OUT MCD_U32     *errorCounter
)
{
    MCD_U32        regAddr;
    MCD_U32        hwDataLow = 0, hwDataHigh = 0;
    MCD_U32        slice, chan;
    MCD_MODE_SPEED speed;
    MCD_MODE       mode;

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

    ATTEMPT(mcdGetModeSpeed(pDev, mdioPort, MCD_LINE_SIDE, &speed, &mode));

    if (mcdIsPortModePcsControlled(mode) == 0)
    {
        MCD_DBG_ERROR("%s: not in PCS mode\n", __func__);
        return MCD_FAIL;
    }

    if (speed == MCD_1GB)
    {
        MCD_DBG_ERROR("%s: speed is 1 GB, FEC not supported\n", __func__);
        return MCD_FAIL;
    }

    if (lane > 3)
    {
        MCD_DBG_ERROR("%s: wrong lane\n", __func__);
        return MCD_FAIL;
    }

    /*<UMAC> UMAC/Slice %m/umac3gbsx4/fecrs0/serlane0lo 0-3*/
    /*<UMAC> UMAC/Slice %m/umac3gbsx4/fecrs0/serlane0hi 0-3*/
    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);

    if (fecCorrect & (MCD_RS_FEC | MCD_RS_FEC_HOST | MCD_RS_FEC_LINE))
    {
        regAddr = (UMAC_FECRS_serlane0lo(slice,chan) + (lane * 4));
        if (host_or_line == MCD_LINE_SIDE) {
            regAddr = UMAC_FECRS_LINE_REG_ADDR(regAddr); /* API for line side only */
        }
        ATTEMPT(mcdHwXmdioRead32bit(
            pDev, mdioPort, regAddr, &hwDataLow));

        regAddr = (UMAC_FECRS_serlane0hi(slice,chan) + (lane * 4));
        if (host_or_line == MCD_LINE_SIDE) {
            regAddr = UMAC_FECRS_LINE_REG_ADDR(regAddr); /* API for line side only */
        }
        ATTEMPT(mcdHwXmdioRead32bit(
            pDev, mdioPort, regAddr, &hwDataHigh));
    }

    if (fecCorrect & (MCD_FC_FEC | MCD_FC_FEC_HOST | MCD_FC_FEC_LINE))
    {
        MCD_DBG_ERROR("%s: FC_FEC counter read not supported.\n", __func__);
    }

    *errorCounter = (((hwDataHigh & 0xFFFF) << 16) | (hwDataLow & 0xFFFF));

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdGetRsFecBipErrorCntr
*******************************************************************************/
MCD_STATUS mcdGetRsFecBipErrorCntr
(
    IN MCD_DEV_PTR  pDev,
    IN MCD_U16      mdioPort,
    IN MCD_U16      pcs_lane,
    OUT MCD_U16     *errorCounter
)
{
    MCD_U32        regAddr;
    MCD_U32        hwData = 0;
    MCD_U32        slice, chan;
    MCD_MODE_SPEED speed;
    MCD_MODE       mode;

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

    ATTEMPT(mcdGetModeSpeed(pDev, mdioPort, MCD_LINE_SIDE, &speed, &mode));

    if (mcdIsPortModePcsControlled(mode) == 0)
    {
        MCD_DBG_ERROR("%s: not in PCS mode\n", __func__);
        return MCD_FAIL;
    }

    if (speed == MCD_1GB)
    {
        MCD_DBG_ERROR("%s: speed is 1 GB, FEC not supported\n", __func__);
        return MCD_FAIL;
    }

    if (pcs_lane > 19)
    {
        MCD_DBG_ERROR("%s: line number is wrong\n", __func__);
        return MCD_FAIL;
    }

    /*<UMAC> UMAC/Slice %m/umac3gbsx4/hsmcpcs0/biperrorsln0-19*/
    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);
    regAddr = (UMAC_MCPCS_BIP_error_counter_lane0(slice,chan) + (pcs_lane * 4));
    regAddr = UMAC_MCPCS_LINE_REG_ADDR(regAddr); /* API for line side only */

    ATTEMPT(mcdHwXmdioRead32bit(
        pDev, mdioPort, regAddr, &hwData));

    *errorCounter = (MCD_U16)(hwData & 0xFFFF);

    return MCD_OK;
}

