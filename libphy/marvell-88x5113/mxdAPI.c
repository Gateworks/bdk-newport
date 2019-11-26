/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/**********************************************************************
This file contains function prototypes for mode selections, interrupts
and real-time controls, configurations and status for the Marvell
X5113 PHY.
**********************************************************************/
#include "mxdApiTypes.h"
#include "mxdApiRegs.h"
#include "mxdUtils.h"
#include "mxdHwCntl.h"
#include "mxdDiagnostics.h"
#include "mxdAPI.h"
#include "mxdAPIInternal.h"
#include "mxdInitialization.h"

/* portModeTbl needs to match up with MXD_FIXED_OP_MODE */
/* Table format */
/*   HOST MXD_OP_CONFIG  LINE MXD_OP_CONFIG  GROUP          */
/*----------------------------------------------------------*/
static const MXD_MODE_TABLE portModeTbl[MXD_MODE_NUM] =
   {{MXD_CONFIG_UNKNOWN, MXD_CONFIG_UNKNOWN},
    {MXD_P1X,            MXD_P1P           },
    {MXD_P1X,            MXD_P1X           },

    {MXD_P10LN,          MXD_P10LF         },
    {MXD_P10LN,          MXD_P10LN         },
    {MXD_P10LN,          MXD_P10KF         },
    {MXD_P10LN,          MXD_P10KN         },

    {MXD_P10KN,          MXD_P10LN         },
    {MXD_P10KN,          MXD_P10KN         },
    {MXD_P10KN,          MXD_P10KF         },
    {MXD_P10KF,          MXD_P10KF         },

    {MXD_P25CF,          MXD_P25BR         },
    {MXD_P25CF,          MXD_P25CF         },
    {MXD_P25CF,          MXD_P25CR         },

    {MXD_P25CN,          MXD_P25BF         },
    {MXD_P25CN,          MXD_P25BN         },
    {MXD_P25CN,          MXD_P25BR         },
    {MXD_P25CN,          MXD_P25CF         },
    {MXD_P25CN,          MXD_P25CN         },
    {MXD_P25CN,          MXD_P25CR         },

    {MXD_P25CR,          MXD_P25BR         },
    {MXD_P25CR,          MXD_P25CR         },

    {MXD_P25KF,          MXD_P25JF         },
    {MXD_P25KF,          MXD_P25JR         },
    {MXD_P25KF,          MXD_P25KF         },
    {MXD_P25KF,          MXD_P25KR         },

    {MXD_P25KN,          MXD_P25JF         },
    {MXD_P25KN,          MXD_P25JN         },
    {MXD_P25KN,          MXD_P25JR         },
    {MXD_P25KN,          MXD_P25KF         },
    {MXD_P25KN,          MXD_P25KN         },
    {MXD_P25KN,          MXD_P25KR         },

    {MXD_P25KR,          MXD_P25JR         },
    {MXD_P25KR,          MXD_P25KR         },

    {MXD_P25LF,          MXD_P25LF         },
    {MXD_P25LF,          MXD_P25LR         },

    {MXD_P25LN,          MXD_P25LF         },
    {MXD_P25LN,          MXD_P25LN         },
    {MXD_P25LN,          MXD_P25LR         },
    {MXD_P25LR,          MXD_P25LR         },

    {MXD_P40LN,          MXD_P25CN         },
    {MXD_P40LN,          MXD_P25CF         },
    {MXD_P40LN,          MXD_P25CR         },
    {MXD_P40LN,          MXD_P25BN         },
    {MXD_P40LN,          MXD_P25BF         },
    {MXD_P40LN,          MXD_P25BR         },
    {MXD_P40LN,          MXD_P25LF         },
    {MXD_P40LN,          MXD_P25LR         },
    {MXD_P40LN,          MXD_P25LN         },

    {MXD_P40KN,          MXD_P25CN         },
    {MXD_P40KN,          MXD_P25CF         },
    {MXD_P40KN,          MXD_P25CR         },
    {MXD_P40KN,          MXD_P25BN         },
    {MXD_P40KN,          MXD_P25BF         },
    {MXD_P40KN,          MXD_P25BR         },
    {MXD_P40KN,          MXD_P25LR         },

    {MXD_P40KN,          MXD_P25KN         },
    {MXD_P40KN,          MXD_P25KF         },
    {MXD_P40KN,          MXD_P25KR         },
    {MXD_P40KF,          MXD_P25KN         },
    {MXD_P40KF,          MXD_P25KF         },
    {MXD_P40KF,          MXD_P25KR         },

    {MXD_P40KN,          MXD_P25JN         },
    {MXD_P40KN,          MXD_P25JF         },
    {MXD_P40KN,          MXD_P25JR         },
    {MXD_P40KF,          MXD_P25JN         },
    {MXD_P40KF,          MXD_P25JF         },
    {MXD_P40KF,          MXD_P25JR         },

    {MXD_P40LN,          MXD_P25BCN        },
    {MXD_P40LN,          MXD_P25BCF        },
    {MXD_P40LN,          MXD_P25BCR        },
    {MXD_P40KN,          MXD_P25BCN        },
    {MXD_P40KN,          MXD_P25BCF        },
    {MXD_P40KN,          MXD_P25BCR        },

    {MXD_P40KN,          MXD_P25JKN        },
    {MXD_P40KN,          MXD_P25JKF        },
    {MXD_P40KN,          MXD_P25JKR        },
    {MXD_P40KF,          MXD_P25JKN        },
    {MXD_P40KF,          MXD_P25JKF        },
    {MXD_P40KF,          MXD_P25JKR        },

    {MXD_P40CN,          MXD_P40CN         },
    {MXD_P40CN,          MXD_P40CF         },
    {MXD_P40CF,          MXD_P40CF         },
    {MXD_P40KN,          MXD_P40KN         },
    {MXD_P40KN,          MXD_P40KF         },
    {MXD_P40KF,          MXD_P40KF         },
    {MXD_P40LN,          MXD_P40LN         },

    {MXD_P50BN,          MXD_P50BN         },
    {MXD_P50BN,          MXD_P50BF         },
    {MXD_P50BN,          MXD_P50BR         },
    {MXD_P50BF,          MXD_P50BF         },
    {MXD_P50BF,          MXD_P50BR         },
    {MXD_P50BR,          MXD_P50BR         },

    {MXD_P50JN,          MXD_P50JN         },
    {MXD_P50JN,          MXD_P50JF         },
    {MXD_P50JN,          MXD_P50JR         },
    {MXD_P50JF,          MXD_P50JF         },
    {MXD_P50JF,          MXD_P50JR         },
    {MXD_P50JR,          MXD_P50JR         },

    {MXD_P50MN,          MXD_P50MN         },
    {MXD_P50MN,          MXD_P50MF         },
    {MXD_P50MN,          MXD_P50MR         },
    {MXD_P50MF,          MXD_P50MF         },
    {MXD_P50MF,          MXD_P50MR         },
    {MXD_P50MR,          MXD_P50MR         },

    {MXD_P50LN,          MXD_P50BN         },
    {MXD_P50LN,          MXD_P50BF         },
    {MXD_P50LN,          MXD_P50BR         },
    {MXD_P50LF,          MXD_P50BN         },
    {MXD_P50LF,          MXD_P50BF         },
    {MXD_P50LF,          MXD_P50BR         },

    {MXD_P50LN,          MXD_P50JN         },
    {MXD_P50LN,          MXD_P50JF         },
    {MXD_P50LN,          MXD_P50JR         },
    {MXD_P50LF,          MXD_P50JN         },
    {MXD_P50LF,          MXD_P50JF         },
    {MXD_P50LF,          MXD_P50JR         },

    {MXD_P50LN,          MXD_P50MN         },
    {MXD_P50LN,          MXD_P50MF         },
    {MXD_P50LN,          MXD_P50MR         },
    {MXD_P50LF,          MXD_P50MN         },
    {MXD_P50LF,          MXD_P50MF         },
    {MXD_P50LF,          MXD_P50MR         },

    {MXD_P50CF,          MXD_P50CN         },
    {MXD_P50KF,          MXD_P50KN         },

    {MXD_P100CR,         MXD_P100CR        },
    {MXD_P100KR,         MXD_P100KR        },
    {MXD_P100LN,         MXD_P100LR        },
    {MXD_P100LR,         MXD_P100LR        },

    {MXD_R1,             MXD_R1            },
    {MXD_R10L,           MXD_R10L          },
    {MXD_R25L,           MXD_R25L          },
    {MXD_R40L,           MXD_R40L          },
    {MXD_R100L,          MXD_R100L         }
};

