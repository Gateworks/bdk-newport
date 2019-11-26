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
* @file mcdInternalPortApInitIf.h
*
* @brief API to configure and run 802.3ap Serdes AutoNeg engine
*
* @version   17
********************************************************************************
*/

#ifndef __mcdInternalPortApInitIf_H
#define __mcdInternalPortApInitIf_H

#ifdef __cplusplus
extern "C" {
#endif


#include "mcdApiTypes.h"
/*
 * IEEE capability vector
 if ($macro_mode eq '1x40G_KR4') {$adv_bitmap=$adv_bitmap+(1<<4);}
    if ($macro_mode eq '2x20G_KR2') {$adv_bitmap=$adv_bitmap+(1<<8);}
    if ($macro_mode eq '4x10G_KR') {$adv_bitmap=$adv_bitmap+(1<<5);}
    if ($macro_mode eq '4x1G') {$adv_bitmap=$adv_bitmap+(1<<7);}
    if ($macro_mode eq '2x10G_KX2') {$adv_bitmap=$adv_bitmap+(1<<9);}
    if ($macro_mode eq '1x10G_KX4') {$adv_bitmap=$adv_bitmap+(1<<6);}
    $master->Reg_Write('address' => 0x088c0000 + ($port*0x1000) + 0x400 + 0x13c,
 */
typedef enum
{
    MCD_1000Base_KX_Bit0 = 1, /* _1000Base_KX */
    MCD_10GBase_KX4_Bit1 = 2, /* _10GBase_KX4 */
    MCD_10GBase_KR_Bit2  = 4, /* _10GBase_KR */
    MCD_40GBase_KR4_Bit3 = 8, /* _40GBase_KR */
    MCD_40GBase_CR4_Bit4 = 16, /* not supported */
    MCD_100GBase_KR10_Bit5 = 32,/* not supported */

    MCD_LAST_ADV_MODE

}MCD_AP_CAPABILITY;

/*
 * Highest common denominator (HCD) results parameters:
 *   hcdFound         - indicating AP resolution completed
 *   hcdLinkStatus    - link status
 *   hcdResult        - the auto negotiation resolution
 *                       (bit location in IEEE capabilities vector)
 *   hcdPcsLockStatus - link/lock status form the relevant PCS/MAC
 *   hcdFec           - FEC negotiation resolution
 *   hcdFcRxPauseEn   - FC Rx pause resolution (true/false)
 *   hcdFcTxPauseEn   - FC Tx pause resolution (true/false)
*/
typedef struct
{
    MCD_BOOL                 hcdFound;
    MCD_U32                  hcdLinkStatus;
    MCD_U32                  hcdResult;
    MCD_U32                  hcdPcsLockStatus;
    MCD_FEC_TYPE             hcdFec;
    MCD_BOOL                 hcdFcRxPauseEn;
    MCD_BOOL                 hcdFcTxPauseEn;

}MCD_HCD_INFO;

/*
 * AP results information:
 *    preApPortNum - requested AP port number (not garante, if apLaneNum != 0)
 *    apLaneNum    - relative lane number
 *    postApPortNum - AP resolved port number (lane swap result)
 *    postApPortMode - port mode - result of auto negotiation
 *    hcdResult     - (HCD) results parameters
 *    smState       - State machine state
 *    smStatus      - State machine status
 *    arbStatus       ARB State machine status
*/
typedef struct
{
    MCD_U32                  preApPortNum;
    MCD_U32                  apLaneNum;
    MCD_U32                  postApPortNum;
    MCD_U32                  postApPortMode;
    MCD_HCD_INFO             hcdResult;
    MCD_U32                  smState;
    MCD_U32                  smStatus;
    MCD_U32                  arbStatus;

}MCD_AP_PORT_STATUS;

/*
 * AP statistics information:
 *    abilityCnt        - Number of Ability detect intervals executed
 *    abilitySuccessCnt - Number of Ability detect successfull intervals executed
 *    linkFailCnt       - Number of Link check fail intervals executed
 *    linkSuccessCnt    - Number of Link check successfull intervals executed
 *    hcdResoultionTime - Time duration for HCD resolution
 *    linkUpTime        - Time duration for Link up
*/
typedef struct
{
    MCD_U16 txDisCnt;
    MCD_U16 abilityCnt;
    MCD_U16 abilitySuccessCnt;
    MCD_U16 linkFailCnt;
    MCD_U16 linkSuccessCnt;
    MCD_U32 hcdResoultionTime;
    MCD_U32 linkUpTime;

}MCD_AP_PORT_STATS;

/*
 * AP introp information:
 *    attrBitMask            - Bit mask for attribute configuration:
 *                             0x1 - TX Disable,....,0x80 - PD_Max Interval
 *    txDisDuration          - Tx Disable duration in msec - default 60msec
 *    abilityDuration        - Ability detect duration in msec - default 5 msec
 *    abilityMaxInterval     - Ability detect max intervals - default 25 intervals ==> 5msec x 25 intervals = 125msec
 *    abilityFailMaxInterval - Ability detect max number of failed intervals where ST_AN_GOOD_CK was detected
 *                             But not resolution was found, trigger move to INIT state, instead of TX Disable in normal case
 *    apLinkDuration         - AP Link check duration in msec - default 10 msec
 *    apLinkMaxInterval      - AP Link check max intervals - default 50 intervals ==> 10msec x 50 intervals = 500msec
 *    pdLinkDuration         - PD Link check duration in msec - default 10 msec
 *    pdLinkMaxInterval      - PD Link check max intervals - default 25 intervals ==> 10msec x 25 intervals = 250msec
*/
typedef struct
{
    MCD_U16 attrBitMask;
    MCD_U16 txDisDuration;
    MCD_U16 abilityDuration;
    MCD_U16 abilityMaxInterval;
    MCD_U16 abilityFailMaxInterval;
    MCD_U16 apLinkDuration;
    MCD_U16 apLinkMaxInterval;
    MCD_U16 pdLinkDuration;
    MCD_U16 pdLinkMaxInterval;

}MCD_AP_PORT_INTROP;

/*
 * AP debug information:
 *    apFwBaseAddr       - AP Firmware Base address
 *    apFwLogBaseAddr    - AP Firmware Real-time log base address
 *    apFwLogCountAddr   - AP Firmware Real-time log count address
 *    apFwLogPointerAddr - AP Firmware Real-time log pointer address
 *    apFwLogResetAddr   - AP Firmware Real-time log reset address
*/
typedef struct
{
    MCD_U32 apFwBaseAddr;
    MCD_U32 apFwLogBaseAddr;
    MCD_U32 apFwLogCountAddr;
    MCD_U32 apFwLogPointerAddr;
    MCD_U32 apFwLogResetAddr;

}MCD_AP_PORT_DEBUG;


#ifdef __cplusplus
}
#endif

#endif /* mcdInternalPortApInitIf_H */




