/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains common types and defines across the Marvell
X5113 API driver (MXD).
********************************************************************/
#ifndef MXD_TYPES_H
#define MXD_TYPES_H

#define DB_TEST_ENVIRONMENT 0 /* set to 0 for host environment */
                              /* set to 1 to build sample code */
                              /* to interface to Marvell DB via SMI board */

#define MXD_ENABLE_SERDES_API 1 /* Set to 1 to include the SERDES API.
                                   All SERDES source files in the serdes folder
                                   are needed to be in the makefile. Otherwise,
                                   it will generate build errors. */

#if DB_TEST_ENVIRONMENT
#define MXD_DEBUG         /* comment out all print code/data */
#endif

#ifdef MXD_DEBUG
#define MXD_DBG_BUFSIZE 1000

#if MXD_ENABLE_SERDES_API
#undef MXD_DBG_BUFSIZE
#define MXD_DBG_BUFSIZE 200000  /* Large buffer needed for logging the eye diagram. Eye diagram
                              size, depending on resolution, can be > several 100s KBytes.
                              Increase size if needed if mxdDbgPrint shows size error.   */
#endif
#endif

#define C_LINKAGE 1 /* set to 1 if C compile/linkage on C files is desired with C++ */

#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

/* general */

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

typedef char                MXD_8;
typedef short               MXD_16;
typedef long                MXD_32;
typedef int                 MXD_INT;
typedef long long           MXD_64;
typedef void                MXD_VOID;
typedef void*               MXD_PVOID;

typedef unsigned char       MXD_U8;
typedef unsigned short      MXD_U16;
typedef unsigned long       MXD_U32;
typedef unsigned int        MXD_UINT;
typedef signed short        MXD_S16;

typedef unsigned long long  MXD_U64;

typedef enum {
    MXD_FALSE = 0,
    MXD_TRUE  = 1
} MXD_BOOL;

#define MXD_ENABLE    1
#define MXD_DISABLE   0

#define MXD_OK        0    /* Operation succeeded */
#define MXD_FAIL      1    /* Operation failed    */
#define MXD_PENDING   2    /* Pending  */

#define MXD_CONVERT_BOOL_TO_UINT(boolVar,uintVar) {(boolVar) ? (uintVar=1) : (uintVar=0);}
#define MXD_CONVERT_UINT_TO_BOOL(uintVar,boolVar) {(uintVar) ? (boolVar=MXD_TRUE) : (boolVar=MXD_FALSE);}
#define MXD_GET_BOOL_AS_BIT(boolVar) ((boolVar) ? 1 : 0)
#define MXD_GET_BIT_AS_BOOL(uintVar) ((uintVar) ? MXD_TRUE : MXD_FALSE)
#define MXD_GET_PORT_IDX(mxdPDev,mxdMdioPort) ((mxdPDev->mdioPort == mxdMdioPort) ? 0 : 1)

typedef MXD_U32 MXD_STATUS;

#define MXD_NUM_LANES       4 /* number of lanes */
#define MXD_NUM_PCS_LANES  20 /* number of PCS lanes for 100G PCS */
#define MXD_NUM_INTERFACE   2 /* number of interfaces; Host and Line */

#define MXD_HOST_MODE_IDX   0
#define MXD_LINE_MODE_IDX   1
#define MXD_GROUP_IDX       2



/* Defines for mxdInitDriver() and all API functions which need MXD_DEV */
typedef struct _MXD_DEV MXD_DEV;
typedef MXD_DEV *MXD_DEV_PTR;

typedef MXD_STATUS (*FMXD_READ_MDIO)(
                        MXD_DEV_PTR pDev,
                        MXD_U16 mdioPort,
                        MXD_U16 mmd,
                        MXD_U16 reg,
                        MXD_U16* value);

typedef MXD_STATUS (*FMXD_WRITE_MDIO)(
                        MXD_DEV_PTR pDev,
                        MXD_U16 mdioPort,
                        MXD_U16 mmd,
                        MXD_U16 reg,
                        MXD_U16 value);

/* mode configuration */
/* NOTE: The naming is a combination of host and line OP configuration.    */
/* Example: MXD_MODE_P40KN_P25CN, Host OP mode: P40KN, Line OP mode: P25CN */
typedef enum
{
    MXD_MODE_UNKNOWN,

    MXD_MODE_P1X_P1P,      /* mode selection = 1 */
    MXD_MODE_P1X_P1X,

    MXD_MODE_P10LN_P10LF,
    MXD_MODE_P10LN_P10LN,
    MXD_MODE_P10LN_P10KF,
    MXD_MODE_P10LN_P10KN,

    MXD_MODE_P10KN_P10LN,
    MXD_MODE_P10KN_P10KN,
    MXD_MODE_P10KN_P10KF,
    MXD_MODE_P10KF_P10KF,

    MXD_MODE_P25CF_P25BR,  /* mode selection = 11 */
    MXD_MODE_P25CF_P25CF,
    MXD_MODE_P25CF_P25CR,

    MXD_MODE_P25CN_P25BF,
    MXD_MODE_P25CN_P25BN,
    MXD_MODE_P25CN_P25BR,
    MXD_MODE_P25CN_P25CF,
    MXD_MODE_P25CN_P25CN,
    MXD_MODE_P25CN_P25CR,

    MXD_MODE_P25CR_P25BR,  /* mode selection = 20 */
    MXD_MODE_P25CR_P25CR,

    MXD_MODE_P25KF_P25JF,
    MXD_MODE_P25KF_P25JR,
    MXD_MODE_P25KF_P25KF,
    MXD_MODE_P25KF_P25KR,

    MXD_MODE_P25KN_P25JF,  /* mode selection = 26 */
    MXD_MODE_P25KN_P25JN,
    MXD_MODE_P25KN_P25JR,
    MXD_MODE_P25KN_P25KF,
    MXD_MODE_P25KN_P25KN,
    MXD_MODE_P25KN_P25KR,

    MXD_MODE_P25KR_P25JR,  /* mode selection = 32 */
    MXD_MODE_P25KR_P25KR,

    MXD_MODE_P25LF_P25LF,
    MXD_MODE_P25LF_P25LR,

    MXD_MODE_P25LN_P25LF,  /* mode selection = 36 */
    MXD_MODE_P25LN_P25LN,
    MXD_MODE_P25LN_P25LR,
    MXD_MODE_P25LR_P25LR,

    MXD_MODE_P40LN_P25CN,  /* mode selection = 40 */
    MXD_MODE_P40LN_P25CF,
    MXD_MODE_P40LN_P25CR,
    MXD_MODE_P40LN_P25BN,
    MXD_MODE_P40LN_P25BF,
    MXD_MODE_P40LN_P25BR,
    MXD_MODE_P40LN_P25LF,
    MXD_MODE_P40LN_P25LR,
    MXD_MODE_P40LN_P25LN,

    MXD_MODE_P40KN_P25CN,  /* mode selection = 49 */
    MXD_MODE_P40KN_P25CF,
    MXD_MODE_P40KN_P25CR,
    MXD_MODE_P40KN_P25BN,
    MXD_MODE_P40KN_P25BF,
    MXD_MODE_P40KN_P25BR,
    MXD_MODE_P40KN_P25LR,

    MXD_MODE_P40KN_P25KN,  /* mode selection = 56 */
    MXD_MODE_P40KN_P25KF,
    MXD_MODE_P40KN_P25KR,
    MXD_MODE_P40KF_P25KN,
    MXD_MODE_P40KF_P25KF,
    MXD_MODE_P40KF_P25KR,

    MXD_MODE_P40KN_P25JN,  /* mode selection = 62 */
    MXD_MODE_P40KN_P25JF,
    MXD_MODE_P40KN_P25JR,
    MXD_MODE_P40KF_P25JN,
    MXD_MODE_P40KF_P25JF,
    MXD_MODE_P40KF_P25JR,

    MXD_MODE_P40LN_P25BCN, /* mode selection = 68 */
    MXD_MODE_P40LN_P25BCF,
    MXD_MODE_P40LN_P25BCR,
    MXD_MODE_P40KN_P25BCN,
    MXD_MODE_P40KN_P25BCF,
    MXD_MODE_P40KN_P25BCR,

    MXD_MODE_P40KN_P25JKN, /* mode selection = 74 */
    MXD_MODE_P40KN_P25JKF,
    MXD_MODE_P40KN_P25JKR,
    MXD_MODE_P40KF_P25JKN,
    MXD_MODE_P40KF_P25JKF,
    MXD_MODE_P40KF_P25JKR,

    MXD_MODE_P40CN_P40CN, /* mode selection = 80 */
    MXD_MODE_P40CN_P40CF,
    MXD_MODE_P40CF_P40CF,
    MXD_MODE_P40KN_P40KN,
    MXD_MODE_P40KN_P40KF,
    MXD_MODE_P40KF_P40KF,
    MXD_MODE_P40LN_P40LN,

    MXD_MODE_P50BN_P50BN, /* mode selection = 87 */
    MXD_MODE_P50BN_P50BF,
    MXD_MODE_P50BN_P50BR,
    MXD_MODE_P50BF_P50BF,
    MXD_MODE_P50BF_P50BR,
    MXD_MODE_P50BR_P50BR,

    MXD_MODE_P50JN_P50JN, /* mode selection = 93 */
    MXD_MODE_P50JN_P50JF,
    MXD_MODE_P50JN_P50JR,
    MXD_MODE_P50JF_P50JF,
    MXD_MODE_P50JF_P50JR,
    MXD_MODE_P50JR_P50JR,

    MXD_MODE_P50MN_P50MN, /* mode selection = 99 */
    MXD_MODE_P50MN_P50MF,
    MXD_MODE_P50MN_P50MR,
    MXD_MODE_P50MF_P50MF,
    MXD_MODE_P50MF_P50MR,
    MXD_MODE_P50MR_P50MR,

    MXD_MODE_P50LN_P50BN, /* mode selection = 105 */
    MXD_MODE_P50LN_P50BF,
    MXD_MODE_P50LN_P50BR,
    MXD_MODE_P50LF_P50BN,
    MXD_MODE_P50LF_P50BF,
    MXD_MODE_P50LF_P50BR,

    MXD_MODE_P50LN_P50JN, /* mode selection = 111 */
    MXD_MODE_P50LN_P50JF,
    MXD_MODE_P50LN_P50JR,
    MXD_MODE_P50LF_P50JN,
    MXD_MODE_P50LF_P50JF,
    MXD_MODE_P50LF_P50JR,

    MXD_MODE_P50LN_P50MN, /* mode selection = 117 */
    MXD_MODE_P50LN_P50MF,
    MXD_MODE_P50LN_P50MR,
    MXD_MODE_P50LF_P50MN,
    MXD_MODE_P50LF_P50MF,
    MXD_MODE_P50LF_P50MR,

    MXD_MODE_P50CF_P50CN, /* work-in-progress */
    MXD_MODE_P50KF_P50KN, /* work-in-progress */

    MXD_MODE_P100CR_P100CR, /* mode selection = 125 */
    MXD_MODE_P100KR_P100KR,
    MXD_MODE_P100LN_P100LR,
    MXD_MODE_P100LR_P100LR,

    MXD_MODE_R1_R1,         /* mode selection = 129 */
    MXD_MODE_R10L_R10L,
    MXD_MODE_R25L_R25L,
    MXD_MODE_R40L_R40L,
    MXD_MODE_R100L_R100L,

    MXD_MODE_NUM,

    MXD_MODE_USER_DEFINED = 0xFFFF
} MXD_FIXED_OP_MODE; /* portModeTbl needs to match up with MXD_FIXED_OP_MODE */

/* operational mode configuration for host and line */
/*****************************************************
Type
--------------------------------
P = PCS
R = Retimer

Speed
--------------------------------
1   = 1 Gbps   - single lane
2_5 = 2.5 Gbps - single lane
5   = 5 Gbps   - single lane
10  = 10 Gbps  - single lane
25  = 25 Gbps  - single lane
40  = 40 Gbps  - 4 lanes x 10 Gbps
50  = 50 Gbps  - 2 lanes x 25 Gbps or 4 lanes x 12.5 Gbps
100 = 100 Gbps - 4 lanes x 25 Gbps

Training/AN/Coding
-------------------------------
X = BASE-X
S = SGMII System
P = SGMII PHY
L = BASE-R, no Auto-Negotiation
K = BASE-R, Backplane
C = BASE-R, Twinax
J = Same as K except consortium
B = Same as C except consortium
M = Non-Standard 50GBASE-R2

FEC
--------------------------------
N = No FEC
F = KR-FEC
R = RS-FEC
*****************************************************/
/* opModeTable needs to match up with MXD_OP_CONFIG */
typedef enum
{
    MXD_CONFIG_UNKNOWN,

    MXD_P1X,        /* 1GB mode, 1 lane, non-grouped  = 1*/
    MXD_P1S,        /* 1GB mode, 1 lane, non-grouped */
    MXD_P1P,        /* 1GB mode, 1 lane, non-grouped */  
    MXD_R1,         /* 1GB mode, 1 lane, non-grouped */ 

    MXD_P2_5X,      /* 2.5GB mode, 1 lane, non-grouped  = 5 */
    MXD_R2_5,       /* 2.5GB mode, 1 lane, non-grouped */

    MXD_P5L,        /* 5GB mode, 1 lane, non-grouped   = 7 */ 
    MXD_P5K,        /* 5GB mode, 1 lane, non-grouped   */ 
    MXD_R5,         /* 5GB mode, 1 lane, non-grouped   */

    MXD_P10LN,      /* 10GB mode, 1 lane, non-grouped  = 10 */
    MXD_P10KN,      /* 10GB mode, 1 lane, non-grouped  */
    MXD_P10KF,      /* 10GB mode, 1 lane, non-grouped  */
    MXD_P10LF,      /* 10GB mode, 1 lane, non-grouped  */
    MXD_R10L,       /* 10GB mode, 1 lane, non-grouped  */
    MXD_R10K,       /* 10GB mode, 1 lane, non-grouped  */

    MXD_P25LN,      /* 25GB mode, 1 lane = 16 */
    MXD_P25LF,      /* 25GB mode, 1 lane */
    MXD_P25LR,      /* 25GB mode, 1 lane */
    MXD_P25CN,      /* 25GB mode, 1 lane */
    MXD_P25CF,      /* 25GB mode, 1 lane */
    MXD_P25CR,      /* 25GB mode, 1 lane */
    MXD_P25KN,      /* 25GB mode, 1 lane */
    MXD_P25KF,      /* 25GB mode, 1 lane */
    MXD_P25KR,      /* 25GB mode, 1 lane */

    MXD_P25BN,      /* 25GB mode, 1 lane = 25 */
    MXD_P25BF,      /* 25GB mode, 1 lane */
    MXD_P25BR,      /* 25GB mode, 1 lane */
    MXD_P25JN,      /* 25GB mode, 1 lane */
    MXD_P25JF,      /* 25GB mode, 1 lane */
    MXD_P25JR,      /* 25GB mode, 1 lane */

    MXD_P25BCN,     /* 25GB mode, 1 lane = 31 */ /* Line side only */
    MXD_P25BCF,     /* 25GB mode, 1 lane */ /* Line side only */
    MXD_P25BCR,     /* 25GB mode, 1 lane */ /* Line side only */
    MXD_P25JKN,     /* 25GB mode, 1 lane */ /* Line side only */
    MXD_P25JKF,     /* 25GB mode, 1 lane */ /* Line side only */
    MXD_P25JKR,     /* 25GB mode, 1 lane */ /* Line side only */ 
    MXD_R25L,       /* 25GB mode, 1 lane */
    MXD_R25C,       /* 25GB mode, 1 lane */
    MXD_R25K,       /* 25GB mode, 1 lane */

    MXD_P29P09LN,   /* 29.09GB mode, 4 lanes, grouped */ /* Host side only */

    MXD_P40LN,      /* 40GB mode, 4 lanes, grouped = 41 */
    MXD_P40CN,      /* 40GB mode, 4 lanes, grouped  */
    MXD_P40CF,      /* 40GB mode, 4 lanes, grouped  */
    MXD_P40KN,      /* 40GB mode, 4 lanes, grouped  */
    MXD_P40KF,      /* 40GB mode, 4 lanes, grouped  */
    MXD_P40LF,      /* 40GB mode, 4 lanes, grouped  */
    MXD_R40L,       /* 40GB mode,  4 lanes, grouped */
    MXD_R40C,       /* 40GB mode,  4 lanes, grouped */
    MXD_R40K,       /* 40GB mode,  4 lanes, grouped */

    MXD_P50LN,      /* 50GB mode, 4 lanes, grouped  = 50 */
    MXD_P50CN,      /* 50GB mode, 4 lanes, grouped  */ /* work-in-progress */
    MXD_P50CF,      /* 50GB mode, 4 lanes, grouped  */ /* work-in-progress */
    MXD_P50KN,      /* 50GB mode, 4 lanes, grouped  */ /* work-in-progress */
    MXD_P50KF,      /* 50GB mode, 4 lanes, grouped  */ /* work-in-progress */
    MXD_P50LF,      /* 50GB mode, 4 lanes, grouped  */
    MXD_P50MN,      /* 50GB mode, 2 lanes, grouped  */
    MXD_P50MF,      /* 50GB mode, 2 lanes, grouped  */
    MXD_P50MR,      /* 50GB mode, 2 lanes, grouped  */
    MXD_P50BN,      /* 50GB mode, 2 lanes, grouped  */
    MXD_P50BF,      /* 50GB mode, 2 lanes, grouped  */
    MXD_P50BR,      /* 50GB mode, 2 lanes, grouped  */
    MXD_P50JN,      /* 50GB mode, 2 lanes, grouped  */
    MXD_P50JF,      /* 50GB mode, 2 lanes, grouped  */
    MXD_P50JR,      /* 50GB mode, 2 lanes, grouped  */

    MXD_P100LN,     /* 100GB mode, 4 lanes, grouped = 65 */
    MXD_P100LR,     /* 100GB mode, 4 lanes, grouped */
    MXD_P100CR,     /* 100GB mode, 4 lanes, grouped */
    MXD_P100KR,     /* 100GB mode, 4 lanes, grouped */
    MXD_P100KN,     /* 100GB mode, 4 lanes, grouped */ /* work-in-progress */
    MXD_R100L,      /* 100GB mode, 4 lanes, grouped */
    MXD_R100C,      /* 100GB mode, 4 lanes, grouped */
    MXD_R100K,      /* 100GB mode, 4 lanes, grouped */

    MXD_OP_CONFIG_NUM
} MXD_OP_CONFIG;

/* PCS Speed - do not rearrange the order */
typedef enum
{
   MXD_1GB,
   MXD_2_5GB,
   MXD_5GB,
   MXD_10GB,
   MXD_25GB,
   MXD_40GB,
   MXD_50GB,
   MXD_100GB,
   MXD_SPEED_UNKNOWN
} MXD_SPEED;

typedef enum
{
   MXD_LANE_SPEED_UNKNOWN,
   MXD_LANE_1GB,
   MXD_LANE_2_5GB,
   MXD_LANE_5GB,
   MXD_LANE_10GB,
   MXD_LANE_12_5GB,
   MXD_LANE_25GB,
   MXD_LANE_40GB,
   MXD_LANE_50GB,
   MXD_LANE_100GB
} MXD_LANE_SPEED;

/* do not rearrange the order */
typedef enum
{
   MXD_TRANSPARENT,
   MXD_PCS,
   MXD_RESERVED_PCS_TYPE
} MXD_PCS_TYPE;

typedef enum
{
    MXD_DEV_UNKNOWN = 0,
    MXD_DEV_X5113,
    MXD_DEV_EC053,
    MXD_DEV_EC055,
    MXD_DEV_COUNT
} MXD_DEVICE_ID;

typedef enum
{
    MXD_REV_UNKNOWN = 0,
    MXD_REV_A0 = 0x4,
    MXD_REV_A1 = 0x5,
} MXD_DEVICE_REV;

typedef struct _MXD_MODE_TABLE
{
    OUT MXD_OP_CONFIG  hostOpMode; /* host operational mode   */
    OUT MXD_OP_CONFIG  lineOpMode; /* line operational mode   */
} MXD_MODE_TABLE;

typedef struct _MXD_MODE_CONFIG
{
    OUT MXD_OP_CONFIG  opConfig;         /* operational mode  */
    OUT MXD_PCS_TYPE   pcsType;          /* PCS type          */
    OUT MXD_SPEED      pcsSpeed;         /* PCS Speed         */
    OUT MXD_LANE_SPEED laneSpeed;        /* individual Lane/Serdes speed */
    OUT MXD_U16        fecType;          /* FEC type          */
    OUT MXD_U16        autoNegAdvPause;  /* Advertised Pause Config for Auto Neg, only for AN modes */
    OUT MXD_U16        reserved;         /* reserved for future use */
} MXD_MODE_CONFIG, *PMXD_MODE_CONFIG;

struct _MXD_DEV
{
    OUT MXD_DEVICE_ID   deviceId;      /* type of device and capabilities */
    OUT MXD_DEVICE_REV  chipRevision;  /* revision */
    IN  MXD_U16         mdioPort;      /* MDIO port number */
    OUT MXD_U16         portCount;     /* 1 port count for X5113 */

    OUT MXD_FIXED_OP_MODE opMode[MXD_NUM_LANES];    /* fixed operational mode for both Host and Line */
    OUT MXD_MODE_CONFIG hostConfig[MXD_NUM_LANES];  /* host mode of operation, per lane depending on mode */
    OUT MXD_MODE_CONFIG lineConfig[MXD_NUM_LANES];  /* line mode of operation, per lane depending on mode */

    /* Serdes ID mapped to HOST_MODE_IDX(0) or LINE_MODE_IDX(1); lane offset[0-3] */
    /* usage: serdesID[LINE_MODE_IDX][3] - returns serdesID for 3rd laneOffset on Line side */
    OUT MXD_U16         serdesID[MXD_NUM_INTERFACE][MXD_NUM_LANES];

    OUT MXD_BOOL        devEnabled;    /* whether mxdInitDriver() called successfully */
    INOUT MXD_U32       devInfo;       /* operations, features, status tracking */

    IN FMXD_READ_MDIO   fmxdReadMdio;  /* passed in function for MDIO Read  */
    IN FMXD_WRITE_MDIO  fmxdWriteMdio; /* passed in function for MDIO Write */

    IN MXD_PVOID        hostContext;   /* user specific data for host to pass to the low layer */
#if MXD_ENABLE_SERDES_API
    IN MXD_PVOID        serdesDev;     /* Device structure for Serdes API */
#endif
    IN MXD_BOOL         use20G;        /* Added for CN96XX, use 20G for 25G speeds */
};

#define MXD_NON_GROUPED    0
#define MXD_GROUPED        1

/*****************************************************************************
 devInfo bit info used in device structure for operations, features,
 status tracking, etc...
*****************************************************************************/
#define MXD_LANES_GROUPED (1<<0)  /* 1 if all lanes operation are grouped */
#define MXD_GEARBOX_MODE  (1<<1)  /* Gearbox mode*/
/* NOT USED (1<<2)  */
/* ...              */
/* NOT USED (1<<31) */


/* MXD error status driver level 0 */
#define MXD_STATUS_INVALID_PORT            0x11 /*Invalid port Number*/
#define MXD_STATUS_FAIL_GET_PHY_ADDR       0x12 /*Failed to get phy Address*/
#define MXD_STATUS_FAIL_READ_REG           0x13 /*Failed to read register*/
#define MXD_STATUS_FAIL_WRITE_REG          0x14 /*Failed to write register*/
#define MXD_STATUS_FAIL_GET_PAGE_ADDR      0x15 /*Failed to get page Address  */
#define MXD_STATUS_FAIL_WRITE_PAGE_NUM     0x16 /*Writing Page Number failed */
#define MXD_STATUS_FAIL_RESET              0x17 /*Reset bit is not cleared */
#define MXD_STATUS_NO_DEVICE_FOUND         0x18 /*Cannot find Marvell Device */
#define MXD_STATUS_UNKNOWN_HW_MOD          0x19 /*Unknown HW Mode */
#define MXD_STATUS_ERR_DEV_ID              0x1a /*Error device ID */
#define MXD_STATUS_ERR_VERSION             0x1b /*Error Version */
#define MXD_STATUS_ERR_DEV                 0x1c /*Invalid device stucture */
#define MXD_STATUS_ERR_INIT                0x1d /*Driver init error */
#define MXD_STATUS_FIRMWARE_ERR            0x1e /*Load firmware error */
#define MXD_STATUS_SERDES_INIT_ERR         0x1f /*Fail to init SERDES */

#define MXD_IO_ERROR                       0xFFFF /* Error reading or writing MDIO register */

#define MXD_MAX_MDIO_NUM 31 /* MDIO number 0 to 31  */

/* Chip,Port reset types */
typedef enum {
    MXD_SOFT_RESET = 1,
    MXD_HARD_RESET = 2
} MXD_RESET_TYPE;


#ifdef MXD_SDEBUG
#include "tstSTypes.h"
#endif

#ifdef MXD_PY_DEBUG
#include "tstMxdTypes.h"
#endif

#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* MXD_TYPES_H */
