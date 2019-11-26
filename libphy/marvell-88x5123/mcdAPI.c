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
This file contains functions and global data for
higher-level functions using MDIO access to perform resets, perform
queries of the phy, etc. that are necessary to control and read
status of the Marvell X5123/EC808 PHY.
********************************************************************/
#include "mcdApiTypes.h"
#include "mcdApiRegs.h"
#include "mcdUtils.h"
#include "mcdHwCntl.h"
#include "mcdDiagnostics.h"
#include "mcdAPI.h"
#include "mcdInitialization.h"
#include "mcdHwSerdesCntl.h"
#include "mcdAPIInternal.h"
#include "mcdInternalCtrlApInitIf.h"
#include "mcdInternalIpcDefs.h"
#include "mcdInternalIpcApis.h"
#include "mcdPortCtrlApLogDefs.h"
#define MAX_WAIT   1000

#define MCD_MASTER_CLOCK_MASK_CNS 0xFF
#define MCD_MAX_SERDES_PER_SLICE 4

#ifndef ASIC_SIMULATION
extern MCD_SERDES_TXRX_LANE_REMAP serdesTxRxLaneRemap[MCD_MAX_PORT_NUM][MCD_MAX_SLICE_NUM];

#endif /* ASIC_SIMULATION */

MCD_STATUS mcdSetSetSerdesElectricalParametersDB
(
    unsigned int        portNum,
    MCD_OP_MODE         portMode,
    MCD_PORT_PER_SERDES_CONFIG_DATA*  paramsPtr
);

MCD_STATUS mcdSetSetSerdesDefaultElectricalParameters
(
    unsigned int        portNum,
    MCD_OP_MODE         portMode
);

MCD_STATUS mcdSetSerdesCtleParametersDB
(
    unsigned int        portNum,
    MCD_OP_MODE         portMode,
    MCD_PORT_PER_SERDES_CTLE_CONFIG_DATA* ctleParamsPtr
);

MCD_STATUS mcdSetSerdesDefaultCtleParameters
(
    unsigned int        portNum,
    MCD_OP_MODE         portMode
);


static int mcdSetModeSelectionExtPortPollingMessageDisable = 0;
static int mcdLaneSteeringServiceCpuDisable = 0;
void mcdSetModeSelectionExtPortPollingMessageDisableSet(int i)
{
    mcdSetModeSelectionExtPortPollingMessageDisable = i;
}

void mcdLaneSteeringServiceCpuDisableSet(int i)
{
    mcdLaneSteeringServiceCpuDisable = i;
}

static int mcdSetModeSelectionExtPortTuningDisable = 0;
void mcdSetModeSelectionExtPortTuningDisableSet(int i)
{
    mcdSetModeSelectionExtPortTuningDisable = i;
}

static MCD_STATUS mcdSetAPModeRetimerSelection
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 portNum,
    IN MCD_OP_MODE portMode,
    IN MCD_MODE_CONFIG_PARAM_PTR configPtr
)
{
    MCD_U8 polarityVector,i;
    MCD_FEC_TYPE_GET apFecSup, apFecReq;
    MCD_OP_MODE newPortMode;

        /* check that portMode in host is with R */
    if ((portMode != MCD_MODE_R100C) &&
        (portMode != MCD_MODE_R40C)  &&
        (portMode != MCD_MODE_R25C)  &&
        (portMode != MCD_MODE_R10K))
    {
        MCD_DBG_ERROR("mcdSetAPModeRetimerSelection: incorrect Ap with retimer portMode: %u\n", portMode);
        return MCD_STATUS_BAD_PARAM;
    }

    ATTEMPT(mcdPortModeVectorToPortMode(configPtr->configApPtr->modeVector,&newPortMode));
    ATTEMPT(mcdPortStop(pDev, portNum, newPortMode/*pDev->portConfig[portNum].portMode*/));

    if (configPtr->configApPtr == NULL)
    {
        MCD_DBG_ERROR("mcdSetAPModeRetimerSelection: incorrect Ap with structure\n");
        return MCD_STATUS_BAD_PARAM;
    }

    polarityVector = 0;
    if (configPtr->configApPtr->configApSerdesPtr != NULL)
    {
        for(i = 0; i < configPtr->configApPtr->configApSerdesPtr->numOfLanes; i++)
        {
            polarityVector |= ((configPtr->configApPtr->configApSerdesPtr->params[i].txPolarity & 1) << (2*i+1)) |
                ((configPtr->configApPtr->configApSerdesPtr->params[i].rxPolarity & 1) << (2*i));
        }
    }
    /* get requested/supported fec mode for LINE_SIDE*/
    MCD_FEC_TYPE_GET_MAC(configPtr->configApPtr->fecSup, apFecSup);
    MCD_FEC_TYPE_GET_MAC(configPtr->configApPtr->fecReq, apFecReq);

    ATTEMPT(mcdSetAutoNegParameters( pDev, portNum, configPtr->configApPtr->laneNum, polarityVector,
                                     configPtr->configApPtr->modeVector, configPtr->configApPtr->fcPause,
                                     configPtr->configApPtr->fcAsmDir, apFecSup.lineFec,
                                     apFecReq.lineFec, configPtr->configApPtr->nonceDis));
    /* configure host side port, line side will be configured also*/
    mcdOneSideSetMode(pDev, portNum, portMode, MCD_HOST_SIDE, MCD_NO_FEC, configPtr);

    return MCD_OK;
}

MCD_STATUS mcdSetDefaultInitDB
(
    IN  MCD_DEV_PTR                    pDev,
    IN  MCD_U16                        mdioPort,
    OUT MCD_MODE_CONFIG_PARAM_PTR      configPtr
)
{
    if (configPtr == NULL)
    {
        MCD_DBG_ERROR("mcdSetDefaultInitDB: incorrect config structure\n");
        return MCD_STATUS_BAD_PARAM;
    }
    else
    {
        mcdMemSet(configPtr, 0, sizeof(MCD_MODE_CONFIG_PARAM));
    }

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdSetDefaultInitDB: device not initialized\n");
        return MCD_FAIL;
    }

    /* Set defaults to DB  */
    configPtr->noPpmMode = MCD_NO_PPM_OFF_MODE;
    configPtr->electricalParamsPtr = NULL;
    configPtr->configApPtr = NULL;
    configPtr->refClk.hsRefClkSel = MCD_PRIMARY_CLK;
    configPtr->refClk.hsRefClkDiv = MCD_REF_CLK_NO_DIV;
    configPtr->refClk.lsRefClkSel = MCD_PRIMARY_CLK;
    configPtr->refClk.lsRefClkDiv = MCD_REF_CLK_NO_DIV;
    configPtr->ctleBiasParams.host = MCD_CTLE_BIAS_NORMAL;
    configPtr->ctleBiasParams.line = MCD_CTLE_BIAS_NORMAL;
    configPtr->ctleParamsPtr = NULL;

    return MCD_OK;
}

 /**
 * @internal mcdSetModeSelectionExt function
 * @endinternal
 *
 * @brief   The main function for configuring all port modes.
 *
 * @param[in]  pDev             - device pointer
 * @param[in]  mdioPort         - port number
 * @param[in]  portMode         - port mode
 * @param[in]  autoNegAdvEnable - Auto-neg enable
 * @param[in]  fecCorrect       - Set FEC mode
 * @param[in]  configPtr        - Electrical and other additional parameters
 *
 * @retval MCD_OK                    - on success.
 * @retval MCD_FAIL                  - on failure
 *
 * @note use like mcdSetModeSelectionExt
 *
 *     ** Capability for AutoNeg advertisment
 *     ** [00:00] Advertisement 1000BASE-KX                            0x0001
 *     ** [01:01] Advertisement 10GBase-KX4                            0x0002
 *     ** [02:02] Advertisement 10GBase-KR                             0x0004
 *     ** [03:03] Advertisement 40GBASE-KR4                            0x0008
 *     ** [04:04] Advertisement 40GBASE-CR4                            0x0010
 *     ** [05:05] Advertisement 100GBASE-CR10                          0x0020
 *     ** [06:06] Advertisement 100GBASE-KP4                           0x0040
 *     ** [07:07] Advertisement 100GBASE-KR4                           0x0080
 *     ** [08:08] Advertisement 100GBASE-CR4                           0x0100
 *     ** [09:09] Advertisement 25GBASE-KR-S or 25GBASE-CR-S           0x0200
 *     ** [10:10] Advertisement 25GBASE-KR or 25GBASE-CR               0x0400
 *     ** [11:11] Advertisement consortium 25GBase KR1                 0x0800
 *     ** [12:12] Advertisement consortium 25GBase CR1                 0x1000
 *     ** [13:13] Advertisement consortium 50GBase KR2                 0x2000
 *     ** [14:14] Advertisement consortium 50GBase CR2                 0x4000
 *     ** [15:15] Reserved
*******************************************************************************/


MCD_STATUS mcdSetModeSelectionExt
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_OP_MODE portMode,
    IN MCD_BOOL autoNegAdvEnable,
    IN MCD_FEC_TYPE fecCorrect,
    IN MCD_MODE_CONFIG_PARAM_PTR configPtr
)
{
    MCD_U8 port,slice,chan, otherSlice;
    MCD_U8 serdesNum;
    MCD_U16 i;
    MCD_U8   serdesLs, serdesHs;
    MCD_NO_PPM_MODE noPpmMode;
    MCD_BOOL noPpmEnable = MCD_FALSE;
    MCD_FEC_TYPE_GET fecConfig;
    MCD_REF_CLK_DIV hsRefClockDiv, lsRefClockDiv;
    MCD_REF_CLK_SEL hsRefClockSel, lsRefClockSel;
    MCD_CTLE_BIAS_VAL hostCtleBiasVal, lineCtleBiasVal;
    MCD_U16 hostLanesNum, lineLanesNum;
    MCD_U8 polarityVector;
    MCD_BOOL updateFromApStc = MCD_FALSE;
    MCD_BOOL laneSteeringEnable;
    MCD_BOOL hostRxTraining = MCD_TRUE;
    MCD_MASTER_SLICE masterSlice = MCD_DUAL_SLICE;
    MCD_U16 otherMdioPort = 0;
    MCD_U16 firstLpbPort = 0;
    MCD_U16 secLpbPort = 0;
    MCD_BOOL slavePortDisabled = MCD_FALSE;
    MCD_SERDES_SPEED  baudrate = MCD_SPEED_NA;
    MCD_BOOL bypassAutoTune = MCD_FALSE;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdSetModeImplement: device not initialized\n");
        return MCD_FAIL;
    }

    ATTEMPT(mcdIsFecParamValid(pDev, mdioPort, portMode, fecCorrect));

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSetModeSelectionExt: incorrect port selection: %u\n", mdioPort);
        return MCD_FAIL;
    }

     slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    /* calculate other Slice for laneSteering mode */
    otherSlice = (slice == 0 ? 1 : 0);

    chan = CHAN_IN_SLICE_NUM(mdioPort);
    /* by default the calibration will be set to default */
    pDev->calibrationCfg[mdioPort].calibrationMode = configPtr->calibrationMode;
    /* by default the calibration algorithm will be confidence interval method */
    pDev->calibrationCfg[mdioPort].calibrationAlgorithm = configPtr->calibrationAlgo;

    /* EO threshold override is applicable only for line side */
    if (configPtr->eyeThresholdPtr != NULL)
    {
        pDev->calibrationCfg[mdioPort].minEyeThreshold = configPtr->eyeThresholdPtr->minEyeThreshold;
        pDev->calibrationCfg[mdioPort].maxEyeThreshold = configPtr->eyeThresholdPtr->maxEyeThreshold;
    }
    else
    {
        pDev->calibrationCfg[mdioPort].minEyeThreshold = MCD_MIN_EYE_TH;
        pDev->calibrationCfg[mdioPort].maxEyeThreshold = MCD_MAX_EYE_TH;
    }

    if (configPtr->confidenceParamsPtr != NULL)
    {
        pDev->calibrationCfg[mdioPort].lfLowThreshold = configPtr->confidenceParamsPtr->lfLowThreshold;
        pDev->calibrationCfg[mdioPort].lfHighThreshold = configPtr->confidenceParamsPtr->lfHighThreshold;
        pDev->calibrationCfg[mdioPort].hfThreshold = configPtr->confidenceParamsPtr->hfThreshold;
    }
    else
    {
        pDev->calibrationCfg[mdioPort].lfLowThreshold = MCD_LF_LOW_TH;
        pDev->calibrationCfg[mdioPort].lfHighThreshold = MCD_LF_HIGH_TH;
        pDev->calibrationCfg[mdioPort].hfThreshold = MCD_HF_TH;
    }

    /* get laneSteering parameters from DB */
    laneSteeringEnable = pDev->laneSteeringCfg.laneSteeringEnable;
    /* if laneSteering mode enabled, initilize relevant parameters */
    if (laneSteeringEnable)
    {
        if (pDev->laneSteeringCfg.reducedRxTraining)
        {
            pDev->calibrationCfg[mdioPort].calibrationMode = MCD_REDUCE_CALIBRATION;
        }
        hostRxTraining = MCD_FALSE;
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
            otherMdioPort = ((masterSlice == MCD_SLICE0) ? (mdioPort + 4) : (mdioPort - 4));
        }
    }
    else
    {
        pDev->laneSteeringCfg.reducedRxTraining = MCD_FALSE;
    }

    pDev->apCfg[mdioPort].options = 0;
    pDev->apCfg[mdioPort].options |= ((autoNegAdvEnable << 2) & MCD_AP_OPTIONS_AN_ADV_ENABLE);
    pDev->apCfg[mdioPort].noPpmMode = (MCD_U8)configPtr->noPpmMode;
    if ((autoNegAdvEnable == MCD_TRUE) && (configPtr->configApPtr != NULL)){
        if (configPtr->configApPtr->modeVector != 0) {
            pDev->apCfg[mdioPort].ctleBiasVal = (MCD_U8)configPtr->configApPtr->ctleBiasVal;
            pDev->apCfg[mdioPort].enSdTuningApRes = configPtr->configApPtr->enSdTuningApRes;
            if (configPtr->configApPtr->g21Mode)
                pDev->apCfg[mdioPort].options |= MCD_AP_OPTIONS_G21_MODE_CNS;
            if (configPtr->configApPtr->g1SgmiiMode)
                pDev->apCfg[mdioPort].options |= MCD_AP_OPTIONS_1G_SGMII_MODE_CNS;
            if (configPtr->configApPtr->retimerEnable == MCD_FALSE) {
                /*Working with AP without retimer - call mcdSetAPModeSelection*/
                return mcdSetAPModeSelection(pDev, mdioPort, configPtr->configApPtr->laneNum, configPtr->configApPtr->modeVector,
                                             configPtr->configApPtr->fcPause, configPtr->configApPtr->fcAsmDir,
                                             configPtr->configApPtr->fecSup,configPtr->configApPtr->fecReq,
                                             configPtr->configApPtr->nonceDis, configPtr->configApPtr->configApSerdesPtr,
                                             configPtr->configApPtr->apEnable);

            }
            else
            {
                return mcdSetAPModeRetimerSelection(pDev, mdioPort, portMode, configPtr);

            }
        }
        else
        {/* update lane number for old api*/
            updateFromApStc = MCD_TRUE;
        }
    }

    /* non AP modes or AP with single speed */
    ATTEMPT(mcdPortStop(pDev, mdioPort, portMode));

    if (updateFromApStc) {
        pDev->apCfg[mdioPort].apLaneNum = configPtr->configApPtr->laneNum;
        polarityVector = 0;
        if (configPtr->configApPtr->configApSerdesPtr != NULL)
        {
            for(i = 0; i < configPtr->configApPtr->configApSerdesPtr->numOfLanes; i++)
            {
                polarityVector |= ((configPtr->configApPtr->configApSerdesPtr->params[i].txPolarity & 1) << (2*i+1)) |
                    ((configPtr->configApPtr->configApSerdesPtr->params[i].rxPolarity & 1) << (2*i));
            }
        }
        pDev->apCfg[mdioPort].polarityVector = polarityVector;

    } else if (autoNegAdvEnable == MCD_TRUE) {
        pDev->apCfg[mdioPort].apLaneNum = mdioPort;
    }

    noPpmMode = configPtr->noPpmMode;
    noPpmEnable = ((noPpmMode > MCD_NO_PPM_OFF_MODE) ? MCD_TRUE : MCD_FALSE);
    pDev->noPpmEn[mdioPort]= noPpmEnable;

    /* assigning reference clock parameters for host and line */
    hsRefClockDiv = configPtr->refClk.hsRefClkDiv;
    lsRefClockDiv = configPtr->refClk.lsRefClkDiv;
    lsRefClockSel = configPtr->refClk.lsRefClkSel;
    hsRefClockSel = configPtr->refClk.hsRefClkSel;

    hostCtleBiasVal = configPtr->ctleBiasParams.host;
    lineCtleBiasVal = configPtr->ctleBiasParams.line;

    if (configPtr->electricalParamsPtr != NULL)
    {
        mcdSetSetSerdesElectricalParametersDB(mdioPort,portMode,configPtr->electricalParamsPtr);
        /* update electrical parameters of other slice port in laneSteering 1 slice mode */
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
                    mcdSetSetSerdesElectricalParametersDB(otherMdioPort, portMode, configPtr->electricalParamsPtr);
                }
            }
        }
    }
    else
    {
        mcdSetSetSerdesDefaultElectricalParameters(mdioPort, portMode);
        /* set electrical default parameters of other slice port in laneSteering 1 slice mode */
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
        /* update CTLE parameters of other slice in laneSteering mode */
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
        /* set default CTLE parameters of other slice in laneSteering mode */
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

    MCD_FEC_TYPE_GET_MAC(fecCorrect, fecConfig);

    pDev->portConfig[mdioPort].fecCorrect = fecCorrect;


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
    lineLanesNum = mcdPortModeGetLanesNum(portMode, MCD_LINE_SIDE);
    for (serdesNum = chan; serdesNum< chan+lineLanesNum; serdesNum++)
    {
        ATTEMPT(mcdSerdesCtleBiasUpdateDB(pDev, MCD_SERDES_NUM(serdesNum,slice), (MCD_U8)lineCtleBiasVal, MCD_LINE_SIDE))
    }

    switch(portMode)
    {
        case MCD_MODE_P100L:
        case MCD_MODE_P100S:
        case MCD_MODE_P100C:
        case MCD_MODE_P100K:
            if (chan != 0) /* 100G  only on chan 0*/
            {
                MCD_DBG_ERROR("mcdSetModeImplement: wrong channel number %u\n", chan);
                return MCD_FAIL;
            }

            /* Setting Serdes speed */
            baudrate = MCD_25_78125G;

            /* power up 4 Host serdeses */
            if (autoNegAdvEnable)
            {
                /* power up 4 Host serdeses */
                 for ( serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER; serdesNum < MCD_HOST_SIDE_START_SERDES_NUMBER + 4; serdesNum++)
                 {
                     ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE, MCD_25_78125G, noPpmEnable, (MCD_U32)hsRefClockSel, (MCD_U32)hsRefClockDiv));
                     ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE));
                 }
                 /* configure Asic side*/
                 ATTEMPT(mcdConfigurePcs100gR4(pDev, portMode, slice, chan, fecConfig.hostFec));
