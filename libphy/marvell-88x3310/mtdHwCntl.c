/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions and global data for
interfacing with the host's hardware-specific MDIO and general-purpose
IO in order to control and query the Marvell 88X32X0, 88X33X0, 
88E20X0 and 88E21X0 ethernet PHYs.

These functions as written were tested with a USB-interface to
access Marvell's EVK. These functions must be ported to 
the host's specific platform.
********************************************************************/
#include <bdk.h>
#include "mtdApiTypes.h"
#include "mtdHwCntl.h"
#include "mtdAPI.h"


#if DB_TEST_ENVIRONMENT
#if 0
#include <stdio.h>
#include <windows.h> 
#include <malloc.h>
#include <comutil.h>
#endif
#include <Windows.h>
#include <WinError.h>
#include "tstSMIInterface.h"  
#include <stdio.h>
const MTD_BOOL dumpIOToFile = MTD_FALSE; /* change to false to have it not dump all MDIO to a file */
FILE *fp;
#endif


#if (MTD_CLAUSE_22_MDIO == 1)
/* does a read or a write using clause 22 to access a clause 45 register */
static MTD_STATUS Cl45UsingCl22ReadWrite
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port, 
    IN MTD_U16 dev, 
    IN MTD_U16 reg, 
    INOUT MTD_U16 *value,
    IN MTD_U16 flag
);
#endif


/****************************************************************************/

/*******************************************************************
  PORT THESE FUNCTIONS
 *******************************************************************/
/****************************************************************************/

#if (MTD_CLAUSE_22_MDIO == 0)

/************** CLAUSE 45 MDIO READ/WRITE FUNCTIONS *************************/

MTD_STATUS mtdHwXmdioWrite
( 
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port, 
    IN MTD_U16 dev, 
    IN MTD_U16 reg, 
    IN MTD_U16 value
)
{
    MTD_STATUS result = MTD_OK;


    if (devPtr->fmtdWriteMdio != NULL)
    {
        if(devPtr->fmtdWriteMdio(devPtr, port, dev,reg, value) == MTD_FAIL)
        {
            result = MTD_FAIL;
            MTD_DBG_INFO("fmtdWriteMdio 0x%04X failed to port=%d, dev=%d, reg=0x%04X\n", (unsigned)(value),(unsigned)port,(unsigned)dev,(unsigned)reg);
        }        
    }
    else
#if DB_TEST_ENVIRONMENT
    {
        if (dumpIOToFile && (!fp))
        {
            if ((fp = fopen("mtdMdioLogfile.txt", "w")) == NULL)
            {
                return MTD_FAIL; /* can't open log file */
            }
        }

        if (MdioWrite(devPtr,
                      (unsigned long)port,
                      (unsigned long)dev, 
                      (unsigned long)reg, 
                      (unsigned short)value) < S_OK)
        {
            result = MTD_FAIL;
            MTD_DBG_INFO("MdioWrite 0x%04X failed to port=%d, dev=%d, reg=0x%04X\n", (unsigned)(value),(unsigned)port,(unsigned)dev,(unsigned)reg);
        }
        else
        {
            if (dumpIOToFile && fp)
            {
                fprintf(fp,"smdio_wr(%d,%d,'%04X','%04X')\n",(int)port,(int)dev,(unsigned)reg,(unsigned)value);
            }
        }
    }
#else
    {
        /* ported code would go here if host decided to use this function instead of their own */    
        result = MTD_FAIL; /* because it's not implemented */
    }
#endif 

    return result;
}

MTD_STATUS mtdHwXmdioRead
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port, 
    IN MTD_U16 dev, 
    IN MTD_U16 reg,
    OUT MTD_U16 *data
)
{    
    MTD_STATUS result = MTD_OK;

#if DB_TEST_ENVIRONMENT
    HRESULT retCode;
#endif

    if (devPtr->fmtdReadMdio != NULL)
    {
        if(devPtr->fmtdReadMdio(devPtr, port, dev,reg, data) == MTD_FAIL)
        {
            result = MTD_FAIL;
            MTD_DBG_INFO("fmtdReadMdio failed from port=%d, dev=%d, reg=0x%04X\n", (unsigned)port,(unsigned)dev,(unsigned)reg);            
        }
        
    }
    else
#if DB_TEST_ENVIRONMENT
    {
        if (dumpIOToFile && (!fp))
        {
            if ((fp = fopen("mtdMdioLogfile.txt", "w")) == NULL)
            {
                return MTD_FAIL; /* can't open log file */
            }
        }

        *data = (MTD_U16)MdioRead(devPtr,
                                  (unsigned long)port,
                                  (unsigned long)dev,
                                  (unsigned long)reg,
                                  &retCode);
        if (retCode < S_OK)
        {
            result = MTD_FAIL;
            MTD_DBG_INFO("MdioRead failed from port=%d, dev=%d, reg=0x%04X\n", (unsigned)port,(unsigned)dev,(unsigned)reg);
        }
        else
        {
            if (dumpIOToFile && fp)
            {
                fprintf(fp,"smdio_rd(%d,%d,'%04X')=%04X\n",(int)port,(int)dev,(unsigned)reg,(unsigned)(*data));
            }

        }
    }
#else
    {
        /* ported code would go here if host uses this function instead of their own */
        result = MTD_FAIL; /* because it's not implemented */
    }
#endif 

    return result;
}
#endif /* MTD_CLAUSE_22_MDIO == 0 */

#if (MTD_CLAUSE_22_MDIO == 1)

/************** CLAUSE 45 MDIO READ/WRITE FUNCTIONS USING CLAUSE 22 *************************/

MTD_STATUS mtdHwXmdioWrite
( 
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port, 
    IN MTD_U16 dev, 
    IN MTD_U16 reg, 
    IN MTD_U16 value
)
{
    MTD_STATUS result = MTD_OK;


    if (Cl45UsingCl22ReadWrite(devPtr,port,dev,reg,&value,1) != MTD_OK) /* host must modify this function if desire to use these functions instead of init through pointers */
    {
        result = MTD_FAIL;
        MTD_DBG_INFO("Cl45UsingCl22ReadWrite write value=0x%04X failed to port=%d, dev=%d, reg=0x%04X\n", (unsigned)(value),(unsigned)port,(unsigned)dev,(unsigned)reg);
    } 

    return result;
}

MTD_STATUS mtdHwXmdioRead
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port, 
    IN MTD_U16 dev, 
    IN MTD_U16 reg,
    OUT MTD_U16 *data
)
{    
    MTD_STATUS result = MTD_OK;
                                                                         
    if (Cl45UsingCl22ReadWrite(devPtr,port,dev,reg,data,0) != MTD_OK) /* host must modify this function if desire to use these functions instead of init through pointers */
    {
        result = MTD_FAIL;
        MTD_DBG_INFO("Cl45UsingCl22ReadWrite read failed from port=%d, dev=%d, reg=0x%04X\n",(unsigned)port,(unsigned)dev,(unsigned)reg);
    } 

    return result;
}
#endif /* MTD_CLAUSE_22_MDIO == 1 */


MTD_STATUS mtdWait
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_UINT x
)
{
#if DB_TEST_ENVIRONMENT            
    Sleep(x);
    return MTD_OK;
#else
    bdk_wait_usec(x*1000);
    return MTD_OK; /* Because not implemented. This is required */ 
#endif
}

/*******************************************************************
   END: PORT THESE FUNCTIONS
 *******************************************************************/

/*******************************************************************
   FUNCTIONS WHICH USE MDIO READ/WRITE FUNCTIONS ABOVE
 *******************************************************************/
/* 
    This macro calculates the mask for partial read/write of register's data.
*/
#define MTD_CALC_MASK(fieldOffset,fieldLen,mask)        \
            if((fieldLen + fieldOffset) >= 16)      \
                mask = (0 - (1 << fieldOffset));    \
            else                                    \
                mask = (((1 << (fieldLen + fieldOffset))) - (1 << fieldOffset))

MTD_STATUS mtdHwGetPhyRegField
(
    IN  MTD_DEV_PTR devPtr,
    IN  MTD_U16      port, 
    IN  MTD_U16      dev, 
    IN  MTD_U16      regAddr,
    IN  MTD_U8       fieldOffset,
    IN  MTD_U8       fieldLength,
    OUT MTD_U16      *data
)
{
    MTD_U16 tmpData;
    MTD_STATUS   retVal;

    retVal = mtdHwXmdioRead(devPtr,port, dev, regAddr, &tmpData);

    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("Failed to read register \n");
        return MTD_FAIL;
    }
    
    mtdHwGetRegFieldFromWord(tmpData,fieldOffset,fieldLength, data);

    /* MTD_DBG_INFO("fOff %d, fLen %d, data 0x%04X.\n",(int)fieldOffset,(int)fieldLength,(int)*data); */

    return MTD_OK;
}

MTD_STATUS mtdHwSetPhyRegField
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16      port, 
    IN MTD_U16      dev, 
    IN MTD_U16      regAddr,
    IN MTD_U8       fieldOffset,
    IN MTD_U8       fieldLength,
    IN MTD_U16      data
)
{
    MTD_U16 tmpData,newData;
    MTD_STATUS   retVal;

    retVal = mtdHwXmdioRead(devPtr,port, dev, regAddr, &tmpData);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("Failed to read register \n");
        return MTD_FAIL;
    }

    mtdHwSetRegFieldToWord(tmpData,data,fieldOffset,fieldLength,&newData);

    retVal = mtdHwXmdioWrite(devPtr,port, dev, regAddr, newData);

    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("Failed to write register \n");
        return MTD_FAIL;
    }

    /*
    MTD_DBG_INFO("fieldOff %d, fieldLen %d, data 0x%x.\n",fieldOffset,\
                  fieldLength,data); 
    */
    return MTD_OK;
}

MTD_STATUS mtdHwGetRegFieldFromWord
(
    IN  MTD_U16      regData,
    IN  MTD_U8       fieldOffset,
    IN  MTD_U8       fieldLength,
    OUT MTD_U16      *data
)
{
    MTD_U16 mask;            /* Bits mask to be read */

    MTD_CALC_MASK(fieldOffset,fieldLength,mask);

    *data = (regData & mask) >> fieldOffset;

    return MTD_OK;
}

MTD_STATUS mtdHwSetRegFieldToWord
(
    IN  MTD_U16      regData,
    IN  MTD_U16      bitFieldData,
    IN  MTD_U8       fieldOffset,
    IN  MTD_U8       fieldLength,
    OUT MTD_U16      *data
)
{
    MTD_U16 mask;            /* Bits mask to be read */

    MTD_CALC_MASK(fieldOffset,fieldLength,mask);

    /* Set the desired bits to 0.                       */
    regData &= ~mask;
    /* Set the given data into the above reset bits.    */
    regData |= ((bitFieldData << fieldOffset) & mask);

    *data = regData;

    return MTD_OK;
}


MTD_STATUS mtdHwWaitForRegFieldValue
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16      port, 
    IN MTD_U16      dev, 
    IN MTD_U16      regAddr,
    IN MTD_U8       fieldOffset,
    IN MTD_U8       fieldLength,
    IN MTD_U16      expectedValue,
    IN MTD_U16      timeoutMs
)
{
    MTD_U16 waitCounter, valueRead;
    
    /* wait for it to be done */
    waitCounter = 0;
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,dev,regAddr,fieldOffset,fieldLength,&valueRead));
    while((valueRead != expectedValue) && (waitCounter < timeoutMs))
    {
        ATTEMPT(mtdWait(devPtr,1));
        ATTEMPT(mtdHwGetPhyRegField(devPtr,port,dev,regAddr,fieldOffset,fieldLength,&valueRead));
        waitCounter++;
    }

    if (valueRead == expectedValue)
    {
        return MTD_OK;
    }
    else
    {
        return MTD_FAIL;
    }
}


#if (MTD_CLAUSE_22_MDIO == 1)
/* does a read or a write using clause 22 to access a clause 45 register */
/* flag=0 is a read, value is an output only */
/* flag=1 is a write, value is an input only */
static MTD_STATUS Cl45UsingCl22ReadWrite
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port, 
    IN MTD_U16 dev, 
    IN MTD_U16 reg, 
    INOUT MTD_U16 *value,
    IN MTD_U16 flag
)
{
    MTD_STATUS result = MTD_OK;

#if DB_TEST_ENVIRONMENT
    HRESULT retCode;
#endif    
    
    /* Clause 45 write using Clause 22 procedure */
    /* R13.4:0 = device id */
    /* R14 = Clause 45 register address */
    /* R13.4:0 = same device id, R13.15:14 = 01b, data no post increment*/
    /* R14 = data to write  */

    /* Clause 45 read using Clause 22 procedure */
    /* R13.4:0 = device id */
    /* R14 = Clause 45 register address */
    /* R13.4:0 = same device id, R13.15:14 = 01b, data no post increment*/
    /* read R14, contains value of data */
        
    if (devPtr->fmtdWriteMdio != NULL)
    {
        if(devPtr->fmtdWriteMdio(devPtr,port,13,dev) == MTD_FAIL)
        {
            result = MTD_FAIL;
            MTD_DBG_INFO("fmtdWriteMdio Cl22 data= 0x%04X failed to port=%d, reg=0x%04X\n", (unsigned)(dev),(unsigned)port,(unsigned)13);
        }  

        if(devPtr->fmtdWriteMdio(devPtr,port,14,reg) == MTD_FAIL)
        {
            result = MTD_FAIL;
            MTD_DBG_INFO("fmtdWriteMdio Cl22 data= 0x%04X failed to port=%d, reg=0x%04X\n", (unsigned)(reg),(unsigned)port,(unsigned)14);
        }

        
        if(devPtr->fmtdWriteMdio(devPtr,port,13,dev+0x4000) == MTD_FAIL)
        {
            result = MTD_FAIL;
            MTD_DBG_INFO("fmtdWriteMdio Cl22 data= 0x%04X failed to port=%d, reg=0x%04X\n", (unsigned)(dev+0x4000),(unsigned)port,(unsigned)13);
        }

        if (flag == 0)
        {
            /* now read the data */
            if(devPtr->fmtdReadMdio(devPtr, port,14, value) == MTD_FAIL)
            {
                result = MTD_FAIL;
                MTD_DBG_INFO("fmtdReadMdio Cl22 failed from port=%d, reg=0x%04X\n", (unsigned)port,(unsigned)14);            
            }
        }
        else
        {
            /* now write the data */
            if(devPtr->fmtdWriteMdio(devPtr,port,14,*value) == MTD_FAIL)
            {
                result = MTD_FAIL;
                MTD_DBG_INFO("fmtdWriteMdio Cl22 data= 0x%04X failed to port=%d, reg=0x%04X\n", (unsigned)(*value),(unsigned)port,(unsigned)14);
            }
        }

    }
    else
#if DB_TEST_ENVIRONMENT
    {
        if (dumpIOToFile && (!fp))
        {
            if ((fp = fopen("mtdMdioLogfile.txt", "w")) == NULL)
            {
                return MTD_FAIL; /* can't open log file */
            }
        }

        if (Cl22MdioWrite(devPtr, 
                          (unsigned long)port, 
                          (unsigned long)13, 
                          (unsigned short)dev) < S_OK)
        {
            result = MTD_FAIL;
            MTD_DBG_INFO("Cl22MdioWrite 0x%04X failed to port=%d, reg=0x%04X\n", (unsigned)(dev),(unsigned)port,(unsigned)13);
        }
        else
        {
            if (dumpIOToFile && fp)
            {
                fprintf(fp,"smdio22_wr(%d, %d,%d)\n",(unsigned)port,(unsigned)13,(unsigned)dev);
            }
        }
    
        if (Cl22MdioWrite(devPtr, 
                          (unsigned long)port, 
                          (unsigned long)14, 
                          (unsigned short)reg) < S_OK)
        {
            result = MTD_FAIL;
            MTD_DBG_INFO("Cl22MdioWrite 0x%04X failed to port=%d, reg=0x%04X\n", (unsigned)(reg),(unsigned)port,(unsigned)14);
        }
        else
        {
            if (dumpIOToFile && fp)
            {
                fprintf(fp,"smdio22_wr(%d, %d,%d)\n",(unsigned)port,(unsigned)14,(unsigned)reg);
            }
        }

        if (Cl22MdioWrite(devPtr, 
                          (unsigned long)port, 
                          (unsigned long)13, 
                          (unsigned short)dev+0x4000) < S_OK)
        {
            result = MTD_FAIL;
            MTD_DBG_INFO("Cl22MdioWrite 0x%04X failed to port=%d, reg=0x%04X\n", (unsigned)(dev+0x4000),(unsigned)port,(unsigned)13);
        }
        else
        {
            if (dumpIOToFile && fp)
            {
                fprintf(fp,"smdio22_wr(%d, %d, '%04X')\n",(unsigned)port,(unsigned)13,(unsigned)dev+0x4000);
            }
        }

        if (flag == 0)
        {
            /* now read the data */
            *value = Cl22MdioRead(devPtr,
                                  (unsigned long)port, 
                                  (unsigned long)14, 
                                  &retCode);
            
            if (retCode < S_OK)
            {
                result = MTD_FAIL;
                MTD_DBG_INFO("Cl22MdioRead failed from port=%d, reg=0x%04X\n",(unsigned)port,(unsigned)14);
            }
            else
            {
                if (dumpIOToFile && fp)
                {
                    fprintf(fp,"smdio22_rd(%d, %d)=0x%04X\n",(unsigned)port,(unsigned)14,(unsigned)*value);
                }
            }            
        }
        else
        {
            /* now write the data */
            if (Cl22MdioWrite(devPtr,
                              (unsigned long)port, 
                              (unsigned long)14, 
                              (unsigned short)*value) < S_OK)
            {
                result = MTD_FAIL;
                MTD_DBG_INFO("Cl22MdioWrite 0x%04X failed to port=%d, reg=0x%04X\n", (unsigned)(*value),(unsigned)port,(unsigned)14);
            }
            else
            {
                if (dumpIOToFile && fp)
                {
                    fprintf(fp,"smdio22_wr(%d, %d, '%04X')\n",(unsigned)port,(unsigned)14,(unsigned)*value);
                }
            }            
        }
    }
#else
    {
        /* ported code would go here if host decided to use this function instead of using their own */
        result = MTD_FAIL; /* because it's not implemented */
    }
#endif 
    

    return result;
    
}
#endif


#if 0
/* EXAMPLE CODE USED FOR READING IN A FILE TO BE DOWNLOADED TO FLASH/RAM */

#if DB_TEST_ENVIRONMENT
/***************************************************************************************** 
    The header file stdio.h needs to be included before compiling and using 
    this function

    See the "Example" section of the function declarations of mtdUpdateFlashImage() and 
    mtdMdioRamDownload() to understand how mtdOpenReadFile() can be used.
******************************************************************************************/
MTD_INT mtdOpenReadFile
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    INOUT FILE **pfp, 
    IN MTD_8 *fname, 
    OUT MTD_U8 *data,
    IN MTD_UINT max_data_size
)
{
    int size;
 
    if ((*pfp = fopen(fname, "rb")) == (FILE *)0)
    {
        return 0; // error
    }
            
    size = (int)fread(data, sizeof(char), max_data_size, *pfp);

    if (ferror(*pfp) || size == 0)
    {
        return 0; // error
    }
    else
    {
        MTD_DBG_INFO("Read from %s, %d bytes\n", fname, size);
    }
    return size;
}
#endif
#endif


