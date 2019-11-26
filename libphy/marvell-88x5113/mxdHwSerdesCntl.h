/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains function prototypes to call Serdes API functions, 
Serdes features and diagnostic operations.  The Serdes API component 
is included by default with define MXD_ENABLE_SERDES_API.
********************************************************************/
#ifndef MXD_HWSERDESCNT_H
#define MXD_HWSERDESCNT_H

#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

/* SBus address for each component */
#define MXD_SBUS_SBUS_MASTER  0xFD
#define MXD_SBUS_SBUS_SERDES  0xFF

/* SBus indirect access register */
#define MXD_SBUS_RX_DATA_VALID  0xF440
#define MXD_SBUS_COMMAND_REG    0xF441
#define MXD_SBUS_ADDR_REG       0xF442
#define MXD_SBUS_EXECUTION      0xF443
#define MXD_SBUS_INPUT_DATA_L   0xF444
#define MXD_SBUS_INPUT_DATA_H   0xF445
#define MXD_SBUS_RESULT_CODE    0xF446
#define MXD_SBUS_OUTPUT_DATA_L  0xF448
#define MXD_SBUS_OUTPUT_DATA_H  0xF449

/* SBus result return code MXD_SBUS_RESULT_CODE */
#define MXD_SBUS_RESET             0x0
#define MXD_SBUS_WRITE_COMPLETE    0x1
#define MXD_SBUS_WRITE_FAILED      0x2
#define MXD_SBUS_READ_ALL_COMPLETE 0x3
#define MXD_SBUS_READ_COMPLETE     0x4
#define MXD_SBUS_READ_FAILED       0x5
#define MXD_SBUS_CMD_ISSUE_DONE    0x6
#define MXD_SBUS_MODE_CHANGE_DONE  0x7

/* SBus Read/Write command */
#define MXD_SBUS_ADDR   0x20
#define MXD_SBUS_WRITE  0x21
#define MXD_SBUS_READ   0x22

/* SBus master register map */
#define MXD_SBUS_MASTER_INTR_CMD     0x02
#define MXD_SBUS_MASTER_INTR_STATUS  0x07
#define MXD_SBUS_MASTER_INTR_RESULT  0x08

/* Sbus SerDes Register */
#define MXD_SBUS_SERDES_INTR_CMD     0x03
#define MXD_SBUS_SERDES_INTR_RESULT  0x04

/* Sbus SerDes Diagnostic Register */
#define MXD_SBUS_TEMPERATURE_SENSOR  0x09
#define MXD_SBUS_TEMPERATURE_DATA    0x17
#define MXD_SBUS_VOLTAGE_DATA        0x18

/* 
   There are 8 SerDes lane in the X5113 device. Below is the mapping
   of the Host/Line lane offset to the SerDes labe IDs. SerDes lane 
   starts from 1 to 8. 
   
   Host Lane 
        Offset 0: SerDesID 1 
        Offset 1: SerDesID 2 
        Offset 2: SerDesID 3 
        Offset 3: SerDesID 4 

   Line Lane
        Offset 0: SerDesID 5 
        Offset 1: SerDesID 6 
        Offset 2: SerDesID 7 
        Offset 3: SerDesID 8 
*/

#define MXD_SERDES_LANE_COUNT 8 /* X5113 supports up to 8 Serdes lanes */

#if MXD_ENABLE_SERDES_API
#include "mxdSerdes.h"
#endif 

/******************************************************************************
MXD_STATUS mxdExecuteIndirectSBusCmd
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31 

 Outputs:
    None

 Returns:
    MXD_OK if command was executed successful, MXD_FAIL otherwise

 Description:
    The function issues an execute command after an indirect SBUS read or write 
    command is issued. 
    
 Side effects:
    None

 Notes/Warnings:
    None

******************************************************************************/
MXD_STATUS mxdExecuteIndirectSBusCmd
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort
);


/******************************************************************************
MXD_STATUS mxdIndirectSBusWrite
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 sBusReceiverAddr, 
    IN MXD_U16 regAddr, 
    IN MXD_U16 dataH, 
    IN MXD_U16 dataL, 
    OUT MXD_U16 *resultCode
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31 
    sBusReceiverAddr - SBUS address 
    regAddr - register address 
    dataH - 16-bit High word to be written
    dataL - 16-bit Low word to be written 

 Outputs:
    resultCode - returns 1 if write is successful. Otherwise 0. 

 Returns:
    MXD_OK if write was successful, MXD_FAIL otherwise

 Description:
    The function performs an indirect write on both the High and Low 16-bit words to the SBUS. 
    There are 3 parts to this operation. The SBUS write command, the High and Low 16-bit words
    and lastly issue the mxdExecuteIndirectSBusCmd to execute the write. 
      
 Side effects:
    None

 Notes/Warnings:
    None
******************************************************************************/
MXD_STATUS mxdIndirectSBusWrite
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 sBusReceiverAddr, 
    IN MXD_U16 regAddr, 
    IN MXD_U16 dataH, 
    IN MXD_U16 dataL, 
    OUT MXD_U16 *resultCode
);


/******************************************************************************
MXD_STATUS mxdIndirectSBusRead
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 sBusReceiverAddr, 
    IN MXD_U16 regAddr, 
    OUT MXD_U16 *dataH, 
    OUT MXD_U16 *dataL, 
    OUT MXD_U16 *resultCode
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31 
    sBusReceiverAddr - SBUS address 
    regAddr - register address 

 Outputs:
    dataH - returns 16-bit High word of the requested address
    dataL - returns 16-bit Low word of the requested address 
    resultCode - returns 1 if write is successful. Otherwise 0. 

 Returns:
    MXD_OK if read was successful, MXD_FAIL otherwise

 Description:
    The function performs an indirect read on both the High and Low 16-bit words to the SBUS. 
    There are 3 parts to this operation. The SBUS read command, the High and Low 16-bit words
    and lastly issue the mxdExecuteIndirectSBusCmd to execute the read. 
      
 Side effects:
    None

 Notes/Warnings:
    None
******************************************************************************/
MXD_STATUS mxdIndirectSBusRead
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 sBusReceiverAddr, 
    IN MXD_U16 regAddr, 
    OUT MXD_U16 *dataH, 
    OUT MXD_U16 *dataL, 
    OUT MXD_U16 *resultCode
);


/******************************************************************************
MXD_STATUS mxdSerdesInterrupt
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 sBusReceiverAddr, 
    IN MXD_U16 interruptCode, 
    IN MXD_U16 interruptData, 
    OUT MXD_U16 interruptResult
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31 
    sBusReceiverAddr - SBUS address 
    interruptCode - SerDes interrupt code to issue
    interruptData - SerDes interrupt data to issue

 Outputs:
    interruptResult - returns the result of the issued interrupt code and data 

 Returns:
    MXD_OK if interrupt issued was successful, MXD_FAIL otherwise

 Description:
    The function issue an interrupt code and data. It retries up to 100 time for
    the interrupt completion.   
      
 Side effects:
    None

 Notes/Warnings:
    None
******************************************************************************/
MXD_STATUS mxdSerdesInterrupt
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 sBusReceiverAddr, 
    IN MXD_U16 interruptCode, 
    IN MXD_U16 interruptData, 
    OUT MXD_U16 *interruptResult
);


/******************************************************************************
MXD_STATUS mxdSbusInterrupt
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 interruptCode, 
    IN MXD_U16 interruptInput, 
    OUT MXD_U16 *interruptResult, 
    OUT MXD_U16 *interruptStatus
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31 
    sBusReceiverAddr - SBUS address 
    interruptCode - SBUS interrupt code to issue
    interruptInput - SBUS interrupt input data to issue

 Outputs:
    interruptResult - returns the result of the issued interrupt code and data 
    interruptStatus - returns the status of the issued interrupt
    
 Returns:
    MXD_OK if interrupt issued was successful, MXD_FAIL otherwise

 Description:
    The function issue an interrupt code and data. It retries up to 500 time for
    the interrupt completion.   
      
 Side effects:
    None

 Notes/Warnings:
    None
******************************************************************************/
MXD_STATUS mxdSbusInterrupt
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 interruptCode, 
    IN MXD_U16 interruptInput, 
    OUT MXD_U16 *interruptResult, 
    OUT MXD_U16 *interruptStatus
);

/******************************************************************************
MXD_STATUS mxdSerdesIntWrite
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 regAddr, 
    IN MXD_U16 dataH, 
    IN MXD_U16 dataL
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31 
    regAddr - Serdes lane and interrupt address 
    dataH - 16-bit High word to be written
    dataL - 16-bit Low word to be written 

 Outputs:
    None 

 Returns:
    MXD_OK if write was successful, MXD_FAIL otherwise

 Description:
    The function performs an indirect write to the Serdes interrupt address using
    the Serdes communication protocol.  

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesIntWrite
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 regAddr, 
    IN MXD_U16 dataH, 
    IN MXD_U16 dataL
);

#if MXD_ENABLE_SERDES_API

/******************************************************************************
 MXD_STATUS mxdInitSerdesDev
(
    IN MXD_DEV_PTR pDev
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call

 Outputs:
    None
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This SerDes initialization function is called during mxdInitDriver() when the
    MXD_ENABLE_SERDES_API is set to 1. This function allocates the device structure
    memory requires when the Serdes API is called. In addition, it will initialize
    the MDIO read/write function pointer for the serdes API operation.
      
 Side effects:
    None

 Notes/Warnings:
    The mxdFreeSerdesDev must be called when the driver unloads or exits. The
    mxdFreeSerdesDev will release the serdes device structure memory.
*******************************************************************************/
MXD_STATUS mxdInitSerdesDev
(
    IN MXD_DEV_PTR pDev
);


/******************************************************************************
MXD_STATUS mxdFreeSerdesDev
(
    IN MXD_DEV_PTR pDev
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call

 Outputs:
    None
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function releases the Serdes API device structure memory.  
      
 Side effects:
    None

 Notes/Warnings:
    The mxdFreeSerdesDev must be called when the driver unloads or exits. The
    mxdFreeSerdesDev will release the serdes device structure memory.
*******************************************************************************/
MXD_STATUS mxdFreeSerdesDev
(
    IN MXD_DEV_PTR pDev
);

/******************************************************************************
MXD_STATUS mxdSerdesTune_iCal
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_U16 iCalVal_1,
   IN MXD_U16 iCalVal_2,
   IN MXD_U16 iCalVal_3,
   IN MXD_U16 iCalVal_4,
   IN MXD_U16 useDefault
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          
    iCalVal_1 - input 1st iCal value 
    iCalVal_2 - input 2nd iCal value 
    iCalVal_3 - input 3rd iCal value 
    iCalVal_4 - input 4th iCal value 
    useDefault - non-zero to use the default values; all above 4 iCal values will be ignored
                 0 to use all above provided 4 iCal values    

 Outputs:
    None
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function initializes the DFE iCal structure and tunes the SerDes with the provided 
    iCal tuning values. The default optimized values are used if the useDefault parameter 
    is set to non-zero.

    Following default iCal values will be used if useDefault = 1:
        iCalVal_1 = 56;
        iCalVal_2 = 12;
        iCalVal_3 =  0;
        iCalVal_4 = 15;

 Side effects:
    None

 Notes/Warnings:
    After calling this function to tune the iCal values, it requires to wait at least 
    6 seconds before the SerDes lane is ready for operation.

    The mxdFreeSerdesDev must be called when the driver unloads or exits. The
    mxdFreeSerdesDev will release the serdes device structure memory.
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
);

/* different control options for DFE tuning execution */
typedef enum
{
    MXD_DFE_START_ADAPTIVE = 3, /* Launch continuous pCAL */
    MXD_DFE_STOP_ADAPTIVE  = 4  /* Stop continuous pCAL */
} MXD_DFE_TUNE_MODE;

/******************************************************************************
MXD_STATUS mxdSerdesTune_pCal
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_DFE_TUNE_MODE tuneMode
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          
    tuneMode - Type of DFE tuning to execute; see MXD_DFE_TUNE_MODE types

 Outputs:
    None
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function provides the option below to control the type of DFE tuning on a
    SerDes lane.

    MXD_DFE_START_ADAPTIVE - Launch continous pCAL 
    MXD_DFE_STOP_ADAPTIVE  - Stop continous pCAL 

 Side effects:
    None

 Notes/Warnings:
    After calling this function to control the tuning, some option requires up to 
    6 seconds before the SerDes lane is ready for operation.  The mxdSerdesGetRxDFEStatus()
    can be called to check the status for completion

    The mxdFreeSerdesDev must be called when the driver unloads or exits. The
    mxdFreeSerdesDev will release the serdes device structure memory.
*******************************************************************************/
MXD_STATUS mxdSerdesTune_pCal
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_DFE_TUNE_MODE tuneMode
);

/******************************************************************************
MXD_STATUS mxdSerdesInitBitRate
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_U16 divider
   IN MXD_BOOL intLoopbackMode
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          
    divider- input divider to configure the SerDes lane bit rate
    intLoopbackMode - option for internal loopback on a same Rx/Tx lane; set to 
                      MXD_DISABLE if Rx and Tx are different or an
                      external loopback device is used on the same Rx/Tx lane

 Outputs:
    None
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function initializes and configures a SerDes lane bit rate with the 
    provided divider ratio. The reference clock is at 156.25Mhz. The divider 
    is the ratio for the SerDes lane bit rate to the reference clock. 
    Following example on setting the SerDes bit rate:
    10G: divider = 66
    25G: divider = 165
      
 Side effects:
    None

 Notes/Warnings:
    The mxdFreeSerdesDev must be called when the driver unloads or exits. The
    mxdFreeSerdesDev will release the serdes device structure memory.

*******************************************************************************/
MXD_STATUS mxdSerdesInitBitRate
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_U16 divider,
   IN MXD_BOOL intLoopbackMode
);


/******************************************************************************
 MXD_STATUS mxdSerdesGetEye
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_U16 sampleSize,
   IN MXD_U16 highDefinition,
   IN MXD_U16 serdesLogLevel, 
   OUT MXD_SER_EYE_DATA_TYPE *pEyeData
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          
    sampleSize - The eye sample size based on the max dwell bit.
                       Range [4 to 8] where x is the exponential 
                       e.g. 4 = 10,000; 8 = 100,000,000 
    highDefinition - MXD_DISABLE: disable high resolution; 
                     MXD_ENABLE: enable high definition
                     The high definition option increases the y resolution to 1 step
    serdesLogLevel - The level of logging in the serdes APIs
                     Range [0 - 15]. Set to 0 when not debugging. 
    
 Outputs:
   pEyeData   - The output results for the SerDes eye, vertical and horizontal bathtub.
                Refer to the MXD_SER_EYE_DATA_TYPE data structure. The caller to this
                API must call mxdWrapperEyeAllocDataSt() to allocate the pEyeData buffer 
                memory before passing in the pointer. The caller must free the pEyeData
                by calling mxdWrapperEyeFreeDataSt() after processing the eye data.
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    The function gathers the eye diagram measurements including the vertical 
    and horizontal bathtub measurements from an individual SerDes lane.     
    The output in the eyeDataBuf returns all the useful eye measurements.
    
    The pEyeData in this function holds the raw data values. Refer to the 
    MXD_SER_EYE_CONFIG_TYPE, MXD_SER_EYE_DATA_TYPE for descriptions of 
    configuration and return data values.

    Refer to the mxdSampleGetEye sample on the usage. 
          
 Side effects:
    None

 Notes/Warnings:
    The caller to this API must call mxdWrapperEyeAllocDataSt() to allocate the 
    pEyeData buffer memory before passing in the pointer. The caller must free the
    pEyeData by calling mxdWrapperEyeFreeDataSt() after processing the eye data.

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
MXD_STATUS mxdSerdesGetEye
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_U16 sampleSize,
   IN MXD_U16 highDefinition,
   IN MXD_U16 serdesLogLevel, 
   OUT MXD_SER_EYE_DATA_TYPE *pEyeData
);


/******************************************************************************
MXD_STATUS mxdSerdesGetRevision
(
   IN MXD_DEV_PTR pDev,
   OUT MXD_U16 *serdesRevision,
   OUT MXD_U16 *sbmRevision
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call

 Outputs:
    serdesRevision - SerDes revision
    sbmRevision - SBus master revision  
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This call returns the SerDes and SBus master revisions   
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesGetRevision
(
   IN MXD_DEV_PTR pDev,
   OUT MXD_U16 *serdesRevision,
   OUT MXD_U16 *sbmRevision
);


/******************************************************************************
MXD_STATUS mxdSerdesGetVoltage
(
   IN MXD_DEV_PTR pDev,
   OUT MXD_U16 *coreVoltage,
   OUT MXD_U16 *DVDDVoltage,
   OUT MXD_U16 *AVDDVoltage
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call

 Outputs:
    coreVoltage - Core voltage value
    DVDDVoltage - DVDD voltage value
    AVDDVoltage - AVDD voltage value
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    The call returns the output voltages of the core, DVDD and AVDD. 
    The values return in the outputs are in millivolt(mV).
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesGetVoltage
(
   IN MXD_DEV_PTR pDev,
   OUT MXD_U16 *coreVoltage,
   OUT MXD_U16 *DVDDVoltage,
   OUT MXD_U16 *AVDDVoltage
);


/******************************************************************************
MXD_STATUS mxdSerdesGetTemperature
(
   IN MXD_DEV_PTR pDev,
   OUT MXD_32 *coreTemperature,
   OUT MXD_32 *serdesTemperature
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call

 Outputs:
    coreTemperature - Core temperature value
    serdesTemperature - SerDes temperature value
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    The call returns the temperatures of the Core and SerDes. 
    The values return in the outputs are in milli-Celsius(mC).
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesGetTemperature
(
   IN MXD_DEV_PTR pDev,
   OUT MXD_32 *coreTemperature,
   OUT MXD_32 *serdesTemperature
);


/******************************************************************************
MXD_STATUS mxdSerdesGetTxFFE
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   OUT MXD_16 *preCursor,
   OUT MXD_16 *attenuation,
   OUT MXD_16 *postCursor,
   OUT MXD_16 *slew
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          

 Outputs:
    preCursor   - Pre-cursor setting 
    attenuation - Attenuator setting 
    postCursor  - Post-cursor setting
    slew - Slew rate setting [0..3], 0 is fastest

 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function call returns the TX equalization values of an individual 
    SerDes lane. Refers to the mxdSerdesSetTxFFE API for the setting ranges.
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesGetTxFFE
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   OUT MXD_16 *preCursor,
   OUT MXD_16 *attenuation,
   OUT MXD_16 *postCursor,
   OUT MXD_16 *slew
);


/******************************************************************************
MXD_STATUS mxdSerdesSetTxFFE
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   IN MXD_16 preCursor,
   IN MXD_16 attenuation,
   IN MXD_16 postCursor,
   IN MXD_16 slew
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset     

    The recommended Tx FFE ranges are as follows: 
    preCursor   - Pre-cursor setting range [0 to 15] 
    attenuation - Attenuator setting range [0 to 23]
    postCursor  - Post-cursor setting [0 to 15]

    The SerDes can support the Tx FFE ranges below but may not apply to most
    environment. These extended ranges may be used for testing and validation.
    preCursor   - Pre-cursor setting range [-7 to 15]
    attenuation - Attenuator setting range [0 to 31]
    postCursor  - Post-cursor setting [-31 to 31]

    slew - Slew rate setting [0..3], 0 is fastest

 Outputs:
    None
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function sets the TX equalization preCursor, attenuation,
    postCursor and slew values on an individual SerDes lane.  
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesSetTxFFE
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   IN MXD_16 preCursor,
   IN MXD_16 attenuation,
   IN MXD_16 postCursor,
   IN MXD_16 slew
);


/******************************************************************************
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
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          

 Outputs:
    dfeStatusICalInProgress - Initial calibration in progress
    dfeStatusPCalInProgress - Periodic calibration in progress
    dfeStatusVosInProgress  - VOS in progress
    dfeStatusRunICal        - Initial calibration in operation
    dfeStatusRunPCal        - Periodic calibration in operation
    dfeStatusDetectEI       - Loss of signal detected

 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function returns the DFE in-progress and operational states of an 
    individual SerDes lane.
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
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
);


/******************************************************************************
MXD_STATUS mxdSerdesGetRxDFE
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   OUT MXD_U16 *dc,        
   OUT MXD_U16 *lf,        
   OUT MXD_U16 *hf,        
   OUT MXD_U16 *bw,        
   OUT MXD_U16 *dfeGAIN,   
   OUT MXD_U16 *dfeGAIN2   
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          

Outputs:
     dc -  DC-Restore value [0-255] 
     lf -  CTLE Low-Frequency setting [0-15] 
     hf -  CTLE High-Frequency setting [0-15] 
     bw -  CTLE Band-width setting [0-15] 
     dfeGAIN - DFE Gain Tap strength setting [0-15] 
     dfeGAIN2DFE - Gain Tap 2 strength setting [0-15] 

 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function call returns the Rx DFE values of an individual 
    SerDes lane. 
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesGetRxDFE
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   OUT MXD_U16 *dc,        
   OUT MXD_U16 *lf,        
   OUT MXD_U16 *hf,        
   OUT MXD_U16 *bw,        
   OUT MXD_U16 *dfeGAIN,   
   OUT MXD_U16 *dfeGAIN2   
);


/******************************************************************************
MXD_STATUS mxdSerdesGetTxPolarity
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   OUT MXD_U16 *polarity
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          

 Outputs:
    polarity - returns 1 if inverter is enabled, 0 if data is not being inverted.
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function returns the TX inverter polarity for an individual SerDes lane.  
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesGetTxPolarity
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   OUT MXD_U16 *polarity
);


/******************************************************************************
MXD_STATUS mxdSerdesSetTxPolarity
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   IN MXD_U16 polarity
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          
    polarity - 1 to invert TX polarity, 0 to use normal polarity.

 Outputs:
    None
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function sets the TX inverter polarity with the given value for an 
    individual SerDes lane.  
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesSetTxPolarity
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   IN MXD_U16 polarity
);


/******************************************************************************
MXD_STATUS mxdSerdesGetRxPolarity
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   OUT MXD_U16 *polarity
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          

 Outputs:
    polarity - returns 1 if inverter is enabled, 0 if data is not being inverted.
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function returns the RX inverter polarity for an individual SerDes lane.  
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesGetRxPolarity
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   OUT MXD_U16 *polarity
);


/******************************************************************************
MXD_STATUS mxdSerdesSetRxPolarity
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   IN MXD_U16 polarity
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          
    polarity - 1 to invert RX polarity, 0 to use normal polarity

 Outputs:
    None
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function sets the RX inverter polarity with the given value for 
    an individual SerDes lane.  
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesSetRxPolarity
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   IN MXD_U16 polarity
);


/******************************************************************************
MXD_STATUS mxdSerdesGetCDRLock
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   OUT MXD_U16 *CDRLockState
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          

 Outputs:
    CDRLockState - returns 1 if locked; 0 if not locked; 
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function retrieves the Clock Data Recovery(CDR) lock state for an 
    individual SerDes lane.  
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesGetCDRLock
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   OUT MXD_U16 *CDRLockState
);


/******************************************************************************
MXD_STATUS mxdSerdesPMDTrainingLog
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   OUT PMXD_TRAINING_INFO pTrainInfo
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          

 Outputs:
    pTrainInfo - Training log data is stored in the output structure. Refer to
                 the MXD_TRAINING_INFO and MXD_TRAINING_STATS structures for more
                 info on the values.

                 This is a pointer to an MXD_TRAINING_INFO structure.
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function retrieves the link training log for an individual SerDes lane. 
    The output results are stored in the pTrainInfo. The caller must pass in 
    a pre-allocated memory MXD_TRAINING_INFO structure for the pTrainInfo 
    to store the training log results. 
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesPMDTrainingLog
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   OUT PMXD_TRAINING_INFO pTrainInfo /* this is a pointer to an MXD_TRAINING_INFO */
);


/******************************************************************************
MXD_STATUS mxdSerdesTxInjectError
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   IN MXD_U16 numErrBit
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          
    numErrBit - Number of error bits to inject (max=65535)

 Outputs:
    None  
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function injects errors into the TX data on an individual SerDes lane. 
    TX error injection affects the transmitted data stream. Therefore, errors 
    are only detected when comparing with a known pattern.

 Side effects:
    None

 Notes/Warnings:
    The mxdSerdesSetRxCmpMode() must be set to either MXD_SERDES_RX_CMP_MODE_TEST_PATGEN
    or MXD_SERDES_RX_CMP_MODE_MAIN_PATGEN mode when injecting Tx errors. Refer to 
    mxdSerdesSetRxCmpMode() for more information.

    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesTxInjectError
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   IN MXD_U16 numErrBit
);


/******************************************************************************
MXD_STATUS mxdSerdesRxInjectError
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   IN MXD_U16 numErrBit
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          
    numErrBit - Number of error bits to inject.

 Outputs:
    None  
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function injects errors into the Rx data path on an individual SerDes lane. 
    RX error injection affects only the main data channel. Therefore, errors 
    are only detected if the MAIN channel is one of the selected compare inputs.
      
 Side effects:
    None

 Notes/Warnings:
    Rx injected errors are detected in MXD_SERDES_RX_CMP_MODE_XOR and 
    MXD_SERDES_RX_CMP_MODE_MAIN_PATGEN compare modes, but are not detected in 
    MXD_SERDES_RX_CMP_MODE_TEST_PATGEN mode.

    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesRxInjectError
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,  
   IN MXD_U16 numErrBit
);


/******************************************************************************
MXD_STATUS mxdSerdesSetRxCmpMode
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_SERDES_RX_CMP_MODE_TYPE rxCmpMode
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          
    rxCmpMode - Rx comparison mode selection. Refer to MXD_SERDES_RX_CMP_MODE_TYPE 
                for selections
        MXD_SERDES_RX_CMP_MODE_OFF         = 0x0000, < Turn Off
        MXD_SERDES_RX_CMP_MODE_XOR         = 0x0100, < Test^Mission
        MXD_SERDES_RX_CMP_MODE_TEST_PATGEN = 0x0120, < Test^PatGen
        MXD_SERDES_RX_CMP_MODE_MAIN_PATGEN = 0x0200  < Mission^PatGen

 Outputs:
    None  
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function sets the Rx comparison mode selection on an individual SerDes lane. This 
    call is needed to detect Tx injected errors in RX MXD_SERDES_RX_CMP_MODE_TEST_PATGEN  
    and MXD_SERDES_RX_CMP_MODE_MAIN_PATGEN modes.
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesSetRxCmpMode
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_SERDES_RX_CMP_MODE_TYPE rxCmpMode
);


/******************************************************************************
MXD_STATUS mxdSerdesGetRxCmpMode
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   OUT MXD_SERDES_RX_CMP_MODE_TYPE *rxCmpMode
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          

 Outputs:
    rxCmpMode - Rx comparison mode selection. Refer to MXD_SERDES_RX_CMP_MODE_TYPE for selections
        MXD_SERDES_RX_CMP_MODE_OFF         = 0x0000, < Turn Off
        MXD_SERDES_RX_CMP_MODE_XOR         = 0x0100, < Test^Mission
        MXD_SERDES_RX_CMP_MODE_TEST_PATGEN = 0x0120, < Test^PatGen
        MXD_SERDES_RX_CMP_MODE_MAIN_PATGEN = 0x0200  < Mission^PatGen
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function gets the Rx comparison mode selection on an individual SerDes lane. 
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesGetRxCmpMode
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   OUT MXD_SERDES_RX_CMP_MODE_TYPE *rxCmpMode
);


/******************************************************************************
MXD_STATUS mxdSerdesSetTxPRBS
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_SERDES_TX_DATA_TYPE txDataType
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          
    txDataType - Tx data selection. Refer to MXD_SERDES_TX_DATA_TYPE for selections
        MXD_SERDES_TX_DATA_SEL_PRBS7    = 0, < PRBS7 (x^7+x^6+1) 
        MXD_SERDES_TX_DATA_SEL_PRBS9    = 1, < PRBS9 (x^9+x^7+1)   
        MXD_SERDES_TX_DATA_SEL_PRBS11   = 2, < PRBS11 (x^11+x^9+1) 
        MXD_SERDES_TX_DATA_SEL_PRBS15   = 3, < PRBS15 (x^15+x^14+1)
        MXD_SERDES_TX_DATA_SEL_PRBS23   = 4, < PRBS23 (x^23+x^18+1)
        MXD_SERDES_TX_DATA_SEL_PRBS31   = 5, < PRBS31 (x^31+x^28+1)
        MXD_SERDES_TX_DATA_SEL_USER     = 7, < User pattern generator
        MXD_SERDES_TX_DATA_SEL_CORE     = 8, < External data
        MXD_SERDES_TX_DATA_SEL_LOOPBACK = 9  < Parallel loopback from receiver

 Outputs:
    None  
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function sets the Tx PRBS data source on an individual SerDes lane. 
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesSetTxPRBS
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_SERDES_TX_DATA_TYPE txDataType
);


/******************************************************************************
MXD_STATUS mxdSerdesGetTxPRBS
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   OUT MXD_SERDES_TX_DATA_TYPE *txDataType
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          

 Outputs:
    txDataType - Returns the Tx data selection. Refer to MXD_SERDES_TX_DATA_TYPE 
                 for selection type.  
        MXD_SERDES_TX_DATA_SEL_PRBS7    = 0, < PRBS7 (x^7+x^6+1) 
        MXD_SERDES_TX_DATA_SEL_PRBS9    = 1, < PRBS9 (x^9+x^7+1)   
        MXD_SERDES_TX_DATA_SEL_PRBS11   = 2, < PRBS11 (x^11+x^9+1) 
        MXD_SERDES_TX_DATA_SEL_PRBS15   = 3, < PRBS15 (x^15+x^14+1)
        MXD_SERDES_TX_DATA_SEL_PRBS23   = 4, < PRBS23 (x^23+x^18+1)
        MXD_SERDES_TX_DATA_SEL_PRBS31   = 5, < PRBS31 (x^31+x^28+1)
        MXD_SERDES_TX_DATA_SEL_USER     = 7, < User pattern generator
        MXD_SERDES_TX_DATA_SEL_CORE     = 8, < External data
        MXD_SERDES_TX_DATA_SEL_LOOPBACK = 9  < Parallel loopback from receiver

 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function retrieves the selected Tx PRBS data type for the SerDes lane.
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesGetTxPRBS
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   OUT MXD_SERDES_TX_DATA_TYPE *txDataType
);

/******************************************************************************
MXD_STATUS mxdSerdesSetTxOutputEnable
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_U16 outputEnable
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          
    outputEnable - MXD_ENABLE to enable output signal; MXD_DISABLE to disable output signal.  

 Outputs:
    none

 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function sets the Tx output enable state on a SerDes lane 
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesSetTxOutputEnable
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_U16 outputEnable
);

/******************************************************************************
MXD_STATUS mxdSerdesGetTxOutputEnable
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   OUT MXD_U16 *outputEnable
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          

 Outputs:
    outputEnable - returns MXD_ENABLE if output signal is enabled; MXD_DISABLE if
                   output signal is disabled  
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function returns the Tx output enable state. Refer to mxdSerdesSetTxOutputEnable() 
    to enable/disable the Tx output state on a SerDes lane.

 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesGetTxOutputEnable
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   OUT MXD_U16 *outputEnable
);

/******************************************************************************
MXD_STATUS mxdSerdesSetTxRxEnable
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_U16 txState,
   IN MXD_U16 rxState,
   IN MXD_U16 txOutputState
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          
    txState - MXD_ENABLE to enable Tx state; MXD_DISABLE to disable Tx state.  
    rxState - MXD_ENABLE to enable Rx state; MXD_DISABLE to disable Rx state.  
    txOutputState - MXD_ENABLE to enable Tx output state; 
                    MXD_DISABLE to disable Tx output state.  

 Outputs:
    none

 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function sets the Tx & Rx enable states, and Tx output values. 
    If enabling Tx or Rx, it waits for the device to become ready.

 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesSetTxRxEnable
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_U16 txState,
   IN MXD_U16 rxState,
   IN MXD_U16 txOutputState
);

/******************************************************************************
MXD_STATUS mxdSerdesGetTxRxReady
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   OUT MXD_U16 *txState,
   OUT MXD_U16 *rxState
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          

 Outputs:
    txState - MXD_ENABLE if Tx ready state is enabled; otherwise Tx ready state is disabled.  
    rxState - MXD_ENABLE if Rx ready state is enabled; otherwise Rx ready state is disabled.  
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function gets the Tx and Rx ready state. Refer to mxdSerdesSetTxRxEnable() 
    to enable/disable the Tx and Rx ready state on a SerDes lane.

 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesGetTxRxReady
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   OUT MXD_U16 *txState,
   OUT MXD_U16 *rxState
);

/******************************************************************************
MXD_STATUS mxdSerdesSetTxUserData
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_32 userData[4]
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          
    userData[4] - 80-bit user data (4 x 20).

 Outputs:
    None  
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function loads the 80-bit value into the TX user data register and 
    select it as the TX input. The bit transmit order is from the least 
    significant bit [0] of user_data[0] through bit [19] of user_data[3].
    Each word holds 20 significant bits.

 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesSetTxUserData
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_32 userData[4]
);


/******************************************************************************
MXD_STATUS mxdSerdesGetTxUserData
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   OUT MXD_32 userData[4]
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          

 Outputs:
    userData[4] - 80-bit user data (4 x 20)  
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function retrieves the 80-bit TX user data register. 

    Only the first 20 bits of the pattern are returned as that is all 
    that is readily available from the SerDes.

    These bits are then duplicated into the other bits.
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.

    Only the first 20 bits of the pattern are returned as that is all 
    that is readily available from the SerDes. See description for details.
*******************************************************************************/
MXD_STATUS mxdSerdesGetTxUserData
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   OUT MXD_32 userData[4]
);


/******************************************************************************
MXD_STATUS mxdSerdesSetRxCmpData
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_SERDES_RX_CMP_TYPE RxCmpType
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          
    RxCmpType - Rx compare data setting. Refer to MXD_SERDES_RX_CMP_TYPE for
                selections
        MXD_SERDES_RX_CMP_DATA_PRBS7     = 0, < PRBS7 (x^7+x^6+1)   
        MXD_SERDES_RX_CMP_DATA_PRBS9     = 1, < PRBS9 (x^9+x^7+1)   
        MXD_SERDES_RX_CMP_DATA_PRBS11    = 2, < PRBS11 (x^11+x^9+1) 
        MXD_SERDES_RX_CMP_DATA_PRBS15    = 3, < PRBS15 (x^15+x^14+1)
        MXD_SERDES_RX_CMP_DATA_PRBS23    = 4, < PRBS23 (x^23+x^18+1)
        MXD_SERDES_RX_CMP_DATA_PRBS31    = 5, < PRBS31 (x^31+x^28+1)
        MXD_SERDES_RX_CMP_DATA_SELF_SEED = 7, < Auto-seed to received 40 bit repeating pattern. 
                                              < NOTE: This is USER mode in firmware. 
        MXD_SERDES_RX_CMP_DATA_OFF       = 8  < Disable cmp data generator 

 Outputs:
    None  
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function sets the RX compare data configuration. It sets the PRBS pattern 
    to compare incoming data against. If MXD_SERDES_RX_CMP_DATA_SELF_SEED is 
    selected, the comparator automatically synchronizes to an incoming 80 bit 
    pattern. The error counter then reports deviations from that pattern.
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesSetRxCmpData
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_SERDES_RX_CMP_TYPE RxCmpType
);


/******************************************************************************
MXD_STATUS mxdSerdesGetRxCmpData
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   OUT MXD_SERDES_RX_CMP_TYPE *RxCmpType
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          

 Outputs:
    RxCmpType - Rx compare data type from the MXD_SERDES_RX_CMP_TYPE selection  
        MXD_SERDES_RX_CMP_DATA_PRBS7     = 0, < PRBS7 (x^7+x^6+1)   
        MXD_SERDES_RX_CMP_DATA_PRBS9     = 1, < PRBS9 (x^9+x^7+1)   
        MXD_SERDES_RX_CMP_DATA_PRBS11    = 2, < PRBS11 (x^11+x^9+1) 
        MXD_SERDES_RX_CMP_DATA_PRBS15    = 3, < PRBS15 (x^15+x^14+1)
        MXD_SERDES_RX_CMP_DATA_PRBS23    = 4, < PRBS23 (x^23+x^18+1)
        MXD_SERDES_RX_CMP_DATA_PRBS31    = 5, < PRBS31 (x^31+x^28+1)
        MXD_SERDES_RX_CMP_DATA_SELF_SEED = 7, < Auto-seed to received 40 bit repeating pattern. 
                                              < NOTE: This is USER mode in firmware. 
        MXD_SERDES_RX_CMP_DATA_OFF       = 8  < Disable cmp data generator 

 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function retrieves the Rx compare data configuration that is set by
    the mxdSerdesSetRxCmpData function.

 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesGetRxCmpData
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   OUT MXD_SERDES_RX_CMP_TYPE *RxCmpType
);


/******************************************************************************
MXD_STATUS mxdSerdesGetErrCount
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_BOOL resetCounter,
   OUT MXD_U32 *errCount
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          
    resetCounter - Set to MXD_TRUE to reset error count after read or
                   MXD_FALSE to not reset the error counter.

 Outputs:
    errCount - returns the number of error count    
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function retrieves the error count for the earlier operations.

    If the resetCounter is MXD_TRUE will reset the error counter to 0 
    after reading the value.

 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesGetErrCount
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_BOOL resetCounter,
   OUT MXD_U32 *errCount
);


#define MXD_CLEAR_SERDES_LOOPBACK 0
#define MXD_DEEP_SERDES_LOOPBACK 1
#define MXD_SHALLOW_SERDES_LOOPBACK 2
/******************************************************************************
MXD_STATUS mxdSerdesSetRxLoopback
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_BOOL loopbackState
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          
    loopbackState - MXD_ENABLE to enable the Rx loopback on the SerDes lane; 
                    otherwise MXD_DISABLE to disable Rx loopback 

 Outputs:
    None  
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function sets the Rx loopback on an individual serdes lane.
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.

    Refer to the mxdSerdesSetLoopback API for more options on loopback settings
*******************************************************************************/
MXD_STATUS mxdSerdesSetRxLoopback
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_BOOL loopbackState
);


#define MXD_CLEAR_SERDES_LOOPBACK 0 /* same as mxdSerdesSetRxLoopback with MXD_DISABLE */
#define MXD_DEEP_SERDES_LOOPBACK 1 /* same as mxdSerdesSetRxLoopback with MXD_ENABLE */
#define MXD_SHALLOW_SERDES_LOOPBACK 2 /* loopback internal Rx traffic to the Tx */
/******************************************************************************
MXD_STATUS mxdSerdesSetLoopback
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_U16 loopbackMode 
);                          

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          
    loopbackMode -  MXD_CLEAR_SERDES_LOOPBACK(0)
                    MXD_DEEP_SERDES_LOOPBACK(1) 
                    MXD_SHALLOW_SERDES_LOOPBACK(2)

 Outputs:
    None  
    
 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function provides more options to set the SerDes loopback modes. It will
    set an individual SerDes lane to input loopback mode.
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesSetLoopback
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr,
   IN MXD_U16 loopbackMode 
);                          


/******************************************************************************
 MXD_STATUS mxdSerdesPRBSDiagnostic
 (
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 txSerDesAddr,
    IN MXD_U16 rxSerDesAddr,
    IN MXD_U16 bitRateDivider,
    IN MXD_BOOL intLoopbackMode,
    IN MXD_SERDES_RX_CMP_MODE_TYPE rxCmpMode,
    IN MXD_SERDES_TX_DATA_TYPE typePRBS
 );

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    txSerDesAddr - Tx SerDes lane addr. Range[1-8]; 
    rxSerDesAddr - Rx SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          
    bitRateDivider - input divider to configure
            The reference clock is at 156.25Mhz. Following example on setting the 
            SerDes bit rate:
            10G: divider = 66
            25G: divider = 165
    intLoopbackMode - option for internal loopback on a same Rx/Tx lane; 
                      set to MXD_DISABLE if Rx and Tx are different or 
                      an external loopback device is used on the same Rx/Tx lane

    rxCmpMode -  Enabled Rx comparison mode to test error injection 
                        - MXD_SERDES_RX_CMP_MODE_TEST_PATGEN(0x0120)
                        - MXD_SERDES_RX_CMP_MODE_MAIN_PATGEN(0x0200) 
                 Disabled Rx comparison mode 
                        - MXD_SERDES_RX_CMP_MODE_OFF(0x0000) 

    typePRBS - PRBS pattern to be used; refer to MXD_SERDES_TX_DATA_TYPE

 Outputs:
        none

 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
     This SerDes PRBS diagnostic API provides an example to run a PRBS pattern test.
     This API runs a basic PRBS pattern test on the provided SerDes Tx and Rx lanes.  
     The lanes are initialized to the requested bit rate based on the bitRateDivider. 
     If the error injection is called during this test, the rxCmpMode has to be set 
     to a listed comparison mode. Running the SerDes PRBS diagnostic test requires 
     the SerDes lane to be in a clean reset state.

 Notes/Warnings:
    The Tx and Rx SerDes lanes bit rate must be configured using the bit rate 
    ratio divider. The SerDes should not be configured with the operational 
    mode using the mxdSetFixedModeSelection() or mxdSetUserFixedModeSelection().

    Running this test requires a valid Tx and Rx paths. If the same Tx and Rx
    SerDes lane is used, an external loopback will be needed. 

    After tuning the iCal values, it needs about 6-8secs for the SerDes lane to be 
    ready for the test.

    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
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
);


/******************************************************************************
MXD_STATUS mxdSerdesReset
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr
);                         

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID mapping in MXD_DEV for Host/Line lane offset          

 Outputs:
    none

 Returns:
    MXD_OK if successful, MXD_FAIL otherwise

 Description:
    This function resets a SerDes lane on a given SerDes lane ID.
      
 Side effects:
    None

 Notes/Warnings:
    Calling this function requires blocking all other caller from issuing 
    interrupt read/write calls to the SerDes and SBus master.
*******************************************************************************/
MXD_STATUS mxdSerdesReset
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 sAddr
);                         


#endif /* MXD_ENABLE_SERDES_API */


#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MXD_HWSERDESCNT_H */

