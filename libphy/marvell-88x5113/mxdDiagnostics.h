/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions and global data for higher-level functions 
using MDIO access to enable test modes, loopbacks, and other diagnostic 
functions of the Marvell X5113 PHY.
********************************************************************/
#ifndef MXDDIAG_H
#define MXDDIAG_H

#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

/******************************************************************************
 MXD_STATUS mxdGetChipRevision
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    OUT MXD_DEVICE_ID *deviceId
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31

 Outputs:
    deviceId - revision of this chip, see MXD_DEVICE_ID definition for
               a list of chip revisions with different options

 Returns:
    MXD_OK if query was successful, MXD_FAIL if not

 Description:
    Determines the PHY revision and returns the value in phyRev.
    See definition of MXD_DEVICE_ID for a list of available
    devices and capabilities.

 Side effects:
    None.

 Notes/Warnings:
    None

******************************************************************************/
MXD_STATUS mxdGetChipRevision
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    OUT MXD_DEVICE_ID *deviceId
);

/******************************************************************************
 MXD_STATUS mxdGetChipFWRevision
(
    IN MXD_DEV_PTR pDev,
    OUT MXD_U16 *major,
    OUT MXD_U16 *minor
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call

 Outputs:
    major - returns the major revision number
    minor - returns the minor revision number
            Revision in <major>.<minor> format 

 Returns:
    MXD_OK if query was successful, MXD_FAIL if chip firmware is not available

 Description:
    Retrieves the chip firmware revision number. The revision is in 
    the <major>.<minor> format.  

 Side effects:
    None.

 Notes/Warnings:
    The version will return 0.0 if chip firmware is not available. Not all devices
    require the chip firmware.

******************************************************************************/
MXD_STATUS mxdGetChipFWRevision
(
    IN MXD_DEV_PTR pDev,
    OUT MXD_U16 *major,
    OUT MXD_U16 *minor
);

/******************************************************************************
 MXD_STATUS mxdGetSerdesSignalDetectAndDspLock
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16 mdioPort,     
     IN MXD_U16  host_or_line,
     IN MXD_U16 laneOffset,
     OUT MXD_U16 *signalDetect,
     OUT MXD_U16 *dspLock
 );

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31    
    host_or_line - which interface is being set:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3


 Outputs:
    signalDetect - value of serdes signal detect,  1 or 0
    dspLock - value of serdes DSP lock, 1 or 0

 Returns:
    MXD_OK if query was successful, MXD_FAIL if not

 Description:
    Reads the corresponding lane signal detect bit and returns it in
    signalDetect. Also reads the corresponding dspLock and returns it
    in dspLock.

    Signal detect is available in 3/4.F2X1.7 (X is 0...6 incrementing by 2
    corresponding to lane number 0...3).

    Dsp lock is available in 3/4.F2X1.5 (X is 0...5 incrementing by 2
    corresponding to lane number 0...3)

 Side effects:
    None.

 Notes/Warnings:
    None

******************************************************************************/
MXD_STATUS mxdGetSerdesSignalDetectAndDspLock
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,    
    IN MXD_U16  host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U16 *signalDetect,
    OUT MXD_U16 *dspLock
);


#define MXD_SHALLOW_PCS_LB    1
#define MXD_DEEP_PCS_LB       2
#define MXD_DEEP_PMA_LB       3
#define MXD_LB_LANE_OFFSET    0x200

/*******************************************************************************
 MXD_STATUS mxdSetLineLoopback
 (
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 laneOffset,
    IN MXD_U16 loopback_type,
    IN MXD_U16 enable
 );

 Inputs:
    pDev     - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    laneOffset - 0..3 for lanes 0-3
    loopback_type - MXD_SHALLOW_PCS_LB, MXD_DEEP_PCS_LB, MXD_DEEP_PMA_LB
    enable   - MXD_ENABLE/MXD_DISABLE

 Outputs:
    None

 Returns:
    MXD_OK or MXD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    This function is used to Enable/Disable line side loopbacks

 Side effects:
    None

 Notes/Warnings:
    None
    
*******************************************************************************/
MXD_STATUS mxdSetLineLoopback
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 laneOffset,
    IN MXD_U16 loopback_type,
    IN MXD_U16 enable
);

/*******************************************************************************
 MXD_STATUS mxdSetHostLoopback
 (
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 laneOffset,
    IN MXD_U16 loopback_type,
    IN MXD_U16 enable
 );

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    laneOffset - 0..3 for lanes 0-3
    loopback_type - MXD_SHALLOW_PCS_LB, MXD_DEEP_PCS_LB, MXD_DEEP_PMA_LB
    enable - MXD_ENABLE/MXD_DISABLE

 Outputs:
    None

 Returns:
    MXD_OK or MXD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    This function is used to Enable/Disable host side loopbacks

 Side effects:
    None
    
 Notes/Warnings:
    None
    
*******************************************************************************/
MXD_STATUS mxdSetHostLoopback
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 laneOffset,
    IN MXD_U16 loopback_type,
    IN MXD_U16 enable
);

/* possible values for pktPatternControl */
#define PACKET_GEN_40G_OFFSET      0xF10
#define PACKET_GEN_25G_OFFSET     (0xF10+0x1000)
#define PACKET_GEN_1G_OFFSET      (0xF10+0x2000)

#define MXD_PKT_NO_MASK            0  /* payload sent without change */
#define MXD_PKT_INV_SKIP_WRD       2  /* inverts every other word  */
#define MXD_PKT_2INV_2NOT          3  /* two inverted two not inverted */
#define MXD_PKT_LFT_SHFT_BYTE      4  /* left shift by byte */
#define MXD_PKT_RHT_SHFT_BYTE      5  /* right shift by byte */
#define MXD_PKT_LFT_SHFT_WRD       6  /* left shift by word */
#define MXD_PKT_RHT_SHFT_WRD       7  /* right shift by word */
#define MXD_PKT_INC_BYTE           8  /* increment by byte */
#define MXD_PKT_DEC_BYTE           9  /* decrement by byte */
#define MXD_PKT_RANDOM_BYTE       10  /* pseudo-random byte */
#define MXD_PKT_RANDOM_WORD       11  /* pseudo-random word */

/* possible values for frameLengthControl */
#define MXD_PKT_RAND_LEN0          0 /* rand len 64 bytes - 1518 bytes */
#define MXD_PKT_RAND_LEN1          1 /* rand len 64 bytes - 0xFFF bytes */
#define MXD_PKT_RAND_LEN2          2 /* rand len 64 bytes - 0x1FFF bytes */
#define MXD_PKT_RAND_LEN3          3 /* rand len 64 bytes - 0x3FFF bytes */
#define MXD_PKT_RAND_LEN4          4 /* rand len 64 bytes - 0x7FFF bytes */
#define MXD_PKT_RAND_LEN5          5 /* rand len 64 bytes - 0xFFFF bytes */
/* 6 and 7 are reserved/undefined */
/* values 8 and greater are the exact length of the frame in bytes up to 0xFFFF */

/******************************************************************************
 MXD_STATUS mxdConfigurePktGeneratorChecker
 (
     IN MXD_DEV_PTR devPtr,
     IN MXD_U16  mdioPort,
     IN MXD_U16  host_or_line,
     IN MXD_U16  laneOffset,
     IN MXD_BOOL readToClear,
     IN MXD_BOOL dontuseSFDinChecker,
     IN MXD_U16  pktPatternControl,
     IN MXD_BOOL generateCRCoff,
     IN MXD_U32  initialPayload,
     IN MXD_U16  frameLengthControl,
     IN MXD_U16  numPktsToSend,
     IN MXD_BOOL randomIPG,
     IN MXD_U16  ipgDuration
 );

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being checked:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3. For 40G and above, use 0.
    readToClear - MXD_TRUE if the desired behavior is that when the
                  counters are read, they are reset. MXD_FALSE if the
                  desired behavior is that they must be explicitly cleared
                  by mxdPktGeneratorCounterReset() and reading
                  them just returns the current value without clearing them.
    dontuseSFDinChecker - MXD_TRUE indicates to start CRC checking after the
                      first 8 bytes in the packet, MXD_FALSE indicates
                      to look for SFD before starting CRC checking
    pktPatternControl - controls the generation of the payload. One of the
                        following:
                            MXD_PKT_NO_MASK
                            MXD_PKT_INV_SKIP_WRD
                            MXD_PKT_2INV_2NOT
                            MXD_PKT_LFT_SHFT_BYTE
                            MXD_PKT_RHT_SHFT_BYTE
                            MXD_PKT_LFT_SHFT_WRD
                            MXD_PKT_RHT_SHFT_WRD
                            MXD_PKT_INC_BYTE
                            MXD_PKT_DEC_BYTE
                            MXD_PKT_RANDOM_BYTE
                            MXD_PKT_RANDOM_WORD
    generateCRCoff - MXD_TRUE turns CRC generation off, MXD_FALSE turns
                     CRC generation on
    initialPayload - start of payload value. Format is from MS bit to
                     LS bit: BYTE3:BYTE2:BYTE1:BYTE0, bit 31 to bit 0,
                     left to right
    frameLengthControl - controls the length of the frame in bytes.
                         values 0...5 (see above) pick various random lengths
                         from 64 to a different stop value. 6/7 is undefined
                         and values 8 and greater are the exact frame length
                         in bytes. See definitions above MXD_PKT_RAND_LEN0-5.
    numPktsToSend - 0 stops generation, 0x001-0xFFFE sends exactly that number
                    of packets then stops. 0xFFFF sends continuously.
    randomIPG - MXD_TRUE uses a random IPG from 5 bytes to value specified
                in ipgDuration. MXD_FALSE uses fixed IPG as specified in
                ipgDuration.
    ipgDuration - Meaning depends on randomIPG (see above). Each bit
                  equals 4 bytes of idle. Valid range is 0...0x7FFF.

 Outputs:
    None

 Returns:
    MXD_OK or MXD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    This function is used to configure the packet generator/checker.

 Side effects:
    None

 Notes/Warnings:
    Call mxdEnablePktGeneratorChecker() to enable/start the generator/checker.

******************************************************************************/
MXD_STATUS mxdConfigurePktGeneratorChecker
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    IN MXD_BOOL readToClear,
    IN MXD_BOOL dontuseSFDinChecker,
    IN MXD_U16  pktPatternControl,
    IN MXD_BOOL generateCRCoff,
    IN MXD_U32  initialPayload,
    IN MXD_U16  frameLengthControl,
    IN MXD_U16  numPktsToSend,
    IN MXD_BOOL randomIPG,
    IN MXD_U16  ipgDuration
);

/******************************************************************************
 MXD_STATUS mxdEnablePktGeneratorChecker
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16  mdioPort,
     IN MXD_U16  host_or_line,
     IN MXD_U16  laneOffset,
     IN MXD_BOOL enableGenerator,
     IN MXD_BOOL enableChecker
 );

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being checked:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3. For 40G and above, set to 0.
    enableGenerator - MXD_TRUE starts the packet generator, MXD_FALSE
                      stops it
    enableChecker - MXD_TRUE starts the packet checker, MXD_FALSE
                    stops it

 Outputs:
    None

 Returns:
    MXD_OK or MXD_FAIL

 Description:
    This function enables/disables either the packet generator or packet checker
    (or both).

 Side effects:
    None

 Notes/Warnings:
    None

******************************************************************************/
MXD_STATUS mxdEnablePktGeneratorChecker
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    IN MXD_BOOL enableGenerator,
    IN MXD_BOOL enableChecker
);

/******************************************************************************
 MXD_STATUS mxdPktGeneratorCounterReset
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16 mdioPort,
     IN MXD_U16 host_or_line,
     IN MXD_U16  laneOffset
 );

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being checked:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3. For 40G and above, set to 0.

 Outputs:
    None

 Returns:
    MXD_OK or MXD_FAIL

 Description:
    This function explicitly clears all the counters when the packet
    generator/checker has been setup to be cleared by writing a
    bit to the control register instead of being cleared when
    the counter(s) are read.

    This function operates on the counters.

    When this function is called (and 3.F010.15/4.F010.15 is 0)
    the transmit, receive, error and link drop counters will be cleared.

 Side effects:
    None

 Notes/Warnings:
    This function assumes the generator/checker has been configured to
    be cleared by bit 3.F010.6/4.F010.6 by previously passing
    MXD_FALSE for parameter readToClear in function
    mxdConfigurePktGeneratorChecker() (thus setting bit F010.15 <= 0).

******************************************************************************/
MXD_STATUS mxdPktGeneratorCounterReset
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16  laneOffset
);

#define MXD_PKT_GET_TX  0
#define MXD_PKT_GET_RX  1
#define MXD_PKT_GET_ERR 2
/******************************************************************************
 MXD_STATUS mxdPktGeneratorGetCounter
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16  mdioPort,
     IN MXD_U16  host_or_line,
     IN MXD_U16  laneOffset,
     IN MXD_U16  whichCounter,
     OUT MXD_U64 *packetCount,
     OUT MXD_U64 *byteCount
 );

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being checked:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3. For 40G and above, set to 0.
    whichCounter - One of the following, depending on which set of counters
                   is being read:
                       MXD_PKT_GET_TX to read the generator/transmit counters
                       MXD_PKT_GET_RX to read the checker/receive counters
                       MXD_PKT_GET_ERR to read the packet error counter


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
                  MXD_PKT_GET_ERR, since error counter is a packet
                  count only.

 Returns:
    MXD_OK or MXD_FAIL

 Description:
    This function is used to read the transmit/receive/error counter for the
    packet generator/checker.

 Side effects:
    None

 Notes/Warnings:
    byteCount is always 0 for MXD_PKT_GET_ERR, since the error counter
    only counts packets.

    If packet generator/checker was configured to clear counter(s) on read,
    this function will clear the counter being read.

******************************************************************************/
MXD_STATUS mxdPktGeneratorGetCounter
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    IN MXD_U16  whichCounter,
    OUT MXD_U64 *packetCount,
    OUT MXD_U64 *byteCount
);

/************** LINE SIDE PRBS SELECTION *************************************/

/* Pattern Selection. An "I" before PRBS indicates it's an inverted pattern. */
/* Used to set 3.F1X0.3:0...3.F1X0.3:0, where X is lanes 0-3 for line side */
/* When bit values 1110b or 1111b is selected, pattern comes from the selection */
/* in 3.F1XA/3.F1XB (where X is 0...3) */
typedef enum
{
    MXD_PRBS31,   /* 0000b */
    MXD_PRBS7,    /* 0001b */
    MXD_PRBS9,    /* 0010b */    
    MXD_PRBS23,   /* 0011b */
    MXD_IPRBS31,  /* 0100b */
    MXD_IPRBS7,   /* 0101b */
    MXD_IPRBS9,   /* 0110b */
    MXD_IPRBS23,  /* 0111b */
    MXD_PRBS15,   /* 1000b */
    MXD_IPRBS15,  /* 1001b */
    MXD_PRBS58,   /* 1010b */
    MXD_IPRBS58,  /* 1011b */
    MXD_PRBS13,   /* 1100b */
    MXD_IPRBS13,  /* 1101b */
    MXD_JP03AB,   /* 1110b, pattern selected from 3.F1XA and 3.F1XB */
    MXD_GEN_TX    /* 1111b, pattern selected from 3.F1XA and 3.F1XB */
} MXD_PRBS_SELECTOR_TYPE;

/* When PRBS selector is set to MXD_LINE_JP03AB or MXD_LINE_GEN_TX, one of the */
/* following must be further selected to pick the actual pattern. */
/* These selections are used to pick an initialization value for */
/* 3.F1XA...3.F1XA and 3.F1XB...3.F1XB, where X is 0...3 */
typedef enum
{
    MXD_PRBS_NONE,       /* goes with all other options */
    MXD_JP03A,           /* goes with MXD_LINE_JP03AB to select JP03A */
    MXD_JP03B,           /* goes with MXD_LINE_JP03AB to select JP03B */
    MXD_LOW_FREQ,        /* goes with MXD_LINE_GEN_TX */
    MXD_SQUARE_WAV,      /* goes with MXD_LINE_GEN_TX */
    MXD_MIXED_FREQ       /* goes with MXD_LINE_GEN_TX */
} MXD_PATTERN_AB_SELECTOR_TYPE;

typedef enum
{
    MXD_ALL_ZERO,        /* all 0's pattern */
    MXD_ALL_ONE,         /* all 1's pattern */
    MXD_SQUARE_WAV_1,    /* square wave #1 pattern */
    MXD_SQUARE_WAV_5,    /* square wave #5 pattern */
    MXD_SQUARE_WAV_8     /* square wave #8 pattern */
} MXD_SQUARE_WAV_PATTERN_TYPE;

/*******************************************************************************
 MXD_STATUS mxdSetLineSidePRBSPattern
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16  mdioPort,
     IN MXD_U16  laneOffset,
     IN MXD_PRBS_SELECTOR_TYPE pattSel,
     IN MXD_PATTERN_AB_SELECTOR_TYPE pattSubSel,
     IN MXD_SQUARE_WAV_PATTERN_TYPE squarePattern
 );

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    laneOffset - 0..3 for lanes 0-3. For 40G and above, set to 0.
    pattSel - one of the following:
         MXD_PRBS31
         MXD_PRBS7
         MXD_PRBS9
         MXD_PRBS23
         MXD_IPRBS31
         MXD_IPRBS7
         MXD_IPRBS9
         MXD_IPRBS23
         MXD_PRBS15
         MXD_IPRBS15
         MXD_PRBS58
         MXD_IPRBS58
         MXD_PRBS13
         MXD_IPRBS13
         MXD_JP03AB
         MXD_GEN_TX

    pattSubSel - valid only if pattSel is either MXD_JP03AB or MXD_GEN_TX 
                 MXD_JP03AB use: MXD_JP03A or MXD_JP03B
                 MXD_GEN_TX use: MXD_LOW_FREQ or MXD_SQUARE_WAV or MXD_MIXED_FREQ  

    squarePattern - valid only if pattSubSel == MXD_GEN_TX
                 MXD_ALL_ZERO     
                 MXD_ALL_ONE      
                 MXD_SQUARE_WAV_1 
                 MXD_SQUARE_WAV_5 
                 MXD_SQUARE_WAV_8

 Outputs:
    None

 Returns:
    MXD_OK or MXD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    This function selects the type of PRBS pattern desired for the individual lane 
    offset on the line side. Some pattern selections require further input selection 
    for pattSubSel and squarePattern.  Refer to the inputs description for the list of 
    selections.

 Side effects:
    None
    
 Notes/Warnings:
    None
    
*******************************************************************************/
MXD_STATUS mxdSetLineSidePRBSPattern
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  laneOffset,
    IN MXD_PRBS_SELECTOR_TYPE pattSel,
    IN MXD_PATTERN_AB_SELECTOR_TYPE pattSubSel,
    IN MXD_SQUARE_WAV_PATTERN_TYPE squarePattern
);

/*******************************************************************************
 MXD_STATUS mxdSetHostSidePRBSPattern
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16  mdioPort,
     IN MXD_U16  laneOffset,
     IN MXD_PRBS_SELECTOR_TYPE pattSel,
     IN MXD_PATTERN_AB_SELECTOR_TYPE pattSubSel,
     IN MXD_SQUARE_WAV_PATTERN_TYPE squarePattern
 );

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    laneOffset - 0..3 for lanes 0-3. For 40G and above, set to 0. 
    pattSel - one of the following:
                 MXD_PRBS31
                 MXD_PRBS7
                 MXD_PRBS9
                 MXD_PRBS23
                 MXD_IPRBS31
                 MXD_IPRBS7
                 MXD_IPRBS9
                 MXD_IPRBS23
                 MXD_PRBS15
                 MXD_IPRBS15
                 MXD_PRBS58
                 MXD_IPRBS58
                 MXD_PRBS13
                 MXD_IPRBS13
                 MXD_JP03AB
                 MXD_GEN_TX

    pattSubSel - valid only if pattSel is either MXD_JP03AB or MXD_GEN_TX 
                 MXD_JP03AB use: MXD_JP03A or MXD_JP03B
                 MXD_GEN_TX use: MXD_LOW_FREQ or MXD_SQUARE_WAV or MXD_MIXED_FREQ  

    squarePattern - valid only if pattSubSel == MXD_GEN_TX
                 MXD_ALL_ZERO     
                 MXD_ALL_ONE      
                 MXD_SQUARE_WAV_1 
                 MXD_SQUARE_WAV_5 
                 MXD_SQUARE_WAV_8

 Outputs:
    None

 Returns:
    MXD_OK or MXD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    This function is used to select the type of PRBS pattern desired for the individual 
    lane offset on the host side. Some pattern selections require further input selection 
    for pattSubSel and squarePattern.  Refer to the inputs description for the list of 
    selections.

 Side effects:
    None
    
 Notes/Warnings:
    None
    
*******************************************************************************/
MXD_STATUS mxdSetHostSidePRBSPattern
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  laneOffset,
    IN MXD_PRBS_SELECTOR_TYPE pattSel,
    IN MXD_PATTERN_AB_SELECTOR_TYPE pattSubSel,
    IN MXD_SQUARE_WAV_PATTERN_TYPE squarePattern
);

/************** COMMON PRBS FUNCTIONS ****************************************/
/*******************************************************************************
MXD_STATUS mxdSetSquareWave
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    IN MXD_SQUARE_WAV_PATTERN_TYPE pattern
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31    
    host_or_line - which interface is being set:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3. 
    pattern - uses MXD_SQUARE_WAV_PATTERN_TYPE enum type
                MXD_ALL_ZERO     -  all 0's pattern 
                MXD_ALL_ONE      -  all 1's pattern 
                MXD_SQUARE_WAV_1 -  square wave #1 pattern 
                MXD_SQUARE_WAV_5 -  square wave #5 pattern 
                MXD_SQUARE_WAV_8 -  square wave #8 pattern 

 Outputs:
    None

 Returns:
    MXD_OK or MXD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    This function generates the patterns based on the MXD_SQUARE_WAV_PATTERN_TYPE 
    pattern input on one of the 8 lanes. 

 Side effects:
    None
   
 Notes/Warnings:
    The channel line rate must have previously been setup by setting the 
    portMode before starting the transmitter.
*******************************************************************************/
MXD_STATUS mxdSetSquareWave
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    IN MXD_SQUARE_WAV_PATTERN_TYPE  pattern
);

/*******************************************************************************
 MXD_STATUS mxdSetPRBSEnableTxRx
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16  mdioPort,     
     IN MXD_U16  host_or_line,
     IN MXD_U16  laneOffset,
     IN MXD_U16  txEnable,
     IN MXD_U16  rxEnable
 );
 
 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31    
    host_or_line - which interface is being set:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3. For 40G and above, set to 0.
    txEnable - MXD_ENABLE or MXD_DISABLE to start or stop the transmit
    rxEnable - MXD_ENABLE or MXD_DISABLE to start or stop the receiver

 Outputs:
    None

 Returns:
    MXD_OK or MXD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    This function is used to start or stop the PRBS transmit and/or 
    receiver.

 Side effects:
    None
   
 Notes/Warnings:
    The channel line rate must have previously been setup by setting the 
    portMode before starting the transmitter.
   
*******************************************************************************/
MXD_STATUS mxdSetPRBSEnableTxRx
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,    
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    IN MXD_U16  txEnable,
    IN MXD_U16  rxEnable
);

/*******************************************************************************
 MXD_STATUS mxdPRBSCounterReset
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16  mdioPort,
     IN MXD_U16  host_or_line,    
     IN MXD_U16  laneOffset
 );
 
 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3. For 40G and above, set to 0.

 Outputs:
    None

 Returns:
    MXD_OK or MXD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    This function is used to reset the counters when the PRBS has been
    setup for manual clearing instead of clear-on-read. Default
    is to use manual clearing. Call mxdSetPRBSEnableClearOnRead() to
    enable clearing the counters when reading the registers.

 Side effects:
    None
   
 Notes/Warnings:
    Assumes the PRBS has not been setup for clear-on-read.
   
*******************************************************************************/
MXD_STATUS mxdPRBSCounterReset
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,    
    IN MXD_U16  host_or_line,    
    IN MXD_U16  laneOffset
);

/*******************************************************************************
 MXD_STATUS mxdSetPRBSWaitForLock
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16  mdioPort,    
     IN MXD_U16  host_or_line,    
     IN MXD_U16  laneOffset,
     IN MXD_U16  disableWaitforLock
 );
 
 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - port number, 0-31    
    host_or_line - which interface is being set:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3
    disableWaitforLock - 1 counts PRBS before locking, 0 waits
        for locking before counting

 Outputs:
    None

 Returns:
    MXD_OK or MXD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    Configures PRBS to wait for locking before counting, or to wait for
    locking before counting.

 Side effects:
    None
   
 Notes/Warnings:
    Should be called before starting the receiver.
   
*******************************************************************************/
MXD_STATUS mxdSetPRBSWaitForLock
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,    
    IN MXD_U16  host_or_line,    
    IN MXD_U16  laneOffset,
    IN MXD_U16  disableWaitforLock
);

/*******************************************************************************
 MXD_STATUS mxdGetPRBSWaitForLock
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16  mdioPort,    
     IN MXD_U16  host_or_line,    
     IN MXD_U16  laneOffset,
     OUT MXD_U16 *disableWaitforLock
 );
 
 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - port number, 0-31    
    host_or_line - which interface is being set:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3

 Outputs:
    disableWaitforLock - 1 counts PRBS before locking, 0 waits
        for locking before counting

 Returns:
    MXD_OK or MXD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    Returns configuration for PRBS whether it is set to wait for locking
    or not before counting.

 Side effects:
    None
   
 Notes/Warnings:
    None
   
*******************************************************************************/
MXD_STATUS mxdGetPRBSWaitForLock
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,    
    IN MXD_U16  host_or_line,    
    IN MXD_U16  laneOffset,
    OUT MXD_U16 *disableWaitforLock
);

/*******************************************************************************
 MXD_STATUS mxdSetPRBSClearOnRead
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16  mdioPort,    
     IN MXD_U16  host_or_line,    
     IN MXD_U16  laneOffset,
     IN MXD_U16  enableReadClear
 );
 
 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - port number, 0-31
    host_or_line - which interface is being set:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3
    enableReadClear - 1 enables clear-on-read, 0 enables manual clear 
        (by setting register bit).

 Outputs:
    None

 Returns:
    MXD_OK or MXD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    The default for the PRBS counters is to be cleared manually by 
    calling mxdPRBSCounterReset(). This configures either to read-clear,or
    manual clear (by setting a register bit).

 Side effects:
    None
   
 Notes/Warnings:
    Should be called before starting the receiver.
   
*******************************************************************************/
MXD_STATUS mxdSetPRBSClearOnRead
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,    
    IN MXD_U16  host_or_line,    
    IN MXD_U16  laneOffset,
    IN MXD_U16  enableReadClear
);


/*******************************************************************************
 MXD_STATUS mxdGetPRBSClearOnRead
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16  mdioPort,    
     IN MXD_U16  host_or_line,    
     IN MXD_U16  laneOffset,
     OUT MXD_U16  *enableReadClear
 );
 
 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - port number, 0-31
    host_or_line - which interface is being set:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3

 Outputs:
    enableReadClear - 1 clear-on-read enabled, 0 manual clear is enabled

 Returns:
    MXD_OK or MXD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    Checks whether the PRBS is configured to clear-on-read (1) or manual
    cleared (0).

 Side effects:
    None
   
 Notes/Warnings:
    None
   
*******************************************************************************/
MXD_STATUS mxdGetPRBSClearOnRead
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,    
    IN MXD_U16  host_or_line,    
    IN MXD_U16  laneOffset,
    OUT MXD_U16  *enableReadClear
);

/*******************************************************************************
 MXD_STATUS mxdGetPRBSLocked
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16  mdioPort,
     IN MXD_U16  host_or_line,
     IN MXD_U16  laneOffset,
     OUT MXD_BOOL *prbsLocked
 );
 
 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3

 Outputs:
    prbsLocked - MXD_TRUE if the PRBS receiver is locked, MXD_FALSE otherwise

 Returns:
    MXD_OK or MXD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    Returns the indicator if the PRBS receiver is locked or not.

 Side effects:
    None
   
 Notes/Warnings:
    Should be called after starting the receiver.
   
*******************************************************************************/
MXD_STATUS mxdGetPRBSLocked
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_BOOL *prbsLocked
);

/*******************************************************************************
 MXD_STATUS mxdGetPRBSCounts
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16  mdioPort,
     IN MXD_U16  host_or_line,
     IN MXD_U16  laneOffset,
     OUT MXD_U64 *txBitCount,
     OUT MXD_U64 *rxBitCount,
     OUT MXD_U64 *rxBitErrorCount
 );
 
 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3

 Outputs:
    txBitCount - number of bits transmitted
    rxBitCount - number of bits received
    rxBitErrorCount - number of bits in error

 Returns:
    MXD_OK or MXD_FAIL if I/O error or bad parameter passed in (out of range)

 Description:
    Returns the 48-bit results in the output parameters above. If the PRBS
    control has been set to clear-on-read, the registers will clear. If
    not, they must be cleared manually by calling mxdPRBSCounterReset()

 Side effects:
    None
   
 Notes/Warnings:
    None
   
*******************************************************************************/
MXD_STATUS mxdGetPRBSCounts
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,    
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U64 *txBitCount,
    OUT MXD_U64 *rxBitCount,
    OUT MXD_U64 *rxBitErrorCount
);


/*******************************************************************************
MXD_STATUS mxdSetTxPolarity
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,     
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_U16 polarity,
    IN MXD_U16 swReset
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - interface to be modified (MXD_HOST_SIDE or MXD_LINE_SIDE)
    laneOffset - 0..3 for lanes 0-3
    polarity - 1 to invert Tx polarity, 0 to use normal polarity.
    swReset - 1:issue s/w reset to apply set polarity change; 0:s/w reset not issue
    
 Outputs:
    None

 Returns:
    MXD_OK - if set Tx polarity is successfully issued
    MXD_FAIL - otherwise returns MXD_FAIL

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
MXD_STATUS mxdSetTxPolarity
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,     
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_U16 polarity,
    IN MXD_U16 swReset
);

/*******************************************************************************
MXD_STATUS mxdGetTxPolarity
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,     
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U16 *polarity
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - interface to be modified (MXD_HOST_SIDE or MXD_LINE_SIDE)
    laneOffset - 0..3 for lanes 0-3
    
 Outputs:
    polarity - 1:inverted Tx polarity, 0:normal polarity.

 Returns:
    MXD_OK - if Tx polarity is successfully read
    MXD_FAIL - otherwise returns MXD_FAIL

 Description:
    This function reads the Tx polarity with the given input parameters. 

 Side effects:
    None

 Notes/Warnings:
    The link will be down if the Tx and Rx polarities are mismatched. 
*******************************************************************************/
MXD_STATUS mxdGetTxPolarity
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,     
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U16 *polarity
);

/*******************************************************************************
MXD_STATUS mxdSetRxPolarity
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,     
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_U16 polarity,
    IN MXD_U16 swReset
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - interface to be modified (MXD_HOST_SIDE or MXD_LINE_SIDE)
    laneOffset - 0..3 for lanes 0-3
    polarity - 1 to invert Rx polarity, 0 to use normal polarity.
    swReset - 1:issue s/w reset to apply set polarity change; 0:s/w reset not issue
    
 Outputs:
    None

 Returns:
    MXD_OK - if set Rx polarity is successfully issued
    MXD_FAIL - otherwise returns MXD_FAIL

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
MXD_STATUS mxdSetRxPolarity
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,     
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_U16 polarity,
    IN MXD_U16 swReset
);

/*******************************************************************************
MXD_STATUS mxdGetRxPolarity
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,     
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U16 *polarity
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - interface to be modified (MXD_HOST_SIDE or MXD_LINE_SIDE)
    laneOffset - 0..3 for lanes 0-3
    
 Outputs:
    polarity - 1:inverted Rx polarity, 0:normal polarity.

 Returns:
    MXD_OK - if Rx polarity is successfully read
    MXD_FAIL - otherwise returns MXD_FAIL

 Description:
    This function reads the Rx polarity with the given input parameters. 

 Side effects:
    None

 Notes/Warnings:
    The link will be down if the Tx and Rx polarities are mismatched. 
*******************************************************************************/
MXD_STATUS mxdGetRxPolarity
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,     
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U16 *polarity
);

/*******************************************************************************
MXD_STATUS mxdSetTxFFE
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,     
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_16 preCursor,
    IN MXD_16 attenuation,
    IN MXD_16 postCursor,
    IN MXD_U16 swReset
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - interface to be modified (MXD_HOST_SIDE or MXD_LINE_SIDE)
    laneOffset - 0..3 for lanes 0-3

    The recommended Tx FFE ranges are as follows: 
    preCursor   - Pre-cursor setting range [0 to 15] 
    attenuation - Attenuator setting range [0 to 23]
    postCursor  - Post-cursor setting [0 to 15]

    The device can support the Tx FFE ranges below but may not apply to most
    environment. These extended ranges may be used for testing and validation.
    preCursor   - Pre-cursor setting range [-7 to 15]
    attenuation - Attenuator setting range [0 to 31]
    postCursor  - Post-cursor setting [-31 to 31]

    swReset - 1:issue s/w reset to apply set Tx FFE change; 0:s/w reset not issue
    
 Outputs:
    None

 Returns:
    MXD_OK - if set Tx FFE is successfully issued
    MXD_FAIL - otherwise returns MXD_FAIL

 Description:
    This function set the Tx FFE with the given input parameters. To change 
    the Tx FFE on a given lane, provide the preCursor, attenuation and postCursor. 
    with the reset enabled bit set(swReset:1). The reset is issued to the entire 
    host or line on a MDIO port.  

 Side effects:
    None

 Notes/Warnings:
    None
*******************************************************************************/
MXD_STATUS mxdSetTxFFE
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,     
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_16 preCursor,
    IN MXD_16 attenuation,
    IN MXD_16 postCursor,
    IN MXD_U16 swReset
);

/*******************************************************************************
MXD_STATUS mxdGetTxFFE
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,     
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_16 *preCursor,
    OUT MXD_16 *attenuation,
    OUT MXD_16 *postCursor
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - interface to be modified (MXD_HOST_SIDE or MXD_LINE_SIDE)
    laneOffset - 0..3 for lanes 0-3
    
 Outputs:
    preCursor   - Pre-cursor setting range [-7 to 15] 
    attenuation - Attenuator setting range [0 to 31]
    postCursor  - Post-cursor setting [-31 to 31]

 Returns:
    MXD_OK - if read Tx FFE is successfully issued
    MXD_FAIL - otherwise returns MXD_FAIL

 Description:
    This function reads the Tx FFE with the given input parameters. 
    Refers to the mxdSetTxFFE API for the setting ranges.

 Side effects:
    None

 Notes/Warnings:
    The recommended Tx FFE ranges are as follows: 
    preCursor   - Pre-cursor setting range [0 to 15] 
    attenuation - Attenuator setting range [0 to 23]
    postCursor  - Post-cursor setting [0 to 15]

    The device can support the Tx FFE ranges below but may not apply to most
    environment. These extended ranges may be used for testings and validations.
    preCursor   - Pre-cursor setting range [-7 to 15]
    attenuation - Attenuator setting range [0 to 31]
    postCursor  - Post-cursor setting [-31 to 31]

 *******************************************************************************/
MXD_STATUS mxdGetTxFFE
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,     
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_16 *preCursor,
    OUT MXD_16 *attenuation,
    OUT MXD_16 *postCursor
);


#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MXDDIAG_H */
