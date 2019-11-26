/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions and data that are strictly internal
for the proper functioning of the API on the Marvell X7120/X6181/X6141 PHY.
********************************************************************/
#include "mydApiTypes.h"
#include "mydApiRegs.h"
#include "mydUtils.h"
#include "mydHwCntl.h"
#include "mydAPI.h"
#include "mydDiagnostics.h"
#include "mydIntrIOConfig.h"
#include "mydAPIInternal.h"
#include "mydFwDownload.h"
#include "mydInitialization.h"

#if DB_TEST_ENVIRONMENT
#include "time.h"
#include "stdio.h"
#endif

const MYD_U16 opModeTable[MYD_OP_MODE_COUNT][MYD_OP_TABLE_COUNT] =
   {{MYD_OP_MODE_UNKNOWN, 0, 0, 0, 0, 0, 0, 0x0},
  /* OP_MODE     SIGNALING         LANE_COUNT           MODE_MOD              FEC          MODE_TYPE      AN_TRAIN       SPEED      REG  */
    {MYD_P1X,    MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  MYD_MOD_1000BASE_X,    MYD_FEC_NONE,   MYD_PCS,  MYD_AN_TRAIN_OFF, MYD_1GB,   0x8020},
    {MYD_P1S,    MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  MYD_MOD_SGMII_SYS,     MYD_FEC_NONE,   MYD_PCS,  MYD_AN_TRAIN_OFF, MYD_1GB,   0x8320},
    {MYD_P1P,    MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  MYD_MOD_SGMII_PHY,     MYD_FEC_NONE,   MYD_PCS,  MYD_AN_TRAIN_OFF, MYD_1GB,   0x8220}, 
    {MYD_P1K,    MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  MYD_MOD_1000BASE_KX,   MYD_FEC_NONE,   MYD_PCS,  MYD_AN_TRAIN_ON,  MYD_1GB,   0x8120},
                                                                      
    {MYD_P2P5XN, MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  MYD_MOD_NONE,          MYD_FEC_NONE,   MYD_PCS,  MYD_AN_TRAIN_OFF, MYD_2P5GB, 0x8021},
    {MYD_P2P5XL, MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  MYD_MOD_2P5GBX_CL127,  MYD_FEC_NONE,   MYD_PCS,  MYD_AN_TRAIN_OFF, MYD_2P5GB, 0x8121},
    {MYD_P2P5XK, MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  MYD_MOD_2P5GBX_CL127,  MYD_FEC_NONE,   MYD_PCS,  MYD_AN_TRAIN_ON,  MYD_2P5GB, 0x8131},
                                                                      
    {MYD_P5L,    MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  MYD_MOD_NONE,          MYD_FEC_NONE,   MYD_PCS,  MYD_AN_TRAIN_OFF, MYD_5GB,   0x8022},
    {MYD_P5K,    MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  MYD_MOD_NONE,          MYD_FEC_NONE,   MYD_PCS,  MYD_AN_TRAIN_ON,  MYD_5GB,   0x8032},
                                                                      
    {MYD_P10LN,  MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  MYD_MOD_NONE,          MYD_FEC_NONE,   MYD_PCS,  MYD_AN_TRAIN_OFF, MYD_10GB,  0x8023},
    {MYD_P10KN,  MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  MYD_MOD_NONE,          MYD_FEC_NONE,   MYD_PCS,  MYD_AN_TRAIN_ON,  MYD_10GB,  0x8033},
    {MYD_P10KF,  MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  MYD_MOD_NONE,          MYD_FEC_KR,     MYD_PCS,  MYD_AN_TRAIN_ON,  MYD_10GB,  0x8073},
    {MYD_P10LF,  MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  MYD_MOD_NONE,          MYD_FEC_KR,     MYD_PCS,  MYD_AN_TRAIN_OFF, MYD_10GB,  0x8063},
                                                                      
    {MYD_P25YN,  MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE,  MYD_MOD_25GR2,         MYD_FEC_NONE,   MYD_PCS,  MYD_AN_TRAIN_OFF, MYD_25GB,  0x8C24},  
    {MYD_P25YF,  MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE,  MYD_MOD_25GR2,         MYD_FEC_KR,     MYD_PCS,  MYD_AN_TRAIN_OFF, MYD_25GB,  0x8C64},  
    {MYD_P25ZN,  MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE,  MYD_MOD_25GR2_MRVL,    MYD_FEC_NONE,   MYD_PCS,  MYD_AN_TRAIN_ON,  MYD_25GB,  0x8D34},  
    {MYD_P25ZF,  MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE,  MYD_MOD_25GR2_MRVL,    MYD_FEC_KR,     MYD_PCS,  MYD_AN_TRAIN_ON,  MYD_25GB,  0x8D74},  
    {MYD_P25AN,  MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE,  MYD_MOD_25GR4_MRVL,    MYD_FEC_NONE,   MYD_PCS,  MYD_AN_TRAIN_OFF, MYD_25GB,  0x8824},  
    {MYD_P25GN,  MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE,  MYD_MOD_25GR4_MRVL,    MYD_FEC_NONE,   MYD_PCS,  MYD_AN_TRAIN_ON,  MYD_25GB,  0x8834},  
    {MYD_P25GF,  MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE,  MYD_MOD_25GR4_MRVL,    MYD_FEC_KR,     MYD_PCS,  MYD_AN_TRAIN_ON,  MYD_25GB,  0x8874},  
    {MYD_P25HN,  MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE,  0x0900,                MYD_FEC_NONE,   MYD_PCS,  MYD_AN_TRAIN_ON,  MYD_25GB,  0x8934},  
    {MYD_P25HF,  MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE,  0x0900,                MYD_FEC_KR,     MYD_PCS,  MYD_AN_TRAIN_ON,  MYD_25GB,  0x8974},  
    {MYD_P25LN,  MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  MYD_MOD_NONE,          MYD_FEC_NONE,   MYD_PCS,  MYD_AN_TRAIN_OFF, MYD_25GB,  0x8024},  
    {MYD_P25LF,  MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  MYD_MOD_NONE,          MYD_FEC_KR,     MYD_PCS,  MYD_AN_TRAIN_OFF, MYD_25GB,  0x8064},  
    {MYD_P25LR,  MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  MYD_MOD_NONE,          MYD_FEC_KR,     MYD_PCS,  MYD_AN_TRAIN_OFF, MYD_25GB,  0x80A4},  
    {MYD_P25CN,  MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  MYD_MOD_NONE,          MYD_FEC_NONE,   MYD_PCS,  MYD_AN_TRAIN_ON,  MYD_25GB,  0x8034},  
    {MYD_P25CF,  MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  MYD_MOD_NONE,          MYD_FEC_KR,     MYD_PCS,  MYD_AN_TRAIN_ON,  MYD_25GB,  0x8074},  
    {MYD_P25CR,  MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  MYD_MOD_NONE,          MYD_FEC_RS_528, MYD_PCS,  MYD_AN_TRAIN_ON,  MYD_25GB,  0x80B4},  
    {MYD_P25BN,  MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  0x0200,                MYD_FEC_NONE,   MYD_PCS,  MYD_AN_TRAIN_ON,  MYD_25GB,  0x8234},
    {MYD_P25BF,  MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  0x0200,                MYD_FEC_KR,     MYD_PCS,  MYD_AN_TRAIN_ON,  MYD_25GB,  0x8274},
    {MYD_P25BR,  MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  0x0200,                MYD_FEC_RS_528, MYD_PCS,  MYD_AN_TRAIN_ON,  MYD_25GB,  0x82B4},
    {MYD_P25JN,  MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  0x0300,                MYD_FEC_NONE,   MYD_PCS,  MYD_AN_TRAIN_ON,  MYD_25GB,  0x8334},
    {MYD_P25JF,  MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  0x0300,                MYD_FEC_KR,     MYD_PCS,  MYD_AN_TRAIN_ON,  MYD_25GB,  0x8374},
    {MYD_P25JR,  MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE,  0x0300,                MYD_FEC_RS_528, MYD_PCS,  MYD_AN_TRAIN_ON,  MYD_25GB,  0x83B4},
                                                                     
    {MYD_P40LN,  MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE,  MYD_MOD_NONE,           MYD_FEC_NONE,   MYD_PCS, MYD_AN_TRAIN_OFF, MYD_40GB,   0x8025},               
    {MYD_P40CN,  MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE,  MYD_MOD_NONE,           MYD_FEC_NONE,   MYD_PCS, MYD_AN_TRAIN_ON,  MYD_40GB,   0x8035}, 
    {MYD_P40CF,  MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE,  MYD_MOD_NONE,           MYD_FEC_KR,     MYD_PCS, MYD_AN_TRAIN_ON,  MYD_40GB,   0x8075}, 
    {MYD_P40KN,  MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE,  0x0100,                 MYD_FEC_NONE,   MYD_PCS, MYD_AN_TRAIN_ON,  MYD_40GB,   0x8135}, 
    {MYD_P40KF,  MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE,  0x0100,                 MYD_FEC_KR,     MYD_PCS, MYD_AN_TRAIN_ON,  MYD_40GB,   0x8175}, 
    {MYD_P40LF,  MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE,  MYD_MOD_NONE,           MYD_FEC_KR,     MYD_PCS, MYD_AN_TRAIN_OFF, MYD_40GB,   0x8065}, 
    {MYD_P40BN,  MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE,  0x0400,                 MYD_FEC_NONE,   MYD_PCS, MYD_AN_TRAIN_ON,  MYD_40GB,   0x8435}, 
    {MYD_P40BF,  MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE,  0x0400,                 MYD_FEC_KR,     MYD_PCS, MYD_AN_TRAIN_ON,  MYD_40GB,   0x8475}, 
    {MYD_P40BR,  MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE,  0x0400,                 MYD_FEC_RS_528, MYD_PCS, MYD_AN_TRAIN_ON,  MYD_40GB,   0x84B5}, 
    {MYD_P40JN,  MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE,  0x0500,                 MYD_FEC_NONE,   MYD_PCS, MYD_AN_TRAIN_ON,  MYD_40GB,   0x8535}, 
    {MYD_P40JF,  MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE,  0x0500,                 MYD_FEC_KR,     MYD_PCS, MYD_AN_TRAIN_ON,  MYD_40GB,   0x8575}, 
    {MYD_P40JR,  MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE,  0x0500,                 MYD_FEC_RS_528, MYD_PCS, MYD_AN_TRAIN_ON,  MYD_40GB,   0x85B5}, 
                                                                                                    
    {MYD_P50LN,  MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE,  MYD_MOD_NONE,           MYD_FEC_NONE,   MYD_PCS, MYD_AN_TRAIN_OFF, MYD_50GB,   0x8026}, 
    {MYD_P50CN,  MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE,  MYD_MOD_NONE,           MYD_FEC_NONE,   MYD_PCS, MYD_AN_TRAIN_ON,  MYD_50GB,   0x8036}, 
    {MYD_P50CF,  MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE,  MYD_MOD_NONE,           MYD_FEC_KR,     MYD_PCS, MYD_AN_TRAIN_ON,  MYD_50GB,   0x8076}, 
    {MYD_P50KN,  MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE,  0x0100,                 MYD_FEC_NONE,   MYD_PCS, MYD_AN_TRAIN_ON,  MYD_50GB,   0x8136}, 
    {MYD_P50KF,  MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE,  0x0100,                 MYD_FEC_KR,     MYD_PCS, MYD_AN_TRAIN_ON,  MYD_50GB,   0x8176}, 
    {MYD_P50LF,  MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE,  MYD_MOD_NONE,           MYD_FEC_KR,     MYD_PCS, MYD_AN_TRAIN_OFF, MYD_50GB,   0x8066}, 
    {MYD_P50MN,  MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE,  0x0200,                 MYD_FEC_NONE,   MYD_PCS, MYD_AN_TRAIN_OFF, MYD_50GB,   0x8226}, 
    {MYD_P50MF,  MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE,  0x0200,                 MYD_FEC_KR,     MYD_PCS, MYD_AN_TRAIN_OFF, MYD_50GB,   0x8266}, 
    {MYD_P50MR,  MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE,  0x0200,                 MYD_FEC_RS_528, MYD_PCS, MYD_AN_TRAIN_OFF, MYD_50GB,   0x82A6}, 
    {MYD_P50BN,  MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE,  0x0200,                 MYD_FEC_NONE,   MYD_PCS, MYD_AN_TRAIN_ON,  MYD_50GB,   0x8236}, 
    {MYD_P50BF,  MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE,  0x0200,                 MYD_FEC_KR,     MYD_PCS, MYD_AN_TRAIN_ON,  MYD_50GB,   0x8276}, 
    {MYD_P50BR,  MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE,  0x0200,                 MYD_FEC_RS_528, MYD_PCS, MYD_AN_TRAIN_ON,  MYD_50GB,   0x82B6}, 
    {MYD_P50JN,  MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE,  0x0300,                 MYD_FEC_NONE,   MYD_PCS, MYD_AN_TRAIN_ON,  MYD_50GB,   0x8336}, 
    {MYD_P50JF,  MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE,  0x0300,                 MYD_FEC_KR,     MYD_PCS, MYD_AN_TRAIN_ON,  MYD_50GB,   0x8376}, 
    {MYD_P50JR,  MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE,  0x0300,                 MYD_FEC_RS_528, MYD_PCS, MYD_AN_TRAIN_ON,  MYD_50GB,   0x83B6}, 
    {MYD_P50UP,  MYD_SIGNAL_PAM4,  MYD_1_LANE_MODE,  0x0100,                 MYD_FEC_RS_544, MYD_PCS, MYD_AN_TRAIN_OFF, MYD_50GB,   0x81E6}, 
    {MYD_P50QP,  MYD_SIGNAL_PAM4,  MYD_1_LANE_MODE,  MYD_MOD_NONE,           MYD_FEC_RS_544, MYD_PCS, MYD_AN_TRAIN_ON,  MYD_50GB,   0x80F6}, 
                                             
    {MYD_P100LN, MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE,  MYD_MOD_NONE,           MYD_FEC_NONE,   MYD_PCS, MYD_AN_TRAIN_OFF, MYD_100GB,  0x8027},
    {MYD_P100LR, MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE,  MYD_MOD_NONE,           MYD_FEC_RS_528, MYD_PCS, MYD_AN_TRAIN_OFF, MYD_100GB,  0x80A7},
    {MYD_P100CR, MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE,  MYD_MOD_NONE,           MYD_FEC_RS_528, MYD_PCS, MYD_AN_TRAIN_ON,  MYD_100GB,  0x80B7},
    {MYD_P100KR, MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE,  0x0100,                 MYD_FEC_RS_528, MYD_PCS, MYD_AN_TRAIN_ON,  MYD_100GB,  0x81B7},
    {MYD_P100KN, MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE,  0x0100,                 MYD_FEC_NONE,   MYD_PCS, MYD_AN_TRAIN_ON,  MYD_100GB,  0x8037},
    {MYD_P100UP, MYD_SIGNAL_PAM4,  MYD_2_LANE_MODE,  0x0100,                 MYD_FEC_RS_544, MYD_PCS, MYD_AN_TRAIN_OFF, MYD_100GB,  0x81E7},
    {MYD_P100QP, MYD_SIGNAL_PAM4,  MYD_2_LANE_MODE,  MYD_MOD_NONE,           MYD_FEC_RS_544, MYD_PCS, MYD_AN_TRAIN_ON,  MYD_100GB,  0x80F7},
                                                                                                    
    {MYD_P200UP, MYD_SIGNAL_PAM4,  MYD_4_LANE_MODE,  MYD_MOD_NONE,           MYD_FEC_RS_544, MYD_PCS, MYD_AN_TRAIN_OFF, MYD_200GB,  0x80E8},
    {MYD_P200QP, MYD_SIGNAL_PAM4,  MYD_4_LANE_MODE,  MYD_MOD_NONE,           MYD_FEC_RS_544, MYD_PCS, MYD_AN_TRAIN_ON,  MYD_200GB,  0x80F8},
    
    {MYD_PCS_RESERVE_0, 0, 0, 0, 0, 0, 0, 0, 0x0},  /*  Reserved */
    {MYD_PCS_RESERVE_1, 0, 0, 0, 0, 0, 0, 0, 0x0},  /*  Reserved */
    {MYD_PCS_RESERVE_2, 0, 0, 0, 0, 0, 0, 0, 0x0},  /*  Reserved */
    {MYD_PCS_RESERVE_3, 0, 0, 0, 0, 0, 0, 0, 0x0},  /*  Reserved */
    {MYD_PCS_RESERVE_4, 0, 0, 0, 0, 0, 0, 0, 0x0},  /*  Reserved */
    {MYD_PCS_RESERVE_5, 0, 0, 0, 0, 0, 0, 0, 0x0},  /*  Reserved */
    {MYD_PCS_RESERVE_6, 0, 0, 0, 0, 0, 0, 0, 0x0},  /*  Reserved */
    {MYD_PCS_RESERVE_7, 0, 0, 0, 0, 0, 0, 0, 0x0},  /*  Reserved */
    {MYD_PCS_RESERVE_8, 0, 0, 0, 0, 0, 0, 0, 0x0},  /*  Reserved */
    {MYD_PCS_RESERVE_9, 0, 0, 0, 0, 0, 0, 0, 0x0},  /*  Reserved */
                                                      
    {MYD_PCS_RESERVE_10, 0, 0, 0, 0, 0, 0, 0, 0x0},  /* Reserved */
    {MYD_PCS_RESERVE_11, 0, 0, 0, 0, 0, 0, 0, 0x0},  /* Reserved */
    {MYD_PCS_RESERVE_12, 0, 0, 0, 0, 0, 0, 0, 0x0},  /* Reserved */
    {MYD_PCS_RESERVE_13, 0, 0, 0, 0, 0, 0, 0, 0x0},  /* Reserved */
    {MYD_PCS_RESERVE_14, 0, 0, 0, 0, 0, 0, 0, 0x0},  /* Reserved */
    {MYD_PCS_RESERVE_15, 0, 0, 0, 0, 0, 0, 0, 0x0},  /* Reserved */
    {MYD_PCS_RESERVE_16, 0, 0, 0, 0, 0, 0, 0, 0x0},  /* Reserved */
    {MYD_PCS_RESERVE_17, 0, 0, 0, 0, 0, 0, 0, 0x0},  /* Reserved */
    {MYD_PCS_RESERVE_18, 0, 0, 0, 0, 0, 0, 0, 0x0},  /* Reserved */
    {MYD_PCS_RESERVE_19, 0, 0, 0, 0, 0, 0, 0, 0x0},  /* Reserved */
                                                      
    {MYD_PCS_RESERVE_20, 0, 0, 0, 0, 0, 0, 0, 0x0},  /* Reserved */
    {MYD_PCS_RESERVE_21, 0, 0, 0, 0, 0, 0, 0, 0x0},  /* Reserved */
    {MYD_PCS_RESERVE_22, 0, 0, 0, 0, 0, 0, 0, 0x0},  /* Reserved */
    {MYD_PCS_RESERVE_23, 0, 0, 0, 0, 0, 0, 0, 0x0},  /* Reserved */
    {MYD_PCS_RESERVE_24, 0, 0, 0, 0, 0, 0, 0, 0x0},  /* Reserved */
    {MYD_PCS_RESERVE_25, 0, 0, 0, 0, 0, 0, 0, 0x0},  /* Reserved */
    {MYD_PCS_RESERVE_26, 0, 0, 0, 0, 0, 0, 0, 0x0},  /* Reserved */
    {MYD_PCS_RESERVE_27, 0, 0, 0, 0, 0, 0, 0, 0x0},  /* Reserved */
    {MYD_PCS_RESERVE_28, 0, 0, 0, 0, 0, 0, 0, 0x0},  /* Reserved */
    {MYD_PCS_RESERVE_29, 0, 0, 0, 0, 0, 0, 0, 0x0},  /* Reserved */

    /* Repeater mode starts here */
    {MYD_R1,     MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE, MYD_MOD_NONE,     MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_OFF, MYD_1GB,   0x8000}, 
                                         
    {MYD_R2P5,   MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE, MYD_MOD_NONE,     MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_OFF, MYD_2P5GB, 0x8001}, 
                                         
    {MYD_R5L,    MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE, MYD_MOD_NONE,     MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_OFF, MYD_5GB,   0x8002}, 
                                         
    {MYD_R10L,   MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE, MYD_MOD_NONE,     MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_OFF, MYD_10GB,   0x8003},  
    {MYD_R10K,   MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE, MYD_MOD_NONE,     MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_ON,  MYD_10GB,   0x8013},  
                                                                                                      
    {MYD_R25L,   MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE, MYD_MOD_NONE,     MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_OFF, MYD_25GB,   0x8004},  
    {MYD_R25C,   MYD_SIGNAL_NRZ,   MYD_1_LANE_MODE, MYD_MOD_NONE,     MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_ON,  MYD_25GB,   0x8014},  
                                                                                                     
    {MYD_R40L,   MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE, MYD_MOD_NONE,     MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_OFF, MYD_40GB,   0x8005},  
    {MYD_R40C,   MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE, MYD_MOD_R40G_CR4, MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_ON,  MYD_40GB,   0x8215},  
    {MYD_R40K,   MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE, MYD_MOD_R40G_KR4, MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_ON,  MYD_40GB,   0x8315},  
                                                                                                      
    {MYD_R50L,   MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE, 0x0200,           MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_OFF, MYD_50GB,   0x8206},  
    {MYD_R50C,   MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE, 0x0200,           MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_ON,  MYD_50GB,   0x8216},  
    {MYD_R50U,   MYD_SIGNAL_PAM4,  MYD_1_LANE_MODE, MYD_MOD_NONE,     MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_OFF, MYD_50GB,   0x8006},  
    {MYD_R50Q,   MYD_SIGNAL_PAM4,  MYD_1_LANE_MODE, MYD_MOD_NONE,     MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_ON,  MYD_50GB,   0x8016},  
                    
    {MYD_R100L,  MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE, MYD_MOD_NONE,     MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_OFF, MYD_100GB,  0x8007},  
    {MYD_R100C,  MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE, 0x0200,           MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_ON,  MYD_100GB,  0x8217},  
    {MYD_R100K,  MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE, 0x0300,           MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_ON,  MYD_100GB,  0x8317},  
    {MYD_R100U,  MYD_SIGNAL_PAM4,  MYD_2_LANE_MODE, 0x0800,           MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_OFF, MYD_100GB,  0x8807},  
    {MYD_R100Q,  MYD_SIGNAL_PAM4,  MYD_2_LANE_MODE, 0x0800,           MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_ON,  MYD_100GB,  0x8817},  
                                                                                                      
    {MYD_R200L,  MYD_SIGNAL_NRZ,   MYD_8_LANE_MODE, 0x0100,           MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_OFF, MYD_200GB,  0x8108},  
    {MYD_R200K,  MYD_SIGNAL_NRZ,   MYD_8_LANE_MODE, 0x0100,           MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_ON,  MYD_200GB,  0x8118},  
    {MYD_R200U,  MYD_SIGNAL_PAM4,  MYD_4_LANE_MODE, MYD_MOD_NONE,     MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_OFF, MYD_200GB,  0x8008},  
    {MYD_R200Q,  MYD_SIGNAL_PAM4,  MYD_4_LANE_MODE, MYD_MOD_NONE,     MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_ON,  MYD_200GB,  0x8018},  
                                                                                                     
    {MYD_R400U,  MYD_SIGNAL_PAM4,  MYD_8_LANE_MODE, MYD_MOD_NONE,     MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_OFF, MYD_400GB,  0x8009},  
    {MYD_R400Q,  MYD_SIGNAL_PAM4,  MYD_8_LANE_MODE, MYD_MOD_NONE,     MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_ON,  MYD_400GB,  0x8019},  
                    
    {MYD_R50LP,  MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE, 0x0200,           MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_OFF, MYD_50GB,   0x0000}, /* 0x8206 work-in-progress */ 
    {MYD_R50CP,  MYD_SIGNAL_NRZ,   MYD_2_LANE_MODE, 0x0200,           MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_ON,  MYD_50GB,   0x0000}, /* 0x8216 work-in-progress */ 
                                                                                                                                                      
    {MYD_R100LP, MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE, MYD_MOD_NONE,     MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_OFF, MYD_100GB,  0x0000}, /* 0x8007 work-in-progress */ 
    {MYD_R100CP, MYD_SIGNAL_NRZ,   MYD_4_LANE_MODE, 0x0200,           MYD_FEC_NONE, MYD_TRANSPARENT, MYD_AN_TRAIN_ON,  MYD_100GB,  0x0000}, /* 0x8217 work-in-progress */ 
                 
    {MYD_RXLA,   MYD_SIGNAL_NRZ,   0, 0,                0,            MYD_TRANSPARENT, 0,                0,          0x0},     
    {MYD_RXLB,   MYD_SIGNAL_NRZ,   0, 0,                0,            MYD_TRANSPARENT, 0,                0,          0x0},     

   };


