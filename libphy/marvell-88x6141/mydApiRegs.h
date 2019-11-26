/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions global register definitions for the
registers in the Marvell X7120/X6181/X6141 PHYs.
********************************************************************/
#ifndef APIREGS_H
#define APIREGS_H
#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

/* Marvell X7120/X6181/X6141 Device Number Definitions */
#define MYD_PMA_DEV    1
#define MYD_LINE_SIDE  3
#define MYD_HOST_SIDE  4
#define MYD_BOTH_SIDE  5
#define MYD_AUTONEG    7
#define MYD_PORT_REG   31
#define MYD_CHIP_REG   31
#define MYD_NIMB_REG   30

/* Misc defines that are used by some functions */
#define MYD_ALL_LANES 4 

/* Chip Level Common Registers */
#define MYD_GLOBAL_RESET      0xF404
#define MYD_GLOBAL_INTR_STAT  0xF420
#define MYD_GLOBAL_INTR_CNTL  0xF421

/* Port Level Common Registers */
#define MYD_PORT_PWD_RESET   0xF003
#define MYD_PORT_PCS_CNTL    0xF010

/* Data Path Control Registers */
#define MYD_DATAPATH_CNTL    0xF085
#define MYD_DISENGAGE_TYPE   0xF0A9

/* Mode setting register */
#define MYD_MODE_SELECTION   0xF000

/* Host and Line PCS controls */
#define MYD_PCS_200G_CNTL    0x4000
#define MYD_PCS_400G_CNTL    0x0000

/* 1G/2.5G registers  */
#define MYD_PCS_1G_CNTL             0x3000
#define MYD_PCS_1G_CNTL_LANE(laneX) MYD_PCS_1G_CNTL+(laneX*0x0200)
#define MYD_PCS_1G_STATUS           0x3001
#define MYD_PCS_1G_AN_ADV           0x3004
#define MYD_PCS_1G_AN_ADV_LANE(laneX) MYD_PCS_1G_AN_ADV+(laneX*0x0200)
#define MYD_PCS_1G_INTR_BASE        0xB001
#define MYD_PCS_1G_INTR_EN_LANE(laneX)      (MYD_PCS_1G_INTR_BASE+(laneX*0x0200))
#define MYD_PCS_1G_INTR_STAT_LANE(laneX)    (MYD_PCS_1G_INTR_BASE+0x0001+(laneX*0x0200))    /* 0xB002 */
#define MYD_PCS_1G_RT_STAT_LANE(laneX)      (MYD_PCS_1G_INTR_BASE+0x0002+(laneX*0x0200))    /* 0xB003 */

/* 25G registers, lane 0, lane offset is 0x200  */
/* also used for 10G and 5G  */
#define MYD_PCS_25G_CNTL            0x2000
#define MYD_PCS_25G_CNTL_LANE(laneX) MYD_PCS_25G_CNTL+(laneX*0x0200)
#define MYD_PCS_25G_STATUS          0x2001
#define MYD_PCS_25G_PCS_STATUS2(laneX) (0x2008 + (laneX*0x0200))
#define MYD_PCS_25G_INTR_BASE       0xA000
#define MYD_PCS_25G_INTR_EN_LANE(laneX)     (MYD_PCS_25G_INTR_BASE+(laneX*0x0200))
#define MYD_PCS_25G_INTR_STAT_LANE(laneX)   (MYD_PCS_25G_INTR_BASE+0x0001+(laneX*0x0200))   /* 0xA001 */
#define MYD_PCS_25G_RT_STAT_LANE(laneX)     (MYD_PCS_25G_INTR_BASE+0x0002+(laneX*0x0200))   /* 0xA002 */

/* 40G registers  */
#define MYD_PCS_40G_CNTL            0x1000
#define MYD_PCS_40G_CNTL_LANE(laneX) MYD_PCS_40G_CNTL+(laneX*0x0200)
#define MYD_PCS_40G_STATUS1         0x1001
#define MYD_PCS_40G_DEV_ID1         0x1002
#define MYD_PCS_40G_DEV_ID2         0x1003
#define MYD_PCS_40G_SPEED_ABILITY   0x1004
#define MYD_PCS_40G_PCS_STATUS2(laneX) (0x1008+(laneX*0x0200))

