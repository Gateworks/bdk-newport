/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions and global data for
higher-level functions using MDIO access to enable test modes,
loopbacks, and other diagnostic functions of the Marvell 88X32X0, 
88X33X0, 88E20X0 and 88E21X0 ethernet PHYs.
********************************************************************/
#ifndef MTDDIAG_H
#define MTDDIAG_H

#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif


/******************************************************************************
MTD_STATUS mtdGetPhyRevision
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_DEVICE_ID *phyRev,
    OUT MTD_U8 *numPorts,
    OUT MTD_U8 *thisPort
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    phyRev - revision of this chip, see MTD_DEVICE_ID definition for
             a list of chip revisions with different options
    numPorts - number of ports on this chip (see note below)
    thisPort - this port's relative port number, range is: 
                    0 (single port or T-unit in download mode, i.e fw not running)
                    0-1 (dual port device)
                    0-1 (quad port device)
                    0-7 (octal port device)

 Returns:
    MTD_OK if query was successful, MTD_FAIL if not.

    Will return MTD_FAIL on an unsupported PHY (but will attempt to
    return correct version). See below for a list of unsupported PHYs.

 Description:
    Determines the PHY revision and returns the value in phyRev.
    See definition of MTD_DEVICE_ID for a list of available
    devices and capabilities.

 Side effects:
    None.

 Notes/Warnings:
    The phyRev can be used to determine number PHY revision,
    number of ports, which port this is from PHY perspective
    (0-based indexing 0...3 or 0..2) and what capabilities
    the PHY has.

    If phyRev is MTD_REV_UNKNOWN, numPorts and thisPort will be returned
    as 0 and the function will return MTD_FAIL. 

    If T-unit is in download mode, thisPort will be returned as 0.

    88X33X0 Z1/Z2 is not supported starting with version 1.2 of API.
    E20X0 Z2 is not supported starting with version 1.2 of API.

******************************************************************************/
MTD_STATUS mtdGetPhyRevision
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_DEVICE_ID *phyRev,
    OUT MTD_U8 *numPorts,
    OUT MTD_U8 *thisPort
);




#define MTD_BIST_ABNORMAL_RESTART  ((MTD_U16)(1 << 0)) /* Non-fatal BIST status, last reset was caused by a processor error */
#define MTD_BIST_CKSUMS_EXCEEDED   ((MTD_U16)(1 << 1)) /* Non-fatal BIST status, indicates 2 or more tries to load from SPI flash was needed */
#define MTD_BIST_PMA_FAIL          ((MTD_U16)(1 << 2)) /* Fatal BIST status, XG PMA test failed */
#define MTD_BIST_ENX_FAIL          ((MTD_U16)(1 << 3)) /* Fatal BIST status, XG ENX test failed */
#define MTD_BIST_RTOS_FAIL         ((MTD_U16)(1 << 4)) /* Fatal BIST Couldn't allocate OS resources */
#define MTD_BIST_SW_FAIL           ((MTD_U16)(1 << 5)) /* Fatal BIST Software Error, only valid on engineering builds */
#define MTD_BIST_ECC_CORRECT       ((MTD_U16)(1 << 6)) /* Non-fatal BIST status, sw corrected an ECC RAM error */
#define MTD_BIST_WAIT_POWERDOWN    ((MTD_U16)(1 << 7)) /* Non-fatal BIST status, BIST is waiting for low power condition to clear before running */
#define MTD_BIST_NO_TUNIT          ((MTD_U16)(1 << 8)) /* BIST will not run, no copper unit in this device */
#define MTD_BIST_UNSUPPORTED_DEV   ((MTD_U16)(1 << 9)) /* BIST will not run, wrong firmware for this device, firmware will not run */ 
#define MTD_BIST_ECHO_TEST_DONE    ((MTD_U16)(1 << 14))/* Non-fatal BIST status, echo test is done */
#define MTD_BIST_IN_PROCESS        ((MTD_U16)(1 << 15))/* BIST is in process, should be true only during reset time or echo test time */
/******************************************************************************
 MTD_STATUS mtdGetTunitBISTStatus
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_U16 *bistStatus
 );
 
 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    bistStatus - value of T-unit's current BIST status, read bit
                 definitions above

            
 Returns:
    MTD_OK if query was successful, MTD_FAIL if not

 Description:
    This function returns the T-unit's Built-In Self Test status from 1.C00C.

    The BIST is run following a T-unit hard reset or software reset before the
    reset completes.

    See defines above for checking for fatal errors or other status.

 Side effects:
    None.

 Notes/Warnings:
    BIST status bits are divided into fatal, non-fatal, and info-only
    bits.
 
    Fatal BIST errors will cause the T-unit to hang in reset until it passes.
    Check this register if the T-unit does not exit reset for the reason.

    On engineering-only builds (non-released firmware), non-fatal BIST errors
    will also cause the T-unit firmware to hang.

******************************************************************************/
MTD_STATUS mtdGetTunitBISTStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *bistStatus
);


#define MTD_POWERON_INIT_AN (0) /* during reset/power-on init, state is 0 for
                                   power on, non-zero for AN */
#define MTD_XG_SPEED_LINK   (1) /* during 10GBASE-T/5G/2.5G training/data, use   */
#define MTD_LOW_POWER_MODE  (2) /* T-unit powered-down/low power mode */
#define MTD_TEST_MODE       (3) /* during a test mode */
#define MTD_IG_SPEED_LINK   (4) /* during 1000BASE-T training/data */
#define MTD_CM_SPEED_LINK   (5) /* during 100BASE-T training/data */
#define MTD_XM_SPEED_LINK   (6) /* during 10BASE-T training/data */
#define MTD_NO_TUNIT        (8) /* device has no T unit/copper ability */
#define MTD_5G_SPEED_LINK   (9) /* during 5G training, only on X33X0/E20X0/E21X0 devices */
#define MTD_2P5_SPEED_LINK  (10) /* during 2.5G training, only on X33X0/E20X0/E21X0 devices */
/******************************************************************************
 MTD_STATUS mtdGetTunitFirmwareMode
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_U16 *tunitMode,
     OUT MTD_U16 *tunitState
 );

 
 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    tunitMode - current mode of the T-unit firmware state machine from
                1.C001.11:8, one of the following    
        MTD_POWERON_INIT_AN          
        MTD_XM_SPEED_LINK 
        MTD_CM_SPEED_LINK 
        MTD_IG_SPEED_LINK 
        MTD_XG_SPEED_LINK (not applicable to E20X0/E21X0)
        MTD_LOW_POWER_MODE
        MTD_TEST_MODE   
        MTD_NO_TUNIT (media converter device)
        MTD_5G_SPEED_LINK (X33X0/E20X0/E21X0 devices)
        MTD_2P5_SPEED_LINK (X33X0/E20X0/E21X0 devices)
        
    
    tunitState - current substate of the current mode of the T-unit firmware
                 state machine from 1.C001.7:0                 
 Returns:
    MTD_OK if query was successful, MTD_FAIL if not

 Description:
    This reads 1.C001 and returns the T-unit mode and state. This 
    information describes the current state of the firmware state machine
    at the time it was read. This is a real-time operating mode/
    state of the firmware state machine.

 Side effects:
    None.

 Notes/Warnings:
    Calling this function will result in a read of register 1.C001 which
    contains the short reach fault bit. Reading this register will clear
    that bit. Check the short reach fault bit before calling this function 
    if that bit value is of interest.

******************************************************************************/
MTD_STATUS mtdGetTunitFirmwareMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *tunitMode,
    OUT MTD_U16 *tunitState
);



/*********************PMA TEST MODES********************************/
#define MTD_PMA_TESTMODE_OFF 0x0000  /* return to normal operation */
#define MTD_PMA_TESTMODE_1  0x2000  /* 0010 0000 0000 0000*/
#define MTD_PMA_TESTMODE_2  0x4000  /* 0100 0000 0000 0000*/
#define MTD_PMA_TESTMODE_3  0x6000  /* 0110 0000 0000 0000*/
#define MTD_PMA_TESTMODE_4  0x8000  /* 1000 0000 0000 0000*/
#define MTD_PMA_TESTMODE_5  0xA000  /* 1010 0000 0000 0000*/
#define MTD_PMA_TESTMODE_6  0xC000  /* 1100 0000 0000 0000*/
#define MTD_PMA_TESTMODE_7  0xE000  /* 1110 0000 0000 0000*/

/*********************PMA TEST MODES - Frequencies*******************/
#define MTD_DUAL_TONE_1     0x0400  /* 0000 0100 0000 0000*/
#define MTD_DUAL_TONE_2     0x0800  /* 0000 1000 0000 0000*/
#define MTD_DUAL_TONE_3     0x1000  /* 0001 0000 0000 0000*/
#define MTD_DUAL_TONE_4     0x1400  /* 0001 0100 0000 0000*/
#define MTD_DUAL_TONE_5     0x1800  /* 0001 1000 0000 0000*/
#define MTD_NO_FREQ         0x0000  /* 0000 0000 0000 0000*/

/******************************************************************************
 MTD_STATUS mtdSetPMATestModes
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 speed,
     IN MTD_U16 testMode, 
     IN MTD_U16 testFrequency
 );
 
 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call.

    port - MDIO port address, 0-31

    speed - Speed selection for the test modes. The following are valid options    
        MTD_SPEED_10GIG_FD (not applicable to E20X0/E21X0)
        MTD_SPEED_5GIG_FD (X33X0/E20X0/E21X0 devices only)
        MTD_SPEED_2P5GIG_FD (X33X0/E20X0/E21X0 devices only)
        MTD_SPEED_1GIG_FD
    
    testMode - The test mode needed for testing. One of the following...
        MTD_PMA_TESTMODE_OFF 
        MTD_PMA_TESTMODE_1 
        MTD_PMA_TESTMODE_2 
        MTD_PMA_TESTMODE_3 
        MTD_PMA_TESTMODE_4 
        MTD_PMA_TESTMODE_5 (not valid for 1G)
        MTD_PMA_TESTMODE_6 (not valid for 1G)
        MTD_PMA_TESTMODE_7 (not valid for 1G)

    testFrequency - These are the test frequency options for test mode 4.
        Only valid for 10G/5G/2.5G. For 1G pass MTD_NO_FREQ.
        MTD_DUAL_TONE_1
        MTD_DUAL_TONE_2
        MTD_DUAL_TONE_3
        MTD_DUAL_TONE_4
        MTD_DUAL_TONE_5
        MTD_NO_FREQ (for other test modes besides test mode 4, pass this value)

 Outputs:
    None

 Returns:
    MTD_OK if successful, or MTD_FAIL if not. Will return MTD_FAIL if
    PHY is in forced 100M/10M speed mode.
    
 Description:
    For 10G/5G/2.5G test mode selection:
    Either puts the PHY into the 10GBASE-T PMA Test mode or removes the
    PHY from the PMA test mode based on testMode and testFrequency.
    
    The bits 1.132.(15:13) are the PMA test mode bits. The function reads
    the register 132 and clears the 3MSB's and writes the (testMode),
    input parameter to the apropriate bits.

    The bits 1.132.(12:10) are the transmitter test frequencies used
    for test mode 4. If test mode 4 is the input option, then the code
    reads register 132 and clears bits 12, 11 & 10. Then it writes the
    input frequency to the apropriate bits.

    To move from one test mode to another, the PMA test mode must first be
    turned off to select a new PMA test mode.

    For test mode 3 and 7, you must first set AN advertisement
    speed to be 5G or 2.5G to get the correct speed for these test modes.

    For 1G test mode selection:
    Modifies 7.8000.15:13 based on MTD_PMA_TESTMODE_OFF....TESTMODE_4.
    
    Only MTD_PMA_TEST_MODE_OFF...MTD_PMA_TESTMODE_4 are valid options.
    For testFrequency pass MTD_NO_FREQ.

 Side effects:
    None.

 Notes/Warnings:
    For 10G/5G/2.5G test mode selection:
    1. For all test modes except test mode 4, the input parameter
    testFrequency should be MTD_NO_FREQ.
    2. For all test modes except test mode 4, the transmitter frequency bits are
    not written.
    3. The user can enter any test mode at anytime during training but the way
    to exit from any of the test modes call this function with testMode set to 
    MTD_PMA_TESTMODE_OFF.
    4. Test mode must be turned off (pass MTD_PMA_TESTMODE_OFF) in prior to
    switching to a new PMA test mode.
    5. The tranceiver should be terminated into a 100 Ohm load or unpowered port
    during these tests and prior to starting a test for any tx only test mode.  
    6. Always turn the tst

    For 1G test mode selection:
    1. AN restart will also clear the test mode selection.

******************************************************************************/
MTD_STATUS mtdSetPMATestModes
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 speed,
    IN MTD_U16 testMode, 
    IN MTD_U16 testFrequency
);

/******************************************************************************
 MTD_STATUS mtdGetPMATestMode
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_U16 *speed,
     OUT MTD_U16 *testMode,
     OUT MTD_U16 *testFrequency
 );
 
 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    speed - if test mode is enabled, returns the speed
        MTD_ADV_NONE (if no test mode is enabled)
        MTD_SPEED_10GIG_FD (not applicable to E20X0/E21X0)
        MTD_SPEED_5GIG_FD (X33X0/E20X0/E21X0 devices only)
        MTD_SPEED_2P5GIG_FD (X33X0/E20X0/E21X0 devices only)
        MTD_SPEED_1GIG_FD
    testMode - The value of 1.132 bits 15:13 with bits 12:0 masked off for
        10G/5G/2.5G test mode, or mapped value based on 7.8000.15:13 for 1G. 
        One of the following
         MTD_PMA_TESTMODE_OFF
         MTD_PMA_TESTMODE_1
         MTD_PMA_TESTMODE_2
         MTD_PMA_TESTMODE_3
         MTD_PMA_TESTMODE_4
         MTD_PMA_TESTMODE_5 (not valid for 1G test modes)
         MTD_PMA_TESTMODE_6 (not valid for 1G test modes)
         MTD_PMA_TESTMODE_7 (not valid for 1G test modes)
    testFrequency - The value of 1.132 bits 12:10 with other bits masked off.
        One of the following
         MTD_DUAL_TONE_1
         MTD_DUAL_TONE_2
         MTD_DUAL_TONE_3
         MTD_DUAL_TONE_4
         MTD_DUAL_TONE_5
         MTD_NO_FREQ (for other test modes besides test mode 4, or 1G test mode)
            
 Returns:
    MTD_OK if query was successful, MTD_FAIL if not

 Description:
    For 10G/5G/2.5G test modes:
    The bits 1.132.(15:13) are the PMA test mode bits. The function reads
    the register 132 and returns the 3MSB's in testMode and bits 12:10 in
    testFrequency with other bits masked off.

    For 1G test modes:
    Uses the value of 7.8000.15:13 to return MTD_PMA_TESTMODE_OFF...
    PMA_TESTMODE_4.;

 Side effects:
    None.

 Notes/Warnings:
    None

******************************************************************************/
MTD_STATUS mtdGetPMATestMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *speed,
    OUT MTD_U16 *testMode,
    OUT MTD_U16 *testFrequency
);

/* for loopbacks see the H-unit API */

/******************************************************************************
 MTD_STATUS mtdGet10GBTSNROperatingMargin
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_S16 snr_4chan[]
 )

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    snr_4chan[] - an array to fetch the SNR operating margin. SNR's are 16 bit
                    signed values in unit of 0.1dB

 Returns:
    MTD_OK if the query was successful, MTD_FAIL if not

 Description:
    Reads the 10G/5G/2.5G SNR operating margin from 1.133-136 (channels A-D)
    and returns it in snr_4chan[] converted from an offset binary number
    to a two's complement number in snr_4chan. The units in
    snr_4chan is 1-bit equals 0.1 dB of margin.

 Side effects:
    None

 Notes/Warnings:
    The 10GBASE-T copper link should be up when calling this function or
    results will not be valid.

    Used for 5G and 2.5G SNR Operating Margin on X33X0/E20X0/E21X0 devices.

******************************************************************************/
MTD_STATUS mtdGet10GBTSNROperatingMargin
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_S16 snr_4chan[]
);

/******************************************************************************
 MTD_STATUS mtdGet10GBTSNRMinimumMargin
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_S16 snr_4chan[]
 )

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    snr_4chan[] - an array to fetch the SNR minimum margin. SNR's are 16 bit
                    signed values in unit of 0.1dB

 Returns:
    MTD_OK if the query was successful, MTD_FAIL if not

 Description:
    Reads the 10G/5G/2.5G SNR minimum margin from 1.137-140 (channels A-D)
    and returns it in snr_4chan[] converted from an offset binary number
    to a two's complement number in snr_4chan. The units in
    snr_4chan is 1-bit equals 0.1 dB of margin.

 Side effects:
    Sets the SNR minimum margin to the maximum value when this register is
    read. The read returns the minimum seen since the last read or since
    the link came up.

 Notes/Warnings:
    The 10GBASE-T copper link should be up when calling this function or
    results will not be valid.

    Used for 5G and 2.5G SNR Operating Margin on X33X0/E20X0/E21X0 devices.
    
******************************************************************************/
MTD_STATUS mtdGet10GBTSNRMinimumMargin
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_S16 snr_4chan[]
);

/********** Cable Diagnostics *********/

/******************************************************************************
 MTD_STATUS mtdRun_CableDiagnostics
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port, 
     IN MTD_BOOL breakLink,
     IN MTD_BOOL disableInterPairShort
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    
    breakLink - MTD_TRUE will break the link in data mode and run the test
                    (data will be interrupted if this option is chosen).
                MTD_FALSE will not run the test, but instead will return
                    results of the link training information available
                    leaving the link up if it's up. 

    disableInterPairShort -  MTD_TRUE disables checking for inter pair shorts
                             MTD_FALSE enables checking for inter pair shorts
                             (MTD_FALSE is only available if breakLink is MTD_TRUE)

 Outputs:
    None.

 Returns:
    MTD_OK if test was started successfully, MTD_FAIL if any error occurred

 Description:
    If breakLink is MTD_TRUE, the link is dropped (if it was up) and the cable
    diagnostics are executed to determine length and termination. If this option
    is chosen and disableInterPairShort is MTD_FALSE, the inter-pair short
    test is also executed.

    Call mtdGet_CableDiagnostics_Status() to determine when the test has completed
    and results may be read using mtdGet_CableDiagnostics_Results(), which
    reads the results and returns the port to normal operating condition.

    If breakLink is MTD_FALSE, the link is not dropped (data will not be interrupted),
    the test is not run. If the link is up in 10GBASE-T mode, length and
    termination status as determined from the training are returned. If
    the link is up at some other speed, or the link is down, 0 is returned
    for termination and 0xFF is returned for the length.

    disableInterPairShort is ignored if breakLink is MTD_FALSE.
 

 Side effects:
     None.

 Notes/Warnings:
    The length is reported in meters only.

    If the test is currently running, this function will return MTD_FAIL and
    no registers will be written.

******************************************************************************/
MTD_STATUS mtdRun_CableDiagnostics
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port, 
    IN MTD_BOOL breakLink,
    IN MTD_BOOL disableInterPairShort
);

/******************************************************************************
 MTD_STATUS mtdGet_CableDiagnostics_Status
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_BOOL *testDone
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    testDone - MTD_TRUE - test is complete, and results may be read
               MTD_FALSE - test is still running

 Returns:
    MTD_OK if query succeeded, MTD_FAIL if not (MTD_FAIL if test was not started)

 Description:
    This function gives the status of the test if the test is complete or still
    running.

 Side effects:
    None

 Notes/Warnings:
    If the function returns MTD_FAIL, testDone should be ignored (it's not valid).

******************************************************************************/
MTD_STATUS mtdGet_CableDiagnostics_Status
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *testDone
);

/******************************************************************************
 MTD_STATUS mtdGet_CableDiagnostics_Results
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port, 
     MTD_U8 terminationCode[],
     MTD_U8 length[]
 );
 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    terminationCode[] - for all 4 channels, A-D, one of the following:
        0x0 - invalid or incomplete test
        0x1 - pair okay, no fault
        0x2 - pair open
        0x3 - intra pair short
        ox4 - inter pair short
        0x5 - 0xF - reserved

    length[] - for all 4 channels, A-D, reported in meters

 Returns:
    MTD_OK if query successful, MTD_FAIL if query is unsuccessful or test
        is still running or was not started

 Description:
    This function checks if the test was started and is complete, and if it was
    not started or is not complete, it returns MTD_FAIL.

    If test is complete, it writes the results to terminationCode[] and length[]
    and clears the request to return the PHY to normal operating mode and returns 
    MTD_OK.

 Side effects:
    None

 Notes/Warnings:
    None.

******************************************************************************/
MTD_STATUS mtdGet_CableDiagnostics_Results
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port, 
    MTD_U8 terminationCode[],
    MTD_U8 length[]
);
    

/******************** Echo Test **********************/
/******************************************************************************
 MTD_STATUS mtdStart10GEchoTest
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    None.

 Returns:
    MTD_OK if the test was requested successfully, MTD_FAIL otherwise
    MTD_FAIL if a previously requested test is still in progress.

 Description:
    Puts the PHY port into a special test mode, and performs various
    echo tests. Use mtdIs10GEchoTestDone() to find out if the test is
    finished and results available. Use mtdGet10GEchoTestResults()
    to read the results and exit the test mode and return to normal
    operation.

 Side effects:
    None

 Notes/Warnings:
    The tranceiver copper port must be terminated into a 100 Ohm load or
    unpowered port during these tests.

    These tests should take about 5 seconds.

    Replaced by mtdStartEchoTest(). Left for backward compatibility. 
    Equivalent to mtdStartEchoTest(devPtr,port,MTD_SPEED_10GIG_FD).

******************************************************************************/
MTD_STATUS mtdStart10GEchoTest
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);

/******************************************************************************
 MTD_STATUS mtdIs10GEchoTestDone
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_BOOL *testDone
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    testDone - MTD_TRUE if the test has completed, MTD_FALSE if the test is in
               progress.

 Returns:
    MTD_OK if the status was returned successfully, MTD_FAIL otherwise. MTD_FAIL
    if the test was not requested.

 Description:
    This function first checks if the PHY was requested to run the echo test.
    If not, it returns MTD_FAIL. If it was, it returns in testDone the result
    of the echo test status bit, 1.C00C.14.

 Side effects:
    None

 Notes/Warnings:
    The tranceiver must be terminated terminated into a 100 Ohm load or
    unpowered port during these tests.


    These tests should take about 5 seconds.

    Replaced by mtdIsEchoTestDone(). Left for backward compatibility.

******************************************************************************/
MTD_STATUS mtdIs10GEchoTestDone
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *testDone
);

/******************************************************************************
 MTD_STATUS mtdGet10GEchoTestResults
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_U16 results[]
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    results[] - 20 element array to store the echo/NEXT values.

 Returns:
    MTD_OK if the results were fetched ok, MTD_FAIL if not. MTD_FAIL if
    the test was not requested to be run or isn't done.

 Description:
    This function first makes sure the test was requested to be run and the
    results are ready. If either isn't true, it returns MTD_FAIL.
 
    Then the function fetches the ECHO/NEXT values for the 10G echo test then
    puts the PHY back into normal operating mode.

 Side effects:
    None

 Notes/Warnings:
    The tranceiver must be terminated terminated into a 100 Ohm load or
    unpowered port during these tests.

    Replaced by mtdGetEchoTestResults(), but left this function interface
    for backward compatibility.

******************************************************************************/
MTD_STATUS mtdGet10GEchoTestResults
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 results[]
);

/******************************************************************************
 MTD_STATUS mtdStartEchoTest
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 speed
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    speed - Speed selection for the test. The following are valid options    
        MTD_SPEED_10GIG_FD
        MTD_SPEED_5GIG_FD (X33X0/E20X0/E21X0 devices only)
        MTD_SPEED_2P5GIG_FD (X33X0/E20X0/E21X0 devices only)    

 Outputs:
    None.

 Returns:
    MTD_OK if the test was requested successfully, MTD_FAIL otherwise
    MTD_FAIL if a previously requested test is still in progress.

 Description:
    Puts the PHY port into a special test mode, and performs various
    echo tests. Use mtdIsEchoTestDone() to find out if the test is
    finished and results available. Use mtdGetEchoTestResults()
    to read the results and exit the test mode and return to normal
    operation.

 Side effects:
    None

 Notes/Warnings:
    The tranceiver copper port must be terminated into a 100 Ohm load or
    unpowered port during these tests.

    These tests should take about 5 seconds.

******************************************************************************/
MTD_STATUS mtdStartEchoTest
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 speed
);

/******************************************************************************
 MTD_STATUS mtdIsEchoTestDone
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_BOOL *testDone
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    testDone - MTD_TRUE if the test has completed, MTD_FALSE if the test is in
               progress.

 Returns:
    MTD_OK if the status was returned successfully, MTD_FAIL otherwise. MTD_FAIL
    if the test was not requested.

 Description:
    This function first checks if the PHY was requested to run the echo test.
    If not, it returns MTD_FAIL. If it was, it returns in testDone the result
    of the echo test status bit, 1.C00C.14.

 Side effects:
    None

 Notes/Warnings:
    The tranceiver must be terminated terminated into a 100 Ohm load or
    unpowered port during these tests.


    These tests should take about 5 seconds.

******************************************************************************/
MTD_STATUS mtdIsEchoTestDone
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *testDone
);

/******************************************************************************
 MTD_STATUS mtdGetEchoTestResults
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_U16 results[]
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    results[] - 20 element array to store the echo/NEXT values.

 Returns:
    MTD_OK if the results were fetched ok, MTD_FAIL if not. MTD_FAIL if
    the test was not requested to be run or isn't done.

 Description:
    This function first makes sure the test was requested to be run and the
    results are ready. If either isn't true, it returns MTD_FAIL.
 
    Then the function fetches the ECHO/NEXT values for the echo test then
    puts the PHY back into normal operating mode.

 Side effects:
    None

 Notes/Warnings:
    The tranceiver must be terminated terminated into a 100 Ohm load or
    unpowered port during these tests.


******************************************************************************/
MTD_STATUS mtdGetEchoTestResults
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 results[]
);


/******************************************************************************
 MTD_STATUS mtdGetAmbientNoise
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_U16 noiseResults[]
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
     noiseResults[] - 4 element array to store the channel noise values for A, B, C, and D

 Returns:
    MTD_OK if the test/query was successful, MTD_FAIL if there was any error

 Description:
    The function disables transmit power and turns on the echo test for 10GBASE-T.
    Once the test is completed it fetches the test results in noiseResults[].

 Side effects:
    None

 Notes/Warnings:
    Calls the following functions.
    1. mtdStart10GEchoTest()
    2. mtdIs10GEchoTestDone()
    3. mtdGet10GEchoTestResults()

******************************************************************************/
MTD_STATUS mtdGetAmbientNoise
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 noiseResults[]
);

/***** BER COUNTER *****/
/******************************************************************************
 MTD_STATUS mtdReadBERCount
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_U16 *count
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    count - BER count (max value is 0x3F)

 Returns:
    MTD_OK if query was successful, MTD_FAIL if not

 Description:
    This function reads the 10GBASE-T PCS Status 2 register bits 13:8 and
    returns the BER count.

 Side effects:
    This function clears the BER counter after reading its value.

 Notes/Warnings:
    1. Call this function only after the link is up.
    2. Call this function at the beginning of the time period for which you want
    to monitor the BER to clear the BER count. Then call this function again at
    the end of the time period to get the correct BER count.
    3. After a link drop, the BER count is most likely to be 0x3F

******************************************************************************/
MTD_STATUS mtdReadBERCount
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *count
);

/******************************************************************************
 MTD_STATUS mtdIsLPInfoValid
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_BOOL *validFlag
 );
 
 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    validFlag - MTD_TRUE if link partner info is valid and can be read, MTD_FALSE
                if not

 Returns:
    MTD_OK if query was successful, MTD_FAIL if not

 Description:
    This function reads the 10GBASE-T status register 1.129 and returns MTD_TRUE
    in validFlag if the 10GBASE-T startup protocol has been completed and the 
    10GBASE-T link partner bits set during the startup protocol are valid for the 
    link partner.

    A MTD_FALSE result indicates the bits set during the startup are invalid for the
    link partner.

 Side effects:
    None

 Notes/Warnings:
    This function should be called and checked before reading any of the link partner
    information exchanged during 10GBASE-T training.

******************************************************************************/
MTD_STATUS mtdIsLPInfoValid
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *validFlag
);

/***** PBO - NEAR END and FAR END *****/
/******************************************************************************
 MTD_STATUS mtdReadNearEndPBO
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT *pboValue
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    pboValue -    PBO value
        0x000 - 0 dB
        0x001 - 2 dB
        0x010 - 4 dB
        0x011 - 6 dB
        0x100 - 8 dB
        0x101 - 10 dB
        0x110 - 12 dB
        0x111 - 14 dB

 Returns:
    MTD_OK if query was successful, MTD_FAIL if not

 Description:
    The function reads the register 1.131.12:10 and returns the value.

 Side effects:
    None

 Notes/Warnings:
    This function should be called only after link up. If called during the
    startup process the value is invalid.
******************************************************************************/
MTD_STATUS mtdReadNearEndPBO
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *pboValue
);

/******************************************************************************
 MTD_STATUS mtdReadFarEndPBO
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT *pboValue
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    pboValue -    PBO value
        0x000 - 0 dB
        0x001 - 2 dB
        0x010 - 4 dB
        0x011 - 6 dB
        0x100 - 8 dB
        0x101 - 10 dB
        0x110 - 12 dB
        0x111 - 14 dB

 Returns:
    MTD_OK if query was successful, MTD_FAIL if not

 Description:
    The function reads the register 1.131.15:13 and returns the value.

 Side effects:
    None

 Notes/Warnings:
    This function should be called only after link up. If called during the
    startup process, the value is invalid. Poll the function
    mtdIsLPInfoValid() until the function returns a MTD_TRUE for validFlag.

******************************************************************************/
MTD_STATUS mtdReadFarEndPBO
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *pboValue
);


#define MTD_EYEDIAGRAM_NROWS 51
#define MTD_EYEDIAGRAM_NCOLS 128
#define MTD_EYEDIAGRAM_NQ (MTD_EYEDIAGRAM_NROWS*MTD_EYEDIAGRAM_NCOLS)
#define MTD_XFI_LANEOFFSET 0x200
#define MTD_EYE_SAMPLE_NUM 20  /* default to 2^20 number of samples; 
                                  changed this value if desired */
/******************************************************************************
MTD_STATUS mtdGetSerdesEyeStatistics
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port, 
    IN MTD_U16 curSelLane,
    OUT MTD_U32 **eyeDataUp, 
    OUT MTD_U32 **eyeDataDn,  
    OUT MTD_U16 *eyeArea, 
    OUT MTD_U16 *eyeWidth, 
    OUT MTD_U16 *eyeHeight
)

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    curSelLane - XFI lane number, 0 or 1

 Outputs:
    eyeDataUp - 26 x 128 array of 32-bit eye data (readout from register 30.8012 & 30.8013)
    eyeDataDn - 26 x 128 array of 32-bit eye data (readout from register 30.8012 & 30.8013)
    eyeArea - number of open samples - to get percentage take eyeArea*100/(51*121)
    eyeWidth - width of the eye opening (in ps)
    eyeHeight - height of the eye opening (in mV)

 Returns:
    MTD_OK if query was successful, MTD_FAIL if not

 Description:
    The function is translated from the source code of Marvell's SMI Eye Diagram GUI. 
    It reads Serdes eye diagram data and computes relevant eye statistics.
    Two arrays of size 26x128x32-bit should be allocated before calling this function and 
    the 2D pointers should be passed down for eye data collection (see example below).

 Usage example:
        :
        MTD_U32 eyeDataUp[(MTD_EYEDIAGRAM_NROWS + 1) / 2][MTD_EYEDIAGRAM_NCOLS] = {0};
        MTD_U32 eyeDataDn[(MTD_EYEDIAGRAM_NROWS + 1) / 2][MTD_EYEDIAGRAM_NCOLS] = {0};

        ATTEMPT(mtdGetSerdesEyeStatistics(devPtr,port,curSelLane,eyeDataUp,eyeDataDn,&eyeArea,&eyeWidth,&eyeHeight));
        :

 Side effects:
    None

 Notes/Warnings:
    1. Eye data can only be collected from active Serdes lanes. 
    2. Eye data collection takes at least 20 seconds.
******************************************************************************/
MTD_STATUS mtdGetSerdesEyeStatistics
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port, 
    IN MTD_U16 curSelLane,
    OUT MTD_U32 eyeDataUp[][MTD_EYEDIAGRAM_NCOLS],
    OUT MTD_U32 eyeDataDn[][MTD_EYEDIAGRAM_NCOLS],
    OUT MTD_U16 *eyeArea,
    OUT MTD_U16 *eyeWidth, 
    OUT MTD_U16 *eyeHeight
);

/*******************************************************************************
MTD_STATUS mtdSerdesEyePlotChart
(
    IN MTD_DEV_PTR pDev,
    IN MTD_U32 raw_topHalf_2eye[][MTD_EYEDIAGRAM_NCOLS], 
    IN MTD_U32 raw_bottomHalf_2eye[][MTD_EYEDIAGRAM_NCOLS]
);

 Inputs:
     devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call

     raw_topHalf_2eye - a two-dimensional array raw eye data collected for 
                        top half eye
     raw_bottomHalf_2eye - a two-dimensional array raw eye data collected for 
                           bottom half eye

 Outputs:
     None

 Returns:
     MTD_OK  - on success
     MTD_FAIL  - on error

Description:
     This function processed the raw eye results and plot the eye diagram. 
     The raw eye results must be collected from the mtdGetSerdesEyeStatistics() 
     API and passed in to this function.
     If this call is successfull, the eye diagram will be plotted in the 
     MTD_DBG_INFO() message logging.

 Side effects:
    None

 Notes/Warnings:
    None

*******************************************************************************/
MTD_STATUS mtdSerdesEyePlotChart
(
    IN MTD_DEV_PTR pDev,
    IN MTD_U32 raw_topHalf_2eye[][MTD_EYEDIAGRAM_NCOLS], 
    IN MTD_U32 raw_bottomHalf_2eye[][MTD_EYEDIAGRAM_NCOLS]
);

/******************************************************************************
 T unit packet generator/checker functions
*******************************************************************************/

/* NOTE: these values are shared with the packet generators in the H and
   X unit */

/* possible values for pktPatternControl */
#define MTD_PKT_NO_MASK            0  /* payload sent without change */
#define MTD_PKT_INV_SKIP_WRD       2  /* inverts every other word  */
#define MTD_PKT_2INV_2NOT          3  /* two inverted two not inverted */
#define MTD_PKT_LFT_SHFT_BYTE      4  /* left shift by byte */
#define MTD_PKT_RHT_SHFT_BYTE      5  /* right shift by byte */
#define MTD_PKT_LFT_SHFT_WRD       6  /* left shift by word */
#define MTD_PKT_RHT_SHFT_WRD       7  /* right shift by word */
#define MTD_PKT_INC_BYTE           8  /* increment by byte */
#define MTD_PKT_DEC_BYTE           9  /* decrement by byte */
#define MTD_PKT_RANDOM_BYTE       10  /* pseudo-random byte */
#define MTD_PKT_RANDOM_WORD       11  /* pseudo-random word */

/* possible values for frameLengthControl */
#define MTD_PKT_RAND_LEN0          0 /* rand len 64 bytes - 1518 bytes */
#define MTD_PKT_RAND_LEN1          1 /* rand len 64 bytes - 0xFFF bytes */
#define MTD_PKT_RAND_LEN2          2 /* rand len 64 bytes - 0x1FFF bytes */
#define MTD_PKT_RAND_LEN3          3 /* rand len 64 bytes - 0x3FFF bytes */
#define MTD_PKT_RAND_LEN4          4 /* rand len 64 bytes - 0x7FFF bytes */
#define MTD_PKT_RAND_LEN5          5 /* rand len 64 bytes - 0xFFFF bytes */
#define MTD_PKT_TUNIT_FIXED_LEN6   6 /* fixed len 64 bytes, for TUNIT 10G/5G/
                                        2.5G ONLY */
#define MTD_PKT_TUNIT_FIXED_LEN7   7 /* fixed len 64 bytes, for TUNIT 10G/5G/
                                        2.5G ONLY */
/* values 8 and greater are the exact length of the frame in bytes up to 
   0xFFFF */


/******************************************************************************
 MTD_STATUS mtdTunitConfigurePktGeneratorChecker
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16  port,
     IN MTD_U16  speed,
     IN MTD_BOOL readToClear,
     IN MTD_U16  pktPatternControl,
     IN MTD_BOOL generateCRCoff,
     IN MTD_U32  initialPayload,
     IN MTD_U16  frameLengthControl,
     IN MTD_U16  numPktsToSend,
     IN MTD_BOOL randomIPG,
     IN MTD_U16  ipgDuration,
     IN MTD_BOOL clearInitCounters
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    speed  - selects packet generator to configure (10G or non-10G packet
             generator based on these values, 2.5G-10G selects the 10G packet 
             generator, others select the 1G):
             MTD_ADV_NONE - autonegotiation is in progress or disabled 
                            (invalid option - will result in an error)
             MTD_SPEED_10M_HD - speed is resolved to 10BT half-duplex
             MTD_SPEED_10M_FD - speed is resolved to 10BT full-duplex
             MTD_SPEED_100M_HD - speed is resolved to 100BASE-TX half-duplex
             MTD_SPEED_100M_FD - speed is resolved to 100BASE-TX full-duplex
             MTD_SPEED_1GIG_HD - speed is resolved to 1000BASE-T half-duplex
             MTD_SPEED_1GIG_FD - speed is resolved to 1000BASE-T full-duplex
             MTD_SPEED_10GIG_FD - speed is resolved to 10GBASE-T 
                                  (88X32X0/88X33X0 devices only)
             MTD_SPEED_2P5GIG_FD - speed is resolved to 2.5GBASE-T 
                                   (88X33X0/88E20X0/88E21X0 family only)
             MTD_SPEED_5GIG_FD - speed is resolved to 5GBASE-T 
                                 (88X33X0/88E20X0/88E21X0 family only)

             MTD_SPEED_10M_HD_AN_DIS - speed forced to 10BT half-duplex
             MTD_SPEED_10M_FD_AN_DIS - speed forced to 10BT full-duplex
             MTD_SPEED_100M_HD_AN_DIS - speed forced to 100BT half-duplex
             MTD_SPEED_100M_FD_AN_DIS - speed forced to 100BT full-duplex
             MTD_SPEED_MISMATCH - speed is forced to one of above speeds, but
                                  indicated up at a different speed (invalid option - will result in an error)
    readToClear - MTD_TRUE if the desired behavior is that when the
                  counters are read, they are reset. MTD_FALSE if the
                  desired behavior is that they must be explicitly cleared
                  by mtdTunitPktGeneratorCounterReset() and reading
                  them just returns the current value without clearing them.
                  NOTE: This parameter only works for 10G/5G/2.5G speeds (i.e
                  on the 10G packet generator). Read-to-clear is not available on the
                  non-10G packet generator.
    pktPatternControl - controls the generation of the payload. One of the
                        following:
                            MTD_PKT_NO_MASK
                            MTD_PKT_INV_SKIP_WRD
                            MTD_PKT_2INV_2NOT
                            MTD_PKT_LFT_SHFT_BYTE
                            MTD_PKT_RHT_SHFT_BYTE
                            MTD_PKT_LFT_SHFT_WRD
                            MTD_PKT_RHT_SHFT_WRD
                            MTD_PKT_INC_BYTE
                            MTD_PKT_DEC_BYTE
                            MTD_PKT_RANDOM_BYTE
                            MTD_PKT_RANDOM_WORD
    generateCRCoff - MTD_TRUE turns CRC generation off, MTD_FALSE turns
                     CRC generation on
    initialPayload - start of payload value. Format is from MS bit to
                     LS bit: BYTE3:BYTE2:BYTE1:BYTE0, bit 31 to bit 0,
                     left to right
    frameLengthControl - controls the length of the frame in bytes.
                         values 0...5 (see above) pick various random lengths
                         from 64 to a different stop value. 6/7 is undefined
                         and values 8 and greater are the exact frame length
                         in bytes. See definitions above MTD_PKT_RAND_LEN0...
                         LEN7.
    numPktsToSend - 0 stops generation, 0x001-0xFFFE sends exactly that number
                    of packets then stops. 0xFFFF sends continuously.
    randomIPG - MTD_TRUE uses a random IPG from 5 bytes to value specified
                in ipgDuration. MTD_FALSE uses fixed IPG as specified in
                ipgDuration.
    ipgDuration - Meaning depends on randomIPG (see above). Each bit
                  equals 4 bytes of idle. Valid range is 0...0x7FFF.
    clearInitCounters - 1 = Clears TX, RX and error counters before enable the 
                        packet generator/checker. 0 = don't clear the counters

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL if io error or bad parameter passed in (out of range)

 Description:
    This function is used to configure the packet generator/checker for the
    T unit. It selects either the 10G packet generator for speeds greater
    than 1G, or the non-10G packet generator for speeds 1G or less based
    on the speed passed in.



 Side effects:
    None

 Notes/Warnings:
    Call mtdTunitEnablePktGeneratorChecker() to enable/start the generator
    or checker or disable/stop it.

    There are two packet generators in the T unit and they have slightly
    different behavior and also have different registers. The API is
    designed to help use them both easily.

    The 10G packet generator is used for 10G, 5G and 2.5G. The non-10G
    packet generator is used for 1G and below.

    The transmit/receive speed is taken from the copper speed.

    For the 10G packet generator, the copper link being down will automatically
    disable the generator/checker. It cannot be enabled with the link down.

    The non-10G packet generator will stop transmitting when the copper link
    is down, but will remain enabled and start transmitting again when the
    link comes back up.

    It's suggested because of this slight difference in behavior to monitor
    for copper link drops while transmitting or receiving data as a link drop
    during a test can affect your results.

    The 10G packet generator can send data towards the line, towards the MAC,
    or both.

    The non-10G packet generator can only send data towards the line.

    Passing in an invalid speed (such as MTD_SPEED_MISMATCH or MTD_ADV_NONE)
    will result in an error.    .
******************************************************************************/
MTD_STATUS mtdTunitConfigurePktGeneratorChecker
(
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16  port,
     IN MTD_U16  speed,
     IN MTD_BOOL readToClear,
     IN MTD_U16  pktPatternControl,
     IN MTD_BOOL generateCRCoff,
     IN MTD_U32  initialPayload,
     IN MTD_U16  frameLengthControl,
     IN MTD_U16  numPktsToSend,
     IN MTD_BOOL randomIPG,
     IN MTD_U16  ipgDuration,
     IN MTD_BOOL clearInitCounters
);

/* Values for 10G/5G/2.5G packet generator mux control.These options are not
   valid for 1G and below. */
/* 1G and below packet generator/checker always goes to/from the line. */
#define MTD_PACKETGEN_TO_LINE     0x0002 /* for generator control */
#define MTD_PACKETGEN_TO_MAC      0x0004 
#define MTD_PACKETGEN_TO_BOTH     0x0006 
#define MTD_CHECKER_FROM_LINE     0x0000 /* for checker control */
#define MTD_CHECKER_FROM_MAC      0x0001 

/******************************************************************************
MTD_STATUS mtdTunit10GPktGenMuxSelect
(
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16  port,
     IN MTD_U16  generatorControl,
     IN MTD_U16  checkerControl
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    generatorControl - Packet generator control with the following: 
                       MTD_PACKETGEN_TO_LINE - Inject packet to LINE
                       MTD_PACKETGEN_TO_MAC  - Inject packet to MAC(XGMII)
                       MTD_PACKETGEN_TO_BOTH  - Inject packet to both LINE and 
                                                MAC(XGMII)
    checkerControl - Packet checker control with the following: 
                     MTD_CHECKER_FROM_LINE - Receive packet from LINE
                     MTD_CHECKER_FROM_MAC  - Receive packet from MAC(XGMII) 

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL if io error or bad parameter passed in (out of range)

 Description:
    This function sets the TX and RX mux of the packet generator and receiver 
    for 10G speed. The TX mux controls the direction which the packet is 
    injected and RX mux controls the direction the packet is received.

 Side effects:
    None

 Notes/Warnings:
    This function is for 10G, 5G and 2.5G speed only. Calling this function 
    for 1G and below speed will result unpredictable result!

******************************************************************************/
MTD_STATUS mtdTunit10GPktGenMuxSelect
(
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16  port,
     IN MTD_U16  generatorControl,
     IN MTD_U16  checkerControl
);

/******************************************************************************
 MTD_STATUS mtdTunitEnablePktGeneratorChecker
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 speed,
     IN MTD_BOOL enableGenerator,
     IN MTD_BOOL enableChecker
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    speed  - selects packet generator to enable/disable (10G or non-10G packet
             generator based on these values, 2.5G-10G selects the 10G packet 
             generator, others select the 1G):
             MTD_ADV_NONE - autonegotiation is in progress or disabled 
                            (invalid option - will result in an error)
             MTD_SPEED_10M_HD - speed is resolved to 10BT half-duplex
             MTD_SPEED_10M_FD - speed is resolved to 10BT full-duplex
             MTD_SPEED_100M_HD - speed is resolved to 100BASE-TX half-duplex
             MTD_SPEED_100M_FD - speed is resolved to 100BASE-TX full-duplex
             MTD_SPEED_1GIG_HD - speed is resolved to 1000BASE-T half-duplex
             MTD_SPEED_1GIG_FD - speed is resolved to 1000BASE-T full-duplex
             MTD_SPEED_10GIG_FD - speed is resolved to 10GBASE-T 
                                  (88X32X0/88X33X0 devices only)
             MTD_SPEED_2P5GIG_FD - speed is resolved to 2.5GBASE-T 
                                   (88X33X0/88E20X0/88E21X0 family only)
             MTD_SPEED_5GIG_FD - speed is resolved to 5GBASE-T 
                                 (88X33X0/88E20X0/88E21X0 family only)

             MTD_SPEED_10M_HD_AN_DIS - speed forced to 10BT half-duplex
             MTD_SPEED_10M_FD_AN_DIS - speed forced to 10BT full-duplex
             MTD_SPEED_100M_HD_AN_DIS - speed forced to 100BT half-duplex
             MTD_SPEED_100M_FD_AN_DIS - speed forced to 100BT full-duplex
             MTD_SPEED_MISMATCH - speed is forced to one of above speeds, but
                                  indicated up at a different speed 
                                  (invalid option - will result in an error)

    enableGenerator - MTD_TRUE starts the packet generator, MTD_FALSE
                      stops it
    enableChecker - MTD_TRUE starts the packet checker, MTD_FALSE
                    stops it

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function enables/disables either the packet generator or packet 
    checker (or both) in T unit.

 Side effects:
    None

 Notes/Warnings:
    The 10G packet generator (10G/5G/2.5G) can be configured to send towards
    the line, the MAC, or both and the checker can be configured to receive 
    from either side.

    The non-10G packet generator (1G and below) can only send/receive from the
    line.

    The input parameters generatorControl and checkerControl are ignored for 
    speeds 1G and below.

    The copper link must be up at the speed configured before enabling the
    generator/checker and must stay up, otherwise the TX count will not
    increment and no RX data will be received.

    See the notes for details on what happens if the copper link is down/drops
    looking at the Notes/Warnings section of 
    mtdTunitConfigurePktGeneratorChecker().

    Passing in an invalid speed (such as MTD_SPEED_MISMATCH or MTD_ADV_NONE)
    will result in an error.
******************************************************************************/
MTD_STATUS mtdTunitEnablePktGeneratorChecker
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  speed,
    IN MTD_BOOL enableGenerator,
    IN MTD_BOOL enableChecker
);

/******************************************************************************
 MTD_STATUS mtdTunitPktGeneratorCounterReset
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 speed
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    speed  - selects packet generator counters to reset (10G or non-10G packet
             generator based on these values):
             MTD_ADV_NONE - autonegotiation is in progress or disabled 
                            (invalid option - will result in an error)
             MTD_SPEED_10M_HD - speed is resolved to 10BT half-duplex
             MTD_SPEED_10M_FD - speed is resolved to 10BT full-duplex
             MTD_SPEED_100M_HD - speed is resolved to 100BASE-TX half-duplex
             MTD_SPEED_100M_FD - speed is resolved to 100BASE-TX full-duplex
             MTD_SPEED_1GIG_HD - speed is resolved to 1000BASE-T half-duplex
             MTD_SPEED_1GIG_FD - speed is resolved to 1000BASE-T full-duplex
             MTD_SPEED_10GIG_FD - speed is resolved to 10GBASE-T 
                                  (88X32X0/88X33X0 devices only)
             MTD_SPEED_2P5GIG_FD - speed is resolved to 2.5GBASE-T 
                                  (88X33X0/88E20X0/88E21X0 family only)
             MTD_SPEED_5GIG_FD - speed is resolved to 5GBASE-T 
                                 (88X33X0/88E20X0/88E21X0 family only)

             MTD_SPEED_10M_HD_AN_DIS - speed forced to 10BT half-duplex
             MTD_SPEED_10M_FD_AN_DIS - speed forced to 10BT full-duplex
             MTD_SPEED_100M_HD_AN_DIS - speed forced to 100BT half-duplex
             MTD_SPEED_100M_FD_AN_DIS - speed forced to 100BT full-duplex
             MTD_SPEED_MISMATCH - speed is forced to one of above speeds, but
                                  indicated up at a different speed 
                                  (invalid option - will result in an error)

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function explicitly clears all the counters when the packet
    generator/checker has been setup to be cleared by writing a
    bit to the control register instead of being cleared when
    the counter(s) are read.

    This function operates on the counters in the T unit. It selects
    either the 10G packet generator or the non-10G packet generator
    based on the speed parameter being passed in.

    When this function is called the transmit, receive, error and
    link drop counters will be cleared.

 Side effects:
    None

 Notes/Warnings:
    This function assumes the generator/checker is enabled and has been 
    configured to be cleared by previously passing MTD_FALSE for parameter 
    readToClear in function mtdConfigurePktGeneratorChecker().

    For the non-10G packet generator, this is the only way to clear the 
    counters. There is no clear-to-read functionality for the non-10G packet 
    generator.

    Passing in an invalid speed (such as MTD_SPEED_MISMATCH or MTD_ADV_NONE)
    will result in an error.
******************************************************************************/
MTD_STATUS mtdTunitPktGeneratorCounterReset
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 speed
);

#define MTD_PKT_GET_TX  0
#define MTD_PKT_GET_RX  1
#define MTD_PKT_GET_ERR 2
/******************************************************************************
 MTD_STATUS mtdTunitPktGeneratorGetCounter
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 speed,
     IN MTD_U16 whichCounter,
     OUT MTD_U64 *packetCount,
     OUT MTD_U64 *byteCount
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    speed  - selects packet generator counters to read (10G or non-10G packet
             generator based on these values):
             MTD_ADV_NONE - autonegotiation is in progress or disabled 
                            (invalid option - will result in an error)
             MTD_SPEED_10M_HD - speed is resolved to 10BT half-duplex
             MTD_SPEED_10M_FD - speed is resolved to 10BT full-duplex
             MTD_SPEED_100M_HD - speed is resolved to 100BASE-TX half-duplex
             MTD_SPEED_100M_FD - speed is resolved to 100BASE-TX full-duplex
             MTD_SPEED_1GIG_HD - speed is resolved to 1000BASE-T half-duplex
             MTD_SPEED_1GIG_FD - speed is resolved to 1000BASE-T full-duplex
             MTD_SPEED_10GIG_FD - speed is resolved to 10GBASE-T 
                                  (88X32X0/8833X0 devices only)
             MTD_SPEED_2P5GIG_FD - speed is resolved to 2.5GBASE-T 
                                   (88X33X0/88E20X0/88E21X0 family only)
             MTD_SPEED_5GIG_FD - speed is resolved to 5GBASE-T 
                                 (88X33X0/88E20X0/88E21X0 family only)

             MTD_SPEED_10M_HD_AN_DIS - speed forced to 10BT half-duplex
             MTD_SPEED_10M_FD_AN_DIS - speed forced to 10BT full-duplex
             MTD_SPEED_100M_HD_AN_DIS - speed forced to 100BT half-duplex
             MTD_SPEED_100M_FD_AN_DIS - speed forced to 100BT full-duplex
             MTD_SPEED_MISMATCH - speed is forced to one of above speeds, but
                                  indicated up at a different speed 
                                  (invalid option - will result in an error)
    whichCounter - One of the following, depending on which set of counters
                   is being read:
                       MTD_PKT_GET_TX to read the generator/transmit counters
                       MTD_PKT_GET_RX to read the checker/receive counters
                       MTD_PKT_GET_ERR to read the packet error counter


 Outputs:
    packetCount - For 2.5G, 5G and 10G speed, tx/rx/err packet count in the
                  following format:
                  from MS bit to LS bit (note top 16-bits is always
                  0, since this is a 48-bit result):
                  0:WORD2:WORD1:WORD0 where each word is a 16-bit
                  unsigned value, and words are combined into
                  a single, 48-bit result.
                  For 1G and lower speed, a 32-bit result of WORD1:WORD0
                  is returned. WORD2 is always 0.
    byteCount -   For 2.5G, 5G and 10G speed, tx/rx byte count in the
                  following format:
                  from MS bit to LS bit (note top 16-bits is always
                  0, since this is a 48-bit result):
                  0:WORD2:WORD1:WORD0 where each word is a 16-bit
                  unsigned value, and words are combined into
                  a single, 48-bit result. NOTE: This parameter
                  is always 0 when whichCounter is set to
                  MTD_PKT_GET_ERR, since error counter is a packet
                  count only.
                  For 1G and lower speed, a 32-bit result of WORD1:WORD0
                  is returned. WORD2 is always 0.
 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function is used to read the transmit/receive/error counter for the
    packet generator(s)/checker(s) in the T unit.

    Which counters are read is based on the speed passed in to select
    either the 10G counters (for speeds 10G/5G/2.5G) or non-10G counters
    (for speeds 1G and below).

 Side effects:
    None

 Notes/Warnings:
    byteCount is always 0 for MTD_PKT_GET_ERR, since the error counter
    only counts packets.

    If packet generator/checker was configured to clear counter(s) on read,
    this function will clear the counter being read.

    Passing in an invalid speed (such as MTD_SPEED_MISMATCH or MTD_ADV_NONE)
    will result in an error.
******************************************************************************/
MTD_STATUS mtdTunitPktGeneratorGetCounter
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 speed,
    IN MTD_U16 whichCounter,
    OUT MTD_U64 *packetCount,
    OUT MTD_U64 *byteCount
);

/******************************************************************************
 MTD_STATUS mtdTunitConfigure10GLinkDropCounter
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_BOOL readToClear,
     IN MTD_BOOL rollOver,
     IN MTD_BOOL enable
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    readToClear - MTD_TRUE selects to configure the link drop counter
                  to clear on read. MTD_FALSE select to not clear
                  until it's forced cleared.
    rollOver    - MTD_TRUE selects counter rolls over when it reaches 0xffff
                  and a subsequent link drop occurs. MTD_FALSE
                  selects to have the counter stop counting when it
                  reaches the maximum value of 0xffff.
    enable      - Enable Link Drop counter for counting 

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function configures the link drop counter register based on the
    input parameters and clears the link drop counter after enabled.

 Side effects:
    None

 Notes/Warnings:
    This is for 10G T unit only. Speeds 10G and also 5G/2.5G for PHYS 
    supporting those speeds. The link drop counter is cleared in this function.
******************************************************************************/
 MTD_STATUS mtdTunitConfigure10GLinkDropCounter
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL readToClear,
    IN MTD_BOOL rollOver,
    IN MTD_BOOL enable
);

/******************************************************************************
 MTD_STATUS mtdTunit10GGetLinkDropCounter
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_BOOL counterReset,
     OUT MTD_U16 *linkDropCounter
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    counterReset - MTD_TRUE forces the link drop counter to be cleared
                   by writing the control register. MTD_FALSE
                   selects to not force the link drop counter to be
                   cleared.

 Outputs:
    linkDropCounter - number of 10G (5G/2.5G) copper link drops which occurred
                      since the last time the counter was cleared.

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function reads the link drop counter register. If the link
    drop counter was configured to be cleared on read, it will clear
    regardless of the "counterReset" flag.

    If counterReset is MTD_TRUE, it will force clear the link drop
    counter by writing the link drop counter configuration control
    register.

 Side effects:
    None

 Notes/Warnings:
    If 10G link drop counter was configured to clear counter(s) on read,
    this function will clear the link drop counter regardless of the value
    of "counterReset".

    This is for 10G T unit only. Speeds 10G and also 5G/2.5G for PHYS 
    supporting those speeds.
******************************************************************************/
MTD_STATUS mtdTunit10GGetLinkDropCounter
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL counterReset,
    OUT MTD_U16 *linkDropCounter
);

/******************************************************************************
MTD_STATUS mtdSetTunitDeepMacLoopback
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  speed,
    IN MTD_BOOL enable
)

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    speed  - Current speed of the T-unit link. the speed is ignored when 
             the loopback is disabled 
             
             MTD_SPEED_10GIG_FD - speed is resolved to 10GBASE-T 
                                  (88X32X0/88X33X0 devices only)
             MTD_SPEED_2P5GIG_FD - speed is resolved to 2.5GBASE-T 
                                   (88X33X0/88E20X0/88E21X0 family only)
             MTD_SPEED_5GIG_FD - speed is resolved to 5GBASE-T 
                                 (88X33X0/88E20X0/88E21X0 family only)
    enable - MTD_TRUE = enable loopback, MTD_FALSE = disable loopback

 Outputs:
    None

 Returns:
    Returns MTD_OK or MTD_FAIL

 Description:
    Enable/Disable T-unit Deep MAC loopback at the speed indicated
    by "speed" when enabled. When disabled, sets the PMA Control
    Register speed bits back to the default (ignores the "speed"
    parameter on disable/MTD_FALSE).

 Side effects:
    None

 Notes/Warnings:
    The other Mac Loopbacks are controlled by mtdSetHXunitMacLoopback().
 
    Only one loopback can be enabled at a time in the PHY. Otherwise, the 
    behavior will be undefined.

    Before calling this API, please make sure the T-unit link speed is matching
    the speed parameter input. Assuming the speed is not forced to 100M or 10M 
    mode when calling this API.

    Deep MAC Loopback in the T-unit is not supported when the T-unit
    media-side link is down.
*******************************************************************************/
MTD_STATUS mtdSetTunitDeepMacLoopback
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  speed,
    IN MTD_BOOL enable
);

#define MTD_2P5G_ABOVE_LB_SPEED    1
#define MTD_1G_BELOW_LB_SPEED      0
/******************************************************************************
MTD_STATUS mtdSetTunitShallowLineLoopback
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  loopbackSpeed,
    IN MTD_BOOL enable
)

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    loopbackSpeed -
                 MTD_2P5G_ABOVE_LB_SPEED = line speed is in 10G/5G/2.5G
                 MTD_1G_BELOW_LB_SPEED   = line speed is in 1000M/100M/10M
    enable - MTD_TRUE = enable loopback, MTD_FALSE = disable loopback

 Outputs:
    None

 Returns:
    Returns MTD_OK or MTD_FAIL

 Description:
    Enable/Disable T-unit from the line back towards the line. The line must 
    be up at the correct speed for the loopback to work according the setting. 
    The loopbackSpeed passed in must match the speed the line is up at for data 
    to be correctly looped back.

 Side effects:
    None

 Notes/Warnings:
    If the wrong loopbackSpeed is passed, the loopback is still enabled or disabled, 
    but returns MTD_FAIL.

    Only one loopback can be enabled at a time in the PHY. Otherwise, the 
    behavior will be undefined.
*******************************************************************************/
MTD_STATUS mtdSetTunitShallowLineLoopback
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  loopbackSpeed,
    IN MTD_BOOL enable
);

typedef struct
{
    MTD_BOOL tunitMacLoopback; 
    MTD_BOOL tunitLineLoopback2P5GAbove;
    MTD_BOOL tunitLineLoopback1GBelow;
    MTD_BOOL hunitMacLoopback; 
    MTD_BOOL hunitLineLoopback;
    MTD_BOOL hunitLinePassThrough;
    MTD_BOOL xunitMacLoopback;      /* NA for E20X0 and E21X0 PHY */
    MTD_BOOL xunitMacPassThrough;   /* NA for E20X0 and E21X0 PHY */ 
    MTD_BOOL xunitLineLoopback;     /* NA for E20X0 and E21X0 PHY */
} MTD_LOOPBACKS_STATUS_STRUCT;

/******************************************************************************
MTD_STATUS mtdGetLoopbackSetting
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16     port,
    OUT MTD_LOOPBACKS_STATUS_STRUCT *loopbackStatus
)

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31

 Outputs:    
    loopbackStatus - tunitMacLoopback 
                     tunitLineLoopback2P5GAbove
                     tunitLineLoopback1GBelow
                     hunitMacLoopback 
                     hunitLineLoopback
                     xunitMacLoopback 
                     xunitLineLoopback
                          MTD_TRUE = loopback enabled
                          MTD_FALSE = loopback disabled

                     hunitLinePassThrough
                          MTD_TRUE = No Ingress Blocking for H-unit
                          MTD_FALSE = Ingress Blocking for H-unit

                     xunitMacPassThrough
                          MTD_TRUE = No Egress Blocking for X-unit
                          MTD_FALSE = Egress Blocking for X-unit

 Returns:
    Returns MTD_OK or MTD_FAIL

 Description:
    Gets the current loopback settings for T-unit, H-unit and X-unit. 

 Side effects:
    None

 Notes/Warnings:
    No X-unit in E20X0 and E21X0 PHY

*******************************************************************************/
MTD_STATUS mtdGetLoopbackSetting
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16     port,
    OUT MTD_LOOPBACKS_STATUS_STRUCT *loopbackStatus
);

/******************************************************************************
MTD_STATUS mtdGetTempSensorMDIOPort
(
    IN MTD_DEV_PTR devPtr,
    IN  MTD_U16  port,
    OUT MTD_U16 *sensorPort
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31

 Output:
    sensorPort - MDIO port number of the temperature sensor on the device(0-31)
             
             Temperature sensor mapping on PHY:

             Cunit
             ---------------------------
             X3220  - *P1 
             X3240  - *P3

             X3310  - *P0
             X3320  - *P0, *P1
             X3340  - *P0, *P1, *P2, *P3

             E2010  - *P0
             E2020  - *P0, *P1
             E2040  - *P0, *P1, *P2, *P3

             Tunit
             ---------------------------
             E2110  - *P0
             E2140  - *P1
             E2180  - *P1, *P3

             This is a relative port number.
             * indicates the port number which the temperature sensor is used.
 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function returns the mdio port number of the temperature sensor 
    for the chip type in devPtr->deviceId

 Side effects:
    None

 Notes/Warnings:
    For X33X0 based PHY, every port has a temperature sensor. For E21X0 PHY, 
    use the temperature sensor of the nearest port.
****************************************************************************/
MTD_STATUS mtdGetTempSensorMDIOPort
(
    IN MTD_DEV_PTR devPtr,
    IN  MTD_U16  port,
    OUT MTD_U16 *sensorPort
);

/******************************************************************************
 MTD_STATUS mtdEnableTemperatureSensor
 (
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function enables the temperature sensor for the PHY type 
    in devPtr->deviceId. It configures it for average mode
    2^11 samples with an intersample period of 2.2ms.

    See mtdGetTempSensorMDIOPort() to see which temperature sensor
    is used on PHYs with multiple temperature sensors.

 Side effects:
    None

 Notes/Warnings:
    On E21X0, the T unit temperature sensor is shared with the T unit 
    embedded processor.
 
    For E21X0, the T Unit temperature sensor is enabled in firmware on newer
    firmware versions. This function checks if it is not enabled, it enables
    the T unit temperature sensor, otherwise it leaves it as is.

    On older firmware that does not enable the temperature sensor, a T unit
    soft reset will result in the temperature sensor being disabled, and 
    it will have to be re-enabled. Re-enable it again immediately following
    any T unit soft reset.

    Read result is not valid for first 4.5 seconds after sensor is enabled
    it if was previous disabled.

****************************************************************************/
MTD_STATUS mtdEnableTemperatureSensor
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);

/******************************************************************************
 MTD_STATUS mtdReadTemperature
 (
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_S16 *temperature
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port on this device. API will determine the port number 
             of the temperature sensor for E21X0, X32X0 PHY.
             
 Outputs:
    temperature - Read out average value of the temperature sensor in Celsius.
                  The temperature resolution is 1 degree increment.

                  The temperature sampling is set to average 2^11 samples
                  at a period of approximately 2.2ms per sample.
                  
                  Temperature range: -75C to +180C

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function reads the C Unit temperature sensor for X32X0, X33X0, E20X0
    and Tunit temperature sensor for E21X0. To get the MDIO port number of 
    the temperature sensor is located, mtdGetTempSensorMDIOPort() is called.

 Side effects:
    None

 Notes/Warnings:
    For X32X0, X33X0, E20X0, the C Unit temperature sensor needs to be enabled 
    by calling mtdEnableTemperatureSensor() before using this function.

    For E21X0, the temperature sensor is shared with the T unit processor.

    Please wait at least 4.5 seconds after the temperature sensor is enabled 
    before calling this API the very first time.
******************************************************************************/
MTD_STATUS mtdReadTemperature
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_S16 *temperature
);

/******************************************************************************
 MTD_STATUS mtdCunitSwResetLeaveCopperLinkUp
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port
 )

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Performs a software reset on one particular port's C Unit. This function
    contains a special workaround to keep the T unit copper link from
    dropping. It should only be called in very specific circumstances and
    as a general rule mtdCunitSwReset() is preferred to be used.

    Retain bits will keep the value that has been written to them. Non-
    retain bits will be reset to the hardware reset state.

    This bit is self clearing once the reset has been complete it will
    return to 0.

 Side effects:
    None

 Notes/Warnings:
    Software resets only the C Unit. The T Unit has its own software reset,
    use mtdSoftwareReset(), or hardware reset the T Unit.

    Note below are for E21X0 devices only:

    This function should NOT be used on the E21X0 device when changing the
    mactype. The new mactype and software reset should be issued in the
    same write on E21X0 devices. When changing the mactype and doing a
    software reset, different sequencing needs to be done than this function
    provides (this function does only a software reset).

    E2140/E2180 when MACTYPE is DXGMII or QXGMII, cannot use the bit 15
    software reset, and instead should use bit 4 port software
    reset. This function checks for that case and uses the correct bit.

    Also, E21X0 devices should use a different register for reading and writing
    CUNIT port control. This function also handles that.

******************************************************************************/
MTD_STATUS mtdCunitSwResetLeaveCopperLinkUp
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);


#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MTDDIAG_H */
