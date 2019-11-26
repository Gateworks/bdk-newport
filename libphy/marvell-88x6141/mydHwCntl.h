/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions and global data for interfacing with 
the host's hardware-specific MDIO and general-purpose
IO in order to control and query the Marvell X7120/X6181/X6141 PHY.

These functions as written were tested with a USB-interface to
access Marvell's EVK. If the user passes a NULL pointer into mydInitDriver 
for MDIO read and write functions then these functions must be ported to 
the host's specific platform.
********************************************************************/
#ifndef MYD_HWCNTL_H
#define MYD_HWCNTL_H

#if C_LINKAGE
#if defined __cplusplus 
    extern "C" { 
#endif 
#endif  

/*******************************************************************
   PORT THESE FUNCTIONS
 *******************************************************************/

/******************************************************************************
MYD_STATUS mydHwXmdioWrite
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort, 
    IN MYD_U16 dev, 
    IN MYD_U16 reg, 
    IN MYD_U16 value
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31 
    dev - MMD device address, 0-31
    reg - MMD register address
    value - data to write

 Outputs:
    None

 Returns:
    MYD_OK - wrote successfully
    MYD_FAIL - an error occurred

 Description:
    Writes a 16-bit word to the MDIO
    Address is in format X.Y.Z, where X selects the MDIO port (0-31), Y selects
    the MMD/Device (0-31), and Z selects the register.

 Side effects:
    None

 Notes/Warnings:
    None

******************************************************************************/
MYD_STATUS mydHwXmdioWrite
( 
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort, 
    IN MYD_U16 dev, 
    IN MYD_U16 reg, 
    IN MYD_U16 value
);


/******************************************************************************
 MYD_STATUS mydHwXmdioRead
 (
     IN MYD_DEV_PTR pDev,
     IN MYD_U16 mdioPort, 
     IN MYD_U16 dev, 
     IN MYD_U16 reg,
     OUT MYD_U16 *data
 );

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31 
    dev - MMD device address, 0-31
    reg - MMD register address

 Outputs:
    data - Returns 16 bit word from the MDIO

 Returns:
    MYD_OK - read successful
    MYD_FAIL - read was unsuccessful
    
 Description:
    Reads a 16-bit word from the MDIO
    Address is in format X.Y.Z, where X selects the MDIO port (0-31), Y selects the 
    MMD/Device (0-31), and Z selects the register.

 Side effects:
    None

 Notes/Warnings:
    None

******************************************************************************/
MYD_STATUS mydHwXmdioRead
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort, 
    IN MYD_U16 dev, 
    IN MYD_U16 reg,
    OUT MYD_U16 *data
);


/*******************************************************************************
  MYD_STATUS mydHwGetPhyRegField
  (
      IN  MYD_DEV_PTR  pDev,
      IN  MYD_U16      mdioPort, 
      IN  MYD_U16      dev, 
      IN  MYD_U16      regAddr,
      IN  MYD_U8       fieldOffset,
      IN  MYD_U8       fieldLength,
      OUT MYD_U16      *data
  );

  Inputs:  
        pDev - pointer to MYD_DEV initialized by mydInitDriver() call
        mdioPort       - The MDIO port address, 0-31
        dev        - The MMD device, 0-31 
        regAddr    - The register's address
        fieldOffset - The field start bit index. (0 - 15)
        fieldLength - Number of bits to read

  Outputs:
        data        - The read register field

  Returns:
        MYD_OK on success, or
        MYD_FAIL  - on error

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
        mydHwXmdioRead() to get the register value, then operate on the
        register data repeatedly using mydHwGetRegFieldFromWord() to
        take apart the bit fields without re-reading the register again.

        This approach should also be used to reduce IO to the PHY when reading
        multiple bit fields (do a single read, then grab different fields 
        from the register by using mydHwGetRegFieldFromWord() repeatedly).

*******************************************************************************/
MYD_STATUS mydHwGetPhyRegField
(
    IN  MYD_DEV_PTR  pDev,
    IN  MYD_U16      mdioPort, 
    IN  MYD_U16      dev, 
    IN  MYD_U16      regAddr,
    IN  MYD_U8       fieldOffset,
    IN  MYD_U8       fieldLength,
    OUT MYD_U16      *data
);


/*******************************************************************************
  MYD_STATUS mydHwSetPhyRegField
  (
      IN MYD_DEV_PTR  pDev,
      IN MYD_U16      mdioPort, 
      IN MYD_U16      dev, 
      IN MYD_U16      regAddr,
      IN MYD_U8       fieldOffset,
      IN MYD_U8       fieldLength,
      IN MYD_U16      data
  );
  
  Inputs:
        pDev       - pointer to MYD_DEV initialized by mydInitDriver() call  
        mdioPort       - The MDIO port address, 0-31
        dev        - The MMD device, 0-31
        regAddr    -  The register's address
        fieldOffset - The field start bit index. (0 - 15)
        fieldLength - Number of bits to write
        data        - Data to be written.
  
  Outputs:
        None.
  
  Returns:
        MYD_OK on success, or
        MYD_FAIL  - on error

  Description:
        This function writes to specified field in a mdioPort's phy register.
  
  Side effects:
     None
  
  Notes/Warnings:
        The sum of fieldOffset & fieldLength parameters must be smaller-
        equal to 16.
  
*******************************************************************************/
MYD_STATUS mydHwSetPhyRegField
(
    IN MYD_DEV_PTR  pDev,
    IN MYD_U16      mdioPort, 
    IN MYD_U16      dev, 
    IN MYD_U16      regAddr,
    IN MYD_U8       fieldOffset,
    IN MYD_U8       fieldLength,
    IN MYD_U16      data
);


/*******************************************************************************
  MYD_STATUS mydHwGetRegFieldFromWord
  (
      IN  MYD_U16      regData,
      IN  MYD_U8       fieldOffset,
      IN  MYD_U8       fieldLength,
      OUT MYD_U16      *data
  );

  Inputs:  
        regData    - The data previously read from the register
        fieldOffset - The field start bit index. (0 - 15)
        fieldLength - Number of bits to read

  Outputs:
        data        - The data from the associated bit field

  Returns:
        MYD_OK always

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

        MYD_U16 aword, nibble1, nibble2;

        mydHwGetRegFieldFromWord(aword,0,4,&nibble1); - grab first nibble
        mydHwGetRegFieldFromWord(aword,4,4,&nibble2); - grab second nibble
                
*******************************************************************************/
MYD_STATUS mydHwGetRegFieldFromWord
(
    IN  MYD_U16 regData,
    IN  MYD_U8  fieldOffset,
    IN  MYD_U8  fieldLength,
    OUT MYD_U16 *data
);


/*******************************************************************************
  MYD_STATUS mydHwSetRegFieldToWord
  (
      IN  MYD_U16 regData,
      IN  MYD_U16 bitFieldData,
      IN  MYD_U8  fieldOffset,
      IN  MYD_U8  fieldLength,
      OUT MYD_U16 *data
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
        MYD_OK always

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

        MYD_U16 aword;

        mydHwSetRegFieldToWord(aword,2,0,4,&aword); - Change first nibble to 2
        mydHwSetRegFieldToWord(aword,3,4,4,&aword); - Change second nibble to 3
        
*******************************************************************************/
MYD_STATUS mydHwSetRegFieldToWord
(
    IN  MYD_U16 regData,
    IN  MYD_U16 bitFieldData,
    IN  MYD_U8  fieldOffset,
    IN  MYD_U8  fieldLength,
    OUT MYD_U16 *data
);


/******************************************************************************
MYD_STATUS mydWait
(
    IN MYD_DEV_PTR pDev,
    IN MYD_UINT waitTime
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    waitTime - number of milliseconds to wait

 Outputs:
    None

 Returns:
    MYD_OK if wait was successful, MYD_FAIL otherwise

 Description:
    The function is platform dependent. It requires to be ported to support platform.
    Waits waitTime milliseconds

 Side effects:
    None

 Notes/Warnings:
    None

******************************************************************************/
MYD_STATUS mydWait
(
    IN MYD_DEV_PTR pDev,
    IN MYD_UINT waitTime
);


#if C_LINKAGE
#if defined __cplusplus 
}
#endif 
#endif

#endif /* defined MYD_HWCNTL_H */



