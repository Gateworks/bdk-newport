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
* @mcdDiagnostics.h
*
* @brief This file contains functions and global data for
* higher-level functions using MDIO access to enable test modes,
* loopbacks, and other diagnostic functions of the Marvell PHY MCD driver
* PHY.
********************************************************************/
#ifndef MCDDIAG_H
#define MCDDIAG_H

#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

/******************************************************************************
MCD_STATUS mcdGetChipRevision
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    OUT MCD_DEVICE_ID *deviceId
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31

 Outputs:
    deviceId - revision of this chip, see MCD_DEVICE_ID definition for
               a list of chip revisions with different options

 Returns:
    MCD_OK if query was successful, MCD_FAIL if not

 Description:
     Determines the PHY revision and returns the value in phyRev.
     See definition of MCD_DEVICE_ID for a list of available
     devices and capabilities.

 Side effects:
    None.

 Notes/Warnings:
    None

******************************************************************************/
MCD_STATUS mcdGetChipRevision
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    OUT MCD_DEVICE_ID *deviceId
);

/******************************************************************************
 MCD_STATUS mcdGetChipFWRevision
(
    IN MCD_DEV_PTR pDev,
    OUT MCD_U16 *major,
    OUT MCD_U16 *minor
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call

 Outputs:
    major - returns the major revision number
    minor - returns the minor revision number
            Revision in <major>.<minor> format

 Returns:
    MCD_OK if query was successful, MCD_FAIL if not

 Description:
    Retrieves the chip firmware revision number. The revision is in
    the <major>.<minor> format.

 Side effects:
    None.

 Notes/Warnings:
    None

******************************************************************************/
MCD_STATUS mcdGetChipFWRevision
(
    IN MCD_DEV_PTR pDev,
    OUT MCD_U16 *major,
    OUT MCD_U16 *minor
);

/******************************************************************************
 MCD_STATUS mcdCheckChipCapablities
(
    IN MCD_DEV_PTR pDev,
    IN MCD_OP_MODE portMode
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    portMode - operational mode

 Outputs:
    none

 Returns:
    MCD_OK if portMode is supported, otherwise, returns MCD_FAIL

 Description:
    Checks the chip capablities with the provided port mode selection. If the
    mode selection is not supported, it will return a MCD_FAIL status. Otherwise,
    a MCD_OK status will be returned.

 Side effects:
    None.

 Notes/Warnings:
    None

******************************************************************************/
MCD_STATUS mcdCheckChipCapablities
(
    IN MCD_DEV_PTR pDev,
    IN MCD_OP_MODE portMode
);

/******************************************************************************
 MCD_STATUS mcdGetSerdesSignalDetectAndDspLock
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 mdioPort,
     IN MCD_U16  host_or_line,
     IN MCD_U16 laneOffset,
     OUT MCD_U16 *signalDetect,
     OUT MCD_U16 *dspLock
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - MDIO port address, 0-7
    host_or_line - which interface is being set:
                   MCD_HOST_SIDE
                   MCD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3


 Outputs:
    signalDetect - value of serdes signal detect,  1 or 0
    dspLock - value of serdes DSP lock, 1 or 0

 Returns:
    MCD_OK if query was successful, MCD_FAIL if not

 Description:
    Reads the corresponding lane signal detect bit and returns it in
    signalDetect. Also reads the corresponding dspLock and returns it
    in dspLock.

    Signal detect is "Serdes Line Signal OK" field.

    Dsp lock is "Channel 0 Link is Up" field.
    See "UMAC/Slice %m/umac3gbsx4/glbl/livelnkstat0"

 Side effects:
    None.

 Notes/Warnings:
    None

******************************************************************************/
MCD_STATUS mcdGetSerdesSignalDetectAndDspLock
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_U16 laneOffset,
    OUT MCD_U16 *signalDetect,
    OUT MCD_U16 *dspLock
);



/*#define MCD_SHALLOW_PCS_LB    1  not supported */
#define MCD_DEEP_PCS_LB       2
#define MCD_DEEP_PMA_LB       3

/*******************************************************************************
 MCD_STATUS mcdSetLineLoopback
 (
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 loopback_type,
    IN MCD_U16 enable
 );

 Inputs:
    pDev     - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - MDIO port address, 0-7
    loopback_type - MCD_SHALLOW_PCS_LB, MCD_DEEP_PCS_LB
    enable   - MCD_ENABLE. MCD_DISABLE

 Outputs:
    None

 Returns:
    MCD_OK or MCD_FAIL if io error or bad parameter passed in (out of range)

 Description:
    This function is used to Enable/Disable line side loopbacks

 Side effects:
    None

 Notes/Warnings:
    None

*******************************************************************************/
MCD_STATUS mcdSetLineLoopback
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 loopback_type,
    IN MCD_U16 enable
);

/*******************************************************************************
 MCD_STATUS mcdSetHostLoopback
 (
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 loopback_type,
    IN MCD_U16 enable
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - MDIO port address, 0-7
    loopback_type - MCD_SHALLOW_PCS_LB,MCD_DEEP_PCS_LB
    enable - MCD_ENABLE. MCD_DISABLE

 Outputs:
    None

 Returns:
    MCD_OK or MCD_FAIL if io error or bad parameter passed in (out of range)

 Description:
    This function is used to Enable/Disable host side loopbacks

 Side effects:
    None

 Notes/Warnings:
    None

*******************************************************************************/
MCD_STATUS mcdSetHostLoopback
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 loopback_type,
    IN MCD_U16 enable
);

/* possible values for pktPatternControl */
#define MCD_PKT_NO_MASK            0  /* payload sent without change */
#define MCD_PKT_INV_SKIP_WRD       2  /* inverts every other word  */
#define MCD_PKT_2INV_2NOT          3  /* two inverted two not inverted */
#define MCD_PKT_LFT_SHFT_BYTE      4  /* left shift by byte */
#define MCD_PKT_RHT_SHFT_BYTE      5  /* right shift by byte */
#define MCD_PKT_LFT_SHFT_WRD       6  /* left shift by word */
#define MCD_PKT_RHT_SHFT_WRD       7  /* right shift by word */
#define MCD_PKT_INC_BYTE           8  /* increment by byte */
#define MCD_PKT_DEC_BYTE           9  /* decrement by byte */
#define MCD_PKT_RANDOM_BYTE       10  /* pseudo-random byte */
#define MCD_PKT_RANDOM_WORD       11  /* pseudo-random word */

/* possible values for frameLengthControl */
#define MCD_PKT_RAND_LEN0          0 /* rand len 64 bytes - 1518 bytes */
#define MCD_PKT_RAND_LEN1          1 /* rand len 64 bytes - 0xFFF bytes */
#define MCD_PKT_RAND_LEN2          2 /* rand len 64 bytes - 0x1FFF bytes */
#define MCD_PKT_RAND_LEN3          3 /* rand len 64 bytes - 0x3FFF bytes */
#define MCD_PKT_RAND_LEN4          4 /* rand len 64 bytes - 0x7FFF bytes */
#define MCD_PKT_RAND_LEN5          5 /* rand len 64 bytes - 0xFFFF bytes */
/* 6 and 7 are reserved/undefined */
/* values 8 and greater are the exact length of the frame in bytes up to 0xFFFF */

