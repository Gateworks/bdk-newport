/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions and data that are strictly internal
for the proper functioning of the API on the Marvell X5113 PHY.
********************************************************************/
#include "mxdApiTypes.h"
#include "mxdApiRegs.h"
#include "mxdUtils.h"
#include "mxdHwCntl.h"
#include "mxdAPI.h"
#include "mxdDiagnostics.h"
#include "mxdAPIInternal.h"
#include "mxdFwDownload.h"
#include "mxdInitialization.h"
#include "mxdHwSerdesCntl.h"

#if DB_TEST_ENVIRONMENT
#include "windows.h"
#include "time.h"
#include "stdio.h"
#endif

#define MXD_RESET_TIMEOUT  10000 /* 10 sec max wait for power down HW reset */

#define MXD_AUTONEG_OFF     0
#define MXD_AUTONEG_ON      1

#define MXD_IEEE_FEC_BASE   0x10

#define MXD_DONT_CARE       0x0
#define MXD_1000B_X         0x0
#define MXD_SGMII_PHY       0x2
#define MXD_SGMII_SYS       0x3

#define MXD_25GB_CR_IEEE    0x0
#define MXD_25GB_KR_IEEE    0x1
#define MXD_25GB_CR_CONS    0x2
#define MXD_25GB_KR_CONS    0x3

#define MXD_25GB_CR_TRANS   0x0
#define MXD_25GB_KR_TRANS   0x1

#define MXD_40GB_CR4        0x0
#define MXD_40GB_KR4        0x1

#define MXD_40GB_CR_TRANS   0x0
#define MXD_40GB_KR_TRANS   0x1

#define MXD_100GB_CR4       0x0
#define MXD_100GB_KR4       0x1

#define MXD_100GB_CR_TRANS  0x0
#define MXD_100GB_KR_TRANS  0x1

/* Table format: portConfigTbl needs to match up with MXD_OP_CONFIG */
/*   PCS TYPE  FEC TYPE         AUTONEG          MXD_SPEED  MODE MODIFIER    */
/*---------------------------------------------------------------------------*/
const MXD_U16 portConfigTbl[MXD_OP_CONFIG_NUM][5] =
   {{0,0,0,0,0},
    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_OFF, MXD_1GB,   MXD_1000B_X      }, /* P1X   0x8020 */
    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_OFF, MXD_1GB,   MXD_SGMII_SYS    }, /* P1S   0x8320 */
    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_OFF, MXD_1GB,   MXD_SGMII_PHY    }, /* P1P   0x8220 */
    {MXD_TRANSPARENT, MXD_FEC_NONE, MXD_AUTONEG_OFF, MXD_1GB,   MXD_DONT_CARE}, /* R1           */

    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_OFF, MXD_2_5GB, MXD_DONT_CARE    }, /* P2.5X        */
    {MXD_TRANSPARENT, MXD_FEC_NONE, MXD_AUTONEG_OFF, MXD_2_5GB, MXD_DONT_CARE}, /* R2.5         */

    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_OFF, MXD_5GB,   MXD_DONT_CARE    }, /* P5L          */
    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_ON,  MXD_5GB,   MXD_DONT_CARE    }, /* P5K          */
    {MXD_TRANSPARENT, MXD_FEC_NONE, MXD_AUTONEG_OFF, MXD_5GB,   MXD_DONT_CARE}, /* R5           */

    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_OFF, MXD_10GB,  MXD_DONT_CARE    }, /* P10LN 0x8023 */
    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_ON,  MXD_10GB,  MXD_DONT_CARE    }, /* P10KN 0x8033 */
    {MXD_PCS,  MXD_KR_FEC,      MXD_AUTONEG_ON,  MXD_10GB,  MXD_DONT_CARE    }, /* P10KF        */
    {MXD_PCS,  MXD_KR_FEC,      MXD_AUTONEG_OFF, MXD_10GB,  MXD_DONT_CARE    }, /* P10LF        */
    {MXD_TRANSPARENT, MXD_FEC_NONE, MXD_AUTONEG_OFF, MXD_10GB,  MXD_DONT_CARE}, /* R10L         */
    {MXD_TRANSPARENT, MXD_FEC_NONE, MXD_AUTONEG_ON,  MXD_10GB,  MXD_DONT_CARE}, /* R10K         */

    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_OFF, MXD_25GB,  MXD_DONT_CARE    }, /* P25LN        */
    {MXD_PCS,  MXD_KR_FEC,      MXD_AUTONEG_OFF, MXD_25GB,  MXD_DONT_CARE    }, /* P25LF        */
    {MXD_PCS,  MXD_RS_FEC,      MXD_AUTONEG_OFF, MXD_25GB,  MXD_DONT_CARE    }, /* P25LR        */
    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_ON,  MXD_25GB,  MXD_25GB_CR_IEEE }, /* P25CN        */
    {MXD_PCS,  MXD_KR_FEC,      MXD_AUTONEG_ON,  MXD_25GB,  MXD_25GB_CR_IEEE }, /* P25CF        */
    {MXD_PCS,  MXD_FEC_BOTH,    MXD_AUTONEG_ON,  MXD_25GB,  MXD_25GB_CR_IEEE }, /* P25CR        */
    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_ON,  MXD_25GB,  MXD_25GB_KR_IEEE }, /* P25KN        */
    {MXD_PCS,  MXD_KR_FEC,      MXD_AUTONEG_ON,  MXD_25GB,  MXD_25GB_KR_IEEE }, /* P25KF        */
    {MXD_PCS,  MXD_RS_FEC,      MXD_AUTONEG_ON,  MXD_25GB,  MXD_25GB_KR_IEEE }, /* P25KR        */

    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_ON,  MXD_25GB,  MXD_25GB_CR_CONS }, /* P25BN        */
    {MXD_PCS,  MXD_KR_FEC_CON,  MXD_AUTONEG_ON,  MXD_25GB,  MXD_25GB_CR_CONS }, /* P25BF        */
    {MXD_PCS,  MXD_RS_FEC_CON,  MXD_AUTONEG_ON,  MXD_25GB,  MXD_25GB_CR_CONS }, /* P25BR        */

    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_ON,  MXD_25GB,  MXD_25GB_KR_CONS }, /* P25JN        */
    {MXD_PCS,  MXD_KR_FEC_CON,  MXD_AUTONEG_ON,  MXD_25GB,  MXD_25GB_KR_CONS }, /* P25JF        */
    {MXD_PCS,  MXD_RS_FEC_CON,  MXD_AUTONEG_ON,  MXD_25GB,  MXD_25GB_KR_CONS }, /* P25JR        */

    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_ON,  MXD_25GB,  MXD_IEEE_FEC_BASE}, /* P25BCN       */
    {MXD_PCS,  MXD_KR_FEC_IEEE, MXD_AUTONEG_ON,  MXD_25GB,  MXD_IEEE_FEC_BASE}, /* P25BCF       */
    {MXD_PCS,  MXD_RS_FEC_IEEE, MXD_AUTONEG_ON,  MXD_25GB,  MXD_IEEE_FEC_BASE}, /* P25BCR       */
    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_ON,  MXD_25GB,  MXD_IEEE_FEC_BASE}, /* P25JKN       */
    {MXD_PCS,  MXD_KR_FEC_IEEE, MXD_AUTONEG_ON,  MXD_25GB,  MXD_IEEE_FEC_BASE}, /* P25JKF       */
    {MXD_PCS,  MXD_RS_FEC_IEEE, MXD_AUTONEG_ON,  MXD_25GB,  MXD_IEEE_FEC_BASE}, /* P25JKR       */

    {MXD_TRANSPARENT, MXD_FEC_NONE, MXD_AUTONEG_OFF, MXD_25GB,  MXD_DONT_CARE}, /* R25L         */
    {MXD_TRANSPARENT, MXD_FEC_NONE, MXD_AUTONEG_ON,  MXD_25GB,  MXD_40GB_CR4 }, /* R25C         */
    {MXD_TRANSPARENT, MXD_FEC_NONE, MXD_AUTONEG_ON,  MXD_25GB,  MXD_40GB_KR4 }, /* R25K         */

    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_OFF, MXD_40GB,  MXD_DONT_CARE    }, /* P29P09LN with 29.09 clock modifier */

    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_OFF, MXD_40GB,  MXD_DONT_CARE    }, /* P40LN        */
    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_ON,  MXD_40GB,  MXD_40GB_CR4     }, /* P40CN        */
    {MXD_PCS,  MXD_KR_FEC,      MXD_AUTONEG_ON,  MXD_40GB,  MXD_40GB_CR4     }, /* P40CF        */
    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_ON,  MXD_40GB,  MXD_40GB_KR4     }, /* P40KN        */
    {MXD_PCS,  MXD_KR_FEC,      MXD_AUTONEG_ON,  MXD_40GB,  MXD_40GB_KR4     }, /* P40KF        */
    {MXD_PCS,  MXD_KR_FEC,      MXD_AUTONEG_OFF, MXD_40GB,  MXD_DONT_CARE    }, /* P40LF        */
    {MXD_TRANSPARENT, MXD_FEC_NONE, MXD_AUTONEG_OFF, MXD_40GB,  MXD_DONT_CARE}, /* R40L         */
    {MXD_TRANSPARENT, MXD_FEC_NONE, MXD_AUTONEG_ON,  MXD_40GB,  MXD_40GB_CR4 }, /* R40C         */
    {MXD_TRANSPARENT, MXD_FEC_NONE, MXD_AUTONEG_ON,  MXD_40GB,  MXD_40GB_KR4 }, /* R40K         */

    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_OFF, MXD_50GB,  MXD_DONT_CARE    }, /* P50LN        */
    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_ON,  MXD_50GB,  MXD_DONT_CARE    }, /* P50CN        */
    {MXD_PCS,  MXD_KR_FEC,      MXD_AUTONEG_ON,  MXD_50GB,  MXD_DONT_CARE    }, /* P50CF        */
    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_ON,  MXD_50GB,  MXD_40GB_KR4     }, /* P50KN        */
    {MXD_PCS,  MXD_KR_FEC,      MXD_AUTONEG_ON,  MXD_50GB,  MXD_40GB_KR4     }, /* P50KF        */
    {MXD_PCS,  MXD_KR_FEC,      MXD_AUTONEG_OFF, MXD_50GB,  MXD_DONT_CARE    }, /* P50LF        */
    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_OFF, MXD_50GB,  MXD_25GB_CR_CONS }, /* P50MN        */
    {MXD_PCS,  MXD_KR_FEC,      MXD_AUTONEG_OFF, MXD_50GB,  MXD_25GB_CR_CONS }, /* P50MF        */
    {MXD_PCS,  MXD_RS_FEC,      MXD_AUTONEG_OFF, MXD_50GB,  MXD_25GB_CR_CONS }, /* P50MR        */
    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_ON,  MXD_50GB,  MXD_25GB_CR_CONS }, /* P50BN        */
    {MXD_PCS,  MXD_KR_FEC_CON,  MXD_AUTONEG_ON,  MXD_50GB,  MXD_25GB_CR_CONS }, /* P50BF        */
    {MXD_PCS,  MXD_RS_FEC_CON,  MXD_AUTONEG_ON,  MXD_50GB,  MXD_25GB_CR_CONS }, /* P50BR        */
    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_ON,  MXD_50GB,  MXD_25GB_KR_CONS }, /* P50JN        */
    {MXD_PCS,  MXD_KR_FEC_CON,  MXD_AUTONEG_ON,  MXD_50GB,  MXD_25GB_KR_CONS }, /* P50JF        */
    {MXD_PCS,  MXD_RS_FEC_CON,  MXD_AUTONEG_ON,  MXD_50GB,  MXD_25GB_KR_CONS }, /* P50JR        */

    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_OFF, MXD_100GB, MXD_DONT_CARE    }, /* P100LN       */
    {MXD_PCS,  MXD_RS_FEC,      MXD_AUTONEG_OFF, MXD_100GB, MXD_DONT_CARE    }, /* P100LR       */
    {MXD_PCS,  MXD_FEC_BOTH,    MXD_AUTONEG_ON,  MXD_100GB, MXD_25GB_CR_IEEE }, /* P100CR       */
    {MXD_PCS,  MXD_RS_FEC,      MXD_AUTONEG_ON,  MXD_100GB, MXD_25GB_KR_IEEE }, /* P100KR       */
    {MXD_PCS,  MXD_FEC_NONE,    MXD_AUTONEG_ON,  MXD_100GB, MXD_DONT_CARE },    /* P100KN       */
    {MXD_TRANSPARENT, MXD_FEC_NONE, MXD_AUTONEG_OFF, MXD_100GB, MXD_DONT_CARE}, /* R100L        */
    {MXD_TRANSPARENT, MXD_FEC_NONE, MXD_AUTONEG_ON,  MXD_100GB, MXD_40GB_CR4 }, /* R100C        */
    {MXD_TRANSPARENT, MXD_FEC_NONE, MXD_AUTONEG_ON,  MXD_100GB, MXD_40GB_KR4 }  /* R100K        */

   };