/*******************************************************************************
 MYD_STATUS mydIsOpModeValid
    Check the host and line Op Mode if it is valid combination
*******************************************************************************/
MYD_STATUS mydIsOpModeValid
(
    IN MYD_DEV_PTR pDev,
    IN MYD_OP_MODE hostOpMode,
    IN MYD_OP_MODE lineOpMode
)
{
    MYD_U16 lineSpeed, hostSpeed, lineModeType, hostModeType;
    MYD_BOOL supported = MYD_FALSE;

    if ((lineOpMode >= MYD_OP_MODE_COUNT) || (hostOpMode >= MYD_OP_MODE_COUNT))
    {
        MYD_DBG_ERROR("mydIsOpModeValid: unsupported mode selection\n");
        return MYD_FAIL;
    }

    if ((lineOpMode != opModeTable[lineOpMode][MYD_OP_TABLE_OP_MODE]) ||
        (hostOpMode != opModeTable[hostOpMode][MYD_OP_TABLE_OP_MODE]))
    {
        MYD_DBG_ERROR("mydIsOpModeValid: opModeTable opMode mismatched lineOpMode:%u, \
                      hostOpMode:%u, lineTable:%u, hostTable:%u\n",
                      lineOpMode, hostOpMode,
                      opModeTable[lineOpMode][MYD_OP_TABLE_OP_MODE],
                      opModeTable[hostOpMode][MYD_OP_TABLE_OP_MODE]);

        return MYD_FAIL;
    }

    hostSpeed = opModeTable[hostOpMode][MYD_OP_TABLE_SPEED];
    hostModeType = opModeTable[hostOpMode][MYD_OP_TABLE_MODE_TYPE];

    lineSpeed = opModeTable[lineOpMode][MYD_OP_TABLE_SPEED];
    lineModeType = opModeTable[lineOpMode][MYD_OP_TABLE_MODE_TYPE];

    if (lineModeType != hostModeType)
    {
        MYD_DBG_ERROR("mydIsOpModeValid: Mixed PCS and Repeater modes is not supported\n");
        return MYD_FAIL;
    }

    switch(lineOpMode)
    {
        case MYD_OP_MODE_UNKNOWN:
        {
            MYD_DBG_ERROR("mydIsOpModeValid: unsupported line mode selection\n");
            break;
        }

        case MYD_P1X:
        {
            if ((hostOpMode == MYD_P1P) || (hostOpMode == MYD_P1X))
            {
                supported = MYD_TRUE;
            }
            break;
        }

        case MYD_P1P:
        {
            if (hostOpMode == MYD_P1X)
            {
                supported = MYD_TRUE;
            }
            break;
        }

        case MYD_P1S:
        {
            if (hostOpMode == MYD_P1P)
            {
                supported = MYD_TRUE;
            }
            break;
        }

        case MYD_P1K:
        {
            if (hostSpeed == MYD_1GB)
            {
                supported = MYD_TRUE;
            }
            break;
        }

        case MYD_P2P5XN:
        case MYD_P2P5XL:
        case MYD_P2P5XK:
        {
            if (hostSpeed == MYD_2P5GB)
            {
                supported = MYD_TRUE;
            }
            break;
        }

        case MYD_P5L:
        case MYD_P5K:
        {
            if (hostSpeed == MYD_5GB)
            {
                supported = MYD_TRUE;
            }
            break;
        }

        case MYD_P10LN:
        case MYD_P10KN:
        case MYD_P10KF:
        case MYD_P10LF:
        {
            if (hostSpeed == MYD_10GB)
            {
                supported = MYD_TRUE;
            }
            break;
        }

        case MYD_P25YN:
        case MYD_P25YF:
        case MYD_P25ZN:
        case MYD_P25ZF:
        case MYD_P25AN:
        case MYD_P25GN:
        case MYD_P25GF:
        case MYD_P25HN:
        case MYD_P25HF:
        {
            switch(hostOpMode)
            {
                case MYD_P25YN:
                case MYD_P25YF:
                case MYD_P25ZN:
                case MYD_P25ZF:
                case MYD_P25AN:
                case MYD_P25GN:
                case MYD_P25GF:
                case MYD_P25HN:
                case MYD_P25HF:
                    supported = MYD_TRUE;
                    break;

                default:
                    MYD_DBG_ERROR("mydIsOpModeValid: unsupported host mode selection!\n");
                    break;
            }
            break;
        }

        case MYD_P25LN:
        case MYD_P25LF:
        case MYD_P25LR:
        case MYD_P25CN:
        case MYD_P25CF:
        case MYD_P25CR:
        case MYD_P25BN:
        case MYD_P25BF:
        case MYD_P25BR:
        case MYD_P25JN:
        case MYD_P25JF:
        case MYD_P25JR:
        {
            if ((hostSpeed == MYD_25GB) || (hostSpeed == MYD_40GB))
            {
                supported = MYD_TRUE;
            }
            break;
        }

        case MYD_P40LN:
        case MYD_P40CN:
        case MYD_P40CF:
        case MYD_P40KN:
        case MYD_P40KF:
        case MYD_P40LF:
        case MYD_P40BN:
        case MYD_P40BF:
        case MYD_P40BR:
        case MYD_P40JN:
        case MYD_P40JF:
        case MYD_P40JR:
        {
            if (hostSpeed == MYD_40GB)
            {
                supported = MYD_TRUE;
            }
            break;
        }

        default:
            break;
    }

    if (lineModeType == MYD_PCS)
    {
        switch(lineSpeed)
        {
            case MYD_40GB:
            case MYD_50GB:
            case MYD_100GB:
            case MYD_200GB:
            {
                if (lineSpeed == hostSpeed)
                {
                    supported = MYD_TRUE;
                }
                break;
            }

            default:
                break;
        }
    }

    if ((lineModeType == MYD_PCS) && (supported == MYD_TRUE))
    {
        /* MYD_DBG_INFO("mydIsOpModeValid: supported PCS Line:%u and Host:%u mode combinations\n", hostOpMode, lineOpMode ); */
        return MYD_OK;
    }

    switch(lineOpMode)
    {
        case MYD_R1:
            if (hostOpMode == MYD_R1)
            {
                supported = MYD_TRUE;
            }
            break;

        case MYD_R2P5:
            if (hostOpMode == MYD_R2P5)
            {
                supported = MYD_TRUE;
            }
            break;

        case MYD_R5L:
            if (hostSpeed == MYD_5GB)
            {
                supported = MYD_TRUE;
            }
            break;

        case MYD_R10L:
            if ((hostOpMode == MYD_R10L) || (hostOpMode == MYD_R10K))
            {
                supported = MYD_TRUE;
            }
            break;

        case MYD_R10K:
            if (hostOpMode == MYD_R10L)
            {
                supported = MYD_TRUE;
            }
            break;

        case MYD_R25L:
            if ((hostOpMode == MYD_R25L) || (hostOpMode == MYD_R25C))
            {
                supported = MYD_TRUE;
            }
            break;

        case MYD_R25C:
            if (hostOpMode == MYD_R25L)
            {
                supported = MYD_TRUE;
            }
            break;

        case MYD_R40L:
            if ((hostOpMode == MYD_R40L) || (hostOpMode == MYD_R40C) || (hostOpMode == MYD_R40K))
            {
                supported = MYD_TRUE;
            }
            break;

        case MYD_R40C:
        case MYD_R40K:
            if (hostOpMode == MYD_R40L)
            {
                supported = MYD_TRUE;
            }
            break;

        case MYD_R50L:
            if (hostOpMode == MYD_R50L)
            {
                supported = MYD_TRUE;
            }
            break;

        case MYD_R50C:
            if (hostOpMode == MYD_R50L)
            {
                supported = MYD_TRUE;
            }
            break;

        case MYD_R50U:
            if ((hostOpMode == MYD_R50U) || (hostOpMode == MYD_R50Q))
            {
                supported = MYD_TRUE;
            }
            break;

        case MYD_R50Q:
            if (hostOpMode == MYD_R50U)
            {
                supported = MYD_TRUE;
            }
            break;

        case MYD_R100L:
            if ((hostOpMode == MYD_R100L) || (hostOpMode == MYD_R100C) || (hostOpMode == MYD_R100K))
            {
                supported = MYD_TRUE;
            }
            break;

        case MYD_R100C:
        case MYD_R100K:
            if (hostOpMode == MYD_R100L)
            {
                supported = MYD_TRUE;
            }
            break;

        case MYD_R100U:
            if ((hostOpMode == MYD_R100U) || (hostOpMode == MYD_R100Q))
            {
                supported = MYD_TRUE;
            }
            break;

        case MYD_R100Q:
            if (hostOpMode == MYD_R100U)
            {
                supported = MYD_TRUE;
            }
            break;

        case MYD_R200K:
        case MYD_R200L: /* TBD: MYD_R200L is host only */
           if (hostOpMode == MYD_R200L)
            {
                supported = MYD_TRUE;
            }
            break;

        case MYD_R200U:
            if ((hostOpMode == MYD_R200Q) || (hostOpMode == MYD_R200U))
            {
                supported = MYD_TRUE;
            }
            break;

        case MYD_R200Q:
            if (hostOpMode == MYD_R200U)
            {
                supported = MYD_TRUE;
            }
            break;

        case MYD_R400Q:
        case MYD_R400U: /* TBD: MYD_R400U is host only */
            if ((hostOpMode == MYD_R400U) && (pDev->portCount > 1))
            {
                supported = MYD_TRUE;
            }
            break;

        default:
            MYD_DBG_ERROR("mydIsOpModeValid: Mode not supported \n");
            break;
    }

    if (supported == MYD_TRUE)
    {
        /* MYD_DBG_INFO("mydIsOpModeValid: supported Repeater Host:%u and Line:%u mode combinations\n", hostOpMode, lineOpMode); */
        return MYD_OK;
    }

    MYD_DBG_ERROR("mydIsOpModeValid: unsupported Host:%u and Line:%u mode combinations\n", hostOpMode, lineOpMode);
    return MYD_FAIL;

}

/*******************************************************************************
 MYD_STATUS mydIsPortValid
    Check the MDIO port address if it is valid against the port address input
    during the mydInitDriver initialization
*******************************************************************************/
MYD_STATUS mydIsPortValid
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort
)
{
    if ((mdioPort < pDev->mdioPort) || (mdioPort >= (pDev->mdioPort + pDev->portCount)))
    {
        MYD_DBG_ERROR("mydIsPortValid: invalid mdioPort number\n");
        return MYD_FAIL;
    }

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydCheckOpModeLaneOffset
    Check if the lane offset is valid for the operational mode
*******************************************************************************/
MYD_STATUS mydCheckOpModeLaneOffset
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    IN MYD_OP_MODE opMode
)
{
    MYD_U16 laneCount;
    MYD_U16 mdioPortIndex = MYD_GET_PORT_IDX(pDev, mdioPort);
    MYD_BOOL supported = MYD_FALSE;

    laneCount = opModeTable[opMode][MYD_OP_TABLE_LANE_COUNT];

    switch(laneCount)
    {
        case MYD_1_LANE_MODE:
            if (laneOffset < MYD_NUM_LANES)
            {
                supported = MYD_TRUE;
            }
            break;

        case MYD_2_LANE_MODE:
            if ((laneOffset == 0) || (laneOffset == 2))
            {
                supported = MYD_TRUE;
            }
            else
            {
                MYD_DBG_ERROR("mydCheckOpModeLaneOffset: Error. 2-lane mode requires lane 0 or 2\n");
            }
            break;

        case MYD_4_LANE_MODE:
            if (laneOffset == 0)
            {
                supported = MYD_TRUE;
            }
            else
            {
                MYD_DBG_ERROR("mydCheckOpModeLaneOffset: Error. 4-lane mode requires lane 0\n");
            }
            break;

        case MYD_8_LANE_MODE:
            if ((laneOffset == 0) && (pDev->portCount > 1))
            {
                if ((mdioPortIndex == 0) || (mdioPortIndex == 2)) 
                {
                    supported = MYD_TRUE;
                }
                else
                {
                    MYD_DBG_ERROR("mydCheckOpModeLaneOffset: Error. 8-lane mode requires mdioPortIndex 0 or 2\n");
                }
            }
            else
            {
                MYD_DBG_ERROR("mydCheckOpModeLaneOffset: Error. 8-lane mode requires lane 0\n");
            }
            break;

        default:
            MYD_DBG_ERROR("mydCheckOpModeLaneOffset: Invalid lane used:%u \n", laneCount);
            break;
    }

    if (supported == MYD_TRUE)
    {
        return MYD_OK;
    }

    return MYD_FAIL;
}

/*******************************************************************************
 MYD_STATUS mydIsLaneOffsetValid
    Check if the lane offset is valid for the current mode setting of the
    given host or line side. Gets the current opMode and checks if the laneOffset
    is in range (0-3 for single lanes, 0 or 4 lanes, or 0,2 for 2 lane modes).
*******************************************************************************/
MYD_STATUS mydIsLaneOffsetValid
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset
)
{
    MYD_OP_MODE opMode;
    MYD_U16 laneCount;
    MYD_STATUS retStatus = MYD_FAIL;
    

    ATTEMPT(mydGetOpMode(pDev, mdioPort, host_or_line, laneOffset, &opMode));
    laneCount = opModeTable[opMode][MYD_OP_TABLE_LANE_COUNT];

    switch(laneCount)
    {
        case MYD_1_LANE_MODE:
            if (laneOffset < MYD_NUM_LANES)
            {
                retStatus = MYD_OK;
            }
            break;   

        case MYD_2_LANE_MODE:
            if (laneOffset == 0 || laneOffset == 2)
            {
                retStatus = MYD_OK;
            }
            break;

        case MYD_4_LANE_MODE: /* only checking the laneOffset is valid, not the MDIO port/lane offset combo */
        case MYD_8_LANE_MODE: /* for 8-lane mode can be port 0/1 or port 2/3, but needs to be lane 0 */
            if (laneOffset == 0)
            {
                retStatus = MYD_OK;
            }
            break;
            
        default:
            MYD_DBG_ERROR("mydIsLaneOffsetValid: Invalid lane selection:%u \n", laneCount);
            break;
    }

    return retStatus;
    
}


