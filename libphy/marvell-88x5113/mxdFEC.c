/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/


/************************************************************************
This file contains functions to configure RS-FEC/KR-FEC
and read RS-FEC/KR-FEC status
************************************************************************/
#include "mxdApiRegs.h"
#include "mxdApiTypes.h"
#include "mxdAPI.h"
#include "mxdAPIInternal.h"
#include "mxdHwCntl.h"
#include "mxdFEC.h"
#include "mxdUtils.h"


/*******************************************************************************
 MXD_STATUS mxdSetRsFecControl
*******************************************************************************/
MXD_STATUS mxdSetRsFecControl
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_U16 bypassIndicationEnable,
    IN MXD_U16 bypassCorrectionEnable
)
{
    MXD_OP_CONFIG opConfig;
    MXD_U16 hostRegOffset=0,rsRegOffset=0;

    ATTEMPT(mxdCheckFecLaneOffset(pDev, mdioPort, host_or_line, laneOffset, MXD_RS_FEC));

    if (host_or_line == MXD_HOST_SIDE)
    {
        opConfig = pDev->hostConfig[laneOffset].opConfig;
        hostRegOffset = MXD_HOST_REG_OFFSET;
    }
    else  if (host_or_line == MXD_LINE_SIDE)
    {
        opConfig = pDev->lineConfig[laneOffset].opConfig;
    }
    else
    {
        MXD_DBG_ERROR("mxdSetRsFecControl: Incorrect line_or_host selection: \n");
        return MXD_FAIL;
    }

    switch(opConfig)  
    {
        case MXD_P25CR:
        case MXD_P25KR:
        case MXD_P25BR:
        case MXD_P25JR:
        case MXD_P25LR:
        case MXD_P25BCR:
        case MXD_P25JKR:
            rsRegOffset = (MXD_RSFEC_CNTL+hostRegOffset+(laneOffset*MXD_FEC_REG_OFFSET));
            break;

        case MXD_P50MR:
        case MXD_P50JR:
        case MXD_P50BR:
        case MXD_P100LR:
        case MXD_P100CR:
        case MXD_P100KR:
            rsRegOffset = (MXD_RSFEC4_CNTL+hostRegOffset);
            break;

        default:
            MXD_DBG_ERROR("mxdSetRsFecControl: invalid operation mode for FEC operation\n");
            return MXD_FAIL;
            break;
    }

    if (bypassIndicationEnable == MXD_ENABLE)
    {
        ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, rsRegOffset, 1, 1, MXD_ENABLE));
    }
    else if(bypassIndicationEnable == MXD_DISABLE)
    {
        ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, rsRegOffset, 1, 1, MXD_DISABLE));
    }
    else
    {
        MXD_DBG_ERROR("mxdSetRsFecControl: bypassIndicationEnable is invalid\n");
        return MXD_FAIL;
    }

    if (bypassCorrectionEnable == MXD_ENABLE)
    {
        ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, rsRegOffset, 0, 1, MXD_ENABLE));
    }
    else if(bypassCorrectionEnable == MXD_DISABLE)
    {
        ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, rsRegOffset, 0, 1, MXD_DISABLE));
    }
    else
    {
        MXD_DBG_ERROR("mxdSetRsFecControl: bypassCorrectionEnable is invalid\n");
        return MXD_FAIL;
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetRsFecStatus
*******************************************************************************/
MXD_STATUS mxdGetRsFecStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U16 *pcsLaneAlignment,
    OUT MXD_U16 *fecLaneAlignment,
    OUT MXD_U16 *rsFecLaneAMLock,
    OUT MXD_U16 *latchedRsFecHighErr,
    OUT MXD_U16 *currRsFecHighErr
)
{
    MXD_OP_CONFIG opConfig;
    MXD_U16 hostRegOffset = 0,rsRegOffset=0;

    ATTEMPT(mxdCheckFecLaneOffset(pDev, mdioPort, host_or_line, laneOffset, MXD_RS_FEC));

    if (host_or_line == MXD_HOST_SIDE)
    {
        opConfig = pDev->hostConfig[laneOffset].opConfig;
        hostRegOffset = MXD_HOST_REG_OFFSET;
    }
    else  if (host_or_line == MXD_LINE_SIDE)
    {
        opConfig = pDev->lineConfig[laneOffset].opConfig;
    }
    else
    {
        MXD_DBG_ERROR("mxdGetRsFecStatus: Incorrect line_or_host selection: \n");
        return MXD_FAIL;
    }

    switch(opConfig)        
    {
        case MXD_P25CR:
        case MXD_P25KR:
        case MXD_P25BR:
        case MXD_P25JR:
        case MXD_P25LR:
        case MXD_P25BCR:
        case MXD_P25JKR:
            rsRegOffset = (MXD_RSFEC_STATUS+hostRegOffset+(laneOffset*MXD_FEC_REG_OFFSET));
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, rsRegOffset, 15, 1, pcsLaneAlignment));
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, rsRegOffset, 14, 1, fecLaneAlignment));
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, rsRegOffset,  2, 1, latchedRsFecHighErr));
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, rsRegOffset,  2, 1, currRsFecHighErr));
            *rsFecLaneAMLock = 0; /* NA for 25GB RS-FEC */
            break;

        case MXD_P50MR:
        case MXD_P50JR:
        case MXD_P50BR:
        case MXD_P100LR:
        case MXD_P100CR:
        case MXD_P100KR:
            rsRegOffset = (MXD_RSFEC4_STATUS+hostRegOffset);
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, rsRegOffset, 15, 1, pcsLaneAlignment));
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, rsRegOffset, 14, 1, fecLaneAlignment));

            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, rsRegOffset, 8, 4, rsFecLaneAMLock));

            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, rsRegOffset,  2, 1, latchedRsFecHighErr));
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, rsRegOffset,  2, 1, currRsFecHighErr));
            break;

        default:
            MXD_DBG_ERROR("mxdGetRsFecStatus: invalid operation mode for FEC operation\n");
            return MXD_FAIL;
            break;
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetRsFecPCSAlignmentStatus
*******************************************************************************/
MXD_STATUS mxdGetRsFecPCSAlignmentStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  pcs_lane,
    OUT MXD_U16 *blockLocked,
    OUT MXD_U16 *laneAligned
)
{
    MXD_U8 laneMap = (MXD_U8)((pcs_lane<8) ? pcs_lane:(pcs_lane-8));
    MXD_OP_CONFIG opConfig;
    MXD_U16 hostRegOffset = 0;

    /* initialized output */
    *blockLocked = *laneAligned = 0;

    if (host_or_line == MXD_HOST_SIDE)
    {
        opConfig = pDev->hostConfig[0].opConfig;
        hostRegOffset = MXD_HOST_REG_OFFSET;
    }
    else  if (host_or_line == MXD_LINE_SIDE)
    {
        opConfig = pDev->lineConfig[0].opConfig;
    }
    else
    {
        MXD_DBG_ERROR("mxdGetRsFecPCSAlignmentStatus: Incorrect line_or_host selection: \n");
        return MXD_FAIL;
    }

    if (pcs_lane >= MXD_NUM_PCS_LANES)
    {
        MXD_DBG_ERROR("mxdGetRsFecPCSAlignmentStatus: pcs_lane is invalid\n");
        return MXD_FAIL;
    }

    switch(opConfig)
    {
        case MXD_P100LR:
        case MXD_P100CR:
        case MXD_P100KR:
            if (pcs_lane < 8)
            {
                ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, (MXD_RSFEC_PCS_ALIGN_STATUS1+hostRegOffset), laneMap, 1, blockLocked));
                ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, (MXD_RSFEC_PCS_ALIGN_STATUS3+hostRegOffset), laneMap, 1, laneAligned));
            }
            else if (pcs_lane < MXD_NUM_PCS_LANES)
            {
                ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, (MXD_RSFEC_PCS_ALIGN_STATUS2+hostRegOffset), laneMap, 1, blockLocked));
                ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, (MXD_RSFEC_PCS_ALIGN_STATUS4+hostRegOffset), laneMap, 1, laneAligned));
            }
            else
            {
                MXD_DBG_ERROR("mxdGetRsFecPCSAlignmentStatus: pcs_lane is invalid\n");
                return MXD_FAIL;
            }
            break;

        case MXD_P50MR:
        case MXD_P50JR:
        case MXD_P50BR:
            if (pcs_lane < 4)
            {
                ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, (MXD_RSFEC_PCS_ALIGN_STATUS1+hostRegOffset), laneMap, 1, blockLocked));
                ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, (MXD_RSFEC_PCS_ALIGN_STATUS3+hostRegOffset), laneMap, 1, laneAligned));
            }
            else
            {
                MXD_DBG_ERROR("mxdGetRsFecPCSAlignmentStatus: pcs_lane invalid. 50G pcs_lane from 0-3\n");
                return MXD_FAIL;
            }
            break;

        default:
            MXD_DBG_ERROR("mxdGetRsFecPCSAlignmentStatus: invalid operation mode for FEC operation\n");
            return MXD_FAIL;
            break;
    }


    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetRsFecPMALaneMapping
*******************************************************************************/
MXD_STATUS mxdGetRsFecPMALaneMapping
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    OUT MXD_U16 mapping[MXD_NUM_LANES]
)
{
    MXD_OP_CONFIG opConfig;
    MXD_U16 hostRegOffset = 0;

    if (host_or_line == MXD_HOST_SIDE)
    {
        opConfig = pDev->hostConfig[0].opConfig;
        hostRegOffset = MXD_HOST_REG_OFFSET;
    }
    else  if (host_or_line == MXD_LINE_SIDE)
    {
        opConfig = pDev->lineConfig[0].opConfig;
    }
    else
    {
        MXD_DBG_ERROR("mxdGetRsFecPMALaneMapping: Incorrect line_or_host selection: \n");
        return MXD_FAIL;
    }

    switch(opConfig)
    {
        case MXD_P100LR:
        case MXD_P100CR:
        case MXD_P100KR:
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, (MXD_RSFEC_LANE_MAPPING+hostRegOffset), 0, 2, &mapping[0]));
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, (MXD_RSFEC_LANE_MAPPING+hostRegOffset), 2, 2, &mapping[1]));
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, (MXD_RSFEC_LANE_MAPPING+hostRegOffset), 4, 2, &mapping[2])); /* NA if 50G */
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, (MXD_RSFEC_LANE_MAPPING+hostRegOffset), 6, 2, &mapping[3])); /* NA if 50G */
            break;

        case MXD_P50MR:
        case MXD_P50JR:
        case MXD_P50BR:
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, (MXD_RSFEC_LANE_MAPPING+hostRegOffset), 0, 2, &mapping[0]));
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, (MXD_RSFEC_LANE_MAPPING+hostRegOffset), 2, 2, &mapping[1]));
            break;

        default:
            MXD_DBG_ERROR("mxdGetRsFecPMALaneMapping: invalid operation mode for FEC operation\n");
            return MXD_FAIL;
            break;
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetRsFecPCSLaneMapping
*******************************************************************************/
MXD_STATUS mxdGetRsFecPCSLaneMapping
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  interface_lane,
    OUT MXD_U16 *pcs_lane
)
{
    MXD_OP_CONFIG opConfig;
    MXD_U16 hostRegOffset = 0;

    if (host_or_line == MXD_HOST_SIDE)
    {
        opConfig = pDev->hostConfig[0].opConfig;
        hostRegOffset = MXD_HOST_REG_OFFSET;
    }
    else  if (host_or_line == MXD_LINE_SIDE)
    {
        opConfig = pDev->lineConfig[0].opConfig;
    }
    else
    {
        MXD_DBG_ERROR("mxdGetRsFecPCSLaneMapping: Incorrect line_or_host selection: \n");
        return MXD_FAIL;
    }

    if (interface_lane >= MXD_NUM_PCS_LANES)
    {
        MXD_DBG_ERROR("mxdGetRsFecPCSLaneMapping: interface_lane is invalid\n");
        return MXD_FAIL;
    }

    switch(opConfig)
    {
        case MXD_P100LR:
        case MXD_P100CR:
        case MXD_P100KR:
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, (MXD_RSFEC_PCS_LANE_MAPPING+hostRegOffset+interface_lane), 0, 5, pcs_lane));
            break;

        case MXD_P50MR:
        case MXD_P50JR:
        case MXD_P50BR:
            if (interface_lane < 4)
            {
                ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, (MXD_RSFEC_PCS_LANE_MAPPING+hostRegOffset+interface_lane), 0, 5, pcs_lane));
            }
            else
            {
                MXD_DBG_ERROR("mxdGetRsFecPCSLaneMapping: interface_lane invalid. 50G interface_lane from 0-3\n");
                return MXD_FAIL;
            }
            break;

        default:
            MXD_DBG_ERROR("mxdGetRsFecPCSLaneMapping: invalid operation mode for FEC operation\n");
            return MXD_FAIL;
            break;
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetRsFecCorrectedCwCntr
*******************************************************************************/
MXD_STATUS mxdGetRsFecCorrectedCwCntr
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U32 *codeWordCounter
)
{
    MXD_U16 temp1, temp2;
    MXD_OP_CONFIG opConfig;
    MXD_U16 hostRegOffset=0,rsRegOffset=0;

    ATTEMPT(mxdCheckFecLaneOffset(pDev, mdioPort, host_or_line, laneOffset, MXD_RS_FEC));

    if (host_or_line == MXD_HOST_SIDE)
    {
        opConfig = pDev->hostConfig[laneOffset].opConfig;
        hostRegOffset = MXD_HOST_REG_OFFSET;
    }
    else  if (host_or_line == MXD_LINE_SIDE)
    {
        opConfig = pDev->lineConfig[laneOffset].opConfig;
    }
    else
    {
        MXD_DBG_ERROR("mxdGetRsFecCorrectedCwCntr: Incorrect line_or_host selection: \n");
        return MXD_FAIL;
    }

    switch(opConfig)  
    {
        case MXD_P25CR:
        case MXD_P25KR:
        case MXD_P25BR:
        case MXD_P25JR:
        case MXD_P25LR:
        case MXD_P25BCR:
        case MXD_P25JKR:
        case MXD_P50MR:
        case MXD_P50JR:
        case MXD_P50BR:
        case MXD_P100LR:
        case MXD_P100CR:
        case MXD_P100KR:
            rsRegOffset = (MXD_RSFEC_CORR_CW_CNTR+hostRegOffset+(laneOffset*MXD_FEC_REG_OFFSET));
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_LINE_PMA, rsRegOffset, &temp1));
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_LINE_PMA, rsRegOffset+1, &temp2));
            *codeWordCounter = ((MXD_U32)temp1|((MXD_U32)temp2<<16));
            break;

        default:
            MXD_DBG_ERROR("mxdGetRsFecUnCorrectedCwCntr: invalid operation mode for FEC operation\n");
            return MXD_FAIL;
            break;
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetRsFecUnCorrectedCwCntr
*******************************************************************************/
MXD_STATUS mxdGetRsFecUnCorrectedCwCntr
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U32 *codeWordCounter
)
{
    MXD_U16 temp1, temp2;
    MXD_OP_CONFIG opConfig;
    MXD_U16 hostRegOffset=0, rsRegOffset=0;

    ATTEMPT(mxdCheckFecLaneOffset(pDev, mdioPort, host_or_line, laneOffset, MXD_RS_FEC));

    if (host_or_line == MXD_HOST_SIDE)
    {
        opConfig = pDev->hostConfig[laneOffset].opConfig;
        hostRegOffset = MXD_HOST_REG_OFFSET;
    }
    else  if (host_or_line == MXD_LINE_SIDE)
    {
        opConfig = pDev->lineConfig[laneOffset].opConfig;
    }
    else
    {
        MXD_DBG_ERROR("mxdGetRsFecUnCorrectedCwCntr: Incorrect line_or_host selection: \n");
        return MXD_FAIL;
    }

    switch(opConfig)       
    {
        case MXD_P25CR:
        case MXD_P25KR:
        case MXD_P25BR:
        case MXD_P25JR:
        case MXD_P25LR:
        case MXD_P25BCR:
        case MXD_P25JKR:
        case MXD_P50MR:
        case MXD_P50JR:
        case MXD_P50BR:
        case MXD_P100LR:
        case MXD_P100CR:
        case MXD_P100KR:
            rsRegOffset = (MXD_RSFEC_UNCORR_CW_CNTR+hostRegOffset+(laneOffset*MXD_FEC_REG_OFFSET));
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_LINE_PMA, rsRegOffset, &temp1));
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_LINE_PMA, rsRegOffset+1, &temp2));
            *codeWordCounter = ((MXD_U32)temp1|((MXD_U32)temp2<<16));
            break;

        default:
            MXD_DBG_ERROR("mxdGetRsFecUnCorrectedCwCntr: invalid operation mode for FEC operation\n");
            return MXD_FAIL;
            break;
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetRsFecSymbolErrorCntr
*******************************************************************************/
MXD_STATUS mxdGetRsFecSymbolErrorCntr
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U32 *errorCounter
)
{
    MXD_U16 temp1, temp2;
    MXD_OP_CONFIG opConfig;
    MXD_U16 hostRegOffset=0,rsRegOffset=0;

    ATTEMPT(mxdCheckFecLaneOffset(pDev, mdioPort, host_or_line, laneOffset, MXD_RS_FEC));

    if (host_or_line == MXD_HOST_SIDE)
    {
        opConfig = pDev->hostConfig[laneOffset].opConfig;
        hostRegOffset = MXD_HOST_REG_OFFSET;
    }
    else  if (host_or_line == MXD_LINE_SIDE)
    {
        opConfig = pDev->lineConfig[laneOffset].opConfig;
    }
    else
    {
        MXD_DBG_ERROR("mxdGetRsFecSymbolErrorCntr: Incorrect line_or_host selection: \n");
        return MXD_FAIL;
    }

    if (laneOffset >= MXD_NUM_LANES)
    {
        MXD_DBG_ERROR("mxdGetRsFecSymbolErrorCntr: lane is invalid\n");
        return MXD_FAIL;
    }

    switch(opConfig)             
    {
        case MXD_P25CR:
        case MXD_P25KR:
        case MXD_P25BR:
        case MXD_P25JR:
        case MXD_P25LR:
        case MXD_P25BCR:
        case MXD_P25JKR:
        case MXD_P50MR:
        case MXD_P50JR:
        case MXD_P50BR:
        case MXD_P100LR:
        case MXD_P100CR:
        case MXD_P100KR:
            rsRegOffset = (MXD_RSFEC_SYM_ERR_CNTR+hostRegOffset+(laneOffset*MXD_FEC_REG_OFFSET));
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_LINE_PMA, rsRegOffset, &temp1));
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_LINE_PMA, rsRegOffset+1, &temp2));
            *errorCounter = ((MXD_U32)temp1|((MXD_U32)temp2<<16));
            break;

        default:
            MXD_DBG_ERROR("mxdGetRsFecSymbolErrorCntr: invalid operation mode for FEC operation\n");
            return MXD_FAIL;
            break;
    }

    return MXD_OK;
}


