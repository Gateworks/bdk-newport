/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains common types and defines across the Marvell
T-unit (copper) API driver (MTD) for the Marvell 88X32X0, 88X33X0, 
88E20X0 and 88E21X0 ethernet PHYs.
********************************************************************/
#ifndef MTD_TYPES_H
#define MTD_TYPES_H

#ifdef MTD_MRVL_DEMO_BOARD    /* for demo board environment */
#define DB_TEST_ENVIRONMENT 1 /* set to 0 for host environment */
                              /* set to 1 to build sample code */
                              /* to interface to Marvell DB via SMI board */
#else
#define DB_TEST_ENVIRONMENT 0
#endif

#define MTD_CLAUSE_22_MDIO  0 /* set to 1 to use Clause 22 MDIO support instead of Clause 45 */
                              /* NOTE: Only 88X33X0/E20X0/E21X0 family supports Clause 22 MDIO */

#if DB_TEST_ENVIRONMENT
#include "stdio.h"
#include "stdarg.h"
#include "stdlib.h"
#define  MTD_DEBUG /* comment out to remove all print code/data */
#define  MTD_USE_MDIO_BLOCK_WRITE 1 /* download will do a block transfer instead of one at-a-time XMDIO write if this is 1 */
#else
#define  MTD_USE_MDIO_BLOCK_WRITE 0 /* API code always does each XMDIO write */
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

typedef void      MTD_VOID;
typedef char      MTD_8;
typedef short     MTD_16; 
typedef long      MTD_32;
typedef long long MTD_64;

typedef unsigned char  MTD_U8;
typedef signed char    MTD_S8;
typedef unsigned short MTD_U16;
typedef unsigned long  MTD_U32;
typedef unsigned int   MTD_UINT; 
typedef int            MTD_INT;
typedef signed short   MTD_S16;
typedef void*          MTD_PVOID;

typedef unsigned long long  MTD_U64;

typedef enum {
    MTD_FALSE = 0,
    MTD_TRUE  = 1
} MTD_BOOL;

#define MTD_CONVERT_BOOL_TO_UINT(boolVar,uintVar) {(boolVar) ? (uintVar=1) : (uintVar=0);}
#define MTD_CONVERT_UINT_TO_BOOL(uintVar,boolVar) {(uintVar) ? (boolVar=MTD_TRUE) : (boolVar=MTD_FALSE);}
#define MTD_GET_BOOL_AS_BIT(boolVar) ((boolVar) ? 1 : 0)
#define MTD_GET_BIT_AS_BOOL(uintVar) ((uintVar) ? MTD_TRUE : MTD_FALSE)

typedef void     (*MTD_VOIDFUNCPTR) (void); /* ptr to function returning void */
typedef MTD_U32  (*MTD_INTFUNCPTR)  (void); /* ptr to function returning int  */

typedef MTD_U32 MTD_STATUS;

/* Defines for semaphore support */
typedef MTD_U32 MTD_SEM;

typedef enum
{
    MTD_SEM_EMPTY,
    MTD_SEM_FULL
} MTD_SEM_BEGIN_STATE;

typedef MTD_SEM (*FMTD_SEM_CREATE)(MTD_SEM_BEGIN_STATE state);
typedef MTD_STATUS (*FMTD_SEM_DELETE)(MTD_SEM semId);
typedef MTD_STATUS (*FMTD_SEM_TAKE)(MTD_SEM semId, MTD_U32 timOut);
typedef MTD_STATUS (*FMTD_SEM_GIVE)(MTD_SEM semId);

/* Defines for mtdLoadDriver() mtdUnloadDriver() and all API functions which need MTD_DEV */
typedef struct _MTD_DEV MTD_DEV;
typedef MTD_DEV *MTD_DEV_PTR;

#if (MTD_CLAUSE_22_MDIO == 0)

/* normal case is Clause 45 MDIO */
typedef MTD_STATUS (*FMTD_READ_MDIO)(
                        MTD_DEV*   dev,
                        MTD_U16 port, 
                        MTD_U16 mmd, 
                        MTD_U16 reg, 
                        MTD_U16* value);
typedef MTD_STATUS (*FMTD_WRITE_MDIO)(
                        MTD_DEV*   dev,
                        MTD_U16 port, 
                        MTD_U16 mmd, 
                        MTD_U16 reg, 
                        MTD_U16 value);