/*
      ** Capability
      ** [00:00] Advertisement 1000BASE-KX                            0x0001
      ** [01:01] Advertisement 10GBase-KX4                            0x0002
      ** [02:02] Advertisement 10GBase-KR                             0x0004
      ** [03:03] Advertisement 40GBASE-KR4                            0x0008
      ** [04:04] Advertisement 40GBASE-CR4                            0x0010
      ** [05:05] Advertisement 100GBASE-CR10                          0x0020
      ** [06:06] Advertisement 100GBASE-KP4                           0x0040
      ** [07:07] Advertisement 100GBASE-KR4                           0x0080
      ** [08:08] Advertisement 100GBASE-CR4                           0x0100
      ** [09:09] Advertisement 25GBASE-KR-S or 25GBASE-CR-S           0x0200
      ** [10:10] Advertisement 25GBASE-KR or 25GBASE-CR               0x0400
      ** [11:11] Advertisement consortium 25GBase KR1                 0x0800
      ** [12:12] Advertisement consortium 25GBase CR1                 0x1000
      ** [13:13] Advertisement consortium 50GBase KR2                 0x2000
      ** [14:14] Advertisement consortium 50GBase CR2                 0x4000
      ** [15:15] Reserved
*/

               /* pDev->apCfg[mdioPort].apLaneNum = mdioPort;*/
                if (portMode == MCD_MODE_P100K)
                {
                    pDev->apCfg[mdioPort].modesVector = MCD_AN_100GBASE_KR4;
                }
                else if (portMode == MCD_MODE_P100C)
                {
                    pDev->apCfg[mdioPort].modesVector = MCD_AN_100GBASE_CR4;

                }
                pDev->apCfg[mdioPort].fecSup = fecConfig.lineFec;
                ATTEMPT( mcdAutoNegPortCtrlStart(pDev, mdioPort,MCD_FALSE));
            }
            else
            {
                for ( serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER; serdesNum < MCD_HOST_SIDE_START_SERDES_NUMBER + 4; serdesNum++)
                {
                    ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE, MCD_25_78125G, noPpmEnable, (MCD_U32)hsRefClockSel, (MCD_U32)hsRefClockDiv));
                    ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE));
                }
                /* power up 4 line serdeses */
                for ( serdesNum = chan ; serdesNum < 4; serdesNum++)
                {
                    ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE, MCD_25_78125G, MCD_FALSE, (MCD_U32)lsRefClockSel, (MCD_U32)lsRefClockDiv));
                    ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE));
                }

                /* set Host side */
                ATTEMPT(mcdConfigurePcs100gR4(pDev, portMode, slice, chan, fecConfig.hostFec));
                /* set line side */
                ATTEMPT(mcdConfigurePcs100gR4(pDev, portMode, slice, (chan + 4), fecConfig.lineFec));
                /* all chans in slice are busy*/

            }
            for (port = 0; port < 4; port++)
                pDev->portConfig[mdioPort + port].portMode = portMode;
            break;
        case MCD_MODE_P40L:
        case MCD_MODE_P40C:
        case MCD_MODE_P40S:
        case MCD_MODE_P40K:
            if (chan != 0) /* only on chan 0*/
            {
                MCD_DBG_ERROR("mcdSetModeImplement: wrong channel number %u\n", chan);
                return MCD_FAIL;
            }

            /* Setting Serdes speed */
            baudrate = MCD_10_3125G;
            if (autoNegAdvEnable)
            {
                 /* power up 4 Host serdeses */
                 for ( serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER; serdesNum < MCD_HOST_SIDE_START_SERDES_NUMBER + 4; serdesNum++)
                 {
                     ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE, MCD_10_3125G, noPpmEnable, (MCD_U32)hsRefClockSel, (MCD_U32)hsRefClockDiv));
                     ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE));
                 }
                 /* configure Asic side*/
                ATTEMPT(mcdConfigurePcs40g(pDev, portMode, slice, chan, MCD_BASE_R4, fecConfig.hostFec));

                /*pDev->apCfg[mdioPort].apLaneNum = mdioPort;*/
                if (portMode == MCD_MODE_P40K)
                {
                    pDev->apCfg[mdioPort].modesVector = MCD_AN_40GBASE_KR4;
                }
                else if (portMode == MCD_MODE_P40C)
                {
                    pDev->apCfg[mdioPort].modesVector = MCD_AN_40GBASE_CR4;
                }
                pDev->apCfg[mdioPort].fecSup = fecConfig.lineFec;

                ATTEMPT( mcdAutoNegPortCtrlStart(pDev, mdioPort,MCD_FALSE));
            }
            else
            {
                /* power up 4 Host serdeses */
                for ( serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER; serdesNum < MCD_HOST_SIDE_START_SERDES_NUMBER + 4; serdesNum++)
                {
                    ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE, MCD_10_3125G, noPpmEnable, (MCD_U32)hsRefClockSel, (MCD_U32)hsRefClockDiv));
                    ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE));
                }
                /* power up 4 Line serdeses */
                for ( serdesNum = 0; serdesNum < 4; serdesNum++)
                {
                    ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE, MCD_10_3125G, MCD_FALSE, (MCD_U32)lsRefClockSel, (MCD_U32)lsRefClockDiv));
                    ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE));
                }

                /* configure Asic side*/
                ATTEMPT(mcdConfigurePcs40g(pDev, portMode, slice, chan, MCD_BASE_R4, fecConfig.hostFec));
                /*configure Line side */
                ATTEMPT(mcdConfigurePcs40g(pDev, portMode, slice, (chan + 4), MCD_BASE_R4, fecConfig.lineFec));

            }
            for (port = 0; port < 4; port++)
                pDev->portConfig[mdioPort + port].portMode = portMode;
            break;
        case MCD_MODE_G21L:
            if ((chan != 0) && (chan != 2))
            {
                MCD_DBG_ERROR("mcdSetModeImplement: wrong channel number %u\n", chan);
                return MCD_FAIL;
            }

            /* Setting Serdes speed */
            baudrate = MCD_20_625G;

            /* Configuration of serdes and PCS block for G21xx mode */
            ATTEMPT(mcdSetPortModeG21common(pDev, mdioPort, portMode, &fecConfig, configPtr));

            for (port = 0; port < 4; port++)
                pDev->portConfig[mdioPort + port].portMode = portMode;

            break;
        case MCD_MODE_G21SK:
            if ((chan != 0) && (chan != 2))
            {
                MCD_DBG_ERROR("mcdSetModeImplement: wrong channel number %u\n", chan);
                return MCD_FAIL;
            }

            /* Setting Serdes speed */
            baudrate = MCD_20_625G;
            
            /* Legacy feature: AN enable and w/(w/o) FC-FEC support on Host/Line/bothSide */
            if (autoNegAdvEnable)
            {
                 /* power up 4 Host serdeses */
                 for ( serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER + chan; serdesNum < MCD_HOST_SIDE_START_SERDES_NUMBER + chan + 2; serdesNum++)
                 {
                     ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE, MCD_20_625G, noPpmEnable, (MCD_U32)hsRefClockSel, (MCD_U32)hsRefClockDiv));
                     ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE));
                 }
                 /* configure Asic side*/
                ATTEMPT(mcdConfigurePcs40g(pDev, portMode, slice, chan, MCD_BASE_R2, fecConfig.hostFec));

                /*pDev->apCfg[mdioPort].apLaneNum = mdioPort;*/
                pDev->apCfg[mdioPort].modesVector = MCD_AN_40GBASE_KR4;
                pDev->apCfg[mdioPort].fecSup = fecConfig.lineFec;

                ATTEMPT( mcdAutoNegPortCtrlStart(pDev, mdioPort, MCD_FALSE));
            }
            else /* New feature: Non-AN and RC-FEC support on Host side only */
            {
                /* Configuration of serdes and PCS block for G21xx mode */
                ATTEMPT(mcdSetPortModeG21common(pDev, mdioPort, portMode, &fecConfig, configPtr));
            }

            for (port = 0; port < 4; port++)
                pDev->portConfig[mdioPort + port].portMode = portMode;

            break;
        case MCD_MODE_P50R2L:
        case MCD_MODE_P50R2S:
            if ((chan != 0) && (chan != 2))
            {
                MCD_DBG_ERROR("mcdSetModeImplement: wrong channel number %u\n", chan);
                return MCD_FAIL;
            }

            /* Setting Serdes speed */
            baudrate = MCD_25_78125G;
            for ( serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER + chan; serdesNum < (MCD_HOST_SIDE_START_SERDES_NUMBER + chan + 2); serdesNum++)
            {
                ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE, MCD_25_78125G, noPpmEnable, (MCD_U32)hsRefClockSel, (MCD_U32)hsRefClockDiv));
                ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE));
            }
            for ( serdesNum = chan; serdesNum < (chan + 2); serdesNum++)
            {
                ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE, MCD_25_78125G, MCD_FALSE, (MCD_U32)lsRefClockSel, (MCD_U32)lsRefClockDiv));
                ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE));
            }
            /* configure Asic side*/
            ATTEMPT(mcdConfigurePcs40g(pDev, portMode, slice, chan, MCD_BASE_R2, fecConfig.hostFec));
            /*configure Line side */
            ATTEMPT(mcdConfigurePcs40g(pDev, portMode, slice, (chan + 4), MCD_BASE_R2, fecConfig.lineFec));
            /* all chans in slice are busy*/

            for (port = 0; port < 2; port++)
                pDev->portConfig[mdioPort + port].portMode = portMode;

            break;
        case MCD_MODE_P40R2L:
        case MCD_MODE_P40R2S:
            if ((chan != 0) && (chan != 2))
            {
                MCD_DBG_ERROR("mcdSetModeImplement: wrong channel number %u\n", chan);
                return MCD_FAIL;
            }

            /* Setting Serdes speed */
            baudrate = MCD_20_625G;
            for ( serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER + chan; serdesNum < (MCD_HOST_SIDE_START_SERDES_NUMBER + chan + 2); serdesNum++)
            {
                ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE, MCD_20_625G, noPpmEnable, (MCD_U32)hsRefClockSel, (MCD_U32)hsRefClockDiv));
                ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE));
            }
            for ( serdesNum = chan; serdesNum < (chan + 2); serdesNum++)
            {
                ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE, MCD_20_625G, MCD_FALSE, (MCD_U32)lsRefClockSel, (MCD_U32)lsRefClockDiv));
                ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(serdesNum,slice), MCD_TRUE));
            }
            /* configure Asic side*/
            ATTEMPT(mcdConfigurePcs40g(pDev, portMode, slice, chan, MCD_BASE_R2, fecConfig.hostFec));
            /*configure Line side */
            ATTEMPT(mcdConfigurePcs40g(pDev, portMode, slice, (chan + 4), MCD_BASE_R2, fecConfig.lineFec));

            for (port = 0; port < 2; port++)
                pDev->portConfig[mdioPort + port].portMode = portMode;

            break;
        case MCD_MODE_P20L:
        case MCD_MODE_P20S:
        case MCD_MODE_P25L:
        case MCD_MODE_P25S:

            /* Setting Serdes speed */
            if ((portMode == MCD_MODE_P25S) || (portMode == MCD_MODE_P25L))
            {
                baudrate = MCD_25_78125G;
            }
            else
            {
                baudrate = MCD_20_625G;
            }

            if (autoNegAdvEnable)
            {
                if ((portMode == MCD_MODE_P20S) || (portMode == MCD_MODE_P20L))
                {
                    MCD_DBG_ERROR("%s: 20G port mode still not supporting AN mode.\n", __func__);
                    return MCD_FAIL;
                }
                /* power up Host serdes */
                ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, baudrate, noPpmEnable, (MCD_U32)hsRefClockSel, (MCD_U32)hsRefClockDiv));
                ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE));
                /* configure Asic side*/
                ATTEMPT(mcdConfigurePcs10_25gR1(pDev, slice, chan, fecConfig.hostFec, (MCD_OP_MODE)baudrate));

                pDev->apCfg[mdioPort].apLaneNum = mdioPort;
                pDev->apCfg[mdioPort].fecSup = fecConfig.lineFec;

                if (portMode == MCD_MODE_P25L)
                {
                   pDev->apCfg[mdioPort].modesVector = MCD_AN_25GBASE_KCR;
                }
                else
                    pDev->apCfg[mdioPort].modesVector = MCD_AN_25GBase_KR1_CONSORTIUM;
                ATTEMPT( mcdAutoNegPortCtrlStart(pDev, mdioPort,MCD_FALSE));
                pDev->portConfig[mdioPort].portMode = portMode;

            }
            else
            {
                if ((pDev->laneSteeringCfg.singlePortEnable[mdioPort]) && (laneSteeringEnable))
                {
                    ATTEMPT(mcdSerdesRxPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, baudrate, noPpmEnable,(MCD_U32)hsRefClockSel,(MCD_U32)hsRefClockDiv));
                    ATTEMPT(mcdSerdesTxPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, baudrate, noPpmEnable,(MCD_U32)hsRefClockSel,(MCD_U32)hsRefClockDiv));
                }
                else
                {
                    ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, baudrate, noPpmEnable, (MCD_U32)hsRefClockSel, (MCD_U32)hsRefClockDiv));
                }
                ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE));

                ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(chan, slice), MCD_TRUE, baudrate, MCD_FALSE, (MCD_U32)lsRefClockSel, (MCD_U32)lsRefClockDiv));
                ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(chan, slice), MCD_TRUE));
                /* configure Asic side, the setting for 25 or 20G is the same */
                ATTEMPT(mcdConfigurePcs10_25gR1(pDev, slice, chan, fecConfig.hostFec, MCD_MODE_P25L));
                /* configure Line side, the setting for 25 or 20G is the same */
                ATTEMPT(mcdConfigurePcs10_25gR1(pDev, slice, chan + 4, fecConfig.lineFec, MCD_MODE_P25L));

            }
            pDev->portConfig[mdioPort].portMode = portMode;
            break;
        case MCD_MODE_P10L:
        case MCD_MODE_P10S:

            /* Setting Serdes speed */
            baudrate = MCD_10_3125G;
            if (autoNegAdvEnable)
            {
                ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, MCD_10_3125G, noPpmEnable, (MCD_U32)hsRefClockSel, (MCD_U32)hsRefClockDiv));
                ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan),slice), MCD_TRUE));
                /* configure Asic side*/
                ATTEMPT(mcdConfigurePcs10_25gR1(pDev, slice, chan, fecConfig.hostFec, MCD_MODE_P10L));
                pDev->apCfg[mdioPort].apLaneNum = mdioPort;
                pDev->apCfg[mdioPort].modesVector = MCD_AN_10GBase_KR;
                pDev->apCfg[mdioPort].fecSup = fecConfig.lineFec;
                ATTEMPT( mcdAutoNegPortCtrlStart(pDev, mdioPort,MCD_FALSE));
                pDev->portConfig[mdioPort].portMode = portMode;

            }
            else
            {
                if ((pDev->laneSteeringCfg.singlePortEnable[mdioPort]) && (laneSteeringEnable))
                {
                    ATTEMPT(mcdSerdesRxPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, MCD_10_3125G, noPpmEnable,(MCD_U32)hsRefClockSel,(MCD_U32)hsRefClockDiv));
                    ATTEMPT(mcdSerdesTxPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, MCD_10_3125G, noPpmEnable,(MCD_U32)hsRefClockSel,(MCD_U32)hsRefClockDiv));
                }
                else
                {
                    ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, MCD_10_3125G, noPpmEnable, (MCD_U32)hsRefClockSel, (MCD_U32)hsRefClockDiv));
                }
                ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan),slice), MCD_TRUE));

                ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(chan, slice), MCD_TRUE, MCD_10_3125G, MCD_FALSE, (MCD_U32)lsRefClockSel, (MCD_U32)lsRefClockDiv));
                ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(chan,slice), MCD_TRUE));
                /* configure Asic side*/
                ATTEMPT(mcdConfigurePcs10_25gR1(pDev, slice, chan, fecConfig.hostFec, MCD_MODE_P10L));
                /*configure Line side */
                ATTEMPT(mcdConfigurePcs10_25gR1(pDev, slice, (chan + 4), fecConfig.lineFec, MCD_MODE_P10L));

                pDev->portConfig[mdioPort].portMode = portMode;
            }
            break;
        case MCD_MODE_R100L:
        case MCD_MODE_R100C:
            if (chan != 0) /* 100G  only on chan 0*/
            {
                MCD_DBG_ERROR("mcdSetModeSelectionExt: wrong channel number %u\n", chan);
                return MCD_FAIL;
            }

            /* Setting Serdes speed */
            baudrate = MCD_25_78125G;
            /* power up 4 Host serdeses */
            if (autoNegAdvEnable)
            {
                MCD_DBG_ERROR("mcdSetModeSelectionExt: not supported configuration mode %d\n", portMode);
                return MCD_FAIL;
            }
            else /* No Auto Neg */
            {
                for (i = chan ; (i < (chan + 4)); i++)
                {
                    serdesLs = MCD_SERDES_NUM(i, slice);
                    serdesHs = MCD_SERDES_NUM((i + MCD_HOST_SIDE_START_SERDES_NUMBER),slice);
                    ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePreSet(pDev, serdesHs, MCD_25_78125G));
                    ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePreSet(pDev, serdesLs, MCD_25_78125G));
                    pDev->portConfig[mdioPort + i].portMode = portMode;
                }
                for (i = chan ; (i < (chan + 4)); i++)
                {
                    serdesLs = MCD_SERDES_NUM(i, slice);
                    serdesHs = MCD_SERDES_NUM((i + MCD_HOST_SIDE_START_SERDES_NUMBER),slice);
                    ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePostSet(
                        pDev, mdioPort, serdesHs, MCD_25_78125G, (serdesHs & MCD_MASTER_CLOCK_MASK_CNS), MCD_TRUE, MCD_TRUE));
                    ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePostSet(
                        pDev, mdioPort, serdesLs, MCD_25_78125G, (serdesLs & MCD_MASTER_CLOCK_MASK_CNS), MCD_TRUE, MCD_TRUE));
                    pDev->portConfig[mdioPort + i].portMode = portMode;
                }
                /* ignore training before passing control to CM3 */
                bypassAutoTune = MCD_TRUE;
#ifndef ASIC_SIMULATION
                mcdWrapperMsSleep(PRV_MCD_DELAY_RETIMER_CLOCK_SWITCH);
#endif
            }
            break;
        case MCD_MODE_R40L:
        case MCD_MODE_R40C:
            if (chan != 0)
            {
                MCD_DBG_ERROR("mcdSetModeSelectionExt: wrong channel number %u\n", chan);
                return MCD_FAIL;
            }

            /* Setting Serdes speed */
            baudrate = MCD_10_3125G;
            if (autoNegAdvEnable)
            {
                MCD_DBG_ERROR("mcdSetModeSelectionExt: not supported configuration mode %d\n", portMode);
                return MCD_FAIL;
            }
            else
            {
                for (i = chan ; (i < (chan + 4)); i++)
                {
                    serdesLs = MCD_SERDES_NUM(i, slice);
                    serdesHs = MCD_SERDES_NUM((i + MCD_HOST_SIDE_START_SERDES_NUMBER),slice);
                    ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePreSet(pDev, serdesHs, MCD_10_3125G));
                    ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePreSet(pDev, serdesLs, MCD_10_3125G));
                    pDev->portConfig[mdioPort + i].portMode = portMode;
                }
                for (i = chan ; (i < (chan + 4)); i++)
                {
                    serdesLs = MCD_SERDES_NUM(i, slice);
                    serdesHs = MCD_SERDES_NUM((i + MCD_HOST_SIDE_START_SERDES_NUMBER),slice);
                    ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePostSet(
                        pDev, mdioPort, serdesHs, MCD_10_3125G, (serdesHs & MCD_MASTER_CLOCK_MASK_CNS), MCD_TRUE, MCD_TRUE));
                    ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePostSet(
                        pDev, mdioPort, serdesLs, MCD_10_3125G, (serdesLs & MCD_MASTER_CLOCK_MASK_CNS), MCD_TRUE, MCD_TRUE));
                    pDev->portConfig[mdioPort + i].portMode = portMode;
                }
                /* ignore training before passing control to CM3 */
                bypassAutoTune = MCD_TRUE;
#ifndef ASIC_SIMULATION
                mcdWrapperMsSleep(PRV_MCD_DELAY_RETIMER_CLOCK_SWITCH);
#endif
            }
            break;
        case MCD_MODE_R25L:
        case MCD_MODE_R25C:
            serdesHs = MCD_SERDES_NUM((chan + MCD_HOST_SIDE_START_SERDES_NUMBER),slice);

            /* Setting Serdes speed */
            baudrate = MCD_25_78125G;
            if (autoNegAdvEnable)
            {
                MCD_DBG_ERROR("mcdSetModeSelectionExt: not supported configuration mode %d\n", portMode);
                return MCD_FAIL;
            }
            else
            {
                serdesLs = MCD_SERDES_NUM(chan, slice);
                ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePreSet(pDev, serdesHs, MCD_25_78125G));
                ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePreSet(pDev, serdesLs, MCD_25_78125G));
                ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePostSet(
                    pDev, mdioPort, serdesHs, MCD_25_78125G, serdesHs, MCD_TRUE, MCD_TRUE));
                ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePostSet(
                    pDev, mdioPort, serdesLs, MCD_25_78125G, serdesLs, MCD_TRUE, MCD_TRUE));
                pDev->portConfig[mdioPort].portMode = portMode;
                /* ignore training before passing control to CM3 */
                bypassAutoTune = MCD_TRUE;
#ifndef ASIC_SIMULATION
                mcdWrapperMsSleep(PRV_MCD_DELAY_RETIMER_CLOCK_SWITCH);
#endif
            }
            break;
        case MCD_MODE_R10L:
        case MCD_MODE_R10K:
            serdesHs = MCD_SERDES_NUM((chan + MCD_HOST_SIDE_START_SERDES_NUMBER),slice);

            /* Setting Serdes speed */
            baudrate = MCD_10_3125G;
            if (autoNegAdvEnable)
            {
                MCD_DBG_ERROR("mcdSetModeSelectionExt: not supported configuration mode %d\n", portMode);
                return MCD_FAIL;
            }
            else
            {
                serdesLs = MCD_SERDES_NUM(chan, slice);
                ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePreSet(pDev, serdesHs, MCD_10_3125G));
                ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePreSet(pDev, serdesLs, MCD_10_3125G));
                ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePostSet(
                    pDev, mdioPort, serdesHs, MCD_10_3125G, serdesHs, MCD_TRUE, MCD_TRUE));
                ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePostSet(
                    pDev, mdioPort, serdesLs, MCD_10_3125G, serdesLs, MCD_TRUE, MCD_TRUE));
                pDev->portConfig[mdioPort].portMode = portMode;
                /* ignore training before passing control to CM3 */
                bypassAutoTune = MCD_TRUE;
#ifndef ASIC_SIMULATION
                mcdWrapperMsSleep(PRV_MCD_DELAY_RETIMER_CLOCK_SWITCH);
#endif
            }
            break;
        case MCD_MODE_R1L:
        case MCD_MODE_R1C:
            serdesHs = MCD_SERDES_NUM((chan + MCD_HOST_SIDE_START_SERDES_NUMBER),slice);

            /* Setting Serdes speed */
            baudrate = MCD_1_25G;
            if (autoNegAdvEnable)
            {
                MCD_DBG_ERROR("mcdSetModeSelectionExt: not supported configuration mode %d\n", portMode);
                return MCD_FAIL;
            }
            else
            {
                serdesLs = MCD_SERDES_NUM(chan, slice);
                ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePreSet(pDev, serdesHs, MCD_1_25G));
                ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePreSet(pDev, serdesLs, MCD_1_25G));
                ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePostSet(
                    pDev, mdioPort, serdesHs, MCD_1_25G, serdesHs, MCD_TRUE, MCD_TRUE));
                ATTEMPT(mcdSetSerdesLaneCfgForRetimerModePostSet(
                    pDev, mdioPort, serdesLs, MCD_1_25G, serdesLs, MCD_TRUE, MCD_TRUE));
                pDev->portConfig[mdioPort].portMode = portMode;
                /* ignore training before passing control to CM3 */
                bypassAutoTune = MCD_TRUE;
#ifndef ASIC_SIMULATION
                mcdWrapperMsSleep(PRV_MCD_DELAY_RETIMER_CLOCK_SWITCH);
#endif
            }
            break;
       case MCD_MODE_P2_5S:

            /* Setting Serdes speed */
            baudrate = MCD_3_125G;
            ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, MCD_3_125G, noPpmEnable, (MCD_U32)hsRefClockSel, (MCD_U32)hsRefClockDiv));
            ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan),slice), MCD_TRUE));
            ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(chan, slice), MCD_TRUE, MCD_3_125G, MCD_FALSE, (MCD_U32)lsRefClockSel, (MCD_U32)lsRefClockDiv));
            ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(chan,slice), MCD_TRUE));
            /* configure Asic side*/
            ATTEMPT(mcdConfigurePcs2p5gR1(pDev, slice, chan, fecConfig.hostFec));
            /*configure Line side */
            ATTEMPT(mcdConfigurePcs2p5gR1(pDev, slice, (chan + 4), fecConfig.lineFec));
            pDev->portConfig[mdioPort].portMode = portMode;

            break;
        case MCD_MODE_P2_5:

            /* Setting Serdes speed */
            baudrate = MCD_3_125G;
            ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, MCD_3_125G, noPpmEnable, (MCD_U32)hsRefClockSel, (MCD_U32)hsRefClockDiv));
            ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan),slice), MCD_TRUE));
            ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(chan, slice), MCD_TRUE, MCD_3_125G, MCD_FALSE, (MCD_U32)lsRefClockSel, (MCD_U32)lsRefClockDiv));
            ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(chan,slice), MCD_TRUE));
            /* configure Asic side*/
            ATTEMPT(mcdConfigurePcs2p5gBasex(pDev, slice, chan));
            /*configure Line side */
            ATTEMPT(mcdConfigurePcs2p5gBasex(pDev, slice, (chan + 4)));
            pDev->portConfig[mdioPort].portMode = portMode;

            break;
        case MCD_MODE_P1:

            /* Setting Serdes speed */
            baudrate = MCD_1_25G;

            if ((pDev->laneSteeringCfg.singlePortEnable[mdioPort]) && (laneSteeringEnable))
            {
                ATTEMPT(mcdSerdesRxPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, MCD_1_25G, noPpmEnable,(MCD_U32)hsRefClockSel,(MCD_U32)hsRefClockDiv));
                ATTEMPT(mcdSerdesTxPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, MCD_1_25G, noPpmEnable,(MCD_U32)hsRefClockSel,(MCD_U32)hsRefClockDiv));
            }
            else
            {
                ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, MCD_1_25G, noPpmEnable, (MCD_U32)hsRefClockSel, (MCD_U32)hsRefClockDiv));
            }
            ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan),slice), MCD_TRUE));
            ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(chan, slice), MCD_TRUE, MCD_1_25G, MCD_FALSE, (MCD_U32)lsRefClockSel, (MCD_U32)lsRefClockDiv));
            ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(chan,slice), MCD_TRUE));
            /* configure Asic side*/
            ATTEMPT(mcdConfigurePcs1gR1(pDev, slice, chan, 1/*BASEx*/, autoNegAdvEnable));
            /*configure Line side */
            ATTEMPT(mcdConfigurePcs1gR1(pDev, slice, (chan + 4), 1/*BASEX*/, autoNegAdvEnable));
            pDev->portConfig[mdioPort].portMode = portMode;

            break;
        case MCD_MODE_P1_SGMII:

            /* Setting Serdes speed */
            baudrate = MCD_1_25G;
            if ((pDev->laneSteeringCfg.singlePortEnable[mdioPort]) && (laneSteeringEnable))
            {
                ATTEMPT(mcdSerdesRxPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, MCD_1_25G, noPpmEnable,(MCD_U32)hsRefClockSel,(MCD_U32)hsRefClockDiv));
                ATTEMPT(mcdSerdesTxPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, MCD_1_25G, noPpmEnable,(MCD_U32)hsRefClockSel,(MCD_U32)hsRefClockDiv));
            }
            else
            {
                ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, MCD_1_25G, noPpmEnable, (MCD_U32)hsRefClockSel, (MCD_U32)hsRefClockDiv));
            }
            ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan),slice), MCD_TRUE));
            ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(chan, slice), MCD_TRUE, MCD_1_25G, MCD_FALSE, (MCD_U32)lsRefClockSel, (MCD_U32)lsRefClockDiv));
            ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(chan,slice), MCD_TRUE));
            /* configure Asic side*/
            ATTEMPT(mcdConfigurePcs1gR1(pDev, slice, chan,0/*SGMII*/, autoNegAdvEnable));
            /*configure Line side */
            ATTEMPT(mcdConfigurePcs1gR1(pDev, slice, (chan + 4), 0/*SGMII*/, autoNegAdvEnable));
            pDev->portConfig[mdioPort].portMode = portMode;

            break;
        case MCD_MODE_P1_BaseX_SGMII:

            /* Setting Serdes speed */
            baudrate = MCD_1_25G;
            ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan), slice), MCD_TRUE, MCD_1_25G, noPpmEnable, (MCD_U32)hsRefClockSel, (MCD_U32)hsRefClockDiv));
            ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM((MCD_HOST_SIDE_START_SERDES_NUMBER + chan),slice), MCD_TRUE));
            ATTEMPT(mcdSerdesPowerCtrl(pDev, MCD_SERDES_NUM(chan, slice), MCD_TRUE, MCD_1_25G, MCD_FALSE, (MCD_U32)lsRefClockSel, (MCD_U32)lsRefClockDiv));
            ATTEMPT(mcdSerdesTxEnable(pDev, MCD_SERDES_NUM(chan,slice), MCD_TRUE));
            /* configure Asic side*/
            ATTEMPT(mcdConfigurePcs1gR1(pDev, slice, chan, 0/*SGMII*/, autoNegAdvEnable));
            /*configure Line side */
            ATTEMPT(mcdConfigurePcs1gR1(pDev, slice, (chan + 4), 1/*BASEX*/, autoNegAdvEnable));
            pDev->portConfig[mdioPort].portMode = portMode;

            break;
        default:
            MCD_DBG_ERROR("mcdSetModeImplement: incorrect mode selection: %u\n", portMode);
            return MCD_FAIL;
    }

    pDev->portConfig[mdioPort].fecCorrect = fecCorrect;

    /* AP is not supported yet */
    pDev->portConfig[mdioPort].autoNegAdvSpeed = 0;
    pDev->portConfig[mdioPort].autoNegAcquSpeed = 0;

    if (noPpmEnable)
    {
        switch (portMode)
        {
            case MCD_MODE_P100L:
            case MCD_MODE_P100S:
            case MCD_MODE_P100C:
            case MCD_MODE_P100K:
                /* Setting Serdes speed */
                baudrate = MCD_25_78125G;
                /* power up 4 Host serdeses */
                for ( serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER; serdesNum < MCD_HOST_SIDE_START_SERDES_NUMBER + 4; serdesNum++)
                {
                    ATTEMPT(mcdSerdesNoPpmModeSet(pDev, MCD_SERDES_NUM(serdesNum, slice), MCD_25_78125G, (MCD_U32)chan, slice, MCD_TRUE));
                }
                for (port = 0; port < 4; port++)
                {
                    pDev->portConfig[mdioPort + port].noPpmMode = noPpmMode;
                }
                mcdWrapperMsSleep(PRV_MCD_DELAY_RETIMER_CLOCK_SWITCH);
                break;
            case MCD_MODE_P40L:
            case MCD_MODE_P40C:
            case MCD_MODE_P40S:
            case MCD_MODE_P40K:
                /* Setting Serdes speed */
                baudrate = MCD_10_3125G;
                /* power up 4 Host serdeses */
                for ( serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER; serdesNum < MCD_HOST_SIDE_START_SERDES_NUMBER + 4; serdesNum++)
                {
                    ATTEMPT(mcdSerdesNoPpmModeSet(pDev, MCD_SERDES_NUM(serdesNum, slice), MCD_10_3125G, (MCD_U32)chan, slice, MCD_TRUE));
                }
                for (port = 0; port < 4; port++)
                {
                    pDev->portConfig[mdioPort + port].noPpmMode = noPpmMode;
                }
                mcdWrapperMsSleep(PRV_MCD_DELAY_RETIMER_CLOCK_SWITCH);
                break;
             case MCD_MODE_G21L:
             case MCD_MODE_G21SK:
                /* Setting Serdes speed */
                baudrate = MCD_20_625G;
                for ( serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER + chan; serdesNum < (MCD_HOST_SIDE_START_SERDES_NUMBER + chan + 2); serdesNum++)
                {
                    ATTEMPT(mcdSerdesNoPpmModeSet(pDev, MCD_SERDES_NUM(serdesNum+chan, slice), MCD_20_625G, (MCD_U32)chan, slice, MCD_TRUE));
                }
                for (port = 0; port < 4; port++)
                {
                    pDev->portConfig[mdioPort + port].noPpmMode = noPpmMode;
                }
                mcdWrapperMsSleep(PRV_MCD_DELAY_RETIMER_CLOCK_SWITCH);
                break;
             case MCD_MODE_P50R2L:
             case MCD_MODE_P50R2S:
                /* Setting Serdes speed */
                baudrate = MCD_25_78125G;
                for ( serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER + chan; serdesNum < (MCD_HOST_SIDE_START_SERDES_NUMBER + chan + 2); serdesNum++)
                {
                    ATTEMPT(mcdSerdesNoPpmModeSet(pDev, serdesNum, MCD_25_78125G, (MCD_U32)chan, slice, MCD_TRUE));
                }
                for (port = 0; port < 2; port++)
                {
                    pDev->portConfig[mdioPort + port].noPpmMode = noPpmMode;
                }
                mcdWrapperMsSleep(PRV_MCD_DELAY_RETIMER_CLOCK_SWITCH);
                break;
            case MCD_MODE_P40R2L:
            case MCD_MODE_P40R2S:
                /* Setting Serdes speed */
                baudrate = MCD_20_625G;
                for ( serdesNum = MCD_HOST_SIDE_START_SERDES_NUMBER + chan; serdesNum < (MCD_HOST_SIDE_START_SERDES_NUMBER + chan + 2); serdesNum++)
                {
                    ATTEMPT(mcdSerdesNoPpmModeSet(pDev, MCD_SERDES_NUM(serdesNum+chan, slice), MCD_20_625G, (MCD_U32)chan, slice, MCD_TRUE));
                }
                for (port = 0; port < 2; port++)
                {
                    pDev->portConfig[mdioPort + port].noPpmMode = noPpmMode;
                }
                mcdWrapperMsSleep(PRV_MCD_DELAY_RETIMER_CLOCK_SWITCH);
                break;
            case MCD_MODE_P25L:
            case MCD_MODE_P25S:
                /* Setting Serdes speed */
                baudrate = MCD_25_78125G;
                ATTEMPT(mcdSerdesNoPpmModeSet(pDev, MCD_SERDES_NUM(MCD_HOST_SIDE_START_SERDES_NUMBER+chan, slice), MCD_25_78125G, (MCD_U32)chan, slice, MCD_TRUE));
                pDev->portConfig[mdioPort].noPpmMode = noPpmMode;
                mcdWrapperMsSleep(PRV_MCD_DELAY_RETIMER_CLOCK_SWITCH);
                break;
            case MCD_MODE_P10L:
            case MCD_MODE_P10S:
                /* Setting Serdes speed */
                baudrate = MCD_10_3125G;
                ATTEMPT(mcdSerdesNoPpmModeSet(pDev, MCD_SERDES_NUM(MCD_HOST_SIDE_START_SERDES_NUMBER+chan, slice), MCD_10_3125G, (MCD_U32)chan, slice, MCD_TRUE));
                pDev->portConfig[mdioPort].noPpmMode = noPpmMode;
                mcdWrapperMsSleep(PRV_MCD_DELAY_RETIMER_CLOCK_SWITCH);
                break;
            case MCD_MODE_P2_5S:
            case MCD_MODE_P2_5:
                /* Setting Serdes speed */
                baudrate = MCD_3_125G;
                ATTEMPT(mcdSerdesNoPpmModeSet(pDev, MCD_SERDES_NUM(MCD_HOST_SIDE_START_SERDES_NUMBER+chan, slice), MCD_3_125G, (MCD_U32)chan, slice, MCD_TRUE));
                pDev->portConfig[mdioPort].noPpmMode = noPpmMode;
                mcdWrapperMsSleep(PRV_MCD_DELAY_RETIMER_CLOCK_SWITCH);
                break;
            case MCD_MODE_P1:
            case MCD_MODE_P1_SGMII:
                /* Setting Serdes speed */
                baudrate = MCD_1_25G;
                ATTEMPT(mcdSerdesNoPpmModeSet(pDev, MCD_SERDES_NUM(MCD_HOST_SIDE_START_SERDES_NUMBER+chan, slice), MCD_1_25G, (MCD_U32)chan, slice, MCD_TRUE));
                pDev->portConfig[mdioPort].noPpmMode = noPpmMode;
                mcdWrapperMsSleep(PRV_MCD_DELAY_RETIMER_CLOCK_SWITCH);
                break;
        default:
            MCD_DBG_INFO("mcdSetModeSelectionExt: noPpmMode is not supported for portMode: %u\n", portMode);
            break;
        }
    }

    /* Retimer mode training is already done prior */
    if ((mcdSetModeSelectionExtPortTuningDisable == 0) && (bypassAutoTune == MCD_FALSE))
    {
        if ((pDev->calibrationCfg[mdioPort].calibrationMode == MCD_REDUCE_CALIBRATION) || (pDev->calibrationCfg[mdioPort].calibrationMode == MCD_OPTICAL_CTLE_BYPASS_CALIBRATION))
        {
            for (serdesNum = chan; serdesNum < chan+lineLanesNum; serdesNum++)
            {
                ATTEMPT(mcdSerdesBypassCtleTuneStart(pDev, MCD_SERDES_NUM(serdesNum,slice), pDev->calibrationCfg[mdioPort].calibrationMode, baudrate));
            }
            if (pDev->calibrationCfg[mdioPort].calibrationMode != MCD_REDUCE_CALIBRATION)
            {
                /* start ICAL on all host serdes lanes of PCS mode port */
                ATTEMPT(mcdPortSerdesDfeConfig_noSignalCheck(
                    pDev, mdioPort, MCD_DFE_ICAL,
                    MCD_FALSE /*configIfRetimerMode*/,
                    MCD_TRUE /*configIfPcsMode*/,
                    hostRxTraining /*configHostSide*/,
                    MCD_FALSE /*configLineSide*/));

            }
        }
        else
        {
            /* start ICAL on all serdes lanes of PCS mode port */
            ATTEMPT(mcdPortSerdesDfeConfig_noSignalCheck(
                pDev, mdioPort, MCD_DFE_ICAL,
                MCD_FALSE /*configIfRetimerMode*/,
                MCD_TRUE /*configIfPcsMode*/,
                hostRxTraining /*configHostSide*/,
                MCD_TRUE /*configLineSide*/));
        }
    }
    else
    {
        if (mcdSetModeSelectionExtPortTuningDisable == 1)
        {
            MCD_DBG_ERROR("ICAL is not running on port %d\n", mdioPort);
        }
    }

    if (mcdSetModeSelectionExtPortPollingMessageDisable == 0)
    {
        ATTEMPT(mcdPortPollingLinkStatusStart(pDev, mdioPort));
    }
    else
    {
        MCD_DBG_ERROR("CM3 is not running on port %d\n", mdioPort);
    }

    return MCD_OK;
}

/******************************************************************************
  MCD_STATUS mcdSetAPModeSelection
  Set port AP mode with referenced parameters - not applicable for retimer mode
*******************************************************************************/
MCD_STATUS mcdSetAPModeSelection
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 portNum,
    IN MCD_U32  apLaneNum,
    IN MCD_U32 modesVector,
    IN MCD_BOOL fcPause,
    IN MCD_BOOL fcAsmDir,
    IN MCD_FEC_TYPE fecSup,
    IN MCD_FEC_TYPE fecReq,
    IN MCD_BOOL nonceDis,
    IN MCD_CONFIG_SERDES_AP_PARAM_PTR configPtr,
    IN MCD_BOOL apEnable
)
{
    MCD_U8 polarityVector,i;
    MCD_FEC_TYPE_GET apFecSup, apFecReq;
    MCD_OP_MODE newPortMode;

    if ((fecSup == MCD_NO_FEC) && (fecReq > MCD_NO_FEC))
    {
        MCD_DBG_ERROR("mcdSetAPModeSelection: fec not supported\n");
        return MCD_FAIL;
    }

    if ((apEnable))
    {
        ATTEMPT(mcdPortModeVectorToPortMode(modesVector,&newPortMode));

        ATTEMPT(mcdPortStop(pDev, portNum, newPortMode/*pDev->portConfig[portNum].portMode*/));
    }
    polarityVector = 0;
    if (configPtr != NULL)
    {
        for(i = 0; i < configPtr->numOfLanes; i++)
        {
            polarityVector |= (configPtr->params[i].txPolarity << (2*i+1)) | (configPtr->params[i].rxPolarity  << (2*i));;
        }
    }

    pDev->portConfig[portNum].fecCorrect = fecSup;

    /* get requested/supported fec mode for LINE_SIDE*/
    MCD_FEC_TYPE_GET_MAC(fecSup, apFecSup);
    MCD_FEC_TYPE_GET_MAC(fecReq, apFecReq);

    ATTEMPT(mcdSetAutoNegParameters( pDev, portNum, apLaneNum, polarityVector, modesVector, fcPause, fcAsmDir, apFecSup.lineFec, apFecReq.lineFec, nonceDis));

    if ((apEnable))
    {
        ATTEMPT(mcdAutoNegPortCtrlStart( pDev, portNum, MCD_FALSE));
    }

    return MCD_OK;

}

static int mcdPortStopShowResetData = 0;
void mcdPortStopShowResetDataSet(int i)
{
    mcdPortStopShowResetData = i;
}
/**
* @internal mcdPortStop function
* @endinternal
*
* @brief   Release all port resources, calls to serdes power down in order to
*         configure new port.
* @param[in] pDev                     - pointer to MCD_DEV
* @param[in] mdioPort                 - MDIO port address 0...7
* @param[in] newPortMode              - operational mode of port that will be configured
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdPortStop
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16     mdioPort,
    IN MCD_OP_MODE newPortMode
)
{
    MCD_U16     port;
    MCD_U16     hostStopSerdesBmp;
    MCD_U16     lineStopSerdesBmp;
    MCD_U16     stopPortsBmp, stopPortsBmpWoRetimer;
    MCD_U16     stopApPortsBmp;
    MCD_REF_CLK_SEL refClkSel = MCD_PRIMARY_CLK;
    MCD_REF_CLK_DIV refClkDiv = MCD_REF_CLK_NO_DIV;
    MCD_BOOL    retimerMode;
    MCD_U16     tmplineSerdesBitmap, tmphostSerdesBitmap;
    MCD_NO_PPM_MODE tmpnoPpmMode;
    MCD_SERDES_SPEED tmplineSerdesSpeed, tmphostSerdesSpeed;
    MCD_U16 hostLanesNum = 0;
    MCD_U16 lineLanesNum = 0;
    MCD_U32 hostSerdesArr[MCD_MAX_LANES_NUM_PER_PORT] = {0};
    MCD_U32 lineSerdesArr[MCD_MAX_LANES_NUM_PER_PORT] = {0};

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdPortStop: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdPortStop: incorrect port selection: %u\n", mdioPort);
        return MCD_FAIL;
    }
    if ((newPortMode == MCD_MODE_UNKNOWN) && (pDev->portConfig[mdioPort].portMode == MCD_MODE_UNKNOWN))
    {
        MCD_DBG_ERROR("mcdPortStop: new port mode isn't set\n");
        return MCD_FAIL;
    }
    else if (newPortMode == MCD_MODE_UNKNOWN)
    {
        newPortMode = pDev->portConfig[mdioPort].portMode;
        MCD_SHOW("mcdPortStop portIndex:%d set mode newPortMode:%d\n",mdioPort, newPortMode);

    }

    if ( pDev->portConfig[mdioPort].portMode != MCD_MODE_UNKNOWN)
    {
        /* caulculate number of active lanes and build SerDes array*/
        lineLanesNum = mcdPortModeGetLanesNum(pDev->portConfig[mdioPort].portMode, MCD_LINE_SIDE);
        ATTEMPT(mcdPortBuildLanesArray(mdioPort,pDev->portConfig[mdioPort].portMode, MCD_LINE_SIDE, lineSerdesArr));
        /* N/A for lane steering host side */
        if (pDev->laneSteeringCfg.laneSteeringEnable == MCD_FALSE)
        {
            hostLanesNum = mcdPortModeGetLanesNum(pDev->portConfig[mdioPort].portMode, MCD_HOST_SIDE);
            ATTEMPT(mcdPortBuildLanesArray(mdioPort,pDev->portConfig[mdioPort].portMode, MCD_HOST_SIDE, hostSerdesArr));
        }
    }

    ATTEMPT(mcdPortModeGetStoppedSerdesBitmaps(
        pDev, newPortMode, mdioPort,
        &hostStopSerdesBmp, &lineStopSerdesBmp, &stopApPortsBmp));
    stopPortsBmp = (hostStopSerdesBmp | lineStopSerdesBmp);
    if (mcdPortStopShowResetData)
    {
        MCD_SHOW("mcdPortStop: port %d newPortMode %d portMode %d host 0x%x line 0x%x ap 0x%x\n",mdioPort, newPortMode, pDev->portConfig[mdioPort].portMode,
                  hostStopSerdesBmp, lineStopSerdesBmp, stopApPortsBmp);
    }

    stopPortsBmpWoRetimer = stopPortsBmp;
    for (port = 0; (port < 8); port++)
    {
        if (((1 << port) & stopPortsBmpWoRetimer) == 0) continue;
        mcdPortPollingLinkStatusStop(pDev, port);
        /* check if port is retimer and remove other serdes from bitmap */
        ATTEMPT(mcdPortPollingParamsGet(
            pDev, port, &retimerMode,
            &tmplineSerdesSpeed, &tmphostSerdesSpeed,
            &tmplineSerdesBitmap, &tmphostSerdesBitmap, &tmpnoPpmMode));
        if (retimerMode) {
            stopPortsBmpWoRetimer &= ~tmplineSerdesBitmap;
        }
    }
    if (mcdPortStopShowResetData)
    {
        MCD_SHOW("mcdPortStop: sent polling-stop to ports 0x%X\n", stopPortsBmp);
    }

    for (port = 0; (port < 8); port++)
    {
        if (((1 << port) & stopApPortsBmp) == 0) continue;
        mcdAutoNegPortCtrlStop(pDev,port);
    }
    if (mcdPortStopShowResetData)
    {
        MCD_SHOW("mcdPortStop: sent AP-stop to ports 0x%X\n", stopApPortsBmp);
    }

    /* stop PCS channel */
    for (port = 0; (port < 8); port++)
    {
        if (((1 << port) & stopPortsBmp) == 0) continue;
        mcdChannelControl(pDev, port, MCD_FALSE);
    }
    if (mcdPortStopShowResetData)
    {
        MCD_SHOW("mcdPortStop: stop PCS channel 0x%X\n", stopPortsBmp);
    }

    /* N/A for lane steering host side */
    if ((pDev->laneSteeringCfg.laneSteeringEnable == MCD_FALSE) &&  (pDev->portConfig[mdioPort].portMode != MCD_MODE_UNKNOWN))
    {
        /* halt DFE tune HOST side - before SerDes power down */
        ATTEMPT(mcdSerdesHaltDfeTraining(pDev, hostSerdesArr, hostLanesNum));
    }
    /* power down all serdes laned related to overlapped */
    /* existing ports,  baud rate ignored for power down */
    for (port = 0; (port < 8); port++)
    {
        if (((1 << port) & hostStopSerdesBmp) == 0)
            continue;
        if (pDev->laneSteeringCfg.singlePortEnable[port])
        {
            ATTEMPT(mcdSerdesTxPowerCtrl(
                pDev, (MCD_HOST_SIDE_START_SERDES_NUMBER + port)/*serdesNum*/,
                MCD_FALSE/*power off*/, MCD_SPEED_NA,
                mcdIsRetimerMode(pDev->portConfig[port].portMode)/*retimer*/, (MCD_U32)refClkSel, (MCD_U32)refClkDiv));
            ATTEMPT(mcdSerdesRxPowerCtrl(
                pDev, (MCD_HOST_SIDE_START_SERDES_NUMBER + port)/*serdesNum*/,
                MCD_FALSE/*power off*/, MCD_SPEED_NA,
                mcdIsRetimerMode(pDev->portConfig[port].portMode)/*retimer*/, (MCD_U32)refClkSel, (MCD_U32)refClkDiv));
        }
        else
        {
            ATTEMPT(mcdSerdesPowerCtrl(
                pDev, (MCD_HOST_SIDE_START_SERDES_NUMBER + port)/*serdesNum*/,
                MCD_FALSE/*power off*/, MCD_SPEED_NA,
                mcdIsRetimerMode(pDev->portConfig[port].portMode)/*retimer*/, (MCD_U32)refClkSel, (MCD_U32)refClkDiv));
        }
    }
    if (mcdPortStopShowResetData)
    {
        MCD_SHOW("mcdPortStop: power down host serdes 0x%X\n", hostStopSerdesBmp);
    }

    /* halt DFE tune LINE side - before SerDes power down */
    if ((!stopApPortsBmp) &&  (pDev->portConfig[mdioPort].portMode != MCD_MODE_UNKNOWN))
    {
        /* for AP the halt DFE process is done inside the FW */
        ATTEMPT(mcdSerdesHaltDfeTraining(pDev, lineSerdesArr, lineLanesNum));
    }
    for (port = 0; (port < 8); port++)
    {
        if ((((1 << port) & lineStopSerdesBmp) == 0) || (((1 << port) & stopApPortsBmp) != 0))
            continue;
        ATTEMPT(mcdSerdesPowerCtrl(
            pDev, port/*serdesNum*/,
            MCD_FALSE/*power off*/, MCD_SPEED_NA,
            mcdIsRetimerMode(pDev->portConfig[port].portMode)/*retimer*/, (MCD_U32)refClkSel, (MCD_U32)refClkDiv));
    }
    if (mcdPortStopShowResetData)
    {
        MCD_SHOW("mcdPortStop: power down line serdes 0x%X\n", lineStopSerdesBmp);
    }

    /* If Local fault is enabled from the UMAC towards the HOST side - disable it. otherwise,
       by connecting Copper module and configure the port to non-MCD_OPTICAL_CALIBRATION the
       local fault bit will be remaining "up" and avoid the Link to go 'up' */
    /* Checking if we operating in MCD_CONFIDENCE_INTERVAL_ALGO or MCD_BOTH_ALGO */
    if (pDev->calibrationCfg[mdioPort].calibrationAlgorithm != MCD_EYE_OPENING_ALGO) {
        ATTEMPT(mcdForceOutputLocalFaults(pDev, mdioPort, MCD_HOST_SIDE, tmphostSerdesSpeed, MCD_FALSE));
    }

    /* clean DB */
    for (port = 0; (port < 8); port++)
    {
        if (((1 << port) & (stopPortsBmp | stopApPortsBmp)) == 0) continue;
        pDev->portConfig[port].portMode = MCD_MODE_UNKNOWN;
        pDev->portConfig[port].autoNegAdvSpeed = 0;
        pDev->portConfig[port].autoNegAcquSpeed = 0;
        pDev->apCfg[port].apLaneNum  = 0xFF;
    }
    if (mcdPortStopShowResetData)
    {
        MCD_SHOW("mcdPortStop: clear ports DB 0x%X\n", stopPortsBmp);
    }

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdSetAutoNegAdvertisingSpeeds
    Set Auto-neg advertising speeds
*******************************************************************************/
MCD_STATUS mcdSetAutoNegAdvertisingSpeeds
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 speed_bits
)
{
     /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSetAutoNegAdvertisingSpeeds: incorrect port selection: %u\n", mdioPort);
        return MCD_FAIL;
    }

    if (host_or_line != MCD_LINE_SIDE)
    {
        MCD_DBG_ERROR("mcdSetAutoNegAdvertisingSpeeds: AP-only on LINE side\n");
        return MCD_FAIL;
    }

    pDev->portApCapability[mdioPort] = speed_bits;
    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdGetAutoNegAdvertisingSpeeds
    Get Auto-neg advertising speeds
*******************************************************************************/
MCD_STATUS mcdGetAutoNegAdvertisingSpeeds
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    OUT MCD_U16 *speed_bits
)
{
       /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSetAutoNegAdvertisingSpeeds: incorrect port selection: %u\n", mdioPort);
        return MCD_FAIL;
    }

    if (host_or_line != MCD_LINE_SIDE)
    {
        MCD_DBG_ERROR("mcdSetAutoNegAdvertisingSpeeds: AP-only on LINE side\n");
        return MCD_FAIL;
    }

    *speed_bits = (MCD_U16)pDev->apCfg[mdioPort].modesVector;
    return MCD_OK;

}


/*******************************************************************************
 MCD_STATUS mcdGetAutoNegParameters
    Get Auto-neg advertising speeds
*******************************************************************************/
MCD_STATUS mcdGetAutoNegParameters
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_AP_CFG_PTR apCfgPtr
)
{
       /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdGetApParameters: incorrect port selection: %u\n", mdioPort);
        return MCD_FAIL;
    }

   apCfgPtr->fcPause  =  pDev->apCfg[mdioPort].fcPause ;
   apCfgPtr->fcAsmDir =  pDev->apCfg[mdioPort].fcAsmDir ;
   apCfgPtr->fecSup   =  pDev->apCfg[mdioPort].fecSup   ;
   apCfgPtr->fecReq   =  pDev->apCfg[mdioPort].fecReq   ;
   apCfgPtr->nonceDis =  pDev->apCfg[mdioPort].nonceDis ;

   return MCD_OK;

}
/*******************************************************************************
 MCD_STATUS mcdSquelchRxClockSet
 The function defines which pin should be set to squelch RX clock
    and enables link status change interrupt for the referenced port
***************************************************************************/
MCD_STATUS mcdSquelchRxClockSet
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U32 laneNum,
    IN MCD_RX_CLOCK_CTRL_TYPE pinNum
)
{
    MCD_U16 slice, i, chan, lanesNum;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdSquelchRxClockSet: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSquelchRxClockSet: incorrect port selection: %u\n", mdioPort);
        return MCD_FAIL;
    }

    /*send squelch parameters to CM3*/
    if (mcdSetSquelchRxClockControlIpc(pDev, mdioPort, pinNum) != MCD_OK)
    {
        MCD_DBG_ERROR(" mcdSquelchRxClockSet Failed to init mcdSetSquelchRxClockControlPinIpc\n");
        return MCD_FAIL;
    }
    /* after CM3 send ACK that it got the parameters - clear interrupt status registers  and enable interrupt
       on all port lanes */
    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    lanesNum = mcdPortModeGetLanesNum(pDev->portConfig[mdioPort].portMode,MCD_LINE_SIDE);
    chan = CHAN_IN_SLICE_NUM(mdioPort);
    for (i = 0; i < lanesNum; i++)
    {
        mcdHwSetPhyRegField32bit(pDev, DONT_CARE, (UMAC_INTERRUPT_LINE_REG_ADDR(UMAC_INTERRUPT_clrintenable(slice, 0))) ,(8 + chan + i), 1, 1);
    }

    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, (UMAC_INTERRUPT_LINE_REG_ADDR(UMAC_INTERRUPT_intclr(slice, 0))), (8 + laneNum), 1, 1));
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, (UMAC_INTERRUPT_LINE_REG_ADDR(UMAC_INTERRUPT_setintenable(slice, 0))) ,(8 + laneNum), 1, 1));

     return MCD_OK;
}


/*******************************************************************************
 MCD_STATUS mcdAutoNegStart
    Starts Auto-neg with set speeds
*******************************************************************************/
MCD_STATUS mcdAutoNegStart
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_BOOL swReset
)
{
    MCD_BOOL retimerMode = MCD_FALSE;
    if (host_or_line != MCD_LINE_SIDE)
    {
        MCD_DBG_ERROR("mcdAutoNegStart: AP-only on LINE side\n");
        return MCD_FAIL;
    }

    if ((pDev->portConfig[mdioPort].portMode == MCD_MODE_R100C) ||
        (pDev->portConfig[mdioPort].portMode == MCD_MODE_R25C) ||
        (pDev->portConfig[mdioPort].portMode == MCD_MODE_R40C) ||
        (pDev->portConfig[mdioPort].portMode == MCD_MODE_R10K))
    {
        retimerMode = MCD_TRUE;
    }
    ATTEMPT( mcdAutoNegPortCtrlStart(pDev, mdioPort, retimerMode));
    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdAutoNegDisable
    Disable Auto-neg function
*******************************************************************************/
MCD_STATUS mcdAutoNegDisable
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_BOOL swReset
)
{
    if (host_or_line != MCD_LINE_SIDE)
    {
        MCD_DBG_ERROR("mcdAutoNegDisable: AP-only on LINE side\n");
        return MCD_FAIL;
    }
     ATTEMPT(mcdAutoNegPortCtrlStop(pDev,mdioPort));
     return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdAutoNegEnable
    Enable Auto-neg function
*******************************************************************************/
MCD_STATUS mcdAutoNegEnable
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line
)
{
    MCD_BOOL retimerMode = MCD_FALSE;

    if (host_or_line != MCD_LINE_SIDE)
    {
        MCD_DBG_ERROR("mcdAutoNegEnable: AP-only on LINE side\n");
        return MCD_FAIL;
    }


    if ((pDev->portConfig[mdioPort].portMode == MCD_MODE_R100C) ||
        (pDev->portConfig[mdioPort].portMode == MCD_MODE_R25C) ||
        (pDev->portConfig[mdioPort].portMode == MCD_MODE_R40C) ||
        (pDev->portConfig[mdioPort].portMode == MCD_MODE_R10K))
    {
        retimerMode = MCD_TRUE;
    }
    ATTEMPT( mcdAutoNegPortCtrlStart(pDev, mdioPort, retimerMode));
    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdAutoNegCheckCompleteExt
   if Auto-neg is completed:

            configure host side and returns MCD_OK
   otherwise -returns MCD_FAIL;
*******************************************************************************/
MCD_STATUS mcdAutoNegCheckCompleteExt
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_BOOL set_speed,
    IN MCD_MODE_CONFIG_PARAM_PTR configPtr,
    OUT MCD_U16 *speed
)
{
    MCD_AP_PORT_STATUS      apStatus;
    MCD_OP_MODE  portMode;
    MCD_FEC_TYPE fecCorrect;
    MCD_BOOL hcdFound = MCD_FALSE;
    MCD_U16 lineLanesNum, port;

    /* initilaize speed and portMode to default values */
    *speed = MCD_NEG_NONE;
    portMode = MCD_MODE_UNKNOWN;


    if (host_or_line != MCD_LINE_SIDE)
    {
        MCD_DBG_ERROR("mmcdAutoNegCheckComplete: AP-only on LINE side\n");
        return MCD_FAIL;
    }

    mcdMemSet (&apStatus, 0 , sizeof(MCD_AP_PORT_STATUS));

    ATTEMPT(mcdApPortCtrlStatusGet(pDev,mdioPort,&apStatus));
    hcdFound = apStatus.hcdResult.hcdFound;
    /* if resolution found, update speed and portMode parameters */
    if (hcdFound)
    {
        *speed = mcdApConvertHdc2Vec(apStatus.hcdResult.hcdResult);
        portMode =  mcdApConvertPortMode(apStatus.hcdResult.hcdResult);
    }

    /* if we reach to this point and HCD did not update, notify the application.
       (extreme scenario that found by customer) */
    if ((set_speed == MCD_TRUE) && (*speed == MCD_NEG_NONE))
    {
        return MCD_HCD_NOT_FOUND;
    }

    if (apStatus.hcdResult.hcdFound)
    {
        if (set_speed)
        {
            lineLanesNum = mcdPortModeGetLanesNum(portMode, MCD_LINE_SIDE);
            for (port = 0; port < lineLanesNum; port++)
                pDev->portConfig[mdioPort + port].portMode = portMode;

            fecCorrect = pDev->portConfig[mdioPort].fecCorrect;
            configPtr->noPpmMode = (MCD_NO_PPM_MODE)pDev->apCfg[mdioPort].noPpmMode;

            if ((pDev->apCfg[mdioPort].options & MCD_AP_OPTIONS_G21_MODE_CNS) &&
                (portMode == MCD_MODE_P40C))
            {
                portMode = MCD_MODE_G21SK;
            }
            if ((pDev->apCfg[mdioPort].options & MCD_AP_OPTIONS_1G_SGMII_MODE_CNS) &&
                (portMode == MCD_MODE_P1))
            {
                portMode = MCD_MODE_P1_BaseX_SGMII;
            }

            if ( fecCorrect <= MCD_FC_FEC)
            {
                ATTEMPT(mcdOneSideSetMode(pDev, mdioPort,portMode,MCD_HOST_SIDE,pDev->apRes[mdioPort].hcdFec, configPtr));
            }
            else
            {
                ATTEMPT(mcdOneSideSetMode(pDev, mdioPort,portMode,MCD_HOST_SIDE,fecCorrect, configPtr));
            }
        }
    }
    return MCD_OK;
}

/**
* @internal mcdLowSpeedAutoNegEnable function
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
MCD_STATUS mcdLowSpeedAutoNegEnable
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16     mdioPort,
    IN MCD_U16     host_or_line,
    IN MCD_BOOL    anEnable
)
{
    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("%s: device not initialized\n", __func__);
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("%s: incorrect port selection: %u\n", __func__, mdioPort);
        return MCD_FAIL;
    }

    /* check if port mode is valid for AN to set */
    if (!((pDev->portConfig[mdioPort].portMode == MCD_MODE_P1) ||
        (pDev->portConfig[mdioPort].portMode == MCD_MODE_P1_SGMII) ||
        (pDev->portConfig[mdioPort].portMode == MCD_MODE_P1_BaseX_SGMII)))
    {
        MCD_DBG_ERROR("%s: Port Mode Selection is wrong!\n", __func__);
        return MCD_FAIL;
    }

    ATTEMPT(mcdLowSpeedANEnable(pDev, mdioPort, host_or_line, anEnable));

    return MCD_OK;
}

/**
* @internal mcdLowSpeedAutoNegEnableGet function
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
MCD_STATUS mcdLowSpeedAutoNegEnableGet
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    OUT MCD_BOOL *anEnableSts
)
{
    MCD_U32 regData, mask = 0x1;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("%s: device not initialized\n", __func__);
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("%s: incorrect port selection: %u\n", __func__, mdioPort);
        return MCD_FAIL;
    }

    /* check if port mode is valid to read AN status */
    if (!((pDev->portConfig[mdioPort].portMode == MCD_MODE_P1) ||
        (pDev->portConfig[mdioPort].portMode == MCD_MODE_P1_SGMII) ||
        (pDev->portConfig[mdioPort].portMode == MCD_MODE_P1_BaseX_SGMII)))
    {
        MCD_DBG_ERROR("%s: Port Mode Selection is wrong!\n", __func__);
        return MCD_FAIL;
    }

    ATTEMPT(mcdLowSpeedANEnableGet(pDev, mdioPort, host_or_line, &regData));

    if (regData & mask)
    {
        /* Anenable bit is set */
        *anEnableSts = MCD_TRUE;
    }
    else
    {
        /* Anenable bit is not set */
        *anEnableSts = MCD_FALSE;
    }

    return MCD_OK;
}

/**
* @internal mcdLowSpeedAutoNegRestart function
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
MCD_STATUS mcdLowSpeedAutoNegRestart
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line
)
{
    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("%s: device not initialized\n", __func__);
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("%s: incorrect port selection: %u\n", __func__, mdioPort);
        return MCD_FAIL;
    }

    /* check if port mode is valid for AN to restart */
    if (!((pDev->portConfig[mdioPort].portMode == MCD_MODE_P1) ||
        (pDev->portConfig[mdioPort].portMode == MCD_MODE_P1_SGMII) ||
        (pDev->portConfig[mdioPort].portMode == MCD_MODE_P1_BaseX_SGMII)))
    {
        MCD_DBG_ERROR("%s: Port Mode Selection is wrong!\n", __func__);
        return MCD_FAIL;
    }

    ATTEMPT(mcdLowSpeedANRestart(pDev, mdioPort, host_or_line));

    return MCD_OK;
}

/**
* @internal mcdLowSpeedAutoNegDoneGet function
* @endinternal
*
* @brief   Read the status of AN done bit.
*
* @param[in] pDev                   - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] mdioPort               - MDIO port, 0-7
* @param[in] host_or_line           - which interface to be monitored, MCD_HOST_SIDE or MCD_LINE_SIDE
* @param[out] anDoneSts             - Read status of AN done.
*
* @retval MCD_OK                    - on success.
* @retval MCD_FAIL                  - on failure
*
*/
MCD_STATUS mcdLowSpeedAutoNegDoneGet
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    OUT MCD_BOOL *anDoneSts
)
{
    MCD_U32 anDone, mask = 0x1;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("%s: device not initialized\n", __func__);
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("%s: incorrect port selection: %u\n", __func__, mdioPort);
        return MCD_FAIL;
    }

    /* check if port mode is valid to read AN Done */
    if (!((pDev->portConfig[mdioPort].portMode == MCD_MODE_P1) ||
        (pDev->portConfig[mdioPort].portMode == MCD_MODE_P1_SGMII) ||
        (pDev->portConfig[mdioPort].portMode == MCD_MODE_P1_BaseX_SGMII)))
    {
        MCD_DBG_ERROR("%s: Port Mode Selection is wrong!\n", __func__);
        return MCD_FAIL;
    }

    /* Read AN done bit */
    ATTEMPT(mcdLowSpeedANDoneGet(pDev, mdioPort, host_or_line, &anDone));

    if (anDone & mask)
    {
        /* AnDone bit is set */
        *anDoneSts = MCD_TRUE;
    }
    else
    {
        /* AnDone bit is not set */
        *anDoneSts = MCD_FALSE;
    }

    return MCD_OK;
}

/**
* @internal mcdLowSpeedAutoNegAdvertSet function
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
* @note                             - This API must be called after mcdSetModeSelectionExt() and having
*                                     1000Base-x has its port mode.
*
*/
MCD_STATUS mcdLowSpeedAutoNegAdvertSet
(
    IN MCD_DEV_PTR      pDev,
    IN MCD_U16          mdioPort,
    IN MCD_U16          host_or_line,
    IN MCD_U32          mode
)
{
    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("%s: device not initialized\n", __func__);
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("%s: incorrect port selection: %u\n", __func__, mdioPort);
        return MCD_FAIL;
    }

    /* check if port mode is valid to set AN Advertisement */
    if (!((pDev->portConfig[mdioPort].portMode == MCD_MODE_P1) ||
        (pDev->portConfig[mdioPort].portMode == MCD_MODE_P1_BaseX_SGMII)))
    {
        MCD_DBG_ERROR("%s: Port Mode Selection is wrong!\n", __func__);
        return MCD_FAIL;
    }

    ATTEMPT(mcdLowSpeedANAdvertSet(pDev, mdioPort, host_or_line, mode));

    return MCD_OK;
}


/*******************************************************************************
 MCD_STATUS mcdCheckLinkStatus
    Check link status
*******************************************************************************/
MCD_STATUS mcdCheckLinkStatus
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    OUT MCD_U16 *currentStatus,
    OUT MCD_U16 *latchedStatus,
    OUT DETAILED_STATUS_TYPE *statusDetail
)
{
    MCD_U32 hostRegAddr;
    MCD_U32 lineRegAddr;
    MCD_U32 bitIndex;
    MCD_U32 slice, chan;
    MCD_U8  revert = 0;
    MCD_U16 rawInterruptReg;
    MCD_U16 hostLinkChanged;
    MCD_U16 lineLinkChanged;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdCheckLinkStatus: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdCheckLinkStatus: incorrect port selection: %u\n", mdioPort);
        return MCD_FAIL;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);
    rawInterruptReg = chan + 7;


    /* High Speed for > 1G                                               */
    /* UMAC/Slice %m/umac3gbsx4/hsmcpcs0/sts1 0..3 host side             */
    /* UMAC/Slice %m/umac3gbsx4/hsmcpcs4/sts1 4..7 is line side for 0..3 */
    /* bit12 - pscstatus                                                 */
    /* Low Speed for <= 1G                                               */
    /* UMAC/Slice %m/umac3gbsx4/lsmcpcs0/sts 0..3 host side              */
    /* UMAC/Slice %m/umac3gbsx4/lsmcpcs4/sts 4..7 is line side for 0..3  */
    /* bit1 - syncstat                                                   */
    switch(pDev->portConfig[mdioPort].portMode)
    {
        /* new modes for X5123 and EC808 */
        case MCD_MODE_P50R2L:        /* 50GBase-R2                                              */
        case MCD_MODE_P50R2S:        /* 50GBase-R2                                              */
        case MCD_MODE_P40R2L:        /* 40GBase-R2                                              */
        case MCD_MODE_P40R2S:        /* 40GBase-R2                                              */
        case MCD_MODE_P25L:          /* 25GBase-R1                                              */
        case MCD_MODE_P25S:          /* 25GBase-R1                                              */
        case MCD_MODE_P10L:          /* 10GBase-R1                                              */
        case MCD_MODE_P10S:          /* 10GBase-R1                                              */
        case MCD_MODE_P2_5:          /* 2.5GBase-X                                              */
        case MCD_MODE_P2_5S:         /* 2.5GBase-X                                              */
        case MCD_MODE_G21L:          /* GEARBOX 40GBase-R2 (host Side) to 40GBase-R4 (Line Side)*/
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
        case MCD_MODE_P20L:          /* 20GBase-R1                                              */
        case MCD_MODE_P20S:          /* 20GBase-R1                                              */
            hostRegAddr = UMAC_MCPCS_BASE_R_and_10GBASE_T_PCS_Status1(slice,chan);
            lineRegAddr = UMAC_MCPCS_LINE_REG_ADDR(hostRegAddr);
            bitIndex    = 12;
            ATTEMPT(mcdReadPCSLinkStatus(
                pDev, mdioPort, hostRegAddr, lineRegAddr, bitIndex,
                currentStatus, latchedStatus, statusDetail));
            ATTEMPT(mcdGetRealtimeStatusEx(pDev, mdioPort, MCD_HOST_SIDE, MCD_TRUE, rawInterruptReg, MCD_UMAC_INTERRUPT_INTRAW_SYNC,
                                           &hostLinkChanged));
            ATTEMPT(mcdGetRealtimeStatusEx(pDev, mdioPort, MCD_LINE_SIDE, MCD_TRUE, rawInterruptReg, MCD_UMAC_INTERRUPT_INTRAW_SYNC,
                                            &lineLinkChanged));
            statusDetail->P100_40_status.hostLinkChanged = (hostLinkChanged ? 1 : 0);
            statusDetail->P100_40_status.lineLinkChanged = (lineLinkChanged ? 1 : 0);
            break;
        /* legacy repeater modes */
        case MCD_MODE_R100L:
        case MCD_MODE_R40L:
        case MCD_MODE_R25L:
        case MCD_MODE_R10L:
        case MCD_MODE_R100C:
        case MCD_MODE_R40C:
        case MCD_MODE_R25C:
        case MCD_MODE_R10K:
        case MCD_MODE_R1L:
        case MCD_MODE_R1C:
            if (pDev->highAvailabilityMode)
            {
                pDev->highAvailabilityMode = MCD_FALSE;
                revert = 1;
            }
            ATTEMPT(mcdReadRepeaterLinkStatus(pDev, mdioPort, currentStatus, statusDetail));
            *latchedStatus = 0; /* not applicable in repeater mode */
            if (revert)
            {
                pDev->highAvailabilityMode = MCD_TRUE;
            }
            break; 
        /* new modes for X5123 and EC808 - low speed */
        case MCD_MODE_P1:
        case MCD_MODE_P1_SGMII:
        case MCD_MODE_P1_BaseX_SGMII:
            hostRegAddr = UMAC_LSMCPCS_sts(slice,chan);
            lineRegAddr = UMAC_LSMCPCS_LINE_REG_ADDR(hostRegAddr);
            bitIndex    = 1; /*syncstat*/
            ATTEMPT(mcdReadPCSLinkStatus(
                pDev, mdioPort, hostRegAddr, lineRegAddr, bitIndex,
                currentStatus, latchedStatus, statusDetail));
            break;
        default:
            MCD_DBG_ERROR("mcdCheckLinkStatus: incorrect/unsupported mode selection: %u\n", pDev->portConfig[MCD_GET_PORT_IDX(pDev,mdioPort)].portMode);
            return MCD_FAIL;
            break;
    }

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdGetPcsFaultStatus
    Check tx/rx fault status
*******************************************************************************/
MCD_STATUS mcdGetPcsFaultStatus
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    OUT MCD_U16 *currentTxFaultStatus,
    OUT MCD_U16 *currentRxFaultStatus,
    OUT MCD_U16 *latchedTxFaultStatus,
    OUT MCD_U16 *latchedRxFaultStatus
)
{
    MCD_U32 regAddrRx, bitIndexRx;
    MCD_U32 currentRxFaultStatus32bit;
    MCD_U32 latchedRxFaultStatus32bit;
    MCD_MODE_SPEED speed;
    MCD_MODE mode;
    MCD_U32 slice, chan;

    *latchedRxFaultStatus = 1; /* in case fails, init to fault */
    *currentRxFaultStatus = 1; /* in case fails, init to fault */
    *latchedTxFaultStatus = 0; /* TxFaultStatus not supported - set no fault */
    *currentTxFaultStatus = 0; /* TxFaultStatus not supported - set no fault */

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdGetPcsFaultStatus: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdGetPcsFaultStatus: incorrect port selection: %uh\n", mdioPort);
        return MCD_FAIL;
    }

    if (!((host_or_line == MCD_HOST_SIDE) || (host_or_line == MCD_LINE_SIDE)))
    {
        MCD_DBG_ERROR("mcdGetPcsFaultStatus: host_or_line is invalid\n");
        return MCD_FAIL;
    }

    ATTEMPT(mcdGetModeSpeed(pDev, mdioPort, host_or_line, &speed, &mode));

    if (mcdIsPortModePcsControlled(mode) == 0)
    {
        MCD_DBG_ERROR("mcdGetPcsFaultStatus: not in PCS mode\n");
        return MCD_FAIL;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);

    switch (speed)
    {
        case MCD_10GB:
        case MCD_20GB:
        case MCD_25GB:
        case MCD_40GB:
        case MCD_100GB:
        case MCD_2_5GB:
            /*host - default*/
            regAddrRx  = UMAC_MCPCS_PCS_Status1(slice, chan);
            bitIndexRx = 7;
            if (host_or_line == MCD_LINE_SIDE)
            {
                /*line*/
                regAddrRx = UMAC_MCPCS_LINE_REG_ADDR(regAddrRx);
            }
            break;

        case MCD_1GB: /* no such indication for low speed */
            *latchedRxFaultStatus = 0; /* not supported, set to no fault */
            *currentRxFaultStatus = 0; /* not supported, set to no fault */
            return MCD_OK;
        case MCD_UNKNOWN_SPEED:
        default:
            MCD_DBG_ERROR("mcdGetPcsFaultStatus: unsupported speed or speed not known\n");
            return MCD_FAIL;
            break;
    }

    ATTEMPT(mcdHwGetPhyRegField32bit(
        pDev, mdioPort, regAddrRx, bitIndexRx, 1, &latchedRxFaultStatus32bit));
    ATTEMPT(mcdHwGetPhyRegField32bit(
        pDev, mdioPort, regAddrRx, bitIndexRx, 1, &currentRxFaultStatus32bit));

    *latchedRxFaultStatus = (MCD_U16)latchedRxFaultStatus32bit;
    *currentRxFaultStatus = (MCD_U16)currentRxFaultStatus32bit;

    return MCD_OK;
}

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************************
* MCD_STATUS mcdGetCm3ToHostSignal
*       get the data that was sent from CM3 to Host via doorbell.
*******************************************************************************/
MCD_STATUS mcdGetCm3ToHostSignal
(
    IN   MCD_DEV_PTR pDev,
    OUT  MCD_U32     *signalCodePtr
)
{
    MCD_U32     regAddr;
    if ((pDev == NULL) || (!pDev->devEnabled))
    {
        MCD_DBG_ERROR("mcdCm3ToHostSignalReceive: device not initialized\n");
        return MCD_FAIL;
    }

    if (signalCodePtr == NULL)
    {
        MCD_DBG_ERROR("mcdCm3ToHostSignalReceive: Null pointer in parameter\n");
        return MCD_FAIL;
    }

    regAddr = REG_ADDR_MG_CM3_TO_HOST_DOORBELL;
    ATTEMPT(mcdHwXmdioRead32bit(pDev, 0, regAddr, signalCodePtr));

    return MCD_OK;
}

#endif /*not MV_HWS_REDUCED_BUILD_EXT_CM3*/

/*******************************************************************************
 MCD_STATUS mcdGetAPIVersion
    Get MCD software API version
*******************************************************************************/
MCD_STATUS mcdGetAPIVersion
(
    OUT MCD_U8 *major,
    OUT MCD_U8 *minor,
    OUT MCD_U8 *patch
)
{
    if (major == NULL)
    {
       MCD_DBG_ERROR("mcdGetAPIVersion: failed to get MCD API\n");
       return MCD_FAIL;
    }

    *major = MCD_API_MAJOR_VERSION;
    *minor = MCD_API_MINOR_VERSION;
    *patch = MCD_API_PATCH_VERSION;

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdSetInterruptEnableEx
    Set interrupt enable.
*******************************************************************************/
MCD_STATUS mcdSetInterruptEnableEx
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U16 mdioPort,
    IN  MCD_U16 host_or_line,
    IN  MCD_U16 interruptRegisterNum, /*0..14*/
    IN  MCD_U16 intrEnableFlags
)
{
    MCD_U32  slice;
    MCD_U32  regAddr;
    MCD_U32  data;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdSetInterruptEnableEx: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSetInterruptEnableEx: incorrect port selection: %uh\n", mdioPort);
        return MCD_FAIL;
    }

    if (interruptRegisterNum > 14)
    {
        MCD_DBG_ERROR(
            "mcdSetInterruptEnableEx: incorrect interruptRegisterNum : %uh\n",
            interruptRegisterNum);
        return MCD_FAIL;
    }

    if ((host_or_line != MCD_HOST_SIDE) && (host_or_line != MCD_LINE_SIDE))
    {
        MCD_DBG_ERROR("mcdSetInterruptEnableEx: host_or_line is invalid\n");
        return MCD_FAIL;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;

    /*<UMAC> UMAC/Slice %m/umac3gbsx4/interrupts0/setintenable0*/
    regAddr = UMAC_INTERRUPT_setintenable(slice, interruptRegisterNum);
    if (host_or_line == MCD_LINE_SIDE)
    {
        regAddr = UMAC_INTERRUPT_LINE_REG_ADDR(regAddr);
    }
    data = (0xFFFF & (MCD_U32)intrEnableFlags);
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, mdioPort, regAddr, data));

    /*<UMAC> UMAC/Slice %m/umac3gbsx4/interrupts0/clrintenable0*/
    regAddr = UMAC_INTERRUPT_clrintenable(slice, interruptRegisterNum);
    if (host_or_line == MCD_LINE_SIDE)
    {
        regAddr = UMAC_INTERRUPT_LINE_REG_ADDR(regAddr);
    }
    data = (0xFFFF & (~ (MCD_U32)intrEnableFlags));
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, mdioPort, regAddr, data));

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdGetInterruptEnableEx
    Get interrupt enable.
*******************************************************************************/
MCD_STATUS mcdGetInterruptEnableEx
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U16 mdioPort,
    IN  MCD_U16 host_or_line,
    IN  MCD_U16 interruptRegisterNum, /*0..14*/
    OUT MCD_U16 *intrEnableFlags
)
{
    MCD_U32  slice;
    MCD_U32  regAddr;
    MCD_U32  data;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdGetInterruptEnableEx: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdGetInterruptEnableEx: incorrect port selection: %uh\n", mdioPort);
        return MCD_FAIL;
    }

    if (interruptRegisterNum > 14)
    {
        MCD_DBG_ERROR(
            "mcdGetInterruptEnableEx: incorrect interruptRegisterNum : %uh\n",
            interruptRegisterNum);
        return MCD_FAIL;
    }

    if ((host_or_line != MCD_HOST_SIDE) && (host_or_line != MCD_LINE_SIDE))
    {
        MCD_DBG_ERROR("mcdGetInterruptEnableEx: host_or_line is invalid\n");
        return MCD_FAIL;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;

    /*<UMAC> UMAC/Slice %m/umac3gbsx4/interrupts0/setintenable0*/
    regAddr = UMAC_INTERRUPT_setintenable(slice, interruptRegisterNum);
    if (host_or_line == MCD_LINE_SIDE)
    {
        regAddr = UMAC_INTERRUPT_LINE_REG_ADDR(regAddr);
    }
    ATTEMPT(mcdHwXmdioRead32bit(pDev, mdioPort, regAddr, &data));

    *intrEnableFlags = (MCD_U16)(0xFFFF & data);

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdGetInterruptStatusEx
    Get interrupt status.
*******************************************************************************/
MCD_STATUS mcdGetInterruptStatusEx
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U16 mdioPort,
    IN  MCD_U16 host_or_line,
    IN  MCD_BOOL toClearStatus,       /* to clear after read */
    IN  MCD_U16 interruptRegisterNum, /*0..14*/
    OUT MCD_U16 *interruptStatusFlags
)
{
    MCD_U32  slice;
    MCD_U32  regAddr;
    MCD_U32  data;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdGetInterruptStatusEx: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdGetInterruptStatusEx: incorrect port selection: %uh\n", mdioPort);
        return MCD_FAIL;
    }

    if (interruptRegisterNum > 14)
    {
        MCD_DBG_ERROR(
            "mcdGetInterruptStatusEx: incorrect interruptRegisterNum : %uh\n",
            interruptRegisterNum);
        return MCD_FAIL;
    }

    if ((host_or_line != MCD_HOST_SIDE) && (host_or_line != MCD_LINE_SIDE))
    {
        MCD_DBG_ERROR("mcdGetInterruptStatusEx: host_or_line is invalid\n");
        return MCD_FAIL;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;

    /*<UMAC> UMAC/Slice %m/umac3gbsx4/interrupts0/intstat0*/
    regAddr = UMAC_INTERRUPT_intstat(slice, interruptRegisterNum);
    if (host_or_line == MCD_LINE_SIDE)
    {
        regAddr = UMAC_INTERRUPT_LINE_REG_ADDR(regAddr);
    }
    ATTEMPT(mcdHwXmdioRead32bit(pDev, mdioPort, regAddr, &data));

    *interruptStatusFlags = (MCD_U16)(0xFFFF & data);

    if (toClearStatus != MCD_FALSE)
    {
        /*<UMAC> UMAC/Slice %m/umac3gbsx4/interrupts0/intclr0*/
        regAddr = UMAC_INTERRUPT_intclr(slice, interruptRegisterNum);
        if (host_or_line == MCD_LINE_SIDE)
        {
            regAddr = UMAC_INTERRUPT_LINE_REG_ADDR(regAddr);
        }
        ATTEMPT(mcdHwXmdioWrite32bit(pDev, mdioPort, regAddr, 0xFFFF));
    }

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdGetRealtimeStatusEx
    Get real-time status.
*******************************************************************************/
MCD_STATUS mcdGetRealtimeStatusEx
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U16 mdioPort,
    IN  MCD_U16 host_or_line,
    IN  MCD_BOOL clearOnRead,
    IN  MCD_U16 interruptRegisterNum, /*0..14*/
    IN  MCD_U16 mask,
    OUT MCD_U16 *intrRtStatusFlags
)
{
    MCD_U32  slice;
    MCD_U32  regAddr;
    MCD_U32  data;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdGetRealtimeStatusEx: device not initialized\n");
        return MCD_FAIL;
    }

    /* check port is valid */
    if (mcdIsPortValid(pDev, mdioPort) != MCD_OK)
    {
        MCD_DBG_ERROR("mcdGetRealtimeStatusEx: incorrect port selection: %uh\n", mdioPort);
        return MCD_FAIL;
    }

    if (interruptRegisterNum > 14)
    {
        MCD_DBG_ERROR(
            "mcdGetRealtimeStatusEx: incorrect interruptRegisterNum : %uh\n",
            interruptRegisterNum);
        return MCD_FAIL;
    }

    if ((host_or_line != MCD_HOST_SIDE) && (host_or_line != MCD_LINE_SIDE))
    {
        MCD_DBG_ERROR("mcdGetRealtimeStatusEx: host_or_line is invalid\n");
        return MCD_FAIL;
    }

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;

    /* if mask equals to zero, returning all the register status */
    if (mask == 0)
    {
        mask = 0xFFFF;
    }

    /*<UMAC> UMAC/Slice %m/umac3gbsx4/interrupts0/intraw0*/
    regAddr = UMAC_INTERRUPT_intraw(slice, interruptRegisterNum);
    if (host_or_line == MCD_LINE_SIDE)
    {
        regAddr = UMAC_INTERRUPT_LINE_REG_ADDR(regAddr);
    }
    ATTEMPT(mcdHwXmdioRead32bit(pDev, mdioPort, regAddr, &data));

    *intrRtStatusFlags = (MCD_U16)(mask & data);

    if (clearOnRead != MCD_FALSE)
    {
        /*<UMAC> UMAC/Slice %m/umac3gbsx4/interrupts0/intclr0*/
        regAddr = UMAC_INTERRUPT_intclr(slice, interruptRegisterNum);
        if (host_or_line == MCD_LINE_SIDE)
        {
            regAddr = UMAC_INTERRUPT_LINE_REG_ADDR(regAddr);
        }
        ATTEMPT(mcdHwXmdioWrite32bit(pDev, mdioPort, regAddr, mask));
    }

    return MCD_OK;
}

/*******************************************************************************
 MCD_STATUS mcdSyncEClkConfig
*******************************************************************************/
MCD_STATUS mcdSyncEClkConfig
(
    IN  MCD_DEV_PTR  pDev,
    IN  MCD_U16      mdioPort,
    IN  MCD_U32      laneNum,
    IN  MCD_RCLK_DIV_VAL divider,
    IN  MCD_BOOL     squelchEnable,
    IN MCD_RCLK_OUT_PIN outPin
)
{
    MCD_U32 slice;
    MCD_RX_CLOCK_CTRL_TYPE rclkPin;
    MCD_STATUS status;
    MCD_U16 numOfActLanes;;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdSyncEClkConfig: device not initialized\n");
        return MCD_FAIL;
    }

    numOfActLanes = mcdPortModeGetLanesNum(pDev->portConfig[mdioPort].portMode,MCD_LINE_SIDE);
    if (numOfActLanes <= (MCD_U16)laneNum)
    {
        MCD_DBG_ERROR("mcdSyncEClkConfig: Error, num of active lanes is : %u\n", numOfActLanes);
        return MCD_FAIL;
    }

    laneNum += mdioPort;

    if (laneNum >= MAX_SERDES_NUM_IN_SLICE)
    {
        MCD_DBG_ERROR("mcdSyncEClkConfig: incorrect lane selection: %u\n", laneNum);
        return MCD_FAIL;
    }

    slice = ((laneNum > 3)? 1:0);

    status = MCD_SYNCE_VALID_PORT(mdioPort,slice);
    if (status != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSyncEClkConfig: incorrect port selection: %u\n", mdioPort);
        return MCD_FAIL;
    }

    laneNum = laneNum % 4;

    /* set lane number (bits 0-1) */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_RCLK_CNTRL_REGISTER_MAC(slice), 0, 2, laneNum));
    /* set the divider (bits 3-4) */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_RCLK_CNTRL_REGISTER_MAC(slice), 3, 2, (MCD_U32)divider));

    if (outPin == MCD_SCL_SDA)
    {
        /* set GPIO_Data_0_1 to output */
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE,RUNIT_RFU_GPIO_Data_0_1_REGISTER, 0, 32, 0));
        rclkPin = (slice? MCD_RCLK_CTRL1 : MCD_RCLK_CTRL0);
    }
    else if (outPin == MCD_INT_N)
    {
        /* set GPIO_Data_0_1 to input */
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE,RUNIT_RFU_GPIO_Data_0_1_REGISTER, 0, 32, 0xFFFFFFFF));
        rclkPin = MCD_RCLK_CTRL2;
    }
    else
    {
        MCD_DBG_ERROR("mcdSyncEClkConfig: wrong output pin\n");
        return MCD_FAIL;
    }

    /* general output clock configuration*/
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE,RUNIT_SOC_MISC_DEBUG_PORT_CONFIGURATION, 0, 32, 0x6000));

    switch (rclkPin)
    {
    case MCD_RCLK_CTRL0:
        /* set SCL pin as output RCLK pin */
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE,RUNIT_RFU_MPP_Control_0_1_REGISTER, 0, 4, 0x4));
        break;
    case MCD_RCLK_CTRL1:
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE,RUNIT_RFU_MPP_Control_0_1_REGISTER, 4, 4, 0x4));
        break;
    case MCD_RCLK_CTRL2:
        /* set SDA/INTn as output RCLK pin */
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE,RUNIT_SOC_MISC_INTERRUPT_OUT_CONTROL, 0, 2, (1 | (slice<<1))));
        break;
    default:
        MCD_DBG_ERROR("mcdSyncEClkConfig: invalid recovered clock pin\n");
        return MCD_FAIL;
    }

    if (squelchEnable)
    {
        ATTEMPT(mcdSquelchRxClockSet(pDev, mdioPort,(MCD_U32)laneNum, rclkPin));
    }

    return MCD_OK;
}


/*******************************************************************************
 MCD_STATUS mcdSetApManualRxParameters
*******************************************************************************/
MCD_STATUS mcdSetApManualRxParameters
(
    IN  MCD_DEV_PTR  pDev,
    IN  MCD_U16      mdioPort,
    IN  MCD_U16      laneNum,
    IN  MCD_PORT_AP_SERDES_RX_CONFIG *rxOverrideParamsPtr
)
{

    MCD_MAN_TUNE_CTLE_CONFIG_OVERRIDE rxCfg;
    MCD_STATUS status;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdSetApManualRxParmaeters: device not initialized\n");
        return MCD_FAIL;
    }

    MCD_NULL_PTR_CHECK_MAC(rxOverrideParamsPtr);

    if (laneNum >= MCD_MAX_CHANNEL_NUM_PER_SLICE)
    {
        MCD_DBG_ERROR("mcdSetApManualRxParmaeters: incorrect lane selection: %u\n", laneNum);
        return MCD_FAIL;
    }

    mdioPort += laneNum;

    if((rxOverrideParamsPtr->lowFrequency > 15)  ||
       (rxOverrideParamsPtr->highFrequency > 15) ||
       (rxOverrideParamsPtr->bandWidth > 15) ||
       (rxOverrideParamsPtr->loopBandwidth > 15) ||
       (rxOverrideParamsPtr->squelch > 308)||
       ((rxOverrideParamsPtr->serdesSpeed != MCD_25_78125G) && (rxOverrideParamsPtr->serdesSpeed != MCD_10_3125G)) ||
       (rxOverrideParamsPtr->etlMinDelay > 31) ||
       (rxOverrideParamsPtr->etlMaxDelay > 31))
    {
        MCD_DBG_ERROR("mcdSetApManualRxParmaeters: OUT OF RANGE\n");
        return MCD_FAIL;
    }

    rxCfg.ctleParams.dcGain         = rxOverrideParamsPtr->dcGain;
    rxCfg.ctleParams.lowFrequency   = rxOverrideParamsPtr->lowFrequency;
    rxCfg.ctleParams.highFrequency  = rxOverrideParamsPtr->highFrequency;
    rxCfg.ctleParams.bandWidth      = rxOverrideParamsPtr->bandWidth;
    rxCfg.ctleParams.loopBandwidth  = rxOverrideParamsPtr->loopBandwidth;
    rxCfg.ctleParams.squelch        = rxOverrideParamsPtr->squelch;
    rxCfg.fieldOverrideBmp          = rxOverrideParamsPtr->fieldOverrideBmp;
    rxCfg.serdesSpeed               = rxOverrideParamsPtr->serdesSpeed;
    rxCfg.etlParams.etlMinDelay     = rxOverrideParamsPtr->etlMinDelay;
    rxCfg.etlParams.etlMaxDelay     = rxOverrideParamsPtr->etlMaxDelay;
    rxCfg.etlParams.etlEnableOverride = (MCD_U8)rxOverrideParamsPtr->etlEnable;

    status = mcdApSerdesRxParametersManualSetStart(pDev, mdioPort, &rxCfg);
    if (status != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSetApManualRxParmaeters: mcdApSerdesRxParametersManualSetStart failed, mdioPort %d\n", mdioPort);
        return MCD_FAIL;
    }

    return MCD_OK;

}

/*******************************************************************************
 MCD_STATUS mcdSetApManualTxParmaeters
*******************************************************************************/
MCD_STATUS mcdSetApManualTxParameters
(
    IN  MCD_DEV_PTR  pDev,
    IN  MCD_U16      mdioPort,
    IN  MCD_U16      laneNum,
    IN  MCD_PORT_AP_SERDES_TX_CONFIG *txOverrideParamsPtr
)
{

    MCD_STATUS status;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdSetApManualTxParmaeters: device not initialized\n");
        return MCD_FAIL;
    }

    MCD_NULL_PTR_CHECK_MAC(txOverrideParamsPtr);

    if (laneNum >= MCD_MAX_CHANNEL_NUM_PER_SLICE)
    {
        MCD_DBG_ERROR("mcdSetApManualTxParmaeters: incorrect lane selection: %u\n", laneNum);
        return MCD_FAIL;
    }

    mdioPort += laneNum;

    if((txOverrideParamsPtr->txAmp > 31)  ||
       (txOverrideParamsPtr->emph0 > 31) ||
       (txOverrideParamsPtr->emph1 > 31) ||
       ((txOverrideParamsPtr->serdesSpeed != MCD_25_78125G) && (txOverrideParamsPtr->serdesSpeed != MCD_10_3125G)))
    {
        MCD_DBG_ERROR("mcdSetApManualTxParmaeters: OUT OF RANGE\n");
        return MCD_FAIL;
    }

    status = mcdApSerdesTxParametersManualSetStart(pDev, mdioPort, txOverrideParamsPtr);
    if (status != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSetApManualTxParmaeters: mcdApSerdesTxParametersManualSetStart failed, mdioPort %d\n", mdioPort);
        return MCD_FAIL;
    }

    return MCD_OK;

}



/*******************************************************************************
 MCD_STATUS mcdSetLaneSteering
*******************************************************************************/
MCD_STATUS mcdSetLaneSteering
(
    IN  MCD_DEV_PTR  pDev,
    IN  MCD_U16      mdioPort,
    IN  MCD_MASTER_SLICE  masterSlice,
    IN  MCD_LANE_STEERING_MODE  laneSteeringMode,
    IN  MCD_FEC_TYPE  fecCorrect,
    IN  MCD_BOOL      reducedRxTraining,
    IN MCD_MODE_CONFIG_PARAM_PTR configPtr
)
{
    MCD_U16 i, slice;
    MCD_BOOL autoNeg = MCD_FALSE;
    MCD_OP_MODE portMode;
    MCD_U32 rxRemapValue = 0x458;
    MCD_U32 txRemapValue = 0x611;
    MCD_U32 localLaneNum;
    MCD_U32 overridePortIdx;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdSetLaneSteering: device not initialized\n");
        return MCD_FAIL;
    }

    /* initilaize lane steering parmaeters */
    pDev->laneSteeringCfg.laneSteeringEnable = MCD_TRUE;
    pDev->laneSteeringCfg.reducedRxTraining = reducedRxTraining;
    pDev->laneSteeringCfg.masterSlice = masterSlice;
    pDev->portConfig[mdioPort].fecCorrect = fecCorrect;
    pDev->laneSteeringCfg.singlePortEnable[mdioPort] = MCD_FALSE;
    pDev->laneSteeringCfg.externalLpPort[mdioPort] = MCD_LANE_STEERING_NO_LPB;
    pDev->laneSteeringCfg.internalLpPort[mdioPort] = MCD_LANE_STEERING_NO_LPB;
    pDev->laneSteeringCfg.externalLpSerdes[mdioPort] = MCD_LANE_STEERING_NO_LPB;
    pDev->laneSteeringCfg.internalLpSerdes[mdioPort] = MCD_LANE_STEERING_NO_LPB;

    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;

    /* validation */
    ATTEMPT(mcdLaneSteeringModeValidate(pDev, mdioPort, masterSlice, laneSteeringMode));

    if (configPtr->laneSteerCfgPtr != NULL)
    {
        /* memset to zero */
        rxRemapValue = 0;
        txRemapValue = 0;
        overridePortIdx = slice * 4;
        /* build the remap vector in overriden case */
        for (localLaneNum = 0; localLaneNum < MCD_MAX_SERDES_PER_SLICE; localLaneNum++)
        {
            rxRemapValue |= ((configPtr->laneSteerCfgPtr[overridePortIdx+localLaneNum].rxRemap & 0x3) << (localLaneNum * 3));
            txRemapValue |= ((configPtr->laneSteerCfgPtr[overridePortIdx+localLaneNum].txRemap & 0x3) << (localLaneNum * 3));
        }
    }
    /* apply remap SerDes values for Tx direction slice 0 */
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0,UMAC_SERDESMUX_laneremaptx(0),txRemapValue));
    /* apply remap SerDes values for Rx direction slice 0 */
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0,UMAC_SERDESMUX_laneremaprx(0),rxRemapValue));
    /* apply remap SerDes values for Tx direction slice 1 */
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0,UMAC_SERDESMUX_laneremaptx(1),txRemapValue));
    /* apply remap SerDes values for Rx direction slice 1 */
    ATTEMPT(mcdHwXmdioWrite32bit(pDev, 0,UMAC_SERDESMUX_laneremaprx(1),rxRemapValue));

    /* update master slice remap data base for lane steering single mode */
    ATTEMPT(mcdLaneSteeringRemapVectorRebuild(pDev, mdioPort, slice, laneSteeringMode, configPtr->laneSteerCfgPtr));

    switch (laneSteeringMode)
    {
        case MCD_P100G_STEERING:
            ATTEMPT(mcdSetModeSelectionExt(pDev, mdioPort, MCD_MODE_P100S, MCD_FALSE,fecCorrect,configPtr));
            ATTEMPT(mcdLaneSteeringOtherSideCfg(pDev, mdioPort, MCD_MODE_P100S, masterSlice, MCD_25_78125G));
            break;
        case  MCD_P40G_STEERING:
            ATTEMPT(mcdSetModeSelectionExt(pDev, mdioPort, MCD_MODE_P40S, MCD_FALSE,fecCorrect,configPtr));
            ATTEMPT(mcdLaneSteeringOtherSideCfg(pDev, mdioPort, MCD_MODE_P40S, masterSlice, MCD_10_3125G));
            break;
        case MCD_4P_P25G_STEERING:
            for (i = 0; i < MCD_MAX_CHANNEL_NUM_PER_SLICE; i++)
            {
                ATTEMPT(mcdSetModeSelectionExt(pDev, mdioPort+i, MCD_MODE_P25S, MCD_FALSE, fecCorrect, configPtr));
            }
            ATTEMPT(mcdLaneSteeringOtherSideCfg(pDev, mdioPort, MCD_MODE_P25S, masterSlice, MCD_25_78125G));
            break;
        case MCD_4P_P10G_STEERING:
            for (i = 0; i < MCD_MAX_CHANNEL_NUM_PER_SLICE; i++)
            {
                ATTEMPT(mcdSetModeSelectionExt(pDev, mdioPort+i, MCD_MODE_P10S, MCD_FALSE, fecCorrect, configPtr));
            }
            ATTEMPT(mcdLaneSteeringOtherSideCfg(pDev, mdioPort, MCD_MODE_P10S, masterSlice, MCD_10_3125G));
            break;
        case MCD_4P_P1G_1000BaseX_STEERING:
            if (configPtr->configApPtr != NULL)
            {
                autoNeg = configPtr->configApPtr->apEnable;
            }
            for (i = 0; i < MCD_MAX_CHANNEL_NUM_PER_SLICE; i++)
            {
                ATTEMPT(mcdSetModeSelectionExt(pDev, mdioPort+i, MCD_MODE_P1, autoNeg, fecCorrect, configPtr));
            }
            return mcdLaneSteeringOtherSideCfg(pDev, mdioPort, MCD_MODE_P1, masterSlice, MCD_1_25G);
        case MCD_4P_P1G_SGMII_STEERING:
            if (configPtr->configApPtr != NULL)
            {
                autoNeg = configPtr->configApPtr->apEnable;
            }
            for (i = 0; i < MCD_MAX_CHANNEL_NUM_PER_SLICE; i++)
            {
                ATTEMPT(mcdSetModeSelectionExt(pDev, mdioPort+i, MCD_MODE_P1_SGMII, autoNeg, fecCorrect, configPtr));
            }
            return mcdLaneSteeringOtherSideCfg(pDev, mdioPort, MCD_MODE_P1_SGMII, masterSlice, MCD_1_25G);
        case MCD_P100G_P40G_P10G_STEERING_AP:
            /*
            MCD_AN_10GBase_KR                             0x0004
            MCD_AN_40GBASE_KR4                            0x0008
            MCD_AN_40GBASE_CR4                            0x0010
            MCD_AN_100GBASE_KR4                           0x0080
            MCD_AN_100GBASE_CR4                           0x0100
            */
            if (configPtr->configApPtr != NULL)
            {
                if ((configPtr->configApPtr->modeVector) & (MCD_AN_10GBase_KR |
                            MCD_AN_40GBASE_KR4 | MCD_AN_40GBASE_CR4 |
                            MCD_AN_100GBASE_KR4 | MCD_AN_100GBASE_CR4))
                {
                    return mcdSetModeSelectionExt(pDev, mdioPort, MCD_MODE_UNKNOWN, MCD_TRUE, fecCorrect, configPtr);
                }
                else
                {
                    MCD_DBG_ERROR("mcdSetLaneSteering: modeVector not supported %d \n", configPtr->configApPtr->modeVector);
                    return MCD_FAIL;
                }
            }
            else
            {
                MCD_DBG_ERROR("mcdSetLaneSteering: configApPtr is NULL \n");
                return MCD_FAIL;
            }
                break;
        case MCD_4P_P25G_STEERING_AP:
            for (i = 0; i< MCD_MAX_CHANNEL_NUM_PER_SLICE; i++)
            {
                ATTEMPT(mcdSetModeSelectionExt(pDev, mdioPort+i, MCD_MODE_P25L, MCD_TRUE, fecCorrect, configPtr));
            }
            ATTEMPT(mcdLaneSteeringOtherSideCfg(pDev, mdioPort, MCD_MODE_P25L, masterSlice, MCD_25_78125G));
                break;
        case MCD_4P_P10G_STEERING_AP:
            for (i = 0; i< MCD_MAX_CHANNEL_NUM_PER_SLICE; i++)
            {
                ATTEMPT(mcdSetModeSelectionExt(pDev, mdioPort+i, MCD_MODE_P10S, MCD_TRUE, fecCorrect, configPtr));
            }
            ATTEMPT(mcdLaneSteeringOtherSideCfg(pDev, mdioPort, MCD_MODE_P10S, masterSlice, MCD_10_3125G));
                break;
        case MCD_G21L_NONE_STEERING:
            ATTEMPT(mcdSetModeSelectionExt(pDev, mdioPort, MCD_MODE_G21L, MCD_FALSE,fecCorrect,configPtr));
                break;
        case MCD_G21L_P10G_NONE_STEERING_AP:
            /*
            MCD_AN_10GBase_KR                             0x0004
            MCD_AN_40GBASE_KR4                            0x0008
            MCD_AN_40GBASE_CR4                            0x0010
            */
            if (configPtr->configApPtr != NULL)
            {
                if (configPtr->configApPtr->g21Mode == 0)
                {
                    MCD_DBG_ERROR("mcdSetLaneSteering: G21L mode flag is disabled %d \n", configPtr->configApPtr->g21Mode);
                    return MCD_FAIL;
                }
                if ((configPtr->configApPtr->modeVector) & (MCD_AN_10GBase_KR |
                            MCD_AN_40GBASE_KR4 | MCD_AN_40GBASE_CR4))
                {
                    return mcdSetModeSelectionExt(pDev, mdioPort, MCD_MODE_UNKNOWN, MCD_TRUE, fecCorrect, configPtr);
                }
                else
                {
                    MCD_DBG_ERROR("mcdSetLaneSteering: modeVector not supported %d \n", configPtr->configApPtr->modeVector);
                    return MCD_FAIL;
                }
            }
            else
            {
                MCD_DBG_ERROR("mcdSetLaneSteering: configApPtr is NULL \n");
                return MCD_FAIL;
            }
                break;
        case MCD_1P_P25G_STEERING:
            pDev->laneSteeringCfg.singlePortEnable[mdioPort] = MCD_TRUE;
            ATTEMPT(mcdSetModeSelectionExt(pDev, mdioPort, MCD_MODE_P25S, MCD_FALSE,fecCorrect,configPtr));
            ATTEMPT(mcdLaneSteeringOtherSideCfg(pDev, mdioPort, MCD_MODE_P25S, masterSlice, MCD_25_78125G));
            return mcdLaneSteeringSingleModeTune(pDev, mdioPort, masterSlice);
            break;
        case MCD_1P_P10G_STEERING:
            pDev->laneSteeringCfg.singlePortEnable[mdioPort] = MCD_TRUE;
            ATTEMPT(mcdSetModeSelectionExt(pDev, mdioPort, MCD_MODE_P10S, MCD_FALSE,fecCorrect,configPtr));
            ATTEMPT(mcdLaneSteeringOtherSideCfg(pDev, mdioPort, MCD_MODE_P10S, masterSlice, MCD_10_3125G));
            return mcdLaneSteeringSingleModeTune(pDev, mdioPort, masterSlice);
            break;
        case MCD_1P_P10G_25G_STEERING_AP:
            /*
            MCD_AN_10GBase_KR                             0x0004
            MCD_AN_25GBase_KR1S                           0x0200
            MCD_AN_25GBASE_KCR                            0x0400
            */
            pDev->laneSteeringCfg.singlePortEnable[mdioPort] = MCD_TRUE;
            if (configPtr->configApPtr != NULL)
            {
                if ((configPtr->configApPtr->modeVector) & (MCD_AN_10GBase_KR |
                            MCD_AN_25GBase_KR1S | MCD_AN_25GBASE_KCR))
                {
                    return mcdSetModeSelectionExt(pDev, mdioPort, MCD_MODE_UNKNOWN, MCD_TRUE, fecCorrect, configPtr);
                }
                else
                {
                    MCD_DBG_ERROR("mcdSetLaneSteering: modeVector not supported %d \n", configPtr->configApPtr->modeVector);
                    return MCD_FAIL;
                }
            }
            else
            {
                MCD_DBG_ERROR("mcdSetLaneSteering: configApPtr is NULL \n");
                return MCD_FAIL;
            }
            break;
        case MCD_1P_P1G_1000BaseX_STEERING:
        case MCD_1P_P1G_SGMII_STEERING:
            pDev->laneSteeringCfg.singlePortEnable[mdioPort] = MCD_TRUE;
            if (configPtr->configApPtr != NULL)
            {
                autoNeg = configPtr->configApPtr->apEnable;
            }
            portMode = (laneSteeringMode == MCD_1P_P1G_1000BaseX_STEERING) ? MCD_MODE_P1 : MCD_MODE_P1_SGMII;
            ATTEMPT(mcdSetModeSelectionExt(pDev, mdioPort, portMode, autoNeg, fecCorrect, configPtr));
            return mcdLaneSteeringOtherSideCfg(pDev, mdioPort, portMode, masterSlice, MCD_1_25G);
            default:
                MCD_DBG_ERROR("mcdSetLaneSteering: unknown laneSteeringMode %d \n", laneSteeringMode);
                return MCD_FAIL;
    }

    if ((laneSteeringMode != MCD_P100G_P40G_P10G_STEERING_AP) &&
        (laneSteeringMode != MCD_G21L_P10G_NONE_STEERING_AP) && (laneSteeringMode !=MCD_1P_P10G_25G_STEERING_AP))
    {
        /* Run Special Rx Training for lane steering mode */
        ATTEMPT(mcdLaneSteeringAutoTuneStart(pDev, slice, masterSlice));
    }

    return MCD_OK;

}

/*******************************************************************************
 MCD_STATUS mcdSetLaneRemapping
*******************************************************************************/
MCD_STATUS mcdSetLaneRemapping
(
    IN  MCD_DEV_PTR  pDev,
    IN  MCD_U16      host_or_line,
    IN  MCD_U16      sliceNum,
    IN  MCD_SERDES_TXRX_LANE_REMAP (*configSerdesRemapPtr)[MCD_MAX_SLICE_NUM]
)
{
#ifndef ASIC_SIMULATION
    MCD_U32 txRemapVector = 0, rxRemapVector = 0;
    MCD_U8 serdesLaneNum, startHostRmap = 4;

    if (!pDev->devEnabled)
    {
        MCD_DBG_ERROR("mcdSetLaneRemapping: device not initialized\n");
        return MCD_FAIL;
    }

    if (configSerdesRemapPtr != NULL)
    {
        for (serdesLaneNum = 0; serdesLaneNum < MCD_MAX_SERDES; serdesLaneNum++)
        {
            serdesTxRxLaneRemap[serdesLaneNum][sliceNum].txRemap = (*configSerdesRemapPtr)[sliceNum].txRemap;
            serdesTxRxLaneRemap[serdesLaneNum][sliceNum].rxRemap = (*configSerdesRemapPtr)[sliceNum].rxRemap;
            configSerdesRemapPtr++;
        }
    }
    else
    {
        MCD_DBG_ERROR("mcdSetLaneRemapping: configSerdesRemapPtr is NULL\n");
        return MCD_FAIL;
    }

    if (host_or_line == MCD_HOST_SIDE)
    {
        for (serdesLaneNum=0; serdesLaneNum < MCD_MAX_SERDES_PER_SLICE; serdesLaneNum++)
        {
            /* Construct data for Host Port Remap */
            txRemapVector |= ((serdesTxRxLaneRemap[serdesLaneNum + startHostRmap][sliceNum].txRemap) << (serdesLaneNum * 3));
            rxRemapVector |= ((serdesTxRxLaneRemap[serdesLaneNum + startHostRmap][sliceNum].rxRemap) << (serdesLaneNum * 3));
        }
        ATTEMPT(mcdHwXmdioWrite32bit(pDev, DONT_CARE, UMAC_SERDESMUX_laneremaptx(sliceNum),txRemapVector));
        ATTEMPT(mcdHwXmdioWrite32bit(pDev, DONT_CARE, UMAC_SERDESMUX_laneremaprx(sliceNum),rxRemapVector));

        /* update pDev structure to operate in remap mode for host */
        pDev->laneRemapCfg[sliceNum].hostRemapMode = MCD_LANE_REMAP_ENABLE;
        pDev->laneRemapCfg[sliceNum].hostTxRemapVector = (MCD_U16)txRemapVector;
        pDev->laneRemapCfg[sliceNum].hostRxRemapVector = (MCD_U16)rxRemapVector;
    }
    else if (host_or_line == MCD_LINE_SIDE)
    {
        for (serdesLaneNum=0; serdesLaneNum < MCD_MAX_SERDES_PER_SLICE; serdesLaneNum++)
        {
            /* Construct data for Line Port Remap */
            txRemapVector |= ((serdesTxRxLaneRemap[(serdesLaneNum)][sliceNum].txRemap) << (serdesLaneNum * 3));
            rxRemapVector |= ((serdesTxRxLaneRemap[(serdesLaneNum)][sliceNum].rxRemap) << (serdesLaneNum * 3));
        }

        ATTEMPT(mcdHwXmdioWrite32bit(pDev, DONT_CARE, UMAC_LSMCPCS_LINE_REG_ADDR(UMAC_SERDESMUX_laneremaptx(sliceNum)),txRemapVector));
        ATTEMPT(mcdHwXmdioWrite32bit(pDev, DONT_CARE, UMAC_LSMCPCS_LINE_REG_ADDR(UMAC_SERDESMUX_laneremaprx(sliceNum)),rxRemapVector));

        /* update pDev structure to operate in remap mode for line */
        pDev->laneRemapCfg[sliceNum].lineRemapMode = MCD_LANE_REMAP_ENABLE;
        pDev->laneRemapCfg[sliceNum].lineTxRemapVector = (MCD_U16)txRemapVector;
        pDev->laneRemapCfg[sliceNum].lineRxRemapVector = (MCD_U16)rxRemapVector;
    }



#endif  /* ASIC_SIMULATION */
    return MCD_OK;
}


/*******************************************************************
  MCD_STATUS mcdSetPortLoopback
  lbMode options are:
    MCD_CLEAR_SERDES_LOOPBACK 0
    MCD_DEEP_SERDES_LOOPBACK 1
    MCD_SHALLOW_SERDES_LOOPBACK 2
    MCD_PARALLEL_SERDES_LOOPBACK 2
*******************************************************************/
MCD_STATUS mcdSetPortLoopback
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U16 mdioPort,
    IN  MCD_OP_MODE portMode,
    IN  MCD_U16 host_or_line,
    IN  MCD_U32  lbMode
)
{
    MCD_U16 lanesNum, laneOffset, sAddr, slice, chan;

    if (lbMode > MCD_PARALLEL_SERDES_LOOPBACK)
    {
        MCD_DBG_ERROR("mcdSetPortLoopback: loopback mode not supported %d \n", lbMode);
        return MCD_FAIL;
    }
    lanesNum = mcdPortModeGetLanesNum(portMode, host_or_line);
    slice = mdioPort / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan  = CHAN_IN_SLICE_NUM(mdioPort);

    for (laneOffset = 0; laneOffset < lanesNum; laneOffset++)
    {
        sAddr = (MCD_U16)MCD_SERDES_LANE_SBUS_ADDR(host_or_line, slice, (chan + laneOffset));
        ATTEMPT(mcdSerdesSetLoopback(pDev, sAddr, lbMode));
    }

    if (lbMode == MCD_CLEAR_SERDES_LOOPBACK)
    {
        ATTEMPT(mcdChannelSwReset(pDev, mdioPort, MCD_TRUE));
        ATTEMPT(mcdChannelSwReset(pDev, mdioPort, MCD_FALSE));
        if (mcdSetModeSelectionExtPortPollingMessageDisable == 0)
        {
            /* restart cm3 machine */
            ATTEMPT(mcdPortPollingLinkStatusStop(pDev, mdioPort));
            ATTEMPT(mcdPortPollingLinkStatusStart(pDev, mdioPort));
        }
    }

    return MCD_OK;
}