/*******************************************************************************
 MXD_STATUS mxdIsLaneOffsetValid
    Checks the lane offset against the operation mode if it is valid
*******************************************************************************/
MXD_STATUS mxdIsLaneOffsetValid
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 laneOffset
)
{
    if (!pDev->devEnabled)
    {
        MXD_DBG_ERROR("mxdIsLaneOffsetValid: device not initialized\n");
        return MXD_FAIL;
    }

    if (laneOffset > 3)
    {
        MXD_DBG_ERROR("mxdIsLaneOffsetValid: incorrect lane selection: %u\n", laneOffset);
        return MXD_FAIL;
    }

    if (pDev->hostConfig[laneOffset].opConfig == MXD_CONFIG_UNKNOWN ||
        pDev->lineConfig[laneOffset].opConfig == MXD_CONFIG_UNKNOWN)
    {
        MXD_DBG_ERROR("mxdIsLaneOffsetValid: lane %u is not configured\n", laneOffset);
        return MXD_FAIL;
    }

    if ((pDev->hostConfig[laneOffset].pcsSpeed >= MXD_40GB) && (laneOffset != 0))
    {
        MXD_DBG_ERROR("mxdIsLaneOffsetValid: incorrect lane selection: %u\n", laneOffset);
        return MXD_FAIL;
    }

    if ((pDev->lineConfig[laneOffset].pcsSpeed >= MXD_40GB) && (laneOffset != 0))
    {
        MXD_DBG_ERROR("mxdIsLaneOffsetValid: portCount is some strange number.\n");
        return MXD_FAIL;
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdIsPortValid
    Check the MDIO port address if it is valid against the port address input
    during the mxdInitDriver initialization
*******************************************************************************/
MXD_STATUS mxdIsPortValid
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort
)
{
    if (pDev && (pDev->mdioPort != mdioPort))
    {
        MXD_DBG_ERROR("mxdIsPortValid: mdioPort mismatched with mdioPort in Device structure\n");
        return MXD_FAIL;
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdIsOpModeValid
    Check the host and line Op Mode if it is valid combination
*******************************************************************************/
MXD_STATUS mxdIsOpModeValid
(
    IN MXD_DEV_PTR pDev,
    IN MXD_OP_CONFIG hostMode,
    IN MXD_OP_CONFIG lineMode
)
{
    MXD_U16 lineSpeed, hostSpeed, linePcsType, hostPcsType;

    switch(hostMode)
    {
        case MXD_CONFIG_UNKNOWN:
        case MXD_P1S:
        case MXD_P25BCN:
        case MXD_P25BCF:
        case MXD_P25BCR:
        case MXD_P25JKN:
        case MXD_P25JKF:
        case MXD_P25JKR:
            MXD_DBG_ERROR("mxdIsOpModeValid: unsupported host mode selection!\n");
            return MXD_FAIL;
            break;

        default:
            break;
    }

    switch(lineMode)
    {
        case MXD_CONFIG_UNKNOWN:
        case MXD_P29P09LN:
            MXD_DBG_ERROR("mxdIsOpModeValid: unsupported line mode selection!\n");
            return MXD_FAIL;
            break;

        default:
            break;
    }

    hostPcsType = portConfigTbl[hostMode][PCS_TYPE_IDX];
    linePcsType = portConfigTbl[lineMode][PCS_TYPE_IDX];

    if (hostPcsType != linePcsType)
    {
        MXD_DBG_ERROR("mxdIsOpModeValid: incorrect host and line PCS Type combination!\n");
        return MXD_FAIL;
    }

    hostSpeed = portConfigTbl[hostMode][SPEED_IDX];
    lineSpeed = portConfigTbl[lineMode][SPEED_IDX];

    if (hostSpeed != lineSpeed)
    {
        if ((hostSpeed == MXD_40GB) && (lineSpeed == MXD_25GB) && (hostPcsType == MXD_PCS))
        {
            return MXD_OK;
        }
        else
        {
            MXD_DBG_ERROR("mxdIsOpModeValid: unsupported host and line mode combination!\n");
            return MXD_FAIL;
        }
    }

    return MXD_OK;
}


/*******************************************************************
 MXD_STATUS mxdSetConfigInfo
    Set the config info on the Line or Host config structure
*******************************************************************/
MXD_STATUS mxdSetConfigInfo
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig
)
{
    MXD_U16 fecType;
    MXD_PCS_TYPE pcsType;
    MXD_SPEED speed;
    MXD_U16 i;
    MXD_MODE_CONFIG *modeConfig;

    pcsType  = (MXD_PCS_TYPE)portConfigTbl[opConfig][PCS_TYPE_IDX];
    fecType  = portConfigTbl[opConfig][FEC_TYPE_IDX];
    speed    = (MXD_SPEED)portConfigTbl[opConfig][SPEED_IDX];

    if (host_or_line == MXD_HOST_SIDE)
    {
        modeConfig = &pDev->hostConfig[0];
    }
    else
    {
        modeConfig = &pDev->lineConfig[0];
    }

    if (pDev->devInfo & MXD_LANES_GROUPED)
    {
        switch(speed)
        {
            case MXD_25GB:
                modeConfig[laneOffset].laneSpeed = MXD_LANE_25GB;  /* Gearbox mode */
                modeConfig[laneOffset].opConfig = opConfig;
                modeConfig[laneOffset].fecType = fecType;
                modeConfig[laneOffset].pcsType = pcsType;
                modeConfig[laneOffset].pcsSpeed = speed;
                break;

            case MXD_40GB:
                for (i=0; i<MXD_NUM_LANES; i++)
                {
                    modeConfig[i].laneSpeed = MXD_LANE_10GB;
                    modeConfig[i].opConfig = opConfig;
                    modeConfig[i].fecType = fecType;
                    modeConfig[i].pcsType = pcsType;
                    modeConfig[i].pcsSpeed = speed;
                }
                break;

            case MXD_50GB:
                {
                    switch(opConfig)
                    {
                        case MXD_P50LN: /* 4-lane configuration */
                        case MXD_P50CN:
                        case MXD_P50CF:
                        case MXD_P50KN:
                        case MXD_P50KF:
                        case MXD_P50LF:
                            for (i=0; i<MXD_NUM_LANES; i++)
                            {
                                modeConfig[i].laneSpeed = MXD_LANE_12_5GB;
                                modeConfig[i].opConfig = opConfig;
                                modeConfig[i].fecType = fecType;
                                modeConfig[i].pcsType = pcsType;
                                modeConfig[i].pcsSpeed = speed;
                            }
                            break;

                        case MXD_P50MN: /* 2-lane configuration */
                        case MXD_P50MF:
                        case MXD_P50MR:
                        case MXD_P50BN:
                        case MXD_P50BF:
                        case MXD_P50BR:
                        case MXD_P50JN:
                        case MXD_P50JF:
                        case MXD_P50JR:
                            for (i=0; i<2; i++)
                            {
                                modeConfig[i].laneSpeed = MXD_LANE_25GB;
                                modeConfig[i].opConfig = opConfig;
                                modeConfig[i].fecType = fecType;
                                modeConfig[i].pcsType = pcsType;
                                modeConfig[i].pcsSpeed = speed;
                            }
                            break;

                        default:
                            MXD_DBG_ERROR("mxdSetConfigInfo: 50G 2 or 4 lanes config error OP mode: %u\n", opConfig);
                            return MXD_FAIL;
                            break;
                    }
                    break;
                }

            case MXD_100GB:
                for (i=0; i<MXD_NUM_LANES; i++)
                {
                    modeConfig[i].laneSpeed = MXD_LANE_25GB;
                    modeConfig[i].opConfig = opConfig;
                    modeConfig[i].fecType = fecType;
                    modeConfig[i].pcsType = pcsType;
                    modeConfig[i].pcsSpeed = speed;
                }
                break;

            default:
                MXD_DBG_ERROR("mxdSetConfigInfo: incorrect/unsupported group speed: %u\n", speed);
                return MXD_FAIL;
                break;
        }
    }
    else
    {
        modeConfig[laneOffset].opConfig = opConfig;
        modeConfig[laneOffset].fecType = fecType;
        modeConfig[laneOffset].pcsType = pcsType;
        modeConfig[laneOffset].pcsSpeed = speed;

        switch(speed)
        {
            case MXD_1GB:
                modeConfig[laneOffset].laneSpeed = MXD_LANE_1GB;
                break;

            case MXD_2_5GB:
                modeConfig[laneOffset].laneSpeed = MXD_LANE_2_5GB;
                break;

            case MXD_5GB:
                modeConfig[laneOffset].laneSpeed = MXD_LANE_5GB;
                break;

            case MXD_10GB:
                modeConfig[laneOffset].laneSpeed = MXD_LANE_10GB;
                break;

            case MXD_25GB:
                modeConfig[laneOffset].laneSpeed = MXD_LANE_25GB;
                break;

            default:
                MXD_DBG_ERROR("mxdSetConfigInfo: incorrect/unsupported speed: %u\n", speed);
                return MXD_FAIL;
                break;
        }
    }

    return MXD_OK;
}

/*******************************************************************
 MXD_STATUS mxdSetFixedMode
    Line and Host mode selection
*******************************************************************/
MXD_STATUS mxdSetFixedMode
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig
)
{
    MXD_U16 fecType, autoNeg, modifier;
    MXD_PCS_TYPE pcsType;
    MXD_SPEED speed;
    MXD_U16 regVal = 0;

    pcsType  = (MXD_PCS_TYPE)portConfigTbl[opConfig][PCS_TYPE_IDX];
    fecType  = portConfigTbl[opConfig][FEC_TYPE_IDX];
    autoNeg  = portConfigTbl[opConfig][AUTONEG_IDX];
    speed    = (MXD_SPEED)portConfigTbl[opConfig][SPEED_IDX];
    modifier = portConfigTbl[opConfig][INTERFACE_IDX];

    if ((speed >= MXD_40GB) && (laneOffset != 0))
    {
        MXD_DBG_ERROR("mxdSetFixedMode: Invalid lane selection: \n");
        return MXD_FAIL;
    }

    if (!(host_or_line == MXD_HOST_SIDE || host_or_line == MXD_LINE_SIDE))
    {
        MXD_DBG_ERROR("mxdSetFixedMode: Incorrect line_or_host selection: \n");
        return MXD_FAIL;
    }

    if (mxdPortPowerUp(pDev, mdioPort, host_or_line, laneOffset, opConfig) == MXD_FAIL)
    {
        MXD_DBG_ERROR("mxdSetFixedMode: Power up fail!\n");
        return MXD_FAIL;
    }

    if (mxdRestoreStart(pDev, mdioPort, host_or_line, laneOffset, opConfig) == MXD_FAIL)
    {
        MXD_DBG_ERROR("mxdSetFixedMode: RestoreStart fail!\n");
        return MXD_FAIL;
    }

    if(autoNeg == MXD_AUTONEG_ON)
    {
        ATTEMPT(mxdAutoNegStart(pDev, mdioPort, host_or_line, laneOffset, opConfig, MXD_FALSE));
    }

    if (mxdSetFecConfig(pDev, mdioPort, host_or_line, laneOffset, fecType, opConfig) == MXD_FAIL)
    {
        MXD_DBG_ERROR("mxdSetFixedMode: set FEC config fail!\n");
        return MXD_FAIL;
    }

    if (pcsType == MXD_TRANSPARENT)
    {
        if (mxdRepeaterConfig(pDev, mdioPort, host_or_line, laneOffset, opConfig) == MXD_FAIL)
        {
            MXD_DBG_ERROR("mxdSetFixedMode: mxdRepeaterConfig fail!\n");
            return MXD_FAIL;
        }
    }

    if (mxdStartEnhance(pDev, mdioPort, host_or_line, laneOffset, opConfig) == MXD_FAIL)
    {
        MXD_DBG_ERROR("mxdSetFixedMode: mxdStartEnhance fail!\n");
        return MXD_FAIL;
    }

    if (mxdPerfConfig(pDev, mdioPort, host_or_line, laneOffset, opConfig) == MXD_FAIL)
    {
        MXD_DBG_ERROR("mxdSetFixedMode: mxdPerfConfig fail!\n");
        return MXD_FAIL;
    }

    if (mxdTapConfig(pDev, mdioPort, host_or_line, laneOffset, opConfig) == MXD_FAIL)
    {
        MXD_DBG_ERROR("mxdSetFixedMode: mxdTapConfig fail!\n");
        return MXD_FAIL;
    }

    /* For 20G operation, adjust baud rate here for both line and host sides.
       We override MXD_P25LR and MXD_P25LN (MXD has no 20G setting), and force
       it to 20G */
    if ((host_or_line == MXD_HOST_SIDE) || pDev->use20G)
    {
        ATTEMPT(mxdOverrideClockModifier(pDev, mdioPort, host_or_line, laneOffset, opConfig));
    }

    if (modifier == MXD_IEEE_FEC_BASE)
    {
        /* Set mode selection to reset. FEC request and ability are set in ANEG base page */
        regVal = 0x8000;
    }
    else
    {
        ATTEMPT(mxdHwSetRegFieldToWord(0, speed, 0, 3, &regVal));
        ATTEMPT(mxdHwSetRegFieldToWord(regVal, autoNeg, 4, 1, &regVal));
        ATTEMPT(mxdHwSetRegFieldToWord(regVal, pcsType, 5, 1, &regVal));

        if ((autoNeg == MXD_AUTONEG_ON) && ((opConfig == MXD_P25CR) || (opConfig == MXD_P100CR)))
        {
            /* If AutoNeg is enable, FEC field in 3.F000.7:6 is ignored in P25CR/P100CR mode */
            ATTEMPT(mxdHwSetRegFieldToWord(regVal, 2, 6, 2, &regVal));
        }
        else
        {
            ATTEMPT(mxdHwSetRegFieldToWord(regVal, fecType, 6, 2, &regVal));
        }

        ATTEMPT(mxdHwSetRegFieldToWord(regVal, modifier, 8, 2, &regVal));
        regVal |= 0x8000;
    }

    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (MXD_IF_MODE_SEL_P0+laneOffset), regVal));
    ATTEMPT(mxdSetConfigInfo(pDev, host_or_line, laneOffset, opConfig));

    return MXD_OK;
}


