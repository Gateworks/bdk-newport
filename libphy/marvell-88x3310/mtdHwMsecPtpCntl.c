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
#if DB_TEST_ENVIRONMENT
#if 0
#include "stdio.h"
#include "windows.h" 
#include "malloc.h"
#include "comutil.h"
#endif
#include "windows.h"
#include "winError.h"
#endif

#include "mtdApiTypes.h"
#include "mtdApiRegs.h"
#include "mtdHwCntl.h"
#include "mtdAPI.h"
#include "mtdHwMsecPtpCntl.h"
#include "mtdSemaphore.h"
#include "mtdMsecPtpApiDefs.h"
#include "mtdMsecInternal.h"
#include "mtdPtp1step.h"

/* possible commands for accessing MacSec */
#define MTD_MACSEC_RD_CMD    1
#define MTD_MACSEC_WR_CMD    2
#define MTD_MACSEC_DBLWR_CMD 3

/* addresses for interfacing to MacSec indirectly */
#define MTD_MACSEC_CNTL        MTD_T_UNIT_PMA_PMD,0xC04A
#define MTD_MACSEC_ADDR_STATUS MTD_T_UNIT_PMA_PMD,0xC04B
#define MTD_MACSEC_HIGH_WORD   MTD_T_UNIT_PMA_PMD,0xC04C
#define MTD_MACSEC_LOW_WORD    MTD_T_UNIT_PMA_PMD,0xC04D

/* status of commands */
#define MTD_MACSEC_BUSY  0xF000
#define MTD_MACSEC_OK    0xF001
#define MTD_MACSEC_ERROR 0xFFFF /* can be caused by timeout, trying to read/write at odd address, MacSec in reset/sleep mode */
                                /* invalid command, address out of range, or trying to do a double write to an address not on a quad boundary */
#define MTD_MACSEC_DEV_ADDR  31

MTD_INT MTD_DEBUG_MSEC_WRITE = 0;
MTD_INT MTD_DEBUG_MSEC_READ = 0;
static MTD_INT indirect = 1; /* select indirect or direct access registers, this is not the same as macsecIndirectAccess! */

#define MTD_MACSEC_READ_RETRY_MAX 3 /* maximum number of tries to retry a read before returning a failure */
                 
MTD_STATUS mtdHwMsecWrite
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 dev,
    IN MTD_U16 reg,
    IN MTD_U32 value
)
{
    MTD_U16 readResult, cntr;

    if ((reg & 1) != 0)
    {
        return MTD_FAIL; /* reg must be even, since we are going to access reg and reg + 1 */
    }

    if (devPtr->macsecIndirectAccess == MTD_TRUE)
    {
        /* check if already busy with another command */
        ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_MACSEC_ADDR_STATUS,&readResult));

        if (readResult == MTD_MACSEC_BUSY)
        {
            return MTD_FAIL;
        }

        /* write 'write' command */
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_MACSEC_CNTL,MTD_MACSEC_WR_CMD));

        /* write data */
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_MACSEC_LOW_WORD,(MTD_U16)(value)));
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_MACSEC_HIGH_WORD,(MTD_U16)(value >> 16)));

        /* write address to start 'write' process */
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_MACSEC_ADDR_STATUS,reg));

        /* wait for done, error, or timeout */
        cntr = 0;
        ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_MACSEC_ADDR_STATUS,&readResult));
        while((readResult == MTD_MACSEC_BUSY) && (cntr++ < 10))
        {
            ATTEMPT(mtdWait(devPtr,1));
            ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_MACSEC_ADDR_STATUS,&readResult));
        }

        if ((cntr == 10 && readResult == MTD_MACSEC_BUSY) || readResult == MTD_MACSEC_ERROR)
        {
            /* timed out or error */
            return MTD_FAIL;
        }

        /* write is done */
    }
    else
    {
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,dev,reg,(MTD_U16)(value & 0xFFFF)));
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,dev,reg+1,(MTD_U16)(value>>16)));
    }

    return MTD_OK;
}

STATIC MTD_STATUS mtdHwMsecReadTry(MTD_DEV_PTR devPtr, MTD_U16 port, MTD_U16 dev, MTD_U16 reg,MTD_U32 *data);
MTD_STATUS mtdHwMsecRead
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 dev,
    IN MTD_U16 reg,
    OUT MTD_U32 *data
)
{
    MTD_U16 tryCounter=0;
    MTD_STATUS status = MTD_FAIL;

    if ((reg & 1) != 0)
    {
        return MTD_FAIL; /* reg must be even, since we are going to access reg and reg + 1 */
    }

    while (tryCounter++ < MTD_MACSEC_READ_RETRY_MAX && status != MTD_OK)
    {
        status = mtdHwMsecReadTry(devPtr, port, dev,reg, data);
    }
    
    return status;
}

STATIC MTD_STATUS mtdHwMsecReadTry(MTD_DEV_PTR devPtr, MTD_U16 port, MTD_U16 dev, MTD_U16 reg,MTD_U32 *data)
{
    MTD_U16 dummy, readResult, cntr;
    
    if (devPtr->macsecIndirectAccess == MTD_TRUE)
    {
        /* check if already busy with another command */
        ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_MACSEC_ADDR_STATUS,&readResult));

        if (readResult == MTD_MACSEC_BUSY)
        {
            return MTD_FAIL;
        }

        /* write 'read' command */
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_MACSEC_CNTL,MTD_MACSEC_RD_CMD));

        /* write address to start 'read' process */
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_MACSEC_ADDR_STATUS,reg));

        /* wait for done, error, or timeout */
        cntr = 0;
        ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_MACSEC_ADDR_STATUS,&readResult));
        while((readResult == MTD_MACSEC_BUSY) && (cntr++ < 10))
        {
            ATTEMPT(mtdWait(devPtr,1));
            ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_MACSEC_ADDR_STATUS,&readResult));
        }

        if ((cntr == 10 && readResult == MTD_MACSEC_BUSY) || readResult == MTD_MACSEC_ERROR)
        {
            /* timed out or error */
            return MTD_FAIL;
        }

        /* result ready, read it out */
        ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_MACSEC_LOW_WORD,&readResult));
        *data = (MTD_U32)readResult; /* assign low word */
        ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_MACSEC_HIGH_WORD,&readResult));
        *data |= (((MTD_U32)readResult) << 16);

    }
    else
    {
        /* first send the read request */
        ATTEMPT(mtdHwXmdioRead(devPtr,port,dev,reg,&dummy));

        /* now make sure the address read is correct */
        ATTEMPT(mtdHwXmdioRead(devPtr,port,dev,0x97FD,&dummy));

        if (dummy != reg)
        {
            return MTD_FAIL;
        }

        /* now read the low word */
        *data = 0;
        ATTEMPT(mtdHwXmdioRead(devPtr,port,dev,0x97FE,&dummy));
        *data = dummy;
        /* now read the high word */
        ATTEMPT(mtdHwXmdioRead(devPtr,port,dev,0x97FF,&dummy));
        *data |= (((MTD_U32)dummy)<<16);
    }

    return MTD_OK;
}

MTD_STATUS mtdHwMsecDoubleWrite
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 dev,
    IN MTD_U16 reg,
    IN MTD_U64 value,
    IN MTD_BOOL useIndirectAddressing
)
{
    MTD_U16 readResult, cntr;

    if ((reg & 0x3) != 0)
    {
        return MTD_FAIL; /* reg must be on 4 word boundary, since we are going to access reg to reg + 3 */
    }

    if (useIndirectAddressing == MTD_TRUE)
    {
        /* check if already busy with another command */
        ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_MACSEC_ADDR_STATUS,&readResult));

        if (readResult == MTD_MACSEC_BUSY)
        {
            return MTD_FAIL;
        }

        /* write 'write' command */
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_MACSEC_CNTL,MTD_MACSEC_DBLWR_CMD));

        /* write data */
        /* data should be in format 0xAAAABBBBCCCCDDDD where DDDD goes to addres reg, CCCC goes to address reg+1, */
        /* BBBB goes to address reg+2 and AAAA goes to address reg+3 */
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_MACSEC_LOW_WORD,(MTD_U16)(value >> 32))); /* write low word of reg + 2 */
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_MACSEC_HIGH_WORD,(MTD_U16)(value >> 48)));
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_MACSEC_LOW_WORD,(MTD_U16)(value)));       /* write low word of reg + 0 */
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_MACSEC_HIGH_WORD,(MTD_U16)(value >> 16)));

        /* write address to start 'write' process */
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_MACSEC_ADDR_STATUS,reg));

        /* wait for done, error, or timeout */
        cntr = 0;
        ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_MACSEC_ADDR_STATUS,&readResult));
        while((readResult == MTD_MACSEC_BUSY) && (cntr++ < 10))
        {
            mtdWait(devPtr,1);
            ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_MACSEC_ADDR_STATUS,&readResult));
        }

        if ((cntr == 10 && readResult == MTD_MACSEC_BUSY) || readResult == MTD_MACSEC_ERROR)
        {
            /* timed out or error */
            return MTD_FAIL;
        }

        /* write is done */

    }
    else
    {
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,dev,reg,(MTD_U16)(value & 0xFFFF)));
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,dev,reg+1,(MTD_U16)((value & 0xFFFF0000ULL)>>16)));
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,dev,reg+2,(MTD_U16)((value & 0xFFFF00000000ULL)>>32)));
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,dev,reg+3,(MTD_U16)((value & 0xFFFF000000000000ULL)>>48)));
    }

    return MTD_OK;
}


MTD_STATUS mtdHwGetMsecPhyRegField
(
    IN  MTD_DEV_PTR devPtr,
    IN  MTD_U16      port,
    IN  MTD_U16      dev,
    IN  MTD_U16      regAddr,
    IN  MTD_U8       fieldOffset,
    IN  MTD_U8       fieldLength,
    OUT MTD_U32      *data
)
{
    MTD_U32 dummy;

    if ((regAddr & 1) != 0)
    {
        return MTD_FAIL; /* reg must be even, since we are going to access reg and reg + 1 */
    }

    ATTEMPT(mtdHwMsecRead(devPtr,port,dev,regAddr,&dummy));

    ATTEMPT(mtdHwGetRegFieldFromLongWord(dummy,fieldOffset,fieldLength,data));

    return MTD_OK;
}

MTD_STATUS mtdHwSetMsecPhyRegField
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16      port,
    IN MTD_U16      dev,
    IN MTD_U16      regAddr,
    IN MTD_U8       fieldOffset,
    IN MTD_U8       fieldLength,
    IN MTD_U32      data
)
{
    MTD_U32 dummy,dummy2;

    if ((regAddr & 1) != 0)
    {
        return MTD_FAIL; /* reg must be even, since we are going to access reg and reg + 1 */
    }

    ATTEMPT(mtdHwMsecRead(devPtr,port,dev,regAddr,&dummy)); 

    ATTEMPT(mtdHwMsecSetRegFieldToLongWord(dummy,data,fieldOffset,fieldLength,&dummy2));

    ATTEMPT(mtdHwMsecWrite(devPtr,port,dev,regAddr,dummy2));

    return MTD_OK;
}

