/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions prototypes and global defines/data for
higher-level functions that are used to interface with the 
X Unit (media/fiber interface) of the Marvell 88X32X0, 88X33X0, 
88E20X0 and 88E21X0 ethernet PHYs.
********************************************************************/
#ifndef MTDXUNIT_H
#define MTDXUNIT_H
#if C_LINKAGE
#if defined __cplusplus 
    extern "C" { 
#endif 
#endif


/******************************************************************************
 1000BX/SGMII functions
******************************************************************************/

/* defines for remote fault bits in 3.2004, 3.2005 */
#define MTD_1000BX_REMOTE_FAULT_NONE  0
#define MTD_1000BX_REMOTE_FAULT_LF    1 /* link failure */
#define MTD_1000BX_REMOTE_FAULT_OFFL  2 /* offline */
#define MTD_1000BX_REMOTE_FAULT_ANERR 3 /* autonegotiation error */
/******************************************************************************
 MTD_STATUS mtdSet1000BXAutoneg_Advertisement
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 remote_fault,
     IN MTD_U16 pause,
     IN MTD_BOOL restart_an    
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - port number, 0-31
    remote_fault - selects which remote fault will be advertised to link partner.
                   one of the following:
                       MTD_1000BX_REMOTE_FAULT_NONE  
                       MTD_1000BX_REMOTE_FAULT_LF    
                       MTD_1000BX_REMOTE_FAULT_OFFL  
                       MTD_1000BX_REMOTE_FAULT_ANERR 
    pause - selects what types of pause will be advertised to link partner.
            one of the following:
                MTD_CLEAR_PAUSE (none)      
                MTD_SYM_PAUSE        
                MTD_ASYM_PAUSE       
                MTD_SYM_ASYM_PAUSE   
    restart_an - MTD_TRUE if autonegotiation should be restarted after the above
                 fields are changed, MTD_FALSE if not (see note below for the
                 conditions needed for changes to take effect).            
 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function can be called to change the X unit's 1000BASE-X autonegotiation
    advertisement register, 3.2004. See the notes below for when these changes
    take effect and will be used for autonegotiation.

 Side effects:
    None

 Notes/Warnings:
    Changes to this register don't take effect until:
        1. autoneg is restarted
        2. link goes down
        3. software reset 3.2000.15 is asserted
        4. power down goes from down to up (3.2000.11)

    Call mtdGet1000BXAutoneg_Advertisement() to read currently selected values.

******************************************************************************/
MTD_STATUS mtdSet1000BXAutoneg_Advertisement
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 remote_fault,
    IN MTD_U16 pause,
    IN MTD_BOOL restart_an    
);

/******************************************************************************
 MTD_STATUS mtdGet1000BXAutoneg_Advertisement
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_U16 *remote_fault,
     OUT MTD_U16 *pause,
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - port number, 0-31

 Outputs:
    remote_fault - reports which remote fault will be advertised to link partner.
                   one of the following:
                       MTD_1000BX_REMOTE_FAULT_NONE  
                       MTD_1000BX_REMOTE_FAULT_LF    
                       MTD_1000BX_REMOTE_FAULT_OFFL  
                       MTD_1000BX_REMOTE_FAULT_ANERR 
    pause - reports what types of pause will be advertised to link partner.
            one of the following:
                MTD_CLEAR_PAUSE (none)  
                MTD_SYM_PAUSE        
                MTD_ASYM_PAUSE       
                MTD_SYM_ASYM_PAUSE   

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function can be called to read the X unit's 1000BASE-X autonegotiation
    advertisement register, 3.2004. See the notes below for when these changes
    take effect and will be used for autonegotiation.

 Side effects:
    None

 Notes/Warnings:
    Call mtdSet1000BXAutoneg_Advertisement() to change these values

******************************************************************************/
MTD_STATUS mtdGet1000BXAutoneg_Advertisement
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *remote_fault,
    OUT MTD_U16 *pause
);

/******************************************************************************
 MTD_STATUS mtdGet1000BXLinkPartner_Ability
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_BOOL *ack,
     OUT MTD_U16 *remote_fault,
     OUT MTD_U16 *pause,
     OUT MTD_BOOL *half_duplex,
     OUT MTD_BOOL *full_duplex
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - port number, 0-31

 Outputs:
    ack - MTD_TRUE if the link partner received the link code word, MTD_FALSE
          if not
    remote_fault - the value transmitted by the link partner for remote fault.
                   one of the following:
                        MTD_1000BX_REMOTE_FAULT_NONE  
                        MTD_1000BX_REMOTE_FAULT_LF    
                        MTD_1000BX_REMOTE_FAULT_OFFL  
                        MTD_1000BX_REMOTE_FAULT_ANERR 
    pause - the pause advertised by the link partner. one of the following:
                MTD_CLEAR_PAUSE (none)  
                MTD_SYM_PAUSE        
                MTD_ASYM_PAUSE       
                MTD_SYM_ASYM_PAUSE   
    half_duplex - MTD_TRUE if the link partner advertised 1000BASE-X half
                  duplex support, MTD_FALSE otherwise
    full_duplex - MTD_TRUE if the link partner advertised 1000BASE-X full
                  duplex support, MTD_FALSE otherwise                       

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function is used to read the X unit's 1000BASE-X Link Partner
    Ability register, 3.2005. This register is only valid in 1000BASE-X
    mode. Use mtdGetSGMIILinkPartner_Ability() to read the link partner
    ability when the X unit is in SGMII mode.

 Side effects:
    None

 Notes/Warnings:
    These values are cleared when the link goes down, and loaded when a 
    base page is received (should be read after the base page has been 
    received or after autoneg is complete).

******************************************************************************/
MTD_STATUS mtdGet1000BXLinkPartner_Ability
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *ack,
    OUT MTD_U16 *remote_fault,
    OUT MTD_U16 *pause,
    OUT MTD_BOOL *half_duplex,
    OUT MTD_BOOL *full_duplex
);

/******************************************************************************
 MTD_STATUS mtdGetSGMIILinkPartner_Ability
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port.
     OUT MTD_BOOL *link_status,
     OUT MTD_BOOL *ack,
     OUT MTD_BOOL *duplex,
     OUT MTD_U16 *speed,
     OUT MTD_BOOL *tx_pause,
     OUT MTD_BOOL *rx_pause,
     OUT MTD_BOOL *fiber_media,
     OUT MTD_BOOL *eee_enabled,
     OUT MTD_BOOL *clock_stop_lpi    
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - port number, 0-31

 Outputs:
    link_status - MTD_TRUE if PHY link status is up on link partner, MTD_FALSE
                  if not
    ack - MTD_TRUE if link partner received link code word, MTD_FALSE otherwise
    duplex - MTD_TRUE if PHY on link partner supports full duplex, MTD_FALSE
             if half duplex
    speed - PHY on link partner resolved to one of the following speeds:
                 MTD_SGMII_SPEED_10M
                 MTD_SGMII_SPEED_100M  
                 MTD_SGMII_SPEED_1G 
    tx_pause - MTD_TRUE if tx_pause is enabled, MTD_FALSE otherwise
    rx_pause - MTD_TRUE if rx_pause is enabled, MTD_FALSE otherwise
    fiber_media - MTD_TRUE if link partner's PHY is fiber media, MTD_FALSE if
                  it is copper media
    eee_enabled - MTD_TRUE if link partner's PHY resolved to use EEE, MTD_FALSE
                  if not
    clock_stop_lpi - MTD_TRUE if link partner's clock stops during LPI, MTD_FALSE
                     if not

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function is used to read the link partner's abilities received
    in the X unit (fiber interface) from 3.2005, SGMII Link Partner
    ability register. This function should only be called if the X unit
    is in SGMII mode.

 Side effects:
    None

 Notes/Warnings:
    These flags are cleared when the link partner's PHY link goes down, and set 
    upon receiving the SGMII autoneg base page from the link partner.

    This call is also used for 2.5G operation on 88X33X0/E20X0/E21X0 PHYs.

******************************************************************************/
MTD_STATUS mtdGetSGMIILinkPartner_Ability
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *link_status,
    OUT MTD_BOOL *ack,
    OUT MTD_BOOL *duplex,
    OUT MTD_U16 *speed,
    OUT MTD_BOOL *tx_pause,
    OUT MTD_BOOL *rx_pause,
    OUT MTD_BOOL *fiber_media,
    OUT MTD_BOOL *eee_enabled,
    OUT MTD_BOOL *clock_stop_lpi    
);

#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif


#endif