/*******************************************************************************
 MXD_STATUS mxdGetModeSpeed
    Get mode speed based on the OP mode setting
    and get pcs type (PCS, TRANSPARENT, etc.) based on the OP mode setting
*******************************************************************************/
MXD_STATUS mxdGetModeSpeed
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16     mdioPort,
    IN MXD_U16     host_or_line,
    IN MXD_U16     laneOffset,
    OUT MXD_SPEED *speed,
    OUT MXD_PCS_TYPE  *pcsType
)
{
    if (host_or_line == MXD_LINE_SIDE)
    {
        *speed = pDev->lineConfig[laneOffset].pcsSpeed;
        *pcsType  = pDev->lineConfig[laneOffset].pcsType;
    }
    else if (host_or_line == MXD_HOST_SIDE)
    {
        *speed = pDev->hostConfig[laneOffset].pcsSpeed;
        *pcsType  = pDev->hostConfig[laneOffset].pcsType;
    }
    else
    {
        MXD_DBG_ERROR("mxdGetModeSpeed: Incorrect line_or_host selection: \n");
        return MXD_FAIL;
    }

    return MXD_OK;
}



/******************************************************************************
 MXD_STATUS mxdGetDetailedLinkStatus
    Gets current and latched status for one side and lane of the interface based
    on the operating mode of that side/lane. Returns 0 for latchStat
    for lanes in any repeater mode.
******************************************************************************/
MXD_STATUS mxdGetDetailedLinkStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 laneOffset,
    IN MXD_U16 host_or_line,
    OUT MXD_U16 *currStat,
    OUT MXD_U16 *latchStat
)
{
    MXD_OP_CONFIG cfg;

    if (mxdIsLaneOffsetValid(pDev, mdioPort, laneOffset) != MXD_OK)
    {
        MXD_DBG_ERROR("mxdGetDetailedLinkStatus: incorrect lane Offset: %u\n", laneOffset);
        return MXD_FAIL;
    }

    if (host_or_line == MXD_HOST_SIDE)
    {
        cfg = pDev->hostConfig[laneOffset].opConfig;
    }
    else if (host_or_line == MXD_LINE_SIDE)
    {
        cfg = pDev->lineConfig[laneOffset].opConfig;
    }
    else
    {
        MXD_DBG_ERROR("mxdGetDetailedLinkStatus: host_or_line is invalid.\n");
        return MXD_FAIL;
    }

    switch (cfg)
    {
        case MXD_P1X:
        case MXD_P1S:
        case MXD_P1P:
        case MXD_P2_5X:
            ATTEMPT(mxdHwGetPhyRegField(pDev,mdioPort,host_or_line,MXD_PCS_1G_STAT+(0x200*laneOffset),2,1,latchStat));
            ATTEMPT(mxdHwGetPhyRegField(pDev,mdioPort,host_or_line,MXD_PCS_1G_STAT+(0x200*laneOffset),2,1,currStat));
            break;

        case MXD_P5L:
        case MXD_P5K:
        case MXD_P10LN:
        case MXD_P10KN:
        case MXD_P10KF:
        case MXD_P10LF:
        case MXD_P25LN:
        case MXD_P25LF:
        case MXD_P25LR:
        case MXD_P25CN:
        case MXD_P25CF:
        case MXD_P25CR:
        case MXD_P25KN:
        case MXD_P25KF:
        case MXD_P25KR:
        case MXD_P25BN:
        case MXD_P25BF:
        case MXD_P25BR:
        case MXD_P25JN:
        case MXD_P25JF:
        case MXD_P25JR:
        case MXD_P25BCN:
        case MXD_P25BCF:
        case MXD_P25BCR:
        case MXD_P25JKN:
        case MXD_P25JKF:
        case MXD_P25JKR:
            ATTEMPT(mxdHwGetPhyRegField(pDev,mdioPort,host_or_line,MXD_PCS_25G_STATUS+(0x200*laneOffset),2,1,latchStat));
            ATTEMPT(mxdHwGetPhyRegField(pDev,mdioPort,host_or_line,MXD_PCS_25G_STATUS+(0x200*laneOffset),2,1,currStat));
            break;

        case MXD_P29P09LN:
        case MXD_P40LN:
        case MXD_P40CN:
        case MXD_P40CF:
        case MXD_P40KN:
        case MXD_P40KF:
        case MXD_P40LF:
        case MXD_P50LN:
        case MXD_P50CN:
        case MXD_P50CF:
        case MXD_P50KN:
        case MXD_P50KF:
        case MXD_P50LF:
        case MXD_P50MN:
        case MXD_P50MF:
        case MXD_P50MR:
        case MXD_P50BN:
        case MXD_P50BF:
        case MXD_P50BR:
        case MXD_P50JN:
        case MXD_P50JF:
        case MXD_P50JR:
            ATTEMPT(mxdHwGetPhyRegField(pDev,mdioPort,host_or_line,MXD_PCS_40G_STATUS1,2,1,latchStat));
            ATTEMPT(mxdHwGetPhyRegField(pDev,mdioPort,host_or_line,MXD_PCS_40G_STATUS1,2,1,currStat));
            break;

        case MXD_P100LN:
        case MXD_P100LR:
        case MXD_P100CR:
        case MXD_P100KR:
        case MXD_P100KN:
            ATTEMPT(mxdHwGetPhyRegField(pDev,mdioPort,host_or_line,MXD_PCS_100G_STATUS1,2,1,latchStat));
            ATTEMPT(mxdHwGetPhyRegField(pDev,mdioPort,host_or_line,MXD_PCS_100G_STATUS1,2,1,currStat));
            break;

        /* NOTE: When adding any repeater modes, always return 1 for latchStat, since the result should not be used for */
        /* aggregated value () */

        default:
            MXD_DBG_ERROR("mxdGetDetailedLinkStatus: unsupported configuration mode:%d\n", cfg);
            return MXD_FAIL;
            break;
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdReadPCSLinkStatus
    Check PCS link status
*******************************************************************************/
MXD_STATUS mxdReadPCSLinkStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16  laneOffset,
    IN MXD_BOOL perLaneStatus,
    OUT MXD_U16 *currentStatus,
    OUT MXD_U16 *latchedStatus,
    OUT MXD_DETAILED_STATUS_TYPE *statusDetail
)
{
    MXD_U16 curr_stat,latch_stat,laneIdx;

    if (pDev->devInfo & MXD_GROUPED)
    {
        /* Get host side link status, latched then current */
        ATTEMPT(mxdGetDetailedLinkStatus(pDev,mdioPort,laneOffset,MXD_HOST_SIDE,&curr_stat,&latch_stat));
        statusDetail->PCS_lanes_grouped_status.hostLatched = latch_stat;
        statusDetail->PCS_lanes_grouped_status.hostCurrent = curr_stat;

        /* Get line side link status, latched then current */
        ATTEMPT(mxdGetDetailedLinkStatus(pDev,mdioPort,laneOffset,MXD_LINE_SIDE,&curr_stat,&latch_stat));
        statusDetail->PCS_lanes_grouped_status.lineLatched = latch_stat;
        statusDetail->PCS_lanes_grouped_status.lineCurrent = curr_stat;

        /* now set aggregated values */
        *currentStatus = (statusDetail->PCS_lanes_grouped_status.hostCurrent) & (statusDetail->PCS_lanes_grouped_status.lineCurrent);
        *latchedStatus = (statusDetail->PCS_lanes_grouped_status.hostLatched) & (statusDetail->PCS_lanes_grouped_status.lineLatched);
    }
    else /* This is a mixed lane configuration */
    {
        /* check if aggregated value should be only the single lane being checked */
        if (perLaneStatus == MXD_TRUE)
        {
            /* only checking one lane */
            ATTEMPT(mxdGetDetailedLinkStatus(pDev,mdioPort,laneOffset,MXD_HOST_SIDE,&curr_stat,&latch_stat));
            *currentStatus = statusDetail->Per_lane_status.hostCurrent[laneOffset] = curr_stat;
            *latchedStatus = statusDetail->Per_lane_status.hostLatched[laneOffset] = latch_stat;

            ATTEMPT(mxdGetDetailedLinkStatus(pDev,mdioPort,laneOffset,MXD_LINE_SIDE,&curr_stat,&latch_stat));
            statusDetail->Per_lane_status.lineCurrent[laneOffset] = curr_stat;
            statusDetail->Per_lane_status.lineLatched[laneOffset] = latch_stat;

            *currentStatus &= curr_stat; /* combined status is host/line status AND together from both sides */
            *latchedStatus &= latch_stat;
        }
        else
        {
            /* checking all lanes, laneOffset must be 0 */
            if (laneOffset != 0)
            {
                MXD_DBG_ERROR("mxdCheckLinkStatus: requested lane %u, but perLaneStatus is MXD_FALSE\n", laneOffset);
                return MXD_FAIL;
            }

            /* loop through lanes on host side, skip any that aren't configured */
            *currentStatus = 1;
            *latchedStatus = 1;
            for (laneIdx=0; laneIdx < MXD_NUM_LANES; laneIdx++)
            {
                /* both host/line of this lane must be configured to be included in results */
                if ((pDev->hostConfig[laneIdx].opConfig != MXD_CONFIG_UNKNOWN) &&
                    (pDev->lineConfig[laneIdx].opConfig != MXD_CONFIG_UNKNOWN))
                {
                    /* get host side status */
                    ATTEMPT(mxdGetDetailedLinkStatus(pDev,mdioPort,laneOffset,MXD_HOST_SIDE,&curr_stat,&latch_stat));
                    statusDetail->Per_lane_status.hostCurrent[laneOffset] = curr_stat;
                    statusDetail->Per_lane_status.hostLatched[laneOffset] = latch_stat;

                    (*currentStatus) &= curr_stat;  /* combined status is host/line status AND together from both sides all lanes */
                    (*latchedStatus) &= latch_stat;

                    /* get line side status */
                    ATTEMPT(mxdGetDetailedLinkStatus(pDev,mdioPort,laneOffset,MXD_LINE_SIDE,&curr_stat,&latch_stat));
                    statusDetail->Per_lane_status.lineCurrent[laneOffset] = curr_stat;
                    statusDetail->Per_lane_status.lineLatched[laneOffset] = latch_stat;

                    (*currentStatus) &= curr_stat;  /* combined status is host/line status AND together from both sides all lanes */
                    (*latchedStatus) &= latch_stat;
                }
                /* else this lane is not configured, skip it */
            }
        }
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdReadRepeaterLinkStatus
    Check Serdes DSP lock status on the ports
    Returns status of single lane or all lanes on both host and line side.
*******************************************************************************/
MXD_STATUS mxdReadRepeaterLinkStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16  laneOffset,
    IN MXD_BOOL perLaneStatus,
    OUT MXD_U16 *CurrentStatus,
    OUT MXD_DETAILED_STATUS_TYPE *statusDetail
)
{
    MXD_U16 i, hostDspLock, hostSigDetect, lineDspLock, lineSigDetect;
    MXD_OP_CONFIG portConfig;

    portConfig = pDev->hostConfig[laneOffset].opConfig;

    switch (portConfig)
    {
        case MXD_R40L:
        case MXD_R40C:
        case MXD_R40K:
        case MXD_R100L:
        case MXD_R100C:
        case MXD_R100K:
        case MXD_R1:
        case MXD_R2_5:
        case MXD_R5:
        case MXD_R10L:
        case MXD_R10K:
        case MXD_R25L:
        case MXD_R25C:
        case MXD_R25K:
            break;

        default:
            MXD_DBG_ERROR("mxdReadRepeaterLinkStatus: incorrect/unsupported mode selection: %u\n", portConfig);
            return MXD_FAIL;
    }

    *CurrentStatus = 1;

    if (perLaneStatus)
    {
        ATTEMPT(mxdGetSerdesSignalDetectAndDspLock(pDev, mdioPort, MXD_HOST_SIDE, laneOffset, &hostSigDetect, &hostDspLock));
        ATTEMPT(mxdGetSerdesSignalDetectAndDspLock(pDev, mdioPort, MXD_LINE_SIDE, laneOffset, &lineSigDetect, &lineDspLock));

        *CurrentStatus &= (hostDspLock & hostSigDetect & lineDspLock & lineSigDetect);
        statusDetail->Repeater_status.hostCurrent[laneOffset] = (hostDspLock & hostSigDetect);
        statusDetail->Repeater_status.lineCurrent[laneOffset] = (lineDspLock & lineSigDetect);
    }
    else
    {
        for (i=0; i<MXD_NUM_LANES; i++)
        {
            ATTEMPT(mxdGetSerdesSignalDetectAndDspLock(pDev, mdioPort, MXD_HOST_SIDE, i, &hostSigDetect, &hostDspLock));
            ATTEMPT(mxdGetSerdesSignalDetectAndDspLock(pDev, mdioPort, MXD_LINE_SIDE, i, &lineSigDetect, &lineDspLock));

            *CurrentStatus &= (hostDspLock & hostSigDetect & lineDspLock & lineSigDetect);
            statusDetail->Repeater_status.hostCurrent[i] = (hostDspLock & hostSigDetect);
            statusDetail->Repeater_status.lineCurrent[i] = (lineDspLock & lineSigDetect);
        }
    }


    return MXD_OK;
}


#define LINE_SOFT_RESET     0x8000
#define LINE_HARD_RESET     0x2000
#define HOST_SOFT_RESET     0x0080
#define HOST_HARD_RESET     0x0020
#define PORT_ALL_RESET      (LINE_SOFT_RESET|LINE_HARD_RESET|HOST_SOFT_RESET|HOST_HARD_RESET)

/*******************************************************************
 MXD_STATUS mxdPortResetTimeout
 Check timeout after the soft or hard reset
*******************************************************************/
MXD_STATUS mxdPortResetTimeout
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 timeoutMs
)
{
    MXD_U16 temp, counter;

    if (timeoutMs)
    {
        counter=0;
        ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_PORT_REG, MXD_PORT_PWD_RESET, &temp));

        while ((temp & PORT_ALL_RESET) && (counter <= timeoutMs))
        {
            ATTEMPT(mxdWait(pDev,1));
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_PORT_REG, MXD_PORT_PWD_RESET, &temp));
            counter++;
        }

        if (counter < timeoutMs)
        {
           return MXD_OK;
        }
        else
        {
           MXD_DBG_ERROR("mxdPortResetTimeout: Timeout: %u failed.\n", counter);
           return MXD_FAIL; /* timed out without becoming ready */
        }
    }
    return MXD_OK;
}


