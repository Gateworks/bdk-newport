/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions and global data for
interfacing with the host's hardware-specific MDIO and general-purpose
IO in order to control and query the Marvell X5113 PHY.

These functions as written were tested with a USB-interface to
access Marvell's EVK. These functions must be ported to 
the host's specific platform.
********************************************************************/
#include "mxdApiTypes.h"
#include "mxdApiRegs.h"
#include "mxdUtils.h"
#include "mxdHwCntl.h"
#include "mxdAPI.h"

#if DB_TEST_ENVIRONMENT
#include "Windows.h"
#include "WinError.h"
#include "tstSMIInterface.h"  
#include "stdio.h"
static const MXD_BOOL dumpIOToFile = MXD_FALSE; /* change to false to have it not dump all MDIO to a file */
FILE *fp;
#endif


/******************************************************************************
 MXD_CALC_MASK - This macro calculates the mask for partial read/write of 
 register's data.
*******************************************************************************/
#define MXD_CALC_MASK(fieldOffset,fieldLen,mask)    \
            if((fieldLen + fieldOffset) >= 16)      \
                mask = (0 - (1 << fieldOffset));    \
            else                                    \
                mask = (((1 << (fieldLen + fieldOffset))) - (1 << fieldOffset))


/******************************************************************************
  PORT THESE FUNCTIONS
*******************************************************************************/
/******************************************************************************
 MXD_STATUS mxdHwXmdioWrite
*******************************************************************************/
MXD_STATUS mxdHwXmdioWrite
( 
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort, 
    IN MXD_U16 dev, 
    IN MXD_U16 reg, 
    IN MXD_U16 value
)
{
    MXD_STATUS result = MXD_OK;

    if (mdioPort > MXD_MAX_MDIO_NUM)
    {
        MXD_DBG_ERROR("mxdHwXmdioWrite: Invalid MDIO port number : %u\n", mdioPort);
        return MXD_FAIL;
    }

    if (pDev->fmxdWriteMdio != NULL)
    {
        if(pDev->fmxdWriteMdio(pDev, mdioPort, dev, reg, value) == MXD_FAIL)
        {
            result = MXD_FAIL;
            MXD_DBG_ERROR("fmxdWriteMdio 0x%04X failed to mdioPort=%u, dev=%u, reg=0x%04X\n", (unsigned)(value),(unsigned)mdioPort,(unsigned)dev,(unsigned)reg);
        }        
    }
    else
#if DB_TEST_ENVIRONMENT
    {
        MXD_U16 fpStatus;

        if (dumpIOToFile && (!fp))
        {
            if ((fpStatus = (MXD_U16)fopen_s(&fp, "mxdMdioLogfile.txt", "w")) != 0)
            {
                return MXD_FAIL; /* can't open log file */
            }
        }
#ifdef MXD_PY_DEBUG
        if (mxdMdioWrite(pDev,
                         (unsigned long)mdioPort,
                         (unsigned long)dev, 
                         (unsigned long)reg, 
                         (unsigned short)value) < S_OK)
#else
        if (mxdMdioWrite((unsigned long)mdioPort,
                         (unsigned long)dev, 
                         (unsigned long)reg, 
                         (unsigned short)value) < S_OK)
#endif
        {
            result = MXD_FAIL;
            MXD_DBG_INFO("MdioWrite 0x%04X failed to mdioPort=%u, dev=%u, reg=0x%04X\n", (unsigned)(value),(unsigned)mdioPort,(unsigned)dev,(unsigned)reg);
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
        result = MXD_FAIL;
#endif 

#if 0 /* debug logging for MDIO write */
    MXD_DBG_INFO("MdioWrite to mdioPort=%u, dev=%u, reg=0x%04X value=0x%04X \n",
                 (unsigned)mdioPort,(unsigned)dev,(unsigned)reg,(unsigned)(value));
#endif

    return result;
}


/******************************************************************************
 MXD_STATUS mxdHwXmdioRead
*******************************************************************************/
MXD_STATUS mxdHwXmdioRead
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort, 
    IN MXD_U16 dev, 
    IN MXD_U16 reg,
    OUT MXD_U16 *data
)
{    
    MXD_STATUS result = MXD_OK;

#if DB_TEST_ENVIRONMENT
    HRESULT retCode;
#endif

    if (mdioPort > MXD_MAX_MDIO_NUM)
    {
        MXD_DBG_ERROR("mxdHwXmdioRead: Invalid MDIO port number : %u\n", mdioPort);
        return MXD_FAIL;
    }

    if (pDev->fmxdReadMdio != NULL)
    {
        if(pDev->fmxdReadMdio(pDev, mdioPort, dev, reg, data) == MXD_FAIL)
        {
            result = MXD_FAIL;
            MXD_DBG_ERROR("fmxdReadMdio failed from mdioPort=%u, dev=%u, reg=0x%04X\n", (unsigned)mdioPort,(unsigned)dev,(unsigned)reg);            
        }
        
    }
    else
#if DB_TEST_ENVIRONMENT
    {
        MXD_U16 fpStatus;

        if (dumpIOToFile && (!fp))
        {
            if ((fpStatus = (MXD_U16)fopen_s(&fp, "mxdMdioLogfile.txt", "w")) != 0)
            {
                return MXD_FAIL; /* can't open log file */
            }
        }
#ifdef MXD_PY_DEBUG
        *data = (MXD_U16)mxdMdioRead(pDev,
                                     (unsigned long)mdioPort,
                                     (unsigned long)dev,
                                     (unsigned long)reg,
                                     &retCode);
#else
        *data = (MXD_U16)mxdMdioRead((unsigned long)mdioPort,
                                     (unsigned long)dev,
                                     (unsigned long)reg,
                                     &retCode);
#endif
        if (retCode < S_OK)
        {
            result = MXD_FAIL;
            MXD_DBG_INFO("MdioRead failed from mdioPort=%u, dev=%u, reg=0x%04X\n", (unsigned)mdioPort,(unsigned)dev,(unsigned)reg);
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
        result = MXD_FAIL;
#endif 

    return result;
}


/******************************************************************************
 MXD_STATUS mxdHwGetPhyRegField
*******************************************************************************/
MXD_STATUS mxdHwGetPhyRegField
(
    IN  MXD_DEV_PTR pDev,
    IN  MXD_U16      mdioPort, 
    IN  MXD_U16      dev, 
    IN  MXD_U16      regAddr,
    IN  MXD_U8       fieldOffset,
    IN  MXD_U8       fieldLength,
    OUT MXD_U16      *data
)
{
    MXD_U16 tmpData;
    MXD_STATUS   retVal;

    retVal = mxdHwXmdioRead(pDev, mdioPort, dev, regAddr, &tmpData);

    if(retVal != MXD_OK)
    {
        MXD_DBG_ERROR("Failed to read register \n");
        return MXD_FAIL;
    }
    
    mxdHwGetRegFieldFromWord(tmpData, fieldOffset, fieldLength, data);

    /* MXD_DBG_INFO("fOff %d, fLen %d, data 0x%04X.\n",(int)fieldOffset,(int)fieldLength,(int)*data);  */

    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdHwSetPhyRegField
*******************************************************************************/
MXD_STATUS mxdHwSetPhyRegField
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16      mdioPort, 
    IN MXD_U16      dev, 
    IN MXD_U16      regAddr,
    IN MXD_U8       fieldOffset,
    IN MXD_U8       fieldLength,
    IN MXD_U16      data
)
{
    MXD_U16 tmpData,newData;
    MXD_STATUS   retVal;

    retVal = mxdHwXmdioRead(pDev, mdioPort, dev, regAddr, &tmpData);
    if(retVal != MXD_OK)
    {
        MXD_DBG_ERROR("Failed to read register \n");
        return MXD_FAIL;
    }

    mxdHwSetRegFieldToWord(tmpData, data, fieldOffset, fieldLength, &newData);

    retVal = mxdHwXmdioWrite(pDev, mdioPort, dev, regAddr, newData);

    if(retVal != MXD_OK)
    {
        MXD_DBG_ERROR("Failed to write register \n");
        return MXD_FAIL;
    }

    /* MXD_DBG_INFO("fieldOff %u, fieldLen %u, data 0x%x.\n",fieldOffset,\
                    fieldLength,data);  */

    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdHwGetRegFieldFromWord
*******************************************************************************/
MXD_STATUS mxdHwGetRegFieldFromWord
(
    IN  MXD_U16      regData,
    IN  MXD_U8       fieldOffset,
    IN  MXD_U8       fieldLength,
    OUT MXD_U16      *data
)
{
    MXD_U16 mask;            /* Bits mask to be read */

    MXD_CALC_MASK(fieldOffset,fieldLength,mask);

    *data = (regData & mask) >> fieldOffset;

    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdHwSetRegFieldToWord
*******************************************************************************/
MXD_STATUS mxdHwSetRegFieldToWord
(
    IN  MXD_U16      regData,
    IN  MXD_U16      bitFieldData,
    IN  MXD_U8       fieldOffset,
    IN  MXD_U8       fieldLength,
    OUT MXD_U16      *data
)
{
    MXD_U16 mask;            /* Bits mask to be read */

    MXD_CALC_MASK(fieldOffset, fieldLength, mask);

    /* Set the desired bits to 0.                       */
    regData &= ~mask;
    /* Set the given data into the above reset bits.    */
    regData |= ((bitFieldData << fieldOffset) & mask);

    *data = regData;

    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdWait
*******************************************************************************/
MXD_STATUS mxdWait
(
    IN MXD_DEV_PTR pDev,
    IN MXD_UINT x
)
{
#if DB_TEST_ENVIRONMENT            
    Sleep(x);
    return MXD_OK;
#else
    /* OcteonTX BDK */
    extern void bdk_wait_usec(MXD_U64 usec);
    bdk_wait_usec(1000ull * x);
    return MXD_OK;
#endif
}


#if 0
#if DB_TEST_ENVIRONMENT
/***************************************************************************************** 
    The header file stdio.h needs to be included before compiling and using 
    this function

    See the "Example" section of the function declarations of mxdUpdateEEPROMImage() and 
    mxdMdioRamDownload() to understand how mxdOpenReadFile() can be used.
******************************************************************************************/
MXD_INT mxdOpenReadFile
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    INOUT FILE **pfp, 
    IN MXD_8 *fname, 
    OUT MXD_U8 *data,
    IN MXD_UINT max_data_size
)
{
    MXD_INT size;
 
    if ((*pfp = fopen(fname, "rb")) == (FILE *)0)
    {
        return 0; /* error */
    }
            
    size = (MXD_INT)fread(data, sizeof(char), max_data_size, *pfp);

    if (ferror(*pfp) || size == 0)
    {
        return 0; /* error */
    }
    else
    {
        MXD_DBG_INFO("Read from %s, %d bytes\n", fname, size);
    }
    return size;
}
#endif
#endif