/*******************************************************************************
 MYD_STATUS mydCheckNeedReConfig
    Check if the new opMode on the laneOffset needs port re-configuration 
*******************************************************************************/
MYD_STATUS mydCheckNeedReConfig
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_OP_MODE opMode
)
{
    MYD_U16 mdioPortIndex = MYD_GET_PORT_IDX(pDev, mdioPort);
    MYD_U16 laneCount;
    MYD_U16 i, j;
    MYD_OP_MODE configMode;
    MYD_U16 configLaneCount;
    MYD_BOOL valid = MYD_FALSE;

    if (mydCheckOpModeLaneOffset(pDev, mdioPort, laneOffset, opMode) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydCheckNeedReConfig: incorrect lane Offset: %u\n", laneOffset);
        return MYD_FAIL;
    }

    laneCount = opModeTable[opMode][MYD_OP_TABLE_LANE_COUNT];

    configMode = (host_or_line == MYD_HOST_SIDE)? pDev->hostConfig[mdioPortIndex][laneOffset].opMode:
                                                  pDev->lineConfig[mdioPortIndex][laneOffset].opMode;

    configLaneCount = opModeTable[configMode][MYD_OP_TABLE_LANE_COUNT];

    switch(laneCount)
    {
        case MYD_1_LANE_MODE:
            if (configLaneCount == MYD_1_LANE_MODE || configLaneCount == 0)
            {
                valid = MYD_TRUE;
            }
            else
            {
                MYD_DBG_ERROR("mydCheckNeedReConfig: error setting 1-lane mode on existing %u-lane mode\n", configLaneCount);
            }
            break;

        case MYD_2_LANE_MODE:
            if (configLaneCount == MYD_2_LANE_MODE)
            {
                valid = MYD_TRUE;
                break;
            }

            for (i=0; i<MYD_2_LANE_MODE; i++)
            {
                configMode = (host_or_line == MYD_HOST_SIDE)? pDev->hostConfig[mdioPortIndex][laneOffset+i].opMode:
                                                              pDev->lineConfig[mdioPortIndex][laneOffset+i].opMode;

                configLaneCount = opModeTable[configMode][MYD_OP_TABLE_LANE_COUNT];

                if ((configLaneCount == 0) || (configLaneCount == MYD_2_LANE_MODE))
                {
                    continue;
                }
                else
                {
                    MYD_DBG_ERROR("mydCheckNeedReConfig: error setting 2-lane mode on existing %u-lane mode\n", configLaneCount);
                    return MYD_FAIL;
                }
            }

            valid = MYD_TRUE;
            break;

        case MYD_4_LANE_MODE:
            if (configLaneCount == MYD_4_LANE_MODE)
            {
                valid = MYD_TRUE;
                break;
            }

            for (i=0; i<MYD_NUM_LANES; i++)
            {
                configMode = (host_or_line == MYD_HOST_SIDE)? pDev->hostConfig[mdioPortIndex][laneOffset+i].opMode:
                                                              pDev->lineConfig[mdioPortIndex][laneOffset+i].opMode;

                configLaneCount = opModeTable[configMode][MYD_OP_TABLE_LANE_COUNT];

                if ((configLaneCount == 0) || (configLaneCount == MYD_4_LANE_MODE))
                {
                    continue;
                }
                else
                {
                    MYD_DBG_ERROR("mydCheckNeedReConfig: error setting 4-lane mode on existing %u-lane mode\n", configLaneCount);
                    return MYD_FAIL;
                }
            }

            valid = MYD_TRUE;
            break;

        case MYD_8_LANE_MODE:
            if (configLaneCount == MYD_8_LANE_MODE)
            {
                valid = MYD_TRUE;
                break;
            }

            for (j=0; j<2; j++) /* 8-lane mode uses 2 lanes */
            {
                for (i=0; i<MYD_NUM_LANES; i++)
                {
                    configMode = (host_or_line == MYD_HOST_SIDE)? pDev->hostConfig[mdioPortIndex+j][laneOffset+i].opMode:
                                                                  pDev->lineConfig[mdioPortIndex+j][laneOffset+i].opMode;

                    configLaneCount = opModeTable[configMode][MYD_OP_TABLE_LANE_COUNT];

                    if ((configLaneCount == 0) || (configLaneCount == MYD_8_LANE_MODE))
                    {
                        continue;
                    }
                    else
                    {
                        MYD_DBG_ERROR("mydCheckNeedReConfig: error setting 8-lane mode on existing %u-lane mode\n", configLaneCount);
                        return MYD_FAIL;
                    }
                }
            }

            valid = MYD_TRUE;
            break;
    
        default:
            MYD_DBG_ERROR("mydCheckNeedReConfig: incorrect lane Offset:%u or mode:%u\n", laneOffset, opMode);
            return MYD_FAIL;
    }

    return (valid == MYD_TRUE) ? MYD_OK : MYD_FAIL;
}


/*******************************************************************************
 MYD_STATUS mydCheckMixedOpModeSupport
    Check if mixed PCS and Repeater Op mode is supported in device or port
*******************************************************************************/
MYD_STATUS mydCheckMixedOpModeSupport
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    IN MYD_OP_MODE hostOpMode,
    IN MYD_OP_MODE lineOpMode
)
{
    MYD_U16 hostModeType, lineModeType;
    MYD_U16 laneIndex;

    hostModeType = opModeTable[hostOpMode][MYD_OP_TABLE_MODE_TYPE];
    lineModeType = opModeTable[lineOpMode][MYD_OP_TABLE_MODE_TYPE];

    if (hostModeType != lineModeType)
    {
        MYD_DBG_ERROR("mydCheckMixedOpModeSupport: Mixed PCS and Repeater modes unsupported: Host mode:%u Line mode:%u\n",
                       hostModeType, lineModeType);
        return MYD_FAIL;
    }

    /* Currently, the port is not supporting mixed PCS and Repeater */
    for (laneIndex=0; laneIndex < MYD_NUM_LANES; laneIndex++)
    {
        if (pDev->hostConfig[MYD_GET_PORT_IDX(pDev, mdioPort)][laneIndex].opMode != MYD_OP_MODE_UNKNOWN)
        {
            if (hostModeType != pDev->hostConfig[MYD_GET_PORT_IDX(pDev, mdioPort)][laneIndex].opModeType)
            {
                MYD_DBG_ERROR("mydCheckMixedOpModeSupport: Mixed PCS and Repeater modes unsupported: Host:%u Line:%u port:%u lane:%u\n", 
                                hostModeType, pDev->hostConfig[MYD_GET_PORT_IDX(pDev, mdioPort)][laneIndex].opModeType, mdioPort, laneIndex);
                return MYD_FAIL;
            }
        }
    }

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydSetConfigInfo
    Set the config info on the Line or Host config structure
    This call assumes all necessary checks are performed before
    calling this function. The laneOffset must be the 1st lane
    of the operational mode.
    For multi-port mode like the 400G 8-lane, the mdioPort must be 
    the 1st port.
*******************************************************************/
MYD_STATUS mydSetConfigInfo
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_OP_MODE opMode
)
{
    PMYD_MODE_CONFIG pModeConfig;
    MYD_U16 laneCount;
    MYD_U16 laneIndex;
    MYD_BOOL multiPortMode = MYD_FALSE;

    laneCount = opModeTable[opMode][MYD_OP_TABLE_LANE_COUNT];

    if (laneCount == MYD_8_LANE_MODE)
    {
        if ((pDev->portCount > 1) && (laneOffset == 0))
        {
            multiPortMode = MYD_TRUE;
            laneCount = MYD_4_LANE_MODE;
        }
        else
        {
            MYD_DBG_ERROR("mydSetConfigInfo: Error. 8-lane mode requires more than 1 port on laneOffset 0\n");
            return MYD_FAIL;
        }
    }

    for (laneIndex=laneOffset; laneIndex<(laneOffset+laneCount); laneIndex++)
    {
        if (host_or_line == MYD_HOST_SIDE)
        {
            pModeConfig = &pDev->hostConfig[MYD_GET_PORT_IDX(pDev, mdioPort)][laneIndex];
        }
        else
        {
            pModeConfig = &pDev->lineConfig[MYD_GET_PORT_IDX(pDev, mdioPort)][laneIndex];
        }

        pModeConfig->opMode = opMode;
        pModeConfig->speed = (MYD_SPEED)opModeTable[opMode][MYD_OP_TABLE_SPEED];
        pModeConfig->opModeType = opModeTable[opMode][MYD_OP_TABLE_MODE_TYPE];
        pModeConfig->signalType = opModeTable[opMode][MYD_OP_TABLE_SIGNAL];
        pModeConfig->typeFEC = opModeTable[opMode][MYD_OP_TABLE_FEC];
        pModeConfig->autoNeg = opModeTable[opMode][MYD_OP_TABLE_AN_TRAIN];
        pModeConfig->modeModifier = opModeTable[opMode][MYD_OP_TABLE_MODE_MOD];
        pModeConfig->laneCount = opModeTable[opMode][MYD_OP_TABLE_LANE_COUNT];
    }

    if (multiPortMode == MYD_TRUE)
    {
        mdioPort++;
        for (laneIndex=laneOffset; laneIndex<(laneOffset+laneCount); laneIndex++)
        {
            if (host_or_line == MYD_HOST_SIDE)
            {
                pModeConfig = &pDev->hostConfig[MYD_GET_PORT_IDX(pDev, mdioPort)][laneIndex];
            }
            else
            {
                pModeConfig = &pDev->lineConfig[MYD_GET_PORT_IDX(pDev, mdioPort)][laneIndex];
            }

            pModeConfig->opMode = opMode;
            pModeConfig->speed = (MYD_SPEED)opModeTable[opMode][MYD_OP_TABLE_SPEED];
            pModeConfig->opModeType = opModeTable[opMode][MYD_OP_TABLE_MODE_TYPE];
            pModeConfig->signalType = opModeTable[opMode][MYD_OP_TABLE_SIGNAL];
            pModeConfig->typeFEC = opModeTable[opMode][MYD_OP_TABLE_FEC];
            pModeConfig->autoNeg = opModeTable[opMode][MYD_OP_TABLE_AN_TRAIN];
            pModeConfig->modeModifier = opModeTable[opMode][MYD_OP_TABLE_MODE_MOD];
            pModeConfig->laneCount = opModeTable[opMode][MYD_OP_TABLE_LANE_COUNT];
        }
    }

    return MYD_OK;
}

/******************************************************************************
 MYD_STATUS mydGetDetailedLinkStatus
    Gets current and latched status for one side and lane of the interface based
    on the operating mode of that side/lane. 

    1G/2.5G = 3|4.3001
    10G/5G/25GR1 = 3|4.2001
    40G/50G/25GR2/25GR4 = 3|4.1001
    100G = 3|4.0001
    200G = 3|4.4001
 
    Lane 0:
    1; 10; 40; 100; 200
    2.5

    Lane 1:
    1; 10; 40
    5; 25R1

    Lane 2:
    1; 10; 40; 100

    Lane 3:
    1; 10; 40

    Speed Base  Link Register   Modes
     1G          3|4.0x3001       P1*
     2.5G        3|4.0x3001       P2p5**
     5G          3|4.0x2001       P5*
     10G         3|4.0x2001       P10**
     25GR1       3|4.0x2001       P25B/C/J/K/L*
     25GR2       3|4.0x1001       P25Y/Z*
     25GR4       3|4.0x1001       P25A/G/H*
     40GR2       3|4.0x1001       P40B/J*
     40GR4       3|4.0x1001       P40C/K/L*
     50GR1       3|4.0x1001       P50U/Q*
     50GR2       3|4.0x1001       P50B/J/M*
     50GR4       3|4.0x1001       P50C/K/L*
     100GR2      3|4.0x0001       P100U/Q*
     100GR4      3|4.0x0001       P100C/K/L*
     200GR4      3|4.0x4001       P200**
******************************************************************************/
MYD_STATUS mydGetDetailedLinkStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    IN MYD_U16 host_or_line,
    OUT MYD_U16 *currStat,
    OUT MYD_U16 *latchStat
)
{
    MYD_U16 modeType, laneCount, speed;
    MYD_OP_MODE opMode;

    if (host_or_line == MYD_HOST_SIDE)
    {
        opMode = pDev->hostConfig[MYD_GET_PORT_IDX(pDev, mdioPort)][laneOffset].opMode;
    }
    else
    {
        opMode = pDev->lineConfig[MYD_GET_PORT_IDX(pDev, mdioPort)][laneOffset].opMode;
    }

    speed     = opModeTable[opMode][MYD_OP_TABLE_SPEED];
    modeType  = opModeTable[opMode][MYD_OP_TABLE_MODE_TYPE];
    laneCount = opModeTable[opMode][MYD_OP_TABLE_LANE_COUNT];

    if (modeType != MYD_PCS)
    {
        MYD_DBG_ERROR("mydGetDetailedLinkStatus: Error. Link status for PCS mode only\n");
        return MYD_FAIL;
    }

    switch(speed)
    {
        case MYD_1GB:
        case MYD_2P5GB:
            ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, 
                                        MYD_PCS_1G_STATUS+(0x200*laneOffset), 2, 1, latchStat));
            ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, 
                                        MYD_PCS_1G_STATUS+(0x200*laneOffset), 2, 1, currStat));
            break;

        case MYD_5GB:
        case MYD_10GB:
            ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, 
                                        MYD_PCS_25G_STATUS+(0x200*laneOffset), 2, 1, latchStat));
            ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, 
                                        MYD_PCS_25G_STATUS+(0x200*laneOffset), 2, 1, currStat));
            break;

        case MYD_25GB:
        {
            if (laneCount == MYD_1_LANE_MODE)
            {
                ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, 
                                            MYD_PCS_25G_STATUS+(0x200*laneOffset), 2, 1, latchStat));
                ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, 
                                            MYD_PCS_25G_STATUS+(0x200*laneOffset), 2, 1, currStat));
            }
            else
            {
                ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, 
                                            MYD_PCS_40G_STATUS1+(0x200*laneOffset), 2, 1, latchStat));
                ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, 
                                            MYD_PCS_40G_STATUS1+(0x200*laneOffset), 2, 1, currStat));
            }
            break;
        }

        case MYD_40GB:
        case MYD_50GB: 
            ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, 
                                        MYD_PCS_40G_STATUS1+(0x200*laneOffset), 2, 1, latchStat));
            ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, 
                                        MYD_PCS_40G_STATUS1+(0x200*laneOffset), 2, 1, currStat));
            break;

        case MYD_100GB: 
            ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, 
                                        MYD_PCS_100G_STATUS1+(0x200*laneOffset), 2, 1, latchStat));
            ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, 
                                        MYD_PCS_100G_STATUS1+(0x200*laneOffset), 2, 1, currStat));
            break;

        case MYD_200GB:
            ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, MYD_PCS_200G_STATUS1, 2, 1, latchStat));
            ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, host_or_line, MYD_PCS_200G_STATUS1, 2, 1, currStat));
            break;

        default:
            MYD_DBG_ERROR("mydGetDetailedLinkStatus: unsupported speed:%d\n", speed);
            return MYD_FAIL;
            break;
    }

    return MYD_OK;
}


/*******************************************************************************
 MYD_STATUS mydReadPCSLinkStatus
    Check PCS link status
*******************************************************************************/
MYD_STATUS mydReadPCSLinkStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *currentStatus,
    OUT MYD_U16 *latchedStatus,
    OUT MYD_PCS_LINK_STATUS *statusDetail
)
{
    MYD_U16 curr_stat, latch_stat;

    /* only checking one lane */
    ATTEMPT(mydGetDetailedLinkStatus(pDev, mdioPort, laneOffset, MYD_HOST_SIDE, &curr_stat, &latch_stat));
    *currentStatus = statusDetail->hostCurrent = curr_stat;
    *latchedStatus = statusDetail->hostLatched = latch_stat;

    ATTEMPT(mydGetDetailedLinkStatus(pDev, mdioPort, laneOffset, MYD_LINE_SIDE, &curr_stat, &latch_stat));
    statusDetail->lineCurrent = curr_stat;
    statusDetail->lineLatched = latch_stat;

    *currentStatus &= curr_stat; /* combined status is host/line status AND together from both sides */
    *latchedStatus &= latch_stat;

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydReadRepeaterLinkStatus
    Check Serdes DSP lock status on the ports
    Returns status of all lanes on both host and line side.
*******************************************************************************/
MYD_STATUS mydReadRepeaterLinkStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    IN MYD_BOOL perLaneStatus,
    OUT MYD_U16 *CurrentStatus,
    OUT MYD_REPEATER_LINK_STATUS *statusDetail
)
{
    MYD_U16 i, hostDspLock, hostSigDetect, lineDspLock, lineSigDetect;
    MYD_U16 opModeType, laneCount;
    MYD_U16 mdioPortIndex = MYD_GET_PORT_IDX(pDev, mdioPort);

    opModeType = pDev->hostConfig[mdioPortIndex][laneOffset].opModeType;
    laneCount = pDev->hostConfig[mdioPortIndex][laneOffset].laneCount;

    if (opModeType != MYD_TRANSPARENT)
    {
        MYD_DBG_ERROR("mydReadRepeaterLinkStatus: incorrect/unsupported Repeater mode: %u\n", opModeType);
        return MYD_FAIL;
    }

    *CurrentStatus = 1;

    if (perLaneStatus == MYD_TRUE)
    {
        ATTEMPT(mydGetSerdesSignalDetectAndDspLock(pDev, mdioPort, MYD_HOST_SIDE, laneOffset, 
                &hostSigDetect, &hostDspLock));
        ATTEMPT(mydGetSerdesSignalDetectAndDspLock(pDev, mdioPort, MYD_LINE_SIDE, laneOffset, 
                &lineSigDetect, &lineDspLock));

        *CurrentStatus &= (hostDspLock & hostSigDetect & lineDspLock & lineSigDetect);
        statusDetail->hostCurrent[laneOffset] = (hostDspLock & hostSigDetect);
        statusDetail->lineCurrent[laneOffset] = (lineDspLock & lineSigDetect);
    }
    else
    {
        for (i=0; i<laneCount; i++)
        {
            ATTEMPT(mydGetSerdesSignalDetectAndDspLock(pDev, mdioPort, MYD_HOST_SIDE, i, 
                    &hostSigDetect, &hostDspLock));
            ATTEMPT(mydGetSerdesSignalDetectAndDspLock(pDev, mdioPort, MYD_LINE_SIDE, i, 
                    &lineSigDetect, &lineDspLock));

            *CurrentStatus &= (hostDspLock & hostSigDetect & lineDspLock & lineSigDetect);
            statusDetail->hostCurrent[i] = (hostDspLock & hostSigDetect);
            statusDetail->lineCurrent[i] = (lineDspLock & lineSigDetect);
        }

        if (laneCount == MYD_8_LANE_MODE)
        {
            for (i=4; i<MYD_8_LANE_MODE; i++) /* 4 lane from 2nd port on 400G */
            {
                ATTEMPT(mydGetSerdesSignalDetectAndDspLock(pDev, mdioPort+1, MYD_HOST_SIDE, i-4, 
                        &hostSigDetect, &hostDspLock));
                ATTEMPT(mydGetSerdesSignalDetectAndDspLock(pDev, mdioPort+1, MYD_LINE_SIDE, i-4, 
                        &lineSigDetect, &lineDspLock));

                *CurrentStatus &= (hostDspLock & hostSigDetect & lineDspLock & lineSigDetect);
                statusDetail->hostCurrent[i] = (hostDspLock & hostSigDetect);
                statusDetail->lineCurrent[i] = (lineDspLock & lineSigDetect);
            }
        }
    }

    return MYD_OK;
}

/* Mode signaling type */
#define MYD_HIGH_SPEED_PAM4 1
#define MYD_HIGH_SPEED_NRZ  2
#define MYD_LOW_SPEED_NRZ   3

/*******************************************************************
 MYD_STATUS mydHiLowNRZspeed
   Used internally to determine Hi/Low speed NRZ mode. 
   speedCheckNRZ = MYD_HIGH_SPEED_PAM4; not NRZ mode
   speedCheckNRZ = MYD_LOW_SPEED_NRZ; per lane 5G and lower
   speedCheckNRZ = MYD_HIGH_SPEED_NRZ; per lane 10G and higher

*******************************************************************/
MYD_STATUS mydHiLowNRZspeed
(
    IN MYD_OP_MODE opMode,
    OUT MYD_U16 *speedCheckNRZ
)
{
    MYD_U16 signaling, laneCount, speed;

    signaling  = opModeTable[opMode][MYD_OP_TABLE_SIGNAL];
    laneCount = opModeTable[opMode][MYD_OP_TABLE_LANE_COUNT];
    speed = opModeTable[opMode][MYD_OP_TABLE_SPEED];

    if (signaling == MYD_SIGNAL_PAM4)
    {
        *speedCheckNRZ = MYD_HIGH_SPEED_PAM4;
        return MYD_OK;
    }

    if (signaling == MYD_SIGNAL_NRZ)
    {
        if (speed > MYD_25GB)
        {
            *speedCheckNRZ = MYD_HIGH_SPEED_NRZ;
        }
        else if (speed == MYD_25GB)
        {
            if (laneCount == MYD_4_LANE_MODE)
            {
                *speedCheckNRZ = MYD_LOW_SPEED_NRZ;
            }
            else
            {
                *speedCheckNRZ = MYD_HIGH_SPEED_NRZ;
            }
        } 
        else if (speed == MYD_10GB)
        {
            *speedCheckNRZ = MYD_HIGH_SPEED_NRZ;
        }
        else if (speed <= MYD_5GB)
        {
            *speedCheckNRZ = MYD_LOW_SPEED_NRZ;
        }
        else
        {
            return MYD_FAIL;
        }
    }

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydWriteDataReg
   Used internally to set data reg for staging interrupts. 
*******************************************************************/
MYD_STATUS mydWriteDataReg
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 slotNum,
    IN MYD_U16 dataNum
)
{
    MYD_U16 baseReg = 0xF230 + (0x0080 * laneOffset);
    
    baseReg += slotNum;

    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, baseReg, dataNum));

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydWriteCodeReg
   Used internally to set code reg for staging interrupts. 
