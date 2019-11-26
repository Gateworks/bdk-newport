/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions prototypes and global defines/data for
higher-level functions for controlling and getting status from 
the Control Unit (C Unit) of the Marvell 88X32X0, 88X33X0, 88E20X0 
and 88E21X0 ethernet PHYs.
********************************************************************/
#ifndef CUNIT_H
#define CUNIT_H
#if C_LINKAGE
#if defined __cplusplus 
    extern "C" { 
#endif 
#endif


/*******************************************************************
  Resets
  C Unit SW Reset
  T Unit SW Reset
  T Unit HW Reset
  Chip HW Reset
 *******************************************************************/

/******************************************************************************
 MTD_STATUS mtdCunitSwReset
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port
 )

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - port number, 0-31

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Performs a software reset on one particular port's C Unit. 

    Retain bits will keep the value that has been written to them. Non-
    retain bits will be reset to the hardware reset state.

    This bit is self clearing once the reset has been complete it will
    return to 0.

 Side effects:
    None

 Notes/Warnings:
    Software resets only the C Unit. The T Unit has its own software reset,
    use mtdSoftwareReset(), or hardware reset the T Unit.

    The T unit copper link may drop when this command is issued.

    Note below are for E21X0 devices only:

    E2140/E2180 when MACTYPE is DXGMII or QXGMII, cannot use the bit 15
    software reset, and instead should use bit 4 port software
    reset. This function checks for that case and uses the correct bit.

    Also, E21X0 devices uses a different register for reading and writing
    CUNIT port control. This function also handles that.

******************************************************************************/
MTD_STATUS mtdCunitSwReset
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);

/******************************************************************************
  NOTE: For T Unit Software Reset, call mtdSoftwareReset() in mtdAPI.c/h
******************************************************************************/

/******************************************************************************
 MTD_STATUS mtdTunitHwReset
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port
 )

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - port number, 0-31

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Performs a hardware reset on the T Unit. All register values will return
    to their hardware reset state.  

    If the firmware was loaded from flash, it will be reloaded from flash.

    If the chip was strapped to load firmware from the host, the firmware
    must be reloaded.

    This bit self clears.

 Side effects:
    None

 Notes/Warnings:
    Any strap values overriden by register 31.F008 will be latched in and take
    effect when this reset is performed.

    Note that this is the major difference between this hardware reset and
    the special software reset, 1.49152.15 in the T Unit.

    The T Unit hardware reset in the C Unit must be used if any new values
    in 31.F008 need to be re-latched to pick up the new strap values.

******************************************************************************/
MTD_STATUS mtdTunitHwReset
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);


/******************************************************************************
 MTD_STATUS mtdChipHardwareReset
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port
 )

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - this can be any port on the chip, entire chip is reset though

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Performs a chip-level hardware reset, 31.F001.14 <= 1. This should reset
    all state machines and restore all registers to their power-on state.

    All ports are reset. This is equivalent to a chip level hardware reset.

 Side effects:
    See below.

 Notes/Warnings:
    Any established data links will drop. The chip will return to the same
    state as the power-on state and must be reinitialized.

******************************************************************************/
MTD_STATUS mtdChipHardwareReset
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);


/*******************************************************************
  Macsec Configuration
  Macsec Set Control
  Macsec Get Control
 *******************************************************************/

#define MTD_MACSEC_POWERON (0x3)
#define MTD_MACSEC_SLEEP   (0x2)
#define MTD_MACSEC_RESET   (0x1)
#define MTD_FAULT_FORWARDING_OFF   (0x0) /* faults are terminated by mac inside phy */
#define MTD_FORWARD_LINK_FAULT     (0x1) /* faults are terminated by mac inside phy except link fault, which is forwarded */
#define MTD_FORWARD_NON_LINK_FAULT (0x2) /* link fault is terminated by mac inside phy, others are forwarded */
#define MTD_FORWARD_ALL_FAULT      (0x3) /* all faults are forwarded, no faults are terminated by mac inside phy */
/******************************************************************************
 MTD_STATUS mtdSetMacsecControl
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 powerControl,
     IN MTD_U16 faultForwardControl
 )

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - port number, 0-31
    powerControl - one of the following:
        MTD_MACSEC_POWERON to power up the Macsec block
        MTD_MACSEC_SLEEP to put the Macsec block in sleep mode
        MTD_MACSET_RESET to put the Macsec block into the reset state
    faultForwardControl - one of the following:
        MTD_FAULT_FORWARDING_OFF
        MTD_FORWARD_LINK_FAULT
        MTD_FORWARD_NON_LINK_FAULT
        MTD_FORWARD_ALL_FAULT

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL if setting the control failed

 Description:
    This function is used to power-up the Macsec block, power it down,
    or put it into the reset state. Writes to the C Unit bits
    31.F000.13:12.

    The Macsec block must be powered up prior to configuring it, if the
    block was not powered up during the power-on initialization.

    The power state of the Macsec is configured according to "powerControl"
    and the fault forwarding is configured according to "faultForwardControl".

 Side effects:
    None

 Notes/Warnings:
    If the Macsec is in reset or sleep, all faults are forwarded through.
    Fault forwarding configuration is only functional if the Macsec is powered
    up, otherwise all faults are passed through to the host.

******************************************************************************/
MTD_STATUS mtdSetMacsecControl
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 powerControl,
    IN MTD_U16 faultForwardControl
);

/******************************************************************************
 MTD_STATUS mtdGetMacsecControl
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_U16 *powerStatus,
     OUT MTD_U16 *faultForwardStatus
 )

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - port number, 0-31

 Outputs:
    powerStatus - one of the following:
        MTD_MACSEC_POWERON Macsec block is powered up
        MTD_MACSEC_SLEEP Macsec block is in sleep mode
        MTD_MACSET_RESET Macsec block is in the reset state
    faultForwardStatus - one of the following:    
        MTD_FAULT_FORWARDING_OFF
        MTD_FORWARD_LINK_FAULT
        MTD_FORWARD_NON_LINK_FAULT
        MTD_FORWARD_ALL_FAULT

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function reads the value of the Macsec power/reset bits in
    31.F000.13:12 and returns it in "powerStatus" and reads the 
    value of the fault forwarding configuration bits in
    31.F000.14 and 11 and returns the configuration in 
    "faultForwardStatus".

 Side effects:
    None

 Notes/Warnings:
    None

******************************************************************************/
MTD_STATUS mtdGetMacsecControl
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *powerStatus,
    OUT MTD_U16 *faultForwardStatus
);


/*******************************************************************
  C Unit Port Power Down
 *******************************************************************/

/******************************************************************************
 MTD_STATUS mtdSetPortPowerDown
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port.
     IN MTD_BOOL powerDown
 )

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - port number, 0-31
    powerDown - MTD_TRUE powers the port down, MTD_FALSE powers the port up

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Powers the port down if powerDown is MTD_TRUE by setting 31.F001.11 <= 1,
    or powers the port back up by setting the bit to 0
    if powerDown is MTD_FALSE.

 Side effects:
    None

 Notes/Warnings:
    Once the port is powered down, the F2R cannot be used to power the port
    back up! Only MDIO write or a hardware reset is capable of setting
    the power back on.
******************************************************************************/
MTD_STATUS mtdSetPortPowerDown
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL powerDown
);

/******************************************************************************
 MTD_STATUS mtdGetPortPowerDown
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port.
     OUT MTD_BOOL *powerDown
 )

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - port number, 0-31

 Outputs:
    powerDown - MTD_TRUE if powered down, MTD_FALSE if powered up

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Returns the value of the bit 31.F001.11, C Unit Port Power Down.

 Side effects:
    None

 Notes/Warnings:
    Once the port is powered down, the F2R cannot be used to power the port
    back up! Only MDIO write or a hardware reset is capable of setting
    the power back on.

******************************************************************************/
MTD_STATUS mtdGetPortPowerDown
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *powerDown
);

/*******************************************************************
  C Unit Top Configuration
 *******************************************************************/


#define MTD_F2R_OFF   (0) 
#define MTD_F2R_0BHDR (1)
#define MTD_F2R_4BHDR (2)
#define MTD_F2R_8BHDR (3)
#define MTD_MS_CU_ONLY         (0)
#define MTD_MS_FBR_ONLY        (1)
#define MTD_MS_AUTO_PREFER_CU  (2)
#define MTD_MS_AUTO_PREFER_FBR (3)
#define MTD_MS_USE_REDNDT_HOST (4)
#define MTD_MS_AUTO_FIRST_LINK (7)
#define MTD_FT_1000BASEX       (0)
#define MTD_FT_SGMII_SYSTEM    (1)
#define MTD_FT_SGMII_PHY       (2) /* unlikely to be used, but hardware supports it */
#define MTD_FT_10GBASER        (3)
#define MTD_FT_2500BASEX       (4) /* only available on 33X0 devices */
#define MTD_FT_5GBASER         (7) /* only available on 33X0 devices */
#define MTD_FT_NONE            (8) /* for E20X0 which have no fiber interface */
/******************************************************************************
 MTD_STATUS mtdSetCunitTopConfig
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 frameToRegister,
     IN MTD_U16 mediaSelect,
     IN MTD_U16 fiberType,
     IN MTD_BOOL npMediaEnergyDetect,
     IN MTD_BOOL maxPowerTunitAMDetect,
     IN MTD_BOOL softwareReset,
    IN MTD_BOOL rerunSerdesInitialization         
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - port number, 0-31
    frameToRegister - overwrites the Frame-To-Register strapped at power-on.
        One of the following:
            MTD_F2R_OFF 
            MTD_F2R_0BHDR
            MTD_F2R_4BHDR
            MTD_F2R_8BHDR    
        Changing this parameter requires a software reset for the change
        to take effect.
        
    mediaSelect - overwrites the media select strapped at power-on.
        One of the following:
            MTD_MS_CU_ONLY
            MTD_MS_FBR_ONLY
            MTD_MS_AUTO_PREFER_CU
            MTD_MS_AUTO_PREFER_FBR
            MTD_MS_USE_REDNDT_HOST
            MTD_MS_AUTO_FIRST_LINK    
        Changing this parameter requires a software reset for the change
        to take effect.
    
    fiberType - overwrites the fiber type selected by strap option. 
        One of the following:
            MTD_FT_1000BASEX
            MTD_FT_SGMII_SYSTEM
            MTD_FT_SGMII_PHY
            MTD_FT_10GBASER    
            
            On 33X0 devices also may set the following values:
            MTD_FT_2500BASEX
            MTD_FT_5GBASER

            On E20X0
            MTD_FT_NONE
            
        Changing this parameter requires a software reset for the change
        to take effect.
    
    npMediaEnergyDetect - MTD_TRUE or MTD_FALSE to set the non-preferred
        media energy detect enable.
    maxPowerTunitAMDetect - MTD_TRUE or MTD_FALSE to set the max power
        consumption for T Unit auto-media detect
    softwareReset - MTD_TRUE or MTD_FALSE to perfom a software reset
        after changing the top configuration.
    rerunSerdesInitialization - MTD_TRUE if any parameter that is likely to change the speed
        of the H or X unit serdes interface was performed like mediaSelect or fiberType will attempt
        to reset both serdes (this needs to be done AFTER the soft reset, so if softwareResetCunit
        is passed as MTD_FALSE, host must later call 
        mtdRerunSerdesAutoInitUseAutoMode() eventually to re-init the serdes).        

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Writes C Unit configuration in 31.F000 and 31.F001 according to parameters
    passed in above. Several of these parameters require a software reset
    of the C Unit before they take effect. Pass in softwareReset
    to MTD_TRUE to have this API function do the software reset after 
    changing all the values.

    Note that if softwareReset is MTD_TRUE, a software reset of the C 
    unit (31.F001.15 = 1) is done. In addition, if this flag is true,
    and the mediaSelect is being set to MTD_MS_FBR_ONLY, a software
    reset of the T unit is also performed.

    This function is not supported on E21X0 devices. It will return an error
    if called. None of these parameters are configurable on E21X0 devices.

 Side effects:
    None

 Notes/Warnings:
    If the link is up when this function is called, the link will drop
    if softwareResetCunit is set to MTD_TRUE.

    Only use MTD_FALSE for softwareReset if planning to do the C Unit
    software reset at a later time. Changes will not take effect until
    the software reset has been done. A few of these parameters do not 
    require a software reset. See the datasheet for details.

    When setting mediaSelect to MTD_MS_FBR_ONLY, a software reset
    of the T unit following the C unit software reset is also required.

    rerunSerdesInitialization is only checked if softwareReset is MTD_TRUE.

******************************************************************************/
MTD_STATUS mtdSetCunitTopConfig
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 frameToRegister,
    IN MTD_U16 mediaSelect,
    IN MTD_U16 fiberType,
    IN MTD_BOOL npMediaEnergyDetect,
    IN MTD_BOOL maxPowerTunitAMDetect,
    IN MTD_BOOL softwareReset,
    IN MTD_BOOL rerunSerdesInitialization    
);

/******************************************************************************
 MTD_STATUS mtdGetCunitTopConfig
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_U16 *frameToRegister,
     OUT MTD_U16 *mediaSelect,
     OUT MTD_U16 *fiberType,
     OUT MTD_BOOL *npMediaEnergyDetect,
     OUT MTD_BOOL *maxPowerTunitAMDetect
 );


 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - port number, 0-31

 Outputs:
    frameToRegister - current register value of this setting.
        One of the following:
        MTD_F2R_OFF 
        MTD_F2R_0BHDR
        MTD_F2R_4BHDR
        MTD_F2R_8BHDR    
    mediaSelect - current register value of this setting.
        One of the following:
        MTD_MS_CU_ONLY
        MTD_MS_FBR_ONLY
        MTD_MS_AUTO_PREFER_CU
        MTD_MS_AUTO_PREFER_FBR
        MTD_MS_USE_REDNDT_HOST
        MTD_MS_AUTO_FIRST_LINK    
    fiberType - current register value of this setting. 
        One of the following:
        MTD_FT_1000BASEX
        MTD_FT_SGMII_SYSTEM
        MTD_FT_SGMII_PHY
        MTD_FT_10GBASER    

        On 33X0 devices also may get the following values:
        MTD_FT_2500BASEX
        MTD_FT_5GBASER

        On E20X0/E21X0
        MTD_FT_NONE  
        
    npMediaEnergyDetect - current register value of this bit
        MTD_TRUE or MTD_FALSE
    maxPowerTunitAMDetect - current register value of this bit
        MTD_TRUE or MTD_FALSE
        
 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Reads the C Unit configuration in 31.F000 and 31.F001 and returns
    the values in the corresponding variables above.

 Side effects:
    None

 Notes/Warnings:
    The current value from the register is returned. If a software reset
    was not performed after the value was written, the values here may
    not be the currently used value.

******************************************************************************/
MTD_STATUS mtdGetCunitTopConfig
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *frameToRegister,
    OUT MTD_U16 *mediaSelect,
    OUT MTD_U16 *fiberType,
    OUT MTD_BOOL *npMediaEnergyDetect,
    OUT MTD_BOOL *maxPowerTunitAMDetect
);

#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif

