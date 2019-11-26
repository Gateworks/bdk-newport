/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions, data structures and definitions for All
levels, interrupt functions, Real-time Status and I/O pin mode
configurations for the Marvell X7120/X6181/X6141 PHY.
********************************************************************/
#ifndef MYD_INTR_IO_H
#define MYD_INTR_IO_H

#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

/******************************************************************************
 DO NOT modify enumerations - order and values are closely coupled to the code
 and register bit definitions.
******************************************************************************/
typedef enum _MYD_PIN_ID
{
    MYD_PIN_GPIO0 = 0,              /* Not available on X7120 */
    MYD_PIN_GPIO1,
    MYD_PIN_GPIO2,
    MYD_PIN_GPIO3,
    MYD_PIN_GPIO4,                  /* Not available on X6141 */
    MYD_PIN_INTn = 5,
    MYD_PIN_CLK_OUT_SE1,
    MYD_PIN_CLK_OUT_SE2,
    MYD_PIN_CLK_OUT_DIFF_N,         /* Not available on X6141 */
    MYD_PIN_CLK_OUT_DIFF_P          /* Not available on X6141 */
} MYD_PIN_ID;

typedef enum _MYD_PIN_MODE
{
    MYD_PIN_MODE_BACKPRESSURE = 0,
    MYD_PIN_MODE_GPIO,
    MYD_PIN_MODE_LED,
    MYD_PIN_MODE_INTR,
    MYD_PIN_MODE_RCLK,
    MYD_PIN_MODE_NUMS
} MYD_PIN_MODE;

typedef enum _MYD_LED_ID
{
    MYD_LED0 = 0,
    MYD_LED1,
    MYD_LED2,
    MYD_LED3,
    MYD_LED4,
    MYD_LED5
} MYD_LED_ID;

/******************************************************************************
    Interrupt overview
    ------------------

The MYD device has one interrupt PIN (Top level interrupts) per device.
For multi-port devices, interrupts of each port are connected to the same interrupt PIN.

The MYD interrupt has three levels. Top level interrupts (Level 1, aggregates interrupts
from all ports), Port Level Interrupts (Level 2) and Unit Level Interrupts (Level 3).
For example, PCS units have interrupt generated on each lane for Link Change,
Fault Signal, CRC Error, RM FIFO Interrupt, etc.

The PIN itself can be configured (polarity/tristate). You can also force
the PIN active by calling the mydSetGlobalInterruptCntl() function. If you don't plan to
use the PIN to implement an interrupt handler, you may poll the status bits to implement
a polled interrupt handler instead.

    - Top Level Interrupt (INTn PIN, Level 1)
    ----- mydGetIntrSrcStatus()
    |
    ----- mydGetEnabledIntrSrcISR()
        |
        - Port level interrupts (Level 2)
        ----- mydGetGlobalInterruptCntl()
        |
        ----- mydGetPerPortGlobalIntrStatus()
            |
            - Unit Level Interrupts (Level 3)
            ---- mydGetPCSInterruptEnable()
            |
            ---- mydGetPCSInterruptStatus()
            |
            ---- mydGetGPIOInterruptEnable()
            |
            ---- mydGetGPIOInterruptStatus()

The upper level interrupt status will retain the lower level interrupt status until
the lower level interrupt is cleared by reading it. The Unit level interrupt
enable only controls if the interrupt will be sent to the Port level interrupt status
register. It will not affect the Unit level interrupt status.

******************************************************************************/

/* See bit definitions of mydSetPCSInterruptEnable for PCS interrupt details */
typedef struct _MYD_PCS_INTR
{
    MYD_U16 srcGroup1[MYD_NUM_LANES];
    MYD_U16 srcGroup2[MYD_NUM_LANES]; /* only valid for 40GBR/50GBR and 100GBR */
} MYD_PCS_INTR;

typedef struct _MYD_PORT_INTR
{
    MYD_BOOL forceInterrupt;
    MYD_BOOL chainedIntr; /* Chained interrupt coming from last port */
    MYD_U16 gpioIntr;
    MYD_BOOL rmFIFOIntr;
    MYD_BOOL onChipProcIntr;
    MYD_PCS_INTR hostIntr;
    MYD_PCS_INTR lineIntr;
} MYD_PORT_INTR;

/*******************************************************************************
MYD_STATUS mydGetIntrSrcStatus
(
    IN MYD_DEV_PTR pDev,
    OUT MYD_PORT_INTR *portsIntrStatusArray
);


 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call

 Outputs:
    portsIntrStatusArray - returns a structure containing all level interrupt status.
                           Caller MUST pass in correct size of array to read all ports'
                           interrupt. The size of array MUST match the number of port
                           of the device. See structure definition above.

 Returns:
    MYD_OK   if there were no errors
    MYD_FAIL if there were errors

 Description:
    This function is provided to poll ALL interrupt status of ALL ports on the device.

    Please check the interrupt definition of the corresponding unit to identify
    the Unit-level(Level 3) PCS interrupt source.

    If portsIntrStatusArray[portIndex].gpioIntr returns a 1, users should check/be
    aware of the Pin mode and consider calling mydGetGPIOInterruptStatus() to poll
    which Pin is generating the Level 3 GPIO Interrupt.

 Side effects:
    None.

 Notes/Warnings:
    Only GPIO and PCS Units interrupts is supported in the Level 3.
    Calling this function will clear all latched PCS units interrupt status.

*******************************************************************************/
MYD_STATUS mydGetIntrSrcStatus
(
    IN MYD_DEV_PTR pDev,
    OUT MYD_PORT_INTR *portsIntrStatusArray
);

/*******************************************************************************
MYD_STATUS mydGetEnabledIntrSrcISR
(
    IN MYD_DEV_PTR pDev,
    OUT MYD_PORT_INTR *portsIntrSrcArray
);


 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call

 Outputs:
    portsIntrSrcArray - returns a structure containing all interrupt source. Caller
                        MUST pass in correct size of array to read all ports' interrupt.
                        The size of array MUST match the number of port of the device.
                        See structure definition above.

 Returns:
    MYD_OK   if there were no errors
    MYD_FAIL if there were errors

 Description:
    This function is provided to be called from an interrupt handler when INTn PIN
    has indicated an interrupt. If INTn Pin is configured to MYD_PIN_MODE_RCLK,
    the output of this API is INVALID.

    For PCS unit interrupts, ONLY enabled interrupt sources will be returned.

    As described in the "Interrupt overview", all interrupts generated on the device
    will be aggregated to the INTn PIN. Call this function to read
    the enabled interrupt sources if INTn PIN generates interrupt to know which
    source(s) are requesting an interrupt service.

    Please check the interrupt definition of the corresponding unit to identify
    the Unit-level(Level 3) PCS interrupt source.

    If portsIntrStatusArray[portIndex].gpioIntr returns a 1, users should check/be
    aware of the Pin mode they configured and consider calling mydGetGPIOInterruptEnable()
    and mydGetGPIOInterruptStatus() to check which GPIO Pin is generating
    unmasked(Enabled) Level 3 GPIO Interrupt.

 Side effects:
    None.

 Notes/Warnings:
    Only GPIO and PCS Units interrupts is supported in the Level 3.
    Calling this function will clear all latched PCS units interrupt status.

 Sample: Check PCS Host interrupt on 3rd mdioPort, using 100GBASE-R2 PCS

        MYD_DEV_PTR pDev;
        MYD_U16 laneOffset;
        MYD_U16 intrEnabled1[4], intrEnabled2[4];
        MYD_PORT_INTR portsIntrSrcArray[4];
        mydGetEnabledIntrSrcISR(pDev, portsIntrSrcArray);
        if (portsIntrSrcArray[2] != 0)
        {
            if (portsIntrSrcArray[2].hostIntr != 0)
            {
                for (laneOffset = 0; laneOffset < 4; laneOffset+=2)
                {
                    intrEnabled1[laneOffset] = portsIntrSrcArray[2].hostIntr.srcGroup1[laneOffset];
                    intrEnabled2[laneOffset] = portsIntrSrcArray[2].hostIntr.srcGroup2[laneOffset];
                }
            }
        }
        There are 2 registers for 100GBASE-R2 PCS interrupts. Please refer to the
        bit definitions above API mydSetPCSInterruptEnable() for details.

*******************************************************************************/
MYD_STATUS mydGetEnabledIntrSrcISR
(
    IN MYD_DEV_PTR pDev,
    OUT MYD_PORT_INTR *portsIntrSrcArray
);

/* NOTE: These bits may only be changed on the first port of a multi-port device to
   control the actual interrupt pin.

   Bit setting for MYD_INTR_TRISTATE_BIT and MYD_INTR_POLARITY_BIT
   00 = Active - drive INTn low, Inactive - drive INTn high
   01 = Active - drive INTn high, Inactive - drive INTn low
   10 = Active - drive INTn low, Inactive - tristate INTn
   11 = Active - drive INTn high, Inactive - tristate INTn
   example: (MYD_INTR_POLARITY_BIT | MYD_INTR_TRISTATE_BIT)
            Active - drive INTn high, Inactive - tristate INTn
*/
#define MYD_INTR_TRISTATE_BIT       (1<<1)  /* Active - drive INTn high, Inactive
                                              - drive tristate INTn (first port only) */
#define MYD_INTR_POLARITY_BIT       (1<<0)  /* Active - drive INTn high, Inactive
                                              - drive INTn low (first port only)  */

/*******************************************************************************
MYD_STATUS mydSetGlobalInterruptCntl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 interruptPinControl,
    IN MYD_BOOL forceInterrupt
);


 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    interruptPinControl - on first port this controls the INTn pin.
        Pass the bitwise logical OR of the following: MYD_INTR_TRISTATE_BIT
                                                      MYD_INTR_POLARITY_BIT
        On other ports this parameter is ignored. Pass anything is fine.

    forceInterrupt - MYD_TRUE will force the interrupt on this port active, MYD_FALSE
        will set the interrupt back to normal mode (depends on the interrupt inputs).

 Outputs:
    None

 Returns:
    MYD_OK   if there were no errors
    MYD_FAIL if there were errors

 Description:
    This function sets the global interrupt control bits. On the first port of a multi-port
    PHY it controls the PIN polarity and what happens when the interrupt is inactive
    (driven versus tristate). On any port, set forceInterrupt to MYD_TRUE to force the
    port interrupt asserted, and MYD_FALSE to have it back in the default mode where
    it depends on the interrupts whether it is asserted or not.

 Side effects:
    None.

 Notes/Warnings:
    On the X7120, if INTn Pin mode is MYD_PIN_MODE_RCLK, the interrupt signal and
    Recovered Clock will interfere with each other if forceInterrupt is enabled.

*******************************************************************************/
MYD_STATUS mydSetGlobalInterruptCntl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 interruptPinControl, /* used only on first port of device, otherwise ignored */
    IN MYD_BOOL forceInterrupt
);

/*******************************************************************************
MYD_STATUS mydGetGlobalInterruptCntl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 interruptPinControl,
    IN MYD_BOOL forceInterrupt
);


 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31.

 Outputs:
    interruptPinControl - read the controls settings for the port. Only the settings of
        the first port should be read. See mydSetGlobalInterruptCntl() for details.

    forceInterrupt - MYD_TRUE indicates the interrupt is forced to be active on this port,
                     MYD_FALSE indicates the port interrupt depends on the interrupt inputs
                     from each unit.

 Returns:
    MYD_OK   if there were no errors
    MYD_FAIL if there were errors

 Description:
    This function reads the global interrupt control bits. On the first port of a multi-port
    PHY it controls the pin polarity and what happens when the interrupt is inactive
    (driven versus tristate). On any port, forceInterrupt indicates if the interrupt is
    forced on this port or it depends on the interrupts inputs from each units.

 Side effects:
    None.

 Notes/Warnings:
    None.

*******************************************************************************/
MYD_STATUS mydGetGlobalInterruptCntl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    OUT MYD_U16 *interruptPinControl,
    OUT MYD_BOOL *forceInterrupt
);

/*****************************************************************************
Checking Per Port Global Interrupts Status Bit Definitions
    0 = No Interrupt
    1 = Active Interrupt
*****************************************************************************/
#define MYD_DAISY_CHAIN_INTR_BIT              (1<<15) /* Other Port Interrupt Chaining Status */
#define MYD_GPIO_INTR_BIT                     (1<<10) /* GPIO Interrupt Status */
#define MYD_RM_FIFO_INTR_BIT                  (1<<9)  /* 40G to 25G Rate Matching FIFO Interrupt Status */
#define MYD_ON_CHIP_PROC_INTR_BIT             (1<<8)  /* On-chip Processor Interrupt Status */
#define MYD_HOST_SIDE_INTR_BIT                (1<<4)  /* Host-side Interrupt Status */
#define MYD_LINE_SIDE_INTR_BIT                (1<<0)  /* Line-side Interrupt Status */

/*******************************************************************************
MYD_STATUS mydGetPerPortGlobalIntrStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    OUT MYD_U16 *perPortIntrStatus
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31

 Outputs:
    perPortIntrStatus -  value of reading the per port global interrupt status register
        Bit values are defined above.

 Returns:
    MYD_OK   if there were no errors
    MYD_FAIL if there were errors

 Description:
    This function reads the per port global interrupt status bits. Refer to the above
    Per Port Global Interrupts Status Bits to decode the status.

 Side effects:
    None.

 Notes/Warnings:
    None.

*******************************************************************************/
MYD_STATUS mydGetPerPortGlobalIntrStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    OUT MYD_U16 *perPortIntrStatus
);


/* Level 3 GPIO Interrupt Enable Control */
#define MYD_GPIO_INTR_DISABLE                   0x0
#define MYD_GPIO_INTR_ENABLE                    0x1

/* Level 3 GPIO Interrupt Types */
#define MYD_GPIO_INTR_NONE                      0x0    /* No Interrupt */
#define MYD_GPIO_INTR_LOW_LEVEL                 0x2
#define MYD_GPIO_INTR_HIGH_LEVEL                0x3
#define MYD_GPIO_INTR_FALLING_EDGE              0x4
#define MYD_GPIO_INTR_RISING_EDGE               0x5
#define MYD_GPIO_INTR_BOTH_EDGE                 0x7

/******************************************************************************
MYD_STATUS mydSetGPIOInterruptEnable
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    IN MYD_U16 gpioIntrEnable
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    gpioPinId - The Pin to configure, the Pin MUST be set to MYD_PIN_MODE_GPIO mode
                See the bit definitions and header of mydSetPinMode() for details.
        MYD_PIN_GPIO0              Not available on X7120
        MYD_PIN_GPIO1
        MYD_PIN_GPIO2
        MYD_PIN_GPIO3
        MYD_PIN_GPIO4              Not available on X6141
        MYD_PIN_CLK_OUT_SE1
        MYD_PIN_CLK_OUT_SE2

    gpioIntrEnable - Enable or Disable the Level 3 GPIO Interrupt.
        MYD_GPIO_INTR_DISABLE
        MYD_GPIO_INTR_ENABLE

 Outputs:
    None.

 Returns:
    MYD_OK if configuration was successful, MYD_FAIL if not
    If the Pin has NOT been set to MYD_PIN_MODE_GPIO or its direction has been set
    to MYD_GPIO_OUTPUT_MODE, MYD_FAIL will be returned.

 Description:
    This function enables(unmasked) or disables(masked) the GPIO interrupt on the given GPIO Pin.
    Noticed that the Level 3 GPIO interrupt ONLY works as an input.

    Please refer to "Interrupt Overview" section for MYD interrupt levels.

 Side effects:
    None.

 Notes/Warnings:
    The given Pins MUST be configured to MYD_PIN_MODE_GPIO mode AND its direction MUST be
    set to MYD_GPIO_INPUT_MODE before calling this API.
******************************************************************************/
MYD_STATUS mydSetGPIOInterruptEnable
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    IN MYD_U16 gpioIntrEnable
);

/******************************************************************************
MYD_STATUS mydGetGPIOInterruptEnable
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    OUT MYD_U16 *gpioIntrEnable
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    gpioPinId - The Pin to read, the Pin should be set to MYD_PIN_MODE_GPIO mode
                See the bit definitions and header of mydSetPinMode() for details.
        MYD_PIN_GPIO0              Not available on X7120
        MYD_PIN_GPIO1
        MYD_PIN_GPIO2
        MYD_PIN_GPIO3
        MYD_PIN_GPIO4              Not available on X6141
        MYD_PIN_CLK_OUT_SE1
        MYD_PIN_CLK_OUT_SE2

 Outputs:
    gpioIntrEnable - Read the Level 3 GPIO Interrupt enable setting.
        MYD_GPIO_INTR_DISABLE
        MYD_GPIO_INTR_ENABLE

 Returns:
    MYD_OK if query was successful, MYD_FAIL if not

 Description:
    This function reads back the GPIO interrupt enable(unmasked/masked) setting.
    Noticed that the Level 3 GPIO interrupt only works as an input.

    Please refer to "Interrupt Overview" section for MYD interrupt levels.

 Side effects:
    None.

 Notes/Warnings:
    None.
******************************************************************************/
MYD_STATUS mydGetGPIOInterruptEnable
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    OUT MYD_U16 *gpioIntrEnable
);

/******************************************************************************
MYD_STATUS mydSetGPIOInterruptType
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    IN MYD_U16 gpioIntrType
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    gpioPinId - The Pin to configure, the Pin MUST be set to MYD_PIN_MODE_GPIO mode
                See the bit definitions and header of mydSetPinMode() for details.
        MYD_PIN_GPIO0              Not available on X7120
        MYD_PIN_GPIO1
        MYD_PIN_GPIO2
        MYD_PIN_GPIO3
        MYD_PIN_GPIO4              Not available on X6141
        MYD_PIN_CLK_OUT_SE1
        MYD_PIN_CLK_OUT_SE2

    gpioIntrType - Select the GPIO interrupt type
        MYD_GPIO_INTR_NONE
        MYD_GPIO_INTR_LOW_LEVEL
        MYD_GPIO_INTR_HIGH_LEVEL
        MYD_GPIO_INTR_FALLING_EDGE
        MYD_GPIO_INTR_RISING_EDGE
        MYD_GPIO_INTR_BOTH_EDGE

 Outputs:
    None.

 Returns:
    MYD_OK if configuration was successful, MYD_FAIL if not
    If the Pin has NOT been set to MYD_PIN_MODE_GPIO or its direction has been set
    to MYD_GPIO_OUTPUT_MODE, MYD_FAIL will be returned.

 Description:
    This function allows users to select GPIO interrupt Pin type. The default value of
    gpioIntrType is MYD_GPIO_INTR_NONE, which means no interrupt will be detected.
    Noticed that the Level 3 GPIO interrupt only works as an input.

    Please refer to "Interrupt Overview" section for MYD interrupt levels.

 Side effects:
    None.

 Notes/Warnings:
    The given Pins MUST be configured to MYD_PIN_MODE_GPIO mode AND its direction MUST be
    set to MYD_GPIO_INPUT_MODE before calling this API.
******************************************************************************/
MYD_STATUS mydSetGPIOInterruptType
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    IN MYD_U16 gpioIntrType
);

/******************************************************************************
MYD_STATUS mydGetGPIOInterruptType
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    OUT MYD_U16 *gpioIntrType
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    gpioPinId - The Pin to read, the Pin should be set to MYD_PIN_MODE_GPIO mode
                See the bit definitions and header of mydSetPinMode() for details.
        MYD_PIN_GPIO0              Not available on X7120
        MYD_PIN_GPIO1
        MYD_PIN_GPIO2
        MYD_PIN_GPIO3
        MYD_PIN_GPIO4              Not available on X6141
        MYD_PIN_CLK_OUT_SE1
        MYD_PIN_CLK_OUT_SE2

 Outputs:
    gpioIntrType - Read the GPIO interrupt type
        MYD_GPIO_INTR_NONE
        MYD_GPIO_INTR_LOW_LEVEL
        MYD_GPIO_INTR_HIGH_LEVEL
        MYD_GPIO_INTR_FALLING_EDGE
        MYD_GPIO_INTR_RISING_EDGE
        MYD_GPIO_INTR_BOTH_EDGE
        Other Reads: Reserved

 Returns:
    MYD_OK if query was successful, MYD_FAIL if not

 Description:
    This function reads back the GPIO interrupt type.
    Noticed that the Level 3 GPIO interrupt only works as an input.

    Please refer to "Interrupt Overview" section for MYD interrupt levels.

 Side effects:
    None.

 Notes/Warnings:
    None.
******************************************************************************/
MYD_STATUS mydGetGPIOInterruptType
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    OUT MYD_U16 *gpioIntrType
);

/******************************************************************************
MYD_STATUS mydGetGPIOInterruptStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    OUT MYD_U16 *gpioIntrLatchedStatus,
    OUT MYD_U16 *gpioIntrCurrentStatus
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    gpioPinId - The Pin to read status, the Pin should be set to MYD_PIN_MODE_GPIO mode
                See the bit definitions and header of mydSetPinMode() for details.
        MYD_PIN_GPIO0              Not available on X7120
        MYD_PIN_GPIO1
        MYD_PIN_GPIO2
        MYD_PIN_GPIO3
        MYD_PIN_GPIO4              Not available on X6141
        MYD_PIN_CLK_OUT_SE1
        MYD_PIN_CLK_OUT_SE2

 Outputs:
    gpioIntrLatchedStatus - value of the first read of the interrupt status register.
    gpioIntrCurrentStatus - value of the second read of the interrupt status register.
        0 - No interrupt has occurred.
        1 - An interrupt has occurred.

    The output readings may be INVALID if the given pin is NOT in the MYD_PIN_MODE_GPIO or
    the GPIO direction of the Pin is NOT set to MYD_GPIO_INPUT_MODE

 Returns:
    MYD_OK if query was successful, MYD_FAIL if not

 Description:
    This function reads back the GPIO interrupt status on given Pin. The status is latched.
    Noticed that the Level 3 GPIO interrupt ONLY works as an input.

    Please refer to "Interrupt Overview" section for MYD interrupt levels.

 Side effects:
    None.

 Notes/Warnings:
    The given Pins should be configured to MYD_PIN_MODE_GPIO mode AND its direction should be
    set to MYD_GPIO_INPUT_MODE before calling this API, otherwise the reading may be INVALID.
******************************************************************************/
MYD_STATUS mydGetGPIOInterruptStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    OUT MYD_U16 *gpioIntrLatchedStatus,
    OUT MYD_U16 *gpioIntrCurrentStatus
);

/*****************************************************************************
Definitions for Enabling, Checking Interrupts and Real-Time Status
*****************************************************************************/

/*****************************************************************************
Enabling and Checking Interrupts 1000BASE-X and 2.5GBASE-R Status Bit Definitions
*****************************************************************************/
/* Bit 15 NOT USED */                        /* Reserved */
#define MYD_1G_SPEED_CHD_BIT         (1<<14) /* Speed Changed Interrupt Enable/Status */
#define MYD_1G_DPX_CHD_BIT           (1<<13) /* Duplex Changed Interrupt Enable/Status */
#define MYD_1G_PAGE_RX_BIT           (1<<12) /* Page Received Interrupt Enable/Status */
#define MYD_1G_ANEG_COMP_BIT         (1<<11) /* Auto-Negotiation Completed Interrupt Enable/Status */
#define MYD_1G_LINK_UP_DN_BIT        (1<<10) /* Link Up to Link Down Interrupt Enable/Status */
#define MYD_1G_LINK_DN_UP_BIT        (1<<9)  /* Link Down to Link Up Interrupt Enable/Status */
#define MYD_1G_SYM_ERR_BIT           (1<<8)  /* Symbol Error Interrupt Enable/Status */
#define MYD_1G_FALSE_CAR_BIT         (1<<7)  /* False Carrier Interrupt Enable/Status */
/* Bit 6:0 NOT USED */                       /* Reserved */

/*****************************************************************************
Real-Time Status 1000BASE-X and 2.5GBASE-R Bit Definitions
*****************************************************************************/
#define MYD_1G_SPEED2_RT_BIT         (1<<15) /* Bits 15-14: 11=Reserved; 10=1000Mbps */
#define MYD_1G_SPEED1_RT_BIT         (1<<14) /* Bits 15-14: 01=100Mbps; 00=10Mbps */
#define MYD_1G_DPX_CHD_RT_BIT        (1<<13) /* Duplex mode (Full-duplex=1; Half-duplex=0) */
#define MYD_1G_PAGE_RX_RT_BIT        (1<<12) /* Page received=1; Page not received=0  */
#define MYD_1G_ANEG_COMP_RT_BIT      (1<<11) /* When ANeg is not enabled this bit is always 1 */
                                             /* Speed and Duplex (Resolved=1; Not Resolved=0) */
#define MYD_1G_RT_LINK_STATUS        (1<<10) /* Realtime Link (Up=1; Down=0) */
/* Bit 9:6 NOT USED */                       /* Reserved */
#define MYD_1G_SYNC_STATUS_BIT       (1<<5)  /* sync status */
#define MYD_1G_ENERGY_DETECT_BIT     (1<<4)  /* Energy Detect Status (0=Energy Detected)*/
/* These two status bit is valid only when Auto-Negotiation is completed or Auto-Negotiation is disabled. */
#define MYD_1G_TX_PAUSE_BIT          (1<<3)  /* Transmit Pause Enabled */
#define MYD_1G_RX_PAUSE_BIT          (1<<2)  /* Receive Pause Enabled */
/* Bit 1:0 NOT USED */                       /* Reserved */

/*****************************************************************************
Enabling and Checking Interrupts 5GBASE-R, 10GBASE-R and 25GBASE-R
Status Bit Definitions
*****************************************************************************/
/* Bit 15:14 NOT USED */                     /* Reserved */
#define MYD_25G_REMOTE_FLT_TX_BIT    (1<<13) /* Remote Fault Transmitted Interrupt Enable/Status */
#define MYD_25G_REMOTE_FLT_RX_BIT    (1<<12) /* Remote Fault Received Interrupt Enable/Status */
#define MYD_25G_LOCAL_FLT_TX_BIT     (1<<11) /* Local Fault Transmitted Interrupt Enable/Status */
#define MYD_25G_LOCAL_FLT_RX_BIT     (1<<10) /* Local Fault Received Interrupt Enable/Status */
/* Bit 9:7 NOT USED */                       /* Reserved */
#define MYD_25G_RX_FIFO_OVER_BIT     (1<<6)  /* Rxfifo Overflow Interrupt Enable/Status */
#define MYD_25G_RX_FIFO_UNDER_BIT    (1<<5)  /* Rxfifo Underflow Interrupt Enable/Status */
/* Bit 4:3 NOT USED */                       /* Reserved */
#define MYD_25G_LINK_CHANGE_BIT      (1<<2)  /* Link status change Interrupt Enable/Status */
#define MYD_25G_HI_BER_BIT           (1<<1)  /* High BER Change Interrupt Enable/Status */
#define MYD_25G_BLK_LOCK_BIT         (1<<0)  /* Block Lock Change Interrupt Enable/Status */

/*****************************************************************************
Real-Time Status 5GBASE-R, 10GBASE-R and 25GBASE-R Bit Definitions
*****************************************************************************/
/* Bit 15:14 NOT USED */                     /* Reserved */
#define MYD_25G_RF_TX_RT_STATUS_BIT  (1<<13) /* Remote Fault Transmitted Interrupt Real-time Status */
#define MYD_25G_RF_RX_RT_STATUS_BIT  (1<<12) /* Remote Fault Received Interrupt Real-time Status */
#define MYD_25G_LF_TX_RT_STATUS_BIT  (1<<11) /* Local Fault Transmitted Real-time Status */
#define MYD_25G_LF_RX_RT_STATUS_BIT  (1<<10) /* Local Fault Received Real-time Status */
/* Bit 9:7 NOT USED */                       /* Reserved */
#define MYD_25G_RX_FIFO_OVER_RT_BIT  (1<<6)  /* Rxfifo Overflow */
#define MYD_25G_RX_FIFO_UNDER_RT_BIT (1<<5)  /* Rxfifo Underflow */
#define MYD_25G_JIT_0_LOCK_BIT       (1<<4)  /* JIT 0 lock achieved if 1 */
#define MYD_25G_JIT_LF_LOCK_BIT      (1<<3)  /* JIT local fault lock achieved */
#define MYD_25G_RT_LINK_STATUS       (1<<2)  /* 5GBASE-R/10GBASE-R/25GBASE-R Real-time Link Status */
#define MYD_25G_HIGH_BER_BIT         (1<<1)  /* High BER Real-time Status */
#define MYD_25G_LN3_BLK_LK_BIT       (1<<0)  /* Lane 3 Block Lock Real-time Status (lock=1) */

/*****************************************************************************
Enabling and Checking Interrupts 40GBASER and 50GBASER Status
Bit Definitions Flags 1
*****************************************************************************/
/* Flag 1 */
#define MYD_40G_LN3_AM_LOCK_BIT      (1<<15) /* Lane 3 AM lock Interrupt Enable/Status */
#define MYD_40G_LN2_AM_LOCK_BIT      (1<<14) /* Lane 2 AM lock Interrupt Enable/Status */
#define MYD_40G_LN1_AM_LOCK_BIT      (1<<13) /* Lane 1 AM lock Interrupt Enable/Status */
#define MYD_40G_LN0_AM_LOCK_BIT      (1<<12) /* Lane 0 AM lock Interrupt Enable/Status */
#define MYD_40G_LOCAL_FLT_TX_BIT     (1<<11) /* Local Fault Transmitted Interrupt Enable/Status */
#define MYD_40G_LOCAL_FLT_RX_BIT     (1<<10) /* Local Fault Received Interrupt Enable/Status */
#define MYD_40G_LN_ALIGN_BIT         (1<<9)  /* Lane alignment interrupt enable/Status */
#define MYD_40G_TX_LN_ERRCNT_BIT     (1<<8)  /* Tx lane count err interrupt enable/Status */
#define MYD_40G_JIT0_LOCK_BIT        (1<<7)  /* JIT 0 Lock Change Interrupt Enable/Status */
#define MYD_40G_JIT_LF_BIT           (1<<6)  /* JIT Local-Fault Lock Change Interrupt Enable/Status */
#define MYD_40G_LINK_CHANGE_BIT      (1<<5)  /* Link Change Interrupt Enable/Status */
#define MYD_40G_HI_BER_BIT           (1<<4)  /* High BER Change Interrupt Enable/Status */
#define MYD_40G_LN3_BLK_LK_BIT       (1<<3)  /* Lane 3 Block Lock Change Interrupt Enable/Status */
#define MYD_40G_LN2_BLK_LK_BIT       (1<<2)  /* Lane 2 Block Lock Change Interrupt Enable/Status */
#define MYD_40G_LN1_BLK_LK_BIT       (1<<1)  /* Lane 1 Block Lock Change Interrupt Enable/Status */
#define MYD_40G_LN0_BLK_LK_BIT       (1<<0)  /* Lane 0 Block Lock Change Interrupt Enable/Status */

/*****************************************************************************
Enabling Interrupts 40GBASER and 50GBASER Bit Definitions Flags 2
*****************************************************************************/
/* Flag 2 */
/* Bit 15:10 NOT USED */                     /* Reserved */
#define MYD_40G_REMOTE_FLT_TX_BIT    (1<<9)  /* Remote Fault Transmitted Interrupt Enable/Status */
#define MYD_40G_REMOTE_FLT_RX_BIT    (1<<8)  /* Remote Fault Received Interrupt Enable/Status */
/* DO NOT modify Bit 7 */                    /* Bits 7 has nothing to do with the interrupt status */
/* Bit 6:0 NOT USED */                       /* Reserved */

/*****************************************************************************
Checking Interrupts 40GBASER and 50GBASER Status Bit Definitions Flags 2
*****************************************************************************/
/* Flag 2 */
/* Bit 15:10 NOT USED */                     /* Reserved */
#define MYD_40G_REMOTE_FLT_TX_STATUS (1<<9)  /* Remote Fault Transmitted Interrupt Enable/Status */
#define MYD_40G_REMOTE_FLT_RX_STATUS (1<<8)  /* Remote Fault Received Interrupt Enable/Status */
/* Bit 7:0 NOT USED */                       /* Reserved */
/* NOTE: Bits 5:0 have nothing to do with the interrupt status */
/* WARNING: The interrupt handler will clear the following LH status bits and/or any main thread */
/*          that reads this register may clear */
/* the interrupt status bits. Suggest not using both features at the same time. */
#define MYD_40G_RXFIFO_OF            (1<<5)  /* RX-FIFO overflow */
#define MYD_40G_RXFIFO_UF            (1<<4)  /* RX-FIFO underflow */
#define MYD_40G_LN3_DESKEW_FIFO_ERR  (1<<3)  /* Lane 3 deskew FIFO pointer error */
#define MYD_40G_LN2_DESKEW_FIFO_ERR  (1<<2)  /* Lane 2 deskew FIFO pointer error */
#define MYD_40G_LN1_DESKEW_FIFO_ERR  (1<<1)  /* Lane 1 deskew FIFO pointer error */
#define MYD_40G_LN0_DESKEW_FIFO_ERR  (1<<0)  /* Lane 0 deskew FIFO pointer error */

/*****************************************************************************
Real-Time Status 40GBASER and 50GBASER Bit Definitions
Definitions Flags 1 and Flags 2
*****************************************************************************/
/* Flag 1 */
/* Bit 15:12 Reserved */                     /* Bits 15:12 are reserved for other purpose */
#define MYD_40G_LF_TX_RT_STATUS_BIT  (1<<11) /* Local Fault Transmitted Interrupt Real-time Status */
#define MYD_40G_LF_RX_RT_STATUS_BIT  (1<<10) /* Local Fault Received Interrupt Real-time Status */
#define MYD_40G_LN_ALIGN_RT_BIT      (1<<9)  /* Lane alignment interrupt Real-time Status */
#define MYD_40G_TX_LN_ERRCNT_RT_BIT  (1<<8)  /* Tx lane count err interrupt Real-time Status */
#define MYD_40G_JIT0_LOCK_RT_BIT     (1<<7)  /* JIT 0 Lock Change Interrupt Real-time Status */
#define MYD_40G_JIT_LF_RT_BIT        (1<<6)  /* JIT Local-Fault Lock Change Interrupt Real-time Status */
#define MYD_40G_RT_LINK_STATUS       (1<<5)  /* Real-time Link Status */
#define MYD_40G_HI_BER_RT_BIT        (1<<4)  /* High BER Change Interrupt Real-time Status */
#define MYD_40G_LN3_BLK_LK_RT_BIT    (1<<3)  /* Lane 3 Block Lock Change Interrupt Real-time Status */
#define MYD_40G_LN2_BLK_LK_RT_BIT    (1<<2)  /* Lane 2 Block Lock Change Interrupt Real-time Status */
#define MYD_40G_LN1_BLK_LK_RT_BIT    (1<<1)  /* Lane 1 Block Lock Change Interrupt Real-time Status */
#define MYD_40G_LN0_BLK_LK_RT_BIT    (1<<0)  /* Lane 0 Block Lock Change Interrupt Real-time Status */

/* Flag 2 */
/* Bit 15:7 NOT USED */                      /* Reserved */
#define MYD_40G_RF_TX_RT_STATUS_BIT  (1<<6)  /* Remote Fault Transmitted Interrupt Real-time Status */
#define MYD_40G_RF_RX_RT_STATUS_BIT  (1<<5)  /* Remote Fault Received Interrupt Real-time Status */
/* Bit 4:0 Reserved */                       /* Bits 15:12 are reserved for other purpose */

/*****************************************************************************
Enabling, Checking Interrupts Status and Real-Time Status 100GBASER Bit
Definitions Flags 1 and Flags 2
*****************************************************************************/
#define MYD_100G_RXIFO_EMPTY_BIT     (1<<15) /* 100G PCS Rx FIFO Empty Interrupt Enable/Status/RT Status */
#define MYD_100G_RXFIFO_FULL_BIT     (1<<14) /* 100G PCS Rx FIFO Full Interrupt Enable/Status/RT Status */
#define MYD_100G_TXFIFO_OF_BIT       (1<<13) /* 100G PCS Tx PPM FIFO Overflow Interrupt Enable/Status/RT Status */
#define MYD_100G_TXFIFO_UF_BIT       (1<<12) /* 100G PCS Tx PPM FIFO Underflow Interrupt Enable/Status/RT Status */
#define MYD_100G_LOCAL_FLT_TX_BIT    (1<<11) /* Rising Edge of the Local Fault Condition on Tx Path Interrupt Enable/Status/RT Status */
#define MYD_100G_LOCAL_FLT_RX_BIT    (1<<10) /* Rising Edge of the Local Fault Condition on Rx Path Interrupt Enable/Status/RT Status */
#define MYD_100G_REMOTE_FLT_TX_BIT   (1<<9)  /* Rising Edge of the Remote Fault Condition on Tx Path Interrupt Enable/Status/RT Status */
#define MYD_100G_REMOTE_FLT_RX_BIT   (1<<8)  /* Rising Edge of the Remote Fault Condition on Rx Path Interrupt Enable/Status/RT Status */
#define MYD_100G_PKTCK_CRCERR_BIT    (1<<7)  /* 100G Packet Check CRC Error interrupt Enable/Status/RT Status */
/* Bit 6 NOT USED */                         /* Reserved */
#define MYD_100G_LINK_BIT            (1<<5)  /* Link Change Interrupt Enable/Status/RT Status */
#define MYD_100G_HI_BER_BIT          (1<<4)  /* High BER Change Interrupt Enable/Status/RT Status */
#define MYD_100G_LN3_BLK_LK_BIT      (1<<3)  /* Lane 3 Block Lock Change Interrupt Enable/Status/RT Status */
#define MYD_100G_LN2_BLK_LK_BIT      (1<<2)  /* Lane 2 Block Lock Change Interrupt Enable/Status/RT Status */
#define MYD_100G_LN1_BLK_LK_BIT      (1<<1)  /* Lane 1 Block Lock Change Interrupt Enable/Status/RT Status */
#define MYD_100G_LN0_BLK_LK_BIT      (1<<0)  /* Lane 0 Block Lock Change Interrupt Enable/Status/RT Status */

/* Flags 2 */
#define MYD_100G_LN19_BLK_LK_BIT     (1<<15) /* Lane 19 Block Lock Change Interrupt Enable/Status/RT Status */
#define MYD_100G_LN18_BLK_LK_BIT     (1<<14) /* Lane 18 Block Lock Change Interrupt Enable/Status/RT Status */
#define MYD_100G_LN17_BLK_LK_BIT     (1<<13) /* Lane 17 Block Lock Change Interrupt Enable/Status/RT Status */
#define MYD_100G_LN16_BLK_LK_BIT     (1<<12) /* Lane 16 Block Lock Change Interrupt Enable/Status/RT Status */
#define MYD_100G_LN15_BLK_LK_BIT     (1<<11) /* Lane 15 Block Lock Change Interrupt Enable/Status/RT Status */
#define MYD_100G_LN14_BLK_LK_BIT     (1<<10) /* Lane 14 Block Lock Change Interrupt Enable/Status/RT Status */
#define MYD_100G_LN13_BLK_LK_BIT     (1<<9)  /* Lane 13 Block Lock Change Interrupt Enable/Status/RT Status */
#define MYD_100G_LN12_BLK_LK_BIT     (1<<8)  /* Lane 12 Block Lock Change Interrupt Enable/Status/RT Status */
#define MYD_100G_LN11_BLK_LK_BIT     (1<<7)  /* Lane 11 Block Lock Change Interrupt Enable/Status/RT Status */
#define MYD_100G_LN10_BLK_LK_BIT     (1<<6)  /* Lane 10 Block Lock Change Interrupt Enable/Status/RT Status */
#define MYD_100G_LN9_BLK_LK_BIT      (1<<5)  /* Lane 9 Block Lock Change Interrupt Enable/Status/RT Status */
#define MYD_100G_LN8_BLK_LK_BIT      (1<<4)  /* Lane 8 Block Lock Change Interrupt Enable/Status/RT Status */
#define MYD_100G_LN7_BLK_LK_BIT      (1<<3)  /* Lane 7 Block Lock Change Interrupt Enable/Status/RT Status */
#define MYD_100G_LN6_BLK_LK_BIT      (1<<2)  /* Lane 6 Block Lock Change Interrupt Enable/Status/RT Status */
#define MYD_100G_LN5_BLK_LK_BIT      (1<<1)  /* Lane 5 Block Lock Change Interrupt Enable/Status/RT Status */
#define MYD_100G_LN4_BLK_LK_BIT      (1<<0)  /* Lane 4 Block Lock Change Interrupt Enable/Status/RT Status */

/*****************************************************************************
Enabling and Checking Interrupts 200GBASE-R4 Status Bit
*****************************************************************************/
#define MYD_200G_RXIFO_EMPTY_BIT     (1<<15) /* 200G PCS Rx FIFO Empty Interrupt Enable/Status */
#define MYD_200G_RXFIFO_FULL_BIT     (1<<14) /* 200G PCS Rx FIFO Full Interrupt Enable/Status */
#define MYD_200G_TXFIFO_OF_BIT       (1<<13) /* 200G PCS Tx PPM FIFO Overflow Interrupt Enable/Status */
#define MYD_200G_TXFIFO_UF_BIT       (1<<12) /* 200G PCS Tx PPM FIFO Underflow Interrupt Enable/Status */
#define MYD_200G_LOCAL_FLT_TX_BIT    (1<<11) /* Rising Edge of the Local Fault Condition on Tx Path Interrupt Enable/Status */
#define MYD_200G_LOCAL_FLT_RX_BIT    (1<<10) /* Rising Edge of the Local Fault Condition on Rx Path Interrupt Enable/Status */
#define MYD_200G_LPI_TX_BIT          (1<<9)  /* 200G PCS Tx LPI Received Interrupt Enable/Status */
#define MYD_200G_LPI_RX_BIT          (1<<8)  /* 200G PCS Rx LPI Received Interrupt Enable/Status */
#define MYD_200G_PKTCK_CRCERR_BIT    (1<<7)  /* 200G Packet Check CRC Error interrupt Enable/Status */
#define MYD_200G_VERY_HIGH_BIT       (1<<6)  /* 200G PCS Tx PPM FIFO Very High Water Interrupt */
#define MYD_200G_LINK_CHANGE_BIT     (1<<5)  /* Link Status Change Interrupt Enable/Status */
#define MYD_200G_REMOTE_FLT_TX_BIT   (1<<4)  /* Rising Edge of the Remote Fault Condition on Tx Path Interrupt Enable/Status */
#define MYD_200G_REMOTE_FLT_RX_BIT   (1<<3)  /* Rising Edge of the Remote Fault Condition on Rx Path Interrupt Enable/Status */
#define MYD_200G_4LOCAL_FLT_TX_BIT   (1<<2)  /* Rising Edge of 4 Local Fault Condition on Tx Path Interrupt Enable/Status */
#define MYD_200G_4REMOTE_FLT_TX_BIT  (1<<1)  /* Rising Edge of 4 Remote Fault Condition on Tx Path Interrupt Enable/Status */
#define MYD_200G_TXFIFO_OR_BIT       (1<<0)  /* Rising edge of 200G PCS Tx PPM FIFO Overrun Interrupt Enable/Status */

/*****************************************************************************
Real-Time Status 200GBASE-R4 Bit Definitions
*****************************************************************************/
#define MYD_200G_RXIFO_EMPTY_RT_BIT  (1<<15) /* 200G PCS Rx FIFO Empty Flag */
#define MYD_200G_RXFIFO_FULL_RT_BIT  (1<<14) /* 200G PCS Rx FIFO Full Flag */
#define MYD_200G_TXFIFO_OF_RT_BIT    (1<<13) /* 200G PCS Tx PPM FIFO Overflow Flag */
#define MYD_200G_TXFIFO_UF_RT_BIT    (1<<12) /* 200G PCS Tx PPM FIFO Underflow Flag */
#define MYD_200G_LF_TX_RT_STATUS_BIT (1<<11) /* Real-Time Status for Local Fault Condition on 200G PCS Tx Path */
#define MYD_200G_LF_RX_RT_STATUS_BIT (1<<10) /* Real-Time Status for Local Fault Condition on 200G PCS Rx Path */
#define MYD_200G_LPI_TX_RT_BIT       (1<<9)  /* 200G PCS Tx Receiving LPI Words */
#define MYD_200G_LPI_RX_RT_BIT       (1<<8)  /* 200G PCS Rx Receiving LPI Words */
#define MYD_200G_PKTCK_CRCERR_RT_BIT (1<<7)  /* 200G PCS Packet Check Detected CRC Error */
#define MYD_200G_VERY_HIGH_FLAG_BIT  (1<<6)  /* 200G PCS Tx PPM FIFO Very High Water Flag */
#define MYD_200G_RT_LINK_STATUS      (1<<5)  /* Real-Time Link Status */
#define MYD_200G_RF_TX_RT_STATUS_BIT (1<<4)  /* Real-Time Status for Remote Fault Condition on 200G PCS Tx Path */
#define MYD_200G_RF_RX_RT_STATUS_BIT (1<<3)  /* Real-Time Status for Remote Fault Condition on 200G PCS Rx Path */
#define MYD_200G_4LF_TX_RT_STATUS    (1<<2)  /* Real-Time Status for 4 Local Fault Condition on 200G PCS Tx Path */
#define MYD_200G_4RF_TX_RT_STATUS    (1<<1)  /* Real-Time Status for 4 Remote Fault Condition on 200G PCS Tx Path */
#define MYD_200G_TXFIFO_OR_RT_STATUS (1<<0)  /* 200G PCS Tx PPM FIFO Overrun */

/*****************************************************************************
Enabling and Checking Interrupts and Real-Time Status Combined Functions for
various speeds
*****************************************************************************/

/******************************************************************************
MYD_STATUS mydSetPCSInterruptEnable
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 intrEnableFlags1,
    IN MYD_U16 intrEnableFlags2
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
       MYD_HOST_SIDE
       MYD_LINE_SIDE
    laneOffset - 0-3; lane offset to be checked for link status;
                 For PCS mode that uses multiple lanes, i.e. R2 and R4, the
                 first lane offset should be provided.
    intrEnableFlags1 - For each flag a 1 enables the interrupt and a
        0 disables the interrupt. Flags are defined above.
        Flag values depend on operating mode
    intrEnableFlags2 - For each flag a 1 enables the interrupt and a
        0 disables the interrupt. Flags are defined above.
        Flag values depend on operating mode
        This flag is only for 40GBR/50GBR and 100GBR mode, ignored for other modes.

 Outputs:
    None

 Returns:
    MYD_OK if change was successful, MYD_FAIL if not.
    MYD_FAIL if the operating mode is not set properly or
    the device is not initialized.

 Description:
    This function can be called after the port has been initialized for
    any of the 1000BASE-X to 200GBR modes of operation to enable interrupts.
    To enable certain interrupts, please read the interrupt enable setting back
    first by mydGetPCSInterruptEnable(), then set corresponding bits and call
    this API to enable interrupts.

 Side effects:
    If INTn Pin mode is MYD_PIN_MODE_RCLK, the interrupt signal and Recovered Clock will
    interfere with each other if any of the interrupt is enabled, including interrupts
    that are not configured in this API.

 Notes/Warnings:
    Please set the INTn Pin to MYD_PIN_MODE_INTR before calling this function.
    The bit flags can be OR together to enable multiple interrupts.
    For example:
        (MYD_100G_RXIFO_FULL_BIT | MYD_100G_RXFIFO_EMPTY_BIT) for
    intrEnableFlags1 to enable these two interrupts on 100GR mode.

******************************************************************************/
MYD_STATUS mydSetPCSInterruptEnable
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 intrEnableFlags1,
    IN MYD_U16 intrEnableFlags2 /* only valid for 40GBR/50GBR and 100GBR */
);

/******************************************************************************
MYD_STATUS mydGetPCSInterruptEnable
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *intrEnableFlags1,
    OUT MYD_U16 *intrEnableFlags2
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being read:
       MYD_HOST_SIDE
       MYD_LINE_SIDE
    laneOffset - 0-3; lane offset to be checked for link status;
                 For PCS mode that uses multiple lanes, i.e. R2 and R4, the
                 first lane offset should be provided.

 Outputs:
    intrEnableFlags1 - For each flag a 1 indicates the interrupt is
        enabled and a 0 indicates the interrupt is disabled.
        Flags are defined above.
        Flag values depend on operating mode
    intrEnableFlags2 - For each flag a 1 indicates the interrupt is
        enabled and a 0 indicates the interrupt is disabled.
        Flags are defined above.
        Flag values depend on current operating mode.
        This flag is only for 40GBR/50GBR, 100G mode, for other modes will
        return 0 (ignore this flag for other modes).

 Returns:
    MYD_OK if query was successful, MYD_FAIL if not.

 Description:
    This function can be called after the port has been initialized for
    any of the 1000BASE-X to 200GBR modes of operation to read what
    interrupts are enabled.

 Side effects:
    None.

 Notes/Warnings:
    None.

******************************************************************************/
MYD_STATUS mydGetPCSInterruptEnable
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *intrEnableFlags1,
    OUT MYD_U16 *intrEnableFlags2 /* only valid for 40GBR/50GBR and 100GBR */
);

/******************************************************************************
MYD_STATUS mydGetPCSInterruptStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *latchedStatusFlags1,
    OUT MYD_U16 *currentStatusFlags1,
    OUT MYD_U16 *latchedStatusFlags2,
    OUT MYD_U16 *currentStatusFlags2,
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being read:
       MYD_HOST_SIDE
       MYD_LINE_SIDE
    laneOffset - 0-3; lane offset to be checked for link status;
                 For PCS mode that uses multiple lanes, i.e. R2 and R4, the
                 first lane offset should be provided.

 Outputs:
    latchedStatusFlags1 - value of the first read of the
        interrupt status register. Bit values are defined above.
    currentStatusFlags1 - value of the second read of the
        interrupt status register. Bit values are defined above.
    latchedStatusFlags2 - value of the first read of the
        interrupt status register 2.
        Bit values are defined above. Only valid in 40GBR/50GBR and 100GR mode.
        Other modes will return 0 (to be ignored by caller).
    currentStatusFlags2 - value of the second read of the
        interrupt status register 2.
        Bit values are defined above. Only valid in 40GBR/50GBR and 100GR mode.
        Other modes will return 0 (to be ignored by caller).

 Returns:
    MYD_OK if query was successful, MYD_FAIL if not.

 Description:
    This function can be called after the port has been initialized for
    any of the 1000BASE-X to 200GBR modes of operation to read what
    interrupts are asserted (being requested). The first read value is passed in the
    latched parameter, while the second read value is passed in the
    current read parameter.

    To determine what interrupt actually occurred at INTn, the latched value must
    be AND with the interrupt enable flag from the function
    mydGetPCSInterruptEnable().

    To determine if the interrupt is still asserted at the INTn pin, the
    current value can be AND with the interrupt enable flag from the function
    mydGetPCSInterruptEnable().

 Side effects:
    None.

 Notes/Warnings:
    If the interrupt has gone away, calling this function will clear the
    latched bit.

******************************************************************************/
MYD_STATUS mydGetPCSInterruptStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *latchedStatusFlags1,
    OUT MYD_U16 *currentStatusFlags1,
    OUT MYD_U16 *latchedStatusFlags2, /* only valid for 40GBR/50GBR and 100GBR */
    OUT MYD_U16 *currentStatusFlags2  /* only valid for 40GBR/50GBR and 100GBR */
);

/******************************************************************************
MYD_STATUS mydGetPCSRealtimeStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *rtStatusFlags1,
    OUT MYD_U16 *rtStatusFlags2
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being read:
       MYD_HOST_SIDE
       MYD_LINE_SIDE
    laneOffset - 0-3; lane offset to be checked for link status;
                 For PCS mode that uses multiple lanes, i.e. R2 and R4, the
                 first lane offset should be provided.

 Outputs:
    rtStatusFlags1 - value of reading the real-time status register
        Bit values are defined above.
    rtStatusFlags2 - value of reading the real-time status register #2.
        Bit values are defined above.
        Only valid for 40/50GBR and 100GBR.
        Returns 0 for other modes (to be ignored by caller).

 Returns:
    MYD_OK if query was successful, MYD_FAIL if not.

 Description:
    This function can be called after the port has been initialized for
    any of the 1000BASE-X to 200GBR modes of operation to read what the
    current status is.

 Side effects:
    None.

 Notes/Warnings:
    None.
******************************************************************************/
MYD_STATUS mydGetPCSRealtimeStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *rtStatusFlags1,
    OUT MYD_U16 *rtStatusFlags2 /* only valid for 40/50GBR and 100GBR */
);

/******************************************************************************
MYD_STATUS mydSetPinMode
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID pinId,
    IN MYD_PIN_MODE pinMode
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    pinId - the Pin to configure
             MYD_PIN_GPIO0              Not available on X7120
             MYD_PIN_GPIO1
             MYD_PIN_GPIO2
             MYD_PIN_GPIO3
             MYD_PIN_GPIO4
             MYD_PIN_INTn
             MYD_PIN_CLK_OUT_SE1
             MYD_PIN_CLK_OUT_SE2
             MYD_PIN_CLK_OUT_DIFF_N     Not available on X6141
             MYD_PIN_CLK_OUT_DIFF_P     Not available on X6141

    pinMode - Set the pin to given mode, please see this API description for
              all available modes.
        MYD_PIN_MODE_BACKPRESSURE
        MYD_PIN_MODE_GPIO
        MYD_PIN_MODE_LED
        MYD_PIN_MODE_INTR
        MYD_PIN_MODE_RCLK

 Outputs:
    None

 Returns:
    MYD_OK if configuration was successful, MYD_FAIL if not

 Description:
    This function configures the mode of the given multi-purpose pins. Here the Pins
    only refers to the one defined in the _MYD_PIN_ID struct

    - Modes Available on X7120 -
    MYD_PIN_MODE_BACKPRESSURE: 40G-25G Gearbox Back pressure Signaling Mode:
    GPIO1, GPIO2, GPIO3, GPIO4,
    CLK_OUT_SE1, CLK_OUT_SE2

    MYD_PIN_MODE_GPIO: GPIO Mode (GPIO In/Out or Interrupt)
    GPIO1, GPIO2, GPIO3, GPIO4,
    CLK_OUT_SE1, CLK_OUT_SE2

    MYD_PIN_MODE_LED: LED Mode. See mydConfigLEDPin() for detailed configurations.
    GPIO1, GPIO2, GPIO3, GPIO4,
    CLK_OUT_SE1, CLK_OUT_SE2

    MYD_PIN_MODE_INTR: Device Interrupt Pin INTn 
    INTn

    MYD_PIN_MODE_RCLK: Recovered clock signal from selected Port, interface and lane
    INTn, GPIO2(Port0, Port1), CLK_OUT_SE1(Port2, Port3), CLK_OUT_SE2,
    CLK_OUT_DIFF_N(Port3), CLK_OUT_DIFF_P(Port3)


    - Modes Available on X6141 -
    MYD_PIN_MODE_BACKPRESSURE: 40G-25G Gearbox Back pressure Signaling Mode:
    GPIO0, GPIO2, CLK_OUT_SE1, CLK_OUT_SE2

    MYD_PIN_MODE_GPIO: GPIO Mode (GPIO In/Out or Interrupt)
    GPIO0, GPIO1, GPIO2, GPIO3,
    CLK_OUT_SE1, CLK_OUT_SE2

    MYD_PIN_MODE_LED: LED Mode. See mydConfigLEDPin() for detailed configurations.
    GPIO0, GPIO1, GPIO2, GPIO3,
    CLK_OUT_SE1, CLK_OUT_SE2

    MYD_PIN_MODE_INTR: Device Interrupt Pin INTn 
    INTn

    MYD_PIN_MODE_RCLK: Recovered clock signal from selected Port, interface and lane
    INTn, CLK_OUT_SE1, CLK_OUT_SE2

 Side effects:
    None.

 Notes/Warnings:
    User should not change the Pin Mode once it is configured, since each mode of
    the Pin MUST match the board schematic.

    DO NOT unmask/enable any interrupt if INTn pin is set to MYD_PIN_MODE_RCLK mode,
    otherwise the recovered clock will be interfered with. DO NOT configure INTn to RCLK mode
    if you are not sure whether there is any interrupt enabled or not.

    Recovered Clock Limitations:
    On the X7120, GPIO2 can output the Recovered Clock only from Ports 0 and 1.
    CLK_OUT_SE1 can output the Recovered Clock only from Ports 2 and 3.
    CLK_OUT_DIFF_N and CLK_OUT_DIFF_P can output the Recovered Clock
    from Port 3 only.

    Default Clock Source Port(X7120):
    PINid                     Default Clock Source Port
    MYD_PIN_INTn                    Port0
    MYD_PIN_GPIO2                   Port1
    MYD_PIN_CLK_OUT_SE1             Port3
    MYD_PIN_CLK_OUT_SE2             Port3
    MYD_PIN_CLK_OUT_DIFF_N          Port3
    MYD_PIN_CLK_OUT_DIFF_P          Port3
    Please call mydConfigRClkPin() to configure clock source.

    By default, the INTn pin is in the MYD_PIN_MODE_INTR mode.
******************************************************************************/
MYD_STATUS mydSetPinMode
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID pinId,
    IN MYD_PIN_MODE pinMode
);

/******************************************************************************
MYD_STATUS mydGetPinMode
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID pinId,
    OUT MYD_PIN_MODE *pinMode
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    pinId - the Pin to read
            MYD_PIN_GPIO0              Not available on X7120
            MYD_PIN_GPIO1
            MYD_PIN_GPIO2
            MYD_PIN_GPIO3
            MYD_PIN_GPIO4
            MYD_PIN_INTn
            MYD_PIN_CLK_OUT_SE1
            MYD_PIN_CLK_OUT_SE2
            MYD_PIN_CLK_OUT_DIFF_N     Not available on X6141
            MYD_PIN_CLK_OUT_DIFF_P     Not available on X6141


 Outputs:
    pinMode - Read the mode of given pin.
              See mydSetPinMode() description for details.
        MYD_PIN_MODE_BACKPRESSURE
        MYD_PIN_MODE_GPIO
        MYD_PIN_MODE_LED
        MYD_PIN_MODE_INTR
        MYD_PIN_MODE_RCLK

 Returns:
    MYD_OK if read was successful, MYD_FAIL if not

 Description:
    This function read the mode of given multi-purpose pins. Here the Pins
    only refers to the one defined in the _MYD_PIN_ID struct. See mydSetPinMode()
    for available mode details.

 Side effects:
    None.

 Notes/Warnings:
    None.
******************************************************************************/
MYD_STATUS mydGetPinMode
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID pinId,
    OUT MYD_PIN_MODE *pinMode
);

/* GPIO Pin Directions */
#define MYD_GPIO_INPUT_MODE                     0x0
#define MYD_GPIO_OUTPUT_MODE                    0x1

/******************************************************************************
MYD_STATUS mydSetGPIOPinDirection
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    IN MYD_U16 gpioPinDirection
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    gpioPinId - The Pin to configure, the Pin MUST be set to MYD_PIN_MODE_GPIO mode
                See the bit definitions and header of mydSetPinMode() for details.
        MYD_PIN_GPIO0              Not available on X7120
        MYD_PIN_GPIO1
        MYD_PIN_GPIO2
        MYD_PIN_GPIO3
        MYD_PIN_GPIO4              Not available on X6141
        MYD_PIN_CLK_OUT_SE1
        MYD_PIN_CLK_OUT_SE2
    gpioPinDirection - Configure the GPIO Pin to output or input mode
        MYD_GPIO_INPUT_MODE
        MYD_GPIO_OUTPUT_MODE

 Outputs:
    None.

 Returns:
    MYD_OK if configuration was successful, MYD_FAIL if not

 Description:
    This function configures the direction of the given GPIO Pin. The given Pin MUST
    be set to MYD_PIN_MODE_GPIO mode before calling this function to make changes
    take effect.

 Side effects:
    None.

 Notes/Warnings:
    gpioPinDirection settings are INVALID if the given Pin is NOT in
    MYD_PIN_MODE_GPIO mode.

    BE CAREFUL WHEN CALLING mydSetGPIOPinDirection() TO SET THE DIRECTION
    OF THE PIN. IT MUST MATCH THE WIRING ON THE BOARD OTHERWISE YOU MAY DAMAGE
    A PIN BY OVERDRIVING IT.
******************************************************************************/
MYD_STATUS mydSetGPIOPinDirection
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    IN MYD_U16 gpioPinDirection
);

/******************************************************************************
MYD_STATUS mydGetGPIOPinDirection
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    OUT MYD_U16 *gpioPinDirection
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    gpioPinId - The Pin to read, the Pin should be set to MYD_PIN_MODE_GPIO mode
                See the bit definitions and header of mydSetPinMode() for details.
        MYD_PIN_GPIO0              Not available on X7120
        MYD_PIN_GPIO1
        MYD_PIN_GPIO2
        MYD_PIN_GPIO3
        MYD_PIN_GPIO4              Not available on X6141
        MYD_PIN_CLK_OUT_SE1
        MYD_PIN_CLK_OUT_SE2

 Outputs:
    gpioPinDirection - returns the GPIO Pin direction
        MYD_GPIO_INPUT_MODE
        MYD_GPIO_OUTPUT_MODE

 Returns:
    MYD_OK if configuration was successful, MYD_FAIL if not

 Description:
    This function queries the data direction of the given GPIO Pin.

 Side effects:
    None.

 Notes/Warnings:
    gpioPinDirection reading is INVALID if the given Pin is NOT in MYD_PIN_MODE_GPIO.
******************************************************************************/
MYD_STATUS mydGetGPIOPinDirection
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    OUT MYD_U16 *gpioPinDirection
);

/******************************************************************************
MYD_STATUS mydSetGPIOPinData
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    IN MYD_U16 gpioData
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    gpioPinId - The Pin to write data, the Pin MUST be set to MYD_PIN_MODE_GPIO mode
                See the bit definitions and header of mydSetPinMode() for details.
        MYD_PIN_GPIO0              Not available on X7120
        MYD_PIN_GPIO1
        MYD_PIN_GPIO2
        MYD_PIN_GPIO3
        MYD_PIN_GPIO4              Not available on X6141
        MYD_PIN_CLK_OUT_SE1
        MYD_PIN_CLK_OUT_SE2

    gpioData - Data written to the output register, 0 or 1.
               If the GPIO Pin is in MYD_GPIO_OUTPUT_MODE, the GPIO Pin will also be
               driven by this value.

 Outputs:
    None.

 Returns:
    MYD_OK if write was successful, MYD_FAIL if not
    If the Pin has NOT been set to MYD_PIN_MODE_GPIO, MYD_FAIL will be returned.

 Description:
    This function writes data to the GPIO interrupt on the given GPIO Pin.
    When the GPIO Pin is in MYD_GPIO_INPUT_MODE, this function will write the data to
    the output register, but will have no effect on given GPIO Pin.

    When the GPIO Pin is in MYD_GPIO_OUTPUT_MODE, this function will write the data to
    the output register and drive the state of given GPIO Pin.

 Side effects:
    None.

 Notes/Warnings:
    The given Pins MUST be configured to MYD_PIN_MODE_GPIO mode before calling this API.
******************************************************************************/
MYD_STATUS mydSetGPIOPinData
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    IN MYD_U16 gpioData         /* 0 or 1 */
);

/******************************************************************************
MYD_STATUS mydGetGPIOPinData
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    OUT MYD_U16 *gpioData
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    gpioPinId - The Pin to read data, the Pin MUST be set to MYD_PIN_MODE_GPIO mode
                See the bit definitions and header of mydSetPinMode() for details.
        MYD_PIN_GPIO0              Not available on X7120
        MYD_PIN_GPIO1
        MYD_PIN_GPIO2
        MYD_PIN_GPIO3
        MYD_PIN_GPIO4              Not available on X6141
        MYD_PIN_CLK_OUT_SE1
        MYD_PIN_CLK_OUT_SE2

 Output:
    gpioData - If the GPIO Pin is in MYD_GPIO_INPUT_MODE, this it the state of the GPIO Pin.
               If the GPIO Pin is in MYD_GPIO_OUTPUT_MODE, this it the state of the output
               register.

 Returns:
    MYD_OK if read was successful, MYD_FAIL if not
    If the Pin has NOT been set to MYD_PIN_MODE_GPIO, MYD_FAIL will be returned.

 Description:
    This function reads data from the given GPIO Pin or its output register.
    When the GPIO Pin is in MYD_GPIO_INPUT_MODE, this function reads the data from the GPIO Pin.
    When the GPIO Pin is in MYD_GPIO_OUTPUT_MODE, this function reads the data from the
    the output register.

 Side effects:
    None.

 Notes/Warnings:
    The given Pins MUST be configured to MYD_PIN_MODE_GPIO mode before calling this API.
******************************************************************************/
MYD_STATUS mydGetGPIOPinData
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    OUT MYD_U16 *gpioData
);

/******************************************************************************
 Definitions for LED Configurations
******************************************************************************/
#define MYD_LED_CONFIG_UNCHANGED                0xFF     /* Keep the settings unchanged */

/* LED Activities Definitions */
#define MYD_LED_ACT_SOLID_OFF                   0x0     /* Solid OFF */
#define MYD_LED_ACT_LANE_TX_RX                  0x1     /* Lane transmit or receive activity */
#define MYD_LED_ACT_LANE_TX                     0x2     /* Lane transmit activity */
#define MYD_LED_ACT_LANE_RX                     0x3     /* Lane receive activity */
#define MYD_LED_ACT_LANE_LINK_UP                0x6     /* Lane receiver link up */
#define MYD_LED_ACT_SOLID_ON                    0x7     /* Solid ON */
#define MYD_LED_ACT_BLINK_MIX                   0xA     /* Blink Mix */
#define MYD_LED_ACT_SOLID_MIX                   0xB     /* Solid Mix */

/* LED Polarity Definitions */
#define MYD_LED_ACTIVE_LOW                      0x0     /* ON: drive LED Pin low, OFF: drive LED Pin high */
#define MYD_LED_ACTIVE_HIGH                     0x1     /* ON: drive LED Pin high, OFF: drive LED Pin low */
#define MYD_LED_ACTIVE_LOW_TRISTATE             0x2     /* ON: drive LED Pin low, OFF: tri-state */
#define MYD_LED_ACTIVE_HIGH_TRISTATE            0x3     /* ON: drive LED Pin high, OFF: tri-state */

/******************************************************************************
typedef struct _MYD_LED_CTRL MYD_LED_CTRL;
    laneSelect - select which lane's activity will be shown on the LED
        see the mydConfigLEDPin() for pin mapping.
        lane number 0-3 or MYD_LED_CONFIG_UNCHANGED
    interfaceSelect - select which interface's activity will be shown on the LED
        see the mydConfigLEDPin() for pin mapping.
        MYD_LINE_SIDE = PHY side (Line side)
        MYD_HOST_SIDE = System side (Host side)
        MYD_LED_CONFIG_UNCHANGED
    blinkActivity - The activity has higher priority than the solid activity
        MYD_LED_ACT_SOLID_OFF
        MYD_LED_ACT_LANE_TX_RX
        MYD_LED_ACT_LANE_TX
        MYD_LED_ACT_LANE_RX
        MYD_LED_ACT_LANE_LINK_UP
        MYD_LED_ACT_SOLID_ON
        MYD_LED_ACT_BLINK_MIX
        MYD_LED_ACT_SOLID_MIX
        MYD_LED_CONFIG_UNCHANGED
    solidActivity - Solid activity has lower priority than the blink activity
        e.g. If blinkActivity = MYD_LED_ACT_LANE_TX, solidActivity = MYD_LED_ACT_LANE_LINK_UP,
             LED will be solid on when the link is up and start blinking when a receive activity
             presents. If blinkActivity = solidActivity = MYD_LED_ACT_LANE_LINK_UP,
             LED will blink when link up.
        MYD_LED_ACT_SOLID_OFF
        MYD_LED_ACT_LANE_TX_RX
        MYD_LED_ACT_LANE_TX
        MYD_LED_ACT_LANE_RX
        MYD_LED_ACT_LANE_LINK_UP
        MYD_LED_ACT_SOLID_ON
        MYD_LED_CONFIG_UNCHANGED
    polarity - Decide if LED pin will be driven high/low or in tri-state
        MYD_LED_ACTIVE_LOW
        MYD_LED_ACTIVE_HIGH
        MYD_LED_ACTIVE_LOW_TRISTATE
        MYD_LED_ACTIVE_HIGH_TRISTATE
        MYD_LED_CONFIG_UNCHANGED
    mixRateLevel - LED mix percentage Level. Level0 to Level8 with a 12.5% step.
              When using two terminal bi-color LEDs, the mixing percentage
              should not be set to greater than Level4.
        0 = Level 0, 0%
        1 = Level 1, 12.5%
        2 = Level 2, 25%
        3 = Level 3, 37.5%
        4 = Level 4, 50%
        5 = Level 5, 62.5%
        6 = Level 6, 75%
        7 = Level 7, 87.5%
        8 = Level 8, 100%
        MYD_LED_CONFIG_UNCHANGED
    blinkRateSelect - MUST be 1, 2 or MYD_LED_CONFIG_UNCHANGED.
                      Select the blink rate options for the LED.
                      The options must be provided to the mydConfigLEDPin() API
                      in MYD_LED_TIMER_CONFIG structure.
******************************************************************************/
typedef struct _MYD_LED_CTRL
{
    MYD_U16 laneSelect;
    MYD_U16 interfaceSelect;
    MYD_U16 blinkActivity;
    MYD_U16 solidActivity;
    MYD_U16 polarity;
    MYD_U16 mixRateLevel;
    MYD_U16 blinkRateSelect;    /* MUST be 1, 2 or MYD_LED_CONFIG_UNCHANGED */
} MYD_LED_CTRL;

/******************************************************************************
typedef struct _MYD_LED_TIMER_CONFIG MYD_LED_TIMER_CONFIG;
    Some of the timing may be off from the listed value.
    blinkRate1, blinkRate2 - Blink Rate Option 1 and 2. Also see mydConfigLEDPin().
        0 = 40 ms
        1 = 81 ms
        2 = 161 ms
        3 = 322 ms
        4 = 644 ms
        5 = 1.3s
        6 = 2.6 s
        7 = 5.2 s
        MYD_LED_CONFIG_UNCHANGED
    pulseStretchDuration - Only the transmit activity, receive activity, and
        transmit or receive activity are stretched. The pulse stretching is applied first
        and the blinking will reflect the duration of the stretched pulse.
        0 = No pulse stretching
        1 = 20 to 40 ms
        2 = 40 to 81 ms
        3 = 81 to 161 ms
        4 = 161 to 322 ms
        5 = 322 to 644 ms
        6 = 644 ms to 1.3s
        7 = 1.3 to 2.6s
        MYD_LED_CONFIG_UNCHANGED
    Note/Warning:
        On the X7120, MYD_LED3, MYD_LED4 and MYD_LED5 share the same _MYD_LED_TIMER_CONFIG structure.
        On the X6141, all LEDs share the same _MYD_LED_TIMER_CONFIG structure.
        Setting one of the LED will also change timer configuration on the other LEDs.
******************************************************************************/
typedef struct _MYD_LED_TIMER_CONFIG
{
    MYD_U16 blinkRate1;
    MYD_U16 blinkRate2;
    MYD_U16 pulseStretchDuration;
} MYD_LED_TIMER_CONFIG;

/******************************************************************************
MYD_STATUS mydConfigLEDPin
(
    IN MYD_DEV_PTR pDev,
    IN MYD_LED_ID ledId,
    IN MYD_LED_CTRL ledCtrl,
    IN MYD_LED_TIMER_CONFIG ledTimerConfig
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    ledId - The Pin to configure, see the definition of MYD_LED_ID.
            The mapped Pin MUST be configured to LED mode first.
            Each LED only represents the activities on the corresponding port.
            X7120 Mapping:                          |   X6141 Mapping:
            ledId       PIN         Port/LEDTimer   |   ledId          PIN        Port/LEDTimer
            MYD_LED0    GPIO1             0         |   MYD_LED0       GPIO0           0
            MYD_LED1    GPIO2             1         |   MYD_LED1       GPIO1           0
            MYD_LED2    GPIO3             2         |   MYD_LED2       GPIO2           0
            MYD_LED3    GPIO4             3         |   MYD_LED3       GPIO3           0
            MYD_LED4    CLK_OUT_SE1       3         |   MYD_LED4       CLK_OUT_SE1     0
            MYD_LED5    CLK_OUT_SE2       3         |   MYD_LED5       CLK_OUT_SE2     0
    ledCtrl - Configure LED sub-lane select, interface select, solid and blink activity,
              LED polarity, mix rate level and which option of blink rate should be selected
    ledTimerConfig - Configure two LED blink rate option and pulse stretch duration
                On the X7120, MYD_LED3, MYD_LED4 and MYD_LED5 share the same ledTimerConfig.
                On the X6141, all LED share the same ledTimerConfig.
                Users can set two blink rate options to be selected in ledCtrl.
 Outputs:
    None

 Returns:
    MYD_OK if configuration was successful, MYD_FAIL if not

 Description:
    This function configures the activities of the given LED Pin. On mapped Port, users can
    select the lane and interface source for the mapped LED. The API provides several activity choices
    to be selected when LED is blinking or in solid status. Also, users can change the
    LED mix rate level, polarity, blink rate and pulse stretch duration.

 Side effects:
    On the X7120, changing one of the MYD_LED3, 4 or 5 ledTimerConfig will also affect the other
    two LEDs.
    
    On the X6141, all LED share the same ledTimerConfig. Changing ledTimerConfig on any of the LED
    will affect all of the LEDs.

 Notes/Warnings:
    This function should only be called after calling the mydPinModeConfig() to configure
    corresponding LED Pin.
    
    See the ledId description for physical Pin mapping.
******************************************************************************/
MYD_STATUS mydConfigLEDPin
(
    IN MYD_DEV_PTR pDev,
    IN MYD_LED_ID ledId,
    IN MYD_LED_CTRL ledCtrl,
    IN MYD_LED_TIMER_CONFIG ledTimerConfig
);


/******************************************************************************
MYD_STATUS mydConfigRClkPin
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID rClkPinId,
    IN MYD_U16 portSelect,
    IN MYD_U16 interfaceSelect,
    IN MYD_U16 muxOptionSelect
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    rClkPinId - the RCLK Pin to configure, the Pin MUST be set to MYD_PIN_MODE_RCLK mode
                See the bit definitions and header of mydSetPinMode() for details.
        MYD_PIN_GPIO2                  Not available on X6141
        MYD_PIN_INTn
        MYD_PIN_CLK_OUT_SE1
        MYD_PIN_CLK_OUT_SE2
        MYD_PIN_CLK_OUT_DIFF_N         Not available on X6141
        MYD_PIN_CLK_OUT_DIFF_P         Not available on X6141

    portSelect - 0-31, select the port for the clock source for the Recovered Clock Pin
    interfaceSelect - select the interface for the clock source for the Recovered Clock Pin
        MYD_LINE_SIDE
        MYD_HOST_SIDE
    muxOptionSelect - Must be 1 or 2. the MUX option is configured by mydConfigRClkMux()

 Outputs:
    None

 Returns:
    MYD_OK if the configuration was successful, MYD_FAIL if not
    If the given Pin is not in MYD_PIN_MODE_RCLK, MYD_FAIL will be returned


 Description:
    Configure the Recovered Clock Pin and select the Recovered Clock source.
    When the Pin is configured to the MYD_PIN_MODE_RCLK, the user can select the port
    and interface where the Recovered Clock signal source generated. Also, the user
    can select which MUX option to use for the selected port and interface.

    The option includes lane selection, source clock(10T/20T/40T or 12T/16T/32T),
    divide ratio(8 bits) and divider enable. Each (port and interface combination) 
    has TWO MUX Options.

 Side effects:
    None.

 Note/Warning:
    User MUST call mydSetPinMode() first to select MYD_PIN_MODE_RCLK for the Pin.
    Then call mydConfigRClkMux() to set the MUX options before using the RCLK Pin.

    On the X7120, GPIO2 can output the Recovered Clock only from Ports 0 and 1.
    CLK_OUT_SE1 can output the Recovered Clock only from Ports 2 and 3.
    CLK_OUT_DIFF_N and CLK_OUT_DIFF_P can output the Recovered Clock
    from Port 3 only.
******************************************************************************/
MYD_STATUS mydConfigRClkPin
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID rClkPinId,
    IN MYD_U16 portSelect,
    IN MYD_U16 interfaceSelect,
    IN MYD_U16 muxOptionSelect
);

/******************************************************************************
Structure for Recovered Clock MUX Configuration
******************************************************************************/

/******************************************************************************
typedef struct _MYD_RCLK_MUX_OPTION MYD_RCLK_MUX_OPTION;
    Structure for each (port, interface) to store RCLK MUX configurations.
    srcClockSelect - Select the clock source for this MUX.
        0 = Select 10T/20T/40T recovered clock
        1 = Select 12T/16T/32T recovered clocks
    laneSelect - select the recovered clock lane
        0 = Select lane 0 recovered clock as source
        1 = Select lane 1 recovered clock as source
        2 = Select lane 2 recovered clock as source
        3 = Select lane 3 recovered clock as source
    divideRatio - Divide ratio for the recovered clock output, 8 bits value
        Divide ratio = 2 * (divideRatio[7:0] + 1)
    dividerConfig - whether the clock output divider should be enabled or not
        0 = Disable
        1 = Enable the recovered clock output divider after the clock is ready
        2 = Enable the recovered clock output divider in any case

******************************************************************************/
typedef struct _MYD_RCLK_MUX_OPTION
{
    MYD_U16 srcClockSelect;
    MYD_U16 laneSelect;
    MYD_U16 divideRatio;
    MYD_U16 dividerConfig;
} MYD_RCLK_MUX_OPTION;

typedef struct _MYD_X7120_RCLK_MUX
{
    MYD_RCLK_MUX_OPTION mux1[MYD_MAX_PORTS][MYD_NUM_INTERFACE];
    MYD_RCLK_MUX_OPTION mux2[MYD_MAX_PORTS][MYD_NUM_INTERFACE];
} MYD_X7120_RCLK_MUX;

typedef struct _MYD_X6141_RCLK_MUX
{
    MYD_RCLK_MUX_OPTION mux1[MYD_NUM_INTERFACE];
    MYD_RCLK_MUX_OPTION mux2[MYD_NUM_INTERFACE];
} MYD_X6141_RCLK_MUX;

typedef union _MYD_RCLK_MUX
{
    MYD_X7120_RCLK_MUX x7120;
    MYD_X6141_RCLK_MUX x6141;
} MYD_RCLK_MUX;

/******************************************************************************
MYD_STATUS mydConfigRClkMux
(
    IN MYD_DEV_PTR pDev,
    IN MYD_RCLK_MUX *pRClkMux
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    pRClkMux - pointer to structure for configuring the Recovered Clock MUX
              on all ports and interfaces
              User MUST pass-in the correct union type for the pRClkMux

 Outputs:
    None

 Returns:
    MYD_OK if the configuration was successful, MYD_FAIL if not

 Description:
    Configure all Recovered Clock MUXs on the device. This functions should be used with
    mydConfigRClkPin() when configuring the recovered clock Pin(s).

    This function allows the user to configure the Recovered Clock MUX options for
    all ports and interfaces.
    
    User can select the clock lane, source clock(10T/20T/40T or 12T/16T/32T), divide
    ratio(8 bits) or disable the divider.

    Please see the structure _MYD_RCLK_MUX_OPTION for details.

 Side effects:
    None.

 Note/Warning:
    All Ports and Interfaces MUX options have to be set at once. i.e. all fields in
    the passed-in array will be used to set MUX options even if the fields are
    filled with the default value of 0.
******************************************************************************/
MYD_STATUS mydConfigRClkMux
(
    IN MYD_DEV_PTR pDev,
    IN MYD_RCLK_MUX *pRClkMux
);

#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MYD_INTR_IO_H */
