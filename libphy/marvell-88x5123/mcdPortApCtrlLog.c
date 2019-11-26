/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
*******************************************************************************/
/**
********************************************************************************
* @file mcdPortApCtrlLog.c
*/
#include "mcdApiTypes.h"
#include "mcdAPI.h"
#include "mcdUtils.h"
#include "mcdHwCntl.h"
#include "mcdInternalIpcDefs.h"
#include "mcdInternalIpcApis.h"
#include "mcdApiRegs.h"
#include "mcdInternalInitApApis.h"
#include "mcdAPIInternal.h"
#include "mcdInternalPortApInitIf.h"
#include "mcdPortCtrlApLogDefs.h"
#include "mcdInternalCtrlApInitIf.h"

/**************************** Pre-Declaration ********************************************/
void mcdApPortCtrlDebugInfoShowEntry(MCD_U32 port, MCD_U32 timestamp, MCD_U32 logInfo, MCD_BOOL apCpssLogEnable);

/**************************** Definition **************************************/
#define MCD_FW_HWS_LOG_SIZE    (12)
#define MCD_PORT_CTRL_LOG_SIZE (416)

#define MCD_AP_PORT_SM_MAX_STATE  (7)
#define MCD_SPV_MAX_STATE         (3)
#define MCD_PORT_MNG_MAX_STATE    (2)
#define MCD_PORT_SM_MAX_STATUS    (30)
#define MCD_PORT_SM_MAX_STATE     (5)
#define MCD_AP_PORT_MAX_STATUS    (20)
#define MCD_GEN_LINK_DOWN      (0x0)
#define MCD_GEN_LINK_UP        (0x1)
#define MCD_GEN_TUNE_FAIL      (0x0)
#define MCD_GEN_TUNE_PASS      (0x1)

/**************************** Globals *****************************************/
/* Port Log Control Parameters */
MCD_U32 mcdFwAPLogOffsetAddr;
MCD_U32 mcdFwAPLogCountOffsetAddr;
MCD_U32 mcdFwAPLogPointerOffsetAddr;
MCD_U32 mcdFwAPLogResetOffsetAddr;
MCD_U32 mcdFwAPLogPointer;

/* Port Log Control Parameters */
MCD_U32 mcdFwLogOffsetAddr;
MCD_U32 mcdFwLogCountOffsetAddr;
MCD_U32 mcdFwLogPointerOffsetAddr;
MCD_U32 mcdFwLogResetOffsetAddr;
MCD_U32 mcdFwLogPointer;
MCD_U32 mcdFwPollingDbAddr;

/* Port Log */
MCD_PORT_CTRL_LOG_ENTRY portLog[MCD_PORT_CTRL_LOG_SIZE];
/* FW Hws Log */
MCD_LOG_ENTRY hwsLog[MCD_FW_HWS_LOG_SIZE];
typedef enum
{
    MCD_PORT_CTRL_AP_REG_CFG_0                                   = 1,
    MCD_PORT_CTRL_AP_REG_CFG_1                                   = 2,
    MCD_PORT_CTRL_AP_REG_ST_0                                    = 3,
    MCD_PORT_CTRL_AP_INT_REG_802_3_AP_CTRL                       = 4,
    MCD_PORT_CTRL_AP_INT_REG_802_3_AP_ST                         = 5,
    MCD_PORT_CTRL_AP_INT_REG_802_3_AP_ADV_REG_1                  = 6,
    MCD_PORT_CTRL_AP_INT_REG_802_3_AP_ADV_REG_2                  = 7,
    MCD_PORT_CTRL_AP_INT_REG_802_3_AP_ADV_REG_3                  = 8,
    MCD_PORT_CTRL_AP_INT_REG_802_3_LP_BASE_ABILITY_REG_1         = 9,
    MCD_PORT_CTRL_AP_INT_REG_802_3_LP_BASE_ABILITY_REG_2         = 10,
    MCD_PORT_CTRL_AP_INT_REG_802_3_LP_BASE_ABILITY_REG_3         = 11,
    MCD_PORT_CTRL_AP_INT_REG_ANEG_CTRL_0                         = 12,
    MCD_PORT_CTRL_AP_INT_REG_ANEG_CTRL_1                         = 13,
    MCD_PORT_CTRL_AP_INT_REG_802_3_NEXT_PG_TX_REG                = 14,
    MCD_PORT_CTRL_AP_INT_REG_802_3_NEXT_PG_TX_CODE_0_15          = 15,
    MCD_PORT_CTRL_AP_INT_REG_802_3_NEXT_PG_TX_CODE_16_31         = 16,
    MCD_PORT_CTRL_AP_INT_REG_802_3_LP_NEXT_PG_ABILITY_REG        = 17,
    MCD_PORT_CTRL_AP_INT_REG_802_3_LP_NEXT_PG_ABILITY_CODE_0_15  = 18,
    MCD_PORT_CTRL_AP_INT_REG_802_3_LP_NEXT_PG_ABILITY_CODE_16_31 = 19,
    MCD_PORT_CTRL_AP_INT_REG_802_3_BP_ETH_ST_REG                 = 20,
    MCD_PORT_CTRL_AP_INT_REG_802_3_LP_ADV_REG                    = 21,
    MCD_PORT_CTRL_AP_REG_ST_1                                    = 22,
    MCD_PORT_CTRL_MAX_AP_REGS

}MCD_PORT_CTRL_AP_REGS;

/* AP Registers description */
static char *regType[MCD_PORT_CTRL_MAX_AP_REGS] =
{
    "",   /* the values in MV_PORT_CTRL_AP_REGS enum started from 1 */
    /* [PORT_CTRL_AP_REG_CFG_0] */                                   "Cfg-0",
    /* [PORT_CTRL_AP_REG_CFG_1] */                                   "Cfg-1",
    /* [PORT_CTRL_AP_REG_ST_0] */                                    "St-0",
    /* [PORT_CTRL_AP_INT_REG_802_3_AP_CTRL] */                       "Ctrl",
    /* [PORT_CTRL_AP_INT_REG_802_3_AP_ST] */                         "St",
    /* [PORT_CTRL_AP_INT_REG_802_3_AP_ADV_REG_1] */                  "AdvReg1",
    /* [PORT_CTRL_AP_INT_REG_802_3_AP_ADV_REG_2] */                  "AdvReg2",
    /* [PORT_CTRL_AP_INT_REG_802_3_AP_ADV_REG_3] */                  "AdvReg3",
    /* [PORT_CTRL_AP_INT_REG_802_3_LP_BASE_ABILITY_REG_1] */         "LpReg1",
    /* [PORT_CTRL_AP_INT_REG_802_3_LP_BASE_ABILITY_REG_2] */         "LpReg2",
    /* [PORT_CTRL_AP_INT_REG_802_3_LP_BASE_ABILITY_REG_3] */         "LpReg3",
    /* [PORT_CTRL_AP_INT_REG_ANEG_CTRL_0] */                         "Aneg0",
    /* [PORT_CTRL_AP_INT_REG_ANEG_CTRL_1] */                         "Aneg1",
    /* [PORT_CTRL_AP_INT_REG_802_3_NEXT_PG_TX_REG] */                "NxtPg",
    /* [PORT_CTRL_AP_INT_REG_802_3_NEXT_PG_TX_CODE_0_15] */          "NxtPg-0",
    /* [PORT_CTRL_AP_INT_REG_802_3_NEXT_PG_TX_CODE_16_31] */         "NxtPg-16",
    /* [PORT_CTRL_AP_INT_REG_802_3_LP_NEXT_PG_ABILITY_REG] */        "LpNxtPg",
    /* [PORT_CTRL_AP_INT_REG_802_3_LP_NEXT_PG_ABILITY_CODE_0_15] */  "LpNxtPg-0",
    /* [PORT_CTRL_AP_INT_REG_802_3_LP_NEXT_PG_ABILITY_CODE_16_31] */ "LpNxtPg-16",
    /* [PORT_CTRL_AP_INT_REG_802_3_BP_ETH_ST_REG] */                 "BpSt",
    /* [PORT_CTRL_AP_INT_REG_802_3_LP_ADV_REG] */                    "LpAdv",
    /* [PORT_CTRL_AP_REG_ST_1] */                                    "St-1"
};

/* Message Type description */
static char *msgType[MCD_IPC_LAST_CTRL_MSG_TYPE] =
{
   /* [MV_HWS_IPC_PORT_AP_ENABLE_MSG] */                    "AP Enable",
   /* [MV_HWS_IPC_PORT_AP_DISABLE_MSG] */                   "AP Disable",
   /* [MV_HWS_IPC_PORT_AP_SYS_CFG_VALID_MSG] */             "AP Sys Cfg",
   /* [MV_HWS_IPC_PORT_AP_CFG_GET_MSG] */                   "AP Cfg Get",
   /* [MV_HWS_IPC_PORT_AP_STATUS_MSG] */                    "AP Status",
   /* [MV_HWS_IPC_PORT_AP_STATS_MSG] */                     "AP Stats",
   /* [MV_HWS_IPC_PORT_AP_STATS_RESET_MSG] */               "AP Reset",
   /* [MV_HWS_IPC_PORT_AP_INTROP_GET_MSG] */                "AP Introp Get",
   /* [MV_HWS_IPC_PORT_AP_INTROP_SET_MSG] */                "AP Introp Set",
   /* [MV_HWS_IPC_PORT_AP_DEBUG_GET_MSG] */                 "AP Debug",
   /* [MV_HWS_IPC_PORT_PARAMS_MSG] */                       "Params Set",
   /* [MV_HWS_IPC_PORT_AVAGO_SERDES_INIT_MSG] */            "Avago Serdes Init",
   /* [MV_HWS_IPC_PORT_AVAGO_GUI_SET_MSG] */                "Avago GUI Set",
   /* [MV_HWS_IPC_PORT_AVAGO_SERDES_RESET_DATA_MSG]  */     "Avago Appl Data Reset",
   /* [MV_HWS_IPC_VOS_OVERRIDE_PARAMS_DATA_MSG]  */         "VOS Override MSG",
   /* [MV_HWS_IPC_VOS_OVERRIDE_MODE_SET_MSG]  */            "VOS Override Mode Set",
   /* [MV_HWS_IPC_NOOP_MSG] */                              "Noop",
   /* [MV_HWS_IPC_PORT_INIT_MSG] */                         "Init",
   /* [MV_HWS_IPC_PORT_RESET_MSG] */                        "Reset",
   /* [MV_HWS_IPC_PORT_RESET_EXT_MSG] */                    "Reset Ext",
   /* [MV_HWS_IPC_HWS_LOG_GET_MSG] */                       "Hws LOG Get",
   /* [MV_HWS_IPC_PORT_AUTO_TUNE_SET_EXT_MSG] */            "Auto Tune Set",
   /* [MV_HWS_IPC_PORT_AUTO_TUNE_STOP_MSG] */               "Auto Tune Stop",
   /* [MV_HWS_IPC_PORT_AUTO_TUNE_STATE_CHK_MSG] */          "Auto Tune Check",
   /* [MV_HWS_IPC_PORT_LINK_STATUS_GET_MSG] */              "Link Status",
   /* [MV_HWS_IPC_PORT_FEC_CONFIG_GET_MSG] */               "Fec Get",
   /* [MV_HWS_IPC_PORT_TX_ENABLE_GET_MSG] */                "Tx Enable Get",
   /* [MV_HWS_IPC_PORT_SERDES_RESET_MSG] */                 "Serdes Reset",
   /* [MV_HWS_IPC_PORT_POLARITY_SET_MSG] */                 "Polarity",
   /* [MV_HWS_IPC_PORT_FEC_CONFIG_MSG] */                   "Fec Config",
   /* [MV_HWS_IPC_PORT_TX_ENABLE_MSG] */                    "Tx Enable",
   /* [MV_HWS_IPC_PORT_SIGNAL_DETECT_GET_MSG] */            "Signal Detect",
   /* [MV_HWS_IPC_PORT_CDR_LOCK_STATUS_GET_MSG] */          "CDR Lock Status",
   /* [MV_HWS_IPC_PORT_LOOPBACK_SET_MSG] */                 "Loopback",
   /* [MV_HWS_IPC_PORT_LOOPBACK_STATUS_GET_MSG] */          "Loopback Status",
   /* [MV_HWS_IPC_PORT_PPM_SET_MSG] */                      "PPM Set",
   /* [MV_HWS_IPC_PORT_PPM_GET_MSG] */                      "PPM Get",
   /* [MV_HWS_IPC_PORT_IF_GET_MSG] */                       "If Get",
   /* [MV_HWS_IPC_PORT_SERDES_MANUAL_RX_CONFIG_MSG] */      "Serdes Man Rx",
   /* [MV_HWS_IPC_PORT_SERDES_MANUAL_TX_CONFIG_MSG] */      "Serdes Man Tx",
   /* [MV_HWS_IPC_PORT_PCS_ACTIVE_STATUS_GET_CONFIG_MSG] */ "PCS Act Status"
   /* [MV_HWS_IPC_PORT_FC_STATE_SET_MSG]  */                "FC State Set",
};

/* Port Type description */
static char *portType[] =
{
    "Reg",
    "AP"
};

/* Supervisour state description */
static char *superState[] =
{
    "High Pri Msg",
    "Low Pri Msg",
    "Delay"
};

/* Port Management state description */
static char *portMngState[] =
{
    "Msg Process",
    "Delay"
};

/* Port State machine state description */
static char *portMngSmState[] =
{
    "Idle",
    "Serdes Config",
    "Serdes Training",
    "Mac/Pcs Config",
    "Active",
    "Delete"
};

/* Port State machine status description */
static char *portMngSmStatus[] =
{
    " ",
    "Start Execute",
    "Serdes Config In Progress",
    "Serdes Config Success",
    "Serdes Config Failure",
    "Serdes Training In Progress",
    "Serdes Training Success",
    "Serdes Training Failure",
    "Serdes Training Config Failure",
    "Serdes Training End Wait for Ack",
    "Mac/Pcs Config In Progress",
    "Mac/Pcs Config Success",
    "Mac/Pcs Config Failure",
    "Delete In Progress",
    "Delete Success",
    "Delete Failure",
    "FEC Config In Progress",
    "FEC Config Success",
    "FEC Config Failure",
    "FC State Set In Progress",
    "FC State Set Success",
    "FC State Set Failure",
    "Serdes Training Not Ready",
    "Serdes Polarity Set In Progress",
    "Serdes Polarity Set Success",
    "Serdes Polarity Set Failure",
    "Serdes Adatprive Training Start Fail",
    "Serdes Enhance Tune Lite Fail",
    "Serdes Enhance Tune Lite In Progress",
    "Serdes Training Not Completed"

};

/* AP HCD Found description */
static char* apPortMngHcdFound[] =
{
    "Not Found",
    "Found"
};

/* AP HCD Tyoe description */
static char* apPortMngHcdType[] =
{
    "1000Base_KX  ",
    "10GBase_KX4  ",
    "10GBase_R    ",
    "25GBASE_KR_S ",
    "25GBASE_KR   ",
    "40GBase_R    ",
    "40GBASE_CR4  ",
    "100GBASE_CR10",
    "100GBASE_KP4 ",
    "100GBASE_KR4 ",
    "100GBASE_CR4 ",
    "25GBASE_KR_CONSORTIUM ",
    "25GBASE_CR_CONSORTIUM ",
    "50GBASE_KR2_CONSORTIUM ",
    "50GBASE_CR2_CONSORTIUM ",

};

/* AP General filed description */
static char* apPortMngGen[] =
{
    "Off",
    "On"
};

/* AP Port State machine description */
char *mcdApPortMngSmState[] =
{
    "Idle",
    "Init",
    "Tx Disable",
    "Resolution",
    "Active",
    "Delete",
    "Ap Disable In Progress"
};

/* AP Port State machine status description */
char *mcdApPortMngSmStatus[] =
{
    "Start Execute",
    "Serdes Init Failure",
    "Init Success",
    "Tx Disable In Progress",
    "Tx Disable Failure",
    "Tx Disable Success",
    "Resolution In Progress",
    "Parallel Detect Resolution In Progress",
    "Parallel Detect Resolution Failure",
    "AP Resolution In Progress",
    "AP No Resolution",
    "AP Resolution Timer Failure",
    "AP Resolution Max Interval Failure",
    "AP Resolution Success",
    "Link Check Start",
    "Link Check Validate",
    "Link Check Failure",
    "Link Check Success",
    "Delete In Progress",
    "Delete Success",
    "Unknown HCD Found"
};
char *mcdPollingSmStatus[] =
{
    "POLLING_PORT_LINK_CHECK_STAGE_FAILED",
    "POLLING_PORT_LINK_CHECK_STAGE_START",
    "POLLING_PORT_LINK_CHECK_STAGE_LINK_LOST_CLEARED",
    "POLLING_PORT_LINK_CHECK_STAGE_SIGNAL_ON",
    "POLLING_PORT_LINK_CHECK_STAGE_SIGNAL_OFF",
    "POLLING_PORT_LINK_CHECK_STAGE_PCS_ALIVE_ON",
    "POLLING_PORT_LINK_CHECK_STAGE_PCS_ALIVE_OFF",
    "POLLING_PORT_LINK_CHECK_STAGE_EYE_ON",
    "POLLING_PORT_LINK_CHECK_STAGE_EYE_OFF",
    "POLLING_PORT_LINK_CHECK_STAGE_LINK_LOST_ON",
    "POLLING_PORT_LINK_CHECK_STAGE_LINK_LOST_OFF",
    "POLLING_PORT_LINK_CHECK_STAGE_TRAINING_NEEDED",
    "POLLING_PORT_LINK_CHECK_STAGE_STABLE_ON",
    "POLLING_PORT_LINK_CHECK_STAGE_LAST"

};

/**
* @internal mcdApPortCtrlDebugParamsSet function
* @endinternal
*
* @brief   Set AP debug information
*
* @param[in] apFwLogBaseAddr          - AP Firmware Real-time log base address
* @param[in] apFwLogCountAddr         - AP Firmware Real-time log count address
* @param[in] apFwLogPointerAddr       - AP Firmware Real-time log pointer address
* @param[in] apFwLogResetAddr         - AP Firmware Real-time log reset address
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
void mcdApPortCtrlDebugParamsSet
(
    MCD_U32 apFwLogBaseAddr,
    MCD_U32 apFwLogCountAddr,
    MCD_U32 apFwLogPointerAddr,
    MCD_U32 apFwLogResetAddr
)
{
    mcdFwAPLogOffsetAddr        = apFwLogBaseAddr;
    mcdFwAPLogCountOffsetAddr   = apFwLogCountAddr;
    mcdFwAPLogPointerOffsetAddr = apFwLogPointerAddr;
    mcdFwAPLogResetOffsetAddr   = apFwLogResetAddr;
    mcdFwAPLogPointer           = 0;
}

/**
* @internal mcdLogParamsSet function
* @endinternal
*
* @brief   Set Hws log information
*
* @param[in] fwLogBaseAddr            - Firmware HWS Real-time log base address
* @param[in] fwLogCountAddr           - Firmware HWS Real-time log count address
* @param[in] fwLogPointerAddr         - Firmware HWS Real-time log pointer address
* @param[in] fwLogResetAddr           - Firmware HWS Real-time log reset address
* @param[in] fwPollingDbAddr          - Firmware HWS Real-time polling DB address
*                                       None
*/
void mcdLogParamsSet
(
    MCD_U32 fwLogBaseAddr,
    MCD_U32 fwLogCountAddr,
    MCD_U32 fwLogPointerAddr,
    MCD_U32 fwLogResetAddr,
    MCD_U32 fwPollingDbAddr
)
{
    mcdFwLogOffsetAddr        = fwLogBaseAddr;
    mcdFwLogCountOffsetAddr   = fwLogCountAddr;
    mcdFwLogPointerOffsetAddr = fwLogPointerAddr;
    mcdFwLogResetOffsetAddr   = fwLogResetAddr;
    mcdFwLogPointer           = 0;
    mcdFwPollingDbAddr        = fwPollingDbAddr;
}
/**
* @internal mcdApConvertHdc2Vec function
* @endinternal
*
* @brief   convert HCD speed resolution to AP mode vector
*/
MCD_U16 mcdApConvertHdc2Vec(MCD_AP_PORT_MODE apPortMode)
{
    switch (apPortMode)
    {
       case MCD_Port_1000Base_KX:
           return MCD_NEG_1000KX;
       case MCD_Port_10GBase_R:
           return MCD_NEG_10KR;
       case MCD_Port_25GBASE_KR_S:
           return MCD_NEG_25KRCS;
       case MCD_Port_25GBASE_KR:
           return MCD_NEG_25KCR;
       case MCD_Port_40GBase_R:
           return MCD_NEG_40KR4;
       case MCD_Port_40GBASE_CR4:
           return MCD_NEG_40CR4;
       case MCD_Port_100GBASE_CR10:
           return MCD_NEG_100CR10;
       case MCD_Port_100GBASE_KP4:
           return MCD_NEG_100KP4;
       case MCD_Port_100GBASE_KR4:
           return MCD_NEG_100KR4;
       case MCD_Port_100GBASE_CR4:
           return MCD_NEG_100CR4;
       case MCD_Port_25GBASE_KR1_CONSORTIUM:
           return MCD_NEG_25KR_CONSORTIUM;
       case MCD_Port_25GBASE_CR1_CONSORTIUM:
           return MCD_NEG_25CR_CONSORTIUM;
       case MCD_Port_50GBASE_KR2_CONSORTIUM:
           return MCD_NEG_50KR_CONSORTIUM;
       case MCD_Port_50GBASE_CR2_CONSORTIUM:
           return MCD_NEG_50CR_CONSORTIUM;
       default:
           return MCD_NEG_NONE;
    }
}
/**
* @internal mcdApConvertPortMode function
* @endinternal
*
*/
MCD_OP_MODE mcdApConvertPortMode
(
    MCD_AP_PORT_MODE apPortMode
)
{
    switch (apPortMode)
    {
    case MCD_Port_1000Base_KX:      return MCD_MODE_P1;
    case MCD_Port_10GBase_R:        return MCD_MODE_P10L;
    case MCD_Port_40GBase_R:        return MCD_MODE_P40L;
    case MCD_Port_40GBASE_CR4:      return MCD_MODE_P40C;
    case MCD_Port_100GBASE_KP4:     return MCD_MODE_P100L;
    case MCD_Port_100GBASE_KR4:     return MCD_MODE_P100L;
    case MCD_Port_100GBASE_CR4:     return MCD_MODE_P100C;
    case MCD_Port_25GBASE_KR_S:     return MCD_MODE_P25S;
    case MCD_Port_25GBASE_KR:       return MCD_MODE_P25L;
    case MCD_Port_25GBASE_KR1_CONSORTIUM: return MCD_MODE_P25L;
    case MCD_Port_25GBASE_CR1_CONSORTIUM: return MCD_MODE_P25L;
    case MCD_Port_50GBASE_KR2_CONSORTIUM: return MCD_MODE_P50R2L;
    case MCD_Port_50GBASE_CR2_CONSORTIUM: return MCD_MODE_P50R2L;

    default:               return     MCD_MODE_UNKNOWN;
    }
}
/**
* @internal mcdArbSmStateDesc function
* @endinternal
*
* @brief   Print AP ARB State machine status description
*/
void mcdArbSmStateDesc(MCD_U32 mask)
{


    if (mask != 0)
    {
        if      (mask & MCD_ST_AN_ENABLE)   MCD_SHOW("ARB Status AN_ENABLE\n");
        else if (mask & MCD_ST_TX_DISABLE)  MCD_SHOW("ARB Status TX_DISABLE\n");
        else if (mask & MCD_ST_LINK_STAT_CK)MCD_SHOW("ARB Status LINK_STATE_CHECK\n");
        else if (mask & MCD_ST_PARALLEL_FLT)MCD_SHOW("ARB Status PARALLEL_FLT\n");
        else if (mask & MCD_ST_ABILITY_DET) MCD_SHOW("ARB Status ABILITY_DET\n");
        else if (mask & MCD_ST_ACK_DETECT)  MCD_SHOW("ARB Status ST_ACK_DETECT\n");
        else if (mask & MCD_ST_COMPLETE_ACK)MCD_SHOW("ARB Status ST_COMPLETE_ACK\n");
        else if (mask & MCD_ST_NP_WAIT)     MCD_SHOW("ARB Status ST_NP_WAIT\n");
        else if (mask & MCD_ST_AN_GOOD_CK)  MCD_SHOW("ARB Status AN_GOOD_CK\n");
        else if (mask & MCD_ST_AN_GOOD)     MCD_SHOW("ARB Status AN_GOOD\n");
        else if (mask & MCD_ST_SERDES_WAIT) MCD_SHOW("ARB Status SERDES WAIT\n");
    }
    else
    {
       MCD_SHOW("\n");
    }

}
/**
* @internal mcdApPortCtrlStatusShow function
* @endinternal
*
* @brief   Print AP port status information stored in system.
*
* @param[in] pDev
* @param[in] apPortNum                - AP port number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdApPortCtrlStatusShow
(
    MCD_DEV_PTR             pDev,
    MCD_U32  apPortNum
)
{
    MCD_AP_PORT_STATUS apStatus;

    mcdMemSet (&apStatus, 0 , sizeof(MCD_AP_PORT_STATUS));

    ATTEMPT(mcdApPortCtrlStatusGet(pDev, apPortNum, &apStatus));

    MCD_SHOW("======== AP Port %d, Lane %d info ========\n", apPortNum, apStatus.apLaneNum);
    MCD_SHOW("AP Port State           - %s\n", mcdApPortMngSmState[apStatus.smState]);
    MCD_SHOW("AP Port Status          - %s\n", mcdApPortMngSmStatus[apStatus.smStatus]);
    MCD_SHOW("AP Port ARB State       - ");
    switch (apStatus.arbStatus)
    {
    case MCD_ST_AN_ENABLE:   MCD_SHOW("ST_AN_ENABLE\n");    break;
    case MCD_ST_TX_DISABLE:  MCD_SHOW("ST_TX_DISABLE\n");   break;
    case MCD_ST_LINK_STAT_CK:MCD_SHOW("ST_LINK_STAT_CK\n"); break;
    case MCD_ST_PARALLEL_FLT:MCD_SHOW("ST_PARALLEL_FLT\n"); break;
    case MCD_ST_ABILITY_DET: MCD_SHOW("ST_ABILITY_DET\n");  break;
    case MCD_ST_ACK_DETECT:  MCD_SHOW("ST_ACK_DETECT\n");   break;
    case MCD_ST_COMPLETE_ACK:MCD_SHOW("ST_COMPLETE_ACK\n"); break;
    case MCD_ST_NP_WAIT:     MCD_SHOW("ST_NP_WAIT\n");      break;
    case MCD_ST_AN_GOOD_CK:  MCD_SHOW("ST_AN_GOOD_CK\n");   break;
    case MCD_ST_AN_GOOD:     MCD_SHOW("ST_AN_GOOD\n");      break;
    case MCD_ST_SERDES_WAIT: MCD_SHOW("ST_SERDES_WAIT\n");  break;
    default:             MCD_SHOW("Unknown\n");         break;
    }

   MCD_SHOW("AP Port HCD             - %s\n", (apStatus.hcdResult.hcdFound) ? ("Found") : ("Not Found."));
   MCD_SHOW("AP Port HCD Type        - ");

    switch (apStatus.postApPortMode)
    {
    case   MCD_Port_1000Base_KX  :  MCD_SHOW("1000Base_KX  \n");break;
    case   MCD_Port_10GBase_KX4  :  MCD_SHOW("10GBase_KX4  \n");break;
    case   MCD_Port_10GBase_R    :  MCD_SHOW("10GBase_R    \n");break;
    case   MCD_Port_40GBase_R    :  MCD_SHOW("40GBase_R    \n");break;
    case   MCD_Port_40GBASE_CR4  :  MCD_SHOW("40GBASE_CR4  \n");break;
    case   MCD_Port_100GBASE_CR10:  MCD_SHOW("100GBASE_CR10\n");break;
    case   MCD_Port_100GBASE_KP4 :  MCD_SHOW("100GBASE_KP4 \n");break;
    case   MCD_Port_100GBASE_KR4 :  MCD_SHOW("100GBASE_KR4 \n");break;
    case   MCD_Port_100GBASE_CR4 :  MCD_SHOW("100GBASE_CR4 \n");break;
    case   MCD_Port_25GBASE_KR_S :  MCD_SHOW("25GBASE_KR_S \n");break;
    case   MCD_Port_25GBASE_KR   :  MCD_SHOW("25GBASE_KR   \n");break;
    default:MCD_SHOW("Unknown\n");     break;
    }

   MCD_SHOW("AP Port HCD FEC Result  - %d\n", pDev->apRes[apPortNum].hcdFec);
   MCD_SHOW("AP Port HCD FC Rx Pause - %s\n", (apStatus.hcdResult.hcdFcRxPauseEn) ? ("FC Rx enabled") : ("FC Rx disabled"));
   MCD_SHOW("AP Port HCD FC Tx Pause - %s\n", (apStatus.hcdResult.hcdFcTxPauseEn) ? ("FC Tx enabled") : ("FC Tx disabled"));
   MCD_SHOW("AP Port HCD Link Status - %s\n", (apStatus.hcdResult.hcdLinkStatus)  ? ("Link Up") : ("Link Down"));

    return MCD_OK;
}

/**
* @internal mcdApPortCtrlStatsShow function
* @endinternal
*
* @brief   Print AP port statistics information stored in system
*
* @param[in] pDev
* @param[in] apPortNum                - AP port number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdApPortCtrlStatsShow
(
    MCD_DEV_PTR             pDev,
    MCD_U32                 apPortNum
)
{
    MCD_AP_PORT_STATS apStats;

    ATTEMPT(mcdApPortCtrlStatsGet(pDev, apPortNum, &apStats));

   MCD_SHOW("======== AP Port %d stats ========\n", apPortNum);
   MCD_SHOW("Tx Disable cnt        %08d\n", apStats.txDisCnt);
   MCD_SHOW("Ability check cnt     %08d\n", apStats.abilityCnt);
   MCD_SHOW("Resolution Detect cnt %08d\n", apStats.abilitySuccessCnt);
   MCD_SHOW("Link Fail cnt         %08d\n", apStats.linkFailCnt);
   MCD_SHOW("Link Success cnt      %08d\n", apStats.linkSuccessCnt);
   MCD_SHOW("HCD Time              %08d\n", apStats.hcdResoultionTime);
   MCD_SHOW("link Up Time          %08d\n", apStats.linkUpTime);
   MCD_SHOW("Total Exec Time       %08d\n", apStats.hcdResoultionTime + apStats.linkUpTime);

    return MCD_OK;
}


/**
* @internal mcdApPortCtrlIntropShow function
* @endinternal
*
* @brief   Print AP port introp information stored in system
*
* @param[in] pDev
* @param[in] apPortNum                - AP port number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdApPortCtrlIntropShow
(
    MCD_DEV_PTR             pDev,
    MCD_U32  apPortNum
)
{
    MCD_AP_PORT_INTROP apIntrop;

    ATTEMPT(mcdApPortCtrlIntropGet(pDev, apPortNum, &apIntrop));

   MCD_SHOW("======== AP Introp Parameters  ========\n");
   MCD_SHOW("Tx Disable duration        %08d msec\n",      apIntrop.txDisDuration);
   MCD_SHOW("Ability duration           %08d msec\n",      apIntrop.abilityDuration);
   MCD_SHOW("Ability max interval       %08d intervals\n", apIntrop.abilityMaxInterval);
   MCD_SHOW("Ability fail max interval  %08d intervals\n", apIntrop.abilityFailMaxInterval);
   MCD_SHOW("AP Link Duration           %08d msec\n",      apIntrop.apLinkDuration);
   MCD_SHOW("AP Link Max interval check %08d intervals\n", apIntrop.apLinkMaxInterval);
   MCD_SHOW("PD Link Duration           %08d msec\n",      apIntrop.pdLinkDuration);
   MCD_SHOW("PD Link Max interval check %08d intervals\n", apIntrop.pdLinkMaxInterval);

    return MCD_OK;
}

/**
* @internal mcdApPortCtrlDebugInfoShow function
* @endinternal
*
* @brief   Print AP port real-time log information stored in system
*
* @param[in] apPortNum                - AP port number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdApPortCtrlDebugInfoShow
(
    MCD_DEV_PTR             pDev,
    MCD_U32    apPortNum,
    MCD_BOOL   apCpssLogEnable
)
{
    MCD_UINT logIndex;
    MCD_UINT logCount=0;
    MCD_UINT logPointer=0;
    MCD_UINT logReset=0;
    MCD_UINT logActiveCount;
    MCD_UINT logActivePointer;
    MCD_UINT logInfo;
    MCD_UINT timestamp;

    /* Log records and all related data are 32-bit words */
    /* not needed special support for BIG Endian CPU     */
    /* read/write functions swap as needed               */

    /* Read log control parameters */
    mcdServiceCpuRead(pDev, mcdFwAPLogCountOffsetAddr,   (unsigned int*)&logCount,   1);
    mcdServiceCpuRead(pDev, mcdFwAPLogPointerOffsetAddr, (unsigned int*)&logPointer, 1);
    mcdServiceCpuRead(pDev, mcdFwAPLogResetOffsetAddr,   (unsigned int*)&logReset,   1);
    /* Read log content */
    mcdServiceCpuRead(pDev, mcdFwAPLogOffsetAddr, (unsigned int*)portLog, sizeof(portLog));
    /* Mark log count reset (by Service CPU) */
    logReset++;
    mcdServiceCpuWrite(pDev, mcdFwAPLogResetOffsetAddr, (unsigned int*)&logReset, 1);

    /* Process Log */
    /* =========== */
    logActiveCount   = logCount;
    logActivePointer = logPointer;

    /* Adjust log control parameters */
    if (logActivePointer >= MCD_PORT_CTRL_LOG_SIZE)
    {
        logActivePointer = 0;
    }

    if (logActiveCount >= MCD_PORT_CTRL_LOG_SIZE)
    {
        logActiveCount = MCD_PORT_CTRL_LOG_SIZE;
    }

    /* The pointer overlapped and we need to read from the start of the newer
       entries which is prior to the overlapping */
    if (logActiveCount > logActivePointer)
    {
        logActivePointer = MCD_PORT_CTRL_LOG_SIZE - (logActiveCount - logActivePointer);
    }
    /* Set pointer to the first of the newer lines */
    else
    {
        logActivePointer = logActivePointer - logActiveCount;
    }

    /* Dump log */
   MCD_SHOW("\nPort Control Realtime Log\n"
                 "=========================\n"
                 "Num of log entries  %03d\n"
                 "Current entry index %03d\n",
                 logActiveCount, logActivePointer);


    mcdFwAPLogPointer = logPointer;

    for (logIndex = 0; logIndex < logActiveCount; logIndex++)
    {
        logInfo   = portLog[logActivePointer].info;
        timestamp = portLog[logActivePointer].timestamp;

        mcdApPortCtrlDebugInfoShowEntry(apPortNum, timestamp, logInfo, apCpssLogEnable);

        logActivePointer++;
        if (logActivePointer >= MCD_PORT_CTRL_LOG_SIZE)
        {
            logActivePointer = 0;
        }
    }

    return MCD_OK;
}

static void mcdPollingStatStructureDataSwap(
    INOUT MCD_POLLING_PORT_STATISTIC_STC  *pollingStatPtr)
{
#ifdef MCD_IPC_CNV_ENABLE
    /* 32-bit data not needed treatment           */
    /* memory read function swapps them as needed */
#define SWAP_U16_ARR(_arr) \
    { \
        unsigned int* p = (unsigned int*)_arr;   \
        unsigned int size = (sizeof(_arr) / 4);  \
        unsigned int i; \
        for (i = 0; (i < size); i++, p++) \
        { \
            *p = mcdInternalIpcSwappedLeToBeConvert( \
                MCD_IPC_CNV_WORD32_FORMAT_2U16_E, *p); \
        } \
    }
/**/
    SWAP_U16_ARR(pollingStatPtr->linePcsCheckCount);
    SWAP_U16_ARR(pollingStatPtr->linePcsCheckFailCount);
    SWAP_U16_ARR(pollingStatPtr->hostPcsCheckCount);
    SWAP_U16_ARR(pollingStatPtr->hostPcsCheckFailCount);
    SWAP_U16_ARR(pollingStatPtr->signalCheckCount);
    SWAP_U16_ARR(pollingStatPtr->signalCheckFailCount);
    SWAP_U16_ARR(pollingStatPtr->trainCount);
    SWAP_U16_ARR(pollingStatPtr->trainFailCount);
    SWAP_U16_ARR(pollingStatPtr->countICalFailed);
    SWAP_U16_ARR(pollingStatPtr->countEoFailed);
    SWAP_U16_ARR(pollingStatPtr->stopAdaptiveFailed);
    SWAP_U16_ARR(pollingStatPtr->countSignalOffToCheckStable);
    SWAP_U16_ARR(pollingStatPtr->countSignalCheckStableToOff);
    SWAP_U16_ARR(pollingStatPtr->countSignalCheckStableToOn);
    SWAP_U16_ARR(pollingStatPtr->countSignalOnToOff);
    SWAP_U16_ARR(pollingStatPtr->countConfidenceIntFailed);
    SWAP_U16_ARR(pollingStatPtr->registedSignalLastStates);

#undef SWAP_U16
#endif
}

/**
* @internal mcdPollingStatShow function
* @endinternal
*
* @brief   Print FW Hws real-time polling statistic information stored in system
*
* @param[in] pDev                     - pointer to device
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdPollingStatShow
(
    MCD_DEV_PTR             pDev
)
{
    MCD_U32 serdes, port, side;
#ifdef  MCD_AP_STATE_STATUS_LOG
    MCD_U32 state, status,index;
    MCD_U64 tempDecode, tempDecodeType;
#endif  /*MCD_AP_STATE_STATUS_LOG*/
    MCD_POLLING_PORT_STATISTIC_STC  pollingStat;

    /* Read statistic */
    mcdServiceCpuRead(pDev, mcdFwPollingDbAddr,   (unsigned int*)&pollingStat, sizeof(pollingStat));
    mcdPollingStatStructureDataSwap(&pollingStat);

   MCD_SHOW("\n pDev %p hostContext %p\n\n",pDev, pDev->hostContext);
   MCD_SHOW(" SERDES | Signal | Signal | Training | Training | ICal     | EO       | Adatptive | Confidence |\n");
   MCD_SHOW("        | Check  | Fail   | Count    | Fails    | Failed   | Failed   | Failed    | Failed     |\n");
   MCD_SHOW("================================================================================================\n");

   for (serdes = 0; serdes < MCD_POLLING_SERDES_NUM_CNS; serdes++)
   {
       MCD_SHOW(" %02d     | %5d  | %5d  | %5d    | %5d    | %5d    | %5d    | %6d    | %6d    |\n",serdes,
                pollingStat.signalCheckCount[serdes],
                pollingStat.signalCheckFailCount[serdes],
                pollingStat.trainCount[serdes],
                pollingStat.trainFailCount[serdes],
                pollingStat.countICalFailed[serdes],
                pollingStat.countEoFailed[serdes],
                pollingStat.stopAdaptiveFailed[serdes],
                pollingStat.countConfidenceIntFailed[serdes]);
   }

   MCD_SHOW("\n");

   MCD_SHOW("\nPort |Host PCS|Host PCS|Line PCS|Line PCS| Host UP | Line UP | Host UP | Line UP |"
            "\n     | Check  | Fail   | Check  | Fail   |Last Time|Last Time| Longest | Longest |\n"
              "==================================================================================\n");

   for (port = 0; port < MCD_POLLING_PORTS_NUM_CNS; port++)
   {
       MCD_SHOW(" %2d  | %5d  | %5d  | %5d  | %5d  | %6d  | %6d  | %6d  | %6d  |\n",
                port,
                pollingStat.hostPcsCheckCount[port],
                pollingStat.hostPcsCheckFailCount[port],
                pollingStat.linePcsCheckCount[port],
                pollingStat.linePcsCheckFailCount[port],
                pollingStat.hostLastUpTime[port],
                pollingStat.lineLastUpTime[port],
                pollingStat.hostLongestUpTime[port],
                pollingStat.lineLongestUpTime[port]);
   }

   MCD_SHOW("\n");

   for (side = 0; (side < 2); side++)
   {
       MCD_SHOW("SIGNAL status statistics, side %s\n", (side ? "LINE" : "HOST"));
       MCD_SHOW("Port | Off to  | Check   | Check   | On To   |\n"
                "     | Check   | To Off  | To On   | Off     |\n"
                  "============================================\n");

       for (port = 0; port < MCD_POLLING_PORTS_NUM_CNS; port++)
       {
           MCD_SHOW(" %2d  | %6d  | %6d  | %6d  | %6d  |\n",
                    port,
                    pollingStat.countSignalOffToCheckStable[side][port],
                    pollingStat.countSignalCheckStableToOff[side][port],
                    pollingStat.countSignalCheckStableToOn[side][port],
                    pollingStat.countSignalOnToOff[side][port]);
       }

       MCD_SHOW("\n");

       MCD_SHOW("SIGNAL states statistics, side %s\n", (side ? "LINE" : "HOST"));
       MCD_SHOW("0-OFF_TO_CHK  1-CHK_TO_OFF  2-CHK_TO_ON  3-ON_TO_OFF\n");
       MCD_SHOW("Port    st-0  st-1  st-2  st-3  st-4  st-5 \n"
                "===========================================\n");
       for (port = 0; port < MCD_POLLING_PORTS_NUM_CNS; port++)
       {
           MCD_SHOW(" %d   | %2d <- %2d <- %2d <- %2d <- %2d <- %2d \n",
                    port,
                    MCD_STAT_SIGNAL_GET(side, port, 0),
                    MCD_STAT_SIGNAL_GET(side, port, 1),
                    MCD_STAT_SIGNAL_GET(side, port, 2),
                    MCD_STAT_SIGNAL_GET(side, port, 3),
                    MCD_STAT_SIGNAL_GET(side, port, 4),
                    MCD_STAT_SIGNAL_GET(side, port, 5));
       }
       MCD_SHOW("\n");
   }

#ifdef  MCD_AP_STATE_STATUS_LOG
   MCD_SHOW("AP status/stats info:\n");
   MCD_SHOW("=====================\n");

   MCD_SHOW("AP_SM status,states info:\n");
   MCD_SHOW("Port    last state to ..... last-11\n"
             "==============================================================\n");
   for (port = 0; port < MCD_POLLING_PORTS_NUM_CNS; port++)
   {
       MCD_SHOW(" %d   | ", port);
       /* Saving the LOG local DB to temp arguments */
       tempDecode     =  MCD_AP_SM_DECODE(port);
       tempDecodeType =  MCD_AP_SM_DECODE_TYPE(port);
       /* At this stage, the maximum # of items can be saved in 64bit argument is 64/5 = 12 */
       for (index = 0; index < 12  ; index++)
       {
           /* if last log index is "state" */
           if (tempDecodeType & 0x1)
           {
               /* Read the state value and shift right the number of "state" bits */
               state = (tempDecode & 0xF);
               MCD_SHOW("|%d|", state);
               tempDecode = (tempDecode >> 4);
           }
           else
           {
               /* Read the status value and shift right the number of "status" bits */
               status = (tempDecode & 0x1F);
               MCD_SHOW("<-%d--", status);
               tempDecode = (tempDecode >> 5);
           }
           /* Get the next codeType (state or status) */
           tempDecodeType = tempDecodeType >> 1;
       }
       MCD_SHOW("\n");
   }
   MCD_SHOW("\n");

   MCD_SHOW("PORT_SM status,states info:\n");
   MCD_SHOW("Port    last state to ..... last-11\n"
             "==============================================================\n");
   for (port = 0; port < MCD_POLLING_PORTS_NUM_CNS; port++)
   {
       MCD_SHOW(" %d   | ", port);
       /* Saving the LOG local DB to temp arguments */
       tempDecode     =  MCD_PORT_SM_DECODE(port);
       tempDecodeType =  MCD_PORT_SM_DECODE_TYPE(port);
       /* At this stage, the maximum # of items can be saved in 64bit argument is 64/5 = 12 */
       for (index = 0; index < 12  ; index++)
       {
           /* if last log index is "state" */
           if (tempDecodeType & 0x1)
           {
               /* Read the state value and shift right the number of "state" bits */
               state = (tempDecode & 0xF);
               MCD_SHOW("|%d|", state);
               tempDecode = (tempDecode >> 4);
           }
           else
           {
               /* Read the status value and shift right the number of "status" bits */
               status = (tempDecode & 0x1F);
               MCD_SHOW("<-%d--", status);
               tempDecode = (tempDecode >> 5);
           }
           /* Get the next codeType (state or status) */
           tempDecodeType = tempDecodeType >> 1;
       }
       MCD_SHOW("\n");
   }
   MCD_SHOW("\n");
#endif  /*MCD_AP_STATE_STATUS_LOG*/

   for (side = 0; (side < 2); side++)
   {
       MCD_SHOW("Retimer mode SIGNAL status mSec time statistics, side %s\n", (side ? "LINE" : "HOST"));
       MCD_SHOW("\nPort |  Min ON   | Max OFF   | Max OFF   |Max Local OFF |"
                "\n     |  continue | To Check  | To On     | To Both ON   |\n"
                  "========================================================|\n");

       for (port = 0; port < MCD_POLLING_PORTS_NUM_CNS; port++)
       {
           MCD_SHOW(" %2d  | %9d  | %9d  | %9d  | %9d  |\n",
                    port,
                    pollingStat.minSignalOnTime[side][port],
                    pollingStat.maxSignalOffToCheckTime[side][port],
                    pollingStat.maxSignalOffToOnTime[side][port],
                    pollingStat.maxSignalOtherSideOnToBothSidesOnTime[side][port]);
       }

       MCD_SHOW("\n");
   }

   MCD_SHOW("Retimer mode SIGNAL ON  on both sides minimal mSec time (ports 0..7)\n");
   for (port = 0; port < MCD_POLLING_PORTS_NUM_CNS; port++)
   {
       MCD_SHOW("%d ", pollingStat.minSignalOnBothSidesTime[port]);
   }
   MCD_SHOW("\n");

   return MCD_OK;
}


/**
* @internal mcdPollingStatClear function
* @endinternal
*
* @brief   Clear FW Hws real-time polling statistic information stored in system
*
* @param[in] pDev                     - pointer to device
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdPollingStatClear
(
    MCD_DEV_PTR             pDev
)
{
    MCD_STATUS rc;
    MCD_POLLING_PORT_STATISTIC_STC  pollingStat;

    mcdMemSet(&pollingStat, 0, sizeof(MCD_POLLING_PORT_STATISTIC_STC));

    /* Read statistic */
    rc = mcdServiceCpuWrite(pDev, mcdFwPollingDbAddr,   (unsigned int*)&pollingStat, sizeof(MCD_POLLING_PORT_STATISTIC_STC));

    return rc;
}

/**
* @internal mcdPollingStatValueGet function
* @endinternal
*
* @brief   Get FW real-time polling statistic information stored in system
*
* @param[in] pDev                     - pointer to device
* @param[in] lineSide                 - host side - 0, line side - 1
*
* @param[out] pollingStatValPtr        - pointer to required value.
*
* @retval MCD_OK                   - on success
* @retval MCD_FAIL                 - on wrong parameters
*/
MCD_STATUS mcdPollingStatValueGet
(
    IN  MCD_DEV_PTR                         pDev,
    IN  MCD_U32                             portOrSerdes,
    IN  MCD_U32                             lineSide,
    IN  MCD_POLLING_PORT_STATISTIC_VAL_ENT  valueType,
    OUT MCD_U32                             *pollingStatValPtr
)
{
    MCD_POLLING_PORT_STATISTIC_STC  pollingStat;
    MCD_U32 portNum, serdesNum;

    if (lineSide > 1) return MCD_FAIL;

    mcdServiceCpuRead(
        pDev, mcdFwPollingDbAddr,
        (unsigned int*)&pollingStat,
        sizeof(MCD_POLLING_PORT_STATISTIC_STC));
    mcdPollingStatStructureDataSwap(&pollingStat);

    portNum = 0xFF;
    serdesNum = 0xFF;

    switch (valueType)
    {
        case MCD_POLLING_PORT_STATISTIC_VAL_LAST_UP_TIME_E:
        case MCD_POLLING_PORT_STATISTIC_VAL_LONGEST_UP_TIME_E:
        case MCD_POLLING_PORT_STATISTIC_VAL_PCS_CHECK_COUNT_E:
        case MCD_POLLING_PORT_STATISTIC_VAL_PCS_CHECK_FAIL_COUNT_E:
            portNum = portOrSerdes;
            break;
        case MCD_POLLING_PORT_STATISTIC_VAL_SERDES_SIGNAL_CHECK_COUNT_E:
        case MCD_POLLING_PORT_STATISTIC_VAL_SERDES_SIGNAL_CHECK_FAIL_COUNT_E:
        case MCD_POLLING_PORT_STATISTIC_VAL_SERDES_TRAIN_COUNT_E:
        case MCD_POLLING_PORT_STATISTIC_VAL_SERDES_TRAIN_FAIL_COUNT_E:
            serdesNum = portOrSerdes + (lineSide ? 0 : 8);
            break;
        case MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_OFF_TO_CHECK_COUNT_E:
        case MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_CHECK_TO_OFF_COUNT_E:
        case MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_CHECK_TO_ON_COUNT_E:
        case MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_ON_TO_OFF_COUNT_E:
        case MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_LAST_STATES_E :
        case MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_MIN_ON_TIME_E:
        case MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_MAX_OFF_TO_CHECK_TIME_E:
        case MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_MAX_OFF_TO_ON_TIME_E:
        case MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_MIN_BOTH_SIDES_ON_TIME_E:
            portNum = portOrSerdes;
            break;
        default: return MCD_FAIL;
    }

    if ((portNum != 0xFF) && (portNum >= 8)) return MCD_FAIL;
    if ((serdesNum != 0xFF) && (serdesNum >= 16)) return MCD_FAIL;

    switch (valueType)
    {
        case MCD_POLLING_PORT_STATISTIC_VAL_LAST_UP_TIME_E:
            *pollingStatValPtr =
                lineSide ? pollingStat.lineLastUpTime[portNum]
                : pollingStat.hostLastUpTime[portNum];
            return MCD_OK;
        case MCD_POLLING_PORT_STATISTIC_VAL_LONGEST_UP_TIME_E:
            *pollingStatValPtr =
                lineSide ? pollingStat.lineLongestUpTime[portNum]
                : pollingStat.hostLongestUpTime[portNum];
            return MCD_OK;
        case MCD_POLLING_PORT_STATISTIC_VAL_PCS_CHECK_COUNT_E:
            *pollingStatValPtr =
                lineSide ? pollingStat.linePcsCheckCount[portNum]
                : pollingStat.hostPcsCheckCount[portNum];
            return MCD_OK;
        case MCD_POLLING_PORT_STATISTIC_VAL_PCS_CHECK_FAIL_COUNT_E:
            *pollingStatValPtr =
                lineSide ? pollingStat.linePcsCheckFailCount[portNum]
                : pollingStat.hostPcsCheckFailCount[portNum];
            return MCD_OK;
        case MCD_POLLING_PORT_STATISTIC_VAL_SERDES_SIGNAL_CHECK_COUNT_E:
            *pollingStatValPtr = pollingStat.signalCheckCount[serdesNum];
            return MCD_OK;
        case MCD_POLLING_PORT_STATISTIC_VAL_SERDES_SIGNAL_CHECK_FAIL_COUNT_E:
            *pollingStatValPtr = pollingStat.signalCheckFailCount[serdesNum];
            return MCD_OK;
        case MCD_POLLING_PORT_STATISTIC_VAL_SERDES_TRAIN_COUNT_E:
            *pollingStatValPtr = pollingStat.trainCount[serdesNum];
            return MCD_OK;
        case MCD_POLLING_PORT_STATISTIC_VAL_SERDES_TRAIN_FAIL_COUNT_E:
            *pollingStatValPtr = pollingStat.trainFailCount[serdesNum];
            return MCD_OK;
        case MCD_POLLING_PORT_STATISTIC_VAL_ICAL_FAILED_COUNT_E:
            *pollingStatValPtr =
                 pollingStat.countICalFailed[serdesNum];
            return MCD_OK;
        case MCD_POLLING_PORT_STATISTIC_VAL_EO_FAILED_COUNT_E:
            *pollingStatValPtr =
                 pollingStat.countEoFailed[serdesNum];
            return MCD_OK;
        case MCD_POLLING_PORT_STATISTIC_VAL_ADAPTIVE_FAILED_COUNT_E:
            *pollingStatValPtr =
                 pollingStat.stopAdaptiveFailed[serdesNum];
            return MCD_OK;
        case MCD_POLLING_PORT_STATISTIC_VAL_CONFIDENCE_INT_FAILED_COUNT_E:
            *pollingStatValPtr =
                pollingStat.countConfidenceIntFailed[serdesNum];
            return MCD_OK;
        case MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_OFF_TO_CHECK_COUNT_E:
            *pollingStatValPtr =
                 pollingStat.countSignalOffToCheckStable[lineSide][portNum];
            return MCD_OK;
        case MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_CHECK_TO_OFF_COUNT_E:
            *pollingStatValPtr =
                 pollingStat.countSignalCheckStableToOff[lineSide][portNum];
            return MCD_OK;
        case MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_CHECK_TO_ON_COUNT_E:
            *pollingStatValPtr =
                 pollingStat.countSignalCheckStableToOn[lineSide][portNum];
            return MCD_OK;
        case MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_ON_TO_OFF_COUNT_E:
            *pollingStatValPtr =
                 pollingStat.countSignalOnToOff[lineSide][portNum];
            return MCD_OK;
        case MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_LAST_STATES_E:
            *pollingStatValPtr =
                 pollingStat.registedSignalLastStates[lineSide][portNum];
            return MCD_OK;
         case MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_MIN_ON_TIME_E:
            *pollingStatValPtr =
                 pollingStat.minSignalOnTime[lineSide][portNum];
            return MCD_OK;
        case MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_MAX_OFF_TO_CHECK_TIME_E:
            *pollingStatValPtr =
                 pollingStat.maxSignalOffToCheckTime[lineSide][portNum];
            return MCD_OK;
        case MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_MAX_OFF_TO_ON_TIME_E:
            *pollingStatValPtr =
                 pollingStat.maxSignalOffToOnTime[lineSide][portNum];
            return MCD_OK;
        case MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_MAX_ONE_SIDE_ON_TO_BOTH_SIDES_ON_TIME_E:
            *pollingStatValPtr =
                 pollingStat.maxSignalOtherSideOnToBothSidesOnTime[lineSide][portNum];
            return MCD_OK;
        case MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_MIN_BOTH_SIDES_ON_TIME_E:
            *pollingStatValPtr =
                 pollingStat.minSignalOnBothSidesTime[portNum];
            return MCD_OK;
        default: return MCD_FAIL;
    }

    return MCD_OK;
}

/**
* @internal mcdPollingStatRetimerPerPortValuesClear function
* @endinternal
*
* @brief   Clear FW real-time polling statistic related to retimer port side.
*
* @param[in] pDev                     - pointer to device
* @param[in] portNum                  - port number
* @param[in] lineSide                 - host side - 0, line side - 1
*
* @retval MCD_OK                   - on success
* @retval MCD_FAIL                 - on wrong parameters
*/
MCD_STATUS mcdPollingStatRetimerPerPortValuesClear
(
    IN  MCD_DEV_PTR                         pDev,
    IN  MCD_U32                             portNum,
    IN  MCD_U32                             lineSide
)
{
    static MCD_U32 nullPattern[MCD_POLLING_PORTS_NUM_CNS] = {0};

    if (portNum > 7)  return MCD_FAIL;
    if (lineSide > 1) return MCD_FAIL;

#define GEN_OFF(str, mem) (((char*)&((str*)0)->mem) - (char*)0)
#define POLL_ADDR(mem) \
    (mcdFwPollingDbAddr + GEN_OFF(MCD_POLLING_PORT_STATISTIC_STC, mem))
#define GEN_SIZE(str, mem) sizeof(((str*)0)->mem)
#define POLL_SIZE(mem) GEN_SIZE(MCD_POLLING_PORT_STATISTIC_STC, mem)

    /* retimer port side statistics counters - index 0 - host, index 1 - line */
    mcdServiceCpuWrite(
        pDev, POLL_ADDR(countSignalOffToCheckStable[lineSide]),
        (unsigned int*)nullPattern,
        POLL_SIZE(countSignalOffToCheckStable[lineSide]));

    mcdServiceCpuWrite(
        pDev, POLL_ADDR(countSignalCheckStableToOff[lineSide]),
        (unsigned int*)nullPattern,
        POLL_SIZE(countSignalCheckStableToOff[lineSide]));

    mcdServiceCpuWrite(
        pDev, POLL_ADDR(countSignalCheckStableToOn[lineSide]),
        (unsigned int*)nullPattern,
        POLL_SIZE(countSignalCheckStableToOn[lineSide]));

    mcdServiceCpuWrite(
        pDev, POLL_ADDR(countSignalOnToOff[lineSide]),
        (unsigned int*)nullPattern,
        POLL_SIZE(countSignalOnToOff[lineSide]));

    mcdServiceCpuWrite(
        pDev, POLL_ADDR(registedSignalLastStates[lineSide]),
        (unsigned int*)nullPattern,
        POLL_SIZE(registedSignalLastStates[lineSide]));

    /* retimer port side statistics OS mSec times - index 0 - host, index 1 - line   */
    mcdServiceCpuWrite(
        pDev, POLL_ADDR(minSignalOnTime[lineSide]),
        (unsigned int*)nullPattern,
        POLL_SIZE(minSignalOnTime[lineSide]));

    mcdServiceCpuWrite(
        pDev, POLL_ADDR(maxSignalOffToCheckTime[lineSide]),
        (unsigned int*)nullPattern,
        POLL_SIZE(maxSignalOffToCheckTime[lineSide]));

    mcdServiceCpuWrite(
        pDev, POLL_ADDR(maxSignalOffToOnTime[lineSide]),
        (unsigned int*)nullPattern,
        POLL_SIZE(maxSignalOffToOnTime[lineSide]));

    mcdServiceCpuWrite(
        pDev, POLL_ADDR(maxSignalOtherSideOnToBothSidesOnTime[lineSide]),
        (unsigned int*)nullPattern,
        POLL_SIZE(maxSignalOtherSideOnToBothSidesOnTime[lineSide]));

    /* port statistic */
    /* retimer port statistics OS mSec times */
    mcdServiceCpuWrite(
        pDev, POLL_ADDR(minSignalOnBothSidesTime),
        (unsigned int*)nullPattern,
        POLL_SIZE(minSignalOnBothSidesTime));

#undef GEN_OFF
#undef POLL_ADDR
#undef GEN_SIZE
#undef POLL_SIZE
    return MCD_OK;
}

/**
* @internal mcdApPortCtrlDebugInfoShowEntry function
* @endinternal
*
* @brief   Print Log content according to Log count
*         The order of print is from the oldest to the newest message
*/
void mcdApPortCtrlDebugInfoShowEntry(MCD_U32 port, MCD_U32 timestamp, MCD_U32 logInfo, MCD_BOOL apCpssLogEnable)
{
    MCD_U32 msgId;
    MCD_U32 stateId;
    MCD_U32 portId;
    MCD_U32 regId;
    MCD_U32 regVal;
    MCD_U32 hcdId;
    MCD_U32 arbId;
    MCD_U32 statusId;

    switch (MCD_LOG_MOD_GET(logInfo))
    {
    case MCD_M0_DEBUG:
        portId  = MCD_REG_LOG_PORT_GET(logInfo);
        stateId = MCD_REG_LOG_STATE_GET(logInfo);
        regId   = MCD_REG_LOG_IDX_GET(logInfo);
        regVal  = MCD_REG_LOG_VAL_GET(logInfo);

        /* Validate inputs params */
        if (((port != MCD_LOG_ALL_PORT_DUMP) && (port != portId)) ||
             (stateId >= MCD_AP_PORT_SM_MAX_STATE) ||
             (regId >= MCD_PORT_CTRL_MAX_AP_REGS))
        {
            break;
        }

        /*print On Demand Registers*/
       MCD_SHOW("%08d: AP REG  Port %d, %s 0x%04x\n", timestamp, portId, regType[regId], regVal);
        break;

    case MCD_M1_SUPERVISOR:
        portId  = MCD_SPV_LOG_PORT_GET(logInfo);
        msgId   = MCD_SPV_LOG_MSG_GET(logInfo);
        stateId = MCD_SPV_LOG_STATE_GET(logInfo);

        /* Validate inputs params */
        if (((port != MCD_LOG_ALL_PORT_DUMP) && (port != portId)) ||
             (msgId >= MCD_IPC_LAST_CTRL_MSG_TYPE) ||
             (stateId >= MCD_SPV_MAX_STATE))
        {
            break;
        }

        /* Process message */
       MCD_SHOW("%08d: Super   Port %02d, %s, %s Msg Sent to execute, O%d(%s)\n",
                      timestamp,
                      portId,
                      portType[MCD_SPV_LOG_TYPE_GET(logInfo)],
                      msgType[msgId],
                      stateId + 1,
                      superState[stateId]);
        break;

    case MCD_M2_PORT_MNG:
        portId  = MCD_PORT_MNG_LOG_PORT_GET(logInfo);
        msgId   = MCD_PORT_MNG_MSG_GET(logInfo);
        stateId = MCD_PORT_MNG_LOG_STATE_GET(logInfo);

        /* Validate inputs params */
        if (((port != MCD_LOG_ALL_PORT_DUMP) && (port != portId)) ||
             (msgId >= MCD_IPC_LAST_CTRL_MSG_TYPE) ||
             (stateId >= MCD_PORT_MNG_MAX_STATE))
        {
            break;
        }

       MCD_SHOW("%08d: PortMng Port %02d, %s Msg start execute, O%d(%s)\n",
                     timestamp,
                     portId,
                     msgType[msgId],
                     stateId,
                     portMngState[stateId]);
        break;

    case MCD_M3_PORT_SM:
        portId   = MCD_PORT_SM_LOG_PORT_GET(logInfo);
        statusId = MCD_PORT_SM_LOG_STATUS_GET(logInfo);
        stateId  = MCD_PORT_SM_LOG_STATE_GET(logInfo);

        /* Validate inputs params */
        if (((port != MCD_LOG_ALL_PORT_DUMP) && (port != portId)) ||
             (statusId >= MCD_PORT_SM_MAX_STATUS) ||
             (stateId >= MCD_PORT_SM_MAX_STATE))
        {
            break;
        }

        /* Process message */
       MCD_SHOW("%08d: Port SM Port %02d, %s, O%d(%s)\n",
                     timestamp,
                     portId,
                     portMngSmStatus[statusId],
                     stateId,
                     portMngSmState[stateId]);
        break;

    case MCD_M4_AP_PORT_MNG:
        portId   = MCD_AP_PORT_MNG_LOG_PORT_GET(logInfo);
        statusId = MCD_AP_PORT_MNG_LOG_STATUS_GET(logInfo);
        stateId  = MCD_AP_PORT_MNG_LOG_STATE_GET(logInfo);

        /* Validate inputs params */
        if (((port != MCD_LOG_ALL_PORT_DUMP) && (port != portId)) ||
             (statusId >= MCD_PORT_SM_MAX_STATUS) ||
             (stateId >= MCD_PORT_SM_MAX_STATE))
        {
            break;
        }

       MCD_SHOW("%08d: Port SM Port %02d, %s, O%d(%s)\n",
                      timestamp,
                      portId,
                      portMngSmStatus[statusId],
                      stateId,
                      portMngSmState[stateId]);
        break;

    case MCD_M5_AP_PORT_DET:
        portId   = MCD_AP_PORT_DET_LOG_PORT_GET(logInfo);
        statusId = MCD_AP_PORT_DET_LOG_STATUS_GET(logInfo);
        stateId  = MCD_AP_PORT_DET_LOG_STATE_GET(logInfo);
        arbId    = MCD_AP_PORT_DET_LOG_HW_SM_GET(logInfo);

        /* Validate inputs params */
        if (((port != MCD_LOG_ALL_PORT_DUMP) && (port != portId)) ||
             (statusId >= MCD_AP_PORT_MAX_STATUS) ||
             (stateId >= MCD_AP_PORT_SM_MAX_STATE))
        {
            break;
        }

        /* Process message */
       MCD_SHOW("%08d: AP SM   Port %02d, %s, O%d(%s) ",
                      timestamp,
                      portId,
                      mcdApPortMngSmStatus[statusId],
                      stateId,
                      mcdApPortMngSmState[stateId]);
        mcdArbSmStateDesc(arbId);
        break;

    case MCD_M5_AP_PORT_DET_EXT:
        portId = MCD_AP_PORT_DET_EXT_LOG_PORT_GET(logInfo);
        hcdId  = MCD_AP_PORT_DET_EXT_LOG_HCD_GET(logInfo);

        /* Validate inputs params */
        if (((port != MCD_LOG_ALL_PORT_DUMP) && (port != portId)) ||
             (hcdId >= 4))
        {
            break;
        }

        /* Process message */
       MCD_SHOW("%08d: AP SM   Port %02d, HCD[%s %s Link %s, FEC Result %s] FC[Tx %s, RX %s] Int[HCD %s, Link %s] \n",
                       timestamp,
                       portId,
                       apPortMngHcdFound[MCD_AP_PORT_DET_EXT_LOG_FOUND_GET(logInfo)],
                       apPortMngHcdType[MCD_AP_PORT_DET_EXT_LOG_HCD_GET(logInfo)],
                       apPortMngGen[MCD_AP_PORT_DET_EXT_LOG_LINK_GET(logInfo)],
                       apPortMngGen[MCD_AP_PORT_DET_EXT_LOG_FEC_RES_GET(logInfo)],
                       apPortMngGen[MCD_AP_PORT_DET_EXT_LOG_TX_FC_GET(logInfo)],
                       apPortMngGen[MCD_AP_PORT_DET_EXT_LOG_RX_FC_GET(logInfo)],
                       apPortMngGen[MCD_AP_PORT_DET_EXT_LOG_HCD_INT_GET(logInfo)],
                       apPortMngGen[MCD_AP_PORT_DET_EXT_LOG_LINK_INT_GET(logInfo)]);
            break;
    case MCD_M6_GENERAL:
        portId = PORT_GENERAL_LOG_PORT_GET(logInfo);
        msgId  = PORT_GENERAL_LOG_MSG_GET(logInfo);
        stateId = PORT_GENERAL_LOG_STATE_GET(logInfo);

        /* Validate inputs params */
        if (port != portId)
        {
            break;
        }

         MCD_SHOW("%08d: Polling Port %02d, %s state:%s",
                       timestamp,
                       portId,
                       ((stateId == 1)? "LINE": "HOST"),mcdPollingSmStatus[msgId]);

#if 0
        switch (msgId)
        {
        case MV_HWS_IPC_PORT_LINK_STATUS_GET_MSG:
            if (PORT_GENERAL_LOG_RES_GET(logInfo))
            {
                     MCD_SHOW(" %s", (PORT_GENERAL_LOG_DETAIL_GET(logInfo) == MV_GEN_LINK_DOWN) ? "Fail" :"OK");
            }
            break;
        case MV_HWS_IPC_PORT_AUTO_TUNE_SET_EXT_MSG:
            if (PORT_GENERAL_LOG_RES_GET(logInfo))
            {
                    MCD_SHOW(" %s", (PORT_GENERAL_LOG_DETAIL_GET(logInfo) == MV_GEN_TUNE_FAIL) ? "Fail" :"Pass");
            }
            break;
        }
#endif
        MCD_SHOW("\n");
        break;

    }
}