/******************************************************************************
 MCD_STATUS mcdConfigurePktGeneratorChecker
 (
     IN MCD_DEV_PTR devPtr,
     IN MCD_U16  mdioPort,
     IN MCD_U16  host_or_line,
     IN MCD_BOOL readToClear,
     IN MCD_BOOL dontuseSFDinChecker,
     IN MCD_U16  pktPatternControl,
     IN MCD_BOOL generateCRCoff,
     IN MCD_U32  initialPayload,
     IN MCD_U16  frameLengthControl,
     IN MCD_U16  numPktsToSend,
     IN MCD_BOOL randomIPG,
     IN MCD_U16  ipgDuration
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being checked:
                   MCD_HOST_SIDE
                   MCD_LINE_SIDE
    readToClear - MCD_TRUE if the desired behavior is that when the
                  counters are read, they are reset. MCD_FALSE if the
                  desired behavior is that they must be explicitly cleared
                  by mcdPktGeneratorCounterReset() and reading
                  them just returns the current value without clearing them.
    dontuseSFDinChecker - MCD_TRUE indicates to start CRC checking after the
                      first 8 bytes in the packet, MCD_FALSE indicates
                      to look for SFD before starting CRC checking
    pktPatternControl - controls the generation of the payload. One of the
                        following:
                            MCD_PKT_NO_MASK
                            MCD_PKT_INV_SKIP_WRD
                            MCD_PKT_2INV_2NOT
                            MCD_PKT_LFT_SHFT_BYTE
                            MCD_PKT_RHT_SHFT_BYTE
                            MCD_PKT_LFT_SHFT_WRD
                            MCD_PKT_RHT_SHFT_WRD
                            MCD_PKT_INC_BYTE
                            MCD_PKT_DEC_BYTE
                            MCD_PKT_RANDOM_BYTE
                            MCD_PKT_RANDOM_WORD
    generateCRCoff - MCD_TRUE turns CRC generation off, MCD_FALSE turns
                     CRC generation on
    initialPayload - start of payload value. Format is from MS bit to
                     LS bit: BYTE3:BYTE2:BYTE1:BYTE0, bit 31 to bit 0,
                     left to right
    frameLengthControl - controls the length of the frame in bytes.
                         values 0...5 (see above) pick various random lengths
                         from 64 to a different stop value. 6/7 is undefined
                         and values 8 and greater are the exact frame length
                         in bytes. See definitions above MCD_PKT_RAND_LEN0-5.
    numPktsToSend - 0 stops generation, 0x001-0xFFFE sends exactly that number
                    of packets then stops. 0xFFFF sends continuously.
    randomIPG - MCD_TRUE uses a random IPG from 5 bytes to value specified
                in ipgDuration. MCD_FALSE uses fixed IPG as specified in
                ipgDuration.
    ipgDuration - Meaning depends on randomIPG (see above). Each bit
                  equals 4 bytes of idle. Valid range is 0...0x7FFF.

 Outputs:
    None

 Returns:
    MCD_OK or MCD_FAIL if io error or bad parameter passed in (out of range)

 Description:
    This function is used to configure the packet generator/checker.

 Side effects:
    None

 Notes/Warnings:
    Call mcdEnablePktGeneratorChecker() to enable/start the generator/checker.

******************************************************************************/
MCD_STATUS mcdConfigurePktGeneratorChecker
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_BOOL readToClear,
    IN MCD_BOOL dontuseSFDinChecker,
    IN MCD_U16  pktPatternControl,
    IN MCD_BOOL generateCRCoff,
    IN MCD_U32  initialPayload,
    IN MCD_U16  frameLengthControl,
    IN MCD_U16  numPktsToSend,
    IN MCD_BOOL randomIPG,
    IN MCD_U16  ipgDuration
);

/******************************************************************************
 MCD_STATUS mcdEnablePktGeneratorChecker
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16  mdioPort,
     IN MCD_U16  host_or_line,
     IN MCD_BOOL enableGenerator,
     IN MCD_BOOL enableChecker
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being checked:
                   MCD_HOST_SIDE
                   MCD_LINE_SIDE
    enableGenerator - MCD_TRUE starts the packet generator, MCD_FALSE
                      stops it
    enableChecker - MCD_TRUE starts the packet checker, MCD_FALSE
                    stops it

 Outputs:
    None

 Returns:
    MCD_OK or MCD_FAIL

 Description:
    This function enables/disables either the packet generator or packet checker
    (or both).

 Side effects:
    None

 Notes/Warnings:
    None

******************************************************************************/
MCD_STATUS mcdEnablePktGeneratorChecker
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_BOOL enableGenerator,
    IN MCD_BOOL enableChecker
);

/******************************************************************************
 MCD_STATUS mcdPktGeneratorCounterReset
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 mdioPort,
     IN MCD_U16 host_or_line
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being checked:
                   MCD_HOST_SIDE
                   MCD_LINE_SIDE

 Outputs:
    None

 Returns:
    MCD_OK or MCD_FAIL

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
    MCD_FALSE for parameter readToClear in function
    mcdConfigurePktGeneratorChecker() (thus setting bit F010.15 <= 0).

******************************************************************************/
MCD_STATUS mcdPktGeneratorCounterReset
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line
);

#define MCD_PKT_GET_TX  0
#define MCD_PKT_GET_RX  1
#define MCD_PKT_GET_ERR 2
/******************************************************************************
 MCD_STATUS mcdPktGeneratorGetCounter
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16  mdioPort,
     IN MCD_U16  host_or_line,
     IN MCD_U16  whichCounter,
     OUT MCD_U64 *packetCount,
     OUT MCD_U64 *byteCount
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being checked:
                   MCD_HOST_SIDE
                   MCD_LINE_SIDE
    whichCounter - One of the following, depending on which set of counters
                   is being read:
                       MCD_PKT_GET_TX to read the generator/transmit counters
                       MCD_PKT_GET_RX to read the checker/receive counters
                       MCD_PKT_GET_ERR to read the packet error counter


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
                  MCD_PKT_GET_ERR, since error counter is a packet
                  count only.

 Returns:
    MCD_OK or MCD_FAIL

 Description:
    This function is used to read the transmit/receive/error counter for the
    packet generator/checker.

 Side effects:
    None

 Notes/Warnings:
    byteCount is always 0 for MCD_PKT_GET_ERR, since the error counter
    only counts packets.

    If packet generator/checker was configured to clear counter(s) on read,
    this function will clear the counter being read.

******************************************************************************/
MCD_STATUS mcdPktGeneratorGetCounter
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_U16  whichCounter,
    OUT MCD_U64 *packetCount,
    OUT MCD_U64 *byteCount
);

/************** LINE SIDE PRBS SELECTION *************************************/

/* Pattern Selection. An "I" before PRBS indicates it's an inverted pattern. */
/* Used to set 3.F1X0.3:0...3.F1X0.3:0, where X is lanes 0-3 for line side */
/* When bit values 1110b or 1111b is selected, pattern comes from the selection */
/* in 3.F1XA/3.F1XB (where X is 0...3) */
typedef enum
{
    MCD_LINE_PRBS31,   /* 0000b */
    MCD_LINE_PRBS7,    /* 0001b */
    MCD_LINE_PRBS9,    /* 0010b */
    MCD_LINE_PRBS23,   /* 0011b */
    MCD_LINE_IPRBS31,  /* 0100b */
    MCD_LINE_IPRBS7,   /* 0101b */
    MCD_LINE_1PRBS5,   /* 0110b */
    MCD_LINE_IPRBS15,  /* 0111b */
    MCD_LINE_IPRBS9,   /* 1000b */
    MCD_LINE_IPRBS23,  /* 1001b */
    MCD_LINE_PRBS58,   /* 1010b */
    MCD_LINE_IPRBS58,  /* 1011b */
    MCD_LINE_PRBS13,   /* 1100b */
    MCD_LINE_IPRBS13,  /* 1101b */
    MCD_LINE_JP03AB,   /* 1110b, pattern selected from 3.F1XA and 3.F1XB */
    MCD_LINE_GEN_TX,   /* 1111b, pattern selected from 3.F1XA and 3.F1XB */
    MCD_LINE_PRBS11,
    MCD_LINE_IPRBS11,
    MCD_LINE_PRBS15
} MCD_PRBS_LINE_SELECTOR_TYPE;

/* When PRBS selector is set to MCD_LINE_JP03AB or MCD_LINE_GEN_TX, one of the */
/* following must be further selected to pick the actual pattern. */
/* These selections are used to pick an initialization value for */
/* 3.F1XA...3.F1XA and 3.F1XB...3.F1XB, where X is 0...3 */
typedef enum
{
    MCD_LINE_PRBS_NONE,       /* goes with all other options */
    MCD_LINE_JP03A,           /* goes with MCD_LINE_JP03AB to select JP03A */
    MCD_LINE_JP03B,           /* goes with MCD_LINE_JP03AB to select JP03B */
    MCD_LINE_LOW_FREQ,        /* goes with MCD_LINE_GEN_TX */
    MCD_LINE_SQUARE_WAV,      /* goes with MCD_LINE_GEN_TX */
    MCD_LINE_MIXED_FREQ       /* goes with MCD_LINE_GEN_TX */
} MCD_PATTERN_LINE_AB_SELECTOR_TYPE;

/*******************************************************************************
 MCD_STATUS mcdSetLineSidePRBSPattern
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16  mdioPort,
     IN MCD_U16  laneOffset,
     IN MCD_PRBS_LINE_SELECTOR_TYPE pattSel,
     IN MCD_PATTERN_LINE_AB_SELECTOR_TYPE pattSubSel
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    laneOffset - 0..3 for lanes 0-3
    pattSel - one of the following:
         MCD_LINE_PRBS31
         MCD_LINE_PRBS7
         MCD_LINE_PRBS9
         MCD_LINE_PRBS23
         MCD_LINE_IPRBS31
         MCD_LINE_IPRBS7
         MCD_LINE_1PRBS5
         MCD_LINE_IPRBS15
         MCD_LINE_IPRBS9
         MCD_LINE_IPRBS23
         MCD_LINE_PRBS58
         MCD_LINE_IPRBS58
         MCD_LINE_PRBS13
         MCD_LINE_IPRBS13
         MCD_LINE_JP03AB
         MCD_LINE_GEN_TX
    pattSubSeLINE_l - one of the following:
         MCD_PRBS_NONE (for MCD_LINE_PRBS31...MCD_LINE_IPRBS13)
         MCD_LINE_JP03A (one of these for MCD_LINE_JP03AB)
         MCD_LINE_JP03B
         MCD_LINE_LOW_FREQ (one of these for MCD_LINE_GEN_TX)
         MCD_LINE_SQUARE_WAV
         MCD_LINE_MIXED_FREQ

 Outputs:
    None

 Returns:
    MCD_OK or MCD_FAIL if io error or bad parameter passed in (out of range)

 Description:
    This function is used to select the type of PRBS pattern

 Side effects:
    None

 Notes/Warnings:
    None

*******************************************************************************/
MCD_STATUS mcdSetLineSidePRBSPattern
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  laneOffset,
    IN MCD_PRBS_LINE_SELECTOR_TYPE pattSel,
    IN MCD_PATTERN_LINE_AB_SELECTOR_TYPE pattSubSel
);

/************** HOST SIDE PRBS SELECTION *************************************/

/* Pattern Selection. An "I" before PRBS indicates it's an inverted pattern. */
/* Used to set 4.AX30.3:0...4.AX30.3:0, where X is 0..E for host side depending on lane */
/* as follows: */
/* Port 0 Lane 0 X = 0 */
/* Port 0 Lane 1 X = 2 */
/* Port 0 Lane 2 X = 4 */
/* Port 0 Lane 3 X = 6 */
/* Port 1 Lane 0 X = 8 */
/* Port 1 Lane 1 X = A */
/* Port 1 Lane 2 X = C */
/* Port 1 Lane 3 X = E */
typedef enum
{
    MCD_HOST_PRBS31,   /* 0000b */
    MCD_HOST_PRBS7,    /* 0001b */
    MCD_HOST_PRBS9,    /* 0010b */
    MCD_HOST_PRBS23,   /* 0011b */
    MCD_HOST_IPRBS31,  /* 0100b */
    MCD_HOST_IPRBS7,   /* 0101b */
    MCD_HOST_PRBS15,   /* 0110b */
    MCD_HOST_IPRBS15,  /* 0111b */
    MCD_HOST_IPRBS9,   /* 1000b */
    MCD_HOST_IPRBS23,  /* 1001b */
    MCD_HOST_PRBS58,   /* 1010b */
    MCD_HOST_IPRBS58,  /* 1011b */
    MCD_HOST_HI_FREQ,  /* 1100b */
    MCD_HOST_LO_FREQ,  /* 1101b */
    MCD_HOST_MX_FREQ,  /* 1110b */
    MCD_HOST_SQ_WAV,   /* 1111b*/
    MCD_HOST_PRBS11,
    MCD_HOST_IPRBS11
} MCD_PRBS_HOST_SELECTOR_TYPE;
/*******************************************************************************
 MCD_STATUS mcdSetHostSidePRBSPattern
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16  mdioPort,
     IN MCD_U16  laneOffset,
     IN MCD_PRBS_HOST_SELECTOR_TYPE pattSel
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    laneOffset - 0..3 for lanes 0-3
    pattSel - one of the following:
         MCD_HOST_PRBS31
         MCD_HOST_PRBS7
         MCD_HOST_PRBS9
         MCD_HOST_PRBS23
         MCD_HOST_IPRBS31
         MCD_HOST_IPRBS7
         MCD_HOST_PRBS15
         MCD_HOST_IPRBS15
         MCD_HOST_IPRBS9
         MCD_HOST_IPRBS23
         MCD_HOST_PRBS58
         MCD_HOST_IPRBS58
         MCD_HOST_HI_FREQ
         MCD_HOST_LO_FREQ
         MCD_HOST_MX_FREQ
         MCD_HOST_SQ_WAV
         MCD_HOST_PRBS11
         MCD_HOST_IPRBS11

 Outputs:
    None

 Returns:
    MCD_OK or MCD_FAIL if io error or bad parameter passed in (out of range)

 Description:
    This function is used to select the type of PRBS pattern

 Side effects:
    None

 Notes/Warnings:
    None

*******************************************************************************/
MCD_STATUS mcdSetHostSidePRBSPattern
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  laneOffset,
    IN MCD_PRBS_HOST_SELECTOR_TYPE pattSel
);

/************** COMMON PRBS FUNCTIONS ****************************************/

/*******************************************************************************
 MCD_STATUS mcdSetPRBSEnableTxRx
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16  mdioPort,
     IN MCD_U16  host_or_line,
     IN MCD_U16  laneOffset,
     IN MCD_U16  txEnable,
     IN MCD_U16  rxEnable
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MCD_HOST_SIDE
                   MCD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3
    txEnable - MCD_ENABLE or MCD_DISABLE to start or stop the transmit
    rxEnable - MCD_ENABLE or MCD_DISABLE to start or stop the receiver

 Outputs:
    None

 Returns:
    MCD_OK or MCD_FAIL if io error or bad parameter passed in (out of range)

 Description:
    This function is used to start or stop the PRBS transmit and/or
    receiver.

 Side effects:
    None

 Notes/Warnings:
    The channel line rate must have previously been setup by setting the
    portMode before starting the transmitter.

*******************************************************************************/
MCD_STATUS mcdSetPRBSEnableTxRx
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_U16  laneOffset,
    IN MCD_U16  txEnable,
    IN MCD_U16  rxEnable
);


/*******************************************************************************
 MCD_STATUS mcdPRBSCounterReset
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16  mdioPort,
     IN MCD_U16  host_or_line,
     IN MCD_U16  laneOffset
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MCD_HOST_SIDE
                   MCD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3

 Outputs:
    None

 Returns:
    MCD_OK or MCD_FAIL if io error or bad parameter passed in (out of range)

 Description:
    This function is used to reset the counters when the PRBS has been
    setup for manual clearing instead of clear-on-read. Default
    is to use manual clearing. Call mcdSetPRBSEnableClearOnRead() to
    enable clearing the counters when reading the registers.

 Side effects:
    None

 Notes/Warnings:
    Assumes the PRBS has not been setup for clear-on-read.

*******************************************************************************/
MCD_STATUS mcdPRBSCounterReset
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_U16  laneOffset
);


/*******************************************************************************
 MCD_STATUS mcdSetPRBSWaitForLock
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16  mdioPort,
     IN MCD_U16  host_or_line,
     IN MCD_U16  laneOffset,
     IN MCD_U16  disableWaitforLock
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - port number, 0-31
    host_or_line - which interface is being set:
                   MCD_HOST_SIDE
                   MCD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3
    disableWaitforLock - 1 counts PRBS before locking, 0 waits
        for locking before counting

 Outputs:
    None

 Returns:
    MCD_OK or MCD_FAIL if io error or bad parameter passed in (out of range)

 Description:
    Configures PRBS to wait for locking before counting, or to wait for
    locking before counting.

 Side effects:
    None

 Notes/Warnings:
    Should be called before starting the receiver.

*******************************************************************************/
MCD_STATUS mcdSetPRBSWaitForLock
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_U16  laneOffset,
    IN MCD_U16  disableWaitforLock
);


/*******************************************************************************
 MCD_STATUS mcdGetPRBSWaitForLock
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16  mdioPort,
     IN MCD_U16  host_or_line,
     IN MCD_U16  laneOffset,
     OUT MCD_U16 *disableWaitforLock
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - port number, 0-31
    host_or_line - which interface is being set:
                   MCD_HOST_SIDE
                   MCD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3

 Outputs:
    disableWaitforLock - 1 counts PRBS before locking, 0 waits
        for locking before counting

 Returns:
    MCD_OK or MCD_FAIL if io error or bad parameter passed in (out of range)

 Description:
    Returns configuration for PRBS whether it is set to wait for locking
    or not before counting.

 Side effects:
    None

 Notes/Warnings:
    None

*******************************************************************************/
MCD_STATUS mcdGetPRBSWaitForLock
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_U16  laneOffset,
    OUT MCD_U16 *disableWaitforLock
);


/*******************************************************************************
 MCD_STATUS mcdSetPRBSClearOnRead
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16  mdioPort,
     IN MCD_U16  host_or_line,
     IN MCD_U16  laneOffset,
     IN MCD_U16  enableReadClear
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - port number, 0-31
    host_or_line - which interface is being set:
                   MCD_HOST_SIDE
                   MCD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3
    enableReadClear - 1 enables clear-on-read, 0 enables manual clear
        (by setting register bit).

 Outputs:
    None

 Returns:
    MCD_OK or MCD_FAIL if io error or bad parameter passed in (out of range)

 Description:
    The default for the PRBS counters is to be cleared manually by
    calling mcdPRBSCounterReset(). This configures either to read-clear,or
    manual clear (by setting a register bit).

 Side effects:
    None

 Notes/Warnings:
    Should be called before starting the receiver.

*******************************************************************************/
MCD_STATUS mcdSetPRBSClearOnRead
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_U16  laneOffset,
    IN MCD_U16  enableReadClear
);


/*******************************************************************************
 MCD_STATUS mcdGetPRBSClearOnRead
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16  mdioPort,
     IN MCD_U16  host_or_line,
     IN MCD_U16  laneOffset,
     OUT MCD_U16  *enableReadClear
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - port number, 0-31
    host_or_line - which interface is being set:
                   MCD_HOST_SIDE
                   MCD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3

 Outputs:
    enableReadClear - 1 clear-on-read enabled, 0 manual clear is enabled

 Returns:
    MCD_OK or MCD_FAIL if io error or bad parameter passed in (out of range)

 Description:
    Checks whether the PRBS is configured to clear-on-read (1) or manual
    cleared (0).

 Side effects:
    None

 Notes/Warnings:
    None

*******************************************************************************/
MCD_STATUS mcdGetPRBSClearOnRead
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_U16  laneOffset,
    OUT MCD_U16  *enableReadClear
);


/*******************************************************************************
 MCD_STATUS mcdGetPRBSLocked
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16  mdioPort,
     IN MCD_U16  host_or_line,
     IN MCD_U16  laneOffset,
     OUT MCD_BOOL *prbsLocked
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MCD_HOST_SIDE
                   MCD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3

 Outputs:
    prbsLocked - MTD_TRUE if the PRBS receiver is locked, MTD_FALSE otherwise

 Returns:
    MCD_OK or MCD_FAIL if io error or bad parameter passed in (out of range)

 Description:
    Returns the indicator if the PRBS receiver is locked or not.

 Side effects:
    None

 Notes/Warnings:
    Should be called after starting the receiver.

*******************************************************************************/
MCD_STATUS mcdGetPRBSLocked
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_U16  laneOffset,
    OUT MCD_BOOL *prbsLocked
);

/*******************************************************************************
 MCD_STATUS mcdGetPRBSCounts
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16  mdioPort,
     IN MCD_U16  host_or_line,
     IN MCD_U16  laneOffset,
     OUT MCD_U64 *txBitCount,
     OUT MCD_U64 *rxBitCount,
     OUT MCD_U64 *rxBitErrorCount
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MCD_HOST_SIDE
                   MCD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3

 Outputs:
    txBitCount - number of bits transmitted
    rxBitCount - number of bits received
    rxBitErrorCount - number of bits in error

 Returns:
    MCD_OK or MCD_FAIL if io error or bad parameter passed in (out of range)

 Description:
    Returns the 48-bit results in the output parameters above. If the PRBS
    control has been set to clear-on-read, the registers will clear. If
    not, they must be cleared manually by calling mcdPRBSCounterReset()

 Side effects:
    None

 Notes/Warnings:
    None

*******************************************************************************/
MCD_STATUS mcdGetPRBSCounts
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16  host_or_line,
    IN MCD_U16  laneOffset,
    OUT MCD_U64 *txBitCount,
    OUT MCD_U64 *rxBitCount,
    OUT MCD_U64 *rxBitErrorCount
);

/*******************************************************************************
MCD_STATUS mcdSetTxPolarity
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 laneOffset,
    IN MCD_U16 polarity,
    IN MCD_U16 swReset
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - interface to be modified (MCD_HOST_SIDE or MCD_LINE_SIDE)
    laneOffset - 0..3 for lanes 0-3
    polarity - 1 to invert Tx polarity, 0 to use normal polarity.
    swReset - 1:issue s/w reset to apply set polarity change; 0:s/w reset not issue

 Outputs:
    None

 Returns:
    MCD_OK - if set Tx polarity is successfully issued
    MCD_FAIL - otherwise returns MCD_FAIL

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
MCD_STATUS mcdSetTxPolarity
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 laneOffset,
    IN MCD_U16 polarity,
    IN MCD_U16 swReset
);

/*******************************************************************************
MCD_STATUS mcdGetTxPolarity
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 laneOffset,
    OUT MCD_U16 *polarity
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - interface to be modified (MCD_HOST_SIDE or MCD_LINE_SIDE)
    laneOffset - 0..3 for lanes 0-3

 Outputs:
    polarity - 1:inverted Tx polarity, 0:normal polarity.

 Returns:
    MCD_OK - if Tx polarity is successfully read
    MCD_FAIL - otherwise returns MCD_FAIL

 Description:
    This function reads the Tx polarity with the given input parameters.

 Side effects:
    None

 Notes/Warnings:
    The link will be down if the Tx and Rx polarities are mismatched.
*******************************************************************************/
MCD_STATUS mcdGetTxPolarity
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 laneOffset,
    OUT MCD_U16 *polarity
);

/*******************************************************************************
MCD_STATUS mcdSetRxPolarity
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 laneOffset,
    IN MCD_U16 polarity,
    IN MCD_U16 swReset
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - interface to be modified (MCD_HOST_SIDE or MCD_LINE_SIDE)
    laneOffset - 0..3 for lanes 0-3
    polarity - 1 to invert Rx polarity, 0 to use normal polarity.
    swReset - 1:issue s/w reset to apply set polarity change; 0:s/w reset not issue

 Outputs:
    None

 Returns:
    MCD_OK - if set Rx polarity is successfully issued
    MCD_FAIL - otherwise returns MCD_FAIL

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
MCD_STATUS mcdSetRxPolarity
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 laneOffset,
    IN MCD_U16 polarity,
    IN MCD_U16 swReset
);

/*******************************************************************************
MCD_STATUS mcdGetRxPolarity
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 laneOffset,
    OUT MCD_U16 *polarity
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - interface to be modified (MCD_HOST_SIDE or MCD_LINE_SIDE)
    laneOffset - 0..3 for lanes 0-3

 Outputs:
    polarity - 1:inverted Rx polarity, 0:normal polarity.

 Returns:
    MCD_OK - if Rx polarity is successfully read
    MCD_FAIL - otherwise returns MCD_FAIL

 Description:
    This function reads the Rx polarity with the given input parameters.

 Side effects:
    None

 Notes/Warnings:
    The link will be down if the Tx and Rx polarities are mismatched.
*******************************************************************************/
MCD_STATUS mcdGetRxPolarity
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 laneOffset,
    OUT MCD_U16 *polarity
);

/*******************************************************************************
MCD_STATUS mcdSetTxFFE
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 laneOffset,
    IN MCD_16 preCursor,
    IN MCD_16 attenuation,
    IN MCD_16 postCursor,
    IN MCD_U16 swReset
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - interface to be modified (MCD_HOST_SIDE or MCD_LINE_SIDE)
    laneOffset - 0..3 for lanes 0-3
    preCursor   - Pre-cursor setting range [-7 to 15]
    attenuation - Attenuator setting range [0 to 31]
    postCursor  - Post-cursor setting [-31 to 31]
    swReset - 1:issue s/w reset to apply set Tx FFE change; 0:s/w reset not issue

 Outputs:
    None

 Returns:
    MCD_OK - if set Tx FFE is successfully issued
    MCD_FAIL - otherwise returns MCD_FAIL

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
MCD_STATUS mcdSetTxFFE
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 laneOffset,
    IN MCD_16 preCursor,
    IN MCD_16 attenuation,
    IN MCD_16 postCursor,
    IN MCD_U16 swReset
);

/*******************************************************************************
MCD_STATUS mcdGetTxFFE
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 laneOffset,
    OUT MCD_16 *preCursor,
    OUT MCD_16 *attenuation,
    OUT MCD_16 *postCursor
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - interface to be modified (MCD_HOST_SIDE or MCD_LINE_SIDE)
    laneOffset - 0..3 for lanes 0-3

 Outputs:
    preCursor   - Pre-cursor setting range [-7 to 15]
    attenuation - Attenuator setting range [0 to 31]
    postCursor  - Post-cursor setting [-31 to 31]

 Returns:
    MCD_OK - if read Tx FFE is successfully issued
    MCD_FAIL - otherwise returns MCD_FAIL

 Description:
    This function reads the Tx FFE with the given input parameters.

 Side effects:
    None

 Notes/Warnings:
    None
 *******************************************************************************/
MCD_STATUS mcdGetTxFFE
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 laneOffset,
    OUT MCD_16 *preCursor,
    OUT MCD_16 *attenuation,
    OUT MCD_16 *postCursor
);

/**
* @internal mcdSampleGetPortStatistics function
* @endinternal
*
* @brief  Print Statistics (MIB) counters of a port.
*
* @param[in] pDev        - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] mdioPort  - represents port  (0..8) number
* @param[in] host_or_line     - host or lane side of a port, values MCD_LINE_SIDE or MCD_HOST_SIDE.
* @param[in] reducedPrint     - if true prints only non-zero counters
*
* @retval MCD_OK                    - on success.
* @retval MCD_FAIL                  - on failure
*
* @note use like mcdSampleGetPortStatistics 0,0,3,0
* statistics can be read from 4 registers - one per side and per slice.  IN each register we can specify from which channel to read a statistics and
* which type of counter.  In this function we dump all counters of a certain port, specific for a defined side.  The port is a "channel", meaning we don't
* relate to ports speed in case of multi-lane ports
*/
MCD_STATUS mcdGetPortStatistics
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16  mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_BOOL   reducedPrint
);


#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MCDDIAG_H */