/*******************************************************************************
 MXD_VOID mxdGetAPIVersion
*******************************************************************************/
MXD_VOID mxdGetAPIVersion
(
    OUT MXD_U8 *major,
    OUT MXD_U8 *minor,
    OUT MXD_U8 *buildID
)
{
    *major = MXD_API_MAJOR_VERSION;
    *minor = MXD_API_MINOR_VERSION;
    *buildID = MXD_API_BUILD_ID;
}


/*******************************************************************************
 MXD_STATUS mxdSetFixedModeSelection
*******************************************************************************/
MXD_STATUS mxdSetFixedModeSelection
(
     IN MXD_DEV_PTR pDev,
     IN MXD_U16     mdioPort,
     IN MXD_U16     laneOffset,
     IN MXD_FIXED_OP_MODE portMode,
     IN MXD_BOOL    forceReConfig,
     OUT MXD_U16    *result
)
{
    MXD_OP_CONFIG lineMode, hostMode;

    *result = MXD_STATUS_MODE_GENERAL_ERROR;

    if ((portMode == MXD_MODE_UNKNOWN) || (portMode >= MXD_MODE_NUM))
    {
        MXD_DBG_ERROR("mxdSetFixedModeSelection: Invalid portMode!\n");
        return MXD_FAIL;
    }

    hostMode = portModeTbl[portMode].hostOpMode;
    lineMode = portModeTbl[portMode].lineOpMode;

    if (mxdSetUserFixedModeSelection(pDev, mdioPort, laneOffset, hostMode, lineMode, forceReConfig, result) == MXD_FAIL)
    {
        pDev->opMode[laneOffset] = MXD_MODE_UNKNOWN;
        MXD_DBG_ERROR("mxdSetFixedModeSelection: Failed\n");
        return MXD_FAIL;
    }

    pDev->opMode[laneOffset] = portMode;

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdSetUserFixedModeSelection
*******************************************************************************/
MXD_STATUS mxdSetUserFixedModeSelection
(
     IN MXD_DEV_PTR   pDev,
     IN MXD_U16       mdioPort,
     IN MXD_U16       laneOffset,
     IN MXD_OP_CONFIG hostMode,
     IN MXD_OP_CONFIG lineMode,
     IN MXD_BOOL      forceReConfig,
     OUT MXD_U16      *result
)
{
    MXD_U16 lineSpeed, hostSpeed, linePause[MXD_NUM_LANES], hostPause[MXD_NUM_LANES];
    MXD_U16 initState,i;
    *result = MXD_STATUS_MODE_GENERAL_ERROR;

    if (mxdIsOpModeValid(pDev,hostMode,lineMode) == MXD_FAIL)
    {
        MXD_DBG_ERROR("mxdSetUserFixedModeSelection: incorrect OP mode hostMode:%u; lineMode:%u\n", hostMode, lineMode);
        *result = MXD_STATUS_MODE_HOST_LINE_ERROR;
        return MXD_FAIL;
    }

    hostSpeed = portConfigTbl[hostMode][SPEED_IDX];
    lineSpeed = portConfigTbl[lineMode][SPEED_IDX];

    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdSetUserFixedModeSelection: device not initialized\n");
        *result = MXD_STATUS_MODE_GENERAL_ERROR;
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    /* check lane offset is valid */
    if (laneOffset >= MXD_NUM_LANES)
    {
        MXD_DBG_ERROR("mxdSetUserFixedModeSelection: incorrect lane selection: %u\n", laneOffset);
        *result = MXD_STATUS_MODE_GENERAL_ERROR;
        return MXD_FAIL;
    }

    initState = MXD_MODE_UNKNOWN;
    for (i=0; i<MXD_NUM_LANES; i++)
    {
        if (pDev->opMode[i] != MXD_MODE_UNKNOWN)
        {
            initState = pDev->opMode[i];
        }
    }

    if ((initState == MXD_MODE_UNKNOWN) || (forceReConfig == MXD_TRUE))
    {
        /* initial config and mode structures */
        mxdMemSet(pDev->opMode, 0, (sizeof(MXD_FIXED_OP_MODE)*MXD_NUM_LANES));
        /* save line and host autoNegAdvPause setting */
        for (i=0;i<MXD_NUM_LANES; i++)
        {
            linePause[i] = pDev->lineConfig[i].autoNegAdvPause;
            hostPause[i] = pDev->hostConfig[i].autoNegAdvPause;
        }
        mxdMemSet(pDev->hostConfig, 0, (sizeof(MXD_MODE_CONFIG)*MXD_NUM_LANES));
        mxdMemSet(pDev->lineConfig, 0, (sizeof(MXD_MODE_CONFIG)*MXD_NUM_LANES));
        /* restore line and host autoNegAdvPause setting */
        for (i=0;i<MXD_NUM_LANES; i++)
        {
            pDev->lineConfig[i].autoNegAdvPause = linePause[i];
            pDev->hostConfig[i].autoNegAdvPause = hostPause[i];
        }
        ATTEMPT(mxdPortPowerHwReset(pDev, mdioPort));

        /* reset the devInfo bit to 0 for non-group  */
        pDev->devInfo &= ~MXD_LANES_GROUPED;
        if (portConfigTbl[hostMode][SPEED_IDX] >= MXD_40GB)
        {
            pDev->devInfo |= MXD_LANES_GROUPED;
        }
    }
    else
    {
        /* at least one lane has been initialized */
        if (pDev->devInfo & MXD_LANES_GROUPED)
        {
            if (hostSpeed < MXD_40GB)
            {
                MXD_DBG_ERROR("mxdSetUserFixedModeSelection: Set forceReConfig to change from group to ungroup mode\n");
                *result = MXD_STATUS_MODE_NON_GROUP_ERROR;
                return MXD_FAIL;
            }
        }
        else
        {
            if (hostSpeed >= MXD_40GB)
            {
                MXD_DBG_ERROR("mxdSetUserFixedModeSelection: Set forceReConfig to change ungroup to group mode\n");
                *result = MXD_STATUS_MODE_GROUP_ERROR;
                return MXD_FAIL;
            }
        }
    }

    pDev->opMode[laneOffset] = MXD_MODE_USER_DEFINED;

    pDev->lineConfig[laneOffset].opConfig = lineMode;
    if (mxdSetFixedMode(pDev, mdioPort, MXD_LINE_SIDE, laneOffset, lineMode) == MXD_FAIL)
    {
        pDev->opMode[laneOffset] = MXD_MODE_UNKNOWN;
        MXD_DBG_ERROR("mxdSetUserFixedModeSelection: mxdSetFixedMode line side failed\n");
        *result = MXD_STATUS_MODE_GENERAL_ERROR;
        return MXD_FAIL;
    }

    pDev->hostConfig[laneOffset].opConfig = hostMode;
    if (hostMode != MXD_CONFIG_UNKNOWN)
    {
        if (mxdSetFixedMode(pDev, mdioPort, MXD_HOST_SIDE, laneOffset, hostMode) == MXD_FAIL)
        {
            pDev->opMode[laneOffset] = MXD_MODE_UNKNOWN;
            MXD_DBG_ERROR("mxdSetUserFixedModeSelection: mxdSetFixedMode host side failed\n");
            *result = MXD_STATUS_MODE_GENERAL_ERROR;
            return MXD_FAIL;
        }
    }

    if (hostSpeed != lineSpeed)
    {
        pDev->devInfo |= MXD_GEARBOX_MODE;
    }
    else
    {
        pDev->devInfo &= ~MXD_GEARBOX_MODE;
    }

    *result = MXD_STATUS_MODE_SUCCESS;
    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetFixedModeSelection
   Get Operational mode, host and line modes
******************************************************************************/
MXD_STATUS mxdGetFixedModeSelection
(
     IN MXD_DEV_PTR      pDev,
     IN MXD_U16          mdioPort,
     OUT MXD_FIXED_OP_MODE opMode[MXD_NUM_LANES],
     OUT MXD_OP_CONFIG   hostMode[MXD_NUM_LANES],
     OUT MXD_OP_CONFIG   lineMode[MXD_NUM_LANES],
     OUT MXD_U16         *groupMode
)
{
    MXD_U16 laneIdx;

    for (laneIdx=0; laneIdx<MXD_NUM_LANES; laneIdx++)
    {
        opMode[laneIdx] = pDev->opMode[laneIdx];
        hostMode[laneIdx] = pDev->hostConfig[laneIdx].opConfig;
        lineMode[laneIdx] = pDev->lineConfig[laneIdx].opConfig;
    }

    if (pDev->devInfo & MXD_LANES_GROUPED)
    {
        *groupMode = 1;
    }
    else
    {
        *groupMode = 0;
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdSetPauseAdvertisement
    Set Auto-neg Pause advertisment
*******************************************************************************/
MXD_STATUS mxdSetPauseAdvertisement
(
     IN MXD_DEV_PTR pDev,
     IN MXD_U16  mdioPort,
     IN MXD_U16  host_or_line,
     IN MXD_U16  laneOffset,
     IN MXD_U8   pauseType,
     IN MXD_BOOL anRestart
)
{
    MXD_OP_CONFIG modeConfig;

    /* sets/clears bits 11, 10 (A6,A5 in the tech bit field of 7.16) */
    if (host_or_line == MXD_LINE_SIDE)
    {
        pDev->lineConfig[laneOffset].autoNegAdvPause = pauseType;
    }
    else if (host_or_line == MXD_HOST_SIDE)
    {
        pDev->hostConfig[laneOffset].autoNegAdvPause = pauseType;
    }
    else
    {
        MXD_DBG_ERROR("mxdSetPauseAdvertisement: Incorrect line_or_host selection: \n");
        return MXD_FAIL;
    }

    if(anRestart)
    {
        if (host_or_line == MXD_LINE_SIDE)
        {
             modeConfig = pDev->lineConfig[laneOffset].opConfig;
        }
        else if (host_or_line == MXD_HOST_SIDE)
        {
             modeConfig = pDev->hostConfig[laneOffset].opConfig;
        }
        else
        {
            MXD_DBG_ERROR("mxdSetPauseAdvertisement: Incorrect line_or_host selection: \n");
            return MXD_FAIL;
        }

        if (mxdAutoNegStart(pDev,mdioPort,host_or_line, laneOffset, modeConfig, MXD_TRUE) != MXD_OK)
        {
            MXD_DBG_ERROR("mxdSetPauseAdvertisement: AutoNeg start fail!\n");
            return MXD_FAIL;
        }
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetPauseAdvertisement
    Get Local Auto-neg Pause advertisment
*******************************************************************************/
MXD_STATUS mxdGetPauseAdvertisement
(
     IN MXD_DEV_PTR pDev,
     IN MXD_U16 mdioPort,
     IN MXD_U16 host_or_line,
     IN MXD_U16 laneOffset,
     OUT MXD_U8 *pauseType
)
{
    MXD_U16 val;

    *pauseType = MXD_CLEAR_PAUSE;

    /* sets/clears bits 11, 10 (A6,A5 in the tech bit field of 7.16) */
    if (host_or_line == MXD_LINE_SIDE)
    {
        ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_ADV1_LINE+(laneOffset*0x200)), \
                        10, 2, &val));
    }
    else if (host_or_line == MXD_HOST_SIDE)
    {
        ATTEMPT(mxdHwGetPhyRegField(pDev,mdioPort, MXD_AUTONEG, (MXD_AUTONEG_ADV1_HOST+(laneOffset*0x200)), \
                        10, 2, &val));
    }
    else
    {
        MXD_DBG_ERROR("mxdGetPauseAdvertisement: Incorrect line_or_host selection: \n");
        return MXD_FAIL;
    }

    *pauseType = (MXD_U8)(val & 0x3);

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetLPAdvertisedPause
    Get Link Partner Auto-neg Pause advertisment
*******************************************************************************/
MXD_STATUS mxdGetLPAdvertisedPause
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U8 *pauseType
)
{
     MXD_U16 val;

     *pauseType = MXD_CLEAR_PAUSE;

     /* get bits 11, 10 (A6,A5 in the tech bit field of 7.19) */
     if (host_or_line == MXD_LINE_SIDE)
     {
         ATTEMPT(mxdHwGetPhyRegField(pDev,mdioPort, MXD_AUTONEG, (MXD_AUTONEG_LP_ABILITY_LINE+(laneOffset*0x200)), \
                        10, 2, &val));
     }
     else if (host_or_line == MXD_HOST_SIDE)
     {
         ATTEMPT(mxdHwGetPhyRegField(pDev,mdioPort, MXD_AUTONEG, (MXD_AUTONEG_LP_ABILITY_HOST+(laneOffset*0x200)), \
                        10, 2, &val));
     }
     else
     {
         MXD_DBG_ERROR("mxdGetLPAdvertisedPause: Incorrect line_or_host selection: \n");
         return MXD_FAIL;
     }

     *pauseType = (MXD_U8) val;

     return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetTxRxPauseResolution
    Get Auto-neg Pause resolution
*******************************************************************************/
MXD_STATUS mxdGetTxRxPauseResolution
(
     IN MXD_DEV_PTR pDev,
     IN MXD_U16 mdioPort,
     IN MXD_U16 host_or_line,
     IN MXD_U16 laneOffset,
     OUT MXD_BOOL *pauseResolved,
     OUT MXD_BOOL *tx_pause_enabled,
     OUT MXD_BOOL *rx_pause_enabled
)
{
    MXD_U16 val,val1, autoNegAdvAddr, autoNegAbilityAddr;

    *pauseResolved = MXD_FALSE;

    if (host_or_line == MXD_LINE_SIDE)
    {
        autoNegAdvAddr = (MXD_AUTONEG_ADV1_LINE+(laneOffset*0x200));
        autoNegAbilityAddr = (MXD_AUTONEG_LP_ABILITY_LINE+(laneOffset*0x200));
    }
    else if (host_or_line == MXD_HOST_SIDE)
    {
        autoNegAdvAddr = (MXD_AUTONEG_ADV1_HOST+(laneOffset*0x200));
        autoNegAbilityAddr = (MXD_AUTONEG_LP_ABILITY_HOST+(laneOffset*0x200));
    }
    else
    {
        MXD_DBG_ERROR("mxdGetTxRxPauseResolution: Incorrect line_or_host selection: \n");
        return MXD_FAIL;
    }

    /* get Local bits 7.0010.11:10 */
    if (mxdHwGetPhyRegField(pDev,mdioPort, MXD_AUTONEG, autoNegAdvAddr, 10, 2, &val) == MXD_FAIL)
    {
        *tx_pause_enabled = *rx_pause_enabled = MXD_FALSE;
        MXD_DBG_ERROR("mxdGetTxRxPauseResolution: get local pause type failed: \n");
        return MXD_FAIL;
    }

    /* get Link Partner bits 7.0013.11:10 */
    if (mxdHwGetPhyRegField(pDev,mdioPort, MXD_AUTONEG, autoNegAbilityAddr, 10, 2, &val1) == MXD_FAIL)
    {
        *tx_pause_enabled = *rx_pause_enabled = MXD_FALSE;
        MXD_DBG_ERROR("mxdGetTxRxPauseResolution: get link partner pause type failed: \n");
        return MXD_FAIL;
    }

    *pauseResolved = MXD_TRUE;

    val |= (val1<<2);

    if ((val & 0x5) == 0x5)
    {
        *tx_pause_enabled = MXD_TRUE;
        *rx_pause_enabled = MXD_TRUE;

    }
    else if ((val & 0xE) == 0xE)
    {
        *tx_pause_enabled = MXD_TRUE;
        *rx_pause_enabled = MXD_FALSE;       
    }
    else if (val == 0xB)
    {
        *tx_pause_enabled = MXD_FALSE;
        *rx_pause_enabled = MXD_TRUE;  
    }
    else
    {
        *tx_pause_enabled = MXD_FALSE;  
        *rx_pause_enabled = MXD_FALSE;  
    }

    return MXD_OK;    
}

/*******************************************************************************
 MXD_STATUS mxdGetAutoNegResolution
    Get Auto-neg acquired speed after auto-neg is completed
*******************************************************************************/
MXD_STATUS mxdGetAutoNegResolution
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U16 *speed_bits
)
{
    *speed_bits = 0;

    if (host_or_line == MXD_LINE_SIDE)
    {
        ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_ETH_STATUS_LINE+(laneOffset*0x200)), speed_bits));
    }
    else if (host_or_line == MXD_HOST_SIDE)
    {
        ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_ETH_STATUS_HOST+(laneOffset*0x200)), speed_bits));
    }
    else
    {
        MXD_DBG_ERROR("mxdGetAutoNegResolution: Invalid Host or Line:%u.\n", host_or_line);
        return MXD_FAIL;
    }

    /* clear off ability bit which is always true, so result coming back is only speed and FEC */
    *speed_bits &= 0xFFFE;

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdCL37AutoNeg
    Enabled or Disabled CL-37 Auto-Neg for 1000BASE-X
