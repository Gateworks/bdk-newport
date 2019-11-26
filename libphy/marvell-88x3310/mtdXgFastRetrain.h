/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions prototypes and global defines/data for
higher-level functions using MDIO access to control and get
status of the 10GBASE-T fast retrain functionality for the 
Marvell 88X32X0, 88X33X0, 88E20X0 and 88E21X0 ethernet PHYs.

For 88X33X0/88E20X0/88E21X0 family of PHY, it also allows configuring and checking
the 2.5/5GBASE-T fast retrain.
********************************************************************/
#ifndef MTDFR_H
#define MTDFR_H

#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif




/* The Marvell Phy 88X3240/88X3140 supports two types of fast retrain:
   the standard-defined one as specified in the 10GBASE-T standard, herein
   referred to 10GBTFR and a pre-standard version in the
   Cisco specification, "Negotiated Fast Retrain Revision 2.0", herein
   referred to as NFR. Both, neither, or either may be advertised.

   Both ends must support the same type of fast retrain for the fast
   retrain to be used once the link goes into data mode. If both ends
   support both fast retrains, the 10GBTFR will be used. 

   The combined fast retrain resolution is reported in 7.32781.12:10 
   for 88X32X0/88X3140 devices.

   Additionally 88X33X0/E20X0/E21X0 devices support the IEEE 2.5/5G 
   fast retrain (as advertised in 7.32/7.33). When the speed is
   resolved to 2.5G or 5G, the 2.5G/5G IEEE fast retrain resolution
   can be checked by AND together the local device and link partner 
   fast retrain bits.

   If NFR is advertised, it applies to 10G, 2.5G and 5G. There is
   no separate fast retrain speed control for NFR for these 
   three speeds. Advertising one, advertises all.

   NFR is the lowest priority of fast retrains. IEEE fast retrain
   always takes highest priority. */
/*******************************************************************
 Fast Retrain Control/Status - Top Level Functions

 Use these functions to configure/enable the NFR/10GBTFR and to 
 check the resolution to see which fast retrain type will be used
 following auto-negotiation.

 It is suggested to use only the top-level function for configuration.

 After the link is up, the function mtdGetFastRetrainResolution()
 should be called to determine the type of fast retrain which is being
 used. 

 While the link is up, mtdGetFastRetrainStatus() can be used to read
 the status (which will clear bits in 1.147) and the corresponding
 set of functions can be called to test the status (see the list of 
 functions in the description for mtdGetFastRetrainStatus()).

 If only the 10GBTFR is desired, the functions in the 10GBTFR section
 plus mtdGetFastRetrainStatus() can be used instead of the top-level
 functions.

 If only the NFR is desired, the functions in the NFR section plus
 mtdGetFastRetrainResolution() and mtdGetFastRetrainStatus() can 
 be used instead of the top-level configuration function.

 Most 10GBTFR functions are shared with the 2.5/5G fast retrain on
 88X33X0/88E20X0/88E21X0 devices. 

 If NFR is advertised for 10GBT, it is also being advertised
 for 2.5/5G (this is on 88X33X0/E20X0/E21X0 devices only).

 *******************************************************************/

// Different combinations for enabling both fast retrains for 10GBASE-T
#define MTD_DISABLE_FR          (0) // Disable all fast retrains
#define MTD_ENABLE_10GBTFR_ONLY (1) // Enable only the 10G standard-defined fast retrain
#define MTD_ENABLE_NFR_ONLY     (2) // Enable only the negotiated fast retrain (applies to 10G/2.5G/5G)
#define MTD_ENABLE_BOTH_FR      (3) // Enable both

// Type of signal to send MAC during fast retrain, note that both types of
// fast retrains share this setting. It's not possible to set different signalling
// for different fast retrains.
#define MTD_FR_IDLE                       0x00
#define MTD_FR_LOCAL_FAULT                0x01
#define MTD_FR_LINK_INTRRUPTION           0x02

// Different combinations for 2.5G and 5G fast retrain, only valid for
// 88X33X0/88E20X0/88E21X0 family of devices OR together to select multiple options
// and OR together with MTD_DISABLE_FR...MTD_ENABLE_BOTH_FR
#define MTD_DISABLE_MBT_FR      (0<<4) // Only this option is valid on 88X32X0 family of devices
#define MTD_ENABLE_2P5G_FR      (1<<4) // Advertise 2.5G fast retrain ability in info field
#define MTD_ENABLE_5G_FR        (2<<4) // Advertise 5G fast retrain ability in info field
#define MTD_SEND_2P5G_THP_REQ   (4<<4) // Request LP to reset THP at beginning of fast retrain
#define MTD_SEND_5G_THP_REQ     (8<<4) // Request LP to reset THP at beginning of fast retrain
/*****************************************************************************
MTD_STATUS mtdConfigureFastRetrain
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 fr_mode, 
    IN MTD_U16 frSignalType,
    IN MTD_BOOL anRestart
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

    fr_mode - Which fast retrains to enable and advertise. One of the following
        MTD_DISABLE_FR
        MTD_ENABLE_10GBTFR_ONLY 
        MTD_ENABLE_NFR_ONLY (this applies to 10G but also 2.5/5G on 88X33X0/E20X0/E21X0 devices)    
        MTD_ENABLE_BOTH_FR for 10GBASE-T (NFR will advertise fast retrain for 10G and 2.5/5G on devices supporting it)

        For 88X33X0/88E20X0/88E21X0 family of device, OR together with one or more of 
        MTD_DISABLE_MBT_FR...MTD_SEND_5G_THP_REQ to configure 2.5G 
        and/or 2G fast retrain.    

    frSignalType - type of signal to send during fast retrain. The options are ...
        MTD_FR_IDLE                       0x00
        MTD_FR_LOCAL_FAULT                0x01
        MTD_FR_LINK_INTRRUPTION           0x02

    anRestart - this takes the value of MTD_TRUE or MTD_FALSE and indicates 
                if auto-negotiation should be restarted following the speed 
                enable change. If this is MTD_FALSE, the change will not
                take effect until AN is restarted in some other way (link
                drop, toggle low power, toggle AN enable).

                If this is MTD_TRUE and AN has been disabled, it will be
                enabled before being restarted.
 
 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL, if action was successful or failed

    Will return MTD_FAIL if select a 2.5/5G option on an 88X32X0 device.
    
 Description: Configures the PHY to enable and advertise one, both, or none
 of the two types of fast retrains, 10GBTFR and NFR.
    
 Notes/Warnings:
    Examples. For 10G, pick one of MTD_DISABLE_FR...MTD_ENABLE_BOTH_FR

    On device 88X33X0/88E20X0/88E21X0 family can also OR in one or more of 2.5/5G options.

    mtdConfigureFastRetrain(devPtr,port,(MTD_ENABLE_10GBTFR_ONLY|
        MTD_ENABLE_2P5G_FR|MTD_ENABLE_5G_FR, MTD_FR_IDLE, MTD_TRUE);

    This call enables the IEEE 10GBT fast retrain and the 2.5/5G
    fast retrains, set the signal during fast retrain to be idle, and
    restarts AN after setting these.

******************************************************************************/
MTD_STATUS mtdConfigureFastRetrain
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 fr_mode, 
    IN MTD_U16 frSignalType,
    IN MTD_BOOL anRestart
);

// Status for 88X32X0 family of devices
#define MTD_FR_DISABLED       (0) // No common fast retrain found, or it's disabled
#define MTD_10GBTFR_RESOLVED  (1) // Both ends using 10GBTFR
#define MTD_NFR_RESOLVED      (2) // Both ends using NFR (applies to 10G as well as 2.5G/5G on devices supporting it)
// Additional status possible for 88X33X0/88E20X0/88E21X0 family of devices
#define MTD_2P5G_FR_RESOLVED  (3) // standard based fast retrain negotiated
#define MTD_5G_FR_RESOLVED    (4) // standard based fast retrain negotiated 
/*****************************************************************************
MTD_STATUS mtdGetFastRetrainResolution
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *frResolution
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 
 Outputs:
    frResolution - the type of fast retrain which will be used among the
        following:
             MTD_FR_DISABLED
             MTD_10GBTFR_RESOLVED
             MTD_NFR_RESOLVED (possible if link speed is 10G and on 
                               88X33X0/E20X0/E21X0 devices also applicable to 2.5/5G)

        on 88X33X0/88E20X0/88E21X0 family of devices might have additional resolution of
            MTD_2P5G_FR_RESOLVED
            MTD_5G_FR_RESOLVED    

 Returns:
    MTD_OK or MTD_FAIL, if query was successful or not
     
 Description: This function must be called only after auto-negotiation is complete
 and the link is up at 10BASE-T/2.5G or 5G speed in order
 to discover which type of fast retrain the PHY is using (if any). It uses
 the Marvell proprietary fast retrain resolution bits in 7.32781.12:10 to
 report the fast retrain resolution for 10GBASE-T and for MultiG-BASET
 it uses a combination of the advertised and LP ability register bits
 to report the resolution for 2.5G and 5G fast retrain.
    
 Notes/Warnings:
    10G fast retrain is resolved during AN, but 2.5/5G is not resolved
    until after link trains up.

    Check if autoneg is complete/done and the link is up before calling this
    function or use 1.129.0, LP info valid, before calling this function.

    2.5G and 5G applies only to 88X33X0/88E20X0/88E21X0 family of devices.
******************************************************************************/
MTD_STATUS mtdGetFastRetrainResolution
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *frResolution
);


/******************************************************************************
MTD_STATUS mtdGetFastRetrainStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 *currentValue
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    
 Outputs:
    currentValue - The value of the fast retrain status and control register
                   (1.147) 

 Returns:
    MTD_OK or MTD_FAIL, if query was successful or not

 Description:
    Reads the fast retrain status and control register (1.147) and 
    stores the value. This value is to be used later to check the status of 
    the various bits in this register by calling the functions listed below
    in the "Notes" section.

 Side effects:
    This register has self clearing bits. After this function has been
    called, those bits will be cleared.

 Notes/Warnings:
    The pointer value should be passed in to the following functions. Call
    mtdGetFastRetrainResolution() to determine which set of functions
    to use during data mode.

    If resolution was NFR, the following function is available for status:
    mtdGetLDNFRCount()

    If resolution was 10GBTFR (or 2.5/5G), the following functions are 
    available for status:
        mtdGetLP10GBTFRCount()
        mtdGetLD10GBTFRCount()
******************************************************************************/
MTD_STATUS mtdGetFastRetrainStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 *currentValue
);


/*******************************************************************
 Fast Retrain Control/Status for 10GBASE-T (see below for 2.5G
 and 5G fast retrain specific control/status)

 NOTE: Some API calls for 10GBASE-T are shared with 2.5G and
 5G. Please see the notes/warning sections for help with
 which functions are shared between 10G and 2.5/5G and which are
 10G only.
 *******************************************************************/
    
/*******************************************************************
 Fast Retrain Control/Status - NFR-specific Functions

 Use these functions to configure/enable and check the status of
 only the NFR (negotiated fast retrain).

 Advertising NFR on 88X33X0/E20X0/E21X0 devices advertised fast retrain
 on 10G as well as 2.5/5G.
 *******************************************************************/

/******************************************************************************
MTD_STATUS mtdAdvertNFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 frSignalType,
    IN MTD_BOOL anRestart
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

    frSignalType - type of signal to send during fast retrain. The options are ...
    MTD_FR_IDLE                       0x00
    MTD_FR_LOCAL_FAULT                0x01
    MTD_FR_LINK_INTRRUPTION           0x02
    
    anRestart - this takes the value of MTD_TRUE or MTD_FALSE and indicates 
                if auto-negotiation should be restarted following the speed 
                enable change. If this is MTD_FALSE, the change will not
                take effect until AN is restarted in some other way (link
                drop, toggle low power, toggle AN enable).

                If this is MTD_TRUE and AN has been disabled, it will be
                enabled before being restarted.
    
 Outputs:
    None.

 Returns:
    MTD_OK or MTD_FAIL, if action was successful or not

 Description:
    Reads the 10GBASE-T Auto negotiation control register 7.49158 and sets
    bit 0 to advertise NFR capability. Also sets the signal type bits in 1.147
    (which are shared with the 10GBTFR).
    
 Side effects:
    None. 
    
 Notes/Warnings:
    Autonegotiation must be restarted before the new setting will be used. The
    link will drop if it is up anRestart is set to MTD_TRUE.

    As a side effect, this function also disables 10GBTFR. Use top-level
    configuration function to enable both.

    On 88X33X0/E20X0/E21X0 devices advertising NFR for 10G also advertises it for
    2.5/5G.

******************************************************************************/
MTD_STATUS mtdAdvertNFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 frSignalType,
    IN MTD_BOOL anRestart
);

/******************************************************************************
MTD_STATUS mtdDoNotAdvertNFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL anRestart
)

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    anRestart - this takes the value of MTD_TRUE or MTD_FALSE and indicates 
                if auto-negotiation should be restarted following the speed 
                enable change. If this is MTD_FALSE, the change will not
                take effect until AN is restarted in some other way (link
                drop, toggle low power, toggle AN enable).

                If this is MTD_TRUE and AN has been disabled, it will be
                enabled before being restarted.
    
 Outputs:
    None.

 Returns:
    MTD_OK or MTD_FAIL, if action was successful or not

 Description:
    Sets 7.800C.0 to 0, and optionally restarts AN, to stop advertisement
    of NFR.
    
 Side effects:
    None. 
    
 Notes/Warnings:
    Autonegotiation must be restarted before the new setting will be used. The
    link will drop if it is up and anRestart is passed as MTD_TRUE.

    Disabling NFR on 88X33X0/E20X0/E21X0 devices will disable it for all 3 speeds,
    10G, 2.5G and 5G.

******************************************************************************/
MTD_STATUS mtdDoNotAdvertNFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL anRestart
);

/******************************************************************************
MTD_STATUS mtdLPNFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *lpNFRAbility    
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    
 Outputs:
    lpNFRAbility - MTD_TRUE - Link partner is capable of NFR
                   MTD_FALSE - Link partner is not capable of NFR

 Returns:
    MTD_OK or MTD_FAIL, if query was successful or not

 Description:
    Reads the Link Partner NFR Ability register 7.800D bit 0 and
    returns the bit value.
    
 Side effects:
    None. 
    
 Notes/Warnings:
    This must be called after the auto-negotiation process has finished.

******************************************************************************/
MTD_STATUS mtdLPNFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *lpNFRAbility
);

/******************************************************************************
MTD_STATUS mtdGetLDNFRCount
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 currentValue,
    OUT MTD_U16 *ldCount
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    currentValue - register value of 1.147 (fast retrain status and control reg)
        
 Outputs:
    ldCount - LD fast retrain count since last time it was "read"

 Returns:
    MTD_OK or MTD_FAIL depending on result of function

 Description:
    Gets the number of NFR fast retrains performed by the local device.
    It parses the information from the parameter passed in (currentValue).
    It returns the count.

 Side effects:
    None 
    
 Notes/Warnings:
    The function "mtdGetFastRetrainStatus" should be called first and the 
    register value should be passed in to this function.
******************************************************************************/
MTD_STATUS mtdGetLDNFRCount
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 currentValue,
    OUT MTD_U16 *ldCount
);


/*******************************************************************
 Fast Retrain Control/Status - 10GBTFR-specific Functions

 Use these functions to configure/enable and check the status of
 only the 10GBTFR (standard-defined fast retrain).

 Some of these are also applicable to 2.5/5G fast retrain on 88X33X0/88E20X0/88E21X0 
 devices.
 *******************************************************************/


/******************************************************************************
MTD_STATUS mtdGetLP10GBTFRCount
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 currentValue,
    OUT MTD_U16 *lpCount
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    currentValue - register value of 1.147 (fast retrain status and control reg)
        
 Outputs:
    lpCount - LP fast retrain count since last time it was "read"

 Returns:
    MTD_OK or MTD_FAIL depending on result of function

 Description:
    Gets the number of 10GBTFR fast retrains rqeuested by the link partner.
    It parses the information from the parameter passed in (currentValue)
    and returns the count.


 Side effects:
    None. 
    
 Notes/Warnings:
    The function "mtdGetFastRetrainStatus" should be called first and the 
    register value should be passed in to this function.

    This function is also valid on 88X33X0/88E20X0/88E21X0 devices when resolution
    is 2.5G or 5G.

******************************************************************************/
MTD_STATUS mtdGetLP10GBTFRCount
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 currentValue,
    OUT MTD_U16 *lpCount
);

/******************************************************************************
MTD_STATUS mtdGetLD10GBTFRCount
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 currentValue,
    OUT MTD_U16 *ldCount
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    currentValue - register value of 1.147 (fast retrain status and control reg)
        
 Outputs:
    ldCount - LD fast retrain count since last time it was "read"

 Returns:
    MTD_OK or MTD_FAIL depending on function success

 Description:
    Gets the number of 10GBTFR fast retrains requested by the local device.
    It parses the information from the parameter passed in (currentValue)
    and returns the count.

 Side effects:
    None 
    
 Notes/Warnings:
    The function "mtdGetFastRetrainStatus" should be called first and the 
    register value should be passed in to this function.

    This function is also valid on 88X33X0/88E20X0/88E21X0 devices when resolution
    is 2.5G or 5G.
    
******************************************************************************/
MTD_STATUS mtdGetLD10GBTFRCount
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 currentValue,
    OUT MTD_U16 *ldCount
);


/******************************************************************************
MTD_STATUS mtdIs10GBTFRNegotiated
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 currentValue,
    OUT MTD_BOOL *isNegotiated
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    currentValue - register value of 1.147 (fast retrain status and control reg)
        
 Outputs:
    isNegotiated - MTD_TRUE -> 10GBTFR was negotiated
                   MTD_FALSE -> 10GBTFR was not negotiated

 Returns:
   MTD_OK or MTD_FAIL depending on function success

 Description:
    Reads the Fast retrain negotiated bit and returns the bit value.
    MTD_TRUE if 10GBTFR was negotiated and MTD_FALSE if not negotiated.
    
 Side effects:
    None 
    
 Notes/Warnings:
    The function "mtdGetFastRetrainStatus" should be called first and the 
    register value should be passed in to this function.

    This is only applicable to 10G speed.
******************************************************************************/
MTD_STATUS mtdIs10GBTFRNegotiated
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 currentValue,
    OUT MTD_BOOL *isNegotiated
);

/******************************************************************************
MTD_STATUS mtdEnable10GBTFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 frSignalType
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    frSignalType - type of signal to send for fast retrain. The options are ...
        MTD_FR_IDLE                       0x00
        MTD_FR_LOCAL_FAULT                0x01
        MTD_FR_LINK_INTRRUPTION           0x02
        
 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL, if command was successful or not

 Description:
    Sets the signal type and enables 10GBTFR by setting the appropriate bits.
    
 Side effects:
    None. 
    
 Notes/Warnings:
    This is applicable to 10G and on 88X33X0/88E20X0/88E21X0 devices also applicable
    to 2.5/5G speeds.
******************************************************************************/
MTD_STATUS mtdEnable10GBTFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 frSignalType
);

/******************************************************************************
MTD_STATUS mtdDisable10GBTFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
            
 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL, if command was successful or not

 Description:
    This function disables 10GBTFR by writing '0' to the register (which
    also clears the signal type at the same time).
    
 Side effects:
    None. 
    
 Notes/Warnings:
    This function writes '0' to the whole register, 1.147. 
    The RO bits do not get affected by this. Counts are left intact since
    the register isn't read.

    Disabling 10GBTFR after the link is up with a resolution of 10GBTFR will
    cause a complete link drop the next time a fast retrain is needed at
    either end of the link.

    Do not call this function when the link is up with a resolution of NFR,
    otherwise the signal type requested may not be provided during NFR.

    This is applicable to 10G and on 88X33X0/88E20X0/88E21X0 devices also applicable
    to 2.5/5G speeds.
    
******************************************************************************/
MTD_STATUS mtdDisable10GBTFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);

/******************************************************************************
MTD_STATUS mtdAdvert10GBTFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL anRestart
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    anRestart - this takes the value of MTD_TRUE or MTD_FALSE and indicates 
                if auto-negotiation should be restarted following the speed 
                enable change. If this is MTD_FALSE, the change will not
                take effect until AN is restarted in some other way (link
                drop, toggle low power, toggle AN enable).

                If this is MTD_TRUE and AN has been disabled, it will be
                enabled before being restarted.
    
 Outputs:
    None.

 Returns:
    MTD_OK or MTD_FAIL, if command was successful or not

 Description:
    Reads the 10GBASE-T Auto negotiation control register 7.32 and sets
    bit 1 to advertise 10GBASE-T fast retrain capability.
    
 Side effects:
    None. 
    
 Notes/Warnings:
    Autonegotiation must be restarted before the new setting will be used. The
    link will drop if it is up and anRestart is passed as MTD_TRUE.

    This is only applicable to 10G fast retrain.

******************************************************************************/
MTD_STATUS mtdAdvert10GBTFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL anRestart
);

/******************************************************************************
MTD_STATUS mtdDoNotAdvert10GBTFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 anRestart
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    anRestart - this takes the value of MTD_TRUE or MTD_FALSE and indicates 
                if auto-negotiation should be restarted following the speed 
                enable change. If this is MTD_FALSE, the change will not
                take effect until AN is restarted in some other way (link
                drop, toggle low power, toggle AN enable).

                If this is MTD_TRUE and AN has been disabled, it will be
                enabled before being restarted.
    
 Outputs:
    None.

 Returns:
    MTD_OK or MTD_FAIL, if command was successful or not

 Description:
    Reads the 10GBASE-T Auto negotiation control register 7.32 and sets
    bit 1 to not advertise 10GBTFR capability.
    
 Side effects:
    None. 
    
 Notes/Warnings:
    Autonegotiation must be restarted before the new setting will be used. The
    link will drop if it is up and restart_an is passed as 1.

    This is only applicable to 10G fast retrain.

******************************************************************************/
MTD_STATUS mtdDoNotAdvert10GBTFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 anRestart
);

/******************************************************************************
MTD_STATUS mtdLP10GBTFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *lp10BTFRAble
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    
 Outputs:
    lp10BTFRAble - MTD_TRUE if the link partner advertised 10GBASE-T Fast
                   Retrain ability, MTD_FALSE otherwise

 Returns:
    MTD_OK or MTD_FAIL, if query was successful or not

 Description:
    Reads the Link Partner Fast Retrain ability  register 7.33 bit 1 and
    returns the bit value in lp10BTFRAble.
    
 Side effects:
    None. 
    
 Notes/Warnings:
    This must be called after the auto-negotiation process has finished.

    This is only applicable to LP 10G fast retrain.    

******************************************************************************/
MTD_STATUS mtdLP10GBTFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *lp10BTFRAble
);

/*******************************************************************
 Fast Retrain Control/Status for IEEE 2.5G and 5G fast retrain
 (multigbase-t) fast retrain.
 *******************************************************************/

/******************************************************************************
MTD_STATUS mtdAdvert2P5GBTFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL thpRequest,
    IN MTD_BOOL anRestart
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    thpRequest - if MTD_TRUE, sets 7.0040.3 = 1 to request LP
                 to reset THP at start of fast retrain, otherwise sets
                 it to 0
    anRestart - this takes the value of MTD_TRUE or MTD_FALSE and indicates 
                if auto-negotiation should be restarted following the speed 
                enable change. If this is MTD_FALSE, the change will not
                take effect until AN is restarted in some other way (link
                drop, toggle low power, toggle AN enable).

                If this is MTD_TRUE and AN has been disabled, it will be
                enabled before being restarted.
    
 Outputs:
    None.

 Returns:
    MTD_OK or MTD_FAIL, if command was successful or not

 Description:
    Reads the 10GBASE-T Auto negotiation control register 7.32 and sets
    bit 5 to advertise 2.5GBASE-T fast retrain capability in the info
    field during training.

    Also sets LP THP Reset Request based on thpRequest value.
    
 Side effects:
    None. 
    
 Notes/Warnings:
    Autonegotiation must be restarted before the new setting will be used. The
    link will drop if it is up and anRestart is passed as MTD_TRUE.

******************************************************************************/
MTD_STATUS mtdAdvert2P5GBTFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL thpRequest,
    IN MTD_BOOL anRestart
);

/******************************************************************************
MTD_STATUS mtdDoNotAdvert2P5GBTFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 anRestart
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    anRestart - this takes the value of MTD_TRUE or MTD_FALSE and indicates 
                if auto-negotiation should be restarted following the speed 
                enable change. If this is MTD_FALSE, the change will not
                take effect until AN is restarted in some other way (link
                drop, toggle low power, toggle AN enable).

                If this is MTD_TRUE and AN has been disabled, it will be
                enabled before being restarted.
    
 Outputs:
    None.

 Returns:
    MTD_OK or MTD_FAIL, if command was successful or not

 Description:
    Reads the 10GBASE-T Auto negotiation control register 7.32 and sets
    bit 5 to not advertise 2.5GBTFR capability.

 Side effects:
    None. 
    
 Notes/Warnings:
    Autonegotiation must be restarted before the new setting will be used. The
    link will drop if it is up and restart_an is passed as 1.

******************************************************************************/
MTD_STATUS mtdDoNotAdvert2P5GBTFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 anRestart
);


/******************************************************************************
MTD_STATUS mtdAdvert5GBTFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL thpRequest,
    IN MTD_BOOL anRestart
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    thpRequest - if MTD_TRUE, sets 7.0040.2 = 1 to request LP
                 to reset THP at start of fast retrain, otherwise sets
                 it to 0
    anRestart - this takes the value of MTD_TRUE or MTD_FALSE and indicates 
                if auto-negotiation should be restarted following the speed 
                enable change. If this is MTD_FALSE, the change will not
                take effect until AN is restarted in some other way (link
                drop, toggle low power, toggle AN enable).

                If this is MTD_TRUE and AN has been disabled, it will be
                enabled before being restarted.
    
 Outputs:
    None.

 Returns:
    MTD_OK or MTD_FAIL, if command was successful or not

 Description:
    Reads the 10GBASE-T Auto negotiation control register 7.32 and sets
    bit 6 to advertise 5GBASE-T fast retrain capability in the info
    field during training.

    Also sets LP THP Reset Request based on thpRequest value.
    
 Side effects:
    None. 
    
 Notes/Warnings:
    Autonegotiation must be restarted before the new setting will be used. The
    link will drop if it is up and anRestart is passed as MTD_TRUE.

******************************************************************************/
MTD_STATUS mtdAdvert5GBTFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL thpRequest,
    IN MTD_BOOL anRestart
);

/******************************************************************************
MTD_STATUS mtdDoNotAdvert5GBTFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 anRestart
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    anRestart - this takes the value of MTD_TRUE or MTD_FALSE and indicates 
                if auto-negotiation should be restarted following the speed 
                enable change. If this is MTD_FALSE, the change will not
                take effect until AN is restarted in some other way (link
                drop, toggle low power, toggle AN enable).

                If this is MTD_TRUE and AN has been disabled, it will be
                enabled before being restarted.
    
 Outputs:
    None.

 Returns:
    MTD_OK or MTD_FAIL, if command was successful or not

 Description:
    Reads the 10GBASE-T Auto negotiation control register 7.32 and sets
    bit 6 to not advertise 5GBTFR capability.

 Side effects:
    None. 
    
 Notes/Warnings:
    Autonegotiation must be restarted before the new setting will be used. The
    link will drop if it is up and restart_an is passed as 1.

******************************************************************************/
MTD_STATUS mtdDoNotAdvert5GBTFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 anRestart
);


/******************************************************************************
MTD_STATUS mtdIs2P5GBTFRNegotiated
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *isNegotiated,
    OUT MTD_BOOL *thpLdRequest,
    OUT MTD_BOOL *thpLpRequest
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    
        
 Outputs:
    isNegotiated - MTD_TRUE -> 2P5GBTFR was negotiated
                   MTD_FALSE -> 2P5GBTFR was not negotiated
    thpLdRequest - MTD_TRUE if 7.0040.3 is 1, MTD_FALSE otherwise
    thpLpRequest - MTD_TRUE if 7.0041.3 is 1, MTD_FALSE otherwise

 Returns:
   MTD_OK or MTD_FAIL depending on function success

 Description:
    Reads 7.0020.5 and 7.0021.3 to determine if LD and LP share 2.5G fast
    retrain ability and returns isNegotiated to MTD_TRUE if they do.

    Also reads 7.0040.3 and 7.0041.3 to return thpLdRequest and thpLpRequest.
    
 Side effects:
    None 
    
 Notes/Warnings:
    This function should not be called until after link is up at 2.5G speed.    
******************************************************************************/
MTD_STATUS mtdIs2P5GBTFRNegotiated
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,    
    OUT MTD_BOOL *isNegotiated,
    OUT MTD_BOOL *thpLdRequest,
    OUT MTD_BOOL *thpLpRequest
);

/******************************************************************************
MTD_STATUS mtdIs5GBTFRNegotiated
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,    
    OUT MTD_BOOL *isNegotiated,
    OUT MTD_BOOL *thpLdRequest,
    OUT MTD_BOOL *thpLpRequest
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    
        
 Outputs:
    isNegotiated - MTD_TRUE -> 5GBTFR was negotiated
                   MTD_FALSE -> 5GBTFR was not negotiated
    thpLdRequest - MTD_TRUE if 7.0040.2 is 1, MTD_FALSE otherwise
    thpLpRequest - MTD_TRUE if 7.0041.2 is 1, MTD_FALSE otherwise

 Returns:
   MTD_OK or MTD_FAIL depending on function success

 Description:
    Reads 7.0020.6 and 7.0021.4 to determine if LD and LP share 5G fast
    retrain ability and returns isNegotiated to MTD_TRUE if they do.

    Also reads 7.0040.2 and 7.0041.2 to return thpLdRequest and thpLpRequest.
    
 Side effects:
    None 
    
 Notes/Warnings:
    This function should not be called until after link is up at 5G speed.    
******************************************************************************/
MTD_STATUS mtdIs5GBTFRNegotiated
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,    
    OUT MTD_BOOL *isNegotiated,
    OUT MTD_BOOL *thpLdRequest,
    OUT MTD_BOOL *thpLpRequest
);

/******************************************************************************
MTD_STATUS mtdLP2P5GBTFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *lp2P5GBTFRAble
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    
 Outputs:
    lp2P5BGTFRAble - MTD_TRUE if the link partner advertised 2.5GBASE-T Fast
                   Retrain ability, MTD_FALSE otherwise

 Returns:
    MTD_OK or MTD_FAIL, if query was successful or not

 Description:
    Reads the Link Partner Fast Retrain ability  register 7.0021 bit 3 and
    returns the bit value in lp2P5GBTFRAble.
    
 Side effects:
    None. 
    
 Notes/Warnings:
    This must be called after the link is up at 2.5G.
******************************************************************************/
MTD_STATUS mtdLP2P5GBTFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *lp2P5GBTFRAble
);

/******************************************************************************
MTD_STATUS mtdLP5GBTFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *lp5GBTFRAble
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    
 Outputs:
    lp2P5BTFRAble - MTD_TRUE if the link partner advertised 5GBASE-T Fast
                   Retrain ability, MTD_FALSE otherwise

 Returns:
    MTD_OK or MTD_FAIL, if query was successful or not

 Description:
    Reads the Link Partner Fast Retrain ability  register 7.0021 bit 4 and
    returns the bit value in lp2P5GBTFRAble.
    
 Side effects:
    None. 
    
 Notes/Warnings:
    This must be called after the link is up at 5G.
******************************************************************************/
MTD_STATUS mtdLP5GBTFR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *lp5GBTFRAble
);


#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MTDFR_H */
