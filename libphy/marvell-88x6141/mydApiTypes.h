/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains common types and defines across the Marvell
X7120/X6181/X6141 PHYs API driver (MYD).
********************************************************************/
#ifndef MYD_TYPES_H
#define MYD_TYPES_H

#ifdef MYD_MRVL_DEMO_BOARD    /* for demo board environment */
#define DB_TEST_ENVIRONMENT 1 /* set to 0 for host environment */
                              /* set to 1 to build sample code */
                              /* to interface to Marvell DB via SMI board */
#else
#define DB_TEST_ENVIRONMENT 0
#endif

#define MYD_ENABLE_SERDES_API 1 /* Set to 1 to include the SERDES API.
                                   All SERDES source files in the serdes folder
                                   are needed to be in the makefile. Otherwise,
                                   it will generate build errors.
                                   Default = 1  */

#define MYD_FW_WRITE_VERIFIED 1 /* Faster firmware download without write verify.
                                   Set to 1 if problem occurs during firmware download.
                                   Depending on the MDIO access speed, with write 
                                   verify set to 1, the loading to 4 ports may take up to a 
                                   minute. With write verify = 0, it takes a few seconds.
                                   Default = 0  */

#if DB_TEST_ENVIRONMENT
#define MYD_DEBUG                /* comment out all print code/data */
#define MYD_FW_MDIO_BURST_MODE 1 /* system dependent MDIO implementation */
#endif

#ifdef MYD_DEBUG
#define MYD_DBG_BUFSIZE 1000

#if MYD_ENABLE_SERDES_API
#undef MYD_DBG_BUFSIZE
#define MYD_DBG_BUFSIZE 200000  /* Large buffer needed for logging the eye diagram. Eye diagram
                                   size, depending on resolution, can be > several 100s KBytes.
                                   Increase size if needed if mydDbgPrint shows size error.   */
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

typedef char       MYD_8;
typedef short      MYD_16;
typedef long       MYD_32;
typedef int        MYD_INT;
typedef long long  MYD_64;
typedef void       MYD_VOID;
typedef void*      MYD_PVOID;

typedef unsigned char  MYD_U8;
typedef unsigned short MYD_U16;
typedef unsigned long  MYD_U32;
typedef unsigned int   MYD_UINT;
typedef signed short   MYD_S16;

typedef unsigned long long  MYD_U64;

typedef enum {
    MYD_FALSE = 0,
    MYD_TRUE  = 1
} MYD_BOOL;

#define MYD_ENABLE    1
#define MYD_DISABLE   0

#define MYD_OK        0    /* Operation succeeded */
#define MYD_FAIL      1    /* Operation failed    */
#define MYD_PENDING   2    /* Pending  */

#define MYD_CONVERT_BOOL_TO_UINT(boolVar,uintVar) {(boolVar) ? (uintVar=1) : (uintVar=0);}
#define MYD_CONVERT_UINT_TO_BOOL(uintVar,boolVar) {(uintVar) ? (boolVar=MYD_TRUE) : (boolVar=MYD_FALSE);}
#define MYD_GET_BOOL_AS_BIT(boolVar) ((boolVar) ? 1 : 0)
#define MYD_GET_BIT_AS_BOOL(uintVar) ((uintVar) ? MYD_TRUE : MYD_FALSE)
#define MYD_GET_PORT_IDX(mydPDev, mydMdioPort) (mydMdioPort - mydPDev->mdioPort)

typedef MYD_U32 MYD_STATUS;

#define MYD_NUM_LANES            4 /* number of lanes */
#define MYD_MAX_PORTS            4 /* number of lanes */

typedef enum _MYD_INTERFACE {
    MYD_HOST_MODE_IDX = 0,
    MYD_LINE_MODE_IDX = 1,
    MYD_NUM_INTERFACE = 2 /* number of interfaces; Host and Line */
} MYD_INTERFACE;

/* Defines for mydInitDriver() and all API functions which need MYD_DEV */
typedef struct _MYD_DEV MYD_DEV;
typedef MYD_DEV *MYD_DEV_PTR;

typedef MYD_STATUS (*FMYD_READ_MDIO)(
                        MYD_DEV_PTR pDev,
                        MYD_U16 mdioPort,
                        MYD_U16 mmd,
                        MYD_U16 reg,
                        MYD_U16* value);

typedef MYD_STATUS (*FMYD_WRITE_MDIO)(
                        MYD_DEV_PTR pDev,
                        MYD_U16 mdioPort,
                        MYD_U16 mmd,
                        MYD_U16 reg,
                        MYD_U16 value);

/* operational mode configuration for host and line */
/*****************************************************
Type
--------------------------------
P = PCS
R = Retimer

Speed
--------------------------------
1 = 1 Gbps - single lane
2P5 = 2.5 Gbps - single lane
5 = 5 Gbps - single lane
10 = 10 Gbps - single lane
25 = 25 Gbps - 1 lane x 25 Gbps or 2 lanes x 12.5 Gbps or 4 Lanes X 6.25G
40 = 40 Gbps - 4 lanes x 10 Gbps
50 = 50 Gbps - 1 lane x 50 Gbps or 2 lanes x 25 Gbps or 4 lanes x 12.5 Gbps
100 = 100 Gbps - 2 lanes x 50 Gbps or 4 lanes x 25 Gbps
200 = 200 Gbps - 4 lanes x 50 Gbps
400 = 400 Gbps - 8 lanes x 50 Gbps

Training/AN/Coding
-------------------------------
X = BASE-X
S = SGMII System
P = SGMII PHY
L = NRZ BASE-R/X, no Auto-Negotiation
K = NRZ BASE-R/X, Backplane
C = NRZ BASE-R, Twinax
J = same as K except consortium
B = same as C except consortium
M = same as L for Non-Standard 50GBASE-R2, no Auto-Negotiation
U = PAM4 BASE-R, no Auto-Negotiation
Q = PAM4 BASE-R, Twinax/Backplane
Y = same as L for Non-Standard 25GBASE-R2, no Auto-Negotiation
Z = same as C for Non-Standard 25GBASE-R2, Auto-Negotiation
A = same as L for Non-Standard 25GBASE-R4, no Auto-Negotiation
G = same as C for Non-Standard 25GBASE-R4, Auto-Negotiation
H = same as K for Non-Standard 25GBASE-R4, Auto-Negotiation

FEC
--------------------------------
N = No FEC
F = KR-FEC (Firecode)
R = RS-FEC (528, 514)
P = RS-FEC (544, 514)

*****************************************************/
/* NOTE: 
   The MYD_OP_MODE list shows all modes that will be supported 
   in future releases. Not all modes are supported yet.  
   Only modes that are listed as "Supported" is implemented
   and tested.  
   Refers to the datasheet for more information on these modes. 
*/
/* opModeTable needs to match up with MYD_OP_MODE */
typedef enum
{
    MYD_OP_MODE_UNKNOWN,

    MYD_P1X,       /* 1 lane PCS mode */  /* Supported version 1.2 and newer */
    MYD_P1S,       /* 1 lane PCS mode */  /* Supported version 1.2 and newer */
    MYD_P1P,       /* 1 lane PCS mode */  /* Supported version 1.2 and newer */ 
    MYD_P1K,       /* 1 lane PCS mode */  /* Supported version 1.2 and newer */
                   
    MYD_P2P5XN,    /* 1 lane PCS mode */  /* Supported version 1.2 and newer */
    MYD_P2P5XL,    /* 1 lane PCS mode */  /* Supported version 1.2 and newer */
    MYD_P2P5XK,    /* 1 lane PCS mode */  /* Supported version 1.2 and newer */
                   
    MYD_P5L,       /* 1 lane PCS mode */  /* Supported version 1.2 and newer */
    MYD_P5K,       /* 1 lane PCS mode */  /* Supported version 1.2 and newer */
                   
    MYD_P10LN,     /* 1 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P10KN,     /* 1 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P10KF,     /* 1 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P10LF,     /* 1 lane PCS mode */  /* Supported version 1.1 and newer */
                   
    MYD_P25YN,     /* 2 lane PCS mode */  /* Supported version 1.1 and newer */  /* 14 */
    MYD_P25YF,     /* 2 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P25ZN,     /* 2 lane PCS mode */  /* Supported version 1.1 and newer */ /* work-in-progress */
    MYD_P25ZF,     /* 2 lane PCS mode */  /* Supported version 1.1 and newer */ /* work-in-progress */
    MYD_P25AN,     /* 4 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P25GN,     /* 4 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P25GF,     /* 4 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P25HN,     /* 4 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P25HF,     /* 4 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P25LN,     /* 1 lane PCS mode */  /* Supported version 1.0 and newer */  /* 23 */
    MYD_P25LF,     /* 1 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P25LR,     /* 1 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P25CN,     /* 1 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P25CF,     /* 1 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P25CR,     /* 1 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P25BN,     /* 1 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P25BF,     /* 1 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P25BR,     /* 1 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P25JN,     /* 1 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P25JF,     /* 1 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P25JR,     /* 1 lane PCS mode */  /* Supported version 1.1 and newer */

    MYD_P40LN,     /* 4 lane PCS mode */  /* Supported version 1.1 and newer */  /* 35 */
    MYD_P40CN,     /* 4 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P40CF,     /* 4 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P40KN,     /* 4 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P40KF,     /* 4 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P40LF,     /* 4 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P40BN,     /* 2 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P40BF,     /* 2 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P40BR,     /* 2 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P40JN,     /* 2 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P40JF,     /* 2 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P40JR,     /* 2 lane PCS mode */  /* Supported version 1.1 and newer */
                                                             
    MYD_P50LN,     /* 4 lane PCS mode */  /* Supported version 1.1 and newer */  /* 47 */
    MYD_P50CN,     /* 4 lane PCS mode */  /* Supported version 1.1 and newer */ /* work-in-progress */
    MYD_P50CF,     /* 4 lane PCS mode */  /* Supported version 1.1 and newer */ /* work-in-progress */
    MYD_P50KN,     /* 4 lane PCS mode */  /* Supported version 1.1 and newer */ /* work-in-progress */
    MYD_P50KF,     /* 4 lane PCS mode */  /* Supported version 1.1 and newer */ /* work-in-progress */
    MYD_P50LF,     /* 4 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P50MN,     /* 2 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P50MF,     /* 2 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P50MR,     /* 2 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P50BN,     /* 2 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P50BF,     /* 2 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P50BR,     /* 2 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P50JN,     /* 2 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P50JF,     /* 2 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P50JR,     /* 2 lane PCS mode */  /* Supported version 1.1 and newer */
    MYD_P50UP,     /* 1 lane PCS mode */  /* Supported version 1.0 and newer */
    MYD_P50QP,     /* 1 lane PCS mode */  /* Supported version 1.0 and newer */
                                  
    MYD_P100LN,    /* 4 lane PCS mode */  /* Supported version 1.0 and newer */  /* 64 */
    MYD_P100LR,    /* 4 lane PCS mode */  /* Supported version 1.0 and newer */
    MYD_P100CR,    /* 4 lane PCS mode */  /* Supported version 1.0 and newer */
    MYD_P100KR,    /* 4 lane PCS mode */  /* Supported version 1.0 and newer */
    MYD_P100KN,    /* 4 lane PCS mode */  /* Supported version 1.0 and newer */
    MYD_P100UP,    /* 2 lane PCS mode */  /* Supported version 1.0 and newer */
    MYD_P100QP,    /* 2 lane PCS mode */  /* Supported version 1.0 and newer */
                                                      
    MYD_P200UP,    /* 4 lane PCS mode */  /* Supported version 1.0 and newer */  /* 71 */
    MYD_P200QP,    /* 4 lane PCS mode */  /* Supported version 1.0 and newer */

    MYD_PCS_RESERVE_0,
    MYD_PCS_RESERVE_1,
    MYD_PCS_RESERVE_2,
    MYD_PCS_RESERVE_3,
    MYD_PCS_RESERVE_4,
    MYD_PCS_RESERVE_5,
    MYD_PCS_RESERVE_6,
    MYD_PCS_RESERVE_7,
    MYD_PCS_RESERVE_8,
    MYD_PCS_RESERVE_9,
    
    MYD_PCS_RESERVE_10,
    MYD_PCS_RESERVE_11,
    MYD_PCS_RESERVE_12,
    MYD_PCS_RESERVE_13,
    MYD_PCS_RESERVE_14,
    MYD_PCS_RESERVE_15,
    MYD_PCS_RESERVE_16,
    MYD_PCS_RESERVE_17,
    MYD_PCS_RESERVE_18,
    MYD_PCS_RESERVE_19,
    
    MYD_PCS_RESERVE_20,
    MYD_PCS_RESERVE_21,
    MYD_PCS_RESERVE_22,
    MYD_PCS_RESERVE_23,
    MYD_PCS_RESERVE_24,
    MYD_PCS_RESERVE_25,
    MYD_PCS_RESERVE_26,
    MYD_PCS_RESERVE_27,
    MYD_PCS_RESERVE_28,
    MYD_PCS_RESERVE_29,
                 /* Repeater mode starts here */
    MYD_R1,      /* 1 lane Repeater mode */  /* Supported version 1.2 and newer */ /* 103 */
                 
    MYD_R2P5,    /* 1 lane Repeater mode */  /* Supported version 1.2 and newer */
                 
    MYD_R5L,     /* 1 lane Repeater mode */  /* Supported version 1.2 and newer */
                 
    MYD_R10L,    /* 1 lane Repeater mode */  /* Supported version 1.2 and newer */
    MYD_R10K,    /* 1 lane Repeater mode */  /* Supported version 1.2 and newer */ /* Line side only */
                 
    MYD_R25L,    /* 1 lane Repeater mode */  /* Supported version 1.0 and newer */
    MYD_R25C,    /* 1 lane Repeater mode */  /* Supported version 1.1 and newer */
                 
    MYD_R40L,    /* 4 lane Repeater mode */  /* Supported version 1.1 and newer */
    MYD_R40C,    /* 4 lane Repeater mode */  /* Supported version 1.1 and newer */
    MYD_R40K,    /* 4 lane Repeater mode */  /* Supported version 1.1 and newer */
                 
    MYD_R50L,    /* 2 lane Repeater mode */  /* Supported version 1.1 and newer */
    MYD_R50C,    /* 2 lane Repeater mode */  /* Supported version 1.1 and newer */
    MYD_R50U,    /* 1 lane Repeater mode */  /* Supported version 1.0 and newer */ 
    MYD_R50Q,    /* 1 lane Repeater mode */  /* Supported version 1.0 and newer */ /* if line is MYD_R50Q, host must be MYD_R50U */
                 
    MYD_R100L,   /* 4 lane Repeater mode */  /* Supported version 1.0 and newer */ /* 117 */
    MYD_R100C,   /* 4 lane Repeater mode */  /* Supported version 1.1 and newer */
    MYD_R100K,   /* 4 lane Repeater mode */  /* Supported version 1.1 and newer */
    MYD_R100U,   /* 2 lane Repeater mode */  /* Supported version 1.1 and newer */
    MYD_R100Q,   /* 2 lane Repeater mode */  /* Supported version 1.1 and newer */
                 
    MYD_R200L,   /* 8 lane Repeater mode */  /* Supported version 1.0 and newer */
    MYD_R200K,   /* 8 lane Repeater mode */  /* Supported version 1.1 and newer */ /* work-in-progress */
    MYD_R200U,   /* 4 lane Repeater mode */  /* Supported version 1.0 and newer */
    MYD_R200Q,   /* 4 lane Repeater mode */  /* Supported version 1.1 and newer */
                 
    MYD_R400U,   /* 8 lane Repeater mode */  /* Supported version 1.0 and newer */
    MYD_R400Q,   /* 8 lane Repeater mode */
                 
    MYD_R50LP,   /* 2 lane Repeater mode */
    MYD_R50CP,   /* 2 lane Repeater mode */
                 
    MYD_R100LP,  /* 4 lane Repeater mode */
    MYD_R100CP,  /* 4 lane Repeater mode */

    MYD_RXLA,
    MYD_RXLB,

    MYD_OP_MODE_COUNT
} MYD_OP_MODE;

/* Fields used in opModeTable */
typedef enum  
{                     
   MYD_OP_TABLE_OP_MODE, 
   MYD_OP_TABLE_SIGNAL, 
   MYD_OP_TABLE_LANE_COUNT, 
   MYD_OP_TABLE_MODE_MOD, 
   MYD_OP_TABLE_FEC, 
   MYD_OP_TABLE_MODE_TYPE, 
   MYD_OP_TABLE_AN_TRAIN, 
   MYD_OP_TABLE_SPEED, 
   MYD_OP_TABLE_REG, 
   MYD_OP_TABLE_COUNT
} MYD_OP_TABLE;

/* Mode Reg 0xF00x.3:0 Lane Speed */
typedef enum  
{                     
   MYD_1GB   = 0,     /* 0000 = 1G   */ 
   MYD_2P5GB = 1,     /* 0001 = 2.5G */
   MYD_5GB   = 2,     /* 0010 = 5G   */
   MYD_10GB  = 3,     /* 0011 = 10G  */
   MYD_25GB  = 4,     /* 0100 = 25G  */
   MYD_40GB  = 5,     /* 0101 = 40G  */
   MYD_50GB  = 6,     /* 0110 = 50G  */
   MYD_100GB = 7,     /* 0111 = 100G */
   MYD_200GB = 8,     /* 1000 = 200G */
   MYD_400GB = 9,     /* 1001 = 400G */
   MYD_SPEED_UNKNOWN
} MYD_SPEED;

/* Mode signaling type */
#define MYD_SIGNAL_NRZ   1
#define MYD_SIGNAL_PAM4  2

/* Lane count used for the operational mode */
#define MYD_1_LANE_MODE  1
#define MYD_2_LANE_MODE  2
#define MYD_4_LANE_MODE  4
#define MYD_8_LANE_MODE  8

/* Mode Reg 0xF00x.4 AP AutoNeg & KR Training */
#define MYD_AN_TRAIN_OFF  0x0000
#define MYD_AN_TRAIN_ON   0x0010

/* Mode Reg 0xF00x.5 Data Termination */
#define MYD_TRANSPARENT  0x0000
#define MYD_PCS          0x0020

/* Mode Reg 0xF00x.7:6 Forward Error Correction */
#define MYD_FEC_NONE    0x0000
#define MYD_FEC_KR      0x0040
#define MYD_FEC_RS_528  0x0080
#define MYD_FEC_RS_544  0x00C0

/* Mode Reg 0xF00x.11:8 Mode Modifier */
#define MYD_MOD_NONE             0x0000
#define MYD_MOD_1000BASE_X       0x0000
#define MYD_MOD_1000BASE_KX      0x0100
#define MYD_MOD_SGMII_PHY        0x0200
#define MYD_MOD_SGMII_SYS        0x0300
#define MYD_MOD_2P5GBX_CL36      0x0000
#define MYD_MOD_2P5GBX_CL127     0x0100
#define MYD_MOD_25GR2            0x0C00
#define MYD_MOD_25GR2_MRVL       0x0D00
#define MYD_MOD_25GR4_MRVL       0x0800
#define MYD_MOD_25GBASE_CR_IEEE  0x0000
#define MYD_MOD_25GBASE_KR_IEEE  0x0100
#define MYD_MOD_25GBASE_CR_CONS  0x0200
#define MYD_MOD_25GBASE_KR_CONS  0x0300
#define MYD_MOD_40GR2_CONS       0x0400
#define MYD_MOD_40GBASE_CR4      0x0000
#define MYD_MOD_40GBASE_KR4      0x0100
#define MYD_MOD_50GR2_CONS_MRVL  0x0200
#define MYD_MOD_50GR4_MRVL       0x0000
#define MYD_MOD_100GBASE_CR4     0x0000
#define MYD_MOD_100GBASE_KR4     0x0100
#define MYD_MOD_R40G_CR4         0x0200
#define MYD_MOD_R40G_KR4         0x0300
#define MYD_MOD_100GR4           0x0000
#define MYD_MOD_100GR2           0x0800

typedef enum
{
    MYD_DEV_X6181   = 0,
    MYD_DEV_X7120   = 1,
    MYD_DEV_X6141   = 2,
    MYD_DEV_UNKNOWN = 0xFF
} MYD_DEVICE_ID;

typedef enum
{
    MYD_REV_A0 = 0x0,
    MYD_REV_A1 = 0x1,
    MYD_REV_UNKNOWN = 0xFF
} MYD_DEVICE_REV;

#define MYD_X7120_PORT_COUNT  4
#define MYD_X6181_PORT_COUNT  2
#define MYD_X6141_PORT_COUNT  1

typedef struct _MYD_MODE_CONFIG
{
    MYD_OP_MODE    opMode;         /* mode operational */
    MYD_SPEED      speed;          /* mode operational speed */
    MYD_U16        opModeType;     /* PCS, Repeater/Retimer */
    MYD_U16        signalType;     /* NRZ or PAM-4 signal */
    MYD_U16        typeFEC;        /* CL-74/91/119/134/, Consortium */
    MYD_U16        autoNeg;        /* auto neg feature */
    MYD_U16        modeModifier;   /* internal usage */
    MYD_U16        laneCount;      /* number of lane used for the mode */
    MYD_U16        reserved0;      /* reserved field */
    MYD_U16        reserved1;      /* reserved field */
    MYD_U16        reserved2;      /* reserved field */
} MYD_MODE_CONFIG, *PMYD_MODE_CONFIG;

struct _MYD_DEV
{
    OUT MYD_DEVICE_ID   deviceId;      /* type of device and capabilities */
    OUT MYD_DEVICE_REV  chipRevision;  /* revision */
    IN  MYD_U16         mdioPort;      /* 1st port MDIO number */
    OUT MYD_U16         portCount;     /* 1,2,4 ports count for X6141, X6181 and X7120 respectively */

    OUT MYD_MODE_CONFIG hostConfig[MYD_MAX_PORTS][MYD_NUM_LANES]; /* host mode of operation, per lane depending on mode */
    OUT MYD_MODE_CONFIG lineConfig[MYD_MAX_PORTS][MYD_NUM_LANES]; /* line mode of operation, per lane depending on mode */

    OUT MYD_BOOL        devEnabled;    /* whether mydInitDriver() called successfully */
    OUT MYD_BOOL        devEEPROM;     /* set MYD_TRUE if EEPROM image loaded; default to MYD_FALSE */
    INOUT MYD_U32       devInfo[MYD_MAX_PORTS]; /* operations, features, status tracking */

    IN FMYD_READ_MDIO   fmydReadMdio;  /* passed in function for MDIO Read  */
    IN FMYD_WRITE_MDIO  fmydWriteMdio; /* passed in function for MDIO Write */

    IN MYD_PVOID        hostContext; /* user specific data for host to pass to the low layer */
#if MYD_ENABLE_SERDES_API
    IN MYD_PVOID        serdesDev[MYD_MAX_PORTS]; /* Device structure for Serdes API */
#endif
};

#define MYD_NON_GROUPED    0
#define MYD_GROUPED        1

/*****************************************************************************
 devInfo bit info used in device structure for operations, features,
 status tracking, etc...
*****************************************************************************/
#define MYD_LANES_GROUPED (1<<0)  /* 1 if all lanes operation are grouped */
#define MYD_GEARBOX_MODE  (1<<1)  /* Gearbox mode */
/* NOT USED (1<<2)  */
/* ...              */
/* NOT USED (1<<31) */

/* MYD error status driver level 0 */
#define MYD_STATUS_INVALID_PORT            0x11 /*Invalid port Number*/
#define MYD_STATUS_FAIL_GET_PHY_ADDR       0x12 /*Failed to get phy Address*/
#define MYD_STATUS_FAIL_READ_REG           0x13 /*Failed to read register*/
#define MYD_STATUS_FAIL_WRITE_REG          0x14 /*Failed to write register*/
#define MYD_STATUS_FAIL_GET_PAGE_ADDR      0x15 /*Failed to get page Address  */
#define MYD_STATUS_FAIL_WRITE_PAGE_NUM     0x16 /*Writing Page Number failed */
#define MYD_STATUS_FAIL_RESET              0x17 /*Reset bit is not cleared */
#define MYD_STATUS_NO_DEVICE_FOUND         0x18 /*Cannot find Marvell Device */
#define MYD_STATUS_UNKNOWN_HW_MOD          0x19 /*Unknown HW Mode */
#define MYD_STATUS_ERR_DEV_ID              0x1a /*Error device ID */
#define MYD_STATUS_ERR_VERSION             0x1b /*Error Version */
#define MYD_STATUS_ERR_DEV                 0x1c /*Invalid device stucture */
#define MYD_STATUS_ERR_INIT                0x1d /*Driver init error */
#define MYD_STATUS_FIRMWARE_ERR            0x1e /*Load firmware error */
#define MYD_STATUS_SERDES_INIT_ERR         0x1f /*Fail to init SERDES */

#define MYD_IO_ERROR                       0xFFFF /* Error reading or writing MDIO register */

#define MYD_MAX_MDIO_NUM 31 /* MDIO number 0 to 31  */
#define MYD_MAX_SERDES_LANE 32

/* Chip,Port reset types */
typedef enum {
    MYD_SOFT_RESET = 1,
    MYD_HARD_RESET = 2
} MYD_RESET_TYPE;


#ifdef MYD_PY_DEBUG
#include "tstMydTypes.h"
#endif

#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* MYD_TYPES_H */
