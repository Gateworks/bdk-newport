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
This file contains functions and data that are strictly internal
for the proper functioning of the API on the Marvell X5123/EC808
PHY.
********************************************************************/
#include "mcdApiTypes.h"
#include "mcdApiRegs.h"
#include "mcdUtils.h"
#include "mcdHwCntl.h"
#include "mcdHwSerdesCntl.h"
#include "mcdAPI.h"
#include "mcdDiagnostics.h"
#include "mcdAPIInternal.h"
#include "mcdFwDownload.h"
#include "mcdInitialization.h"
#include "mcdPortCtrlApLogDefs.h"
#include "mcdInternalIpcApis.h"

#if DB_TEST_ENVIRONMENT
#include "windows.h"
#include "time.h"
#include "stdio.h"
#endif

/* device HW ID for X5123 and EC808 */
#define  MCD_MARVELL_OUI_X5123_HW_ID           0x005043
#define  MCD_MARVELL_OUI_X5123_HW_DEVICE_MODEL 0x3F

#ifdef MV_HWS_REDUCED_BUILD_EXT_CM3
extern MCD_DEV mcdDevDb;
#endif


extern MCD_STATUS mcdSetSetSerdesElectricalParametersDB
(
    unsigned int        portNum,
    MCD_OP_MODE         portMode,
    MCD_PORT_PER_SERDES_CONFIG_DATA*  paramsPtr
);

extern MCD_STATUS mcdSetSerdesCtleParametersDB
(
    unsigned int        portNum,
    MCD_OP_MODE         portMode,
    MCD_PORT_PER_SERDES_CTLE_CONFIG_DATA* ctleParamsPtr
);

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
MCD_STATUS mcdCheckIsDeviceSupported
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort
)
{
    MCD_STATUS rc;
    MCD_U16    data_high;
    MCD_U16    data_low;
    MCD_U32    dev_id;
    MCD_U32    model_num;

    rc = mcdHwXmdioRead(
        pDev, mdioPort,
        MCD_SMI_DEVICE_ID_HIGH_REGISTER/*dev*/,
        0/*reg*/ ,&data_high);
    if (rc != MCD_OK) return rc;

    rc = mcdHwXmdioRead(
        pDev, mdioPort,
        MCD_SMI_DEVICE_ID_LOW_REGISTER/*dev*/,
        0/*reg*/ ,&data_low);
    if (rc != MCD_OK) return rc;

    dev_id = (((MCD_U32)data_high << 6) | ((MCD_U32)(data_low >> 10) & 0x3F));
    model_num = ((MCD_U32)(data_low >> 4) & 0x3F);

    if ((dev_id != MCD_MARVELL_OUI_X5123_HW_ID) ||
        (model_num != MCD_MARVELL_OUI_X5123_HW_DEVICE_MODEL))
    {
        return MCD_FAIL;
    }

    return MCD_OK;
}
#endif
/*******************************************************************************
 MCD_STATUS mmcdSetApParameters
    Set Auto-neg advertising speeds
*******************************************************************************/
MCD_STATUS mcdSetAutoNegParameters
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U32  apLaneNum,
    IN MCD_U32 polarityVector,
    IN MCD_U32 modesVector,
    IN MCD_BOOL fcPause,
    IN MCD_BOOL fcAsmDir,
    IN MCD_FEC_TYPE fecSup,
    IN MCD_FEC_TYPE fecReq,
    IN MCD_BOOL nonceDis

)
{
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSetAutoNegParameters: incorrect port selection: %u\n", mdioPort);
        return MCD_FAIL;
    }
    pDev->apCfg[mdioPort].apLaneNum = apLaneNum;
    pDev->apCfg[mdioPort].modesVector = modesVector;
    pDev->apCfg[mdioPort].polarityVector = polarityVector;
    pDev->apCfg[mdioPort].fcPause =  fcPause;
    pDev->apCfg[mdioPort].fcAsmDir = fcAsmDir;
    pDev->apCfg[mdioPort].fecSup   = fecSup  ;
    pDev->apCfg[mdioPort].fecReq   = fecReq  ;
    pDev->apCfg[mdioPort].nonceDis = nonceDis;

    return MCD_OK;
}
/*******************************************************************************
 MCD_STATUS mcdIsPortValid
    Check the MDIO port  is valid
*******************************************************************************/
MCD_STATUS mcdIsPortValid
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort
)
{
    if (mdioPort >= MCD_MAX_PORT_NUM)
    {
        return MCD_STATUS_INVALID_PORT;
    }
    return MCD_OK;
}


#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3

/*******************************************************************************
 MCD_STATUS mcdIsFecParamValid
    Check if Fec is valid for the mode type
*******************************************************************************/
MCD_STATUS mcdIsFecParamValid
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_OP_MODE portMode,
    IN MCD_FEC_TYPE fecCorrect
)
{
    MCD_BOOL isFecInvalid = MCD_FALSE;

    //printf("portmode:%d, fecCorrect:%d\n", portMode, fecCorrect);
    switch (portMode)
    {
        case MCD_MODE_P100L:
        case MCD_MODE_P40L:
        case MCD_MODE_P50R2L:
        case MCD_MODE_P40R2L:
        case MCD_MODE_P25L:
        case MCD_MODE_P20L:
        case MCD_MODE_P10L:
            /* No FEC support for these modes */
            if (fecCorrect != MCD_NO_FEC)
            {
                isFecInvalid = MCD_TRUE;
            }
            break;
        case MCD_MODE_P10S:
        case MCD_MODE_P40C:
        case MCD_MODE_P40K:
        case MCD_MODE_P40S:
        case MCD_MODE_G21L:
            /* Supports only FC-FEC */
            if (fecCorrect & (MCD_RS_FEC_HOST | MCD_RS_FEC_LINE | MCD_RS_FEC))
            {
                isFecInvalid = MCD_TRUE;
            }
            break;
        case MCD_MODE_G21SK:
            /* Legacy feature, was only to support AP and FC-FEC configuration
               For new feature, where G21SK may also be used for non-AP & RS-FEC (host side only) */
            if (fecCorrect & (MCD_RS_FEC_LINE | MCD_RS_FEC))
            {
                isFecInvalid = MCD_TRUE;
            }
            break;
        case MCD_MODE_P100S:
        case MCD_MODE_P100C:
        case MCD_MODE_P100K:
            /* Supports only RS-FEC */
            if (fecCorrect & (MCD_FC_FEC_HOST | MCD_FC_FEC_LINE | MCD_FC_FEC))
            {
                isFecInvalid = MCD_TRUE;
            }
            break;
        default:
            if (fecCorrect > 0x3F)
            {
                MCD_DBG_ERROR("mcdIsFecParamValid :Error, value out of range");
                return MCD_FAIL;
            }
    }

    if (isFecInvalid)
    {
       MCD_DBG_ERROR("mcdIsFecParamValid :wrong FEC type %d port %d mode %d\n",fecCorrect, mdioPort,portMode);
       return MCD_FAIL;
    }

    return MCD_OK;
}

/**
* @internal mcdLaneSteeringModeValidate function
* @endinternal
*
* @brief   lane steering validation function
*
* @param[in] pDev                   - device pointer
* @param[in] mdioPort               - MDIO port, 0-7
* @param[in] masterSlice            - master slice 
* @param[in] laneSteeringMode       - lane steering port mode
*
* @retval MCD_OK                    - on success
* @retval MCD_FAIL                  - on failure
*
*
*/
MCD_STATUS mcdLaneSteeringModeValidate
(
    IN  MCD_DEV_PTR  pDev,
    IN  MCD_U16      mdioPort,
    IN  MCD_MASTER_SLICE  masterSlice,
    IN  MCD_LANE_STEERING_MODE  laneSteeringMode
)
{
    MCD_U16 slice;
    slice = mdioPort/MCD_MAX_CHANNEL_NUM_PER_SLICE;

    if (pDev == NULL)
    {
        MCD_DBG_ERROR("device data base was not allocated\n");
        return MCD_BAD_PTR;
    }

    if ((laneSteeringMode != MCD_G21L_NONE_STEERING) && (laneSteeringMode  != MCD_G21L_P10G_NONE_STEERING_AP)
        && (masterSlice == MCD_DUAL_SLICE))
    {
        MCD_DBG_ERROR("mcdLaneSteeringModeValidate: not supported masterSlice mode %d\n", masterSlice);
        return MCD_FAIL;
    }

    if ((laneSteeringMode == MCD_G21L_NONE_STEERING) &&  (masterSlice != MCD_DUAL_SLICE ))
    {
        MCD_DBG_ERROR("mcdLaneSteeringModeValidate: not supported masterSlice mode %d\n", masterSlice);
        return MCD_FAIL;
    }

    if ((laneSteeringMode == MCD_G21L_P10G_NONE_STEERING_AP) &&  (masterSlice != MCD_DUAL_SLICE ))
    {
        MCD_DBG_ERROR("mcdLaneSteeringModeValidate: not supported masterSlice mode %d\n", masterSlice);
        return MCD_FAIL;
    }

    if ((slice == 0) && (masterSlice == MCD_SLICE1))
    {
         MCD_DBG_ERROR("mcdLaneSteeringModeValidate: not supported masterSlice mode %d\n", masterSlice);
         return MCD_FAIL;
    }
    if ((slice == 1) && (masterSlice == MCD_SLICE0))
    {
         MCD_DBG_ERROR("mcdLaneSteeringModeValidate: not supported masterSlice mode %d\n", masterSlice);
         return MCD_FAIL;
    }

    return MCD_OK;

}

/**
* @internal mcdLaneSteeringRemapVectorRebuild function
* @endinternal
*
* @brief   constructing the remap data for single lane 
* lane steering mode
*
* @param[in] pDev                   - device pointer
* @param[in] mdioPort               - MDIO port, 0-7
* @param[in] slice                  - slice
* @param[in] laneSteeringMode       - lane steering port mode
* @param[in] laneSteeringOverride   - lane steering override
* pointer
*
* @retval MCD_OK                    - on success
* @retval MCD_FAIL                  - on failure
*
*
*/
MCD_STATUS mcdLaneSteeringRemapVectorRebuild
(
    IN  MCD_DEV_PTR  pDev,
    IN  MCD_U16 mdioPort,
    IN  MCD_U16 slice,
    IN  MCD_LANE_STEERING_MODE  laneSteeringMode,
    IN  MCD_LANE_STEERING_OVERRIDE_CFG* laneSteeringOverride
)
{
    MCD_U32 txRemapVector, rxRemapVector;
    MCD_U16  otherSlice;

    otherSlice = slice ? 0 : 1;
    switch (laneSteeringMode)
    {
        case MCD_1P_P25G_STEERING:
        case MCD_1P_P10G_STEERING:
        case MCD_1P_P10G_25G_STEERING_AP:
        case MCD_1P_P1G_1000BaseX_STEERING:
        case MCD_1P_P1G_SGMII_STEERING:
            ATTEMPT(mcdHwXmdioRead32bit(pDev, 0/* Don't care */, UMAC_SERDESMUX_laneremaptx(slice), (MCD_U32*)&txRemapVector));
            ATTEMPT(mcdHwXmdioRead32bit(pDev, 0/* Don't care */, UMAC_SERDESMUX_laneremaprx(slice), (MCD_U32*)&rxRemapVector));

            /* update pDev structure to operate in remap mode for host */
            pDev->laneRemapCfg[slice].hostRemapMode = MCD_LANE_REMAP_ENABLE;
            pDev->laneRemapCfg[slice].hostTxRemapVector = (MCD_U16)txRemapVector;
            pDev->laneRemapCfg[slice].hostRxRemapVector = (MCD_U16)rxRemapVector;
            if (laneSteeringOverride != NULL)
            {
                pDev->laneSteeringCfg.internalLpSerdes[mdioPort] = laneSteeringOverride[mdioPort].internalLpSerdes;
                pDev->laneSteeringCfg.externalLpSerdes[mdioPort] = laneSteeringOverride[mdioPort].externalLpbSerdes;
                /* in case we don't need lpb services from slave it's already updated */
                if (pDev->laneSteeringCfg.internalLpSerdes[mdioPort] != MCD_LANE_STEERING_NO_LPB)
                {
                    pDev->laneSteeringCfg.internalLpPort[mdioPort] = pDev->laneSteeringCfg.internalLpSerdes[mdioPort] - MCD_HOST_SIDE_START_SERDES_NUMBER; 
                    pDev->laneSteeringCfg.externalLpPort[mdioPort] = pDev->laneSteeringCfg.externalLpSerdes[mdioPort] - MCD_HOST_SIDE_START_SERDES_NUMBER;
                }
                break;
            }
            else
            {
                if (mdioPort == 2)
                {
                    pDev->laneSteeringCfg.internalLpSerdes[mdioPort] = 14;
                    pDev->laneSteeringCfg.externalLpSerdes[mdioPort] = 15;
                    pDev->laneSteeringCfg.internalLpPort[mdioPort] = pDev->laneSteeringCfg.internalLpSerdes[mdioPort] - MCD_HOST_SIDE_START_SERDES_NUMBER;
                    pDev->laneSteeringCfg.externalLpPort[mdioPort] = pDev->laneSteeringCfg.externalLpSerdes[mdioPort] - MCD_HOST_SIDE_START_SERDES_NUMBER;
                }
                if (mdioPort == 3)
                {
                    pDev->laneSteeringCfg.externalLpSerdes[mdioPort] = 12;
                    pDev->laneSteeringCfg.internalLpSerdes[mdioPort] = 13;
                    pDev->laneSteeringCfg.internalLpPort[mdioPort] = pDev->laneSteeringCfg.internalLpSerdes[mdioPort] - MCD_HOST_SIDE_START_SERDES_NUMBER;
                    pDev->laneSteeringCfg.externalLpPort[mdioPort] = pDev->laneSteeringCfg.externalLpSerdes[mdioPort] - MCD_HOST_SIDE_START_SERDES_NUMBER;
                }
                if (mdioPort == 4)
                {
                    pDev->laneSteeringCfg.externalLpSerdes[mdioPort] = 8;
                    pDev->laneSteeringCfg.internalLpSerdes[mdioPort] = 9;
                    pDev->laneSteeringCfg.internalLpPort[mdioPort] = pDev->laneSteeringCfg.internalLpSerdes[mdioPort] - MCD_HOST_SIDE_START_SERDES_NUMBER;
                    pDev->laneSteeringCfg.externalLpPort[mdioPort] = pDev->laneSteeringCfg.externalLpSerdes[mdioPort] - MCD_HOST_SIDE_START_SERDES_NUMBER;
                }
                if (mdioPort == 5)
                {
                    pDev->laneSteeringCfg.internalLpSerdes[mdioPort] = 10;
                    pDev->laneSteeringCfg.externalLpSerdes[mdioPort] = 11;
                    pDev->laneSteeringCfg.internalLpPort[mdioPort] = pDev->laneSteeringCfg.internalLpSerdes[mdioPort] - MCD_HOST_SIDE_START_SERDES_NUMBER;
                    pDev->laneSteeringCfg.externalLpPort[mdioPort] = pDev->laneSteeringCfg.externalLpSerdes[mdioPort] - MCD_HOST_SIDE_START_SERDES_NUMBER;
                }
                break;
            }
        default:
            /* for legacy lane steering modes the remap is done by software logic */
            pDev->laneRemapCfg[slice].hostRemapMode = MCD_LANE_REMAP_DISABLE;
            pDev->laneRemapCfg[slice].hostTxRemapVector = (MCD_U16)0;
            pDev->laneRemapCfg[slice].hostRxRemapVector = (MCD_U16)0;
    }

    /* At any case clear other slice remap configuration */
    pDev->laneRemapCfg[otherSlice].hostRemapMode = MCD_LANE_REMAP_DISABLE;
    pDev->laneRemapCfg[otherSlice].hostTxRemapVector = (MCD_U16)0;
    pDev->laneRemapCfg[otherSlice].hostRxRemapVector = (MCD_U16)0;

    return MCD_OK;
}

/**
* @internal mcdLaneSteeringSingleModeTune function
* @endinternal
*
* @brief   single mode tuning for lane steering
* lane steering mode
*
* @param[in] pDev                   - device pointer
* @param[in] mdioPort               - MDIO port, 0-7
* @param[in] masterSlice            - master slice
*
* @retval MCD_OK                    - on success
* @retval MCD_FAIL                  - on failure
*
*
*/
MCD_STATUS mcdLaneSteeringSingleModeTune
(
    IN  MCD_DEV_PTR  pDev,
    IN  MCD_U16  mdioPort,
    IN  MCD_MASTER_SLICE  masterSlice
)
{
    MCD_U16 chan;
    MCD_U8 indirectSerdes = 0; /* defines the serdes on the slave slice that connected to the ASIC */
    MCD_U8 indirectInternalSerdes = 0; /* defines the serdes on the slave slice that internally connected to the master slice */
    MCD_AUTO_TUNE_STATUS rxStatus = MCD_TUNE_FAIL;
    chan = mdioPort % MCD_MAX_CHANNEL_NUM_PER_SLICE;

    /* serdes RX lane that connected to the ASIC */
    indirectSerdes = pDev->laneSteeringCfg.externalLpSerdes[mdioPort];
    /* serdes RX lane that connected between slices */
    indirectInternalSerdes = pDev->laneSteeringCfg.internalLpSerdes[mdioPort];

    if (indirectSerdes != MCD_LANE_STEERING_NO_LPB)
    {
        ATTEMPT(mcdSerdesAutoTuneStartExt(pDev, indirectSerdes, MCD_ONE_SHOT_DFE_TUNING, MCD_IGNORE_TX_TRAINING));
    }
    else
    {
         ATTEMPT(mcdSerdesAutoTuneStartExt(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), masterSlice), MCD_ONE_SHOT_DFE_TUNING, MCD_IGNORE_TX_TRAINING));
    }

    /* Note!!!
       since we only have remap configuration on the master slice, the slave slice must get physical values */
    if (pDev->highAvailabilityMode == MCD_FALSE)
    {
        if (indirectSerdes != MCD_LANE_STEERING_NO_LPB)
        {
            /* verify iCal is finished before running Adaptive DFE */
            ATTEMPT(mcdSerdesAutoTuneStatus(pDev, indirectSerdes, &rxStatus, NULL));
        }
        else
        {
             /* verify iCal is finished before running Adaptive DFE */
            ATTEMPT(mcdSerdesAutoTuneStatus(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), masterSlice), &rxStatus, NULL));
        }

        if (rxStatus != MCD_TUNE_PASS)
        {
            MCD_DBG_ERROR("mcdSetLaneSteering: AutoTuneStatus fail, mdioPort %d \n", mdioPort);
            return MCD_FAIL;
        }
    }

    mcdWrapperMsSleep(500);

    /* Run adaptive pCal training on rx serdes which connected to ASIC */
    if (indirectSerdes != MCD_LANE_STEERING_NO_LPB)
    {
        ATTEMPT(mcdSerdesAutoTuneStartExt(pDev, indirectSerdes, MCD_START_CONTINUE_ADAPTIVE_TUNING, MCD_IGNORE_TX_TRAINING));
    }
    else
    {
        ATTEMPT(mcdSerdesAutoTuneStartExt(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), masterSlice),
                                                MCD_START_CONTINUE_ADAPTIVE_TUNING, MCD_IGNORE_TX_TRAINING));
    }


    /* Run iCal/VSR training on the internal lanes connected between the slices for each port
    need to apply iCal on the master slice and slave slice - total 2 SerDes */
    if (indirectSerdes != MCD_LANE_STEERING_NO_LPB)
    {
        /* first run iCal/VSR on the logical serdes number which will be converted to the physical serdes */
        ATTEMPT(mcdSerdesAutoTuneStartExt(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), masterSlice),
                                              MCD_ONE_SHOT_DFE_TUNING, MCD_IGNORE_TX_TRAINING));
        /* secondly, run iCal/VSR on the serdes that is internally connected to the physical serdes */
        ATTEMPT(mcdSerdesAutoTuneStartExt(pDev, indirectInternalSerdes,
                                              MCD_ONE_SHOT_DFE_TUNING, MCD_IGNORE_TX_TRAINING));
    }

    if (pDev->highAvailabilityMode == MCD_FALSE)
    {
        if (indirectSerdes != MCD_LANE_STEERING_NO_LPB)
        {
            ATTEMPT(mcdSerdesAutoTuneStatus(pDev, indirectInternalSerdes, &rxStatus, NULL));
            ATTEMPT(mcdSerdesAutoTuneStatus(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), masterSlice), &rxStatus, NULL));
        }

        if (rxStatus != MCD_TUNE_PASS)
        {
            MCD_DBG_ERROR("mcdSetLaneSteering: AutoTuneStatus fail, mdioPort %d \n", mdioPort);
            return MCD_FAIL;
        }
    }
    /* reconfigure loopback so the serdes will reclaibrate */
    if (indirectSerdes != MCD_LANE_STEERING_NO_LPB)
    {
        ATTEMPT(mcdSerdesSetLoopback(pDev, ((MCD_U16)indirectSerdes +1), MCD_PARALLEL_SERDES_LOOPBACK));
        ATTEMPT(mcdSerdesSetLoopback(pDev, ((MCD_U16)indirectInternalSerdes +1), MCD_PARALLEL_SERDES_LOOPBACK));
    }

    mcdWrapperMsSleep(50);

    return MCD_OK;
}

/*******************************************************************
 MCD_STATUS mcdPowerMgmtLineWait
    Extend power management wait time
*******************************************************************/
MCD_STATUS mcdPowerMgmtLineWait
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_OP_MODE portMode,
    IN MCD_U16 waitBits
)
{
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdPowerMgmtLineWait: incorrect mdioPort selection: %u\n", mdioPort);
        return MCD_FAIL;
    }

    return MCD_NOT_IMPLEMENTED;
}

/*******************************************************************
 MCD_STATUS mcdPCSModePortPowerUp
    Power up chip PCS Mode
*******************************************************************/
MCD_STATUS mcdPCSModePortPowerUp
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_OP_MODE portMode
)
{
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdPCSModePortPowerUp: incorrect mdioPort selection: %u\n", mdioPort);
        return MCD_FAIL;
    }

    return MCD_NOT_IMPLEMENTED;
}

/*******************************************************************
 MCD_STATUS mcdPortPowerUp
    Power up chip PCS Mode
*******************************************************************/
MCD_STATUS mcdPortPowerUp
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_OP_MODE portMode
)
{
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdPortPowerUp: incorrect mdioPort selection: %u\n", mdioPort);
        return MCD_FAIL;
    }

    return MCD_NOT_IMPLEMENTED;
}

/*******************************************************************
 MCD_STATUS mcdConfigRepeaterCK
    Power up chip PCS Mode
*******************************************************************/
MCD_STATUS mcdConfigRepeaterCK
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_OP_MODE portMode
)
{
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdConfigRepeaterCK: incorrect mdioPort selection: %u\n", mdioPort);
        return MCD_FAIL;
    }

    return MCD_NOT_IMPLEMENTED;
}
#endif
/*******************************************************************
 MCD_STATUS mcdChannelSwReset
    Software Reset/Unreset of channel.
    Both Host and Line sides are in same state.
*******************************************************************/
MCD_STATUS mcdChannelSwReset
(
    IN MCD_DEV_PTR  pDev,
    IN MCD_U16      port,
    IN MCD_BOOL     action
)
{
    /* Assert/De-assert software reset for selected channel*/
    MCD_U32       fieldOffset,slice;

    slice = port / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    fieldOffset = CHAN_IN_SLICE_NUM(port);

    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, UMAC_GLBL_Software_Reset(slice), fieldOffset, 1/*    fieldLength*/, action/* 1 -set  ,0 - clear */));

    return MCD_OK;
}

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/* MCD_STATUS mcdChannelMacBypas set/clear MAC and MACSEC and rate match bypass */
MCD_STATUS mcdChannelMacBypass
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 chan,
    IN MCD_BOOL action
)
{
    MCD_U8       slice;

    slice = chan / MCD_MAX_CHANNEL_NUM_PER_SLICE;

    chan = CHAN_IN_SLICE_NUM(chan);

    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, UMAC_GLBL_Bypass(slice), chan, 1, action));       /* MACSEC bypass*/
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, UMAC_GLBL_Bypass(slice), (4 + chan), 1, action)); /* MAC and MACSEC bypass   */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, UMAC_GLBL_Bypass(slice), (8 + chan), 1, action)); /* rate match bypass*/

    return MCD_OK;
}