*******************************************************************************/
MXD_STATUS mxdCL37AutoNeg
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig,
    IN MXD_U16 enabledAutoNeg
)
{
    if (opConfig != MXD_P1X)
    {
        MXD_DBG_ERROR("mxdCL37AutoNeg: Incorrect mode. CL-37 AutoNeg applies to MXD_P1X\n");
        return MXD_FAIL;
    }

    if (!((host_or_line == MXD_LINE_SIDE) || (host_or_line == MXD_HOST_SIDE) ||
        (host_or_line == MXD_BOTH_SIDE)))
    {
        MXD_DBG_ERROR("mxdCL37AutoNeg: Incorrect host or line interface\n");
        return MXD_FAIL;
    }

    if (enabledAutoNeg == MXD_ENABLE)
    {
        if ((host_or_line == MXD_LINE_SIDE) || (host_or_line == MXD_BOTH_SIDE))
        {
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, MXD_PCS_1G_CNTL_LANE(laneOffset), 0x1140));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, MXD_PCS_1G_AN_ADV_LANE(laneOffset), 0x0020));
        }

        if ((host_or_line == MXD_HOST_SIDE) || (host_or_line == MXD_BOTH_SIDE))
        {
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, MXD_PCS_1G_CNTL_LANE(laneOffset), 0x1140));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, MXD_PCS_1G_AN_ADV_LANE(laneOffset), 0x0020));
        }
    }
    else if (enabledAutoNeg == MXD_DISABLE)
    {
        if ((host_or_line == MXD_LINE_SIDE) || (host_or_line == MXD_BOTH_SIDE))
        {
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, MXD_PCS_1G_CNTL_LANE(laneOffset), 0x0140));
        }

        if ((host_or_line == MXD_HOST_SIDE) || (host_or_line == MXD_BOTH_SIDE))
        {
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, MXD_PCS_1G_CNTL_LANE(laneOffset), 0x0140));
        }
    }
    else
    {
        MXD_DBG_ERROR("mxdCL37AutoNeg: Error - invalid enabledAutoNeg input:0x%x\n", enabledAutoNeg);
        return MXD_FAIL;
    }

    return MXD_OK;
}