MTD_STATUS mtdHwGetRegFieldFromLongWord
(
    IN  MTD_U32      regData,
    IN  MTD_U8       fieldOffset,
    IN  MTD_U8       fieldLength,
    OUT MTD_U32      *data
)
{
    MTD_U32 mask;

    /* do some range checking on the fieldOffset and fieldLength */
    if ((fieldOffset + fieldLength) > 32)
    {
        return MTD_FAIL;
    }

    mask = (((1<<(fieldOffset+fieldLength)))-(1<<fieldOffset));
    regData &= mask;
    *data = (regData>>fieldOffset);

    return MTD_OK;
}

MTD_STATUS mtdHwMsecSetRegFieldToLongWord
(
    IN  MTD_U32      regData,
    IN  MTD_U32      bitFieldData,
    IN  MTD_U8       fieldOffset,
    IN  MTD_U8       fieldLength,
    OUT MTD_U32      *data
)
{
    MTD_U32 mask;

    /* do some range checking on the fieldOffset and fieldLength */
    if ((fieldOffset + fieldLength) > 32)
    {
        return MTD_FAIL;
    }

    mask = (((1<<(fieldOffset+fieldLength)))-(1<<fieldOffset));

    /* Set the desired bits to 0.                       */
    regData &= ~mask;
    /* Set the given data into the above reset bits.    */
    regData |= ((bitFieldData << fieldOffset) & mask);

    *data = regData;

    return MTD_OK;
}


/*******************************************************************************
 Provided with Macsec/PTP package
 ******************************************************************************/

/* 
    This macro calculates the mask for partial read/write of register's data.
*/
#define MTD_CALC_MASK(fieldOffset,fieldLen,mask)        \
            if((fieldLen + fieldOffset) >= 16)      \
                mask = (0 - (1 << fieldOffset));    \
            else                                    \
                mask = (((1 << (fieldLen + fieldOffset))) - (1 << fieldOffset))


MTD_STATUS mtdHwReadPhyReg
(
    IN  MTD_DEV    *mtd_dev,
    IN  MTD_U16     port,
    IN  MTD_U32    _regAddr,
    OUT MTD_U16    *data
)
{
  MTD_U16 dev;
  MTD_U16 reg;

  dev = (MTD_U16)(_regAddr>>16);
  reg = (MTD_U16)(_regAddr & 0xffff);

  mtdSemTake(mtd_dev,mtd_dev->multiAddrSem,OS_WAIT_FOREVER);

  if (mtdHwXmdioRead(mtd_dev,port,dev,reg,data) == MTD_FAIL)
  {
       mtdSemGive(mtd_dev,mtd_dev->multiAddrSem);
       return (MTD_DRV_FAIL_READ_REG | MTD_FAIL);
  }

  mtdSemGive(mtd_dev,mtd_dev->multiAddrSem);

  return MTD_OK;
}

MTD_STATUS _mtdHwReadPhyReg
(
    IN  MTD_DEV    *mtd_dev,
    IN  MTD_U16     port,
    IN  MTD_U32    _regAddr,
    OUT MTD_U16    *data
)
{
  MTD_U16 dev;
  MTD_U16 reg;

  dev = (MTD_U16)(_regAddr>>16);
  reg = (MTD_U16)(_regAddr & 0xffff);

  if (mtdHwXmdioRead(mtd_dev,port,dev,reg,data) == MTD_FAIL)
  {
       return (MTD_DRV_FAIL_READ_REG | MTD_FAIL);
  }


  return MTD_OK;
}

MTD_STATUS mtdHwWritePhyReg
(
    IN  MTD_DEV    *mtd_dev,
    IN  MTD_U16     port,
    IN  MTD_U32    _regAddr,
    IN  MTD_U16    data
)
{
   MTD_U16 dev;
   MTD_U16 reg;

   dev = (MTD_U16)(_regAddr>>16);
   reg = (MTD_U16)(_regAddr & 0xffff);

   mtdSemTake(mtd_dev,mtd_dev->multiAddrSem,OS_WAIT_FOREVER);

   if (mtdHwXmdioWrite(mtd_dev,port,dev,reg,data) == MTD_FAIL)
   {
        mtdSemGive(mtd_dev,mtd_dev->multiAddrSem);
        return (MTD_DRV_FAIL_WRITE_REG | MTD_FAIL);
   }

  mtdSemGive(mtd_dev,mtd_dev->multiAddrSem);

  return MTD_OK;
}

MTD_STATUS _mtdHwWritePhyReg
(
    IN  MTD_DEV    *mtd_dev,
    IN  MTD_U16     port,
    IN  MTD_U32    _regAddr,
    IN  MTD_U16    data
)
{
  MTD_U16 dev;
  MTD_U16 reg;

   dev = (MTD_U16)(_regAddr>>16);
   reg = (MTD_U16)(_regAddr & 0xffff);

  if (mtdHwXmdioWrite(mtd_dev,port,dev,reg,data) == MTD_FAIL)
  {
       return (MTD_DRV_FAIL_WRITE_REG | MTD_FAIL);
  }
  
  return MTD_OK;
}


/*******************************************************************************
* mtdHw_Get_PhyRegField
*
* DESCRIPTION:
*       This function reads a specified field from a switch's port phy register.
*
* INPUTS:
*       port        - The port number.
*       regAddr - The device address + register's address.
*       fieldOffset - The field start bit index. (0 - 15)
*       fieldLength - Number of bits to read.
*
* OUTPUTS:
*       data        - The read register field.
*
* RETURNS:
*       MTD_OK on success, or
*       MTD_FAIL | [reason]  - on error
*
* COMMENTS:
*       1.  The sum of fieldOffset & fieldLength parameters must be smaller-
*           equal to 16.
*
*******************************************************************************/
MTD_STATUS mtdHw_Get_PhyRegField
(
    IN  MTD_DEV    *dev,
    IN  MTD_U16     port,
    IN  MTD_U32    regAddr,
    IN  MTD_U8     fieldOffset,
    IN  MTD_U8     fieldLength,
    OUT MTD_U16    *data
)
{
    MTD_U16 mask;            /* Bits mask to be read */
    MTD_U16 tmpData;
    MTD_STATUS   retVal;

    retVal = mtdHwReadPhyReg(dev, port, regAddr,&tmpData);

    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("Failed to read register \n");
        return MTD_FAIL;
    }
    
    MTD_CALC_MASK(fieldOffset,fieldLength,mask);

    tmpData = (tmpData & mask) >> fieldOffset;
    *data = tmpData;

/*    MTD_DBG_INFO("fOff %d, fLen %d, data 0x%x.\n",fieldOffset,fieldLength,*data); */

    return MTD_OK;
}


/*******************************************************************************
* mtdHw_Set_PhyRegField
*
* DESCRIPTION:
*       This function writes to specified field in a switch's port phy register.
*
* INPUTS:
*       port        - The port number.
*       regAddr - The device address + register's address.
*       fieldOffset - The field start bit index. (0 - 15)
*       fieldLength - Number of bits to write.
*       data        - Data to be written.
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       MTD_OK on success, or
*       MTD_FAIL | [reason]  - on error
*
* COMMENTS:
*       1.  The sum of fieldOffset & fieldLength parameters must be smaller-
*           equal to 16.
*
*******************************************************************************/
MTD_STATUS mtdHw_Set_PhyRegField
(
    IN  MTD_DEV    *dev,
    IN  MTD_U16     port,
    IN  MTD_U32       regAddr,
    IN  MTD_U8     fieldOffset,
    IN  MTD_U8     fieldLength,
    IN  MTD_U16    data
)
{
    MTD_U16 mask;
    MTD_U16 tmpData;
    MTD_STATUS   retVal;

    retVal = mtdHwReadPhyReg(dev, port,  regAddr,&tmpData);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("Failed to read register \n");
        return MTD_FAIL;
    }

    MTD_CALC_MASK(fieldOffset,fieldLength,mask);

    /* Set the desired bits to 0.                       */
    tmpData &= ~mask;
    /* Set the given data into the above reset bits.    */
    tmpData |= ((data << fieldOffset) & mask);

    retVal = mtdHwWritePhyReg(dev, port, regAddr,tmpData);

    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("Failed to write register \n");
        return MTD_FAIL;
    }

/*    MTD_DBG_INFO("fieldOff %d, fieldLen %d, data 0x%x.\n",fieldOffset,
                  fieldLength,data); */

    return MTD_OK;
}


MTD_STATUS _mtdMsecWritePortReg 
(
    IN  MTD_DEV    *dev,
    IN  MTD_U16    port,
    IN  MTD_U16    addr,
    IN  MTD_U32    data
)
{
    MTD_STATUS   retVal;
    MTD_U32 phy;
    MTD_INT i;
    MTD_U16 tmpData = 0;

    if(dev->macsecIndirectAccess)
    {
        /* make sure not busy with another command, should never be */
        phy = (1<<16)|0xC04B;        
        if((retVal = _mtdHwReadPhyReg(dev, port, phy, &tmpData))
            != MTD_OK)
        {
            MTD_DBG_ERROR("Writing to macsec reg %x failed.\n",addr);
            return(retVal | MTD_API_FAIL_READ_REG);
        }
        
        if(tmpData == 0xF000)
        {
            return(retVal | MTD_API_FAIL_WRITE_REG);
        }
        
        phy = (1<<16)|0xC04A;
        if((retVal = _mtdHwWritePhyReg(dev, port, phy, 2))
            != MTD_OK)
        {
            MTD_DBG_ERROR("Writing to macsec reg %x failed.\n",addr);
            return(retVal | MTD_API_FAIL_WRITE_REG);
        }

        phy = (1<<16)|0xC04D;
        if((retVal = _mtdHwWritePhyReg(dev, port, phy,(MTD_U16)(data&0xffff)))
            != MTD_OK)
        {
            MTD_DBG_ERROR("Writing to macsec reg %x failed.\n",addr);
            return(retVal | MTD_API_FAIL_WRITE_REG);
        }

        phy = (1<<16)|0xC04C;
        if((retVal = _mtdHwWritePhyReg(dev, port, phy,(MTD_U16)(data>>16)))
            != MTD_OK)
        {
            MTD_DBG_ERROR("Writing to macsec reg %x failed.\n",addr+1);
            return(retVal | MTD_API_FAIL_WRITE_REG);
        }

        if(MTD_DEBUG_MSEC_WRITE == 1)
        {
            MTD_DBG_CRITIC_INFO("mtdMsecWritePortReg                 : port %d Addr %04x Data %08x\n", port, addr, data);
        }

        phy = (1<<16)|0xC04B;
        if((retVal = _mtdHwWritePhyReg(dev, port, phy, addr))
            != MTD_OK)
        {
            MTD_DBG_ERROR("Writing to reg %x failed.\n",addr);
            return(retVal | MTD_API_FAIL_WRITE_REG);
        }

    /* Added to check write register */
        for(i=0; i<10; i++)
        {
            ATTEMPT(mtdWait(dev,1));
            if((retVal = _mtdHwReadPhyReg(dev, port, phy, &tmpData))
                != MTD_OK)
            {
                MTD_DBG_ERROR("Read to reg 0x1C04B failed.\n");
                return(retVal | MTD_API_FAIL_READ_REG);
            }
            if(tmpData == 0xF001)
                break;
        }
        if(tmpData != 0xF001)
        {
            MTD_DBG_ERROR("Writing to reg %x failed.\n",addr);
            return(MTD_FAIL);
        }
    }
    else
    {
        for(i=0; i<20; i++)
        {
            phy = (MTD_MACSEC_DEV_ADDR<<16)|addr;
            if((retVal = _mtdHwWritePhyReg(dev, port, phy,(MTD_U16)(data&0xffff)))
                != MTD_OK)
            {
                MTD_DBG_ERROR("Writing to reg %x failed.\n",addr);
                return(retVal | MTD_API_FAIL_WRITE_REG);
            }

            phy = (MTD_MACSEC_DEV_ADDR<<16)|(addr+1);
            if((retVal = _mtdHwWritePhyReg(dev, port, phy,(MTD_U16)(data >> 16)))
                != MTD_OK)
            {
                MTD_DBG_ERROR("Writing to reg %x failed.\n",addr+1);
                return(retVal | MTD_API_FAIL_WRITE_REG);
            }
            if(MTD_DEBUG_MSEC_WRITE == 1)
            {
                MTD_DBG_CRITIC_INFO("mtdMsecWritePortReg                 : port %d Addr %04x Data %08x\n", port, addr, data);
            }

        /* Added to check write register */
            if((retVal = _mtdHwReadPhyReg(dev, port, 0x001f97fc, &tmpData))
                != MTD_OK)
            {
                MTD_DBG_ERROR("Read to reg 0x1f97fc failed.\n");
                return(retVal | MTD_API_FAIL_READ_REG);
            }
            if(tmpData == 0)
                break;
            if(i>=10)
            {
                MTD_DBG_ERROR("Writing to reg %x failed.\n",addr);
                return(MTD_FAIL);
            }
        }
    }

    return MTD_OK;
}

MTD_STATUS _mtdMsecWritePortReg_64 
(
    IN  MTD_DEV    *dev,
    IN  MTD_U16    port,
    IN  MTD_U16    addr,
    IN  MTD_U32    dataL,
    IN  MTD_U32    dataH
)
{
    MTD_STATUS   retVal;
    MTD_U32 phy;
    MTD_U16 tmpData;
    MTD_INT i;

    if(dev->macsecIndirectAccess)
    {

        /* make sure not busy with another command, should never be */
        phy = (1<<16)|0xC04B;        
        if((retVal = _mtdHwReadPhyReg(dev, port, phy, &tmpData))
            != MTD_OK)
        {
            MTD_DBG_ERROR("Writing to macsec reg %x failed.\n",addr);
            return(retVal | MTD_API_FAIL_READ_REG);
        }
        
        if(tmpData == 0xF000)
        {
            return(retVal | MTD_API_FAIL_WRITE_REG);
        }        
        
        phy = (1<<16)|0xC04A;
        if((retVal = _mtdHwWritePhyReg(dev, port, phy, 3))
            != MTD_OK)
        {
            MTD_DBG_ERROR("Writing to reg %x failed.\n",addr);
            return(retVal | MTD_API_FAIL_WRITE_REG);
        }

        phy = (1<<16)|0xC04D;
        if((retVal = _mtdHwWritePhyReg(dev, port, phy,(MTD_U16)(dataH&0xffff)))
            != MTD_OK)
        {
            MTD_DBG_ERROR("Writing to reg %x failed.\n",addr+2);
            return(retVal | MTD_API_FAIL_WRITE_REG);
        }

        phy = (1<<16)|0xC04C;
        if((retVal = _mtdHwWritePhyReg(dev, port, phy,(MTD_U16)(dataH>>16)))
            != MTD_OK)
        {
            MTD_DBG_ERROR("Writing to reg %x failed.\n",addr+3);
            return(retVal | MTD_API_FAIL_WRITE_REG);
        }

        phy = (1<<16)|0xC04D;
        if((retVal = _mtdHwWritePhyReg(dev, port, phy,(MTD_U16)(dataL&0xffff)))
            != MTD_OK)
        {
            MTD_DBG_ERROR("Writing to reg %x failed.\n",addr);
            return(retVal | MTD_API_FAIL_WRITE_REG);
        }

        phy = (1<<16)|0xC04C;
        if((retVal = _mtdHwWritePhyReg(dev, port, phy,(MTD_U16)(dataL>>16)))
            != MTD_OK)
        {
            MTD_DBG_ERROR("Writing to reg %x failed.\n",addr+1);
            return(retVal | MTD_API_FAIL_WRITE_REG);
        }

        if(MTD_DEBUG_MSEC_WRITE == 1)
        {
            MTD_DBG_CRITIC_INFO("mtdMsecWritePortReg                 : port %d Addr %04x DataH %08x DataL %08x\n", port, addr, dataH, dataL);
        }

        phy = (1<<16)|0xC04B;
        if((retVal = _mtdHwWritePhyReg(dev, port, phy, addr))
            != MTD_OK)
        {
            MTD_DBG_ERROR("Writing to reg %x failed.\n",addr);
            return(retVal | MTD_API_FAIL_WRITE_REG);
        }

        for(i=0; i<10; i++)
        {
        /* Added to check write register */
            ATTEMPT(mtdWait(dev,1));
            if((retVal = _mtdHwReadPhyReg(dev, port, phy, &tmpData))
                != MTD_OK)
            {
                MTD_DBG_ERROR("Read to reg 0x1f97fc failed.\n");
                return(retVal | MTD_API_FAIL_READ_REG);
            }
            if(tmpData == 0xF001)
                break;
        }
        if(tmpData != 0xF001)
        {
            MTD_DBG_ERROR("Writing to reg %x failed.\n",addr);
            return(MTD_FAIL);
        }

    }
    else
    {
        retVal = _mtdMsecWritePortReg (dev, port, addr, dataL);
        if(retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return retVal;
        }

        retVal = _mtdMsecWritePortReg (dev, port, addr+2, dataH);
        if(retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return retVal;
        }
    }

    return MTD_OK;
}

STATIC MTD_STATUS _mtdMsecReadPortRegTry (MTD_DEV *dev,MTD_U16 port,MTD_U16 addr,MTD_U32   *data);
MTD_STATUS _mtdMsecReadPortReg 
(
    IN  MTD_DEV    *dev,
    IN  MTD_U16    port,
    IN  MTD_U16   addr,
    OUT MTD_U32   *data
)
{
    MTD_U16 tryCounter=0;
    MTD_STATUS status = MTD_FAIL;

    if ((addr & 1) != 0)
    {
        return MTD_FAIL; /* reg must be even, since we are going to access reg and reg + 1 */
    }

    while (tryCounter++ < MTD_MACSEC_READ_RETRY_MAX && status != MTD_OK)
    {
        status = _mtdMsecReadPortRegTry(dev, port, addr, data);
    }
    
    return status;
}



STATIC MTD_STATUS _mtdMsecReadPortRegTry (MTD_DEV *dev,MTD_U16 port,MTD_U16 addr,MTD_U32   *data)
{
    MTD_STATUS   retVal;
    MTD_U32 phy;
    MTD_U16 dataH, dataL;
    MTD_U16 tmpData;
    MTD_INT i;

    if(dev->macsecIndirectAccess)
    {
        /* make sure not busy with another command, should never be */
        phy = (1<<16)|0xC04B;        
        if((retVal = _mtdHwReadPhyReg(dev, port, phy, &tmpData))
            != MTD_OK)
        {
            MTD_DBG_ERROR("Reading from macsec reg %x failed.\n",addr);
            return(retVal | MTD_API_FAIL_READ_REG);
        }
        
        if(tmpData == 0xF000)
        {
            return(retVal | MTD_API_FAIL_WRITE_REG);
        }        
        
        phy = (1<<16)|0xC04A;
        if((retVal = _mtdHwWritePhyReg(dev, port, phy, 1))
            != MTD_OK)
        {
            MTD_DBG_ERROR("Reading from reg %x failed.\n",addr);
            return(retVal | MTD_API_FAIL_WRITE_REG);
        }

        phy = (1<<16)|0xC04B;
        if((retVal = _mtdHwWritePhyReg(dev, port, phy, addr))
            != MTD_OK)
        {
            MTD_DBG_ERROR("Reading from reg %x failed.\n",addr);
            return(retVal | MTD_API_FAIL_WRITE_REG);
        }

        for(i = 0; i < 10; i++)
        {
            ATTEMPT(mtdWait(dev,1));
            if((retVal = _mtdHwReadPhyReg(dev, port, phy, &tmpData))
                != MTD_OK)
            {
                MTD_DBG_ERROR("Reading from reg %x failed.\n",addr);
                return(retVal | MTD_API_FAIL_WRITE_REG);
            }

            if(tmpData == 0xF001)
                break;
        }

        if(tmpData != 0xF001)
        {
            MTD_DBG_ERROR("Reading from reg %x failed.\n",addr);
            return(MTD_FAIL);
        }

        phy = (1<<16)|0xC04D;
        if((retVal = _mtdHwReadPhyReg(dev, port, phy, &dataL))
            != MTD_OK)
        {
            MTD_DBG_ERROR("Reading from reg %x failed.\n",addr);
            return(retVal | MTD_API_FAIL_WRITE_REG);
        }

        phy = (1<<16)|0xC04C;
        if((retVal = _mtdHwReadPhyReg(dev, port, phy, &dataH))
            != MTD_OK)
        {
            MTD_DBG_ERROR("Reading from reg %x failed.\n",addr);
            return(retVal | MTD_API_FAIL_WRITE_REG);
        }

        *data = (dataH << 16) + (dataL & 0xFFFF);
#ifdef DEBUG
        MTD_DBG_CRITIC_INFO("mtdMsecReadReg                 : Addr %04x Data %08x\n", addr, (MTD_UINT)*data);
#endif
        if(MTD_DEBUG_MSEC_READ == 1)
        {
            MTD_DBG_CRITIC_INFO("mtdMsecReadPortReg                 : port %d Addr %04x Data %08x\n", port, addr, (MTD_UINT)*data);
        }
    }
    else
    {
    /* The read procedure requires 3 MDIO reads for each 32-bit LinkCrypt registers */
    /* 1. send read request for address */
        phy = (MTD_MACSEC_DEV_ADDR<<16)|addr;
        if((retVal = _mtdHwReadPhyReg(dev, port, phy,&dataL))
            != MTD_OK)
        {
            MTD_DBG_ERROR("Reading from reg %x failed.\n",addr);
            return(retVal | MTD_API_FAIL_WRITE_REG);
        }
        if(indirect == 1)
        {
            phy = (MTD_MACSEC_DEV_ADDR<<16)|0x97FD;
            for(i=0;i<100;i++)
            {
                if((retVal = _mtdHwReadPhyReg(dev, port, phy,&dataL))
                    != MTD_OK)
                {
                    MTD_DBG_ERROR("Reading from reg %x failed.\n",addr);
                    return(retVal | MTD_API_FAIL_WRITE_REG);
                }
                if((dataL & 0xFFFF) == addr)
                    break;
            }

        /* 2. read indirect_read_data_low */
            phy = (MTD_MACSEC_DEV_ADDR<<16)|0x97FE;
            if((retVal = _mtdHwReadPhyReg(dev, port, phy, &dataL))
                != MTD_OK)
            {
                MTD_DBG_ERROR("Reading from reg %x failed.\n",addr+1);
                return(retVal | MTD_API_FAIL_WRITE_REG);
            }
        /* 3. read indirect_read_data_high */
            phy = (MTD_MACSEC_DEV_ADDR<<16)|0x97FF;
            if((retVal = _mtdHwReadPhyReg(dev, port,  phy, &dataH))
                != MTD_OK)
            {
                MTD_DBG_ERROR("Reading from reg %x failed.\n",addr+1);
                return(retVal | MTD_API_FAIL_WRITE_REG);
            }
        }
        else
        {
            phy = (MTD_MACSEC_DEV_ADDR<<16)|addr;
            retVal = _mtdHwReadPhyReg(dev, port, phy,&dataL);
            retVal = _mtdHwReadPhyReg(dev, port, phy+1, &dataH);
        }
        *data = (dataH << 16) + (dataL & 0xFFFF);

#ifdef DEBUG
        MTD_DBG_CRITIC_INFO("mtdMsecReadReg                 : Addr %04x Data %08x\n", addr, (MTD_UINT)*data);
#endif
        if(MTD_DEBUG_MSEC_READ == 1)
        {
            MTD_DBG_CRITIC_INFO("mtdMsecReadPortReg                 : port %d Addr %04x Data %08x\n", port, addr, (MTD_UINT)*data);
        }

    }

    return MTD_OK;

}



/*******************************************************************************
* mtdMsecWritePortReg
*
* DESCRIPTION:
*       This routine write Port register.
*
* INPUTS:
*       dev  - pointer to MTD driver structure returned from mtdLoadDriver
*       port        - The port number.
*       addr - MacSec register addr.
*       data - data value to be written
*   
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtdMsecWritePortReg 
(
    IN  MTD_DEV    *dev,
    IN  MTD_U16    port,
    IN  MTD_U16    addr,
    IN  MTD_U32    data
)
{
    MTD_STATUS ret;
    mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
    if(mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    ret = _mtdMsecWritePortReg(dev,port,addr,data);
    if(mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtdSemGive(dev,dev->multiAddrSem);
    /*ret = mtd_msec_64bit_write (addr);
    if (ret != MTD_OK)
      printf ("!!!! writing register 0x%x takes 64-bit to complete!\n", addr);*/
    return ret;
}

/*******************************************************************************
* mtdMsecReadPortReg
*
* DESCRIPTION:
*       This routine read Port register.
*
* INPUTS:
*       dev  - pointer to MTD driver structure returned from mtdLoadDriver
*       port        - The port number.
*       addr - MacSec register addr.
*   
* OUTPUTS:
*       data - read data value
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtdMsecReadPortReg 
(
    IN  MTD_DEV    *dev,
    IN  MTD_U16    port,
    IN  MTD_U16   addr,
    OUT MTD_U32   *data
)
{
    MTD_STATUS ret;
    mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
    if(mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    ret = _mtdMsecReadPortReg(dev,port,addr,data);
    if(mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtdSemGive(dev,dev->multiAddrSem);
    return ret;
}

/*******************************************************************************
* mtdMsecWritePortReg_64
*
* DESCRIPTION:
*       This routine write Port register.for 64 bits data
*
* INPUTS:
*       dev  - pointer to MTD driver structure returned from mtdLoadDriver
*       port        - The port number.
*       addr - MacSec register addr.
*       dataL - data value to be written(lower 32 bits)
*       dataH - data value to be written(higher 32 bits)
*   
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtdMsecWritePortReg_64 
(
    IN  MTD_DEV    *dev,
    IN  MTD_U16    port,
    IN  MTD_U16    addr,
    IN  MTD_U32    dataL,
    IN  MTD_U32    dataH
)
{
    MTD_STATUS ret;
    mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
    if(mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    ret = _mtdMsecWritePortReg_64(dev,port,addr,dataL, dataH);
    if(mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtdSemGive(dev,dev->multiAddrSem);
    return ret;
}


/*******************************************************************************
* mtd_msecPtpWriteReg
*
* DESCRIPTION:
*       This routine write data Value to MTD MacSec register address.
*
* INPUTS:
*       port - port number.
*       addr - MTD MacSec register addr.
*       data - data value to be written
*   
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS _mtd_msecPtpWriteReg 
(
    IN  MTD_DEV    *dev,
    IN  MTD_U16    port,
    IN  MTD_U16    addr,
    IN  MTD_U32    data
)
{
    MTD_STATUS   retVal = MTD_OK;
    if(_mtdMsecWritePortReg(dev, port, addr, data)!=MTD_OK)
        retVal = MTD_FAIL;
    return retVal;
}
MTD_STATUS mtd_msecPtpWriteReg 
(
    IN  MTD_DEV    *dev,
    IN  MTD_U16    port,
    IN  MTD_U16    addr,
    IN  MTD_U32    data
)
{
    MTD_STATUS   retVal = MTD_OK;
    mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
    if(mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    retVal = _mtd_msecPtpWriteReg(dev, port, addr,data);
    if(mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtdSemGive(dev,dev->multiAddrSem);
    return retVal;
}

/*******************************************************************************
* mtd_msecPtpReadReg
*
* DESCRIPTION:
*       This routine read data Value to MTD MacSec register address.
*
* INPUTS:
*       port - port number.
*       addr - MTD MacSec register addr.
*   
* OUTPUTS:
*       data - data value to be written
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS _mtd_msecPtpReadReg 
(
    IN  MTD_DEV    *dev,
    IN  MTD_U16    port,
    IN  MTD_U16    addr,
    OUT MTD_U32   *data
)
{
    MTD_STATUS   retVal = MTD_OK;
    if(_mtdMsecReadPortReg(dev, port, addr, data)!=MTD_OK)
        retVal = MTD_FAIL;
/*  MTD_DBG_INFO("msecPtpReadReg: Addr %x Data %x\n", addr, (MTD_UINT)*data); */
    return retVal;
}

MTD_STATUS mtd_msecPtpReadReg 
    (
    IN  MTD_DEV    *dev,
    IN  MTD_U16    port,
    IN  MTD_U16    addr,
    OUT MTD_U32   *data
    )
{
    MTD_STATUS   retVal = MTD_OK;
    mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
    if(mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    retVal = _mtd_msecPtpReadReg(dev, port, addr, data);
    if(mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtdSemGive(dev,dev->multiAddrSem);
    return retVal;
}

MTD_UINT _mtd_ptp_read_reg 
(
    MTD_U16 port, 
    MTD_U16 addr
)
{
    MTD_STATUS   retVal;
    MTD_U32      data;
    MTD_DEV_PTR  devPtr;

    devPtr = mtdGetMTDDev();
    if(devPtr == NULL)
    {
        MTD_DBG_ERROR("mtdGetMTDDev returns NULL devPtr.\n");
        return MTD_FAIL;
    }

    retVal  = _mtd_msecPtpReadReg(devPtr, port, addr, &data);
    if(retVal == MTD_OK)
        return data;
    else
    {
        MTD_DBG_INFO("Reading from ptp reg (%x) failed.\n",addr);
        return 0;
    }
}
MTD_UINT mtd_ptp_read_reg 
(
    MTD_U16 port, 
    MTD_U16 addr
 )
{
    MTD_UINT    data;
    MTD_DEV_PTR  devPtr;

    devPtr = mtdGetMTDDev();
    if(devPtr == NULL)
    {
        MTD_DBG_ERROR("mtdGetMTDDev returns NULL devPtr.\n");
        return MTD_FAIL;
    }

    mtdSemTake(devPtr, devPtr->multiAddrSem, OS_WAIT_FOREVER);
    if(mtd_ptp_msec_set_link_down_reset(port,0)!= MTD_OK)
    {
        mtdSemGive(devPtr, devPtr->multiAddrSem);
        MTD_DBG_ERROR("mtd_ptp_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }

    data  = _mtd_ptp_read_reg(port, addr);
    if(mtd_ptp_msec_set_link_down_reset(port,1)!= MTD_OK)
    {
        mtdSemGive(devPtr, devPtr->multiAddrSem);
        MTD_DBG_ERROR("mtd_ptp_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }

    mtdSemGive(devPtr, devPtr->multiAddrSem);
    return data;
}


MTD_STATUS _mtd_ptp_write_reg 
(
    MTD_U16 port, 
    MTD_U16 addr, 
    MTD_UINT data
 )
{
    MTD_STATUS   retVal;
    MTD_DEV_PTR  devPtr;

    devPtr = mtdGetMTDDev();
    if(devPtr == NULL)
    {
        MTD_DBG_ERROR("mtdGetMTDDev returns NULL devPtr.\n");
        return MTD_FAIL;
    }

    retVal  = _mtd_msecPtpWriteReg(devPtr, port, addr, data); 
    if(retVal != MTD_OK)
    {
        MTD_DBG_INFO("Wring to ptp reg (%x) failed.\n",addr);
    }
    return retVal;
}

MTD_STATUS mtd_ptp_write_reg 
(
    MTD_U16 port, 
    MTD_U16 addr, 
    MTD_UINT data
 )
{
    MTD_STATUS   retVal;
    MTD_DEV_PTR  devPtr;

    devPtr = mtdGetMTDDev();
    if(devPtr == NULL)
    {
        MTD_DBG_ERROR("mtdGetMTDDev returns NULL devPtr.\n");
        return MTD_FAIL;
    }

    mtdSemTake(devPtr, devPtr->multiAddrSem, OS_WAIT_FOREVER);

    if(mtd_ptp_msec_set_link_down_reset(port,0)!= MTD_OK)
    {
        mtdSemGive(devPtr, devPtr->multiAddrSem);
        MTD_DBG_ERROR("mtd_ptp_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    retVal  = _mtd_ptp_write_reg(port, addr, data); 
    if(mtd_ptp_msec_set_link_down_reset(port,1)!= MTD_OK)
    {
        mtdSemGive(devPtr, devPtr->multiAddrSem);
        MTD_DBG_ERROR("mtd_ptp_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }

    mtdSemGive(devPtr, devPtr->multiAddrSem);
    return retVal;
}


MTD_UINT mtd_ptp_readcheck_reg 
(
    MTD_U16 port, 
    MTD_U16 addr
 )
{
    MTD_INT trycount = 0;
    MTD_UINT val = mtd_ptp_read_reg (port, addr);
    MTD_UINT data =  ~val;
    while(data != val)
    {
        data = val;
        val = mtd_ptp_read_reg (port, addr);
        MTD_DBG_INFO("try %d: read 0x%x from address 0x%x, old val 0x%x in port %d.\n", trycount, val, addr, data, port);
        trycount = trycount+1;
        if(trycount > 10)
        {
            MTD_DBG_INFO("Error: too many tries!\n");
            break;
        }
    }
    return val;
}

MTD_STATUS mtd_ptp_writecheck_reg
(
    MTD_U16 port, 
    MTD_U16 addr, 
    MTD_UINT data
 )
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT val = ~data;
    MTD_U16  trycount = 0;
    while(data != val)
    {
        retVal = mtd_ptp_write_reg(port, addr, data);
        val = mtd_ptp_read_reg(port, addr);
/*    MTD_DBG_INFO("try %d: wrote 0x%x to address 0x%x, read back 0x%x in port %d.\n",  */
/*            trycount, data, addr, val, port); */
        trycount = trycount+1;
        if(trycount > 10)
        {
            MTD_DBG_INFO("Error: too many tries!\n");
            break;
        }
    }
    return retVal;
}







