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
**
* @file mcdApiTypes.h
*
* @brief This file contains common types and defines across the Marvell MCD driver.
*
********************************************************************************
*/


#ifndef MCD_TYPES_H
#define MCD_TYPES_H

#define DB_TEST_ENVIRONMENT 0 /* set to 0 for host environment */
                              /* set to 1 to build sample code */
                              /* to interface to Marvell DB via SMI board */

#define MCD_ENABLE_SERDES_API 1 /* Set to 1 to include the SERDES API.
                                   All SERDES source files in the serdes folder
                                   are needed to be in the makefile. Otherwise,
                                   it will generate build errors. */

#if DB_TEST_ENVIRONMENT
#define MCD_INCLUDE_STUBS /* comment out stub functions not fully implemented */
#endif

//#define MCD_DEBUG         /* comment out all print code/data */

#define C_LINKAGE 1 /* set to 1 if C compile/linkage on C files is desired with C++ */

#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif


#undef IN
#define IN
#undef OUT
#define OUT
#undef INOUT
#define INOUT

#define STATIC static

#ifndef NULL
#define NULL ((void*)0)
#endif
#define VAR_32BIT   int

#define VAR_64BIT   long long

typedef char      MCD_8;
typedef short     MCD_16;
typedef VAR_32BIT MCD_32;
typedef int       MCD_INT;
typedef VAR_64BIT MCD_64;
typedef void      MCD_VOID;
typedef void*     MCD_PVOID;

typedef unsigned char           MCD_U8;
typedef unsigned short          MCD_U16;
typedef unsigned VAR_32BIT      MCD_U32;
typedef unsigned int            MCD_UINT;
typedef signed short            MCD_S16;

typedef unsigned VAR_64BIT      MCD_U64;

/* type MCD_UINTPTR is unsigned integer that may hold value of pointer */
typedef unsigned long MCD_UINTPTR;

typedef union
{
    MCD_U8   c[8];
    MCD_U16  s[4];
    MCD_U32  l[2];
}MCD_UNION64;

typedef enum {
    MCD_FALSE = 0,
    MCD_TRUE  = 1
} MCD_BOOL;

#define MCD_ENABLE    1
#define MCD_DISABLE   0

#define DONT_CARE 0xFFFF

#define MCD_CONVERT_BOOL_TO_UINT(boolVar,uintVar) {(boolVar) ? (uintVar=1) : (uintVar=0);}
#define MCD_CONVERT_UINT_TO_BOOL(uintVar,boolVar) {(uintVar) ? (boolVar=MCD_TRUE) : (boolVar=MCD_FALSE);}
#define MCD_GET_BOOL_AS_BIT(boolVar) ((boolVar) ? 1 : 0)
#define MCD_GET_BIT_AS_BOOL(uintVar) ((uintVar) ? MCD_TRUE : MCD_FALSE)

typedef MCD_U32 MCD_STATUS;
#define MCD_OK       0    /* Operation succeeded */
#define MCD_FAIL     1    /* Operation failed    */
#define MCD_PENDING  2    /* Pending  */
#define MCD_BAD_PTR  3   /* Pointer is NULL */
#define MCD_OUT_OF_CPU_MEM 4 /* Alocation failed */
#define MCD_HCD_NOT_FOUND 5 /* HCD not found */
#define MCD_CREATE_ERROR  (0x0A) /* Fail while creating an item           */

#define MCD_MAX_CHANNEL_NUM_PER_SLICE      4 /* number of lanes per slice in X5123 */
#define MCD_MAX_SLICE_NUM                  2 /* number of slices in X5123 */
#define MCD_MAX_PORT_NUM                   8 /* max port number in X5123 */
#define MCD_MAX_SERDES_NUM                 16

#define MCD_NUM_LANES       4 /* number of serdes lanes for 100G and 40G PCS */

#define MCD_UMAC_INTERRUPT_INTRAW_SYNC  0x800/* defines los of sync bit in umac interrupt raw register*/

/* Defines for mcdInitDriver() and all API functions which need MCD_DEV */
typedef struct _MCD_DEV MCD_DEV;
typedef MCD_DEV *MCD_DEV_PTR;

typedef MCD_STATUS (*FMCD_READ_MDIO)(
                        MCD_DEV_PTR pDev,
                        MCD_U16 mdioPort,
                        MCD_U16 mmd,
                        MCD_U16 reg,
                        MCD_U16* value);

typedef MCD_STATUS (*FMCD_WRITE_MDIO)(
                        MCD_DEV_PTR pDev,
                        MCD_U16 mdioPort,
                        MCD_U16 mmd,
                        MCD_U16 reg,
                        MCD_U16 value);


/**
* @enum MCD_SIDE_ENT
 *
 * @brief Enumeration for device side.
*/
typedef enum
{
    /** @brief Host Side       */
    MCD_SIDE_HOST,
    /** @brief Line Side       */
    MCD_SIDE_LINE,
    /** @brief Both Sides       */
    MCD_SIDE_BOTH
}MCD_SIDE_ENT;


