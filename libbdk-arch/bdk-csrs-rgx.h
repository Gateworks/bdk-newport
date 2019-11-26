#ifndef __BDK_CSRS_RGX_H__
#define __BDK_CSRS_RGX_H__
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
 * OcteonTX RGX.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration rgx_bar_e
 *
 * RGX Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_RGX_BAR_E_RGXX_PF_BAR0(a) (0x87e0e8000000ll + 0x1000000ll * (a))
#define BDK_RGX_BAR_E_RGXX_PF_BAR0_SIZE 0x400000ull
#define BDK_RGX_BAR_E_RGXX_PF_BAR4(a) (0x87e0e8400000ll + 0x1000000ll * (a))
#define BDK_RGX_BAR_E_RGXX_PF_BAR4_SIZE 0x400000ull

/**
 * Enumeration rgx_int_vec_e
 *
 * RGX MSI-X Vector Enumeration
 * Enumeration the MSI-X interrupt vectors.
 */
#define BDK_RGX_INT_VEC_E_CMRX_INT(a) (0 + 4 * (a))
#define BDK_RGX_INT_VEC_E_CMR_MEM_INT (0x10)
#define BDK_RGX_INT_VEC_E_GMPX_GMI_RX_INT(a) (2 + 4 * (a))
#define BDK_RGX_INT_VEC_E_GMPX_GMI_TX_INT(a) (3 + 4 * (a))
#define BDK_RGX_INT_VEC_E_GMPX_PCS_INT(a) (1 + 4 * (a))

/**
 * Enumeration rgx_opcode_e
 *
 * INTERNAL: RGX Error Opcode Enumeration
 *
 * Enumerates the error opcodes created by RGX and presented to NIC.
 */
#define BDK_RGX_OPCODE_E_RE_FCS (7)
#define BDK_RGX_OPCODE_E_RE_FCS_RCV (8)
#define BDK_RGX_OPCODE_E_RE_JABBER (2)
#define BDK_RGX_OPCODE_E_RE_NONE (0)
#define BDK_RGX_OPCODE_E_RE_PARTIAL (1)
#define BDK_RGX_OPCODE_E_RE_RX_CTL (0xb)
#define BDK_RGX_OPCODE_E_RE_SKIP (0xc)
#define BDK_RGX_OPCODE_E_RE_TERMINATE (9)

/**
 * Register (RSL) rgx#_cmr#_config
 *
 * RGX CMR Configuration Registers
 * Logical MAC configuration registers; one per LMAC.
 * Internal:
 * \<pre\>
 * Typical configurations:
 *   ---------------------------------------------------------------------------
 *   Configuration           LMACS  Register             [ENABLE]    [LMAC_TYPE]
 *   ---------------------------------------------------------------------------
 *   RGMII                   `      RGXn_CMR0_CONFIG     1           5
 *   ---------------------------------------------------------------------------
 * \</pre\>
 */
union bdk_rgxx_cmrx_config
{
    uint64_t u;
    struct bdk_rgxx_cmrx_config_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_18_63        : 46;
        uint64_t p2x_select            : 1;  /**< [ 17: 17](R/W) Selects interior side P2X interface over which the LMAC will communicate:
                                                                 \<pre\>
                                                                   [P2X_SELECT]      Name      Connected block
                                                                   -------------------------------------------
                                                                   0                 P2X0      NIC
                                                                   1                 P2X1      Reserved
                                                                 \</pre\> */
        uint64_t x2p_select            : 1;  /**< [ 16: 16](R/W) Selects interior side X2P interface over which the LMAC will communicate:
                                                                 \<pre\>
                                                                   [X2P_SELECT]      Name      Connected block
                                                                   -------------------------------------------
                                                                   0                 X2P0      NIC
                                                                   1                 X2P1      Reserved
                                                                 \</pre\> */
        uint64_t enable                : 1;  /**< [ 15: 15](R/W) Logical MAC enable. This is the master enable for the LMAC. When clear, all the
                                                                 dedicated RGX context state for the LMAC (state machines, FIFOs, counters, etc.) is reset,
                                                                 and LMAC access to shared RGX resources is disabled.

                                                                 When set, LMAC operation is enabled, including link bring-up, synchronization, and
                                                                 transmit/receive of idles and fault sequences. Note that configuration registers for an
                                                                 LMAC are not reset when this bit is clear, allowing software to program them before
                                                                 setting this bit to enable the LMAC. This bit together with [LMAC_TYPE] is also used to
                                                                 enable the clocking to the GMP. CMR clocking is enabled when any of the paths are enabled. */
        uint64_t data_pkt_rx_en        : 1;  /**< [ 14: 14](R/W) Data packet receive enable. When [ENABLE] = 1 and [DATA_PKT_RX_EN] = 1, the reception of
                                                                 data
                                                                 packets is enabled in the MAC layer. When [ENABLE] = 1 and [DATA_PKT_RX_EN] = 0, the MAC
                                                                 layer
                                                                 drops received data and flow-control packets. */
        uint64_t data_pkt_tx_en        : 1;  /**< [ 13: 13](R/W) Data packet transmit enable. When [ENABLE] = 1 and [DATA_PKT_TX_EN] = 1, the transmission
                                                                 of
                                                                 data
                                                                 packets is enabled in the MAC layer. When [ENABLE] = 1 and [DATA_PKT_TX_EN] = 0, the MAC
                                                                 layer
                                                                 suppresses the transmission of new data and packets for the LMAC. */
        uint64_t int_beat_gen          : 1;  /**< [ 12: 12](R/W) Reserved.
                                                                 Internal:
                                                                 Internal beat generation. This bit is used for debug/test purposes and should be clear
                                                                 during normal operation. When set, the LMAC's PCS layer ignores RXVALID and
                                                                 TXREADY/TXCREDIT from the associated SerDes lanes, internally generates fake (idle)
                                                                 RXVALID and TXCREDIT pulses, and suppresses transmission to the SerDes. */
        uint64_t mix_en                : 1;  /**< [ 11: 11](R/W) Must be 0. */
        uint64_t lmac_type             : 3;  /**< [ 10:  8](R/W) Logical MAC/port type:

                                                                 \<pre\>
                                                                   LMAC_TYPE  Name       Description
                                                                   ---------------------------------
                                                                   0x5        RGMII      RGMII
                                                                   Other      --         Reserved
                                                                 \</pre\>

                                                                 This field must be programmed to its final value before [ENABLE] is set, and must not
                                                                 be changed when [ENABLE] = 1. */
        uint64_t lane_to_sds           : 8;  /**< [  7:  0](R/W) Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t lane_to_sds           : 8;  /**< [  7:  0](R/W) Reserved. */
        uint64_t lmac_type             : 3;  /**< [ 10:  8](R/W) Logical MAC/port type:

                                                                 \<pre\>
                                                                   LMAC_TYPE  Name       Description
                                                                   ---------------------------------
                                                                   0x5        RGMII      RGMII
                                                                   Other      --         Reserved
                                                                 \</pre\>

                                                                 This field must be programmed to its final value before [ENABLE] is set, and must not
                                                                 be changed when [ENABLE] = 1. */
        uint64_t mix_en                : 1;  /**< [ 11: 11](R/W) Must be 0. */
        uint64_t int_beat_gen          : 1;  /**< [ 12: 12](R/W) Reserved.
                                                                 Internal:
                                                                 Internal beat generation. This bit is used for debug/test purposes and should be clear
                                                                 during normal operation. When set, the LMAC's PCS layer ignores RXVALID and
                                                                 TXREADY/TXCREDIT from the associated SerDes lanes, internally generates fake (idle)
                                                                 RXVALID and TXCREDIT pulses, and suppresses transmission to the SerDes. */
        uint64_t data_pkt_tx_en        : 1;  /**< [ 13: 13](R/W) Data packet transmit enable. When [ENABLE] = 1 and [DATA_PKT_TX_EN] = 1, the transmission
                                                                 of
                                                                 data
                                                                 packets is enabled in the MAC layer. When [ENABLE] = 1 and [DATA_PKT_TX_EN] = 0, the MAC
                                                                 layer
                                                                 suppresses the transmission of new data and packets for the LMAC. */
        uint64_t data_pkt_rx_en        : 1;  /**< [ 14: 14](R/W) Data packet receive enable. When [ENABLE] = 1 and [DATA_PKT_RX_EN] = 1, the reception of
                                                                 data
                                                                 packets is enabled in the MAC layer. When [ENABLE] = 1 and [DATA_PKT_RX_EN] = 0, the MAC
                                                                 layer
                                                                 drops received data and flow-control packets. */
        uint64_t enable                : 1;  /**< [ 15: 15](R/W) Logical MAC enable. This is the master enable for the LMAC. When clear, all the
                                                                 dedicated RGX context state for the LMAC (state machines, FIFOs, counters, etc.) is reset,
                                                                 and LMAC access to shared RGX resources is disabled.

                                                                 When set, LMAC operation is enabled, including link bring-up, synchronization, and
                                                                 transmit/receive of idles and fault sequences. Note that configuration registers for an
                                                                 LMAC are not reset when this bit is clear, allowing software to program them before
                                                                 setting this bit to enable the LMAC. This bit together with [LMAC_TYPE] is also used to
                                                                 enable the clocking to the GMP. CMR clocking is enabled when any of the paths are enabled. */
        uint64_t x2p_select            : 1;  /**< [ 16: 16](R/W) Selects interior side X2P interface over which the LMAC will communicate:
                                                                 \<pre\>
                                                                   [X2P_SELECT]      Name      Connected block
                                                                   -------------------------------------------
                                                                   0                 X2P0      NIC
                                                                   1                 X2P1      Reserved
                                                                 \</pre\> */
        uint64_t p2x_select            : 1;  /**< [ 17: 17](R/W) Selects interior side P2X interface over which the LMAC will communicate:
                                                                 \<pre\>
                                                                   [P2X_SELECT]      Name      Connected block
                                                                   -------------------------------------------
                                                                   0                 P2X0      NIC
                                                                   1                 P2X1      Reserved
                                                                 \</pre\> */
        uint64_t reserved_18_63        : 46;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_config_s cn; */
};
typedef union bdk_rgxx_cmrx_config bdk_rgxx_cmrx_config_t;

static inline uint64_t BDK_RGXX_CMRX_CONFIG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_CONFIG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000000ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_CONFIG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_CONFIG(a,b) bdk_rgxx_cmrx_config_t
#define bustype_BDK_RGXX_CMRX_CONFIG(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_CONFIG(a,b) "RGXX_CMRX_CONFIG"
#define device_bar_BDK_RGXX_CMRX_CONFIG(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_CONFIG(a,b) (a)
#define arguments_BDK_RGXX_CMRX_CONFIG(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_int
 *
 * RGX CMR Interrupt Register
 */
union bdk_rgxx_cmrx_int
{
    uint64_t u;
    struct bdk_rgxx_cmrx_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t nic_nxc               : 1;  /**< [  3:  3](R/W1C/H) TX channel out-of-range from NIC interface. */
        uint64_t pko_nxc               : 1;  /**< [  2:  2](R/W1C/H) Reserved. */
        uint64_t overflw               : 1;  /**< [  1:  1](R/W1C/H) RX overflow. */
        uint64_t pause_drp             : 1;  /**< [  0:  0](R/W1C/H) RX PAUSE packet was dropped due to full RXB FIFO or during partner reset. */
#else /* Word 0 - Little Endian */
        uint64_t pause_drp             : 1;  /**< [  0:  0](R/W1C/H) RX PAUSE packet was dropped due to full RXB FIFO or during partner reset. */
        uint64_t overflw               : 1;  /**< [  1:  1](R/W1C/H) RX overflow. */
        uint64_t pko_nxc               : 1;  /**< [  2:  2](R/W1C/H) Reserved. */
        uint64_t nic_nxc               : 1;  /**< [  3:  3](R/W1C/H) TX channel out-of-range from NIC interface. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_int_s cn; */
};
typedef union bdk_rgxx_cmrx_int bdk_rgxx_cmrx_int_t;

static inline uint64_t BDK_RGXX_CMRX_INT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_INT(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000040ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_INT", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_INT(a,b) bdk_rgxx_cmrx_int_t
#define bustype_BDK_RGXX_CMRX_INT(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_INT(a,b) "RGXX_CMRX_INT"
#define device_bar_BDK_RGXX_CMRX_INT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_INT(a,b) (a)
#define arguments_BDK_RGXX_CMRX_INT(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_int_ena_w1c
 *
 * RGX CMR Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_rgxx_cmrx_int_ena_w1c
{
    uint64_t u;
    struct bdk_rgxx_cmrx_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t nic_nxc               : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for RGX(0)_CMR(0)_INT[NIC_NXC]. */
        uint64_t pko_nxc               : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for RGX(0)_CMR(0)_INT[PKO_NXC]. */
        uint64_t overflw               : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for RGX(0)_CMR(0)_INT[OVERFLW]. */
        uint64_t pause_drp             : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for RGX(0)_CMR(0)_INT[PAUSE_DRP]. */
#else /* Word 0 - Little Endian */
        uint64_t pause_drp             : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for RGX(0)_CMR(0)_INT[PAUSE_DRP]. */
        uint64_t overflw               : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for RGX(0)_CMR(0)_INT[OVERFLW]. */
        uint64_t pko_nxc               : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for RGX(0)_CMR(0)_INT[PKO_NXC]. */
        uint64_t nic_nxc               : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for RGX(0)_CMR(0)_INT[NIC_NXC]. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_int_ena_w1c_s cn; */
};
typedef union bdk_rgxx_cmrx_int_ena_w1c bdk_rgxx_cmrx_int_ena_w1c_t;

static inline uint64_t BDK_RGXX_CMRX_INT_ENA_W1C(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_INT_ENA_W1C(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000050ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_INT_ENA_W1C", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_INT_ENA_W1C(a,b) bdk_rgxx_cmrx_int_ena_w1c_t
#define bustype_BDK_RGXX_CMRX_INT_ENA_W1C(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_INT_ENA_W1C(a,b) "RGXX_CMRX_INT_ENA_W1C"
#define device_bar_BDK_RGXX_CMRX_INT_ENA_W1C(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_INT_ENA_W1C(a,b) (a)
#define arguments_BDK_RGXX_CMRX_INT_ENA_W1C(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_int_ena_w1s
 *
 * RGX CMR Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_rgxx_cmrx_int_ena_w1s
{
    uint64_t u;
    struct bdk_rgxx_cmrx_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t nic_nxc               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for RGX(0)_CMR(0)_INT[NIC_NXC]. */
        uint64_t pko_nxc               : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for RGX(0)_CMR(0)_INT[PKO_NXC]. */
        uint64_t overflw               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for RGX(0)_CMR(0)_INT[OVERFLW]. */
        uint64_t pause_drp             : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for RGX(0)_CMR(0)_INT[PAUSE_DRP]. */
#else /* Word 0 - Little Endian */
        uint64_t pause_drp             : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for RGX(0)_CMR(0)_INT[PAUSE_DRP]. */
        uint64_t overflw               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for RGX(0)_CMR(0)_INT[OVERFLW]. */
        uint64_t pko_nxc               : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for RGX(0)_CMR(0)_INT[PKO_NXC]. */
        uint64_t nic_nxc               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for RGX(0)_CMR(0)_INT[NIC_NXC]. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_int_ena_w1s_s cn; */
};
typedef union bdk_rgxx_cmrx_int_ena_w1s bdk_rgxx_cmrx_int_ena_w1s_t;

static inline uint64_t BDK_RGXX_CMRX_INT_ENA_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_INT_ENA_W1S(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000058ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_INT_ENA_W1S", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_INT_ENA_W1S(a,b) bdk_rgxx_cmrx_int_ena_w1s_t
#define bustype_BDK_RGXX_CMRX_INT_ENA_W1S(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_INT_ENA_W1S(a,b) "RGXX_CMRX_INT_ENA_W1S"
#define device_bar_BDK_RGXX_CMRX_INT_ENA_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_INT_ENA_W1S(a,b) (a)
#define arguments_BDK_RGXX_CMRX_INT_ENA_W1S(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_int_w1s
 *
 * RGX CMR Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_rgxx_cmrx_int_w1s
{
    uint64_t u;
    struct bdk_rgxx_cmrx_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t nic_nxc               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets RGX(0)_CMR(0)_INT[NIC_NXC]. */
        uint64_t pko_nxc               : 1;  /**< [  2:  2](R/W1S/H) Reads or sets RGX(0)_CMR(0)_INT[PKO_NXC]. */
        uint64_t overflw               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets RGX(0)_CMR(0)_INT[OVERFLW]. */
        uint64_t pause_drp             : 1;  /**< [  0:  0](R/W1S/H) Reads or sets RGX(0)_CMR(0)_INT[PAUSE_DRP]. */
#else /* Word 0 - Little Endian */
        uint64_t pause_drp             : 1;  /**< [  0:  0](R/W1S/H) Reads or sets RGX(0)_CMR(0)_INT[PAUSE_DRP]. */
        uint64_t overflw               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets RGX(0)_CMR(0)_INT[OVERFLW]. */
        uint64_t pko_nxc               : 1;  /**< [  2:  2](R/W1S/H) Reads or sets RGX(0)_CMR(0)_INT[PKO_NXC]. */
        uint64_t nic_nxc               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets RGX(0)_CMR(0)_INT[NIC_NXC]. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_int_w1s_s cn; */
};
typedef union bdk_rgxx_cmrx_int_w1s bdk_rgxx_cmrx_int_w1s_t;

static inline uint64_t BDK_RGXX_CMRX_INT_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_INT_W1S(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000048ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_INT_W1S", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_INT_W1S(a,b) bdk_rgxx_cmrx_int_w1s_t
#define bustype_BDK_RGXX_CMRX_INT_W1S(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_INT_W1S(a,b) "RGXX_CMRX_INT_W1S"
#define device_bar_BDK_RGXX_CMRX_INT_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_INT_W1S(a,b) (a)
#define arguments_BDK_RGXX_CMRX_INT_W1S(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_prt_cbfc_ctl
 *
 * RGX CMR LMAC CBFC Control Registers
 * See XOFF definition listed under RGX()_SMU()_CBFC_CTL.
 */
union bdk_rgxx_cmrx_prt_cbfc_ctl
{
    uint64_t u;
    struct bdk_rgxx_cmrx_prt_cbfc_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t phys_bp               : 16; /**< [ 31: 16](R/W) When the hardware is backpressuring any LMACs (from either DFC or
                                                                 RGX()_CMR()_TX_OVR_BP[TX_CHAN_BP])
                                                                 and all LMACs indicated by PHYS_BP are backpressured, simulate physical backpressure by
                                                                 deferring all packets on the transmitter. */
        uint64_t reserved_0_15         : 16;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_15         : 16;
        uint64_t phys_bp               : 16; /**< [ 31: 16](R/W) When the hardware is backpressuring any LMACs (from either DFC or
                                                                 RGX()_CMR()_TX_OVR_BP[TX_CHAN_BP])
                                                                 and all LMACs indicated by PHYS_BP are backpressured, simulate physical backpressure by
                                                                 deferring all packets on the transmitter. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_prt_cbfc_ctl_s cn; */
};
typedef union bdk_rgxx_cmrx_prt_cbfc_ctl bdk_rgxx_cmrx_prt_cbfc_ctl_t;

static inline uint64_t BDK_RGXX_CMRX_PRT_CBFC_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_PRT_CBFC_CTL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000508ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_PRT_CBFC_CTL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_PRT_CBFC_CTL(a,b) bdk_rgxx_cmrx_prt_cbfc_ctl_t
#define bustype_BDK_RGXX_CMRX_PRT_CBFC_CTL(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_PRT_CBFC_CTL(a,b) "RGXX_CMRX_PRT_CBFC_CTL"
#define device_bar_BDK_RGXX_CMRX_PRT_CBFC_CTL(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_PRT_CBFC_CTL(a,b) (a)
#define arguments_BDK_RGXX_CMRX_PRT_CBFC_CTL(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_rx_bp_drop
 *
 * RGX Receive Backpressure Drop Register
 */
union bdk_rgxx_cmrx_rx_bp_drop
{
    uint64_t u;
    struct bdk_rgxx_cmrx_rx_bp_drop_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t mark                  : 7;  /**< [  6:  0](R/W) Number of eight-byte cycles to reserve in the RX FIFO. When the number of free
                                                                 entries in the RX FIFO is less than or equal to [MARK], incoming packet data is
                                                                 dropped. [MARK] additionally indicates the number of entries to reserve in the RX FIFO for
                                                                 closing partially received packets. [MARK] should typically be programmed to its reset
                                                                 value; failure to program correctly can lead to system instability. */
#else /* Word 0 - Little Endian */
        uint64_t mark                  : 7;  /**< [  6:  0](R/W) Number of eight-byte cycles to reserve in the RX FIFO. When the number of free
                                                                 entries in the RX FIFO is less than or equal to [MARK], incoming packet data is
                                                                 dropped. [MARK] additionally indicates the number of entries to reserve in the RX FIFO for
                                                                 closing partially received packets. [MARK] should typically be programmed to its reset
                                                                 value; failure to program correctly can lead to system instability. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_rx_bp_drop_s cn; */
};
typedef union bdk_rgxx_cmrx_rx_bp_drop bdk_rgxx_cmrx_rx_bp_drop_t;

static inline uint64_t BDK_RGXX_CMRX_RX_BP_DROP(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_RX_BP_DROP(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e80000c8ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_RX_BP_DROP", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_RX_BP_DROP(a,b) bdk_rgxx_cmrx_rx_bp_drop_t
#define bustype_BDK_RGXX_CMRX_RX_BP_DROP(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_RX_BP_DROP(a,b) "RGXX_CMRX_RX_BP_DROP"
#define device_bar_BDK_RGXX_CMRX_RX_BP_DROP(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_RX_BP_DROP(a,b) (a)
#define arguments_BDK_RGXX_CMRX_RX_BP_DROP(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_rx_bp_off
 *
 * RGX Receive Backpressure Off Register
 */
union bdk_rgxx_cmrx_rx_bp_off
{
    uint64_t u;
    struct bdk_rgxx_cmrx_rx_bp_off_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t mark                  : 7;  /**< [  6:  0](R/W) Low watermark (number of eight-byte cycles to deassert backpressure). Level is also used
                                                                 to exit the overflow dropping state. */
#else /* Word 0 - Little Endian */
        uint64_t mark                  : 7;  /**< [  6:  0](R/W) Low watermark (number of eight-byte cycles to deassert backpressure). Level is also used
                                                                 to exit the overflow dropping state. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_rx_bp_off_s cn; */
};
typedef union bdk_rgxx_cmrx_rx_bp_off bdk_rgxx_cmrx_rx_bp_off_t;

static inline uint64_t BDK_RGXX_CMRX_RX_BP_OFF(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_RX_BP_OFF(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e80000d8ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_RX_BP_OFF", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_RX_BP_OFF(a,b) bdk_rgxx_cmrx_rx_bp_off_t
#define bustype_BDK_RGXX_CMRX_RX_BP_OFF(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_RX_BP_OFF(a,b) "RGXX_CMRX_RX_BP_OFF"
#define device_bar_BDK_RGXX_CMRX_RX_BP_OFF(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_RX_BP_OFF(a,b) (a)
#define arguments_BDK_RGXX_CMRX_RX_BP_OFF(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_rx_bp_on
 *
 * RGX Receive Backpressure On Register
 */
union bdk_rgxx_cmrx_rx_bp_on
{
    uint64_t u;
    struct bdk_rgxx_cmrx_rx_bp_on_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t mark                  : 10; /**< [  9:  0](R/W) High watermark. Buffer depth in multiple of 16-bytes, at which RGX will
                                                                 assert backpressure for each individual LMAC. Must satisfy:

                                                                   RGX()_CMR()_RX_BP_OFF[MARK] \<= RGX()_CMR()_RX_BP_ON[MARK] \<
                                                                   (FIFO_SIZE - RGX()_CMR()_RX_BP_DROP[MARK]).

                                                                 A value of 0x0 immediately asserts backpressure.

                                                                 The recommended value is 1/4th the size of the per-LMAC RX FIFO_SIZE as
                                                                 determined by RGX()_CMR_RX_LMACS[LMACS]. For example, with
                                                                 16 KB of buffering, the recommended 1/4th size of that 16 KB is 4 KB, which
                                                                 in units of 16 bytes gives [MARK] = 0x100 (the reset value). */
#else /* Word 0 - Little Endian */
        uint64_t mark                  : 10; /**< [  9:  0](R/W) High watermark. Buffer depth in multiple of 16-bytes, at which RGX will
                                                                 assert backpressure for each individual LMAC. Must satisfy:

                                                                   RGX()_CMR()_RX_BP_OFF[MARK] \<= RGX()_CMR()_RX_BP_ON[MARK] \<
                                                                   (FIFO_SIZE - RGX()_CMR()_RX_BP_DROP[MARK]).

                                                                 A value of 0x0 immediately asserts backpressure.

                                                                 The recommended value is 1/4th the size of the per-LMAC RX FIFO_SIZE as
                                                                 determined by RGX()_CMR_RX_LMACS[LMACS]. For example, with
                                                                 16 KB of buffering, the recommended 1/4th size of that 16 KB is 4 KB, which
                                                                 in units of 16 bytes gives [MARK] = 0x100 (the reset value). */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_rx_bp_on_s cn; */
};
typedef union bdk_rgxx_cmrx_rx_bp_on bdk_rgxx_cmrx_rx_bp_on_t;

static inline uint64_t BDK_RGXX_CMRX_RX_BP_ON(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_RX_BP_ON(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e80000d0ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_RX_BP_ON", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_RX_BP_ON(a,b) bdk_rgxx_cmrx_rx_bp_on_t
#define bustype_BDK_RGXX_CMRX_RX_BP_ON(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_RX_BP_ON(a,b) "RGXX_CMRX_RX_BP_ON"
#define device_bar_BDK_RGXX_CMRX_RX_BP_ON(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_RX_BP_ON(a,b) (a)
#define arguments_BDK_RGXX_CMRX_RX_BP_ON(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_rx_bp_status
 *
 * RGX CMR Receive Backpressure Status Registers
 */
union bdk_rgxx_cmrx_rx_bp_status
{
    uint64_t u;
    struct bdk_rgxx_cmrx_rx_bp_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t bp                    : 1;  /**< [  0:  0](RO/H) Per-LMAC backpressure status.
                                                                 0 = LMAC is not backpressured.
                                                                 1 = LMAC is backpressured. */
#else /* Word 0 - Little Endian */
        uint64_t bp                    : 1;  /**< [  0:  0](RO/H) Per-LMAC backpressure status.
                                                                 0 = LMAC is not backpressured.
                                                                 1 = LMAC is backpressured. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_rx_bp_status_s cn; */
};
typedef union bdk_rgxx_cmrx_rx_bp_status bdk_rgxx_cmrx_rx_bp_status_t;

static inline uint64_t BDK_RGXX_CMRX_RX_BP_STATUS(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_RX_BP_STATUS(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e80000f0ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_RX_BP_STATUS", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_RX_BP_STATUS(a,b) bdk_rgxx_cmrx_rx_bp_status_t
#define bustype_BDK_RGXX_CMRX_RX_BP_STATUS(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_RX_BP_STATUS(a,b) "RGXX_CMRX_RX_BP_STATUS"
#define device_bar_BDK_RGXX_CMRX_RX_BP_STATUS(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_RX_BP_STATUS(a,b) (a)
#define arguments_BDK_RGXX_CMRX_RX_BP_STATUS(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_rx_dmac_ctl
 *
 * RGX CMR Receive DMAC Address-Control Register
 * Internal:
 * "* ALGORITHM
 * Here is some pseudo code that represents the address filter behavior.
 * dmac_addr_filter(uint8 prt, uint48 dmac) {
 * for (lmac=0, lmac\<1, lmac++) {
 *   if (is_bcst(dmac))                               // broadcast accept
 *     return (RGX()_CMR({lmac})_RX_DMAC_CTL[BCST_ACCEPT] ? ACCEPT : REJECT);
 *   if (is_mcst(dmac) && RGX()_CMR({lmac})_RX_DMAC_CTL[MCST_MODE] == 0)   // multicast reject
 *     return REJECT;
 *   if (is_mcst(dmac) && RGX()_CMR({lmac})_RX_DMAC_CTL[MCST_MODE] == 1)   // multicast accept
 *     return ACCEPT;
 *   else        // DMAC CAM filter
 *     cam_hit = 0;
 *   for (i=0; i\<32; i++) {
 *     cam = RGX()_CMR_RX_DMAC({i})_CAM;
 *     if (cam[EN] && cam[ID] == {lmac} && cam[ADR] == dmac) {
 *       cam_hit = 1;
 *       break;
 *     }
 *   }
 *   if (cam_hit) {
 *     return (RGX()_CMR({lmac})_RX_DMAC_CTL[CAM_ACCEPT] ? ACCEPT : REJECT);
 *   else
 *     return (RGX()_CMR({lmac})_RX_DMAC_CTL[CAM_ACCEPT] ? REJECT : ACCEPT);
 *   }
 * }"
 */
union bdk_rgxx_cmrx_rx_dmac_ctl
{
    uint64_t u;
    struct bdk_rgxx_cmrx_rx_dmac_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t cam_accept            : 1;  /**< [  3:  3](R/W) Allow or deny DMAC address filter.
                                                                 0 = Reject the packet on DMAC CAM address match.
                                                                 1 = Accept the packet on DMAC CAM address match. */
        uint64_t mcst_mode             : 2;  /**< [  2:  1](R/W) Multicast mode.
                                                                 0x0 = Force reject all multicast packets.
                                                                 0x1 = Force accept all multicast packets.
                                                                 0x2 = Use the address filter CAM.
                                                                 0x3 = Reserved. */
        uint64_t bcst_accept           : 1;  /**< [  0:  0](R/W) Allow or deny broadcast packets.
                                                                 0 = Reject all broadcast packets.
                                                                 1 = Accept all broadcast Packets. */
#else /* Word 0 - Little Endian */
        uint64_t bcst_accept           : 1;  /**< [  0:  0](R/W) Allow or deny broadcast packets.
                                                                 0 = Reject all broadcast packets.
                                                                 1 = Accept all broadcast Packets. */
        uint64_t mcst_mode             : 2;  /**< [  2:  1](R/W) Multicast mode.
                                                                 0x0 = Force reject all multicast packets.
                                                                 0x1 = Force accept all multicast packets.
                                                                 0x2 = Use the address filter CAM.
                                                                 0x3 = Reserved. */
        uint64_t cam_accept            : 1;  /**< [  3:  3](R/W) Allow or deny DMAC address filter.
                                                                 0 = Reject the packet on DMAC CAM address match.
                                                                 1 = Accept the packet on DMAC CAM address match. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_rx_dmac_ctl_s cn; */
};
typedef union bdk_rgxx_cmrx_rx_dmac_ctl bdk_rgxx_cmrx_rx_dmac_ctl_t;

static inline uint64_t BDK_RGXX_CMRX_RX_DMAC_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_RX_DMAC_CTL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e80000e8ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_RX_DMAC_CTL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_RX_DMAC_CTL(a,b) bdk_rgxx_cmrx_rx_dmac_ctl_t
#define bustype_BDK_RGXX_CMRX_RX_DMAC_CTL(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_RX_DMAC_CTL(a,b) "RGXX_CMRX_RX_DMAC_CTL"
#define device_bar_BDK_RGXX_CMRX_RX_DMAC_CTL(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_RX_DMAC_CTL(a,b) (a)
#define arguments_BDK_RGXX_CMRX_RX_DMAC_CTL(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_rx_fifo_len
 *
 * RGX CMR Receive FIFO Length Registers
 */
union bdk_rgxx_cmrx_rx_fifo_len
{
    uint64_t u;
    struct bdk_rgxx_cmrx_rx_fifo_len_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t busy                  : 1;  /**< [ 13: 13](RO/H) Indicates if GMP and CMR are busy processing a packet. Used when bringing an LMAC
                                                                 down since in low bandwidth cases, as the FIFO length may often appear to be 0x0. */
        uint64_t reserved_11_12        : 2;
        uint64_t fifo_len              : 11; /**< [ 10:  0](RO/H) Per-LMAC FIFO length. Useful for determining if FIFO is empty when bringing an LMAC down. */
#else /* Word 0 - Little Endian */
        uint64_t fifo_len              : 11; /**< [ 10:  0](RO/H) Per-LMAC FIFO length. Useful for determining if FIFO is empty when bringing an LMAC down. */
        uint64_t reserved_11_12        : 2;
        uint64_t busy                  : 1;  /**< [ 13: 13](RO/H) Indicates if GMP and CMR are busy processing a packet. Used when bringing an LMAC
                                                                 down since in low bandwidth cases, as the FIFO length may often appear to be 0x0. */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_rx_fifo_len_s cn; */
};
typedef union bdk_rgxx_cmrx_rx_fifo_len bdk_rgxx_cmrx_rx_fifo_len_t;

static inline uint64_t BDK_RGXX_CMRX_RX_FIFO_LEN(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_RX_FIFO_LEN(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000108ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_RX_FIFO_LEN", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_RX_FIFO_LEN(a,b) bdk_rgxx_cmrx_rx_fifo_len_t
#define bustype_BDK_RGXX_CMRX_RX_FIFO_LEN(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_RX_FIFO_LEN(a,b) "RGXX_CMRX_RX_FIFO_LEN"
#define device_bar_BDK_RGXX_CMRX_RX_FIFO_LEN(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_RX_FIFO_LEN(a,b) (a)
#define arguments_BDK_RGXX_CMRX_RX_FIFO_LEN(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_rx_id_map
 *
 * RGX CMR Receive ID Map Register
 * These registers set the RX LMAC ID mapping for X2P/NIC.
 */
union bdk_rgxx_cmrx_rx_id_map
{
    uint64_t u;
    struct bdk_rgxx_cmrx_rx_id_map_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_15_63        : 49;
        uint64_t rid                   : 7;  /**< [ 14:  8](R/W) Reserved.
                                                                 Internal:
                                                                 Defeatured. Reassembly ID for Octeon PKI; not used in CNXXXX.
                                                                 Reassembly ID map for this LMAC. A shared pool of 96 reassembly IDs (RIDs) exists for all
                                                                 MACs.

                                                                 The RID for this LMAC must be constrained such that it does not overlap with any other MAC
                                                                 in the system. Its reset value has been chosen such that this condition is satisfied:

                                                                 _ RID reset value = 4*(RGX_ID + 1) + LMAC_ID

                                                                 Changes to RID must only occur when the LMAC is quiescent (i.e. the LMAC receive interface
                                                                 is down and the RX FIFO is empty). */
        uint64_t unused                : 2;  /**< [  7:  6](RAZ) Reserved. */
        uint64_t pknd                  : 6;  /**< [  5:  0](R/W) Port kind for this LMAC. */
#else /* Word 0 - Little Endian */
        uint64_t pknd                  : 6;  /**< [  5:  0](R/W) Port kind for this LMAC. */
        uint64_t unused                : 2;  /**< [  7:  6](RAZ) Reserved. */
        uint64_t rid                   : 7;  /**< [ 14:  8](R/W) Reserved.
                                                                 Internal:
                                                                 Defeatured. Reassembly ID for Octeon PKI; not used in CNXXXX.
                                                                 Reassembly ID map for this LMAC. A shared pool of 96 reassembly IDs (RIDs) exists for all
                                                                 MACs.

                                                                 The RID for this LMAC must be constrained such that it does not overlap with any other MAC
                                                                 in the system. Its reset value has been chosen such that this condition is satisfied:

                                                                 _ RID reset value = 4*(RGX_ID + 1) + LMAC_ID

                                                                 Changes to RID must only occur when the LMAC is quiescent (i.e. the LMAC receive interface
                                                                 is down and the RX FIFO is empty). */
        uint64_t reserved_15_63        : 49;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_rx_id_map_s cn; */
};
typedef union bdk_rgxx_cmrx_rx_id_map bdk_rgxx_cmrx_rx_id_map_t;

static inline uint64_t BDK_RGXX_CMRX_RX_ID_MAP(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_RX_ID_MAP(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000060ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_RX_ID_MAP", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_RX_ID_MAP(a,b) bdk_rgxx_cmrx_rx_id_map_t
#define bustype_BDK_RGXX_CMRX_RX_ID_MAP(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_RX_ID_MAP(a,b) "RGXX_CMRX_RX_ID_MAP"
#define device_bar_BDK_RGXX_CMRX_RX_ID_MAP(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_RX_ID_MAP(a,b) (a)
#define arguments_BDK_RGXX_CMRX_RX_ID_MAP(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_rx_logl_xoff
 *
 * RGX CMR Receive Logical XOFF Registers
 */
union bdk_rgxx_cmrx_rx_logl_xoff
{
    uint64_t u;
    struct bdk_rgxx_cmrx_rx_logl_xoff_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t xoff                  : 16; /**< [ 15:  0](R/W1S/H) Together with RGX()_CMR()_RX_LOGL_XON, defines type of channel backpressure to
                                                                 apply to the MAC. Writing 1 sets the same physical
                                                                 register as that which is cleared by RGX()_CMR()_RX_LOGL_XON[XON]. An XOFF value
                                                                 of 1 will cause a backpressure on the MAC. */
#else /* Word 0 - Little Endian */
        uint64_t xoff                  : 16; /**< [ 15:  0](R/W1S/H) Together with RGX()_CMR()_RX_LOGL_XON, defines type of channel backpressure to
                                                                 apply to the MAC. Writing 1 sets the same physical
                                                                 register as that which is cleared by RGX()_CMR()_RX_LOGL_XON[XON]. An XOFF value
                                                                 of 1 will cause a backpressure on the MAC. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_rx_logl_xoff_s cn; */
};
typedef union bdk_rgxx_cmrx_rx_logl_xoff bdk_rgxx_cmrx_rx_logl_xoff_t;

static inline uint64_t BDK_RGXX_CMRX_RX_LOGL_XOFF(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_RX_LOGL_XOFF(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e80000f8ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_RX_LOGL_XOFF", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_RX_LOGL_XOFF(a,b) bdk_rgxx_cmrx_rx_logl_xoff_t
#define bustype_BDK_RGXX_CMRX_RX_LOGL_XOFF(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_RX_LOGL_XOFF(a,b) "RGXX_CMRX_RX_LOGL_XOFF"
#define device_bar_BDK_RGXX_CMRX_RX_LOGL_XOFF(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_RX_LOGL_XOFF(a,b) (a)
#define arguments_BDK_RGXX_CMRX_RX_LOGL_XOFF(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_rx_logl_xon
 *
 * RGX CMR Receive Logical XON Registers
 */
union bdk_rgxx_cmrx_rx_logl_xon
{
    uint64_t u;
    struct bdk_rgxx_cmrx_rx_logl_xon_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t xon                   : 16; /**< [ 15:  0](R/W1C/H) Together with RGX()_CMR()_RX_LOGL_XOFF, defines type of channel backpressure to
                                                                 apply. Do not write when HiGig2 is enabled. Writing 1 clears the same physical register as
                                                                 that which is set by XOFF. An XON value of 1 means only NIC channel BP can cause a
                                                                 backpressure on the MAC. */
#else /* Word 0 - Little Endian */
        uint64_t xon                   : 16; /**< [ 15:  0](R/W1C/H) Together with RGX()_CMR()_RX_LOGL_XOFF, defines type of channel backpressure to
                                                                 apply. Do not write when HiGig2 is enabled. Writing 1 clears the same physical register as
                                                                 that which is set by XOFF. An XON value of 1 means only NIC channel BP can cause a
                                                                 backpressure on the MAC. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_rx_logl_xon_s cn; */
};
typedef union bdk_rgxx_cmrx_rx_logl_xon bdk_rgxx_cmrx_rx_logl_xon_t;

static inline uint64_t BDK_RGXX_CMRX_RX_LOGL_XON(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_RX_LOGL_XON(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000100ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_RX_LOGL_XON", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_RX_LOGL_XON(a,b) bdk_rgxx_cmrx_rx_logl_xon_t
#define bustype_BDK_RGXX_CMRX_RX_LOGL_XON(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_RX_LOGL_XON(a,b) "RGXX_CMRX_RX_LOGL_XON"
#define device_bar_BDK_RGXX_CMRX_RX_LOGL_XON(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_RX_LOGL_XON(a,b) (a)
#define arguments_BDK_RGXX_CMRX_RX_LOGL_XON(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_rx_pause_drop_time
 *
 * RGX CMR Receive Pause Drop-Time Register
 */
union bdk_rgxx_cmrx_rx_pause_drop_time
{
    uint64_t u;
    struct bdk_rgxx_cmrx_rx_pause_drop_time_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t pause_time            : 16; /**< [ 15:  0](R/W1C/H) Time extracted from the dropped PAUSE packet dropped due to RXB FIFO full or during partner reset. */
#else /* Word 0 - Little Endian */
        uint64_t pause_time            : 16; /**< [ 15:  0](R/W1C/H) Time extracted from the dropped PAUSE packet dropped due to RXB FIFO full or during partner reset. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_rx_pause_drop_time_s cn; */
};
typedef union bdk_rgxx_cmrx_rx_pause_drop_time bdk_rgxx_cmrx_rx_pause_drop_time_t;

static inline uint64_t BDK_RGXX_CMRX_RX_PAUSE_DROP_TIME(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_RX_PAUSE_DROP_TIME(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000068ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_RX_PAUSE_DROP_TIME", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_RX_PAUSE_DROP_TIME(a,b) bdk_rgxx_cmrx_rx_pause_drop_time_t
#define bustype_BDK_RGXX_CMRX_RX_PAUSE_DROP_TIME(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_RX_PAUSE_DROP_TIME(a,b) "RGXX_CMRX_RX_PAUSE_DROP_TIME"
#define device_bar_BDK_RGXX_CMRX_RX_PAUSE_DROP_TIME(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_RX_PAUSE_DROP_TIME(a,b) (a)
#define arguments_BDK_RGXX_CMRX_RX_PAUSE_DROP_TIME(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_rx_stat0
 *
 * RGX Receive Status Register 0
 * These registers provide a count of received packets that meet the following conditions:
 * * are not recognized as PAUSE packets.
 * * are not dropped due DMAC filtering.
 * * are not dropped due FIFO full status.
 * * do not have any other OPCODE (FCS, Length, etc).
 */
union bdk_rgxx_cmrx_rx_stat0
{
    uint64_t u;
    struct bdk_rgxx_cmrx_rx_stat0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of received packets. [CNT] will wrap and is cleared if LMAC is disabled with
                                                                 RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of received packets. [CNT] will wrap and is cleared if LMAC is disabled with
                                                                 RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_rx_stat0_s cn; */
};
typedef union bdk_rgxx_cmrx_rx_stat0 bdk_rgxx_cmrx_rx_stat0_t;

static inline uint64_t BDK_RGXX_CMRX_RX_STAT0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_RX_STAT0(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000070ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_RX_STAT0", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_RX_STAT0(a,b) bdk_rgxx_cmrx_rx_stat0_t
#define bustype_BDK_RGXX_CMRX_RX_STAT0(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_RX_STAT0(a,b) "RGXX_CMRX_RX_STAT0"
#define device_bar_BDK_RGXX_CMRX_RX_STAT0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_RX_STAT0(a,b) (a)
#define arguments_BDK_RGXX_CMRX_RX_STAT0(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_rx_stat1
 *
 * RGX Receive Status Register 1
 * These registers provide a count of octets of received packets.
 */
union bdk_rgxx_cmrx_rx_stat1
{
    uint64_t u;
    struct bdk_rgxx_cmrx_rx_stat1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Octet count of received packets. [CNT] will wrap and is cleared if LMAC is disabled with
                                                                 RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Octet count of received packets. [CNT] will wrap and is cleared if LMAC is disabled with
                                                                 RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_rx_stat1_s cn; */
};
typedef union bdk_rgxx_cmrx_rx_stat1 bdk_rgxx_cmrx_rx_stat1_t;

static inline uint64_t BDK_RGXX_CMRX_RX_STAT1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_RX_STAT1(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000078ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_RX_STAT1", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_RX_STAT1(a,b) bdk_rgxx_cmrx_rx_stat1_t
#define bustype_BDK_RGXX_CMRX_RX_STAT1(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_RX_STAT1(a,b) "RGXX_CMRX_RX_STAT1"
#define device_bar_BDK_RGXX_CMRX_RX_STAT1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_RX_STAT1(a,b) (a)
#define arguments_BDK_RGXX_CMRX_RX_STAT1(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_rx_stat2
 *
 * RGX Receive Status Register 2
 * These registers provide a count of all packets received that were recognized as flow-control
 * or PAUSE packets. PAUSE packets with any kind of error are counted in
 * RGX()_CMR()_RX_STAT8 (error stats register). Pause packets can be optionally dropped
 * or forwarded based on RGX()_GMP_GMI_RX_FRM_CTL[CTL_DRP]. This count increments
 * regardless of whether the packet is dropped. PAUSE packets are never counted in
 * RGX()_CMR()_RX_STAT0.
 */
union bdk_rgxx_cmrx_rx_stat2
{
    uint64_t u;
    struct bdk_rgxx_cmrx_rx_stat2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of received PAUSE packets. [CNT] will wrap and is cleared if LMAC is disabled with
                                                                 RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of received PAUSE packets. [CNT] will wrap and is cleared if LMAC is disabled with
                                                                 RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_rx_stat2_s cn; */
};
typedef union bdk_rgxx_cmrx_rx_stat2 bdk_rgxx_cmrx_rx_stat2_t;

static inline uint64_t BDK_RGXX_CMRX_RX_STAT2(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_RX_STAT2(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000080ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_RX_STAT2", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_RX_STAT2(a,b) bdk_rgxx_cmrx_rx_stat2_t
#define bustype_BDK_RGXX_CMRX_RX_STAT2(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_RX_STAT2(a,b) "RGXX_CMRX_RX_STAT2"
#define device_bar_BDK_RGXX_CMRX_RX_STAT2(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_RX_STAT2(a,b) (a)
#define arguments_BDK_RGXX_CMRX_RX_STAT2(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_rx_stat3
 *
 * RGX Receive Status Register 3
 * These registers provide a count of octets of received PAUSE and control packets.
 */
union bdk_rgxx_cmrx_rx_stat3
{
    uint64_t u;
    struct bdk_rgxx_cmrx_rx_stat3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Octet count of received PAUSE packets. [CNT] will wrap and is cleared if LMAC is disabled
                                                                 with RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Octet count of received PAUSE packets. [CNT] will wrap and is cleared if LMAC is disabled
                                                                 with RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_rx_stat3_s cn; */
};
typedef union bdk_rgxx_cmrx_rx_stat3 bdk_rgxx_cmrx_rx_stat3_t;

static inline uint64_t BDK_RGXX_CMRX_RX_STAT3(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_RX_STAT3(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000088ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_RX_STAT3", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_RX_STAT3(a,b) bdk_rgxx_cmrx_rx_stat3_t
#define bustype_BDK_RGXX_CMRX_RX_STAT3(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_RX_STAT3(a,b) "RGXX_CMRX_RX_STAT3"
#define device_bar_BDK_RGXX_CMRX_RX_STAT3(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_RX_STAT3(a,b) (a)
#define arguments_BDK_RGXX_CMRX_RX_STAT3(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_rx_stat4
 *
 * RGX Receive Status Register 4
 * These registers provide a count of all packets received that were dropped by the DMAC filter.
 * Packets that match the DMAC are dropped and counted here regardless of whether they were ERR
 * packets, but does not include those reported in RGX()_CMR()_RX_STAT6. These packets
 * are never counted in RGX()_CMR()_RX_STAT0. Eight-byte packets as the result of
 * truncation or other means are not dropped by CNXXXX and will never appear in this count.
 */
union bdk_rgxx_cmrx_rx_stat4
{
    uint64_t u;
    struct bdk_rgxx_cmrx_rx_stat4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of filtered DMAC packets. [CNT] will wrap and is cleared if LMAC is disabled with
                                                                 RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of filtered DMAC packets. [CNT] will wrap and is cleared if LMAC is disabled with
                                                                 RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_rx_stat4_s cn; */
};
typedef union bdk_rgxx_cmrx_rx_stat4 bdk_rgxx_cmrx_rx_stat4_t;

static inline uint64_t BDK_RGXX_CMRX_RX_STAT4(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_RX_STAT4(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000090ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_RX_STAT4", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_RX_STAT4(a,b) bdk_rgxx_cmrx_rx_stat4_t
#define bustype_BDK_RGXX_CMRX_RX_STAT4(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_RX_STAT4(a,b) "RGXX_CMRX_RX_STAT4"
#define device_bar_BDK_RGXX_CMRX_RX_STAT4(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_RX_STAT4(a,b) (a)
#define arguments_BDK_RGXX_CMRX_RX_STAT4(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_rx_stat5
 *
 * RGX Receive Status Register 5
 * These registers provide a count of octets of filtered DMAC packets.
 */
union bdk_rgxx_cmrx_rx_stat5
{
    uint64_t u;
    struct bdk_rgxx_cmrx_rx_stat5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Octet count of filtered DMAC packets. [CNT] will wrap and is cleared if LMAC is disabled
                                                                 with RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Octet count of filtered DMAC packets. [CNT] will wrap and is cleared if LMAC is disabled
                                                                 with RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_rx_stat5_s cn; */
};
typedef union bdk_rgxx_cmrx_rx_stat5 bdk_rgxx_cmrx_rx_stat5_t;

static inline uint64_t BDK_RGXX_CMRX_RX_STAT5(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_RX_STAT5(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000098ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_RX_STAT5", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_RX_STAT5(a,b) bdk_rgxx_cmrx_rx_stat5_t
#define bustype_BDK_RGXX_CMRX_RX_STAT5(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_RX_STAT5(a,b) "RGXX_CMRX_RX_STAT5"
#define device_bar_BDK_RGXX_CMRX_RX_STAT5(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_RX_STAT5(a,b) (a)
#define arguments_BDK_RGXX_CMRX_RX_STAT5(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_rx_stat6
 *
 * RGX Receive Status Register 6
 * These registers provide a count of all packets received that were dropped due to a full
 * receive FIFO. They do not count any packet that is truncated at the point of overflow and sent
 * on to the NIC. These registers count all entire packets dropped by the FIFO for a given LMAC
 * regardless of DMAC or PAUSE type.
 */
union bdk_rgxx_cmrx_rx_stat6
{
    uint64_t u;
    struct bdk_rgxx_cmrx_rx_stat6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of dropped packets. [CNT] will wrap and is cleared if LMAC is disabled with
                                                                 RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of dropped packets. [CNT] will wrap and is cleared if LMAC is disabled with
                                                                 RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_rx_stat6_s cn; */
};
typedef union bdk_rgxx_cmrx_rx_stat6 bdk_rgxx_cmrx_rx_stat6_t;

static inline uint64_t BDK_RGXX_CMRX_RX_STAT6(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_RX_STAT6(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e80000a0ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_RX_STAT6", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_RX_STAT6(a,b) bdk_rgxx_cmrx_rx_stat6_t
#define bustype_BDK_RGXX_CMRX_RX_STAT6(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_RX_STAT6(a,b) "RGXX_CMRX_RX_STAT6"
#define device_bar_BDK_RGXX_CMRX_RX_STAT6(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_RX_STAT6(a,b) (a)
#define arguments_BDK_RGXX_CMRX_RX_STAT6(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_rx_stat7
 *
 * RGX Receive Status Register 7
 * These registers provide a count of octets of received packets that were dropped due to a full
 * receive FIFO.
 */
union bdk_rgxx_cmrx_rx_stat7
{
    uint64_t u;
    struct bdk_rgxx_cmrx_rx_stat7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Octet count of dropped packets. [CNT] will wrap and is cleared if LMAC is disabled with
                                                                 RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Octet count of dropped packets. [CNT] will wrap and is cleared if LMAC is disabled with
                                                                 RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_rx_stat7_s cn; */
};
typedef union bdk_rgxx_cmrx_rx_stat7 bdk_rgxx_cmrx_rx_stat7_t;

static inline uint64_t BDK_RGXX_CMRX_RX_STAT7(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_RX_STAT7(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e80000a8ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_RX_STAT7", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_RX_STAT7(a,b) bdk_rgxx_cmrx_rx_stat7_t
#define bustype_BDK_RGXX_CMRX_RX_STAT7(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_RX_STAT7(a,b) "RGXX_CMRX_RX_STAT7"
#define device_bar_BDK_RGXX_CMRX_RX_STAT7(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_RX_STAT7(a,b) (a)
#define arguments_BDK_RGXX_CMRX_RX_STAT7(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_rx_stat8
 *
 * RGX Receive Status Register 8
 * These registers provide a count of all packets received with some error that were not dropped
 * either due to the DMAC filter or lack of room in the receive FIFO.
 * This does not include packets which were counted in
 * RGX()_CMR()_RX_STAT2, RGX()_CMR()_RX_STAT4 nor
 * RGX()_CMR()_RX_STAT6.
 *
 * Which statistics are updated on control packet errors and drops are shown below:
 *
 * \<pre\>
 * if dropped {
 *   if !errored STAT8
 *   if overflow STAT6
 *   else if dmac drop STAT4
 *   else if filter drop STAT2
 * } else {
 *   if errored STAT2
 *   else STAT8
 * }
 * \</pre\>
 */
union bdk_rgxx_cmrx_rx_stat8
{
    uint64_t u;
    struct bdk_rgxx_cmrx_rx_stat8_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of error packets. [CNT] will wrap and is cleared if LMAC is disabled with
                                                                 RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of error packets. [CNT] will wrap and is cleared if LMAC is disabled with
                                                                 RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_rx_stat8_s cn; */
};
typedef union bdk_rgxx_cmrx_rx_stat8 bdk_rgxx_cmrx_rx_stat8_t;

static inline uint64_t BDK_RGXX_CMRX_RX_STAT8(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_RX_STAT8(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e80000b0ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_RX_STAT8", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_RX_STAT8(a,b) bdk_rgxx_cmrx_rx_stat8_t
#define bustype_BDK_RGXX_CMRX_RX_STAT8(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_RX_STAT8(a,b) "RGXX_CMRX_RX_STAT8"
#define device_bar_BDK_RGXX_CMRX_RX_STAT8(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_RX_STAT8(a,b) (a)
#define arguments_BDK_RGXX_CMRX_RX_STAT8(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_rx_weight
 *
 * RGX CMR Receive-Weight Register
 */
union bdk_rgxx_cmrx_rx_weight
{
    uint64_t u;
    struct bdk_rgxx_cmrx_rx_weight_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t weight                : 4;  /**< [  3:  0](R/W) For the weighted round robin algorithm in CMR RXB, weight to assign for this LMAC relative
                                                                 to other LMAC weights. Defaults to round-robin (non-weighted minimum setting of 0x1). A
                                                                 setting of 0x0 effectively takes the LMAC out of eligibility. */
#else /* Word 0 - Little Endian */
        uint64_t weight                : 4;  /**< [  3:  0](R/W) For the weighted round robin algorithm in CMR RXB, weight to assign for this LMAC relative
                                                                 to other LMAC weights. Defaults to round-robin (non-weighted minimum setting of 0x1). A
                                                                 setting of 0x0 effectively takes the LMAC out of eligibility. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_rx_weight_s cn; */
};
typedef union bdk_rgxx_cmrx_rx_weight bdk_rgxx_cmrx_rx_weight_t;

static inline uint64_t BDK_RGXX_CMRX_RX_WEIGHT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_RX_WEIGHT(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e80000e0ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_RX_WEIGHT", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_RX_WEIGHT(a,b) bdk_rgxx_cmrx_rx_weight_t
#define bustype_BDK_RGXX_CMRX_RX_WEIGHT(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_RX_WEIGHT(a,b) "RGXX_CMRX_RX_WEIGHT"
#define device_bar_BDK_RGXX_CMRX_RX_WEIGHT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_RX_WEIGHT(a,b) (a)
#define arguments_BDK_RGXX_CMRX_RX_WEIGHT(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_tx_channel
 *
 * RGX CMR Transmit-Channels Registers
 */
union bdk_rgxx_cmrx_tx_channel
{
    uint64_t u;
    struct bdk_rgxx_cmrx_tx_channel_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t msk                   : 16; /**< [ 31: 16](R/W) Backpressure channel mask. RGX can completely ignore the channel backpressure for channel
                                                                 specified by this field. Any channel in which MSK\<n\> is set never sends backpressure
                                                                 information to NIC. */
        uint64_t dis                   : 16; /**< [ 15:  0](R/W) Credit return backpressure disable. RGX stops returning channel credits for any
                                                                 channel that is backpressured. These bits can be used to override that. If
                                                                 [DIS]\<n\> is set, channel credits may flow back regardless of the backpressure
                                                                 for that channel. */
#else /* Word 0 - Little Endian */
        uint64_t dis                   : 16; /**< [ 15:  0](R/W) Credit return backpressure disable. RGX stops returning channel credits for any
                                                                 channel that is backpressured. These bits can be used to override that. If
                                                                 [DIS]\<n\> is set, channel credits may flow back regardless of the backpressure
                                                                 for that channel. */
        uint64_t msk                   : 16; /**< [ 31: 16](R/W) Backpressure channel mask. RGX can completely ignore the channel backpressure for channel
                                                                 specified by this field. Any channel in which MSK\<n\> is set never sends backpressure
                                                                 information to NIC. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_tx_channel_s cn; */
};
typedef union bdk_rgxx_cmrx_tx_channel bdk_rgxx_cmrx_tx_channel_t;

static inline uint64_t BDK_RGXX_CMRX_TX_CHANNEL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_TX_CHANNEL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000500ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_TX_CHANNEL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_TX_CHANNEL(a,b) bdk_rgxx_cmrx_tx_channel_t
#define bustype_BDK_RGXX_CMRX_TX_CHANNEL(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_TX_CHANNEL(a,b) "RGXX_CMRX_TX_CHANNEL"
#define device_bar_BDK_RGXX_CMRX_TX_CHANNEL(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_TX_CHANNEL(a,b) (a)
#define arguments_BDK_RGXX_CMRX_TX_CHANNEL(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_tx_fifo_len
 *
 * RGX CMR Transmit FIFO Length Registers
 */
union bdk_rgxx_cmrx_tx_fifo_len
{
    uint64_t u;
    struct bdk_rgxx_cmrx_tx_fifo_len_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_15_63        : 49;
        uint64_t lmac_idle             : 1;  /**< [ 14: 14](RO/H) Idle signal to identify when all credits and other pipeline buffers are also cleared out
                                                                 and LMAC can be considered IDLE in the RGX CMR TX. */
        uint64_t reserved_12_13        : 2;
        uint64_t fifo_len              : 12; /**< [ 11:  0](RO/H) Per-LMAC TXB main FIFO length. Useful for determining if main FIFO is empty when bringing
                                                                 an LMAC down. */
#else /* Word 0 - Little Endian */
        uint64_t fifo_len              : 12; /**< [ 11:  0](RO/H) Per-LMAC TXB main FIFO length. Useful for determining if main FIFO is empty when bringing
                                                                 an LMAC down. */
        uint64_t reserved_12_13        : 2;
        uint64_t lmac_idle             : 1;  /**< [ 14: 14](RO/H) Idle signal to identify when all credits and other pipeline buffers are also cleared out
                                                                 and LMAC can be considered IDLE in the RGX CMR TX. */
        uint64_t reserved_15_63        : 49;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_tx_fifo_len_s cn; */
};
typedef union bdk_rgxx_cmrx_tx_fifo_len bdk_rgxx_cmrx_tx_fifo_len_t;

static inline uint64_t BDK_RGXX_CMRX_TX_FIFO_LEN(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_TX_FIFO_LEN(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000518ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_TX_FIFO_LEN", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_TX_FIFO_LEN(a,b) bdk_rgxx_cmrx_tx_fifo_len_t
#define bustype_BDK_RGXX_CMRX_TX_FIFO_LEN(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_TX_FIFO_LEN(a,b) "RGXX_CMRX_TX_FIFO_LEN"
#define device_bar_BDK_RGXX_CMRX_TX_FIFO_LEN(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_TX_FIFO_LEN(a,b) (a)
#define arguments_BDK_RGXX_CMRX_TX_FIFO_LEN(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_tx_hg2_status
 *
 * RGX CMR Transmit HiGig2 Status Registers
 */
union bdk_rgxx_cmrx_tx_hg2_status
{
    uint64_t u;
    struct bdk_rgxx_cmrx_tx_hg2_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t xof                   : 16; /**< [ 31: 16](RO/H) 16-bit XOF back pressure vector from HiGig2 message packet or from PFC/CBFC packets. Non-
                                                                 zero only when logical back pressure is active. All bits are 0 when [LGTIM2GO] = 0x0. */
        uint64_t lgtim2go              : 16; /**< [ 15:  0](RO/H) Logical packet flow back pressure time remaining. Initial value set from XOF time field of
                                                                 HiGig2 message packet received or a function of the enabled and current timers for
                                                                 PFC/CBFC packets. Nonzero only when logical back pressure is active. */
#else /* Word 0 - Little Endian */
        uint64_t lgtim2go              : 16; /**< [ 15:  0](RO/H) Logical packet flow back pressure time remaining. Initial value set from XOF time field of
                                                                 HiGig2 message packet received or a function of the enabled and current timers for
                                                                 PFC/CBFC packets. Nonzero only when logical back pressure is active. */
        uint64_t xof                   : 16; /**< [ 31: 16](RO/H) 16-bit XOF back pressure vector from HiGig2 message packet or from PFC/CBFC packets. Non-
                                                                 zero only when logical back pressure is active. All bits are 0 when [LGTIM2GO] = 0x0. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_tx_hg2_status_s cn; */
};
typedef union bdk_rgxx_cmrx_tx_hg2_status bdk_rgxx_cmrx_tx_hg2_status_t;

static inline uint64_t BDK_RGXX_CMRX_TX_HG2_STATUS(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_TX_HG2_STATUS(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000510ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_TX_HG2_STATUS", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_TX_HG2_STATUS(a,b) bdk_rgxx_cmrx_tx_hg2_status_t
#define bustype_BDK_RGXX_CMRX_TX_HG2_STATUS(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_TX_HG2_STATUS(a,b) "RGXX_CMRX_TX_HG2_STATUS"
#define device_bar_BDK_RGXX_CMRX_TX_HG2_STATUS(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_TX_HG2_STATUS(a,b) (a)
#define arguments_BDK_RGXX_CMRX_TX_HG2_STATUS(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_tx_ovr_bp
 *
 * RGX CMR Transmit-Channels Backpressure Override Registers
 */
union bdk_rgxx_cmrx_tx_ovr_bp
{
    uint64_t u;
    struct bdk_rgxx_cmrx_tx_ovr_bp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t tx_chan_bp            : 16; /**< [ 15:  0](R/W) Per-channel backpressure status sent to NIC.  Also see RGX()_PRT_CBFC_CTL for details on
                                                                 impact to physical backpressure.
                                                                 0 = Channel is available.
                                                                 1 = Channel is backpressured. */
#else /* Word 0 - Little Endian */
        uint64_t tx_chan_bp            : 16; /**< [ 15:  0](R/W) Per-channel backpressure status sent to NIC.  Also see RGX()_PRT_CBFC_CTL for details on
                                                                 impact to physical backpressure.
                                                                 0 = Channel is available.
                                                                 1 = Channel is backpressured. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_tx_ovr_bp_s cn; */
};
typedef union bdk_rgxx_cmrx_tx_ovr_bp bdk_rgxx_cmrx_tx_ovr_bp_t;

static inline uint64_t BDK_RGXX_CMRX_TX_OVR_BP(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_TX_OVR_BP(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000520ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_TX_OVR_BP", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_TX_OVR_BP(a,b) bdk_rgxx_cmrx_tx_ovr_bp_t
#define bustype_BDK_RGXX_CMRX_TX_OVR_BP(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_TX_OVR_BP(a,b) "RGXX_CMRX_TX_OVR_BP"
#define device_bar_BDK_RGXX_CMRX_TX_OVR_BP(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_TX_OVR_BP(a,b) (a)
#define arguments_BDK_RGXX_CMRX_TX_OVR_BP(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_tx_stat0
 *
 * RGX CMR Transmit Statistics Registers 0
 */
union bdk_rgxx_cmrx_tx_stat0
{
    uint64_t u;
    struct bdk_rgxx_cmrx_tx_stat0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t xscol                 : 48; /**< [ 47:  0](R/W/H) Number of packets dropped (never successfully sent) due to excessive collision. Defined by
                                                                 RGX()_GMP_GMI_TX_COL_ATTEMPT[LIMIT]. Half-duplex mode only and does not account for late
                                                                 collisions.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t xscol                 : 48; /**< [ 47:  0](R/W/H) Number of packets dropped (never successfully sent) due to excessive collision. Defined by
                                                                 RGX()_GMP_GMI_TX_COL_ATTEMPT[LIMIT]. Half-duplex mode only and does not account for late
                                                                 collisions.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_tx_stat0_s cn; */
};
typedef union bdk_rgxx_cmrx_tx_stat0 bdk_rgxx_cmrx_tx_stat0_t;

static inline uint64_t BDK_RGXX_CMRX_TX_STAT0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_TX_STAT0(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000600ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_TX_STAT0", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_TX_STAT0(a,b) bdk_rgxx_cmrx_tx_stat0_t
#define bustype_BDK_RGXX_CMRX_TX_STAT0(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_TX_STAT0(a,b) "RGXX_CMRX_TX_STAT0"
#define device_bar_BDK_RGXX_CMRX_TX_STAT0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_TX_STAT0(a,b) (a)
#define arguments_BDK_RGXX_CMRX_TX_STAT0(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_tx_stat1
 *
 * RGX CMR Transmit Statistics Registers 1
 */
union bdk_rgxx_cmrx_tx_stat1
{
    uint64_t u;
    struct bdk_rgxx_cmrx_tx_stat1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t xsdef                 : 48; /**< [ 47:  0](R/W/H) A count of the number of times any frame was deferred for an excessive period of time.
                                                                 See maxDeferTime in the IEEE 802.3 specification. Half-duplex mode only and not updated
                                                                 for late collisions.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t xsdef                 : 48; /**< [ 47:  0](R/W/H) A count of the number of times any frame was deferred for an excessive period of time.
                                                                 See maxDeferTime in the IEEE 802.3 specification. Half-duplex mode only and not updated
                                                                 for late collisions.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_tx_stat1_s cn; */
};
typedef union bdk_rgxx_cmrx_tx_stat1 bdk_rgxx_cmrx_tx_stat1_t;

static inline uint64_t BDK_RGXX_CMRX_TX_STAT1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_TX_STAT1(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000608ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_TX_STAT1", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_TX_STAT1(a,b) bdk_rgxx_cmrx_tx_stat1_t
#define bustype_BDK_RGXX_CMRX_TX_STAT1(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_TX_STAT1(a,b) "RGXX_CMRX_TX_STAT1"
#define device_bar_BDK_RGXX_CMRX_TX_STAT1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_TX_STAT1(a,b) (a)
#define arguments_BDK_RGXX_CMRX_TX_STAT1(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_tx_stat10
 *
 * RGX CMR Transmit Statistics Registers 10
 */
union bdk_rgxx_cmrx_tx_stat10
{
    uint64_t u;
    struct bdk_rgxx_cmrx_tx_stat10_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t hist4                 : 48; /**< [ 47:  0](R/W/H) Number of packets sent with an octet count between 256-511. Packet length is the sum of
                                                                 all data transmitted on the wire for the given packet including packet data, pad bytes,
                                                                 FCS bytes, and JAM bytes. The octet counts do not include PREAMBLE byte or EXTEND cycles.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t hist4                 : 48; /**< [ 47:  0](R/W/H) Number of packets sent with an octet count between 256-511. Packet length is the sum of
                                                                 all data transmitted on the wire for the given packet including packet data, pad bytes,
                                                                 FCS bytes, and JAM bytes. The octet counts do not include PREAMBLE byte or EXTEND cycles.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_tx_stat10_s cn; */
};
typedef union bdk_rgxx_cmrx_tx_stat10 bdk_rgxx_cmrx_tx_stat10_t;

static inline uint64_t BDK_RGXX_CMRX_TX_STAT10(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_TX_STAT10(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000650ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_TX_STAT10", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_TX_STAT10(a,b) bdk_rgxx_cmrx_tx_stat10_t
#define bustype_BDK_RGXX_CMRX_TX_STAT10(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_TX_STAT10(a,b) "RGXX_CMRX_TX_STAT10"
#define device_bar_BDK_RGXX_CMRX_TX_STAT10(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_TX_STAT10(a,b) (a)
#define arguments_BDK_RGXX_CMRX_TX_STAT10(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_tx_stat11
 *
 * RGX CMR Transmit Statistics Registers 11
 */
union bdk_rgxx_cmrx_tx_stat11
{
    uint64_t u;
    struct bdk_rgxx_cmrx_tx_stat11_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t hist5                 : 48; /**< [ 47:  0](R/W/H) Number of packets sent with an octet count between 512-1023. Packet length is the sum of
                                                                 all data transmitted on the wire for the given packet including packet data, pad bytes,
                                                                 FCS bytes, and JAM bytes. The octet counts do not include PREAMBLE byte or EXTEND cycles.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t hist5                 : 48; /**< [ 47:  0](R/W/H) Number of packets sent with an octet count between 512-1023. Packet length is the sum of
                                                                 all data transmitted on the wire for the given packet including packet data, pad bytes,
                                                                 FCS bytes, and JAM bytes. The octet counts do not include PREAMBLE byte or EXTEND cycles.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_tx_stat11_s cn; */
};
typedef union bdk_rgxx_cmrx_tx_stat11 bdk_rgxx_cmrx_tx_stat11_t;

static inline uint64_t BDK_RGXX_CMRX_TX_STAT11(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_TX_STAT11(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000658ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_TX_STAT11", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_TX_STAT11(a,b) bdk_rgxx_cmrx_tx_stat11_t
#define bustype_BDK_RGXX_CMRX_TX_STAT11(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_TX_STAT11(a,b) "RGXX_CMRX_TX_STAT11"
#define device_bar_BDK_RGXX_CMRX_TX_STAT11(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_TX_STAT11(a,b) (a)
#define arguments_BDK_RGXX_CMRX_TX_STAT11(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_tx_stat12
 *
 * RGX CMR Transmit Statistics Registers 12
 */
union bdk_rgxx_cmrx_tx_stat12
{
    uint64_t u;
    struct bdk_rgxx_cmrx_tx_stat12_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t hist6                 : 48; /**< [ 47:  0](R/W/H) Number of packets sent with an octet count between 1024-1518. Packet length is the sum of
                                                                 all data transmitted on the wire for the given packet including packet data, pad bytes,
                                                                 FCS bytes, and JAM bytes. The octet counts do not include PREAMBLE byte or EXTEND cycles.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t hist6                 : 48; /**< [ 47:  0](R/W/H) Number of packets sent with an octet count between 1024-1518. Packet length is the sum of
                                                                 all data transmitted on the wire for the given packet including packet data, pad bytes,
                                                                 FCS bytes, and JAM bytes. The octet counts do not include PREAMBLE byte or EXTEND cycles.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_tx_stat12_s cn; */
};
typedef union bdk_rgxx_cmrx_tx_stat12 bdk_rgxx_cmrx_tx_stat12_t;

static inline uint64_t BDK_RGXX_CMRX_TX_STAT12(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_TX_STAT12(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000660ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_TX_STAT12", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_TX_STAT12(a,b) bdk_rgxx_cmrx_tx_stat12_t
#define bustype_BDK_RGXX_CMRX_TX_STAT12(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_TX_STAT12(a,b) "RGXX_CMRX_TX_STAT12"
#define device_bar_BDK_RGXX_CMRX_TX_STAT12(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_TX_STAT12(a,b) (a)
#define arguments_BDK_RGXX_CMRX_TX_STAT12(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_tx_stat13
 *
 * RGX CMR Transmit Statistics Registers 13
 */
union bdk_rgxx_cmrx_tx_stat13
{
    uint64_t u;
    struct bdk_rgxx_cmrx_tx_stat13_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t hist7                 : 48; /**< [ 47:  0](R/W/H) Number of packets sent with an octet count \> 1518. Packet length is the sum of all data
                                                                 transmitted on the wire for the given packet including packet data, pad bytes, FCS bytes,
                                                                 and JAM bytes. The octet counts do not include PREAMBLE byte or EXTEND cycles.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t hist7                 : 48; /**< [ 47:  0](R/W/H) Number of packets sent with an octet count \> 1518. Packet length is the sum of all data
                                                                 transmitted on the wire for the given packet including packet data, pad bytes, FCS bytes,
                                                                 and JAM bytes. The octet counts do not include PREAMBLE byte or EXTEND cycles.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_tx_stat13_s cn; */
};
typedef union bdk_rgxx_cmrx_tx_stat13 bdk_rgxx_cmrx_tx_stat13_t;

static inline uint64_t BDK_RGXX_CMRX_TX_STAT13(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_TX_STAT13(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000668ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_TX_STAT13", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_TX_STAT13(a,b) bdk_rgxx_cmrx_tx_stat13_t
#define bustype_BDK_RGXX_CMRX_TX_STAT13(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_TX_STAT13(a,b) "RGXX_CMRX_TX_STAT13"
#define device_bar_BDK_RGXX_CMRX_TX_STAT13(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_TX_STAT13(a,b) (a)
#define arguments_BDK_RGXX_CMRX_TX_STAT13(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_tx_stat14
 *
 * RGX CMR Transmit Statistics Registers 14
 */
union bdk_rgxx_cmrx_tx_stat14
{
    uint64_t u;
    struct bdk_rgxx_cmrx_tx_stat14_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t bcst                  : 48; /**< [ 47:  0](R/W/H) Number of packets sent to broadcast DMAC, excluding PAUSE or PFC control packets generated
                                                                 by RGX. Does not include MCST packets.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap.

                                                                 Note that RGX determines if the packet is MCST or BCST from the DMAC of the packet. RGX
                                                                 assumes that the DMAC lies in the first six bytes of the packet as per the 802.3 frame
                                                                 definition. If the system requires additional data before the L2 header, the MCST and BCST
                                                                 counters may not reflect reality and should be ignored by software. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t bcst                  : 48; /**< [ 47:  0](R/W/H) Number of packets sent to broadcast DMAC, excluding PAUSE or PFC control packets generated
                                                                 by RGX. Does not include MCST packets.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap.

                                                                 Note that RGX determines if the packet is MCST or BCST from the DMAC of the packet. RGX
                                                                 assumes that the DMAC lies in the first six bytes of the packet as per the 802.3 frame
                                                                 definition. If the system requires additional data before the L2 header, the MCST and BCST
                                                                 counters may not reflect reality and should be ignored by software. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_tx_stat14_s cn; */
};
typedef union bdk_rgxx_cmrx_tx_stat14 bdk_rgxx_cmrx_tx_stat14_t;

static inline uint64_t BDK_RGXX_CMRX_TX_STAT14(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_TX_STAT14(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000670ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_TX_STAT14", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_TX_STAT14(a,b) bdk_rgxx_cmrx_tx_stat14_t
#define bustype_BDK_RGXX_CMRX_TX_STAT14(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_TX_STAT14(a,b) "RGXX_CMRX_TX_STAT14"
#define device_bar_BDK_RGXX_CMRX_TX_STAT14(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_TX_STAT14(a,b) (a)
#define arguments_BDK_RGXX_CMRX_TX_STAT14(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_tx_stat15
 *
 * RGX CMR Transmit Statistics Registers 15
 */
union bdk_rgxx_cmrx_tx_stat15
{
    uint64_t u;
    struct bdk_rgxx_cmrx_tx_stat15_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t mcst                  : 48; /**< [ 47:  0](R/W/H) Number of packets sent to multicast DMAC, excluding PAUSE or PFC control packets generated
                                                                 by RGX. Does not include BCST packets.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap.

                                                                 Note that RGX determines if the packet is MCST or BCST from the DMAC of the packet. RGX
                                                                 assumes that the DMAC lies in the first six bytes of the packet as per the 802.3 frame
                                                                 definition. If the system requires additional data before the L2 header, then the MCST and
                                                                 BCST counters may not reflect reality and should be ignored by software. Cleared if LMAC
                                                                 is disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t mcst                  : 48; /**< [ 47:  0](R/W/H) Number of packets sent to multicast DMAC, excluding PAUSE or PFC control packets generated
                                                                 by RGX. Does not include BCST packets.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap.

                                                                 Note that RGX determines if the packet is MCST or BCST from the DMAC of the packet. RGX
                                                                 assumes that the DMAC lies in the first six bytes of the packet as per the 802.3 frame
                                                                 definition. If the system requires additional data before the L2 header, then the MCST and
                                                                 BCST counters may not reflect reality and should be ignored by software. Cleared if LMAC
                                                                 is disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_tx_stat15_s cn; */
};
typedef union bdk_rgxx_cmrx_tx_stat15 bdk_rgxx_cmrx_tx_stat15_t;

static inline uint64_t BDK_RGXX_CMRX_TX_STAT15(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_TX_STAT15(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000678ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_TX_STAT15", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_TX_STAT15(a,b) bdk_rgxx_cmrx_tx_stat15_t
#define bustype_BDK_RGXX_CMRX_TX_STAT15(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_TX_STAT15(a,b) "RGXX_CMRX_TX_STAT15"
#define device_bar_BDK_RGXX_CMRX_TX_STAT15(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_TX_STAT15(a,b) (a)
#define arguments_BDK_RGXX_CMRX_TX_STAT15(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_tx_stat16
 *
 * RGX CMR Transmit Statistics Registers 16
 */
union bdk_rgxx_cmrx_tx_stat16
{
    uint64_t u;
    struct bdk_rgxx_cmrx_tx_stat16_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t undflw                : 48; /**< [ 47:  0](R/W/H) Number of underflow packets.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t undflw                : 48; /**< [ 47:  0](R/W/H) Number of underflow packets.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_tx_stat16_s cn; */
};
typedef union bdk_rgxx_cmrx_tx_stat16 bdk_rgxx_cmrx_tx_stat16_t;

static inline uint64_t BDK_RGXX_CMRX_TX_STAT16(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_TX_STAT16(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000680ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_TX_STAT16", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_TX_STAT16(a,b) bdk_rgxx_cmrx_tx_stat16_t
#define bustype_BDK_RGXX_CMRX_TX_STAT16(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_TX_STAT16(a,b) "RGXX_CMRX_TX_STAT16"
#define device_bar_BDK_RGXX_CMRX_TX_STAT16(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_TX_STAT16(a,b) (a)
#define arguments_BDK_RGXX_CMRX_TX_STAT16(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_tx_stat17
 *
 * RGX CMR Transmit Statistics Registers 17
 */
union bdk_rgxx_cmrx_tx_stat17
{
    uint64_t u;
    struct bdk_rgxx_cmrx_tx_stat17_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t ctl                   : 48; /**< [ 47:  0](R/W/H) Number of PAUSE or PFC control packets generated by RGX. It does not include control
                                                                 packets forwarded or generated by the cores. Does not track the number of generated HG2
                                                                 messages.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t ctl                   : 48; /**< [ 47:  0](R/W/H) Number of PAUSE or PFC control packets generated by RGX. It does not include control
                                                                 packets forwarded or generated by the cores. Does not track the number of generated HG2
                                                                 messages.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_tx_stat17_s cn; */
};
typedef union bdk_rgxx_cmrx_tx_stat17 bdk_rgxx_cmrx_tx_stat17_t;

static inline uint64_t BDK_RGXX_CMRX_TX_STAT17(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_TX_STAT17(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000688ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_TX_STAT17", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_TX_STAT17(a,b) bdk_rgxx_cmrx_tx_stat17_t
#define bustype_BDK_RGXX_CMRX_TX_STAT17(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_TX_STAT17(a,b) "RGXX_CMRX_TX_STAT17"
#define device_bar_BDK_RGXX_CMRX_TX_STAT17(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_TX_STAT17(a,b) (a)
#define arguments_BDK_RGXX_CMRX_TX_STAT17(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_tx_stat2
 *
 * RGX CMR Transmit Statistics Registers 2
 */
union bdk_rgxx_cmrx_tx_stat2
{
    uint64_t u;
    struct bdk_rgxx_cmrx_tx_stat2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t mcol                  : 48; /**< [ 47:  0](R/W/H) Number of packets sent with multiple collisions. Must be less than
                                                                 RGX()_GMP_GMI_TX_COL_ATTEMPT[LIMIT]. Half-duplex mode only and not updated
                                                                 for late collisions.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t mcol                  : 48; /**< [ 47:  0](R/W/H) Number of packets sent with multiple collisions. Must be less than
                                                                 RGX()_GMP_GMI_TX_COL_ATTEMPT[LIMIT]. Half-duplex mode only and not updated
                                                                 for late collisions.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_tx_stat2_s cn; */
};
typedef union bdk_rgxx_cmrx_tx_stat2 bdk_rgxx_cmrx_tx_stat2_t;

static inline uint64_t BDK_RGXX_CMRX_TX_STAT2(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_TX_STAT2(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000610ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_TX_STAT2", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_TX_STAT2(a,b) bdk_rgxx_cmrx_tx_stat2_t
#define bustype_BDK_RGXX_CMRX_TX_STAT2(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_TX_STAT2(a,b) "RGXX_CMRX_TX_STAT2"
#define device_bar_BDK_RGXX_CMRX_TX_STAT2(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_TX_STAT2(a,b) (a)
#define arguments_BDK_RGXX_CMRX_TX_STAT2(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_tx_stat3
 *
 * RGX CMR Transmit Statistics Registers 3
 */
union bdk_rgxx_cmrx_tx_stat3
{
    uint64_t u;
    struct bdk_rgxx_cmrx_tx_stat3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t scol                  : 48; /**< [ 47:  0](R/W/H) Number of packets sent with a single collision. Half-duplex mode only and not updated
                                                                 for late collisions.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t scol                  : 48; /**< [ 47:  0](R/W/H) Number of packets sent with a single collision. Half-duplex mode only and not updated
                                                                 for late collisions.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_tx_stat3_s cn; */
};
typedef union bdk_rgxx_cmrx_tx_stat3 bdk_rgxx_cmrx_tx_stat3_t;

static inline uint64_t BDK_RGXX_CMRX_TX_STAT3(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_TX_STAT3(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000618ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_TX_STAT3", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_TX_STAT3(a,b) bdk_rgxx_cmrx_tx_stat3_t
#define bustype_BDK_RGXX_CMRX_TX_STAT3(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_TX_STAT3(a,b) "RGXX_CMRX_TX_STAT3"
#define device_bar_BDK_RGXX_CMRX_TX_STAT3(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_TX_STAT3(a,b) (a)
#define arguments_BDK_RGXX_CMRX_TX_STAT3(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_tx_stat4
 *
 * RGX CMR Transmit Statistics Registers 4
 */
union bdk_rgxx_cmrx_tx_stat4
{
    uint64_t u;
    struct bdk_rgxx_cmrx_tx_stat4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t octs                  : 48; /**< [ 47:  0](R/W/H) Number of total octets sent on the interface, excluding PAUSE or PFC control packets
                                                                 generated by RGX. Does not count octets from frames that were truncated due to collisions
                                                                 in half-duplex mode.
                                                                 Octet counts are the sum of all data transmitted on the wire including packet data, pad
                                                                 bytes, FCS bytes, and JAM bytes. The octet counts do not include PREAMBLE byte or EXTEND
                                                                 cycles.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t octs                  : 48; /**< [ 47:  0](R/W/H) Number of total octets sent on the interface, excluding PAUSE or PFC control packets
                                                                 generated by RGX. Does not count octets from frames that were truncated due to collisions
                                                                 in half-duplex mode.
                                                                 Octet counts are the sum of all data transmitted on the wire including packet data, pad
                                                                 bytes, FCS bytes, and JAM bytes. The octet counts do not include PREAMBLE byte or EXTEND
                                                                 cycles.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_tx_stat4_s cn; */
};
typedef union bdk_rgxx_cmrx_tx_stat4 bdk_rgxx_cmrx_tx_stat4_t;

static inline uint64_t BDK_RGXX_CMRX_TX_STAT4(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_TX_STAT4(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000620ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_TX_STAT4", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_TX_STAT4(a,b) bdk_rgxx_cmrx_tx_stat4_t
#define bustype_BDK_RGXX_CMRX_TX_STAT4(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_TX_STAT4(a,b) "RGXX_CMRX_TX_STAT4"
#define device_bar_BDK_RGXX_CMRX_TX_STAT4(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_TX_STAT4(a,b) (a)
#define arguments_BDK_RGXX_CMRX_TX_STAT4(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_tx_stat5
 *
 * RGX CMR Transmit Statistics Registers 5
 */
union bdk_rgxx_cmrx_tx_stat5
{
    uint64_t u;
    struct bdk_rgxx_cmrx_tx_stat5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t pkts                  : 48; /**< [ 47:  0](R/W/H) Number of total frames sent on the interface, excluding PAUSE or PFC control packets
                                                                 generated by RGX. Does not count octets from frames that were truncated due to collisions
                                                                 in half-duplex mode.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t pkts                  : 48; /**< [ 47:  0](R/W/H) Number of total frames sent on the interface, excluding PAUSE or PFC control packets
                                                                 generated by RGX. Does not count octets from frames that were truncated due to collisions
                                                                 in half-duplex mode.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_tx_stat5_s cn; */
};
typedef union bdk_rgxx_cmrx_tx_stat5 bdk_rgxx_cmrx_tx_stat5_t;

static inline uint64_t BDK_RGXX_CMRX_TX_STAT5(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_TX_STAT5(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000628ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_TX_STAT5", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_TX_STAT5(a,b) bdk_rgxx_cmrx_tx_stat5_t
#define bustype_BDK_RGXX_CMRX_TX_STAT5(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_TX_STAT5(a,b) "RGXX_CMRX_TX_STAT5"
#define device_bar_BDK_RGXX_CMRX_TX_STAT5(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_TX_STAT5(a,b) (a)
#define arguments_BDK_RGXX_CMRX_TX_STAT5(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_tx_stat6
 *
 * RGX CMR Transmit Statistics Registers 6
 */
union bdk_rgxx_cmrx_tx_stat6
{
    uint64_t u;
    struct bdk_rgxx_cmrx_tx_stat6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t hist0                 : 48; /**< [ 47:  0](R/W/H) Number of packets sent with an octet count \< 64, excluding PAUSE or PFC control packets
                                                                 generated by RGX. Packet length is the sum of all data transmitted on the wire for the
                                                                 given packet including packet data, pad bytes, FCS bytes, and JAM bytes. The octet counts
                                                                 do not include PREAMBLE byte or EXTEND cycles.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t hist0                 : 48; /**< [ 47:  0](R/W/H) Number of packets sent with an octet count \< 64, excluding PAUSE or PFC control packets
                                                                 generated by RGX. Packet length is the sum of all data transmitted on the wire for the
                                                                 given packet including packet data, pad bytes, FCS bytes, and JAM bytes. The octet counts
                                                                 do not include PREAMBLE byte or EXTEND cycles.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_tx_stat6_s cn; */
};
typedef union bdk_rgxx_cmrx_tx_stat6 bdk_rgxx_cmrx_tx_stat6_t;

static inline uint64_t BDK_RGXX_CMRX_TX_STAT6(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_TX_STAT6(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000630ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_TX_STAT6", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_TX_STAT6(a,b) bdk_rgxx_cmrx_tx_stat6_t
#define bustype_BDK_RGXX_CMRX_TX_STAT6(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_TX_STAT6(a,b) "RGXX_CMRX_TX_STAT6"
#define device_bar_BDK_RGXX_CMRX_TX_STAT6(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_TX_STAT6(a,b) (a)
#define arguments_BDK_RGXX_CMRX_TX_STAT6(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_tx_stat7
 *
 * RGX CMR Transmit Statistics Registers 7
 */
union bdk_rgxx_cmrx_tx_stat7
{
    uint64_t u;
    struct bdk_rgxx_cmrx_tx_stat7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t hist1                 : 48; /**< [ 47:  0](R/W/H) Number of packets sent with an octet count of 64, excluding PAUSE or PFC control packets
                                                                 generated by RGX. Packet length is the sum of all data transmitted on the wire for the
                                                                 given packet including packet data, pad bytes, FCS bytes, and JAM bytes. The octet counts
                                                                 do not include PREAMBLE byte or EXTEND cycles.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t hist1                 : 48; /**< [ 47:  0](R/W/H) Number of packets sent with an octet count of 64, excluding PAUSE or PFC control packets
                                                                 generated by RGX. Packet length is the sum of all data transmitted on the wire for the
                                                                 given packet including packet data, pad bytes, FCS bytes, and JAM bytes. The octet counts
                                                                 do not include PREAMBLE byte or EXTEND cycles.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_tx_stat7_s cn; */
};
typedef union bdk_rgxx_cmrx_tx_stat7 bdk_rgxx_cmrx_tx_stat7_t;

static inline uint64_t BDK_RGXX_CMRX_TX_STAT7(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_TX_STAT7(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000638ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_TX_STAT7", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_TX_STAT7(a,b) bdk_rgxx_cmrx_tx_stat7_t
#define bustype_BDK_RGXX_CMRX_TX_STAT7(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_TX_STAT7(a,b) "RGXX_CMRX_TX_STAT7"
#define device_bar_BDK_RGXX_CMRX_TX_STAT7(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_TX_STAT7(a,b) (a)
#define arguments_BDK_RGXX_CMRX_TX_STAT7(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_tx_stat8
 *
 * RGX CMR Transmit Statistics Registers 8
 */
union bdk_rgxx_cmrx_tx_stat8
{
    uint64_t u;
    struct bdk_rgxx_cmrx_tx_stat8_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t hist2                 : 48; /**< [ 47:  0](R/W/H) Number of packets sent with an octet count between 65-127. Packet length is the sum of all
                                                                 data transmitted on the wire for the given packet including packet data, pad bytes, FCS
                                                                 bytes, and JAM bytes. The octet counts do not include PREAMBLE byte or EXTEND cycles.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t hist2                 : 48; /**< [ 47:  0](R/W/H) Number of packets sent with an octet count between 65-127. Packet length is the sum of all
                                                                 data transmitted on the wire for the given packet including packet data, pad bytes, FCS
                                                                 bytes, and JAM bytes. The octet counts do not include PREAMBLE byte or EXTEND cycles.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_tx_stat8_s cn; */
};
typedef union bdk_rgxx_cmrx_tx_stat8 bdk_rgxx_cmrx_tx_stat8_t;

static inline uint64_t BDK_RGXX_CMRX_TX_STAT8(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_TX_STAT8(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000640ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_TX_STAT8", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_TX_STAT8(a,b) bdk_rgxx_cmrx_tx_stat8_t
#define bustype_BDK_RGXX_CMRX_TX_STAT8(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_TX_STAT8(a,b) "RGXX_CMRX_TX_STAT8"
#define device_bar_BDK_RGXX_CMRX_TX_STAT8(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_TX_STAT8(a,b) (a)
#define arguments_BDK_RGXX_CMRX_TX_STAT8(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr#_tx_stat9
 *
 * RGX CMR Transmit Statistics Registers 9
 */
union bdk_rgxx_cmrx_tx_stat9
{
    uint64_t u;
    struct bdk_rgxx_cmrx_tx_stat9_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t hist3                 : 48; /**< [ 47:  0](R/W/H) Number of packets sent with an octet count between 128-255. Packet length is the sum of
                                                                 all data transmitted on the wire for the given packet including packet data, pad bytes,
                                                                 FCS bytes, and JAM bytes. The octet counts do not include PREAMBLE byte or EXTEND cycles.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
#else /* Word 0 - Little Endian */
        uint64_t hist3                 : 48; /**< [ 47:  0](R/W/H) Number of packets sent with an octet count between 128-255. Packet length is the sum of
                                                                 all data transmitted on the wire for the given packet including packet data, pad bytes,
                                                                 FCS bytes, and JAM bytes. The octet counts do not include PREAMBLE byte or EXTEND cycles.

                                                                 Not cleared on read; cleared on a write with 0x0. Counters will wrap. Cleared if LMAC is
                                                                 disabled with RGX()_CMR()_CONFIG[ENABLE]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmrx_tx_stat9_s cn; */
};
typedef union bdk_rgxx_cmrx_tx_stat9 bdk_rgxx_cmrx_tx_stat9_t;

static inline uint64_t BDK_RGXX_CMRX_TX_STAT9(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMRX_TX_STAT9(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8000648ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_CMRX_TX_STAT9", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMRX_TX_STAT9(a,b) bdk_rgxx_cmrx_tx_stat9_t
#define bustype_BDK_RGXX_CMRX_TX_STAT9(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMRX_TX_STAT9(a,b) "RGXX_CMRX_TX_STAT9"
#define device_bar_BDK_RGXX_CMRX_TX_STAT9(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMRX_TX_STAT9(a,b) (a)
#define arguments_BDK_RGXX_CMRX_TX_STAT9(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr_bad
 *
 * RGX CMR Bad Registers
 */
union bdk_rgxx_cmr_bad
{
    uint64_t u;
    struct bdk_rgxx_cmr_bad_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t rxb_nxl               : 1;  /**< [  0:  0](R/W1C/H) Receive side LMAC ID \> RGX()_CMR_RX_LMACS. */
#else /* Word 0 - Little Endian */
        uint64_t rxb_nxl               : 1;  /**< [  0:  0](R/W1C/H) Receive side LMAC ID \> RGX()_CMR_RX_LMACS. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmr_bad_s cn; */
};
typedef union bdk_rgxx_cmr_bad bdk_rgxx_cmr_bad_t;

static inline uint64_t BDK_RGXX_CMR_BAD(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMR_BAD(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8001020ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_CMR_BAD", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMR_BAD(a) bdk_rgxx_cmr_bad_t
#define bustype_BDK_RGXX_CMR_BAD(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMR_BAD(a) "RGXX_CMR_BAD"
#define device_bar_BDK_RGXX_CMR_BAD(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMR_BAD(a) (a)
#define arguments_BDK_RGXX_CMR_BAD(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_cmr_bist_status
 *
 * RGX Built-in Self-Test Registers
 */
union bdk_rgxx_cmr_bist_status
{
    uint64_t u;
    struct bdk_rgxx_cmr_bist_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_25_63        : 39;
        uint64_t status                : 25; /**< [ 24:  0](RO/H) '"BIST results. Hardware sets a bit to 1 for memory that fails; 0 indicates pass or never
                                                                 run.'

                                                                 Internal:
                                                                 "\<0\> = bgx#.rxb.infif_gmp.
                                                                 \<1\> = bgx#.rxb.infif_smu.
                                                                 \<2\> = bgx#.rxb.fif_bnk00.
                                                                 \<3\> = bgx#.rxb.fif_bnk01.
                                                                 \<4\> = bgx#.rxb.fif_bnk10.
                                                                 \<5\> = bgx#.rxb.fif_bnk11.
                                                                 \<6\> = bgx#.rxb.pki_skd_fif.
                                                                 \<7\> = bgx#.rxb.nic_skd_fif.
                                                                 \<8\> = bgx#.rxb_mix0_fif.
                                                                 \<9\> = bgx#.rxb_mix1_fif.
                                                                 \<10\> = 0.
                                                                 \<11\> = bgx#.txb_fif_bnk0.
                                                                 \<12\> = bgx#.txb_fif_bnk1.
                                                                 \<13\> = bgx#.txb_skd_m0_pko_fif.
                                                                 \<14\> = bgx#.txb_skd_m1_pko_fif.
                                                                 \<15\> = bgx#.txb_skd_m2_pko_fif.
                                                                 \<16\> = bgx#.txb_skd_m3_pko_fif.
                                                                 \<17\> = bgx#.txb_skd_m0_nic_fif.
                                                                 \<18\> = bgx#.txb_skd_m1_nic_fif.
                                                                 \<19\> = bgx#.txb_skd_m2_nic_fif.
                                                                 \<20\> = bgx#.txb_skd_m3_nic_fif.
                                                                 \<21\> = bgx#.txb_mix0_fif.
                                                                 \<22\> = bgx#.txb_mix1_fif.
                                                                 \<23\> = bgx#.txb_ncsi_fif.
                                                                 \<24\> = 0." */
#else /* Word 0 - Little Endian */
        uint64_t status                : 25; /**< [ 24:  0](RO/H) '"BIST results. Hardware sets a bit to 1 for memory that fails; 0 indicates pass or never
                                                                 run.'

                                                                 Internal:
                                                                 "\<0\> = bgx#.rxb.infif_gmp.
                                                                 \<1\> = bgx#.rxb.infif_smu.
                                                                 \<2\> = bgx#.rxb.fif_bnk00.
                                                                 \<3\> = bgx#.rxb.fif_bnk01.
                                                                 \<4\> = bgx#.rxb.fif_bnk10.
                                                                 \<5\> = bgx#.rxb.fif_bnk11.
                                                                 \<6\> = bgx#.rxb.pki_skd_fif.
                                                                 \<7\> = bgx#.rxb.nic_skd_fif.
                                                                 \<8\> = bgx#.rxb_mix0_fif.
                                                                 \<9\> = bgx#.rxb_mix1_fif.
                                                                 \<10\> = 0.
                                                                 \<11\> = bgx#.txb_fif_bnk0.
                                                                 \<12\> = bgx#.txb_fif_bnk1.
                                                                 \<13\> = bgx#.txb_skd_m0_pko_fif.
                                                                 \<14\> = bgx#.txb_skd_m1_pko_fif.
                                                                 \<15\> = bgx#.txb_skd_m2_pko_fif.
                                                                 \<16\> = bgx#.txb_skd_m3_pko_fif.
                                                                 \<17\> = bgx#.txb_skd_m0_nic_fif.
                                                                 \<18\> = bgx#.txb_skd_m1_nic_fif.
                                                                 \<19\> = bgx#.txb_skd_m2_nic_fif.
                                                                 \<20\> = bgx#.txb_skd_m3_nic_fif.
                                                                 \<21\> = bgx#.txb_mix0_fif.
                                                                 \<22\> = bgx#.txb_mix1_fif.
                                                                 \<23\> = bgx#.txb_ncsi_fif.
                                                                 \<24\> = 0." */
        uint64_t reserved_25_63        : 39;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmr_bist_status_s cn; */
};
typedef union bdk_rgxx_cmr_bist_status bdk_rgxx_cmr_bist_status_t;

static inline uint64_t BDK_RGXX_CMR_BIST_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMR_BIST_STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8000460ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_CMR_BIST_STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMR_BIST_STATUS(a) bdk_rgxx_cmr_bist_status_t
#define bustype_BDK_RGXX_CMR_BIST_STATUS(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMR_BIST_STATUS(a) "RGXX_CMR_BIST_STATUS"
#define device_bar_BDK_RGXX_CMR_BIST_STATUS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMR_BIST_STATUS(a) (a)
#define arguments_BDK_RGXX_CMR_BIST_STATUS(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_cmr_chan_msk_and
 *
 * RGX CMR Backpressure Channel Mask AND Registers
 */
union bdk_rgxx_cmr_chan_msk_and
{
    uint64_t u;
    struct bdk_rgxx_cmr_chan_msk_and_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t msk_and               : 64; /**< [ 63:  0](R/W) Assert physical backpressure when the backpressure channel vector combined with [MSK_AND]
                                                                 indicates backpressure as follows:
                                                                 _ phys_bp_msk_and = [MSK_AND]\<x:y\> != 0 && (chan_vector\<x:y\> & [MSK_AND]\<x:y\>) ==
                                                                 [MSK_AND]\<x:y\>
                                                                 _ phys_bp = phys_bp_msk_or || phys_bp_msk_and

                                                                 x/y are as follows:
                                                                 _ LMAC 0: \<x:y\> = \<15:0\>.

                                                                 Bits \<63:16\> are reserved. */
#else /* Word 0 - Little Endian */
        uint64_t msk_and               : 64; /**< [ 63:  0](R/W) Assert physical backpressure when the backpressure channel vector combined with [MSK_AND]
                                                                 indicates backpressure as follows:
                                                                 _ phys_bp_msk_and = [MSK_AND]\<x:y\> != 0 && (chan_vector\<x:y\> & [MSK_AND]\<x:y\>) ==
                                                                 [MSK_AND]\<x:y\>
                                                                 _ phys_bp = phys_bp_msk_or || phys_bp_msk_and

                                                                 x/y are as follows:
                                                                 _ LMAC 0: \<x:y\> = \<15:0\>.

                                                                 Bits \<63:16\> are reserved. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmr_chan_msk_and_s cn; */
};
typedef union bdk_rgxx_cmr_chan_msk_and bdk_rgxx_cmr_chan_msk_and_t;

static inline uint64_t BDK_RGXX_CMR_CHAN_MSK_AND(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMR_CHAN_MSK_AND(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8000450ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_CMR_CHAN_MSK_AND", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMR_CHAN_MSK_AND(a) bdk_rgxx_cmr_chan_msk_and_t
#define bustype_BDK_RGXX_CMR_CHAN_MSK_AND(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMR_CHAN_MSK_AND(a) "RGXX_CMR_CHAN_MSK_AND"
#define device_bar_BDK_RGXX_CMR_CHAN_MSK_AND(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMR_CHAN_MSK_AND(a) (a)
#define arguments_BDK_RGXX_CMR_CHAN_MSK_AND(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_cmr_chan_msk_or
 *
 * RGX Backpressure Channel Mask OR Registers
 */
union bdk_rgxx_cmr_chan_msk_or
{
    uint64_t u;
    struct bdk_rgxx_cmr_chan_msk_or_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t msk_or                : 64; /**< [ 63:  0](R/W) Assert physical backpressure when the backpressure channel vector combined with [MSK_OR]
                                                                 indicates backpressure as follows:

                                                                 _ phys_bp_msk_or = (chan_vector\<x:y\> & [MSK_OR]\<x:y\>) != 0
                                                                 _ phys_bp = phys_bp_msk_or || phys_bp_msk_and

                                                                 x/y are as follows:
                                                                 _ LMAC 0: \<x:y\> = \<15:0\>.

                                                                 Bits \<63:16\> are reserved. */
#else /* Word 0 - Little Endian */
        uint64_t msk_or                : 64; /**< [ 63:  0](R/W) Assert physical backpressure when the backpressure channel vector combined with [MSK_OR]
                                                                 indicates backpressure as follows:

                                                                 _ phys_bp_msk_or = (chan_vector\<x:y\> & [MSK_OR]\<x:y\>) != 0
                                                                 _ phys_bp = phys_bp_msk_or || phys_bp_msk_and

                                                                 x/y are as follows:
                                                                 _ LMAC 0: \<x:y\> = \<15:0\>.

                                                                 Bits \<63:16\> are reserved. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmr_chan_msk_or_s cn; */
};
typedef union bdk_rgxx_cmr_chan_msk_or bdk_rgxx_cmr_chan_msk_or_t;

static inline uint64_t BDK_RGXX_CMR_CHAN_MSK_OR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMR_CHAN_MSK_OR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8000458ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_CMR_CHAN_MSK_OR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMR_CHAN_MSK_OR(a) bdk_rgxx_cmr_chan_msk_or_t
#define bustype_BDK_RGXX_CMR_CHAN_MSK_OR(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMR_CHAN_MSK_OR(a) "RGXX_CMR_CHAN_MSK_OR"
#define device_bar_BDK_RGXX_CMR_CHAN_MSK_OR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMR_CHAN_MSK_OR(a) (a)
#define arguments_BDK_RGXX_CMR_CHAN_MSK_OR(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_cmr_eco
 *
 * INTERNAL: RGX ECO Registers
 */
union bdk_rgxx_cmr_eco
{
    uint64_t u;
    struct bdk_rgxx_cmr_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t eco_ro                : 32; /**< [ 63: 32](RO) Internal:
                                                                 Reserved for ECO usage. */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
        uint64_t eco_ro                : 32; /**< [ 63: 32](RO) Internal:
                                                                 Reserved for ECO usage. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmr_eco_s cn; */
};
typedef union bdk_rgxx_cmr_eco bdk_rgxx_cmr_eco_t;

static inline uint64_t BDK_RGXX_CMR_ECO(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMR_ECO(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8001028ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_CMR_ECO", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMR_ECO(a) bdk_rgxx_cmr_eco_t
#define bustype_BDK_RGXX_CMR_ECO(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMR_ECO(a) "RGXX_CMR_ECO"
#define device_bar_BDK_RGXX_CMR_ECO(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMR_ECO(a) (a)
#define arguments_BDK_RGXX_CMR_ECO(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_cmr_global_config
 *
 * RGX CMR Global Configuration Register
 * These registers configure the global CMR and MAC.
 */
union bdk_rgxx_cmr_global_config
{
    uint64_t u;
    struct bdk_rgxx_cmr_global_config_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t cmr_ncsi_reset        : 1;  /**< [ 10: 10](R/W) Reserved. */
        uint64_t cmr_ncsi_drop         : 1;  /**< [  9:  9](R/W) Reserved. */
        uint64_t ncsi_lmac_id          : 2;  /**< [  8:  7](R/W) Reserved. */
        uint64_t fcs_strip             : 1;  /**< [  6:  6](R/W) A setting of 1 means the RGX strip the FCS bytes of every packet.  For packets less than 4
                                                                 bytes, the packet will be removed.
                                                                 A setting of 0 means the RGX will not modify or remove the FCS bytes. */
        uint64_t interleave_mode       : 1;  /**< [  5:  5](RAZ) Reserved. */
        uint64_t cmr_mix1_reset        : 1;  /**< [  4:  4](R/W) Must be 0. */
        uint64_t cmr_mix0_reset        : 1;  /**< [  3:  3](R/W) Must be 0. */
        uint64_t cmr_x2p_reset         : 1;  /**< [  2:  2](R/W) If the NIC block is reset, software also needs to reset the X2P interface in the
                                                                 RGX by
                                                                 setting this bit to 1. It resets the X2P interface state in the RGX (skid FIFO and pending
                                                                 requests to NIC) and prevents the RXB FIFOs for all LMACs from pushing data to the
                                                                 interface.

                                                                 Setting this bit to 0 does not reset the X2P interface.
                                                                 After NIC comes out of reset, software should clear this bit. */
        uint64_t rgx_clk_enable        : 1;  /**< [  1:  1](R/W) The global clock enable for RGX. Setting this bit overrides clock enables set by
                                                                 RGX()_CMR()_CONFIG[ENABLE] and RGX()_CMR()_CONFIG[LMAC_TYPE], essentially
                                                                 turning on clocks for the entire RGX. Setting this bit to 0 results in not overriding
                                                                 clock enables set by RGX()_CMR()_CONFIG[ENABLE] and
                                                                 RGX()_CMR()_CONFIG[LMAC_TYPE]. */
        uint64_t pmux_sds_sel          : 1;  /**< [  0:  0](R/W) SerDes/GSER output select. Must be 0. */
#else /* Word 0 - Little Endian */
        uint64_t pmux_sds_sel          : 1;  /**< [  0:  0](R/W) SerDes/GSER output select. Must be 0. */
        uint64_t rgx_clk_enable        : 1;  /**< [  1:  1](R/W) The global clock enable for RGX. Setting this bit overrides clock enables set by
                                                                 RGX()_CMR()_CONFIG[ENABLE] and RGX()_CMR()_CONFIG[LMAC_TYPE], essentially
                                                                 turning on clocks for the entire RGX. Setting this bit to 0 results in not overriding
                                                                 clock enables set by RGX()_CMR()_CONFIG[ENABLE] and
                                                                 RGX()_CMR()_CONFIG[LMAC_TYPE]. */
        uint64_t cmr_x2p_reset         : 1;  /**< [  2:  2](R/W) If the NIC block is reset, software also needs to reset the X2P interface in the
                                                                 RGX by
                                                                 setting this bit to 1. It resets the X2P interface state in the RGX (skid FIFO and pending
                                                                 requests to NIC) and prevents the RXB FIFOs for all LMACs from pushing data to the
                                                                 interface.

                                                                 Setting this bit to 0 does not reset the X2P interface.
                                                                 After NIC comes out of reset, software should clear this bit. */
        uint64_t cmr_mix0_reset        : 1;  /**< [  3:  3](R/W) Must be 0. */
        uint64_t cmr_mix1_reset        : 1;  /**< [  4:  4](R/W) Must be 0. */
        uint64_t interleave_mode       : 1;  /**< [  5:  5](RAZ) Reserved. */
        uint64_t fcs_strip             : 1;  /**< [  6:  6](R/W) A setting of 1 means the RGX strip the FCS bytes of every packet.  For packets less than 4
                                                                 bytes, the packet will be removed.
                                                                 A setting of 0 means the RGX will not modify or remove the FCS bytes. */
        uint64_t ncsi_lmac_id          : 2;  /**< [  8:  7](R/W) Reserved. */
        uint64_t cmr_ncsi_drop         : 1;  /**< [  9:  9](R/W) Reserved. */
        uint64_t cmr_ncsi_reset        : 1;  /**< [ 10: 10](R/W) Reserved. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmr_global_config_s cn; */
};
typedef union bdk_rgxx_cmr_global_config bdk_rgxx_cmr_global_config_t;

static inline uint64_t BDK_RGXX_CMR_GLOBAL_CONFIG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMR_GLOBAL_CONFIG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8000008ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_CMR_GLOBAL_CONFIG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMR_GLOBAL_CONFIG(a) bdk_rgxx_cmr_global_config_t
#define bustype_BDK_RGXX_CMR_GLOBAL_CONFIG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMR_GLOBAL_CONFIG(a) "RGXX_CMR_GLOBAL_CONFIG"
#define device_bar_BDK_RGXX_CMR_GLOBAL_CONFIG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMR_GLOBAL_CONFIG(a) (a)
#define arguments_BDK_RGXX_CMR_GLOBAL_CONFIG(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_cmr_mem_ctrl
 *
 * RGX CMR Memory Control Register
 */
union bdk_rgxx_cmr_mem_ctrl
{
    uint64_t u;
    struct bdk_rgxx_cmr_mem_ctrl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t txb_ncsi_synd         : 2;  /**< [ 35: 34](R/W) Reserved. */
        uint64_t txb_ncsi_cor_dis      : 1;  /**< [ 33: 33](R/W) Reserved. */
        uint64_t txb_skid_m3_synd      : 2;  /**< [ 32: 31](R/W) Syndrome to flip and generate single-bit/double-bit for TXB SKID FIFO */
        uint64_t txb_skid_m3_cor_dis   : 1;  /**< [ 30: 30](R/W) ECC-correction disable for the TXB SKID FIFO */
        uint64_t txb_skid_m2_synd      : 2;  /**< [ 29: 28](R/W) Syndrome to flip and generate single-bit/double-bit for TXB SKID FIFO */
        uint64_t txb_skid_m2_cor_dis   : 1;  /**< [ 27: 27](R/W) ECC-correction disable for the TXB SKID FIFO */
        uint64_t txb_skid_m1_synd      : 2;  /**< [ 26: 25](R/W) Syndrome to flip and generate single-bit/double-bit for TXB SKID FIFO */
        uint64_t txb_skid_m1_cor_dis   : 1;  /**< [ 24: 24](R/W) ECC-correction disable for the TXB SKID FIFO */
        uint64_t txb_skid_m0_synd      : 2;  /**< [ 23: 22](R/W) Syndrome to flip and generate single-bit/double-bit for TXB SKID FIFO. */
        uint64_t txb_skid_m0_cor_dis   : 1;  /**< [ 21: 21](R/W) ECC-correction disable for the TXB SKID FIFO. */
        uint64_t txb_fif_bk1_syn       : 2;  /**< [ 20: 19](R/W) Syndrome to flip and generate single-bit/double-bit error for TXB main bank1. */
        uint64_t txb_fif_bk1_cdis      : 1;  /**< [ 18: 18](R/W) ECC-correction disable for the TXB main bank1. */
        uint64_t txb_fif_bk0_syn       : 2;  /**< [ 17: 16](R/W) Syndrome to flip and generate single-bit/double-bit error for TXB main bank0. */
        uint64_t txb_fif_bk0_cdis      : 1;  /**< [ 15: 15](R/W) ECC-correction disable for the TXB main bank0. */
        uint64_t rxb_skid_synd         : 2;  /**< [ 14: 13](R/W) Syndrome to flip and generate single-bit/double-bit error for RXB SKID FIFO. */
        uint64_t rxb_skid_cor_dis      : 1;  /**< [ 12: 12](R/W) ECC-correction disable for the RXB SKID FIFO. */
        uint64_t rxb_fif_bk1_syn1      : 2;  /**< [ 11: 10](R/W) Syndrome to flip and generate single-bit/double-bit error for RXB main bank1 srf1. */
        uint64_t rxb_fif_bk1_cdis1     : 1;  /**< [  9:  9](R/W) ECC-correction disable for the RXB main bank1 srf1. */
        uint64_t rxb_fif_bk1_syn0      : 2;  /**< [  8:  7](R/W) Syndrome to flip and generate single-bit/double-bit error for RXB main bank1 srf0. */
        uint64_t rxb_fif_bk1_cdis0     : 1;  /**< [  6:  6](R/W) ECC-correction disable for the RXB main bank1 srf0. */
        uint64_t rxb_fif_bk0_syn1      : 2;  /**< [  5:  4](R/W) Syndrome to flip and generate single-bit/double-bit error for RXB main bank0 srf1. */
        uint64_t rxb_fif_bk0_cdis1     : 1;  /**< [  3:  3](R/W) ECC-correction disable for the RXB main bank0 srf1. */
        uint64_t rxb_fif_bk0_syn0      : 2;  /**< [  2:  1](R/W) Syndrome to flip and generate single-bit/double-bit error for RXB main bank0 srf0. */
        uint64_t rxb_fif_bk0_cdis0     : 1;  /**< [  0:  0](R/W) ECC-correction disable for the RXB main bank0 srf0. */
#else /* Word 0 - Little Endian */
        uint64_t rxb_fif_bk0_cdis0     : 1;  /**< [  0:  0](R/W) ECC-correction disable for the RXB main bank0 srf0. */
        uint64_t rxb_fif_bk0_syn0      : 2;  /**< [  2:  1](R/W) Syndrome to flip and generate single-bit/double-bit error for RXB main bank0 srf0. */
        uint64_t rxb_fif_bk0_cdis1     : 1;  /**< [  3:  3](R/W) ECC-correction disable for the RXB main bank0 srf1. */
        uint64_t rxb_fif_bk0_syn1      : 2;  /**< [  5:  4](R/W) Syndrome to flip and generate single-bit/double-bit error for RXB main bank0 srf1. */
        uint64_t rxb_fif_bk1_cdis0     : 1;  /**< [  6:  6](R/W) ECC-correction disable for the RXB main bank1 srf0. */
        uint64_t rxb_fif_bk1_syn0      : 2;  /**< [  8:  7](R/W) Syndrome to flip and generate single-bit/double-bit error for RXB main bank1 srf0. */
        uint64_t rxb_fif_bk1_cdis1     : 1;  /**< [  9:  9](R/W) ECC-correction disable for the RXB main bank1 srf1. */
        uint64_t rxb_fif_bk1_syn1      : 2;  /**< [ 11: 10](R/W) Syndrome to flip and generate single-bit/double-bit error for RXB main bank1 srf1. */
        uint64_t rxb_skid_cor_dis      : 1;  /**< [ 12: 12](R/W) ECC-correction disable for the RXB SKID FIFO. */
        uint64_t rxb_skid_synd         : 2;  /**< [ 14: 13](R/W) Syndrome to flip and generate single-bit/double-bit error for RXB SKID FIFO. */
        uint64_t txb_fif_bk0_cdis      : 1;  /**< [ 15: 15](R/W) ECC-correction disable for the TXB main bank0. */
        uint64_t txb_fif_bk0_syn       : 2;  /**< [ 17: 16](R/W) Syndrome to flip and generate single-bit/double-bit error for TXB main bank0. */
        uint64_t txb_fif_bk1_cdis      : 1;  /**< [ 18: 18](R/W) ECC-correction disable for the TXB main bank1. */
        uint64_t txb_fif_bk1_syn       : 2;  /**< [ 20: 19](R/W) Syndrome to flip and generate single-bit/double-bit error for TXB main bank1. */
        uint64_t txb_skid_m0_cor_dis   : 1;  /**< [ 21: 21](R/W) ECC-correction disable for the TXB SKID FIFO. */
        uint64_t txb_skid_m0_synd      : 2;  /**< [ 23: 22](R/W) Syndrome to flip and generate single-bit/double-bit for TXB SKID FIFO. */
        uint64_t txb_skid_m1_cor_dis   : 1;  /**< [ 24: 24](R/W) ECC-correction disable for the TXB SKID FIFO */
        uint64_t txb_skid_m1_synd      : 2;  /**< [ 26: 25](R/W) Syndrome to flip and generate single-bit/double-bit for TXB SKID FIFO */
        uint64_t txb_skid_m2_cor_dis   : 1;  /**< [ 27: 27](R/W) ECC-correction disable for the TXB SKID FIFO */
        uint64_t txb_skid_m2_synd      : 2;  /**< [ 29: 28](R/W) Syndrome to flip and generate single-bit/double-bit for TXB SKID FIFO */
        uint64_t txb_skid_m3_cor_dis   : 1;  /**< [ 30: 30](R/W) ECC-correction disable for the TXB SKID FIFO */
        uint64_t txb_skid_m3_synd      : 2;  /**< [ 32: 31](R/W) Syndrome to flip and generate single-bit/double-bit for TXB SKID FIFO */
        uint64_t txb_ncsi_cor_dis      : 1;  /**< [ 33: 33](R/W) Reserved. */
        uint64_t txb_ncsi_synd         : 2;  /**< [ 35: 34](R/W) Reserved. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmr_mem_ctrl_s cn; */
};
typedef union bdk_rgxx_cmr_mem_ctrl bdk_rgxx_cmr_mem_ctrl_t;

static inline uint64_t BDK_RGXX_CMR_MEM_CTRL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMR_MEM_CTRL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8000030ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_CMR_MEM_CTRL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMR_MEM_CTRL(a) bdk_rgxx_cmr_mem_ctrl_t
#define bustype_BDK_RGXX_CMR_MEM_CTRL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMR_MEM_CTRL(a) "RGXX_CMR_MEM_CTRL"
#define device_bar_BDK_RGXX_CMR_MEM_CTRL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMR_MEM_CTRL(a) (a)
#define arguments_BDK_RGXX_CMR_MEM_CTRL(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_cmr_mem_int
 *
 * RGX CMR Memory Interrupt Register
 */
union bdk_rgxx_cmr_mem_int
{
    uint64_t u;
    struct bdk_rgxx_cmr_mem_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t txb_skid_m3_nic_sbe   : 1;  /**< [ 35: 35](R/W1C/H) TXB SKID NIC FIFO single-bit error */
        uint64_t txb_skid_m3_nic_dbe   : 1;  /**< [ 34: 34](R/W1C/H) TXB SKID NIC FIFO double-bit error */
        uint64_t txb_skid_m2_nic_sbe   : 1;  /**< [ 33: 33](R/W1C/H) TXB SKID FIFO single-bit error */
        uint64_t txb_skid_m2_nic_dbe   : 1;  /**< [ 32: 32](R/W1C/H) TXB SKID NIC FIFO double-bit error */
        uint64_t txb_skid_m1_nic_sbe   : 1;  /**< [ 31: 31](R/W1C/H) TXB SKID NIC FIFO single-bit error */
        uint64_t txb_skid_m1_nic_dbe   : 1;  /**< [ 30: 30](R/W1C/H) TXB SKID NIC FIFO double-bit error */
        uint64_t txb_skid_m0_nic_sbe   : 1;  /**< [ 29: 29](R/W1C/H) TXB SKID NIC FIFO double-bit error */
        uint64_t txb_skid_m0_nic_dbe   : 1;  /**< [ 28: 28](R/W1C/H) TXB SKID NIC FIFO double-bit error */
        uint64_t txb_ncsi_sbe          : 1;  /**< [ 27: 27](R/W1C/H) Reserved. */
        uint64_t txb_ncsi_dbe          : 1;  /**< [ 26: 26](R/W1C/H) Reserved. */
        uint64_t txb_skid_m3_pko_sbe   : 1;  /**< [ 25: 25](R/W1C/H) Reserved. */
        uint64_t txb_skid_m3_pko_dbe   : 1;  /**< [ 24: 24](R/W1C/H) Reserved. */
        uint64_t txb_skid_m2_pko_sbe   : 1;  /**< [ 23: 23](R/W1C/H) Reserved. */
        uint64_t txb_skid_m2_pko_dbe   : 1;  /**< [ 22: 22](R/W1C/H) Reserved. */
        uint64_t txb_skid_m1_pko_sbe   : 1;  /**< [ 21: 21](R/W1C/H) Reserved. */
        uint64_t txb_skid_m1_pko_dbe   : 1;  /**< [ 20: 20](R/W1C/H) Reserved. */
        uint64_t smu_in_overfl         : 1;  /**< [ 19: 19](R/W1C/H) Reserved. */
        uint64_t gmp_in_overfl         : 1;  /**< [ 18: 18](R/W1C/H) RX GMP INFIFO overflow. */
        uint64_t txb_skid_m0_pko_sbe   : 1;  /**< [ 17: 17](R/W1C/H) Reserved. */
        uint64_t txb_skid_m0_pko_dbe   : 1;  /**< [ 16: 16](R/W1C/H) Reserved. */
        uint64_t txb_fif_bk1_sbe       : 1;  /**< [ 15: 15](R/W1C/H) TXB Main FIFO Bank1 single-bit error. */
        uint64_t txb_fif_bk1_dbe       : 1;  /**< [ 14: 14](R/W1C/H) TXB Main FIFO Bank1 double-bit error. */
        uint64_t txb_fif_bk0_sbe       : 1;  /**< [ 13: 13](R/W1C/H) TXB Main FIFO Bank0 single-bit error. */
        uint64_t txb_fif_bk0_dbe       : 1;  /**< [ 12: 12](R/W1C/H) TXB Main FIFO Bank0 double-bit error. */
        uint64_t rxb_nic_skid_sbe      : 1;  /**< [ 11: 11](R/W1C/H) RXB NIC SKID FIFO single-bit error. */
        uint64_t rxb_nic_skid_dbe      : 1;  /**< [ 10: 10](R/W1C/H) RXB NIC SKID FIFO double-bit error. */
        uint64_t rxb_pki_skid_sbe      : 1;  /**< [  9:  9](R/W1C/H) RXB PKI SKID FIFO single-bit error. */
        uint64_t rxb_pki_skid_dbe      : 1;  /**< [  8:  8](R/W1C/H) RXB PKI SKID FIFO double-bit error. */
        uint64_t rxb_fif_bk1_sbe1      : 1;  /**< [  7:  7](R/W1C/H) RXB main FIFO bank1 srf1 single-bit error. */
        uint64_t rxb_fif_bk1_dbe1      : 1;  /**< [  6:  6](R/W1C/H) RXB main FIFO bank1 srf1 double-bit error. */
        uint64_t rxb_fif_bk1_sbe0      : 1;  /**< [  5:  5](R/W1C/H) RXB main FIFO bank1 srf0 single-bit error. */
        uint64_t rxb_fif_bk1_dbe0      : 1;  /**< [  4:  4](R/W1C/H) RXB main FIFO bank1 srf0 double-bit error. */
        uint64_t rxb_fif_bk0_sbe1      : 1;  /**< [  3:  3](R/W1C/H) RXB main FIFO bank0 srf1 single-bit error. */
        uint64_t rxb_fif_bk0_dbe1      : 1;  /**< [  2:  2](R/W1C/H) RXB main FIFO bank0 srf1 double-bit error. */
        uint64_t rxb_fif_bk0_sbe0      : 1;  /**< [  1:  1](R/W1C/H) RXB main FIFO bank0 srf0 single-bit error. */
        uint64_t rxb_fif_bk0_dbe0      : 1;  /**< [  0:  0](R/W1C/H) RXB main FIFO bank0 srf0 double-bit error. */
#else /* Word 0 - Little Endian */
        uint64_t rxb_fif_bk0_dbe0      : 1;  /**< [  0:  0](R/W1C/H) RXB main FIFO bank0 srf0 double-bit error. */
        uint64_t rxb_fif_bk0_sbe0      : 1;  /**< [  1:  1](R/W1C/H) RXB main FIFO bank0 srf0 single-bit error. */
        uint64_t rxb_fif_bk0_dbe1      : 1;  /**< [  2:  2](R/W1C/H) RXB main FIFO bank0 srf1 double-bit error. */
        uint64_t rxb_fif_bk0_sbe1      : 1;  /**< [  3:  3](R/W1C/H) RXB main FIFO bank0 srf1 single-bit error. */
        uint64_t rxb_fif_bk1_dbe0      : 1;  /**< [  4:  4](R/W1C/H) RXB main FIFO bank1 srf0 double-bit error. */
        uint64_t rxb_fif_bk1_sbe0      : 1;  /**< [  5:  5](R/W1C/H) RXB main FIFO bank1 srf0 single-bit error. */
        uint64_t rxb_fif_bk1_dbe1      : 1;  /**< [  6:  6](R/W1C/H) RXB main FIFO bank1 srf1 double-bit error. */
        uint64_t rxb_fif_bk1_sbe1      : 1;  /**< [  7:  7](R/W1C/H) RXB main FIFO bank1 srf1 single-bit error. */
        uint64_t rxb_pki_skid_dbe      : 1;  /**< [  8:  8](R/W1C/H) RXB PKI SKID FIFO double-bit error. */
        uint64_t rxb_pki_skid_sbe      : 1;  /**< [  9:  9](R/W1C/H) RXB PKI SKID FIFO single-bit error. */
        uint64_t rxb_nic_skid_dbe      : 1;  /**< [ 10: 10](R/W1C/H) RXB NIC SKID FIFO double-bit error. */
        uint64_t rxb_nic_skid_sbe      : 1;  /**< [ 11: 11](R/W1C/H) RXB NIC SKID FIFO single-bit error. */
        uint64_t txb_fif_bk0_dbe       : 1;  /**< [ 12: 12](R/W1C/H) TXB Main FIFO Bank0 double-bit error. */
        uint64_t txb_fif_bk0_sbe       : 1;  /**< [ 13: 13](R/W1C/H) TXB Main FIFO Bank0 single-bit error. */
        uint64_t txb_fif_bk1_dbe       : 1;  /**< [ 14: 14](R/W1C/H) TXB Main FIFO Bank1 double-bit error. */
        uint64_t txb_fif_bk1_sbe       : 1;  /**< [ 15: 15](R/W1C/H) TXB Main FIFO Bank1 single-bit error. */
        uint64_t txb_skid_m0_pko_dbe   : 1;  /**< [ 16: 16](R/W1C/H) Reserved. */
        uint64_t txb_skid_m0_pko_sbe   : 1;  /**< [ 17: 17](R/W1C/H) Reserved. */
        uint64_t gmp_in_overfl         : 1;  /**< [ 18: 18](R/W1C/H) RX GMP INFIFO overflow. */
        uint64_t smu_in_overfl         : 1;  /**< [ 19: 19](R/W1C/H) Reserved. */
        uint64_t txb_skid_m1_pko_dbe   : 1;  /**< [ 20: 20](R/W1C/H) Reserved. */
        uint64_t txb_skid_m1_pko_sbe   : 1;  /**< [ 21: 21](R/W1C/H) Reserved. */
        uint64_t txb_skid_m2_pko_dbe   : 1;  /**< [ 22: 22](R/W1C/H) Reserved. */
        uint64_t txb_skid_m2_pko_sbe   : 1;  /**< [ 23: 23](R/W1C/H) Reserved. */
        uint64_t txb_skid_m3_pko_dbe   : 1;  /**< [ 24: 24](R/W1C/H) Reserved. */
        uint64_t txb_skid_m3_pko_sbe   : 1;  /**< [ 25: 25](R/W1C/H) Reserved. */
        uint64_t txb_ncsi_dbe          : 1;  /**< [ 26: 26](R/W1C/H) Reserved. */
        uint64_t txb_ncsi_sbe          : 1;  /**< [ 27: 27](R/W1C/H) Reserved. */
        uint64_t txb_skid_m0_nic_dbe   : 1;  /**< [ 28: 28](R/W1C/H) TXB SKID NIC FIFO double-bit error */
        uint64_t txb_skid_m0_nic_sbe   : 1;  /**< [ 29: 29](R/W1C/H) TXB SKID NIC FIFO double-bit error */
        uint64_t txb_skid_m1_nic_dbe   : 1;  /**< [ 30: 30](R/W1C/H) TXB SKID NIC FIFO double-bit error */
        uint64_t txb_skid_m1_nic_sbe   : 1;  /**< [ 31: 31](R/W1C/H) TXB SKID NIC FIFO single-bit error */
        uint64_t txb_skid_m2_nic_dbe   : 1;  /**< [ 32: 32](R/W1C/H) TXB SKID NIC FIFO double-bit error */
        uint64_t txb_skid_m2_nic_sbe   : 1;  /**< [ 33: 33](R/W1C/H) TXB SKID FIFO single-bit error */
        uint64_t txb_skid_m3_nic_dbe   : 1;  /**< [ 34: 34](R/W1C/H) TXB SKID NIC FIFO double-bit error */
        uint64_t txb_skid_m3_nic_sbe   : 1;  /**< [ 35: 35](R/W1C/H) TXB SKID NIC FIFO single-bit error */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmr_mem_int_s cn; */
};
typedef union bdk_rgxx_cmr_mem_int bdk_rgxx_cmr_mem_int_t;

static inline uint64_t BDK_RGXX_CMR_MEM_INT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMR_MEM_INT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8000010ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_CMR_MEM_INT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMR_MEM_INT(a) bdk_rgxx_cmr_mem_int_t
#define bustype_BDK_RGXX_CMR_MEM_INT(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMR_MEM_INT(a) "RGXX_CMR_MEM_INT"
#define device_bar_BDK_RGXX_CMR_MEM_INT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMR_MEM_INT(a) (a)
#define arguments_BDK_RGXX_CMR_MEM_INT(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_cmr_mem_int_ena_w1c
 *
 * RGX CMR Memory Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_rgxx_cmr_mem_int_ena_w1c
{
    uint64_t u;
    struct bdk_rgxx_cmr_mem_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t txb_skid_m3_nic_sbe   : 1;  /**< [ 35: 35](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M3_NIC_SBE]. */
        uint64_t txb_skid_m3_nic_dbe   : 1;  /**< [ 34: 34](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M3_NIC_DBE]. */
        uint64_t txb_skid_m2_nic_sbe   : 1;  /**< [ 33: 33](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M2_NIC_SBE]. */
        uint64_t txb_skid_m2_nic_dbe   : 1;  /**< [ 32: 32](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M2_NIC_DBE]. */
        uint64_t txb_skid_m1_nic_sbe   : 1;  /**< [ 31: 31](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M1_NIC_SBE]. */
        uint64_t txb_skid_m1_nic_dbe   : 1;  /**< [ 30: 30](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M1_NIC_DBE]. */
        uint64_t txb_skid_m0_nic_sbe   : 1;  /**< [ 29: 29](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M0_NIC_SBE]. */
        uint64_t txb_skid_m0_nic_dbe   : 1;  /**< [ 28: 28](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M0_NIC_DBE]. */
        uint64_t txb_ncsi_sbe          : 1;  /**< [ 27: 27](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_NCSI_SBE]. */
        uint64_t txb_ncsi_dbe          : 1;  /**< [ 26: 26](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_NCSI_DBE]. */
        uint64_t txb_skid_m3_pko_sbe   : 1;  /**< [ 25: 25](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M3_PKO_SBE]. */
        uint64_t txb_skid_m3_pko_dbe   : 1;  /**< [ 24: 24](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M3_PKO_DBE]. */
        uint64_t txb_skid_m2_pko_sbe   : 1;  /**< [ 23: 23](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M2_PKO_SBE]. */
        uint64_t txb_skid_m2_pko_dbe   : 1;  /**< [ 22: 22](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M2_PKO_DBE]. */
        uint64_t txb_skid_m1_pko_sbe   : 1;  /**< [ 21: 21](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M1_PKO_SBE]. */
        uint64_t txb_skid_m1_pko_dbe   : 1;  /**< [ 20: 20](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M1_PKO_DBE]. */
        uint64_t smu_in_overfl         : 1;  /**< [ 19: 19](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[SMU_IN_OVERFL]. */
        uint64_t gmp_in_overfl         : 1;  /**< [ 18: 18](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[GMP_IN_OVERFL]. */
        uint64_t txb_skid_m0_pko_sbe   : 1;  /**< [ 17: 17](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M0_PKO_SBE]. */
        uint64_t txb_skid_m0_pko_dbe   : 1;  /**< [ 16: 16](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M0_PKO_DBE]. */
        uint64_t txb_fif_bk1_sbe       : 1;  /**< [ 15: 15](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_FIF_BK1_SBE]. */
        uint64_t txb_fif_bk1_dbe       : 1;  /**< [ 14: 14](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_FIF_BK1_DBE]. */
        uint64_t txb_fif_bk0_sbe       : 1;  /**< [ 13: 13](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_FIF_BK0_SBE]. */
        uint64_t txb_fif_bk0_dbe       : 1;  /**< [ 12: 12](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_FIF_BK0_DBE]. */
        uint64_t rxb_nic_skid_sbe      : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_NIC_SKID_SBE]. */
        uint64_t rxb_nic_skid_dbe      : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_NIC_SKID_DBE]. */
        uint64_t rxb_pki_skid_sbe      : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_PKI_SKID_SBE]. */
        uint64_t rxb_pki_skid_dbe      : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_PKI_SKID_DBE]. */
        uint64_t rxb_fif_bk1_sbe1      : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_SBE1]. */
        uint64_t rxb_fif_bk1_dbe1      : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_DBE1]. */
        uint64_t rxb_fif_bk1_sbe0      : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_SBE0]. */
        uint64_t rxb_fif_bk1_dbe0      : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_DBE0]. */
        uint64_t rxb_fif_bk0_sbe1      : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_SBE1]. */
        uint64_t rxb_fif_bk0_dbe1      : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_DBE1]. */
        uint64_t rxb_fif_bk0_sbe0      : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_SBE0]. */
        uint64_t rxb_fif_bk0_dbe0      : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_DBE0]. */
#else /* Word 0 - Little Endian */
        uint64_t rxb_fif_bk0_dbe0      : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_DBE0]. */
        uint64_t rxb_fif_bk0_sbe0      : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_SBE0]. */
        uint64_t rxb_fif_bk0_dbe1      : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_DBE1]. */
        uint64_t rxb_fif_bk0_sbe1      : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_SBE1]. */
        uint64_t rxb_fif_bk1_dbe0      : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_DBE0]. */
        uint64_t rxb_fif_bk1_sbe0      : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_SBE0]. */
        uint64_t rxb_fif_bk1_dbe1      : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_DBE1]. */
        uint64_t rxb_fif_bk1_sbe1      : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_SBE1]. */
        uint64_t rxb_pki_skid_dbe      : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_PKI_SKID_DBE]. */
        uint64_t rxb_pki_skid_sbe      : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_PKI_SKID_SBE]. */
        uint64_t rxb_nic_skid_dbe      : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_NIC_SKID_DBE]. */
        uint64_t rxb_nic_skid_sbe      : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[RXB_NIC_SKID_SBE]. */
        uint64_t txb_fif_bk0_dbe       : 1;  /**< [ 12: 12](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_FIF_BK0_DBE]. */
        uint64_t txb_fif_bk0_sbe       : 1;  /**< [ 13: 13](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_FIF_BK0_SBE]. */
        uint64_t txb_fif_bk1_dbe       : 1;  /**< [ 14: 14](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_FIF_BK1_DBE]. */
        uint64_t txb_fif_bk1_sbe       : 1;  /**< [ 15: 15](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_FIF_BK1_SBE]. */
        uint64_t txb_skid_m0_pko_dbe   : 1;  /**< [ 16: 16](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M0_PKO_DBE]. */
        uint64_t txb_skid_m0_pko_sbe   : 1;  /**< [ 17: 17](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M0_PKO_SBE]. */
        uint64_t gmp_in_overfl         : 1;  /**< [ 18: 18](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[GMP_IN_OVERFL]. */
        uint64_t smu_in_overfl         : 1;  /**< [ 19: 19](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[SMU_IN_OVERFL]. */
        uint64_t txb_skid_m1_pko_dbe   : 1;  /**< [ 20: 20](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M1_PKO_DBE]. */
        uint64_t txb_skid_m1_pko_sbe   : 1;  /**< [ 21: 21](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M1_PKO_SBE]. */
        uint64_t txb_skid_m2_pko_dbe   : 1;  /**< [ 22: 22](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M2_PKO_DBE]. */
        uint64_t txb_skid_m2_pko_sbe   : 1;  /**< [ 23: 23](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M2_PKO_SBE]. */
        uint64_t txb_skid_m3_pko_dbe   : 1;  /**< [ 24: 24](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M3_PKO_DBE]. */
        uint64_t txb_skid_m3_pko_sbe   : 1;  /**< [ 25: 25](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M3_PKO_SBE]. */
        uint64_t txb_ncsi_dbe          : 1;  /**< [ 26: 26](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_NCSI_DBE]. */
        uint64_t txb_ncsi_sbe          : 1;  /**< [ 27: 27](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_NCSI_SBE]. */
        uint64_t txb_skid_m0_nic_dbe   : 1;  /**< [ 28: 28](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M0_NIC_DBE]. */
        uint64_t txb_skid_m0_nic_sbe   : 1;  /**< [ 29: 29](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M0_NIC_SBE]. */
        uint64_t txb_skid_m1_nic_dbe   : 1;  /**< [ 30: 30](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M1_NIC_DBE]. */
        uint64_t txb_skid_m1_nic_sbe   : 1;  /**< [ 31: 31](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M1_NIC_SBE]. */
        uint64_t txb_skid_m2_nic_dbe   : 1;  /**< [ 32: 32](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M2_NIC_DBE]. */
        uint64_t txb_skid_m2_nic_sbe   : 1;  /**< [ 33: 33](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M2_NIC_SBE]. */
        uint64_t txb_skid_m3_nic_dbe   : 1;  /**< [ 34: 34](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M3_NIC_DBE]. */
        uint64_t txb_skid_m3_nic_sbe   : 1;  /**< [ 35: 35](R/W1C/H) Reads or clears enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M3_NIC_SBE]. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmr_mem_int_ena_w1c_s cn; */
};
typedef union bdk_rgxx_cmr_mem_int_ena_w1c bdk_rgxx_cmr_mem_int_ena_w1c_t;

static inline uint64_t BDK_RGXX_CMR_MEM_INT_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMR_MEM_INT_ENA_W1C(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8000020ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_CMR_MEM_INT_ENA_W1C", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMR_MEM_INT_ENA_W1C(a) bdk_rgxx_cmr_mem_int_ena_w1c_t
#define bustype_BDK_RGXX_CMR_MEM_INT_ENA_W1C(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMR_MEM_INT_ENA_W1C(a) "RGXX_CMR_MEM_INT_ENA_W1C"
#define device_bar_BDK_RGXX_CMR_MEM_INT_ENA_W1C(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMR_MEM_INT_ENA_W1C(a) (a)
#define arguments_BDK_RGXX_CMR_MEM_INT_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_cmr_mem_int_ena_w1s
 *
 * RGX CMR Memory Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_rgxx_cmr_mem_int_ena_w1s
{
    uint64_t u;
    struct bdk_rgxx_cmr_mem_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t txb_skid_m3_nic_sbe   : 1;  /**< [ 35: 35](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M3_NIC_SBE]. */
        uint64_t txb_skid_m3_nic_dbe   : 1;  /**< [ 34: 34](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M3_NIC_DBE]. */
        uint64_t txb_skid_m2_nic_sbe   : 1;  /**< [ 33: 33](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M2_NIC_SBE]. */
        uint64_t txb_skid_m2_nic_dbe   : 1;  /**< [ 32: 32](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M2_NIC_DBE]. */
        uint64_t txb_skid_m1_nic_sbe   : 1;  /**< [ 31: 31](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M1_NIC_SBE]. */
        uint64_t txb_skid_m1_nic_dbe   : 1;  /**< [ 30: 30](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M1_NIC_DBE]. */
        uint64_t txb_skid_m0_nic_sbe   : 1;  /**< [ 29: 29](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M0_NIC_SBE]. */
        uint64_t txb_skid_m0_nic_dbe   : 1;  /**< [ 28: 28](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M0_NIC_DBE]. */
        uint64_t txb_ncsi_sbe          : 1;  /**< [ 27: 27](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_NCSI_SBE]. */
        uint64_t txb_ncsi_dbe          : 1;  /**< [ 26: 26](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_NCSI_DBE]. */
        uint64_t txb_skid_m3_pko_sbe   : 1;  /**< [ 25: 25](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M3_PKO_SBE]. */
        uint64_t txb_skid_m3_pko_dbe   : 1;  /**< [ 24: 24](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M3_PKO_DBE]. */
        uint64_t txb_skid_m2_pko_sbe   : 1;  /**< [ 23: 23](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M2_PKO_SBE]. */
        uint64_t txb_skid_m2_pko_dbe   : 1;  /**< [ 22: 22](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M2_PKO_DBE]. */
        uint64_t txb_skid_m1_pko_sbe   : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M1_PKO_SBE]. */
        uint64_t txb_skid_m1_pko_dbe   : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M1_PKO_DBE]. */
        uint64_t smu_in_overfl         : 1;  /**< [ 19: 19](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[SMU_IN_OVERFL]. */
        uint64_t gmp_in_overfl         : 1;  /**< [ 18: 18](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[GMP_IN_OVERFL]. */
        uint64_t txb_skid_m0_pko_sbe   : 1;  /**< [ 17: 17](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M0_PKO_SBE]. */
        uint64_t txb_skid_m0_pko_dbe   : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M0_PKO_DBE]. */
        uint64_t txb_fif_bk1_sbe       : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_FIF_BK1_SBE]. */
        uint64_t txb_fif_bk1_dbe       : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_FIF_BK1_DBE]. */
        uint64_t txb_fif_bk0_sbe       : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_FIF_BK0_SBE]. */
        uint64_t txb_fif_bk0_dbe       : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_FIF_BK0_DBE]. */
        uint64_t rxb_nic_skid_sbe      : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_NIC_SKID_SBE]. */
        uint64_t rxb_nic_skid_dbe      : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_NIC_SKID_DBE]. */
        uint64_t rxb_pki_skid_sbe      : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_PKI_SKID_SBE]. */
        uint64_t rxb_pki_skid_dbe      : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_PKI_SKID_DBE]. */
        uint64_t rxb_fif_bk1_sbe1      : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_SBE1]. */
        uint64_t rxb_fif_bk1_dbe1      : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_DBE1]. */
        uint64_t rxb_fif_bk1_sbe0      : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_SBE0]. */
        uint64_t rxb_fif_bk1_dbe0      : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_DBE0]. */
        uint64_t rxb_fif_bk0_sbe1      : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_SBE1]. */
        uint64_t rxb_fif_bk0_dbe1      : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_DBE1]. */
        uint64_t rxb_fif_bk0_sbe0      : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_SBE0]. */
        uint64_t rxb_fif_bk0_dbe0      : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_DBE0]. */
#else /* Word 0 - Little Endian */
        uint64_t rxb_fif_bk0_dbe0      : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_DBE0]. */
        uint64_t rxb_fif_bk0_sbe0      : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_SBE0]. */
        uint64_t rxb_fif_bk0_dbe1      : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_DBE1]. */
        uint64_t rxb_fif_bk0_sbe1      : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_SBE1]. */
        uint64_t rxb_fif_bk1_dbe0      : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_DBE0]. */
        uint64_t rxb_fif_bk1_sbe0      : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_SBE0]. */
        uint64_t rxb_fif_bk1_dbe1      : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_DBE1]. */
        uint64_t rxb_fif_bk1_sbe1      : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_SBE1]. */
        uint64_t rxb_pki_skid_dbe      : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_PKI_SKID_DBE]. */
        uint64_t rxb_pki_skid_sbe      : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_PKI_SKID_SBE]. */
        uint64_t rxb_nic_skid_dbe      : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_NIC_SKID_DBE]. */
        uint64_t rxb_nic_skid_sbe      : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[RXB_NIC_SKID_SBE]. */
        uint64_t txb_fif_bk0_dbe       : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_FIF_BK0_DBE]. */
        uint64_t txb_fif_bk0_sbe       : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_FIF_BK0_SBE]. */
        uint64_t txb_fif_bk1_dbe       : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_FIF_BK1_DBE]. */
        uint64_t txb_fif_bk1_sbe       : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_FIF_BK1_SBE]. */
        uint64_t txb_skid_m0_pko_dbe   : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M0_PKO_DBE]. */
        uint64_t txb_skid_m0_pko_sbe   : 1;  /**< [ 17: 17](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M0_PKO_SBE]. */
        uint64_t gmp_in_overfl         : 1;  /**< [ 18: 18](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[GMP_IN_OVERFL]. */
        uint64_t smu_in_overfl         : 1;  /**< [ 19: 19](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[SMU_IN_OVERFL]. */
        uint64_t txb_skid_m1_pko_dbe   : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M1_PKO_DBE]. */
        uint64_t txb_skid_m1_pko_sbe   : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M1_PKO_SBE]. */
        uint64_t txb_skid_m2_pko_dbe   : 1;  /**< [ 22: 22](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M2_PKO_DBE]. */
        uint64_t txb_skid_m2_pko_sbe   : 1;  /**< [ 23: 23](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M2_PKO_SBE]. */
        uint64_t txb_skid_m3_pko_dbe   : 1;  /**< [ 24: 24](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M3_PKO_DBE]. */
        uint64_t txb_skid_m3_pko_sbe   : 1;  /**< [ 25: 25](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M3_PKO_SBE]. */
        uint64_t txb_ncsi_dbe          : 1;  /**< [ 26: 26](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_NCSI_DBE]. */
        uint64_t txb_ncsi_sbe          : 1;  /**< [ 27: 27](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_NCSI_SBE]. */
        uint64_t txb_skid_m0_nic_dbe   : 1;  /**< [ 28: 28](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M0_NIC_DBE]. */
        uint64_t txb_skid_m0_nic_sbe   : 1;  /**< [ 29: 29](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M0_NIC_SBE]. */
        uint64_t txb_skid_m1_nic_dbe   : 1;  /**< [ 30: 30](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M1_NIC_DBE]. */
        uint64_t txb_skid_m1_nic_sbe   : 1;  /**< [ 31: 31](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M1_NIC_SBE]. */
        uint64_t txb_skid_m2_nic_dbe   : 1;  /**< [ 32: 32](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M2_NIC_DBE]. */
        uint64_t txb_skid_m2_nic_sbe   : 1;  /**< [ 33: 33](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M2_NIC_SBE]. */
        uint64_t txb_skid_m3_nic_dbe   : 1;  /**< [ 34: 34](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M3_NIC_DBE]. */
        uint64_t txb_skid_m3_nic_sbe   : 1;  /**< [ 35: 35](R/W1S/H) Reads or sets enable for RGX(0)_CMR_MEM_INT[TXB_SKID_M3_NIC_SBE]. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmr_mem_int_ena_w1s_s cn; */
};
typedef union bdk_rgxx_cmr_mem_int_ena_w1s bdk_rgxx_cmr_mem_int_ena_w1s_t;

static inline uint64_t BDK_RGXX_CMR_MEM_INT_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMR_MEM_INT_ENA_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8000028ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_CMR_MEM_INT_ENA_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMR_MEM_INT_ENA_W1S(a) bdk_rgxx_cmr_mem_int_ena_w1s_t
#define bustype_BDK_RGXX_CMR_MEM_INT_ENA_W1S(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMR_MEM_INT_ENA_W1S(a) "RGXX_CMR_MEM_INT_ENA_W1S"
#define device_bar_BDK_RGXX_CMR_MEM_INT_ENA_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMR_MEM_INT_ENA_W1S(a) (a)
#define arguments_BDK_RGXX_CMR_MEM_INT_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_cmr_mem_int_w1s
 *
 * RGX CMR Memory Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_rgxx_cmr_mem_int_w1s
{
    uint64_t u;
    struct bdk_rgxx_cmr_mem_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t txb_skid_m3_nic_sbe   : 1;  /**< [ 35: 35](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M3_NIC_SBE]. */
        uint64_t txb_skid_m3_nic_dbe   : 1;  /**< [ 34: 34](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M3_NIC_DBE]. */
        uint64_t txb_skid_m2_nic_sbe   : 1;  /**< [ 33: 33](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M2_NIC_SBE]. */
        uint64_t txb_skid_m2_nic_dbe   : 1;  /**< [ 32: 32](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M2_NIC_DBE]. */
        uint64_t txb_skid_m1_nic_sbe   : 1;  /**< [ 31: 31](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M1_NIC_SBE]. */
        uint64_t txb_skid_m1_nic_dbe   : 1;  /**< [ 30: 30](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M1_NIC_DBE]. */
        uint64_t txb_skid_m0_nic_sbe   : 1;  /**< [ 29: 29](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M0_NIC_SBE]. */
        uint64_t txb_skid_m0_nic_dbe   : 1;  /**< [ 28: 28](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M0_NIC_DBE]. */
        uint64_t txb_ncsi_sbe          : 1;  /**< [ 27: 27](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_NCSI_SBE]. */
        uint64_t txb_ncsi_dbe          : 1;  /**< [ 26: 26](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_NCSI_DBE]. */
        uint64_t txb_skid_m3_pko_sbe   : 1;  /**< [ 25: 25](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M3_PKO_SBE]. */
        uint64_t txb_skid_m3_pko_dbe   : 1;  /**< [ 24: 24](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M3_PKO_DBE]. */
        uint64_t txb_skid_m2_pko_sbe   : 1;  /**< [ 23: 23](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M2_PKO_SBE]. */
        uint64_t txb_skid_m2_pko_dbe   : 1;  /**< [ 22: 22](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M2_PKO_DBE]. */
        uint64_t txb_skid_m1_pko_sbe   : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M1_PKO_SBE]. */
        uint64_t txb_skid_m1_pko_dbe   : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M1_PKO_DBE]. */
        uint64_t smu_in_overfl         : 1;  /**< [ 19: 19](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[SMU_IN_OVERFL]. */
        uint64_t gmp_in_overfl         : 1;  /**< [ 18: 18](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[GMP_IN_OVERFL]. */
        uint64_t txb_skid_m0_pko_sbe   : 1;  /**< [ 17: 17](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M0_PKO_SBE]. */
        uint64_t txb_skid_m0_pko_dbe   : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M0_PKO_DBE]. */
        uint64_t txb_fif_bk1_sbe       : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_FIF_BK1_SBE]. */
        uint64_t txb_fif_bk1_dbe       : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_FIF_BK1_DBE]. */
        uint64_t txb_fif_bk0_sbe       : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_FIF_BK0_SBE]. */
        uint64_t txb_fif_bk0_dbe       : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_FIF_BK0_DBE]. */
        uint64_t rxb_nic_skid_sbe      : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_NIC_SKID_SBE]. */
        uint64_t rxb_nic_skid_dbe      : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_NIC_SKID_DBE]. */
        uint64_t rxb_pki_skid_sbe      : 1;  /**< [  9:  9](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_PKI_SKID_SBE]. */
        uint64_t rxb_pki_skid_dbe      : 1;  /**< [  8:  8](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_PKI_SKID_DBE]. */
        uint64_t rxb_fif_bk1_sbe1      : 1;  /**< [  7:  7](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_SBE1]. */
        uint64_t rxb_fif_bk1_dbe1      : 1;  /**< [  6:  6](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_DBE1]. */
        uint64_t rxb_fif_bk1_sbe0      : 1;  /**< [  5:  5](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_SBE0]. */
        uint64_t rxb_fif_bk1_dbe0      : 1;  /**< [  4:  4](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_DBE0]. */
        uint64_t rxb_fif_bk0_sbe1      : 1;  /**< [  3:  3](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_SBE1]. */
        uint64_t rxb_fif_bk0_dbe1      : 1;  /**< [  2:  2](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_DBE1]. */
        uint64_t rxb_fif_bk0_sbe0      : 1;  /**< [  1:  1](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_SBE0]. */
        uint64_t rxb_fif_bk0_dbe0      : 1;  /**< [  0:  0](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_DBE0]. */
#else /* Word 0 - Little Endian */
        uint64_t rxb_fif_bk0_dbe0      : 1;  /**< [  0:  0](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_DBE0]. */
        uint64_t rxb_fif_bk0_sbe0      : 1;  /**< [  1:  1](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_SBE0]. */
        uint64_t rxb_fif_bk0_dbe1      : 1;  /**< [  2:  2](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_DBE1]. */
        uint64_t rxb_fif_bk0_sbe1      : 1;  /**< [  3:  3](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_FIF_BK0_SBE1]. */
        uint64_t rxb_fif_bk1_dbe0      : 1;  /**< [  4:  4](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_DBE0]. */
        uint64_t rxb_fif_bk1_sbe0      : 1;  /**< [  5:  5](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_SBE0]. */
        uint64_t rxb_fif_bk1_dbe1      : 1;  /**< [  6:  6](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_DBE1]. */
        uint64_t rxb_fif_bk1_sbe1      : 1;  /**< [  7:  7](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_FIF_BK1_SBE1]. */
        uint64_t rxb_pki_skid_dbe      : 1;  /**< [  8:  8](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_PKI_SKID_DBE]. */
        uint64_t rxb_pki_skid_sbe      : 1;  /**< [  9:  9](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_PKI_SKID_SBE]. */
        uint64_t rxb_nic_skid_dbe      : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_NIC_SKID_DBE]. */
        uint64_t rxb_nic_skid_sbe      : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[RXB_NIC_SKID_SBE]. */
        uint64_t txb_fif_bk0_dbe       : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_FIF_BK0_DBE]. */
        uint64_t txb_fif_bk0_sbe       : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_FIF_BK0_SBE]. */
        uint64_t txb_fif_bk1_dbe       : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_FIF_BK1_DBE]. */
        uint64_t txb_fif_bk1_sbe       : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_FIF_BK1_SBE]. */
        uint64_t txb_skid_m0_pko_dbe   : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M0_PKO_DBE]. */
        uint64_t txb_skid_m0_pko_sbe   : 1;  /**< [ 17: 17](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M0_PKO_SBE]. */
        uint64_t gmp_in_overfl         : 1;  /**< [ 18: 18](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[GMP_IN_OVERFL]. */
        uint64_t smu_in_overfl         : 1;  /**< [ 19: 19](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[SMU_IN_OVERFL]. */
        uint64_t txb_skid_m1_pko_dbe   : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M1_PKO_DBE]. */
        uint64_t txb_skid_m1_pko_sbe   : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M1_PKO_SBE]. */
        uint64_t txb_skid_m2_pko_dbe   : 1;  /**< [ 22: 22](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M2_PKO_DBE]. */
        uint64_t txb_skid_m2_pko_sbe   : 1;  /**< [ 23: 23](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M2_PKO_SBE]. */
        uint64_t txb_skid_m3_pko_dbe   : 1;  /**< [ 24: 24](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M3_PKO_DBE]. */
        uint64_t txb_skid_m3_pko_sbe   : 1;  /**< [ 25: 25](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M3_PKO_SBE]. */
        uint64_t txb_ncsi_dbe          : 1;  /**< [ 26: 26](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_NCSI_DBE]. */
        uint64_t txb_ncsi_sbe          : 1;  /**< [ 27: 27](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_NCSI_SBE]. */
        uint64_t txb_skid_m0_nic_dbe   : 1;  /**< [ 28: 28](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M0_NIC_DBE]. */
        uint64_t txb_skid_m0_nic_sbe   : 1;  /**< [ 29: 29](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M0_NIC_SBE]. */
        uint64_t txb_skid_m1_nic_dbe   : 1;  /**< [ 30: 30](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M1_NIC_DBE]. */
        uint64_t txb_skid_m1_nic_sbe   : 1;  /**< [ 31: 31](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M1_NIC_SBE]. */
        uint64_t txb_skid_m2_nic_dbe   : 1;  /**< [ 32: 32](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M2_NIC_DBE]. */
        uint64_t txb_skid_m2_nic_sbe   : 1;  /**< [ 33: 33](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M2_NIC_SBE]. */
        uint64_t txb_skid_m3_nic_dbe   : 1;  /**< [ 34: 34](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M3_NIC_DBE]. */
        uint64_t txb_skid_m3_nic_sbe   : 1;  /**< [ 35: 35](R/W1S/H) Reads or sets RGX(0)_CMR_MEM_INT[TXB_SKID_M3_NIC_SBE]. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmr_mem_int_w1s_s cn; */
};
typedef union bdk_rgxx_cmr_mem_int_w1s bdk_rgxx_cmr_mem_int_w1s_t;

static inline uint64_t BDK_RGXX_CMR_MEM_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMR_MEM_INT_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8000018ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_CMR_MEM_INT_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMR_MEM_INT_W1S(a) bdk_rgxx_cmr_mem_int_w1s_t
#define bustype_BDK_RGXX_CMR_MEM_INT_W1S(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMR_MEM_INT_W1S(a) "RGXX_CMR_MEM_INT_W1S"
#define device_bar_BDK_RGXX_CMR_MEM_INT_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMR_MEM_INT_W1S(a) (a)
#define arguments_BDK_RGXX_CMR_MEM_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_cmr_nic_nxc_adr
 *
 * RGX CMR NIC NXC Exception Registers
 */
union bdk_rgxx_cmr_nic_nxc_adr
{
    uint64_t u;
    struct bdk_rgxx_cmr_nic_nxc_adr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t lmac_id               : 4;  /**< [ 15: 12](RO/H) Logged LMAC ID associated with NXC exceptions associated with NIC. */
        uint64_t channel               : 12; /**< [ 11:  0](RO/H) Logged channel for NXC exceptions associated with NIC. */
#else /* Word 0 - Little Endian */
        uint64_t channel               : 12; /**< [ 11:  0](RO/H) Logged channel for NXC exceptions associated with NIC. */
        uint64_t lmac_id               : 4;  /**< [ 15: 12](RO/H) Logged LMAC ID associated with NXC exceptions associated with NIC. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmr_nic_nxc_adr_s cn; */
};
typedef union bdk_rgxx_cmr_nic_nxc_adr bdk_rgxx_cmr_nic_nxc_adr_t;

static inline uint64_t BDK_RGXX_CMR_NIC_NXC_ADR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMR_NIC_NXC_ADR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8001030ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_CMR_NIC_NXC_ADR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMR_NIC_NXC_ADR(a) bdk_rgxx_cmr_nic_nxc_adr_t
#define bustype_BDK_RGXX_CMR_NIC_NXC_ADR(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMR_NIC_NXC_ADR(a) "RGXX_CMR_NIC_NXC_ADR"
#define device_bar_BDK_RGXX_CMR_NIC_NXC_ADR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMR_NIC_NXC_ADR(a) (a)
#define arguments_BDK_RGXX_CMR_NIC_NXC_ADR(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_cmr_pko_nxc_adr
 *
 * INTERNAL: RGX CMR PKO NXC Exception Registers
 */
union bdk_rgxx_cmr_pko_nxc_adr
{
    uint64_t u;
    struct bdk_rgxx_cmr_pko_nxc_adr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t lmac_id               : 4;  /**< [ 15: 12](RO/H) Logged LMAC ID associated with NXC exceptions associated with PKO. */
        uint64_t channel               : 12; /**< [ 11:  0](RO/H) Logged channel for NXC exceptions associated with PKO. */
#else /* Word 0 - Little Endian */
        uint64_t channel               : 12; /**< [ 11:  0](RO/H) Logged channel for NXC exceptions associated with PKO. */
        uint64_t lmac_id               : 4;  /**< [ 15: 12](RO/H) Logged LMAC ID associated with NXC exceptions associated with PKO. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmr_pko_nxc_adr_s cn; */
};
typedef union bdk_rgxx_cmr_pko_nxc_adr bdk_rgxx_cmr_pko_nxc_adr_t;

static inline uint64_t BDK_RGXX_CMR_PKO_NXC_ADR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMR_PKO_NXC_ADR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8001018ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_CMR_PKO_NXC_ADR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMR_PKO_NXC_ADR(a) bdk_rgxx_cmr_pko_nxc_adr_t
#define bustype_BDK_RGXX_CMR_PKO_NXC_ADR(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMR_PKO_NXC_ADR(a) "RGXX_CMR_PKO_NXC_ADR"
#define device_bar_BDK_RGXX_CMR_PKO_NXC_ADR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMR_PKO_NXC_ADR(a) (a)
#define arguments_BDK_RGXX_CMR_PKO_NXC_ADR(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_cmr_rx_dmac#_cam
 *
 * RGX CMR Receive CAM Registers
 * These registers provide access to the 32 DMAC CAM entries in RGX.
 */
union bdk_rgxx_cmr_rx_dmacx_cam
{
    uint64_t u;
    struct bdk_rgxx_cmr_rx_dmacx_cam_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t id                    : 2;  /**< [ 50: 49](R/W) Logical LMAC ID that this DMAC CAM address applies to. Must be 0. */
        uint64_t en                    : 1;  /**< [ 48: 48](R/W) CAM entry enable for this DMAC address.
                                                                 1 = Include this address in the matching algorithm.
                                                                 0 = Don't include this address in the matching algorithm. */
        uint64_t adr                   : 48; /**< [ 47:  0](R/W) DMAC address in the CAM used for matching. Specified in network byte order, i.e.
                                                                 ADR\<47:40\> is for the first DMAC byte on the wire. The CAM matches against unicast or
                                                                 multicast DMAC addresses. */
#else /* Word 0 - Little Endian */
        uint64_t adr                   : 48; /**< [ 47:  0](R/W) DMAC address in the CAM used for matching. Specified in network byte order, i.e.
                                                                 ADR\<47:40\> is for the first DMAC byte on the wire. The CAM matches against unicast or
                                                                 multicast DMAC addresses. */
        uint64_t en                    : 1;  /**< [ 48: 48](R/W) CAM entry enable for this DMAC address.
                                                                 1 = Include this address in the matching algorithm.
                                                                 0 = Don't include this address in the matching algorithm. */
        uint64_t id                    : 2;  /**< [ 50: 49](R/W) Logical LMAC ID that this DMAC CAM address applies to. Must be 0. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmr_rx_dmacx_cam_s cn; */
};
typedef union bdk_rgxx_cmr_rx_dmacx_cam bdk_rgxx_cmr_rx_dmacx_cam_t;

static inline uint64_t BDK_RGXX_CMR_RX_DMACX_CAM(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMR_RX_DMACX_CAM(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=31)))
        return 0x87e0e8000200ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1f);
    __bdk_csr_fatal("RGXX_CMR_RX_DMACX_CAM", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMR_RX_DMACX_CAM(a,b) bdk_rgxx_cmr_rx_dmacx_cam_t
#define bustype_BDK_RGXX_CMR_RX_DMACX_CAM(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMR_RX_DMACX_CAM(a,b) "RGXX_CMR_RX_DMACX_CAM"
#define device_bar_BDK_RGXX_CMR_RX_DMACX_CAM(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMR_RX_DMACX_CAM(a,b) (a)
#define arguments_BDK_RGXX_CMR_RX_DMACX_CAM(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr_rx_lmacs
 *
 * RGX CMR Receive Logical MACs Registers
 */
union bdk_rgxx_cmr_rx_lmacs
{
    uint64_t u;
    struct bdk_rgxx_cmr_rx_lmacs_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t lmacs                 : 3;  /**< [  2:  0](R/W) Number of LMACS. Specifies the number of LMACs that can be enabled.
                                                                 This determines the logical RX buffer size per LMAC and the maximum
                                                                 LMAC ID that can be used:

                                                                 0x0 = Reserved.
                                                                 0x1 = 16 KB per LMAC, maximum LMAC ID is 0.
                                                                 0x2-0x7 = Reserved.

                                                                 Note the maximum LMAC ID is determined by the smaller of
                                                                 RGX()_CMR_RX_LMACS[LMACS] and RGX()_CMR_TX_LMACS[LMACS]. The two fields
                                                                 should be set to the same value for normal operation. */
#else /* Word 0 - Little Endian */
        uint64_t lmacs                 : 3;  /**< [  2:  0](R/W) Number of LMACS. Specifies the number of LMACs that can be enabled.
                                                                 This determines the logical RX buffer size per LMAC and the maximum
                                                                 LMAC ID that can be used:

                                                                 0x0 = Reserved.
                                                                 0x1 = 16 KB per LMAC, maximum LMAC ID is 0.
                                                                 0x2-0x7 = Reserved.

                                                                 Note the maximum LMAC ID is determined by the smaller of
                                                                 RGX()_CMR_RX_LMACS[LMACS] and RGX()_CMR_TX_LMACS[LMACS]. The two fields
                                                                 should be set to the same value for normal operation. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmr_rx_lmacs_s cn; */
};
typedef union bdk_rgxx_cmr_rx_lmacs bdk_rgxx_cmr_rx_lmacs_t;

static inline uint64_t BDK_RGXX_CMR_RX_LMACS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMR_RX_LMACS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8000468ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_CMR_RX_LMACS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMR_RX_LMACS(a) bdk_rgxx_cmr_rx_lmacs_t
#define bustype_BDK_RGXX_CMR_RX_LMACS(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMR_RX_LMACS(a) "RGXX_CMR_RX_LMACS"
#define device_bar_BDK_RGXX_CMR_RX_LMACS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMR_RX_LMACS(a) (a)
#define arguments_BDK_RGXX_CMR_RX_LMACS(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_cmr_rx_ovr_bp
 *
 * RGX CMR Receive-Ports Backpressure Override Registers
 * Per-LMAC backpressure override register.
 */
union bdk_rgxx_cmr_rx_ovr_bp
{
    uint64_t u;
    struct bdk_rgxx_cmr_rx_ovr_bp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t en                    : 4;  /**< [ 11:  8](R/W) Per-LMAC enable backpressure override.
                                                                 0 = Don't enable.
                                                                 1 = Enable override.

                                                                 Bit\<8\> represents LMAC 0, ..., bit\<11\> represents LMAC 3. */
        uint64_t bp                    : 4;  /**< [  7:  4](R/W) Per-LMAC backpressure status to use:
                                                                 0 = LMAC is available.
                                                                 1 = LMAC should be backpressured.

                                                                 Bit\<4\> represents LMAC 0, ..., bit\<7\> represents LMAC 3. */
        uint64_t ign_fifo_bp           : 4;  /**< [  3:  0](R/W) Ignore RGX()_CMR()_RX_BP_ON[MARK] when computing backpressure. CMR does not backpressure
                                                                 the
                                                                 MAC due to the FIFO length passing RGX()_CMR()_RX_BP_ON[MARK]. */
#else /* Word 0 - Little Endian */
        uint64_t ign_fifo_bp           : 4;  /**< [  3:  0](R/W) Ignore RGX()_CMR()_RX_BP_ON[MARK] when computing backpressure. CMR does not backpressure
                                                                 the
                                                                 MAC due to the FIFO length passing RGX()_CMR()_RX_BP_ON[MARK]. */
        uint64_t bp                    : 4;  /**< [  7:  4](R/W) Per-LMAC backpressure status to use:
                                                                 0 = LMAC is available.
                                                                 1 = LMAC should be backpressured.

                                                                 Bit\<4\> represents LMAC 0, ..., bit\<7\> represents LMAC 3. */
        uint64_t en                    : 4;  /**< [ 11:  8](R/W) Per-LMAC enable backpressure override.
                                                                 0 = Don't enable.
                                                                 1 = Enable override.

                                                                 Bit\<8\> represents LMAC 0, ..., bit\<11\> represents LMAC 3. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmr_rx_ovr_bp_s cn; */
};
typedef union bdk_rgxx_cmr_rx_ovr_bp bdk_rgxx_cmr_rx_ovr_bp_t;

static inline uint64_t BDK_RGXX_CMR_RX_OVR_BP(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMR_RX_OVR_BP(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8000470ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_CMR_RX_OVR_BP", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMR_RX_OVR_BP(a) bdk_rgxx_cmr_rx_ovr_bp_t
#define bustype_BDK_RGXX_CMR_RX_OVR_BP(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMR_RX_OVR_BP(a) "RGXX_CMR_RX_OVR_BP"
#define device_bar_BDK_RGXX_CMR_RX_OVR_BP(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMR_RX_OVR_BP(a) (a)
#define arguments_BDK_RGXX_CMR_RX_OVR_BP(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_cmr_rx_stat10
 *
 * INTERNAL: RGX Receive Status Register 10
 *
 * Not applicable to RGX.
 *
 * This register provide a count of octets of dropped at the NCSI interface.
 */
union bdk_rgxx_cmr_rx_stat10
{
    uint64_t u;
    struct bdk_rgxx_cmr_rx_stat10_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Octet count of dropped NCSI packets. [CNT] will wrap and is cleared if NCSI is reset with
                                                                 RGX()_CMR_GLOBAL_CONFIG[CMR_NCSI_RESET]. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Octet count of dropped NCSI packets. [CNT] will wrap and is cleared if NCSI is reset with
                                                                 RGX()_CMR_GLOBAL_CONFIG[CMR_NCSI_RESET]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmr_rx_stat10_s cn; */
};
typedef union bdk_rgxx_cmr_rx_stat10 bdk_rgxx_cmr_rx_stat10_t;

static inline uint64_t BDK_RGXX_CMR_RX_STAT10(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMR_RX_STAT10(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e80000c0ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_CMR_RX_STAT10", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMR_RX_STAT10(a) bdk_rgxx_cmr_rx_stat10_t
#define bustype_BDK_RGXX_CMR_RX_STAT10(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMR_RX_STAT10(a) "RGXX_CMR_RX_STAT10"
#define device_bar_BDK_RGXX_CMR_RX_STAT10(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMR_RX_STAT10(a) (a)
#define arguments_BDK_RGXX_CMR_RX_STAT10(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_cmr_rx_stat9
 *
 * INTERNAL: RGX Receive Status Register 9
 *
 * Not applicable to RGX.
 *
 * This registers provides a count of packets dropped at the NCSI interface.
 * The count of dropped NCSI packets is not accounted for in any other stats
 * registers.
 */
union bdk_rgxx_cmr_rx_stat9
{
    uint64_t u;
    struct bdk_rgxx_cmr_rx_stat9_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of dropped packets. [CNT] will wrap and is cleared if NCSI is reset with
                                                                 RGX()_CMR_GLOBAL_CONFIG[CMR_NCSI_RESET]. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Count of dropped packets. [CNT] will wrap and is cleared if NCSI is reset with
                                                                 RGX()_CMR_GLOBAL_CONFIG[CMR_NCSI_RESET]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmr_rx_stat9_s cn; */
};
typedef union bdk_rgxx_cmr_rx_stat9 bdk_rgxx_cmr_rx_stat9_t;

static inline uint64_t BDK_RGXX_CMR_RX_STAT9(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMR_RX_STAT9(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e80000b8ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_CMR_RX_STAT9", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMR_RX_STAT9(a) bdk_rgxx_cmr_rx_stat9_t
#define bustype_BDK_RGXX_CMR_RX_STAT9(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMR_RX_STAT9(a) "RGXX_CMR_RX_STAT9"
#define device_bar_BDK_RGXX_CMR_RX_STAT9(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMR_RX_STAT9(a) (a)
#define arguments_BDK_RGXX_CMR_RX_STAT9(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_cmr_rx_steering#
 *
 * INTERNAL: RGX CMR Receive Steering Registers
 *
 * Not applicable to RGX.
 *
 * These registers, along with RGX()_CMR_RX_STEERING_VETYPE(), provide eight filters for
 * identifying and steering NCSI receive traffic.
 *
 * Steering is done for the designated LMAC specified by RGX()_CMR_GLOBAL_CONFIG[NCSI_LMAC_ID].
 * The steering algorithm is applied after the RX DMAC filter specified by
 * RGX()_CMR()_RX_DMAC_CTL and RGX()_CMR_RX_DMAC()_CAM. As such, the DMAC filter and steering
 * filters should be set in a consistent manner.
 *
 * Internal:
 * "* ALGORITHM
 * // Steering of RX packets for LMAC identified by RGX()_CMR_GLOBAL_CONFIG[NCSI_LMAC_ID].
 * rx_steering(uint48 pkt_dmac, uint16 pkt_etype, uint16 pkt_vlan_id) {
 *    for (int i = 0; i \< 8; i++) {
 *       steer = RGX()_CMR_RX_STEERING(i);
 *       vetype = RGX()_CMR_RX_STEERING_VETYPE(i);
 *       if (steer[MCST_EN] || steer[DMAC_EN] || vetype[VLAN_EN] || vetype[VLAN_TAG_EN]) {
 *          // Filter is enabled.
 *          if (   (!steer[MCST_EN] || is_mcst(pkt_dmac))
 *              && (!steer[DMAC_EN] || pkt_dmac != steer[DMAC])
 *              && (!vetype[VLAN_EN] || pkt_vlan_id != vetype[VLAN_ID])
 *              && (!vetype[VLAN_TAG_EN] || pkt_etype != vetype[VLAN_ETYPE]) )
 *          {
 *             // Filter match (all enabled matching criteria are met).
 *             return steer[DEST];
 *          }
 *       }
 *    }
 *    return RGX()_CMR_RX_STEERING_DEFAULT[DEST]; // No match
 * }"
 */
union bdk_rgxx_cmr_rx_steeringx
{
    uint64_t u;
    struct bdk_rgxx_cmr_rx_steeringx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t dest                  : 2;  /**< [ 51: 50](R/W) Destination for traffic that meets all criteria of the matching algorithm:
                                                                 0x0 = Steer this traffic exclusively to NCSI.
                                                                 0x1 = Steer this traffic exclusively to NIC.
                                                                 0x2 = Steer this traffic to BOTH NIC and NCSI.
                                                                 0x3 = Steer this traffic to the bit bucket (drop). */
        uint64_t mcst_en               : 1;  /**< [ 49: 49](R/W) Enable for identifying multicast packets:
                                                                 1 = Include multicast packets in the matching algorithm.
                                                                 0 = Do not include multicast packets in the matching algorithm. */
        uint64_t dmac_en               : 1;  /**< [ 48: 48](R/W) Enable DMAC address check:
                                                                 1 = Include DMAC address checking in the matching algorithm.
                                                                 0 = Do not include DMAC address checking in the matching algorithm. */
        uint64_t dmac                  : 48; /**< [ 47:  0](R/W) DMAC address used for the matching algorithm when [DMAC_EN] is set. Broadcast can be
                                                                 specified with value 0xFFFF_FFFFFFFF. */
#else /* Word 0 - Little Endian */
        uint64_t dmac                  : 48; /**< [ 47:  0](R/W) DMAC address used for the matching algorithm when [DMAC_EN] is set. Broadcast can be
                                                                 specified with value 0xFFFF_FFFFFFFF. */
        uint64_t dmac_en               : 1;  /**< [ 48: 48](R/W) Enable DMAC address check:
                                                                 1 = Include DMAC address checking in the matching algorithm.
                                                                 0 = Do not include DMAC address checking in the matching algorithm. */
        uint64_t mcst_en               : 1;  /**< [ 49: 49](R/W) Enable for identifying multicast packets:
                                                                 1 = Include multicast packets in the matching algorithm.
                                                                 0 = Do not include multicast packets in the matching algorithm. */
        uint64_t dest                  : 2;  /**< [ 51: 50](R/W) Destination for traffic that meets all criteria of the matching algorithm:
                                                                 0x0 = Steer this traffic exclusively to NCSI.
                                                                 0x1 = Steer this traffic exclusively to NIC.
                                                                 0x2 = Steer this traffic to BOTH NIC and NCSI.
                                                                 0x3 = Steer this traffic to the bit bucket (drop). */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmr_rx_steeringx_s cn; */
};
typedef union bdk_rgxx_cmr_rx_steeringx bdk_rgxx_cmr_rx_steeringx_t;

static inline uint64_t BDK_RGXX_CMR_RX_STEERINGX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMR_RX_STEERINGX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=7)))
        return 0x87e0e8000300ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x7);
    __bdk_csr_fatal("RGXX_CMR_RX_STEERINGX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMR_RX_STEERINGX(a,b) bdk_rgxx_cmr_rx_steeringx_t
#define bustype_BDK_RGXX_CMR_RX_STEERINGX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMR_RX_STEERINGX(a,b) "RGXX_CMR_RX_STEERINGX"
#define device_bar_BDK_RGXX_CMR_RX_STEERINGX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMR_RX_STEERINGX(a,b) (a)
#define arguments_BDK_RGXX_CMR_RX_STEERINGX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr_rx_steering_default
 *
 * INTERNAL: RGX CMR Receive Steering Default Destination Register
 *
 * Not applicable to RGX.
 */
union bdk_rgxx_cmr_rx_steering_default
{
    uint64_t u;
    struct bdk_rgxx_cmr_rx_steering_default_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t dest                  : 2;  /**< [  1:  0](R/W) Destination for traffic that does not match any of the steering filters specified by
                                                                 RGX()_CMR_RX_STEERING() and and RGX()_CMR_RX_STEERING_VETYPE():
                                                                 0x0 = Steer traffic exclusively to NCSI.
                                                                 0x1 = Steer traffic exclusively to NIC.
                                                                 0x2 = Steer traffic to BOTH NIC and NCSI.
                                                                 0x3 = Steer traffic to the bit bucket (drop). */
#else /* Word 0 - Little Endian */
        uint64_t dest                  : 2;  /**< [  1:  0](R/W) Destination for traffic that does not match any of the steering filters specified by
                                                                 RGX()_CMR_RX_STEERING() and and RGX()_CMR_RX_STEERING_VETYPE():
                                                                 0x0 = Steer traffic exclusively to NCSI.
                                                                 0x1 = Steer traffic exclusively to NIC.
                                                                 0x2 = Steer traffic to BOTH NIC and NCSI.
                                                                 0x3 = Steer traffic to the bit bucket (drop). */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmr_rx_steering_default_s cn; */
};
typedef union bdk_rgxx_cmr_rx_steering_default bdk_rgxx_cmr_rx_steering_default_t;

static inline uint64_t BDK_RGXX_CMR_RX_STEERING_DEFAULT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMR_RX_STEERING_DEFAULT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8000448ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_CMR_RX_STEERING_DEFAULT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMR_RX_STEERING_DEFAULT(a) bdk_rgxx_cmr_rx_steering_default_t
#define bustype_BDK_RGXX_CMR_RX_STEERING_DEFAULT(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMR_RX_STEERING_DEFAULT(a) "RGXX_CMR_RX_STEERING_DEFAULT"
#define device_bar_BDK_RGXX_CMR_RX_STEERING_DEFAULT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMR_RX_STEERING_DEFAULT(a) (a)
#define arguments_BDK_RGXX_CMR_RX_STEERING_DEFAULT(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_cmr_rx_steering_vetype#
 *
 * INTERNAL: RGX CMR Receive VLAN Ethertype Register
 *
 * Not applicable to RGX.
 *
 * These registers, along with RGX()_CMR_RX_STEERING(), provide eight filters for identifying and
 * steering NCSI receive traffic.
 */
union bdk_rgxx_cmr_rx_steering_vetypex
{
    uint64_t u;
    struct bdk_rgxx_cmr_rx_steering_vetypex_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_30_63        : 34;
        uint64_t vlan_en               : 1;  /**< [ 29: 29](R/W) Enable VLAN ID check:
                                                                 1 = Include VLAN ID checking in the matching algorithm.
                                                                 0 = Do not include VLAN ID checking in the matching algorithm. */
        uint64_t vlan_id               : 12; /**< [ 28: 17](R/W) VLAN ID used for the matching algorithm when [VLAN_EN] is set. */
        uint64_t vlan_tag_en           : 1;  /**< [ 16: 16](R/W) Enable VLAN tag Ethertype check:
                                                                 1 = Include VLAN tag Ethertype checking in the matching algorithm.
                                                                 0 = Do not include VLAN tag Ethertype checking in the matching algorithm. */
        uint64_t vlan_etype            : 16; /**< [ 15:  0](R/W) VLAN Ethertype for the matching algorithm when [VLAN_TAG_EN] is set.
                                                                 802.1Q and 802.1ad specify several Ethertypes used to identify VLAN tagged and VLAN double
                                                                 tagged packets. RGX will always match against the tag immediately following the SMAC
                                                                 address of the L2 header. */
#else /* Word 0 - Little Endian */
        uint64_t vlan_etype            : 16; /**< [ 15:  0](R/W) VLAN Ethertype for the matching algorithm when [VLAN_TAG_EN] is set.
                                                                 802.1Q and 802.1ad specify several Ethertypes used to identify VLAN tagged and VLAN double
                                                                 tagged packets. RGX will always match against the tag immediately following the SMAC
                                                                 address of the L2 header. */
        uint64_t vlan_tag_en           : 1;  /**< [ 16: 16](R/W) Enable VLAN tag Ethertype check:
                                                                 1 = Include VLAN tag Ethertype checking in the matching algorithm.
                                                                 0 = Do not include VLAN tag Ethertype checking in the matching algorithm. */
        uint64_t vlan_id               : 12; /**< [ 28: 17](R/W) VLAN ID used for the matching algorithm when [VLAN_EN] is set. */
        uint64_t vlan_en               : 1;  /**< [ 29: 29](R/W) Enable VLAN ID check:
                                                                 1 = Include VLAN ID checking in the matching algorithm.
                                                                 0 = Do not include VLAN ID checking in the matching algorithm. */
        uint64_t reserved_30_63        : 34;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmr_rx_steering_vetypex_s cn; */
};
typedef union bdk_rgxx_cmr_rx_steering_vetypex bdk_rgxx_cmr_rx_steering_vetypex_t;

static inline uint64_t BDK_RGXX_CMR_RX_STEERING_VETYPEX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMR_RX_STEERING_VETYPEX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=7)))
        return 0x87e0e8000400ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x7);
    __bdk_csr_fatal("RGXX_CMR_RX_STEERING_VETYPEX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMR_RX_STEERING_VETYPEX(a,b) bdk_rgxx_cmr_rx_steering_vetypex_t
#define bustype_BDK_RGXX_CMR_RX_STEERING_VETYPEX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMR_RX_STEERING_VETYPEX(a,b) "RGXX_CMR_RX_STEERING_VETYPEX"
#define device_bar_BDK_RGXX_CMR_RX_STEERING_VETYPEX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMR_RX_STEERING_VETYPEX(a,b) (a)
#define arguments_BDK_RGXX_CMR_RX_STEERING_VETYPEX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_cmr_tx_lmacs
 *
 * RGX CMR Transmit Logical MACs Registers
 * This register sets the number of LMACs allowed on the TX interface. The value is important for
 * defining the partitioning of the transmit FIFO.
 */
union bdk_rgxx_cmr_tx_lmacs
{
    uint64_t u;
    struct bdk_rgxx_cmr_tx_lmacs_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t lmacs                 : 3;  /**< [  2:  0](R/W) Number of LMACS: Specifies the number of LMACs that can be enabled.
                                                                 This determines the logical TX buffer size per LMAC and the maximum
                                                                 LMAC ID that can be used:

                                                                 0x0 = Reserved.
                                                                 0x1 = 12 KB per LMAC, maximum LMAC ID is 0.
                                                                 0x2-0x7 = Reserved.

                                                                 The maximum LMAC ID is determined by the smaller of RGX()_CMR_RX_LMACS[LMACS]
                                                                 and RGX()_CMR_TX_LMACS[LMACS]. The two fields should be set to the same value for
                                                                 normal operation.' */
#else /* Word 0 - Little Endian */
        uint64_t lmacs                 : 3;  /**< [  2:  0](R/W) Number of LMACS: Specifies the number of LMACs that can be enabled.
                                                                 This determines the logical TX buffer size per LMAC and the maximum
                                                                 LMAC ID that can be used:

                                                                 0x0 = Reserved.
                                                                 0x1 = 12 KB per LMAC, maximum LMAC ID is 0.
                                                                 0x2-0x7 = Reserved.

                                                                 The maximum LMAC ID is determined by the smaller of RGX()_CMR_RX_LMACS[LMACS]
                                                                 and RGX()_CMR_TX_LMACS[LMACS]. The two fields should be set to the same value for
                                                                 normal operation.' */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_cmr_tx_lmacs_s cn; */
};
typedef union bdk_rgxx_cmr_tx_lmacs bdk_rgxx_cmr_tx_lmacs_t;

static inline uint64_t BDK_RGXX_CMR_TX_LMACS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CMR_TX_LMACS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8001000ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_CMR_TX_LMACS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CMR_TX_LMACS(a) bdk_rgxx_cmr_tx_lmacs_t
#define bustype_BDK_RGXX_CMR_TX_LMACS(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CMR_TX_LMACS(a) "RGXX_CMR_TX_LMACS"
#define device_bar_BDK_RGXX_CMR_TX_LMACS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CMR_TX_LMACS(a) (a)
#define arguments_BDK_RGXX_CMR_TX_LMACS(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_const
 *
 * RGX CONST Registers
 * This register contains constants for software discovery.
 */
union bdk_rgxx_const
{
    uint64_t u;
    struct bdk_rgxx_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t lmacs                 : 8;  /**< [ 31: 24](RO) Number of LMACs.
                                                                 If 0x0, indicates 1 LMAC, otherwise, the number of LMACs. */
        uint64_t tx_fifosz             : 24; /**< [ 23:  0](RO) Number of bytes of transmit buffering in entire RGX. This buffering may be split
                                                                 between LMACs; see RGX()_CMR_TX_LMACS[LMACS].  If 0x0, indicates size of 0x3000. */
#else /* Word 0 - Little Endian */
        uint64_t tx_fifosz             : 24; /**< [ 23:  0](RO) Number of bytes of transmit buffering in entire RGX. This buffering may be split
                                                                 between LMACs; see RGX()_CMR_TX_LMACS[LMACS].  If 0x0, indicates size of 0x3000. */
        uint64_t lmacs                 : 8;  /**< [ 31: 24](RO) Number of LMACs.
                                                                 If 0x0, indicates 1 LMAC, otherwise, the number of LMACs. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_const_s cn; */
};
typedef union bdk_rgxx_const bdk_rgxx_const_t;

static inline uint64_t BDK_RGXX_CONST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CONST(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8040000ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_CONST", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CONST(a) bdk_rgxx_const_t
#define bustype_BDK_RGXX_CONST(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CONST(a) "RGXX_CONST"
#define device_bar_BDK_RGXX_CONST(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CONST(a) (a)
#define arguments_BDK_RGXX_CONST(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_const1
 *
 * RGX CONST1 Registers
 * This register contains constants for software discovery.
 */
union bdk_rgxx_const1
{
    uint64_t u;
    struct bdk_rgxx_const1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t res_types             : 24; /**< [ 31:  8](RO) Reserved for more LMAC TYPES. */
        uint64_t types                 : 8;  /**< [  7:  0](RO) LMAC types supported. Each bit if set corresponds to that value of
                                                                 BGX_LMAC_TYPES_E being supported. E.g. TYPES\<5\> if set indicates
                                                                 BGX_LMAC_TYPES_E::RGMII is supported. If 0x0, [TYPES] should be treated by
                                                                 software as if the read value was 0x20 (RGMII). */
#else /* Word 0 - Little Endian */
        uint64_t types                 : 8;  /**< [  7:  0](RO) LMAC types supported. Each bit if set corresponds to that value of
                                                                 BGX_LMAC_TYPES_E being supported. E.g. TYPES\<5\> if set indicates
                                                                 BGX_LMAC_TYPES_E::RGMII is supported. If 0x0, [TYPES] should be treated by
                                                                 software as if the read value was 0x20 (RGMII). */
        uint64_t res_types             : 24; /**< [ 31:  8](RO) Reserved for more LMAC TYPES. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_const1_s cn; */
};
typedef union bdk_rgxx_const1 bdk_rgxx_const1_t;

static inline uint64_t BDK_RGXX_CONST1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_CONST1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8040008ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_CONST1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_CONST1(a) bdk_rgxx_const1_t
#define bustype_BDK_RGXX_CONST1(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_CONST1(a) "RGXX_CONST1"
#define device_bar_BDK_RGXX_CONST1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_CONST1(a) (a)
#define arguments_BDK_RGXX_CONST1(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_prt#_cfg
 *
 * RGX GMP GMI LMAC Configuration Registers
 * This register controls the configuration of the LMAC.
 */
union bdk_rgxx_gmp_gmi_prtx_cfg
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_prtx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t tx_idle               : 1;  /**< [ 13: 13](RO/H) TX machine is idle. */
        uint64_t rx_idle               : 1;  /**< [ 12: 12](RO/H) RX machine is idle. */
        uint64_t reserved_9_11         : 3;
        uint64_t speed_msb             : 1;  /**< [  8:  8](R/W) Link speed MSB (SGMII/QSGMII/1000Base-X only). See [SPEED]. */
        uint64_t reserved_4_7          : 4;
        uint64_t slottime              : 1;  /**< [  3:  3](R/W) Slot time for half-duplex operation
                                                                 (SGMII/QSGMII/1000Base-X only):
                                                                 0 = 512 bit times (10/100 Mb/s operation).
                                                                 1 = 4096 bit times (1000 Mb/s operation). */
        uint64_t duplex                : 1;  /**< [  2:  2](R/W) Duplex mode
                                                                 (SGMII/QSGMII/1000Base-X only):
                                                                 0 = half-duplex (collisions/extensions/bursts):
                                                                 1 = full-duplex. */
        uint64_t speed                 : 1;  /**< [  1:  1](R/W) Link Speed LSB (SGMII/QSGMII/1000Base-X only):
                                                                 _ [SPEED_MSB,SPEED] = 0x0: 100 Mb/s operation.
                                                                 _ [SPEED_MSB,SPEED] = 0x1: 1000 Mb/s operation.
                                                                 _ [SPEED_MSB,SPEED] = 0x2: 10 Mb/s operation.
                                                                 _ [SPEED_MSB,SPEED] = 0x3: Reserved. */
        uint64_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0            : 1;
        uint64_t speed                 : 1;  /**< [  1:  1](R/W) Link Speed LSB (SGMII/QSGMII/1000Base-X only):
                                                                 _ [SPEED_MSB,SPEED] = 0x0: 100 Mb/s operation.
                                                                 _ [SPEED_MSB,SPEED] = 0x1: 1000 Mb/s operation.
                                                                 _ [SPEED_MSB,SPEED] = 0x2: 10 Mb/s operation.
                                                                 _ [SPEED_MSB,SPEED] = 0x3: Reserved. */
        uint64_t duplex                : 1;  /**< [  2:  2](R/W) Duplex mode
                                                                 (SGMII/QSGMII/1000Base-X only):
                                                                 0 = half-duplex (collisions/extensions/bursts):
                                                                 1 = full-duplex. */
        uint64_t slottime              : 1;  /**< [  3:  3](R/W) Slot time for half-duplex operation
                                                                 (SGMII/QSGMII/1000Base-X only):
                                                                 0 = 512 bit times (10/100 Mb/s operation).
                                                                 1 = 4096 bit times (1000 Mb/s operation). */
        uint64_t reserved_4_7          : 4;
        uint64_t speed_msb             : 1;  /**< [  8:  8](R/W) Link speed MSB (SGMII/QSGMII/1000Base-X only). See [SPEED]. */
        uint64_t reserved_9_11         : 3;
        uint64_t rx_idle               : 1;  /**< [ 12: 12](RO/H) RX machine is idle. */
        uint64_t tx_idle               : 1;  /**< [ 13: 13](RO/H) TX machine is idle. */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_prtx_cfg_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_prtx_cfg bdk_rgxx_gmp_gmi_prtx_cfg_t;

static inline uint64_t BDK_RGXX_GMP_GMI_PRTX_CFG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_PRTX_CFG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038020ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_PRTX_CFG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_PRTX_CFG(a,b) bdk_rgxx_gmp_gmi_prtx_cfg_t
#define bustype_BDK_RGXX_GMP_GMI_PRTX_CFG(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_PRTX_CFG(a,b) "RGXX_GMP_GMI_PRTX_CFG"
#define device_bar_BDK_RGXX_GMP_GMI_PRTX_CFG(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_PRTX_CFG(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_PRTX_CFG(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_rx#_decision
 *
 * RGX GMP Packet-Decision Registers
 * This register specifies the byte count used to determine when to accept or to filter a packet.
 * As each byte in a packet is received by GMI, the L2 byte count is compared against
 * [CNT]. In normal operation, the L2 header begins after the
 * PREAMBLE + SFD (RGX()_GMP_GMI_RX()_FRM_CTL[PRE_CHK] = 1) and any optional UDD skip
 * data (RGX()_GMP_GMI_RX()_UDD_SKP[LEN]).
 *
 * Internal:
 * Notes:
 * As each byte in a packet is received by GMI, the L2 byte count is compared
 * against the [CNT].  The L2 byte count is the number of bytes
 * from the beginning of the L2 header (DMAC).  In normal operation, the L2
 * header begins after the PREAMBLE+SFD (RGX()_GMP_GMI_RX()_FRM_CTL[PRE_CHK]=1) and any
 * optional UDD skip data (RGX()_GMP_GMI_RX()_UDD_SKP[LEN]).
 * When RGX()_GMP_GMI_RX()_FRM_CTL[PRE_CHK] is clear, PREAMBLE+SFD are prepended to the
 * packet and would require UDD skip length to account for them.
 *
 * Full Duplex:
 * _   L2 Size \<  [CNT] - Accept packet. No filtering is applied.
 * _   L2 Size \>= [CNT] - Apply filter. Accept packet based on PAUSE packet filter.
 *
 * Half Duplex:
 * _   L2 Size \<  [CNT] - Drop packet. Packet is unconditionally dropped.
 * _   L2 Size \>= [CNT] - Accept packet.
 *
 * where L2_size = MAX(0, total_packet_size - RGX()_GMP_GMI_RX()_UDD_SKP[LEN] -
 *                        ((RGX()_GMP_GMI_RX()_FRM_CTL[PRE_CHK]==1)*8))
 */
union bdk_rgxx_gmp_gmi_rxx_decision
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_rxx_decision_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t cnt                   : 5;  /**< [  4:  0](R/W) The byte count used to decide when to accept or filter a packet. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 5;  /**< [  4:  0](R/W) The byte count used to decide when to accept or filter a packet. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_rxx_decision_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_rxx_decision bdk_rgxx_gmp_gmi_rxx_decision_t;

static inline uint64_t BDK_RGXX_GMP_GMI_RXX_DECISION(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_RXX_DECISION(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038040ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_RXX_DECISION", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_RXX_DECISION(a,b) bdk_rgxx_gmp_gmi_rxx_decision_t
#define bustype_BDK_RGXX_GMP_GMI_RXX_DECISION(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_RXX_DECISION(a,b) "RGXX_GMP_GMI_RXX_DECISION"
#define device_bar_BDK_RGXX_GMP_GMI_RXX_DECISION(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_RXX_DECISION(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_RXX_DECISION(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_rx#_frm_chk
 *
 * RGX GMP Frame Check Registers
 */
union bdk_rgxx_gmp_gmi_rxx_frm_chk
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_rxx_frm_chk_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t skperr                : 1;  /**< [  8:  8](R/W) Skipper error. */
        uint64_t rcverr                : 1;  /**< [  7:  7](R/W) Frame was received with data-reception error. */
        uint64_t reserved_5_6          : 2;
        uint64_t fcserr                : 1;  /**< [  4:  4](R/W) Frame was received with FCS/CRC error. */
        uint64_t jabber                : 1;  /**< [  3:  3](R/W) Frame was received with length \> sys_length. */
        uint64_t reserved_2            : 1;
        uint64_t carext                : 1;  /**< [  1:  1](R/W) Carrier extend error. SGMII/QSGMII/1000Base-X only. */
        uint64_t minerr                : 1;  /**< [  0:  0](R/W) PAUSE frame was received with length \< minFrameSize. */
#else /* Word 0 - Little Endian */
        uint64_t minerr                : 1;  /**< [  0:  0](R/W) PAUSE frame was received with length \< minFrameSize. */
        uint64_t carext                : 1;  /**< [  1:  1](R/W) Carrier extend error. SGMII/QSGMII/1000Base-X only. */
        uint64_t reserved_2            : 1;
        uint64_t jabber                : 1;  /**< [  3:  3](R/W) Frame was received with length \> sys_length. */
        uint64_t fcserr                : 1;  /**< [  4:  4](R/W) Frame was received with FCS/CRC error. */
        uint64_t reserved_5_6          : 2;
        uint64_t rcverr                : 1;  /**< [  7:  7](R/W) Frame was received with data-reception error. */
        uint64_t skperr                : 1;  /**< [  8:  8](R/W) Skipper error. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_rxx_frm_chk_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_rxx_frm_chk bdk_rgxx_gmp_gmi_rxx_frm_chk_t;

static inline uint64_t BDK_RGXX_GMP_GMI_RXX_FRM_CHK(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_RXX_FRM_CHK(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038030ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_RXX_FRM_CHK", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_RXX_FRM_CHK(a,b) bdk_rgxx_gmp_gmi_rxx_frm_chk_t
#define bustype_BDK_RGXX_GMP_GMI_RXX_FRM_CHK(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_RXX_FRM_CHK(a,b) "RGXX_GMP_GMI_RXX_FRM_CHK"
#define device_bar_BDK_RGXX_GMP_GMI_RXX_FRM_CHK(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_RXX_FRM_CHK(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_RXX_FRM_CHK(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_rx#_frm_ctl
 *
 * RGX GMP Frame Control Registers
 * This register controls the handling of the frames.
 * The [CTL_BCK] and [CTL_DRP] bits control how the hardware handles incoming PAUSE packets. The
 * most
 * common modes of operation:
 * _ [CTL_BCK] = 1, [CTL_DRP] = 1: hardware handles everything.
 * _ [CTL_BCK] = 0, [CTL_DRP] = 0: software sees all PAUSE frames.
 * _ [CTL_BCK] = 0, [CTL_DRP] = 1: all PAUSE frames are completely ignored.
 *
 * These control bits should be set to [CTL_BCK] = 0, [CTL_DRP] = 0 in half-duplex mode. Since
 * PAUSE
 * packets only apply to full duplex operation, any PAUSE packet would constitute an exception
 * which should be handled by the processing cores. PAUSE packets should not be forwarded.
 *
 * Internal:
 * Notes:
 * [PRE_STRP]:
 * When [PRE_CHK] is set (indicating that the PREAMBLE will be sent), [PRE_STRP]
 * determines if the PREAMBLE+SFD bytes are thrown away or sent to the Octane
 * core as part of the packet.
 * In either mode, the PREAMBLE+SFD bytes are not counted toward the packet
 * size when checking against the MIN and MAX bounds.  Furthermore, the bytes
 * are skipped when locating the start of the L2 header for DMAC and Control
 * frame recognition.
 */
union bdk_rgxx_gmp_gmi_rxx_frm_ctl
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_rxx_frm_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t rx_fc_type            : 1;  /**< [ 13: 13](R/W) Receive side flow control type select.
                                                                 0 = GMI MAC receives and processes ITU G.999.1 pause frames.
                                                                 1 = GMI MAC receives and processes 802.3 pause frames. */
        uint64_t ptp_mode              : 1;  /**< [ 12: 12](R/W) Timestamp mode. When [PTP_MODE] is set, a 64-bit timestamp is prepended to every incoming
                                                                 packet.

                                                                 The timestamp bytes are added to the packet in such a way as to not modify the packet's
                                                                 receive byte count. This implies that the RGX()_GMP_GMI_RX()_JABBER,
                                                                 RGX()_GMP_GMI_RX()_DECISION, RGX()_GMP_GMI_RX()_UDD_SKP, and
                                                                 RGX()_CMR()_RX_STAT0..RGX()_CMR()_RX_STAT8
                                                                 do not require any adjustment as they operate on the received
                                                                 packet size. When the packet reaches NIC, its size reflects the additional bytes. */
        uint64_t reserved_11           : 1;
        uint64_t null_dis              : 1;  /**< [ 10: 10](R/W) When set, do not modify the MOD bits on NULL ticks due to partial packets. */
        uint64_t pre_align             : 1;  /**< [  9:  9](R/W) When set, PREAMBLE parser aligns the SFD byte regardless of the number of previous
                                                                 PREAMBLE nibbles. In this mode, [PRE_STRP] should be set to account for the variable
                                                                 nature of the PREAMBLE. [PRE_CHK] must be set to enable this and all PREAMBLE features.
                                                                 SGMII at 10/100Mbs only. */
        uint64_t reserved_7_8          : 2;
        uint64_t pre_free              : 1;  /**< [  6:  6](RO/H) When set, PREAMBLE checking is less strict. GMI will begin the frame at the first SFD.
                                                                 [PRE_CHK] must be set to enable this and all PREAMBLE features. SGMII/QSGMII/1000Base-X
                                                                 only. */
        uint64_t ctl_smac              : 1;  /**< [  5:  5](R/W) Control PAUSE frames can match station SMAC. */
        uint64_t ctl_mcst              : 1;  /**< [  4:  4](R/W) Control PAUSE frames can match globally assigned multicast address. */
        uint64_t ctl_bck               : 1;  /**< [  3:  3](R/W) Forward PAUSE information to TX block. */
        uint64_t ctl_drp               : 1;  /**< [  2:  2](R/W) Drop control-PAUSE frames. */
        uint64_t pre_strp              : 1;  /**< [  1:  1](R/W) Strip off the preamble (when present).
                                                                 0 = PREAMBLE + SFD is sent to core as part of frame.
                                                                 1 = PREAMBLE + SFD is dropped.
                                                                 [PRE_CHK] must be set to enable this and all PREAMBLE features.

                                                                 If [PTP_MODE]=1 and [PRE_CHK]=1, [PRE_STRP] must be 1.

                                                                 When [PRE_CHK] is set (indicating that the PREAMBLE will be sent), [PRE_STRP] determines
                                                                 if
                                                                 the PREAMBLE+SFD bytes are thrown away or sent to the core as part of the packet. In
                                                                 either mode, the PREAMBLE+SFD bytes are not counted toward the packet size when checking
                                                                 against the MIN and MAX bounds. Furthermore, the bytes are skipped when locating the start
                                                                 of the L2 header for DMAC and control frame recognition. */
        uint64_t pre_chk               : 1;  /**< [  0:  0](R/W) Check the preamble for correctness. This port is configured to send a valid 802.3 PREAMBLE
                                                                 to begin every frame. GMI checks that a valid PREAMBLE is received (based on [PRE_FREE]).
                                                                 When a problem does occur within the PREAMBLE sequence, the frame is marked as bad and not
                                                                 sent into the core. The RGX()_GMI()_RX_INT[PCTERR] interrupt is also raised. */
#else /* Word 0 - Little Endian */
        uint64_t pre_chk               : 1;  /**< [  0:  0](R/W) Check the preamble for correctness. This port is configured to send a valid 802.3 PREAMBLE
                                                                 to begin every frame. GMI checks that a valid PREAMBLE is received (based on [PRE_FREE]).
                                                                 When a problem does occur within the PREAMBLE sequence, the frame is marked as bad and not
                                                                 sent into the core. The RGX()_GMI()_RX_INT[PCTERR] interrupt is also raised. */
        uint64_t pre_strp              : 1;  /**< [  1:  1](R/W) Strip off the preamble (when present).
                                                                 0 = PREAMBLE + SFD is sent to core as part of frame.
                                                                 1 = PREAMBLE + SFD is dropped.
                                                                 [PRE_CHK] must be set to enable this and all PREAMBLE features.

                                                                 If [PTP_MODE]=1 and [PRE_CHK]=1, [PRE_STRP] must be 1.

                                                                 When [PRE_CHK] is set (indicating that the PREAMBLE will be sent), [PRE_STRP] determines
                                                                 if
                                                                 the PREAMBLE+SFD bytes are thrown away or sent to the core as part of the packet. In
                                                                 either mode, the PREAMBLE+SFD bytes are not counted toward the packet size when checking
                                                                 against the MIN and MAX bounds. Furthermore, the bytes are skipped when locating the start
                                                                 of the L2 header for DMAC and control frame recognition. */
        uint64_t ctl_drp               : 1;  /**< [  2:  2](R/W) Drop control-PAUSE frames. */
        uint64_t ctl_bck               : 1;  /**< [  3:  3](R/W) Forward PAUSE information to TX block. */
        uint64_t ctl_mcst              : 1;  /**< [  4:  4](R/W) Control PAUSE frames can match globally assigned multicast address. */
        uint64_t ctl_smac              : 1;  /**< [  5:  5](R/W) Control PAUSE frames can match station SMAC. */
        uint64_t pre_free              : 1;  /**< [  6:  6](RO/H) When set, PREAMBLE checking is less strict. GMI will begin the frame at the first SFD.
                                                                 [PRE_CHK] must be set to enable this and all PREAMBLE features. SGMII/QSGMII/1000Base-X
                                                                 only. */
        uint64_t reserved_7_8          : 2;
        uint64_t pre_align             : 1;  /**< [  9:  9](R/W) When set, PREAMBLE parser aligns the SFD byte regardless of the number of previous
                                                                 PREAMBLE nibbles. In this mode, [PRE_STRP] should be set to account for the variable
                                                                 nature of the PREAMBLE. [PRE_CHK] must be set to enable this and all PREAMBLE features.
                                                                 SGMII at 10/100Mbs only. */
        uint64_t null_dis              : 1;  /**< [ 10: 10](R/W) When set, do not modify the MOD bits on NULL ticks due to partial packets. */
        uint64_t reserved_11           : 1;
        uint64_t ptp_mode              : 1;  /**< [ 12: 12](R/W) Timestamp mode. When [PTP_MODE] is set, a 64-bit timestamp is prepended to every incoming
                                                                 packet.

                                                                 The timestamp bytes are added to the packet in such a way as to not modify the packet's
                                                                 receive byte count. This implies that the RGX()_GMP_GMI_RX()_JABBER,
                                                                 RGX()_GMP_GMI_RX()_DECISION, RGX()_GMP_GMI_RX()_UDD_SKP, and
                                                                 RGX()_CMR()_RX_STAT0..RGX()_CMR()_RX_STAT8
                                                                 do not require any adjustment as they operate on the received
                                                                 packet size. When the packet reaches NIC, its size reflects the additional bytes. */
        uint64_t rx_fc_type            : 1;  /**< [ 13: 13](R/W) Receive side flow control type select.
                                                                 0 = GMI MAC receives and processes ITU G.999.1 pause frames.
                                                                 1 = GMI MAC receives and processes 802.3 pause frames. */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } s;
    struct bdk_rgxx_gmp_gmi_rxx_frm_ctl_cn
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t rx_fc_type            : 1;  /**< [ 13: 13](R/W) Receive side flow control type select.
                                                                 0 = GMI MAC receives and processes ITU G.999.1 pause frames.
                                                                 1 = GMI MAC receives and processes 802.3 pause frames. */
        uint64_t ptp_mode              : 1;  /**< [ 12: 12](R/W) Timestamp mode. When [PTP_MODE] is set, a 64-bit timestamp is prepended to every incoming
                                                                 packet.

                                                                 The timestamp bytes are added to the packet in such a way as to not modify the packet's
                                                                 receive byte count. This implies that the RGX()_GMP_GMI_RX()_JABBER,
                                                                 RGX()_GMP_GMI_RX()_DECISION, RGX()_GMP_GMI_RX()_UDD_SKP, and
                                                                 RGX()_CMR()_RX_STAT0..RGX()_CMR()_RX_STAT8
                                                                 do not require any adjustment as they operate on the received
                                                                 packet size. When the packet reaches NIC, its size reflects the additional bytes. */
        uint64_t reserved_11           : 1;
        uint64_t null_dis              : 1;  /**< [ 10: 10](R/W) When set, do not modify the MOD bits on NULL ticks due to partial packets. */
        uint64_t pre_align             : 1;  /**< [  9:  9](R/W) When set, PREAMBLE parser aligns the SFD byte regardless of the number of previous
                                                                 PREAMBLE nibbles. In this mode, [PRE_STRP] should be set to account for the variable
                                                                 nature of the PREAMBLE. [PRE_CHK] must be set to enable this and all PREAMBLE features.
                                                                 SGMII at 10/100Mbs only. */
        uint64_t reserved_8            : 1;
        uint64_t reserved_7            : 1;
        uint64_t pre_free              : 1;  /**< [  6:  6](RO/H) When set, PREAMBLE checking is less strict. GMI will begin the frame at the first SFD.
                                                                 [PRE_CHK] must be set to enable this and all PREAMBLE features. SGMII/QSGMII/1000Base-X
                                                                 only. */
        uint64_t ctl_smac              : 1;  /**< [  5:  5](R/W) Control PAUSE frames can match station SMAC. */
        uint64_t ctl_mcst              : 1;  /**< [  4:  4](R/W) Control PAUSE frames can match globally assigned multicast address. */
        uint64_t ctl_bck               : 1;  /**< [  3:  3](R/W) Forward PAUSE information to TX block. */
        uint64_t ctl_drp               : 1;  /**< [  2:  2](R/W) Drop control-PAUSE frames. */
        uint64_t pre_strp              : 1;  /**< [  1:  1](R/W) Strip off the preamble (when present).
                                                                 0 = PREAMBLE + SFD is sent to core as part of frame.
                                                                 1 = PREAMBLE + SFD is dropped.
                                                                 [PRE_CHK] must be set to enable this and all PREAMBLE features.

                                                                 If [PTP_MODE]=1 and [PRE_CHK]=1, [PRE_STRP] must be 1.

                                                                 When [PRE_CHK] is set (indicating that the PREAMBLE will be sent), [PRE_STRP] determines
                                                                 if
                                                                 the PREAMBLE+SFD bytes are thrown away or sent to the core as part of the packet. In
                                                                 either mode, the PREAMBLE+SFD bytes are not counted toward the packet size when checking
                                                                 against the MIN and MAX bounds. Furthermore, the bytes are skipped when locating the start
                                                                 of the L2 header for DMAC and control frame recognition. */
        uint64_t pre_chk               : 1;  /**< [  0:  0](R/W) Check the preamble for correctness. This port is configured to send a valid 802.3 PREAMBLE
                                                                 to begin every frame. GMI checks that a valid PREAMBLE is received (based on [PRE_FREE]).
                                                                 When a problem does occur within the PREAMBLE sequence, the frame is marked as bad and not
                                                                 sent into the core. The RGX()_GMI()_RX_INT[PCTERR] interrupt is also raised. */
#else /* Word 0 - Little Endian */
        uint64_t pre_chk               : 1;  /**< [  0:  0](R/W) Check the preamble for correctness. This port is configured to send a valid 802.3 PREAMBLE
                                                                 to begin every frame. GMI checks that a valid PREAMBLE is received (based on [PRE_FREE]).
                                                                 When a problem does occur within the PREAMBLE sequence, the frame is marked as bad and not
                                                                 sent into the core. The RGX()_GMI()_RX_INT[PCTERR] interrupt is also raised. */
        uint64_t pre_strp              : 1;  /**< [  1:  1](R/W) Strip off the preamble (when present).
                                                                 0 = PREAMBLE + SFD is sent to core as part of frame.
                                                                 1 = PREAMBLE + SFD is dropped.
                                                                 [PRE_CHK] must be set to enable this and all PREAMBLE features.

                                                                 If [PTP_MODE]=1 and [PRE_CHK]=1, [PRE_STRP] must be 1.

                                                                 When [PRE_CHK] is set (indicating that the PREAMBLE will be sent), [PRE_STRP] determines
                                                                 if
                                                                 the PREAMBLE+SFD bytes are thrown away or sent to the core as part of the packet. In
                                                                 either mode, the PREAMBLE+SFD bytes are not counted toward the packet size when checking
                                                                 against the MIN and MAX bounds. Furthermore, the bytes are skipped when locating the start
                                                                 of the L2 header for DMAC and control frame recognition. */
        uint64_t ctl_drp               : 1;  /**< [  2:  2](R/W) Drop control-PAUSE frames. */
        uint64_t ctl_bck               : 1;  /**< [  3:  3](R/W) Forward PAUSE information to TX block. */
        uint64_t ctl_mcst              : 1;  /**< [  4:  4](R/W) Control PAUSE frames can match globally assigned multicast address. */
        uint64_t ctl_smac              : 1;  /**< [  5:  5](R/W) Control PAUSE frames can match station SMAC. */
        uint64_t pre_free              : 1;  /**< [  6:  6](RO/H) When set, PREAMBLE checking is less strict. GMI will begin the frame at the first SFD.
                                                                 [PRE_CHK] must be set to enable this and all PREAMBLE features. SGMII/QSGMII/1000Base-X
                                                                 only. */
        uint64_t reserved_7            : 1;
        uint64_t reserved_8            : 1;
        uint64_t pre_align             : 1;  /**< [  9:  9](R/W) When set, PREAMBLE parser aligns the SFD byte regardless of the number of previous
                                                                 PREAMBLE nibbles. In this mode, [PRE_STRP] should be set to account for the variable
                                                                 nature of the PREAMBLE. [PRE_CHK] must be set to enable this and all PREAMBLE features.
                                                                 SGMII at 10/100Mbs only. */
        uint64_t null_dis              : 1;  /**< [ 10: 10](R/W) When set, do not modify the MOD bits on NULL ticks due to partial packets. */
        uint64_t reserved_11           : 1;
        uint64_t ptp_mode              : 1;  /**< [ 12: 12](R/W) Timestamp mode. When [PTP_MODE] is set, a 64-bit timestamp is prepended to every incoming
                                                                 packet.

                                                                 The timestamp bytes are added to the packet in such a way as to not modify the packet's
                                                                 receive byte count. This implies that the RGX()_GMP_GMI_RX()_JABBER,
                                                                 RGX()_GMP_GMI_RX()_DECISION, RGX()_GMP_GMI_RX()_UDD_SKP, and
                                                                 RGX()_CMR()_RX_STAT0..RGX()_CMR()_RX_STAT8
                                                                 do not require any adjustment as they operate on the received
                                                                 packet size. When the packet reaches NIC, its size reflects the additional bytes. */
        uint64_t rx_fc_type            : 1;  /**< [ 13: 13](R/W) Receive side flow control type select.
                                                                 0 = GMI MAC receives and processes ITU G.999.1 pause frames.
                                                                 1 = GMI MAC receives and processes 802.3 pause frames. */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } cn;
};
typedef union bdk_rgxx_gmp_gmi_rxx_frm_ctl bdk_rgxx_gmp_gmi_rxx_frm_ctl_t;

static inline uint64_t BDK_RGXX_GMP_GMI_RXX_FRM_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_RXX_FRM_CTL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038028ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_RXX_FRM_CTL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_RXX_FRM_CTL(a,b) bdk_rgxx_gmp_gmi_rxx_frm_ctl_t
#define bustype_BDK_RGXX_GMP_GMI_RXX_FRM_CTL(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_RXX_FRM_CTL(a,b) "RGXX_GMP_GMI_RXX_FRM_CTL"
#define device_bar_BDK_RGXX_GMP_GMI_RXX_FRM_CTL(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_RXX_FRM_CTL(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_RXX_FRM_CTL(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_rx#_ifg
 *
 * RGX GMI Minimum Interframe-Gap Cycles Registers
 * This register specifies the minimum number of interframe-gap (IFG) cycles between packets.
 */
union bdk_rgxx_gmp_gmi_rxx_ifg
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_rxx_ifg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t ifg                   : 4;  /**< [  3:  0](R/W) Min IFG (in IFG * 8 bits) between packets used to determine IFGERR. Normally IFG is 96
                                                                 bits. Values 0x1 or smaller are illegal.

                                                                 Note that in some operating modes, IFG cycles can be inserted or removed in order to
                                                                 achieve clock rate adaptation. For these reasons, the default value is slightly
                                                                 conservative and does not check up to the full 96 bits of IFG.
                                                                 (SGMII/QSGMII/1000Base-X only) */
#else /* Word 0 - Little Endian */
        uint64_t ifg                   : 4;  /**< [  3:  0](R/W) Min IFG (in IFG * 8 bits) between packets used to determine IFGERR. Normally IFG is 96
                                                                 bits. Values 0x1 or smaller are illegal.

                                                                 Note that in some operating modes, IFG cycles can be inserted or removed in order to
                                                                 achieve clock rate adaptation. For these reasons, the default value is slightly
                                                                 conservative and does not check up to the full 96 bits of IFG.
                                                                 (SGMII/QSGMII/1000Base-X only) */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_rxx_ifg_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_rxx_ifg bdk_rgxx_gmp_gmi_rxx_ifg_t;

static inline uint64_t BDK_RGXX_GMP_GMI_RXX_IFG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_RXX_IFG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038058ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_RXX_IFG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_RXX_IFG(a,b) bdk_rgxx_gmp_gmi_rxx_ifg_t
#define bustype_BDK_RGXX_GMP_GMI_RXX_IFG(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_RXX_IFG(a,b) "RGXX_GMP_GMI_RXX_IFG"
#define device_bar_BDK_RGXX_GMP_GMI_RXX_IFG(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_RXX_IFG(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_RXX_IFG(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_rx#_int
 *
 * RGX GMP GMI RX Interrupt Registers
 * '"These registers allow interrupts to be sent to the control processor.
 * * Exception conditions \<10:0\> can also set the rcv/opcode in the received packet's work-queue
 * entry. RGX()_GMP_GMI_RX()_FRM_CHK provides a bit mask for configuring which conditions
 * set the error.
 * In half duplex operation, the expectation is that collisions will appear as either MINERR or
 * CAREXT errors.'
 *
 * Internal:
 * Notes:
 * (1) exception conditions 10:0 can also set the rcv/opcode in the received
 * packet's workQ entry.  The RGX()_GMP_GMI_RX()_FRM_CHK register provides a bit mask
 * for configuring which conditions set the error.
 *
 * (2) in half duplex operation, the expectation is that collisions will appear
 * as either MINERR o r CAREXT errors.
 *
 * (3) JABBER An RX jabber error indicates that a packet was received which
 * is longer than the maximum allowed packet as defined by the
 * system.  GMI will truncate the packet at the JABBER count.
 * Failure to do so could lead to system instabilty.
 *
 * (4) NIBERR This error is illegal at 1000Mbs speeds
 * (RGX()_GMP_GMI_PRT()_CFG[SPEED]==0) and will never assert.
 *
 * (5) MINERR total frame DA+SA+TL+DATA+PAD+FCS \< 64
 *
 * (6) ALNERR Indicates that the packet received was not an integer number of
 * bytes.  If FCS checking is enabled, ALNERR will only assert if
 * the FCS is bad.  If FCS checking is disabled, ALNERR will
 * assert in all non-integer frame cases.
 *
 * (7) Collisions Collisions can only occur in half-duplex mode.  A collision
 * is assumed by the receiver when the slottime
 * (RGX()_GMP_GMI_PRT()_CFG[SLOTTIME]) is not satisfied.  In 10/100 mode,
 * this will result in a frame \< SLOTTIME.  In 1000 mode, it
 * could result either in frame \< SLOTTIME or a carrier extend
 * error with the SLOTTIME.  These conditions are visible by...
 * . transfer ended before slottime COLDET
 * . carrier extend error           CAREXT
 *
 * (A) LENERR Length errors occur when the received packet does not match the
 * length field.  LENERR is only checked for packets between 64
 * and 1500 bytes.  For untagged frames, the length must exact
 * match.  For tagged frames the length or length+4 must match.
 *
 * (B) PCTERR checks that the frame begins with a valid PREAMBLE sequence.
 * Does not check the number of PREAMBLE cycles.
 *
 * (C) OVRERR *DON'T PUT IN HRM*
 * OVRERR is an architectural assertion check internal to GMI to
 * make sure no assumption was violated.  In a correctly operating
 * system, this interrupt can never fire.
 * GMI has an internal arbiter which selects which of 4 ports to
 * buffer in the main RX FIFO.  If we normally buffer 8 bytes,
 * then each port will typically push a tick every 8 cycles if
 * the packet interface is going as fast as possible.  If there
 * are four ports, they push every two cycles.  So that's the
 * assumption.  That the inbound module will always be able to
 * consume the tick before another is produced.  If that doesn't
 * happen that's when OVRERR will assert."
 */
union bdk_rgxx_gmp_gmi_rxx_int
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_rxx_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t ifgerr                : 1;  /**< [ 11: 11](R/W1C/H) Interframe gap violation. Does not necessarily indicate a failure. SGMII/QSGMII/1000Base-X only. */
        uint64_t coldet                : 1;  /**< [ 10: 10](R/W1C/H) Collision detection. Collisions can only occur in half-duplex mode. A collision is assumed
                                                                 by the receiver when the slottime (RGX()_GMP_GMI_PRT()_CFG[SLOTTIME]) is not
                                                                 satisfied. In 10/100 mode, this will result in a frame \< SLOTTIME. In 1000 mode, it could
                                                                 result either in frame \< SLOTTIME or a carrier extend error with the SLOTTIME. These
                                                                 conditions are visible by 1) transfer ended before slottime - COLDET or 2) carrier extend
                                                                 error - CAREXT. */
        uint64_t falerr                : 1;  /**< [  9:  9](R/W1C/H) False-carrier error, or carrier-extend error after slottime is satisfied.
                                                                 SGMII/QSGMII/1000Base-X only. */
        uint64_t rsverr                : 1;  /**< [  8:  8](R/W1C/H) Detected reserved opcode. */
        uint64_t pcterr                : 1;  /**< [  7:  7](R/W1C/H) Bad preamble/protocol error. Checks that the frame begins with a valid PREAMBLE sequence.
                                                                 Does not check the number of PREAMBLE cycles. */
        uint64_t ovrerr                : 1;  /**< [  6:  6](R/W1C/H) Internal data aggregation overflow. This interrupt should never assert.
                                                                 SGMII/QSGMII/1000Base-X only. */
        uint64_t skperr                : 1;  /**< [  5:  5](R/W1C/H) Skipper error. */
        uint64_t rcverr                : 1;  /**< [  4:  4](R/W1C/H) Data-reception error. Frame was received with data-reception error. */
        uint64_t fcserr                : 1;  /**< [  3:  3](R/W1C/H) FCS/CRC error. Frame was received with FCS/CRC error. */
        uint64_t jabber                : 1;  /**< [  2:  2](R/W1C/H) System-length error: frame was received with length \> sys_length.
                                                                 An RX Jabber error indicates that a packet was received which is longer than the maximum
                                                                 allowed packet as defined by the system. GMI truncates the packet at the JABBER count.
                                                                 Failure to do so could lead to system instability. */
        uint64_t carext                : 1;  /**< [  1:  1](R/W1C/H) Carrier-extend error. (SGMII/QSGMII/1000Base-X only) */
        uint64_t minerr                : 1;  /**< [  0:  0](R/W1C/H) PAUSE frame was received with length \< minFrameSize. Frame length checks are typically
                                                                 handled in NIC, but PAUSE frames are normally discarded before being inspected by NIC.
                                                                 Total frame DA+SA+TL+DATA+PAD+FCS \< 64. */
#else /* Word 0 - Little Endian */
        uint64_t minerr                : 1;  /**< [  0:  0](R/W1C/H) PAUSE frame was received with length \< minFrameSize. Frame length checks are typically
                                                                 handled in NIC, but PAUSE frames are normally discarded before being inspected by NIC.
                                                                 Total frame DA+SA+TL+DATA+PAD+FCS \< 64. */
        uint64_t carext                : 1;  /**< [  1:  1](R/W1C/H) Carrier-extend error. (SGMII/QSGMII/1000Base-X only) */
        uint64_t jabber                : 1;  /**< [  2:  2](R/W1C/H) System-length error: frame was received with length \> sys_length.
                                                                 An RX Jabber error indicates that a packet was received which is longer than the maximum
                                                                 allowed packet as defined by the system. GMI truncates the packet at the JABBER count.
                                                                 Failure to do so could lead to system instability. */
        uint64_t fcserr                : 1;  /**< [  3:  3](R/W1C/H) FCS/CRC error. Frame was received with FCS/CRC error. */
        uint64_t rcverr                : 1;  /**< [  4:  4](R/W1C/H) Data-reception error. Frame was received with data-reception error. */
        uint64_t skperr                : 1;  /**< [  5:  5](R/W1C/H) Skipper error. */
        uint64_t ovrerr                : 1;  /**< [  6:  6](R/W1C/H) Internal data aggregation overflow. This interrupt should never assert.
                                                                 SGMII/QSGMII/1000Base-X only. */
        uint64_t pcterr                : 1;  /**< [  7:  7](R/W1C/H) Bad preamble/protocol error. Checks that the frame begins with a valid PREAMBLE sequence.
                                                                 Does not check the number of PREAMBLE cycles. */
        uint64_t rsverr                : 1;  /**< [  8:  8](R/W1C/H) Detected reserved opcode. */
        uint64_t falerr                : 1;  /**< [  9:  9](R/W1C/H) False-carrier error, or carrier-extend error after slottime is satisfied.
                                                                 SGMII/QSGMII/1000Base-X only. */
        uint64_t coldet                : 1;  /**< [ 10: 10](R/W1C/H) Collision detection. Collisions can only occur in half-duplex mode. A collision is assumed
                                                                 by the receiver when the slottime (RGX()_GMP_GMI_PRT()_CFG[SLOTTIME]) is not
                                                                 satisfied. In 10/100 mode, this will result in a frame \< SLOTTIME. In 1000 mode, it could
                                                                 result either in frame \< SLOTTIME or a carrier extend error with the SLOTTIME. These
                                                                 conditions are visible by 1) transfer ended before slottime - COLDET or 2) carrier extend
                                                                 error - CAREXT. */
        uint64_t ifgerr                : 1;  /**< [ 11: 11](R/W1C/H) Interframe gap violation. Does not necessarily indicate a failure. SGMII/QSGMII/1000Base-X only. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_rxx_int_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_rxx_int bdk_rgxx_gmp_gmi_rxx_int_t;

static inline uint64_t BDK_RGXX_GMP_GMI_RXX_INT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_RXX_INT(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038000ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_RXX_INT", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_RXX_INT(a,b) bdk_rgxx_gmp_gmi_rxx_int_t
#define bustype_BDK_RGXX_GMP_GMI_RXX_INT(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_RXX_INT(a,b) "RGXX_GMP_GMI_RXX_INT"
#define device_bar_BDK_RGXX_GMP_GMI_RXX_INT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_RXX_INT(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_RXX_INT(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_rx#_int_ena_w1c
 *
 * RGX GMP GMI RX Interrupt Enable Clear Registers
 * This register clears interrupt enable bits.
 */
union bdk_rgxx_gmp_gmi_rxx_int_ena_w1c
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_rxx_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t ifgerr                : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[IFGERR]. */
        uint64_t coldet                : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[COLDET]. */
        uint64_t falerr                : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[FALERR]. */
        uint64_t rsverr                : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[RSVERR]. */
        uint64_t pcterr                : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[PCTERR]. */
        uint64_t ovrerr                : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[OVRERR]. */
        uint64_t skperr                : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[SKPERR]. */
        uint64_t rcverr                : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[RCVERR]. */
        uint64_t fcserr                : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[FCSERR]. */
        uint64_t jabber                : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[JABBER]. */
        uint64_t carext                : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[CAREXT]. */
        uint64_t minerr                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[MINERR]. */
#else /* Word 0 - Little Endian */
        uint64_t minerr                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[MINERR]. */
        uint64_t carext                : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[CAREXT]. */
        uint64_t jabber                : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[JABBER]. */
        uint64_t fcserr                : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[FCSERR]. */
        uint64_t rcverr                : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[RCVERR]. */
        uint64_t skperr                : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[SKPERR]. */
        uint64_t ovrerr                : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[OVRERR]. */
        uint64_t pcterr                : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[PCTERR]. */
        uint64_t rsverr                : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[RSVERR]. */
        uint64_t falerr                : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[FALERR]. */
        uint64_t coldet                : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[COLDET]. */
        uint64_t ifgerr                : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_RX(0)_INT[IFGERR]. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_rxx_int_ena_w1c_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_rxx_int_ena_w1c bdk_rgxx_gmp_gmi_rxx_int_ena_w1c_t;

static inline uint64_t BDK_RGXX_GMP_GMI_RXX_INT_ENA_W1C(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_RXX_INT_ENA_W1C(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038010ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_RXX_INT_ENA_W1C", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_RXX_INT_ENA_W1C(a,b) bdk_rgxx_gmp_gmi_rxx_int_ena_w1c_t
#define bustype_BDK_RGXX_GMP_GMI_RXX_INT_ENA_W1C(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_RXX_INT_ENA_W1C(a,b) "RGXX_GMP_GMI_RXX_INT_ENA_W1C"
#define device_bar_BDK_RGXX_GMP_GMI_RXX_INT_ENA_W1C(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_RXX_INT_ENA_W1C(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_RXX_INT_ENA_W1C(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_rx#_int_ena_w1s
 *
 * RGX GMP GMI RX Interrupt Enable Set Registers
 * This register sets interrupt enable bits.
 */
union bdk_rgxx_gmp_gmi_rxx_int_ena_w1s
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_rxx_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t ifgerr                : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[IFGERR]. */
        uint64_t coldet                : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[COLDET]. */
        uint64_t falerr                : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[FALERR]. */
        uint64_t rsverr                : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[RSVERR]. */
        uint64_t pcterr                : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[PCTERR]. */
        uint64_t ovrerr                : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[OVRERR]. */
        uint64_t skperr                : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[SKPERR]. */
        uint64_t rcverr                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[RCVERR]. */
        uint64_t fcserr                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[FCSERR]. */
        uint64_t jabber                : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[JABBER]. */
        uint64_t carext                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[CAREXT]. */
        uint64_t minerr                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[MINERR]. */
#else /* Word 0 - Little Endian */
        uint64_t minerr                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[MINERR]. */
        uint64_t carext                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[CAREXT]. */
        uint64_t jabber                : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[JABBER]. */
        uint64_t fcserr                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[FCSERR]. */
        uint64_t rcverr                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[RCVERR]. */
        uint64_t skperr                : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[SKPERR]. */
        uint64_t ovrerr                : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[OVRERR]. */
        uint64_t pcterr                : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[PCTERR]. */
        uint64_t rsverr                : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[RSVERR]. */
        uint64_t falerr                : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[FALERR]. */
        uint64_t coldet                : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[COLDET]. */
        uint64_t ifgerr                : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_RX(0)_INT[IFGERR]. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_rxx_int_ena_w1s_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_rxx_int_ena_w1s bdk_rgxx_gmp_gmi_rxx_int_ena_w1s_t;

static inline uint64_t BDK_RGXX_GMP_GMI_RXX_INT_ENA_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_RXX_INT_ENA_W1S(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038018ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_RXX_INT_ENA_W1S", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_RXX_INT_ENA_W1S(a,b) bdk_rgxx_gmp_gmi_rxx_int_ena_w1s_t
#define bustype_BDK_RGXX_GMP_GMI_RXX_INT_ENA_W1S(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_RXX_INT_ENA_W1S(a,b) "RGXX_GMP_GMI_RXX_INT_ENA_W1S"
#define device_bar_BDK_RGXX_GMP_GMI_RXX_INT_ENA_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_RXX_INT_ENA_W1S(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_RXX_INT_ENA_W1S(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_rx#_int_w1s
 *
 * RGX GMP GMI RX Interrupt Set Registers
 * This register sets interrupt bits.
 */
union bdk_rgxx_gmp_gmi_rxx_int_w1s
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_rxx_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t ifgerr                : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[IFGERR]. */
        uint64_t coldet                : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[COLDET]. */
        uint64_t falerr                : 1;  /**< [  9:  9](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[FALERR]. */
        uint64_t rsverr                : 1;  /**< [  8:  8](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[RSVERR]. */
        uint64_t pcterr                : 1;  /**< [  7:  7](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[PCTERR]. */
        uint64_t ovrerr                : 1;  /**< [  6:  6](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[OVRERR]. */
        uint64_t skperr                : 1;  /**< [  5:  5](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[SKPERR]. */
        uint64_t rcverr                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[RCVERR]. */
        uint64_t fcserr                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[FCSERR]. */
        uint64_t jabber                : 1;  /**< [  2:  2](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[JABBER]. */
        uint64_t carext                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[CAREXT]. */
        uint64_t minerr                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[MINERR]. */
#else /* Word 0 - Little Endian */
        uint64_t minerr                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[MINERR]. */
        uint64_t carext                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[CAREXT]. */
        uint64_t jabber                : 1;  /**< [  2:  2](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[JABBER]. */
        uint64_t fcserr                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[FCSERR]. */
        uint64_t rcverr                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[RCVERR]. */
        uint64_t skperr                : 1;  /**< [  5:  5](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[SKPERR]. */
        uint64_t ovrerr                : 1;  /**< [  6:  6](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[OVRERR]. */
        uint64_t pcterr                : 1;  /**< [  7:  7](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[PCTERR]. */
        uint64_t rsverr                : 1;  /**< [  8:  8](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[RSVERR]. */
        uint64_t falerr                : 1;  /**< [  9:  9](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[FALERR]. */
        uint64_t coldet                : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[COLDET]. */
        uint64_t ifgerr                : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_RX(0)_INT[IFGERR]. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_rxx_int_w1s_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_rxx_int_w1s bdk_rgxx_gmp_gmi_rxx_int_w1s_t;

static inline uint64_t BDK_RGXX_GMP_GMI_RXX_INT_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_RXX_INT_W1S(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038008ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_RXX_INT_W1S", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_RXX_INT_W1S(a,b) bdk_rgxx_gmp_gmi_rxx_int_w1s_t
#define bustype_BDK_RGXX_GMP_GMI_RXX_INT_W1S(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_RXX_INT_W1S(a,b) "RGXX_GMP_GMI_RXX_INT_W1S"
#define device_bar_BDK_RGXX_GMP_GMI_RXX_INT_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_RXX_INT_W1S(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_RXX_INT_W1S(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_rx#_jabber
 *
 * RGX GMP Maximum Packet-Size Registers
 * This register specifies the maximum size for packets, beyond which the GMI truncates.
 */
union bdk_rgxx_gmp_gmi_rxx_jabber
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_rxx_jabber_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t cnt                   : 16; /**< [ 15:  0](R/W) Byte count for jabber check. Failing packets set the JABBER interrupt and are optionally
                                                                 sent with opcode = JABBER. GMI truncates the packet to [CNT] bytes.
                                                                 [CNT] must be 8-byte aligned such that CNT\<2:0\> = 000. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 16; /**< [ 15:  0](R/W) Byte count for jabber check. Failing packets set the JABBER interrupt and are optionally
                                                                 sent with opcode = JABBER. GMI truncates the packet to [CNT] bytes.
                                                                 [CNT] must be 8-byte aligned such that CNT\<2:0\> = 000. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_rxx_jabber_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_rxx_jabber bdk_rgxx_gmp_gmi_rxx_jabber_t;

static inline uint64_t BDK_RGXX_GMP_GMI_RXX_JABBER(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_RXX_JABBER(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038038ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_RXX_JABBER", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_RXX_JABBER(a,b) bdk_rgxx_gmp_gmi_rxx_jabber_t
#define bustype_BDK_RGXX_GMP_GMI_RXX_JABBER(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_RXX_JABBER(a,b) "RGXX_GMP_GMI_RXX_JABBER"
#define device_bar_BDK_RGXX_GMP_GMI_RXX_JABBER(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_RXX_JABBER(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_RXX_JABBER(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_rx#_udd_skp
 *
 * RGX GMP GMI User-Defined Data Skip Registers
 * This register specifies the amount of user-defined data (UDD) added before the start of the
 * L2C data.
 *
 * Internal:
 * Notes:
 * (1) The skip bytes are part of the packet and will be handled by NIC.
 *
 * (2) The system can determine if the UDD bytes are included in the FCS check
 * by using the FCSSEL field - if the FCS check is enabled.
 *
 * (3) Assume that the preamble/sfd is always at the start of the frame - even
 * before UDD bytes.  In most cases, there will be no preamble in these
 * cases since it will be packet interface in direct communication to
 * another packet interface (MAC to MAC) without a PHY involved.
 *
 * (4) We can still do address filtering and control packet filtering is the
 * user desires.
 *
 * (5) RGX()_GMP_GMI_RX()_UDD_SKP[LEN] must be 0 in half-duplex operation unless
 * RGX()_GMP_GMI_RX()_FRM_CTL[PRE_CHK] is clear.  If RGX()_GMP_GMI_RX()_FRM_CTL[PRE_CHK] is
 * clear,
 * then RGX()_GMP_GMI_RX()_UDD_SKP[LEN] will normally be 8.
 *
 * (6) In all cases, the UDD bytes will be sent down the packet interface as
 * part of the packet.  The UDD bytes are never stripped from the actual
 * packet.
 */
union bdk_rgxx_gmp_gmi_rxx_udd_skp
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_rxx_udd_skp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t fcssel                : 1;  /**< [  8:  8](R/W) Include the skip bytes in the FCS calculation.
                                                                 0 = All skip bytes are included in FCS.
                                                                 1 = The skip bytes are not included in FCS.

                                                                 The skip bytes are part of the packet and are
                                                                 handled by NIC. The system can determine if the UDD bytes are included in the FCS check by
                                                                 using [FCSSEL], if the FCS check is enabled. */
        uint64_t reserved_7            : 1;
        uint64_t len                   : 7;  /**< [  6:  0](R/W) Amount of user-defined data before the start of the L2C data, in bytes.
                                                                 Setting to 0 means L2C comes first; maximum value is 64.
                                                                 LEN must be 0x0 in half-duplex operation.

                                                                 If LEN != 0, then RGX()_GMP_GMI_RX()_FRM_CHK[MINERR] will be disabled and
                                                                 RGX()_GMP_GMI_RX()_INT[MINERR] will be zero. */
#else /* Word 0 - Little Endian */
        uint64_t len                   : 7;  /**< [  6:  0](R/W) Amount of user-defined data before the start of the L2C data, in bytes.
                                                                 Setting to 0 means L2C comes first; maximum value is 64.
                                                                 LEN must be 0x0 in half-duplex operation.

                                                                 If LEN != 0, then RGX()_GMP_GMI_RX()_FRM_CHK[MINERR] will be disabled and
                                                                 RGX()_GMP_GMI_RX()_INT[MINERR] will be zero. */
        uint64_t reserved_7            : 1;
        uint64_t fcssel                : 1;  /**< [  8:  8](R/W) Include the skip bytes in the FCS calculation.
                                                                 0 = All skip bytes are included in FCS.
                                                                 1 = The skip bytes are not included in FCS.

                                                                 The skip bytes are part of the packet and are
                                                                 handled by NIC. The system can determine if the UDD bytes are included in the FCS check by
                                                                 using [FCSSEL], if the FCS check is enabled. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_rxx_udd_skp_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_rxx_udd_skp bdk_rgxx_gmp_gmi_rxx_udd_skp_t;

static inline uint64_t BDK_RGXX_GMP_GMI_RXX_UDD_SKP(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_RXX_UDD_SKP(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038048ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_RXX_UDD_SKP", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_RXX_UDD_SKP(a,b) bdk_rgxx_gmp_gmi_rxx_udd_skp_t
#define bustype_BDK_RGXX_GMP_GMI_RXX_UDD_SKP(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_RXX_UDD_SKP(a,b) "RGXX_GMP_GMI_RXX_UDD_SKP"
#define device_bar_BDK_RGXX_GMP_GMI_RXX_UDD_SKP(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_RXX_UDD_SKP(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_RXX_UDD_SKP(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_smac#
 *
 * RGX GMI SMAC Registers
 */
union bdk_rgxx_gmp_gmi_smacx
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_smacx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t smac                  : 48; /**< [ 47:  0](R/W) The SMAC field is used for generating and accepting control PAUSE packets. */
#else /* Word 0 - Little Endian */
        uint64_t smac                  : 48; /**< [ 47:  0](R/W) The SMAC field is used for generating and accepting control PAUSE packets. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_smacx_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_smacx bdk_rgxx_gmp_gmi_smacx_t;

static inline uint64_t BDK_RGXX_GMP_GMI_SMACX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_SMACX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038230ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_SMACX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_SMACX(a,b) bdk_rgxx_gmp_gmi_smacx_t
#define bustype_BDK_RGXX_GMP_GMI_SMACX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_SMACX(a,b) "RGXX_GMP_GMI_SMACX"
#define device_bar_BDK_RGXX_GMP_GMI_SMACX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_SMACX(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_SMACX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_tx#_append
 *
 * RGX GMI TX Append Control Registers
 */
union bdk_rgxx_gmp_gmi_txx_append
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_txx_append_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t force_fcs             : 1;  /**< [  3:  3](R/W) Append the Ethernet FCS on each PAUSE packet. */
        uint64_t fcs                   : 1;  /**< [  2:  2](R/W) Append the Ethernet FCS on each packet. */
        uint64_t pad                   : 1;  /**< [  1:  1](R/W) Append PAD bytes such that minimum-sized packet is transmitted. */
        uint64_t preamble              : 1;  /**< [  0:  0](R/W) Prepend the Ethernet preamble on each transfer. */
#else /* Word 0 - Little Endian */
        uint64_t preamble              : 1;  /**< [  0:  0](R/W) Prepend the Ethernet preamble on each transfer. */
        uint64_t pad                   : 1;  /**< [  1:  1](R/W) Append PAD bytes such that minimum-sized packet is transmitted. */
        uint64_t fcs                   : 1;  /**< [  2:  2](R/W) Append the Ethernet FCS on each packet. */
        uint64_t force_fcs             : 1;  /**< [  3:  3](R/W) Append the Ethernet FCS on each PAUSE packet. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_txx_append_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_txx_append bdk_rgxx_gmp_gmi_txx_append_t;

static inline uint64_t BDK_RGXX_GMP_GMI_TXX_APPEND(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_TXX_APPEND(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038218ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_TXX_APPEND", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_TXX_APPEND(a,b) bdk_rgxx_gmp_gmi_txx_append_t
#define bustype_BDK_RGXX_GMP_GMI_TXX_APPEND(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_TXX_APPEND(a,b) "RGXX_GMP_GMI_TXX_APPEND"
#define device_bar_BDK_RGXX_GMP_GMI_TXX_APPEND(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_TXX_APPEND(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_TXX_APPEND(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_tx#_burst
 *
 * RGX GMI TX Burst-Counter Registers
 */
union bdk_rgxx_gmp_gmi_txx_burst
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_txx_burst_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t burst                 : 16; /**< [ 15:  0](R/W) Burst (refer to 802.3 to set correctly). Only valid for 1000Mb/s half-duplex operation as
                                                                 follows:
                                                                 half duplex/1000Mb/s: 0x2000
                                                                 all other modes: 0x0
                                                                 SGMII/QSGMII/1000Base-X only. */
#else /* Word 0 - Little Endian */
        uint64_t burst                 : 16; /**< [ 15:  0](R/W) Burst (refer to 802.3 to set correctly). Only valid for 1000Mb/s half-duplex operation as
                                                                 follows:
                                                                 half duplex/1000Mb/s: 0x2000
                                                                 all other modes: 0x0
                                                                 SGMII/QSGMII/1000Base-X only. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_txx_burst_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_txx_burst bdk_rgxx_gmp_gmi_txx_burst_t;

static inline uint64_t BDK_RGXX_GMP_GMI_TXX_BURST(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_TXX_BURST(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038228ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_TXX_BURST", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_TXX_BURST(a,b) bdk_rgxx_gmp_gmi_txx_burst_t
#define bustype_BDK_RGXX_GMP_GMI_TXX_BURST(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_TXX_BURST(a,b) "RGXX_GMP_GMI_TXX_BURST"
#define device_bar_BDK_RGXX_GMP_GMI_TXX_BURST(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_TXX_BURST(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_TXX_BURST(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_tx#_ctl
 *
 * RGX GMI Transmit Control Registers
 */
union bdk_rgxx_gmp_gmi_txx_ctl
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_txx_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t tx_fc_type            : 1;  /**< [  2:  2](R/W) Transmit side flow control type select.
                                                                 0 = GMI MAC transmits ITU G.999.1 pause frames.
                                                                 1 = GMI MAC transmits 802.3 pause frames. */
        uint64_t xsdef_en              : 1;  /**< [  1:  1](R/W) Enables the excessive-deferral check for statistics and interrupts. SGMII/1000Base-X half-
                                                                 duplex only. */
        uint64_t xscol_en              : 1;  /**< [  0:  0](R/W) Enables the excessive-collision check for statistics and interrupts. SGMII/1000Base-X
                                                                 half-duplex only. */
#else /* Word 0 - Little Endian */
        uint64_t xscol_en              : 1;  /**< [  0:  0](R/W) Enables the excessive-collision check for statistics and interrupts. SGMII/1000Base-X
                                                                 half-duplex only. */
        uint64_t xsdef_en              : 1;  /**< [  1:  1](R/W) Enables the excessive-deferral check for statistics and interrupts. SGMII/1000Base-X half-
                                                                 duplex only. */
        uint64_t tx_fc_type            : 1;  /**< [  2:  2](R/W) Transmit side flow control type select.
                                                                 0 = GMI MAC transmits ITU G.999.1 pause frames.
                                                                 1 = GMI MAC transmits 802.3 pause frames. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_txx_ctl_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_txx_ctl bdk_rgxx_gmp_gmi_txx_ctl_t;

static inline uint64_t BDK_RGXX_GMP_GMI_TXX_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_TXX_CTL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038270ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_TXX_CTL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_TXX_CTL(a,b) bdk_rgxx_gmp_gmi_txx_ctl_t
#define bustype_BDK_RGXX_GMP_GMI_TXX_CTL(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_TXX_CTL(a,b) "RGXX_GMP_GMI_TXX_CTL"
#define device_bar_BDK_RGXX_GMP_GMI_TXX_CTL(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_TXX_CTL(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_TXX_CTL(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_tx#_int
 *
 * RGX GMI TX Interrupt Registers
 */
union bdk_rgxx_gmp_gmi_txx_int
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_txx_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t ptp_lost              : 1;  /**< [  4:  4](R/W1C/H) A packet with a PTP request was not able to be sent due to XSCOL. */
        uint64_t late_col              : 1;  /**< [  3:  3](R/W1C/H) TX late collision. (SGMII/1000BASE-X half-duplex only) */
        uint64_t xsdef                 : 1;  /**< [  2:  2](R/W1C/H) TX excessive deferral. (SGMII/1000BASE-X half-duplex only) */
        uint64_t xscol                 : 1;  /**< [  1:  1](R/W1C/H) TX excessive collisions. (SGMII/1000BASE-X half-duplex only) */
        uint64_t undflw                : 1;  /**< [  0:  0](R/W1C/H) TX underflow. */
#else /* Word 0 - Little Endian */
        uint64_t undflw                : 1;  /**< [  0:  0](R/W1C/H) TX underflow. */
        uint64_t xscol                 : 1;  /**< [  1:  1](R/W1C/H) TX excessive collisions. (SGMII/1000BASE-X half-duplex only) */
        uint64_t xsdef                 : 1;  /**< [  2:  2](R/W1C/H) TX excessive deferral. (SGMII/1000BASE-X half-duplex only) */
        uint64_t late_col              : 1;  /**< [  3:  3](R/W1C/H) TX late collision. (SGMII/1000BASE-X half-duplex only) */
        uint64_t ptp_lost              : 1;  /**< [  4:  4](R/W1C/H) A packet with a PTP request was not able to be sent due to XSCOL. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_txx_int_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_txx_int bdk_rgxx_gmp_gmi_txx_int_t;

static inline uint64_t BDK_RGXX_GMP_GMI_TXX_INT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_TXX_INT(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038500ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_TXX_INT", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_TXX_INT(a,b) bdk_rgxx_gmp_gmi_txx_int_t
#define bustype_BDK_RGXX_GMP_GMI_TXX_INT(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_TXX_INT(a,b) "RGXX_GMP_GMI_TXX_INT"
#define device_bar_BDK_RGXX_GMP_GMI_TXX_INT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_TXX_INT(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_TXX_INT(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_tx#_int_ena_w1c
 *
 * RGX GMI TX Interrupt Enable Clear Registers
 * This register clears interrupt enable bits.
 */
union bdk_rgxx_gmp_gmi_txx_int_ena_w1c
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_txx_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t ptp_lost              : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_TX(0)_INT[PTP_LOST]. */
        uint64_t late_col              : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_TX(0)_INT[LATE_COL]. */
        uint64_t xsdef                 : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_TX(0)_INT[XSDEF]. */
        uint64_t xscol                 : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_TX(0)_INT[XSCOL]. */
        uint64_t undflw                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_TX(0)_INT[UNDFLW]. */
#else /* Word 0 - Little Endian */
        uint64_t undflw                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_TX(0)_INT[UNDFLW]. */
        uint64_t xscol                 : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_TX(0)_INT[XSCOL]. */
        uint64_t xsdef                 : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_TX(0)_INT[XSDEF]. */
        uint64_t late_col              : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_TX(0)_INT[LATE_COL]. */
        uint64_t ptp_lost              : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for RGX(0)_GMP_GMI_TX(0)_INT[PTP_LOST]. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_txx_int_ena_w1c_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_txx_int_ena_w1c bdk_rgxx_gmp_gmi_txx_int_ena_w1c_t;

static inline uint64_t BDK_RGXX_GMP_GMI_TXX_INT_ENA_W1C(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_TXX_INT_ENA_W1C(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038510ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_TXX_INT_ENA_W1C", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_TXX_INT_ENA_W1C(a,b) bdk_rgxx_gmp_gmi_txx_int_ena_w1c_t
#define bustype_BDK_RGXX_GMP_GMI_TXX_INT_ENA_W1C(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_TXX_INT_ENA_W1C(a,b) "RGXX_GMP_GMI_TXX_INT_ENA_W1C"
#define device_bar_BDK_RGXX_GMP_GMI_TXX_INT_ENA_W1C(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_TXX_INT_ENA_W1C(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_TXX_INT_ENA_W1C(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_tx#_int_ena_w1s
 *
 * RGX GMI TX Interrupt Enable Set Registers
 * This register sets interrupt enable bits.
 */
union bdk_rgxx_gmp_gmi_txx_int_ena_w1s
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_txx_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t ptp_lost              : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_TX(0)_INT[PTP_LOST]. */
        uint64_t late_col              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_TX(0)_INT[LATE_COL]. */
        uint64_t xsdef                 : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_TX(0)_INT[XSDEF]. */
        uint64_t xscol                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_TX(0)_INT[XSCOL]. */
        uint64_t undflw                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_TX(0)_INT[UNDFLW]. */
#else /* Word 0 - Little Endian */
        uint64_t undflw                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_TX(0)_INT[UNDFLW]. */
        uint64_t xscol                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_TX(0)_INT[XSCOL]. */
        uint64_t xsdef                 : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_TX(0)_INT[XSDEF]. */
        uint64_t late_col              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_TX(0)_INT[LATE_COL]. */
        uint64_t ptp_lost              : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for RGX(0)_GMP_GMI_TX(0)_INT[PTP_LOST]. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_txx_int_ena_w1s_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_txx_int_ena_w1s bdk_rgxx_gmp_gmi_txx_int_ena_w1s_t;

static inline uint64_t BDK_RGXX_GMP_GMI_TXX_INT_ENA_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_TXX_INT_ENA_W1S(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038518ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_TXX_INT_ENA_W1S", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_TXX_INT_ENA_W1S(a,b) bdk_rgxx_gmp_gmi_txx_int_ena_w1s_t
#define bustype_BDK_RGXX_GMP_GMI_TXX_INT_ENA_W1S(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_TXX_INT_ENA_W1S(a,b) "RGXX_GMP_GMI_TXX_INT_ENA_W1S"
#define device_bar_BDK_RGXX_GMP_GMI_TXX_INT_ENA_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_TXX_INT_ENA_W1S(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_TXX_INT_ENA_W1S(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_tx#_int_w1s
 *
 * RGX GMI TX Interrupt Set Registers
 * This register sets interrupt bits.
 */
union bdk_rgxx_gmp_gmi_txx_int_w1s
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_txx_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t ptp_lost              : 1;  /**< [  4:  4](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_TX(0)_INT[PTP_LOST]. */
        uint64_t late_col              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_TX(0)_INT[LATE_COL]. */
        uint64_t xsdef                 : 1;  /**< [  2:  2](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_TX(0)_INT[XSDEF]. */
        uint64_t xscol                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_TX(0)_INT[XSCOL]. */
        uint64_t undflw                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_TX(0)_INT[UNDFLW]. */
#else /* Word 0 - Little Endian */
        uint64_t undflw                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_TX(0)_INT[UNDFLW]. */
        uint64_t xscol                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_TX(0)_INT[XSCOL]. */
        uint64_t xsdef                 : 1;  /**< [  2:  2](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_TX(0)_INT[XSDEF]. */
        uint64_t late_col              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_TX(0)_INT[LATE_COL]. */
        uint64_t ptp_lost              : 1;  /**< [  4:  4](R/W1S/H) Reads or sets RGX(0)_GMP_GMI_TX(0)_INT[PTP_LOST]. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_txx_int_w1s_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_txx_int_w1s bdk_rgxx_gmp_gmi_txx_int_w1s_t;

static inline uint64_t BDK_RGXX_GMP_GMI_TXX_INT_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_TXX_INT_W1S(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038508ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_TXX_INT_W1S", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_TXX_INT_W1S(a,b) bdk_rgxx_gmp_gmi_txx_int_w1s_t
#define bustype_BDK_RGXX_GMP_GMI_TXX_INT_W1S(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_TXX_INT_W1S(a,b) "RGXX_GMP_GMI_TXX_INT_W1S"
#define device_bar_BDK_RGXX_GMP_GMI_TXX_INT_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_TXX_INT_W1S(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_TXX_INT_W1S(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_tx#_min_pkt
 *
 * RGX GMI TX Minimum-Size-Packet Registers
 */
union bdk_rgxx_gmp_gmi_txx_min_pkt
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_txx_min_pkt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t min_size              : 8;  /**< [  7:  0](R/W) Minimum frame size in bytes before the FCS is applied.
                                                                 Padding is only appended when RGX()_GMP_GMI_TX()_APPEND[PAD] for the corresponding
                                                                 LMAC is set.

                                                                 Packets are padded to [MIN_SIZE]+1. The reset value pads to 60 bytes. */
#else /* Word 0 - Little Endian */
        uint64_t min_size              : 8;  /**< [  7:  0](R/W) Minimum frame size in bytes before the FCS is applied.
                                                                 Padding is only appended when RGX()_GMP_GMI_TX()_APPEND[PAD] for the corresponding
                                                                 LMAC is set.

                                                                 Packets are padded to [MIN_SIZE]+1. The reset value pads to 60 bytes. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_txx_min_pkt_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_txx_min_pkt bdk_rgxx_gmp_gmi_txx_min_pkt_t;

static inline uint64_t BDK_RGXX_GMP_GMI_TXX_MIN_PKT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_TXX_MIN_PKT(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038240ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_TXX_MIN_PKT", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_TXX_MIN_PKT(a,b) bdk_rgxx_gmp_gmi_txx_min_pkt_t
#define bustype_BDK_RGXX_GMP_GMI_TXX_MIN_PKT(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_TXX_MIN_PKT(a,b) "RGXX_GMP_GMI_TXX_MIN_PKT"
#define device_bar_BDK_RGXX_GMP_GMI_TXX_MIN_PKT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_TXX_MIN_PKT(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_TXX_MIN_PKT(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_tx#_pause_pkt_interval
 *
 * RGX GMI TX PAUSE-Packet Transmission-Interval Registers
 * This register specifies how often PAUSE packets are sent.
 * Internal:
 * Notes:
 * Choosing proper values of RGX()_GMP_GMI_TX()_PAUSE_PKT_TIME[PTIME] and
 * RGX()_GMP_GMI_TX()_PAUSE_PKT_INTERVAL[INTERVAL] can be challenging to the system
 * designer.  It is suggested that TIME be much greater than INTERVAL and
 * RGX()_GMP_GMI_TX()_PAUSE_ZERO[SEND] be set.  This allows a periodic refresh of the PAUSE
 * count and then when the backpressure condition is lifted, a PAUSE packet
 * with TIME==0 will be sent indicating that Octane is ready for additional
 * data.
 *
 * If the system chooses to not set RGX()_GMP_GMI_TX()_PAUSE_ZERO[SEND], then it is
 * suggested that TIME and INTERVAL are programmed such that they satisify the
 * following rule:
 *
 * _ INTERVAL \<= TIME - (largest_pkt_size + IFG + pause_pkt_size)
 *
 * where largest_pkt_size is that largest packet that the system can send
 * (normally 1518B), IFG is the interframe gap and pause_pkt_size is the size
 * of the PAUSE packet (normally 64B).
 */
union bdk_rgxx_gmp_gmi_txx_pause_pkt_interval
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_txx_pause_pkt_interval_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t interval              : 16; /**< [ 15:  0](R/W) Arbitrate for a 802.3 PAUSE packet every ([INTERVAL] * 512)
                                                                 bit-times. Normally, 0 \< [INTERVAL] \< RGX()_GMP_GMI_TX()_PAUSE_PKT_TIME[PTIME].

                                                                 [INTERVAL] = 0 only sends a single PAUSE packet for each backpressure event.
                                                                 RGX()_GMP_GMI_TX()_PAUSE_ZERO[SEND] must be 1 when [INTERVAL] = 0.
                                                                 [INTERVAL] should be 0x0 if RGX()_GMP_GMI_TX()_CTL[TX_FC_TYPE] is clear (G.999.1). */
#else /* Word 0 - Little Endian */
        uint64_t interval              : 16; /**< [ 15:  0](R/W) Arbitrate for a 802.3 PAUSE packet every ([INTERVAL] * 512)
                                                                 bit-times. Normally, 0 \< [INTERVAL] \< RGX()_GMP_GMI_TX()_PAUSE_PKT_TIME[PTIME].

                                                                 [INTERVAL] = 0 only sends a single PAUSE packet for each backpressure event.
                                                                 RGX()_GMP_GMI_TX()_PAUSE_ZERO[SEND] must be 1 when [INTERVAL] = 0.
                                                                 [INTERVAL] should be 0x0 if RGX()_GMP_GMI_TX()_CTL[TX_FC_TYPE] is clear (G.999.1). */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_txx_pause_pkt_interval_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_txx_pause_pkt_interval bdk_rgxx_gmp_gmi_txx_pause_pkt_interval_t;

static inline uint64_t BDK_RGXX_GMP_GMI_TXX_PAUSE_PKT_INTERVAL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_TXX_PAUSE_PKT_INTERVAL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038248ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_TXX_PAUSE_PKT_INTERVAL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_TXX_PAUSE_PKT_INTERVAL(a,b) bdk_rgxx_gmp_gmi_txx_pause_pkt_interval_t
#define bustype_BDK_RGXX_GMP_GMI_TXX_PAUSE_PKT_INTERVAL(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_TXX_PAUSE_PKT_INTERVAL(a,b) "RGXX_GMP_GMI_TXX_PAUSE_PKT_INTERVAL"
#define device_bar_BDK_RGXX_GMP_GMI_TXX_PAUSE_PKT_INTERVAL(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_TXX_PAUSE_PKT_INTERVAL(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_TXX_PAUSE_PKT_INTERVAL(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_tx#_pause_pkt_time
 *
 * RGX GMI TX PAUSE Packet PAUSE-Time Registers
 */
union bdk_rgxx_gmp_gmi_txx_pause_pkt_time
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_txx_pause_pkt_time_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t ptime                 : 16; /**< [ 15:  0](R/W) Provides the pause_time field placed in outbound 802.3 PAUSE packets
                                                                 in 512 bit-times. Normally, [PTIME] \>
                                                                 RGX()_GMP_GMI_TX()_PAUSE_PKT_INTERVAL[INTERVAL]. For programming information see
                                                                 RGX()_GMP_GMI_TX()_PAUSE_PKT_INTERVAL.
                                                                 [PTIME] should be 0x0 if RGX()_GMP_GMI_TX()_CTL[TX_FC_TYPE] is clear (G.999.1). */
#else /* Word 0 - Little Endian */
        uint64_t ptime                 : 16; /**< [ 15:  0](R/W) Provides the pause_time field placed in outbound 802.3 PAUSE packets
                                                                 in 512 bit-times. Normally, [PTIME] \>
                                                                 RGX()_GMP_GMI_TX()_PAUSE_PKT_INTERVAL[INTERVAL]. For programming information see
                                                                 RGX()_GMP_GMI_TX()_PAUSE_PKT_INTERVAL.
                                                                 [PTIME] should be 0x0 if RGX()_GMP_GMI_TX()_CTL[TX_FC_TYPE] is clear (G.999.1). */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_txx_pause_pkt_time_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_txx_pause_pkt_time bdk_rgxx_gmp_gmi_txx_pause_pkt_time_t;

static inline uint64_t BDK_RGXX_GMP_GMI_TXX_PAUSE_PKT_TIME(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_TXX_PAUSE_PKT_TIME(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038238ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_TXX_PAUSE_PKT_TIME", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_TXX_PAUSE_PKT_TIME(a,b) bdk_rgxx_gmp_gmi_txx_pause_pkt_time_t
#define bustype_BDK_RGXX_GMP_GMI_TXX_PAUSE_PKT_TIME(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_TXX_PAUSE_PKT_TIME(a,b) "RGXX_GMP_GMI_TXX_PAUSE_PKT_TIME"
#define device_bar_BDK_RGXX_GMP_GMI_TXX_PAUSE_PKT_TIME(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_TXX_PAUSE_PKT_TIME(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_TXX_PAUSE_PKT_TIME(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_tx#_pause_togo
 *
 * RGX GMI TX Time-to-Backpressure Registers
 */
union bdk_rgxx_gmp_gmi_txx_pause_togo
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_txx_pause_togo_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t ptime                 : 16; /**< [ 15:  0](RO/H) Amount of time remaining to backpressure, from the standard 802.3 PAUSE timer. */
#else /* Word 0 - Little Endian */
        uint64_t ptime                 : 16; /**< [ 15:  0](RO/H) Amount of time remaining to backpressure, from the standard 802.3 PAUSE timer. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_txx_pause_togo_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_txx_pause_togo bdk_rgxx_gmp_gmi_txx_pause_togo_t;

static inline uint64_t BDK_RGXX_GMP_GMI_TXX_PAUSE_TOGO(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_TXX_PAUSE_TOGO(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038258ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_TXX_PAUSE_TOGO", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_TXX_PAUSE_TOGO(a,b) bdk_rgxx_gmp_gmi_txx_pause_togo_t
#define bustype_BDK_RGXX_GMP_GMI_TXX_PAUSE_TOGO(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_TXX_PAUSE_TOGO(a,b) "RGXX_GMP_GMI_TXX_PAUSE_TOGO"
#define device_bar_BDK_RGXX_GMP_GMI_TXX_PAUSE_TOGO(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_TXX_PAUSE_TOGO(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_TXX_PAUSE_TOGO(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_tx#_pause_zero
 *
 * RGX GMI TX PAUSE-Zero-Enable Registers
 */
union bdk_rgxx_gmp_gmi_txx_pause_zero
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_txx_pause_zero_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t send                  : 1;  /**< [  0:  0](R/W) Send PAUSE-zero enable. When this bit is set, and the backpressure condition is clear, it
                                                                 allows sending a PAUSE packet with pause_time of 0 to enable the channel.
                                                                 [SEND] should be set if RGX()_GMP_GMI_TX()_CTL[TX_FC_TYPE] is clear (G.999.1). */
#else /* Word 0 - Little Endian */
        uint64_t send                  : 1;  /**< [  0:  0](R/W) Send PAUSE-zero enable. When this bit is set, and the backpressure condition is clear, it
                                                                 allows sending a PAUSE packet with pause_time of 0 to enable the channel.
                                                                 [SEND] should be set if RGX()_GMP_GMI_TX()_CTL[TX_FC_TYPE] is clear (G.999.1). */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_txx_pause_zero_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_txx_pause_zero bdk_rgxx_gmp_gmi_txx_pause_zero_t;

static inline uint64_t BDK_RGXX_GMP_GMI_TXX_PAUSE_ZERO(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_TXX_PAUSE_ZERO(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038260ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_TXX_PAUSE_ZERO", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_TXX_PAUSE_ZERO(a,b) bdk_rgxx_gmp_gmi_txx_pause_zero_t
#define bustype_BDK_RGXX_GMP_GMI_TXX_PAUSE_ZERO(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_TXX_PAUSE_ZERO(a,b) "RGXX_GMP_GMI_TXX_PAUSE_ZERO"
#define device_bar_BDK_RGXX_GMP_GMI_TXX_PAUSE_ZERO(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_TXX_PAUSE_ZERO(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_TXX_PAUSE_ZERO(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_tx#_sgmii_ctl
 *
 * RGX SGMII Control Registers
 */
union bdk_rgxx_gmp_gmi_txx_sgmii_ctl
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_txx_sgmii_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t align                 : 1;  /**< [  0:  0](R/W) Align the transmission to even cycles: (SGMII/1000BASE-X half-duplex only)
                                                                 Recommended value is: ALIGN = !RGX()_GMP_GMI_TX()_APPEND[PREAMBLE].
                                                                 (See Transmit Conversion to Code groups, Transmit Conversion to Code Groups for a complete
                                                                 discussion.)

                                                                 _ 0 = Data can be sent on any cycle. In this mode, the interface functions at maximum
                                                                 bandwidth. It is possible for the TX PCS machine to drop the first byte of the TX frame.
                                                                 When RGX()_GMP_GMI_TX()_APPEND[PREAMBLE] is set, the first byte is a preamble
                                                                 byte, which can be dropped to compensate for an extended IPG.

                                                                 _ 1 = Data is only sent on even cycles. In this mode, there can be bandwidth implications
                                                                 when sending odd-byte packets as the IPG can extend an extra cycle. There will be no loss
                                                                 of data. */
#else /* Word 0 - Little Endian */
        uint64_t align                 : 1;  /**< [  0:  0](R/W) Align the transmission to even cycles: (SGMII/1000BASE-X half-duplex only)
                                                                 Recommended value is: ALIGN = !RGX()_GMP_GMI_TX()_APPEND[PREAMBLE].
                                                                 (See Transmit Conversion to Code groups, Transmit Conversion to Code Groups for a complete
                                                                 discussion.)

                                                                 _ 0 = Data can be sent on any cycle. In this mode, the interface functions at maximum
                                                                 bandwidth. It is possible for the TX PCS machine to drop the first byte of the TX frame.
                                                                 When RGX()_GMP_GMI_TX()_APPEND[PREAMBLE] is set, the first byte is a preamble
                                                                 byte, which can be dropped to compensate for an extended IPG.

                                                                 _ 1 = Data is only sent on even cycles. In this mode, there can be bandwidth implications
                                                                 when sending odd-byte packets as the IPG can extend an extra cycle. There will be no loss
                                                                 of data. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_txx_sgmii_ctl_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_txx_sgmii_ctl bdk_rgxx_gmp_gmi_txx_sgmii_ctl_t;

static inline uint64_t BDK_RGXX_GMP_GMI_TXX_SGMII_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_TXX_SGMII_CTL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038300ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_TXX_SGMII_CTL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_TXX_SGMII_CTL(a,b) bdk_rgxx_gmp_gmi_txx_sgmii_ctl_t
#define bustype_BDK_RGXX_GMP_GMI_TXX_SGMII_CTL(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_TXX_SGMII_CTL(a,b) "RGXX_GMP_GMI_TXX_SGMII_CTL"
#define device_bar_BDK_RGXX_GMP_GMI_TXX_SGMII_CTL(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_TXX_SGMII_CTL(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_TXX_SGMII_CTL(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_tx#_slot
 *
 * RGX GMI TX Slottime Counter Registers
 */
union bdk_rgxx_gmp_gmi_txx_slot
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_txx_slot_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t slot                  : 10; /**< [  9:  0](R/W) Slottime (refer to Std 802.3 to set correctly):
                                                                 10/100 Mbs: Set SLOT to 0x40.
                                                                 1000 Mbs: Set SLOT to 0x200.

                                                                 SGMII/QSGMII/1000Base-X only. */
#else /* Word 0 - Little Endian */
        uint64_t slot                  : 10; /**< [  9:  0](R/W) Slottime (refer to Std 802.3 to set correctly):
                                                                 10/100 Mbs: Set SLOT to 0x40.
                                                                 1000 Mbs: Set SLOT to 0x200.

                                                                 SGMII/QSGMII/1000Base-X only. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_txx_slot_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_txx_slot bdk_rgxx_gmp_gmi_txx_slot_t;

static inline uint64_t BDK_RGXX_GMP_GMI_TXX_SLOT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_TXX_SLOT(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038220ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_TXX_SLOT", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_TXX_SLOT(a,b) bdk_rgxx_gmp_gmi_txx_slot_t
#define bustype_BDK_RGXX_GMP_GMI_TXX_SLOT(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_TXX_SLOT(a,b) "RGXX_GMP_GMI_TXX_SLOT"
#define device_bar_BDK_RGXX_GMP_GMI_TXX_SLOT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_TXX_SLOT(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_TXX_SLOT(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_tx#_soft_pause
 *
 * RGX GMI TX Software PAUSE Registers
 */
union bdk_rgxx_gmp_gmi_txx_soft_pause
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_txx_soft_pause_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t ptime                 : 16; /**< [ 15:  0](R/W) Back off the TX bus for ([PTIME] * 512) bit-times. */
#else /* Word 0 - Little Endian */
        uint64_t ptime                 : 16; /**< [ 15:  0](R/W) Back off the TX bus for ([PTIME] * 512) bit-times. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_txx_soft_pause_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_txx_soft_pause bdk_rgxx_gmp_gmi_txx_soft_pause_t;

static inline uint64_t BDK_RGXX_GMP_GMI_TXX_SOFT_PAUSE(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_TXX_SOFT_PAUSE(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038250ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_TXX_SOFT_PAUSE", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_TXX_SOFT_PAUSE(a,b) bdk_rgxx_gmp_gmi_txx_soft_pause_t
#define bustype_BDK_RGXX_GMP_GMI_TXX_SOFT_PAUSE(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_TXX_SOFT_PAUSE(a,b) "RGXX_GMP_GMI_TXX_SOFT_PAUSE"
#define device_bar_BDK_RGXX_GMP_GMI_TXX_SOFT_PAUSE(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_TXX_SOFT_PAUSE(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_TXX_SOFT_PAUSE(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_tx#_thresh
 *
 * RGX GMI TX Threshold Registers
 */
union bdk_rgxx_gmp_gmi_txx_thresh
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_txx_thresh_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t cnt                   : 11; /**< [ 10:  0](R/W) Number of 128-bit words to accumulate in the TX FIFO before sending on the packet
                                                                 interface. This field should be large enough to prevent underflow on the packet interface
                                                                 and must never be set to 0x0.

                                                                 In all modes, this register cannot exceed the TX FIFO depth configured by
                                                                 RGX()_CMR_TX_LMACS[LMACS]. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 11; /**< [ 10:  0](R/W) Number of 128-bit words to accumulate in the TX FIFO before sending on the packet
                                                                 interface. This field should be large enough to prevent underflow on the packet interface
                                                                 and must never be set to 0x0.

                                                                 In all modes, this register cannot exceed the TX FIFO depth configured by
                                                                 RGX()_CMR_TX_LMACS[LMACS]. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_txx_thresh_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_txx_thresh bdk_rgxx_gmp_gmi_txx_thresh_t;

static inline uint64_t BDK_RGXX_GMP_GMI_TXX_THRESH(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_TXX_THRESH(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8038210ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_TXX_THRESH", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_TXX_THRESH(a,b) bdk_rgxx_gmp_gmi_txx_thresh_t
#define bustype_BDK_RGXX_GMP_GMI_TXX_THRESH(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_TXX_THRESH(a,b) "RGXX_GMP_GMI_TXX_THRESH"
#define device_bar_BDK_RGXX_GMP_GMI_TXX_THRESH(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_TXX_THRESH(a,b) (a)
#define arguments_BDK_RGXX_GMP_GMI_TXX_THRESH(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_tx_col_attempt
 *
 * RGX TX Collision Attempts Before Dropping Frame Registers
 */
union bdk_rgxx_gmp_gmi_tx_col_attempt
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_tx_col_attempt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t limit                 : 5;  /**< [  4:  0](R/W) Number of collision attempts allowed. (SGMII/1000BASE-X half-duplex only.) */
#else /* Word 0 - Little Endian */
        uint64_t limit                 : 5;  /**< [  4:  0](R/W) Number of collision attempts allowed. (SGMII/1000BASE-X half-duplex only.) */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_tx_col_attempt_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_tx_col_attempt bdk_rgxx_gmp_gmi_tx_col_attempt_t;

static inline uint64_t BDK_RGXX_GMP_GMI_TX_COL_ATTEMPT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_TX_COL_ATTEMPT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8039010ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_TX_COL_ATTEMPT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_TX_COL_ATTEMPT(a) bdk_rgxx_gmp_gmi_tx_col_attempt_t
#define bustype_BDK_RGXX_GMP_GMI_TX_COL_ATTEMPT(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_TX_COL_ATTEMPT(a) "RGXX_GMP_GMI_TX_COL_ATTEMPT"
#define device_bar_BDK_RGXX_GMP_GMI_TX_COL_ATTEMPT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_TX_COL_ATTEMPT(a) (a)
#define arguments_BDK_RGXX_GMP_GMI_TX_COL_ATTEMPT(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_tx_ifg
 *
 * RGX GMI TX Interframe-Gap Cycles Registers
 * Consider the following when programming IFG1 and IFG2:
 * * For 10/100/1000 Mb/s half-duplex systems that require IEEE 802.3 compatibility, IFG1 must be
 * in the range of 1-8, IFG2 must be in the range of 4-12, and the IFG1 + IFG2 sum must be 12.
 * * For 10/100/1000 Mb/s full-duplex systems that require IEEE 802.3 compatibility, IFG1 must be
 * in the range of 1-11, IFG2 must be in the range of 1-11, and the IFG1 + IFG2 sum must be 12.
 * For all other systems, IFG1 and IFG2 can be any value in the range of 1-15, allowing for a
 * total possible IFG sum of 2-30.
 */
union bdk_rgxx_gmp_gmi_tx_ifg
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_tx_ifg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t ifg2                  : 4;  /**< [  7:  4](R/W) Remainder of interFrameGap timing, equal to interFrameGap - IFG1 (in IFG2 * 8 bits). If
                                                                 CRS is detected during IFG2, the interFrameSpacing timer is not reset and a frame is
                                                                 transmitted once the timer expires. */
        uint64_t ifg1                  : 4;  /**< [  3:  0](R/W) First portion of interFrameGap timing, in the range of 0 to 2/3 (in IFG2 * 8 bits). If CRS
                                                                 is detected during IFG1, the interFrameSpacing timer is reset and a frame is not
                                                                 transmitted. */
#else /* Word 0 - Little Endian */
        uint64_t ifg1                  : 4;  /**< [  3:  0](R/W) First portion of interFrameGap timing, in the range of 0 to 2/3 (in IFG2 * 8 bits). If CRS
                                                                 is detected during IFG1, the interFrameSpacing timer is reset and a frame is not
                                                                 transmitted. */
        uint64_t ifg2                  : 4;  /**< [  7:  4](R/W) Remainder of interFrameGap timing, equal to interFrameGap - IFG1 (in IFG2 * 8 bits). If
                                                                 CRS is detected during IFG2, the interFrameSpacing timer is not reset and a frame is
                                                                 transmitted once the timer expires. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_tx_ifg_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_tx_ifg bdk_rgxx_gmp_gmi_tx_ifg_t;

static inline uint64_t BDK_RGXX_GMP_GMI_TX_IFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_TX_IFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8039000ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_TX_IFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_TX_IFG(a) bdk_rgxx_gmp_gmi_tx_ifg_t
#define bustype_BDK_RGXX_GMP_GMI_TX_IFG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_TX_IFG(a) "RGXX_GMP_GMI_TX_IFG"
#define device_bar_BDK_RGXX_GMP_GMI_TX_IFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_TX_IFG(a) (a)
#define arguments_BDK_RGXX_GMP_GMI_TX_IFG(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_tx_jam
 *
 * RGX GMI TX JAM Pattern Registers
 * This register provides the pattern used in JAM bytes.
 */
union bdk_rgxx_gmp_gmi_tx_jam
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_tx_jam_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t jam                   : 8;  /**< [  7:  0](R/W) JAM pattern. (SGMII/1000BASE-X half-duplex only.) */
#else /* Word 0 - Little Endian */
        uint64_t jam                   : 8;  /**< [  7:  0](R/W) JAM pattern. (SGMII/1000BASE-X half-duplex only.) */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_tx_jam_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_tx_jam bdk_rgxx_gmp_gmi_tx_jam_t;

static inline uint64_t BDK_RGXX_GMP_GMI_TX_JAM(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_TX_JAM(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8039008ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_TX_JAM", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_TX_JAM(a) bdk_rgxx_gmp_gmi_tx_jam_t
#define bustype_BDK_RGXX_GMP_GMI_TX_JAM(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_TX_JAM(a) "RGXX_GMP_GMI_TX_JAM"
#define device_bar_BDK_RGXX_GMP_GMI_TX_JAM(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_TX_JAM(a) (a)
#define arguments_BDK_RGXX_GMP_GMI_TX_JAM(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_tx_lfsr
 *
 * RGX GMI TX LFSR Registers
 * This register shows the contents of the linear feedback shift register (LFSR), which is used
 * to implement truncated binary exponential backoff.
 */
union bdk_rgxx_gmp_gmi_tx_lfsr
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_tx_lfsr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t lfsr                  : 16; /**< [ 15:  0](R/W/H) Contains the current state of the LFSR, which is used to feed random numbers to compute
                                                                 truncated binary exponential backoff. (SGMII/1000Base-X half-duplex only.) */
#else /* Word 0 - Little Endian */
        uint64_t lfsr                  : 16; /**< [ 15:  0](R/W/H) Contains the current state of the LFSR, which is used to feed random numbers to compute
                                                                 truncated binary exponential backoff. (SGMII/1000Base-X half-duplex only.) */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_tx_lfsr_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_tx_lfsr bdk_rgxx_gmp_gmi_tx_lfsr_t;

static inline uint64_t BDK_RGXX_GMP_GMI_TX_LFSR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_TX_LFSR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8039028ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_TX_LFSR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_TX_LFSR(a) bdk_rgxx_gmp_gmi_tx_lfsr_t
#define bustype_BDK_RGXX_GMP_GMI_TX_LFSR(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_TX_LFSR(a) "RGXX_GMP_GMI_TX_LFSR"
#define device_bar_BDK_RGXX_GMP_GMI_TX_LFSR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_TX_LFSR(a) (a)
#define arguments_BDK_RGXX_GMP_GMI_TX_LFSR(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_tx_pause_pkt_dmac
 *
 * RGX TX PAUSE-Packet DMAC-Field Registers
 */
union bdk_rgxx_gmp_gmi_tx_pause_pkt_dmac
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_tx_pause_pkt_dmac_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t dmac                  : 48; /**< [ 47:  0](R/W) The DMAC field, which is placed in outbound PAUSE packets. */
#else /* Word 0 - Little Endian */
        uint64_t dmac                  : 48; /**< [ 47:  0](R/W) The DMAC field, which is placed in outbound PAUSE packets. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_tx_pause_pkt_dmac_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_tx_pause_pkt_dmac bdk_rgxx_gmp_gmi_tx_pause_pkt_dmac_t;

static inline uint64_t BDK_RGXX_GMP_GMI_TX_PAUSE_PKT_DMAC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_TX_PAUSE_PKT_DMAC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8039018ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_TX_PAUSE_PKT_DMAC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_TX_PAUSE_PKT_DMAC(a) bdk_rgxx_gmp_gmi_tx_pause_pkt_dmac_t
#define bustype_BDK_RGXX_GMP_GMI_TX_PAUSE_PKT_DMAC(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_TX_PAUSE_PKT_DMAC(a) "RGXX_GMP_GMI_TX_PAUSE_PKT_DMAC"
#define device_bar_BDK_RGXX_GMP_GMI_TX_PAUSE_PKT_DMAC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_TX_PAUSE_PKT_DMAC(a) (a)
#define arguments_BDK_RGXX_GMP_GMI_TX_PAUSE_PKT_DMAC(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_gmp_gmi_tx_pause_pkt_type
 *
 * RGX GMI TX PAUSE-Packet-PTYPE Field Registers
 * This register provides the PTYPE field that is placed in outbound PAUSE packets.
 */
union bdk_rgxx_gmp_gmi_tx_pause_pkt_type
{
    uint64_t u;
    struct bdk_rgxx_gmp_gmi_tx_pause_pkt_type_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t ptype                 : 16; /**< [ 15:  0](R/W) The PTYPE field placed in outbound PAUSE packets. */
#else /* Word 0 - Little Endian */
        uint64_t ptype                 : 16; /**< [ 15:  0](R/W) The PTYPE field placed in outbound PAUSE packets. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_gmi_tx_pause_pkt_type_s cn; */
};
typedef union bdk_rgxx_gmp_gmi_tx_pause_pkt_type bdk_rgxx_gmp_gmi_tx_pause_pkt_type_t;

static inline uint64_t BDK_RGXX_GMP_GMI_TX_PAUSE_PKT_TYPE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_GMI_TX_PAUSE_PKT_TYPE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0e8039020ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_GMI_TX_PAUSE_PKT_TYPE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_GMI_TX_PAUSE_PKT_TYPE(a) bdk_rgxx_gmp_gmi_tx_pause_pkt_type_t
#define bustype_BDK_RGXX_GMP_GMI_TX_PAUSE_PKT_TYPE(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_GMI_TX_PAUSE_PKT_TYPE(a) "RGXX_GMP_GMI_TX_PAUSE_PKT_TYPE"
#define device_bar_BDK_RGXX_GMP_GMI_TX_PAUSE_PKT_TYPE(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_GMI_TX_PAUSE_PKT_TYPE(a) (a)
#define arguments_BDK_RGXX_GMP_GMI_TX_PAUSE_PKT_TYPE(a) (a),-1,-1,-1

/**
 * Register (RSL) rgx#_gmp_pcs_an#_adv
 *
 * INTERNAL: RGX GMP PCS Autonegotiation Advertisement Registers
 */
union bdk_rgxx_gmp_pcs_anx_adv
{
    uint64_t u;
    struct bdk_rgxx_gmp_pcs_anx_adv_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t np                    : 1;  /**< [ 15: 15](RO/H) Next page capable. This feature is not supported; this field is always 0. */
        uint64_t reserved_14           : 1;
        uint64_t rem_flt               : 2;  /**< [ 13: 12](R/W/H) Remote fault.
                                                                 0x0 = Link OK, XMIT = DATA.
                                                                 0x1 = Link failure (loss of sync, XMIT !=DATA).
                                                                 0x2 = Local device offline.
                                                                 0x3 = Autonegotiation error; failure to complete autonegotiation. AN error is set if
                                                                 resolution function precludes operation with link partner. */
        uint64_t reserved_9_11         : 3;
        uint64_t pause                 : 2;  /**< [  8:  7](R/W) PAUSE frame flow capability across link, exchanged during autonegotiation as follows:
                                                                 0x0 = No PAUSE.
                                                                 0x1 = Symmetric PAUSE.
                                                                 0x2 = Asymmetric PAUSE.
                                                                 0x3 = Both symmetric and asymmetric PAUSE to local device. */
        uint64_t hfd                   : 1;  /**< [  6:  6](R/W) Half-duplex. When set, local device is half-duplex capable. */
        uint64_t fd                    : 1;  /**< [  5:  5](R/W) Full-duplex. When set, local device is full-duplex capable. */
        uint64_t reserved_0_4          : 5;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_4          : 5;
        uint64_t fd                    : 1;  /**< [  5:  5](R/W) Full-duplex. When set, local device is full-duplex capable. */
        uint64_t hfd                   : 1;  /**< [  6:  6](R/W) Half-duplex. When set, local device is half-duplex capable. */
        uint64_t pause                 : 2;  /**< [  8:  7](R/W) PAUSE frame flow capability across link, exchanged during autonegotiation as follows:
                                                                 0x0 = No PAUSE.
                                                                 0x1 = Symmetric PAUSE.
                                                                 0x2 = Asymmetric PAUSE.
                                                                 0x3 = Both symmetric and asymmetric PAUSE to local device. */
        uint64_t reserved_9_11         : 3;
        uint64_t rem_flt               : 2;  /**< [ 13: 12](R/W/H) Remote fault.
                                                                 0x0 = Link OK, XMIT = DATA.
                                                                 0x1 = Link failure (loss of sync, XMIT !=DATA).
                                                                 0x2 = Local device offline.
                                                                 0x3 = Autonegotiation error; failure to complete autonegotiation. AN error is set if
                                                                 resolution function precludes operation with link partner. */
        uint64_t reserved_14           : 1;
        uint64_t np                    : 1;  /**< [ 15: 15](RO/H) Next page capable. This feature is not supported; this field is always 0. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_pcs_anx_adv_s cn; */
};
typedef union bdk_rgxx_gmp_pcs_anx_adv bdk_rgxx_gmp_pcs_anx_adv_t;

static inline uint64_t BDK_RGXX_GMP_PCS_ANX_ADV(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_PCS_ANX_ADV(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8030010ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_PCS_ANX_ADV", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_PCS_ANX_ADV(a,b) bdk_rgxx_gmp_pcs_anx_adv_t
#define bustype_BDK_RGXX_GMP_PCS_ANX_ADV(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_PCS_ANX_ADV(a,b) "RGXX_GMP_PCS_ANX_ADV"
#define device_bar_BDK_RGXX_GMP_PCS_ANX_ADV(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_PCS_ANX_ADV(a,b) (a)
#define arguments_BDK_RGXX_GMP_PCS_ANX_ADV(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_pcs_an#_ext_st
 *
 * INTERNAL: RGX GMO PCS Autonegotiation Extended Status Registers
 */
union bdk_rgxx_gmp_pcs_anx_ext_st
{
    uint64_t u;
    struct bdk_rgxx_gmp_pcs_anx_ext_st_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t thou_xfd              : 1;  /**< [ 15: 15](RO/H) When set, PHY is 1000 BASE-X full duplex capable. */
        uint64_t thou_xhd              : 1;  /**< [ 14: 14](RO/H) When set, PHY is 1000 BASE-X half duplex capable. */
        uint64_t thou_tfd              : 1;  /**< [ 13: 13](RO/H) When set, PHY is 1000 BASE-T full duplex capable. */
        uint64_t thou_thd              : 1;  /**< [ 12: 12](RO/H) When set, PHY is 1000 BASE-T half duplex capable. */
        uint64_t reserved_0_11         : 12;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_11         : 12;
        uint64_t thou_thd              : 1;  /**< [ 12: 12](RO/H) When set, PHY is 1000 BASE-T half duplex capable. */
        uint64_t thou_tfd              : 1;  /**< [ 13: 13](RO/H) When set, PHY is 1000 BASE-T full duplex capable. */
        uint64_t thou_xhd              : 1;  /**< [ 14: 14](RO/H) When set, PHY is 1000 BASE-X half duplex capable. */
        uint64_t thou_xfd              : 1;  /**< [ 15: 15](RO/H) When set, PHY is 1000 BASE-X full duplex capable. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_pcs_anx_ext_st_s cn; */
};
typedef union bdk_rgxx_gmp_pcs_anx_ext_st bdk_rgxx_gmp_pcs_anx_ext_st_t;

static inline uint64_t BDK_RGXX_GMP_PCS_ANX_EXT_ST(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_PCS_ANX_EXT_ST(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8030028ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_PCS_ANX_EXT_ST", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_PCS_ANX_EXT_ST(a,b) bdk_rgxx_gmp_pcs_anx_ext_st_t
#define bustype_BDK_RGXX_GMP_PCS_ANX_EXT_ST(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_PCS_ANX_EXT_ST(a,b) "RGXX_GMP_PCS_ANX_EXT_ST"
#define device_bar_BDK_RGXX_GMP_PCS_ANX_EXT_ST(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_PCS_ANX_EXT_ST(a,b) (a)
#define arguments_BDK_RGXX_GMP_PCS_ANX_EXT_ST(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_pcs_an#_lp_abil
 *
 * INTERNAL: RGX GMP PCS Autonegotiation Link Partner Ability Registers
 *
 * This is the autonegotiation Link partner ability register 5 as per IEEE 802.3, Clause 37.
 */
union bdk_rgxx_gmp_pcs_anx_lp_abil
{
    uint64_t u;
    struct bdk_rgxx_gmp_pcs_anx_lp_abil_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t np                    : 1;  /**< [ 15: 15](RO/H) Next page capable:
                                                                 0 = Link partner not next page capable.
                                                                 1 = Link partner next page capable. */
        uint64_t ack                   : 1;  /**< [ 14: 14](RO/H) When set, indicates acknowledgement received. */
        uint64_t rem_flt               : 2;  /**< [ 13: 12](RO/H) Link partner's link status as follows:
                                                                 0x0 = Link OK.
                                                                 0x1 = Offline.
                                                                 0x2 = Link failure.
                                                                 0x3 = Autonegotiation error. */
        uint64_t reserved_9_11         : 3;
        uint64_t pause                 : 2;  /**< [  8:  7](RO/H) Link partner PAUSE setting as follows:
                                                                 0x0 = No PAUSE.
                                                                 0x1 = Symmetric PAUSE.
                                                                 0x2 = Asymmetric PAUSE.
                                                                 0x3 = Both symmetric and asymmetric PAUSE to local device. */
        uint64_t hfd                   : 1;  /**< [  6:  6](RO/H) Half-duplex. When set, link partner is half-duplex capable. */
        uint64_t fd                    : 1;  /**< [  5:  5](RO/H) Full-duplex. When set, link partner is full-duplex capable. */
        uint64_t reserved_0_4          : 5;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_4          : 5;
        uint64_t fd                    : 1;  /**< [  5:  5](RO/H) Full-duplex. When set, link partner is full-duplex capable. */
        uint64_t hfd                   : 1;  /**< [  6:  6](RO/H) Half-duplex. When set, link partner is half-duplex capable. */
        uint64_t pause                 : 2;  /**< [  8:  7](RO/H) Link partner PAUSE setting as follows:
                                                                 0x0 = No PAUSE.
                                                                 0x1 = Symmetric PAUSE.
                                                                 0x2 = Asymmetric PAUSE.
                                                                 0x3 = Both symmetric and asymmetric PAUSE to local device. */
        uint64_t reserved_9_11         : 3;
        uint64_t rem_flt               : 2;  /**< [ 13: 12](RO/H) Link partner's link status as follows:
                                                                 0x0 = Link OK.
                                                                 0x1 = Offline.
                                                                 0x2 = Link failure.
                                                                 0x3 = Autonegotiation error. */
        uint64_t ack                   : 1;  /**< [ 14: 14](RO/H) When set, indicates acknowledgement received. */
        uint64_t np                    : 1;  /**< [ 15: 15](RO/H) Next page capable:
                                                                 0 = Link partner not next page capable.
                                                                 1 = Link partner next page capable. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_pcs_anx_lp_abil_s cn; */
};
typedef union bdk_rgxx_gmp_pcs_anx_lp_abil bdk_rgxx_gmp_pcs_anx_lp_abil_t;

static inline uint64_t BDK_RGXX_GMP_PCS_ANX_LP_ABIL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_PCS_ANX_LP_ABIL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8030018ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_PCS_ANX_LP_ABIL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_PCS_ANX_LP_ABIL(a,b) bdk_rgxx_gmp_pcs_anx_lp_abil_t
#define bustype_BDK_RGXX_GMP_PCS_ANX_LP_ABIL(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_PCS_ANX_LP_ABIL(a,b) "RGXX_GMP_PCS_ANX_LP_ABIL"
#define device_bar_BDK_RGXX_GMP_PCS_ANX_LP_ABIL(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_PCS_ANX_LP_ABIL(a,b) (a)
#define arguments_BDK_RGXX_GMP_PCS_ANX_LP_ABIL(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_pcs_an#_results
 *
 * INTERNAL: RGX GMP PCS Autonegotiation Results Registers
 *
 * This register is not valid when RGX()_GMP_PCS_MISC()_CTL[AN_OVRD] is set to 1. If
 * RGX()_GMP_PCS_MISC()_CTL[AN_OVRD] is set to 0 and
 * RGX()_GMP_PCS_AN()_RESULTS[AN_CPT] is set to 1, this register is valid.
 */
union bdk_rgxx_gmp_pcs_anx_results
{
    uint64_t u;
    struct bdk_rgxx_gmp_pcs_anx_results_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t pause                 : 2;  /**< [  6:  5](RO/H) PAUSE selection ('don't care' for SGMII/QSGMII) as follows:
                                                                 0x0 = Disable PAUSE, TX and RX.
                                                                 0x1 = Enable PAUSE frames, RX only.
                                                                 0x2 = Enable PAUSE frames, TX only.
                                                                 0x3 = Enable PAUSE frames, TX and RX. */
        uint64_t spd                   : 2;  /**< [  4:  3](RO/H) Link speed selection as follows:
                                                                 0x0 = 10 Mb/s.
                                                                 0x1 = 100 Mb/s.
                                                                 0x2 = 1000 Mb/s.
                                                                 0x3 = Reserved. */
        uint64_t an_cpt                : 1;  /**< [  2:  2](RO/H) Autonegotiation completed.
                                                                 1 = Autonegotiation completed.
                                                                 0 = Autonegotiation not completed or failed. */
        uint64_t dup                   : 1;  /**< [  1:  1](RO/H) Duplex mode. 1 = full duplex, 0 = half duplex. */
        uint64_t link_ok               : 1;  /**< [  0:  0](RO/H) Link status: 1 = link up (OK), 1 = link down. */
#else /* Word 0 - Little Endian */
        uint64_t link_ok               : 1;  /**< [  0:  0](RO/H) Link status: 1 = link up (OK), 1 = link down. */
        uint64_t dup                   : 1;  /**< [  1:  1](RO/H) Duplex mode. 1 = full duplex, 0 = half duplex. */
        uint64_t an_cpt                : 1;  /**< [  2:  2](RO/H) Autonegotiation completed.
                                                                 1 = Autonegotiation completed.
                                                                 0 = Autonegotiation not completed or failed. */
        uint64_t spd                   : 2;  /**< [  4:  3](RO/H) Link speed selection as follows:
                                                                 0x0 = 10 Mb/s.
                                                                 0x1 = 100 Mb/s.
                                                                 0x2 = 1000 Mb/s.
                                                                 0x3 = Reserved. */
        uint64_t pause                 : 2;  /**< [  6:  5](RO/H) PAUSE selection ('don't care' for SGMII/QSGMII) as follows:
                                                                 0x0 = Disable PAUSE, TX and RX.
                                                                 0x1 = Enable PAUSE frames, RX only.
                                                                 0x2 = Enable PAUSE frames, TX only.
                                                                 0x3 = Enable PAUSE frames, TX and RX. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_pcs_anx_results_s cn; */
};
typedef union bdk_rgxx_gmp_pcs_anx_results bdk_rgxx_gmp_pcs_anx_results_t;

static inline uint64_t BDK_RGXX_GMP_PCS_ANX_RESULTS(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_PCS_ANX_RESULTS(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8030020ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_PCS_ANX_RESULTS", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_PCS_ANX_RESULTS(a,b) bdk_rgxx_gmp_pcs_anx_results_t
#define bustype_BDK_RGXX_GMP_PCS_ANX_RESULTS(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_PCS_ANX_RESULTS(a,b) "RGXX_GMP_PCS_ANX_RESULTS"
#define device_bar_BDK_RGXX_GMP_PCS_ANX_RESULTS(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_PCS_ANX_RESULTS(a,b) (a)
#define arguments_BDK_RGXX_GMP_PCS_ANX_RESULTS(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_pcs_int#
 *
 * INTERNAL: RGX GMP PCS Interrupt Registers
 */
union bdk_rgxx_gmp_pcs_intx
{
    uint64_t u;
    struct bdk_rgxx_gmp_pcs_intx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t dbg_sync              : 1;  /**< [ 12: 12](R/W1C/H) Code group sync failure debug help. RGX()_GMP_PCS_INT()[DBG_SYNC] interrupt fires when
                                                                 code group
                                                                 synchronization state machine makes a transition from SYNC_ACQUIRED_1 state to
                                                                 SYNC_ACQUIRED_2 state. (See IEEE 802.3-2005, figure 37-9). It indicates that a bad code
                                                                 group was received after code group synchronization was achieved. This interrupt should be
                                                                 disabled during normal link operation. Use it as a debug help feature only. */
        uint64_t dup                   : 1;  /**< [ 11: 11](R/W1C/H) Set whenever duplex mode changes on the link. */
        uint64_t sync_bad              : 1;  /**< [ 10: 10](R/W1C/H) Set by hardware whenever RX sync state machine reaches a bad state. Should never be set
                                                                 during normal operation. */
        uint64_t an_bad                : 1;  /**< [  9:  9](R/W1C/H) Set by hardware whenever autonegotiation state machine reaches a bad state. Should never
                                                                 be set during normal operation. */
        uint64_t rxlock                : 1;  /**< [  8:  8](R/W1C/H) Set by hardware whenever code group sync or bit lock failure occurs. Cannot fire in loopback1 mode. */
        uint64_t rxbad                 : 1;  /**< [  7:  7](R/W1C/H) Set by hardware whenever RX state machine reaches a bad state. Should never be set during
                                                                 normal operation. */
        uint64_t rxerr                 : 1;  /**< [  6:  6](R/W1C/H) Set whenever RX receives a code group error in 10-bit to 8-bit decode logic. Cannot fire
                                                                 in loopback1 mode. */
        uint64_t txbad                 : 1;  /**< [  5:  5](R/W1C/H) Set by hardware whenever TX state machine reaches a bad state. Should never be set during
                                                                 normal operation. */
        uint64_t txfifo                : 1;  /**< [  4:  4](R/W1C/H) Set whenever hardware detects a TX FIFO overflow condition. */
        uint64_t txfifu                : 1;  /**< [  3:  3](R/W1C/H) Set whenever hardware detects a TX FIFO underflow condition. */
        uint64_t an_err                : 1;  /**< [  2:  2](R/W1C/H) Autonegotiation error; AN resolution function failed. */
        uint64_t xmit                  : 1;  /**< [  1:  1](R/W1C/H) Set whenever hardware detects a change in the XMIT variable. XMIT variable states are
                                                                 IDLE, CONFIG and DATA. */
        uint64_t lnkspd                : 1;  /**< [  0:  0](R/W1C/H) Set by hardware whenever link speed has changed. */
#else /* Word 0 - Little Endian */
        uint64_t lnkspd                : 1;  /**< [  0:  0](R/W1C/H) Set by hardware whenever link speed has changed. */
        uint64_t xmit                  : 1;  /**< [  1:  1](R/W1C/H) Set whenever hardware detects a change in the XMIT variable. XMIT variable states are
                                                                 IDLE, CONFIG and DATA. */
        uint64_t an_err                : 1;  /**< [  2:  2](R/W1C/H) Autonegotiation error; AN resolution function failed. */
        uint64_t txfifu                : 1;  /**< [  3:  3](R/W1C/H) Set whenever hardware detects a TX FIFO underflow condition. */
        uint64_t txfifo                : 1;  /**< [  4:  4](R/W1C/H) Set whenever hardware detects a TX FIFO overflow condition. */
        uint64_t txbad                 : 1;  /**< [  5:  5](R/W1C/H) Set by hardware whenever TX state machine reaches a bad state. Should never be set during
                                                                 normal operation. */
        uint64_t rxerr                 : 1;  /**< [  6:  6](R/W1C/H) Set whenever RX receives a code group error in 10-bit to 8-bit decode logic. Cannot fire
                                                                 in loopback1 mode. */
        uint64_t rxbad                 : 1;  /**< [  7:  7](R/W1C/H) Set by hardware whenever RX state machine reaches a bad state. Should never be set during
                                                                 normal operation. */
        uint64_t rxlock                : 1;  /**< [  8:  8](R/W1C/H) Set by hardware whenever code group sync or bit lock failure occurs. Cannot fire in loopback1 mode. */
        uint64_t an_bad                : 1;  /**< [  9:  9](R/W1C/H) Set by hardware whenever autonegotiation state machine reaches a bad state. Should never
                                                                 be set during normal operation. */
        uint64_t sync_bad              : 1;  /**< [ 10: 10](R/W1C/H) Set by hardware whenever RX sync state machine reaches a bad state. Should never be set
                                                                 during normal operation. */
        uint64_t dup                   : 1;  /**< [ 11: 11](R/W1C/H) Set whenever duplex mode changes on the link. */
        uint64_t dbg_sync              : 1;  /**< [ 12: 12](R/W1C/H) Code group sync failure debug help. RGX()_GMP_PCS_INT()[DBG_SYNC] interrupt fires when
                                                                 code group
                                                                 synchronization state machine makes a transition from SYNC_ACQUIRED_1 state to
                                                                 SYNC_ACQUIRED_2 state. (See IEEE 802.3-2005, figure 37-9). It indicates that a bad code
                                                                 group was received after code group synchronization was achieved. This interrupt should be
                                                                 disabled during normal link operation. Use it as a debug help feature only. */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_pcs_intx_s cn; */
};
typedef union bdk_rgxx_gmp_pcs_intx bdk_rgxx_gmp_pcs_intx_t;

static inline uint64_t BDK_RGXX_GMP_PCS_INTX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_PCS_INTX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8030080ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_PCS_INTX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_PCS_INTX(a,b) bdk_rgxx_gmp_pcs_intx_t
#define bustype_BDK_RGXX_GMP_PCS_INTX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_PCS_INTX(a,b) "RGXX_GMP_PCS_INTX"
#define device_bar_BDK_RGXX_GMP_PCS_INTX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_PCS_INTX(a,b) (a)
#define arguments_BDK_RGXX_GMP_PCS_INTX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_pcs_int#_ena_w1c
 *
 * INTERNAL: RGX GMP PCS Interrupt Enable Clear Registers
 *
 * This register clears interrupt enable bits.
 */
union bdk_rgxx_gmp_pcs_intx_ena_w1c
{
    uint64_t u;
    struct bdk_rgxx_gmp_pcs_intx_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t dbg_sync              : 1;  /**< [ 12: 12](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[DBG_SYNC]. */
        uint64_t dup                   : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[DUP]. */
        uint64_t sync_bad              : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[SYNC_BAD]. */
        uint64_t an_bad                : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[AN_BAD]. */
        uint64_t rxlock                : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[RXLOCK]. */
        uint64_t rxbad                 : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[RXBAD]. */
        uint64_t rxerr                 : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[RXERR]. */
        uint64_t txbad                 : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[TXBAD]. */
        uint64_t txfifo                : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[TXFIFO]. */
        uint64_t txfifu                : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[TXFIFU]. */
        uint64_t an_err                : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[AN_ERR]. */
        uint64_t xmit                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[XMIT]. */
        uint64_t lnkspd                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[LNKSPD]. */
#else /* Word 0 - Little Endian */
        uint64_t lnkspd                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[LNKSPD]. */
        uint64_t xmit                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[XMIT]. */
        uint64_t an_err                : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[AN_ERR]. */
        uint64_t txfifu                : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[TXFIFU]. */
        uint64_t txfifo                : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[TXFIFO]. */
        uint64_t txbad                 : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[TXBAD]. */
        uint64_t rxerr                 : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[RXERR]. */
        uint64_t rxbad                 : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[RXBAD]. */
        uint64_t rxlock                : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[RXLOCK]. */
        uint64_t an_bad                : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[AN_BAD]. */
        uint64_t sync_bad              : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[SYNC_BAD]. */
        uint64_t dup                   : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[DUP]. */
        uint64_t dbg_sync              : 1;  /**< [ 12: 12](R/W1C/H) Reads or clears enable for RGX(0)_GMP_PCS_INT(0)[DBG_SYNC]. */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_pcs_intx_ena_w1c_s cn; */
};
typedef union bdk_rgxx_gmp_pcs_intx_ena_w1c bdk_rgxx_gmp_pcs_intx_ena_w1c_t;

static inline uint64_t BDK_RGXX_GMP_PCS_INTX_ENA_W1C(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_PCS_INTX_ENA_W1C(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8030090ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_PCS_INTX_ENA_W1C", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_PCS_INTX_ENA_W1C(a,b) bdk_rgxx_gmp_pcs_intx_ena_w1c_t
#define bustype_BDK_RGXX_GMP_PCS_INTX_ENA_W1C(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_PCS_INTX_ENA_W1C(a,b) "RGXX_GMP_PCS_INTX_ENA_W1C"
#define device_bar_BDK_RGXX_GMP_PCS_INTX_ENA_W1C(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_PCS_INTX_ENA_W1C(a,b) (a)
#define arguments_BDK_RGXX_GMP_PCS_INTX_ENA_W1C(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_pcs_int#_ena_w1s
 *
 * INTERNAL: RGX GMP PCS Interrupt Enable Set Registers
 *
 * This register sets interrupt enable bits.
 */
union bdk_rgxx_gmp_pcs_intx_ena_w1s
{
    uint64_t u;
    struct bdk_rgxx_gmp_pcs_intx_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t dbg_sync              : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[DBG_SYNC]. */
        uint64_t dup                   : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[DUP]. */
        uint64_t sync_bad              : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[SYNC_BAD]. */
        uint64_t an_bad                : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[AN_BAD]. */
        uint64_t rxlock                : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[RXLOCK]. */
        uint64_t rxbad                 : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[RXBAD]. */
        uint64_t rxerr                 : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[RXERR]. */
        uint64_t txbad                 : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[TXBAD]. */
        uint64_t txfifo                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[TXFIFO]. */
        uint64_t txfifu                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[TXFIFU]. */
        uint64_t an_err                : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[AN_ERR]. */
        uint64_t xmit                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[XMIT]. */
        uint64_t lnkspd                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[LNKSPD]. */
#else /* Word 0 - Little Endian */
        uint64_t lnkspd                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[LNKSPD]. */
        uint64_t xmit                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[XMIT]. */
        uint64_t an_err                : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[AN_ERR]. */
        uint64_t txfifu                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[TXFIFU]. */
        uint64_t txfifo                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[TXFIFO]. */
        uint64_t txbad                 : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[TXBAD]. */
        uint64_t rxerr                 : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[RXERR]. */
        uint64_t rxbad                 : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[RXBAD]. */
        uint64_t rxlock                : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[RXLOCK]. */
        uint64_t an_bad                : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[AN_BAD]. */
        uint64_t sync_bad              : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[SYNC_BAD]. */
        uint64_t dup                   : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[DUP]. */
        uint64_t dbg_sync              : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets enable for RGX(0)_GMP_PCS_INT(0)[DBG_SYNC]. */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_pcs_intx_ena_w1s_s cn; */
};
typedef union bdk_rgxx_gmp_pcs_intx_ena_w1s bdk_rgxx_gmp_pcs_intx_ena_w1s_t;

static inline uint64_t BDK_RGXX_GMP_PCS_INTX_ENA_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_PCS_INTX_ENA_W1S(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8030098ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_PCS_INTX_ENA_W1S", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_PCS_INTX_ENA_W1S(a,b) bdk_rgxx_gmp_pcs_intx_ena_w1s_t
#define bustype_BDK_RGXX_GMP_PCS_INTX_ENA_W1S(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_PCS_INTX_ENA_W1S(a,b) "RGXX_GMP_PCS_INTX_ENA_W1S"
#define device_bar_BDK_RGXX_GMP_PCS_INTX_ENA_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_PCS_INTX_ENA_W1S(a,b) (a)
#define arguments_BDK_RGXX_GMP_PCS_INTX_ENA_W1S(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_pcs_int#_w1s
 *
 * INTERNAL: RGX GMP PCS Interrupt Set Registers
 *
 * This register sets interrupt bits.
 */
union bdk_rgxx_gmp_pcs_intx_w1s
{
    uint64_t u;
    struct bdk_rgxx_gmp_pcs_intx_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t dbg_sync              : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[DBG_SYNC]. */
        uint64_t dup                   : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[DUP]. */
        uint64_t sync_bad              : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[SYNC_BAD]. */
        uint64_t an_bad                : 1;  /**< [  9:  9](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[AN_BAD]. */
        uint64_t rxlock                : 1;  /**< [  8:  8](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[RXLOCK]. */
        uint64_t rxbad                 : 1;  /**< [  7:  7](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[RXBAD]. */
        uint64_t rxerr                 : 1;  /**< [  6:  6](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[RXERR]. */
        uint64_t txbad                 : 1;  /**< [  5:  5](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[TXBAD]. */
        uint64_t txfifo                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[TXFIFO]. */
        uint64_t txfifu                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[TXFIFU]. */
        uint64_t an_err                : 1;  /**< [  2:  2](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[AN_ERR]. */
        uint64_t xmit                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[XMIT]. */
        uint64_t lnkspd                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[LNKSPD]. */
#else /* Word 0 - Little Endian */
        uint64_t lnkspd                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[LNKSPD]. */
        uint64_t xmit                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[XMIT]. */
        uint64_t an_err                : 1;  /**< [  2:  2](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[AN_ERR]. */
        uint64_t txfifu                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[TXFIFU]. */
        uint64_t txfifo                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[TXFIFO]. */
        uint64_t txbad                 : 1;  /**< [  5:  5](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[TXBAD]. */
        uint64_t rxerr                 : 1;  /**< [  6:  6](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[RXERR]. */
        uint64_t rxbad                 : 1;  /**< [  7:  7](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[RXBAD]. */
        uint64_t rxlock                : 1;  /**< [  8:  8](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[RXLOCK]. */
        uint64_t an_bad                : 1;  /**< [  9:  9](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[AN_BAD]. */
        uint64_t sync_bad              : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[SYNC_BAD]. */
        uint64_t dup                   : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[DUP]. */
        uint64_t dbg_sync              : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets RGX(0)_GMP_PCS_INT(0)[DBG_SYNC]. */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_pcs_intx_w1s_s cn; */
};
typedef union bdk_rgxx_gmp_pcs_intx_w1s bdk_rgxx_gmp_pcs_intx_w1s_t;

static inline uint64_t BDK_RGXX_GMP_PCS_INTX_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_PCS_INTX_W1S(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8030088ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_PCS_INTX_W1S", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_PCS_INTX_W1S(a,b) bdk_rgxx_gmp_pcs_intx_w1s_t
#define bustype_BDK_RGXX_GMP_PCS_INTX_W1S(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_PCS_INTX_W1S(a,b) "RGXX_GMP_PCS_INTX_W1S"
#define device_bar_BDK_RGXX_GMP_PCS_INTX_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_PCS_INTX_W1S(a,b) (a)
#define arguments_BDK_RGXX_GMP_PCS_INTX_W1S(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_pcs_link#_timer
 *
 * INTERNAL: RGX GMP PCS Link Timer Registers
 *
 * This is the 1.6 ms nominal link timer register.
 */
union bdk_rgxx_gmp_pcs_linkx_timer
{
    uint64_t u;
    struct bdk_rgxx_gmp_pcs_linkx_timer_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t count                 : 16; /**< [ 15:  0](R/W) (Coprocessor clock period * 1024) * [COUNT] should be 1.6 ms for SGMII/QSGMII and 10 ms
                                                                 otherwise,
                                                                 which is the link timer used in autonegotiation. Reset assumes a 700 MHz coprocessor
                                                                 clock for 1.6 ms link timer. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 16; /**< [ 15:  0](R/W) (Coprocessor clock period * 1024) * [COUNT] should be 1.6 ms for SGMII/QSGMII and 10 ms
                                                                 otherwise,
                                                                 which is the link timer used in autonegotiation. Reset assumes a 700 MHz coprocessor
                                                                 clock for 1.6 ms link timer. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_pcs_linkx_timer_s cn; */
};
typedef union bdk_rgxx_gmp_pcs_linkx_timer bdk_rgxx_gmp_pcs_linkx_timer_t;

static inline uint64_t BDK_RGXX_GMP_PCS_LINKX_TIMER(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_PCS_LINKX_TIMER(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8030040ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_PCS_LINKX_TIMER", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_PCS_LINKX_TIMER(a,b) bdk_rgxx_gmp_pcs_linkx_timer_t
#define bustype_BDK_RGXX_GMP_PCS_LINKX_TIMER(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_PCS_LINKX_TIMER(a,b) "RGXX_GMP_PCS_LINKX_TIMER"
#define device_bar_BDK_RGXX_GMP_PCS_LINKX_TIMER(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_PCS_LINKX_TIMER(a,b) (a)
#define arguments_BDK_RGXX_GMP_PCS_LINKX_TIMER(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_pcs_misc#_ctl
 *
 * INTERNAL: RGX GMP SGMII Miscellaneous Control Registers
 *
 * Internal:
 * SGMII bit [12] is really a misnomer, it is a decode  of pi_qlm_cfg pins to indicate SGMII or
 * 1000Base-X modes.
 *
 * Note: The SGMII AN Advertisement Register above will be sent during Auto Negotiation if
 * [MAC_PHY] is set (1=PHY mode). If the bit is not set (0=MAC mode), the
 * tx_Config_Reg\<14\> becomes ACK bit and tx_Config_Reg\<0\> is always 1.
 * All other bits in tx_Config_Reg sent will be 0. The PHY dictates the Auto Negotiation results.
 */
union bdk_rgxx_gmp_pcs_miscx_ctl
{
    uint64_t u;
    struct bdk_rgxx_gmp_pcs_miscx_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t disp_en               : 1;  /**< [ 13: 13](R/W) Disparity check enable.  When LMAC_TYPE=QSGMII the running disparity check should be
                                                                 disabled
                                                                 to
                                                                 prevent propogation across ports.
                                                                 0 = disable disparity check
                                                                 1 = enable disparity checking

                                                                 See GSER()_LANE_MODE[LMODE]. */
        uint64_t sgmii                 : 1;  /**< [ 12: 12](RO/H) SGMII mode.
                                                                 0 = other mode selected.
                                                                 1 = SGMII or 1000BASE-X mode selected.

                                                                 See GSER()_LANE_MODE[LMODE]. */
        uint64_t gmxeno                : 1;  /**< [ 11: 11](R/W) GMI enable override. When set, forces GMI to appear disabled. The enable/disable status of
                                                                 GMI is checked only at SOP of every packet. */
        uint64_t loopbck2              : 1;  /**< [ 10: 10](R/W) Sets external loopback mode to return RX data back out via the TX data path. 0 = No
                                                                 loopback, 1 = Loopback.
                                                                 LOOPBCK1 and LOOPBCK2 modes may not be supported simultaneously. */
        uint64_t mac_phy               : 1;  /**< [  9:  9](R/W) MAC/PHY.
                                                                 0 = MAC.
                                                                 1 = PHY decides the tx_Config_Reg value to be sent during autonegotiation. */
        uint64_t mode                  : 1;  /**< [  8:  8](R/W) Mode bit.

                                                                 _ 0 = SGMII mode is selected and the following note applies.
                                                                 The SGMII AN advertisement register (RGX()_GMP_PCS_SGM()_AN_ADV) is sent during
                                                                 autonegotiation if RGX()_GMP_PCS_MISC()_CTL[MAC_PHY] = 1 (PHY mode). If [MAC_PHY]
                                                                 = 0 (MAC mode), the tx_Config_Reg\<14\> becomes ACK bit and \<0\> is always 1. All other bits
                                                                 in tx_Config_Reg sent are 0. The PHY dictates the autonegotiation results.

                                                                 _ 1 = 1000Base-X mode is selected. Autonegotiation follows IEEE 802.3 clause 37. */
        uint64_t an_ovrd               : 1;  /**< [  7:  7](R/W) Autonegotiation results override:
                                                                 0 = Disable.
                                                                 1 = Enable override. Autonegotiation is allowed to happen but the results are ignored
                                                                 when this bit is set.  Duplex and Link speed values are set from RGX()_GMP_PCS_MISC()_CTL. */
        uint64_t samp_pt               : 7;  /**< [  6:  0](R/W) Byte number in elongated frames for 10/100 Mb/s operation for data sampling on RX side in
                                                                 PCS. Recommended values are 0x5 for 100 Mb/s operation and 0x32 for 10 Mb/s operation.

                                                                 For 10 Mb/s operation, this field should be set to a value less than 99 and greater than
                                                                 0.
                                                                 If set out of this range, a value of 50 is used for actual sampling internally without
                                                                 affecting the CSR field.

                                                                 For 100 Mb/s operation this field should be set to a value less than 9 and greater than 0.
                                                                 If set out of this range, a value of 5 is used for actual sampling internally without
                                                                 affecting the CSR field. */
#else /* Word 0 - Little Endian */
        uint64_t samp_pt               : 7;  /**< [  6:  0](R/W) Byte number in elongated frames for 10/100 Mb/s operation for data sampling on RX side in
                                                                 PCS. Recommended values are 0x5 for 100 Mb/s operation and 0x32 for 10 Mb/s operation.

                                                                 For 10 Mb/s operation, this field should be set to a value less than 99 and greater than
                                                                 0.
                                                                 If set out of this range, a value of 50 is used for actual sampling internally without
                                                                 affecting the CSR field.

                                                                 For 100 Mb/s operation this field should be set to a value less than 9 and greater than 0.
                                                                 If set out of this range, a value of 5 is used for actual sampling internally without
                                                                 affecting the CSR field. */
        uint64_t an_ovrd               : 1;  /**< [  7:  7](R/W) Autonegotiation results override:
                                                                 0 = Disable.
                                                                 1 = Enable override. Autonegotiation is allowed to happen but the results are ignored
                                                                 when this bit is set.  Duplex and Link speed values are set from RGX()_GMP_PCS_MISC()_CTL. */
        uint64_t mode                  : 1;  /**< [  8:  8](R/W) Mode bit.

                                                                 _ 0 = SGMII mode is selected and the following note applies.
                                                                 The SGMII AN advertisement register (RGX()_GMP_PCS_SGM()_AN_ADV) is sent during
                                                                 autonegotiation if RGX()_GMP_PCS_MISC()_CTL[MAC_PHY] = 1 (PHY mode). If [MAC_PHY]
                                                                 = 0 (MAC mode), the tx_Config_Reg\<14\> becomes ACK bit and \<0\> is always 1. All other bits
                                                                 in tx_Config_Reg sent are 0. The PHY dictates the autonegotiation results.

                                                                 _ 1 = 1000Base-X mode is selected. Autonegotiation follows IEEE 802.3 clause 37. */
        uint64_t mac_phy               : 1;  /**< [  9:  9](R/W) MAC/PHY.
                                                                 0 = MAC.
                                                                 1 = PHY decides the tx_Config_Reg value to be sent during autonegotiation. */
        uint64_t loopbck2              : 1;  /**< [ 10: 10](R/W) Sets external loopback mode to return RX data back out via the TX data path. 0 = No
                                                                 loopback, 1 = Loopback.
                                                                 LOOPBCK1 and LOOPBCK2 modes may not be supported simultaneously. */
        uint64_t gmxeno                : 1;  /**< [ 11: 11](R/W) GMI enable override. When set, forces GMI to appear disabled. The enable/disable status of
                                                                 GMI is checked only at SOP of every packet. */
        uint64_t sgmii                 : 1;  /**< [ 12: 12](RO/H) SGMII mode.
                                                                 0 = other mode selected.
                                                                 1 = SGMII or 1000BASE-X mode selected.

                                                                 See GSER()_LANE_MODE[LMODE]. */
        uint64_t disp_en               : 1;  /**< [ 13: 13](R/W) Disparity check enable.  When LMAC_TYPE=QSGMII the running disparity check should be
                                                                 disabled
                                                                 to
                                                                 prevent propogation across ports.
                                                                 0 = disable disparity check
                                                                 1 = enable disparity checking

                                                                 See GSER()_LANE_MODE[LMODE]. */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_pcs_miscx_ctl_s cn; */
};
typedef union bdk_rgxx_gmp_pcs_miscx_ctl bdk_rgxx_gmp_pcs_miscx_ctl_t;

static inline uint64_t BDK_RGXX_GMP_PCS_MISCX_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_PCS_MISCX_CTL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8030078ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_PCS_MISCX_CTL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_PCS_MISCX_CTL(a,b) bdk_rgxx_gmp_pcs_miscx_ctl_t
#define bustype_BDK_RGXX_GMP_PCS_MISCX_CTL(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_PCS_MISCX_CTL(a,b) "RGXX_GMP_PCS_MISCX_CTL"
#define device_bar_BDK_RGXX_GMP_PCS_MISCX_CTL(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_PCS_MISCX_CTL(a,b) (a)
#define arguments_BDK_RGXX_GMP_PCS_MISCX_CTL(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_pcs_mr#_control
 *
 * INTERNAL: RGX GMP PCS Control Registers
 */
union bdk_rgxx_gmp_pcs_mrx_control
{
    uint64_t u;
    struct bdk_rgxx_gmp_pcs_mrx_control_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t reset                 : 1;  /**< [ 15: 15](R/W/H) Set to reset.
                                                                 0 = Normal operation.
                                                                 1 = Software PCS reset.

                                                                 The bit returns to 0 after PCS has been reset. Takes 32 coprocessor-clock cycles to reset
                                                                 PCS.   This bit, when set, also drains the tx gmi fifo and can be used as a fifo draining
                                                                 mechanism for both Serdes reset conditions and for XCV reset conditions. */
        uint64_t loopbck1              : 1;  /**< [ 14: 14](R/W) Enable loopback:
                                                                   0 = Normal operation.
                                                                   1 = Internal loopback mode.

                                                                 The loopback mode returns loopback TX data from GMII TX back to GMII RX interface. The
                                                                 loopback happens in the PCS module. Autonegotiation is disabled even if AN_EN is set
                                                                 during loopback. */
        uint64_t spdlsb                : 1;  /**< [ 13: 13](R/W) Least-significant bit of the link-speed field, i.e. SPD\<0\>. Refer to SPDMSB. */
        uint64_t an_en                 : 1;  /**< [ 12: 12](R/W) Autonegotiation enable. */
        uint64_t pwr_dn                : 1;  /**< [ 11: 11](R/W) Power down:
                                                                   0 = Normal operation.
                                                                   1 = Power down (hardware reset). */
        uint64_t reserved_10           : 1;
        uint64_t rst_an                : 1;  /**< [  9:  9](R/W/H) Reset autonegotiation. When set, if AN_EN = 1 and
                                                                 RGX()_GMP_PCS_MR()_STATUS[AN_ABIL] = 1, autonegotiation begins. Otherwise,
                                                                 software write requests are ignored and this bit remains at 0. This bit clears itself to
                                                                 0, when autonegotiation starts. */
        uint64_t dup                   : 1;  /**< [  8:  8](R/W) Duplex mode:
                                                                   0 = half duplex; effective only if autonegotiation is disabled.
                                                                   1 = full duplex.

                                                                 If RGX()_GMP_PCS_MR()_STATUS \<15:9\> and
                                                                 RGX()_GMP_PCS_AN()_ADV\<15:12\> allow only one duplex mode, this bit corresponds to
                                                                 that value and any attempts to write are ignored. */
        uint64_t coltst                : 1;  /**< [  7:  7](R/W) Enable COL signal test.
                                                                 During COL test, the COL signal reflects the GMII TX_EN signal with less than 16BT delay. */
        uint64_t spdmsb                : 1;  /**< [  6:  6](R/W) Link speed most-significant bit, i.e SPD\<1\>; effective only if autonegotiation is
                                                                 disabled.

                                                                 \<pre\>
                                                                 [SPDMSB]   [SPDLSB]   Link Speed
                                                                  0          0         10 Mb/s
                                                                  0          1         100 Mb/s
                                                                  1          0         1000 Mb/s
                                                                  1          1         reserved
                                                                 \</pre\> */
        uint64_t uni                   : 1;  /**< [  5:  5](R/W) Unidirectional (Std 802.3-2005, Clause 66.2). When set to 1, this bit overrides [AN_EN]
                                                                 and
                                                                 disables the autonegotiation variable mr_an_enable. Used in both 1000BASE-X and
                                                                 SGMII/QSGMII
                                                                 modes. */
        uint64_t reserved_0_4          : 5;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_4          : 5;
        uint64_t uni                   : 1;  /**< [  5:  5](R/W) Unidirectional (Std 802.3-2005, Clause 66.2). When set to 1, this bit overrides [AN_EN]
                                                                 and
                                                                 disables the autonegotiation variable mr_an_enable. Used in both 1000BASE-X and
                                                                 SGMII/QSGMII
                                                                 modes. */
        uint64_t spdmsb                : 1;  /**< [  6:  6](R/W) Link speed most-significant bit, i.e SPD\<1\>; effective only if autonegotiation is
                                                                 disabled.

                                                                 \<pre\>
                                                                 [SPDMSB]   [SPDLSB]   Link Speed
                                                                  0          0         10 Mb/s
                                                                  0          1         100 Mb/s
                                                                  1          0         1000 Mb/s
                                                                  1          1         reserved
                                                                 \</pre\> */
        uint64_t coltst                : 1;  /**< [  7:  7](R/W) Enable COL signal test.
                                                                 During COL test, the COL signal reflects the GMII TX_EN signal with less than 16BT delay. */
        uint64_t dup                   : 1;  /**< [  8:  8](R/W) Duplex mode:
                                                                   0 = half duplex; effective only if autonegotiation is disabled.
                                                                   1 = full duplex.

                                                                 If RGX()_GMP_PCS_MR()_STATUS \<15:9\> and
                                                                 RGX()_GMP_PCS_AN()_ADV\<15:12\> allow only one duplex mode, this bit corresponds to
                                                                 that value and any attempts to write are ignored. */
        uint64_t rst_an                : 1;  /**< [  9:  9](R/W/H) Reset autonegotiation. When set, if AN_EN = 1 and
                                                                 RGX()_GMP_PCS_MR()_STATUS[AN_ABIL] = 1, autonegotiation begins. Otherwise,
                                                                 software write requests are ignored and this bit remains at 0. This bit clears itself to
                                                                 0, when autonegotiation starts. */
        uint64_t reserved_10           : 1;
        uint64_t pwr_dn                : 1;  /**< [ 11: 11](R/W) Power down:
                                                                   0 = Normal operation.
                                                                   1 = Power down (hardware reset). */
        uint64_t an_en                 : 1;  /**< [ 12: 12](R/W) Autonegotiation enable. */
        uint64_t spdlsb                : 1;  /**< [ 13: 13](R/W) Least-significant bit of the link-speed field, i.e. SPD\<0\>. Refer to SPDMSB. */
        uint64_t loopbck1              : 1;  /**< [ 14: 14](R/W) Enable loopback:
                                                                   0 = Normal operation.
                                                                   1 = Internal loopback mode.

                                                                 The loopback mode returns loopback TX data from GMII TX back to GMII RX interface. The
                                                                 loopback happens in the PCS module. Autonegotiation is disabled even if AN_EN is set
                                                                 during loopback. */
        uint64_t reset                 : 1;  /**< [ 15: 15](R/W/H) Set to reset.
                                                                 0 = Normal operation.
                                                                 1 = Software PCS reset.

                                                                 The bit returns to 0 after PCS has been reset. Takes 32 coprocessor-clock cycles to reset
                                                                 PCS.   This bit, when set, also drains the tx gmi fifo and can be used as a fifo draining
                                                                 mechanism for both Serdes reset conditions and for XCV reset conditions. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_pcs_mrx_control_s cn; */
};
typedef union bdk_rgxx_gmp_pcs_mrx_control bdk_rgxx_gmp_pcs_mrx_control_t;

static inline uint64_t BDK_RGXX_GMP_PCS_MRX_CONTROL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_PCS_MRX_CONTROL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8030000ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_PCS_MRX_CONTROL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_PCS_MRX_CONTROL(a,b) bdk_rgxx_gmp_pcs_mrx_control_t
#define bustype_BDK_RGXX_GMP_PCS_MRX_CONTROL(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_PCS_MRX_CONTROL(a,b) "RGXX_GMP_PCS_MRX_CONTROL"
#define device_bar_BDK_RGXX_GMP_PCS_MRX_CONTROL(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_PCS_MRX_CONTROL(a,b) (a)
#define arguments_BDK_RGXX_GMP_PCS_MRX_CONTROL(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_pcs_mr#_status
 *
 * INTERNAL: RGX GMP PCS Status Registers
 *
 * Bits \<15:9\> in this register indicate the ability to operate when
 * RGX()_GMP_PCS_MISC()_CTL[MAC_PHY] is set to MAC mode. Bits \<15:9\> are always read as
 * 0, indicating that the chip cannot operate in the corresponding modes. The field [RM_FLT] is a
 * 'don't care' when the selected mode is SGMII/QSGMII.
 */
union bdk_rgxx_gmp_pcs_mrx_status
{
    uint64_t u;
    struct bdk_rgxx_gmp_pcs_mrx_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t hun_t4                : 1;  /**< [ 15: 15](RO/H) Indicates 100BASE-T4 capable. */
        uint64_t hun_xfd               : 1;  /**< [ 14: 14](RO/H) Indicates 100BASE-X full duplex. */
        uint64_t hun_xhd               : 1;  /**< [ 13: 13](RO/H) Indicates 100BASE-X half duplex. */
        uint64_t ten_fd                : 1;  /**< [ 12: 12](RO/H) Indicates 10Mb/s full duplex. */
        uint64_t ten_hd                : 1;  /**< [ 11: 11](RO/H) Indicates 10Mb/s half duplex. */
        uint64_t hun_t2fd              : 1;  /**< [ 10: 10](RO/H) Indicates 100BASE-T2 full duplex. */
        uint64_t hun_t2hd              : 1;  /**< [  9:  9](RO/H) Indicates 100BASE-T2 half duplex. */
        uint64_t ext_st                : 1;  /**< [  8:  8](RO/H) Extended status information. When set to 1, indicates that additional status data is
                                                                 available in RGX()_GMP_PCS_AN()_EXT_ST. */
        uint64_t reserved_7            : 1;
        uint64_t prb_sup               : 1;  /**< [  6:  6](RO/H) Preamble not needed.
                                                                 0 = Cannot accept frames without preamble bytes.
                                                                 1 = Can work without preamble bytes at the beginning of frames. */
        uint64_t an_cpt                : 1;  /**< [  5:  5](RO/H) Indicates autonegotiation is complete; the contents of the
                                                                 RGX()_GMP_PCS_AN()_RESULTS are valid. */
        uint64_t rm_flt                : 1;  /**< [  4:  4](RO/H) Indicates remote fault condition occurred. This bit implements a latching-high behavior.
                                                                 It is cleared when software reads this register or when
                                                                 RGX()_GMP_PCS_MR()_CONTROL[RESET] is asserted.
                                                                 See RGX()_GMP_PCS_AN()_ADV[REM_FLT] for fault conditions. */
        uint64_t an_abil               : 1;  /**< [  3:  3](RO/H) Indicates autonegotiation capable. */
        uint64_t lnk_st                : 1;  /**< [  2:  2](RO/H) Link state:
                                                                   0 = link down.
                                                                   1 = link up.

                                                                 Set during autonegotiation process. Set whenever XMIT = DATA. Latching-low behavior when
                                                                 link goes down. Link down value of the bit stays low until software reads the register. */
        uint64_t reserved_1            : 1;
        uint64_t extnd                 : 1;  /**< [  0:  0](RO/H) This field is always 0, extended capability registers not present. */
#else /* Word 0 - Little Endian */
        uint64_t extnd                 : 1;  /**< [  0:  0](RO/H) This field is always 0, extended capability registers not present. */
        uint64_t reserved_1            : 1;
        uint64_t lnk_st                : 1;  /**< [  2:  2](RO/H) Link state:
                                                                   0 = link down.
                                                                   1 = link up.

                                                                 Set during autonegotiation process. Set whenever XMIT = DATA. Latching-low behavior when
                                                                 link goes down. Link down value of the bit stays low until software reads the register. */
        uint64_t an_abil               : 1;  /**< [  3:  3](RO/H) Indicates autonegotiation capable. */
        uint64_t rm_flt                : 1;  /**< [  4:  4](RO/H) Indicates remote fault condition occurred. This bit implements a latching-high behavior.
                                                                 It is cleared when software reads this register or when
                                                                 RGX()_GMP_PCS_MR()_CONTROL[RESET] is asserted.
                                                                 See RGX()_GMP_PCS_AN()_ADV[REM_FLT] for fault conditions. */
        uint64_t an_cpt                : 1;  /**< [  5:  5](RO/H) Indicates autonegotiation is complete; the contents of the
                                                                 RGX()_GMP_PCS_AN()_RESULTS are valid. */
        uint64_t prb_sup               : 1;  /**< [  6:  6](RO/H) Preamble not needed.
                                                                 0 = Cannot accept frames without preamble bytes.
                                                                 1 = Can work without preamble bytes at the beginning of frames. */
        uint64_t reserved_7            : 1;
        uint64_t ext_st                : 1;  /**< [  8:  8](RO/H) Extended status information. When set to 1, indicates that additional status data is
                                                                 available in RGX()_GMP_PCS_AN()_EXT_ST. */
        uint64_t hun_t2hd              : 1;  /**< [  9:  9](RO/H) Indicates 100BASE-T2 half duplex. */
        uint64_t hun_t2fd              : 1;  /**< [ 10: 10](RO/H) Indicates 100BASE-T2 full duplex. */
        uint64_t ten_hd                : 1;  /**< [ 11: 11](RO/H) Indicates 10Mb/s half duplex. */
        uint64_t ten_fd                : 1;  /**< [ 12: 12](RO/H) Indicates 10Mb/s full duplex. */
        uint64_t hun_xhd               : 1;  /**< [ 13: 13](RO/H) Indicates 100BASE-X half duplex. */
        uint64_t hun_xfd               : 1;  /**< [ 14: 14](RO/H) Indicates 100BASE-X full duplex. */
        uint64_t hun_t4                : 1;  /**< [ 15: 15](RO/H) Indicates 100BASE-T4 capable. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_pcs_mrx_status_s cn; */
};
typedef union bdk_rgxx_gmp_pcs_mrx_status bdk_rgxx_gmp_pcs_mrx_status_t;

static inline uint64_t BDK_RGXX_GMP_PCS_MRX_STATUS(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_PCS_MRX_STATUS(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8030008ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_PCS_MRX_STATUS", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_PCS_MRX_STATUS(a,b) bdk_rgxx_gmp_pcs_mrx_status_t
#define bustype_BDK_RGXX_GMP_PCS_MRX_STATUS(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_PCS_MRX_STATUS(a,b) "RGXX_GMP_PCS_MRX_STATUS"
#define device_bar_BDK_RGXX_GMP_PCS_MRX_STATUS(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_PCS_MRX_STATUS(a,b) (a)
#define arguments_BDK_RGXX_GMP_PCS_MRX_STATUS(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_pcs_rx#_states
 *
 * INTERNAL: RGX GMP PCS RX State-Machines States Registers
 */
union bdk_rgxx_gmp_pcs_rxx_states
{
    uint64_t u;
    struct bdk_rgxx_gmp_pcs_rxx_states_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t rx_bad                : 1;  /**< [ 15: 15](RO/H) Receive state machine is in an illegal state. */
        uint64_t rx_st                 : 5;  /**< [ 14: 10](RO/H) Receive state-machine state. */
        uint64_t sync_bad              : 1;  /**< [  9:  9](RO/H) Receive synchronization state machine is in an illegal state. */
        uint64_t sync                  : 4;  /**< [  8:  5](RO/H) Receive synchronization state-machine state. */
        uint64_t an_bad                : 1;  /**< [  4:  4](RO/H) Autonegotiation state machine is in an illegal state. */
        uint64_t an_st                 : 4;  /**< [  3:  0](RO/H) Autonegotiation state-machine state. */
#else /* Word 0 - Little Endian */
        uint64_t an_st                 : 4;  /**< [  3:  0](RO/H) Autonegotiation state-machine state. */
        uint64_t an_bad                : 1;  /**< [  4:  4](RO/H) Autonegotiation state machine is in an illegal state. */
        uint64_t sync                  : 4;  /**< [  8:  5](RO/H) Receive synchronization state-machine state. */
        uint64_t sync_bad              : 1;  /**< [  9:  9](RO/H) Receive synchronization state machine is in an illegal state. */
        uint64_t rx_st                 : 5;  /**< [ 14: 10](RO/H) Receive state-machine state. */
        uint64_t rx_bad                : 1;  /**< [ 15: 15](RO/H) Receive state machine is in an illegal state. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_pcs_rxx_states_s cn; */
};
typedef union bdk_rgxx_gmp_pcs_rxx_states bdk_rgxx_gmp_pcs_rxx_states_t;

static inline uint64_t BDK_RGXX_GMP_PCS_RXX_STATES(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_PCS_RXX_STATES(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8030058ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_PCS_RXX_STATES", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_PCS_RXX_STATES(a,b) bdk_rgxx_gmp_pcs_rxx_states_t
#define bustype_BDK_RGXX_GMP_PCS_RXX_STATES(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_PCS_RXX_STATES(a,b) "RGXX_GMP_PCS_RXX_STATES"
#define device_bar_BDK_RGXX_GMP_PCS_RXX_STATES(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_PCS_RXX_STATES(a,b) (a)
#define arguments_BDK_RGXX_GMP_PCS_RXX_STATES(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_pcs_rx#_sync
 *
 * INTERNAL: RGX GMP PCS Code Group Synchronization Registers
 */
union bdk_rgxx_gmp_pcs_rxx_sync
{
    uint64_t u;
    struct bdk_rgxx_gmp_pcs_rxx_sync_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t sync                  : 1;  /**< [  1:  1](RO/H) When set, code group synchronization achieved. */
        uint64_t bit_lock              : 1;  /**< [  0:  0](RO/H) When set, bit lock achieved. */
#else /* Word 0 - Little Endian */
        uint64_t bit_lock              : 1;  /**< [  0:  0](RO/H) When set, bit lock achieved. */
        uint64_t sync                  : 1;  /**< [  1:  1](RO/H) When set, code group synchronization achieved. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_pcs_rxx_sync_s cn; */
};
typedef union bdk_rgxx_gmp_pcs_rxx_sync bdk_rgxx_gmp_pcs_rxx_sync_t;

static inline uint64_t BDK_RGXX_GMP_PCS_RXX_SYNC(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_PCS_RXX_SYNC(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8030050ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_PCS_RXX_SYNC", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_PCS_RXX_SYNC(a,b) bdk_rgxx_gmp_pcs_rxx_sync_t
#define bustype_BDK_RGXX_GMP_PCS_RXX_SYNC(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_PCS_RXX_SYNC(a,b) "RGXX_GMP_PCS_RXX_SYNC"
#define device_bar_BDK_RGXX_GMP_PCS_RXX_SYNC(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_PCS_RXX_SYNC(a,b) (a)
#define arguments_BDK_RGXX_GMP_PCS_RXX_SYNC(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_pcs_sgm#_an_adv
 *
 * INTERNAL: RGX GMP PCS SGMII Autonegotiation Advertisement Registers
 *
 * This is the SGMII autonegotiation advertisement register (sent out as tx_Config_Reg\<15:0\> as
 * defined in IEEE 802.3 clause 37). This register is sent during autonegotiation if
 * RGX()_GMP_PCS_MISC()_CTL[MAC_PHY] is set (1 = PHY mode). If the bit is not set (0 =
 * MAC mode), then tx_Config_Reg\<14\> becomes ACK bit and tx_Config_Reg\<0\> is always 1. All other
 * bits in tx_Config_Reg sent will be 0. The PHY dictates the autonegotiation results.
 */
union bdk_rgxx_gmp_pcs_sgmx_an_adv
{
    uint64_t u;
    struct bdk_rgxx_gmp_pcs_sgmx_an_adv_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t link                  : 1;  /**< [ 15: 15](R/W) Link status: 1 = Link up. 0 = Link down. */
        uint64_t ack                   : 1;  /**< [ 14: 14](RO/H) Autonegotiation acknowledgement. */
        uint64_t reserved_13           : 1;
        uint64_t dup                   : 1;  /**< [ 12: 12](R/W) Duplex mode: 1 = full duplex, 0 = half duplex. */
        uint64_t speed                 : 2;  /**< [ 11: 10](R/W) Link speed:
                                                                 0x0 = 10 Mb/s.
                                                                 0x1 = 100 Mb/s.
                                                                 0x2 = 1000 Mb/s.
                                                                 0x3 = Reserved. */
        uint64_t reserved_1_9          : 9;
        uint64_t one                   : 1;  /**< [  0:  0](RO/H) Always set to match tx_Config_Reg\<0\>. */
#else /* Word 0 - Little Endian */
        uint64_t one                   : 1;  /**< [  0:  0](RO/H) Always set to match tx_Config_Reg\<0\>. */
        uint64_t reserved_1_9          : 9;
        uint64_t speed                 : 2;  /**< [ 11: 10](R/W) Link speed:
                                                                 0x0 = 10 Mb/s.
                                                                 0x1 = 100 Mb/s.
                                                                 0x2 = 1000 Mb/s.
                                                                 0x3 = Reserved. */
        uint64_t dup                   : 1;  /**< [ 12: 12](R/W) Duplex mode: 1 = full duplex, 0 = half duplex. */
        uint64_t reserved_13           : 1;
        uint64_t ack                   : 1;  /**< [ 14: 14](RO/H) Autonegotiation acknowledgement. */
        uint64_t link                  : 1;  /**< [ 15: 15](R/W) Link status: 1 = Link up. 0 = Link down. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_pcs_sgmx_an_adv_s cn; */
};
typedef union bdk_rgxx_gmp_pcs_sgmx_an_adv bdk_rgxx_gmp_pcs_sgmx_an_adv_t;

static inline uint64_t BDK_RGXX_GMP_PCS_SGMX_AN_ADV(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_PCS_SGMX_AN_ADV(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8030068ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_PCS_SGMX_AN_ADV", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_PCS_SGMX_AN_ADV(a,b) bdk_rgxx_gmp_pcs_sgmx_an_adv_t
#define bustype_BDK_RGXX_GMP_PCS_SGMX_AN_ADV(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_PCS_SGMX_AN_ADV(a,b) "RGXX_GMP_PCS_SGMX_AN_ADV"
#define device_bar_BDK_RGXX_GMP_PCS_SGMX_AN_ADV(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_PCS_SGMX_AN_ADV(a,b) (a)
#define arguments_BDK_RGXX_GMP_PCS_SGMX_AN_ADV(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_pcs_sgm#_lp_adv
 *
 * INTERNAL: RGX GMP PCS SGMII Link-Partner-Advertisement Registers
 *
 * This is the SGMII link partner advertisement register (received as rx_Config_Reg\<15:0\> as
 * defined in IEEE 802.3 clause 37).
 */
union bdk_rgxx_gmp_pcs_sgmx_lp_adv
{
    uint64_t u;
    struct bdk_rgxx_gmp_pcs_sgmx_lp_adv_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t link                  : 1;  /**< [ 15: 15](RO/H) Link status: 1 = Link up. 0 = Link down. */
        uint64_t reserved_13_14        : 2;
        uint64_t dup                   : 1;  /**< [ 12: 12](RO/H) Duplex mode: 1 = Full duplex, 0 = Half duplex. */
        uint64_t speed                 : 2;  /**< [ 11: 10](RO/H) Link speed:
                                                                 0x0 = 10 Mb/s.
                                                                 0x1 = 100 Mb/s.
                                                                 0x2 = 1000 Mb/s.
                                                                 0x3 = Reserved. */
        uint64_t reserved_1_9          : 9;
        uint64_t one                   : 1;  /**< [  0:  0](RO/H) Always set to match tx_Config_Reg\<0\> */
#else /* Word 0 - Little Endian */
        uint64_t one                   : 1;  /**< [  0:  0](RO/H) Always set to match tx_Config_Reg\<0\> */
        uint64_t reserved_1_9          : 9;
        uint64_t speed                 : 2;  /**< [ 11: 10](RO/H) Link speed:
                                                                 0x0 = 10 Mb/s.
                                                                 0x1 = 100 Mb/s.
                                                                 0x2 = 1000 Mb/s.
                                                                 0x3 = Reserved. */
        uint64_t dup                   : 1;  /**< [ 12: 12](RO/H) Duplex mode: 1 = Full duplex, 0 = Half duplex. */
        uint64_t reserved_13_14        : 2;
        uint64_t link                  : 1;  /**< [ 15: 15](RO/H) Link status: 1 = Link up. 0 = Link down. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    struct bdk_rgxx_gmp_pcs_sgmx_lp_adv_cn
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t link                  : 1;  /**< [ 15: 15](RO/H) Link status: 1 = Link up. 0 = Link down. */
        uint64_t reserved_14           : 1;
        uint64_t reserved_13           : 1;
        uint64_t dup                   : 1;  /**< [ 12: 12](RO/H) Duplex mode: 1 = Full duplex, 0 = Half duplex. */
        uint64_t speed                 : 2;  /**< [ 11: 10](RO/H) Link speed:
                                                                 0x0 = 10 Mb/s.
                                                                 0x1 = 100 Mb/s.
                                                                 0x2 = 1000 Mb/s.
                                                                 0x3 = Reserved. */
        uint64_t reserved_1_9          : 9;
        uint64_t one                   : 1;  /**< [  0:  0](RO/H) Always set to match tx_Config_Reg\<0\> */
#else /* Word 0 - Little Endian */
        uint64_t one                   : 1;  /**< [  0:  0](RO/H) Always set to match tx_Config_Reg\<0\> */
        uint64_t reserved_1_9          : 9;
        uint64_t speed                 : 2;  /**< [ 11: 10](RO/H) Link speed:
                                                                 0x0 = 10 Mb/s.
                                                                 0x1 = 100 Mb/s.
                                                                 0x2 = 1000 Mb/s.
                                                                 0x3 = Reserved. */
        uint64_t dup                   : 1;  /**< [ 12: 12](RO/H) Duplex mode: 1 = Full duplex, 0 = Half duplex. */
        uint64_t reserved_13           : 1;
        uint64_t reserved_14           : 1;
        uint64_t link                  : 1;  /**< [ 15: 15](RO/H) Link status: 1 = Link up. 0 = Link down. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } cn;
};
typedef union bdk_rgxx_gmp_pcs_sgmx_lp_adv bdk_rgxx_gmp_pcs_sgmx_lp_adv_t;

static inline uint64_t BDK_RGXX_GMP_PCS_SGMX_LP_ADV(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_PCS_SGMX_LP_ADV(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8030070ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_PCS_SGMX_LP_ADV", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_PCS_SGMX_LP_ADV(a,b) bdk_rgxx_gmp_pcs_sgmx_lp_adv_t
#define bustype_BDK_RGXX_GMP_PCS_SGMX_LP_ADV(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_PCS_SGMX_LP_ADV(a,b) "RGXX_GMP_PCS_SGMX_LP_ADV"
#define device_bar_BDK_RGXX_GMP_PCS_SGMX_LP_ADV(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_PCS_SGMX_LP_ADV(a,b) (a)
#define arguments_BDK_RGXX_GMP_PCS_SGMX_LP_ADV(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_pcs_tx#_states
 *
 * INTERNAL: RGX GMP PCS TX State-Machines States Registers
 */
union bdk_rgxx_gmp_pcs_txx_states
{
    uint64_t u;
    struct bdk_rgxx_gmp_pcs_txx_states_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t xmit                  : 2;  /**< [  6:  5](RO/H) 0x0 = Undefined.
                                                                 0x1 = Config.
                                                                 0x2 = Idle.
                                                                 0x3 = Data. */
        uint64_t tx_bad                : 1;  /**< [  4:  4](RO/H) Transmit state machine in an illegal state. */
        uint64_t ord_st                : 4;  /**< [  3:  0](RO/H) Transmit ordered set state-machine state. */
#else /* Word 0 - Little Endian */
        uint64_t ord_st                : 4;  /**< [  3:  0](RO/H) Transmit ordered set state-machine state. */
        uint64_t tx_bad                : 1;  /**< [  4:  4](RO/H) Transmit state machine in an illegal state. */
        uint64_t xmit                  : 2;  /**< [  6:  5](RO/H) 0x0 = Undefined.
                                                                 0x1 = Config.
                                                                 0x2 = Idle.
                                                                 0x3 = Data. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_pcs_txx_states_s cn; */
};
typedef union bdk_rgxx_gmp_pcs_txx_states bdk_rgxx_gmp_pcs_txx_states_t;

static inline uint64_t BDK_RGXX_GMP_PCS_TXX_STATES(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_PCS_TXX_STATES(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8030060ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_PCS_TXX_STATES", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_PCS_TXX_STATES(a,b) bdk_rgxx_gmp_pcs_txx_states_t
#define bustype_BDK_RGXX_GMP_PCS_TXX_STATES(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_PCS_TXX_STATES(a,b) "RGXX_GMP_PCS_TXX_STATES"
#define device_bar_BDK_RGXX_GMP_PCS_TXX_STATES(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_PCS_TXX_STATES(a,b) (a)
#define arguments_BDK_RGXX_GMP_PCS_TXX_STATES(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_gmp_pcs_tx_rx#_polarity
 *
 * INTERNAL: RGX GMP PCS TX/RX Polarity Registers
 *
 * RGX()_GMP_PCS_TX_RX()_POLARITY[AUTORXPL] shows correct polarity needed on the link
 * receive path after code group synchronization is achieved.
 */
union bdk_rgxx_gmp_pcs_tx_rxx_polarity
{
    uint64_t u;
    struct bdk_rgxx_gmp_pcs_tx_rxx_polarity_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t rxovrd                : 1;  /**< [  3:  3](R/W) RX polarity override.
                                                                 0 = AUTORXPL determines polarity.
                                                                 1 = [RXPLRT] determines polarity. */
        uint64_t autorxpl              : 1;  /**< [  2:  2](RO/H) Auto RX polarity detected:
                                                                 0 = Normal polarity.
                                                                 1 = Inverted polarity.

                                                                 This bit always represents the correct RX polarity setting needed for successful RX path
                                                                 operation, once a successful code group sync is obtained. */
        uint64_t rxplrt                : 1;  /**< [  1:  1](R/W) RX polarity: 0 = Normal polarity, 1 = Inverted polarity. */
        uint64_t txplrt                : 1;  /**< [  0:  0](R/W) TX polarity: 0 = Normal polarity, 1 = Inverted polarity. */
#else /* Word 0 - Little Endian */
        uint64_t txplrt                : 1;  /**< [  0:  0](R/W) TX polarity: 0 = Normal polarity, 1 = Inverted polarity. */
        uint64_t rxplrt                : 1;  /**< [  1:  1](R/W) RX polarity: 0 = Normal polarity, 1 = Inverted polarity. */
        uint64_t autorxpl              : 1;  /**< [  2:  2](RO/H) Auto RX polarity detected:
                                                                 0 = Normal polarity.
                                                                 1 = Inverted polarity.

                                                                 This bit always represents the correct RX polarity setting needed for successful RX path
                                                                 operation, once a successful code group sync is obtained. */
        uint64_t rxovrd                : 1;  /**< [  3:  3](R/W) RX polarity override.
                                                                 0 = AUTORXPL determines polarity.
                                                                 1 = [RXPLRT] determines polarity. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_gmp_pcs_tx_rxx_polarity_s cn; */
};
typedef union bdk_rgxx_gmp_pcs_tx_rxx_polarity bdk_rgxx_gmp_pcs_tx_rxx_polarity_t;

static inline uint64_t BDK_RGXX_GMP_PCS_TX_RXX_POLARITY(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_GMP_PCS_TX_RXX_POLARITY(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e8030048ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_GMP_PCS_TX_RXX_POLARITY", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_GMP_PCS_TX_RXX_POLARITY(a,b) bdk_rgxx_gmp_pcs_tx_rxx_polarity_t
#define bustype_BDK_RGXX_GMP_PCS_TX_RXX_POLARITY(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_GMP_PCS_TX_RXX_POLARITY(a,b) "RGXX_GMP_PCS_TX_RXX_POLARITY"
#define device_bar_BDK_RGXX_GMP_PCS_TX_RXX_POLARITY(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RGXX_GMP_PCS_TX_RXX_POLARITY(a,b) (a)
#define arguments_BDK_RGXX_GMP_PCS_TX_RXX_POLARITY(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_msix_pba#
 *
 * RGX MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table, the bit number is indexed by the RGX_INT_VEC_E
 * enumeration.
 */
union bdk_rgxx_msix_pbax
{
    uint64_t u;
    struct bdk_rgxx_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated RGX()_MSIX_VEC()_CTL, enumerated by RGX_INT_VEC_E.
                                                                 Bits that have no associated RGX_INT_VEC_E are zero. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated RGX()_MSIX_VEC()_CTL, enumerated by RGX_INT_VEC_E.
                                                                 Bits that have no associated RGX_INT_VEC_E are zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_msix_pbax_s cn; */
};
typedef union bdk_rgxx_msix_pbax bdk_rgxx_msix_pbax_t;

static inline uint64_t BDK_RGXX_MSIX_PBAX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_MSIX_PBAX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0e84f0000ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("RGXX_MSIX_PBAX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_MSIX_PBAX(a,b) bdk_rgxx_msix_pbax_t
#define bustype_BDK_RGXX_MSIX_PBAX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_MSIX_PBAX(a,b) "RGXX_MSIX_PBAX"
#define device_bar_BDK_RGXX_MSIX_PBAX(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_RGXX_MSIX_PBAX(a,b) (a)
#define arguments_BDK_RGXX_MSIX_PBAX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_msix_vec#_addr
 *
 * RGX MSI-X Vector Table Address Registers
 * This register is the MSI-X vector table, indexed by the RGX_INT_VEC_E enumeration.
 */
union bdk_rgxx_msix_vecx_addr
{
    uint64_t u;
    struct bdk_rgxx_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's RGX()_MSIX_VEC()_ADDR, RGX()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of RGX()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_RGX()_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC])
                                                                 is set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's RGX()_MSIX_VEC()_ADDR, RGX()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of RGX()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_RGX()_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC])
                                                                 is set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_msix_vecx_addr_s cn; */
};
typedef union bdk_rgxx_msix_vecx_addr bdk_rgxx_msix_vecx_addr_t;

static inline uint64_t BDK_RGXX_MSIX_VECX_ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_MSIX_VECX_ADDR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=16)))
        return 0x87e0e8400000ll + 0x1000000ll * ((a) & 0x0) + 0x10ll * ((b) & 0x1f);
    __bdk_csr_fatal("RGXX_MSIX_VECX_ADDR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_MSIX_VECX_ADDR(a,b) bdk_rgxx_msix_vecx_addr_t
#define bustype_BDK_RGXX_MSIX_VECX_ADDR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_MSIX_VECX_ADDR(a,b) "RGXX_MSIX_VECX_ADDR"
#define device_bar_BDK_RGXX_MSIX_VECX_ADDR(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_RGXX_MSIX_VECX_ADDR(a,b) (a)
#define arguments_BDK_RGXX_MSIX_VECX_ADDR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rgx#_msix_vec#_ctl
 *
 * RGX MSI-X Vector Table Control and Data Registers
 * This register is the MSI-X vector table, indexed by the RGX_INT_VEC_E enumeration.
 */
union bdk_rgxx_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_rgxx_msix_vecx_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts will be sent to this vector. */
        uint64_t reserved_20_31        : 12;
        uint64_t data                  : 20; /**< [ 19:  0](R/W) Data to use for MSI-X delivery of this vector. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 20; /**< [ 19:  0](R/W) Data to use for MSI-X delivery of this vector. */
        uint64_t reserved_20_31        : 12;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts will be sent to this vector. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rgxx_msix_vecx_ctl_s cn; */
};
typedef union bdk_rgxx_msix_vecx_ctl bdk_rgxx_msix_vecx_ctl_t;

static inline uint64_t BDK_RGXX_MSIX_VECX_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RGXX_MSIX_VECX_CTL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=16)))
        return 0x87e0e8400008ll + 0x1000000ll * ((a) & 0x0) + 0x10ll * ((b) & 0x1f);
    __bdk_csr_fatal("RGXX_MSIX_VECX_CTL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RGXX_MSIX_VECX_CTL(a,b) bdk_rgxx_msix_vecx_ctl_t
#define bustype_BDK_RGXX_MSIX_VECX_CTL(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RGXX_MSIX_VECX_CTL(a,b) "RGXX_MSIX_VECX_CTL"
#define device_bar_BDK_RGXX_MSIX_VECX_CTL(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_RGXX_MSIX_VECX_CTL(a,b) (a)
#define arguments_BDK_RGXX_MSIX_VECX_CTL(a,b) (a),(b),-1,-1

#endif /* __BDK_CSRS_RGX_H__ */