/*******************************************************************
 MCD_STATUS mcdChannelControl
   Channel enable/disable.
    Both Host and Line sides are in same state.
*******************************************************************/
MCD_STATUS mcdChannelControl
(
    IN MCD_DEV_PTR  pDev,
    IN MCD_U16      port,
    IN MCD_BOOL     action
)
{
    /* Assert/De-assert software reset for selected channel*/
    MCD_U32       fieldOffset,slice;
    MCD_U32       fieldOffsetLs = 0;

    slice = port / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    fieldOffset = CHAN_IN_SLICE_NUM(port);

    /* Fall back Link timer & AN Advertisement to default value */
    if (((pDev->portConfig[port].portMode == MCD_MODE_P1) ||
         (pDev->portConfig[port].portMode == MCD_MODE_P1_SGMII) ||
         (pDev->portConfig[port].portMode == MCD_MODE_P1_BaseX_SGMII)))
    {
        /* override LinkTimer on Host side to default */
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, port, UMAC_LSMCPCS_lnktimer(slice, fieldOffset), 0, 16, 0x12D0));
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, port, UMAC_LSMCPCS_lnktimer2(slice, fieldOffset), 0, 8, 0x13));

        /* for Line side */
        fieldOffsetLs = fieldOffset + 4;
        /* override LinkTimer on Line side to default */
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, port, UMAC_LSMCPCS_lnktimer(slice, fieldOffsetLs), 0, 16, 0x12D0));
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, port, UMAC_LSMCPCS_lnktimer2(slice, fieldOffsetLs), 0, 8, 0x13));

        /* override AN Advertisement bits on Host side to default */
        ATTEMPT(mcdHwXmdioWrite32bit(pDev, port, UMAC_LSMCPCS_mradvability(slice, fieldOffset), 0x800));
        /* override AN Advertisement bits on Line side to default */
        ATTEMPT(mcdHwXmdioWrite32bit(pDev, port, UMAC_LSMCPCS_mradvability(slice, fieldOffsetLs), 0x800));
    }

    /* PCS Channel Enable/Disable */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, port, UMAC_GLBL_Channel_Enable(slice), fieldOffset, 1, action));

    return MCD_OK;
}

/* MCD_STATUS mcdClockGatingControl set/clear clock gating for MAC ,MACSEC, PCS and PCS channels*/
MCD_STATUS mcdClockGatingControl
(
    IN MCD_DEV_PTR pDev,
    IN MCD_CLOCK_GATE_TYPE cgType,
    IN MCD_U16 portNum,
    IN MCD_U16 host_or_line,
    IN MCD_BOOL action
)
{
    MCD_U8       slice,chan,side=0;
    MCD_U8       fieldOffset;


    slice = portNum / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan = CHAN_IN_SLICE_NUM(portNum);

    switch (host_or_line)
    {
    case MCD_HOST_SIDE:
        side = 0;
        break;
    case MCD_LINE_SIDE:
        side = 1;
        break;
    case MCD_BOTH_SIDE:
        side = 2;
        break;
    default:
        if ((cgType == MCD_PCS_CHANNEL_CLOCK_GATE) || (cgType == MCD_PCS_CLOCK_GATE))
        {
            MCD_DBG_ERROR("ClockGatingControl: incorrect host_or_line value: %u\n", host_or_line);
            return MCD_FAIL;
        }
    }

    switch(cgType)
    {
    case MCD_PCS_CHANNEL_CLOCK_GATE:
        if (side == 2)
        {
            fieldOffset = MCD_CLOCK_GATING_SLICE_OFFSET * slice + MCD_CLOCK_GATING_PCS_CHANNEL_OFFSET + chan;
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, RUNIT_SOC_MISC_CLOCK_GATING_REGISTER, fieldOffset, 1, action));
            fieldOffset = MCD_CLOCK_GATING_SLICE_OFFSET * slice + MCD_CLOCK_GATING_PCS_CHANNEL_OFFSET + chan + 4;
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, RUNIT_SOC_MISC_CLOCK_GATING_REGISTER, fieldOffset, 1, action));
        }
        else
        {
            fieldOffset = MCD_CLOCK_GATING_SLICE_OFFSET * slice + MCD_CLOCK_GATING_PCS_CHANNEL_OFFSET + chan + side  * 4;
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, RUNIT_SOC_MISC_CLOCK_GATING_REGISTER, fieldOffset, 1, action));
        }
        break;
    case MCD_PCS_CLOCK_GATE:
        if (side == 2)
        {
            fieldOffset = MCD_CLOCK_GATING_SLICE_OFFSET * slice;
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, RUNIT_SOC_MISC_CLOCK_GATING_REGISTER, fieldOffset, 1, action));
            fieldOffset = MCD_CLOCK_GATING_SLICE_OFFSET * slice + 1;
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, RUNIT_SOC_MISC_CLOCK_GATING_REGISTER, fieldOffset, 1, action));
        }
        else
        {
            fieldOffset = MCD_CLOCK_GATING_SLICE_OFFSET * slice + side;
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, RUNIT_SOC_MISC_CLOCK_GATING_REGISTER, fieldOffset, 1, action));
        }
        break;
    case MCD_MAC_CLOCK_GATE:
        fieldOffset = MCD_CLOCK_GATING_SLICE_OFFSET * slice + MCD_CLOCK_GATING_MAC_OFFSET;
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, RUNIT_SOC_MISC_CLOCK_GATING_REGISTER, fieldOffset, 1, action));
        break;
    case MCD_MACSEC_CLOCK_GATE:
        fieldOffset = MCD_CLOCK_GATING_SLICE_OFFSET * slice + MCD_CLOCK_GATING_MACSEC_OFFSET;
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, RUNIT_SOC_MISC_CLOCK_GATING_REGISTER, fieldOffset, 1, action));
        break;
    default:
        MCD_DBG_ERROR("ClockGatingControl: incorrect ClockGating type: %u\n", cgType);
        return MCD_FAIL;
    }

    return MCD_OK;
}

#endif /*#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3*/
/* mcdGlobalModeSet set mode for channel both sides, channel number is 0-3 */
MCD_STATUS mcdGlobalModeSet
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 slice,
    IN MCD_U16 chan,
    IN MCD_OP_MODE portMode
)
{
   MCD_U32 readMode,mdioPort, data;

   mdioPort = pDev->firstMdioPort;

   switch (portMode)
    {
        case MCD_MODE_P100L:
        case MCD_MODE_P100S:
        case MCD_MODE_P100C:
        case MCD_MODE_P100K:
            data = UMAC_GLOBAL_MODE_100G;
            /*ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Global_Mode(slice), 0, 4, UMAC_GLOBAL_MODE_100G));*/
            break;
        case MCD_MODE_G21L:
        case MCD_MODE_G21SK:
        case MCD_MODE_P40L:
        case MCD_MODE_P40C:
        case MCD_MODE_P40S:
        case MCD_MODE_P40K:
            data = UMAC_GLOBAL_MODE_2x40G;
            /* only one port may be define in this mode since on other side all lines in use UMAC_GLOBAL_MODE_1x40G??? */
           /* ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Global_Mode(slice), 0, 4, UMAC_GLOBAL_MODE_2x40G));*/
            break;
        case MCD_MODE_P50R2L:
        case MCD_MODE_P50R2S:
        case MCD_MODE_P40R2L:
        case MCD_MODE_P40R2S:
        {
        /* check the mode of second half of the slice */
            ATTEMPT(mcdHwGetPhyRegField32bit(pDev,mdioPort,UMAC_GLBL_Global_Mode(slice), 0, 4, &readMode));
            if (chan == 0)
            {
                if ((readMode == UMAC_GLOBAL_MODE_50G_2x25G) ||(readMode == UMAC_GLOBAL_MODE_4x25G ))
                {
                    data = UMAC_GLOBAL_MODE_50G_2x25G;
                    /*ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Global_Mode(slice), 0, 4, UMAC_GLOBAL_MODE_50G_2x25G));*/
                }
                else
                {
                    data = UMAC_GLOBAL_MODE_2x40G;
                    /*ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Global_Mode(slice), 0, 4, UMAC_GLOBAL_MODE_2x40G));*/
                }
            }
            else if (chan == 2)
            {
                if ((readMode == UMAC_GLOBAL_MODE_2x25G_50G) ||(readMode == UMAC_GLOBAL_MODE_4x25G ))
                {
                    data = UMAC_GLOBAL_MODE_2x25G_50G;
                    /*ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Global_Mode(slice), 0, 4, UMAC_GLOBAL_MODE_2x25G_50G));*/
                }
                else
                {
                    data = UMAC_GLOBAL_MODE_2x40G;
                    /*ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Global_Mode(slice), 0, 4, UMAC_GLOBAL_MODE_2x40G));*/
                }
            }
            else
            {
                return MCD_OK;
            }
            /*ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Global_Mode(slice), 0, 4, data));*/
            break;
        }
        case MCD_MODE_P20L:
        case MCD_MODE_P20S:
        case MCD_MODE_P25L:
        case MCD_MODE_P25S:
        case MCD_MODE_P10L:
        case MCD_MODE_P10S:
        {
            ATTEMPT(mcdHwGetPhyRegField32bit(pDev,mdioPort,UMAC_GLBL_Global_Mode(slice), 0, 4, &readMode));
            if ((chan == 0) || (chan == 1))
            {
                if ((readMode == UMAC_GLOBAL_MODE_2x25G_50G) || (readMode == UMAC_GLOBAL_MODE_2x40G ))
                {
                    data = UMAC_GLOBAL_MODE_2x25G_50G;
                }
                else
                {
                    data = UMAC_GLOBAL_MODE_4x25G;
                }
            }
            else /* ((chan == 2) || (chan == 3)) */
            {
                if ((readMode == UMAC_GLOBAL_MODE_2x40G) || (readMode == UMAC_GLOBAL_MODE_50G_2x25G ))
                {
                    data = UMAC_GLOBAL_MODE_50G_2x25G;
                }
                else
                {
                    data = UMAC_GLOBAL_MODE_4x25G;
                }
            }
            break;
        }
        case MCD_MODE_P2_5:
        case MCD_MODE_P1:
        default:
        {
            MCD_DBG_ERROR("mcdGlobalModeSet: incorrect Port mode %u\n", portMode);
            return MCD_FAIL;
        }
   }
   ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Global_Mode(slice), 0, 4, data));
   return MCD_OK;
}

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/**
* @internal mcdPortSerdesTxEnable function
* @endinternal
*
* @brief   Enable/Disable Tx of port lines.
*
* @retval MCD_OK                   - on success
* @retval MCD_FAIL                 - on error
* @retval MCD_STATUS_NOT_READY     - when training is in process.
*/
MCD_STATUS mcdPortSerdesTxEnable
(
   MCD_DEV_PTR      pDev,
   MCD_U16          phyPortNum,
   MCD_BOOL         enable
)
{
    MCD_U16 slice,chan,serdesNum;
    MCD_OP_MODE      portMode;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("%s: device not initialized\n", __func__);
        return MCD_FAIL;
    }
    slice = phyPortNum / MCD_MAX_CHANNEL_NUM_PER_SLICE;

    chan = CHAN_IN_SLICE_NUM(phyPortNum);

    portMode = pDev->portConfig[phyPortNum].portMode;

    switch(portMode)
    {
        case MCD_MODE_P100L:
        case MCD_MODE_P100S:
        case MCD_MODE_P100C:
        case MCD_MODE_P100K:
        case MCD_MODE_P40L:
        case MCD_MODE_P40S:
        case MCD_MODE_P40C:
        case MCD_MODE_P40K:
        case MCD_MODE_G21L:
        case MCD_MODE_G21SK:
            if (chan != 0) /* only on chan 0*/
            {
                MCD_DBG_ERROR("%s: wrong channel number %u\n", __func__, chan);
                return MCD_FAIL;
            }

            for ( serdesNum = 0; serdesNum < 4; serdesNum++)
            {
                ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), enable));
            }
            break;

        case MCD_MODE_P50R2L:
        case MCD_MODE_P50R2S:
        case MCD_MODE_P40R2L:
        case MCD_MODE_P40R2S:
            if ((chan != 0) && (chan != 2))
            {
                MCD_DBG_ERROR("%s: wrong channel number %u\n", __func__, chan);
                return MCD_FAIL;
            }
            for ( serdesNum = chan; serdesNum < (chan + 2); serdesNum++)
            {
                ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), enable));
            }
            break;
        case MCD_MODE_P20L:
        case MCD_MODE_P20S:
        case MCD_MODE_P25L:
        case MCD_MODE_P25S:
        case MCD_MODE_P10L:
        case MCD_MODE_P10S:
        case MCD_MODE_P2_5:
        case MCD_MODE_P2_5S:
        case MCD_MODE_P1:
        case MCD_MODE_P1_SGMII:
        case MCD_MODE_P1_BaseX_SGMII:
            ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(chan,slice), enable));
            break;
        case MCD_MODE_R100L:
        case MCD_MODE_R100C:
            if (chan != 0) /* 100G  only on chan 0*/
            {
                MCD_DBG_ERROR("%s: wrong channel number %u\n", __func__, chan);
                return MCD_FAIL;
            }
            for ( serdesNum = chan ; serdesNum < 4; serdesNum++)
            {
                ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), enable));
            }
            break;
        case MCD_MODE_R40L:
        case MCD_MODE_R40C:
            if ((chan != 0) && (chan != 2))
            {
                MCD_DBG_ERROR("%s: wrong channel number %u\n", __func__, chan);
                return MCD_FAIL;
            }
            ATTEMPT(mcdChannelMacBypass(pDev, chan, MCD_TRUE));
            for ( serdesNum = chan; serdesNum <  (chan + 2); serdesNum++)
            {
                ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), enable));
            }

            break;
        case MCD_MODE_R25L:
        case MCD_MODE_R25C:
            ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(chan, slice), enable));
             break;
        case MCD_MODE_R10L:
        case MCD_MODE_R10K:
        case MCD_MODE_R1L:
        case MCD_MODE_R1C:
            ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(chan, slice), enable));
            break;
        default:
            MCD_DBG_ERROR("%s: incorrect mode selection: %u\n", __func__, portMode);
            return MCD_FAIL;
    }

    return MCD_OK;
}
#endif /*#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3*/
/* MCD_STATUS mcdConfigurePcs1gR1 configure 1GR1 mode on unit - channel one side,
   side is defined by unit number( 0-3 - host side, 4-7 line side)
   basex_or_sgmii = 0 (SGMII) or 1 (BASE-R1/BASEX)*/
MCD_STATUS mcdConfigurePcs1gR1
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 slice,
    IN MCD_U16 channelUnit,
    IN MCD_U16 basex_or_sgmii,
    IN MCD_BOOL anEnable
)
{

    MCD_U16     mdioPort;
    MCD_U16     host_or_line;
    MCD_U16     portNum;
    MCD_U8      chnOffset;

    mdioPort = pDev->firstMdioPort;

    chnOffset       = CHAN_IN_SLICE_NUM(channelUnit);
    host_or_line    = MCD_HOST_OR_LINE_SIDE(channelUnit);
    portNum         = MCD_GET_PORTNUM_FROM_CHANUNIT(slice, channelUnit);

    /* Assert software reset for the channel*/
    ATTEMPT(mcdChannelSwReset(pDev, chnOffset, MCD_TRUE));

   /*set Global mode*/
    ATTEMPT(mcdGlobalModeSet(pDev, slice, chnOffset,  MCD_MODE_P10L));

   /* Reset Channel L1_0 PPM link-up threshold to 5*/
    if (channelUnit < 4)
    {
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (UMAC_GLBL_L1_1_B2B_PPM_Compensation_Ctrl_CH0(slice) + 4 * chnOffset), 4, 6, 5));
    }
    else
    {
        if ((channelUnit >= 4) && (channelUnit < 6))
        {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (UMAC_GLBL_L1_0_B2B_PPM_Compensation_Ctrl_CH0(slice) + 4 * chnOffset), 4, 6, 5));
        }
        /* L1_0_B2B CH2 & CH3 address are not in steps of 4 w.r.t CH1 */
        else if (channelUnit >= 6)
        {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (UMAC_GLBL_L1_0_B2B_PPM_Compensation_Ctrl_CH0(slice) + 4 * (chnOffset+1)), 4, 6, 5));
        }
    }
   /* Enable Channel*/
   ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Channel_Enable(slice), chnOffset, 1, 1));

   /* Enable Channel  RX MAC */
   ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_Channel_MAC_Control(slice,channelUnit), 1, 1, 1));

   /* Set Channel mode to 1G*/
   ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Channel_Mode(slice), (chnOffset*2), 2, UMAC_CHANNEL_MODE_1G));

   /*Set PMA mode to BASE-R1/BASEX or SGMII; SGMII= 0, BASEX= 1 */
   ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_MCPCS_Ch_Mode(slice, channelUnit), 2, 4, (1 + (basex_or_sgmii*2))));

   /* If AN is enabled, Advertise capabilites for 1000Base-x */
   if ((basex_or_sgmii == MCD_TRUE) && (anEnable))
   {
       ATTEMPT(mcdLowSpeedANAdvertSet(pDev, portNum, host_or_line, (MCD_BASEX_AD_1000FDX | MCD_BASEX_AD_1000HDX)));
   }

   /* Set LS speed to 1G */
   ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_LSMCPCS_ctrl(slice, channelUnit), 10, 2, MCD_LOW_SPEED_1000M));

   /* Auto neg enable/disable */
   ATTEMPT(mcdLowSpeedANEnable(pDev, portNum, host_or_line, anEnable));

   /*Remove software reset on the channel */
   ATTEMPT(mcdChannelSwReset(pDev, chnOffset, MCD_FALSE));
   return MCD_OK;
}

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/* ******************************************************************************************
   MCD_STATUS mcdConfigurePcs2p5gR1
   This function performs channel configuration in 2.5G USXGMII mode
   on unit - channel one side,side is defined by unit number( 0-3 - host side, 4-7 line side)
********************************************************************************************/
MCD_STATUS mcdConfigurePcs2p5gR1
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 slice,
    IN MCD_U16 channelUnit,
    IN MCD_FEC_TYPE fecCorrect
)
{

    MCD_U16      mdioPort;
    MCD_U8       chnOffset;

    mdioPort = pDev->firstMdioPort;
    chnOffset = CHAN_IN_SLICE_NUM(channelUnit);

    /* Assert software reset for the channel*/
    ATTEMPT(mcdChannelSwReset(pDev, chnOffset, MCD_TRUE));

   /*set Global mode*/
    ATTEMPT(mcdGlobalModeSet(pDev, slice, chnOffset,  MCD_MODE_P10L));

   /* Reset Channel L1_0 PPM link-up threshold to 5*/
    if (channelUnit < 4)
    {
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (UMAC_GLBL_L1_1_B2B_PPM_Compensation_Ctrl_CH0(slice) + 4 * chnOffset), 4, 6, 5));
    }
    else
    {
        if ((channelUnit >= 4) && (channelUnit < 6))
        {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (UMAC_GLBL_L1_0_B2B_PPM_Compensation_Ctrl_CH0(slice) + 4 * chnOffset), 4, 6, 5));
        }
        /* L1_0_B2B CH2 & CH3 address are not in steps of 4 w.r.t CH1 */
        else if (channelUnit >= 6)
        {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (UMAC_GLBL_L1_0_B2B_PPM_Compensation_Ctrl_CH0(slice) + 4 * (chnOffset+1)), 4, 6, 5));
        }
    }
   /* Enable Channel*/
   ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Channel_Enable(slice), chnOffset, 1, 1));

   /* Enable Channel  RX MAC */
   ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_Channel_MAC_Control(slice,channelUnit), 1, 1, 1));

   /* Set Channel mode to 0 - in 2.5G mode thes bits are ignored by the UMAC*/
   ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Channel_Mode(slice), (chnOffset*2), 2, 0));

   /*Set PMA mode to USXGMII for Channel */
   ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_MCPCS_Ch_Mode(slice,channelUnit), 2, 4, 0xC));

   /* Enabled USXGMII faults on RX and TX for Channel*/
   ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_MCPCS_UXGMII_Faults_Control(slice,channelUnit), 0, 2, 0x3));

   if (fecCorrect)
   {
       /* Set FEC mode to RS or FC  for the Channel -  bits 0-1 set to 1 or 2 */
       ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_MCPCS_Ch_Mode(slice,channelUnit), 0, 2, ~(fecCorrect & 3)));
       if (fecCorrect == MCD_FC_FEC)
       {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_MCPCS_Debug_Control1(slice,channelUnit), 14, 1, 1));
       }
   }
   else
   {
       /* Set FEC mode to none for the Channel   -  bits 0-1 set to 0*/
      ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_MCPCS_Ch_Mode(slice,channelUnit), 0, 2, 0));
   }

   /*Remove software reset on the channel */
   ATTEMPT(mcdChannelSwReset(pDev, chnOffset, MCD_FALSE));
   return MCD_OK;
}
/* *******************************************************************************
  MCD_STATUS mcdConfigurePcs2p5gBasex
   This function performs channel configuration in 2.5G BASEx mode
*******************************************************************************/
MCD_STATUS mcdConfigurePcs2p5gBasex
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 slice,
    IN MCD_U16 channelUnit
)
{

    MCD_U16      mdioPort;
    MCD_U8       chnOffset;

    mdioPort = pDev->firstMdioPort;
    chnOffset = CHAN_IN_SLICE_NUM(channelUnit);

    /* Assert software reset for the channel*/
    ATTEMPT(mcdChannelSwReset(pDev, chnOffset, MCD_TRUE));

   /*set Global mode*/
    ATTEMPT(mcdGlobalModeSet(pDev, slice, chnOffset,  MCD_MODE_P10L));

   /* Reset Channel L1_0 PPM link-up threshold to 5*/
    if (channelUnit < 4)
    {
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (UMAC_GLBL_L1_1_B2B_PPM_Compensation_Ctrl_CH0(slice) + 4 * chnOffset), 4, 6, 5));
    }
    else
    {
        if ((channelUnit >= 4) && (channelUnit < 6))
        {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (UMAC_GLBL_L1_0_B2B_PPM_Compensation_Ctrl_CH0(slice) + 4 * chnOffset), 4, 6, 5));
        }
        /* L1_0_B2B CH2 & CH3 address are not in steps of 4 w.r.t CH1 */
        else if (channelUnit >= 6)
        {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (UMAC_GLBL_L1_0_B2B_PPM_Compensation_Ctrl_CH0(slice) + 4 * (chnOffset+1)), 4, 6, 5));
        }
    }
   /* Enable Channel*/
   ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Channel_Enable(slice), chnOffset, 1, 1));

   /* Enable Channel  RX MAC */
   ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_Channel_MAC_Control(slice,channelUnit), 1, 1, 1));

   /* SSet Channel mode 0 to 1G*/
   ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Channel_Mode(slice), (chnOffset*2), 2, 1));

   /*Set PMA mode to USXGMII for Channel */
   ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_MCPCS_Ch_Mode(slice,channelUnit), 2, 4, 0x3));

   /* Set LS speed to 1G*/
   ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_LSMCPCS_ctrl(slice,channelUnit), 10, 2, 0x2));

   /*Remove software reset on the channel */
   ATTEMPT(mcdChannelSwReset(pDev, chnOffset, MCD_FALSE));
   return MCD_OK;
}
#endif /*#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3*/

MCD_STATUS mcdConfigurePcsEnChannelCommon
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 slice,
    IN MCD_U16 channelUnit,
    MCD_U8       chnOffset,
    MCD_U16      mdioPort
)
{
        /* Enable Channel 0*/
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Channel_Enable(slice), chnOffset, 1,  1));

    /*Enable Channel 0 RX MAC*/
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_Channel_MAC_Control(slice,channelUnit), 1, 1, 1));
    return MCD_OK;
}

MCD_STATUS mcdConfigurePcsCommon(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 slice,
    IN MCD_U16 channelUnit,
    IN MCD_FEC_TYPE fecCorrect,
    IN MCD_CHANNEL_MODE_TYPE chanMode,
    IN MCD_U16 checkFec

)
{
    MCD_U8       chnOffset = CHAN_IN_SLICE_NUM(channelUnit);
    MCD_U16      mdioPort = pDev->firstMdioPort;
   /* Set PMA mode */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_MCPCS_Ch_Mode(slice,channelUnit), 2, 4, chanMode));

    if (fecCorrect)
    {
        /* Set FEC mode to RS or FC  for the Channel - bits 0-1 set to 1 or 2 */
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_MCPCS_Ch_Mode(slice,channelUnit), 0, 2, ~(fecCorrect & 3)));
        if (checkFec) {
            if (fecCorrect == MCD_FC_FEC)
            {
                 ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_MCPCS_Debug_Control1(slice,channelUnit), 14, 1, 1));
            }
        }
    }
    else
    {
        /* Set FEC mode to none for the Channel -  bits 0-1 set to 0*/
       ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_MCPCS_Ch_Mode(slice,channelUnit), 0, 2, 0));
    }

    /*Remove software reset on the channel */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Software_Reset(slice), chnOffset, 1, 0));
    return MCD_OK;
}

/* MCD_STATUS mcdConfigurePcs10_25gR1 configure 10GR1 or25GR1 mode on unit - channel one side;
   side is defined by unit number( 0-3 - host side, 4-7 line side)  */
MCD_STATUS mcdConfigurePcs10_25gR1
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 slice,
    IN MCD_U16 channelUnit,
    IN MCD_FEC_TYPE fecCorrect,
    IN MCD_OP_MODE portMode
)
{

    MCD_U8      chnOffset;
    MCD_U16     mdioPort;
    MCD_BOOL    isMode10 = (portMode == MCD_MODE_P10L)? MCD_TRUE: MCD_FALSE;

    chnOffset = CHAN_IN_SLICE_NUM(channelUnit);

    mdioPort = pDev->firstMdioPort;

    /* Assert software reset for the channel*/
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Software_Reset(slice), chnOffset, 1, 1));

   /*set Global mode*/
    ATTEMPT(mcdGlobalModeSet(pDev, slice, chnOffset,  portMode));

   /* Reset Channel L1_0 PPM link-up threshold to 5*/
    if (channelUnit < 4)
    {
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (UMAC_GLBL_L1_1_B2B_PPM_Compensation_Ctrl_CH0(slice) + 4 * chnOffset), 4, 6, 5));
        if (isMode10) {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (UMAC_GLBL_L1_1_B2B_PPM_Compensation_Ctrl_CH0(slice) + 4 * chnOffset), 10, 6, 3));
        }
    }
    else
    {
        if ((channelUnit >= 4) && (channelUnit < 6))
        {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (UMAC_GLBL_L1_0_B2B_PPM_Compensation_Ctrl_CH0(slice) + 4 * chnOffset), 4, 6, 5));
            if (isMode10) {
                ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (UMAC_GLBL_L1_0_B2B_PPM_Compensation_Ctrl_CH0(slice)+ 4 * chnOffset), 10, 6, 3));
            }
        }
        /* L1_0_B2B CH2 & CH3 address are not in steps of 4 w.r.t CH1 */
        else if (channelUnit >= 6)
        {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (UMAC_GLBL_L1_0_B2B_PPM_Compensation_Ctrl_CH0(slice) + 4 * (chnOffset+1)), 4, 6, 5));
            if (isMode10) {
                ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (UMAC_GLBL_L1_0_B2B_PPM_Compensation_Ctrl_CH0(slice)+ 4 * (chnOffset+1)), 10, 6, 3));
            }
        }
    }

    ATTEMPT(mcdConfigurePcsEnChannelCommon(pDev, slice, channelUnit, chnOffset, mdioPort));
   /* Set Channel mode to 10G/25G*/
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Channel_Mode(slice), (chnOffset*2), 2, (isMode10)? UMAC_CHANNEL_MODE_10G: UMAC_CHANNEL_MODE_25G));

    ATTEMPT(mcdConfigurePcsCommon(pDev, slice, channelUnit, fecCorrect, MCD_BASE_R1, 1));
   return MCD_OK;
}


/* MCD_STATUS mcdConfigurePcs40g configure 40GRx mode on on unit */
MCD_STATUS mcdConfigurePcs40g
(
    IN MCD_DEV_PTR pDev,
    IN MCD_OP_MODE portMode,
    IN MCD_U16 slice,
    IN MCD_U16 channelUnit,
    IN MCD_CHANNEL_MODE_TYPE chanMode,
    IN MCD_FEC_TYPE fecCorrect
)
{

    MCD_U8       chnOffset;
    MCD_U32      ppmRegAdr;
    MCD_U16      mdioPort;

    chnOffset = CHAN_IN_SLICE_NUM(channelUnit);

    mdioPort = pDev->firstMdioPort;
    /* Assert software reset for the channel*/
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Software_Reset(slice),chnOffset, 1, 1));

    /* Set Global Mode */
    ATTEMPT(mcdGlobalModeSet(pDev, slice, chnOffset, portMode));

   /* Reset Channel L1_x PPM link-up threshold to 5*/
    if (channelUnit < 4)
        ppmRegAdr = UMAC_GLBL_L1_1_B2B_PPM_Compensation_Ctrl_CH0(slice);
    else
        ppmRegAdr = UMAC_GLBL_L1_0_B2B_PPM_Compensation_Ctrl_CH0(slice);

    if (fecCorrect == MCD_FC_FEC)
    {/* Set Channel L1_x PPM link-up threshold to 16*/
        if (channelUnit <= 5)
        {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (ppmRegAdr + 4 * chnOffset), 4, 6, 0x10));
        }
        /* L1_0_B2B CH2 & CH3 address are not in steps of 4 w.r.t CH1 */
        else if (channelUnit >= 6)
        {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (ppmRegAdr + 4 * (chnOffset+1)), 4, 6, 0x10));
        }
    }
    else
    {
        /* Reset Channel L1_x PPM link-up threshold to 5*/
        if (channelUnit <= 5)
        {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (ppmRegAdr + 4 * chnOffset), 4, 6, 5));
        }
        /* L1_0_B2B CH2 & CH3 address are not in steps of 4 w.r.t CH1 */
        else if (channelUnit >= 6)
        {
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (ppmRegAdr + 4 * (chnOffset+1)), 4, 6, 5));
        }
    }
    ATTEMPT(mcdConfigurePcsEnChannelCommon(pDev, slice, channelUnit, chnOffset, mdioPort));
    ATTEMPT(mcdConfigurePcsCommon(pDev, slice, channelUnit, fecCorrect, chanMode, 1));
   return MCD_OK;
}

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/* MCD_STATUS mcdConfigurePcs40gNewLs
   configure 40GR2 mode with lane remapping on on unit */
MCD_STATUS mcdConfigurePcs40gNewLs
(
    IN MCD_DEV_PTR pDev,
    IN MCD_OP_MODE portMode,
    IN MCD_U16 slice,
    IN MCD_U16 channelUnit,
    IN MCD_CHANNEL_MODE_TYPE chanMode,
    IN MCD_U16 laneRxDstArr[],
    IN MCD_U16 laneTxDstArr[],
    IN MCD_FEC_TYPE fecCorrect
)
{

    MCD_U8       chnOffset,i,laneNum;
    MCD_U32      ppmRegAdr;
    MCD_U16      mdioPort;
    MCD_U16    remapRegValue;
    chnOffset = CHAN_IN_SLICE_NUM(channelUnit);

    mdioPort = pDev->firstMdioPort;
    /* Assert software reset for the channel*/
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Software_Reset(slice),chnOffset, 1, 1));

    /* Set Global Mode */
    ATTEMPT(mcdGlobalModeSet(pDev, slice, chnOffset, portMode));

   /* Reset Channel L1_x PPM link-up threshold to 5*/
    if (channelUnit < 4)
        ppmRegAdr = UMAC_GLBL_L1_1_B2B_PPM_Compensation_Ctrl_CH0(slice);
    else
        ppmRegAdr = UMAC_GLBL_L1_0_B2B_PPM_Compensation_Ctrl_CH0(slice);

    if (fecCorrect == MCD_FC_FEC)
    {/* Set Channel L1_x PPM link-up threshold to 16*/
        if (channelUnit <= 5)
        {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (ppmRegAdr + 4 * chnOffset), 4, 6, 0x10));
        }
        /* L1_0_B2B CH2 & CH3 address are not in steps of 4 w.r.t CH1 */
        else if (channelUnit >= 6)
        {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (ppmRegAdr + 4 * (chnOffset+1)), 4, 6, 0x10));
        }
    }
    else
    {
        /* Reset Channel L1_x PPM link-up threshold to 5*/
        if (channelUnit <= 5)
        {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (ppmRegAdr + 4 * chnOffset), 4, 6, 5));
        }
        /* L1_0_B2B CH2 & CH3 address are not in steps of 4 w.r.t CH1 */
        else if (channelUnit >= 6)
        {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (ppmRegAdr + 4 * (chnOffset+1)), 4, 6, 5));
        }
    }

    /* Enable Channel */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Channel_Enable(slice),chnOffset, 1,  1));

    /* Enable Channel  RX MAC */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_Channel_MAC_Control(slice,channelUnit), 1, 1, 1));

   /* Set PMA mode */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_MCPCS_Ch_Mode(slice,channelUnit), 2, 4, chanMode));

    if (fecCorrect)
    {
        /* Set FEC mode to RS or FC  for the Channel -  bits 0-1 set to 1 or 2 */
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_MCPCS_Ch_Mode(slice,channelUnit), 0, 2, ~(fecCorrect & 3)));
        if (fecCorrect == MCD_FC_FEC)
        {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_MCPCS_Debug_Control1(slice,channelUnit), 14, 1, 1));
        }
    }
    else
    {
       /* Set FEC mode to none for Channel 0  bits 0-1 set to 0*/
       ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort,UMAC_MCPCS_Ch_Mode(slice,channelUnit), 0, 2, 0));
    }

     /* Rx lane remap*/
    remapRegValue = (laneRxDstArr[0]  & 3) | ((laneRxDstArr[1] & 3) << 3);
    /* find value for lane 2 and 3 - it shouldn be equal to already used values */
    laneNum = 2;
    for (i = 0; i < 4; i++)
    {
        if ((i != laneRxDstArr[0]) && (i != laneRxDstArr[1]))
        {
            remapRegValue |=  (i << (3 * laneNum));
            laneNum++;
        }
    }
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, mdioPort,UMAC_SERDESMUX_laneremaprx(slice),remapRegValue));

    /* TX lane remap*/
    remapRegValue = (laneTxDstArr[0]  & 3) | ((laneTxDstArr[1] & 3) << 3);
    /* find value for lane 2 and 3 - it shouldn be equal to already used values */
    laneNum = 2;
    for (i = 0; i < 4; i++)
    {
        if ((i != laneTxDstArr[0]) && ( i != laneTxDstArr[1]))
        {
            remapRegValue |=  (i << (3 * laneNum));
            laneNum++;
        }
    }
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, mdioPort,UMAC_SERDESMUX_laneremaptx(slice),remapRegValue));

    /*Remove software reset on the channel */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Software_Reset(slice), chnOffset, 1, 0));

   return MCD_OK;
}
#endif /*#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3*/

/* MCD_STATUS mcdConfigurePcs100gR4 configure 100GR4 mode on on unit */
MCD_STATUS mcdConfigurePcs100gR4
(
    IN MCD_DEV_PTR pDev,
    IN MCD_OP_MODE portMode,
    IN MCD_U16 slice,
    IN MCD_U16 channelUnit,
    IN MCD_FEC_TYPE fecCorrect
)
{
    MCD_U8       chnOffset;
    MCD_U32      ppmRegAdr;
    MCD_U16      mdioPort;

    chnOffset = CHAN_IN_SLICE_NUM(channelUnit);

    mdioPort = pDev->firstMdioPort;
    /* Assert software reset for the channel*/
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Software_Reset(slice),chnOffset, 1, 1));

    /* Set Global Mode */
    ATTEMPT(mcdGlobalModeSet(pDev, slice, chnOffset, portMode));

   /* Reset Channel L1_x PPM link-up threshold to 5*/
    if (channelUnit < 4)
        ppmRegAdr = UMAC_GLBL_L1_1_B2B_PPM_Compensation_Ctrl_CH0(slice);
    else
        ppmRegAdr = UMAC_GLBL_L1_0_B2B_PPM_Compensation_Ctrl_CH0(slice);

    /* Reset Channel 0 L1_x PPM link-up threshold to 5*/
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, (ppmRegAdr + 4 * chnOffset), 4, 6, 5));

    /* Reset Channel 1 L1_x PPM link-up threshold to 5*/
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, ((ppmRegAdr + 4) + 4 * chnOffset), 4, 6, 5));

    ATTEMPT(mcdConfigurePcsEnChannelCommon(pDev, slice, channelUnit, chnOffset, mdioPort));
#if 0
    /* Enable Channel 0*/
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Channel_Enable(slice), chnOffset, 1,  1));

    /*Enable Channel 0 RX MAC*/
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_Channel_MAC_Control(slice,channelUnit), 1, 1, 1));
#endif

    ATTEMPT(mcdConfigurePcsCommon(pDev, slice, channelUnit, fecCorrect, 5, 0));
#if 0
    /*Set PMA mode to R4 for Channel 0 */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_MCPCS_Ch_Mode(slice,channelUnit), 2, 4, 0x5));

    if (fecCorrect)
    {
        /* Set FEC mode to RS or FC  for Channel 0 bits 0-1 set to 1 or 2 */
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_MCPCS_Ch_Mode(slice,channelUnit), 0, 2, ~(fecCorrect & 3)));

    }
    else
    {
        /* Set FEC mode to none for Channel 0 bits 0-1 set to 0*/
       ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_MCPCS_Ch_Mode(slice,channelUnit), 0, 2, 0));
    }

    /*Remove software reset on the channel */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_GLBL_Software_Reset(slice), chnOffset, 1, 0));
#endif
   return MCD_OK;
}

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*mcd25gRsFecRegistersInit  init AMx registers to support 25 G RS FEC consortioum 1.6*/
static MCD_STATUS mcd25gRsFecRegistersInit
(
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 slice
)
{

    ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0 ,UMAC_MCPCS_Programmable_AM0_low (slice, 0), 0x68c1));
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0 ,UMAC_MCPCS_Programmable_AM0_high(slice, 0), 0x3321));
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0 ,UMAC_MCPCS_Programmable_AM1_low (slice, 0), 0xc4f0));
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0 ,UMAC_MCPCS_Programmable_AM1_high(slice, 0), 0x00e6));
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0 ,UMAC_MCPCS_Programmable_AM2_low (slice, 0), 0x65c5));
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0 ,UMAC_MCPCS_Programmable_AM2_high(slice, 0), 0x009b));
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0 ,UMAC_MCPCS_Programmable_AM3_low (slice, 0), 0x79a2));
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0 ,UMAC_MCPCS_Programmable_AM3_high(slice, 0), 0x003d));

    ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0 ,UMAC_MCPCS_Programmable_AM0_low (slice, 4), 0x68c1));
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0 ,UMAC_MCPCS_Programmable_AM0_high(slice, 4), 0x3321));
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0 ,UMAC_MCPCS_Programmable_AM1_low (slice, 4), 0xc4f0));
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0 ,UMAC_MCPCS_Programmable_AM1_high(slice, 4), 0x00e6));
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0 ,UMAC_MCPCS_Programmable_AM2_low (slice, 4), 0x65c5));
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0 ,UMAC_MCPCS_Programmable_AM2_high(slice, 4), 0x009b));
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0 ,UMAC_MCPCS_Programmable_AM3_low (slice, 4), 0x79a2));
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0 ,UMAC_MCPCS_Programmable_AM3_high(slice, 4), 0x003d));

    return MCD_OK;
}
/**
* @internal mcdRsFecConsortiumModeEnable function
* @endinternal
*
* @brief   enables RS FEC 1.6 consortium.
*
* @param[in] pDev                     - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] slice                    -  0..1
* @param[in] chan                     -  0..7
*
* @retval MCD_OK                   - on success
* @retval MCD_FAIL                 - on error
*/
static MCD_STATUS mcdRsFecConsortiumModeEnable
(
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 slice,
     IN MCD_U16 chan
)
{
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, 0, UMAC_MCPCS_Programmable_AM_ctrl(slice,chan), 0, 2, 3));

    return MCD_OK;
}

/**
* @internal mcd25gRsFecInit function
* @endinternal
*
* @brief   Init registers to support RS FEC 1.6 consortium.
*
* @param[in] pDev                     - pointer to MCD_DEV initialized by mcdInitDriver() call
*
* @retval MCD_OK                   - on success
* @retval MCD_FAIL                 - on error
*/
MCD_STATUS mcd25gRsFecInit
(
     IN MCD_DEV_PTR pDev
)
{
    MCD_U16 slice,chan;

    for (slice = 0; slice < MCD_MAX_SLICE_NUM; slice++)
    {   /*reset all slice channels*/
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, UMAC_GLBL_Software_Reset(slice), 0, 4, 0xF));
        for (chan = 0; chan < MCD_MAX_CHANNEL_NUM_PER_SLICE; chan++)
        {
            ATTEMPT(mcdRsFecConsortiumModeEnable(pDev, slice, chan));
            ATTEMPT(mcdRsFecConsortiumModeEnable(pDev, slice, (chan + 4)));
        }

        ATTEMPT(mcd25gRsFecRegistersInit(pDev, slice));

        for (chan = 0; chan < MCD_MAX_CHANNEL_NUM_PER_SLICE; chan++)
        {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, 0, UMAC_FECRS_ieeecfg(slice,chan), 11, 1, 1));
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, 0, UMAC_FECRS_ieeecfg(slice,(chan + 4)), 11, 1, 1));

        }
        /*unreset all slice channels*/
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, UMAC_GLBL_Software_Reset(slice), 0, 4, 0x0));
    }
        return MCD_OK;
}

MCD_STATUS mcdOneSideSetMode
(
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 mdioPort,
     IN MCD_OP_MODE portMode,
     IN MCD_U16 host_or_line,
     IN MCD_FEC_TYPE fecCorrect,
     IN MCD_MODE_CONFIG_PARAM_PTR configPtr
)
{
    MCD_U16 slice,chan,serdesNum, i;
    MCD_NO_PPM_MODE noPpmMode;
    MCD_BOOL noPpmEnable = MCD_FALSE;

    MCD_BOOL retimerMode = MCD_FALSE;
    MCD_U16  lineSerdesSpeed =0;
    MCD_U16  hostSerdesSpeed = 0;
    MCD_U16  lineSerdesBitmap = 0;
    MCD_U16  hostSerdesBitmap = 0;
    MCD_U16  hostLanesNum = 0, lineLanesNum;
    MCD_FEC_TYPE_GET fecConfig;
    MCD_REF_CLK_SEL refClkSel = MCD_PRIMARY_CLK;
    MCD_REF_CLK_DIV refClkDiv = MCD_REF_CLK_NO_DIV;
    MCD_CTLE_BIAS_VAL  hostCtleBiasVal, lineCtleBiasVal;
    MCD_BOOL laneSteeringEnable = MCD_FALSE;
    MCD_MASTER_SLICE masterSlice = MCD_DUAL_SLICE;
    MCD_U16 otherMdioPort = 0;
    MCD_U16 otherSlice = 0;
    MCD_BOOL slavePortDisabled = MCD_FALSE;
    MCD_U16 firstLpbPort = 0;
    MCD_U16 secLpbPort =0;
    MCD_CONFIDENCE_INTERVAL_PARAMS_OVERRIDE  confidenceInterval;
    MCD_LINE_SIDE_EO_TH_OVERRIDE             eoThreshold;
    MCD_SERDES_SPEED  baudrate = MCD_SPEED_NA;

    /* fill confidince interval and EO data base */
    confidenceInterval.lfLowThreshold = pDev->calibrationCfg[mdioPort].lfLowThreshold;
    confidenceInterval.lfHighThreshold = pDev->calibrationCfg[mdioPort].lfHighThreshold;
    confidenceInterval.hfThreshold = pDev->calibrationCfg[mdioPort].hfThreshold;
    eoThreshold.minEyeThreshold = pDev->calibrationCfg[mdioPort].minEyeThreshold;
    eoThreshold.maxEyeThreshold = pDev->calibrationCfg[mdioPort].maxEyeThreshold;

    pDev->calibrationCfg[mdioPort].calibrationAlgorithm = configPtr->calibrationAlgo;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdOneSideSetMode: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdOneSideSetMode: incorrect port selection: %u\n", mdioPort);
        return MCD_FAIL;
    }

    MCD_FEC_TYPE_GET_MAC(fecCorrect,fecConfig);

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;

    chan = CHAN_IN_SLICE_NUM(mdioPort);

    laneSteeringEnable = pDev->laneSteeringCfg.laneSteeringEnable;
    if (laneSteeringEnable)
    {
        masterSlice = pDev->laneSteeringCfg.masterSlice;
        if (pDev->laneSteeringCfg.singlePortEnable[mdioPort])
        {
            if (pDev->laneSteeringCfg.externalLpPort[mdioPort] == MCD_LANE_STEERING_NO_LPB)
            {
                slavePortDisabled = MCD_TRUE;
            }
            else
            {
                firstLpbPort = pDev->laneSteeringCfg.externalLpPort[mdioPort];
                secLpbPort = pDev->laneSteeringCfg.internalLpPort[mdioPort];
            }
        }
        else
        {
            otherMdioPort = ((masterSlice == MCD_SLICE0) ? (mdioPort+4) : (mdioPort-4));
            otherSlice = (masterSlice == MCD_SLICE0 ? 1 : 0);
        }
    }
    noPpmMode = configPtr->noPpmMode;
    noPpmEnable = ((noPpmMode > MCD_NO_PPM_OFF_MODE) ? MCD_TRUE : MCD_FALSE);

    if (configPtr->electricalParamsPtr != NULL)
    {
        mcdSetSetSerdesElectricalParametersDB(mdioPort,portMode,configPtr->electricalParamsPtr);
        if (laneSteeringEnable && (masterSlice < MCD_DUAL_SLICE))
        {
            if (!slavePortDisabled)
            {
                if (pDev->laneSteeringCfg.singlePortEnable[mdioPort])
                {
                    mcdSetSetSerdesElectricalParametersDB(firstLpbPort, portMode, configPtr->electricalParamsPtr);
                    mcdSetSetSerdesElectricalParametersDB(secLpbPort, portMode, configPtr->electricalParamsPtr);
                }
                else
                {
                    mcdSetSetSerdesElectricalParametersDB(otherMdioPort,portMode,configPtr->electricalParamsPtr);
                }
            }
        }
    }
    else
    {
        mcdSetSetSerdesDefaultElectricalParameters(mdioPort, portMode);
        if (laneSteeringEnable && (masterSlice < MCD_DUAL_SLICE))
        {
            if (!slavePortDisabled)
            {
                if (pDev->laneSteeringCfg.singlePortEnable[mdioPort])
                {
                    mcdSetSetSerdesDefaultElectricalParameters(firstLpbPort, portMode);
                    mcdSetSetSerdesDefaultElectricalParameters(secLpbPort, portMode);
                }
                else
                {
                    mcdSetSetSerdesDefaultElectricalParameters(otherMdioPort, portMode);
                }
            }
        }
    }

    if (configPtr->ctleParamsPtr != NULL)
    {
        mcdSetSerdesCtleParametersDB(mdioPort,portMode,configPtr->ctleParamsPtr);
        if (laneSteeringEnable && (masterSlice < MCD_DUAL_SLICE))
        {
            if (!slavePortDisabled)
            {
                if (pDev->laneSteeringCfg.singlePortEnable[mdioPort])
                {
                    mcdSetSerdesCtleParametersDB(firstLpbPort, portMode, configPtr->ctleParamsPtr);
                    mcdSetSerdesCtleParametersDB(secLpbPort, portMode, configPtr->ctleParamsPtr);
                }
                else
                {
                    mcdSetSerdesCtleParametersDB(otherMdioPort,portMode,configPtr->ctleParamsPtr);
                }
            }
        }
    }
    else
    {
        mcdSetSerdesDefaultCtleParameters(mdioPort, portMode);
        if (laneSteeringEnable && (masterSlice < MCD_DUAL_SLICE))
        {
            if (!slavePortDisabled)
            {
                if (pDev->laneSteeringCfg.singlePortEnable[mdioPort])
                {
                    mcdSetSerdesDefaultCtleParameters(firstLpbPort, portMode);
                    mcdSetSerdesDefaultCtleParameters(secLpbPort, portMode);
                }
                else
                {
                    mcdSetSerdesDefaultCtleParameters(otherMdioPort, portMode);
                }
            }
        }
    }

    if (host_or_line == MCD_HOST_SIDE)
    {
        hostCtleBiasVal = configPtr->ctleBiasParams.host;
        hostLanesNum = mcdPortModeGetLanesNum(portMode, MCD_HOST_SIDE);
        for (serdesNum = chan; serdesNum< chan+hostLanesNum; serdesNum++)
        {
            ATTEMPT(mcdSerdesCtleBiasUpdateDB(pDev, MCD_SERDES_NUM(serdesNum, slice), (MCD_U8)hostCtleBiasVal, MCD_HOST_SIDE))
             if (laneSteeringEnable && (masterSlice < MCD_DUAL_SLICE))
             {
                 if (pDev->laneSteeringCfg.singlePortEnable[mdioPort])
                 {
                     if (!slavePortDisabled)
                     {
                            ATTEMPT(mcdSerdesCtleBiasUpdateDB(pDev, pDev->laneSteeringCfg.externalLpSerdes[mdioPort], (MCD_U8)hostCtleBiasVal, MCD_HOST_SIDE));
                            ATTEMPT(mcdSerdesCtleBiasUpdateDB(pDev, pDev->laneSteeringCfg.internalLpSerdes[mdioPort], (MCD_U8)hostCtleBiasVal, MCD_HOST_SIDE));
                     }
                 }
                 else
                 {
                     ATTEMPT(mcdSerdesCtleBiasUpdateDB(pDev, MCD_SERDES_NUM(serdesNum, otherSlice), (MCD_U8)hostCtleBiasVal, MCD_HOST_SIDE));
                 }
             }
        }
    }
    else
    {
        lineCtleBiasVal = configPtr->ctleBiasParams.line;
        lineLanesNum = mcdPortModeGetLanesNum(portMode, MCD_LINE_SIDE);
        for (serdesNum = chan; serdesNum< chan+lineLanesNum; serdesNum++)
        {
            ATTEMPT(mcdSerdesCtleBiasUpdateDB(pDev, MCD_SERDES_NUM(serdesNum,slice), (MCD_U8)lineCtleBiasVal, MCD_LINE_SIDE))
        }
    }

    switch(portMode)
    {
        case MCD_MODE_P100L:
        case MCD_MODE_P100S:
        case MCD_MODE_P100C:
        case MCD_MODE_P100K:
            if (chan != 0) /* 100G  only on chan 0*/
            {
                MCD_DBG_ERROR("mcdOneSideSetMode: wrong channel number %u\n", chan);
                return MCD_FAIL;
            }
            if (host_or_line == MCD_HOST_SIDE)
            {
                hostSerdesBitmap = (0x0F << (slice * 4));
                lineSerdesBitmap = 0;
                retimerMode      = 0;
                lineSerdesSpeed  = MCD_25_78125G;
                hostSerdesSpeed  = MCD_25_78125G;

                /* power up 4 Host serdeses */
                for ( serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER; serdesNum < MCD_HOST_SIDE_START_SERDES_NUMBER + 4; serdesNum++)
                {
                    ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE, MCD_25_78125G, noPpmEnable, (MCD_U32)refClkSel, (MCD_U32)refClkDiv));
                    ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE));
                }
                /* power up 4 line serdeses */
                ATTEMPT(mcdConfigurePcs100gR4(pDev, portMode, slice, chan, fecConfig.hostFec));
                if (laneSteeringEnable)
                {
                    ATTEMPT(mcdLaneSteeringOtherSideCfg(pDev, mdioPort, portMode, masterSlice, MCD_25_78125G));
                    mcdWrapperMsSleep(50);
                }
            }
            else  if (host_or_line == MCD_LINE_SIDE)
            {
                for ( serdesNum = chan ; serdesNum < 4; serdesNum++)
                {
                    ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE, MCD_25_78125G, MCD_FALSE, (MCD_U32)refClkSel, (MCD_U32)refClkDiv));
                    ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE));
                }
                ATTEMPT(mcdConfigurePcs100gR4(pDev, portMode, slice, (chan + 4), fecConfig.lineFec));
            }
            break;
        case MCD_MODE_P40L:
        case MCD_MODE_P40S:
        case MCD_MODE_P40C:
        case MCD_MODE_P40K:
            if (chan != 0) /* only on chan 0*/
            {
                MCD_DBG_ERROR("mcdOneSideSetMode: wrong channel number %u\n", chan);
                return MCD_FAIL;
            }
            if (host_or_line == MCD_HOST_SIDE)
            {
                hostSerdesBitmap = (0x0F << (slice * 4));
                lineSerdesBitmap = 0;
                retimerMode      = 0;
                lineSerdesSpeed  = MCD_10_3125G;
                hostSerdesSpeed  = MCD_10_3125G;
            /* power up 4 Host serdeses */
                for ( serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER; serdesNum < MCD_HOST_SIDE_START_SERDES_NUMBER + 4; serdesNum++)
                {
                    ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE, MCD_10_3125G, noPpmEnable, (MCD_U32)refClkSel, (MCD_U32)refClkDiv));
                    ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE));
                }
                ATTEMPT(mcdConfigurePcs40g(pDev, portMode, slice, chan, MCD_BASE_R4, fecConfig.hostFec));
                if (laneSteeringEnable)
                {
                    ATTEMPT(mcdLaneSteeringOtherSideCfg(pDev, mdioPort, portMode, masterSlice, MCD_10_3125G));
                    mcdWrapperMsSleep(50);
                }
            }
            else if (host_or_line == MCD_LINE_SIDE)    /* power up 4 Line serdeses */
            {

                for ( serdesNum = 0; serdesNum < 4; serdesNum++)
                {
                    ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE, MCD_10_3125G, MCD_FALSE, (MCD_U32)refClkSel, (MCD_U32)refClkDiv));
                    ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE));
                }
                ATTEMPT(mcdConfigurePcs40g(pDev, portMode, slice, (chan + 4), MCD_BASE_R4, fecConfig.lineFec));
            }

            break;
        case MCD_MODE_P20L:
        case MCD_MODE_P20S:
        case MCD_MODE_P25L:
        case MCD_MODE_P25S:
            if ((portMode == MCD_MODE_P25L) || (portMode == MCD_MODE_P25S))
            {
                baudrate = MCD_25_78125G;
            }
            else /* Means we support 20G-R1 */
            {
                baudrate = MCD_20_625G;
            }

            if (host_or_line == MCD_HOST_SIDE)
            {
                hostSerdesBitmap = (0x01 << ((slice * 4) + chan));
                retimerMode      = 0;
                lineSerdesSpeed  = baudrate;
                hostSerdesSpeed  = baudrate;
                lineSerdesBitmap = 0;

                if ((pDev->laneSteeringCfg.singlePortEnable[mdioPort]) && (laneSteeringEnable))
                {
                    ATTEMPT(mcdSerdesRxPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, baudrate, noPpmEnable,(MCD_U32)refClkSel,(MCD_U32)refClkDiv));
                    ATTEMPT(mcdSerdesTxPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, baudrate, noPpmEnable,(MCD_U32)refClkSel,(MCD_U32)refClkDiv));
                }
                else
                {
                    ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, baudrate, noPpmEnable, (MCD_U32)refClkSel, (MCD_U32)refClkDiv));
                }
                ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE));
                ATTEMPT(mcdConfigurePcs10_25gR1(pDev, slice, chan, fecConfig.hostFec, MCD_MODE_P25L));
                if (laneSteeringEnable)
                {
                    ATTEMPT(mcdLaneSteeringOtherSideCfg(pDev, mdioPort, portMode, masterSlice, baudrate));
                    mcdWrapperMsSleep(50);
                }
            }
            else if (host_or_line == MCD_LINE_SIDE)/*configure Line side */
            {
                ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(chan, slice), MCD_TRUE, baudrate, MCD_FALSE, (MCD_U32)refClkSel, (MCD_U32)refClkDiv));
                ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(chan, slice), MCD_TRUE));
                ATTEMPT(mcdConfigurePcs10_25gR1(pDev, slice, chan + 4, fecConfig.lineFec, MCD_MODE_P25L));
            }
            break;
        case MCD_MODE_P10L:
        case MCD_MODE_P10S:
            if (host_or_line == MCD_HOST_SIDE)
            {
                hostSerdesBitmap = (0x01 << ((slice * 4) + chan));
                retimerMode      = 0;
                lineSerdesSpeed  = MCD_10_3125G;
                hostSerdesSpeed  = MCD_10_3125G;
                lineSerdesBitmap = 0;

                if ((pDev->laneSteeringCfg.singlePortEnable[mdioPort]) && (laneSteeringEnable))
                {
                    ATTEMPT(mcdSerdesRxPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, MCD_10_3125G, noPpmEnable,(MCD_U32)refClkSel,(MCD_U32)refClkDiv));
                    ATTEMPT(mcdSerdesTxPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, MCD_10_3125G, noPpmEnable,(MCD_U32)refClkSel,(MCD_U32)refClkDiv));
                }
                else
                {

                    ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, MCD_10_3125G, noPpmEnable, (MCD_U32)refClkSel, (MCD_U32)refClkDiv));
                }
                ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan),slice), MCD_TRUE));
                ATTEMPT(mcdConfigurePcs10_25gR1(pDev, slice, chan, fecConfig.hostFec, MCD_MODE_P10L));
                /* configure Asic side*/
                if (laneSteeringEnable)
                {
                    ATTEMPT(mcdLaneSteeringOtherSideCfg(pDev, mdioPort, portMode, masterSlice, MCD_10_3125G));
                    mcdWrapperMsSleep(50);
                }
            }
            else if (host_or_line == MCD_LINE_SIDE)
            {
                ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(chan, slice), MCD_TRUE, MCD_10_3125G, MCD_FALSE, (MCD_U32)refClkSel, (MCD_U32)refClkDiv));
                ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(chan,slice), MCD_TRUE));
                /*configure Line side */
                ATTEMPT(mcdConfigurePcs10_25gR1(pDev, slice, (chan + 4), fecConfig.lineFec, MCD_MODE_P10L));
            }
            break;
        case MCD_MODE_P1:
            if (host_or_line == MCD_HOST_SIDE)
            {
                if ((pDev->laneSteeringCfg.singlePortEnable[mdioPort]) && (laneSteeringEnable))
                {
                    ATTEMPT(mcdSerdesRxPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, MCD_1_25G, noPpmEnable,(MCD_U32)refClkSel,(MCD_U32)refClkDiv));
                    ATTEMPT(mcdSerdesTxPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, MCD_1_25G, noPpmEnable,(MCD_U32)refClkSel,(MCD_U32)refClkDiv));
                }
                else
                {
                    ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, MCD_1_25G, noPpmEnable, (MCD_U32)refClkSel, (MCD_U32)refClkDiv));
                }
                ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan),slice), MCD_TRUE));
                /* configure Asic side*/
                ATTEMPT(mcdConfigurePcs1gR1(pDev, slice, chan, 1/*BASEx*/, MCD_FALSE));
           }
            else if (host_or_line == MCD_LINE_SIDE)
            {
                ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(chan, slice), MCD_TRUE, MCD_1_25G, MCD_FALSE, (MCD_U32)refClkSel, (MCD_U32)refClkDiv));
                ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(chan,slice), MCD_TRUE));
                /*configure Line side */
                ATTEMPT(mcdConfigurePcs1gR1(pDev, slice, (chan + 4), 1/*BASEX*/, MCD_FALSE));
            }
            break;
        case MCD_MODE_P1_BaseX_SGMII:
            if (host_or_line == MCD_HOST_SIDE)
            {
                ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, MCD_1_25G, noPpmEnable, (MCD_U32)refClkSel, (MCD_U32)refClkDiv));
                ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan),slice), MCD_TRUE));
                /* configure Asic side*/
                ATTEMPT(mcdConfigurePcs1gR1(pDev, slice, chan, 0/*SGMII*/, MCD_FALSE));
            }
            break;

        case MCD_MODE_R100C:
            if (chan != 0) /* 100G  only on chan 0*/
            {
                MCD_DBG_ERROR("mcdSetModeImplement: wrong channel number %u\n", chan);
                return MCD_FAIL;
            }
            /* power up 4 Host serdeses */
            if (host_or_line == MCD_HOST_SIDE)
            {
                hostSerdesBitmap = (0x0F << (slice * 4));
                lineSerdesBitmap = 0;
                lineSerdesSpeed  = MCD_25_78125G;
                hostSerdesSpeed  = MCD_25_78125G;
                retimerMode      = 1;
                for ( i=0,serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER; serdesNum < MCD_HOST_SIDE_START_SERDES_NUMBER + 4; serdesNum++,i++)
                {
                    ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePreSet(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_25_78125G));
                    pDev->portConfig[mdioPort + i].portMode = portMode;
                }
                for ( serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER; serdesNum < MCD_HOST_SIDE_START_SERDES_NUMBER + 4; serdesNum++)
                {
                    ATTEMPT(mcdSerdesResetImpl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_FALSE, MCD_TRUE, MCD_FALSE));
                }
            }
            break;
        case MCD_MODE_R40C:
            if (chan != 0)
            {
                MCD_DBG_ERROR("mcdSetModeImplement: wrong channel number %u\n", chan);
                return MCD_FAIL;
            }
            if (host_or_line == MCD_HOST_SIDE)
            {
                hostSerdesBitmap = (0x0F << (slice * 4));
                lineSerdesBitmap = 0;
                lineSerdesSpeed  = MCD_10_3125G;
                hostSerdesSpeed  = MCD_10_3125G;
                retimerMode      = 1;
                for ( i=0,serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER; serdesNum < MCD_HOST_SIDE_START_SERDES_NUMBER + 4; serdesNum++,i++)
                {
                    ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePreSet(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_10_3125G));
                    pDev->portConfig[mdioPort + i].portMode = portMode;
                }
                for (serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER; serdesNum < MCD_HOST_SIDE_START_SERDES_NUMBER + 4; serdesNum++)
                {
                    ATTEMPT(mcdSerdesResetImpl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_FALSE, MCD_TRUE, MCD_FALSE));
                }
            }
            break;
        case MCD_MODE_R25C:
            if (host_or_line == MCD_HOST_SIDE)
            {
                hostSerdesBitmap = (0x01 << ((slice * 4) + chan));
                lineSerdesSpeed  = MCD_25_78125G;
                hostSerdesSpeed  = MCD_25_78125G;
                lineSerdesBitmap = 0;
                retimerMode      = 1;
                serdesNum = MCD_SERDES_NUM((chan + MCD_HOST_SIDE_START_SERDES_NUMBER),slice);
                ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePreSet(pDev, serdesNum, MCD_25_78125G));
                pDev->portConfig[mdioPort].portMode = portMode;
                ATTEMPT(mcdSerdesResetImpl(pDev, serdesNum, MCD_FALSE, MCD_TRUE, MCD_FALSE));
            }
            break;
        case MCD_MODE_R10K:
            if (host_or_line == MCD_HOST_SIDE)
            {
                hostSerdesBitmap = (0x01 << ((slice * 4) + chan));
                lineSerdesSpeed  = MCD_10_3125G;
                hostSerdesSpeed  = MCD_10_3125G;
                lineSerdesBitmap = 0;
                retimerMode      = 1;
                serdesNum = MCD_SERDES_NUM((chan + MCD_HOST_SIDE_START_SERDES_NUMBER),slice);
                ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePreSet(pDev, serdesNum, MCD_10_3125G));
                pDev->portConfig[mdioPort].portMode = portMode;
               ATTEMPT(mcdSerdesResetImpl(pDev, serdesNum, MCD_FALSE, MCD_TRUE, MCD_FALSE));
            }
            break;
        case MCD_MODE_G21SK:
            if ((chan != 0) && (chan != 2))
            {
                MCD_DBG_ERROR("mcdSetModeImplement: wrong channel number %u\n", chan);
                return MCD_FAIL;
            }
            if (host_or_line == MCD_HOST_SIDE)
            {
                hostSerdesBitmap = (0x03 << ((slice * 4)+ chan));
                lineSerdesBitmap = 0;
                retimerMode      = 0;
                lineSerdesSpeed  = MCD_10_3125G;
                hostSerdesSpeed  = MCD_20_625G;
                if (laneSteeringEnable)
                {
                    for ( serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER + chan; serdesNum < MCD_HOST_SIDE_START_SERDES_NUMBER + chan + 4; serdesNum++)
                    {
                        /* power up 4 Host serdeses */
                        ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE, MCD_20_625G, noPpmEnable, (MCD_U32)refClkSel, (MCD_U32)refClkDiv));
                        ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE));
                    }
                }
                else
                {
                    /* power up 2 Host serdeses */
                    for ( serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER + chan; serdesNum < MCD_HOST_SIDE_START_SERDES_NUMBER + chan + 2; serdesNum++)
                    {
                        ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE, MCD_20_625G, noPpmEnable, (MCD_U32)refClkSel, (MCD_U32)refClkDiv));
                        ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE));
                    }
                }
                ATTEMPT(mcdConfigurePcs40g(pDev, portMode, slice, chan, MCD_BASE_R2, fecConfig.hostFec));
            }
            break;
        case MCD_MODE_P50R2L:
        case MCD_MODE_P50R2S:
            if ((chan != 0) && (chan != 2))
            {
                MCD_DBG_ERROR("mcdSetModeImplement: wrong channel number %u\n", chan);
                return MCD_FAIL;
            }
            if (host_or_line == MCD_HOST_SIDE)
            {
                hostSerdesBitmap = (0x03 << ((slice * 4)+ chan));
                lineSerdesBitmap = 0;
                retimerMode      = 0;
                lineSerdesSpeed  = MCD_25_78125G;
                hostSerdesSpeed  = MCD_25_78125G;
                /* power up 4 Host serdeses */
                for ( serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER + chan; serdesNum < MCD_HOST_SIDE_START_SERDES_NUMBER + chan + 2; serdesNum++)
                {
                    ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE, MCD_25_78125G, noPpmEnable, (MCD_U32)refClkSel, (MCD_U32)refClkDiv));
                    ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE));
                }
                /* configure Asic side*/
                ATTEMPT(mcdConfigurePcs40g(pDev, portMode, slice, chan, MCD_BASE_R2, fecConfig.hostFec));
            }
            break;
        default:
            MCD_DBG_ERROR("mcdOneSideSetMode: incorrect mode selection: %u\n", portMode);
            return MCD_FAIL;
    }

    if ((host_or_line == MCD_HOST_SIDE) && (noPpmEnable) && (!retimerMode))
    {
        /* power up  Host serdeses */
        for ( serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER + chan; serdesNum < (MCD_HOST_SIDE_START_SERDES_NUMBER + chan + hostLanesNum); serdesNum++)
        {
            ATTEMPT(mcdSerdesNoPpmModeSet(pDev, MCD_SERDES_NUM(serdesNum, slice), hostSerdesSpeed, (MCD_U32)chan, slice, MCD_TRUE));
        }
        for (i = 0; i < hostLanesNum; i++)
        {
            pDev->portConfig[mdioPort + i].noPpmMode = noPpmMode;
        }
        mcdWrapperMsSleep(PRV_MCD_DELAY_RETIMER_CLOCK_SWITCH);
    }

    /* fec was configured in mcdSetModeSelectionExt function*/
    /*pDev->portConfig[mdioPort].fecCorrect = fecCorrect;*/

    pDev->portConfig[mdioPort].autoNegAdvSpeed = 0;
    pDev->portConfig[mdioPort].autoNegAcquSpeed = 0;
        /* start ICAL on all serdes lanes of PCS mode port */

    if (laneSteeringEnable)
    {
        /* Run special Rx training for lane steering mode */
        if (pDev->laneSteeringCfg.singlePortEnable[mdioPort])
        {
            ATTEMPT(mcdLaneSteeringSingleModeTune(pDev, mdioPort, masterSlice));
        }
        else
        {
            ATTEMPT(mcdLaneSteeringAutoTuneStart(pDev, slice, masterSlice));
        }
    }
    else
    {
        ATTEMPT(mcdPortSerdesDfeConfig_noSignalCheck(
            pDev, mdioPort, MCD_DFE_ICAL,
            retimerMode,
            MCD_TRUE /*configIfPcsMode*/,
            MCD_TRUE /*configHostSide*/,
            MCD_FALSE /*configLineSide*/));

        if (retimerMode)
        {
            mcdWrapperMsSleep(50);
        }
        ATTEMPT(mcdPortPollingLinkStatusStartIpc(pDev, mdioPort, retimerMode, retimerMode,lineSerdesSpeed,
                                                 hostSerdesSpeed,lineSerdesBitmap, hostSerdesBitmap, 0 /* noPpmMode disabled */, (MCD_U8)0 /* normal Rx Training */,
                                                 pDev->calibrationCfg[mdioPort].calibrationAlgorithm,
                                                 &confidenceInterval, &eoThreshold));
    }

    return MCD_OK;
}


MCD_STATUS mcdSetHostSideRetimerMode
(
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 mdioPort,
     IN MCD_U32 laneSpeed,
     IN MCD_U32 numOfActLanes
)
{
    MCD_U16 slice,chan,i;
    MCD_U8 serdesNum;
    MCD_REF_CLK_SEL refClkSel = MCD_PRIMARY_CLK;
    MCD_REF_CLK_DIV refClkDiv = MCD_REF_CLK_NO_DIV;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdSetHostSideRetimerMode: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSetHostSideRetimerMode: incorrect port selection: %u\n", mdioPort);
        return MCD_FAIL;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;

    chan = CHAN_IN_SLICE_NUM(mdioPort);
    /* power up 4 Host serdeses */
    for ( i = MCD_HOST_SIDE_START_SERDES_NUMBER; i < numOfActLanes + MCD_HOST_SIDE_START_SERDES_NUMBER; i++)
    {
        serdesNum = MCD_SERDES_NUM((i + chan) ,slice);
        ATTEMPT(mcdSerdesPowerCtrl(pDev, serdesNum, MCD_TRUE, laneSpeed, MCD_FALSE, (MCD_U32)refClkSel, (MCD_U32)refClkDiv));
        ATTEMPT(mcdSerdesTxEnable(pDev, serdesNum, MCD_TRUE));
        ATTEMPT(mcdSerdesEnhanceTune(pDev, &serdesNum, 1, 0, 15));
    }
    return MCD_OK;
}
#endif /*#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3 */

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************
MCD_STATUS mcdPortPowerHwResetTimeout
    Power down and Reset mdioPort wait time
*******************************************************************/
 MCD_STATUS mcdPortPowerHwResetTimeout
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 timeoutMs
 )
{
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdPortPowerHwResetWait: incorrect mdioPort selection: %u\n", mdioPort);
        return MCD_FAIL;
    }

    return MCD_NOT_IMPLEMENTED; /* timed out without becoming ready */
}

/*******************************************************************
 MCD_STATUS mcdPortPowerHwReset
   Power down and reset mdioPort on both the host and line side
*******************************************************************/
MCD_STATUS mcdPortPowerHwReset
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort
)
{
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdPortPowerHwReset: incorrect mdioPort selection: %u\n", mdioPort);
        return MCD_FAIL;
    }

    return MCD_NOT_IMPLEMENTED;
}
#endif

/**
* @internal mcdPortBuildLanesArray function
* @endinternal
*
* @brief   build an array of active SerDes lanes per side
*
* @param[in] pDev                   - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] portMode               - port mode.
* @param[in] host_or_line           - side.
* @param[out] serdesArr             - array of active lanes.
*
* @retval MCD_OK                    - on success.
* @retval MCD_FAIL                  - on failure
*
*/
MCD_STATUS mcdPortBuildLanesArray
(
    IN  MCD_U16     mdioPort,
    IN  MCD_OP_MODE portMode,
    IN  MCD_U16 host_or_line,
    OUT MCD_U32 *serdesArr
)
{
    MCD_U32 laneNum;
    MCD_U32 slice;
    MCD_U32 chan;
    MCD_U32 activeChan;
    MCD_U32 numOfActiveLanes;
    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan = CHAN_IN_SLICE_NUM(mdioPort);

    switch (portMode)
    {
        case MCD_MODE_P100_40_C:
        case MCD_MODE_P100L:
        case MCD_MODE_P100S:
        case MCD_MODE_P100C:
        case MCD_MODE_P100K:
        case MCD_MODE_P40L:
        case MCD_MODE_P40S:
        case MCD_MODE_P40C:
        case MCD_MODE_P40K:
        case MCD_MODE_P100_40_K:
        case MCD_MODE_R100L:
        case MCD_MODE_R100C:
        case MCD_MODE_R40L:
        case MCD_MODE_R40C:
            numOfActiveLanes = 4;
            activeChan = 0;
            break;
        case MCD_MODE_R25L:
        case MCD_MODE_R25C:
        case MCD_MODE_R10L:
        case MCD_MODE_R10K:
        case MCD_MODE_R1L:
        case MCD_MODE_R1C:
        case MCD_MODE_P25L:
        case MCD_MODE_P25S:
        case MCD_MODE_P20L:
        case MCD_MODE_P20S:
        case MCD_MODE_P10L:
        case MCD_MODE_P10S:
        case MCD_MODE_P2_5:
        case MCD_MODE_P2_5S:
        case MCD_MODE_P1:
        case MCD_MODE_P1_SGMII:
        case MCD_MODE_P1_BaseX_SGMII:
            numOfActiveLanes = 1;
            activeChan = chan;
            break;
        case MCD_MODE_P50R2L:
        case MCD_MODE_P50R2S:
        case MCD_MODE_P40R2L:
        case MCD_MODE_P40R2S:
            numOfActiveLanes = 2;
            activeChan = (chan & 0x02);
            break;
        case MCD_MODE_G21L:
        case MCD_MODE_G21SK:
            numOfActiveLanes = ((host_or_line == MCD_HOST_SIDE) ? 2 : 4);
            activeChan = ((host_or_line == MCD_HOST_SIDE) ? (chan & 0x02) : 0);
            break;
        default:
            MCD_DBG_ERROR("mcdPortBuildLanesArray: port mode is invalid\n");
            return MCD_FAIL;
    }

        for (laneNum=0; laneNum < numOfActiveLanes; laneNum++)
        {
            if (host_or_line == MCD_HOST_SIDE)
            {
                serdesArr[laneNum] =  MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + activeChan + laneNum), slice);
            }
            else /* MCD_LINE_SIDE */
            {
                serdesArr[laneNum] =  MCD_SERDES_NUM((activeChan + laneNum), slice);
            }
        }

        return MCD_OK;
}

/*******************************************************************
 MCD_STATUS mcdPortModeGetLanesNum
   returns number of lanes used by port mode (0 on wrong params).
*******************************************************************/
MCD_U16 mcdPortModeGetLanesNum
(
    IN MCD_OP_MODE portMode,
    IN MCD_U16 host_or_line
)
{
    MCD_U16 hostLanes = 0;
    MCD_U16 lineLanes = 0;

    if ((host_or_line != MCD_HOST_SIDE) && (host_or_line != MCD_LINE_SIDE))
    {
        MCD_DBG_ERROR("mcdPortModeGetLanesNum: host_or_line is invalid\n");
        return 0;
    }

    switch (portMode)
    {
        case MCD_MODE_P100_40_C:
        case MCD_MODE_P100L:
        case MCD_MODE_P100S:
        case MCD_MODE_P100C:
        case MCD_MODE_P100K:
        case MCD_MODE_P40L:
        case MCD_MODE_P40S:
        case MCD_MODE_P40C:
        case MCD_MODE_P40K:
        case MCD_MODE_P100_40_K:
        case MCD_MODE_R100L:
        case MCD_MODE_R100C:
        case MCD_MODE_R40L:
        case MCD_MODE_R40C:
            hostLanes = 4; lineLanes = 4;
            break;
        case MCD_MODE_R25L:
        case MCD_MODE_R25C:

        case MCD_MODE_R10L:
        case MCD_MODE_R10K:
        case MCD_MODE_R1L:
        case MCD_MODE_R1C:

        case MCD_MODE_P20L:
        case MCD_MODE_P20S:
        case MCD_MODE_P25L:
        case MCD_MODE_P25S:
        case MCD_MODE_P10L:
        case MCD_MODE_P10S:
        case MCD_MODE_P2_5:
        case MCD_MODE_P2_5S:
        case MCD_MODE_P1:
        case MCD_MODE_P1_SGMII:
        case MCD_MODE_P1_BaseX_SGMII:
            hostLanes = 1; lineLanes = 1;
            break;
        case MCD_MODE_P50R2L:
        case MCD_MODE_P50R2S:
        case MCD_MODE_P40R2L:
        case MCD_MODE_P40R2S:
            hostLanes = 2; lineLanes = 2;
            break;
        case MCD_MODE_G21L:
        case MCD_MODE_G21SK:
            hostLanes = 2; lineLanes = 4;
            break;
        default:
            MCD_DBG_ERROR("mcdPortModeGetLanesNum: port mode is invalid\n");
            return 0;
    }
    return ((host_or_line == MCD_HOST_SIDE) ? hostLanes : lineLanes);
}

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************
 MCD_STATUS mcdPortModeGetSideSerdesBitmaps
   returns bitmap of lanes in the slice that will be used
   by port with given mode at host and line sides.
*******************************************************************/
MCD_STATUS mcdPortModeGetSideSerdesBitmaps
(
    IN  MCD_OP_MODE portMode,
    IN  MCD_U16     mdioPort,
    OUT MCD_U16     *hostBmpPtr,
    OUT MCD_U16     *lineBmpPtr
)
{
    MCD_U16 hostLanes  = mcdPortModeGetLanesNum(portMode, MCD_HOST_SIDE);
    MCD_U16 lineLanes  = mcdPortModeGetLanesNum(portMode, MCD_LINE_SIDE);
    MCD_U16 alignment  = ((hostLanes > lineLanes) ? hostLanes : lineLanes);
    MCD_U16 serdesBase = (mdioPort - (mdioPort % alignment));
    if ((hostLanes == 0) || (lineLanes == 0))
    {
        return MCD_FAIL;
    }

    switch (portMode)
    {
        case MCD_MODE_G21L:
        case MCD_MODE_G21SK:
            *hostBmpPtr = (0x3 << serdesBase);
            *lineBmpPtr = (0xF << serdesBase);
            break;
        default:
            *hostBmpPtr = (((1 << hostLanes) - 1) << serdesBase);
            *lineBmpPtr = (((1 << lineLanes) - 1) << serdesBase);
            break;
    }
    return MCD_OK;
}

/*******************************************************************
 MCD_STATUS mcdPortModeGetStoppedSerdesBitmaps
   returns bitmap of lanes in the slice that should be powered down
   before initialization of port with given mode at host and line sides.
*******************************************************************/
MCD_STATUS mcdPortModeGetStoppedSerdesBitmaps
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_OP_MODE portMode,
    IN  MCD_U16     mdioPort,
    OUT MCD_U16     *hostBmpPtr,
    OUT MCD_U16     *lineBmpPtr,
    OUT MCD_U16     *apPortsBmpPtr
)
{
    MCD_U16     newPortHostBmp;
    MCD_U16     newPortLineBmp;
    MCD_U16     hostBmp;
    MCD_U16     lineBmp;
    MCD_U16     port, laneNum;
    MCD_OP_MODE foundMode;
    MCD_U16 serdesBaseMod4 = (mdioPort - (mdioPort % 4));
    MCD_U16 serdesBaseMod2 = (mdioPort - (mdioPort % 2));
    MCD_OP_MODE tempPortMode;

    ATTEMPT(mcdPortModeGetSideSerdesBitmaps(
        portMode, mdioPort, &newPortHostBmp, &newPortLineBmp));

    *hostBmpPtr = 0;
    for (port = 0; (port < 8); port++)
    {
        if (((1 << port) & newPortHostBmp) == 0)
            continue;
        foundMode = pDev->portConfig[port].portMode;
        if (foundMode == MCD_MODE_UNKNOWN)
            continue;
        ATTEMPT(mcdPortModeGetSideSerdesBitmaps(
            foundMode, port, &hostBmp, &lineBmp));
        *hostBmpPtr |= hostBmp;
    }

    *lineBmpPtr = 0;
    *apPortsBmpPtr = 0;
    for (port = 0; (port < 8); port++)
    {
        if (((1 << port) & newPortLineBmp) == 0)
            continue;
        foundMode = pDev->portConfig[port].portMode;
        if (pDev->apCfg[port].apLaneNum  != 0xFF)
        {
            /*AP port line side*/
            *apPortsBmpPtr |= (1 << port);
        }
        if (foundMode == MCD_MODE_UNKNOWN)
            continue;
        ATTEMPT(mcdPortModeGetSideSerdesBitmaps(
            foundMode, port, &hostBmp, &lineBmp));
        *lineBmpPtr |= lineBmp;
    }
    for (port = 0; (port < 8); port++)
    {
        if (((1 << port) & *lineBmpPtr) == 0)
            continue;
        if (pDev->apCfg[port].apLaneNum  != 0xFF)
        {
            /*AP port line side*/
            *apPortsBmpPtr |= (1 << port);
        }
    }
    if (mdioPort == serdesBaseMod4) {
        return MCD_OK; /* port is 0 or 4*/
    }
    else
    {
        if (pDev->apCfg[serdesBaseMod4].apLaneNum  != 0xFF)
        {
            ATTEMPT(mcdPortModeVectorToPortMode(pDev->apCfg[serdesBaseMod4].modesVector, &tempPortMode));
           laneNum = mcdPortModeGetLanesNum(tempPortMode,MCD_LINE_SIDE);
           if ((serdesBaseMod4 + laneNum) > mdioPort)
           {
               printf("mcdPortModeGetStoppedSerdesBitmaps add serdesBaseMod4 %d \n",serdesBaseMod4);
             *apPortsBmpPtr |= (1 << serdesBaseMod4);
           }
        }
        if (mdioPort == serdesBaseMod2) {
            return MCD_OK;
        }
        else
        {
            if (pDev->apCfg[serdesBaseMod2].apLaneNum  != 0xFF)
            {
                ATTEMPT(mcdPortModeVectorToPortMode(pDev->apCfg[serdesBaseMod2].modesVector, &tempPortMode));
               laneNum = mcdPortModeGetLanesNum(tempPortMode,MCD_LINE_SIDE);
               if ((serdesBaseMod2 + laneNum) > mdioPort)
               {
                   printf("mcdPortModeGetStoppedSerdesBitmaps add serdesBaseMod2 %d \n",serdesBaseMod2);
                 *apPortsBmpPtr |= (1 << serdesBaseMod2);
               }
            }
        }

    }
    return MCD_OK;
}

/*******************************************************************
 MCD_STATUS mcdIsRetimerMode
   returns MCD_TRUE for retimer mode, otherwize MCD_FALSE.
*******************************************************************/
MCD_BOOL mcdIsRetimerMode
(
    IN MCD_OP_MODE portMode
)
{
    switch (portMode)
    {
        case MCD_MODE_R100L:
        case MCD_MODE_R100C:
        case MCD_MODE_R25L:
        case MCD_MODE_R25C:
        case MCD_MODE_BM21L:
        case MCD_MODE_BM21C:
        case MCD_MODE_R40L:
        case MCD_MODE_R40C:
        case MCD_MODE_R10L:
        case MCD_MODE_R10K:
        case MCD_MODE_R1L:
        case MCD_MODE_R1C:

            return MCD_TRUE;
        default: return MCD_FALSE;
    }
}
#endif

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************
 MCD_STATUS mcdGetLaneSpeed
   returns lane speed.
*******************************************************************/
MCD_STATUS mcdGetLaneSpeed
(
    IN MCD_OP_MODE portMode,
    IN MCD_U16 host_or_line,
    OUT MCD_U32  *laneSpeed
)
{
    if ((host_or_line != MCD_HOST_SIDE) && (host_or_line != MCD_LINE_SIDE))
    {
        MCD_DBG_ERROR("mcdGetLaneSpeed: host_or_line is invalid\n");
        return 0;
    }
    switch(portMode)
    {
        case MCD_MODE_P100L:
        case MCD_MODE_P100S:
        case MCD_MODE_P100C:
        case MCD_MODE_P100K:
        case MCD_MODE_R100L:
        case MCD_MODE_R100C:
        case MCD_MODE_P50R2L:
        case MCD_MODE_P50R2S:
        case MCD_MODE_P20L:
        case MCD_MODE_P20S:
        case MCD_MODE_P25L:
        case MCD_MODE_P25S:
        case MCD_MODE_R25L:
        case MCD_MODE_R25C:
            *laneSpeed = MCD_25_78125G;
            break;
        case MCD_MODE_P40L:
        case MCD_MODE_P40C:
        case MCD_MODE_P40S:
        case MCD_MODE_P40K:
        case MCD_MODE_R40L:
        case MCD_MODE_R40C:
        case MCD_MODE_P10L:
        case MCD_MODE_P10S:
        case MCD_MODE_R10L:
        case MCD_MODE_R10K:
           *laneSpeed = MCD_10_3125G;
            break;
        case MCD_MODE_G21L:
        case MCD_MODE_G21SK:
            if (host_or_line == MCD_LINE_SIDE)
            {
                *laneSpeed = MCD_10_3125G;
            }
            else
            {
                *laneSpeed = MCD_20_625G;
            }
            break;
        case MCD_MODE_P40R2L:
        case MCD_MODE_P40R2S:
            *laneSpeed = MCD_20_625G;
           break;
        case MCD_MODE_P2_5:
        case MCD_MODE_P2_5S:
            *laneSpeed = MCD_3_125G;
            break;
        case MCD_MODE_P1:
        case MCD_MODE_P1_SGMII:
        case MCD_MODE_P1_BaseX_SGMII:
        case MCD_MODE_R1L:
        case MCD_MODE_R1C:
            *laneSpeed = MCD_1_25G;
            break;
        default:
            MCD_DBG_ERROR("mcdGetLaneSpeed: incorrect mode selection: %u\n", portMode);
            return MCD_FAIL;
    }
    return MCD_OK;
}
/*******************************************************************
 MCD_STATUS mcdPortGetLanesNum
   Amount of lanes used by port (0 on wrong params).
*******************************************************************/
MCD_U16 mcdPortGetLanesNum
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line
)
{
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdPortGetLanesNum: incorrect mdioPort selection: %u\n", mdioPort);
        return 0;
    }

    return mcdPortModeGetLanesNum(
        pDev->portConfig[mdioPort].portMode,
        host_or_line);
}
#endif /*#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3*/


#define LINE_MODE_IDX     0
#define LINE_SPEED_IDX    1
#define HOST_MODE_IDX     2
#define HOST_SPEED_IDX    3
#define OVERALL_SPEED_IDX 4

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
MCD_U16 portModeTbl[MCD_MODE_NUM][5] =
   {{0,0,0,0,0},
    {MCD_PCS,             MCD_100GB_CR4, MCD_PCS,         MCD_100GB_R4, MCD_UNKNOWN_SPEED }, /* P100_40_C */

    {MCD_PCS,             MCD_100GB_LR4, MCD_PCS,         MCD_100GB_R4, MCD_100GB }, /* P100L */
    {MCD_PCS,             MCD_100GB_SR4, MCD_PCS,         MCD_100GB_R4, MCD_100GB }, /* P100S */
    {MCD_PCS,             MCD_100GB_CR4, MCD_PCS,         MCD_100GB_R4, MCD_100GB }, /* P100C */
    {MCD_PCS,             MCD_100GB_KR4, MCD_PCS,         MCD_100GB_R4, MCD_100GB }, /* P100K */

    {MCD_PCS,             MCD_40GB_SLR4, MCD_PCS,         MCD_40GB_R4,  MCD_40GB  }, /* P40L  */
    {MCD_PCS,             MCD_40GB_CR4,  MCD_PCS,         MCD_40GB_R4,  MCD_40GB  }, /* P40C  */
    {MCD_PCS,             MCD_40GB_KR4,  MCD_PCS,         MCD_40GB_R4,  MCD_40GB  }, /* P40K  */

    {MCD_PCS,             MCD_100GB_KR4, MCD_PCS,         MCD_100GB_R4, MCD_UNKNOWN_SPEED }, /* P100_40_K */

    {MCD_TRANSPARENT,     MCD_100GB_LR4, MCD_TRANSPARENT, MCD_100GB_R4, MCD_100GB }, /* R100L */
    {MCD_TRANSPARENT,     MCD_100GB_CR4, MCD_TRANSPARENT, MCD_100GB_R4, MCD_100GB }, /* R100C */
    {MCD_TRANSPARENT,     MCD_25GB_SLR,  MCD_TRANSPARENT, MCD_25GB_R,   MCD_25GB },  /* R25L  */
    {MCD_TRANSPARENT,     MCD_25GB_CKR,  MCD_TRANSPARENT, MCD_25GB_R,   MCD_25GB },  /* R25C  */
    {MCD_40G_INTERLEAVED, MCD_100GB_LR4, MCD_TRANSPARENT, MCD_20GB_R2,  MCD_20GB },  /* BM21L */
    {MCD_40G_INTERLEAVED, MCD_100GB_CR4, MCD_TRANSPARENT, MCD_20GB_R2,  MCD_20GB },  /* BM21C */

    {MCD_TRANSPARENT,     MCD_10GB_SLR,  MCD_TRANSPARENT, MCD_10GB_R,   MCD_10GB },  /* R10L  */
    {MCD_TRANSPARENT,     MCD_10GB_CKR,  MCD_TRANSPARENT, MCD_10GB_R,   MCD_10GB },  /* R10K  */
    {MCD_TRANSPARENT,     MCD_40GB_SLR4, MCD_TRANSPARENT, MCD_40GB_R4,  MCD_40GB },  /* R40L  */
    {MCD_TRANSPARENT,     MCD_40GB_CR4,  MCD_TRANSPARENT, MCD_40GB_R4,  MCD_40GB },  /* R40C  */


    {MCD_MLG_10G,         MCD_100GB_LR4, MCD_MLG_10G,      0,           MCD_10GB },  /* G10L  */
    {MCD_MLG_10G,         MCD_100GB_SR4, MCD_MLG_10G,      0,           MCD_10GB },  /* G10S  */
    {MCD_MLG_10G,         MCD_100GB_CR4, MCD_MLG_10G,      0,           MCD_10GB },  /* G10C  */
    {MCD_MLG_10G,         MCD_100GB_KR4, MCD_MLG_10G,      0,           MCD_10GB },  /* G10K  */

    {MCD_MLG_10G_40G,     MCD_100GB_LR4, MCD_MLG_10G_40G,  0,           MCD_40GB },  /* G14L  */
    {MCD_MLG_10G_40G,     MCD_100GB_SR4, MCD_MLG_10G_40G,  0,           MCD_40GB },  /* G14S  */
    {MCD_MLG_10G_40G,     MCD_100GB_CR4, MCD_MLG_10G_40G,  0,           MCD_40GB },  /* G14C  */
    {MCD_MLG_10G_40G,     MCD_100GB_KR4, MCD_MLG_10G_40G,  0,           MCD_40GB },  /* G14K  */

    {MCD_MLG_40G_10G,     MCD_100GB_LR4, MCD_MLG_40G_10G,  0,           MCD_40GB },  /* G41L  */
    {MCD_MLG_40G_10G,     MCD_100GB_SR4, MCD_MLG_40G_10G,  0,           MCD_40GB },  /* G41S  */
    {MCD_MLG_40G_10G,     MCD_100GB_CR4, MCD_MLG_40G_10G,  0,           MCD_40GB },  /* G41C  */
    {MCD_MLG_40G_10G,     MCD_100GB_KR4, MCD_MLG_40G_10G,  0,           MCD_40GB },  /* G41K  */

    {MCD_MLG_40G_40G,     MCD_100GB_LR4, MCD_MLG_40G_40G,  0,           MCD_40GB },  /* G44L  */
    {MCD_MLG_40G_40G,     MCD_100GB_SR4, MCD_MLG_40G_40G,  0,           MCD_40GB },  /* G44S  */
    {MCD_MLG_40G_40G,     MCD_100GB_CR4, MCD_MLG_40G_40G,  0,           MCD_40GB },  /* G44C  */
    {MCD_MLG_40G_40G,     MCD_100GB_KR4, MCD_MLG_40G_40G,  0,           MCD_40GB },  /* G44K  */

    {MCD_PCS,             MCD_100GB_LR4, MCD_PCS,          MCD_100GB_R10, MCD_100GB }, /* G100L */
    {MCD_PCS,             MCD_100GB_SR4, MCD_PCS,          MCD_100GB_R10, MCD_100GB }, /* G100S */
    {MCD_PCS,             MCD_100GB_CR4, MCD_PCS,          MCD_100GB_R10, MCD_100GB }, /* G100C */
    {MCD_PCS,             MCD_100GB_KR4, MCD_PCS,          MCD_100GB_R10, MCD_100GB },  /* G100K */
    /* X5123 and EC808 modes */
    {MCD_PCS,             MCD_50GB_SLR2, MCD_PCS,          MCD_50GB_R2,   MCD_50GB}, /*MCD_MODE_P50R2L*/
    {MCD_PCS,             MCD_50GB_SLR2, MCD_PCS,          MCD_50GB_R2,   MCD_50GB}, /*MCD_MODE_P50R2S*/
    {MCD_PCS,             MCD_40GB_SLR2, MCD_PCS,          MCD_40GB_R2,   MCD_40GB}, /*MCD_MODE_P40R2L*/
    {MCD_PCS,             MCD_40GB_SLR2, MCD_PCS,          MCD_40GB_R2,   MCD_40GB}, /*MCD_MODE_P40R2S*/
    {MCD_PCS,             MCD_25GB_SLR,  MCD_PCS,          MCD_25GB_R,    MCD_25GB}, /*MCD_MODE_P25L*/
    {MCD_PCS,             MCD_25GB_SLR,  MCD_PCS,          MCD_25GB_R,    MCD_25GB}, /*MCD_MODE_P25S*/
    {MCD_PCS,             MCD_10GB_SLR,  MCD_PCS,          MCD_10GB_R,    MCD_10GB}, /*MCD_MODE_P10L*/
    {MCD_PCS,             MCD_10GB_SLR,  MCD_PCS,          MCD_10GB_R,    MCD_10GB}, /*MCD_MODE_P10S*/
    {MCD_PCS,             MCD_2_5GB_R_LINE, MCD_PCS,       MCD_2_5GB_R,   MCD_2_5GB},/*MCD_MODE_P2_5*/
    {MCD_PCS,             MCD_1GB_R_LINE,MCD_PCS,          MCD_1GB_R,     MCD_1GB},  /*MCD_MODE_P1*/
    {MCD_MLG_10GX4,       MCD_40GB_SLR4, MCD_MLG_20GX2,    MCD_40GB_R2,   MCD_40GB}, /*MCD_MODE_40G_R2_R4_GB == MCD_MODE_G21L*/
    {MCD_PCS,             MCD_40GB_SLR4, MCD_PCS,          MCD_40GB_R4,   MCD_40GB}, /*MCD_MODE_P40S*/
    {MCD_PCS,             MCD_2_5GB_R_LINE, MCD_PCS,       MCD_2_5GB_R,   MCD_2_5GB},/*MCD_MODE_P2_5S*/
    {MCD_PCS,             MCD_1GB_R_LINE, MCD_PCS,         MCD_1GB_R,     MCD_1GB},  /*MCD_MODE_P1_SGMII*/
    {MCD_TRANSPARENT,     MCD_1GB_R_LINE, MCD_TRANSPARENT, MCD_1GB_R_LINE, MCD_1GB}, /* MCD_MODE_R1L  */
    {MCD_TRANSPARENT,     MCD_1GB_R_LINE, MCD_TRANSPARENT, MCD_1GB_R_LINE, MCD_1GB}, /* MCD_MODE_R1C  */
    {MCD_PCS,             MCD_1GB_R_LINE, MCD_PCS,         MCD_1GB_R,     MCD_1GB},  /*MCD_MODE_P1_BaseX_SGMII*/
    {MCD_MLG_10GX4,       MCD_40GB_SLR4,  MCD_MLG_20GX2,   MCD_40GB_R2,   MCD_40GB}, /*MCD_MODE_40G_R2_R4_GB == MCD_MODE_G21SK*/
    {MCD_PCS,             MCD_20GB_SLR,  MCD_PCS,          MCD_20GB_R,    MCD_20GB}, /*MCD_MODE_P20L*/
    {MCD_PCS,             MCD_20GB_SLR,  MCD_PCS,          MCD_20GB_R,    MCD_20GB}  /*MCD_MODE_P20S*/
   };


/*******************************************************************************
 MCD_STATUS mcdGetApPortParams
    Get AP port parameters
*******************************************************************************/
MCD_STATUS mcdGetApPortParams
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U32 mdioPort,
    IN MCD_OP_MODE portMode,
    OUT MCD_U32  *modeVector,
    OUT MCD_U32  *laneSpeed,
    OUT MCD_U32 *numOfActLanes
)
{
    switch(portMode)
    {
        case MCD_MODE_P100C:
        case MCD_MODE_R100C:
            *modeVector = MCD_AN_100GBASE_CR4;
            *laneSpeed = MCD_25_78125G;
            *numOfActLanes = 4;
            break;
        case MCD_MODE_P100K:
            *modeVector = MCD_AN_100GBASE_KR4;
            *laneSpeed = MCD_25_78125G;
            *numOfActLanes = 4;
            break;
        case MCD_MODE_P40K:
            *modeVector = MCD_AN_40GBASE_KR4;
            *laneSpeed = MCD_10_3125G;
            *numOfActLanes = 4;
            break;
        case MCD_MODE_P40C:
        case MCD_MODE_R40C:
            *modeVector = MCD_AN_40GBASE_CR4;
            *laneSpeed = MCD_10_3125G;
            *numOfActLanes = 4;
            break;
        case MCD_MODE_R25C:
            *modeVector = MCD_AN_25GBASE_KCR;
            *laneSpeed = MCD_25_78125G;
            *numOfActLanes = 1;
            break;
        case MCD_MODE_R10K:
            *modeVector = MCD_AN_10GBase_KR;
            *laneSpeed = MCD_10_3125G;
            *numOfActLanes = 1;
            break;
        case MCD_MODE_P1:
            *modeVector = MCD_AN_1000BASE_KX;
            *laneSpeed =  MCD_1_25G;;
            *numOfActLanes = 1;
            break;
        default:
            MCD_DBG_ERROR("mcdGetApPortParams: incorrect mode selection: %u\n", portMode);
            return MCD_FAIL;
    }
    return MCD_OK;

}



/*******************************************************************
 MCD_STATUS mcdSetMode
    Line and Host mode selection
    Soft reset is performed.
*******************************************************************/
MCD_STATUS mcdSetMode
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_OP_MODE portMode
)
{
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSetMode: incorrect mdioPort selection: %u\n", mdioPort);
        return MCD_FAIL;
    }

    return MCD_NOT_IMPLEMENTED;
}

/*******************************************************************************
 MCD_STATUS mcdGetModeSpeed
    Get mode speed based on the OP mode setting
    and get mode (PCS, TRANSPARENT, etc.) based on the OP mode setting
*******************************************************************************/
MCD_STATUS mcdGetModeSpeed
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    OUT MCD_MODE_SPEED *speed,
    OUT MCD_MODE *mode
)
{
    MCD_OP_MODE portMode;

    portMode = pDev->portConfig[mdioPort].portMode;

    if (((portMode >= MCD_MODE_P100L) && (portMode <= MCD_MODE_P40K)) ||
        ((portMode >= MCD_MODE_P50R2L) && (portMode <= MCD_MODE_G21L))||
        (portMode == MCD_MODE_G21SK)  || (portMode == MCD_MODE_P20S))
    {
        *speed = portModeTbl[portMode][OVERALL_SPEED_IDX];
        if (host_or_line == MCD_LINE_SIDE)
        {
            *mode = portModeTbl[portMode][LINE_MODE_IDX];
        }
        else if (host_or_line == MCD_HOST_SIDE)
        {
            *mode = portModeTbl[portMode][HOST_MODE_IDX];
        }
        else
        {
            MCD_DBG_ERROR("mcdGetModeSpeed: host or line select incorrect: %d\n", host_or_line);
            return MCD_FAIL;
        }
    }
    else
    {
        MCD_DBG_ERROR(
            "mcdGetModeSpeed: incorrect/unsupported mode selection: %u\n",
            portMode);
        return MCD_FAIL;
    }
    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdIsPortModePcsControlled
    Checks is mode of port controlled by PCS (retutn 1) or not (return 0).
*******************************************************************************/
MCD_U16 mcdIsPortModePcsControlled
(
    IN MCD_MODE portMode
)
{
    if (portMode >= MCD_MODES_NUM) return 0;
    switch (portMode)
    {
        case MCD_TRANSPARENT:
        case MCD_40G_INTERLEAVED:
        case MCD_POWER_DOWN:
        case MCD_RESERVED_MODE:
            return 0;
        default: return 1; /*PCS controlled mode*/
    }
}
#endif /*#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3*/

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************
 MCD_STATUS mcdGetNumberPorts
     returns number of ports on the device based on the mode a mdioPort is set to
*******************************************************************/
MCD_STATUS mcdGetNumberPorts
(
    IN MCD_OP_MODE mode,
    IN MCD_U16 *numPorts
)
{
    if (mode == MCD_MODE_UNKNOWN)
    {
        *numPorts = 0;
    }
    else if (mode >= MCD_MODE_P100_40_C && mode <= MCD_MODE_P100_40_K)
    {
        *numPorts = 2; /* these modes have 2 ports, 4 lanes each */
    }
    else if (mode >= MCD_MODE_R100L && mode <= MCD_MODE_G100K)
    {
        *numPorts = 1; /* repeater modes/MLG have only 1 mdioPort for addressing purposes API */
    }
    else
    {
        *numPorts = 0;
        MCD_DBG_ERROR("mcdGetNumberPorts: unknown mode: %u failed.\n", mode);
        return MCD_FAIL;
    }

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdGetAutoNegAcquiredSpeed
    Get Auto-neg acquired speed after auto-neg is completed
*******************************************************************************/
MCD_STATUS mcdGetAutoNegAcquiredSpeed
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    OUT MCD_U16 *speed_bits
)
{
    return MCD_NOT_IMPLEMENTED;
}

/*******************************************************************************
 MCD_STATUS mcdSetAutoNegAcquiredSpeed
    Set Auto-neg acquired speed after auto-neg is completed
*******************************************************************************/
MCD_STATUS mcdSetAutoNegAcquiredSpeed
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 speed_bit
)
{
    return MCD_NOT_IMPLEMENTED;
}
#endif

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************************
 MCD_STATUS mcdReadPCSLinkStatus
    Check 40G PCS link status
*******************************************************************************/
MCD_STATUS mcdReadPCSLinkStatus
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U32 hostRegAddr,
    IN MCD_U32 lineRegAddr,
    IN MCD_U32 bitIndex,
    OUT MCD_U16 *currentStatus,
    OUT MCD_U16 *latchedStatus,
    OUT DETAILED_STATUS_TYPE *statusDetail
)
{
    MCD_U32 hostLatchedStatus, hostCurrentStatus, lineLatchedStatus, lineCurrentStatus;

    ATTEMPT(mcdHwGetPhyRegField32bit(
        pDev, mdioPort, hostRegAddr, bitIndex, 1, &hostLatchedStatus));
    ATTEMPT(mcdHwGetPhyRegField32bit(
        pDev, mdioPort, hostRegAddr, bitIndex, 1, &hostCurrentStatus));
    ATTEMPT(mcdHwGetPhyRegField32bit(
        pDev, mdioPort, lineRegAddr, bitIndex, 1, &lineLatchedStatus));
    ATTEMPT(mcdHwGetPhyRegField32bit(
        pDev, mdioPort, lineRegAddr, bitIndex, 1, &lineCurrentStatus));

    *currentStatus = (MCD_U16)(hostCurrentStatus & lineCurrentStatus);
    *latchedStatus = (MCD_U16)(hostLatchedStatus & lineLatchedStatus);
    statusDetail->P100_40_status.hostCurrent = (MCD_U16)hostCurrentStatus;
    statusDetail->P100_40_status.hostLatched = (MCD_U16)hostLatchedStatus;
    statusDetail->P100_40_status.lineCurrent = (MCD_U16)lineCurrentStatus;
    statusDetail->P100_40_status.lineLatched = (MCD_U16)lineLatchedStatus;

    return MCD_OK;
}

MCD_STATUS mcdReadPCSLineLinkStatus
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    OUT MCD_U32 *currentStatus
)
{
    MCD_U32 lineRegAddr;
    MCD_U32 bitIndex;
    MCD_U32 slice, chan;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdReadPCSLineLinkStatus: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdReadPCSLineLinkStatus: incorrect port selection: %u\n", mdioPort);
        return MCD_FAIL;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);

     switch(pDev->portConfig[mdioPort].portMode)
    {
        /* new modes for X5123 and EC808 */
        case MCD_MODE_P50R2L:        /* 50GBase-R2                                              */
        case MCD_MODE_P50R2S:        /* 50GBase-R2                                              */
        case MCD_MODE_P40R2L:        /* 40GBase-R2                                              */
        case MCD_MODE_P40R2S:        /* 40GBase-R2                                              */
        case MCD_MODE_P25L:          /* 25GBase-R1                                              */
        case MCD_MODE_P25S:          /* 25GBase-R1                                              */
        case MCD_MODE_P20L:          /* 20GBase-R1                                              */
        case MCD_MODE_P20S:          /* 20GBase-R1                                              */
        case MCD_MODE_P10L:          /* 10GBase-R1                                              */
        case MCD_MODE_P10S:          /* 10GBase-R1                                              */
        case MCD_MODE_P2_5:          /* 2.5GBase-X                                              */
        case MCD_MODE_P2_5S:
        case MCD_MODE_G21L:
        case MCD_MODE_G21SK:
        /* legacy modes */
        case MCD_MODE_P100_40_C:
        case MCD_MODE_P100_40_K:
        case MCD_MODE_P100L:
        case MCD_MODE_P100S:
        case MCD_MODE_P100C:
        case MCD_MODE_P100K:
        case MCD_MODE_P40L:
        case MCD_MODE_P40S:
        case MCD_MODE_P40C:
        case MCD_MODE_P40K:
            lineRegAddr = UMAC_MCPCS_LINE_REG_ADDR(UMAC_MCPCS_BASE_R_and_10GBASE_T_PCS_Status1(slice,chan));
            bitIndex    = 12;
            ATTEMPT(mcdHwGetPhyRegField32bit(pDev, mdioPort, lineRegAddr, bitIndex, 1, currentStatus));
            break;
        /* new modes for X5123 and EC808 - low speed */
        case MCD_MODE_P1:
        case MCD_MODE_P1_SGMII:
        case MCD_MODE_P1_BaseX_SGMII:
            lineRegAddr = UMAC_LSMCPCS_LINE_REG_ADDR(UMAC_LSMCPCS_sts(slice,chan));
            bitIndex    = 1; /*syncstat*/
            ATTEMPT(mcdHwGetPhyRegField32bit(pDev, mdioPort, lineRegAddr, bitIndex, 1, currentStatus));
            break;
        default:
            MCD_DBG_ERROR("mcdReadPCSLineLinkStatus: incorrect/unsupported mode selection: %u\n", pDev->portConfig[MCD_GET_PORT_IDX(pDev,mdioPort)].portMode);
            return MCD_FAIL;
            break;
    }

    return MCD_OK;
}



/*******************************************************************************
 MCD_STATUS mcdDisableAllUmacInterrupts
*******************************************************************************/
MCD_STATUS mcdDisableAllUmacInterrupts
(
    IN MCD_DEV_PTR pDev

)
{
    MCD_U32 i;
    MCD_U32 slice;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdDisableAllUmacInterrupts: device not initialized\n");
        return MCD_FAIL;
    }


    for (slice =0; slice < 2; slice++)
    {
        for (i = 0; i <= 14; i++)
        {
            ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0, UMAC_INTERRUPT_clrintenable(slice, i), 0xFFFF));
            ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0, UMAC_INTERRUPT_LINE_REG_ADDR(UMAC_INTERRUPT_clrintenable(slice, i)), 0xFFFF));
        }

    }
    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdReadRepeaterLinkStatus
    Check Serdes DSP lock status of both P0 and P1,
    NOTE: mdioPort must be MDIO address of first port only
    Returns status of all lanes on both host and line side.
*******************************************************************************/
MCD_STATUS mcdReadRepeaterLinkStatus
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    OUT MCD_U16 *CurrentStatus,
    OUT DETAILED_STATUS_TYPE *statusDetail
)
{
    MCD_U32 slice, channel, start_channel, max_channel;
    MCD_U32 hostSigDetect, lineSigDetect;
    MCD_OP_MODE portMode;

    portMode = pDev->portConfig[mdioPort].portMode;

    mcdMemSet(statusDetail, 0xFF, sizeof(DETAILED_STATUS_TYPE));
    slice         = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    start_channel = CHAN_IN_SLICE_NUM(mdioPort);
    switch (portMode)
    {
        case MCD_MODE_R100L:
        case MCD_MODE_R40L:
        case MCD_MODE_R100C:
        case MCD_MODE_R40C:
            max_channel = start_channel + 3;
            break;
        case MCD_MODE_R25L:
        case MCD_MODE_R10L:
        case MCD_MODE_R25C:
        case MCD_MODE_R10K:
        case MCD_MODE_R1L:
        case MCD_MODE_R1C:
            max_channel = start_channel;
            break;
        default:
            MCD_DBG_ERROR(
                "mcdReadRepeaterLinkStatus: incorrect/unsupported mode selection: %u\n",
                pDev->portConfig[MCD_GET_PORT_IDX(pDev,mdioPort)].portMode);
            return MCD_FAIL;
    }

    hostSigDetect = 0;
    lineSigDetect = 0;
    *CurrentStatus = 1;
    for (channel = start_channel; (channel <= max_channel); channel++)
    {
        ATTEMPT(mcdCheckSerdesSignalStability(
            pDev, MCD_HOST_SIDE,
            slice, channel,
            1 /*testTimeMs*/, &hostSigDetect));
        ATTEMPT(mcdCheckSerdesSignalStability(
            pDev, MCD_LINE_SIDE,
            slice, channel,
            1 /*testTimeMs*/, &lineSigDetect));

        *CurrentStatus &= (MCD_U16)(hostSigDetect & lineSigDetect);

        switch (portMode)
        {
            case MCD_MODE_R100L:
            case MCD_MODE_R40L:
            case MCD_MODE_R100C:
            case MCD_MODE_R40C:
                if (slice == 0)
                {
                    statusDetail->R100_40_status.host_P0[channel] = (MCD_U16)(hostSigDetect);
                    statusDetail->R100_40_status.line_P0[channel] = (MCD_U16)(lineSigDetect);
                }
                else
                {
                    statusDetail->R100_40_status.host_P1[channel] = (MCD_U16)hostSigDetect;
                    statusDetail->R100_40_status.line_P1[channel] = (MCD_U16)lineSigDetect;
                }
                statusDetail->R100_40_status.hostCurrent[(slice*4)+channel] = (MCD_U16)hostSigDetect;
                statusDetail->R100_40_status.lineCurrent[(slice*4)+channel] = (MCD_U16)lineSigDetect;
                break;
            case MCD_MODE_R25L:
            case MCD_MODE_R10L:
            case MCD_MODE_R25C:
            case MCD_MODE_R10K:
            case MCD_MODE_R1L:
            case MCD_MODE_R1C:
                statusDetail->R25_10_status.hostCurrent[(slice*4)+channel] = (MCD_U16)hostSigDetect;
                statusDetail->R25_10_status.lineCurrent[(slice*4)+channel] = (MCD_U16)lineSigDetect;
                break;
            default:
                MCD_DBG_ERROR(
                    "mcdReadRepeaterLinkStatus: incorrect/unsupported mode selection: %u\n",
                    pDev->portConfig[MCD_GET_PORT_IDX(pDev,mdioPort)].portMode);
                return MCD_FAIL;
        }
    }
    return MCD_OK;
}

/*******************************************************************
 MCD_STATUS mcdPortResetTimeout
 Check timeout after the soft or hard reset
*******************************************************************/
MCD_STATUS mcdPortResetTimeout
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 timeoutMs
)
{
    return MCD_NOT_IMPLEMENTED;
}

/*******************************************************************
 MCD_STATUS mcdLaneReset
     Check timeout after the Lane soft reset
*******************************************************************/
MCD_STATUS mcdLaneSoftReset
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 timeoutMs
)
{
    return MCD_NOT_IMPLEMENTED;
}

/*******************************************************************
 MCD_STATUS mcdLaneResetTimeout
 Check timeout after the Lane soft reset
*******************************************************************/
MCD_STATUS mcdLaneResetTimeout
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 timeoutMs
)
{
    return MCD_NOT_IMPLEMENTED;
}

#ifndef ASIC_SIMULATION
/* initializes driver for broadcast */
/* destructed by mcdUnloadDriver    */
MCD_STATUS mcdInitBroadcastDev
(
    IN  MCD_DEV_PTR pPatternDev,
    OUT MCD_DEV_PTR pBroadcastDev
)
{
    MCD_SER_DEV_PTR pSerdesDev = 0;

    if (pPatternDev->devEnabled == MCD_FALSE) return MCD_FAIL;

    mcdMemSet(pBroadcastDev, 0, (sizeof(MCD_DEV)));
    pBroadcastDev->firstMdioPort  = 0x1F;
    pBroadcastDev->fmcdReadMdio   = pPatternDev->fmcdReadMdio;
    pBroadcastDev->fmcdWriteMdio  = pPatternDev->fmcdWriteMdio;
    pBroadcastDev->shadowValidBmp = 0;
    pBroadcastDev->deviceId       = pPatternDev->deviceId;
    pBroadcastDev->devEnabled     = pPatternDev->devEnabled;

    pSerdesDev = mcdWrapperAllocDevStruct();
    if (pSerdesDev)
    {
        pSerdesDev->client_data = (MCD_PVOID)pBroadcastDev;
        pBroadcastDev->serdesDev = pSerdesDev;
        pSerdesDev->sbus_func_ptr = ((MCD_SER_DEV_PTR)(pPatternDev->serdesDev))->sbus_func_ptr;
        pSerdesDev->communication_method =
            ((MCD_SER_DEV_PTR)(pPatternDev->serdesDev))->communication_method;
    }
    else
    {
        MCD_DBG_ERROR("mcdInitSerdesDev: pSerdesDev is NULL\n");
        return MCD_FAIL;
    }
    return MCD_OK;
}
#endif /* ASIC_SIMULATION*/

/******************************************************************************
 MCD_STATUS mcdLoadCm3FWImageStartOrEnd
*******************************************************************************/
MCD_STATUS mcdLoadCm3FWImageStartOrEnd
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_BOOL start    /* MCD_TRUE - start, MCD_FALSE - END */
)
{
    MCD_U32 regAddr;
    MCD_U32 value;

    regAddr  = REG_ADDR_CM3_GLOBAL_CONFIGURATION;
    value    = ((start == MCD_FALSE) ? 3 : 0);

    /* value == 0 Stop CM3 before load FW */
    /* value == 1 Start CM3 after load FW */
    ATTEMPT(mcdHwSetPhyRegField32bit(
        pDev, mdioPort, regAddr, 28, 2, value));

    return MCD_OK;
}

/******************************************************************************
 MCD_STATUS mcdLoadCm3FWImageLoad
*******************************************************************************/
MCD_STATUS mcdLoadCm3FWImageLoad
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U32 imageSize, /* size in bytes  */
    IN const MCD_U8 image[]
)
{
    MCD_U32    memoBaseAddr;
    MCD_U32    data;
    MCD_U32    byteIdx;

    memoBaseAddr = REG_ADDR_CM3_MEMORY_BASE;
    if ((imageSize == 0) || (image == NULL))
    {
        return MCD_OK;
    }

    /* Load image */
    for (byteIdx = 0; (byteIdx < imageSize); (byteIdx = byteIdx+4))
    {
        /* the image is array of bytes in LE order.
           Copy four bytes to word in LE order. */
        data =   (MCD_U32)image[byteIdx]             |
               (((MCD_U32)image[byteIdx + 1]) << 8)  |
               (((MCD_U32)image[byteIdx + 2]) << 16) |
               (((MCD_U32)image[byteIdx + 3]) << 24);

        ATTEMPT(mcdHwXmdioWrite32bit(
            pDev, mdioPort, (memoBaseAddr + byteIdx), data));
    }

    return MCD_OK;
}
/**
* @internal mcdServiceCpuRead function
* @endinternal
*
*/
MCD_STATUS mcdServiceCpuRead
(
    IN MCD_DEV_PTR pDev,
    unsigned int offset,
    unsigned int *dataPtr,
    unsigned int size
)
{
    MCD_U32    wordIdx, data,adr;
    for (wordIdx = 0; (wordIdx < size); (wordIdx = wordIdx+4))
    {
        adr = (0x30080000 + offset + wordIdx);
        ATTEMPT(mcdHwXmdioRead32bit(pDev, pDev->firstMdioPort, adr, &data));
        *(MCD_U32*)(dataPtr++) = data;
    }

    return MCD_OK;
}
/**
* @internal mcdServiceCpuWrite function
* @endinternal
*
*/
MCD_STATUS mcdServiceCpuWrite
(
    IN MCD_DEV_PTR pDev,
    unsigned int offset,
    unsigned int *dataPtr,
    unsigned int size
)
{
    MCD_U32    wordIdx, data2write,adr;
    for (wordIdx = 0; (wordIdx < size); (wordIdx = wordIdx+4))
    {
        data2write = *(MCD_U32*)(dataPtr++);
        adr = (0x30080000 + offset + wordIdx);
        ATTEMPT(mcdHwXmdioWrite32bit(pDev, pDev->firstMdioPort, adr, data2write));

    }

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdPortPollingParamsGet
  *******************************************************************************/
MCD_STATUS mcdPortPollingParamsGet
(
    IN   MCD_DEV_PTR       pDev,
    IN   MCD_U16           mdioPort,
    OUT  MCD_BOOL          *retimerModePtr,
    OUT  MCD_SERDES_SPEED  *lineSerdesSpeedPtr,
    OUT  MCD_SERDES_SPEED  *hostSerdesSpeedPtr,
    OUT  MCD_U16           *lineSerdesBitmapPtr,
    OUT  MCD_U16           *hostSerdesBitmapPtr,
    OUT  MCD_NO_PPM_MODE   *noPpmModePtr
)
{
    MCD_U8            slice,chan;
    MCD_BOOL          retimerMode;
    MCD_SERDES_SPEED  lineSerdesSpeed;
    MCD_SERDES_SPEED  hostSerdesSpeed;
    MCD_U16           lineSerdesBitmap;
    MCD_U16           hostSerdesBitmap;
    MCD_BOOL          noPpmSupport;
    MCD_SERDES_SPEED  baudrate = MCD_SPEED_NA;
    MCD_OP_MODE       portMode = pDev->portConfig[mdioPort].portMode;


    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("%s: incorrect port selection: %u\n", __func__, mdioPort);
        return MCD_FAIL;
    }
    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan = CHAN_IN_SLICE_NUM(mdioPort);

    switch(portMode)
    {
        case MCD_MODE_P100L:
        case MCD_MODE_P100S:
        case MCD_MODE_P100C:
        case MCD_MODE_P100K:
            hostSerdesBitmap = (0x0F << (slice * 4));
            retimerMode      = 0;
            noPpmSupport    = 1;
            lineSerdesSpeed  = MCD_25_78125G;
            hostSerdesSpeed  = MCD_25_78125G;
            /* power up 4 Host serdeses */
            if (pDev->apCfg[mdioPort].apLaneNum  != 0xFF)
            {
                lineSerdesBitmap = 0;
            }
            else
            {
                lineSerdesBitmap = (0x0F << (slice * 4));
            }
            break;
        case MCD_MODE_P40L:
        case MCD_MODE_P40C:
        case MCD_MODE_P40S:
        case MCD_MODE_P40K:
            hostSerdesBitmap = (0x0F << (slice * 4));
            retimerMode      = 0;
            noPpmSupport    = 1;
            lineSerdesSpeed  = MCD_10_3125G;
            hostSerdesSpeed  = MCD_10_3125G;
            if (pDev->apCfg[mdioPort].apLaneNum  != 0xFF)
            {
                lineSerdesBitmap = 0;
            }
            else
            {
                lineSerdesBitmap = (0x0F << (slice * 4));
            }
            break;
        case MCD_MODE_G21L:
        case MCD_MODE_G21SK:
            lineSerdesBitmap = (0x0F << (slice * 4));
            hostSerdesBitmap = (0x03 << ((slice * 4) + chan));
            retimerMode      = 0;
            noPpmSupport    = 1;
            lineSerdesSpeed  = MCD_10_3125G;
            hostSerdesSpeed  = MCD_20_625G;
            break;

        case MCD_MODE_P50R2L:
        case MCD_MODE_P50R2S:
            lineSerdesBitmap = (0x03 << ((slice * 4) + chan));
            hostSerdesBitmap = (0x03 << ((slice * 4) + chan));
            retimerMode      = 0;
            noPpmSupport     = 1;
            lineSerdesSpeed  = MCD_25_78125G;
            hostSerdesSpeed  = MCD_25_78125G;
            break;

        case MCD_MODE_P40R2L:
        case MCD_MODE_P40R2S:
            lineSerdesBitmap = (0x03 << ((slice * 4) + chan));
            hostSerdesBitmap = (0x03 << ((slice * 4) + chan));
            retimerMode      = 0;
            noPpmSupport     = 1;
            lineSerdesSpeed  = MCD_20_625G;
            hostSerdesSpeed  = MCD_20_625G;
            break;
        case MCD_MODE_P25L:
        case MCD_MODE_P25S:
        case MCD_MODE_P20L:
        case MCD_MODE_P20S:
        case MCD_MODE_P10L:
        case MCD_MODE_P10S:
            if ((portMode == MCD_MODE_P10S) || (portMode == MCD_MODE_P10L))
            {
                baudrate = MCD_10_3125G;
            }
            else if ((portMode == MCD_MODE_P20S) || (portMode == MCD_MODE_P20L))
            {
                baudrate = MCD_20_625G;
            }
            else
            {
                baudrate = MCD_25_78125G;
            }
            hostSerdesBitmap = (0x01 << ((slice * 4) + chan));
            retimerMode      = 0;
            noPpmSupport     = 1;
            lineSerdesSpeed  = baudrate;
            hostSerdesSpeed  = baudrate;
            if (pDev->apCfg[mdioPort].apLaneNum  != 0xFF)
            {
                lineSerdesBitmap = 0;
            }
            else
            {
                lineSerdesBitmap = (0x01 << ((slice * 4) + chan));
            }
            break;
        case MCD_MODE_R100L:
        case MCD_MODE_R100C:
            hostSerdesBitmap = (0x0F << (slice * 4));
            retimerMode      = 1;
            noPpmSupport     = 0;
            lineSerdesSpeed  = MCD_25_78125G;
            hostSerdesSpeed  = MCD_25_78125G;
            /* power up 4 Host serdeses */
            if (pDev->apCfg[mdioPort].apLaneNum  != 0xFF)
            {
                lineSerdesBitmap = 0;
            }
            else
            {
                lineSerdesBitmap = (0x0F << (slice * 4));
             }
            break;
        case MCD_MODE_R40L:
        case MCD_MODE_R40C:
            hostSerdesBitmap = (0x0F << (slice * 4));
            retimerMode      = 1;
            noPpmSupport     = 0;
            lineSerdesSpeed  = MCD_10_3125G;
            hostSerdesSpeed  = MCD_10_3125G;
            if (pDev->apCfg[mdioPort].apLaneNum  != 0xFF)
            {
                lineSerdesBitmap = 0;
             }
            else
            {
                lineSerdesBitmap = (0x0F << (slice * 4));
            }
            break;
        case MCD_MODE_R25L:
        case MCD_MODE_R25C:
            hostSerdesBitmap = (0x01 << ((slice * 4) + chan));
            retimerMode      = 1;
            noPpmSupport     = 0;
            lineSerdesSpeed  = MCD_25_78125G;
            hostSerdesSpeed  = MCD_25_78125G;
            if (pDev->apCfg[mdioPort].apLaneNum  != 0xFF)
            {
                lineSerdesBitmap = 0;
            }
            else
            {
                lineSerdesBitmap = (0x01 << ((slice * 4) + chan));
            }
            break;
        case MCD_MODE_R10L:
        case MCD_MODE_R10K:
            hostSerdesBitmap = (0x01 << ((slice * 4) + chan));
            retimerMode      = 1;
            noPpmSupport     = 0;
            lineSerdesSpeed  = MCD_10_3125G;
            hostSerdesSpeed  = MCD_10_3125G;
            if (pDev->apCfg[mdioPort].apLaneNum  != 0xFF)
            {
                lineSerdesBitmap = 0;
            }
            else
            {
                lineSerdesBitmap = (0x01 << ((slice * 4) + chan));
            }
            break;
        case MCD_MODE_R1L:
        case MCD_MODE_R1C:
            hostSerdesBitmap = (0x01 << ((slice * 4) + chan));
            retimerMode      = 1;
            noPpmSupport     = 0;
            lineSerdesSpeed  = MCD_1_25G;
            hostSerdesSpeed  = MCD_1_25G;
            if (pDev->apCfg[mdioPort].apLaneNum  != 0xFF)
            {
                lineSerdesBitmap = 0;
            }
            else
            {
                lineSerdesBitmap = (0x01 << ((slice * 4) + chan));
            }
            break;
        case MCD_MODE_P2_5:
            lineSerdesBitmap = (0x01 << ((slice * 4) + chan));
            hostSerdesBitmap = (0x01 << ((slice * 4) + chan));
            retimerMode      = 0;
            noPpmSupport     = 1;
            lineSerdesSpeed  = MCD_3_125G;
            hostSerdesSpeed  = MCD_3_125G;
            break;
        case MCD_MODE_P2_5S:
            lineSerdesBitmap = (0x01 << ((slice * 4) + chan));
            hostSerdesBitmap = (0x01 << ((slice * 4) + chan));
            retimerMode      = 0;
            noPpmSupport     = 1;
            lineSerdesSpeed  = MCD_3_125G;
            hostSerdesSpeed  = MCD_3_125G;
            break;
        case MCD_MODE_P1:
        case MCD_MODE_P1_SGMII:
        case MCD_MODE_P1_BaseX_SGMII:
            retimerMode      = 0;
            noPpmSupport     = 1;
            lineSerdesBitmap = (0x01 << ((slice * 4) + chan));
            hostSerdesBitmap = (0x01 << ((slice * 4) + chan));
            lineSerdesSpeed = MCD_1_25G;
            hostSerdesSpeed = MCD_1_25G;
            break;
        default:
            MCD_DBG_ERROR(
                "$s: incorrect mode selection: %u\n", __func__,
                pDev->portConfig[mdioPort].portMode);
            return MCD_FAIL;
    }

    if (noPpmSupport)
    {
        *noPpmModePtr = pDev->portConfig[mdioPort].noPpmMode;
    }
    else
    {
        *noPpmModePtr = 0;
    }

    if (retimerModePtr)
    {
        *retimerModePtr = retimerMode;
    }
    if (lineSerdesSpeedPtr)
    {
        *lineSerdesSpeedPtr = lineSerdesSpeed;
    }
    if (hostSerdesSpeedPtr)
    {
        *hostSerdesSpeedPtr = hostSerdesSpeed;
    }
    if (lineSerdesBitmapPtr)
    {
        *lineSerdesBitmapPtr = lineSerdesBitmap;
    }
    if (hostSerdesBitmapPtr)
    {
        *hostSerdesBitmapPtr = hostSerdesBitmap;
    }

    if (pDev->laneSteeringCfg.laneSteeringEnable)
    {
        *hostSerdesBitmapPtr = 0;
    }

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdPortPollingLinkStatusStart
  *******************************************************************************/
MCD_STATUS mcdPortPollingLinkStatusStart
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort
)
{
    MCD_BOOL          retimerMode;
    MCD_SERDES_SPEED  lineSerdesSpeed;
    MCD_SERDES_SPEED  hostSerdesSpeed;
    MCD_U16           lineSerdesBitmap;
    MCD_U16           hostSerdesBitmap;
    MCD_U16           i;
    MCD_U16           onePortBitmap;
    MCD_NO_PPM_MODE   noPpmMode;
    MCD_CONFIDENCE_INTERVAL_PARAMS_OVERRIDE  confidenceInterval;
    MCD_LINE_SIDE_EO_TH_OVERRIDE             eoThreshold;

    ATTEMPT(mcdPortPollingParamsGet(
        pDev, mdioPort, &retimerMode,
        &lineSerdesSpeed, &hostSerdesSpeed,
        &lineSerdesBitmap, &hostSerdesBitmap, &noPpmMode));

    /* fill confidince interval and EO data base */
    confidenceInterval.lfLowThreshold = pDev->calibrationCfg[mdioPort].lfLowThreshold;
    confidenceInterval.lfHighThreshold = pDev->calibrationCfg[mdioPort].lfHighThreshold;
    confidenceInterval.hfThreshold = pDev->calibrationCfg[mdioPort].hfThreshold;
    eoThreshold.minEyeThreshold = pDev->calibrationCfg[mdioPort].minEyeThreshold;
    eoThreshold.maxEyeThreshold = pDev->calibrationCfg[mdioPort].maxEyeThreshold;


    if (retimerMode == 0)
    {
        /* PCS mode */
        ATTEMPT(mcdPortPollingLinkStatusStartIpc(
            pDev, mdioPort, retimerMode, MCD_FALSE,
            (MCD_U16)lineSerdesSpeed, (MCD_U16)hostSerdesSpeed,
            lineSerdesBitmap, hostSerdesBitmap, (MCD_U16)noPpmMode, pDev->calibrationCfg[mdioPort].calibrationMode,
                    pDev->calibrationCfg[mdioPort].calibrationAlgorithm,
            &confidenceInterval, &eoThreshold));
    }
    else
    {
        /* Retimer mode Port per serdes pair */
        for (i = 0; (i < 8); i++)
        {
            onePortBitmap = (1 << i);
            if (onePortBitmap & lineSerdesBitmap)
            {
                ATTEMPT(mcdPortPollingLinkStatusStartIpc(
                    pDev, i /*mdioPort*/, retimerMode, MCD_FALSE,
                    (MCD_U16)lineSerdesSpeed, (MCD_U16)hostSerdesSpeed,
                    onePortBitmap/*lineSerdesBitmap*/,
                    onePortBitmap/*hostSerdesBitmap*/,
                            (MCD_U16)noPpmMode, pDev->calibrationCfg[mdioPort].calibrationMode,
                    pDev->calibrationCfg[mdioPort].calibrationAlgorithm, &confidenceInterval, &eoThreshold));
            }
        }
    }

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdPortPollingLinkStatusStop
  *******************************************************************************/
MCD_STATUS mcdPortPollingLinkStatusStop
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort
)
{
    MCD_BOOL          retimerMode;
    MCD_SERDES_SPEED  lineSerdesSpeed;
    MCD_SERDES_SPEED  hostSerdesSpeed;
    MCD_U16           lineSerdesBitmap;
    MCD_U16           hostSerdesBitmap;
    MCD_U16           i;
    MCD_U16           onePortBitmap;
    MCD_NO_PPM_MODE   noPpmMode;

    ATTEMPT(mcdPortPollingParamsGet(
        pDev, mdioPort, &retimerMode,
        &lineSerdesSpeed, &hostSerdesSpeed,
        &lineSerdesBitmap, &hostSerdesBitmap, &noPpmMode));

    if (retimerMode == 0)
    {
        /* PCS mode */
        ATTEMPT(mcdPortPollingLinkStatusStopIpc(
            pDev, mdioPort));
    }
    else
    {
        /* Retimer mode Port per serdes pair */
        for (i = 0; (i < 8); i++)
        {
            onePortBitmap = (1 << i);
            if (onePortBitmap & (lineSerdesBitmap | hostSerdesBitmap))
            {
                ATTEMPT(mcdPortPollingLinkStatusStopIpc(
                    pDev, i /*mdioPort*/));
            }
        }
    }

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdPortSerdesDfeConfig_noSignalCheck
  *******************************************************************************/
MCD_STATUS mcdPortSerdesDfeConfig_noSignalCheck
(
    IN MCD_DEV_PTR       pDev,
    IN MCD_U16           mdioPort,
    IN MCD_DFE_MODE      dfeMode,
    IN MCD_BOOL          configIfRetimerMode,
    IN MCD_BOOL          configIfPcsMode,
    IN MCD_BOOL          configHostSide,
    IN MCD_BOOL          configLineSide
)
{
    MCD_BOOL          retimerMode;
    MCD_U16           lineSerdesBitmap;
    MCD_U16           hostSerdesBitmap;
    MCD_SERDES_SPEED  hostSerdesSpeed;
    MCD_SERDES_SPEED  lineSerdesSpeed;
    MCD_U8            i;
    MCD_U8            serdesNum;
    MCD_NO_PPM_MODE   noPpmMode;

    ATTEMPT(mcdPortPollingParamsGet(
        pDev, mdioPort, &retimerMode,
        &lineSerdesSpeed, &hostSerdesSpeed,
        &lineSerdesBitmap, &hostSerdesBitmap, &noPpmMode));
    if ((!configIfRetimerMode) && retimerMode) return MCD_OK;
    if ((! configIfPcsMode) && (! retimerMode)) return MCD_OK;
    if (configHostSide)
    {
        for (i = 0; (i < 8); i++)
        {
            if (hostSerdesSpeed == MCD_1_25G)
            {
                dfeMode = MCD_DFE_ICAL_VSR;
            }
            if (((1 << i) & hostSerdesBitmap) == 0) continue;
            serdesNum = i + 8;
            ATTEMPT(mcdSerdesDfeConfig/*mcdSerdesDfeConfig_noSignalCheck*/(pDev, serdesNum, dfeMode));
        }
    }
    if (configLineSide)
    {
        for (i = 0; (i < 8); i++)
        {
            if (lineSerdesSpeed == MCD_1_25G)
            {
                dfeMode = MCD_DFE_ICAL_VSR;
            }
            if (((1 << i) & lineSerdesBitmap) == 0) continue;
            serdesNum = i;
            ATTEMPT(mcdSerdesDfeConfig/*mcdSerdesDfeConfig_noSignalCheck*/(pDev, serdesNum, dfeMode));
        }
    }

    return MCD_OK;
}

#else
/*******************************************************************************
 MCD_STATUS mcdSquelchRxClockParamsSet - store parameters in CM3 DB
*******************************************************************************/
MCD_STATUS mcdSquelchRxClockParamsSet
(
    MCD_U32                     phyPortNum,
    MCD_U32                     portMode,
    MCD_RX_CLOCK_CTRL_TYPE      clckCtrl
)
{
    MCD_U16 slice;

    slice = phyPortNum/ MCD_MAX_CHANNEL_NUM_PER_SLICE;

    mcdDevDb.rxCloclControl[slice].phyPortNum = phyPortNum;
    mcdDevDb.portConfig[phyPortNum].portMode = portMode;
    mcdDevDb.rxCloclControl[slice].clckCtrl = clckCtrl;
    return MCD_OK;
}

void mcdSquelchRxClockImplement(unsigned short slice)
{
    MCD_U16 chan,i,lanesNum;

    switch (mcdDevDb.rxCloclControl[slice].clckCtrl)
    {
    case MCD_RCLK_CTRL0:
        mcdHwSetPhyRegField32bit(&mcdDevDb, DONT_CARE, RUNIT_RFU_MPP_Control_0_1_REGISTER, 0, 4, 0);
        break;
    case MCD_RCLK_CTRL1:
        mcdHwSetPhyRegField32bit(&mcdDevDb, DONT_CARE, RUNIT_RFU_MPP_Control_0_1_REGISTER, 4, 4, 0);
        break;
    case MCD_RCLK_CTRL2:
        mcdHwSetPhyRegField32bit(&mcdDevDb, DONT_CARE, RUNIT_SOC_MISC_INTERRUPT_OUT_CONTROL, 0, 1, 0);
        break;
    default:
        tfp_printf(" mcdSquelchRxClockImplement failed %d \n", mcdDevDb.rxCloclControl[slice].clckCtrl);
    }

       /* disable interrupt on all port lanes */
    lanesNum = mcdPortModeGetLanesNum(mcdDevDb.portConfig[mcdDevDb.rxCloclControl[slice].phyPortNum].portMode,MCD_LINE_SIDE);
    chan = CHAN_IN_SLICE_NUM(mcdDevDb.rxCloclControl[slice].phyPortNum);
    for (i = 0; i < lanesNum; i++)
    {
        mcdHwSetPhyRegField32bit(&mcdDevDb, DONT_CARE, (UMAC_INTERRUPT_LINE_REG_ADDR(UMAC_INTERRUPT_clrintenable(slice, 0))) ,(8 + chan + i), 1, 1);
    }
}
#endif


/**
* @internal mcdClearSerdesSignalLostIntCause function
* @endinternal
*
* @brief   Clear status of Serdes Signal Lost Interrupt.
*
* @param[in] pDev                     - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] host_or_line             - the side of port (host or line)
* @param[in] slice                    -  0..1
* @param[in] channel                  -  0..3
*
* @retval MCD_OK                   - on success
* @retval MCD_FAIL                 - on error
*/
MCD_STATUS mcdClearSerdesSignalLostIntCause
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U32 host_or_line,
    IN MCD_U32 slice,
    IN MCD_U32 channel
)
{
#ifndef ASIC_SIMULATION
    MCD_U32  regAddr;
    MCD_U32  bitIndex;
    MCD_U32  regData;

    if (slice >= MCD_MAX_SLICE_NUM)
    {
        MCD_DBG_ERROR("mcdClearSerdesSignalLostIntCause: slice number is out of range\n");
        return MCD_FAIL;
    }
    if (channel >= MCD_MAX_CHANNEL_NUM_PER_SLICE)
    {
        MCD_DBG_ERROR("mcdClearSerdesSignalLostIntCause: channel number is out of range\n");
        return MCD_FAIL;
    }
    if ((host_or_line != MCD_HOST_SIDE) && (host_or_line != MCD_LINE_SIDE))
    {
        MCD_DBG_ERROR("mcdClearSerdesSignalLostIntCause: host_or_line is invalid\n");
        return 0;
    }
    regAddr = UMAC_INTERRUPT_intclr(slice, 0/*_reg_idx*/);
    if (host_or_line == MCD_LINE_SIDE)
    {
        regAddr = UMAC_INTERRUPT_LINE_REG_ADDR(regAddr);
    }
    bitIndex = (8 + channel);
    regData  = (1 << bitIndex);
    return mcdHwXmdioWrite32bit(
        pDev, 0/*mdioPort*/, regAddr, regData);
#else /* ASIC_SIMULATION */
    return MCD_OK;
#endif /* ASIC_SIMULATION */
}

/**
* @internal mcdGetSerdesSignalLostIntCause function
* @endinternal
*
* @brief   Get status of Serdes Signal Lost Interrupt.
*
* @param[in] pDev                     - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] host_or_line             - the side of port (host or line)
* @param[in] slice                    -  0..1
* @param[in] channel                  -  0..3
*
* @param[out] status                   - pointer to  of interrupt (0 - no signal lost or 1 - signal lost)
*
* @retval MCD_OK                   - on success
* @retval MCD_FAIL                 - on error
*/
MCD_STATUS mcdGetSerdesSignalLostIntCause
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U32 host_or_line,
    IN  MCD_U32 slice,
    IN  MCD_U32 channel,
    OUT MCD_U32 *status
)
{
#ifndef ASIC_SIMULATION
    MCD_U32  regAddr;
    MCD_U32  bitIndex;
    MCD_U32  regData;

    if (slice >= MCD_MAX_SLICE_NUM)
    {
        MCD_DBG_ERROR("mcdGetSerdesSignalLostIntCause: slice number is out of range\n");
        return MCD_FAIL;
    }
    if (channel >= MCD_MAX_CHANNEL_NUM_PER_SLICE)
    {
        MCD_DBG_ERROR("mcdGetSerdesSignalLostIntCause: channel number is out of range\n");
        return MCD_FAIL;
    }
    if ((host_or_line != MCD_HOST_SIDE) && (host_or_line != MCD_LINE_SIDE))
    {
        MCD_DBG_ERROR("mcdGetSerdesSignalLostIntCause: host_or_line is invalid\n");
        return 0;
    }
    /* inerrupt raw status bits rised also when interrupt disabled */
    regAddr = UMAC_INTERRUPT_intraw(slice, 0/*_reg_idx*/);
    if (host_or_line == MCD_LINE_SIDE)
    {
        regAddr = UMAC_INTERRUPT_LINE_REG_ADDR(regAddr);
    }
    bitIndex = (8 + channel);
    ATTEMPT(mcdHwXmdioRead32bit(
        pDev, 0/*mdioPort*/, regAddr, &regData));
    *status = ((regData >> bitIndex) & 1);
#endif /* ASIC_SIMULATION */
    return MCD_OK;
}

/**
* @internal mcdCheckSerdesSignalStability function
* @endinternal
*
* @brief   Check Serdes Signal Stability.
*
* @param[in] pDev                     - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] host_or_line             - the side of port (host or line)
* @param[in] slice                    -  0..1
* @param[in] channel                  -  0..3
* @param[in] testTimeMs               - time of period without signal lost in milliseconds.
*
* @param[out] status                   - pointer to  of interrupt (0 - signal not stable or 1 - signal stable)
*
* @retval MCD_OK                   - on success
* @retval MCD_FAIL                 - on error
*/
MCD_STATUS mcdCheckSerdesSignalStability
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U32 host_or_line,
    IN  MCD_U32 slice,
    IN  MCD_U32 channel,
    IN  MCD_U32 testTimeMs,
    OUT MCD_U32 *status
)
{
#ifndef ASIC_SIMULATION
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    MCD_U16         sAddr;
    MCD_BOOL        liveOk;
    MCD_U32         signalLost = 0;
    /* this calculation is a must in order to use the covert logical to physical serdes */
    MCD_U32         logicalSerdesNum = channel + (slice*4);
    if (host_or_line == MCD_HOST_SIDE)
    {
        logicalSerdesNum = logicalSerdesNum + MCD_HOST_SIDE_START_SERDES_NUMBER;
    }
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(logicalSerdesNum,channel);
    if (host_or_line == MCD_HOST_SIDE)
    {
        channel = channel - (slice*4) - MCD_HOST_SIDE_START_SERDES_NUMBER;
    }
    else
    {
        channel = channel - (slice*4);
    }
    ATTEMPT(mcdClearSerdesSignalLostIntCause(
        pDev, host_or_line, slice, channel));
    sAddr = (MCD_U16)MCD_SERDES_LANE_SBUS_ADDR(host_or_line, slice, channel);
    liveOk = avago_serdes_get_signal_ok_live(pSerdesDev, sAddr);
    if (liveOk == 0)
    {
        *status = 0;
        return MCD_OK;
    }
    mcdWrapperMsSleep(testTimeMs);
    ATTEMPT(mcdGetSerdesSignalLostIntCause(
        pDev, host_or_line, slice, channel, &signalLost));
    *status = (signalLost ? 0 : 1);
#endif /* ASIC_SIMULATION */
    return MCD_OK;
}
/**
* @internal mcdTryLockHwSemaphore function
* @endinternal
*
* @brief   Lock HW semaphore if it is avalible.
*
* @param[in] pDev                     - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] semaphore_id             - semaphore id 0..127
* @param[in] event_id                 - event id 0..254
*
* @retval MCD_OK                   - on success
* @retval MCD_PENDING              - semaphore locked by other event
* @retval MCD_FAIL                 - on error
*/
MCD_STATUS mcdTryLockHwSemaphore
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U32 semaphore_id,
    IN  MCD_U32 event_id
)
{
#ifndef ASIC_SIMULATION
    MCD_U32 regAddr;
    MCD_U32 readData;
    if (semaphore_id > 127)
    {
        MCD_DBG_ERROR("mcdTryLockHwSemaphore: semaphore_id more then 127\n");
        return MCD_FAIL;
    }
    if (event_id > 254)
    {
        MCD_DBG_ERROR("mcdTryLockHwSemaphore: event_id more then 254\n");
        return MCD_FAIL;
    }
    regAddr = REG_ADDR_HW_SEMAPHORE_TABLE_BASE + (4 * semaphore_id);
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0/*mdioPort*/, regAddr, event_id));
    ATTEMPT(mcdHwXmdioRead32bit(pDev, 0/*mdioPort*/, regAddr, &readData));
    return ((event_id == readData) ? MCD_OK : MCD_PENDING);
#else /* ASIC_SIMULATION */
    return MCD_OK;
#endif /* ASIC_SIMULATION */
}

/**
* @internal mcdLockHwSemaphore function
* @endinternal
*
* @brief   Lock HW semaphore.
*
* @param[in] pDev                     - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] semaphore_id             - semaphore id 0..127
* @param[in] event_id                 - event id 0..254
*
* @retval MCD_OK                   - on success
* @retval MCD_PENDING              - semaphore locked by other event
* @retval MCD_FAIL                 - on error
*/
MCD_STATUS mcdLockHwSemaphore
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U32 semaphore_id,
    IN  MCD_U32 event_id
)
{
#ifndef ASIC_SIMULATION
    MCD_U32 regAddr;
    MCD_U32 readData;
    if (semaphore_id > 127)
    {
        MCD_DBG_ERROR("mcdLockHwSemaphore: semaphore_id more then 127\n");
        return MCD_FAIL;
    }
    if (event_id > 254)
    {
        MCD_DBG_ERROR("mcdLockHwSemaphore: event_id more then 254\n");
        return MCD_FAIL;
    }
    regAddr = REG_ADDR_HW_SEMAPHORE_TABLE_BASE + (4 * semaphore_id);

    do {
        ATTEMPT(mcdHwXmdioWrite32bit(
            pDev, 0/*mdioPort*/, regAddr, event_id));
        ATTEMPT(mcdHwXmdioRead32bit(
            pDev, 0/*mdioPort*/, regAddr, &readData));
    } while (event_id != readData);

#endif /* ASIC_SIMULATION */

   return MCD_OK;
}

/**
* @internal mcdUnlockHwSemaphore function
* @endinternal
*
* @brief   Unock HW semaphore.
*
* @param[in] pDev                     - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] semaphore_id             - semaphore id 0..127
*
* @retval MCD_OK                   - on success
* @retval MCD_FAIL                 - on error
*/
MCD_STATUS mcdUnlockHwSemaphore
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U32 semaphore_id
)
{
#ifndef ASIC_SIMULATION
    MCD_U32 regAddr;
    if (semaphore_id > 127)
    {
        MCD_DBG_ERROR("mcdGetHwSemaphore: semaphore_id more then 127\n");
        return MCD_FAIL;
    }
    regAddr = REG_ADDR_HW_SEMAPHORE_TABLE_BASE + (4 * semaphore_id);
    ATTEMPT(mcdHwXmdioWrite32bit(
        pDev, 0/*mdioPort*/, regAddr, 0xFF));
#endif /* ASIC_SIMULATION */
    return MCD_OK;
}

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************************
 MCD_STATUS  mcdPowerConsumptionReduce
   enable/disable  MACSEC
*******************************************************************************/
MCD_STATUS  mcdPowerConsumptionReduce
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_BOOL    action
)
{
    if (action)
    {
        /*  MACSEC clock gating in slice 0 */
        ATTEMPT(mcdClockGatingControl(pDev,MCD_MACSEC_CLOCK_GATE,0,DONT_CARE,MCD_FALSE));
        /*  MACSEC clock gating in slice 1 */
        ATTEMPT(mcdClockGatingControl(pDev,MCD_MACSEC_CLOCK_GATE,4,DONT_CARE,MCD_FALSE));
        /* disable  MACSEC */
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, 0, RUNIT_SOC_MISC_MACSEC_CONFIGURATION, 0, 2, 3));
    }
    else
    {
        /*  MACSEC clock gating in slice 0 */
        ATTEMPT(mcdClockGatingControl(pDev,MCD_MACSEC_CLOCK_GATE,0,DONT_CARE,MCD_TRUE));
        /*  MACSEC clock gating in slice 1 */
        ATTEMPT(mcdClockGatingControl(pDev,MCD_MACSEC_CLOCK_GATE,4,DONT_CARE,MCD_TRUE));
        /* enable  MACSEC */
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, 0, RUNIT_SOC_MISC_MACSEC_CONFIGURATION, 0, 2, 0));
    }

    return MCD_OK;
}
#endif /*#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3*/
/**
* @internal mcdGetHwTimestamp function
* @endinternal
*
* @brief   Get HW timestamp.
*
* @param[in] pDev                     - pointer to MCD_DEV initialized by mcdInitDriver() call
*                                       Timestamp value in clocks.
*/
MCD_STATUS mcdGetHwTimestamp
(
    IN  MCD_DEV_PTR pDev
)
{
    MCD_U32 data = 0;
#ifndef ASIC_SIMULATION
    MCD_U32 regAddr;

    /* read something to cause latching of access time in TIMESTAMP register */
    /* TIMESTAMP register reading does not cause updatinig of its contents   */
    regAddr = REG_ADDR_MG_DEV_ID;
    if (MCD_OK != mcdHwXmdioRead32bit(
        pDev, 0/*mdioPort*/, regAddr, &data))
    {
        MCD_DBG_ERROR("mcdGetHwTimestamp: mcdHwXmdioRead32bit error\n");
        return 0;
    }
    /* read latched access time from TIMESTAMP register */
    regAddr = REG_ADDR_HW_LAST_ACCESS_TIMESTAMP;
    if (MCD_OK != mcdHwXmdioRead32bit(
        pDev, 0/*mdioPort*/, regAddr, &data))
    {
        MCD_DBG_ERROR("mcdGetHwTimestamp: mcdHwXmdioRead32bit error\n");
        return 0;
    }
#endif /* ASIC_SIMULATION */
    return data;
}

/*******************************************************************
 MCD_STATUS mcdPortModeVectorToPortMode
   returns portMode that mach the Port vector (for AP port), get the fastest mode.

#define MCD_AN_1000BASE_KX                            0x0001
#define MCD_AN_10GBase_KX4                            0x0002
#define MCD_AN_10GBase_KR                             0x0004
#define MCD_AN_40GBASE_KR4                            0x0008
#define MCD_AN_40GBASE_CR4                            0x0010
#define MCD_AN_100GBASE_CR10                          0x0020
#define MCD_AN_100GBASE_KP4                           0x0040
#define MCD_AN_100GBASE_KR4                           0x0080
#define MCD_AN_100GBASE_CR4                           0x0100
#define MCD_AN_25GBase_KR1S                           0x0200
#define MCD_AN_25GBASE_KCR                            0x0400
#define MCD_AN_25GBase_KR1_CONSORTIUM                 0x0800
#define MCD_AN_25GBase_CR1_CONSORTIUM                 0x1000
#define MCD_AN_50GBase_KR2_CONSORTIUM                 0x2000
#define MCD_AN_50GBase_CR2_CONSORTIUM                 0x4000
*******************************************************************/
MCD_STATUS mcdPortModeVectorToPortMode
(
    IN  MCD_U32     modesVector,
    OUT MCD_OP_MODE *portModePtr
)
{
    if (modesVector & (MCD_AN_100GBASE_KP4| MCD_AN_100GBASE_KR4| MCD_AN_100GBASE_CR4))
    {
        *portModePtr = MCD_MODE_P100C;
    }
    else if (modesVector & (MCD_AN_50GBase_CR2_CONSORTIUM| MCD_AN_50GBase_KR2_CONSORTIUM))
    {
        *portModePtr = MCD_MODE_P50R2L;
    }
    else if (modesVector & (MCD_AN_40GBASE_KR4| MCD_AN_40GBASE_CR4))
    {
        *portModePtr = MCD_MODE_P40C;
    }
    else if (modesVector & (MCD_AN_25GBase_KR1S| MCD_AN_25GBASE_KCR| MCD_AN_25GBase_KR1_CONSORTIUM | MCD_AN_25GBase_CR1_CONSORTIUM))
    {
        *portModePtr = MCD_MODE_P25L;
    }
    else if (modesVector & (MCD_AN_10GBase_KR))
    {
        *portModePtr = MCD_MODE_P10L;
    }
    else
    {
        *portModePtr = MCD_MODE_P1;
    }
    return MCD_OK;
}

/**
* @internal mcdForceOutputLocalFaults function
* @endinternal
*
* @brief   Start/Stop trasnmiting local faults
*
* @param[in] pDev                     - pointer to MCD_DEV
* @param[in] mdioPort                 - mdioPort
* @param[in] host_or_line             - side
* @param[in] serdesSpeed              - serdesSpeed
* @param[in] outputEnable             - enable/disable outputing
*       Local Faults.
*/
MCD_STATUS mcdForceOutputLocalFaults
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U16 mdioPort,
    IN  MCD_U16 host_or_line,
    IN  MCD_SERDES_SPEED serdesSpeed,
    IN  MCD_BOOL outputEnable
)
{
    MCD_U16 slice;
    MCD_U16 chan;

    if (pDev == NULL)
    {
        MCD_DBG_ERROR("Dvice Pointer is NULL\n");
        return MCD_BAD_PTR;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan = CHAN_IN_SLICE_NUM(mdioPort);

    /* TBD - the register that transmit local fault does not support 1G, need
       to consider other solution for 1G */
    if (serdesSpeed != MCD_1_25G)
    {
        if (host_or_line == MCD_HOST_SIDE)
        {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_MCPCS_Debug_Control2(slice, chan), 13, 2, 2*outputEnable));
        }
        else
        {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_MCPCS_LINE_REG_ADDR(UMAC_MCPCS_Debug_Control2(slice, chan)), 13, 2, 2*outputEnable));
        }
    }

    return MCD_OK;

}

/**
* @internal mcdLowSpeedANEnable function
* @endinternal
*
* @brief   Enable/Disable Auto Negotiation for 1G (Low speed) port mode.
*
* @param[in] pDev                   - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] mdioPort               - MDIO port, 0-7
* @param[in] host_or_line           - which interface to be modified, MCD_HOST_SIDE or MCD_LINE_SIDE
* @param[in] anEnable               - 1 for AN enable, 0 for disable
*
* @retval MCD_OK                    - on success.
* @retval MCD_FAIL                  - on failure
*
*/
MCD_STATUS mcdLowSpeedANEnable
(
    IN  MCD_DEV_PTR     pDev,
    IN  MCD_U16         mdioPort,
    IN  MCD_U16         host_or_line,
    IN  MCD_BOOL        anEnable
)
{
    MCD_U16     slice;
    MCD_U16     chan;

    if (pDev == NULL)
    {
        MCD_DBG_ERROR("%s: Device Pointer is NULL\n", __func__);
        return MCD_BAD_PTR;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);

    if (host_or_line == MCD_LINE_SIDE)
    {
        chan |= 4;
    }

    if (anEnable)
    {
        /* For 1G AN mode, modifying linktimer value to match clk rate of 852MHz */
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_LSMCPCS_lnktimer(slice, chan), 0, 16, 0x140));
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_LSMCPCS_lnktimer2(slice, chan), 0, 8, 0x82));

        /* Enable Auto Negotiation */
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_LSMCPCS_ctrl(slice, chan), 0, 1, MCD_TRUE));
    }
    else
    {
        /* fall back linktimer to default */
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_LSMCPCS_lnktimer(slice, chan), 0, 16, 0x12D0));
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_LSMCPCS_lnktimer2(slice, chan), 0, 8, 0x13));

        /* Disable Auto Negotiation */
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_LSMCPCS_ctrl(slice, chan), 0, 1, MCD_FALSE));
    }

    return MCD_OK;
}

/**
* @internal mcdLowSpeedANEnableGet function
* @endinternal
*
* @brief   Read status (Enabled/Disabled) of ANenable for 1G (Low speed) port mode.
*
* @param[in] pDev                   - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] mdioPort               - MDIO port, 0-7
* @param[in] host_or_line           - which interface to be monitored, MCD_HOST_SIDE or MCD_LINE_SIDE
* @param[out] anEnableSts           - Read ANenable status, 1=AN is Enabled, 0=AN Disabled.
*
* @retval MCD_OK                    - on success.
* @retval MCD_FAIL                  - on failure
*
*/
MCD_STATUS mcdLowSpeedANEnableGet
(
    IN  MCD_DEV_PTR     pDev,
    IN  MCD_U16         mdioPort,
    IN  MCD_U16         host_or_line,
    OUT MCD_U32         *anEnableSts
)
{
    MCD_U16     slice;
    MCD_U16     chan;

    if (pDev == NULL)
    {
        MCD_DBG_ERROR("%s: Device Pointer is NULL\n", __func__);
        return MCD_BAD_PTR;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);

    if (host_or_line == MCD_LINE_SIDE)
    {
        chan |= 4;
    }

    /* Read ANenable status */
    ATTEMPT(mcdHwGetPhyRegField32bit(pDev, mdioPort, UMAC_LSMCPCS_ctrl(slice, chan), 0, 1, anEnableSts));

    return MCD_OK;
}

/**
* @internal mcdLowSpeedANRestart function
* @endinternal
*
* @brief   Restarting AN will enable ANenable bit in case it is disabled (or) if ANenable bit is already
*          set then just restart AN state machine.
*
* @param[in] pDev                   - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] mdioPort               - MDIO port, 0-7
* @param[in] host_or_line           - which interface to be monitored, MCD_HOST_SIDE or MCD_LINE_SIDE
*
* @retval MCD_OK                    - on success.
* @retval MCD_FAIL                  - on failure
*
*/
MCD_STATUS mcdLowSpeedANRestart
(
    IN  MCD_DEV_PTR     pDev,
    IN  MCD_U16         mdioPort,
    IN  MCD_U16         host_or_line
)
{
    MCD_U16     slice;
    MCD_U16     chan;
    MCD_U32     data;

    if (pDev == NULL)
    {
        MCD_DBG_ERROR("%s: Device Pointer is NULL\n", __func__);
        return MCD_BAD_PTR;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);

    if (host_or_line == MCD_LINE_SIDE)
    {
        chan |= 4;
    }

    /* Read status of ANenable bit */
    ATTEMPT(mcdHwGetPhyRegField32bit(pDev, mdioPort, UMAC_LSMCPCS_ctrl(slice, chan), 0, 1, &data));
    /* I`f ANenable is disabled, first Enable ANenable bit */
    if (!data)
    {
        ATTEMPT(mcdLowSpeedANEnable(pDev, mdioPort, host_or_line, MCD_TRUE));
    }

    /* Restart AN state machine. Note, this bit is self cleared */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, mdioPort, UMAC_LSMCPCS_ctrl(slice, chan), 1, 1, MCD_TRUE));

    return MCD_OK;
}

/**
* @internal mcdLowSpeedANDoneGet function
* @endinternal
*
* @brief   Read the status of AN done bit.
*
* @param[in] pDev                   - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] mdioPort               - MDIO port, 0-7
* @param[in] host_or_line           - which interface to be monitored, MCD_HOST_SIDE or MCD_LINE_SIDE
* @param[out] anDoneReg             - Read status of AN done.
*
* @retval MCD_OK                    - on success.
* @retval MCD_FAIL                  - on failure
*
*/
MCD_STATUS mcdLowSpeedANDoneGet
(
    IN  MCD_DEV_PTR     pDev,
    IN  MCD_U16         mdioPort,
    IN  MCD_U16         host_or_line,
    OUT MCD_U32         *anDoneReg
)
{
    MCD_U16     slice;
    MCD_U16     chan;

    if (pDev == NULL)
    {
        MCD_DBG_ERROR("%s: Device Pointer is NULL\n", __func__);
        return MCD_BAD_PTR;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);

    if (host_or_line == MCD_LINE_SIDE)
    {
        chan |= 4;
    }

    /* Read status of AN done bit */
    ATTEMPT(mcdHwGetPhyRegField32bit(pDev, mdioPort, UMAC_LSMCPCS_sts(slice, chan), 0, 1, anDoneReg));

    return MCD_OK;
}

/**
* @internal mcdLowSpeedANAdvertSet function
* @endinternal
*
* @brief   Advertise AN capabilities.
*
* @param[in] pDev                   - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] mdioPort               - MDIO port, 0-7
* @param[in] host_or_line           - which interface to be monitored, MCD_HOST_SIDE or MCD_LINE_SIDE
* @param[in] mode                   - Advertise modes of operation
*                                     MCD_BASEX_AD_ASYM_PAUSE 0x0100, i.e Bit-8: Asymm Pause bit
*                                     MCD_BASEX_AD_PAUSE      0x0080, i.e Bit-7: Pause
*                                     MCD_BASEX_AD_1000HDX    0x0040, i.e Bit-6: 1000X Half Duplex
*                                     MCD_BASEX_AD_1000FDX    0x0020, i.e Bit-5: 1000X Full Duplex
*                                     Ex1: To advertise Full duplex and pause, set mode = 0x00A0
*                                     Ex2: To advertise HALF & FULL duplex, set mode = 0x0060
*                                     Ex3: To advertise all of 1000Base-x capability, set mode = 0x01E0
*
* @retval MCD_OK                    - on success.
* @retval MCD_FAIL                  - on failure
*
*/
MCD_STATUS mcdLowSpeedANAdvertSet
(
    IN MCD_DEV_PTR      pDev,
    IN MCD_U16          mdioPort,
    IN MCD_U16          host_or_line,
    IN MCD_U32          mode
)
{
    MCD_U16     slice;
    MCD_U16     chan;
    MCD_U32     data;

    if (pDev == NULL)
    {
        MCD_DBG_ERROR("%s: Device Pointer is NULL\n", __func__);
        return MCD_BAD_PTR;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);

    if (host_or_line == MCD_LINE_SIDE)
    {
        chan |= 4;
    }

    /* check if input mode is valid for Base-X */
    if (mode & ~MCD_BASEX_AD_MASK)
    {
        MCD_DBG_ERROR("%s: Unknown Autoneg advertisement for BASE-X: %u\n", __func__, (mode & ~MCD_BASEX_AD_MASK));
        return MCD_FAIL;
    }

    /* Read AN advertisement register */
    ATTEMPT(mcdHwXmdioRead32bit(pDev, mdioPort, UMAC_LSMCPCS_mradvability(slice, chan), &data));

    /* Modify AN advertisement register */
    data = (((data & 0xF7FF /*override Bit-11(RSVD)=0 for BASE-X */) & ~MCD_BASEX_AD_MASK) | (mode & 0xFFFF));
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, mdioPort, UMAC_LSMCPCS_mradvability(slice, chan), data));

    return MCD_OK;
}

/**
* @internal mcdSetPortModeG21common function
* @endinternal
*
* @brief   Port configuration for G21L/G21SK.
*
* @param[in] pDev                   - pointer to MCD_DEV initialized by mcdInitDriver() call.
* @param[in] mdioPort               - MDIO port 0 to 7.
* @param[in] portMode               - operational mode of port that will be configured.
* @param[in] fecConfigPtr           - pointer to FEC type.
* @param[in] configPtr              - pointer to config DB.
*
* @retval MCD_OK                    - on success.
* @retval MCD_FAIL                  - on failure
* @retval MCD_STATUS_BAD_PARAM      - on incorrect config structure
*
*/
MCD_STATUS mcdSetPortModeG21common
(
    IN  MCD_DEV_PTR               pDev,
    IN  MCD_U16                   mdioPort,
    IN  MCD_OP_MODE               portMode,
    IN  MCD_FEC_TYPE_GET          *fecConfigPtr,
    IN  MCD_MODE_CONFIG_PARAM_PTR configPtr
)
{
    MCD_U8      serdesNum, slice, chan;
    MCD_BOOL    noPpmEnable;

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan = CHAN_IN_SLICE_NUM(mdioPort);

    /* Get noPpm enable state from pDev DB */
    noPpmEnable = pDev->noPpmEn[mdioPort];

    if (configPtr == NULL)
    {
        MCD_DBG_ERROR("%s: Incorrect config structure\n", __func__);
        return MCD_STATUS_BAD_PARAM;
    }

    /* Host side serdes configuration for lane steering mode */
    if (pDev->laneSteeringCfg.laneSteeringEnable)
    {
        for (serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER + chan; serdesNum < (MCD_HOST_SIDE_START_SERDES_NUMBER + chan + 4); serdesNum++)
        {
            ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE, MCD_20_625G, noPpmEnable,
                        (MCD_U32)configPtr->refClk.hsRefClkSel, (MCD_U32)configPtr->refClk.hsRefClkDiv));
            ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE));
        }
    }
    else /* Host side serdes configuration for normal mode */
    {
        for (serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER + chan; serdesNum < (MCD_HOST_SIDE_START_SERDES_NUMBER + chan + 2); serdesNum++)
        {
            ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE, MCD_20_625G, noPpmEnable,
                        (MCD_U32)configPtr->refClk.hsRefClkSel, (MCD_U32)configPtr->refClk.hsRefClkDiv));
            ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE));
        }
    }

    /* Line side serdes configuration */
    for ( serdesNum = 0; serdesNum < 4; serdesNum++)
    {
        ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE, MCD_10_3125G, MCD_FALSE,
                    (MCD_U32)configPtr->refClk.lsRefClkSel, (MCD_U32)configPtr->refClk.lsRefClkDiv));
        ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE));
    }

    /* configure Asic side*/
    ATTEMPT(mcdConfigurePcs40g(pDev, portMode, slice, chan, MCD_BASE_R2, fecConfigPtr->hostFec));
    /* configure Line side */
    ATTEMPT(mcdConfigurePcs40g(pDev, portMode, slice, (chan + 4), MCD_BASE_R4, fecConfigPtr->lineFec));

    return MCD_OK;
}

