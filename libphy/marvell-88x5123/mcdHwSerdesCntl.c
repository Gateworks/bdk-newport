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
* @file sample.c
*
* @brief This file contains higher level functions and global data for
* working with the SERDES driver of the Marvell X5123/EC808 PHY.
********************************************************************/
#include "mcdApiTypes.h"
#include "mcdApiRegs.h"
#include "mcdUtils.h"
#include "mcdHwCntl.h"
#include "mcdDiagnostics.h"
#include "mcdAPI.h"
#include "mcdFwDownload.h"
#include "mcdHwSerdesCntl.h"
#include "mcdAPIInternal.h"
#include "mcdInternalIpcApis.h"
#include "mcdPortCtrlApLogDefs.h"
#include "mcdInternalCtrlApInitIf.h"

#ifndef ASIC_SIMULATION
#ifndef MCD_RUN_WITH_CPSS
/* Avago include */
#include <aapl.h>
#include <aapl_core.h>
#include <serdes_core.h>
#include <sbus.h>
#else
/* Avago include */
#include <serdes/avago/aapl/include/aapl.h>
#include <serdes/avago/aapl/include/aapl_core.h>
#include <serdes/avago/aapl/include/serdes_core.h>
#include <serdes/avago/aapl/include/sbus.h>

#endif /*MCD_RUN_WITH_CPSS */
#endif /* ASIC_SIMULATION */

#ifdef MV_HWS_REDUCED_BUILD_EXT_CM3
extern MCD_STATUS genSwitchRegisterGet(MCD_U32 address, MCD_U32 *data, MCD_U32 mask);
extern MCD_STATUS genSwitchRegisterSet(MCD_U32 address, MCD_U32 data, MCD_U32 mask);
#endif
extern MCD_BOOT_MODE bootMode;
/************************* Globals *******************************************************/
#ifndef ASIC_SIMULATION
EXT void  ms_sleep(uint msec);

/* By default the VCO calibration is operated on Avago Serdes.
   To bypass the VCO calibration for AP port set:
   vcoSerdesCal = AVAGO_SERDES_INIT_BYPASS_VCO */
MCD_U32 vcoSerdesCal = 0x0;

/* For non-AP port: delay values for EnhanceTune and EnhanceTuneLite configuration */
MCD_U32  mcd_static_delay_10G[] = {25, 26, 28, 30}; /* best delay values for 10G speed */
MCD_U32  mcd_static_delay_25G[] = {15, 17, 19, 21}; /* best delay values for 25G speed */

#endif /* ASIC_SIMULATION */


/************************* * Pre-Declarations *******************************************************/
#ifdef MV_HWS_FREE_RTOS
extern MCD_STATUS mvPortCtrlAvagoLock(void);
extern MCD_STATUS mvPortCtrlAvagoUnlock(void);
#endif /* MV_HWS_FREE_RTOS */
MCD_STATUS mcdSerdesAutoTuneStatusShort
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_AUTO_TUNE_STATUS            *rxStatus,
    MCD_AUTO_TUNE_STATUS            *txStatus
);


#ifndef ASIC_SIMULATION
MCD_STATUS  mcdSerdesRxAutoTuneStatusShort
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_AUTO_TUNE_STATUS            *rxStatus
);
#endif


#define MCD_MAX_SERDES_NUMBER               16
#define MCD_SLICE_NUMBER                    2
#define MCD_MAX_SERDES_PER_PORT             4
#define MCD_MIN_EYE_SIZE                        10
#define MCD_EYE_TAP                              4

#define MCD_ICAL_TRAINING_MODE                   0
#define MCD_PCAL_TRAINING_MODE                   1

/* timeout for ICal tuning - 2 second should be enough */
#define ICAL_TUNE_TIME_LIMIT 2000

#ifdef MV_HWS_REDUCED_BUILD_EXT_CM3
extern MCD_SER_DEV  aaplSerdesDbDef[];
extern MCD_SER_DEV_PTR aaplSerdesDb[];
#endif
MCD_STATUS mcdSerdesAccessValidate(MCD_SER_DEV_PTR pSerdesDev, MCD_U32 sbus_addr);
MCD_STATUS mcdCheckSerdesInitStatus(MCD_DEV_PTR pDev, MCD_U16 serdesNum);

#ifndef ASIC_SIMULATION
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
static void user_supplied_xsmi_sbus_soft_reset(MCD_SER_DEV_PTR pSerdesDev);
static uint user_supplied_xsmi_sbus_function( void *ptr, unsigned int addr, unsigned char reg_addr,
                                           unsigned char command, unsigned int sbus_data, int recv_data_back);
#endif

/* extern */
MCD_U8 mcdBaudRate2DividerValue[LAST_MCD_SERDES_SPEED]=
{
    NA_VALUE,   /*  SPEED_NA   */
    8,          /*  _1_25G     */
    20,         /*  _3_125G    */
    32,         /*  _5G        */
    40,         /*  _6_25G     */
    66,         /*  _10_3125G  */
    70,         /*  _10_9375G  */
    78,         /*  _12_1875G  */
    80,         /*  _12_5G     */
    132,        /*  _20_625G   */
    165,        /*  _25_78125G */
    180         /*  _28_05G    */
};

static MCD_U8 mcdRetimerBaudRate2DividerValue[LAST_MCD_SERDES_SPEED]=
{
    NA_VALUE,   /*  SPEED_NA   */
    20,          /*  _1_25G     */
    10,         /*  _3_125G    */
    10,         /*  _5G        */
    10,         /*  _6_25G     */
    20,         /*  _10_3125G  */
    20,         /*  _10_9375G  */
    20,         /*  _12_1875G  */
    20,         /*  _12_5G     */
    40,         /*  _20_625G   */
    40,         /*  _25_78125G */
    40          /*  _28_05G    */
};

static MCD_U8 mcdBaudRate2DwellTimeValue[LAST_MCD_SERDES_SPEED]=
{
    NA_VALUE,   /*  SPEED_NA  */
    8,          /*  _1_25G    */
    8,          /*  _3_125G   */
    8,          /*  _5G       */
    9,          /*  _6_25G    */
    15,         /*  _10_3125G */
    15,         /*  _10_9375G */
    15,         /*  _12_1875G */
    15,         /*  _12_5G    */
    15,         /*  _20_625G  */
    15,         /*  _25_78125G*/
    15          /*  _28_05G   */
};

static int prvMcdSerdesRetimerRequireSignalOk = 1; /* default - signal_ok reqired */

MCD_PRE_DEFINED_CTLE_DATA serdesCtleParams[MCD_MAX_SERDES_NUMBER]=
{
   { 0, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0},
   { 0, 0, 0, 0, 0, 0}
};

MCD_SERDES_CONFIG_DATA serdesElectricalParams[MCD_MAX_SERDES_NUMBER]=
{
   { 0, 0, 7, 0, 0, 0},
   { 0, 0, 7, 0, 0, 0},
   { 0, 0, 7, 0, 0, 0},
   { 0, 0, 7, 0, 0, 0},
   { 0, 0, 7, 0, 0, 0},
   { 0, 0, 7, 0, 0, 0},
   { 0, 0, 7, 0, 0, 0},
   { 0, 0, 7, 0, 0, 0},
   { 0, 0, 7, 0, 0, 0},
   { 0, 0, 7, 0, 0, 0},
   { 0, 0, 7, 0, 0, 0},
   { 0, 0, 7, 0, 0, 0},
   { 0, 0, 7, 0, 0, 0},
   { 0, 0, 7, 0, 0, 0},
   { 0, 0, 7, 0, 0, 0},
   { 0, 0, 7, 0, 0, 0}

};

#ifdef MV_HWS_REDUCED_BUILD_EXT_CM3
MCD_MAN_TUNE_TX_CONFIG_OVERRIDE_DB serdesTxApOverrideParams[8][2] =
{
   { {0, 0}, {0, 0}},
   { {0, 0}, {0, 0}},
   { {0, 0}, {0, 0}},
   { {0, 0}, {0, 0}},
   { {0, 0}, {0, 0}},
   { {0, 0}, {0, 0}},
   { {0, 0}, {0, 0}},
   { {0, 0}, {0, 0}}
};
#endif

MCD_SERDES_LANE_STEERING_REMAP serdesTxRxRemapLaneSteering[MCD_MAX_SERDES_PER_PORT][MCD_SLICE_NUMBER] =
{
   { {1, 0}, {0, 1}},
   { {2, 3}, {3, 2}},
   { {3, 2}, {2, 3}},
   { {0, 1}, {1, 0}}
};

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
MCD_SERDES_TXRX_LANE_REMAP serdesTxRxLaneRemap[MCD_MAX_SERDES][MCD_SLICE_NUMBER] =
{
   { {0, 0}, {0, 0}},       /*Line port mapping - remap0 */
   { {1, 1}, {1, 1}},       /*Line port mapping - remap1 */
   { {2, 2}, {2, 2}},       /*Line port mapping - remap2 */
   { {3, 3}, {3, 3}},       /*Line port mapping - remap3 */
   { {0, 0}, {0, 0}},       /*Host port mapping - remap0 */
   { {1, 1}, {1, 1}},       /*Host port mapping - remap1 */
   { {2, 2}, {2, 2}},       /*Host port mapping - remap2 */
   { {3, 3}, {3, 3}}        /*Host port mapping - remap3 */
};
#endif

MCD_SERDES_TXRX_TUNE_PARAMS mcdSerdesTxRxTuneParamsArray[LAST_MCD_SERDES_SPEED] =
           { /*txAmp    emph0    emph1    DC    LF    HF    BW   LB   SQ */
                {0,       0,       0,     0,    0,    0,    0,    0,    0},
/* _1_25G */    {19,      0,       0,     100,  15,   15,   13,   0,  150},
/* _3_125G */   {16,      0,       0,     100,  15,   15,   13,   0,  150},
/* _5G */       {12,      0,       0,     80,   6,    15,   13,   0,  150},
/* _6_25G */    {12,      0,       0,     110,  4,    15,   13,   0,  150},
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3 /* none AP/ host CPU */
/* _10_3125G */ {4,       0,       0,     100,  3,    15,   13,   0,   68}, /* use copper/non-AP values (10G-KR/CR), for 10G-SR/10G-LR mode values use Tx/Rx manual API's */
#else
/* _10_3125G */ {2,      18,       4,     100,  3,    15,   13,   0,   68}, /* for AP - Tx Values must be the same as in init */
#endif
                {0,       0,       0,       0,  0,    0,    0,    0,    0},
/* _12_1875G */ {4,       0,       0,     100,  3,    15,   13,   0,   68},
                {0,       0,       0,       0,  0,    0,    0,    0,    0},
/* _20_625G */  {4,       0,       0,     110,  6,    9,    9,    0,   68},
/* _25_78125G */{1,       0,       6,     110,  6,    9,    9,    0,   84}, /* for AP TX values must be same as init */
                {0,       0,       0,       0,  0,    0,    0,    0,    0}
};

int mcdSerdesSetRetimerRequireSignalOk(int enable)
{
    prvMcdSerdesRetimerRequireSignalOk = enable;
    return 0;
}
/*******************************************************************************
* user_supplied_address
*
* DESCRIPTION:
*       Build address from sbus_addr, and reg_addr
*
* INPUTS:
*       None
*
* OUTPUTS:
*       None
*
* RETURNS:
*        register address
*******************************************************************************/
static MCD_U32 user_supplied_address
(
    unsigned char sbus_addr,
    unsigned char reg_addr
)
{
    MCD_U32 serdesAddress;

    serdesAddress = ((MCD_SBC_MASTER_BASE_ADDRESS)                  |
                     (sbus_addr << MCD_SBC_MASTER_SERDES_NUM_SHIFT) |
                     (reg_addr  << MCD_SBC_MASTER_REG_ADDR_SHIFT));

    return serdesAddress;
}

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************************
* user_supplied_xsmi_sbus_function
*
* DESCRIPTION:
*       Execute an sbus command
*
* INPUTS:
*       aapl      - Pointer to Aapl_t structure
*       addr      - SBus slice address
*       reg_addr  - SBus register to read/write
*       command   - 0 = reset, 1 = write, 2 = read
*       sbus_data - Data to write
*
* OUTPUTS:
*       None
*
* RETURNS:
*       Reads, returns read data
*       Writes and reset, returns 0
*******************************************************************************/
static unsigned int user_supplied_xsmi_sbus_function
(
    void *       ptr,
    unsigned int addr,
    unsigned char reg_addr,
    unsigned char command,
    unsigned int sbus_data,
    int recv_data_back)
{
    MCD_SER_ADDR_TYPE addr_struct;
    MCD_U32      commandAddress;
    MCD_U32      data      = 0;
    unsigned int rcode     = 0x0;

    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR) ptr;

    mcdWrapperAddrToStruct(addr,&addr_struct);

    if (command == 1/*Write Command - WRITE_SBUS_DEVICE*/)
    {
        commandAddress = user_supplied_address(addr_struct.sbus, reg_addr);
        mcdHwXmdioWrite32bit( pSerdesDev->client_data,  DONT_CARE, commandAddress, sbus_data);
    }
    else if (command == 2/*Read Command - READ_SBUS_DEVICE*/)
    {
        commandAddress = user_supplied_address(addr_struct.sbus, reg_addr);
        mcdHwXmdioRead32bit( pSerdesDev->client_data,  DONT_CARE, commandAddress, &data);
        /* return data in case of read command */
        rcode = data;
    }
    else if (command == 0 /*Soft Reset - RESET_SBUS_DEVICE*/)
    {
        user_supplied_xsmi_sbus_soft_reset(pSerdesDev);
    }
    else if (command == 3/*Hard Reset - CORE_SBUS_RESET*/)
    {
        /* This command is part of the entire chip reset */
        /* The AAPL start execute after chip reset, therefore this command can be removed */
    }

    return rcode;
}
/*******************************************************************************
* user_supplied_xsmi_sbus_soft_reset
*
* DESCRIPTION:
*       Execute Software reset
*
* INPUTS:
*       aapl - Pointer to Aapl_t structure
*
* OUTPUTS:
*       None
*
* RETURNS:
*       None
*******************************************************************************/
static void user_supplied_xsmi_sbus_soft_reset
(
    MCD_SER_DEV_PTR pSerdesDev
)
{
    MCD_U32 data      = 0;

    /* Read Common control register */
    mcdHwXmdioRead32bit(pSerdesDev->client_data,  DONT_CARE, MCD_SBC_UNIT_REG_ADDR(MCD_SBC_UNIT_COMMOM_CTRL_REG_ADDR), &data);

    if (data & MCD_SBC_UNIT_SOFT_RESET)
        return;

    /* Set SBC in reset */
    data &= ~MCD_SBC_UNIT_SOFT_RESET;
    /* Clear internal ROM enable - loading ROM from the application */
    data &= ~MCD_SBC_UNIT_INTERNAL_ROM_ENABLE;
    mcdHwXmdioWrite32bit( pSerdesDev->client_data,  DONT_CARE, MCD_SBC_UNIT_REG_ADDR(MCD_SBC_UNIT_COMMOM_CTRL_REG_ADDR), data);
    /* Take SBC out of reset */
    data |= MCD_SBC_UNIT_SOFT_RESET;
    mcdHwXmdioWrite32bit( pSerdesDev->client_data,  DONT_CARE, MCD_SBC_UNIT_REG_ADDR(MCD_SBC_UNIT_COMMOM_CTRL_REG_ADDR), data);
}
#else /*MV_HWS_REDUCED_BUILD_EXT_CM3*/
/*******************************************************************************
* user_supplied_cm3_sbus_soft_reset
*
* DESCRIPTION:
*       Execute Software reset
*
* INPUTS:
*       none
*
* OUTPUTS:
*       None
*
* RETURNS:
*       None
*******************************************************************************/
static void user_supplied_cm3_sbus_soft_reset ( void)
{
    MCD_U32 data      = 0;

    /* Read Common control register */
    genSwitchRegisterGet(MCD_SBC_UNIT_REG_ADDR(MCD_SBC_UNIT_COMMOM_CTRL_REG_ADDR), &data , 0xFFFFFFFF);

    if (data & MCD_SBC_UNIT_SOFT_RESET)
        return;

    /* Set SBC in reset */
    data &= ~MCD_SBC_UNIT_SOFT_RESET;
    /* Clear internal ROM enable - loading ROM from the application */
    data &= ~MCD_SBC_UNIT_INTERNAL_ROM_ENABLE;
    genSwitchRegisterSet(MCD_SBC_UNIT_REG_ADDR(MCD_SBC_UNIT_COMMOM_CTRL_REG_ADDR), data, 0xFFFFFFFF);
    /* Take SBC out of reset */
    data |= MCD_SBC_UNIT_SOFT_RESET;
    genSwitchRegisterSet(MCD_SBC_UNIT_REG_ADDR(MCD_SBC_UNIT_COMMOM_CTRL_REG_ADDR), data, 0xFFFFFFFF);
}

/*******************************************************************************
* user_supplied_cm3_sbus_function
*
* DESCRIPTION:
*       Execute an sbus command
*
* INPUTS:
*       aapl      - Pointer to Aapl_t structure
*       addr      - SBus slice address
*       reg_addr  - SBus register to read/write
*       command   - 0 = reset, 1 = write, 2 = read
*       sbus_data - Data to write
*
* OUTPUTS:
*       None
*
* RETURNS:
*       Reads, returns read data
*       Writes and reset, returns 0
*******************************************************************************/
static unsigned int user_supplied_cm3_sbus_function
(
    void *       ptr,
    unsigned int addr,
    unsigned char reg_addr,
    unsigned char command,
    unsigned int sbus_data,
    int recv_data_back)
{
    MCD_SER_ADDR_TYPE addr_struct;
    MCD_U32      commandAddress;
    MCD_U32      data      = 0;
    unsigned int rcode     = 0x0;

    mcdWrapperAddrToStruct(addr,&addr_struct);

    if (command == 1/*Write Command - WRITE_SBUS_DEVICE*/)
    {
        commandAddress = user_supplied_address(addr_struct.sbus, reg_addr);
        genSwitchRegisterSet (commandAddress, sbus_data, 0xFFFFFFFF) ;
    }
    else if (command == 2/*Read Command - READ_SBUS_DEVICE*/)
    {
        commandAddress = user_supplied_address(addr_struct.sbus, reg_addr);
        genSwitchRegisterGet( commandAddress, &data, 0xFFFFFFFF) ;
        /* return data in case of read command */
        rcode = data;
    }
    else if (command == 0/*Soft Reset - RESET_SBUS_DEVICE*/)
    {
        user_supplied_cm3_sbus_soft_reset();
    }
    else if (command == 3/*Hard Reset - CORE_SBUS_RESET*/)
    {
        /* This command is part of the entire chip reset */
        /* The AAPL start execute after chip reset, therefore this command can be removed */
    }

    return rcode;
}
#endif /* MV_HWS_REDUCED_BUILD_EXT_CM3 */
#endif/*ASIC_SIMULATION*/

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************************
* mcdLoadSBusSerdesFromCpuMemory
*
* DESCRIPTION:
*       Load Avago SPICO Firmware
*******************************************************************************/
MCD_STATUS mcdLoadSBusSerdesFromCpuMemory
(
    MCD_DEV_PTR pDev,
    unsigned int sbus_addr,
    IN MCD_U16 imageSize,
    IN MCD_U16 const image[]
)
{
#ifndef ASIC_SIMULATION
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    MCD_DBG_INFO(
        "Loading to SBus address %x data[0]=%x size(dec) %d\n",
        sbus_addr, image[0], imageSize);
    mcdWrapperSerdesUpload(
        pSerdesDev, sbus_addr, FALSE,
        imageSize, (short *)image);
#endif /* ASIC_SIMULATION*/
    return MCD_OK;
}

/*******************************************************************************
* mcdLoadSbusMasterFromCpuMemory
*
* DESCRIPTION:
*       Load Avago Sbus Master Firmware
*******************************************************************************/
MCD_STATUS mcdLoadSBusMasterFromCpuMemory
(
    MCD_DEV_PTR pDev,
    IN MCD_U16 imageSize, /* 0 if skipped */
    IN MCD_U16 const image[],
    IN MCD_U16 swapImageSize, /* 0 if skipped */
    IN MCD_U16 const swapImage[]
)
{
#ifndef ASIC_SIMULATION
   MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
   unsigned int sbus_addr = AVAGO_SBUS_MASTER_ADDRESS;

   if ((imageSize != 0) && (image != NULL))
   {
        mcdWrapperSerdesUpload(
            pSerdesDev, sbus_addr, FALSE,
            imageSize, (short *)image);

        if (pSerdesDev->return_code < 0)
        {
            MCD_DBG_ERROR("Avago FW Load Failed (return code 0x%x)\n", pSerdesDev->return_code);
            return MCD_STATUS_ERR_INIT;
        }
   }
   if ((swapImageSize != 0) && (swapImage != NULL))
   {
        mcdWrapperSerdesUploadSwapImage(
            pSerdesDev, sbus_addr,
            swapImageSize, (short *)swapImage);
        if (pSerdesDev->return_code < 0)
        {
            MCD_DBG_ERROR("Avago SWAP Load Failed (return code 0x%x)\n", pSerdesDev->return_code);
            return MCD_STATUS_ERR_INIT;
        }
   }
#endif /* ASIC_SIMULATION*/
    return MCD_OK;
}

/******************************************************************************
 MCD_STATUS mcdInitSerdesDev
*******************************************************************************/
MCD_STATUS mcdInitSerdesDev
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16     const *pBusMasterImage,
    IN MCD_U16     busMasterImageSize,
    IN MCD_U16     const *pBusMasterSwapImage,
    IN MCD_U16     busMasterSwapImageSize,
    IN MCD_U16     const *pSerdesImage,
    IN MCD_U16     serdesImageSize
)
{
#ifndef ASIC_SIMULATION
    MCD_SER_DEV_PTR pSerdesDev = 0;
    MCD_U16 errCode;

    pSerdesDev = mcdWrapperAllocDevStruct();
    if (pSerdesDev)
    {
        pDev->serdesDev = pSerdesDev;
    }
    else
    {
        MCD_DBG_ERROR("mcdInitSerdesDev: pSerdesDev is NULL\n");
        return MCD_FAIL;
    }

    pSerdesDev->client_data = (MCD_PVOID)pDev;

    pSerdesDev->sbus_func_ptr = user_supplied_xsmi_sbus_function;

    /* Take Avago device out of reset */
    user_supplied_xsmi_sbus_soft_reset(pSerdesDev);

     /* Change the SBUS master clk divider to 16. 0x3307F828 is indirect address */
    ATTEMPT(mcdHwSetPhyRegMask32bit(pDev,  DONT_CARE, 0x3307F828, 0xFFFF, 0x4));

    /* Change the Sensor clk divider to 78  to adr 0x33044404*/
    ATTEMPT(mcdHwSetPhyRegMask32bit(pDev,  DONT_CARE, MCD_SERDES_TSEN_IP_clock_divider, 0xFFFF, 0x4E));


    /* MCD supports SBUS only method */
    pSerdesDev->communication_method = AVAGO_USER_SUPPLIED_SBUS_DIRECT;

    /* Validate access to Avago device */
    ATTEMPT(mcdSerdesAccessValidate(pSerdesDev, 0));

    /* Initialize AAPL structure */
    aapl_get_ip_info(pSerdesDev,1);

    MCD_DBG_INFO("Loading Avago Firmware.......\n");
    /* SerDes FW was already downloaded when operating in HA mode */
    if (bootMode == MCD_REGULAR_BOOT_MODE)
    {
        /* Download Serdes's Firmware */
        /* ========================== */
        ATTEMPT(mcdLoadSBusSerdesFW(
            pDev, 0/*mdioPort*/, serdesImageSize, pSerdesImage, &errCode));
        if (pSerdesDev->return_code < 0)
        {
            MCD_DBG_ERROR("Avago Serdes FW Load Failed (return code 0x%x)\n", pSerdesDev->return_code);
            return MCD_STATUS_ERR_INIT;
        }

        /* Download SBus_Master Firmware */
        /* ============================= */
        ATTEMPT(mcdLoadSBusMasterFW(
            pDev, 0/*mdioPort*/,
            busMasterImageSize, pBusMasterImage,
            busMasterSwapImageSize, pBusMasterSwapImage,
            &errCode));
    }
    if (pSerdesDev->return_code < 0)
    {
        MCD_DBG_ERROR("Avago Master FW Load Failed (return code 0x%x)\n", pSerdesDev->return_code);
        return MCD_STATUS_ERR_INIT;
    }

    MCD_DBG_INFO("Done\n");

    /* Init Avago Access Protection in multi-process environment */
    /* This protection is implemented at the scope of the Host!! */

#endif /* ASIC_SIMULATION*/
 return MCD_OK;
}

#else
void mcdSerdesAaplAddrGet
(
    IN MCD_DEV_PTR pDev,
    OUT unsigned int  **devAddr,
    OUT unsigned int  *devSize
)
{
    MCD_SER_DEV_PTR pSerdesDev;
    pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    *devAddr = (unsigned int *)(pSerdesDev);
    MCD_DBG_INFO("mcdSerdesAaplAddrGet pDev->serdesDev %x serdes_int_timeout %x adr =%x \n",pSerdesDev,pSerdesDev->serdes_int_timeout,(&pSerdesDev->serdes_int_timeout));
    *devSize = (unsigned int)sizeof(_MCD_SER_DEV);
}


MCD_STATUS mcdSerdesAaplInit
(
    MCD_DEV_PTR  pDev
)
{
    unsigned int i;
    unsigned char devNum = 0;

    aaplSerdesDbDef[devNum].buf_cmd = NULL;
    aaplSerdesDbDef[devNum].buf_cmd_end = NULL;
    aaplSerdesDbDef[devNum].aacs_server_buffer = NULL;
    aaplSerdesDbDef[devNum].aacs_server = NULL;
    for(i = 0; i < AAPL_MAX_CHIPS; i++)
    {
        aaplSerdesDbDef[devNum].chip_name[i] = NULL;
        aaplSerdesDbDef[devNum].chip_rev[i] = NULL;
    }
    aaplSerdesDbDef[devNum].data_char_end = NULL;
    aaplSerdesDbDef[devNum].log = NULL;
    aaplSerdesDbDef[devNum].log_end = NULL;
    aaplSerdesDbDef[devNum].data_char = NULL;
    aaplSerdesDbDef[devNum].client_data = NULL;

    aaplSerdesDb[devNum]->sbus_func_ptr = user_supplied_cm3_sbus_function;
    aaplSerdesDb[devNum]->client_data = pDev;

    /* Initialize AAPL  */
    pDev->serdesDev = &(aaplSerdesDbDef[devNum]);
    return MCD_OK;
}
#endif /*#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3*/


#ifndef ASIC_SIMULATION
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************************
* mcdSerdesSetOneSideRetimerMode
*
* DESCRIPTION:
*       Configure serdes PCIE clock mux and  SD1 TX input mux
*
* INPUTS:
*       pSerdesDev
*       serdesNum - SERDES number
*       clockSourceSerdesNum - clock Source SERDES number
*       baudRate  - baudRate enum value
*       useSimpleTuneOnly - 0 - use enhanced tune, 1 - use simple tune
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesSetOneSideRetimerMode
(
    MCD_DEV_PTR         pDev,
    MCD_U8              serdesNum,
    MCD_U8              clockSourceSerdesNum,
    MCD_SERDES_SPEED    baudRate,
    MCD_U8              useSimpleTuneOnly
)
{
    MCD_U8 txdivider;
    MCD_U32  data;

    MCD_U8        serdes2Num = (serdesNum < MCD_HOST_SIDE_START_SERDES_NUMBER)
        ?(serdesNum + MCD_HOST_SIDE_START_SERDES_NUMBER)
        :(serdesNum - MCD_HOST_SIDE_START_SERDES_NUMBER);
#if 0
    MCD_U8  serdesArr[1] = {0};
#endif
    txdivider = mcdRetimerBaudRate2DividerValue[baudRate];

    /* Serdes Digital Reset */
    ATTEMPT(mcdSerdesResetImpl(pDev, serdes2Num, MCD_FALSE, MCD_TRUE, MCD_FALSE));

    /*ATTEMPT(mcdHwSetPhyRegField32bit(
      pDev, DONT_CARE, MCD_SERDES_Miscellaneous(serdes2Num) , 1, 2, (serdesNum & 3)));*/
    /* use clock of the 0-th serdes in the side of slice as reference for each opposite side TX */
    ATTEMPT(mcdHwSetPhyRegField32bit(
        pDev, DONT_CARE, MCD_SERDES_Miscellaneous(serdes2Num) , 1, 2, (clockSourceSerdesNum & 3)));
    ATTEMPT(mcdHwSetPhyRegField32bit(
        pDev, DONT_CARE, MCD_SERDES_EXTERNAL_CONFIGURATION_0(serdes2Num), 3, 3, ((serdesNum & 3) + 1)));

#if 0
    if (useSimpleTuneOnly)
    {
        ATTEMPT(mcdSerdesRxTune(pDev,serdesNum));
    }
    else
    {
        serdesArr[0] =  serdesNum;
        ATTEMPT(mcdSerdesEnhanceTune(pDev,serdesArr,1,0,15));
    }
#endif
    /* clear sig_ok_change interrupt */
    ATTEMPT(mcdHwGetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_Interrupt0_cause(serdesNum) , 5, 1, &data));

#define FAST_SWITCH_CLOCK
#ifdef FAST_SWITCH_CLOCK
    /*switch clock  */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdes2Num, 0x30,0x70, NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdes2Num, 0x5,(0x1000 + txdivider), NULL));
    /* TX PLL need time to change clock */
    mcdWrapperMsSleep(600);
#else
    /*switch clock  */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdes2Num, 0x5,(0x1000 + txdivider), NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdes2Num, 0x30,0x70, NULL));

    /* TX PLL need time to change clock */
    mcdWrapperMsSleep(100);
#endif

    /* Serdes Digital UnReset */
    ATTEMPT(mcdSerdesResetImpl(pDev, serdes2Num, MCD_FALSE, MCD_FALSE, MCD_FALSE));

#if 0
    /* Enable TX - moved to caller */
    ATTEMPT(mcdSerdesTxEnable(pDev, serdes2Num, MCD_TRUE));
#endif

    return MCD_OK;
}
#endif /*#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3*/
#endif /* ASIC_SIMULATION */
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************************
* mcdSerdesSetRetimerMode
*
* DESCRIPTION:
*       Configure serdes PCIE clock mux and  SD1 TX input mux
*
* INPUTS:
*       pSerdesDev
*       serdesNum - SERDES number
*       baudRate  - baudRate enum value
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesSetRetimerMode
(
    MCD_DEV_PTR         pDev,
    MCD_U8              serdesNum,
    MCD_SERDES_SPEED    baudRate
)
{
    MCD_U8 width;
#ifndef ASIC_SIMULATION
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
#endif
    MCD_U8        serdesHs = serdesNum + MCD_HOST_SIDE_START_SERDES_NUMBER;
    MCD_U8  serdesArr[1] = {0};

    if((baudRate == MCD_10_3125G) || (baudRate == MCD_12_1875G))        /* for 11.8G, 23.6G, 47.2G */
        width = 20;

    else
        /* (mode =_40BIT_ON)*/
        width = 40;

    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_Miscellaneous(serdesNum) , 1, 2, (serdesNum & 3)));
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_Miscellaneous(serdesHs) , 1, 2, (serdesNum & 3)));
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_EXTERNAL_CONFIGURATION_0(serdesNum), 3, 3, ((serdesNum & 3) + 1)));
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_EXTERNAL_CONFIGURATION_0(serdesHs), 3, 3, ((serdesNum & 3) + 1)));

    serdesArr[0] =  serdesHs;
    ATTEMPT(mcdSerdesEnhanceTune(pDev,serdesArr,1,0,15));
    serdesArr[0] =  serdesNum;
    ATTEMPT(mcdSerdesEnhanceTune(pDev,serdesArr,1,0,15));

    /*clear pending interrupts */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18, 0x8000, NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, 2, NULL));

    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesHs, 0x18, 0x8000, NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesHs, 0x19, 2, NULL));

    /*switch clock  */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x30,0x70, NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x5,(0x1000 + width), NULL));

    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesHs, 0x30,0x70, NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesHs, 0x5, (0x1000 + width), NULL));

    /*recalibrate CDR on line side */
    /*ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x1, 0x5, NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x1,0x7, NULL));*/
#ifndef ASIC_SIMULATION
    ATTEMPT(mcdWrapperSerdesTxRxEnableSet(pSerdesDev, (serdesNum + 1), MCD_TRUE, MCD_FALSE, MCD_TRUE));
    ATTEMPT(mcdWrapperSerdesTxRxEnableSet(pSerdesDev, (serdesNum + 1), MCD_TRUE, MCD_TRUE, MCD_TRUE));
#endif
    /* Serdes Digital Reset */
    ATTEMPT(mcdSerdesResetImpl(pDev, serdesNum, MCD_FALSE, MCD_TRUE, MCD_FALSE));
    ATTEMPT(mcdSerdesResetImpl(pDev, serdesHs, MCD_FALSE, MCD_TRUE, MCD_FALSE));
    /* Serdes Digital UnReset */
    ATTEMPT(mcdSerdesResetImpl(pDev, serdesNum, MCD_FALSE, MCD_FALSE, MCD_FALSE));
    ATTEMPT(mcdSerdesResetImpl(pDev, serdesHs, MCD_FALSE, MCD_FALSE, MCD_FALSE));
    return MCD_OK;
}


/*******************************************************************************
* mcdSerdesSetRetimerMode
*
* DESCRIPTION:
*       Configure serdes PCIE clock mux and  SD1 TX input mux
*
* INPUTS:
*       pSerdesDev
*       serdesNum - SERDES number
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesSetApRetimerMode
(
    MCD_DEV_PTR         pDev,
    MCD_U8              serdesNum,
    MCD_SERDES_SPEED    baudRate
)
{
#ifndef ASIC_SIMULATION
    MCD_U8 width;
    MCD_U8 serdesHs = serdesNum + MCD_HOST_SIDE_START_SERDES_NUMBER;

    if((baudRate == MCD_10_3125G) || (baudRate == MCD_12_1875G))        /* for 11.8G, 23.6G, 47.2G */
        width = 20;

    else
        /* (mode =_40BIT_ON)*/
        width = 40;

    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_Miscellaneous(serdesNum) , 1, 2, (serdesNum & 3)));
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_Miscellaneous(serdesHs) , 1, 2, (serdesNum & 3)));
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_EXTERNAL_CONFIGURATION_0(serdesNum), 3, 3, ((serdesNum & 3) + 1)));
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_EXTERNAL_CONFIGURATION_0(serdesHs), 3, 3, ((serdesNum & 3) + 1)));

    /*clear pending interrupts */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18, 0x8000, NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, 2, NULL));

    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesHs, 0x18, 0x8000, NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesHs, 0x19, 2, NULL));

    /*switch clock  */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x30,0x70, NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x5,(0x1000 + width), NULL));

    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesHs, 0x30,0x70, NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesHs, 0x5, (0x1000 + width), NULL));

    /*recalibrate CDR on line side */
    /*ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x1, 0x5, NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x1,0x7, NULL));*/

    ATTEMPT(mcdSerdesTxRxEnableSet(pDev, serdesNum, MCD_TRUE, MCD_FALSE, MCD_TRUE));
    ATTEMPT(mcdSerdesTxRxEnableSet(pDev, serdesNum, MCD_TRUE, MCD_TRUE, MCD_TRUE));

    /* Serdes Digital Reset */
    ATTEMPT(mcdSerdesResetImpl(pDev, serdesNum, MCD_FALSE, MCD_TRUE, MCD_FALSE));
    ATTEMPT(mcdSerdesResetImpl(pDev, serdesHs, MCD_FALSE, MCD_TRUE, MCD_FALSE));
    /* Serdes Digital UnReset */
    ATTEMPT(mcdSerdesResetImpl(pDev, serdesNum, MCD_FALSE, MCD_FALSE, MCD_FALSE));
    ATTEMPT(mcdSerdesResetImpl(pDev, serdesHs, MCD_FALSE, MCD_FALSE, MCD_FALSE));
#endif
    return MCD_OK;
}
/*******************************************************************************
* mcdSerdesSetRetimerClock
*
* DESCRIPTION:
*       Configure retimer clockk
*
* INPUTS:
*       pSerdesDev
*       serdesNum - SERDES number
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesSetRetimerClock
(
    MCD_DEV_PTR         pDev,
    unsigned int        serdesNum,
    MCD_SERDES_SPEED    baudRate
    )
{
#ifndef ASIC_SIMULATION
    MCD_U32 i,rc1,rc2;
    unsigned int txdivider,partner_sbus;
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;

    mcdWrapperMsSleep(10);
    for (i = 0; i < 10; i++)
    {
        /* check that the signal from this serdes is ok , so test its partner signal*/
        partner_sbus =  (serdesNum >= 8)? (serdesNum - 7): (serdesNum +  0x9);
        MCD_DBG_INFO("mcdSerdesSetRetimerClock  partner_sbus = %x\n", partner_sbus);
        /* check that the signal from this serdes is aok , so test its partner signal*/
        if (prvMcdSerdesRetimerRequireSignalOk)
        {
            rc1 = avago_serdes_get_signal_ok_live(pSerdesDev, partner_sbus);
        }
        else
        {
            rc1 = 1;
        }
        rc2 = avago_serdes_get_frequency_lock(pSerdesDev, partner_sbus);
        if (rc1 && rc2)
        {
           /*rxdivider = mcdBaudRate2DividerValue[baudRate];*/
            txdivider = mcdRetimerBaudRate2DividerValue[baudRate];
            /*external PCIE clock*/
            ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x30, 0x70, NULL));
            /*divider & 0xff) | (config->refclk_sync_master ? 1<<12 : 0) since config->refclk_sync_master = TRUE =>  divider & 0xff) | 1<<12*/
            ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x05, ((txdivider & 0xff) | 1 << 12), NULL));
            /*ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x06, rxdivider , NULL));*/
            break;
        }
        else mcdWrapperMsSleep(10);
    }

    if (i == 10) {
        MCD_DBG_ERROR("mcdSerdesSetRetimerClock  serdes %d; not ready1 rc1=%x rc2= %x\n", serdesNum, rc1, rc2);
        return MCD_FAIL;

    }

     /* after clock setting wait 100 msec for signals to be stable before TX connection setting*/
    mcdWrapperMsSleep(100);
    /* Serdes Digital Reset */
    ATTEMPT(mcdSerdesResetImpl(pDev, serdesNum, MCD_FALSE, MCD_TRUE, MCD_FALSE));
   /*Configure the SD1 TX input mux bits [5:3]*/
    MCD_DBG_ERROR("Configure the SD1 TX input mux bits  serdes = %x write %x \n", serdesNum, ((serdesNum & 3) + 1));
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_EXTERNAL_CONFIGURATION_0(serdesNum), 3, 3, ((serdesNum & 3) + 1)));
    mcdWrapperMsSleep(1);
    /* Serdes Digital UnReset */
    ATTEMPT(mcdSerdesResetImpl(pDev, serdesNum, MCD_FALSE, MCD_FALSE, MCD_FALSE));

#endif
    return MCD_OK;
}
#endif /* MV_HWS_REDUCED_BUILD_EXT_CM3 */

/*******************************************************************************
* mcdSerdesSetRetimerClockLaneSteeringMode
*
* DESCRIPTION:
*       Configure retimer clock in lane Steering mode
*
* INPUTS:
*       pSerdesDev
*       serdesNum - SERDES number
*       partnerSerdesNum
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
MCD_STATUS mcdSerdesSetRetimerClockLaneSteeringMode
(
    MCD_DEV_PTR         pDev,
    unsigned int        serdesNum,
    unsigned int        partnerSerdesNum,
    MCD_SERDES_SPEED    baudRate
)
{
#ifndef ASIC_SIMULATION
    MCD_U32 i;
    unsigned int txdivider;
    unsigned int partner_sbus  = partnerSerdesNum + 1;
    MCD_BOOL rc1, rc2;

    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;

    mcdWrapperMsSleep(10);
    for (i = 0; i < 10; i++)
    {
        /* check that the signal from this serdes is aok , so test its partner signal*/
        if (prvMcdSerdesRetimerRequireSignalOk)
        {
            rc1 = avago_serdes_get_signal_ok_live(pSerdesDev, partner_sbus);
        }
        else
        {
            rc1 = 1;
        }
        rc2 = avago_serdes_get_frequency_lock(pSerdesDev, partner_sbus);
        if (rc1 && rc2)
        {
            txdivider = mcdRetimerBaudRate2DividerValue[baudRate];
            /*divider & 0xff) | (config->refclk_sync_master ? 1<<12 : 0) since config->refclk_sync_master = TRUE =>  divider & 0xff) | 1<<12*/
            ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x05, ((txdivider & 0xff) | 1 << 12), NULL));
            /*external PCIE clock*/
            ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x30, 0x70, NULL));
            break;

        }
        else mcdWrapperMsSleep(1);
    }
    if (i == 10) {
        MCD_DBG_ERROR("mcdSerdesSetRetimerClock  serdes %d; not ready1 rc1=%x rc2= %x\n", serdesNum, rc1, rc2);
        return MCD_FAIL;
    }
    /* after clock setting wait 1 sec for signals to be stable before TX connection setting*/
    mcdWrapperMsSleep(1000);
    /* Serdes Digital Reset */
    ATTEMPT(mcdSerdesResetImpl(pDev, serdesNum, MCD_FALSE, MCD_TRUE, MCD_FALSE));
    /*Configure the SD1 TX input mux bits [5:3]*/
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_EXTERNAL_CONFIGURATION_0(serdesNum), 3, 3, ((partnerSerdesNum & 3) + 1)));
    mcdWrapperMsSleep(1);
    /* Serdes Digital UnReset */
    ATTEMPT(mcdSerdesResetImpl(pDev, serdesNum, MCD_FALSE, MCD_FALSE, MCD_FALSE));

#endif
    return MCD_OK;
}
#endif /*#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3*/

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************************
* mcdSetSerdesCtleParametersDB
*
* DESCRIPTION:
*       Store port serdeses electrical parameters in DB
*
* INPUTS:
*       port number
*       port mode
*       pointer to array with parameters values
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSetSerdesCtleParametersDB
(
    unsigned int        portNum,
    MCD_OP_MODE         portMode,
    MCD_PORT_PER_SERDES_CTLE_CONFIG_DATA* ctleParamsPtr
)
{
#ifndef ASIC_SIMULATION
    MCD_U32 lanesNum, serdesLaneNum;
    MCD_U32 baudRate;
    lanesNum = mcdPortModeGetLanesNum(portMode, MCD_LINE_SIDE);
    ATTEMPT(mcdGetLaneSpeed( portMode, MCD_LINE_SIDE, &baudRate));
    for (serdesLaneNum = portNum; serdesLaneNum < (lanesNum + portNum); serdesLaneNum++)
    {
        if ((ctleParamsPtr->ctleParams[serdesLaneNum].bitMapEnable >> MCD_CTLE_PARAM_DC_OFFSET) & 0x1)
        {
            serdesCtleParams[serdesLaneNum].dcGain = ctleParamsPtr->ctleParams[serdesLaneNum].dcGain;
        }
        else
        {
            serdesCtleParams[serdesLaneNum].dcGain = mcdSerdesTxRxTuneParamsArray[baudRate].dcGain;
        }
        if ((ctleParamsPtr->ctleParams[serdesLaneNum].bitMapEnable >> MCD_CTLE_PARAM_LF_OFFSET) & 0x1)
        {
            serdesCtleParams[serdesLaneNum].lowFrequency = ctleParamsPtr->ctleParams[serdesLaneNum].lowFrequency;
        }
        else
        {
            serdesCtleParams[serdesLaneNum].lowFrequency = mcdSerdesTxRxTuneParamsArray[baudRate].lowFrequency;
        }
        if ((ctleParamsPtr->ctleParams[serdesLaneNum].bitMapEnable >> MCD_CTLE_PARAM_HF_OFFSET) & 0x1)
        {
            serdesCtleParams[serdesLaneNum].highFrequency = ctleParamsPtr->ctleParams[serdesLaneNum].highFrequency;
        }
        else
        {
            serdesCtleParams[serdesLaneNum].highFrequency = mcdSerdesTxRxTuneParamsArray[baudRate].highFrequency;
        }
        if ((ctleParamsPtr->ctleParams[serdesLaneNum].bitMapEnable >> MCD_CTLE_PARAM_BW_OFFSET) & 0x1)
        {
            serdesCtleParams[serdesLaneNum].bandWidth = ctleParamsPtr->ctleParams[serdesLaneNum].bandWidth;
        }
        else
        {
            serdesCtleParams[serdesLaneNum].bandWidth = mcdSerdesTxRxTuneParamsArray[baudRate].bandWidth;
        }
        if ((ctleParamsPtr->ctleParams[serdesLaneNum].bitMapEnable >> MCD_CTLE_PARAM_LBW_OFFSET) & 0x1)
        {
            serdesCtleParams[serdesLaneNum].loopBandwidth = ctleParamsPtr->ctleParams[serdesLaneNum].loopBandwidth;
        }
        else
        {
            serdesCtleParams[serdesLaneNum].loopBandwidth = mcdSerdesTxRxTuneParamsArray[baudRate].loopBandwidth;
        }
    }

    lanesNum = mcdPortModeGetLanesNum(portMode,MCD_HOST_SIDE);
    ATTEMPT(mcdGetLaneSpeed( portMode, MCD_HOST_SIDE, &baudRate));
    for (serdesLaneNum = portNum; serdesLaneNum < (lanesNum + portNum); serdesLaneNum++)
    {
        if ((ctleParamsPtr->ctleParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].bitMapEnable >> MCD_CTLE_PARAM_DC_OFFSET) & 0x1)
        {
            serdesCtleParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].dcGain =
                                ctleParamsPtr->ctleParams[MCD_HOST_SIDE_START_SERDES_NUMBER +serdesLaneNum].dcGain;
        }
        else
        {
            serdesCtleParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].dcGain =
                                mcdSerdesTxRxTuneParamsArray[baudRate].dcGain;
        }
        if ((ctleParamsPtr->ctleParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].bitMapEnable >> MCD_CTLE_PARAM_LF_OFFSET) & 0x1)
        {
            serdesCtleParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].lowFrequency =
                                ctleParamsPtr->ctleParams[MCD_HOST_SIDE_START_SERDES_NUMBER +serdesLaneNum].lowFrequency;
        }
        else
        {
            serdesCtleParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].lowFrequency =
                                mcdSerdesTxRxTuneParamsArray[baudRate].lowFrequency;
        }
        if ((ctleParamsPtr->ctleParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].bitMapEnable >> MCD_CTLE_PARAM_HF_OFFSET) & 0x1)
        {
            serdesCtleParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].highFrequency =
                                ctleParamsPtr->ctleParams[MCD_HOST_SIDE_START_SERDES_NUMBER +serdesLaneNum].highFrequency;
        }
        else
        {
            serdesCtleParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].highFrequency =
                                mcdSerdesTxRxTuneParamsArray[baudRate].highFrequency;
        }
        if ((ctleParamsPtr->ctleParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].bitMapEnable >> MCD_CTLE_PARAM_BW_OFFSET) & 0x1)
        {
            serdesCtleParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].bandWidth =
                                ctleParamsPtr->ctleParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].bandWidth;
        }
        else
        {
            serdesCtleParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].bandWidth =
                                mcdSerdesTxRxTuneParamsArray[baudRate].bandWidth;
        }
        if ((ctleParamsPtr->ctleParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].bitMapEnable >> MCD_CTLE_PARAM_LBW_OFFSET) & 0x1)
        {
            serdesCtleParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].loopBandwidth =
                                ctleParamsPtr->ctleParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].loopBandwidth;
        }
        else
        {
            serdesCtleParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].loopBandwidth =
                                mcdSerdesTxRxTuneParamsArray[baudRate].loopBandwidth;
        }
    }
#endif
    return MCD_OK;

}

/*******************************************************************************
* mcdSetSerdesDefaultCtleParameters
*
* DESCRIPTION:
*       Store default per baud rateport serdeses CTLE parameters in DB
*
* INPUTS:
*       port number
*       port mode
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSetSerdesDefaultCtleParameters
(
    unsigned int        portNum,
    MCD_OP_MODE         portMode
)
{
#ifndef ASIC_SIMULATION
    MCD_U32 lanesNum, serdesLaneNum;
    MCD_U32    baudRate;

    lanesNum = mcdPortModeGetLanesNum(portMode,MCD_LINE_SIDE);
    ATTEMPT(mcdGetLaneSpeed( portMode, MCD_LINE_SIDE, &baudRate));
    for (serdesLaneNum = portNum; serdesLaneNum < (lanesNum + portNum); serdesLaneNum++)
    {
        serdesCtleParams[serdesLaneNum].dcGain        = mcdSerdesTxRxTuneParamsArray[baudRate].dcGain;
        serdesCtleParams[serdesLaneNum].lowFrequency  = mcdSerdesTxRxTuneParamsArray[baudRate].lowFrequency;
        serdesCtleParams[serdesLaneNum].highFrequency = mcdSerdesTxRxTuneParamsArray[baudRate].highFrequency;
        serdesCtleParams[serdesLaneNum].bandWidth     = mcdSerdesTxRxTuneParamsArray[baudRate].bandWidth;
        serdesCtleParams[serdesLaneNum].loopBandwidth = mcdSerdesTxRxTuneParamsArray[baudRate].loopBandwidth;
    }

    lanesNum = mcdPortModeGetLanesNum(portMode,MCD_HOST_SIDE);
    ATTEMPT(mcdGetLaneSpeed( portMode, MCD_HOST_SIDE, &baudRate));
    for (serdesLaneNum = portNum; serdesLaneNum < (lanesNum + portNum); serdesLaneNum++)
    {
        serdesCtleParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].dcGain        = mcdSerdesTxRxTuneParamsArray[baudRate].dcGain;
        serdesCtleParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].lowFrequency  = mcdSerdesTxRxTuneParamsArray[baudRate].lowFrequency;
        serdesCtleParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].highFrequency = mcdSerdesTxRxTuneParamsArray[baudRate].highFrequency;
        serdesCtleParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].bandWidth     = mcdSerdesTxRxTuneParamsArray[baudRate].bandWidth;
        serdesCtleParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].loopBandwidth = mcdSerdesTxRxTuneParamsArray[baudRate].loopBandwidth;
    }
#endif

    return MCD_OK;
}

/*******************************************************************************
* mcdSetSetSerdesElectricalParametersDB
*
* DESCRIPTION:
*       Store port serdeses electrical parameters in DB
*
* INPUTS:
*       port number
*       port mode
*       pointer to arraya with parameters values
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSetSetSerdesElectricalParametersDB
(
    unsigned int        portNum,
    MCD_OP_MODE         portMode,
    MCD_PORT_PER_SERDES_CONFIG_DATA*  paramsPtr
)
{
#ifndef ASIC_SIMULATION
        MCD_U32 lanesNum, serdesLaneNum;
        MCD_U32    baudRate;

    lanesNum = mcdPortModeGetLanesNum(portMode, MCD_LINE_SIDE);
    ATTEMPT(mcdGetLaneSpeed(portMode, MCD_LINE_SIDE, &baudRate));

    for (serdesLaneNum = portNum; serdesLaneNum < (lanesNum + portNum); serdesLaneNum++)
    {
        if ((paramsPtr->params[serdesLaneNum].bitMapEnable >> MCD_ELEC_PARAM_RX_POL_OFFSET) & 0x1)
        {
            serdesElectricalParams[serdesLaneNum].rxPolarity = paramsPtr->params[serdesLaneNum].rxPolarity;
        }
        else
        {
            serdesElectricalParams[serdesLaneNum].rxPolarity = 0;
        }
        if ((paramsPtr->params[serdesLaneNum].bitMapEnable >> MCD_ELEC_PARAM_TX_POL_OFFSET) & 0x1)
        {
            serdesElectricalParams[serdesLaneNum].txPolarity = paramsPtr->params[serdesLaneNum].txPolarity ;
        }
        else
        {
            serdesElectricalParams[serdesLaneNum].txPolarity = 0;
        }
        if ((paramsPtr->params[serdesLaneNum].bitMapEnable >> MCD_ELEC_PARAM_PRECUSOR_OFFSET) & 0x1)
        {
            serdesElectricalParams[serdesLaneNum].preCursor = paramsPtr->params[serdesLaneNum].preCursor;
        }
        else
        {
            serdesElectricalParams[serdesLaneNum].preCursor = mcdSerdesTxRxTuneParamsArray[baudRate].preCursor;
        }
        if ((paramsPtr->params[serdesLaneNum].bitMapEnable >> MCD_ELEC_PARAM_ATTENU_OFFSET) & 0x1)
        {
            serdesElectricalParams[serdesLaneNum].attenuation = paramsPtr->params[serdesLaneNum].attenuation;
        }
        else
        {
            serdesElectricalParams[serdesLaneNum].attenuation = mcdSerdesTxRxTuneParamsArray[baudRate].attenuation;
        }
        if ((paramsPtr->params[serdesLaneNum].bitMapEnable >> MCD_ELEC_PARAM_POSTCURSOR_OFFSET) & 0x1)
        {
            serdesElectricalParams[serdesLaneNum].postCursor = paramsPtr->params[serdesLaneNum].postCursor;
        }
        else
        {
            serdesElectricalParams[serdesLaneNum].postCursor = mcdSerdesTxRxTuneParamsArray[baudRate].postCursor;
        }
    }

    lanesNum = mcdPortModeGetLanesNum(portMode,MCD_HOST_SIDE);
    ATTEMPT(mcdGetLaneSpeed( portMode, MCD_HOST_SIDE, &baudRate));
    for (serdesLaneNum = portNum; serdesLaneNum < (lanesNum + portNum); serdesLaneNum++)
    {
        if ((paramsPtr->params[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].bitMapEnable >> MCD_ELEC_PARAM_RX_POL_OFFSET) & 0x1)
        {
            serdesElectricalParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].rxPolarity =
                                        paramsPtr->params[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].rxPolarity;
        }
        else
        {
            serdesElectricalParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].rxPolarity = 0;
        }
        if ((paramsPtr->params[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].bitMapEnable >> MCD_ELEC_PARAM_TX_POL_OFFSET) & 0x1)
        {
            serdesElectricalParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].txPolarity =
                                        paramsPtr->params[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].txPolarity;
        }
        else
        {
            serdesElectricalParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].txPolarity = 0;
        }
        if ((paramsPtr->params[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].bitMapEnable >> MCD_ELEC_PARAM_PRECUSOR_OFFSET) & 0x1)
        {
            serdesElectricalParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].preCursor =
                                        paramsPtr->params[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].preCursor;
        }
        else
        {
            serdesElectricalParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].preCursor =
                                        mcdSerdesTxRxTuneParamsArray[baudRate].preCursor;
        }
        if ((paramsPtr->params[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].bitMapEnable >> MCD_ELEC_PARAM_ATTENU_OFFSET) & 0x1)
        {
            serdesElectricalParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].attenuation =
                                        paramsPtr->params[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].attenuation;
        }
        else
        {
            serdesElectricalParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].attenuation =
                                        mcdSerdesTxRxTuneParamsArray[baudRate].attenuation;
        }
        if ((paramsPtr->params[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].bitMapEnable >> MCD_ELEC_PARAM_POSTCURSOR_OFFSET) & 0x1)
        {
            serdesElectricalParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].postCursor =
                                        paramsPtr->params[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].postCursor;
        }
        else
        {
            serdesElectricalParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].postCursor =
                                        mcdSerdesTxRxTuneParamsArray[baudRate].postCursor;
        }
    }
#endif
return MCD_OK;
}

/*******************************************************************************
* mcdSetSetSerdesDefaultElectricalParameters
*
* DESCRIPTION:
*       Store default per baud rateport serdeses electrical parameters in DB
*
* INPUTS:
*       port number
*       port mode
*       pointer to arraya with parameters values
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSetSetSerdesDefaultElectricalParameters
(
    unsigned int        portNum,
    MCD_OP_MODE         portMode
)
{
#ifndef ASIC_SIMULATION
    MCD_U32 lanesNum, serdesLaneNum;
    MCD_U32    baudRate;

    lanesNum = mcdPortModeGetLanesNum(portMode,MCD_LINE_SIDE);
    ATTEMPT(mcdGetLaneSpeed( portMode, MCD_LINE_SIDE, &baudRate));
    for (serdesLaneNum = portNum; serdesLaneNum < (lanesNum + portNum); serdesLaneNum++)
    {
        serdesElectricalParams[serdesLaneNum].rxPolarity  = 0;
        serdesElectricalParams[serdesLaneNum].txPolarity  = 0;
        serdesElectricalParams[serdesLaneNum].attenuation = mcdSerdesTxRxTuneParamsArray[baudRate].attenuation;
        serdesElectricalParams[serdesLaneNum].preCursor   = mcdSerdesTxRxTuneParamsArray[baudRate].preCursor;
        serdesElectricalParams[serdesLaneNum].postCursor  = mcdSerdesTxRxTuneParamsArray[baudRate].postCursor;
     }
    lanesNum = mcdPortModeGetLanesNum(portMode,MCD_HOST_SIDE);
    ATTEMPT(mcdGetLaneSpeed( portMode, MCD_HOST_SIDE, &baudRate));

    for (serdesLaneNum = portNum; serdesLaneNum < (lanesNum+ portNum); serdesLaneNum++)
    {
        serdesElectricalParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].rxPolarity  = 0;
        serdesElectricalParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].txPolarity  = 0;
        serdesElectricalParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].attenuation = mcdSerdesTxRxTuneParamsArray[baudRate].attenuation;
        serdesElectricalParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].preCursor   = mcdSerdesTxRxTuneParamsArray[baudRate].preCursor;
        serdesElectricalParams[MCD_HOST_SIDE_START_SERDES_NUMBER + serdesLaneNum].postCursor  = mcdSerdesTxRxTuneParamsArray[baudRate].postCursor;
    }
#endif
return MCD_OK;
}
#endif /*#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3*/

/**
* @internal mcdSerdesHaltDfeTraining function
* @endinternal
*
* @brief   Halt DFE tuning by reset un-reset sbus reset register
*
* @param[in] pDev                   - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] serdesArr              - SerDes Array
* @param[in] lanesNum               - num of active lanes
*
* @retval MCD_OK                    - on success.
* @retval MCD_FAIL                  - on failure
*
*/
MCD_STATUS mcdSerdesHaltDfeTraining
(
    MCD_DEV_PTR         pDev,
    unsigned int        *serdesArr,
    MCD_U16             lanesNum
)
{
#ifndef ASIC_SIMULATION
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    unsigned int phySerdesNum;
    unsigned int sbus_addr;
    MCD_U32 slice;
    /* get slice number */
    MCD_AUTO_TUNE_STATUS rxStatus;
    MCD_U32 tryCount = 0;
    MCD_U32 i;
    MCD_BOOL skipSbusReset = MCD_TRUE;

    /* Performing hard reset to the SERDES to ensure no training is running while
     the SERDES will go to disable mode */
    for (i=0; i<lanesNum; i++)
    {
        ATTEMPT(mcdSerdesRxAutoTuneStatusShort(pDev, serdesArr[i], &rxStatus));
        if ((rxStatus != MCD_TUNE_PASS) && (rxStatus != MCD_TUNE_RESET))
        {
            /* it's enough if even 1 of the lane needs sbus_reset to apply it for all active lanes */
            skipSbusReset = MCD_FALSE;
        }
    }

    if (skipSbusReset)
    {
        /* sbus reset is not needed */
        return MCD_OK;
    }

    for (i=0; i<lanesNum; i++)
    {
        MCD_GET_SLICE_NUM_BY_SERDES(serdesArr[i],slice);
        MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesArr[i],phySerdesNum);
        sbus_addr = phySerdesNum + 1;
        mcdSerdesAccessLock( pDev);
        if (pDev->haAccessDisable == MCD_FALSE)
        {
            avago_sbus_wr(pSerdesDev, sbus_addr, 0x07, 0x0);
        }
        mcdSerdesAccessUnlock( pDev);
    }

    ms_sleep(20);

    for (i=0; i< lanesNum; i++)
    {
        MCD_GET_SLICE_NUM_BY_SERDES(serdesArr[i], slice);
        MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesArr[i],phySerdesNum);
        sbus_addr = phySerdesNum + 1;
        mcdSerdesAccessLock( pDev);
        if (pDev->haAccessDisable == MCD_FALSE)
        {
            avago_sbus_wr( pSerdesDev, sbus_addr, 0x07, 0x02);
        }
        mcdSerdesAccessUnlock( pDev);
    }
    ms_sleep(10);

    for (i=0; i< lanesNum; i++)
    {
        ATTEMPT(mcdSerdesRxAutoTuneStatusShort(pDev, serdesArr[i], &rxStatus));
        while ((rxStatus != MCD_TUNE_PASS) && (rxStatus != MCD_TUNE_RESET) && (tryCount < 500))
        {
            ATTEMPT(mcdSerdesRxAutoTuneStatusShort(pDev, serdesArr[i], &rxStatus));
            /* since we are waiting for HW to finish it is ok to use delay at this point, there is no need
               for SW parallelization - same effect */
            tryCount++;
            ms_sleep(10);
        }
    }
#endif
    return MCD_OK;
}


/*******************************************************************************
* mcdSerdesPowerCtrl
*
* DESCRIPTION:
*       Power up SERDES
*
* INPUTS:
*       pSerdesDev
*       serdesNum - SERDES number
*       powerUp   - True for PowerUP, False for PowerDown
*       baudRate  - Serdes speed
*       retimerMode TRUE if serdes in Retimer mode
*       refClkSel - reference clock source select (primary/secondary)
*       refClkDiv - refernce clock source divider
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
int mcdSerdesPowerCtrl
(
    MCD_DEV_PTR         pDev,
    unsigned int        serdesNum,
    unsigned char       powerUp,
    MCD_SERDES_SPEED    baudRate,
    MCD_BOOL            retimerMode,
    MCD_U32             refClkSel,
    MCD_U32             refClkDiv
)
{
#ifndef ASIC_SIMULATION
    Avago_serdes_init_config_t *config;
    Avago_serdes_init_config_t configDef;

    unsigned int rxdivider,dwell,sbus_addr;
    unsigned int tryCount;
    unsigned int errors = 0;
    int data;
    MCD_U32 regData = 0;
    MCD_U32 widthMode10Bit = 0;
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    MCD_U32 slice = 0;
    unsigned int phySerdesNum;

    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);

    sbus_addr = phySerdesNum + 1;

    if ((pDev->serdesStatus.serdesPowerStatus[serdesNum] == powerUp) && (powerUp == MCD_FALSE))
    {
        /* operation already done by service CPU */
        return MCD_OK;
    }

    pDev->serdesStatus.serdesPowerStatus[serdesNum] = powerUp;

   /* for Serdes PowerDown */
    if (powerUp == MCD_FALSE)
    {
        /* if Training is in progress give it chance to finish and turn serdes off anyway */
        ATTEMPT(mcdHwGetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_Core_Status(phySerdesNum), 1, 1, &regData));
        tryCount = 0;
        while (regData && (tryCount++ < 5))
        {
           ATTEMPT(mcdHwGetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_Core_Status(phySerdesNum), 1, 1, &regData));
        }
        /* turn serdes off */
        ATTEMPT(mcdSerdesTxRxEnableSet(pDev, serdesNum, MCD_FALSE, MCD_FALSE, MCD_FALSE));
        /* TxClk/RxClk Tlat_en=0. Return to default */
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_EXTERNAL_CONFIGURATION_0(phySerdesNum), 13, 2, 0));

        /* Read the saved value from AVAGO_SD_METAL_FIX register to check the Rx/Tx width (saved in mode == _10BIT_ON) */
        ATTEMPT(mcdHwGetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_Miscellaneous(phySerdesNum) , 9, 1, &widthMode10Bit));
        if ((widthMode10Bit >> 9) == 1)
        {
            /* Set back the value of AVAGO_SD_METAL_FIX register if it was changed in 10BIT_ON mode for GPCS modes */
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_Miscellaneous(phySerdesNum) , 9, 1, 0));
        }

        if (retimerMode)
        {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_EXTERNAL_CONFIGURATION_0(phySerdesNum), 3, 3, 0));
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_EXTERNAL_CONFIGURATION_1(phySerdesNum), 2, 2, 0x00));
            /*Configure the serdes PCIE clock mux using the SD1 Miscellaneous register bits [2:1]*/
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_Miscellaneous(phySerdesNum) , 1, 2, 0));
        }
       /* Serdes Reset */
        ATTEMPT(mcdSerdesResetImpl(pDev, serdesNum, MCD_TRUE, MCD_TRUE, MCD_TRUE));

        return MCD_OK;
    }

    /* Power On !!!!!!!!*/

    /*Serdes external conf1 bits[3:2]=0x01 (serdes analog unreset ,digital still in reset)*/
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_EXTERNAL_CONFIGURATION_1(phySerdesNum), 2, 2, 0x01));

    /* for Serdes PowerUp */
    /* Initialize the SerDes slice */
    mcdWrapperSerdesInitConfig(&configDef);
    config = &configDef;

    rxdivider = mcdBaudRate2DividerValue[baudRate];

    if (rxdivider == NA_VALUE)
    {
        MCD_DBG_ERROR("mcdSerdesPowerCtrl no rxdivider for baudRate %d. \n", baudRate);
        return MCD_STATUS_BAD_PARAM;
    }

    config->tx_divider = rxdivider;
    config->rx_divider = rxdivider;
    /* initializes the Avago_serdes_init_config_t struct */
    config->sbus_reset = FALSE;
    config->signal_ok_threshold = MCD_SERDES_DEFAILT_SIGNAL_OK_THRESHOLD;

    /* Select the Rx & Tx data path width */
    if (baudRate == MCD_1_25G) /* mode is 10BIT_ON)*/
    {
        if ((pDev->noPpmEn[serdesNum & 0x7] == MCD_FALSE) && retimerMode)
        {
            /* Valid only for Retimer mode and not for noPpm mode */
            config->rx_width = config->tx_width = 20;
        }
        else
        {
            config->rx_width = config->tx_width = 10;
        }

        /* Save the width setting for PRBS test in AVAGO_SD_METAL_FIX register.
           It is needed for GPCS modes: the PRBS test can run in these modes only with Rx/Tx width=20BIT.
           If the Rx/Tx width=10BIT then it will be changed to 20BIT in mcdSerdesTestGen function */
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_Miscellaneous(phySerdesNum) , 9, 1, 1));
    }
    else if((baudRate == MCD_10_3125G) || (baudRate == MCD_12_1875G) || (baudRate == MCD_3_125G))       /* for 3_125G 11.8G, 23.6G, 47.2G */
        config->rx_width = config->tx_width = 20;

    else
    /* (mode =_40BIT_ON)*/
           config->rx_width = config->tx_width = 40;

    config->init_mode = AVAGO_INIT_ONLY;
    MCD_DBG_INFO("mcdSerdesPowerCtrlImpl init_configuration: physical serdes %d\n",phySerdesNum);
    MCD_DBG_INFO("   sbus_reset = %x \n",config->sbus_reset);
    MCD_DBG_INFO("   init_tx = %x \n",config->init_tx);
    MCD_DBG_INFO("   init_rx = %x \n",config->init_rx);
    MCD_DBG_INFO("   init_mode = %x \n",config->init_mode);
    MCD_DBG_INFO("   tx_divider = 0x%x \n",config->tx_divider);
    MCD_DBG_INFO("   rx_divider = 0x%x \n",config->rx_divider);
    MCD_DBG_INFO("   tx_width = 0x%x \n",config->tx_width);
    MCD_DBG_INFO("   rx_width = 0x%x \n",config->rx_width);
    MCD_DBG_INFO("   tx_phase_cal = %x \n",config->tx_phase_cal);
    MCD_DBG_INFO("   tx_output_en = %x \n",config->tx_output_en);
    MCD_DBG_INFO("   signal_ok_en = %x \n",config->signal_ok_en);
    MCD_DBG_INFO("   signal_ok_threshold= %x \n",config->signal_ok_threshold);

    /* Serdes Analog Un Reset*/
    ATTEMPT(mcdSerdesResetImpl(pDev, serdesNum, MCD_FALSE, MCD_TRUE, MCD_TRUE));
     /* Reference clock source */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_EXTERNAL_CONFIGURATION_0(phySerdesNum), 8, 1, refClkSel));
     /* Reference clock divider */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_EXTERNAL_CONFIGURATION_0(phySerdesNum), 11, 2, refClkDiv));

    /* TxClk/RxClk Tlat_en=1. The logic of the Tlat need to be 1 in order to enable Clk to MAC/PCS regardless of Serdes readiness */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_EXTERNAL_CONFIGURATION_0(phySerdesNum), 13, 2, 3));
    mcdSerdesAccessLock( pDev);
    if (pDev->haAccessDisable == MCD_FALSE)
    {
        errors = mcdWrapperSerdesInit(pSerdesDev, sbus_addr, config);
    /*set the polarity - it is not hanled in SerdeInit*/

        mcdWrapperSetRxPolarity(pSerdesDev, (sbus_addr), serdesElectricalParams[serdesNum].rxPolarity);
        mcdWrapperSetTxPolarity(pSerdesDev, (sbus_addr), serdesElectricalParams[serdesNum].txPolarity);
    }
    mcdSerdesAccessUnlock( pDev);
    MCD_CHECK_RET_CODE1(pSerdesDev,sbus_addr);
    if (errors > 0)
    {
        MCD_DBG_ERROR("SerDes init complete for SerDes at addr 0x%x; Errors in ILB: %d. \n", sbus_addr, errors);
    }
    if (errors == 0 && mcdWrapperGetReturnCode(pSerdesDev) == 0)
    {
        MCD_DBG_INFO("The SerDes at address 0x%x is initialized.\n", sbus_addr);
    }

    if (vcoSerdesCal != AVAGO_SERDES_INIT_BYPASS_VCO)
    {
        MCD_STATUS     res;
        int serdesTemperature, coreTemperature;
        int txTherm, txBin, rxTherm, rxBin;

        /* get the Avago Serdes Temperature (in C) */
        ATTEMPT(mcdSerdesGetTemperature(pDev, &serdesTemperature, &coreTemperature));

        /* get the calibration code(value) for Tx */
        ATTEMPT(mcdSerdesCalCodeGet(pDev, serdesNum, MCD_TRUE, &txTherm, &txBin));

        /* get the calibration code(value) for Rx */
        ATTEMPT(mcdSerdesCalCodeGet(pDev,serdesNum, MCD_FALSE , &rxTherm, &rxBin));

        /* Compensate the VCO calibration value according to Temperature */
        res = mcdSerdesVcoConfig(pDev,serdesNum, serdesTemperature, txTherm, txBin, rxTherm, rxBin);
        if (res != MCD_OK)
        {
            MCD_DBG_INFO("mcdSerdesVcoConfig failed (%d)\n", res);
            return MCD_FAIL;
        }
    }

    /* Disable TAP1 before training */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x26, 0x5B00, NULL));

    /* change CTLE bias from 1 to 0 */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18, 0x4033, NULL));

    /* read the CTLE bias */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x1A, 0x0, &data));
    if (pDev->serdesStatus.ctleBiasData[serdesNum])
    {
        /* set CTLE bias to 1 */
        data |= 0x1000;
    }
    else
    {
        /* set CTLE bias to 0 to */
        data &= 0xCFFF;
    }
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, data, NULL));

    /*clear pending interrupts */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18, 0x8000, NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, 2, NULL));

#ifdef MV_HWS_REDUCED_BUILD_EXT_CM3
    if (baudRate == MCD_3_125G)
    {
       /* Improve the CDR lock process */
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18,0x40FB, NULL));
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19,0x1200, NULL));
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18,0x40A9, NULL));
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19,0x1100, NULL));
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18,0x4001, NULL));
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19,0x41FF, NULL));
    }
#endif

    ATTEMPT(mcdSerdesManualTxConfig( pDev, serdesNum, serdesElectricalParams[serdesNum].attenuation,
                                 serdesElectricalParams[serdesNum].postCursor, serdesElectricalParams[serdesNum].preCursor));
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
    ATTEMPT(mcdSerdesManualCtleConfig (pDev, serdesNum,
                                    serdesCtleParams[serdesNum].dcGain, serdesCtleParams[serdesNum].lowFrequency,
                                    serdesCtleParams[serdesNum].highFrequency,serdesCtleParams[serdesNum].bandWidth,
                                    serdesCtleParams[serdesNum].loopBandwidth, mcdSerdesTxRxTuneParamsArray[baudRate].squelch ));
#else
    ATTEMPT(mcdSerdesManualCtleConfig (pDev, serdesNum,
                                    mcdSerdesTxRxTuneParamsArray[baudRate].dcGain, mcdSerdesTxRxTuneParamsArray[baudRate].lowFrequency,
                                    mcdSerdesTxRxTuneParamsArray[baudRate].highFrequency,mcdSerdesTxRxTuneParamsArray[baudRate].bandWidth,
                                    mcdSerdesTxRxTuneParamsArray[baudRate].loopBandwidth, mcdSerdesTxRxTuneParamsArray[baudRate].squelch ));
#endif

    ATTEMPT(mcdSerdesResetImpl(pDev, serdesNum, MCD_FALSE, retimerMode, MCD_FALSE));


#if 1 /**/
   dwell = 1;
   dwell = dwell;
   if (baudRate == MCD_1_25G)
   { /* set dwwell time only in 1G */
       /* select DFE tuning dwell time */
       ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18, 0x7, NULL));

       /* big register write LSB */
       ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, 0x800, NULL));

       /* big register write MSB */
       ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, 0, NULL));
   }
#else /**/
    dwell = mcdBaudRate2DwellTimeValue[baudRate];

    /* select DFE tuning dwell time */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18, 0x7, NULL));

    /* big register write LSB */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, 1<<dwell, NULL));

    /* big register write MSB */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, 0, NULL));
#endif
#endif /* ASIC_SIMULATION*/
    return MCD_OK;
}
/**
* @internal mcdSerdesLogicalToPhysicalConvert function
* @endinternal
*
* @brief   convert Rx logical serdes to physical serdes
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_U32 mcdSerdesLogicalToPhysicalConvert(MCD_DEV_PTR  pDev, MCD_U32 serdesNum, MCD_U32 slice)
{
    MCD_U32 phySerdes;
    phySerdes = serdesNum;
    if (serdesNum < MCD_HOST_SIDE_START_SERDES_NUMBER)
    {
        if (pDev->laneRemapCfg[slice].lineRemapMode == MCD_LANE_REMAP_ENABLE)
        {
            phySerdes = (((pDev->laneRemapCfg[slice].lineRxRemapVector >> ((serdesNum - (4*slice))*3)) & 0x3))
                    + (slice * 4);
        }
    }
    else
    {
        if (pDev->laneRemapCfg[slice].hostRemapMode == MCD_LANE_REMAP_ENABLE)
        {
            phySerdes = ((pDev->laneRemapCfg[slice].hostRxRemapVector >> ((serdesNum-MCD_HOST_SIDE_START_SERDES_NUMBER)
                    - (4*slice))*3) & 0x3) + MCD_HOST_SIDE_START_SERDES_NUMBER + (slice*4);
        }
    }
    return phySerdes;
}

/**
* @internal mcdSerdesLogicalToPhysicalConvertTx function
* @endinternal
*
* @brief   convert Tx logical serdes to physical serdes
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_U32 mcdSerdesLogicalToPhysicalConvertTx(MCD_DEV_PTR  pDev, MCD_U32 serdesNum, MCD_U32 slice)
{
    MCD_U32 phySerdes;
    phySerdes = serdesNum;
    if (serdesNum < MCD_HOST_SIDE_START_SERDES_NUMBER)
    {
        if (pDev->laneRemapCfg[slice].lineRemapMode == MCD_LANE_REMAP_ENABLE)
        {
            phySerdes = (((pDev->laneRemapCfg[slice].lineTxRemapVector >> ((serdesNum - (4*slice))*3)) & 0x3))
                    + (slice * 4);
        }
    }
    else
    {
        if (pDev->laneRemapCfg[slice].hostRemapMode == MCD_LANE_REMAP_ENABLE)
        {
            phySerdes = ((pDev->laneRemapCfg[slice].hostTxRemapVector >> ((serdesNum-MCD_HOST_SIDE_START_SERDES_NUMBER)
                    - (4*slice))*3) & 0x3) + MCD_HOST_SIDE_START_SERDES_NUMBER + (slice*4);
        }
    }
    return phySerdes;
}

/*******************************************************************************
* mcdSerdesResetImpl
*
* DESCRIPTION:
*       Per SERDES Clear the serdes registers (back to defaults.
*
* INPUTS:
*       pSerdesDev
*       serdesNum - serdes number
*       analogReset - Analog Reset (On/Off)
*       digitalReset - digital Reset (On/Off)
*       syncEReset - SyncE Reset (On/Off)
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
unsigned int mcdSerdesResetImpl
(
    MCD_DEV_PTR      pDev,
    unsigned int     serdesNum,
    unsigned int     analogReset,
    unsigned int     digitalReset,
    unsigned int     syncEReset
)
{

#ifndef ASIC_SIMULATION
    unsigned int slice;
    unsigned int phySerdesNum;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    if (pDev->laneSteeringCfg.laneSteeringTxRemap[serdesNum])
    {
        MCD_LOGIC_TO_PHYSICAL_SERDES_TX_MAC((MCD_U32)serdesNum, phySerdesNum);
    }
    else
    {
        MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);
    }
    /* SERDES SD RESET/UNRESET init */
    /* to do analog reset - write 0 to SD analog reset bit in MCD_SERDES_EXTERNAL_CONFIGURATION_1 register */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_EXTERNAL_CONFIGURATION_1(phySerdesNum), 2, 1, ~analogReset ));

    /* SERDES RF RESET/UNRESET init */
    /* to do digital reset - write 0 to SD digital reset bit in MCD_SERDES_EXTERNAL_CONFIGURATION_1 register */

    ATTEMPT(mcdHwSetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_EXTERNAL_CONFIGURATION_1(phySerdesNum), 3, 1, ~digitalReset ));

    /* SERDES SYNCE RESET init */
    if(syncEReset == MCD_TRUE)
    {
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_EXTERNAL_CONFIGURATION_0(phySerdesNum), 6, 1, 0 ));
    }
    else /* SERDES SYNCE UNRESET init */
    {
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_EXTERNAL_CONFIGURATION_0(phySerdesNum), 6, 1, 1 ));
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_EXTERNAL_CONFIGURATION_1(phySerdesNum), 8, 8, 0xDD));
    }

#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

/* flags for enabling trace of register and spico interrupt access  - see mcdSetRegAccessTraceOn*/
extern  MCD_BOOL mcdTraceSpicoInterruptTraceEn;

/*******************************************************************************
* mcdSerdesSpicoInterrupt
*
* DESCRIPTION:
*       Issue the interrupt to the Spico processor.
*       The return value is the interrupt number.
*
* INPUTS:
*       pSerdesDev
*       serdesNum - physical serdes number
*       interruptCode - Code of interrupt
*       interruptData - Data to write
*
* OUTPUTS:
*       result - spico interrupt return value
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
int mcdSerdesSpicoInterrupt
(
    MCD_DEV_PTR     pDev,
    unsigned int    serdesNum,
    unsigned int    interruptCode,
    unsigned int    interruptData,
    int             *result
)
{
#ifndef ASIC_SIMULATION
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    unsigned int  sbus_addr;
    unsigned int slice;
    unsigned int phySerdesNum;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    if (pDev->laneSteeringCfg.laneSteeringTxRemap[serdesNum])
    {
        MCD_LOGIC_TO_PHYSICAL_SERDES_TX_MAC((MCD_U32)serdesNum, phySerdesNum);
    }
    else
    {
        MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);
    }
    sbus_addr = phySerdesNum + 1;

    if (result == NULL)
    {
            mcdSerdesAccessLock(pDev);
            if (pDev->haAccessDisable == MCD_FALSE)
            {
                mcdWrapperSerdesInt(pSerdesDev, sbus_addr, interruptCode, interruptData);
            }
            mcdSerdesAccessUnlock(pDev);
    }
    else
    {
            mcdSerdesAccessLock(pDev);
            *result = mcdWrapperSerdesInt(pSerdesDev, sbus_addr, interruptCode, interruptData);
            mcdSerdesAccessUnlock(pDev);
    }

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
     /* trace */
     if(mcdTraceSpicoInterruptTraceEn)
     {
         if(result != NULL)
         {
             printf("\nmcdSerdesSpicoInterrupt:Interrupt Code: 0x%08X data: 0x%08X  result: 0x%08X\n",
                     interruptCode, interruptData, *result);
         }
         else
         {
             printf("\nmcdSerdesSpicoInterrupt:Interrupt Code: 0x%08X data: 0x%08X\n", interruptCode, interruptData);
         }
     }

#endif
     MCD_CHECK_RET_CODE(pSerdesDev);

#endif /* ASIC_SIMULATION */

    return MCD_OK;
}


int mcdtemperatureGlobal = 0;
unsigned int mcdtimeInterval = 5000;
unsigned int mcdlastTimeStamp = 0;

extern MCD_U32 mvPortCtrlCurrentTs(void);

/*******************************************************************************
* mcdSerdesGetTemperature
*
* DESCRIPTION:
*       Get the Temperature (in C)of hottest TEMP sensor.
* INPUTS:
*       pSerdesDev
*
* OUTPUTS:
*       coreTemperature,serdesTemperature - (pointer to) temperature in Celsius degrees
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesGetTemperature
(
    MCD_DEV_PTR     pDev,
    OUT MCD_32 *serdesTemperature,
    OUT MCD_32 *coreTemperature
)
{
#ifndef ASIC_SIMULATION
    MCD_UINT data;
    MCD_32 temperatureVal;
#ifdef MV_HWS_REDUCED_BUILD_EXT_CM3
    MCD_U32 miliSeconds=0;
#endif
    *serdesTemperature = 0;
    *coreTemperature = 0;


    /* set TSEN reset to normal state*/
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
    ATTEMPT(mcdHwSetPhyRegMask32bit(pDev, DONT_CARE, TEMPERATURE_SENSOR_28NM_CONTROL_MSB, 0x100, 0x100));
    /* unreset takes some time */
    mcdWait(pDev, 10);
#else
    miliSeconds = mvPortCtrlCurrentTs();
    if ((miliSeconds > mcdlastTimeStamp + mcdtimeInterval) || (miliSeconds < mcdlastTimeStamp))
    {
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, TEMPERATURE_SENSOR_28NM_CONTROL_MSB, 8, 1, 1));
        /* unreset takes some time */
        mcdWrapperMsSleep(10);
#endif

    /*read sensor data*/
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
    ATTEMPT(mcdHwGetPhyRegMask32bit(pDev, DONT_CARE, TEMPERATURE_SENSOR_STATUS,0x7ff, &data));
#else
    ATTEMPT(mcdHwGetPhyRegField32bit(pDev, DONT_CARE, TEMPERATURE_SENSOR_STATUS, 0, 11, &data));
#endif
    if (data & 0x400) /*if valid bit is OK*/
    {
        data &= 0x03FF;     /* Mask down to 9b temp value */
        temperatureVal = (MCD_32)data;
        mcdtemperatureGlobal = ((temperatureVal * 10000) - 5844500) / (21445);  /* Scale to degrees */
    }
    else
    {
        MCD_DBG_ERROR("mcdSerdesGetTemperature: data is not ready\n");
        return MCD_FAIL;
    }
    MCD_DBG_INFO("mcdSerdesGetTemperature: serdesTemperature:%7d C\n coreTemperature:%7d C\n", *serdesTemperature, *coreTemperature);
#ifdef MV_HWS_REDUCED_BUILD_EXT_CM3
        mcdlastTimeStamp = miliSeconds;
    }
#endif
    *coreTemperature = *serdesTemperature = mcdtemperatureGlobal;
#endif


    return MCD_OK;

}

/*******************************************************************************
* mcdSerdesCalCodeSet
*
* DESCRIPTION:
*       Set the calibration code(value) for Rx or Tx
*
* INPUTS:
*       pSerdesDev
*       serdesNum - SERDES number
*       mode      - True for Tx mode, False for Rx mode
*       therm     - Thermometer of VCO (0...0xFFFF)
*       bin       - bin of VCO (0...0xFFFF)
*
* OUTPUTS:
*       None.
*
* RETURNS:*       0  - on success
*       1  - on error
*
*******************************************************************************/
unsigned int mcdSerdesCalCodeSet
(
    MCD_DEV_PTR     pDev,
    int serdesNum,
    MCD_BOOL mode,
    int therm,
    int bin
)
{
#ifndef ASIC_SIMULATION
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18, 0x4002 | (mode << 9), NULL));

    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, therm, NULL));

    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18, 0x4003 | (mode << 9), NULL));

    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, bin, NULL));
#endif /* ASIC_SIMULATION */
    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesCalCodeGet
*
* DESCRIPTION:
*       Get the calibration code(value) for Rx or Tx
*
* INPUTS:
*       pDev
*       serdesNum - SERDES number
*       mode      - True for Tx mode, False for Rx mode
*
* OUTPUTS:
*       therm - Thermometer of VCO  (0...0xFFFF)
*       bin   - bin of VCO  (0...0xFFFF)
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
unsigned int mcdSerdesCalCodeGet
(
    MCD_DEV_PTR     pDev,
    int serdesNum,
    MCD_BOOL    mode,
    int         *therm,
    int         *bin
)
{
#ifndef ASIC_SIMULATION
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18, 0x4002 | (mode << 9), NULL));

    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x1A, 0, therm));

    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18, 0x4003 | (mode << 9), NULL));

    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x1A, 0, bin));
#endif /* ASIC_SIMULATION */
    return MCD_OK;
}
/*******************************************************************************
* mcdSerdesCalCodeShift
*
* DESCRIPTION:
*       Shift the calcode according to the amount value
*
* INPUTS:
*       pDev
*       serdesNum - SERDES number
*       mode      - True for Tx mode, False for Rx mode
*       shift     - amount of cal-code shift
*       therm     - Thermometer of VCO  (0...0xFFFF)
*       bin       - bin of VCO  (0...0xFFFF)
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
unsigned int mcdSerdesCalCodeShift
(
    MCD_DEV_PTR     pDev,
    int serdesNum,
    MCD_BOOL mode,
    int shift,
    int therm,
    int bin
)
{
#ifndef ASIC_SIMULATION
    unsigned int    res;
    int             bin_portion;

    bin_portion = (bin & 0x7) + shift;

    therm = (bin_portion > 7) ? ((therm  <<1 )+1): therm;
    therm = (bin_portion < 0) ? (therm >> 1) : therm;

    bin_portion &=0x7;
    bin = (bin & 0xFFF8)| bin_portion;

    res = mcdSerdesCalCodeSet(pDev, serdesNum, mode, therm, bin);
    if (res != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSerdesCalCodeSet failed (%d)\n", res);
        return MCD_FAIL;
    }
#endif /* ASIC_SIMULATION */
    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesShiftCalc
*
* DESCRIPTION:
*       Calculate the Shift value according to the Temperature
*
* INPUTS:
*       pDev
*
* OUTPUTS:
*       shift - Shift value for calibration code in Rx and Tx
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
unsigned int mcdSerdesShiftCalc
(
   MCD_DEV_PTR     pDev,
   int             temperature,
   int             *shift
)
{
#ifndef ASIC_SIMULATION
    *shift = 0;

    if (temperature < -20)
        *shift = 2;
    else if ((temperature >= -20) && (temperature <= 0))
        *shift = 1;
    else if ((temperature > 30) && (temperature <= 75))
        *shift = -1;
    else if (temperature > 75)
        *shift = -2;

#endif /* ASIC_SIMULATION */
    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesVcoConfig
*
* DESCRIPTION:
*       Compensate the VCO calibration value according to Temperature in order
*       to enable Itemp operation
*
* INPUTS:
*       pSerdesDev
*       serdesNum - SERDES number
*       temperature - Temperature (in C) from Avago Serdes
*       txTherm     - Tx Thermometer of VCO  (0...0xFFFF)
*       txBin       - Tx bin of VCO  (0...0xFFFF)
*       rxTherm     - Rx Thermometer of VCO  (0...0xFFFF)
*       rxBin       - Rx bin of VCO  (0...0xFFFF)
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
unsigned int mcdSerdesVcoConfig
(
    MCD_DEV_PTR     pDev,
    unsigned int    serdesNum,
    int     temperature,
    int     txTherm,
    int     txBin,
    int     rxTherm,
    int     rxBin
)
{
#ifndef ASIC_SIMULATION
    int shift=0;
    unsigned int res;

    /* Calculate the Shift value according to the Temperature */
    res = mcdSerdesShiftCalc(pDev, temperature, &shift);
    if (res != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSerdesShiftCalc failed (%d)\n", res);
        return MCD_FAIL;
    }

    /* Shift the calibration code for Tx */
    res = mcdSerdesCalCodeShift(pDev, serdesNum, MCD_TRUE, shift, txTherm, txBin);
    if (res != MCD_OK)
    {
        MCD_DBG_ERROR("mcdAvagoCalCodeShift failed (%d)\n", res);
        return MCD_FAIL;
    }

    /* shift the calibration code for Rx */
    res = mcdSerdesCalCodeShift(pDev, serdesNum, MCD_FALSE, shift, rxTherm, rxBin);
    if (res != MCD_OK)
    {
        MCD_DBG_ERROR("mcdAvagoCalCodeShift failed (%d)\n", res);
        return MCD_FAIL;
    }
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesAutoTuneResult
*
* DESCRIPTION:
*       Per SERDES return the adapted tuning results
*       Can be run after create port.
*
* INPUTS:
*        pSerdesDev
*       serdesNum - physical serdes number
*
* OUTPUTS:
*       results - the adapted tuning results.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesAutoTuneResult
(
    MCD_DEV_PTR                 pDev,
    MCD_U8                      serdesNum,
    MCD_AUTO_TUNE_RESULTS       *results
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    mcdMemSet(results,0,sizeof(*results));

#else
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    unsigned int sbus_addr;
    unsigned int   data, column, i;
    unsigned int phySerdesNum, slice;
    int ctle[5];
    int dfe[13];
    MCD_SER_TX_EQ_TYPE tx_eq;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC((MCD_U32)serdesNum,phySerdesNum);

    sbus_addr = phySerdesNum + 1;

    mcdSerdesAccessLock(pDev);
    /* Gets the TX equalization values */
    mcdWrapperGetTxFFE(pSerdesDev, sbus_addr, &tx_eq);
    mcdSerdesAccessUnlock(pDev);
    MCD_CHECK_RET_CODE(pSerdesDev);

    results->txAmp   = tx_eq.atten;
    results->txEmph0 = tx_eq.post;
    results->txEmph1 = tx_eq.pre;

    for (i=0; i <= 12; i++)
    {
        if (i==0)
        {
            /* TAP1 is in column 1 */
            column=1;
            data = (column << 12) | (8 << 8);
        }
        else
        {
            column=3;
            data = (column << 12) | (i << 8);
        }
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x126, data, &dfe[i]));
        (dfe[i] > 0x8000) ? (dfe[i] = dfe[i] - 0x10000) : dfe[i];
        results->DFE[i] = dfe[i];
        MCD_DBG_INFO("   DFE[%d] = %d \n", i, results->DFE[i]);
    }

    column=2;
    for (i = 0; i <= 4; i++)
    {
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x126, ((column << 12) | (i << 8)), &ctle[i]));
    }

    results->HF = ctle[0];
    results->LF = ctle[1];
    results->DC = ctle[2];
    results->BW = ctle[3];
    results->LB = ctle[4];
    mcdSerdesAccessLock( pDev);
    results->EO = mcdWrapperEyeGetSimpleMetric(pSerdesDev, sbus_addr);
    mcdSerdesAccessUnlock( pDev);
    MCD_CHECK_RET_CODE(pSerdesDev);

    MCD_DBG_INFO("   HF = %d \n", results->HF);
    MCD_DBG_INFO("   LF = %d \n", results->LF);
    MCD_DBG_INFO("   DC = %d \n", results->DC);
    MCD_DBG_INFO("   BW = %d \n", results->BW);
    MCD_DBG_INFO("   LB = %d \n", results->LB);
    MCD_DBG_INFO("   EO = %d \n", results->EO);
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesManualTxConfig
*
* DESCRIPTION:
*       Per SERDES configure the TX parameters: amplitude, 3 TAP Tx FIR.
*       Can be run after create port.
*
* INPUTS:
*       pSerdesDev
*       serdesNum - physical serdes number
*       txAmp     - Tx amplitude 10
*       emph0     - Post-cursor setting 9
*       emph1     - Pre-cursor setting 2
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*******************************************************************************/
MCD_STATUS mcdSerdesManualTxConfig
(
    MCD_DEV_PTR         pDev,
    MCD_U8              serdesNum,
    MCD_16              txAmp,
    MCD_16              emph0,
    MCD_16              emph1
 )
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    txAmp = txAmp;
    emph0 = emph0;
    emph1 = emph1;
#else
    Avago_serdes_tx_eq_t tx_eq;
    MCD_INT     rc1, rc2, rc3, rc4;


    /* Set the TX equalization values */
    tx_eq.atten = (short)txAmp;     /* Attenuator setting */
    tx_eq.post  = (short)emph0;     /* Post-cursor setting */
    tx_eq.pre   = (short)emph1;     /* Pre-cursor setting */

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
    if (pDev->highAvailabilityMode)
    {
        return MCD_OK;
    }
#endif
    if((tx_eq.atten == tx_eq.pre) && (tx_eq.atten == tx_eq.post))
    {
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x15, (3 << 14) | (tx_eq.atten & 0xFF), &rc3));
    }
    else
    {
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x15, (3 << 14) | 0, &rc1));
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x15, (2 << 14) | (tx_eq.post & 0xFF), &rc2));
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x15, (1 << 14) | (tx_eq.atten & 0xFF), &rc3));
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x15, (0 << 14) | (tx_eq.pre & 0xFF), &rc4));

        /* If SpicoInterrupt 0x15 succeeds to run - the return code is the Interrupt number=0x15
           The TX equalization configuration succeeds only if all the four SpicoInterrupt settings are passed: (0x15)x4=0x54 */
        if ((rc1+rc2+rc3+rc4) != MCD_SERDES_TX_EQUALIZE_PASS)
        {
            MCD_DBG_ERROR("SerDes failed to apply since new EQ settings exceed the limit %d %d %d %d\n", rc1, rc2, rc3, rc4);
            return MCD_FAIL;
        }
    }

#if 0
    /* the SlewRate parameter is not supported in Avago Serdes */
    /* these settings are needed due to problem with SlewRate configuration in avago_serdes_set_tx_eq */
    ATTEMPT(mcdSerdesSpicoInterrupt(devNum, portGroup, serdesNum, 0x18, 0x4240, NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(devNum, portGroup, serdesNum, 0x19, (0x184 + slewRate), NULL));
#endif

#endif /* ASIC_SIMULATION */
    return MCD_OK;
}
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************************
* mcdSerdesManualTxConfigGet
*
* DESCRIPTION:
*       Per SERDES get the configure TX parameters: amplitude, 3 TAP Tx FIR.
*       Can be run after create port.
*
* INPUTS:
*       pSerdesDev
*       serdesNum - physical serdes number
*
* OUTPUTS:
*       configParams - Manual Tx params structures:
*           txAmp       Tx amplitude
*           txAmpAdj    not used in Avago serdes
*           emph0       TX emphasis 0
*           emph1       TX emphasis 1
*           txAmpShft   not used in Avago serdes
*
* RETURNS:
*       0  - on success
*       1  - on error
*******************************************************************************/
MCD_STATUS mcdSerdesManualTxConfigGet
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_MAN_TUNE_TX_CONFIG_DATA      *configParams
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    mcdMemSet(configParams,0,sizeof(*configParams));
#else

    MCD_AUTO_TUNE_RESULTS   results;

    /* txAmpAdj and txAmpShft are not used in Avago serdes */
    configParams->txAmpAdj  = MCD_FALSE;
    configParams->txAmpShft = MCD_FALSE;

    ATTEMPT(mcdSerdesAutoTuneResult(pDev, serdesNum, &results));

    /* Get the TX configuration values */
    configParams->txAmp   = results.txAmp;
    configParams->txEmph0 = results.txEmph0;
    configParams->txEmph1 = results.txEmph1;
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}
#endif /*MV_HWS_REDUCED_BUILD_EXT_CM3*/
/*******************************************************************************
* mcdSerdesTxEnable
*
* DESCRIPTION:
*       Enable/Disable Tx.
*
* INPUTS:
*       pSerdesDev
*       serdesNum - physical serdes number
*       enable    - whether to enable or disable Tx.
*
* OUTPUTS:
*    None
*
* RETURNS:
*       MCD_OK        - on success
*       MCD_FAIL      - on error
*       MCD_STATUS_NOT_READY - when training is in process.
*
*******************************************************************************/
MCD_STATUS mcdSerdesTxEnable
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_BOOL                        enable
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    enable = enable;
#else
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    unsigned int sbus_addr;
    unsigned int data;
    unsigned int slice;
    unsigned int phySerdesNum;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES((MCD_U32)serdesNum,slice);
    if (pDev->laneSteeringCfg.laneSteeringTxRemap[serdesNum])
    {
        /* convert logic serdes number to physical serdes number */
        MCD_LOGIC_TO_PHYSICAL_SERDES_TX_MAC((MCD_U32)serdesNum,phySerdesNum);
    }
    else
    {
        /* convert logic serdes number to physical serdes number */
        MCD_LOGIC_TO_PHYSICAL_SERDES_MAC((MCD_U32)serdesNum,phySerdesNum);
    }

    sbus_addr = phySerdesNum + 1;


    /* Semaphore protection should start before training-check function is performed and take place until
       tx-enable function is finised, to avoid situations where training-check function returned one status
       and by the time we will perform tx-enable, the training status will be changed by another CPU.*/
    mcdSerdesAccessLock(pDev);

    if (pDev->haAccessDisable == MCD_FALSE)
    {
        /* If training is in process, not performing tx enable */
        data = mcdWrapperPMDStatus(pSerdesDev, sbus_addr);
        MCD_CHECK_RET_CODE_WITH_ACTION(pSerdesDev, mcdSerdesAccessUnlock(pDev));

        if (data == 0x2)
        {
            MCD_DBG_ERROR("mcdSerdesTxEnable failed because training is in process\n");
            mcdSerdesAccessUnlock(pDev);
            return MCD_STATUS_NOT_READY;
        }

    /* Set the TX output Enabled/Disabled */
        mcdWrapperSerdesTXenableSet(pSerdesDev, sbus_addr, enable);
    }
    mcdSerdesAccessUnlock(pDev);
    MCD_CHECK_RET_CODE(pSerdesDev);

#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesTxRxEnableSet
*
* DESCRIPTION:
*       Enable/Disable Tx, Rx, Tx Output.
*
* INPUTS:
*       pSerdesDev
*       serdesNum - physical serdes number
*       enable    - whether to enable or disable Tx.
*
* OUTPUTS:
*    None
*
* RETURNS:
*       MCD_OK        - on success
*       MCD_FAIL      - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesTxRxEnableSet
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_BOOL                        txEnable,
    MCD_BOOL                        rxEnable,
    MCD_BOOL                        tx_outputEnable
)
{
#ifndef ASIC_SIMULATION
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    unsigned int sbus_addr;
    unsigned int slice;
    unsigned int phySerdesNum;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES((MCD_U32)serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    if (pDev->laneSteeringCfg.laneSteeringTxRemap[serdesNum])
    {
        MCD_LOGIC_TO_PHYSICAL_SERDES_TX_MAC((MCD_U32)serdesNum, phySerdesNum);
    }
    else
    {
        MCD_LOGIC_TO_PHYSICAL_SERDES_MAC((MCD_U32)serdesNum, phySerdesNum);
    }
    sbus_addr = phySerdesNum + 1;

    mcdSerdesAccessLock(pDev);
    if (pDev->haAccessDisable == MCD_FALSE)
    {
        /* Set the TX/RX/Output Enabled/Disabled */
        mcdWrapperSerdesTxRxEnableSet(pSerdesDev, sbus_addr, txEnable, rxEnable, tx_outputEnable);
    }
    mcdSerdesAccessUnlock(pDev);
    MCD_CHECK_RET_CODE(pSerdesDev);
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************************
* mcdSerdesTxEnableGet
*
* DESCRIPTION:
*        Gets the status of SERDES Tx mode - Enable/Disable transmission of packets.
*        Use this API to disable Tx for loopback ports.
*
* INPUTS:
*       pSerdesDev
*       serdesNum - physical serdes number
*
* OUTPUTS:
*       enablePtr:
*           - MCD_TRUE - Enable transmission of packets from SERDES
*           - MCD_FALSE - Disable transmission of packets from SERDES
*
* RETURNS:
*       0  - on success
*       1  - on error
*
* COMMENTS:
*       Disabling transmission of packets from SERDES causes to link down
*       of devices that are connected to the port.
*
*******************************************************************************/
MCD_STATUS mcdSerdesTxEnableGet
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_BOOL                        *enablePtr
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    enablePtr = enablePtr;
#else
    MCD_U32 phySerdesNum, slice;
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    unsigned int sbus_addr;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES((MCD_U32)serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC((MCD_U32)serdesNum,phySerdesNum);
    sbus_addr = phySerdesNum + 1;

    mcdSerdesAccessLock(pDev);
    /* Get the SERDES TX output mode: TRUE in enabled, FALSE otherwise */
    *enablePtr = mcdWrapperSerdesTXenableGet(pSerdesDev, sbus_addr);
    mcdSerdesAccessUnlock(pDev);
    MCD_CHECK_RET_CODE(pSerdesDev);
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}
#endif /*#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3*/
/*******************************************************************************
* mcdSerdesSignalDetectGet
*
* DESCRIPTION:
*       Per SERDES get indication is signal detected.
* INPUTS:
*       pSerdesDev
*       serdesNum - physical serdes number
*
* OUTPUTS:
*       signalDet - TRUE if signal detected and FALSE otherwise.
*
* RETURNS:
*       0  - on success
*       1  - on error
*******************************************************************************/
MCD_STATUS mcdSerdesSignalDetectGet
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_BOOL                        *signalDet
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    signalDet = signalDet;
#else

    MCD_U32 i, data;
    unsigned int slice, phySerdesNum;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES((MCD_U32)serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC((MCD_U32)serdesNum,phySerdesNum);

     /* check is Signal detected on Serdes */
    for(i=0; i < 10; i++)
    {

        ATTEMPT(mcdHwGetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_External_Status(phySerdesNum), 2, 1, &data));
        if(data)
        {
            *signalDet = MCD_FALSE;
            return MCD_OK;
        }
    }

    *signalDet = MCD_TRUE;
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************************
* mcdSerdesRxSignalCheck
*
* DESCRIPTION:
*       Per SERDES check there is Rx Signal and indicate if Serdes is ready for Tuning or not
*
* INPUTS:
*       pDev
*       serdesNum - physical serdes number
*
* OUTPUTS:
*       rxSignal - Serdes is ready for Tuning or not
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesRxSignalCheck
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_AUTO_TUNE_STATUS            *rxSignal
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    rxSignal = rxSignal;
#else

    MCD_U32 i,data;
    MCD_U32 phySerdesNum, slice;
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    unsigned int sbus_addr;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES((MCD_U32)serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC((MCD_U32)serdesNum,phySerdesNum);
    sbus_addr = phySerdesNum + 1;

    *rxSignal =  MCD_TUNE_NOT_READY;
    for (i = 0;i<50; i++)
    {
        /* check if there is Rx Signal on Serdes */
        data = mcdWrapperMemRead(pSerdesDev, sbus_addr, AVAGO_LSB, 0x027);
        if ((data  & 0x0010) != 0)
        {
            *rxSignal =  MCD_TUNE_READY;
            MCD_DBG_INFO("*rxSignal  i= %d\n",i);
            break;
        }
        else
             mcdWrapperMsSleep(10);

    }

#endif /* ASIC_SIMULATION */

    return MCD_OK;
}
#endif /*#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3*/
/*******************************************************************************
* mcdSerdesDfeConfig
*
* DESCRIPTION:
*       Per SERDES configure the DFE parameters.
*       Can be run after create port.
*
* INPUTS:
*       pDev
*       serdesNum - physical serdes number
*       dfeMode   - start/stop/iCal/pCal
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*******************************************************************************/
MCD_STATUS mcdSerdesDfeConfig
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_DFE_MODE                    dfeMode
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    dfeMode = dfeMode;
#else

    Avago_serdes_dfe_tune_t  dfe_state;
    unsigned int sbus_addr;
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    unsigned int phySerdesNum;
    unsigned int slice;
    MCD_U16      spicoData = 0xFFFF;
    MCD_CTLE_CALIBRATION_MODE_E calibrationMode;

    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES((MCD_U32)serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC((MCD_U32)serdesNum,phySerdesNum);

    sbus_addr = phySerdesNum + 1;

    /* Initialize the dfe_state struct with default values */
    mcdWrapperTuneInit(pSerdesDev, &dfe_state);
    MCD_CHECK_RET_CODE(pSerdesDev);

    switch (dfeMode)
    {
        case MCD_DFE_STOP_ADAPTIVE:
            if (pDev->serdesStatus.stopAdaptiveFlag[serdesNum] == MCD_TRUE) {
                return MCD_OK;
            }
            dfe_state.tune_mode = AVAGO_DFE_STOP_ADAPTIVE;
            pDev->serdesStatus.stopAdaptiveFlag[serdesNum] = MCD_TRUE;
            break;
        case MCD_DFE_START_ADAPTIVE:
            dfe_state.tune_mode = AVAGO_DFE_START_ADAPTIVE;
            pDev->serdesStatus.stopAdaptiveFlag[serdesNum] = MCD_FALSE;
            /* Enable TAP1 before pCal */
            spicoData = 0x5B08;
            /*ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x26, 0x5B08, NULL));*/
            break;
        case MCD_DFE_ICAL:
            dfe_state.tune_mode = AVAGO_DFE_ICAL;
            /* Disable TAP1 before iCal */
            spicoData = 0x5B00;
            /*ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x26, 0x5B00, NULL));*/
            break;
        case MCD_DFE_PCAL:
            dfe_state.tune_mode = AVAGO_DFE_PCAL;
            /* Enable TAP1 before pCal */
            spicoData = 0x5B08;
            /*ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x26, 0x5B08, NULL));*/
            break;
        case MCD_DFE_ICAL_VSR:

            calibrationMode = pDev->calibrationCfg[serdesNum % 8].calibrationMode;

            /* If the calibration mode is optical-bypass and Serdes is in the Line Side - VSR/iCAL is not allowed */
            if ( (calibrationMode == MCD_OPTICAL_CTLE_BYPASS_CALIBRATION) && (serdesNum < MCD_HOST_SIDE_START_SERDES_NUMBER) ) {
                /* avoid running VSR on Optical modules and 1G port speed */
                ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0xA, 0xF, NULL));
                return MCD_OK;
            }
            dfe_state.dfe_disable = MCD_TRUE;
            dfe_state.tune_mode   = AVAGO_DFE_ICAL;
            spicoData = 0x5B01;
            /* ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0xA, 0x41, NULL)); */
            break;
        default:
            return MCD_STATUS_BAD_PARAM;
    }

    if (spicoData != 0xFFFF) {
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x26, spicoData, NULL));
    }
    mcdSerdesAccessLock(pDev);
    /* Run/Halt DFE tuning on a serdes based on dfe_tune_mode */
    if (pDev->haAccessDisable == MCD_FALSE)
    {
        mcdWrapperTune(pSerdesDev, sbus_addr, &dfe_state);
    }
    mcdSerdesAccessUnlock(pDev);
    MCD_CHECK_RET_CODE(pSerdesDev);

#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesRxAutoTuneStatusShort
*
* DESCRIPTION:
*       Per SERDES check the Rx training status
*       This function is necessary for 802.3ap functionality
*
* INPUTS:
*       pDev
*       serdesNum - physical serdes number
*
* OUTPUTS:
*       rxStatus - status of Rx-Training
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
#ifndef ASIC_SIMULATION
MCD_STATUS mcdSerdesRxAutoTuneStatusShort
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_AUTO_TUNE_STATUS            *rxStatus
)
{
    MCD_U16/*int*/ data;

    /* MCD_TUNE_FAIL is relevant only for MCD_DFE_ICAL mode */
    *rxStatus = MCD_TUNE_FAIL;

    /* get DFE status */
    /*ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x126, ((0 << 12) | (0xB << 8)),&data));*/
    ATTEMPT(mcdSerdesDfeStatusGet(pDev, serdesNum, &data));
    /*MCD_DBG_ERROR("SERDES %d TuneStatus %x\n", serdesNum, data);*/
    if ((data == 0xC0) || (data ==  0x80))
    {
        *rxStatus = MCD_TUNE_PASS;
    }
    else if (data == 0x0)
    {
        *rxStatus = MCD_TUNE_RESET;
    }
    else if (data & 0x200)
    {
        *rxStatus = MCD_TUNE_INTERRUPTED;
    }
    else if((data & 0x33) != 0)
    {
        *rxStatus = MCD_TUNE_NOT_COMPLITED;
    }


    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesDataVoltageOffsetCheck
*
* DESCRIPTION:
*       Per SERDES check Data Voltage Offeset
*
* INPUTS:
*       pDev
*       serdesNum - physical serdes number
*
* OUTPUTS:
*       stateIsOk - MCD_TRUE - data voltage offset OK, MCD_FALSE - out of valid bounds
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesDataVoltageOffsetCheck
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_BOOL                        *stateIsOk
)
{
    int  i;
    int  data;

    for (i = 0; (i < 8); i++)
    {
        /* read DVOS[i] */
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x126, (0x1000 + (i * 0x100)), &data));
        if ((data > 150) || (data < 55))
        {
            *stateIsOk = MCD_FALSE;
            return MCD_OK;
        }
    }
    *stateIsOk = MCD_TRUE;
    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesRxAutoTuneStatusGet
*
* DESCRIPTION:
*       Per SERDES check the Rx training status
*
* INPUTS:
*       pDev
*       serdesNum - physical serdes number
*
* OUTPUTS:
*       rxStatus - status of Rx-Training
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesRxAutoTuneStatusGet
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_AUTO_TUNE_STATUS            *rxStatus
)
{
    MCD_U16/*int*/ data;

    /* set default to be fail */
    *rxStatus = MCD_TUNE_FAIL;

    /* get DFE status */
   /* ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x126, ((0 << 12) | (0xB << 8)),&data));*/
    ATTEMPT(mcdSerdesDfeStatusGet(pDev, serdesNum, &data));
    /*MCD_DBG_ERROR("SERDES %d TuneStatus %x\n", serdesNum, data);*/
/* DFE Status has the following bits:
   0 - ICal in progress
   1 - PCal in progress
   4 - ICal pending, signal off
   5 - PCal pending, signal off
   6 - adaptive PCal enabled
   7 - Input Offset correction done
   9 - Electrical idle condition detected during calibration:
       - 1 signal was down or still down,
       - 0 signal OK */

    if((data == 0x80) || (data == 0xC0))
    {
        *rxStatus = MCD_TUNE_PASS;
    }
    else if((data & 0x33) != 0)
    {
        /* tuning not done if one of ICal/PCal in progress or pending */
        *rxStatus = MCD_TUNE_NOT_COMPLITED;
    }

    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesDfeStatusGet
*
* DESCRIPTION:
*       Per SERDES check the DFE status
*
* INPUTS:
*       pDev
*       serdesNum - physical serdes number
*
* OUTPUTS:
*       dfeStatusBitmapPtr - status of DFE as in HW
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesDfeStatusGet
(
    MCD_DEV_PTR               pDev,
    MCD_U8                    serdesNum,
    MCD_U16/*MCD_DFE_STATUS*/            *dfeStatusBitmapPtr
)
{
    int data;

    /* get DFE status */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x126, ((0 << 12) | (0xB << 8)),&data));

    *dfeStatusBitmapPtr = (MCD_U16/*MCD_DFE_STATUS*/)data;

    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesTxAutoTuneStatusShort
*
* DESCRIPTION:
*       Per SERDES check the Tx training status
*       This function is necessary for 802.3ap functionality
*
* INPUTS:
*        pDev
*       serdesNum - physical serdes number
*
* OUTPUTS:
*       txStatus - status of Tx-Training
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesTxAutoTuneStatusShort
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_AUTO_TUNE_STATUS            *txStatus
)
{
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    unsigned int sbus_addr;
    MCD_U32 data;
    MCD_U32 slice, phySerdesNum;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES((MCD_U32)serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC((MCD_U32)serdesNum,phySerdesNum);
    sbus_addr = phySerdesNum + 1;
    *txStatus = MCD_TUNE_NOT_COMPLITED;

    /* check PMD training status */
    data = mcdWrapperPMDStatus(pSerdesDev, sbus_addr);
    if (data == 0)
        *txStatus = MCD_TUNE_FAIL;
    else if (data == 0x1)
    {
        *txStatus = MCD_TUNE_PASS;
        /* Enable TAP1 after pmd_train is completed */
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x26, 0x5B08, NULL));
    }
        else if (data == 0x2)
        *txStatus = MCD_TUNE_NOT_COMPLITED;
    return MCD_OK;
}
#endif /* ASIC_SIMULATION */
/*******************************************************************************
* mcdSerdesAutoTuneStatusShort
*
* DESCRIPTION:
*       Check the Serdes Rx or Tx training status
*
* INPUTS:
*       pDev
*       serdesNum - physical serdes number
*
* OUTPUTS:
*       rxStatus - Rx-Training status
*       txStatus - Tx-Training status
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesAutoTuneStatusShort
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_AUTO_TUNE_STATUS            *rxStatus,
    MCD_AUTO_TUNE_STATUS            *txStatus
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    if(rxStatus)
    {
        *rxStatus = MCD_TUNE_PASS;
    }
    if(txStatus)
    {
        *txStatus = MCD_TUNE_PASS;
    }
#else
    if ((NULL == rxStatus) && (NULL == txStatus))
    {
        return MCD_STATUS_BAD_PARAM;
    }

    if (rxStatus != NULL)
    {
        ATTEMPT(mcdSerdesRxAutoTuneStatusShort(pDev, serdesNum, rxStatus));
    }

    if (txStatus != NULL)
    {
        ATTEMPT(mcdSerdesTxAutoTuneStatusShort(pDev, serdesNum, txStatus));
    }
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesBypassCtleTuneStart
*
* DESCRIPTION:
*       Per SERDES running reduced iCal.
*
* INPUTS:
*       pDev
*       serdesNum  - physical serdes number
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesBypassCtleTuneStart
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_CTLE_CALIBRATION_MODE_E     calibrationMode,
    MCD_SERDES_SPEED                baudrate
)
{
#ifdef ASIC_SIMULATION
    serdesNum = serdesNum;
    calibrationMode = calibrationMode;

#else
    MCD_U16  data;
     switch (calibrationMode)
     {
     case MCD_OPTICAL_CTLE_BYPASS_CALIBRATION:
     case MCD_REDUCE_CALIBRATION:
         /* Avoid running iCAL or VSR if 1G speed HOWEVER...*/
         if  (baudrate == MCD_1_25G) {
             /* In rare cases, we see that 1G port will required some "Training kick" in order
                 to achieve "Link Up" when FIXED CTLE configuration is used.
                 This Kick will mostly issued in the driver during the port initialization.
                 This is the only Training value found resolving the Link down issue (Taken from EOM) */
             ATTEMPT(mcdSerdesSpicoInterrupt(pDev, (MCD_U32)serdesNum, 0xA, 0xF, NULL));
             return MCD_OK;
         }
         /* This is the native functionality before adding support for 1G */
         data = 0x781;
         break;
     /*case MCD_OPTICAL_CALIBRATION_WITHOUT_DFE:
         data = 0x7c1;
         break;*/
     default:
         MCD_DBG_ERROR("%s: calibration %d not supported\n", __func__, calibrationMode);
         return MCD_FAIL;
     }
        /* Disable TAP1 before iCal */
     ATTEMPT(mcdSerdesSpicoInterrupt(pDev, (MCD_U32)serdesNum, 0x26, 0x5B00, NULL));
     /* run reduced iCal skip bypass ctle values */
     ATTEMPT(mcdSerdesSpicoInterrupt(pDev, (MCD_U32)serdesNum, 0xA, data, NULL));
#endif

    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesAutoTuneStartExt
*
* DESCRIPTION:
*       Per SERDES control the TX training & Rx Training starting
*
* INPUTS:
*       pDev
*       serdesNum  - physical serdes number
*       rxTraining - Rx Training modes
*       txTraining - Tx Training modes
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesAutoTuneStartExt
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_RX_TRAINING_MODES           rxTraining,
    MCD_TX_TRAINING_MODES           txTraining
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    rxTraining = rxTraining;
    txTraining = txTraining;
#else
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    unsigned int sbus_addr;
    MCD_SER_DFE_TUNE_TYPE   dfe_state;
    MCD_SER_PMD_CONFIG_TYPE pmd_mode;
    MCD_BOOL signalDet = MCD_FALSE;
    unsigned int slice, phySerdesNum;
    MCD_U16      data = 0xFFFF;

    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES((MCD_U32)serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC((MCD_U32)serdesNum,phySerdesNum);

    sbus_addr = phySerdesNum + 1;


    if ((txTraining != MCD_IGNORE_TX_TRAINING) && (rxTraining != MCD_IGNORE_RX_TRAINING))
    {
        return MCD_STATUS_BAD_PARAM;
    }


    /* Initialize the dfe_state struct with default values */
    mcdWrapperTuneInit(pSerdesDev, &dfe_state);
    MCD_CHECK_RET_CODE(pSerdesDev);

    /* Initialize the pmd_mode */
    mcdWrapperPMDInit(pSerdesDev, &pmd_mode);

    switch(rxTraining)
    {
        case MCD_IGNORE_RX_TRAINING:
            break;
        case MCD_START_CONTINUE_ADAPTIVE_TUNING:
            /* start continues adaptive tuning */
            dfe_state.tune_mode = AVAGO_DFE_START_ADAPTIVE;
            /* Enable TAP1 before pCal */
            data = 0x5B08;
            /*ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x26, 0x5B08, NULL));*/
            break;
        case MCD_STOP_CONTINUE_ADAPTIVE_TUNING:
            /* stop continues adaptive tuning */
            dfe_state.tune_mode = AVAGO_DFE_STOP_ADAPTIVE;
            break;
        case MCD_ONE_SHOT_DFE_TUNING:
            dfe_state.tune_mode = AVAGO_DFE_ICAL;
            /* Disable TAP1 before iCal */
            data = 0x5B00;
            /*ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x26, 0x5B00, NULL));*/
            break;
        case MCD_DFE_VSR_TUNING:
            dfe_state.dfe_disable = MCD_TRUE;
            dfe_state.tune_mode = AVAGO_DFE_ICAL;
            /* Disable TAP1 before iCal */
            data = 0x5B01;
            /*ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x26, 0x5B00, NULL));*/
            break;
        default:
            return MCD_STATUS_NOT_SUPPORTED;
    }
    if (data != 0xFFFF) {
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x26, data, NULL));
    }
    if ((rxTraining != MCD_IGNORE_RX_TRAINING))
    {
        if (MCD_STOP_CONTINUE_ADAPTIVE_TUNING != rxTraining)
        {
            /* signal check - if currently no signal could be detected on the serdes, skippin the rx training */
            ATTEMPT(mcdSerdesSignalDetectGet(pDev, serdesNum, &signalDet));
        }
        else
        {
            /* ignore signal when stop adaptive tune */
            signalDet = MCD_TRUE;
        }

        if (signalDet == MCD_TRUE)
        {
            mcdSerdesAccessLock(pDev);
            /* Launches and halts DFE tuning procedures */
            if (pDev->haAccessDisable == MCD_FALSE)
            {
                mcdWrapperTune(pSerdesDev, sbus_addr, &dfe_state);
            }
            mcdSerdesAccessUnlock(pDev);
            MCD_CHECK_RET_CODE(pSerdesDev);
        }
        else
        {
            MCD_DBG_ERROR("Training can not be done when signal is not detected physicalSerdesNum %d \n", phySerdesNum);
        }
    }

    if (txTraining != MCD_IGNORE_TX_TRAINING)
    {
        pmd_mode.sbus_addr = sbus_addr;
        pmd_mode.disable_timeout = TRUE;
        pmd_mode.train_mode = (txTraining == MCD_START_TRAINING) ? AVAGO_PMD_TRAIN : AVAGO_PMD_BYPASS;

        /* disable TAP1 before iCal */
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x26, 0x5B00, NULL));

        /* change IF_Dwell_Shift to 0x1 */
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x26, 0x5C00, NULL));
        mcdSerdesAccessLock(pDev);
        /* Launches and halts PMD link training procedure */
        if (pDev->haAccessDisable == MCD_FALSE)
        {
            mcdWrapperPMDTraining(pSerdesDev, &pmd_mode);
        }
        mcdSerdesAccessUnlock(pDev);
        MCD_CHECK_RET_CODE1(pSerdesDev, phySerdesNum);
    }
#endif /* ASIC_SIMULATION */
    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesAutoTuneStartExtAp
*
* DESCRIPTION:
*       Per SERDES control the AP TX training & Rx Training starting
*
* INPUTS:
*       pDev
*       serdesNum  - physical serdes number
*       rxTraining - Rx Training modes
*       txTraining - Tx Training modes
*       laneSpeed  - serdes speed
*       laneNum    - lane number (in multilane port)
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
MCD_STATUS mcdSerdesAutoTuneStartExtAp
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_RX_TRAINING_MODES           rxTraining,
    MCD_TX_TRAINING_MODES           txTraining,
    MCD_U32                         laneSpeed,
    MCD_U32                         laneNum

)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    rxTraining = rxTraining;
    txTraining = txTraining;
    laneSpeed = laneSpeed;
    laneNum   = laneNum;
#else
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    unsigned int sbus_addr = serdesNum + 1;
    MCD_SER_DFE_TUNE_TYPE   dfe_state;
    MCD_SER_PMD_CONFIG_TYPE pmd_mode;
    MCD_BOOL signalDet = MCD_FALSE;

    if ((txTraining != MCD_IGNORE_TX_TRAINING) && (rxTraining != MCD_IGNORE_RX_TRAINING))
    {
        return MCD_STATUS_BAD_PARAM;
    }
   /* Initialize the dfe_state struct with default values */
    mcdWrapperTuneInit(pSerdesDev, &dfe_state);
    MCD_CHECK_RET_CODE(pSerdesDev);

    /* Initialize the pmd_mode */
    mcdWrapperPMDInit(pSerdesDev, &pmd_mode);

    switch(rxTraining)
    {
        case MCD_IGNORE_RX_TRAINING:
            break;
        case MCD_START_CONTINUE_ADAPTIVE_TUNING:
            /* start continues adaptive tuning */
            dfe_state.tune_mode = AVAGO_DFE_START_ADAPTIVE;
            break;
        case MCD_STOP_CONTINUE_ADAPTIVE_TUNING:
            /* stop continues adaptive tuning */
            dfe_state.tune_mode = AVAGO_DFE_STOP_ADAPTIVE;
            break;
        case MCD_ONE_SHOT_DFE_TUNING:
            dfe_state.tune_mode = AVAGO_DFE_ICAL;
            /* disable TAP1 before iCal */
            ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x26, 0x5B00, NULL));
            break;
        default:
            return MCD_STATUS_NOT_SUPPORTED;
    }

    if ((rxTraining != MCD_IGNORE_RX_TRAINING))
    {
        /* signal check - if currently no signal could be detected on the serdes, skippin the rx training */
        ATTEMPT(mcdSerdesSignalDetectGet(pDev, serdesNum, &signalDet));
        if (signalDet == MCD_TRUE)
        {
            mcdSerdesAccessLock(pDev);
            /* Launches and halts DFE tuning procedures */
            if (pDev->haAccessDisable == MCD_FALSE)
            {
                mcdWrapperTune(pSerdesDev, sbus_addr, &dfe_state);
            }
            mcdSerdesAccessUnlock(pDev);
            MCD_CHECK_RET_CODE(pSerdesDev);
        }
        else
        {
            MCD_DBG_ERROR("Training can not be done when signal is not detected\n");
        }
    }

    if (txTraining != MCD_IGNORE_TX_TRAINING)
    {
        pmd_mode.sbus_addr = sbus_addr;
        pmd_mode.disable_timeout = TRUE;
        pmd_mode.train_mode = (txTraining == MCD_START_TRAINING) ? AVAGO_PMD_TRAIN : AVAGO_PMD_BYPASS;

        /* change IF_Dwell_Shift to 0x1 */
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x26, 0x5C01, NULL));

        if (laneSpeed == MCD_25_78125G)
        {
            /*Set PMD PRBS Sequence  based on per lane*/
            ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x3D, (0x3000 | laneNum), NULL));
        }
        else
            /*Set PMD PRBS Sequence to default*/
            ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x3D, (0x3000 | 4), NULL));

        mcdSerdesAccessLock(pDev);
        /* Launches and halts PMD link training procedure */
        if (pDev->haAccessDisable == MCD_FALSE)
        {
            mcdWrapperPMDTraining(pSerdesDev, &pmd_mode);
        }
        mcdSerdesAccessUnlock(pDev);
        MCD_CHECK_RET_CODE1(pSerdesDev, serdesNum);
    }
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

/**
* @internal mcdSerdesRxCalibrationConfig function
* @endinternal
*
* @brief   Per SERDES, configs Rx paramter.
*
* @param[in] pDev           - pointer to device
* @param[in] serdesNum      - physical serdes number
* @param[in] baudRate       - baudRate enum value
*
* @retval MCD_OK            - on success
* @retval MCD_FAIL          - on error
*/
MCD_STATUS mcdSerdesRxCalibrationConfig
(
    MCD_DEV_PTR                     pDev,
    MCD_U16                         serdesLane,
    MCD_U32                         baudRate
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesLane = serdesLane;
    baudRate   = baudRate;
#else
    MCD_DBG_INFO("%s: calibration on %d serdesLane \n", __func__, serdesLane);
    if ((pDev->calibrationCfg[serdesLane & 7].calibrationMode == MCD_REDUCE_CALIBRATION)
        || (pDev->calibrationCfg[serdesLane & 7].calibrationMode == MCD_OPTICAL_CTLE_BYPASS_CALIBRATION))
    {
        /* The "Reduced" or "CTLE Fixed Calibration" for 1G port with Opticals module is required only on the Line Side.
            If the serdes is in the Host Side - doing standard VSR calibration */

        /* Doing changes in the last test, remove the baudrate query */
        if (serdesLane >= MCD_HOST_SIDE_START_SERDES_NUMBER)
        {
            if (baudRate == MCD_1_25G)
            {
                ATTEMPT(mcdSerdesDfeConfig(pDev,serdesLane, MCD_DFE_ICAL_VSR));
            }
            else
            {
                ATTEMPT(mcdSerdesDfeConfig(pDev,serdesLane, MCD_DFE_ICAL));
            }
        }
        else
        {
            ATTEMPT(mcdSerdesBypassCtleTuneStart(pDev, serdesLane, pDev->calibrationCfg[serdesLane & 7].calibrationMode, baudRate));
        }
    }
    else
    {
        if (baudRate == MCD_1_25G)
        {
            ATTEMPT(mcdSerdesDfeConfig(pDev, serdesLane, MCD_DFE_ICAL_VSR));
        }
        else
        {
            /* 6. Run Initial Calibration (a.k.a ICal and ONE_SHOT_DFE) */
            ATTEMPT(mcdSerdesDfeConfig(pDev, serdesLane, MCD_DFE_ICAL));
        }
    }
#endif /* ASIC_SIMULATION */
    return MCD_OK;
}

#endif /* MV_HWS_REDUCED_BUILD_EXT_CM3 */
/*******************************************************************************
* mcdSerdesAutoTuneStart
*
* DESCRIPTION:
*       Per SERDES control the TX training & Rx Training starting.
*       This function calls to the mcdSerdesAutoTuneStartExt, which includes
*       all the functional options.
*
* INPUTS:
*       pDev
*       serdesNum  - physical serdes number
*       rxTraining - Rx Training (true (AVAGO_DFE_ICAL) /false)
*       txTraining - Tx Training (true (AVAGO_PMD_TRAIN) /false)
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesAutoTuneStart
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_BOOL                        rxTraining,
    MCD_BOOL                        txTraining
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    rxTraining = rxTraining;
    txTraining = txTraining;
#else

    MCD_RX_TRAINING_MODES    rxMode;
    MCD_TX_TRAINING_MODES    txMode;

    if (txTraining && rxTraining)
    {
        return MCD_STATUS_BAD_PARAM;
    }

    /* for TRUE: set Single time iCal */
    rxMode = (rxTraining == MCD_TRUE) ? MCD_ONE_SHOT_DFE_TUNING : MCD_IGNORE_RX_TRAINING;

    txMode = (txTraining == MCD_TRUE) ? MCD_START_TRAINING : MCD_IGNORE_TX_TRAINING;

    ATTEMPT(mcdSerdesAutoTuneStartExt(pDev, serdesNum, rxMode, txMode));
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesRxAutoTuneStart
*
* DESCRIPTION:
*       Per SERDES control the Rx Training starting.
*
* INPUTS:
*       pDev
*       serdesNum - physical serdes number
*       rxTraining - Rx Training (true/false)
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesRxAutoTuneStart
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_BOOL                        rxTraining
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    rxTraining = rxTraining;
#else

    MCD_RX_TRAINING_MODES    rxMode;

    /* for TRUE: set Single time iCal */
    rxMode = (rxTraining == MCD_TRUE) ? MCD_ONE_SHOT_DFE_TUNING : MCD_IGNORE_RX_TRAINING;

    ATTEMPT(mcdSerdesAutoTuneStartExt(pDev, serdesNum, rxMode, MCD_IGNORE_TX_TRAINING));
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesTxAutoTuneStart
*
* DESCRIPTION:
*       Per SERDES control the TX training starting.
*
* INPUTS:
*       pDev
*       serdesNum - physical serdes number
*       txTraining - Tx Training (true/false)
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesTxAutoTuneStart
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_BOOL                        txTraining
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    txTraining = txTraining;
#else

    MCD_TX_TRAINING_MODES    txMode;

    /* for TRUE: set the AVAGO_PMD_TRAIN mode, for FALSE: set the AVAGO_PMD_BYPASS mode */
    txMode = (txTraining == MCD_TRUE) ? MCD_START_TRAINING : MCD_STOP_TRAINING;

    ATTEMPT(mcdSerdesAutoTuneStartExt(pDev, serdesNum, MCD_IGNORE_RX_TRAINING, txMode));
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesAutoTuneStatus
*
* DESCRIPTION:
*       Per SERDES check the Rx & Tx training status
* INPUTS:
*       pDev
*       serdesNum - physical serdes number
*
* OUTPUTS:
*       rxTraining - Rx Training (true/false)
*       txTraining - Tx Training (true/false)
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesAutoTuneStatus
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_AUTO_TUNE_STATUS            *rxStatus,
    MCD_AUTO_TUNE_STATUS            *txStatus
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    rxStatus = rxStatus;
    txStatus = txStatus;
#else
    MCD_U32 i;

    if ((NULL == rxStatus) && (NULL == txStatus))
    {
        return MCD_STATUS_BAD_PARAM;
    }

    if (rxStatus != NULL)
    {
        *rxStatus = MCD_TUNE_NOT_COMPLITED;

        for (i = 0; i < MCD_TRAINING_TIMEOUT; i++)
        {
            /* Delay in 1ms */
            mcdWrapperMsSleep(1);

            ATTEMPT(mcdSerdesRxAutoTuneStatusShort(pDev, serdesNum, rxStatus));
            if (*rxStatus == MCD_TUNE_PASS)
                break;
        }

        /* in case training failed or took too long/short */
        if ((*rxStatus != MCD_TUNE_PASS) || (i == MCD_TRAINING_TIMEOUT))
        {
            *rxStatus = MCD_TUNE_FAIL;
        }
    }

    if (txStatus != NULL)
    {
        *txStatus = MCD_TUNE_NOT_COMPLITED;

        for (i = 0; i < MCD_TRAINING_TIMEOUT; i++)
        {
            /* Delay in 1ms */
            mcdWrapperMsSleep(1);

            ATTEMPT(mcdSerdesTxAutoTuneStatusShort(pDev, serdesNum, txStatus));
            if (*txStatus == MCD_TUNE_PASS)
                break;
        }

        /* in case training failed or took too long/short */
        if ((*txStatus != MCD_TUNE_PASS) || (i == MCD_TRAINING_TIMEOUT))
        {
            *txStatus = MCD_TUNE_FAIL;
        }
    }
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesTxAutoTuneStop
*
* DESCRIPTION:
*       Per SERDES stop the TX training
*
* INPUTS:
*       pDev
*       serdesNum - physical serdes number
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesTxAutoTuneStop
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
#else
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    MCD_U8 phySerdesNum;
    unsigned int slice;
    unsigned int sbus_addr;
    MCD_SER_PMD_CONFIG_TYPE pmd_mode;

    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES((MCD_U32)serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC((MCD_U32)serdesNum,phySerdesNum);

    sbus_addr = phySerdesNum + 1;

    /* Initialize the pmd_mode */
    mcdWrapperPMDInit(pSerdesDev, &pmd_mode);

    pmd_mode.sbus_addr = sbus_addr;
    pmd_mode.disable_timeout = TRUE;
    pmd_mode.train_mode = AVAGO_PMD_RESTART;

    mcdSerdesAccessLock(pDev);
     /* stop the PMD link training procedure */
    if (pDev->haAccessDisable == MCD_FALSE)
    {
        mcdWrapperPMDTraining(pSerdesDev, &pmd_mode);
    }
    mcdSerdesAccessUnlock(pDev);
    MCD_CHECK_RET_CODE(pSerdesDev);
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}
/*******************************************************************************
* mcdSerdesManualCtleConfig
*
* DESCRIPTION:
*       Set the Serdes Manual CTLE config for DFE
*
* INPUTS:
*       pDev
*       serdesNum - physical serdes number
*       dcGain        - DC-Gain value        (rang: 0-255)
*       lowFrequency  - CTLE Low-Frequency   (rang: 0-15)
*       highFrequency - CTLE High-Frequency  (rang: 0-15)
*       bandWidth     - CTLE Band-width      (rang: 0-15)
*       loopBandwidth - CTLE Loop Band-width (rang: 0-15)
*       squelch       - Signal OK threshold  (rang: 0-310)
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesManualCtleConfig
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_U8                          dcGain,
    MCD_U8                          lowFrequency,
    MCD_U8                          highFrequency,
    MCD_U8                          bandWidth,
    MCD_U8                          loopBandwidth,
    MCD_U16                         squelch
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    dcGain = dcGain;
    lowFrequency = lowFrequency;
    highFrequency = highFrequency;
    bandWidth = bandWidth;
    loopBandwidth = loopBandwidth;
    squelch = squelch;
#else
    MCD_U32  ctleParam=0;
    MCD_U32  row;
    MCD_U32  column = 2;
    MCD_U32  data;


    if (squelch > 308)
    {
        return MCD_STATUS_BAD_PARAM;
    }

    for (row = 0; row <= 4; row++)
    {
        switch (row)
        {
            case 0:
                ctleParam = highFrequency;
                break;
            case 1:
                ctleParam = lowFrequency;
                break;
            case 2:
                ctleParam = dcGain;
                break;
            case 3:
                ctleParam = bandWidth;
                break;
            case 4:
                ctleParam = loopBandwidth;
                break;
        }

        data = ((column << 12) | (row << 8)) | ctleParam;

        /* Update the param values of DFE */
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x26, data, NULL));
    }
   /* formula to convert the milli-volt to fix value */
    squelch = (squelch < 68) ? 68 : squelch;
    squelch = (squelch - 68) / 16;

    /* Set the signal OK threshold on Serdes */
    ATTEMPT(mcdSerdesSignalOkCfg(pDev, serdesNum, squelch));
#endif /* ASIC_SIMULATION */
    MCD_DBG_INFO("mcdSerdesManualCtleConfig serdes %d squelch %d\n", serdesNum, squelch);
    return MCD_OK;
}


/*******************************************************************************
 * mcdSerdesSetTxMux
 *
 * DESCRIPTION:
 *       Configure serdes PCIE clock mux and  SD1 TX input mux
 *
 * INPUTS:
 *       pSerdesDev
 *       serdesNum - SERDES number
 *       baudRate  - baudRate enum value
 *       clockSourceSerdes - clock Source Serdes
 *       switchClk  - change the clock
 * OUTPUTS:
 *       None.
 *
 * RETURNS:
 *       0  - on success
 *       1  - on error
 *
 *******************************************************************************/
 MCD_STATUS mcdSerdesSetTxMux
 (
     MCD_DEV_PTR         pDev,
     MCD_U8              localSerdes,
     MCD_SERDES_SPEED    baudRate,
     MCD_U8              clockSourceSerdes,
     MCD_BOOL            switchClk
 )
 {
#ifdef ASIC_SIMULATION
     pDev         = pDev;
     localSerdes  = localSerdes;
     baudRate     = baudRate;
#else
     MCD_U8 txdivider;
     unsigned int        otherSideSerdes = (localSerdes < MCD_HOST_SIDE_START_SERDES_NUMBER)
         ?(localSerdes + MCD_HOST_SIDE_START_SERDES_NUMBER)
         :(localSerdes - MCD_HOST_SIDE_START_SERDES_NUMBER);
     /*MCD_U32 pllRxReady;*/
     unsigned int slice, phySerdesNum;
     unsigned int remotePhySerdes;
     /* get slice number */
     MCD_GET_SLICE_NUM_BY_SERDES((MCD_U32)localSerdes,slice);
     /* convert logic serdes number to physical serdes number */
     MCD_LOGIC_TO_PHYSICAL_SERDES_MAC((MCD_U32)localSerdes,phySerdesNum);
     MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(otherSideSerdes,remotePhySerdes);
     /* to prevent errors, and for future support of coupled mode */
     //clockSourceSerdes = phySerdesNum;

     /* localSerdes will use clock from otherSideSerdes */

     txdivider = mcdRetimerBaudRate2DividerValue[baudRate];

     /* Serdes Digital Reset not needed - done in mcdSerdesPowerCtrl */
     /* ATTEMPT(mcdSerdesResetImpl(pDev, otherSideSerdes, MCD_FALSE, MCD_TRUE, MCD_FALSE)); */

     /* Set external MUX */
     /* clock source */


     ATTEMPT(mcdHwSetPhyRegField32bit(
         pDev, DONT_CARE, MCD_SERDES_Miscellaneous(phySerdesNum) , 1, 2, (remotePhySerdes & 3)));
     /* opposite side data connection */
     ATTEMPT(mcdHwSetPhyRegField32bit(
         pDev, DONT_CARE, MCD_SERDES_EXTERNAL_CONFIGURATION_0(phySerdesNum), 3, 3, ((remotePhySerdes & 3) + 1)));


     #if 0
     mcdWrapperMsSleep(1);
     ATTEMPT(mcdHwGetPhyRegField32bit(
         pDev, DONT_CARE, MCD_SERDES_External_Status(phySerdesNum), 1, 1, &pllRxReady));
     if (pllRxReady == 0)
     {
         MCD_DBG_ERROR("mcdSerdesSetTxMux ERROR: PLL not ready serdes %d\n", remotePhySerdes);
     }
     #endif

     if (switchClk) {
         /*switch clock to local serdes */
         ATTEMPT(mcdSerdesSpicoInterrupt(pDev, localSerdes, 0x30,0x70, NULL));
         ATTEMPT(mcdSerdesSpicoInterrupt(pDev, localSerdes, 0x5,(0x1000 + txdivider), NULL));
     }

     /* TX PLL need time to change clock */
     /* No need to wait per lane here */
     /* In CM3 we will wait one time for all port-side */
     /*mcdWrapperMsSleep(100);*/
#endif /* ASIC_SIMULATION */
     return MCD_OK;
 }
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************************
 * mcdSerdesSetTxMuxLaneSteering
 *
 * DESCRIPTION:
 *       Configure serdes PCIE clock mux and  SD1 TX input mux
 *
 * INPUTS:
 *       pSerdesDev
 *       serdesNum - SERDES number
 *       laneOut
 *       baudRate  - baudRate enum value
 * OUTPUTS:
 *       None.
 *
 * RETURNS:
 *       0  - on success
 *       1  - on error
 *
 *******************************************************************************/
 MCD_STATUS mcdSerdesSetTxMuxLaneSteering
 (
     MCD_DEV_PTR         pDev,
     MCD_U8              localSerdes,
     MCD_U8              otherSideSerdes,
     MCD_SERDES_SPEED    baudRate
 )
 {
#ifdef ASIC_SIMULATION
     pDev         = pDev;
     localSerdes  = localSerdes;
     baudRate     = baudRate;
#else
     MCD_U8 txdivider;
     MCD_U32 pllRxReady;

     /* localSerdes will use clock from otherSideSerdes */

     txdivider = mcdRetimerBaudRate2DividerValue[baudRate];

     /* Serdes Digital Reset not needed - done in mcdSerdesPowerCtrl */
     /* ATTEMPT(mcdSerdesResetImpl(pDev, otherSideSerdes, MCD_FALSE, MCD_TRUE, MCD_FALSE)); */

     /* Set external MUX */
     MCD_DBG_INFO("mcdSerdesSetTxMuxLaneSteering write to serdes %d data %x\n",otherSideSerdes, (localSerdes & 3));

     ATTEMPT(mcdHwSetPhyRegField32bit(
         pDev, DONT_CARE, MCD_SERDES_Miscellaneous(otherSideSerdes) , 1, 2, (localSerdes & 3)));
     ATTEMPT(mcdHwSetPhyRegField32bit(
         pDev, DONT_CARE, MCD_SERDES_EXTERNAL_CONFIGURATION_0(otherSideSerdes), 3, 3, ((localSerdes & 3) + 1)));

     MCD_DBG_INFO("mcdSerdesSetTxMuxLaneSteering switch clock in serdes %d\n",localSerdes);
     mcdWrapperMsSleep(1);
     ATTEMPT(mcdHwGetPhyRegField32bit(
         pDev, DONT_CARE, MCD_SERDES_External_Status(otherSideSerdes), 1, 1, &pllRxReady));
     if (pllRxReady == 0)
     {
         MCD_DBG_ERROR("mcdSerdesSetTxMux ERROR: PLL not ready serdes %d\n", otherSideSerdes);
     }


     /*switch clock to local serdes */
     ATTEMPT(mcdSerdesSpicoInterrupt(pDev, localSerdes, 0x5,(0x1000 + txdivider), NULL));
     ATTEMPT(mcdSerdesSpicoInterrupt(pDev, localSerdes, 0x30,0x70, NULL));

     /* TX PLL need time to change clock */
     /* TX PLL need time to change clock */
     /* No need to wait per lane here */
     /* wait one time for all port-side */
     /*mcdWrapperMsSleep(100);*/

#endif /* ASIC_SIMULATION */
     return MCD_OK;
 }
#endif /*#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3*/
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************************
 * mcdSetSerdesLaneCfgForRetimerMode
 *
 * DESCRIPTION:
 *
 *
 * INPUTS:
 *       pSerdesDev
 *       serdesNum - SERDES number
 *       baudRate  - baudRate enum value
 * OUTPUTS:
 *       None.
 *
 * RETURNS:
 *       0  - on success
 *       1  - on error
 *
 *******************************************************************************/
MCD_STATUS mcdSetSerdesLaneCfgForRetimerMode
(
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 serdesLane,
     IN MCD_SERDES_SPEED baudRate       /*  Retimer mode from the list             */
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    pDev       = pDev;
    serdesLane = serdesLane;
    baudRate   = baudRate;
#else

/* This API is un used !!!!!!!!!!!! */
    /* avoid warnings */
    pDev       = pDev;
    serdesLane = serdesLane;
    baudRate   = baudRate;
#if 0
    MCD_U8        otherSideSerdes = (serdesLane < MCD_HOST_SIDE_START_SERDES_NUMBER)
        ?(serdesLane + MCD_HOST_SIDE_START_SERDES_NUMBER)
        :(serdesLane - MCD_HOST_SIDE_START_SERDES_NUMBER);


    /* 1. SerDes Power Cotrol with Tx disable */
    ATTEMPT(mcdSerdesPowerCtrl(pDev, serdesLane, MCD_TRUE, baudRate, MCD_FALSE));
    /* 2. CTLE config*/
    ATTEMPT(mcdSerdesManualCtleConfig (pDev, serdesLane,
                                       MCD_SERDES_DEFAILT_DC_GAIN, MCD_SERDES_DEFAILT_LOW_FREQUENCY,
                                       MCD_SERDES_DEFAILT_HIGH_FREQUENCY,MCD_SERDES_DEFAILT_BANDWIDTH,
                                       MCD_SERDES_DEFAILT_LOOP_BANDWIDTH,MCD_SERDES_DEFAILT_SQUELCH ));

    /* 3. Set SerDes Tx Mux  */
    ATTEMPT(mcdSerdesSetTxMux(pDev, serdesLane, baudRate));

    /* 4. Enable Tx output */
    ATTEMPT(mcdSerdesTxEnable(pDev, serdesLane, MCD_TRUE));

    /* 5. Run Initial Calibration (a.k.a ICal and ONE_SHOT_DFE) */
    ATTEMPT(mcdSerdesDfeConfig_noSignalCheck(pDev,serdesLane, MCD_DFE_ICAL));

    /* 6. Digtal un-reset - Temparary!!!!*/
    ATTEMPT(mcdSerdesResetImpl(pDev, otherSideSerdes, MCD_FALSE, MCD_FALSE, MCD_FALSE));

    MCD_DBG_INFO(
        "serdes %d signal_ok_live %d\n", serdesLane,
        avago_serdes_get_signal_ok_live(pDev->serdesDev, (serdesLane + 1)));

#endif
#endif
    return MCD_OK;
}
#endif
/*******************************************************************************
 * mcdSetSerdesLaneCfgForRetimerModePreSet
 *
 * DESCRIPTION:
 *
 *
 * INPUTS:
 *       pSerdesDev
 *       serdesNum - SERDES number
 *       baudRate  - baudRate enum value
 * OUTPUTS:
 *       None.
 *
 * RETURNS:
 *       0  - on success
 *       1  - on error
 *
 *******************************************************************************/
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
MCD_STATUS mcdSetSerdesLaneCfgForRetimerModePreSet
(
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 serdesLane,
     IN MCD_SERDES_SPEED baudRate       /*  Retimer mode from the list             */
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    pDev       = pDev;
    serdesLane = serdesLane;
    baudRate   = baudRate;
#else
    MCD_REF_CLK_SEL refClkSel = MCD_PRIMARY_CLK;
    MCD_REF_CLK_DIV refClkDiv = MCD_REF_CLK_NO_DIV;

    /* 1. SerDes Power Cotrol with Tx disable */
    /* mcdSerdesPowerCtrl for retimer mode leaves digital reset serdes state */
    ATTEMPT(mcdSerdesPowerCtrl(pDev, serdesLane, MCD_FALSE, baudRate, MCD_TRUE, (MCD_U32)refClkSel, (MCD_U32)refClkDiv));
    ATTEMPT(mcdSerdesPowerCtrl(pDev, serdesLane, MCD_TRUE, baudRate, MCD_TRUE, (MCD_U32)refClkSel, (MCD_U32)refClkDiv));
    /* 2. CTLE config is done inside mcdSerdesPowerCtrl*/
    MCD_DBG_INFO("mcdSetSerdesLaneCfgForRetimerModePreSet %d\n", serdesLane);
#endif
    return MCD_OK;
}
#endif /*#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3*/
/*******************************************************************************
 * mcdSetSerdesLaneCfgForRetimerModePostSet
 *
 * DESCRIPTION:
 *
 *
 * INPUTS:
 *       pSerdesDev
 *       serdesNum - SERDES number
 *       baudRate  - baudRate enum value
 *       clockSourceSerdes - clock Source Serdes
 *       sendIcal   - need to send Ical
 *       switchClk  - change the clock
 * OUTPUTS:
 *       None.
 *
 * RETURNS:
 *       0  - on success
 *       1  - on error
 *
 *******************************************************************************/
MCD_STATUS mcdSetSerdesLaneCfgForRetimerModePostSet
(
     IN MCD_DEV_PTR      pDev,
     IN MCD_U16          mdioPort,
     IN MCD_U16          serdesLane,
     IN MCD_SERDES_SPEED baudRate,       /*  Retimer mode from the list             */
     IN MCD_U16          clockSourceSerdes,
     IN MCD_BOOL         sendIcal,
     IN MCD_BOOL         switchClk

)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    pDev       = pDev;
    serdesLane = serdesLane;
    baudRate   = baudRate;
#else

    MCD_U8        otherSideSerdes = (serdesLane < MCD_HOST_SIDE_START_SERDES_NUMBER)
        ?(serdesLane + MCD_HOST_SIDE_START_SERDES_NUMBER)
        :(serdesLane - MCD_HOST_SIDE_START_SERDES_NUMBER);

    /* 3. Set SerDes Tx Mux  */
    ATTEMPT(mcdSerdesSetTxMux(pDev, serdesLane, baudRate, clockSourceSerdes, switchClk));

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
    /* 4. Enable Tx output */
    ATTEMPT(mcdSerdesTxEnable(pDev, serdesLane, MCD_TRUE));
#else
    if (serdesLane >= MCD_HOST_SIDE_START_SERDES_NUMBER) /* host side */
    {
        ATTEMPT(mcdSerdesTxEnable(pDev, serdesLane, MCD_TRUE));
    }
    else
    {
        ATTEMPT(mcdSerdesTxEnable(pDev, serdesLane, MCD_FALSE));
    }
#endif
    otherSideSerdes = 1;
    otherSideSerdes = otherSideSerdes;

    if (sendIcal == MCD_TRUE) {
        if ((pDev->calibrationCfg[mdioPort].calibrationMode == MCD_REDUCE_CALIBRATION) || (pDev->calibrationCfg[mdioPort].calibrationMode == MCD_OPTICAL_CTLE_BYPASS_CALIBRATION))
        {
             /* The "Reduced" or "CTLE Fixed Calibration" for 1G port with Opticals module is required only on the Line Side.
                If the serdes is in the Host Side - doing standard VSR calibration */

             /* Doing changes in the last test, remove the baudrate query */
             if (serdesLane >= MCD_HOST_SIDE_START_SERDES_NUMBER)  {
                 if (baudRate == MCD_1_25G) {
                     ATTEMPT(mcdSerdesDfeConfig(pDev,serdesLane, MCD_DFE_ICAL_VSR));
                  }else {
                     ATTEMPT(mcdSerdesDfeConfig(pDev,serdesLane, MCD_DFE_ICAL));
                  }
             }
             else {
                 ATTEMPT(mcdSerdesBypassCtleTuneStart(pDev, serdesLane, pDev->calibrationCfg[mdioPort].calibrationMode, baudRate));
             }
        }
        else
        {
            if (baudRate == MCD_1_25G)
            {
                ATTEMPT(mcdSerdesDfeConfig/*mcdSerdesDfeConfig_noSignalCheck*/(pDev,serdesLane, MCD_DFE_ICAL_VSR));
            }
            else
            {
                /* 6. Run Initial Calibration (a.k.a ICal and ONE_SHOT_DFE) */
                ATTEMPT(mcdSerdesDfeConfig/*mcdSerdesDfeConfig_noSignalCheck*/(pDev,serdesLane, MCD_DFE_ICAL));
            }
        }
    }
    MCD_DBG_INFO("mcdSetSerdesLaneCfgForRetimerModePostSet %d\n", serdesLane);
#endif
    return MCD_OK;
}

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
MCD_STATUS mcdSetRetimerMode
(
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 portNum,
     IN MCD_SERDES_SPEED baudRate
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    pDev     = pDev;
    portNum  = portNum;
    baudRate = baudRate;
#else
    MCD_U8 slice,chan;
    MCD_U8 serdesLs, serdesHs;

    slice = portNum / MCD_MAX_CHANNEL_NUM_PER_SLICE;
    chan = CHAN_IN_SLICE_NUM(portNum);

    serdesLs = MCD_SERDES_NUM(chan, slice);
    serdesHs = MCD_SERDES_NUM((chan + MCD_HOST_SIDE_START_SERDES_NUMBER),slice);

    ATTEMPT(mcdSetSerdesLaneCfgForRetimerMode(pDev, serdesHs, baudRate));
    ATTEMPT(mcdSetSerdesLaneCfgForRetimerMode(pDev, serdesLs, baudRate));

    /* calculates serdesHs and configures both inside */
     ATTEMPT(mcdSerdesSetRetimerMode(pDev, serdesLs, baudRate));
#endif
    return MCD_OK;
}
#endif /* MV_HWS_REDUCED_BUILD_EXT_CM3 */
/*******************************************************************************
* mcdSerdesManualCtleConfigGet
*
* DESCRIPTION:
*       Get the Serdes CTLE (RX) configurations
*
*
* INPUTS:
*       pDev
*       serdesNum - physical lane number
*
* OUTPUTS:
*       configParams - Ctle params structures:
*       dcGain         DC-Gain value        (rang: 0-255)
*       lowFrequency   CTLE Low-Frequency   (rang: 0-15)
*       highFrequency  CTLE High-Frequency  (rang: 0-15)
*       bandWidth      CTLE Band-width      (rang: 0-15)
*       loopBandwidth  CTLE Loop Band-width (rang: 0-15)
*       squelch        Signal OK threshold  (rang: 0-310)
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesManualCtleConfigGet
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_MAN_TUNE_CTLE_CONFIG_DATA   *configParams
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    mcdMemSet(configParams,0,sizeof(*configParams));
#else

    MCD_AUTO_TUNE_RESULTS    results;
    MCD_U8                   signalThreshold;

    ATTEMPT(mcdSerdesAutoTuneResult(pDev, serdesNum, &results));

    configParams->highFrequency = results.HF;
    configParams->lowFrequency = results.LF;
    configParams->dcGain = results.DC;
    configParams->bandWidth = results.BW;
    configParams->loopBandwidth = results.LB;

    /* Get the signal OK threshold on Serdes */
    ATTEMPT(mcdSerdesSignalOkThresholdGet(pDev, serdesNum, &signalThreshold));
    configParams->squelch = signalThreshold;

#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesShiftSamplePoint
*
* DESCRIPTION:
*       Shift Serdes sampling point earlier in time
*
* INPUTS:
*       pDev
*       serdesNum - physical serdes number
*       delay     - set the delay (0..31)
*
* OUTPUTS:
*       None
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesShiftSamplePoint
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_U32                         delay
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    delay = delay;
#else
    int y;
    int intValue1, intValue2;

    if (delay <= 14)
    {
        y = (15 - delay);
        intValue1 = y | (y << 4);
        intValue2 = 0;
    }
    else
    {
        y = (delay - 15);
        intValue1 = 0;
        intValue2 = (y | (y << 4)) << 8 | y | (y << 4);
    }

    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18, 0x402d, NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, intValue1, NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18, 0x402e, NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, intValue2, NULL));
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************************
* mcdSerdesArrayAutoTuneSet
*
* DESCRIPTION:
*       Set iCAL(CTLE and DFE) or pCAL(DFE) Auto Tuning on multiple Serdeses
*
* INPUTS:
*       pDev
*       serdesArr - collection of SERDESes to configure
*       numOfSerdes  - number of SERDESes to configure
*       trainingMode - for value 0: set iCAL mode,
*                      for value 1: set pCAL mode
*
* OUTPUTS:
*       None
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesArrayAutoTuneSet
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          *serdesArr,
    MCD_U8                          numOfSerdes,
    MCD_BOOL                        trainingMode
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    numOfSerdes  = numOfSerdes;
    trainingMode = trainingMode;
