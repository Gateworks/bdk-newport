/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions to call Serdes API functions, various 
Serdes features and diagnostic operations.  The Serdes API component 
is included by default with define MXD_ENABLE_SERDES_API.
********************************************************************/
#include "mxdApiRegs.h"
#include "mxdApiTypes.h"
#include "mxdUtils.h"
#include "mxdHwCntl.h"
#include "mxdDiagnostics.h"
#include "mxdAPI.h"
#include "mxdHwSerdesCntl.h"


/******************************************************************************
 MXD_STATUS mxdExecuteIndirectSBusCmd
*******************************************************************************/
MXD_STATUS mxdExecuteIndirectSBusCmd
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort
)
{
    MXD_U16 executionStatus = 0;
    MXD_U16 retry;

    /* wait till last command complete, then send execute and wait for completion */
    for (retry = 0; retry < 5; retry++)
    {
        if ((mxdHwXmdioRead(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_EXECUTION, &executionStatus) != MXD_OK) ||
            ((executionStatus & 0x3) != 0))
        {
            ATTEMPT(mxdWait(pDev, 1));
        }
        else
        {
            break;
        }
    }

    if ((executionStatus & 0x3) != 0)
    {
        MXD_DBG_ERROR("mxdExecuteIndirectSBusCmd: executionStatus failed: 0x%x\n", executionStatus);
        return MXD_FAIL;
    }

    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_EXECUTION, 0x1));

    for (retry = 0; retry < 5; retry++)
    {
        if ((mxdHwXmdioRead(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_EXECUTION, &executionStatus) != MXD_OK) ||
            ((executionStatus & 0x3) != 0))
        {
            ATTEMPT(mxdWait(pDev, 1));
        }
        else
        {
            break;
        }
    }

    if ((executionStatus & 0x3) != 0)
    {
        MXD_DBG_ERROR("mxdExecuteIndirectSBusCmd: executionStatus2 failed: 0x%x\n", executionStatus);
        return MXD_FAIL;
    }

    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdIndirectSBusWrite
*******************************************************************************/
MXD_STATUS mxdIndirectSBusWrite
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 sBusReceiverAddr, 
    IN MXD_U16 regAddr, 
    IN MXD_U16 dataH, 
    IN MXD_U16 dataL, 
    OUT MXD_U16 *resultCode
)
{
    MXD_STATUS status = MXD_OK; 
    MXD_U16 retResultCode;

    /* Store the command, SBus receiver address, and register address */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_COMMAND_REG, MXD_SBUS_WRITE));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_ADDR_REG, 
                    (MXD_U16)((sBusReceiverAddr & 0xFF) << 8 | (regAddr & 0xFF))));

    /* If it is a SBus write command, also store the output data */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_INPUT_DATA_H, dataH));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_INPUT_DATA_L, dataL));

    /* set Sbus command receive data valid selection mode to level */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_RX_DATA_VALID, 0x00));

    /* execute command */
    if ((mxdExecuteIndirectSBusCmd(pDev, mdioPort)) != MXD_OK)
    {
        status = MXD_FAIL;
    }

    /* store result code */
    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_RESULT_CODE, &retResultCode));

    *resultCode = retResultCode & 0x07;

    /* clean execution bit */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_EXECUTION, 0x00));

    return status;
}


