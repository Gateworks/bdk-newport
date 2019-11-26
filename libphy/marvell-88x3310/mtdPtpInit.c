/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************************
* mtd_ptp_init.c
* 
* DESCRIPTION:
*       Functions to access platform layer by PTP in MacSec control program.
*
* DEPENDENCIES:
*       None.
*
* FILE REVISION NUMBER:
*       $Revision: 1 $
*
*******************************************************************************/

#include "mtdApiTypes.h"
#include "mtdHwCntl.h"
#include "mtdSemaphore.h"
#include "mtdMsecPtpApiDefs.h"
#include "mtdMsecApi.h"
#include "mtdHwMsecPtpCntl.h"
#include "mtdMsecTypes.h"
#include "mtdAPIInternal.h"
#include "mtdPtp1step.h"

static MTD_DEV       *mtd_ptp_mtddev;

 /* 1-step PTP in 10G Phy 2242 */
#include "mtdMsecInternal.h"

/*******************************************************************************
* mtd_ptp_dev_init
*
* DESCRIPTION:
*     Initialization of PTP block. 
*
* INPUTS:
*       dev  - pointer to MTD driver structure returned from mtdLoadDriver
*       port - port number
*       link_mode - MTD running mode.
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
MTD_STATUS mtd_ptp_dev_init(void * dev, MTD_U16 port, int link_mode)
{
    MTD_STATUS   retVal = MTD_OK;

    mtd_ptp_mtddev = (MTD_DEV *)dev;

//  retVal = mtd_init_macsec(port, link_mode);  

    return retVal;
}  

MTD_STATUS mtd_ptp_msec_set_link_down_reset(MTD_U16 port, int flag)
{
    return(mtd_msec_set_link_down_reset(mtd_ptp_mtddev, port, flag));
}

MTD_STATUS mtd_ptp_msec_sem_take(MTD_U32 timeOut)
{
    return     mtdSemTake(mtd_ptp_mtddev,mtd_ptp_mtddev->multiAddrSem,timeOut);
}

MTD_STATUS mtd_ptp_msec_sem_give()
{
    return     mtdSemGive(mtd_ptp_mtddev,mtd_ptp_mtddev->multiAddrSem);
}


/* Set bits by ORing new value with old value */
MTD_STATUS mtd_set_bits (MTD_U16 port, MTD_U16 addr, MTD_UINT data)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT val = mtd_ptp_read_reg(port, addr)|data;
    retVal = mtd_ptp_writecheck_reg(port, addr, val);
    return retVal;
}

/* Set bits by ANDing inverse of new value with old value */
MTD_STATUS mtd_clear_bits (MTD_U16 port, MTD_U16 addr, MTD_UINT data)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT val = mtd_ptp_read_reg(port, addr)&~data;
    retVal = mtd_ptp_writecheck_reg(port, addr, val );
    return retVal;
}

/* Workaround procedures */
MTD_STATUS mtd_init_macsec (MTD_U16 port, int link_mode)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_DEV_PTR  devPtr;

    retVal = mtd_ptp_writecheck_reg(port, 0x803a, 0xab018d0c);
    if(retVal != MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, 0x803c, 0x5488eeec);
    if(retVal != MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, 0x8008, 0x0000ddad);
    if(retVal != MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, 0x800a, 0xaddbadca);
    if(retVal != MTD_OK) return retVal;    

    devPtr = mtdGetMTDDev();
    if(devPtr == NULL)
    {
        MTD_DBG_ERROR("mtdGetMTDDev returns NULL devPtr.\n");
        return MTD_FAIL;
    }
       if (MTD_IS_X33X0_BASE(devPtr->deviceId))
      retVal = mtd_ptp_writecheck_reg(port, 0x8000, 0x7dd00f3b);
    else
    {
        if(link_mode == 0)
        {
            retVal = mtd_ptp_writecheck_reg(port, 0x8000, 0x7c500f30);
        }
        else
        {
            retVal = mtd_ptp_writecheck_reg(port, 0x8000, 0x7c500f33);
        }
    }
   
    if(retVal != MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, 0x80a2, 0x00000020);
    if(retVal != MTD_OK) return retVal;
    if (MTD_IS_X32X0_BASE(devPtr->deviceId))
    {
        retVal = mtd_ptp_writecheck_reg(port, 0x800e, 0x00000004);
        if(retVal != MTD_OK) return retVal;
    }

    retVal = mtd_ptp_writecheck_reg(port,MTD_SI_EGR_PKT_SZ, 0xC25 );
    if(retVal != MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port,MTD_SI_EGR_THR, 0x200 );
    if(retVal != MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port,MTD_SI_EGR_RC0, 0x1DFFB1 );
    if(retVal != MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port,MTD_SI_EGR_RC1, 0x88E50000 );
    if(retVal != MTD_OK) return retVal;

    retVal = mtd_ptp_writecheck_reg(port, MTD_SI_IGR_PKT_SZ, 0x60EF);
    if(retVal != MTD_OK) return retVal;

    /* Commented out below code since this will cause packet drop on ingress path 
       when drop badtag is enabled. [102115] */
    /*
    retVal = mgd_ptp_writecheck_reg(port, MGD_SI_IGR_CHK_ACT, 0xf );
    if(retVal != MGD_OK) return retVal;  
    */
    /* max timer to avoid timeout on 0x1B8x registers */
    mtd_msec_set_mdio_watchdog_timer (devPtr, port, 1, 0x1007);
    /* workaround for ppm tolerance */
    retVal = mtd_msec_set_10g_mac_ipgMode_ipgVal(devPtr, port, 2, MTD_SMAC, 8);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtd_init_macsec: mtd_msec_set_10g_mac_ipgMode_ipgVal on MTD_SMAC failed\n");
        return(retVal);
    }

    retVal = mtd_msec_set_10g_mac_ipgMode_ipgVal(devPtr, port, 2, MTD_WMAC, 8);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtd_init_macsec: mtd_msec_set_10g_mac_ipgMode_ipgVal on MTD_WMAC failed\n");
        return(retVal);
    }

    return retVal;
}

/*******************************************************************************
* mtdGetMTDDev
*
* DESCRIPTION:
*       This function returns the static defined MTD Dev object.
*
* INPUTS:
*       None
*
* OUTPUTS:
*       None
*
* RETURNS:
*       Returns MTD_DEV if success
*       Returns NULL pointer if mtd_ptp_mtddev in NULL
*
* COMMENTS:
*       
*
*******************************************************************************/
MTD_DEV_PTR mtdGetMTDDev(void)
{
    if(mtd_ptp_mtddev)
    {
        return mtd_ptp_mtddev;
    }

    return NULL;
}



