/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions prototypes and global defines/data for
higher-level functions that are shared by the H Unit (host/interface
to the MAC) and the X Unit (media/fiber interface) for the 
Marvell 88X32X0, 88X33X0, 88E20X0 and 88E21X0 ethernet PHYs.
********************************************************************/
#ifndef MTDHXUNIT_H
#define MTDHXUNIT_H
#if C_LINKAGE
#if defined __cplusplus 
    extern "C" { 
#endif 
#endif

/******************************************************************************
 SERDES control (common)
******************************************************************************/

#define MTD_SERDES_SHORT_REACH (1)
#define MTD_SERDES_LONG_REACH  (0)
/******************************************************************************
 MTD_STATUS mtdSetSerdesOverrideReach
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit,
     IN MTD_BOOL reachFlag
 );

 Inputs:
    devPtr - pointer to host's private data
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
                being set
    reachFlag - MTD_SERDES_SHORT_REACH or MTD_SERDES_LONG_REACH

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Sets the H or X unit serdes to operate in short or long reach mode.

    The next time the serdes link drops and comes back up, it will use the
    new setting. To force it to use the new setting, after changing
    this setting, do a software reset on the T unit or call 
    mtdRerunSerdesAutoInitialization() to have the serdes re-initialized.

 Side effects:
    None

 Notes/Warnings:
    This is a retain bit and will be retained between software resets.

******************************************************************************/
MTD_STATUS mtdSetSerdesOverrideReach
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    IN MTD_BOOL reachFlag
);

/******************************************************************************
 MTD_STATUS mtdGetSerdesOverrideReach
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit,
     OUT MTD_BOOL *reachFlag
 );

 Inputs:
    devPtr - pointer to host's private data
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
                being set

 Outputs:
    reachFlag - MTD_SERDES_SHORT_REACH or MTD_SERDES_LONG_REACH

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Reads the serdes control/status register and returns the value
    of the short reach bit for either the H unit or the X unit.

 Side effects:
    None

 Notes/Warnings:

******************************************************************************/
MTD_STATUS mtdGetSerdesOverrideReach
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    OUT MTD_BOOL *reachFlag
);

#define MTD_SERDES_DISABLE_AUTO_INIT (1)
#define MTD_SERDES_ENABLE_AUTO_INIT  (0)
/******************************************************************************
 MTD_STATUS mtdSetSerdesAutoInitialization
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_BOOL autoInitFlag
 );

 Inputs:
    devPtr - pointer to host's private data
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
                being set
    autoInitFlag - MTD_SERDES_DISABLE_AUTO_INIT or MTD_SERDES_ENABLE_AUTO_INIT

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Calling this function disables BOTH H unit and X unit serdes auto-
    initialization behavior in the T unit processor. 

    Only call this function if the host plans to completely initialize
    the serdes for the correct speed after each speed change.

 Side effects:
    None

 Notes/Warnings:
    Normally this function should not be called. The default behavior of
    the PHY is to allow the T unit processor to apply the correct 
    initialization sequence after any link speed change of the serdes.

    This bit is a retain bit and will be retained between software resets.

******************************************************************************/
MTD_STATUS mtdSetSerdesAutoInitialization
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL autoInitFlag
);

/******************************************************************************
 MTD_STATUS mtdGetSerdesAutoInitialization
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_BOOL *autoInitFlag
 );

 Inputs:
    devPtr - pointer to host's private data
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
                being set

 Outputs:
    autoInitFlag - MTD_SERDES_DISABLE_AUTO_INIT or MTD_SERDES_ENABLE_AUTO_INIT

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Reads the value of the H and X unit serdes auto-initialization control
    bit in the T unit serdes control/status register.

 Side effects:
    None

 Notes/Warnings:

******************************************************************************/
MTD_STATUS mtdGetSerdesAutoInitialization
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *autoInitFlag
);

/******************************************************************************
 MTD_STATUS mtdRerunSerdesAutoInitialization
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit
 );

 Inputs:
    devPtr - pointer to host's private data
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
                being set

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Temporarily disables the serdes auto-initialization (restores it if
    is enabled upon entry), and has the serdes re-run the initialization
    sequence for the serdes at the speed indicated in the serdes control/
    status register.

    Make sure the media link is stable up at the desired speed before
    calling this function (or stable down).

    If the serdes link is up when this function is called it will go
    down momentarily.

 Side effects:
    None

 Notes/Warnings:
    This function waits for the initialization to complete before returning.
    It will return MTD_FAIL if the T unit processor times out.

******************************************************************************/
MTD_STATUS mtdRerunSerdesAutoInitialization
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit
);


/******************************************************************************
 MTD_STATUS mtdRerunSerdesAutoInitUseAutoMode
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port
 );

 Inputs:
    devPtr - pointer to host's private data
    port   - MDIO port address, 0-31

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Signals the T unit processor to run its auto-initialization code
    for the serdes. Whether the serdes settings is modified will be based
    on the inputs to the serdes state machine having been modified
    since the last time it was run. If the speed did not change,
    no change will take effect. To force the serdes initialization
    to run at the speed stored in 7.800F.7:0, call 
    mtdRerunSerdesAutoInitialization() which will force the serdes
    to be re-initialized.

    If the serdes link is up when this function is called it may go
    down momentarily but only if the speed or interface settings changed
    since the last time the link changed state.

 Side effects:
    None

 Notes/Warnings:
    This function has the T processor check the current state of the
    serdes according to the various inputs into the serdes speed (link down
    speed, copper link up/down, copper speed, etc.) and will re-execute
    the serdes initializatoin if any of those inputs changed. If none
    of them changed, the serdes will not be re-initialized.

    You can call mtdGetSerdesAutoInitSpeed() before and after to see
    if the speed changed. If the speed changed, the serdes will have
    been re-initialized.
 
    This function waits for the initialization to complete before returning.
    It will return MTD_FAIL if the T unit processor times out.

******************************************************************************/
MTD_STATUS mtdRerunSerdesAutoInitUseAutoMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);


#define MTD_SERDES_SPEED_GIG   5 /* serdes is set to operate at SGMII speed (1G or below) */
#define MTD_SERDES_SPEED_RXAUI 6 /* serdes is set to operate at RXAUI speed */
#define MTD_SERDES_SPEED_XFI   7 /* serdes is set to operate at XFI speed */

/* following are only on 88X33X0 family and 88E20X0 family */
#define MTD_SERDES_SPEED_2P5G  8 /* serdes is set to operate at 2.5GBASE-X speed */
#define MTD_SERDES_SPEED_5G    9 /* serdes is set to operate at 5GBASE-R speed */
#define MTD_SERDES_SPEED_XAUI 10 /* serdes is set to operate at XAUI speed 88X3310 and 88E2010 only */
/******************************************************************************
 MTD_STATUS mtdGetSerdesAutoInitSpeed
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit,
     OUT MTD_U16 *autoSpeedDetected
 );

 Inputs:
    devPtr - pointer to host's private data
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
                being set

 Outputs:
    autoSpeedDetected - One of the following:
        MTD_SERDES_SPEED_GIG - the serdes was initialized to run at
                               1G or below speed
        MTD_SERDES_SPEED_RXAUI - the serdes was initialized to run at
                                 RXAUI speed        
        MTD_SERDES_SPEED_XFI - the serdes was initialized to run at
                               XFI speed     
        MTD_SERDES_SPEED_2P5G - the serdes was initialized to run at
                               2.5GBASE-X (88X33X0 family and 88E20X0 family only)
        MTD_SERDES_SPEED_5G - the serdes was initialized to run at
                              5GBASE-R (88X33X0 family and 88E20X0 family only)
        MTD_SERDES_SPEED_XAUI - the serdes was initialized to run at                       
                               XAUI speed (88X3310 and 88E2010 only)
         

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Reads the H or X unit speed bits in the serdes control/status register
    and returns the speed of the last workaround which was run to 
    indicate how the serdes is currently configured.

 Side effects:
    None

 Notes/Warnings:

******************************************************************************/
MTD_STATUS mtdGetSerdesAutoInitSpeed
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    OUT MTD_U16 *autoSpeedDetected
);
    
/******************************************************************************
 MTD_STATUS mtdSetSerdesControl1
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit,
     IN MTD_BOOL loopback,
     IN MTD_BOOL rx_powerdown,
     IN MTD_BOOL block_tx_on_loopback
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
                being set
    loopback - MTD_TRUE to set loopback, MTD_FALSE otherwise
    tx_powerdown - MTD_TRUE to power down receiver, MTD_FALSE to power up
    block_tx_on_loopback - MTD_TRUE if when loopback is true, will not pass
                           loopbacked data through to tx path, MTD_FALSE
                           loopbacked data will be transmitted through

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Controls the Serdes for the H unit or X unit.

    On loopback = MTD_TRUE, on H unit does a host loopback, on the X unit does
    a link loopback.

    block_tx_on_loopback = MTD_TRUE, on H unit blocks ingress path during loopback,
    on X unit blocks egress path during loopback.

 Side effects:
    None

 Notes/Warnings:
    Use mtdGetSerdesControl1() to get current settings.

******************************************************************************/
MTD_STATUS mtdSetSerdesControl1
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    IN MTD_BOOL loopback,
    IN MTD_BOOL rx_powerdown,
    IN MTD_BOOL block_tx_on_loopback
);

/******************************************************************************
 MTD_STATUS mtdGetSerdesControl1
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit,
     OUT MTD_BOOL *loopback,
     OUT MTD_BOOL *rx_powerdown,
     OUT MTD_BOOL *block_tx_on_loopback
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
                being read

 Outputs:
    loopback - MTD_TRUE indicates loopback set, MTD_FALSE otherwise
    tx_powerdown - MTD_TRUE receiver powered down, MTD_FALSE otherwise
    block_tx_on_loopback - MTD_TRUE if when loopback is true, data blocked
                           on transmit path, MTD_FALSE
                           data not blocked on transmit path 

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Reads the the Serdes control register 1 for the H unit or X unit.

    On loopback = MTD_TRUE, on H unit indicates a host loopback, on the X unit 
    indicates a link loopback.

    block_tx_on_loopback = MTD_TRUE, on H unit indicates ingress path blocked
    during loopback, on X unit indicates egress path blocked during loopback.

 Side effects:
    None

 Notes/Warnings:
    Use mtdSetSerdesControl1() to change current settings.

******************************************************************************/
MTD_STATUS mtdGetSerdesControl1
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    OUT MTD_BOOL *loopback,
    OUT MTD_BOOL *rx_powerdown,
    OUT MTD_BOOL *block_tx_on_loopback
);


/******************************************************************************
 MTD_STATUS mtdSetSerdesLanePolarity
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit,
     IN MTD_BOOL invert_input_pol,
     IN MTD_BOOL invert_output_pol
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which lane is
                being set (see description below)
    invert_input_pol - MTD_TRUE to invert the serdes input polarity, 
                       MTD_FALSE to leave it as-is
    invert_output_pol - MTD_TRUE to invert the serdes output polarity, 
                        MTD_FALSE to leave it as-is

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function can be used to invert the input or output polarity of
    the serdes pins for either the H unit (lane 0) or X unit (lane 1)
    in either 10GBASE-R mode (lane0/1), or 1000BASE-X/SGMII fiber mode.

    Passing in MTD_H_UNIT adjusts lane 0, MTD_X_UNIT adjusts lane 1,
    or in 1000BASE-X/SGMII mode MTD_H_UNIT adjusts the MAC interface
    and MTD_X_UNIT adjusts the fiber interface.

 Side effects:
    None

 Notes/Warnings:
    This is only for 10GBASE-R, 1000BASE-X, or SGMII mode. In these modes,
    lane 0 polarity is controlled by 4.F004.[14,12] (H unit), and lane 1
    polarity is controlled by 3.F004.[15,13] (X unit).

    In 10GBASE-X2 (RXAUI) mode, both lanes are controlled by 4.F004.15:12. A
    different API function call is provided for this mode of operation,
    mtdSetX2SerdesLanePolarity().   

    Call mtdGetSerdesLanePolarity() to find out the current setting.

******************************************************************************/
MTD_STATUS mtdSetSerdesLanePolarity
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    IN MTD_BOOL invert_input_pol,
    IN MTD_BOOL invert_output_pol
);


/******************************************************************************
 MTD_STATUS mtdGetSerdesLanePolarity
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit,
     IN MTD_BOOL *invert_input_pol,
     IN MTD_BOOL *invert_output_pol
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which lane is
                being gotten (see description below)

 Outputs:
    invert_input_pol - MTD_TRUE the serdes input polarity is inverted, 
                       MTD_FALSE it's not inverted
    invert_output_pol - MTD_TRUE the serdes output polarity is inverted, 
                       MTD_FALSE it's not inverted

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function can be called to read the current polarity setting
    in 10GBASE-R, 1000BASE-X/SGMII mode. Pass in MTD_H_UNIT to 
    read the lane 0 setting (or MAC interface setting) and MTD_X_UNIT
    to read the lane 1 setting (or fiber interface setting).

    A different function is provided for setting/getting the polarity
    in 10GBASE-X2 (RXAUI) mode, mtdGetX2SerdesLanePolarity().

 Side effects:
    None

 Notes/Warnings:
    This is only for 10GBASE-R, 1000BASE-X, or SGMII mode. In these modes,
    lane 0 polarity is controlled by 4.F004.[14,12] (H unit), and lane 1
    polarity is controlled by 3.F004.[15,13] (X unit).

    In 10GBASE-X2 (RXAUI) mode, both lanes are controlled by 4.F004.15:12. A
    different API function call is provided for this mode of operation,
    mtdGetX2SerdesLanePolarity().   

    Call mtdSetSerdesLanePolarity() to change the current setting.

******************************************************************************/
MTD_STATUS mtdGetSerdesLanePolarity
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    IN MTD_BOOL *invert_input_pol,
    IN MTD_BOOL *invert_output_pol
);



/******************************************************************************
 MTD_STATUS mtdSetSerdesInterruptEnable
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit,
     IN MTD_BOOL fifo_overflow,
     IN MTD_BOOL fifo_underflow,
     IN MTD_BOOL pkt_check_crc
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being set
    fifo_overflow - MTD_TRUE to enable the fifo overflow interrupt, MTD_FALSE
                    to disable                    
    fifo_underflow - MTD_TRUE to enable the fifo underflow interrupt, MTD_FALSE
                     to disable
    pkt_check_crc - MTD_TRUE to enable the packet checker CRC interrupt, MTD_FALSE
                    to disable    

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function can be used to enable one of the above interrupts on the H
    or X unit serdes interface.

    Call mtdGetSerdesInterruptEnable() to check if an interrupt is enabled.

    Call mtdGetSerdesInterruptStatus() to check the interrupt status.
    
 Side effects:
    None

 Notes/Warnings:
    None

******************************************************************************/
MTD_STATUS mtdSetSerdesInterruptEnable
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    IN MTD_BOOL fifo_overflow,
    IN MTD_BOOL fifo_underflow,
    IN MTD_BOOL pkt_check_crc
);


/******************************************************************************
 MTD_STATUS mtdGetSerdesInterruptEnable
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit,
     OUT MTD_BOOL *fifo_overflow,
     OUT MTD_BOOL *fifo_underflow,
     OUT MTD_BOOL *pkt_check_crc
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being set

 Outputs:
    fifo_overflow - MTD_TRUE if the fifo overflow interrupt enabled, MTD_FALSE
                    if disabled
    fifo_underflow - MTD_TRUE if the fifo underflow interrupt enabled, MTD_FALSE
                     if disabled
    pkt_check_crc - MTD_TRUE if the packet checker CRC interrupt enabled, MTD_FALSE
                    if disabled    

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function can be called to check if an interrupt is enabled on one
    of the serdes interfaces for the H unit or X unit.

    Call mtdSetSerdesInterruptEnable() to enable/disable an interrupt.

    Call mtdGetSerdesInterruptStatus() to check the interrupt status.
    
 Side effects:
    None

 Notes/Warnings:
    None

******************************************************************************/
MTD_STATUS mtdGetSerdesInterruptEnable
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    OUT MTD_BOOL *fifo_overflow,
    OUT MTD_BOOL *fifo_underflow,
    OUT MTD_BOOL *pkt_check_crc
);


/******************************************************************************
 MTD_STATUS mtdGetSerdesInterruptStatus
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit,
     OUT MTD_BOOL *fifo_overflow,
     OUT MTD_BOOL *fifo_underflow,
     OUT MTD_BOOL *pkt_check_crc
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being set

 Outputs:
    fifo_overflow - MTD_TRUE if a fifo overflow was detected, MTD_FALSE
                    if not
    fifo_underflow - MTD_TRUE if a fifo underflow was detect, MTD_FALSE
                     if not
    pkt_check_crc - MTD_TRUE if the packet checker detected a CRC error
                    and it is enabled, MTD_FALSE if not  

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function can be called to check the status of an interrupt on the
    serdes of the H unit or X unit. Calling this function clears the
    latched high bits for these bits in 3.F00B and 4.F00B.

    Call mtdSetSerdesInterruptEnable() to enable/disable an interrupt.
    
 Side effects:
    None

 Notes/Warnings:
    Clears latch high (LH) interrupt status bits in the status register
    when this function is called.

******************************************************************************/
MTD_STATUS mtdGetSerdesInterruptStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    OUT MTD_BOOL *fifo_overflow,
    OUT MTD_BOOL *fifo_underflow,
    OUT MTD_BOOL *pkt_check_crc
);


#define MTD_SERDES_PPM_FIFO_2K         0 /* set fifo depth to 2K bytes */
#define MTD_SERDES_PPM_FIFO_10K        1 /* set fifo depth to 10K bytes */
#define MTD_SERDES_PPM_FIFO_20K        2 /* set fifo depth to 20K bytes */
#define MTD_SERDES_PPM_FIF0_40K        3 /* set fifo depth to 40K bytes */
#define MTD_SERDES_PPM_FIFO_GETONLY    4 /* This value will cause function to return
                                            current setting without updating */
/******************************************************************************
 MTD_STATUS mtdSetGetSerdesPPMFifo
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit,    
     INOUT MTD_U16 *fifo_offset
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being set
    fifo_offset - if input parameter is set to one of the following: 
                    MTD_SERDES_PPM_FIFO_2K
                    MTD_SERDES_PPM_FIFO_10K
                    MTD_SERDES_PPM_FIFO_20K
                    MTD_SERDES_PPM_FIF0_40K
                  updates the serdes PPM fifo depth accordingly and
                  returns the parameter unchanged.
                  if input parameter is:
                    MTD_SERDES_PPM_FIFO_GETONLY
                  returns the current PPM fifo offset without changing
                  the register.
    

 Outputs:
    fifo_offset - if input parameter is set to MTD_SERDES_PPM_FIFO_GETONLY,
                  returns the current setting in fifo_offset without
                  modifying the register bits. The returned value will be
                  one of the following:
                    MTD_SERDES_PPM_FIFO_2K
                    MTD_SERDES_PPM_FIFO_10K
                    MTD_SERDES_PPM_FIFO_20K
                    MTD_SERDES_PPM_FIF0_40K
                                    
 Returns:
    MTD_OK or MTD_FAIL if there's an io error, or input parameter is out of range.

 Description:
    This function is used to either set the PPM fifo depth of the H unit
    or X unit fifo by writing 4.F00C.15:14 or 3.F00c.15:14, or returns
    the current setting by reading the same bit field without modifying
    the register bits if the input parameter fifo_offset is set to
    MTD_SERDES_PPM_FIFO_GETONLY.

 Side effects:
    None

 Notes/Warnings:
    The PPM Fifo Offset is not allowed to be changed on X32X0, X33X0, E20X0,
    or E21X0 parts. It may be read but not changed on these parts. Trying
    to set it on these parts will result in an error.

******************************************************************************/
MTD_STATUS mtdSetGetSerdesPPMFifo
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,    
    INOUT MTD_U16 *fifo_offset
);

/* possible values for pktPatternControl and frameLengthControl */
/* Please refer to mtdDiagnostics.h for definition */

/******************************************************************************
 MTD_STATUS mtdConfigurePktGeneratorChecker
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit,
     IN MTD_BOOL readToClear,
     IN MTD_BOOL dontuseSFDinChecker,
     IN MTD_U16 pktPatternControl,
     IN MTD_BOOL generateCRCoff,
     IN MTD_U32 initialPayload,
     IN MTD_U16 frameLengthControl,
     IN MTD_U16 numPktsToSend,
     IN MTD_BOOL randomIPG,
     IN MTD_U16 ipgDuration
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being configured
    readToClear - MTD_TRUE if the desired behavior is that when the
                  counters are read, they are reset. MTD_FALSE if the
                  desired behavior is that they must be explicitly cleared
                  by mtdPktGeneratorCounterReset() and reading
                  them just returns the current value without clearing them.
    dontuseSFDinChecker - MTD_TRUE indicates to start CRC checking after the
                      first 8 bytes in the packet, MTD_FALSE indicates
                      to look for SFD before starting CRC checking
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
                         in bytes. See definitions above MTD_PKT_RAND_LEN0-5.
    numPktsToSend - 0 stops generation, 0x001-0xFFFE sends exactly that number
                    of packets then stops. 0xFFFF sends continuously.
    randomIPG - MTD_TRUE uses a random IPG from 5 bytes to value specified
                in ipgDuration. MTD_FALSE uses fixed IPG as specified in
                ipgDuration.
    ipgDuration - Meaning depends on randomIPG (see above). Each bit
                  equals 4 bytes of idle. Valid range is 0...0x7FFF.

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL if io error or bad parameter passed in (out of range)

 Description:
    This function is used to configure the packet generator/checker for the
    H unit or X unit.

 Side effects:
    None

 Notes/Warnings:
    Call mtdEnablePktGeneratorChecker() to enable/start the generator/checker.

******************************************************************************/
MTD_STATUS mtdConfigurePktGeneratorChecker
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    IN MTD_BOOL readToClear,
    IN MTD_BOOL dontuseSFDinChecker,
    IN MTD_U16 pktPatternControl,
    IN MTD_BOOL generateCRCoff,
    IN MTD_U32 initialPayload,
    IN MTD_U16 frameLengthControl,
    IN MTD_U16 numPktsToSend,
    IN MTD_BOOL randomIPG,
    IN MTD_U16 ipgDuration
);

/******************************************************************************
 MTD_STATUS mtdEnablePktGeneratorChecker
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit,
     IN MTD_BOOL enableGenerator,
     IN MTD_BOOL enableChecker
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being enabled
    enableGenerator - MTD_TRUE starts the packet generator, MTD_FALSE
                      stops it
    enableChecker - MTD_TRUE starts the packet checker, MTD_FALSE
                    stops it
        
 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function enables/disables either the packet generator or packet checker 
    (or both) in either the H unit or the X unit.

 Side effects:
    None

 Notes/Warnings:
    None

******************************************************************************/
MTD_STATUS mtdEnablePktGeneratorChecker
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    IN MTD_BOOL enableGenerator,
    IN MTD_BOOL enableChecker
);

/******************************************************************************
 MTD_STATUS mtdPktGeneratorCounterReset
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit    
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being reset
    
 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function explicitly clears all the counters when the packet
    generator/checker has been setup to be cleared by writing a 
    bit to the control register instead of being cleared when
    the counter(s) are read.

    This function operates on the counters in the H unit or X unit.

    When this function is called (and 3.F010.15/4.F010.15 is 0)
    the transmit, receive, error and link drop counters will be cleared.

 Side effects:
    None

 Notes/Warnings:
    This function assumes the generator/checker has been configured to
    be cleared by bit 3.F010.6/4.F010.6 by previously passing 
    MTD_FALSE for parameter readToClear in function 
    mtdConfigurePktGeneratorChecker() (thus setting bit F010.15 <= 0).

******************************************************************************/
MTD_STATUS mtdPktGeneratorCounterReset
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit    
);

/* Please refer to mtdDiagnostics.h for definition of whichCounter possible values */

/******************************************************************************
 MTD_STATUS mtdPktGeneratorGetCounter
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit,
     IN MTD_U16 whichCounter,
     OUT MTD_U64 *packetCount,
     OUT MTD_U64 *byteCount    
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being reset
    whichCounter - One of the following, depending on which set of counters
                   is being read:
                       MTD_PKT_GET_TX to read the generator/transmit counters
                       MTD_PKT_GET_RX to read the checker/receive counters
                       MTD_PKT_GET_ERR to read the packet error counter
                           

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
                  MTD_PKT_GET_ERR, since error counter is a packet
                  count only.

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function is used to read the transmit/receive/error counter for the
    packet generator/checker in either the H unit or X unit.

 Side effects:
    None

 Notes/Warnings:
    byteCount is always 0 for MTD_PKT_GET_ERR, since the error counter
    only counts packets.

    If packet generator/checker was configured to clear counter(s) on read,
    this function will clear the counter being read.

******************************************************************************/
MTD_STATUS mtdPktGeneratorGetCounter
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    IN MTD_U16 whichCounter,
    OUT MTD_U64 *packetCount,
    OUT MTD_U64 *byteCount    
);

/******************************************************************************
 MTD_STATUS mtdPktGeneratorCheckerGetLinkDrop
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit,
     OUT MTD_U16 *linkDropCounter        
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being reset
    

 Outputs:
    linkDropCounter - number of link drops received

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function reads the link drop counter register.

 Side effects:
    None

 Notes/Warnings:
    If packet generator/checker was configured to clear counter(s) on read,
    this function will clear the link drop counter.

******************************************************************************/
MTD_STATUS mtdPktGeneratorCheckerGetLinkDrop
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    OUT MTD_U16 *linkDropCounter        
);

/*******************************************************************************
 PRBS Functions shared between H unit and X unit

 Pattern Selection. An "I" before PRBS indicates it's an inverted pattern. 
 Used to set 3.F030.3:0 for X unit and 4.F030.3:0 for H unit
*******************************************************************************/
#define    MTD_PRBS31    0x0000
#define    MTD_PRBS7     0x0001
#define    MTD_PRBS9     0x0002   
#define    MTD_PRBS23    0x0003
#define    MTD_IPRBS31   0x0004
#define    MTD_IPRBS7    0x0005
#define    MTD_IPRBS9    0x0006
#define    MTD_IPRBS23   0x0007
#define    MTD_PRBS15    0x0008
#define    MTD_IPRBS15   0x0009
#define    MTD_HFP       0x000C /* High Frequency Pattern  */
#define    MTD_LFP       0x000D /* Low Frequency Pattern   */
#define    MTD_MFP       0x000E /* Mixed Frequency Pattern */
#define    MTD_SQWV      0x000F /* Square Wave Pattern     */

/*******************************************************************************
 MTD_STATUS mtdSetPRBSPattern
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16  port,
     IN MTD_U16  HorXunit,
     IN MTD_U16  pattSel
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being set

    pattSel - one of the following:
         MTD_LINE_PRBS31
         MTD_LINE_PRBS7
         MTD_LINE_PRBS9
         MTD_LINE_PRBS23
         MTD_LINE_IPRBS31
         MTD_LINE_IPRBS7
         MTD_LINE_IPRBS9
         MTD_LINE_IPRBS23
         MTD_LINE_PRBS15
         MTD_LINE_IPRBS15
         MTD_LINE_HFP
         MTD_LINE_LFP
         MTD_LINE_MFP
         MTD_LINE_SQWV

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function is used to select the type of PRBS pattern desired 
    for the X unit in registers 3.F030.3:0 and H unit in 4.F030.3:0.

 Side effects:
    None
    
 Notes/Warnings:
    None
    
*******************************************************************************/
MTD_STATUS mtdSetPRBSPattern
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  HorXunit,
    IN MTD_U16  pattSel
);

/*******************************************************************************
 MTD_STATUS mtdSetPRBSEnableTxRx
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16  port,     
     IN MTD_U16  HorXunit,
     IN MTD_U16  txEnable,
     IN MTD_U16  rxEnable
 );
 
 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being set       
    txEnable - MTD_ENABLE or MTD_DISABLE to start or stop the transmit
    rxEnable - MTD_ENABLE or MTD_DISABLE to start or stop the receiver

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function is used to start or stop the PRBS transmit and/or 
    receiver.

 Side effects:
    None
   
 Notes/Warnings:
    None

*******************************************************************************/
MTD_STATUS mtdSetPRBSEnableTxRx
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,    
    IN MTD_U16  HorXunit,
    IN MTD_U16  txEnable,
    IN MTD_U16  rxEnable
);


/*******************************************************************************
 MTD_STATUS mtdPRBSCounterReset
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16  port,
     IN MTD_U16  HorXunit  
 );
 
 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being set       

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function is used to reset the counters when the PRBS has been
    setup for manual clearing instead of clear-on-read. Default
    is to use manual clearing. Call mtdSetPRBSEnableClearOnRead() to
    enable clearing the counters when reading the registers.

    This function operates on the counters in the H unit or X unit.

 Side effects:
    None
   
 Notes/Warnings:
    Assumes the PRBS has not been setup for clear-on-read.
   
*******************************************************************************/
MTD_STATUS mtdPRBSCounterReset
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,    
    IN MTD_U16  HorXunit   
);


/*******************************************************************************
 MTD_STATUS mtdSetPRBSWaitForLock
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16  port,    
     IN MTD_U16  HorXunit,    
     IN MTD_U16  disableWaitforLock
 );
 
 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31    
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being set       
    disableWaitforLock - 1 counts PRBS before locking, 0 waits
        for locking before counting

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Configures PRBS to wait for locking before counting, or to start counting 
    before locking.

 Side effects:
    None
   
 Notes/Warnings:
    Should be called before starting the receiver.
   
*******************************************************************************/
MTD_STATUS mtdSetPRBSWaitForLock
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,    
    IN MTD_U16  HorXunit,    
    IN MTD_U16  disableWaitforLock
);


/*******************************************************************************
 MTD_STATUS mtdGetPRBSWaitForLock
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16   port,    
     IN MTD_U16   HorXunit,    
     OUT MTD_U16 *disableWaitforLock
 );
 
 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31    
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being set       
 
 Outputs:
    disableWaitforLock - 1 counts PRBS before locking, 0 waits
        for locking before counting

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Returns configuration for PRBS whether it is set to wait for locking
    or not before counting.

 Side effects:
    None
   
 Notes/Warnings:
    None
   
*******************************************************************************/
MTD_STATUS mtdGetPRBSWaitForLock
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,    
    IN MTD_U16   HorXunit,    
    OUT MTD_U16 *disableWaitforLock
);


/*******************************************************************************
 MTD_STATUS mtdSetPRBSClearOnRead
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16  port,    
     IN MTD_U16  HorXunit,    
     IN MTD_U16  enableReadClear
 );
 
 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being set     
    enableReadClear - 1 enables clear-on-read, 0 enables manual clear 
        (by setting register bit).

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    The default for the PRBS counters is to be cleared manually by 
    calling mtdPRBSCounterReset(). This configures either to read-clear,or
    manual clear (by setting a register bit).

 Side effects:
    None
   
 Notes/Warnings:
    Should be called before starting the receiver.
   
*******************************************************************************/
MTD_STATUS mtdSetPRBSClearOnRead
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,    
    IN MTD_U16  HorXunit,    
    IN MTD_U16  enableReadClear
);


/*******************************************************************************
 MTD_STATUS mtdGetPRBSClearOnRead
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16  port,    
     IN MTD_U16  HorXunit,    
     OUT MTD_U16  *enableReadClear
 );
 
 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being set       

 Outputs:
    enableReadClear - 1 clear-on-read enabled, 0 manual clear is enabled

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Checks whether the PRBS is configured to clear-on-read (1) or manual
    cleared (0).

 Side effects:
    None
   
 Notes/Warnings:
    None
   
*******************************************************************************/
MTD_STATUS mtdGetPRBSClearOnRead
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16    port,    
    IN MTD_U16    HorXunit,    
    OUT MTD_U16  *enableReadClear
);

/*******************************************************************************
 MTD_STATUS mtdGetPRBSLocked
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16    port,
     IN MTD_U16    HorXunit,
     OUT MTD_BOOL *prbsLocked
 );
 
 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being set       

Outputs:
    prbsLocked - MTD_TRUE if the PRBS receiver is locked, MTD_FALSE otherwise

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Returns the indicator if the PRBS receiver is locked or not.

 Side effects:
    None
   
 Notes/Warnings:
    Should be called after starting the receiver.
   
*******************************************************************************/
MTD_STATUS mtdGetPRBSLocked
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16    port,
    IN MTD_U16    HorXunit,
    OUT MTD_BOOL *prbsLocked
);

/*******************************************************************************
 MTD_STATUS mtdGetPRBSCounts
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16   port,
     IN MTD_U16   HorXunit,
     OUT MTD_U64 *txBitCount,
     OUT MTD_U64 *rxBitCount,
     OUT MTD_U64 *rxBitErrorCount
 );
 
 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being set       

 Outputs:
    txBitCount - number of bits transmitted
    rxBitCount - number of bits received
    rxBitErrorCount - number of bits in error

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Returns the 48-bit results in the output parameters above. If the PRBS
    control has been set to clear-on-read, the registers will clear. If
    not, they must be cleared manually by calling mtdPRBSCounterReset()

 Side effects:
    None
   
 Notes/Warnings:
    None
   
*******************************************************************************/
MTD_STATUS mtdGetPRBSCounts
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,    
    IN MTD_U16   HorXunit,
    OUT MTD_U64 *txBitCount,
    OUT MTD_U64 *rxBitCount,
    OUT MTD_U64 *rxBitErrorCount
);

/******************************************************************************
 Functions shared between H unit and X unit for 1000BX/SGMII
******************************************************************************/

/* defines for bit 6,13 in SGMII control register */
#define MTD_SGMII_SPEED_10M   0
#define MTD_SGMII_SPEED_100M  1
#define MTD_SGMII_SPEED_1G    2
#define MTD_SGMII_SPEED_ASIS  3 /* to leave the setting as it is */
/******************************************************************************
 MTD_STATUS mtdSet1000BXSGMIIControl
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit,
     IN MTD_BOOL loopback,
     IN MTD_U16 speed,
     IN MTD_BOOL an_enable,
     IN MTD_BOOL power_down,
     IN MTD_BOOL restart_an,
     IN MTD_BOOL sw_reset
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
                being configured
    loopback - MTD_TRUE to set to loopback, MTD_FALSE to undo loopback
    speed - one of the following (only applies when AN is disabled)
        MTD_SGMII_SPEED_10M
        MTD_SGMII_SPEED_100M  
        MTD_SGMII_SPEED_1G    
    an_enable - MTD_TRUE to enable autonegotiation, MTD_FALSE to disable it
                NOTE: Toggling this setting will cause link to go down
                and restart AN bit 9 automatically will get set to 1
    power_down - MTD_TRUE to power down all PCS/PMA of this interface, MTD_FALSE
                 otherwise
    restart_an - MTD_TRUE to restart the SGMII autonegotiation, MTD_FALSE otherwise,
                 this bit self clears
    sw_reset - MTD_TRUE to do a software reset on this interface, MTD_FALSE otherwise,
               this bit self clears           

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL if some error occurred

 Description:
    This is a multi-purpose control function for controlling the H Unit SGMII
    interface or the X Unit SGMII interface. Most parameters of this function
    should only be used individually. Using this function, you may

        1. Disable autoneg or Enable autoneg (changing this automatically restarts an) (an_enable)
        2. Restart autoneg (restart_an)
        3. Set the SGMII speed (which only takes effect if AN is disabled) (speed)
        4. Put the SGMII into loopback (loopback)
        5. Power down the SGMII interface (power_down)
        6. Perform a software reset on the SGMII MMD

 Side effects:
    None

 Notes/Warnings:
    Call mtdGet1000BXSGMIIControl() to get the current settings. If 
    software reset is set to MTD_TRUE, the software reset will be performed 
    last.

    This call is also used for 2.5G operation on 88X33X0/E20X0/E21X0 PHYs.

******************************************************************************/
MTD_STATUS mtdSet1000BXSGMIIControl
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    IN MTD_BOOL loopback,
    IN MTD_U16 speed,
    IN MTD_BOOL an_enable,
    IN MTD_BOOL power_down,
    IN MTD_BOOL restart_an,
    IN MTD_BOOL sw_reset
);


/******************************************************************************
 MTD_STATUS mtdGet1000BXSGMIIControl
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit,
     OUT MTD_BOOL *loopback,
     OUT MTD_U16 *speed,
     OUT MTD_BOOL *an_enable,
     OUT MTD_BOOL *power_down
 );


 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
                being queried

 Outputs:
    loopback - MTD_TRUE = loopback enabled, MTD_FALSE to otherwise
    speed - one of the following (only applies when AN is disabled)
        MTD_SGMII_SPEED_10M
        MTD_SGMII_SPEED_100M  
        MTD_SGMII_SPEED_1G    
    an_enable - MTD_TRUE autonegotiation enabled, MTD_FALSE otherwise
    power_down - MTD_TRUE if powered down, MTD_FALSE otherwise

 Returns:
    MTD_OK or MTD_FAIL if some error occurred

 Description:
    This function may be called to query the state of the bits in 3.2000
    (X unit SGMII control register) or 4.2000 (H unit SGMII control register).

 Side effects:
    None

 Notes/Warnings:
    Call mtdSet1000BXSGMIIControl() to change the current settings.
    
    This call is also used for 2.5G operation on 88X33X0/E20X0/E21X0 PHYs.

******************************************************************************/
MTD_STATUS mtdGet1000BXSGMIIControl
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    OUT MTD_BOOL *loopback,
    OUT MTD_U16 *speed,
    OUT MTD_BOOL *an_enable,
    OUT MTD_BOOL *power_down
);

/******************************************************************************
 MTD_STATUS mtdGet1000BXSGMIIStatus
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit,
     OUT MTD_BOOL *an_complete,
     OUT MTD_BOOL *remote_fault,
     OUT MTD_BOOL *link_status_latched,
     OUT MTD_BOOL *link_status_current
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
                being queried    

 Outputs:
    an_complete - MTD_TRUE if autonegotiation has completed (MTD_FALSE
                  indicates link down, autoneg disabled or link up due
                  to autoneg bypassed)
    remote_fault - MTD_TRUE if remote fault condition detected, MTD_FALSE
                   in SGMII mode, or no remote fault condition detected
                   (this parameter only valid in 1000BX mode)
    link_status_latched - MTD_FALSE, indicates link was lost since last read.
                  This bit is a latched low bit. This is first read
                  value.
    link_status_current - MTD_FALSE, indicates link is currently down. 
                  This bit is a latched low bit. This is second read of
                  register.
                  

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Queries the status register in 3.2001 (X unit 1000BX/SGMII Status)
    or 4.2001 (H unit SGMII Status) and returns the value of bits:
    5: autoneg complete (MTD_TRUE if link up and autoneg has completed)
    4: remote fault (1000BX only mode valid, always MTD_FALSE in SGMII mode)
    2: link status (value of first read of register returned in
       link_status_latched, value of second read returned in link_status_current)
    
    

 Side effects:
    None

 Notes/Warnings:
    The SGMII status is not valid unless the host interface is up at
    a speed of 1G/100M or 10M. Check the media side link up and speed
    before calling this function.

    This means if the media side link is down and the host link down
    speed is set to 10G, the host SGMII link status returned by this function
    is not valid and should be ignored.

    This call is also used for 2.5G operation on 88X33X0/E20X0/E21X0 PHYs.    

******************************************************************************/
MTD_STATUS mtdGet1000BXSGMIIStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    OUT MTD_BOOL *an_complete,
    OUT MTD_BOOL *remote_fault,
    OUT MTD_BOOL *link_status_latched,
    OUT MTD_BOOL *link_status_current
);




/******************************************************************************
 Functions shared between H unit and X unit for 10GBASE-R PCS
 XFI
 SFI
 USXGMII
 All use H unit or X unit 10GBASE-R PCS
******************************************************************************/

/******************************************************************************
 MTD_STATUS mtdSetUSXGMIIControl or
 MTD_STATUS mtdSet10GBRControl 
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit,
     IN MTD_BOOL loopback,
     IN MTD_BOOL power_down,
     IN MTD_BOOL sw_reset
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
                being configured
    loopback - MTD_TRUE to set to loopback, MTD_FALSE to undo loopback
    power_down - MTD_TRUE to power down all PCS/PMA of this interface, MTD_FALSE
                 otherwise
    sw_reset - MTD_TRUE to do a software reset on this interface, MTD_FALSE otherwise,
               this bit self clears           
    

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function is used to control the 10GBASE-R PCS interface on either the
    H unit (MAC interface) or the X unit (fiber interface) on the 88X3240.
    The PCS may be put in loopback, powered down, or a software reset may 
    be performed. The software reset bit is self clearing.

 Side effects:
    None

 Notes/Warnings:
    Use mtdGet10GBRControl() to read the current value of the loopback
    and power_down bits. In registers 3.1000 or 4.1000.

    This call is also used for 5G operation on 88X33X0/E20X0/E21X0 PHYs.
    
******************************************************************************/
MTD_STATUS mtdSet10GBRControl
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    IN MTD_BOOL loopback,
    IN MTD_BOOL power_down,
    IN MTD_BOOL sw_reset
);
#define mtdSetUSXGMIIControl mtdSet10GBRControl

/******************************************************************************
 MTD_STATUS mtdGetUSXGMIIControl
 MTD_STATUS mtdGet10GBRControl
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit,
     OUT MTD_BOOL *loopback,
     OUT MTD_BOOL *power_down,
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
                being read
 Outputs:
    loopback - MTD_TRUE if loopback is set, MTD_FALSE if not
    power_down - MTD_TRUE if PCS/PMA is powered down, MTD_FALSE
                 otherwise

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function is used to read the values of bits in the 10GBASE-R
    PCS control register of the H or X unit.

 Side effects:
    None

 Notes/Warnings:
    Use mtdSet10GBRControl() to change the settings on the 10GBASE-R PCS
    control register, 3.1000 or 4.1000.

    This call is also used for 5G operation on 88X33X0/E20X0/E21X0 PHYs.    

******************************************************************************/
MTD_STATUS mtdGet10GBRControl
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    OUT MTD_BOOL *loopback,
    OUT MTD_BOOL *power_down
);
#define mtdGetUSXGMIIControl mtdGet10GBRControl

/******************************************************************************
 MTD_STATUS mtdGetUSXGMIIStatus1 or
 MTD_STATUS mtdGet10GBRStatus1
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit,
     OUT MTD_BOOL *tx_lpi_latch,
     OUT MTD_BOOL *rx_lpi_latch,
     OUT MTD_BOOL *tx_lpi_current,
     OUT MTD_BOOL *rx_lpi_current,
     OUT MTD_BOOL *fault,
     OUT MTD_BOOL *link_status_latch,
     OUT MTD_BOOL *link_status_current    
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being read
 Outputs:
    tx_lpi_latch - value of bit 11, MTD_TRUE if Tx PCS has received LPI
                   since last read of this bit, MTD_FALSE if not
    rx_lpi_latch- value of bit 10, MTD_TRUE if Rx PCS has received LPI
                   since last read of this bit, MTD_FALSE if not
    tx_lpi_current - value of bit 9, MTD_TRUE if Tx PCS is receiving LPI
                     currently, MTD_FALSE if not
    rx_lpi_current - value of bit 8, MTD_TRUE if Rx PCS is receiving LPI
                     currently, MTD_FALSE if not
    fault - value of bit 7, MTD_TRUE if a fault is indicated by 
            bit 10 or 11 in register 0x1008, MTD_FALSE otherwise
    link_status_latch - first read value of bit 2, which is a latched
            low bit. MTD_FALSE if PCS has had a link down since last
            time this register was read, MTD_TRUE if no link down
            has occurred.
    link_status_current - second read of bit 2. MTD_TRUE if link is
            currently up, MTD_FALSE if link is currently down    

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function returns the value of status bits in the 10GBASE-R PCS
    STATUS 1 Register in either the H unit or X unit (4.1001 or 3.1001).    

 Side effects:
    None

 Notes/Warnings:
    Latch bits may be cleared when calling this register if the underlying
    condition has changed.

    Clearing fault requires reading register 0x1008.

    This call is also used for 5G operation on 88X33X0/E20X0/E21X0 PHYs.    

******************************************************************************/
MTD_STATUS mtdGet10GBRStatus1
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,
    OUT MTD_BOOL *tx_lpi_latch,
    OUT MTD_BOOL *rx_lpi_latch,
    OUT MTD_BOOL *tx_lpi_current,
    OUT MTD_BOOL *rx_lpi_current,
    OUT MTD_BOOL *fault,
    OUT MTD_BOOL *link_status_latch,
    OUT MTD_BOOL *link_status_current    
);
#define mtdGetUSXGMIIStatus1 mtdGet10GBRStatus1

/******************************************************************************
 MTD_STATUS mtdGetUSXGMIIFault or
 MTD_STATUS mtdGet10GBRFault
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit,         
     OUT MTD_BOOL *tx_fault_latch,
     OUT MTD_BOOL *rx_fault_latch,
     OUT MTD_BOOL *tx_fault_current,
     OUT MTD_BOOL *rx_fault_current
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being read
               
 Outputs:
    tx_fault_latch - MTD_TRUE if there was a fault on the tx path since the last
                     call of this function, MTD_FALSE if not (bit 11)
    rx_fault_latch - MTD_TRUE if there was a fault on the rx path since the last
                     call of this function, MTD_FALSE if not (bit 10)
    tx_fault_current - MTD_TRUE if there is currently a fault on the tx path, 
                       MTD_FALSE if not (bit 11)
    rx_fault_current - MTD_TRUE if there is currently a fault on the rx path, 
                       MTD_FALSE if not (bit 10)
                                          
 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Reads the Status 2 register in either the H unit or X unit twice and
    returns the tx/rx fault latched value (first read) in the latch variables
    and the current tx/rx fault value (second read) in the current variables.

    Latched variables indicate if there was a fault since the last read, 
    whereas current variables indicate if there is currently a tx/rx fault.

 Side effects:
    None

 Notes/Warnings:
    Reading this register will clear the fault bit in register 0x1001 if
    the fault condition has cleared.

    This call is also used for 5G operation on 88X33X0/E20X0/E21X0 PHYs.    

******************************************************************************/
MTD_STATUS mtdGet10GBRFault
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit,    
    OUT MTD_BOOL *tx_fault_latch,
    OUT MTD_BOOL *rx_fault_latch,
    OUT MTD_BOOL *tx_fault_current,
    OUT MTD_BOOL *rx_fault_current
);
#define mtdGetUSXGMIIFault mtdGet10GBRFault

/******************************************************************************
 MTD_STATUS mtdGetUSXGMIIReceiveStatus or
 MTD_STATUS mtdGet10GBRReceiveStatus
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit, 
     OUT MTD_BOOL *link_up,
     OUT MTD_BOOL *high_ber,
     OUT MTD_BOOL *block_lock    
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being read    

 Outputs:
    link_up - MTD_TRUE if receive link is up, MTD_FALSE if down (bit 12)
    high_ber - MTD_TRUE if receive link is reporting high bit error rate,
               MTD_FALSE if not (bit 1)
    block_lock - MTD_TRUE if receive link is locked to received block,
                 MTD_FALSE if not (bit 0)

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Reads register 0x1020 in either the H unit or X unit and returns the
    flags above reporting the status of the 10GBASE-R PCS Receive path.

 Side effects:
    None

 Notes/Warnings:
    This call is also used for 5G operation on 88X33X0/E20X0/E21X0 PHYs.

******************************************************************************/
MTD_STATUS mtdGet10GBRReceiveStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit, 
    OUT MTD_BOOL *link_up,
    OUT MTD_BOOL *high_ber,
    OUT MTD_BOOL *block_lock    
);
#define mtdGetUSXGMIIReceiveStatus mtdGet10GBRReceiveStatus


/******************************************************************************
 MTD_STATUS mtdGetUSXGMIIStatus2 or
 MTD_STATUS mtdGet10GBRStatus2
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 HorXunit, 
     OUT MTD_BOOL *has_block_lock,
     OUT MTD_BOOL *reported_high_ber,
     OUT MTD_U8 *ber_counter,
     OUT MTD_U8 *errored_blocks_counter    
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being read    
   
 Outputs:
    has_block_lock - MTD_FALSE if block lock was lost since the last time
                      this function was called (link encountered rx
                      errors to the point of losing lock), MTD_TRUE
                      if block lock was not lost since last time
                      this function was called.
    reported_high_ber - MTD_TRUE if a high ber condition was reported
                        since the last time this function was called,
                        MTD_FALSE if not (bit14)
    ber_counter - Number of bit errors since last read (0xFF indicates
                  counter saturated) (bits 13:8)
    errored_blocks_counter - Number of errored blocks since last read
                  (0xFF indicates counter saturated) (bits 7:0)

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function reads register 0x1021 in either the H unit or X unit
    and returns the above values. Latched bits are cleared if the 
    condition has changed and counters are cleared when read.

    This function is useful to check if there have been errors on
    the rx path since the last time this function was called and how many
    errors may have occurred.

    Call once at the beginning of the period desired to monitor to clear
    the latched bits and counters, and then call again at the end of the
    period to check if any errors occurred during the period.

 Side effects:
    None

 Notes/Warnings:
    Calling this function clears the latched bits in register 0x1021 and
    the counters.

    Current values are not provided in this function. Current values
    for block lock and high ber can be fetched by calling 
    mtdGet10GBRReceiveStatus().

    This call is also used for 5G operation on 88X33X0/E20X0/E21X0 PHYs.    

******************************************************************************/
MTD_STATUS mtdGet10GBRStatus2
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 HorXunit, 
    OUT MTD_BOOL *has_block_lock,
    OUT MTD_BOOL *reported_high_ber,
    OUT MTD_U8 *ber_counter,
    OUT MTD_U8 *errored_blocks_counter    
);
#define mtdGetUSXGMIIStatus2 mtdGet10GBRStatus2

/******************************************************************************
MTD_STATUS mtdSetHXunitMacLoopback
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  HorXunit,
    IN MTD_BOOL passThrough,
    IN MTD_BOOL enable
)

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being configured  
    passThrough - MTD_TRUE = No Egress Blocking for X-unit
                  MTD_FALSE = Egress Blocking for X-unit
                  This parameter is Ignored for H-unit
    enable - MTD_TRUE = enable loopback, MTD_FALSE = disable loopback

 Outputs:
    None

 Returns:
    Returns MTD_OK or MTD_FAIL 

 Description:
    Enables/Disables the Shallow Mac Loopback in the H-unit or the
    Deep Mac Loopback in the X-unit.

 Side effects:
    None

 Notes/Warnings:
    The Deep Mac Loopback in the T-unit is controlled by mtdSetTunitDeepMacLoopback().
 
    Only one loopback can be enabled at a time in the PHY. Otherwise, the 
    behavior will be undefined

    To set the default MAC interface speed during link down, please refer to 
    mtdSetMacInterfaceControl() in mtdHunit.h. If the link is down, the default 
    link down speed must be set correctly and the host interface powerdown must 
    be set correctly for the data to be passed. When the media side link is 
    down, please call mtdSetShallowMacLoopbackLinkDown() to enable/disable
    loopback.

    Deep Mac loopback is not supported in the X-unit if the X-unit media-side 
    link is down.

    To read back the loopback setting, please call mtdGetLoopbackSetting() 
    in mtdDiagnostics.h
*******************************************************************************/
MTD_STATUS mtdSetHXunitMacLoopback
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  HorXunit,
    IN MTD_BOOL passThrough,
    IN MTD_BOOL enable
);

/******************************************************************************
MTD_STATUS mtdSetHXunitLineLoopback
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  HorXunit,
    IN MTD_BOOL passThrough,
    IN MTD_BOOL enable
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being configured  
    passThrough - MTD_TRUE = No Ingress Blocking for H-unit
                  MTD_FALSE = Ingress Blocking for H-unit
                  This parameter is Ignored for X-unit
    enable - MTD_TRUE = enable loopback, MTD_FALSE = disable loopback

 Outputs:
    None

 Returns:
    Returns MTD_OK or MTD_FAIL

 Description:
    Enable/Disable H-unit or X-unit Shallow or Deep Line loopback.
    The Shallow Line Loopback is at the X-unit and Deep Line Loopback is
    at H-unit.

 Side effects:
    None

 Notes/Warnings:
    Only one loopback can be enabled at a time in the PHY. Otherwise, the 
    behavior will be undefined

    To read back the loopback setting, please call mtdGetLoopbackSetting() 
    in mtdDiagnostics.h
*******************************************************************************/
MTD_STATUS mtdSetHXunitLineLoopback
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  HorXunit,
    IN MTD_BOOL passThrough,
    IN MTD_BOOL enable
);

/******************************************************************************
MTD_STATUS mtdSetShallowMacLoopbackLinkDown
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  linkDownSpeed,
    IN MTD_BOOL enable
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - MDIO port address, 0-31
    linkDownSpeed - MAC Interface Speed during loopback when enable the 
                    loopback. When disabling the loopback, this is what 
                    to set the MAC interface Link Down speed back to for
                    default link down speed when media side is down.

                    MTD_SPEED_10M_HD   
                    MTD_SPEED_10M_FD   
                    MTD_SPEED_100M_HD  
                    MTD_SPEED_100M_FD  
                    MTD_SPEED_1GIG_HD  
                    MTD_SPEED_1GIG_FD  
                    MTD_SPEED_10GIG_FD 
                    MTD_SPEED_2P5GIG_FD
                    MTD_SPEED_5GIG_FD  

    enable - MTD_TRUE = enable loopback, MTD_FALSE = disable loopback

 Outputs:
    None

 Returns:
    Returns MTD_OK or MTD_FAIL

 Description:
    Enable/Disable H-unit Shallow MAC loopback when the Media Link is down.
    To be called when the media side link is down to enable the shallow MAC
    loopback at the speed indicated in the linkDownSpeed. When disabling the 
    loopback, sets the default link down speed for the MAC interface back to
    the linkDownSpeed.

 Side effects:
    None

 Notes/Warnings:
    Only one loopback can be enabled at a time in the PHY. Otherwise, the 
    behavior will be undefined

    To read back the loopback setting, please call mtdGetLoopbackSetting() 
    in mtdDiagnostics.h
*******************************************************************************/
MTD_STATUS mtdSetShallowMacLoopbackLinkDown
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  linkDownSpeed,
    IN MTD_BOOL enable
);


#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif


#endif

