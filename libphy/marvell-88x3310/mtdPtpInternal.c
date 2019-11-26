/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************************
* mtd_ptp_func.c
* 
* DESCRIPTION:
*       Internal functions of 1-step PTP.
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
#include "mtdAPIInternal.h"
#include "mtdMsecTypes.h"
#include "mtdMsecInternal.h"
#include "mtdPtp1step.h"
#include "mtdPtpApi.h"

//#include "../shared/pmeu.inc"
//#include "../shared/umeu.inc"

static MTD_UINT mtd_pr_init_data[] =
{
0x200ea, 0x0d008, 0x0c140, 0x28427, 0x2cc27, 0x29c4a, 0x2a44a, 0x2c417, 0x2e4aa, 0x2ecb7, 
0x2ac25, 0x28c37, 0x2b469, 0x2bc83, 0x294c6, 0x2f414, 0x0d840, 0x35452, 0x23836, 0x30000, 
0x0e050, 0x07008, 0x30000, 0x0d0c0, 0x7cb23, 0x7dddb, 0x7bddb, 0x33167, 0x0d8e0, 0x1d802, 
0x06040, 0x76b03, 0x1d804, 0x06040, 0x20003, 0x3700e, 0x30000, 0x1d808, 0x20028, 0x1d801, 
0x28427, 0x2cc27, 0x29c4a, 0x2a44a, 0x2c417, 0x2b469, 0x2bc83, 0x294c6, 0x2ac25, 0x28c37, 
0x2f414, 0x0d840, 0x35452, 0x30400, 0x1d801, 0x0d8a0, 0x35496, 0x30900, 0x0d8a0, 0x1e098, 
0x35497, 0x30900, 0x3702c, 0x0d8a0, 0x28427, 0x2cc27, 0x2ac25, 0x29c4a, 0x2a44a, 0x2c417, 
0x2b469, 0x2bc83, 0x294c6, 0x30000, 0x0d860, 0x0d8a0, 0x7c259, 0x0d8e0, 0x0d8e0, 0x7c359, 
0x0d8e0, 0x0d8e0, 0x7c359, 0x0d8e0, 0x0d8e0, 0x7c359, 0x0d8e0, 0x0d8e0, 0x743db, 0x1e453, 
0x2185e, 0x1e095, 0x1e494, 0x21067, 0x0d840, 0x1de4c, 0x35844, 0x24069, 0x35846, 0x24083, 
0x35840, 0x30900, 0x1d802, 0x1d806, 0x20028, 0x37022, 0x0d840, 0x0c081, 0x1d804, 0x1de8c, 
0x35884, 0x248ea, 0x1e050, 0x1de47, 0x3584a, 0x230ea, 0x1da44, 0x05900, 0x1c801, 0x35911, 
0x240bb, 0x3592f, 0x2408d, 0x35904, 0x24069, 0x35929, 0x24083, 0x35932, 0x2409f, 0x0d900, 
0x30000, 0x0d880, 0x1de8c, 0x35886, 0x248ea, 0x1d803, 0x37023, 0x0d900, 0x1d811, 0x1df08, 
0x20077, 0x37025, 0x0d860, 0x1de4a, 0x30300, 0x2d467, 0x28427, 0x2cc27, 0x2ac25, 0x29c4a, 
0x2a44a, 0x2b469, 0x2bc83, 0x294c6, 0x28c37, 0x0d840, 0x35452, 0x23836, 0x30000, 0x74ddb, 
0x1d802, 0x0f00c, 0x0f024, 0x0d860, 0x35841, 0x240a8, 0x37020, 0x30000, 0x37026, 0x30000, 
0x7d5ea, 0x0d860, 0x1e05b, 0x0e011, 0x0d9e0, 0x0d9a0, 0x3316e, 0x77928, 0x3722f, 0x1d802, 
0x0f02c, 0x1d801, 0x20028, 0x7d5ea, 0x1d802, 0x0f02c, 0x20028, 0x37021, 0x0d8e0, 0x2dcc1, 
0x2fcc1, 0x2f4ed, 0x30000, 0x1d801, 0x0d8e0, 0x358c0, 0x240c6, 0x3722d, 0x06050, 0x0d840, 
0x709dc, 0x37020, 0x0f00c, 0x1d801, 0x0f024, 0x0f01c, 0x0f07c, 0x0f074, 0x0f06c, 0x0f064, 
0x0f034, 0x0f03c, 0x1d805, 0x0f04c, 0x1d805, 0x775da, 0x0e037, 0x0e03e, 0x0d900, 0x30000, 
0x1d801, 0x37000, 0x37028, 0x0f07c, 0x1d808, 0x0f00c, 0x0f074, 0x0f06c, 0x0f064, 0x0f024, 
0x0f04c, 0x1d801, 0x0f018, 0x30000, 0x0c800, 0x3702f, 0x30000, 0x1d801, 0x0d8e0, 0x358c0, 
0x240f2, 0x3722d, 0x06050, 0x0f04c, 0x1d805, 0x0f00c, 0x0f024, 0x1d80f, 0x37006, 0x37027, 
0x0f060, 0x30000, 0xffffffff
};

static MTD_UINT mtd_ur_init_data[] =
{

0x2008d, 0x0d055, 0x46801, 0x0d1c0, 0x0d088, 0x7d1bf, 0x7f10e, 0x76913, 0x42000, 0x8c450, 
0x8c513, 0x8c489, 0x8c044, 0x20013, 0x42000, 0x8b450, 0x8b513, 0x8b489, 0x8b044, 0x75234, 
0x7ca1b, 0x0d110, 0x0d0d1, 0x0d192, 0x7061b, 0xd4230, 0xdc611, 0x7493e, 0x07e08, 0x0d148, 
0x1dd41, 0x71924, 0x40546, 0x8d754, 0x8d4d2, 0x2003e, 0x77926, 0x1d988, 0x40546, 0x0c141, 
0x1dd4d, 0x1df4d, 0x7f92e, 0x474e5, 0x8d450, 0x2003e, 0x3316f, 0x474e5, 0x434c4, 0x8d513, 
0x8d496, 0x2003e, 0x7493e, 0x7273e, 0x0d108, 0x7993b, 0x77c3b, 0x0fb10, 0x2003c, 0x0fb08, 
0x1dd01, 0x40d03, 0x0514a, 0x1db41, 0x1dd41, 0x76a44, 0x48942, 0x49082, 0x7079c, 0x1d94a, 
0x0d18f, 0x7524e, 0x72961, 0x535ba, 0x5b9db, 0xdbc0f, 0x330a8, 0x20061, 0x75961, 0x7078d, 
0x0d105, 0x70454, 0xd1e27, 0xd9a06, 0x0d112, 0x70458, 0xd4230, 0xdc611, 0x0d111, 0x35506, 
0x22061, 0x2305f, 0x0d110, 0x35507, 0x22061, 0xd4270, 0xdc651, 0x7316c, 0x330a8, 0x0d118, 
0x7fc69, 0x535b7, 0x5b9d8, 0xdbc0f, 0x2006c, 0x535b7, 0x5b9d8, 0xdbfef, 0x7d27d, 0x7597d, 
0x330a8, 0x640f0, 0x6c4d1, 0xec812, 0x5360d, 0x5ba2e, 0xdbc0f, 0x2587d, 0x7fe7d, 0x0d119, 
0x0e064, 0x0e06c, 0x0e074, 0x3310f, 0x0e07c, 0x74281, 0x48948, 0x8d3ce, 0x8d34c, 0x1d948, 
0x7d28f, 0x76185, 0x49944, 0x7418d, 0x7bf98, 0x7b7a2, 0x1d952, 0x4894a, 0x8d513, 0x8d491, 
0x45082, 0x40000, 0x30000, 0x76196, 0x48944, 0x71995, 0x434c4, 0x40000, 0x30000, 0x8d450, 
0x40000, 0x30000, 0x1d96a, 0x200b5, 0x1d962, 0x200b5, 0x75285, 0x7618d, 0x7bf9a, 0x7378d, 
0x0fe08, 0x200a4, 0x7418d, 0x0fe00, 0x0d14a, 0x1dd41, 0x1c96e, 0x0d1c1, 0x0fe2e, 0x351c6, 
0x240b2, 0x0fe2d, 0x351c6, 0x240b4, 0x0fe2f, 0x351c6, 0x240b4, 0x2008d, 0x1d954, 0x200b5, 
0x1d944, 0x48948, 0x8d4d2, 0x752bc, 0x7cabc, 0x434c4, 0x40000, 0x30000, 0x8d450, 0x40000, 
0x30000, 0x41400, 0x30000, 0xffffffff
};

/*************************************************************************/

#ifdef DEBUG_MTD
MTD_STATUS mtd_ptp_1step_dump_mac_statistics (MTD_U16 port, MTD_UINT *macValList)
{
    MTD_STATUS   retVal = MTD_OK;
    int n;
    MTD_DBG_INFO("\nDump all MAC statistics counters on dev dev_num.\n");
    for(n=0; n<1; n++)
    {
        int i = 0x2000;
        int macName = 0;
        while(mtd_ptp_1step_macNmList[macName]!=0)
        {
            MTD_UINT val = mtd_ptp_read_reg(port, i);
            macValList[macName] = val;
            i++;
            macName++;
        }
    }
    return retVal;
}

MTD_STATUS mtd_ptp_1step_dump_sysmac_statistics (MTD_U16 port, MTD_UINT *sysmacValList)
{
    MTD_STATUS   retVal = MTD_OK;
    int macName = 0;

    int n;
    MTD_DBG_INFO("\nDump all SYSMAC statistics counters on dev dev_num.\n");
    for(n=0; n<1; n++)
    {
        int i =(0x2000 + 32 * 4);
        while(mtd_ptp_1step_macNmList[macName]!=0)
        {
            MTD_UINT val = mtd_ptp_read_reg(port, i);
            sysmacValList[macName] = val;
            i++;
            macName++;
        }
    }
    return retVal;
}
#endif

MTD_STATUS mtd_ptp_1step_set_smac_loopback (MTD_U16 port, int en)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 regaddr = 0x8c02;
    MTD_U32 data = mtd_ptp_read_reg (port, regaddr);
  /* for 1G */
    if(en)
        mtd_msec_bit_set (data, 5);  /*13 for 10G */
    else
        mtd_msec_bit_clear (data, 5);
    retVal = mtd_ptp_write_reg(port, regaddr, data);
    return retVal;
}

/* Some PTP definitions */

/* common PTP init  */
MTD_STATUS mtd_ptp_common_init (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
  /* Setup STT_CTL */

    retVal = mtd_ptp_writecheck_reg(port, MTD_VN_EG_PTP+MTD_PTP_RF+5*MTD_PTP_ADDR_ADJ+MTD_PTP_PORT_OFF(port), 0x145);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, MTD_VN_IG_PTP+MTD_PTP_RF+5*MTD_PTP_ADDR_ADJ+MTD_PTP_PORT_OFF(port), 0x145);
    mtd_enable_ptp(port);
    return retVal;
}

/* PTP parser init */
MTD_STATUS mtd_ptp_parser_init (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;


  /* Egress only */
/*  retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_PMEU_PAM+27), 0x81ff); */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_PMEU_PAM+25*MTD_PTP_ADDR_ADJ), 0xca00);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_PMEU_PAM+26*MTD_PTP_ADDR_ADJ), 0x3b9a);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_PMEU_PAM+27*MTD_PTP_ADDR_ADJ), 0x8007);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_PMEU_PAM+28*MTD_PTP_ADDR_ADJ), 0x88b5);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_PMEU_PAM+29*MTD_PTP_ADDR_ADJ), 0x88b6);
    if(retVal!=MTD_OK) return retVal;
/*  retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_PMEU_PAM+30*MTD_PTP_ADDR_ADJ), 0xca00);
  retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_PMEU_PAM+31*MTD_PTP_ADDR_ADJ), 0x3b9a); */

/* .............. */

  /* Both ingress and egress paths */
  /* Write `PPED+16 `ENV_IPV4_LEN_MSK=0xf00 */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+16*MTD_PTP_ADDR_ADJ), 0xf00);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port)+16*MTD_PTP_ADDR_ADJ), 0xf00);
  /* Write `PPED+18 `LLC_HDR_MAX_LEN=1500 (decimal) */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+18*MTD_PTP_ADDR_ADJ), 1500);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port)+18*MTD_PTP_ADDR_ADJ), 1500);
    if(retVal!=MTD_OK) return retVal;
  /* Write `PPED+19 `ENV_MPLS_LBL_19_4=0 */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+19*MTD_PTP_ADDR_ADJ), 0);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port)+19*MTD_PTP_ADDR_ADJ), 0);
    if(retVal!=MTD_OK) return retVal;
  /* Write `PPED+20 `ENV_MPLS_LBL_3_0= MTD_VN_EG_PTP */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+20*MTD_PTP_ADDR_ADJ), 0x3000);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port)+20*MTD_PTP_ADDR_ADJ), 0x3000);
    if(retVal!=MTD_OK) return retVal;
  /* Write `PPED+21 `ENV_MPLS_LBL_MSK=0xf000 */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+21*MTD_PTP_ADDR_ADJ), 0xf000);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port)+21*MTD_PTP_ADDR_ADJ), 0xf000);
    if(retVal!=MTD_OK) return retVal;
  /* Write `PPED+22 `ENV_DSAP_SSAP_23_8=0xaaaa */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+22*MTD_PTP_ADDR_ADJ), 0xaaaa);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port)+22*MTD_PTP_ADDR_ADJ), 0xaaaa);
    if(retVal!=MTD_OK) return retVal;
  /* Write `PPED+23 `ENV_DSAP_SSAP_7_0=0x300 */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+23*MTD_PTP_ADDR_ADJ), 0x300);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port)+23*MTD_PTP_ADDR_ADJ), 0x300);
    if(retVal!=MTD_OK) return retVal;
  /* Write `PPED+24 `ENV_DSAP_SSAP_MSK=0xff00 */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+24*MTD_PTP_ADDR_ADJ), 0xff00);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port)+24*MTD_PTP_ADDR_ADJ), 0xff00);
    if(retVal!=MTD_OK) return retVal;
  /* Write `PPED+30 `NTP_DST_PRT=0x7b */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+30*MTD_PTP_ADDR_ADJ), 0x7b);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port)+30*MTD_PTP_ADDR_ADJ), 0x7b);
    if(retVal!=MTD_OK) return retVal;
  /* Write `PPED+31 `PTPG_DST_PRT=0x140 */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+31*MTD_PTP_ADDR_ADJ), 0x140);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port)+31*MTD_PTP_ADDR_ADJ), 0x140);
    return retVal;
}
MTD_STATUS mtd_ptp_set_udata ( MTD_U16 port, MTD_UINT * filedata, MTD_UINT baseaddr );

MTD_STATUS mtd_ptp_parser_set_udata (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT eg_addr = (MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_PMEU_UDATA);
    MTD_UINT ig_addr = (MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_PMEU_UDATA);
  /* Load egress parser udata */
    retVal = mtd_ptp_set_udata( port, mtd_pr_init_data, eg_addr);
    if(retVal!=MTD_OK) return retVal;
  /* Load ingress parser udata */
    retVal = mtd_ptp_set_udata( port, mtd_pr_init_data, ig_addr);
    return retVal;
}

MTD_STATUS mtd_ptp_parser_set_udata_ntp (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT eg_addr = (MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_PMEU_UDATA);
    MTD_UINT ig_addr = (MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_PMEU_UDATA);
  /* Load egress parser udata */
    retVal = mtd_ptp_set_udata( port, mtd_pr_init_data, eg_addr);
    if(retVal!=MTD_OK) return retVal;
  /* Load ingress parser udata */
    retVal = mtd_ptp_set_udata( port, mtd_pr_init_data, ig_addr);
    return retVal;
}
//MTD_STATUS mtd_ptp_check_udata ( MTD_U16 port, MTD_UINT * filedata, MTD_UINT baseaddr );


MTD_STATUS mtd_ptp_parser_check_udata (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT eg_addr = MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_PMEU_UDATA;
    MTD_UINT  ig_addr = MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_PMEU_UDATA;
  /* Check egress parser udata */
    retVal = mtd_ptp_check_udata( port, mtd_pr_init_data, eg_addr);
    if(retVal!=MTD_OK) return retVal;
  /* Check ingress parser udata */
    retVal = mtd_ptp_check_udata( port, mtd_pr_init_data, ig_addr);
    return retVal;
}

MTD_STATUS mtd_ptp_parser_check_udata_ntp (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT eg_addr = MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_PMEU_UDATA;
    MTD_UINT  ig_addr = MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_PMEU_UDATA;
  /* Check egress parser udata */
    retVal = mtd_ptp_check_udata( port, mtd_pr_init_data, eg_addr);
    if(retVal!=MTD_OK) return retVal;
  /* Check ingress parser udata */
    retVal = mtd_ptp_check_udata( port, mtd_pr_init_data, ig_addr);
    return retVal;
}

/* PTP update init */
MTD_STATUS mtd_ptp_update_init (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
  /*Both ingress and egress paths */
  /*Write `PPDD+23 Asymmetry[15:0] */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+23*MTD_PTP_ADDR_ADJ), 0x0);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_IG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+23*MTD_PTP_ADDR_ADJ), 0x0);
    if(retVal!=MTD_OK) return retVal;
  /*Write `PPDD+24 Asymmetry[31:16] */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+24*MTD_PTP_ADDR_ADJ), 0x0);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_IG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+24*MTD_PTP_ADDR_ADJ), 0x0);
    if(retVal!=MTD_OK) return retVal;
  /*Write `PPDD+25 `ENV_ALL_ONE_VAL=0xffff */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+25*MTD_PTP_ADDR_ADJ), 0xffff);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_IG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+25*MTD_PTP_ADDR_ADJ), 0xffff);
    if(retVal!=MTD_OK) return retVal;
  /*Write `PPDD+30 one_sec[15:0] */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+30*MTD_PTP_ADDR_ADJ), 0xca00);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_IG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+30*MTD_PTP_ADDR_ADJ), 0xca00);
    if(retVal!=MTD_OK) return retVal;
  /*Write `PPDD+31 one_sec[31:16] */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+31*MTD_PTP_ADDR_ADJ), 0x3b9a);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_IG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+31*MTD_PTP_ADDR_ADJ), 0x3b9a);
    if(retVal!=MTD_OK) return retVal;

  /*Egress path */
  /*Write `PPDD+26 `ENV_ONE_VAL */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+26*MTD_PTP_ADDR_ADJ), 1);
    if(retVal!=MTD_OK) return retVal;
 /*Write `PPDD+27 lat_adj[15:0] */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+27*MTD_PTP_ADDR_ADJ), (0x145*8+24));
    if(retVal!=MTD_OK) return retVal;
  /*Write `PPDD+28 lat_adj[31:16] */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+28*MTD_PTP_ADDR_ADJ), 0x0);
    if(retVal!=MTD_OK) return retVal;
  /*Write `PPDD+29 `ENV_ZERO_VAL */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+29*MTD_PTP_ADDR_ADJ), 0);
    if(retVal!=MTD_OK) return retVal;

  /*Ingress */
  /*Write `PPDD+26 LinkDelay[15:0] */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_IG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+26*MTD_PTP_ADDR_ADJ), 0x0);
    if(retVal!=MTD_OK) return retVal;
  /*Write `PPDD+27 LinkDelay[31:16] */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_IG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+27*MTD_PTP_ADDR_ADJ), 0x0);
    if(retVal!=MTD_OK) return retVal;
  /*Write `PPDD+28 `TST_HDR_ETYPE */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_IG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+28*MTD_PTP_ADDR_ADJ), 0x88b5);
    if(retVal!=MTD_OK) return retVal;
  /*Write `PPDD+29 `ENV_TST_RSV_MSK */
/*  retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_IG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+29*MTD_PTP_ADDR_ADJ), 0x8007); */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_IG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+29*MTD_PTP_ADDR_ADJ), 0x88b6);
    return retVal;
}

MTD_STATUS mtd_ptp_update_set_udata (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT  eg_addr = MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_UMEU_UDATA;
    MTD_UINT  ig_addr = MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_UMEU_UDATA;

  /* Load egress update udata */
    retVal = mtd_ptp_set_udata( port, mtd_ur_init_data, eg_addr);
    if(retVal!=MTD_OK) return retVal;
  /* Load ingress update udata */
    retVal = mtd_ptp_set_udata( port, mtd_ur_init_data, ig_addr);
    return retVal;
}
MTD_STATUS mtd_ptp_update_check_udata (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT  eg_addr = MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_UMEU_UDATA;
    MTD_UINT  ig_addr = MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_UMEU_UDATA;

  /* Check egress update udata */
    retVal = mtd_ptp_check_udata( port, mtd_ur_init_data, eg_addr);
    if(retVal!=MTD_OK) return retVal;
  /* Check ingress update udata */
    retVal = mtd_ptp_check_udata( port, mtd_ur_init_data, ig_addr);
    return retVal;
}

MTD_STATUS mtd_ptp_update_set_udata_ntp (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT  eg_addr = MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_UMEU_UDATA;
    MTD_UINT  ig_addr = MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_UMEU_UDATA;

  /* Load egress update udata */
    retVal = mtd_ptp_set_udata( port, mtd_ur_init_data, eg_addr);
    if(retVal!=MTD_OK) return retVal;
  /* Load ingress update udata */
    retVal = mtd_ptp_set_udata( port, mtd_ur_init_data, ig_addr);
    return retVal;
}
MTD_STATUS mtd_ptp_update_check_udata_ntp (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT  eg_addr = MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_UMEU_UDATA;
    MTD_UINT  ig_addr = MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_UMEU_UDATA;

  /* Check egress update udata */
    retVal = mtd_ptp_check_udata( port, mtd_ur_init_data, eg_addr);
    if(retVal!=MTD_OK) return retVal;
  /* Check ingress update udata */
    retVal = mtd_ptp_check_udata( port, mtd_ur_init_data, ig_addr);
    return retVal;
}

/* Load PTP udata into udata space */
MTD_STATUS mtd_ptp_set_udata (MTD_U16 port, MTD_UINT * filedata, MTD_UINT baseaddr )
{
    MTD_STATUS   retVal = MTD_OK;
    int word_index = 0;
    MTD_UINT word;
    MTD_DBG_INFO("Loading PTP microcode data addr 0x%x\n", baseaddr);
    while((word=*filedata)!=-1)
    {
        filedata++;
    /*PTP_DBG_INFO( ("0x%x 0x%x 0x%x" baseaddr word_index val] */
/*    retVal = mtd_ptp_writecheck_reg (baseaddr+word_index, word); */
        retVal = mtd_ptp_write_reg (port, baseaddr+word_index*MTD_PTP_ADDR_ADJ, word);
        if(retVal!=MTD_OK) return retVal;
        word_index ++;
    }
    return retVal;
}

/* Check PTP udata from file against udata space */
MTD_STATUS mtd_ptp_check_udata (MTD_U16 port, MTD_UINT * filedata, MTD_UINT baseaddr )
{
    MTD_STATUS   retVal = MTD_OK;
    int word_index= 0;
    int err = 0;
    MTD_UINT word;
    MTD_DBG_INFO("Checking PTP microcode data addr 0x%x\n",  baseaddr);
    while((word=*filedata)!=-1)
    {
        MTD_UINT expect_val = word;
        MTD_U16 addr = baseaddr+word_index*MTD_PTP_ADDR_ADJ;
        MTD_UINT val = mtd_ptp_read_reg(port, addr);
/*    MTD_U16 val = mtd_ptp_readcheck_reg(addr); */
        if(val != expect_val)
        {
            MTD_DBG_CRITIC_INFO("ERROR: memory addr 0x%x value 0x%x does not match file value 0x%x\n", addr, 
                val, expect_val);
            err++;
        }
        filedata++;
        word_index++;
    }

    if(err != 0)
    {
        MTD_DBG_CRITIC_INFO("ERROR: found %d mismatches\n", err);
        return MTD_FAIL;
    }
    return retVal;
}

/* Write DONE to udata spaces to just make PTP pass packet along */
/* (Enric modified this as follows) */
/* for parser (both ingress and egress): addr 0 & 1 => HALT */
/* for update: for ingress: addr 0 => HALT, addr 1 => OUT EOP, addr 2 => HALT */
/*             for egress : addr 0 => HALT, addr 1 => OUT HFT, addr 2 => OUT EOP, addr 3 => HALT  */
MTD_STATUS mtd_ptp_1step_setup_simple_udata (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
/*   Egress parser udata */
/*  retVal = mtd_ptp_writecheck_reg(port, 0x3100, 0x30000); */
/*  retVal = mtd_ptp_writecheck_reg(port, 0x3101, 0x30000); */
/*  retVal = mtd_ptp_writecheck_reg(port, 0x3102, 0x30000); */
/*   Egress update udata */
/*  retVal = mtd_ptp_writecheck_reg(port, 0x3200, 0x30000); */
/*  retVal = mtd_ptp_writecheck_reg(port, 0x3201, 0x30000); */
/*  retVal = mtd_ptp_writecheck_reg(port, 0x3202, 0x30000); */
/*   Ingress parser udata */
/*  retVal = mtd_ptp_writecheck_reg(port, 0x3500, 0x30000); */
/*  retVal = mtd_ptp_writecheck_reg(port, 0x3501, 0x30000); */
/*  retVal = mtd_ptp_writecheck_reg(port, 0x3502, 0x30000); */
/*   Ingress update udata */
/*  retVal = mtd_ptp_writecheck_reg(port, 0x3600, 0x30000); */
/*  retVal = mtd_ptp_writecheck_reg(port, 0x3601, 0x30000); */
/*  retVal = mtd_ptp_writecheck_reg(port, 0x3602, 0x30000); */

  /* Parser Egress */
    retVal = mtd_ptp_writecheck_reg(port, MTD_VN_EG_PTP+MTD_PTP_PMEU_UDATA+MTD_PTP_PORT_OFF(port), 0x30000);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, MTD_VN_EG_PTP+MTD_PTP_PMEU_UDATA+1*MTD_PTP_ADDR_ADJ+MTD_PTP_PORT_OFF(port), 0x30000);
    if(retVal!=MTD_OK) return retVal;
  /* Parser Ingress */
    retVal = mtd_ptp_writecheck_reg(port, MTD_VN_IG_PTP+MTD_PTP_PMEU_UDATA+MTD_PTP_PORT_OFF(port), 0x30000);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, MTD_VN_IG_PTP+MTD_PTP_PMEU_UDATA+1*MTD_PTP_ADDR_ADJ+MTD_PTP_PORT_OFF(port), 0x30000);
    if(retVal!=MTD_OK) return retVal;
  /* Update Egress */
    retVal = mtd_ptp_writecheck_reg(port, MTD_VN_EG_PTP+MTD_PTP_UMEU_UDATA+MTD_PTP_PORT_OFF(port), 0x30000);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, MTD_VN_EG_PTP+MTD_PTP_UMEU_UDATA+1*MTD_PTP_ADDR_ADJ+MTD_PTP_PORT_OFF(port), 0x42400);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, MTD_VN_EG_PTP+MTD_PTP_UMEU_UDATA+2*MTD_PTP_ADDR_ADJ+MTD_PTP_PORT_OFF(port), 0x40000);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, MTD_VN_EG_PTP+MTD_PTP_UMEU_UDATA+3*MTD_PTP_ADDR_ADJ+MTD_PTP_PORT_OFF(port), 0x30000);
    if(retVal!=MTD_OK) return retVal;
  /* Update Ingress */
    retVal = mtd_ptp_writecheck_reg(port, MTD_VN_IG_PTP+MTD_PTP_UMEU_UDATA+MTD_PTP_PORT_OFF(port), 0x30000);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, MTD_VN_IG_PTP+MTD_PTP_UMEU_UDATA+1*MTD_PTP_ADDR_ADJ+MTD_PTP_PORT_OFF(port), 0x40000);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_writecheck_reg(port, MTD_VN_IG_PTP+MTD_PTP_UMEU_UDATA+2*MTD_PTP_ADDR_ADJ+MTD_PTP_PORT_OFF(port), 0x30000);
    return retVal;
}


/* return LUT value adjusted for field position */
MTD_64 mtd_ptp_lut_match_fld_val(MTD_PTP_MATCH field, MTD_64 value )
{

    MTD_64  mask = ((1 << mtd_ptp_lut_match_fld_sz[field])-1);
    MTD_DBG_INFO("ptp_lut_match_fld_val\n");
    return((value&mask) << mtd_ptp_lut_match_fld_pos[field]);
}
/* return LUT value extracted from vector */
MTD_64  mtd_ptp_lut_match_fld_extract( MTD_PTP_MATCH field, MTD_64 vector)
{

    MTD_64  mask = ((1 << mtd_ptp_lut_match_fld_sz[field])-1);
    return((vector >> mtd_ptp_lut_match_fld_pos[field])&mask);
}

/* return RX LUT value adjusted for field position */
MTD_U16 mtd_ptp_lut_rx_action_fld_val( MTD_PTP_RX_ACTION field, MTD_U16 value )
{

    MTD_U16 mask = ((1 << mtd_ptp_lut_rx_action_fld_sz[field])-1);
    return((value&mask) << mtd_ptp_lut_rx_action_fld_pos[field]);
}

/* return RX LUT value extracted from vector  */
MTD_U64 mtd_ptp_lut_rx_action_fld_extract (MTD_PTP_RX_ACTION field, MTD_U64 vector )
{

    MTD_U64  mask = ((1 << mtd_ptp_lut_rx_action_fld_sz[field])-1);
    return((vector >> mtd_ptp_lut_rx_action_fld_pos[field])&mask);
}

/* return TX LUT value adjusted for field position */
MTD_U16 mtd_ptp_lut_tx_action_fld_val( MTD_PTP_TX_ACTION field, MTD_U16 value )
{

    MTD_U16 mask = ((1 << mtd_ptp_lut_tx_action_fld_sz[field])-1);
    return((value&mask) << mtd_ptp_lut_tx_action_fld_pos[field]);
}

/* return TX LUT value extracted from vector  */
MTD_U64 mtd_ptp_lut_tx_action_fld_extract (MTD_PTP_TX_ACTION field, MTD_U64 vector )
{

    MTD_U64  mask = ((1 << mtd_ptp_lut_tx_action_fld_sz[field])-1);
    return((vector >> mtd_ptp_lut_tx_action_fld_pos[field])&mask);
}

/* return flag value adjusted for flag position */
MTD_U64 mtd_lut_flag_fld_val(int flag, MTD_U64 value )
{

/*   return ((value&1) << [lsearch pam_out_flags flag] ]; */
    return((value&1) << flag);
}
/*MTD_STATUS mtd_read_lut_entry (MTD_64 *lut_match, MTD_64 *lut_valid, MTD_64 *lut_action, short lut_index, MTD_PTP_TYPE path ); */


/* Read lut entry */
MTD_STATUS mtd_read_lut_entry (MTD_U16 port, MTD_64 *lut_key, MTD_64 *lut_valid, long *lut_key_top, long *lut_valid_top, MTD_64 *lut_action, short lut_index, int path )
{
    MTD_STATUS   retVal = MTD_OK;
//  MTD_U16 match_base_addr =(path+MTD_PTP_LUT_KEYMASK+0x10*MTD_PTP_ADDR_ADJ*lut_index);
    MTD_U16 match_base_addr =(path+MTD_PTP_LUT_KEYMASK+0x10*lut_index);
    MTD_U16 action_base_addr;
    MTD_U32 data;
    MTD_U64 dataLong;

    MTD_DBG_INFO("mtd_read_lut_entry %d\n", lut_index);

    mtd_ptp_msec_sem_take(OS_WAIT_FOREVER);
    if(mtd_ptp_msec_set_link_down_reset(port,0)!= MTD_OK)
    {
        mtd_ptp_msec_sem_give();
        MTD_DBG_ERROR("mtd_ptp_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }

  /* Have to write multiple words at a time, so don't use retVal = mtd_ptp_writecheck_reg */
    data = _mtd_ptp_read_reg (port, match_base_addr+1*MTD_PTP_ADDR_ADJ);
    dataLong = data;
    dataLong <<=32;
    data = _mtd_ptp_read_reg (port, match_base_addr+0*MTD_PTP_ADDR_ADJ);
    dataLong|= data;
    *lut_key = dataLong;
    data = _mtd_ptp_read_reg (port, match_base_addr+2*MTD_PTP_ADDR_ADJ);
    *lut_key_top = data;

    data = _mtd_ptp_read_reg (port, match_base_addr+5*MTD_PTP_ADDR_ADJ);
    dataLong = data;
    dataLong <<=32;
    data = _mtd_ptp_read_reg (port, match_base_addr+4*MTD_PTP_ADDR_ADJ);
    dataLong|= data;
    *lut_valid = dataLong;
    data = _mtd_ptp_read_reg (port, match_base_addr+6*MTD_PTP_ADDR_ADJ);
    *lut_valid_top = data;

    if(mtd_ptp_msec_set_link_down_reset(port,1)!= MTD_OK)
    {
        mtd_ptp_msec_sem_give();
        MTD_DBG_ERROR("mtd_ptp_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtd_ptp_msec_sem_give();

    action_base_addr = (path+MTD_PTP_LUT_ACTION+lut_index*MTD_PTP_ADDR_ADJ);
/*   action_base_addr = (path+MTD_PTP_LUT_ACTION+2*lut_index); */
  /* Have to read multiple words at a time, so don't use mtd_ptp_readcheck_reg */
/*  data = mtd_ptp_read_reg (port, action_base_addr+1);
  dataLong = data;
  dataLong <<=32;
*/
    dataLong = 0LL;
    data = mtd_ptp_read_reg (port, action_base_addr+0);
    dataLong = data;
    *lut_action = dataLong;
    MTD_DBG_INFO(">>> Read %s lut entry %d : key %llx  vld %llx  act %llx\n", 
        (path== MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port))?"igr": "egr", lut_index,   *lut_key, *lut_valid, *lut_action);
    return retVal;
}


MTD_STATUS mtd_ptp_find_lut_action(MTD_U16 port, MTD_PTP_1STEP_LUT_ACT action, MTD_PTP_Blk _path, int *entryNum) 
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_64 lut_key;
    MTD_64 lut_vld;
    long lut_key_top;
    long lut_vld_top;
    MTD_64 lut_act; 
    MTD_64 lut_act_tmp; 
    int idx =0;
    int path = (_path == MTD_PTP_igr)?MTD_VN_IG_PTP:MTD_VN_EG_PTP;

    MTD_DBG_INFO("PTP enable_lut_action port %d path %d idx %d action %x\n", port, path, idx, action);


    lut_act_tmp = mtd_prgm_ptp_get_lut_act(action);
    for(idx=0; idx<15; idx++)
    {
        retVal = mtd_read_lut_entry (port, &lut_key, &lut_vld, &lut_key_top, &lut_vld_top, &lut_act, idx, path );
        if(retVal!=MTD_OK) return retVal;

        if(lut_act&lut_act_tmp)
        {
            *entryNum = idx;
            break;
        }
    }
    return retVal;
}


MTD_STATUS mtd_ptp_enable_lut_action(MTD_U16 port, int idx, MTD_PTP_1STEP_LUT_ACT action, MTD_PTP_Blk path, MTD_BOOL en )
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_64 lut_key;
    MTD_64 lut_vld;
    long lut_key_top;
    long lut_vld_top;
    MTD_64 lut_act; 
    MTD_64 lut_act_tmp; 
    int addr = (path == MTD_PTP_igr)?MTD_VN_IG_PTP:MTD_VN_EG_PTP;
    MTD_DBG_INFO("PTP enable_lut_action port %d path %d idx %d action %x\n", port, path, idx, action);

    retVal = mtd_read_lut_entry (port, &lut_key, &lut_vld, &lut_key_top, &lut_vld_top, &lut_act, idx, addr );
    if(retVal!=MTD_OK) return retVal;

    lut_act_tmp = mtd_prgm_ptp_get_lut_act(action);
//  if(lut_act&lut_act_tmp)   /* 2242P */
    {
        if(en == MTD_TRUE)
        {
            lut_act |= lut_act_tmp;
        }
        else
        {
            lut_act &= ~lut_act_tmp;
        }
    }
    retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_top, lut_vld_top, lut_act, idx, addr+MTD_PTP_PORT_OFF(port));

    return retVal;
}


#ifdef DEBUG_MTD
/* dump memory */
MTD_STATUS mtd_ptp_1step_dump_mem (MTD_U16 port, MTD_UINT addr, int range)
{
    int i;
    MTD_UINT full_addr;

    for(i=0; i < range; i++)
    {
        full_addr =addr+i*MTD_PTP_ADDR_ADJ;
        MTD_DBG_INFO("0x%x 0x%x\n", full_addr, mtd_ptp_readcheck_reg(port, full_addr));
    }
    return MTD_OK;
}
#endif


/* Clear memory */
MTD_STATUS mtd_ptp_1step_write_zeroes (MTD_U16 port, MTD_UINT addr, int range)
{
    MTD_STATUS   retVal = MTD_OK;
    int i;

    for(i=0; i < range; i++)
    {
        MTD_UINT full_addr =addr+i*MTD_PTP_ADDR_ADJ;
        retVal = mtd_ptp_writecheck_reg(port, full_addr, 0);
        if(retVal!=MTD_OK) return retVal;
    }
    return retVal;
}


/* memory test */
MTD_STATUS mtd_ptp_1step_write_fs_check (MTD_U16 port, MTD_UINT addr, int range, MTD_UINT mask)
{
    MTD_STATUS   retVal = MTD_OK;
    int err = 0;
    int i;

    MTD_U16 expect_val =((0xffffffff)&mask);
    for(i=0; i < range; i++)
    {
        MTD_UINT full_addr =addr+i*MTD_PTP_ADDR_ADJ;
        retVal = mtd_ptp_writecheck_reg(port, full_addr, expect_val);
        if(retVal!=MTD_OK) return retVal;
    }
/*  for {set i 0} {i < range} {incr i} { */
/*    set full_addr (addr+i] */
/*    set val mtd_ptp_read_reg(port, full_addr] */
/*    if(val != expect_val} { */
/*      MTD_DBG_INFO( ("ERROR: memory addr 0x%x value 0x%x does not match expected value 0x%x" full_addr val expect_val] */
/*      incr err */
/*    } */
/*  } */
    if(err != 0)
    {
        MTD_DBG_CRITIC_INFO("ERROR: found %d mismatches\n", err);
        return MTD_FAIL;
    }
    return retVal;
}


/* memory test */
MTD_STATUS mtd_ptp_1step_write_unique_check (MTD_U16 port, MTD_U16 addr, int range, MTD_UINT mask)
{
    MTD_STATUS   retVal = MTD_OK;
    int err = 0;
    int i;

    for(i=0; i < range; i++)
    {
        MTD_U16 full_addr =addr+i*MTD_PTP_ADDR_ADJ;
        MTD_UINT expect_val = (((full_addr<<16)|(full_addr))&mask);
        retVal = mtd_ptp_writecheck_reg(port, full_addr, expect_val);
        if(retVal!=MTD_OK) return retVal;
    }
/*  for {set i 0} {i < range} {incr i} { */
/*    set full_addr (addr+i] */
/*    set expect_val full_addr */
/*    set val mtd_ptp_read_reg(port, full_addr] */
/*    if(val != expect_val} { */
/*      MTD_DBG_INFO( ("ERROR: memory addr 0x%x value 0x%x does not match expected value 0x%x" full_addr val expect_val] */
/*      incr err */
/*    } */
/*  } */
    if(err != 0)
    {
        MTD_DBG_CRITIC_INFO("ERROR: found %d mismatches\n", err);
        return MTD_FAIL;
    }
    return retVal;
}


#ifdef DEBUG_MTD
/* udata mem dump */
MTD_STATUS mtd_ptp_1step_mem_dump_update_udata (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT eg_addr =(MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_UMEU_UDATA);

    retVal = mtd_ptp_1step_dump_mem(port,  eg_addr, 0x40);
    return retVal;
}
#endif


/* udata mem test */
MTD_STATUS mtd_ptp_1step_mem_test_update_udata (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16  eg_addr = (MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_UMEU_UDATA);
    MTD_U16  ig_addr = (MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_UMEU_UDATA);

    retVal = mtd_ptp_1step_write_zeroes(port, eg_addr, 0x100); 
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_1step_write_unique_check(port, eg_addr, 0x100, 0xfffff);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_1step_write_fs_check(port, eg_addr, 0x100, 0xfffff);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_1step_write_zeroes(port, ig_addr, 0x100); 
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_1step_write_unique_check(port, ig_addr, 0x100, 0xfffff);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_1step_write_fs_check(port, ig_addr, 0x100, 0xfffff);
    return retVal;
}


/* udata mem test */
MTD_STATUS mtd_ptp_1step_mem_test_parser_udata (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16  eg_addr = (MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_PMEU_UDATA);
    MTD_U16  ig_addr = (MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port)+MTD_PTP_PMEU_UDATA); 

    retVal = mtd_ptp_1step_write_zeroes(port, eg_addr, 0x100);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_1step_write_unique_check(port, eg_addr, 0x100, 0xfffff);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_1step_write_fs_check(port, eg_addr, 0x100, 0xfffff);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_1step_write_zeroes(port, ig_addr, 0x100);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_1step_write_unique_check(port, ig_addr, 0x100, 0xfffff);
    if(retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_1step_write_fs_check(port, ig_addr, 0x100, 0xfffff);
    return retVal;
}


MTD_PTP_TYPE mtd_get_ptp_base_addr_id (MTD_PTP_Blk path )
{
    MTD_PTP_TYPE base_addr_id;
    int path_igr = (path == MTD_PTP_igr)?1:0;
    int path_egr = (path == MTD_PTP_egr)?1:0;

/*  set path_igr (![string compare -nocase path "igr"]] */
/*  set path_egr (![string compare -nocase path "egr"]] */

    if(path_igr)
    {
        base_addr_id = MTD_IG_PTP;
    }
    else if(path_egr)
    {
        base_addr_id = MTD_EG_PTP;
    }
    else
    {
        MTD_DBG_CRITIC_INFO("ERROR: path path not recognized\n");
        return -1;
    }

    return base_addr_id;
}


/* prints out the ptp registers (portber 'port') */
MTD_STATUS mtd_get_ptp_regs ( MTD_U16 port, MTD_PTP_Blk path )
{
#if DEBUG_MTD
    MTD_U16 my_base_addr;

    int index = 0;
    MTD_PTP_TYPE base_addr_id;
    MTD_U16 reg_addr;

    MTD_DBG_INFO("PTP regs (port %d, path %d)\n", port, path);

    base_addr_id = mtd_get_ptp_base_addr_id(path);
    my_base_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_RF;

    index = 0;
/*  foreach reg mtd_ptp_rf_names_list { */
    while (mtd_ptp_rf_names_list[index]!=0)
    {
        reg_addr = my_base_addr + index*MTD_PTP_ADDR_ADJ;
        MTD_DBG_INFO( ("%04x %15s %08x\n", reg_addr, mtd_ptp_rf_names_list[index], mtd_ptp_read_reg(port, reg_addr));
            index++;
    }
#endif
    return MTD_OK;
}


MTD_STATUS mtd_ptp_1step_display_contents(MTD_U16 port, MTD_U16 addr, int size)
{
    MTD_STATUS   retVal = MTD_OK;
    int index;

    for (index=0; index < size; index++)
    {
        MTD_U16 reg_addr; 

        reg_addr = addr + index*MTD_PTP_ADDR_ADJ;
        MTD_DBG_CRITIC_INFO("%04x %02d %08x\n", reg_addr, index, mtd_ptp_read_reg(port, reg_addr));
    }
    return retVal;
}


/* prints out the ptp pam (parser and update) contents (portber 'port' and path 'egr|igr') */
MTD_STATUS mtd_get_ptp_pam ( MTD_U16 port, MTD_PTP_Blk path )
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 my_base_addr;

    MTD_PTP_TYPE base_addr_id = mtd_get_ptp_base_addr_id (path);

    MTD_DBG_INFO("PTP Parser PAM (port port, path path)\n");
    my_base_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_PMEU_PAM;
    mtd_ptp_1step_display_contents(port, my_base_addr, 32);

    MTD_DBG_INFO("PTP Update PAM (port %d, path path)\n", port);
    my_base_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_UMEU_PAM;
    mtd_ptp_1step_display_contents(port, my_base_addr, 32);
    return retVal;
}


/* prints out the ptp lut (key, mask and action) contents */
MTD_STATUS mtd_get_ptp_lut ( MTD_U16 port, MTD_PTP_Blk path )
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 my_base_addr;

    MTD_PTP_TYPE base_addr_id = mtd_get_ptp_base_addr_id (path);

    MTD_DBG_INFO("PTP LUT key (port port, path path)\n");
    my_base_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_LUT_KEYMASK;
    mtd_ptp_1step_display_contents( port, my_base_addr, 32);

    MTD_DBG_INFO("PTP LUT mask (port %d, path path)\n", port);
    my_base_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_LUT_KEYMASK + 32*MTD_PTP_ADDR_ADJ;
    mtd_ptp_1step_display_contents( port,my_base_addr, 32);

    MTD_DBG_INFO("PTP LUT action (port port, path path)\n");
    my_base_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_LUT_ACTION;
    mtd_ptp_1step_display_contents(port, my_base_addr, 32);
    return retVal;
}


MTD_U64 mtd_ptp_lut_key_adjust ( MTD_PTP_KEY name, MTD_U64 value )
{
    MTD_U64 dataLong = 0LL;

    dataLong = value&0xffffffffLL;
    return(dataLong << mtd_ptp_lut_key_pos[name] );
}


MTD_U64 mtd_ptp_vld_key_adjust ( MTD_PTP_KEY name )
{
    MTD_U64 dataLong = 0LL;

    dataLong = 1LL << mtd_ptp_lut_key_size[name];
    dataLong = dataLong - 1;
    dataLong = dataLong << mtd_ptp_lut_key_pos[name];
    return(dataLong);
}

MTD_U64 mtd_ptp_lut_act_adjust ( MTD_PTP_1STEP_LUT_ACT name, MTD_U64 value )
{
    MTD_U64 dataLong = 0LL;

    dataLong = value&0xffffffffLL;
    return(dataLong << mtd_ptp_lut_act_pos[name] );
}


/* demo LUT */
MTD_STATUS mtd_ptp_lut_init (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 reg_addr;
    MTD_PTP_TYPE base_addr_id;

    retVal = mtd_ptp_lut_clear(port);
    if (retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_lut_default(port);
    if (retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_lut_interrupt(port);
    if (retVal!=MTD_OK) return retVal;

#if 1 /* for Y1731 */
    base_addr_id = mtd_get_ptp_base_addr_id( MTD_PTP_egr);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_PMEU_PAM + 30*MTD_PTP_ADDR_ADJ;
    retVal = mtd_ptp_writecheck_reg(port, reg_addr, 0x8902); 
    if (retVal!=MTD_OK) return retVal;
    base_addr_id = mtd_get_ptp_base_addr_id( MTD_PTP_igr);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_PMEU_PAM + 30*MTD_PTP_ADDR_ADJ;
    retVal = mtd_ptp_writecheck_reg(port, reg_addr, 0x8902); 
#endif
    return retVal;
}


MTD_STATUS mtd_ptp_lut_init_ntp (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_PTP_TYPE base_addr_id;
    MTD_U16 reg_addr;

  /*
  mtd_ptp_lut_clear(port);
  mtd_ptp_lut_default(port);
  mtd_ptp_lut_interrupt(port);
  */

    base_addr_id = mtd_get_ptp_base_addr_id( MTD_PTP_egr);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_PMEU_PAM + 30*MTD_PTP_ADDR_ADJ;
    retVal = mtd_ptp_writecheck_reg(port, reg_addr, 0x007b); 
    if (retVal!=MTD_OK) return retVal;
    base_addr_id = mtd_get_ptp_base_addr_id( MTD_PTP_igr);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_PMEU_PAM + 30*MTD_PTP_ADDR_ADJ;
    retVal = mtd_ptp_writecheck_reg(port, reg_addr, 0x007b); 
    return retVal;
}


MTD_STATUS mtd_ptp_lut_init_ntp_2 (MTD_U16 port, int udp_src_port, int udp_dst_port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_PTP_TYPE base_addr_id;
    MTD_U16 reg_addr;

  /*
  mtd_ptp_lut_clear(port);
  mtd_ptp_lut_default(port);
  mtd_ptp_lut_interrupt(port);
  */

  /* overwrite entry 31 in parser MEU PAM with 0x007b (for ntp)  */
    base_addr_id = mtd_get_ptp_base_addr_id( MTD_PTP_egr);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_PMEU_PAM + 31*MTD_PTP_ADDR_ADJ;
    retVal = mtd_ptp_writecheck_reg(port, reg_addr, udp_src_port); 
    if (retVal!=MTD_OK) return retVal;
    base_addr_id = mtd_get_ptp_base_addr_id( MTD_PTP_igr);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_PMEU_PAM + 31*MTD_PTP_ADDR_ADJ;
    retVal = mtd_ptp_writecheck_reg(port, reg_addr, udp_dst_port); 
    return retVal;
}


/* init example */
MTD_STATUS _mtd_set_ptp_tai_tod (MTD_U16 port, MTD_UINT ns, MTD_UINT sec_lo, MTD_UINT sec_hi )
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 my_base_addr = mtd_ptp_1step_base_addr[MTD_TAI_CFG];
    MTD_U64 sec;

    retVal = mtd_ptp_write_reg (port, my_base_addr + MTD_REG_TOD_0*MTD_PTP_ADDR_ADJ, 0x0);
    if (retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_write_reg (port, my_base_addr + MTD_REG_TOD_1*MTD_PTP_ADDR_ADJ, ns);
    if (retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_write_reg (port, my_base_addr + MTD_REG_TOD_2*MTD_PTP_ADDR_ADJ, sec_lo);
    if (retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_write_reg (port, my_base_addr + MTD_REG_TOD_3*MTD_PTP_ADDR_ADJ, sec_hi);
    if (retVal!=MTD_OK) return retVal;

    sec =  sec_hi;
    sec =  (sec << 32);
    sec = sec + sec_lo + ns/1000000000;

    MTD_DBG_INFO("sec_hi:%08x sec_lo:%08x ns:%08x => seconds sec\n", sec_hi, sec_lo, ns);

    return retVal;
}


MTD_STATUS mtd_set_ptp_tai_frc (MTD_U16 port, MTD_UINT ns, MTD_UINT sec_lo, MTD_UINT sec_hi )
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 my_base_addr = mtd_ptp_1step_base_addr[MTD_TAI_CFG];
    MTD_U64 sec;

    retVal = mtd_ptp_write_reg (port, my_base_addr + MTD_REG_FRC_0*MTD_PTP_ADDR_ADJ, 0x0);
    if (retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_write_reg (port, my_base_addr + MTD_REG_FRC_1*MTD_PTP_ADDR_ADJ, ns);
    if (retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_write_reg (port, my_base_addr + MTD_REG_FRC_2*MTD_PTP_ADDR_ADJ, sec_lo);
    if (retVal!=MTD_OK) return retVal;
    retVal = mtd_ptp_write_reg (port, my_base_addr + MTD_REG_FRC_3*MTD_PTP_ADDR_ADJ, sec_hi);
    if (retVal!=MTD_OK) return retVal;

    sec =  sec_hi;
    sec =  (sec << 32);
    sec = sec + sec_lo + ns/1000000000;

    MTD_DBG_INFO("sec_hi:%08x sec_lo:%08x ns:%08x => seconds sec\n", sec_hi, sec_lo, ns);

    return retVal;
}


MTD_STATUS mtd_get_ptp_tai_step (MTD_U16 port, MTD_UINT *nanosec, MTD_UINT *fracnanosec)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 my_base_addr = mtd_ptp_1step_base_addr[MTD_TAI_CFG];
  /* nanosecond, default is 8 */
    MTD_U16 reg_addr = my_base_addr + MTD_REG_TOD_STEP_NS*MTD_PTP_ADDR_ADJ;

    *nanosec   = mtd_ptp_read_reg(port, reg_addr);
  /* fraction of nanoseconds, default is 0 */
    reg_addr = my_base_addr + MTD_REG_TOD_STEP_FS*MTD_PTP_ADDR_ADJ;
    *fracnanosec   = mtd_ptp_read_reg(port, reg_addr);
    return retVal;
}


MTD_STATUS mtd_set_ptp_tai_step (MTD_U16 port, MTD_UINT nanosec, MTD_UINT fracnanosec)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 my_base_addr = mtd_ptp_1step_base_addr[MTD_TAI_CFG];
  /* nanosecond, default is 8 */
    MTD_U16 reg_addr = my_base_addr + MTD_REG_TOD_STEP_NS*MTD_PTP_ADDR_ADJ;

    retVal = mtd_ptp_writecheck_reg(port, reg_addr, nanosec); 
  /* fraction of nanoseconds, default is 0 */
    reg_addr = my_base_addr + MTD_REG_TOD_STEP_FS*MTD_PTP_ADDR_ADJ;
    retVal = mtd_ptp_writecheck_reg(port, reg_addr, fracnanosec);
    return retVal;
}


int mtd_get_ptp_tsql_usage ( MTD_U16 port,  MTD_PTP_Blk path )
{
    MTD_U16 reg_addr;
    MTD_UINT result;

    MTD_PTP_TYPE base_addr_id;

    MTD_DBG_INFO( "PTP timestamp queue low usage (port %d, path %d)\n",port, path);

    base_addr_id = mtd_get_ptp_base_addr_id (path);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_RF + MTD_PTP_1STEP_TS_USAGE;

    result = mtd_ptp_read_reg (port, reg_addr) & 0xffff;
    result *=2;  /* Xu */

    MTD_DBG_INFO("tsql usage %04x %04x (%d)\n", reg_addr, result, result);

    return result;
}


int mtd_get_ptp_tsqh_usage ( MTD_U16 port,  MTD_PTP_Blk path )
{
    MTD_PTP_TYPE base_addr_id;
    MTD_U16 reg_addr;
    MTD_UINT result;

    MTD_DBG_INFO( "PTP timestamp queue high usage port %d path %d\n", port, path);
    base_addr_id = mtd_get_ptp_base_addr_id (path);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_RF + MTD_PTP_1STEP_TS_USAGE;

/*  set base_addr_id [get_ptp_base_addr_id $port $path] */
/*  set reg_addr [expr $base_addr($base_addr_id) + $ptp_addr(RF) + [lsearch $ptp_rf_names_list "ts_usage"]] */

    result = (mtd_ptp_read_reg(port, reg_addr)>>16) & 0xffff;
    result *=2;  /* Xu for 10G*/

    MTD_DBG_INFO("tsqh usage %04x %04x (%d)\n", reg_addr, result, result);

    return result;
}


static MTD_STATUS getPTPTsQueue(MtdPtpTsQueueStruct *tsQueue, MTD_U16 *buf)
{
    MTD_STATUS   retVal = MTD_OK;
    int i;


    tsQueue->seqId = *(buf + 5);
    tsQueue->domainNum  = (*(buf + 7)>>8)&0xff;
    tsQueue->transpSpec  = (*(buf + 6)>>12)&0xf;
    tsQueue->msgId  = (*(buf + 6)>>8)&0xf;
    
    tsQueue->ts.extTs.nanoseconds = *(buf + 1);
    tsQueue->ts.extTs.nanoseconds <<= 16;
    tsQueue->ts.extTs.nanoseconds |= *(buf + 0);
    
    tsQueue->ts.extTs.topseconds = *(buf + 3);
    tsQueue->ts.extTs.seconds = *(buf + 2);
    
    tsQueue->ts.extTs.seconds <<= 16;
    tsQueue->ts.extTs.seconds |= *(buf + 4);
    for (i=0; i<8;i++)
    {
        MTD_DBG_INFO(" buf %d: %04x\n", i, *(buf+i));
    }
    MTD_DBG_INFO("ts.extTs.topseconds %x\n", tsQueue->ts.extTs.topseconds);
    MTD_DBG_INFO("ts.extTs.seconds %x\n", tsQueue->ts.extTs.seconds);
    MTD_DBG_INFO("ts.extTs.nanoseconds %x\n", tsQueue->ts.extTs.nanoseconds);
    return retVal;
}


MTD_STATUS mtd_displayPTPTsQueue(MtdPtpTsQueueStruct *tsQueue)
{
    MTD_STATUS   retVal = MTD_OK;

    MTD_DBG_INFO("Get PTP TS Queue:\n");
    MTD_DBG_INFO("sequence Id  %d\n", tsQueue->seqId);
    MTD_DBG_INFO("domain Number  %d\n", tsQueue->domainNum);
    MTD_DBG_INFO("transport Specific  %d\n", tsQueue->transpSpec);
    MTD_DBG_INFO("message Id  %x\n", tsQueue->msgId);
    MTD_DBG_INFO("ts.extTs.nanoseconds %x\n", tsQueue->ts.extTs.nanoseconds);
    MTD_DBG_INFO("ts.extTs.topseconds %x\n", tsQueue->ts.extTs.topseconds);
    MTD_DBG_INFO("ts.extTs.seconds %x\n", tsQueue->ts.extTs.seconds);
    return retVal;
}


MTD_STATUS mtd_ptp_get_tsql_part ( MTD_U16 port,  MTD_PTP_Blk path, int count, MtdPtpTsQueueStruct *tsQueue)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_PTP_TYPE base_addr_id;
    MTD_U16 reg_addr;
    int j;
    MTD_U32 data;
    MTD_U16 tsQuBuf[8];
/*   MtdPtpTsQueueStruct ptpTsQueue; */

    MTD_DBG_INFO("PTP get queue low data port %d, path %d\n", port, path);

    base_addr_id = mtd_get_ptp_base_addr_id (path);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_RF + MTD_PTP_1STEP_TSQL_DATA;

    for (j=0; j<(count/2); j++)
    {
        data = mtd_ptp_read_reg(port, reg_addr);
        tsQuBuf[2*j]=(MTD_U16)data;
        tsQuBuf[2*j+1]=(MTD_U16)((data>>16));
        MTD_DBG_INFO("%04x = %08x (%04x, %04x)\n", reg_addr,  data, tsQuBuf[2*j],  tsQuBuf[2*j+1]);
    }
    getPTPTsQueue(tsQueue, tsQuBuf);        
/* test */
    mtd_displayPTPTsQueue(tsQueue);         
    return retVal;
}


MTD_STATUS mtd_ptp_get_tsqh_part ( MTD_U16 port,  MTD_PTP_Blk path, int count, MtdPtpTsQueueStruct *tsQueue)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_PTP_TYPE base_addr_id;
    MTD_U16 reg_addr;
    int j;
    MTD_U32 data;
    MTD_U16 tsQuBuf[8];
/*   MtdPtpTsQueueStruct ptpTsQueue; */

    MTD_DBG_INFO("PTP get queue high data port %d, path %d\n", port, path);

    base_addr_id = mtd_get_ptp_base_addr_id (path);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_RF + MTD_PTP_1STEP_TSQH_DATA;

    for (j=0; j<(count/2); j++)
    {
        data = mtd_ptp_read_reg(port, reg_addr);
        tsQuBuf[2*j]=(MTD_U16)(data);
        tsQuBuf[2*j+1]=(MTD_U16)((data>>16));
        MTD_DBG_INFO("%04x = %08x (%04x, %04x)\n", reg_addr,  data, tsQuBuf[2*j],  tsQuBuf[2*j+1]);
    }
    getPTPTsQueue(tsQueue, tsQuBuf);        
/* test */
/*    mtd_displayPTPTsQueue(tsQueue);         */
    return retVal;
}


MTD_STATUS mtd_ptp_get_tsql ( MTD_U16 port,  MTD_PTP_Blk path, MtdPtpTsQueueStruct *tsQueue)
{
    return mtd_ptp_get_tsql_part(port, path, MTD_PTP_TS_QUEUE_SIZE, tsQueue);
}


MTD_STATUS mtd_ptp_get_tsqh ( MTD_U16 port,  MTD_PTP_Blk path, MtdPtpTsQueueStruct *tsQueue)
{
    return mtd_ptp_get_tsqh_part(port, path, MTD_PTP_TS_QUEUE_SIZE, tsQueue);
}


MTD_STATUS mtd_get_ptp_tsql_data ( MTD_U16 port,  MTD_PTP_Blk path, int numhwords)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_PTP_TYPE base_addr_id;
    MTD_U16 reg_addr;
    int i, j;
    MtdPtpTsQueueStruct ptpTsQueue;
    MTD_U32 data;
    MTD_U16 tsQuBuf[16];

    MTD_DBG_CRITIC_INFO( "PTP timestamp queue low data port %d , path %s , hwords %d\n", port, 
        (path==MTD_PTP_igr)?"igr":"egr", numhwords);

/*  set base_addr_id [get_ptp_base_addr_id $port $path] */
/*  set reg_addr [expr $base_addr($base_addr_id) + $ptp_addr(RF) + [lsearch $ptp_rf_names_list "ts_tsql_data"]] */
    base_addr_id = mtd_get_ptp_base_addr_id (path);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_RF + MTD_PTP_1STEP_TSQL_DATA;

    for (i=0; i < numhwords; i+= MTD_PTP_TS_QUEUE_SIZE)
    {
        for (j=0; j<(MTD_PTP_TS_QUEUE_SIZE/2); j++)
        {
            data = mtd_ptp_read_reg(port, reg_addr);
            tsQuBuf[2*j]=(MTD_U16)(data);
            tsQuBuf[2*j+1]=(MTD_U16)((data>>16));
            MTD_DBG_INFO("%04x %02d %08x (%04x, %04x)\n", reg_addr, i,  data, tsQuBuf[2*j],  tsQuBuf[2*j+1]);
        }
        getPTPTsQueue(&ptpTsQueue, tsQuBuf);        
        mtd_displayPTPTsQueue(&ptpTsQueue);        
    }
    return retVal;
}


MTD_STATUS mtd_get_ptp_tsqh_data ( MTD_U16 port,  MTD_PTP_Blk path, int numhwords)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_PTP_TYPE base_addr_id;
    MTD_U16 reg_addr;
    int i, j;
    MTD_U32 data;
    MtdPtpTsQueueStruct ptpTsQueue;
    MTD_U16 tsQuBuf[16];

    MTD_DBG_CRITIC_INFO( "PTP timestamp queue high data port %d , path %s , hwords %d\n", port, 
        (path==MTD_PTP_igr)?"igr":"egr", numhwords);

/*  set base_addr_id [get_ptp_base_addr_id $port $path] */
/*  set reg_addr [expr $base_addr($base_addr_id) + $ptp_addr(RF) + [lsearch $ptp_rf_names_list "ts_tsqh_data"]] */
    base_addr_id = mtd_get_ptp_base_addr_id (path);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_RF + MTD_PTP_1STEP_TSQH_DATA;

    for (i=0; i < numhwords; i+= MTD_PTP_TS_QUEUE_SIZE)
    {
        for (j=0; j<(MTD_PTP_TS_QUEUE_SIZE/2); j++)
        {
            data = mtd_ptp_read_reg(port, reg_addr);
            tsQuBuf[2*j]=(MTD_U16)(data);
            tsQuBuf[2*j+1]=(MTD_U16)((data>>16));
            MTD_DBG_INFO("%04x %02d %08x (%04x, %04x)\n", reg_addr, i,  data, tsQuBuf[2*j],  tsQuBuf[2*j+1]);
        }
        getPTPTsQueue(&ptpTsQueue, tsQuBuf);        
        mtd_displayPTPTsQueue(&ptpTsQueue);        
    }
    return retVal;
}


MTD_STATUS mtd_get_ptp_stuff (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;

    mtd_get_ptp_stats( port, MTD_PTP_igr);
    mtd_get_ptp_stats (port, MTD_PTP_egr);
    mtd_get_ptp_tsql_drain (port, MTD_PTP_igr);
    mtd_get_ptp_tsqh_drain (port, MTD_PTP_igr);
    mtd_get_ptp_tsql_drain (port, MTD_PTP_egr);
    mtd_get_ptp_tsqh_drain (port, MTD_PTP_egr);
    return retVal;
}


MTD_STATUS mtd_ptp_lut_update (MTD_U16 port, 
    MTD_U64 delete_lut_key , 
    MTD_U64 delete_lut_vld,
    MTD_U64 delete_lut_act,
    MTD_U64 add_lut_key , 
    MTD_U64 add_lut_vld,
    MTD_U64 add_lut_act,
    short lut_index, int path )
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_64 tmp_lut_key;
    MTD_64 tmp_lut_vld;
    long tmp_lut_key_top;
    long tmp_lut_vld_top;
    MTD_64 tmp_lut_act; 

    mtd_read_lut_entry( port, &tmp_lut_key, &tmp_lut_vld, &tmp_lut_key_top, &tmp_lut_vld_top, &tmp_lut_act, lut_index, path);
    MTD_DBG_INFO(">>> read lut entry : key %x:%llx  vld %x:%llx  act %llx\n", 
        tmp_lut_key_top, tmp_lut_key, tmp_lut_vld_top, tmp_lut_vld, tmp_lut_act);
    MTD_DBG_INFO(">>> delete lut entry : key %llx  vld %llx  act %llx\n", 
        delete_lut_key, delete_lut_vld, delete_lut_act);
    MTD_DBG_INFO(">>> add lut entry : key %llx  vld %llx  act %llx\n", 
        add_lut_key, add_lut_vld, add_lut_act);
    tmp_lut_key &= ~delete_lut_key;
    tmp_lut_vld &= ~delete_lut_vld;
    tmp_lut_act &= ~delete_lut_act;
    tmp_lut_key |= add_lut_key;
    tmp_lut_vld |= add_lut_vld;
    tmp_lut_act |= add_lut_act;
    MTD_DBG_INFO(">>> updated lut entry : key %x:%llx  vld %x:%llx  act %llx\n", 
        tmp_lut_key_top, tmp_lut_key, tmp_lut_vld_top, tmp_lut_vld, tmp_lut_act);
    mtd_ptp_prgm_lut_entry( port, tmp_lut_key, tmp_lut_vld, tmp_lut_key_top, tmp_lut_vld_top, tmp_lut_act, lut_index, path);
    return retVal;
}


/* Set PTP register */
MTD_STATUS mtd_set_ptp_tai_reg (MTD_U16 port, MTD_PTP_1STEP_TAI_REGS regname, MTD_UINT value )
{
    MTD_STATUS   retVal = MTD_OK;
/*  set reg_addr [lsearch $ptp_tai_regs_list $regname] */
    MTD_UINT reg_addr = regname;
    MTD_UINT my_base_addr;

    if (reg_addr < 0)
    {
        MTD_DBG_INFO( "Error: register %d not found", (int)regname);
    }
    else
    {
        my_base_addr = mtd_ptp_1step_base_addr[MTD_TAI_CFG]+ reg_addr;
        retVal = mtd_ptp_write_reg(port,  my_base_addr, value);
    }
    return retVal;
}


/* Set PTP register */
MTD_STATUS mtd_get_ptp_tai_reg (MTD_U16 port, MTD_PTP_1STEP_TAI_REGS regname, MTD_UINT *value)
{
    MTD_STATUS   retVal = MTD_OK;
/*  set reg_addr [lsearch $ptp_tai_regs_list $regname] */
    MTD_UINT reg_addr = regname;
    MTD_UINT my_base_addr;

    if (reg_addr < 0)
    {
        MTD_DBG_INFO( "Error: register %d not found", (int)regname);
    }
    else
    {
        my_base_addr = mtd_ptp_1step_base_addr[MTD_TAI_CFG]+ reg_addr;
        MTD_DBG_INFO( " address is %x\n", my_base_addr);
        *value = mtd_ptp_read_reg(port,  my_base_addr);
    }
    return retVal;
}


/* set drift adjustment (frac nsec) */
MTD_STATUS mtd_set_drift_adj (MTD_U16 port, MTD_UINT frac_ns)
{
    MTD_STATUS   retVal = MTD_OK;

    mtd_set_ptp_tai_reg(port,  MTD_REG_DRIFT_ADJ_CFG*MTD_PTP_ADDR_ADJ, frac_ns); 
    return retVal;
}


/* get drift adjustment (frac nsec) */
MTD_STATUS mtd_get_drift_adj (MTD_U16 port, MTD_UINT *frac_ns)
{
    MTD_STATUS   retVal = MTD_OK;

    mtd_get_ptp_tai_reg(port,  MTD_REG_DRIFT_ADJ_CFG*MTD_PTP_ADDR_ADJ, frac_ns);
    return retVal;
}

/* TAI / TOD */

/* Get PTP time register  */
/* Valid regname is one of: tod_0, frc_0, trig_gen_tod_0, trig_gen_msk_0, tod_load_0, tod_cap_0, tod_cap1_0, next_rt_0 */
MTD_STATUS mtd_get_ptp_tai_timereg (MTD_U16 port, MTD_PTP_1STEP_TAI_REGS regname,MTD_UINT *sec_hi,MTD_UINT *sec_lo,MTD_UINT *ns, MTD_UINT *fs)
{
    MTD_STATUS   retVal = MTD_OK;
/*  set my_base_addr [expr $base_addr(MTD_TAI_CFG)+ [lsearch $ptp_tai_regs_list $regname] ] */
    MTD_UINT my_base_addr = mtd_ptp_1step_base_addr[MTD_TAI_CFG]+regname*MTD_PTP_ADDR_ADJ;
    MTD_U64  sec;

/*  set frac   [read_reg [expr $my_base_addr + 0]] */
/*  set ns     [read_reg [expr $my_base_addr + 1]] */
/*  set sec_lo [read_reg [expr $my_base_addr + 2]] */
/*  set sec_hi [read_reg [expr $my_base_addr + 3]] */
    *fs  =mtd_ptp_read_reg(port, my_base_addr + 0); 
    *ns    =mtd_ptp_read_reg(port, my_base_addr + 1*MTD_PTP_ADDR_ADJ);
    *sec_lo  =mtd_ptp_read_reg(port, my_base_addr + 2*MTD_PTP_ADDR_ADJ);
    *sec_hi  =mtd_ptp_read_reg(port, my_base_addr + 3*MTD_PTP_ADDR_ADJ);

/*  set sec [expr  [expr $sec_hi << 32] + $sec_lo + $ns/10e9] */
    sec =  *sec_hi;
    sec =  (sec << 32);
    sec = sec + *sec_lo + *ns/1000000000;

/*  MTD_DBG_INFO("$regname: sec_hi:%08x sec_lo:%08x ns:%08x => seconds $sec" $sec_hi $sec_lo $ns] */
    MTD_DBG_INFO("Reg: %x: sec_hi:%08x sec_lo:%08x ns:%08x fs:%08x => \n", regname*MTD_PTP_ADDR_ADJ, *sec_hi, *sec_lo, *ns, *fs);
    MTD_DBG_INFO(" => seconds sec %lld\n", sec);
    return retVal;
}


/* Set PTP time register  */
/* Valid regname is one of: tod_0, frc_0, trig_gen_tod_0, trig_gen_msk_0, tod_load_0, tod_cap_0, tod_cap1_0, next_rt_0 */
MTD_STATUS mtd_set_ptp_tai_timereg (MTD_U16 port, MTD_PTP_1STEP_TAI_REGS regname,MTD_UINT sec_hi, MTD_UINT sec_lo,MTD_UINT ns, MTD_UINT fs)
{
    MTD_STATUS   retVal = MTD_OK;
/*  set my_base_addr [expr $base_addr(MTD_TAI_CFG)+ [lsearch $ptp_tai_regs_list $regname] ] */
    MTD_UINT my_base_addr = mtd_ptp_1step_base_addr[MTD_TAI_CFG]+regname*MTD_PTP_ADDR_ADJ;
    MTD_U64  sec;

/*  retVal = mtd_ptp_write_reg(port,  [expr $my_base_addr + 0] 0  */
/*  retVal = mtd_ptp_write_reg(port,  [expr $my_base_addr + 1] $ns */
/*  retVal = mtd_ptp_write_reg(port,  [expr $my_base_addr + 2] $sec_lo */
/*  retVal = mtd_ptp_write_reg(port,  [expr $my_base_addr + 3] $sec_hi */
    mtd_ptp_msec_sem_take(OS_WAIT_FOREVER);
    if (mtd_ptp_msec_set_link_down_reset(port,0)!= MTD_OK)
    {
        mtd_ptp_msec_sem_give();
        MTD_DBG_ERROR("mtd_ptp_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    retVal = _mtd_ptp_write_reg (port, my_base_addr+0, fs);
    if (retVal!=MTD_OK)
    {
        mtd_ptp_msec_sem_give();
        return retVal;
    }
    retVal = _mtd_ptp_write_reg (port, my_base_addr+1*MTD_PTP_ADDR_ADJ, ns);
    if (retVal!=MTD_OK)
    {
        mtd_ptp_msec_sem_give();
        return retVal;
    }
    retVal = _mtd_ptp_write_reg (port, my_base_addr+2*MTD_PTP_ADDR_ADJ, sec_lo);
    if (retVal!=MTD_OK)
    {
        mtd_ptp_msec_sem_give();
        return retVal;
    }
    retVal = _mtd_ptp_write_reg (port, my_base_addr+3*MTD_PTP_ADDR_ADJ, sec_hi);
    if (mtd_ptp_msec_set_link_down_reset(port,1)!= MTD_OK)
    {
        mtd_ptp_msec_sem_give();
        MTD_DBG_ERROR("mtd_ptp_msec_set_link_down_reset failed.\n");
        return MTD_FAIL;
    }
    mtd_ptp_msec_sem_give();
    if (retVal!=MTD_OK) return retVal;

/*  set sec [expr  [expr $sec_hi << 32] + $sec_lo + $ns/10e9] */
    sec =  sec_hi;
    sec =  (sec << 32);
    sec = sec + sec_lo + ns/1000000000;

    MTD_DBG_INFO("sec_hi:%08x sec_lo:%08x ns:%08x fs:%08x => seconds", sec_hi, sec_lo, ns, fs);
    return retVal;
}


/* return value with modified field  */
MTD_UINT mtd_tai_tod_cfg_gen_set_field (MTD_UINT oldvalue, int field, MTD_UINT value)
{
/*  MTD_DBG_INFO( "mtd_tai_tod_cfg_gen_val" */

/*   mask = ((1 << mtd_tai_tod_cfg_gen_sz[field])-1) << mtd_tai_tod_cfg_gen_pos[field]] ; */
    MTD_UINT mask = ((1 << mtd_tai_tod_cfg_gen_sz[field])-1) << mtd_tai_tod_cfg_gen_pos[field];
    MTD_UINT adjvalue = value << mtd_tai_tod_cfg_gen_pos[field];
    return((oldvalue&~mask)|(adjvalue&mask));
}


/* return value extracted from vector */
MTD_UINT mtd_tai_tod_cfg_gen_extract(int field, int vector)
{

    MTD_UINT mask = ((1 << mtd_tai_tod_cfg_gen_sz[field])-1);
    return((vector >> mtd_tai_tod_cfg_gen_pos[field])&mask);
}


/* return value with modified field  */
MTD_UINT mtd_tai_tod_func_cfg_set_field(MTD_UINT oldvalue, int field, MTD_UINT value)
{
    MTD_UINT mask = ((1 << mtd_tai_tod_func_cfg_sz[field])-1) << mtd_tai_tod_func_cfg_pos[field];
    MTD_UINT adjvalue = value << mtd_tai_tod_func_cfg_pos[field];
    MTD_DBG_INFO("mtd_tai_tod_func_cfg_val");

    return((oldvalue&~mask)|(adjvalue&mask));
}


/* return value extracted from vector */
MTD_UINT mtd_tai_tod_func_cfg_extract(int field, int vector)
{

    MTD_UINT mask = (1 << mtd_tai_tod_func_cfg_sz[field])-1;
    return((vector >> mtd_tai_tod_func_cfg_pos[field])&mask);
}

/* Show TAI TOD cfg gen */


/* ------------------------------------------------------------------------------------ zzz */
MTD_STATUS mtd_set_tai_pulse_in_cnt (MTD_U16 port, MTD_UINT val)
{
    MTD_STATUS   retVal = MTD_OK;
/*  set addr [expr $base_addr(MTD_TAI_CFG)+ [lsearch $ptp_tai_regs_list pulse_in_cnt] ] */
/*   MTD_UINT addr = mtd_ptp_1step_base_addr[MTD_TAI_CFG]+ pulse_in_cnt; */
    MTD_UINT addr = MTD_PULSE_IN_CNT;

/*   writecheck_reg addr val */
    retVal = mtd_ptp_writecheck_reg(port, addr, val);
    return retVal;
}


MTD_STATUS mtd_get_tai_pulse_in_cnt (MTD_U16 port)
{
#ifdef DEBUG_MTD
    MTD_UINT addr = MTD_PULSE_IN_CNT;
    MTD_UINT cnt;
    cnt = mtd_ptp_read_reg (port, addr);
    MTD_DBG_INFO("%08h (%d)", cnt, cnt);
#endif
    return MTD_OK;
}


MTD_STATUS mtd_ptp_lut_default (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U64 lut_key;
    MTD_U64 lut_vld;
    MTD_U32 lut_key_top=0;
    MTD_U32 lut_vld_top=0;
    MTD_U64 lut_act; 

  /* Ingress */
  /* Default => do nothing */

    lut_key = mtd_ptp_lut_key_adjust( MTD_K_AlwaysZero, 0);
    lut_vld = mtd_ptp_vld_key_adjust(MTD_K_AlwaysZero);
    lut_act = 0x0;
    retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_top, lut_vld_top, lut_act, 15, MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port));
    if (retVal!=MTD_OK) return retVal;

  /* Egress */
  /* Default => do nothing */
    lut_key = mtd_ptp_lut_key_adjust( MTD_K_AlwaysZero, 0);
    lut_vld = mtd_ptp_vld_key_adjust(MTD_K_AlwaysZero);
    lut_act = 0x0;
    retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_top, lut_vld_top, lut_act, 15, MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port));
    return retVal;
}


/* entry 14 */
/* if parser is interrupted => do nothing */
MTD_STATUS mtd_ptp_lut_interrupt (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U64 lut_key;
    MTD_U64 lut_vld;
    MTD_U32 lut_key_top=0;
    MTD_U32 lut_vld_top=0;
    MTD_U64 lut_act; 

  /* Ingress */
    lut_key = mtd_ptp_lut_key_adjust( MTD_K_AlwaysZero, 1);
    lut_vld = mtd_ptp_vld_key_adjust(MTD_K_AlwaysZero);
    lut_act = 0x0;
    retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_top, lut_vld_top, lut_act, 14, MTD_VN_IG_PTP+MTD_PTP_PORT_OFF(port));
    if (retVal!=MTD_OK) return retVal;

  /* Egress */
  /* Default => do nothing */
    lut_key = mtd_ptp_lut_key_adjust( MTD_K_AlwaysZero, 1);
    lut_vld = mtd_ptp_vld_key_adjust(MTD_K_AlwaysZero);
    lut_act = 0x0;
    retVal = mtd_ptp_prgm_lut_entry( port, lut_key, lut_vld, lut_key_top, lut_vld_top, lut_act, 14, MTD_VN_EG_PTP+MTD_PTP_PORT_OFF(port));
    return retVal;
}


MTD_STATUS mtd_set_tai_ntp_mode (MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    retVal = mtd_set_ntp_tod_mode(port, 1);

    mtd_set_ptp_tai_step (port, 0x6, 0xDF37F675);  
    return retVal;
}


/* set tod_cap_cfg bits cap_ */
MTD_STATUS mtd_set_tod_cap_cfg (MTD_U16 port, MTD_UINT val)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_UINT addr = MTD_TOD_CAP_CFG;
    MTD_U32  regval = mtd_ptp_read_reg (port, addr);

    regval = mtd_msec_bits_write(&regval, val & 3, 3, 2);
    retVal = mtd_ptp_writecheck_reg(port, addr, regval);
    if (retVal!=MTD_OK) return retVal;
    return retVal;
}


MTD_STATUS mtd_set_elu_entry_match_da (MTD_U16 port, int en, int da)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 base0 = port * 0x800 + 0x100 + 8*en*MTD_PTP_ADDR_ADJ;
    MTD_UINT te = (1 << 17) | (1 << 18) | (1 << 28);
    MTD_U16 base = base0 + 4;

    retVal = mtd_ptp_write_reg (port, base,te);
    if (retVal!=MTD_OK) return retVal;

    te = (da & 0xFFFF) << 16;
    base = base0 + 1*MTD_PTP_ADDR_ADJ;
    retVal = mtd_ptp_write_reg (port, base,te);
    if (retVal!=MTD_OK) return retVal;

    te = (da >> 16) & 0xFFFFFFFF;
    base = base0 + 2*MTD_PTP_ADDR_ADJ;
    retVal = mtd_ptp_write_reg (port, base,te);
    if (retVal!=MTD_OK) return retVal;

    return retVal;
}


/* Action abreviation
# single action is defined */
MTD_U64  mtd_prgm_ptp_get_lut_act (MTD_PTP_1STEP_LUT_ACT action)
{
    MTD_U64 lut_act = 0L; 

    if (action == MTD_PTP_Act_No_Action)
    {
        lut_act = 0L;
    }
    else
    {
        lut_act = lut_act | mtd_ptp_lut_act_adjust(action, 1);


    }
    return lut_act;
}


/* Action abreviation
# multiple actions are defined in a list 
*/
MTD_U64  mtd_prgm_ptp_get_lut_actions (MTD_PTP_1STEP_LUT_ACTIONS actions)
{
    MTD_U64 lut_act = 0L; 
    MTD_PTP_1STEP_LUT_ACT act;

    act = 0;
    while (actions)
    {
        if (actions &1)
        {
            lut_act = (lut_act | mtd_ptp_lut_act_adjust(act, 1));
        }
        act++;
        actions >>= 1;
    }
    return lut_act;
}


/* 
The time ctl shall be disabled when PTP is running in 10/100mbps 
so that the watchdog timer does not interrupt the ptp actions. 
Also mtd_set_asymmtry, mtd_set_link_delay are used to adjust the delay on the link.
*/ 

/* watchdog timeout in clocks
 15:8 PPD watchdog timeout
 7:0 PPE watchdog timeout */
MTD_STATUS mtd_set_ptp_timeout_ctrl(MTD_UINT cycles, MTD_U16 port)
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_PTP_TYPE base_addr_id;
    MTD_U16 reg_addr;
    MTD_U32 regval;

    base_addr_id = mtd_get_ptp_base_addr_id (MTD_PTP_egr);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_RF + MTD_PTP_1STEP_TIMEOUT_CTL;
    regval = mtd_ptp_read_reg (port, reg_addr);
    mtd_msec_bits_write(&regval, cycles, 15, 0);  
    mtd_msec_bits_write(&regval, cycles, 31, 16);
    retVal = mtd_ptp_write_reg(port, reg_addr, regval);
    if (retVal!=MTD_OK) return retVal;

    base_addr_id = mtd_get_ptp_base_addr_id(MTD_PTP_igr);
    reg_addr = mtd_ptp_1step_base_addr[base_addr_id] + MTD_PTP_RF + MTD_PTP_1STEP_TIMEOUT_CTL;
    regval = mtd_ptp_read_reg (port, reg_addr);
    mtd_msec_bits_write(&regval, cycles, 15, 0);  
    mtd_msec_bits_write(&regval, cycles, 31, 16);
    retVal = mtd_ptp_write_reg(port, reg_addr, regval);
    if (retVal!=MTD_OK) return retVal;

    return retVal;
}


MTD_STATUS mtd_set_ptp_igr_mode (MTD_U16 port, MTD_UINT mode )
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_UINT regval;

    addr = 0xA938;
    regval = mtd_ptp_read_reg (port, addr);

    mtd_msec_bit_write(regval, mode, 10);
    retVal = mtd_ptp_write_reg(port, addr, regval);
    return retVal;
}


MTD_UINT mtd_get_ptp_igr_mode (MTD_U16 port)
{
    MTD_U16 reg_addr;
    MTD_U32 data;

    reg_addr = 0xa938;
    data = mtd_ptp_read_reg (port, reg_addr);
    return(mtd_msec_bit_get (data, 10));
}

/* new ntp mode bit, replace old ntp mode bit */

MTD_STATUS mtd_set_ntp_mode (MTD_U16 port, MTD_UINT flag )
{
    MTD_STATUS   retVal = MTD_OK;
    MTD_U16 addr;
    MTD_UINT regval;

    addr = 0xA138;
    regval = mtd_ptp_read_reg (port, addr);

    mtd_msec_bit_write(regval, flag, 9);
    retVal = mtd_ptp_write_reg(port, addr, regval);
    if (retVal!=MTD_OK) return retVal;
  //return retVal;
    addr = 0xA938;
    regval = mtd_ptp_read_reg (port, addr);

    mtd_msec_bit_write(regval, flag, 9);
    retVal = mtd_ptp_write_reg(port, addr, regval);
    if (retVal!=MTD_OK) return retVal;
    return retVal;
}


MTD_UINT mtd_get_ntp_mode (MTD_U16 port, MTD_PTP_Blk path)
{
    MTD_U16 reg_addr;
    MTD_U32 data;

    if (path == MTD_PTP_egr)
    {
        reg_addr = 0xa138;
    }
    else
    {
        reg_addr = 0xa938;
    }
    data = mtd_ptp_read_reg (port, reg_addr);
    return(mtd_msec_bit_get (data, 9));
}


MTD_STATUS mtd_set_ptp_pam_egr_latadj (MTD_U16 port, MtdPtpPamLatAdj *lat)
{
    MTD_STATUS retVal;

  /*Write `PPDD+27 lat_adj[15:0] */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+27*MTD_PTP_ADDR_ADJ), lat->lat_adj1);
    if (retVal!=MTD_OK) return retVal;
  /*Write `PPDD+28 lat_adj[31:16] */
    retVal = mtd_ptp_writecheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+28*MTD_PTP_ADDR_ADJ), lat->lat_adj0);
    if (retVal!=MTD_OK) return retVal;
    return retVal;
}


MTD_STATUS mtd_get_ptp_pam_egr_latadj (MTD_U16 port, MtdPtpPamLatAdj *lat)
{
  /*Read `PPDD+27 lat_adj[15:0] */
    lat->lat_adj1 = mtd_ptp_readcheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+27*MTD_PTP_ADDR_ADJ));
  /*Read `PPDD+28 lat_adj[31:16] */
    lat->lat_adj0 = mtd_ptp_readcheck_reg(port, (MTD_VN_EG_PTP+MTD_PTP_UMEU_PAM+MTD_PTP_PORT_OFF(port)+28*MTD_PTP_ADDR_ADJ));
    return MTD_OK;
}


#if 1

/*
# 10/12/2012
# Move latency adjust from PAM27,28 to TAI register 0xBC72 and 0xBC74
# 2/28/2013
# these two registers are used for TAI to calculate latency adjustment
# based on stt_ctl and core_clk_period
# latadj = stt_ctl * core_period
# instead we use stt_ctl in ptp and latency setting in sigba
*/
MTD_UINT  mtd_get_ptp_egr_latadj(MTD_U16 port)
{
    MTD_U16 reg_addr;
    MTD_U32 data;

    reg_addr = 0xBC72;
//  MTD_DBG_CRITIC_INFO("PTP EGR Latency Adjustment (port %d)", port);

    data = mtd_ptp_read_reg (port, reg_addr);

    return data;
}


MTD_STATUS mtd_set_ptp_egr_latadj (MTD_U16 port, MTD_UINT ns )
{
    MTD_STATUS retVal;
    MTD_U16 reg_addr;

    reg_addr = 0xBC72;
//  MTD_DBG_CRITIC_INFO("Set PTP EGR Latency Adjustment (port %d ns %x)", port, ns);

//  write_reg2 $reg_addr [expr round($ns)] $portnum
    retVal = mtd_ptp_write_reg(port, reg_addr, ns);
    return retVal;
}


MTD_UINT  mtd_get_ptp_igr_latadj(MTD_U16 port)
{
    MTD_U16 reg_addr;
    MTD_U32 data;

    reg_addr = 0xBC74;
//  MTD_DBG_CRITIC_INFO("PTP IGR Latency Adjustment (port %d)", port);

    data = mtd_ptp_read_reg (port, reg_addr);

    return data;
}


MTD_STATUS mtd_set_ptp_igr_latadj(MTD_U16 port, MTD_UINT ns )
{
    MTD_STATUS retVal;
    MTD_U16 reg_addr;

    reg_addr = 0xBC74;
//  MTD_DBG_CRITIC_INFO("Set PTP IGR Latency Adjustment (port %d ns %x)", port, ns);

//  write_reg2 $reg_addr [expr round($ns)] $portnum
    retVal = mtd_ptp_write_reg(port, reg_addr, ns);
    return retVal;
}


MTD_STATUS mtd_set_ptp_egr_stt_ctl(MTD_U16 port, MTD_UINT value)
{
    MTD_STATUS retVal;
    MTD_U16 reg_addr;
    MTD_U32 data;

    reg_addr = 0xA10A;
    data = mtd_ptp_read_reg (port, reg_addr);
//  write_reg2 $reg_addr [bits_write [read_reg2 $reg_addr $portnum] $value 19 0] $portnum
    mtd_msec_bits_write(&data, value, 19, 0);
    retVal = mtd_ptp_write_reg(port, reg_addr, data);
    return retVal;
}

MTD_UINT  mtd_get_ptp_egr_stt_ctl(MTD_U16 port)
{
    MTD_U16 reg_addr;
    MTD_U32 data;

    reg_addr = 0xA10A;
    data = mtd_ptp_read_reg (port, reg_addr);

    return data;
}


MTD_STATUS mtd_set_ptp_igr_stt_ctl(MTD_U16 port, MTD_UINT value)
{
    MTD_STATUS retVal;
    MTD_U16 reg_addr;
    MTD_U32 data;

    reg_addr = 0xA90A;
    data = mtd_ptp_read_reg (port, reg_addr);
//  write_reg2 $reg_addr [bits_write [read_reg2 $reg_addr $portnum] $value 19 0] $portnum
    mtd_msec_bits_write(&data, value, 19, 0);
    retVal = mtd_ptp_write_reg(port, reg_addr, data);
    return retVal;
}


MTD_UINT  mtd_get_ptp_igr_stt_ctl(MTD_U16 port)
{
    MTD_U16 reg_addr;
    MTD_U32 data;

    reg_addr = 0xA90A;
    data = mtd_ptp_read_reg (port, reg_addr);

    return data;
}

MTD_STATUS mtd_set_egr_fr_latency(MTD_U16 port, MTD_UINT fr_lat)
{
    MTD_STATUS retVal;
    MTD_U16 reg_addr;
    MTD_U32 data;

    reg_addr = 0xC2C;
    data = mtd_ptp_read_reg (port, reg_addr);
//  write_reg2 $reg_addr [bits_write [read_reg2 $reg_addr $portnum] $fr_lat 15 0] $portnum
    mtd_msec_bits_write(&data, fr_lat, 15, 0);
    retVal = mtd_ptp_write_reg(port, reg_addr, data);
    return retVal;
}


MTD_UINT  mtd_get_egr_fr_latency(MTD_U16 port)
{
    MTD_U16 reg_addr;
    MTD_U32 data;

    reg_addr = 0xC2C;
    data = mtd_ptp_read_reg (port, reg_addr);
    return(mtd_msec_bits_get(data, 15,0));
}


MTD_UINT  mtd_get_egr_latency(MTD_U16 port)
{
    MTD_U16 reg_addr;
    MTD_U32 data;

    reg_addr = 0xC2C;
    data = mtd_ptp_read_reg (port, reg_addr);

    return data;
}


MTD_STATUS mtd_set_igr_fr_latency(MTD_U16 port, MTD_UINT fr_lat)
{
    MTD_STATUS retVal;
    MTD_U16 reg_addr;
    MTD_U32 data;

    reg_addr = 0x1C56;
    data = mtd_ptp_read_reg (port, reg_addr);
//  write_reg2 $reg_addr [bits_write [read_reg2 $reg_addr $portnum] $fr_lat 15 0] $portnum
    mtd_msec_bits_write(&data, fr_lat, 15, 0);
    retVal = mtd_ptp_write_reg(port, reg_addr, data);
    return retVal;
}

/*
# sigba core runs on core_clk
# when core_clk is 625MHz, core_period is 1.6ns
*/
MTD_UINT mtd_get_core_period (void)
{
    return MTD_PTP_CYCLE/10;
}


MTD_UINT  mtd_get_igr_fr_latency(MTD_U16 port)
{
    MTD_U16 reg_addr;
    MTD_U32 data;

    reg_addr = 0x1C56;
    data = mtd_ptp_read_reg (port, reg_addr);
    return(mtd_msec_bits_get(data, 15,0));
}


MTD_UINT  mtd_get_igr_latency(MTD_U16 port)
{
    MTD_U16 reg_addr;
    MTD_U32 data;

    reg_addr = 0x1C56;
    data = mtd_ptp_read_reg (port, reg_addr);

    return data;
}

/*
# set top_interrupt mask in 0x8006
# b8~11, port0~3
# b12, global interrupt for MACsec and PTP
# b15, TAI interrupt
*/
MTD_STATUS mtd_set_top_intr_msk(MTD_U16 port, MTD_UINT msk)
{
    MTD_STATUS retVal;
    MTD_U16 reg_addr;
    MTD_U32 data;

    reg_addr = MTD_SLC_INT_SET_MSK;
    data = mtd_ptp_read_reg (port, reg_addr);
//  set data [bits_write $data [expr $msk & 0x3FF] 17 0]
    mtd_msec_bits_write(&data, msk & 0x3FF, 17, 0);
//  write_reg2 $reg_addr $data $port
    retVal = mtd_ptp_write_reg(port, reg_addr, data);
    return retVal;
}


MTD_UINT  mtd_get_top_intr_msk(MTD_U16 port)
{
    MTD_U16 reg_addr;
    MTD_U32 data;

    reg_addr = MTD_SLC_INT_SET_MSK;
    data = mtd_ptp_read_reg (port, reg_addr);

    return(mtd_msec_bits_get(data, 17,0));
}

/*
# get interrupt source in 0x8004
*/
MTD_UINT  mtd_get_intr_src(MTD_U16 port)
{
    MTD_U16 reg_addr;
    MTD_U32 data;

    reg_addr = 0x8004;
    data = mtd_ptp_read_reg (port, reg_addr);
    MTD_DBG_CRITIC_INFO("PTP igr intr %X", mtd_msec_bit_get(data, 17));
    MTD_DBG_CRITIC_INFO("PTP egr intr %X", mtd_msec_bit_get(data, 16));
    MTD_DBG_CRITIC_INFO("link change event indication %X", mtd_msec_bit_get(data, 15));
    MTD_DBG_CRITIC_INFO("intr test %X", mtd_msec_bit_get(data, 12));
    MTD_DBG_CRITIC_INFO("double-bit rd err %X", mtd_msec_bit_get(data, 11));
    MTD_DBG_CRITIC_INFO("single-bit rd err %X", mtd_msec_bit_get(data, 10));
    MTD_DBG_CRITIC_INFO("rx_lpi_enabled %X", mtd_msec_bit_get(data, 9));
    MTD_DBG_CRITIC_INFO("tx_lpi_enabled %X", mtd_msec_bit_get(data, 8));
    MTD_DBG_CRITIC_INFO("MAC stats full %X", mtd_msec_bits_get(data, 7,4));
    MTD_DBG_CRITIC_INFO("MAC stats 3/4 full %X", mtd_msec_bits_get(data, 3,0));
    return data;
}

#endif


/*******************************************************************************
* mtd_get_ptp_tai
*
* DESCRIPTION:
*       This routine prints PTP TAI for debug.
*
* INPUTS:
*       None.
*   
* OUTPUTS:
*       None.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_ptp_tai (void)
{
#if DEBUG_MTD
    MTD_U16  my_base_addr = mtd_ptp_1step_base_addr[MTD_TAI_CFG];
    int index = 0;
    MTD_U16 port =0;
    MTD_U16 reg_addr;
    MTD_DBG_INFO("PTP TAI regs\n");

/*  foreach reg mtd_ptp_tai_regs_list { */
    while (mtd_ptp_tai_regs_list_name[index]!=0)
    {
        reg_addr = my_base_addr + index*MTD_PTP_ADDR_ADJ;
        MTD_DBG_INFO( ("%04x %15s %08x\n\n", reg_addr, mtd_ptp_tai_regs_list_name[index], mtd_ptp_read_reg(port, reg_addr));
            index++;
        }
#endif
            return MTD_OK;
}



            
