/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions and global data for higher-level functions 
using MDIO access to enable test modes, loopbacks, and other diagnostic 
functions for the Marvell X7120/X6181/X6141 PHY.
********************************************************************/
#ifndef MYDDIAG_H
#define MYDDIAG_H

#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

/******************************************************************************
 MYD_STATUS mydGetChipRevision
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    OUT MYD_DEVICE_ID *deviceId
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31

 Outputs:
    deviceId - revision of this chip, see MYD_DEVICE_ID definition for
               a list of chip revisions with different options

 Returns:
    MYD_OK if query was successful, MYD_FAIL if not

 Description:
    Determines the PHY revision and returns the value in phyRev.
    See definition of MYD_DEVICE_ID for a list of available
    devices and capabilities.

 Side effects:
    None.

 Notes/Warnings:
    None

******************************************************************************/
MYD_STATUS mydGetChipRevision
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    OUT MYD_DEVICE_ID *deviceId
);

/******************************************************************************
MYD_STATUS mydDevicePortCount
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    OUT MYD_U16 *portCount
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31

 Outputs:
    portCount - returns the number of ports for the device type

 Returns:
    MYD_OK if query was successful, MYD_FAIL if not

 Description:
    Determines the number of port count based on the MYD_DEVICE_ID device
    type.

 Side effects:
    None.

 Notes/Warnings:
    None

******************************************************************************/
MYD_STATUS mydDevicePortCount
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    OUT MYD_U16 *portCount
);

/******************************************************************************
 MYD_STATUS mydGetChipFWRevision
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    OUT MYD_U16 *major,
    OUT MYD_U16 *minor
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31    

 Outputs:
    major - returns the major revision number
    minor - returns the minor revision number
            Revision in <major>.<minor> format 

 Returns:
    MYD_OK if query was successful, MYD_FAIL if chip firmware is not available

 Description:
    Retrieves the chip firmware revision number. The revision is in 
    the <major>.<minor> format.  

 Side effects:
    None.

 Notes/Warnings:
    The version will return 0.0 if chip firmware is not available. Not all devices
    require the chip firmware.

******************************************************************************/
MYD_STATUS mydGetChipFWRevision
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    OUT MYD_U16 *major,
    OUT MYD_U16 *minor
);

/******************************************************************************
 MYD_STATUS mydGetSerdesSignalDetectAndDspLock
 (
     IN MYD_DEV_PTR pDev,
     IN MYD_U16 mdioPort,     
     IN MYD_U16  host_or_line,
     IN MYD_U16 laneOffset,
     OUT MYD_U16 *signalDetect,
     OUT MYD_U16 *dspLock
 );

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31    
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3


 Outputs:
    signalDetect - value of serdes signal detect,  1 or 0
    dspLock - value of serdes DSP lock, 1 or 0

 Returns:
    MYD_OK if query was successful, MYD_FAIL if not

 Description:
    Reads the corresponding lane Signal Detect and DSP Lock status. This call
    is used for the Repeater mode to determine if the lane and link signal.

 Side effects:
    None.

 Notes/Warnings:
    None

******************************************************************************/
MYD_STATUS mydGetSerdesSignalDetectAndDspLock
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,    
    IN MYD_U16  host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *signalDetect,
    OUT MYD_U16 *dspLock
);


#define MYD_SHALLOW_PCS_LB    1
#define MYD_DEEP_PCS_LB       2
#define MYD_DEEP_PMA_LB       3

/*******************************************************************************
 MYD_STATUS mydSetPCSLineLoopback
 (
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    IN MYD_U16 loopback_type,
    IN MYD_U16 enable
 );

 Inputs:
    pDev     - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    laneOffset - 0..3 for lanes 0-3
    loopback_type - MYD_SHALLOW_PCS_LB, MYD_DEEP_PCS_LB, MYD_DEEP_PMA_LB
    enable   - MYD_ENABLE/MYD_DISABLE

 Outputs:
    None

 Returns:
    MYD_OK or MYD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    This function is used to Enable/Disable line side loopbacks. There are 
    3 loopback options for the loopback_type parameter. One of these 3 options, 
    MYD_SHALLOW_PCS_LB, MYD_DEEP_PCS_LB and MYD_DEEP_PMA_LB should be used when 
    calling this API.  Only a single loopback type should be used each time.  

    Refer to the datasheet for more detail on the differences on the 3 types of 
    loopbacks.

 Side effects:
    None

 Notes/Warnings:
    Only a single loopback type should be used each time.  Setting more than one 
    loopback either on the host and line sides will have unpredictable behavior.

    A lane soft reset(mydLaneSoftReset)is recommended after disabling this feature.
*******************************************************************************/
MYD_STATUS mydSetPCSLineLoopback
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    IN MYD_U16 loopback_type,
    IN MYD_U16 enable
);

/*******************************************************************************
 MYD_STATUS mydSetPCSHostLoopback
 (
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    IN MYD_U16 loopback_type,
    IN MYD_U16 enable
 );

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    laneOffset - 0..3 for lanes 0-3
    loopback_type - MYD_SHALLOW_PCS_LB, MYD_DEEP_PCS_LB, MYD_DEEP_PMA_LB
    enable - MYD_ENABLE/MYD_DISABLE

 Outputs:
    None

 Returns:
    MYD_OK or MYD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    This function is used to Enable/Disable host side loopbacks. There are 
    3 loopback options for the loopback_type parameter. One of these 3 options, 
    MYD_SHALLOW_PCS_LB, MYD_DEEP_PCS_LB and MYD_DEEP_PMA_LB should be used when 
    calling this API.  Only a single loopback type should be used each time.  

    Refer to the datasheet for more detail on the differences on the 3 types of 
    loopbacks.

 Side effects:
    None

 Notes/Warnings:
    Only a single loopback type should be used each time.  Setting more than one 
    loopback either on the host and line sides will have unpredictable behavior.

    A lane soft reset(mydLaneSoftReset)is recommended after disabling this feature.

*******************************************************************************/
MYD_STATUS mydSetPCSHostLoopback
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    IN MYD_U16 loopback_type,
    IN MYD_U16 enable
);

/* possible values for pktPatternControl */
#define PACKET_GEN_200G_OFFSET     0x4000
#define PACKET_GEN_40G_OFFSET      0x0F10
#define PACKET_GEN_25G_OFFSET     (0x0F10+0x1000)
#define PACKET_GEN_1G_OFFSET      (0x0F10+0x2000)

#define MYD_PKT_NO_MASK            0  /* payload sent without change */
#define MYD_PKT_INV_SKIP_WRD       2  /* inverts every other word  */
#define MYD_PKT_2INV_2NOT          3  /* two inverted two not inverted */
#define MYD_PKT_LFT_SHFT_BYTE      4  /* left shift by byte */
#define MYD_PKT_RHT_SHFT_BYTE      5  /* right shift by byte */
#define MYD_PKT_LFT_SHFT_WRD       6  /* left shift by word */
#define MYD_PKT_RHT_SHFT_WRD       7  /* right shift by word */
#define MYD_PKT_INC_BYTE           8  /* increment by byte */
#define MYD_PKT_DEC_BYTE           9  /* decrement by byte */
#define MYD_PKT_RANDOM_BYTE       10  /* pseudo-random byte */
#define MYD_PKT_RANDOM_WORD       11  /* pseudo-random word */

/* possible values for frameLengthControl */
#define MYD_PKT_RAND_LEN0          0 /* rand len 64 bytes - 1518 bytes */
#define MYD_PKT_RAND_LEN1          1 /* rand len 64 bytes - 0xFFF bytes */
#define MYD_PKT_RAND_LEN2          2 /* rand len 64 bytes - 0x1FFF bytes */
#define MYD_PKT_RAND_LEN3          3 /* rand len 64 bytes - 0x3FFF bytes */
#define MYD_PKT_RAND_LEN4          4 /* rand len 64 bytes - 0x7FFF bytes */
#define MYD_PKT_RAND_LEN5          5 /* rand len 64 bytes - 0xFFFF bytes */
/* 6 and 7 are reserved/undefined */
/* values 8 and greater are the exact length of the frame in bytes up to 0xFFFF */

/******************************************************************************
 MYD_STATUS mydConfigurePktGeneratorChecker
 (
     IN MYD_DEV_PTR devPtr,
     IN MYD_U16  mdioPort,
     IN MYD_U16  host_or_line,
     IN MYD_U16  laneOffset,
     IN MYD_BOOL readToClear,
     IN MYD_BOOL dontuseSFDinChecker,
     IN MYD_U16  pktPatternControl,
     IN MYD_BOOL generateCRCoff,
     IN MYD_U32  initialPayload,
     IN MYD_U16  frameLengthControl,
     IN MYD_U16  numPktsToSend,
     IN MYD_BOOL randomIPG,
     IN MYD_U16  ipgDuration
 );

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being checked:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3.
    readToClear - MYD_TRUE if the desired behavior is that when the
                  counters are read, they are reset. MYD_FALSE if the
                  desired behavior is that they must be explicitly cleared
                  by mydPktGeneratorCounterReset() and reading
                  them just returns the current value without clearing them.
    dontuseSFDinChecker - MYD_TRUE indicates to start CRC checking after the
                      first 8 bytes in the packet, MYD_FALSE indicates
                      to look for SFD before starting CRC checking
    pktPatternControl - controls the generation of the payload. One of the
                        following:
                            MYD_PKT_NO_MASK
                            MYD_PKT_INV_SKIP_WRD
                            MYD_PKT_2INV_2NOT
                            MYD_PKT_LFT_SHFT_BYTE
                            MYD_PKT_RHT_SHFT_BYTE
                            MYD_PKT_LFT_SHFT_WRD
                            MYD_PKT_RHT_SHFT_WRD
                            MYD_PKT_INC_BYTE
                            MYD_PKT_DEC_BYTE
                            MYD_PKT_RANDOM_BYTE
                            MYD_PKT_RANDOM_WORD
    generateCRCoff - MYD_TRUE turns CRC generation off, MYD_FALSE turns
                     CRC generation on
    initialPayload - start of payload value. Format is from MS bit to
                     LS bit: BYTE3:BYTE2:BYTE1:BYTE0, bit 31 to bit 0,
                     left to right
    frameLengthControl - controls the length of the frame in bytes.
                         values 0...5 (see above) pick various random lengths
                         from 64 to a different stop value. 6/7 is undefined
                         and values 8 and greater are the exact frame length
                         in bytes. See definitions above MYD_PKT_RAND_LEN0-5.
    numPktsToSend - 0 stops generation, 0x001-0xFFFE sends exactly that number
                    of packets then stops. 0xFFFF sends continuously.
    randomIPG - MYD_TRUE uses a random IPG from 5 bytes to value specified
                in ipgDuration. MYD_FALSE uses fixed IPG as specified in
                ipgDuration.
    ipgDuration - Meaning depends on randomIPG (see above). Each bit
                  equals 4 bytes of idle. Valid range is 0...0x7FFF.

 Outputs:
    None

 Returns:
    MYD_OK or MYD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    This function is used to configure the packet generator/checker.

 Side effects:
    None

 Notes/Warnings:
    Call mydEnablePktGeneratorChecker() to enable/start the generator/checker.

******************************************************************************/
MYD_STATUS mydConfigurePktGeneratorChecker
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    IN MYD_BOOL readToClear,
    IN MYD_BOOL dontuseSFDinChecker,
    IN MYD_U16  pktPatternControl,
    IN MYD_BOOL generateCRCoff,
    IN MYD_U32  initialPayload,
    IN MYD_U16  frameLengthControl,
    IN MYD_U16  numPktsToSend,
    IN MYD_BOOL randomIPG,
    IN MYD_U16  ipgDuration
);

/******************************************************************************
 MYD_STATUS mydEnablePktGeneratorChecker
 (
     IN MYD_DEV_PTR pDev,
     IN MYD_U16  mdioPort,
     IN MYD_U16  host_or_line,
     IN MYD_U16  laneOffset,
     IN MYD_BOOL enableGenerator,
     IN MYD_BOOL enableChecker
 );

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being checked:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3. 
    enableGenerator - MYD_TRUE starts the packet generator, MYD_FALSE
                      stops it
    enableChecker - MYD_TRUE starts the packet checker, MYD_FALSE
                    stops it

 Outputs:
    None

 Returns:
    MYD_OK or MYD_FAIL

 Description:
    This function enables/disables either the packet generator or packet checker
    (or both).

 Side effects:
    None

 Notes/Warnings:
    A lane soft reset(mydLaneSoftReset)is recommended after disabling this feature.

******************************************************************************/
MYD_STATUS mydEnablePktGeneratorChecker
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    IN MYD_BOOL enableGenerator,
    IN MYD_BOOL enableChecker
);

/******************************************************************************
 MYD_STATUS mydPktGeneratorCounterReset
 (
     IN MYD_DEV_PTR pDev,
     IN MYD_U16 mdioPort,
     IN MYD_U16 host_or_line,
     IN MYD_U16 laneOffset
 );

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being checked:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3. 

 Outputs:
    None

 Returns:
    MYD_OK or MYD_FAIL

 Description:
    This function explicitly clears all the counters when the packet
    generator/checker has been setup to be cleared by writing a
    bit to the control register instead of being cleared when
    the counter(s) are read.

 Side effects:
    None

 Notes/Warnings:
    None
******************************************************************************/
MYD_STATUS mydPktGeneratorCounterReset
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset
);

#define MYD_PKT_GET_TX  0
#define MYD_PKT_GET_RX  1
#define MYD_PKT_GET_ERR 2
/******************************************************************************
 MYD_STATUS mydPktGeneratorGetCounter
 (
     IN MYD_DEV_PTR pDev,
     IN MYD_U16  mdioPort,
     IN MYD_U16  host_or_line,
     IN MYD_U16  laneOffset,
     IN MYD_U16  whichCounter,
     OUT MYD_U64 *packetCount,
     OUT MYD_U64 *byteCount
 );

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being checked:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3. 
    whichCounter - One of the following, depending on which set of counters
                   is being read:
                       MYD_PKT_GET_TX to read the generator/transmit counters
                       MYD_PKT_GET_RX to read the checker/receive counters
                       MYD_PKT_GET_ERR to read the packet error counter


 Outputs:
    packetCount - tx/rx/err packet count in the following format
                  from MS bit to LS bit (note top 16-bits is always
                  0, since this is a 48-bit result):
                  0:WORD2:WORD1:WORD0 where each word is a 16-bit
                  unsigned value, and words are combined into
                  a single, 48-bit result.
    byteCount - tx/rx byte count in the following format
                  from MS bit to LS bit (note top 16-bits is always
                  0, since this is a 48-bit result):
                  0:WORD2:WORD1:WORD0 where each word is a 16-bit
                  unsigned value, and words are combined into
                  a single, 48-bit result. NOTE: This parameter
                  is always 0 when whichCounter is set to
                  MYD_PKT_GET_ERR, since error counter is a packet
                  count only.

 Returns:
    MYD_OK or MYD_FAIL

 Description:
    This function is used to read the transmit/receive/error counter for the
    packet generator/checker.

 Side effects:
    None

 Notes/Warnings:
    byteCount is always 0 for MYD_PKT_GET_ERR, since the error counter
    only counts packets.

    If packet generator/checker was configured to clear counter(s) on read,
    this function will clear the counter being read.

******************************************************************************/
MYD_STATUS mydPktGeneratorGetCounter
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    IN MYD_U16  whichCounter,
    OUT MYD_U64 *packetCount,
    OUT MYD_U64 *byteCount
);

typedef enum
{
    /* NRZ signal supported PRBS patterns starts here */ 
    MYD_PRBS31,   /* 0000b */
    MYD_PRBS7,    /* 0001b */  
    MYD_PRBS9,    /* 0010b */   
    MYD_PRBS23,   /* 0011b */  
    MYD_IPRBS31,  /* 0100b */  
    MYD_IPRBS7,   /* 0101b */  
    MYD_IPRBS9,   /* 0110b */  
    MYD_IPRBS23,  /* 0111b */  
    MYD_PRBS15,   /* 1000b */  
    MYD_IPRBS15,  /* 1001b */  
    MYD_PRBS58,   /* 1010b */  
    MYD_IPRBS58,  /* 1011b */  
    MYD_PRBS13,   /* 1100b */  
    MYD_IPRBS13,  /* 1101b */  
    MYD_JP03AB,   /* 1110b */
    MYD_GEN_TX,   /* 1111b */

    /* PAM-4 supported PRBS patterns starts here */ 
    MYD_PAM4_PRBS31Q = 100,  
    MYD_PAM4_PRBS13Q,
    MYD_PAM4_PRBS15Q,  
    MYD_PAM4_JP03A,
    MYD_PAM4_JP03B,
    MYD_PAM4_SSPRQ  /* Short Stress Pattern Random - Quaternary */
} MYD_PRBS_SELECTOR_TYPE;

typedef enum
{
    MYD_PRBS_NONE,       /* goes with all other options */
    MYD_JP03A,           /* goes with MYD_LINE_JP03AB to select JP03A */
    MYD_JP03B,           /* goes with MYD_LINE_JP03AB to select JP03B */
    MYD_LOW_FREQ,        /* goes with MYD_LINE_GEN_TX */
    MYD_SQUARE_WAV,      /* goes with MYD_LINE_GEN_TX */
    MYD_MIXED_FREQ       /* goes with MYD_LINE_GEN_TX */
} MYD_PATTERN_AB_SELECTOR_TYPE;

/*******************************************************************************
 MYD_STATUS mydSetPRBSPattern
 (
     IN MYD_DEV_PTR pDev,
     IN MYD_U16  mdioPort,
     IN MYD_U16  host_or_line,    
     IN MYD_U16  laneOffset,
     IN MYD_PRBS_SELECTOR_TYPE pattSel,
     IN MYD_PATTERN_AB_SELECTOR_TYPE pattSubSel
 );

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being checked:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3. 
    pattSel - one of the patterns from the MYD_PRBS_SELECTOR_TYPE
         
    pattSubSel - valid only if pattSel is either MYD_JP03AB or MYD_GEN_TX 
                 MYD_JP03AB use: MYD_JP03A or MYD_JP03B
                 MYD_GEN_TX use: MYD_LOW_FREQ or MYD_SQUARE_WAV or MYD_MIXED_FREQ  

 Outputs:
    None

 Returns:
    MYD_OK or MYD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    This function selects the type of PRBS pattern desired for the individual lane 
    offset on either the line or host side. Some pattern selections require further 
    input selection for pattSubSel.  Refer to the inputs description for the list 
    of selections.

 Side effects:
    None
    
 Notes/Warnings:
    From the MYD_PRBS_SELECTOR_TYPE pattern selections, there are 2 sets of pattern 
    types.  The PAM-4 PRBS are designed for the PAM-4 signal modes and the non-PAM4 
    are for the NRZ signal modes.  Before running the PRBS test, the link should be 
    up with the appropriate signal mode. 
    
*******************************************************************************/
MYD_STATUS mydSetPRBSPattern
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,    
    IN MYD_U16  laneOffset,
    IN MYD_PRBS_SELECTOR_TYPE pattSel,
    IN MYD_PATTERN_AB_SELECTOR_TYPE pattSubSel
);


/*******************************************************************************
 MYD_STATUS mydSetPRBSEnableTxRx
 (
     IN MYD_DEV_PTR pDev,
     IN MYD_U16  mdioPort,     
     IN MYD_U16  host_or_line,
     IN MYD_U16  laneOffset,
     IN MYD_U16  txEnable,
     IN MYD_U16  rxEnable,
     IN MYD_PRBS_SELECTOR_TYPE pattSel
 );
 
 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31    
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3. 
    txEnable - MYD_ENABLE or MYD_DISABLE to start or stop the transmit
    rxEnable - MYD_ENABLE or MYD_DISABLE to start or stop the receiver
    pattSel - one of the patterns from the MYD_PRBS_SELECTOR_TYPE

 Outputs:
    None

 Returns:
    MYD_OK or MYD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    This function is used to start or stop the PRBS transmit and/or 
    receiver.

 Side effects:
    None
   
 Notes/Warnings:
    From the MYD_PRBS_SELECTOR_TYPE pattern selections, there are 2 sets of pattern 
    types.  The PAM-4 PRBS are designed for the PAM-4 signal modes and the non-PAM4 
    are for the NRZ signal modes.  Before running the PRBS test, the link should be 
    up with the appropriate signal mode. 
   
*******************************************************************************/
MYD_STATUS mydSetPRBSEnableTxRx
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,    
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    IN MYD_U16  txEnable,
    IN MYD_U16  rxEnable,
    IN MYD_PRBS_SELECTOR_TYPE pattSel
);

/*******************************************************************************
 MYD_STATUS mydPRBSCounterReset
 (
     IN MYD_DEV_PTR pDev,
     IN MYD_U16  mdioPort,
     IN MYD_U16  host_or_line,    
     IN MYD_U16  laneOffset
 );
 
 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3. 

 Outputs:
    None

 Returns:
    MYD_OK or MYD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    This function is used to reset the counters when the PRBS has been
    setup for manual clearing instead of clear-on-read. Default
    is to use manual clearing. Call mydSetPRBSEnableClearOnRead() to
    enable clearing the counters when reading the registers.

 Side effects:
    None
   
 Notes/Warnings:
    Assumes the PRBS has not been setup for clear-on-read.
   
*******************************************************************************/
MYD_STATUS mydPRBSCounterReset
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,    
    IN MYD_U16  host_or_line,    
    IN MYD_U16  laneOffset
);

/*******************************************************************************
 MYD_STATUS mydSetPRBSWaitForLock
 (
     IN MYD_DEV_PTR pDev,
     IN MYD_U16  mdioPort,    
     IN MYD_U16  host_or_line,    
     IN MYD_U16  laneOffset,
     IN MYD_U16  disableWaitforLock
 );
 
 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - port number, 0-31    
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3
    disableWaitforLock - 1 counts PRBS before locking, 0 waits
        for locking before counting

 Outputs:
    None

 Returns:
    MYD_OK or MYD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    Configures PRBS wait lock to wait for locking before counting

 Side effects:
    None
   
 Notes/Warnings:
    Should be called before starting the receiver.
   
*******************************************************************************/
MYD_STATUS mydSetPRBSWaitForLock
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,    
    IN MYD_U16  host_or_line,    
    IN MYD_U16  laneOffset,
    IN MYD_U16  disableWaitforLock
);

/*******************************************************************************
 MYD_STATUS mydGetPRBSWaitForLock
 (
     IN MYD_DEV_PTR pDev,
     IN MYD_U16  mdioPort,    
     IN MYD_U16  host_or_line,    
     IN MYD_U16  laneOffset,
     OUT MYD_U16 *disableWaitforLock
 );
 
 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - port number, 0-31    
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3

 Outputs:
    disableWaitforLock - 1 counts PRBS before locking, 0 waits
        for locking before counting

 Returns:
    MYD_OK or MYD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    Returns configuration for PRBS whether it is set to wait for locking
    or not before counting.

 Side effects:
    None
   
 Notes/Warnings:
    None
   
*******************************************************************************/
MYD_STATUS mydGetPRBSWaitForLock
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,    
    IN MYD_U16  host_or_line,    
    IN MYD_U16  laneOffset,
    OUT MYD_U16 *disableWaitforLock
);

/*******************************************************************************
 MYD_STATUS mydSetPRBSClearOnRead
 (
     IN MYD_DEV_PTR pDev,
     IN MYD_U16  mdioPort,    
     IN MYD_U16  host_or_line,    
     IN MYD_U16  laneOffset,
     IN MYD_U16  enableReadClear
 );
 
 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - port number, 0-31
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3
    enableReadClear - 1 enables clear-on-read, 0 enables manual clear 
        (by setting register bit).

 Outputs:
    None

 Returns:
    MYD_OK or MYD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    The default for the PRBS counters is to be cleared manually by 
    calling mydPRBSCounterReset(). This configures either to read-clear,or
    manual clear (by setting a register bit).

 Side effects:
    None
   
 Notes/Warnings:
    Should be called before starting the receiver.
   
*******************************************************************************/
MYD_STATUS mydSetPRBSClearOnRead
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,    
    IN MYD_U16  host_or_line,    
    IN MYD_U16  laneOffset,
    IN MYD_U16  enableReadClear
);


/*******************************************************************************
 MYD_STATUS mydGetPRBSClearOnRead
 (
     IN MYD_DEV_PTR pDev,
     IN MYD_U16  mdioPort,    
     IN MYD_U16  host_or_line,    
     IN MYD_U16  laneOffset,
     OUT MYD_U16  *enableReadClear
 );
 
 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - port number, 0-31
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3

 Outputs:
    enableReadClear - 1 clear-on-read enabled, 0 manual clear is enabled

 Returns:
    MYD_OK or MYD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    Checks whether the PRBS is configured to clear-on-read (1) or manual
    cleared (0).

 Side effects:
    None
   
 Notes/Warnings:
    None
   
*******************************************************************************/
MYD_STATUS mydGetPRBSClearOnRead
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,    
    IN MYD_U16  host_or_line,    
    IN MYD_U16  laneOffset,
    OUT MYD_U16  *enableReadClear
);

/*******************************************************************************
 MYD_STATUS mydGetPRBSLocked
 (
     IN MYD_DEV_PTR pDev,
     IN MYD_U16  mdioPort,
     IN MYD_U16  host_or_line,
     IN MYD_U16  laneOffset,
     OUT MYD_BOOL *prbsLocked
 );
 
 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3

 Outputs:
    prbsLocked - MYD_TRUE if the PRBS receiver is locked, MYD_FALSE otherwise

 Returns:
    MYD_OK or MYD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    Returns the indicator if the PRBS receiver is locked or not.

 Side effects:
    None
   
 Notes/Warnings:
    Should be called after starting the receiver.
   
*******************************************************************************/
MYD_STATUS mydGetPRBSLocked
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    OUT MYD_BOOL *prbsLocked
);

/*******************************************************************************
 MYD_STATUS mydGetPRBSCounts
 (
     IN MYD_DEV_PTR pDev,
     IN MYD_U16  mdioPort,
     IN MYD_U16  host_or_line,
     IN MYD_U16  laneOffset,
     IN MYD_PRBS_SELECTOR_TYPE pattSel,
     OUT MYD_U64 *txBitCount,
     OUT MYD_U64 *rxBitCount,
     OUT MYD_U64 *rxBitErrorCount
 );
 
 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3
    pattSel - one of the patterns from the MYD_PRBS_SELECTOR_TYPE

 Outputs:
    txBitCount - number of bits transmitted
    rxBitCount - number of bits received
    rxBitErrorCount - number of bits in error

 Returns:
    MYD_OK or MYD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    Returns the 48-bit results in the output parameters above. If the PRBS
    control has been set to clear-on-read, the registers will clear. If
    not, they must be cleared manually by calling mydPRBSCounterReset()

 Side effects:
    None
   
 Notes/Warnings:
    rxBitErrorCount will not be computed for PAM-4 PRBS MYD_PAM4_JP03A and 
    MYD_PAM4_JP03B.

*******************************************************************************/
MYD_STATUS mydGetPRBSCounts
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,    
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    IN MYD_PRBS_SELECTOR_TYPE pattSel,
    OUT MYD_U64 *txBitCount,
    OUT MYD_U64 *rxBitCount,
    OUT MYD_U64 *rxBitErrorCount
);


/*******************************************************************************
MYD_STATUS mydSetTxPolarity
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,     
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 polarity,
    IN MYD_U16 swReset
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - interface to be modified (MYD_HOST_SIDE or MYD_LINE_SIDE)
    laneOffset - 0..3 for lanes 0-3
    polarity - 1 to invert Tx polarity, 0 to use normal polarity.
    swReset - 1:issue s/w reset to apply set polarity change; 0:s/w reset not issue
    
 Outputs:
    None

 Returns:
    MYD_OK - if set Tx polarity is successfully issued
    MYD_FAIL - otherwise returns MYD_FAIL

 Description:
    This function set the Tx polarity with the given input parameters. To invert 
    the polarity on a given lane, set the polarity to 1 and issued a software 
    host or line reset(swReset:1). The reset is issued to the entire host or line 
    on a MDIO port.  

 Side effects:
    None

 Notes/Warnings:
    The link will be down if the Tx and Rx polarities are mismatched. The set 
    polarity will take effects after a software reset is issued.
*******************************************************************************/
MYD_STATUS mydSetTxPolarity
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,     
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 polarity,
    IN MYD_U16 swReset
);

/*******************************************************************************
MYD_STATUS mydGetTxPolarity
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,     
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *polarity
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - interface to be modified (MYD_HOST_SIDE or MYD_LINE_SIDE)
    laneOffset - 0..3 for lanes 0-3
    
 Outputs:
    polarity - 1:inverted Tx polarity, 0:normal polarity.

 Returns:
    MYD_OK - if Tx polarity is successfully read
    MYD_FAIL - otherwise returns MYD_FAIL

 Description:
    This function reads the Tx polarity with the given input parameters. 

 Side effects:
    None

 Notes/Warnings:
    The link will be down if the Tx and Rx polarities are mismatched. 
*******************************************************************************/
MYD_STATUS mydGetTxPolarity
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,     
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *polarity
);

/*******************************************************************************
MYD_STATUS mydSetRxPolarity
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,     
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 polarity,
    IN MYD_U16 swReset
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - interface to be modified (MYD_HOST_SIDE or MYD_LINE_SIDE)
    laneOffset - 0..3 for lanes 0-3
    polarity - 1 to invert Rx polarity, 0 to use normal polarity.
    swReset - 1:issue s/w reset to apply set polarity change; 0:s/w reset not issue
    
 Outputs:
    None

 Returns:
    MYD_OK - if set Rx polarity is successfully issued
    MYD_FAIL - otherwise returns MYD_FAIL

 Description:
    This function set the Rx polarity with the given input parameters. To invert 
    the polarity on a given lane, set the polarity to 1 and issued a software 
    host or line reset(swReset:1). The reset is issued to the entire host or line 
    on a MDIO port.  

 Side effects:
    None

 Notes/Warnings:
    The link will be down if the Tx and Rx polarities are mismatched. The set 
    polarity will take effects after a software reset is issued.
*******************************************************************************/
MYD_STATUS mydSetRxPolarity
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,     
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 polarity,
    IN MYD_U16 swReset
);

/*******************************************************************************
MYD_STATUS mydGetRxPolarity
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,     
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *polarity
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - interface to be modified (MYD_HOST_SIDE or MYD_LINE_SIDE)
    laneOffset - 0..3 for lanes 0-3
    
 Outputs:
    polarity - 1:inverted Rx polarity, 0:normal polarity.

 Returns:
    MYD_OK - if Rx polarity is successfully read
    MYD_FAIL - otherwise returns MYD_FAIL

 Description:
    This function reads the Rx polarity with the given input parameters. 

 Side effects:
    None

 Notes/Warnings:
    The link will be down if the Tx and Rx polarities are mismatched. 
*******************************************************************************/
MYD_STATUS mydGetRxPolarity
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,     
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *polarity
);

typedef struct _MYD_TX_FFE
{
    MYD_16 preCursor;
    MYD_16 pre2Cursor;
    MYD_16 pre3Cursor;
    MYD_16 attenuation;
    MYD_16 postCursor;
} MYD_TX_FFE, *PMYD_TX_FFE;

typedef struct _MYD_STATE_DUMP  /* Dump info for a MDIO port */
{
    MYD_DEV devStuct; 
    MYD_U16 serdesRevision;
    MYD_U16 sbmRevision;
    MYD_U32 apiVersion;
    MYD_32  coreTemperature;
    MYD_U16 voltageCore;
    MYD_U16 voltageDVDD;
    MYD_U16 voltageAVDD;
    MYD_U16 cntlPCSReg; /* 3/4.0000, ..., 3/4.4000 */
    MYD_U16 statusPCSReg; /* 3/4.0001, ..., 3/4.4001 */
    MYD_U16 modeSelectReg; /* 3/4.F000, ..., 3/4.F003 */
    MYD_U16 controlANEGReg; /* 7.8/9000, 7.8/9200, 7.8/9400, 7.8/9600 */
    MYD_U16 powerMgmtStateReg; /* 3/4.F050, 0xF053, 3/4.F056, 3/4.F059 */
    MYD_U16 serdesStateReg; /* 3/4.F204, 0xF284, 3/4.F304, 3/4.F384 */
    MYD_U16 params[4];
    MYD_U16 clkList[10];
    MYD_TX_FFE txFFE;
} MYD_STATE_DUMP, *PMYD_STATE_DUMP;
 
/*******************************************************************************
MYD_STATUS mydDiagStateDump
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort, 
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U32 stateDumpOptions,
    OUT PMYD_STATE_DUMP pStateDumpInfo
);
 
 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - interface to be modified (MYD_HOST_SIDE or MYD_LINE_SIDE)
    laneOffset - 0..3 for lanes 0-3
    stateDumpOptions - various state dump options; 0:default is all
 
 Outputs:
    pStateDumpInfo - retrieves the info in the MYD_STATE_DUMP structure. All the 
          Rx state dump info will be displayed in the logging output. See  
          notes/warnings below for logging output 
 
 Returns:
    MYD_OK - if successfully retrieve dump info
    MYD_FAIL - otherwise returns MYD_FAIL
 
 Description:
    This function retrieves all the useful state information on a provided lane. 
    Information includes the device structure, temperature, voltage, versions, 
    mode selection, link info, Rx DFE, Tx FFEs coefficients, etc.. are either  
    logged in the MYD_STATE_DUMP structure or displayed in the output logging.
 
 Side effects:
    None
 
 Notes/Warnings:
    The Rx state dump and all loggings are output from the MYD_DBG_INFO macro. The
    MYD_DBG_INFO should be implemented and enabled for this mydDiagStateDump API.
    Some of these data in the state dump are used only for internal debugging and 
    would be not meaningful for end user.
    Contact customer support for more details on the state dump output. 
 
    The MYD_ENABLE_SERDES_API should be set for this API to retrieve all the info. 
    Otherwise, only a partial state dump will be retrieved.
*******************************************************************************/
MYD_STATUS mydDiagStateDump
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort, 
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U32 stateDumpOptions,
    OUT PMYD_STATE_DUMP pStateDumpInfo
);


#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MYDDIAG_H */

