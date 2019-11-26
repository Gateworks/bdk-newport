/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains sample function prototypes, macros and definitions 
for the Marvell 88X32X0, 88X33X0, 88E20X0 and 88E21X0 ethernet PHYs.
********************************************************************/
#ifndef MTD_SAMPLE_H
#define MTD_SAMPLE_H

#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

#if 0 /* obsolete, change 0-> if used these previously and want to continue using them */
/* NOTE: These macros were given out in a pre-release before the loopback functions had been provided. */
/* They match the terminology in an older version of the datasheet. Please use the C functions: */
/* mtdSetTunitDeepMacLoopback() */
/* mtdSetTunitShallowLineLoopback() */
/* mtdSetHXunitLineLoopback() */
/* mtdSetHXunitMacLoopback() */
/* instead if possible. */

/* 
   Loopback macros for various units: 
   devPtr - allocated memory for the device structure
   port - MDIO port address, 0-31
   flag - MTD_TRUE to enable loopback; MTD_FALSE set to normal/disable 
*/
#define MTD_TUNIT_MAC_LOOPBACK(devPtr,port,flag)                 mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_IEEE_PCS_CTRL1,14,1,flag)
#define MTD_TUNIT_LINE_10M_100M_1000M_LOOPBACK(devPtr,port,flag) mtdHwSetPhyRegField(devPtr,port,MTD_T_UNIT_PCS_CU,0x8002,5,1,flag)
#define MTD_TUNIT_LINE_2P5G_5G_10G_LOOPBACK(devPtr,port,flag)    mtdHwSetPhyRegField(devPtr,port,1,0xC000,11,1,flag)

#define MTD_XUNIT_MAC_LOOPBACK(devPtr,port,flag)   mtdHwSetPhyRegField(devPtr,port,MTD_X_UNIT,0x1000,14,1,flag)
#define MTD_XUNIT_LINE_LOOPBACK(devPtr,port,flag)  mtdHwSetPhyRegField(devPtr,port,MTD_X_UNIT,0xF003,12,1,flag)

#define MTD_HUNIT_MAC_LOOPBACK(devPtr,port,flag)  mtdHwSetPhyRegField(devPtr,port,MTD_H_UNIT,0x0000,14,1,flag)
#define MTD_HUNIT_LINE_LOOPBACK(devPtr,port,flag) mtdHwSetPhyRegField(devPtr,port,MTD_H_UNIT,0xF003,12,1,flag)
#endif

/* 
   Force link good macros for various units: 
   devPtr - allocated memory for the device structure
   port - MDIO port address, 0-31
   flag - MTD_TRUE to Force Link good; MTD_FALSE set to normal operation  
*/
#define MTD_TUNIT_FORCE_LINK_GOOD(devPtr,port,flag)  mtdHwSetPhyRegField(devPtr,port,MTD_T_UNIT_PCS_CU,0x8002,1,1,flag)
#define MTD_HUNIT_FORCE_LINK_GOOD(devPtr,port,flag)  mtdHwSetPhyRegField(devPtr,port,MTD_H_UNIT,MTD_SERDES_CONTROL1,10,1,flag)
#define MTD_XUNIT_FORCE_LINK_GOOD(devPtr,port,flag)  mtdHwSetPhyRegField(devPtr,port,MTD_X_UNIT,MTD_SERDES_CONTROL1,10,1,flag)


#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* MTD_SAMPLE_H */
