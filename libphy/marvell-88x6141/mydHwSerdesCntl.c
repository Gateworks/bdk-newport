/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions to call Serdes API functions, various 
Serdes features and diagnostic operations for the Marvell X7120/X6181/X6141 Device.  
The Serdes API component is included by default with define 
MYD_ENABLE_SERDES_API.
********************************************************************/
#include "mydApiRegs.h"
#include "mydApiTypes.h"
#include "mydUtils.h"
#include "mydHwCntl.h"
#include "mydDiagnostics.h"
#include "mydAPI.h"
#include "mydHwSerdesCntl.h"

const MYD_U16 MYD_SerdesID[MYD_MAX_PORTS]
                      [MYD_NUM_INTERFACE]
                      [MYD_NUM_LANES] = {{{1,2,3,4},   {5,6,7,8}},
                                         {{9,10,11,12},{13,14,15,16}},
                                         {{17,18,19,20},{21,22,23,24}},
                                         {{25,26,27,28},{29,30,31,32}}};

/* Maps the PortID to the SerDes lane number. 
   1st set of 8 = Port0; 2nd set of 8 = Port1, ... */
const MYD_U16 PortIDSerdesIDMap[MYD_MAX_SERDES_LANE] = {0,0,0,0,0,0,0,0,
                                                        1,1,1,1,1,1,1,1,
                                                        2,2,2,2,2,2,2,2,
                                                        3,3,3,3,3,3,3,3};

#define MYD_SERDES_CMD_RETRY_COUNT 100
/******************************************************************************
 MYD_STATUS mydExecuteIndirectSBusCmd
*******************************************************************************/
MYD_STATUS mydExecuteIndirectSBusCmd
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort
)
{
    MYD_U16 executionStatus = 0;
    MYD_U16 retry;

    /* wait till last command complete, then send execute and wait for completion */
    for (retry = 0; retry < MYD_SERDES_CMD_RETRY_COUNT; retry++)
    {
        if ((mydHwXmdioRead(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_EXECUTION, &executionStatus) != MYD_OK) ||
            ((executionStatus & 0x3) != 0))
        {
            ATTEMPT(mydWait(pDev, 1));
        }
        else
        {
            break;
        }
    }

    if ((executionStatus & 0x3) != 0)
    {
        MYD_DBG_ERROR("mydExecuteIndirectSBusCmd: executionStatus failed: 0x%x\n", executionStatus);
        return MYD_FAIL;
    }

    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_EXECUTION, 0x1));

    for (retry = 0; retry < MYD_SERDES_CMD_RETRY_COUNT; retry++)
    {
        if ((mydHwXmdioRead(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_EXECUTION, &executionStatus) != MYD_OK) ||
            ((executionStatus & 0x3) != 0))
        {
            ATTEMPT(mydWait(pDev, 1));
        }
        else
        {
            break;
        }
    }

    if ((executionStatus & 0x3) != 0)
    {
        MYD_DBG_ERROR("mydExecuteIndirectSBusCmd: executionStatus2 failed: 0x%x\n", executionStatus);
        return MYD_FAIL;
    }

    return MYD_OK;
}


/******************************************************************************
 MYD_STATUS mydIndirectSBusWrite
*******************************************************************************/
MYD_STATUS mydIndirectSBusWrite
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 sBusReceiverAddr, 
    IN MYD_U16 regAddr, 
    IN MYD_U16 dataH, 
    IN MYD_U16 dataL, 
    OUT MYD_U16 *resultCode
)
{
    MYD_STATUS status = MYD_OK; 
    MYD_U16 retResultCode;

    /* Store the command, SBus receiver address, and register address */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_COMMAND_REG, MYD_SBUS_WRITE));
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_ADDR_REG, 
                    (MYD_U16)((sBusReceiverAddr & 0xFF) << 8 | (regAddr & 0xFF))));

    /* If it is a SBus write command, also store the output data */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_INPUT_DATA_H, dataH));
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_INPUT_DATA_L, dataL));

    /* set Sbus command receive data valid selection mode to level */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_RX_DATA_VALID, 0x00));

    /* execute command */
    if ((mydExecuteIndirectSBusCmd(pDev, mdioPort)) != MYD_OK)
    {
        status = MYD_FAIL;
    }

    /* store result code */
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_RESULT_CODE, &retResultCode));

    *resultCode = retResultCode & 0x07;

    /* clean execution bit */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_EXECUTION, 0x00));

    return status;
}

/******************************************************************************
 MYD_STATUS mydIndirectSBusWriteNoVerify
*******************************************************************************/
MYD_STATUS mydIndirectSBusWriteNoVerify
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 sBusReceiverAddr, 
    IN MYD_U16 regAddr, 
    IN MYD_U16 dataH, 
    IN MYD_U16 dataL, 
    OUT MYD_U16 *resultCode
)
{
    MYD_STATUS status = MYD_OK; 

    /* Store the command, SBus receiver address, and register address */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_COMMAND_REG, MYD_SBUS_WRITE));
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_ADDR_REG, 
                    (MYD_U16)((sBusReceiverAddr & 0xFF) << 8 | (regAddr & 0xFF))));

    /* If it is a SBus write command, also store the output data */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_INPUT_DATA_H, dataH));
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_INPUT_DATA_L, dataL));

    /* set Sbus command receive data valid selection mode to level */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_RX_DATA_VALID, 0x00));

    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_EXECUTION, 0x1));
    *resultCode = 1;

    /* clean execution bit */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_EXECUTION, 0x00));

    return status;
}

/******************************************************************************
 MYD_STATUS mydIndirectSBusRead
*******************************************************************************/
MYD_STATUS mydIndirectSBusRead
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 sBusReceiverAddr, 
    IN MYD_U16 regAddr, 
    OUT MYD_U16 *dataH, 
    OUT MYD_U16 *dataL, 
    OUT MYD_U16 *resultCode
)
{
    MYD_STATUS status = MYD_OK; 
    MYD_U16 retResultCode;
    MYD_U16 tempH = 0;
    MYD_U16 tempL = 0;

    /* Store the command, SBus receiver address, and register address */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_COMMAND_REG, MYD_SBUS_READ));
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_ADDR_REG, 
                            (MYD_U16)((sBusReceiverAddr & 0xFF) << 8 | (regAddr & 0xFF))));

    /* set Sbus command receive data valid selection mode to level */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_RX_DATA_VALID, 0x00));

    /* execute command */
    if ((mydExecuteIndirectSBusCmd(pDev, mdioPort))!= MYD_OK)
    {
        status = MYD_FAIL;
    }

    /* verify data is correctly written to register */
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_OUTPUT_DATA_L, &tempL));
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_OUTPUT_DATA_H, &tempH));

    *dataH = (MYD_U16)tempH;
    *dataL = (MYD_U16)tempL;

    /* store result code */
    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_RESULT_CODE, &retResultCode));

    *resultCode = retResultCode & 0x07;

    /* clean execution bit */
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_EXECUTION, 0x00));

    return status;
}

 
/******************************************************************************
 MYD_STATUS mydSerdesInterrupt
*******************************************************************************/
MYD_STATUS mydSerdesInterrupt
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 sBusReceiverAddr, 
    IN MYD_U16 interruptCode, 
    IN MYD_U16 interruptData, 
    OUT MYD_U16 *interruptResult
)
{
    MYD_U16 executionStatus;
    MYD_U16 retry;
    MYD_U16 tempInterruptOutput = 0;
    MYD_U16 tempInterruptStatus = 0;

    /* Store Serdes Interrupt command */
    if (mydIndirectSBusWrite(pDev, mdioPort, 
                             sBusReceiverAddr, 
                             MYD_SBUS_SERDES_INTR_CMD, 
                             interruptCode, 
                             interruptData, 
                             &executionStatus) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydSerdesInterrupt: mydIndirectSBusWrite INTR_CMD failed: 0x%x\n", executionStatus);
        return MYD_FAIL;
    }
    if ((executionStatus & 0x7) != MYD_SBUS_WRITE_COMPLETE)
    {
        MYD_DBG_ERROR("mydSerdesInterrupt: MYD_SBUS_SERDES_INTR_CMD executionStatus: 0x%x\n", executionStatus);
        return MYD_FAIL;
    }

    /* readback interrupt result until interrupt has been completed */
    for (retry = 0; retry < 100; retry++)
    {
        if (mydIndirectSBusRead(pDev, mdioPort,
                                sBusReceiverAddr, 
                                MYD_SBUS_SERDES_INTR_RESULT, 
                                &tempInterruptStatus, 
                                &tempInterruptOutput, 
                                &executionStatus) == MYD_FAIL)
        {
            MYD_DBG_ERROR("mydSerdesInterrupt: mydIndirectSBusWrite INTR_RESULT failed: 0x%x\n", 
                          executionStatus);
            return MYD_FAIL;
        }

        if ((executionStatus & 0x7) != MYD_SBUS_READ_COMPLETE)
        {
            MYD_DBG_ERROR("mydSerdesInterrupt: MYD_SBUS_SERDES_INTR_RESULT executionStatus: 0x%x\n", executionStatus);
            return MYD_FAIL;
        }

        if ((tempInterruptStatus & 0x01) == 0) /* if interrupts complete, stop waiting */
        {
            break;
        }

        ATTEMPT(mydWait(pDev, 5));
    }

    *interruptResult = (MYD_U16)(tempInterruptOutput & 0xFFFF);

    if ((tempInterruptStatus & 0x01) != 0) /* if interrupt still not completed after 500ms, quit */
    {
        MYD_DBG_ERROR("mydSerdesInterrupt: Device Access timeout tempInterruptStatus: 0x%x\n", 
                      tempInterruptStatus);
        return MYD_FAIL;
    }

    return MYD_OK;
}


/******************************************************************************
 MYD_STATUS mydSbusInterrupt
*******************************************************************************/
MYD_STATUS mydSbusInterrupt
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 interruptCode, 
    IN MYD_U16 interruptInput, 
    OUT MYD_U16 *interruptResult, 
    OUT MYD_U16 *interruptStatus
)
{
    MYD_U16 executionStatus;
    MYD_U16 tempInterruptOutput = 0;
    MYD_U16 tempInterruptStatus = 0;
    MYD_U16 retry;

    /* Store SBus Interrupt command */
    if (mydIndirectSBusWrite(pDev, mdioPort,
                             MYD_SBUS_SBUS_MASTER, 
                             MYD_SBUS_MASTER_INTR_CMD, 
                             interruptInput, 
                             interruptCode, 
                             &executionStatus) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydSbusInterrupt: Device Access timeout INTR_CMD failed: 0x%x\n", executionStatus);
        return MYD_FAIL;
    }

    if ((executionStatus & 0x7) != MYD_SBUS_WRITE_COMPLETE)
    {
        MYD_DBG_ERROR("mydSbusInterrupt: MYD_SBUS_MASTER_INTR_CMD executionStatus: 0x%x\n", executionStatus);
        return MYD_FAIL;
    }

    /* assert interrupt and wait till complete or timeout */
    if (mydIndirectSBusWrite(pDev, mdioPort, 
                             MYD_SBUS_SBUS_MASTER, 
                             MYD_SBUS_MASTER_INTR_STATUS, 
                             0x00, 
                             0x01, 
                             &executionStatus) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydSbusInterrupt: Device Access timeout INTR_STATUS failed: 0x%x\n", executionStatus);
        return MYD_FAIL;
    }
    
    if ((executionStatus & 0x7) != MYD_SBUS_WRITE_COMPLETE)
    {
        MYD_DBG_ERROR("mydSbusInterrupt: MYD_SBUS_MASTER_INTR_STATUS executionStatus: 0x%x\n", executionStatus);
        return MYD_FAIL;
    }

    /* read back interrupt result until interrupt has been completed */
    for (retry = 0; retry < 500; retry++)
    {
        if (mydIndirectSBusRead(pDev, mdioPort, 
                                MYD_SBUS_SBUS_MASTER, 
                                MYD_SBUS_MASTER_INTR_RESULT, 
                                &tempInterruptOutput, 
                                &tempInterruptStatus, 
                                &executionStatus) == MYD_FAIL)
        {
            MYD_DBG_ERROR("mydSbusInterrupt: Device Access timeout INTR_RESULT failed: 0x%x\n", executionStatus);
            return MYD_FAIL;
        }

        if ((executionStatus & 0x7) != MYD_SBUS_READ_COMPLETE)
        {
            MYD_DBG_ERROR("mydSbusInterrupt: MYD_SBUS_MASTER_INTR_RESULT executionStatus: 0x%x\n", executionStatus);
            return MYD_FAIL;
        }
        
        if ((tempInterruptStatus & 0x8000) == 0)
        {
            break;
        }

        ATTEMPT(mydWait(pDev, 1));
    }

    *interruptStatus = (MYD_U16)(tempInterruptStatus & 0xFFFF);
    *interruptResult = (MYD_U16)(tempInterruptOutput & 0xFFFF);

    if ((tempInterruptStatus & 0x8000) != 0) /* if interrupt still not completed after 500ms, quit */
    {
        MYD_DBG_ERROR("mydSbusInterrupt: Device Access timeout tempInterruptStatus: 0x%x\n", tempInterruptStatus);
        return MYD_FAIL;
    }

    return MYD_OK;
}

/******************************************************************************
 MYD_STATUS mydSerdesIntWrite
*******************************************************************************/
MYD_STATUS mydSerdesIntWrite
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 regAddr, 
    IN MYD_U16 dataH, 
    IN MYD_U16 dataL
)
{
    MYD_U16 serdesInterruptAddr;
    MYD_U16 retStatus;

    serdesInterruptAddr = (regAddr & 0xFF00) >> 8; 

    if (mydIndirectSBusWrite(pDev, mdioPort, serdesInterruptAddr, MYD_SBUS_SERDES_INTR_CMD, 
                             dataH, dataL, &retStatus) == MYD_FAIL)
    {
        MYD_DBG_ERROR("mydSerdesIntWrite: mydIndirectSBusWrite failed: 0x%x\n", retStatus);
        return MYD_FAIL;
    }
    if ((retStatus & 0x7) != MYD_SBUS_WRITE_COMPLETE)
    {
        MYD_DBG_ERROR("mydSerdesIntWrite: mydIndirectSBusWrite write error: 0x%x\n", retStatus);
        return MYD_FAIL;
    }

    return MYD_OK;
}


/******************************************************************************
 MYD_STATUS mydSerdesGetVoltage
*******************************************************************************/
MYD_STATUS mydSerdesGetVoltage
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 mdioPort,
   OUT MYD_U16 *coreVoltage,
   OUT MYD_U16 *DVDDVoltage,
   OUT MYD_U16 *AVDDVoltage
)
{
    MYD_U16 voltageReading;
    MYD_U16 interruptStatus;

    ATTEMPT(mydSbusInterrupt(pDev, mdioPort, MYD_SBUS_VOLTAGE_DATA, (MYD_U16)((0 << 12) | MYD_SBUS_TEMPERATURE_SENSOR), 
                     &voltageReading, &interruptStatus));
    *coreVoltage = (MYD_U16)((voltageReading & 0xFFF) * 0.5);

    ATTEMPT(mydSbusInterrupt(pDev, mdioPort, MYD_SBUS_VOLTAGE_DATA, (MYD_U16)((1 << 12) | MYD_SBUS_TEMPERATURE_SENSOR), 
                     &voltageReading, &interruptStatus));
    *DVDDVoltage = (MYD_U16)((voltageReading & 0xFFF) * 0.5);
    
    ATTEMPT(mydSbusInterrupt(pDev, mdioPort, MYD_SBUS_VOLTAGE_DATA, (MYD_U16)((2 << 12) | MYD_SBUS_TEMPERATURE_SENSOR), 
                     &voltageReading, &interruptStatus));
    *AVDDVoltage = (MYD_U16)((voltageReading & 0xFFF) * 0.5);

    MYD_DBG_INFO("mydSerdesGetVoltage: voltages Core:%umV; DVDD:%umV; AVDD:%umV\n", 
                 *coreVoltage, *DVDDVoltage, *AVDDVoltage);

    return MYD_OK;
}


/******************************************************************************
 MYD_STATUS mydSerdesGetTemperature
*******************************************************************************/
MYD_STATUS mydSerdesGetTemperature
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 mdioPort,
   OUT MYD_32 *coreTemperature
)
{
    MYD_U16 temperatureReading;
    MYD_U16 interruptStatus;

    ATTEMPT(mydSbusInterrupt(pDev, mdioPort, MYD_SBUS_TEMPERATURE_DATA, (MYD_U16)((0 << 12) | MYD_SBUS_TEMPERATURE_SENSOR), 
                             &temperatureReading, &interruptStatus));

    if (temperatureReading & 0x0800)
    {
        *coreTemperature = (((~temperatureReading + 1) & 0x7FF) * 125) * -1;
    }
    else
    {
        *coreTemperature = (temperatureReading & 0x7FF) * 125;
    }

    MYD_DBG_INFO("mydSerdesGetTemperature: coreTemperature:%7dmC\n", 
                 *coreTemperature);

    return MYD_OK;
}


/******************************************************************************
 MYD_STATUS mydSerdesGetRevision
*******************************************************************************/
MYD_STATUS mydSerdesGetRevision
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 mdioPort,
   OUT MYD_U16 *serdesRevision,
   OUT MYD_U16 *sbmRevision
)
{
    MYD_U16 interruptStatus;

    ATTEMPT(mydSerdesInterrupt(pDev, mdioPort, 1, 0x0, 0x0, serdesRevision));
         
    ATTEMPT(mydSbusInterrupt(pDev, mdioPort, 0, 0, sbmRevision, &interruptStatus));

    MYD_DBG_INFO("mydSerdesGetRevision: SerDes revision:0x%04X SBM revision:0x%04X\n",
                 *serdesRevision, *sbmRevision);

    return MYD_OK;
}

#if MYD_ENABLE_SERDES_API
/******************************************************************************
 MYD_STATUS mydSerdesGetPortID
    Internally used to return the port index based on the SerDes device structure
*******************************************************************************/
MYD_STATUS mydSerdesGetPortID
(
    IN MYD_DEV_PTR pDev,
    IN MYD_SER_DEV_PTR pSerdesDev,
    OUT MYD_U16 *portIndex
)
{
    MYD_U16 i;

    for (i=0; i<pDev->portCount; i++)
    {
        if (pSerdesDev == pDev->serdesDev[i])
        {
            *portIndex = i;
            return MYD_OK;
        }
    }

    return MYD_FAIL;
}

/******************************************************************************
 MYD_UINT mydSerdesMDIO
    Internally used for the SerDes MDIO access in mydInitSerdesDev
*******************************************************************************/
MYD_UINT mydSerdesMDIO
(
    IN MYD_SER_DEV_PTR pSerdesDev,
    IN uint sbusAddr,   
    IN MYD_U8 regAddr,
    IN MYD_U8 mdioCmd,
    OUT uint *sbusData
)
{
    MYD_U16 cmdSucceeded = FALSE;  /* TRUE if SBus call succeeds, FALSE if not. */
    MYD_U16 retData = 0;
    MYD_U16 cmd = 0;
    MYD_U16 sbusRegAddr;
    MYD_U16 dataH = 0;
    MYD_U16 dataL = 0;
    MYD_U16 outDataL = 0;
    MYD_U16 outDataH = 0;
    MYD_U16 portIndex, mdioPort;

    MYD_DEV_PTR pDev =(MYD_DEV_PTR)pSerdesDev->client_data;

    ATTEMPT((mydSerdesGetPortID(pDev, pSerdesDev, &portIndex)));
    mdioPort = pDev->mdioPort + portIndex;

    sbusRegAddr =(MYD_U16)(sbusAddr << 8) + (MYD_U16)regAddr;
    dataH = (MYD_U16)(*sbusData >> 16);
    dataL = (MYD_U16)(*sbusData & 0xFFFF);
    
    if (mdioCmd == 1)      /* Write */
    {
        cmd = MYD_SBUS_WRITE;
    }
    else if (mdioCmd == 2) /* Read */
    {
       cmd = MYD_SBUS_READ;
    }
    else if (mdioCmd == 0) /* ADDR */
    {
        cmd = MYD_SBUS_ADDR;
    }

    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_COMMAND_REG, cmd));
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_ADDR_REG, sbusRegAddr));

    if ((cmd & 0x1) == 0x1) /* write */
    {
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_INPUT_DATA_H, dataH));
        ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_INPUT_DATA_L, dataL));
    }

    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_RX_DATA_VALID, 0x0)); 

    if (mydExecuteIndirectSBusCmd(pDev, mdioPort))
    {
        cmdSucceeded = MYD_FALSE;
        MYD_DBG_ERROR("Non Read, Failed\n");
    }
    else
    {
        cmdSucceeded = MYD_TRUE;
        /* MYD_DBG_INFO("Non Read, Succeed\n"); */
    }

    /* make sure it's done */ 
    /* MYD_DBG_INFO("SBUS: Execution complete\n"); */

    ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_RESULT_CODE, &retData)); 

    if ((cmd & 0x2) == 0x2) /* read */
    {
        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_OUTPUT_DATA_L, &outDataL));
        ATTEMPT(mydHwXmdioRead(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_OUTPUT_DATA_H, &outDataH));

        retData = ((MYD_U32)outDataH<<16) + outDataL;
        *sbusData = ((MYD_U32)outDataH<<16) + outDataL;
    }
    
    ATTEMPT(mydHwXmdioWrite(pDev, mdioPort, MYD_CHIP_REG, MYD_SBUS_EXECUTION, 0x0));   

    /* MYD_DBG_INFO("SBus %u %02x %02x 0x%08x, retData=%u\n", sbusAddr, regAddr, mdioCmd, *sbusData, retData); */
    
    if( !cmdSucceeded )
    {
        /* Log error: */
        MYD_DBG_ERROR("SBus %u, %02x %02x 0x%08x FAILED\n", sbusAddr, regAddr, cmd, *sbusData); 
    }
    
    return TRUE;
}

/******************************************************************************
 MYD_STATUS mydInitSerdesDev
*******************************************************************************/
MYD_STATUS mydInitSerdesDev
(
    IN MYD_DEV_PTR pDev
)
{   
    MYD_SER_DEV_PTR pSerdesDev[MYD_MAX_PORTS];
    MYD_U16 i;

    for (i=0; i<pDev->portCount; i++)
    {
        pSerdesDev[i] = mydWrapperAllocDevStruct();
        if (!pSerdesDev[i])
        {
            MYD_DBG_ERROR("mydInitSerdesDev: pSerdesDev is NULL\n");
            return MYD_FAIL;
        }

        pSerdesDev[i]->client_data = pDev;
        pSerdesDev[i]->debug = MYD_SER_LOG_OFF;  /* default SerDes debug to off */

#ifdef MYD_DEBUG 
        switch (myd_debug_level)
        {
            case MYD_DBG_OFF_LVL:
                pSerdesDev[i]->debug = MYD_SER_LOG_OFF;  
                break;
            case MYD_DBG_ERR_LVL:
                pSerdesDev[i]->debug = MYD_SER_LOG_ERROR;  
                break;
            case MYD_DBG_INF_LVL:
            case MYD_DBG_ALL_LVL:
                pSerdesDev[i]->debug = MYD_SER_LOG_INFO;  
                break;
            default: 
                pSerdesDev[i]->debug = MYD_SER_LOG_INFO;  
                break;
        }
#endif
#ifdef MYD_PY_DEBUG
        pSerdesDev[i]->debug = MYD_SER_LOG_OFF;  
#endif
        pDev->serdesDev[i] = pSerdesDev[i];
    }

    for (i=0; i<pDev->portCount; i++)
    {
        mydWrapperSBusComm(pSerdesDev[i]);
        mydWrapperRegisterSBusFn(pSerdesDev[i], &mydSerdesMDIO, NULL, NULL);  

        mydWrapperConnect(pSerdesDev[i], 0, 0);
        mydWrapperGetIpInfo(pSerdesDev[i], 0);
    }
    
    return MYD_OK;
}

/******************************************************************************
 MYD_STATUS mydFreeSerdesDev
*******************************************************************************/
MYD_STATUS mydFreeSerdesDev
(
    IN MYD_DEV_PTR pDev
)
{   
    MYD_U16 i;

    for (i=0; i<pDev->portCount; i++)
    {
        if (pDev->serdesDev[i])
        {
            mydWrapperFreeDevStruct((MYD_SER_DEV_PTR)pDev->serdesDev[i]);
        }
    }

    return MYD_OK;
}

/******************************************************************************
 MYD_STATUS mydGetSerdesAddress
*******************************************************************************/

MYD_STATUS mydGetSerdesAddress
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,     
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *sAddr
)
{
    if (host_or_line == MYD_HOST_SIDE)
    {
        *sAddr = MYD_MAPPED_SERDES_ID(MYD_GET_PORT_IDX(pDev,mdioPort), MYD_HOST_MODE_IDX, laneOffset);
    }
    else
    {
        *sAddr = MYD_MAPPED_SERDES_ID(MYD_GET_PORT_IDX(pDev,mdioPort), MYD_LINE_MODE_IDX, laneOffset);
    }

    return MYD_OK;
}

/******************************************************************************
 MYD_STATUS mydSerdesTuneCTLE
*******************************************************************************/
MYD_STATUS mydSerdesTuneCTLE
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 sAddr,
    IN MYD_U16 dc,
    IN MYD_U16 lf,
    IN MYD_U16 hf,
    IN MYD_U16 bw,
    IN MYD_U16 optionCTLE 
)
{       
    MYD_STATUS status;
    MYD_U16 wrapperStatus;
    MYD_SER_INIT_DFE_TUNE_TYPE control;
    MYD_SER_DEV_PTR pSerdesDev;
    
    pSerdesDev = (MYD_SER_DEV_PTR)pDev->serdesDev[MYD_MAPPED_PORT_IDX(sAddr)];
    sAddr = MYD_PHY_SERDES_ADDR(sAddr);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MYD_SERDES_LANE_COUNT))
    {
        MYD_DBG_ERROR("mydSerdesTuneCTLE: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MYD_FAIL;
    }

    mydWrapperSerDesTuneInit(pSerdesDev, &control);

    /* Specify tuning options.
       The order of fixed and value array elements is DC, LF, HF and BW.
       If fixed[n] is 0, then fixed tuning for that value will be disabled.
       If fixed[n] is 1, then fixed tuning using value[n] will be enabled.
       All fixed setting changes are applied before tuning begins.
     */
    if (optionCTLE == MYD_FIXED_CTLE_DISABLED) /* MYD_FIXED_CTLE_DISABLED: fixed tuning for that value will be disabled. */ 
    {
        control.fixed[0] = control.fixed[1] = control.fixed[2] = control.fixed[3] = 0;
    }
    else if (optionCTLE == MYD_FIXED_CTLE_ENABLED) /* MYD_FIXED_CTLE_ENABLED: fixed tuning using value[n] will be enabled. */ 
    {
        control.fixed[0] = control.fixed[1] = control.fixed[2] = control.fixed[3] = 1;
        control.value[0] = dc;
        control.value[1] = lf;
        control.value[2] = hf;
        control.value[3] = bw;
    }
    else
    {
        MYD_DBG_ERROR("mydSerdesTuneCTLE: Invalid optionCTLE option\n");
        return MYD_FAIL;
    }

    wrapperStatus = mydWrapperSerDesTune(pSerdesDev, sAddr, &control);

    if (wrapperStatus == MYD_TRUE)
    {
        MYD_DBG_INFO("mydSerdesTuneCTLE: values dc:0x%X; lf:0x%X; hf:0x%X; bw:0x%X\n", 
                      control.value[0], control.value[1], control.value[2], control.value[3]);
        status = MYD_OK;
    }
    else
    {
        MYD_DBG_ERROR("mydSerdesTuneCTLE: Failed to tune iCal\n");
        status = MYD_FAIL;
   }

    return status;
}


/******************************************************************************
 MYD_STATUS mydSerdesTune_pCal
*******************************************************************************/
MYD_STATUS mydSerdesTune_pCal
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,
   IN MYD_DFE_TUNE_MODE tuneMode
)
{       
    MYD_STATUS status;
    MYD_U16 wrapperStatus;
    MYD_SER_INIT_DFE_TUNE_TYPE control;
    MYD_SER_DEV_PTR pSerdesDev;
    
    pSerdesDev = (MYD_SER_DEV_PTR)pDev->serdesDev[MYD_MAPPED_PORT_IDX(sAddr)];
    sAddr = MYD_PHY_SERDES_ADDR(sAddr);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MYD_SERDES_LANE_COUNT))
    {
        MYD_DBG_ERROR("mydSerdesGetRxDFE: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MYD_FAIL;
    }

    mydMemSet(&control, 0, sizeof(MYD_SER_INIT_DFE_TUNE_TYPE));

    control.tune_mode = (Avago_serdes_dfe_tune_mode_t)tuneMode;

    wrapperStatus = mydWrapperSerDesTune(pSerdesDev, sAddr, &control);

    if (wrapperStatus == MYD_TRUE)
    {
        MYD_DBG_INFO("mydSerdesTune_pCal: tuneMode:%u\n", tuneMode);
        status = MYD_OK;
    }
    else
    {
        MYD_DBG_ERROR("mydSerdesTune_pCal: Failed to tune pCal\n");
        status = MYD_FAIL;
   }

    return status;
}


/******************************************************************************
 MYD_STATUS mydSerdesGetEye
*******************************************************************************/
MYD_STATUS mydSerdesGetEye
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,
   IN MYD_U16 sampleSize,
   IN MYD_U16 highDefinition,
   IN MYD_U16 serdesLogLevel, 
   OUT MYD_SER_EYE_DATA_TYPE *pEyeData
)
{   
    MYD_16  status;
    MYD_U16 serdesTempLogLevel;
    MYD_SER_EYE_CONFIG_TYPE *pEyeConfig;
    MYD_SER_DEV_PTR pSerdesDev;
    MYD_U16 phySerDesAddr;

    pSerdesDev = (MYD_SER_DEV_PTR)pDev->serdesDev[MYD_MAPPED_PORT_IDX(sAddr)];
    phySerDesAddr = MYD_PHY_SERDES_ADDR(sAddr);

    if ((!pSerdesDev) || (!phySerDesAddr) || (phySerDesAddr > MYD_SERDES_LANE_COUNT))
    {
        MYD_DBG_ERROR("mydSerdesGetEye: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, phySerDesAddr);
        return MYD_FAIL;
    }

    if (pEyeData == NULL)
    {
        MYD_DBG_ERROR("mydSerdesGetEye: pEyeData memory must be pre-allocated\n", pSerdesDev, phySerDesAddr);
        return MYD_FAIL;
    }

    serdesTempLogLevel = (MYD_U16)pSerdesDev->debug;
    pSerdesDev->debug = serdesLogLevel;
    
    pEyeConfig = mydWrapperEyeAllocConfig(pSerdesDev);

    MYD_DBG_INFO("mydSerdesGetEye: eye_config_t size: %u; eye_data_t size: %u \n", 
                 (sizeof(MYD_SER_EYE_CONFIG_TYPE)), (sizeof(MYD_SER_EYE_DATA_TYPE)));

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

    status = (MYD_16)mydWrapperGetEye(pSerdesDev, phySerDesAddr, pEyeConfig, pEyeData);

    if( status < 0 )
    {
        mydWrapperEyeFreeConfig(pSerdesDev, pEyeConfig);

        MYD_DBG_ERROR("mydSerdesGetEye: Eye capture failed.\n");
        return MYD_FAIL;
    }

    /* Logged result to a file */
    /* mydWrapperEyeWriteToFile("eyeDataResult.log", pEyeData); */

    mydWrapperEyeFreeConfig(pSerdesDev, pEyeConfig);

    pSerdesDev->debug = serdesTempLogLevel;

    return MYD_OK;
}

/******************************************************************************
 MYD_STATUS mydSerdesGetTxFFE
*******************************************************************************/
MYD_STATUS mydSerdesGetTxFFE
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   OUT MYD_16 *preCursor,
   OUT MYD_16 *pre2Cursor,
   OUT MYD_16 *pre3Cursor,
   OUT MYD_16 *attenuation,
   OUT MYD_16 *postCursor
)
{
    MYD_SER_DEV_PTR pSerdesDev;
    MYD_SER_TX_EQ_TYPE txEq;
    MYD_16 status;

    pSerdesDev = (MYD_SER_DEV_PTR)pDev->serdesDev[MYD_MAPPED_PORT_IDX(sAddr)];
    sAddr = MYD_PHY_SERDES_ADDR(sAddr);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MYD_SERDES_LANE_COUNT))
    {
        MYD_DBG_ERROR("mydSerdesGetTxFFE: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MYD_FAIL;
    }

    status = (MYD_16)mydWrapperGetTxFFE(pSerdesDev, sAddr, &txEq);
    
    MYD_DBG_INFO("mydSerdesGetTxFFE: preCursor:%d; pre2Cursor:%d; pre3Cursor:%d; attenuation:%u; postCursor:%d\n", 
                 txEq.pre, txEq.pre2, txEq.pre3, txEq.atten, txEq.post);
    
    if (status == MYD_OK)
    {
        *preCursor   = txEq.pre;
        *pre2Cursor  = txEq.pre2;
        *pre3Cursor  = txEq.pre3;
        *attenuation = txEq.atten;
        *postCursor  = txEq.post;
    }
    else
    {
       MYD_DBG_ERROR("mydSerdesGetTxFFE: Failed with status:0x%08X\n", status);
       return MYD_FAIL;
    }

    return MYD_OK;
}

/******************************************************************************
 MYD_STATUS mydSerdesSetTxFFE
*******************************************************************************/
MYD_STATUS mydSerdesSetTxFFE
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   IN MYD_16 preCursor,
   IN MYD_16 pre2Cursor,
   IN MYD_16 pre3Cursor,
   IN MYD_16 attenuation,
   IN MYD_16 postCursor
)
{
    MYD_SER_DEV_PTR pSerdesDev;
    MYD_SER_TX_EQ_TYPE txEq;
    MYD_16 status;

    pSerdesDev = (MYD_SER_DEV_PTR)pDev->serdesDev[MYD_MAPPED_PORT_IDX(sAddr)];
    sAddr = MYD_PHY_SERDES_ADDR(sAddr);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MYD_SERDES_LANE_COUNT))
    {
        MYD_DBG_ERROR("mydSerdesSetTxFFE: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MYD_FAIL;
    }

    /* basic sanity check for inputs within ranges; 
       these ranges may not apply to all modes and signal types */
    if ((preCursor < -7) || (preCursor > 15) || (pre2Cursor < -7) || (pre2Cursor > 15) ||
        (pre3Cursor < -1) || (pre3Cursor > 1) || (postCursor < -31) || (postCursor > 31) ||
        (attenuation < 0) || (attenuation > 31))
    {
        MYD_DBG_ERROR("mydSerdesSetTxFFE: invalid FFE values - preCursor:%d; pre2Cursor:%d; pre3Cursor:%d; attenuation:%d; postCursor:%d\n",
                       preCursor, pre2Cursor, pre3Cursor, preCursor, attenuation, postCursor);
        return MYD_FAIL;
    }

    mydMemSet(&txEq, 0, sizeof(MYD_SER_TX_EQ_TYPE));

    txEq.pre   = preCursor;
    txEq.pre2  = pre2Cursor;
    txEq.pre3  = pre3Cursor;
    txEq.atten = attenuation;
    txEq.post  = postCursor;

    status = (MYD_16)mydWrapperSetTxFFE(pSerdesDev, sAddr, &txEq);
    
    MYD_DBG_INFO("mydSerdesSetTxFFE: preCursor:%d; pre2Cursor:%d; pre3Cursor:%d; attenuation:%u; postCursor:%d\n", 
                 txEq.pre, txEq.pre2, txEq.pre3, txEq.atten, txEq.post);
    
    if (status != MYD_OK)
    {
        MYD_DBG_ERROR("mydSerdesSetTxFFE: Failed with status:0x%08X\n", status);
        return MYD_FAIL;
    }

    return MYD_OK;
}

/******************************************************************************
 MYD_STATUS mydSerdesGetStateDump
*******************************************************************************/
MYD_STATUS mydSerdesGetStateDump
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr
)
{
    MYD_SER_DEV_PTR pSerdesDev;
    MYD_PVOID strBuf = NULL;
    
    pSerdesDev = (MYD_SER_DEV_PTR)pDev->serdesDev[MYD_MAPPED_PORT_IDX(sAddr)];
    sAddr = MYD_PHY_SERDES_ADDR(sAddr);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MYD_SERDES_LANE_COUNT))
    {
        MYD_DBG_ERROR("mydSerdesGetStateDump: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MYD_FAIL;
    }

    /* pSerdesDev->debug = 2; */
    strBuf = mydWrapperGetStateDump(pSerdesDev, sAddr, 0, 1);

    if (strBuf)
    {
        MYD_DBG_INFO("%s\n", strBuf);
        free(strBuf);
    }

    return MYD_OK;
}


#define MYD_ICalInProgress  0x01
#define MYD_PCalInProgress  0x02
#define MYD_VosInProgress   0x04
#define MYD_RunICal         0x10
#define MYD_RunPCal         0x20
#define MYD_DetectEI        0x200

/******************************************************************************
 MYD_STATUS mydSerdesGetRxDFEStatus
*******************************************************************************/
MYD_STATUS mydSerdesGetRxDFEStatus
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   OUT MYD_BOOL *dfeStatusICalInProgress,  
   OUT MYD_BOOL *dfeStatusPCalInProgress,  
   OUT MYD_BOOL *dfeStatusVosInProgress,   
   OUT MYD_BOOL *dfeStatusRunICal,         
   OUT MYD_BOOL *dfeStatusRunPCal,         
   OUT MYD_BOOL *dfeStatusDetectEI         
)
{
    MYD_SER_DEV_PTR pSerdesDev;
    MYD_U16 data = 0;

    pSerdesDev = (MYD_SER_DEV_PTR)pDev->serdesDev[MYD_MAPPED_PORT_IDX(sAddr)];
    sAddr = MYD_PHY_SERDES_ADDR(sAddr);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MYD_SERDES_LANE_COUNT))
    {
        MYD_DBG_ERROR("mydSerdesGetRxDFEStatus: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", 
                       pSerdesDev, sAddr);
        return MYD_FAIL;
    }

    /* mydWrapperGetRxDFEStatus doesn't return status. Assume success */
    data = mydWrapperGetRxDFEStatus(pSerdesDev, sAddr);

    *dfeStatusICalInProgress = (MYD_BOOL)((data & MYD_ICalInProgress)? 1:0);     
    *dfeStatusPCalInProgress = (MYD_BOOL)((data & MYD_PCalInProgress)? 1:0);     
    *dfeStatusVosInProgress = (MYD_BOOL)((data & MYD_VosInProgress)? 1:0);     
    *dfeStatusRunICal = (MYD_BOOL)((data & MYD_RunICal)? 1:0);             
    *dfeStatusRunPCal  = (MYD_BOOL)((data & MYD_RunPCal)? 1:0);            
    *dfeStatusDetectEI = (MYD_BOOL)((data & MYD_DetectEI)? 1:0);

    MYD_DBG_INFO("mydSerdesGetRxDFEStatus: ICalInProg:%u, PCalInProg:%u, VosInProg:%u, RunICal:%u, RunPCal:%u, DetectEI:%u\n", 
                 *dfeStatusICalInProgress, 
                 *dfeStatusPCalInProgress,
                 *dfeStatusVosInProgress,
                 *dfeStatusRunICal,
                 *dfeStatusRunPCal,
                 *dfeStatusDetectEI);

    return MYD_OK;
}


/******************************************************************************
 MYD_STATUS mydSerdesGetRxDFE
*******************************************************************************/
MYD_STATUS mydSerdesGetRxDFE
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 sAddr,  
    OUT MYD_U16 *dc,        /* DC-Restore value [0-255] */
    OUT MYD_U16 *lf,        /* CTLE Low-Frequency setting [0-15] */
    OUT MYD_U16 *hf,        /* CTLE High-Frequency setting [0-15] */
    OUT MYD_U16 *bw,        /* CTLE Band-width setting [0-15] */
    OUT MYD_U16 *gainShape1, /* CTLE gainShape1 setting */
    OUT MYD_U16 *gainShape2, /* CTLE gainShape2 setting */
    OUT MYD_U16 *dfeGAIN,   /* DFE Gain Tap strength setting [0-15] */
    OUT MYD_U16 *dfeGAIN2   /* DFE Gain Tap 2 strength setting [0-15] */
)
{
    MYD_SER_DEV_PTR pSerdesDev;
    MYD_SER_RX_DFE_TYPE rxDFE;
    
    pSerdesDev = (MYD_SER_DEV_PTR)pDev->serdesDev[MYD_MAPPED_PORT_IDX(sAddr)];
    sAddr = MYD_PHY_SERDES_ADDR(sAddr);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MYD_SERDES_LANE_COUNT))
    {
        MYD_DBG_ERROR("mydSerdesGetRxDFE: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MYD_FAIL;
    }

    mydMemSet(&rxDFE, 0, sizeof(MYD_SER_RX_DFE_TYPE));

    /* mydWrapperGetRxDFE doesn't return status. Assume success */
    mydWrapperGetRxDFE(pSerdesDev, sAddr, &rxDFE);

    *dc = rxDFE.dc;     
    *lf = rxDFE.lf;   
    *hf = rxDFE.hf;  
    *bw = rxDFE.bw;  
    *gainShape1 = rxDFE.gainshape1;
    *gainShape2 = rxDFE.gainshape2;
    *dfeGAIN = rxDFE.dfeGAIN;
    *dfeGAIN2 = rxDFE.dfeGAIN2;

    *dfeGAIN = (*dfeGAIN > 15)? 0:*dfeGAIN;
    *dfeGAIN2 = (*dfeGAIN2 > 15)? 0:*dfeGAIN2;

    MYD_DBG_INFO("mydSerdesGetRxDFE: sAddr::%u, DFE.dc:%u, DFE.lf:%u, DFE.hf:%u, DFE.bw:%u, gainShape1:%u, gainShape2:%u, DFE.dfeGAIN:%u, DFE.dfeGAIN2:%u\n", 
                 sAddr, rxDFE.dc, rxDFE.lf, rxDFE.hf, rxDFE.bw, *gainShape1, *gainShape2, *dfeGAIN, *dfeGAIN2);

    return MYD_OK;
}


/******************************************************************************
 MYD_STATUS mydSerdesGetTxPolarity
*******************************************************************************/
MYD_STATUS mydSerdesGetTxPolarity
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   OUT MYD_U16 *polarity
)
{
    MYD_SER_DEV_PTR pSerdesDev;

    pSerdesDev = (MYD_SER_DEV_PTR)pDev->serdesDev[MYD_MAPPED_PORT_IDX(sAddr)];
    sAddr = MYD_PHY_SERDES_ADDR(sAddr);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MYD_SERDES_LANE_COUNT))
    {
        MYD_DBG_ERROR("mydSerdesGetTxPolarity: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MYD_FAIL;
    }

    *polarity = (MYD_U16)mydWrapperGetTxPolarity(pSerdesDev, sAddr);
    
    MYD_DBG_INFO("mydSerdesGetTxPolarity: polarity:0x%X\n", *polarity);
    
    return MYD_OK;
}

/******************************************************************************
 MYD_STATUS mydSerdesSetTxPolarity
*******************************************************************************/
MYD_STATUS mydSerdesSetTxPolarity
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   IN MYD_U16 polarity
)
{
    MYD_SER_DEV_PTR pSerdesDev;
    MYD_16 status;

    pSerdesDev = (MYD_SER_DEV_PTR)pDev->serdesDev[MYD_MAPPED_PORT_IDX(sAddr)];
    sAddr = MYD_PHY_SERDES_ADDR(sAddr);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MYD_SERDES_LANE_COUNT))
    {
        MYD_DBG_ERROR("mydSerdesSetTxPolarity: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MYD_FAIL;
    }

    status = (MYD_16)mydWrapperSetTxPolarity(pSerdesDev, sAddr, polarity);
    
    MYD_DBG_INFO("mydSerdesSetTxPolarity: polarity:0x%X\n", polarity);
    
    if (status != MYD_OK)
    {
        return MYD_FAIL;
    }

    return MYD_OK;
}

/******************************************************************************
 MYD_STATUS mydSerdesGetRxPolarity
*******************************************************************************/
MYD_STATUS mydSerdesGetRxPolarity
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   OUT MYD_U16 *polarity
)
{
    MYD_SER_DEV_PTR pSerdesDev;

    pSerdesDev = (MYD_SER_DEV_PTR)pDev->serdesDev[MYD_MAPPED_PORT_IDX(sAddr)];
    sAddr = MYD_PHY_SERDES_ADDR(sAddr);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MYD_SERDES_LANE_COUNT))
    {
        MYD_DBG_ERROR("mydSerdesGetRxPolarity: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MYD_FAIL;
    }

    *polarity = (MYD_U16)mydWrapperGetRxPolarity(pSerdesDev, sAddr);
    
    MYD_DBG_INFO("mydSerdesGetRxPolarity: polarity:0x%X\n", *polarity);
    
    return MYD_OK;
}

/******************************************************************************
 MYD_STATUS mydSerdesSetRxPolarity
*******************************************************************************/
MYD_STATUS mydSerdesSetRxPolarity
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   IN MYD_U16 polarity
)
{
    MYD_SER_DEV_PTR pSerdesDev;
    MYD_U16 status;

    pSerdesDev = (MYD_SER_DEV_PTR)pDev->serdesDev[MYD_MAPPED_PORT_IDX(sAddr)];
    sAddr = MYD_PHY_SERDES_ADDR(sAddr);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MYD_SERDES_LANE_COUNT))
    {
        MYD_DBG_ERROR("mydSerdesSetRxPolarity: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MYD_FAIL;
    }

    status = (MYD_U16)mydWrapperSetRxPolarity(pSerdesDev, sAddr, polarity);
    
    MYD_DBG_INFO("mydSerdesSetRxPolarity: polarity:0x%X\n", polarity);
    
    if (status != MYD_OK)
    {
        return MYD_FAIL;
    }

    return MYD_OK;
}

/******************************************************************************
 MYD_STATUS mydSerdesTxInjectError
*******************************************************************************/
MYD_STATUS mydSerdesTxInjectError
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   IN MYD_U16 numErrors
)
{
    MYD_SER_DEV_PTR pSerdesDev;
    MYD_U16 status;

    pSerdesDev = (MYD_SER_DEV_PTR)pDev->serdesDev[MYD_MAPPED_PORT_IDX(sAddr)];
    sAddr = MYD_PHY_SERDES_ADDR(sAddr);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MYD_SERDES_LANE_COUNT))
    {
        MYD_DBG_ERROR("mydSerdesTxInjectError: Invalid pSerdesDev:0x%08X or Serdes Lane: %u\n", pSerdesDev, sAddr);
        return MYD_FAIL;
    }

    status = (MYD_U16)mydWrapperTxInjectError(pSerdesDev, sAddr, numErrors);
    
    MYD_DBG_INFO("mydSerdesTxInjectError: numErrors %u on Serdes %u\n", numErrors, sAddr);
    
    if (status != MYD_OK)
    {
        return MYD_FAIL;
    }

    return MYD_OK;
}


/******************************************************************************
 MYD_STATUS mydSerdesRxInjectError
*******************************************************************************/
MYD_STATUS mydSerdesRxInjectError
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   IN MYD_U16 numErrors
)
{
    MYD_SER_DEV_PTR pSerdesDev;
    MYD_U16 status;

    pSerdesDev = (MYD_SER_DEV_PTR)pDev->serdesDev[MYD_MAPPED_PORT_IDX(sAddr)];
    sAddr = MYD_PHY_SERDES_ADDR(sAddr);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MYD_SERDES_LANE_COUNT))
    {
        MYD_DBG_ERROR("mydSerdesRxInjectError: Invalid pSerdesDev:0x%08X or Serdes Lane: %u\n", pSerdesDev, sAddr);
        return MYD_FAIL;
    }

    status = (MYD_U16)mydWrapperRxInjectError(pSerdesDev, sAddr, numErrors);
    
    MYD_DBG_INFO("mydSerdesRxInjectError: numErrors %u on Serdes %u\n", numErrors, sAddr);
    
    if (status != MYD_OK)
    {
        return MYD_FAIL;
    }

    return MYD_OK;
}


/******************************************************************************
 MYD_STATUS mydSerdesGetCDRLock
*******************************************************************************/
MYD_STATUS mydSerdesGetCDRLock
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   OUT MYD_U16 *CDRLockState
)
{
    MYD_SER_DEV_PTR pSerdesDev;

    pSerdesDev = (MYD_SER_DEV_PTR)pDev->serdesDev[MYD_MAPPED_PORT_IDX(sAddr)];
    sAddr = MYD_PHY_SERDES_ADDR(sAddr);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MYD_SERDES_LANE_COUNT))
    {
        MYD_DBG_ERROR("mydSerdesGetCDRLock: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MYD_FAIL;
    }

    /*
      CDRLockState = 1 is locked; CDRLockState = 0 is not locked; 
    */
    *CDRLockState = (MYD_U16)mydWrapperGetCDRLock(pSerdesDev, sAddr);
    
    MYD_DBG_INFO("mydSerdesGetCDRLock: CDRLockState:0x%X\n", *CDRLockState);
    
    return MYD_OK;
}

/******************************************************************************
 MYD_STATUS mydSerdesPMDTrainingLog
*******************************************************************************/
MYD_STATUS mydSerdesPMDTrainingLog
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,
   OUT PMYD_TRAINING_INFO pTrainInfo
)
{
    MYD_SER_DEV_PTR pSerdesDev;
    MYD_SER_PMD_DEBUG_TYPE *pSerdesDebugStruct = NULL;
    MYD_U16 index = 0;

    pSerdesDev = (MYD_SER_DEV_PTR)pDev->serdesDev[MYD_MAPPED_PORT_IDX(sAddr)];
    sAddr = MYD_PHY_SERDES_ADDR(sAddr);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MYD_SERDES_LANE_COUNT))
    {
        MYD_DBG_ERROR("mydSerdesPMDTrainingLog: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MYD_FAIL;
    }

    if (!pTrainInfo)
    {
        MYD_DBG_ERROR("mydSerdesPMDTrainingLog: pTrainInfo is NULL\n");
        return MYD_FAIL;
    }
       
    mydMemSet(pTrainInfo, 0, (sizeof(MYD_TRAINING_INFO)));

    /* Allocate a PMD structure for training log */
    pSerdesDebugStruct = mydWrapperPMDAllocDebugStruct(pSerdesDev);
    if (pSerdesDebugStruct == NULL)
    {
        MYD_DBG_ERROR("mydSerdesPMDTrainingLog: pSerdesDebugSt is NULL\n");
        return MYD_FAIL;
    }

    mydWrapperPMDDebug(pSerdesDev, sAddr, pSerdesDebugStruct);
    
    pTrainInfo->reset = (MYD_BOOL)pSerdesDebugStruct->reset;
    pTrainInfo->rx_metric = pSerdesDebugStruct->rx_metric;
    pTrainInfo->local.preset = pSerdesDebugStruct->lcl->preset;
    pTrainInfo->local.initialize = pSerdesDebugStruct->lcl->initialize;
    pTrainInfo->remote.preset = pSerdesDebugStruct->remote->preset;
    pTrainInfo->remote.initialize = pSerdesDebugStruct->remote->initialize;
    pTrainInfo->last_local_request = pSerdesDebugStruct->last_local_request;
    mydMemCpy(&pTrainInfo->last_remote_request, &pSerdesDebugStruct->last_remote_request, 
              (sizeof(MYD_UINT)*8)); 

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
    mydWrapperPMDDebugPrint(pSerdesDev, pSerdesDebugStruct);
    mydWrapperPMDFreeDebugStruct(pSerdesDev, pSerdesDebugStruct);

    MYD_DBG_INFO("mydSerdesPMDTrainingLog: Completed\n");
    
    return MYD_OK;
}


/******************************************************************************
 MYD_STATUS mydSerdesReset
*******************************************************************************/
MYD_STATUS mydSerdesReset
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr
)                         
{
    MYD_SER_DEV_PTR pSerdesDev;
    MYD_STATUS status = MYD_OK;

    pSerdesDev = (MYD_SER_DEV_PTR)pDev->serdesDev[MYD_MAPPED_PORT_IDX(sAddr)];
    sAddr = MYD_PHY_SERDES_ADDR(sAddr);

    if ((!pSerdesDev) || (!sAddr) || (sAddr > MYD_SERDES_LANE_COUNT))
    {
        MYD_DBG_ERROR("mydSerdesReset: Invalid pSerdesDev:0x%08X or Serdes Lane:%u\n", pSerdesDev, sAddr);
        return MYD_FAIL;
    }

    status = mydWrapperResetSerdes(pSerdesDev, sAddr);
    
    if (status != MYD_OK)
    {
        MYD_DBG_ERROR("mydSerdesReset: Failed\n");
        return MYD_FAIL;
   }

    MYD_DBG_INFO("mydSerdesReset: Completed\n");
    
    return MYD_OK;
}


#endif /* MYD_ENABLE_SERDES_API */ 


    


