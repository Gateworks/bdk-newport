/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains global defines/data for doing register dumps
of registers for the Marvell 88X32X0, 88X33X0, 88E20X0 
and 88E21X0 ethernet PHYs.
********************************************************************/
#ifndef MTDDIAGREGDUMP_H
#define MTDDIAGREGDUMP_H
#if C_LINKAGE
#if defined __cplusplus 
    extern "C" { 
#endif 
#endif

/* change define to 0 to save memory if dump functions aren't used */
#define MTD_CUNIT_REG_DATA          1
#define MTD_F2R_REG_DATA            1
#define MTD_HUNIT_10GBASER_REG_DATA 1
#define MTD_HUNIT_1000BX_REG_DATA   1
#define MTD_HUNIT_COMMON_REG_DATA   1
#define MTD_HUNIT_RXAUI_REG_DATA    1
#define MTD_TUNIT_MMD1_REG_DATA     1
#define MTD_TUNIT_MMD3_REG_DATA     1
#define MTD_TUNIT_MMD3_REG_DATA2    1
#define MTD_TUNIT_MMD3_REG_DATA3    1
#define MTD_TUNIT_MMD7_REG_DATA     1
#define MTD_XUNIT_10GBASER_REG_DATA 1
#define MTD_XUNIT_1000BX_REG_DATA   1
#define MTD_XUNIT_COMMON_REG_DATA   1

#define MTD_DUMP_MAX_REGISTERS 89 /* max registers among all the dump modules in case a single buffer is desired */
#define MTD_SIZEOF_OUTPUT 17 /* sizeof this output string "%2d %2d.%4X=%4X\n" for each register being dumped */
                             /* including NULL character for end of string */

typedef struct
{
    MTD_U16 mmd;
    MTD_U16 reg;
}MTD_MDIO_ADDR_TYPE;

#if MTD_CUNIT_REG_DATA
extern const MTD_MDIO_ADDR_TYPE cUnitRegData[];
#define MTD_CUNIT_NUM_REGS 89
#endif

#if MTD_F2R_REG_DATA
extern const MTD_MDIO_ADDR_TYPE f2rRegData[];
#define MTD_F2R_NUM_REGS 8
#endif

#if MTD_HUNIT_10GBASER_REG_DATA
extern const MTD_MDIO_ADDR_TYPE hUnit10grRegData[];
#define MTD_HUNIT_10GBASER_NUM_REGS 29
#endif

#if MTD_HUNIT_1000BX_REG_DATA
extern const MTD_MDIO_ADDR_TYPE hUnit1000bxRegData[];
#define MTD_HUNIT_1000BX_NUM_REGS 16
#endif

#if MTD_HUNIT_COMMON_REG_DATA
extern const MTD_MDIO_ADDR_TYPE hUnitCommonRegData[];
#define MTD_HUNIT_COMMON_NUM_REGS 46
#endif

#if MTD_HUNIT_RXAUI_REG_DATA
extern const MTD_MDIO_ADDR_TYPE hUnitRxauiRegData[];
#define MTD_HUNIT_RXAUI_NUM_REGS 29
#endif

#if MTD_TUNIT_MMD1_REG_DATA
extern const MTD_MDIO_ADDR_TYPE tUnitMmd1RegData[];
#define MTD_TUNIT_MMD1_NUM_REGS 60
#endif

#if MTD_TUNIT_MMD3_REG_DATA
extern const MTD_MDIO_ADDR_TYPE tUnitMmd3RegData[];
#define MTD_TUNIT_MMD3_NUM_REGS 18
#endif

#if MTD_TUNIT_MMD3_REG_DATA2
extern const MTD_MDIO_ADDR_TYPE tUnitMmd3RegData2[];
#define MTD_TUNIT_MMD3_2_NUM_REGS 25
#endif

#if MTD_TUNIT_MMD3_REG_DATA3
extern const MTD_MDIO_ADDR_TYPE tUnitMmd3RegData3[];
#define MTD_TUNIT_MMD3_3_NUM_REGS 32
#endif

#if MTD_TUNIT_MMD7_REG_DATA
extern const MTD_MDIO_ADDR_TYPE tUnitMmd7RegData[];
#define MTD_TUNIT_MMD7_NUM_REGS 39
#endif

#if MTD_XUNIT_10GBASER_REG_DATA
extern const MTD_MDIO_ADDR_TYPE xUnit10grRegData[];
#define MTD_XUNIT_10GBASER_NUM_REGS 29
#endif

#if MTD_XUNIT_1000BX_REG_DATA
extern const MTD_MDIO_ADDR_TYPE xUnit1000bxRegData[];
#define MTD_XUNIT_1000BX_NUM_REGS 21
#endif

#if MTD_XUNIT_COMMON_REG_DATA
extern const MTD_MDIO_ADDR_TYPE xUnitCommonRegData[];
#define MTD_XUNIT_COMMON_NUM_REGS 46
#endif

/******************************************************************************

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    addrArray - array of MDIO addresses in form
                device id/register pairs. These
                are the addresses to dump.
    addrArrayLength - length of the addrArray
    dumpBuffer - character array to write
                 the output to
    dumpBufferLength - number of characters available
                       in dumpBuffer (remaining characters
                       starting from bufferOffset to end
                       of buffer). Use total size of buffer
                       if bufferOffset is 0.
    bufferOffset - index into dumpBuffer to where to start
                   writing data (use 0 to begin at beginning)
  
 Outputs:
    dumpBuffer - updated character array
    bufferOffset - updated bufferOffset after copying the data.
                   Points past end of buffer if buffer is full,
                   if buffer is not full, points to next available
                   character to start copying data.

 Returns:
    MTD_OK if data was read and copied without error, MTD_FAIL
    if an error occurred reading a register or there was not
    room in the buffer to copy all the data.

 Description: Reads each register from the given "port" in the list
 of mmd/register pairs and writes a formatted string to the character
 buffer, "dumpBuffer". Each string is terminated with '\n\0'. If
 all registers are read successfully, and copied successfully, MTD_OK
 is returned. If any error occurs (an IO error or there isn't room
 in the buffer for the result), MTD_FAIL is returned.

 The copying starts at index location "bufferOffset", in case the same
 buffer is to be used to copy multiple calls of this function. The
 function returns an updated index to the next available space if 
 there is still space available, or returns the total length of the
 buffer if the buffer is full.


 Side effects:
    None.

 Notes/Warnings:
    Note that dumpBufferLength is the number of characters remaining
    in the buffer calculated from bufferOffset to the end of the 
    buffer and not the total length of the dumpBuffer (unless 
    bufferOffset is 0).

    To calculate the total size of the char buffer needed, take 
    addrArrayLength * MTD_SIZEOF_OUTPUT.

    Example: To dump the C unit registers:
    MTD_STATUS result;
    char outputBuf[MTD_CUNIT_REG_DATA_SIZE*MTD_SIZEOF_OUTPUT];
    MTD_U16 startLocation = 0;

    result = mtdCopyRegsToBuf
               (devPtr,port, cUnitRegData, MTD_CUNIT_REG_DATA_SIZE,
                outputBuf, MTD_CUNIT_REG_DATA_SIZE*MTD_SIZEOF_OUTPUT,
                &startLocation);

    if (result == MTD_OK)
    {
        printf("%s",outputBuf);
    }
    else
    {
        printError("Some kind of error occurred.\n");
    }

    Note that mtdDiagnosticsRegDumpData.c contains lists of datasheet
    registers commonly used. Registers that contain latch high (LH)
    or latch low (LL) bits are included twice so the latch status can
    be seen.
    
******************************************************************************/
MTD_STATUS mtdCopyRegsToBuf
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port, 
    IN const MTD_MDIO_ADDR_TYPE addrArray[],
    IN MTD_U16 addrArrayLength,
    INOUT MTD_8 dumpBuffer[],
    IN MTD_U16 dumpBufferLength,
    INOUT MTD_U16 *bufferOffset
);

#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif


#endif