*******************************************************************/
MYD_STATUS mydWriteCodeReg
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 slotNum,
    IN MYD_U16 codeNum
)
{
    MYD_U16 baseReg = 0xF220 + (0x0080 * laneOffset);
    MYD_U16 tmpReg = slotNum / 2;
    MYD_U16 tmp = slotNum % 2;

    baseReg += tmpReg;

    if (tmp == 0)
    {
        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, baseReg, 0, 8, codeNum));
    }
    else
    {
        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, baseReg, 8, 8, codeNum));
    }

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydWriteStageReg
   Used internally to set stage reg for staging interrupts. 
*******************************************************************/
MYD_STATUS mydWriteStageReg
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 slotNum,
    IN MYD_U16 stageNum
)
{
    MYD_U16 baseReg = 0xF250 + (0x0080 * laneOffset);
    MYD_U16 tmpReg = slotNum / 4;
    MYD_U16 tmp = slotNum % 4;    

    baseReg += tmpReg;
    
    if (tmp == 0)
    {
        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, baseReg, 0, 4, stageNum));
    }
    else if (tmp == 1)
    {
        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, baseReg, 4, 4, stageNum));
    }
    else if (tmp == 2)
    {
        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, baseReg, 8, 4, stageNum));
    }
    else 
    {
        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, baseReg, 12, 4, stageNum));
    }

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydWriteCommandReg
   Used internally to set command reg for staging interrupts. 
*******************************************************************/
MYD_STATUS mydWriteCommandReg
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 isAneg,
    IN MYD_U16 slotNum,
    IN MYD_U16 techNum
)
{
    MYD_U16 baseReg = 0;
    MYD_U16 bits = 0;
    MYD_U16 tmpReg = slotNum / 16;
    MYD_U16 tmp = slotNum % 16;
    MYD_U16 temp;

    baseReg += tmpReg;
    
    if (isAneg)
    {
        baseReg = 0xF25A + (0x0080 * laneOffset);
        baseReg += tmpReg;
        bits |= 1<<tmp;
    }
    else if (techNum == MYD_HIGH_SPEED_PAM4)
    {
        if (tmpReg == 0)
        {
            baseReg = (0xF25E) + (0x0080 * laneOffset);
            bits |= 1<<tmp;
        }
        else
        {
            baseReg = 0xF259 + (0x0080 * laneOffset);
            bits |= 1<<(tmp+8);
        }
    }
    else if (techNum == MYD_HIGH_SPEED_NRZ)
    {
        baseReg = 0xF258 + (0x0080 * laneOffset);
        baseReg += tmpReg;
        bits |= 1<<tmp;
    }
    else 
    {
        if (tmpReg == 0)
        {
            baseReg = 0xF25F + (0x0080 * laneOffset);
            bits |= 1<<tmp;
        }
        else
        {
            baseReg = 0xF25B + (0x0080 * laneOffset);
            bits |= 1<<(tmp+8);
        }
    }

    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, baseReg, &temp));
    temp |= bits;
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, baseReg, temp));

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydGenerateInterruptNoStageValid
   Used internally to set staging interrupts. 

*******************************************************************/
MYD_STATUS mydGenerateInterruptNoStageValid
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 isAneg,
    IN MYD_U16 slotNum,
    IN MYD_U16 codeNum,
    IN MYD_U16 dataNum,
    IN MYD_U16 stageNum,
    IN MYD_U16 techNum
)
{
    ATTEMPT(mydWriteCodeReg(pDev, mdioPort, host_or_line, laneOffset, slotNum, codeNum));
    ATTEMPT(mydWriteDataReg(pDev, mdioPort, host_or_line, laneOffset, slotNum, dataNum));
    ATTEMPT(mydWriteStageReg(pDev, mdioPort, host_or_line, laneOffset, slotNum, stageNum));
    ATTEMPT(mydWriteCommandReg(pDev, mdioPort, host_or_line, laneOffset, isAneg, slotNum, techNum));

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydPortPowerUp
   Used internally for mode configuration. 
   Power down and reset mdioPort on both the host and line side
*******************************************************************/
MYD_STATUS mydPortPowerUp
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_OP_MODE opMode
)
{
    MYD_U16 laneCount, speed;

    laneCount = opModeTable[opMode][MYD_OP_TABLE_LANE_COUNT];
    speed     = opModeTable[opMode][MYD_OP_TABLE_SPEED];

    if (host_or_line == MYD_HOST_SIDE)
    {
        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_PWD_RESET, 6, 1, 0x0));
    }
    else
    {
        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_PWD_RESET, 14, 1, 0x0));
    }

    switch(speed)
    {
        case MYD_1GB:
        case MYD_2P5GB:
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x3000+(0x0200*laneOffset), 0x0140));
            break;

        case MYD_5GB:
        case MYD_10GB:
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x2000+(0x0200*laneOffset), 0x2040));
            break;

        case MYD_25GB: 
            if (laneCount == MYD_1_LANE_MODE)
            {
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_PCS_25G_CNTL+(0x0200*laneOffset), 0x2040));
            }
            else if (laneCount == MYD_2_LANE_MODE)
            {
                if (laneOffset == 0)
                {
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x1000, 0x204C));
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x3200, 0x0940));
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x2200, 0x2840));
                }
                else
                {
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x1400, 0x204C));
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x3600, 0x0940));
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x2600, 0x2840));
                }
            }
            else
            {
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x1000, 0x204C));
            }

            if (laneCount == MYD_4_LANE_MODE)
            {
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x3200, 0x0940));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x3400, 0x0940));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x3600, 0x0940));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x2200, 0x2840));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x2400, 0x2840));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x2600, 0x2840));

            }
            break;

        case MYD_40GB:
        case MYD_50GB:
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_PCS_40G_CNTL+(0x0200*laneOffset), 0x204C));
            if (laneCount == MYD_1_LANE_MODE)
            {
            }
            else if (laneCount == MYD_2_LANE_MODE)
            {
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x3200+(0x0200*laneOffset), 0x0940));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x2200+(0x0200*laneOffset), 0x2840));
            }
            else if (laneCount == MYD_4_LANE_MODE)
            {
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x3200, 0x0940));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x3400, 0x0940));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x3600, 0x0940));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x2200, 0x2840));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x2400, 0x2840));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x2600, 0x2840));
            }
            break;

        case MYD_100GB:
            if (laneCount == MYD_2_LANE_MODE)
            {
                if (laneOffset == 0)
                {
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_PCS_100G_CNTL, 0x204C));
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x3200, 0x0940));
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x2200, 0x2840));
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x1200, 0x284C));
                }
                else
                {
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, (MYD_PCS_100G_CNTL+0x0400), 0x204C));
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x3600, 0x0940));
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x2600, 0x2840));
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x1600, 0x284C));
                }
            }
            else
            {
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_PCS_100G_CNTL, 0x204C));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x3200, 0x0940));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x3400, 0x0940));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x3600, 0x0940));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x2200, 0x2840));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x2400, 0x2840));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x2600, 0x2840));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x1200, 0x284C));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x1400, 0x284C));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x1600, 0x284C));
            }
            break;

        case MYD_200GB:
        case MYD_400GB:
            if (speed == MYD_200GB)
            {
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_PCS_200G_CNTL, 0x2064));
            }
            else
            {
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, MYD_PCS_400G_CNTL, 0x204C));
            }
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x3200, 0x0940));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x3400, 0x0940));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x3600, 0x0940));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x2200, 0x2840));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x2400, 0x2840));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x2600, 0x2840));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x1200, 0x284C));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x1400, 0x284C));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0x1600, 0x284C));
            break;

        default:
            break;
    }

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydRestoreStart
   Used internally for mode configuration. 
   Restore the states for both the host and line sides
*******************************************************************/
MYD_STATUS mydRestoreStart
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_OP_MODE opMode
)
{
    MYD_U16 laneCount, speed;
    MYD_U16 temp;

    laneCount = opModeTable[opMode][MYD_OP_TABLE_LANE_COUNT];
    speed     = opModeTable[opMode][MYD_OP_TABLE_SPEED];

    switch(speed)
    {
        case MYD_1GB:
        case MYD_2P5GB:
        case MYD_5GB:
        case MYD_10GB:
        case MYD_25GB:
        case MYD_40GB:
        case MYD_50GB:
        case MYD_100GB:
            if (host_or_line == MYD_HOST_SIDE)
            {
                ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_CNTL_HOST+(0x0200*laneOffset), 12, 1, 0x0));
            
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_ADV2_HOST+(0x0200*laneOffset), &temp));
                temp &= 0x0C40;/* b0000 xx00 0x00 0000 */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_ADV2_HOST+(0x0200*laneOffset), temp));

                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_LANE_CTRL20_HOST+(0x0200*laneOffset), &temp));
                temp &= 0xFC4F;/* bxxxx xx00 0x00 xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_LANE_CTRL20_HOST+(0x0200*laneOffset), temp));

                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_ADV3_HOST+(0x0200*laneOffset), 0x0));

                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_LANE_CTRL21_HOST+(0x0200*laneOffset), 0x0));
            }
            else
            {
                ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_CNTL_LINE+(0x0200*laneOffset), 12, 1, 0x0));
            
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_ADV2_LINE+(0x0200*laneOffset), &temp));
                temp &= 0x0C40;/* b0000 xx00 0x00 0000 */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_ADV2_LINE+(0x0200*laneOffset), temp));
                
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_LANE_CTRL20_LINE+(0x0200*laneOffset), &temp));
                temp &= 0xFC4F;/* bxxxx xx00 0x00 xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_LANE_CTRL20_LINE+(0x0200*laneOffset), temp));

                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_ADV3_LINE+(0x0200*laneOffset), 0x0));

                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_LANE_CTRL21_LINE+(0x0200*laneOffset), 0x0));
            }
            break;

        case MYD_200GB:
        case MYD_400GB:
            if (host_or_line == MYD_HOST_SIDE)
            {
                ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_CNTL_HOST, 12, 1, 0x0));
            
                if (opMode == MYD_R200Q || opMode == MYD_P200QP)
                {
                    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_ADV2_HOST, &temp));
                    temp &= 0x0C40;/* b0000 xx00 0x00 0000 */
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_ADV2_HOST, temp));
                }
                else
                {
                    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_ADV2_HOST, &temp));
                    temp &= 0x0C40;/* b0000 xx00 0x00 0000 */
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_ADV2_HOST, temp));
                }

                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_LANE_CTRL20_HOST, &temp));
                temp &= 0xFC4F;/* bxxxx xx00 0x00 xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_LANE_CTRL20_HOST, temp));

                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_ADV3_HOST, 0x0));

                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_LANE_CTRL21_HOST, 0x0));
            }
            else
            {
                ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_CNTL_LINE, 12, 1, 0x0));
            
                if (opMode == MYD_R200Q || opMode == MYD_P200QP)
                {
                    
                    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_ADV2_LINE, &temp));
                    temp &= 0x0C40;/* b0000 xx00 0x00 0000 */
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_ADV2_LINE, temp));
                }
                else
                {
                    
                    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_ADV2_LINE, &temp));
                    temp &= 0x0C40;/* b0000 xx00 0x00 0000*/
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_ADV2_LINE, temp));
                }
                
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_LANE_CTRL20_LINE, &temp));
                temp &= 0xFC4F;/* bxxxx xx00 0x00 xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_LANE_CTRL20_LINE, temp));

                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_ADV3_LINE, 0x0));

                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_AUTONEG, MYD_AUTONEG_LANE_CTRL21_LINE, 0x0));
           }
            break;

        default:
            break;
    }

    switch(laneCount)
    {
        case MYD_4_LANE_MODE:
        case MYD_8_LANE_MODE:
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF378, 0x1));

            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF24F, 12, 4, 0x0));

            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF24E, 0x0));

            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF249, &temp));
            temp &= 0xBBD7;
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF249, temp));

            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF27F, 10, 1, 0x0));

            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF273, 0x0));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF276, 0x0));

            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF0B1, &temp));
            temp &= 0xFEFE; /* bxxxx xxx0 xxxx xxx0 */
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF0B1, temp));

            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF26E, 0, 8, 0x2A));

            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF06A, 0, 4, 0x0));

            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF26F, 1, 1, 0x0));

            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF20B, 9, 1, 0x1));

            if (host_or_line == MYD_HOST_SIDE)
            {
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, 0xD8FE, &temp));
                temp &= 0x0F0F; /* b0000 xxxx 0000 xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_PMA_DEV, 0xD8FE, temp));
            }
            else
            {
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, 0xC8FE, &temp));
                temp &= 0x0F0F; /* b0000 xxxx 0000 xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_PMA_DEV, 0xC8FE, temp));
            }

            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF263, 0x0));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF21A, 0x4444));
            break;

        case MYD_2_LANE_MODE:
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF378, 0x0));

            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset), 12, 4, 0x0));
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF2CF+(0x0080*laneOffset), 12, 4, 0x0));

            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF24E)+(0x0080*laneOffset), 0x0));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF2CE)+(0x0080*laneOffset), 0x0));

            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF249+(0x0080*laneOffset), &temp));
            temp &= 0xBBD7; /* bx0xx x0xx xx0x 0xxx */
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF249+(0x0080*laneOffset), temp));

            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF2C9+(0x0080*laneOffset), &temp));
            temp &= 0xBBD7; /* bx0xx x0xx xx0x 0xxx */
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF2C9+(0x0080*laneOffset), temp));

            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF27F+(0x0080*laneOffset), 10, 1, 0x0));
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF2FF+(0x0080*laneOffset), 10, 1, 0x0));

            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF273+(0x0080*laneOffset), 0x0));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF2F3+(0x0080*laneOffset), 0x0));

            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF276+(0x0080*laneOffset), 0x0));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF276+(0x0080*(laneOffset+1)), 0x0));

            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF0B1, &temp));
            temp &= 0xFEFE; /* bxxxx xxx0 xxxx xxx0 */
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF0B1, temp));

            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, (0xF26E)+(0x0080*laneOffset), 0, 8, 0x2A));
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, (0xF26E)+(0x0080*laneOffset)+0x0080, 0, 8, 0x2A));

            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF06A, (MYD_U8)laneOffset, 2, 0x0));

            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF26F+(0x0080*laneOffset), 1, 1, 0x0));
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF26F+(0x0080*(laneOffset+1)), 1, 1, 0x0));

            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF20B+(0x0080*laneOffset), 9, 1, 0x1));
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF20B+(0x0080*(laneOffset+1)), 9, 1, 0x1));

            if (host_or_line == MYD_HOST_SIDE)
            {
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, 0xD8FE, &temp));
                temp &= 0x0F0F; /* b0000 xxxx 0000 xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_PMA_DEV, 0xD8FE, temp));
            }
            else
            {
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, 0xC8FE, &temp));
                temp &= 0x0F0F; /* b0000 xxxx 0000 xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_PMA_DEV, 0xC8FE, temp));
            }

            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF263+(0x0080*laneOffset), 0x0));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF263+(0x0080*(laneOffset+1)), 0x0));

            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF21A+(0x0080*laneOffset), 0x4444));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF21A+(0x0080*(laneOffset+1)), 0x4444));
            break;

        case MYD_1_LANE_MODE:
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF378, 0x0));

            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset), 12, 4, 0x0));

            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF24E)+(0x0080*laneOffset), 0x0));

            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF249+(0x0080*laneOffset), &temp));
            temp &= 0xBBD7; /* bx0xx x0xx xx0x 0xxx */
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF249+(0x0080*laneOffset), temp));

            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF27F+(0x0080*laneOffset), 10, 1, 0x0));

            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF273+(0x0080*laneOffset), 0x0));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF276+(0x0080*laneOffset), 0x0));

            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF0B1, &temp));
            temp &= 0xFEFE; /* bxxxx xxx0 xxxx xxx0 */
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF0B1, temp));

            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, (0xF26E)+(0x0080*laneOffset), 0, 8, 0x2A));

            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF06A, (MYD_U8)laneOffset, 1, 0x0));

            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF26F+(0x0080*laneOffset), 1, 1, 0x0));

            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF20B+(0x0080*laneOffset), 9, 1, 0x1));

            if (host_or_line == MYD_HOST_SIDE)
            {
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, 0xD8FE, &temp));
                temp &= 0x0F0F; /* b0000 xxxx 0000 xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_PMA_DEV, 0xD8FE, temp));
            }
            else
            {
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PMA_DEV, 0xC8FE, &temp));
                temp &= 0x0F0F; /* b0000 xxxx 0000 xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_PMA_DEV, 0xC8FE, temp));
            }

            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF263+(0x0080*laneOffset), 0x0));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF21A+(0x0080*laneOffset), 0x4444));
            break;

        default:
            break;
    }

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydConfigAutoNeg
   Used internally for mode configuration. 
   Configures the AutoNeg and Training mode setting for the host or 
   line sides
*******************************************************************/
MYD_STATUS mydConfigAutoNeg
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_OP_MODE opMode,
    IN MYD_U16 enableFlag /* MYD_ENABLE or MYD_DISABLE */
)
{
    MYD_U16 autoNeg, modeType;
    MYD_U16 autoNegCntlReg, autoNegAdv2Reg, autoNegAdv3Reg;
    MYD_U16 autoNegCntlReg20, autoNegCntlReg21;

    autoNeg   = opModeTable[opMode][MYD_OP_TABLE_AN_TRAIN];
    modeType  = opModeTable[opMode][MYD_OP_TABLE_MODE_TYPE];

    if (autoNeg != MYD_AN_TRAIN_ON)
    {
        MYD_DBG_ERROR("mydConfigAutoNeg: OpMode AutoNeg not supported\n");
        return MYD_FAIL;
    }
    
    if (host_or_line == MYD_LINE_SIDE)
    {
        autoNegCntlReg = MYD_AUTONEG_CNTL_LINE;  /* 0x0000 */
        autoNegAdv2Reg = MYD_AUTONEG_ADV2_LINE;  /* 0x0011 */
        autoNegAdv3Reg = MYD_AUTONEG_ADV3_LINE;  /* 0x0012 */
        autoNegCntlReg20 = MYD_AUTONEG_LANE_CTRL20_LINE; /* 0x8014 */
        autoNegCntlReg21 = MYD_AUTONEG_LANE_CTRL21_LINE; /* 0x8015 */
    }
    else
    {
        autoNegCntlReg = MYD_AUTONEG_CNTL_HOST;  /* 0x1000 */
        autoNegAdv2Reg = MYD_AUTONEG_ADV2_HOST;  /* 0x1011 */
        autoNegAdv3Reg = MYD_AUTONEG_ADV3_HOST;  /* 0x1012 */
        autoNegCntlReg20 = MYD_AUTONEG_LANE_CTRL20_HOST; /* 09014 */
        autoNegCntlReg21 = MYD_AUTONEG_LANE_CTRL21_HOST; /* 09015 */
    }

    if (modeType == MYD_PCS)
    {
        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegCntlReg+(laneOffset*0x200), 12, 1, enableFlag));
    }

    switch(opMode)
    {
        case MYD_P1K:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv2Reg+(laneOffset*0x200), 5, 1, enableFlag));
            break;

        case MYD_P5K:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv3Reg+(laneOffset*0x200), 1, 1, enableFlag));
            break;

        case MYD_P2P5XK:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv3Reg+(laneOffset*0x200), 0, 1, enableFlag));
            break;

        case MYD_P10KF:
        case MYD_P10KN:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv2Reg+(laneOffset*0x200), 7, 1, enableFlag));
            break;

        case MYD_P25ZN:
        case MYD_P25ZF:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv3Reg+(laneOffset*0x200), 9, 1, enableFlag));
            break;

        case MYD_P25GN:
        case MYD_P25GF:
        case MYD_P25HN:
        case MYD_P25HF:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv3Reg, 10, 1, enableFlag));
            break;

        case MYD_P25CN:
        case MYD_P25CF:
        case MYD_P25CR:
            enableFlag = (enableFlag)?0x3:0;
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv2Reg+(laneOffset*0x200), 14, 2, enableFlag));
            break;

        case MYD_P25BN:
        case MYD_P25BF:
        case MYD_P25BR:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegCntlReg20+(laneOffset*0x200), 5, 1, enableFlag));
            break;

        case MYD_P25JN:
        case MYD_P25JF:
        case MYD_P25JR:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegCntlReg20+(laneOffset*0x200), 4, 1, enableFlag));
            break;

        case MYD_P40CN:
        case MYD_P40CF:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv2Reg+(laneOffset*0x200), 9, 1, enableFlag));
            break;

        case MYD_P40KN:
        case MYD_P40KF:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv2Reg+(laneOffset*0x200), 8, 1, enableFlag));
            break;

        case MYD_P40BN:
        case MYD_P40BF:
        case MYD_P40BR:
        case MYD_P40JN:
        case MYD_P40JF:
        case MYD_P40JR:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegCntlReg21+(laneOffset*0x200), 7, 1, enableFlag));
            break;

        case MYD_P50KF:
        case MYD_P50CN:
        case MYD_P50CF:
        case MYD_P50KN:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv3Reg, 11, 1, enableFlag));
            break;

        case MYD_P50BN:
        case MYD_P50BF:
        case MYD_P50BR:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegCntlReg20+(laneOffset*0x200), 9, 1, enableFlag));
            break;

        case MYD_P50JN:
        case MYD_P50JF:
        case MYD_P50JR:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegCntlReg20+(laneOffset*0x200), 8, 1, enableFlag));
            break;

        case MYD_P100CR:
        case MYD_P100KN:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv2Reg, 13, 1, enableFlag));
            break;

        case MYD_P100KR:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv2Reg, 12, 1, enableFlag));
            break;

        case MYD_P100QP:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv3Reg+(laneOffset*0x200), 3, 1, enableFlag));
            break;

        case MYD_P200QP:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv3Reg, 4, 1, enableFlag));
            break;

        case MYD_R10K:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv2Reg + (laneOffset * 0x200), 7, 1, enableFlag));
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv3Reg + (laneOffset * 0x200), 14, 2, enableFlag));
            break;

        case MYD_R25C:
            enableFlag = (enableFlag)?0x3:0;
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv2Reg+(laneOffset*0x200), 14, 2, enableFlag));
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegCntlReg20+(laneOffset*0x200), 4, 2, enableFlag));
            break;

        case MYD_R40C:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv2Reg, 9, 1, enableFlag));
            break;

        case MYD_R40K:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv2Reg, 8, 1, enableFlag));
            break;

        case MYD_R50C:
            enableFlag = (enableFlag)?0x3:0;
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegCntlReg20+(laneOffset*0x200), 8, 2, enableFlag));
            break;

        case MYD_P50QP:
        case MYD_R50Q:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv3Reg+(laneOffset*0x200), 2, 1, enableFlag));
            break;

        case MYD_R100C:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv2Reg, 13, 1, enableFlag));
            break;

        case MYD_R100K:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv2Reg, 12, 1, enableFlag));
            break;

        case MYD_R100Q:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv3Reg+(laneOffset*0x200), 3, 1, enableFlag));
            break;

        case MYD_R200K:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv2Reg, 4, 1, enableFlag));
            break;

        case MYD_R200Q:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv3Reg, 4, 1, enableFlag));
            break;

        default:
            break;
    }

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydModeInterruptMod
   Used internally for mode interrupt configuration. 
   Called by mydModeModifier to finalize the mode selection settings
*******************************************************************/
MYD_STATUS mydModeInterruptMod
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U32 modeOption,
    IN MYD_OP_MODE opMode
)
{
    MYD_U16 signaling, autoNeg, speed, modeType;
    MYD_U16 temp, baseReg, stageValidBits=0;
    MYD_U16 speedCheckNRZ, isAneg=0;

    signaling  = opModeTable[opMode][MYD_OP_TABLE_SIGNAL];
    autoNeg  = opModeTable[opMode][MYD_OP_TABLE_AN_TRAIN];
    speed = opModeTable[opMode][MYD_OP_TABLE_SPEED];
    modeType = opModeTable[opMode][MYD_OP_TABLE_MODE_TYPE];

    autoNeg  = MYD_AN_TRAIN_OFF; /* set to off - work-in-progress */

    ATTEMPT(mydHiLowNRZspeed(opMode, &speedCheckNRZ));

    stageValidBits = 0x0002;

    if ((signaling != MYD_SIGNAL_PAM4) && (speedCheckNRZ != MYD_HIGH_SPEED_NRZ))
    {
        return MYD_OK;
    }

    if ((modeType == MYD_TRANSPARENT) && (signaling == MYD_SIGNAL_PAM4 || (speed == MYD_25GB)))
    {
        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF273+(0x0080*laneOffset), &temp));
        temp |= 0x000F; /* xxxx xxxx xxxx 1111 */
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF273+(0x0080*laneOffset), temp));

        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF276+(0x0080*laneOffset), &temp));
        temp |= 0x0062; /* xxxx xxxx x11x xx1x */
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF276+(0x0080*laneOffset), temp));

        if (autoNeg == MYD_AN_TRAIN_ON)
        {
            baseReg = 0xF25D + (0x0080*laneOffset);
            isAneg = 1;
        }
        else
        {
            baseReg = 0xF25C + (0x0080*laneOffset);
        }

        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, baseReg, &temp));
        temp |= 0x0020;
        temp |= stageValidBits;
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, baseReg, temp));

        ATTEMPT(mydGenerateInterruptNoStageValid(pDev, mdioPort, host_or_line, laneOffset, isAneg, 0, 0x5, 0x28, 5, speedCheckNRZ));
        ATTEMPT(mydGenerateInterruptNoStageValid(pDev, mdioPort, host_or_line, laneOffset, isAneg, 1, 0x30, 0x70, 5, speedCheckNRZ));
        ATTEMPT(mydGenerateInterruptNoStageValid(pDev, mdioPort, host_or_line, laneOffset, isAneg, 2, 0x18, 0x80D2, 5, speedCheckNRZ));
        ATTEMPT(mydGenerateInterruptNoStageValid(pDev, mdioPort, host_or_line, laneOffset, isAneg, 3, 0x19, 0x3F1F, 5, speedCheckNRZ));
        ATTEMPT(mydGenerateInterruptNoStageValid(pDev, mdioPort, host_or_line, laneOffset, isAneg, 4, 0xB, 0x1, 5, speedCheckNRZ));
    }
    else
    {
        MYD_U16 baseReg = 0;

        if (autoNeg == MYD_AN_TRAIN_ON)
        {
            baseReg = 0xF25D + (0x0080*laneOffset);
        }
        else
        {
            baseReg = 0xF25C + (0x0080*laneOffset);
        }

        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, baseReg, &temp));
        temp |= stageValidBits;
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, baseReg, temp));

    }

    /* temperature ramping option for PAM4 */
    if ((signaling == MYD_SIGNAL_PAM4) && (modeOption & MYD_MODE_TEMPERATURE_RAMP))
    {
        ATTEMPT(mydGenerateInterruptNoStageValid(pDev, mdioPort, host_or_line, laneOffset, isAneg, 5,  0x2c, 0xd0d,  1, speedCheckNRZ));
        ATTEMPT(mydGenerateInterruptNoStageValid(pDev, mdioPort, host_or_line, laneOffset, isAneg, 6,  0x6c, 0x8,    1, speedCheckNRZ));
        ATTEMPT(mydGenerateInterruptNoStageValid(pDev, mdioPort, host_or_line, laneOffset, isAneg, 7,  0x2c, 0xd09,  1, speedCheckNRZ));
        ATTEMPT(mydGenerateInterruptNoStageValid(pDev, mdioPort, host_or_line, laneOffset, isAneg, 8,  0x6c, 0xfffd, 1, speedCheckNRZ));
        ATTEMPT(mydGenerateInterruptNoStageValid(pDev, mdioPort, host_or_line, laneOffset, isAneg, 9,  0x2c, 0x909,  1, speedCheckNRZ));
        ATTEMPT(mydGenerateInterruptNoStageValid(pDev, mdioPort, host_or_line, laneOffset, isAneg, 10, 0x6c, 0x2,    1, speedCheckNRZ));
        ATTEMPT(mydGenerateInterruptNoStageValid(pDev, mdioPort, host_or_line, laneOffset, isAneg, 11, 0x2c, 0x117,  1, speedCheckNRZ));
        ATTEMPT(mydGenerateInterruptNoStageValid(pDev, mdioPort, host_or_line, laneOffset, isAneg, 12, 0x6c, 0x295c, 1, speedCheckNRZ));
    }

    if ((signaling == MYD_SIGNAL_PAM4) || (speedCheckNRZ == MYD_HIGH_SPEED_NRZ))
    {
        ATTEMPT(mydGenerateInterruptNoStageValid(pDev, mdioPort, host_or_line, laneOffset, isAneg, 14, 0x2C, 0x90A, 1, speedCheckNRZ));
        ATTEMPT(mydGenerateInterruptNoStageValid(pDev, mdioPort, host_or_line, laneOffset, isAneg, 15, 0x6C, 0x5, 1, speedCheckNRZ));
    }

    if (signaling == MYD_SIGNAL_PAM4)
    {
        ATTEMPT(mydGenerateInterruptNoStageValid(pDev, mdioPort, host_or_line, laneOffset, isAneg, 16, 0x2c, 0x10D, 1, speedCheckNRZ));
        ATTEMPT(mydGenerateInterruptNoStageValid(pDev, mdioPort, host_or_line, laneOffset, isAneg, 17, 0x6c, 0x1, 1, speedCheckNRZ));

        ATTEMPT(mydGenerateInterruptNoStageValid(pDev, mdioPort, host_or_line, laneOffset, isAneg, 19, 0x2C, 0xD03, 1, speedCheckNRZ));
        ATTEMPT(mydGenerateInterruptNoStageValid(pDev, mdioPort, host_or_line, laneOffset, isAneg, 20, 0x6C, 0x2, 1, speedCheckNRZ));
        ATTEMPT(mydGenerateInterruptNoStageValid(pDev, mdioPort, host_or_line, laneOffset, isAneg, 21, 0xeC, 0x12, 1, speedCheckNRZ));
    }

   return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydModeCTLEEqualization
   Used internally for mode CTLE EQ configuration. 
*******************************************************************/
MYD_STATUS mydModeCTLEEqualization
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U32 modeOption,
    IN MYD_OP_MODE opMode
)
{
    MYD_U16 speed;
    MYD_U16 speedCheckNRZ;
    MYD_U16 baseReg;
    MYD_U16 regVal;

    MYD_U16 HF = 0x8;
    MYD_U16 LF = 0x0;

    speed = opModeTable[opMode][MYD_OP_TABLE_SPEED];

    ATTEMPT(mydHiLowNRZspeed(opMode, &speedCheckNRZ));

    if (speedCheckNRZ == MYD_HIGH_SPEED_NRZ)
    {
        if (speed != MYD_25GB)
        {
            LF = 0x6;
        }
    }
    else if (speedCheckNRZ == MYD_LOW_SPEED_NRZ)
    {
        HF = 0xA;
        LF = 0x3;
    }

    baseReg = 0xF22C + (0x80 * laneOffset);
    regVal = (HF << 8) + LF;
    
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, baseReg, regVal));

    baseReg = 0xF22D + (0x80 * laneOffset);
    if (speedCheckNRZ == MYD_HIGH_SPEED_PAM4)
    {
        regVal = 0x8F00;
    }
    else if (speedCheckNRZ == MYD_HIGH_SPEED_NRZ)
    {
        regVal = 0x4F00;
    }
    else
    {
        regVal = 0x2F00;
    }
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, baseReg, regVal));
        
    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydModeAdvancedEqualization
   Used internally for mode advance EQ configuration. 
*******************************************************************/
MYD_STATUS mydModeAdvancedEqualization
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U32 modeOption,
    IN MYD_OP_MODE opMode
)
{
    MYD_U16 signaling;
    MYD_U16 baseReg, regOffset;

    signaling  = opModeTable[opMode][MYD_OP_TABLE_SIGNAL];

    if (signaling != MYD_SIGNAL_PAM4)
    {
        return MYD_OK;
    }

    regOffset = 0x80;

    baseReg = 0xF208 + regOffset * laneOffset;
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, baseReg, 0x0109));

    baseReg = 0xF209 + regOffset * laneOffset;
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, baseReg, 0x0018));

    baseReg = 0xF20A + regOffset * laneOffset;
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, baseReg, 0x0D04));
    baseReg = 0xF246 + regOffset * laneOffset;
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, baseReg, 0x0008));

    baseReg = 0xF247 + regOffset * laneOffset;
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, baseReg, 0x0904));
    baseReg = 0xF22B + regOffset * laneOffset;
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, baseReg, 0x0002));

    baseReg = 0xF261 + regOffset * laneOffset;
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, baseReg, 0x0905));
    baseReg = 0xF262 + regOffset * laneOffset;
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, baseReg, 0x0002));

    baseReg = 0xF263 + regOffset * laneOffset;

    /* long or short channel option */
    if (modeOption & MYD_MODE_SHORT_CHANNEL)
    {
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, baseReg, 0x0));
    }
    else
    {
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, baseReg, 0x9FFF));
    }

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydModeModifierExtension
   Used internally for mode configuration. 
   Called by mydModeModifier to finalize the mode selection settings
*******************************************************************/
MYD_STATUS mydModeModifierExtension
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U32 modeOption,
    IN MYD_OP_MODE opMode
)
{
    MYD_U16 laneCount, speed;

    laneCount = opModeTable[opMode][MYD_OP_TABLE_LANE_COUNT];
    speed = opModeTable[opMode][MYD_OP_TABLE_SPEED];

    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF25C+(0x0080*laneOffset), 1, 1, 0x1));

    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF224+(0x0080*laneOffset), 0, 8, 0x26));
    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF224+(0x0080*laneOffset), 8, 8, 0x26));
    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF225+(0x0080*laneOffset), 0, 8, 0x26));

    {
        MYD_U16 slot8val = 0x2008;
        MYD_U16 slot9val = 0x2100;
        MYD_U16 slot10val = 0x230F;
        MYD_BOOL needSlot10 = MYD_FALSE;

        if (laneCount == 4)
        {
            if ((speed == MYD_40GB) || (speed == MYD_50GB))
            {
                slot9val = 0x2106;
            }
        }
        else if (laneCount == 2)
        {
            if (speed == MYD_25GB)
            {
                slot9val = 0x2106;
            }
        }
        else if (speed == MYD_10GB)
        {
            slot9val = 0x2106;
        }

        if ((laneCount == 4) && (speed == MYD_25GB))
        {
            slot8val = 0x200F;
            slot9val = 0x2100;
            needSlot10 = MYD_TRUE;
        }
        else if ((speed == MYD_1GB) || (speed == MYD_2P5GB))
        {
            slot8val = 0x200F;
            slot9val = 0x2100;
            needSlot10 = MYD_TRUE;
        }
        else if ((laneCount == 1) && (speed == MYD_5GB))
        {
            slot8val = 0x200F;
            slot9val = 0x2100;
            needSlot10 = MYD_TRUE;
        }

        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF238+(0x0080*laneOffset), slot8val));
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF239+(0x0080*laneOffset), slot9val));

        if (needSlot10 == MYD_TRUE)
        {
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF23A+(0x0080*laneOffset), slot10val));
        }
    }

    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF252+(0x0080*laneOffset), 0, 4, 0x1));
    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF252+(0x0080*laneOffset), 4, 4, 0x1));
    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF252+(0x0080*laneOffset), 8, 4, 0x1));

    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, (0xF25E)+(0x0080*laneOffset), 8, 1, 0x1));
    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, (0xF25E)+(0x0080*laneOffset), 9, 1, 0x1));
    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, (0xF25E)+(0x0080*laneOffset), 10, 1, 0x1));

    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF258+(0x0080*laneOffset), 8, 1, 0x1));
    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF258+(0x0080*laneOffset), 9, 1, 0x1));
    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF258+(0x0080*laneOffset), 10, 1, 0x1));

    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF25F+(0x0080*laneOffset), 8, 1, 0x1));
    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF25F+(0x0080*laneOffset), 9, 1, 0x1));
    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF25F+(0x0080*laneOffset), 10, 1, 0x1));

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydModeModifier
   Used internally for mode configuration. 
   Finalized the mode selection settings
*******************************************************************/
MYD_STATUS mydModeModifier
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U32 modeOption,
    IN MYD_OP_MODE opMode
)
{
    MYD_U16 signaling, laneCount, autoNeg, speed, modeType;
    MYD_U16 temp;

    signaling  = opModeTable[opMode][MYD_OP_TABLE_SIGNAL];
    laneCount = opModeTable[opMode][MYD_OP_TABLE_LANE_COUNT];
    autoNeg  = opModeTable[opMode][MYD_OP_TABLE_AN_TRAIN];
    speed = opModeTable[opMode][MYD_OP_TABLE_SPEED];
    modeType = opModeTable[opMode][MYD_OP_TABLE_MODE_TYPE];

    switch(laneCount)
    {
        case MYD_4_LANE_MODE:
        case MYD_8_LANE_MODE:
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF249, &temp));
            temp |= 0x4428; /* bx1xx x1xx xx1x 1xxx */
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF249, temp));

            if (modeOption & MYD_MODE_ICAL_EFFORT_0)
            {
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF24F, &temp));
                temp |= 0xF000; /* b1111 xxxx xxxx xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF24F, temp));

                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF24E, 0x0));
            }
            else if (modeOption & MYD_MODE_ICAL_EFFORT_1)
            {
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF24F, &temp));
                temp |= 0xF000; /* b1111 xxxx xxxx xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF24F, temp));

                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF24E, 0x1));
            }
            else if (modeOption & MYD_MODE_ICAL_EFFORT_0_FV)
            {
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF24F, &temp));
                temp |= 0xF000; /* b1111 xxxx xxxx xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF24F, temp));

                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF24E, 0x2));
            }
            else
            {
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF24F, &temp));
                temp |= 0xF000; /* b1111 xxxx xxxx xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF24F, temp));

                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF24E, 0x10));
            }

            if (signaling == MYD_SIGNAL_PAM4)
            {
                MYD_U16 cntlANReg;

                cntlANReg = (host_or_line == MYD_LINE_SIDE) ? 0x8001:0x9001;

                ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, cntlANReg+(0x0200*laneOffset), 9, 2, 0x01));
            }
            
            if (autoNeg == MYD_AN_TRAIN_ON)
            {
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF27F+(0x0080*laneOffset), &temp));
                temp |= 0x0400;
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF27F+(0x0080*laneOffset), temp));
            }

            if (modeType == MYD_TRANSPARENT)
            {
                if (signaling == MYD_SIGNAL_PAM4 || speed == MYD_25GB)
                {
                    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF06A, &temp));
                    temp |= 0x800F; 
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF06A, temp));

                    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF26F, 1, 1, 0x1));
                    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF20B, 9, 1, 0x0));
                }

                if ((signaling == MYD_SIGNAL_PAM4)&& (autoNeg != MYD_AN_TRAIN_ON))
                {
                    if (host_or_line == MYD_HOST_SIDE)
                    {
                        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, 0xD8FE, 12, 4, 0xF));
                    }
                    else
                    {
                        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, 0xC8FE, 12, 4, 0xF));
                    }
                }
            }

            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF273, 0x2));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF276, 0x10));

            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF0B1, &temp));
            temp |= 0x0101; /* bxxxx xxx1 xxxx xxx1 */
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF0B1, temp));

            if (opMode == MYD_P25AN)
            {
                if (host_or_line == MYD_HOST_SIDE)
                {
                    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, 0xD8FE, 4, 4, 0xF));
                }
                else
                {
                    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, 0xC8FE, 4, 4, 0xF));
                }
            }

            ATTEMPT(mydModeInterruptMod(pDev, mdioPort, host_or_line, laneOffset, modeOption, opMode));
            ATTEMPT(mydModeCTLEEqualization(pDev, mdioPort, host_or_line, laneOffset, modeOption, opMode));
            ATTEMPT(mydModeAdvancedEqualization(pDev, mdioPort, host_or_line, laneOffset, modeOption, opMode));
            break;

        case MYD_2_LANE_MODE:
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF249+(0x0080*laneOffset), &temp));
            temp |= 0x4428; /* bx1xx x1xx xx1x 1xxx */
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF249+(0x0080*laneOffset), temp));

            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF249+(0x0080*laneOffset)+0x0080, &temp));
            temp |= 0x4428; /* bx1xx x1xx xx1x 1xxx */
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF249+(0x0080*laneOffset)+0x0080, temp));

            if (modeOption & MYD_MODE_ICAL_EFFORT_0)
            {
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset), &temp));
                temp |= 0xF000; /* b1111 xxxx xxxx xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset), temp));

                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset)+0x0080, &temp));
                temp |= 0xF000; /* b1111 xxxx xxxx xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset)+0x0080, temp));

                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF24E)+(0x0080*laneOffset), 0x0));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF2CE)+(0x0080*laneOffset), 0x0));
            }
            else if (modeOption & MYD_MODE_ICAL_EFFORT_1)
            {
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset), &temp));
                temp |= 0xF000; /* b1111 xxxx xxxx xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset), temp));

                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset)+0x0080, &temp));
                temp |= 0xF000; /* b1111 xxxx xxxx xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset)+0x0080, temp));

                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF24E)+(0x0080*laneOffset), 0x1));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF2CE)+(0x0080*laneOffset), 0x1));
            }
            else if (modeOption & MYD_MODE_ICAL_EFFORT_0_FV)
            {
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset), &temp));
                temp |= 0xF000; /* b1111 xxxx xxxx xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset), temp));

                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset)+0x0080, &temp));
                temp |= 0xF000; /* b1111 xxxx xxxx xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset)+0x0080, temp));

                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF24E)+(0x0080*laneOffset), 0x2));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF2CE)+(0x0080*laneOffset), 0x2));
            }
            else
            {
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset), &temp));
                temp |= 0xF000; /* b1111 xxxx xxxx xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset), temp));

                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset)+0x0080, &temp));
                temp |= 0xF000; /* b1111 xxxx xxxx xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset)+0x0080, temp));

                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF24E)+(0x0080*laneOffset), 0x10));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF2CE)+(0x0080*laneOffset), 0x10));
            }

            if (signaling == MYD_SIGNAL_PAM4)
            {
                MYD_U16 cntlANReg;

                cntlANReg = (host_or_line == MYD_LINE_SIDE) ? 0x8001:0x9001;

                ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, cntlANReg+(0x0200*laneOffset), 9, 2, 0x01));
                ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, cntlANReg+(0x0200*(laneOffset+1)), 9, 2, 0x01));
            }

            if (autoNeg == MYD_AN_TRAIN_ON)
            {
                MYD_U16 temp1;

                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF27F+(0x0080*laneOffset), &temp));
                temp |= 0x0400;

                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF27F+(0x0080*(laneOffset+1)), &temp1));
                temp1 |= 0x0400;

                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF27F+(0x0080*laneOffset), temp));
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF27F+(0x0080*(laneOffset+1)), temp1));
            }

            if (modeType == MYD_TRANSPARENT)
            {
                if (signaling == MYD_SIGNAL_PAM4 || speed == MYD_25GB)
                {
                    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF06A, &temp));
                    temp |= 0x8000;
                    temp |= (1<<laneOffset);
                    temp |= (1<<(laneOffset+1));
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF06A, temp));

                    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF26F+(0x0080*laneOffset), 1, 1, 0x1));
                    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF26F+(0x0080*(laneOffset+1)), 1, 1, 0x1));

                    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF20B+(0x0080*laneOffset), 9, 1, 0x0));
                    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF20B+(0x0080*(laneOffset+1)), 9, 1, 0x0));
                }

                if ((signaling == MYD_SIGNAL_PAM4)&& (autoNeg != MYD_AN_TRAIN_ON))
                {
                    if (host_or_line == MYD_HOST_SIDE)
                    {
                        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, 0xD8FE, 12, 4, 0xF));
                    }
                    else
                    {
                        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, 0xC8FE, 12, 4, 0xF));
                    }
                }
            }

            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF273+(0x0080*laneOffset), 0x2));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF2F3+(0x0080*laneOffset), 0x2));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF276+(0x0080*laneOffset), 0x10));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF2F6+(0x0080*laneOffset), 0x10));

            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF0B1, &temp));
            temp |= 0x0101; /* bxxxx xxx1 xxxx xxx1 */
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF0B1, temp));

            ATTEMPT(mydModeInterruptMod(pDev, mdioPort, host_or_line, laneOffset, modeOption, opMode));
            ATTEMPT(mydModeInterruptMod(pDev, mdioPort, host_or_line, laneOffset+1, modeOption, opMode));

            ATTEMPT(mydModeCTLEEqualization(pDev, mdioPort, host_or_line, laneOffset, modeOption, opMode));
            ATTEMPT(mydModeCTLEEqualization(pDev, mdioPort, host_or_line, laneOffset+1, modeOption, opMode));

            ATTEMPT(mydModeAdvancedEqualization(pDev, mdioPort, host_or_line, laneOffset, modeOption, opMode));
            ATTEMPT(mydModeAdvancedEqualization(pDev, mdioPort, host_or_line, laneOffset+1, modeOption, opMode));
            break;

        case MYD_1_LANE_MODE:
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF249+(0x0080*laneOffset), &temp));
            temp |= 0x4428;
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF249+(0x0080*laneOffset), temp));

            if (modeOption & MYD_MODE_ICAL_EFFORT_0)
            {
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset), &temp));
                temp |= 0xF000; /* b1111 xxxx xxxx xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset), temp));

                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF24E)+(0x0080*laneOffset), 0x0));
            }
            else if (modeOption & MYD_MODE_ICAL_EFFORT_1)
            {
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset), &temp));
                temp |= 0xF000; /* b1111 xxxx xxxx xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset), temp));

                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF24E)+(0x0080*laneOffset), 0x1));
            }
            else if (modeOption & MYD_MODE_ICAL_EFFORT_0_FV)
            {
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset), &temp));
                temp |= 0xF000; /* b1111 xxxx xxxx xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset), temp));

                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF24E)+(0x0080*laneOffset), 0x2));
            }
            else
            {
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset), &temp));
                temp |= 0xF000; /* b1111 xxxx xxxx xxxx */
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF24F+(0x0080*laneOffset), temp));

                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, (0xF24E)+(0x0080*laneOffset), 0x10));
            }

            if (signaling == MYD_SIGNAL_PAM4)
            {
                MYD_U16 cntlANReg;

                cntlANReg = (host_or_line == MYD_LINE_SIDE) ? 0x8001:0x9001;

                ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, cntlANReg+(0x0200*laneOffset), 9, 2, 0x01));
            }

            if (autoNeg == MYD_AN_TRAIN_ON)
            {
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF27F+(0x0080*laneOffset), &temp));
                temp |= 0x0400;
                ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF27F+(0x0080*laneOffset), temp));
            }

            if (modeType == MYD_TRANSPARENT)
            {
                if (signaling == MYD_SIGNAL_PAM4 || speed == MYD_25GB)
                {
                    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF06A, &temp));
                    temp |= 0x8000;
                    temp |= (1<<laneOffset);
                    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF06A, temp));

                    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF26F+(0x0080*laneOffset), 1, 1, 0x1));
                    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xF20B+(0x0080*laneOffset), 9, 1, 0x0));
                }

                if ((signaling == MYD_SIGNAL_PAM4)&& (autoNeg != MYD_AN_TRAIN_ON))
                {
                    if (host_or_line == MYD_HOST_SIDE)
                    {
                        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, 0xD8FE, 12, 4, 0xF));
                    }
                    else
                    {
                        ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_PMA_DEV, 0xC8FE, 12, 4, 0xF));
                    }
                }
            }

            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF273+(0x0080*laneOffset), 0x2));
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF276+(0x0080*laneOffset), 0x10));

            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, 0xF0B1, &temp));
            temp |= 0x0101; /* bxxxx xxx1 xxxx xxx1 */
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, 0xF0B1, temp));

            ATTEMPT(mydModeInterruptMod(pDev, mdioPort, host_or_line, laneOffset, modeOption, opMode));
            ATTEMPT(mydModeCTLEEqualization(pDev, mdioPort, host_or_line, laneOffset, modeOption, opMode));
            ATTEMPT(mydModeAdvancedEqualization(pDev, mdioPort, host_or_line, laneOffset, modeOption, opMode));
            break;

        default:
            break;
    }

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydSetFecANConfig
  Used internally for mode configuration. 
  Configures the FEC mode selection settings
*******************************************************************/
MYD_STATUS mydSetFecANConfig
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_OP_MODE opMode
)
{
    MYD_U16 autoNegAdv3Reg;
    MYD_U16 autoNegCntlReg21;

    if (host_or_line == MYD_LINE_SIDE)
    {
        autoNegAdv3Reg = MYD_AUTONEG_ADV3_LINE;  /* 0x0012 */
        autoNegCntlReg21 = MYD_AUTONEG_LANE_CTRL21_LINE; /* 0x8015 */
    }
    else
    {
        autoNegAdv3Reg = MYD_AUTONEG_ADV3_HOST;  /* 0x1012 */
        autoNegCntlReg21 = MYD_AUTONEG_LANE_CTRL21_HOST; /* 0x9015 */
    }

    switch(opMode)
    {
        case MYD_P10KF:
        case MYD_P25ZF:
        case MYD_P25GF:
        case MYD_P25HF:
        case MYD_P40CF:
        case MYD_P40KF:
        case MYD_P50CF:
        case MYD_P50KF:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv3Reg+(laneOffset*0x200), 14, 2, 0x3));
            break;

        case MYD_P25CF:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv3Reg+(laneOffset*0x200), 12, 2, 0x2));
            break;

        case MYD_P25CR:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv3Reg+(laneOffset*0x200), 12, 2, 0x3));
            break;

        case MYD_P25CN:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv3Reg+(laneOffset*0x200), 12, 2, 0x0));
            break;

        case MYD_P25BF:
        case MYD_P25JF:
        case MYD_P40BF:
        case MYD_P40JF:
        case MYD_P50BF:
        case MYD_P50JF:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv3Reg+(laneOffset*0x200), 14, 2, 0x3));
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegCntlReg21+(laneOffset*0x200), 8, 4, 0xA));
            break;

        case MYD_P25BR:
        case MYD_P25JR:
        case MYD_P40BR:
        case MYD_P40JR:
        case MYD_P50BR:
        case MYD_P50JR:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegCntlReg21+(laneOffset*0x200), 8, 4, 0x5));
            break;

        case MYD_R40C:
        case MYD_R40K:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv3Reg+(laneOffset*0x200), 14, 2, 0x1));
            break;

        case MYD_R25C:
        case MYD_R50C:
        case MYD_R50Q:
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegAdv3Reg+(laneOffset*0x200), 14, 2, 0x1));
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, autoNegCntlReg21+(laneOffset*0x200), 8, 4, 0x3));
            break;

        default:
            break;
    }

    return MYD_OK;
}


/*******************************************************************
 MYD_STATUS mydExtendDeviceAutoNegTimer
    Used internally for mode configuration to extend the AN timer. 
*******************************************************************/
MYD_STATUS mydExtendDeviceAutoNegTimer
(
    IN MYD_DEV_PTR pDev
)
{
    MYD_U16 portIndex;
    MYD_U16 laneOffset;

    for (portIndex=0; portIndex<pDev->portCount; portIndex++)
    {
        for (laneOffset=0; laneOffset<MYD_NUM_LANES; laneOffset++)
        {
            ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort+portIndex, MYD_AUTONEG,
                                        0x8001+(0x0200*laneOffset), 9, 6, 0x2A));
            ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort+portIndex, MYD_AUTONEG,
                                        0x9001+(0x0200*laneOffset), 9, 6, 0x2A));
        }
    }

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydSetFixedMode
    Used internally for mode configuration. 
    Setting the Line or Host mode selection
*******************************************************************/
MYD_STATUS mydSetFixedMode
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U32 modeOption,
    IN MYD_OP_MODE opMode
)
{
    MYD_U16 autoNeg, modeReg;

    autoNeg = opModeTable[opMode][MYD_OP_TABLE_AN_TRAIN];
    modeReg = opModeTable[opMode][MYD_OP_TABLE_REG];

    if (!(host_or_line == MYD_HOST_SIDE || host_or_line == MYD_LINE_SIDE))
    {
        MYD_DBG_ERROR("mydSetFixedMode: Incorrect line_or_host selection: \n");
        return MYD_FAIL;
    }

    if (mydPortPowerUp(pDev, mdioPort, host_or_line, laneOffset, opMode) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydSetFixedMode: Power up fail!\n");
        return MYD_FAIL;
    }

    if (mydRestoreStart(pDev, mdioPort, host_or_line, laneOffset, opMode) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydSetFixedMode: RestoreStart fail!\n");
        return MYD_FAIL;
    }

    if(autoNeg == MYD_AN_TRAIN_ON)
    {
        ATTEMPT(mydConfigAutoNeg(pDev, mdioPort, host_or_line, laneOffset, opMode, MYD_ENABLE));
    }

    ATTEMPT(mydSetFecANConfig(pDev, mdioPort, host_or_line, laneOffset, opMode));

    if (mydModeModifier(pDev, mdioPort, host_or_line, laneOffset, modeOption, opMode) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydSetFixedMode: mydStartEnhance fail!\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, (MYD_MODE_SELECTION+laneOffset), modeReg));

    ATTEMPT(mydSetConfigInfo(pDev, mdioPort, host_or_line, laneOffset, opMode)); 

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydSetRepeater400U
    Use 8xR50U for the R400U 
*******************************************************************/
MYD_STATUS mydSetRepeater400U
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    IN MYD_U32 modeOption
)
{
    MYD_OP_MODE opMode = MYD_R50U;
    MYD_U16 i, j, result;
    MYD_U32 tempModeOption;

    for (j=0; j<2; j++) /* set port and port+1 for 8 lanes 50G */
    {
        for (i=0; i<MYD_NUM_LANES; i++)
        {
            tempModeOption = (i==0) ? modeOption:(modeOption & ~MYD_MODE_FORCE_RECONFIG);
            ATTEMPT(mydSetModeSelection(pDev, mdioPort+j, laneOffset+i, opMode, opMode, 
                                        tempModeOption, &result));
        }
    }

    ATTEMPT(mydSetConfigInfo(pDev, mdioPort, MYD_LINE_SIDE, laneOffset, MYD_R400U)); 
    ATTEMPT(mydSetConfigInfo(pDev, mdioPort, MYD_HOST_SIDE, laneOffset, MYD_R400U)); 

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydSetRepeater200L
    Use 8xR25L for the R200L 
*******************************************************************/
MYD_STATUS mydSetRepeater200L
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    IN MYD_U32 modeOption
)
{
    MYD_OP_MODE opMode = MYD_R25L;
    MYD_U16 i, j, result;
    MYD_U32 tempModeOption;

    for (j=0; j<2; j++) /* set port and port+1 for 8 lanes 25G */
    {
        for (i=0; i<MYD_NUM_LANES; i++)
        {
            tempModeOption = (i==0) ? modeOption:(modeOption & ~MYD_MODE_FORCE_RECONFIG);
            ATTEMPT(mydSetModeSelection(pDev, mdioPort+j, laneOffset+i, opMode, opMode, 
                                        tempModeOption, &result));
        }
    }

    ATTEMPT(mydSetConfigInfo(pDev, mdioPort, MYD_LINE_SIDE, laneOffset, MYD_R200L)); 
    ATTEMPT(mydSetConfigInfo(pDev, mdioPort, MYD_HOST_SIDE, laneOffset, MYD_R200L)); 

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydGetPktGenRegOffset
    Get packet generator register address offset based on mode speed and lane
*******************************************************************************/
MYD_STATUS mydGetPktGenRegOffset
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    OUT MYD_U16 *regAddrOffset
)
{
    MYD_SPEED speed;
    MYD_U16 modeType;
    MYD_U16 mdioPortIndex = MYD_GET_PORT_IDX(pDev, mdioPort);

    if (host_or_line == MYD_HOST_SIDE)
    {
        modeType = pDev->hostConfig[mdioPortIndex][laneOffset].opModeType;
        speed = pDev->hostConfig[mdioPortIndex][laneOffset].speed;
    }
    else 
    {
        modeType = pDev->lineConfig[mdioPortIndex][laneOffset].opModeType;
        speed = pDev->lineConfig[mdioPortIndex][laneOffset].speed;
    }

    if (modeType != MYD_PCS)
    {
        MYD_DBG_ERROR("mydGetPktGenRegOffset: not a PCS mode\n");
        return MYD_FAIL;
    }

    if (laneOffset >= MYD_NUM_LANES)
    {
        MYD_DBG_ERROR("mydGetPktGenRegOffset: incorrect lane offset: %u\n", laneOffset);
        return MYD_FAIL;
    }

    *regAddrOffset = 0;  /* for MYD_100GB speed */

    switch(speed)
    {
        case MYD_1GB:
        case MYD_2P5GB:
            *regAddrOffset = PACKET_GEN_1G_OFFSET+laneOffset*0x200;
            break;

        case MYD_5GB:
        case MYD_10GB:
        case MYD_25GB:
            *regAddrOffset = PACKET_GEN_25G_OFFSET+laneOffset*0x200;
            break;

        case MYD_40GB:
        case MYD_50GB:
            *regAddrOffset = PACKET_GEN_40G_OFFSET+laneOffset*0x200;
            break;

        case MYD_100GB:
            *regAddrOffset = laneOffset*0x200;
            break;

        case MYD_200GB:
        case MYD_400GB:
            *regAddrOffset = PACKET_GEN_200G_OFFSET;
            break;

        default:
            MYD_DBG_ERROR("mydGetPktGenRegOffset: unsupported speed: %u\n", speed);
            return MYD_FAIL;
            break;
    }
        
    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydPortPowerHwReset
   Power down and reset mdioPort on both the host and line side
*******************************************************************/
MYD_STATUS mydPortPowerHwReset
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort
)
{
    if (mydIsPortValid(pDev, mdioPort) != MYD_OK)
    {
        MYD_DBG_ERROR("mydPortPowerHwReset: incorrect mdioPort selection: %u\n", mdioPort);
        return MYD_FAIL;
    }

    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_PWD_RESET, 0x4040));

    if (mydPortPowerHwResetTimeout(pDev, mdioPort, MYD_RESET_TIMEOUT) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydPortPowerHwReset: power down fail on mdioPort: %u\n", mdioPort);
        return MYD_FAIL;
    }

    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_PWD_RESET, 0x6060));

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydPortPowerHwResetTimeout
    Power down and Reset mdioPort wait time
*******************************************************************/
MYD_STATUS mydPortPowerHwResetTimeout
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 timeoutMs
)
{
    MYD_U16 lane0, lane1, lane2, lane3;
    MYD_U16 counter = 0;

    if (mydIsPortValid(pDev, mdioPort) != MYD_OK)
    {
        MYD_DBG_ERROR("mydPortPowerHwResetWait: incorrect mdioPort selection: %u\n", mdioPort);
        return MYD_FAIL;
    }

    do
    {
        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_LINE_SIDE, 0xF200, 4, 1, &lane0));
        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_LINE_SIDE, 0xF280, 4, 1, &lane1));
        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_LINE_SIDE, 0xF300, 4, 1, &lane2));
        ATTEMPT(mydHwGetPhyRegField(pDev, mdioPort, MYD_LINE_SIDE, 0xF380, 4, 1, &lane3));

        if (lane0 && lane1 && lane2 && lane3)
        {
            /* MYD_DBG_INFO("mydPortPowerHwResetTimeout: counter: %u\n", counter); */
            return MYD_OK;
        }

        ATTEMPT(mydWait(pDev, 200));
        counter = counter + 200;

    } while (timeoutMs > counter);

    MYD_DBG_ERROR("mydPortPowerHwResetTimeout: Timeout: %u failed. Ln0:0x%x Ln1:0x%x Ln2:0x%x Ln3:0x%x\n",
                  counter, lane0, lane1, lane2, lane3);

    return MYD_FAIL; /* timed out without becoming ready */
}

#define LINE_SOFT_RESET     0x8000
#define LINE_HARD_RESET     0x2000
#define HOST_SOFT_RESET     0x0080
#define HOST_HARD_RESET     0x0020
#define PORT_ALL_RESET      (LINE_SOFT_RESET|LINE_HARD_RESET|HOST_SOFT_RESET|HOST_HARD_RESET)
/*******************************************************************
 MYD_STATUS mydPortResetTimeout
 Check timeout after the soft or hard reset
*******************************************************************/
MYD_STATUS mydPortResetTimeout
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 timeoutMs
)
{
    MYD_U16 temp, counter;

    if (timeoutMs)
    {
        counter=0;
        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_PWD_RESET, &temp));

        while ((temp & PORT_ALL_RESET) && (counter <= timeoutMs))
        {
            ATTEMPT(mydWait(pDev,1));
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_PORT_REG, MYD_PORT_PWD_RESET, &temp));
            counter++;
        }

        if (counter < timeoutMs)
        {
           return MYD_OK;
        }
        else
        {
           MYD_DBG_ERROR("mydPortResetTimeout: Timeout: %u failed.\n", counter);
           return MYD_FAIL; /* timed out without becoming ready */
        }
    }
    return MYD_OK;
}


/*******************************************************************************
 MYD_STATUS mydSetDeepPCSLoopback
*******************************************************************************/
MYD_STATUS mydSetDeepPCSLoopback
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    IN MYD_U16 host_or_line,
    IN MYD_U16 gearboxMode,
    IN MYD_U16 autoNeg,
    IN MYD_SPEED Speed,
    IN MYD_U16 regAddrPCS,
    IN MYD_U16 loopbackBit /* 1-enabled; 0-disabled */
)
{
    MYD_U16 temp;

    if ((loopbackBit == 1) && (autoNeg))
    {
        /* Disable auto-neg */
        if (host_or_line == MYD_HOST_SIDE)
        {
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, (MYD_AUTONEG_CNTL_HOST+(laneOffset*0x200)), 12, 1, 0));
        }
        else
        {
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, (MYD_AUTONEG_CNTL_LINE+(laneOffset*0x200)), 12, 1, 0));
        }

        /*Disable fake auto-neg */
        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, (MYD_MODE_SELECTION+laneOffset), &temp));
        temp &= ~0x0010;
        temp |= 0x8000;
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line, (MYD_MODE_SELECTION+laneOffset), temp));
    }

    /* Turn Deep Line side Loopback on/off */
    ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, regAddrPCS, 14, 1, loopbackBit));

    if (loopbackBit == 0)
    {
        if (autoNeg)
        {
            /* Enable auto-neg */
            if (host_or_line == MYD_HOST_SIDE)
            {
                ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, (MYD_AUTONEG_CNTL_HOST+(laneOffset*0x200)), 12, 1, 1));
            }
            else
            {
                ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, MYD_AUTONEG, (MYD_AUTONEG_CNTL_LINE+(laneOffset*0x200)), 12, 1, 1));
            }
            /* Enable fake auto-neg */
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, (MYD_MODE_SELECTION+laneOffset), &temp));
            temp |= 0x8010;
            ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, host_or_line,(MYD_MODE_SELECTION+laneOffset), temp));
        }
    }

    if (gearboxMode == 1)
    {
        /*Disable/Enable Resetting FIFO based on other side PCS RX reset*/
        if (host_or_line == MYD_HOST_SIDE)
        {
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0x904D, 15, 1, loopbackBit));
        }
        else
        {
            ATTEMPT(mydHwSetPhyRegField(pDev, mdioPort, host_or_line, 0xA04D, 15, 1, loopbackBit));
        }
    }

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydReloadConfigInfo
 Called by reload driver to update the host and line config info
*******************************************************************/
MYD_STATUS mydReloadConfigInfo
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort
)
{
    MYD_U16 portIndex, laneOffset;
    MYD_U16 interfaceIndex, host_or_line, modeReg;
    MYD_U16 opModeIndex;
    MYD_OP_MODE opMode;
    MYD_U16 laneCount;

    for (portIndex=0; portIndex<pDev->portCount; portIndex++)
    {
        for(interfaceIndex=0; interfaceIndex<MYD_NUM_INTERFACE; interfaceIndex++)
        {
            host_or_line = (interfaceIndex == 0) ? MYD_LINE_SIDE:MYD_HOST_SIDE;
            for (laneOffset=0; laneOffset<MYD_NUM_LANES; laneOffset++)
            {
                ATTEMPT(mydHwXmdioRead(pDev, mdioPort+portIndex, host_or_line, 
                                       (MYD_MODE_SELECTION+laneOffset), &modeReg));
                if ((modeReg & 0x0FFF) == 0)
                {
                    continue;
                }
                for (opModeIndex=0; opModeIndex<MYD_OP_MODE_COUNT; opModeIndex++)
                {
                    if ((modeReg & 0x0FFF) == (opModeTable[opModeIndex][MYD_OP_TABLE_REG] & 0x0FFF))
                    {
                        opMode = (MYD_OP_MODE)opModeTable[opModeIndex][MYD_OP_TABLE_OP_MODE];
                        laneCount = opModeTable[opMode][MYD_OP_TABLE_LANE_COUNT];
                        if (laneCount == MYD_1_LANE_MODE)
                        {
                            ATTEMPT(mydSetConfigInfo(pDev, portIndex, host_or_line, laneOffset, opMode));
                        }
                        else if (laneCount == MYD_2_LANE_MODE)
                        {
                            if ((laneOffset == 0) || (laneOffset == 2))
                            {
                                ATTEMPT(mydSetConfigInfo(pDev, portIndex, host_or_line, laneOffset, opMode));
                                pDev->devInfo[portIndex] |= MYD_LANES_GROUPED;
                            }
                        }
                        else if ((laneCount == MYD_4_LANE_MODE) || (laneCount == MYD_8_LANE_MODE))
                        {
                            if (laneOffset == 0)
                            {
                                ATTEMPT(mydSetConfigInfo(pDev, portIndex, host_or_line, laneOffset, opMode));
                                pDev->devInfo[portIndex] |= MYD_LANES_GROUPED;
                            }
                        }
                        else
                        {
                            MYD_DBG_ERROR("mydReloadConfigInfo: Error reloading. opMode:%u laneCount:%u\n", 
                                          opMode, laneCount);
                            return MYD_FAIL;
                        }
                    }
                }
            }
        }
    }

    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydLaneResetTimeout
 Check timeout after the Lane soft reset
*******************************************************************/
MYD_STATUS mydLaneResetTimeout
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 timeoutMs
)
{
    MYD_U16 temp, counter;

    if (timeoutMs)
    {
        counter=0;
        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, (MYD_MODE_SELECTION+laneOffset), &temp));

        while ((temp & 0x8000) && (counter <= timeoutMs))
        {
            ATTEMPT(mydWait(pDev,1));
            ATTEMPT(mydHwXmdioRead(pDev, mdioPort, host_or_line, (MYD_MODE_SELECTION+laneOffset), &temp));
            counter++;
        }

        if (counter < timeoutMs)
        {
           return MYD_OK;
        }
        else
        {
           MYD_DBG_ERROR("mydLaneResetTimeout: Timeout: %u failed.\n", counter);
           return MYD_FAIL; /* timed out without becoming ready */
        }
    }
    return MYD_OK;
}

/*******************************************************************
 MYD_STATUS mydLoadEEPROMSerdesWaitTime
 This will always return MYD_OK. It will speed up the wait time
 if loading from EEPROM is available.
 Checks Serdes firmware loading from EEPROM completion
 If no EEPROM, no wait is needed and return MYD_OK
*******************************************************************/
MYD_STATUS mydLoadEEPROMSerdesWaitTime
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 timeoutMs,
    OUT MYD_U16 *waitTimeMs
)
{
    MYD_U16 temp, i;

    *waitTimeMs = timeoutMs;

    if (mdioPort != (pDev->portCount-1))
    {
        if (pDev->devEEPROM == MYD_FALSE)
        {
            return MYD_OK; /* do not need to wait since there is no valid EEPROM image */
        }
    }

    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_CHIP_REG, 0xF418, &temp)); 
    if ((temp & 0x0001) == 1) 
    {
        return MYD_OK; /* do not need to wait since EEPROM load is disabled. */
    }

    for (i=0; i<(timeoutMs/100); i++) 
    {
        ATTEMPT(mydWait(pDev, 100)); /*  */

        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_NIMB_REG, 0xF845, &temp)); 

        if ((temp & 0x0001) == 1) 
        {
            if (i && (i*100 < timeoutMs)) 
            {                                /* if EEPROM is reloaded,  */
                ATTEMPT(mydWait(pDev, 300)); /* add another 300ms for SerDes to settle */
            }

            pDev->devEEPROM = MYD_TRUE;
            MYD_DBG_INFO("mydLoadEEPROMSerdesWaitTime: Load completed in %u msec. Return val:0x%X\n", i*100, temp);
            
            *waitTimeMs = i*100;
            return MYD_OK;
        }
    }

    MYD_DBG_INFO("mydLoadEEPROMSerdesWaitTime: EEPROM failed loading in %u msec. Return val:0x%X\n", i*100, temp);

    return MYD_OK;
}

/*******************************************************************************
 MYD_STATUS mydCheckSupportedPinMode
    Check if a mode is supported for the given multi-purpose Pin
*******************************************************************************/
MYD_STATUS mydCheckSupportedPinMode
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID pinId,
    IN MYD_PIN_MODE pinMode
)
{
    MYD_BOOL support;

    if (!pDev)
    {
        MYD_DBG_ERROR("mydCheckSupportedPinMode: pDev is NULL\n");
        return MYD_FAIL;
    }

    if (!pDev->devEnabled)
    {
        MYD_DBG_ERROR("mydCheckSupportedPinMode: device is not initialized\n");
        return MYD_FAIL;
    }

    if (pinMode >= MYD_PIN_MODE_NUMS)
    {
        MYD_DBG_ERROR("Invalid Pin Mode selected: %d\n", pinMode);
        return MYD_FAIL;
    }

    support = MYD_FALSE;
    switch(pDev->deviceId)
    {
        case MYD_DEV_X7120:
            switch(pinId)
            {
                case MYD_PIN_GPIO1:
                case MYD_PIN_GPIO3:
                case MYD_PIN_GPIO4:
                    if (pinMode == MYD_PIN_MODE_BACKPRESSURE ||
                        pinMode == MYD_PIN_MODE_GPIO ||
                        pinMode == MYD_PIN_MODE_LED)
                    {
                        support = MYD_TRUE;
                    }
                    break;

                case MYD_PIN_GPIO2:
                case MYD_PIN_CLK_OUT_SE1:
                case MYD_PIN_CLK_OUT_SE2:
                    if (pinMode == MYD_PIN_MODE_BACKPRESSURE ||
                        pinMode == MYD_PIN_MODE_GPIO ||
                        pinMode == MYD_PIN_MODE_LED ||
                        pinMode == MYD_PIN_MODE_RCLK)
                    {
                        support = MYD_TRUE;
                    }
                    break;

                case MYD_PIN_CLK_OUT_DIFF_N:
                case MYD_PIN_CLK_OUT_DIFF_P:
                    if (pinMode == MYD_PIN_MODE_RCLK)
                    {
                        support = MYD_TRUE;
                    }
                    break;

                case MYD_PIN_INTn:
                    if (pinMode == MYD_PIN_MODE_RCLK ||
                        pinMode == MYD_PIN_MODE_INTR)
                    {
                        support = MYD_TRUE;
                    }
                    break;

                default:
                    MYD_DBG_ERROR("mydCheckSupportedPinMode: incorrect Pin selected: %d\n", pinId);
                    return MYD_FAIL;
                    break;
            }
            break;

        case MYD_DEV_X6141:
            switch(pinId)
            {
                case MYD_PIN_GPIO0:
                case MYD_PIN_GPIO2:
                    if (pinMode == MYD_PIN_MODE_BACKPRESSURE ||
                        pinMode == MYD_PIN_MODE_GPIO ||
                        pinMode == MYD_PIN_MODE_LED)
                    {
                        support = MYD_TRUE;
                    }
                    break;

                case MYD_PIN_GPIO1:
                case MYD_PIN_GPIO3:
                    if (pinMode == MYD_PIN_MODE_GPIO ||
                        pinMode == MYD_PIN_MODE_LED)
                    {
                        support = MYD_TRUE;
                    }
                    break;

                case MYD_PIN_CLK_OUT_SE1:
                case MYD_PIN_CLK_OUT_SE2:
                    if (pinMode == MYD_PIN_MODE_BACKPRESSURE ||
                        pinMode == MYD_PIN_MODE_GPIO ||
                        pinMode == MYD_PIN_MODE_LED ||
                        pinMode == MYD_PIN_MODE_RCLK)
                    {
                        support = MYD_TRUE;
                    }
                    break;

                case MYD_PIN_INTn:
                    if (pinMode == MYD_PIN_MODE_RCLK ||
                        pinMode == MYD_PIN_MODE_INTR)
                    {
                        support = MYD_TRUE;
                    }
                    break;
                default:
                    MYD_DBG_ERROR("mydCheckSupportedPinMode: incorrect Pin selected: %d\n", pinId);
                    return MYD_FAIL;
                    break;
            }
            break;

        default:
            MYD_DBG_ERROR("mydCheckSupportedPinMode: Unknown or Unsupported device model: 0x%x\n", pDev->deviceId);
            return MYD_FAIL;
    }

    if (support == MYD_FALSE)
    {
        MYD_DBG_ERROR("mydCheckSupportedPinMode: Mode %d is not supported for Pin %d,\n", (MYD_U16)pinMode, pinId);
        MYD_DBG_ERROR("mydCheckSupportedPinMode: Please check the mydSetPinMode() and structure definitions for details.\n", (MYD_U16)pinMode, pinId);
        return MYD_FAIL;
    }

    return MYD_OK;
}

/******************************************************************************
 MYD_STATUS mydGPIOPinGetPortAndReg()
    This function calculate the port and register needed for configure/read GPIO Pin
******************************************************************************/
MYD_STATUS mydGPIOPinGetPortAndReg
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    OUT MYD_U16 *GPIOPort,
    OUT MYD_U16 *GPIOCtrlReg
)
{
    if (!pDev)
    {
        MYD_DBG_ERROR("mydGPIOPinGetPortAndReg: pDev is NULL\n");
        return MYD_FAIL;
    }

    if (!pDev->devEnabled)
    {
        MYD_DBG_ERROR("mydGPIOPinGetPortAndReg: device is not initialized\n");
        return MYD_FAIL;
    }

    if (pDev->deviceId == MYD_DEV_X7120)
    {
        switch(gpioPinId)
        {
            case MYD_PIN_GPIO1:
                *GPIOCtrlReg = MYD_GPIO0_CTRL;
                *GPIOPort = pDev->mdioPort;
                break;

            case MYD_PIN_GPIO2:
                *GPIOCtrlReg = MYD_GPIO4_CTRL;
                *GPIOPort = pDev->mdioPort + 1;
                break;

            case MYD_PIN_GPIO3:
                *GPIOCtrlReg = MYD_GPIO0_CTRL;
                *GPIOPort = pDev->mdioPort + 2;
                break;

            case MYD_PIN_GPIO4:
                *GPIOCtrlReg = MYD_GPIO2_CTRL;
                *GPIOPort = pDev->mdioPort + 3;
                break;

            case MYD_PIN_CLK_OUT_SE1:
                *GPIOCtrlReg = MYD_GPIO4_CTRL;
                *GPIOPort = pDev->mdioPort + 3;
                break;

            case MYD_PIN_CLK_OUT_SE2:
                *GPIOCtrlReg = MYD_GPIO5_CTRL;
                *GPIOPort = pDev->mdioPort + 3;
                break;

            default:
                MYD_DBG_ERROR("mydGPIOPinGetPortAndReg: Invalid Pin:%d selected on device model: 0x%x\n", gpioPinId, pDev->deviceId);
                return MYD_FAIL;
        }
    }
    else if (pDev->deviceId == MYD_DEV_X6141)
    {
        *GPIOPort = pDev->mdioPort;
        switch(gpioPinId)
        {
            case MYD_PIN_GPIO0:
                *GPIOCtrlReg = MYD_GPIO0_CTRL;
                break;

            case MYD_PIN_GPIO1:
                *GPIOCtrlReg = MYD_GPIO1_CTRL;
                break;

            case MYD_PIN_GPIO2:
                *GPIOCtrlReg = MYD_GPIO2_CTRL;
                break;

            case MYD_PIN_GPIO3:
                *GPIOCtrlReg = MYD_GPIO3_CTRL;
                break;

            case MYD_PIN_CLK_OUT_SE1:
                *GPIOCtrlReg = MYD_GPIO4_CTRL;
                break;

            case MYD_PIN_CLK_OUT_SE2:
                *GPIOCtrlReg = MYD_GPIO5_CTRL;
                break;

            default:
                MYD_DBG_ERROR("mydGPIOPinGetPortAndReg: Invalid Pin:%d selected on device model: 0x%x\n", gpioPinId, pDev->deviceId);
                return MYD_FAIL;
        }
    }
    else
    {
        MYD_DBG_ERROR("mydGPIOPinGetPortAndReg: Unknown or Unsupported device model: 0x%x\n", pDev->deviceId);
        return MYD_FAIL;
    }

    return MYD_OK;
}

/******************************************************************************
 MYD_STATUS mydLEDConfigInputCheck
    This function check if passed-in LED configuration is out of range 
    See mydConfigLEDPin() for details.
******************************************************************************/
MYD_STATUS mydLEDConfigInputCheck
(
    IN MYD_LED_ID ledId,
    IN MYD_LED_CTRL ledCtrl,
    IN MYD_LED_TIMER_CONFIG ledTimerConfig
)
{
    if (ledCtrl.laneSelect >= MYD_NUM_LANES && ledCtrl.laneSelect != MYD_LED_CONFIG_UNCHANGED)
    {
        MYD_DBG_ERROR("mydLEDConfigInputCheck: Invalid lane:%d selected for the LED%d\n", ledCtrl.laneSelect, (MYD_U16)ledId);
        return MYD_FAIL;
    }

    if (!(ledCtrl.interfaceSelect == MYD_LINE_SIDE || ledCtrl.interfaceSelect == MYD_HOST_SIDE || ledCtrl.interfaceSelect == MYD_LED_CONFIG_UNCHANGED))
    {
        MYD_DBG_ERROR("mydLEDConfigInputCheck: Invalid interface:%d selected for the LED%d\n", ledCtrl.interfaceSelect, (MYD_U16)ledId);
        return MYD_FAIL;
    }

    if (!(ledCtrl.blinkActivity == MYD_LED_ACT_SOLID_OFF ||
          ledCtrl.blinkActivity == MYD_LED_ACT_LANE_TX_RX ||
          ledCtrl.blinkActivity == MYD_LED_ACT_LANE_TX ||
          ledCtrl.blinkActivity == MYD_LED_ACT_LANE_RX ||
          ledCtrl.blinkActivity == MYD_LED_ACT_LANE_LINK_UP ||
          ledCtrl.blinkActivity == MYD_LED_ACT_SOLID_ON ||
          ledCtrl.blinkActivity == MYD_LED_ACT_BLINK_MIX ||
          ledCtrl.blinkActivity == MYD_LED_ACT_SOLID_MIX ||
          ledCtrl.blinkActivity == MYD_LED_CONFIG_UNCHANGED))
    {
        MYD_DBG_ERROR("mydLEDConfigInputCheck: Invalid blink activity:0x%x selected for the LED%d\n", ledCtrl.blinkActivity, (MYD_U16)ledId);
        return MYD_FAIL;
    }

    if (!(ledCtrl.solidActivity == MYD_LED_ACT_SOLID_OFF ||
          ledCtrl.solidActivity == MYD_LED_ACT_LANE_TX_RX ||
          ledCtrl.solidActivity == MYD_LED_ACT_LANE_TX ||
          ledCtrl.solidActivity == MYD_LED_ACT_LANE_RX ||
          ledCtrl.solidActivity == MYD_LED_ACT_LANE_LINK_UP ||
          ledCtrl.solidActivity == MYD_LED_ACT_SOLID_ON ||
          ledCtrl.solidActivity == MYD_LED_CONFIG_UNCHANGED))
    {
        MYD_DBG_ERROR("mydLEDConfigInputCheck: Invalid solid activity:0x%x selected for the LED%d\n", ledCtrl.solidActivity, (MYD_U16)ledId);
        return MYD_FAIL;
    }

    if (!(ledCtrl.polarity == MYD_LED_ACTIVE_LOW ||
          ledCtrl.polarity == MYD_LED_ACTIVE_HIGH ||
          ledCtrl.polarity == MYD_LED_ACTIVE_LOW_TRISTATE ||
          ledCtrl.polarity == MYD_LED_ACTIVE_HIGH_TRISTATE ||
          ledCtrl.polarity == MYD_LED_CONFIG_UNCHANGED))
    {
        MYD_DBG_ERROR("mydLEDConfigInputCheck: Invalid polarity:0x%x selected for the LED%d\n", ledCtrl.polarity, (MYD_U16)ledId);
        return MYD_FAIL;
    }

    if (ledCtrl.mixRateLevel > 0x8 && ledCtrl.mixRateLevel != MYD_LED_CONFIG_UNCHANGED)
    {
        MYD_DBG_ERROR("mydLEDConfigInputCheck: Invalid mix rate level:0x%x selected for the LED%d\n", ledCtrl.mixRateLevel, (MYD_U16)ledId);
        return MYD_FAIL;
    }

    if (!(ledCtrl.blinkRateSelect == 1 || ledCtrl.blinkRateSelect == 2 || ledCtrl.blinkRateSelect == MYD_LED_CONFIG_UNCHANGED))
    {
        MYD_DBG_ERROR("mydLEDConfigInputCheck: Invalid blink rate option:%d selected for the LED%d\n", ledCtrl.blinkRateSelect, (MYD_U16)ledId);
        return MYD_FAIL;
    }

    if (ledTimerConfig.blinkRate1 > 0x7 && ledTimerConfig.blinkRate1 != MYD_LED_CONFIG_UNCHANGED)
    {
        MYD_DBG_ERROR("mydLEDConfigInputCheck: Invalid setting value:%d for Blink Rate 1.\n", ledTimerConfig.blinkRate1);
        return MYD_FAIL;
    }

    if (ledTimerConfig.blinkRate2 > 0x7 && ledTimerConfig.blinkRate2 != MYD_LED_CONFIG_UNCHANGED)
    {
        MYD_DBG_ERROR("mydLEDConfigInputCheck: Invalid setting value:%d for Blink Rate 2.\n", ledTimerConfig.blinkRate2);
        return MYD_FAIL;
    }

    if (ledTimerConfig.pulseStretchDuration > 0x7 && ledTimerConfig.pulseStretchDuration != MYD_LED_CONFIG_UNCHANGED)
    {
        MYD_DBG_ERROR("mydLEDConfigInputCheck: Invalid setting value:%d for Pulse Stretch Duration.\n", ledTimerConfig.pulseStretchDuration);
        return MYD_FAIL;
    }

    return MYD_OK;
}

/******************************************************************************
 MYD_STATUS mydRClkMuxInputCheck
    This function check if passed-in MYD_RCLK_MUX_OPTION is out of range
    See mydConfigRClkMux() for details.
******************************************************************************/
MYD_STATUS mydRClkMuxInputCheck
(
    IN MYD_U16 portIndex,
    IN MYD_U16 interfaceIndex,
    IN MYD_U16 muxNum,
    IN MYD_RCLK_MUX_OPTION mux
)
{
    if (mux.srcClockSelect > 0x1)
    {
        MYD_DBG_ERROR("mydRClkMuxInputCheck: On Port:%d at interface:%d RCLK MUX%d, invalid source clock:%d is selected\n",
                      portIndex, (interfaceIndex == MYD_HOST_MODE_IDX)?MYD_HOST_SIDE:MYD_LINE_SIDE, muxNum, mux.srcClockSelect);
        return MYD_FAIL;
    }

    if (mux.laneSelect >= MYD_NUM_LANES)
    {
        MYD_DBG_ERROR("mydRClkMuxInputCheck: On Port:%d at interface:%d RCLK MUX%d, invalid lane:%d is selected\n",
                      portIndex, (interfaceIndex == MYD_HOST_MODE_IDX)?MYD_HOST_SIDE:MYD_LINE_SIDE, muxNum, mux.laneSelect);
        return MYD_FAIL;
    }

    if (mux.divideRatio > 0xFF)
    {
        MYD_DBG_ERROR("mydRClkMuxInputCheck: On Port:%d at interface:%d RCLK MUX%d, invalid divide ratio:0x%02x is selected\n",
                      portIndex, (interfaceIndex == MYD_HOST_MODE_IDX)?MYD_HOST_SIDE:MYD_LINE_SIDE, muxNum, mux.divideRatio);
        return MYD_FAIL;
    }

    if (mux.dividerConfig > 0x2)
    {
        MYD_DBG_ERROR("mydRClkMuxInputCheck: On Port:%d at interface:%d RCLK MUX%d, invalid divider config:0x%x is selected\n",
                      portIndex, (interfaceIndex == MYD_HOST_MODE_IDX)?MYD_HOST_SIDE:MYD_LINE_SIDE, muxNum, mux.dividerConfig);
        return MYD_FAIL;
    }

    return MYD_OK;
}

/******************************************************************************
 MYD_STATUS mydRClkConfigInputCheck
    This function check if passed-in RCLK configuration is out of range 
    See mydConfigRClkPin() for details.
******************************************************************************/
MYD_STATUS mydRClkConfigInputCheck
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID rClkPinId,
    IN MYD_U16 portSelect,
    IN MYD_U16 interfaceSelect,
    IN MYD_U16 muxOptionSelect
)
{
    if (!pDev)
    {
        MYD_DBG_ERROR("mydRClkConfigInputCheck: pDev is NULL\n");
        return MYD_FAIL;
    }

    if (!pDev->devEnabled)
    {
        MYD_DBG_ERROR("mydRClkConfigInputCheck: device is not initialized\n");
        return MYD_FAIL;
    }

    if (portSelect < pDev->mdioPort || portSelect >= (pDev->mdioPort+pDev->portCount))
    {
        MYD_DBG_ERROR("mydRClkConfigInputCheck: Invalid port:%d RCLK source selected for the Pin:%d\n", portSelect, (MYD_U16)rClkPinId);
        return MYD_FAIL;
    }

    /* Check if the passed-in Recovered Clock Pin is invalid for the device */
    ATTEMPT(mydCheckSupportedPinMode(pDev, rClkPinId, MYD_PIN_MODE_RCLK));

    if (pDev->deviceId == MYD_DEV_X7120)
    {
        if (rClkPinId == MYD_PIN_GPIO2)
        {
            if (!(portSelect == pDev->mdioPort || portSelect == pDev->mdioPort+1))
            {
                MYD_DBG_ERROR("mydRClkConfigInputCheck: Invalid port:%d RCLK source selected for X7120 GPIO2 Pin.\n", portSelect);
                MYD_DBG_ERROR("mydRClkConfigInputCheck: X7120 GPIO2 Pin can only output RCLK from Port0 and Port1.\n");
                return MYD_FAIL;
            }
        }
        else if (rClkPinId == MYD_PIN_CLK_OUT_SE1)
        {
            if (!(portSelect == pDev->mdioPort+2 || portSelect == pDev->mdioPort+3))
            {
                MYD_DBG_ERROR("mydRClkConfigInputCheck: Invalid port:%d RCLK source selected for X7120 CLK_OUT_SE1 Pin.\n", portSelect);
                MYD_DBG_ERROR("mydRClkConfigInputCheck: X7120 CLK_OUT_SE1 Pin can only output RCLK from Port2 and Port3.\n");
                return MYD_FAIL;
            }
        }
        else if (rClkPinId == MYD_PIN_CLK_OUT_DIFF_N)
        {
            if (portSelect != pDev->mdioPort+3)
            {
                MYD_DBG_ERROR("mydRClkConfigInputCheck: Invalid port:%d RCLK source selected for X7120 CLK_OUT_DIFF_N Pin.\n", portSelect);
                MYD_DBG_ERROR("mydRClkConfigInputCheck: X7120 CLK_OUT_DIFF_N Pin can only output RCLK from Port3.\n");
                return MYD_FAIL;
            }
        }
        else if (rClkPinId == MYD_PIN_CLK_OUT_DIFF_P)
        {
            if (portSelect != pDev->mdioPort+3)
            {
                MYD_DBG_ERROR("mydRClkConfigInputCheck: Invalid port:%d RCLK source selected for X7120 CLK_OUT_DIFF_P Pin.\n", portSelect);
                MYD_DBG_ERROR("mydRClkConfigInputCheck: X7120 CLK_OUT_DIFF_P Pin can only output RCLK from Port3.\n");
                return MYD_FAIL;
            }
        }
    }
    else if (pDev->deviceId != MYD_DEV_X6141)
    {
        MYD_DBG_ERROR("mydRClkConfigInputCheck: Unknown or unsupported device: 0x%x.\n", pDev->deviceId);
        return MYD_FAIL;
    }

    if (!(interfaceSelect == MYD_LINE_SIDE || interfaceSelect == MYD_HOST_SIDE))
    {
        MYD_DBG_ERROR("mydRClkConfigInputCheck: Invalid interface:%d RCLK source selected for the Pin:%d\n", interfaceSelect, (MYD_U16)rClkPinId);
        return MYD_FAIL;
    }

    if (!(muxOptionSelect == 1 || muxOptionSelect == 2))
    {
        MYD_DBG_ERROR("mydRClkConfigInputCheck: Invalid RCLK MUX option:%d selected for the Pin:%d\n", muxOptionSelect, (MYD_U16)rClkPinId);
        return MYD_FAIL;
    }

    return MYD_OK;
}

#define MYD_RCLK_COUNTS             5
#define MYD_RCLK_TABLE_COLS         5
typedef enum _MYD_RCLK_ID
{
    MYD_RCLK_A = 0,
    MYD_RCLK_B,
    MYD_RCLK_C,
    MYD_RCLK_D,
    MYD_RCLK_E,
    MYD_RCLK_NUMS
} MYD_RCLK_ID;

typedef enum _MYD_RCLK_TABLE
{
    MYD_RTABLE_ID = 0,
    MYD_RTABLE_MUX_REG,
    MYD_RTABLE_SIDE_BIT,
    MYD_RTABLE_LINE_BIT,
    MYD_RTABLE_HOST_BIT
} MYD_RCLK_TABLE;

/******************************************************************************
 MYD_STATUS mydRClkSelectSource
    This function select source for given RCLK Pin by given Port, interface and MUX
    See mydConfigRClkPin() for details.
******************************************************************************/
MYD_STATUS mydRClkSelectSource
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID pinId,
    IN MYD_U16 portSelect,
    IN MYD_U16 interfaceSelect,
    IN MYD_U16 muxOptionSelect
)
{
    MYD_U8 MUXOffset;
    MYD_U16 rClkId;
    MYD_U16 interfaceSelectMuxValue, topLevelMuxValue;
    MYD_PIN_MODE pinMode;

    const MYD_U16 RCLK_TABLE[MYD_RCLK_COUNTS][MYD_RCLK_TABLE_COLS] =
    /* RCLK_ID          MUX_REG                SIDE_MUX_BIT    LINE_MUX_BIT   HOST_MUX_BIT */
    {{MYD_RCLK_A,     MYD_PORT_RCVCLK_CTRL1,      2,             0,               1},
     {MYD_RCLK_B,     MYD_PORT_RCVCLK_CTRL1,      6,             4,               5},
     {MYD_RCLK_C,     MYD_PORT_RCVCLK_CTRL1,      10,            8,               9},
     {MYD_RCLK_D,     MYD_PORT_RCVCLK_CTRL2,      2,             0,               1},     /* Not available on X6141 */
     {MYD_RCLK_E,     MYD_PORT_RCVCLK_CTRL2,      10,            8,               9}};    /* Not available on X6141 */

    if (!pDev)
    {
        MYD_DBG_ERROR("mydRClkSelectSource: pDev is NULL\n");
        return MYD_FAIL;
    }

    if (!pDev->devEnabled)
    {
        MYD_DBG_ERROR("mydRClkSelectSource: device is not initialized\n");
        return MYD_FAIL;
    }

    ATTEMPT(mydGetPinMode(pDev, pinId, &pinMode));
    if (pinMode != MYD_PIN_MODE_RCLK)
    {
        MYD_DBG_ERROR("mydRClkSelectSource: The given Pin:%d is not in the MYD_PIN_MODE_RCLK mode.\n");
        return MYD_FAIL;
    }

    interfaceSelectMuxValue = (interfaceSelect==MYD_HOST_SIDE) ? 1 : 0;
    topLevelMuxValue = (muxOptionSelect==1) ? 0 : 1;

    /* Select Port */
    rClkId = MYD_RCLK_NUMS;
    if (pDev->deviceId == MYD_DEV_X7120)
    {
        switch(pinId)
        {
            case MYD_PIN_INTn:
                rClkId = MYD_RCLK_A;
                MUXOffset = 3;

                if (portSelect == pDev->mdioPort)
                {
                    ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, MUXOffset, 1, 0x1));
                    break;
                }
                else
                {
                    ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, MUXOffset, 1, 0x0));
                }

                if (portSelect == pDev->mdioPort+1)
                {
                    ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort+1, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, MUXOffset, 1, 0x1));
                    break;
                }
                else
                {
                    ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort+1, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, MUXOffset, 1, 0x0));
                }

                if (portSelect == pDev->mdioPort+2)
                {
                    ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort+2, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, MUXOffset, 1, 0x1));
                    break;
                }
                else
                {
                    ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort+2, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, MUXOffset, 1, 0x0));
                }

                if (portSelect == pDev->mdioPort+3)
                {
                    ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort+3, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, MUXOffset, 1, 0x1));
                }

                break;

            case MYD_PIN_GPIO2:
                rClkId = MYD_RCLK_B;
                if (portSelect == pDev->mdioPort)
                {
                    ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort+1, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 12, 1, 0x1));
                    ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 12, 1, 0x0));
                }
                else if (portSelect == pDev->mdioPort+1)
                {
                    ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort+1, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 12, 1, 0x0));
                }
                else
                {
                    /* Not possible, but in case we reach here. */
                    MYD_DBG_ERROR("mydRClkSelectSource: Invalid port:%d selected for X7120 GPIO2 Pin.\n", portSelect);
                    MYD_DBG_ERROR("mydRClkSelectSource: X7120 GPIO2 Pin can only output RCLK from Port0 and Port1.\n");
                    return MYD_FAIL;
                }
                break;

            case MYD_PIN_CLK_OUT_SE1:
                rClkId = MYD_RCLK_B;
                if (portSelect == pDev->mdioPort+2)
                {
                    ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort+3, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 12, 1, 0x1));
                    ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort+2, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 12, 1, 0x0));
                }
                else if (portSelect == pDev->mdioPort+3)
                {
                    ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort+3, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, 12, 1, 0x0));
                }
                else
                {
                    /* Not possible, but in case we reach here. */
                    MYD_DBG_ERROR("mydRClkSelectSource: Invalid port:%d selected for X7120 CLK_OUT_SE1 Pin.\n", portSelect);
                    MYD_DBG_ERROR("mydRClkSelectSource: X7120 CLK_OUT_SE1 Pin can only output RCLK from Port2 and Port3.\n");
                    return MYD_FAIL;
                }
                break;

            case MYD_PIN_CLK_OUT_SE2:
                rClkId = MYD_RCLK_C;
                MUXOffset = 13;

                if (portSelect == pDev->mdioPort+3)
                {
                    ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort+3, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, MUXOffset, 1, 0x0));
                    break;
                }
                else
                {
                    ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort+3, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, MUXOffset, 1, 0x1));
                }

                if (portSelect == pDev->mdioPort+2)
                {
                    ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort+2, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, MUXOffset, 1, 0x0));
                    break;
                }
                else
                {
                    ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort+2, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, MUXOffset, 1, 0x1));
                }

                if (portSelect == pDev->mdioPort+1)
                {
                    ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort+1, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, MUXOffset, 1, 0x0));
                    break;
                }
                else
                {
                    ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort+1, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, MUXOffset, 1, 0x1));
                }

                if (portSelect == pDev->mdioPort)
                {
                    ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, MUXOffset, 1, 0x0));
                }
                else
                {
                    ATTEMPT(mydHwSetPhyRegField(pDev, pDev->mdioPort, MYD_PORT_REG, MYD_PORT_RCVCLK_CTRL1, MUXOffset, 1, 0x1));
                }
                break;

            case MYD_PIN_CLK_OUT_DIFF_N:
            case MYD_PIN_CLK_OUT_DIFF_P:
                if (pinId == MYD_PIN_CLK_OUT_DIFF_N)
                {
                    rClkId = MYD_RCLK_D;
                }
                else
                {
                    rClkId = MYD_RCLK_E;
                }
                /* Only supports Port3, no selection needed */
                if (portSelect != pDev->mdioPort+3)
                {
                    MYD_DBG_ERROR("mydRClkSelectSource: Invalid port:%d selected for X7120 CLK_OUT_DIFF Pin.\n", portSelect);
                    MYD_DBG_ERROR("mydRClkSelectSource: X7120 CLK_OUT_DIFF Pin can only output RCLK from Port3.\n");
                    return MYD_FAIL;
                }
                break;

            default:
                MYD_DBG_ERROR("mydRClkSelectSource: Invalid Pin selected: %d\n", pinId);
                return MYD_FAIL;
        }
    }
    else if (pDev->deviceId == MYD_DEV_X6141)
    {
        /* Only one port on the x6141, no selection needed */
        switch(pinId)
        {
            case MYD_PIN_INTn:
                rClkId = MYD_RCLK_A;
                break;
            case MYD_PIN_CLK_OUT_SE1:
                rClkId = MYD_RCLK_B;
                break;
            case MYD_PIN_CLK_OUT_SE2:
                rClkId = MYD_RCLK_C;
                break;
            default:
                MYD_DBG_ERROR("mydRClkSelectSource: Invalid Pin selected: %d\n", pinId);
                return MYD_FAIL;
        }
    }
    else
    {
        MYD_DBG_ERROR("mydRClkSelectSource: Unknown or unsupported device: 0x%x.\n", pDev->deviceId);
        return MYD_FAIL;
    }

    /* Not possible but in case we are here, to avoid array index access out of range */
    if (rClkId >= MYD_RCLK_NUMS)
    {
        MYD_DBG_ERROR("mydRClkSelectSource: Invalid MYD_RCLK_ID\n");
        return MYD_FAIL;
    }
    if (!(interfaceSelect == MYD_LINE_SIDE || interfaceSelect == MYD_HOST_SIDE))
    {
        MYD_DBG_ERROR("mydRClkSelectSource: Invalid side selected\n");
        return MYD_FAIL;
    }

    /* Select which interface provide the clock source */
    ATTEMPT(mydHwSetPhyRegField(pDev, portSelect, MYD_PORT_REG, RCLK_TABLE[rClkId][MYD_RTABLE_MUX_REG],
                                (MYD_U8)RCLK_TABLE[rClkId][MYD_RTABLE_SIDE_BIT], 1, interfaceSelectMuxValue));
    /* Select MUX */
    ATTEMPT(mydHwSetPhyRegField(pDev, portSelect, MYD_PORT_REG, RCLK_TABLE[rClkId][MYD_RTABLE_MUX_REG],
                                (MYD_U8)RCLK_TABLE[rClkId][interfaceSelect], 1, topLevelMuxValue));

    return MYD_OK;
}