#define MAX_WAIT  1000
/*******************************************************************************
 MXD_STATUS mxdAutoNegStart
    Starts Auto-neg with set speeds and advertised Pause type
*******************************************************************************/
MXD_STATUS mxdAutoNegStart
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig,
    IN MXD_BOOL swReset
)
{
    MXD_U16 autoNegPause;

    switch(opConfig)
    {
        case MXD_P5K:
        case MXD_P50CN:
        case MXD_P50CF:
        case MXD_P50KN:
        case MXD_P50KF:
        case MXD_P100KN:
        {
            MXD_U16 autoNegAdvReg;

            if (host_or_line == MXD_LINE_SIDE)
            {
                /* Write the Pause type which is set in mxdSetPauseAdvertisement() to the AN advertisement register */
                autoNegPause = pDev->lineConfig[laneOffset].autoNegAdvPause;
                autoNegAdvReg = MXD_AUTONEG_ADV1_LINE;
            }
            else if (host_or_line == MXD_HOST_SIDE)
            {
                autoNegPause = pDev->hostConfig[laneOffset].autoNegAdvPause;
                autoNegAdvReg = MXD_AUTONEG_ADV1_HOST;
            }
            else
            {
                MXD_DBG_ERROR("mxdAutoNegStart: Invalid Host or Line:%u.\n", host_or_line);
                return MXD_FAIL;
            }

            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (autoNegAdvReg+(laneOffset*0x200)), 10, 2, autoNegPause));

            /* Do nothing for auto neg */
            if (swReset)
            {
                ATTEMPT(mxdLaneSoftReset(pDev, mdioPort, host_or_line, laneOffset, MAX_WAIT));
            }

            return MXD_OK;
            break;

        default:
            /* Allows fall through for below operations */
            break;
        }
    }

    if (host_or_line == MXD_LINE_SIDE)
    {
        /* Write the Pause type which is set in mxdSetPauseAdvertisement() to the AN advertisement register */
        autoNegPause = pDev->lineConfig[laneOffset].autoNegAdvPause;
        ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_ADV1_LINE+(laneOffset*0x200)), 10, 2, autoNegPause));
        ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_CNTL_LINE+(laneOffset*0x200)), 12, 1, 1));

        switch(opConfig)
        {
            case MXD_P10KN:
            case MXD_P10KF:
            case MXD_R10K:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_ADV2_LINE+(laneOffset*0x200)),  7, 1, 1));
                break;

            case MXD_P25BN:
            case MXD_P25BF:
            case MXD_P25BR:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_LANE_CTRL1_LINE+(laneOffset*0x200)), 5, 1, 1));
                break;

            case MXD_P25JN:
            case MXD_P25JF:
            case MXD_P25JR:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_LANE_CTRL1_LINE+(laneOffset*0x200)), 4, 1, 1));
                break;

            case MXD_P25CN:
            case MXD_P25CF:
            case MXD_P25CR:
            case MXD_P25KN:
            case MXD_P25KF:
            case MXD_P25KR:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_ADV2_LINE+(laneOffset*0x200)), 14, 2, 3));
                break;

            case MXD_P25BCN:
            case MXD_P25BCF:
            case MXD_P25BCR:
            case MXD_R25C:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_ADV2_LINE+(laneOffset*0x200)), 14, 2, 3));
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_LANE_CTRL1_LINE+(laneOffset*0x200)), 5, 1, 1));
                break;

            case MXD_P25JKN:
            case MXD_P25JKF:
            case MXD_P25JKR:
            case MXD_R25K:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_ADV2_LINE+(laneOffset*0x200)), 14, 2, 3));
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_LANE_CTRL1_LINE+(laneOffset*0x200)), 4, 1, 1));
                break;

            case MXD_P40CN:
            case MXD_P40CF:
            case MXD_R40C:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_ADV2_LINE+(laneOffset*0x200)),  9, 1, 1));
                break;

            case MXD_P40KN:
            case MXD_P40KF:
            case MXD_R40K:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_ADV2_LINE+(laneOffset*0x200)),  8, 1, 1));
                break;

            case MXD_P50BN:
            case MXD_P50BF:
            case MXD_P50BR:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, MXD_AUTONEG_LANE_CTRL1_LINE, 9, 1, 1));
                break;

            case MXD_P50JN:
            case MXD_P50JF:
            case MXD_P50JR:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, MXD_AUTONEG_LANE_CTRL1_LINE, 8, 1, 1));
                break;

            case MXD_P100CR:
            case MXD_R100C:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, MXD_AUTONEG_ADV2_LINE, 13, 1, 1));
                break;

            case MXD_P100KR:
            case MXD_R100K:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, MXD_AUTONEG_ADV2_LINE, 12, 1, 1));
                break;

            default:
                MXD_DBG_ERROR("mxdAutoNegStart: OP Config mode:%u line side not supported or implemented yet.\n", opConfig);
                return MXD_FAIL;
                break;
        }
    }
    else if (host_or_line == MXD_HOST_SIDE)
    {
        /* Write the Pause type which is set in mxdSetPauseAdvertisement() to the AN advertisement register */
        autoNegPause = pDev->hostConfig[laneOffset].autoNegAdvPause;
        ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_ADV1_HOST+(laneOffset*0x200)), 10, 2, autoNegPause));
        ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_CNTL_HOST+(laneOffset*0x200)), 12, 1, 1));

        switch(opConfig)
        {
            case MXD_P10KN:
            case MXD_P10KF:
            case MXD_R10K:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_ADV2_HOST+(laneOffset*0x200)), 7, 1, 1));
                break;

            case MXD_P25BN:
            case MXD_P25BF:
            case MXD_P25BR:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_LANE_CTRL1_HOST+(laneOffset*0x200)), 5, 1, 1));
                break;

            case MXD_P25JN:
            case MXD_P25JF:
            case MXD_P25JR:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_LANE_CTRL1_HOST+(laneOffset*0x200)), 4, 1, 1));
                break;

            case MXD_P25CN:
            case MXD_P25CF:
            case MXD_P25CR:
            case MXD_P25KN:
            case MXD_P25KF:
            case MXD_P25KR:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_ADV2_HOST+(laneOffset*0x200)), 14, 2, 3));
                break;

            case MXD_R25C:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_ADV2_HOST+(laneOffset*0x200)), 14, 2, 3));
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_LANE_CTRL1_HOST+(laneOffset*0x200)), 5, 1, 1));
                break;

            case MXD_R25K:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_ADV2_HOST+(laneOffset*0x200)), 14, 2, 3));
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_LANE_CTRL1_HOST+(laneOffset*0x200)), 4, 1, 1));
                break;

            case MXD_P40CN:
            case MXD_P40CF:
            case MXD_R40C:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_ADV2_HOST+(laneOffset*0x200)),  9, 1, 1));
                break;

            case MXD_P40KN:
            case MXD_P40KF:
            case MXD_R40K:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_ADV2_HOST+(laneOffset*0x200)),  8, 1, 1));
                break;

            case MXD_P50BN:
            case MXD_P50BF:
            case MXD_P50BR:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, MXD_AUTONEG_LANE_CTRL1_HOST, 9, 1, 1));
                break;

            case MXD_P50JN:
            case MXD_P50JF:
            case MXD_P50JR:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, MXD_AUTONEG_LANE_CTRL1_HOST, 8, 1, 1));
                break;

            case MXD_P100CR:
            case MXD_R100C:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, MXD_AUTONEG_ADV2_HOST, 13, 1, 1));
                break;

            case MXD_P100KR:
            case MXD_R100K:
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, MXD_AUTONEG_ADV2_HOST, 12, 1, 1));
                break;

            default:
                 MXD_DBG_ERROR("mxdAutoNegStart: OP Config mode:%u host side not supported or implemented yet.\n", opConfig);
                 return MXD_FAIL;
                 break;
        }
    }
    else
    {
        MXD_DBG_ERROR("mxdAutoNegStart: host_or_line is invalid.\n");
        return MXD_FAIL;
    }

    if (swReset)
    {
        ATTEMPT(mxdLaneSoftReset(pDev, mdioPort, host_or_line, laneOffset, MAX_WAIT));
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdAutoNegCheckComplete
    Check if Auto-neg is completed.
    Successful when *autoNegComplete = MXD_TRUE and return MXD_OK
*******************************************************************************/
MXD_STATUS mxdAutoNegCheckComplete
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U8 *autoNegComplete
)
{
    MXD_U16 temp = 0;

    *autoNegComplete = 0;

    if (pDev->devInfo & MXD_LANES_GROUPED)
    {
        laneOffset = 0;
    }

    if (host_or_line == MXD_LINE_SIDE)
    {
        ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_STATUS_LINE+(laneOffset*0x200)), 5, 1, &temp));
    }
    else if (host_or_line == MXD_HOST_SIDE)
    {
        ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_STATUS_HOST+(laneOffset*0x200)), 5, 1, &temp));
    }
    else
    {
        MXD_DBG_ERROR("mxdAutoNegCheckComplete: Invalid Host or Line:%u.\n", host_or_line);
        return MXD_FAIL;
    }

    if (temp)
    {
        *autoNegComplete = 1;
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdCheckLinkStatus
    Check link status
*******************************************************************************/
MXD_STATUS mxdCheckLinkStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  laneOffset,
    IN MXD_BOOL perLaneStatus,
    OUT MXD_U16 *currentStatus,
    OUT MXD_U16 *latchedStatus,
    OUT MXD_DETAILED_STATUS_TYPE *statusDetail
)
{
    MXD_U16 hostPcsType;
    MXD_OP_CONFIG portConfig;


    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdCheckLinkStatus: device not initialized\n");
        return MXD_FAIL;
    }

     ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    /* check lane offset is valid and lane is configured */
    if (mxdIsLaneOffsetValid(pDev, mdioPort, laneOffset) != MXD_OK)
    {
        MXD_DBG_ERROR("mxdCheckLinkStatus: incorrect lane Offset: %u\n", laneOffset);
        return MXD_FAIL;
    }

    portConfig = pDev->hostConfig[laneOffset].opConfig;
    hostPcsType = portConfigTbl[portConfig][PCS_TYPE_IDX];

    if (hostPcsType == MXD_PCS)
    {
        ATTEMPT(mxdReadPCSLinkStatus(pDev, mdioPort, laneOffset, perLaneStatus, currentStatus, latchedStatus, statusDetail));
    }
    else
    {
        ATTEMPT(mxdReadRepeaterLinkStatus(pDev, mdioPort, laneOffset, perLaneStatus, currentStatus, statusDetail));
        *latchedStatus = 0; /* not applicable in repeater mode */
    }

    return MXD_OK;
}


/*******************************************************************************
 MXD_STATUS mxdSetRmFifoCntl

*******************************************************************************/
MXD_STATUS mxdSetRmFifoCntl
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 txThresholdHigh,
    IN MXD_U16 txThresholdLow,
    IN MXD_U16 rxThreshold,
    IN MXD_U16 txSatThreshold
)
{
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdSetRmFifoCntl: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    if ((txThresholdHigh > 0x7FF) || (txThresholdLow > 0x7FF) ||
        (rxThreshold > 0x7FF) || (txSatThreshold > 0x7FF))
    {
        MXD_DBG_ERROR("mxdSetRmFifoCntl: Out of range; values must be < 0x7FF.\n");
        return MXD_FAIL;
    }

    if (txThresholdLow > txThresholdHigh)
    {
        MXD_DBG_ERROR("mxdSetRmFifoCntl: txThresholdLow cannot be more than txThresholdHigh.\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_CHIP_REG, MXD_RM_FIFO_TX_THR_H, 0, 11, txThresholdHigh));
    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_CHIP_REG, MXD_RM_FIFO_TX_THR_L, 0, 11, txThresholdLow));
    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_CHIP_REG, MXD_RM_FIFO_RX_THR, 0, 11, rxThreshold));
    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_CHIP_REG, MXD_RM_FIFO_TX_SAT_THR, 0, 11, txSatThreshold));

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetRmFifoCntl

*******************************************************************************/
MXD_STATUS mxdGetRmFifoCntl
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    OUT MXD_U16 *txThresholdHigh,
    OUT MXD_U16 *txThresholdLow,
    OUT MXD_U16 *rxThreshold,
    OUT MXD_U16 *txSatThreshold
)
{
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdGetRmFifoCntl: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_CHIP_REG, MXD_RM_FIFO_TX_THR_H, 0, 11, txThresholdHigh));
    ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_CHIP_REG, MXD_RM_FIFO_TX_THR_L, 0, 11, txThresholdLow));
    ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_CHIP_REG, MXD_RM_FIFO_RX_THR, 0, 11, rxThreshold));
    ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_CHIP_REG, MXD_RM_FIFO_TX_SAT_THR, 0, 11, txSatThreshold));

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetRmFifoPktDropCntr

*******************************************************************************/
MXD_STATUS mxdGetRmFifoPktDropCntr
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 readClear,
    OUT MXD_U16 *txPktDropCntr
)
{
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdGetRmFifoPktDropCntr: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_CHIP_REG, MXD_RM_FIFO_TX_DROP_CNTR, txPktDropCntr));

    if (readClear)
    {
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_RM_FIFO_TX_DROP_CNTR, 0));
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdSetRmFifoInterruptEnable

*******************************************************************************/
MXD_STATUS mxdSetRmFifoInterruptEnable
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 intrEnableFlags
)
{
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdSetRmFifoInterruptEnable: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_CHIP_REG, MXD_RM_FIFO_INTR_MASK, 0, 13, intrEnableFlags));

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetRmFifoInterruptStatus
    Get rate matching FIFO interrupt status
*******************************************************************************/
MXD_STATUS mxdGetRmFifoInterruptStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    OUT MXD_U16 *rmFifoIntrStatus
)
{
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdGetRmFifoInterruptStatus: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_CHIP_REG, MXD_RM_FIFO_INTR_STAT, 0, 13, rmFifoIntrStatus));

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdSetIPGMode
*******************************************************************************/
MXD_STATUS mxdSetIPGMode
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 rxIPGMode,
    IN MXD_U16 txIPGMode,
    IN MXD_U16 avgDIC
)
{
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdSetIPGMode: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));
    /*
        rxIPGMode - Rx direction (25Gb/s to 40Gb/s) IPG control between packets
                    00/01: minimum 8 bytes IPG
                    10: minimum 16 bytes IPG
    */
    if (rxIPGMode <= 2)
    {
        ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_CHIP_REG, MXD_IPG_CFG_CNTL, 6, 2, rxIPGMode));
    }
    else
    {
        MXD_DBG_ERROR("mxdSetIPGMode: incorrect rxIPGMode value:%u\n", rxIPGMode);
        return MXD_FAIL;
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
        ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_CHIP_REG, MXD_IPG_CFG_CNTL, 4, 2, txIPGMode));
    }
    else
    {
        MXD_DBG_ERROR("mxdSetIPGMode: incorrect txIPGMode value:%u\n", rxIPGMode);
        return MXD_FAIL;
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
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_CHIP_REG, MXD_IPG_CFG_CNTL, 0, 4, avgDIC));
        }
        else
        {
            MXD_DBG_ERROR("mxdSetIPGMode: incorrect avgDIC value:%u\n", avgDIC);
            return MXD_FAIL;
        }
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetIPGMode
*******************************************************************************/
MXD_STATUS mxdGetIPGMode
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    OUT MXD_U16 *rxIPGMode,
    OUT MXD_U16 *txIPGMode,
    OUT MXD_U16 *avgDIC
)
{
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdGetIPGMode: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_CHIP_REG, MXD_IPG_CFG_CNTL, 6, 2, rxIPGMode));
    ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_CHIP_REG, MXD_IPG_CFG_CNTL, 4, 2, txIPGMode));
    ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_CHIP_REG, MXD_IPG_CFG_CNTL, 0, 4, avgDIC));

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetPcsFaultStatus
    Check tx/rx fault status
*******************************************************************************/
MXD_STATUS mxdGetPcsFaultStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U16 *currentTxFaultStatus,
    OUT MXD_U16 *currentRxFaultStatus,
    OUT MXD_U16 *latchedTxFaultStatus,
    OUT MXD_U16 *latchedRxFaultStatus
)
{
    MXD_U16 regAddr;
    MXD_SPEED speed;
    MXD_PCS_TYPE mode;

    *currentTxFaultStatus = *currentRxFaultStatus = *latchedTxFaultStatus =
    *latchedRxFaultStatus = 1; /* in case fails, init to fault */

    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdGetPcsFaultStatus: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    /* check lane offset is valid */
    if (mxdIsLaneOffsetValid(pDev, mdioPort, laneOffset) != MXD_OK)
    {
        MXD_DBG_ERROR("mxdGetPcsFaultStatus: incorrect lane Offset: %u\n", laneOffset);
        return MXD_FAIL;
    }

    ATTEMPT(mxdGetModeSpeed(pDev, mdioPort, host_or_line, laneOffset, &speed, &mode));

    if (mode != MXD_PCS)
    {
        MXD_DBG_ERROR("mxdGetPcsFaultStatus: not in PCS mode\n");
        return MXD_FAIL;
    }

    switch (speed)
    {
        case MXD_10GB:
        case MXD_25GB:
            regAddr = MXD_PCS_25G_PCS_STATUS2+laneOffset*0x200;
            break;

        case MXD_40GB:
        case MXD_50GB:
            regAddr = MXD_PCS_40G_PCS_STATUS2;
            break;

        case MXD_100GB:
            regAddr = MXD_PCS_100G_PCS_STATUS2;
            break;

        default:
            MXD_DBG_ERROR("mxdGetPcsFaultStatus: unsupported speed or speed unknown\n");
            return MXD_FAIL;
            break;
    }

    ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, host_or_line, regAddr, 11, 1, latchedTxFaultStatus));
    ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, host_or_line, regAddr, 11, 1, currentTxFaultStatus));
    ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, host_or_line, regAddr, 10, 1, latchedRxFaultStatus));
    ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, host_or_line, regAddr, 10, 1, currentRxFaultStatus));

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdSetGlobalInterruptCntl

*******************************************************************************/
MXD_STATUS mxdSetGlobalInterruptCntl
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 globalIntrCntl
)
{
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdSetGlobalInterruptCntl: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_GLOBAL_INTR_CNTL, globalIntrCntl));

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetGlobalInterruptStatus

*******************************************************************************/
MXD_STATUS mxdGetGlobalInterruptStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    OUT MXD_U16 *globalIntrStatus
)
{
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdGetGlobalInterruptStatus: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_CHIP_REG, MXD_GLOBAL_INTR_STAT, globalIntrStatus));

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdSetInterruptEnable
    Set interrupt enable for various modes
*******************************************************************************/
MXD_STATUS mxdSetInterruptEnable
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_U16 intrEnableFlags1,
    IN MXD_U16 intrEnableFlags2 /* only valid for 100GBR */
)
{
    MXD_SPEED speed;
    MXD_PCS_TYPE mode;

    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdSetInterruptEnable: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    /* check lane offset is valid */
    if (mxdIsLaneOffsetValid(pDev, mdioPort, laneOffset) != MXD_OK)
    {
        MXD_DBG_ERROR("mxdSetInterruptEnable: incorrect lane Offset: %u\n", laneOffset);
        return MXD_FAIL;
    }

    ATTEMPT(mxdGetModeSpeed(pDev, mdioPort, host_or_line, laneOffset, &speed, &mode));

    if (mode != MXD_PCS)
    {
        MXD_DBG_ERROR("mxdSetInterruptEnable: not in PCS mode\n");
        return MXD_FAIL;
    }

    switch (speed)
    {
        case MXD_1GB:
        case MXD_2_5GB:
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, MXD_PCS_1G_INTR_EN+laneOffset*0x200, intrEnableFlags1));
            break;

        case MXD_5GB:
        case MXD_10GB:
        case MXD_25GB:
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, MXD_PCS_25G_INTR_EN+laneOffset*0x200, intrEnableFlags1));
            break;

        case MXD_40GB:
        case MXD_50GB:
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, MXD_PCS_40G_INTR_EN, intrEnableFlags1));
            break;

        case MXD_100GB:
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, MXD_PCS_100G_INTR_EN1, intrEnableFlags1));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, MXD_PCS_100G_INTR_EN2, intrEnableFlags2));
            break;

        default:
            MXD_DBG_ERROR("mxdSetInterruptEnable: unsupported speed or speed unknown\n");
            return MXD_FAIL;
            break;
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetInterruptEnable
    Get interrupt enable for various modes
*******************************************************************************/
MXD_STATUS mxdGetInterruptEnable
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U16 *intrEnableFlags1,
    OUT MXD_U16 *intrEnableFlags2 /* only valid for 100GBR */
)
{
    MXD_SPEED speed;
    MXD_PCS_TYPE mode;

    /* in case it fails, init return value */
    *intrEnableFlags1 = *intrEnableFlags2 = 0;

    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdGetInterruptEnable: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    /* check lane offset is valid */
    if (mxdIsLaneOffsetValid(pDev, mdioPort, laneOffset) != MXD_OK)
    {
        MXD_DBG_ERROR("mxdGetInterruptEnable: incorrect lane Offset: %u\n", laneOffset);
        return MXD_FAIL;
    }

    ATTEMPT(mxdGetModeSpeed(pDev, mdioPort, host_or_line, laneOffset, &speed, &mode));

    if (mode != MXD_PCS)
    {
        MXD_DBG_ERROR("mxdGetInterruptEnable: not in PCS mode\n");
        return MXD_FAIL;
    }

    switch (speed)
    {
        case MXD_1GB:
        case MXD_2_5GB:
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PCS_1G_INTR_EN+laneOffset*0x200, intrEnableFlags1));
            break;

        case MXD_5GB:
        case MXD_10GB:
        case MXD_25GB:
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PCS_25G_INTR_EN+laneOffset*0x200, intrEnableFlags1));
            break;

        case MXD_40GB:
        case MXD_50GB:
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PCS_40G_INTR_EN, intrEnableFlags1));
            break;

        case MXD_100GB:
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PCS_100G_INTR_EN1, intrEnableFlags1));
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PCS_100G_INTR_EN2, intrEnableFlags2));
            break;

        default:
            MXD_DBG_ERROR("mxdGetInterruptEnable: unsupported speed or speed unknown\n");
            return MXD_FAIL;
            break;
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetInterruptStatus
    Get interrupt status for various modes
*******************************************************************************/
MXD_STATUS mxdGetInterruptStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U16 *latchedStatusFlags1,
    OUT MXD_U16 *currentStatusFlags1,
    OUT MXD_U16 *latchedStatusFlags2, /* only valid for 100GBR */
    OUT MXD_U16 *currentStatusFlags2  /* only valid for 100GBR */
)
{
    MXD_SPEED speed;
    MXD_PCS_TYPE mode;

    /* in case it fails, init return value */
    *latchedStatusFlags1 = *currentStatusFlags1 = 0;
    *latchedStatusFlags2 = *currentStatusFlags2 = 0;

    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdGetInterruptStatus: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    /* check lane offset is valid */
    if (mxdIsLaneOffsetValid(pDev, mdioPort, laneOffset) != MXD_OK)
    {
        MXD_DBG_ERROR("mxdGetInterruptStatus: incorrect lane Offset: %u\n", laneOffset);
        return MXD_FAIL;
    }

    ATTEMPT(mxdGetModeSpeed(pDev, mdioPort, host_or_line, laneOffset, &speed, &mode));

    if (mode != MXD_PCS)
    {
        MXD_DBG_ERROR("mxdGetInterruptStatus: not in PCS mode\n");
        return MXD_FAIL;
    }

    switch (speed)
    {
        case MXD_1GB:
        case MXD_2_5GB:
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PCS_1G_INTR_STAT+laneOffset*0x200, latchedStatusFlags1));
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PCS_1G_INTR_STAT+laneOffset*0x200, currentStatusFlags1));
            break;

        case MXD_5GB:
        case MXD_10GB:
        case MXD_25GB:
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PCS_25G_INTR_STAT+laneOffset*0x200, latchedStatusFlags1));
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PCS_25G_INTR_STAT+laneOffset*0x200, currentStatusFlags1));
            break;

        case MXD_40GB:
        case MXD_50GB:
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PCS_40G_INTR_STAT, latchedStatusFlags1));
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PCS_40G_INTR_STAT, currentStatusFlags1));
            break;

        case MXD_100GB:
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PCS_100G_INTR_STAT1, latchedStatusFlags1));
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PCS_100G_INTR_STAT1, currentStatusFlags1));
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PCS_100G_INTR_STAT2, latchedStatusFlags2));
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PCS_100G_INTR_STAT2, currentStatusFlags2));
            break;

        default:
            MXD_DBG_ERROR("mxdGetInterruptStatus: unsupported speed or speed unknown\n");
            return MXD_FAIL;
            break;
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetRealtimeStatus
    Get real-time status for various modes
*******************************************************************************/
MXD_STATUS mxdGetRealtimeStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U16 *rtStatusFlags1,
    OUT MXD_U16 *rtStatusFlags2 /* only valid for 100GBR */
)
{
    MXD_SPEED speed;
    MXD_PCS_TYPE mode;

    /* in case it fails, init return value */
    *rtStatusFlags1 = *rtStatusFlags2 = 0;

    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdGetRealtimeStatus: device not initialized\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdIsPortValid(pDev, mdioPort));

    /* check lane offset is valid */
    if (mxdIsLaneOffsetValid(pDev, mdioPort, laneOffset) != MXD_OK)
    {
        MXD_DBG_ERROR("mxdGetRealtimeStatus: incorrect lane Offset: %u\n", laneOffset);
        return MXD_FAIL;
    }

    ATTEMPT(mxdGetModeSpeed(pDev, mdioPort, host_or_line, laneOffset, &speed, &mode));

    if (mode != MXD_PCS)
    {
        MXD_DBG_ERROR("mxdGetRealtimeStatus: not in PCS mode\n");
        return MXD_FAIL;
    }

    switch (speed)
    {
        case MXD_1GB:
        case MXD_2_5GB:
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PCS_1G_RT_STAT+laneOffset*0x200, rtStatusFlags1));
            break;

        case MXD_5GB:
        case MXD_10GB:
        case MXD_25GB:
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PCS_25G_RT_STAT+laneOffset*0x200, rtStatusFlags1));
            break;

        case MXD_40GB:
        case MXD_50GB:
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PCS_40G_RT_STAT, rtStatusFlags1));
            break;

        case MXD_100GB:
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PCS_100G_RT_STAT1, rtStatusFlags1));
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, MXD_PCS_100G_RT_STAT2, rtStatusFlags2));
            break;

        default:
            MXD_DBG_ERROR("mxdGetRealtimeStatus: unsupported speed or speed unknown\n");
            return MXD_FAIL;
            break;
    }

    return MXD_OK;
}