/**
* @enum MCD_BOOT_MODE
 *
 * @brief Enumeration for boot mode.
*/
typedef enum
{
    /** @brief Regular Mode            */
    MCD_REGULAR_BOOT_MODE,
    /** @brief High Availability Mode  */
    MCD_HIGH_AVAILABILITY_BOOT_MODE
}MCD_BOOT_MODE;

/* operational mode configuration */
/* those ifdef 0 are not supported in this release */

/* Note: MCD_MODE_P100_40_CK: AutoNeg with multi-speed selection. Requires
   polling for mcdAutoNegCheckCompleteExt() after calling mcdOneSideSetMode() */
typedef enum
{
    MCD_MODE_UNKNOWN,    /* 0 */
    MCD_MODE_P100_40_C,  /* 1 AutoNeg with both 40G/100G CR4 advertised */
    MCD_MODE_P100L,      /* 2 X5121 and X5123: 100G-LR4 PCS No FEC No AN */
    MCD_MODE_P100S,      /* 3 X5121 and X5123: 100G-SR4 PCS w/FEC No AN */
    MCD_MODE_P100C,      /* 4 X5121 and X5123: 100G-CR4 PCS w/FEC AN advertises only 100G-CR4 */
    MCD_MODE_P100K,      /*  5 X5121 and X5123: 100G-KR4 PCS w/FEC AN advertises only 100G-KR4*/
    MCD_MODE_P40L,       /* 6 X5121, X5123 and X2381: 40G-LR4/SR4 PCS No FEC No AN */
    MCD_MODE_P40C,       /* 7 X5121, X5123 and X2381: 40G-CR4 PCS No FEC AN advertises only 40G-CR4 */
    MCD_MODE_P40K,       /* 8 X5121, X5123 and X2381: 40G-KR4 PCS No FEC AN advertises only 40G-KR4 */
    MCD_MODE_P100_40_K,  /* 9 AutoNeg with both 40G/100G KR4 advertised */
                         /* Repeater Modes */
    MCD_MODE_R100L,      /* 10 X5121 and X5123 */
    MCD_MODE_R100C,      /* 11 X5121 and X5123 */
    MCD_MODE_R25L,       /* 12 X5121 and X5123 */
    MCD_MODE_R25C,       /* 13 X5121 and X5123 */
    MCD_MODE_BM21L,      /* 14 X5121 only */
    MCD_MODE_BM21C,      /* 15 X5121 only */

    MCD_MODE_R10L,       /* 16 X5121, X5123 and X2381: 10GB-SR/LR repeater mode No PCS/FEC/AN */
    MCD_MODE_R10K,       /* 17 X5121, X5123 and X2381: 10GB-CR/KR repeater mode No PCS/FEC AN enabled */

    MCD_MODE_R40L,       /* 18 X5121, X5123 and X2381 */
    MCD_MODE_R40C,       /* 19 X5121, X5123 and X2381 */

                         /* MLG Modes */
    MCD_MODE_G10L,       /* 20 X5111 */
    MCD_MODE_G10S,
    MCD_MODE_G10C,
    MCD_MODE_G10K,
    MCD_MODE_G14L,
    MCD_MODE_G14S,
    MCD_MODE_G14C,
    MCD_MODE_G14K,
    MCD_MODE_G41L,
    MCD_MODE_G41S,
    MCD_MODE_G41C,
    MCD_MODE_G41K,
    MCD_MODE_G44L,
    MCD_MODE_G44S,
    MCD_MODE_G44C,
    MCD_MODE_G44K,
    MCD_MODE_G100L,
    MCD_MODE_G100S,
    MCD_MODE_G100C,
    MCD_MODE_G100K,
                            /* new modes for X5123                                     */
    MCD_MODE_P50R2L,        /* 40  50GBase-R2                                              */
    MCD_MODE_P50R2S,        /* 41 50GBase-R2                                              */
    MCD_MODE_P40R2L,        /* 42 40GBase-R2                                              */
    MCD_MODE_P40R2S,        /* 43 40GBase-R2                                              */
    MCD_MODE_P25L,          /* 44 25GBase-R1                                              */
    MCD_MODE_P25S,          /* 45 25GBase-R1                                              */
    MCD_MODE_P10L,          /* 46 10GBase-R1                                              */
    MCD_MODE_P10S,          /* 47 10GBase-R1                                              */
    MCD_MODE_P2_5,          /* 48 2.5Gusxgmii                                             */
    MCD_MODE_P1,            /* 49 1000Base-X                                              */
    MCD_MODE_G21L,          /* 50 GEARBOX 40GBase-R2 (host Side) to 40GBase-R4 (Line Side)*/
    MCD_MODE_P40S,          /* 51 40GBase-R4 with FEC                                     */
    MCD_MODE_P2_5S,         /* 52 2.5G Basex                                              */
    MCD_MODE_P1_SGMII,      /* 53 1G SGMII                                                */
    MCD_MODE_R1L,           /* 54 1000Base-X repeater mode No PCS/FEC/AN                  */
    MCD_MODE_R1C,           /* 55 1000Base-X repeater mode                                */
    MCD_MODE_P1_BaseX_SGMII,/* 56 host side - SGMII, line side - 1000BaseX                 */
    MCD_MODE_G21SK,         /* 57 GEARBOX 40GB-R2(host Side) to 40GB-R4(Line Side): w/AN,FC-FEC or w/oAN,RS-FEC(host only) */
    MCD_MODE_P20L,          /* 58 20GBase-R1                                              */
    MCD_MODE_P20S,          /* 59 20GBase-R1 with FEC and AN                              */

    MCD_MODE_NUM
} MCD_OP_MODE;

