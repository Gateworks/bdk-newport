/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions and global defines/data for
high and low level interrupt functions of the Marvell 88X32X0, 
88X33X0, 88E20X0 and 88E21X0 ethernet PHYs.
********************************************************************/
#ifndef MTDINTR_H
#define MTDINTR_H
#if C_LINKAGE
#if defined __cplusplus 
    extern "C" { 
#endif 
#endif

/******************************************************************************
    Interrupt overview
    ------------------

The MTD interrupt has two levels. Top level interrupts (C-unit) and lower level 
interrupts (T-unit, H-unit and X-unit). There is one interrupt PIN per PHY. For 
multi-port PHYs, interrupts of each port are connected to the same interrupt PIN.

The interrupt pin is controlled at the top level interrupt API. The Top level 
API function mtdEnableDisableTopInterrupts() controls which interrupt(s) go to 
the PIN. The interrupt polarity at the PIN can be configured. You can also force 
the PIN active by mtdInterruptPinControl() function. If you don't plan to use
the PIN to implement an interrupt handler, you may leave all top level interrupts
disabled, and poll the status bits to implement a polled interrupt handler instead.

Interrupt PIN
    |
    ----- mtdInterruptPinControl()
    |
    ----- mtdEnableDisableTopInterrupts()
            |
            ---- Port level interrupts (WOL, Temperature, Frame to Register Memory, 
            |                           MACsec, Processor, GPIO).   
            |
            ---- mtdEnableDisableTunitInterrupts()
            |
            ---- mtdEnableDisableHunitInterrupts()
            |
            ---- mtdEnableDisableXunitInterrupts()

The Top level interrupt status will retain the lower level interrupt status until 
the lower level interrupt is cleared by reading it. The lower level interrupt 
enable/disable only controls if the interrupt will be sent to the top level 
interrupt status register. It will not affect the lower level interrupt status.

Example: To enable the T-unit Link status changed interrupt to the PIN, 
         use the following procedure:
    
    mtdEnableDisableTopInterrupts(devPtr, port, MTD_T_UNIT_INTR, MTD_TRUE);
    mtdEnableDisableTunitInterrupts(devPtr, port, MTD_LINK_STATUS_CHG_INTR, MTD_TRUE);

******************************************************************************/

typedef struct
{
    MTD_U16 baseRIntr; /* 10/5 GBASE-R */
    MTD_U32 x2x4Intr;  /* RXAUI/XAUI */
    MTD_U16 baseXIntr; /* 1000BX/2.5GBX/SGMII */
    MTD_U16 miscIntr;
} MTD_H_INTR_SRC;

typedef struct
{
    MTD_U16 baseRIntr; /*10/5 GBASE-R */
    MTD_U16 baseXIntr; /* 1000BX/2.5GB/SGMII */
    MTD_U16 miscIntr;
} MTD_X_INTR_SRC;

typedef struct
{
    MTD_U16 cunitIntr;
    MTD_U32 tunitIntr;
    MTD_H_INTR_SRC hunitIntr;
    MTD_X_INTR_SRC xunitIntr;
} MTD_INTR_STATUS;

/******************************************************************************
MTD_STATUS mtdGetPortIntrStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    OUT MTD_BOOL *interruptTrig,
    OUT MTD_INTR_STATUS *interruptStatus
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - port number, 0-31

 Outputs:
    interruptTrig - MTD_TRUE  = interrupt(s) triggered on this port
                    MTD_FALSE = no interrupt triggered on this port
    interruptStatus.cunitIntr - C-unit interrupt status 
            MTD_WOL_INTR                      0x0100
            MTD_TEMP_SENSOR_INTR              0x0080
            MTD_F2R_MEM_INTR                  0x0040
            MTD_MACSEC_INTR                   0x0020
            MTD_PROC_INTR                     0x0010
            MTD_GPIO_INTR                     0x0008
            MTD_M_UNIT_INTR                   0x0004
            MTD_X_UNIT_INTR                   0x0002   == not applicable to E20X0 and E21X0 PHYs 
            MTD_T_UNIT_INTR                   0x0001

    interruptStatus.tunitIntr - T-unit interrupt status
            MTD_SYMBOL_ERR_INTR           0x00200000
            MTD_FALSE_CARR_INTR           0x00100000
            MTD_TX_FIFO_OF_UF_INTR        0x00020000
            MTD_JABBER_INTR               0x00010000
            MTD_AN_ERR_INTR               0x00008000
            MTD_SPEED_CHG_INTR            0x00004000
            MTD_DX_CHG_INTR               0x00002000
            MTD_PAGE_RX_INTR              0x00001000
            MTD_AN_COMPLETED_INTR         0x00000800
            MTD_LINK_STATUS_CHG_INTR      0x00000400
            MTD_AN_MDI_CROS_CHG_INTR      0x00000040
            MTD_DOWNSHIFT_INTR            0x00000020
            MTD_ENG_DETECT_INTR           0x00000010
            MTD_FLP_XCHG_NO_LINK_INTR     0x00000008
            MTD_POLARITY_CHG_INTR         0x00000002

    interruptStatus.hunitIntr - H-unit interrupt status
            == X2/X4 Interrupts
            MTD_LINK_UP_TO_DN_INTR        0x00080000
            MTD_LINK_DN_TO_UP_INTR        0x00040000
            MTD_FAULT_LINE_TO_CORE_INTR   0x00000200
            MTD_FAULT_CORE_TO_LINE_INTR   0x00000100
            MTD_LN1_ENG_DETECT_CHG_INTR   0x00000020  == lane 1 Energy Detect Changed Interrupt
            MTD_LN0_ENG_DETECT_CHG_INTR   0x00000010  == lane 0 Energy Detect changed Interrupt
            MTD_LN1_SYNC_CHG_INTR         0x00000002
            MTD_LN0_SYNC_CHG_INTR         0x00000001
            == 5G/10G BaseR Interrupts
            MTD_BASER_LOCAL_FAULT_TX_INTR     0x0800
            MTD_BASER_LOCAL_FAULT_RX_INTR     0x0400
            MTD_BASER_LINK_STATUS_CHG_INTR    0x0004
            MTD_BASER_HIGH_BER_CHG_INTR       0x0002
            MTD_BASER_BLK_LOCK_CHG_INTR       0x0001
            == 1G/2.5GBASE-X Interrupts
            MTD_BASEX_SPEED_CHG_INTR          0x4000
            MTD_BASEX_DX_CHG_INTR             0x2000
            MTD_BASEX_PAGE_RX_INTR            0x1000
            MTD_BASEX_AN_COMPLETED_INTR       0x0800
            MTD_BASEX_LINK_UP_TO_DN_INTR      0x0400
            MTD_BASEX_LINK_DN_TO_UP_INTR      0x0200
            MTD_BASEX_SYMBOL_ERR_INTR         0x0100
            MTD_BASEX_FALSE_CARR_INTR         0x0080

    interruptStatus.xunitIntr - X-unit interrupt status 
            == 5G/10G BaseR Interrupts
            MTD_BASER_LOCAL_FAULT_TX_INTR     0x0800
            MTD_BASER_LOCAL_FAULT_RX_INTR     0x0400
            MTD_BASER_LINK_STATUS_CHG_INTR    0x0004
            MTD_BASER_HIGH_BER_CHG_INTR       0x0002
            MTD_BASER_BLK_LOCK_CHG_INTR       0x0001
            == 1G/2.5GBASE-X Interrupts
            MTD_BASEX_SPEED_CHG_INTR          0x4000
            MTD_BASEX_DX_CHG_INTR             0x2000
            MTD_BASEX_PAGE_RX_INTR            0x1000
            MTD_BASEX_AN_COMPLETED_INTR       0x0800
            MTD_BASEX_LINK_UP_TO_DN_INTR      0x0400
            MTD_BASEX_LINK_DN_TO_UP_INTR      0x0200
            MTD_BASEX_SYMBOL_ERR_INTR         0x0100
            MTD_BASEX_FALSE_CARR_INTR         0x0080

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function is provided to implement a polled interrupt handler.

    Get the status of all the triggered interrupts on this port. User should
    check the interruptTrig first, if it is MTD_TRUE, then get the interruptStatus. 

    Please check the interrupt definition of the corresponding unit to identify 
    the interrupt source.

    This function should be used to poll the interrupt status.

 Side effects:
    None

 Notes/Warnings:
    No X-unit on E20X0 and E21X0 PHYs. 

    All individual interrupts are cleared after this API call.
******************************************************************************/
MTD_STATUS mtdGetPortIntrStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16     port,
    OUT MTD_BOOL   *interruptTrig,
    OUT MTD_INTR_STATUS *interruptStatus
);

/******************************************************************************
MTD_STATUS mtdGetPortIntrStatusISR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16     port,
    OUT MTD_BOOL   *interruptTrig,
    OUT MTD_INTR_STATUS *interruptStatus
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - port number, 0-31

 Outputs:
    interruptTrig - MTD_TRUE  = interrupt(s) triggered on this port
                    MTD_FALSE = no interrupt triggered on this port
    interruptStatus.cunitIntr - C-unit interrupt status
            MTD_WOL_INTR                      0x0100
            MTD_TEMP_SENSOR_INTR              0x0080
            MTD_F2R_MEM_INTR                  0x0040
            MTD_MACSEC_INTR                   0x0020
            MTD_PROC_INTR                     0x0010
            MTD_GPIO_INTR                     0x0008
            MTD_M_UNIT_INTR                   0x0004
            MTD_X_UNIT_INTR                   0x0002   == not applicable to E20X0 and E21X0 PHYs
            MTD_T_UNIT_INTR                   0x0001

    interruptStatus.tunitIntr - T-unit interrupt status
            MTD_SYMBOL_ERR_INTR           0x00200000
            MTD_FALSE_CARR_INTR           0x00100000
            MTD_TX_FIFO_OF_UF_INTR        0x00020000
            MTD_JABBER_INTR               0x00010000
            MTD_AN_ERR_INTR               0x00008000
            MTD_SPEED_CHG_INTR            0x00004000
            MTD_DX_CHG_INTR               0x00002000
            MTD_PAGE_RX_INTR              0x00001000
            MTD_AN_COMPLETED_INTR         0x00000800
            MTD_LINK_STATUS_CHG_INTR      0x00000400
            MTD_AN_MDI_CROS_CHG_INTR      0x00000040
            MTD_DOWNSHIFT_INTR            0x00000020
            MTD_ENG_DETECT_INTR           0x00000010
            MTD_FLP_XCHG_NO_LINK_INTR     0x00000008
            MTD_POLARITY_CHG_INTR         0x00000002

    interruptStatus.hunitIntr - H-unit interrupt status
            == X2/X4 Interrupts
            MTD_LINK_UP_TO_DN_INTR        0x00080000
            MTD_LINK_DN_TO_UP_INTR        0x00040000
            MTD_FAULT_LINE_TO_CORE_INTR   0x00000200
            MTD_FAULT_CORE_TO_LINE_INTR   0x00000100
            MTD_LN1_ENG_DETECT_CHG_INTR   0x00000020  == lane 1 Energy Detect Changed Interrupt
            MTD_LN0_ENG_DETECT_CHG_INTR   0x00000010  == lane 0 Energy Detect changed Interrupt
            MTD_LN1_SYNC_CHG_INTR         0x00000002
            MTD_LN0_SYNC_CHG_INTR         0x00000001
            == 5G/10G BaseR Interrupts
            MTD_BASER_LOCAL_FAULT_TX_INTR     0x0800
            MTD_BASER_LOCAL_FAULT_RX_INTR     0x0400
            MTD_BASER_LINK_STATUS_CHG_INTR    0x0004
            MTD_BASER_HIGH_BER_CHG_INTR       0x0002
            MTD_BASER_BLK_LOCK_CHG_INTR       0x0001
            == 1G/2.5GBASE-X/SGMII Interrupts
            MTD_BASEX_SPEED_CHG_INTR          0x4000
            MTD_BASEX_DX_CHG_INTR             0x2000
            MTD_BASEX_PAGE_RX_INTR            0x1000
            MTD_BASEX_AN_COMPLETED_INTR       0x0800
            MTD_BASEX_LINK_UP_TO_DN_INTR      0x0400
            MTD_BASEX_LINK_DN_TO_UP_INTR      0x0200
            MTD_BASEX_SYMBOL_ERR_INTR         0x0100
            MTD_BASEX_FALSE_CARR_INTR         0x0080

    interruptStatus.xunitIntr - X-unit interrupt status 
            == 5G/10G BaseR Interrupts
            MTD_BASER_LOCAL_FAULT_TX_INTR     0x0800
            MTD_BASER_LOCAL_FAULT_RX_INTR     0x0400
            MTD_BASER_LINK_STATUS_CHG_INTR    0x0004
            MTD_BASER_HIGH_BER_CHG_INTR       0x0002
            MTD_BASER_BLK_LOCK_CHG_INTR       0x0001
            == 1G/2.5GBASE-X Interrupts
            MTD_BASEX_SPEED_CHG_INTR          0x4000
            MTD_BASEX_DX_CHG_INTR             0x2000
            MTD_BASEX_PAGE_RX_INTR            0x1000
            MTD_BASEX_AN_COMPLETED_INTR       0x0800
            MTD_BASEX_LINK_UP_TO_DN_INTR      0x0400
            MTD_BASEX_LINK_DN_TO_UP_INTR      0x0200
            MTD_BASEX_SYMBOL_ERR_INTR         0x0100
            MTD_BASEX_FALSE_CARR_INTR         0x0080

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    This function is provided to be called from an interrupt handler when triggered
    via the interrupt PIN to clear the interrupt and return all the
    interrupt reasons that triggered the interrupt.

    Get the status of all the enabled interrupts on this port. Interrupt enable 
    mask is checked in this API and only the unmasked interrupt statuses are checked,
    masked interrupt status are ignored.

    Please check the interrupt definition of the corresponding unit to identify 
    the interrupt source.

 Side effects:
    None

 Notes/Warnings:
    No X-unit on E20X0 and E21X0 PHYs. 
    
    All individual interrupts are cleared after this API call.
    
******************************************************************************/
MTD_STATUS mtdGetPortIntrStatusISR
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16     port,
    OUT MTD_BOOL   *interruptTrig,
    OUT MTD_INTR_STATUS *interruptStatus
);

/* Top interrupts */
#define MTD_WOL_INTR                   0x0100
#define MTD_TEMP_SENSOR_INTR           0x0080
#define MTD_F2R_MEM_INTR               0x0040
#define MTD_MACSEC_INTR                0x0020
#define MTD_PROC_INTR                  0x0010
#define MTD_GPIO_INTR                  0x0008
#define MTD_M_UNIT_INTR                0x0004
#define MTD_X_UNIT_INTR                0x0002  /* not applicable to E20X0 and E21X0 PHYs */ 
#define MTD_T_UNIT_INTR                0x0001
#define MTD_ALL_X32X0_X33X0_TOP_INTR  (MTD_WOL_INTR|MTD_TEMP_SENSOR_INTR|MTD_F2R_MEM_INTR|\
                                       MTD_MACSEC_INTR|MTD_PROC_INTR|MTD_GPIO_INTR|\
                                       MTD_M_UNIT_INTR|MTD_X_UNIT_INTR|MTD_T_UNIT_INTR)
#define MTD_ALL_E20X0_E21X0_TOP_INTR  (MTD_WOL_INTR|MTD_TEMP_SENSOR_INTR|MTD_F2R_MEM_INTR|\
                                       MTD_MACSEC_INTR|MTD_PROC_INTR|MTD_GPIO_INTR|\
                                       MTD_M_UNIT_INTR|MTD_T_UNIT_INTR)
/* Top interrupt polarity */
#define MTD_ACTIVE_LOW_INACTIVE_HIGH   0x0000
#define MTD_ACTIVE_HIGH_INACTIVE_LOW   0x0002
#define MTD_ACTIVE_LOW_INACTIVE_TRI    0x0004
#define MTD_ACTIVE_HIGH_INACTIVE_TRI   0x0006

/******************************************************************************
MTD_STATUS mtdEnableDisableTopInterrupts
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  interrupt_sel,
    IN MTD_BOOL  enable
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - port number, 0-31
    interrupt_sel - select single or multiple interrupts(OR together) from the list:
                    MTD_WOL_INTR        
                    MTD_TEMP_SENSOR_INTR
                    MTD_F2R_MEM_INTR    
                    MTD_MACSEC_INTR     
                    MTD_PROC_INTR       
                    MTD_GPIO_INTR       
                    MTD_M_UNIT_INTR      
                    MTD_X_UNIT_INTR      
                    MTD_T_UNIT_INTR

                    MTD_ALL_X32X0_X33X0_TOP_INTR
                       or
                    MTD_ALL_E20X0_E21X0_TOP_INTR

    enable - MTD_TRUE  = enable all selected interrupts 
             MTD_FALSE = disable all selected interrupts

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Enable or disable all selected top interrupts. 

 Side effects:
    None

 Notes/Warnings:
    No X-unit on E20X0 and E21X0 PHYs. Select MTD_X_UNIT_INTR on these PHYs 
    will return MTD_FAIL.

 Example:
 To enable MTD_MACSEC_INTR and MTD_T_UNIT_INTR interrupts:
   mtdEnableDisableTopInterrupts(devPtr,port,(MTD_MACSEC_INTR|MTD_T_UNIT_INTR),\
                                 MTD_TRUE);
 To disable MTD_MACSEC_INTR and MTD_T_UNIT_INTR interrupts:
   mtdEnableDisableTopInterrupts(devPtr,port,(MTD_MACSEC_INTR|MTD_T_UNIT_INTR),\
                                 MTD_FALSE);
******************************************************************************/
MTD_STATUS mtdEnableDisableTopInterrupts
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  interrupt_sel,
    IN MTD_BOOL enable
);

/******************************************************************************
MTD_STATUS mtdInterruptPinControl
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  polarity,
    IN MTD_BOOL force
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - port number, 0-31
    polarity - set interrupt polarity from the list:
               MTD_ACTIVE_LOW_INACTIVE_HIGH
               MTD_ACTIVE_HIGH_INACTIVE_LOW
               MTD_ACTIVE_LOW_INACTIVE_TRI 
               MTD_ACTIVE_HIGH_INACTIVE_TRI

    force  - MTD_TRUE  = force interrupt pin active (only first port has effect); 
             MTD_FALSE = normal operation

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Set interrupt pin polarity
    Force interrupt pin active

 Side effects:
    None

 Notes/Warnings:
******************************************************************************/
MTD_STATUS mtdInterruptPinControl
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  polarity,
    IN MTD_BOOL force
);

/******************************************************************************
MTD_STATUS mtdGetTopInterruptsEnabled
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    OUT MTD_U16 *interruptEnabled
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - port number, 0-31

 Outputs:
    interruptEnabled - enabled interrupts(OR together) from the list:
                MTD_WOL_INTR        
                MTD_TEMP_SENSOR_INTR
                MTD_F2R_MEM_INTR    
                MTD_MACSEC_INTR     
                MTD_PROC_INTR       
                MTD_GPIO_INTR       
                MTD_M_UNIT_INTR      
                MTD_X_UNIT_INTR      
                MTD_T_UNIT_INTR      
                MTD_ALL_TOP_INTR    

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Get enabled top interrupts. 

 Side effects:
    None

 Notes/Warnings:
******************************************************************************/
MTD_STATUS mtdGetTopInterruptsEnabled
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    OUT MTD_U16 *interruptEnabled
);

/******************************************************************************
MTD_STATUS mtdGetTopInterruptStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    OUT MTD_U16 *interruptStatus
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - port number, 0-31

 Outputs:
    interruptStatus - 
               MTD_WOL_INTR        
               MTD_TEMP_SENSOR_INTR
               MTD_F2R_MEM_INTR    
               MTD_MACSEC_INTR     
               MTD_PROC_INTR       
               MTD_GPIO_INTR       
               MTD_M_UNIT_INTR      
               MTD_X_UNIT_INTR      
               MTD_T_UNIT_INTR     

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Get top interrupt status. 

 Side effects:
    None

 Notes/Warnings:
    No X-unit on E20X0 and E21X0 PHYs. 
    The individual interrupt is not cleared until after call the local interrupt 
    status API to read and clear all the local interrupt status.
******************************************************************************/
MTD_STATUS mtdGetTopInterruptStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    OUT MTD_U16 *interruptStatus
);


/* H unit interrupt */
/* X2/X4 Interrupts */
#define MTD_LINK_UP_TO_DN_INTR         0x00080000
#define MTD_LINK_DN_TO_UP_INTR         0x00040000
#define MTD_FAULT_LINE_TO_CORE_INTR    0x00000200
#define MTD_FAULT_CORE_TO_LINE_INTR    0x00000100
#define MTD_LN1_ENG_DETECT_CHG_INTR    0x00000020  /* lane 1 Energy Detect Changed Interrupt */
#define MTD_LN0_ENG_DETECT_CHG_INTR    0x00000010  /* lane 0 Energy Detect changed Interrupt */
#define MTD_LN1_SYNC_CHG_INTR          0x00000002
#define MTD_LN0_SYNC_CHG_INTR          0x00000001
#define MTD_ALL_X2_X4_INTR            (MTD_LINK_UP_TO_DN_INTR|MTD_LINK_DN_TO_UP_INTR|\
                                       MTD_FAULT_LINE_TO_CORE_INTR|MTD_FAULT_CORE_TO_LINE_INTR|\
                                       MTD_LN1_ENG_DETECT_CHG_INTR|MTD_LN0_ENG_DETECT_CHG_INTR|\
                                       MTD_LN1_SYNC_CHG_INTR|MTD_LN0_SYNC_CHG_INTR)
/* X2/X4 Realtime status */
#define MTD_LN1_ENG_DETECT_STATUS      0x0020  /* lane 1 Energy Detect Status */
#define MTD_LN0_ENG_DETECT_STATUS      0x0010  /* lane 0 Energy Detect Status */
#define MTD_LN1_SYNC_STATUS            0x0002
#define MTD_LN0_SYNC_STATUS            0x0001

/******************************************************************************
MTD_STATUS mtdEnableDisableX2X4Interrupts
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U32  interrupt_sel,
    IN MTD_BOOL enable
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - port number, 0-31
    interrupt_sel - select single or multiple interrupts(OR together) from the list:
                MTD_LINK_UP_TO_DN_INTR   
                MTD_LINK_DN_TO_UP_INTR   
                MTD_FAULT_LINE_TO_CORE_INTR
                MTD_FAULT_LINE_TO_CORE_INTR
                MTD_LN1_ENG_DETECT_CHG_INTR
                MTD_LN0_ENG_DETECT_CHG_INTR
                MTD_LN1_SYNC_CHG_INTR      
                MTD_LN0_SYNC_CHG_INTR      
                MTD_ALL_X2_X4_INTR         

    enable - MTD_TRUE  = enable all selected interrupts 
             MTD_FALSE = disable all selected interrupts

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Enable or disable all selected interrupts. 

 Side effects:
    None

 Notes/Warnings:
 Example:
 To enable MTD_LINK_UP_TO_DN_INTR and MTD_LN0_SYNC_CHG_INTR interrupts:
   mtdEnableDisableX2X4Interrupts(devPtr,port,(MTD_LINK_UP_TO_DN_INTR|MTD_LN0_SYNC_CHG_INTR),\
                                  MTD_TRUE);
 To disable MTD_LINK_UP_TO_DN_INTR and MTD_LN0_SYNC_CHG_INTR interrupts:
   mtdEnableDisableX2X4Interrupts(devPtr,port,(MTD_LINK_UP_TO_DN_INTR|MTD_LN0_SYNC_CHG_INTR),\
                                  MTD_FALSE);
******************************************************************************/
MTD_STATUS mtdEnableDisableX2X4Interrupts
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U32  interrupt_sel,
    IN MTD_BOOL enable
);

/******************************************************************************
MTD_STATUS mtdGetX2X4InterruptsEnabled
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    OUT MTD_U32 *interruptEnabled
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - port number, 0-31

 Outputs:
    interruptEnabled - enabled interrupts:
                MTD_LINK_UP_TO_DN_INTR   
                MTD_LINK_DN_TO_UP_INTR   
                MTD_FAULT_LINE_TO_CORE_INTR
                MTD_FAULT_LINE_TO_CORE_INTR
                MTD_LN1_ENG_DETECT_CHG_INTR
                MTD_LN0_ENG_DETECT_CHG_INTR
                MTD_LN1_SYNC_CHG_INTR      
                MTD_LN0_SYNC_CHG_INTR      
                MTD_ALL_X2_X4_INTR         

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Get Enabled X2/X4 interrupts. 

 Side effects:
    None

 Notes/Warnings:
******************************************************************************/
MTD_STATUS mtdGetX2X4InterruptsEnabled
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    OUT MTD_U32 *interruptEnabled
);


/******************************************************************************
MTD_STATUS mtdGetX2X4InterruptStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    OUT MTD_U32 *interruptStatus
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - port number, 0-31

 Outputs:
    interruptStatus - 
             MTD_LINK_UP_TO_DN_INTR     
             MTD_LINK_DN_TO_UP_INTR     
             MTD_FAULT_LINE_TO_CORE_INTR
             MTD_FAULT_CORE_TO_LINE_INTR
             MTD_LN1_ENG_DETECT_CHG_INTR
             MTD_LN0_ENG_DETECT_CHG_INTR
             MTD_LN1_SYNC_CHG_INTR      
             MTD_LN0_SYNC_CHG_INTR      
      
 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Get X2/X4 interrupt status. The interrupts are cleared after this API call.

 Side effects:
    None

 Notes/Warnings:
    The interrupts are cleared after this API call. 
******************************************************************************/
MTD_STATUS mtdGetX2X4InterruptStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    OUT MTD_U32 *interruptStatus
);

/******************************************************************************
MTD_STATUS mtdGetX2X4RealTimeStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    OUT MTD_U16 *realTimeStatus
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - port number, 0-31

 Outputs:
    realTimeStatus - 
             MTD_LN1_ENG_DETECT_STATUS 
             MTD_LN0_ENG_DETECT_STATUS 
             MTD_LN1_SYNC_STATUS      
             MTD_LN0_SYNC_STATUS             

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Get X2/X4 realtime status. 

 Side effects:
    None

 Notes/Warnings:
******************************************************************************/
MTD_STATUS mtdGetX2X4RealTimeStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    OUT MTD_U16 *realTimeStatus
);

/* H and X unit interrupt. Note: E20X0 and E21X0 PHY have no X unit */
/* Interrupts - 5G/10GB-R */
#define MTD_BASER_LOCAL_FAULT_TX_INTR     0x0800
#define MTD_BASER_LOCAL_FAULT_RX_INTR     0x0400
#define MTD_BASER_LINK_STATUS_CHG_INTR    0x0004
#define MTD_BASER_HIGH_BER_CHG_INTR       0x0002
#define MTD_BASER_BLK_LOCK_CHG_INTR       0x0001
#define MTD_ALL_BASER_INTR               (MTD_BASER_LOCAL_FAULT_TX_INTR|MTD_BASER_LOCAL_FAULT_RX_INTR|\
                                          MTD_BASER_LINK_STATUS_CHG_INTR|MTD_BASER_HIGH_BER_CHG_INTR|\
                                          MTD_BASER_BLK_LOCK_CHG_INTR)
/* Realtime status - 5G/10GB-R */
#define MTD_LOCAL_FAULT_TX_STATUS         0x0800
#define MTD_LOCAL_FAULT_RX_STATUS         0x0400
#define MTD_JIT_0_LOCK_STATUS             0x0010
#define MTD_JIT_IF_LOCK_STATUS            0x0008
#define MTD_R_LINK_STATUS                 0x0004
#define MTD_HIGH_BER_STATUS               0x0002
#define MTD_BLK_LOCK_STATUS               0x0001

/******************************************************************************
MTD_STATUS mtdEnableDisableBaseRInterrupts
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  HorXunit,
    IN MTD_U16  interrupt_sel,
    IN MTD_BOOL enable
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - port number, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being read
    interrupt_sel - select single or multiple interrupts(OR together) from the list:
                    MTD_BASER_LOCAL_FAULT_TX_INTR 
                    MTD_BASER_LOCAL_FAULT_RX_INTR 
                    MTD_BASER_LINK_STATUS_CHG_INTR
                    MTD_BASER_HIGH_BER_CHG_INTR   
                    MTD_BASER_BLK_LOCK_CHG_INTR   
                    MTD_ALL_BASER_INTR            

     enable - MTD_TRUE  = enable all selected interrupts
              MTD_FALSE = disable all selected interrupts

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Enable or disable all selected interrupts. 

 Side effects:
    None

 Notes/Warnings:
    No X unit on E20X0 and E21X0 devices. Set HorXunit to MTD_X_UNIT on these 
    devices will return MTD_FAIL.

 Example:
 To enable MTD_BASER_HIGH_BER_CHG_INTR and MTD_BASER_BLK_LOCK_CHG_INTR interrupts:
   mtdEnableDisableBaseRInterrupts(devPtr,port,(MTD_BASER_HIGH_BER_CHG_INTR|MTD_BASER_BLK_LOCK_CHG_INTR),\
                                   MTD_TRUE);
 To disable MTD_BASER_HIGH_BER_CHG_INTR and MTD_BASER_BLK_LOCK_CHG_INTR interrupts:
   mtdEnableDisableBaseRInterrupts(devPtr,port,(MTD_BASER_HIGH_BER_CHG_INTR|MTD_BASER_BLK_LOCK_CHG_INTR),\
                                   MTD_FALSE);
******************************************************************************/
MTD_STATUS mtdEnableDisableBaseRInterrupts
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  HorXunit,
    IN MTD_U16  interrupt_sel,
    IN MTD_BOOL enable
);

/******************************************************************************
MTD_STATUS mtdGetBaseRInterruptsEnabled
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *interruptEnabled
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - port number, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being read
 Outputs:
    interruptEnabled - enabled interrupts:
                MTD_BASER_LOCAL_FAULT_TX_INTR 
                MTD_BASER_LOCAL_FAULT_RX_INTR 
                MTD_BASER_LINK_STATUS_CHG_INTR
                MTD_BASER_HIGH_BER_CHG_INTR   
                MTD_BASER_BLK_LOCK_CHG_INTR   
                MTD_ALL_BASER_INTR

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Get enabled 10GBASE-R interrupts. 

 Side effects:
    None

 Notes/Warnings:
    No X unit on E20X0 and E21X0 PHYs. Set HorXunit to MTD_X_UNIT on these 
    devices will return MTD_FAIL.
******************************************************************************/
MTD_STATUS mtdGetBaseRInterruptsEnabled
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *interruptEnabled
);


/******************************************************************************
MTD_STATUS mtdGetBaseRInterruptStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *interruptStatus
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - port number, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being read

 Outputs:
    interruptStatus - 
             MTD_BASER_LOCAL_FAULT_TX_INTR 
             MTD_BASER_LOCAL_FAULT_RX_INTR 
             MTD_BASER_LINK_STATUS_CHG_INTR
             MTD_BASER_HIGH_BER_CHG_INTR   
             MTD_BASER_BLK_LOCK_CHG_INTR   

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Get 10GBASE-R interrupts status. The interrupts are cleared after this API call.

 Side effects:
    None

 Notes/Warnings:
    The interrupts are cleared after this API call. 
    No X unit on E20X0 and E21X0 PHYs. Set HorXunit to MTD_X_UNIT on these 
    devices will return MTD_FAIL.
******************************************************************************/
MTD_STATUS mtdGetBaseRInterruptStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *interruptStatus
);

/******************************************************************************
MTD_STATUS mtdGetBaseRrealTimeStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *realTimeStatus
);

 Inputs:
    devPtr   - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port     - port number, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being read
 Outputs:
    realTimeStatus - 
             MTD_LOCAL_FAULT_TX_STATUS
             MTD_LOCAL_FAULT_RX_STATUS
             MTD_JIT_0_LOCK_STATUS    
             MTD_JIT_1_LOCK_STATUS    
             MTD_R_LINK_STATUS          
             MTD_HIGH_BER_STATUS      
             MTD_BLK_LOCK_STATUS                 

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Get 10GBASE-R realtime status. 

 Side effects:
    None

 Notes/Warnings:
    No X unit on E20X0 and E21X0 PHYs. Set HorXunit to MTD_X_UNIT on these 
    devices will return MTD_FAIL.
******************************************************************************/
MTD_STATUS mtdGetBaseRrealTimeStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *realTimeStatus
);

/* Interrupts- 1G/2.5GBASE-X for the X-unit*/
/* Interrupts- 1G/2.5GBASE-X/SGMII for the H-unit*/
#define MTD_BASEX_SPEED_CHG_INTR           0x4000
#define MTD_BASEX_DX_CHG_INTR              0x2000
#define MTD_BASEX_PAGE_RX_INTR             0x1000
#define MTD_BASEX_AN_COMPLETED_INTR        0x0800
#define MTD_BASEX_LINK_UP_TO_DN_INTR       0x0400
#define MTD_BASEX_LINK_DN_TO_UP_INTR       0x0200
#define MTD_BASEX_SYMBOL_ERR_INTR          0x0100
#define MTD_BASEX_FALSE_CARR_INTR          0x0080
#define MTD_ALL_BASEX_INTR                (MTD_BASEX_SPEED_CHG_INTR|MTD_BASEX_DX_CHG_INTR|\
                                           MTD_BASEX_PAGE_RX_INTR|MTD_BASEX_AN_COMPLETED_INTR|\
                                           MTD_BASEX_LINK_UP_TO_DN_INTR|MTD_BASEX_LINK_DN_TO_UP_INTR|\
                                           MTD_BASEX_SYMBOL_ERR_INTR|MTD_BASEX_FALSE_CARR_INTR)
/* Realtime Status- 1G/2.5GBASE-X */
#define MTD_RT_SPEED_STATUS                0x8000
#define MTD_RT_DX_STATUS                   0x2000
#define MTD_RT_PAGE_RX_STATUS              0x1000
#define MTD_RT_SPEED_DX_RESOLVED           0x0800
#define MTD_RT_LINK_STATUS                 0x0400
#define MTD_RT_SYNC_STATUS                 0x0020
#define MTD_RT_ENG_DETECT_STATUS           0x0010
#define MTD_RT_TX_PAUSE_STATUS             0x0008
#define MTD_RT_RX_PAUSE_STATUS             0x0004
                                          
/******************************************************************************
MTD_STATUS mtdEnableDisableBaseXInterrupts
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  HorXunit,
    IN MTD_U16  interrupt_sel,
    IN MTD_BOOL enable
);

 Inputs:
    devPtr   - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port     - port number, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being read
    interrupt_sel - select single or multiple interrupts(OR together) from the list:
                    MTD_BASEX_SPEED_CHG_INTR    
                    MTD_BASEX_DX_CHG_INTR       
                    MTD_BASEX_PAGE_RX_INTR      
                    MTD_BASEX_AN_COMPLETED_INTR 
                    MTD_BASEX_LINK_UP_TO_DN_INTR
                    MTD_BASEX_LINK_DN_TO_UP_INTR
                    MTD_BASEX_SYMBOL_ERR_INTR   
                    MTD_BASEX_FALSE_CARR_INTR   
                    MTD_ALL_BASEX_INTR          

     enable - MTD_TRUE  = enable all selected interrupts
              MTD_FALSE = disable all selected interrupts

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Enable or disable all selected interrupts. 

 Side effects:
    None

 Notes/Warnings:
    No X unit on E20X0 and E21X0 devices. Set HorXunit to MTD_X_UNIT on these 
    devices will return MTD_FAIL.

 Example:
 To enable MTD_BASEX_SPEED_CHG_INTR and MTD_BASEX_DX_CHG_INTR interrupts:
   mtdEnableDisableBaseXInterrupts(devPtr,port,(MTD_BASEX_SPEED_CHG_INTR|MTD_BASEX_DX_CHG_INTR),\
                                  MTD_TRUE);
 To disable MTD_BASEX_SPEED_CHG_INTR and MTD_BASEX_DX_CHG_INTR interrupts:
   mtdEnableDisableBaseXInterrupts(devPtr,port,(MTD_BASEX_SPEED_CHG_INTR|MTD_BASEX_DX_CHG_INTR),\
                                  MTD_FALSE);
******************************************************************************/
MTD_STATUS mtdEnableDisableBaseXInterrupts
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  HorXunit,
    IN MTD_U16  interrupt_sel,
    IN MTD_BOOL enable
);

/******************************************************************************
MTD_STATUS mtdGetBaseXInterruptsEnabled
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *interruptEnabled
);

 Inputs:
    devPtr   - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port     - port number, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being read
 Outputs:
    interruptEnabled - enabled interrupts:
                MTD_BASEX_SPEED_CHG_INTR    
                MTD_BASEX_DX_CHG_INTR       
                MTD_BASEX_PAGE_RX_INTR      
                MTD_BASEX_AN_COMPLETED_INTR 
                MTD_BASEX_LINK_UP_TO_DN_INTR
                MTD_BASEX_LINK_DN_TO_UP_INTR
                MTD_BASEX_SYMBOL_ERR_INTR   
                MTD_BASEX_FALSE_CARR_INTR   
                MTD_ALL_BASEX_INTR          

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Get Enabled SGMII interrupts. 

 Side effects:
    None

 Notes/Warnings:
    No X unit on E20X0 and E21X0 devices. Set HorXunit to MTD_X_UNIT on these 
    devices will return MTD_FAIL.
******************************************************************************/
MTD_STATUS mtdGetBaseXInterruptsEnabled
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *interruptEnabled
);

/******************************************************************************
MTD_STATUS mtdGetBaseXInterruptStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *interruptStatus
);

 Inputs:
    devPtr   - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port     - port number, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being read
 Outputs:
    interruptStatus - 
              MTD_BASEX_SPEED_CHG_INTR    
              MTD_BASEX_DX_CHG_INTR       
              MTD_BASEX_PAGE_RX_INTR      
              MTD_BASEX_AN_COMPLETED_INTR 
              MTD_BASEX_LINK_UP_TO_DN_INTR
              MTD_BASEX_LINK_DN_TO_UP_INTR
              MTD_BASEX_SYMBOL_ERR_INTR   
              MTD_BASEX_FALSE_CARR_INTR   
         
 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Get SGMII interrupts status. The interrupts are cleared after this API call.

 Side effects:
    None

 Notes/Warnings:
    The interrupts are cleared after this API call.
    No X unit on E20X0 and E21X0 devices. Set HorXunit to MTD_X_UNIT on these 
    devices will return MTD_FAIL.
******************************************************************************/
MTD_STATUS mtdGetBaseXInterruptStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *interruptStatus
);

/******************************************************************************
MTD_STATUS mtdGetBaseXrealTimeStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *realTimeStatus
);

 Inputs:
    devPtr   - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port     - port number, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being read
 Outputs:
    realTimeStatus -
             MTD_RT_SPEED_STATUS         
             MTD_RT_DX_STATUS        
             MTD_RT_PAGE_RX_STATUS       
             MTD_RT_SPEED_DX_RESOLVED
             MTD_RT_LINK_STATUS          
             MTD_RT_SYNC_STATUS          
             MTD_RT_ENG_DETECT_STATUS    
             MTD_RT_TX_PAUSE_STATUS                 
             MTD_RT_RX_PAUSE_STATUS      

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Get SGMII realtime status. 

 Side effects:
    None

 Notes/Warnings:
******************************************************************************/
MTD_STATUS mtdGetBaseXrealTimeStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *realTimeStatus
);

/* interrupt - Misc. */
#define MTD_CRC_INTR                   0x0004
#define MTD_FIFO_OVERFLOW_INTR         0x0002
#define MTD_FIFO_UNDERFLOW_INTR        0x0001
#define MTD_ALL_MISC_INTR             (MTD_CRC_INTR|MTD_FIFO_OVERFLOW_INTR|\
                                       MTD_FIFO_UNDERFLOW_INTR)
/******************************************************************************
MTD_STATUS mtdEnableDisableMiscInterrupts
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  HorXunit,
    IN MTD_U16  interrupt_sel,
    IN MTD_BOOL enable
);

 Inputs:
    devPtr   - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port     - port number, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being read
    interrupt_sel - select single or multiple interrupts(OR together) from the list:
                    MTD_CRC_INTR           
                    MTD_FIFO_OVERFLOW_INTR 
                    MTD_FIFO_UNDERFLOW_INTR
                    MTD_ALL_MISC_INTR      

     enable - MTD_TRUE  = enable all selected interrupts
              MTD_FALSE = disable all selected interrupts

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Enable or disable all selected interrupts. 

 Side effects:
    None

 Notes/Warnings:
    No X unit on E20X0 and E21X0 devices. Set HorXunit to MTD_X_UNIT on these 
    devices will return MTD_FAIL.

 Example:
 To enable MTD_CRC_INTR and MTD_FIFO_OVERFLOW_INTR interrupts:
   mtdEnableDisableMiscInterrupts(devPtr,port,(MTD_CRC_INTR|MTD_FIFO_OVERFLOW_INTR),\
                                  MTD_TRUE);
 To disable MTD_CRC_INTR and MTD_FIFO_OVERFLOW_INTR interrupts:
   mtdEnableDisableMiscInterrupts(devPtr,port,(MTD_CRC_INTR|MTD_FIFO_OVERFLOW_INTR),\
                                  MTD_FALSE);
******************************************************************************/
MTD_STATUS mtdEnableDisableMiscInterrupts
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  HorXunit,
    IN MTD_U16  interrupt_sel,
    IN MTD_BOOL enable
);

/******************************************************************************
MTD_STATUS mtdGetMiscInterruptsEnabled
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *interruptEnabled
);

 Inputs:
    devPtr   - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port     - port number, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being read
 Outputs:
    interruptEnabled - enabled interrupts:
                MTD_CRC_INTR           
                MTD_FIFO_OVERFLOW_INTR 
                MTD_FIFO_UNDERFLOW_INTR

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Get Enabled Misc. interrupts. 

 Side effects:
    None

 Notes/Warnings:
    No X unit on E20X0 and E21X0 devices. Set HorXunit to MTD_X_UNIT on these 
    devices will return MTD_FAIL.
******************************************************************************/
MTD_STATUS mtdGetMiscInterruptsEnabled
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *interruptEnabled
);

/******************************************************************************
MTD_STATUS mtdGetMiscInterruptStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *interruptStatus
);

 Inputs:
    devPtr   - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port     - port number, 0-31
    HorXunit - MTD_H_UNIT or MTD_X_UNIT, depending on which interface is
               being read
 Outputs:
    interruptStatus - 
              MTD_CRC_INTR           
              MTD_FIFO_OVERFLOW_INTR 
              MTD_FIFO_UNDERFLOW_INTR

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Get Misc. interrupts status. The interrupts are cleared after this API call.

 Side effects:
    None

 Notes/Warnings:
    The interrupts are cleared after this API call.
    No X unit on E20X0 and E21X0 devices. Set HorXunit to MTD_X_UNIT on these 
    devices will return MTD_FAIL.
******************************************************************************/
MTD_STATUS mtdGetMiscInterruptStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    IN MTD_U16   HorXunit,
    OUT MTD_U16 *interruptStatus
);

/* T-unit Interrupts */
#define MTD_SYMBOL_ERR_INTR           0x00200000
#define MTD_FALSE_CARR_INTR           0x00100000
#define MTD_TX_FIFO_OF_UF_INTR        0x00020000
#define MTD_JABBER_INTR               0x00010000
#define MTD_AN_ERR_INTR               0x00008000
#define MTD_SPEED_CHG_INTR            0x00004000 /* Speed change between 2.5G, 5G and 10G will not generate an interrupt */
#define MTD_DX_CHG_INTR               0x00002000
#define MTD_PAGE_RX_INTR              0x00001000
#define MTD_AN_COMPLETED_INTR         0x00000800
#define MTD_LINK_STATUS_CHG_INTR      0x00000400
#define MTD_AN_MDI_CROS_CHG_INTR      0x00000040
#define MTD_DOWNSHIFT_INTR            0x00000020
#define MTD_ENG_DETECT_INTR           0x00000010
#define MTD_FLP_XCHG_NO_LINK_INTR     0x00000008
#define MTD_POLARITY_CHG_INTR         0x00000002
#define MTD_ALL_TUNIT_INTR           (MTD_SYMBOL_ERR_INTR|MTD_FALSE_CARR_INTR|\
                                      MTD_TX_FIFO_OF_UF_INTR|MTD_JABBER_INTR|\
                                      MTD_AN_ERR_INTR|MTD_SPEED_CHG_INTR|\
                                      MTD_DX_CHG_INTR|MTD_PAGE_RX_INTR|\
                                      MTD_AN_COMPLETED_INTR|MTD_LINK_STATUS_CHG_INTR|\
                                      MTD_AN_MDI_CROS_CHG_INTR|MTD_DOWNSHIFT_INTR|\
                                      MTD_ENG_DETECT_INTR|MTD_FLP_XCHG_NO_LINK_INTR|\
                                      MTD_POLARITY_CHG_INTR)
/******************************************************************************
MTD_STATUS mtdEnableDisableTunitInterrupts
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U32  interrupt_sel,
    IN MTD_BOOL enable
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - port number, 0-31
    interrupt_sel - select single or multiple interrupts(OR together) from the list:
                    MTD_SYMBOL_ERR_INTR      
                    MTD_FALSE_CARR_INTR   
                    MTD_TX_FIFO_OV_UV_INTR   
                    MTD_JABBER_INTR          
                    MTD_AN_ERR_INTR          
                    MTD_SPEED_CHG_INTR       
                    MTD_DX_CHG_INTR      
                    MTD_PAGE_RX_INTR         
                    MTD_AN_COMPLETED_INTR    
                    MTD_LINK_STATUS_CHG_INTR     
                    MTD_AN_MDI_CROS_CHG_INTR 
                    MTD_DOWNSHIFT_INTR       
                    MTD_ENG_DETECT_INTR      
                    MTD_FLP_XCHG_NO_LINK_INTR
                    MTD_POLARITY_CHG_INTR    
                    MTD_ALL_TUNIT_INTR          

    enable - MTD_TRUE  = enable all selected interrupts
             MTD_FALSE = disable all selected interrupts

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Enable or disable all selected interrupts. 

 Side effects:
    None

 Notes/Warnings:
 Example:
 To enable MTD_SPEED_CHG_INTR and MTD_PAGE_RX_INTR interrupts:
   mtdEnableDisableTunitInterrupts(devPtr,port,(MTD_SPEED_CHG_INTR|MTD_PAGE_RX_INTR),\
                                   MTD_TRUE);
 To disable MTD_SPEED_CHG_INTR and MTD_PAGE_RX_INTR interrupts:
   mtdEnableDisableTunitInterrupts(devPtr,port,(MTD_SPEED_CHG_INTR|MTD_PAGE_RX_INTR),\
                                   MTD_FALSE);
******************************************************************************/
MTD_STATUS mtdEnableDisableTunitInterrupts
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U32  interrupt_sel,
    IN MTD_BOOL enable
);

/******************************************************************************
MTD_STATUS mtdGetTunitInterruptsEnabled
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U32 *interruptEnabled
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - port number, 0-31

 Outputs:
    interruptEnabled - enabled interrupts:
                MTD_SYMBOL_ERR_INTR      
                MTD_FALSE_CARR_INTR   
                MTD_TX_FIFO_OV_UV_INTR   
                MTD_JABBER_INTR          
                MTD_AN_ERR_INTR          
                MTD_SPEED_CHG_INTR       
                MTD_DX_CHG_INTR      
                MTD_PAGE_RX_INTR         
                MTD_AN_COMPLETED_INTR    
                MTD_LINK_STATUS_CHG_INTR     
                MTD_AN_MDI_CROS_CHG_INTR 
                MTD_DOWNSHIFT_INTR       
                MTD_ENG_DETECT_INTR      
                MTD_FLP_XCHG_NO_LINK_INTR
                MTD_POLARITY_CHG_INTR    
                MTD_ALL_TUNIT_INTR          

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Get Enabled or disabled interrupts. 

 Side effects:
    None

 Notes/Warnings:
******************************************************************************/
MTD_STATUS mtdGetTunitInterruptsEnabled
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    OUT MTD_U32 *interruptEnabled
);


/******************************************************************************
MTD_STATUS mtdGetTunitInterruptStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U32 *interruptStatus
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - port number, 0-31

 Outputs:
    interruptStatus - 
                MTD_SYMBOL_ERR_INTR      
                MTD_FALSE_CARR_INTR      
                MTD_TX_FIFO_OF_UF_INTR   
                MTD_JABBER_INTR          
                MTD_AN_ERR_INTR          
                MTD_SPEED_CHG_INTR       
                MTD_DX_CHG_INTR          
                MTD_PAGE_RX_INTR         
                MTD_AN_COMPLETED_INTR    
                MTD_LINK_STATUS_CHG_INTR     
                MTD_AN_MDI_CROS_CHG_INTR 
                MTD_DOWNSHIFT_INTR       
                MTD_ENG_DETECT_INTR      
                MTD_FLP_XCHG_NO_LINK_INTR
                MTD_POLARITY_CHG_INTR    
                
 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Get T-unit interrupt status. 

 Side effects:
    None

 Notes/Warnings:
    The interrupts are cleared after this API call.
******************************************************************************/
MTD_STATUS mtdGetTunitInterruptStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    OUT MTD_U32 *interruptStatus
);

#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif
