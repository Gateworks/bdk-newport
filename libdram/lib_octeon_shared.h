/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

extern const dimm_odt_config_t disable_odt_config[];

#define rttnom_none   0         /* Rtt_Nom disabled */
#define rttnom_60ohm  1         /* RZQ/4  = 240/4  =  60 ohms */
#define rttnom_120ohm 2         /* RZQ/2  = 240/2  = 120 ohms */
#define rttnom_40ohm  3         /* RZQ/6  = 240/6  =  40 ohms */
#define rttnom_20ohm  4         /* RZQ/12 = 240/12 =  20 ohms */
#define rttnom_30ohm  5         /* RZQ/8  = 240/8  =  30 ohms */
#define rttnom_rsrv1  6         /* Reserved */
#define rttnom_rsrv2  7         /* Reserved */

#define rttwr_none    0         /* Dynamic ODT off */
#define rttwr_60ohm   1         /* RZQ/4  = 240/4  =  60 ohms */
#define rttwr_120ohm  2         /* RZQ/2  = 240/2  = 120 ohms */
#define rttwr_rsrv1   3         /* Reserved */

#define dic_40ohm     0         /* RZQ/6  = 240/6  =  40 ohms */
#define dic_34ohm     1         /* RZQ/7  = 240/7  =  34 ohms */

#define driver_24_ohm   1
#define driver_27_ohm   2
#define driver_30_ohm   3
#define driver_34_ohm   4
#define driver_40_ohm   5
#define driver_48_ohm   6
#define driver_60_ohm   7

#define rodt_ctl_none     0
#define rodt_ctl_20_ohm   1
#define rodt_ctl_30_ohm   2
#define rodt_ctl_40_ohm   3
#define rodt_ctl_60_ohm   4
#define rodt_ctl_120_ohm  5

#define ddr4_rttnom_none   0         /* Rtt_Nom disabled */
#define ddr4_rttnom_60ohm  1         /* RZQ/4  = 240/4  =  60 ohms */
#define ddr4_rttnom_120ohm 2         /* RZQ/2  = 240/2  = 120 ohms */
#define ddr4_rttnom_40ohm  3         /* RZQ/6  = 240/6  =  40 ohms */
#define ddr4_rttnom_240ohm 4         /* RZQ/1  = 240/1  = 240 ohms */
#define ddr4_rttnom_48ohm  5         /* RZQ/5  = 240/5  =  48 ohms */
#define ddr4_rttnom_80ohm  6         /* RZQ/3  = 240/3  =  80 ohms */
#define ddr4_rttnom_34ohm  7         /* RZQ/7  = 240/7  =  34 ohms */

#define ddr4_rttwr_none    0         /* Dynamic ODT off */
#define ddr4_rttwr_120ohm  1         /* RZQ/2  = 240/2  = 120 ohms */
#define ddr4_rttwr_240ohm  2         /* RZQ/1  = 240/1  = 240 ohms */
#define ddr4_rttwr_HiZ     3         /* HiZ */
/* This setting is available for 81xx and 83xx */
#define ddr4_rttwr_80ohm   4         /* RZQ/3  = 240/3  =  80 ohms */

#define ddr4_dic_34ohm     0         /* RZQ/7  = 240/7  =  34 ohms */
#define ddr4_dic_48ohm     1         /* RZQ/5  = 240/5  =  48 ohms */

#define ddr4_rttpark_none   0         /* Rtt_Park disabled */
#define ddr4_rttpark_60ohm  1         /* RZQ/4  = 240/4  =  60 ohms */
#define ddr4_rttpark_120ohm 2         /* RZQ/2  = 240/2  = 120 ohms */
#define ddr4_rttpark_40ohm  3         /* RZQ/6  = 240/6  =  40 ohms */
#define ddr4_rttpark_240ohm 4         /* RZQ/1  = 240/1  = 240 ohms */
#define ddr4_rttpark_48ohm  5         /* RZQ/5  = 240/5  =  48 ohms */
#define ddr4_rttpark_80ohm  6         /* RZQ/3  = 240/3  =  80 ohms */
#define ddr4_rttpark_34ohm  7         /* RZQ/7  = 240/7  =  34 ohms */

#define ddr4_driver_26_ohm   2
#define ddr4_driver_30_ohm   3
#define ddr4_driver_34_ohm   4
#define ddr4_driver_40_ohm   5
#define ddr4_driver_48_ohm   6

#define ddr4_dqx_driver_24_ohm   1
#define ddr4_dqx_driver_27_ohm   2
#define ddr4_dqx_driver_30_ohm   3
#define ddr4_dqx_driver_34_ohm   4
#define ddr4_dqx_driver_40_ohm   5
#define ddr4_dqx_driver_48_ohm   6
#define ddr4_dqx_driver_60_ohm   7

#define ddr4_rodt_ctl_none     0
#define ddr4_rodt_ctl_40_ohm   1
#define ddr4_rodt_ctl_60_ohm   2
#define ddr4_rodt_ctl_80_ohm   3
#define ddr4_rodt_ctl_120_ohm  4
#define ddr4_rodt_ctl_240_ohm  5
#define ddr4_rodt_ctl_34_ohm   6
#define ddr4_rodt_ctl_48_ohm   7

// for CN9XXX
#define ddr4_driver_21_ohm_cn9   1
#define ddr4_driver_24_ohm_cn9   2
#define ddr4_driver_27_ohm_cn9   3
#define ddr4_driver_30_ohm_cn9   4
#define ddr4_driver_36_ohm_cn9   5
#define ddr4_driver_44_ohm_cn9   6

#define ddr4_dqx_driver_20_ohm_cn9   1
#define ddr4_dqx_driver_22_ohm_cn9   2
#define ddr4_dqx_driver_25_ohm_cn9   3
#define ddr4_dqx_driver_29_ohm_cn9   4
#define ddr4_dqx_driver_34_ohm_cn9   5
#define ddr4_dqx_driver_40_ohm_cn9   6
#define ddr4_dqx_driver_50_ohm_cn9   7

#define ddr4_rodt_ctl_none_cn9     0
#define ddr4_rodt_ctl_34_ohm_cn9   1
#define ddr4_rodt_ctl_40_ohm_cn9   2
#define ddr4_rodt_ctl_50_ohm_cn9   3
#define ddr4_rodt_ctl_67_ohm_cn9   4
#define ddr4_rodt_ctl_100_ohm_cn9  5

