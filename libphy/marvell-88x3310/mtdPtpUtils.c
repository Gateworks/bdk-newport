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
#include "mtdMsecTypes.h"
#include "mtdPtp1step.h"

/*
static unsigned short macValList[256];
static unsigned short sysmacValList[256];
*/

MTD_VOID mtd_ptp_1step_print_reg (MTD_U16 port, MTD_U16 addr)
{
    MTD_DBG_CRITIC_INFO("%x ", mtd_ptp_read_reg(port, addr));
}  

MTD_VOID mtd_ptp_1step_print_mac_statistics (MTD_U16 port, MTD_UINT *macValList)
{
    int n;
    MTD_DBG_CRITIC_INFO("\nprint all MAC statistics counters on dev dev_num.\n");
    n = port; /*for (n=0; n<1; n++) */
    {
        int macName = 0;
        while(mtd_ptp_1step_macNmList[macName]!=0)
        {
/*    for (name = RxGoodOctLo; name < EndMacName; name++) { */
            MTD_DBG_CRITIC_INFO ("port%1d %20s %10d\n", n, mtd_ptp_1step_macNmList[macName], macValList[macName]);
            macName++;
        }
    }
/*  for {set n 4} {n<1} {incr n} { */
    n = port; /*for (n=0; n<1; n++)   */
    {
/*    for (macName = RxGoodOctLo; macName < EndMacName; macName++) { */
        int macName = 0;
        while(mtd_ptp_1step_macNmList[macName]!=0)
        {
/*      val = macValList[macName]; */
            MTD_DBG_CRITIC_INFO("port%1d %20s %10d\n", n, mtd_ptp_1step_macNmList[macName], macValList[macName]);
            macName++;
        }
    }
}

MTD_VOID mtd_ptp_1step_print_sysmac_statistics (MTD_U16 port, MTD_UINT *sysmacValList)
{
    MTD_MacName macName=0;

/*    for (macName = RxGoodOctLo; macName < EndMacName; macName++) { */
    while(mtd_ptp_1step_macNmList[macName]!=0)
    {
/*      val = sysmacValList[macName]; */
        MTD_DBG_CRITIC_INFO("port%1d %20s %10d\n", port, mtd_ptp_1step_macNmList[macName], sysmacValList[macName]);
        macName++;
    }
}

#ifdef DEBUG_MTD
MTD_VOID mtd_get_mac_stats (MTD_U16 port, MTD_UINT *macValList)
{
    mtd_ptp_1step_dump_mac_statistics(port, macValList);
    mtd_ptp_1step_print_mac_statistics(port, macValList);
}

MTD_VOID mtd_get_sysmac_stats (MTD_U16 port, MTD_UINT *sysmacValList)
{
    mtd_ptp_1step_dump_sysmac_statistics(port, sysmacValList);
    mtd_ptp_1step_print_sysmac_statistics(port, sysmacValList);
}
#endif

MTD_VOID mtd_ptp_1step_print_rumi_stats (MTD_U16 port)
{
    MTD_DBG_CRITIC_INFO("IGR_MISS:    %10d\n", mtd_ptp_read_reg(port, 0x294D));
    MTD_DBG_CRITIC_INFO("IGR_OCT_TOT: %10d\n", mtd_ptp_read_reg(port, 0x2949));
    MTD_DBG_CRITIC_INFO("EGR_MISS:    %10d\n", mtd_ptp_read_reg(port, 0x294E));
    MTD_DBG_CRITIC_INFO("EGR_OCT_TOT: %10d\n", mtd_ptp_read_reg(port, 0x294C));
}

/* Show TAI TOD cfg gen */
MTD_VOID mtd_ptp_1step_print_tai_tod_func_cfg (MTD_U16 port)
{
/*  set addr [expr $base_addr(TAI_CFG)+ [lsearch $ptp_tai_regs_list tod_func_cfg] ] */
/*   MTD_UINT addr = mtd_ptp_1step_base_addr[TAI_CFG]+ tod_func_cfg; */
    MTD_UINT addr = MTD_TOD_FUNC_CFG;
    MTD_UINT regval = mtd_ptp_read_reg (port, addr);

/*   foreach field [array names tai_tod_func_cfg_pos] { */
/*     set field_val [tai_tod_func_cfg_extract field regval); */
    int field = 0;
    MTD_DBG_CRITIC_INFO("\n");
    while(mtd_tai_tod_func_cfg_pos[field]!=-1)
    {
    /* set field_val [tai_tod_cfg_gen_extract field regval] */
        MTD_UINT field_val;

        field_val = mtd_tai_tod_func_cfg_extract( field, regval);
        MTD_DBG_CRITIC_INFO("TAI TOD FUNC CFG field %s = 0x%x\n", mtd_tai_tod_func_cfg_name[field], field_val);
        field++;
    }
}

