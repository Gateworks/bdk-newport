/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions for initializing the driver and setting 
up the user-provide MDIO access functions for the Marvell 88X32X0, 
88X33X0, 88E20X0 and 88E21X0 ethernet PHYs.
********************************************************************/
#include "mtdApiTypes.h"
#include "mtdSemaphore.h"
#include "mtdMsecPtpApiDefs.h"
#include "mtdMsecInternal.h"
#include "mtdMsecApi.h"
#include "mtdInitialization.h"
#include "mtdHwCntl.h"

/*******************************************************************************
*
********************************************************************************/

MTD_STATUS mtdLoadDriver
(
    IN FMTD_READ_MDIO     readMdio,    
    IN FMTD_WRITE_MDIO    writeMdio,   
    IN MTD_BOOL           macsecIndirectAccess, 
    IN FMTD_SEM_CREATE    semCreate,     
    IN FMTD_SEM_DELETE    semDelete,    
    IN FMTD_SEM_TAKE      semTake,    
    IN FMTD_SEM_GIVE      semGive,
    IN MTD_U16            anyPort,    
    OUT MTD_DEV          *dev
)
{
    MTD_U16 data;

    MTD_DBG_INFO("mtdLoadDriver Called.\n");

    /* Check for parameters validity        */
#if 0 /* allow to be called with NULL for IO functions, in case host wants to implement their own and not use the */
      /* ones inside the MTD_DEV struct */
    if(readMdio == NULL || writeMdio == NULL )
    {
        MTD_DBG_ERROR("MDIO read or write pointers are NULL.\n");
        return MTD_API_ERR_SYS_CFG;
    }
#endif


    /* Check for parameters validity        */
    if(dev == NULL)
    {
        MTD_DBG_ERROR("MTD_DEV pointer is NULL.\n");
        return MTD_API_ERR_DEV;        
    }
    
    /* The initialization was already done. */
    if(dev->devEnabled)
    {
        MTD_DBG_ERROR("Device Driver already loaded.\n");
        return MTD_API_ERR_DEV_ALREADY_EXIST;
    }

    /* Make sure mtdWait() was implemented */
    if (mtdWait(dev,1) == MTD_FAIL)
    {
        MTD_DBG_ERROR("mtdWait() not implemented.\n");        
        return MTD_FAIL;        
    }

    dev->fmtdReadMdio =  readMdio;
    dev->fmtdWriteMdio = writeMdio;

    dev->semCreate = semCreate;
    dev->semDelete = semDelete;
    dev->semTake   = semTake;
    dev->semGive   = semGive;
    dev->macsecIndirectAccess = macsecIndirectAccess;  /* 88X33X0 and later force direct access */


    if((mtdHwXmdioRead(dev, anyPort,1,0 ,&data))!= MTD_OK) /* try to read 1.0 */
    {
        MTD_DBG_ERROR("Reading to reg %x failed.\n",0);
        mtdUnloadDriver(dev);
        return MTD_API_FAIL_READ_REG;
    }

    if (data == 0x0000 || data == 0xFFFF)
    {
        MTD_DBG_ERROR("Reading to reg %x failed.\n",0);
        mtdUnloadDriver(dev);
        return MTD_API_FAIL_READ_REG;
    }
  
    /* MTD_DBG_INFO("mtdLoadDriver successful.\n"); */

    /* Initialize the MACsec Register Access semaphore.    */
    if((dev->multiAddrSem = mtdSemCreate(dev,MTD_SEM_FULL)) == 0)
    {
        MTD_DBG_ERROR("semCreate Failed.\n");
        mtdUnloadDriver(dev);
        return MTD_API_FAIL_SEM_CREATE;
    }

    if (dev->msec_ctrl.msec_rev == MTD_MSEC_REV_FPGA)
    {
        dev->deviceId = MTD_REV_3310P_A0; /* verification: change if needed */
        dev->numPorts = 1; /* verification: change if needed */
        dev->thisPort = 0;
    } 
    else
    {
        /* After everything else is done, can fill in the device id */
        if ((mtdGetPhyRevision(dev, anyPort, 
                               &(dev->deviceId), 
                               &(dev->numPorts), 
                               &(dev->thisPort))) != MTD_OK)
        {
            MTD_DBG_ERROR("mtdGetPhyRevision Failed.\n");
            mtdUnloadDriver(dev);
            return MTD_FAIL;
        }
    }
    
    if (MTD_IS_X33X0_BASE(dev->deviceId))
    {
        dev->macsecIndirectAccess = MTD_FALSE; /* bug was fixed in 88X33X0 and later revisions, go direct */   
    }

#if (MTD_CLAUSE_22_MDIO == 1) 
    if (!MTD_IS_X33X0_BASE(dev->deviceId) && !MTD_IS_E21X0_BASE(dev->deviceId))
    {
        mtdUnloadDriver(dev);
        return MTD_FAIL; /* Clause 45 using Clause 22 is only available in 88X33X0 and later phys */   
    }
#endif

    dev->devEnabled = MTD_TRUE;

    MTD_DBG_INFO("mtdLoadDriver successful.\n");

    return MTD_OK;
}

/*******************************************************************************
* mtdUnloadDriver
*
* DESCRIPTION:
*       This function clears MTD_DEV structure.
*
* INPUTS:
*       None.
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       MTD_OK           - on success
*       MTD_FAIL         - on error
*
* COMMENTS:
*       1.  This function should be called only after successful execution of
*           mtdLoadDriver().
*
*******************************************************************************/
MTD_STATUS mtdUnloadDriver
(
    IN MTD_DEV* dev
)
{
    MTD_DBG_INFO("mtdUnloadDriver Called.\n");

    /* Delete the MACsec register access semaphore.    */
    if(mtdSemDelete(dev,dev->multiAddrSem) != MTD_OK)
    {
        MTD_DBG_ERROR("SemDelete Failed.\n");
        return MTD_API_FAIL_SEM_DELETE;
    }

    dev->fmtdReadMdio =  NULL;
    dev->fmtdWriteMdio = NULL;

    dev->semCreate = NULL;
    dev->semDelete = NULL;
    dev->semTake   = NULL;
    dev->semGive   = NULL;

    dev->devEnabled = MTD_FALSE;

    return MTD_OK;
}

