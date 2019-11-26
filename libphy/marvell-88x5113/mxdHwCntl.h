/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions and global data for interfacing with 
the host's hardware-specific MDIO and general-purpose
IO in order to control and query the Marvell X5113 PHY.

These functions as written were tested with a USB-interface to
access Marvell's EVK. If the user passes a NULL pointer into mxdInitDriver 
for MDIO read and write functions then these functions must be ported to 
the host's specific platform.
********************************************************************/
#ifndef MXD_HWCNTL_H
#define MXD_HWCNTL_H

#if C_LINKAGE
#if defined __cplusplus 
    extern "C" { 
#endif 
#endif  

/*******************************************************************
   PORT THESE FUNCTIONS
 *******************************************************************/

/******************************************************************************
MXD_STATUS mxdHwXmdioWrite
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort, 
    IN MXD_U16 dev, 
    IN MXD_U16 reg, 
    IN MXD_U16 value
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31 
    dev - MMD device address, 0-31
    reg - MMD register address
    value - data to write

 Outputs:
    None

 Returns:
    MXD_OK - wrote successfully
    MXD_FAIL - an error occurred

 Description:
    Writes a 16-bit word to the MDIO
    Address is in format X.Y.Z, where X selects the MDIO port (0-31), Y selects
    the MMD/Device (0-31), and Z selects the register.

 Side effects:
    None

 Notes/Warnings:
    None

******************************************************************************/
MXD_STATUS mxdHwXmdioWrite
( 
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort, 
    IN MXD_U16 dev, 
    IN MXD_U16 reg, 
    IN MXD_U16 value
);


/******************************************************************************
 MXD_STATUS mxdHwXmdioRead
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16 mdioPort, 
     IN MXD_U16 dev, 
     IN MXD_U16 reg,
     OUT MXD_U16 *data
 );

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31 
    dev - MMD device address, 0-31
    reg - MMD register address

 Outputs:
    data - Returns 16 bit word from the MDIO

 Returns:
    MXD_OK - read successful
    MXD_FAIL - read was unsuccessful
    
 Description:
    Reads a 16-bit word from the MDIO
    Address is in format X.Y.Z, where X selects the MDIO port (0-31), Y selects the 
    MMD/Device (0-31), and Z selects the register.

 Side effects:
    None

 Notes/Warnings:
    None

******************************************************************************/
MXD_STATUS mxdHwXmdioRead
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort, 
    IN MXD_U16 dev, 
    IN MXD_U16 reg,
    OUT MXD_U16 *data
);


/*******************************************************************************
  MXD_STATUS mxdHwGetPhyRegField
  (
      IN  MXD_DEV_PTR  pDev,
      IN  MXD_U16      mdioPort, 
      IN  MXD_U16      dev, 
      IN  MXD_U16      regAddr,
      IN  MXD_U8       fieldOffset,
      IN  MXD_U8       fieldLength,
      OUT MXD_U16      *data
  );

  Inputs:  
        pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
        mdioPort       - The MDIO port address, 0-31
        dev        - The MMD device, 0-31 
        regAddr    - The register's address
        fieldOffset - The field start bit index. (0 - 15)
        fieldLength - Number of bits to read

  Outputs:
        data        - The read register field

  Returns:
        MXD_OK on success, or
        MXD_FAIL  - on error

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
        mxdHwXmdioRead() to get the register value, then operate on the
        register data repeatedly using mxdHwGetRegFieldFromWord() to
        take apart the bit fields without re-reading the register again.

        This approach should also be used to reduce IO to the PHY when reading
        multiple bit fields (do a single read, then grab different fields 
        from the register by using mxdHwGetRegFieldFromWord() repeatedly).

*******************************************************************************/
MXD_STATUS mxdHwGetPhyRegField
(
    IN  MXD_DEV_PTR  pDev,
    IN  MXD_U16      mdioPort, 
    IN  MXD_U16      dev, 
    IN  MXD_U16      regAddr,
    IN  MXD_U8       fieldOffset,
    IN  MXD_U8       fieldLength,
    OUT MXD_U16      *data
);


/*******************************************************************************
  MXD_STATUS mxdHwSetPhyRegField
  (
      IN MXD_DEV_PTR  pDev,
      IN MXD_U16      mdioPort, 
      IN MXD_U16      dev, 
      IN MXD_U16      regAddr,
      IN MXD_U8       fieldOffset,
      IN MXD_U8       fieldLength,
      IN MXD_U16      data
  );
  
  Inputs:
        pDev       - pointer to MXD_DEV initialized by mxdInitDriver() call  
        mdioPort       - The MDIO port address, 0-31
        dev        - The MMD device, 0-31
        regAddr    -  The register's address
        fieldOffset - The field start bit index. (0 - 15)
        fieldLength - Number of bits to write
        data        - Data to be written.
  
  Outputs:
        None.
  
  Returns:
        MXD_OK on success, or
        MXD_FAIL  - on error

  Description:
        This function writes to specified field in a mdioPort's phy register.
  
  Side effects:
     None
  
  Notes/Warnings:
        The sum of fieldOffset & fieldLength parameters must be smaller-
        equal to 16.
  
*******************************************************************************/
MXD_STATUS mxdHwSetPhyRegField
(
    IN MXD_DEV_PTR  pDev,
    IN MXD_U16      mdioPort, 
    IN MXD_U16      dev, 
    IN MXD_U16      regAddr,
    IN MXD_U8       fieldOffset,
    IN MXD_U8       fieldLength,
    IN MXD_U16      data
);


/*******************************************************************************
  MXD_STATUS mxdHwGetRegFieldFromWord
  (
      IN  MXD_U16      regData,
      IN  MXD_U8       fieldOffset,
      IN  MXD_U8       fieldLength,
      OUT MXD_U16      *data
  );

  Inputs:  
        regData    - The data previously read from the register
        fieldOffset - The field start bit index. (0 - 15)
        fieldLength - Number of bits to read

  Outputs:
        data        - The data from the associated bit field

  Returns:
        MXD_OK always

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

        MXD_U16 aword, nibble1, nibble2;

        mxdHwGetRegFieldFromWord(aword,0,4,&nibble1); - grab first nibble
        mxdHwGetRegFieldFromWord(aword,4,4,&nibble2); - grab second nibble
                
*******************************************************************************/
MXD_STATUS mxdHwGetRegFieldFromWord
(
    IN  MXD_U16 regData,
    IN  MXD_U8  fieldOffset,
    IN  MXD_U8  fieldLength,
    OUT MXD_U16 *data
);


/*******************************************************************************
  MXD_STATUS mxdHwSetRegFieldToWord
  (
      IN  MXD_U16 regData,
      IN  MXD_U16 bitFieldData,
      IN  MXD_U8  fieldOffset,
      IN  MXD_U8  fieldLength,
      OUT MXD_U16 *data
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
        MXD_OK always

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

        MXD_U16 aword;

        mxdHwSetRegFieldToWord(aword,2,0,4,&aword); - Change first nibble to 2
        mxdHwSetRegFieldToWord(aword,3,4,4,&aword); - Change second nibble to 3
        
*******************************************************************************/
MXD_STATUS mxdHwSetRegFieldToWord
(
    IN  MXD_U16 regData,
    IN  MXD_U16 bitFieldData,
    IN  MXD_U8  fieldOffset,
    IN  MXD_U8  fieldLength,
    OUT MXD_U16 *data
);


/******************************************************************************
MXD_STATUS mxdWait
(
    IN MXD_DEV_PTR pDev,
    IN unsigned waitTime
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    waitTime - number of milliseconds to wait

 Outputs:
    None

 Returns:
    MXD_OK if wait was successful, MXD_FAIL otherwise

 Description:
    The function is platform dependent. It requires to be ported to support platform.
    Waits waitTime milliseconds

 Side effects:
    None

 Notes/Warnings:
    None

******************************************************************************/
MXD_STATUS mxdWait
(
    IN MXD_DEV_PTR pDev,
    IN MXD_UINT waitTime
);


#if C_LINKAGE
#if defined __cplusplus 
}
#endif 
#endif

#endif /* defined MXD_HWCNTL_H */