/*******************************************************************************
 MXD_STATUS mxdGetRsFecBipErrorCntr
*******************************************************************************/
MXD_STATUS mxdGetRsFecBipErrorCntr
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  pcs_lane,
    OUT MXD_U16 *errorCounter
)
{
    MXD_OP_CONFIG opConfig;
    MXD_U16 hostRegOffset = 0;

    if (host_or_line == MXD_HOST_SIDE)
    {
        opConfig = pDev->hostConfig[0].opConfig;
        hostRegOffset = MXD_HOST_REG_OFFSET;
    }
    else  if (host_or_line == MXD_LINE_SIDE)
    {
        opConfig = pDev->lineConfig[0].opConfig;
    }
    else
    {
        MXD_DBG_ERROR("mxdGetRsFecBipErrorCntr: Incorrect line_or_host selection: \n");
        return MXD_FAIL;
    }

    if (pcs_lane >= MXD_NUM_PCS_LANES)
    {
        MXD_DBG_ERROR("mxdGetRsFecBipErrorCntr: pcs_lane is invalid\n");
        return MXD_FAIL;
    }

    switch(opConfig)
    {
        case MXD_P100LR:
        case MXD_P100CR:
        case MXD_P100KR:
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_LINE_PMA, (MXD_RSFEC_BIP_ERR_CNTR+hostRegOffset+pcs_lane), errorCounter));
            break;

        case MXD_P50MR:
        case MXD_P50JR:
        case MXD_P50BR:
            if (pcs_lane < 4)
            {
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_LINE_PMA, (MXD_RSFEC_BIP_ERR_CNTR+hostRegOffset+pcs_lane), errorCounter));
            }
            else
            {
                MXD_DBG_ERROR("mxdGetRsFecBipErrorCntr: pcs_lane invalid. 50G pcs_lane from 0-3\n");
                return MXD_FAIL;
            }
            break;

        default:
            MXD_DBG_ERROR("mxdGetRsFecBipErrorCntr: invalid operation mode for FEC operation\n");
            return MXD_FAIL;
            break;
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdSetKrFecControl
*******************************************************************************/
MXD_STATUS mxdSetKrFecControl
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_U16 bypassIndicationEnable
)
{
    MXD_OP_CONFIG opConfig;
    MXD_U16 hostRegOffset = 0, krRegOffset=0;

    ATTEMPT(mxdCheckFecLaneOffset(pDev, mdioPort, host_or_line, laneOffset, MXD_KR_FEC));

    if (host_or_line == MXD_HOST_SIDE)
    {
        opConfig = pDev->hostConfig[laneOffset].opConfig;
        hostRegOffset = MXD_HOST_REG_OFFSET;
    }
    else  if (host_or_line == MXD_LINE_SIDE)
    {
        opConfig = pDev->lineConfig[laneOffset].opConfig;
    }
    else
    {
        MXD_DBG_ERROR("mxdSetKrFecControl: Incorrect line_or_host selection: \n");
        return MXD_FAIL;
    }

    switch(opConfig)            
    {
        case MXD_P10KF:
        case MXD_P10LF:
        case MXD_P25LF:
        case MXD_P25CF:
        case MXD_P25KF:
        case MXD_P25BF:
        case MXD_P25JF:
        case MXD_P25BCF:
        case MXD_P25JKF:
            krRegOffset = (MXD_KRFEC_CNTL+hostRegOffset+(laneOffset*MXD_FEC_REG_OFFSET));

            if (bypassIndicationEnable == MXD_ENABLE)
            {
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, krRegOffset, 1, 1, MXD_ENABLE));
            }
            else if(bypassIndicationEnable == MXD_DISABLE)
            {
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, krRegOffset, 1, 1, MXD_DISABLE));
            }
            else
            {
                MXD_DBG_ERROR("mxdSetKrFecControl: bypassIndicationEnable is invalid\n");
                return MXD_FAIL;
            }
            break;

        case MXD_P40CF:
        case MXD_P40KF:
        case MXD_P40LF:
        case MXD_P50CF:
        case MXD_P50KF:
        case MXD_P50LF:
        case MXD_P50MF:
        case MXD_P50BF:
        case MXD_P50JF:
            krRegOffset = (MXD_KRFEC_CNTL+hostRegOffset);

            if (bypassIndicationEnable == MXD_ENABLE)
            {
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, krRegOffset, 1, 1, MXD_ENABLE));
            }
            else if(bypassIndicationEnable == MXD_DISABLE)
            {
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, krRegOffset, 1, 1, MXD_DISABLE));
            }
            else
            {
                MXD_DBG_ERROR("mxdSetKrFecControl: bypassIndicationEnable is invalid\n");
                return MXD_FAIL;
            }
            break;

        default:
            MXD_DBG_ERROR("mxdSetKrFecControl: invalid operation mode for FEC operation\n");
            return MXD_FAIL;
            break;
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetKrFecAbility
*******************************************************************************/
MXD_STATUS mxdGetKrFecAbility
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U16 *krFecAbility,
    OUT MXD_U16 *errIndicationAbility
)
{
    MXD_OP_CONFIG opConfig;
    MXD_U16 hostRegOffset = 0, krRegOffset=0;

    ATTEMPT(mxdCheckFecLaneOffset(pDev, mdioPort, host_or_line, laneOffset, MXD_KR_FEC));

    if (host_or_line == MXD_HOST_SIDE)
    {
        opConfig = pDev->hostConfig[laneOffset].opConfig;
        hostRegOffset = MXD_HOST_REG_OFFSET;
    }
    else  if (host_or_line == MXD_LINE_SIDE)
    {
        opConfig = pDev->lineConfig[laneOffset].opConfig;
    }
    else
    {
        MXD_DBG_ERROR("mxdGetKrFecAbility: Incorrect line_or_host selection: \n");
        return MXD_FAIL;
    }

    switch(opConfig)         
    {
        case MXD_P10KF:
        case MXD_P10LF:
        case MXD_P25LF:
        case MXD_P25CF:
        case MXD_P25KF:
        case MXD_P25BF:
        case MXD_P25JF:
        case MXD_P25BCF:
        case MXD_P25JKF:
            krRegOffset = (MXD_KRFEC_ABILITY+hostRegOffset+(laneOffset*MXD_FEC_REG_OFFSET));
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, krRegOffset, 0, 1, krFecAbility));
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, krRegOffset, 1, 1, errIndicationAbility));
            break;

        case MXD_P40CF:
        case MXD_P40KF:
        case MXD_P40LF:
        case MXD_P50CF:
        case MXD_P50KF:
        case MXD_P50LF:
        case MXD_P50MF:
        case MXD_P50BF:
        case MXD_P50JF:
            krRegOffset = (MXD_KRFEC_ABILITY+hostRegOffset);
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, krRegOffset, 0, 1, krFecAbility));
            ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, krRegOffset, 1, 1, errIndicationAbility));
            break;

        default:
            MXD_DBG_ERROR("mxdGetKrFecAbility: invalid operation mode for FEC operation\n");
            return MXD_FAIL;
            break;
    }

    return MXD_OK;
}


/*******************************************************************************
 MXD_STATUS mxdGetKrFecCorrectedBlkCntr
*******************************************************************************/
MXD_STATUS mxdGetKrFecCorrectedBlkCntr
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U32 *blockCounter
)
{
    MXD_U16 temp1, temp2;
    MXD_OP_CONFIG opConfig;
    MXD_U16 hostRegOffset=0, krRegOffset=0;

    ATTEMPT(mxdCheckFecLaneOffset(pDev, mdioPort, host_or_line, laneOffset, MXD_KR_FEC));

    if (host_or_line == MXD_HOST_SIDE)
    {
        opConfig = pDev->hostConfig[laneOffset].opConfig;
        hostRegOffset = MXD_HOST_REG_OFFSET;
    }
    else  if (host_or_line == MXD_LINE_SIDE)
    {
        opConfig = pDev->lineConfig[laneOffset].opConfig;
    }
    else
    {
        MXD_DBG_ERROR("mxdGetKrFecCorrectedBlkCntr: Incorrect line_or_host selection: \n");
        return MXD_FAIL;
    }

    switch(opConfig)      
    {
        case MXD_P10KF:
        case MXD_P10LF:
            krRegOffset = (MXD_10GKRFEC_CORR_BLK_CNTR+hostRegOffset+(laneOffset*MXD_FEC_REG_OFFSET));
            break;

        case MXD_P25LF:
        case MXD_P25CF:
        case MXD_P25KF:
        case MXD_P25BF:
        case MXD_P25JF:
        case MXD_P25BCF:
        case MXD_P25JKF:
            krRegOffset = (MXD_KRFEC_CORR_BLK_CNTR+hostRegOffset+(laneOffset*0x2));
            break;

        case MXD_P40CF:
        case MXD_P40KF:
        case MXD_P40LF:
        case MXD_P50CF:
        case MXD_P50KF:
        case MXD_P50LF:
        case MXD_P50MF:
        case MXD_P50BF:
        case MXD_P50JF:
            krRegOffset = (MXD_KRFEC_CORR_BLK_CNTR+hostRegOffset);
            break;

        default:
            MXD_DBG_ERROR("mxdGetKrFecCorrectedBlkCntr: invalid operation mode for FEC operation\n");
            *blockCounter = 0;
            return MXD_FAIL;
            break;
    }

    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_LINE_PMA, krRegOffset, &temp1));
    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_LINE_PMA, krRegOffset+1, &temp2));
    *blockCounter = ((MXD_U32)temp1|((MXD_U32)temp2<<16));

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetKrFecUnCorrectedBlkCntr
*******************************************************************************/
MXD_STATUS mxdGetKrFecUnCorrectedBlkCntr
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U32 *blockCounter
)
{
    MXD_U16 temp1, temp2;
    MXD_OP_CONFIG opConfig;
    MXD_U16 hostRegOffset=0,krRegOffset=0;

    ATTEMPT(mxdCheckFecLaneOffset(pDev, mdioPort, host_or_line, laneOffset, MXD_KR_FEC));

    if (host_or_line == MXD_HOST_SIDE)
    {
        opConfig = pDev->hostConfig[laneOffset].opConfig;
        hostRegOffset = MXD_HOST_REG_OFFSET;
    }
    else  if (host_or_line == MXD_LINE_SIDE)
    {
        opConfig = pDev->lineConfig[laneOffset].opConfig;
    }
    else
    {
        MXD_DBG_ERROR("mxdGetKrFecUnCorrectedBlkCntr: Incorrect line_or_host selection: \n");
        return MXD_FAIL;
    }

    switch(opConfig)                
    {
        case MXD_P10KF:
        case MXD_P10LF:
            krRegOffset = (MXD_10GKRFEC_UNCORR_BLK_CNTR+hostRegOffset+(laneOffset*MXD_FEC_REG_OFFSET));
            break;

        case MXD_P25LF:
        case MXD_P25CF:
        case MXD_P25KF:
        case MXD_P25BF:
        case MXD_P25JF:
        case MXD_P25BCF:
        case MXD_P25JKF:
            krRegOffset = (MXD_KRFEC_UNCORR_BLK_CNTR+hostRegOffset+(laneOffset*0x2));
            break;

        case MXD_P40CF:
        case MXD_P40KF:
        case MXD_P40LF:
        case MXD_P50CF:
        case MXD_P50KF:
        case MXD_P50LF:
        case MXD_P50MF:
        case MXD_P50BF:
        case MXD_P50JF:
            krRegOffset = (MXD_KRFEC_UNCORR_BLK_CNTR+hostRegOffset);
            break;

        default:
            MXD_DBG_ERROR("mxdGetKrFecUnCorrectedBlkCntr: invalid operation mode for FEC operation\n");
            *blockCounter = 0;
            return MXD_FAIL;
            break;
    }

    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_LINE_PMA, krRegOffset, &temp1));
    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_LINE_PMA, krRegOffset+1, &temp2));
    *blockCounter = ((MXD_U32)temp1|((MXD_U32)temp2<<16));

    return MXD_OK;
}
