/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************************
* mtdMsecPtpApiDefs.h
*
* DESCRIPTION:
*       API definitions for Marvell Phy Devices
*
* DEPENDENCIES:
*
* FILE REVISION NUMBER:
*
*******************************************************************************/
#ifndef __MTDMsecPtpApiDefs_h
#define __MTDMsecPtpApiDefs_h

#if C_LINKAGE
#ifdef __cplusplus
extern "C" {
#endif
#endif

#if defined(LINUX)
 #ifdef __KERNEL__
  #include "linux/kernel.h" 
 #endif
#elif defined(WIN32)
#include "stdio.h"
#endif

/* set debug log enable */
#define MTD_UNUSED_PARAM(_a)        (_a)=(_a)

typedef enum
{
    MTD_PATH_TYPE_LINE        = 0,
    MTD_PATH_TYPE_HOST        = 1,
} MTD_PATH_TYPE;

typedef enum
{
    MTD_MACSEC_BYPASS_RESERVED        = 0,
    MTD_MACSEC_BYPASS_RESET           = 1,
    MTD_MACSEC_BYPASS_SLEEP           = 2,
    MTD_MACSEC_BYPASS_ACTIVE           = 3,
} MTD_MACSEC_BYPASS_MODE;

#define MTD_RUN_ST_MASK            0x0000000F

#define MTD_ERR_ST_DRV_0_BASE    0x00000000
#define MTD_ERR_ST_DRV_1_BASE    0x00000100
#define MTD_ERR_ST_API_0_BASE    0x00010000
#define MTD_ERR_ST_API_1_BASE    0x01000000


#define MTD_ERR_ST_DRV_0_MASK    0x000000FF
#define MTD_ERR_ST_DRV_1_MASK    0x0000FF00
#define MTD_ERR_ST_API_0_MASK    0x00FF0000
#define MTD_ERR_ST_API_1_MASK    0xFF000000

/* MTD error status driver level 0 */
#define MTD_DRV_INVALID_PORT            0x11    /*Invalid port Number*/
#define MTD_DRV_FAIL_GET_PHY_ADDR        0x12    /*Failed to get phy Address*/
#define MTD_DRV_FAIL_READ_REG            0x13    /*Failed to read register*/
#define MTD_DRV_FAIL_WRITE_REG            0x14    /*Failed to write register*/
#define MTD_DRV_FAIL_GET_PAGE_ADDR        0x15    /*Failed to get page Address  */
#define MTD_DRV_FAIL_WRITE_PAGE_NUM        0x16    /*Writing Page Number failed */
#define MTD_DRV_FAIL_RESET                0x17    /*Reset bit is not cleared */
#define MTD_DRV_NO_DEVICE_FOUND            0x18    /*Cannot find Marvell Device */
#define MTD_DRV_UNKNOWN_HW_MOD            0x19    /*Unknown HW Mode */
#define MTD_DRV_ERROR_DEV_ID            0x1a    /*Error device ID */
#define MTD_DRV_ERROR_VERSION            0x1b    /*Error Version */

/* MTD error status driver level 1 */

#define MTD_DRV_FAIL_ACCESS_PAGE_REG    0x1<<8    /*Accessing Page Register failed */
#define MTD_DRV_FAIL_WRITE_PAGED_REG    0x2<<8    /*SMI Paged register Write failed */
#define MTD_DRV_NO_ABLE_READ_REG        0x3<<8    /*Not able to read Phy Register. */
#define MTD_DRV_NO_ABLE_WRITE_REG        0x4<<8    /*Not able to write Phy Register. */
#define MTD_DRV_FAIL_READ_PAGED_REG    0x5<<8    /*SMI Paged register Read failed */

#define MTD_API_SFI_NOT_SUPPORT        0x1<<16    /* SFI not supported. */
#define MTD_API_XFI_NOT_SUPPORT        0x2<<16    /* XFI not supported. */
#define MTD_API_IS_NOT_SFI            0x8<<16    /* Input is not SFI. */
#define MTD_API_IS_NOT_XFI            0x9<<16    /* Input is not XFI. */
#define MTD_API_BAD_PARAMS            0xA<<16    /* Set bad parameters. */
#define MTD_API_FAIL_READ_REG            0x16<<16    /*Reading from phy reg failed. */
#define MTD_API_FAIL_WRITE_REG            0x17<<16    /*Writing to phy reg failed. */
#define MTD_API_FAIL_GET_REG_FIELD        0x1a<<16    /*Get from phy reg field failed. */
#define MTD_API_FAIL_SET_REG_FIELD        0x1b<<16    /*Set to phy reg field failed. */
#define MTD_API_UNKNOWN_DEV                0x1e<<16    /*Unknown Device */
#define MTD_API_UNKNOWN_PKG_GEN_TYPE    0x26<<16/*Unknown package generator type is set. */
#define MTD_API_UNKNOWN_CRC_CHECK_TYPE    0x27<<16/*Unknown CRC Check type is set. */
#define MTD_API_UNKNOWN_CRC_ERR_COUNT_TYPE    0x28<<16 /*Unknown CRC Error Counter type is set. */
#define MTD_API_UNKNOWN_CRC_FRM_COUNT_TYPE    0x29<<16 /*Unknown CRC Frame Counter type is set. */
 
#define MTD_API_CRC_FRM_COUNT_NOT_SUPPORT    0x2c<<16 /*CRC Frame Counter not supported. */
#define MTD_API_CRC_ERR_COUNT_NOT_SUPPORT    0x2d<<16 /*CRC Error Counter not supported. */
#define MTD_API_CRC_CHECK_NOT_SUPPORT    0x2e<<16/*CRC Check not supported. */
#define MTD_API_PKG_GEN_NOT_SUPPORT        0x2f<<16/*Package generator not supported. */
#define MTD_API_ERR_DEV                    0x3c<<16/*driver struture is NULL. */
#define MTD_API_ERR_SYS_CFG                0x3d<<16/*sys config is NULL. */
#define MTD_API_ERR_DEV_ALREADY_EXIST    0x3e<<16/*Device Driver already loaded. */
#define MTD_API_ERR_REGISTERD_FUNC        0x3f<<16/*Register function Failed. */

#define MTD_API_MACSEC_NOT_SUPPORT      0x46<<16 /*MACSEC not supported. */
#define MTD_API_PTP_NOT_SUPPORT         0x47<<16 /*1-step PTP not supported. */
#define MTD_API_BAD_PARAM               0x49<<16 /*Set  bad parameters. */

#define MTD_MSEC_FAIL_PORT_SET_MAC_CTRL            0x60<<16/*MacSec Set Port Mac Ctrl error.*/
#define MTD_MSEC_FAIL_PORT_GET_MAC_CTRL            0x61<<16/*MacSec Get Port Mac Ctrl error.*/
#define MTD_MSEC_FAIL_PORT_SET_MAC_SPEED        0x62<<16/*MacSec Set Port Speed error.*/
#define MTD_MSEC_FAIL_PORT_GET_MAC_SPEED        0x63<<16/*MacSec Get Port Speed error.*/
#define MTD_MSEC_FAIL_PORT_DIS_ELU_ENTRY        0x64<<16/*MacSec disable Elu entry error.*/
#define MTD_MSEC_FAIL_PORT_SET_ELU_ENTRY        0x65<<16/*MacSec set Elu entry error.*/
#define MTD_MSEC_FAIL_PORT_SET_ECT_ENTRY        0x66<<16/*MacSec set ECT entry error.*/
#define MTD_MSEC_FAIL_PORT_SET_EKEY_ENTRY        0x67<<16/*MacSec set EKey entry error.*/
#define MTD_MSEC_FAIL_PORT_SET_EHKEY_ENTRY        0x68<<16/*MacSec set EHKey entry error.*/
#define MTD_MSEC_FAIL_PORT_GET_ELU_ENTRY        0x69<<16/*MacSec get Elu entry error.*/
#define MTD_MSEC_FAIL_PORT_GET_ECT_ENTRY        0x6a<<16/*MacSec get ECT entry error.*/
#define MTD_MSEC_FAIL_PORT_GET_EKEY_ENTRY        0x6b<<16/*MacSec get EKey entry error.*/
#define MTD_MSEC_FAIL_PORT_GET_EHKEY_ENTRY        0x6c<<16/*MacSec get EHKey entry error.*/

#define MTD_MSEC_FAIL_PORT_DIS_ILU_ENTRY        0x70<<16/*MacSec disable Ilu entry error.*/
#define MTD_MSEC_FAIL_PORT_SET_ILU_ENTRY        0x71<<16/*MacSec set Ilu entry error.*/
#define MTD_MSEC_FAIL_PORT_SET_ICT_ENTRY        0x72<<16/*MacSec set ICT entry error.*/
#define MTD_MSEC_FAIL_PORT_SET_IKEY_ENTRY        0x73<<16/*MacSec set IKey entry error.*/
#define MTD_MSEC_FAIL_PORT_SET_IHKEY_ENTRY        0x74<<16/*MacSec set IHKey entry error.*/
#define MTD_MSEC_FAIL_PORT_GET_ILU_ENTRY        0x75<<16/*MacSec get Ilu entry error.*/
#define MTD_MSEC_FAIL_PORT_GET_ICT_ENTRY        0x76<<16/*MacSec get ICT entry error.*/
#define MTD_MSEC_FAIL_PORT_GET_IKEY_ENTRY        0x77<<16/*MacSec get IKey entry error.*/
#define MTD_MSEC_FAIL_PORT_GET_IHKEY_ENTRY        0x78<<16/*MacSec get IHKey entry error.*/
#define MTD_MSEC_FAIL_PORT_SET_NEXPN_ENTRY        0x79<<16/*MacSec set NexPn entry error.*/
#define MTD_MSEC_FAIL_PORT_GET_IGR_ENTRY        0x7a<<16/*MacSec get IGR entry error.*/

#define MTD_API_COPPER_NOT_SUPPORT       0x1<<16    /* Copper not supported. */
#define MTD_API_WOL_NOT_SUPPORT          0x2c<<16 /*WOL not supported. */
#define MTD_API_SYNCE_NOT_SUPPORT        0x2d<<16 /*SyncE not supported. */
#define MTD_API_ERROR_OVER_PORT_RANGE    0x38<<16/*The port is over range. */
#define MTD_API_FAIL_READ_PAGED_REG        0x4<<16    /*Reading from paged phy reg failed. */
#define MTD_API_FAIL_WRITE_PAGED_REG    0x5<<16    /*Writing to paged phy reg failed. */
#define MTD_API_FAIL_GET_PAGED_REG_FIELD    0x8<<16     /*Get from paged phy reg field failed. */
#define MTD_API_FAIL_SET_PAGED_REG_FIELD    0x9<<16     /*Set to paged phy reg field failed. */


#define MTD_DEV_MSECPTPCAPABLE(dev)   (dev->devEnabled && MTD_IS_MACSEC_CAPABLE(dev->deviceId))


/* WOL type and configuration */
/* WOL Type */
#define MTD_PHY_WOL_TYPE_PKT    0x4    /* SRAM Packet Match, frame event*/
#define MTD_PHY_WOL_TYPE_MAGIC  0x2    /* Magic Packet Match */
#define MTD_PHY_WOL_TYPE_LINKUP 0x1    /* Link up */

typedef struct
{
    MTD_U8    enable;  /* enable bit */
    MTD_U8    byte;    /* data */
} MTD_WOL_SRAM_DAT_STRUCT;

typedef struct 
{
    MTD_U8    sramPktNum;   /* Sram packet number(0-7); */
    MTD_BOOL  enable;       /* Enable; */
    MTD_BOOL  matchStatus;  /* Real time enable status; */
    MTD_U8    sramPktLength; /* Sram Packet Match length; */
    MTD_WOL_SRAM_DAT_STRUCT   sramPacket[128]; /* Sram packet data: 128 X [enable,byte] */
} MTD_WOL_PKT_MATCH_STRUCT;


/* Sync Clocking mode for 1340 and later */
#define MTD_SYNC_CLK_MODE_PORT_COPPER            0x0001
#define MTD_SYNC_CLK_MODE_PORT_125SERDES         0x0002
#define MTD_SYNC_CLK_MODE_PORT_QSGMII            0x0003

/* Sync Clocking Recovered clock for 1340 and later */
#define MTD_SYNC_CLK_RCLK1            0x0000
#define MTD_SYNC_CLK_RCLK2            0x0001
#define MTD_SYNC_CLK_RCLK1_2          0x0002
#define MTD_SYNC_CLK_RCLK_NO          0x0003

/* Sync Clocking Recovered clock frequency for 1340 and later */
#define MTD_SYNC_CLK_FREQ_25M            0x0000
#define MTD_SYNC_CLK_FREQ_125M            0x0001
#define MTD_SYNC_CLK_FREQ_NO            0x0002

/* Sync Clocking Reference clock  for 1340 and later */
#define MTD_SYNC_CLK_REF_CLK_XTAL        0x0000
#define MTD_SYNC_CLK_REF_CLK_SCLK        0x0001
#define MTD_SYNC_CLK_REF_CLK_NO            0x0002

#if C_LINKAGE
#ifdef __cplusplus
}
#endif
#endif

#endif /* __MTDMsecPtpApiDefs_h */
