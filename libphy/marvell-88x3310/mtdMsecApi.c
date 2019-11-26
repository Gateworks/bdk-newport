/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains MACsec functions for initializing the MACsec 
operations and setting various features for the Marvell 88X32X0, 
88X33X0 and 88E20X0 ethernet PHYs.
********************************************************************/
#include "mtdApiTypes.h"
#include "mtdHwCntl.h"
#include "mtdSemaphore.h"
#include "mtdMsecPtpApiDefs.h"
#include "mtdAPIInternal.h"
#include "mtdHwCntl.h"

#include "mtdMsecInternal.h"
#include "mtdMsecApi.h"
#include "mtdMsecTypes.h"
#include "mtdMsecPtpDrvRegs.h"
#include "mtdHwMsecPtpCntl.h"
#include "mtdAPI.h"

/*#ifdef LINUX */
#ifdef __KERNEL__ 
#include "linux/kernel.h"
#endif

/* #define DEBUG 1 */
#undef DEBUG

/*******************************************************************************
* mtd_msec_ae_init
*
* DESCRIPTION:
*        \brief Initialize AE core
*        Brings core out of reset and into a basic bypass configuration with all
*        traffic passing through the core.  In this state the core is ready to begin
*        encrypt and decrypt operations.
*
* INPUTS:
*       \param dev pointer to MTD driver structure returned from mtdLoadDriver
*                (2 -> 1000 Mbps, 1 -> 100 Mbps, 0 -> 10 Mbps)
*
* OUTPUTS:
*        None
*
* RETURNS:
*       \return MTD_OK on success, MTD_FAIL on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_ae_init
(
    IN  MTD_DEV     *dev,
    IN  MTD_U16     port
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_INT bypass_macsec, fwd_mode;  

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    mtd_msec_dev_init(dev);

  /* Set Mac power on */
    mtd_msec_set_mac_power_mode (dev, port, MTD_MACSEC_POWER_MODE_ACTIVE);

  /* bypass_macsec = 0, fwd_mode = store-forward */
    bypass_macsec = 0;
    fwd_mode = 2;

    MTD_DBG_CRITIC_INFO("!!!! mtd_msec_ae_init \n");

  /* MacSec Configuration */
    MTD_DBG_CRITIC_INFO("!!!! MacSec Configuration  port %d \n", port);

  /* AE core init */
    retVal = mtd_init_linkcrypt(dev, port, bypass_macsec, fwd_mode);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtd_init_linkcrypt Failed\n");
        return(retVal);
    }

    /* Disable constant latency for lockup workaround */
    retVal = mtd_msec_set_constant_latency(port, 0);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtd_msec_ae_init: mtd_msec_set_constant_latency failed\n");
        return(retVal);
    }

    /*  MACsec rate matching mode workaround */
    if (MTD_IS_X33X0_BASE(dev->deviceId))
    {
        /* set MACsec XOFF/XON to 32% */
        retVal = mtd_msec_set_egr_xoff_xon_threshold(dev, port, 0x140, 0xA0);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("mtd_msec_ae_init: mtd_msec_set_egr_xoff_xon_threshold failed\n");
            return(retVal);
        }

        /* set MACsec XOFF/XON to 32% */
        retVal = mtd_msec_set_igr_xoff_xon_threshold(dev, port, 0x140, 0xA0);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("mtd_msec_ae_init: mtd_msec_set_igr_xoff_xon_threshold failed\n");
            return(retVal);
        }

        /* workaround for MACsec egress flow control drop threshold to 86% */
        mtd_msec_set_egr_flow_ctrl_drop_thrh(dev, port, 0x370, 0x100, 1);

        /* workaround for MACsec ingress flow control drop threshold to 86% */  
        mtd_msec_set_igr_flow_ctrl_drop_thrh(dev, port, 0x370, 0x100, 0x8, 0x4, 1);

        /* Enable periodic pause trigger */
        retVal = mtd_msec_periodic_pause(dev, port, 1);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("mtd_msec_ae_init: mtd_msec_periodic_pause failed\n");
            return(retVal);
        }
    }

    /* workaround for ppm tolerance */
    retVal = mtd_msec_set_10g_mac_ipgMode_ipgVal(dev, port, 2, MTD_SMAC, 8);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtd_msec_ae_init: mtd_msec_set_10g_mac_ipgMode_ipgVal on MTD_SMAC failed\n");
        return(retVal);
    }

    retVal = mtd_msec_set_10g_mac_ipgMode_ipgVal(dev, port, 2, MTD_WMAC, 8);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtd_msec_ae_init: mtd_msec_set_10g_mac_ipgMode_ipgVal on MTD_WMAC failed\n");
        return(retVal);
    }

    MTD_DBG_CRITIC_INFO("!!!! mtd_msec_ae_init done\n");
    return retVal;

}

/*****************************************************************************
* mtd_msec_set_fwd_mode
*
* DESCRIPTION:
*       set forward mode: 
*
* INPUTS:
*        dev - pointer to device handle
*    fwd_mode - fowarding mode
*        - 2'b00= cut-through; 
*        - 2'b01=egr store-foward; 
*        - 2'b10=igr store-foward;
*        - 2'b11 = store-forward;
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
MTD_STATUS mtd_msec_set_fwd_mode
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT fwd_mode
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_SLC_CFG_GEN;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, fwd_mode, 3, 2);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }
    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_mac_power_mode
*
* DESCRIPTION:
   set mac power mode
*
* INPUTS:
*    dev - pointer to device handle
*    mode - 
*            MTD_MACSEC_POWER_MODE_POWEROFF     
*            MTD_MACSEC_POWER_MODE_RESET     
*            MTD_MACSEC_POWER_MODE_SLEEP      
*            MTD_MACSEC_POWER_MODE_ACTIVE    
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
void mtd_msec_set_mac_power_mode 
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_MACSEC_POWER_MODE _mode
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_MACSEC_BYPASS_MODE    mode = _mode;
    retVal = mtdPortSetMacsecBypass(dev, port, mode);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("Get Mac power mode failed");
    }
}
/*****************************************************************************
*  mtd_msec_get_mac_power_mode
*
* DESCRIPTION:
   get mac power mode
*
* INPUTS:
*    dev - pointer to device handle
* 
* OUTPUTS:
*    mode - 
*            MTD_MACSEC_POWER_MODE_POWEROFF     
*            MTD_MACSEC_POWER_MODE_RESET     
*            MTD_MACSEC_POWER_MODE_SLEEP      
*            MTD_MACSEC_POWER_MODE_ACTIVE    
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
int mtd_msec_get_mac_power_mode 
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_MACSEC_POWER_MODE *_mode
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_MACSEC_BYPASS_MODE    mode;
    retVal = mtdPortGetMacsecBypass(dev, port, &mode);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("Get Mac power mode failed");
        return(-1);             
    }
    *_mode = mode;
    return(mode);
}

/*****************************************************************************
*  mtd_set_mac_speed
*
* DESCRIPTION:
   set mac link speed
*
* INPUTS:
*    dev - pointer to device handle
*    mac_type - mac type: 1 - MTD_SMAC, 2 -MTD_WMAC
*    speed - link speed : 0 - MTD_GMII, 1 - MTD_XGMII
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
MTD_STATUS mtd_set_mac_speed 
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT mac_type,
    MTD_INT speed
)
{
    MTD_STATUS   retVal = MTD_OK;
    /*       
       starting from X3340/X3320/X3310, MAC speeds supported are: 10G, 5G, 2.5G, 1G, 100M, 10M
       and MAC interface use 1G speed configuration for all lower speed 1G/100M/10M
    */
    MTD_U32 slc_cfg_gen;
    MTD_U32 pause_ctl;
    MTD_U16 addr = 0;

    if (mac_type != 1 && mac_type != 2)
    {
        MTD_DBG_ERROR("invalid mac_type parameter, mac_type = 1 for MTD_SMAC, 2 for MTD_WMAC");
        return MTD_FAIL;
    }
    if (MTD_IS_X32X0_BASE(dev->deviceId))
    {
      if (speed != 0 && speed != 1)
      {
        MTD_DBG_ERROR("invalid speed parameter, speed = 0 for MTD_GMII, 1 for MTD_XGMII");
        return MTD_FAIL;
      }

      /* set xg_select in slc_cfg_gen */
      retVal= mtdMsecReadPortReg(dev, port, MTD_SLC_CFG_GEN, &slc_cfg_gen);
      if (retVal != MTD_OK)
      {
          MTD_DBG_ERROR("MSEC Read Failed\n");
          return(retVal);
      }

      /* program sysmac / wire mac */
      if (mac_type == MTD_SMAC)
      {
        mtd_msec_bit_write (slc_cfg_gen, speed, 1);
        addr =  MTD_SMAC_REG;
      }
      else if (mac_type == MTD_WMAC) /* MTD_WMAC */
      {
        mtd_msec_bit_write (slc_cfg_gen, speed, 0);
        addr =  MTD_WMAC_REG;
      }
      retVal = mtdMsecWritePortReg (dev, port, MTD_SLC_CFG_GEN, slc_cfg_gen);
    }
    else if (MTD_IS_X33X0_BASE(dev->deviceId))
    {
        if (speed != MTD_MSEC_SPEED_MII_10M && speed != MTD_MSEC_SPEED_MII_100M && speed != MTD_MSEC_SPEED_GMII_1G && speed != MTD_MSEC_SPEED_XGMII_10G && speed != MTD_MSEC_SPEED_XGMII_5G && speed != MTD_MSEC_SPEED_XGMII_2P5G)
        {
            MTD_DBG_ERROR("invalid speed parameter\n");
            return MTD_FAIL;
        }
        
        /* check aneg_en bits in slc_cfg_gen */
        retVal= mtdMsecReadPortReg(dev, port, MTD_SLC_CFG_GEN, &slc_cfg_gen);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Read Failed\n");
            return(retVal);
        }
        if (mtd_msec_bits_get (slc_cfg_gen, 24, 23) == 3)
        {
            /* aneg_en bits set. no need to set MAC speed */
            MTD_DBG_ERROR ("MSEC slc_cfg_gen aneg_en is set, shall disable aneg before config MAC speed.");
            return MTD_FAIL;
        }
        retVal= mtdMsecReadPortReg(dev, port, MTD_SLC_CFG_PAUSE_CTL, &pause_ctl);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Read Failed\n");
            return(retVal);
        }
        /* program sysmac / wire mac */
        if (mac_type == MTD_SMAC)
        {
            mtd_msec_bits_write (&pause_ctl, speed, 13, 11);
            addr =  MTD_SMAC_REG;
        }
        else if (mac_type == MTD_WMAC) /* MTD_WMAC */
        {
            mtd_msec_bits_write (&pause_ctl, speed, 10, 8);
            addr =  MTD_WMAC_REG;
        }
        retVal = mtdMsecWritePortReg (dev, port, MTD_SLC_CFG_PAUSE_CTL, pause_ctl);
    }
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }
    
    if (MTD_IS_X32X0_BASE(dev->deviceId))
    {
        if (speed == MTD_XGMII)
        {
            MTD_U32 mac_ctrl;
            /* MTD_XGMII mode
               crc check enable, set 8B preamble. */
            retVal= mtdMsecReadPortReg(dev, port, addr, &mac_ctrl);
            if (retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Read Failed\n");
                return(retVal);
            }
            mtd_msec_bit_set (mac_ctrl, 11);
            mtd_msec_bit_set (mac_ctrl, 9);
            retVal = mtdMsecWritePortReg (dev, port, addr, mac_ctrl);
            if (retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Write Failed\n");
                return(retVal);
            }
     }    
    }

    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_mac_framesize
*
* DESCRIPTION:
*   set mac frame size
*
* INPUTS:
*    dev - pointer to device handle
*    mactype - mac type: 1 - MTD_SMAC, 2 -MTD_WMAC
*    size - frame size
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
/* mactype: MTD_SMAC=1, MTD_WMAC=2 */
MTD_STATUS mtd_msec_set_mac_framesize 
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT mactype, 
    MTD_INT size
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;
    MTD_INT xg_sel;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    if (mactype == MTD_SMAC)
        addr =  MTD_SMAC_REG;
    else if (mactype == MTD_WMAC)
        addr =  MTD_WMAC_REG;
    else
        return MTD_FAIL;
    xg_sel = mtd_msec_get_mac_xg_sel(dev, port, mactype);
    if (xg_sel == MTD_XGMII)
    {
        addr  +=  MTD_MAC_CTL1;
        retVal = mtdMsecReadPortReg(dev, port, addr, &data);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Read Failed\n");
            return(retVal);
        }
        mtd_msec_bits_write(&data, size, 12, 0);
        retVal = mtdMsecWritePortReg(dev, port, addr, data);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return(retVal);
        }
    }
    else if (xg_sel == MTD_GMII)
    {
        retVal = mtdMsecReadPortReg(dev, port, addr, &data);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Read Failed\n");
            return(retVal);
        }
        mtd_msec_bits_write(&data, size, 14, 2);
        retVal = mtdMsecWritePortReg (dev, port, addr, data);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return(retVal);
        }
    }
    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_10g_mac_pause_fwd
*
* DESCRIPTION:
*   set 10G mac MACsec pause forwarding
*
* INPUTS:
*    dev - pointer to device handle
*    mactype - mac type: 1 - MTD_SMAC, 2 -MTD_WMAC
*    flag - pause forwarding flag: 1 = forward pause, 0 = No forward pause
* 
* OUTPUTS:
*    None
*
* RETURNS:
*    MTD_OK          - on success
*    MTD_FAIL        - on error
*
* COMMENTS:
*    Enable pause forwarding on SMAC or WMAC when link speed is 10G,5G and 
*    2.5G. This API does not apply to 1G and lower speed.
*    
*    By default, when flow control is not enabled, pause frames are 
*    terminated in MAC.
*
*    When flow control is not enabled, pause frames can be forwarded this 
*    flag is set
*
*    When flow control is enabled, pause frames are terminated regardless of 
*    setting of this flag.
*******************************************************************************/
MTD_STATUS mtd_msec_set_10g_mac_pause_fwd 
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT mactype, 
    MTD_INT flag
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;
    MTD_INT speed_status;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
    {
        return MTD_API_MACSEC_NOT_SUPPORT;
    }

    speed_status = mtd_msec_get_speed_status(dev, port, mactype); 

    if(!(speed_status == MTD_MAC_XGMII || speed_status == MTD_MAC_XGMII_2P5G || speed_status == MTD_MAC_XGMII_5G))
    {
        MTD_DBG_ERROR("mtd_msec_set_10g_mac_pause_fwd: speed not supported:%x \n", speed_status);
        return MTD_MSEC_FAIL_PORT_GET_MAC_SPEED;
    }

    if (mactype == MTD_SMAC)
    {
        addr =  MTD_SMAC_REG;
    }
    else if (mactype == MTD_WMAC)
    {
        addr =  MTD_WMAC_REG;
    }
    else
    {
        MTD_DBG_ERROR("Invalid mac type!\n");
        return MTD_FAIL;
    }

    retVal = mtdMsecReadPortReg(dev, port, addr, &data);

    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtdMsecReadPortReg Failed\n");
        return(retVal);
    }

    mtd_msec_bit_write(data, (flag?1:0), 4);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtdMsecWritePortReg Failed\n");
        return(retVal);
    }

    return retVal;
}

/*****************************************************************************
*  mtd_msec_get_10g_mac_pause_fwd
*
* DESCRIPTION:
*   get 10G mac MACsec pause forwarding setting
*
* INPUTS:
*    dev - pointer to device handle
*    mactype - mac type: 1 - MTD_SMAC, 2 -MTD_WMAC
* 
* OUTPUTS:
*    flag - pause forwarding flag: 1 = forward pause, 0 = No forward pause
*
* RETURNS:
*    MTD_OK          - on success
*    MTD_FAIL        - on error
*
* COMMENTS:
*    The pause forwarding on SMAC or WMAC is only available when link speed is 
*    10G, 5G and 2.5G. This API does not apply to 1G and lower speed.
*******************************************************************************/
MTD_STATUS mtd_msec_get_10g_mac_pause_fwd 
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT mactype, 
    MTD_INT *flag
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;
    MTD_INT speed_status;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
    {
        return MTD_API_MACSEC_NOT_SUPPORT;
    }

    speed_status = mtd_msec_get_speed_status(dev, port, mactype); 

    if(!(speed_status == MTD_MAC_XGMII || speed_status == MTD_MAC_XGMII_2P5G || speed_status == MTD_MAC_XGMII_5G))
    {
        MTD_DBG_ERROR("mtd_msec_get_10g_mac_pause_fwd: speed not supported:%x \n", speed_status);
        return MTD_MSEC_FAIL_PORT_GET_MAC_SPEED;
    }

    if (mactype == MTD_SMAC)
    {
        addr =  MTD_SMAC_REG;
    }
    else if (mactype == MTD_WMAC)
    {
        addr =  MTD_WMAC_REG;
    }
    else
    {
        MTD_DBG_ERROR("Invalid mac type!\n");
        return MTD_FAIL;
    }

    retVal = mtdMsecReadPortReg(dev, port, addr, &data);

    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtdMsecReadPortReg Failed\n");
        return(retVal);
    }

    *flag = mtd_msec_bit_get(data, 4);

    return retVal;
}

/*****************************************************************************
*  mtd_msec_mac_init
*
* DESCRIPTION:
*   initialize mac with specified speed
*
* INPUTS:
*    dev - pointer to device handle
*    speed - wmac and smac link speed
*       - 0 1G-1G symmetric speed
*       - 1 10G-10G symmetric speed
*       - 2 1G-10G asymmetric speed
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
MTD_STATUS mtd_msec_mac_init
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT speed 
)
{
    MTD_STATUS   retVal = MTD_OK;
    if (speed == 0 || speed == 1)
    {
        retVal = mtd_set_mac_speed(dev, port, MTD_SMAC, speed);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("set_mac_speed Failed\n");
            return(retVal);
        }
        retVal = mtd_set_mac_speed(dev, port, MTD_WMAC, speed);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("set_mac_speed Failed\n");
            return(retVal);
        }
    }
    else if (speed == 2)
    {
        retVal = mtd_set_mac_speed(dev, port, MTD_SMAC, 1);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("set_mac_speed Failed\n");
            return(retVal);
        }
        retVal = mtd_set_mac_speed(dev, port, MTD_WMAC, 0);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("set_mac_speed Failed\n");
            return(retVal);
        }
    }
    return retVal;
}
/*****************************************************************************
*  mtd_msec_set_sym_flow_ctrl
*
* DESCRIPTION:
*   set mac symmetric flow control
*
* INPUTS:
*    dev - pointer to device handle
*    flag - flow control flag: 0- disable, 1-enable
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
MTD_STATUS mtd_msec_set_sym_flow_ctrl
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT flag
)

{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 s_addr, addr;
    MTD_U32 data;
    MTD_INT xg_sel, i;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    for (i=1; i<=2; i++)
    {
        if (i==1)
            s_addr =  MTD_SMAC_REG;
        else
            s_addr =  MTD_WMAC_REG;
        xg_sel = mtd_msec_get_mac_xg_sel(dev, port, i);
        if (xg_sel == MTD_GMII)
        {
            addr = s_addr +  MTD_MAC_CTL2;
            retVal = mtdMsecReadPortReg(dev, port, addr, &data);
            if (retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Read Failed\n");
                return(retVal);
            }
                  /* 1. FC_MODE b1=0 */
            mtd_msec_bit_clear(data, 1); 
            retVal = mtdMsecWritePortReg(dev, port, addr, data);
            if (retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Write Failed\n");
                return(retVal);
            }
            /* 2. Set AnFcEn=0 and SetFcEn=1 */
            addr = s_addr + MTD_AUTO_NEG;
            retVal = mtdMsecReadPortReg(dev, port, addr, &data);
            if (retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Read Failed\n");
                return(retVal);
            }
            mtd_msec_bit_write(data, (flag?0:1), 11);
            mtd_msec_bit_write(data, flag, 8);
            retVal = mtdMsecWritePortReg(dev, port, addr, data);
            if (retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Write Failed\n");
                return(retVal);
            }
        }
        else if (xg_sel == MTD_XGMII)
        {
            /*  MTD_MAC_CTL0 Set TxFcEn and RxFcEn */
            addr = s_addr;
            retVal = mtdMsecReadPortReg(dev, port, addr, &data);
            if (retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Read Failed\n");
                return(retVal);
            }
            mtd_msec_bit_write(data, flag, 8);
            mtd_msec_bit_write(data, flag, 7);
            mtd_msec_bit_write(data, (flag?0:1), 4);
            retVal = mtdMsecWritePortReg(dev, port, addr, data);
            if (retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Write Failed\n");
                return(retVal);
            }
            /*  MTD_MAC_CTL2 FC_MODE =0 */
            addr = s_addr +  MTD_MAC_CTL2;
            retVal = mtdMsecReadPortReg(dev, port, addr, &data);
            if (retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Read Failed\n");
                return(retVal);
            }
            mtd_msec_bit_clear(data, 14);
            retVal = mtdMsecWritePortReg(dev, port, addr, data);
            if (retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Write Failed\n");
                return(retVal);
            }
        }
    }
      /* MTD_SLC_CFG_GEN */
    addr = MTD_SLC_CFG_GEN;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bit_write(data, flag, 5);
    mtd_msec_bit_write(data, flag, 4);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

      /* pause control 4'b1010 */
    addr = MTD_SLC_CFG_PAUSE_CTL;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, 0xA, 3, 0);
    mtd_msec_bit_write(data, flag, 5);
    mtd_msec_bit_write(data, flag, 4);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }
      /* 802.3x flow control pkt drop enable */
    addr = MTD_SLC_CFG_QOS_FC;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bit_write(data, flag, 0);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_asym_flow_ctrl
*
* DESCRIPTION:
*   set mac asymmetric flow control
*   Asymetric flow control only set flow control on one MAC side, not both side. 
*   mac_type 1 - smac, 2 - wmac 
*   It's mainly used for a port operating in Asymmetric speed 10G-1G, flow control shall be enabled
*   on 10G side.
*
* INPUTS:
*    dev - pointer to device handle
*    mactype  -  1 - smac, 2 - wmac 
*    flag - flow control flag: 0- disable, 1-enable
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
MTD_STATUS mtd_msec_set_asym_flow_ctrl
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT mactype, 
    MTD_INT flag
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 s_addr, addr;
    MTD_U32 data;
    MTD_INT xg_sel;


    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    if (mactype==MTD_SMAC)
        s_addr =  MTD_SMAC_REG;
    else
        s_addr =  MTD_WMAC_REG;
    xg_sel = mtd_msec_get_mac_xg_sel(dev, port, mactype);
    if (xg_sel == MTD_GMII)
    {
        addr = s_addr +  MTD_MAC_CTL2;
        retVal = mtdMsecReadPortReg(dev, port, addr, &data);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Read Failed\n");
            return(retVal);
        }
        /* 1. FC_MODE b1=0 */
        mtd_msec_bit_clear(data, 1); 
        retVal = mtdMsecWritePortReg(dev, port, addr, data);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return(retVal);
        }

      /* 2. Set AnFcEn=0 and SetFcEn=1 */
        addr = s_addr + MTD_AUTO_NEG;
        retVal = mtdMsecReadPortReg(dev, port, addr, &data);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Read Failed\n");
            return(retVal);
        }
//      mtd_msec_bit_clear(data, 11);
        mtd_msec_bit_write(data, (flag?0:1), 11);
        mtd_msec_bit_write(data, flag, 8);
        retVal = mtdMsecWritePortReg(dev, port, addr, data);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return(retVal);
        }
    }
    else if (xg_sel == MTD_XGMII)
    {
      /*  MTD_MAC_CTL0 Set TxFcEn and RxFcEn */
        addr = s_addr;
        retVal = mtdMsecReadPortReg(dev, port, addr, &data);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Read Failed\n");
            return(retVal);
        }
        mtd_msec_bit_write(data, flag, 8);
        mtd_msec_bit_write(data, flag, 7);
        retVal = mtdMsecWritePortReg(dev, port, addr, data);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return(retVal);
        }
      /*  MTD_MAC_CTL2 FC_MODE =0 */
        addr = s_addr +  MTD_MAC_CTL2;
        retVal = mtdMsecReadPortReg(dev, port, addr, &data);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Read Failed\n");
            return(retVal);
        }
        mtd_msec_bit_clear(data, 14);
        retVal = mtdMsecWritePortReg(dev, port, addr, data);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return(retVal);
        }
    }
    else
    {
        MTD_DBG_ERROR("mtd_msec_get_mac_xg_sel Failed\n");
        return(MTD_FAIL);
    }


    /* MTD_SLC_CFG_GEN */
    addr = MTD_SLC_CFG_GEN;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bit_write(data, flag, 5);
    mtd_msec_bit_write(data, flag, 4);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    /* pause control 4'b1010 */
    addr = MTD_SLC_CFG_PAUSE_CTL;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, 0xA, 3, 0);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    /* 802.3x flow control pkt drop enable */
    addr = MTD_SLC_CFG_QOS_FC;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bit_write(data, flag, 0);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    return retVal;
}
/*****************************************************************************
*  mtd_msec_set_priority_flow_ctrl
*
* DESCRIPTION:
   Set priority flow control: qos_def_class, qos_stats_en, qbb_en, x_drop_en 
*
* INPUTS:
*    dev - pointer to device handle
*    flag - flow control flag: 0- disable, 1-enable
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
MTD_STATUS mtd_msec_set_priority_flow_ctrl
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT flag
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 s_addr, addr;
    MTD_U32 data;
    MTD_INT xg_sel, i;


    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    for (i=1;i<=2;i++)
    {
        if (i==1)
            s_addr =  MTD_SMAC_REG;
        else
            s_addr =  MTD_WMAC_REG;
        xg_sel = mtd_msec_get_mac_xg_sel(dev, port, i);
        if (xg_sel == MTD_GMII)
        {    /* FC_MODE=1 */
            addr = s_addr +  MTD_MAC_CTL2;
            retVal = mtdMsecReadPortReg(dev, port, addr, &data);
            if (retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Read Failed\n");
                return(retVal);
            }
            mtd_msec_bit_write(data, flag, 1);
            retVal = mtdMsecWritePortReg(dev, port, addr, data);
            if (retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Write Failed\n");
                return(retVal);
            }
          /* auto-neg cfg SetFcEn=1, AnFcEn=0 */
            addr = s_addr + MTD_AUTO_NEG;
            retVal = mtdMsecReadPortReg(dev, port, addr, &data);
            if (retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Read Failed\n");
                return(retVal);
            }
//          mtd_msec_bit_clear(data, 11);
            mtd_msec_bit_write(data, (flag?0:1), 11);
            mtd_msec_bit_write(data, flag, 8);
            retVal = mtdMsecWritePortReg(dev, port, addr, data);
            if (retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Write Failed\n");
                return(retVal);
            }
        }
        else if (xg_sel == MTD_XGMII)
        {
            /* TxFcEn=flag */
            addr = s_addr;
            if (retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Read Failed\n");
                return(retVal);
            }
            mtd_msec_bit_write(data, flag, 8);
            retVal = mtdMsecWritePortReg(dev, port, addr, data);
            if (retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Write Failed\n");
                return(retVal);
            }
            /* FC_MODE=1 */
            addr = s_addr +  MTD_MAC_CTL2;    
            retVal = mtdMsecReadPortReg(dev, port, addr, &data);
            if (retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Read Failed\n");
                return(retVal);
            }
            mtd_msec_bit_write(data, flag, 14);
            retVal = mtdMsecWritePortReg(dev, port, addr, data);
            if (retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Write Failed\n");
                return(retVal);
            }
        }
    }
        /* MTD_SLC_CFG_GEN */
    addr = MTD_SLC_CFG_GEN;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bit_write(data, flag, 5);
    mtd_msec_bit_write(data, flag, 4);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    /* pause control 4'b1010 */
    addr = MTD_SLC_CFG_PAUSE_CTL;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, 0xA, 3, 0);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    addr = MTD_SLC_CFG_QOS_FC;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bit_write(data, flag, 1);
    mtd_msec_bit_clear(data, 0);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    return retVal;
}

/*****************************************************************************
*  mtd_msec_get_etm_ent
*
* DESCRIPTION:
*   get ETM entry
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
* 
* OUTPUTS:
*    etm - structure of MTD_ETM_T
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_etm_ent 
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT ent_num, 
    MTD_ETM_T *etm
)
{
    MTD_STATUS   retVal = MTD_OK;
    /* get etm handle for given entry number */
    MTD_U32 etm_tbl;


    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    retVal = mtdMsecReadPortReg (dev, port, MTD_ETM_REG+ent_num*2, &etm_tbl);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    etm->etype = (MTD_U16)(etm_tbl & 0xFFFF);
    etm->act_e = mtd_msec_bits_get (etm_tbl, 23, 22);
    etm->act_i = mtd_msec_bits_get (etm_tbl, 31, 30);
    etm->rc_idx_e = mtd_msec_bits_get (etm_tbl, 21, 16);
    etm->rc_idx_i = mtd_msec_bits_get (etm_tbl, 29, 24);

    return retVal;    
}


/*****************************************************************************
*  mtd_msec_set_egr_gen_pn_roll_over
*
* DESCRIPTION:
*   when pn is saturated, it is allowed to roll over pn by setting
*    this bit 
*
* INPUTS:
*    dev - pointer to device handle
*    ro - rollover flag
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
MTD_STATUS mtd_msec_set_egr_gen_pn_roll_over
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT ro
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr =MTD_SI_EGR_GEN;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bit_write(data, ro, 4);
    retVal = mtdMsecWritePortReg (dev, port, addr, data);
    return retVal;
}
/*****************************************************************************
*  mtd_msec_set_bypass_macsec
*
* DESCRIPTION:
*   bypass MACsec on both egress and ingress path 
*
* INPUTS:
*    dev - pointer to device handle
*    bp - bypass flag
*       1 - bypass MACsec 
*       0 - enable MACsec 
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
MTD_STATUS mtd_msec_set_bypass_macsec
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT bp
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr =MTD_SI_EGR_GEN;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bit_write(data, bp, 0);
    retVal = mtdMsecWritePortReg (dev, port, addr, data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }


    addr = MTD_SI_IGR_GEN;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bit_write(data, bp, 0);
    mtdMsecWritePortReg (dev, port, addr, data);
    return retVal;
}
/*****************************************************************************
*  mtd_msec_set_igr_scb_port
*
* DESCRIPTION:
*   set ingress scb port
*
* INPUTS:
*    dev - pointer to device handle
*    scb_p - scb port
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
MTD_STATUS mtd_msec_set_igr_scb_port
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_U32 scb_p
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_SI_IGR_SCB;
    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, scb_p, 15, 0);
    mtd_msec_bit_set(data, 16);
    retVal = mtdMsecWritePortReg (dev, port, addr, data);

    return retVal;
}
/*****************************************************************************
*  mtd_msec_set_igr_implicit_sci
*
* DESCRIPTION:
*   set ingress implicit SCI
*
* INPUTS:
*    dev - pointer to device handle
*    sci_hi - higher 32 bits of SCI (63:32)
*    sci_lo - lower 32 bits of SCI (31:0)
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
MTD_STATUS mtd_msec_set_igr_implicit_sci
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_U32 sci_hi, 
    MTD_U32 sci_lo
)
{
    MTD_STATUS   retVal = MTD_OK;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    retVal = mtdMsecWritePortReg (dev, port, MTD_SI_IGR_SCI_LO, sci_lo);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg (dev, port, MTD_SI_IGR_SCI_HI, sci_hi);

    return retVal;
}
/* Ingress CHK CTL sliding window setting 0- disable, 1 - enable */
/*****************************************************************************
*  mtd_msec_set_igr_chk_slide_wind
*
* DESCRIPTION:
*   Set ingress CHK CTL sliding window 
*
* INPUTS:
*    dev - pointer to device handle
*    flag - sliding window flag
*        0- disable, 1 - enable 
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
MTD_STATUS mtd_msec_set_igr_chk_slide_wind
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT flag
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_SI_IGR_CHK_CTL;
    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bit_write(data, flag, 4);
    retVal = mtdMsecWritePortReg (dev, port, addr, data);

    return retVal;
}
/* Ingress CHK CTL Validate frames setting 0- disable, 1 - check, 2- strict */
/*****************************************************************************
*  mtd_msec_set_igr_chk_validate_frames
*
* DESCRIPTION:
*   Ingress CHK CTL Validate frames setting 
*
* INPUTS:
*    dev - pointer to device handle
*    flag - Validate frames setting
*      - 1 - disable
*      - 2 - check
*      - 3 - strict 
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
MTD_STATUS mtd_msec_set_igr_chk_validate_frames
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT flags
)
{
    MTD_STATUS   retVal = MTD_OK;    
    MTD_U16 addr;
    MTD_U32 data;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_SI_IGR_CHK_CTL;
    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, flags, 3, 2);
    retVal = mtdMsecWritePortReg (dev, port, addr, data);

    return retVal;
}
/* Ingress CHK CTL Validate frames setting 0- disable, 1 - enable */
/*****************************************************************************
*  mtd_msec_set_igr_chk_rpy_prot
*
* DESCRIPTION:
*   Ingress CHK CTL replay protect
*
* INPUTS:
*    dev - pointer to device handle
*    flag - replay protect flag
*      - 0 - disable
*      - 1 - enable
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
MTD_STATUS mtd_msec_set_igr_chk_rpy_prot
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT flag
)
{
    MTD_STATUS   retVal = MTD_OK;    
    MTD_U16 addr;
    MTD_U32 data;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_SI_IGR_CHK_CTL;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bit_write(data, flag, 1);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);

    return retVal;
}
/*****************************************************************************
*  mtd_msec_set_igr_chk_act_en
*
* DESCRIPTION:
*   Ingress CHK CTL action enable
*
* INPUTS:
*    dev - pointer to device handle
*    flag - action enable flag
*      - 0 - disable
*      - 1 - enable
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
MTD_STATUS mtd_msec_set_igr_chk_act_en
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT flag
)
{
    MTD_STATUS   retVal = MTD_OK;    
    MTD_U16 addr;
    MTD_U32 data;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_SI_IGR_CHK_CTL;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bit_write(data, flag, 0);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);

    return retVal;
}
/*****************************************************************************
*  mtd_msec_set_igr_gen_cfg
*
* DESCRIPTION:
*   set ingress general config
*
* INPUTS:
*    dev - pointer to device handle
*    igr_gen - structure for ingress general config
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
MTD_STATUS mtd_msec_set_igr_gen_cfg
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_IGR_GEN_T *igr_gen
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_SI_IGR_GEN;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bit_write(data, igr_gen->aa_disable, 12);
    mtd_msec_bit_write(data, igr_gen->badtag_rej, 11);
    mtd_msec_bit_write(data, igr_gen->pad_en, 10);
    mtd_msec_bit_write(data, igr_gen->byp_ctl_sl, 9);
    mtd_msec_bit_write(data, igr_gen->byp_ctl_v, 8);
    mtd_msec_bit_write(data, igr_gen->byp_ctl_sc, 7);
    mtd_msec_bit_write(data, igr_gen->byp_ctl_ec, 6);
    mtd_msec_bits_write(&data, igr_gen->sectag_flag, 5, 3);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);

    return retVal;
}

/* set ingress path next pn */
/*****************************************************************************
*  mtd_msec_set_igr_nxtpn
*
* DESCRIPTION:
*   set ingress path next pn 
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    nxtpn - next pn
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
MTD_STATUS mtd_msec_set_igr_nxtpn
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT ent_num, 
    MTD_U32 nxtpn
)
{
    MTD_STATUS   retVal = MTD_OK;    
    MTD_U16 addr;
    MTD_U32 data;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_SI_IGR_NXT_PN + ent_num * 4;
    /* it takes 64bits to complete the write. the upper 32bits for sliding window protection 
       must read first, then write 64bits in low to high order.
       write low 32bits, then read and write back high 32 bits does not achieve the same result
    */
    mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
    if (mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }

    retVal = _mtdMsecReadPortReg (dev, port, addr+2, &data);
    if (retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    retVal = _mtdMsecWritePortReg (dev, port, addr, nxtpn);
    if (retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }
    retVal = _mtdMsecWritePortReg (dev, port, addr+2, data);
    if (mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtdSemGive(dev,dev->multiAddrSem);

    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_igr_rpy_wind
*
* DESCRIPTION:
*   set ingress path replay window 
*
* INPUTS:
*    dev - pointer to device handle
*    rpy - replay window
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
/* set ingress path replay window */
MTD_STATUS mtd_msec_set_igr_rpy_wind
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_U32 rpy
)
{
    MTD_STATUS   retVal = MTD_OK;    
    MTD_U16 addr;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_SI_IGR_RPY_WND;
    retVal = mtdMsecWritePortReg (dev, port, addr, rpy);

    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_ect_bk_ent_all
*
* DESCRIPTION:
*   set egress Context Back Table
*
* INPUTS:
*    dev - pointer to device handle
*    asa - authentication stop field
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
MTD_STATUS mtd_msec_set_ect_bk_ent_all 
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_U8 asa
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    data = asa + asa * 0x100 + asa * 0x10000 + asa * 0x1000000;
    for (addr=MTD_SI_ECT_BK;addr<(MTD_SI_ECT_BK + 14);addr+=4)
    {
        retVal = mtdMsecWritePortReg_64(dev, port, addr, data, data);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return(retVal);
        }
    }

    return retVal;
}

/* setup egress entry */
/*****************************************************************************
*  mtd_msec_set_egr_entry
*
* DESCRIPTION:
*   setup egress entry 
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    flag_en - bitmask for flag_en
*    flag_data - bitmask for flag_data
*    match_en - structure for match enable
*    match_fld - structure for match fields
*    ect - structure for context entry
*    act_fld - structure for action field
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
MTD_STATUS mtd_msec_set_egr_entry 
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT ent_num, 
    MTD_U8 flag_en, 
    MTD_U8 flag_data, 
    MTD_MATCH_EN *match_en, 
    MTD_MATCH_FLD* match_fld, 
    MTD_CTX_T *ect, 
    MTD_ACT_FLD *act_fld
)
{
    MTD_STATUS   retVal = MTD_OK;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    mtd_msec_set_egr_parser(dev, port);
    mtd_msec_set_egr_rc(dev, port);
    mtd_msec_set_ect_front_ent(dev, port, ent_num, ect, act_fld);
    mtd_msec_set_elu_ent(dev, port, ent_num, flag_en, flag_data, match_en, match_fld);
    return retVal;
}


MTD_STATUS mtd_msec_set_egr_entry_atomic 
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT ent_num, 
    MTD_U8 flag_en, 
    MTD_U8 flag_data, 
    MTD_MATCH_EN *match_en, 
    MTD_MATCH_FLD* match_fld, 
    MTD_CTX_T *ect, 
    MTD_ACT_FLD *act_fld
)
{
    MTD_STATUS   retVal = MTD_OK;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    mtd_msec_set_egr_parser_atomic(dev, port);
    mtd_msec_set_egr_rc(dev, port);
    mtd_msec_set_ect_front_ent(dev, port, ent_num, ect, act_fld);
    mtd_msec_set_elu_ent(dev, port, ent_num, flag_en, flag_data, match_en, match_fld);
    return retVal;
}
/*****************************************************************************
*  mtd_msec_set_ect_pn
*
* DESCRIPTION:
*   set egress Context Front Table pn field
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    pn - pn field
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
MTD_STATUS mtd_msec_set_ect_pn 
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT ent_num, 
    MTD_U32 pn
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;


    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
    if (mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }

    addr =MTD_SI_ECT_FR + ent_num *32 + 20;
    retVal = _mtdMsecWritePortReg (dev, port, addr, pn);
    if (retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = _mtdMsecReadPortReg (dev, port, addr+2, &data);
    if (retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    retVal = _mtdMsecWritePortReg (dev, port, addr+2, data);
    if (mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtdSemGive(dev,dev->multiAddrSem);
    return retVal;
}


/* setup ingress entry */
/*****************************************************************************
*  mtd_msec_set_igr_entry
*
* DESCRIPTION:
*   setup ingress entry 
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    flag_en - bitmask for flag_en
*    flag_data - bitmask for flag_data
*    match_en - structure for match enable
*    match_fld - structure for match fields
*    ect - structure for context entry
*    act_fld - structure for action field
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
MTD_STATUS mtd_msec_set_igr_entry_atomic 
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT ent_num, 
    MTD_U8 flag_en, 
    MTD_U8 flag_data, 
    MTD_MATCH_EN *match_en, 
    MTD_MATCH_FLD* match_fld, 
    MTD_CTX_T *ict, 
    MTD_ACT_FLD *act_fld
)
{
    MTD_STATUS   retVal = MTD_OK;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    retVal = mtd_msec_set_igr_parser_atomic(dev, port);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("msec_set_igr_parser Failed\n");
        return(retVal);
    }
    retVal = mtd_msec_set_ict_front_ent(dev, port, ent_num, ict, act_fld);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("msec_set_ict_front_ent Failed\n");
        return(retVal);
    }
    retVal = mtd_msec_set_igr_rc(dev, port);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("msec_set_igr_rc Failed\n");
        return(retVal);
    }
  /* mask off upper 6bits of TCI */
    retVal = mtd_msec_cfg_igr_pmask (dev, port, 0, 111, 106);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("msec_cfg_igr_pmask Failed\n");
        return(retVal);
    }
    retVal = mtd_msec_set_ilu_ent(dev, port, ent_num, flag_en, flag_data, match_en, match_fld);
    return retVal;
}


MTD_STATUS mtd_msec_set_igr_entry 
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT ent_num, 
    MTD_U8 flag_en, 
    MTD_U8 flag_data, 
    MTD_MATCH_EN *match_en, 
    MTD_MATCH_FLD* match_fld, 
    MTD_CTX_T *ict, 
    MTD_ACT_FLD *act_fld
)
{
    MTD_STATUS   retVal = MTD_OK;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    retVal = mtd_msec_set_igr_parser(dev, port);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("msec_set_igr_parser Failed\n");
        return(retVal);
    }
    retVal = mtd_msec_set_ict_front_ent(dev, port, ent_num, ict, act_fld);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("msec_set_ict_front_ent Failed\n");
        return(retVal);
    }
    retVal = mtd_msec_set_igr_rc(dev, port);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("msec_set_igr_rc Failed\n");
        return(retVal);
    }
  /* mask off upper 6bits of TCI */
    retVal = mtd_msec_cfg_igr_pmask (dev, port, 0, 111, 106);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("msec_cfg_igr_pmask Failed\n");
        return(retVal);
    }
    retVal = mtd_msec_set_ilu_ent(dev, port, ent_num, flag_en, flag_data, match_en, match_fld);
    return retVal;
}
/*******************************************************************************
* mtd_msec_port_fips_chk
*
* DESCRIPTION:
*         Per Port FIPS Compliance Check 
*         It programs 128 bit input vector (Plain Text).
*         It    also programs key or hash key for egress or ingress path as defined by user.
*         For AES operation, Key[0] is programmed.
*         For GHASH operation, Hash Key[0] is programmed.
*        It triggers AES or GHASH operation and returns 128 bit output vector when operation is done.
*        After operation is done, It clears MTD_FIPS_CTL register.
*        It also toggles MACSEC core soft reset.
*
* INPUTS:
*       dev       - pointer to MTD driver structure returned from mtdLoadDriver
*        port      - port number.
*       fips_cfg  - MTD_FIPS_CFG_T
*
* OUTPUTS:
*        fips_out  - 128 bits AES or GHASH observation vector output 
*                    (fips_out[3] -> [31:0], fips_out[0] -> [127:96])
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_port_fips_chk 
(
    IN MTD_DEV *dev,
    IN MTD_U16 port,
    IN MTD_FIPS_CFG_T *fips_cfg,
    OUT MTD_U32 *fips_out
)
{
    MTD_STATUS   retVal;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

#ifdef DEBUG
    MTD_DBG_CRITIC_INFO( ("Programming MTD_FIPS_CFG     : Port %0d\n", port);
/*  mtd_msec_print_fips_cfg (fips_cfg); */
#endif

  /* set fips_vec */
    retVal = mtd_msec_set_fips_vec (dev, port, fips_cfg);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("Failed to call mtd_msec_set_fips_vec \n");
        return retVal;
    }

  /* per port FIPS Control setting */
    retVal = mtd_msec_port_fips_ctl (dev, port, fips_cfg);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("Failed to call mtd_msec_port_fips_ctl \n");
        return retVal;
    }

  /* FIPS Observation register */
    retVal = mtd_port_fips_obv (dev, port, fips_cfg, fips_out);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("Failed to call mtd_port_fips_obv \n");
        return retVal;
    }
    return retVal;
}

/*******************************************************************************
* mtd_msec_port_fips_ctl
*
* DESCRIPTION:
*            Per Port FIPS Control Setting
*            It programs key or hash key for egress or ingress path as defined by user.
*            For AES operation, Key[0] is programmed.
*            For GHASH operation, Hash Key[0] is programmed.
*            It triggers AES or GHASH operation.
*
* INPUTS:
*       dev  - pointer to MTD driver structure returned from mtdLoadDriver
*        port - port number.
*        fips_cfg MTD_FIPS_CFG_T
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
MTD_STATUS mtd_msec_port_fips_ctl 
(
    IN MTD_DEV *dev,
    IN MTD_U16 port,
    IN MTD_FIPS_CFG_T *fips_cfg
)
{
    MTD_STATUS   retVal;
    MTD_U16 addr;
    MTD_U32 data;


    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_FIPS_CTL; 
    data = 0x0;
    if (fips_cfg->egr_igr == 1)
    {
        if (fips_cfg->eng_type == 1)
        {
            mtd_msec_bit_set (data, 1);
            retVal = mtd_msec_set_fips_key_in(dev, port, fips_cfg);
          /*retVal = mtd_msec_port_set_ekey_entry (dev, port, 0x0, &ctx); */
            if (retVal != MTD_OK)
            {
                MTD_DBG_ERROR("Failed to call mtd_msec_port_set_ekey_entry \n");
                return retVal|MTD_MSEC_FAIL_PORT_SET_EKEY_ENTRY;
            }
        }
        else
        {
            mtd_msec_bit_set (data, 0);
            retVal = mtd_msec_set_fips_key_in(dev, port, fips_cfg);
          /*retVal = mtd_msec_port_set_ehkey_entry (dev, port, 0x0, &ctx); */
            if (retVal != MTD_OK)
            {
                MTD_DBG_ERROR("Failed to call mtd_msec_port_set_ehkey_entry \n");
                return retVal|MTD_MSEC_FAIL_PORT_SET_EHKEY_ENTRY;
            }
        }
    }
    else
    {
        if (fips_cfg->eng_type == 1)
        {
            mtd_msec_bit_set (data, 3);
            retVal = mtd_msec_set_fips_key_in(dev, port, fips_cfg);
          /*retVal = mtd_msec_port_set_ikey_entry (dev, port, 0x0, &ctx); */
            if (retVal != MTD_OK)
            {
                MTD_DBG_ERROR("Failed to call mtd_msec_port_set_ikey_entry \n");
                return retVal|MTD_MSEC_FAIL_PORT_SET_IKEY_ENTRY;
            }
        }
        else
        {
            mtd_msec_bit_set (data, 2);
            retVal = mtd_msec_set_fips_key_in(dev, port, fips_cfg);
          /*retVal = mtd_msec_port_set_ihkey_entry (dev, port, 0x0, &ctx); */
            if (retVal != MTD_OK)
            {
                MTD_DBG_ERROR("Failed to call mtd_msec_port_set_ihkey_entry \n");
                return retVal|MTD_MSEC_FAIL_PORT_SET_IHKEY_ENTRY;
            }
        }
    }
    retVal = mtdMsecWritePortReg (dev, port, addr, data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("Failed to call mtdMsecWritePortReg \n");
        return retVal;
    }

    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_intr_msk
*
* DESCRIPTION:
*   set macsec interrupt mask
*
* INPUTS:
*    dev - pointer to device handle
*    msk - structure of MTD_MSEC_INT_T
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
MTD_STATUS mtd_msec_set_intr_msk
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_MSEC_INT_T *msk
)
{
    MTD_STATUS   retVal;
    MTD_U16 addr;
    MTD_U32 data;
    MTD_INT xg_sel;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr =MTD_SI_EGR_INT_MSK;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, msk->msec_tx_stats_full, 20, 18);
    mtd_msec_bits_write(&data, msk->msec_tx_stats_almost_full, 17, 15);
    mtd_msec_bits_write(&data, msk->msec_tx_mem_rd_err, 14, 0);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    addr = MTD_SI_IGR_INT_MSK;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, msk->msec_rx_stats_full, 21, 19); /* {igr_stat, etm_stat, replay table} */
    mtd_msec_bits_write(&data, msk->msec_rx_stats_almost_full, 18, 16);/* {igr_stat, etm_stat, replay table} */
    mtd_msec_bits_write(&data, msk->msec_rx_mem_rd_err, 15, 0);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }


    addr = MTD_SLC_INT_SET_MSK;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, msk->slc_intr_set, 12,0);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    xg_sel = mtd_msec_get_mac_xg_sel (dev, port, MTD_WMAC);
    if (xg_sel == MTD_XGMII)
        addr =  MTD_WMAC_REG +  MTD_MAC_INT_MSK_XGMII;
    else
        addr =  MTD_WMAC_REG +  MTD_MAC_INT_MSK_GMII;

    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    if (xg_sel == MTD_XGMII)
        mtd_msec_bits_write(&data, msk->wmac_intr, 6,0);
    else
        mtd_msec_bits_write(&data, msk->wmac_intr, 15,0);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    xg_sel = mtd_msec_get_mac_xg_sel (dev, port, MTD_SMAC);
    if (xg_sel == MTD_XGMII)
        addr =  MTD_SMAC_REG +  MTD_MAC_INT_MSK_XGMII;
    else
        addr =  MTD_SMAC_REG +  MTD_MAC_INT_MSK_GMII; 
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    if (xg_sel == MTD_XGMII)
        mtd_msec_bits_write(&data, msk->wmac_intr, 6,0);
    else
        mtd_msec_bits_write(&data, msk->wmac_intr, 15,0);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    return retVal;

}

/*****************************************************************************
*  mtd_msec_get_intr
*
* DESCRIPTION:
  get macsec interrupt
*
* INPUTS:
*    dev - pointer to device handle
* 
* OUTPUTS:
*    intr - structure of MTD_MSEC_INT_T
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_intr
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_MSEC_INT_T *intr
)
{
    MTD_STATUS   retVal;
    MTD_U16 addr;
    MTD_U32 data;
    MTD_INT xg_sel;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr =MTD_SI_EGR_INT;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    intr->msec_tx_stats_full = mtd_msec_bits_get(data, 20, 18);
    intr->msec_tx_stats_almost_full= mtd_msec_bits_get(data,  17, 15);
    intr->msec_tx_mem_rd_err = mtd_msec_bits_get(data, 14, 0);

    addr = MTD_SI_IGR_INT;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    intr->msec_rx_stats_full = mtd_msec_bits_get(data, 21, 19);
    intr->msec_rx_stats_almost_full = mtd_msec_bits_get(data, 18, 16);
    intr->msec_rx_mem_rd_err = mtd_msec_bits_get(data, 15, 0);

    addr = MTD_SLC_INT_SET;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    intr->slc_intr_set = mtd_msec_bits_get(data, 12,0);

    xg_sel = mtd_msec_get_mac_xg_sel (dev, port, MTD_WMAC);
    if (xg_sel == MTD_XGMII)
        addr =  MTD_WMAC_REG +  MTD_MAC_INT_XGMII;
    else
        addr =  MTD_WMAC_REG +  MTD_MAC_INT_GMII;

    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    if (xg_sel == MTD_XGMII)
        intr->wmac_intr = mtd_msec_bits_get(data,  6,0);
    else
        intr->wmac_intr = mtd_msec_bits_get(data,  15,0);

    xg_sel = mtd_msec_get_mac_xg_sel (dev, port, MTD_SMAC);
    if (xg_sel == MTD_XGMII)
        addr =  MTD_SMAC_REG +  MTD_MAC_INT_XGMII;
    else
        addr =  MTD_SMAC_REG +  MTD_MAC_INT_GMII; 
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }

    if (xg_sel == MTD_XGMII)
        intr->smac_intr = mtd_msec_bits_get(data,  6,0);
    else
        intr->smac_intr = mtd_msec_bits_get(data,  15,0);
    return retVal;

}
/*****************************************************************************
*  mtd_msec_get_stats
*
* DESCRIPTION:
   read statistics value
*
* INPUTS:
*    dev - pointer to device handle
*    group - MTD_EGR_SEC, MTD_IGR_SEC,  MTD_SMAC_RX,  MTD_SMAC_TX,WMAC_RX,WMAC_TX 
* 
* OUTPUTS:
*    stats - statistics data
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_stats 
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT group, 
    MTD_U64 *stats
)
{
/*
      read stats value
      group : MTD_EGR_SEC, MTD_IGR_SEC,  MTD_SMAC_RX,  MTD_SMAC_TX,WMAC_RX,WMAC_TX 
      size of stats should match total entry number of each group.

*/
    MTD_STATUS retVal = MTD_OK;
    MTD_INT i, tot_ent_num;
    MTD_U32 stats_lo, stats_hi;
    MTD_U16 addr;


    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    switch (group)
    {
    case    MTD_EGR_SEC_STAT: tot_ent_num = MTD_EGR_SEC_STAT_TOT;
        break;
    case    MTD_IGR_SEC_STAT: tot_ent_num = MTD_IGR_SEC_STAT_TOT;
        break;
    case    MTD_SMAC_RX_STAT: tot_ent_num =  MTD_SMAC_STAT_TOT;
        break;
    case    MTD_SMAC_TX_STAT: tot_ent_num =  MTD_SMAC_STAT_TOT;
        break;
    case    MTD_WMAC_RX_STAT: tot_ent_num =  MTD_WMAC_STAT_TOT;
        break;
    case    MTD_WMAC_TX_STAT: tot_ent_num =  MTD_WMAC_STAT_TOT;
        break;
    default: tot_ent_num =  MTD_WMAC_STAT_TOT;
        break;
    }

    for (i = 0; i < tot_ent_num; i++)
    {
        addr = group + i*4;
        mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
        if (mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
        {
            mtdSemGive(dev,dev->multiAddrSem);
            MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
            return MTD_FAIL;
        }
        retVal = _mtdMsecReadPortReg (dev, port, addr, &stats_lo);
        if (retVal != MTD_OK)
        {
            mtdSemGive(dev,dev->multiAddrSem);
            MTD_DBG_ERROR("MSEC Read Failed\n");
            return(retVal);
        }
        retVal = _mtdMsecReadPortReg (dev, port, addr+2, &stats_hi);
        if (retVal != MTD_OK)
        {
            mtdSemGive(dev,dev->multiAddrSem);
            MTD_DBG_ERROR("MSEC Read Failed\n");
            return(retVal);
        }

        (*stats) =  ((MTD_U64)stats_hi << 32) + (MTD_U64) stats_lo;
        stats++;
        if (mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
        {
            mtdSemGive(dev,dev->multiAddrSem);
            MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
            return MTD_FAIL;
        }
        mtdSemGive(dev,dev->multiAddrSem);
    }
    stats--;

    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_egr_flow_ctrl_drop_thrh
******************************************************************************/
void mtd_msec_set_egr_flow_ctrl_drop_thrh
(
    MTD_DEV *devp, 
    MTD_U16 port, 
    MTD_INT thrh_h, 
    MTD_INT thrh_l,
    MTD_INT enableFlag
)
{
    MTD_U32 data;

    mtdMsecReadPortReg(devp,  port, MTD_EGR_FC_PKT_DROP_CFG, &data);

    mtd_msec_bit_write(data, (enableFlag ? 1 : 0), 0);

    mtd_msec_bits_write(&data,  thrh_h, 10,1);
    mtd_msec_bits_write(&data,  thrh_l, 20,11);

    mtdMsecWritePortReg(devp,  port, MTD_EGR_FC_PKT_DROP_CFG,  data);
}

/*****************************************************************************
*  mtd_msec_set_igr_flow_ctrl_drop_thrh
******************************************************************************/
void mtd_msec_set_igr_flow_ctrl_drop_thrh
(
    MTD_DEV *devp, 
    MTD_U16 port, 
    MTD_INT thrh_h64, 
    MTD_INT thrh_l64, 
    MTD_INT thrh_h32, 
    MTD_INT thrh_l32,
    MTD_INT enableFlag
)
{
    MTD_U32 data;

    mtdMsecReadPortReg(devp,  port, MTD_IGR_FC_PKT_DROP_CFG, &data);
   
    mtd_msec_bit_write(data, (enableFlag ? 1 : 0), 0);

    mtd_msec_bits_write(&data,  thrh_h64, 10, 1);
    mtd_msec_bits_write(&data,  thrh_l64, 20, 11);
    mtd_msec_bits_write(&data,  thrh_h32, 24, 21);
    mtd_msec_bits_write(&data,  thrh_l32, 28, 25);

    mtdMsecWritePortReg(devp,  port, MTD_IGR_FC_PKT_DROP_CFG,  data);
}

/*****************************************************************************
*  mtd_msec_set_egr_xoff_xon_threshold
******************************************************************************/
MTD_STATUS mtd_msec_set_egr_xoff_xon_threshold
(
    MTD_DEV *devp, 
    MTD_U16 port, 
    MTD_INT xoff_thrh, 
    MTD_INT xon_thrh
)
{
    MTD_U32 data;
    MTD_STATUS retVal = MTD_OK;

    retVal = mtdMsecReadPortReg(devp,  port, MTD_SLC_EDB_THRESH, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtd_msec_set_egr_xoff_xon_threshold: read MTD_SLC_EDB_THRESH failed\n");
        return retVal;
    }

    mtd_msec_bits_write(&data,  xoff_thrh, 9,0);
    mtd_msec_bits_write(&data,  xon_thrh, 19,10);

    retVal = mtdMsecWritePortReg(devp,  port, MTD_SLC_EDB_THRESH,  data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtd_msec_set_egr_xoff_xon_threshold: write MTD_SLC_EDB_THRESH failed\n");
        return retVal;
    }

    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_igr_xoff_xon_threshold
******************************************************************************/
MTD_STATUS mtd_msec_set_igr_xoff_xon_threshold
(
    MTD_DEV *devp, 
    MTD_U16 port, 
    MTD_INT xoff_thrh, 
    MTD_INT xon_thrh
)
{
    MTD_U32 data;
    MTD_STATUS retVal = MTD_OK;

    retVal = mtdMsecReadPortReg(devp,  port, MTD_SLC_IDB_THRESH, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtd_msec_set_igr_xoff_xon_threshold: read MTD_SLC_EDB_THRESH failed\n");
        return retVal;
    }

    mtd_msec_bits_write(&data,  xoff_thrh, 9,0);
    mtd_msec_bits_write(&data,  xon_thrh, 19,10);

    retVal = mtdMsecWritePortReg(devp,  port, MTD_SLC_IDB_THRESH,  data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtd_msec_set_igr_xoff_xon_threshold: write MTD_SLC_EDB_THRESH failed\n");
        return retVal;
    }

    return retVal;
}

/*****************************************************************************
*  mtd_msec_periodic_pause
*
******************************************************************************/
MTD_STATUS mtd_msec_periodic_pause(MTD_DEV *devp, MTD_U16 port, MTD_U16 sel)
{
    MTD_STATUS retVal = MTD_OK;
    MTD_U32 data;

    mtdMsecReadPortReg(devp,  port, MTD_SLC_CFG_PAUSE_CTL, &data);

    if (sel)
    {
        mtd_msec_bits_write(&data, 0x3, 7, 6);
    }
    else
    {
        mtd_msec_bits_write(&data, 0x0, 7, 6);
    }

    retVal = mtdMsecWritePortReg(devp, port, MTD_SLC_CFG_PAUSE_CTL, data);

    return retVal;
}


MTD_STATUS mtd_msec_set_egr_pn_rollover 
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT flag
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U32 data;
    MTD_U16 addr = 0xC02;
    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return 0xffff;
    }

    mtd_msec_bit_write(data, flag, 4);  
    retVal = mtdMsecWritePortReg (dev, port, addr, data);
    return retVal;
}

int  mtd_msec_get_pn_almost_full_intr
(
    MTD_DEV *dev, 
    MTD_U16 port
) 
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U32 data;
    MTD_U16 addr = 0xC22;
    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return 0xffff;
    }

    return(mtd_msec_bit_get(data, 15));
}

int  mtd_msec_get_pn_full_intr
(
    MTD_DEV *dev, 
    MTD_U16 port
) 
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U32 data;
    MTD_U16 addr = 0xC22;
    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return 0xffff;
    }

    return(mtd_msec_bit_get(data, 18));
}

int  mtd_msec_get_nextpn_almost_intr
(
    MTD_DEV * dev, 
    MTD_U16 port
) 
{

    MTD_STATUS   retVal = MTD_OK;
    MTD_U32 data;
    MTD_U16 addr = 0x1C26;
    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return 0xffff;
    }
    return(mtd_msec_bit_get(data, 16));
}

int  mtd_msec_get_nextpn_full_intr
(
    MTD_DEV * dev, 
    MTD_U16 port
) 
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U32 data;
    MTD_U16 addr = 0x1C26;
    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return 0xffff;
    }
    return(mtd_msec_bit_get(data, 19));
}

MTD_STATUS mtd_msec_clr_pn_almost_full_intr
(
    MTD_DEV *dev, 
    MTD_U16 port
) 
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U32 data;
    MTD_U16 addr = 0xC22;
    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return MTD_FAIL;
    }
    retVal = mtdMsecWritePortReg (dev, port, addr, mtd_msec_bit_clear(data, 15));
    return retVal;
}

MTD_STATUS mtd_msec_clr_pn_full_intr
(
    MTD_DEV *dev, 
    MTD_U16 port
) 
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U32 data;
    MTD_U16 addr = 0xC22;
    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return MTD_FAIL;
    }
    retVal = mtdMsecWritePortReg (dev, port, addr, mtd_msec_bit_clear(data, 18));
    return retVal;
}

MTD_STATUS mtd_msec_clr_nxtpn_almost_full_intr
(
    MTD_DEV *dev, 
    MTD_U16 port
) 
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U32 data;
    MTD_U16 addr = 0x1C26;
    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return MTD_FAIL;
    }
    retVal = mtdMsecWritePortReg (dev, port, addr, mtd_msec_bit_clear(data, 16));
    return retVal;
}

MTD_STATUS mtd_msec_clr_nxtpn_full_intr
(
    MTD_DEV *dev, 
    MTD_U16 port
) 
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U32 data;
    MTD_U16 addr = 0x1C26;
    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return MTD_FAIL;
    }
    retVal = mtdMsecWritePortReg (dev, port, addr, mtd_msec_bit_clear(data, 19));
    return retVal;
}

/* 
# there is a bug in X2140L where  MTD_MAC_CTL values cannot come
# back when swapping from 10G to 1G. It stays with 10G value
# The workaround is to overwrite them with corrct 1G values
*/
void  mtd_msec_force_1g_mac_ctl
(
    MTD_DEV *dev,
    MTD_U16 port
) 
{
    MTD_STATUS   retVal = MTD_OK;
    if (mtd_msec_get_mac_xg_sel(dev, port, MTD_SMAC) == MTD_GMII)
    {
        mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
        if (mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
        {
            mtdSemGive(dev,dev->multiAddrSem);
            MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
            return;
        }
        retVal = _mtdMsecWritePortReg (dev, port, MTD_SMAC_REG, 0x8BE5);
        if (retVal != MTD_OK)
        {
            mtdSemGive(dev,dev->multiAddrSem);
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return;
        }
        retVal = _mtdMsecWritePortReg (dev, port, MTD_SMAC_REG+2, 0x3);
        if (retVal != MTD_OK)
        {
            mtdSemGive(dev,dev->multiAddrSem);
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return;
        }
        retVal = _mtdMsecWritePortReg (dev, port, MTD_SMAC_REG+4, 0xc000);
        if (retVal != MTD_OK)
        {
            mtdSemGive(dev,dev->multiAddrSem);
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return;
        }
        if (mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
        {
            mtdSemGive(dev,dev->multiAddrSem);
            MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
            return;
        }
        mtdSemGive(dev,dev->multiAddrSem);
    }
    if (mtd_msec_get_mac_xg_sel(dev, port, MTD_WMAC) == MTD_GMII)
    {
        mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
        if (mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
        {
            mtdSemGive(dev,dev->multiAddrSem);
            MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
            return;
        }
        retVal = _mtdMsecWritePortReg (dev, port, MTD_WMAC_REG, 0x8BE5);
        if (retVal != MTD_OK)
        {
            mtdSemGive(dev,dev->multiAddrSem);
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return;
        }
        retVal = _mtdMsecWritePortReg (dev, port, MTD_WMAC_REG+2, 0x83);
        if (retVal != MTD_OK)
        {
            mtdSemGive(dev,dev->multiAddrSem);
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return;
        }
        retVal = _mtdMsecWritePortReg (dev, port, MTD_WMAC_REG+4, 0xc000);
        if (retVal != MTD_OK)
        {
            mtdSemGive(dev,dev->multiAddrSem);
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return;
        }
        if (mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
        {
            mtdSemGive(dev,dev->multiAddrSem);
            MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
            return;
        }
        mtdSemGive(dev,dev->multiAddrSem);
    }
}

/*
# default preamble setting for 10G mode is 4B, shall set to 8B 
# flag 1 - 8B preamble, 0 - 4B preamble
*/
void mtd_msec_set_10g_mac_ctl_preamble_rx
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT flag
) 
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16  smac_ctl = 0x8C00;
    MTD_U16  wmac_ctl = 0x8E00;
    MTD_U32 data;
    if (mtd_msec_get_smac_xg_sel(dev, port))
    {
        retVal = mtdMsecReadPortReg (dev, port, smac_ctl, &data);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Read Failed\n");
            return;
        }
        mtd_msec_bit_write(data, flag, 11);
        retVal = mtdMsecWritePortReg (dev, port, smac_ctl, data);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Read Failed\n");
            return;
        }
    }
    if (mtd_msec_get_wmac_xg_sel(dev, port))
    {
        retVal = mtdMsecReadPortReg (dev, port, wmac_ctl, &data);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Read Failed\n");
            return;
        }
        mtd_msec_bit_write(data, flag, 11);
        retVal = mtdMsecWritePortReg (dev, port, wmac_ctl, data);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Read Failed\n");
            return;
        }
    }
}


MTD_STATUS mtd_msec_dis_elu_ent 
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT ent_num
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
    if (mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }

    addr =MTD_SI_ELU + ent_num *0x20 + 16;
    retVal = _mtdMsecReadPortReg (dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return 0xffff;
    }

    retVal = _mtdMsecWritePortReg (dev, port, addr, data);
    addr +=2;
    data =  retVal = _mtdMsecReadPortReg (dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return 0xffff;
    }
    mtd_msec_bit_set(data, 7); //#flag_data bit7 =1 to miss def match in elu
    retVal = _mtdMsecWritePortReg (dev, port, addr, data);
    if (mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtdSemGive(dev,dev->multiAddrSem);
    return retVal;
}
void mtd_msec_dis_ilu_ent 
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT ent_num
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data ;

    mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
    if (mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return;
    }
    addr = MTD_SI_ILU + ent_num *0x20 + 16;
    retVal = _mtdMsecReadPortReg (dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return;
    }
    retVal = _mtdMsecWritePortReg (dev, port, addr, data);
    addr +=2;
    retVal = _mtdMsecReadPortReg (dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return;
    }
    mtd_msec_bit_set(data, 7); //#flag_data bit7 =1 to miss def match in elu
    retVal = _mtdMsecWritePortReg (dev, port, addr, data);
    mtd_msec_bit_clear(data, 9); //;#flag_en bit1=0 to disable this ilu ent
    retVal = _mtdMsecWritePortReg (dev, port, addr, data);
    if (mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return;
    }
    mtdSemGive(dev,dev->multiAddrSem);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return;
    }
}

/*# MTD_GMII - 1Gbps, MTD_XGMII - 10Gbps*/
int mtd_msec_get_smac_xg_sel 
(
    MTD_DEV *dev, 
    MTD_U16 port
) 
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr = 0x8000;
    MTD_U32 data;
    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return -1;
    }
    return(mtd_msec_bit_get(data, 1));
}

/*# MTD_GMII - 1Gbps, MTD_XGMII - 10Gbps*/
int mtd_msec_get_wmac_xg_sel 
(
    MTD_DEV *dev, 
    MTD_U16 port
) 
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr = 0x8000;
    MTD_U32 data;
    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return -1;
    }
    return(mtd_msec_bit_get(data, 0));
}

MTD_STATUS mtd_msec_clr_cam_tbl
(
    MTD_DEV *dev, 
    MTD_U16 port
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_INT i;

    for (i=0x000; i<=0x3fc; i+=4)
    {
        retVal |= mtdMsecWritePortReg_64(dev, port, i, 0, 0);
    }

    for (i=0x400; i<=0x7fc; i+=4)
    {
        retVal |= mtdMsecWritePortReg_64(dev, port, i, 0, 0);
    }

    for (i=0x800; i<=0x9fc; i+=4)
    {
        retVal |= mtdMsecWritePortReg_64(dev, port, i, 0, 0);
    }
    for (i=0xa00; i<=0xa7c; i+=4)
    {
        retVal |= mtdMsecWritePortReg_64(dev, port, i, 0, 0);
    }
    for (i=0x1000; i<=0x13fc; i+=4)
    {
        retVal |= mtdMsecWritePortReg_64(dev, port, i, 0, 0);
    }
    for (i=0x1400; i<=0x17fc; i+=4)
    {
        retVal |= mtdMsecWritePortReg_64(dev, port, i, 0, 0);
    }
    for (i=0x1800; i<=0x19fc; i+=4)
    {
        retVal |= mtdMsecWritePortReg_64(dev, port, i, 0, 0);
    }
    for (i=0x1a00; i<=0x1a7c; i+=4)
    {
        retVal |= mtdMsecWritePortReg_64(dev, port, i, 0, 0);
    }

    return retVal;
}

MTD_STATUS mtd_msec_set_local_fault_fwd
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT flag
) 
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U32 addr;
    MTD_U16 data ;
    addr =  0x001ff000;
    retVal = mtdHwReadPhyReg(dev, port, addr, &data);
    if (retVal!=MTD_OK)
    {
        MTD_DBG_ERROR("MTD reading register failed\n");
        return retVal;
    }

    mtd_msec_bit_write (data, flag, 11);
    retVal = mtdHwWritePhyReg (dev, port, addr, data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MTD Writing Failed\n");
        return retVal;
    }
    return(retVal);

}

/*******************************************************************************
* mtd_msec_get_intr_src
*
* DESCRIPTION:
*         Get new PTP interrupt source.
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*       intSrc  -  interrupt source.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_intr_src 
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    unsigned *intSrc
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 reg_addr = MTD_SLC_INT_SET;
    MTD_U32 data;  

    retVal = mtdMsecReadPortReg (dev, port, reg_addr, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }

    MTD_DBG_ERROR("MAC stats 3/4 Full %X\n", (MTD_UINT)mtd_msec_bits_get(data, 3, 0));
    MTD_DBG_ERROR("MAC stats Full %X\n", (MTD_UINT)mtd_msec_bits_get(data, 7, 4));
    MTD_DBG_ERROR("Single-bit detection ECC %X\n", (MTD_UINT)mtd_msec_bit_get(data, 10));
    MTD_DBG_ERROR("Double-bit detection ECC %X\n", (MTD_UINT)mtd_msec_bit_get(data, 11));
    MTD_DBG_ERROR("Interrupt Test %X\n", (MTD_UINT)mtd_msec_bit_get(data, 12));
    MTD_DBG_ERROR("Link change event %X\n", (MTD_UINT)mtd_msec_bit_get(data, 15));
    MTD_DBG_ERROR("PTP Egr intr %X\n", (MTD_UINT)mtd_msec_bit_get(data, 16));
    MTD_DBG_ERROR("PTP Igr intr %X\n", (MTD_UINT)mtd_msec_bit_get(data, 17));
    *intSrc = data;
    return retVal;
}

MTD_STATUS mtdPortSetMacsecBypass
(
    MTD_DEV *dev,MTD_U16 port,
    MTD_MACSEC_BYPASS_MODE msecBypassMode
)
{
    MTD_U16     data;
    MTD_STATUS  retVal;

    MTD_DBG_INFO("mtdPortSetMacsecBypass called.\n");

    data = msecBypassMode;
    if ((retVal = mtdHw_Set_PhyRegField(dev, port, MTD_REG_MACSEC_CONFIG, /*  */
        12,2, data)) != MTD_OK)
    {
        MTD_DBG_ERROR("Writing from paged phy reg failed.\n");
        return(retVal | MTD_API_FAIL_SET_REG_FIELD);
    }

    return MTD_OK;
}

MTD_STATUS mtdPortGetMacsecBypass
(
    MTD_DEV *dev,
    MTD_U16 port,
    MTD_MACSEC_BYPASS_MODE *msecBypassMode
)
{
    MTD_U16     data;
    MTD_STATUS  retVal;

    MTD_DBG_INFO("mtdPortGetMacsecBypass called.\n");

    if ((retVal = mtdHw_Get_PhyRegField(dev, port, MTD_REG_MACSEC_CONFIG, /*  */
        12,2,&data)) != MTD_OK)
    {
        MTD_DBG_ERROR("Reading from paged phy reg failed.\n");
        return(retVal | MTD_API_FAIL_GET_REG_FIELD);
    }
    *msecBypassMode = data;

    return MTD_OK;
}

/*****************************************************************************
*  mtd_msec_set_pcs_block_traffic
*
* DESCRIPTION:
*   set macsec pcs block trafic.
*
* INPUTS:
*    dev - pointer to device handle
*    flag - 0 clear, 1: set.
*    type - for 3240 type can be MTD_PATH_TYPE_LINE 
*                                MTD_PATH_TYPE_HOST 
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
MTD_STATUS mtd_msec_set_pcs_block_traffic
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT flag, 
    MTD_INT type
)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U32 reg;
    MTD_U16 data;
    MTD_U32 datal;
    MTD_INT bit_from, bit_to;

    if (!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    reg = (31<<16)|0xf04a;
    retVal = mtdHwReadPhyReg(dev, port, reg, &data);
    datal = (MTD_U32)data;

    if (retVal!=MTD_OK)
    {
        MTD_DBG_ERROR("MTD reding register failed\n");
        return retVal;
    }

    if (type == MTD_PATH_TYPE_LINE)
    {
        bit_from = 10;
        bit_to = 11;    
    }
    else if (type == MTD_PATH_TYPE_HOST)
    {
        bit_from = 8;
        bit_to = 9;
    }
    else
    {
        return MTD_API_BAD_PARAM;
    }

    if (flag)
        mtd_msec_bits_write(&datal, 3, bit_to, bit_from);
    else
        mtd_msec_bits_write(&datal, 0, bit_to, bit_from);

    data = (MTD_U16)datal;
    retVal = mtdHwWritePhyReg(dev, port, reg, data);
    if (retVal!=MTD_OK)
    {
        MTD_DBG_ERROR("MTD writing register failed\n");
        return retVal;
    }

    return retVal;
}


/*******************************************************************************
* mtd_msec_set_10g_mac_ipg_mode
*
* DESCRIPTION:
*  This function sets both the 10G Tx Inter-Packet gap mode and value
*
*******************************************************************************/
MTD_STATUS mtd_msec_set_10g_mac_ipgMode_ipgVal(
    IN MTD_DEV_PTR devPtr, 
    IN MTD_U16 port, 
    IN MTD_U16 ipgMode,
    IN MTD_U16 macType,
    IN MTD_U16 ipgVal
    ) 
{
    MTD_STATUS retVal = MTD_OK;
    MTD_U16 macCtrlAddr0, macCtrlAddr2;
    MTD_U32 data;
    MTD_INT xg_sel;

    if (!MTD_DEV_MSECPTPCAPABLE(devPtr))
        return MTD_API_MACSEC_NOT_SUPPORT;

    if (ipgMode > 2)
    {
        MTD_DBG_ERROR("mtd_msec_set_10g_mac_ipgMode_ipgVal: ipgMode not supported:%x \n", 
                      ipgMode);
        return MTD_FAIL;
    }

    xg_sel = mtd_msec_get_mac_xg_sel(devPtr, port, macType); 

    if (xg_sel != MTD_XGMII) 
    {
        MTD_DBG_ERROR("mtd_msec_set_10g_mac_ipgMode_ipgVal: speed not supported:%x \n", 
                      xg_sel);
        return MTD_MSEC_FAIL_PORT_GET_MAC_SPEED;
    }
    
    if (macType == MTD_SMAC)
    {
        macCtrlAddr0 = MTD_SMAC_REG;
        macCtrlAddr2 = 0x8C04;
    }
    else if (macType == MTD_WMAC)
    {
        macCtrlAddr0 = MTD_WMAC_REG;
        macCtrlAddr2 = 0x8E04;
    }
    else
    {
        MTD_DBG_ERROR("mtd_msec_set_10g_mac_ipgMode_ipgVal: invalid mactype:%x", macType);
        return MTD_FAIL;             
    }

    retVal= mtdMsecReadPortReg(devPtr, port, macCtrlAddr0, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtd_msec_set_10g_mac_ipgMode_ipgVal: MSEC Read macCtrlAddr0 failed\n");
        return retVal;
    }

    mtd_msec_bits_write(&data, ipgMode, 6, 5);
    retVal = mtdMsecWritePortReg (devPtr, port, macCtrlAddr0, data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtd_msec_set_10g_mac_ipgMode_ipgVal: MSEC Write macCtrlAddr0 failed\n");
        return retVal;
    }

    retVal= mtdMsecReadPortReg(devPtr, port, macCtrlAddr2, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtd_msec_set_10g_mac_ipgMode_ipgVal: MSEC Read macCtrlAddr2 failed\n");
        return retVal;
    }

    if (ipgVal == 12)
    {
        mtd_msec_bit_clear(data, 9);
        retVal = mtdMsecWritePortReg (devPtr, port, macCtrlAddr2, data);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("mtd_msec_set_10g_mac_ipgMode_ipgVal: MSEC Write macCtrlAddr2 failed ipgVal:%x\n", 
                          ipgVal);
            return retVal;
        }
    }
    else
    {
        mtd_msec_bit_set(data, 9);
        retVal = mtdMsecWritePortReg (devPtr, port, macCtrlAddr2, data);
        if (retVal != MTD_OK)
        {
            MTD_DBG_ERROR("mtd_msec_set_10g_mac_ipgMode_ipgVal: MSEC Write macCtrlAddr2 failed ipgVal:%x\n", 
                          ipgVal);
            return retVal;
        }
    }
    
    return retVal;
}


/*******************************************************************************
* mtd_msec_get_10g_mac_ipg_mode
*
* DESCRIPTION:
*  Gets the 10G Tx Inter-Packet mode
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_10g_mac_ipg_mode(
    IN MTD_DEV_PTR devPtr, 
    IN MTD_U16 port, 
    IN MTD_U16 macType,
    OUT MTD_U32 *txIPGMode
    ) 
{
    MTD_U16 macCtrlAddr0;
    MTD_U32 data;
    MTD_INT xg_sel;
    MTD_U32 retVal = MTD_OK;

    if (!MTD_DEV_MSECPTPCAPABLE(devPtr))
        return MTD_API_MACSEC_NOT_SUPPORT;

    xg_sel = mtd_msec_get_mac_xg_sel(devPtr, port, macType); 

    if (xg_sel != MTD_XGMII) 
    {
        MTD_DBG_ERROR("mtd_msec_get_10g_mac_ipg_mode: speed not supported:%x \n", xg_sel);
        return MTD_MSEC_FAIL_PORT_GET_MAC_SPEED;
    }

    if (macType == MTD_SMAC)
    {
        macCtrlAddr0 = MTD_SMAC_REG;
    }
    else if (macType == MTD_WMAC)
    {
        macCtrlAddr0 = MTD_WMAC_REG;
    }
    else
    {
        MTD_DBG_ERROR("mtd_msec_get_10g_mac_ipg_mode: invalid mactype:%x", macType);
        return MTD_FAIL;             
    }

    retVal= mtdMsecReadPortReg(devPtr, port, macCtrlAddr0, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtd_msec_get_10g_mac_ipg_mode: MSEC Read macCtrlAddr0 failed\n");
        return retVal;
    }

    /* Transmit Inter-Packet Gap Mode */
    *txIPGMode = mtd_msec_bits_get(data, 6, 5);

    return retVal;
}


/*******************************************************************************
* mtd_msec_get_10g_mac_ipg
*
* DESCRIPTION:
*  Gets the 10G Inter-Packet Gap Tx and Rx length
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_10g_mac_ipg(
    IN MTD_DEV_PTR devPtr, 
    IN MTD_U16 port, 
    IN MTD_U16 macType,
    OUT MTD_U32 *fixedIPGByteSize
    ) 
{
    MTD_U16 macCtrlAddr2;
    MTD_U32 data;
    MTD_INT xg_sel;
    MTD_U32 fixedIPGBaseBit;
    MTD_U32 retVal = MTD_OK;
    
    if (!MTD_DEV_MSECPTPCAPABLE(devPtr))
        return MTD_API_MACSEC_NOT_SUPPORT;

    xg_sel = mtd_msec_get_mac_xg_sel(devPtr, port, macType); 

    if (xg_sel != MTD_XGMII) 
    {
        MTD_DBG_ERROR("mtd_msec_get_10g_mac_ipg: speed not supported:%x \n", xg_sel);
        return MTD_MSEC_FAIL_PORT_GET_MAC_SPEED;
    }

    if (macType == MTD_SMAC)
    {
        macCtrlAddr2 = 0x8C04;
    }
    else if (macType == MTD_WMAC)
    {
        macCtrlAddr2 = 0x8E04;
    }
    else
    {
        MTD_DBG_ERROR("mtd_msec_get_10g_mac_ipg: invalid mactype:%x", macType);
        retVal = MTD_FAIL;
        return retVal;
    }

    retVal = mtdMsecReadPortReg(devPtr, port, macCtrlAddr2, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtd_msec_get_10g_mac_ipg: MSEC Read macCtrlAddr0 failed\n");
        return retVal;
    }

    /*
      0 = 12byte: Fixed IPG uses 12 bytes as the base IPG.
      1 = 8byte: Fixed IPG uses 8 bytes as the base IPG
    */
    fixedIPGBaseBit = mtd_msec_bit_get(data, 9);

    if(fixedIPGBaseBit == 1)
    {
        *fixedIPGByteSize = 8;
    }
    else if (fixedIPGBaseBit == 0)
    {
        *fixedIPGByteSize = 12;
    }

    return retVal;
}


/*******************************************************************************
* mtd_msec_set_10g_mac_preamble
*
* DESCRIPTION:
*  Sets the 10G Preamble Tx and Rx length
*
*******************************************************************************/
MTD_STATUS mtd_msec_set_10g_mac_preamble(
    IN MTD_DEV_PTR devPtr, 
    IN MTD_U16 port, 
    IN MTD_U16 macType,
    IN MTD_U16 preAmble
    ) 
{
    MTD_U16 macCtrlAddr0;
    MTD_U32 data;
    MTD_INT xg_sel;
    MTD_U32 retVal = MTD_OK;

    if (!MTD_DEV_MSECPTPCAPABLE(devPtr))
        return (MTD_STATUS)MTD_API_MACSEC_NOT_SUPPORT;

    xg_sel = mtd_msec_get_mac_xg_sel(devPtr, port, macType); 

    if (xg_sel != MTD_XGMII) 
    {
        MTD_DBG_ERROR("mtd_msec_set_10g_mac_preamble: speed not supported:%x \n", xg_sel);
        return MTD_MSEC_FAIL_PORT_GET_MAC_SPEED;
    }

    if (macType == MTD_SMAC)
    {
        macCtrlAddr0 = MTD_SMAC_REG;
    }
    else if (macType == MTD_WMAC)
    {
        macCtrlAddr0 = MTD_WMAC_REG;
    }
    else
    {
        MTD_DBG_ERROR("mtd_msec_set_10g_mac_preamble: invalid mactype:%x", macType);
        return MTD_FAIL;             
    }

    retVal= mtdMsecReadPortReg(devPtr, port, macCtrlAddr0, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtd_msec_set_10g_mac_preamble: MSEC Read macCtrlAddr0 failed\n");
        return retVal;
    }

    mtd_msec_bits_write(&data, preAmble, 12, 11);

    retVal = mtdMsecWritePortReg (devPtr, port, macCtrlAddr0, data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtd_msec_set_10g_mac_preamble: MSEC Write macCtrlAddr0 failed\n");
        return retVal;
    }
 
    return retVal;
}


/*******************************************************************************
* mtd_msec_get_10g_mac_preamble
*
* DESCRIPTION:
*  Gets the 10G Preamble Tx and Rx length
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_10g_mac_preamble(
    IN MTD_DEV_PTR devPtr, 
    IN MTD_U16 port, 
    IN MTD_U16 macType,
    OUT MTD_U32 *preAmble
    ) 
{
    MTD_U16 macCtrlAddr0;
    MTD_U32 data;
    MTD_INT xg_sel;
    MTD_U32 retVal = MTD_OK;

    if (!MTD_DEV_MSECPTPCAPABLE(devPtr))
        return MTD_API_MACSEC_NOT_SUPPORT;

    xg_sel = mtd_msec_get_mac_xg_sel(devPtr, port, macType); 

    if (xg_sel != MTD_XGMII) 
    {
        MTD_DBG_ERROR("mtd_msec_get_10g_mac_preamble: speed not supported:%x \n", xg_sel);
        return MTD_MSEC_FAIL_PORT_GET_MAC_SPEED;
    }
    
    if (macType == MTD_SMAC)
    {
        macCtrlAddr0 = MTD_SMAC_REG;
    }
    else if (macType == MTD_WMAC)
    {
        macCtrlAddr0 = MTD_WMAC_REG;
    }
    else
    {
        MTD_DBG_ERROR("mtd_msec_get_10g_mac_preamble: invalid mactype:%x", macType);
        return MTD_FAIL;             
    }

    retVal= mtdMsecReadPortReg(devPtr, port, macCtrlAddr0, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtd_msec_get_10g_mac_preamble: MSEC Read macCtrlAddr0 failed\n");
        return retVal;
    }

    *preAmble = mtd_msec_bits_get(data, 12, 11);

    return retVal;
}


/*******************************************************************************
* mtd_msec_set_1g_mac_ipg
*
* DESCRIPTION:
*  Sets the Minimal Inter-packet gap for 1G mode
*
*******************************************************************************/
MTD_STATUS mtd_msec_set_1g_mac_ipg(
    IN MTD_DEV_PTR devPtr, 
    IN MTD_U16 port, 
    IN MTD_U16 macType,
    IN MTD_U16 ipg
    ) 
{
    MTD_U16 macCtrlAddr3;
    MTD_U32 data; 
    MTD_INT xg_sel;
    MTD_U32 retVal = MTD_OK;

    if (!MTD_DEV_MSECPTPCAPABLE(devPtr))
        return (MTD_STATUS)MTD_API_MACSEC_NOT_SUPPORT;

    xg_sel = mtd_msec_get_mac_xg_sel(devPtr, port, macType); 

    if (xg_sel != MTD_GMII) 
    {
        MTD_DBG_ERROR("mtd_msec_set_1g_mac_ipg: speed not supported:%x \n", xg_sel);
        return MTD_MSEC_FAIL_PORT_GET_MAC_SPEED;
    }

    if (macType == MTD_SMAC)
    {
        macCtrlAddr3 = 0x8C18;
    }
    else if (macType == MTD_WMAC)
    {
        macCtrlAddr3 = 0x8E18;
    }
    else
    {
        MTD_DBG_ERROR("mtd_msec_set_1g_mac_ipg: invalid mactype:%x", macType);
        return MTD_FAIL;             
    }

    retVal= mtdMsecReadPortReg(devPtr, port, macCtrlAddr3, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtd_msec_set_1g_mac_ipg: MSEC Read macCtrlAddr0 failed\n");
        return retVal;
    }

    mtd_msec_bits_write(&data, 0, 14, 6);   
    mtd_msec_bits_write(&data, ipg, 14, 6);  

    retVal = mtdMsecWritePortReg (devPtr, port, macCtrlAddr3, data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtd_msec_set_1g_mac_ipg: MSEC Write macCtrlAddr0 failed\n");
        return retVal;
    }
 
    return retVal;
}


/*******************************************************************************
* mtd_msec_get_1g_mac_ipg
*
* DESCRIPTION:
*  Returns the Minimal Inter-packet gap for 1G mode
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_1g_mac_ipg(
    IN MTD_DEV_PTR devPtr, 
    IN MTD_U16 port, 
    IN MTD_U16 macType,
    OUT MTD_U32 *ipg
    ) 
{
    MTD_U16 macCtrlAddr3;
    MTD_U32 data;
    MTD_INT xg_sel;
    MTD_U32 retVal = MTD_OK;

    if (!MTD_DEV_MSECPTPCAPABLE(devPtr))
        return MTD_API_MACSEC_NOT_SUPPORT;

    xg_sel = mtd_msec_get_mac_xg_sel(devPtr, port, macType); 

    if (xg_sel != MTD_GMII) 
    {
        MTD_DBG_ERROR("mtd_msec_get_1g_mac_ipg: speed not supported\n");
        return MTD_MSEC_FAIL_PORT_GET_MAC_SPEED;
    }
    
    if (macType == MTD_SMAC)
    {
        macCtrlAddr3 = 0x8C18;
    }
    else if (macType == MTD_WMAC)
    {
        macCtrlAddr3 = 0x8E18;
    }
    else
    {
        MTD_DBG_ERROR("mtd_msec_get_1g_mac_ipg: invalid mactype:%x", macType);
        return MTD_FAIL;             
    }

    retVal= mtdMsecReadPortReg(devPtr, port, macCtrlAddr3, &data);
    if (retVal != MTD_OK)
    {
        MTD_DBG_ERROR("mtd_msec_get_1g_mac_ipg: MSEC Read macCtrlAddr3 failed\n");
        return retVal;
    }

    *ipg = mtd_msec_bits_get(data, 14, 6);

    return retVal;
}

