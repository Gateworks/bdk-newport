/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
*******************************************************************************/

/********************************************************************************
* mcdInitialization.h
*
* DESCRIPTION:
*       API Prototypes for Marvell X5121/X5111/X2381/X5123/EC808 Device for
*       initializing the driver.
*
* DEPENDENCIES:
*
* FILE REVISION NUMBER:
*
*******************************************************************************/

#ifndef MCDINITIALIZATION_H
#define MCDINITIALIZATION_H

#if C_LINKAGE
#ifdef __cplusplus
extern "C" {
#endif
#endif

/*******************************************************************************
MCD_STATUS mcdInitDriver
(
    IN FMCD_READ_MDIO  readMdio,
    IN FMCD_WRITE_MDIO writeMdio,
    IN MCD_U16         firstMDIOPort,
    IN MCD_U32         const *pCm3Image,
    IN MCD_U32         cm3ImageSize,
    IN MCD_U16         const *pBusMasterImage,
    IN MCD_U16         busMasterImageSize,
    IN MCD_U16         const *pBusMasterSwappedImage,
    IN MCD_U16         busMasterSwappedImageSize,
    IN MCD_U16         const *pSerdesImage,
    IN MCD_U16         serdesImageSize,
    IN MCD_PVOID       pHostContext,
    OUT MCD_DEV_PTR    pDev
);

 Inputs:
   readMdio                  - pointer to host's function to do MDIO read
   writeMdio                 - point to host's function to do MDIO write
   firstMDIOPort             - PHY address
   pCm3Image                 - input buffer image of the CM3 firmware
   cm3ImageSize              - CM3 firmware image size in bytes
   pBusMasterImage           - input buffer image of the SBUS Master ROM
   busMasterImageSize        - SBUS Master ROM image size
   pBusMasterSwappedImage    - input buffer Swapped image of the SBUS Master ROM
   busMasterImageSwappedSize - SBUS Master ROM Swapped image size
   pSerdesImage              - input buffer image of the SERDES ROM
   serdesImageSize           - SERDES ROM image size
   pHostContext              - user specific data for host to pass to the low layer

 Outputs:
       pDev  - pointer to holds device information to be used for each API call.

 Returns:
       MCD_OK               - on success
       MCD_FAIL             - on error

 Description:
   Marvell X5123 and EC808 Driver Initialization Routine.
   This is the first routine that needs be called by system software.
   It takes parameters from system software, and returns a pointer (*dev)
   to a data structure which includes infomation related to this Marvell Phy
   device. This pointer (*dev) is then used for all the API functions.
   The following is the job performed by this routine:
       1. store MDIO read/write function into the given MCD_DEV structure
       2. run any device specific initialization routine (chip hardware reset,
          firmware download, etc.)
       3. Initialize the deviceId and revision information

 Side effects:
   None

 Notes/Warnings:
   An MCD_DEV is required for each Marvell X5123 and EC808
   device in the system.

   This function will skip the firmware/ROM images download if any of the
   4 images has a NULL pointer or image size is 0. However, it will
   continue with the rest of the driver initialization.

*******************************************************************************/
MCD_STATUS mcdInitDriver
(
    IN FMCD_READ_MDIO  readMdio,
    IN FMCD_WRITE_MDIO writeMdio,
    IN MCD_U16         firstMDIOPort,
    IN MCD_U8          const *pCm3Image,
    IN MCD_U32         cm3ImageSize,
    IN MCD_U16         const *pBusMasterImage,
    IN MCD_U16         busMasterImageSize,
    IN MCD_U16         const *pBusMasterSwappedImage,
    IN MCD_U16         busMasterSwappedImageSize,
    IN MCD_U16         const *pSerdesImage,
    IN MCD_U16         serdesImageSize,
    IN MCD_PVOID       pHostContext,
    OUT MCD_DEV_PTR    pDev
);

/*******************************************************************************
MCD_STATUS mcdInitDriverAllDevices
(
    IN FMCD_READ_MDIO  readMdio,
    IN FMCD_WRITE_MDIO writeMdio,
    IN MCD_U16         numOfDevs,
    IN MCD_U16         firstMDIOPortArr[],
    IN MCD_U16         firstMDIOPort,
    IN MCD_U32         const *pCm3Image,
    IN MCD_U32         cm3ImageSize,
    IN MCD_U16         const *pBusMasterImage,
    IN MCD_U16         busMasterImageSize,
    IN MCD_U16         const *pBusMasterSwappedImage,
    IN MCD_U16         busMasterSwappedImageSize,
    IN MCD_U16         const *pSerdesImage,
    IN MCD_U16         serdesImageSize,
    IN MCD_PVOID       pHostContextArr[],
    OUT MCD_DEV_PTR    pDevArr[]
);

 Inputs:
   readMdio                  - pointer to host's function to do MDIO read
   writeMdio                 - point to host's function to do MDIO write
   numOfDevs                 - number of initialized devices
   firstMDIOPortArr          - array of PHY addresses
   pCm3Image                 - input buffer image of the CM3 firmware
   cm3ImageSize              - CM3 firmware image size in bytes
   pBusMasterImage           - input buffer image of the SBUS Master ROM
   busMasterImageSize        - SBUS Master ROM image size
   pBusMasterSwappedImage    - input buffer Swapped image of the SBUS Master ROM
   busMasterImageSwappedSize - SBUS Master ROM Swapped image size
   pSerdesImage              - input buffer image of the SERDES ROM
   serdesImageSize           - SERDES ROM image size
   pHostContextArr           - array of user specific data for host to pass to the low layer

 Outputs:
       pDevArr  - array of pointers to holders of device information to be used for each API call.

 Returns:
       MCD_OK               - on success
       MCD_FAIL             - on error

 Description:
   Marvell X5123/EC808 Driver Initialization Routine.
   This function calls mcdInitDriver function to each of devices without passing loaded FW
   and then downloads FW using broadcast access to all devices.

 Side effects:
   None

 Notes/Warnings:
   An MCD_DEV is required for each Marvell X5123/EC808
   device in the system.

   This function will skip the firmware/ROM images download if any of the
   4 images has a NULL pointer or image size is 0. However, it will
   continue with the rest of the driver initialization.

*******************************************************************************/
MCD_STATUS mcdInitDriverAllDevices
(
    IN FMCD_READ_MDIO  readMdio,
    IN FMCD_WRITE_MDIO writeMdio,
    IN MCD_U16         numOfDevs,
    IN MCD_U16         firstMDIOPortArr[],
    IN MCD_U8          const *pCm3Image,
    IN MCD_U32         cm3ImageSize,
    IN MCD_U16         const *pBusMasterImage,
    IN MCD_U16         busMasterImageSize,
    IN MCD_U16         const *pBusMasterSwappedImage,
    IN MCD_U16         busMasterSwappedImageSize,
    IN MCD_U16         const *pSerdesImage,
    IN MCD_U16         serdesImageSize,
    IN MCD_PVOID       pHostContextArr[],
    OUT MCD_DEV_PTR    pDevArr[]
);

/*******************************************************************
MCD_STATUS mcdUnloadDriver
(
    IN MCD_DEV_PTR pDev
);

 Inputs:
   pDev  - pointer to holds device information to be used for each API call.

 Outputs:
   None

 Returns:
   MCD_OK    - on success
   MCD_FAIL  - on error

 Description:
   This function performs the clean-up task in releasing the Serdes
   memory structure, resetting the dev structure and other clean-up
   operations.

 Side effects:
   None

 Notes/Warnings:
*******************************************************************/
MCD_STATUS mcdUnloadDriver
(
    IN MCD_DEV_PTR pDev
);

/*******************************************************************
MCD_STATUS mcdPortReset
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_RESET_TYPE resetType,
    IN MCD_U16 timeoutMs
);

 Inputs:
   pDev  - pointer to holds device information to be used for each API call.
   mdioPort - MDIO port address, 0-31
   host_or_line - which interface is being modified:
        MCD_HOST_SIDE
        MCD_LINE_SIDE
        MCD_BOTH_SIDE
   resetType - option for Hard or Soft port reset
        MCD_SOFT_RESET
        MCD_HARD_RESET
   timeoutMs - reset timeout in ms

 Outputs:
   None

 Returns:
   MCD_OK               - on success
   MCD_FAIL             - on error

 Description:
   This function performs a port level hardware or software reset.

 Side effects:
   None

 Notes/Warnings:
*******************************************************************/
MCD_STATUS mcdPortReset
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_RESET_TYPE resetType,
    IN MCD_U16 timeoutMs
);

/**
* @internal mcdPreInitSetBootMode function
* @endinternal
*
* @brief   set boot mode before driver initalization
*
* @param[in] mode                 -  Boot Mode
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdPreInitSetBootMode(MCD_BOOT_MODE mode);

/**
* @internal mcdPostInitSetBootMode function
* @endinternal
*
* @brief   set boot mode after Driver was initalized
*
* @param[in] phyId
* @param[in] mode                 -  Boot Mode
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdPostInitSetBootMode
(
    IN MCD_DEV_PTR pDev,
    IN MCD_BOOT_MODE mode
);

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
/**
* @internal mcdGetBootModeState function
* @endinternal
*
* @brief   get the current boot mode
*
* @param[in] phyId 
* @param[in] mode - pointer to boot mode
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdGetBootModeState(MCD_DEV_PTR pDev, MCD_BOOT_MODE *mode);
#endif

/* LED behavior selections. */
typedef enum
{
    MCD_LED_BEHAVIOR_SOLID,
    MCD_LED_BEHAVIOR_BLINK
} MCD_LED_BEHAVIOR_TYPE;
/* LED function selections. */
typedef enum
{
    MCD_LED_FUNC_OFF,            /*0000 - Solid OFF*/
    MCD_LED_FUNC_TXorRX,         /*0001 - LED Transmit OR Receive activity*/
    MCD_LED_FUNC_TX,             /*0010 - LED Transmit Activity */
    MCD_LED_FUNC_RX,             /*0011 - LED Receive Activity */
    MCD_LED_FUNC_LINK_STATUS = 6,/*0110 - LED Link status */
    MCD_LED_FUNC_ON              /*0111 - Solid ON */
} MCD_LED_FUNC_TYPE;

typedef enum
{
    MCD_LED_BLINK_RATE_40ms,        /*000 - 40ms*/
    MCD_LED_BLINK_RATE_161ms,       /*010 - 161ms    */
    MCD_LED_BLINK_RATE_322ms,       /*011 - 322ms    */
    MCD_LED_BLINK_RATE_644ms,       /*100 - 644ms    */
    MCD_LED_BLINK_RATE_1p3s,        /*101 - 1.3s     */
    MCD_LED_BLINK_RATE_2p3s         /*110 - 2.6s     */
} MCD_LED_BLINK_RATE_TYPE;

typedef enum
{
    MCD_LED_NO_PULSE_STRETCH,               /*000 - No pulse stretching   */
    MCD_LED_PULSE_STRETCH_20_TO_40,         /*001 - 20ms to 40ms          */
    MCD_LED_PULSE_STRETCH_40_TO_81,         /*010 - 40ms to 81ms          */
    MCD_LED_PULSE_STRETCH_80_TO_161,        /*011 - 81ms to 161ms         */
    MCD_LED_PULSE_STRETCH_161_TO_322,       /*100 - 161ms to 322ms        */
    MCD_LED_PULSE_STRETCH_322_TO_644,       /*101 - 322ms to 644ms        */
    MCD_LED_PULSE_STRETCH_644_TO_1p3,       /*110 - 644ms to 1.3s         */
    MCD_LED_PULSE_STRETCH_1p3_TO_2p6        /*111 - 1.3s to 2.6s          */
} MCD_LED_PULSE_STRETCH_TYPE;

typedef enum
{
    MCD_LED_POLARITY_ON_LOW_OFF_HIGH,       /* On - drive LED low,  OFF - Drive LED high   */
    MCD_LED_POLARITY_ON_HIGH_OFF_LOW,       /* On - drive LED high, OFF - Drive LED low   */
    MCD_LED_POLARITY_ON_LOW_OFF_TRISTATE,   /* On - drive LED low,  OFF - Tristate LED     */
    MCD_LED_POLARITY_ON_HIGH_OFF_TRISTATE   /* ON - drive LED high, OFF - Tristate LED    */
} MCD_LED_POLARITY_TYPE;

typedef enum
{
    MCD_LED_MIX_PERCENTAGE_0,           /*0000 = 0%         */
    MCD_LED_MIX_PERCENTAGE_12p5,        /*0001 = 12.5%      */
    MCD_LED_MIX_PERCENTAGE_25,          /*0010 = 25 %       */
    MCD_LED_MIX_PERCENTAGE_37p5,        /*0011 = 37.5 %     */
    MCD_LED_MIX_PERCENTAGE_50,          /*0100 = 50 %       */
    MCD_LED_MIX_PERCENTAGE_62p5,        /*0101 = 62.5%      */
    MCD_LED_MIX_PERCENTAGE_75,          /*0110 = 75 %       */
    MCD_LED_MIX_PERCENTAGE_87p5,        /*0111 = 87.5%      */
    MCD_LED_MIX_PERCENTAGE_100          /*1000 = 100%       */
} MCD_LED_MIX_PERCENTAGE_TYPE;

/*******************************************************************
 MCD_STATUS mcdLedControl
Inputs:
    IN pDev  - pointer to holds device information to be used for each API call.
    IN MCD_U16                      ledNum - led number (0 or 1)
    IN MCD_U16                      portNum - port number to display
    IN MCD_U16                      host_or_line
    IN MCD_LED_PULSE_STRETCH_TYPE   pulseStretch
    IN MCD_LED_BEHAVIOR_TYPE        ledBehavior - solid or blink
    IN MCD_LED_FUNC_TYPE            ledFunction - MCD_LED_OFF,  LED_TXorRX, MCD_LED_TX, MCD_LED_RX,  MCD_LED_LINK_STATUS,MCD_LED_ON
    IN MCD_LED_BLINK_RATE_TYPE      blinkRate,
    IN MCD_LED_POLARITY_TYPE        ledPolarity,
    IN MCD_LED_MIX_PERCENTAGE_TYPE  ledMixPercentage

 Outputs:
   None

 Returns:
   MCD_OK    - on success
   MCD_FAIL  - on error

 Description:
   This function defines LED parameters
   operations.

 Side effects:
   None

 Notes/Warnings:

*******************************************************************/
MCD_STATUS mcdLedControl
(
    IN MCD_DEV_PTR                  pDev,
    IN MCD_U16                      ledNum,
    IN MCD_U16                      portNum,
    IN MCD_U16                      host_or_line,
    IN MCD_LED_PULSE_STRETCH_TYPE   pulseStretch,
    IN MCD_LED_BEHAVIOR_TYPE        ledBehavoir,
    IN MCD_LED_FUNC_TYPE            ledFunction,
    IN MCD_LED_BLINK_RATE_TYPE      blinkRate,
    IN MCD_LED_POLARITY_TYPE        ledPolarity,
    IN MCD_LED_MIX_PERCENTAGE_TYPE  ledMixPercentage

 );


#define MCD_CHIP_SW_RESET     (1<<15) /* This reset self clears */
#define MCD_CHIP_HW_RESET     (1<<14) /* This reset self clears, can be combined with MCD_Z80_RESET */
#define MCD_Z80_RESET         (1<<13) /* Will leave Z80 in reset, does not self clear */
#define MCD_Z80_RESET_RELEASE 0

/*******************************************************************
MCD_STATUS mcdChipAndZ80ResetControl
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 resetType,
    IN MCD_BOOL bRestore
);

 Inputs:
   pDev  - pointer to holds device information to be used for each API call.
   resetType - From the following list
    MCD_CHIP_SW_RESET
         or
    MCD_CHIP_HW_RESET (optionally | with MCD_Z80_RESET to reset both)
    MCD_Z80_RESET (optionally | with MCD_CHIP_HW_RESET to reset both)
         or
    MCD_Z80_RESET_RELEASE (following MCD_Z80_RESET to take the Z80 out of reset)

   bRestore - restore saved registers on power-on default

 Outputs:
   None

 Returns:
   MCD_OK               - on success
   MCD_FAIL             - on error

 Description:
   If the option is MCD_CHIP_SW_RESET, does a chip-level software reset
   (this bit self clears).

   If the option is MCD_CHIP_HW_RESET, does a chip-level hardware reset
   (this bit self clears)

   MCD_CHIP_HW_RESET | MCD_Z80_RESET, will do a chip-level and also
   reset the Z80 leaving the Z80 in reset when this function exits. Call
   with MCD_Z80_RESET_RELEASE to take the Z80 out of reset.

   MCD_Z80_RESET, does a Z80 reset, leaving the Z80 in reset. Call
   with MCD_Z80_RESET_RELEASE to take the Z80 out of reset.

 Side effects:
   None

 Notes/Warnings:

*******************************************************************/
MCD_STATUS mcdChipAndZ80ResetControl
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 resetType,
    IN MCD_BOOL bRestore
);


#if C_LINKAGE
#ifdef __cplusplus
}
#endif
#endif

#endif /* MCDINITIALIZATION_H */