/******************************************************************************
 MXD_STATUS mxdIndirectSBusRead
*******************************************************************************/
MXD_STATUS mxdIndirectSBusRead
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 sBusReceiverAddr, 
    IN MXD_U16 regAddr, 
    OUT MXD_U16 *dataH, 
    OUT MXD_U16 *dataL, 
    OUT MXD_U16 *resultCode
)
{
    MXD_STATUS status = MXD_OK; 
    MXD_U16 retResultCode;
    MXD_U16 tempH = 0;
    MXD_U16 tempL = 0;

    /* Store the command, SBus receiver address, and register address */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_COMMAND_REG, MXD_SBUS_READ));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_ADDR_REG, 
                            (MXD_U16)((sBusReceiverAddr & 0xFF) << 8 | (regAddr & 0xFF))));

    /* set Sbus command receive data valid selection mode to level */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_RX_DATA_VALID, 0x00));

    /* execute command */
    if ((mxdExecuteIndirectSBusCmd(pDev, mdioPort))!= MXD_OK)
    {
        status = MXD_FAIL;
    }

    /* verify data is correctly written to register */
    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_OUTPUT_DATA_L, &tempL));
    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_OUTPUT_DATA_H, &tempH));

    *dataH = (MXD_U16)tempH;
    *dataL = (MXD_U16)tempL;

    /* store result code */
    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_RESULT_CODE, &retResultCode));

    *resultCode = retResultCode & 0x07;

    /* clean execution bit */
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_EXECUTION, 0x00));

    return status;
}

 
/******************************************************************************
 MXD_STATUS mxdSerdesInterrupt
*******************************************************************************/
MXD_STATUS mxdSerdesInterrupt
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 sBusReceiverAddr, 
    IN MXD_U16 interruptCode, 
    IN MXD_U16 interruptData, 
    OUT MXD_U16 *interruptResult
)
{
    MXD_U16 executionStatus;
    MXD_U16 retry;
    MXD_U16 tempInterruptOutput = 0;
    MXD_U16 tempInterruptStatus = 0;

    /* Store Sedres Interrupt command */
    if (mxdIndirectSBusWrite(pDev, mdioPort, 
                             sBusReceiverAddr, 
                             MXD_SBUS_SERDES_INTR_CMD, 
                             interruptCode, 
                             interruptData, 
                             &executionStatus) == MXD_FAIL)
    {
        MXD_DBG_ERROR("mxdSerdesInterrupt: mxdIndirectSBusWrite INTR_CMD failed: 0x%x\n", executionStatus);
        return MXD_FAIL;
    }
    if ((executionStatus & 0x7) != MXD_SBUS_WRITE_COMPLETE)
    {
        MXD_DBG_ERROR("mxdSerdesInterrupt: MXD_SBUS_SERDES_INTR_CMD executionStatus: 0x%x\n", executionStatus);
        return MXD_FAIL;
    }

    /* readback interrupt result until interrupt has been completed */
    for (retry = 0; retry < 100; retry++)
    {
        if (mxdIndirectSBusRead(pDev, mdioPort,
                                sBusReceiverAddr, 
                                MXD_SBUS_SERDES_INTR_RESULT, 
                                &tempInterruptStatus, 
                                &tempInterruptOutput, 
                                &executionStatus) == MXD_FAIL)
        {
            MXD_DBG_ERROR("mxdSerdesInterrupt: mxdIndirectSBusWrite INTR_RESULT failed: 0x%x\n", 
                          executionStatus);
            return MXD_FAIL;
        }

        if ((executionStatus & 0x7) != MXD_SBUS_READ_COMPLETE)
        {
            MXD_DBG_ERROR("mxdSerdesInterrupt: MXD_SBUS_SERDES_INTR_RESULT executionStatus: 0x%x\n", executionStatus);
            return MXD_FAIL;
        }

        if ((tempInterruptStatus & 0x01) == 0) /* if interrupts complete, stop waiting */
        {
            break;
        }

        ATTEMPT(mxdWait(pDev, 5));
    }

    *interruptResult = (MXD_U16)(tempInterruptOutput & 0xFFFF);

    if ((tempInterruptStatus & 0x01) != 0) /* if interrupt still not completed after 500ms, quit */
    {
        MXD_DBG_ERROR("mxdSerdesInterrupt: Device Access timeout tempInterruptStatus: 0x%x\n", 
                      tempInterruptStatus);
        return MXD_FAIL;
    }

    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdSbusInterrupt
*******************************************************************************/
MXD_STATUS mxdSbusInterrupt
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 interruptCode, 
    IN MXD_U16 interruptInput, 
    OUT MXD_U16 *interruptResult, 
    OUT MXD_U16 *interruptStatus
)
{
    MXD_U16 executionStatus;
    MXD_U16 tempInterruptOutput = 0;
    MXD_U16 tempInterruptStatus = 0;
    MXD_U16 retry;

    /* Store SBus Interrupt command */
    if (mxdIndirectSBusWrite(pDev, mdioPort,
                             MXD_SBUS_SBUS_MASTER, 
                             MXD_SBUS_MASTER_INTR_CMD, 
                             interruptInput, 
                             interruptCode, 
                             &executionStatus) == MXD_FAIL)
    {
        MXD_DBG_ERROR("mxdSbusInterrupt: Device Access timeout INTR_CMD failed: 0x%x\n", executionStatus);
        return MXD_FAIL;
    }

    if ((executionStatus & 0x7) != MXD_SBUS_WRITE_COMPLETE)
    {
        MXD_DBG_ERROR("mxdSbusInterrupt: MXD_SBUS_MASTER_INTR_CMD executionStatus: 0x%x\n", executionStatus);
        return MXD_FAIL;
    }

    /* assert interrupt and wait till complete or timeout */
    if (mxdIndirectSBusWrite(pDev, mdioPort, 
                             MXD_SBUS_SBUS_MASTER, 
                             MXD_SBUS_MASTER_INTR_STATUS, 
                             0x00, 
                             0x01, 
                             &executionStatus) == MXD_FAIL)
    {
        MXD_DBG_ERROR("mxdSbusInterrupt: Device Access timeout INTR_STATUS failed: 0x%x\n", executionStatus);
        return MXD_FAIL;
    }
    
    if ((executionStatus & 0x7) != MXD_SBUS_WRITE_COMPLETE)
    {
        MXD_DBG_ERROR("mxdSbusInterrupt: MXD_SBUS_MASTER_INTR_STATUS executionStatus: 0x%x\n", executionStatus);
        return MXD_FAIL;
    }

    /* read back interrupt result until interrupt has been completed */
    for (retry = 0; retry < 500; retry++)
    {
        if (mxdIndirectSBusRead(pDev, mdioPort, 
                                MXD_SBUS_SBUS_MASTER, 
                                MXD_SBUS_MASTER_INTR_RESULT, 
                                &tempInterruptOutput, 
                                &tempInterruptStatus, 
                                &executionStatus) == MXD_FAIL)
        {
            MXD_DBG_ERROR("mxdSbusInterrupt: Device Access timeout INTR_RESULT failed: 0x%x\n", executionStatus);
            return MXD_FAIL;
        }

        if ((executionStatus & 0x7) != MXD_SBUS_READ_COMPLETE)
        {
            MXD_DBG_ERROR("mxdSbusInterrupt: MXD_SBUS_MASTER_INTR_RESULT executionStatus: 0x%x\n", executionStatus);
            return MXD_FAIL;
        }
        
        if ((tempInterruptStatus & 0x8000) == 0)
        {
            break;
        }

        ATTEMPT(mxdWait(pDev, 1));
    }

    *interruptStatus = (MXD_U16)(tempInterruptStatus & 0xFFFF);
    *interruptResult = (MXD_U16)(tempInterruptOutput & 0xFFFF);

    if ((tempInterruptStatus & 0x8000) != 0) /* if interrupt still not completed after 500ms, quit */
    {
        MXD_DBG_ERROR("mxdSbusInterrupt: Device Access timeout tempInterruptStatus: 0x%x\n", tempInterruptStatus);
        return MXD_FAIL;
    }

    return MXD_OK;
}

/******************************************************************************
 MXD_STATUS mxdSerdesIntWrite
*******************************************************************************/
MXD_STATUS mxdSerdesIntWrite
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 regAddr, 
    IN MXD_U16 dataH, 
    IN MXD_U16 dataL
)
{
    MXD_U16 serdesInterruptAddr;
    MXD_U16 retStatus;

    serdesInterruptAddr = (regAddr & 0xFF00) >> 8; 

    if (mxdIndirectSBusWrite(pDev, mdioPort, serdesInterruptAddr, MXD_SBUS_SERDES_INTR_CMD, 
                             dataH, dataL, &retStatus) == MXD_FAIL)
    {
        MXD_DBG_ERROR("mxdSerdesIntWrite: mxdIndirectSBusWrite failed: 0x%x\n", retStatus);
        return MXD_FAIL;
    }
    if ((retStatus & 0x7) != MXD_SBUS_WRITE_COMPLETE)
    {
        MXD_DBG_ERROR("mxdSerdesIntWrite: mxdIndirectSBusWrite write error: 0x%x\n", retStatus);
        return MXD_FAIL;
    }

    return MXD_OK;
}

#if MXD_ENABLE_SERDES_API

/******************************************************************************
 MXD_UINT mxdSerdesMDIO
*******************************************************************************/
MXD_UINT mxdSerdesMDIO
(
    IN MXD_SER_DEV_PTR pSerdesDev,
    IN uint sbusAddr,   
    IN MXD_U8 regAddr,
    IN MXD_U8 mdioCmd,
    OUT uint *sbusData
)
{
    MXD_U16 cmdSucceeded = FALSE;  /* TRUE if SBus call succeeds, FALSE if not. */
    MXD_U16 retData = 0;
    MXD_U16 cmd = 0;
    MXD_U16 sbusRegAddr;
    MXD_U16 dataH = 0;
    MXD_U16 dataL = 0;
    MXD_U16 outDataL = 0;
    MXD_U16 outDataH = 0;

    MXD_DEV_PTR pDev =(MXD_DEV_PTR)pSerdesDev->client_data;
    MXD_U16 mdioPort = pDev->mdioPort;

    sbusRegAddr =(MXD_U16)(sbusAddr << 8) + (MXD_U16)regAddr;
    dataH = (MXD_U16)(*sbusData >> 16);
    dataL = (MXD_U16)(*sbusData & 0xFFFF);
    
    if (mdioCmd == 1)      /* Write */
    {
        cmd = MXD_SBUS_WRITE;
    }
    else if (mdioCmd == 2) /* Read */
    {
       cmd = MXD_SBUS_READ;
    }
    else if (mdioCmd == 0) /* ADDR */
    {
        cmd = MXD_SBUS_ADDR;
    }

    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_COMMAND_REG, cmd));
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_ADDR_REG, sbusRegAddr));

    if ((cmd & 0x1) == 0x1) /* write */
    {
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_INPUT_DATA_H, dataH));
        ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_INPUT_DATA_L, dataL));
    }

    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_RX_DATA_VALID, 0x0)); 

    if (mxdExecuteIndirectSBusCmd(pDev, mdioPort))
    {
        cmdSucceeded = MXD_FALSE;
        MXD_DBG_ERROR("Non Read, Failed\n");
    }
    else
    {
        cmdSucceeded = MXD_TRUE;
        /* MXD_DBG_INFO("Non Read, Succeed\n"); */
    }

    /* make sure it's done */ 
    /* MXD_DBG_INFO("SBUS: Execution complete\n"); */

    ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_RESULT_CODE, &retData)); 

    if ((cmd & 0x2) == 0x2) /* read */
    {
        ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_OUTPUT_DATA_L, &outDataL));
        ATTEMPT(mxdHwXmdioRead(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_OUTPUT_DATA_H, &outDataH));

        retData = ((MXD_U32)outDataH<<16) + outDataL;
        *sbusData = ((MXD_U32)outDataH<<16) + outDataL;
    }
    
    ATTEMPT(mxdHwXmdioWrite(pDev, mdioPort, MXD_CHIP_REG, MXD_SBUS_EXECUTION, 0x0));   

    /* MXD_DBG_INFO("SBus %u %02x %02x 0x%08x, retData=%u\n", sbusAddr, regAddr, mdioCmd, *sbusData, retData); */
    
    if( !cmdSucceeded )
    {
        /* Log error: */
        MXD_DBG_ERROR("SBus %u, %02x %02x 0x%08x FAILED\n", sbusAddr, regAddr, cmd, *sbusData); 
    }
    
    return TRUE;
}


/******************************************************************************
 MXD_STATUS mxdInitSerdesDev
*******************************************************************************/
MXD_STATUS mxdInitSerdesDev
(
    IN MXD_DEV_PTR pDev
)
{   
    MXD_STATUS retStatus = MXD_OK;
    MXD_SER_DEV_PTR pSerdesDev = 0;

    pSerdesDev = mxdWrapperAllocDevStruct();
    if (!pSerdesDev)
    {
        MXD_DBG_ERROR("mxdInitSerdesDev: pSerdesDev is NULL\n");
        return MXD_FAIL;
    }

    pDev->serdesDev = pSerdesDev;
    pSerdesDev->client_data = (MXD_PVOID)pDev;
    pSerdesDev->debug = MXD_SER_LOG_OFF;  /* default SerDes debug to off */

#ifdef MXD_DEBUG 
    switch (mxd_debug_level)
    {
        case MXD_DBG_OFF_LVL:
            pSerdesDev->debug = MXD_SER_LOG_OFF;  
            break;
        case MXD_DBG_ERR_LVL:
            pSerdesDev->debug = MXD_SER_LOG_ERROR;  
            break;
        case MXD_DBG_INF_LVL:
        case MXD_DBG_ALL_LVL:
            pSerdesDev->debug = MXD_SER_LOG_INFO;  
            break;
        default: 
            pSerdesDev->debug = MXD_SER_LOG_INFO;  
            break;
    }
#endif
#ifdef MXD_PY_DEBUG
    pSerdesDev->debug = MXD_SER_LOG_OFF;  
#endif

    mxdWrapperSBusComm(pSerdesDev);
    mxdWrapperRegisterSBusFn(pSerdesDev, &mxdSerdesMDIO, NULL, NULL);  

    mxdWrapperConnect(pSerdesDev, 0, 0);
    mxdWrapperGetIpInfo(pSerdesDev, 0);
    
    return retStatus;
}

/******************************************************************************
 MXD_STATUS mxdFreeSerdesDev
*******************************************************************************/
MXD_STATUS mxdFreeSerdesDev
(
    IN MXD_DEV_PTR pDev
)
{   
    if (!pDev->serdesDev)
    {
        return MXD_FAIL;
    }

    mxdWrapperFreeDevStruct((MXD_SER_DEV_PTR)pDev->serdesDev);

    return MXD_OK;
}

/******************************************************************************
 MXD_STATUS mxdSerdesTune_iCal
*******************************************************************************/
MXD_STATUS mxdSerdesTune_iCal
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_U16 iCalVal_1,
   IN MXD_U16 iCalVal_2,
   IN MXD_U16 iCalVal_3,
   IN MXD_U16 iCalVal_4,
   IN MXD_U16 useDefault
)
{       
    MXD_STATUS status;
    MXD_U16 wrapperStatus;
    MXD_SER_INIT_DFE_TUNE_TYPE control;
    
    if ((!pDev->serdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesTune_iCal: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pDev->serdesDev, sAddr);
        return MXD_FAIL;
    }

    mxdMemSet(&control, 0, sizeof(MXD_SER_INIT_DFE_TUNE_TYPE));

    control.tune_mode = AVAGO_DFE_ICAL;

    if (useDefault == 0) /* use provided 4 iCal values if "useDefault = 0" */ 
    {
        control.fixed[0] = control.fixed[1] = control.fixed[2] = control.fixed[3] = 1;
        control.value[0] = iCalVal_1;
        control.value[1] = iCalVal_2;
        control.value[2] = iCalVal_3;
        control.value[3] = iCalVal_4;
    }

    wrapperStatus = mxdWrapperSerDesTune((MXD_SER_DEV_PTR)pDev->serdesDev, sAddr, &control);

    if (wrapperStatus == MXD_TRUE)
    {
        MXD_DBG_INFO("mxdSerdesTune_iCal: values:0x%X; 0x%X; 0x%X; 0x%X\n", 
                      control.value[0], control.value[1], control.value[2], control.value[3]);
        status = MXD_OK;
    }
    else
    {
        MXD_DBG_ERROR("mxdSerdesTune_iCal: Failed to tune iCal\n");
        status = MXD_FAIL;
   }

    return status;
}


/******************************************************************************
 MXD_STATUS mxdSerdesTune_pCal
*******************************************************************************/
MXD_STATUS mxdSerdesTune_pCal
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_DFE_TUNE_MODE tuneMode
)
{       
    MXD_STATUS status;
    MXD_U16 wrapperStatus;
    MXD_SER_INIT_DFE_TUNE_TYPE control;
    
    if (!pDev->serdesDev)
    {
        MXD_DBG_ERROR("mxdSerdesTune_pCal: serdesDev is NULL\n");
        return MXD_FAIL;
    }

    mxdMemSet(&control, 0, sizeof(MXD_SER_INIT_DFE_TUNE_TYPE));

    control.tune_mode = (Avago_serdes_dfe_tune_mode_t)tuneMode;

    wrapperStatus = mxdWrapperSerDesTune((MXD_SER_DEV_PTR)pDev->serdesDev, sAddr, &control);

    if (wrapperStatus == MXD_TRUE)
    {
        MXD_DBG_INFO("mxdSerdesTune_pCal: tuneMode:%u\n", tuneMode);
        status = MXD_OK;
    }
    else
    {
        MXD_DBG_ERROR("mxdSerdesTune_pCal: Failed to tune pCal\n");
        status = MXD_FAIL;
   }

    return status;
}

/******************************************************************************
 MXD_STATUS mxdSerdesInitBitRate
*******************************************************************************/
MXD_STATUS mxdSerdesInitBitRate
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_U16 divider,
   IN MXD_BOOL intLoopbackMode
)
{   
    MXD_STATUS status;
    
    if (!pDev->serdesDev)
    {
        MXD_DBG_ERROR("mxdSerdesInitBitRate: serdesDev is NULL\n");
        return MXD_FAIL;
    }

    status = mxdWrapperSerdesQuickInit((MXD_SER_DEV_PTR)pDev->serdesDev, sAddr, divider);

    ATTEMPT(mxdWait(pDev, 10));

    ATTEMPT(mxdSerdesSetRxLoopback(pDev, sAddr, intLoopbackMode));

    if (status != MXD_OK)
    {
        MXD_DBG_ERROR("mxdSerdesInitBitRate: Failed with status:0x%08X\n", status);
        return MXD_FAIL;
    }

    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdSerdesGetEye
*******************************************************************************/
MXD_STATUS mxdSerdesGetEye
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_U16 sampleSize,
   IN MXD_U16 highDefinition,
   IN MXD_U16 serdesLogLevel, 
   OUT MXD_SER_EYE_DATA_TYPE *pEyeData
)
{   
    MXD_16  status;
    MXD_U16 serdesTempLogLevel;
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_SER_EYE_CONFIG_TYPE *pEyeConfig;
    
    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesGetEye: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    if (pEyeData == NULL)
    {
        MXD_DBG_ERROR("mxdSerdesGetEye: pEyeData memory must be pre-allocated\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    serdesTempLogLevel = (MXD_U16)pSerdesDev->debug;
    pSerdesDev->debug = serdesLogLevel;
    
    pEyeConfig = mxdWrapperEyeAllocConfig(pSerdesDev);

    MXD_DBG_INFO("mxdSerdesGetEye: eye_config_t size: %u; eye_data_t size: %u \n", 
                 (sizeof(MXD_SER_EYE_CONFIG_TYPE)), (sizeof(MXD_SER_EYE_DATA_TYPE)));

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

    status = (MXD_16)mxdWrapperGetEye(pSerdesDev, sAddr, pEyeConfig, pEyeData);

    if( status < 0 )
    {
        mxdWrapperEyeFreeConfig(pSerdesDev, pEyeConfig);

        MXD_DBG_ERROR("mxdSerdesGetEye: Eye capture failed.\n");
        return MXD_FAIL;
    }

    /* Logged result to a file */
    /* mxdWrapperEyeWriteToFile("eyeDataResult.log", pEyeData); */

    mxdWrapperEyeFreeConfig(pSerdesDev, pEyeConfig);

    pSerdesDev->debug = serdesTempLogLevel;

    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdSerdesGetRevision
*******************************************************************************/
MXD_STATUS mxdSerdesGetRevision
(
   IN MXD_DEV_PTR pDev,
   OUT MXD_U16 *serdesRevision,
   OUT MXD_U16 *sbmRevision
)
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_U16 sbmAddr;
    MXD_U16 sAddr = 1; 

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if (!pSerdesDev)
    {
        MXD_DBG_ERROR("mxdSerdesGetRevision: pSerdesDev is NULL\n");
        return MXD_FAIL;
    }

    sbmAddr = (MXD_U16)mxdWrapperBusMasterAddr(sAddr);
    
    *serdesRevision = (MXD_U16)mxdWrapperGetSerdesRev(pSerdesDev, sAddr);
    *sbmRevision = (MXD_U16)mxdWrapperGetSerdesRev(pSerdesDev, sbmAddr);

    MXD_DBG_INFO("mxdSerdesGetRevision: SerDes revision:0x%04X SBM revision:0x%04X\n",
                 *serdesRevision, *sbmRevision);

    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdSerdesGetVoltage
*******************************************************************************/
MXD_STATUS mxdSerdesGetVoltage
(
   IN MXD_DEV_PTR pDev,
   OUT MXD_U16 *coreVoltage,
   OUT MXD_U16 *DVDDVoltage,
   OUT MXD_U16 *AVDDVoltage
)
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_U16 voltageReading;
    MXD_U16 interruptStatus;
     
    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if (!pSerdesDev)
    {
        MXD_DBG_ERROR("mxdSerdesGetVoltage: pSerdesDev is NULL\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdSbusInterrupt(pDev, pDev->mdioPort, MXD_SBUS_VOLTAGE_DATA, (uint)((0 << 12) | MXD_SBUS_TEMPERATURE_SENSOR), 
                     &voltageReading, &interruptStatus));
    *coreVoltage = (MXD_U16)((voltageReading & 0xFFF) * 0.5);

    ATTEMPT(mxdSbusInterrupt(pDev, pDev->mdioPort, MXD_SBUS_VOLTAGE_DATA, (uint)((1 << 12) | MXD_SBUS_TEMPERATURE_SENSOR), 
                     &voltageReading, &interruptStatus));
    *DVDDVoltage = (MXD_U16)((voltageReading & 0xFFF) * 0.5);
    
    ATTEMPT(mxdSbusInterrupt(pDev, pDev->mdioPort, MXD_SBUS_VOLTAGE_DATA, (uint)((2 << 12) | MXD_SBUS_TEMPERATURE_SENSOR), 
                     &voltageReading, &interruptStatus));
    *AVDDVoltage = (MXD_U16)((voltageReading & 0xFFF) * 0.5);

    MXD_DBG_INFO("mxdSerdesGetVoltage: voltages Core:%umV; DVDD:%umV; AVDD:%umV\n", 
                 *coreVoltage, *DVDDVoltage, *AVDDVoltage);

    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdSerdesGetTemperature
*******************************************************************************/
MXD_STATUS mxdSerdesGetTemperature
(
   IN MXD_DEV_PTR pDev,
   OUT MXD_32 *coreTemperature,
   OUT MXD_32 *serdesTemperature
)
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_U16 temperatureReading;
    MXD_U16 interruptStatus;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if (!pSerdesDev)
    {
        MXD_DBG_ERROR("mxdSerdesGetTemperature: pSerdesDev is NULL\n");
        return MXD_FAIL;
    }

    ATTEMPT(mxdSbusInterrupt(pDev, pDev->mdioPort, MXD_SBUS_TEMPERATURE_DATA, (uint)((0 << 12) | MXD_SBUS_TEMPERATURE_SENSOR), 
                             &temperatureReading, &interruptStatus));

    if (temperatureReading & 0x0800)
    {
        *coreTemperature = (((~temperatureReading + 1) & 0x7FF) * 125) * -1;
    }
    else
    {
        *coreTemperature = (temperatureReading & 0x7FF) * 125;
    }

    ATTEMPT(mxdSbusInterrupt(pDev, pDev->mdioPort, MXD_SBUS_TEMPERATURE_DATA, (uint)((1 << 12) | MXD_SBUS_TEMPERATURE_SENSOR), 
                             &temperatureReading, &interruptStatus));

    if (temperatureReading & 0x0800)
    {
        *serdesTemperature = (((~temperatureReading + 1) & 0x7FF) * 125) * -1;
    }
    else
    {
        *serdesTemperature = (temperatureReading & 0x7FF) * 125;
    }

    MXD_DBG_INFO("mxdSerdesGetTemperature: coreTemperature:%7dmC; serdesTemperature:%7dmC\n", 
                 *coreTemperature, *serdesTemperature);

    return MXD_OK;
}

/******************************************************************************
 MXD_STATUS mxdSerdesGetTxFFE
*******************************************************************************/
MXD_STATUS mxdSerdesGetTxFFE
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   OUT MXD_16 *preCursor,
   OUT MXD_16 *attenuation,
   OUT MXD_16 *postCursor,
   OUT MXD_16 *slew
)
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_SER_TX_EQ_TYPE txEq;
    MXD_16 status;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesGetTxFFE: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    status = (MXD_16)mxdWrapperGetTxFFE(pSerdesDev, sAddr, &txEq);
    
    MXD_DBG_INFO("mxdSerdesGetTxFFE: preCursor:%d; attenuation:%u; postCursor:%d; slew:%d\n", 
                 txEq.pre, txEq.atten, txEq.post, txEq.slew);
    
    if (status == MXD_OK)
    {
        *preCursor   = txEq.pre;
        *attenuation = txEq.atten;
        *postCursor  = txEq.post;
        *slew  = txEq.slew;
    }
    else
    {
       MXD_DBG_ERROR("mxdSerdesGetTxFFE: Failed with status:0x%08X\n", status);
       return MXD_FAIL;
    }

    return MXD_OK;
}

/******************************************************************************
 MXD_STATUS mxdSerdesSetTxFFE
*******************************************************************************/
MXD_STATUS mxdSerdesSetTxFFE
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   IN MXD_16 preCursor,
   IN MXD_16 attenuation,
   IN MXD_16 postCursor,
   IN MXD_16 slew
)
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_SER_TX_EQ_TYPE txEq;
    MXD_16 status;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesSetTxFFE: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    mxdMemSet(&txEq, 0, sizeof(MXD_SER_TX_EQ_TYPE));

    txEq.pre   = preCursor;
    txEq.atten = attenuation;
    txEq.post  = postCursor;
    txEq.slew  = slew; 

    status = (MXD_16)mxdWrapperSetTxFFE(pSerdesDev, sAddr, &txEq);
    
    MXD_DBG_INFO("mxdSerdesSetTxFFE: preCursor:%d; attenuation:%u; postCursor:%d; slew:%d\n", 
                 txEq.pre, txEq.atten, txEq.post, txEq.slew);
    
    if (status != MXD_OK)
    {
        MXD_DBG_ERROR("mxdSerdesSetTxFFE: Failed with status:0x%08X\n", status);
        return MXD_FAIL;
    }

    return MXD_OK;
}

#define MXD_ICalInProgress  0x01
#define MXD_PCalInProgress  0x02
#define MXD_VosInProgress   0x04
#define MXD_RunICal         0x10
#define MXD_RunPCal         0x20
#define MXD_DetectEI        0x200

/******************************************************************************
 MXD_STATUS mxdSerdesGetRxDFEStatus
*******************************************************************************/
MXD_STATUS mxdSerdesGetRxDFEStatus
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   OUT MXD_BOOL *dfeStatusICalInProgress,  
   OUT MXD_BOOL *dfeStatusPCalInProgress,  
   OUT MXD_BOOL *dfeStatusVosInProgress,   
   OUT MXD_BOOL *dfeStatusRunICal,         
   OUT MXD_BOOL *dfeStatusRunPCal,         
   OUT MXD_BOOL *dfeStatusDetectEI         
)
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_U16 data = 0;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesGetRxDFEStatus: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", 
                       pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    /* mxdWrapperGetRxDFEStatus doesn't return status. Assume success */
    data = mxdWrapperGetRxDFEStatus(pSerdesDev, sAddr);

    *dfeStatusICalInProgress = (MXD_BOOL)((data & MXD_ICalInProgress)? 1:0);     
    *dfeStatusPCalInProgress = (MXD_BOOL)((data & MXD_PCalInProgress)? 1:0);     
    *dfeStatusVosInProgress = (MXD_BOOL)((data & MXD_VosInProgress)? 1:0);     
    *dfeStatusRunICal = (MXD_BOOL)((data & MXD_RunICal)? 1:0);             
    *dfeStatusRunPCal  = (MXD_BOOL)((data & MXD_RunPCal)? 1:0);            
    *dfeStatusDetectEI = (MXD_BOOL)((data & MXD_DetectEI)? 1:0);

    MXD_DBG_INFO("mxdSerdesGetRxDFEStatus: ICalInProg:%u, PCalInProg:%u, VosInProg:%u, RunICal:%u, RunPCal:%u, DetectEI:%u\n", 
                 *dfeStatusICalInProgress, 
                 *dfeStatusPCalInProgress,
                 *dfeStatusVosInProgress,
                 *dfeStatusRunICal,
                 *dfeStatusRunPCal,
                 *dfeStatusDetectEI);

    return MXD_OK;
}

/******************************************************************************
 MXD_STATUS mxdSerdesGetRxDFE
*******************************************************************************/
MXD_STATUS mxdSerdesGetRxDFE
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   OUT MXD_U16 *dc,        /* DC-Restore value [0-255] */
   OUT MXD_U16 *lf,        /* CTLE Low-Frequency setting [0-15] */
   OUT MXD_U16 *hf,        /* CTLE High-Frequency setting [0-15] */
   OUT MXD_U16 *bw,        /* CTLE Band-width setting [0-15] */
   OUT MXD_U16 *dfeGAIN,   /* DFE Gain Tap strength setting [0-15] */
   OUT MXD_U16 *dfeGAIN2   /* DFE Gain Tap 2 strength setting [0-15] */
)
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_SER_RX_DFE_TYPE rxDFE;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesGetRxDFE: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    mxdMemSet(&rxDFE, 0, sizeof(MXD_SER_RX_DFE_TYPE));

    /* mxdWrapperGetRxDFE doesn't return status. Assume success */
    mxdWrapperGetRxDFE(pSerdesDev, sAddr, &rxDFE);

    *dc = rxDFE.dc;     
    *lf = rxDFE.lf;   
    *hf = rxDFE.hf;  
    *bw = rxDFE.bw;  
    *dfeGAIN = rxDFE.dfeGAIN;
    *dfeGAIN2 = rxDFE.dfeGAIN2;

    MXD_DBG_INFO("mxdSerdesGetRxDFE: DFE.dc:%u, DFE.lf:%u, DFE.hf:%u, DFE.bw:%u, DFE.dfeGAIN:%u, DFE.dfeGAIN2:%u\n", 
                 rxDFE.dc, rxDFE.lf, rxDFE.hf, rxDFE.bw, rxDFE.dfeGAIN, rxDFE.dfeGAIN2);

    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdSerdesGetTxPolarity
*******************************************************************************/
MXD_STATUS mxdSerdesGetTxPolarity
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   OUT MXD_U16 *polarity
)
{
    MXD_SER_DEV_PTR pSerdesDev;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesGetTxPolarity: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    *polarity = (MXD_U16)mxdWrapperGetTxPolarity(pSerdesDev, sAddr);
    
    MXD_DBG_INFO("mxdSerdesGetTxPolarity: polarity:0x%X\n", *polarity);
    
    return MXD_OK;
}

/******************************************************************************
 MXD_STATUS mxdSerdesSetTxPolarity
*******************************************************************************/
MXD_STATUS mxdSerdesSetTxPolarity
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   IN MXD_U16 polarity
)
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_16 status;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesSetTxPolarity: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    status = (MXD_16)mxdWrapperSetTxPolarity(pSerdesDev, sAddr, polarity);
    
    MXD_DBG_INFO("mxdSerdesSetTxPolarity: polarity:0x%X\n", polarity);
    
    if (status != MXD_OK)
    {
        return MXD_FAIL;
    }

    return MXD_OK;
}

/******************************************************************************
 MXD_STATUS mxdSerdesGetRxPolarity
*******************************************************************************/
MXD_STATUS mxdSerdesGetRxPolarity
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   OUT MXD_U16 *polarity
)
{
    MXD_SER_DEV_PTR pSerdesDev;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesGetRxPolarity: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    *polarity = (MXD_U16)mxdWrapperGetRxPolarity(pSerdesDev, sAddr);
    
    MXD_DBG_INFO("mxdSerdesGetRxPolarity: polarity:0x%X\n", *polarity);
    
    return MXD_OK;
}

/******************************************************************************
 MXD_STATUS mxdSerdesSetRxPolarity
*******************************************************************************/
MXD_STATUS mxdSerdesSetRxPolarity
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   IN MXD_U16 polarity
)
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_U16 status;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesSetRxPolarity: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    status = (MXD_U16)mxdWrapperSetRxPolarity(pSerdesDev, sAddr, polarity);
    
    MXD_DBG_INFO("mxdSerdesSetRxPolarity: polarity:0x%X\n", polarity);
    
    if (status != MXD_OK)
    {
        return MXD_FAIL;
    }

    return MXD_OK;
}

/******************************************************************************
 MXD_STATUS mxdSerdesGetCDRLock
*******************************************************************************/
MXD_STATUS mxdSerdesGetCDRLock
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   OUT MXD_U16 *CDRLockState
)
{
    MXD_SER_DEV_PTR pSerdesDev;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesGetCDRLock: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    /*
      CDRLockState = 1 is locked; CDRLockState = 0 is not locked; 
    */
    *CDRLockState = (MXD_U16)mxdWrapperGetCDRLock(pSerdesDev, sAddr);
    
    MXD_DBG_INFO("mxdSerdesGetCDRLock: CDRLockState:0x%X\n", *CDRLockState);
    
    return MXD_OK;
}

/******************************************************************************
 MXD_STATUS mxdSerdesPMDTrainingLog
*******************************************************************************/
MXD_STATUS mxdSerdesPMDTrainingLog
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   OUT PMXD_TRAINING_INFO pTrainInfo
)
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_SER_PMD_DEBUG_TYPE *pSerdesDebugStruct = NULL;
    MXD_U16 index = 0;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesPMDTrainingLog: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    if (!pTrainInfo)
    {
        MXD_DBG_ERROR("mxdSerdesPMDTrainingLog: pTrainInfo is NULL\n");
        return MXD_FAIL;
    }
       
    mxdMemSet(pTrainInfo, 0, (sizeof(MXD_TRAINING_INFO)));

    /* Allocate a PMD structure for training log */
    pSerdesDebugStruct = mxdWrapperPMDAllocDebugStruct(pSerdesDev);
    if (pSerdesDebugStruct == NULL)
    {
        MXD_DBG_ERROR("mxdSerdesPMDTrainingLog: pSerdesDebugSt is NULL\n");
        return MXD_FAIL;
    }

    mxdWrapperPMDDebug(pSerdesDev, sAddr, pSerdesDebugStruct);
    
    pTrainInfo->reset = (MXD_BOOL)pSerdesDebugStruct->reset;
    pTrainInfo->rx_metric = pSerdesDebugStruct->rx_metric;
    pTrainInfo->local.preset = pSerdesDebugStruct->lcl->preset;
    pTrainInfo->local.initialize = pSerdesDebugStruct->lcl->initialize;
    pTrainInfo->remote.preset = pSerdesDebugStruct->remote->preset;
    pTrainInfo->remote.initialize = pSerdesDebugStruct->remote->initialize;
    pTrainInfo->last_local_request = pSerdesDebugStruct->last_local_request;
    mxdMemCpy(&pTrainInfo->last_remote_request, &pSerdesDebugStruct->last_remote_request, 
              (sizeof(MXD_UINT)*8)); 

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
    mxdWrapperPMDDebugPrint(pSerdesDev, pSerdesDebugStruct);
    mxdWrapperPMDFreeDebugStruct(pSerdesDev, pSerdesDebugStruct);

    MXD_DBG_INFO("mxdSerdesPMDTrainingLog: Completed\n");
    
    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdSerdesTxInjectError
*******************************************************************************/
MXD_STATUS mxdSerdesTxInjectError
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   IN MXD_U16 numErrBit
)
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_16 status = MXD_OK;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesTxInjectError: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    status = (MXD_16)mxdWrapperTxInjectError(pSerdesDev, sAddr, numErrBit);
    if (status != MXD_OK)
    {
        MXD_DBG_ERROR("mxdSerdesTxInjectError: Failed\n");
        return MXD_FAIL;
   }
    
    MXD_DBG_INFO("mxdSerdesTxInjectError: Completed\n");
    
    return MXD_OK;
}

/******************************************************************************
 MXD_STATUS mxdSerdesRxInjectError
*******************************************************************************/
MXD_STATUS mxdSerdesRxInjectError
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   IN MXD_U16 numErrBit
)
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_16 status = MXD_OK;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesTxInjectError: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    status = (MXD_16)mxdWrapperRxInjectError(pSerdesDev, sAddr, numErrBit);
    if (status != MXD_OK)
    {
        MXD_DBG_ERROR("mxdSerdesRxInjectError: Failed\n");
        return MXD_FAIL;
   }
    
    MXD_DBG_INFO("mxdSerdesRxInjectError: Completed\n");
    
    return MXD_OK;
}

/******************************************************************************
 MXD_STATUS mxdSerdesSetRxCmpMode
*******************************************************************************/
MXD_STATUS mxdSerdesSetRxCmpMode
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_SERDES_RX_CMP_MODE_TYPE rxCmpMode
)
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_16 status = MXD_OK;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesSetRxCmpMode: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    status = (MXD_16)mxdWrapperSetRxCmpMode(pSerdesDev, sAddr, (Avago_serdes_rx_cmp_mode_t)rxCmpMode);
    if (status != MXD_OK)
    {
        MXD_DBG_ERROR("mxdSerdesSetRxCmpMode: Failed\n");
        return MXD_FAIL;
   }
    
    MXD_DBG_INFO("mxdSerdesSetRxCmpMode: Completed\n");
    
    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdSerdesGetRxCmpMode
*******************************************************************************/
MXD_STATUS mxdSerdesGetRxCmpMode
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   OUT MXD_SERDES_RX_CMP_MODE_TYPE *rxCmpMode
)
{
    MXD_SER_DEV_PTR pSerdesDev;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesGetRxCmpMode: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    *rxCmpMode = (MXD_SERDES_RX_CMP_MODE_TYPE)mxdWrapperGetRxCmpMode(pSerdesDev, sAddr);
    
    MXD_DBG_INFO("mxdSerdesGetRxCmpMode: rxCmpMode:%u\n", *rxCmpMode);
    
    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdSerdesSetTxPRBS
*******************************************************************************/
MXD_STATUS mxdSerdesSetTxPRBS
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_SERDES_TX_DATA_TYPE txDataType
)
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_16 status = MXD_OK;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesSetTxPRBS: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    status = (MXD_16)mxdWrapperSetTxPRBS(pSerdesDev, sAddr, (Avago_serdes_tx_data_sel_t)txDataType);
    if (status != MXD_OK)
    {
        MXD_DBG_ERROR("mxdSerdesSetTxPRBS: Failed on SerDes lane:%u\n", sAddr);
        return MXD_FAIL;
   }
    
    MXD_DBG_INFO("mxdSerdesSetTxPRBS: Completed on SerDes lane:%u\n", sAddr);
    
    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdSerdesGetTxPRBS
*******************************************************************************/
MXD_STATUS mxdSerdesGetTxPRBS
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   OUT MXD_SERDES_TX_DATA_TYPE *txDataType
)
{
    MXD_SER_DEV_PTR pSerdesDev;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesGetTxPRBS: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    *txDataType = (MXD_SERDES_TX_DATA_TYPE)mxdWrapperGetTxPRBS(pSerdesDev, sAddr);
    
    MXD_DBG_INFO("mxdSerdesGetTxPRBS: txDataType:%u\n", *txDataType);
    
    return MXD_OK;
}

/******************************************************************************
 MXD_STATUS mxdSerdesSetTxOutputEnable
*******************************************************************************/
MXD_STATUS mxdSerdesSetTxOutputEnable
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_U16 outputEnable
)
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_16 status = MXD_OK;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesSetTxOutputEnable: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    status = (MXD_16)mxdWrapperSetTxOutputEnable(pSerdesDev, sAddr, outputEnable);
    if (status != MXD_OK)
    {
        MXD_DBG_ERROR("mxdSerdesSetTxOutputEnable: Failed\n");
        return MXD_FAIL;
    }
    
    MXD_DBG_INFO("mxdSerdesSetTxOutputEnable: Completed\n");
    
    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdSerdesGetTxOutputEnable
*******************************************************************************/
MXD_STATUS mxdSerdesGetTxOutputEnable
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   OUT MXD_U16 *outputEnable
)
{
    MXD_SER_DEV_PTR pSerdesDev;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesGetTxOutputEnable: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    *outputEnable = (MXD_BOOL)mxdWrapperGetTxOutputEnable(pSerdesDev, sAddr);
    
    MXD_DBG_INFO("mxdSerdesGetTxOutputEnable: outputEnable:%u\n", *outputEnable);
    
    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdSerdesSetTxRxEnable
*******************************************************************************/
MXD_STATUS mxdSerdesSetTxRxEnable
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_U16 txState,
   IN MXD_U16 rxState,
   IN MXD_U16 txOutputState
)
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_16 status = MXD_OK;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesSetTxRxEnable: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    status = (MXD_16)mxdWrapperSetTxRxEnable(pSerdesDev, sAddr, txState, rxState, txOutputState);
    if (status != MXD_OK)
    {
        MXD_DBG_ERROR("mxdSerdesSetTxRxEnable: Failed\n");
        return MXD_FAIL;
    }
    
    MXD_DBG_INFO("mxdSerdesSetTxRxEnable: Completed\n");
    
    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdSerdesGetTxRxReady
*******************************************************************************/
MXD_STATUS mxdSerdesGetTxRxReady
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   OUT MXD_U16 *txState,
   OUT MXD_U16 *rxState
)
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_16 status = MXD_OK;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesGetTxRxReady: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    status = (MXD_BOOL)mxdWrapperGetTxRxReady(pSerdesDev, sAddr, (BOOL*)txState, (BOOL*)rxState);
    
    if (status != MXD_OK)
    {
        MXD_DBG_ERROR("mxdSerdesGetTxRxReady: Failed\n");
        return MXD_FAIL;
    }

    MXD_DBG_INFO("mxdSerdesGetTxRxReady: txState:%u rxState:%u\n", *txState, *rxState);
    
    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdSerdesSetTxUserData
*******************************************************************************/
MXD_STATUS mxdSerdesSetTxUserData
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_32 userData[4]
)
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_16 status = MXD_OK;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesSetTxUserData: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    status = (MXD_16)mxdWrapperSetTxUserData(pSerdesDev, sAddr, userData);
    if (status != MXD_OK)
    {
        MXD_DBG_ERROR("mxdSerdesSetTxUserData: Failed\n");
        return MXD_FAIL;
   }
    
    MXD_DBG_INFO("mxdSerdesSetTxUserData: Completed\n");
    
    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdSerdesGetTxUserData
*******************************************************************************/
MXD_STATUS mxdSerdesGetTxUserData
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   OUT MXD_32 userData[4]
)
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_16 status = MXD_OK;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesGetTxUserData: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    status = (MXD_16)mxdWrapperGetTxUserData(pSerdesDev, sAddr, userData);
    if (status != MXD_OK)
    {
        MXD_DBG_ERROR("mxdSerdesGetTxUserData: Failed\n");
        return MXD_FAIL;
   }
    
    MXD_DBG_INFO("mxdSerdesGetTxUserData: Completed\n");
    
    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdSerdesSetRxCmpData
*******************************************************************************/
MXD_STATUS mxdSerdesSetRxCmpData
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_SERDES_RX_CMP_TYPE RxCmpType
)
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_16 status = MXD_OK;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesSetRxCmpData: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    status = (MXD_16)mxdWrapperSetRxCmpData(pSerdesDev, sAddr, (Avago_serdes_rx_cmp_data_t)RxCmpType);
    if (status != MXD_OK)
    {
        MXD_DBG_ERROR("mxdSerdesSetRxCmpData: Failed\n");
        return MXD_FAIL;
   }
    
    MXD_DBG_INFO("mxdSerdesSetRxCmpData: Completed\n");
    
    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdSerdesGetRxCmpData
*******************************************************************************/
MXD_STATUS mxdSerdesGetRxCmpData
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   OUT MXD_SERDES_RX_CMP_TYPE *RxCmpType
)
{
    MXD_SER_DEV_PTR pSerdesDev;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesGetRxCmpData: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    *RxCmpType = (MXD_SERDES_RX_CMP_TYPE)mxdWrapperGetRxCmpData(pSerdesDev, sAddr);
    
    MXD_DBG_INFO("mxdSerdesGetRxCmpData: RxCmpType:%u\n", *RxCmpType);
    
    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdSerdesGetErrCount
*******************************************************************************/
MXD_STATUS mxdSerdesGetErrCount
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_BOOL resetCounter,
   OUT MXD_U32 *errCount
)
{
    MXD_SER_DEV_PTR pSerdesDev;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesGetErrCount: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    *errCount = (MXD_U32)mxdWrapperGetErrCounter(pSerdesDev, sAddr, 0, resetCounter);
    
    MXD_DBG_INFO("mxdSerdesGetErrCount: errCount:%u\n", *errCount);
    
    return MXD_OK;
}

/******************************************************************************
 MXD_STATUS mxdSerdesSetRxLoopback
*******************************************************************************/
MXD_STATUS mxdSerdesSetRxLoopback
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_BOOL loopbackState
)
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_16 status = MXD_OK;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesSetRxLoopback: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    status = (MXD_16)mxdWrapperSetRxLoopback(pSerdesDev, sAddr, loopbackState);
    if (status != MXD_OK)
    {
        MXD_DBG_ERROR("mxdSerdesSetRxLoopback: Failed\n");
        return MXD_FAIL;
   }
    
    MXD_DBG_INFO("mxdSerdesSetRxLoopback: Completed\n");
    
    return MXD_OK;
}

/******************************************************************************
 MXD_STATUS mxdSerdesSetLoopback
 loopbackMode:
     MXD_CLEAR_SERDES_LOOPBACK(0)
     MXD_DEEP_SERDES_LOOPBACK(1) 
     MXD_SHALLOW_SERDES_LOOPBACK(2)
*******************************************************************************/
MXD_STATUS mxdSerdesSetLoopback
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_U16 loopbackMode  
)                           
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_U16 status = MXD_OK;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesSetLoopback: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    if (loopbackMode > MXD_SHALLOW_SERDES_LOOPBACK)
    {
        MXD_DBG_ERROR("mxdSerdesSetLoopback: Invalid loopbackMode:%u\n", loopbackMode);
        return MXD_FAIL;
   }

    switch(loopbackMode)
    {
    case MXD_CLEAR_SERDES_LOOPBACK:
        status = (MXD_U16)mxdWrapperSerdesInt(pSerdesDev, sAddr, 0x8, 0x0300);
        break;

    case MXD_DEEP_SERDES_LOOPBACK:
        status = (MXD_U16)mxdWrapperSerdesInt(pSerdesDev, sAddr, 0x8, 0x0301);
        break;

    case MXD_SHALLOW_SERDES_LOOPBACK:
        status = (MXD_U16)mxdWrapperSerdesInt(pSerdesDev, sAddr, 0x8, 0x0310);
        break;

    default:
        MXD_DBG_ERROR("mxdSerdesSetLoopback: Invalid loopbackMode:%u\n", loopbackMode);
        return MXD_FAIL;
        break;
    }
    
    if (status != 0x8) /* loopback int 0x8 returns 0x8 for success*/
    {
        MXD_DBG_ERROR("mxdSerdesSetLoopback: Failed\n");
        return MXD_FAIL;
   }

    MXD_DBG_INFO("mxdSerdesSetLoopback: Completed\n");
    
    return MXD_OK;
}

/******************************************************************************
 MXD_STATUS mxdSerdesPRBSDiagnostic
*******************************************************************************/
MXD_STATUS mxdSerdesPRBSDiagnostic
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 txSerDesAddr,
    IN MXD_U16 rxSerDesAddr,
    IN MXD_U16 bitRateDivider,
    IN MXD_BOOL intLoopbackMode,
    IN MXD_SERDES_RX_CMP_MODE_TYPE rxCmpMode,
    IN MXD_SERDES_TX_DATA_TYPE typePRBS
)
{
    MXD_STATUS status = MXD_OK;
    MXD_U32 errCount;

    if ((!pDev) || (!txSerDesAddr) || (txSerDesAddr > MXD_SERDES_LANE_COUNT) ||
        (!rxSerDesAddr) || (rxSerDesAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesPRBSDiagnostic: Invalid pDev:0x%08X or Serdes Tx Lane:%u or Rx Lane:%u\n", 
                      pDev, txSerDesAddr, rxSerDesAddr);
        return MXD_FAIL;
    }

    if (txSerDesAddr != rxSerDesAddr)
    {
        if (intLoopbackMode == MXD_ENABLE)
        {
            MXD_DBG_ERROR("mxdSerdesPRBSDiagnostic: intLoopbackMode must be disabled if Rx != Tx lane\n");
            return MXD_FAIL;
        }

        /* needs to init the Rx bitRateDivider if Tx/Rx is not the same */
        ATTEMPT(mxdSerdesInitBitRate(pDev, rxSerDesAddr, bitRateDivider, intLoopbackMode));
    } 

    /* setting the bit rate using the bitRateDivider ratio */
    ATTEMPT(mxdSerdesInitBitRate(pDev, txSerDesAddr, bitRateDivider, intLoopbackMode));

    /* tune the Rx lane iCal with the 4 values. 
       Set useDefault=1 if default values are desired */
    ATTEMPT(mxdSerdesTune_iCal(pDev, rxSerDesAddr, 0, 0, 0, 0, 1)); /* use default */

    /* give it about 8s to settle down after tuning the iCal */
    ATTEMPT(mxdWait(pDev, (8*1000))); 

    /* set Rx lane to TEST_PATGEN comparison mode for testing the injecting error */
    ATTEMPT(mxdSerdesSetRxCmpMode(pDev, rxSerDesAddr, rxCmpMode));

    /* Set the PRBS pattern type on both the Rx and Tx lanes*/
    ATTEMPT(mxdSerdesSetRxCmpData(pDev, rxSerDesAddr, (MXD_SERDES_RX_CMP_TYPE)typePRBS));
    ATTEMPT(mxdSerdesSetTxPRBS(pDev, txSerDesAddr, typePRBS));

    /* enable all the Tx and Rx paths. */
    ATTEMPT(mxdSerdesSetTxRxEnable(pDev, rxSerDesAddr, MXD_ENABLE, MXD_ENABLE, MXD_ENABLE));

    /* reset Rx error count after starting the PRBS test */
    ATTEMPT(mxdSerdesGetErrCount(pDev, rxSerDesAddr, MXD_TRUE, &errCount)); /* reset error count */

    /* read the Rx error count after resetting the error count value */
    ATTEMPT(mxdSerdesGetErrCount(pDev, rxSerDesAddr, MXD_FALSE, &errCount)); 

    MXD_DBG_INFO("mxdSerdesPRBSDiagnostic: Successfully started PRBS test with errCount:%u\n", 
                 errCount);

    return status;

}


/******************************************************************************
 MXD_STATUS mxdSerdesReset
*******************************************************************************/
MXD_STATUS mxdSerdesReset
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr
)                         
{
    MXD_SER_DEV_PTR pSerdesDev;
    MXD_STATUS status = MXD_OK;

    pSerdesDev = (MXD_SER_DEV_PTR)pDev->serdesDev;

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MXD_SERDES_LANE_COUNT))
    {
        MXD_DBG_ERROR("mxdSerdesReset: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MXD_FAIL;
    }

    status = mxdWrapperResetSerdes(pSerdesDev, sAddr);
    
    if (status != MXD_OK)
    {
        MXD_DBG_ERROR("mxdSerdesReset: Failed\n");
        return MXD_FAIL;
   }

    MXD_DBG_INFO("mxdSerdesReset: Completed\n");
    
    return MXD_OK;
}


#endif /* MXD_ENABLE_SERDES_API */ 


    