/*******************************************************************
 MXD_STATUS mxdLaneReset
     Check timeout after the Lane soft reset
*******************************************************************/
MXD_STATUS mxdLaneSoftReset
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_U16 timeoutMs
)
{
    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, (MXD_IF_MODE_SEL_P0+laneOffset), 15, 1, 1));
    ATTEMPT(mxdLaneResetTimeout(pDev, mdioPort, host_or_line, laneOffset, timeoutMs));

    return MXD_OK;
}

/*******************************************************************
 MXD_STATUS mxdLaneResetTimeout
 Check timeout after the Lane soft reset
*******************************************************************/
MXD_STATUS mxdLaneResetTimeout
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_U16 timeoutMs
)
{
    MXD_U16 temp, counter;

    if (timeoutMs)
    {
        counter=0;
        ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, (MXD_IF_MODE_SEL_P0+laneOffset), &temp));

        while ((temp & 0x8000) && (counter <= timeoutMs))
        {
            ATTEMPT(mxdWait(pDev,1));
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, (MXD_IF_MODE_SEL_P0+laneOffset), &temp));
            counter++;
        }

        if (counter < timeoutMs)
        {
           return MXD_OK;
        }
        else
        {
           MXD_DBG_ERROR("mxdLaneResetTimeout: Timeout: %u failed.\n", counter);
           return MXD_FAIL; /* timed out without becoming ready */
        }
    }
    return MXD_OK;
}

/*******************************************************************
 MXD_STATUS mxdPortPowerHwResetTimeout
    Power down and Reset mdioPort wait time
*******************************************************************/
MXD_STATUS mxdPortPowerHwResetTimeout
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 timeoutMs
)
{
    MXD_U16 lane0, lane1, lane2, lane3;
    MXD_U16 counter = 0;

    if (mxdIsPortValid(pDev, mdioPort) != MXD_OK)
    {
        MXD_DBG_ERROR("mxdPortPowerHwResetWait: incorrect mdioPort selection: %u\n", mdioPort);
        return MXD_FAIL;
    }

    do
    {
        ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_SIDE, 0xF200, 4, 1, &lane0));
        ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_SIDE, 0xF280, 4, 1, &lane1));
        ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_SIDE, 0xF300, 4, 1, &lane2));
        ATTEMPT(mxdHwGetPhyRegField(pDev, mdioPort, MXD_LINE_SIDE, 0xF380, 4, 1, &lane3));

        if (lane0 && lane1 && lane2 && lane3)
        {
            /* MXD_DBG_INFO("mxdPortPowerHwResetTimeout: counter: %u\n", counter); */
            return MXD_OK;
        }

        ATTEMPT(mxdWait(pDev, 200));
        counter = counter + 200;

    } while (timeoutMs > counter);

    MXD_DBG_ERROR("mxdPortPowerHwResetTimeout: Timeout: %u failed. Ln0:0x%x Ln1:0x%x Ln2:0x%x Ln3:0x%x\n",
                  counter, lane0, lane1, lane2, lane3);

    return MXD_FAIL; /* timed out without becoming ready */
}

/*******************************************************************
 MXD_STATUS mxdPortPowerHwReset
   Power down and reset mdioPort on both the host and line side
*******************************************************************/
MXD_STATUS mxdPortPowerHwReset
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort
)
{
    if (mxdIsPortValid(pDev, mdioPort) != MXD_OK)
    {
        MXD_DBG_ERROR("mxdPortPowerHwReset: incorrect mdioPort selection: %u\n", mdioPort);
        return MXD_FAIL;
    }

    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_PORT_REG, MXD_PORT_PWD_RESET, 0x4040));

    if (mxdPortPowerHwResetTimeout(pDev, mdioPort, MXD_RESET_TIMEOUT) == MXD_FAIL)
    {
        MXD_DBG_ERROR("mxdPortPowerHwReset: power down fail on mdioPort: %u\n", mdioPort);
        return MXD_FAIL;
    }

    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_PORT_REG, MXD_PORT_PWD_RESET, 0x6060));

    return MXD_OK;
}

/*******************************************************************
 MXD_STATUS mxdPortPowerUp
   Power down and reset mdioPort on both the host and line side
*******************************************************************/
MXD_STATUS mxdPortPowerUp
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig
)
{

    if (host_or_line == MXD_LINE_SIDE)
    {
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_PORT_PWD_RESET, 0x0000));
        switch(opConfig)
        {
            case MXD_P1X:
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, (MXD_PCS_1G_CNTL+(laneOffset*0x200)), 0x0140));
                break;

            case MXD_P1P:
            case MXD_P1S:
            case MXD_R1:
            case MXD_P2_5X:
            case MXD_R2_5:
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, (MXD_PCS_1G_CNTL+(laneOffset*0x200)), 0x2040));
                break;

            case MXD_P5L:
            case MXD_P5K:
            case MXD_R5:
            case MXD_P10LN:
            case MXD_P10LF:
            case MXD_P10KN:
            case MXD_P10KF:
            case MXD_R10L:
            case MXD_R10K:
            case MXD_R25L:
            case MXD_R25C:
            case MXD_R25K:
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, (MXD_PCS_25G_CNTL+(laneOffset*0x200)), 0x2040));
                break;

            case MXD_P25CN:
            case MXD_P25CF:
            case MXD_P25CR:
            case MXD_P25BN:
            case MXD_P25BF:
            case MXD_P25BR:
            case MXD_P25LF:
            case MXD_P25LR:
            case MXD_P25LN:
            case MXD_P25KN:
            case MXD_P25KF:
            case MXD_P25KR:
            case MXD_P25JN:
            case MXD_P25JF:
            case MXD_P25JR:
            case MXD_P25BCN:
            case MXD_P25BCF:
            case MXD_P25BCR:
            case MXD_P25JKN:
            case MXD_P25JKF:
            case MXD_P25JKR:
                if (pDev->devInfo & MXD_LANES_GROUPED)
                {
                    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, MXD_PCS_25G_CNTL, 0x2040));
                }
                else
                {
                    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, (MXD_PCS_25G_CNTL+(laneOffset*0x200)), 0x2040));
                }
                break;

            case MXD_P29P09LN:
            case MXD_P40LN:
            case MXD_P40CN:
            case MXD_P40CF:
            case MXD_P40KN:
            case MXD_P40KF:
            case MXD_P40LF:
            case MXD_P50LN:
            case MXD_P50CN:
            case MXD_P50CF:
            case MXD_P50KN:
            case MXD_P50KF:
            case MXD_P50LF:
            case MXD_P50MN:
            case MXD_P50MF:
            case MXD_P50MR:
            case MXD_P50BN:
            case MXD_P50BF:
            case MXD_P50BR:
            case MXD_P50JN:
            case MXD_P50JF:
            case MXD_P50JR:
            case MXD_R40L:
            case MXD_R40C:
            case MXD_R40K:
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0x1000, 0x204C));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0x3200, 0x2840));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0x3400, 0x2840));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0x3600, 0x2840));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0x2200, 0x2840));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0x2400, 0x2840));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0x2600, 0x2840));
                break;

            case MXD_P100CR:
            case MXD_P100KR:
            case MXD_P100KN:
            case MXD_P100LN:
            case MXD_P100LR:
            case MXD_R100L:
            case MXD_R100C:
            case MXD_R100K:
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0x0000, 0x204C));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0x3200, 0x2840));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0x3400, 0x2840));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0x3600, 0x2840));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0x2200, 0x2840));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0x2400, 0x2840));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0x2600, 0x2840));
                break;

            default:
                MXD_DBG_ERROR("mxdPortPowerUp: OP Config:%u line side not supported.\n", opConfig);
                return MXD_FAIL;
                break;
        }
    }
    else if (host_or_line == MXD_HOST_SIDE)
    {
        switch(opConfig)
        {
            case MXD_P1X:
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, (MXD_PCS_1G_CNTL+(laneOffset*0x200)), 0x0140));
                break;

            case MXD_P1P:
            case MXD_R1:
            case MXD_P2_5X:
            case MXD_R2_5:
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, (MXD_PCS_1G_CNTL+(laneOffset*0x200)), 0x2040));
                break;

            case MXD_P5L:
            case MXD_P5K:
            case MXD_R5:
            case MXD_P10LF:
            case MXD_P10LN:
            case MXD_P10KN:
            case MXD_P10KF:
            case MXD_R10L:
            case MXD_R10K:
            case MXD_R25L:
            case MXD_R25C:
            case MXD_R25K:
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, (MXD_PCS_25G_CNTL+(laneOffset*0x200)), 0x2040));
                break;

            case MXD_P25CN:
            case MXD_P25CF:
            case MXD_P25CR:
            case MXD_P25BN:
            case MXD_P25BF:
            case MXD_P25BR:
            case MXD_P25LF:
            case MXD_P25LR:
            case MXD_P25LN:
            case MXD_P25KN:
            case MXD_P25KF:
            case MXD_P25KR:
            case MXD_P25JN:
            case MXD_P25JF:
            case MXD_P25JR:
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, (MXD_PCS_25G_CNTL+(laneOffset*0x200)), 0x2040));
                break;

            case MXD_P29P09LN:
            case MXD_P40LN:
            case MXD_P40CN:
            case MXD_P40CF:
            case MXD_P40KN:
            case MXD_P40KF:
            case MXD_P40LF:
            case MXD_P50LN:
            case MXD_P50CN:
            case MXD_P50CF:
            case MXD_P50KN:
            case MXD_P50KF:
            case MXD_P50LF:
            case MXD_P50MN:
            case MXD_P50MF:
            case MXD_P50MR:
            case MXD_P50BN:
            case MXD_P50BF:
            case MXD_P50BR:
            case MXD_P50JN:
            case MXD_P50JF:
            case MXD_P50JR:
            case MXD_R40L:
            case MXD_R40C:
            case MXD_R40K:
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, 0x1000, 0x204C));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, 0x3200, 0x2840));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, 0x3400, 0x2840));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, 0x3600, 0x2840));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, 0x2200, 0x2840));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, 0x2400, 0x2840));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, 0x2600, 0x2840));
                break;

            case MXD_P100CR:
            case MXD_P100KR:
            case MXD_P100KN:
            case MXD_P100LN:
            case MXD_P100LR:
            case MXD_R100L:
            case MXD_R100C:
            case MXD_R100K:
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, 0x0000, 0x204C));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, 0x3200, 0x2840));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, 0x3400, 0x2840));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, 0x3600, 0x2840));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, 0x2200, 0x2840));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, 0x2400, 0x2840));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, 0x2600, 0x2840));
                break;

            default:
                MXD_DBG_ERROR("mxdPortPowerUp: OP Config:%u host side not supported.\n", opConfig);
                return MXD_FAIL;
                break;
        }
    }
    else
    {
       MXD_DBG_ERROR("mxdPortPowerUp: host_or_line is invalid.\n");
       return MXD_FAIL;
    }

    return MXD_OK;
}

/*******************************************************************
 MXD_STATUS mxdRestoreStart
   Restore start of a port
*******************************************************************/
MXD_STATUS mxdRestoreStart
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig
)
{
    MXD_U16 temp;
    MXD_U16 regOffset = 0;
    MXD_BOOL groupMode = MXD_FALSE;

    if (!(host_or_line == MXD_HOST_SIDE || host_or_line == MXD_LINE_SIDE))
    {
        MXD_DBG_ERROR("mxdRestoreStart: host_or_line is invalid\n");
        return MXD_FAIL;
    }

    if (host_or_line == MXD_HOST_SIDE)
    {
        regOffset = 0x1000;
    }

    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_CNTL_LINE+regOffset)+(laneOffset*0x200)), 12, 1, 0x0));

    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_ADV2_LINE+regOffset)+(laneOffset*0x200)), &temp));
    temp &= 0x0C5F;  /* b0000 xx00 0x0x xxxx */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_ADV2_LINE+regOffset)+(laneOffset*0x200)), temp));

    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_LANE_CTRL1_LINE+regOffset)+(laneOffset*0x200)), &temp));
    temp &= 0xFCCF;  /* bxxxx xx00 xx00 xxxx */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_LANE_CTRL1_LINE+regOffset)+(laneOffset*0x200)), temp));

    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_ADV3_LINE+regOffset)+(laneOffset*0x200)), 0x0000));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_LANE_CTRL2_LINE+regOffset)+(laneOffset*0x200)), 0x0000));

    if (host_or_line == MXD_HOST_SIDE)
    {
        switch(opConfig)
        {
            case MXD_P1X:
            case MXD_P1P:
            case MXD_R1:
                ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_HOST_SIDE, 0xF0BA, &temp));
                temp |= (0x8000|(0x0800<<laneOffset));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, 0xF0BA, temp));

                ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_HOST_SIDE, 0xF0A6, &temp));
                temp |= 0x8000;
                temp &= ~(0x0800<<laneOffset);
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, 0xF0A6, temp));


                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, 0xF378,  0x0));
                break;

            case MXD_P2_5X:
            case MXD_R2_5:
            case MXD_P5L:
            case MXD_P5K:
            case MXD_R5:
            case MXD_P10LF:
            case MXD_P10LN:
            case MXD_P10KN:
            case MXD_P10KF:
            case MXD_R10L:
            case MXD_R10K:
            case MXD_P25CN:
            case MXD_P25CF:
            case MXD_P25CR:
            case MXD_P25BN:
            case MXD_P25BF:
            case MXD_P25BR:
            case MXD_P25LF:
            case MXD_P25LR:
            case MXD_P25LN:
            case MXD_P25KN:
            case MXD_P25KF:
            case MXD_P25KR:
            case MXD_P25JN:
            case MXD_P25JF:
            case MXD_P25JR:
            case MXD_R25L:
            case MXD_R25C:
            case MXD_R25K:
                ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_HOST_SIDE, 0xF0BA, &temp));
                temp |= 0x8000;
                temp &= ~(0x0800<<laneOffset);
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, 0xF0BA, temp));

                ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_HOST_SIDE, 0xF0A6, &temp));
                temp |= 0x8000;
                temp &= ~(0x0800<<laneOffset);
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, 0xF0A6, temp));

                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, 0xF378,  0x0));
                break;

            case MXD_P29P09LN:
            case MXD_P40LN:
            case MXD_P40CN:
            case MXD_P40CF:
            case MXD_P40KN:
            case MXD_P40KF:
            case MXD_P40LF:
            case MXD_P50CN:
            case MXD_P50CF:
            case MXD_P50KN:
            case MXD_P50KF:
            case MXD_P50LN:
            case MXD_P50LF:
            case MXD_P50MN:
            case MXD_P50MF:
            case MXD_P50MR:
            case MXD_P50BN:
            case MXD_P50BF:
            case MXD_P50BR:
            case MXD_P50JN:
            case MXD_P50JF:
            case MXD_P50JR:
            case MXD_P100CR:
            case MXD_P100KR:
            case MXD_P100KN:
            case MXD_P100LN:
            case MXD_P100LR:
            case MXD_R40L:
            case MXD_R40C:
            case MXD_R40K:
            case MXD_R100L:
            case MXD_R100C:
            case MXD_R100K:
                ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_HOST_SIDE, 0xF0BA, &temp));
                temp |= 0x8000;
                temp &= ~(0x0800);
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, 0xF0BA, temp));

                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_HOST_SIDE, 0xF0A6, 15, 1, 0x0));
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_HOST_SIDE, 0xF378, 0, 1, 0x1));

                groupMode = MXD_TRUE;
                break;

            default:
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, 0xF378, 0x0000));
                break;
        }
    }
    else
    {
        switch(opConfig)
        {
            case MXD_P1X:
            case MXD_P1S:
            case MXD_P1P:
            case MXD_R1:
                ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_LINE_SIDE, 0xF0BA, &temp));
                temp |= (0x8000|(0x0800<<laneOffset));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0xF0BA, temp));

                ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_LINE_SIDE, 0xF0A6, &temp));
                temp |= 0x8000;
                temp &= ~(0x0800<<laneOffset);
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0xF0A6, temp));

                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0xF378,  0x0));
                break;

            case MXD_P2_5X:
            case MXD_R2_5:
            case MXD_P5L:
            case MXD_P5K:
            case MXD_R5:
            case MXD_P10LF:
            case MXD_P10LN:
            case MXD_P10KN:
            case MXD_P10KF:
            case MXD_R10L:
            case MXD_R10K:
            case MXD_P25CN:
            case MXD_P25CF:
            case MXD_P25CR:
            case MXD_P25BN:
            case MXD_P25BF:
            case MXD_P25BR:
            case MXD_P25LF:
            case MXD_P25LR:
            case MXD_P25LN:
            case MXD_P25KN:
            case MXD_P25KF:
            case MXD_P25KR:
            case MXD_P25JN:
            case MXD_P25JF:
            case MXD_P25JR:
            case MXD_R25L:
            case MXD_R25C:
            case MXD_R25K:
                ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_LINE_SIDE, 0xF0BA, &temp));
                temp |= 0x8000;
                temp &= ~(0x0800<<laneOffset);
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0xF0BA, temp));

                ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_LINE_SIDE, 0xF0A6, &temp));
                temp |= 0x8000;
                temp &= ~(0x0800<<laneOffset);
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0xF0A6, temp));

                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0xF378,  0x0));
                break;

            case MXD_P29P09LN:
            case MXD_P40LN:
            case MXD_P40CN:
            case MXD_P40CF:
            case MXD_P40KN:
            case MXD_P40KF:
            case MXD_P40LF:
            case MXD_P50CN:
            case MXD_P50CF:
            case MXD_P50KN:
            case MXD_P50KF:
            case MXD_P50LN:
            case MXD_P50LF:
            case MXD_P50MN:
            case MXD_P50MF:
            case MXD_P50MR:
            case MXD_P50BN:
            case MXD_P50BF:
            case MXD_P50BR:
            case MXD_P50JN:
            case MXD_P50JF:
            case MXD_P50JR:
            case MXD_P100CR:
            case MXD_P100KR:
            case MXD_P100KN:
            case MXD_P100LN:
            case MXD_P100LR:
            case MXD_R40L:
            case MXD_R40C:
            case MXD_R40K:
            case MXD_R100L:
            case MXD_R100C:
            case MXD_R100K:
                ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_LINE_SIDE, 0xF0BA, &temp));
                temp |= 0x8000;
                temp &= ~(0x0800);
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0xF0BA, temp));

                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_LINE_SIDE, 0xF0A6, 15, 1, 0x0));
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_LINE_SIDE, 0xF378, 0, 1, 0x1));

                groupMode = MXD_TRUE;
                break;

            case MXD_P25BCN:
            case MXD_P25BCF:
            case MXD_P25BCR:
            case MXD_P25JKN:
            case MXD_P25JKF:
            case MXD_P25JKR:
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0xF378, 0x0000));
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, (0xF258+(laneOffset*0x80)), 0x0000));
                return MXD_OK;  /* combined IEEE/Consortium modes ends here */
                break;

            default:
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_LINE_SIDE, 0xF378, 0x0000));
                break;
        }
    }

    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF258+(laneOffset*0x80)), 0x0000));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF259+(laneOffset*0x80)), 0x0000));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF25A+(laneOffset*0x80)), 0x0000));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF25B+(laneOffset*0x80)), 0x0000));

    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, (0xF26F+(laneOffset*0x80)),  14, 2, 0x0));

    if (groupMode == MXD_FALSE)
    {
        ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF060,  2, 1, 0x0));
    }

    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF053, 0x0000));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF056, 0x0000));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF059, 0x0000));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_AUTONEG, (0x8200+regOffset), 0x0000));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_AUTONEG, (0x8400+regOffset), 0x0000));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_AUTONEG, (0x8600+regOffset), 0x0000));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF0E7, 0x0000));

    if (groupMode == MXD_TRUE)
    {
        ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF060,  2, 1, 0x0));
    }

    return MXD_OK;
}

/*******************************************************************
 MXD_STATUS mxdRepeaterConfig
   Repeater modes config 
*******************************************************************/
MXD_STATUS mxdRepeaterConfig
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig
)
{
    MXD_U16 temp;

    if (!(host_or_line == MXD_HOST_SIDE || host_or_line == MXD_LINE_SIDE))
    {
        MXD_DBG_ERROR("mxdRepeaterConfig: host_or_line is invalid\n");
        return MXD_FAIL;
    }

    switch(opConfig)
    {
        case MXD_R1:
        case MXD_R2_5:
        case MXD_R5:
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, (0xF25C+(laneOffset*0x80)), &temp));
            temp |= 0x0002;  /* bxxxx xxxx xxxx xx1x */
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF25C+(laneOffset*0x80)), temp));
    
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, (0xF258+(laneOffset*0x80)), &temp));
            temp |= 0x0007;  /* bxxxx xxxx xxxx x111 */
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF258+(laneOffset*0x80)), temp));

            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, 0xF060, &temp));
            temp |= 0x0004;  /* bxxxx xxxx xxxx x1xx */
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF060, temp));
            break;

        case MXD_R10L:
        case MXD_R10K:
        case MXD_R40L:
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, (0xF25C+(laneOffset*0x80)), &temp));
            temp |= 0x0022;  /* bxxxx xxxx xx1x xx1x */
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF25C+(laneOffset*0x80)), temp));
    
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF220+(laneOffset*0x80)), 0x1918));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF221+(laneOffset*0x80)), 0x1819));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF230+(laneOffset*0x80)), 0x0007));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF231+(laneOffset*0x80)), 0x0aff));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF232+(laneOffset*0x80)), 0x0000));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF250+(laneOffset*0x80)), 0x1111));

            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, (0xF251+(laneOffset*0x80)), &temp));
            temp |= 0x0055;  /* bxxxx xxxx 0101 0101 */
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF251+(laneOffset*0x80)), temp));

            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF222+(laneOffset*0x80)), 0x0530));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF234+(laneOffset*0x80)), 0x0070));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF235+(laneOffset*0x80)), 0x0014));
            
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, (0xF26F+(laneOffset*0x80)), 14, 2, 0x3));

            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, (0xF258+(laneOffset*0x80)), &temp));
            temp |= 0x0037;  /* bxxxx xxxx xx11 x111 */
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF258+(laneOffset*0x80)), temp));

            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF060, 2, 1, 0x1));
            break;

        case MXD_R40C:
        case MXD_R40K:
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, 0xF25C , &temp));
            temp |= 0x0022;  /* bxxxx xxxx xx1x xx1x */
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF25C, temp));
    
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF220, 0x1918));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF221, 0x1819));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF230, 0x0007));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF231, 0x0aff));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF232, 0x0000));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF250, 0x1111));

            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF251, 0, 8, 0x55));

            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF222, 0x0530));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF234, 0x0070));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF235, 0x0014));
            
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF26F, 14, 2, 0x3));

            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, 0xF258, &temp));
            temp |= 0x0037;  /* bxxxx xxxx xx11 x111 */
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF258, temp));

            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF053, 0x0035));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF056, 0x0035));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF059, 0x0035));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0x8200, 0x0105));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0x8400, 0x0105));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0x8600, 0x0105));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF0E7, 0xf800));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF378, 0x0000));

            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF2DD, 1, 1, 0x1));

            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF2A3, 0x0800));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF2B7, 0x0101));

            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF2D1, 12, 1, 0x1));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF2DA, 7, 1, 0x1));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF35D, 1, 1, 0x1));

            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF323, 0x0800));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF337, 0x0101));

            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF351, 12, 1, 0x1));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF35A, 7, 1, 0x1));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF3DD, 1, 1, 0x1));

            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF3A3, 0x0800));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF3B7, 0x0101));

            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF3D1, 12, 1, 0x1));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF3DA, 7, 1, 0x1));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF060, 2, 1, 0x1));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF25D, 3, 1, 0x1));

            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF224, 0x1918));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF238, 0x4001));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF239, 0x01ff));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF252, 0x0033));

            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF25A, 8, 2, 0x3));
            break;

        case MXD_R25L:
        case MXD_R25C:
        case MXD_R25K:
        case MXD_R100L:
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, (0xF25C+(laneOffset*0x80)), &temp));
            temp |= 0x0020;  /* bxxxx xxxx xx1x xxxx */
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF25C+(laneOffset*0x80)), temp));
    
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF222+(laneOffset*0x80)), 0x0530));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF234+(laneOffset*0x80)), 0x0070));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF235+(laneOffset*0x80)), 0x0028));
            
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, (0xF251+(laneOffset*0x80)), 0, 8, 0x55));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, (0xF26F+(laneOffset*0x80)), 14, 2, 0x3));

            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, (0xF258+(laneOffset*0x80)), &temp));
            temp |= 0x0030;  /* bxxxx xxxx xx11 xxxx */
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF258+(laneOffset*0x80)), temp));

            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF060, 2, 1, 0x1));
            break;

        case MXD_R100C:
        case MXD_R100K:
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF25C, 5, 1, 0x1));

            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF222, 0x0530));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF234, 0x0070));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF235, 0x0028));
            
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF251, 0, 8, 0x55));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF26F, 14, 2, 0x3));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF258, 4, 2, 0x3));

            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF053, 0x0035));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF056, 0x0035));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF059, 0x0035));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_AUTONEG, 0x8200, 0x0105));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_AUTONEG, 0x8400, 0x0105));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_AUTONEG, 0x8600, 0x0105));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF0E7, 0xF800));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF378, 0x0000));

            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF2DD, 1, 1, 0x1));

            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF2A3, 0x0800));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF2B7, 0x0101));

            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF2D1, 12, 1, 0x1));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF2DA, 7, 1, 0x1));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF35D, 1, 1, 0x1));

            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF323, 0x0800));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF337, 0x0101));

            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF351, 12, 1, 0x1));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF35A, 7, 1, 0x1));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF3DD, 1, 1, 0x1));

            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF3A3, 0x0800));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF3B7, 0x0101));

            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF3D1, 12, 1, 0x1));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF3DA, 7, 1, 0x1));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF060, 2, 1, 0x1));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF25D, 3, 1, 0x1));

            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF224, 0x1918));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF238, 0x4001));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF239, 0x01ff));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF252, 0x0033));

            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF25A, 8, 2, 0x3));
            break;

        default:
            MXD_DBG_ERROR("mxdRepeaterConfig: OP Config mode:%u not supported or implemented yet.\n", opConfig);
            return MXD_FAIL;
            break;
    }


    return MXD_OK;
}

/*******************************************************************
 MXD_STATUS mxdStartEnhance
   Start enhancements 
*******************************************************************/
MXD_STATUS mxdStartEnhance
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig
)
{
    MXD_U16 temp;

    if (!(host_or_line == MXD_HOST_SIDE || host_or_line == MXD_LINE_SIDE))
    {
        MXD_DBG_ERROR("mxdStartEnhance: host_or_line is invalid\n");
        return MXD_FAIL;
    }

    switch(opConfig)
    {
        case MXD_P5K:
        case MXD_P10KN:
        case MXD_P10KF:
        case MXD_R10K:
        case MXD_P25CN:
        case MXD_P25CF:
        case MXD_P25CR:
        case MXD_P25KN:
        case MXD_P25KF:
        case MXD_P25KR:
        case MXD_P25BN:
        case MXD_P25BF:
        case MXD_P25BR:
        case MXD_P25JN:
        case MXD_P25JF:
        case MXD_P25JR:
        case MXD_R25C:
        case MXD_R25K:
        case MXD_P40CN:
        case MXD_P40CF:
        case MXD_P40KN:
        case MXD_P40KF:
        case MXD_P50CN:
        case MXD_P50CF:
        case MXD_P50KN:
        case MXD_P50KF:
        case MXD_P50BN:
        case MXD_P50BF:
        case MXD_P50BR:
        case MXD_P50JN:
        case MXD_P50JF:
        case MXD_P50JR:
        case MXD_P100CR:
        case MXD_P100KR:
        case MXD_P100KN:
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, (0xF25D+(laneOffset*0x80)), &temp));
            temp |= 0x0008;  /* bxxxx xxxx xxxx 1xxx */
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF25D+(laneOffset*0x80)), temp));
    
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF224+(laneOffset*0x80)), 0x1918));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF238+(laneOffset*0x80)), 0x4001));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF239+(laneOffset*0x80)), 0x01ff));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF252+(laneOffset*0x80)), 0x0033));

            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, (0xF25A+(laneOffset*0x80)), &temp));
            temp |= 0x0300;  /* bxxxx xx11 xxxx xxxx */
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF25A+(laneOffset*0x80)), temp));
            break;

        case MXD_P10LN:
        case MXD_P10LF:
        case MXD_P29P09LN:
        case MXD_P40LN:
        case MXD_P40LF:
        case MXD_P50LN:
        case MXD_P50LF:
        case MXD_P50MN:
        case MXD_P50MF:
        case MXD_P50MR:
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, (0xF25C+(laneOffset*0x80)), &temp));
            temp |= 0x0002;  /* bxxxx xxxx xxxx xx1x */
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF25C+(laneOffset*0x80)), temp));
    
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF220+(laneOffset*0x80)), 0x1918));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF221+(laneOffset*0x80)), 0x1819));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF230+(laneOffset*0x80)), 0x0007));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF231+(laneOffset*0x80)), 0x0aff));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF232+(laneOffset*0x80)), 0x0000));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF250+(laneOffset*0x80)), 0x1111));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF251+(laneOffset*0x80)), 0x1111));

            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, (0xF258+(laneOffset*0x80)), &temp));
            temp |= 0x0007;  /* bxxxx xxxx xxxx x111 */
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF258+(laneOffset*0x80)), temp));
            break;

        default:
            break;
    }

    return MXD_OK;
}


/*******************************************************************
 MXD_STATUS mxdPerfConfig
   Performance config 
*******************************************************************/
MXD_STATUS mxdPerfConfig
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig
)
{
    MXD_U16 temp;

    if (!(host_or_line == MXD_HOST_SIDE || host_or_line == MXD_LINE_SIDE))
    {
        MXD_DBG_ERROR("mxdPerfConfig: host_or_line is invalid\n");
        return MXD_FAIL;
    }

    switch (opConfig)
    {
        case MXD_P25BCN:
        case MXD_P25BCF:
        case MXD_P25BCR: 
        case MXD_P25JKN:
        case MXD_P25JKF:
        case MXD_P25JKR:
            return MXD_OK;
            break;

        default:
            /* continue below performance config if not in above list */
            break;
    }

    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, (0xF25C+(laneOffset*0x80)), &temp));
    temp |= 0x0002;  /* bxxxx xxxx xxxx xx1x */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF25C+(laneOffset*0x80)), temp));
    
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF22B+(laneOffset*0x80)), 0x1918));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF246+(laneOffset*0x80)), 0x4033));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF247+(laneOffset*0x80)), 0x4820));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF255+(laneOffset*0x80)), 0x1100));

    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, (0xF259+(laneOffset*0x80)), &temp));
    temp |= 0x00C0;  /* bxxxx xxxx 11xx xxxx */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF259+(laneOffset*0x80)), temp));

    return MXD_OK;
}

/*******************************************************************
 MXD_STATUS mxdOverrideClockModifier
  Override clock on some speeds
*******************************************************************/
MXD_STATUS mxdOverrideClockModifier
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig
)
{
    MXD_U16 i;

    /* For 20G operation, adjust baud rate here for both line and host sides.
       We override MXD_P25LR and MXD_P25LN (MXD has no 20G setting), and force
       it to 20G */
    if ((host_or_line == MXD_LINE_SIDE) && !pDev->use20G)
    {
        MXD_DBG_ERROR("mxdOverrideClockModifier: Override clock only on host side\n");
        return MXD_FAIL;
    }

    switch (opConfig)
    {
        case MXD_P29P09LN:
            for (i=0; i<MXD_NUM_LANES; i++)
            {
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_HOST_SIDE, (0xF005+i), 0x8030));
            }
            break;

        case MXD_P25LR:
        case MXD_P25LN:
        case MXD_R25L:
            if (pDev->use20G)
            {
                for (i = 0; i < MXD_NUM_LANES; i++)
                {
                    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF005+i), 0x8084));
                }
            }
            break;

        default:
            break;
    }

    return MXD_OK;
}

/*******************************************************************
 MXD_STATUS mxdTapConfig
   Tap Settings 
*******************************************************************/
MXD_STATUS mxdTapConfig
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig
)
{
    MXD_U16 i;

    if (!(host_or_line == MXD_HOST_SIDE || host_or_line == MXD_LINE_SIDE))
    {
        MXD_DBG_ERROR("mxdPerfConfig: host_or_line is invalid\n");
        return MXD_FAIL;
    }

    if (laneOffset == 0 && (host_or_line == MXD_LINE_SIDE))
    {
        switch (opConfig)
        {
            case MXD_P1X:
            case MXD_P1S:
            case MXD_P1P: 
            case MXD_R1:
            case MXD_P2_5X:
            case MXD_R2_5:
            case MXD_P5L: 
            case MXD_P5K:
            case MXD_R5:
            case MXD_P10LN:
            case MXD_P10KN:
            case MXD_P10KF:
            case MXD_P10LF:
            case MXD_R10L:
            case MXD_R10K:
            case MXD_R25L:
            case MXD_R25C:
            case MXD_R25K:
            case MXD_P40LN:
            case MXD_P40CN:
            case MXD_P40CF:
            case MXD_P40KN:
            case MXD_P40KF:
            case MXD_P40LF:
            case MXD_R40L:
            case MXD_R40C:
            case MXD_R40K:
            case MXD_P50LN:
            case MXD_P50CN:
            case MXD_P50CF:
            case MXD_P50KN:
            case MXD_P50KF:
            case MXD_P50LF:
            case MXD_P50MN:
            case MXD_P50MF:
            case MXD_P50MR:
            case MXD_P50BN:
            case MXD_P50BF:
            case MXD_P50BR:
            case MXD_P50JN:
            case MXD_P50JF:
            case MXD_P50JR:
            case MXD_P100LN:
            case MXD_P100LR:
            case MXD_P100CR:
            case MXD_P100KR:
            case MXD_P100KN:
            case MXD_R100L:
            case MXD_R100C:
            case MXD_R100K:
                ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, 0x0503, 0x003d, 0x9004));
                ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, 0x0503, 0x003d, 0x9800));
                ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, 0x0503, 0x003d, 0xa002));
                ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, 0x0503, 0x003d, 0xa800));
                ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, 0x0503, 0x003d, 0xb012));
                ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, 0x0503, 0x003d, 0xb800));
                break;

            case MXD_P25CN:
            case MXD_P25CF:
            case MXD_P25CR:
            case MXD_P25BN:
            case MXD_P25BF:
            case MXD_P25BR:
                ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, 0x0503, 0x003d, 0x9004));
                ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, 0x0503, 0x003d, 0x9800));
                ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, 0x0503, 0x003d, 0xa006));
                ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, 0x0503, 0x003d, 0xa800));
                ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, 0x0503, 0x003d, 0xb010));
                ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, 0x0503, 0x003d, 0xb800));
                break;

            case MXD_P25KN:
            case MXD_P25KF:
            case MXD_P25KR:
            case MXD_P25JN:
            case MXD_P25JF:
            case MXD_P25JR:
                ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, 0x0503, 0x003d, 0x9004));
                ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, 0x0503, 0x003d, 0x9800));
                ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, 0x0503, 0x003d, 0xa006));
                ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, 0x0503, 0x003d, 0xa804));
                ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, 0x0503, 0x003d, 0xb010));
                ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, 0x0503, 0x003d, 0xb800));
                break;

            case MXD_P25LN:
            case MXD_P25LF:
            case MXD_P25LR:
                ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, 0x0503, 0x003d, 0x9800));
                ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, 0x0503, 0x003d, 0xa809));
                ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, 0x0503, 0x003d, 0xb800));
                break;

            default:
                break;
        }
    }

    if (host_or_line == MXD_HOST_SIDE)
    {
        switch (opConfig)
        {
            case MXD_P1X:
            case MXD_P1S:
            case MXD_P1P: 
            case MXD_R1:
            case MXD_P2_5X:
            case MXD_R2_5:
            case MXD_P5L: 
            case MXD_P5K:
            case MXD_R5:
            case MXD_P10LF:
            case MXD_P10LN:
            case MXD_R10L:
            case MXD_R10K:
            case MXD_P25LN:
            case MXD_P25LF:
            case MXD_P25LR:
            case MXD_P25CN:
            case MXD_P25CF:
            case MXD_P25CR:
            case MXD_P25KN:
            case MXD_P25KF:
            case MXD_P25KR:
            case MXD_P25BN:
            case MXD_P25BF:
            case MXD_P25BR:
            case MXD_P25JN:
            case MXD_P25JF:
            case MXD_P25JR:
            case MXD_R25L:
            case MXD_R25C:
            case MXD_R25K:
                {
                    MXD_U16 interruptAddr = 0x0103+(laneOffset*0x100);

                    ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, interruptAddr, 0x003d, 0x9004));
                    ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, interruptAddr, 0x003d, 0xa002));
                    ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, interruptAddr, 0x003d, 0xb012));
                }
                break;

            case MXD_P10KF:
            case MXD_P10KN:
                {
                    MXD_U16 interruptAddr = 0x0103+(laneOffset*0x100);

                    ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, interruptAddr, 0x003d, 0x9002));
                    ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, interruptAddr, 0x003d, 0xa005));
                    ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, interruptAddr, 0x003d, 0xb012));
                }
                break;

            case MXD_P40CF:
            case MXD_P40CN:
                {
                    for (i=0; i<MXD_NUM_LANES; i++)
                    {
                        ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, (0x0103 + (i*0x100)), 0x003d, 0x9004));
                    }

                    for (i=0; i<MXD_NUM_LANES; i++)
                    {
                        ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, (0x0103 + (i*0x100)), 0x003d, 0xa006));
                    }

                    for (i=0; i<MXD_NUM_LANES; i++)
                    {
                        ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, (0x0103 + (i*0x100)), 0x003d, 0xb010));
                    }
                }
                break;

            case MXD_P40KN:
            case MXD_P40KF:
                {
                    for (i=0; i<MXD_NUM_LANES; i++)
                    {
                        ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, (0x0103 + (i*0x100)), 0x003d, 0x9002));
                    }

                    for (i=0; i<MXD_NUM_LANES; i++)
                    {
                        ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, (0x0103 + (i*0x100)), 0x003d, 0xa005));
                    }

                    for (i=0; i<MXD_NUM_LANES; i++)
                    {
                        ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, (0x0103 + (i*0x100)), 0x003d, 0xb012));
                    }
                }
                break;

            case MXD_P29P09LN:
            case MXD_P40LN:
            case MXD_P40LF:
            case MXD_R40L:
            case MXD_R40C:
            case MXD_R40K:
            case MXD_P50LN:
            case MXD_P50CN:
            case MXD_P50CF:
            case MXD_P50KN:
            case MXD_P50KF:
            case MXD_P50LF:
            case MXD_P50MN:
            case MXD_P50MF:
            case MXD_P50MR:
            case MXD_P50BN:
            case MXD_P50BF:
            case MXD_P50BR:
            case MXD_P50JN:
            case MXD_P50JF:
            case MXD_P50JR:
            case MXD_P100LN:
            case MXD_P100LR:
            case MXD_P100CR:
            case MXD_P100KR:
            case MXD_P100KN:
            case MXD_R100L:
            case MXD_R100C:
            case MXD_R100K:
                {
                    for (i=0; i<MXD_NUM_LANES; i++)
                    {
                        ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, (0x0103 + (i*0x100)), 0x003d, 0x9004));
                    }

                    for (i=0; i<MXD_NUM_LANES; i++)
                    {
                        ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, (0x0103 + (i*0x100)), 0x003d, 0xa002));
                    }

                    for (i=0; i<MXD_NUM_LANES; i++)
                    {
                        ATTEMPT(mxdSerdesIntWrite(pDev, mdioPort, (0x0103 + (i*0x100)), 0x003d, 0xb012));
                    }
                }
                break;

            default:
                break;
        }
    }
                                            
    return MXD_OK;
}

/*******************************************************************
 MXD_STATUS mxdSetFecConfig
   Set FEC Configurations
*******************************************************************/
MXD_STATUS mxdSetFecConfig
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_U16 fecType,
    IN MXD_OP_CONFIG opConfig
)
{
    MXD_U16 regOffset=0;
    MXD_BOOL isFECSet = MXD_FALSE;

    if (host_or_line == MXD_HOST_SIDE)
    {
        regOffset = 0x1000;
    }

    /* These OP modes requires special FEC handling */
    switch (opConfig)
    {
        case MXD_R10K:
        case MXD_R40C:
        case MXD_R40K:
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_ADV3_LINE+regOffset)+(laneOffset*0x200)), 14, 2, 0x01));
            isFECSet = MXD_TRUE;
            break;

        case MXD_R25C:
        case MXD_R25K:
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_ADV3_LINE+regOffset)+(laneOffset*0x200)), 14, 2, 0x01));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_LANE_CTRL2_LINE+regOffset)+(laneOffset*0x200)), 8, 4, 0x3));
            isFECSet = MXD_TRUE;
            break;

        case MXD_P25KR:
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_ADV3_LINE+regOffset)+(laneOffset*0x200)), 12, 2, 0x3));
            isFECSet = MXD_TRUE;
            break;

        case MXD_P10KF:
        case MXD_P40CF:
        case MXD_P40KF:
            /* Set both FEC Request and Ability */
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_ADV3_LINE+regOffset)+(laneOffset*0x200)), 14, 2, 0x3));
            isFECSet = MXD_TRUE;
            break;

        case MXD_P50BF:
        case MXD_P50JF:
        case MXD_P25BF:
        case MXD_P25JF:
            /* Set both FEC Request and Ability */
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_ADV3_LINE+regOffset)+(laneOffset*0x200)), 14, 2, 0x3));
            isFECSet = MXD_FALSE;
            break;

        case MXD_P10LF:
        case MXD_P25LF:
        case MXD_P25LR:
        case MXD_P25JN:
        case MXD_P29P09LN:
        case MXD_P40LN:
        case MXD_P40LF:
        case MXD_P40CN:
        case MXD_P40KN:
        case MXD_R40L:
        case MXD_P50LN:
        case MXD_P50CN:
        case MXD_P50MN:
        case MXD_P50MF:
        case MXD_P50MR:
        case MXD_P50LF:
        case MXD_P50CF:
        case MXD_P50KF:
        case MXD_P50JN:
        case MXD_P100LN:
        case MXD_P100LR:
        case MXD_P100CR:
        case MXD_P100KR:
        case MXD_P100KN:
        case MXD_R100L:
        case MXD_R100C:
        case MXD_R100K:
            /* No need to set FEC at 7.0012*/
            isFECSet = MXD_TRUE;
            break;

        default:
            /* MXD_DBG_INFO("mxdSetFecConfig: OP mode does not require special FEC handling\n"); */
            isFECSet = MXD_FALSE;
            break;
    }

    if (isFECSet)
    {
        /* If FEC is set in above cases, no need to proceed further. */
        return MXD_OK;
    }

    switch (fecType)
    {
        case MXD_FEC_NONE:
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_ADV3_LINE+regOffset)+(laneOffset*0x200)), 12, 2, 0x0));
            break;

        case MXD_KR_FEC:
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_ADV3_LINE+regOffset)+(laneOffset*0x200)), 12, 2, 0x2));
            break;

        case MXD_RS_FEC:
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_ADV3_LINE+regOffset)+(laneOffset*0x200)), 12, 2, 0x1));
            break;

        case MXD_FEC_BOTH:
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_ADV3_LINE+regOffset)+(laneOffset*0x200)), 12, 2, 0x3));
            break;

        case MXD_KR_FEC_CON:
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_LANE_CTRL2_LINE+regOffset)+(laneOffset*0x200)), 8, 4, 0xA));
            break;

        case MXD_RS_FEC_CON:
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_LANE_CTRL2_LINE+regOffset)+(laneOffset*0x200)), 8, 4, 0x5));
            break;

        case MXD_KR_FEC_IEEE:
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_ADV3_LINE+regOffset)+(laneOffset*0x200)), 12, 4, 0xE));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_LANE_CTRL2_LINE+regOffset)+(laneOffset*0x200)), 8, 4, 0xA));
            break;

        case MXD_RS_FEC_IEEE:
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_ADV3_LINE+regOffset)+(laneOffset*0x200)), 12, 2, 0x3));
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, ((MXD_AUTONEG_LANE_CTRL2_LINE+regOffset)+(laneOffset*0x200)), 8, 4, 0x5));
            break;

        default:
            MXD_DBG_ERROR("mxdSetFecConfig: Unsupported FEC type!\n");
            return MXD_FAIL;
            break;
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdGetPktGenRegOffset
    Get packet generator register address offset based on Mode speed and lane
*******************************************************************************/
MXD_STATUS mxdGetPktGenRegOffset
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U16 *regAddrOffset
)
{
    MXD_SPEED speed;
    MXD_PCS_TYPE mode;

    ATTEMPT(mxdGetModeSpeed(pDev, mdioPort, host_or_line, laneOffset, &speed, &mode));
    if (mode != MXD_PCS)
    {
        MXD_DBG_ERROR("mxdGetPktGenRegOffset: not a PCS mode\n");
        return MXD_FAIL;
    }

    if (laneOffset >= MXD_NUM_LANES)
    {
        MXD_DBG_ERROR("mxdGetPktGenRegOffset: incorrect lane offset: %u\n", (unsigned)laneOffset);
        return MXD_FAIL;
    }

    *regAddrOffset = 0;  /* for MXD_100GB speed */

    if ((speed == MXD_40GB) || (speed == MXD_50GB))
    {
        *regAddrOffset = PACKET_GEN_40G_OFFSET;
    }
    else if ((speed >= MXD_5GB) && (speed <= MXD_25GB))
    {
        *regAddrOffset = PACKET_GEN_25G_OFFSET+laneOffset*0x200;
    }
    else if (speed < MXD_5GB)
    {
        *regAddrOffset = PACKET_GEN_1G_OFFSET+laneOffset*0x200;
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdCheckFecLaneOffset
   Check if the laneOffset is valid to FEC
*******************************************************************************/
MXD_STATUS mxdCheckFecLaneOffset
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    IN MXD_U16  fecType
)
{
    MXD_SPEED speed;
    MXD_PCS_TYPE mode;

    ATTEMPT(mxdGetModeSpeed(pDev, mdioPort, host_or_line, laneOffset, &speed, &mode));
    if (mode != MXD_PCS)
    {
        MXD_DBG_ERROR("mxdCheckFecLaneOffset: not a PCS mode\n");
        return MXD_FAIL;
    }

    if (laneOffset >= MXD_NUM_LANES)
    {
        MXD_DBG_ERROR("mxdCheckFecLaneOffset: incorrect lane offset: %u\n", (unsigned)laneOffset);
        return MXD_FAIL;
    }

    if ((fecType == MXD_RS_FEC) || (fecType == MXD_RS_FEC_CON))
    {
        /* lane 0 is for all speeds; lane 1-3 are only for 25GB */
        if (!((laneOffset == 0) || (speed == MXD_25GB)))
        {
            MXD_DBG_ERROR("mxdCheckFecLaneOffset: incorrect lane offset for RS-FEC: %u\n", (unsigned)laneOffset);
            return MXD_FAIL;
        }
    }
    else if ((fecType == MXD_KR_FEC) || (fecType == MXD_KR_FEC_CON))
    {
        /* lane 0 is for all speeds; lane 1-3 are only for 10GB and 25GB */
        if (!((laneOffset == 0) || (speed == MXD_10GB) || (speed == MXD_25GB)))
        {
            MXD_DBG_ERROR("mxdCheckFecLaneOffset: incorrect lane offset for KR-FEC: %u\n", (unsigned)laneOffset);
            return MXD_FAIL;
        }
    }

    return MXD_OK;
}

/*******************************************************************
 MXD_STATUS mxdMappedSerdesIDs
   Mapped the Serdes ID to the matching Host and Line lanes
       Host LaneOffset   SerdesID
             0              1
             1              2
             2              3
             3              4
       Line LaneOffset   SerdesID
             0              5
             1              6
             2              7
             3              8
*******************************************************************/
MXD_STATUS mxdMappedSerdesIDs
(
    IN MXD_DEV_PTR pDev
)
{
    MXD_U16 i, laneOffset;

    for(i=0; i<MXD_NUM_INTERFACE; i++)
    {
        for(laneOffset=0; laneOffset<MXD_NUM_LANES; laneOffset++)
        {
            pDev->serdesID[i][laneOffset] = (laneOffset+1) + (i*4);
        }
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdSetDeepPCSLoopback
*******************************************************************************/
MXD_STATUS mxdSetDeepPCSLoopback
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 laneOffset,
    IN MXD_U16 host_or_line,
    IN MXD_U16 gearboxMode,
    IN MXD_U16 autoNeg,
    IN MXD_SPEED Speed,
    IN MXD_U16 regAddrPCS,
    IN MXD_U16 loopbackBit
)
{
    MXD_U16 temp;
    MXD_OP_CONFIG lineMode;
    
    lineMode = pDev->lineConfig[laneOffset].opConfig;

    if ((loopbackBit == 1) && (autoNeg == 1))
    {
        /* Disable auto-neg */
        if (host_or_line == MXD_HOST_SIDE)
        {
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_CNTL_HOST+(laneOffset*0x200)), 12, 1, 0));
        }
        else
        {
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_CNTL_LINE+(laneOffset*0x200)), 12, 1, 0));
        }

        if ((host_or_line == MXD_LINE_SIDE) && (lineMode >= MXD_P25BCN) && (lineMode <= MXD_P25JKR))
        {
            /* for Grouped mode only */
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, MXD_IF_MODE_SEL_P0, 0x8024)); /* set to 25G */
        }        
        else
        {
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, (MXD_IF_MODE_SEL_P0+laneOffset), &temp));
            temp &= ~0x0010;
            temp |= 0x8000;
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, (MXD_IF_MODE_SEL_P0+laneOffset), temp));
        }
    }

    if (loopbackBit == 0)
    {
        if (Speed == MXD_100GB)
        {
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF070, 0x2001));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF06E, 0x0FC0));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF0D8, 0xF800));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF0CF, 0xC000));
        }
        else if (Speed >= MXD_40GB)
        {
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF072, 0x81FF));
        }
        else if (Speed >= MXD_5GB)
        {
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF0C4, 0x003F));
        }
    }

    /* BEFORE */

    /* Turn Deep Line side Loopback on/off */
    ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, regAddrPCS, 14, 1, loopbackBit));

    /* AFTER */
    if (loopbackBit == 0)
    {
        if (Speed == MXD_100GB)
        {
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, MXD_IF_MODE_SEL_P0, 15, 1, 1));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF070, 0x0000));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF06E, 0x0000));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF0D8, 0x0000));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF0CF, 0x0000));
        }
        else if (Speed >= MXD_40GB)
        {
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, MXD_IF_MODE_SEL_P0, 15, 1, 1));
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF072, 0x0100));
        }
        else if (Speed >= MXD_5GB)
        {
            /* Port 0, laneOffset, software reset */
            if ((host_or_line == MXD_LINE_SIDE) && (lineMode >= MXD_P25BCN) && (lineMode <= MXD_P25JKR))
            {
                /* for Grouped mode only */
                ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, MXD_IF_MODE_SEL_P0, 0x8000)); /* set to 25G */
            }        
            else
            {
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, (MXD_IF_MODE_SEL_P0+laneOffset), 15, 1, 1));
            }
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF0C4, 0x0000));
        }

        if (autoNeg == 1)
        {
            /* Enable auto-neg */
            if (host_or_line == MXD_HOST_SIDE)
            {
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_CNTL_HOST+(laneOffset*0x200)), 12, 1, 1));
            }
            else
            {
                ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, (MXD_AUTONEG_CNTL_LINE+(laneOffset*0x200)), 12, 1, 1));
            }
            ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, host_or_line, (MXD_IF_MODE_SEL_P0+laneOffset), &temp));
            temp |= 0x8010;
            ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line,(MXD_IF_MODE_SEL_P0+laneOffset), temp));
        }
    }

    if (gearboxMode == 1)
    {
        /*Disable/Enable Resetting FIFO based on other side PCS RX reset*/
        if (host_or_line == MXD_HOST_SIDE)
        {
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0x904D, 15, 1, loopbackBit));
        }
        else
        {
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xA04D, 15, 1, loopbackBit));
        }
    }

    return MXD_OK;
}

/*******************************************************************************
 MXD_STATUS mxdSetDeepPMALoopback100G
*******************************************************************************/
MXD_STATUS mxdSetDeepPMALoopback100G
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 autoNeg,
    IN MXD_U16 enableLoopback
)
{
    MXD_U16 regOffset = 0;

    if (host_or_line == MXD_LINE_SIDE)
    {
        regOffset = 0x0000;
    }
    else if (host_or_line == MXD_HOST_SIDE)
    {
        regOffset = 0x1000;
    }

    if (enableLoopback == MXD_ENABLE)
    {
        /*Enable PCS deep loopback */
        ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, 0x0000 + regOffset, 0, 1, enableLoopback));
        if (autoNeg == 1)
        {
            /* Enable overridding nonce match (default override value is 0x0) */
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, 0x8001 + regOffset, 10, 1, 1));
        }
    }
    else if (enableLoopback == MXD_DISABLE)
    {
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF070, 0x2001));
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF06E, 0x0FC0));
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF0D8, 0xF800));
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF0CF, 0xC000));

        /* Disable PMA deep loopback (Tx to Rx) */
        ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_LINE_PMA, 0x0000 + regOffset, 0, 1, enableLoopback));

        ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF000, 15, 1, 1));
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF070, 0x0000));
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF06E, 0x0000));
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF0D8, 0x0000));
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF0CF, 0x0000));

        if (autoNeg == 1)
        {
            /* Disable overriding nonce match */
            ATTEMPT(mxdHwSetPhyRegField(pDev, mdioPort, MXD_AUTONEG, 0x8001 + regOffset, 10, 1, 0));
        }

    }

    return MXD_OK;
}