#else

    MCD_U32  i, k, j;
    MCD_U32  serdesArr_copy[MCD_MAX_SERDES_PER_PORT] = {0};
    MCD_U32  passCounter = 0;
    MCD_U32  numOfActiveSerdes = 0;
    MCD_BOOL signalDet = MCD_FALSE;
    MCD_AUTO_TUNE_STATUS  rxStatus = MCD_TUNE_PASS; /* KW warning fix */
    MCD_DFE_MODE dfeMode;

    /* copy the original Serdes array for saving the data */
    for (j=0; j < numOfSerdes; j++)
        serdesArr_copy[j] =  serdesArr[j];

    /* for iCAL data=0x1, for pCAL data=0x2 */
    dfeMode = (trainingMode) ? MCD_DFE_PCAL : MCD_DFE_ICAL;

    for (j=0; j < numOfSerdes; j++)
    {
        if (serdesArr_copy[j] == MCD_SKIP_SERDES) /* skip Serdes[j] if No Signal-Detect */
            continue;

        /* signal check - if currently no signal could be detected on the serdes, skippin the training */
        ATTEMPT(mcdSerdesSignalDetectGet(pDev, serdesArr_copy[j], &signalDet));
        if (signalDet == MCD_FALSE)
        {
            MCD_DBG_ERROR("Training can not be done when no signal is detected serdes %x\n", serdesArr_copy[j]);
            return MCD_STATUS_BAD_STATE;
        }

        numOfActiveSerdes++;

        /* run iCAL(CTLE and DFE) or pCAL(DFE) */
        ATTEMPT(mcdSerdesDfeConfig(pDev,serdesArr_copy[j],dfeMode));
    }

    if (numOfActiveSerdes == 0)
    {
        MCD_DBG_INFO("No need to run Training on Serdes\n");
        return MCD_OK;
    }
    for (k = 0; k < MCD_TRAINING_TIMEOUT; k++)
    {
        for (i=0; i < numOfSerdes; i++)
        {
            if (serdesArr_copy[i] == MCD_SKIP_SERDES) /* if Serdes pass then no need to check status on it */
                continue;

            /* check that training completed */
           ATTEMPT(mcdSerdesRxAutoTuneStatusShort(pDev, serdesArr_copy[i], &rxStatus));
           if (rxStatus == MCD_TUNE_PASS)
            {
                passCounter++;

                /* Stop traning if Timeout reached or if traning finished too fast */
                if ((k >= MCD_TRAINING_TIMEOUT-1) || (k < 7))
                {
                    /* stop the training */
                    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesArr_copy[i], 0xa, 0x0, NULL));
                    MCD_DBG_ERROR("Error: Training failed. Stopped training i = %d k=%d\n", i, k);
                    return MCD_STATUS_TIMEOUT;
                }
                serdesArr_copy[i] = MCD_SKIP_SERDES;
            }
            else if ((dfeMode == MCD_DFE_ICAL) && (rxStatus == MCD_TUNE_FAIL))
            {
                break;
            }
        }
        if((dfeMode == MCD_DFE_ICAL) && (rxStatus == MCD_TUNE_FAIL))
        {
            break;
        }

        /* when all Serdeses finish, then stop the Timeout loop */
        if (passCounter == numOfActiveSerdes)
            break;
        else{
            mcdWrapperMsSleep( 1); /* Delay of 1ms */
        }
    }
    if((dfeMode == MCD_DFE_ICAL) && (rxStatus == MCD_TUNE_FAIL))
    {
        for (j = 0; j< 3; j++)
        {
            for (k = 0; k < MCD_TRAINING_TIMEOUT; k++)
            {
                for (i=0; i < numOfSerdes; i++)
                {
                    if (serdesArr_copy[i] == MCD_SKIP_SERDES) /* if Serdes pass then no need to check status on it */
                        continue;

                    /* check that training completed */
                   ATTEMPT(mcdSerdesRxAutoTuneStatusShort(pDev, serdesArr_copy[i], &rxStatus));
                   if (rxStatus == MCD_TUNE_PASS)
                    {
                        passCounter++;

                        /* Stop traning if Timeout reached or if traning finished too fast */
                        if ((k >= MCD_TRAINING_TIMEOUT-1) || (k < 7))
                        {
                            /* stop the training */
                            ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesArr_copy[i], 0xa, 0x0, NULL));
                            MCD_DBG_ERROR("Error: Training failed. Stopped training i = %d k=%d\n", i, k);
                            return MCD_STATUS_TIMEOUT;
                        }
                        serdesArr_copy[i] = MCD_SKIP_SERDES;
                    }
                    else if(rxStatus == MCD_TUNE_FAIL) /* dfeMode == MCD_DFE_ICAL */
                    {
                        break;
                    }
                }
                if(rxStatus == MCD_TUNE_FAIL) /* dfeMode == MCD_DFE_ICAL */
                {
                    break;
                }

                /* when all Serdeses finish, then stop the Timeout loop */
                if (passCounter == numOfActiveSerdes)
                    break;
                else{
                    mcdWrapperMsSleep( 1); /* Delay of 1ms */
                }
            }
        }
    }
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesRxTune
*
* DESCRIPTION:
*       Serdes RX training (ONE_SHOT and PCal)
*
* INPUTS:
*       pDev
*       serdesNum -  SERDES number
*
* OUTPUTS:
*       None
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesRxTune
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum  = serdesNum;

#else
    MCD_U32 i;
    MCD_AUTO_TUNE_STATUS rxTuneStatus;

    for (i = 0; i < ICAL_TUNE_TIME_LIMIT; i++)
    {
        ATTEMPT(mcdSerdesRxAutoTuneStatusGet(pDev, serdesNum, &rxTuneStatus));
        if (rxTuneStatus == MCD_TUNE_NOT_COMPLITED)
        {
            mcdWrapperMsSleep(1);
            continue;
        }
        break;
    }

    if (i == ICAL_TUNE_TIME_LIMIT)
    {
        MCD_DBG_ERROR("mcdSerdesRxTune serdes %d; prev tune not completed\n", serdesNum);
        return MCD_FAIL;
    }

    /* Run Initial Calibration (a.k.a ICal and ONE_SHOT_DFE) */
    ATTEMPT(mcdSerdesAutoTuneStartExt(pDev,serdesNum, MCD_ONE_SHOT_DFE_TUNING, MCD_IGNORE_TX_TRAINING));

    for (i = 0; i < ICAL_TUNE_TIME_LIMIT; i++)
    {
        ATTEMPT(mcdSerdesRxAutoTuneStatusGet(pDev, serdesNum, &rxTuneStatus));
        if (rxTuneStatus == MCD_TUNE_NOT_COMPLITED)
        {
            mcdWrapperMsSleep(1);
            continue;
        }
        if (rxTuneStatus == MCD_TUNE_PASS)
        {
            break;
        }
        else
        {
            MCD_DBG_ERROR("mcdSerdesRxTune  serdes %d; tune failed\n", serdesNum);
            return MCD_FAIL;
        }
    }

    if (i == ICAL_TUNE_TIME_LIMIT)
    {
        MCD_DBG_ERROR("mcdSerdesRxTune  serdes %d; tune not completed\n", serdesNum);
        return MCD_FAIL;
    }

    /* use single PCal, adaptive cannot be used in CM3 FW because it may be
       crashed when signal OFF. Full reconfiguration of port need to be used after that. */
    ATTEMPT(mcdSerdesDfeConfig(pDev, serdesNum, MCD_DFE_PCAL));

#endif
    return MCD_OK;
}
/*******************************************************************************
* mcdSerdesEnhanceTune
*
* DESCRIPTION:
*       Set the ICAL with shifted sampling point to find best sampling point
*
* INPUTS:
*       pDev
*       serdesArr - collection of SERDESes to configure
*       numOfSerdes - number of SERDESes to configure
*       min_LF      - Minimum LF value that can be set on Serdes (0...15)
*       max_LF      - Maximum LF value that can be set on Serdes (0...15)
*
* OUTPUTS:
*       None
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesEnhanceTune
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                         *serdesArr,
    MCD_U8                          numOfSerdes,
    MCD_U8                          min_LF,
    MCD_U8                          max_LF
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    numOfSerdes = numOfSerdes;
    min_LF = min_LF;
    max_LF = max_LF;
#else

    unsigned int sbus_addr;
    MCD_U32  dly, eye;
    MCD_U32  sdDetect;
    MCD_U32  i, j, k;
    int      LF, GAIN;
    MCD_U32  static_delay[] = {0,2,4,6,8,10, 11, 13, 15}; /* these are currently best belay values */
    MCD_U32  best_dly[MCD_MAX_SERDES_NUMBER] = {0};
    MCD_U32  best_eye[MCD_MAX_SERDES_NUMBER] = {0};
    MCD_32   best_LF[MCD_MAX_SERDES_NUMBER]  = {0};
    int      LF1_Arr[MCD_MAX_SERDES_NUMBER]  = {0};
    int      LF2_Arr[MCD_MAX_SERDES_NUMBER]  = {0};
    int      DFEgain_Arr[MCD_MAX_SERDES_NUMBER]    = {0};
    MCD_U32  serdesArrValid[MCD_MAX_SERDES_NUMBER] = {0};
    MCD_U32 slice, phySerdesNum;

     MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES((MCD_U32)serdesArr[0],slice);


#ifdef TUNE_EXEC_TIME
    struct timeval tvalBefore, tvalAfter;
    gettimeofday (&tvalBefore, NULL);
#endif

    for (i=0; i < MCD_MAX_SERDES_NUMBER; i++)
    {
        best_eye[i] = 4;
    }
    if (numOfSerdes > MCD_MAX_SERDES_NUMBER)
    {
        MCD_DBG_ERROR("numOfSerdes %d is greater than MAX_AMCD_MAX_SERDES_NUMBER %d\n", numOfSerdes, MCD_MAX_SERDES_NUMBER);
        return MCD_STATUS_BAD_PARAM;
    }

    /* check CDR lock and Signal Detect on all Serdeses */
    for (i=0; i < numOfSerdes; i++)
    {
        /* convert logic serdes number to physical serdes number */
        MCD_LOGIC_TO_PHYSICAL_SERDES_MAC((MCD_U32)serdesArr[i],phySerdesNum);
        ATTEMPT(mcdHwGetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_External_Status(phySerdesNum) , 2, 1, &sdDetect));
        if (sdDetect != 0)
        {
            serdesArr[i] = MCD_SKIP_SERDES; /* change the Serdes number to mark this array's element as not relevant */
            continue;
        }

        /* set SamplePoint to default value (delay=0) */
        ATTEMPT(mcdSerdesShiftSamplePoint(pDev, phySerdesNum, static_delay[0]));
    }

    /* copy the original Serdes array for saving the data */
    for (k=0; k < numOfSerdes; k++)
        serdesArrValid[k] = serdesArr[k];

    /* run iCAL(CTLE and DFE) */
    ATTEMPT(mcdSerdesArrayAutoTuneSet(pDev, serdesArr, numOfSerdes, MCD_ICAL_TRAINING_MODE));

    /* save the LF value of all Serdeses */
    for (k=0; k < numOfSerdes; k++)
    {
        if (serdesArr[k] == MCD_SKIP_SERDES) /* No Signal-Detect on this Serdes */
            continue;

        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesArr[k], 0x126, ((2 << 12) | (1 << 8)), &LF));
        best_LF[k]=LF;
    }

    /* find the peak of the eye accoding to delay */
    for (i=0; ((i < (sizeof(static_delay)/sizeof(MCD_U32))) && (static_delay[i] <= max_LF)); i++)
    {
        dly = static_delay[i];
         for (k=0; k < numOfSerdes; k++)
        {
            if (serdesArr[k] == MCD_SKIP_SERDES) /* No Signal-Detect on this Serdes */
                continue;

            ATTEMPT(mcdSerdesShiftSamplePoint(pDev, serdesArr[k], dly));
        }

        /* trigger pCAL(DFE) on all relevant Serdeses */
        ATTEMPT(mcdSerdesArrayAutoTuneSet(pDev, serdesArr, numOfSerdes, MCD_PCAL_TRAINING_MODE));

        for (j=0; j < numOfSerdes; j++)
        {
            if (serdesArr[j] == MCD_SKIP_SERDES) /* No Signal-Detect on this Serdes */
                continue;
            MCD_LOGIC_TO_PHYSICAL_SERDES_MAC((MCD_U32)serdesArr[j],phySerdesNum);
            sbus_addr = phySerdesNum + 1;

            mcdSerdesAccessLock(pDev);
            /* get a simple eye metric in range [0..1000] */
            eye = mcdWrapperEyeGetSimpleMetric(pSerdesDev , sbus_addr);
            mcdSerdesAccessUnlock(pDev);
            MCD_CHECK_RET_CODE(pSerdesDev);

            ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesArr[j], 0x126, ((2 << 12) | (1 << 8)), &LF));

            if (eye > (best_eye[j] - MCD_EYE_TAP))
            {
                if (eye > best_eye[j])
                {
                    best_eye[j] = eye;
                }
                best_dly[j] = dly;

                if (LF >= best_LF[j])
                    best_LF[j] = LF;
            }
            MCD_DBG_ERROR("current_eye[%d]=%d dly=%d\n", j, eye, dly);

            if (best_eye[j] < MCD_MIN_EYE_SIZE)
            {
                MCD_DBG_ERROR("Error on Serdes %d: Eye is too small (size is %d). Training Failed\n", serdesArr[j], best_eye[j]);
                return MCD_FAIL;
            }
        }
    }

    for (k=0; k < numOfSerdes; k++)
    {
        if (serdesArr[k] == MCD_SKIP_SERDES) /* skip Serdes if the dly is the same as the best_dly */
            continue;

        ATTEMPT(mcdSerdesShiftSamplePoint(pDev, serdesArr[k], best_dly[k]));
    }

    /* run iCAL(CTLE and DFE) with best delay */
    ATTEMPT(mcdSerdesArrayAutoTuneSet(pDev, serdesArr, numOfSerdes, MCD_ICAL_TRAINING_MODE));

    for (k=0; k < numOfSerdes; k++)
    {
        /* read the LF value */
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesArrValid[k], 0x126, ((2 << 12) | (1 << 8)), &LF1_Arr[k]));
    }

    /* run iCAL(CTLE and DFE) with best delay */
    ATTEMPT(mcdSerdesArrayAutoTuneSet(pDev, serdesArr, numOfSerdes, MCD_ICAL_TRAINING_MODE));

    for (k=0; k < numOfSerdes; k++)
    {
        /* read again the LF value after run the iCAL */
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesArrValid[k], 0x126, ((2 << 12) | (1 << 8)), &LF2_Arr[k]));

        /* read the DFE gain */
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesArrValid[k], 0x126, ((3 << 12) | (0 << 8)), &DFEgain_Arr[k]));

        LF = (LF1_Arr[k] + LF2_Arr[k])/2; /* take the avarge from two tunning values */
        LF = (LF < min_LF) ? min_LF : LF;
        LF = (LF > max_LF) ? max_LF : LF;

        /* write the selected LF value back to Serdes */
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesArrValid[k], 0x26, ((2 << 12) | (1 << 8) | LF), NULL));

        GAIN = (DFEgain_Arr[k] > 1) ? (DFEgain_Arr[k]-1) : DFEgain_Arr[k];
        /* write the selected GAIN value back to Serdes */
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesArrValid[k], 0x26, ((3 << 12) | (0 << 8) | GAIN), NULL));

        MCD_DBG_ERROR("Serdes %d: setting best_dly=%d best_eye=%d LF=%d GAIN=%d\n", serdesArrValid[k], best_dly[k], best_eye[k], LF, GAIN);

        /* run  pCAL(DFE) */
        ATTEMPT(mcdSerdesDfeConfig(pDev,serdesArrValid[k],MCD_DFE_PCAL));
    }


#ifdef TUNE_EXEC_TIME
    gettimeofday (&tvalAfter, NULL);
    printf("mcdSerdesEnhanceTune Time in microseconds: %ld microseconds\n", ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
                                                        +tvalAfter.tv_usec) - tvalBefore.tv_usec);
#endif /* TUNE_EXEC_TIME */

#endif /* ASIC_SIMULATION */

    return MCD_OK;
}


/*******************************************************************************
* mcdSerdesEnhanceTuneLite
*
* DESCRIPTION:
*       Set the PCAL with shifted sampling point to find best sampling point
*       This API runs only for AP port after linkUp indication and before running
*       the Rx-Training Adative pCal
*
* INPUTS:
*       pDev    - system device number
*       serdesArr - collection of SERDESes to configure
*       numOfSerdes - number of SERDESes to configure
*       serdesSpeed - speed of serdes
*       min_dly     - Minimum delay_cal value:
*                     - for Serdes speed 10G (25...28)
*                     - for Serdes speed 25G (15...19)
*       max_dly     - Maximum delay_cal value:
*                     - for Serdes speed 10G (30)
*                     - for Serdes speed 25G (21)
*
* OUTPUTS:
*       None
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesEnhanceTuneLite
(
    MCD_DEV_PTR       pDev,
    MCD_U8      *serdesArr,
    MCD_U8     numOfSerdes,
    MCD_SERDES_SPEED    serdesSpeed,
    MCD_U8                   min_dly,
    MCD_U8                   max_dly
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    numOfSerdes = numOfSerdes;
    min_dly = min_dly;
    max_dly = max_dly;
#else

    unsigned int sbus_addr;
    MCD_U32  dly, eye;
    MCD_AUTO_TUNE_STATUS  sdDetect;
    MCD_U32  i, j, k;
    MCD_U32  best_dly[MCD_MAX_SERDES_PER_PORT] = {0};
    MCD_U32  best_eye[MCD_MAX_SERDES_PER_PORT] = {0};
    MCD_U32 *currentDelayPtr;
    MCD_U32 currentDelaySize;
    MCD_U32 dwell;
    MCD_U32 slice, phySerdesNum;

    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES((MCD_U32)serdesArr[0],slice);


    if (numOfSerdes > MCD_MAX_SERDES_PER_PORT)
    {
        MCD_DBG_ERROR("numOfSerdes %d is greater than MCD_MAX_SERDES_PER_PORT %d\n", numOfSerdes, 4);
        return MCD_FAIL;
    }

    for (i=0; i < numOfSerdes; i++)
    {
        best_eye[i] = 4;
    }

    /* define dwell value */
    if (mcdBaudRate2DwellTimeValue[serdesSpeed] != NA_VALUE)
    {
        dwell = mcdBaudRate2DwellTimeValue[serdesSpeed];
    }
    else
    {
        dwell = 11;
    }

    if (serdesSpeed >= MCD_20_625G)
    {
        currentDelayPtr = mcd_static_delay_25G;
        currentDelaySize = sizeof(mcd_static_delay_25G)/sizeof(MCD_U32);
    }
    else
    {
        currentDelayPtr = mcd_static_delay_10G;
        currentDelaySize = sizeof(mcd_static_delay_10G)/sizeof(MCD_U32);
    }

    for (i=0; i < numOfSerdes; i++)
    {
        sbus_addr = serdesArr[i]+1;

        /* check CDR lock and Signal Detect on Serdes */
        ATTEMPT(mcdSerdesRxSignalCheck(pDev, serdesArr[i], &sdDetect));
        if (sdDetect == MCD_TUNE_NOT_READY)
        {
            serdesArr[i] = MCD_SKIP_SERDES; /* change the Serdes number to mark this array's element as not relevant */
            continue;
        }

        /* select DFE tuning dwell time */
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesArr[i], 0x18, 0x7, NULL));
        /* big register write LSB */
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesArr[i], 0x19, 1 << dwell, NULL));
        /* big register write MSB */
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesArr[i], 0x19, 0, NULL));

    }

    /* find the peak of the eye according to delay */
    for (i=0; i < currentDelaySize; i++)
    {
        dly = currentDelayPtr[i];

        if(dly >= min_dly && dly <= max_dly)
        {

            for (k=0; k < numOfSerdes; k++)
            {
                if (serdesArr[k] == MCD_SKIP_SERDES) /* No Signal-Detect on this Serdes */
                    continue;
                ATTEMPT(mcdSerdesShiftSamplePoint(pDev, serdesArr[k], dly));
            }

            /* trigger pCAL(DFE) on all relevant Serdeses */
            ATTEMPT(mcdSerdesArrayAutoTuneSet(pDev, serdesArr, numOfSerdes, MCD_PCAL_TRAINING_MODE));

            for (j=0; j < numOfSerdes; j++)
            {
                if (serdesArr[j] == MCD_SKIP_SERDES) /* No Signal-Detect on this Serdes */
                    continue;
                /* convert logic serdes number to physical serdes number */
                MCD_LOGIC_TO_PHYSICAL_SERDES_MAC((MCD_U32)serdesArr[j],phySerdesNum);
                sbus_addr = phySerdesNum+1;

                mcdSerdesAccessLock(pDev);
                /* get a simple eye metric in range [0..1000] */
                eye = mcdWrapperEyeGetSimpleMetric(pSerdesDev , sbus_addr);
                mcdSerdesAccessUnlock(pDev);
                MCD_CHECK_RET_CODE(pSerdesDev);

                if (eye > (best_eye[j] + MCD_EYE_TAP))
                {
                    best_eye[j] = eye;
                    best_dly[j] = dly;
                }
                if (best_eye[j] < MCD_MIN_EYE_SIZE)
                {
                    MCD_DBG_ERROR("Error on Serdes %d: Eye is too small (size is %d). Training Failed\n", serdesArr[j], best_eye[j]);
                    return MCD_FAIL;
                }
            }
        }
    }

    for (k=0; k < numOfSerdes; k++)
    {
        if (serdesArr[k] == MCD_SKIP_SERDES) /* skip Serdes if the dly is the same as the best_dly */
            continue;
        ATTEMPT(mcdSerdesShiftSamplePoint(pDev, serdesArr[k], best_dly[k]));
    }
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}
#endif /* MV_HWS_REDUCED_BUILD_EXT_CM3 */

/*******************************************************************************
* mcdSerdesEnhanceTuneLitePhase1
*
* DESCRIPTION:
*       Set the PCAL with shifted sampling point to find best sampling point.
*       This API runs only for AP port after linkUp indication and before running
*       the Rx-Training Adative pCal.
*
* INPUTS:
*       pDev    - system device number
*       serdesArr - collection of SERDESes to configure
*       numOfSerdes - number of SERDESes to configure
*       serdesSpeed - speed of serdes
*       currentDelaySize - delays array size
*       currentDelayPtr  - delays array
*       inOutI   - iteration index between different phases
*       best_eye - best eyes array to update
*       best_dly - best delays array to update
*       subPhase - assist flag to know which code to execute in this sub-phase
*
* OUTPUTS:
*       inOutI   - iteration index between different phases
*       best_eye - best eyes array to update
*       best_dly - best delays array to update
*       subPhase - assist flag to know which code to execute in this sub-phase
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesEnhanceTuneLitePhase1
(
    MCD_DEV_PTR       pDev,
    MCD_U8      *serdesArr,
    MCD_U8     numOfSerdes,
    MCD_SERDES_SPEED     serdesSpeed,
    MCD_U8       currentDelaySize,
    MCD_U8       *currentDelayPtr,
    MCD_U8       *inOutI,
    MCD_U16      *best_eye,
    MCD_U8       *best_dly,
    MCD_U8       *subPhase,
    MCD_U8    min_dly,
    MCD_U8    max_dly
)
{

#ifdef ASIC_SIMULATION
    /* avoid warnings */
    numOfSerdes = numOfSerdes;
    currentDelaySize = currentDelaySize;
    currentDelayPtr  = currentDelayPtr;
    inOutI   = inOutI;
    best_eye = best_eye;
    best_dly = best_dly;
    subPhase = subPhase;
    serdesSpeed = serdesSpeed;
    min_dly = min_dly;
    max_dly = max_dly;
#else

    unsigned int sbus_addr;
    MCD_U8   dly;
    MCD_U16  eye;
    MCD_U8   i, k, j;
    MCD_U8   dwell;
    MCD_U8 slice, phySerdesNum;
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;

    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesArr[0],slice);

    if (numOfSerdes > MCD_MAX_SERDES_PER_PORT)
    {
        MCD_DBG_ERROR("numOfSerdes %d is greater than MCD_MAX_SERDES_PER_PORT %d\n", numOfSerdes, 4);
        return MCD_FAIL;
    }

    /* define dwell value */
    if (mcdBaudRate2DwellTimeValue[serdesSpeed] != NA_VALUE)
    {
        dwell = mcdBaudRate2DwellTimeValue[serdesSpeed];
    }
    else
    {
        dwell = 11;
    }

    /* find the peak of the eye according to delay */
    for (i=(*inOutI); i < currentDelaySize; i++)
    {
        if (*subPhase == 0)
        {
            dly = currentDelayPtr[i];
            if (dly >= min_dly && dly <= max_dly)
            {
                for (k = 0; k < numOfSerdes; k++)
                {
                    /* select DFE tuning dwell time */
                    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesArr[0]+k, 0x18, 0x7, NULL));
                    /* big register write LSB */
                    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesArr[0]+k, 0x19, 1 << dwell, NULL));
                    /* big register write MSB */
                    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesArr[0]+k, 0x19, 0, NULL));

                    ATTEMPT(mcdSerdesShiftSamplePoint(pDev, serdesArr[0]+k, dly));

                    ATTEMPT(mcdSerdesDfeConfig(pDev, serdesArr[0]+k, MCD_DFE_PCAL));
                }
            }

            *subPhase = 1;
            break;
        }
        else
        {
            for (j=0; j < numOfSerdes; j++)
            {
                dly = currentDelayPtr[i];
                MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesArr[0]+j,phySerdesNum);
                sbus_addr = phySerdesNum+1;

                mcdSerdesAccessLock(pDev);
                /* get a simple eye metric in range [0..1000] */
                eye = mcdWrapperEyeGetSimpleMetric(pSerdesDev , sbus_addr);
                mcdSerdesAccessUnlock(pDev);
                MCD_CHECK_RET_CODE(pSerdesDev);
                if (eye > (best_eye[j] + MCD_EYE_TAP))
                {
                    best_eye[j] = eye;
                    best_dly[j] = dly;
                }
                if (best_eye[j] < MCD_MIN_EYE_SIZE)
                {
                    MCD_DBG_ERROR("Error on Serdes %d: Eye is too small (size is %d). Training Failed\n", serdesArr[0]+j, best_eye[j]);
                    return MCD_FAIL;
                }
            }

            *subPhase = 0;
        }
    }

    if (i < currentDelaySize)
    {
        (*inOutI) = i;
    }
    else
    {
        if ((*subPhase) == 0)
        {
            (*inOutI) = 0xFF;
        }
    }
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesEnhanceTuneLitePhase2
*
* DESCRIPTION:
*       Set shift sample point to with the best delay_cal value.
*       This API runs only for AP port after linkUp indication and before running
*       the Rx-Training Adative pCal
*
* INPUTS:
*       pDev    - system device number
*       serdesArr - collection of SERDESes to configure
*       numOfSerdes - number of SERDESes to configure
*       best_dly    - best delay to set on serdes
*
* OUTPUTS:
*       None
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesEnhanceTuneLitePhase2
(
    MCD_DEV_PTR    pDev,
    MCD_U8      *serdesArr,
    MCD_U8     numOfSerdes,
    MCD_U8       *best_dly
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    numOfSerdes = numOfSerdes;
    best_dly    = best_dly;
#else
    MCD_U8 k;

    for (k=0; k < numOfSerdes; k++)
    {
        ATTEMPT(mcdSerdesShiftSamplePoint(pDev, serdesArr[0]+k, best_dly[k]));
    }
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesDefaultMinMaxDlyGet
*
* DESCRIPTION:
*       This function returns the default minimum and maximum delay
*       values according to the given port mode
*
* INPUTS:
*       laneSpeed   - mode type of port
*
* OUTPUTS:
*       mib_dly_ptr     - default minimum delay value for the port mode
*       max_dly_ptr     - default maximum delay value for the port mode
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************//*******************************************************************************
* mcdSerdesDefaultMinMaxDlyGet
*
* DESCRIPTION:
*       This function returns the default minimum and maximum delay
*       values according to the given port mode
*
* INPUTS:
*       laneSpeed   - mode type of port
*
* OUTPUTS:
*       mib_dly_ptr     - default minimum delay value for the port mode
*       max_dly_ptr     - default maximum delay value for the port mode
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesDefaultMinMaxDlyGet
(
    MCD_SERDES_SPEED         laneSpeed,
    MCD_U8              *min_dly_ptr,
    MCD_U8              *max_dly_ptr
)
{
    if (min_dly_ptr == NULL || max_dly_ptr == NULL)
    {
        MCD_DBG_ERROR(" dly_ptr is NULL\n");
        return MCD_FAIL;
    }


    if ( laneSpeed > MCD_10_9375G )
    {
        *min_dly_ptr = 15;
        *max_dly_ptr = 21;
    }
    else
    {
        *min_dly_ptr = 25;
        *max_dly_ptr = 30;
    }

    return  MCD_OK;
}
/*******************************************************************************
* mcdSerdesSignalOkCfg
*
* DESCRIPTION:
*       Set the signal OK threshold on Serdes
*
* INPUTS:
*       pDev
*       serdesNum - physical serdes number
*       signalThreshold - Signal OK threshold (0-15)
*
* OUTPUTS:
*       None
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesSignalOkCfg
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_U8                          signalThreshold
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    signalThreshold = signalThreshold;
#else

    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    unsigned int slice;
    unsigned int phySerdesNum;
    unsigned int sbus_addr;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC((MCD_U32)serdesNum,phySerdesNum);
    sbus_addr = phySerdesNum + 1;
    mcdSerdesAccessLock(pDev);
    if (pDev->haAccessDisable == MCD_FALSE)
    {
        mcdWrapperInitSignalOk(pSerdesDev, sbus_addr, signalThreshold);
    }
    mcdSerdesAccessUnlock(pDev);

    MCD_CHECK_RET_CODE(pSerdesDev);
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesSignalOkThresholdGet
*
* DESCRIPTION:
*       Get the signal OK threshold on Serdes
*
* INPUTS:
*       pDev
*       serdesNum - physical serdes number
*
* OUTPUTS:
*       signalThreshold - Signal OK threshold (0-15)
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesSignalOkThresholdGet
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_U8                          *signalThreshold
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
     serdesNum = serdesNum;
    *signalThreshold = 0;
#else
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    unsigned int sbus_addr;
    unsigned int slice, phySerdesNum;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES((MCD_U32)serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC((MCD_U32)serdesNum,phySerdesNum);

    sbus_addr = phySerdesNum + 1;


    mcdSerdesAccessLock(pDev);
    *signalThreshold = mcdWrapperGetSignalOk(pSerdesDev, sbus_addr);
    mcdSerdesAccessUnlock(pDev);

    MCD_CHECK_RET_CODE(pSerdesDev);
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
#ifdef AAPL_ENABLE_EYE_MEASUREMENT
/*******************************************************************************
* mcdSerdesEyeGetExt
*
* DESCRIPTION:
*       Per SERDES return the adapted tuning results
*       Can be run after create port.
*
* INPUTS:
*        pSerdesDev
*       eye_inputPtr - pointer to input parameters structure
*
* OUTPUTS:
*       eye_resultsPtr - pointer to results structure
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesEyeGetExt
(
    IN MCD_DEV_PTR                          pDev,
    IN MCD_U16                              sAddr,
    IN MCD_SERDES_EYE_GET_INPUT             *eye_inputPtr,
    OUT MCD_SERDES_EYE_GET_RESULT           *eye_resultsPtr
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    sAddr = sAddr;
#else
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;

    MCD_SER_EYE_CONFIG_TYPE *configp;
    MCD_SER_EYE_DATA_TYPE *datap;
    unsigned int slice, phySerdesNum;
    MCD_U32     serdesNum = sAddr - 1, counter;
    MCD_BOOL    adaptiveIsOn = MCD_FALSE;
    MCD_AUTO_TUNE_STATUS rxStatus;

    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES((MCD_U32)serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC((MCD_U32)serdesNum,phySerdesNum);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MCD_SERDES_LANE_COUNT))
    {
        MCD_DBG_ERROR("mcdSerdesGetEyeExt: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MCD_FAIL;
    }
    configp = mcdWrapperEyeAllocConfig(pSerdesDev);
    if (!configp)
    {
        MCD_DBG_ERROR("mcdSerdesGetEyeExt: Invalid configp:0x%08X \n", configp);
        return MCD_FAIL;

    }
    configp->ec_min_dwell_bits = (bigint)eye_inputPtr->min_dwell_bits;
    configp->ec_max_dwell_bits = (bigint)eye_inputPtr->max_dwell_bits;

    datap = mcdWrapperEyeAllocDataSt( pSerdesDev);

    if (!datap)
    {
        mcdWrapperEyeFreeConfig(pSerdesDev,configp);
        MCD_DBG_ERROR("mcdSerdesGetEyeExt: Invalid datap:0x%08X \n", datap);
        return MCD_FAIL;
    }

    if(mcdSerdesAdaptiveStatusGet(pDev,serdesNum, &rxStatus)!= MCD_OK)
    {
        mcdWrapperEyeFreeDataSt(pSerdesDev,datap);
        mcdWrapperEyeFreeConfig(pSerdesDev,configp);

        MCD_DBG_ERROR("mcdSerdesAdaptiveStatusGet failed at %s:%u\n",__FUNCTION__,__LINE__);
        return MCD_FAIL;
    }
    else
    {
        if (rxStatus != MCD_TUNE_PASS) { /* adaptive pcal is running */
            adaptiveIsOn = MCD_TRUE;
            ATTEMPT(mcdSerdesDfeConfig(pDev,serdesNum,MCD_DFE_STOP_ADAPTIVE));
            counter = 0;
            while(rxStatus != MCD_TUNE_PASS)
            {
                mcdSerdesAdaptiveStatusGet(pDev,serdesNum, &rxStatus);
                mcdWrapperMsSleep(20);
                counter++;
                if (counter> 50) {
                    mcdWrapperEyeFreeDataSt(pSerdesDev,datap);
                    mcdWrapperEyeFreeConfig(pSerdesDev,configp);

                    MCD_DBG_ERROR("mcdSerdesDfeConfig stop adaptive failed at %s:%u\n",__FUNCTION__,__LINE__);
                    return MCD_FAIL;
                }
            }
        }
    }

    mcdSerdesAccessLock(pDev);
    if(mcdWrapperGetEye( pSerdesDev, phySerdesNum+1, configp, datap) != MCD_OK)
    {
        mcdSerdesAccessUnlock(pDev);
        mcdWrapperEyeFreeDataSt(pSerdesDev,datap);
        mcdWrapperEyeFreeConfig(pSerdesDev,configp);

        MCD_DBG_ERROR("ATTEMPT failed at %s:%u\n",__FUNCTION__,__LINE__);
        return MCD_FAIL;
    }
    mcdSerdesAccessUnlock(pDev);
    if (adaptiveIsOn == MCD_TRUE)
    {   /* need to start adaptive again after reading the eye*/
        ATTEMPT(mcdSerdesDfeConfig(pDev,serdesNum,MCD_DFE_START_ADAPTIVE));
    }

    eye_resultsPtr->matrixPtr = mcdWrapperEyePlotFormat(datap);
    eye_resultsPtr->x_points = datap->ed_x_points;
    eye_resultsPtr->y_points = datap->ed_y_points;
    eye_resultsPtr->height_mv = datap->ed_height_mV;
    eye_resultsPtr->width_mui = datap->ed_width_mUI;
    eye_resultsPtr->vbtcPtr = mcdWrapperEyeVbtcFormat(&datap->ed_vbtc);
    eye_resultsPtr->hbtcPtr = mcdWrapperEyeHbtcFormat(&datap->ed_hbtc);

    mcdWrapperEyeFreeDataSt(pSerdesDev,datap);
    mcdWrapperEyeFreeConfig(pSerdesDev,configp);
#endif
    return MCD_OK;
}


/******************************************************************************
 MCD_STATUS mcdSerdesGetEye
*******************************************************************************/
MCD_STATUS mcdSerdesGetEye
(
   IN MCD_DEV_PTR pDev,
   IN MCD_U16 sAddr,
   IN MCD_U16 sampleSize,
   IN MCD_U16 highDefinition,
   IN MCD_U16 serdesLogLevel,
   OUT PMCD_EYE_DATA eyeDataBuf
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    sAddr = sAddr;
    sampleSize = sampleSize;
    serdesLogLevel= serdesLogLevel;
#else
    MCD_16  status;
    MCD_U16 serdesTempLogLevel;
    MCD_SER_DEV_PTR pSerdesDev;
    MCD_SER_EYE_CONFIG_TYPE *pEyeConfig;
    MCD_SER_EYE_DATA_TYPE *pEyeData;
    unsigned int slice, phySerdesNum;
    MCD_U32 serdesNum = sAddr - 1;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES((MCD_U32)serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC((MCD_U32)serdesNum,phySerdesNum);

    pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MCD_SERDES_LANE_COUNT))
    {
        MCD_DBG_ERROR("mcdSerdesGetEye: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MCD_FAIL;
    }

    serdesTempLogLevel = (MCD_U16)pSerdesDev->debug;
    pSerdesDev->debug = serdesLogLevel;

    pEyeConfig = mcdWrapperEyeAllocConfig(pSerdesDev);
    pEyeData = mcdWrapperEyeAllocDataSt(pSerdesDev);

    if ((!pEyeConfig) || (!pEyeData))
    {
        if (pEyeData)
        {
            MCD_DBG_ERROR("mcdSerdesGetEye: can't allocate buffer pEyeConfig while pEyeData = :0x%08X\n",pEyeData);
            mcdWrapperEyeFreeDataSt(pSerdesDev, pEyeData);
        }
        if (pEyeConfig)
        {
            MCD_DBG_ERROR("mcdSerdesGetEye: can't allocate buffer pEyeData while pEyeConfig = :0x%08X\n",pEyeConfig);
            mcdWrapperEyeFreeConfig(pSerdesDev, pEyeConfig);
        }

        return MCD_FAIL;
    }
    else
        MCD_DBG_INFO("mcdSerdesGetEye: eye_config_t size: %u; eye_data_t size: %u \n",
                 (sizeof(MCD_SER_EYE_CONFIG_TYPE)), (sizeof(MCD_SER_EYE_DATA_TYPE)));

    switch(sampleSize)
    {
        case 4:
            pEyeConfig->ec_max_dwell_bits = 10000;
            break;
        case 5:
            pEyeConfig->ec_max_dwell_bits = 100000;
            break;
        case 6:
            pEyeConfig->ec_max_dwell_bits = 1000000;
            break;
        case 7:
            pEyeConfig->ec_max_dwell_bits = 10000000;
            break;
        case 8:
            pEyeConfig->ec_max_dwell_bits = 100000000;
            break;
        default:
            pEyeConfig->ec_max_dwell_bits = 1000000;
    }

    if ((pEyeConfig->ec_max_dwell_bits) > 100000)
    {
        pEyeConfig->ec_min_dwell_bits = pEyeConfig->ec_max_dwell_bits / 10;
    }

    pEyeConfig->ec_x_auto_scale = TRUE;   /* auto-scale x resolution */
    pEyeConfig->ec_x_resolution = 64;     /* x resolution */
    pEyeConfig->ec_y_step_size = highDefinition ? 1 : 4; /* y resolution, auto-scale */

    status = (MCD_16)mcdWrapperGetEye(pSerdesDev, phySerdesNum + 1, pEyeConfig, pEyeData);

    if( status < 0 )
    {
        mcdWrapperEyeFreeDataSt(pSerdesDev, pEyeData);
        mcdWrapperEyeFreeConfig(pSerdesDev, pEyeConfig);

        MCD_DBG_ERROR("mcdBSDGetEye: Eye capture failed.\n");
        return MCD_FAIL;
    }

    mcdMemCpy(eyeDataBuf, pEyeData, (MCD_U32)((MCD_UINTPTR)&(((MCD_EYE_DATA *)0)->ed_dc_balance)));

    mcdMemCpy(&eyeDataBuf->hbtcData, &pEyeData->ed_hbtc, sizeof(MCD_SERDES_EYE_HBTC));
    mcdMemCpy(&eyeDataBuf->vbtcData, &pEyeData->ed_vbtc, sizeof(MCD_SERDES_EYE_VBTC));

    eyeDataBuf->ed_error_threshold = (MCD_U16)pEyeData->ed_error_threshold;
    eyeDataBuf->ed_min_dwell_bits = (MCD_64)pEyeData->ed_min_dwell_bits;
    eyeDataBuf->ed_max_dwell_bits = (MCD_64)pEyeData->ed_max_dwell_bits;
    eyeDataBuf->ed_fast_dynamic = (MCD_U16)pEyeData->ed_fast_dynamic;

    mcdWrapperEyeFreeDataSt(pSerdesDev, pEyeData);
    mcdWrapperEyeFreeConfig(pSerdesDev, pEyeConfig);

    pSerdesDev->debug = serdesTempLogLevel;
#endif
    return MCD_OK;
}
#endif
#endif
/*******************************************************************************
* mcdSerdesPolarityConfigImpl
*
* DESCRIPTION:
*       Per Serdes invert the Tx or Rx.
*       Can be run after create port.
*
* INPUTS:
*       MCD_SER_DEV_PTR  pSerdesDev,
*       serdesNum - physical Serdes number
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
int mcdSerdesPolarityConfigImpl
(
    MCD_DEV_PTR         pDev,
    unsigned int        serdesNum,
    unsigned int        invertTx,
    unsigned int        invertRx
)
{
#ifndef ASIC_SIMULATION

    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    unsigned int sbus_addr;
    unsigned int phySerdesNum, slice;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);
    sbus_addr = phySerdesNum + 1;

    mcdSerdesAccessLock(pDev);
    /* Tx polarity En */
    if (pDev->haAccessDisable == MCD_FALSE)
    {
        mcdWrapperSetTxPolarity( pSerdesDev, sbus_addr, invertTx);
    }
    mcdSerdesAccessUnlock(pDev);
    MCD_CHECK_RET_CODE(pSerdesDev);

    mcdSerdesAccessLock( pDev);
    /* Rx Polarity En */
    if (pDev->haAccessDisable == MCD_FALSE)
    {
        mcdWrapperSetRxPolarity(pSerdesDev, sbus_addr, invertRx);
    }
    mcdSerdesAccessUnlock( pDev);
    MCD_CHECK_RET_CODE(pSerdesDev);

#endif /* ASIC_SIMULATION */
    return MCD_OK;
}
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************************
* mcdSerdesPolarityConfigGetImpl
*
* DESCRIPTION:
*       Returns the Tx and Rx SERDES invert state.
*       Can be run after create port.
*
* INPUTS:
*       pSerdesDev
*       serdesNum - physical serdes number
*
* OUTPUTS:
*       invertTx - invert TX polarity (MCD_TRUE - invert, MCD_FALSE - don't)
*       invertRx - invert RX polarity (MCD_TRUE - invert, MCD_FALSE - don't)
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
int mcdSerdesPolarityConfigGetImpl
(
    MCD_SER_DEV_PTR  pSerdesDev,
    unsigned int     serdesNum,
    unsigned int     *invertTx,
    unsigned int     *invertRx
)
{
#ifndef ASIC_SIMULATION
    MCD_DEV_PTR  pDev = pSerdesDev->client_data;
    unsigned int phySerdesNum, slice;
    unsigned int sbus_addr;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);
    sbus_addr = phySerdesNum + 1;

    mcdSerdesAccessLock(pDev);
    /* Get the TX inverter polarity mode: TRUE - inverter is enabled, FALSE - data is not being inverted */
    *invertTx = avago_serdes_get_tx_invert(pSerdesDev, sbus_addr);
    mcdSerdesAccessUnlock( pDev);
    MCD_CHECK_RET_CODE(pSerdesDev);

    mcdSerdesAccessLock(pDev);
    /* Get the RX inverter polarity mode: TRUE - inverter is enabled, FALSE - data is not being inverted */
    *invertRx = avago_serdes_get_rx_invert(pSerdesDev, sbus_addr);
    mcdSerdesAccessUnlock(pDev);
    MCD_CHECK_RET_CODE(pSerdesDev);

#endif /* ASIC_SIMULATION */
    return MCD_OK;
}

/******************************************************************************
 MCD_STATUS mcdSerdesGetTxPolarity
*******************************************************************************/
MCD_STATUS mcdSerdesGetTxPolarity
(
   IN MCD_DEV_PTR pDev,
   IN MCD_U16 sAddr,
   OUT MCD_U16 *polarity
)
{
#ifndef ASIC_SIMULATION

    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    MCD_U32 serdesNum = (MCD_U32)sAddr - 1;
    MCD_U32 slice, phySerdesNum;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);

    mcdSerdesAccessLock(pDev);
    /* Tx polarity En */
    *polarity = mcdWrapperGetTxPolarity( pSerdesDev, phySerdesNum + 1);
    mcdSerdesAccessUnlock(pDev);
    MCD_CHECK_RET_CODE(pSerdesDev);
#endif /* ASIC_SIMULATION */
    return MCD_OK;

}

/******************************************************************************
 MCD_STATUS mcdSerdesSetTxPolarity
*******************************************************************************/
MCD_STATUS mcdSerdesSetTxPolarity
(
   IN MCD_DEV_PTR pDev,
   IN MCD_U16 sAddr,
   IN MCD_U16 polarity
)
{
    return MCD_NOT_IMPLEMENTED;

}

/******************************************************************************
 MCD_STATUS mcdSerdesGetRxPolarity
*******************************************************************************/
MCD_STATUS mcdSerdesGetRxPolarity
(
   IN MCD_DEV_PTR pDev,
   IN MCD_U16 sAddr,
   OUT MCD_U16 *polarity
)
{
#ifndef ASIC_SIMULATION
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    MCD_U32 serdesNum = (MCD_U32)sAddr - 1;
    MCD_U32 slice, phySerdesNum;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);

    mcdSerdesAccessLock(pDev);
    /* Tx polarity En */
    *polarity = mcdWrapperGetRxPolarity( pSerdesDev, phySerdesNum + 1);
    mcdSerdesAccessUnlock(pDev);
    MCD_CHECK_RET_CODE(pSerdesDev);
#endif /* ASIC_SIMULATION */
    return MCD_OK;
}

/******************************************************************************
 MCD_STATUS mcdSerdesSetRxPolarity
*******************************************************************************/
MCD_STATUS mcdSerdesSetRxPolarity
(
   IN MCD_DEV_PTR pDev,
   IN MCD_U16 sAddr,
   IN MCD_U16 polarity
)
{
    return MCD_NOT_IMPLEMENTED;
}

/*******************************************************************************
* mcdSerdesSbmVoltageGet
*
* DESCRIPTION:
*       Gets the voltage data from a given AVAGO_THERMAL_SENSOR sensor.
*       Returns the voltage in milli-volt.
*
* INPUTS:
*       pSerdesDev
*       serdesNum   - physical serdes number
*       sensorAddr  - SBus address of the AVAGO_THERMAL_SENSOR
*
* OUTPUTS:
*       voltage - Serdes voltage in milli-volt
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
int mcdSerdesSbmVoltageGet
(
    MCD_SER_DEV_PTR  pSerdesDev,
    unsigned int    serdesNum,
    unsigned int    sensorAddr,
    unsigned int    *voltage
)
{
#ifndef ASIC_SIMULATION
    MCD_UINT        data;
    unsigned int    i;
    unsigned int    retry=10;
    MCD_DEV_PTR  pDev = pSerdesDev->client_data;

    /* trying to get the Voltage value maximum 10 times and set 1ms delay between each time */
    for(i=0; i < retry; i++)
    {
        mcdSerdesAccessLock(pDev);
        data =  mcdWrapperSerdesInt(pSerdesDev, AVAGO_SBUS_MASTER_ADDRESS, MCD_SBUS_TEMPERATURE_DATA, ((0 << 12) | MCD_SBUS_TEMPERATURE_SENSOR));
        mcdSerdesAccessUnlock(pDev);
        if (data & 0x8000)
        {
            data &= 0x0FFF;         /* Mask down to 12b voltage value */
            *voltage = (data / 2);  /* Scale to milli-volt */

            return MCD_OK;
        }

        /* Delay in 1ms */
        ms_sleep(1);
    }

    return MCD_STATUS_BAD_VALUE;  /* voltage not valid */

#endif /* ASIC_SIMULATION */
    return MCD_OK;
}
#endif
/*******************************************************************************
* mcdSerdesAccessValidate
*
* DESCRIPTION:
*       Validate access to Avago device
*
* INPUTS:
*       pSerdesDev
*       uint sbus_addr
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       None.
*
*******************************************************************************/
MCD_STATUS mcdSerdesAccessValidate
(
    MCD_SER_DEV_PTR pSerdesDev,
    MCD_U32 sbus_addr
)
{
#ifndef ASIC_SIMULATION
    if (mcdWrapperSbusTest(pSerdesDev, mcdWrapperBusCntrrAddr(sbus_addr), 2) == TRUE)
    {
        MCD_DBG_INFO("Access Verified\n");
        return MCD_OK;
    }
    else
    {
        MCD_DBG_ERROR("Access Failed\n");
        return MCD_FAIL;
    }
#else /* ASIC_SIMULATION */
    return MCD_OK;
#endif /* ASIC_SIMULATION */
}
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************************
* mcdCheckSerdesInitStatus
*******************************************************************************/
MCD_STATUS mcdCheckSerdesInitStatus
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 serdesNum
)
{
    MCD_U32 readData;

    /* check digital reset */
    ATTEMPT(mcdHwGetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_EXTERNAL_CONFIGURATION_1(serdesNum), 3, 1, &readData));

    if(readData == 0)
        return MCD_STATUS_NOT_INITIALIZED;

  return MCD_OK;
}
#endif /*MV_HWS_REDUCED_BUILD_EXT_CM3*/
/*******************************************************************************
* mcdSerdesAccessLock
*
*******************************************************************************/
void mcdSerdesAccessLock
(
     MCD_DEV_PTR pDev
)
{
    /*
    ** SW Semaphore Protection Section
    ** ===============================
    */

#ifdef MV_HWS_FREE_RTOS
    /* Service CPU SW Protection */
    mvPortCtrlAvagoLock();

#endif /* MV_HWS_FREE_RTOS */

    /*
    ** HW Semaphore Protection Section
    ** ===============================
    */
#ifdef MV_HWS_REDUCED_BUILD_EXT_CM3
    /* When running on  Service CPU */
    mcdLockHwSemaphore(pDev, MCD_SEMA_SERDES, MCD_CM3_SERDES_LOCK);
#else
    /* When running on Host CPU*/
    if (pDev->highAvailabilityMode == MCD_TRUE)
    {
        /* WA to allow lock/unlock under HA mode */
        pDev->haAccessDisable = MCD_TRUE;
        pDev->highAvailabilityMode = MCD_FALSE;
    }
        mcdLockHwSemaphore(pDev, MCD_SEMA_SERDES, MCD_HOST_SERDES_LOCK);
#endif

}

/*******************************************************************************
* mcdSerdesAccessUnlock
*
*
*******************************************************************************/
void mcdSerdesAccessUnlock
(
       MCD_DEV_PTR pDev
)
{
    /*
    ** SW Semaphore Protection Section
    ** ===============================
    */
#ifdef MV_HWS_FREE_RTOS
    /* Service CPU SW Protection */
    mvPortCtrlAvagoUnlock();
#endif /*MV_HWS_FREE_RTOS */

    /*
    ** HW Semaphore Protection Section
    ** ===============================
    */

    mcdUnlockHwSemaphore(pDev, MCD_SEMA_SERDES);
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
    if (pDev->haAccessDisable == MCD_TRUE)
    {
        /* WA to allow lock/unlock under HA mode */
        pDev->highAvailabilityMode = MCD_TRUE;
        pDev->haAccessDisable = MCD_FALSE;
    }
#endif /* MV_HWS_REDUCED_BUILD_EXT_CM3 */

}
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/******************************************************************************
 MCD_STATUS mcdExecuteIndirectSBusCmd
*******************************************************************************/
MCD_STATUS mcdExecuteIndirectSBusCmd
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort
)
{
    return MCD_NOT_IMPLEMENTED;
}


/******************************************************************************
 MCD_STATUS mcdIndirectSBusWrite
*******************************************************************************/
MCD_STATUS mcdIndirectSBusWrite
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 sBusReceiverAddr,
    IN MCD_U16 regAddr,
    IN MCD_U16 dataH,
    IN MCD_U16 dataL,
    OUT MCD_U16 *resultCode
)
{
    return MCD_NOT_IMPLEMENTED;
}

/******************************************************************************
 MCD_STATUS mcdIndirectSBusRead
*******************************************************************************/
MCD_STATUS mcdIndirectSBusRead
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 sBusReceiverAddr,
    IN MCD_U16 regAddr,
    OUT MCD_U16 *dataH,
    OUT MCD_U16 *dataL,
    OUT MCD_U16 *resultCode
)
{
    return MCD_NOT_IMPLEMENTED;
}

/******************************************************************************
 MCD_STATUS mcdSerdesInterrupt
*******************************************************************************/
MCD_STATUS mcdSerdesInterrupt
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 sBusReceiverAddr,
    IN MCD_U16 interruptCode,
    IN MCD_U16 interruptData,
    OUT MCD_U16 *interruptResult
)
{
    return MCD_NOT_IMPLEMENTED;
}

/******************************************************************************
 MCD_STATUS mcdSbusInterrupt
*******************************************************************************/
MCD_STATUS mcdSbusInterrupt
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 interruptCode,
    IN MCD_U16 interruptInput,
    OUT MCD_U16 *interruptResult,
    OUT MCD_U16 *interruptStatus
)
{
    return MCD_NOT_IMPLEMENTED;
}
#if MCD_ENABLE_SERDES_API

#if 0
/******************************************************************************
 MCD_UINT mcdSerdesMDIO
*******************************************************************************/
MCD_UINT mcdSerdesMDIO
(
    IN MCD_SER_DEV_PTR pSerdesDev,
    IN uint sbusAddr,
    IN MCD_U8 regAddr,
    IN MCD_U8 mdioCmd,
    OUT uint *sbusData
)
{
    return MCD_NOT_IMPLEMENTED;
}
#endif /*0*/

/**
 * @internal mcdFreeSerdesDev function
 * @endinternal
 *
 * @brief   Frees SERDES driver memory allocated in mcdInitSerdesDev
 *
 * @param[in] pDev
 *
 * @retval 0                        - on success
 * @retval 1                        - on error
 */

MCD_STATUS mcdFreeSerdesDev
(
    IN MCD_DEV_PTR pDev
)
{
#ifndef ASIC_SIMULATION
    MCD_SER_DEV_PTR pSerdesDev;
#endif

    if (!pDev->serdesDev)
    {
        MCD_DBG_ERROR("mcdFreeSerdesDev: pSerdesDev is NULL\n");
        return MCD_FAIL;
    }
#ifndef ASIC_SIMULATION
    pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    mcdWrapperFreeDevStruct(pSerdesDev);
    if(pSerdesDev != NULL)
    {
        AAPL_FREE(pSerdesDev);
        MCD_DBG_INFO("mcdFreeSerdesDev: free pDev->serdesDev\n");
    }
    else
        MCD_DBG_INFO("mcdFreeSerdesDev: pDev->serdesDev is NULL, no need to free\n");
#endif

    return MCD_OK;

}
/******************************************************************************
 MCD_STATUS mcdSerdesGetRevision
*******************************************************************************/
MCD_STATUS mcdSerdesGetRevision
(
   IN MCD_DEV_PTR pDev,
   OUT MCD_U16 *serdesRevision,
   OUT MCD_U16 *sbmRevision
)
{
#ifndef ASIC_SIMULATION
    MCD_SER_DEV_PTR pSerdesDev;
    MCD_U16 sbmAddr;
    MCD_U16 sAddr = 1;

    pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;

    if (!pSerdesDev)
    {
        MCD_DBG_ERROR("mcdSerdesGetRevision: pSerdesDev is NULL\n");
        return MCD_FAIL;
    }

    sbmAddr = (MCD_U16)mcdWrapperBusMasterAddr(sAddr);

    *serdesRevision = (MCD_U16)mcdWrapperGetSerdesRev(pSerdesDev, sAddr);
    *sbmRevision = (MCD_U16)mcdWrapperGetSerdesRev(pSerdesDev, sbmAddr);

    MCD_DBG_INFO("mcdSerdesGetRevision: SerDes revision:0x%04X SBM revision:0x%04X\n",
                 *serdesRevision, *sbmRevision);
#endif
    return MCD_OK;

}
/******************************************************************************
 MCD_STATUS mcdSerdesGetVoltage
*******************************************************************************/
MCD_STATUS mcdSerdesGetVoltage
(
   IN MCD_DEV_PTR pDev,
   OUT MCD_U16 *coreVoltage,
   OUT MCD_U16 *DVDDVoltage,
   OUT MCD_U16 *AVDDVoltage
)
{
#ifndef ASIC_SIMULATION
    MCD_UINT          data;
    MCD_SER_DEV_PTR pSerdesDev;

    *coreVoltage = *DVDDVoltage = *AVDDVoltage =0;

    pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;

    if (!pSerdesDev)
    {
        MCD_DBG_ERROR("mcdSerdesGetVoltage: pSerdesDev is NULL\n");
        return MCD_FAIL;
    }
    ATTEMPT(mcdHwSetPhyRegMask32bit(pDev,  DONT_CARE, MCD_SERDES_TSEN_IP_sensor_enable, 0x3FF, 0x3FF));

    mcdSerdesAccessLock(pDev);
    data =  mcdWrapperSerdesInt(pSerdesDev, AVAGO_SBUS_MASTER_ADDRESS, MCD_SBUS_VOLTAGE_DATA, ((0 << 12) | MCD_SBUS_TEMPERATURE_SENSOR));
    mcdSerdesAccessUnlock(pDev);
    if (data & 0x8000)
    {
        data &= 0x0FFF;         /* Mask down to 12b voltage value */
        *coreVoltage = (data / 2);  /* Scale to milli-volt */
    }

    mcdSerdesAccessLock(pDev);
    data =  mcdWrapperSerdesInt(pSerdesDev, AVAGO_SBUS_MASTER_ADDRESS,  MCD_SBUS_VOLTAGE_DATA, ((1 << 12) | MCD_SBUS_TEMPERATURE_SENSOR));
    mcdSerdesAccessUnlock(pDev);
    if (data & 0x8000)
    {
        data &= 0x0FFF;         /* Mask down to 12b voltage value */
        *DVDDVoltage = (data / 2);  /* Scale to milli-volt */
    }

    mcdSerdesAccessLock(pDev);
    data =  mcdWrapperSerdesInt(pSerdesDev, AVAGO_SBUS_MASTER_ADDRESS,  MCD_SBUS_VOLTAGE_DATA, ((2 << 12) | MCD_SBUS_TEMPERATURE_SENSOR));
    mcdSerdesAccessUnlock(pDev);
    if (data & 0x8000)
    {
        data &= 0x0FFF;         /* Mask down to 12b voltage value */
        *AVDDVoltage = (data / 2);  /* Scale to milli-volt */
    }

    MCD_DBG_INFO("mcdSerdesGetVoltage: voltages Core:%umV; DVDD:%umV; AVDD:%umV\n",
                 *coreVoltage, *DVDDVoltage, *AVDDVoltage);

#endif /* ASIC_SIMULATION */
    return MCD_OK;
}

/******************************************************************************
 MCD_STATUS mcdSerdesGetTxFFE
*******************************************************************************/
MCD_STATUS mcdSerdesGetTxFFE
(
   IN MCD_DEV_PTR pDev,
   IN MCD_U16 sAddr,
   OUT MCD_16 *preCursor,
   OUT MCD_16 *attenuation,
   OUT MCD_16 *postCursor,
   OUT MCD_16 *slew
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    sAddr = sAddr;
#else

    MCD_AUTO_TUNE_RESULTS    results;
    unsigned int serdesNum = MCD_SERDES_FROM_SBUS_ADDR_GET(sAddr);

    ATTEMPT(mcdSerdesAutoTuneResult(pDev, serdesNum, &results));

    /* Get the TX configuration values */
    *attenuation  = results.txAmp;
    *postCursor = results.txEmph0;
    *preCursor = results.txEmph1;
#endif /* ASIC_SIMULATION */

    return MCD_OK;

}

/******************************************************************************
 MCD_STATUS mcdSerdesSetTxFFE
*******************************************************************************/
MCD_STATUS mcdSerdesSetTxFFE
(
   IN MCD_DEV_PTR pDev,
   IN MCD_U16 sAddr,
   IN MCD_16 preCursor,
   IN MCD_16 attenuation,
   IN MCD_16 postCursor,
   IN MCD_16 slew
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    sAddr         = sAddr;
    preCursor     = preCursor;
    attenuation   = attenuation;
    postCursor    = postCursor;
    slew          = slew;
#else

    Avago_serdes_tx_eq_t tx_eq;
    unsigned int serdesNum = MCD_SERDES_FROM_SBUS_ADDR_GET(sAddr);
    int rc1, rc2, rc3, rc4;

    /* Set the TX equalization values */
    tx_eq.atten = (short)attenuation;   /* Attenuator setting */
    tx_eq.post  = (short)postCursor;    /* Post-cursor setting */
    tx_eq.pre   = (short)preCursor;     /* Pre-cursor setting */
    tx_eq.slew  = (short)slew;          /* Slew rate setting */

    if((tx_eq.atten == tx_eq.pre) && (tx_eq.atten == tx_eq.post))
    {
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x15, (3 << 14) | (tx_eq.atten & 0xFF), &rc3));
    }
    else
    {
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x15, (3 << 14) | 0, &rc1));
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x15, (2 << 14) | (tx_eq.post & 0xFF), &rc2));
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x15, (1 << 14) | (tx_eq.atten & 0xFF), &rc3));
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x15, (0 << 14) | (tx_eq.pre & 0xFF), &rc4));

        /* If SpicoInterrupt 0x15 succeeds to run - the return code is the Interrupt number=0x15
           The TX equalization configuration succeeds only if all the four SpicoInterrupt settings are passed: (0x15)x4=0x54 */
        if ((rc1+rc2+rc3+rc4) != MCD_SERDES_TX_EQUALIZE_PASS)
        {
            MCD_DBG_ERROR("mcdSerdesSetTxFFE: SerDes failed to apply since new EQ settings exceed the limit %d %d %d %d\n", rc1, rc2, rc3, rc4);
            return MCD_FAIL;
        }
    }

#if 0
    /* the SlewRate parameter is not supported in Avago Serdes */
    /* these settings are needed due to problem with SlewRate configuration in avago_serdes_set_tx_eq */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18, 0x4240, NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, (0x184 + slew), NULL));
#endif

#endif /* ASIC_SIMULATION */
    return MCD_OK;

}

/******************************************************************************
 MCD_STATUS mcdSerdesGetCDRLock
*******************************************************************************/
MCD_STATUS mcdSerdesGetCDRLock
(
   IN MCD_DEV_PTR pDev,
   IN MCD_U16 sAddr,
   OUT MCD_U16 *CDRLockState
)
{
#ifndef ASIC_SIMULATION
    MCD_SER_DEV_PTR pSerdesDev;
    MCD_U32 serdesNum = (MCD_U32)sAddr - 1;
    MCD_U32 slice, phySerdesNum;

    pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;

    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MCD_SERDES_LANE_COUNT))
    {
        MCD_DBG_ERROR("mcdSerdesGetCDRLock: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MCD_FAIL;
    }

    /*
      CDRLockState = 1 is locked; CDRLockState = 0 is not locked;
    */
    mcdSerdesAccessLock(pDev);
    *CDRLockState = (MCD_U16)mcdWrapperGetCDRLock(pSerdesDev, phySerdesNum + 1);
    mcdSerdesAccessUnlock(pDev);
    MCD_DBG_INFO("mcdSerdesGetCDRLock: CDRLockState:0x%X\n", *CDRLockState);
#endif
    return MCD_OK;
}

/******************************************************************************
 MCD_STATUS mcdSerdesPMDTrainingLog
*******************************************************************************/
MCD_STATUS mcdSerdesPMDTrainingLog
(
   IN MCD_DEV_PTR pDev,
   IN MCD_U16 sAddr,
   OUT PMCD_TRAINING_INFO pTrainInfo
)
{
#ifndef ASIC_SIMULATION
    MCD_SER_DEV_PTR pSerdesDev;
    MCD_SER_PMD_DEBUG_TYPE *pSerdesDebugStruct = NULL;
    MCD_U16 index = 0;
    MCD_U32 slice, phySerdesNum;
    MCD_U32 serdesNum = (MCD_U32)sAddr - 1;

    pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;

    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MCD_SERDES_LANE_COUNT))
    {
        MCD_DBG_ERROR("mcdSerdesPMDTrainingLog: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MCD_FAIL;
    }

    if (!pTrainInfo)
    {
        MCD_DBG_ERROR("mcdSerdesPMDTrainingLog: pTrainInfo is NULL\n");
        return MCD_FAIL;
    }
    mcdMemSet(pTrainInfo, 0, (sizeof(MCD_TRAINING_INFO)));

    /* Allocate a PMD structure for training log */
    pSerdesDebugStruct = mcdWrapperPMDAllocDebugStruct(pSerdesDev);
    if (pSerdesDebugStruct == NULL)
    {
        MCD_DBG_ERROR("mcdSerdesPMDTrainingLog: pSerdesDebugSt is NULL\n");
        return MCD_FAIL;
    }

    mcdSerdesAccessLock(pDev);
    mcdWrapperPMDDebug(pSerdesDev, phySerdesNum + 1, pSerdesDebugStruct);
    mcdSerdesAccessUnlock(pDev);

    pTrainInfo->reset = (MCD_BOOL)pSerdesDebugStruct->reset;
    pTrainInfo->rx_metric = pSerdesDebugStruct->rx_metric;
    pTrainInfo->local.preset = pSerdesDebugStruct->lcl->preset;
    pTrainInfo->local.initialize = pSerdesDebugStruct->lcl->initialize;
    pTrainInfo->remote.preset = pSerdesDebugStruct->remote->preset;
    pTrainInfo->remote.initialize = pSerdesDebugStruct->remote->initialize;
    pTrainInfo->last_local_request = pSerdesDebugStruct->last_local_request;
    mcdMemCpy(&pTrainInfo->last_remote_request, &pSerdesDebugStruct->last_remote_request,
              (sizeof(MCD_UINT)*8));

    for (index=0; index<3; index++)
    {
        pTrainInfo->local.tap[index].inc = pSerdesDebugStruct->lcl->tap[index]->inc;
        pTrainInfo->local.tap[index].dec = pSerdesDebugStruct->lcl->tap[index]->dec;
        pTrainInfo->local.tap[index].max = pSerdesDebugStruct->lcl->tap[index]->max;
        pTrainInfo->local.tap[index].min = pSerdesDebugStruct->lcl->tap[index]->min;

        pTrainInfo->remote.tap[index].inc = pSerdesDebugStruct->remote->tap[index]->inc;
        pTrainInfo->remote.tap[index].dec = pSerdesDebugStruct->remote->tap[index]->dec;
        pTrainInfo->remote.tap[index].max = pSerdesDebugStruct->remote->tap[index]->max;
        pTrainInfo->remote.tap[index].min = pSerdesDebugStruct->remote->tap[index]->min;
    }

    /* print training log output */
    mcdWrapperPMDDebugPrint(pSerdesDev, pSerdesDebugStruct);
    mcdWrapperPMDFreeDebugStruct(pSerdesDev, pSerdesDebugStruct);

    MCD_DBG_INFO("mcdSerdesPMDTrainingLog: Completed\n");

#endif
    return MCD_OK;
}

/******************************************************************************
 MCD_STATUS mcdSerdesTxInjectError
*******************************************************************************/
MCD_STATUS mcdSerdesTxInjectError
(
   IN MCD_DEV_PTR pDev,
   IN MCD_U16 sAddr,
   IN MCD_U16 numErrBit
)
{
#ifndef ASIC_SIMULATION
    MCD_SER_DEV_PTR pSerdesDev;
    MCD_16 status = MCD_OK;
    MCD_U32 slice, phySerdesNum;
    MCD_U32 serdesNum = (MCD_U32)sAddr - 1;

    pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;

        /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MCD_SERDES_LANE_COUNT))
    {
        MCD_DBG_ERROR("mcdSerdesTxInjectError: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MCD_FAIL;
    }
    mcdSerdesAccessLock(pDev);
    if (pDev->haAccessDisable == MCD_FALSE)
    {
        status = (MCD_16)mcdWrapperTxInjectError(pSerdesDev, phySerdesNum + 1, numErrBit);
    }
    mcdSerdesAccessUnlock(pDev);
    if (status != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSerdesTxInjectError: Failed\n");
        return MCD_FAIL;
    }

    MCD_DBG_INFO("mcdSerdesTxInjectError: Completed\n");
#endif
    return MCD_OK;
}

/******************************************************************************
 MCD_STATUS mcdSerdesRxInjectError
*******************************************************************************/
MCD_STATUS mcdSerdesRxInjectError
(
   IN MCD_DEV_PTR pDev,
   IN MCD_U16 sAddr,
   IN MCD_U16 numErrBit
)
{
#ifndef ASIC_SIMULATION
    MCD_SER_DEV_PTR pSerdesDev;
    MCD_16 status = MCD_OK;
    MCD_U32 slice, phySerdesNum;
    MCD_U32 serdesNum = (MCD_U32)sAddr - 1;

    pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;

    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MCD_SERDES_LANE_COUNT))
    {
        MCD_DBG_ERROR("mcdSerdesTxInjectError: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MCD_FAIL;
    }
    mcdSerdesAccessLock(pDev);
    if (pDev->haAccessDisable == MCD_FALSE)
    {
        status = (MCD_16)mcdWrapperRxInjectError(pSerdesDev, phySerdesNum + 1, numErrBit);
    }
     mcdSerdesAccessUnlock(pDev);
    if (status != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSerdesRxInjectError: Failed\n");
        return MCD_FAIL;
   }
    MCD_DBG_INFO("mcdSerdesRxInjectError: Completed\n");
#endif
    return MCD_OK;
}

/******************************************************************************
 MCD_STATUS mcdSerdesSetTxPRBS
*******************************************************************************/
MCD_STATUS mcdSerdesSetTxPRBS
(
   IN MCD_DEV_PTR pDev,
   IN MCD_U16 sAddr,
   IN MCD_SERDES_TX_DATA_TYPE txDataType
)
{
#ifndef ASIC_SIMULATION
    MCD_SER_DEV_PTR pSerdesDev;
    MCD_16 status = MCD_OK;
    MCD_U32 serdesNum = (MCD_U32)sAddr - 1;
    MCD_U32 slice, phySerdesNum;
    pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MCD_SERDES_LANE_COUNT))
    {
        MCD_DBG_ERROR("mcdSerdesSetTxPRBS: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MCD_FAIL;
    }

    mcdSerdesAccessLock(pDev);
    if (pDev->haAccessDisable == MCD_FALSE)
    {
        status = (MCD_16)mcdWrapperSetTxPRBS(pSerdesDev, phySerdesNum + 1, (Avago_serdes_tx_data_sel_t)txDataType);
    }
    mcdSerdesAccessUnlock(pDev);
    if (status != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSerdesSetTxPRBS: Failed\n");
        return MCD_FAIL;
    }
    MCD_DBG_INFO("mcdSerdesSetTxPRBS: Completed\n");
#endif
    return MCD_OK;
}

/******************************************************************************
 MCD_STATUS mcdSerdesGetTxPRBS
*******************************************************************************/
MCD_STATUS mcdSerdesGetTxPRBS
(
   IN MCD_DEV_PTR pDev,
   IN MCD_U16 sAddr,
   OUT MCD_SERDES_TX_DATA_TYPE *txDataType
)
{
#ifndef ASIC_SIMULATION
    MCD_SER_DEV_PTR pSerdesDev;
    MCD_U32 serdesNum = (MCD_U32)sAddr - 1;
    MCD_U32 slice, phySerdesNum;
    pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MCD_SERDES_LANE_COUNT))
    {
        MCD_DBG_ERROR("mcdSerdesGetTxPRBS: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MCD_FAIL;
    }
    mcdSerdesAccessLock(pDev);
    *txDataType = (MCD_SERDES_TX_DATA_TYPE)mcdWrapperGetTxPRBS(pSerdesDev, phySerdesNum + 1);
    mcdSerdesAccessUnlock(pDev);

    MCD_DBG_INFO("mcdSerdesGetTxPRBS: txDataType:%u\n", *txDataType);
#endif
    return MCD_OK;
}


/******************************************************************************
 MCD_STATUS mcdSerdesSetTxUserData
*******************************************************************************/
MCD_STATUS mcdSerdesSetTxUserData
(
   IN MCD_DEV_PTR pDev,
   IN MCD_U16 sAddr,
   IN MCD_32 userData[4]
)
{
#ifndef ASIC_SIMULATION

    MCD_SER_DEV_PTR pSerdesDev;
    MCD_16 status = MCD_OK;
    long tx_user[4];
    MCD_U32 ii;
    MCD_U32 serdesNum = (MCD_U32)sAddr - 1;
    MCD_U32 slice, phySerdesNum;
    pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);
    MCD_DBG_ERROR("mcdSerdesSetTxUserData: %x %x %x %x\n",userData[0],userData[1],userData[2],userData[3]);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MCD_SERDES_LANE_COUNT))
    {
        MCD_DBG_ERROR("mcdSerdesSetTxUserData: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MCD_FAIL;
    }

    /* convert types */
    for (ii = 0; ii < 4; ii++)
    {
        tx_user[ii] = userData[ii];
    }

    mcdSerdesAccessLock(pDev);
    if (pDev->haAccessDisable == MCD_FALSE)
    {
        status = (MCD_16)mcdWrapperSetTxUserData(pSerdesDev, phySerdesNum + 1, tx_user);
    }
    mcdSerdesAccessUnlock(pDev);
    if (status != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSerdesSetTxUserData: Failed\n");
        return MCD_FAIL;
    }

    MCD_DBG_INFO("mcdSerdesSetTxUserData: Completed\n");
#endif
    return MCD_OK;
}


/******************************************************************************
 MCD_STATUS mcdSerdesGetTxUserData
*******************************************************************************/
MCD_STATUS mcdSerdesGetTxUserData
(
   IN MCD_DEV_PTR pDev,
   IN MCD_U16 sAddr,
   OUT MCD_32 userData[4]
)
{
#ifndef ASIC_SIMULATION
    MCD_SER_DEV_PTR pSerdesDev;
    MCD_16 status = MCD_OK;
    long tx_user[4];
    MCD_U32 ii;
    MCD_U32 serdesNum = (MCD_U32)sAddr - 1;
    MCD_U32 slice, phySerdesNum;
    pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
        /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MCD_SERDES_LANE_COUNT))
    {
        MCD_DBG_ERROR("mcdSerdesGetTxUserData: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MCD_FAIL;
    }
    mcdSerdesAccessLock(pDev);
    status = (MCD_16)mcdWrapperGetTxUserData(pSerdesDev, phySerdesNum + 1, tx_user);
    mcdSerdesAccessUnlock(pDev);
    if (status != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSerdesGetTxUserData: Failed\n");
        return MCD_FAIL;
   }

    /* convert types */
    for (ii = 0; ii < 4; ii++)
    {
        userData[ii] = (MCD_32)tx_user[ii];
    }

    MCD_DBG_INFO("mcdSerdesGetTxUserData: %x %x %x %x\n",userData[0],userData[1],userData[2],userData[3]);
    MCD_DBG_INFO("mcdSerdesGetTxUserData: Completed\n");
#endif
    return MCD_OK;

}
/******************************************************************************
 MCD_STATUS mcdSerdesSetRxCmpData
*******************************************************************************/
MCD_STATUS mcdSerdesSetRxCmpData
(
   IN MCD_DEV_PTR pDev,
   IN MCD_U16 sAddr,
   IN MCD_SERDES_RX_CMP_TYPE RxCmpType
)
{
#ifndef ASIC_SIMULATION
    MCD_SER_DEV_PTR pSerdesDev;
    MCD_16 status = MCD_OK;
    MCD_U32 serdesNum = (MCD_U32)sAddr - 1;
    MCD_U32 slice, phySerdesNum;
    pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;

    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);
    if ((!pSerdesDev) || (!sAddr) || (sAddr > MCD_SERDES_LANE_COUNT))
    {
        MCD_DBG_ERROR("mcdSerdesSetRxCmpData: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MCD_FAIL;
    }

    mcdSerdesAccessLock(pDev);
    if (pDev->haAccessDisable == MCD_FALSE)
    {
        status = (MCD_16)mcdWrapperSetRxCmpData(pSerdesDev, phySerdesNum+1, (Avago_serdes_rx_cmp_data_t)RxCmpType);
    }
    mcdSerdesAccessUnlock(pDev);
    if (status != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSerdesSetRxCmpData: Failed\n");
        return MCD_FAIL;
    }

    MCD_DBG_INFO("mcdSerdesSetRxCmpData: Completed\n");
#endif
    return MCD_OK;
}


/******************************************************************************
 MCD_STATUS mcdSerdesGetRxCmpData
*******************************************************************************/
MCD_STATUS mcdSerdesGetRxCmpData
(
   IN MCD_DEV_PTR pDev,
   IN MCD_U16 sAddr,
   OUT MCD_SERDES_RX_CMP_TYPE *RxCmpType
)
{
#ifndef ASIC_SIMULATION
    MCD_SER_DEV_PTR pSerdesDev;
    MCD_U32 serdesNum = (MCD_U32)sAddr - 1;
    MCD_U32 slice, phySerdesNum;
    pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MCD_SERDES_LANE_COUNT))
    {
        MCD_DBG_ERROR("mcdSerdesGetRxCmpData: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MCD_FAIL;
    }

    mcdSerdesAccessLock(pDev);
    *RxCmpType = (MCD_SERDES_RX_CMP_TYPE)mcdWrapperGetRxCmpData(pSerdesDev, phySerdesNum + 1);
    mcdSerdesAccessUnlock(pDev);

    MCD_DBG_INFO("mcdSerdesGetRxCmpData: RxCmpType:%u\n", *RxCmpType);
#endif
    return MCD_OK;
}

/******************************************************************************
 MCD_STATUS mcdSerdesGetErrCount
*******************************************************************************/
MCD_STATUS mcdSerdesGetErrCount
(
   IN MCD_DEV_PTR pDev,
   IN MCD_U16 sAddr,
   IN MCD_BOOL resetCounter,
   OUT MCD_U32 *errCount
)
{
#ifndef ASIC_SIMULATION
    MCD_U32 serdesNum = (MCD_U32)sAddr - 1;
    MCD_U32 slice, phySerdesNum;
    MCD_SER_DEV_PTR pSerdesDev;
    pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MCD_SERDES_LANE_COUNT))
    {
        MCD_DBG_ERROR("mcdSerdesGetErrCount: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MCD_FAIL;
    }

    mcdSerdesAccessLock(pDev);
    *errCount = (MCD_U32)mcdWrapperGetErrCounter(pSerdesDev, phySerdesNum+1, 0, resetCounter);
    mcdSerdesAccessUnlock(pDev);

    MCD_DBG_INFO("mcdSerdesGetErrCount: errCount:%u\n", *errCount);
#endif
    return MCD_OK;

}

/*******************************************************************************
mcdSerdesGetLoopbackInfo
*
* DESCRIPTION:
*       Gets the status of Internal/External SERDES loopback mode.
*       Can be run after create port.
*
* INPUTS:
*       pDev
*       serdesNum - physical Serdes number
*
* OUTPUTS:
*     lbModePtr - current loopback mode
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesGetLoopbackInfo
(
    IN MCD_DEV_PTR  pDev,
    IN MCD_U16      sAddr,
    IN MCD_U16      *lbModePtr
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    sAddr = sAddr;
    *lbModePtr = MCD_SERDES_LP_DISABLE;
#else

    MCD_SER_DEV_PTR pSerdesDev;
    MCD_BOOL internalLB;
    MCD_SER_TX_DATA_SEL_TYPE  externalLB;
    MCD_U32 serdesNum = (MCD_U32)sAddr - 1;
    MCD_U32 slice, phySerdesNum;
    pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;

    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MCD_SERDES_LANE_COUNT))
    {
        MCD_DBG_ERROR("mcdSerdesSetLoopback: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MCD_FAIL;
    }
    mcdSerdesAccessLock(pDev);
    /* Get TRUE if internal loopback is enabled, FALSE if external signal */
    internalLB =mcdWrapperGetRxLoopbackInfo(pSerdesDev, phySerdesNum+1);
    mcdSerdesAccessUnlock(pDev);
    MCD_CHECK_RET_CODE(pSerdesDev);

    if (internalLB == MCD_TRUE)
    {
        /* Internal Loopback mode */
        *lbModePtr = MCD_SERDES_LP_AN_TX_RX;
        return MCD_OK;
    }

    mcdSerdesAccessLock(pDev);
    /* Get the selected TX data source */
    externalLB = mcdWrapperGetTxPRBS(pSerdesDev, phySerdesNum+1);
    mcdSerdesAccessUnlock(pDev);
    MCD_CHECK_RET_CODE(pSerdesDev);

    /* Check the External Loopback or Disable mode */
    *lbModePtr = (externalLB == AVAGO_SERDES_TX_DATA_SEL_LOOPBACK) ? MCD_SHALLOW_SERDES_LOOPBACK : MCD_CLEAR_SERDES_LOOPBACK;
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

#endif /*MCD_ENABLE_SERDES_API*/

/******************************************************************************
 MCD_STATUS mcdSerdesSetLoopback
 Inputs:
 pDev:
     pointer to MCD_DEV initialized by mcdInitDriver() call
 sAddr:
     SerDes lane. Range [1 to 16]; Refer to MCD_GET_SERDES_ID for sAddr
 loopbackMode:
     MCD_CLEAR_SERDES_LOOPBACK(0)
     MCD_DEEP_SERDES_LOOPBACK(1)
     MCD_SHALLOW_SERDES_LOOPBACK(2)
     MCD_PARALLEL_SERDES_LOOPBACK(2)
*******************************************************************************/
MCD_STATUS mcdSerdesSetLoopback
(
   IN MCD_DEV_PTR pDev,
   IN MCD_U16 sAddr,
   IN MCD_U16 loopbackMode
)
{
#ifndef ASIC_SIMULATION
    MCD_SER_DEV_PTR pSerdesDev;
    MCD_U8 side;
    MCD_U8 txdivider;
    unsigned int serdesNum = MCD_SERDES_FROM_SBUS_ADDR_GET(sAddr);
    unsigned int invertTx = MCD_FALSE, invertRx = MCD_FALSE;
    MCD_U32  laneSpeed;
    MCD_U32 slice, phySerdesNum;
    MCD_BOOL retimerMode;
    pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;

    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);
    side = (serdesNum < 8)? MCD_LINE_SIDE : MCD_HOST_SIDE;
    if ((!pSerdesDev) || (!sAddr) || (sAddr > MCD_SERDES_LANE_COUNT))
    {
        MCD_DBG_ERROR("mcdSerdesSetLoopback: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MCD_FAIL;
    }

    /* update to physical serdes address  */
    sAddr = phySerdesNum + 1;

    if (loopbackMode > MCD_SHALLOW_SERDES_LOOPBACK)
    {
        MCD_DBG_ERROR("mcdSerdesSetLoopback: Invalid loopbackMode:%u\n", loopbackMode);
        return MCD_FAIL;
    }
    /* Get lane speed */
    ATTEMPT(mcdGetLaneSpeed(pDev->portConfig[(serdesNum & 7)].portMode, side, &laneSpeed));
    /* Check to see if port mode is in Retimer */
    retimerMode = mcdIsRetimerMode(pDev->portConfig[(serdesNum & 7)].portMode);

    switch(loopbackMode)
    {
    case MCD_CLEAR_SERDES_LOOPBACK:
        /* return polarity to default */
        invertTx = serdesElectricalParams[serdesNum].txPolarity;
        invertRx = serdesElectricalParams[serdesNum].rxPolarity;
        ATTEMPT(mcdSerdesPolarityConfigImpl(pDev, serdesNum, invertTx, invertRx));

        if (pDev->serdesStatus.serdesLpbkMode[serdesNum & 7] == MCD_DEEP_SERDES_LOOPBACK)
        {
            /* Clear Deep Loopback mode */
            mcdSerdesAccessLock(pDev);
            if (pDev->haAccessDisable == MCD_FALSE)
            {
                mcdWrapperSetRxLoopback(pSerdesDev, sAddr, MCD_FALSE);
            }
            mcdSerdesAccessUnlock(pDev);
            mcdWrapperMsSleep(5);

            mcdSerdesAccessLock(pDev);
            if (pDev->haAccessDisable == MCD_FALSE)
            {
                mcdWrapperSerdesTxRxEnableSet(pSerdesDev,sAddr,MCD_TRUE, MCD_FALSE, MCD_TRUE);
            }
            mcdSerdesAccessUnlock(pDev);

            mcdSerdesAccessLock(pDev);
            if (pDev->haAccessDisable == MCD_FALSE)
            {
                mcdWrapperSerdesTxRxEnableSet(pSerdesDev,sAddr,MCD_TRUE, MCD_TRUE, MCD_TRUE);
            }
            mcdSerdesAccessUnlock(pDev);

            /* Run calibration, whenever serdes Rx_En bit is toggled */
            ATTEMPT(mcdSerdesRxCalibrationConfig(pDev, serdesNum, laneSpeed));
        }
        else if (pDev->serdesStatus.serdesLpbkMode[serdesNum & 7] == MCD_SHALLOW_SERDES_LOOPBACK)
        {
            if (retimerMode)
            {
                txdivider = mcdRetimerBaudRate2DividerValue[laneSpeed];
                /* Serdes External config1 reg bit[3], RFResetIn is asserted */
                ATTEMPT(mcdHwSetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_EXTERNAL_CONFIGURATION_1(phySerdesNum), 3, 1, 0x0));
                /* switch clock to local serdes */
                ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x30,0x70, NULL));
                ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x5,(0x1000 + txdivider), NULL));
                /* Serdes External config1 reg bit[3], RFResetIn is de-asserted */
                ATTEMPT(mcdHwSetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_EXTERNAL_CONFIGURATION_1(phySerdesNum), 3, 1, 0x1));
            }
            else
            {
                /* set loopback_clock=ref_clock */
                ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x30, 0, NULL));
            }

            mcdSerdesAccessLock(pDev);
            if (pDev->haAccessDisable == MCD_FALSE)
            {
                mcdWrapperSerdesTxRxEnableSet(pSerdesDev,sAddr,MCD_TRUE, MCD_TRUE, MCD_FALSE);
            }
            mcdSerdesAccessUnlock(pDev);

            /* Clear Shallow Loopback mode */
            mcdSerdesAccessLock(pDev);
            if (pDev->haAccessDisable == MCD_FALSE)
            {
                ATTEMPT(mcdWrapperSetTxPRBS(pSerdesDev, sAddr, AVAGO_SERDES_TX_DATA_SEL_CORE));
            }
            mcdSerdesAccessUnlock(pDev);

            mcdSerdesAccessLock(pDev);
            if (pDev->haAccessDisable == MCD_FALSE)
            {
                mcdWrapperSerdesTxRxEnableSet(pSerdesDev,sAddr,MCD_TRUE, MCD_TRUE, MCD_TRUE);
            }
            mcdSerdesAccessUnlock(pDev);
        }

        break;

    case MCD_DEEP_SERDES_LOOPBACK:/*AN TX_RX*/
        /* disable polarity */
        ATTEMPT(mcdSerdesPolarityConfigImpl(pDev, serdesNum, invertTx, invertRx));

        /* Set Internal Loopback mode */
        mcdSerdesAccessLock(pDev);
        if (pDev->haAccessDisable == MCD_FALSE)
        {
            mcdWrapperSetRxLoopback(pSerdesDev, sAddr, MCD_TRUE);
        }
        mcdSerdesAccessUnlock(pDev);

        mcdSerdesAccessLock(pDev);
        if (pDev->haAccessDisable == MCD_FALSE)
        {
            mcdWrapperSerdesTxRxEnableSet(pSerdesDev,sAddr,MCD_TRUE, MCD_FALSE, MCD_TRUE);
        }
        mcdSerdesAccessUnlock(pDev);

        mcdSerdesAccessLock(pDev);
        if (pDev->haAccessDisable == MCD_FALSE)
        {
            mcdWrapperSerdesTxRxEnableSet(pSerdesDev,sAddr,MCD_TRUE, MCD_TRUE, MCD_TRUE);
        }
        mcdSerdesAccessUnlock(pDev);

        /* Run calibration, whenever serdes Rx_En bit is toggled */
        ATTEMPT(mcdSerdesRxCalibrationConfig(pDev, serdesNum, laneSpeed));

        pDev->serdesStatus.serdesLpbkMode[serdesNum & 7] = MCD_DEEP_SERDES_LOOPBACK;

        break;

    case MCD_SHALLOW_SERDES_LOOPBACK:/*DIG RX_TX*/
        /* Serdes External config1 reg bit[3], RFResetIn is asserted */
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_EXTERNAL_CONFIGURATION_1(phySerdesNum), 3, 1, 0x0));
        /* switch clock to RXDIVX */
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x30, 0x10, NULL));

        if (retimerMode)
        {
            ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x5, mcdBaudRate2DividerValue[laneSpeed], NULL));
        }

        /* Serdes External config1 reg bit[3], RFResetIn is de-asserted */
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_EXTERNAL_CONFIGURATION_1(phySerdesNum), 3, 1, 0x1));

        if (laneSpeed == MCD_25_78125G) {
            ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18, 0x8024, NULL));
            ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, 0x184c, NULL));
        }

        mcdSerdesAccessLock(pDev);
        if (pDev->haAccessDisable == MCD_FALSE)
        {
            mcdWrapperSerdesTxRxEnableSet(pSerdesDev,sAddr,MCD_TRUE, MCD_TRUE, MCD_FALSE);
        }
        mcdSerdesAccessUnlock(pDev);

        /* Set to Shallow Loopback mode */
        mcdSerdesAccessLock(pDev);
        if (pDev->haAccessDisable == MCD_FALSE)
        {
            mcdWrapperSetTxPRBS(pSerdesDev, sAddr, AVAGO_SERDES_TX_DATA_SEL_LOOPBACK);
        }
        mcdSerdesAccessUnlock(pDev);

        mcdSerdesAccessLock(pDev);
        if (pDev->haAccessDisable == MCD_FALSE)
        {
            mcdWrapperSerdesTxRxEnableSet(pSerdesDev,sAddr,MCD_TRUE, MCD_TRUE, MCD_TRUE);
        }
        mcdSerdesAccessUnlock(pDev);

        pDev->serdesStatus.serdesLpbkMode[serdesNum & 7] = MCD_SHALLOW_SERDES_LOOPBACK;

        break;

    default:
        MCD_DBG_ERROR("mcdSerdesSetLoopback: Invalid loopbackMode:%u\n", loopbackMode);
        return MCD_FAIL;
        break;
    }

    MCD_DBG_INFO("mcdSerdesSetLoopback: Completed\n");
#endif

    return MCD_OK;
}

/******************************************************************************
 MCD_STATUS mcdSerdesReset
*******************************************************************************/
MCD_STATUS mcdSerdesReset
(
   IN MCD_DEV_PTR pDev,
   IN MCD_U16 sAddr
)
{
    MCD_U16 serdesNum = MCD_SERDES_FROM_SBUS_ADDR_GET(sAddr);
    return mcdSerdesResetImpl(pDev,serdesNum,MCD_TRUE,MCD_TRUE,MCD_TRUE);
}

/*******************************************************************************
* mcdSerdesDigitalReset
*
* DESCRIPTION:
*       Run digital reset / unreset on current SERDES.
*
* INPUTS:
*       pDev
*       serdesNum - serdes number
*       digitalReset - digital Reset (On/Off)
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesDigitalReset
(
    MCD_DEV_PTR      pDev,
    unsigned int     serdesNum,
    MCD_BOOL         digitalReset
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    digitalReset = digitalReset;
#else

    MCD_U32  data;
    MCD_U32 slice, phySerdesNum;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);
    /* SERDES SD RESET/UNRESET init */
    data = (digitalReset) ? 1 : 0;
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_EXTERNAL_CONFIGURATION_1(phySerdesNum) , 2, 1, data));
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}
#endif /*MV_HWS_REDUCED_BUILD_EXT_CM3*/

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************************
* mcdSerdesTestGen
*
* DESCRIPTION:
*       Activates the Serdes test generator/checker.
*       Can be run after create port.
*
* INPUTS:
*       pDev
*       serdesNum - physical Serdes number
*       txPattern - pattern to transmit ("Other" means HW default - K28.5
*                                        [alternate running disparity])
*       mode      - test mode or normal
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesTestGen
(
   MCD_DEV_PTR              pDev,
   MCD_U16                  serdesNum,
   MCD_SERDES_TX_PATTERN    txPattern,
   MCD_SERDES_TEST_GEN_MODE mode
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    txPattern = txPattern;
    mode = mode;
#else

    MCD_SER_DEV_PTR pSerdesDev;
    unsigned int sbus_addr;
    MCD_SER_RX_CMP_DATA_TYPE  rxPatternData = AVAGO_SERDES_RX_CMP_DATA_OFF;
    MCD_SER_TX_DATA_SEL_TYPE  txPatternData = AVAGO_SERDES_TX_DATA_SEL_CORE;
    long tx_user[4] = {0};
    MCD_U32 widthMode10Bit;
    MCD_U32 slice, phySerdesNum;
    pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;

    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES((MCD_U32)serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC((MCD_U32)serdesNum,phySerdesNum);
    sbus_addr = phySerdesNum + 1;
    /* Read the saved value from AVAGO_SD_METAL_FIX register to check the Rx/Tx width (saved in mcdSerdesPowerCtrlImpl).
       PRBS test in GPCS modes can run only with Rx/Tx width=20BIT. */
    ATTEMPT(mcdHwGetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_Miscellaneous(phySerdesNum) , 9, 1, &widthMode10Bit));
    if ((widthMode10Bit >> 9) == 1)
    {
        /* Change Rx/Tx width mode to 20BIT for GPCS modes */
        mcdSerdesAccessLock(pDev);
        if (pDev->haAccessDisable == MCD_FALSE)
        {
            mcdWrapperSetTxRxWidth(pSerdesDev, sbus_addr, 20, 20);
        }
        mcdSerdesAccessUnlock(pDev);
        MCD_CHECK_RET_CODE(pSerdesDev);
    }

    if (mode == MCD_SERDES_TEST)
    {
        switch (txPattern)
        {
            case MCD_1T:
                tx_user[0] = 0xAAAAA;
                tx_user[1] = 0xAAAAA;
                tx_user[2] = 0xAAAAA;
                tx_user[3] = 0xAAAAA;
                break;
            case MCD_2T:
                tx_user[0] = 0xCCCCC;
                tx_user[1] = 0xCCCCC;
                tx_user[2] = 0xCCCCC;
                tx_user[3] = 0xCCCCC;
                break;
            case MCD_5T:
                tx_user[0] = 0x7C1F;
                tx_user[1] = 0x7C1F;
                tx_user[2] = 0x7C1F;
                tx_user[3] = 0x7C1F;
                break;
            case MCD_10T:
                tx_user[0] = 0x3FF;
                tx_user[1] = 0x3FF;
                tx_user[2] = 0x3FF;
                tx_user[3] = 0x3FF;
                break;
            case MCD_PRBS7:
                txPatternData = AVAGO_SERDES_TX_DATA_SEL_PRBS7;
                rxPatternData = AVAGO_SERDES_RX_CMP_DATA_PRBS7;
                break;
            case MCD_PRBS9:
                txPatternData = AVAGO_SERDES_TX_DATA_SEL_PRBS9;
                rxPatternData = AVAGO_SERDES_RX_CMP_DATA_PRBS9;
                break;
            case MCD_PRBS11:
                txPatternData = AVAGO_SERDES_TX_DATA_SEL_PRBS11;
                rxPatternData = AVAGO_SERDES_RX_CMP_DATA_PRBS11;
                break;
            case MCD_PRBS15:
                txPatternData = AVAGO_SERDES_TX_DATA_SEL_PRBS15;
                rxPatternData = AVAGO_SERDES_RX_CMP_DATA_PRBS15;
                break;
            case MCD_PRBS23:
                txPatternData = AVAGO_SERDES_TX_DATA_SEL_PRBS23;
                rxPatternData = AVAGO_SERDES_RX_CMP_DATA_PRBS23;
                break;
            case MCD_PRBS31:
                txPatternData = AVAGO_SERDES_TX_DATA_SEL_PRBS31;
                rxPatternData = AVAGO_SERDES_RX_CMP_DATA_PRBS31;
                break;
            default:
                return MCD_STATUS_NOT_SUPPORTED;
        }

        /* USER modes txPattern: 1T, 2T, 5T, 10T */
        if (txPattern <= MCD_10T)
        {
            mcdSerdesAccessLock(pDev);
            /* Sets the USER TX data source */
            if (pDev->haAccessDisable == MCD_FALSE)
            {
                mcdWrapperSetTxPRBS(pSerdesDev, sbus_addr, AVAGO_SERDES_TX_DATA_SEL_USER);
            }
            mcdSerdesAccessUnlock(pDev);
            MCD_CHECK_RET_CODE(pSerdesDev);

            mcdSerdesAccessLock(pDev);
            /* Sets the USER pattern to compare incoming data against, Auto-seed to received 40 bit repeating pattern */
            if (pDev->haAccessDisable == MCD_FALSE)
            {
                mcdWrapperSetRxCmpData(pSerdesDev, sbus_addr, AVAGO_SERDES_RX_CMP_DATA_SELF_SEED);
            }
            mcdSerdesAccessUnlock(pDev);
            MCD_CHECK_RET_CODE(pSerdesDev);

            mcdSerdesAccessLock(pDev);
            /* Loads the 80-bit value into the TX user data register */
            if (pDev->haAccessDisable == MCD_FALSE)
            {
                mcdWrapperSetTxUserData(pSerdesDev, sbus_addr, tx_user);
            }
            mcdSerdesAccessUnlock(pDev);
            MCD_CHECK_RET_CODE(pSerdesDev);

            mcdSerdesAccessLock(pDev);
            /* reset counter */
            if (pDev->haAccessDisable == MCD_FALSE)
            {
                mcdWrapperErrorReset(pSerdesDev, sbus_addr);
            }
            mcdSerdesAccessUnlock(pDev);
            MCD_CHECK_RET_CODE(pSerdesDev);
        }
        else /* for PRBS modes */
        {
            mcdSerdesAccessLock(pDev);
            /* Sets the PRBS TX data source */
            if (pDev->haAccessDisable == MCD_FALSE)
            {
                mcdWrapperSetTxPRBS(pSerdesDev, sbus_addr, txPatternData);
            }
            mcdSerdesAccessUnlock(pDev);
            MCD_CHECK_RET_CODE(pSerdesDev);

            mcdSerdesAccessLock(pDev);
            /* Sets the PRBS pattern to compare incoming data against */
            if (pDev->haAccessDisable == MCD_FALSE)
            {
                mcdWrapperSetRxCmpData(pSerdesDev, sbus_addr, rxPatternData);
            }
            mcdSerdesAccessUnlock(pDev);
            MCD_CHECK_RET_CODE(pSerdesDev);

            /* Sets the data comparisons (0x203): Turn on data comparison with Compare Sum and PRBS-generated data */
            ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x3, 0x203, NULL));

            mcdSerdesAccessLock(pDev);
            /* reset counter */
            if (pDev->haAccessDisable == MCD_FALSE)
            {
                mcdWrapperErrorReset(pSerdesDev, sbus_addr);
            }
            mcdSerdesAccessUnlock(pDev);
            MCD_CHECK_RET_CODE(pSerdesDev);
        }
    }
    else /* for SERDES_NORMAL mode */
    {
        if ((widthMode10Bit >> 9) == 1)
        {
            /* Set back the Rx/Tx width mode to 10BIT if it was changed to 20BIT for GPCS modes */
            mcdSerdesAccessLock(pDev);
            if (pDev->haAccessDisable == MCD_FALSE)
            {
                mcdWrapperSetTxRxWidth(pSerdesDev, sbus_addr, 10, 10);
            }
            mcdSerdesAccessUnlock(pDev);
            MCD_CHECK_RET_CODE(pSerdesDev);

            /* perform Serdes Digital Reset/Unreset */
            ATTEMPT(mcdSerdesDigitalReset(pDev, serdesNum, MCD_TRUE));
            /* delay 1ms */
            mcdWrapperMsSleep(1);

            ATTEMPT(mcdSerdesDigitalReset(pDev, serdesNum, MCD_FALSE));
        }

        mcdSerdesAccessLock(pDev);
        /* Sets the TX data source */
        if (pDev->haAccessDisable == MCD_FALSE)
        {
            mcdWrapperSetTxPRBS(pSerdesDev, sbus_addr, AVAGO_SERDES_TX_DATA_SEL_CORE);
        }
        mcdSerdesAccessUnlock(pDev);
        MCD_CHECK_RET_CODE(pSerdesDev);

        mcdSerdesAccessLock(pDev);
        /* Sets the PRBS pattern to compare incoming data against */
        if (pDev->haAccessDisable == MCD_FALSE)
        {
            mcdWrapperSetRxCmpData(pSerdesDev, sbus_addr, AVAGO_SERDES_RX_CMP_DATA_OFF);
        }
        mcdSerdesAccessUnlock(pDev);
        MCD_CHECK_RET_CODE(pSerdesDev);
    }
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}
/*******************************************************************************
* mcdSerdesTestGenGet
*
* DESCRIPTION:
*       Get configuration of the Serdes test generator/checker.
*       Can be run after create port.
*
* INPUTS:
*       pDev
*       serdesNum - physical serdes number
*
* OUTPUTS:
*       txPatternPtr - pattern to transmit ("Other" means any mode not
*                       included explicitly in MV_HWS_SERDES_TX_PATTERN type)
*       modePtr      - test mode or normal
*
* RETURNS:
*       MCD_OK  - on success
*       MCD_NOT_SUPPORTED - unexpected pattern
*       MCD_FAIL - HW error
*
*******************************************************************************/
MCD_STATUS mcdSerdesTestGenGet
(
    MCD_DEV_PTR              pDev,
    MCD_U16                  serdesNum,
    MCD_SERDES_TX_PATTERN    *txPatternPtr,
    MCD_SERDES_TEST_GEN_MODE *modePtr
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    txPatternPtr = txPatternPtr;
    modePtr = modePtr;
#else
    MCD_SER_DEV_PTR pSerdesDev;
    unsigned int sbus_addr;
    MCD_SER_TX_DATA_SEL_TYPE data_sel;
    long tx_user[4] = {0};
    MCD_U32 slice, phySerdesNum;
    pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;

    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES((MCD_U32)serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC((MCD_U32)serdesNum,phySerdesNum);
    sbus_addr = phySerdesNum + 1;
    mcdSerdesAccessLock(pDev);
    data_sel = mcdWrapperGetTxPRBS(pSerdesDev, sbus_addr);
    mcdSerdesAccessUnlock(pDev);
    MCD_CHECK_RET_CODE(pSerdesDev);

    switch(data_sel)
    {
        case AVAGO_SERDES_TX_DATA_SEL_PRBS7:
            *txPatternPtr = MCD_PRBS7;
            break;
        case AVAGO_SERDES_TX_DATA_SEL_PRBS9:
            *txPatternPtr = MCD_PRBS9;
            break;
        case AVAGO_SERDES_TX_DATA_SEL_PRBS11:
            *txPatternPtr = MCD_PRBS11;
            break;
        case AVAGO_SERDES_TX_DATA_SEL_PRBS15:
            *txPatternPtr = MCD_PRBS15;
            break;
        case AVAGO_SERDES_TX_DATA_SEL_PRBS23:
            *txPatternPtr = MCD_PRBS23;
            break;
        case AVAGO_SERDES_TX_DATA_SEL_PRBS31:
            *txPatternPtr = MCD_PRBS31;
            break;
        case AVAGO_SERDES_TX_DATA_SEL_USER: /* User pattern generator */
            mcdSerdesAccessLock(pDev);
            mcdWrapperGetTxUserData(pSerdesDev, sbus_addr, tx_user);
            mcdSerdesAccessUnlock(pDev);
            tx_user[0] = tx_user[0] & 0x3FF;
            tx_user[1] = (tx_user[1] >> 4) & 0x3FFF;

            if (tx_user[0] == 0x2AA)
            {
                *txPatternPtr = MCD_1T;
            }
            else if (tx_user[0] == 0x333)
            {
                *txPatternPtr = MCD_2T;
            }
            else if (tx_user[0] == 0x1F)
            {
                *txPatternPtr = MCD_5T;
            }
            else if ((tx_user[0] == 0x3FF) && (tx_user[1] == 0x3FF0))
            {
                *txPatternPtr = MCD_10T;
            }
            break;
        default:
            *txPatternPtr = MCD_Other;
            break;
    }

    *modePtr = (data_sel == AVAGO_SERDES_TX_DATA_SEL_CORE) ? MCD_SERDES_NORMAL : MCD_SERDES_TEST;
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

/*******************************************************************************
* mcdSerdesTestGenStatus
*
* DESCRIPTION:
*       Read the tested pattern receive error counters.
*       Can be run after create port.
*
* INPUTS:
*       pDev
*       serdesNum - physical serdes number
*       txPattern - pattern to transmit
*       counterAccumulateMode - Enable/Disable reset the accumulation of error counters
*
* OUTPUTS:
*       error counter.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesTestGenStatus
(
    MCD_DEV_PTR                  pDev,
    MCD_U16                      serdesNum,
    MCD_SERDES_TX_PATTERN        txPattern,
    MCD_BOOL                     counterAccumulateMode,
    MCD_SERDES_TEST_GEN_STATUS   *status
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    txPattern = txPattern;
    counterAccumulateMode = counterAccumulateMode;
    mcdMemSet(status,0,sizeof(*status));
#else

    MCD_SER_DEV_PTR pSerdesDev;
    MCD_U32 slice, phySerdesNum;
    MCD_U32 data;
    unsigned int sbus_addr;

    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES((MCD_U32)serdesNum,slice);
    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC((MCD_U32)serdesNum,phySerdesNum);
    sbus_addr = phySerdesNum + 1;
    pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;


    /* avoid warning */
    txPattern = txPattern;

    ATTEMPT(mcdHwGetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_External_Status(phySerdesNum) , 2, 1, &data));

    mcdSerdesAccessLock(pDev);
    /* Retrieves the value of the error counter */
    status->errorsCntr = mcdWrapperGetErrCounter(pSerdesDev, sbus_addr, AVAGO_LSB, 1);
    mcdSerdesAccessUnlock(pDev);
    status->lockStatus = (data) ? 0 : 1; /* if bit[2] is set then there is not signal (and vice versa) */
    status->txFramesCntr.s[0] = 0;
    status->txFramesCntr.s[1] = 0;
    status->txFramesCntr.s[2] = 0;
    status->txFramesCntr.s[3] = 0;

    MCD_CHECK_RET_CODE(pSerdesDev);

    /* reset counter */
    if (counterAccumulateMode == MCD_FALSE)
    {

        mcdSerdesAccessLock(pDev);
        if (pDev->haAccessDisable == MCD_FALSE)
        {
            mcdWrapperErrorReset(pSerdesDev, sbus_addr);
        }
        mcdSerdesAccessUnlock(pDev);
        MCD_CHECK_RET_CODE(pSerdesDev);
    }
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

MCD_STATUS mcdPrbsStartCheck
(
    MCD_DEV_PTR              pDev,
    MCD_U16                  serdesNum
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
#else


    MCD_SERDES_TEST_GEN_STATUS   status = { 0, { .l = { 0, 0 } }, 0 };
    MCD_SERDES_TX_PATTERN txPattern = MCD_PRBS31;

    mcdSerdesTestGen( pDev, serdesNum, txPattern, MCD_SERDES_TEST);
    mcdWrapperMsSleep(10);
    mcdSerdesTestGenStatus(pDev, serdesNum, txPattern,MCD_FALSE,&status);
    if (status.errorsCntr)
    {
        MCD_DBG_ERROR("mcdPrbsStartCheck error COUNT =%d\n",status.errorsCntr);
        return MCD_STATUS_GET_ERROR;
    }
    else
    {
        mcdSerdesTestGen( pDev, serdesNum, txPattern, MCD_SERDES_NORMAL);
    }
#endif
    return MCD_OK;
}

#endif /*MV_HWS_REDUCED_BUILD_EXT_CM3*/

MCD_STATUS mcdSerdesClockRegular
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 serdesNum,
    IN MCD_SERDES_SPEED baudRate       /*  Retimer mode from the list             */
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
    baudRate = baudRate;
#else

    unsigned int txdivider = mcdBaudRate2DividerValue[baudRate];

    /* disable the serdes*/
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x1, 0, NULL));
    /*external PCIE clock*/
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x30, 0, NULL));
    /*divider & 0xff) | (config->refclk_sync_master ? 1<<12 : 0) since config->refclk_sync_master = TRUE =>  divider & 0xff) | 1<<12*/
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x05, ((txdivider & 0xff) | 1 << 12), NULL));
    /* enale the serdes*/
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x1, 7, NULL));

    mcdWrapperMsSleep(10);
#endif
    return MCD_OK;
}

MCD_STATUS mcdSerdesAdaptiveStatusGet
(
    MCD_DEV_PTR                     pDev,
    MCD_U8                          serdesNum,
    MCD_AUTO_TUNE_STATUS            *rxStatus
)
{
#ifdef ASIC_SIMULATION
    /* avoid warnings */
    serdesNum = serdesNum;
#else
    MCD_U16/*int*/ data;

    /* set default to be fail */
    *rxStatus = MCD_TUNE_FAIL;

    /* get DFE status */

    /*MCD_DBG_ERROR("SERDES %d TuneStatus %x\n", serdesNum, data);*/
/* DFE Status has the following bits:
   0 - ICal in progress
   1 - PCal in progress
   4 - ICal pending, signal off
   5 - PCal pending, signal off
   6 - adaptive PCal enabled
   7 - Input Offset correction done
   9 - Electrical idle condition detected during calibration:
       - 1 signal was down or still down,
       - 0 signal OK */

    /*ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x126, ((0 << 12) | (0xB << 8)), &data));*/
    ATTEMPT(mcdSerdesDfeStatusGet(pDev, serdesNum, &data));

    if((data & 0x83)== 0x80) /* bit 7 = 1 and bits 0,1 =0 */
    {
       *rxStatus = MCD_TUNE_PASS;
    }

#endif
    return MCD_OK;
}
/*******************************************************************************
* mcdSerdesRealCdrStateGet
*
* DESCRIPTION:
*       Get serdes CDR lock state.
*
* INPUTS:
*       pSerdesDev
*       serdesNum - SERDES number
*
* OUTPUTS:
*       lockedPtr - locked or not.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesRealCdrStateGet
(
    MCD_DEV_PTR         pDev,
    unsigned int        serdesNum,
    MCD_BOOL            *lockedPtr
)
{
    int  data, prevData, i, diffCount;

    diffCount = 0;
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18, 0x801D, NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x1a, 0x0, &data));
    for (i = 0; (i < 5); i++)
    {
        mcdWrapperMsSleep( 1); /* Delay of 1ms */
        prevData = data;
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x1a, 0x0, &data));
        if (prevData != data)
        {
            diffCount ++;
            break;
        }
    }
    *lockedPtr = (diffCount) ? MCD_TRUE : MCD_FALSE;
    return MCD_OK;
}

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************************
* mcdSerdesDwellTimeSet
*
* DESCRIPTION:
*       Set serdes Dwell time.
*
* INPUTS:
*       pSerdesDev
*       serdesNum - SERDES number
*       time      - 2^time bits to record for every iCal
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesDwellTimeSet
(
    MCD_DEV_PTR         pDev,
    unsigned int        serdesNum,
    unsigned int        time
)
{
    unsigned int        data = (1 << time);

    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18, 0x7, NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, (data & 0xFFFF), NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, ((data >> 16) & 0xFFFF), NULL));
    return MCD_OK;
}
#endif /*#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3*/
/*******************************************************************************
* mcdSerdesNoPpmModeSet
*
* DESCRIPTION:
*       Set host serdes with noPpmMode.
*
* INPUTS:
*       pDev
*       serdesNum - SERDES number.
*       baudRate  - serdes speed.
*       refRxClk  - selects which of the 4 remote lanes RX clock is used.
*       slice     - slice number [0..1].
*       enable    - MCD_TRUE - refernce clock supplied by line side, MCD_FALSE
*       - local reference clock.
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesNoPpmModeSet
(
    MCD_DEV_PTR         pDev,
    unsigned int        serdesNum,
    MCD_SERDES_SPEED    baudRate,
    unsigned int        refRxClk,
    MCD_U8              slice,
    MCD_BOOL            enable
)
{
#ifdef ASIC_SIMULATION
     pDev         = pDev;
     serdesNum  = serdesNum;
     baudRate     = baudRate;
#else
    MCD_U8 txDivider;
    unsigned int interruptData = 0;
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
    unsigned int phySerdesNum;
    MCD_U32 pllRxReady = 0;

    /* convert logic serdes number to physical serdes number */
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);
#endif
    /* SerDes Digital Reset is needed before clocks configuration */
    ATTEMPT(mcdSerdesResetImpl(pDev, serdesNum, MCD_FALSE, MCD_TRUE, MCD_FALSE));
    if (enable)
    {
        if (baudRate == MCD_1_25G)
        {
            /* for noPpm mode, divider value should be still 10 */
            txDivider = 10;
        }
        else
        {
            txDivider = mcdRetimerBaudRate2DividerValue[baudRate];
        }
#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3

        /* select which of the 4 remote lanes RX clock is used as reference to the SERDES TX PLL */
        ATTEMPT(mcdHwSetPhyRegField32bit(
            pDev, DONT_CARE, MCD_SERDES_Miscellaneous(phySerdesNum) , 1, 2, refRxClk));

        mcdWrapperMsSleep(1);

        ATTEMPT(mcdHwGetPhyRegField32bit(
            pDev, DONT_CARE, MCD_SERDES_External_Status(phySerdesNum), 1, 1, &pllRxReady));
        if (pllRxReady == 0)
        {
            MCD_DBG_ERROR("mcdSerdesNoPpmModeSet ERROR: PLL not ready serdes %d\n", serdesNum);
        }
#endif /* MV_HWS_REDUCED_BUILD_EXT_CM3 */
        /*switch clock to local serdes */
        interruptData = 0x70;
    }
    else
    {
        txDivider = mcdBaudRate2DividerValue[baudRate];
    }

    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x30,interruptData, NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x5,(0x1000 + txDivider), NULL));
    /* pcs software reset */
    mcdHwSetPhyRegField32bit(pDev, DONT_CARE, UMAC_GLBL_Software_Reset(slice), 0, 4, (1 << refRxClk /* chan */));
    /* pcs software unreset */
    mcdHwSetPhyRegField32bit(pDev, DONT_CARE, UMAC_GLBL_Software_Reset(slice), 0, 4, 0);

#endif
    return MCD_OK;
}

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/*******************************************************************************
* mcdSerdesCtleBiasUpdateDB
*
* DESCRIPTION:
*       Update CTLE BIAS data base per serdes.
*
* INPUTS:
*       pDev
*       serdesNum - SERDES number.
*       ctleBiasVal  - ctle bias value [0..1].
*       host_or_line  - host/line serdes.
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
MCD_STATUS mcdSerdesCtleBiasUpdateDB
(
    MCD_DEV_PTR         pDev,
    unsigned int        serdesNum,
    MCD_U16             ctleBiasVal,
    MCD_U8              host_or_line
)
{
#ifndef ASIC_SIMULATION
    switch (host_or_line)
    {
    case MCD_HOST_SIDE:
        pDev->serdesStatus.ctleBiasData[serdesNum + MCD_HOST_SIDE_START_SERDES_NUMBER] = ctleBiasVal;
        break;
    case MCD_LINE_SIDE:
        pDev->serdesStatus.ctleBiasData[serdesNum] = ctleBiasVal;
        break;
    default:
        return MCD_STATUS_BAD_PARAM;
    }
#endif
    return MCD_OK;
}

/**
* @internal mcdLaneSteeringOtherSideCfg function
* @endinternal
*
* @brief   power up slave slice in lane steering mode
*
* @param[in] pDev                     - device pointer
* @param[in] mdioPort                 - mdio port
* @param[in] portMode                 - port mode
* @param[in] masterSlice              - master slice
* @param[in] baud rate                 - serdes baud rate
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdLaneSteeringOtherSideCfg
(
    MCD_DEV_PTR    pDev,
    MCD_U16        mdioPort,
    MCD_OP_MODE    portMode,
    MCD_MASTER_SLICE  masterSlice,
    MCD_SERDES_SPEED  baudRate
)
{
    MCD_U8 i, serdesNum, lpSerdes;
    MCD_U8 slavePort;
    MCD_U8 portsToStop;
    MCD_U16 lanesNum = 0;
    MCD_U8 lpSerdesLength = 4;
    MCD_U8 secSlavePort = 0; /* initalize to avoid warrnings */
    MCD_U8 secLpSerdes = 0; /* initalize to avoid warrnings */

    if (masterSlice > MCD_SLICE1)
    {
        MCD_DBG_ERROR("mcdLaneSteeringOtherSideCfg ERROR: wrong value of masterSlice %d\n", masterSlice);
        return MCD_FAIL;
    }

    if (pDev->laneSteeringCfg.singlePortEnable[mdioPort])
    {
        lpSerdes = pDev->laneSteeringCfg.externalLpSerdes[mdioPort];
        secLpSerdes = pDev->laneSteeringCfg.internalLpSerdes[mdioPort];
        slavePort = pDev->laneSteeringCfg.externalLpPort[mdioPort];
        secSlavePort = pDev->laneSteeringCfg.internalLpPort[mdioPort];
    }
    else
    {
        lpSerdes = (masterSlice == MCD_SLICE0 ? 12 : 8);
        slavePort = (masterSlice == MCD_SLICE0 ? 4 : 0);
        lanesNum = mcdPortModeGetLanesNum(portMode, MCD_HOST_SIDE);
    }



    /* for ports that are mapped directly to the ASIC we don't need the loopback serdes lanes */
    if (slavePort != MCD_LANE_STEERING_NO_LPB)
    {
        if (pDev->laneSteeringCfg.singlePortEnable[mdioPort])
        {
            ATTEMPT(mcdPortStop(pDev, slavePort, portMode));
            ATTEMPT(mcdPortStop(pDev, secSlavePort, portMode));
            pDev->portConfig[slavePort].portMode = portMode;
            pDev->portConfig[secSlavePort].portMode = portMode;

            /* power up loopback serdes's */
            ATTEMPT(mcdSerdesPowerCtrl(pDev, lpSerdes, MCD_TRUE, baudRate, MCD_FALSE, (MCD_U32)MCD_PRIMARY_CLK, (MCD_U32)MCD_REF_CLK_NO_DIV));
            ATTEMPT(mcdSerdesPowerCtrl(pDev, secLpSerdes, MCD_TRUE, baudRate, MCD_FALSE, (MCD_U32)MCD_PRIMARY_CLK, (MCD_U32)MCD_REF_CLK_NO_DIV));

            ATTEMPT(mcdSerdesTxEnable(pDev, lpSerdes, MCD_TRUE));
            ATTEMPT(mcdSerdesTxEnable(pDev, secLpSerdes, MCD_TRUE));

            /* set parallel loopback */
            ATTEMPT(mcdSerdesSetLoopback(pDev, (lpSerdes + 1), MCD_PARALLEL_SERDES_LOOPBACK));
            ATTEMPT(mcdSerdesSetLoopback(pDev, (secLpSerdes + 1), MCD_PARALLEL_SERDES_LOOPBACK));
        }
        else
        {
            switch (lanesNum)
            {
            case 1:
                portsToStop = 4;
                break;
            case 2:
                portsToStop = 2;
                break;
            case 4:
                portsToStop = 1;
                break;
            default:
                return MCD_FAIL;
            }

            for (i = 0; i < portsToStop; i++)
            {
                ATTEMPT(mcdPortStop(pDev, i + slavePort, portMode));
            }
            /*update other slice port data*/
            for (i = slavePort ; i < slavePort + lpSerdesLength; i++)
            {
               pDev->portConfig[i].portMode = portMode;
            }

            /* power up loopback serdes's */
            for ( serdesNum = lpSerdes; serdesNum < (lpSerdes + lpSerdesLength); serdesNum++)
            {
                ATTEMPT(mcdSerdesPowerCtrl(pDev, serdesNum, MCD_TRUE, baudRate, MCD_FALSE, (MCD_U32)MCD_PRIMARY_CLK, (MCD_U32)MCD_REF_CLK_NO_DIV));
            }
            for ( serdesNum = lpSerdes; serdesNum < (lpSerdes + lpSerdesLength); serdesNum++)
            {
                ATTEMPT(mcdSerdesTxEnable(pDev, serdesNum, MCD_TRUE));
            }

            /* set parallel loopback */
            for ( serdesNum = lpSerdes; serdesNum < (lpSerdes + lpSerdesLength); serdesNum++)
            {
                ATTEMPT(mcdSerdesSetLoopback(pDev, (serdesNum + 1), MCD_PARALLEL_SERDES_LOOPBACK));
            }
        }
    }


    return MCD_OK;
}

MCD_STATUS mcdLaneSteeringAutoTuneStart
(
    MCD_DEV_PTR    pDev,
    MCD_U16        slice,
    MCD_MASTER_SLICE  masterSlice
)
{
    MCD_U8 rxDstSerdes, vsrSerdes;
    MCD_AUTO_TUNE_STATUS rxStatus = MCD_TUNE_FAIL;
    MCD_U8 lpSerdes, serdesNum;

    lpSerdes = (masterSlice == MCD_SLICE0 ? 12 : 8);
    /* start iCal on rx destination serdes's */
    /* slice 0*/
    if (((masterSlice == MCD_DUAL_SLICE) && (slice == 0)) || (masterSlice != MCD_DUAL_SLICE))
    {
        for (rxDstSerdes = MCD_HOST_SIDE_START_SERDES_NUMBER; rxDstSerdes < (MCD_HOST_SIDE_START_SERDES_NUMBER + 4); rxDstSerdes += 3)
        {
            ATTEMPT(mcdSerdesAutoTuneStartExt(pDev,rxDstSerdes, MCD_ONE_SHOT_DFE_TUNING, MCD_IGNORE_TX_TRAINING));
        }
    }
    /* slice 1*/
    if (((masterSlice == MCD_DUAL_SLICE) && (slice == 1)) || (masterSlice != MCD_DUAL_SLICE))
    {
        for (rxDstSerdes = MCD_HOST_SIDE_START_SERDES_NUMBER + 4; rxDstSerdes < (MCD_HOST_SIDE_START_SERDES_NUMBER + 8); rxDstSerdes += 3)
        {
            ATTEMPT(mcdSerdesAutoTuneStartExt(pDev,rxDstSerdes, MCD_ONE_SHOT_DFE_TUNING, MCD_IGNORE_TX_TRAINING));
        }
    }

    if (pDev->highAvailabilityMode == MCD_FALSE)
    {
        /* verify iCal is finished before running pCal for slice 0 */
        if (((masterSlice == MCD_DUAL_SLICE) && (slice == 0)) || (masterSlice != MCD_DUAL_SLICE))
        {
            for (rxDstSerdes = MCD_HOST_SIDE_START_SERDES_NUMBER; rxDstSerdes < (MCD_HOST_SIDE_START_SERDES_NUMBER + 4); rxDstSerdes += 3)
            {
                ATTEMPT(mcdSerdesAutoTuneStatus(pDev, rxDstSerdes, &rxStatus, NULL));
                if (rxStatus != MCD_TUNE_PASS)
                {
                    MCD_DBG_ERROR("mcdSetLaneSteering: AutoTuneStatus fail, serdesNum %d \n", rxDstSerdes);
                    return MCD_FAIL;
                }
            }
        }

        if (((masterSlice == MCD_DUAL_SLICE) && (slice == 1)) || (masterSlice != MCD_DUAL_SLICE))
        {
            /* verify iCal is finished before running pCal for slice 1 */
            for (rxDstSerdes = MCD_HOST_SIDE_START_SERDES_NUMBER+4; rxDstSerdes < (MCD_HOST_SIDE_START_SERDES_NUMBER + 8); rxDstSerdes += 3 )
            {
                ATTEMPT(mcdSerdesAutoTuneStatus(pDev, rxDstSerdes, &rxStatus, NULL));
                if (rxStatus != MCD_TUNE_PASS)
                {
                    MCD_DBG_ERROR("mcdSetLaneSteering: AutoTuneStatus fail, serdesNum %d \n", rxDstSerdes);
                    return MCD_FAIL;
                }
            }
        }
    }

    mcdWrapperMsSleep(500);

    /* start adaptive pCal training on rx destination serdes's */
    if (((masterSlice == MCD_DUAL_SLICE) && (slice == 0)) || (masterSlice != MCD_DUAL_SLICE))
    {
        for (rxDstSerdes = MCD_HOST_SIDE_START_SERDES_NUMBER; rxDstSerdes < (MCD_HOST_SIDE_START_SERDES_NUMBER + 4); rxDstSerdes += 3)
        {
            ATTEMPT(mcdSerdesAutoTuneStartExt(pDev,rxDstSerdes,  MCD_START_CONTINUE_ADAPTIVE_TUNING, MCD_IGNORE_TX_TRAINING));
        }
    }
    if (((masterSlice == MCD_DUAL_SLICE) && (slice == 1)) || (masterSlice != MCD_DUAL_SLICE))
    {
        for (rxDstSerdes = MCD_HOST_SIDE_START_SERDES_NUMBER + 4; rxDstSerdes < (MCD_HOST_SIDE_START_SERDES_NUMBER + 8); rxDstSerdes += 3)
        {
            ATTEMPT(mcdSerdesAutoTuneStartExt(pDev,rxDstSerdes, MCD_START_CONTINUE_ADAPTIVE_TUNING, MCD_IGNORE_TX_TRAINING));
        }
    }

    if (masterSlice != MCD_DUAL_SLICE)
    {
        for (vsrSerdes = MCD_HOST_SIDE_START_SERDES_NUMBER + 1; vsrSerdes < (MCD_HOST_SIDE_START_SERDES_NUMBER + 3); vsrSerdes++)
        {
            ATTEMPT(mcdSerdesAutoTuneStartExt(pDev,vsrSerdes, MCD_ONE_SHOT_DFE_TUNING, MCD_IGNORE_TX_TRAINING));
        }
        for (vsrSerdes = MCD_HOST_SIDE_START_SERDES_NUMBER+5; vsrSerdes < (MCD_HOST_SIDE_START_SERDES_NUMBER + 7); vsrSerdes++)
        {
            ATTEMPT(mcdSerdesAutoTuneStartExt(pDev,vsrSerdes, MCD_ONE_SHOT_DFE_TUNING, MCD_IGNORE_TX_TRAINING));
        }
        /* verify iCal tuning is finished */
        for (vsrSerdes = MCD_HOST_SIDE_START_SERDES_NUMBER+1; vsrSerdes < (MCD_HOST_SIDE_START_SERDES_NUMBER + 3); vsrSerdes++ )
        {
            ATTEMPT(mcdSerdesAutoTuneStatus(pDev, vsrSerdes, &rxStatus, NULL));
            if (rxStatus != MCD_TUNE_PASS)
            {
                MCD_DBG_ERROR("mcdSetLaneSteering: AutoTuneStatus fail, serdesNum %d \n", vsrSerdes);
                return MCD_FAIL;
            }
        }
        for (vsrSerdes = MCD_HOST_SIDE_START_SERDES_NUMBER+5; vsrSerdes < (MCD_HOST_SIDE_START_SERDES_NUMBER + 7); vsrSerdes++ )
        {
            ATTEMPT(mcdSerdesAutoTuneStatus(pDev, vsrSerdes, &rxStatus, NULL));
            if (rxStatus != MCD_TUNE_PASS)
            {
                MCD_DBG_ERROR("mcdSetLaneSteering: AutoTuneStatus fail, serdesNum %d \n", vsrSerdes);
                return MCD_FAIL;
            }
        }

        for ( serdesNum = lpSerdes; serdesNum < (lpSerdes + 4); serdesNum++)
        {
            ATTEMPT(mcdSerdesSetLoopback(pDev, (serdesNum + 1), MCD_PARALLEL_SERDES_LOOPBACK));
        }

        mcdWrapperMsSleep(50);
    }

    return MCD_OK;
}

/**
* @internal mcdSerdesTxPowerCtrl function
* @endinternal
*
* @brief   power up/down SerDes Tx direction
*
* @param[in] pDev                     - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] serdesNum                - serdes number
* @param[in] powerUp                  - power up/down
* @param[in] baudRate                 - serdes baud rate
* @param[in] retimerMode              - retimer enable/disable
* @param[in] refClkSel                - reference clock
* @param[in] refClkDiv                - reference clock divider
*
* @retval MCD_OK                   - on success
* @retval MCD_FAIL                 - on error
*/
int mcdSerdesTxPowerCtrl
(
    MCD_DEV_PTR         pDev,
    unsigned int        serdesNum,
    unsigned char       powerUp,
    MCD_SERDES_SPEED    baudRate,
    MCD_BOOL            retimerMode,
    MCD_U32             refClkSel,
    MCD_U32             refClkDiv
)
{
#ifndef ASIC_SIMULATION
    Avago_serdes_init_config_t *config;
    MCD_TX_RX_SERDES_SW_DB *txRxSerdesSwDbPtr;
    unsigned int txdivider, sbus_addr;
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    MCD_U32 slice = 0;
    unsigned int phySerdesNum;

    /* use tx remap vector instead of rx vector */
    pDev->laneSteeringCfg.laneSteeringTxRemap[serdesNum] = MCD_TRUE;
    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    MCD_LOGIC_TO_PHYSICAL_SERDES_TX_MAC(serdesNum,phySerdesNum);

    sbus_addr = phySerdesNum + 1;

    /* allocate serdes SW data base to support Tx/Rx seperate operation */
    ATTEMPT(mcdSerdesTxRxAllocateSwDb(pDev,phySerdesNum));
    txRxSerdesSwDbPtr = &(pDev->txRxSerdesSwDb);

   /* for Serdes PowerDown */
    if (powerUp == MCD_FALSE)
    {
        /* turn serdes off */
        ATTEMPT(mcdSerdesTxRxEnableSet(pDev, serdesNum, MCD_FALSE, txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->serdesTxRxEnable.rxEnable,
                                        MCD_FALSE));
        /* update TX SW DB values */
        txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->serdesTxRxEnable.txEnable = MCD_FALSE;
        txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->serdesTxRxEnable.txOutputEnable = MCD_FALSE;

        /* TxClk/RxClk Tlat_en=0. Return to default */
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_EXTERNAL_CONFIGURATION_0(phySerdesNum), 14, 1, 0));

        if (retimerMode)
        {
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_EXTERNAL_CONFIGURATION_0(phySerdesNum), 3, 3, 0));
            /* digital reset TX only */
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_EXTERNAL_CONFIGURATION_1(phySerdesNum), 3, 1, 0));
            /*Configure the serdes PCIE clock mux using the SD1 Miscellaneous register bits [2:1]*/
            ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_Miscellaneous(phySerdesNum) , 1, 2, 0));
        }
       /* Serdes Reset - not modigying analog reset, just digital reset (affect TX only) and syncE reset*/
        ATTEMPT(mcdSerdesResetImpl(pDev, serdesNum, MCD_FALSE, MCD_TRUE, MCD_TRUE));

        /* return remap mode to rx vector */
        pDev->laneSteeringCfg.laneSteeringTxRemap[serdesNum] = MCD_FALSE;
        return MCD_OK;
    }

    /* Power On !!!!!!!!*/

    /*Serdes external conf1 bits[3:2]=0x01 (serdes analog unreset ,digital still in reset)*/
    /* digital is for TX only */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_EXTERNAL_CONFIGURATION_1(phySerdesNum), 2, 2, 0x01));

    /* for Serdes PowerUp */
    /* Initialize the SerDes slice */
    if (!(txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->txRxConfigInitalized))
    {
        mcdWrapperSerdesInitConfig(&(txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->txRxConfigDef));
        txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->txRxConfigInitalized= MCD_TRUE;
    }
    config = &(txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->txRxConfigDef);

    txdivider = mcdBaudRate2DividerValue[baudRate];

    if (txdivider == NA_VALUE)
    {
        MCD_DBG_ERROR("mcdSerdesTxPowerCtrl no txdivider for baudRate %d. \n", baudRate);
        return MCD_STATUS_BAD_PARAM;
    }

    config->tx_divider = txdivider;

    /* initializes the Avago_serdes_init_config_t struct */
    config->sbus_reset = FALSE;
    config->signal_ok_threshold = MCD_SERDES_DEFAILT_SIGNAL_OK_THRESHOLD;

    /* Select the Tx data path width */
    if (baudRate == MCD_1_25G) /* mode is 10BIT_ON)*/
    {
        /*config->tx_width =*/ config->tx_width = 10;
    }
    else if((baudRate == MCD_10_3125G) || (baudRate == MCD_12_1875G) || (baudRate == MCD_3_125G))       /* for 3_125G 11.8G, 23.6G, 47.2G */
        /*config->tx_width = */config->tx_width = 20;

    else
    /* (mode =_40BIT_ON)*/
           /*config->tx_width = */config->tx_width = 40;

    config->init_mode = AVAGO_INIT_ONLY;
    MCD_DBG_INFO("mcdSerdesTxPowerCtrlImpl init_configuration: physical serdes %d\n",phySerdesNum);
    MCD_DBG_INFO("   sbus_reset = %x \n",config->sbus_reset);
    MCD_DBG_INFO("   init_tx = %x \n",config->init_tx);
    MCD_DBG_INFO("   init_rx = %x \n",config->init_rx);
    MCD_DBG_INFO("   init_mode = %x \n",config->init_mode);
    MCD_DBG_INFO("   tx_divider = 0x%x \n",config->tx_divider);
    MCD_DBG_INFO("   rx_divider = 0x%x \n",config->rx_divider);
    MCD_DBG_INFO("   tx_width = 0x%x \n",config->tx_width);
    MCD_DBG_INFO("   rx_width = 0x%x \n",config->rx_width);
    MCD_DBG_INFO("   tx_phase_cal = %x \n",config->tx_phase_cal);
    MCD_DBG_INFO("   tx_output_en = %x \n",config->tx_output_en);
    MCD_DBG_INFO("   signal_ok_en = %x \n",config->signal_ok_en);
    MCD_DBG_INFO("   signal_ok_threshold= %x \n",config->signal_ok_threshold);

    /* Serdes Analog Un Reset*/
    ATTEMPT(mcdSerdesResetImpl(pDev, serdesNum, MCD_FALSE, MCD_TRUE, MCD_TRUE));

    /* Reference clock source */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_EXTERNAL_CONFIGURATION_0(phySerdesNum), 8, 1, refClkSel));
    /* Reference clock divider */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_EXTERNAL_CONFIGURATION_0(phySerdesNum), 11, 2, refClkDiv));

    /* TxClk/RxClk Tlat_en=1. The logic of the Tlat need to be 1 in order to enable Clk to MAC/PCS regardless of Serdes readiness */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_EXTERNAL_CONFIGURATION_0(phySerdesNum), 14, 1, 1));

    /* implementing avago_serdes_init for TX path only */
    ATTEMPT(mcdSerdesTxRxEnableSet(pDev, serdesNum, MCD_FALSE, txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->serdesTxRxEnable.rxEnable,
                                        MCD_FALSE));
    /* update TX SW DB */
    txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->serdesTxRxEnable.txEnable = MCD_FALSE;
    txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->serdesTxRxEnable.txOutputEnable = MCD_FALSE;

    txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->txRxPllRecal |= MCD_TX_PLL_RECAL;
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x11, txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->txRxPllRecal, NULL));

    /* enable TX phase calibration */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0xB, 0x0, NULL));
    /* set TX Divider */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x5, (config->tx_divider & 0xff) | (config->refclk_sync_master ? 1<<12 : 0), NULL));

    mcdSerdesAccessLock(pDev);
    if (pDev->haAccessDisable == MCD_FALSE)
    {
        mcdWrapperSetTxRxWidth(pSerdesDev,sbus_addr,config->tx_width, config->rx_width);
    }
    mcdSerdesAccessUnlock(pDev);

    ATTEMPT(mcdSerdesTxRxEnableSet(pDev, serdesNum, MCD_TRUE, txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->serdesTxRxEnable.rxEnable,
                                        MCD_TRUE));
    txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->serdesTxRxEnable.txEnable = MCD_TRUE;
    txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->serdesTxRxEnable.txOutputEnable = MCD_TRUE;

    mcdSerdesAccessLock(pDev);
    if (pDev->haAccessDisable == MCD_FALSE)
    {
        /*set the polarity - it is not hanled in SerdeInit*/
        mcdWrapperSetTxPolarity(pSerdesDev, (sbus_addr), serdesElectricalParams[serdesNum].txPolarity);
    }
    mcdSerdesAccessUnlock(pDev);
    MCD_CHECK_RET_CODE1(pSerdesDev,sbus_addr);

    if (mcdWrapperGetReturnCode(pSerdesDev) == 0)
    {
        MCD_DBG_INFO("The SerDes at address 0x%x is initialized.\n", sbus_addr);
    }

    if (vcoSerdesCal != AVAGO_SERDES_INIT_BYPASS_VCO)
    {
        MCD_STATUS     res;
        int serdesTemperature, coreTemperature;
        int txTherm, txBin;

        /* get the Avago Serdes Temperature (in C) */
        ATTEMPT(mcdSerdesGetTemperature(pDev, &serdesTemperature, &coreTemperature));

        /* get the calibration code(value) for Tx */
        ATTEMPT(mcdSerdesCalCodeGet(pDev, serdesNum, MCD_TRUE, &txTherm, &txBin));

        /* Compensate the VCO calibration value according to Temperature */
        res = mcdSerdesVcoTxConfig(pDev,serdesNum, serdesTemperature, txTherm, txBin);
        if (res != MCD_OK)
        {
            MCD_DBG_INFO("mcdSerdesVcoConfig failed (%d)\n", res);
            return MCD_FAIL;
        }
    }

    /*clear pending interrupts both*/
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18, 0x8000, NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, 2, NULL));


#ifdef MV_HWS_REDUCED_BUILD_EXT_CM3
    if (baudRate == MCD_3_125G)
    {
       /* Improve the CDR lock process */
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18,0x40FB, NULL));
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19,0x1200, NULL));
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18,0x40A9, NULL));
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19,0x1100, NULL));
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18,0x4001, NULL));
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19,0x41FF, NULL));
    }
#endif

    ATTEMPT(mcdSerdesManualTxConfig( pDev, serdesNum, serdesElectricalParams[serdesNum].attenuation,
                                 serdesElectricalParams[serdesNum].postCursor, serdesElectricalParams[serdesNum].preCursor));

    /* when retimer mode is on, digital reset is applied */
    ATTEMPT(mcdSerdesResetImpl(pDev, serdesNum, MCD_FALSE, retimerMode, MCD_FALSE));

    /* set remap mode to rx - back to default */
    pDev->laneSteeringCfg.laneSteeringTxRemap[serdesNum] = MCD_FALSE;

#endif /* ASIC_SIMULATION*/
    return MCD_OK;
}

/**
* @internal mcdSerdesRxPowerCtrl function
* @endinternal
*
* @brief   power up/down SerDes Rx direction
*
* @param[in] pDev                     - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] serdesNum                - serdes number
* @param[in] powerUp                  - power up/down
* @param[in] baudRate                 - serdes baud rate
* @param[in] retimerMode              - retimer enable/disable
* @param[in] refClkSel                - reference clock
* @param[in] refClkDiv                - reference clock divider
*
* @retval MCD_OK                   - on success
* @retval MCD_FAIL                 - on error
*/
int mcdSerdesRxPowerCtrl
(
    MCD_DEV_PTR         pDev,
    unsigned int        serdesNum,
    unsigned char       powerUp,
    MCD_SERDES_SPEED    baudRate,
    MCD_BOOL            retimerMode,
    MCD_U32             refClkSel,
    MCD_U32             refClkDiv
)
{
#ifndef ASIC_SIMULATION
    Avago_serdes_init_config_t *config;
    MCD_TX_RX_SERDES_SW_DB *txRxSerdesSwDbPtr;
    unsigned int rxdivider,dwell,sbus_addr;
    unsigned int tryCount;
    int data;
    MCD_U32 regData = 0;
    MCD_SER_DEV_PTR pSerdesDev = (MCD_SER_DEV_PTR)pDev->serdesDev;
    MCD_U32 slice = 0;
    unsigned int phySerdesNum;

    /* get slice number */
    MCD_GET_SLICE_NUM_BY_SERDES(serdesNum,slice);
    MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(serdesNum,phySerdesNum);


    sbus_addr = phySerdesNum + 1;

    /* allocate serdes SW date base to support Tx/Rx seperate operation */
    ATTEMPT(mcdSerdesTxRxAllocateSwDb(pDev,phySerdesNum));
    txRxSerdesSwDbPtr = &(pDev->txRxSerdesSwDb);

   /* for Serdes PowerDown */
    if (powerUp == MCD_FALSE)
    {
        /* if Training is in progress give it chance to finish and turn serdes off anyway */
        ATTEMPT(mcdHwGetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_Core_Status(phySerdesNum), 1, 1, &regData));
        tryCount = 0;
        while (regData && (tryCount++ < 5))
        {
           ATTEMPT(mcdHwGetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_Core_Status(phySerdesNum), 1, 1, &regData));
        }
        /* turn serdes off */
        ATTEMPT(mcdSerdesTxRxEnableSet(pDev, serdesNum, txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->serdesTxRxEnable.txEnable,
                                       MCD_FALSE, txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->serdesTxRxEnable.txOutputEnable));
        /* update RX SerDes SW DB */
        txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->serdesTxRxEnable.rxEnable = MCD_FALSE;
        /* TxClk/RxClk Tlat_en=0. Return to default */
        ATTEMPT(mcdHwSetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_EXTERNAL_CONFIGURATION_0(phySerdesNum), 13, 1, 0));

        return MCD_OK;
    }

    /* Power On !!!!!!!!*/

    ATTEMPT(mcdHwSetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_EXTERNAL_CONFIGURATION_1(phySerdesNum), 2, 1, 0x01));

    /* for Serdes PowerUp */
    /* Initialize the SerDes slice */

    if (!(txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->txRxConfigInitalized))
    {
        mcdWrapperSerdesInitConfig(&(txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->txRxConfigDef));
        txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->txRxConfigInitalized = MCD_TRUE;
    }
    config = &(txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->txRxConfigDef);

    rxdivider = mcdBaudRate2DividerValue[baudRate];

    if (rxdivider == NA_VALUE)
    {
        MCD_DBG_ERROR("mcdSerdesRxPowerCtrl no rxdivider for baudRate %d. \n", baudRate);
        return MCD_STATUS_BAD_PARAM;
    }

    config->rx_divider = rxdivider;
    /* initializes the Avago_serdes_init_config_t struct */
    config->sbus_reset = FALSE;
    config->signal_ok_threshold = MCD_SERDES_DEFAILT_SIGNAL_OK_THRESHOLD;

    /* Select the Rx data path width */
    if (baudRate == MCD_1_25G) /* mode is 10BIT_ON)*/
    {
        config->rx_width = /*config->tx_width =*/ 10;
    }
    else if((baudRate == MCD_10_3125G) || (baudRate == MCD_12_1875G) || (baudRate == MCD_3_125G))       /* for 3_125G 11.8G, 23.6G, 47.2G */
    {
        config->rx_width = /*config->tx_width = */20;
    }
    else
    {
    /* (mode =_40BIT_ON)*/
           config->rx_width =/* config->tx_width = */40;
    }

    config->init_mode = AVAGO_INIT_ONLY;
    MCD_DBG_INFO("mcdSerdesPowerCtrlImpl init_configuration: physical serdes %d\n",phySerdesNum);
    MCD_DBG_INFO("   sbus_reset = %x \n",config->sbus_reset);
    MCD_DBG_INFO("   init_tx = %x \n",config->init_tx);
    MCD_DBG_INFO("   init_rx = %x \n",config->init_rx);
    MCD_DBG_INFO("   init_mode = %x \n",config->init_mode);
    MCD_DBG_INFO("   tx_divider = 0x%x \n",config->tx_divider);
    MCD_DBG_INFO("   rx_divider = 0x%x \n",config->rx_divider);
    MCD_DBG_INFO("   tx_width = 0x%x \n",config->tx_width);
    MCD_DBG_INFO("   rx_width = 0x%x \n",config->rx_width);
    MCD_DBG_INFO("   tx_phase_cal = %x \n",config->tx_phase_cal);
    MCD_DBG_INFO("   tx_output_en = %x \n",config->tx_output_en);
    MCD_DBG_INFO("   signal_ok_en = %x \n",config->signal_ok_en);
    MCD_DBG_INFO("   signal_ok_threshold= %x \n",config->signal_ok_threshold);

     /* Reference clock source */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_EXTERNAL_CONFIGURATION_0(phySerdesNum), 8, 1, refClkSel));
     /* Reference clock divider */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev, DONT_CARE, MCD_SERDES_EXTERNAL_CONFIGURATION_0(phySerdesNum), 11, 2, refClkDiv));

    /* RxClk Tlat_en=1. The logic of the Tlat need to be 1 in order to enable Clk to MAC/PCS regardless of Serdes readiness */
    ATTEMPT(mcdHwSetPhyRegField32bit(pDev,DONT_CARE,MCD_SERDES_EXTERNAL_CONFIGURATION_0(phySerdesNum), 13, 1, 1));

    /* implementing avago_serdes_init RX Path */
    ATTEMPT(mcdSerdesTxRxEnableSet(pDev, serdesNum, txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->serdesTxRxEnable.txEnable,
                                   MCD_FALSE, txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->serdesTxRxEnable.txOutputEnable));
    /* update RX software data base */
    txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->serdesTxRxEnable.rxEnable = MCD_FALSE;

    /* config RX_PLL_RECAL must not override the existing value */
    txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->txRxPllRecal |= MCD_RX_PLL_RECAL;

    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x11, txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->txRxPllRecal, NULL));

    /* set RX divider */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x6, config->rx_divider & 0xff, NULL));

    mcdSerdesAccessLock(pDev);
    if (pDev->haAccessDisable == MCD_FALSE)
    {
        mcdWrapperSetTxRxWidth(pSerdesDev,sbus_addr,config->tx_width, config->rx_width);
    }
    mcdSerdesAccessUnlock(pDev);

    ATTEMPT(mcdSerdesTxRxEnableSet(pDev, serdesNum, txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->serdesTxRxEnable.txEnable,
                                   MCD_TRUE, txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->serdesTxRxEnable.txOutputEnable));
    txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[phySerdesNum]->serdesTxRxEnable.rxEnable = MCD_TRUE;


    mcdSerdesAccessLock( pDev);
    if (pDev->haAccessDisable == MCD_FALSE)
    {
        mcdWrapperInitSignalOk(pSerdesDev, sbus_addr, config->signal_ok_threshold);
        mcdWrapperSetRxLoopback(pSerdesDev,sbus_addr,MCD_FALSE);
        /*set the polarity - it is not hanled in SerdeInit*/
        mcdWrapperSetRxPolarity(pSerdesDev, (sbus_addr), serdesElectricalParams[serdesNum].rxPolarity);
    }
    mcdSerdesAccessUnlock( pDev);
    MCD_CHECK_RET_CODE1(pSerdesDev,sbus_addr);


    if (vcoSerdesCal != AVAGO_SERDES_INIT_BYPASS_VCO)
    {
        MCD_STATUS     res;
        int serdesTemperature, coreTemperature;
        int rxTherm, rxBin;

        /* get the Avago Serdes Temperature (in C) */
        ATTEMPT(mcdSerdesGetTemperature(pDev, &serdesTemperature, &coreTemperature));

        /* get the calibration code(value) for Rx */
        ATTEMPT(mcdSerdesCalCodeGet(pDev,serdesNum, MCD_FALSE , &rxTherm, &rxBin));

        /* Compensate the VCO calibration value according to Temperature */
        res = mcdSerdesVcoRxConfig(pDev,serdesNum, serdesTemperature, rxTherm, rxBin);
        if (res != MCD_OK)
        {
            MCD_DBG_INFO("mcdSerdesVcoConfig failed (%d)\n", res);
            return MCD_FAIL;
        }
    }

    /* Disable TAP1 before training */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x26, 0x5B00, NULL));

    /* change CTLE bias from 1 to 0 */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18, 0x4033, NULL));

    /* read the CTLE bias */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x1A, 0x0, &data));
    if (pDev->serdesStatus.ctleBiasData[serdesNum])
    {
        /* set CTLE bias to 1 */
        data |= 0x1000;
    }
    else
    {
        /* set CTLE bias to 0 to */
        data &= 0xCFFF;
    }
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, data, NULL));

    /*clear pending interrupts */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18, 0x8000, NULL));
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, 2, NULL));

#ifdef MV_HWS_REDUCED_BUILD_EXT_CM3
    if (baudRate == MCD_3_125G)
    {
       /* Improve the CDR lock process */
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18,0x40FB, NULL));
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19,0x1200, NULL));
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18,0x40A9, NULL));
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19,0x1100, NULL));
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18,0x4001, NULL));
        ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19,0x41FF, NULL));
    }
#endif


#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
    ATTEMPT(mcdSerdesManualCtleConfig (pDev, serdesNum,
                                    serdesCtleParams[serdesNum].dcGain, serdesCtleParams[serdesNum].lowFrequency,
                                    serdesCtleParams[serdesNum].highFrequency,serdesCtleParams[serdesNum].bandWidth,
                                    serdesCtleParams[serdesNum].loopBandwidth, mcdSerdesTxRxTuneParamsArray[baudRate].squelch ));
#else
    ATTEMPT(mcdSerdesManualCtleConfig (pDev, serdesNum,
                                    mcdSerdesTxRxTuneParamsArray[baudRate].dcGain, mcdSerdesTxRxTuneParamsArray[baudRate].lowFrequency,
                                    mcdSerdesTxRxTuneParamsArray[baudRate].highFrequency,mcdSerdesTxRxTuneParamsArray[baudRate].bandWidth,
                                    mcdSerdesTxRxTuneParamsArray[baudRate].loopBandwidth, mcdSerdesTxRxTuneParamsArray[baudRate].squelch ));
#endif

#if 1 /**/
   dwell = 1;
   dwell = dwell;
   if (baudRate == MCD_1_25G)
   { /* set dwwell time only in 1G */
       /* select DFE tuning dwell time */
       ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18, 0x7, NULL));

       /* big register write LSB */
       ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, 0x800, NULL));

       /* big register write MSB */
       ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, 0, NULL));
   }
#else /**/
    dwell = mcdBaudRate2DwellTimeValue[baudRate];

    /* select DFE tuning dwell time */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x18, 0x7, NULL));

    /* big register write LSB */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, 1<<dwell, NULL));

    /* big register write MSB */
    ATTEMPT(mcdSerdesSpicoInterrupt(pDev, serdesNum, 0x19, 0, NULL));
#endif
#endif /* ASIC_SIMULATION*/
    return MCD_OK;
}

/**
* @internal mcdSerdesTxRxAllocateSwDb function
* @endinternal
*
* @brief   allocate serdes Tx/Rx SW data base
*
* @param[in] pDev                     - pointer to device
* @param[in] serdesNum                - serdes number
*
* @retval MCD_OK                   - on success
* @retval MCD_FAIL                 - on error
*/
MCD_STATUS mcdSerdesTxRxAllocateSwDb
(
    MCD_DEV_PTR         pDev,
    unsigned int        serdesNum
)
{

    MCD_TX_RX_SERDES_SW_DB *txRxSerdesSwDbPtr;
    txRxSerdesSwDbPtr = &(pDev->txRxSerdesSwDb);
    if (txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb == NULL)
    {
        txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb = (MCD_AVAGO_SERDES_SW_DB **)malloc(sizeof(MCD_AVAGO_SERDES_SW_DB*)*MCD_MAX_SERDES_NUMBER);
        if (txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb == NULL)
        {
            MCD_DBG_ERROR("Allocation failed, out of CPU memory");
            return MCD_OUT_OF_CPU_MEM;
        }
        mcdMemSet(txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb, 0, sizeof(MCD_AVAGO_SERDES_SW_DB*)*MCD_MAX_SERDES_NUMBER);
    }

    if (txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[serdesNum] == NULL)
    {
        txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[serdesNum] = (MCD_AVAGO_SERDES_SW_DB*)malloc(sizeof(MCD_AVAGO_SERDES_SW_DB));
        if (txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[serdesNum] == NULL)
        {
            MCD_DBG_ERROR("Allocation failed, out of CPU memory");
            return MCD_OUT_OF_CPU_MEM;
        }
        mcdMemSet(txRxSerdesSwDbPtr->txRxAvagoSerdesSwDb[serdesNum], 0, sizeof(MCD_AVAGO_SERDES_SW_DB));
    }

    return MCD_OK;

}

/**
* @internal mcdSerdesVcoRxConfig function
* @endinternal
*
* @brief   allocate serdes Tx/Rx SW data base
*
* @param[in] pDev           - pointer to device
* @param[in] serdesNum      - serdes number
* @param[in] temperature    - Temperature (in C) from Avago Serdes
* @param[in] rxTherm        - Rx therm of VCO  (0...0xFFFF)
* @param[in] rxBin          - Rx bin of VCO  (0...0xFFFF)
*
* @retval MCD_OK            - on success
* @retval MCD_FAIL          - on error
*/
unsigned int mcdSerdesVcoRxConfig
(
    MCD_DEV_PTR     pDev,
    unsigned int    serdesNum,
    int     temperature,
    int     rxTherm,
    int     rxBin
)
{
#ifndef ASIC_SIMULATION
    int shift=0;
    unsigned int res;

    /* Calculate the Shift value according to the Temperature */
    res = mcdSerdesShiftCalc(pDev, temperature, &shift);
    if (res != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSerdesShiftCalc failed (%d)\n", res);
        return MCD_FAIL;
    }

    /* shift the calibration code for Rx */
    res = mcdSerdesCalCodeShift(pDev, serdesNum, MCD_FALSE, shift, rxTherm, rxBin);
    if (res != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSerdesCalCodeShift failed (%d)\n", res);
        return MCD_FAIL;
    }
#endif /* ASIC_SIMULATION */

    return MCD_OK;
}

/**
* @internal mcdSerdesVcoTxConfig function
* @endinternal
*
* @brief   allocate serdes Tx/Rx SW data base
*
* @param[in] pDev           - pointer to device
* @param[in] serdesNum      - serdes number
* @param[in] temperature    - Temperature (in C) from Avago Serdes
* @param[in] rxTherm        - Tx therm of VCO  (0...0xFFFF)
* @param[in] rxBin          - Tx bin of VCO  (0...0xFFFF)
*
* @retval MCD_OK            - on success
* @retval MCD_FAIL          - on error
*/
unsigned int mcdSerdesVcoTxConfig
(
    MCD_DEV_PTR     pDev,
    unsigned int    serdesNum,
    int     temperature,
    int     txTherm,
    int     txBin
)
{
#ifndef ASIC_SIMULATION
    int shift=0;
    unsigned int res;

    /* Calculate the Shift value according to the Temperature */
    res = mcdSerdesShiftCalc(pDev, temperature, &shift);
    if (res != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSerdesShiftCalc failed (%d)\n", res);
        return MCD_FAIL;
    }

    /* Shift the calibration code for Tx */
    res = mcdSerdesCalCodeShift(pDev, serdesNum, MCD_TRUE, shift, txTherm, txBin);
    if (res != MCD_OK)
    {
        MCD_DBG_ERROR("mcdSerdesCalCodeShift failed (%d)\n", res);
        return MCD_FAIL;
    }

#endif /* ASIC_SIMULATION */

    return MCD_OK;
}


#endif /* MV_HWS_REDUCED_BUILD_EXT_CM3 */