/* do not rearrange the order */
typedef enum
{
    MCD_MLG_10G,
    MCD_MLG_10G_40G,
    MCD_MLG_40G_10G,
    MCD_MLG_40G_40G,
    MCD_TRANSPARENT,
    MCD_PCS,
    MCD_40G_INTERLEAVED,/*Line side only*/
    MCD_POWER_DOWN,
    MCD_RESERVED_MODE,
    MCD_MLG_10GX4, /*40G via 4 lanes each 10G, X5123 related*/
    MCD_MLG_20GX2, /*40G via 2 lanes each 20G, X5123 related*/
    MCD_MODES_NUM
} MCD_MODE;


typedef enum
{
    MCD_P100G_STEERING,
    MCD_P40G_STEERING,
    MCD_4P_P25G_STEERING,
    MCD_4P_P10G_STEERING,
    MCD_P100G_P40G_P10G_STEERING_AP,
    MCD_4P_P25G_STEERING_AP,
    MCD_4P_P10G_STEERING_AP,
    MCD_4P_P1G_1000BaseX_STEERING,
    MCD_4P_P1G_SGMII_STEERING,
    MCD_G21L_NONE_STEERING,
    MCD_G21L_P10G_NONE_STEERING_AP,
    MCD_1P_P25G_STEERING,
    MCD_1P_P10G_STEERING,
    MCD_1P_P10G_25G_STEERING_AP,
    MCD_1P_P1G_1000BaseX_STEERING,
    MCD_1P_P1G_SGMII_STEERING
} MCD_LANE_STEERING_MODE;

/* do not rearrange the order */
typedef enum
{
    MCD_10GB_SLR,
    MCD_10GB_CKR,
    MCD_25GB_SLR,
    MCD_25GB_CKR,
    MCD_40GB_SLR4,
    MCD_40GB_CR4,
    MCD_40GB_KR4,
    MCD_RESERVED,
    MCD_100GB_LR4,
    MCD_100GB_SR4,
    MCD_100GB_CR4,
    MCD_100GB_KR4,
    MCD_40GB_SLR2,
    MCD_40GB_CR2,
    MCD_40GB_KR2,
    MCD_50GB_SLR2,
    MCD_50GB_CR2,
    MCD_50GB_KR2,
    MCD_2_5GB_R_LINE,
    MCD_1GB_R_LINE,
    MCD_20GB_SLR,
    MCD_SPEED_NUM
} MCD_LINE_SPEED;

/* do not rearrange the order */
typedef enum
{
   MCD_10GB_R=0,
   MCD_25GB_R=2,
   MCD_40GB_R4=4,
   MCD_20GB_R2=6,
   MCD_100GB_R4=8,
   MCD_100GB_R10=15,
   MCD_40GB_R2,
   MCD_50GB_R2,
   MCD_2_5GB_R,
   MCD_1GB_R,
   MCD_20GB_R,
} MCD_HOST_SPEED;

typedef enum
{
    MCD_UNKNOWN_SPEED,
    MCD_10GB,
    MCD_20GB,
    MCD_25GB,
    MCD_40GB,
    MCD_100GB,
    MCD_2_5GB,
    MCD_1GB,
    MCD_50GB
} MCD_MODE_SPEED;


/* MCD device IDs list (TBD X5121)*/
/* WARNING: If you add/modify this list, you must also modify mcdIsPhyRevisionValid() */
typedef enum
{
    MCD_REV_UNKNOWN = 0,
    MCD_REV_X5121,
    MCD_REV_X5111,
    MCD_REV_X2381,
    MCD_REV_X5123,
    MCD_REV_EC808
} MCD_DEVICE_ID;

/* defines the reference clock selection */
typedef enum
{
    MCD_PRIMARY_CLK,
    MCD_SECONDARY_CLK
} MCD_REF_CLK_SEL;

/* defines the reference clock ratio*/
typedef enum
{
    MCD_REF_CLK_DISABLE,
    MCD_REF_CLK_NO_DIV,
    MCD_REF_CLK_DIV_BY_2,
    MCD_REF_CLK_DIV_BY_4
} MCD_REF_CLK_DIV;

