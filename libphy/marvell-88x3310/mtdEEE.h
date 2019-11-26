/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions and global data for
higher-level functions using MDIO access to control and read 
status of the energy efficient ethernet (EEE) functions of the 
Marvell 88X32X0, 88X33X0, 88E20X0 and 88E21X0 ethernet PHYs.
********************************************************************/
#ifndef MTDEEE_H
#define MTDEEE_H

#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

/******************************************************************************
MTD_STATUS mtdGetLPIStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *latchedValue,
    OUT MTD_U16 *currentValue
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    latchedValue - the value of the first read of PCS status1 register
    currentValue - the value of the second read of PCS status1 register

 Returns:
    MTD_OK if query was successful, or MTD_FAIL if it was not

 Description:
    Reads the PCS status1 register (3.1) twice and returns the results of
    both reads. The value of the first read is returned in latchedValue and
    the value of the second read is returned in currentValue. These values
    should then be used with other functions to test for changes in status.

 Side effects:
    None.

 Notes/Warnings:
    The functions that will use the latchedValue are
    mtdGetTxLPIReceived()
    mtdGetRxLPIReceived()
    The functions that will use the currentValue are
    mtdGetTxLPIIndication()
    mtdGetRxLPIIndication()

    Note that register also contains the latched PCS receive link status (3.1.2)
    Calling this function will clear the latched value, similarly if another
    management function reads this register, the latched EEE LPI received status
    bits will be cleared.
******************************************************************************/
MTD_STATUS mtdGetLPIStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *latchedValue,
    OUT MTD_U16 *currentValue
);

/******************************************************************************
MTD_STATUS mtdGetTxLPIReceived
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 latchedValue,
    OUT MTD_BOOL *lpiReceived
);


 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    latchedValue - the value of the first read of PCS status1 register as read
        by mtdGetLPIStatus()

 Outputs:
    txlpiReceived - MTD_TRUE - Tx PCS has received LPI.
                  MTD_FALSE - has not received LPI.

 Returns:
    MTD_FAIL if an error occurred, MTD_OK otherwise

 Description:
    Tests the "latched value" of 3.1.11 as read previously by mtdGetLPIStatus()
    and returns MTD_TRUE if PCS Tx has received an LPI since the last time
    it was checked, or a MTD_FALSE if no PCS Tx LPI has been received.

 Side effects:
    None.

 Notes/Warnings:
    Call mtdGetLPIStatus() to get latchedValue to pass into this function.

******************************************************************************/
MTD_STATUS mtdGetTxLPIReceived
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 latchedValue,
    OUT MTD_BOOL *txlpiReceived
);

/******************************************************************************
MTD_STATUS mtdGetRxLPIReceived
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 latchedValue,
    OUT MTD_BOOL *rxlpiReceived
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    latchedValue - the value of the first read of PCS status1 register

 Outputs:
    rxlpiReceived - MTD_TRUE - Rx PCS has received LPI.
                  MTD_FALSE - has not received LPI.

 Returns:
    MTD_FAIL if an error occurred, MTD_OK otherwise

 Description:
    Tests the "latched value" of 3.1.10 as read previously by mtdGetLPIStatus()
    and returns MTD_TRUE if PCS Rx has received an LPI since the last time
    it was checked, or a MTD_FALSE if no PCS Rx LPI has been received in 
    rxlpiReceived.

 Side effects:
    None.

 Notes/Warnings:
    Call mtdGetLPIStatus() to get latchedValue to pass into this function.

******************************************************************************/
MTD_STATUS mtdGetRxLPIReceived
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 latchedValue,
    OUT MTD_BOOL *rxlpiReceived
);

/******************************************************************************
MTD_STATUS mtdGetTxLPIIndication
(
 IN MTD_DEV_PTR devPtr,
 IN MTD_U16 currentValue,
 OUT MTD_BOOL *txlpiIndication
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    currentValue - the value of the second read of PCS status1 register

 Outputs:
    txlpiIndication - MTD_TRUE if currently PCS Tx is receiving LPI
                      MTD_FALSE if not

 Returns:
    MTD_FAIL if an error occurred, MTD_OK otherwise

 Description:
    Tests the "current value" of 3.1 as read previously by mtdGetLPIStatus()
    and returns MTD_TRUE if PCS Tx is receiving an LPI currently and
    MTD_FALSE otherwise in txlpiIndiciation

 Side effects:
    None.

 Notes/Warnings:
    Call mtdGetLPIStatus() to get currentValue to pass into this function.

******************************************************************************/
MTD_STATUS mtdGetTxLPIIndication
(
 IN MTD_DEV_PTR devPtr,
 IN MTD_U16 currentValue,
 OUT MTD_BOOL *txlpiIndication
);

/******************************************************************************
MTD_STATUS mtdGetRxLPIIndication
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 currentValue,
    OUT MTD_BOOL *rxlpiIndication
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    currentValue - the value of the second read of PCS status1 register

 Outputs:
    rxlpiIndication - MTD_TRUE if currently PCS Rx is receiving LPI
                      MTD_FALSE if not

 Returns:
    MTD_FAIL if an error occurred, MTD_OK otherwise


 Description:
    Tests the "current value" of 3.1 as read previously by mtdGetLPIStatus()
    and returns MTD_TRUE if PCS Rx is receiving an LPI currently and
    MTD_FALSE otherwise in rxlpiIndiciation

 Side effects:
    None.

 Notes/Warnings:
    Call mtdGetLPIStatus() to get currentValue to pass into this function.

******************************************************************************/
MTD_STATUS mtdGetRxLPIIndication
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 currentValue,
    OUT MTD_BOOL *rxlpiIndication
);

/******************************************************************************
MTD_U16 mtdWakeErrorCount(MTD_DEV_PTR devPtr,
                                   MTD_U16 port)

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    wakeErrCount - 3.22 register value

 Returns:
    MTD_FAIL if an error occurred, MTD_OK otherwise

 Description:
    Reads the register 3.22 and returns the wake error count value since
    the last time the register was read/cleared.

 Side effects:
    None.

 Notes/Warnings:
    This register clears when read.

******************************************************************************/
MTD_STATUS mtdWakeErrorCount
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *wakeErrCount
);


/*******************************************************************
 Enabling speeds for autonegotiation
 Reading speeds enabled for autonegotation
 Set/get pause advertisement for autonegotiation
 Other Autoneg-related Control and Status (restart,disable/enable,
 force master/slave/auto, checking for autoneg resolution, etc.)
 *******************************************************************/
#define MTD_EEE_NONE           ((MTD_U16)0x0000) /* No speeds to be advertised */
#define MTD_EEE_100M           ((MTD_U16)0x0002) /* 100BASE-TX EEE to be advertised */
#define MTD_EEE_1G             ((MTD_U16)0x0004) /* 1000BASE-T EEE to be advertised */
#define MTD_EEE_10G            ((MTD_U16)0x0008) /* 10GBASE-T EEE  to be advertised */
#define MTD_EEE_2P5G           ((MTD_U16)0x0010) /* 2.5GBASE-T EEE  to be advertised 88X33x0/E20x0/E21x0 devices only */
#define MTD_EEE_5G             ((MTD_U16)0x0020) /* 5GBASE-T EEE  to be advertised  88X33x0/E20x0/E21x0 devices only */
#define MTD_EEE_ALL            (MTD_EEE_100M | MTD_EEE_1G | MTD_EEE_10G) /* 88X32X0 */
#define MTD_EEE_ALL_33X0       (MTD_EEE_100M | MTD_EEE_1G | MTD_EEE_10G | MTD_EEE_2P5G | MTD_EEE_5G) /* X33x0/E20x0/E21x0 devices */
#define MTD_EEE_ALL_20X0_21X0  (MTD_EEE_100M | MTD_EEE_1G| MTD_EEE_2P5G | MTD_EEE_5G) /* E20x0/E21x0 devices */

/******************************************************************************
 MTD_STATUS mtdGetEEESupported
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_U16 *EEE_support_bits,     
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    EEE_support_bits - bits set according to which EEE speeds are supported as
    indicated in 3.20 bits 3,2,1 and 3.21 bits 1,0. One or more bits set according 
    to the defines above.

 Returns:
    MTD_OK or MTD_FAIL, if query succeeded or failed

 Description:
    This function returns the EEE speeds that are supported as indicated in 
    3.20 bits 3,2,1 and 3.21 bit 1,0.

 Side effects:
    None.

 Notes/Warnings:
    None.

******************************************************************************/
MTD_STATUS mtdGetEEESupported
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *EEE_support_bits
);

/******************************************************************************
 MTD_STATUS mtdAdvert_EEE
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 EEE_advertise_bits, 
     IN MTD_BOOL anRestart
 );

 Inputs: 
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    EEE_advertise_bits - EEE speeds to be advertised during auto-negotiation. One or more 
                 of the following (bits logically OR together):
                MTD_EEE_NONE 
                MTD_EEE_100M
                MTD_EEE_1G
                MTD_EEE_10G
                MTD_EEE_ALL

                For 88X33x0/E20x0/E21x0 devices, following additional bits are valid:
                MTD_EEE_2P5G
                MTD_EEE_5G
                MTD_EEE_ALL_33X0
                MTD_EEE_ALL_20X0_21X0
                                
    anRestart - this takes the value of MTD_TRUE or MTD_FALSE and indicates 
                if auto-negotiation should be restarted following the EEE speed 
                advertisement change. If this is MTD_FALSE, the change will not
                take effect until AN is restarted. 

 Outputs:
    None

 Returns:
    MTD_OK if action was successfully taken, MTD_FAIL if not

    MTD_FAIL on 88X32X0 devices that set 2.5/5G EEE advertisement bits

 Description:    
    Sets the EEE auto negotiation advertisement register 7.60 to advertise the
    10GBASE-T, 1000BASE-T, and 100BASE-TX EEE capability during auto-negotiation.

    The function takes in a 16 bit value and sets the appropriate bits in MMD
    7 to have those EEE speeds advertised.

    Additionally, for 88X3X0/E20X0/E21X0 devies, sets advertisement of 2.5G and/or 5G 
    EEE in 7.003E, which is advertised during training.

    If anRestart is MTD_TRUE, an auto-negotiation restart is issued making the change 
    immediate. If anRestart is MTD_FALSE, the change will not take effect until the 
    next time auto-negotiation restarts.

 Side effects:
    None

 Notes/Warnings:
    An autonegotiation restart is needed before the new settings will be used.

    If the link is up and anRestart is MTD_TRUE, the link will drop.

    Devices without 2.5/5G ability that set 2.5/5G EEE advertisement will result
    in MTD_FAIL being returned.

******************************************************************************/
MTD_STATUS mtdAdvert_EEE
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 EEE_advertise_bits, 
    IN MTD_BOOL anRestart
);


/******************************************************************************
 MTD_STATUS mtdGetAdvert_EEE
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_U16 *EEE_advertise_bits,     
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    EEE_advertise_bits - bits set according to which EEE speeds are currently being
        advertised. One or more bits set according to the defines above
        in mtdAdvert_EEE().

 Returns:
    MTD_OK or MTD_FAIL, if query succeeded or failed

 Description:
    This function returns the EEE speeds that have been advertised.

 Side effects:

 Notes/Warnings:
    EEE speeds advertised don't take effect until auto-negotiation is
    restarted.

******************************************************************************/
MTD_STATUS mtdGetAdvert_EEE
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *EEE_advertise_bits     
);


/******************************************************************************
 MTD_STATUS mtdGetLP_Advert_EEE
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_U16 *LP_EEE_advertise_bits,     
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    LP_EEE_advertise_bits - bits set according to which EEE speeds were
        advertised by the link partner and indicated in 7.61.3:1 and
        7.003F.1:0. One or more bits set according to the defines above in 
        mtdAdvert_EEE().

 Returns:
    MTD_OK or MTD_FAIL, if query succeeded or failed

 Description:
    This function returns the EEE speeds that were advertised by the link 
    partner and indicated in EEE link partner ability register 7.61 bits 32,1
    and returns the value.

    For 88X3X0/E20X0 devices, the function additionally returns LP bits
    for EEE as advertised by LP during training and reported in 7.003F
    for 2.5/5G.

 Side effects:

 Notes/Warnings:
    This function must be called after the autonegotiation process has been
    completed on 88X32X0 devices (non-2.5/5G devices). 

    On 88X3X0/E20X0 devices it must be called after link is up (EEE bits for
    2.5/5G are exchanged during training).

******************************************************************************/
MTD_STATUS mtdGetLP_Advert_EEE
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *LP_EEE_advertise_bits     
);

/******************************************************************************
 MTD_STATUS mtdGetEEEResolution
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_U16 *EEE_resolved_bits,     
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    EEE_resolved_bits - bits set according to which EEE speeds are
        advertised by both the local device and the link partner as indicated 
        in 7.60.3:1 and 7.61.3:1. One or more bits set according to the defines 
        above in mtdAdvert_EEE().

        Additional bits advertised by local device and link partner as
        indicated in 7.003E.1:0 and 7.003F.1:0 for 88X33x0/E20x0/E21x0 devices
        will be made available to indicate if 2.5/5G EEE is supported by
        both local device and link partner.

 Returns:
    MTD_OK or MTD_FAIL, if query succeeded or failed

 Description:
    This function returns the EEE speeds that were advertised by both the local 
    device and the link partner as indicated in 7.60.3:1 and 7.61.3:1 (the 
    logical AND of these bits, indicating which EEE speeds both ends had
    in common).

    Additionally, for 88X33x0/E20x0/E21x0 devices, 2.5/5G EEE bits are available
    indicating if local device and link partner both support 2.5/5G EEE
    by reading 7.003E.1:0 and 7.003F.1:0 and returning the result.

 Side effects:

 Notes/Warnings:
    This function must be called after the autonegotiation process has been
    completed on 88X32X0 devices (non-2.5/5G devices). 

    On 88X3X0/E20X0 devices it must be called after link is up (EEE bits for
    2.5/5G are exchanged during training).


******************************************************************************/
MTD_STATUS mtdGetEEEResolution
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *EEE_resolved_bits     
);

#define MTD_EEE_MODE_DISABLE              ((MTD_U8)0x00) /* Disables EEE mode altogether */
#define MTD_EEE_MODE_ENABLE_NO_LEGACY     ((MTD_U8)0x01) /* Enables EEE without the legacy buffer (MAC generates LPI) */
#define MTD_EEE_MODE_ENABLE_WITH_LEGACY   ((MTD_U8)0x02) /* Enables EEE using the legacy buffer (PHY generates LPI) */

#define MTD_EEE_LL_EXIT_TIMER 1 /* Set to 1 to have mtdEeeBufferConfig() call mtdEeeBufferConfigLL() */
                                /* using MTD_TRUE for Use0p5usecResolution */
                                /* Set to 0 for old behavior (using 1 usec resolution) */

/******************************************************************************
 MTD_STATUS mtdEeeBufferConfig
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U8 EEE_Mode_Control, 
     IN MTD_U8 XGMII_Enter_Timeout, 
     IN MTD_U8 GMII_Enter_Timeout, 
     IN MTD_U8 MII_Enter_Timeout, 
     IN MTD_U8 XGMII_Exit_Timeout, 
     IN MTD_U8 GMII_Exit_Timeout, 
     IN MTD_U8 MII_Exit_Timeout, 
     IN MTD_U8 IPG_Length
 );



 Inputs: 
     See mtdEeeBufferConfigLL for details 

 Outputs:
    None

 Returns:
    MTD_OK if action was successfully taken, MTD_FAIL if not

 Description:
    This function is left for backward compatibility. It is equivalent
    to calling mtdEeeBufferConfigLL() with Use0p5usecResolution set to
    either:
        MTD_FALSE (to use 1 usec resolution)
        MTD_TRUE (to use 0.5 usec resolution)

   based on the compile switch MTD_EEE_LL_EXIT_TIMER.
        

 Side effects:
    None

 Notes/Warnings:
    See mtdEeeBufferConfigLL for details.

******************************************************************************/
MTD_STATUS mtdEeeBufferConfig
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U8 EEE_Mode_Control, 
    IN MTD_U8 XGMII_Enter_Timeout, 
    IN MTD_U8 GMII_Enter_Timeout, 
    IN MTD_U8 MII_Enter_Timeout, 
    IN MTD_U8 XGMII_Exit_Timeout, /* ignored on X33x0/E20x0/E21x0 devices */
    IN MTD_U8 GMII_Exit_Timeout, 
    IN MTD_U8 MII_Exit_Timeout, 
    IN MTD_U8 IPG_Length
);

/******************************************************************************
 MTD_STATUS mtdEeeBufferConfigLL
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U8 EEE_Mode_Control, 
     IN MTD_U8 XGMII_Enter_Timeout, 
     IN MTD_U8 GMII_Enter_Timeout, 
     IN MTD_U8 MII_Enter_Timeout, 
     IN MTD_U8 XGMII_Exit_Timeout, 
     IN MTD_U8 GMII_Exit_Timeout, 
     IN MTD_U8 MII_Exit_Timeout, 
     IN MTD_U8 IPG_Length,
     IN MTD_U8 Use0p5usecResolution
 );



 Inputs: 
     devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
     port - MDIO port address, 0-31
     EEE_Mode_Control - One of the following:
        MTD_EEE_MODE_DISABLE, to disable EEE
        MTD_EEE_MODE_ENABLE_NO_LEGACY, for MACs which are capable of generating LPI
        MTD_EEE_MODE_ENABLE_WITH_LEGACY, for MACs which are not capable of generating LPI
                                          NOTE: this setting not allowed if MACSEC
                                          exists in the PHY. MTD_FAIL will
                                          be returned if the PHY contains MACSEC
                                          capability. Use mtdMACSECEeeBufferConfig()
                                          instead.
     
     XGMII_Enter_Timeout - Sets the delay in microseconds from the start of idle
       until the buffer begins sending Low Power Idle in 10G mode. Default is 26us.
       0-255(127). Set to 0 or 26 to get default.

     GMII_Enter_Timeout - Sets the delay in microseconds from the start of idle
       until the buffer begins sending Low Power Idle in 1G mode. Default is 18us
       0-255(127), Set to 0 or 18 to get default.

     MII_Enter_Timeout - Sets the delay in microseconds from the start of idle
       until the buffer begins sending Low Power Idle in 100M mode. Default is 32us.
       0-255(127), Set to 0 or 32 to get default.

     XGMII_Exit_Timeout - Sets the delay in microseconds from the first frame 
       received until the buffer sends the frame in 10G mode. Default is 8us.
       0-255(127), Set to 0 or 32 to get default. NOTE: This parameter is not adjustable
       on X33x0/E20x0/E21x0 PHYs. XGMII_Exit_Timeout is ignored on these devices and the exit timer
       is set to 8, 15 and 30 microseconds for 10G, 5G and 2.5GBASE-T by firmware.

       If Use0p5usecResolution is passed as MTD_EEE_0P5USEC_TIMER_RESOLUTION and that
       feature is available on the PHY, the 10G exit timer is set to 7.5 usec
       and the 2.5G exit timer is set to 29.5 usec.

     GMII_Exit_Timeout - Sets the delay in microseconds from the first frame 
       received until the buffer sends the frame in 1G mode . Default is 18us.
       0-255(127), Set to 0 or 18 to get default. 

     MII_Exit_Timeout - Sets the delay in microseconds from the first frame 
       received until the buffer sends the frame in 100M mode .Default is 32us.
       0-255(127), Set to 0 or 32 to get default.

     IPG_Length - number of bytes of IPG sent between frames while buffer is
       being emptied. Default is 12.
       0-255(127), Set to 0 or 12 to get default.

     Use0p5usecResolution - 
        MTD_FALSE - Uses 1 usec resolution for EEE timers to the PHY
        MTD_TRUE - Uses 0.5 usec resolution for EEE timers to the PHY 
                   if the feature is supported by the firmware. This is only available 
                   on X33X0/E20X0 and E21X0 PHYs and on certain firmware versions.
                   Specifying this will result in slightly lower latency on 10G 
                   and 2.5G speeds when EEE is enabled. When this flag is
                   set, the hardware is configured to use this value
                   if the firmware supports it, in which case the XGMII
                   Exit timer for 10G will be 7.5 usec and for 2.5G will
                   be 29.5 usec.

 Outputs:
    None

 Returns:
    MTD_OK if action was successfully taken, MTD_FAIL if not

 Description:
    Enables EEE mode in the H unit so that LPI symbols may be passed to the 
    T unit.
    
    Optionally enables the EEE Legacy Mode buffer so that EEE may be used with a 
    MAC that is not capable of sourcing the Low Power Idle symbols. During periods 
    without transmit activity the EEE buffer will convert idle symbols to 
    low power idle symbols. The buffer will wait 'enter timer' microseconds 
    and begin sending LPI. Any frame received will be buffered until the exit 
    from LPI. Upon receiving a frame the buffer will send Idle for 'exit timer'
    microseconds before sending the frame. This option is for PHYs without
    MACSEC capability.

    Auto-negotiation has to be restarted for configured EEE mode to take effect.

 Side effects:
    None

 Notes/Warnings:
    If EEE will not be enabled, be certain to turn off advertisement by calling
    mtdAdvert_EEE() and restarting AN, otherwise the link may not be stable.

    Usage Notes:

    The calls:
    mtdEeeBufferConfig(devPtr,port,MTD_EEE_MODE_DISABLE,0,0,0,0,0,0,0)
    will disable the EEE and set the timeouts/IPG to the suggested values.

    mtdEeeBufferConfig(devPtr,port,MTD_EEE_MODE_ENABLE_NO_LEGACY,0,0,0,0,0,0,0)
    will enable the EEE and set the timeouts/IPG to the suggested values. This
    is the call for a MAC which supports sending its own LPI signalling.

    mtdEeeBufferConfig(devPtr,port,MTD_EEE_MODE_ENABLE_WITH_LEGACY,0,0,0,0,0,0,0)
    will enable the EEE and set the timeouts/IPG to the suggested values. This
    is the call for a MAC which does not support sending LPI signalling, and
    is requesting the PHY to do it when the internal buffer is empty.

    Any non-zero value will overwrite the default/suggested value.

    Whether Use0p5usecResolution is 0 or 1, the input timers should be passed
    in 1 usec resolution. The API will translate between 1 sec resolution
    and 0.5 usec resolution only if the PHY being configured supports this
    feature and is configured to use this feature.

    When Use0p5usecResolution is MTD_TRUE, and that feature is available on the PHY,
    the range of 0...255 is reduced to 0...127. If you require the larger
    range, you must use 1 usec resolution.

******************************************************************************/
MTD_STATUS mtdEeeBufferConfigLL
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U8 EEE_Mode_Control, 
    IN MTD_U8 XGMII_Enter_Timeout, 
    IN MTD_U8 GMII_Enter_Timeout, 
    IN MTD_U8 MII_Enter_Timeout, 
    IN MTD_U8 XGMII_Exit_Timeout, /* ignored on X33x0/E20x0/E21x0 devices */
    IN MTD_U8 GMII_Exit_Timeout, 
    IN MTD_U8 MII_Exit_Timeout, 
    IN MTD_U8 IPG_Length, 
    IN MTD_BOOL Use0p5usecResolution 
);



/******************************************************************************
 MTD_STATUS mtdGetEeeBufferConfig
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_U8 *EEE_Mode_Control, 
     OUT MTD_U8 *XGMII_Enter_Timeout, 
     OUT MTD_U8 *GMII_Enter_Timeout, 
     OUT MTD_U8 *MII_Enter_Timeout, 
     OUT MTD_U8 *XGMII_Exit_Timeout, 
     OUT MTD_U8 *GMII_Exit_Timeout, 
     OUT MTD_U8 *MII_Exit_Timeout, 
     OUT MTD_U8 *IPG_Length 
 );


 Inputs: 
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    EEE_Mode_Control - One of the following:
       MTD_EEE_MODE_DISABLE, to disable EEE
       MTD_EEE_MODE_ENABLE_NO_LEGACY, for MACs which are capable of generating LPI
       MTD_EEE_MODE_ENABLE_WITH_LEGACY, for MACs which are not capable of generating LPI
    
    XGMII_Enter_Timeout - delay in microseconds from the start of idle
      until the buffer begins sending Low Power Idle in 10G mode. 
    
    GMII_Enter_Timeout - delay in microseconds from the start of idle
      until the buffer begins sending Low Power Idle in 1G mode. 
    
    MII_Enter_Timeout - delay in microseconds from the start of idle
      until the buffer begins sending Low Power Idle in 100M mode. 
    
    XGMII_Exit_Timeout - delay in microseconds from the first frame 
      received until the buffer sends the frame in 10G mode. 
      NOTE: This parameter is not adjustable on X33x0/E20x0/E21x0 PHYs. 
      The exit timer is set to 8, 15 and 30 microseconds for 10G, 5G and 2.5GBASE-T 
      by firmware. These settings can be verified by checking after link is up.

      Note: if the PHY is able to use 0.5 usec resolution and is configured to use
      it, the value returned by this function will be slightly off for the 
      10G and 2.5G exit timer, which will be set by the PHY to 7.5 usec and
      29.5 usec respectively. When read you will get 7 and 29 respectively instead
      as a result of the integer division by 2 of the register value programmed.
    
    GMII_Exit_Timeout - delay in microseconds from the first frame 
      received until the buffer sends the frame in 1G mode. 
    
    MII_Exit_Timeout - delay in microseconds from the first frame 
      received until the buffer sends the frame in 100M mode.
    
    IPG_Length - number of bytes of IPG sent between frames while buffer is
      being emptied.

 Returns:
    MTD_OK if query was successful, MTD_FAIL if not

 Description:
    This function returns the EEE Legacy Mode buffer configurations as set in
    31.F004 to 31.F006 and 1.C033 by call to mtdEeeBufferConfig().

 Side effects:
    None

 Notes/Warnings:
    This function should only be called to get the EEE configuration when
    MacSec is disabled/bypassed. Use mtdGetMACSECEeeBufferConfig() if
    using MacSec with EEE.

******************************************************************************/
MTD_STATUS mtdGetEeeBufferConfig
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U8 *EEE_Mode_Control, 
    OUT MTD_U8 *XGMII_Enter_Timeout, 
    OUT MTD_U8 *GMII_Enter_Timeout, 
    OUT MTD_U8 *MII_Enter_Timeout, 
    OUT MTD_U8 *XGMII_Exit_Timeout, 
    OUT MTD_U8 *GMII_Exit_Timeout, 
    OUT MTD_U8 *MII_Exit_Timeout, 
    OUT MTD_U8 *IPG_Length 
);


/******************************************************************************
 MTD_STATUS mtdMACSECEeeBufferConfig
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U8 EEE_Mode_Control, 
     IN MTD_U8 XGMII_Enter_Timeout, 
     IN MTD_U8 GMII_Enter_Timeout, 
     IN MTD_U8 MII_Enter_Timeout, 
     IN MTD_U8 XGMII_Exit_Timeout, 
     IN MTD_U8 GMII_Exit_Timeout, 
     IN MTD_U8 MII_Exit_Timeout, 
     IN MTD_BOOL Force_Sys_LPI, 
     IN MTD_BOOL Force_Wre_LPI 
 );


 Inputs: 
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

    EEE_Mode_Control - One of the following:
       MTD_EEE_MODE_DISABLE, to disable EEE
       MTD_EEE_MODE_ENABLE_NO_LEGACY, for MACs which are capable of generating LPI
       MTD_EEE_MODE_ENABLE_WITH_LEGACY, for MACs which are not capable of generating LPI

    XGMII_Enter_Timeout - Sets the delay in 100ns steps from the start of idle
      until the buffer begins sending Low Power Idle in 10G mode. Default is
      0xFF (26 us). 0-255, set to 0 or 0xFF to get default setting.
      
    GMII_Enter_Timeout - Sets the delay in microseconds from the start of idle
      until the buffer begins sending Low Power Idle in 1G mode. Default is
      18 us. 0-255. Set to 0 or 18 to get default setting.

    MII_Enter_Timeout - Sets the delay in microseconds from the start of idle
      until the buffer begins sending Low Power Idle in 100M mode. Default is
      32 us. 0-255. Set to 0 or 32 to get default setting.

    XGMII_Exit_Timeout - Sets the delay in 100ns steps from the first frame 
      received until the buffer sends the frame in 10G mode. Default is
      0x4B (7.5 us). 0-255, set to 0 or 0x4B to get default setting.

    GMII_Exit_Timeout - Sets the delay in microseconds from the first frame 
      received until the buffer sends the frame in 1G mode. Default is
      18 us. 0-255. Set to 0 or 18 to get default setting.

    MII_Exit_Timeout - Sets the delay in microseconds from the first frame 
      received until the buffer sends the frame in 100M mode. Default is
      32 us. 0-255. Set to 0 or 32 to get default setting.

    Force_Sys_LPI - MTD_TRUE forces LPI symbols towards the System (MAC)

    Force_Wre_LPI - MTD_TRUE forces LPI symbols towards the Wire (PHY)

 Outputs:
    None

 Returns:
    MTD_OK if action was successfully taken, MTD_FAIL if not

 Description:
    This function sets the MACSEC EEE Legacy Mode buffer configurations in 
    31.809C to 31.809F.
    Enables EEE mode in the MACSEC so that LPI symbols may be passed to the 
    T unit.
    Optionally enables the EEE Legacy Mode buffer so that EEE may be used with a 
    MAC that is not capable of sourcing the Low Power Idle symbols. During periods 
    without transmit activity the EEE buffer will convert idle symbols to 
    low power idle symbols. The buffer will wait 'enter timer' microseconds 
    and begin sending LPI. Any frame received will be buffered until the exit 
    from LPI. Upon receiving a frame the buffer will send Idle for 'exit timer'
    microseconds before sending the frame.

 Side effects:
    None

 Notes/Warnings:
    mtdMACSECEeeBufferConfig() is applicable only for the case when MACSEC is enabled,
     (31.F000.13:12 = 11). If MACSEC is not enabled, this function will return MTD_FAIL.

    Per IEEE 802.3 78.1.2.1.2, the EEE Buffer must be disabled for 1 second after 
    initial link up and may then be enabled.
        **This function must be called EVERY time the link transitions from down
        to up for speeds where EEE was resolved as supported after a 1 second delay.
        ** Note that the XGMII_Enter_Timeout and MII_Exit_Timeout timers are set
        in 100ns steps, the other timers are set in 1us steps.

    If EEE is disabled, be certain to turn off advertisement by calling
    mtdAdvert_EEE() and restarting AN, otherwise the link may not be stable.

    Usage Notes:

    The calls
    mtdMACSECEeeBufferConfig(devPtr,port,MTD_EEE_MODE_DISABLE,0,0,0,0,0,0,
                             MTD_FALSE,MTD_FALSE)
    will disable the EEE and set the timeouts to the suggested values.

    mtdMACSECEeeBufferConfig(devPtr,port,MTD_EEE_MODE_ENABLE_NO_LEGACY,0,0,0,0,0,0,
                             MTD_FALSE,MTD_FALSE)
    will enable the EEE and set the timeouts to the suggested values. This
    is the call for a MAC which supports sending its own LPI signalling to/through
    the MACSEC.

    mtdMACSECEeeBufferConfig(devPtr,port,MTD_EEE_MODE_ENABLE_NO_LEGACY,0,0,0,0,0,0,
                             MTD_FALSE,MTD_FALSE)
    will enable the EEE and set the timeouts to the suggested values. This
    is the call for a MAC which does not support sending LPI signalling, and
    is requesting the MACSEC to do it when the MACSEC internal data buffer is 
    empty.

    To force LPI in one direction or the other, change one or both of the above
    MTD_FALSE to MTD_TRUE.

******************************************************************************/
MTD_STATUS mtdMACSECEeeBufferConfig
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U8 EEE_Mode_Control, 
    IN MTD_U8 XGMII_Enter_Timeout, 
    IN MTD_U8 GMII_Enter_Timeout, 
    IN MTD_U8 MII_Enter_Timeout, 
    IN MTD_U8 XGMII_Exit_Timeout, 
    IN MTD_U8 GMII_Exit_Timeout, 
    IN MTD_U8 MII_Exit_Timeout, 
    IN MTD_BOOL Force_Sys_LPI, 
    IN MTD_BOOL Force_Wre_LPI 
);

/******************************************************************************
 MTD_STATUS mtdMACSECEeeBufferConfig5G_2P5G
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U8 FiveG_Enter_Timeout, 
     IN MTD_U8 TwoP5G_Enter_Timeout, 
     IN MTD_U8 FiveG_Exit_Timeout, 
     IN MTD_U8 TwoP5G_Exit_Timeout
 );


 Inputs: 
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

    FiveG_Enter_Timeout - Sets the delay in 100ns steps from the start of idle
      until the buffer begins sending Low Power Idle in 10G mode. Default is
      0xB4 (18 us). 0-255, set to 0 or 0xB4 to get default setting.
      
    TwoP5G_Enter_Timeout - Sets the delay in microseconds from the start of idle
      until the buffer begins sending Low Power Idle in 1G mode. Default is
      18 us. 0-255. Set to 0 or 18 to get default setting.

    FiveG_Exit_Timeout - Sets the delay in 100ns steps from the first frame 
      received until the buffer sends the frame in 10G mode. Default is
      0x96 (15 us). 0-255, set to 0 or 0x96 to get default setting.

    TwoP5G_Exit_Timeout - Sets the delay in microseconds from the first frame 
      received until the buffer sends the frame in 1G mode. Default is
      30 us. 0-255. Set to 0 or 30 to get default setting.

 Outputs:
    None

 Returns:
    MTD_OK if action was successfully taken, MTD_FAIL if not

 Description:
    Modifies the enter/exit timers for 5G/2.5G EEE. Pass 0 for a parameter
    to use the default setting.

    See notes below for usage instructions.

 Side effects:
    None

 Notes/Warnings:
    Use mtdMACSECEeeBufferConfig() first to configure MacSec EEE buffer,
    then call this function only to change the 5G/2.5G Enter/Exit timers
    on X33x0/E20x0/E21x0 devices.

    This function is only applicable to X33x0/E20x0/E21x0 devices.

******************************************************************************/
MTD_STATUS mtdMACSECEeeBufferConfig5G_2P5G
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U8 FiveG_Enter_Timeout, 
    IN MTD_U8 TwoP5G_Enter_Timeout, 
    IN MTD_U8 FiveG_Exit_Timeout, 
    IN MTD_U8 TwoP5G_Exit_Timeout
);

/******************************************************************************
 MTD_STATUS mtdGetMACSECEeeBufferConfig
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_U8 *EEE_Mode_Control, 
     OUT MTD_U8 *XGMII_Enter_Timeout, 
     OUT MTD_U8 *GMII_Enter_Timeout, 
     OUT MTD_U8 *MII_Enter_Timeout, 
     OUT MTD_U8 *XGMII_Exit_Timeout, 
     OUT MTD_U8 *GMII_Exit_Timeout, 
     OUT MTD_U8 *MII_Exit_Timeout, 
     OUT MTD_BOOL *Force_Sys_LPI, 
     OUT MTD_BOOL *Force_Wre_LPI 
 );


 Inputs: 
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    EEE_Mode_Control - One of the following:
       MTD_EEE_MODE_DISABLE, to disable EEE
       MTD_EEE_MODE_ENABLE_NO_LEGACY, for MACs which are capable of generating LPI
       MTD_EEE_MODE_ENABLE_WITH_LEGACY, for MACs which are not capable of generating LPI

    XGMII_Enter_Timeout - delay in 100ns steps from the start of idle
      until the buffer begins sending Low Power Idle in 10G mode. 
      
    GMII_Enter_Timeout - delay in microseconds from the start of idle
      until the buffer begins sending Low Power Idle in 1G mode. 

    MII_Enter_Timeout - delay in microseconds from the start of idle
      until the buffer begins sending Low Power Idle in 100M mode. 

    XGMII_Exit_Timeout - delay in 100ns steps from the first frame 
      received until the buffer sends the frame in 10G mode. 

    GMII_Exit_Timeout - delay in microseconds from the first frame 
      received until the buffer sends the frame in 1G mode. 

    MII_Exit_Timeout - delay in microseconds from the first frame 
      received until the buffer sends the frame in 100M mode. 

    Force_Sys_LPI - MTD_TRUE/MTD_FALSE

    Force_Wre_LPI - MTD_TRUE/MTD_FALSE

 Returns:
    MTD_OK if query was successful, MTD_FAIL if not

 Description:
    This function returns the MACSEC EEE Mode buffer configurations as set in 
    31.809C to 31.809F by call to mtdMACSECEeeBufferConfig()

 Side effects:
    None

 Notes/Warnings:
    MACSEC must be enabled to read the configuration. This function will return
    MTD_FAIL if MACSEC is disabled (31.F000.13:12 is not 11b).

******************************************************************************/
MTD_STATUS mtdGetMACSECEeeBufferConfig
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U8 *EEE_Mode_Control, 
    OUT MTD_U8 *XGMII_Enter_Timeout, 
    OUT MTD_U8 *GMII_Enter_Timeout, 
    OUT MTD_U8 *MII_Enter_Timeout, 
    OUT MTD_U8 *XGMII_Exit_Timeout, 
    OUT MTD_U8 *GMII_Exit_Timeout, 
    OUT MTD_U8 *MII_Exit_Timeout, 
    OUT MTD_BOOL *Force_Sys_LPI, 
    OUT MTD_BOOL *Force_Wre_LPI 
);


/******************************************************************************
 MTD_STATUS mtdGetMACSECEeeBufferConfig5G_2P5G
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_U8 *FiveG_Enter_Timeout, 
     OUT MTD_U8 *TwoP5G_Enter_Timeout, 
     OUT MTD_U8 *FiveG_Exit_Timeout, 
     OUT MTD_U8 *TwoP5G_Exit_Timeout
 );


 Inputs: 
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    FiveG_Enter_Timeout - delay in 100ns steps from the start of idle
      until the buffer begins sending Low Power Idle in 10G mode. 
      
    TwoP5G_Enter_Timeout - delay in microseconds from the start of idle
      until the buffer begins sending Low Power Idle in 1G mode. 

    FiveG_Exit_Timeout - delay in 100ns steps from the first frame 
      received until the buffer sends the frame in 10G mode. 

    TwoP5G_Exit_Timeout - delay in microseconds from the first frame 
      received until the buffer sends the frame in 1G mode. 

 Returns:
    MTD_OK if action was successfully taken, MTD_FAIL if not

 Description:
    Reads the 5G/2.5G enter/exit timer values from the MacSec
    EEE buffer configuration registers.

 Side effects:
    None

 Notes/Warnings:
    This function is only applicable to X33x0/E20x0/E21x0 devices.

******************************************************************************/
MTD_STATUS mtdGetMACSECEeeBufferConfig5G_2P5G
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U8 *FiveG_Enter_Timeout, 
    OUT MTD_U8 *TwoP5G_Enter_Timeout, 
    OUT MTD_U8 *FiveG_Exit_Timeout, 
    OUT MTD_U8 *TwoP5G_Exit_Timeout
);

/******************************************************************************
MTD_STATUS mtdEeeEnableOverrideMode 
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
    None

 Description:
    Enable EEE Override Mode. This bit enables the Energy Efficient Ethernet
    Override function which allows the PHY to disable EEE advertisement for
    cases where the link or link partner cannot support reliable EEE operation.

 Side effects:
    None.

 Notes/Warnings:


******************************************************************************/
MTD_STATUS mtdEeeEnableOverrideMode 
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port  
);


/******************************************************************************
MTD_STATUS mtdEeeDisableOverrideMode 
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
    None

 Description:
    Disables EEE Override Mode. This bit disables the Energy Efficient Ethernet
    Override function which allows the PHY to disable EEE advertisement for
    cases where the link or link partner cannot support reliable EEE operation.

 Side effects:
    None.

 Notes/Warnings:
    None

******************************************************************************/
MTD_STATUS mtdEeeDisableOverrideMode 
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port  
);



#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MTDEEE_H */
