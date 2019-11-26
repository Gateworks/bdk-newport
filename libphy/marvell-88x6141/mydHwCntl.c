/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions and global data for
interfacing with the host's hardware-specific MDIO and general-purpose
IO in order to control and query the Marvell X7120/X6181/X6141 PHY.

These functions as written were tested with a USB-interface to
access Marvell's EVK. These functions must be ported to 
the host's specific platform.
********************************************************************/
#include <bdk.h>
#include "mydApiTypes.h"
#include "mydApiRegs.h"
#include "mydUtils.h"
#include "mydHwCntl.h"
#include "mydAPI.h"

#if DB_TEST_ENVIRONMENT
#include "Windows.h"
#include "tstSMIInterface.h"  
#include "stdio.h"
static const MYD_BOOL dumpIOToFile = MYD_FALSE; /* change to false to have it not dump all MDIO to a file */
FILE *fp;
#endif


/******************************************************************************
 MYD_CALC_MASK - This macro calculates the mask for partial read/write of 
 register's data.
*******************************************************************************/
#define MYD_CALC_MASK(fieldOffset,fieldLen,mask)    \
            if((fieldLen + fieldOffset) >= 16)      \
                mask = (0 - (1 << fieldOffset));    \
            else                                    \
                mask = (((1 << (fieldLen + fieldOffset))) - (1 << fieldOffset))


/******************************************************************************
  PORT THESE FUNCTIONS
*******************************************************************************/
/******************************************************************************
 MYD_STATUS mydHwXmdioWrite
*******************************************************************************/
MYD_STATUS mydHwXmdioWrite
( 
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort, 
    IN MYD_U16 dev, 
    IN MYD_U16 reg, 
    IN MYD_U16 value
)
{
    MYD_STATUS result = MYD_OK;

    if (mdioPort > MYD_MAX_MDIO_NUM)
    {
        MYD_DBG_ERROR("mydHwXmdioWrite: Invalid MDIO port number : %u\n", mdioPort);
        return MYD_FAIL;
    }

    if (pDev->fmydWriteMdio != NULL)
    {
        if(pDev->fmydWriteMdio(pDev, mdioPort, dev, reg, value) == MYD_FAIL)
        {
            result = MYD_FAIL;
            MYD_DBG_ERROR("fmydWriteMdio 0x%04X failed to mdioPort=%u, dev=%u, reg=0x%04X\n", (unsigned)(value),(unsigned)mdioPort,(unsigned)dev,(unsigned)reg);
        }        
    }
    else
#if DB_TEST_ENVIRONMENT
    {
        MYD_U16 fpStatus;

        if (dumpIOToFile && (!fp))
        {
            if ((fpStatus = (MYD_U16)fopen_s(&fp, "mydMdioLogfile.txt", "w")) != 0)
            {
                return MYD_FAIL; /* can't open log file */
            }
        }
#ifdef MYD_PY_DEBUG
        if (mydMdioWrite(pDev,
                         (unsigned long)mdioPort,
                         (unsigned long)dev, 
                         (unsigned long)reg, 
                         (unsigned short)value) < S_OK)
#else
        if (mydMdioWrite((unsigned long)mdioPort,
                         (unsigned long)dev, 
                         (unsigned long)reg, 
                         (unsigned short)value) < S_OK)
#endif
        {
            result = MYD_FAIL;
            MYD_DBG_ERROR("MdioWrite 0x%04X failed to mdioPort=%u, dev=%u, reg=0x%04X\n", (unsigned)(value),(unsigned)mdioPort,(unsigned)dev,(unsigned)reg);
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
        result = MYD_FAIL;
#endif 

#if 0 /* debug logging for MDIO write */
    MYD_DBG_INFO("xrw smi_u4 d%d p%d r%04X h%04X \n", 
                 (unsigned)dev,(unsigned)mdioPort,(unsigned)reg, (unsigned)value);
#endif
    
    return result;
}


/******************************************************************************
 MYD_STATUS mydHwXmdioRead
*******************************************************************************/
MYD_STATUS mydHwXmdioRead
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort, 
    IN MYD_U16 dev, 
    IN MYD_U16 reg,
    OUT MYD_U16 *data
)
{    
    MYD_STATUS result = MYD_OK;

#if DB_TEST_ENVIRONMENT
    HRESULT retCode;
#endif

    if (mdioPort > MYD_MAX_MDIO_NUM)
    {
        MYD_DBG_ERROR("mydHwXmdioRead: Invalid MDIO port number : %u\n", mdioPort);
        return MYD_FAIL;
    }

    if (pDev->fmydReadMdio != NULL)
    {
        if(pDev->fmydReadMdio(pDev, mdioPort, dev, reg, data) == MYD_FAIL)
        {
            result = MYD_FAIL;
            MYD_DBG_ERROR("fmydReadMdio failed from mdioPort=%u, dev=%u, reg=0x%04X\n", (unsigned)mdioPort,(unsigned)dev,(unsigned)reg);            
        }
        
    }
    else
#if DB_TEST_ENVIRONMENT
    {
        MYD_U16 fpStatus;

        if (dumpIOToFile && (!fp))
        {
            if ((fpStatus = (MYD_U16)fopen_s(&fp, "mydMdioLogfile.txt", "w")) != 0)
            {
                return MYD_FAIL; /* can't open log file */
            }
        }
#ifdef MYD_PY_DEBUG
        *data = (MYD_U16)mydMdioRead(pDev,
                                     (unsigned long)mdioPort,
                                     (unsigned long)dev,
                                     (unsigned long)reg,
                                     &retCode);
#else
        *data = (MYD_U16)mydMdioRead((unsigned long)mdioPort,
                                     (unsigned long)dev,
                                     (unsigned long)reg,
                                     &retCode);
#endif
        if (retCode < S_OK)
        {
            result = MYD_FAIL;
            MYD_DBG_ERROR("MdioRead failed from mdioPort=%u, dev=%u, reg=0x%04X\n", (unsigned)mdioPort,(unsigned)dev,(unsigned)reg);
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
        result = MYD_FAIL;
#endif 

    return result;
}


/******************************************************************************
 MYD_STATUS mydHwGetPhyRegField
*******************************************************************************/
MYD_STATUS mydHwGetPhyRegField
(
    IN  MYD_DEV_PTR pDev,
    IN  MYD_U16      mdioPort, 
    IN  MYD_U16      dev, 
    IN  MYD_U16      regAddr,
    IN  MYD_U8       fieldOffset,
    IN  MYD_U8       fieldLength,
    OUT MYD_U16      *data
)
{
    MYD_U16 tmpData;
    MYD_STATUS   retVal;

    retVal = mydHwXmdioRead(pDev, mdioPort, dev, regAddr, &tmpData);

    if(retVal != MYD_OK)
    {
        MYD_DBG_ERROR("Failed to read register \n");
        return MYD_FAIL;
    }
    
    mydHwGetRegFieldFromWord(tmpData, fieldOffset, fieldLength, data);

    /* MYD_DBG_INFO("fOff %d, fLen %d, data 0x%04X.\n",(int)fieldOffset,(int)fieldLength,(int)*data);  */

    return MYD_OK;
}


/******************************************************************************
 MYD_STATUS mydHwSetPhyRegField
*******************************************************************************/
MYD_STATUS mydHwSetPhyRegField
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16      mdioPort, 
    IN MYD_U16      dev, 
    IN MYD_U16      regAddr,
    IN MYD_U8       fieldOffset,
    IN MYD_U8       fieldLength,
    IN MYD_U16      data
)
{
    MYD_U16 tmpData,newData;
    MYD_STATUS   retVal;

    retVal = mydHwXmdioRead(pDev, mdioPort, dev, regAddr, &tmpData);
    if(retVal != MYD_OK)
    {
        MYD_DBG_ERROR("Failed to read register \n");
        return MYD_FAIL;
    }

    mydHwSetRegFieldToWord(tmpData, data, fieldOffset, fieldLength, &newData);

    retVal = mydHwXmdioWrite(pDev, mdioPort, dev, regAddr, newData);

    if(retVal != MYD_OK)
    {
        MYD_DBG_ERROR("Failed to write register \n");
        return MYD_FAIL;
    }

    /* MYD_DBG_INFO("fieldOff %u, fieldLen %u, data 0x%x.\n",fieldOffset,\
                    fieldLength,data);  */

    return MYD_OK;
}


/******************************************************************************
 MYD_STATUS mydHwGetRegFieldFromWord
*******************************************************************************/
MYD_STATUS mydHwGetRegFieldFromWord
(
    IN  MYD_U16      regData,
    IN  MYD_U8       fieldOffset,
    IN  MYD_U8       fieldLength,
    OUT MYD_U16      *data
)
{
    MYD_U16 mask;            /* Bits mask to be read */

    MYD_CALC_MASK(fieldOffset,fieldLength,mask);

    *data = (regData & mask) >> fieldOffset;

    return MYD_OK;
}


/******************************************************************************
 MYD_STATUS mydHwSetRegFieldToWord
*******************************************************************************/
MYD_STATUS mydHwSetRegFieldToWord
(
    IN  MYD_U16      regData,
    IN  MYD_U16      bitFieldData,
    IN  MYD_U8       fieldOffset,
    IN  MYD_U8       fieldLength,
    OUT MYD_U16      *data
)
{
    MYD_U16 mask;            /* Bits mask to be read */

    MYD_CALC_MASK(fieldOffset, fieldLength, mask);

    /* Set the desired bits to 0.                       */
    regData &= ~mask;
    /* Set the given data into the above reset bits.    */
    regData |= ((bitFieldData << fieldOffset) & mask);

    *data = regData;

    return MYD_OK;
}


/******************************************************************************
 MYD_STATUS mydWait
    The function is platform dependent. It requires to be ported to supported platform.
    Waits waitTime milliseconds
*******************************************************************************/
MYD_STATUS mydWait
(
    IN MYD_DEV_PTR pDev,
    IN MYD_UINT waitTime
)
{
    bdk_wait_usec(waitTime * 1000);
    return MYD_OK;
}

