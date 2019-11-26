#ifndef __BDK_CSRS_NCSI_H__
#define __BDK_CSRS_NCSI_H__
/* This file is auto-generated. Do not edit */

/***********************license start***********************************
* Copyright (C) 2019 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/


/**
 * @file
 *
 * Configuration and status register (CSR) address and type definitions for
 * OcteonTX NCSI.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration ncsi_bar_e
 *
 * NCSI Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_NCSI_BAR_E_NCSI_PF_BAR0_CN8 (0x87e00b000000ll)
#define BDK_NCSI_BAR_E_NCSI_PF_BAR0_CN8_SIZE 0x800000ull
#define BDK_NCSI_BAR_E_NCSI_PF_BAR0_CN9 (0x87e00b000000ll)
#define BDK_NCSI_BAR_E_NCSI_PF_BAR0_CN9_SIZE 0x10000ull
#define BDK_NCSI_BAR_E_NCSI_PF_BAR4 (0x87e00bf00000ll)
#define BDK_NCSI_BAR_E_NCSI_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration ncsi_ctl_pkt_type_e
 *
 * NCSI Control Packet Type Enumeration
 * Enumerates the control packet types. For more information see the NC-SI standard.
 */
#define BDK_NCSI_CTL_PKT_TYPE_E_AEN_EN (8)
#define BDK_NCSI_CTL_PKT_TYPE_E_CLR_INIT (0)
#define BDK_NCSI_CTL_PKT_TYPE_E_DIS_BCST (0x11)
#define BDK_NCSI_CTL_PKT_TYPE_E_DIS_CHAN (4)
#define BDK_NCSI_CTL_PKT_TYPE_E_DIS_CHAN_NW (7)
#define BDK_NCSI_CTL_PKT_TYPE_E_DIS_MCST (0x13)
#define BDK_NCSI_CTL_PKT_TYPE_E_DIS_VLAN (0xd)
#define BDK_NCSI_CTL_PKT_TYPE_E_DSEL_PKG (2)
#define BDK_NCSI_CTL_PKT_TYPE_E_EN_BCST (0x10)
#define BDK_NCSI_CTL_PKT_TYPE_E_EN_CHAN (3)
#define BDK_NCSI_CTL_PKT_TYPE_E_EN_CHAN_NW (6)
#define BDK_NCSI_CTL_PKT_TYPE_E_EN_MCST (0x12)
#define BDK_NCSI_CTL_PKT_TYPE_E_EN_VLAN (0xc)
#define BDK_NCSI_CTL_PKT_TYPE_E_GET_CAP (0x16)
#define BDK_NCSI_CTL_PKT_TYPE_E_GET_ID (0x15)
#define BDK_NCSI_CTL_PKT_TYPE_E_GET_LINK (0xa)
#define BDK_NCSI_CTL_PKT_TYPE_E_GET_NCSI_STAT (0x19)
#define BDK_NCSI_CTL_PKT_TYPE_E_GET_PAR (0x17)
#define BDK_NCSI_CTL_PKT_TYPE_E_GET_PASS_STAT (0x1a)
#define BDK_NCSI_CTL_PKT_TYPE_E_GET_PKT_STAT (0x18)
#define BDK_NCSI_CTL_PKT_TYPE_E_OEM (0x50)
#define BDK_NCSI_CTL_PKT_TYPE_E_RST_CHAN (5)
#define BDK_NCSI_CTL_PKT_TYPE_E_SEL_PKG (1)
#define BDK_NCSI_CTL_PKT_TYPE_E_SET_FLOW (0x14)
#define BDK_NCSI_CTL_PKT_TYPE_E_SET_LINK (9)
#define BDK_NCSI_CTL_PKT_TYPE_E_SET_MAC (0xe)
#define BDK_NCSI_CTL_PKT_TYPE_E_SET_VLAN (0xb)

/**
 * Enumeration ncsi_int_vec_e
 *
 * NCSI MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_NCSI_INT_VEC_E_INTS (0)

/**
 * Enumeration ncsi_reason_e
 *
 * NCSI Reason Code Enumeration
 * Enumerates the NCSI standard reason codes.
 */
#define BDK_NCSI_REASON_E_CHAN (3)
#define BDK_NCSI_REASON_E_INIT (1)
#define BDK_NCSI_REASON_E_NONE (0)
#define BDK_NCSI_REASON_E_UNSUP (2)

/**
 * Enumeration ncsi_resp_e
 *
 * NCSI Response Code Enumeration
 */
#define BDK_NCSI_RESP_E_COMPLETED (0)
#define BDK_NCSI_RESP_E_CSR_READ (0x8000)
#define BDK_NCSI_RESP_E_CSR_WRITE (0x8001)
#define BDK_NCSI_RESP_E_FAILED (1)
#define BDK_NCSI_RESP_E_UNAVAIL (2)
#define BDK_NCSI_RESP_E_UNSUP (3)

/**
 * Register (RSL) ncsi_bist_status
 *
 * NCSI BIST Register
 */
union bdk_ncsi_bist_status
{
    uint64_t u;
    struct bdk_ncsi_bist_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t status                : 4;  /**< [  3:  0](RO/H) BIST results. Hardware sets a bit to 1 for memory that fails; 0 indicates pass
                                                                 or never run.

                                                                 Internal:
                                                                 \<0\> = ncsi.rx.rx_rsp.rsp_bnk.
                                                                 \<1\> = ncsi.rx.rx_pmac.pmac_bnk.
                                                                 \<2\> = ncsi.rx.rx_mix.mix_bnk.
                                                                 \<3\> = ncsi.tx.tx_mix.mix_bnk. */
#else /* Word 0 - Little Endian */
        uint64_t status                : 4;  /**< [  3:  0](RO/H) BIST results. Hardware sets a bit to 1 for memory that fails; 0 indicates pass
                                                                 or never run.

                                                                 Internal:
                                                                 \<0\> = ncsi.rx.rx_rsp.rsp_bnk.
                                                                 \<1\> = ncsi.rx.rx_pmac.pmac_bnk.
                                                                 \<2\> = ncsi.rx.rx_mix.mix_bnk.
                                                                 \<3\> = ncsi.tx.tx_mix.mix_bnk. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_bist_status_s cn; */
};
typedef union bdk_ncsi_bist_status bdk_ncsi_bist_status_t;

#define BDK_NCSI_BIST_STATUS BDK_NCSI_BIST_STATUS_FUNC()
static inline uint64_t BDK_NCSI_BIST_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_BIST_STATUS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000b00ll;
    __bdk_csr_fatal("NCSI_BIST_STATUS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_BIST_STATUS bdk_ncsi_bist_status_t
#define bustype_BDK_NCSI_BIST_STATUS BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_BIST_STATUS "NCSI_BIST_STATUS"
#define device_bar_BDK_NCSI_BIST_STATUS 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_BIST_STATUS 0
#define arguments_BDK_NCSI_BIST_STATUS -1,-1,-1,-1

/**
 * Register (RSL) ncsi_bmc2cpu_msg
 *
 * NCSI BMC to CPU Message Control Register
 */
union bdk_ncsi_bmc2cpu_msg
{
    uint64_t u;
    struct bdk_ncsi_bmc2cpu_msg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t msg                   : 64; /**< [ 63:  0](R/W) Data to communicate between BMC and CPU. Provides a mechanism for BMC to signal
                                                                 to the CPU. CPU software and BMC firmware must agree on the messaging definition
                                                                 which is beyond the scope of this register definition.

                                                                 When this register is written, NCSI_INT[BMC2CPU] is set. */
#else /* Word 0 - Little Endian */
        uint64_t msg                   : 64; /**< [ 63:  0](R/W) Data to communicate between BMC and CPU. Provides a mechanism for BMC to signal
                                                                 to the CPU. CPU software and BMC firmware must agree on the messaging definition
                                                                 which is beyond the scope of this register definition.

                                                                 When this register is written, NCSI_INT[BMC2CPU] is set. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_bmc2cpu_msg_s cn; */
};
typedef union bdk_ncsi_bmc2cpu_msg bdk_ncsi_bmc2cpu_msg_t;

#define BDK_NCSI_BMC2CPU_MSG BDK_NCSI_BMC2CPU_MSG_FUNC()
static inline uint64_t BDK_NCSI_BMC2CPU_MSG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_BMC2CPU_MSG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000108ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000108ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000108ll;
    __bdk_csr_fatal("NCSI_BMC2CPU_MSG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_BMC2CPU_MSG bdk_ncsi_bmc2cpu_msg_t
#define bustype_BDK_NCSI_BMC2CPU_MSG BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_BMC2CPU_MSG "NCSI_BMC2CPU_MSG"
#define device_bar_BDK_NCSI_BMC2CPU_MSG 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_BMC2CPU_MSG 0
#define arguments_BDK_NCSI_BMC2CPU_MSG -1,-1,-1,-1

/**
 * Register (RSL) ncsi_bp_test
 *
 * INTERNAL: NCSI Backpressure Test Register
 *
 * These registers contians the back pressure diagnotics data.
 */
union bdk_ncsi_bp_test
{
    uint64_t u;
    struct bdk_ncsi_bp_test_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<60\> = Limit RX RSP FIFO traffic. Never limit 100% of the time.
                                                                 \<61\> = Limit RX AEN FIFO traffic. Never limit 100% of the time.
                                                                 \<62\> = Limit RX PMAC FIFO traffic. Never limit 100% of the time.
                                                                 \<63\> = Limit NCSI to CGX transactions. Never limit 100% of the time. */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = Config 3.
                                                                   \<21:20\> = Config 2.
                                                                   \<19:18\> = Config 1.
                                                                   \<17:16\> = Config 0. */
        uint64_t reserved_12_15        : 4;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
        uint64_t reserved_12_15        : 4;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = Config 3.
                                                                   \<21:20\> = Config 2.
                                                                   \<19:18\> = Config 1.
                                                                   \<17:16\> = Config 0. */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<60\> = Limit RX RSP FIFO traffic. Never limit 100% of the time.
                                                                 \<61\> = Limit RX AEN FIFO traffic. Never limit 100% of the time.
                                                                 \<62\> = Limit RX PMAC FIFO traffic. Never limit 100% of the time.
                                                                 \<63\> = Limit NCSI to CGX transactions. Never limit 100% of the time. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_bp_test_s cn; */
};
typedef union bdk_ncsi_bp_test bdk_ncsi_bp_test_t;

#define BDK_NCSI_BP_TEST BDK_NCSI_BP_TEST_FUNC()
static inline uint64_t BDK_NCSI_BP_TEST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_BP_TEST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000c00ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000c00ll;
    __bdk_csr_fatal("NCSI_BP_TEST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_BP_TEST bdk_ncsi_bp_test_t
#define bustype_BDK_NCSI_BP_TEST BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_BP_TEST "NCSI_BP_TEST"
#define device_bar_BDK_NCSI_BP_TEST 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_BP_TEST 0
#define arguments_BDK_NCSI_BP_TEST -1,-1,-1,-1

/**
 * Register (RSL) ncsi_clk_en
 *
 * NCSI Clock Enable Register
 */
union bdk_ncsi_clk_en
{
    uint64_t u;
    struct bdk_ncsi_clk_en_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t clken                 : 1;  /**< [  0:  0](SR/W) Override conditional clocks to always be on. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t clken                 : 1;  /**< [  0:  0](SR/W) Override conditional clocks to always be on. For diagnostic use only. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_clk_en_s cn; */
};
typedef union bdk_ncsi_clk_en bdk_ncsi_clk_en_t;

#define BDK_NCSI_CLK_EN BDK_NCSI_CLK_EN_FUNC()
static inline uint64_t BDK_NCSI_CLK_EN_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_CLK_EN_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000810ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000810ll;
    __bdk_csr_fatal("NCSI_CLK_EN", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_CLK_EN bdk_ncsi_clk_en_t
#define bustype_BDK_NCSI_CLK_EN BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_CLK_EN "NCSI_CLK_EN"
#define device_bar_BDK_NCSI_CLK_EN 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_CLK_EN 0
#define arguments_BDK_NCSI_CLK_EN -1,-1,-1,-1

/**
 * Register (RSL) ncsi_cmd_sw_process#
 *
 * NCSI MCP Command Software Process Registers
 * This register selects between software processing of incoming NCSI commands versus NCSI
 * hardware processing.
 */
union bdk_ncsi_cmd_sw_processx
{
    uint64_t u;
    struct bdk_ncsi_cmd_sw_processx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cmd                   : 64; /**< [ 63:  0](R/W) NCSI_CMD_SW_PROCESS(0) for NCSI commands 0 through 63 (0x3F).
                                                                 NCSI_CMD_SW_PROCESS(1) for NCSI commands 64 (0x40) through 127 (0x7F).

                                                                 Allows the MCP to choose to override the NCSI hardware handling of any of the
                                                                 hardware supported commands by setting the appropriate bits.

                                                                 If a bit is clear, receiving the corresponding command code is handled by
                                                                 hardware if hardware has a decoder for that command; if hardware doesn't know how to
                                                                 handle it, then the command is responded to as "unsupported" as in CNXXXX.

                                                                 If a bit is set the corresponding command code will be sent to the MCP and MCP
                                                                 will generate the response.

                                                                 Bits 0 through 7 should remain 0 as NCSI hardware must process these commands
                                                                 which in turn control hardware channel and package state machines.

                                                                 Resets to 0x0, which allows NCSI hardware to properly return unsupported until
                                                                 the MCP code is loaded. */
#else /* Word 0 - Little Endian */
        uint64_t cmd                   : 64; /**< [ 63:  0](R/W) NCSI_CMD_SW_PROCESS(0) for NCSI commands 0 through 63 (0x3F).
                                                                 NCSI_CMD_SW_PROCESS(1) for NCSI commands 64 (0x40) through 127 (0x7F).

                                                                 Allows the MCP to choose to override the NCSI hardware handling of any of the
                                                                 hardware supported commands by setting the appropriate bits.

                                                                 If a bit is clear, receiving the corresponding command code is handled by
                                                                 hardware if hardware has a decoder for that command; if hardware doesn't know how to
                                                                 handle it, then the command is responded to as "unsupported" as in CNXXXX.

                                                                 If a bit is set the corresponding command code will be sent to the MCP and MCP
                                                                 will generate the response.

                                                                 Bits 0 through 7 should remain 0 as NCSI hardware must process these commands
                                                                 which in turn control hardware channel and package state machines.

                                                                 Resets to 0x0, which allows NCSI hardware to properly return unsupported until
                                                                 the MCP code is loaded. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_cmd_sw_processx_s cn; */
};
typedef union bdk_ncsi_cmd_sw_processx bdk_ncsi_cmd_sw_processx_t;

static inline uint64_t BDK_NCSI_CMD_SW_PROCESSX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_CMD_SW_PROCESSX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=1))
        return 0x87e00b000620ll + 8ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x87e00b000620ll + 8ll * ((a) & 0x1);
    __bdk_csr_fatal("NCSI_CMD_SW_PROCESSX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_CMD_SW_PROCESSX(a) bdk_ncsi_cmd_sw_processx_t
#define bustype_BDK_NCSI_CMD_SW_PROCESSX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_CMD_SW_PROCESSX(a) "NCSI_CMD_SW_PROCESSX"
#define device_bar_BDK_NCSI_CMD_SW_PROCESSX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_CMD_SW_PROCESSX(a) (a)
#define arguments_BDK_NCSI_CMD_SW_PROCESSX(a) (a),-1,-1,-1

/**
 * Register (RSL) ncsi_config
 *
 * NCSI Configuration Register
 */
union bdk_ncsi_config
{
    uint64_t u;
    struct bdk_ncsi_config_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t pkg_id                : 3;  /**< [  4:  2](R/W/H) Override the NCSI package id
                                                                 which defaults to the global node ID.  MSB must be set to 0
                                                                 for NCSI V1.0 compliance. */
        uint64_t pkg_desel_tx_ch_dis   : 1;  /**< [  1:  1](R/W) This bit controls whether the NCSI will disable the TX_CH upon pkg deselect command.
                                                                 0 = On pkg deselect command, keep TX channel enabled, enabling pass through traffic to
                                                                 BGX.
                                                                 1 = On pkg deselect command, disable TX channel preventing pass through traffic to BGX. */
        uint64_t cam_accept            : 1;  /**< [  0:  0](R/W) Allow or deny SMAC address filter.  Applies to both SMAC filters in the CAM.
                                                                 See NCSI_TX_FRM_SMAC()_CAM for additional details.
                                                                 0 = Reject the packet on SMAC CAM address match.
                                                                 1 = Accept the packet on SMAC CAM address match. */
#else /* Word 0 - Little Endian */
        uint64_t cam_accept            : 1;  /**< [  0:  0](R/W) Allow or deny SMAC address filter.  Applies to both SMAC filters in the CAM.
                                                                 See NCSI_TX_FRM_SMAC()_CAM for additional details.
                                                                 0 = Reject the packet on SMAC CAM address match.
                                                                 1 = Accept the packet on SMAC CAM address match. */
        uint64_t pkg_desel_tx_ch_dis   : 1;  /**< [  1:  1](R/W) This bit controls whether the NCSI will disable the TX_CH upon pkg deselect command.
                                                                 0 = On pkg deselect command, keep TX channel enabled, enabling pass through traffic to
                                                                 BGX.
                                                                 1 = On pkg deselect command, disable TX channel preventing pass through traffic to BGX. */
        uint64_t pkg_id                : 3;  /**< [  4:  2](R/W/H) Override the NCSI package id
                                                                 which defaults to the global node ID.  MSB must be set to 0
                                                                 for NCSI V1.0 compliance. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_config_s cn8; */
    struct bdk_ncsi_config_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t pkg_id                : 3;  /**< [  4:  2](R/W/H) Override the NCSI package id
                                                                 which defaults to the global node ID.  MSB must be set to 0
                                                                 for NCSI V1.0 compliance. */
        uint64_t pkg_desel_tx_ch_dis   : 1;  /**< [  1:  1](R/W) Package deselect channel disable.
                                                                 0 = On pkg deselect command, keep TX channel enabled, enabling pass through traffic to
                                                                 CGX.
                                                                 1 = On pkg deselect command, disable TX channel preventing pass through traffic to CGX. */
        uint64_t cam_accept            : 1;  /**< [  0:  0](R/W) Allow or deny SMAC address filter.  Applies to both SMAC filters in the CAM.
                                                                 See NCSI_TX_FRM_SMAC()_CAM for additional details.
                                                                 0 = Reject the packet on SMAC CAM address match.
                                                                 1 = Accept the packet on SMAC CAM address match. */
#else /* Word 0 - Little Endian */
        uint64_t cam_accept            : 1;  /**< [  0:  0](R/W) Allow or deny SMAC address filter.  Applies to both SMAC filters in the CAM.
                                                                 See NCSI_TX_FRM_SMAC()_CAM for additional details.
                                                                 0 = Reject the packet on SMAC CAM address match.
                                                                 1 = Accept the packet on SMAC CAM address match. */
        uint64_t pkg_desel_tx_ch_dis   : 1;  /**< [  1:  1](R/W) Package deselect channel disable.
                                                                 0 = On pkg deselect command, keep TX channel enabled, enabling pass through traffic to
                                                                 CGX.
                                                                 1 = On pkg deselect command, disable TX channel preventing pass through traffic to CGX. */
        uint64_t pkg_id                : 3;  /**< [  4:  2](R/W/H) Override the NCSI package id
                                                                 which defaults to the global node ID.  MSB must be set to 0
                                                                 for NCSI V1.0 compliance. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_ncsi_config bdk_ncsi_config_t;

#define BDK_NCSI_CONFIG BDK_NCSI_CONFIG_FUNC()
static inline uint64_t BDK_NCSI_CONFIG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_CONFIG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000110ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000110ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000110ll;
    __bdk_csr_fatal("NCSI_CONFIG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_CONFIG bdk_ncsi_config_t
#define bustype_BDK_NCSI_CONFIG BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_CONFIG "NCSI_CONFIG"
#define device_bar_BDK_NCSI_CONFIG 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_CONFIG 0
#define arguments_BDK_NCSI_CONFIG -1,-1,-1,-1

/**
 * Register (RSL) ncsi_const
 *
 * NCSI Constant Register
 * This register contains constant for software discovery.
 */
union bdk_ncsi_const
{
    uint64_t u;
    struct bdk_ncsi_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_const_s cn; */
};
typedef union bdk_ncsi_const bdk_ncsi_const_t;

#define BDK_NCSI_CONST BDK_NCSI_CONST_FUNC()
static inline uint64_t BDK_NCSI_CONST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_CONST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000b08ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000b08ll;
    __bdk_csr_fatal("NCSI_CONST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_CONST bdk_ncsi_const_t
#define bustype_BDK_NCSI_CONST BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_CONST "NCSI_CONST"
#define device_bar_BDK_NCSI_CONST 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_CONST 0
#define arguments_BDK_NCSI_CONST -1,-1,-1,-1

/**
 * Register (RSL) ncsi_cpu2bmc_msg
 *
 * NCSI CPU to BMC Message Control Register
 */
union bdk_ncsi_cpu2bmc_msg
{
    uint64_t u;
    struct bdk_ncsi_cpu2bmc_msg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t msg                   : 64; /**< [ 63:  0](R/W) Data to communicate between CPU and BMC. Provides a mechanism for CPU to signal
                                                                 to the BMC. CPU software and BMC firmware must agree on the messaging definition
                                                                 which is beyond the scope of this register definition. */
#else /* Word 0 - Little Endian */
        uint64_t msg                   : 64; /**< [ 63:  0](R/W) Data to communicate between CPU and BMC. Provides a mechanism for CPU to signal
                                                                 to the BMC. CPU software and BMC firmware must agree on the messaging definition
                                                                 which is beyond the scope of this register definition. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_cpu2bmc_msg_s cn; */
};
typedef union bdk_ncsi_cpu2bmc_msg bdk_ncsi_cpu2bmc_msg_t;

#define BDK_NCSI_CPU2BMC_MSG BDK_NCSI_CPU2BMC_MSG_FUNC()
static inline uint64_t BDK_NCSI_CPU2BMC_MSG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_CPU2BMC_MSG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000100ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000100ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000100ll;
    __bdk_csr_fatal("NCSI_CPU2BMC_MSG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_CPU2BMC_MSG bdk_ncsi_cpu2bmc_msg_t
#define bustype_BDK_NCSI_CPU2BMC_MSG BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_CPU2BMC_MSG "NCSI_CPU2BMC_MSG"
#define device_bar_BDK_NCSI_CPU2BMC_MSG 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_CPU2BMC_MSG 0
#define arguments_BDK_NCSI_CPU2BMC_MSG -1,-1,-1,-1

/**
 * Register (RSL) ncsi_csclk_active_pc
 *
 * NCSI Conditional Clock Counter Register
 * This register counts Conditional Clock Cycles.
 */
union bdk_ncsi_csclk_active_pc
{
    uint64_t u;
    struct bdk_ncsi_csclk_active_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of conditinal clock cycles since reset. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of conditinal clock cycles since reset. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_csclk_active_pc_s cn; */
};
typedef union bdk_ncsi_csclk_active_pc bdk_ncsi_csclk_active_pc_t;

#define BDK_NCSI_CSCLK_ACTIVE_PC BDK_NCSI_CSCLK_ACTIVE_PC_FUNC()
static inline uint64_t BDK_NCSI_CSCLK_ACTIVE_PC_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_CSCLK_ACTIVE_PC_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000b20ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000b20ll;
    __bdk_csr_fatal("NCSI_CSCLK_ACTIVE_PC", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_CSCLK_ACTIVE_PC bdk_ncsi_csclk_active_pc_t
#define bustype_BDK_NCSI_CSCLK_ACTIVE_PC BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_CSCLK_ACTIVE_PC "NCSI_CSCLK_ACTIVE_PC"
#define device_bar_BDK_NCSI_CSCLK_ACTIVE_PC 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_CSCLK_ACTIVE_PC 0
#define arguments_BDK_NCSI_CSCLK_ACTIVE_PC -1,-1,-1,-1

/**
 * Register (RSL) ncsi_eco
 *
 * INTERNAL: NCSI ECO Registers
 *
 * This register contains eco registers.
 */
union bdk_ncsi_eco
{
    uint64_t u;
    struct bdk_ncsi_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_ro                : 16; /**< [ 31: 16](RO) Reserved for ECO usage. */
        uint64_t eco_rw                : 16; /**< [ 15:  0](R/W) Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 16; /**< [ 15:  0](R/W) Reserved for ECO usage. */
        uint64_t eco_ro                : 16; /**< [ 31: 16](RO) Reserved for ECO usage. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_eco_s cn; */
};
typedef union bdk_ncsi_eco bdk_ncsi_eco_t;

#define BDK_NCSI_ECO BDK_NCSI_ECO_FUNC()
static inline uint64_t BDK_NCSI_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_ECO_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000b10ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000b10ll;
    __bdk_csr_fatal("NCSI_ECO", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_ECO bdk_ncsi_eco_t
#define bustype_BDK_NCSI_ECO BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_ECO "NCSI_ECO"
#define device_bar_BDK_NCSI_ECO 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_ECO 0
#define arguments_BDK_NCSI_ECO -1,-1,-1,-1

/**
 * Register (RSL) ncsi_int
 *
 * NCSI Memory Interrupt Register
 */
union bdk_ncsi_int
{
    uint64_t u;
    struct bdk_ncsi_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t sw_cmd_to             : 1;  /**< [ 21: 21](R/W1C/H) Software command timeout. See NCSI_SW_TO_VALUE[TO_VALUE]. */
        uint64_t rx_aen_overfl         : 1;  /**< [ 20: 20](R/W1C/H) RX AEN FIFO overflow. */
        uint64_t reserved_18_19        : 2;
        uint64_t cmd_pkt_avail         : 1;  /**< [ 17: 17](R/W1C/H) Indicates to the MCP that a command has arrived the NCSI_MCP_CMD() registers and is ready to
                                                                 be processed. */
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1C/H) Underflow of RX RMII FIFO.  FIFO drained on a non-packet boundary. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1C/H) Messaging interrupt set whenever NCSI_BMC2CPU_MSG is written by the BMC. */
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1C/H) RX RSP FIFO overflow. */
        uint64_t rx_rsp_sbe            : 1;  /**< [ 13: 13](R/W1C/H) RX RSP FIFO single-bit error. */
        uint64_t rx_rsp_dbe            : 1;  /**< [ 12: 12](R/W1C/H) RX RSP FIFO double-bit error. */
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1C/H) Underflow through RX PMAC path.  FIFO drained on a non-packet boundary */
        uint64_t rx_pmac_sbe           : 1;  /**< [ 10: 10](R/W1C/H) RX PMAC FIFO single-bit error. */
        uint64_t rx_pmac_dbe           : 1;  /**< [  9:  9](R/W1C/H) RX PMAC FIFO double-bit error. */
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1C/H) TX MIX FIFO overflow. */
        uint64_t tx_mix_sbe            : 1;  /**< [  7:  7](R/W1C/H) TX MIX FIFO single-bit error. */
        uint64_t tx_mix_dbe            : 1;  /**< [  6:  6](R/W1C/H) TX MIX FIFO double-bit error. */
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1C/H) Frame received without a proper L2 header needed for NCSI command detection. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1C/H) Interframe gap violation. Does not necessarily indicate a failure. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1C/H) Bad preamble/protocol error. Checks that the frame begins with a valid PREAMBLE sequence. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1C/H) NCSI command received with FCS/CRC error. Frame was received with FCS/CRC error. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1C/H) Pass through received FCS/CRC error. Frame was received with FCS/CRC error.
                                                                 FCSERR indication takes precedence over JABBER error. */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1C/H) System-length error. Frame was received with length \> sys_length. A jabber error
                                                                 indicates that a packet was received from RMII interface which is longer than the maximum
                                                                 allowed packet as defined by the system. NCSI truncates the packet at the JABBER count+1
                                                                 bytes. */
