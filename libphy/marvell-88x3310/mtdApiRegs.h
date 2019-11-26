/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions global register definitions for the
registers in the Marvell 88X32X0, 88X33X0, 88E20X0 and 88E21X0 
ethernet PHYs.
********************************************************************/
#ifndef APIREGS_H
#define APIREGS_H
#if C_LINKAGE
#if defined __cplusplus 
    extern "C" { 
#endif 
#endif

/* 88X3240/3220 Device Number Definitions */
#define MTD_T_UNIT_PMA_PMD  1
#define MTD_T_UNIT_PCS_CU   3
#define MTD_X_UNIT          3
#define MTD_H_UNIT          4
#define MTD_T_UNIT_AN       7
#define MTD_XFI_DSP         30
#define MTD_C_UNIT_GENERAL  31
#define MTD_M_UNIT          31

/* 88X3240/3220 Device Number Definitions Host Redundant Mode */
#define MTD_BASER_LANE_0  MTD_H_UNIT
#define MTD_BASER_LANE_1  MTD_X_UNIT

/* 88X3240/3220 T Unit Registers MMD 1 */
#define MTD_TUNIT_IEEE_PMA_CTRL1       MTD_T_UNIT_PMA_PMD,0x0000
#define MTD_TUNIT_IEEE_PMA_DEVID2      MTD_T_UNIT_PMA_PMD,0x0003
#define MTD_TUNIT_PHY_EXT_CTRL_1       MTD_T_UNIT_PMA_PMD,0xC000
#define MTD_TUNIT_XG_EXT_STATUS        MTD_T_UNIT_PMA_PMD,0xC001
#define MTD_TUNIT_BIST_STATUS_REG      MTD_T_UNIT_PMA_PMD,0xC00C
#define MTD_TUNIT_PHY_REV_INFO_REG     MTD_T_UNIT_PMA_PMD,0xC04E
#define MTD_BOOT_STATUS_REG            MTD_T_UNIT_PMA_PMD,0xC050

#define MTD_TUNIT_IEEE_PCS_CTRL1       MTD_T_UNIT_PCS_CU,0x0000

/* T unit 10G, 5G, 2.5G Packet generator registers */
#define MTD_TUNIT_10G_PKTGEN_CTRL      MTD_T_UNIT_PCS_CU,0xDC90
#define MTD_TUNIT_10G_PKTGEN_CTRL1     MTD_T_UNIT_PCS_CU,0xDC91
#define MTD_TUNIT_10G_PKTGEN_INIT0     MTD_T_UNIT_PCS_CU,0xDC92
#define MTD_TUNIT_10G_PKTGEN_INIT1     MTD_T_UNIT_PCS_CU,0xDC93
#define MTD_TUNIT_10G_PKTGEN_LENGTH    MTD_T_UNIT_PCS_CU,0xDC94
#define MTD_TUNIT_10G_PKTGEN_BURST     MTD_T_UNIT_PCS_CU,0xDC95
#define MTD_TUNIT_10G_PKTGEN_IPG       MTD_T_UNIT_PCS_CU,0xDC96
#define MTD_TUNIT_10G_PKTGEN_TXPKTCTR1 MTD_T_UNIT_PCS_CU,0xDC97
#define MTD_TUNIT_10G_PKTGEN_TXPKTCTR2 MTD_T_UNIT_PCS_CU,0xDC98
#define MTD_TUNIT_10G_PKTGEN_TXPKTCTR3 MTD_T_UNIT_PCS_CU,0xDC99
#define MTD_TUNIT_10G_PKTGEN_TXBYTCTR1 MTD_T_UNIT_PCS_CU,0xDC9A
#define MTD_TUNIT_10G_PKTGEN_TXBYTCTR2 MTD_T_UNIT_PCS_CU,0xDC9B
#define MTD_TUNIT_10G_PKTGEN_TXBYTCTR3 MTD_T_UNIT_PCS_CU,0xDC9C
#define MTD_TUNIT_10G_PKTCHK_CNTL      MTD_T_UNIT_PCS_CU,0xDCA0
#define MTD_TUNIT_10G_PKTGEN_RXPKTCTR1 MTD_T_UNIT_PCS_CU,0xDCA1
#define MTD_TUNIT_10G_PKTGEN_RXPKTCTR2 MTD_T_UNIT_PCS_CU,0xDCA2
#define MTD_TUNIT_10G_PKTGEN_RXPKTCTR3 MTD_T_UNIT_PCS_CU,0xDCA3
#define MTD_TUNIT_10G_PKTGEN_RXBYTCTR1 MTD_T_UNIT_PCS_CU,0xDCA4
#define MTD_TUNIT_10G_PKTGEN_RXBYTCTR2 MTD_T_UNIT_PCS_CU,0xDCA5
#define MTD_TUNIT_10G_PKTGEN_RXBYTCTR3 MTD_T_UNIT_PCS_CU,0xDCA6
#define MTD_TUNIT_10G_PKTGEN_ERRCTR1   MTD_T_UNIT_PCS_CU,0xDCA7
#define MTD_TUNIT_10G_PKTGEN_ERRCTR2   MTD_T_UNIT_PCS_CU,0xDCA8
#define MTD_TUNIT_10G_PKTGEN_ERRCTR3   MTD_T_UNIT_PCS_CU,0xDCA9  

#define MTD_TUNIT_TEST_CTRL            MTD_T_UNIT_PMA_PMD,0xC00B
#define MTD_TUNIT_LINK_DROP_CTRL       MTD_T_UNIT_PMA_PMD,0xC055
#define MTD_TUNIT_LINK_DROP_CTR        MTD_T_UNIT_PMA_PMD,0xC056

/* T unit Advanced PCS registers */
#define MTD_TUNIT_COPPER_SPEC_CTRL3    MTD_T_UNIT_PCS_CU,0x8002

/* T unit Interrupt registers */
#define MTD_TUNIT_INTERRUPT_CTRL1      MTD_T_UNIT_PCS_CU,0x8010
#define MTD_TUNIT_INTERRUPT_CTRL2      MTD_T_UNIT_PCS_CU,0x8012
#define MTD_TUNIT_INTERRUPT_STATUS1    MTD_T_UNIT_PCS_CU,0x8011
#define MTD_TUNIT_INTERRUPT_STATUS2    MTD_T_UNIT_PCS_CU,0x8013 

/* T unit Non-10G Packet generator registers */
#define MTD_TUNIT_PKTGEN_CTRL          MTD_T_UNIT_PCS_CU,0x8030
#define MTD_TUNIT_PKTGEN_INIT0         MTD_T_UNIT_PCS_CU,0x8031
#define MTD_TUNIT_PKTGEN_INIT1         MTD_T_UNIT_PCS_CU,0x8032
#define MTD_TUNIT_PKTGEN_LENGTH        MTD_T_UNIT_PCS_CU,0x8033
#define MTD_TUNIT_PKTGEN_BURST         MTD_T_UNIT_PCS_CU,0x8034
#define MTD_TUNIT_PKTGEN_IPG           MTD_T_UNIT_PCS_CU,0x8035
#define MTD_TUNIT_PKTGEN_TXPKTCTR1     MTD_T_UNIT_PCS_CU,0x8036
#define MTD_TUNIT_PKTGEN_TXPKTCTR2     MTD_T_UNIT_PCS_CU,0x8037
#define MTD_TUNIT_PKTGEN_TXBYTCTR1     MTD_T_UNIT_PCS_CU,0x8038
#define MTD_TUNIT_PKTGEN_TXBYTCTR2     MTD_T_UNIT_PCS_CU,0x8039
#define MTD_TUNIT_PKTGEN_RXPKTCTR1     MTD_T_UNIT_PCS_CU,0x803A
#define MTD_TUNIT_PKTGEN_RXPKTCTR2     MTD_T_UNIT_PCS_CU,0x803B
#define MTD_TUNIT_PKTGEN_RXBYTCTR1     MTD_T_UNIT_PCS_CU,0x803C
#define MTD_TUNIT_PKTGEN_RXBYTCTR2     MTD_T_UNIT_PCS_CU,0x803D
#define MTD_TUNIT_PKTGEN_ERRCTR1       MTD_T_UNIT_PCS_CU,0x803E
#define MTD_TUNIT_PKTGEN_ERRCTR2       MTD_T_UNIT_PCS_CU,0x803F

#define MTD_TUNIT_TEMP_SENSOR1         MTD_T_UNIT_PCS_CU,0x8041
#define MTD_TUNIT_TEMP_SENSOR2         MTD_T_UNIT_PCS_CU,0x8042 /* low 8 bits is average reading */
#define MTD_TUNIT_TEMP_SENSOR3         MTD_T_UNIT_PCS_CU,0x8043 /* low 8 bits is instantaneous reading */


/* 88X3240/3220 C Unit Registers MMD 31 */
#define MTD_CUNIT_MODE_CONFIG           MTD_C_UNIT_GENERAL,0xF000
#define MTD_CUNIT_PORT_CTRL             MTD_C_UNIT_GENERAL,0xF001 /* E21X0 devices use some bits on 0xF001 */
#define MTD_CUNIT_E21X0_PORT_CTRL       MTD_T_UNIT_PMA_PMD,0xC04A /* and 0xC04A for port control */
#define MTD_CUNIT_INTERRUPT_STATUS      MTD_C_UNIT_GENERAL,0xF040
#define MTD_CUNIT_INTERRUPT_CTRL1       MTD_C_UNIT_GENERAL,0xF041
#define MTD_GLOBE_INTERRUPT_STATUS      MTD_C_UNIT_GENERAL,0xF042
#define MTD_CUNIT_INTERRUPT_CTRL        MTD_C_UNIT_GENERAL,0xF043
#define MTD_CUNIT_TEMP_SENSOR_CTRL1     MTD_C_UNIT_GENERAL,0xF089
#define MTD_CUNIT_TEMP_SENSOR_CTRL_STAT MTD_C_UNIT_GENERAL,0xF08A
#define MTD_CUNIT_TEMP_SENSOR_INST      MTD_C_UNIT_GENERAL,0xF08C

/* H unit 10GB-X2/X4 Interrupt registers */
#define MTD_X2_X4_INTERRUPT_CTRL1      MTD_H_UNIT,0x8001
#define MTD_X2_X4_INTERRUPT_CTRL2      MTD_H_UNIT,0x8002
#define MTD_X2_X4_INTERRUPT_STATUS1    MTD_H_UNIT,0x8003
#define MTD_X2_X4_INTERRUPT_STATUS2    MTD_H_UNIT,0x8004 
#define MTD_X2_X4_REALTIME_STATUS      MTD_H_UNIT,0x8006

/* 88X3240/3220 H Unit and X Unit 1000BASE-X and SGMII Registers 
   Shared registers:
 */
#define MTD_1000X_SGMII_CONTROL               0x2000
#define MTD_1000X_SGMII_STATUS                0x2001
#define MTD_1000X_SGMII_PHYID1                0x2002
#define MTD_1000X_SGMII_PHYID2                0x2003
#define MTD_1000X_SGMII_AN_ADV                0x2004
#define MTD_1000X_SGMII_LP_ABL                0x2005

/* X unit only registers */
#define MTD_1000X_AN_EXPANSION                MTD_X_UNIT,0x2006
#define MTD_1000X_NP_TX                       MTD_X_UNIT,0x2007
#define MTD_1000X_LP_NP                       MTD_X_UNIT,0x2008
#define MTD_1000X_EXT_STATUS                  MTD_X_UNIT,0x200F
#define MTD_1000X_TIMR_MODE_SEL               MTD_X_UNIT,0xA000
#define MTD_1000X_INTR_ENABLE                 MTD_X_UNIT,0xA001
#define MTD_1000X_INTR_STATUS                 MTD_X_UNIT,0xA002
#define MTD_1000X_PHY_SPEC_STATUS             MTD_X_UNIT,0xA003

/* 88X3240/3220 H Unit and X Unit 10GBASE-R Shared Registers */
#define MTD_10GBR_PCS_CONTROL                 0x1000
#define MTD_10GBR_PCS_STATUS1                 0x1001
#define MTD_10GBR_PCS_FAULT                   0x1008 /* called STATUS2 in datasheet */
#define MTD_10GBR_PCS_RXSTATUS                0x1020 /* called STATUS1 in datasheet */
#define MTD_10GBR_PCS_STATUS2                 0x1021

/* H & X unit 10GB-R Interrupt registers */
#define MTD_10GBR_INTERRUPT_CTRL              0x9000
#define MTD_10GBR_INTERRUPT_STATUS            0x9001
#define MTD_10GBR_REALTIME_STATUS             0x9002

/* H & X unit 1GB-X Interrupt registers */
#define MTD_1GBX_INTERRUPT_CTRL               0xA001
#define MTD_1GBX_INTERRUPT_STATUS             0xA002
#define MTD_1GBX_REALTIME_STATUS              0xA003

/* 88X3240/3220 H Unit and X Unit Common Registers */
#define MTD_SERDES_CONTROL1                   0xF003
#define MTD_SERDES_CONTROL2                   0xF004
#define MTD_FIFO_CRC_INTR_ENABLE              0xF00A
#define MTD_FIFO_CRC_INTR_STATUS              0xF00B
#define MTD_FIFO_CONTROL1                     0xF00C
#define MTD_PKT_GEN_CONTROL1                  0xF010
#define MTD_PKT_GEN_CONTROL2                  0xF011
#define MTD_PKT_GEN_PAYLOAD1                  0xF012
#define MTD_PKT_GEN_PAYLOAD2                  0xF013
#define MTD_PKT_GEN_LENGTH                    0xF016
#define MTD_PKT_GEN_BURSTSEQ                  0xF017
#define MTD_PKT_GEN_IPG                       0xF018
#define MTD_PKT_GEN_TXPKTCTR1                 0xF01B
#define MTD_PKT_GEN_TXPKTCTR2                 0xF01C
#define MTD_PKT_GEN_TXPKTCTR3                 0xF01D
#define MTD_PKT_GEN_TXBYTCTR1                 0xF01E
#define MTD_PKT_GEN_TXBYTCTR2                 0xF01F
#define MTD_PKT_GEN_TXBYTCTR3                 0xF020
#define MTD_PKT_GEN_RXPKTCTR1                 0xF021
#define MTD_PKT_GEN_RXPKTCTR2                 0xF022
#define MTD_PKT_GEN_RXPKTCTR3                 0xF023
#define MTD_PKT_GEN_RXBYTCTR1                 0xF024
#define MTD_PKT_GEN_RXBYTCTR2                 0xF025
#define MTD_PKT_GEN_RXBYTCTR3                 0xF026
#define MTD_PKT_GEN_ERRPKTCTR1                0xF027
#define MTD_PKT_GEN_ERRPKTCTR2                0xF028
#define MTD_PKT_GEN_ERRPKTCTR3                0xF029
#define MTD_LINK_DROP_COUNTER                 0xF02A
#define MTD_PRBS_CONTROL                      0xF030
#define MTD_PRBS_SYM_TXCTR1                   0xF031
#define MTD_PRBS_SYM_TXCTR2                   0xF032
#define MTD_PRBS_SYM_TXCTR3                   0xF033
#define MTD_PRBS_SYM_RXCTR1                   0xF034
#define MTD_PRBS_SYM_RXCTR2                   0xF035
#define MTD_PRBS_SYM_RXCTR3                   0xF036
#define MTD_PRBS_SYM_ERRCTR1                  0xF037
#define MTD_PRBS_SYM_ERRCTR2                  0xF038
#define MTD_PRBS_SYM_ERRCTR3                  0xF039
#define MTD_PRBS_CONTROL2                     0xF040
#define MTD_PRBS_ELAPSE_TIME                  0xF041
#define MTD_PRBS_MSTR_ERRCTR1                 0xF042
#define MTD_PRBS_MSTR_ERRCTR2                 0xF043
#define MTD_PRBS_MSTR_ERRCTR3                 0xF044
#define MTD_PRBS_INTM_ERRCTR1                 0xF045
#define MTD_PRBS_INTM_ERRCTR2                 0xF046
#define MTD_PRBS_INTM_ERRCTR3                 0xF047

/* 88E2110/2180 LED Registers */
#define CUNIT_SLED_CONTROL        0xF03A
#define CUNIT_GPIO_CONTROL        0xF015
#define CUNIT_LED0_CONTROL        0xF020
#define CUNIT_LED1_CONTROL        0xF021
#define CUNIT_LED2_CONTROL        0xF022


#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif


#endif