/* NO-PPM squelch modes */
typedef enum
{
    MCD_NO_PPM_OFF_MODE,             /* noPpmMode disabled */
    MCD_NO_PPM_NORMAL_MODE,          /* regular noPpmMode */
    MCD_NO_PPM_RX_SQUELCH_MODE,      /* squelch noPpmMode - CM3 will squelch the rx clock in case of singal loss*/
    MCD_NO_PPM_SEND_FAULT_MODE       /* fault noPpmMode - CM3 will send fault in case of signal loss*/
} MCD_NO_PPM_MODE;

/* FEC types */
typedef enum
{
    MCD_NO_FEC,                 /* No FEC (Backward compatible) */
    MCD_RS_FEC,                 /* RS FEC at both sides (Backward compatible) */
    MCD_FC_FEC,                 /* FC FEC at both sides (Backward compatible) */
    MCD_RS_FEC_HOST = 4,        /* RS FEC at host side*/
    MCD_FC_FEC_HOST = 8,        /* FC FEC at host side*/
    MCD_RS_FEC_LINE = 0x10,     /* RS FEC at line side*/
    MCD_FC_FEC_LINE = 0x20      /* FC FEC at line side*/
} MCD_FEC_TYPE;

/* defines on which pin of the device RX clock is set (RCLK0, RCLK1 or  RCLK2*/
typedef enum {
    MCD_RCLK_CTRL0,
    MCD_RCLK_CTRL1,
    MCD_RCLK_CTRL2
}MCD_RX_CLOCK_CTRL_TYPE;

/* defines the RX clock divide value*/
typedef enum
{
    MCD_RCLK_DIV_BY_8,
    MCD_RCLK_DIV_BY_16,
    MCD_RCLK_DIV_BY_32,
    MCD_RCLK_DIV_BY_64
} MCD_RCLK_DIV_VAL;

/* defines the pin that output the selected recovered clock */
typedef enum
{
    MCD_SCL_SDA, /* RCLK0/RCLK1 */
    MCD_INT_N    /* RCLK2 */
} MCD_RCLK_OUT_PIN;

/* defines the master Slice # */
typedef enum
{
    MCD_SLICE0, /* slice Zero as master */
    MCD_SLICE1, /* slice one as master */
    MCD_DUAL_SLICE /* for dual slice no need master */
} MCD_MASTER_SLICE;

typedef struct
{
    MCD_U32                              phyPortNum;
    MCD_RX_CLOCK_CTRL_TYPE                clckCtrl;
}MCD_RX_CLOCK_CTRL;

#include "mcdInternalShmIpc.h"
#include "mcdInternalIpcDefs.h"
#include "mcdHwSerdesCntl.h"


typedef enum
{
    MCD_LANE_REMAP_DISABLE,
    MCD_LANE_REMAP_ENABLE
} MCD_LANE_REMAP_MODE;

typedef struct
{
    MCD_SERDES_TXRX_LANE_REMAP  sliceZeroHostRemap[MCD_MAX_CHANNEL_NUM_PER_SLICE];
    MCD_SERDES_TXRX_LANE_REMAP  sliceOneHostRemap[MCD_MAX_CHANNEL_NUM_PER_SLICE];
} MCD_LANE_STEERING_HOST_REMAP_CFG;

typedef struct
{
    MCD_REF_CLK_SEL      lsRefClkSel;
    MCD_REF_CLK_SEL      hsRefClkSel;
    MCD_REF_CLK_DIV      lsRefClkDiv;
    MCD_REF_CLK_DIV      hsRefClkDiv;
} MCD_SERDES_REF_CLK;

typedef struct
{
    MCD_U8     rxPolarity;
    MCD_U8     txPolarity;

}MCD_AP_SERDES_CONFIG_DATA;
typedef MCD_AP_SERDES_CONFIG_DATA *MCD_AP_SERDES_CONFIG_DATA_PTR;

typedef struct
{
    MCD_U16                     numOfLanes; /* number of lanes                                            */
    MCD_AP_SERDES_CONFIG_DATA*  params;     /* pointer to array that consists TX and RX polarity per lane */
}MCD_CONFIG_SERDES_AP_PARAM;
typedef MCD_CONFIG_SERDES_AP_PARAM *MCD_CONFIG_SERDES_AP_PARAM_PTR;

typedef enum
{
    MCD_CTLE_BIAS_NORMAL, /* default bias value */
    MCD_CTLE_BIAS_HIGH /* may be used for short length cables (under 1m) */
}MCD_CTLE_BIAS_VAL;

typedef struct
{
    MCD_CTLE_BIAS_VAL    host;
    MCD_CTLE_BIAS_VAL    line;
}MCD_CTLE_BIAS_CONFIG;

/**
* @struct MCD_PORT_AP_SERDES_RX_CONFIG
 *
 * @brief Structure for serdes RX parameters
 * to take place during AP port init TRx training
*/
typedef struct{

    /** 310) */
    MCD_U16 squelch;

    /** Frequency  (rang: 0 */
    MCD_U8 lowFrequency;

    /** Frequency (rang: 0 */
    MCD_U8 highFrequency;

    /** Gain value    (rang: 0 */
    MCD_U8 dcGain;

    /** width   (rang: 0 */
    MCD_U8 bandWidth;

    /** width (rang: 0 */
    MCD_U8 loopBandwidth;

    /** @brief 31)
     *  etlMinDelay  ETL max delay    (rang: 0-31)
     */
    MCD_U8 etlMinDelay;

    MCD_U8 etlMaxDelay;

    /** Etl enable(override defaults) */
    MCD_BOOL etlEnable;

    /** @brief field bitmap
     *  speed   - serdes speed associated with the config values
     */
    MCD_U16 fieldOverrideBmp;

    MCD_SERDES_SPEED serdesSpeed;

} MCD_PORT_AP_SERDES_RX_CONFIG;

#define MCD_MAN_TUNE_CTLE_CONFIG_SQLCH_CNS           0x1
#define MCD_MAN_TUNE_CTLE_CONFIG_LF_CNS              0x2
#define MCD_MAN_TUNE_CTLE_CONFIG_HF_CNS              0x4
#define MCD_MAN_TUNE_CTLE_CONFIG_DCGAIN_CNS          0x8
#define MCD_MAN_TUNE_CTLE_CONFIG_BANDWIDTH_CNS       0x10
#define MCD_MAN_TUNE_CTLE_CONFIG_LOOPBANDWIDTH_CNS   0x20
#define MCD_MAN_TUNE_ETL_MIN_DELAY_CNS               0x40
#define MCD_MAN_TUNE_ETL_MAX_DELAY_CNS               0x80
#define MCD_MAN_TUNE_ETL_ENABLE_CNS                  0x100

typedef struct
{
    MCD_U16 txAmp;
    MCD_U16 emph0;
    MCD_U16 emph1;
    MCD_U8 txOverrideBmp;
    MCD_SERDES_SPEED serdesSpeed;

}MCD_PORT_AP_SERDES_TX_CONFIG;

#define MCD_MAN_TUNE_TX_CONFIG_AMP_CNS           0x1
#define MCD_MAN_TUNE_TX_CONFIG_EMPH0_CNS         0x2
#define MCD_MAN_TUNE_TX_CONFIG_EMPH1_CNS         0x4


#define MCD_MAN_TUNE_CTLE_CONFIG_10G_INDEX_CNS       0
#define MCD_MAN_TUNE_CTLE_CONFIG_25G_INDEX_CNS       1

#define MCD_AP_OPTIONS_G21_MODE_CNS          0x1
#define MCD_AP_OPTIONS_1G_SGMII_MODE_CNS     0x2
#define MCD_AP_OPTIONS_AN_ADV_ENABLE         0x4

typedef struct
{
    MCD_U32                              serdesSpeed;
    MCD_MAN_TUNE_CTLE_CONFIG_DATA        ctleParams;
    MCD_ETL_CONFIG_DATA                  etlParams;
    MCD_U16                              fieldOverrideBmp;
}MCD_MAN_TUNE_CTLE_CONFIG_OVERRIDE;

typedef struct
{
    MCD_BOOL                            retimerEnable;
    MCD_U32                             laneNum;
    MCD_U32                             modeVector;
    MCD_BOOL                            fcPause;
    MCD_BOOL                            fcAsmDir;
    MCD_FEC_TYPE                        fecSup;
    MCD_FEC_TYPE                        fecReq;
    MCD_FEC_TYPE                        fecSupConsortium;
    MCD_FEC_TYPE                        fecReqConsortium;
    MCD_BOOL                            nonceDis;
    MCD_BOOL                            apEnable;
    MCD_CONFIG_SERDES_AP_PARAM_PTR      configApSerdesPtr;
    MCD_CTLE_BIAS_VAL                   ctleBiasVal;
    MCD_U8                              g21Mode;
    MCD_U8                              g1SgmiiMode;
    MCD_BOOL                            enSdTuningApRes;
}MCD_CONFIG_AP_PARAM;
typedef MCD_CONFIG_AP_PARAM *MCD_CONFIG_AP_PARAM_PTR;

typedef struct
{
    MCD_PRE_DEFINED_CTLE_DATA ctleParams[16];
}MCD_PORT_PER_SERDES_CTLE_CONFIG_DATA;

typedef struct
{
    MCD_SERDES_CONFIG_DATA  params[16];
}MCD_PORT_PER_SERDES_CONFIG_DATA;

typedef struct
{
    MCD_U32 minEyeThreshold;
    MCD_U32 maxEyeThreshold;
}MCD_LINE_SIDE_EO_TH_OVERRIDE;

/**
* @struct MCD_LANE_STEERING_OVERRIDE_CFG
 *
*  @brief A struct containing the override parameters for lane
*         steering single port mode
*/
typedef struct
{
    MCD_U16 externalLpbSerdes;
    MCD_U16 internalLpSerdes;
    MCD_U8  txRemap;
    MCD_U8  rxRemap;
}MCD_LANE_STEERING_OVERRIDE_CFG;

typedef struct
{
    MCD_U32 lfHighThreshold;
    MCD_U32 lfLowThreshold;
    MCD_U32 hfThreshold;
} MCD_CONFIDENCE_INTERVAL_PARAMS_OVERRIDE;

typedef struct
{
    MCD_NO_PPM_MODE                                noPpmMode;
    MCD_PORT_PER_SERDES_CONFIG_DATA*               electricalParamsPtr;
    MCD_CONFIG_AP_PARAM_PTR                        configApPtr;
    MCD_SERDES_REF_CLK                             refClk;
    MCD_CTLE_BIAS_CONFIG                           ctleBiasParams;
    MCD_PORT_PER_SERDES_CTLE_CONFIG_DATA*          ctleParamsPtr;
    MCD_CTLE_CALIBRATION_MODE_E                    calibrationMode;
    MCD_CALIBRATION_ALGO_E                         calibrationAlgo;
    MCD_LINE_SIDE_EO_TH_OVERRIDE*                  eyeThresholdPtr;
    MCD_CONFIDENCE_INTERVAL_PARAMS_OVERRIDE*       confidenceParamsPtr;
    MCD_LANE_STEERING_OVERRIDE_CFG*                laneSteerCfgPtr;
}MCD_MODE_CONFIG_PARAM;
typedef MCD_MODE_CONFIG_PARAM *MCD_MODE_CONFIG_PARAM_PTR;

/*
 * Reference Clock configuration
 *   refClockFreq   - Reference clock frequency
 *   refClockSource - Reference clock source
 */
typedef struct
{
    MCD_U32  refClockFreq;
    MCD_U32  refClockSource;
}MCD_REF_CLOCK_CFG;

/*
 * AP configuration parameters:
 *   apLaneNum   - lane number inside a port (if not 0, pre AP port number isn't guarantee)
 *   modesVector - bitmap of supported port modes (IEEE capabilities):
 *                     _1000Base_KX_Bit0 = 1,
 *                     _10GBase_KX4_Bit1 = 2,
 *                     _10GBase_KR_Bit2  = 4,
 *                     _40GBase_KR4_Bit3 = 8,
 *                     _40GBase_CR4_Bit4 = 16,
 *                     _100GBase_KR10_Bit5 = 32
 *   fcPause        - FC pause (true/false)
 *   fcAsmDir       - FC ASM_DIR (Annex 28B)
 *   fecSup         - FEC ability (MCD_NO_FEC, MCD_RS_FEC, MCD_FC_FEC)
 *   fecReq         - Request link partner to enable FEC ((MCD_NO_FEC, MCD_RS_FEC, MCD_FC_FEC))
 *   nonceDis       - indicates the port mode for the AP-Init (In loopback
 *                    Nonce detection is disabled)
 *   polarityVector - Vector that defines all serdeses polarity - 2 bits per serdes - even - Rx polarity
                                                                                      odd  - Tx polarity
*/
typedef struct
{
    MCD_U32                modesVector;
    MCD_U32                apLaneNum;
    MCD_BOOL               retimerMode;
    MCD_BOOL               fcPause;
    MCD_BOOL               fcAsmDir;
    MCD_FEC_TYPE           fecSup;
    MCD_FEC_TYPE           fecReq;
    MCD_BOOL               nonceDis;
    MCD_U32                polarityVector;
    MCD_U8                 ctleBiasVal;
    MCD_U8                 noPpmMode;
    MCD_U8                 options;
    MCD_BOOL               enSdTuningApRes;
}MCD_AP_CFG;

typedef MCD_AP_CFG *MCD_AP_CFG_PTR;

/* Autonegotiation results */
typedef struct
{
    MCD_U32                  hcdResult;         /*the auto negotiation resolution in capabilities vector*/
    MCD_FEC_TYPE             hcdFec;            /*FEC negotiation resolution*/
    MCD_BOOL                 hcdFcRxPauseEn;    /*FC Rx pause resolution*/
    MCD_BOOL                 hcdFcTxPauseEn;    /*FC Tx pause resolution*/
}MCD_AP_RESOLUTION;

typedef struct _MCD_MODE_CONFIG
{
    IN MCD_OP_MODE  portMode;         /* operational mode */
    IN MCD_U16      autoNegAdvSpeed;  /* Advertised speed(s) for Auto Neg, only for AN modes */
    IN MCD_U16      autoNegAcquSpeed; /* Acquired speed(s) for Auto Neg, only for AN modes */
    IN MCD_FEC_TYPE fecCorrect;       /* FEC correct */
    IN MCD_NO_PPM_MODE noPpmMode;     /* noPpmMode */
} MCD_MODE_CONFIG,  *PMCD_MODE_CONFIG;

/**
* @struct MCD_LANE_STEERING_CONFIG
 *
*  @brief A struct containing the data base
*  of lane steering configuration
*/
typedef struct
{
    MCD_BOOL  laneSteeringEnable;
    MCD_MASTER_SLICE  masterSlice;
    MCD_BOOL  reducedRxTraining;
    MCD_BOOL  singlePortEnable[MCD_MAX_PORT_NUM];
    MCD_U16   externalLpPort[MCD_MAX_PORT_NUM];
    MCD_U16   internalLpPort[MCD_MAX_PORT_NUM];
    MCD_U16   externalLpSerdes[MCD_MAX_PORT_NUM];
    MCD_U16   internalLpSerdes[MCD_MAX_PORT_NUM];
    MCD_BOOL  laneSteeringTxRemap[MCD_MAX_SERDES_NUM];
}MCD_LANE_STEERING_CONFIG;

typedef struct
{
    MCD_LANE_REMAP_MODE hostRemapMode;
    MCD_LANE_REMAP_MODE lineRemapMode;
    MCD_U16 hostRxRemapVector;
    MCD_U16 hostTxRemapVector;
    MCD_U16 lineRxRemapVector;
    MCD_U16 lineTxRemapVector;
} MCD_LANE_REMAPING_CONFIG;

typedef Avago_serdes_init_config_t MCD_AVAGO_SERDES_INIT_CFG;
#define MCD_TX_PLL_RECAL 0x1;
#define MCD_RX_PLL_RECAL 0x2;

typedef struct
{
    MCD_AVAGO_SERDES_INIT_CFG  txRxConfigDef;
    MCD_BOOL                   txRxConfigInitalized;
    MCD_SERDES_TX_RX_ENABLE    serdesTxRxEnable;
    MCD_U32                    txRxPllRecal;
} MCD_AVAGO_SERDES_SW_DB;

typedef struct
{
    MCD_AVAGO_SERDES_SW_DB  **txRxAvagoSerdesSwDb;
} MCD_TX_RX_SERDES_SW_DB;

typedef struct
{
    MCD_U8      ctleBiasData[MCD_MAX_SERDES_NUM];
    MCD_BOOL    serdesPowerStatus[MCD_MAX_SERDES_NUM];
    MCD_BOOL    stopAdaptiveFlag[MCD_MAX_SERDES_NUM];
    MCD_U8      serdesLpbkMode[MCD_MAX_PORT_NUM];
} MCD_SERDES_STATUS_DB;

#define MCD_PHY_SHADOW_REG_MAX_INDEX 2

struct _MCD_DEV
{
    OUT MCD_DEVICE_ID   deviceId;                       /* type of device and capabilities */
    OUT MCD_U32         chipRevision;                   /* revision */
    IN  MCD_U16         firstMdioPort;                  /* X5123 PHY Port Address  */
    OUT MCD_U16         portCount;                      /* number of port available in this configuration, 0 (not configured) or 1 or 2 */
    OUT MCD_MODE_CONFIG portConfig[MCD_MAX_PORT_NUM];   /* mode of operation, per port depending on mode */

    OUT MCD_BOOL        devEnabled;                     /* whether mcdInitDriver() called successfully */

    IN FMCD_READ_MDIO   fmcdReadMdio;                   /* passed in function for MDIO Read */
    IN FMCD_WRITE_MDIO  fmcdWriteMdio;                  /* passed in function for MDIO Write */

    IN MCD_PVOID        hostContext;                    /* user specific data for host to pass to the low layer */
#if MCD_ENABLE_SERDES_API
    IN MCD_PVOID        serdesDev;                      /* Device structure for Serdes API */
#endif
    OUT MCD_U8          chnAllocMap[MCD_MAX_SLICE_NUM][MCD_MAX_CHANNEL_NUM_PER_SLICE];
    MCD_AP_CFG          apCfg[MCD_MAX_PORT_NUM];
    MCD_U16             portApCapability[MCD_MAX_PORT_NUM]; /* speed_bits - speeds that advertise during auto-negotiation*/
    /* shadows of SSMI controller 16-bit registers of indirect access to 32-bit registers */
    MCD_LANE_STEERING_CONFIG  laneSteeringCfg;
    MCD_LANE_REMAPING_CONFIG  laneRemapCfg[MCD_MAX_SLICE_NUM];
    MCD_U16             shadowValidBmp;
    MCD_U16             regShadow[MCD_PHY_SHADOW_REG_MAX_INDEX];
    MCD_RX_CLOCK_CTRL   rxCloclControl[MCD_MAX_SLICE_NUM];
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
    MCD_U32                     mcdIpcQueueIdPool[MCD_MAX_HOST2SCPU_REQ_MSG_NUM];     /* IPC queue IDs pool */
    MCD_IPC_STATISTICS_STRUCT   mcdIpcStatistics;                     /* the structure to gather IPC statistics on Host*/
    MCD_IPC_SHM_STC             shm; /* IPC sared mempory message send/receive */
    MCD_AP_RESOLUTION           apRes[MCD_MAX_PORT_NUM];
#endif
    MCD_CTLE_CALIBRATION_MODE_CFG   calibrationCfg[MCD_MAX_PORT_NUM];
    MCD_BOOL                    highAvailabilityMode;
    MCD_BOOL                    haAccessDisable;
    MCD_TX_RX_SERDES_SW_DB      txRxSerdesSwDb;
    MCD_SERDES_STATUS_DB        serdesStatus;
    MCD_BOOL                    noPpmEn[MCD_MAX_PORT_NUM];
};

/* Chip,Port reset types */
typedef enum {
    MCD_SOFT_RESET = 1,
    MCD_HARD_RESET = 2,
} MCD_RESET_TYPE;


#define MCD_GET_PORT_IDX(mcdPDev,mcdMdioPort) ((mcdPDev->firstMdioPort == mcdMdioPort) ? 0 : 1)

#define MCD_MAX_MDIO_NUM 31 /* MDIO number 0 to 31  */

/* MCD ANEG acquired speed in REG 7.0030 */
#define MCD_AN_10GBKR                      0x0008
#define MCD_AN_40GBKR4                     0x0020
#define MCD_AN_40GBCR4                     0x0040
#define MCD_AN_100GBCR10                   0x0100
#define MCD_AN_100GBKP4                    0x0200
#define MCD_AN_100GBKR4                    0x0400
#define MCD_AN_100GBCR4                    0x0800

/* MCD error status driver level 0 */

#define MCD_STATUS_OUT_OF_RANGE        (0x03) /* Value is out of range*/
#define MCD_STATUS_BAD_PARAM           (0x04) /* Illegal parameter in function called  */
#define MCD_STATUS_BAD_PTR             (0x05) /* Illegal pointer value                 */
#define MCD_STATUS_BAD_SIZE            (0x06) /* Illegal size                          */
#define MCD_STATUS_BAD_STATE           (0x07) /* Illegal state of state machine        */
#define MCD_STATUS_SET_ERROR           (0x08) /* Set operation failed                  */
#define MCD_STATUS_GET_ERROR           (0x09) /* Get operation failed                  */
#define MCD_STATUS_CREATE_ERROR        (0x0A) /* Fail while creating an item           */
#define MCD_STATUS_NOT_FOUND           (0x0B) /* Item not found                        */
#define MCD_STATUS_NOT_INITIALIZED     (0x0C) /* Not initialized                    */
#define MCD_STATUS_NO_SUCH             (0x0D) /* No such item                          */
#define MCD_STATUS_TIMEOUT             (0x0E) /* Time Out                              */
#define MCD_STATUS_NO_CHANGE           (0x0F) /* The parameter is already in this value*/
#define MCD_STATUS_NOT_SUPPORTED       (0x10) /* This request is not support           */
#define MCD_STATUS_INVALID_PORT        (0x11) /*Invalid port Number*/
#define MCD_STATUS_FAIL_GET_PHY_ADDR   (0x12) /*Failed to get phy Address*/
#define MCD_STATUS_FAIL_READ_REG       (0x13) /*Failed to read register*/
#define MCD_STATUS_FAIL_WRITE_REG      (0x14) /*Failed to write register*/
#define MCD_STATUS_FAIL_GET_PAGE_ADDR  (0x15) /*Failed to get page Address  */
#define MCD_STATUS_FAIL_WRITE_PAGE_NUM (0x16) /*Writing Page Number failed */
#define MCD_STATUS_FAIL_RESET          (0x17) /*Reset bit is not cleared */
#define MCD_STATUS_NO_DEVICE_FOUND     (0x18) /*Cannot find Marvell Device */
#define MCD_STATUS_UNKNOWN_HW_MOD      (0x19) /*Unknown HW Mode */
#define MCD_STATUS_ERR_DEV_ID          (0x1a) /*Error device ID */
#define MCD_STATUS_ERR_VERSION         (0x1b) /*Error Version */
#define MCD_STATUS_ERR_DEV             (0x1c) /*Invalid device stucture */
#define MCD_STATUS_ERR_INIT            (0x1d) /*Driver init error */
#define MCD_STATUS_FIRMWARE_ERR        (0x1e) /*Load firmware error */
#define MCD_STATUS_SERDES_INIT_ERR     (0x1f) /*Fail to init SERDES */

#define MCD_STATUS_NOT_READY            (0x21)      /* HW unit is not ready       */
#define MCD_STATUS_BAD_VALUE            (0x22)      /* Illegal value        */
#define MCD_NOT_IMPLEMENTED             (0x23)      /* return from yet not implemented finction */
#define MCD_STATUS_NO_RESOURCES         (0x24)      /* Resource not available (memory ...)   */

#define MCD_IO_ERROR                    (0xFFFF)    /* Error reading or writing MDIO register */

#ifdef MCD_SDEBUG
#include "tstSTypes.h"
#endif


#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

/* Enable the MCD_AP_STATE_STATUS_LOG by setting #define
   The reason isn't enabled - it requires 1.1KB of memory 
   in the FW. */
#undef MCD_AP_STATE_STATUS_LOG

#endif /* MCD_TYPES_H */


