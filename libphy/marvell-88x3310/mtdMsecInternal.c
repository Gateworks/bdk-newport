/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions to access platform layer by MacSec 
control program..
********************************************************************/
#include "mtdApiTypes.h"
#include "mtdHwCntl.h"
#include "mtdSemaphore.h"
#include "mtdMsecPtpApiDefs.h"
#include "mtdHwCntl.h"
#include "mtdMsecInternal.h"
#include "mtdMsecApi.h"
#include "mtdHwMsecPtpCntl.h"
#include "mtdUtils.h"

void MTDWait (MTD_INT waitTime);

MTD_DEV       *mtd_msec_mtddev;

MTD_STATUS mtd_ptp_dev_init(void * dev, MTD_U16 port, int link_mode);

MTD_STATUS mtd_msec_dev_init(void *dev)
{
    MTD_STATUS retVal = MTD_OK;

    mtd_msec_mtddev = (MTD_DEV *)dev;

    /* init the PtP global dev pointer regardless PtP is used */
    mtd_ptp_dev_init(dev, 0, 0);
    
    return retVal;
}  


int mtd_aes_hkey (MTD_CTX_T *ctx)
{
    MTD_INT             i;
    MTD_U8         in [16];
    aes_encrypt_ctx acx[1];

    for(i = 0; i < 16; i++)
        in[i] = 0;
    aes_encrypt_key (ctx->key, 16, acx);
    aes_encrypt     (in, ctx->hkey, acx);

    return 1;

}

int mtd_msec_bits_write (MTD_U32 *data, MTD_INT in_data, MTD_INT bit_to, MTD_INT bit_from)
{
    MTD_INT      i; 
    for(i = bit_from; i <= bit_to; i++)
    {
        mtd_msec_bit_write (*data, mtd_msec_bit_get(in_data, i-bit_from), i);
    }

#ifdef DEBUG_BITS
    MTD_DBG_CRITIC_INFO("mtd_msec_bits_write               : data %x [%d:%d] %x-> data %x\n", 
        (MTD_UINT)*data, bit_to, bit_from, in_data, (MTD_UINT)*data));
#endif

    return 1;
}

int mtd_msec_bits_get (MTD_INT in_data, MTD_INT bit_to, MTD_INT bit_from)
{
    MTD_INT i, out;

    out    = 0x0;
    for(i = bit_from; i <= bit_to; i++)
    {
        out |= (mtd_msec_bit_get(in_data, i) << (i-bit_from));
    }

#ifdef DEBUG_BITS
    MTD_DBG_CRITIC_INFO("mtd_msec_bits_get                 : data %x [%d:%d] %x-> data %x\n", in_data, bit_to, bit_from, in_data, out);
#endif

    return out;
}



#if 1
void MTDWait (MTD_INT waitTime)
{
    volatile int count=waitTime*100000;
    while(count--);
}
#endif

void mtd_msec_soft_reset(MTD_U16 port)
{
    MTD_INT  devAddr, reg;
    MTD_U32 data = 0;
    MTD_U16 tmpdata = 0;
    devAddr = 3;
    reg = 0xf073;
    data = 0;

    mtdHwReadPhyReg(mtd_msec_mtddev, port, (devAddr<<16)|reg, &tmpdata);
    data = tmpdata;
    mtd_msec_bits_write (&data, 0x3, 3, 2);

    mtdHwWritePhyReg(mtd_msec_mtddev, port, (devAddr<<16)|reg, (MTD_U16)data);
    mtd_msec_bits_write (&data, 0x2, 3, 2);
    mtdHwWritePhyReg(mtd_msec_mtddev, port, (devAddr<<16)|reg, (MTD_U16)data);
    mtd_msec_bits_write (&data, 0x0, 3, 2);
    mtdHwWritePhyReg(mtd_msec_mtddev, port, (devAddr<<16)|reg, (MTD_U16)data);
}

/*
# reset the sigba core on both egress and ingress
# then bring it out of reset
*/
void mtd_macsec_core_reset(MTD_U16 port)
{
    MTD_U16 egr_gen, igr_gen;
    MTD_U32 egr, igr;
    MTD_U16 devAddr;
    devAddr = 31;
    egr_gen = 0xC02;
    igr_gen = 0x1C0A;

//  mtdMsecWritePortReg $port $devAddr $egr_gen [bit_set [mtdMsecReadPortReg $port $devAddr $egr_gen] 2]
//  mtdMsecWritePortReg $port $devAddr $igr_gen [bit_set [mtdMsecReadPortReg $port $devAddr $igr_gen] 2]
//  MTDWait(100);
//  mtdMsecWritePortReg $port $devAddr $egr_gen [bit_clr [mtdMsecReadPortReg $port $devAddr $egr_gen] 2]
//  mtdMsecWritePortReg $port $devAddr $igr_gen [bit_clr [mtdMsecReadPortReg $port $devAddr $igr_gen] 2]


    mtdMsecReadPortReg(mtd_msec_mtddev, port, egr_gen, &egr);
    mtdMsecReadPortReg(mtd_msec_mtddev, port, igr_gen, &igr);
    mtd_msec_bit_set(egr, 2);
    mtd_msec_bit_set(igr, 2);
    mtdMsecWritePortReg(mtd_msec_mtddev,  port, egr_gen, egr);
    mtdMsecWritePortReg(mtd_msec_mtddev,  port, igr_gen, igr);
    MTDWait(100);
    mtdMsecReadPortReg(mtd_msec_mtddev, port, egr_gen, &egr);
    mtdMsecReadPortReg(mtd_msec_mtddev, port, igr_gen, &igr);
    mtd_msec_bit_clear(egr, 2);
    mtd_msec_bit_clear(igr, 2);
    mtdMsecWritePortReg(mtd_msec_mtddev,  port, egr_gen, egr);
    mtdMsecWritePortReg(mtd_msec_mtddev,  port, igr_gen, igr);
}

/* # when this bit is set, macsec stats is cleared when a PHY soft reset is applied.  */
void mtd_mac_clr_stats_on_reset(MTD_U16 port, MTD_INT flag)
{
    MTD_INT  reg;
    MTD_U32  data;
    reg = 0x80B0;

//  mtdMsecWritePortReg $port $devAddr 0x80B0 [bit_write [mtdMsecReadPortReg $port $devAddr 0x80B0] $flag 11]
    mtdMsecReadPortReg(mtd_msec_mtddev,  port, reg, &data);
    mtd_msec_bit_write(data, flag, 11);
    mtdMsecWritePortReg(mtd_msec_mtddev,  port,  reg,  data);
}

MTD_STATUS mtd_set_frag_drop_size (MTD_U16 port, MTD_INT size)
{
    MTD_INT  reg;
    MTD_UINT val; 
    MTD_U32  data;

    reg = 0x80B8;

    val = size / 8;
    mtdMsecReadPortReg(mtd_msec_mtddev, port, reg, &data);
//  mtdMsecWritePortReg $port $devAddr $reg [bits_write [bits_write $data $val 7 2] $val 15 10]
    mtd_msec_bits_write(&data, val, 7, 2);
    mtd_msec_bits_write(&data, val, 15, 10);
    mtdMsecWritePortReg(mtd_msec_mtddev,  port,  reg,  data);
    return MTD_OK;
}
MTD_UINT  mtd_get_frag_drop_size(MTD_U16 port)
{
    MTD_INT  reg;
    MTD_U32 data;        

    reg = 0x80B8;
//  set data [mtdMsecReadPortReg $port $devAddr $reg]
    mtdMsecReadPortReg(mtd_msec_mtddev,  port,  reg, &data);
    return(8*mtd_msec_bits_get(data, 7, 2));
}

void mtd_macsec_clr_stats_on_reset(MTD_U16 port, MTD_INT flag)
{
    MTD_INT  reg;
    MTD_U32  data;

/*  foreach reg [list 0xC02 0x1C0A] {
    mtdMsecWritePortReg $port $devAddr $reg [bit_write [mtdMsecReadPortReg $port $devAddr $reg] $flag 30]
  } */
    reg = 0xC02;
    mtdMsecReadPortReg(mtd_msec_mtddev,  port,  reg, &data);
    mtd_msec_bit_write(data, flag, 30);
    mtdMsecWritePortReg(mtd_msec_mtddev,  port,  reg,  data);
    reg = 0x1C0A;
    mtdMsecReadPortReg(mtd_msec_mtddev,  port,  reg, &data);
    mtd_msec_bit_write(data, flag, 30);
    mtdMsecWritePortReg(mtd_msec_mtddev,  port,  reg,  data);
}

MTD_STATUS mtd_disable_macsec_encrypt(MTD_U16 port)
{
    MTD_INT reg;
    MTD_U32 data;

//  mtdMsecWritePortReg $reg [bit_set [read_reg2 $reg $port] 0] $port

    reg = 0xC02;
    mtdMsecReadPortReg(mtd_msec_mtddev,  port,  reg, &data);
    mtd_msec_bit_set(data, 0);
    mtdMsecWritePortReg(mtd_msec_mtddev,  port,  reg,  data);
    MTD_DBG_ERROR("Macsec encryption is disabled on egress path.\n");
    return MTD_OK;
}

MTD_STATUS mtd_disable_macsec_decrypt(MTD_U16 port)
{
    MTD_INT reg;
    MTD_U32 data;

  //mtdMsecWritePortReg $reg [bit_set [read_reg2 $reg $port] 0] $port
    reg = 0x1C0A;
    mtdMsecReadPortReg(mtd_msec_mtddev,  port,  reg, &data);
    mtd_msec_bit_set(data, 0);
    mtdMsecWritePortReg(mtd_msec_mtddev,  port,  reg,  data);
    MTD_DBG_ERROR("Macsec decryption is disabled on ingress path.\n");
    return MTD_OK;
}



/*********************************************************************************
*********************************************************************************/

MTD_MATCH_EN lk_match_en;
MTD_MATCH_FLD  lk_match_fld;
MTD_ACT_FLD act_fld;
MTD_CTX_T ect;
MTD_CTX_T ict;
static char keyStr[32] ={1,2,3,4,5,6,7,8,9,0,0xA,0xB,0xC,0xD,0xE,0xF,0xF,0xE,0xD,0xC,0xB,0xA,9,8,7,6,5,4,3,2,1,0};



MTD_STATUS mtd_enable_macsec_encrypt(MTD_U16 port)
{
    MTD_INT flag_en =0;
    MTD_INT flag_data  = 0;
    MTD_U32 data;
    MTD_INT reg;
    MTD_INT ent_num = 0;
    
    MTD_DBG_ERROR("\n");
/*# setup macsec encryption ent_num $ent_num on port $port" */
    lk_match_en.en_def = 1;
    lk_match_en.en_mc = 0;
    lk_match_en.en_da = 0;
    lk_match_en.en_sa = 0;
    lk_match_en.en_vlan = 0;
    lk_match_en.en_et = 0;
    lk_match_en.en_sci = 0;

    lk_match_fld.da = 0;
    lk_match_fld.sa = 0;
    lk_match_fld.vlan = 0;
    lk_match_fld.et = 0;
    lk_match_fld.sci = 0LL;
    lk_match_fld.tci = 0;
    lk_match_fld.tci_msk = 0;

    act_fld.set_idx = 3; 
    act_fld.drop = 0;
    act_fld.redir = 0;
    act_fld.auth_en = 1;
    act_fld.enc_en = 1;
    act_fld.enc_start_adj = 0; 
    act_fld.retain_hdr = 0;
    act_fld.tci = 0x2c;

/*
# The key array and ctx are shared structures for egress and ingress,
# it is created here and deleted later.
*/
    ect.sci = 0xCAFEFEEDDEED0001LL;
    ect.pn = 1;
//  pn_rollover = 1;
    mtdMemCpy(ect.key, keyStr, 16);

/*
# Setup EGR entry 
# setup flag_en and flag_data
*/
    flag_en = 0;
    flag_data = 0;

    mtd_msec_bit_write(flag_data, lk_match_en.en_vlan,  MTD_ENV_EPR_1Q_FLAG);
    mtd_msec_bit_write(flag_data, act_fld.enc_en,  MTD_ENV_EPR_SEC_FLAG);
    mtd_msec_bit_write(flag_en, lk_match_en.en_vlan,  MTD_ENV_EPR_1Q_FLAG);
    mtd_msec_bit_write(flag_en, lk_match_en.en_def,  MTD_ENV_EPR_MATCH_FLAG);


    mtd_msec_set_egr_entry(mtd_msec_mtddev, port, ent_num, flag_en, flag_data, &lk_match_en, &lk_match_fld, &ect, &act_fld);

    mtd_msec_set_ect_bk_ent_all(mtd_msec_mtddev, port, 0xf);

    reg = 0xC02;
    mtdMsecReadPortReg(mtd_msec_mtddev,  port, reg, &data);
    mtd_msec_bit_clear(data, 0);
    mtdMsecWritePortReg(mtd_msec_mtddev,  port,  reg,  data);
    MTD_DBG_ERROR("Macsec encryption is enabled on egress path.\n");

/*  # set parser workaround to avoid going to a unknown state */
//  mtd_set_parser_workaround(port);
    return MTD_OK;
}

MTD_STATUS mtd_enable_macsec_decrypt(MTD_U16 port)
{
    MTD_INT flag_en =0;
    MTD_INT flag_data  = 0;
    MTD_INT reg;
    MTD_U32 data;
    MTD_INT ent_num = 0;
    MTD_DBG_ERROR("\n");

    MTD_DBG_ERROR("Setup macsec ingress ent_num %d on port %d\n", ent_num, port);

/*  # setup ILU match enables" */
    lk_match_en.en_def = 0;
    lk_match_en.en_mc = 0;
    lk_match_en.en_da = 0;
    lk_match_en.en_sa = 0;
    lk_match_en.en_vlan = 0;
    lk_match_en.en_et = 0;
    lk_match_en.en_sci = 0x1FF;

/*
# setup ILU match fields
*/
    lk_match_fld.da = 0;
    lk_match_fld.sa = 0;
    lk_match_fld.vlan = 0;
    lk_match_fld.et = 0;
    lk_match_fld.sci = 0xCAFEFEEDDEED0001ll;
    lk_match_fld.tci = 0x2C;
    lk_match_fld.tci_msk = 0xFF;

  /*
# setup ILU action
*/
//  ctx_num = ent_num;
    act_fld.set_idx = 1; 
    act_fld.drop = 0;
    act_fld.redir = 0;
    act_fld.auth_en = 1;
    act_fld.enc_en = 1;
    act_fld.enc_start_adj = 0; 
    act_fld.retain_hdr = 0;
    act_fld.tci = 0x2c;
//  conf_offset = 0;

  /*
# setup ICT
# IGR use same key as EGR, sci, tci, pn fields are not valid for ingress.
set ict [mtd_new_ctx_ent $ent_num $keyStr $sci $pn]
*/
    ict.sci = 0LL;
    ict.pn = 1;
    mtdMemCpy(ict.key, keyStr, 16);

/*
# setup ctrl port_num
# setup flag_en and flag_data
*/
    flag_en = 0;
    flag_data = 0;

    mtd_msec_bit_write(flag_data, lk_match_en.en_sci | lk_match_en.en_def,  MTD_ENV_IPR_AE_FLAG);
    mtd_msec_bit_write(flag_en, 1,  MTD_ENV_IPR_AE_FLAG);
    mtd_msec_bit_write(flag_en, 1,  MTD_ENV_EPR_MATCH_FLAG);


/*
  # Setup IGR entry 
*/
    mtd_msec_set_igr_entry(mtd_msec_mtddev, port, ent_num, flag_en, flag_data, &lk_match_en, &lk_match_fld, &ict, &act_fld);
    MTD_DBG_ERROR("Setup port %d IGR entry %d as configured above.\n", port, ent_num);

    reg = 0x1c0a;
    mtdMsecReadPortReg(mtd_msec_mtddev,  port, reg, &data);
    mtd_msec_bit_clear(data, 0);
    mtdMsecWritePortReg(mtd_msec_mtddev,  port,  reg,  data);
    MTD_DBG_ERROR("Macsec decryption is enabled on ingress path.\n");
    return MTD_OK;
}

MTD_STATUS mtd_disable_macsec_both(MTD_U16 port)
{
    MTD_STATUS retVal;
    retVal = mtd_disable_macsec_encrypt(port);
    retVal |= mtd_disable_macsec_decrypt(port);
    return retVal;
}
MTD_STATUS mtd_enable_macsec_both(MTD_U16 port)
{
    MTD_STATUS retVal;
    retVal = mtd_enable_macsec_encrypt(port);
    retVal |= mtd_enable_macsec_decrypt(port);
    return retVal;
}

/*# 0x8000.24 smac_aneg_en */
void mtd_set_smac_aneg_en(MTD_U16 port, MTD_INT mode)
{
    MTD_U32 data;
    MTD_INT reg = 0x8000;

    mtdMsecReadPortReg(mtd_msec_mtddev,  port,  reg, &data);
    mtd_msec_bit_write(data, mode, 24);
    mtdMsecWritePortReg(mtd_msec_mtddev,  port,  reg,  data);
}

/*# 0x8000.23 wmac_aneg_en */
void mtd_set_wmac_aneg_en(MTD_U16 port, MTD_INT mode)
{
    MTD_U32 data;
    MTD_INT reg = 0x8000;

    mtdMsecReadPortReg(mtd_msec_mtddev,  port,  reg, &data);
    mtd_msec_bit_write(data, mode, 23);
    mtdMsecWritePortReg(mtd_msec_mtddev,  port,  reg,  data);
}

void mtd_set_mac_xg_sel (MTD_DEV * devp, MTD_U16 port, MTD_INT sel)
{
    MTD_U32 data;
    mtdMsecReadPortReg(devp,  port, 0x8000, &data);
    mtd_msec_bits_write(&data,  sel, 1,0);
    mtdMsecWritePortReg(devp,  port, 0x8000,  data);
}


void mtd_msec_set_mdio_watchdog_timer (MTD_DEV * devp, MTD_U16 port, MTD_INT mode, MTD_INT cycle)
{
    MTD_U32 data;
    data = 0;
    mtd_msec_bits_write(&data,  cycle, 14,0);
    mtd_msec_bit_write(data, mode, 15);
    mtdMsecWritePortReg(devp,  port, 0x80ac,  data);
}


/*****************************************************************************
* mtd_msec_set_strip_add_crc
*
* DESCRIPTION:
*    set smac and wmac strip crc, add crc
*
* INPUTS:
*    dev - pointer to device handle
*    bmsk - bitmask for strip and add crc
*       - 4'b0000 = no strip or add crc; 
*       - 4'b1111 = strip and add crc on smac and wmac
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
MTD_STATUS mtd_msec_set_strip_add_crc(MTD_DEV *dev, MTD_U16 port, MTD_U8 bmsk)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_SLC_CFG_GEN;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, bmsk, 11, 8);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_qos_stag
*
* DESCRIPTION:
*   set 802.1s ether-type 
*
* INPUTS:
*    dev - pointer to device handle
*    tag - 802.1s ether-type
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
MTD_STATUS mtd_msec_set_qos_stag(MTD_DEV *dev, MTD_U16 port, MTD_U16 tag)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_SLC_CFG_QOS_ETYPE;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, tag, 31,16);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    return retVal;
}
/*****************************************************************************
* mtd_msec_set_qos_qtag
*
* DESCRIPTION:
   set 802.1q ether-type 
*
* INPUTS:
*    dev - pointer to device handle
*    tag - 802.1q ether-type
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
MTD_STATUS mtd_msec_set_qos_qtag(MTD_DEV *dev, MTD_U16 port, MTD_U16 tag)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_SLC_CFG_QOS_ETYPE;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, tag, 15,0);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    return retVal;
}

/*****************************************************************************
* mtd_init_linkcrypt
*
* DESCRIPTION:
*   initialize linkcrypt
*
* INPUTS:
*    dev - pointer to device handle
*    macsec_mode 
*          - 1 to bypass
*          - 0 to enable
*    fwd_mode
*          - 0: cut-through
*          - 1: egress cut-through, ingress store-forward,
*          - 2: egress store-forward, ingress cut-through
*          - 3: store-forward
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
MTD_STATUS mtd_init_linkcrypt(MTD_DEV *dev, MTD_U16 port, MTD_INT macsec_mode, MTD_INT fwd_mode)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U32 slc_cfg_gen;
    MTD_U32 si_egr_gen;
    MTD_U32 si_igr_gen;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    /* program slc_cfg_gen */
    slc_cfg_gen = 0x7c500000;
    mtd_msec_bits_write (&slc_cfg_gen, fwd_mode, 3,2);
    mtd_msec_bits_write(&slc_cfg_gen, 0xf3, 15, 4);
    mtd_msec_bits_write(&slc_cfg_gen, 0x3, 1, 0); /*real speed will be same as phy speed as aneg_en bits are set.*/
    if (MTD_IS_X33X0_BASE(dev->deviceId))
    {
      mtd_msec_bits_write(&slc_cfg_gen, 0x3, 24, 23); /* set aneg_en bits */
    }
    retVal = mtdMsecWritePortReg (dev, port, MTD_SLC_CFG_GEN, slc_cfg_gen); 
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    /* program egress GEN */
    si_egr_gen = 0x0; 
    mtd_msec_bit_write (si_egr_gen, 0x1, 1);
    mtd_msec_bit_write (si_egr_gen, macsec_mode, 0); 
    retVal = mtdMsecWritePortReg (dev, port,MTD_SI_EGR_GEN, si_egr_gen);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    /* program ingress GEN */
    si_igr_gen = 0xBCA;
    mtd_msec_bit_write (si_igr_gen, macsec_mode, 0); 
    retVal = mtdMsecWritePortReg (dev, port, MTD_SI_IGR_GEN, si_igr_gen);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    if(macsec_mode != MTD_MACSEC_BYPASS)
    {
        mtd_msec_set_egr_short_pkt_adj(dev, port, 0xc);
        mtd_msec_set_egr_short_pkt_sz(dev, port, 0x25);
        mtd_msec_set_egr_thr(dev, port, 4, 0);
        retVal = mtdMsecWritePortReg (dev, port,MTD_SI_EGR_RC0, 0x1DFFB1); 
        retVal = mtdMsecWritePortReg (dev, port,MTD_SI_EGR_RC1, 0x88E50000);
        if(retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return(retVal);
        }
        mtd_msec_set_igr_short_pkt_sz(dev, port, 96);
        mtd_msec_set_ict_trail_sz(dev, port, 239);
        mtd_msec_set_igr_scb_port(dev, port, 0x1BABE);
        mtd_msec_set_igr_implicit_sci(dev, port, 0x98765432, 0x10FEDCBA);
        mtd_msec_set_igr_chk_validate_frames(dev, port, 3);
        mtd_msec_set_igr_chk_act_en(dev, port, 1);
        mtd_msec_set_igr_chk_rpy_prot(dev, port, 1);
        mtd_msec_set_igr_rpy_wind(dev, port, 0);
        retVal = mtdMsecWritePortReg (dev, port, MTD_SI_IGR_BYPIDX, 0x20);
        if(retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return(retVal);
        }
        if (MTD_IS_X32X0_BASE(dev->deviceId))
        {
           mtd_msec_set_egr_flow_ctrl_drop_thrh(dev, port, 0x2A0, 0x180, 1);
           mtd_msec_set_mdio_watchdog_timer (dev, port, 1, 0x1007);
        }
        else if (MTD_IS_X33X0_BASE(dev->deviceId))
        {
          /* from X33x0 the buffer size is increased, setting the threshold will cause unexpected pkt drop 
           for earlier products, setting the threshold still helps to prevent pkt drop */
          //mtd_msec_set_egr_flow_ctrl_drop_thrh(dev, port, 0x2A0, 0x180, 1);
          /* set a larger timer to avoid MDIO timeout in 2.5G as it runs on slower clock */
          mtd_msec_set_mdio_watchdog_timer (dev, port, 1, 0x1007);
        }
    }

    {
        mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);        
        retVal = mtd_msec_set_link_down_reset(dev, port, 1);
        if(retVal != MTD_OK)
        {
            mtdSemGive(dev,dev->multiAddrSem);
            MTD_DBG_ERROR("mtd_msec_set_link_down_reset Failed\n");
            return(retVal);
        }
        retVal = mtd_msec_set_link_down_detect(dev, port, 1);
        if(retVal != MTD_OK)
        {
            mtdSemGive(dev,dev->multiAddrSem);
            MTD_DBG_ERROR("mtd_msec_set_link_down_detect Failed\n");
            return(retVal);
        }
        retVal = mtd_msec_set_delay_ext_reset(dev, port, 1);
        if(retVal != MTD_OK)
        {
            mtdSemGive(dev,dev->multiAddrSem);
            MTD_DBG_ERROR("mtd_msec_set_delay_ext_reset Failed\n");
            return(retVal);
        }
        mtdSemGive(dev,dev->multiAddrSem);
    }

    return retVal;
}

/*****************************************************************************
*  mtd_set_mac_MTU
*
* DESCRIPTION:
   set mac MTU
*
* INPUTS:
*    dev - pointer to device handle
*    mac - structure for mac with mac type and link speed
*    MTU - maximum frame size
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
MTD_STATUS mtd_set_mac_MTU (MTD_DEV *dev, MTD_U16 port, MTD_MAC_T *mac, MTD_INT MTU)
{
    MTD_STATUS   retVal = MTD_OK;
    /* 
    frame size will be MTU * 2.
    default is 1522. It can increase up to 16382 (2^14-2)
    */
    MTD_U32 mac_ctl;
    MTD_U16 addr;


    if(mac->mac_type == MTD_SMAC)
    {
        addr =  MTD_SMAC_REG;
    }
    else /* MTD_WMAC */
    {
        addr =  MTD_WMAC_REG;
    }

    if(mac->speed == MTD_XGMII)
    {
        retVal = mtdMsecReadPortReg (dev, port, addr+MTD_MAC_CTL1, &mac_ctl);
        if(retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Read Failed\n");
            return(retVal);
        }
        mtd_msec_bits_write (&mac_ctl, MTU, 12, 0);
        retVal = mtdMsecWritePortReg (dev, port, addr+MTD_MAC_CTL1, mac_ctl);    
        if(retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return(retVal);
        }
    }
    else /* MTD_GMII */
    {
        retVal = mtdMsecReadPortReg (dev, port, addr, &mac_ctl);
        if(retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Read Failed\n");
            return(retVal);
        }
        mtd_msec_bits_write (&mac_ctl, MTU, 14, 2);
        retVal = mtdMsecWritePortReg (dev, port, addr, mac_ctl);    
        if(retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return(retVal);
        }
    }

    return retVal;
}
int mtd_msec_get_speed_status(MTD_DEV *dev, MTD_U16 port, MTD_INT mactype)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_INT addr;
    MTD_U32 data;
    addr = MTD_MAC_SPEED_STATUS;
    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    if(mactype == MTD_SMAC)
    {
        return mtd_msec_bits_get(data, 5, 3);
    }
    if(mactype == MTD_WMAC)
    {
        return mtd_msec_bits_get(data, 2, 0);
    }
    return -1;
}
/*****************************************************************************
*  mtd_msec_get_mac_xg_sel
*
* DESCRIPTION:
*   get mac speed mode
*
* INPUTS:
*    dev - pointer to device handle
*    mactype - mac type: 1 - MTD_SMAC, 2 -MTD_WMAC
* 
* OUTPUTS:
*        None
*
* RETURNS:
*   speed mode:
*       1 - 10G, 0 - 1G 
*
* COMMENTS:
*
*******************************************************************************/
int mtd_msec_get_mac_xg_sel(MTD_DEV *dev, MTD_U16 port, MTD_INT mactype)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_INT addr;
    MTD_U32 data;
    MTD_INT aneg_en;
    MTD_INT speed_status;
    addr = MTD_SLC_CFG_GEN;

    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    if (MTD_IS_X32X0_BASE(dev->deviceId))
    {
        if(mactype == MTD_SMAC)
        {
            aneg_en= mtd_msec_bit_get(data, 24);
            if(aneg_en == 0)
                return mtd_msec_bit_get(data,1);
            else
            {
                speed_status = mtd_msec_get_speed_status(dev, port,mactype);
                if(speed_status == MTD_MAC_XGMII)
                    return MTD_XGMII;
                else
                    return MTD_GMII;
            }
        }

        if(mactype == MTD_WMAC)
        {
            aneg_en = mtd_msec_bit_get(data, 23);
            if(aneg_en == 0)
                return mtd_msec_bit_get(data,0);
            else
            {
                speed_status = mtd_msec_get_speed_status(dev, port,mactype);
                if(speed_status == MTD_MAC_XGMII)
                    return MTD_XGMII;
                else
                    return MTD_GMII;
            }
        }
    }
    else if (MTD_IS_X33X0_BASE(dev->deviceId))
    {
        speed_status = mtd_msec_get_speed_status(dev, port,mactype);
        if(speed_status == MTD_MAC_XGMII || speed_status == MTD_MAC_XGMII_2P5G || speed_status == MTD_MAC_XGMII_5G)
            return MTD_XGMII;
        else
            return MTD_GMII;
    }
   
    return -1;
}

/*****************************************************************************
*  mtd_msec_set_mac_loopback
*
* DESCRIPTION:
*   set mac loopback
*
* INPUTS:
*    dev - pointer to device handle
*    mactype - mac type: 1 - MTD_SMAC, 2 -MTD_WMAC
*    flag - loopback flag
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
MTD_STATUS mtd_msec_set_mac_loopback(MTD_DEV *dev, MTD_U16 port, MTD_INT mactype, MTD_INT flag)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr = 0;
    MTD_U32 data;
    MTD_INT xg_sel;
    MTD_INT sbit;


    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    xg_sel = mtd_msec_get_mac_xg_sel(dev, port, mactype);
    if(mactype == MTD_SMAC)
        addr =  MTD_SMAC_REG;
    else if(mactype == MTD_WMAC)
        addr =  MTD_WMAC_REG;
    if(xg_sel == MTD_GMII)
    {
        addr +=  MTD_MAC_CTL1;
        sbit = 5;
    }
    else if(xg_sel == MTD_XGMII)
    {
        addr +=  MTD_MAC_CTL1;
        sbit = 13;
    }
    else
        return -1;

    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bit_write(data, flag, sbit);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_mac_forward_fc
*
* DESCRIPTION:
*   Enable foR/Ward 802.3x flow control frames (instead of termination in port).
*
* INPUTS:
*    dev - pointer to device handle
*    mactype - mac type: 1 - MTD_SMAC, 2 -MTD_WMAC
*    en - 0: disable, 1: enable
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
MTD_STATUS mtd_msec_set_mac_forward_fc(MTD_DEV *dev, MTD_U16 port, MTD_INT mactype, MTD_INT en)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr = 0;
    MTD_U32 data;
    MTD_INT xg_sel;
/*    MTD_INT sbit; */


    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    xg_sel = mtd_msec_get_mac_xg_sel(dev, port, mactype);
    if(xg_sel != MTD_XGMII)  /* for 10G mode  */
        return -1;

    if(mactype == MTD_SMAC)
        addr =  MTD_SMAC_REG;
    else if(mactype == MTD_WMAC)
        addr =  MTD_WMAC_REG;

    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bit_write(data, en, 4);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_etm_ent
*
* DESCRIPTION:
*   set ETM entry
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    etm - structure of MTD_ETM_T
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
MTD_STATUS mtd_msec_set_etm_ent (MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num, MTD_ETM_T *etm)
{
    MTD_STATUS   retVal = MTD_OK;
    /*
        act_e : egress action,
        act_i : ingress action
         action type :
        0: disable, 1: redirect or loopback, 2: drop    
    */
    MTD_U16 addr;
    MTD_U32 data;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_ETM_REG + ent_num * 2;
    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write (&data, etm->act_e, 23, 22);
    mtd_msec_bits_write (&data, etm->act_i, 31, 30);
    mtd_msec_bits_write (&data, etm->rc_idx_e, 21, 16);
    mtd_msec_bits_write (&data, etm->rc_idx_i, 29, 24);
    mtd_msec_bits_write (&data, etm->etype, 15, 0);
    retVal = mtdMsecWritePortReg (dev, port, addr, data);

    return retVal;    
}

/*****************************************************************************
*  mtd_msec_set_etm_ent_igr_mode
*
* DESCRIPTION:
   get ETM entry ingress mode
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    igr_mode - ingress mode
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
MTD_STATUS mtd_msec_set_etm_ent_igr_mode (MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num, MTD_INT igr_mode)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_ETM_T etm;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    retVal = mtd_msec_get_etm_ent (dev, port, ent_num, &etm);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("msec_get_etm_ent Failed\n");
        return(retVal);
    }
    etm.act_i = igr_mode;
    retVal = mtd_msec_set_etm_ent (dev, port, ent_num, &etm);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("msec_set_etm_ent Failed\n");
        return(retVal);
    }
    return retVal;
}
/*****************************************************************************
*  mtd_msec_set_etm_ent_egr_mode
*
* DESCRIPTION:
*   set ETM entry egress mode
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    egr_mode - egress mode
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
MTD_STATUS mtd_msec_set_etm_ent_egr_mode (MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num, MTD_INT egr_mode)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_ETM_T etm;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    retVal = mtd_msec_get_etm_ent (dev, port,ent_num,  &etm);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("msec_get_etm_ent Failed\n");
        return(retVal);
    }
    etm.act_e = egr_mode;
    retVal = mtd_msec_set_etm_ent (dev, port, ent_num, &etm);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("msec_set_etm_ent Failed\n");
        return(retVal);
    }
    return retVal;
}
/*****************************************************************************
*  mtd_msec_set_etm_ent_etype
*
* DESCRIPTION:
*   set ETM entry etype
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    etype - ether-type
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
MTD_STATUS mtd_msec_set_etm_ent_etype (MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num, MTD_INT etype)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_ETM_T etm;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    retVal = mtd_msec_get_etm_ent (dev, port, ent_num, &etm);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("msec_get_etm_ent Failed\n");
        return(retVal);
    }
    etm.etype = etype;
    retVal = mtd_msec_set_etm_ent (dev, port, ent_num, &etm);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("msec_set_etm_ent Failed\n");
        return(retVal);
    }
    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_egr_parser
*
* DESCRIPTION:
*   set egress parser
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_set_egr_parser(MTD_DEV *dev, MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;
    /*
       egress parsing DA/SA/ET/VLAN(2B only if exist)
       ingress parsing DA/SA/16B macsec
    */

    /* egress parser */
    retVal = mtdMsecWritePortReg_64(dev, port, 0x800, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x804, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x808, 0x0, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0xA00, 0xC0001, 0x40B);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg_64(dev, port, 0x810, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x814, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x818, 0x1, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0xA04, 0x62000002, 0x3);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg_64(dev, port, 0x820, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x824, 0x88E52000, 0xFFFF2000);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x828, 0x2, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0xA08, 0xC3100403, 0x407);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg_64(dev, port, 0x830, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x834, 0x88E50000, 0xFFFF2000);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x838, 0x2, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0xA0C, 0xC3080403, 0x407);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg_64(dev, port, 0x840, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x844, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x848, 0x2, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0xA10, 0x91000004, 0x401);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg_64(dev, port, 0x850, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x854, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x858, 0x3, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0xA14, 0x91000004, 0x401);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg_64(dev, port, 0x860, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x864, 0x81000000, 0xFFFF0000);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x868, 0x4, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0xA18, 0x60060205, 0xC45);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }
    
    retVal = mtdMsecWritePortReg_64(dev, port, 0x870, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x874, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x878, 0x4, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0xA1C, 0x5, 0x800);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }
    retVal = mtdMsecWritePortReg_64(dev, port, 0x880, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x884, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x888, 0x5, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0xA20, 0x5, 0x800);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }
    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_igr_parser
*
* DESCRIPTION:
*   set ingress parser
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_set_igr_parser(MTD_DEV *dev, MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    /* ingress parser */
    retVal = mtdMsecWritePortReg_64(dev, port, 0x1800, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1804, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1808, 0x0, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1A00, 0xC0001, 0x40B);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg_64(dev, port, 0x1810, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1814, 0x88E52000, 0xFFFF2000);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1818, 0x1, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1A04, 0x61020202, 0x401);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg_64(dev, port, 0x1820, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1824, 0x88E50000, 0xFFFF2000);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1828, 0x1, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1A08, 0x61020203, 0x401);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg_64(dev, port, 0x1830, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1834, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1838, 0x1, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1A0C, 0x60020003, 0xC01);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg_64(dev, port, 0x1840, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1844, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1848, 0x2, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1A10, 0x900E0003, 0xC0D);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg_64(dev, port, 0x1850, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1854, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1858, 0x3, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1A14, 0x90060003, 0xC05);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    return retVal;    
}
/*****************************************************************************
*  mtd_msec_set_egr_parser_atomic
*
* DESCRIPTION:
*   set egress parser
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_set_egr_parser_atomic(MTD_DEV *dev, MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;
    /*
       egress parsing DA/SA/ET/VLAN(2B only if exist)
       ingress parsing DA/SA/16B macsec
    */
    /* egress parser */
    /* entry 0 first set done bit so that it does not goto next state
    after we finished programming other entries then we remove the done
    bit on entry 0 
    */
    retVal = mtdMsecWritePortReg_64(dev, port, 0xA00, 0xC0001, 0xC0B);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x800, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x804, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x808, 0x0, 0xFF);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg_64(dev, port, 0x810, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x814, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x818, 0x1, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0xA04, 0x62000002, 0x3);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg_64(dev, port, 0x820, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x824, 0x88E52000, 0xFFFF2000);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x828, 0x2, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0xA08, 0xC3100403, 0x407);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg_64(dev, port, 0x830, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x834, 0x88E50000, 0xFFFF2000);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x838, 0x2, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0xA0C, 0xC3080403, 0x407);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg_64(dev, port, 0x840, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x844, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x848, 0x2, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0xA10, 0x91000004, 0x401);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg_64(dev, port, 0x850, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x854, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x858, 0x3, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0xA14, 0x91000004, 0x401);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg_64(dev, port, 0x860, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x864, 0x81000000, 0xFFFF0000);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x868, 0x4, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0xA18, 0x60060205, 0xC45);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }
    /* back to entry 0, clear the done bit */
    retVal = mtdMsecWritePortReg (dev, port, 0xA02, 0x40B);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    return retVal;
}


/*****************************************************************************
*  mtd_msec_set_igr_parser_atomic
*
* DESCRIPTION:
*   set ingress parser
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_set_igr_parser_atomic(MTD_DEV *dev, MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    /* ingress parser */
    retVal = mtdMsecWritePortReg_64(dev, port, 0x1A00, 0xC0001, 0xC0B);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1800, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1804, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1808, 0x0, 0xFF);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg_64(dev, port, 0x1810, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1814, 0x88E52000, 0xFFFF2000);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1818, 0x1, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1A04, 0x61020202, 0x401);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg_64(dev, port, 0x1820, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1824, 0x88E50000, 0xFFFF2000);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1828, 0x1, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1A08, 0x61020203, 0x401);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg_64(dev, port, 0x1830, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1834, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1838, 0x1, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1A0C, 0x60020203, 0xC01);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg_64(dev, port, 0x1840, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1844, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1848, 0x2, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1A10, 0x900E0003, 0xC0D);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg_64(dev, port, 0x1850, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1854, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1858, 0x3, 0xFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1A14, 0x90060003, 0xC05);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    /* then clear the done bit of entry 0 */
    retVal = mtdMsecWritePortReg (dev, port, 0x1A02, 0x40B);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    return retVal;    
}

/*****************************************************************************
*  mtd_msec_set_egr_rc
*
* DESCRIPTION:
*   set egress rewrite constructor
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_set_egr_rc (MTD_DEV *dev, MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    /* egress rc engine */
    /* Entry 0 is programmed to NOP
     Entry 1 is programmed to DEL COT tag
     Entry 2 and 3 is porgrammed to DEL COT tag and Insert MACSEC header.
    */

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    retVal = mtdMsecWritePortReg_64(dev, port, 0xA80, 0x830000, 0x78204);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0xA84, 0x68204, 0x6381CF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0xB00, 0xCBCAC9C8, 0x3736CCCD);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0xB04, 0xC3C2C1C0, 0xC7C6C5C4);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    retVal = mtdMsecWritePortReg (dev, port, 0xA88, 0x2678308);    
    retVal |= mtdMsecWritePortReg_64 (dev, port, 0xB08, 0xCBCAC9C8, 0x67666564);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }


    /* egress rc ASA: 0x0f per entry means authentication stop before offset 15
       from end of packet, which skips the 16bit ICV field */
    /* This part is moved to new function mtd_msec_set_egr_rc_asa
    retVal = mtdMsecWritePortReg (dev, port, 0xB80, 0x0f0f0f0f);
    retVal = mtdMsecWritePortReg (dev, port, 0xB82, 0x0f0f0f0f);
    retVal = mtdMsecWritePortReg (dev, port, 0xB84, 0x0f0f0f0f);
    retVal = mtdMsecWritePortReg (dev, port, 0xB86, 0x0f0f0f0f);
    retVal = mtdMsecWritePortReg (dev, port, 0xB88, 0x0f0f0f0f);
    retVal = mtdMsecWritePortReg (dev, port, 0xB8A, 0x0f0f0f0f);
    retVal = mtdMsecWritePortReg (dev, port, 0xB8C, 0x0f0f0f0f);
    retVal = mtdMsecWritePortReg (dev, port, 0xB8E, 0x0f0f0f0f);
    if (retVal != MTD_OK)
    {
      MTD_DBG_ERROR("MSEC Write Failed\n");
      return (retVal);
    }

    */
    return MTD_OK;
}


/*****************************************************************************
*  mtd_msec_set_igr_rc
*
* DESCRIPTION:
*   set ingress rewrite constructor
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_set_igr_rc (MTD_DEV *dev, MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    /* ingress rc engine */
    /* Entry 0       is programmed to NOP
       Entry 1       is programmed to DEL MACSEC header.
     */
    retVal = mtdMsecWritePortReg_64 (dev, port, 0x1A80, 0x830000, 0x781CF);    
    /*retVal = mtdMsecWritePortReg (dev, port, 0x1A84, 0x1671202);    
    retVal = mtdMsecWritePortReg (dev, port, 0x1B04, 0x0);    
    retVal = mtdMsecWritePortReg (dev, port, 0x1B06, 0x34330000);    */
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    return retVal;    
}

/*****************************************************************************
*  mtd_msec_set_egress_seca
*
* DESCRIPTION:
*   set egress security entry - obsolete
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_set_egress_seca (MTD_DEV *dev, MTD_U16 port, MTD_INT seca_num)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;


    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

/* 
    set secure association with
    - default match, 
    - 16B macsec
*/
  /* ect */
    addr =MTD_SI_ECT_FR + seca_num * 32;
    retVal = mtdMsecWritePortReg_64(dev, port, addr, 0x76543210, 0xFEDCBA98);
    retVal |= mtdMsecWritePortReg_64(dev, port, addr+4, 0x90ABCDEF, 0x12345678);
    retVal |= mtdMsecWritePortReg_64(dev, port, addr+8, 0xA4BD647D, 0xF1DA897E);
    retVal |= mtdMsecWritePortReg_64(dev, port, addr+12, 0x850B1273, 0xBFF23ABD);
    retVal |= mtdMsecWritePortReg_64(dev, port, addr+16, 0xDEEDF00D, 0xCAFEFEED);
    retVal |= mtdMsecWritePortReg_64(dev, port, addr+20, 0x1, 0x800C32C);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    addr =MTD_SI_ECT_BK + seca_num / 4;
    retVal = mtdMsecWritePortReg (dev, port, addr, 0xF);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

/*elu */
    addr =MTD_SI_ELU * seca_num*32;
    retVal = mtdMsecWritePortReg_64(dev, port, addr, 0x8888, 0x88E52C26);
    retVal |= mtdMsecWritePortReg_64(dev, port, addr+4, 0x0, 0xBADBABE);
    retVal |= mtdMsecWritePortReg_64(dev, port, addr+8, 0xDEADFACE, 0xADCADDAD);
    retVal |= mtdMsecWritePortReg_64(dev, port, addr+12, 0xBEEFADDB, 0xFEEDDEAD);
    retVal |= mtdMsecWritePortReg_64(dev, port, addr+16, 0x0, 0x8000);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_ingress_seca
*
* DESCRIPTION:
*   set ingress security entry - obsolete
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_set_ingress_seca (MTD_DEV *dev, MTD_U16 port, MTD_INT seca_num)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

/* 
    set secure association with
    - sci and an match, 
    - 16B macsec
*/
/*ict */
    addr = MTD_SI_ICT_FR + seca_num*32;
    retVal = mtdMsecWritePortReg_64(dev, port, addr, 0x76543210, 0xFEDCBA98);
    retVal |= mtdMsecWritePortReg_64(dev, port, addr+4, 0x90ABCDEF, 0x12345678);
    retVal |= mtdMsecWritePortReg_64(dev, port, addr+8, 0xA4BD647D, 0xF1DA897E);
    retVal |= mtdMsecWritePortReg_64(dev, port, addr+12, 0x850B1273, 0xBFF23ABD);
    retVal |= mtdMsecWritePortReg_64(dev, port, addr+16, 0x10021, 0x0);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

/*ilu */
    retVal = mtdMsecWritePortReg_64(dev, port, 0x1C10, 0xFFFFFFFF, 0xFFFFFFFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1C14, 0xFFFFFFFF, 0xFFFF03FF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1C18, 0xFFFFFFFF, 0xFFFFFFFF);
    retVal |= mtdMsecWritePortReg_64(dev, port, 0x1C1C, 0xFFFFFFFF, 0xFFFFFFFF);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    addr = MTD_SI_ILU * seca_num*32;
    retVal = mtdMsecWritePortReg_64(dev, port, addr, 0xDEEDF00D, 0xCAFEFEED);
    retVal |= mtdMsecWritePortReg_64(dev, port, addr+4, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, addr+8, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, addr+12, 0x0, 0x0);
    retVal |= mtdMsecWritePortReg_64(dev, port, addr+16, 0x20FF, 0x202);

    return retVal;
}


/*****************************************************************************
*  mtd_msec_elu_init
*
* DESCRIPTION:
*   ELU init
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_elu_init(MTD_DEV *dev, MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_INT i, j;
    MTD_U16 addr;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    for(i=0;i<32;i++)
    {
        addr =MTD_SI_ELU + i * 32;
        for(j=0;j<17;j+=4)
        {
            retVal = mtdMsecWritePortReg_64(dev, port, addr+j, 0, 0);
            if(retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Write Failed\n");
                return(retVal);
            }
        }
    }

    return retVal;
}

/*****************************************************************************
*  mtd_msec_ect_fr_init
*
* DESCRIPTION:
*   ECT front table init
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_ect_fr_init(MTD_DEV *dev, MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_INT i, j;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    for(i=0;i<32;i++)
    {
        addr =MTD_SI_ECT_FR + i * 32;
        for(j=0;j<22;j+=4)
        {
            retVal = mtdMsecWritePortReg_64(dev, port, addr+j, 0, 0);
            if(retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Write Failed\n");
                return(retVal);
            }

        }
    }

    return retVal;

}
/*****************************************************************************
*  mtd_msec_ect_bk_init
*
* DESCRIPTION:
*   ECT back table init
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_ect_bk_init(MTD_DEV *dev, MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_INT i, j;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    for(i=0;i<32;i++)
    {
        addr =MTD_SI_ECT_BK + i * 32;
        for(j=0;j<22;j+=4)
        {
            retVal = mtdMsecWritePortReg_64 (dev, port, addr+j, 0, 0);
            if(retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Write Failed\n");
                return(retVal);
            }
        }
    }

    return retVal;
}
/*****************************************************************************
*  mtd_msec_ilu_init
*
* DESCRIPTION:
*   ILU init
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_ilu_init(MTD_DEV *dev, MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_INT i,j;
    MTD_U16 addr;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    for(i=0;i<32;i++)
    {
        addr = MTD_SI_ILU + i * 32;
        for(j=0;j<17;j+=4)
        {
            retVal = mtdMsecWritePortReg_64(dev, port, addr+j, 0, 0);
            if(retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Write Failed\n");
                return(retVal);
            }

        }
    }

    return retVal;
}
/*****************************************************************************
*  mtd_msec_ict_fr_init
*
* DESCRIPTION:
*   ICT front table init
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_ict_fr_init(MTD_DEV *dev, MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_INT i,j;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    for(i=0;i<32;i++)
    {
        addr = MTD_SI_ICT_FR + i * 32;
        for(j=0;j<22;j+=4)
        {
            retVal = mtdMsecWritePortReg_64(dev, port, addr+j, 0, 0);
            if(retVal != MTD_OK)
            {
                MTD_DBG_ERROR("MSEC Write Failed\n");
                return(retVal);
            }
        }
    }

    return retVal;

}

/*****************************************************************************
* mtd_msec_set_egr_short_pkt_adj
*
* DESCRIPTION:
*   set egress short packet adjacency
*
* INPUTS:
*    dev - pointer to device handle
*    s_pkt_adj - short packet adjacency
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
/* Short packet adjustment value */
MTD_STATUS mtd_msec_set_egr_short_pkt_adj(MTD_DEV *dev, MTD_U16 port, MTD_U8 s_pkt_adj)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr =MTD_SI_EGR_PKT_SZ;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, s_pkt_adj, 13, 8);
    retVal = mtdMsecWritePortReg (dev, port, addr, data);
    return retVal;
}
/*****************************************************************************
*  mtd_msec_set_egr_short_pkt_sz
*
* DESCRIPTION:
   set short packet size 
*
* INPUTS:
*    dev - pointer to device handle
*    s_pkt_sz - short packet size
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
/* Short packet size */
MTD_STATUS mtd_msec_set_egr_short_pkt_sz(MTD_DEV *dev, MTD_U16 port, MTD_U8 s_pkt_sz)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr =MTD_SI_EGR_PKT_SZ;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, s_pkt_sz, 7, 0);
    retVal = mtdMsecWritePortReg (dev, port, addr, data);
    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_egr_thr
*
* DESCRIPTION:
   set Egress threshold register 
*
* INPUTS:
*    dev - pointer to device handle
*    e_thr - transmit threshold for egress HYST FIFO
*    m_thr - transmit threshold for main data FIFO
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
MTD_STATUS mtd_msec_set_egr_thr(MTD_DEV *dev, MTD_U16 port, MTD_U8 e_thr, MTD_U8 m_thr)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr =MTD_SI_EGR_THR;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, e_thr, 11, 7);
    mtd_msec_bits_write(&data, m_thr, 6, 0);
    retVal = mtdMsecWritePortReg (dev, port, addr, data);
    return retVal;
}
/*****************************************************************************
*  mtd_msec_set_egr_gen_miss_act
*
* DESCRIPTION:
*    Egress Gen Register
*
* INPUTS:
*    dev - pointer to device handle
*    act - action field for missing lookup match packet:
*       2'b00 - bypass, 2'b01 drop, 2'b10 loopback
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
MTD_STATUS mtd_msec_set_egr_gen_miss_act(MTD_DEV *dev, MTD_U16 port, MTD_INT act)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr =MTD_SI_EGR_GEN;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, act, 9, 8);
    retVal = mtdMsecWritePortReg (dev, port, addr, data);
    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_egr_reset
*
* DESCRIPTION:
*   egress path soft reset 
*
* INPUTS:
*    dev - pointer to device handle
*    rs - reset flag
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
MTD_STATUS mtd_msec_set_egr_reset(MTD_DEV *dev, MTD_U16 port, MTD_INT rs)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr =MTD_SI_EGR_GEN;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bit_write(data, rs, 2);
    retVal = mtdMsecWritePortReg (dev, port, addr, data);
    return retVal;
}
/*****************************************************************************
*  mtd_msec_set_igr_reset
*
* DESCRIPTION:
*   ingress path soft reset 
*
* INPUTS:
*    dev - pointer to device handle
*    rs - reset flag
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
MTD_STATUS mtd_msec_set_igr_reset(MTD_DEV *dev, MTD_U16 port, MTD_INT rs)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_SI_IGR_GEN;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bit_write(data, rs, 2);
    retVal = mtdMsecWritePortReg (dev, port, addr, data);
    return retVal;
}
/*****************************************************************************
*  mtd_msec_path_soft_reset
*
* DESCRIPTION:
*   egress and ingress path soft reset 
*
* INPUTS:
*    dev - pointer to device handle
*    rs - reset flag
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
MTD_STATUS mtd_msec_path_soft_reset(MTD_DEV *dev, MTD_U16 port, MTD_INT rs)
{
    MTD_STATUS   retVal = MTD_OK;
    retVal = mtd_msec_set_egr_reset(dev, port, rs);

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("msec_set_egr_reset Failed\n");
        return(retVal);
    }
    retVal = mtd_msec_set_igr_reset(dev, port, rs);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("msec_set_igr_reset Failed\n");
        return(retVal);
    }
    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_clr_read
*
* DESCRIPTION:
*   Enable or disable clear-on-read statistics behavior 
*
* INPUTS:
*    dev - pointer to device handle
*    clr - clear flag
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
MTD_STATUS mtd_msec_set_clr_read(MTD_DEV *dev, MTD_U16 port, MTD_INT clr)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr =MTD_SI_EGR_GEN;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bit_write(data, clr, 1);
    retVal = mtdMsecWritePortReg (dev, port, addr, data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }


    addr = MTD_SI_IGR_GEN;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bit_write(data, clr, 1);
    retVal = mtdMsecWritePortReg (dev, port, addr, data);
    return retVal;
}
/*****************************************************************************
*  mtd_msec_set_igr_short_pkt_sz
*
* DESCRIPTION:
*   set ingress short packet size 
*
* INPUTS:
*    dev - pointer to device handle
*    sz - short packet size
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
MTD_STATUS mtd_msec_set_igr_short_pkt_sz(MTD_DEV *dev, MTD_U16 port, MTD_INT sz)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_SI_IGR_PKT_SZ;
    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, sz, 15, 8);
    retVal = mtdMsecWritePortReg (dev, port, addr, data);

    return retVal;
}

/*****************************************************************************
* mtd_msec_set_ict_trail_sz
*
* DESCRIPTION:
*   set ICT trail size 
*
* INPUTS:
*    dev - pointer to device handle
*    sz - trail size
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
MTD_STATUS mtd_msec_set_ict_trail_sz(MTD_DEV *dev, MTD_U16 port, MTD_INT sz)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_SI_IGR_PKT_SZ;
    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, sz, 7, 0);
    retVal = mtdMsecWritePortReg (dev, port, addr, data);

    return retVal;
}

/* set ingress check action fields 2'b00 - bypass, 2'b01 - drop, 2'b10 -redir */
/*****************************************************************************
*  mtd_msec_set_igr_chk_act
*
* DESCRIPTION:
*   set ingress check action fields 
*
* INPUTS:
*    dev - pointer to device handle
*    igr_act - structure for ingress action fields
*      - 2'b00 - bypass
*      - 2'b01 - drop
*      - 2'b10 - redir 
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
MTD_STATUS mtd_msec_set_igr_chk_act(MTD_DEV *dev, MTD_U16 port, MTD_IGR_CHK_ACT_T *igr_act)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_SI_IGR_CHK_ACT;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, igr_act->bad_tag, 25, 24);
    mtd_msec_bits_write(&data, igr_act->notag, 23, 22);
    mtd_msec_bits_write(&data, igr_act->untagged, 21, 20);
    mtd_msec_bits_write(&data, igr_act->notusingsa, 19, 18);
    mtd_msec_bits_write(&data, igr_act->unusedsa, 17, 16);
    mtd_msec_bits_write(&data, igr_act->nosci, 15, 14);
    mtd_msec_bits_write(&data, igr_act->unknownsci, 13, 12);
    mtd_msec_bits_write(&data, igr_act->late, 11, 10);
    mtd_msec_bits_write(&data, igr_act->notvalid, 9, 8);
    mtd_msec_bits_write(&data, igr_act->invalid, 7, 6);
    mtd_msec_bits_write(&data, igr_act->delayed, 5, 4);
    mtd_msec_bits_write(&data, igr_act->unchecked, 3, 2);    
    mtd_msec_bits_write(&data, igr_act->ok, 1, 0);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    return retVal;
}

/*****************************************************************************
*  mtd_msec_get_igr_chk_act
*
* DESCRIPTION:
*   get ingress check action fields 
*
* INPUTS:
*    dev - pointer to device handle
* 
* OUTPUTS:
*      igr_act - structure for ingress action fields
*          - 2'b00 - bypass
*          - 2'b01 - drop
*          - 2'b10 - redir 
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_igr_chk_act (MTD_DEV *dev, MTD_U16 port, MTD_IGR_CHK_ACT_T *igr_act)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_SI_IGR_CHK_ACT;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    igr_act->bad_tag = mtd_msec_bits_get(data, 25, 24);
    igr_act->notag = mtd_msec_bits_get(data, 23, 22);
    igr_act->untagged = mtd_msec_bits_get(data, 21, 20);
    igr_act->notusingsa = mtd_msec_bits_get(data, 19, 18);
    igr_act->unusedsa = mtd_msec_bits_get(data, 17, 16);
    igr_act->nosci = mtd_msec_bits_get(data, 15, 14);
    igr_act->unknownsci = mtd_msec_bits_get(data, 13, 12);
    igr_act->late = mtd_msec_bits_get(data, 11, 10);
    igr_act->notvalid = mtd_msec_bits_get(data, 9, 8);
    igr_act->invalid = mtd_msec_bits_get(data, 7, 6);
    igr_act->delayed = mtd_msec_bits_get(data, 5, 4);
    igr_act->unchecked = mtd_msec_bits_get(data, 3, 2);    
    igr_act->ok = mtd_msec_bits_get(data, 1, 0);
    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_igr_rpy_var
*
* DESCRIPTION:
*   set ingress path replay variable 
*
* INPUTS:
*    dev - pointer to device handle
*    rpy - replay variable
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
MTD_STATUS mtd_msec_set_igr_rpy_var (MTD_DEV *dev, MTD_U16 port, MTD_RPY_T *rpy)
{
    MTD_STATUS   retVal = MTD_OK;    
    MTD_U16 addr;
    MTD_U32 data;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_SI_IGR_RPY_WND;
    retVal = mtdMsecWritePortReg (dev, port, addr, rpy->replay_window);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    addr = MTD_SI_IGR_CHK_CTL;
    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bit_write(data, rpy->sliding_window, 4);
    mtd_msec_bits_write(&data, rpy->validate_frames, 3, 2);
    mtd_msec_bit_write(data, rpy->replay_protect, 1);
    retVal = mtdMsecWritePortReg (dev, port, addr, data);
    return retVal;
}
/*****************************************************************************
*  mtd_msec_get_igr_rpy_var
*
* DESCRIPTION:
*   get ingress path replay variable 
*
* INPUTS:
*    dev - pointer to device handle
* 
* OUTPUTS:
*    rpy - replay variable
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_igr_rpy_var (MTD_DEV *dev, MTD_U16 port, MTD_RPY_T *rpy)
{
    MTD_STATUS   retVal = MTD_OK;    
    MTD_U16 addr;
    MTD_U32 data;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_SI_IGR_RPY_WND;
    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    rpy->replay_window = data;
    addr = MTD_SI_IGR_CHK_CTL;
    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    rpy->sliding_window = mtd_msec_bit_get(data, 4);
    rpy->validate_frames = mtd_msec_bits_get(data, 3, 2);
    rpy->replay_protect = mtd_msec_bit_get(data, 1);
    return retVal;
}
/* Egress Context Front Table 383:352 */
/*****************************************************************************
*  mtd_msec_set_ect_act_fld
*
* DESCRIPTION:
*   set egress Context Front Table action field
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
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
MTD_STATUS mtd_msec_set_ect_act_fld (MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num, MTD_ACT_FLD *act_fld)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;
    MTD_U8 rc_idx;
    MTD_U8 auth_off_sel;
    MTD_U8 enc_off_sel;
    MTD_U8 enc_en;
    MTD_U8 auth_en;


    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    /* TCI 359:352, RC_IDX 365:360, */
    addr =MTD_SI_ECT_FR + ent_num *32 + 22;
    if(act_fld->drop)
    {
        rc_idx = 0;
        auth_off_sel = 0;
        enc_off_sel = 0;
        auth_en =0;
        enc_en =0;
    }
    else
    {
        rc_idx = act_fld->set_idx;
        auth_en = act_fld ->auth_en;
        enc_en = act_fld->enc_en;
        auth_off_sel = 0;
        /* enc_off_sel =  MTD_ENV_EPR_MACSEC_PTR; */ /* commented out for CQ 6563 */
        enc_off_sel = MTD_ENV_EPR_COT_PTR;
    }

    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, act_fld->tci, 7, 0);
    mtd_msec_bits_write(&data, rc_idx, 13, 8);
    mtd_msec_bit_write(data, auth_en, 14);
    mtd_msec_bit_write(data, enc_en, 15);
    mtd_msec_bits_write(&data, act_fld->enc_start_adj, 23, 16);
    mtd_msec_bits_write(&data, auth_off_sel, 26, 24);
    mtd_msec_bits_write(&data, enc_off_sel, 29, 27);
    mtd_msec_bit_write(data, act_fld->redir, 30);
    mtd_msec_bit_write(data, act_fld->drop, 31);
    retVal = mtdMsecWritePortReg(dev, port, addr, data);

    return retVal;
}


/* Egress Context Front Table 383:352 */
/*****************************************************************************
*  mtd_msec_get_ect_act_fld
*
* DESCRIPTION:
*   get egress Context Front Table action field
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
* 
* OUTPUTS:
*    act_fld - structure for action field
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_ect_act_fld (MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num, MTD_ACT_FLD *act_fld)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;
//    MTD_U8 auth_off_sel;
//    MTD_U8 enc_off_sel;


    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    /* TCI 359:352, RC_IDX 365:360, */
    addr =MTD_SI_ECT_FR + ent_num *32 + 22;

    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    act_fld->tci = mtd_msec_bits_get(data, 7, 0);
    act_fld->set_idx = mtd_msec_bits_get(data, 13, 8);
    act_fld->auth_en = mtd_msec_bit_get(data, 14);
    act_fld->enc_en = mtd_msec_bit_get(data, 15);
    act_fld->enc_start_adj = mtd_msec_bits_get(data, 23, 16);
//    auth_off_sel = mtd_msec_bits_get(data, 26, 24);
//    enc_off_sel = mtd_msec_bits_get(data, 29, 27);
    act_fld->redir = mtd_msec_bit_get(data, 30);
    act_fld->drop = mtd_msec_bit_get(data, 31);
    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_ect_front_ent
*
* DESCRIPTION:
*   set egress Context Front Table entry
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    ctx - structure for context entry
*    act_fld - action field
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
MTD_STATUS mtd_msec_set_ect_front_ent(MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num, MTD_CTX_T *ctx, MTD_ACT_FLD *act_fld)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;
    MTD_INT i, j;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
    if(mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    /* KEY 127:0 */
    addr =MTD_SI_ECT_FR + ent_num *32;

    for(i = 3; i>=0; i--)
    {
        data = 0;
        for(j=0; j<=3; j++)
            data = data << 8 | ctx->key[j+i*4];

        retVal = _mtdMsecWritePortReg (dev, port, addr + 6 - 2*i, data);        
        if(retVal != MTD_OK)
        {
            mtdSemGive(dev,dev->multiAddrSem);
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return(retVal);
        }

    }
    if(mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtdSemGive(dev,dev->multiAddrSem);
    /* calculate hkey */
    mtd_aes_hkey (ctx);
    /* HKEY 255:128 */
    addr =MTD_SI_ECT_FR + ent_num *32 + 8;
    mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
    if(mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }

    for(i = 3; i>=0; i--)
    {
        data = 0;
        for(j=0; j<=3; j++)
            data = data << 8 | ctx->hkey[j+i*4];
        retVal = _mtdMsecWritePortReg (dev, port, addr + 6 - 2*i, data);
        if(retVal != MTD_OK)
        {
            mtdSemGive(dev,dev->multiAddrSem);
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return(retVal);
        }

    }
    /* SCI 319:256 */
    addr =MTD_SI_ECT_FR + ent_num *32 + 16;
    data = (MTD_U32) (ctx->sci & 0xFFFFFFFF);
    retVal = _mtdMsecWritePortReg(dev, port, addr, data);
    if(retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    addr += 2;
    data = (MTD_U32) (ctx->sci >> 32);
    retVal = _mtdMsecWritePortReg(dev, port, addr, data);
    if(retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }


    /* PN 351:320, tci and act_fld 381:352
       Note: must write in pair with incr order */
    addr += 2;
    data = ctx->pn;
    retVal = _mtdMsecWritePortReg(dev, port, addr, data);    
    mtd_msec_set_ect_act_fld(dev, port, ent_num, act_fld);
    if(mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtdSemGive(dev,dev->multiAddrSem);
    return retVal;
}

/* set authentication stop bits in ECT_BK table */
/*****************************************************************************
*  mtd_msec_set_ect_bk_ent
*
* DESCRIPTION:
*   set egress Context Back Table entry
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
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
MTD_STATUS mtd_msec_set_ect_bk_ent (MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num, MTD_U8 asa)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;
    MTD_INT i;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr =MTD_SI_ECT_BK + ent_num / 4;
    i = (ent_num % 4) * 8;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, asa, i+7, i);
    retVal = mtdMsecWritePortReg (dev, port, addr, data);
    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_igr_retain_hdr
*
* DESCRIPTION:
*   set ingress retain header
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    retain_hdr - retain header flag
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
MTD_STATUS mtd_msec_set_igr_retain_hdr (MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num, MTD_INT retain_hdr)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
    if(mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    /* MTD_SI_ICT_FR 282:256 */
    addr = MTD_SI_ICT_FR + ent_num *32 + 16;
    retVal = _mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bit_write(data, retain_hdr, 25);    
    retVal = _mtdMsecWritePortReg(dev, port, addr, data);
    if(retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    /* must write 64bits in order for the write to be successful. */
    retVal = _mtdMsecReadPortReg(dev, port, addr+2, &data);
    if(retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    retVal = _mtdMsecWritePortReg(dev, port, addr+2, data);
    if(mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtdSemGive(dev,dev->multiAddrSem);

    return retVal;
}
/*****************************************************************************
*  mtd_msec_get_igr_retain_hdr
*
* DESCRIPTION:
*   get ingress retain header
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
* 
* OUTPUTS:
*        None
*
* RETURNS:
*    retain_hdr - retain header flag
*
* COMMENTS:
*
*******************************************************************************/
int mtd_msec_get_igr_retain_hdr (MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;
    MTD_INT retain_hdr;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    /* MTD_SI_ICT_FR 282:256 */
    addr = MTD_SI_ICT_FR + ent_num *32 + 16;
    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    retain_hdr = mtd_msec_bit_get(data, 25);
    return retain_hdr;
}
/*****************************************************************************
*  mtd_msec_set_ict_act_fld
*
* DESCRIPTION:
*   set ICT action field
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    act_fld - action field
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
MTD_STATUS mtd_msec_set_ict_act_fld (MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num, MTD_ACT_FLD *act_fld)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;
    MTD_U8 rc_idx;
    MTD_U8 auth_off_sel;
    MTD_U8 dec_off_sel;


    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
    if(mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    /* MTD_SI_ICT_FR 282:256 */
    addr = MTD_SI_ICT_FR + ent_num *32 + 16;

    rc_idx = act_fld->set_idx;
    auth_off_sel = 0;
    dec_off_sel =  MTD_ENV_IPR_MACSEC_PTR;

    retVal = _mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bit_write(data, act_fld->auth_en, 0);
    mtd_msec_bit_write(data, act_fld->drop, 1);
    mtd_msec_bits_write(&data, auth_off_sel, 4, 2);
    mtd_msec_bits_write(&data, dec_off_sel, 7, 5);
    mtd_msec_bits_write(&data, act_fld->enc_start_adj, 15, 8);
    mtd_msec_bits_write(&data, rc_idx, 23, 16);
    mtd_msec_bit_write(data, act_fld->retain_hdr, 25);
    mtd_msec_bit_write(data, act_fld->redir, 26);
    retVal = _mtdMsecWritePortReg(dev, port, addr, data);
    if(retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    /* must write 64bits in order for the write to be successful. */
    retVal = _mtdMsecReadPortReg(dev, port, addr+2, &data);
    if(retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    retVal = _mtdMsecWritePortReg(dev, port, addr+2, data);
    if(mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtdSemGive(dev,dev->multiAddrSem);
    return retVal;
}
/*****************************************************************************
*  mtd_msec_get_ict_act_fld
*
* DESCRIPTION:
*   get ICT action field
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
* 
* OUTPUTS:
*    act_fld - structure for action field
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_ict_act_fld (MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num, MTD_ACT_FLD *act_fld)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;


    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    /* MTD_SI_ICT_FR 282:256 */
    addr = MTD_SI_ICT_FR + ent_num *32 + 16;


    retVal = mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    act_fld->auth_en = mtd_msec_bit_get(data,  0);
    act_fld->drop = mtd_msec_bit_get(data, 1);
    act_fld->enc_start_adj = mtd_msec_bits_get(data,  15, 8);
    act_fld->set_idx = mtd_msec_bits_get(data, 23, 16);
    act_fld->retain_hdr = mtd_msec_bit_get(data,  25);
    act_fld->redir = mtd_msec_bit_get(data,  26);
    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_ict_front_ent
*
* DESCRIPTION:
   set ICT front entry
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    ctx - structure for context fields
*    act_fld - action field
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
MTD_STATUS mtd_msec_set_ict_front_ent(MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num, MTD_CTX_T *ctx, MTD_ACT_FLD *act_fld)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;
    MTD_INT i,j;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    /* KEY 127:0 */
    mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
    if(mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    addr = MTD_SI_ICT_FR + ent_num *32;
    for(i = 3; i>=0; i--)
    {
        data = 0;
        for(j=0; j<=3; j++)
            data = data << 8 | ctx->key[j+i*4];

        retVal = _mtdMsecWritePortReg (dev, port, addr + 6 - 2*i, data);        
        if(retVal != MTD_OK)
        {
            mtdSemGive(dev,dev->multiAddrSem);
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return(retVal);
        }

    }
    if(mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtdSemGive(dev,dev->multiAddrSem);
    /* calculate hkey */
    mtd_aes_hkey (ctx);
    /* HKEY 255:128 */
    mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
    if(mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    addr = MTD_SI_ICT_FR + ent_num *32 + 8;
    for(i = 3; i>=0; i--)
    {
        data = 0;
        for(j=0; j<=3; j++)
            data = data << 8 | ctx->hkey[j+i*4];

        retVal = _mtdMsecWritePortReg (dev, port, addr + 6 - 2*i, data);        
        if(retVal != MTD_OK)
        {
            mtdSemGive(dev,dev->multiAddrSem);
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return(retVal);
        }

    }
    addr = MTD_SI_IGR_NXT_PN + ent_num *4;
    retVal = _mtdMsecWritePortReg (dev, port, addr, ctx->pn);
    /* 64-bit write has to be done in order for the write to complete */
    retVal = _mtdMsecReadPortReg (dev, port, addr+2, &data);
    if(retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    retVal = _mtdMsecWritePortReg (dev, port, addr+2, data);
    if(mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtdSemGive(dev,dev->multiAddrSem);
    mtd_msec_set_ict_act_fld(dev, port, ent_num, act_fld);
    return retVal;

}

/*****************************************************************************
*  mtd_msec_set_elu_match_en
*
* DESCRIPTION:
*   set ELU match enable
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    match_en - structure for match enable
*    flag_en - flag enable bits
*    flag_data - flag data bits
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
MTD_STATUS mtd_msec_set_elu_match_en (MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num, MTD_MATCH_EN *match_en, MTD_U8 flag_en, MTD_U8 flag_data)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;


    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr =MTD_SI_ELU + ent_num *32 + 16;
    data = 0;
    /* bits set according to EPR Output Parser Vector bitmap */
    /* From High to Low:
    da(6b), sa(6b), cot(4b), vlan(2b), etype(2b), rsvd(12b)
    changed to
    da(6b), sa(6b), cot(2b), vlan(2b), taggedpayloadetype(2b), 
    untaggedpayloadetype(2b), rsvd(12b)    
    Note: taggedpayloadetype is the payload etype of vlan tagged frame; 
    untaggedpayloadetype is for non-vlan tagged frame
    */
    if(match_en->en_vlan)
    {
        mtd_msec_bits_write(&data, match_en->en_et, 15, 14);
    }
    else
    {
        mtd_msec_bits_write(&data, match_en->en_et, 13, 12);
    }
    mtd_msec_bits_write(&data, match_en->en_vlan, 17, 16);
    mtd_msec_bits_write(&data, 0, 19, 18);
    mtd_msec_bits_write(&data, match_en->en_sa, 25, 20);
    mtd_msec_bits_write(&data, match_en->en_da, 31, 26);

    mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
    if(mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    retVal = _mtdMsecWritePortReg(dev, port, addr, data);
    if(retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }
    addr += 2;
    data = (flag_en * 256 + flag_data);
    retVal = _mtdMsecWritePortReg(dev, port, addr, data);
    if(mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtdSemGive(dev,dev->multiAddrSem);

    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_elu_match_data
*
* DESCRIPTION:
*   set ELU match data
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    match_fld - structure for match data fields
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
MTD_STATUS mtd_msec_set_elu_match_data(MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num, MTD_MATCH_FLD * match_fld)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    /* From High to Low:
    da(48b), sa(48b), cot(32b), rsvd(4b), vlan(12b), etype(16b), rsvd(96b)
    changed to
    da(48b), sa(48b), cot(16b), rsvd(4b), vlan(12b), taggedpayloadetype(16b), 
    untaggedpayloadetype(16b), rsvd(96b)
    Note: taggedpayloadetype is the payload etype of vlan tagged frame; 
    untaggedpayloadetype is for non-vlan tagged frame
    */
    mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
    if(mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    addr =MTD_SI_ELU + ent_num * 32 + 4;
    retVal = _mtdMsecReadPortReg (dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    retVal = _mtdMsecWritePortReg(dev, port, addr, data);
    if(retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    addr =MTD_SI_ELU + ent_num *32 + 6;
    data = (match_fld->et << 16) | match_fld->et;
    /*data = match_fld ->et; */
    retVal = _mtdMsecWritePortReg(dev, port, addr, data);
    if(retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    if(mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtdSemGive(dev,dev->multiAddrSem);

    addr =MTD_SI_ELU + ent_num *32 + 8;
    /*retVal = mtdMsecReadPortReg (dev, port, addr, &data); */
    data = match_fld->vlan;

    mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
    if(mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    retVal = _mtdMsecWritePortReg(dev, port, addr, data);
    if(retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    addr =MTD_SI_ELU + ent_num *32 + 10;
    data = (MTD_U32) (match_fld->sa & 0xFFFFFFFF);
    retVal = _mtdMsecWritePortReg(dev, port, addr, data);
    if(retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    if(mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtdSemGive(dev,dev->multiAddrSem);

    addr += 2;
    data =(MTD_32)( (match_fld->sa >> 32) | ((match_fld->da & 0xFFFF) << 16));

    mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
    if(mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    retVal = _mtdMsecWritePortReg(dev, port, addr, data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    addr += 2;
    data = (MTD_U32) (match_fld->da >> 16);
    retVal = _mtdMsecWritePortReg(dev, port, addr, data);
    if(mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtdSemGive(dev,dev->multiAddrSem);
    return retVal;
}

/* set egress parser mask eg. from_bit 140, to_bit 143 to mask off CFI bits of vlan*/
/*****************************************************************************
*  mtd_msec_cfg_egr_pmask
*
* DESCRIPTION:
*   set egress parser mask eg. from_bit 140, to_bit 143 to mask off CFI bits of
*   vlan
*
* INPUTS:
*    dev - pointer to device handle
*    flag - bitmask data
*    to_bit - to bit
*    from_bit - from bit
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
MTD_STATUS mtd_msec_cfg_egr_pmask(MTD_DEV *dev, MTD_U16 port, MTD_INT flag, MTD_INT to_bit, MTD_INT from_bit)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U32 data;
    MTD_U16 addr1, addr2;
    MTD_INT i;


    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr1 =MTD_SI_EGR_PMSK + (from_bit / 32)*2;
    addr2 =MTD_SI_EGR_PMSK + (to_bit / 32)*2;
    if(addr1 != addr2)
    {
        MTD_DBG_ERROR("incorrect bit setting.");
        return -1;
    }
    if(addr1 == addr2)
    {
        retVal = mtdMsecReadPortReg(dev, port, addr1, &data);
        if(retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Read Failed\n");
            return(retVal);
        }
        for(i=(from_bit % 32);i<=(to_bit % 32);i++)
        {
            if(flag)
                mtd_msec_bit_set(data, i);
            else
                mtd_msec_bit_clear(data, i);
        }
        retVal = mtdMsecWritePortReg (dev, port, addr1, data);
        if(retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return(retVal);
        }

    }
    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_elu_ent
*
* DESCRIPTION:
*    Program ELU Table Entry
*
* INPUTS:
*    dev Device ID
*    ent_num Lookup table entry number (0-31)
*    flag_en 8-bit bit field enabling match on particular packet types
*    flag_data 8-bit bit field showing value to match on.
   - 0: Match on flag not set
   - 1: Match on flag set
*    match_en structure enabling match on particular fields in the packet
*    match_fld structure containing values to be matched against packet fields
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
MTD_STATUS mtd_msec_set_elu_ent(MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num, MTD_U8 flag_en, MTD_U8 flag_data, MTD_MATCH_EN *match_en, MTD_MATCH_FLD* match_fld)
{
    MTD_STATUS   retVal = MTD_OK;


    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    if(match_en->en_vlan)
    {
        retVal = mtd_msec_cfg_egr_pmask(dev, port, 0, 143, 140);
        if(retVal != MTD_OK)
        {
            MTD_DBG_ERROR("msec_cfg_egr_pmask Failed\n");
            return(retVal);
        }
    }
    retVal = mtd_msec_set_elu_match_data(dev, port, ent_num, match_fld);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("msec_set_elu_match_data Failed\n");
        return(retVal);
    }
    retVal = mtd_msec_set_elu_match_en(dev, port, ent_num, match_en, flag_en, flag_data);

    return retVal;
}
/*****************************************************************************
*  mtd_msec_set_ilu_match_en
*
* DESCRIPTION:
*   set ILU match enable
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    match_en - structure for match enable
*    flag_en - flag enable bits
*    flag_data - flag data bits
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
MTD_STATUS mtd_msec_set_ilu_match_en (MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num, MTD_MATCH_EN *match_en, MTD_U8 flag_en, MTD_U8 flag_data)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;


    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_SI_ILU + ent_num *32 + 16;
    data = 0;
    /* bits set according to IPR Output Parser Vector bitmap 
     SCI: 0~7, PN: 8~11, SL: 12, TCI: 13, ... ETH: 18~19, SA: 20~25, DA:26~31
    */
    if(match_en->en_sci)
        retVal = mtd_msec_bits_write(&data, match_en->en_sci, 7, 0);
    else
        retVal = mtd_msec_bits_write(&data, 0, 7, 0);
    if(match_en->en_an)
        mtd_msec_bit_set(data, 13);
    else
        mtd_msec_bit_clear(data, 13);
    if (match_en->en_et)
        retVal = mtd_msec_bits_write(&data, match_en->en_et, 19, 18);
    if (match_en->en_sa)
        retVal = mtd_msec_bits_write(&data, match_en->en_sa, 25, 20);
    if (match_en->en_da)
        retVal = mtd_msec_bits_write(&data, match_en->en_da, 31, 26);

    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }


    /* set flag_data and flag_en */
    addr += 2;
    data = flag_en * 256 + flag_data;
    retVal = mtdMsecWritePortReg(dev, port, addr, data);
    return retVal;
}
/*****************************************************************************
*  mtd_msec_set_ilu_match_data
*
* DESCRIPTION:
*  set ILU match data
* according to IPR Output Parse Vector bitmap *
* ~~~~~~~~~~ IPR defines   ~~~~~~~~~~
*   define  MTD_ENV_IPR_SCI          63:0
*   define  MTD_ENV_IPR_PN           95:64
*   define  MTD_ENV_IPR_SL           103:96
*   define  MTD_ENV_IPR_TCI          111:104
*   define  MTD_ENV_IPR_PHDR         143:128
*   define  MTD_ENV_IPR_ETH          159:144
*   define  MTD_ENV_IPR_MACSA        207:160
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    match_fld - structure for match data fields
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
MTD_STATUS mtd_msec_set_ilu_match_data(MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num, MTD_MATCH_FLD * match_fld)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_U32 data;


    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
    if(mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    addr = MTD_SI_ILU + ent_num *32;
    /* SCI - 63:0 */
    data = (MTD_U32) (match_fld->sci & 0xFFFFFFFF);    
    retVal = _mtdMsecWritePortReg(dev, port, addr, data);
    if(retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    addr += 2;
    data = (MTD_U32) (match_fld->sci >> 32);    
    retVal = _mtdMsecWritePortReg(dev, port, addr, data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    if(mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtdSemGive(dev,dev->multiAddrSem);

    mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
    if(mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    /* first 8B of MACsec header 127:64*/
    addr += 2; /* skip 95:64 */
    retVal = _mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    retVal = _mtdMsecWritePortReg(dev, port, addr, data);
    if(retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    /* TCI - 111:104, take AN field only */
    addr += 2;
    retVal = _mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, (match_fld->tci & 0x3), 15, 8);
    retVal = _mtdMsecWritePortReg(dev, port, addr, data);

    /* EtherType - 159:144 */
    addr = MTD_SI_ILU + ent_num *32 + 8;
    retVal = _mtdMsecReadPortReg(dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }
    mtd_msec_bits_write(&data, (match_fld->et), 31, 16);
    retVal = _mtdMsecWritePortReg(dev, port, addr, data);
    
    /* SA - 207:160 */
    /* DA - 255:208 */
    addr = MTD_SI_ILU + ent_num *32 + 10;
    data = (MTD_U32) (match_fld->sa & 0xFFFFFFFF);
    retVal = _mtdMsecWritePortReg(dev, port, addr, data);
    if(retVal != MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    if(mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtdSemGive(dev,dev->multiAddrSem);

    addr += 2;
    data =(MTD_32)( (match_fld->sa >> 32) | ((match_fld->da & 0xFFFF) << 16));

    mtdSemTake(dev,dev->multiAddrSem,OS_WAIT_FOREVER);
    if(mtd_msec_set_link_down_reset(dev,port,0)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    retVal = _mtdMsecWritePortReg(dev, port, addr, data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    addr += 2;
    data = (MTD_U32) (match_fld->da >> 16);
    retVal = _mtdMsecWritePortReg(dev, port, addr, data);
    if(mtd_msec_set_link_down_reset(dev,port,1)!= MTD_OK)
    {
        mtdSemGive(dev,dev->multiAddrSem);
        MTD_DBG_ERROR("mtd_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }

    mtdSemGive(dev,dev->multiAddrSem);
    return retVal;
}
/*****************************************************************************
*  mtd_msec_cfg_igr_pmask
*
* DESCRIPTION:
*   set igress parser mask eg. from_bit 109, to_bit 112
*       flag: 0 - clear, 1 - set
*
*
* INPUTS:
*    dev - pointer to device handle
*    flag - bitmask data
*    to_bit - to bit
*    from_bit - from bit
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
MTD_STATUS mtd_msec_cfg_igr_pmask(MTD_DEV *dev, MTD_U16 port, MTD_INT flag, MTD_INT to_bit, MTD_INT from_bit)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U32 data;
    MTD_U16 addr1, addr2;
    MTD_INT i;


    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr1 = MTD_SI_IGR_PMSK + (from_bit / 32)*2;
    addr2 = MTD_SI_IGR_PMSK + (to_bit / 32)*2;
    if(addr1 != addr2)
    {
        MTD_DBG_ERROR("incorrect bit setting.");
        return -1;
    }
    if(addr1 == addr2)
    {
        retVal = mtdMsecReadPortReg(dev, port, addr1, &data);
        if(retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Read Failed\n");
            return(retVal);
        }
        for(i=(from_bit % 32);i<=(to_bit % 32);i++)
        {
            if(flag)
                mtd_msec_bit_set(data, i);
            else
                mtd_msec_bit_clear(data, i);
        }
        retVal = mtdMsecWritePortReg (dev, port, addr1, data);
        if(retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return(retVal);
        }

    }
    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_ilu_ent
*
* DESCRIPTION:
*   Program ILU Table Entry
*
* INPUTS:
*    dev Device ID
*    ent_num Lookup table entry number (0-31)
*    flag_en 8-bit bit field enabling match on particular packet types
*    flag_data 8-bit bit field showing value to match on.
*       - 0: Match on flag not set
*       - 1: Match on flag set
*    match_en structure enabling match on particular fields in the packet
*    match_fld structure containing values to be matched against packet fields
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
MTD_STATUS mtd_msec_set_ilu_ent(MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num, MTD_U8 flag_en, MTD_U8 flag_data, MTD_MATCH_EN *match_en, MTD_MATCH_FLD* match_fld)
{
    MTD_STATUS   retVal = MTD_OK;


    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    retVal = mtd_msec_set_ilu_match_data(dev, port, ent_num, match_fld);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("msec_set_ilu_match_data Failed\n");
        return(retVal);
    }
    retVal = mtd_msec_set_ilu_match_en(dev, port, ent_num, match_en, flag_en, flag_data);

    return retVal;
}

/*****************************************************************************
*  mtd_port_fips_obv
*
* DESCRIPTION:
*   FIPS observation
*
* INPUTS:
*    dev - pointer to device handle
*    fips_cfg - structure of MTD_FIPS_CFG_T
* 
* OUTPUTS:
*    fips_out - FIPs output data
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_port_fips_obv (MTD_DEV *dev,  MTD_U16 port, MTD_FIPS_CFG_T *fips_cfg, MTD_U32 *fips_out)
{
    MTD_STATUS   retVal;
    MTD_U16 addr;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    if(fips_cfg->egr_igr == 1)
    {
        if(fips_cfg->eng_type == 1)
        {
            addr = MTD_FIPS_VEC_OUT_EAES0;
        }
        else
        {
            addr = MTD_FIPS_VEC_OUT_EGHASH0;
        }
    }
    else
    {
        if(fips_cfg->eng_type == 1)
        {
            addr = MTD_FIPS_VEC_OUT_IAES0;
        }
        else
        {
            addr = MTD_FIPS_VEC_OUT_IGHASH0;
        }
    }

    retVal = mtdMsecReadPortReg (dev, port, addr, &fips_out[0]);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("Failed to call mtdMsecReadPortReg \n");
        return retVal;
    }
    addr +=2;
    retVal = mtdMsecReadPortReg (dev, port, addr, &fips_out[1]);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("Failed to call mtdMsecReadPortReg \n");
        return retVal;
    }
    addr +=2;
    retVal = mtdMsecReadPortReg (dev, port, addr, &fips_out[2]);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("Failed to call mtdMsecReadPortReg \n");
        return retVal;
    }
    addr +=2;
    retVal = mtdMsecReadPortReg (dev, port, addr, &fips_out[3]);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("Failed to call mtdMsecReadPortReg \n");
        return retVal;
    }

    return retVal;
}

/*****************************************************************************
*  mtd_clear_fips_vec
*
* DESCRIPTION:
*   clear FIPS vector
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_clear_fips_vec (MTD_DEV *dev,MTD_U16 port)
{
    MTD_STATUS   retVal;
    MTD_U16 addr;
    MTD_U32 data, i;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    retVal = mtdMsecWritePortReg(dev, port, MTD_FIPS_CTL, 0x0);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Write Failed\n");
        return(retVal);
    }

    addr = MTD_FIPS_VEC_IN3;
    data = 0x0;
    for(i = 4; i > 0; i--)
    {
        retVal = mtdMsecWritePortReg(dev, port, addr, data);
        if(retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return(retVal);
        }

        addr -=2;
    }

    return retVal;
}

/*******************************************************************************
* mtd_msec_set_fips_vec
*
* DESCRIPTION:
*            FIPS Vector setting
*            It programs 128 bit input vector (Plain Text).
*
* INPUTS:
*       dev  - pointer to MTD driver structure returned from mtdLoadDriver
*       port - The port number
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
MTD_STATUS mtd_msec_set_fips_vec 
(
    IN  MTD_DEV        *dev,
    IN  MTD_U16        port,
    IN  MTD_FIPS_CFG_T *fips_cfg
)
{
    MTD_STATUS   retVal;
    MTD_U16 addr;
    MTD_U32 data, i, j;


    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_FIPS_VEC_IN0;
    data = 0x0;

    for(i = 4; i > 0; i--)
    {
        for(j = 0; j < 4; j++)
        {
            mtd_msec_bits_write (&data, fips_cfg->fips_vec[((i*4)-j-1)], ((j*8)+7), (j*8));
        }

        retVal = mtdMsecWritePortReg (dev, port, addr, data);
        if(retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return(retVal);
        }

        addr +=2;
    }

    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_fips_key_in
*
* DESCRIPTION:
*   set FIPS encryption decryption key
*
* INPUTS:
*    dev - pointer to device handle
*    fips_cfg - structure of MTD_FIPS_CFG_T
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
MTD_STATUS mtd_msec_set_fips_key_in 
(
    IN  MTD_DEV        *dev,
    IN  MTD_U16        port,
    IN  MTD_FIPS_CFG_T *fips_cfg
)
{
    MTD_STATUS   retVal;
    MTD_U16 addr;
    MTD_U32 data;
    MTD_INT i, j;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    addr = MTD_FIPS_KEY_IN0;

    for(i = 4; i > 0; i--)
    {
        data  = 0x0;
        for(j = 0; j < 4; j++)
        {
            mtd_msec_bits_write (&data, fips_cfg->key[((i*4)-j-1)], ((j*8)+7), (j*8));
        }

        retVal = mtdMsecWritePortReg (dev, port, addr, data);
        if(retVal != MTD_OK)
        {
            MTD_DBG_ERROR("MSEC Write Failed\n");
            return(retVal);
        }

        addr +=2;
    }

    return retVal;
}

/*****************************************************************************
*  mtd_msec_get_egr_stats_val_lo
*
* DESCRIPTION:
*   Get egress individual statistics value Lower 32bits counter
*   ent_num only applies to per-entry based statistics
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    stat_idx - index for ENUM MTD_MSEC_EGR_STAT_E
* 
* OUTPUTS:
*        None
*
* RETURNS:
*       stats_lo - egress individual statistics value Lower 32bits counter       
*
* COMMENTS:
*
*******************************************************************************/
MTD_U32 mtd_msec_get_egr_stats_val_lo (MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num, MTD_MSEC_EGR_STAT_E stat_idx)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U32 stats_lo;
    MTD_U16 addr = 0;


    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    if(stat_idx >= MTD_EGR_SEC_STAT_PKT_PROT && stat_idx <= MTD_EGR_SEC_STAT_CTX_HIT)
        addr = stat_idx + ent_num * 4 ;
    else if(stat_idx >= MTD_EGR_SEC_STAT_OCT_PROT && stat_idx <= MTD_EGR_SEC_STAT_ETM_MISS_BAD)
        addr = stat_idx;

    retVal = mtdMsecReadPortReg (dev, port, addr, &stats_lo);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return(retVal);
    }

    return stats_lo;
}

/*****************************************************************************
* mtd_msec_get_egr_stats_val_hi
*
* DESCRIPTION:
*   Get egress individual statistics value higer 16 bits counter
*   ent_num only applies to per-entry based statistics
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    stat_idx - index for ENUM MTD_MSEC_EGR_STAT_E
* 
* OUTPUTS:
*        None
*
* RETURNS:
*       stats_hi - egress individual statistics value higer 16 bits counter
*
* COMMENTS:
*
*******************************************************************************/
MTD_U16 mtd_msec_get_egr_stats_val_hi (MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num, MTD_MSEC_EGR_STAT_E stat_idx)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U32 data;
    MTD_U16 stats_hi;
    MTD_U16 addr;


    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return 0xffff;

    if(stat_idx >= MTD_EGR_SEC_STAT_PKT_PROT && stat_idx <= MTD_EGR_SEC_STAT_CTX_HIT)
        addr = stat_idx + ent_num * 4 + 2;
    else if(stat_idx >= MTD_EGR_SEC_STAT_OCT_PROT && stat_idx <= MTD_EGR_SEC_STAT_ETM_MISS_BAD)
        addr = stat_idx + 2;
    else
        return 0xffff;

    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return 0xffff;
    }
    stats_hi = (MTD_U16) (data & 0xFFFF);
    return stats_hi;
}
/* Get ingress individual statistics value Lower 32bits counter
   ent_num only applies to per-entry based statistics
   */
/*****************************************************************************
* mtd_msec_get_igr_stats_val_lo
*
* DESCRIPTION:
*   Get ingress individual statistics value Lower 32bits counter
*   ent_num only applies to per-entry based statistics
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    stat_idx - index for ENUM MTD_MSEC_IGR_STAT_E
* 
* OUTPUTS:
*        None
*
* RETURNS:
*       stats_lo - ingress individual statistics value Lower 32bits counter
*
* COMMENTS:
*
*******************************************************************************/
MTD_U32 mtd_msec_get_igr_stats_val_lo (MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num, MTD_MSEC_IGR_STAT_E stat_idx)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U32 stats_lo;
    MTD_U16 addr = 0;


    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    if(stat_idx >= MTD_IGR_SEC_STAT_HIT && stat_idx <= MTD_IGR_SEC_STAT_NOTVALID)
        addr = stat_idx + ent_num * 4 ;
    else if(stat_idx >= MTD_IGR_SEC_STAT_OCT_VAL && stat_idx <= MTD_IGR_SEC_STAT_ETM_HIT)
        addr = stat_idx;

    retVal = mtdMsecReadPortReg (dev, port, addr, &stats_lo);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return 0xffff;
    }

    return stats_lo;
}

/*************************************************************************
*  mtd_msec_get_igr_stats_val_hi
*
* DESCRIPTION:
*   Get ingress individual statistics value higer 16 bits counter
*   ent_num only applies to per-entry based statistics
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    stat_idx - index for ENUM MTD_MSEC_IGR_STAT_E
* 
* OUTPUTS:
*        None
*
* RETURNS:
*       stats_hi - ingress individual statistics value higer 16 bits counter
*
* COMMENTS:
*
*******************************************************************************/
MTD_U16 mtd_msec_get_igr_stats_val_hi (MTD_DEV *dev, MTD_U16 port, MTD_INT ent_num, MTD_MSEC_IGR_STAT_E stat_idx)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U32 data;
    MTD_U16 stats_hi;
    MTD_U16 addr = 0;


    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return 0xffff;

    if(stat_idx >= MTD_IGR_SEC_STAT_HIT && stat_idx <= MTD_IGR_SEC_STAT_NOTVALID)
        addr = stat_idx + ent_num * 4 + 2;
    else if(stat_idx >= MTD_IGR_SEC_STAT_OCT_VAL && stat_idx <= MTD_IGR_SEC_STAT_ETM_HIT)
        addr = stat_idx + 2;

    retVal = mtdMsecReadPortReg (dev, port, addr, &data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("MSEC Read Failed\n");
        return 0xffff;
    }
    stats_hi = (MTD_U16) (data & 0xFFFF);
    return stats_hi;
}

/*****************************************************************************
*  mtd_msec_set_link_down_reset
*
* DESCRIPTION:
*  set macsec link down reset
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*     flag - 1: enable    0: disable   
* 
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_API_MACSEC_NOT_SUPPORT        - on error
*
* COMMENTS:
    Workaround for MACsec lockup issue. When link down reset bit is set, it holds MACsec data path 
    under resets for a couple of cycles whenever there is a link down event. Side effect occurs when 
    resetting the data path; the MACsec table registers are also held for reset, causing register access
    failure during the reset. To avoid this side effect, clears the reset bits before any MACsec register 
    access, then set the reset bits after that.  This workaround is required for X32x0/X2242/X33x0. 
*
*******************************************************************************/
MTD_STATUS mtd_msec_set_link_down_reset(MTD_DEV *dev, MTD_U16 port, MTD_INT flag)
{
    MTD_STATUS retVal = MTD_OK;
    MTD_U16 regAddr;
    MTD_U32 data;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    data = flag ? 1:0;
    data |= 0x3900;
    regAddr = 0x80B0;

    retVal = _mtdMsecWritePortReg(dev,port,regAddr,data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("Writing to phy reg failed.\n");
        return(retVal | MTD_API_FAIL_WRITE_REG);
    }

    return MTD_OK;
}

/*****************************************************************************
*  mtd_msec_set_link_down_detect
*
* DESCRIPTION:
*   set macsec link down detect
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*     flag - 1: enable    0: disable   
* 
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_API_MACSEC_NOT_SUPPORT        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_set_link_down_detect(MTD_DEV *dev, MTD_U16 port, MTD_INT flag)
{
    MTD_STATUS retVal = MTD_OK;
    MTD_U16 regAddr;
    MTD_U32 data;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    regAddr = 0x80B0;

    retVal = _mtdMsecReadPortReg(dev,port,regAddr,&data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("Reading to phy reg field failed.\n");
        return(retVal | MTD_API_FAIL_READ_REG);
    }

    data = flag ? (data|0x1000) : (data&0xefff);

    retVal = _mtdMsecWritePortReg(dev,port,regAddr,data);

    return retVal;
}

/*****************************************************************************
*  mtd_msec_set_delay_ext_reset
*
* DESCRIPTION:
*   set delay external reset
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*     flag - 1: enable    0: disable   
* 
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_API_MACSEC_NOT_SUPPORT        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_set_delay_ext_reset(MTD_DEV *dev, MTD_U16 port, MTD_INT flag)
{
    MTD_STATUS retVal = MTD_OK;
    MTD_U16 regAddr;
    MTD_U32 data;

    if(!MTD_DEV_MSECPTPCAPABLE(dev))
        return MTD_API_MACSEC_NOT_SUPPORT;

    regAddr = 0x80B0;

    retVal = _mtdMsecReadPortReg(dev,port,regAddr,&data);
    if(retVal != MTD_OK)
    {
        MTD_DBG_ERROR("Reading to phy reg field failed.\n");
        return(retVal | MTD_API_FAIL_READ_REG);
    }

    data = flag ? (data|0x2000) : (data&0xdfff);

    retVal = _mtdMsecWritePortReg(dev,port,regAddr,data);

    return retVal;
}
