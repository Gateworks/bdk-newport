/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/


/************************************************************************
This file contains functions to configure RS-FEC/KR-FEC
and read RS-FEC/KR-FEC status for the Marvell X7120/X6181/X6141 Device.
************************************************************************/
#include "mydApiRegs.h"
#include "mydApiTypes.h"
#include "mydAPI.h"
#include "mydIntrIOConfig.h"
#include "mydAPIInternal.h"
#include "mydHwCntl.h"
#include "mydFEC.h"
#include "mydUtils.h"

/*******************************************************************************
 These functions are general RS-FEC functions. Some are applicable to all
 RS-FEC and some are not applicable to certain PCSs. Read each function
 header to find which are applicable/not applicable. Note: two 40G modes
 use the 50G PCS. Those are P40BR and P40JR. For those modes, the comments
 related to 50G apply to those 40G modes as well.
*******************************************************************************/

/*******************************************************************************
 MYD_STATUS mydSetRsFecControl
    Configure the RS-FEC for those parameters that are configurable
*******************************************************************************/
MYD_STATUS mydSetRsFecControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 bypassIndicationEnable,
    IN MYD_U16 bypassCorrectionEnable
)
{
    MYD_OP_MODE opMode;
    MYD_U16 controlRegisterAddr, lineSpeed;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode)); 
    
    if (mydIsLaneOffsetValid(pDev, mdioPort, host_or_line, laneOffset) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydSetRsFecControl: Invalid lane used:%u \n", laneOffset);
        return MYD_FAIL;
    }

    lineSpeed = opModeTable[opMode][MYD_OP_TABLE_SPEED];

    if (lineSpeed == MYD_200GB)
    {
        MYD_DBG_ERROR("mydSetRsFecControl: Not applicable to 200G modes\n");
        return MYD_FAIL;
    }

    controlRegisterAddr = MYD_RSFEC_CNTL(host_or_line, laneOffset);

    if (bypassCorrectionEnable == MYD_ENABLE && bypassIndicationEnable == MYD_ENABLE)
    {
        MYD_DBG_ERROR("mydSetRsFecControl: Bypass both is an error.\n");
    }

    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, controlRegisterAddr, 0, 1, bypassCorrectionEnable));
    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, controlRegisterAddr, 1, 1, bypassIndicationEnable));    

    return MYD_OK;
    
}

/*******************************************************************************
 MYD_STATUS mydGetRsFecControl
    Read the values of the current settings for the RS-FEC
*******************************************************************************/
MYD_STATUS mydGetRsFecControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *bypassIndicationEnable,
    OUT MYD_U16 *bypassCorrectionEnable
)
{
    MYD_OP_MODE opMode;
    MYD_U16 controlRegisterAddr, lineSpeed;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode)); 
    
    if (mydIsLaneOffsetValid(pDev, mdioPort, host_or_line, laneOffset) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydGetRsFecControl: Invalid lane used:%u \n", laneOffset);
        return MYD_FAIL;
    }

    lineSpeed = opModeTable[opMode][MYD_OP_TABLE_SPEED];

    controlRegisterAddr = MYD_RSFEC_CNTL(host_or_line, laneOffset);

    if (lineSpeed == MYD_200GB)
    {
        MYD_DBG_ERROR("mydGetRsFecControl: Not applicable to 200G modes\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, controlRegisterAddr, 0, 1, bypassCorrectionEnable));
    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, controlRegisterAddr, 1, 1, bypassIndicationEnable));    

    return MYD_OK;
}


/*******************************************************************************
 MYD_STATUS mydGetRsFecStatus
    Get the high-level status of the RS-FEC
*******************************************************************************/
MYD_STATUS mydGetRsFecStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    OUT MYD_U16 *pcsLaneAlignment,
    OUT MYD_U16 *fecLaneAlignment,
    OUT MYD_U16 *rsFecLaneAMLock,
    OUT MYD_U16 *latchedRsFecHighErr,
    OUT MYD_U16 *currRsFecHighErr
)
{
    MYD_OP_MODE opMode;
    MYD_U16 statusRegisterAddr, lineSpeed;

    *pcsLaneAlignment = *fecLaneAlignment = *rsFecLaneAMLock = *latchedRsFecHighErr
                      = *currRsFecHighErr = 0; /* will return 0 for all if error */

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode)); 
    
    if (mydIsLaneOffsetValid(pDev, mdioPort, host_or_line, laneOffset) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydGetRsFecStatus: Invalid lane used:%u \n", laneOffset);
        return MYD_FAIL;
    }
    
    lineSpeed = opModeTable[opMode][MYD_OP_TABLE_SPEED];

    /* 200G mode FEC status is in a different place in register map */
    if (lineSpeed == MYD_200GB)
    {        
        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_RX_LINK_STATUS, 12, 1, pcsLaneAlignment));

        *fecLaneAlignment = *pcsLaneAlignment; /* this bit is not applicable in this mode, FEC and PCS are integrated in 200G/400G  */

        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_LANE_ALIGN, 0, MYD_NUM_200G_FEC_LANES, rsFecLaneAMLock));
        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_DEG_SER, 2, 1, latchedRsFecHighErr));
        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_DEG_SER, 2, 1, currRsFecHighErr));
    }
    else
    {

        statusRegisterAddr = MYD_RSFEC_STAT(host_or_line, laneOffset);

        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, statusRegisterAddr, 15, 1, pcsLaneAlignment));
        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, statusRegisterAddr, 14, 1, fecLaneAlignment));

        switch (lineSpeed)
        {
            case MYD_25GB:
                /* always returns 0, this is not applicable */
                break;

            case MYD_40GB: 
                if (!(opModeTable[opMode][MYD_OP_TABLE_FEC] == MYD_FEC_RS_528))
                {
                    MYD_DBG_ERROR("mydGetRsFecStatus: Invalid 40G mode selected.\n");
                    return MYD_FAIL;
                }
                /* falls through on purpose, these 40G modes use 50G PCS */
            case MYD_50GB:
                ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, statusRegisterAddr, 8, MYD_NUM_50G_FEC_LANES, rsFecLaneAMLock));
                break;

            case MYD_100GB:
                ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, statusRegisterAddr, 8, MYD_NUM_100G_FEC_LANES, rsFecLaneAMLock));                
                break;

            default:
                /* any other speed is an error */
                MYD_DBG_ERROR("mydGetRsFecStatus: Invalid line speed used. Only 25G/50G/100G is valid. \n");     
                return MYD_FAIL;
                break;            
        }

        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, statusRegisterAddr, 2, 1, latchedRsFecHighErr));
        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, statusRegisterAddr, 2, 1, currRsFecHighErr));
        
    }

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydGetRsFecPCSAlignmentStatus
    Read the locked/lane alignment status of a given RS-FEC PCS lane
*******************************************************************************/
MYD_STATUS mydGetRsFecPCSAlignmentStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,    
    IN MYD_U16  pcs_lane,
    OUT MYD_U16 *blockLocked,
    OUT MYD_U16 *laneAligned
)
{
    MYD_OP_MODE opMode;    
    MYD_U8 laneMap = (MYD_U8)((pcs_lane<8) ? pcs_lane:(pcs_lane-8)); /*bit position of lane status */
    MYD_U16 status1RegisterAddr, status2RegisterAddr, status3RegisterAddr, status4RegisterAddr, lineSpeed;

    *blockLocked = *laneAligned = 0; /* will return 0 for all if error */

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode)); 
    
    if (mydIsLaneOffsetValid(pDev, mdioPort, host_or_line, laneOffset) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydGetRsFecPCSAlignmentStatus: Invalid lane used:%u \n", laneOffset);
        return MYD_FAIL;
    }
    
    lineSpeed = opModeTable[opMode][MYD_OP_TABLE_SPEED];

    if (lineSpeed == MYD_200GB || lineSpeed == MYD_25GB)
    {
        MYD_DBG_ERROR("mydGetRsFecPCSAlignmentStatus: Not applicable to 200G/25G modes\n");
        return MYD_FAIL;
    }
    
    status1RegisterAddr = MYD_RSFEC_PCS_ALIGN_STAT1(host_or_line, laneOffset);
    status2RegisterAddr = MYD_RSFEC_PCS_ALIGN_STAT2(host_or_line, laneOffset);
    status3RegisterAddr = MYD_RSFEC_PCS_ALIGN_STAT3(host_or_line, laneOffset);
    status4RegisterAddr = MYD_RSFEC_PCS_ALIGN_STAT4(host_or_line, laneOffset);

    if (lineSpeed == MYD_100GB)
    {
        if (pcs_lane < 8)
        {
            ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, status1RegisterAddr, laneMap, 1, blockLocked));
            ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, status3RegisterAddr, laneMap, 1, laneAligned));
        }
        else if (pcs_lane < MYD_NUM_100G_PCS_LANES)
        {
            ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, status2RegisterAddr, laneMap, 1, blockLocked));
            ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, status4RegisterAddr, laneMap, 1, laneAligned));
        }
        else
        {
            MYD_DBG_ERROR("mydGetRsFecPCSAlignmentStatus: pcs_lane is invalid (range 0-19):%u \n", pcs_lane);
            return MYD_FAIL;
        }
    }
    else
    {
        if (pcs_lane < MYD_NUM_50G_PCS_LANES)
        {
            ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, status1RegisterAddr, laneMap, 1, blockLocked));
            ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, status3RegisterAddr, laneMap, 1, laneAligned));
        }
        else
        {
            MYD_DBG_ERROR("mydGetRsFecPCSAlignmentStatus: pcs_lane invalid (range 0-3):%u \n", pcs_lane);
            return MYD_FAIL;
        }
    }

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydGetRsFecPMALaneMapping
    Read the RS-FEC to PMA lane mapping
*******************************************************************************/
MYD_STATUS mydGetRsFecPMALaneMapping
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,        
    OUT MYD_U16 mapping[MYD_NUM_LANES]
)
{
    MYD_OP_MODE opMode;    
    MYD_U16 laneMappingRegisterAddr, idx, temp, lineSpeed;

    for (idx=0; idx < MYD_NUM_LANES; idx++)
    {
        mapping[idx] = 0;
    }

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode)); 
    
    if (mydIsLaneOffsetValid(pDev, mdioPort, host_or_line, laneOffset) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydGetRsFecPMALaneMapping: Invalid lane used:%u \n", laneOffset);
        return MYD_FAIL;
    }

    lineSpeed = opModeTable[opMode][MYD_OP_TABLE_SPEED];

    if (lineSpeed == MYD_200GB || lineSpeed == MYD_25GB)
    {
        MYD_DBG_ERROR("mydGetRsFecPMALaneMapping: Not applicable to 200G/25G modes\n");
        return MYD_FAIL;
    }

    laneMappingRegisterAddr = MYD_RSFEC_LANE_MAP(host_or_line, laneOffset);

    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, laneMappingRegisterAddr, &temp));

    for (idx=0; idx < MYD_NUM_LANES; idx++)
    {
        mapping[idx] = temp & 3;
        temp >>= 2;
    }

    return MYD_OK;    
}

/*******************************************************************************
 MYD_STATUS mydGetRxPCSLaneMapping
    Read the PCS lane to interface lane mapping
*******************************************************************************/
MYD_STATUS mydGetRxPCSLaneMapping
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 interface_lane,
    OUT MYD_U16 *pcs_lane
)
{
    MYD_OP_MODE opMode;    
    MYD_U16 pcsLaneMappingRegisterAddr, lineSpeed;

    *pcs_lane = 0;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode)); 
    
    if (mydIsLaneOffsetValid(pDev, mdioPort, host_or_line, laneOffset) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydGetRxPCSLaneMapping: Invalid lane used:%u \n", laneOffset);
        return MYD_FAIL;
    }

    lineSpeed = opModeTable[opMode][MYD_OP_TABLE_SPEED];

    if (lineSpeed == MYD_25GB)
    {
        MYD_DBG_ERROR("mydGetRxPCSLaneMapping: Not applicable to 25G mode \n");
        return MYD_FAIL;        
    }

    if (lineSpeed == MYD_200GB)
    {
        if (interface_lane >= MYD_NUM_200G_FEC_LANES)
        {
            MYD_DBG_ERROR("mydGetRxPCSLaneMapping: Invalid 200G interface lane used:%u \n", interface_lane);
            return MYD_FAIL;
        }    

        pcsLaneMappingRegisterAddr = MYD_200GR4_FEC_LANE_MAP(interface_lane);
        
        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, pcsLaneMappingRegisterAddr, pcs_lane));
        
        return MYD_OK;        
    }
    else if (lineSpeed == MYD_100GB)
    {
        if (interface_lane >= MYD_NUM_100G_PCS_LANES)
        {
            MYD_DBG_ERROR("mydGetRxPCSLaneMapping: Invalid 100G interface lane used:%u \n", interface_lane);
            return MYD_FAIL;
        }
    }
    else if (lineSpeed == MYD_50GB || lineSpeed == MYD_40GB)
    {
        if (interface_lane >= MYD_NUM_50G_PCS_LANES)
        {
            MYD_DBG_ERROR("mydGetRxPCSLaneMapping: Invalid 40G/50G interface lane used:%u \n", interface_lane);
            return MYD_FAIL;
        }        
    }
    else
    {
        MYD_DBG_ERROR("mydGetRxPCSLaneMapping: line speed \n");
        return MYD_FAIL;
    }

    if (lineSpeed == MYD_100GB)
    {
        pcsLaneMappingRegisterAddr = MYD_100G_PCS_LN_MAP(laneOffset, interface_lane);
    }
    else
    {
        /* handles both 50G and 40G cases */
        pcsLaneMappingRegisterAddr = MYD_40G50G_PCS_LN_MAP(laneOffset, interface_lane);
    }

    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, pcsLaneMappingRegisterAddr, pcs_lane));

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydGetRsFecCorrectedCwCntr
    Read the RS-FEC Corrected Code Word Counter
*******************************************************************************/
MYD_STATUS mydGetRsFecCorrectedCwCntr
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    OUT MYD_U32 *codeWordCounter
)
{
    MYD_OP_MODE opMode;    
    MYD_U16 correctedCwCounterLowerAddr, correctedCodeWordLower, correctedCodeWordUpper, lineSpeed;

    *codeWordCounter = 0;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode)); 
    
    if (mydIsLaneOffsetValid(pDev, mdioPort, host_or_line, laneOffset) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydGetRsFecCorrectedCwCntr: Invalid lane used:%u \n", laneOffset);
        return MYD_FAIL;
    }

    lineSpeed = opModeTable[opMode][MYD_OP_TABLE_SPEED];

    if (lineSpeed == MYD_200GB)
    {
        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_CORR_CW_LOW, &correctedCodeWordLower));
        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_CORR_CW_LOW+1, &correctedCodeWordUpper));
    }
    else
    {    
        correctedCwCounterLowerAddr = MYD_RSFEC_CORR_CW_LOW(host_or_line, laneOffset);
        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, correctedCwCounterLowerAddr, &correctedCodeWordLower));
        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, correctedCwCounterLowerAddr+1, &correctedCodeWordUpper));
    }

    *codeWordCounter = correctedCodeWordLower;
    *codeWordCounter |= (((MYD_U32)(correctedCodeWordUpper))<<16);

    return MYD_OK;    
}

/*******************************************************************************
 MYD_STATUS mydGetRsFecUnCorrectedCwCntr
    Read the RS-FEC Uncorrected Code Word Counter
*******************************************************************************/
MYD_STATUS mydGetRsFecUnCorrectedCwCntr
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    OUT MYD_U32 *codeWordCounter
)
{
    MYD_OP_MODE opMode;    
    MYD_U16 uncorrectedCwCounterLowerAddr, uncorrectedCodeWordLower, uncorrectedCodeWordUpper, lineSpeed;

    *codeWordCounter = 0;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode)); 
    
    if (mydIsLaneOffsetValid(pDev, mdioPort, host_or_line, laneOffset) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydGetRsFecUnCorrectedCwCntr: Invalid lane used:%u \n", laneOffset);
        return MYD_FAIL;
    }

    lineSpeed = opModeTable[opMode][MYD_OP_TABLE_SPEED];

    if (lineSpeed == MYD_200GB)
    {
        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_UNCORR_CW_LOW, &uncorrectedCodeWordLower));
        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_UNCORR_CW_LOW+1, &uncorrectedCodeWordUpper));
    }
    else
    {    
        uncorrectedCwCounterLowerAddr = MYD_RSFEC_UNCORR_CW_LOW(host_or_line, laneOffset);
        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, uncorrectedCwCounterLowerAddr, &uncorrectedCodeWordLower));
        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, uncorrectedCwCounterLowerAddr+1, &uncorrectedCodeWordUpper));
    }
    
    *codeWordCounter = uncorrectedCodeWordLower;
    *codeWordCounter |= (((MYD_U32)(uncorrectedCodeWordUpper))<<16);

    return MYD_OK;    
}

/*******************************************************************************
 MYD_STATUS mydGetRsFecSymbolErrorCntr
    Read the RS-FEC Symbol Error Counter
*******************************************************************************/
MYD_STATUS mydGetRsFecSymbolErrorCntr
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    IN MYD_U16  fecLane,
    OUT MYD_U32 *errorCounter
)
{
    MYD_OP_MODE opMode;    
    MYD_U16 symbolErrorCtrLowerAddr, symbolErrorCtrLower, symbolErrorCtrUpper, lineSpeed;

    *errorCounter = 0;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode)); 
    
    if (mydIsLaneOffsetValid(pDev, mdioPort, host_or_line, laneOffset) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydGetRsFecSymbolErrorCntr: Invalid lane used:%u \n", laneOffset);
        return MYD_FAIL;
    }

    lineSpeed = opModeTable[opMode][MYD_OP_TABLE_SPEED];

    if (lineSpeed == MYD_200GB)
    {
        if (fecLane < MYD_NUM_200G_FEC_LANES)
        {
            symbolErrorCtrLowerAddr = MYD_200GR4_FEC_SYM_ERR_CTR_LOW(fecLane);
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, symbolErrorCtrLowerAddr, &symbolErrorCtrLower));
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, symbolErrorCtrLowerAddr+1, &symbolErrorCtrUpper));            
        }
        else
        {
            MYD_DBG_ERROR("mydGetRsFecSymbolErrorCntr: Invalid fec lane used:%u \n", fecLane);
            return MYD_FAIL;
        }
    }
    else
    {
        if (lineSpeed == MYD_100GB)
        {
            if (fecLane > MYD_NUM_100G_FEC_LANES)
            {
                MYD_DBG_ERROR("mydGetRsFecSymbolErrorCntr: Invalid fec lane used:%u \n", fecLane);
                return MYD_FAIL;
            }
        }
        else if (lineSpeed == MYD_50GB || lineSpeed == MYD_40GB)
        {
            if (fecLane > MYD_NUM_50G_FEC_LANES)
            {
                MYD_DBG_ERROR("mydGetRsFecSymbolErrorCntr: Invalid fec lane used:%u \n", fecLane);
                return MYD_FAIL;
            }
        }
        else
        {
            if (fecLane != 0) /* 25G case */
            {
                MYD_DBG_ERROR("mydGetRsFecSymbolErrorCntr: Invalid fec lane used:%u \n", fecLane);
                return MYD_FAIL;                
            }
        }
        
        symbolErrorCtrLowerAddr = MYD_RSFEC_SYM_ERR_CTR_LOW(host_or_line, laneOffset, fecLane);
        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, symbolErrorCtrLowerAddr, &symbolErrorCtrLower));
        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, symbolErrorCtrLowerAddr+1, &symbolErrorCtrUpper));
    }

    *errorCounter = symbolErrorCtrLower;
    *errorCounter |= (((MYD_U32)(symbolErrorCtrUpper))<<16);
    
    return MYD_OK;        
}

/*******************************************************************************
 MYD_STATUS mydGetRxPcsBipErrorCntr
    Read the RS-FEC BIP error counter corresponding to a given PCS lane
*******************************************************************************/
MYD_STATUS mydGetRxPcsBipErrorCntr
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    IN MYD_U16  pcs_lane,
    OUT MYD_U16 *errorCounter
)
{
    MYD_OP_MODE opMode;    
    MYD_U16 bipErrorCtrAddr, lineSpeed;

    *errorCounter= 0;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode)); 
    
    if (mydIsLaneOffsetValid(pDev, mdioPort, host_or_line, laneOffset) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydGetRxPcsBipErrorCntr: Invalid lane used:%u \n", laneOffset);
        return MYD_FAIL;
    }

    lineSpeed = opModeTable[opMode][MYD_OP_TABLE_SPEED];

    if (lineSpeed == MYD_200GB || lineSpeed == MYD_25GB)
    {
        MYD_DBG_ERROR("mydGetRxPcsBipErrorCntr: Not applicable to 200G/25G modes\n");
        return MYD_FAIL;
    }

    if (lineSpeed == MYD_100GB)
    {
        if (pcs_lane >= MYD_NUM_100G_PCS_LANES)
        {
            MYD_DBG_ERROR("mydGetRxPcsBipErrorCntr: Invalid 100G interface lane used:%u \n", pcs_lane);
            return MYD_FAIL;
        }
    }
    else if (lineSpeed == MYD_50GB || lineSpeed == MYD_40GB)
    {
        if (pcs_lane >= MYD_NUM_50G_PCS_LANES)
        {
            MYD_DBG_ERROR("mydGetRxPcsBipErrorCntr: Invalid 40G/50G interface lane used:%u \n", pcs_lane);
            return MYD_FAIL;
        }        
    }
    else
    {
        MYD_DBG_ERROR("mydGetRxPcsBipErrorCntr: Invalid line speed\n");
        return MYD_FAIL;
    }

    if (lineSpeed == MYD_100GB)
    {
        bipErrorCtrAddr = MYD_100G_BIP_ERR_CTR(laneOffset, pcs_lane);
    }
    else
    {
        bipErrorCtrAddr = MYD_40G50G_BIP_ERR_CTR(laneOffset, pcs_lane);
    }
    
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, bipErrorCtrAddr, errorCounter));

    return MYD_OK;    
}

/*******************************************************************************
 These functions are specific to the 200G RS-FEC
*******************************************************************************/

/*******************************************************************************
 MYD_STATUS mydSetRsFecSERControl
    To control signaling of errors and degraded SER
*******************************************************************************/
MYD_STATUS mydSetRsFecSERControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,    
    IN MYD_U16 laneOffset,
    IN MYD_U16 degradedSEREnable,
    IN MYD_U16 bypassIndicationEnable
)
{
    MYD_OP_MODE opMode;    
    MYD_U16 lineSpeed, tmpIn, tmpOut;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode)); 
    
    if (mydIsLaneOffsetValid(pDev, mdioPort, host_or_line, laneOffset) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydSetRsFecSERControl: Invalid lane used:%u \n", laneOffset);
        return MYD_FAIL;
    }

    lineSpeed = opModeTable[opMode][MYD_OP_TABLE_SPEED];

    if (lineSpeed != MYD_200GB)
    {
        MYD_DBG_ERROR("mydSetRsFecSERControl: Only supported on 200G RS-FEC\n");
        return MYD_FAIL;        
    }

    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_DEG_SER_CTL, &tmpIn));

    ATTEMPT(mydHwSetRegFieldToWord(tmpIn, degradedSEREnable, 2, 1, &tmpOut));
    tmpIn = tmpOut;
    ATTEMPT(mydHwSetRegFieldToWord(tmpIn, bypassIndicationEnable, 1, 1, &tmpOut));

    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_DEG_SER_CTL, tmpOut));
        
    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydGetRsFecSERControl
    To read setting of signaling of errors and degraded SER bits
*******************************************************************************/
MYD_STATUS mydGetRsFecSERControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,    
    IN MYD_U16 laneOffset,
    IN MYD_U16 *degradedSEREnable,
    IN MYD_U16 *bypassIndicationEnable
)
{
    MYD_OP_MODE opMode;    
    MYD_U16 lineSpeed, tmpIn;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode)); 
    
    if (mydIsLaneOffsetValid(pDev, mdioPort, host_or_line, laneOffset) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydGetRsFecSERControl: Invalid lane used:%u \n", laneOffset);
        return MYD_FAIL;
    }

    lineSpeed = opModeTable[opMode][MYD_OP_TABLE_SPEED];

    if (lineSpeed != MYD_200GB)
    {
        MYD_DBG_ERROR("mydGetRsFecSERControl: Only supported on 200G RS-FEC\n");
        return MYD_FAIL;        
    }

    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_DEG_SER_CTL, &tmpIn));

    ATTEMPT(mydHwGetRegFieldFromWord(tmpIn, 2, 1, degradedSEREnable));
    ATTEMPT(mydHwGetRegFieldFromWord(tmpIn, 1, 1, bypassIndicationEnable));
        
    return MYD_OK;
}


/*******************************************************************************
 MYD_STATUS mydSetRsFecSERThresholds
    To set the activate and deactivate thresholds and interval for degraded SER
*******************************************************************************/
MYD_STATUS mydSetRsFecSERThresholds
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,    
    IN MYD_U16 laneOffset,
    IN MYD_U32 serActivateThreshold,
    IN MYD_U32 serDeactivateThreshold,
    IN MYD_U32 serInterval
)
{
    MYD_OP_MODE opMode;    
    MYD_U16 lineSpeed;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode)); 
    
    if (mydIsLaneOffsetValid(pDev, mdioPort, host_or_line, laneOffset) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydSetRsFecSERControl: Invalid lane used:%u \n", laneOffset);
        return MYD_FAIL;
    }

    lineSpeed = opModeTable[opMode][MYD_OP_TABLE_SPEED];

    if (lineSpeed != MYD_200GB)
    {
        MYD_DBG_ERROR("mydSetRsFecSERThresholds: Only supported on 200G RS-FEC\n");
        return MYD_FAIL;        
    }

    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_DEGSER_ACT_LOW, ((MYD_U16)serActivateThreshold)));    
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_DEGSER_ACT_LOW+1, ((MYD_U16)(serActivateThreshold>>16))));

    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_DEGSER_DEACT_LOW, ((MYD_U16)serDeactivateThreshold)));    
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_DEGSER_DEACT_LOW+1, ((MYD_U16)(serDeactivateThreshold>>16))));

    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_DEGSER_INT_LOW, ((MYD_U16)serInterval)));    
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_DEGSER_INT_LOW+1, ((MYD_U16)(serInterval>>16))));


    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydGetRsFecSERThresholds
    To read the activate and deactivate thresholds and interval for degraded SER
*******************************************************************************/
MYD_STATUS mydGetRsFecSERThresholds
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,    
    IN MYD_U16 laneOffset,
    OUT MYD_U32 *serActivateThreshold,
    OUT MYD_U32 *serDeactivateThreshold,
    OUT MYD_U32 *serInterval
)
{
    MYD_OP_MODE opMode;    
    MYD_U16 lineSpeed, tmpLow, tmpHigh;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode)); 
    
    if (mydIsLaneOffsetValid(pDev, mdioPort, host_or_line, laneOffset) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydGetRsFecSERThresholds: Invalid lane used:%u \n", laneOffset);
        return MYD_FAIL;
    }

    lineSpeed = opModeTable[opMode][MYD_OP_TABLE_SPEED];

    if (lineSpeed != MYD_200GB)
    {
        MYD_DBG_ERROR("mydGetRsFecSERThresholds: Only supported on 200G RS-FEC\n");
        return MYD_FAIL;        
    }

    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_DEGSER_ACT_LOW, &tmpLow));    
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_DEGSER_ACT_LOW+1, &tmpHigh));
    *serActivateThreshold = (((MYD_U32)(tmpHigh))<<16) | ((MYD_U32)tmpLow);

    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_DEGSER_DEACT_LOW, &tmpLow));    
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_DEGSER_DEACT_LOW+1, &tmpHigh));
    *serDeactivateThreshold = (((MYD_U32)(tmpHigh))<<16) | ((MYD_U32)tmpLow);

    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_DEGSER_INT_LOW, &tmpLow));    
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_DEGSER_INT_LOW+1, &tmpHigh));
    *serInterval = (((MYD_U32)(tmpHigh))<<16) | ((MYD_U32)tmpLow);

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydGetRsFecDegradedSERStatus
    To read the status of the RS-FEC degraded SER.
*******************************************************************************/
MYD_STATUS mydGetRsFecDegradedSERStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,    
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *localDegradedSerRcvd,
    OUT MYD_U16 *remoteDegradedSerRcvd,
    OUT MYD_U16 *serDegraded
)
{
    MYD_OP_MODE opMode;    
    MYD_U16 lineSpeed, tmp;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);

    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode)); 
    
    if (mydIsLaneOffsetValid(pDev, mdioPort, host_or_line, laneOffset) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydGetRsFecSERThresholds: Invalid lane used:%u \n", laneOffset);
        return MYD_FAIL;
    }

    lineSpeed = opModeTable[opMode][MYD_OP_TABLE_SPEED];

    if (lineSpeed != MYD_200GB)
    {
        MYD_DBG_ERROR("mydGetRsFecSERThresholds: Only supported on 200G RS-FEC\n");
        return MYD_FAIL;        
    }    

    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, MYD_200GR4_FEC_DEG_SER, &tmp));

    ATTEMPT(mydHwGetRegFieldFromWord(tmp, 6, 1, localDegradedSerRcvd));
    ATTEMPT(mydHwGetRegFieldFromWord(tmp, 5, 1, remoteDegradedSerRcvd));    
    ATTEMPT(mydHwGetRegFieldFromWord(tmp, 4, 1, serDegraded));

    return MYD_OK;
    
}


/*******************************************************************************
 These functions are for KR-FEC
*******************************************************************************/

/*******************************************************************************
 MYD_STATUS mydSetKrFecControl
    Sets whether or not the FEC should indicate errors to the PCS layer
*******************************************************************************/
MYD_STATUS mydSetKrFecControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 bypassIndicationEnable
)
{ 
    MYD_U16 krFecControlAddr;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);
    
    if (mydIsLaneOffsetValid(pDev, mdioPort, host_or_line, laneOffset) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydSetKrFecControl: Invalid lane used:%u \n", laneOffset);
        return MYD_FAIL;
    }    

    krFecControlAddr = MYD_KRFEC_CNTL(host_or_line, laneOffset);

    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, krFecControlAddr, 1, 1, bypassIndicationEnable));

    return MYD_OK;
}


/*******************************************************************************
 MYD_STATUS mydGetKrFecControl
    Gets whether or not the FEC is set to indicate errors to the PCS layer
*******************************************************************************/
MYD_STATUS mydGetKrFecControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 *bypassIndicationEnable
)
{
    MYD_U16 krFecControlAddr;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);
    
    if (mydIsLaneOffsetValid(pDev, mdioPort, host_or_line, laneOffset) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydSetKrFecControl: Invalid lane used:%u \n", laneOffset);
        return MYD_FAIL;
    }    

    krFecControlAddr = MYD_KRFEC_CNTL(host_or_line, laneOffset);

    ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, krFecControlAddr, 1, 1, bypassIndicationEnable));

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydGetKrFecAbility
    Reads the ability bits from the KR-FEC status register.
*******************************************************************************/
MYD_STATUS mydGetKrFecAbility
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    OUT MYD_U16 *krFecAbility,
    OUT MYD_U16 *errIndicationAbility
)
{
    MYD_U16 krFecStatAddr, temp;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);
    
    if (mydIsLaneOffsetValid(pDev, mdioPort, host_or_line, laneOffset) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydSetKrFecControl: Invalid lane used:%u \n", laneOffset);
        return MYD_FAIL;
    }    

    krFecStatAddr = MYD_KRFEC_STAT(host_or_line, laneOffset);

    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, krFecStatAddr, &temp));
    *krFecAbility = (temp & 1);
    *errIndicationAbility = ((temp>>1) & 1);

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydGetKrFecCorrectedBlkCntr
    Reads the corrected block counter from the KR-FEC corrected block counter
    register.
*******************************************************************************/
MYD_STATUS mydGetKrFecCorrectedBlkCntr
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    OUT MYD_U32 *blockCounter
)
{   
    MYD_U16 correctedBlockLowerAddr, correctedBlockLower, correctedBlockUpper;

    *blockCounter = 0;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);
    
    if (mydIsLaneOffsetValid(pDev, mdioPort, host_or_line, laneOffset) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydGetKrFecCorrectedBlkCntr: Invalid lane used:%u \n", laneOffset);
        return MYD_FAIL;
    }
    
    correctedBlockLowerAddr = MYD_KRFEC_CORR_BLK_LOW(host_or_line, laneOffset);
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, correctedBlockLowerAddr, &correctedBlockLower));
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, correctedBlockLowerAddr+1, &correctedBlockUpper));

    *blockCounter = correctedBlockLower;
    *blockCounter |= (((MYD_U32)(correctedBlockUpper))<<16);

    return MYD_OK;
}


/*******************************************************************************
 MYD_STATUS mydGetKrFecCorrectedBlkCntr
    Reads the uncorrected block counter from the KR-FEC uncorrected block counter
    register.
*******************************************************************************/
MYD_STATUS mydGetKrFecUnCorrectedBlkCntr
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    OUT MYD_U32 *blockCounter
)
{  
    MYD_U16 uncorrectedBlockLowerAddr, uncorrectedBlockLower, uncorrectedBlockUpper;

    *blockCounter = 0;

    MYD_CHECK_DEV_SIDE(pDev, mdioPort, laneOffset, host_or_line);
    
    if (mydIsLaneOffsetValid(pDev, mdioPort, host_or_line, laneOffset) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydGetKrFecUnCorrectedBlkCntr: Invalid lane used:%u \n", laneOffset);
        return MYD_FAIL;
    }
    
    uncorrectedBlockLowerAddr = MYD_KRFEC_UNCORR_BLK_LOW(host_or_line, laneOffset);
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, uncorrectedBlockLowerAddr, &uncorrectedBlockLower));
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, uncorrectedBlockLowerAddr+1, &uncorrectedBlockUpper));

    *blockCounter = uncorrectedBlockLower;
    *blockCounter |= (((MYD_U32)(uncorrectedBlockUpper))<<16);

    return MYD_OK;
    
}