#define MYD_PCS_40G_INTR_BASE1      0x9001
#define MYD_PCS_40G_INTR_EN1_LANE(laneX)    (MYD_PCS_40G_INTR_BASE1+(laneX*0x0200))
#define MYD_PCS_40G_INTR_STAT1_LANE(laneX)  (MYD_PCS_40G_INTR_BASE1+0x0001+(laneX*0x0200))  /* 0x9002 */
#define MYD_PCS_40G_RT_STAT1_LANE(laneX)    (MYD_PCS_40G_INTR_BASE1+0x0002+(laneX*0x0200))  /* 0x9003 */
#define MYD_PCS_40G_INTR_BASE2      0x900D
#define MYD_PCS_40G_INTR_EN2_LANE(laneX)    (MYD_PCS_40G_INTR_BASE2+(laneX*0x0200))
#define MYD_PCS_40G_INTR_STAT2_LANE(laneX)  (MYD_PCS_40G_INTR_BASE2+0x0001+(laneX*0x0200))  /* 0x900E */
#define MYD_PCS_40G_RT_STAT2_LANE(laneX)    (MYD_PCS_40G_INTR_BASE2+0x0002+(laneX*0x0200))  /* 0x900F */

/* 100G registers  */
#define MYD_PCS_100G_CNTL           0x0000
#define MYD_PCS_100G_CNTL_LANE(laneX) MYD_PCS_100G_CNTL+(laneX*0x0200)
#define MYD_PCS_100G_STATUS1        0x0001
#define MYD_PCS_100G_DEV_ID1        0x0002
#define MYD_PCS_100G_DEV_ID2        0x0003
#define MYD_PCS_100G_SPEED_ABILITY  0x0004
#define MYD_PCS_100G_PCS_STATUS2(laneX) (0x0008 +(laneX*0x0200))

#define MYD_PCS_100G_INTR_BASE1     0x8001
#define MYD_PCS_100G_INTR_EN1_LANE(laneX)   (MYD_PCS_100G_INTR_BASE1+(laneX*0x0200))
#define MYD_PCS_100G_INTR_STAT1_LANE(laneX) (MYD_PCS_100G_INTR_BASE1+0x0002+(laneX*0x0200))  /* 0x8003 */
#define MYD_PCS_100G_RT_STAT1_LANE(laneX)   (MYD_PCS_100G_INTR_BASE1+0x0004+(laneX*0x0200))  /* 0x8005 */
#define MYD_PCS_100G_INTR_BASE2     0x8002
#define MYD_PCS_100G_INTR_EN2_LANE(laneX)   (MYD_PCS_100G_INTR_BASE2+(laneX*0x0200))
#define MYD_PCS_100G_INTR_STAT2_LANE(laneX) (MYD_PCS_100G_INTR_BASE2+0x0002+(laneX*0x0200))  /* 0x8004 */
#define MYD_PCS_100G_RT_STAT2_LANE(laneX)   (MYD_PCS_100G_INTR_BASE2+0x0004+(laneX*0x0200))  /* 0x8006 */

/* 200G registers  */
#define MYD_PCS_200G_CNTL           0x4000
#define MYD_PCS_200G_STATUS1        0x4001
#define MYD_PCS_200G_DEV_ID1        0x4002
#define MYD_PCS_200G_DEV_ID2        0x4003
#define MYD_PCS_200G_SPEED_ABILITY  0x4004
#define MYD_PCS_200G_PCS_STATUS2    0x4008

#define MYD_PMA_100G_CNTL           0x0000
#define MYD_PMA_100G_CNTL_LANE(laneX) MYD_PMA_100G_CNTL+(laneX*0x2000)
#define MYD_PMA_40G_CNTL            0x2000
#define MYD_PMA_25G_CNTL            0x4000
#define MYD_PMA_1G_CNTL             0x6000

#define MYD_PCS_200G_INTR_EN        0xC001
#define MYD_PCS_200G_INTR_STAT      0xC003
#define MYD_PCS_200G_RT_STAT        0xC005

#define MYD_PMA_HOST_200G_CNTL      0x1000
#define MYD_PMA_HOST_100G_CNTL      0x1000
#define MYD_PMA_HOST_100G_CNTL_LANE(laneX) MYD_PMA_HOST_100G_CNTL+(laneX*0x2000)
#define MYD_PMA_HOST_40G_CNTL       0x3000
#define MYD_PMA_HOST_25G_CNTL       0x5000
#define MYD_PMA_HOST_1G_CNTL        0x7000

/* Auto-neg registers  */
#define MYD_AUTONEG_CNTL_LINE        0x0000
#define MYD_AUTONEG_STATUS_LINE      0x0001
#define MYD_AUTONEG_ADV1_LINE        0x0010
#define MYD_AUTONEG_ADV2_LINE        0x0011
#define MYD_AUTONEG_ADV3_LINE        0x0012
#define MYD_AUTONEG_LP_ABILITY_LINE  0x0013
#define MYD_AUTONEG_CNTL_HOST        0x1000
#define MYD_AUTONEG_STATUS_HOST      0x1001
#define MYD_AUTONEG_ADV1_HOST        0x1010
#define MYD_AUTONEG_ADV2_HOST        0x1011
#define MYD_AUTONEG_ADV3_HOST        0x1012
#define MYD_AUTONEG_LP_ABILITY_HOST  0x1013
#define MYD_AUTONEG_ETH_STATUS_LINE  0x0030
#define MYD_AUTONEG_ETH_STATUS_HOST  0x1030
#define MYD_AUTONEG_CTRL_REG_LINE    0x8000
#define MYD_AUTONEG_LANE_CTRL18_LINE 0x8012
#define MYD_AUTONEG_LANE_CTRL20_LINE 0x8014
#define MYD_AUTONEG_LANE_CTRL21_LINE 0x8015
#define MYD_AUTONEG_CTRL_REG_HOST    0x9000
#define MYD_AUTONEG_LANE_CTRL18_HOST 0x9012
#define MYD_AUTONEG_LANE_CTRL20_HOST 0x9014
#define MYD_AUTONEG_LANE_CTRL21_HOST 0x9015

/* Serdes Lane registers */
#define MYD_SERDES_LANE0            0xF201
#define MYD_SERDES_LANE0_REG_B      0xF20B
#define MYD_SERDES_LANE0_REG_14     0xF214
#define MYD_SERDES_LANE0_REG_15     0xF215
#define MYD_SERDES_LANE0_REG_16     0xF216
#define MYD_SERDES_LANE0_REG_17     0xF217
#define MYD_SERDES_LANE0_REG_18     0xF218
#define MYD_SERDES_LANE0_REG_19     0xF219

/* Packet Generator registers */
#define MYD_SERDES_CONTROL1         0x8103
#define MYD_SERDES_CONTROL2         0x8104
#define MYD_FIFO_CRC_INTR_ENABLE    0x810A
#define MYD_FIFO_CRC_INTR_STATUS    0x810B
#define MYD_FIFO_CONTROL1           0x810C
#define MYD_PKT_GEN_CONTROL1        0x8100
#define MYD_PKT_GEN_CONTROL2        0x8101
#define MYD_PKT_GEN_PAYLOAD1        0x8102
#define MYD_PKT_GEN_PAYLOAD2        0x8103
#define MYD_PKT_GEN_LENGTH          0x8106
#define MYD_PKT_GEN_BURSTSEQ        0x8107
#define MYD_PKT_GEN_IPG             0x8108
#define MYD_PKT_GEN_TXPKTCTR1       0x810B
#define MYD_PKT_GEN_TXPKTCTR2       0x810C
#define MYD_PKT_GEN_TXPKTCTR3       0x810D
#define MYD_PKT_GEN_TXBYTCTR1       0x810E
#define MYD_PKT_GEN_TXBYTCTR2       0x810F
#define MYD_PKT_GEN_TXBYTCTR3       0x8110
#define MYD_PKT_GEN_RXPKTCTR1       0x8111
#define MYD_PKT_GEN_RXPKTCTR2       0x8112
#define MYD_PKT_GEN_RXPKTCTR3       0x8113
#define MYD_PKT_GEN_RXBYTCTR1       0x8114
#define MYD_PKT_GEN_RXBYTCTR2       0x8115
#define MYD_PKT_GEN_RXBYTCTR3       0x8116
#define MYD_PKT_GEN_ERRPKTCTR1      0x8117
#define MYD_PKT_GEN_ERRPKTCTR2      0x8118
#define MYD_PKT_GEN_ERRPKTCTR3      0x8119

/* PRBS */
/* Side Lane 0 Registers, other lanes are offset 0x10 */
#define MYD_PRBS_CONTROL            0xF100
#define MYD_PRBS_SYM_TXCTR1         0xF101
#define MYD_PRBS_SYM_TXCTR2         0xF102
#define MYD_PRBS_SYM_TXCTR3         0xF103
#define MYD_PRBS_SYM_RXCTR1         0xF104
#define MYD_PRBS_SYM_RXCTR2         0xF105
#define MYD_PRBS_SYM_RXCTR3         0xF106
#define MYD_PRBS_SYM_ERRCTR1        0xF107
#define MYD_PRBS_SYM_ERRCTR2        0xF108
#define MYD_PRBS_SYM_ERRCTR3        0xF109
#define MYD_PRBS0_TEST_PATTA        0xF10A
#define MYD_PRBS0_TEST_PATTB        0xF10B

#define MYD_IEEE_LINE_PRBS_CONTROL   0x05DD
#define MYD_IEEE_HOST_PRBS_CONTROL   0x15DD

/* RS-FEC Registers */
#define MYD_RSFEC_CNTL(lineX, laneX) ((lineX == MYD_LINE_SIDE) ? (0x00C8+laneX*0x2000) : (0x10C8+laneX*0x2000))
#define MYD_RSFEC_STAT(lineX, laneX) ((lineX == MYD_LINE_SIDE) ? (0x00C9+laneX*0x2000) : (0x10C9+laneX*0x2000))
#define MYD_RSFEC_CORR_CW_LOW(lineX, laneX) ((lineX == MYD_LINE_SIDE) ? (0x00CA+laneX*0x2000) : (0x10CA+laneX*0x2000))
#define MYD_RSFEC_UNCORR_CW_LOW(lineX, laneX) ((lineX == MYD_LINE_SIDE) ? (0x00CC+laneX*0x2000) : (0x10CC+laneX*0x2000))
#define MYD_RSFEC_LANE_MAP(lineX, laneX) ((lineX == MYD_LINE_SIDE) ? ((0x00CE)+laneX*0x2000) : ((0x10CE)+laneX*0x2000)) /* this is the PMA lane mapping register */
#define MYD_RSFEC_SYM_ERR_CTR_LOW(lineX, laneX, pcslaneX) ((lineX == MYD_LINE_SIDE) ? (0x00D2+laneX*0x2000+pcslaneX*2) : (0x10D2+laneX*0x2000+pcslaneX*2))
#define MYD_RSFEC_PCS_ALIGN_STAT1(lineX, laneX) ((lineX == MYD_LINE_SIDE) ? (0x0118+laneX*0x2000) : (0x1118+laneX*0x2000))
#define MYD_RSFEC_PCS_ALIGN_STAT2(lineX, laneX) ((lineX == MYD_LINE_SIDE) ? (0x0119+laneX*0x2000) : (0x1119+laneX*0x2000))
#define MYD_RSFEC_PCS_ALIGN_STAT3(lineX, laneX) ((lineX == MYD_LINE_SIDE) ? (0x011A+laneX*0x2000) : (0x111A+laneX*0x2000))
#define MYD_RSFEC_PCS_ALIGN_STAT4(lineX, laneX) ((lineX == MYD_LINE_SIDE) ? (0x011B+laneX*0x2000) : (0x111B+laneX*0x2000))

/* These are TX and not very useful. Always return 0 or static count 0...10 */
#define MYD_RSFEC_BIP_ERR_CTR(lineX, laneX, pcslaneX) ((lineX == MYD_LINE_SIDE) ? (0x00E6+laneX*0x2000+pcslaneX*1) : (0x10E6+laneX*0x2000+pcslaneX*1))
#define MYD_RSFEC_PCS_LN_MAP(lineX, laneX, ifX) ((lineX == MYD_LINE_SIDE) ? (0x00FA+laneX*0x2000+ifX*1) : (0x10FA+laneX*0x2000+ifX*1))

/* 40G and 50G PCS RX Registers */
#define MYD_40G50G_BIP_ERR_CTR(laneX, pcslaneX) (0x10C8 + 0x200 * laneX + pcslaneX) /* range for pcslaneX is 0...3 */
#define MYD_40G50G_PCS_LN_MAP(laneX, pcslaneX)  (0x1190 + 0x200 * laneX + pcslaneX) /* range for laneX is 0...3 */

/* 100G PCS RX Registers */
#define MYD_100G_BIP_ERR_CTR(laneX, pcslaneX) (0x00C8 + 0x200 * laneX + pcslaneX) /* range for pcslaneX is 0...19 */
#define MYD_100G_PCS_LN_MAP(laneX, pcslaneX)  (0x0190 + 0x200 * laneX + pcslaneX) /* range for laneX is 0 or 2*/

/* 200GR4 RS-FEC Registers */
#define MYD_200GR4_FEC_RX_LINK_STATUS            0x4032
#define MYD_200GR4_FEC_LANE_ALIGN                0x4034
#define MYD_200GR4_FEC_DEG_SER_CTL               0x4320
#define MYD_200GR4_FEC_DEG_SER                   0x4321
#define MYD_200GR4_FEC_LANE_MAP(feclaneX)        (0x4190+feclaneX)
#define MYD_200GR4_FEC_CORR_CW_LOW               0x4322
#define MYD_200GR4_FEC_UNCORR_CW_LOW             0x4324
#define MYD_200GR4_FEC_SYM_ERR_CTR_LOW(feclaneX) (0x4258+2*feclaneX)
#define MYD_200GR4_FEC_DEGSER_ACT_LOW            0x4326
#define MYD_200GR4_FEC_DEGSER_DEACT_LOW          0x4328
#define MYD_200GR4_FEC_DEGSER_INT_LOW            0x432A

/* KR-FEC Registers */
#define MYD_KRFEC_STAT(lineX, laneX) ((lineX == MYD_LINE_SIDE) ? (0x00AA+laneX*0x2000) : (0x10AA+laneX*0x2000))
#define MYD_KRFEC_CNTL(lineX, laneX) ((lineX == MYD_LINE_SIDE) ? (0x00AB+laneX*0x2000) : (0x10AB+laneX*0x2000))
#define MYD_KRFEC_CORR_BLK_LOW(lineX, laneX) ((lineX == MYD_LINE_SIDE) ? (0x00AC+laneX*0x2000) : (0x10AC+laneX*0x2000))
#define MYD_KRFEC_UNCORR_BLK_LOW(lineX, laneX) ((lineX == MYD_LINE_SIDE) ? ((0x00AE)+laneX*0x2000) : ((0x10AE)+laneX*0x2000))

/* GPIO/LED/RCLK Control Registers */
#define MYD_LINE_RCVCLK_CTRL1                    0xF422
#define MYD_LINE_RCVCLK_CTRL2                    0xF423
#define MYD_HOST_RCVCLK_CTRL1                    0xF424
#define MYD_HOST_RCVCLK_CTRL2                    0xF425
#define MYD_PORT_RCVCLK_SRC_MUX                  0xF426
#define MYD_PORT_RCVCLK_CTRL1                    0xF427
#define MYD_PORT_RCVCLK_CTRL2                    0xF429
#define MYD_GPIO4_CTRL                           0xF430
#define MYD_CLK_OUT_SE1_CTRL                     0xF430
#define MYD_LED4_CTRL_STATUS                     0xF431
#define MYD_GPIO5_CTRL                           0xF432
#define MYD_CLK_OUT_SE2_CTRL                     0xF432
#define MYD_LED5_CTRL_STATUS                     0xF433
#define MYD_LED_MIXING_CTRL1                     0xF434
#define MYD_LED_TIMER_CTRL                       0xF435
#define MYD_GPIO0_CTRL                           0xF437
#define MYD_LED0_CTRL_STATUS                     0xF438
#define MYD_GPIO1_CTRL                           0xF439
#define MYD_LED1_CTRL_STATUS                     0xF43A
#define MYD_GPIO2_CTRL                           0xF43B
#define MYD_LED2_CTRL_STATUS                     0xF43C
#define MYD_GPIO3_CTRL                           0xF43D
#define MYD_LED3_CTRL_STATUS                     0xF43E
#define MYD_LED_MIXING_CTRL2                     0xF43F

/* IPG and FIFO Control Registers */
#define MYD_IPG_CFG_CNTL            0xF600
#define MYD_RM_FIFO_INTR_STAT       0xF60C
#define MYD_RM_FIFO_INTR_MASK       0xF60D
#define MYD_RM_FIFO_TX_THR_H        0xF603
#define MYD_RM_FIFO_TX_THR_L        0xF604
#define MYD_RM_FIFO_RX_THR          0xF605
#define MYD_RM_FIFO_TX_SAT_THR      0xF607
#define MYD_RM_FIFO_TX_DROP_CNTR    0xF646
#define MYD_RM_FIFO_RX_DROP_CNTR    0xF686


#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif

