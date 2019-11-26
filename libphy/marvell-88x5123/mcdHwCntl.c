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
This file contains functions and global data for
interfacing with the host's hardware-specific MDIO and general-purpose
IO in order to control and query the Marvell X5123/EC808 PHY.

These functions as written were tested with a USB-interface to
access Marvell's EVK. These functions must be ported to
the host's specific platform.
********************************************************************/
#include "mcdApiTypes.h"
#include "mcdApiRegs.h"
#include "mcdUtils.h"
#include "mcdHwCntl.h"
#include "mcdAPI.h"

#if DB_TEST_ENVIRONMENT
#include "Windows.h"
#include "WinError.h"
#include "tstSMIInterface.h"
#include "stdio.h"
const MCD_BOOL dumpIOToFile = MCD_FALSE; /* change to false to have it not dump all MDIO to a file */
FILE *fp;
#endif

//extern MCD_32 usleep(MCD_U32 usec);



/* flags for enabling trace of register and spico interrupt access  - see mcdSetRegAccessTraceOn*/
MCD_BOOL mcdTraceReadEn = MCD_FALSE;
MCD_BOOL mcdTraceWriteEn = MCD_FALSE;
MCD_BOOL mcdTraceSpicoInterruptTraceEn = MCD_FALSE;

/**
* @internal mcdSetRegAccessTraceOn function
* @endinternal
*
* @brief   Enable trace on register accessl
*
* @param[in] enableRead         -               trace register read
* @param[in] enableWrite         -               trace register write
* @param[in] enableSpicoInterruptTrace      trace Spico interrupt access
*
* @note trace print is independent of mcd_debug_level, does not trace register access done from FW
*/
MCD_VOID mcdSetRegAccessTraceOn
(
    IN MCD_BOOL enableRead,
    IN MCD_BOOL enableWrite,
    IN MCD_BOOL enableSpicoInterruptTrace
)
{
    mcdTraceReadEn = enableRead;
    mcdTraceWriteEn = enableWrite;
    mcdTraceSpicoInterruptTraceEn = enableSpicoInterruptTrace;

    printf("\nTrace Read Enabled: %d Trace Write Enabled: %d\n"
        "Spico Interrupt Trace Access Enabled: %d\n",
        mcdTraceReadEn, mcdTraceWriteEn, mcdTraceSpicoInterruptTraceEn);

    return;

}


/******************************************************************************
 MCD_CALC_MASK - This macro calculates the mask for partial read/write of
 register's data.
*******************************************************************************/
#define MCD_CALC_MASK(fieldOffset,fieldLen,mask)    \
            if((fieldLen + fieldOffset) >= 16)      \
                mask = (0 - (1 << fieldOffset));    \
            else                                    \
                mask = (((1 << (fieldLen + fieldOffset))) - (1 << fieldOffset))

/******************************************************************************
  PORT THESE FUNCTIONS
*******************************************************************************/
/******************************************************************************
 MCD_STATUS mcdHwXmdioWrite
*******************************************************************************/
MCD_STATUS mcdHwXmdioWrite
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 dev,
    IN MCD_U16 reg,
    IN MCD_U16 value
)
{
    MCD_STATUS result = MCD_OK;

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
    if (pDev->highAvailabilityMode)
    {
        return MCD_OK;
    }
#endif

    if (mdioPort > MCD_MAX_MDIO_NUM)
    {
        MCD_DBG_ERROR("mcdHwXmdioWrite: Invalid MDIO port number : %u\n", mdioPort);
        return MCD_FAIL;
    }

    if (pDev->fmcdWriteMdio != NULL)
    {
        if(pDev->fmcdWriteMdio(pDev, mdioPort, dev,reg, value) == MCD_FAIL)
        {
            result = MCD_FAIL;
            MCD_DBG_INFO("fmcdWriteMdio 0x%04X failed to mdioPort=%u, dev=%u, reg=0x%04X\n", (unsigned)(value),(unsigned)mdioPort,(unsigned)dev,(unsigned)reg);
        }
    }
    else
#if DB_TEST_ENVIRONMENT
    {
        MCD_U16 fpStatus;

        if (dumpIOToFile && (!fp))
        {
            if ((fpStatus = fopen_s(&fp, "mcdMdioLogfile.txt", "w")) != 0)
            {
                return MCD_FAIL; /* can't open log file */
            }
        }

        if (MdioWrite((unsigned long)mdioPort,
                      (unsigned long)dev,
                      (unsigned long)reg,
                      (unsigned short)value) < S_OK)
        {
            result = MCD_FAIL;
            MCD_DBG_INFO("MdioWrite 0x%04X failed to mdioPort=%u, dev=%u, reg=0x%04X\n", (unsigned)(value),(unsigned)mdioPort,(unsigned)dev,(unsigned)reg);
        }
        else
        {
            if (dumpIOToFile && fp)
            {
                fprintf(fp,"smdio_wr(%d,%d,'%04X','%04X')\n",(int)mdioPort,(int)dev,(unsigned)reg,(unsigned)value);
            }
        }
    }
#else
        result = MCD_FAIL;
#endif

    return result;
}


/******************************************************************************
 MCD_STATUS mcdHwXmdioRead
*******************************************************************************/
MCD_STATUS mcdHwXmdioRead
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 dev,
    IN MCD_U16 reg,
    OUT MCD_U16 *data
)
{
    MCD_STATUS result = MCD_OK;

#if DB_TEST_ENVIRONMENT
    HRESULT retCode;
#endif

    if (mdioPort > MCD_MAX_MDIO_NUM)
    {
        MCD_DBG_ERROR("mcdHwXmdioRead: Invalid MDIO port number : %u\n", mdioPort);
        return MCD_FAIL;
    }

    if (pDev->fmcdReadMdio != NULL)
    {
        if(pDev->fmcdReadMdio(pDev, mdioPort, dev,reg, data) == MCD_FAIL)
        {
            result = MCD_FAIL;
            MCD_DBG_INFO("fmcdReadMdio failed from mdioPort=%u, dev=%u, reg=0x%04X\n", (unsigned)mdioPort,(unsigned)dev,(unsigned)reg);
        }

    }
    else
#if DB_TEST_ENVIRONMENT
    {
        MCD_U16 fpStatus;

        if (dumpIOToFile && (!fp))
        {
            if ((fpStatus = fopen_s(&fp, "mcdMdioLogfile.txt", "w")) != 0)
            {
                return MCD_FAIL; /* can't open log file */
            }
        }

        *data = (MCD_U16)MdioRead((unsigned long)mdioPort,
                                  (unsigned long)dev,
                                  (unsigned long)reg,
                                  &retCode);
        if (retCode < S_OK)
        {
            result = MCD_FAIL;
            MCD_DBG_INFO("MdioRead failed from mdioPort=%u, dev=%u, reg=0x%04X\n", (unsigned)mdioPort,(unsigned)dev,(unsigned)reg);
        }
        else
        {
            if (dumpIOToFile && fp)
            {
                fprintf(fp,"smdio_rd(%d,%d,'%04X')=%04X\n",(int)mdioPort,(int)dev,(unsigned)reg,(unsigned)(*data));
            }

        }
    }
#else
        result = MCD_FAIL;
#endif

    return result;
}


/******************************************************************************
 MCD_STATUS mcdHwGetPhyRegField
*******************************************************************************/
MCD_STATUS mcdHwGetPhyRegField
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U16      mdioPort,
    IN  MCD_U16      dev,
    IN  MCD_U16      regAddr,
    IN  MCD_U8       fieldOffset,
    IN  MCD_U8       fieldLength,
    OUT MCD_U16      *data
)
{
    MCD_U16 tmpData;
    MCD_STATUS   retVal;

    retVal = mcdHwXmdioRead(pDev,mdioPort, dev, regAddr, &tmpData);

    if(retVal != MCD_OK)
    {
        MCD_DBG_ERROR("Failed to read register \n");
        return MCD_FAIL;
    }

    mcdHwGetRegFieldFromWord(tmpData,fieldOffset,fieldLength, data);

    /* MCD_DBG_INFO("fOff %d, fLen %d, data 0x%04X.\n",(int)fieldOffset,(int)fieldLength,(int)*data);  */

    return MCD_OK;
}


/******************************************************************************
 MCD_STATUS mcdHwSetPhyRegField
*******************************************************************************/
MCD_STATUS mcdHwSetPhyRegField
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16      mdioPort,
    IN MCD_U16      dev,
    IN MCD_U16      regAddr,
    IN MCD_U8       fieldOffset,
    IN MCD_U8       fieldLength,
    IN MCD_U16      data
)
{
    MCD_U16 tmpData,newData;
    MCD_STATUS   retVal;

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
    if (pDev->highAvailabilityMode)
    {
        return MCD_OK;
    }
#endif

    retVal = mcdHwXmdioRead(pDev,mdioPort, dev, regAddr, &tmpData);
    if(retVal != MCD_OK)
    {
        MCD_DBG_ERROR("Failed to read register \n");
        return MCD_FAIL;
    }

    mcdHwSetRegFieldToWord(tmpData,data,fieldOffset,fieldLength,&newData);

    retVal = mcdHwXmdioWrite(pDev,mdioPort, dev, regAddr, newData);

    if(retVal != MCD_OK)
    {
        MCD_DBG_ERROR("Failed to write register \n");
        return MCD_FAIL;
    }

    /* MCD_DBG_INFO("fieldOff %u, fieldLen %u, data 0x%x.\n",fieldOffset,\
                    fieldLength,data);  */

    return MCD_OK;
}


/******************************************************************************
 MCD_STATUS mcdHwGetRegFieldFromWord
*******************************************************************************/
MCD_STATUS mcdHwGetRegFieldFromWord
(
    IN  MCD_U16      regData,
    IN  MCD_U8       fieldOffset,
    IN  MCD_U8       fieldLength,
    OUT MCD_U16      *data
)
{
    MCD_U16 mask;            /* Bits mask to be read */

    MCD_CALC_MASK(fieldOffset,fieldLength,mask);

    *data = (regData & mask) >> fieldOffset;

    return MCD_OK;
}


/******************************************************************************
 MCD_STATUS mcdHwSetRegFieldToWord
*******************************************************************************/
MCD_STATUS mcdHwSetRegFieldToWord
(
    IN  MCD_U16      regData,
    IN  MCD_U16      bitFieldData,
    IN  MCD_U8       fieldOffset,
    IN  MCD_U8       fieldLength,
    OUT MCD_U16      *data
)
{
    MCD_U16 mask;            /* Bits mask to be read */

    MCD_CALC_MASK(fieldOffset,fieldLength,mask);

    /* Set the desired bits to 0.                       */
    regData &= ~mask;
    /* Set the given data into the above reset bits.    */
    regData |= ((bitFieldData << fieldOffset) & mask);

    *data = regData;

    return MCD_OK;
}


/******************************************************************************
 MCD_STATUS mcdWait
*******************************************************************************/
MCD_STATUS mcdWait
(
    IN MCD_DEV_PTR pDev,
    IN MCD_UINT x
)
{
#if DB_TEST_ENVIRONMENT
    Sleep(x);
    return MCD_OK;
#elif !defined(ASIC_SIMULATION)

    usleep(x*1000);
    return MCD_OK;
#else
   return MCD_FAIL;
#endif
}


#if 0
#if DB_TEST_ENVIRONMENT
/*****************************************************************************************
    The header file stdio.h needs to be included before compiling and using
    this function

    See the "Example" section of the function declarations of mcdUpdateFlashImage() and
    mcdMdioRamDownload() to understand how mcdOpenReadFile() can be used.
******************************************************************************************/
MCD_INT mcdOpenReadFile
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    INOUT FILE **pfp,
    IN MCD_8 *fname,
    OUT MCD_U8 *data,
    IN MCD_UINT max_data_size
)
{
    MCD_INT size;

    if ((*pfp = fopen(fname, "rb")) == (FILE *)0)
    {
        return 0; /* error */
    }

    size = (MCD_INT)fread(data, sizeof(char), max_data_size, *pfp);

    if (ferror(*pfp) || size == 0)
    {
        return 0; /* error */
    }
    else
    {
        MCD_DBG_INFO("Read from %s, %d bytes\n", fname, size);
    }
    return size;
}
#endif
#endif

/******************************************************************************
   32-BIT Access Support
******************************************************************************/

MCD_STATUS mcdHwXmdioWaitStatus
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16     reg,
    IN MCD_U16     mask,
    IN MCD_U32     timeout
)
{
    MCD_STATUS rc;
    MCD_U16    data;

    if (timeout == 0) return MCD_OK;
    for (/*none*/; (timeout > 0); timeout--)
    {
        rc = pDev->fmcdReadMdio(
            pDev, pDev->firstMdioPort/*mdioPort*/, reg/*mmd*/, (MCD_U16)0/*reg*/, &data);
        if (MCD_OK != rc) return rc;
        if ((data & mask) == mask) return MCD_OK;
    }
    return MCD_FAIL;
}

MCD_STATUS mcdHwXmdioWait32bitWrite
(
    IN MCD_DEV_PTR pDev
)
{
    return mcdHwXmdioWaitStatus(
        pDev,
        MCD_SMI_STATUS_REGISTER,
        MCD_SMI_STATUS_READ_READY,
        MCD_SMI_TIMEOUT_COUNTER);
}

MCD_STATUS mcdHwXmdioWait32bitRead
(
    IN MCD_DEV_PTR pDev
)
{
    return mcdHwXmdioWaitStatus(
        pDev,
        MCD_SMI_STATUS_REGISTER,
        MCD_SMI_STATUS_WRITE_DONE,
        MCD_SMI_TIMEOUT_COUNTER);
}

/* SSMI control registers shadow */
#define PRV_MCD_PHY_SHADOW_NUM_OF 16
static const MCD_U16 prvMcdPhyShadowRegIndex[] =
{
    /*0 - same as 4 */ 0, /*1 - same as 5*/ 0xFFFF, /*2*/ 0xFFFF, /*3*/ 0xFFFF,
    /*4 - same as 0 */ 0, /*5 - same as 1*/ 0xFFFF,
    /*6*/ 0xFFFF, /*7*/ 0xFFFF, /*8*/ 0xFFFF, /*9*/ 0xFFFF, /*10*/ 1
};

#define PRV_MCD_PHY_SHADOW_REG_MAX_REGISTER \
    (sizeof(prvMcdPhyShadowRegIndex) / sizeof(prvMcdPhyShadowRegIndex[0]))

#define PRV_MCD_PHY_SHADOW_REG_INDEX(_reg) \
    ((_reg >= PRV_MCD_PHY_SHADOW_REG_MAX_REGISTER) ? 0xFFFF : prvMcdPhyShadowRegIndex[_reg])

/* returns 1 if needed value found, otherwize - 0     */
/* if register has shadow checked valus set to shadow */
MCD_U16 prvMcdPhyShadowRegCheckAndSet
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16     reg,
    IN MCD_U16     value
)
{
    MCD_U16                      reg_index;

    reg_index = PRV_MCD_PHY_SHADOW_REG_INDEX(reg);
    if (reg_index == 0xFFFF) return 0; /* register has no shadow */
    /* check shadow */
    if (((pDev->shadowValidBmp & (1 << reg_index)) != 0)
        && (pDev->regShadow[reg_index] == value)) return 1;
    /* set shadow */
    pDev->shadowValidBmp |= (1 << reg_index);
    pDev->regShadow[reg_index] = value;

    return 0;
}

void prvMcdPhyShadowRegInvalidate
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16     reg
)
{
    MCD_U16                      reg_index;

    reg_index = PRV_MCD_PHY_SHADOW_REG_INDEX(reg);
    if (reg_index == 0xFFFF) return; /* register has no shadow */
    pDev->shadowValidBmp &= (~ (1 << reg_index));
}

MCD_STATUS prvMcdPhyShadowWrite16BitRegister
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16     mdioPort,
    IN MCD_U16     reg,
    IN MCD_U16     value
)
{
    MCD_STATUS rc;

    if (prvMcdPhyShadowRegCheckAndSet(
        pDev, reg, value)) return MCD_OK;
    rc = pDev->fmcdWriteMdio(
        pDev, pDev->firstMdioPort, reg/*mmd*/, (MCD_U16)0/*reg*/, value);
    if (rc != MCD_OK) prvMcdPhyShadowRegInvalidate(pDev, reg);
    return rc;
}

/******************************************************************************
 MCD_STATUS mcdHwXmdioAccessInit32bit
*******************************************************************************/
MCD_STATUS mcdHwXmdioAccessInit32bit
(
    IN MCD_DEV_PTR pDev
)
{
    MCD_STATUS rc;

    /* initialize Slave SMI controller registers shadows */
    /* after it Read/Write for internal registers ready  */
    pDev->shadowValidBmp = 0;

    /* configure SMI=>XBAR remap mechanism: declare XBAR ports 3 and 8 external */
    /* after it SMI Read/Write for external registers also ready                    */
    rc = mcdHwXmdioWrite32bit(
        pDev, 0/*mdioPort*/, 0x0001310C/*reg*/, 0x00010000/*value*/);
    if (rc != MCD_OK) return rc;
    rc = mcdHwXmdioWrite32bit(
        pDev, 0/*mdioPort*/, 0x00013120/*reg*/, 0x00010000/*value*/);
    if (rc != MCD_OK) return rc;

    /* configure TWSI (I2C) =>XBAR remap mechanism: declare XBAR ports 3 and 8 external */
    /* after it TWSI (I2C) Read/Write for external registers also ready                 */
    rc = mcdHwXmdioWrite32bit(
        pDev, 0/*mdioPort*/, 0x0001320C/*reg*/, 0x00010000/*value*/);
    if (rc != MCD_OK) return rc;
    rc = mcdHwXmdioWrite32bit(
        pDev, 0/*mdioPort*/, 0x00013220/*reg*/, 0x00010000/*value*/);
    if (rc != MCD_OK) return rc;

    return MCD_OK;
}

/* returns 1 - external, 0 - internal */
MCD_U16 prvMcdIs32bitAddressExternal
(
    IN MCD_U32     reg
)
{
    /* 0 - 0x2FFFFFFF */
    if (reg < 0x30000000) return 0;
    /* 0x30000000 - 0x33FFFFFF */
    if (reg < 0x34000000) return 1;
    /* 0x80000000 - 0x80FFFFFF */
    if ((reg >= 0x80000000) && (reg <= 0x80FFFFFF)) return 1;
    /* 0xA0000000 - 0xA00FFFFF */
    if ((reg >= 0xA0000000) && (reg <= 0xA00FFFFF)) return 1;
    return 0;
}

/* returns fixed register address to be recognized by XBAR as external if needed */
MCD_U32 prvMcd32bitAddressExternalFixed
(
    IN MCD_U32     reg
)
{
    return (prvMcdIs32bitAddressExternal(reg) ? (reg | 2) : reg);
}


/******************************************************************************
 MCD_STATUS mcdHwXmdioWrite32bit
*******************************************************************************/
MCD_STATUS mcdHwXmdioWrite32bit
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U32     mdioPort,
    IN MCD_U32     reg,
    IN MCD_U32     value
)
{
    MCD_STATUS rc;

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
    if (pDev->highAvailabilityMode)
    {
        return MCD_OK;
    }
#endif

    if (reg & 3)
    {
        MCD_DBG_ERROR(
            "mcdHwXmdioWrite32bit: Wrong Register 0x%08X, Data 0x%08X\n",
            reg, value);
        return MCD_FAIL;
    }

    MCD_DBG_INFO("mcdHwXmdioWrite32bit: MDIO Port[%d], Register 0x%08X, Data 0x%08X\n", pDev->firstMdioPort, reg, value);
    if(mcdTraceWriteEn)
        printf("\nwrote to register: 0x%08X data: 0x%08X\n", reg, value);

    rc = mcdHwXmdioWait32bitWrite(pDev);
    if (rc != MCD_OK) return rc;

    reg = prvMcd32bitAddressExternalFixed(reg);

    rc = prvMcdPhyShadowWrite16BitRegister(
        pDev, (MCD_U16)mdioPort,
        MCD_SMI_CONFIGURATION_REGISTER,
        MCD_SMI_CONFIGURATION_WRITE_BY_ADDRESS);
    if (rc != MCD_OK) return rc;

    rc = prvMcdPhyShadowWrite16BitRegister(
        pDev, (MCD_U16)mdioPort,
        MCD_SMI_WRITE_ADDRESS_MSB_REGISTER, (MCD_U16)(reg >> 16));
    if (rc != MCD_OK) return rc;

    rc = prvMcdPhyShadowWrite16BitRegister(
        pDev, (MCD_U16)mdioPort,
        MCD_SMI_WRITE_ADDRESS_LSB_REGISTER, (MCD_U16)(reg & 0xFFFF));
    if (rc != MCD_OK) return rc;

    rc = prvMcdPhyShadowWrite16BitRegister(
        pDev, (MCD_U16)mdioPort,
        MCD_SMI_WRITE_DATA_MSB_REGISTER, (MCD_U16)(value >> 16));
    if (rc != MCD_OK) return rc;

    /* write to DEVADD (MMD) = 9 triggers indirect write transaction */
    rc = pDev->fmcdWriteMdio(
        pDev, pDev->firstMdioPort, MCD_SMI_WRITE_DATA_LSB_REGISTER/*mmd*/,
        (MCD_U16)0/*reg*/, (MCD_U16)(value & 0xFFFF));
    if (rc != MCD_OK) return rc;

    return MCD_OK;
}

/******************************************************************************
 MCD_STATUS mcdHwXmdioRead32bit
*******************************************************************************/
MCD_STATUS mcdHwXmdioRead32bit
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U32     mdioPort,
    IN  MCD_U32     reg,
    OUT MCD_U32     *data
)
{
    MCD_STATUS rc;
    MCD_U16     low, high;
    MCD_U32     regAddrForAccess; /* address of register for HW access */

    if (reg & 3)
    {
        MCD_DBG_ERROR(
            "mcdHwXmdioRead32bit: Wrong Register 0x%08X \n",reg);
        return MCD_FAIL;
    }

    rc = mcdHwXmdioWait32bitRead(pDev);
    if (rc != MCD_OK) return rc;

    regAddrForAccess = prvMcd32bitAddressExternalFixed(reg);

    rc = prvMcdPhyShadowWrite16BitRegister(
        pDev, (MCD_U16)mdioPort,
        MCD_SMI_READ_ADDRESS_MSB_REGISTER, (MCD_U16)(regAddrForAccess >> 16));
    if (rc != MCD_OK) return rc;

    /* write to DEVADD (MMD) = 5 triggers indirect read transaction */
    rc = pDev->fmcdWriteMdio(
        pDev, pDev->firstMdioPort, MCD_SMI_READ_ADDRESS_LSB_REGISTER/*mmd*/,
        (MCD_U16)0/*reg*/, (MCD_U16)(regAddrForAccess & 0xFFFF));
    if (rc != MCD_OK) return rc;

    rc = pDev->fmcdReadMdio(
        pDev, pDev->firstMdioPort, MCD_SMI_READ_DATA_MSB_REGISTER/*mmd*/,
        (MCD_U16)0/*reg*/, &high);
    if (rc != MCD_OK) return rc;

    rc = pDev->fmcdReadMdio(
        pDev, pDev->firstMdioPort, MCD_SMI_READ_DATA_LSB_REGISTER/*mmd*/,
        (MCD_U16)0/*reg*/, &low);
    if (rc != MCD_OK) return rc;

    *data = (((MCD_U32)high << 16) | (MCD_U32)low);

    if(mcdTraceReadEn)
        printf("\nread from register: 0x%08X data: 0x%08X\n", reg, *data);

    MCD_DBG_INFO("mcdHwXmdioRead32bit: MDIO Port[%d], Register 0x%08X, Data 0x%08X\n", pDev->firstMdioPort, reg, *data);
    return MCD_OK;
}

/******************************************************************************
 MCD_STATUS mcdHwSetPhyRegField32bit
*******************************************************************************/
MCD_STATUS mcdHwSetPhyRegField32bit
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U32     mdioPort,
    IN MCD_U32     reg,
    IN MCD_U32     offset,
    IN MCD_U32     length,
    IN MCD_U32     value
)
{
    MCD_U32    data;
    MCD_U32    mask;
    MCD_STATUS rc;

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
    if (pDev->highAvailabilityMode)
    {
        return MCD_OK;
    }
#endif

    if ((offset + length) > 32) return MCD_FAIL;

    if ((offset == 0) && (length == 32))
    {
        data = value;
    }
    else
    {
        rc = mcdHwXmdioRead32bit(
            pDev, mdioPort, reg, &data);
        if (rc != MCD_OK) return rc;
        mask  = (((1 << length) - 1) << offset);
        data &= (~ mask);
        data |= (mask & (value << offset));
    }
    return mcdHwXmdioWrite32bit(
        pDev, mdioPort, reg, data);
}

/******************************************************************************
 MCD_STATUS mcdHwGetPhyRegField32bit
*******************************************************************************/
MCD_STATUS mcdHwGetPhyRegField32bit
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U32     mdioPort,
    IN  MCD_U32     reg,
    IN  MCD_U32     offset,
    IN  MCD_U32     length,
    OUT MCD_U32     *value
)
{
    MCD_U32    data;
    MCD_U32    mask;
    MCD_STATUS rc;

    if ((offset + length) > 32) return MCD_FAIL;

    rc = mcdHwXmdioRead32bit(
        pDev, mdioPort, reg, &data);
    if (rc != MCD_OK) return rc;

    if ((offset == 0) && (length == 32))
    {
        *value = data;
    }
    else
    {
        mask  = ((1 << length) - 1);
        *value = ((data >> offset) & mask);
    }
    return MCD_OK;
}

/******************************************************************************
 MCD_STATUS mcdHwSetPhyRegField32bit
*******************************************************************************/
MCD_STATUS mcdHwSetPhyRegMask32bit
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U32     mdioPort,
    IN MCD_U32     reg,
    IN MCD_U32     mask,
    IN MCD_U32     value
)
{
    MCD_U32    data;
    MCD_STATUS rc;

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
    if (pDev->highAvailabilityMode)
    {
        return MCD_OK;
    }
#endif

    if (mask == 0) return MCD_OK;

    rc = mcdHwXmdioRead32bit(
        pDev, mdioPort, reg, &data);
    if (rc != MCD_OK) return rc;

    data &= (~ mask);
    data |= (mask & value);
    return mcdHwXmdioWrite32bit(
        pDev, mdioPort, reg, data);
}

/******************************************************************************
 MCD_STATUS mcdHwGetPhyRegField32bit
*******************************************************************************/
MCD_STATUS mcdHwGetPhyRegMask32bit
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U32     mdioPort,
    IN  MCD_U32     reg,
    IN  MCD_U32     mask,
    OUT MCD_U32     *value
)
{
    MCD_U32    data;
    MCD_STATUS rc;

    *value = 0;
    if (mask == 0) return MCD_OK;

    rc = mcdHwXmdioRead32bit(
        pDev, mdioPort, reg, &data);
    if (rc != MCD_OK) return rc;

    *value = (data & mask);
    return MCD_OK;
}

/******************************************************************************
 MCD_STATUS mcdHwXmdioWaitStatus32Bit
*******************************************************************************/
MCD_STATUS mcdHwXmdioWaitStatus32Bit
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U32     mdioPort,
    IN MCD_U32     reg,
    IN MCD_U32     mask,
    IN MCD_U32     pattern,
    IN MCD_U32     timeout
)
{
    MCD_STATUS rc;
    MCD_U32    data;

    if (timeout == 0) return MCD_OK;
    for (/*none*/; (timeout > 0); timeout--)
    {
        rc = mcdHwXmdioRead32bit(pDev, mdioPort, reg, &data);
        if (MCD_OK != rc) return rc;
        if ((data & mask) == pattern) return MCD_OK;
    }
    return MCD_FAIL;
}



