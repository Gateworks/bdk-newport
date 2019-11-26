/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions global register definitions for the
registers in the X5113.
********************************************************************/
#ifndef APIREGS_H
#define APIREGS_H
#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

/* X5113 Device Number Definitions */
#define MXD_LINE_PMA   1
#define MXD_LINE_SIDE  3
#define MXD_HOST_SIDE  4
#define MXD_BOTH_SIDE  5
#define MXD_AUTONEG    7
#define MXD_PORT_REG   31
#define MXD_CHIP_REG   31
#define MXD_A1_NIMB_REG  30

/* X5113 Register Offset Definitions */
#define MXD_HOST_REG_OFFSET         0x1000
#define MXD_FEC_REG_OFFSET          0x2000

/* X5113 Common registers */
#define MXD_IF_MODE_SEL_P0          0xF000

/* X5113 PMA and PMD registers */
#define MXD_PMA_CNTL                0x0000
#define MXD_PMA_STATUS1             0x0001
#define MXD_PMA_DEV_ID1             0x0002
#define MXD_PMA_DEV_ID2             0x0003
#define MXD_PMA_SPEED_ABILITY       0x0004
#define MXD_RSFEC_CNTL              0x00C8
#define MXD_RSFEC4_CNTL             0x80C8
#define MXD_RSFEC_STATUS            0x00C9
#define MXD_RSFEC4_STATUS           0x80C9
#define MXD_RSFEC_CORR_CW_CNTR      0x00CA
#define MXD_RSFEC_UNCORR_CW_CNTR    0x00CC
#define MXD_RSFEC_LANE_MAPPING      0x80CE
#define MXD_RSFEC_SYM_ERR_CNTR      0x00D2
#define MXD_RSFEC_BIP_ERR_CNTR      0x80E6
#define MXD_RSFEC_PCS_LANE_MAPPING  0x80FA
#define MXD_RSFEC_PCS_ALIGN_STATUS1 0x8118
#define MXD_RSFEC_PCS_ALIGN_STATUS2 0x8119
#define MXD_RSFEC_PCS_ALIGN_STATUS3 0x811A
#define MXD_RSFEC_PCS_ALIGN_STATUS4 0x811B

/* X5113 KR-FEC register */
#define MXD_KRFEC_ABILITY            0x00AA
#define MXD_KRFEC_CNTL               0x00AB
#define MXD_10GKRFEC_CORR_BLK_CNTR   0x00AC
#define MXD_10GKRFEC_UNCORR_BLK_CNTR 0x00AE
#define MXD_KRFEC_CORR_BLK_CNTR      0x012C
#define MXD_KRFEC_UNCORR_BLK_CNTR    0x02BC

#define MXD_PMA_100G_CNTL           0x0000
#define MXD_PMA_100G_CNTL_LANE(laneX) MXD_PMA_100G_CNTL+(laneX*0x2000)
#define MXD_PMA_40G_CNTL            0x2000
#define MXD_PMA_25G_CNTL            0x4000
#define MXD_PMA_1G_CNTL             0x6000

#define MXD_PMA_HOST_100G_CNTL      0x1000
#define MXD_PMA_HOST_100G_CNTL_LANE(laneX) MXD_PMA_HOST_100G_CNTL+(laneX*0x2000)
#define MXD_PMA_HOST_40G_CNTL       0x3000
#define MXD_PMA_HOST_25G_CNTL       0x5000
#define MXD_PMA_HOST_1G_CNTL        0x7000

/* X5113 Serdes Lane registers */
#define MXD_SERDES_LANE0            0xF201
#define MXD_SERDES_LANE0_REG_B      0xF20B
#define MXD_SERDES_LANE0_REG_14     0xF214
#define MXD_SERDES_LANE0_REG_15     0xF215
#define MXD_SERDES_LANE0_REG_16     0xF216
#define MXD_SERDES_LANE0_REG_17     0xF217
#define MXD_SERDES_LANE0_REG_18     0xF218
#define MXD_SERDES_LANE0_REG_19     0xF219

/* X5113 Auto-neg registers  */
#define MXD_AUTONEG_CNTL_LINE       0x0000
#define MXD_AUTONEG_STATUS_LINE     0x0001
#define MXD_AUTONEG_ADV1_LINE       0x0010
#define MXD_AUTONEG_ADV2_LINE       0x0011
#define MXD_AUTONEG_ADV3_LINE       0x0012
#define MXD_AUTONEG_LP_ABILITY_LINE 0x0013
#define MXD_AUTONEG_CNTL_HOST       0x1000
#define MXD_AUTONEG_STATUS_HOST     0x1001
#define MXD_AUTONEG_ADV1_HOST       0x1010
#define MXD_AUTONEG_ADV2_HOST       0x1011
#define MXD_AUTONEG_LP_ABILITY_HOST 0x1013
#define MXD_AUTONEG_ETH_STATUS_LINE 0x0030
#define MXD_AUTONEG_ETH_STATUS_HOST 0x1030
#define MXD_AUTONEG_LANE_CTRL_LINE  0x8012
#define MXD_AUTONEG_LANE_CTRL1_LINE 0x8014
#define MXD_AUTONEG_LANE_CTRL2_LINE 0x8015
#define MXD_AUTONEG_LANE_CTRL_HOST  0x9012
#define MXD_AUTONEG_LANE_CTRL1_HOST 0x9014

/* X5113 Packet Generator registers */
#define MXD_SERDES_CONTROL1         0x8103
#define MXD_SERDES_CONTROL2         0x8104
#define MXD_FIFO_CRC_INTR_ENABLE    0x810A
#define MXD_FIFO_CRC_INTR_STATUS    0x810B
#define MXD_FIFO_CONTROL1           0x810C
#define MXD_PKT_GEN_CONTROL1        0x8100
#define MXD_PKT_GEN_CONTROL2        0x8101
#define MXD_PKT_GEN_PAYLOAD1        0x8102
#define MXD_PKT_GEN_PAYLOAD2        0x8103
#define MXD_PKT_GEN_LENGTH          0x8106
#define MXD_PKT_GEN_BURSTSEQ        0x8107
#define MXD_PKT_GEN_IPG             0x8108
#define MXD_PKT_GEN_TXPKTCTR1       0x810B
#define MXD_PKT_GEN_TXPKTCTR2       0x810C
#define MXD_PKT_GEN_TXPKTCTR3       0x810D
#define MXD_PKT_GEN_TXBYTCTR1       0x810E
#define MXD_PKT_GEN_TXBYTCTR2       0x810F
#define MXD_PKT_GEN_TXBYTCTR3       0x8110
#define MXD_PKT_GEN_RXPKTCTR1       0x8111
#define MXD_PKT_GEN_RXPKTCTR2       0x8112
#define MXD_PKT_GEN_RXPKTCTR3       0x8113
#define MXD_PKT_GEN_RXBYTCTR1       0x8114
#define MXD_PKT_GEN_RXBYTCTR2       0x8115
#define MXD_PKT_GEN_RXBYTCTR3       0x8116
#define MXD_PKT_GEN_ERRPKTCTR1      0x8117
#define MXD_PKT_GEN_ERRPKTCTR2      0x8118
#define MXD_PKT_GEN_ERRPKTCTR3      0x8119

/* X5113 PRBS */
/* Line Side Lane 0 Registers, other lanes are offset 0x10 */
#define MXD_PRBS_CONTROL            0xF100
#define MXD_PRBS_SYM_TXCTR1         0xF101
#define MXD_PRBS_SYM_TXCTR2         0xF102
#define MXD_PRBS_SYM_TXCTR3         0xF103
#define MXD_PRBS_SYM_RXCTR1         0xF104
#define MXD_PRBS_SYM_RXCTR2         0xF105
#define MXD_PRBS_SYM_RXCTR3         0xF106
#define MXD_PRBS_SYM_ERRCTR1        0xF107
#define MXD_PRBS_SYM_ERRCTR2        0xF108
#define MXD_PRBS_SYM_ERRCTR3        0xF109
#define MXD_PRBS0_TEST_PATTA        0xF10A
#define MXD_PRBS0_TEST_PATTB        0xF10B

/* Host Side Lane 0 Registers, other lanes are offset 0x10 */
#define MXD_HOST_PRBS_CONTROL       0xF100
#define MXD_HOST_PRBS_SYM_TXCTR1    0xF101
#define MXD_HOST_PRBS_SYM_TXCTR2    0xF102
#define MXD_HOST_PRBS_SYM_TXCTR3    0xF103
#define MXD_HOST_PRBS_SYM_RXCTR1    0xF104
#define MXD_HOST_PRBS_SYM_RXCTR2    0xF105
#define MXD_HOST_PRBS_SYM_RXCTR3    0xF106
#define MXD_HOST_PRBS_SYM_ERRCTR1   0xF107
#define MXD_HOST_PRBS_SYM_ERRCTR2   0xF108
#define MXD_HOST_PRBS_SYM_ERRCTR3   0xF109
#define MXD_HOST_PRBS0_TEST_PATTA   0xF10A
#define MXD_HOST_PRBS0_TEST_PATTB   0xF10B

#define MXD_PCS_LANE_OFFSET_SHIFT   0x200

/* X5113 100G registers  */
#define MXD_PCS_100G_CNTL           0x0000
#define MXD_PCS_100G_STATUS1        0x0001
#define MXD_PCS_100G_DEV_ID1        0x0002
#define MXD_PCS_100G_DEV_ID2        0x0003
#define MXD_PCS_100G_SPEED_ABILITY  0x0004
#define MXD_PCS_100G_PCS_STATUS2    0x0008

#define MXD_PCS_100G_INTR_EN1       0x8001
#define MXD_PCS_100G_INTR_EN2       0x8002
#define MXD_PCS_100G_INTR_STAT1     0x8003
#define MXD_PCS_100G_INTR_STAT2     0x8004
#define MXD_PCS_100G_RT_STAT1       0x8005
#define MXD_PCS_100G_RT_STAT2       0x8006

/* X5113 40G registers  */
#define MXD_PCS_40G_CNTL            0x1000
#define MXD_PCS_40G_STATUS1         0x1001
#define MXD_PCS_40G_DEV_ID1         0x1002
#define MXD_PCS_40G_DEV_ID2         0x1003
#define MXD_PCS_40G_SPEED_ABILITY   0x1004
#define MXD_PCS_40G_PCS_STATUS2     0x1008

#define MXD_PCS_40G_INTR_EN         0x9001
#define MXD_PCS_40G_INTR_STAT       0x9002
#define MXD_PCS_40G_RT_STAT         0x9003

/* X5113 25G registers, lane 0, lane offset is 0x200  */
/* also used for 10G and 5G                           */
#define MXD_PCS_25G_CNTL            0x2000
#define MXD_PCS_25G_CNTL_LANE(laneX) MXD_PCS_25G_CNTL+(laneX*MXD_PCS_LANE_OFFSET_SHIFT)
#define MXD_PCS_25G_STATUS          0x2001
#define MXD_PCS_25G_PCS_STATUS2     0x2008
#define MXD_PCS_25G_INTR_EN         0xA000
#define MXD_PCS_25G_INTR_STAT       0xA001
#define MXD_PCS_25G_RT_STAT         0xA002

/* X5113 1G/2.5G registers  */
#define MXD_PCS_1G_CNTL             0x3000
#define MXD_PCS_1G_CNTL_LANE(laneX)   MXD_PCS_1G_CNTL+(laneX*MXD_PCS_LANE_OFFSET_SHIFT)
#define MXD_PCS_1G_STAT             0x3001
#define MXD_PCS_1G_AN_ADV           0x3004
#define MXD_PCS_1G_AN_ADV_LANE(laneX) MXD_PCS_1G_AN_ADV+(laneX*MXD_PCS_LANE_OFFSET_SHIFT)
#define MXD_PCS_1G_INTR_EN          0xB001
#define MXD_PCS_1G_INTR_STAT        0xB002
#define MXD_PCS_1G_RT_STAT          0xB003

/* Chip Level Common Registers */
#define MXD_GLOBAL_RESET            0xF404
#define MXD_GLOBAL_INTR_STAT        0xF420
#define MXD_GLOBAL_INTR_CNTL        0xF421
#define MXD_IPG_CFG_CNTL            0xF600
#define MXD_RM_FIFO_INTR_STAT       0xF60C
#define MXD_RM_FIFO_INTR_MASK       0xF60D
#define MXD_RM_FIFO_TX_THR_H        0xF603
#define MXD_RM_FIFO_TX_THR_L        0xF604
#define MXD_RM_FIFO_RX_THR          0xF605
#define MXD_RM_FIFO_TX_SAT_THR      0xF607
#define MXD_RM_FIFO_TX_DROP_CNTR    0xF646
#define MXD_RM_FIFO_RX_DROP_CNTR    0xF686

/* Port Level Common Registers */
#define MXD_PORT_PWD_RESET          0xF003
#define MXD_PORT_PCS_CNTL           0xF010

#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif

