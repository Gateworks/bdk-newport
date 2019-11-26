/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
********************************************************************************
*/
/**
********************************************************************************
* @file mcdPortCtrlApLogDefs.h
*
* @brief Port Control Log Definitions
*
* @version   1
********************************************************************************
*/

#ifndef __mcdPortCtrlApLogDefs_H
#define __mcdPortCtrlApLogDefs_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "mcdApiTypes.h"

/* AP ARB State Machine Numbering Definition */

typedef enum
{
    MCD_ST_AN_ENABLE    = 0x001,
    MCD_ST_TX_DISABLE   = 0x002,
    MCD_ST_LINK_STAT_CK = 0x004,
    MCD_ST_PARALLEL_FLT = 0x008,
    MCD_ST_ABILITY_DET  = 0x010,
    MCD_ST_ACK_DETECT   = 0x020,
    MCD_ST_COMPLETE_ACK = 0x040,
    MCD_ST_NP_WAIT      = 0x080,
    MCD_ST_AN_GOOD_CK   = 0x100,
    MCD_ST_AN_GOOD      = 0x200,
    MCD_ST_SERDES_WAIT  = 0x400

}MCD_AP_SM_STATE;

/* AP Port Mode Definition */
typedef enum
{
     MCD_Port_1000Base_KX,
     MCD_Port_10GBase_KX4,
     MCD_Port_10GBase_R,
     MCD_Port_25GBASE_KR_S,
     MCD_Port_25GBASE_KR,
     MCD_Port_40GBase_R,
     MCD_Port_40GBASE_CR4,
     MCD_Port_100GBASE_CR10,
     MCD_Port_100GBASE_KP4,
     MCD_Port_100GBASE_KR4,
     MCD_Port_100GBASE_CR4,
     MCD_Port_25GBASE_KR1_CONSORTIUM,
     MCD_Port_25GBASE_CR1_CONSORTIUM,
     MCD_Port_50GBASE_KR2_CONSORTIUM,
     MCD_Port_50GBASE_CR2_CONSORTIUM,
     MCD_MODE_NOT_SUPPORTED,
     MCD__AP_LAST = MCD_MODE_NOT_SUPPORTED
}MCD_AP_PORT_MODE;
typedef struct
{
    MCD_U32 fwBaseAddr;
    MCD_U32 fwLogBaseAddr;
    MCD_U32 fwLogCountAddr;
    MCD_U32 fwLogPointerAddr;
    MCD_U32 fwLogResetAddr;
    MCD_U32 fwPollingDbAddr;

}MCD_FW_LOG;

#define MCD_AP_CTRL_GET(param, mask, shift) (((param) >> (shift)) & (mask))
#define MCD_AP_CTRL_SET(param, mask, shift, val) \
{ \
    param &= (~((mask) << (shift))); \
    param |= ((val) << (shift)); \
}

/*
** AP Configuration
** ================
*/

/*
** Interface Number
** [00:07] Lane Number
** [08:15] PCS Number
** [16:23] MAC Number
** [24:31] Reserved
*/
#define MCD_AP_CTRL_LANE_MASK                  (0x7F)
#define MCD_AP_CTRL_LANE_SHIFT                 (0)
#define MCD_AP_CTRL_LANE_GET(ifNum)            MCD_AP_CTRL_GET(ifNum, MCD_AP_CTRL_LANE_MASK, MCD_AP_CTRL_LANE_SHIFT)
#define MCD_AP_CTRL_LANE_SET(ifNum, val)       MCD_AP_CTRL_SET(ifNum, MCD_AP_CTRL_LANE_MASK, MCD_AP_CTRL_LANE_SHIFT, val)

#define MCD_AP_CTRL_PCS_MASK                   (0x7F)
#define MCD_AP_CTRL_PCS_SHIFT                  (8)
#define MCD_AP_CTRL_PCS_GET(ifNum)             MCD_AP_CTRL_GET(ifNum, MCD_AP_CTRL_PCS_MASK, MCD_AP_CTRL_PCS_SHIFT)
#define MCD_AP_CTRL_PCS_SET(ifNum, val)        MCD_AP_CTRL_SET(ifNum, MCD_AP_CTRL_PCS_MASK, MCD_AP_CTRL_PCS_SHIFT, val)

#define MCD_AP_CTRL_MAC_MASK                   (0x7F)
#define MCD_AP_CTRL_MAC_SHIFT                  (16)
#define MCD_AP_CTRL_MAC_GET(ifNum)             MCD_AP_CTRL_GET(ifNum, MCD_AP_CTRL_MAC_MASK, MCD_AP_CTRL_MAC_SHIFT)
#define MCD_AP_CTRL_MAC_SET(ifNum, val)        MCD_AP_CTRL_SET(ifNum, MCD_AP_CTRL_MAC_MASK, MCD_AP_CTRL_MAC_SHIFT, val)

/*
** Capability
** [00:00] Advertisement 40GBase KR4
** [01:01] Advertisement 10GBase KR
** [02:02] Advertisement 10GBase KX4
** [03:03] Advertisement 1000Base KX
** [04:04] Advertisement 20GBase KR2
** [05:05] Advertisement 10GBase KX2
** [06:15] Reserved
*/
#define MCD_AP_CTRL_ADV_MASK                   (0x1)
#define MCD_AP_CTRL_40GBase_KR4_SHIFT          (0)
#define MCD_AP_CTRL_40GBase_KR4_GET(adv)       MCD_AP_CTRL_GET(adv, MCD_AP_CTRL_ADV_MASK, MCD_AP_CTRL_40GBase_KR4_SHIFT)
#define MCD_AP_CTRL_40GBase_KR4_SET(adv, val)  MCD_AP_CTRL_SET(adv, MCD_AP_CTRL_ADV_MASK, MCD_AP_CTRL_40GBase_KR4_SHIFT, val)

#define MCD_AP_CTRL_10GBase_KR_SHIFT           (1)
#define MCD_AP_CTRL_10GBase_KR_GET(adv)        MCD_AP_CTRL_GET(adv, MCD_AP_CTRL_ADV_MASK, MCD_AP_CTRL_10GBase_KR_SHIFT)
#define MCD_AP_CTRL_10GBase_KR_SET(adv, val)   MCD_AP_CTRL_SET(adv, MCD_AP_CTRL_ADV_MASK, MCD_AP_CTRL_10GBase_KR_SHIFT, val)

#define MCD_AP_CTRL_10GBase_KX4_SHIFT          (2)
#define MCD_AP_CTRL_10GBase_KX4_GET(adv)       MCD_AP_CTRL_GET(adv, MCD_AP_CTRL_ADV_MASK, MCD_AP_CTRL_10GBase_KX4_SHIFT)
#define MCD_AP_CTRL_10GBase_KX4_SET(adv, val)  MCD_AP_CTRL_SET(adv, MCD_AP_CTRL_ADV_MASK, MCD_AP_CTRL_10GBase_KX4_SHIFT, val)

#define MCD_AP_CTRL_1000Base_KX_SHIFT          (3)
#define MCD_AP_CTRL_1000Base_KX_GET(adv)       MCD_AP_CTRL_GET(adv, MCD_AP_CTRL_ADV_MASK, MCD_AP_CTRL_1000Base_KX_SHIFT)
#define MCD_AP_CTRL_1000Base_KX_SET(adv, val)  MCD_AP_CTRL_SET(adv, MCD_AP_CTRL_ADV_MASK, MCD_AP_CTRL_1000Base_KX_SHIFT, val)

#define MCD_AP_CTRL_20GBase_KR2_SHIFT          (4)
#define MCD_AP_CTRL_20GBase_KR2_GET(adv)       MCD_AP_CTRL_GET(adv, MCD_AP_CTRL_ADV_MASK, MCD_AP_CTRL_20GBase_KR2_SHIFT)
#define MCD_AP_CTRL_20GBase_KR2_SET(adv, val)  MCD_AP_CTRL_SET(adv, MCD_AP_CTRL_ADV_MASK, MCD_AP_CTRL_20GBase_KR2_SHIFT, val)

#define MCD_AP_CTRL_10GBase_KX2_SHIFT          (5)
#define MCD_AP_CTRL_10GBase_KX2_GET(adv)       MCD_AP_CTRL_GET(adv, MCD_AP_CTRL_ADV_MASK, MCD_AP_CTRL_10GBase_KX2_SHIFT)
#define MCD_AP_CTRL_10GBase_KX2_SET(adv, val)  MCD_AP_CTRL_SET(adv, MCD_AP_CTRL_ADV_MASK, MCD_AP_CTRL_10GBase_KX2_SHIFT, val)

#define MCD_AP_CTRL_ADV_ALL_MASK               (0xF)
#define MCD_AP_CTRL_ADV_ALL_SHIFT              (0)
#define MCD_AP_CTRL_ADV_ALL_GET(adv)           MCD_AP_CTRL_GET(adv, MCD_AP_CTRL_ADV_ALL_MASK, MCD_AP_CTRL_ADV_ALL_SHIFT)
#define MCD_AP_CTRL_ADV_ALL_SET(adv, val)      MCD_AP_CTRL_SET(adv, MCD_AP_CTRL_ADV_ALL_MASK, MCD_AP_CTRL_ADV_ALL_SHIFT, val)

/*
** Options
** [00:00] Flow Control Pause Enable
** [01:01] Flow Control Asm Direction
** [02:02] Remote Flow Control Pause Enable
** [03:03] Remote Flow Control Asm Direction
** [04:04] FEC Suppress En
** [05:05] FEC Request
** [06:07] Reserved
** [09:09] loopback Enable
** [10:15] Reserved
*/
#define MCD_AP_CTRL_FC_PAUSE_MASK              (0x1)
#define MCD_AP_CTRL_FC_PAUSE_SHIFT             (0)
#define MCD_AP_CTRL_FC_PAUSE_GET(opt)          MCD_AP_CTRL_GET(opt, MCD_AP_CTRL_FC_PAUSE_MASK, MCD_AP_CTRL_FC_PAUSE_SHIFT)
#define MCD_AP_CTRL_FC_PAUSE_SET(opt, val)     MCD_AP_CTRL_SET(opt, MCD_AP_CTRL_FC_PAUSE_MASK, MCD_AP_CTRL_FC_PAUSE_SHIFT, val)

#define MCD_AP_CTRL_FC_ASM_MASK                (0x1)
#define MCD_AP_CTRL_FC_ASM_SHIFT               (1)
#define MCD_AP_CTRL_FC_ASM_GET(opt)            MCD_AP_CTRL_GET(opt, MCD_AP_CTRL_FC_ASM_MASK, MCD_AP_CTRL_FC_ASM_SHIFT)
#define MCD_AP_CTRL_FC_ASM_SET(opt, val)       MCD_AP_CTRL_SET(opt, MCD_AP_CTRL_FC_ASM_MASK, MCD_AP_CTRL_FC_ASM_SHIFT, val)

#define MCD_AP_CTRL_REM_FC_PAUSE_MASK          (0x1)
#define MCD_AP_CTRL_REM_FC_PAUSE_SHIFT         (2)
#define MCD_AP_CTRL_REM_FC_PAUSE_GET(opt)      MCD_AP_CTRL_GET(opt, MCD_AP_CTRL_REM_FC_PAUSE_MASK, MCD_AP_CTRL_REM_FC_PAUSE_SHIFT)
#define MCD_AP_CTRL_REM_FC_PAUSE_SET(opt, val) MCD_AP_CTRL_SET(opt, MCD_AP_CTRL_REM_FC_PAUSE_MASK, MCD_AP_CTRL_REM_FC_PAUSE_SHIFT, val)

#define MCD_AP_CTRL_REM_FC_ASM_MASK            (0x1)
#define MCD_AP_CTRL_REM_FC_ASM_SHIFT           (3)
#define MCD_AP_CTRL_REM_FC_ASM_GET(opt)        MCD_AP_CTRL_GET(opt, MCD_AP_CTRL_REM_FC_ASM_MASK, MCD_AP_CTRL_REM_FC_ASM_SHIFT)
#define MCD_AP_CTRL_REM_FC_ASM_SET(opt, val)   MCD_AP_CTRL_SET(opt, MCD_AP_CTRL_REM_FC_ASM_MASK, MCD_AP_CTRL_REM_FC_ASM_SHIFT, val)

#define MCD_AP_CTRL_FEC_ABIL_MASK              (0x1)
#define MCD_AP_CTRL_FEC_ABIL_SHIFT             (4)
#define MCD_AP_CTRL_FEC_ABIL_GET(opt)          MCD_AP_CTRL_GET(opt, MCD_AP_CTRL_FEC_ABIL_MASK, MCD_AP_CTRL_FEC_ABIL_SHIFT)
#define MCD_AP_CTRL_FEC_ABIL_SET(opt, val)     MCD_AP_CTRL_SET(opt, MCD_AP_CTRL_FEC_ABIL_MASK, MCD_AP_CTRL_FEC_ABIL_SHIFT, val)

#define MCD_AP_CTRL_FEC_REQ_MASK               (0x1)
#define MCD_AP_CTRL_FEC_REQ_SHIFT              (5)
#define MCD_AP_CTRL_FEC_REQ_GET(opt)           MCD_AP_CTRL_GET(opt, MCD_AP_CTRL_FEC_REQ_MASK, MCD_AP_CTRL_FEC_REQ_SHIFT)
#define MCD_AP_CTRL_FEC_REQ_SET(opt, val)      MCD_AP_CTRL_SET(opt, MCD_AP_CTRL_FEC_REQ_MASK, MCD_AP_CTRL_FEC_REQ_SHIFT, val)

#define MCD_AP_CTRL_LB_EN_MASK                 (0x1)
#define MCD_AP_CTRL_LB_EN_SHIFT                (9)
#define MCD_AP_CTRL_LB_EN_GET(opt)             MCD_AP_CTRL_GET(opt, MCD_AP_CTRL_LB_EN_MASK, MCD_AP_CTRL_LB_EN_SHIFT)
#define MCD_AP_CTRL_LB_EN_SET(opt, val)        MCD_AP_CTRL_SET(opt, MCD_AP_CTRL_LB_EN_MASK, MCD_AP_CTRL_LB_EN_SHIFT, val)

/*
** AP Status Info
** ==============
**/

/*
** HCD Status
** [03:03] Found
** [04:04] ARBSmError
** [05:05] FEC Result
** [06:06] Flow Control Rx Result
** [07:07] Flow Control Tx Result
** [08:15] HCD Type ------------> [00:00] 40GBase KR4
** [16:16] HCD Interrupt Trigger  [01:01] 10GBase KR
** [17:17] Link Interrupt Trigger [02:02] 10GBase KX4
** [18:30] Reserved               [03:03] 1000Base KX
** [31:31] Link                   [04:04] 20GBase KR2
**                                [05:05] 10GBase KX2
*/

#define MCD_AP_ST_HCD_FOUND_MASK                 (0x1)
#define MCD_AP_ST_HCD_FOUND_SHIFT                (3)
#define MCD_AP_ST_HCD_FOUND_GET(hcd)             MCD_AP_CTRL_GET(hcd, MCD_AP_ST_HCD_FOUND_MASK, MCD_AP_ST_HCD_FOUND_SHIFT)
#define MCD_AP_ST_HCD_FOUND_SET(hcd, val)        MCD_AP_CTRL_SET(hcd, MCD_AP_ST_HCD_FOUND_MASK, MCD_AP_ST_HCD_FOUND_SHIFT, val)

#define MCD_AP_ST_AP_ERR_MASK                    (0x1)
#define MCD_AP_ST_AP_ERR_SHIFT                   (4)
#define MCD_AP_ST_AP_ERR_GET(hcd)                MCD_AP_CTRL_GET(hcd, MCD_AP_ST_AP_ERR_MASK, MCD_AP_ST_AP_ERR_SHIFT)
#define MCD_AP_ST_AP_ERR_SET(hcd, val)           MCD_AP_CTRL_SET(hcd, MCD_AP_ST_AP_ERR_MASK, MCD_AP_ST_AP_ERR_SHIFT, val)

#define MCD_AP_ST_HCD_FEC_RES_MASK               (0x3)
#define MCD_AP_ST_HCD_FEC_RES_SHIFT              (22)
#define MCD_AP_ST_HCD_FEC_RES_GET(hcd)           MCD_AP_CTRL_GET(hcd, MCD_AP_ST_HCD_FEC_RES_MASK, MCD_AP_ST_HCD_FEC_RES_SHIFT)
#define MCD_AP_ST_HCD_FEC_RES_SET(hcd, val)      MCD_AP_CTRL_SET(hcd, MCD_AP_ST_HCD_FEC_RES_MASK, MCD_AP_ST_HCD_FEC_RES_SHIFT, val)

#define MCD_AP_ST_HCD_FC_RX_RES_MASK             (0x1)
#define MCD_AP_ST_HCD_FC_RX_RES_SHIFT            (6)
#define MCD_AP_ST_HCD_FC_RX_RES_GET(hcd)         MCD_AP_CTRL_GET(hcd, MCD_AP_ST_HCD_FC_RX_RES_MASK, MCD_AP_ST_HCD_FC_RX_RES_SHIFT)
#define MCD_AP_ST_HCD_FC_RX_RES_SET(hcd, val)    MCD_AP_CTRL_SET(hcd, MCD_AP_ST_HCD_FC_RX_RES_MASK, MCD_AP_ST_HCD_FC_RX_RES_SHIFT, val)

#define MCD_AP_ST_HCD_FC_TX_RES_MASK             (0x1)
#define MCD_AP_ST_HCD_FC_TX_RES_SHIFT            (7)
#define MCD_AP_ST_HCD_FC_TX_RES_GET(hcd)         MCD_AP_CTRL_GET(hcd, MCD_AP_ST_HCD_FC_TX_RES_MASK, MCD_AP_ST_HCD_FC_TX_RES_SHIFT)
#define MCD_AP_ST_HCD_FC_TX_RES_SET(hcd, val)    MCD_AP_CTRL_SET(hcd, MCD_AP_ST_HCD_FC_TX_RES_MASK, MCD_AP_ST_HCD_FC_TX_RES_SHIFT, val)

#define MCD_AP_ST_HCD_TYPE_MASK                  (0xFF)
#define MCD_AP_ST_HCD_TYPE_SHIFT                 (8)
#define MCD_AP_ST_HCD_TYPE_GET(hcd)              MCD_AP_CTRL_GET(hcd, MCD_AP_ST_HCD_TYPE_MASK, MCD_AP_ST_HCD_TYPE_SHIFT)
#define MCD_AP_ST_HCD_TYPE_SET(hcd, val)         MCD_AP_CTRL_SET(hcd, MCD_AP_ST_HCD_TYPE_MASK, MCD_AP_ST_HCD_TYPE_SHIFT, val)

#define MCD_AP_ST_HCD_INT_TRIG_MASK              (0x1)
#define MCD_AP_ST_HCD_INT_TRIG_SHIFT             (16)
#define MCD_AP_ST_HCD_INT_TRIG_GET(hcd)          MCD_AP_CTRL_GET(hcd, MCD_AP_ST_HCD_INT_TRIG_MASK, MCD_AP_ST_HCD_INT_TRIG_SHIFT)
#define MCD_AP_ST_HCD_INT_TRIG_SET(hcd, val)     MCD_AP_CTRL_SET(hcd, MCD_AP_ST_HCD_INT_TRIG_MASK, MCD_AP_ST_HCD_INT_TRIG_SHIFT, val)

#define MCD_AP_ST_LINK_INT_TRIG_MASK             (0x1)
#define MCD_AP_ST_LINK_INT_TRIG_SHIFT            (17)
#define MCD_AP_ST_LINK_INT_TRIG_GET(hcd)         MCD_AP_CTRL_GET(hcd, MCD_AP_ST_LINK_INT_TRIG_MASK, MCD_AP_ST_LINK_INT_TRIG_SHIFT)
#define MCD_AP_ST_LINK_INT_TRIG_SET(hcd, val)    MCD_AP_CTRL_SET(hcd, MCD_AP_ST_LINK_INT_TRIG_MASK, MCD_AP_ST_LINK_INT_TRIG_SHIFT, val)

#define MCD_AP_ST_HCD_LINK_MASK                  (0x1)
#define MCD_AP_ST_HCD_LINK_SHIFT                 (31)
#define MCD_AP_ST_HCD_LINK_GET(hcd)              MCD_AP_CTRL_GET(hcd, MCD_AP_ST_HCD_LINK_MASK, MCD_AP_ST_HCD_LINK_SHIFT)
#define MCD_AP_ST_HCD_LINK_SET(hcd, val)         MCD_AP_CTRL_SET(hcd, MCD_AP_ST_HCD_LINK_MASK, MCD_AP_ST_HCD_LINK_SHIFT, val)

/*
** ARBSmStatus
** [00:00] ST_AN_ENABLE
** [01:01] ST_TX_DISABLE
** [02:02] ST_LINK_STAT_CK
** [03:03] ST_PARALLEL_FLT
** [04:04] ST_ABILITY_DET
** [05:05] ST_ACK_DETECT
** [06:06] ST_COMPLETE_ACK
** [07:07] ST_NP_WAIT
** [08:08] ST_AN_GOOD_CK
** [09:09] ST_AN_GOOD
** [10:10] ST_SERDES_WAIT
*/
#define MCD_AP_ST_ARB_FSM_MASK                   (0x7FF)
#define MCD_AP_ST_ARB_FSM_SHIFT                  (0)
#define MCD_AP_ST_ARB_FSM_GET(arb)               MCD_AP_CTRL_GET(arb, MCD_AP_ST_ARB_FSM_MASK, MCD_AP_ST_ARB_FSM_SHIFT)
#define MCD_AP_ST_ARB_FSM_SET(arb, val)          MCD_AP_CTRL_SET(arb, MCD_AP_ST_ARB_FSM_MASK, MCD_AP_ST_ARB_FSM_SHIFT, val)

/*
** AP Status
** [00:00] Signal Detect
** [01:01] CDR Lock
** [02:02] PCS Lock
** [03:07] Reserved

#define MCD_AP_ST_SD_MASK                        (0x1)
#define MCD_AP_ST_SD_SHIFT                       (0)
#define MCD_AP_ST_SD_GET(status)                 MCD_AP_CTRL_GET(arb, MCD_AP_ST_SD_MASK, MCD_AP_ST_SD_SHIFT)
#define MCD_AP_ST_SD_SET(status, val)            MCD_AP_CTRL_SET(arb, MCD_AP_ST_SD_MASK, MCD_AP_ST_SD_SHIFT, val)

#define MCD_AP_ST_CDR_LOCK_MASK                  (0x1)
#define MCD_AP_ST_CDR_LOCK_SHIFT                 (1)
#define MCD_AP_ST_CDR_LOCK_GET(status)           MCD_AP_CTRL_GET(arb, MCD_AP_ST_CDR_LOCK_MASK, MCD_AP_ST_CDR_LOCK_SHIFT)
#define MCD_AP_ST_CDR_LOCK_SET(status, val)      MCD_AP_CTRL_SET(arb, MCD_AP_ST_CDR_LOCK_MASK, MCD_AP_ST_CDR_LOCK_SHIFT, val)

#define MCD_AP_ST_PCS_LOCK_MASK                  (0x1)
#define MCD_AP_ST_PCS_LOCK_SHIFT                 (2)
#define MCD_AP_ST_PCS_LOCK_GET(status)           MCD_AP_CTRL_GET(arb, MCD_AP_ST_PCS_LOCK_MASK, MCD_AP_ST_PCS_LOCK_SHIFT)
#define MCD_AP_ST_PCS_LOCK_SET(status, val)      MCD_AP_CTRL_SET(arb, MCD_AP_ST_PCS_LOCK_MASK, MCD_AP_ST_PCS_LOCK_SHIFT, val)

*/


/* Port Control modules definition */
typedef enum
{
    MCD_M0_DEBUG           = 0,
    MCD_M1_SUPERVISOR      = 1,
    MCD_M2_PORT_MNG        = 2,
    MCD_M3_PORT_SM         = 3,
    MCD_M4_AP_PORT_MNG     = 4,
    MCD_M5_AP_PORT_DET     = 5,
    MCD_M5_AP_PORT_DET_EXT = 6,
    MCD_M6_GENERAL         = 7,
    MCD_MAX_MODULE         = 8

}MV_PORT_CTRL_MODULE;

#define MCD_LOG_ALL_PORT_DUMP (0xFF)
#define MCD_LOG_PARAM_UNUSED  (0x1F)
#define MCD_LOG_RESULT_MASK   (0x1)

#define MCD_LOG_MOD_MASK      (0x7)
#define MCD_LOG_MOD_SHIFT     (0)
#define MCD_LOG_MOD_SET(mod)  (mod & MCD_LOG_MOD_MASK)
#define MCD_LOG_MOD_GET(info) (info & MCD_LOG_MOD_MASK)

/*
** Reg Log Info
** +====================================================+===========+============+=======+========+
** + 31:16                                              + 15:11     + 10:06      + 05:03 + 02:00  +
** +====================================================+===========+============+=======+========+
** + Reg Value                                          + Reg Index + Port Index + State + Module +
** +====================================================+===========+============+=======+========+
*/
#define MCD_REG_LOG_STATE_MASK         (0x7)
#define MCD_REG_LOG_STATE_SHIFT        (3)
#define MCD_REG_LOG_STATE_SET(state)   (state << MCD_REG_LOG_STATE_SHIFT)
#define MCD_REG_LOG_STATE_GET(info)   ((info  >> MCD_REG_LOG_STATE_SHIFT) & MCD_REG_LOG_STATE_MASK)

#define MCD_REG_LOG_PORT_MASK          (0x1F)
#define MCD_REG_LOG_PORT_SHIFT         (6)
#define MCD_REG_LOG_PORT_SET(port)     (port << MCD_REG_LOG_PORT_SHIFT)
#define MCD_REG_LOG_PORT_GET(info)    ((info >> MCD_REG_LOG_PORT_SHIFT) & MCD_REG_LOG_PORT_MASK)

#define MCD_REG_LOG_IDX_MASK           (0x1F)
#define MCD_REG_LOG_IDX_SHIFT          (11)
#define MCD_REG_LOG_IDX_SET(reg)       (reg  << MCD_REG_LOG_IDX_SHIFT)
#define MCD_REG_LOG_IDX_GET(info)     ((info >> MCD_REG_LOG_IDX_SHIFT) & MCD_REG_LOG_IDX_MASK)

#define MCD_REG_LOG_VAL_MASK           (0xFFFF)
#define MCD_REG_LOG_VAL_SHIFT          (16)
#define MCD_REG_LOG_VAL_SET(val)       (val  << MCD_REG_LOG_VAL_SHIFT)
#define MCD_REG_LOG_VAL_GET(info)     ((info >> MCD_REG_LOG_VAL_SHIFT) & MCD_REG_LOG_VAL_MASK)

#define MCD_REG_LOG(state, port, reg, val) \
    (MCD_M0_DEBUG | \
     MCD_REG_LOG_STATE_SET(state) | \
     MCD_REG_LOG_PORT_SET(port)   | \
     MCD_REG_LOG_IDX_SET(reg)     | \
     MCD_REG_LOG_VAL_SET(val))

/*
** Supervisor Log Info
** +======================================================+======+=======+=======+=======+========+
** + 31:20                                                +  19  + 18:12 + 11:06 + 05:03 + 02:00  +
** +======================================================+======+=======+=======+=======+========+
** + Reserved                                             + Type + Port  + Msg   + State + Module +
** +======================================================+======+=======+=======+=======+========+
*/
#define MCD_SPV_LOG_STATE_MASK         (0x7)
#define MCD_SPV_LOG_STATE_SHIFT        (3)
#define MCD_SPV_LOG_STATE_SET(state)   (state << MCD_SPV_LOG_STATE_SHIFT)
#define MCD_SPV_LOG_STATE_GET(info)   ((info  >> MCD_SPV_LOG_STATE_SHIFT) & MCD_SPV_LOG_STATE_MASK)

#define MCD_SPV_LOG_MSG_MASK           (0x3F)
#define MCD_SPV_LOG_MSG_SHIFT          (6)
#define MCD_SPV_LOG_MSG_SET(msg)       (msg  << MCD_SPV_LOG_MSG_SHIFT)
#define MCD_SPV_LOG_MSG_GET(info)     ((info >> MCD_SPV_LOG_MSG_SHIFT) & MCD_SPV_LOG_MSG_MASK)

#define MCD_SPV_LOG_PORT_MASK          (0x7F)
#define MCD_SPV_LOG_PORT_SHIFT         (12)
#define MCD_SPV_LOG_PORT_SET(port)     (port << MCD_SPV_LOG_PORT_SHIFT)
#define MCD_SPV_LOG_PORT_GET(info)    ((info >> MCD_SPV_LOG_PORT_SHIFT) & MCD_SPV_LOG_PORT_MASK)

#define MCD_SPV_LOG_TYPE_MASK          (0x1)
#define MCD_SPV_LOG_TYPE_SHIFT         (19)
#define MCD_SPV_LOG_TYPE_SET(type)     (type << MCD_SPV_LOG_TYPE_SHIFT)
#define MCD_SPV_LOG_TYPE_GET(info)    ((info >> MCD_SPV_LOG_TYPE_SHIFT) & MCD_SPV_LOG_TYPE_MASK)

#define MCD_SPV_LOG(state, msg, port, type) \
    (MCD_M1_SUPERVISOR | \
     MCD_SPV_LOG_STATE_SET(state) | \
     MCD_SPV_LOG_MSG_SET(msg)     | \
     MCD_SPV_LOG_PORT_SET(port)   | \
     MCD_SPV_LOG_TYPE_SET(type))

/*
** Port Management Log Info
** +=============================================================+=======+=======+=======+========+
** + 31:17                                                       + 16:12 + 11:05 + 04:03 + 02:00  +
** +=============================================================+=======+=======+=======+========+
** + Reserved                                                    + Msg   + Port  + State + Module +
** +=============================================================+=======+=======+=======+========+
*/
#define MCD_PORT_MNG_LOG_STATE_MASK        (0x3)
#define MCD_PORT_MNG_LOG_STATE_SHIFT       (3)
#define MCD_PORT_MNG_LOG_STATE_SET(state)  (state << MCD_PORT_MNG_LOG_STATE_SHIFT)
#define MCD_PORT_MNG_LOG_STATE_GET(info)  ((info  >> MCD_PORT_MNG_LOG_STATE_SHIFT) & MCD_PORT_MNG_LOG_STATE_MASK)

#define MCD_PORT_MNG_LOG_PORT_MASK         (0x7F)
#define MCD_PORT_MNG_LOG_PORT_SHIFT        (5)
#define MCD_PORT_MNG_LOG_PORT_SET(port)    (port  << MCD_PORT_MNG_LOG_PORT_SHIFT)
#define MCD_PORT_MNG_LOG_PORT_GET(info)   ((info  >> MCD_PORT_MNG_LOG_PORT_SHIFT) & MCD_PORT_MNG_LOG_PORT_MASK)

#define MCD_PORT_MNG_MSG_MASK              (0x1F)
#define MCD_PORT_MNG_MSG_SHIFT             (12)
#define MCD_PORT_MNG_MSG_SET(msg)          (msg  << MCD_PORT_MNG_MSG_SHIFT)
#define MCD_PORT_MNG_MSG_GET(info)        ((info >> MCD_PORT_MNG_MSG_SHIFT) & MCD_PORT_MNG_MSG_MASK)

#define MCD_PORT_MNG_LOG(state, port, msg) \
    (MCD_M2_PORT_MNG | \
     MCD_PORT_MNG_LOG_STATE_SET(state) | \
     MCD_PORT_MNG_LOG_PORT_SET(port)   | \
     MCD_PORT_MNG_MSG_SET(msg))

/*
** Port State Machine Log Info
** +============================================================+=======+========+=======+========+
** + 31:18                                                      + 17:11 + 10:06  + 05:03 + 02:00  +
** +============================================================+=======+========+=======+========+
** + Reserved                                                   + Port  + Status + State + Module +
** +============================================================+=======+========+=======+========+
*/
#define MCD_PORT_SM_LOG_STATE_MASK          (0x7)
#define MCD_PORT_SM_LOG_STATE_SHIFT         (3)
#define MCD_PORT_SM_LOG_STATE_SET(state)    (state << MCD_PORT_SM_LOG_STATE_SHIFT)
#define MCD_PORT_SM_LOG_STATE_GET(info)    ((info  >> MCD_PORT_SM_LOG_STATE_SHIFT) & MCD_PORT_SM_LOG_STATE_MASK)

#define MCD_PORT_SM_LOG_STATUS_MASK         (0x1F)
#define MCD_PORT_SM_LOG_STATUS_SHIFT        (6)
#define MCD_PORT_SM_LOG_STATUS_SET(status)  (status   << MCD_PORT_SM_LOG_STATUS_SHIFT)
#define MCD_PORT_SM_LOG_STATUS_GET(info)   ((info  >> MCD_PORT_SM_LOG_STATUS_SHIFT) & MCD_PORT_SM_LOG_STATUS_MASK)

#define MCD_PORT_SM_LOG_PORT_MASK           (0x7F)
#define MCD_PORT_SM_LOG_PORT_SHIFT          (11)
#define MCD_PORT_SM_LOG_PORT_SET(port)      (port  << MCD_PORT_SM_LOG_PORT_SHIFT)
#define MCD_PORT_SM_LOG_PORT_GET(info)     ((info  >> MCD_PORT_SM_LOG_PORT_SHIFT) & MCD_PORT_SM_LOG_PORT_MASK)

#define MCD_PORT_SM_LOG(state, status, port) \
    (M3_PORT_SM | \
     MCD_PORT_SM_LOG_STATE_SET(state)   | \
     MCD_PORT_SM_LOG_STATUS_SET(status) | \
     MCD_PORT_SM_LOG_PORT_SET(port))

/*
** AP Port Management Log Info
** +============================================================+=======+========+=======+========+
** + 31:18                                                      + 17:11 + 10:06  + 05:03 + 02:00  +
** +============================================================+=======+========+=======+========+
** + Reserved                                                   + Port  + Status + State + Module +
** +============================================================+=======+========+=======+========+
*/
#define MCD_AP_PORT_MNG_LOG_STATE_MASK          (0x7)
#define MCD_AP_PORT_MNG_LOG_STATE_SHIFT         (3)
#define MCD_AP_PORT_MNG_LOG_STATE_SET(state)    (state  << MCD_AP_PORT_MNG_LOG_STATE_SHIFT)
#define MCD_AP_PORT_MNG_LOG_STATE_GET(info)    ((info   >> MCD_AP_PORT_MNG_LOG_STATE_SHIFT) & MCD_AP_PORT_MNG_LOG_STATE_MASK)

#define MCD_AP_PORT_MNG_LOG_STATUS_MASK         (0x1F)
#define MCD_AP_PORT_MNG_LOG_STATUS_SHIFT        (6)
#define MCD_AP_PORT_MNG_LOG_STATUS_SET(status)  (status << MCD_AP_PORT_MNG_LOG_STATUS_SHIFT)
#define MCD_AP_PORT_MNG_LOG_STATUS_GET(info)   ((info   >> MCD_AP_PORT_MNG_LOG_STATUS_SHIFT) & MCD_AP_PORT_MNG_LOG_STATUS_MASK)

#define MCD_AP_PORT_MNG_LOG_PORT_MASK           (0x7F)
#define MCD_AP_PORT_MNG_LOG_PORT_SHIFT          (11)
#define MCD_AP_PORT_MNG_LOG_PORT_SET(port)      (port   << MCD_AP_PORT_MNG_LOG_PORT_SHIFT)
#define MCD_AP_PORT_MNG_LOG_PORT_GET(info)     ((info   >> MCD_AP_PORT_MNG_LOG_PORT_SHIFT) & MCD_AP_PORT_MNG_LOG_PORT_MASK)

#define MCD_AP_PORT_MNG_LOG(state, status, port) \
    (MCD_M4_AP_PORT_MNG | \
     MCD_AP_PORT_MNG_LOG_STATE_SET(state)   | \
     MCD_AP_PORT_MNG_LOG_STATUS_SET(status) | \
     MCD_AP_PORT_MNG_LOG_PORT_SET(port))

/*
** AP Port State Machine Log Info
** +=================================================+==========+=======+========+=======+========+
** + 31:29                                           + 28:18    + 17:11 + 10:06  + 05:03 + 02:00  +
** +=================================================+==========+=======+========+=======+========+
** + Reserved                                        + AP HW SM + Port  + Status + State + Module +
** +=================================================+==========+=======+========+=======+========+
*/
#define MCD_AP_PORT_DET_LOG_STATE_MASK             (0x7)
#define MCD_AP_PORT_DET_LOG_STATE_SHIFT            (3)
#define MCD_AP_PORT_DET_LOG_STATE_SET(state)       (state    << MCD_AP_PORT_DET_LOG_STATE_SHIFT)
#define MCD_AP_PORT_DET_LOG_STATE_GET(info)       ((info     >> MCD_AP_PORT_DET_LOG_STATE_SHIFT) & MCD_AP_PORT_DET_LOG_STATE_MASK)

#define MCD_AP_PORT_DET_LOG_STATUS_MASK            (0x1F)
#define MCD_AP_PORT_DET_LOG_STATUS_SHIFT           (6)
#define MCD_AP_PORT_DET_LOG_STATUS_SET(status)     (status   << MCD_AP_PORT_DET_LOG_STATUS_SHIFT)
#define MCD_AP_PORT_DET_LOG_STATUS_GET(info)      ((info     >> MCD_AP_PORT_DET_LOG_STATUS_SHIFT) & MCD_AP_PORT_DET_LOG_STATUS_MASK)

#define MCD_AP_PORT_DET_LOG_PORT_MASK              (0x7F)
#define MCD_AP_PORT_DET_LOG_PORT_SHIFT             (11)
#define MCD_AP_PORT_DET_LOG_PORT_SET(port)         (port     << MCD_AP_PORT_DET_LOG_PORT_SHIFT)
#define MCD_AP_PORT_DET_LOG_PORT_GET(info)        ((info     >> MCD_AP_PORT_DET_LOG_PORT_SHIFT) & MCD_AP_PORT_DET_LOG_PORT_MASK)

#define MCD_AP_PORT_DET_LOG_HW_SM_MASK             (0x7FF)
#define MCD_AP_PORT_DET_LOG_HW_SM_SHIFT            (18)
#define MCD_AP_PORT_DET_LOG_HW_SM_SET(apHw)        (apHw    << MCD_AP_PORT_DET_LOG_HW_SM_SHIFT)
#define MCD_AP_PORT_DET_LOG_HW_SM_GET(info)       ((info    >> MCD_AP_PORT_DET_LOG_HW_SM_SHIFT) & MCD_AP_PORT_DET_LOG_HW_SM_MASK)

#define AP_PORT_SM_LOG(state, status, port, apHw) \
    (MCD_M5_AP_PORT_DET | \
     MCD_AP_PORT_DET_LOG_STATE_SET(state)   | \
     MCD_AP_PORT_DET_LOG_STATUS_SET(status) | \
     MCD_AP_PORT_DET_LOG_PORT_SET(port)     | \
     MCD_AP_PORT_DET_LOG_HW_SM_SET(apHw))

/*
** AP Port State Machine Extended Log Info - Defined in DB as 32bit HCD Status
** +==========+=======+==========+===========+=======+=======+=========+==========+=======+========+
** + 31       + 30:24 + 16:23    + 08:15     + 07    + 06    + 05      + 04       + 03    + 02:00  +
** +==========+=======+==========+===========+=======+=======+=========+==========+=======+========+
** + HCD Link + Port  + Reserved + Local HCD + FC TX + FC RX + FEC Res + ARBSmErr + Found + Module +
** +==========+=======+======|===+===========+=======+=======+=========+==========+=======+========+
**                           |
**                           | [16:16] HCD Interrupt Trigger
**                           | [17:17] Link Interrupt Trigger
*/
#define MCD_AP_PORT_DET_EXT_LOG_FOUND_MASK          (0x1)
#define MCD_AP_PORT_DET_EXT_LOG_FOUND_SHIFT         (3)
#define MCD_AP_PORT_DET_EXT_LOG_FOUND_GET(info)    ((info >> MCD_AP_PORT_DET_EXT_LOG_FOUND_SHIFT) & MCD_AP_PORT_DET_EXT_LOG_FOUND_MASK)

#define MCD_AP_PORT_DET_EXT_LOG_ARB_ERR_MASK        (0x1)
#define MCD_AP_PORT_DET_EXT_LOG_ARB_ERR_SHIFT       (4)
#define MCD_AP_PORT_DET_EXT_LOG_ARB_ERR_GET(info)  ((info >> MCD_AP_PORT_DET_EXT_LOG_ARB_ERR_SHIFT) & MCD_AP_PORT_DET_EXT_LOG_ARB_ERR_MASK)

#define MCD_AP_PORT_DET_EXT_LOG_FEC_RES_MASK        (0x1)
#define MCD_AP_PORT_DET_EXT_LOG_FEC_RES_SHIFT       (5)
#define MCD_AP_PORT_DET_EXT_LOG_FEC_RES_GET(info)  ((info >> MCD_AP_PORT_DET_EXT_LOG_FEC_RES_SHIFT) & MCD_AP_PORT_DET_EXT_LOG_FEC_RES_MASK)

#define MCD_AP_PORT_DET_EXT_LOG_RX_FC_MASK          (0x1)
#define MCD_AP_PORT_DET_EXT_LOG_RX_FC_SHIFT         (6)
#define MCD_AP_PORT_DET_EXT_LOG_RX_FC_GET(info)    ((info >> MCD_AP_PORT_DET_EXT_LOG_RX_FC_SHIFT) & MCD_AP_PORT_DET_EXT_LOG_RX_FC_MASK)

#define MCD_AP_PORT_DET_EXT_LOG_TX_FC_MASK          (0x1)
#define MCD_AP_PORT_DET_EXT_LOG_TX_FC_SHIFT         (7)
#define MCD_AP_PORT_DET_EXT_LOG_TX_FC_GET(info)    ((info >> MCD_AP_PORT_DET_EXT_LOG_TX_FC_SHIFT) & MCD_AP_PORT_DET_EXT_LOG_TX_FC_MASK)

#define MCD_AP_PORT_DET_EXT_LOG_HCD_MASK            (0xFF)
#define MCD_AP_PORT_DET_EXT_LOG_HCD_SHIFT           (8)
#define MCD_AP_PORT_DET_EXT_LOG_HCD_GET(info)      ((info >> MCD_AP_PORT_DET_EXT_LOG_HCD_SHIFT) & MCD_AP_PORT_DET_EXT_LOG_HCD_MASK)

#define MCD_AP_PORT_DET_EXT_LOG_HCD_INT_MASK        (0x1)
#define MCD_AP_PORT_DET_EXT_LOG_HCD_INT_SHIFT       (16)
#define MCD_AP_PORT_DET_EXT_LOG_HCD_INT_GET(info)  ((info >> MCD_AP_PORT_DET_EXT_LOG_HCD_INT_SHIFT) & MCD_AP_PORT_DET_EXT_LOG_HCD_INT_MASK)

#define MCD_AP_PORT_DET_EXT_LOG_LINK_INT_MASK       (0x1)
#define MCD_AP_PORT_DET_EXT_LOG_LINK_INT_SHIFT      (17)
#define MCD_AP_PORT_DET_EXT_LOG_LINK_INT_GET(info) ((info >> MCD_AP_PORT_DET_EXT_LOG_LINK_INT_SHIFT) & MCD_AP_PORT_DET_EXT_LOG_LINK_INT_MASK)

#define MCD_AP_PORT_DET_EXT_LOG_PORT_MASK           (0x7F)
#define MCD_AP_PORT_DET_EXT_LOG_PORT_SHIFT          (24)
#define MCD_AP_PORT_DET_EXT_LOG_PORT_SET(port)      (port << MCD_AP_PORT_DET_EXT_LOG_PORT_SHIFT)
#define MCD_AP_PORT_DET_EXT_LOG_PORT_GET(info)     ((info >> MCD_AP_PORT_DET_EXT_LOG_PORT_SHIFT) & MCD_AP_PORT_DET_EXT_LOG_PORT_MASK)

#define MCD_AP_PORT_DET_EXT_LOG_LINK_MASK           (0x1)
#define MCD_AP_PORT_DET_EXT_LOG_LINK_SHIFT          (31)
#define MCD_AP_PORT_DET_EXT_LOG_LINK_GET(info)     ((info >> MCD_AP_PORT_DET_EXT_LOG_LINK_SHIFT) & MCD_AP_PORT_DET_EXT_LOG_LINK_MASK)

#define MCD_AP_PORT_DET_LOG_EXT(hcdStatus, port) \
    (MCD_M5_AP_PORT_DET_EXT | \
     hcdStatus | \
     MCD_AP_PORT_DET_EXT_LOG_PORT_SET(port))

/*
** Port General Log Info
** +===========================================+========+========+=======+=======+=======+========+
** + 31:27                                     + 26:19  +   18   + 17:11 + 10:05 + 04:03 + 02:00  +
** +===========================================+========+========+=======+=======+=======+========+
** + Reserved                                  + Detail + Result + Port  + Msg   + State + Module +
** +===========================================+========+========+=======+=======+=======+========+
*/
#define PORT_GENERAL_LOG_STATE_MASK         (0x3)
#define PORT_GENERAL_LOG_STATE_SHIFT        (3)
#define PORT_GENERAL_LOG_STATE_SET(state)   (state << PORT_GENERAL_LOG_STATE_SHIFT)
#define PORT_GENERAL_LOG_STATE_GET(info)   ((info  >> PORT_GENERAL_LOG_STATE_SHIFT) & PORT_GENERAL_LOG_STATE_MASK)

#define PORT_GENERAL_LOG_MSG_MASK           (0x3F)
#define PORT_GENERAL_LOG_MSG_SHIFT          (5)
#define PORT_GENERAL_LOG_MSG_SET(msg)       (msg   << PORT_GENERAL_LOG_MSG_SHIFT)
#define PORT_GENERAL_LOG_MSG_GET(info)     ((info  >> PORT_GENERAL_LOG_MSG_SHIFT) & PORT_GENERAL_LOG_MSG_MASK)

#define PORT_GENERAL_LOG_PORT_MASK          (0x7F)
#define PORT_GENERAL_LOG_PORT_SHIFT         (11)
#define PORT_GENERAL_LOG_PORT_SET(port)     (port  << PORT_GENERAL_LOG_PORT_SHIFT)
#define PORT_GENERAL_LOG_PORT_GET(info)    ((info  >> PORT_GENERAL_LOG_PORT_SHIFT) & PORT_GENERAL_LOG_PORT_MASK)

#define PORT_GENERAL_LOG_RES_MASK           (0x1)
#define PORT_GENERAL_LOG_RES_SHIFT          (18)
#define PORT_GENERAL_LOG_RES_SET(result)    (result << PORT_GENERAL_LOG_RES_SHIFT)
#define PORT_GENERAL_LOG_RES_GET(info)     ((info   >> PORT_GENERAL_LOG_RES_SHIFT) & PORT_GENERAL_LOG_RES_MASK)

#define PORT_GENERAL_LOG_DETAIL_MASK        (0xFF)
#define PORT_GENERAL_LOG_DETAIL_SHIFT       (19)
#define PORT_GENERAL_LOG_DETAIL_SET(detail) (detail << PORT_GENERAL_LOG_DETAIL_SHIFT)
#define PORT_GENERAL_LOG_DETAIL_GET(info)  ((info   >> PORT_GENERAL_LOG_DETAIL_SHIFT) & PORT_GENERAL_LOG_DETAIL_MASK)

#define PORT_GENERAL_LOG(state, msg, port) \
    (M6_GENERAL | \
     PORT_GENERAL_LOG_STATE_SET(state) | \
     PORT_GENERAL_LOG_MSG_SET(msg)     | \
     PORT_GENERAL_LOG_PORT_SET(port))

#define PORT_GENERAL_LOG_RES(state, msg, port, result, detail) \
    (M6_GENERAL | \
     PORT_GENERAL_LOG_STATE_SET(state) | \
     PORT_GENERAL_LOG_MSG_SET(msg)     | \
     PORT_GENERAL_LOG_PORT_SET(port)   | \
     PORT_GENERAL_LOG_RES_SET(result)  | \
     PORT_GENERAL_LOG_DETAIL_SET(detail))

#define MCD_FW_HWS_LOG_STRING_SIZE 60

/* FW AP LOG Entry Structure Definition */
typedef struct
{
    MCD_U32 timestamp;
    MCD_U32 info;
}MCD_PORT_CTRL_LOG_ENTRY;

/* FW HWS LOG Entry Structure Definition */
typedef struct
{
    MCD_U32 timestamp;
    char   info[MCD_FW_HWS_LOG_STRING_SIZE];
}MCD_LOG_ENTRY;

/*******************************************************************
 MCD_U16 mcdApConvertHdc2V
*******************************************************************/
MCD_U16 mcdApConvertHdc2Vec
(
    MCD_AP_PORT_MODE apPortMode
);


MCD_OP_MODE mcdApConvertPortMode
(
    MCD_AP_PORT_MODE apPortMode
);

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
);

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
);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __mvHwsPortCtrlApLogDefs_H */