#else

/* Clause 22 MDIO has a different format */
typedef MTD_STATUS (*FMTD_READ_MDIO)(
                        MTD_DEV*   dev,
                        MTD_U16 port, 
                        MTD_U16 reg, 
                        MTD_U16* value);
typedef MTD_STATUS (*FMTD_WRITE_MDIO)(
                        MTD_DEV*   dev,
                        MTD_U16 port, 
                        MTD_U16 reg, 
                        MTD_U16 value);

#endif

#if 0
typedef enum
{
    MTD_REV_UNK = 0,    /* unknown phy type */
    MTD_REV_QZ2 = 1,    /* quad-port chip Z2 */
    MTD_REV_QA0 = 2,    /* quad-port A0 */
    MTD_REV_QA1 = 3,    /* quad-port A1 */
    MTD_REV_DZ2 = 4,    /* dual-port Z2 */
    MTD_REV_DA0 = 5     /* dual-port A0 */
                        /* NOTE: releases prior to 0.1.3.0 firmware */
                        /* use following definitions: */
                        /* MTD_REV_DZ1 (4) */
                        /* MTD_REV_DZ2 (5) */

} MTD_DEVICE_ID; 
#endif


/* MTD_DEVICE_ID format:  */
/* Bits 15:13 reserved */
/* Bit 12: 1-> E20X0 device with max speed of 5G and no fiber interface */
/* Bit 11: 1-> Macsec Capable (Macsec/PTP module included */
/* Bit  10: 1-> Copper Capable (T unit interface included) */
/* Bits 9:4 0x18 -> X32X0 base, 0x1A X33X0 base, 0x1B E21X0 base */
/* Bits 3:0 revision/number of ports indication, see list */
/* Following defines are for building MTD_DEVICE_ID */
#define MTD_E20X0_DEVICE (1<<12)   /* whether this is an E20X0 device group */
#define MTD_MACSEC_CAPABLE (1<<11) /* whether the device has a Macsec/PTP module */
#define MTD_COPPER_CAPABLE (1<<10) /* whether the device has a copper (T unit) module */
#define MTD_X32X0_BASE (0x18<<4)   /* whether the device uses X32X0 firmware base */
#define MTD_X33X0_BASE (0x1A<<4)   /* whether the device uses X33X0 firmware base */
#define MTD_E21X0_BASE (0x1B<<4)   /* whether the device uses E21X0 firmware base, this is a max 5G part, copper only, no Macsec, basic PTP */

/* Following macros are to test MTD_DEVICE_ID for various features */
#define MTD_IS_E20X0_DEVICE(mTdrevId) ((MTD_BOOL)(mTdrevId & MTD_E20X0_DEVICE))
#define MTD_IS_MACSEC_CAPABLE(mTdrevId) ((MTD_BOOL)(mTdrevId & MTD_MACSEC_CAPABLE))
#define MTD_IS_COPPER_CAPABLE(mTdrevId) ((MTD_BOOL)(mTdrevId & MTD_COPPER_CAPABLE))
#define MTD_IS_X32X0_BASE(mTdrevId) ((MTD_BOOL)((mTdrevId & (0x3F<<4)) == MTD_X32X0_BASE))
#define MTD_IS_X33X0_BASE(mTdrevId) ((MTD_BOOL)((mTdrevId & (0x3F<<4)) == MTD_X33X0_BASE))
#define MTD_IS_E21X0_BASE(mTdrevId) ((MTD_BOOL)((mTdrevId & (0x3F<<4)) == MTD_E21X0_BASE))
#define MTD_HAS_X_UNIT(mTddevPtr)   !(MTD_IS_E21X0_BASE(mTddevPtr->deviceId) || MTD_IS_E20X0_DEVICE(mTddevPtr->deviceId))

#define MTD_X33X0BASE_SINGLE_PORTA0 0xA
#define MTD_X33X0BASE_DUAL_PORTA0   0x6
#define MTD_X33X0BASE_QUAD_PORTA0   0x2
#define MTD_X33X0BASE_SINGLE_PORTA1 0xB
#define MTD_X33X0BASE_DUAL_PORTA1   0x7
#define MTD_X33X0BASE_QUAD_PORTA1   0x3

#define MTD_E21X0BASE_SINGLE_PORTZ1 0x8 /* Base for single port */
#define MTD_E21X0BASE_SINGLE_PORTA0 0x9 
#define MTD_E21X0BASE_QUAD_PORTA0   0x4 /* Base for quad, currently not available */
#define MTD_E21X0BASE_OCTAL_PORTA0  0x0 /* base for octal */
#define MTD_E21X0BASE_OCTAL_PORTA1  0x1

/* WARNING: If you add/modify this list, you must also modify mtdIsPhyRevisionValid() */
typedef enum
{
    MTD_REV_UNKNOWN = 0,
    MTD_REV_3240P_Z2 = (MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X32X0_BASE | 0x1),
    MTD_REV_3240P_A0 = (MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X32X0_BASE | 0x2),
    MTD_REV_3240P_A1 = (MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X32X0_BASE | 0x3),
    MTD_REV_3220P_Z2 = (MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X32X0_BASE | 0x4),
    MTD_REV_3220P_A0 = (MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X32X0_BASE | 0x5),
    MTD_REV_3240_Z2 = (MTD_COPPER_CAPABLE | MTD_X32X0_BASE | 0x1),
    MTD_REV_3240_A0 = (MTD_COPPER_CAPABLE | MTD_X32X0_BASE | 0x2),
    MTD_REV_3240_A1 = (MTD_COPPER_CAPABLE | MTD_X32X0_BASE | 0x3),
    MTD_REV_3220_Z2 = (MTD_COPPER_CAPABLE | MTD_X32X0_BASE | 0x4),
    MTD_REV_3220_A0 = (MTD_COPPER_CAPABLE | MTD_X32X0_BASE | 0x5),

    MTD_REV_3310P_Z1 = (MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | 0x8), /* 88X33X0 Z1 not supported starting with version 1.2 of API */ 
    MTD_REV_3320P_Z1 = (MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | 0x4),
    MTD_REV_3340P_Z1 = (MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | 0x0),
    MTD_REV_3310_Z1 = (MTD_COPPER_CAPABLE | MTD_X33X0_BASE | 0x8),
    MTD_REV_3320_Z1 = (MTD_COPPER_CAPABLE | MTD_X33X0_BASE | 0x4),
    MTD_REV_3340_Z1 = (MTD_COPPER_CAPABLE | MTD_X33X0_BASE | 0x0),

    MTD_REV_3310P_Z2 = (MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | 0x9),  /* 88X33X0 Z2 not supported starting with version 1.2 of API */
    MTD_REV_3320P_Z2 = (MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | 0x5),
    MTD_REV_3340P_Z2 = (MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | 0x1),
    MTD_REV_3310_Z2 = (MTD_COPPER_CAPABLE | MTD_X33X0_BASE | 0x9),
    MTD_REV_3320_Z2 = (MTD_COPPER_CAPABLE | MTD_X33X0_BASE | 0x5),
    MTD_REV_3340_Z2 = (MTD_COPPER_CAPABLE | MTD_X33X0_BASE | 0x1),

    MTD_REV_E2010P_Z2 = (MTD_E20X0_DEVICE | MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | 0x9), /* E20X0 Z2 not supported starting with version 1.2 of API */
    MTD_REV_E2020P_Z2 = (MTD_E20X0_DEVICE | MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | 0x5),
    MTD_REV_E2040P_Z2 = (MTD_E20X0_DEVICE | MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | 0x1),
    MTD_REV_E2010_Z2 = (MTD_E20X0_DEVICE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | 0x9),
    MTD_REV_E2020_Z2 = (MTD_E20X0_DEVICE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | 0x5),
    MTD_REV_E2040_Z2 = (MTD_E20X0_DEVICE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | 0x1),


    MTD_REV_3310P_A0 = (MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_SINGLE_PORTA0),
    MTD_REV_3320P_A0 = (MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_DUAL_PORTA0),
    MTD_REV_3340P_A0 = (MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_QUAD_PORTA0),
    MTD_REV_3310_A0 = (MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_SINGLE_PORTA0),
    MTD_REV_3320_A0 = (MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_DUAL_PORTA0),
    MTD_REV_3340_A0 = (MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_QUAD_PORTA0),

    MTD_REV_E2010P_A0 = (MTD_E20X0_DEVICE | MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_SINGLE_PORTA0),
    MTD_REV_E2020P_A0 = (MTD_E20X0_DEVICE | MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_DUAL_PORTA0),
    MTD_REV_E2040P_A0 = (MTD_E20X0_DEVICE | MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_QUAD_PORTA0),
    MTD_REV_E2010_A0 = (MTD_E20X0_DEVICE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_SINGLE_PORTA0),
    MTD_REV_E2020_A0 = (MTD_E20X0_DEVICE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_DUAL_PORTA0),
    MTD_REV_E2040_A0 = (MTD_E20X0_DEVICE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_QUAD_PORTA0),

    MTD_REV_2340P_A0 = (MTD_MACSEC_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_QUAD_PORTA0),
    MTD_REV_2340_A0 = (MTD_X33X0_BASE | MTD_X33X0BASE_QUAD_PORTA0), 

    MTD_REV_3310P_A1 = (MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_SINGLE_PORTA1),
    MTD_REV_3320P_A1 = (MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_DUAL_PORTA1),
    MTD_REV_3340P_A1 = (MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_QUAD_PORTA1),
    MTD_REV_3310_A1 = (MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_SINGLE_PORTA1),
    MTD_REV_3320_A1 = (MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_DUAL_PORTA1),
    MTD_REV_3340_A1 = (MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_QUAD_PORTA1),

    MTD_REV_E2010P_A1 = (MTD_E20X0_DEVICE | MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_SINGLE_PORTA1),
    MTD_REV_E2020P_A1 = (MTD_E20X0_DEVICE | MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_DUAL_PORTA1),
    MTD_REV_E2040P_A1 = (MTD_E20X0_DEVICE | MTD_MACSEC_CAPABLE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_QUAD_PORTA1),
    MTD_REV_E2010_A1 = (MTD_E20X0_DEVICE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_SINGLE_PORTA1),
    MTD_REV_E2020_A1 = (MTD_E20X0_DEVICE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_DUAL_PORTA1),
    MTD_REV_E2040_A1 = (MTD_E20X0_DEVICE | MTD_COPPER_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_QUAD_PORTA1),

    MTD_REV_2340P_A1 = (MTD_MACSEC_CAPABLE | MTD_X33X0_BASE | MTD_X33X0BASE_QUAD_PORTA1),
    MTD_REV_2340_A1 = (MTD_X33X0_BASE | MTD_X33X0BASE_QUAD_PORTA1),     

    MTD_REV_2340P_A1_NA = (MTD_MACSEC_CAPABLE | MTD_X32X0_BASE | 0x3),  /* 2340 is based on 33X0 device, there is no such device as this one */
    MTD_REV_2320P_A0 = (MTD_MACSEC_CAPABLE | MTD_X32X0_BASE | 0x5),     /* 2320 is based on 32X0 device */
    MTD_REV_2340_A1_NA = (MTD_X32X0_BASE | 0x3),                        /* 2340 is based on 33X0 device, there is no such device as this one */
    MTD_REV_2320_A0 = (MTD_X32X0_BASE | 0x5),                           /* 2320 is based on 32X0 device */

    MTD_REV_E2110_Z1 = (MTD_E21X0_BASE | MTD_COPPER_CAPABLE | MTD_E21X0BASE_SINGLE_PORTZ1),
    MTD_REV_E2110_A0 = (MTD_E21X0_BASE | MTD_COPPER_CAPABLE | MTD_E21X0BASE_SINGLE_PORTA0),
    
    MTD_REV_E2140_A0 = (MTD_E21X0_BASE | MTD_COPPER_CAPABLE | MTD_E21X0BASE_QUAD_PORTA0), /* part not currently available */
    
    MTD_REV_E2180_A0 = (MTD_E21X0_BASE | MTD_COPPER_CAPABLE | MTD_E21X0BASE_OCTAL_PORTA0),
    MTD_REV_E2180_A1 = (MTD_E21X0_BASE | MTD_COPPER_CAPABLE | MTD_E21X0BASE_OCTAL_PORTA1)
    
} MTD_DEVICE_ID;

typedef enum
{
    MTD_MSEC_REV_Z0A,
    MTD_MSEC_REV_Y0A,
    MTD_MSEC_REV_A0B,
    MTD_MSEC_REV_FPGA,
    MTD_MSEC_REV_UNKNOWN  = -1
} MTD_MSEC_REV;

/* compatible for USB test */
typedef struct  _MTD_MSEC_CTRL {
  MTD_32 dev_num;      /* indicates the device number (0 if only one) when multiple devices are present on SVB.*/
  MTD_32 port_num;     /* Indicates which port (0 to 4) is requesting CPU */
  MTD_U16 prev_addr;   /* < Prev write address */
  MTD_U16 prev_dataL;  /* < Prev dataL value */
  MTD_MSEC_REV msec_rev;  /* revision */
} MTD_MSEC_CTRL;

struct _MTD_DEV
{
    MTD_DEVICE_ID   deviceId;      /* type of device and capabilities */
    MTD_BOOL        devEnabled;    /* whether mtdLoadDriver() called successfully */
    MTD_U8          numPorts;      /* number of ports per device */
    MTD_U8          thisPort;      /* relative port number on this device starting with 0 (not MDIO address) */
    MTD_SEM         multiAddrSem;

    FMTD_READ_MDIO  fmtdReadMdio;  
    FMTD_WRITE_MDIO fmtdWriteMdio; 

    FMTD_SEM_CREATE semCreate;  /* create semapore */
    FMTD_SEM_DELETE semDelete;  /* delete the semapore */
    FMTD_SEM_TAKE   semTake;    /* try to get a semapore */
    FMTD_SEM_GIVE   semGive;    /* return semaphore */

    MTD_U8          macsecIndirectAccess; /* if MTD_TRUE use internal processor to access Macsec */ 
    MTD_MSEC_CTRL   msec_ctrl;  /* structure use for internal verification */

    MTD_PVOID       appData; /* application specific data, anything the host wants to pass to the low layer */
};




#define MTD_OK       0    /* Operation succeeded */
#define MTD_FAIL     1    /* Operation failed    */
#define MTD_PENDING  2    /* Pending  */

#define MTD_ENABLE   1    /* feature enable */
#define MTD_DISABLE  0    /* feature disable */


/* bit definition */
#define MTD_BIT_0       0x0001
#define MTD_BIT_1       0x0002
#define MTD_BIT_2       0x0004
#define MTD_BIT_3       0x0008
#define MTD_BIT_4       0x0010
#define MTD_BIT_5       0x0020
#define MTD_BIT_6       0x0040
#define MTD_BIT_7       0x0080
#define MTD_BIT_8       0x0100
#define MTD_BIT_9       0x0200
#define MTD_BIT_10      0x0400
#define MTD_BIT_11      0x0800
#define MTD_BIT_12      0x1000
#define MTD_BIT_13      0x2000
#define MTD_BIT_14      0x4000
#define MTD_BIT_15      0x8000



#ifdef MTD_DEBUG
typedef enum 
{
    MTD_DBG_OFF_LVL,
    MTD_DBG_ERR_LVL,
    MTD_DBG_INF_LVL,
    MTD_DBG_ALL_LVL
} MTD_DBG_LEVEL;

//extern void mtdFuncDbgPrint(char* format, ...);
void mtdDbgPrint(FILE *stream, MTD_DBG_LEVEL debug_level, char* format, ...);

#define MTD_DBG_ERROR(...)       mtdDbgPrint(stderr, MTD_DBG_ERR_LVL, __VA_ARGS__) /* macro for error messages */
#define MTD_DBG_INFO(...)        mtdDbgPrint(stdout, MTD_DBG_ALL_LVL, __VA_ARGS__) /* macro for informational messages */
#define MTD_DBG_CRITIC_INFO(...) mtdDbgPrint(stdout, MTD_DBG_INF_LVL, __VA_ARGS__) /* macro for informational messages */

#else /* MTD_DEBUG not defined */

#define MTD_DBG_ERROR(...)
#define MTD_DBG_INFO(...)
#define MTD_DBG_CRITIC_INFO(...)

#endif

#ifdef MTD_SDEBUG
#include "..\mtdMatLab\tstSTypes.h"
#endif

#ifdef MTD_PY_DEBUG
#include "..\mtdPython\mtdPythonSrc\tstSTypes.h"
#endif

#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* MTD_TYPES_H */
