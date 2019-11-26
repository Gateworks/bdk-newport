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
This file contains functions and global data for interfacing with
the host's hardware-specific MDIO and general-purpose
IO in order to control and query the Marvell X5121/X5111/X2381/X5123/EC808
PHY.

These functions as written were tested with a USB-interface to
access Marvell's EVK. If the user passes a NULL pointer into mcdInitDriver
for MDIO read and write functions then these functions must be ported to
the host's specific platform.
********************************************************************/
#ifndef MCD_HWCNTL_H
#define MCD_HWCNTL_H

#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

#define  MCD_PHY_BROADCAST_HW 0x1F

/* control registers accessable by SMI ditectly */
#define  MCD_SMI_WRITE_ADDRESS_MSB_REGISTER       (0x00)
#define  MCD_SMI_WRITE_ADDRESS_LSB_REGISTER       (0x01)
#define  MCD_SMI_READ_ADDRESS_MSB_REGISTER        (0x04)
#define  MCD_SMI_READ_ADDRESS_LSB_REGISTER        (0x05)
#define  MCD_SMI_READ_DATA_MSB_REGISTER           (0x06)
#define  MCD_SMI_READ_DATA_LSB_REGISTER           (0x07)
#define  MCD_SMI_WRITE_DATA_MSB_REGISTER          (0x08)
#define  MCD_SMI_WRITE_DATA_LSB_REGISTER          (0x09)
#define  MCD_SMI_CONFIGURATION_REGISTER           (0x0a)
#define  MCD_SMI_STATUS_REGISTER                  (0x1f)
#define  MCD_SMI_DEVICE_ID_HIGH_REGISTER          (0x02)
#define  MCD_SMI_DEVICE_ID_LOW_REGISTER           (0x03)
/* several fields in registers */
#define  MCD_SMI_STATUS_READ_READY                (0x01)
#define  MCD_SMI_STATUS_WRITE_DONE                (0x02)
#define  MCD_SMI_CONFIGURATION_WRITE_BY_ADDRESS   0
#define  MCD_SMI_CONFIGURATION_WRITE_INCREMENTED  1
/* indirect write timeout in status regireter reads */
#define  MCD_SMI_TIMEOUT_COUNTER                  0 /*10000*/


    /*******************************************************************
   PORT THESE FUNCTIONS
 *******************************************************************/

/******************************************************************************
MCD_STATUS mcdHwXmdioWrite
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 dev,
    IN MCD_U16 reg,
    IN MCD_U16 value
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    dev - MMD device address, 0-31
    reg - MMD register address
    value - data to write

 Outputs:
    None

 Returns:
    MCD_OK - wrote successfully
    MCD_FAIL - an error occurred

 Description:
    Writes a 16-bit word to the MDIO
    Address is in format X.Y.Z, where X selects the MDIO port (0-31), Y selects
    the MMD/Device (0-31), and Z selects the register.

 Side effects:
    None

 Notes/Warnings:
    None

******************************************************************************/
MCD_STATUS mcdHwXmdioWrite
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 dev,
    IN MCD_U16 reg,
    IN MCD_U16 value
);


/******************************************************************************
 MCD_STATUS mcdHwXmdioRead
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 mdioPort,
     IN MCD_U16 dev,
     IN MCD_U16 reg,
     OUT MCD_U16 *data
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    dev - MMD device address, 0-31
    reg - MMD register address

 Outputs:
    data - Returns 16 bit word from the MDIO

 Returns:
    MCD_OK - read successful
    MCD_FAIL - read was unsuccessful

 Description:
    Reads a 16-bit word from the MDIO
    Address is in format X.Y.Z, where X selects the MDIO port (0-31), Y selects the
    MMD/Device (0-31), and Z selects the register.

 Side effects:
    None

 Notes/Warnings:
    None

******************************************************************************/
MCD_STATUS mcdHwXmdioRead
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 dev,
    IN MCD_U16 reg,
    OUT MCD_U16 *data
);


/*******************************************************************************
  MCD_STATUS mcdHwGetPhyRegField
  (
      IN  MCD_DEV_PTR  pDev,
      IN  MCD_U16      mdioPort,
      IN  MCD_U16      dev,
      IN  MCD_U16      regAddr,
      IN  MCD_U8       fieldOffset,
      IN  MCD_U8       fieldLength,
      OUT MCD_U16      *data
  );

  Inputs:
        pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
        mdioPort       - The MDIO port address, 0-31
        dev        - The MMD device, 0-31
        regAddr    - The register's address
        fieldOffset - The field start bit index. (0 - 15)
        fieldLength - Number of bits to read

  Outputs:
        data        - The read register field

  Returns:
        MCD_OK on success, or
        MCD_FAIL  - on error

  Description:
        This function reads a specified field from a mdioPort's phy register.
        It first reads the register, then returns the specified bit
        field from what was read.

  Side effects:
     None

  Notes/Warnings:
        The sum of fieldOffset & fieldLength parameters must be smaller-
        equal to 16

        Reading a register with latched bits may clear the latched bits.
        Use with caution for registers with latched bits.

        To operate on several bits within a register which has latched bits
        before reading the register again, first read the register with
        mcdHwXmdioRead() to get the register value, then operate on the
        register data repeatedly using mcdHwGetRegFieldFromWord() to
        take apart the bit fields without re-reading the register again.

        This approach should also be used to reduce IO to the PHY when reading
        multiple bit fields (do a single read, then grab different fields
        from the register by using mcdHwGetRegFieldFromWord() repeatedly).

*******************************************************************************/
MCD_STATUS mcdHwGetPhyRegField
(
    IN  MCD_DEV_PTR  pDev,
    IN  MCD_U16      mdioPort,
    IN  MCD_U16      dev,
    IN  MCD_U16      regAddr,
    IN  MCD_U8       fieldOffset,
    IN  MCD_U8       fieldLength,
    OUT MCD_U16      *data
);


/*******************************************************************************
  MCD_STATUS mcdHwSetPhyRegField
  (
      IN MCD_DEV_PTR  pDev,
      IN MCD_U16      mdioPort,
      IN MCD_U16      dev,
      IN MCD_U16      regAddr,
      IN MCD_U8       fieldOffset,
      IN MCD_U8       fieldLength,
      IN MCD_U16      data
  );

  Inputs:
        pDev       - pointer to MCD_DEV initialized by mcdInitDriver() call
        mdioPort       - The MDIO port address, 0-31
        dev        - The MMD device, 0-31
        regAddr    -  The register's address
        fieldOffset - The field start bit index. (0 - 15)
        fieldLength - Number of bits to write
        data        - Data to be written.

  Outputs:
        None.

  Returns:
        MCD_OK on success, or
        MCD_FAIL  - on error

  Description:
        This function writes to specified field in a mdioPort's phy register.

  Side effects:
     None

  Notes/Warnings:
        The sum of fieldOffset & fieldLength parameters must be smaller-
        equal to 16.

*******************************************************************************/
MCD_STATUS mcdHwSetPhyRegField
(
    IN MCD_DEV_PTR  pDev,
    IN MCD_U16      mdioPort,
    IN MCD_U16      dev,
    IN MCD_U16      regAddr,
    IN MCD_U8       fieldOffset,
    IN MCD_U8       fieldLength,
    IN MCD_U16      data
);


/*******************************************************************************
  MCD_STATUS mcdHwGetRegFieldFromWord
  (
      IN  MCD_U16      regData,
      IN  MCD_U8       fieldOffset,
      IN  MCD_U8       fieldLength,
      OUT MCD_U16      *data
  );

  Inputs:
        regData    - The data previously read from the register
        fieldOffset - The field start bit index. (0 - 15)
        fieldLength - Number of bits to read

  Outputs:
        data        - The data from the associated bit field

  Returns:
        MCD_OK always

  Description:
        This function grabs a value from a bitfield within a word. It could
        be used to get the value of a bitfield within a word which was previously
        read from the PHY.

  Side effects:
     None

  Notes/Warnings:
        The sum of fieldOffset & fieldLength parameters must be smaller-
        equal to 16

        This register acts on data passed in. It does no hardware access.

        This function is useful if you want to do 1 register access and then
        get different bit fields without doing another register access either
        because there are latched bits in the register to avoid another read,
        or to keep hardware IO down to improve performance/throughput.

        Example:

        MCD_U16 aword, nibble1, nibble2;

        mcdHwGetRegFieldFromWord(aword,0,4,&nibble1); - grab first nibble
        mcdHwGetRegFieldFromWord(aword,4,4,&nibble2); - grab second nibble

*******************************************************************************/
MCD_STATUS mcdHwGetRegFieldFromWord
(
    IN  MCD_U16 regData,
    IN  MCD_U8  fieldOffset,
    IN  MCD_U8  fieldLength,
    OUT MCD_U16 *data
);


/*******************************************************************************
  MCD_STATUS mcdHwSetRegFieldToWord
  (
      IN  MCD_U16 regData,
      IN  MCD_U16 bitFieldData,
      IN  MCD_U8  fieldOffset,
      IN  MCD_U8  fieldLength,
      OUT MCD_U16 *data
  );

  Inputs:
        regData - original word to modify
        bitFieldData   - The data to set the register field to
                     (must be <= largest value for that bit field,
                      no range checking is done by this function)
        fieldOffset - The field start bit index. (0 - 15)
        fieldLength - Number of bits to write to regData

  Outputs:
        data        - The new/modified regData with the bitfield changed

  Returns:
        MCD_OK always

  Description:
        This function write a value to a bitfield within a word.

  Side effects:
     None

  Notes/Warnings:
        The sum of fieldOffset & fieldLength parameters must be smaller-
        equal to 16

        This register acts on data passed in. It does no hardware access.

        This function is useful to reduce IO if several bit fields of a register
        that has been read is to be changed before writing it back.

        MCD_U16 aword;

        mcdHwSetRegFieldToWord(aword,2,0,4,&aword); - Change first nibble to 2
        mcdHwSetRegFieldToWord(aword,3,4,4,&aword); - Change second nibble to 3

*******************************************************************************/
MCD_STATUS mcdHwSetRegFieldToWord
(
    IN  MCD_U16 regData,
    IN  MCD_U16 bitFieldData,
    IN  MCD_U8  fieldOffset,
    IN  MCD_U8  fieldLength,
    OUT MCD_U16 *data
);


/******************************************************************************
MCD_STATUS mcdWait
(
    IN MCD_DEV_PTR pDev,
    IN unsigned waitTime
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    waitTime - number of milliseconds to wait

 Outputs:
    None

 Returns:
    MCD_OK if wait was successful, MCD_FAIL otherwise

 Description:
    The function is platform dependent. It requires to be ported to support platform.
    Waits waitTime milliseconds

 Side effects:
    None

 Notes/Warnings:
    None

******************************************************************************/
MCD_STATUS mcdWait
(
    IN MCD_DEV_PTR pDev,
    IN MCD_UINT waitTime
);


/******************************************************************************
   32-BIT Access Support
******************************************************************************/

/******************************************************************************
MCD_STATUS mcdHwXmdioWaitStatus
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16     mdioPort,
    IN MCD_U16     reg,
    IN MCD_U16     mask,
    IN MCD_U32     timeout
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    reg - MMD register address
    mask - 16 bit value of bits to check all of them to be ones
    timeout - maximal amount of reading the given register.

 Outputs:
    None

 Returns:
    MCD_OK - wrote successfully
    MCD_FAIL - an error occurred

 Description:
    Reads the given register until bits given in mask set or timeout attempts finished.

 Side effects:
    None

 Notes/Warnings:
    None

*******************************************************************************/
MCD_STATUS mcdHwXmdioWaitStatus
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16     reg,
    IN MCD_U16     mask,
    IN MCD_U32     timeout
);

/******************************************************************************
MCD_STATUS mcdHwXmdioAccessInit32bit
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U32     mdioPort
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call

 Outputs:
    None

 Returns:
    MCD_OK - wrote successfully
    MCD_FAIL - an error occurred

 Description:
    Initializes 32-bit read/write mechanism.

 Side effects:
    None

 Notes/Warnings:
    None

*******************************************************************************/
MCD_STATUS mcdHwXmdioAccessInit32bit
(
    IN MCD_DEV_PTR pDev
);

/******************************************************************************
MCD_STATUS mcdHwXmdioWrite32bit
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U32     mdioPort,
    IN MCD_U32     reg,
    IN MCD_U32     value
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    reg - register address
    value - data to write

 Outputs:
    None

 Returns:
    MCD_OK - wrote successfully
    MCD_FAIL - an error occurred

 Description:
    Writes a 32-bit word to the MDIO.
    Address is 32 bit value from Functional Specification.

 Side effects:
    None

 Notes/Warnings:
    None

*******************************************************************************/
MCD_STATUS mcdHwXmdioWrite32bit
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U32     mdioPort,
    IN MCD_U32     reg,
    IN MCD_U32     value
);

/******************************************************************************
MCD_STATUS mcdHwXmdioRead32bit
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U32     mdioPort,
    IN  MCD_U32     reg,
    OUT MCD_U32     *data
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    reg - register address

 Outputs:
    data - Returns 32 bit word from the MDIO

 Returns:
    MCD_OK - read successful
    MCD_FAIL - read was unsuccessful

 Description:
    Reads a 32-bit word from the MDIO
    Address is 32 bit value from Functional Specification.

 Side effects:
    None

 Notes/Warnings:
    None

*******************************************************************************/
MCD_STATUS mcdHwXmdioRead32bit
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U32     mdioPort,
    IN  MCD_U32     reg,
    OUT MCD_U32     *data
);

/******************************************************************************
MCD_STATUS mcdHwSetPhyRegField32bit
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U32     mdioPort,
    IN MCD_U32     reg,
    IN MCD_U32     offset,
    IN MCD_U32     length,
    IN MCD_U32     value
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    reg    -  register address
    offset - offset of field in bits
    length - length of field in bits
    value  - value to set.

 Outputs:
    None

 Returns:
    MCD_OK - read successful
    MCD_FAIL - read was unsuccessful

 Description:
    set a field of the 32-bit register from the MDIO
    Address is 32 bit value from Functional Specification.

 Side effects:
    None

 Notes/Warnings:
    None

*******************************************************************************/
MCD_STATUS mcdHwSetPhyRegField32bit
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U32     mdioPort,
    IN MCD_U32     reg,
    IN MCD_U32     offset,
    IN MCD_U32     length,
    IN MCD_U32     value
);

/******************************************************************************
MCD_STATUS mcdHwGetPhyRegField32bit
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U32     mdioPort,
    IN  MCD_U32     reg,
    IN  MCD_U32     offset,
    IN  MCD_U32     length,
    OUT MCD_U32     *value
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    reg - register address
    offset - offset of field in bits
    length - length of field in bits

 Outputs:
    value - Returns 32 bit word containig retrieved field.

 Returns:
    MCD_OK - read successful
    MCD_FAIL - read was unsuccessful

 Description:
    get a field of the 32-bit register from the MDIO
    Address is 32 bit value from Functional Specification.

 Side effects:
    None

 Notes/Warnings:
    None

*******************************************************************************/
MCD_STATUS mcdHwGetPhyRegField32bit
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U32     mdioPort,
    IN  MCD_U32     reg,
    IN  MCD_U32     offset,
    IN  MCD_U32     length,
    OUT MCD_U32     *value
);

/******************************************************************************
MCD_STATUS mcdHwSetPhyRegMask32bit
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U32     mdioPort,
    IN MCD_U32     reg,
    IN MCD_U32     mask,
    IN MCD_U32     value
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    reg - register address
    mask - mask of updated bits
    value  - value to set.

 Outputs:
    None

 Returns:
    MCD_OK - read successful
    MCD_FAIL - read was unsuccessful

 Description:
    set a bits of the 32-bit register from the MDIO given by mask
    Address is 32 bit value from Functional Specification.

 Side effects:
    None

 Notes/Warnings:
    None

*******************************************************************************/
MCD_STATUS mcdHwSetPhyRegMask32bit
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U32     mdioPort,
    IN MCD_U32     reg,
    IN MCD_U32     mask,
    IN MCD_U32     value
);

/******************************************************************************
MCD_STATUS mcdHwGetPhyRegMask32bit
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U32     mdioPort,
    IN  MCD_U32     reg,
    IN  MCD_U32     mask,
    OUT MCD_U32     *value
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    reg - register address
    mask - mask of retieved bits

 Outputs:
    value - Returns 32 bit word containig retrieved field.

 Returns:
    MCD_OK - read successful
    MCD_FAIL - read was unsuccessful

 Description:
    get a field of the 32-bit register from the MDIO
    Address is 32 bit value from Functional Specification.

 Side effects:
    None

 Notes/Warnings:
    None

*******************************************************************************/
MCD_STATUS mcdHwGetPhyRegMask32bit
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U32     mdioPort,
    IN  MCD_U32     reg,
    IN  MCD_U32     mask,
    OUT MCD_U32     *value
);

/******************************************************************************
MCD_STATUS mcdHwXmdioWaitStatus32Bit
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U32     mdioPort,
    IN MCD_U32     reg,
    IN MCD_U32     mask,
    IN MCD_U32     timeout
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    reg      - register address
    mask     - 32 bit value of bits to check all of them to be as in pattern
    pattern  - 32 bit value of pattern bits to check
    timeout  - maximal amount of reading the given register.

 Outputs:
    None

 Returns:
    MCD_OK - wrote successfully
    MCD_FAIL - an error occurred

 Description:
    Reads the given register until bits given in mask set or timeout attempts finished.

 Side effects:
    None

 Notes/Warnings:
    None

*******************************************************************************/
MCD_STATUS mcdHwXmdioWaitStatus32Bit
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U32     mdioPort,
    IN MCD_U32     reg,
    IN MCD_U32     mask,
    IN MCD_U32     pattern,
    IN MCD_U32     timeout
);


#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MCD_HWCNTL_H */