#else /* Word 0 - Little Endian */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1C/H) System-length error. Frame was received with length \> sys_length. A jabber error
                                                                 indicates that a packet was received from RMII interface which is longer than the maximum
                                                                 allowed packet as defined by the system. NCSI truncates the packet at the JABBER count+1
                                                                 bytes. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1C/H) Pass through received FCS/CRC error. Frame was received with FCS/CRC error.
                                                                 FCSERR indication takes precedence over JABBER error. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1C/H) NCSI command received with FCS/CRC error. Frame was received with FCS/CRC error. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1C/H) Bad preamble/protocol error. Checks that the frame begins with a valid PREAMBLE sequence. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1C/H) Interframe gap violation. Does not necessarily indicate a failure. */
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1C/H) Frame received without a proper L2 header needed for NCSI command detection. */
        uint64_t tx_mix_dbe            : 1;  /**< [  6:  6](R/W1C/H) TX MIX FIFO double-bit error. */
        uint64_t tx_mix_sbe            : 1;  /**< [  7:  7](R/W1C/H) TX MIX FIFO single-bit error. */
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1C/H) TX MIX FIFO overflow. */
        uint64_t rx_pmac_dbe           : 1;  /**< [  9:  9](R/W1C/H) RX PMAC FIFO double-bit error. */
        uint64_t rx_pmac_sbe           : 1;  /**< [ 10: 10](R/W1C/H) RX PMAC FIFO single-bit error. */
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1C/H) Underflow through RX PMAC path.  FIFO drained on a non-packet boundary */
        uint64_t rx_rsp_dbe            : 1;  /**< [ 12: 12](R/W1C/H) RX RSP FIFO double-bit error. */
        uint64_t rx_rsp_sbe            : 1;  /**< [ 13: 13](R/W1C/H) RX RSP FIFO single-bit error. */
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1C/H) RX RSP FIFO overflow. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1C/H) Messaging interrupt set whenever NCSI_BMC2CPU_MSG is written by the BMC. */
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1C/H) Underflow of RX RMII FIFO.  FIFO drained on a non-packet boundary. */
        uint64_t cmd_pkt_avail         : 1;  /**< [ 17: 17](R/W1C/H) Indicates to the MCP that a command has arrived the NCSI_MCP_CMD() registers and is ready to
                                                                 be processed. */
        uint64_t reserved_18_19        : 2;
        uint64_t rx_aen_overfl         : 1;  /**< [ 20: 20](R/W1C/H) RX AEN FIFO overflow. */
        uint64_t sw_cmd_to             : 1;  /**< [ 21: 21](R/W1C/H) Software command timeout. See NCSI_SW_TO_VALUE[TO_VALUE]. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    struct bdk_ncsi_int_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1C/H) Underflow of RX RMII FIFO.  FIFO drained on a non-packet boundary. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1C/H) Messaging interrupt set whenever NCSI_BMC2CPU_MSG is written by the BMC. */
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1C/H) RX RSP FIFO overflow. */
        uint64_t rx_rsp_sbe            : 1;  /**< [ 13: 13](R/W1C/H) RX RSP FIFO single-bit error. */
        uint64_t rx_rsp_dbe            : 1;  /**< [ 12: 12](R/W1C/H) RX RSP FIFO double-bit error. */
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1C/H) Underflow through RX PMAC path.  FIFO drained on a non-packet boundary */
        uint64_t rx_pmac_sbe           : 1;  /**< [ 10: 10](R/W1C/H) RX PMAC FIFO single-bit error. */
        uint64_t rx_pmac_dbe           : 1;  /**< [  9:  9](R/W1C/H) RX PMAC FIFO double-bit error. */
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1C/H) TX MIX FIFO overflow. */
        uint64_t tx_mix_sbe            : 1;  /**< [  7:  7](R/W1C/H) TX MIX FIFO single-bit error. */
        uint64_t tx_mix_dbe            : 1;  /**< [  6:  6](R/W1C/H) TX MIX FIFO double-bit error. */
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1C/H) Frame received without a proper L2 header needed for NCSI command detection. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1C/H) Interframe gap violation. Does not necessarily indicate a failure. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1C/H) Bad preamble/protocol error. Checks that the frame begins with a valid PREAMBLE sequence. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1C/H) NCSI command received with FCS/CRC error. Frame was received with FCS/CRC error. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1C/H) Pass through received FCS/CRC error. Frame was received with FCS/CRC error.
                                                                 FCSERR indication takes precedence over JABBER error. */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1C/H) System-length error. Frame was received with length \> sys_length. A jabber error
                                                                 indicates that a packet was received from RMII interface which is longer than the maximum
                                                                 allowed packet as defined by the system. NCSI truncates the packet at the JABBER count+1
                                                                 bytes. */
#else /* Word 0 - Little Endian */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1C/H) System-length error. Frame was received with length \> sys_length. A jabber error
                                                                 indicates that a packet was received from RMII interface which is longer than the maximum
                                                                 allowed packet as defined by the system. NCSI truncates the packet at the JABBER count+1
                                                                 bytes. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1C/H) Pass through received FCS/CRC error. Frame was received with FCS/CRC error.
                                                                 FCSERR indication takes precedence over JABBER error. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1C/H) NCSI command received with FCS/CRC error. Frame was received with FCS/CRC error. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1C/H) Bad preamble/protocol error. Checks that the frame begins with a valid PREAMBLE sequence. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1C/H) Interframe gap violation. Does not necessarily indicate a failure. */
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1C/H) Frame received without a proper L2 header needed for NCSI command detection. */
        uint64_t tx_mix_dbe            : 1;  /**< [  6:  6](R/W1C/H) TX MIX FIFO double-bit error. */
        uint64_t tx_mix_sbe            : 1;  /**< [  7:  7](R/W1C/H) TX MIX FIFO single-bit error. */
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1C/H) TX MIX FIFO overflow. */
        uint64_t rx_pmac_dbe           : 1;  /**< [  9:  9](R/W1C/H) RX PMAC FIFO double-bit error. */
        uint64_t rx_pmac_sbe           : 1;  /**< [ 10: 10](R/W1C/H) RX PMAC FIFO single-bit error. */
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1C/H) Underflow through RX PMAC path.  FIFO drained on a non-packet boundary */
        uint64_t rx_rsp_dbe            : 1;  /**< [ 12: 12](R/W1C/H) RX RSP FIFO double-bit error. */
        uint64_t rx_rsp_sbe            : 1;  /**< [ 13: 13](R/W1C/H) RX RSP FIFO single-bit error. */
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1C/H) RX RSP FIFO overflow. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1C/H) Messaging interrupt set whenever NCSI_BMC2CPU_MSG is written by the BMC. */
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1C/H) Underflow of RX RMII FIFO.  FIFO drained on a non-packet boundary. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_ncsi_int_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t sw_cmd_to             : 1;  /**< [ 21: 21](R/W1C/H) Software command timeout. See NCSI_SW_TO_VALUE[TO_VALUE]. */
        uint64_t rx_aen_overfl         : 1;  /**< [ 20: 20](R/W1C/H) RX AEN FIFO overflow. */
        uint64_t reserved_18_19        : 2;
        uint64_t cmd_pkt_avail         : 1;  /**< [ 17: 17](R/W1C/H) Indicates to the MCP that a command has arrived the NCSI_MCP_CMD() registers and is ready to
                                                                 be processed. */
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1C/H) Underflow of RX RMII FIFO.  FIFO drained on a non-packet boundary. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1C/H) Messaging interrupt set whenever NCSI_BMC2CPU_MSG is written by the BMC. */
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1C/H) RX RSP FIFO overflow. */
        uint64_t reserved_12_13        : 2;
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1C/H) Underflow through RX PMAC path.  FIFO drained on a non-packet boundary */
        uint64_t reserved_9_10         : 2;
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1C/H) TX MIX FIFO overflow. */
        uint64_t reserved_6_7          : 2;
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1C/H) Frame received without a proper L2 header needed for NCSI command detection. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1C/H) Interframe gap violation. Does not necessarily indicate a failure. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1C/H) Bad preamble/protocol error. Checks that the frame begins with a valid PREAMBLE sequence. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1C/H) NCSI command received with FCS/CRC error. Frame was received with FCS/CRC error. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1C/H) Pass through received FCS/CRC error. Frame was received with FCS/CRC error.
                                                                 FCSERR indication takes precedence over JABBER error. */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1C/H) System-length error. Frame was received with length \> sys_length. A jabber error
                                                                 indicates that a packet was received from RMII interface which is longer than the maximum
                                                                 allowed packet as defined by the system. NCSI truncates the packet at the JABBER count+1
                                                                 bytes. */
#else /* Word 0 - Little Endian */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1C/H) System-length error. Frame was received with length \> sys_length. A jabber error
                                                                 indicates that a packet was received from RMII interface which is longer than the maximum
                                                                 allowed packet as defined by the system. NCSI truncates the packet at the JABBER count+1
                                                                 bytes. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1C/H) Pass through received FCS/CRC error. Frame was received with FCS/CRC error.
                                                                 FCSERR indication takes precedence over JABBER error. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1C/H) NCSI command received with FCS/CRC error. Frame was received with FCS/CRC error. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1C/H) Bad preamble/protocol error. Checks that the frame begins with a valid PREAMBLE sequence. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1C/H) Interframe gap violation. Does not necessarily indicate a failure. */
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1C/H) Frame received without a proper L2 header needed for NCSI command detection. */
        uint64_t reserved_6_7          : 2;
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1C/H) TX MIX FIFO overflow. */
        uint64_t reserved_9_10         : 2;
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1C/H) Underflow through RX PMAC path.  FIFO drained on a non-packet boundary */
        uint64_t reserved_12_13        : 2;
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1C/H) RX RSP FIFO overflow. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1C/H) Messaging interrupt set whenever NCSI_BMC2CPU_MSG is written by the BMC. */
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1C/H) Underflow of RX RMII FIFO.  FIFO drained on a non-packet boundary. */
        uint64_t cmd_pkt_avail         : 1;  /**< [ 17: 17](R/W1C/H) Indicates to the MCP that a command has arrived the NCSI_MCP_CMD() registers and is ready to
                                                                 be processed. */
        uint64_t reserved_18_19        : 2;
        uint64_t rx_aen_overfl         : 1;  /**< [ 20: 20](R/W1C/H) RX AEN FIFO overflow. */
        uint64_t sw_cmd_to             : 1;  /**< [ 21: 21](R/W1C/H) Software command timeout. See NCSI_SW_TO_VALUE[TO_VALUE]. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_ncsi_int bdk_ncsi_int_t;

#define BDK_NCSI_INT BDK_NCSI_INT_FUNC()
static inline uint64_t BDK_NCSI_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000000ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000000ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000000ll;
    __bdk_csr_fatal("NCSI_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_INT bdk_ncsi_int_t
#define bustype_BDK_NCSI_INT BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_INT "NCSI_INT"
#define device_bar_BDK_NCSI_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_INT 0
#define arguments_BDK_NCSI_INT -1,-1,-1,-1

/**
 * Register (RSL) ncsi_int_ena_w1c
 *
 * NCSI Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_ncsi_int_ena_w1c
{
    uint64_t u;
    struct bdk_ncsi_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t sw_cmd_to             : 1;  /**< [ 21: 21](R/W1C/H) Reads or clears enable for NCSI_INT[SW_CMD_TO]. */
        uint64_t rx_aen_overfl         : 1;  /**< [ 20: 20](R/W1C/H) Reads or clears enable for NCSI_INT[RX_AEN_OVERFL]. */
        uint64_t reserved_18_19        : 2;
        uint64_t cmd_pkt_avail         : 1;  /**< [ 17: 17](R/W1C/H) Reads or clears enable for NCSI_INT[CMD_PKT_AVAIL]. */
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1C/H) Reads or clears enable for NCSI_INT[RX_RMII_UNDERFL]. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1C/H) Reads or clears enable for NCSI_INT[BMC2CPU]. */
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1C/H) Reads or clears enable for NCSI_INT[RX_RSP_OVERFL]. */
        uint64_t rx_rsp_sbe            : 1;  /**< [ 13: 13](R/W1C/H) Reads or clears enable for NCSI_INT[RX_RSP_SBE]. */
        uint64_t rx_rsp_dbe            : 1;  /**< [ 12: 12](R/W1C/H) Reads or clears enable for NCSI_INT[RX_RSP_DBE]. */
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for NCSI_INT[RX_PMAC_UNDERFL]. */
        uint64_t rx_pmac_sbe           : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for NCSI_INT[RX_PMAC_SBE]. */
        uint64_t rx_pmac_dbe           : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for NCSI_INT[RX_PMAC_DBE]. */
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for NCSI_INT[TX_MIX_OVERFL]. */
        uint64_t tx_mix_sbe            : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for NCSI_INT[TX_MIX_SBE]. */
        uint64_t tx_mix_dbe            : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for NCSI_INT[TX_MIX_DBE]. */
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for NCSI_INT[RUNTERR]. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for NCSI_INT[IFGERR]. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for NCSI_INT[PCTERR]. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for NCSI_INT[NCP_FCSERR]. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for NCSI_INT[PMAC_FCSERR]. */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for NCSI_INT[JABBER]. */
#else /* Word 0 - Little Endian */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for NCSI_INT[JABBER]. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for NCSI_INT[PMAC_FCSERR]. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for NCSI_INT[NCP_FCSERR]. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for NCSI_INT[PCTERR]. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for NCSI_INT[IFGERR]. */
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for NCSI_INT[RUNTERR]. */
        uint64_t tx_mix_dbe            : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for NCSI_INT[TX_MIX_DBE]. */
        uint64_t tx_mix_sbe            : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for NCSI_INT[TX_MIX_SBE]. */
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for NCSI_INT[TX_MIX_OVERFL]. */
        uint64_t rx_pmac_dbe           : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for NCSI_INT[RX_PMAC_DBE]. */
        uint64_t rx_pmac_sbe           : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for NCSI_INT[RX_PMAC_SBE]. */
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for NCSI_INT[RX_PMAC_UNDERFL]. */
        uint64_t rx_rsp_dbe            : 1;  /**< [ 12: 12](R/W1C/H) Reads or clears enable for NCSI_INT[RX_RSP_DBE]. */
        uint64_t rx_rsp_sbe            : 1;  /**< [ 13: 13](R/W1C/H) Reads or clears enable for NCSI_INT[RX_RSP_SBE]. */
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1C/H) Reads or clears enable for NCSI_INT[RX_RSP_OVERFL]. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1C/H) Reads or clears enable for NCSI_INT[BMC2CPU]. */
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1C/H) Reads or clears enable for NCSI_INT[RX_RMII_UNDERFL]. */
        uint64_t cmd_pkt_avail         : 1;  /**< [ 17: 17](R/W1C/H) Reads or clears enable for NCSI_INT[CMD_PKT_AVAIL]. */
        uint64_t reserved_18_19        : 2;
        uint64_t rx_aen_overfl         : 1;  /**< [ 20: 20](R/W1C/H) Reads or clears enable for NCSI_INT[RX_AEN_OVERFL]. */
        uint64_t sw_cmd_to             : 1;  /**< [ 21: 21](R/W1C/H) Reads or clears enable for NCSI_INT[SW_CMD_TO]. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    struct bdk_ncsi_int_ena_w1c_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1C/H) Reads or clears enable for NCSI_INT[RX_RMII_UNDERFL]. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1C/H) Reads or clears enable for NCSI_INT[BMC2CPU]. */
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1C/H) Reads or clears enable for NCSI_INT[RX_RSP_OVERFL]. */
        uint64_t rx_rsp_sbe            : 1;  /**< [ 13: 13](R/W1C/H) Reads or clears enable for NCSI_INT[RX_RSP_SBE]. */
        uint64_t rx_rsp_dbe            : 1;  /**< [ 12: 12](R/W1C/H) Reads or clears enable for NCSI_INT[RX_RSP_DBE]. */
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for NCSI_INT[RX_PMAC_UNDERFL]. */
        uint64_t rx_pmac_sbe           : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for NCSI_INT[RX_PMAC_SBE]. */
        uint64_t rx_pmac_dbe           : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for NCSI_INT[RX_PMAC_DBE]. */
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for NCSI_INT[TX_MIX_OVERFL]. */
        uint64_t tx_mix_sbe            : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for NCSI_INT[TX_MIX_SBE]. */
        uint64_t tx_mix_dbe            : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for NCSI_INT[TX_MIX_DBE]. */
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for NCSI_INT[RUNTERR]. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for NCSI_INT[IFGERR]. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for NCSI_INT[PCTERR]. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for NCSI_INT[NCP_FCSERR]. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for NCSI_INT[PMAC_FCSERR]. */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for NCSI_INT[JABBER]. */
#else /* Word 0 - Little Endian */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for NCSI_INT[JABBER]. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for NCSI_INT[PMAC_FCSERR]. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for NCSI_INT[NCP_FCSERR]. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for NCSI_INT[PCTERR]. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for NCSI_INT[IFGERR]. */
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for NCSI_INT[RUNTERR]. */
        uint64_t tx_mix_dbe            : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for NCSI_INT[TX_MIX_DBE]. */
        uint64_t tx_mix_sbe            : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for NCSI_INT[TX_MIX_SBE]. */
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for NCSI_INT[TX_MIX_OVERFL]. */
        uint64_t rx_pmac_dbe           : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for NCSI_INT[RX_PMAC_DBE]. */
        uint64_t rx_pmac_sbe           : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for NCSI_INT[RX_PMAC_SBE]. */
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for NCSI_INT[RX_PMAC_UNDERFL]. */
        uint64_t rx_rsp_dbe            : 1;  /**< [ 12: 12](R/W1C/H) Reads or clears enable for NCSI_INT[RX_RSP_DBE]. */
        uint64_t rx_rsp_sbe            : 1;  /**< [ 13: 13](R/W1C/H) Reads or clears enable for NCSI_INT[RX_RSP_SBE]. */
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1C/H) Reads or clears enable for NCSI_INT[RX_RSP_OVERFL]. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1C/H) Reads or clears enable for NCSI_INT[BMC2CPU]. */
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1C/H) Reads or clears enable for NCSI_INT[RX_RMII_UNDERFL]. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_ncsi_int_ena_w1c_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t sw_cmd_to             : 1;  /**< [ 21: 21](R/W1C/H) Reads or clears enable for NCSI_INT[SW_CMD_TO]. */
        uint64_t rx_aen_overfl         : 1;  /**< [ 20: 20](R/W1C/H) Reads or clears enable for NCSI_INT[RX_AEN_OVERFL]. */
        uint64_t reserved_18_19        : 2;
        uint64_t cmd_pkt_avail         : 1;  /**< [ 17: 17](R/W1C/H) Reads or clears enable for NCSI_INT[CMD_PKT_AVAIL]. */
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1C/H) Reads or clears enable for NCSI_INT[RX_RMII_UNDERFL]. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1C/H) Reads or clears enable for NCSI_INT[BMC2CPU]. */
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1C/H) Reads or clears enable for NCSI_INT[RX_RSP_OVERFL]. */
        uint64_t reserved_12_13        : 2;
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for NCSI_INT[RX_PMAC_UNDERFL]. */
        uint64_t reserved_9_10         : 2;
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for NCSI_INT[TX_MIX_OVERFL]. */
        uint64_t reserved_6_7          : 2;
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for NCSI_INT[RUNTERR]. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for NCSI_INT[IFGERR]. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for NCSI_INT[PCTERR]. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for NCSI_INT[NCP_FCSERR]. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for NCSI_INT[PMAC_FCSERR]. */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for NCSI_INT[JABBER]. */
#else /* Word 0 - Little Endian */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for NCSI_INT[JABBER]. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for NCSI_INT[PMAC_FCSERR]. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for NCSI_INT[NCP_FCSERR]. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for NCSI_INT[PCTERR]. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for NCSI_INT[IFGERR]. */
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for NCSI_INT[RUNTERR]. */
        uint64_t reserved_6_7          : 2;
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for NCSI_INT[TX_MIX_OVERFL]. */
        uint64_t reserved_9_10         : 2;
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for NCSI_INT[RX_PMAC_UNDERFL]. */
        uint64_t reserved_12_13        : 2;
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1C/H) Reads or clears enable for NCSI_INT[RX_RSP_OVERFL]. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1C/H) Reads or clears enable for NCSI_INT[BMC2CPU]. */
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1C/H) Reads or clears enable for NCSI_INT[RX_RMII_UNDERFL]. */
        uint64_t cmd_pkt_avail         : 1;  /**< [ 17: 17](R/W1C/H) Reads or clears enable for NCSI_INT[CMD_PKT_AVAIL]. */
        uint64_t reserved_18_19        : 2;
        uint64_t rx_aen_overfl         : 1;  /**< [ 20: 20](R/W1C/H) Reads or clears enable for NCSI_INT[RX_AEN_OVERFL]. */
        uint64_t sw_cmd_to             : 1;  /**< [ 21: 21](R/W1C/H) Reads or clears enable for NCSI_INT[SW_CMD_TO]. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_ncsi_int_ena_w1c bdk_ncsi_int_ena_w1c_t;

#define BDK_NCSI_INT_ENA_W1C BDK_NCSI_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_NCSI_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_INT_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000018ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000018ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000018ll;
    __bdk_csr_fatal("NCSI_INT_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_INT_ENA_W1C bdk_ncsi_int_ena_w1c_t
#define bustype_BDK_NCSI_INT_ENA_W1C BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_INT_ENA_W1C "NCSI_INT_ENA_W1C"
#define device_bar_BDK_NCSI_INT_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_INT_ENA_W1C 0
#define arguments_BDK_NCSI_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (RSL) ncsi_int_ena_w1s
 *
 * NCSI Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_ncsi_int_ena_w1s
{
    uint64_t u;
    struct bdk_ncsi_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t sw_cmd_to             : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets enable for NCSI_INT[SW_CMD_TO]. */
        uint64_t rx_aen_overfl         : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets enable for NCSI_INT[RX_AEN_OVERFL]. */
        uint64_t reserved_18_19        : 2;
        uint64_t cmd_pkt_avail         : 1;  /**< [ 17: 17](R/W1S/H) Reads or sets enable for NCSI_INT[CMD_PKT_AVAIL]. */
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets enable for NCSI_INT[RX_RMII_UNDERFL]. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets enable for NCSI_INT[BMC2CPU]. */
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets enable for NCSI_INT[RX_RSP_OVERFL]. */
        uint64_t rx_rsp_sbe            : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets enable for NCSI_INT[RX_RSP_SBE]. */
        uint64_t rx_rsp_dbe            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets enable for NCSI_INT[RX_RSP_DBE]. */
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for NCSI_INT[RX_PMAC_UNDERFL]. */
        uint64_t rx_pmac_sbe           : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for NCSI_INT[RX_PMAC_SBE]. */
        uint64_t rx_pmac_dbe           : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for NCSI_INT[RX_PMAC_DBE]. */
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for NCSI_INT[TX_MIX_OVERFL]. */
        uint64_t tx_mix_sbe            : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for NCSI_INT[TX_MIX_SBE]. */
        uint64_t tx_mix_dbe            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for NCSI_INT[TX_MIX_DBE]. */
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for NCSI_INT[RUNTERR]. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for NCSI_INT[IFGERR]. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for NCSI_INT[PCTERR]. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for NCSI_INT[NCP_FCSERR]. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for NCSI_INT[PMAC_FCSERR]. */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for NCSI_INT[JABBER]. */
#else /* Word 0 - Little Endian */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for NCSI_INT[JABBER]. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for NCSI_INT[PMAC_FCSERR]. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for NCSI_INT[NCP_FCSERR]. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for NCSI_INT[PCTERR]. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for NCSI_INT[IFGERR]. */
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for NCSI_INT[RUNTERR]. */
        uint64_t tx_mix_dbe            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for NCSI_INT[TX_MIX_DBE]. */
        uint64_t tx_mix_sbe            : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for NCSI_INT[TX_MIX_SBE]. */
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for NCSI_INT[TX_MIX_OVERFL]. */
        uint64_t rx_pmac_dbe           : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for NCSI_INT[RX_PMAC_DBE]. */
        uint64_t rx_pmac_sbe           : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for NCSI_INT[RX_PMAC_SBE]. */
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for NCSI_INT[RX_PMAC_UNDERFL]. */
        uint64_t rx_rsp_dbe            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets enable for NCSI_INT[RX_RSP_DBE]. */
        uint64_t rx_rsp_sbe            : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets enable for NCSI_INT[RX_RSP_SBE]. */
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets enable for NCSI_INT[RX_RSP_OVERFL]. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets enable for NCSI_INT[BMC2CPU]. */
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets enable for NCSI_INT[RX_RMII_UNDERFL]. */
        uint64_t cmd_pkt_avail         : 1;  /**< [ 17: 17](R/W1S/H) Reads or sets enable for NCSI_INT[CMD_PKT_AVAIL]. */
        uint64_t reserved_18_19        : 2;
        uint64_t rx_aen_overfl         : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets enable for NCSI_INT[RX_AEN_OVERFL]. */
        uint64_t sw_cmd_to             : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets enable for NCSI_INT[SW_CMD_TO]. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    struct bdk_ncsi_int_ena_w1s_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets enable for NCSI_INT[RX_RMII_UNDERFL]. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets enable for NCSI_INT[BMC2CPU]. */
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets enable for NCSI_INT[RX_RSP_OVERFL]. */
        uint64_t rx_rsp_sbe            : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets enable for NCSI_INT[RX_RSP_SBE]. */
        uint64_t rx_rsp_dbe            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets enable for NCSI_INT[RX_RSP_DBE]. */
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for NCSI_INT[RX_PMAC_UNDERFL]. */
        uint64_t rx_pmac_sbe           : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for NCSI_INT[RX_PMAC_SBE]. */
        uint64_t rx_pmac_dbe           : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for NCSI_INT[RX_PMAC_DBE]. */
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for NCSI_INT[TX_MIX_OVERFL]. */
        uint64_t tx_mix_sbe            : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for NCSI_INT[TX_MIX_SBE]. */
        uint64_t tx_mix_dbe            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for NCSI_INT[TX_MIX_DBE]. */
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for NCSI_INT[RUNTERR]. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for NCSI_INT[IFGERR]. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for NCSI_INT[PCTERR]. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for NCSI_INT[NCP_FCSERR]. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for NCSI_INT[PMAC_FCSERR]. */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for NCSI_INT[JABBER]. */
#else /* Word 0 - Little Endian */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for NCSI_INT[JABBER]. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for NCSI_INT[PMAC_FCSERR]. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for NCSI_INT[NCP_FCSERR]. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for NCSI_INT[PCTERR]. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for NCSI_INT[IFGERR]. */
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for NCSI_INT[RUNTERR]. */
        uint64_t tx_mix_dbe            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for NCSI_INT[TX_MIX_DBE]. */
        uint64_t tx_mix_sbe            : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for NCSI_INT[TX_MIX_SBE]. */
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for NCSI_INT[TX_MIX_OVERFL]. */
        uint64_t rx_pmac_dbe           : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for NCSI_INT[RX_PMAC_DBE]. */
        uint64_t rx_pmac_sbe           : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for NCSI_INT[RX_PMAC_SBE]. */
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for NCSI_INT[RX_PMAC_UNDERFL]. */
        uint64_t rx_rsp_dbe            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets enable for NCSI_INT[RX_RSP_DBE]. */
        uint64_t rx_rsp_sbe            : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets enable for NCSI_INT[RX_RSP_SBE]. */
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets enable for NCSI_INT[RX_RSP_OVERFL]. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets enable for NCSI_INT[BMC2CPU]. */
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets enable for NCSI_INT[RX_RMII_UNDERFL]. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_ncsi_int_ena_w1s_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t sw_cmd_to             : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets enable for NCSI_INT[SW_CMD_TO]. */
        uint64_t rx_aen_overfl         : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets enable for NCSI_INT[RX_AEN_OVERFL]. */
        uint64_t reserved_18_19        : 2;
        uint64_t cmd_pkt_avail         : 1;  /**< [ 17: 17](R/W1S/H) Reads or sets enable for NCSI_INT[CMD_PKT_AVAIL]. */
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets enable for NCSI_INT[RX_RMII_UNDERFL]. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets enable for NCSI_INT[BMC2CPU]. */
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets enable for NCSI_INT[RX_RSP_OVERFL]. */
        uint64_t reserved_12_13        : 2;
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for NCSI_INT[RX_PMAC_UNDERFL]. */
        uint64_t reserved_9_10         : 2;
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for NCSI_INT[TX_MIX_OVERFL]. */
        uint64_t reserved_6_7          : 2;
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for NCSI_INT[RUNTERR]. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for NCSI_INT[IFGERR]. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for NCSI_INT[PCTERR]. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for NCSI_INT[NCP_FCSERR]. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for NCSI_INT[PMAC_FCSERR]. */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for NCSI_INT[JABBER]. */
#else /* Word 0 - Little Endian */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for NCSI_INT[JABBER]. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for NCSI_INT[PMAC_FCSERR]. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for NCSI_INT[NCP_FCSERR]. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for NCSI_INT[PCTERR]. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for NCSI_INT[IFGERR]. */
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for NCSI_INT[RUNTERR]. */
        uint64_t reserved_6_7          : 2;
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for NCSI_INT[TX_MIX_OVERFL]. */
        uint64_t reserved_9_10         : 2;
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for NCSI_INT[RX_PMAC_UNDERFL]. */
        uint64_t reserved_12_13        : 2;
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets enable for NCSI_INT[RX_RSP_OVERFL]. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets enable for NCSI_INT[BMC2CPU]. */
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets enable for NCSI_INT[RX_RMII_UNDERFL]. */
        uint64_t cmd_pkt_avail         : 1;  /**< [ 17: 17](R/W1S/H) Reads or sets enable for NCSI_INT[CMD_PKT_AVAIL]. */
        uint64_t reserved_18_19        : 2;
        uint64_t rx_aen_overfl         : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets enable for NCSI_INT[RX_AEN_OVERFL]. */
        uint64_t sw_cmd_to             : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets enable for NCSI_INT[SW_CMD_TO]. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_ncsi_int_ena_w1s bdk_ncsi_int_ena_w1s_t;

#define BDK_NCSI_INT_ENA_W1S BDK_NCSI_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_NCSI_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_INT_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000010ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000010ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000010ll;
    __bdk_csr_fatal("NCSI_INT_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_INT_ENA_W1S bdk_ncsi_int_ena_w1s_t
#define bustype_BDK_NCSI_INT_ENA_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_INT_ENA_W1S "NCSI_INT_ENA_W1S"
#define device_bar_BDK_NCSI_INT_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_INT_ENA_W1S 0
#define arguments_BDK_NCSI_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (RSL) ncsi_int_w1s
 *
 * NCSI Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_ncsi_int_w1s
{
    uint64_t u;
    struct bdk_ncsi_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t sw_cmd_to             : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets NCSI_INT[SW_CMD_TO]. */
        uint64_t rx_aen_overfl         : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets NCSI_INT[RX_AEN_OVERFL]. */
        uint64_t reserved_18_19        : 2;
        uint64_t cmd_pkt_avail         : 1;  /**< [ 17: 17](R/W1S/H) Reads or sets NCSI_INT[CMD_PKT_AVAIL]. */
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets NCSI_INT[RX_RMII_UNDERFL]. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets NCSI_INT[BMC2CPU]. */
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets NCSI_INT[RX_RSP_OVERFL]. */
        uint64_t rx_rsp_sbe            : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets NCSI_INT[RX_RSP_SBE]. */
        uint64_t rx_rsp_dbe            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets NCSI_INT[RX_RSP_DBE]. */
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets NCSI_INT[RX_PMAC_UNDERFL]. */
        uint64_t rx_pmac_sbe           : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets NCSI_INT[RX_PMAC_SBE]. */
        uint64_t rx_pmac_dbe           : 1;  /**< [  9:  9](R/W1S/H) Reads or sets NCSI_INT[RX_PMAC_DBE]. */
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1S/H) Reads or sets NCSI_INT[TX_MIX_OVERFL]. */
        uint64_t tx_mix_sbe            : 1;  /**< [  7:  7](R/W1S/H) Reads or sets NCSI_INT[TX_MIX_SBE]. */
        uint64_t tx_mix_dbe            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets NCSI_INT[TX_MIX_DBE]. */
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1S/H) Reads or sets NCSI_INT[RUNTERR]. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets NCSI_INT[IFGERR]. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets NCSI_INT[PCTERR]. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets NCSI_INT[NCP_FCSERR]. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1S/H) Reads or sets NCSI_INT[PMAC_FCSERR]. */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets NCSI_INT[JABBER]. */
#else /* Word 0 - Little Endian */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets NCSI_INT[JABBER]. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1S/H) Reads or sets NCSI_INT[PMAC_FCSERR]. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets NCSI_INT[NCP_FCSERR]. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets NCSI_INT[PCTERR]. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets NCSI_INT[IFGERR]. */
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1S/H) Reads or sets NCSI_INT[RUNTERR]. */
        uint64_t tx_mix_dbe            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets NCSI_INT[TX_MIX_DBE]. */
        uint64_t tx_mix_sbe            : 1;  /**< [  7:  7](R/W1S/H) Reads or sets NCSI_INT[TX_MIX_SBE]. */
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1S/H) Reads or sets NCSI_INT[TX_MIX_OVERFL]. */
        uint64_t rx_pmac_dbe           : 1;  /**< [  9:  9](R/W1S/H) Reads or sets NCSI_INT[RX_PMAC_DBE]. */
        uint64_t rx_pmac_sbe           : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets NCSI_INT[RX_PMAC_SBE]. */
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets NCSI_INT[RX_PMAC_UNDERFL]. */
        uint64_t rx_rsp_dbe            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets NCSI_INT[RX_RSP_DBE]. */
        uint64_t rx_rsp_sbe            : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets NCSI_INT[RX_RSP_SBE]. */
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets NCSI_INT[RX_RSP_OVERFL]. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets NCSI_INT[BMC2CPU]. */
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets NCSI_INT[RX_RMII_UNDERFL]. */
        uint64_t cmd_pkt_avail         : 1;  /**< [ 17: 17](R/W1S/H) Reads or sets NCSI_INT[CMD_PKT_AVAIL]. */
        uint64_t reserved_18_19        : 2;
        uint64_t rx_aen_overfl         : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets NCSI_INT[RX_AEN_OVERFL]. */
        uint64_t sw_cmd_to             : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets NCSI_INT[SW_CMD_TO]. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    struct bdk_ncsi_int_w1s_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets NCSI_INT[RX_RMII_UNDERFL]. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets NCSI_INT[BMC2CPU]. */
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets NCSI_INT[RX_RSP_OVERFL]. */
        uint64_t rx_rsp_sbe            : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets NCSI_INT[RX_RSP_SBE]. */
        uint64_t rx_rsp_dbe            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets NCSI_INT[RX_RSP_DBE]. */
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets NCSI_INT[RX_PMAC_UNDERFL]. */
        uint64_t rx_pmac_sbe           : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets NCSI_INT[RX_PMAC_SBE]. */
        uint64_t rx_pmac_dbe           : 1;  /**< [  9:  9](R/W1S/H) Reads or sets NCSI_INT[RX_PMAC_DBE]. */
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1S/H) Reads or sets NCSI_INT[TX_MIX_OVERFL]. */
        uint64_t tx_mix_sbe            : 1;  /**< [  7:  7](R/W1S/H) Reads or sets NCSI_INT[TX_MIX_SBE]. */
        uint64_t tx_mix_dbe            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets NCSI_INT[TX_MIX_DBE]. */
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1S/H) Reads or sets NCSI_INT[RUNTERR]. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets NCSI_INT[IFGERR]. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets NCSI_INT[PCTERR]. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets NCSI_INT[NCP_FCSERR]. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1S/H) Reads or sets NCSI_INT[PMAC_FCSERR]. */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets NCSI_INT[JABBER]. */
#else /* Word 0 - Little Endian */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets NCSI_INT[JABBER]. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1S/H) Reads or sets NCSI_INT[PMAC_FCSERR]. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets NCSI_INT[NCP_FCSERR]. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets NCSI_INT[PCTERR]. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets NCSI_INT[IFGERR]. */
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1S/H) Reads or sets NCSI_INT[RUNTERR]. */
        uint64_t tx_mix_dbe            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets NCSI_INT[TX_MIX_DBE]. */
        uint64_t tx_mix_sbe            : 1;  /**< [  7:  7](R/W1S/H) Reads or sets NCSI_INT[TX_MIX_SBE]. */
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1S/H) Reads or sets NCSI_INT[TX_MIX_OVERFL]. */
        uint64_t rx_pmac_dbe           : 1;  /**< [  9:  9](R/W1S/H) Reads or sets NCSI_INT[RX_PMAC_DBE]. */
        uint64_t rx_pmac_sbe           : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets NCSI_INT[RX_PMAC_SBE]. */
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets NCSI_INT[RX_PMAC_UNDERFL]. */
        uint64_t rx_rsp_dbe            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets NCSI_INT[RX_RSP_DBE]. */
        uint64_t rx_rsp_sbe            : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets NCSI_INT[RX_RSP_SBE]. */
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets NCSI_INT[RX_RSP_OVERFL]. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets NCSI_INT[BMC2CPU]. */
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets NCSI_INT[RX_RMII_UNDERFL]. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_ncsi_int_w1s_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t sw_cmd_to             : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets NCSI_INT[SW_CMD_TO]. */
        uint64_t rx_aen_overfl         : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets NCSI_INT[RX_AEN_OVERFL]. */
        uint64_t reserved_18_19        : 2;
        uint64_t cmd_pkt_avail         : 1;  /**< [ 17: 17](R/W1S/H) Reads or sets NCSI_INT[CMD_PKT_AVAIL]. */
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets NCSI_INT[RX_RMII_UNDERFL]. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets NCSI_INT[BMC2CPU]. */
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets NCSI_INT[RX_RSP_OVERFL]. */
        uint64_t reserved_12_13        : 2;
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets NCSI_INT[RX_PMAC_UNDERFL]. */
        uint64_t reserved_9_10         : 2;
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1S/H) Reads or sets NCSI_INT[TX_MIX_OVERFL]. */
        uint64_t reserved_6_7          : 2;
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1S/H) Reads or sets NCSI_INT[RUNTERR]. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets NCSI_INT[IFGERR]. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets NCSI_INT[PCTERR]. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets NCSI_INT[NCP_FCSERR]. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1S/H) Reads or sets NCSI_INT[PMAC_FCSERR]. */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets NCSI_INT[JABBER]. */
#else /* Word 0 - Little Endian */
        uint64_t jabber                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets NCSI_INT[JABBER]. */
        uint64_t pmac_fcserr           : 1;  /**< [  1:  1](R/W1S/H) Reads or sets NCSI_INT[PMAC_FCSERR]. */
        uint64_t ncp_fcserr            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets NCSI_INT[NCP_FCSERR]. */
        uint64_t pcterr                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets NCSI_INT[PCTERR]. */
        uint64_t ifgerr                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets NCSI_INT[IFGERR]. */
        uint64_t runterr               : 1;  /**< [  5:  5](R/W1S/H) Reads or sets NCSI_INT[RUNTERR]. */
        uint64_t reserved_6_7          : 2;
        uint64_t tx_mix_overfl         : 1;  /**< [  8:  8](R/W1S/H) Reads or sets NCSI_INT[TX_MIX_OVERFL]. */
        uint64_t reserved_9_10         : 2;
        uint64_t rx_pmac_underfl       : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets NCSI_INT[RX_PMAC_UNDERFL]. */
        uint64_t reserved_12_13        : 2;
        uint64_t rx_rsp_overfl         : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets NCSI_INT[RX_RSP_OVERFL]. */
        uint64_t bmc2cpu               : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets NCSI_INT[BMC2CPU]. */
        uint64_t rx_rmii_underfl       : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets NCSI_INT[RX_RMII_UNDERFL]. */
        uint64_t cmd_pkt_avail         : 1;  /**< [ 17: 17](R/W1S/H) Reads or sets NCSI_INT[CMD_PKT_AVAIL]. */
        uint64_t reserved_18_19        : 2;
        uint64_t rx_aen_overfl         : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets NCSI_INT[RX_AEN_OVERFL]. */
        uint64_t sw_cmd_to             : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets NCSI_INT[SW_CMD_TO]. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_ncsi_int_w1s bdk_ncsi_int_w1s_t;

#define BDK_NCSI_INT_W1S BDK_NCSI_INT_W1S_FUNC()
static inline uint64_t BDK_NCSI_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000008ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000008ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000008ll;
    __bdk_csr_fatal("NCSI_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_INT_W1S bdk_ncsi_int_w1s_t
#define bustype_BDK_NCSI_INT_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_INT_W1S "NCSI_INT_W1S"
#define device_bar_BDK_NCSI_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_INT_W1S 0
#define arguments_BDK_NCSI_INT_W1S -1,-1,-1,-1

/**
 * Register (RSL) ncsi_mcp_aen#
 *
 * NCSI MCP AEN Register
 * This register holds the event notification data from the MCP that indicates
 * the NCSI formulate an AEN packet to report link status, host network driver status
 * and config required request.
 */
union bdk_ncsi_mcp_aenx
{
    uint64_t u;
    struct bdk_ncsi_mcp_aenx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pkt                   : 64; /**< [ 63:  0](R/W) This register contains packet information for the NCSI AEN command that will be
                                                                 sent to the BMC. Entry 0 contains the first eight bytes of the L2 header and
                                                                 bits 63:56 contain the LSB.  Software is responsible for padding to the
                                                                 min Ethernet size of 64 bytes in the case of smaller than minimum responses and
                                                                 for creating a valid CRC-32b FCS and placing in the last four bytes to be played
                                                                 out.

                                                                 Software should only set one of the field types corresponding to
                                                                 NCSI_MCP_AEN_CTL[AEN_RDY] since NCSI AEN commands cannot report simultaneous
                                                                 events. */
#else /* Word 0 - Little Endian */
        uint64_t pkt                   : 64; /**< [ 63:  0](R/W) This register contains packet information for the NCSI AEN command that will be
                                                                 sent to the BMC. Entry 0 contains the first eight bytes of the L2 header and
                                                                 bits 63:56 contain the LSB.  Software is responsible for padding to the
                                                                 min Ethernet size of 64 bytes in the case of smaller than minimum responses and
                                                                 for creating a valid CRC-32b FCS and placing in the last four bytes to be played
                                                                 out.

                                                                 Software should only set one of the field types corresponding to
                                                                 NCSI_MCP_AEN_CTL[AEN_RDY] since NCSI AEN commands cannot report simultaneous
                                                                 events. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_mcp_aenx_s cn; */
};
typedef union bdk_ncsi_mcp_aenx bdk_ncsi_mcp_aenx_t;

static inline uint64_t BDK_NCSI_MCP_AENX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_MCP_AENX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=7))
        return 0x87e00b000540ll + 8ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=7))
        return 0x87e00b000540ll + 8ll * ((a) & 0x7);
    __bdk_csr_fatal("NCSI_MCP_AENX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_MCP_AENX(a) bdk_ncsi_mcp_aenx_t
#define bustype_BDK_NCSI_MCP_AENX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_MCP_AENX(a) "NCSI_MCP_AENX"
#define device_bar_BDK_NCSI_MCP_AENX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_MCP_AENX(a) (a)
#define arguments_BDK_NCSI_MCP_AENX(a) (a),-1,-1,-1

/**
 * Register (RSL) ncsi_mcp_aen_ctl
 *
 * NCSI RX AEN CTL Register
 * This register holds the handshake signals from the MCP.
 */
union bdk_ncsi_mcp_aen_ctl
{
    uint64_t u;
    struct bdk_ncsi_mcp_aen_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t aen_rdy               : 1;  /**< [  0:  0](R/W/H) MCP sets to indicate
                                                                 that NCSI must formulate an AEN packet to report link status, host network driver status,
                                                                 and config required request.  NCSI will clear the register once the command is sent.
                                                                 Software must only set [AEN_RDY] if the BMC has sent the AEN enable command, a command
                                                                 which
                                                                 is only processed by software through NCSI_MCP_CMD(). */
#else /* Word 0 - Little Endian */
        uint64_t aen_rdy               : 1;  /**< [  0:  0](R/W/H) MCP sets to indicate
                                                                 that NCSI must formulate an AEN packet to report link status, host network driver status,
                                                                 and config required request.  NCSI will clear the register once the command is sent.
                                                                 Software must only set [AEN_RDY] if the BMC has sent the AEN enable command, a command
                                                                 which
                                                                 is only processed by software through NCSI_MCP_CMD(). */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_mcp_aen_ctl_s cn; */
};
typedef union bdk_ncsi_mcp_aen_ctl bdk_ncsi_mcp_aen_ctl_t;

#define BDK_NCSI_MCP_AEN_CTL BDK_NCSI_MCP_AEN_CTL_FUNC()
static inline uint64_t BDK_NCSI_MCP_AEN_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_MCP_AEN_CTL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000530ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000530ll;
    __bdk_csr_fatal("NCSI_MCP_AEN_CTL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_MCP_AEN_CTL bdk_ncsi_mcp_aen_ctl_t
#define bustype_BDK_NCSI_MCP_AEN_CTL BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_MCP_AEN_CTL "NCSI_MCP_AEN_CTL"
#define device_bar_BDK_NCSI_MCP_AEN_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_MCP_AEN_CTL 0
#define arguments_BDK_NCSI_MCP_AEN_CTL -1,-1,-1,-1

/**
 * Register (RSL) ncsi_mcp_cmd#
 *
 * NCSI MCP Command Registers
 * These registers contain the payload of the incoming NCSI command.
 */
union bdk_ncsi_mcp_cmdx
{
    uint64_t u;
    struct bdk_ncsi_mcp_cmdx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pkt                   : 64; /**< [ 63:  0](RO/H) When a command arrives that is due for MCP processing as dictated by
                                                                 NCSI_CMD_SW_PROCESS(), this register holds the NCSI command packet containing the
                                                                 L2 header, NCSI header and the NCSI command payload. In addition an interrupt,
                                                                 NCSI_INT[CMD_PKT_AVAIL] is set to notify the MCP the command is ready for
                                                                 processing.

                                                                 See NCSI specification Table 18.

                                                                 _ NCSI_MCP_CMD(0) for L2 header; format bytes 0..7,
                                                                 _ NCSI_MCP_CMD(1) for L2 and NCSI control packet header; format bytes 8..15.
                                                                 _ NCSI_MCP_CMD(2) for NCSI control packet header and payload data; format bytes 16..23.
                                                                 _ NCSI_MCP_CMD(3) for NCSI control packet header and payload data; format bytes 24..31.
                                                                 _ NCSI_MCP_CMD(4) for NCSI control packet payload data; format bytes 32..39.
                                                                 _ NCSI_MCP_CMD(5) for NCSI control packet payload data; format bytes 40..47.
                                                                 _ NCSI_MCP_CMD(6) for NCSI control packet payload data; format bytes 48..55.
                                                                 _ NCSI_MCP_CMD(7) for NCSI control packet payload data; format bytes 56..63. */
#else /* Word 0 - Little Endian */
        uint64_t pkt                   : 64; /**< [ 63:  0](RO/H) When a command arrives that is due for MCP processing as dictated by
                                                                 NCSI_CMD_SW_PROCESS(), this register holds the NCSI command packet containing the
                                                                 L2 header, NCSI header and the NCSI command payload. In addition an interrupt,
                                                                 NCSI_INT[CMD_PKT_AVAIL] is set to notify the MCP the command is ready for
                                                                 processing.

                                                                 See NCSI specification Table 18.

                                                                 _ NCSI_MCP_CMD(0) for L2 header; format bytes 0..7,
                                                                 _ NCSI_MCP_CMD(1) for L2 and NCSI control packet header; format bytes 8..15.
                                                                 _ NCSI_MCP_CMD(2) for NCSI control packet header and payload data; format bytes 16..23.
                                                                 _ NCSI_MCP_CMD(3) for NCSI control packet header and payload data; format bytes 24..31.
                                                                 _ NCSI_MCP_CMD(4) for NCSI control packet payload data; format bytes 32..39.
                                                                 _ NCSI_MCP_CMD(5) for NCSI control packet payload data; format bytes 40..47.
                                                                 _ NCSI_MCP_CMD(6) for NCSI control packet payload data; format bytes 48..55.
                                                                 _ NCSI_MCP_CMD(7) for NCSI control packet payload data; format bytes 56..63. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_mcp_cmdx_s cn; */
};
typedef union bdk_ncsi_mcp_cmdx bdk_ncsi_mcp_cmdx_t;

static inline uint64_t BDK_NCSI_MCP_CMDX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_MCP_CMDX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=7))
        return 0x87e00b000680ll + 8ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=7))
        return 0x87e00b000680ll + 8ll * ((a) & 0x7);
    __bdk_csr_fatal("NCSI_MCP_CMDX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_MCP_CMDX(a) bdk_ncsi_mcp_cmdx_t
#define bustype_BDK_NCSI_MCP_CMDX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_MCP_CMDX(a) "NCSI_MCP_CMDX"
#define device_bar_BDK_NCSI_MCP_CMDX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_MCP_CMDX(a) (a)
#define arguments_BDK_NCSI_MCP_CMDX(a) (a),-1,-1,-1

/**
 * Register (RSL) ncsi_mcp_rsp#
 *
 * NCSI MCP Response Register
 */
union bdk_ncsi_mcp_rspx
{
    uint64_t u;
    struct bdk_ncsi_mcp_rspx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pkt                   : 64; /**< [ 63:  0](R/W) When an NCSI command is processed by the MCP, this register holds the NCSI
                                                                 response for the NCSI packet that will be sent to the BMC. Entry 0 contains
                                                                 the first eight bytes of the L2 header. Software is responsible for padding to the
                                                                 min Ethernet size of 64 bytes in the case of smaller than minimum responses and
                                                                 for creating a valid CRC-32b FCS and placing in the last four bytes to be played
                                                                 out. */
#else /* Word 0 - Little Endian */
        uint64_t pkt                   : 64; /**< [ 63:  0](R/W) When an NCSI command is processed by the MCP, this register holds the NCSI
                                                                 response for the NCSI packet that will be sent to the BMC. Entry 0 contains
                                                                 the first eight bytes of the L2 header. Software is responsible for padding to the
                                                                 min Ethernet size of 64 bytes in the case of smaller than minimum responses and
                                                                 for creating a valid CRC-32b FCS and placing in the last four bytes to be played
                                                                 out. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_mcp_rspx_s cn; */
};
typedef union bdk_ncsi_mcp_rspx bdk_ncsi_mcp_rspx_t;

static inline uint64_t BDK_NCSI_MCP_RSPX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_MCP_RSPX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=25))
        return 0x87e00b000700ll + 8ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=25))
        return 0x87e00b000700ll + 8ll * ((a) & 0x1f);
    __bdk_csr_fatal("NCSI_MCP_RSPX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_MCP_RSPX(a) bdk_ncsi_mcp_rspx_t
#define bustype_BDK_NCSI_MCP_RSPX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_MCP_RSPX(a) "NCSI_MCP_RSPX"
#define device_bar_BDK_NCSI_MCP_RSPX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_MCP_RSPX(a) (a)
#define arguments_BDK_NCSI_MCP_RSPX(a) (a),-1,-1,-1

/**
 * Register (RSL) ncsi_mcp_rsp_ctl
 *
 * NCSI MCP Response Control Register
 */
union bdk_ncsi_mcp_rsp_ctl
{
    uint64_t u;
    struct bdk_ncsi_mcp_rsp_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t rsp_len               : 5;  /**< [ 12:  8](R/W) Number of NCSI_MCP_RSP() entries the NCSI hardware should use to formulate a response
                                                                 packet. Valid on [RSP_RDY]. */
        uint64_t reserved_1_7          : 7;
        uint64_t rsp_rdy               : 1;  /**< [  0:  0](R/W/H) Set by software to indicate
                                                                 the NCSI hardware formulate a response packet with the contents
                                                                 of NCSI_MCP_RSP().  NCSI will clear this field once the response is sent.
                                                                 [RSP_RDY] should only be set by software in response to receiving an NCSI CMD via
                                                                 NCSI_MCP_CMD() directed to software by NCSI_CMD_SW_PROCESS(). */
#else /* Word 0 - Little Endian */
        uint64_t rsp_rdy               : 1;  /**< [  0:  0](R/W/H) Set by software to indicate
                                                                 the NCSI hardware formulate a response packet with the contents
                                                                 of NCSI_MCP_RSP().  NCSI will clear this field once the response is sent.
                                                                 [RSP_RDY] should only be set by software in response to receiving an NCSI CMD via
                                                                 NCSI_MCP_CMD() directed to software by NCSI_CMD_SW_PROCESS(). */
        uint64_t reserved_1_7          : 7;
        uint64_t rsp_len               : 5;  /**< [ 12:  8](R/W) Number of NCSI_MCP_RSP() entries the NCSI hardware should use to formulate a response
                                                                 packet. Valid on [RSP_RDY]. */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_mcp_rsp_ctl_s cn; */
};
typedef union bdk_ncsi_mcp_rsp_ctl bdk_ncsi_mcp_rsp_ctl_t;

#define BDK_NCSI_MCP_RSP_CTL BDK_NCSI_MCP_RSP_CTL_FUNC()
static inline uint64_t BDK_NCSI_MCP_RSP_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_MCP_RSP_CTL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b0006f0ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b0006f0ll;
    __bdk_csr_fatal("NCSI_MCP_RSP_CTL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_MCP_RSP_CTL bdk_ncsi_mcp_rsp_ctl_t
#define bustype_BDK_NCSI_MCP_RSP_CTL BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_MCP_RSP_CTL "NCSI_MCP_RSP_CTL"
#define device_bar_BDK_NCSI_MCP_RSP_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_MCP_RSP_CTL 0
#define arguments_BDK_NCSI_MCP_RSP_CTL -1,-1,-1,-1

/**
 * Register (RSL) ncsi_mem_ctrl
 *
 * NCSI Memory Control Register
 */
union bdk_ncsi_mem_ctrl
{
    uint64_t u;
    struct bdk_ncsi_mem_ctrl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t rx_rsp_synd           : 2;  /**< [  8:  7](R/W) Syndrome to flip and generate single-bit/double-bit for RX RSP FIFO. */
        uint64_t rx_rsp_cor_dis        : 1;  /**< [  6:  6](R/W) ECC-correction disable for the RX RSP FIFO. */
        uint64_t rx_pmac_synd          : 2;  /**< [  5:  4](R/W) Syndrome to flip and generate single-bit/double-bit for RX PMAC FIFO. */
        uint64_t rx_pmac_cor_dis       : 1;  /**< [  3:  3](R/W) ECC-correction disable for the RX PMAC FIFO. */
        uint64_t tx_mix_synd           : 2;  /**< [  2:  1](R/W) Syndrome to flip and generate single-bit/double-bit for TX MIX FIFO. */
        uint64_t tx_mix_cor_dis        : 1;  /**< [  0:  0](R/W) ECC-correction disable for the TX MIX FIFO. */
#else /* Word 0 - Little Endian */
        uint64_t tx_mix_cor_dis        : 1;  /**< [  0:  0](R/W) ECC-correction disable for the TX MIX FIFO. */
        uint64_t tx_mix_synd           : 2;  /**< [  2:  1](R/W) Syndrome to flip and generate single-bit/double-bit for TX MIX FIFO. */
        uint64_t rx_pmac_cor_dis       : 1;  /**< [  3:  3](R/W) ECC-correction disable for the RX PMAC FIFO. */
        uint64_t rx_pmac_synd          : 2;  /**< [  5:  4](R/W) Syndrome to flip and generate single-bit/double-bit for RX PMAC FIFO. */
        uint64_t rx_rsp_cor_dis        : 1;  /**< [  6:  6](R/W) ECC-correction disable for the RX RSP FIFO. */
        uint64_t rx_rsp_synd           : 2;  /**< [  8:  7](R/W) Syndrome to flip and generate single-bit/double-bit for RX RSP FIFO. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_mem_ctrl_s cn; */
};
typedef union bdk_ncsi_mem_ctrl bdk_ncsi_mem_ctrl_t;

#define BDK_NCSI_MEM_CTRL BDK_NCSI_MEM_CTRL_FUNC()
static inline uint64_t BDK_NCSI_MEM_CTRL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_MEM_CTRL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000118ll;
    __bdk_csr_fatal("NCSI_MEM_CTRL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_MEM_CTRL bdk_ncsi_mem_ctrl_t
#define bustype_BDK_NCSI_MEM_CTRL BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_MEM_CTRL "NCSI_MEM_CTRL"
#define device_bar_BDK_NCSI_MEM_CTRL 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_MEM_CTRL 0
#define arguments_BDK_NCSI_MEM_CTRL -1,-1,-1,-1

/**
 * Register (RSL) ncsi_msix_pba#
 *
 * NCSI MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table; the bit number is indexed by the NCSI_INT_VEC_E enumeration.
 */
union bdk_ncsi_msix_pbax
{
    uint64_t u;
    struct bdk_ncsi_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated NCSI_MSIX_VEC()_CTL, enumerated by NCSI_INT_VEC_E.
                                                                 Bits that have no associated NCSI_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated NCSI_MSIX_VEC()_CTL, enumerated by NCSI_INT_VEC_E.
                                                                 Bits that have no associated NCSI_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_msix_pbax_s cn; */
};
typedef union bdk_ncsi_msix_pbax bdk_ncsi_msix_pbax_t;

static inline uint64_t BDK_NCSI_MSIX_PBAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_MSIX_PBAX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x87e00bff0000ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a==0))
        return 0x87e00bff0000ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a==0))
        return 0x87e00bff0000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("NCSI_MSIX_PBAX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_MSIX_PBAX(a) bdk_ncsi_msix_pbax_t
#define bustype_BDK_NCSI_MSIX_PBAX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_MSIX_PBAX(a) "NCSI_MSIX_PBAX"
#define device_bar_BDK_NCSI_MSIX_PBAX(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_NCSI_MSIX_PBAX(a) (a)
#define arguments_BDK_NCSI_MSIX_PBAX(a) (a),-1,-1,-1

/**
 * Register (RSL) ncsi_msix_vec#_addr
 *
 * NCSI MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the NCSI_INT_VEC_E enumeration.
 */
union bdk_ncsi_msix_vecx_addr
{
    uint64_t u;
    struct bdk_ncsi_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's NCSI_MSIX_VEC()_ADDR, NCSI_MSIX_VEC()_CTL, and corresponding
                                                                 bit of NCSI_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_NCSI_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC])
                                                                 is set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's NCSI_MSIX_VEC()_ADDR, NCSI_MSIX_VEC()_CTL, and corresponding
                                                                 bit of NCSI_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_NCSI_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC])
                                                                 is set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    struct bdk_ncsi_msix_vecx_addr_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's NCSI_MSIX_VEC()_ADDR, NCSI_MSIX_VEC()_CTL, and corresponding
                                                                 bit of NCSI_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_NCSI_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC])
                                                                 is set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's NCSI_MSIX_VEC()_ADDR, NCSI_MSIX_VEC()_CTL, and corresponding
                                                                 bit of NCSI_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_NCSI_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC])
                                                                 is set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_ncsi_msix_vecx_addr_s cn9; */
    /* struct bdk_ncsi_msix_vecx_addr_s cn96xxp1; */
    struct bdk_ncsi_msix_vecx_addr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 The vector's IOVA is sent to the SMMU as nonsecure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1).

                                                                 1 = This vector's NCSI_MSIX_VEC()_ADDR, NCSI_MSIX_VEC()_CTL, and corresponding
                                                                 bit of NCSI_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.
                                                                 The vector's IOVA is sent to the SMMU as secure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1 or
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1).

                                                                 If PCCPF_NCSI_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC])
                                                                 is set, all vectors are secure and function as if [SECVEC] was set.

                                                                 Also note the following:
                                                                 * When PCCPF_XXX_VSEC_SCTL[MSIX_SEC_EN]=1, all secure vectors (including secure
                                                                 VF vectors) will act as if PCCPF/PCCVF_XXX_MSIX_CAP_HDR[MSIXEN]=1,
                                                                 PCCPF/PCCVF_XXX_MSIX_CAP_HDR[FUNM]=0 and PCCPF/PCCVF_XXX_CMD[ME]=1.
                                                                 * When PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1, all secure vectors (including
                                                                 secure VF vectors) are considered physical, regardless of
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 The vector's IOVA is sent to the SMMU as nonsecure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1).

                                                                 1 = This vector's NCSI_MSIX_VEC()_ADDR, NCSI_MSIX_VEC()_CTL, and corresponding
                                                                 bit of NCSI_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.
                                                                 The vector's IOVA is sent to the SMMU as secure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1 or
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1).

                                                                 If PCCPF_NCSI_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC])
                                                                 is set, all vectors are secure and function as if [SECVEC] was set.

                                                                 Also note the following:
                                                                 * When PCCPF_XXX_VSEC_SCTL[MSIX_SEC_EN]=1, all secure vectors (including secure
                                                                 VF vectors) will act as if PCCPF/PCCVF_XXX_MSIX_CAP_HDR[MSIXEN]=1,
                                                                 PCCPF/PCCVF_XXX_MSIX_CAP_HDR[FUNM]=0 and PCCPF/PCCVF_XXX_CMD[ME]=1.
                                                                 * When PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1, all secure vectors (including
                                                                 secure VF vectors) are considered physical, regardless of
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_ncsi_msix_vecx_addr_cn96xxp3 cn98xx; */
};
typedef union bdk_ncsi_msix_vecx_addr bdk_ncsi_msix_vecx_addr_t;

static inline uint64_t BDK_NCSI_MSIX_VECX_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_MSIX_VECX_ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x87e00bf00000ll + 0x10ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a==0))
        return 0x87e00bf00000ll + 0x10ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a==0))
        return 0x87e00bf00000ll + 0x10ll * ((a) & 0x0);
    __bdk_csr_fatal("NCSI_MSIX_VECX_ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_MSIX_VECX_ADDR(a) bdk_ncsi_msix_vecx_addr_t
#define bustype_BDK_NCSI_MSIX_VECX_ADDR(a) BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_MSIX_VECX_ADDR(a) "NCSI_MSIX_VECX_ADDR"
#define device_bar_BDK_NCSI_MSIX_VECX_ADDR(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_NCSI_MSIX_VECX_ADDR(a) (a)
#define arguments_BDK_NCSI_MSIX_VECX_ADDR(a) (a),-1,-1,-1

/**
 * Register (RSL) ncsi_msix_vec#_ctl
 *
 * NCSI MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the NCSI_INT_VEC_E enumeration.
 */
union bdk_ncsi_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_ncsi_msix_vecx_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts are sent to this vector. */
        uint64_t data                  : 32; /**< [ 31:  0](R/W) Data to use for MSI-X delivery of this vector. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 32; /**< [ 31:  0](R/W) Data to use for MSI-X delivery of this vector. */
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts are sent to this vector. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    struct bdk_ncsi_msix_vecx_ctl_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts are sent to this vector. */
        uint64_t reserved_20_31        : 12;
        uint64_t data                  : 20; /**< [ 19:  0](R/W) Data to use for MSI-X delivery of this vector. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 20; /**< [ 19:  0](R/W) Data to use for MSI-X delivery of this vector. */
        uint64_t reserved_20_31        : 12;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts are sent to this vector. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_ncsi_msix_vecx_ctl_s cn9; */
};
typedef union bdk_ncsi_msix_vecx_ctl bdk_ncsi_msix_vecx_ctl_t;

static inline uint64_t BDK_NCSI_MSIX_VECX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_MSIX_VECX_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x87e00bf00008ll + 0x10ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a==0))
        return 0x87e00bf00008ll + 0x10ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a==0))
        return 0x87e00bf00008ll + 0x10ll * ((a) & 0x0);
    __bdk_csr_fatal("NCSI_MSIX_VECX_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_MSIX_VECX_CTL(a) bdk_ncsi_msix_vecx_ctl_t
#define bustype_BDK_NCSI_MSIX_VECX_CTL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_MSIX_VECX_CTL(a) "NCSI_MSIX_VECX_CTL"
#define device_bar_BDK_NCSI_MSIX_VECX_CTL(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_NCSI_MSIX_VECX_CTL(a) (a)
#define arguments_BDK_NCSI_MSIX_VECX_CTL(a) (a),-1,-1,-1

/**
 * Register (RSL) ncsi_rx_frm_ctl
 *
 * NCSI RX Frame Control Registers
 * This register should be set in coordination with CGX registers that control similar
 * parameters.
 * If NCSI is configured to prepend preamble and postpend FCS, then these should be
 * stripped
 * by CGX.  If NCSI is configured not to prepend preamble and postpend FCS, then CGX should not
 * be stripping these values.
 * Practically speaking, preamble and FCS should be set together.
 */
union bdk_ncsi_rx_frm_ctl
{
    uint64_t u;
    struct bdk_ncsi_rx_frm_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t fcs                   : 1;  /**< [  2:  2](R/W) Append the Ethernet FCS on each pass through packet going to RMII. */
        uint64_t pad                   : 1;  /**< [  1:  1](R/W) Append PAD bytes such that minimum-sized pass through packet is sent over RMII. FCS will
                                                                 be appended in this case by default. */
        uint64_t preamble              : 1;  /**< [  0:  0](R/W) Prepend the Ethernet preamble on each pass through transfer over RMII */
#else /* Word 0 - Little Endian */
        uint64_t preamble              : 1;  /**< [  0:  0](R/W) Prepend the Ethernet preamble on each pass through transfer over RMII */
        uint64_t pad                   : 1;  /**< [  1:  1](R/W) Append PAD bytes such that minimum-sized pass through packet is sent over RMII. FCS will
                                                                 be appended in this case by default. */
        uint64_t fcs                   : 1;  /**< [  2:  2](R/W) Append the Ethernet FCS on each pass through packet going to RMII. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_rx_frm_ctl_s cn; */
};
typedef union bdk_ncsi_rx_frm_ctl bdk_ncsi_rx_frm_ctl_t;

#define BDK_NCSI_RX_FRM_CTL BDK_NCSI_RX_FRM_CTL_FUNC()
static inline uint64_t BDK_NCSI_RX_FRM_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_RX_FRM_CTL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000508ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000508ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000508ll;
    __bdk_csr_fatal("NCSI_RX_FRM_CTL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_RX_FRM_CTL bdk_ncsi_rx_frm_ctl_t
#define bustype_BDK_NCSI_RX_FRM_CTL BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_RX_FRM_CTL "NCSI_RX_FRM_CTL"
#define device_bar_BDK_NCSI_RX_FRM_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_RX_FRM_CTL 0
#define arguments_BDK_NCSI_RX_FRM_CTL -1,-1,-1,-1

/**
 * Register (RSL) ncsi_rx_ifg
 *
 * NCSI RX Interframe-Gap Cycles Registers
 * Interframe gap between packets going out on the RMII interface.
 * For IEEE 802.3 compatibility, IFG1 must be in the range of 1-11, IFG2 must be in the range
 * of 1-11, and the IFG1 + IFG2 sum must be 12 resulting in 96 bit times.
 * For all other systems, IFG1 and IFG2 can be any value in the range of 1-15, allowing for a
 * total possible IFG sum of 2 minimum and 30 maximum.
 */
union bdk_ncsi_rx_ifg
{
    uint64_t u;
    struct bdk_ncsi_rx_ifg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t ifg2                  : 4;  /**< [  7:  4](R/W) Remainder of interFrameGap timing, equal to interFrameGap - IFG1 (in IFG2 * 8 bits). A
                                                                 value of 4 sets an IFG2 of 32 bit times appropriate for 802.3 compliance. */
        uint64_t ifg1                  : 4;  /**< [  3:  0](R/W) First portion of interFrameGap timing, (in IFG1 * 8 bits). A value of 8 sets an IFG1 of 64
                                                                 bit times appropriate for 802.3 compliance. */
#else /* Word 0 - Little Endian */
        uint64_t ifg1                  : 4;  /**< [  3:  0](R/W) First portion of interFrameGap timing, (in IFG1 * 8 bits). A value of 8 sets an IFG1 of 64
                                                                 bit times appropriate for 802.3 compliance. */
        uint64_t ifg2                  : 4;  /**< [  7:  4](R/W) Remainder of interFrameGap timing, equal to interFrameGap - IFG1 (in IFG2 * 8 bits). A
                                                                 value of 4 sets an IFG2 of 32 bit times appropriate for 802.3 compliance. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_rx_ifg_s cn; */
};
typedef union bdk_ncsi_rx_ifg bdk_ncsi_rx_ifg_t;

#define BDK_NCSI_RX_IFG BDK_NCSI_RX_IFG_FUNC()
static inline uint64_t BDK_NCSI_RX_IFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_RX_IFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000518ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000518ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000518ll;
    __bdk_csr_fatal("NCSI_RX_IFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_RX_IFG bdk_ncsi_rx_ifg_t
#define bustype_BDK_NCSI_RX_IFG BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_RX_IFG "NCSI_RX_IFG"
#define device_bar_BDK_NCSI_RX_IFG 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_RX_IFG 0
#define arguments_BDK_NCSI_RX_IFG -1,-1,-1,-1

/**
 * Register (RSL) ncsi_rx_mfg
 *
 * NCSI RX Manufacturer ID Register
 * This register sets the manufacturer ID.
 */
union bdk_ncsi_rx_mfg
{
    uint64_t u;
    struct bdk_ncsi_rx_mfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t id                    : 32; /**< [ 31:  0](R/W) Manufacturer ID to place in the NCSI OEM and GET_ID response packets.
                                                                 The value should not conflict with the existing vendor enterprise numbers in the
                                                                 IANA database. For commands on the TX side, the incoming OEM command mfg id entry
                                                                 will go unchecked since the package and channel fields of the NCSI header are
                                                                 sufficient to address the network controller. */
#else /* Word 0 - Little Endian */
        uint64_t id                    : 32; /**< [ 31:  0](R/W) Manufacturer ID to place in the NCSI OEM and GET_ID response packets.
                                                                 The value should not conflict with the existing vendor enterprise numbers in the
                                                                 IANA database. For commands on the TX side, the incoming OEM command mfg id entry
                                                                 will go unchecked since the package and channel fields of the NCSI header are
                                                                 sufficient to address the network controller. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_rx_mfg_s cn; */
};
typedef union bdk_ncsi_rx_mfg bdk_ncsi_rx_mfg_t;

#define BDK_NCSI_RX_MFG BDK_NCSI_RX_MFG_FUNC()
static inline uint64_t BDK_NCSI_RX_MFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_RX_MFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000520ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000520ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000520ll;
    __bdk_csr_fatal("NCSI_RX_MFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_RX_MFG bdk_ncsi_rx_mfg_t
#define bustype_BDK_NCSI_RX_MFG BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_RX_MFG "NCSI_RX_MFG"
#define device_bar_BDK_NCSI_RX_MFG 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_RX_MFG 0
#define arguments_BDK_NCSI_RX_MFG -1,-1,-1,-1

/**
 * Register (RSL) ncsi_rx_min_pkt
 *
 * NCSI RX Minimum-Size-Packet Registers
 */
union bdk_ncsi_rx_min_pkt
{
    uint64_t u;
    struct bdk_ncsi_rx_min_pkt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t min_size              : 6;  /**< [  5:  0](R/W) Minimum frame size in bytes before the FCS is applied for packets going to the RMII
                                                                 interface and does not include Preamble/SFD. Padding is only appended when
                                                                 NCSI_RX_FRM_CTL[PAD] set.
                                                                 The reset value pads to 60 bytes. */
#else /* Word 0 - Little Endian */
        uint64_t min_size              : 6;  /**< [  5:  0](R/W) Minimum frame size in bytes before the FCS is applied for packets going to the RMII
                                                                 interface and does not include Preamble/SFD. Padding is only appended when
                                                                 NCSI_RX_FRM_CTL[PAD] set.
                                                                 The reset value pads to 60 bytes. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_rx_min_pkt_s cn; */
};
typedef union bdk_ncsi_rx_min_pkt bdk_ncsi_rx_min_pkt_t;

#define BDK_NCSI_RX_MIN_PKT BDK_NCSI_RX_MIN_PKT_FUNC()
static inline uint64_t BDK_NCSI_RX_MIN_PKT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_RX_MIN_PKT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000510ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000510ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000510ll;
    __bdk_csr_fatal("NCSI_RX_MIN_PKT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_RX_MIN_PKT bdk_ncsi_rx_min_pkt_t
#define bustype_BDK_NCSI_RX_MIN_PKT BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_RX_MIN_PKT "NCSI_RX_MIN_PKT"
#define device_bar_BDK_NCSI_RX_MIN_PKT 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_RX_MIN_PKT 0
#define arguments_BDK_NCSI_RX_MIN_PKT -1,-1,-1,-1

/**
 * Register (RSL) ncsi_rx_stat0
 *
 * NCSI RX Statistics Register 0
 * This register provides a count of valid packets through the receive side NCSI at the output of
 * the receive side buffers.
 */
union bdk_ncsi_rx_stat0
{
    uint64_t u;
    struct bdk_ncsi_rx_stat0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of packets through the RX-side NCSI. This includes both pass through and response
                                                                 packets and does not include those stored in the FIFO waiting to be dequeued.
                                                                 CNT will wrap and is cleared if NCSI is
                                                                 disabled with NCSI_SECURE_CONFIG[NCSIEN]=0. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of packets through the RX-side NCSI. This includes both pass through and response
                                                                 packets and does not include those stored in the FIFO waiting to be dequeued.
                                                                 CNT will wrap and is cleared if NCSI is
                                                                 disabled with NCSI_SECURE_CONFIG[NCSIEN]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_rx_stat0_s cn8; */
    struct bdk_ncsi_rx_stat0_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of packets through the RX-side NCSI. This includes both pass through and response
                                                                 packets and does not include those stored in the FIFO waiting to be dequeued.
                                                                 It does not include AEN packets which are counted in STAT2.
                                                                 CNT will wrap and is cleared if NCSI is
                                                                 disabled with NCSI_SECURE_CONFIG[NCSIEN]=0. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of packets through the RX-side NCSI. This includes both pass through and response
                                                                 packets and does not include those stored in the FIFO waiting to be dequeued.
                                                                 It does not include AEN packets which are counted in STAT2.
                                                                 CNT will wrap and is cleared if NCSI is
                                                                 disabled with NCSI_SECURE_CONFIG[NCSIEN]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_ncsi_rx_stat0 bdk_ncsi_rx_stat0_t;

#define BDK_NCSI_RX_STAT0 BDK_NCSI_RX_STAT0_FUNC()
static inline uint64_t BDK_NCSI_RX_STAT0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_RX_STAT0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000600ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000600ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000600ll;
    __bdk_csr_fatal("NCSI_RX_STAT0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_RX_STAT0 bdk_ncsi_rx_stat0_t
#define bustype_BDK_NCSI_RX_STAT0 BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_RX_STAT0 "NCSI_RX_STAT0"
#define device_bar_BDK_NCSI_RX_STAT0 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_RX_STAT0 0
#define arguments_BDK_NCSI_RX_STAT0 -1,-1,-1,-1

/**
 * Register (RSL) ncsi_rx_stat1
 *
 * NCSI RX Statistics Register 1
 * This register provides a count of valid bytes through the receive side NCSI at the output of
 * the receive side buffers. During underflow situations the count may deviate from
 * the number of bytes that appear on the RMII interface.  This is due to the fact the design
 * does not deassert NCSI_CRS_DV during underflow situations until the packet boundary is detected.
 */
union bdk_ncsi_rx_stat1
{
    uint64_t u;
    struct bdk_ncsi_rx_stat1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of valid bytes through the RX-side NCSI.  This includes both pass through and
                                                                 response packet bytes and does not include those stored in the FIFO waiting to be
                                                                 dequeued. CNT will wrap and is cleared if NCSI is disabled with
                                                                 NCSI_SECURE_CONFIG[NCSIEN]=0. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of valid bytes through the RX-side NCSI.  This includes both pass through and
                                                                 response packet bytes and does not include those stored in the FIFO waiting to be
                                                                 dequeued. CNT will wrap and is cleared if NCSI is disabled with
                                                                 NCSI_SECURE_CONFIG[NCSIEN]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_rx_stat1_s cn8; */
    struct bdk_ncsi_rx_stat1_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of valid bytes through the RX-side NCSI.  This includes both pass through and
                                                                 response packet bytes and does not include those stored in the FIFO waiting to be
                                                                 dequeued.
                                                                 It does not include AEN packets bytes.
                                                                 CNT will wrap and is cleared if NCSI is disabled with
                                                                 NCSI_SECURE_CONFIG[NCSIEN]=0. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of valid bytes through the RX-side NCSI.  This includes both pass through and
                                                                 response packet bytes and does not include those stored in the FIFO waiting to be
                                                                 dequeued.
                                                                 It does not include AEN packets bytes.
                                                                 CNT will wrap and is cleared if NCSI is disabled with
                                                                 NCSI_SECURE_CONFIG[NCSIEN]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_ncsi_rx_stat1 bdk_ncsi_rx_stat1_t;

#define BDK_NCSI_RX_STAT1 BDK_NCSI_RX_STAT1_FUNC()
static inline uint64_t BDK_NCSI_RX_STAT1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_RX_STAT1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000608ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000608ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000608ll;
    __bdk_csr_fatal("NCSI_RX_STAT1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_RX_STAT1 bdk_ncsi_rx_stat1_t
#define bustype_BDK_NCSI_RX_STAT1 BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_RX_STAT1 "NCSI_RX_STAT1"
#define device_bar_BDK_NCSI_RX_STAT1 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_RX_STAT1 0
#define arguments_BDK_NCSI_RX_STAT1 -1,-1,-1,-1

/**
 * Register (RSL) ncsi_rx_stat2
 *
 * NCSI RX Statistics Register 2
 * This register provides statistics counts.
 */
union bdk_ncsi_rx_stat2
{
    uint64_t u;
    struct bdk_ncsi_rx_stat2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t cnt                   : 32; /**< [ 31:  0](R/W/H) Count of AEN command packets through the receive-side NCSI. It does not include
                                                                 those stored in the FIFO waiting to be dequeued. [CNT] will wrap and is cleared if
                                                                 NCSI is disabled with NCSI_SECURE_CONFIG[NCSIEN]=0. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 32; /**< [ 31:  0](R/W/H) Count of AEN command packets through the receive-side NCSI. It does not include
                                                                 those stored in the FIFO waiting to be dequeued. [CNT] will wrap and is cleared if
                                                                 NCSI is disabled with NCSI_SECURE_CONFIG[NCSIEN]=0. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_rx_stat2_s cn; */
};
typedef union bdk_ncsi_rx_stat2 bdk_ncsi_rx_stat2_t;

#define BDK_NCSI_RX_STAT2 BDK_NCSI_RX_STAT2_FUNC()
static inline uint64_t BDK_NCSI_RX_STAT2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_RX_STAT2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000610ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000610ll;
    __bdk_csr_fatal("NCSI_RX_STAT2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_RX_STAT2 bdk_ncsi_rx_stat2_t
#define bustype_BDK_NCSI_RX_STAT2 BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_RX_STAT2 "NCSI_RX_STAT2"
#define device_bar_BDK_NCSI_RX_STAT2 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_RX_STAT2 0
#define arguments_BDK_NCSI_RX_STAT2 -1,-1,-1,-1

/**
 * Register (RSL) ncsi_rx_thresh
 *
 * NCSI RX Threshold Register
 */
union bdk_ncsi_rx_thresh
{
    uint64_t u;
    struct bdk_ncsi_rx_thresh_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t cnt                   : 11; /**< [ 10:  0](R/W) Number of bytes to accumulate in the RX FIFO before sending on the RMII
                                                                 interface. This field should be large enough to prevent underflow on the packet interface
                                                                 and must never be set to 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 11; /**< [ 10:  0](R/W) Number of bytes to accumulate in the RX FIFO before sending on the RMII
                                                                 interface. This field should be large enough to prevent underflow on the packet interface
                                                                 and must never be set to 0x0. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_rx_thresh_s cn; */
};
typedef union bdk_ncsi_rx_thresh bdk_ncsi_rx_thresh_t;

#define BDK_NCSI_RX_THRESH BDK_NCSI_RX_THRESH_FUNC()
static inline uint64_t BDK_NCSI_RX_THRESH_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_RX_THRESH_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000500ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000500ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000500ll;
    __bdk_csr_fatal("NCSI_RX_THRESH", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_RX_THRESH bdk_ncsi_rx_thresh_t
#define bustype_BDK_NCSI_RX_THRESH BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_RX_THRESH "NCSI_RX_THRESH"
#define device_bar_BDK_NCSI_RX_THRESH 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_RX_THRESH 0
#define arguments_BDK_NCSI_RX_THRESH -1,-1,-1,-1

/**
 * Register (RSL) ncsi_secure_config
 *
 * NCSI Secure Configuration Register
 */
union bdk_ncsi_secure_config
{
    uint64_t u;
    struct bdk_ncsi_secure_config_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t ncsien                : 1;  /**< [  1:  1](SR/W) Master enable for the NCSI block. */
        uint64_t ncsisecen             : 1;  /**< [  0:  0](SR/W) For BMC access using the OEM command, allow or deny secure access into CNXXXX.
                                                                 Also see NCSI_TX_NCP_PERM()_TABLE_HI/NCSI_TX_NCP_PERM()_TABLE_LOW.
                                                                 0 = OEM command address must pass the permission table filter before being forwarded to
                                                                 the MRML. Access to NCSI_CPU2BMC_MSG and NCSI_BMC2CPU_MSG are always allowed.
                                                                 1 = Bypass the permissions table and allow any secure or nonsecure register access
                                                                 in the RSL address space. */
#else /* Word 0 - Little Endian */
        uint64_t ncsisecen             : 1;  /**< [  0:  0](SR/W) For BMC access using the OEM command, allow or deny secure access into CNXXXX.
                                                                 Also see NCSI_TX_NCP_PERM()_TABLE_HI/NCSI_TX_NCP_PERM()_TABLE_LOW.
                                                                 0 = OEM command address must pass the permission table filter before being forwarded to
                                                                 the MRML. Access to NCSI_CPU2BMC_MSG and NCSI_BMC2CPU_MSG are always allowed.
                                                                 1 = Bypass the permissions table and allow any secure or nonsecure register access
                                                                 in the RSL address space. */
        uint64_t ncsien                : 1;  /**< [  1:  1](SR/W) Master enable for the NCSI block. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_secure_config_s cn; */
};
typedef union bdk_ncsi_secure_config bdk_ncsi_secure_config_t;

#define BDK_NCSI_SECURE_CONFIG BDK_NCSI_SECURE_CONFIG_FUNC()
static inline uint64_t BDK_NCSI_SECURE_CONFIG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_SECURE_CONFIG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000800ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000800ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000800ll;
    __bdk_csr_fatal("NCSI_SECURE_CONFIG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_SECURE_CONFIG bdk_ncsi_secure_config_t
#define bustype_BDK_NCSI_SECURE_CONFIG BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_SECURE_CONFIG "NCSI_SECURE_CONFIG"
#define device_bar_BDK_NCSI_SECURE_CONFIG 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_SECURE_CONFIG 0
#define arguments_BDK_NCSI_SECURE_CONFIG -1,-1,-1,-1

/**
 * Register (RSL) ncsi_sw_to_value
 *
 * NCSI Software Command Timeout Register
 * This register configures software command timeouts.
 */
union bdk_ncsi_sw_to_value
{
    uint64_t u;
    struct bdk_ncsi_sw_to_value_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t to_value              : 32; /**< [ 31:  0](R/W) Software command timeout value in number of 10 ns ticks. The timeout counter
                                                                 starts counting when NCSI_INT[CMD_PKT_AVAIL] is set, and if software completes
                                                                 the command with NCSI_MCP_AEN_CTL[AEN_RDY] or NCSI_MCP_RSP_CTL[RSP_RDY] the
                                                                 counter completes. If the counter reaches [TO_VALUE], the NCSI_INT[SW_CMD_TO]
                                                                 interrupt will be set. */
#else /* Word 0 - Little Endian */
        uint64_t to_value              : 32; /**< [ 31:  0](R/W) Software command timeout value in number of 10 ns ticks. The timeout counter
                                                                 starts counting when NCSI_INT[CMD_PKT_AVAIL] is set, and if software completes
                                                                 the command with NCSI_MCP_AEN_CTL[AEN_RDY] or NCSI_MCP_RSP_CTL[RSP_RDY] the
                                                                 counter completes. If the counter reaches [TO_VALUE], the NCSI_INT[SW_CMD_TO]
                                                                 interrupt will be set. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_sw_to_value_s cn; */
};
typedef union bdk_ncsi_sw_to_value bdk_ncsi_sw_to_value_t;

#define BDK_NCSI_SW_TO_VALUE BDK_NCSI_SW_TO_VALUE_FUNC()
static inline uint64_t BDK_NCSI_SW_TO_VALUE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_SW_TO_VALUE_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000b18ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000b18ll;
    __bdk_csr_fatal("NCSI_SW_TO_VALUE", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_SW_TO_VALUE bdk_ncsi_sw_to_value_t
#define bustype_BDK_NCSI_SW_TO_VALUE BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_SW_TO_VALUE "NCSI_SW_TO_VALUE"
#define device_bar_BDK_NCSI_SW_TO_VALUE 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_SW_TO_VALUE 0
#define arguments_BDK_NCSI_SW_TO_VALUE -1,-1,-1,-1

/**
 * Register (RSL) ncsi_tx_frm_ctl
 *
 * NCSI TX Frame Control Registers
 * Frame control register for packets coming in from the RMII interface.
 */
union bdk_ncsi_tx_frm_ctl
{
    uint64_t u;
    struct bdk_ncsi_tx_frm_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t fcs_strp              : 1;  /**< [  4:  4](R/W) Strip off the FCS for pass through packets.
                                                                 0 = FCS is not removed from the pass through packets.
                                                                 1 = FCS is removed from the pass through packets. */
        uint64_t pre_strp              : 1;  /**< [  3:  3](R/W) Strip off the PREAMBLE and SFD:
                                                                 0 = PREAMBLE + SFD is sent to core as part of frame.
                                                                 1 = PREAMBLE + SFD is dropped.

                                                                 [PRE_STRP] determines if the PREAMBLE+SFD bytes are thrown away or sent to the
                                                                 core as part of the packet. With either setting, the PREAMBLE and SFD bytes are
                                                                 not counted toward the packet size when checking against the MIN and MAX
                                                                 bounds. Furthermore, the bytes are skipped when locating the start of the L2
                                                                 header for DMAC recognition. */
        uint64_t pre_chk_len           : 3;  /**< [  2:  0](R/W) Check that a correct preamble of a given length is present.

                                                                 With a setting of \> 0, NCSI checks that a valid PREAMBLE is received and of the
                                                                 corresponding length in bytes.
                                                                 If a problem does occur within the PREAMBLE sequence, the frame is marked as bad and not
                                                                 sent into the core. The NCSI_INT[PCTERR] interrupt is also raised.

                                                                 With a setting of 0, NCSI checks the first byte is an valid SFD symbol and not a PREAMBLE
                                                                 symbol. */
#else /* Word 0 - Little Endian */
        uint64_t pre_chk_len           : 3;  /**< [  2:  0](R/W) Check that a correct preamble of a given length is present.

                                                                 With a setting of \> 0, NCSI checks that a valid PREAMBLE is received and of the
                                                                 corresponding length in bytes.
                                                                 If a problem does occur within the PREAMBLE sequence, the frame is marked as bad and not
                                                                 sent into the core. The NCSI_INT[PCTERR] interrupt is also raised.

                                                                 With a setting of 0, NCSI checks the first byte is an valid SFD symbol and not a PREAMBLE
                                                                 symbol. */
        uint64_t pre_strp              : 1;  /**< [  3:  3](R/W) Strip off the PREAMBLE and SFD:
                                                                 0 = PREAMBLE + SFD is sent to core as part of frame.
                                                                 1 = PREAMBLE + SFD is dropped.

                                                                 [PRE_STRP] determines if the PREAMBLE+SFD bytes are thrown away or sent to the
                                                                 core as part of the packet. With either setting, the PREAMBLE and SFD bytes are
                                                                 not counted toward the packet size when checking against the MIN and MAX
                                                                 bounds. Furthermore, the bytes are skipped when locating the start of the L2
                                                                 header for DMAC recognition. */
        uint64_t fcs_strp              : 1;  /**< [  4:  4](R/W) Strip off the FCS for pass through packets.
                                                                 0 = FCS is not removed from the pass through packets.
                                                                 1 = FCS is removed from the pass through packets. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_tx_frm_ctl_s cn; */
};
typedef union bdk_ncsi_tx_frm_ctl bdk_ncsi_tx_frm_ctl_t;

#define BDK_NCSI_TX_FRM_CTL BDK_NCSI_TX_FRM_CTL_FUNC()
static inline uint64_t BDK_NCSI_TX_FRM_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_TX_FRM_CTL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000120ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000120ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000120ll;
    __bdk_csr_fatal("NCSI_TX_FRM_CTL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_TX_FRM_CTL bdk_ncsi_tx_frm_ctl_t
#define bustype_BDK_NCSI_TX_FRM_CTL BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_TX_FRM_CTL "NCSI_TX_FRM_CTL"
#define device_bar_BDK_NCSI_TX_FRM_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_TX_FRM_CTL 0
#define arguments_BDK_NCSI_TX_FRM_CTL -1,-1,-1,-1

/**
 * Register (RSL) ncsi_tx_frm_smac#_cam
 *
 * NCSI TX SMAC CAM Registers
 * These registers set TX framer source MAC address CAM.  See NCSI_CONFIG for addition CAM config
 * options.
 */
union bdk_ncsi_tx_frm_smacx_cam
{
    uint64_t u;
    struct bdk_ncsi_tx_frm_smacx_cam_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t en                    : 1;  /**< [ 48: 48](R/W) CAM entry enable for this SMAC address.
                                                                 1 = Include this address in the matching algorithm.
                                                                 0 = Don't include this address in the matching algorithm. */
        uint64_t adr                   : 48; /**< [ 47:  0](R/W) SMAC address in the CAM used for matching. */
#else /* Word 0 - Little Endian */
        uint64_t adr                   : 48; /**< [ 47:  0](R/W) SMAC address in the CAM used for matching. */
        uint64_t en                    : 1;  /**< [ 48: 48](R/W) CAM entry enable for this SMAC address.
                                                                 1 = Include this address in the matching algorithm.
                                                                 0 = Don't include this address in the matching algorithm. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_tx_frm_smacx_cam_s cn; */
};
typedef union bdk_ncsi_tx_frm_smacx_cam bdk_ncsi_tx_frm_smacx_cam_t;

static inline uint64_t BDK_NCSI_TX_FRM_SMACX_CAM(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_TX_FRM_SMACX_CAM(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1))
        return 0x87e00b000200ll + 8ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=1))
        return 0x87e00b000200ll + 8ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x87e00b000200ll + 8ll * ((a) & 0x1);
    __bdk_csr_fatal("NCSI_TX_FRM_SMACX_CAM", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_TX_FRM_SMACX_CAM(a) bdk_ncsi_tx_frm_smacx_cam_t
#define bustype_BDK_NCSI_TX_FRM_SMACX_CAM(a) BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_TX_FRM_SMACX_CAM(a) "NCSI_TX_FRM_SMACX_CAM"
#define device_bar_BDK_NCSI_TX_FRM_SMACX_CAM(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_TX_FRM_SMACX_CAM(a) (a)
#define arguments_BDK_NCSI_TX_FRM_SMACX_CAM(a) (a),-1,-1,-1

/**
 * Register (RSL) ncsi_tx_ifg
 *
 * NCSI TX Minimum Interframe-Gap Cycles Registers
 * This register specifies the minimum number of interframe-gap (IFG) cycles between packets
 * received from the RMII input interface.
 */
union bdk_ncsi_tx_ifg
{
    uint64_t u;
    struct bdk_ncsi_tx_ifg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t ifg                   : 6;  /**< [  5:  0](R/W) Min IFG (in reference clock cycles) between packets used to determine IFGERR.
                                                                 Normally IFG is 96 bits, and with 2 bits per cycle, equates to 48.
                                                                 The CNXXXX NCSI datapath can tolerate an IFG as small as 32 bit times or 16
                                                                 reference clock cycles. Incoming [IFG] values less than this may cause data
                                                                 corruption particularly if FCS stripping is turned on. */
#else /* Word 0 - Little Endian */
        uint64_t ifg                   : 6;  /**< [  5:  0](R/W) Min IFG (in reference clock cycles) between packets used to determine IFGERR.
                                                                 Normally IFG is 96 bits, and with 2 bits per cycle, equates to 48.
                                                                 The CNXXXX NCSI datapath can tolerate an IFG as small as 32 bit times or 16
                                                                 reference clock cycles. Incoming [IFG] values less than this may cause data
                                                                 corruption particularly if FCS stripping is turned on. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_tx_ifg_s cn; */
};
typedef union bdk_ncsi_tx_ifg bdk_ncsi_tx_ifg_t;

#define BDK_NCSI_TX_IFG BDK_NCSI_TX_IFG_FUNC()
static inline uint64_t BDK_NCSI_TX_IFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_TX_IFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000130ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000130ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000130ll;
    __bdk_csr_fatal("NCSI_TX_IFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_TX_IFG bdk_ncsi_tx_ifg_t
#define bustype_BDK_NCSI_TX_IFG BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_TX_IFG "NCSI_TX_IFG"
#define device_bar_BDK_NCSI_TX_IFG 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_TX_IFG 0
#define arguments_BDK_NCSI_TX_IFG -1,-1,-1,-1

/**
 * Register (RSL) ncsi_tx_jabber
 *
 * NCSI TX Maximum Packet-Size Registers
 * The max size of a packet in bytes, including preamble, SFD and FCS, that the NCSI will allow.
 * Any packet received by the NCSI TX RMII interface larger than NCSI_TX_JABBER[CNT] will be
 * marked with error and become eligible for packet truncation.  Transmission will resume at
 * the detection of the next packet.
 */
union bdk_ncsi_tx_jabber
{
    uint64_t u;
    struct bdk_ncsi_tx_jabber_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t cnt                   : 16; /**< [ 15:  0](R/W) Byte count for jabber check. Failing packets set the JABBER interrupt and are
                                                                 sent with opcode = JABBER. NCSI truncates the packet to [CNT]+1 bytes. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 16; /**< [ 15:  0](R/W) Byte count for jabber check. Failing packets set the JABBER interrupt and are
                                                                 sent with opcode = JABBER. NCSI truncates the packet to [CNT]+1 bytes. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_tx_jabber_s cn; */
};
typedef union bdk_ncsi_tx_jabber bdk_ncsi_tx_jabber_t;

#define BDK_NCSI_TX_JABBER BDK_NCSI_TX_JABBER_FUNC()
static inline uint64_t BDK_NCSI_TX_JABBER_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_TX_JABBER_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000128ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000128ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000128ll;
    __bdk_csr_fatal("NCSI_TX_JABBER", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_TX_JABBER bdk_ncsi_tx_jabber_t
#define bustype_BDK_NCSI_TX_JABBER BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_TX_JABBER "NCSI_TX_JABBER"
#define device_bar_BDK_NCSI_TX_JABBER 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_TX_JABBER 0
#define arguments_BDK_NCSI_TX_JABBER -1,-1,-1,-1

/**
 * Register (RSL) ncsi_tx_mix
 *
 * NCSI TX MIX Configuration Register
 * This register specifies configuration parameters for the MIX interface of CGX.
 */
union bdk_ncsi_tx_mix
{
    uint64_t u;
    struct bdk_ncsi_tx_mix_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t port                  : 4;  /**< [  3:  0](R/W) Port value inserted into MIX frames headed to the BGX where it is used as the channel number. */
#else /* Word 0 - Little Endian */
        uint64_t port                  : 4;  /**< [  3:  0](R/W) Port value inserted into MIX frames headed to the BGX where it is used as the channel number. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_tx_mix_s cn8; */
    struct bdk_ncsi_tx_mix_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t port                  : 4;  /**< [  3:  0](R/W) Port value inserted into MIX frames headed to the CGX where it is used as the channel number. */
#else /* Word 0 - Little Endian */
        uint64_t port                  : 4;  /**< [  3:  0](R/W) Port value inserted into MIX frames headed to the CGX where it is used as the channel number. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_ncsi_tx_mix bdk_ncsi_tx_mix_t;

#define BDK_NCSI_TX_MIX BDK_NCSI_TX_MIX_FUNC()
static inline uint64_t BDK_NCSI_TX_MIX_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_TX_MIX_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000138ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000138ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000138ll;
    __bdk_csr_fatal("NCSI_TX_MIX", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_TX_MIX bdk_ncsi_tx_mix_t
#define bustype_BDK_NCSI_TX_MIX BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_TX_MIX "NCSI_TX_MIX"
#define device_bar_BDK_NCSI_TX_MIX 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_TX_MIX 0
#define arguments_BDK_NCSI_TX_MIX -1,-1,-1,-1

/**
 * Register (RSL) ncsi_tx_ncp_ch_st
 *
 * NCSI TX NCP State Register
 * This register provides the NCSI command processor channel state status.
 */
union bdk_ncsi_tx_ncp_ch_st
{
    uint64_t u;
    struct bdk_ncsi_tx_ncp_ch_st_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t ald                   : 1;  /**< [  1:  1](RO/H) Current state of ALD (allow link disable) in the last received disable channel command. */
        uint64_t state                 : 1;  /**< [  0:  0](RO/H) Current state of the NCSI command processor channel state. */
#else /* Word 0 - Little Endian */
        uint64_t state                 : 1;  /**< [  0:  0](RO/H) Current state of the NCSI command processor channel state. */
        uint64_t ald                   : 1;  /**< [  1:  1](RO/H) Current state of ALD (allow link disable) in the last received disable channel command. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_tx_ncp_ch_st_s cn; */
};
typedef union bdk_ncsi_tx_ncp_ch_st bdk_ncsi_tx_ncp_ch_st_t;

#define BDK_NCSI_TX_NCP_CH_ST BDK_NCSI_TX_NCP_CH_ST_FUNC()
static inline uint64_t BDK_NCSI_TX_NCP_CH_ST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_TX_NCP_CH_ST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000140ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000140ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000140ll;
    __bdk_csr_fatal("NCSI_TX_NCP_CH_ST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_TX_NCP_CH_ST bdk_ncsi_tx_ncp_ch_st_t
#define bustype_BDK_NCSI_TX_NCP_CH_ST BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_TX_NCP_CH_ST "NCSI_TX_NCP_CH_ST"
#define device_bar_BDK_NCSI_TX_NCP_CH_ST 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_TX_NCP_CH_ST 0
#define arguments_BDK_NCSI_TX_NCP_CH_ST -1,-1,-1,-1

/**
 * Register (RSL) ncsi_tx_ncp_perm#_table_hi
 *
 * NCSI TX NCP Permissions Table Hi Registers
 * These registers set the TX NCP permission table high address range filter for the OEM command.
 */
union bdk_ncsi_tx_ncp_permx_table_hi
{
    uint64_t u;
    struct bdk_ncsi_tx_ncp_permx_table_hi_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](SR/W) Specifies the high physical address in formulating a permissions filter for OEM command
                                                                 access.
                                                                 Together with the respective NCSI_TX_NCP_PERM()_TABLE_LOW entry, specifies
                                                                 a range, from NCSI_TX_NCP_PERM_TABLE()_LOW[n] to NCSI_TX_NCP_PERM()_TABLE_HI[n] of
                                                                 physical addresses, contained in the OEM command, that have permissions to execute
                                                                 read or writes to CNXXXX general registers through MRML.

                                                                 Values per entry should be set such that LOW[n]\<=HI[n]. To specify a single address the hi
                                                                 and low are programmed with the same value.
                                                                 If a range in one set of HI/LOW entries overlaps with another, the
                                                                 overlap is harmlessly redundant.

                                                                 Address bit \<63\> is used as the secure bit, and thus to allow secure and
                                                                 nonsecure access to a given register, both the register's address with \<63\>=0,
                                                                 and register's address with \<63\>=1 must be within the range(s).

                                                                 Default values allow default access to:

                                                                   * All NCSI addresses except secure registers.
                                                                   * All BGX(0..3) addresses except secure registers.
                                                                   * All SERDES addresses serving BGX(0...3), namely QLM2, QLM3, DLM4, DLM5 and DLM6.

                                                                 Access to NCSI_CPU2BMC_MSG and NCSI_BMC2CPU_MSG are always allowed. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](SR/W) Specifies the high physical address in formulating a permissions filter for OEM command
                                                                 access.
                                                                 Together with the respective NCSI_TX_NCP_PERM()_TABLE_LOW entry, specifies
                                                                 a range, from NCSI_TX_NCP_PERM_TABLE()_LOW[n] to NCSI_TX_NCP_PERM()_TABLE_HI[n] of
                                                                 physical addresses, contained in the OEM command, that have permissions to execute
                                                                 read or writes to CNXXXX general registers through MRML.

                                                                 Values per entry should be set such that LOW[n]\<=HI[n]. To specify a single address the hi
                                                                 and low are programmed with the same value.
                                                                 If a range in one set of HI/LOW entries overlaps with another, the
                                                                 overlap is harmlessly redundant.

                                                                 Address bit \<63\> is used as the secure bit, and thus to allow secure and
                                                                 nonsecure access to a given register, both the register's address with \<63\>=0,
                                                                 and register's address with \<63\>=1 must be within the range(s).

                                                                 Default values allow default access to:

                                                                   * All NCSI addresses except secure registers.
                                                                   * All BGX(0..3) addresses except secure registers.
                                                                   * All SERDES addresses serving BGX(0...3), namely QLM2, QLM3, DLM4, DLM5 and DLM6.

                                                                 Access to NCSI_CPU2BMC_MSG and NCSI_BMC2CPU_MSG are always allowed. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_tx_ncp_permx_table_hi_s cn8; */
    struct bdk_ncsi_tx_ncp_permx_table_hi_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](SR/W) Specifies the high physical address in formulating a permissions filter for OEM command
                                                                 access.
                                                                 Together with the respective NCSI_TX_NCP_PERM()_TABLE_LOW entry, specifies
                                                                 a range, from NCSI_TX_NCP_PERM_TABLE()_LOW[n] to NCSI_TX_NCP_PERM()_TABLE_HI[n] of
                                                                 physical addresses, contained in the OEM command, that have permissions to execute
                                                                 read or writes to CNXXXX general registers through MRML.

                                                                 Values per entry should be set such that LOW[n]\<=HI[n]. To specify a single address the hi
                                                                 and low are programmed with the same value.
                                                                 If a range in one set of HI/LOW entries overlaps with another, the
                                                                 overlap is harmlessly redundant.

                                                                 Address bit \<63\> is used as the secure bit, and thus to allow secure and
                                                                 nonsecure access to a given register, both the register's address with \<63\>=0,
                                                                 and register's address with \<63\>=1 must be within the range(s).

                                                                 Default values allow default access to:

                                                                   * All NCSI addresses except secure registers.
                                                                   * All CGX(0..3) addresses except secure registers.
                                                                   * All SerDes addresses serving CGX(0...3).

                                                                 Access to NCSI_CPU2BMC_MSG and NCSI_BMC2CPU_MSG are always allowed. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](SR/W) Specifies the high physical address in formulating a permissions filter for OEM command
                                                                 access.
                                                                 Together with the respective NCSI_TX_NCP_PERM()_TABLE_LOW entry, specifies
                                                                 a range, from NCSI_TX_NCP_PERM_TABLE()_LOW[n] to NCSI_TX_NCP_PERM()_TABLE_HI[n] of
                                                                 physical addresses, contained in the OEM command, that have permissions to execute
                                                                 read or writes to CNXXXX general registers through MRML.

                                                                 Values per entry should be set such that LOW[n]\<=HI[n]. To specify a single address the hi
                                                                 and low are programmed with the same value.
                                                                 If a range in one set of HI/LOW entries overlaps with another, the
                                                                 overlap is harmlessly redundant.

                                                                 Address bit \<63\> is used as the secure bit, and thus to allow secure and
                                                                 nonsecure access to a given register, both the register's address with \<63\>=0,
                                                                 and register's address with \<63\>=1 must be within the range(s).

                                                                 Default values allow default access to:

                                                                   * All NCSI addresses except secure registers.
                                                                   * All CGX(0..3) addresses except secure registers.
                                                                   * All SerDes addresses serving CGX(0...3).

                                                                 Access to NCSI_CPU2BMC_MSG and NCSI_BMC2CPU_MSG are always allowed. */
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_ncsi_tx_ncp_permx_table_hi bdk_ncsi_tx_ncp_permx_table_hi_t;

static inline uint64_t BDK_NCSI_TX_NCP_PERMX_TABLE_HI(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_TX_NCP_PERMX_TABLE_HI(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=15))
        return 0x87e00b000900ll + 8ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=15))
        return 0x87e00b000900ll + 8ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=15))
        return 0x87e00b000900ll + 8ll * ((a) & 0xf);
    __bdk_csr_fatal("NCSI_TX_NCP_PERMX_TABLE_HI", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_TX_NCP_PERMX_TABLE_HI(a) bdk_ncsi_tx_ncp_permx_table_hi_t
#define bustype_BDK_NCSI_TX_NCP_PERMX_TABLE_HI(a) BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_TX_NCP_PERMX_TABLE_HI(a) "NCSI_TX_NCP_PERMX_TABLE_HI"
#define device_bar_BDK_NCSI_TX_NCP_PERMX_TABLE_HI(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_TX_NCP_PERMX_TABLE_HI(a) (a)
#define arguments_BDK_NCSI_TX_NCP_PERMX_TABLE_HI(a) (a),-1,-1,-1

/**
 * Register (RSL) ncsi_tx_ncp_perm#_table_low
 *
 * NCSI TX NCP Permissions Table Low Registers
 * These registers set the TX NCP permission table low address range filter for the OEM command.
 */
union bdk_ncsi_tx_ncp_permx_table_low
{
    uint64_t u;
    struct bdk_ncsi_tx_ncp_permx_table_low_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](SR/W) Specifies the low physical address in formulating a permissions filter for OEM command
                                                                 access.  See NCSI_TX_NCP_PERM()_TABLE_HI. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](SR/W) Specifies the low physical address in formulating a permissions filter for OEM command
                                                                 access.  See NCSI_TX_NCP_PERM()_TABLE_HI. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_tx_ncp_permx_table_low_s cn; */
};
typedef union bdk_ncsi_tx_ncp_permx_table_low bdk_ncsi_tx_ncp_permx_table_low_t;

static inline uint64_t BDK_NCSI_TX_NCP_PERMX_TABLE_LOW(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_TX_NCP_PERMX_TABLE_LOW(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=15))
        return 0x87e00b000a00ll + 8ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=15))
        return 0x87e00b000a00ll + 8ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=15))
        return 0x87e00b000a00ll + 8ll * ((a) & 0xf);
    __bdk_csr_fatal("NCSI_TX_NCP_PERMX_TABLE_LOW", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_TX_NCP_PERMX_TABLE_LOW(a) bdk_ncsi_tx_ncp_permx_table_low_t
#define bustype_BDK_NCSI_TX_NCP_PERMX_TABLE_LOW(a) BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_TX_NCP_PERMX_TABLE_LOW(a) "NCSI_TX_NCP_PERMX_TABLE_LOW"
#define device_bar_BDK_NCSI_TX_NCP_PERMX_TABLE_LOW(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_TX_NCP_PERMX_TABLE_LOW(a) (a)
#define arguments_BDK_NCSI_TX_NCP_PERMX_TABLE_LOW(a) (a),-1,-1,-1

/**
 * Register (RSL) ncsi_tx_ncp_pkg_st
 *
 * NCSI TX NCP State Register
 * This register provides the NCSI command processor package state status.
 */
union bdk_ncsi_tx_ncp_pkg_st
{
    uint64_t u;
    struct bdk_ncsi_tx_ncp_pkg_st_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t state                 : 1;  /**< [  0:  0](RO/H) Current state of the NCSI command processor package state. */
#else /* Word 0 - Little Endian */
        uint64_t state                 : 1;  /**< [  0:  0](RO/H) Current state of the NCSI command processor package state. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_tx_ncp_pkg_st_s cn; */
};
typedef union bdk_ncsi_tx_ncp_pkg_st bdk_ncsi_tx_ncp_pkg_st_t;

#define BDK_NCSI_TX_NCP_PKG_ST BDK_NCSI_TX_NCP_PKG_ST_FUNC()
static inline uint64_t BDK_NCSI_TX_NCP_PKG_ST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_TX_NCP_PKG_ST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000148ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000148ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000148ll;
    __bdk_csr_fatal("NCSI_TX_NCP_PKG_ST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_TX_NCP_PKG_ST bdk_ncsi_tx_ncp_pkg_st_t
#define bustype_BDK_NCSI_TX_NCP_PKG_ST BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_TX_NCP_PKG_ST "NCSI_TX_NCP_PKG_ST"
#define device_bar_BDK_NCSI_TX_NCP_PKG_ST 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_TX_NCP_PKG_ST 0
#define arguments_BDK_NCSI_TX_NCP_PKG_ST -1,-1,-1,-1

/**
 * Register (RSL) ncsi_tx_stat0
 *
 * NCSI TX Statistics Register 0
 * This register provides a count of valid packets detected at the output of the transmit side
 * NCSI framer.
 */
union bdk_ncsi_tx_stat0
{
    uint64_t u;
    struct bdk_ncsi_tx_stat0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of valid packets through the TX side framers. CNT will wrap and is cleared if NCSI
                                                                 is disabled with
                                                                 NCSI_SECURE_CONFIG[NCSIEN]=0. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of valid packets through the TX side framers. CNT will wrap and is cleared if NCSI
                                                                 is disabled with
                                                                 NCSI_SECURE_CONFIG[NCSIEN]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_tx_stat0_s cn; */
};
typedef union bdk_ncsi_tx_stat0 bdk_ncsi_tx_stat0_t;

#define BDK_NCSI_TX_STAT0 BDK_NCSI_TX_STAT0_FUNC()
static inline uint64_t BDK_NCSI_TX_STAT0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_TX_STAT0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000300ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000300ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000300ll;
    __bdk_csr_fatal("NCSI_TX_STAT0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_TX_STAT0 bdk_ncsi_tx_stat0_t
#define bustype_BDK_NCSI_TX_STAT0 BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_TX_STAT0 "NCSI_TX_STAT0"
#define device_bar_BDK_NCSI_TX_STAT0 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_TX_STAT0 0
#define arguments_BDK_NCSI_TX_STAT0 -1,-1,-1,-1

/**
 * Register (RSL) ncsi_tx_stat1
 *
 * NCSI TX Statistics Register 1
 * This register provides a count of valid bytes detected at the output of the transmit side
 * NCSI framer.  These bytes are detected as being part of a valid frame.
 */
union bdk_ncsi_tx_stat1
{
    uint64_t u;
    struct bdk_ncsi_tx_stat1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of valid bytes through the TX side framer. CNT will wrap and is cleared if NCSI is
                                                                 disabled with
                                                                 NCSI_SECURE_CONFIG[NCSIEN]=0. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of valid bytes through the TX side framer. CNT will wrap and is cleared if NCSI is
                                                                 disabled with
                                                                 NCSI_SECURE_CONFIG[NCSIEN]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ncsi_tx_stat1_s cn; */
};
typedef union bdk_ncsi_tx_stat1 bdk_ncsi_tx_stat1_t;

#define BDK_NCSI_TX_STAT1 BDK_NCSI_TX_STAT1_FUNC()
static inline uint64_t BDK_NCSI_TX_STAT1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NCSI_TX_STAT1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x87e00b000308ll;
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00b000308ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00b000308ll;
    __bdk_csr_fatal("NCSI_TX_STAT1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NCSI_TX_STAT1 bdk_ncsi_tx_stat1_t
#define bustype_BDK_NCSI_TX_STAT1 BDK_CSR_TYPE_RSL
#define basename_BDK_NCSI_TX_STAT1 "NCSI_TX_STAT1"
#define device_bar_BDK_NCSI_TX_STAT1 0x0 /* PF_BAR0 */
#define busnum_BDK_NCSI_TX_STAT1 0
#define arguments_BDK_NCSI_TX_STAT1 -1,-1,-1,-1

#endif /* __BDK_CSRS_NCSI_H__ */
