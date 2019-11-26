/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains function prototypes to call Serdes API functions, 
Serdes features and diagnostic operations for the Marvell X7120/X6181/X6141 Device.  
The Serdes API component is included by default with define 
MYD_ENABLE_SERDES_API.
********************************************************************/
#ifndef MYD_HWSERDESCNT_H
#define MYD_HWSERDESCNT_H

#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

/* 
   Below mapping applies to the 4-port X7120. For 1-port X6141, only 
   Port 0 mapping applies.

   The MYD_MAPPED_SERDES_ID returns the matching SerDes lane with the given
   parameters below.  Use the MYD_HOST_MODE_IDX and MYD_LINE_MODE_IDX
   definitions to identify the host or line side. 

   SerDes lane starts from 1 to 32 when calling SerDes diagnostic API 
   
   Port 0:    Host Side           Line Side
            Lane0: SerDesID 1    Lane0: SerDesID 5
            Lane1: SerDesID 2    Lane1: SerDesID 6
            Lane2: SerDesID 3    Lane2: SerDesID 7
            Lane3: SerDesID 4    Lane3: SerDesID 8

   Port 1:    Host Side           Line Side
            Lane0: SerDesID 9    Lane0: SerDesID 13
            Lane1: SerDesID 10   Lane1: SerDesID 14
            Lane2: SerDesID 11   Lane2: SerDesID 15
            Lane3: SerDesID 12   Lane3: SerDesID 16

   Port 2:    Host Side           Line Side
            Lane0: SerDesID 17   Lane0: SerDesID 21
            Lane1: SerDesID 18   Lane1: SerDesID 22
            Lane2: SerDesID 19   Lane2: SerDesID 23
            Lane3: SerDesID 20   Lane3: SerDesID 24

   Port 3:    Host Side           Line Side
            Lane0: SerDesID 25   Lane0: SerDesID 29
            Lane1: SerDesID 26   Lane1: SerDesID 30
            Lane2: SerDesID 27   Lane2: SerDesID 31
            Lane3: SerDesID 28   Lane3: SerDesID 32
 */

/* Use in MYD_MAPPED_SERDES_ID macro; MYD_SerdesID[] stores the mapping of 32 SerDes lanes */
/* [Port 0-3][MYD_HOST_MODE_IDX/MYD_LINE_MODE_IDX][LaneOffset 0-3] */
extern const MYD_U16 MYD_SerdesID[MYD_MAX_PORTS][MYD_NUM_INTERFACE][MYD_NUM_LANES]; 

/* Use in MYD_MAPPED_PORT_IDX macro; PortIDSerdesIDMap maps the 8 lanes to each port */
extern const MYD_U16 PortIDSerdesIDMap[MYD_MAX_SERDES_LANE]; 

/* Returns the SerDes ID [1-32] from provided Port ID, Host/Line index and lane offset */
#define MYD_MAPPED_SERDES_ID(portIDx,HostOrLinex,laneOffsetx) MYD_SerdesID[portIDx][HostOrLinex][laneOffsetx]

/* Returns the Port ID [0-3] with the provided SerDesID [1-32] */
#define MYD_MAPPED_PORT_IDX(SerdesIDx) PortIDSerdesIDMap[SerdesIDx-1]

/* Returns the physical SerDes ID [1-8] on a port with mapped SerDes ID [1-32] */
#define MYD_PHY_SERDES_ADDR(MappedSAddr) ((MappedSAddr & 0x7) ? (MappedSAddr & 0x7) : 8)

/* SBus address for each component */
#define MYD_SBUS_SBUS_MASTER  0xFD
#define MYD_SBUS_SBUS_SERDES  0xEE

/* SBus indirect access register */
#define MYD_SBUS_RX_DATA_VALID  0xF440
#define MYD_SBUS_COMMAND_REG    0xF441
#define MYD_SBUS_ADDR_REG       0xF442
#define MYD_SBUS_EXECUTION      0xF443
#define MYD_SBUS_INPUT_DATA_L   0xF444
#define MYD_SBUS_INPUT_DATA_H   0xF445
#define MYD_SBUS_RESULT_CODE    0xF446
#define MYD_SBUS_OUTPUT_DATA_L  0xF448
#define MYD_SBUS_OUTPUT_DATA_H  0xF449

/* SBus result return code MYD_SBUS_RESULT_CODE */
#define MYD_SBUS_RESET             0x0
#define MYD_SBUS_WRITE_COMPLETE    0x1
#define MYD_SBUS_WRITE_FAILED      0x2
#define MYD_SBUS_READ_ALL_COMPLETE 0x3
#define MYD_SBUS_READ_COMPLETE     0x4
#define MYD_SBUS_READ_FAILED       0x5
#define MYD_SBUS_CMD_ISSUE_DONE    0x6
#define MYD_SBUS_MODE_CHANGE_DONE  0x7

/* SBus Read/Write command */
#define MYD_SBUS_ADDR   0x20
#define MYD_SBUS_WRITE  0x21
#define MYD_SBUS_READ   0x22

/* SBus master register map */
#define MYD_SBUS_MASTER_INTR_CMD     0x02
#define MYD_SBUS_MASTER_INTR_STATUS  0x07
#define MYD_SBUS_MASTER_INTR_RESULT  0x08

/* Sbus SerDes Register */
#define MYD_SBUS_SERDES_INTR_CMD     0x03
#define MYD_SBUS_SERDES_INTR_RESULT  0x04

/* Sbus SerDes Diagnostic Register */
#define MYD_SBUS_TEMPERATURE_SENSOR  0x09
#define MYD_SBUS_TEMPERATURE_DATA    0x17
#define MYD_SBUS_VOLTAGE_DATA        0x18

#define MYD_SERDES_LANE_COUNT 8 /* 8 Serdes lanes on each port */

#if MYD_ENABLE_SERDES_API
#include "mydSerdes.h"
#endif 

/******************************************************************************
MYD_STATUS mydExecuteIndirectSBusCmd
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31 

 Outputs:
    None

 Returns:
    MYD_OK if command was executed successful, MYD_FAIL otherwise

 Description:
    The function issues an execute command after an indirect SBUS read or write 
    command is issued. 
    
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
******************************************************************************/
MYD_STATUS mydExecuteIndirectSBusCmd
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort
);


/******************************************************************************
MYD_STATUS mydIndirectSBusWrite
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 sBusReceiverAddr, 
    IN MYD_U16 regAddr, 
    IN MYD_U16 dataH, 
    IN MYD_U16 dataL, 
    OUT MYD_U16 *resultCode
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31 
    sBusReceiverAddr - SBUS address 
    regAddr - register address 
    dataH - 16-bit High word to be written
    dataL - 16-bit Low word to be written 

 Outputs:
    resultCode - returns 1 if write is successful. Otherwise 0. 

 Returns:
    MYD_OK if write was successful, MYD_FAIL otherwise

 Description:
    The function performs an indirect write on both the High and Low 16-bit words to the SBUS. 
    There are 3 parts to this operation. The SBUS write command, the High and Low 16-bit words
    and lastly issue the mydExecuteIndirectSBusCmd to execute the write. 
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
******************************************************************************/
MYD_STATUS mydIndirectSBusWrite
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 sBusReceiverAddr, 
    IN MYD_U16 regAddr, 
    IN MYD_U16 dataH, 
    IN MYD_U16 dataL, 
    OUT MYD_U16 *resultCode
);

/******************************************************************************
MYD_STATUS mydIndirectSBusWriteNoVerify
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 sBusReceiverAddr, 
    IN MYD_U16 regAddr, 
    IN MYD_U16 dataH, 
    IN MYD_U16 dataL, 
    OUT MYD_U16 *resultCode
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31 
    sBusReceiverAddr - SBUS address 
    regAddr - register address 
    dataH - 16-bit High word to be written
    dataL - 16-bit Low word to be written 

 Outputs:
    resultCode - returns 1 if write is successful. Otherwise 0. 

 Returns:
    MYD_OK if write was successful, MYD_FAIL otherwise

 Description:
    The function is similar to mydIndirectSBusWrite except it will not call 
    mydExecuteIndirectSBusCmd to verify the write.  This function is useful for
    large count of consecutive writes, i.e. firmware download, to reduce the write
    access time.   
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
******************************************************************************/
MYD_STATUS mydIndirectSBusWriteNoVerify
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 sBusReceiverAddr, 
    IN MYD_U16 regAddr, 
    IN MYD_U16 dataH, 
    IN MYD_U16 dataL, 
    OUT MYD_U16 *resultCode
);

/******************************************************************************
MYD_STATUS mydIndirectSBusRead
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 sBusReceiverAddr, 
    IN MYD_U16 regAddr, 
    OUT MYD_U16 *dataH, 
    OUT MYD_U16 *dataL, 
    OUT MYD_U16 *resultCode
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31 
    sBusReceiverAddr - SBUS address 
    regAddr - register address 

 Outputs:
    dataH - returns 16-bit High word of the requested address
    dataL - returns 16-bit Low word of the requested address 
    resultCode - returns 1 if write is successful. Otherwise 0. 

 Returns:
    MYD_OK if read was successful, MYD_FAIL otherwise

 Description:
    The function performs an indirect read on both the High and Low 16-bit words to the SBUS. 
    There are 3 parts to this operation. The SBUS read command, the High and Low 16-bit words
    and lastly issue the mydExecuteIndirectSBusCmd to execute the read. 
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
******************************************************************************/
MYD_STATUS mydIndirectSBusRead
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 sBusReceiverAddr, 
    IN MYD_U16 regAddr, 
    OUT MYD_U16 *dataH, 
    OUT MYD_U16 *dataL, 
    OUT MYD_U16 *resultCode
);

/******************************************************************************
MYD_STATUS mydSerdesInterrupt
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 sBusReceiverAddr, 
    IN MYD_U16 interruptCode, 
    IN MYD_U16 interruptData, 
    OUT MYD_U16 interruptResult
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31 
    sBusReceiverAddr - SBUS address 
    interruptCode - SerDes interrupt code to issue
    interruptData - SerDes interrupt data to issue

 Outputs:
    interruptResult - returns the result of the issued interrupt code and data 

 Returns:
    MYD_OK if interrupt issued was successful, MYD_FAIL otherwise

 Description:
    The function issue an interrupt code and data. It retries up to 100 time for
    the interrupt completion.   
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
******************************************************************************/
MYD_STATUS mydSerdesInterrupt
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 sBusReceiverAddr, 
    IN MYD_U16 interruptCode, 
    IN MYD_U16 interruptData, 
    OUT MYD_U16 *interruptResult
);


/******************************************************************************
MYD_STATUS mydSbusInterrupt
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 interruptCode, 
    IN MYD_U16 interruptInput, 
    OUT MYD_U16 *interruptResult, 
    OUT MYD_U16 *interruptStatus
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31 
    sBusReceiverAddr - SBUS address 
    interruptCode - SBUS interrupt code to issue
    interruptInput - SBUS interrupt input data to issue

 Outputs:
    interruptResult - returns the result of the issued interrupt code and data 
    interruptStatus - returns the status of the issued interrupt
    
 Returns:
    MYD_OK if interrupt issued was successful, MYD_FAIL otherwise

 Description:
    The function issue an interrupt code and data. It retries up to 500 time for
    the interrupt completion.   
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
******************************************************************************/
MYD_STATUS mydSbusInterrupt
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 interruptCode, 
    IN MYD_U16 interruptInput, 
    OUT MYD_U16 *interruptResult, 
    OUT MYD_U16 *interruptStatus
);

/******************************************************************************
MYD_STATUS mydSerdesIntWrite
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 regAddr, 
    IN MYD_U16 dataH, 
    IN MYD_U16 dataL
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31 
    regAddr - Serdes lane and interrupt address 
    dataH - 16-bit High word to be written
    dataL - 16-bit Low word to be written 

 Outputs:
    None 

 Returns:
    MYD_OK if write was successful, MYD_FAIL otherwise

 Description:
    The function performs an indirect write to the Serdes interrupt address using
    the Serdes communication protocol.  

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MYD_STATUS mydSerdesIntWrite
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 regAddr, 
    IN MYD_U16 dataH, 
    IN MYD_U16 dataL
);


/******************************************************************************
MYD_STATUS mydSerdesGetVoltage
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 mdioPort,
   OUT MYD_U16 *coreVoltage,
   OUT MYD_U16 *DVDDVoltage,
   OUT MYD_U16 *AVDDVoltage
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31

 Outputs:
    coreVoltage - Core voltage value
    DVDDVoltage - DVDD voltage value
    AVDDVoltage - AVDD voltage value
    
 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    The call returns the output voltages of the core, DVDD and AVDD. 
    The values return in the outputs are in millivolt(mV).
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MYD_STATUS mydSerdesGetVoltage
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 mdioPort,
   OUT MYD_U16 *coreVoltage,
   OUT MYD_U16 *DVDDVoltage,
   OUT MYD_U16 *AVDDVoltage
);


/******************************************************************************
MYD_STATUS mydSerdesGetTemperature
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 mdioPort,
   OUT MYD_32 *coreTemperature
)

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31

 Outputs:
    coreTemperature - Core temperature value
    
 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    The call returns the Core temperature. 
    The values return in the outputs are in milli-Celsius(mC).
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MYD_STATUS mydSerdesGetTemperature
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 mdioPort,
   OUT MYD_32 *coreTemperature
);


/******************************************************************************
MYD_STATUS mydSerdesGetRevision
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 mdioPort,
   OUT MYD_U16 *serdesRevision,
   OUT MYD_U16 *sbmRevision
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31

 Outputs:
    serdesRevision - SerDes revision
    sbmRevision - SBus master revision  
    
 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    This call returns the SerDes and SBus master revisions   
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MYD_STATUS mydSerdesGetRevision
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 mdioPort,
   OUT MYD_U16 *serdesRevision,
   OUT MYD_U16 *sbmRevision
);

#if MYD_ENABLE_SERDES_API

/******************************************************************************
 MYD_STATUS mydInitSerdesDev
(
    IN MYD_DEV_PTR pDev
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call

 Outputs:
    None
    
 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    This SerDes initialization function is called during mydInitDriver() when the
    MYD_ENABLE_SERDES_API is set to 1. This function allocates the device structure
    memory requires when the Serdes API is called. In addition, it will initialize
    the MDIO read/write function pointer for the serdes API operation.
      
 Side effects:
    None

 Notes/Warnings:
    The mydFreeSerdesDev must be called when the driver unloads or exits. The
    mydFreeSerdesDev will release the serdes device structure memory.
*******************************************************************************/
MYD_STATUS mydInitSerdesDev
(
    IN MYD_DEV_PTR pDev
);


/******************************************************************************
MYD_STATUS mydFreeSerdesDev
(
    IN MYD_DEV_PTR pDev
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call

 Outputs:
    None
    
 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    This function releases the Serdes API device structure memory.  
      
 Side effects:
    None

 Notes/Warnings:
    The mydFreeSerdesDev must be called when the driver unloads or exits. The
    mydFreeSerdesDev will release the serdes device structure memory.
*******************************************************************************/
MYD_STATUS mydFreeSerdesDev
(
    IN MYD_DEV_PTR pDev
);

/******************************************************************************
MYD_STATUS mydGetSerdesAddress
(
 IN MYD_DEV_PTR pDev,
 IN MYD_U16 mdioPort,     
 IN MYD_U16 host_or_line,
 IN MYD_U16 laneOffset,
 OUT MYD_U16 *sAddr
);


 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being checked:
                MYD_HOST_SIDE
                MYD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3.


 Outputs:
    sAddr - this is the SerDes sAddr passed into the SerDes functions
    
 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    This function gets the SerDes address associated with the given
    port, host/line side and lane.
      
 Side effects:
    None

 Notes/Warnings:
    None
*******************************************************************************/
MYD_STATUS mydGetSerdesAddress
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,     
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *sAddr
);

#define MYD_FIXED_CTLE_DISABLED 1
#define MYD_FIXED_CTLE_ENABLED  2
/******************************************************************************
MYD_STATUS mydSerdesTuneCTLE
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 sAddr,
    IN MYD_U16 dc,
    IN MYD_U16 lf,
    IN MYD_U16 hf,
    IN MYD_U16 bw,
    IN MYD_U16 optionCTLE 
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    sAddr - SerDes lane addr. Range[1-(8*portCount)]; 
            Refer to MYD_MAPPED_SERDES_ID or mydGetSerdesAddress for sAddr mapping          
    dc -  DC-Restore value [0-255] 
    lf -  CTLE Low-Frequency setting [0-15] 
    hf -  CTLE High-Frequency setting [0-15] 
    bw -  CTLE Band-width setting [0-15] 
    optionCTLE - MYD_FIXED_CTLE_DISABLED: fixed tuning for that value will be disabled
                 MYD_FIXED_CTLE_ENABLED: fixed tuning using value[n] will be enabled.

 Outputs:
    None
    
 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    This function provides the option to set the fixed CTLE values of DFE tuning 
    on a SerDes lane.

    Specify tuning options.
       The order of fixed and value array elements is DC, LF, HF and BW.
       If fixed[n] is 0, then fixed tuning for that value will be disabled.
       If fixed[n] is 1, then fixed tuning using value[n] will be enabled.
       All fixed setting changes are applied before tuning begins.
    
 Side effects:
    None

 Notes/Warnings:
    After calling this function to tune the CTLE parameters, give it a few seconds
    before calling mydSerdesGetRxDFE() to read back the updated values.

    The mydFreeSerdesDev must be called when the driver unloads or exits. The
    mydFreeSerdesDev will release the serdes device structure memory.

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
);

/* different control options for DFE tuning execution */
typedef enum
{
    MYD_DFE_START_ADAPTIVE = 3, /* Launch continuous pCAL */
    MYD_DFE_STOP_ADAPTIVE  = 4  /* Stop continuous pCAL */
} MYD_DFE_TUNE_MODE;

/******************************************************************************
MYD_STATUS mydSerdesTune_pCal
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,
   IN MYD_DFE_TUNE_MODE tuneMode
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    sAddr - SerDes lane addr. Range[1-(8*portCount)]; 
            Refer to MYD_MAPPED_SERDES_ID or mydGetSerdesAddress for sAddr mapping          
    tuneMode - Type of DFE tuning to execute; see MYD_DFE_TUNE_MODE types

 Outputs:
    None
    
 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    This function provides the options to either start/restart the progression calibration
    or stop the progression calibration for the DFE tuning on a SerDes lane.

    MYD_DFE_START_ADAPTIVE - Launch continuous pCAL 
    MYD_DFE_STOP_ADAPTIVE  - Stop continuous pCAL 

 Side effects:
    None

 Notes/Warnings:
    After calling this function to control the tuning, some option requires up to 
    6 seconds before the SerDes lane is ready for operation.  The mydSerdesGetRxDFEStatus()
    can be called to check the status for completion

    The mydFreeSerdesDev must be called when the driver unloads or exits. The
    mydFreeSerdesDev will release the serdes device structure memory.
*******************************************************************************/
MYD_STATUS mydSerdesTune_pCal
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,
   IN MYD_DFE_TUNE_MODE tuneMode
);


/******************************************************************************
MYD_STATUS mydSerdesGetEye
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,
   IN MYD_U16 sampleSize,
   IN MYD_U16 highDefinition,
   IN MYD_U16 serdesLogLevel, 
   OUT MYD_SER_EYE_DATA_TYPE *pEyeData
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    sAddr - SerDes lane addr. Range[1-(8*portCount)]; 
            Refer to MYD_MAPPED_SERDES_ID or mydGetSerdesAddress for sAddr mapping          
    sampleSize - The eye sample size based on the max dwell bit.
                       Range [4 to 8] where x is the exponential 
                       e.g. 4 = 10,000; 8 = 100,000,000 
    highDefinition - MYD_DISABLE: disable high resolution; 
                     MYD_ENABLE: enable high definition
                     The high definition option increases the y resolution to 1 step
    serdesLogLevel - The level of logging in the serdes APIs
                     Range [0 - 15]. Set to 0 when not debugging. 
    
 Outputs:
   pEyeData   - The output results for the SerDes eye, vertical and horizontal bathtub.
                Refer to the MYD_SER_EYE_DATA_TYPE data structure. The caller to this
                API must call mydWrapperEyeAllocDataSt() to allocate the pEyeData buffer 
                memory before passing in the pointer. The caller must free the pEyeData
                by calling mydWrapperEyeFreeDataSt() after processing the eye data.
    
 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    The function gathers the eye diagram measurements including the vertical 
    and horizontal bathtub measurements from an individual SerDes lane.     
    The output in the eyeDataBuf returns all the useful eye measurements.
    
    The pEyeData in this function holds the raw data values. Refer to the 
    MYD_SER_EYE_CONFIG_TYPE, MYD_SER_EYE_DATA_TYPE for descriptions of 
    configuration and return data values.

    Refer to the mydSampleGetEye sample on the usage. 
          
 Side effects:
    None

 Notes/Warnings:
    The caller to this API must call mydWrapperEyeAllocDataSt() to allocate the 
    pEyeData buffer memory before passing in the pointer. The caller must free the
    pEyeData by calling mydWrapperEyeFreeDataSt() after processing the eye data.

    If pCal is running before plotting the eye, the pCal must be disabled before 
    plotting the eye.  After completion, the pCal DFE tuning needs to be re-enabled 
    after eye measurement.

    This function takes several seconds to complete. In the event of a slower 
    read access or selecting the high definition measurements, it may take up 
    to a minute. 
    
    The memory usage significantly increases when the serdesLogLevel is set 
    to > 0. If debugging/logging is not required, serdesLogLevel should be 0.
    
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MYD_STATUS mydSerdesGetEye
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,
   IN MYD_U16 sampleSize,
   IN MYD_U16 highDefinition,
   IN MYD_U16 serdesLogLevel, 
   OUT MYD_SER_EYE_DATA_TYPE *pEyeData
);


/******************************************************************************
MYD_STATUS mydSerdesGetTxFFE
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   OUT MYD_16 *preCursor,
   OUT MYD_16 *pre2Cursor,
   OUT MYD_16 *pre3Cursor,
   OUT MYD_16 *attenuation,
   OUT MYD_16 *postCursor
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    sAddr - SerDes lane addr. Range[1-(8*portCount)]; 
            Refer to MYD_MAPPED_SERDES_ID or mydGetSerdesAddress for sAddr mapping          

 Outputs:
    preCursor   - Pre-cursor setting 
    pre2Cursor  - Pre2-cursor setting 
    pre3Cursor  - Pre3-cursor setting 
    attenuation - Attenuator setting 
    postCursor  - Post-cursor setting

 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    This function returns the TX equalization values of an individual 
    SerDes lane. Refer to the mydSerdesSetTxFFE API for the setting ranges.
      
 Side effects:
    None

 Notes/Warnings:
    For the preCursor, pre2Cursor and postCursor, it will return even values.

    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
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
);

/******************************************************************************
MYD_STATUS mydSerdesSetTxFFE
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   IN MYD_16 preCursor,
   IN MYD_16 pre2Cursor,
   IN MYD_16 pre3Cursor,
   IN MYD_16 attenuation,
   IN MYD_16 postCursor
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    sAddr - SerDes lane addr. Range[1-(8*portCount)]; 
            Refer to MYD_MAPPED_SERDES_ID or mydGetSerdesAddress for sAddr mapping          

    The recommended Tx FFE ranges are as follows; however these ranges may 
    not apply to all modes and signal types. 
    preCursor   - Pre-cursor setting range [0 to 15] 
    pre2Cursor   - Pre2-cursor setting range [0 to 15] 
    pre3Cursor   - Pre3-cursor setting range [-1 to 1] 
    attenuation - Attenuator setting range [0 to 23]
    postCursor  - Post-cursor setting [0 to 15]

    The SerDes can support the Tx FFE ranges below but may not apply to most
    environment. These extended ranges may be used for testing and validation.
    preCursor   - Pre-cursor setting range [-7 to 15]
    pre2Cursor   - Pre2-cursor setting range [-7 to 15]
    pre3Cursor   - Pre3-cursor setting range [-1 to 1]
    attenuation - Attenuator setting range [0 to 31]
    postCursor  - Post-cursor setting [-31 to 31]

 Outputs:
    None
    
 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    This function sets the TX equalization preCursor, pre2Cursor, pre3Cursor, 
    attenuation and postCursor values on an individual SerDes lane.  
      
 Side effects:
    None

 Notes/Warnings:
    For the preCursor, pre2Cursor and postCursor, use only even values.

    Note that the software reset will reset the Tx FFE back to the default 
    values. 

    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
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
);

/******************************************************************************
MYD_STATUS mydSerdesGetStateDump
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    sAddr - SerDes lane addr. Range[1-(8*portCount)]; 
            Refer to MYD_MAPPED_SERDES_ID or mydGetSerdesAddress for sAddr mapping          

Outputs:
    none

 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    This function provides a log of a SerDes lane state dump. The dump includes 
    the DFE and CTLE data.
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MYD_STATUS mydSerdesGetStateDump
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr
);

/******************************************************************************
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
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    sAddr - SerDes lane addr. Range[1-(8*portCount)]; 
            Refer to MYD_MAPPED_SERDES_ID or mydGetSerdesAddress for sAddr mapping          

 Outputs:
    dfeStatusICalInProgress - Initial calibration in progress
    dfeStatusPCalInProgress - Periodic calibration in progress
    dfeStatusVosInProgress  - VOS in progress
    dfeStatusRunICal        - Initial calibration in operation
    dfeStatusRunPCal        - Periodic calibration in operation
    dfeStatusDetectEI       - Loss of signal detected

 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    This function returns the DFE in-progress and operational states of an 
    individual SerDes lane.
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
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
);

/******************************************************************************
MYD_STATUS mydSerdesGetRxDFE
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 sAddr,  
    OUT MYD_U16 *dc,        
    OUT MYD_U16 *lf,        
    OUT MYD_U16 *hf,        
    OUT MYD_U16 *bw,        
    OUT MYD_U16 *gainShape1, 
    OUT MYD_U16 *gainShape2, 
    OUT MYD_U16 *dfeGAIN,   
    OUT MYD_U16 *dfeGAIN2   
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    sAddr - SerDes lane addr. Range[1-(8*portCount)]; 
            Refer to MYD_MAPPED_SERDES_ID or mydGetSerdesAddress for sAddr mapping          

Outputs:
     dc -  DC-Restore value [0-255] 
     lf -  CTLE Low-Frequency setting [0-15] 
     hf -  CTLE High-Frequency setting [0-15] 
     bw -  CTLE Band-width setting [0-15] 
     gainShape1 - CTLE gainShape1 setting
     gainShape2 - CTLE gainShape2 setting 
     dfeGAIN - DFE Gain Tap strength setting [0-15] 
     dfeGAIN2DFE - Gain Tap 2 strength setting [0-15] 

 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    This function call returns the Rx DFE values of an individual 
    SerDes lane. 
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MYD_STATUS mydSerdesGetRxDFE
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 sAddr,  
    OUT MYD_U16 *dc,        
    OUT MYD_U16 *lf,        
    OUT MYD_U16 *hf,        
    OUT MYD_U16 *bw,        
    OUT MYD_U16 *gainShape1, 
    OUT MYD_U16 *gainShape2, 
    OUT MYD_U16 *dfeGAIN,   
    OUT MYD_U16 *dfeGAIN2   
);


/******************************************************************************
MYD_STATUS mydSerdesGetTxPolarity
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   OUT MYD_U16 *polarity
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    sAddr - SerDes lane addr. Range[1-(8*portCount)]; 
            Refer to MYD_MAPPED_SERDES_ID or mydGetSerdesAddress for sAddr mapping          

 Outputs:
    polarity - returns 1 if inverter is enabled, 0 if data is not being inverted.
    
 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    This function returns the TX inverter polarity for an individual SerDes lane.  
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MYD_STATUS mydSerdesGetTxPolarity
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   OUT MYD_U16 *polarity
);


/******************************************************************************
MYD_STATUS mydSerdesSetTxPolarity
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   IN MYD_U16 polarity
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    sAddr - SerDes lane addr. Range[1-(8*portCount)]; 
            Refer to MYD_MAPPED_SERDES_ID or mydGetSerdesAddress for sAddr mapping          
    polarity - 1 to invert TX polarity, 0 to use normal polarity.

 Outputs:
    None
    
 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    This function sets the TX inverter polarity with the given value for an 
    individual SerDes lane.  
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MYD_STATUS mydSerdesSetTxPolarity
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   IN MYD_U16 polarity
);


/******************************************************************************
MYD_STATUS mydSerdesGetRxPolarity
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   OUT MYD_U16 *polarity
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    sAddr - SerDes lane addr. Range[1-(8*portCount)]; 
            Refer to MYD_MAPPED_SERDES_ID or mydGetSerdesAddress for sAddr mapping          

 Outputs:
    polarity - returns 1 if inverter is enabled, 0 if data is not being inverted.
    
 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    This function returns the RX inverter polarity for an individual SerDes lane.  
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MYD_STATUS mydSerdesGetRxPolarity
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   OUT MYD_U16 *polarity
);


/******************************************************************************
MYD_STATUS mydSerdesSetRxPolarity
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   IN MYD_U16 polarity
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    sAddr - SerDes lane addr. Range[1-(8*portCount)]; 
            Refer to MYD_MAPPED_SERDES_ID or mydGetSerdesAddress for sAddr mapping          
    polarity - 1 to invert RX polarity, 0 to use normal polarity

 Outputs:
    None
    
 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    This function sets the RX inverter polarity with the given value for 
    an individual SerDes lane.  
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MYD_STATUS mydSerdesSetRxPolarity
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   IN MYD_U16 polarity
);


/******************************************************************************
MYD_STATUS mydSerdesTxInjectError
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   IN MYD_U16 numErrors
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    sAddr - SerDes lane addr. Range[1-(8*portCount)]; 
            Refer to MYD_MAPPED_SERDES_ID or mydGetSerdesAddress for sAddr mapping          
    numErrors - number of bit errors to inject

 Outputs:
    None
    
 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    This function injects a number of bit errors into the transmit path.  
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MYD_STATUS mydSerdesTxInjectError
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   IN MYD_U16 numErrors
);


/******************************************************************************
MYD_STATUS mydSerdesRxInjectError
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   IN MYD_U16 numErrors
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    sAddr - SerDes lane addr. Range[1-(8*portCount)]; 
            Refer to MYD_MAPPED_SERDES_ID or mydGetSerdesAddress for sAddr mapping          
    numErrors - number of bit errors to inject

 Outputs:
    None
    
 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    This function injects a number of bit errors into the receive path.  
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MYD_STATUS mydSerdesRxInjectError
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   IN MYD_U16 numErrors
);


/******************************************************************************
MYD_STATUS mydSerdesGetCDRLock
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   OUT MYD_U16 *CDRLockState
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    sAddr - SerDes lane addr. Range[1-(8*portCount)]; 
            Refer to MYD_MAPPED_SERDES_ID or mydGetSerdesAddress for sAddr mapping          

 Outputs:
    CDRLockState - returns 1 if locked; 0 if not locked; 
    
 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    This function retrieves the Clock Data Recovery(CDR) lock state for an 
    individual SerDes lane.  
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MYD_STATUS mydSerdesGetCDRLock
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   OUT MYD_U16 *CDRLockState
);


/******************************************************************************
MYD_STATUS mydSerdesPMDTrainingLog
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,  
   OUT PMYD_TRAINING_INFO pTrainInfo
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    sAddr - SerDes lane addr. Range[1-(8*portCount)]; 
            Refer to MYD_MAPPED_SERDES_ID or mydGetSerdesAddress for sAddr mapping          

 Outputs:
    pTrainInfo - Training log data is stored in the output structure. Refer to
                 the MYD_TRAINING_INFO and MYD_TRAINING_STATS structures for more
                 info on the values.

                 This is a pointer to an MYD_TRAINING_INFO structure.
    
 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    This function retrieves the link training log for an individual SerDes lane. 
    The output results are stored in the pTrainInfo. The caller must pass in 
    a pre-allocated memory MYD_TRAINING_INFO structure for the pTrainInfo 
    to store the training log results. 
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MYD_STATUS mydSerdesPMDTrainingLog
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr,
   OUT PMYD_TRAINING_INFO pTrainInfo /* this is a pointer to an MYD_TRAINING_INFO */
);


/******************************************************************************
MYD_STATUS mydSerdesReset
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr
);                         

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    sAddr - SerDes lane addr. Range[1-(8*portCount)]; 
            Refer to MYD_MAPPED_SERDES_ID or mydGetSerdesAddress for sAddr mapping          

 Outputs:
    none

 Returns:
    MYD_OK if successful, MYD_FAIL otherwise

 Description:
    This function resets a SerDes lane on a given SerDes lane ID.
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MYD_STATUS mydSerdesReset
(
   IN MYD_DEV_PTR pDev,
   IN MYD_U16 sAddr
);                         


#endif /* MYD_ENABLE_SERDES_API */


#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MYD_HWSERDESCNT_H */

