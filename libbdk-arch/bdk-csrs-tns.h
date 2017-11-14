#ifndef __BDK_CSRS_TNS_H__
#define __BDK_CSRS_TNS_H__
/* This file is auto-generated. Do not edit */

/***********************license start***************
 * Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
 * reserved.
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.

 *   * Neither the name of Cavium Inc. nor the names of
 *     its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written
 *     permission.

 * This Software, including technical data, may be subject to U.S. export  control
 * laws, including the U.S. Export Administration Act and its  associated
 * regulations, and may be subject to export or import  regulations in other
 * countries.

 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND CAVIUM  NETWORKS MAKES NO PROMISES, REPRESENTATIONS OR
 * WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO
 * THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY REPRESENTATION OR
 * DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT DEFECTS, AND CAVIUM
 * SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES OF TITLE,
 * MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF
 * VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
 * CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK ARISING OUT OF USE OR
 * PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
 ***********************license end**************************************/


/**
 * @file
 *
 * Configuration and status register (CSR) address and type definitions for
 * Cavium TNS.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration tns_bar_e
 *
 * TNS Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_TNS_BAR_E_TNS_PF_BAR0 (0x842000000000ll)
#define BDK_TNS_BAR_E_TNS_PF_BAR0_SIZE 0x10000ull
#define BDK_TNS_BAR_E_TNS_PF_BAR2 (0x842040000000ll)
#define BDK_TNS_BAR_E_TNS_PF_BAR2_SIZE 0x40000000ull
#define BDK_TNS_BAR_E_TNS_PF_BAR4 (0x842000f00000ll)
#define BDK_TNS_BAR_E_TNS_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration tns_int_vec_e
 *
 * TNS MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_TNS_INT_VEC_E_DP_RDMA (1)
#define BDK_TNS_INT_VEC_E_DP_RDMA_NB (3)
#define BDK_TNS_INT_VEC_E_DP_TDMA (0)
#define BDK_TNS_INT_VEC_E_DP_TDMA_NB (2)
#define BDK_TNS_INT_VEC_E_SDE_HPX(a) (0xa + (a))
#define BDK_TNS_INT_VEC_E_SDE_LPX(a) (0x17 + (a))
#define BDK_TNS_INT_VEC_E_SE_HPX(a) (4 + (a))
#define BDK_TNS_INT_VEC_E_SE_LPX(a) (7 + (a))
#define BDK_TNS_INT_VEC_E_TXQ_HPX(a) (0x24 + (a))
#define BDK_TNS_INT_VEC_E_TXQ_LPX(a) (0x2a + (a))

/**
 * Enumeration tns_phys_port_e
 *
 * TNS Physical Port Enumeration
 * Enumerates the physical port identifier for received and transmitted packets.
 */
#define BDK_TNS_PHYS_PORT_E_LMAC0 (0)
#define BDK_TNS_PHYS_PORT_E_LMAC1 (1)
#define BDK_TNS_PHYS_PORT_E_LMAC2 (2)
#define BDK_TNS_PHYS_PORT_E_LMAC3 (3)
#define BDK_TNS_PHYS_PORT_E_LMAC4 (4)
#define BDK_TNS_PHYS_PORT_E_LMAC5 (5)
#define BDK_TNS_PHYS_PORT_E_LMAC6 (6)
#define BDK_TNS_PHYS_PORT_E_LMAC7 (7)
#define BDK_TNS_PHYS_PORT_E_LOOPBACK (0xa)
#define BDK_TNS_PHYS_PORT_E_NICI0 (8)
#define BDK_TNS_PHYS_PORT_E_NICI1 (9)

/**
 * Enumeration tns_rdma_hdr_sz_e
 *
 * TNS RDMA Header Size Enumeration
 * Enumerates the header size selection for received packets.
 */
#define BDK_TNS_RDMA_HDR_SZ_E_BYTES_128 (1)
#define BDK_TNS_RDMA_HDR_SZ_E_BYTES_192 (2)
#define BDK_TNS_RDMA_HDR_SZ_E_BYTES_256 (3)
#define BDK_TNS_RDMA_HDR_SZ_E_BYTES_64 (0)

/**
 * Register (NCB) tns_bist_status
 *
 * TNS BIST Status Register
 * BIST status.
 * Internal:
 * All memories listed below are TDMA memories used for both bypass and non-bypass operation.
 */
union bdk_tns_bist_status
{
    uint64_t u;
    struct bdk_tns_bist_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t vmem                  : 1;  /**< [  4:  4](RO/H) BIST failure for the MSIX VMEM RAM. */
        uint64_t nici                  : 2;  /**< [  3:  2](RO/H) BIST failure for the NIC Interface RAMs. */
        uint64_t lmac                  : 2;  /**< [  1:  0](RO/H) BIST failure for the LMAC RAMs. */
#else /* Word 0 - Little Endian */
        uint64_t lmac                  : 2;  /**< [  1:  0](RO/H) BIST failure for the LMAC RAMs. */
        uint64_t nici                  : 2;  /**< [  3:  2](RO/H) BIST failure for the NIC Interface RAMs. */
        uint64_t vmem                  : 1;  /**< [  4:  4](RO/H) BIST failure for the MSIX VMEM RAM. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_bist_status_s cn; */
};
typedef union bdk_tns_bist_status bdk_tns_bist_status_t;

#define BDK_TNS_BIST_STATUS BDK_TNS_BIST_STATUS_FUNC()
static inline uint64_t BDK_TNS_BIST_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_BIST_STATUS_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000000ll;
    __bdk_csr_fatal("TNS_BIST_STATUS", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_BIST_STATUS bdk_tns_bist_status_t
#define bustype_BDK_TNS_BIST_STATUS BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_BIST_STATUS "TNS_BIST_STATUS"
#define device_bar_BDK_TNS_BIST_STATUS 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_BIST_STATUS 0
#define arguments_BDK_TNS_BIST_STATUS -1,-1,-1,-1

/**
 * Register (NCB) tns_bist_status1
 *
 * TNS TDMA BIST Status Register
 * BIST status.
 * Internal:
 * All TDMA memories listed below are used for non-bypass operation only.
 */
union bdk_tns_bist_status1
{
    uint64_t u;
    struct bdk_tns_bist_status1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t prc                   : 1;  /**< [  6:  6](RO/H) BIST failure for the PRC RAM. */
        uint64_t ll                    : 1;  /**< [  5:  5](RO/H) BIST failure for the LL RAM. */
        uint64_t fpm                   : 1;  /**< [  4:  4](RO/H) BIST failure for the FPM RAM. */
        uint64_t pkt_lb                : 1;  /**< [  3:  3](RO/H) BIST failure for the PKT_LB RAM. */
        uint64_t pkt_x2p               : 1;  /**< [  2:  2](RO/H) BIST failure for the PKT_X2P RAM. */
        uint64_t pkt_p2x_data          : 1;  /**< [  1:  1](RO/H) BIST failure for the PKT_P2X_DATA RAM. */
        uint64_t pkt_p2x_tkn           : 1;  /**< [  0:  0](RO/H) BIST failure for the PKT_P2X_TKN RAM. */
#else /* Word 0 - Little Endian */
        uint64_t pkt_p2x_tkn           : 1;  /**< [  0:  0](RO/H) BIST failure for the PKT_P2X_TKN RAM. */
        uint64_t pkt_p2x_data          : 1;  /**< [  1:  1](RO/H) BIST failure for the PKT_P2X_DATA RAM. */
        uint64_t pkt_x2p               : 1;  /**< [  2:  2](RO/H) BIST failure for the PKT_X2P RAM. */
        uint64_t pkt_lb                : 1;  /**< [  3:  3](RO/H) BIST failure for the PKT_LB RAM. */
        uint64_t fpm                   : 1;  /**< [  4:  4](RO/H) BIST failure for the FPM RAM. */
        uint64_t ll                    : 1;  /**< [  5:  5](RO/H) BIST failure for the LL RAM. */
        uint64_t prc                   : 1;  /**< [  6:  6](RO/H) BIST failure for the PRC RAM. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_bist_status1_s cn; */
};
typedef union bdk_tns_bist_status1 bdk_tns_bist_status1_t;

#define BDK_TNS_BIST_STATUS1 BDK_TNS_BIST_STATUS1_FUNC()
static inline uint64_t BDK_TNS_BIST_STATUS1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_BIST_STATUS1_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000010ll;
    __bdk_csr_fatal("TNS_BIST_STATUS1", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_BIST_STATUS1 bdk_tns_bist_status1_t
#define bustype_BDK_TNS_BIST_STATUS1 BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_BIST_STATUS1 "TNS_BIST_STATUS1"
#define device_bar_BDK_TNS_BIST_STATUS1 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_BIST_STATUS1 0
#define arguments_BDK_TNS_BIST_STATUS1 -1,-1,-1,-1

/**
 * Register (NCB) tns_bist_status10
 *
 * TNS SE BIST Status Register
 * BIST status.
 * Internal:
 * All memories listed below are used only for non-bypass operation.
 */
union bdk_tns_bist_status10
{
    uint64_t u;
    struct bdk_tns_bist_status10_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t se_age                : 4;  /**< [ 35: 32](RO/H) BIST failure for the SE AGE RAM. */
        uint64_t se_sram1              : 16; /**< [ 31: 16](RO/H) BIST failure for the SE SRAM1 RAM. */
        uint64_t se_sram0              : 16; /**< [ 15:  0](RO/H) BIST failure for the SE SRAM0 RAM. */
#else /* Word 0 - Little Endian */
        uint64_t se_sram0              : 16; /**< [ 15:  0](RO/H) BIST failure for the SE SRAM0 RAM. */
        uint64_t se_sram1              : 16; /**< [ 31: 16](RO/H) BIST failure for the SE SRAM1 RAM. */
        uint64_t se_age                : 4;  /**< [ 35: 32](RO/H) BIST failure for the SE AGE RAM. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_bist_status10_s cn; */
};
typedef union bdk_tns_bist_status10 bdk_tns_bist_status10_t;

#define BDK_TNS_BIST_STATUS10 BDK_TNS_BIST_STATUS10_FUNC()
static inline uint64_t BDK_TNS_BIST_STATUS10_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_BIST_STATUS10_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x8420000000a0ll;
    __bdk_csr_fatal("TNS_BIST_STATUS10", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_BIST_STATUS10 bdk_tns_bist_status10_t
#define bustype_BDK_TNS_BIST_STATUS10 BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_BIST_STATUS10 "TNS_BIST_STATUS10"
#define device_bar_BDK_TNS_BIST_STATUS10 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_BIST_STATUS10 0
#define arguments_BDK_TNS_BIST_STATUS10 -1,-1,-1,-1

/**
 * Register (NCB) tns_bist_status11
 *
 * TNS TxQ BIST Status Register
 * BIST status.
 * Internal:
 * All memories listed below are used only for non-bypass operation.
 */
union bdk_tns_bist_status11
{
    uint64_t u;
    struct bdk_tns_bist_status11_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_34_63        : 30;
        uint64_t txq_qac               : 12; /**< [ 33: 22](RO/H) BIST failure for the TxQ QAC RAM. */
        uint64_t txq_tbc               : 7;  /**< [ 21: 15](RO/H) BIST failure for the TxQ TBC RAM. */
        uint64_t txq_eq                : 1;  /**< [ 14: 14](RO/H) BIST failure for the TxQ EQ RAM. */
        uint64_t txq_dq                : 14; /**< [ 13:  0](RO/H) BIST failure for the TxQ DQ RAM. */
#else /* Word 0 - Little Endian */
        uint64_t txq_dq                : 14; /**< [ 13:  0](RO/H) BIST failure for the TxQ DQ RAM. */
        uint64_t txq_eq                : 1;  /**< [ 14: 14](RO/H) BIST failure for the TxQ EQ RAM. */
        uint64_t txq_tbc               : 7;  /**< [ 21: 15](RO/H) BIST failure for the TxQ TBC RAM. */
        uint64_t txq_qac               : 12; /**< [ 33: 22](RO/H) BIST failure for the TxQ QAC RAM. */
        uint64_t reserved_34_63        : 30;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_bist_status11_s cn; */
};
typedef union bdk_tns_bist_status11 bdk_tns_bist_status11_t;

#define BDK_TNS_BIST_STATUS11 BDK_TNS_BIST_STATUS11_FUNC()
static inline uint64_t BDK_TNS_BIST_STATUS11_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_BIST_STATUS11_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x8420000000b0ll;
    __bdk_csr_fatal("TNS_BIST_STATUS11", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_BIST_STATUS11 bdk_tns_bist_status11_t
#define bustype_BDK_TNS_BIST_STATUS11 BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_BIST_STATUS11 "TNS_BIST_STATUS11"
#define device_bar_BDK_TNS_BIST_STATUS11 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_BIST_STATUS11 0
#define arguments_BDK_TNS_BIST_STATUS11 -1,-1,-1,-1

/**
 * Register (NCB) tns_bist_status2
 *
 * TNS RDMA BIST Status Register
 * BIST status.
 * Internal:
 * All RDMA memories listed below are used only for non-bypass operation.
 */
union bdk_tns_bist_status2
{
    uint64_t u;
    struct bdk_tns_bist_status2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t b_x2p1                : 1;  /**< [ 35: 35](RO/H) BIST failure for the B_X2P1 RAM. */
        uint64_t b_x2p0                : 1;  /**< [ 34: 34](RO/H) BIST failure for the B_X2P0 RAM. */
        uint64_t b_p2x                 : 1;  /**< [ 33: 33](RO/H) BIST failure for the B_P2X RAM. */
        uint64_t sdma                  : 1;  /**< [ 32: 32](RO/H) BIST failure for the SDMA RAM. */
        uint64_t plut_sdma             : 1;  /**< [ 31: 31](RO/H) BIST failure for the PLUT_SDMA RAM. */
        uint64_t plut_p2x              : 1;  /**< [ 30: 30](RO/H) BIST failure for the PLUT_P2X RAM. */
        uint64_t pkt_lb                : 2;  /**< [ 29: 28](RO/H) BIST failure for the PKT_LB RAMs. */
        uint64_t pkt_nici1             : 2;  /**< [ 27: 26](RO/H) BIST failure for the PKT_NICI1 RAMs. */
        uint64_t pkt_nici0             : 2;  /**< [ 25: 24](RO/H) BIST failure for the PKT_NICI0 RAMs. */
        uint64_t pkt_lmac_ts           : 8;  /**< [ 23: 16](RO/H) BIST failure for the PKT_LMAC_TS RAMs. */
        uint64_t pkt_lmac7             : 2;  /**< [ 15: 14](RO/H) BIST failure for the PKT_LMAC7 RAMs. */
        uint64_t pkt_lmac6             : 2;  /**< [ 13: 12](RO/H) BIST failure for the PKT_LMAC6 RAMs. */
        uint64_t pkt_lmac5             : 2;  /**< [ 11: 10](RO/H) BIST failure for the PKT_LMAC5 RAMs. */
        uint64_t pkt_lmac4             : 2;  /**< [  9:  8](RO/H) BIST failure for the PKT_LMAC4 RAMs. */
        uint64_t pkt_lmac3             : 2;  /**< [  7:  6](RO/H) BIST failure for the PKT_LMAC3 RAMs. */
        uint64_t pkt_lmac2             : 2;  /**< [  5:  4](RO/H) BIST failure for the PKT_LMAC2 RAMs. */
        uint64_t pkt_lmac1             : 2;  /**< [  3:  2](RO/H) BIST failure for the PKT_LMAC1 RAMs. */
        uint64_t pkt_lmac0             : 2;  /**< [  1:  0](RO/H) BIST failure for the PKT_LMAC0 RAMs. */
#else /* Word 0 - Little Endian */
        uint64_t pkt_lmac0             : 2;  /**< [  1:  0](RO/H) BIST failure for the PKT_LMAC0 RAMs. */
        uint64_t pkt_lmac1             : 2;  /**< [  3:  2](RO/H) BIST failure for the PKT_LMAC1 RAMs. */
        uint64_t pkt_lmac2             : 2;  /**< [  5:  4](RO/H) BIST failure for the PKT_LMAC2 RAMs. */
        uint64_t pkt_lmac3             : 2;  /**< [  7:  6](RO/H) BIST failure for the PKT_LMAC3 RAMs. */
        uint64_t pkt_lmac4             : 2;  /**< [  9:  8](RO/H) BIST failure for the PKT_LMAC4 RAMs. */
        uint64_t pkt_lmac5             : 2;  /**< [ 11: 10](RO/H) BIST failure for the PKT_LMAC5 RAMs. */
        uint64_t pkt_lmac6             : 2;  /**< [ 13: 12](RO/H) BIST failure for the PKT_LMAC6 RAMs. */
        uint64_t pkt_lmac7             : 2;  /**< [ 15: 14](RO/H) BIST failure for the PKT_LMAC7 RAMs. */
        uint64_t pkt_lmac_ts           : 8;  /**< [ 23: 16](RO/H) BIST failure for the PKT_LMAC_TS RAMs. */
        uint64_t pkt_nici0             : 2;  /**< [ 25: 24](RO/H) BIST failure for the PKT_NICI0 RAMs. */
        uint64_t pkt_nici1             : 2;  /**< [ 27: 26](RO/H) BIST failure for the PKT_NICI1 RAMs. */
        uint64_t pkt_lb                : 2;  /**< [ 29: 28](RO/H) BIST failure for the PKT_LB RAMs. */
        uint64_t plut_p2x              : 1;  /**< [ 30: 30](RO/H) BIST failure for the PLUT_P2X RAM. */
        uint64_t plut_sdma             : 1;  /**< [ 31: 31](RO/H) BIST failure for the PLUT_SDMA RAM. */
        uint64_t sdma                  : 1;  /**< [ 32: 32](RO/H) BIST failure for the SDMA RAM. */
        uint64_t b_p2x                 : 1;  /**< [ 33: 33](RO/H) BIST failure for the B_P2X RAM. */
        uint64_t b_x2p0                : 1;  /**< [ 34: 34](RO/H) BIST failure for the B_X2P0 RAM. */
        uint64_t b_x2p1                : 1;  /**< [ 35: 35](RO/H) BIST failure for the B_X2P1 RAM. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_bist_status2_s cn; */
};
typedef union bdk_tns_bist_status2 bdk_tns_bist_status2_t;

#define BDK_TNS_BIST_STATUS2 BDK_TNS_BIST_STATUS2_FUNC()
static inline uint64_t BDK_TNS_BIST_STATUS2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_BIST_STATUS2_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000020ll;
    __bdk_csr_fatal("TNS_BIST_STATUS2", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_BIST_STATUS2 bdk_tns_bist_status2_t
#define bustype_BDK_TNS_BIST_STATUS2 BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_BIST_STATUS2 "TNS_BIST_STATUS2"
#define device_bar_BDK_TNS_BIST_STATUS2 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_BIST_STATUS2 0
#define arguments_BDK_TNS_BIST_STATUS2 -1,-1,-1,-1

/**
 * Register (NCB) tns_bist_status3
 *
 * TNS Packet Memory BIST Status Register
 * BIST status.
 * Internal:
 * All Packet Memory memories listed below are used only for non-bypass operation.
 * Bypass will still operate correctly if any of the memories below has a BIST failure.
 * Each field is organized as: {8k[3],8k[2],8k[1],8k[0],16k[3],16k[2],16k[1],16k[0]}.
 * Each of the PM regions stores one quarter of the word width, with each word being written to
 * and read from all four PM regions simultaneously.
 * Within a PM region, word width is organized as {[1], [0]} and {[3], [2]}.
 * Within a PM region, memory depth is organized as:
 *   * rows 0      - 16,383: 16k[1,0]
 *   * rows 16,384 - 32,767: 16k[3,2]
 *   * rows 32,768 - 40,959:  8k[1,0]
 *   * rows 40,960 - 49,151:  8k[3,2]
 */
union bdk_tns_bist_status3
{
    uint64_t u;
    struct bdk_tns_bist_status3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t pm3                   : 8;  /**< [ 31: 24](RO/H) BIST failure in the PM3 region. */
        uint64_t pm2                   : 8;  /**< [ 23: 16](RO/H) BIST failure in the PM2 region. */
        uint64_t pm1                   : 8;  /**< [ 15:  8](RO/H) BIST failure in the PM1 region. */
        uint64_t pm0                   : 8;  /**< [  7:  0](RO/H) BIST failure in the PM0 region. */
#else /* Word 0 - Little Endian */
        uint64_t pm0                   : 8;  /**< [  7:  0](RO/H) BIST failure in the PM0 region. */
        uint64_t pm1                   : 8;  /**< [ 15:  8](RO/H) BIST failure in the PM1 region. */
        uint64_t pm2                   : 8;  /**< [ 23: 16](RO/H) BIST failure in the PM2 region. */
        uint64_t pm3                   : 8;  /**< [ 31: 24](RO/H) BIST failure in the PM3 region. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_bist_status3_s cn; */
};
typedef union bdk_tns_bist_status3 bdk_tns_bist_status3_t;

#define BDK_TNS_BIST_STATUS3 BDK_TNS_BIST_STATUS3_FUNC()
static inline uint64_t BDK_TNS_BIST_STATUS3_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_BIST_STATUS3_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000030ll;
    __bdk_csr_fatal("TNS_BIST_STATUS3", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_BIST_STATUS3 bdk_tns_bist_status3_t
#define bustype_BDK_TNS_BIST_STATUS3 BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_BIST_STATUS3 "TNS_BIST_STATUS3"
#define device_bar_BDK_TNS_BIST_STATUS3 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_BIST_STATUS3 0
#define arguments_BDK_TNS_BIST_STATUS3 -1,-1,-1,-1

/**
 * Register (NCB) tns_bist_status4
 *
 * TNS SDE BIST Status Register
 * BIST status.
 * Internal:
 * All memories listed below are used only for non-bypass operation.
 */
union bdk_tns_bist_status4
{
    uint64_t u;
    struct bdk_tns_bist_status4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_59_63        : 5;
        uint64_t sde_mre               : 21; /**< [ 58: 38](RO/H) BIST failure for the SDE MRE RAM. */
        uint64_t sde_hdbf              : 7;  /**< [ 37: 31](RO/H) BIST failure for the SDE HDBF RAM. */
        uint64_t sde_parser_cam        : 7;  /**< [ 30: 24](RO/H) BIST failure for the SDE Parser CAM. */
        uint64_t sde_parser            : 24; /**< [ 23:  0](RO/H) BIST failure for the SDE Parser RAM. */
#else /* Word 0 - Little Endian */
        uint64_t sde_parser            : 24; /**< [ 23:  0](RO/H) BIST failure for the SDE Parser RAM. */
        uint64_t sde_parser_cam        : 7;  /**< [ 30: 24](RO/H) BIST failure for the SDE Parser CAM. */
        uint64_t sde_hdbf              : 7;  /**< [ 37: 31](RO/H) BIST failure for the SDE HDBF RAM. */
        uint64_t sde_mre               : 21; /**< [ 58: 38](RO/H) BIST failure for the SDE MRE RAM. */
        uint64_t reserved_59_63        : 5;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_bist_status4_s cn; */
};
typedef union bdk_tns_bist_status4 bdk_tns_bist_status4_t;

#define BDK_TNS_BIST_STATUS4 BDK_TNS_BIST_STATUS4_FUNC()
static inline uint64_t BDK_TNS_BIST_STATUS4_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_BIST_STATUS4_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000040ll;
    __bdk_csr_fatal("TNS_BIST_STATUS4", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_BIST_STATUS4 bdk_tns_bist_status4_t
#define bustype_BDK_TNS_BIST_STATUS4 BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_BIST_STATUS4 "TNS_BIST_STATUS4"
#define device_bar_BDK_TNS_BIST_STATUS4 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_BIST_STATUS4 0
#define arguments_BDK_TNS_BIST_STATUS4 -1,-1,-1,-1

/**
 * Register (NCB) tns_bist_status5
 *
 * TNS SDE BIST Status Register
 * BIST status.
 * Internal:
 * All memories listed below are used only for non-bypass operation.
 */
union bdk_tns_bist_status5
{
    uint64_t u;
    struct bdk_tns_bist_status5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t sde_isme              : 6;  /**< [ 47: 42](RO/H) BIST failure for the SDE ISME RAM. */
        uint64_t sde_ldea1             : 21; /**< [ 41: 21](RO/H) BIST failure for the SDE LDEA1 RAM. */
        uint64_t sde_ldea0             : 21; /**< [ 20:  0](RO/H) BIST failure for the SDE LDEA0 RAM. */
#else /* Word 0 - Little Endian */
        uint64_t sde_ldea0             : 21; /**< [ 20:  0](RO/H) BIST failure for the SDE LDEA0 RAM. */
        uint64_t sde_ldea1             : 21; /**< [ 41: 21](RO/H) BIST failure for the SDE LDEA1 RAM. */
        uint64_t sde_isme              : 6;  /**< [ 47: 42](RO/H) BIST failure for the SDE ISME RAM. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_bist_status5_s cn; */
};
typedef union bdk_tns_bist_status5 bdk_tns_bist_status5_t;

#define BDK_TNS_BIST_STATUS5 BDK_TNS_BIST_STATUS5_FUNC()
static inline uint64_t BDK_TNS_BIST_STATUS5_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_BIST_STATUS5_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000050ll;
    __bdk_csr_fatal("TNS_BIST_STATUS5", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_BIST_STATUS5 bdk_tns_bist_status5_t
#define bustype_BDK_TNS_BIST_STATUS5 BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_BIST_STATUS5 "TNS_BIST_STATUS5"
#define device_bar_BDK_TNS_BIST_STATUS5 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_BIST_STATUS5 0
#define arguments_BDK_TNS_BIST_STATUS5 -1,-1,-1,-1

/**
 * Register (NCB) tns_bist_status6
 *
 * TNS SDE BIST Status Register
 * BIST status.
 * Internal:
 * All memories listed below are used only for non-bypass operation.
 */
union bdk_tns_bist_status6
{
    uint64_t u;
    struct bdk_tns_bist_status6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t sde_cnt               : 50; /**< [ 49:  0](RO/H) BIST failure for the SDE CNT RAM. */
#else /* Word 0 - Little Endian */
        uint64_t sde_cnt               : 50; /**< [ 49:  0](RO/H) BIST failure for the SDE CNT RAM. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_bist_status6_s cn; */
};
typedef union bdk_tns_bist_status6 bdk_tns_bist_status6_t;

#define BDK_TNS_BIST_STATUS6 BDK_TNS_BIST_STATUS6_FUNC()
static inline uint64_t BDK_TNS_BIST_STATUS6_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_BIST_STATUS6_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000060ll;
    __bdk_csr_fatal("TNS_BIST_STATUS6", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_BIST_STATUS6 bdk_tns_bist_status6_t
#define bustype_BDK_TNS_BIST_STATUS6 BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_BIST_STATUS6 "TNS_BIST_STATUS6"
#define device_bar_BDK_TNS_BIST_STATUS6 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_BIST_STATUS6 0
#define arguments_BDK_TNS_BIST_STATUS6 -1,-1,-1,-1

/**
 * Register (NCB) tns_bist_status7
 *
 * TNS SDE BIST Status Register
 * BIST status.
 * Internal:
 * All memories listed below are used only for non-bypass operation.
 */
union bdk_tns_bist_status7
{
    uint64_t u;
    struct bdk_tns_bist_status7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t sde_urw3              : 40; /**< [ 63: 24](RO/H) BIST failure for the SDE URW3 RAM. */
        uint64_t sde_urw1              : 24; /**< [ 23:  0](RO/H) BIST failure for the SDE URW1 RAM. */
#else /* Word 0 - Little Endian */
        uint64_t sde_urw1              : 24; /**< [ 23:  0](RO/H) BIST failure for the SDE URW1 RAM. */
        uint64_t sde_urw3              : 40; /**< [ 63: 24](RO/H) BIST failure for the SDE URW3 RAM. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_bist_status7_s cn; */
};
typedef union bdk_tns_bist_status7 bdk_tns_bist_status7_t;

#define BDK_TNS_BIST_STATUS7 BDK_TNS_BIST_STATUS7_FUNC()
static inline uint64_t BDK_TNS_BIST_STATUS7_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_BIST_STATUS7_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000070ll;
    __bdk_csr_fatal("TNS_BIST_STATUS7", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_BIST_STATUS7 bdk_tns_bist_status7_t
#define bustype_BDK_TNS_BIST_STATUS7 BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_BIST_STATUS7 "TNS_BIST_STATUS7"
#define device_bar_BDK_TNS_BIST_STATUS7 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_BIST_STATUS7 0
#define arguments_BDK_TNS_BIST_STATUS7 -1,-1,-1,-1

/**
 * Register (NCB) tns_bist_status8
 *
 * TNS SE BIST Status Register
 * BIST status.
 * Internal:
 * All memories listed below are used only for non-bypass operation.
 */
union bdk_tns_bist_status8
{
    uint64_t u;
    struct bdk_tns_bist_status8_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t se_tcam_cam           : 48; /**< [ 63: 16](RO/H) BIST failure for the SE TCAM CAM.
                                                                 Internal:
                                                                 Due to the late addition of a multi-bank TCAM BIST controller, only a
                                                                 sub-set of the bits in this field will be set. Bug 20606. */
        uint64_t se_tcam               : 16; /**< [ 15:  0](RO/H) BIST failure for the SE TCAM RAM. */
#else /* Word 0 - Little Endian */
        uint64_t se_tcam               : 16; /**< [ 15:  0](RO/H) BIST failure for the SE TCAM RAM. */
        uint64_t se_tcam_cam           : 48; /**< [ 63: 16](RO/H) BIST failure for the SE TCAM CAM.
                                                                 Internal:
                                                                 Due to the late addition of a multi-bank TCAM BIST controller, only a
                                                                 sub-set of the bits in this field will be set. Bug 20606. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_bist_status8_s cn; */
};
typedef union bdk_tns_bist_status8 bdk_tns_bist_status8_t;

#define BDK_TNS_BIST_STATUS8 BDK_TNS_BIST_STATUS8_FUNC()
static inline uint64_t BDK_TNS_BIST_STATUS8_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_BIST_STATUS8_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000080ll;
    __bdk_csr_fatal("TNS_BIST_STATUS8", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_BIST_STATUS8 bdk_tns_bist_status8_t
#define bustype_BDK_TNS_BIST_STATUS8 BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_BIST_STATUS8 "TNS_BIST_STATUS8"
#define device_bar_BDK_TNS_BIST_STATUS8 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_BIST_STATUS8 0
#define arguments_BDK_TNS_BIST_STATUS8 -1,-1,-1,-1

/**
 * Register (NCB) tns_bist_status9
 *
 * TNS SE BIST Status Register
 * BIST status.
 * Internal:
 * All memories listed below are used only for non-bypass operation.
 */
union bdk_tns_bist_status9
{
    uint64_t u;
    struct bdk_tns_bist_status9_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t se_tcam_ecc           : 48; /**< [ 47:  0](RO/H) BIST failure for the SE TCAM ECC RAM. */
#else /* Word 0 - Little Endian */
        uint64_t se_tcam_ecc           : 48; /**< [ 47:  0](RO/H) BIST failure for the SE TCAM ECC RAM. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_bist_status9_s cn; */
};
typedef union bdk_tns_bist_status9 bdk_tns_bist_status9_t;

#define BDK_TNS_BIST_STATUS9 BDK_TNS_BIST_STATUS9_FUNC()
static inline uint64_t BDK_TNS_BIST_STATUS9_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_BIST_STATUS9_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000090ll;
    __bdk_csr_fatal("TNS_BIST_STATUS9", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_BIST_STATUS9 bdk_tns_bist_status9_t
#define bustype_BDK_TNS_BIST_STATUS9 BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_BIST_STATUS9 "TNS_BIST_STATUS9"
#define device_bar_BDK_TNS_BIST_STATUS9 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_BIST_STATUS9 0
#define arguments_BDK_TNS_BIST_STATUS9 -1,-1,-1,-1

/**
 * Register (NCB) tns_msix_pba#
 *
 * TNS MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table; the bit number is indexed by the TNS_INT_VEC_E enumeration.
 */
union bdk_tns_msix_pbax
{
    uint64_t u;
    struct bdk_tns_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated TNS_MSIX_VEC()_CTL, enumerated by TNS_INT_VEC_E.
                                                                 Bits that have no associated TNS_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated TNS_MSIX_VEC()_CTL, enumerated by TNS_INT_VEC_E.
                                                                 Bits that have no associated TNS_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_msix_pbax_s cn; */
};
typedef union bdk_tns_msix_pbax bdk_tns_msix_pbax_t;

static inline uint64_t BDK_TNS_MSIX_PBAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_MSIX_PBAX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a==0))
        return 0x842000ff0000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("TNS_MSIX_PBAX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_MSIX_PBAX(a) bdk_tns_msix_pbax_t
#define bustype_BDK_TNS_MSIX_PBAX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_MSIX_PBAX(a) "TNS_MSIX_PBAX"
#define device_bar_BDK_TNS_MSIX_PBAX(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_TNS_MSIX_PBAX(a) (a)
#define arguments_BDK_TNS_MSIX_PBAX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_msix_vec#_addr
 *
 * TNS MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the TNS_INT_VEC_E enumeration.
 */
union bdk_tns_msix_vecx_addr
{
    uint64_t u;
    struct bdk_tns_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's TNS_MSIX_VEC()_ADDR, TNS_MSIX_VEC()_CTL, and corresponding
                                                                 bit of TNS_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_TNS_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's TNS_MSIX_VEC()_ADDR, TNS_MSIX_VEC()_CTL, and corresponding
                                                                 bit of TNS_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_TNS_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_msix_vecx_addr_s cn; */
};
typedef union bdk_tns_msix_vecx_addr bdk_tns_msix_vecx_addr_t;

static inline uint64_t BDK_TNS_MSIX_VECX_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_MSIX_VECX_ADDR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x842000f00000ll + 0x10ll * ((a) & 0x3f);
    __bdk_csr_fatal("TNS_MSIX_VECX_ADDR", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_MSIX_VECX_ADDR(a) bdk_tns_msix_vecx_addr_t
#define bustype_BDK_TNS_MSIX_VECX_ADDR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_MSIX_VECX_ADDR(a) "TNS_MSIX_VECX_ADDR"
#define device_bar_BDK_TNS_MSIX_VECX_ADDR(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_TNS_MSIX_VECX_ADDR(a) (a)
#define arguments_BDK_TNS_MSIX_VECX_ADDR(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_msix_vec#_ctl
 *
 * TNS MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the TNS_INT_VEC_E enumeration.
 */
union bdk_tns_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_tns_msix_vecx_ctl_s
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
    } s;
    /* struct bdk_tns_msix_vecx_ctl_s cn; */
};
typedef union bdk_tns_msix_vecx_ctl bdk_tns_msix_vecx_ctl_t;

static inline uint64_t BDK_TNS_MSIX_VECX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_MSIX_VECX_CTL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x842000f00008ll + 0x10ll * ((a) & 0x3f);
    __bdk_csr_fatal("TNS_MSIX_VECX_CTL", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_MSIX_VECX_CTL(a) bdk_tns_msix_vecx_ctl_t
#define bustype_BDK_TNS_MSIX_VECX_CTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_MSIX_VECX_CTL(a) "TNS_MSIX_VECX_CTL"
#define device_bar_BDK_TNS_MSIX_VECX_CTL(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_TNS_MSIX_VECX_CTL(a) (a)
#define arguments_BDK_TNS_MSIX_VECX_CTL(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_pm_rd_acc#
 *
 * INTERNAL: TNS Packet Memory Read Access Registers
 *
 * Provides the ability for software to read the network switch packet memory.
 * The packet memory consists of 49,152 512-bit words.
 * Write access of the packet memory is provided by TNS_PM_WR_ACC.
 */
union bdk_tns_pm_rd_accx
{
    uint64_t u;
    struct bdk_tns_pm_rd_accx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](RO/H) Packet data. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](RO/H) Packet data. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_pm_rd_accx_s cn; */
};
typedef union bdk_tns_pm_rd_accx bdk_tns_pm_rd_accx_t;

static inline uint64_t BDK_TNS_PM_RD_ACCX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_PM_RD_ACCX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=393215))
        return 0x842041800000ll + 0x10ll * ((a) & 0x7ffff);
    __bdk_csr_fatal("TNS_PM_RD_ACCX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_PM_RD_ACCX(a) bdk_tns_pm_rd_accx_t
#define bustype_BDK_TNS_PM_RD_ACCX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_PM_RD_ACCX(a) "TNS_PM_RD_ACCX"
#define device_bar_BDK_TNS_PM_RD_ACCX(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_PM_RD_ACCX(a) (a)
#define arguments_BDK_TNS_PM_RD_ACCX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_pm_wr_acc#
 *
 * INTERNAL: TNS Packet Memory Write Access Registers
 *
 * Provides the ability for software to write the network switch packet memory.
 * The packet memory consists of 49,152 512-bit words.
 * To write data to a piece of a memory word software must write the entire word, 8 bytes at a
 * time,
 * starting with the least significant bits at 0x...00 and incrementing sequentially up
 * to 0x...80.
 * Read access of the packet memory is provided elsewhere.
 */
union bdk_tns_pm_wr_accx
{
    uint64_t u;
    struct bdk_tns_pm_wr_accx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](WO/H) Packet data. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](WO/H) Packet data. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_pm_wr_accx_s cn; */
};
typedef union bdk_tns_pm_wr_accx bdk_tns_pm_wr_accx_t;

static inline uint64_t BDK_TNS_PM_WR_ACCX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_PM_WR_ACCX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=393215))
        return 0x842042800000ll + 0x10ll * ((a) & 0x7ffff);
    __bdk_csr_fatal("TNS_PM_WR_ACCX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_PM_WR_ACCX(a) bdk_tns_pm_wr_accx_t
#define bustype_BDK_TNS_PM_WR_ACCX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_PM_WR_ACCX(a) "TNS_PM_WR_ACCX"
#define device_bar_BDK_TNS_PM_WR_ACCX(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_PM_WR_ACCX(a) (a)
#define arguments_BDK_TNS_PM_WR_ACCX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_rdma_cnt#
 *
 * TNS RDMA Receive Counter Register
 * Packets and bytes received by the physical port.
 * All fields have roll over counters.
 * Register number enumerated by TNS_PHYS_PORT_E.
 */
union bdk_tns_rdma_cntx
{
    uint64_t u;
    struct bdk_tns_rdma_cntx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_60_63        : 4;
        uint64_t bytes                 : 36; /**< [ 59: 24](R/W/H) Packet bytes. */
        uint64_t packets               : 24; /**< [ 23:  0](R/W/H) Packets. */
#else /* Word 0 - Little Endian */
        uint64_t packets               : 24; /**< [ 23:  0](R/W/H) Packets. */
        uint64_t bytes                 : 36; /**< [ 59: 24](R/W/H) Packet bytes. */
        uint64_t reserved_60_63        : 4;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_cntx_s cn; */
};
typedef union bdk_tns_rdma_cntx bdk_tns_rdma_cntx_t;

static inline uint64_t BDK_TNS_RDMA_CNTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_CNTX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=9))
        return 0x842000001500ll + 0x10ll * ((a) & 0xf);
    __bdk_csr_fatal("TNS_RDMA_CNTX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_CNTX(a) bdk_tns_rdma_cntx_t
#define bustype_BDK_TNS_RDMA_CNTX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_CNTX(a) "TNS_RDMA_CNTX"
#define device_bar_BDK_TNS_RDMA_CNTX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_CNTX(a) (a)
#define arguments_BDK_TNS_RDMA_CNTX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_rdma_cnt_bytes#
 *
 * TNS RDMA Receive Byte Counter Register
 * Bytes received by the physical port. All fields have roll over counters. Register
 * number enumerated by TNS_PHYS_PORT_E.
 */
union bdk_tns_rdma_cnt_bytesx
{
    uint64_t u;
    struct bdk_tns_rdma_cnt_bytesx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t bytes                 : 48; /**< [ 47:  0](R/W/H) Packet bytes. */
#else /* Word 0 - Little Endian */
        uint64_t bytes                 : 48; /**< [ 47:  0](R/W/H) Packet bytes. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_cnt_bytesx_s cn; */
};
typedef union bdk_tns_rdma_cnt_bytesx bdk_tns_rdma_cnt_bytesx_t;

static inline uint64_t BDK_TNS_RDMA_CNT_BYTESX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_CNT_BYTESX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X) && (a<=9))
        return 0x842000001480ll + 8ll * ((a) & 0xf);
    __bdk_csr_fatal("TNS_RDMA_CNT_BYTESX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_CNT_BYTESX(a) bdk_tns_rdma_cnt_bytesx_t
#define bustype_BDK_TNS_RDMA_CNT_BYTESX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_CNT_BYTESX(a) "TNS_RDMA_CNT_BYTESX"
#define device_bar_BDK_TNS_RDMA_CNT_BYTESX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_CNT_BYTESX(a) (a)
#define arguments_BDK_TNS_RDMA_CNT_BYTESX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_rdma_cnt_pkts#
 *
 * TNS RDMA Receive Packet Counter Register
 * Packets received by the physical port. All fields have roll over counters. Register
 * number enumerated by TNS_PHYS_PORT_E.
 */
union bdk_tns_rdma_cnt_pktsx
{
    uint64_t u;
    struct bdk_tns_rdma_cnt_pktsx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t packets               : 36; /**< [ 35:  0](R/W/H) Packets. */
#else /* Word 0 - Little Endian */
        uint64_t packets               : 36; /**< [ 35:  0](R/W/H) Packets. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_cnt_pktsx_s cn; */
};
typedef union bdk_tns_rdma_cnt_pktsx bdk_tns_rdma_cnt_pktsx_t;

static inline uint64_t BDK_TNS_RDMA_CNT_PKTSX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_CNT_PKTSX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X) && (a<=9))
        return 0x842000001400ll + 8ll * ((a) & 0xf);
    __bdk_csr_fatal("TNS_RDMA_CNT_PKTSX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_CNT_PKTSX(a) bdk_tns_rdma_cnt_pktsx_t
#define bustype_BDK_TNS_RDMA_CNT_PKTSX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_CNT_PKTSX(a) "TNS_RDMA_CNT_PKTSX"
#define device_bar_BDK_TNS_RDMA_CNT_PKTSX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_CNT_PKTSX(a) (a)
#define arguments_BDK_TNS_RDMA_CNT_PKTSX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_rdma_config
 *
 * TNS RDMA Packet Configuration Register
 */
union bdk_tns_rdma_config
{
    uint64_t u;
    struct bdk_tns_rdma_config_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t lmac_bp_enable        : 2;  /**< [  3:  2](R/W) Enable sending of back pressure information to the LMACs.
                                                                 Bits correspond to {LMACs7..4, LMACs3..0}.

                                                                 Internal:
                                                                 Enables sending of Xon/Xoff back pressure calendar. */
        uint64_t nici_bp_enable        : 2;  /**< [  1:  0](R/W) Enable sending of back pressure information to the NIC Interfaces.
                                                                 Bits correspond to {NICI1, NICI0}.

                                                                 Internal:
                                                                 Enables sending of Xon/Xoff EBP back pressure calendar.
                                                                 Also enables sending of channel credit return messages to NIC Interface. */
#else /* Word 0 - Little Endian */
        uint64_t nici_bp_enable        : 2;  /**< [  1:  0](R/W) Enable sending of back pressure information to the NIC Interfaces.
                                                                 Bits correspond to {NICI1, NICI0}.

                                                                 Internal:
                                                                 Enables sending of Xon/Xoff EBP back pressure calendar.
                                                                 Also enables sending of channel credit return messages to NIC Interface. */
        uint64_t lmac_bp_enable        : 2;  /**< [  3:  2](R/W) Enable sending of back pressure information to the LMACs.
                                                                 Bits correspond to {LMACs7..4, LMACs3..0}.

                                                                 Internal:
                                                                 Enables sending of Xon/Xoff back pressure calendar. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_config_s cn; */
};
typedef union bdk_tns_rdma_config bdk_tns_rdma_config_t;

#define BDK_TNS_RDMA_CONFIG BDK_TNS_RDMA_CONFIG_FUNC()
static inline uint64_t BDK_TNS_RDMA_CONFIG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_CONFIG_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000001200ll;
    __bdk_csr_fatal("TNS_RDMA_CONFIG", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_CONFIG bdk_tns_rdma_config_t
#define bustype_BDK_TNS_RDMA_CONFIG BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_CONFIG "TNS_RDMA_CONFIG"
#define device_bar_BDK_TNS_RDMA_CONFIG 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_CONFIG 0
#define arguments_BDK_TNS_RDMA_CONFIG -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_dbg_cdt_ctl
 *
 * INTERNAL: TNS RDMA Debug Credit Control Register
 *
 * This register provides debug control of packet receipt.
 */
union bdk_tns_rdma_dbg_cdt_ctl
{
    uint64_t u;
    struct bdk_tns_rdma_dbg_cdt_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t nbyp_credits_inc      : 2;  /**< [ 11: 10](WO/H) Each write to this field increments the count of non-bypass credit storage for {BGX1, BGX0}. */
        uint64_t byp_credits_inc       : 2;  /**< [  9:  8](WO/H) Each write to this field increments the count of bypass credit storage for {BGX1, BGX0}. */
        uint64_t pending_req_inc       : 2;  /**< [  7:  6](WO/H) Each write to this field increments the count of pending requests from {BGX1, BGX0}. */
        uint64_t nbyp_credits_dec      : 2;  /**< [  5:  4](WO/H) Each write to this field decrements the count of non-bypass credit storage for {BGX1, BGX0}. */
        uint64_t byp_credits_dec       : 2;  /**< [  3:  2](WO/H) Each write to this field decrements the count of bypass credit storage for {BGX1, BGX0}. */
        uint64_t pending_req_dec       : 2;  /**< [  1:  0](WO/H) Each write to this field decrements the count of pending requests from {BGX1, BGX0}. */
#else /* Word 0 - Little Endian */
        uint64_t pending_req_dec       : 2;  /**< [  1:  0](WO/H) Each write to this field decrements the count of pending requests from {BGX1, BGX0}. */
        uint64_t byp_credits_dec       : 2;  /**< [  3:  2](WO/H) Each write to this field decrements the count of bypass credit storage for {BGX1, BGX0}. */
        uint64_t nbyp_credits_dec      : 2;  /**< [  5:  4](WO/H) Each write to this field decrements the count of non-bypass credit storage for {BGX1, BGX0}. */
        uint64_t pending_req_inc       : 2;  /**< [  7:  6](WO/H) Each write to this field increments the count of pending requests from {BGX1, BGX0}. */
        uint64_t byp_credits_inc       : 2;  /**< [  9:  8](WO/H) Each write to this field increments the count of bypass credit storage for {BGX1, BGX0}. */
        uint64_t nbyp_credits_inc      : 2;  /**< [ 11: 10](WO/H) Each write to this field increments the count of non-bypass credit storage for {BGX1, BGX0}. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_dbg_cdt_ctl_s cn; */
};
typedef union bdk_tns_rdma_dbg_cdt_ctl bdk_tns_rdma_dbg_cdt_ctl_t;

#define BDK_TNS_RDMA_DBG_CDT_CTL BDK_TNS_RDMA_DBG_CDT_CTL_FUNC()
static inline uint64_t BDK_TNS_RDMA_DBG_CDT_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_DBG_CDT_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000001a10ll;
    __bdk_csr_fatal("TNS_RDMA_DBG_CDT_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_DBG_CDT_CTL bdk_tns_rdma_dbg_cdt_ctl_t
#define bustype_BDK_TNS_RDMA_DBG_CDT_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_DBG_CDT_CTL "TNS_RDMA_DBG_CDT_CTL"
#define device_bar_BDK_TNS_RDMA_DBG_CDT_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_DBG_CDT_CTL 0
#define arguments_BDK_TNS_RDMA_DBG_CDT_CTL -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_dbg_cx_full
 *
 * INTERNAL: TNS RDMA Debug CX Full Level Control Register
 *
 * This register provides debug control of FIFO full.
 * Async FIFOs assert an early full indication when occupancies reach the values
 * below.
 */
union bdk_tns_rdma_dbg_cx_full
{
    uint64_t u;
    struct bdk_tns_rdma_dbg_cx_full_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_37_63        : 27;
        uint64_t lmac_rx_ebp           : 5;  /**< [ 36: 32](R/W) EBP back pressure information received from LMACs. */
        uint64_t reserved_29_31        : 3;
        uint64_t lmac_rx_chan_bp       : 5;  /**< [ 28: 24](R/W) Channel credit messages received from LMACs. */
        uint64_t reserved_21_23        : 3;
        uint64_t nic_rx_bp             : 5;  /**< [ 20: 16](R/W) Back pressure received from NIC. */
        uint64_t reserved_13_15        : 3;
        uint64_t lmac_pkt              : 5;  /**< [ 12:  8](R/W) Packet data received from LMACs. */
        uint64_t reserved_5_7          : 3;
        uint64_t nic_pkt               : 5;  /**< [  4:  0](R/W) Packet data received from NIC. */
#else /* Word 0 - Little Endian */
        uint64_t nic_pkt               : 5;  /**< [  4:  0](R/W) Packet data received from NIC. */
        uint64_t reserved_5_7          : 3;
        uint64_t lmac_pkt              : 5;  /**< [ 12:  8](R/W) Packet data received from LMACs. */
        uint64_t reserved_13_15        : 3;
        uint64_t nic_rx_bp             : 5;  /**< [ 20: 16](R/W) Back pressure received from NIC. */
        uint64_t reserved_21_23        : 3;
        uint64_t lmac_rx_chan_bp       : 5;  /**< [ 28: 24](R/W) Channel credit messages received from LMACs. */
        uint64_t reserved_29_31        : 3;
        uint64_t lmac_rx_ebp           : 5;  /**< [ 36: 32](R/W) EBP back pressure information received from LMACs. */
        uint64_t reserved_37_63        : 27;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_dbg_cx_full_s cn; */
};
typedef union bdk_tns_rdma_dbg_cx_full bdk_tns_rdma_dbg_cx_full_t;

#define BDK_TNS_RDMA_DBG_CX_FULL BDK_TNS_RDMA_DBG_CX_FULL_FUNC()
static inline uint64_t BDK_TNS_RDMA_DBG_CX_FULL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_DBG_CX_FULL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000001a20ll;
    __bdk_csr_fatal("TNS_RDMA_DBG_CX_FULL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_DBG_CX_FULL bdk_tns_rdma_dbg_cx_full_t
#define bustype_BDK_TNS_RDMA_DBG_CX_FULL BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_DBG_CX_FULL "TNS_RDMA_DBG_CX_FULL"
#define device_bar_BDK_TNS_RDMA_DBG_CX_FULL 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_DBG_CX_FULL 0
#define arguments_BDK_TNS_RDMA_DBG_CX_FULL -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_dbg_cx_occ
 *
 * INTERNAL: TNS RDMA Debug CX FIFO Occupancy Status Register
 *
 * Async FIFO occupancies.
 */
union bdk_tns_rdma_dbg_cx_occ
{
    uint64_t u;
    struct bdk_tns_rdma_dbg_cx_occ_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_61_63        : 3;
        uint64_t lmac7_4_rx_ebp        : 5;  /**< [ 60: 56](RO/H) EBP received from LMACs 4..7. */
        uint64_t reserved_53_55        : 3;
        uint64_t lmac3_0_rx_ebp        : 5;  /**< [ 52: 48](RO/H) EBP received from LMACs 0..3. */
        uint64_t reserved_45_47        : 3;
        uint64_t lmac7_4_rx_chan_bp    : 5;  /**< [ 44: 40](RO/H) Channel credit messages received from LMACs 4..7. */
        uint64_t reserved_37_39        : 3;
        uint64_t lmac3_0_rx_chan_bp    : 5;  /**< [ 36: 32](RO/H) Channel credit messages received from LMACs 0..3. */
        uint64_t reserved_29_31        : 3;
        uint64_t nici1_rx_bp           : 5;  /**< [ 28: 24](RO/H) Back pressure received from NICI1. */
        uint64_t reserved_21_23        : 3;
        uint64_t nici0_rx_bp           : 5;  /**< [ 20: 16](RO/H) Back pressure received from NICI0. */
        uint64_t reserved_13_15        : 3;
        uint64_t lmac_pkt              : 5;  /**< [ 12:  8](RO/H) Data flits received from LMACs. */
        uint64_t reserved_5_7          : 3;
        uint64_t nic_pkt               : 5;  /**< [  4:  0](RO/H) Data flits received from NIC. */
#else /* Word 0 - Little Endian */
        uint64_t nic_pkt               : 5;  /**< [  4:  0](RO/H) Data flits received from NIC. */
        uint64_t reserved_5_7          : 3;
        uint64_t lmac_pkt              : 5;  /**< [ 12:  8](RO/H) Data flits received from LMACs. */
        uint64_t reserved_13_15        : 3;
        uint64_t nici0_rx_bp           : 5;  /**< [ 20: 16](RO/H) Back pressure received from NICI0. */
        uint64_t reserved_21_23        : 3;
        uint64_t nici1_rx_bp           : 5;  /**< [ 28: 24](RO/H) Back pressure received from NICI1. */
        uint64_t reserved_29_31        : 3;
        uint64_t lmac3_0_rx_chan_bp    : 5;  /**< [ 36: 32](RO/H) Channel credit messages received from LMACs 0..3. */
        uint64_t reserved_37_39        : 3;
        uint64_t lmac7_4_rx_chan_bp    : 5;  /**< [ 44: 40](RO/H) Channel credit messages received from LMACs 4..7. */
        uint64_t reserved_45_47        : 3;
        uint64_t lmac3_0_rx_ebp        : 5;  /**< [ 52: 48](RO/H) EBP received from LMACs 0..3. */
        uint64_t reserved_53_55        : 3;
        uint64_t lmac7_4_rx_ebp        : 5;  /**< [ 60: 56](RO/H) EBP received from LMACs 4..7. */
        uint64_t reserved_61_63        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_dbg_cx_occ_s cn; */
};
typedef union bdk_tns_rdma_dbg_cx_occ bdk_tns_rdma_dbg_cx_occ_t;

#define BDK_TNS_RDMA_DBG_CX_OCC BDK_TNS_RDMA_DBG_CX_OCC_FUNC()
static inline uint64_t BDK_TNS_RDMA_DBG_CX_OCC_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_DBG_CX_OCC_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000001c20ll;
    __bdk_csr_fatal("TNS_RDMA_DBG_CX_OCC", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_DBG_CX_OCC bdk_tns_rdma_dbg_cx_occ_t
#define bustype_BDK_TNS_RDMA_DBG_CX_OCC BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_DBG_CX_OCC "TNS_RDMA_DBG_CX_OCC"
#define device_bar_BDK_TNS_RDMA_DBG_CX_OCC 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_DBG_CX_OCC 0
#define arguments_BDK_TNS_RDMA_DBG_CX_OCC -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_dbg_pkt1_status
 *
 * INTERNAL: TNS RDMA Debug Packet Status Register
 *
 * This register provides debug information of packet receipt status.
 */
union bdk_tns_rdma_dbg_pkt1_status
{
    uint64_t u;
    struct bdk_tns_rdma_dbg_pkt1_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_61_63        : 3;
        uint64_t bgx1_x2p_nbyp_credits : 5;  /**< [ 60: 56](RO/H) BGX1 X2P non-bypass credits.
                                                                 Non-allocated non-bypass FIFO space.
                                                                 Ranges from 0 through 16. */
        uint64_t bgx1_x2p_byp_credits  : 8;  /**< [ 55: 48](RO/H) BGX1 X2P bypass credits.
                                                                 Available bypass FIFO space in the TDMA, as determined by credits in RDMA.
                                                                 Ranges from 0 through 96. */
        uint64_t reserved_45_47        : 3;
        uint64_t bgx1_x2p_req_pending  : 5;  /**< [ 44: 40](RO/H) BGX1 X2P pending requests.
                                                                 X2P requests received that have not yet been granted.
                                                                 Ranges from 0 through 16. */
        uint64_t reserved_37_39        : 3;
        uint64_t bgx1_x2p_fifo_occ     : 5;  /**< [ 36: 32](RO/H) Non-bypass BGX1 X2P packet FIFO occupancy.
                                                                 Ranges from 0 through 16. */
        uint64_t reserved_29_31        : 3;
        uint64_t bgx0_x2p_nbyp_credits : 5;  /**< [ 28: 24](RO/H) BGX0 X2P non-bypass credits.
                                                                 Non-allocated non-bypass FIFO space.
                                                                 Ranges from 0 through 16. */
        uint64_t bgx0_x2p_byp_credits  : 8;  /**< [ 23: 16](RO/H) BGX0 X2P bypass credits.
                                                                 Available bypass FIFO space in the TDMA, as determined by credits in RDMA.
                                                                 Ranges from 0 through 96. */
        uint64_t reserved_13_15        : 3;
        uint64_t bgx0_x2p_req_pending  : 5;  /**< [ 12:  8](RO/H) BGX0 X2P pending requests.
                                                                 X2P requests received that have not yet been granted.
                                                                 Ranges from 0 through 16. */
        uint64_t reserved_5_7          : 3;
        uint64_t bgx0_x2p_fifo_occ     : 5;  /**< [  4:  0](RO/H) Non-bypass BGX0 X2P packet FIFO occupancy.
                                                                 Ranges from 0 through 16. */
#else /* Word 0 - Little Endian */
        uint64_t bgx0_x2p_fifo_occ     : 5;  /**< [  4:  0](RO/H) Non-bypass BGX0 X2P packet FIFO occupancy.
                                                                 Ranges from 0 through 16. */
        uint64_t reserved_5_7          : 3;
        uint64_t bgx0_x2p_req_pending  : 5;  /**< [ 12:  8](RO/H) BGX0 X2P pending requests.
                                                                 X2P requests received that have not yet been granted.
                                                                 Ranges from 0 through 16. */
        uint64_t reserved_13_15        : 3;
        uint64_t bgx0_x2p_byp_credits  : 8;  /**< [ 23: 16](RO/H) BGX0 X2P bypass credits.
                                                                 Available bypass FIFO space in the TDMA, as determined by credits in RDMA.
                                                                 Ranges from 0 through 96. */
        uint64_t bgx0_x2p_nbyp_credits : 5;  /**< [ 28: 24](RO/H) BGX0 X2P non-bypass credits.
                                                                 Non-allocated non-bypass FIFO space.
                                                                 Ranges from 0 through 16. */
        uint64_t reserved_29_31        : 3;
        uint64_t bgx1_x2p_fifo_occ     : 5;  /**< [ 36: 32](RO/H) Non-bypass BGX1 X2P packet FIFO occupancy.
                                                                 Ranges from 0 through 16. */
        uint64_t reserved_37_39        : 3;
        uint64_t bgx1_x2p_req_pending  : 5;  /**< [ 44: 40](RO/H) BGX1 X2P pending requests.
                                                                 X2P requests received that have not yet been granted.
                                                                 Ranges from 0 through 16. */
        uint64_t reserved_45_47        : 3;
        uint64_t bgx1_x2p_byp_credits  : 8;  /**< [ 55: 48](RO/H) BGX1 X2P bypass credits.
                                                                 Available bypass FIFO space in the TDMA, as determined by credits in RDMA.
                                                                 Ranges from 0 through 96. */
        uint64_t bgx1_x2p_nbyp_credits : 5;  /**< [ 60: 56](RO/H) BGX1 X2P non-bypass credits.
                                                                 Non-allocated non-bypass FIFO space.
                                                                 Ranges from 0 through 16. */
        uint64_t reserved_61_63        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_dbg_pkt1_status_s cn; */
};
typedef union bdk_tns_rdma_dbg_pkt1_status bdk_tns_rdma_dbg_pkt1_status_t;

#define BDK_TNS_RDMA_DBG_PKT1_STATUS BDK_TNS_RDMA_DBG_PKT1_STATUS_FUNC()
static inline uint64_t BDK_TNS_RDMA_DBG_PKT1_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_DBG_PKT1_STATUS_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000001c00ll;
    __bdk_csr_fatal("TNS_RDMA_DBG_PKT1_STATUS", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_DBG_PKT1_STATUS bdk_tns_rdma_dbg_pkt1_status_t
#define bustype_BDK_TNS_RDMA_DBG_PKT1_STATUS BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_DBG_PKT1_STATUS "TNS_RDMA_DBG_PKT1_STATUS"
#define device_bar_BDK_TNS_RDMA_DBG_PKT1_STATUS 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_DBG_PKT1_STATUS 0
#define arguments_BDK_TNS_RDMA_DBG_PKT1_STATUS -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_dbg_pkt2_status
 *
 * INTERNAL: TNS RDMA Debug Packet Status Register
 *
 * This register provides debug information of packet receipt status.
 */
union bdk_tns_rdma_dbg_pkt2_status
{
    uint64_t u;
    struct bdk_tns_rdma_dbg_pkt2_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t nic_p2x_fifo_occ      : 6;  /**< [  5:  0](RO/H) Non-bypass NIC P2X packet FIFO occupancy. */
#else /* Word 0 - Little Endian */
        uint64_t nic_p2x_fifo_occ      : 6;  /**< [  5:  0](RO/H) Non-bypass NIC P2X packet FIFO occupancy. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_dbg_pkt2_status_s cn; */
};
typedef union bdk_tns_rdma_dbg_pkt2_status bdk_tns_rdma_dbg_pkt2_status_t;

#define BDK_TNS_RDMA_DBG_PKT2_STATUS BDK_TNS_RDMA_DBG_PKT2_STATUS_FUNC()
static inline uint64_t BDK_TNS_RDMA_DBG_PKT2_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_DBG_PKT2_STATUS_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000001c10ll;
    __bdk_csr_fatal("TNS_RDMA_DBG_PKT2_STATUS", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_DBG_PKT2_STATUS bdk_tns_rdma_dbg_pkt2_status_t
#define bustype_BDK_TNS_RDMA_DBG_PKT2_STATUS BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_DBG_PKT2_STATUS "TNS_RDMA_DBG_PKT2_STATUS"
#define device_bar_BDK_TNS_RDMA_DBG_PKT2_STATUS 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_DBG_PKT2_STATUS 0
#define arguments_BDK_TNS_RDMA_DBG_PKT2_STATUS -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_dbg_pkt_ctl
 *
 * INTERNAL: TNS RDMA Debug Packet Control Register
 *
 * This register provides debug control of packet receipt.
 */
union bdk_tns_rdma_dbg_pkt_ctl
{
    uint64_t u;
    struct bdk_tns_rdma_dbg_pkt_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t rtn_nici_cdt          : 2;  /**< [  1:  0](WO/H) Each write to this field returns 1 packet skid credit to {NICI1, NICI0}. */
#else /* Word 0 - Little Endian */
        uint64_t rtn_nici_cdt          : 2;  /**< [  1:  0](WO/H) Each write to this field returns 1 packet skid credit to {NICI1, NICI0}. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_dbg_pkt_ctl_s cn; */
};
typedef union bdk_tns_rdma_dbg_pkt_ctl bdk_tns_rdma_dbg_pkt_ctl_t;

#define BDK_TNS_RDMA_DBG_PKT_CTL BDK_TNS_RDMA_DBG_PKT_CTL_FUNC()
static inline uint64_t BDK_TNS_RDMA_DBG_PKT_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_DBG_PKT_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000001a00ll;
    __bdk_csr_fatal("TNS_RDMA_DBG_PKT_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_DBG_PKT_CTL bdk_tns_rdma_dbg_pkt_ctl_t
#define bustype_BDK_TNS_RDMA_DBG_PKT_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_DBG_PKT_CTL "TNS_RDMA_DBG_PKT_CTL"
#define device_bar_BDK_TNS_RDMA_DBG_PKT_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_DBG_PKT_CTL 0
#define arguments_BDK_TNS_RDMA_DBG_PKT_CTL -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_dbgb_sel
 *
 * INTERNAL: TNS RDMA Debug Bus Select Register
 *
 * Debug bus select register.
 * This register is only used in pass 1.x.
 */
union bdk_tns_rdma_dbgb_sel
{
    uint64_t u;
    struct bdk_tns_rdma_dbgb_sel_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t sel1                  : 24; /**< [ 47: 24](R/W) Select group for upper debug bus bits */
        uint64_t sel0                  : 24; /**< [ 23:  0](R/W) Select group for lower debug bus bits */
#else /* Word 0 - Little Endian */
        uint64_t sel0                  : 24; /**< [ 23:  0](R/W) Select group for lower debug bus bits */
        uint64_t sel1                  : 24; /**< [ 47: 24](R/W) Select group for upper debug bus bits */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_dbgb_sel_s cn; */
};
typedef union bdk_tns_rdma_dbgb_sel bdk_tns_rdma_dbgb_sel_t;

#define BDK_TNS_RDMA_DBGB_SEL BDK_TNS_RDMA_DBGB_SEL_FUNC()
static inline uint64_t BDK_TNS_RDMA_DBGB_SEL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_DBGB_SEL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS1_X))
        return 0x842000001e00ll;
    __bdk_csr_fatal("TNS_RDMA_DBGB_SEL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_DBGB_SEL bdk_tns_rdma_dbgb_sel_t
#define bustype_BDK_TNS_RDMA_DBGB_SEL BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_DBGB_SEL "TNS_RDMA_DBGB_SEL"
#define device_bar_BDK_TNS_RDMA_DBGB_SEL 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_DBGB_SEL 0
#define arguments_BDK_TNS_RDMA_DBGB_SEL -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_ecc_ctl
 *
 * TNS RDMA ECC Control Register
 * This register can be used to disable ECC data correction, insert ECC errors.
 * Fields *ECC_DIS disable SBE data correction. If ECC_DIS is 0x1, then no data correction is
 * performed but errors will still be reported.
 * Fields *ECC_FLIP_SYND flip the syndrome\<1:0\> bits to generate 1-bit/2-bit error for testing.
 * * 0x0 = normal operation.
 * * 0x1 = SBE on bit\<0\>.
 * * 0x2 = SBE on bit\<1\>.
 * * 0x3 = DBE on bits\<1:0\>.
 */
union bdk_tns_rdma_ecc_ctl
{
    uint64_t u;
    struct bdk_tns_rdma_ecc_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_35_63        : 29;
        uint64_t b_x2p_ecc_dis         : 2;  /**< [ 34: 33](R/W) Disable ECC data correction for B_X2P[1..0] RAM. */
        uint64_t b_p2x_ecc_dis         : 1;  /**< [ 32: 32](R/W) Disable ECC data correction for B_P2X RAM. */
        uint64_t reserved_6_31         : 26;
        uint64_t b_x2p1_ecc_flip_synd  : 2;  /**< [  5:  4](R/W) Flip syndrome for all data written to B_X2P1 RAM. */
        uint64_t b_x2p0_ecc_flip_synd  : 2;  /**< [  3:  2](R/W) Flip syndrome for all data written to B_X2P0 RAM. */
        uint64_t b_p2x_ecc_flip_synd   : 2;  /**< [  1:  0](R/W) Flip syndrome for all data written to B_P2X RAM. */
#else /* Word 0 - Little Endian */
        uint64_t b_p2x_ecc_flip_synd   : 2;  /**< [  1:  0](R/W) Flip syndrome for all data written to B_P2X RAM. */
        uint64_t b_x2p0_ecc_flip_synd  : 2;  /**< [  3:  2](R/W) Flip syndrome for all data written to B_X2P0 RAM. */
        uint64_t b_x2p1_ecc_flip_synd  : 2;  /**< [  5:  4](R/W) Flip syndrome for all data written to B_X2P1 RAM. */
        uint64_t reserved_6_31         : 26;
        uint64_t b_p2x_ecc_dis         : 1;  /**< [ 32: 32](R/W) Disable ECC data correction for B_P2X RAM. */
        uint64_t b_x2p_ecc_dis         : 2;  /**< [ 34: 33](R/W) Disable ECC data correction for B_X2P[1..0] RAM. */
        uint64_t reserved_35_63        : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_ecc_ctl_s cn; */
};
typedef union bdk_tns_rdma_ecc_ctl bdk_tns_rdma_ecc_ctl_t;

#define BDK_TNS_RDMA_ECC_CTL BDK_TNS_RDMA_ECC_CTL_FUNC()
static inline uint64_t BDK_TNS_RDMA_ECC_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_ECC_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000001800ll;
    __bdk_csr_fatal("TNS_RDMA_ECC_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_ECC_CTL bdk_tns_rdma_ecc_ctl_t
#define bustype_BDK_TNS_RDMA_ECC_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_ECC_CTL "TNS_RDMA_ECC_CTL"
#define device_bar_BDK_TNS_RDMA_ECC_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_ECC_CTL 0
#define arguments_BDK_TNS_RDMA_ECC_CTL -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_ecc_err_stat
 *
 * TNS RDMA ECC Error Status Register
 * This register logs information to help debug ECC errors.
 */
union bdk_tns_rdma_ecc_err_stat
{
    uint64_t u;
    struct bdk_tns_rdma_ecc_err_stat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t syndrome              : 9;  /**< [ 16:  8](RO/H) Error syndrome. */
        uint64_t reserved_5_7          : 3;
        uint64_t address               : 5;  /**< [  4:  0](RO/H) Address of ECC error. */
#else /* Word 0 - Little Endian */
        uint64_t address               : 5;  /**< [  4:  0](RO/H) Address of ECC error. */
        uint64_t reserved_5_7          : 3;
        uint64_t syndrome              : 9;  /**< [ 16:  8](RO/H) Error syndrome. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_ecc_err_stat_s cn; */
};
typedef union bdk_tns_rdma_ecc_err_stat bdk_tns_rdma_ecc_err_stat_t;

#define BDK_TNS_RDMA_ECC_ERR_STAT BDK_TNS_RDMA_ECC_ERR_STAT_FUNC()
static inline uint64_t BDK_TNS_RDMA_ECC_ERR_STAT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_ECC_ERR_STAT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000001810ll;
    __bdk_csr_fatal("TNS_RDMA_ECC_ERR_STAT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_ECC_ERR_STAT bdk_tns_rdma_ecc_err_stat_t
#define bustype_BDK_TNS_RDMA_ECC_ERR_STAT BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_ECC_ERR_STAT "TNS_RDMA_ECC_ERR_STAT"
#define device_bar_BDK_TNS_RDMA_ECC_ERR_STAT 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_ECC_ERR_STAT 0
#define arguments_BDK_TNS_RDMA_ECC_ERR_STAT -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_eco
 *
 * INTERNAL: TNS RDMA ECO Register
 *
 * ECO register.
 */
union bdk_tns_rdma_eco
{
    uint64_t u;
    struct bdk_tns_rdma_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t rst1                  : 8;  /**< [ 15:  8](R/W) Reset to 1 spare bits */
        uint64_t rst0                  : 8;  /**< [  7:  0](R/W) Reset to 0 spare bits */
#else /* Word 0 - Little Endian */
        uint64_t rst0                  : 8;  /**< [  7:  0](R/W) Reset to 0 spare bits */
        uint64_t rst1                  : 8;  /**< [ 15:  8](R/W) Reset to 1 spare bits */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_eco_s cn; */
};
typedef union bdk_tns_rdma_eco bdk_tns_rdma_eco_t;

#define BDK_TNS_RDMA_ECO BDK_TNS_RDMA_ECO_FUNC()
static inline uint64_t BDK_TNS_RDMA_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_ECO_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000001f00ll;
    __bdk_csr_fatal("TNS_RDMA_ECO", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_ECO bdk_tns_rdma_eco_t
#define bustype_BDK_TNS_RDMA_ECO BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_ECO "TNS_RDMA_ECO"
#define device_bar_BDK_TNS_RDMA_ECO 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_ECO 0
#define arguments_BDK_TNS_RDMA_ECO -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_hdr_ts_cfg
 *
 * TNS RDMA Packet Header Timestamp Configuration Register
 */
union bdk_tns_rdma_hdr_ts_cfg
{
    uint64_t u;
    struct bdk_tns_rdma_hdr_ts_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t lmac                  : 8;  /**< [  7:  0](R/W) This field is used to indicate that all packets arriving on a LMAC port
                                                                 are prepended with an 8-byte timestamp that must be extracted.
                                                                 If enabled, timestamp bytes received from the LMAC are not counted as part of the packet
                                                                 header.
                                                                 Each bit corresponds to 1 LMAC.
                                                                 For each bit, when set the first 8 bytes of every packet received from the LMAC
                                                                 will be interpreted as timestamp information.
                                                                 The extraction occurs blindly, assuming all packets have a timestamp.
                                                                 Unpredictable behavior may occur if software changes the timestamp configuration
                                                                 for a port while packets are being received.
                                                                 Unpredictable behavior may occur if timestamp extraction is enabled and a packet
                                                                 is received on the port without a prepended timestamp. */
#else /* Word 0 - Little Endian */
        uint64_t lmac                  : 8;  /**< [  7:  0](R/W) This field is used to indicate that all packets arriving on a LMAC port
                                                                 are prepended with an 8-byte timestamp that must be extracted.
                                                                 If enabled, timestamp bytes received from the LMAC are not counted as part of the packet
                                                                 header.
                                                                 Each bit corresponds to 1 LMAC.
                                                                 For each bit, when set the first 8 bytes of every packet received from the LMAC
                                                                 will be interpreted as timestamp information.
                                                                 The extraction occurs blindly, assuming all packets have a timestamp.
                                                                 Unpredictable behavior may occur if software changes the timestamp configuration
                                                                 for a port while packets are being received.
                                                                 Unpredictable behavior may occur if timestamp extraction is enabled and a packet
                                                                 is received on the port without a prepended timestamp. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_hdr_ts_cfg_s cn; */
};
typedef union bdk_tns_rdma_hdr_ts_cfg bdk_tns_rdma_hdr_ts_cfg_t;

#define BDK_TNS_RDMA_HDR_TS_CFG BDK_TNS_RDMA_HDR_TS_CFG_FUNC()
static inline uint64_t BDK_TNS_RDMA_HDR_TS_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_HDR_TS_CFG_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000001210ll;
    __bdk_csr_fatal("TNS_RDMA_HDR_TS_CFG", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_HDR_TS_CFG bdk_tns_rdma_hdr_ts_cfg_t
#define bustype_BDK_TNS_RDMA_HDR_TS_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_HDR_TS_CFG "TNS_RDMA_HDR_TS_CFG"
#define device_bar_BDK_TNS_RDMA_HDR_TS_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_HDR_TS_CFG 0
#define arguments_BDK_TNS_RDMA_HDR_TS_CFG -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_int_en_w1c
 *
 * TNS RDMA Interrupt Enable (Read/Write-1-Clear) Register
 * RDMA Interrupt Enable Register.
 */
union bdk_tns_rdma_int_en_w1c
{
    uint64_t u;
    struct bdk_tns_rdma_int_en_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t lmac_unex_data        : 8;  /**< [ 31: 24](R/W1C) Unexpected data from LMAC. Data was received before an SOP flag was received. The data was dropped. */
        uint64_t lmac_unex_sop         : 8;  /**< [ 23: 16](R/W1C) Unexpected SOP from LMAC An SOP was received while a packet is already being received. The
                                                                 in-progress packet and the new packet initiated by the SOP were dropped. */
        uint64_t lmac_srunt            : 8;  /**< [ 15:  8](R/W1C) A packet was received from the LMAC which did not meet framing requirements for minimum size. */
        uint64_t reserved_7            : 1;
        uint64_t b_x2p_dbe             : 2;  /**< [  6:  5](R/W1C) Double-bit ECC error detected on B_X2P[1..0] RAM */
        uint64_t b_p2x_dbe             : 1;  /**< [  4:  4](R/W1C) Double-bit ECC error detected on B_P2X RAM. */
        uint64_t reserved_3            : 1;
        uint64_t b_x2p_sbe             : 2;  /**< [  2:  1](R/W1C) Single-bit ECC error detected on B_X2P[1..0] RAM */
        uint64_t b_p2x_sbe             : 1;  /**< [  0:  0](R/W1C) Single-bit ECC error detected on B_P2X RAM. */
#else /* Word 0 - Little Endian */
        uint64_t b_p2x_sbe             : 1;  /**< [  0:  0](R/W1C) Single-bit ECC error detected on B_P2X RAM. */
        uint64_t b_x2p_sbe             : 2;  /**< [  2:  1](R/W1C) Single-bit ECC error detected on B_X2P[1..0] RAM */
        uint64_t reserved_3            : 1;
        uint64_t b_p2x_dbe             : 1;  /**< [  4:  4](R/W1C) Double-bit ECC error detected on B_P2X RAM. */
        uint64_t b_x2p_dbe             : 2;  /**< [  6:  5](R/W1C) Double-bit ECC error detected on B_X2P[1..0] RAM */
        uint64_t reserved_7            : 1;
        uint64_t lmac_srunt            : 8;  /**< [ 15:  8](R/W1C) A packet was received from the LMAC which did not meet framing requirements for minimum size. */
        uint64_t lmac_unex_sop         : 8;  /**< [ 23: 16](R/W1C) Unexpected SOP from LMAC An SOP was received while a packet is already being received. The
                                                                 in-progress packet and the new packet initiated by the SOP were dropped. */
        uint64_t lmac_unex_data        : 8;  /**< [ 31: 24](R/W1C) Unexpected data from LMAC. Data was received before an SOP flag was received. The data was dropped. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_int_en_w1c_s cn; */
};
typedef union bdk_tns_rdma_int_en_w1c bdk_tns_rdma_int_en_w1c_t;

#define BDK_TNS_RDMA_INT_EN_W1C BDK_TNS_RDMA_INT_EN_W1C_FUNC()
static inline uint64_t BDK_TNS_RDMA_INT_EN_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_INT_EN_W1C_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000001130ll;
    __bdk_csr_fatal("TNS_RDMA_INT_EN_W1C", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_INT_EN_W1C bdk_tns_rdma_int_en_w1c_t
#define bustype_BDK_TNS_RDMA_INT_EN_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_INT_EN_W1C "TNS_RDMA_INT_EN_W1C"
#define device_bar_BDK_TNS_RDMA_INT_EN_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_INT_EN_W1C 0
#define arguments_BDK_TNS_RDMA_INT_EN_W1C -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_int_en_w1s
 *
 * TNS RDMA Interrupt Enable (Read/Write-1-Set) Register
 * RDMA Interrupt Enable Register.
 */
union bdk_tns_rdma_int_en_w1s
{
    uint64_t u;
    struct bdk_tns_rdma_int_en_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t lmac_unex_data        : 8;  /**< [ 31: 24](R/W1S) Unexpected data from LMAC. Data was received before an SOP flag was received. The data was dropped. */
        uint64_t lmac_unex_sop         : 8;  /**< [ 23: 16](R/W1S) Unexpected SOP from LMAC An SOP was received while a packet is already being received. The
                                                                 in-progress packet and the new packet initiated by the SOP were dropped. */
        uint64_t lmac_srunt            : 8;  /**< [ 15:  8](R/W1S) A packet was received from the LMAC which did not meet framing requirements for minimum size. */
        uint64_t reserved_7            : 1;
        uint64_t b_x2p_dbe             : 2;  /**< [  6:  5](R/W1S) Double-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t b_p2x_dbe             : 1;  /**< [  4:  4](R/W1S) Double-bit ECC error detected on B_P2X RAM. */
        uint64_t reserved_3            : 1;
        uint64_t b_x2p_sbe             : 2;  /**< [  2:  1](R/W1S) Single-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t b_p2x_sbe             : 1;  /**< [  0:  0](R/W1S) Single-bit ECC error detected on B_P2X RAM. */
#else /* Word 0 - Little Endian */
        uint64_t b_p2x_sbe             : 1;  /**< [  0:  0](R/W1S) Single-bit ECC error detected on B_P2X RAM. */
        uint64_t b_x2p_sbe             : 2;  /**< [  2:  1](R/W1S) Single-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t reserved_3            : 1;
        uint64_t b_p2x_dbe             : 1;  /**< [  4:  4](R/W1S) Double-bit ECC error detected on B_P2X RAM. */
        uint64_t b_x2p_dbe             : 2;  /**< [  6:  5](R/W1S) Double-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t reserved_7            : 1;
        uint64_t lmac_srunt            : 8;  /**< [ 15:  8](R/W1S) A packet was received from the LMAC which did not meet framing requirements for minimum size. */
        uint64_t lmac_unex_sop         : 8;  /**< [ 23: 16](R/W1S) Unexpected SOP from LMAC An SOP was received while a packet is already being received. The
                                                                 in-progress packet and the new packet initiated by the SOP were dropped. */
        uint64_t lmac_unex_data        : 8;  /**< [ 31: 24](R/W1S) Unexpected data from LMAC. Data was received before an SOP flag was received. The data was dropped. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_int_en_w1s_s cn; */
};
typedef union bdk_tns_rdma_int_en_w1s bdk_tns_rdma_int_en_w1s_t;

#define BDK_TNS_RDMA_INT_EN_W1S BDK_TNS_RDMA_INT_EN_W1S_FUNC()
static inline uint64_t BDK_TNS_RDMA_INT_EN_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_INT_EN_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000001120ll;
    __bdk_csr_fatal("TNS_RDMA_INT_EN_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_INT_EN_W1S bdk_tns_rdma_int_en_w1s_t
#define bustype_BDK_TNS_RDMA_INT_EN_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_INT_EN_W1S "TNS_RDMA_INT_EN_W1S"
#define device_bar_BDK_TNS_RDMA_INT_EN_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_INT_EN_W1S 0
#define arguments_BDK_TNS_RDMA_INT_EN_W1S -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_int_fen_w1c
 *
 * TNS RDMA Interrupt First Enable (Read/Write-1-Clear) Register
 * RDMA Interrupt First Enable Register.
 */
union bdk_tns_rdma_int_fen_w1c
{
    uint64_t u;
    struct bdk_tns_rdma_int_fen_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t lmac_unex_data        : 8;  /**< [ 31: 24](R/W1C) Unexpected data from LMAC. Data was received before an SOP flag was received. The data was dropped. */
        uint64_t lmac_unex_sop         : 8;  /**< [ 23: 16](R/W1C) Unexpected SOP from LMAC An SOP was received while a packet is already being received. The
                                                                 in-progress packet and the new packet initiated by the SOP were dropped. */
        uint64_t lmac_srunt            : 8;  /**< [ 15:  8](R/W1C) A packet was received from the LMAC which did not meet framing requirements for minimum size. */
        uint64_t reserved_7            : 1;
        uint64_t b_x2p_dbe             : 2;  /**< [  6:  5](R/W1C) Double-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t b_p2x_dbe             : 1;  /**< [  4:  4](R/W1C) Double-bit ECC error detected on B_P2X RAM. */
        uint64_t reserved_3            : 1;
        uint64_t b_x2p_sbe             : 2;  /**< [  2:  1](R/W1C) Single-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t b_p2x_sbe             : 1;  /**< [  0:  0](R/W1C) Single-bit ECC error detected on B_P2X RAM. */
#else /* Word 0 - Little Endian */
        uint64_t b_p2x_sbe             : 1;  /**< [  0:  0](R/W1C) Single-bit ECC error detected on B_P2X RAM. */
        uint64_t b_x2p_sbe             : 2;  /**< [  2:  1](R/W1C) Single-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t reserved_3            : 1;
        uint64_t b_p2x_dbe             : 1;  /**< [  4:  4](R/W1C) Double-bit ECC error detected on B_P2X RAM. */
        uint64_t b_x2p_dbe             : 2;  /**< [  6:  5](R/W1C) Double-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t reserved_7            : 1;
        uint64_t lmac_srunt            : 8;  /**< [ 15:  8](R/W1C) A packet was received from the LMAC which did not meet framing requirements for minimum size. */
        uint64_t lmac_unex_sop         : 8;  /**< [ 23: 16](R/W1C) Unexpected SOP from LMAC An SOP was received while a packet is already being received. The
                                                                 in-progress packet and the new packet initiated by the SOP were dropped. */
        uint64_t lmac_unex_data        : 8;  /**< [ 31: 24](R/W1C) Unexpected data from LMAC. Data was received before an SOP flag was received. The data was dropped. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_int_fen_w1c_s cn; */
};
typedef union bdk_tns_rdma_int_fen_w1c bdk_tns_rdma_int_fen_w1c_t;

#define BDK_TNS_RDMA_INT_FEN_W1C BDK_TNS_RDMA_INT_FEN_W1C_FUNC()
static inline uint64_t BDK_TNS_RDMA_INT_FEN_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_INT_FEN_W1C_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000001160ll;
    __bdk_csr_fatal("TNS_RDMA_INT_FEN_W1C", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_INT_FEN_W1C bdk_tns_rdma_int_fen_w1c_t
#define bustype_BDK_TNS_RDMA_INT_FEN_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_INT_FEN_W1C "TNS_RDMA_INT_FEN_W1C"
#define device_bar_BDK_TNS_RDMA_INT_FEN_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_INT_FEN_W1C 0
#define arguments_BDK_TNS_RDMA_INT_FEN_W1C -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_int_fen_w1s
 *
 * TNS RDMA Interrupt First Enable (Read/Write-1-Set) Register
 * RDMA Interrupt First Enable Register.
 */
union bdk_tns_rdma_int_fen_w1s
{
    uint64_t u;
    struct bdk_tns_rdma_int_fen_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t lmac_unex_data        : 8;  /**< [ 31: 24](R/W1S) Unexpected data from LMAC. Data was received before an SOP flag was received. The data was dropped. */
        uint64_t lmac_unex_sop         : 8;  /**< [ 23: 16](R/W1S) Unexpected SOP from LMAC An SOP was received while a packet is already being received. The
                                                                 in-progress packet and the new packet initiated by the SOP were dropped. */
        uint64_t lmac_srunt            : 8;  /**< [ 15:  8](R/W1S) A packet was received from the LMAC which did not meet framing requirements for minimum size. */
        uint64_t reserved_7            : 1;
        uint64_t b_x2p_dbe             : 2;  /**< [  6:  5](R/W1S) Double-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t b_p2x_dbe             : 1;  /**< [  4:  4](R/W1S) Double-bit ECC error detected on B_P2X RAM. */
        uint64_t reserved_3            : 1;
        uint64_t b_x2p_sbe             : 2;  /**< [  2:  1](R/W1S) Single-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t b_p2x_sbe             : 1;  /**< [  0:  0](R/W1S) Single-bit ECC error detected on B_P2X RAM. */
#else /* Word 0 - Little Endian */
        uint64_t b_p2x_sbe             : 1;  /**< [  0:  0](R/W1S) Single-bit ECC error detected on B_P2X RAM. */
        uint64_t b_x2p_sbe             : 2;  /**< [  2:  1](R/W1S) Single-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t reserved_3            : 1;
        uint64_t b_p2x_dbe             : 1;  /**< [  4:  4](R/W1S) Double-bit ECC error detected on B_P2X RAM. */
        uint64_t b_x2p_dbe             : 2;  /**< [  6:  5](R/W1S) Double-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t reserved_7            : 1;
        uint64_t lmac_srunt            : 8;  /**< [ 15:  8](R/W1S) A packet was received from the LMAC which did not meet framing requirements for minimum size. */
        uint64_t lmac_unex_sop         : 8;  /**< [ 23: 16](R/W1S) Unexpected SOP from LMAC An SOP was received while a packet is already being received. The
                                                                 in-progress packet and the new packet initiated by the SOP were dropped. */
        uint64_t lmac_unex_data        : 8;  /**< [ 31: 24](R/W1S) Unexpected data from LMAC. Data was received before an SOP flag was received. The data was dropped. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_int_fen_w1s_s cn; */
};
typedef union bdk_tns_rdma_int_fen_w1s bdk_tns_rdma_int_fen_w1s_t;

#define BDK_TNS_RDMA_INT_FEN_W1S BDK_TNS_RDMA_INT_FEN_W1S_FUNC()
static inline uint64_t BDK_TNS_RDMA_INT_FEN_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_INT_FEN_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000001150ll;
    __bdk_csr_fatal("TNS_RDMA_INT_FEN_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_INT_FEN_W1S bdk_tns_rdma_int_fen_w1s_t
#define bustype_BDK_TNS_RDMA_INT_FEN_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_INT_FEN_W1S "TNS_RDMA_INT_FEN_W1S"
#define device_bar_BDK_TNS_RDMA_INT_FEN_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_INT_FEN_W1S 0
#define arguments_BDK_TNS_RDMA_INT_FEN_W1S -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_int_fstat
 *
 * TNS RDMA Interrupt First Status Register
 * RDMA Interrupt First Status Register.
 * Indicates which interrupt asserted first.
 * This register holds its nonzero value until all TNS_RDMA_INT_STAT_W1S register bits,
 * as enabled by TNS_RDMA_INT_FIRST_EN_W1S, are cleared to 0x0.
 */
union bdk_tns_rdma_int_fstat
{
    uint64_t u;
    struct bdk_tns_rdma_int_fstat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t lmac_unex_data        : 8;  /**< [ 31: 24](RO/H) Unexpected data from LMAC. Data was received before an SOP flag was received. The data was dropped. */
        uint64_t lmac_unex_sop         : 8;  /**< [ 23: 16](RO/H) Unexpected SOP from LMAC An SOP was received while a packet is already being received. The
                                                                 in-progress packet and the new packet initiated by the SOP were dropped. */
        uint64_t lmac_srunt            : 8;  /**< [ 15:  8](RO/H) A packet was received from the LMAC which did not meet framing requirements for minimum size. */
        uint64_t reserved_7            : 1;
        uint64_t b_x2p_dbe             : 2;  /**< [  6:  5](RO/H) Double-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t b_p2x_dbe             : 1;  /**< [  4:  4](RO/H) Double-bit ECC error detected on B_P2X RAM. */
        uint64_t reserved_3            : 1;
        uint64_t b_x2p_sbe             : 2;  /**< [  2:  1](RO/H) Single-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t b_p2x_sbe             : 1;  /**< [  0:  0](RO/H) Single-bit ECC error detected on B_P2X RAM. */
#else /* Word 0 - Little Endian */
        uint64_t b_p2x_sbe             : 1;  /**< [  0:  0](RO/H) Single-bit ECC error detected on B_P2X RAM. */
        uint64_t b_x2p_sbe             : 2;  /**< [  2:  1](RO/H) Single-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t reserved_3            : 1;
        uint64_t b_p2x_dbe             : 1;  /**< [  4:  4](RO/H) Double-bit ECC error detected on B_P2X RAM. */
        uint64_t b_x2p_dbe             : 2;  /**< [  6:  5](RO/H) Double-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t reserved_7            : 1;
        uint64_t lmac_srunt            : 8;  /**< [ 15:  8](RO/H) A packet was received from the LMAC which did not meet framing requirements for minimum size. */
        uint64_t lmac_unex_sop         : 8;  /**< [ 23: 16](RO/H) Unexpected SOP from LMAC An SOP was received while a packet is already being received. The
                                                                 in-progress packet and the new packet initiated by the SOP were dropped. */
        uint64_t lmac_unex_data        : 8;  /**< [ 31: 24](RO/H) Unexpected data from LMAC. Data was received before an SOP flag was received. The data was dropped. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_int_fstat_s cn; */
};
typedef union bdk_tns_rdma_int_fstat bdk_tns_rdma_int_fstat_t;

#define BDK_TNS_RDMA_INT_FSTAT BDK_TNS_RDMA_INT_FSTAT_FUNC()
static inline uint64_t BDK_TNS_RDMA_INT_FSTAT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_INT_FSTAT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000001140ll;
    __bdk_csr_fatal("TNS_RDMA_INT_FSTAT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_INT_FSTAT bdk_tns_rdma_int_fstat_t
#define bustype_BDK_TNS_RDMA_INT_FSTAT BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_INT_FSTAT "TNS_RDMA_INT_FSTAT"
#define device_bar_BDK_TNS_RDMA_INT_FSTAT 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_INT_FSTAT 0
#define arguments_BDK_TNS_RDMA_INT_FSTAT -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_int_stat_w1c
 *
 * TNS RDMA Interrupt Status (Read/Write-1-Clear) Register
 * RDMA Interrupt Status Register.
 */
union bdk_tns_rdma_int_stat_w1c
{
    uint64_t u;
    struct bdk_tns_rdma_int_stat_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t lmac_unex_data        : 8;  /**< [ 31: 24](R/W1C/H) Unexpected data from LMAC. Data was received before an SOP flag was received. The data was dropped. */
        uint64_t lmac_unex_sop         : 8;  /**< [ 23: 16](R/W1C/H) Unexpected SOP from LMAC An SOP was received while a packet is already being received. The
                                                                 in-progress packet and the new packet initiated by the SOP were dropped. */
        uint64_t lmac_srunt            : 8;  /**< [ 15:  8](R/W1C/H) A packet was received from the LMAC which did not meet framing requirements for minimum size. */
        uint64_t reserved_7            : 1;
        uint64_t b_x2p_dbe             : 2;  /**< [  6:  5](R/W1C/H) Double-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t b_p2x_dbe             : 1;  /**< [  4:  4](R/W1C/H) Double-bit ECC error detected on B_P2X RAM. */
        uint64_t reserved_3            : 1;
        uint64_t b_x2p_sbe             : 2;  /**< [  2:  1](R/W1C/H) Single-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t b_p2x_sbe             : 1;  /**< [  0:  0](R/W1C/H) Single-bit ECC error detected on B_P2X RAM. */
#else /* Word 0 - Little Endian */
        uint64_t b_p2x_sbe             : 1;  /**< [  0:  0](R/W1C/H) Single-bit ECC error detected on B_P2X RAM. */
        uint64_t b_x2p_sbe             : 2;  /**< [  2:  1](R/W1C/H) Single-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t reserved_3            : 1;
        uint64_t b_p2x_dbe             : 1;  /**< [  4:  4](R/W1C/H) Double-bit ECC error detected on B_P2X RAM. */
        uint64_t b_x2p_dbe             : 2;  /**< [  6:  5](R/W1C/H) Double-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t reserved_7            : 1;
        uint64_t lmac_srunt            : 8;  /**< [ 15:  8](R/W1C/H) A packet was received from the LMAC which did not meet framing requirements for minimum size. */
        uint64_t lmac_unex_sop         : 8;  /**< [ 23: 16](R/W1C/H) Unexpected SOP from LMAC An SOP was received while a packet is already being received. The
                                                                 in-progress packet and the new packet initiated by the SOP were dropped. */
        uint64_t lmac_unex_data        : 8;  /**< [ 31: 24](R/W1C/H) Unexpected data from LMAC. Data was received before an SOP flag was received. The data was dropped. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_int_stat_w1c_s cn; */
};
typedef union bdk_tns_rdma_int_stat_w1c bdk_tns_rdma_int_stat_w1c_t;

#define BDK_TNS_RDMA_INT_STAT_W1C BDK_TNS_RDMA_INT_STAT_W1C_FUNC()
static inline uint64_t BDK_TNS_RDMA_INT_STAT_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_INT_STAT_W1C_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000001110ll;
    __bdk_csr_fatal("TNS_RDMA_INT_STAT_W1C", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_INT_STAT_W1C bdk_tns_rdma_int_stat_w1c_t
#define bustype_BDK_TNS_RDMA_INT_STAT_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_INT_STAT_W1C "TNS_RDMA_INT_STAT_W1C"
#define device_bar_BDK_TNS_RDMA_INT_STAT_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_INT_STAT_W1C 0
#define arguments_BDK_TNS_RDMA_INT_STAT_W1C -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_int_stat_w1s
 *
 * TNS RDMA Interrupt Status (Read/Write-1-Set) Register
 * RDMA Interrupt Status Register.
 */
union bdk_tns_rdma_int_stat_w1s
{
    uint64_t u;
    struct bdk_tns_rdma_int_stat_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t lmac_unex_data        : 8;  /**< [ 31: 24](R/W1S/H) Unexpected data from LMAC. Data was received before an SOP flag was received. The data was dropped. */
        uint64_t lmac_unex_sop         : 8;  /**< [ 23: 16](R/W1S/H) Unexpected SOP from LMAC An SOP was received while a packet is already being received. The
                                                                 in-progress packet and the new packet initiated by the SOP were dropped. */
        uint64_t lmac_srunt            : 8;  /**< [ 15:  8](R/W1S/H) A packet was received from the LMAC which did not meet framing requirements for minimum size. */
        uint64_t reserved_7            : 1;
        uint64_t b_x2p_dbe             : 2;  /**< [  6:  5](R/W1S/H) Double-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t b_p2x_dbe             : 1;  /**< [  4:  4](R/W1S/H) Double-bit ECC error detected on B_P2X RAM. */
        uint64_t reserved_3            : 1;
        uint64_t b_x2p_sbe             : 2;  /**< [  2:  1](R/W1S/H) Single-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t b_p2x_sbe             : 1;  /**< [  0:  0](R/W1S/H) Single-bit ECC error detected on B_P2X RAM. */
#else /* Word 0 - Little Endian */
        uint64_t b_p2x_sbe             : 1;  /**< [  0:  0](R/W1S/H) Single-bit ECC error detected on B_P2X RAM. */
        uint64_t b_x2p_sbe             : 2;  /**< [  2:  1](R/W1S/H) Single-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t reserved_3            : 1;
        uint64_t b_p2x_dbe             : 1;  /**< [  4:  4](R/W1S/H) Double-bit ECC error detected on B_P2X RAM. */
        uint64_t b_x2p_dbe             : 2;  /**< [  6:  5](R/W1S/H) Double-bit ECC error detected on B_X2P[1..0] RAM. */
        uint64_t reserved_7            : 1;
        uint64_t lmac_srunt            : 8;  /**< [ 15:  8](R/W1S/H) A packet was received from the LMAC which did not meet framing requirements for minimum size. */
        uint64_t lmac_unex_sop         : 8;  /**< [ 23: 16](R/W1S/H) Unexpected SOP from LMAC An SOP was received while a packet is already being received. The
                                                                 in-progress packet and the new packet initiated by the SOP were dropped. */
        uint64_t lmac_unex_data        : 8;  /**< [ 31: 24](R/W1S/H) Unexpected data from LMAC. Data was received before an SOP flag was received. The data was dropped. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_int_stat_w1s_s cn; */
};
typedef union bdk_tns_rdma_int_stat_w1s bdk_tns_rdma_int_stat_w1s_t;

#define BDK_TNS_RDMA_INT_STAT_W1S BDK_TNS_RDMA_INT_STAT_W1S_FUNC()
static inline uint64_t BDK_TNS_RDMA_INT_STAT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_INT_STAT_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000001100ll;
    __bdk_csr_fatal("TNS_RDMA_INT_STAT_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_INT_STAT_W1S bdk_tns_rdma_int_stat_w1s_t
#define bustype_BDK_TNS_RDMA_INT_STAT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_INT_STAT_W1S "TNS_RDMA_INT_STAT_W1S"
#define device_bar_BDK_TNS_RDMA_INT_STAT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_INT_STAT_W1S 0
#define arguments_BDK_TNS_RDMA_INT_STAT_W1S -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_lmac#_drop_cnt
 *
 * TNS RDMA BGX Drop Counter Register
 */
union bdk_tns_rdma_lmacx_drop_cnt
{
    uint64_t u;
    struct bdk_tns_rdma_lmacx_drop_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t packets               : 8;  /**< [  7:  0](R/W/H) Packets arriving from LMAC dropped due to insufficient size.
                                                                 A packet received from a LMAC is immediately dropped if timestamp extraction
                                                                 is enabled for the LMAC and the arriving packet is not large enough
                                                                 to contain a full 8-byte timestamp and at least 1-byte of packet data.
                                                                 This field counts all packets dropped due to insufficient packet size when
                                                                 timestamp extraction is enabled.
                                                                 This counter rolls over. */
#else /* Word 0 - Little Endian */
        uint64_t packets               : 8;  /**< [  7:  0](R/W/H) Packets arriving from LMAC dropped due to insufficient size.
                                                                 A packet received from a LMAC is immediately dropped if timestamp extraction
                                                                 is enabled for the LMAC and the arriving packet is not large enough
                                                                 to contain a full 8-byte timestamp and at least 1-byte of packet data.
                                                                 This field counts all packets dropped due to insufficient packet size when
                                                                 timestamp extraction is enabled.
                                                                 This counter rolls over. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_lmacx_drop_cnt_s cn; */
};
typedef union bdk_tns_rdma_lmacx_drop_cnt bdk_tns_rdma_lmacx_drop_cnt_t;

static inline uint64_t BDK_TNS_RDMA_LMACX_DROP_CNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_LMACX_DROP_CNT(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=7))
        return 0x842000001600ll + 0x10ll * ((a) & 0x7);
    __bdk_csr_fatal("TNS_RDMA_LMACX_DROP_CNT", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_LMACX_DROP_CNT(a) bdk_tns_rdma_lmacx_drop_cnt_t
#define bustype_BDK_TNS_RDMA_LMACX_DROP_CNT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_LMACX_DROP_CNT(a) "TNS_RDMA_LMACX_DROP_CNT"
#define device_bar_BDK_TNS_RDMA_LMACX_DROP_CNT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_LMACX_DROP_CNT(a) (a)
#define arguments_BDK_TNS_RDMA_LMACX_DROP_CNT(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_cnt_lb
 *
 * TNS RDMA Loopback Receive Counter Register
 * Packets and bytes received by the internal loopback port.
 * All fields have roll over counters.
 */
union bdk_tns_rdma_nb_cnt_lb
{
    uint64_t u;
    struct bdk_tns_rdma_nb_cnt_lb_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_60_63        : 4;
        uint64_t bytes                 : 36; /**< [ 59: 24](R/W/H) Packet bytes. */
        uint64_t packets               : 24; /**< [ 23:  0](R/W/H) Packets. */
#else /* Word 0 - Little Endian */
        uint64_t packets               : 24; /**< [ 23:  0](R/W/H) Packets. */
        uint64_t bytes                 : 36; /**< [ 59: 24](R/W/H) Packet bytes. */
        uint64_t reserved_60_63        : 4;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_cnt_lb_s cn; */
};
typedef union bdk_tns_rdma_nb_cnt_lb bdk_tns_rdma_nb_cnt_lb_t;

#define BDK_TNS_RDMA_NB_CNT_LB BDK_TNS_RDMA_NB_CNT_LB_FUNC()
static inline uint64_t BDK_TNS_RDMA_NB_CNT_LB_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_CNT_LB_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842042000200ll;
    __bdk_csr_fatal("TNS_RDMA_NB_CNT_LB", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_CNT_LB bdk_tns_rdma_nb_cnt_lb_t
#define bustype_BDK_TNS_RDMA_NB_CNT_LB BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_CNT_LB "TNS_RDMA_NB_CNT_LB"
#define device_bar_BDK_TNS_RDMA_NB_CNT_LB 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_CNT_LB 0
#define arguments_BDK_TNS_RDMA_NB_CNT_LB -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_config
 *
 * TNS RDMA Configuration Register
 * General configuration register.
 */
union bdk_tns_rdma_nb_config
{
    uint64_t u;
    struct bdk_tns_rdma_nb_config_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t master_en             : 1;  /**< [ 63: 63](R/W/H) Master RDMA enable.
                                                                 When set, allows functional use of the network switch.
                                                                 Usage of TNS_TDMA_NB_CONFIG1[AUTO_INIT] will clear this field. */
        uint64_t reserved_0_62         : 63;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_62         : 63;
        uint64_t master_en             : 1;  /**< [ 63: 63](R/W/H) Master RDMA enable.
                                                                 When set, allows functional use of the network switch.
                                                                 Usage of TNS_TDMA_NB_CONFIG1[AUTO_INIT] will clear this field. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_config_s cn; */
};
typedef union bdk_tns_rdma_nb_config bdk_tns_rdma_nb_config_t;

#define BDK_TNS_RDMA_NB_CONFIG BDK_TNS_RDMA_NB_CONFIG_FUNC()
static inline uint64_t BDK_TNS_RDMA_NB_CONFIG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_CONFIG_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842042004020ll;
    __bdk_csr_fatal("TNS_RDMA_NB_CONFIG", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_CONFIG bdk_tns_rdma_nb_config_t
#define bustype_BDK_TNS_RDMA_NB_CONFIG BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_CONFIG "TNS_RDMA_NB_CONFIG"
#define device_bar_BDK_TNS_RDMA_NB_CONFIG 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_CONFIG 0
#define arguments_BDK_TNS_RDMA_NB_CONFIG -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_dbg_config
 *
 * INTERNAL: TNS RDMA Debug Configuration Register
 *
 * This register provides debug control of RDMA functionality.
 */
union bdk_tns_rdma_nb_dbg_config
{
    uint64_t u;
    struct bdk_tns_rdma_nb_dbg_config_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_61_63        : 3;
        uint64_t sdma_fifo_bp          : 5;  /**< [ 60: 56](R/W) Occupancy level at which the SDMA will assert back pressure to the SDE. */
        uint64_t reserved_14_55        : 42;
        uint64_t body_ptr_error_value  : 10; /**< [ 13:  4](R/W) When SDE Parser is configured to allow a RX port to operate in cut-through mode, the
                                                                 indication of an error for a single-page (header only) packet must be sent along with
                                                                 the packet header because the SDE will ignore the EOP message.
                                                                 In the event a header-only sized packet is received with error or an error is detected
                                                                 in the RDMA (e.g. in the event of runt or ECC error) bits 13:4 of the non-valid packet
                                                                 body pointer will be set to the value indicated by this field, with a 4-bit error code
                                                                 inserted in bits 3:0.
                                                                 The allowable range of values for this field must reflect page pointers that would
                                                                 never be present in the system.
                                                                 14-bit body page values from 0x3000 through 0x3fff are not supported by
                                                                 the 3MB TNS Packet Memory.
                                                                 Therefore, any body pointer value within this range is acceptable to indicate error.
                                                                 This field must be configured to match the corresponding CSR value in the SDE Parser.
                                                                 This field must never be set to a value below 0x300. */
        uint64_t reserved_0_3          : 4;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_3          : 4;
        uint64_t body_ptr_error_value  : 10; /**< [ 13:  4](R/W) When SDE Parser is configured to allow a RX port to operate in cut-through mode, the
                                                                 indication of an error for a single-page (header only) packet must be sent along with
                                                                 the packet header because the SDE will ignore the EOP message.
                                                                 In the event a header-only sized packet is received with error or an error is detected
                                                                 in the RDMA (e.g. in the event of runt or ECC error) bits 13:4 of the non-valid packet
                                                                 body pointer will be set to the value indicated by this field, with a 4-bit error code
                                                                 inserted in bits 3:0.
                                                                 The allowable range of values for this field must reflect page pointers that would
                                                                 never be present in the system.
                                                                 14-bit body page values from 0x3000 through 0x3fff are not supported by
                                                                 the 3MB TNS Packet Memory.
                                                                 Therefore, any body pointer value within this range is acceptable to indicate error.
                                                                 This field must be configured to match the corresponding CSR value in the SDE Parser.
                                                                 This field must never be set to a value below 0x300. */
        uint64_t reserved_14_55        : 42;
        uint64_t sdma_fifo_bp          : 5;  /**< [ 60: 56](R/W) Occupancy level at which the SDMA will assert back pressure to the SDE. */
        uint64_t reserved_61_63        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_dbg_config_s cn; */
};
typedef union bdk_tns_rdma_nb_dbg_config bdk_tns_rdma_nb_dbg_config_t;

#define BDK_TNS_RDMA_NB_DBG_CONFIG BDK_TNS_RDMA_NB_DBG_CONFIG_FUNC()
static inline uint64_t BDK_TNS_RDMA_NB_DBG_CONFIG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_DBG_CONFIG_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842042004400ll;
    __bdk_csr_fatal("TNS_RDMA_NB_DBG_CONFIG", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_DBG_CONFIG bdk_tns_rdma_nb_dbg_config_t
#define bustype_BDK_TNS_RDMA_NB_DBG_CONFIG BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_DBG_CONFIG "TNS_RDMA_NB_DBG_CONFIG"
#define device_bar_BDK_TNS_RDMA_NB_DBG_CONFIG 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_DBG_CONFIG 0
#define arguments_BDK_TNS_RDMA_NB_DBG_CONFIG -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_dbg_cx_full
 *
 * INTERNAL: TNS RDMA Debug CX Full Level Control Register
 *
 * This register provides debug control of FIFO full.
 * Async FIFOs assert an early full indication when occupancies reach the values
 * below.
 */
union bdk_tns_rdma_nb_dbg_cx_full
{
    uint64_t u;
    struct bdk_tns_rdma_nb_dbg_cx_full_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_21_63        : 43;
        uint64_t lmac_tx_bp            : 5;  /**< [ 20: 16](R/W) Back pressure to LMACs. */
        uint64_t reserved_13_15        : 3;
        uint64_t nic_tx_ebp            : 5;  /**< [ 12:  8](R/W) Back pressure to NIC. */
        uint64_t reserved_5_7          : 3;
        uint64_t nic_tx_chan_bp        : 5;  /**< [  4:  0](R/W) Channel back pressure to NIC. */
#else /* Word 0 - Little Endian */
        uint64_t nic_tx_chan_bp        : 5;  /**< [  4:  0](R/W) Channel back pressure to NIC. */
        uint64_t reserved_5_7          : 3;
        uint64_t nic_tx_ebp            : 5;  /**< [ 12:  8](R/W) Back pressure to NIC. */
        uint64_t reserved_13_15        : 3;
        uint64_t lmac_tx_bp            : 5;  /**< [ 20: 16](R/W) Back pressure to LMACs. */
        uint64_t reserved_21_63        : 43;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_dbg_cx_full_s cn; */
};
typedef union bdk_tns_rdma_nb_dbg_cx_full bdk_tns_rdma_nb_dbg_cx_full_t;

#define BDK_TNS_RDMA_NB_DBG_CX_FULL BDK_TNS_RDMA_NB_DBG_CX_FULL_FUNC()
static inline uint64_t BDK_TNS_RDMA_NB_DBG_CX_FULL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_DBG_CX_FULL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842042000c40ll;
    __bdk_csr_fatal("TNS_RDMA_NB_DBG_CX_FULL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_DBG_CX_FULL bdk_tns_rdma_nb_dbg_cx_full_t
#define bustype_BDK_TNS_RDMA_NB_DBG_CX_FULL BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_DBG_CX_FULL "TNS_RDMA_NB_DBG_CX_FULL"
#define device_bar_BDK_TNS_RDMA_NB_DBG_CX_FULL 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_DBG_CX_FULL 0
#define arguments_BDK_TNS_RDMA_NB_DBG_CX_FULL -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_dbg_cx_occ
 *
 * INTERNAL: TNS RDMA Debug CX FIFO Occupancy Status Register
 *
 * Async FIFO occupancies.
 */
union bdk_tns_rdma_nb_dbg_cx_occ
{
    uint64_t u;
    struct bdk_tns_rdma_nb_dbg_cx_occ_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_45_63        : 19;
        uint64_t lmac7_4_tx_bp         : 5;  /**< [ 44: 40](RO/H) Back pressure to LMACs 7..4. */
        uint64_t reserved_37_39        : 3;
        uint64_t lmac3_0_tx_bp         : 5;  /**< [ 36: 32](RO/H) Back pressure to LMACs 3..0. */
        uint64_t reserved_29_31        : 3;
        uint64_t nici1_tx_ebp          : 5;  /**< [ 28: 24](RO/H) Back pressure to NICI1. */
        uint64_t reserved_21_23        : 3;
        uint64_t nici0_tx_ebp          : 5;  /**< [ 20: 16](RO/H) Back pressure to NICI0. */
        uint64_t reserved_13_15        : 3;
        uint64_t nici1_tx_chan_bp      : 5;  /**< [ 12:  8](RO/H) Channel back pressure to NICI1. */
        uint64_t reserved_5_7          : 3;
        uint64_t nici0_tx_chan_bp      : 5;  /**< [  4:  0](RO/H) Channel back pressure to NICI0. */
#else /* Word 0 - Little Endian */
        uint64_t nici0_tx_chan_bp      : 5;  /**< [  4:  0](RO/H) Channel back pressure to NICI0. */
        uint64_t reserved_5_7          : 3;
        uint64_t nici1_tx_chan_bp      : 5;  /**< [ 12:  8](RO/H) Channel back pressure to NICI1. */
        uint64_t reserved_13_15        : 3;
        uint64_t nici0_tx_ebp          : 5;  /**< [ 20: 16](RO/H) Back pressure to NICI0. */
        uint64_t reserved_21_23        : 3;
        uint64_t nici1_tx_ebp          : 5;  /**< [ 28: 24](RO/H) Back pressure to NICI1. */
        uint64_t reserved_29_31        : 3;
        uint64_t lmac3_0_tx_bp         : 5;  /**< [ 36: 32](RO/H) Back pressure to LMACs 3..0. */
        uint64_t reserved_37_39        : 3;
        uint64_t lmac7_4_tx_bp         : 5;  /**< [ 44: 40](RO/H) Back pressure to LMACs 7..4. */
        uint64_t reserved_45_63        : 19;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_dbg_cx_occ_s cn; */
};
typedef union bdk_tns_rdma_nb_dbg_cx_occ bdk_tns_rdma_nb_dbg_cx_occ_t;

#define BDK_TNS_RDMA_NB_DBG_CX_OCC BDK_TNS_RDMA_NB_DBG_CX_OCC_FUNC()
static inline uint64_t BDK_TNS_RDMA_NB_DBG_CX_OCC_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_DBG_CX_OCC_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842042000c50ll;
    __bdk_csr_fatal("TNS_RDMA_NB_DBG_CX_OCC", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_DBG_CX_OCC bdk_tns_rdma_nb_dbg_cx_occ_t
#define bustype_BDK_TNS_RDMA_NB_DBG_CX_OCC BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_DBG_CX_OCC "TNS_RDMA_NB_DBG_CX_OCC"
#define device_bar_BDK_TNS_RDMA_NB_DBG_CX_OCC 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_DBG_CX_OCC 0
#define arguments_BDK_TNS_RDMA_NB_DBG_CX_OCC -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_dbgb_sel
 *
 * INTERNAL: TNS RDMA Debug Bus Select Register
 *
 * Debug bus select register.
 * This register is only used in pass 1.x.
 */
union bdk_tns_rdma_nb_dbgb_sel
{
    uint64_t u;
    struct bdk_tns_rdma_nb_dbgb_sel_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t sel1                  : 24; /**< [ 47: 24](R/W) Select group for upper debug bus bits */
        uint64_t sel0                  : 24; /**< [ 23:  0](R/W) Select group for lower debug bus bits */
#else /* Word 0 - Little Endian */
        uint64_t sel0                  : 24; /**< [ 23:  0](R/W) Select group for lower debug bus bits */
        uint64_t sel1                  : 24; /**< [ 47: 24](R/W) Select group for upper debug bus bits */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_dbgb_sel_s cn; */
};
typedef union bdk_tns_rdma_nb_dbgb_sel bdk_tns_rdma_nb_dbgb_sel_t;

#define BDK_TNS_RDMA_NB_DBGB_SEL BDK_TNS_RDMA_NB_DBGB_SEL_FUNC()
static inline uint64_t BDK_TNS_RDMA_NB_DBGB_SEL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_DBGB_SEL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS1_X))
        return 0x842042004700ll;
    __bdk_csr_fatal("TNS_RDMA_NB_DBGB_SEL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_DBGB_SEL bdk_tns_rdma_nb_dbgb_sel_t
#define bustype_BDK_TNS_RDMA_NB_DBGB_SEL BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_DBGB_SEL "TNS_RDMA_NB_DBGB_SEL"
#define device_bar_BDK_TNS_RDMA_NB_DBGB_SEL 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_DBGB_SEL 0
#define arguments_BDK_TNS_RDMA_NB_DBGB_SEL -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_ecc_ctl
 *
 * TNS RDMA ECC Control Register
 * This register can be used to disable ECC data correction, insert ECC errors.
 * Fields *ECC_DIS disable SBE data correction. If ECC_DIS is 0x1, then no data correction is
 * performed but errors will still be reported.
 * Fields *ECC_FLIP_SYND flip the syndrome\<1:0\> bits to generate 1-bit/2-bit error for testing.
 * * 0x0 = normal operation.
 * * 0x1 = SBE on bit\<0\>.
 * * 0x2 = SBE on bit\<1\>.
 * * 0x3 = DBE on bits\<1:0\>.
 */
union bdk_tns_rdma_nb_ecc_ctl
{
    uint64_t u;
    struct bdk_tns_rdma_nb_ecc_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t sdma_ecc_dis          : 1;  /**< [ 39: 39](R/W) Disable ECC data correction for SDMA path. */
        uint64_t plut_sdma_ecc_dis     : 1;  /**< [ 38: 38](R/W) Disable ECC data correction for SDMA port LUT. */
        uint64_t plut_p2x_ecc_dis      : 1;  /**< [ 37: 37](R/W) Disable ECC data correction for P2X port LUT. */
        uint64_t pkt_lb_ecc_dis        : 1;  /**< [ 36: 36](R/W) Disable ECC data correction for loopback packet path FIFOs. */
        uint64_t pkt_lmacts_ecc_dis    : 1;  /**< [ 35: 35](R/W) Disable ECC data correction for LMAC packet path timestamp FIFOs. */
        uint64_t pkt_lmac_ecc_dis      : 1;  /**< [ 34: 34](R/W) Disable ECC data correction for LMAC packet path FIFOs. */
        uint64_t pkt_nici_ecc_dis      : 2;  /**< [ 33: 32](R/W) Disable ECC data correction for NICI[1..0] packet path FIFOs. */
        uint64_t reserved_16_31        : 16;
        uint64_t pm_ecc_flip_synd      : 2;  /**< [ 15: 14](R/W) Flip syndrome for all data written to the packet memory. */
        uint64_t sdma_ecc_flip_synd    : 2;  /**< [ 13: 12](R/W) Flip syndrome for all data written to the SDMA FIFOs. */
        uint64_t plut_sdma_ecc_flip_synd : 2;/**< [ 11: 10](R/W) Flip syndrome for all data written to the SDMA port LUT. */
        uint64_t plut_p2x_ecc_flip_synd : 2; /**< [  9:  8](R/W) Flip syndrome for all data written to the P2X port LUT. */
        uint64_t pkt_lb_ecc_flip_synd  : 2;  /**< [  7:  6](R/W) Flip syndrome for all data written to loopback packet path FIFOs. */
        uint64_t pkt_lmacts_ecc_flip_synd : 2;/**< [  5:  4](R/W) Flip syndrome for all data written to LMAC packet path timestamp FIFOs. */
        uint64_t pkt_lmac_ecc_flip_synd : 2; /**< [  3:  2](R/W) Flip syndrome for all data written to LMAC packet path FIFOs. */
        uint64_t pkt_nici_ecc_flip_synd : 2; /**< [  1:  0](R/W) Flip syndrome for all data written to P2X packet path FIFOs. */
#else /* Word 0 - Little Endian */
        uint64_t pkt_nici_ecc_flip_synd : 2; /**< [  1:  0](R/W) Flip syndrome for all data written to P2X packet path FIFOs. */
        uint64_t pkt_lmac_ecc_flip_synd : 2; /**< [  3:  2](R/W) Flip syndrome for all data written to LMAC packet path FIFOs. */
        uint64_t pkt_lmacts_ecc_flip_synd : 2;/**< [  5:  4](R/W) Flip syndrome for all data written to LMAC packet path timestamp FIFOs. */
        uint64_t pkt_lb_ecc_flip_synd  : 2;  /**< [  7:  6](R/W) Flip syndrome for all data written to loopback packet path FIFOs. */
        uint64_t plut_p2x_ecc_flip_synd : 2; /**< [  9:  8](R/W) Flip syndrome for all data written to the P2X port LUT. */
        uint64_t plut_sdma_ecc_flip_synd : 2;/**< [ 11: 10](R/W) Flip syndrome for all data written to the SDMA port LUT. */
        uint64_t sdma_ecc_flip_synd    : 2;  /**< [ 13: 12](R/W) Flip syndrome for all data written to the SDMA FIFOs. */
        uint64_t pm_ecc_flip_synd      : 2;  /**< [ 15: 14](R/W) Flip syndrome for all data written to the packet memory. */
        uint64_t reserved_16_31        : 16;
        uint64_t pkt_nici_ecc_dis      : 2;  /**< [ 33: 32](R/W) Disable ECC data correction for NICI[1..0] packet path FIFOs. */
        uint64_t pkt_lmac_ecc_dis      : 1;  /**< [ 34: 34](R/W) Disable ECC data correction for LMAC packet path FIFOs. */
        uint64_t pkt_lmacts_ecc_dis    : 1;  /**< [ 35: 35](R/W) Disable ECC data correction for LMAC packet path timestamp FIFOs. */
        uint64_t pkt_lb_ecc_dis        : 1;  /**< [ 36: 36](R/W) Disable ECC data correction for loopback packet path FIFOs. */
        uint64_t plut_p2x_ecc_dis      : 1;  /**< [ 37: 37](R/W) Disable ECC data correction for P2X port LUT. */
        uint64_t plut_sdma_ecc_dis     : 1;  /**< [ 38: 38](R/W) Disable ECC data correction for SDMA port LUT. */
        uint64_t sdma_ecc_dis          : 1;  /**< [ 39: 39](R/W) Disable ECC data correction for SDMA path. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_ecc_ctl_s cn; */
};
typedef union bdk_tns_rdma_nb_ecc_ctl bdk_tns_rdma_nb_ecc_ctl_t;

#define BDK_TNS_RDMA_NB_ECC_CTL BDK_TNS_RDMA_NB_ECC_CTL_FUNC()
static inline uint64_t BDK_TNS_RDMA_NB_ECC_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_ECC_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842042004000ll;
    __bdk_csr_fatal("TNS_RDMA_NB_ECC_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_ECC_CTL bdk_tns_rdma_nb_ecc_ctl_t
#define bustype_BDK_TNS_RDMA_NB_ECC_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_ECC_CTL "TNS_RDMA_NB_ECC_CTL"
#define device_bar_BDK_TNS_RDMA_NB_ECC_CTL 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_ECC_CTL 0
#define arguments_BDK_TNS_RDMA_NB_ECC_CTL -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_ecc_err_stat
 *
 * TNS RDMA ECC Error Status Register
 * This register logs information to help debug ECC errors.
 */
union bdk_tns_rdma_nb_ecc_err_stat
{
    uint64_t u;
    struct bdk_tns_rdma_nb_ecc_err_stat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_19_63        : 45;
        uint64_t syndrome              : 11; /**< [ 18:  8](RO/H) Error syndrome. */
        uint64_t address               : 8;  /**< [  7:  0](RO/H) Address of ECC error. */
#else /* Word 0 - Little Endian */
        uint64_t address               : 8;  /**< [  7:  0](RO/H) Address of ECC error. */
        uint64_t syndrome              : 11; /**< [ 18:  8](RO/H) Error syndrome. */
        uint64_t reserved_19_63        : 45;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_ecc_err_stat_s cn; */
};
typedef union bdk_tns_rdma_nb_ecc_err_stat bdk_tns_rdma_nb_ecc_err_stat_t;

#define BDK_TNS_RDMA_NB_ECC_ERR_STAT BDK_TNS_RDMA_NB_ECC_ERR_STAT_FUNC()
static inline uint64_t BDK_TNS_RDMA_NB_ECC_ERR_STAT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_ECC_ERR_STAT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842042004010ll;
    __bdk_csr_fatal("TNS_RDMA_NB_ECC_ERR_STAT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_ECC_ERR_STAT bdk_tns_rdma_nb_ecc_err_stat_t
#define bustype_BDK_TNS_RDMA_NB_ECC_ERR_STAT BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_ECC_ERR_STAT "TNS_RDMA_NB_ECC_ERR_STAT"
#define device_bar_BDK_TNS_RDMA_NB_ECC_ERR_STAT 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_ECC_ERR_STAT 0
#define arguments_BDK_TNS_RDMA_NB_ECC_ERR_STAT -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_eco
 *
 * INTERNAL: TNS RDMA ECO Register
 *
 * ECO register.
 */
union bdk_tns_rdma_nb_eco
{
    uint64_t u;
    struct bdk_tns_rdma_nb_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t rst1                  : 8;  /**< [ 15:  8](R/W) Reset to 1 spare bits */
        uint64_t rst0                  : 8;  /**< [  7:  0](R/W) Reset to 0 spare bits */
#else /* Word 0 - Little Endian */
        uint64_t rst0                  : 8;  /**< [  7:  0](R/W) Reset to 0 spare bits */
        uint64_t rst1                  : 8;  /**< [ 15:  8](R/W) Reset to 1 spare bits */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_eco_s cn; */
};
typedef union bdk_tns_rdma_nb_eco bdk_tns_rdma_nb_eco_t;

#define BDK_TNS_RDMA_NB_ECO BDK_TNS_RDMA_NB_ECO_FUNC()
static inline uint64_t BDK_TNS_RDMA_NB_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_ECO_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842042004800ll;
    __bdk_csr_fatal("TNS_RDMA_NB_ECO", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_ECO bdk_tns_rdma_nb_eco_t
#define bustype_BDK_TNS_RDMA_NB_ECO BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_ECO "TNS_RDMA_NB_ECO"
#define device_bar_BDK_TNS_RDMA_NB_ECO 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_ECO 0
#define arguments_BDK_TNS_RDMA_NB_ECO -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_force_lmac#_bp
 *
 * TNS RDMA LMAC Back Pressure Forcing Register
 */
union bdk_tns_rdma_nb_force_lmacx_bp
{
    uint64_t u;
    struct bdk_tns_rdma_nb_force_lmacx_bp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t priorities            : 16; /**< [ 15:  0](R/W) Force XOFF back pressure for specific LMAC priorities as though the
                                                                 LMAC was indicating back pressure.
                                                                 For each bit:
                                                                 When 1, forces XOFF for LMAC priority [15..0].
                                                                 When 0, passes XON/XOFF information arriving from the LMAC. */
#else /* Word 0 - Little Endian */
        uint64_t priorities            : 16; /**< [ 15:  0](R/W) Force XOFF back pressure for specific LMAC priorities as though the
                                                                 LMAC was indicating back pressure.
                                                                 For each bit:
                                                                 When 1, forces XOFF for LMAC priority [15..0].
                                                                 When 0, passes XON/XOFF information arriving from the LMAC. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_force_lmacx_bp_s cn; */
};
typedef union bdk_tns_rdma_nb_force_lmacx_bp bdk_tns_rdma_nb_force_lmacx_bp_t;

static inline uint64_t BDK_TNS_RDMA_NB_FORCE_LMACX_BP(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_FORCE_LMACX_BP(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=7))
        return 0x842042000900ll + 0x10ll * ((a) & 0x7);
    __bdk_csr_fatal("TNS_RDMA_NB_FORCE_LMACX_BP", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_FORCE_LMACX_BP(a) bdk_tns_rdma_nb_force_lmacx_bp_t
#define bustype_BDK_TNS_RDMA_NB_FORCE_LMACX_BP(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_FORCE_LMACX_BP(a) "TNS_RDMA_NB_FORCE_LMACX_BP"
#define device_bar_BDK_TNS_RDMA_NB_FORCE_LMACX_BP(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_FORCE_LMACX_BP(a) (a)
#define arguments_BDK_TNS_RDMA_NB_FORCE_LMACX_BP(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_force_nic#_bp
 *
 * TNS RDMA NIC Back Pressure Forcing Register
 */
union bdk_tns_rdma_nb_force_nicx_bp
{
    uint64_t u;
    struct bdk_tns_rdma_nb_force_nicx_bp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t chan                  : 64; /**< [ 63:  0](R/W) Force XOFF back pressure for specific NIC channels as though the
                                                                 NIC was indicating back pressure.
                                                                 For each bit:
                                                                 When 1, forces XOFF for channels.
                                                                 When 0, passes XON/XOFF information arriving from the NIC. */
#else /* Word 0 - Little Endian */
        uint64_t chan                  : 64; /**< [ 63:  0](R/W) Force XOFF back pressure for specific NIC channels as though the
                                                                 NIC was indicating back pressure.
                                                                 For each bit:
                                                                 When 1, forces XOFF for channels.
                                                                 When 0, passes XON/XOFF information arriving from the NIC. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_force_nicx_bp_s cn; */
};
typedef union bdk_tns_rdma_nb_force_nicx_bp bdk_tns_rdma_nb_force_nicx_bp_t;

static inline uint64_t BDK_TNS_RDMA_NB_FORCE_NICX_BP(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_FORCE_NICX_BP(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x842042000980ll + 0x10ll * ((a) & 0x3);
    __bdk_csr_fatal("TNS_RDMA_NB_FORCE_NICX_BP", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_FORCE_NICX_BP(a) bdk_tns_rdma_nb_force_nicx_bp_t
#define bustype_BDK_TNS_RDMA_NB_FORCE_NICX_BP(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_FORCE_NICX_BP(a) "TNS_RDMA_NB_FORCE_NICX_BP"
#define device_bar_BDK_TNS_RDMA_NB_FORCE_NICX_BP(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_FORCE_NICX_BP(a) (a)
#define arguments_BDK_TNS_RDMA_NB_FORCE_NICX_BP(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_hdr_sz_cfg
 *
 * TNS RDMA Packet Header Size Configuration Register
 * This register is used to designate the number of bytes which are considered part
 * of the packet header and will be extracted for processing.
 * Bytes received after the header are considered part of the body.
 * Timestamp bytes received from the LMAC (if enabled) are not counted against the
 * header size.
 * Unpredictable behavior will occur if software changes the header size configuration
 * for a port while packets are being received.
 * All fields are enumerated by TNS_RDMA_HDR_SZ_E.
 */
union bdk_tns_rdma_nb_hdr_sz_cfg
{
    uint64_t u;
    struct bdk_tns_rdma_nb_hdr_sz_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t lb                    : 2;  /**< [ 21: 20](R/W) Packet header size for the loopback packet path. */
        uint64_t nici1                 : 2;  /**< [ 19: 18](R/W) Packet header size for the NICI1 packet path. */
        uint64_t nici0                 : 2;  /**< [ 17: 16](R/W) Packet header size for the NICI0 packet path. */
        uint64_t lmac7                 : 2;  /**< [ 15: 14](R/W) Packet header size for the LMAC7 packet path. */
        uint64_t lmac6                 : 2;  /**< [ 13: 12](R/W) Packet header size for the LMAC6 packet path. */
        uint64_t lmac5                 : 2;  /**< [ 11: 10](R/W) Packet header size for the LMAC5 packet path. */
        uint64_t lmac4                 : 2;  /**< [  9:  8](R/W) Packet header size for the LMAC4 packet path. */
        uint64_t lmac3                 : 2;  /**< [  7:  6](R/W) Packet header size for the LMAC3 packet path. */
        uint64_t lmac2                 : 2;  /**< [  5:  4](R/W) Packet header size for the LMAC2 packet path. */
        uint64_t lmac1                 : 2;  /**< [  3:  2](R/W) Packet header size for the LMAC1 packet path. */
        uint64_t lmac0                 : 2;  /**< [  1:  0](R/W) Packet header size for the LMAC0 packet path. */
#else /* Word 0 - Little Endian */
        uint64_t lmac0                 : 2;  /**< [  1:  0](R/W) Packet header size for the LMAC0 packet path. */
        uint64_t lmac1                 : 2;  /**< [  3:  2](R/W) Packet header size for the LMAC1 packet path. */
        uint64_t lmac2                 : 2;  /**< [  5:  4](R/W) Packet header size for the LMAC2 packet path. */
        uint64_t lmac3                 : 2;  /**< [  7:  6](R/W) Packet header size for the LMAC3 packet path. */
        uint64_t lmac4                 : 2;  /**< [  9:  8](R/W) Packet header size for the LMAC4 packet path. */
        uint64_t lmac5                 : 2;  /**< [ 11: 10](R/W) Packet header size for the LMAC5 packet path. */
        uint64_t lmac6                 : 2;  /**< [ 13: 12](R/W) Packet header size for the LMAC6 packet path. */
        uint64_t lmac7                 : 2;  /**< [ 15: 14](R/W) Packet header size for the LMAC7 packet path. */
        uint64_t nici0                 : 2;  /**< [ 17: 16](R/W) Packet header size for the NICI0 packet path. */
        uint64_t nici1                 : 2;  /**< [ 19: 18](R/W) Packet header size for the NICI1 packet path. */
        uint64_t lb                    : 2;  /**< [ 21: 20](R/W) Packet header size for the loopback packet path. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_hdr_sz_cfg_s cn; */
};
typedef union bdk_tns_rdma_nb_hdr_sz_cfg bdk_tns_rdma_nb_hdr_sz_cfg_t;

#define BDK_TNS_RDMA_NB_HDR_SZ_CFG BDK_TNS_RDMA_NB_HDR_SZ_CFG_FUNC()
static inline uint64_t BDK_TNS_RDMA_NB_HDR_SZ_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_HDR_SZ_CFG_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842042004030ll;
    __bdk_csr_fatal("TNS_RDMA_NB_HDR_SZ_CFG", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_HDR_SZ_CFG bdk_tns_rdma_nb_hdr_sz_cfg_t
#define bustype_BDK_TNS_RDMA_NB_HDR_SZ_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_HDR_SZ_CFG "TNS_RDMA_NB_HDR_SZ_CFG"
#define device_bar_BDK_TNS_RDMA_NB_HDR_SZ_CFG 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_HDR_SZ_CFG 0
#define arguments_BDK_TNS_RDMA_NB_HDR_SZ_CFG -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_int_en_w1c
 *
 * TNS RDMA Interrupt Enable (Read/Write-1-Clear) Register
 * RDMA Interrupt Enable Register.
 */
union bdk_tns_rdma_nb_int_en_w1c
{
    uint64_t u;
    struct bdk_tns_rdma_nb_int_en_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t hts_exists            : 1;  /**< [ 49: 49](R/W1C/H) A token received from the SDE had the HTS flag set. */
        uint64_t runt_pkt              : 1;  /**< [ 48: 48](R/W1C/H) Runt packet received and captured. */
        uint64_t reserved_46_47        : 2;
        uint64_t sdma_dbe              : 1;  /**< [ 45: 45](R/W1C/H) Double-bit ECC error detected on SDMA RAM. */
        uint64_t plut_sdma_dbe         : 1;  /**< [ 44: 44](R/W1C/H) Double-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t plut_p2x_dbe          : 1;  /**< [ 43: 43](R/W1C/H) Double-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 42: 42](R/W1C/H) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_nici_dbe          : 2;  /**< [ 41: 40](R/W1C/H) Double-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lmacts_dbe        : 8;  /**< [ 39: 32](R/W1C/H) Double-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_lmac_dbe          : 8;  /**< [ 31: 24](R/W1C/H) Double-bit ECC error detected on PKT_LMAC[7..0] RAM. */
        uint64_t reserved_22_23        : 2;
        uint64_t sdma_sbe              : 1;  /**< [ 21: 21](R/W1C/H) Single-bit ECC error detected on SDMA RAM. */
        uint64_t plut_sdma_sbe         : 1;  /**< [ 20: 20](R/W1C/H) Single-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t plut_p2x_sbe          : 1;  /**< [ 19: 19](R/W1C/H) Single-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [ 18: 18](R/W1C/H) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_nici_sbe          : 2;  /**< [ 17: 16](R/W1C/H) Single-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lmacts_sbe        : 8;  /**< [ 15:  8](R/W1C/H) Single-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_lmac_sbe          : 8;  /**< [  7:  0](R/W1C/H) Single-bit ECC error detected on PKT_LMAC[7..0] RAM. */
#else /* Word 0 - Little Endian */
        uint64_t pkt_lmac_sbe          : 8;  /**< [  7:  0](R/W1C/H) Single-bit ECC error detected on PKT_LMAC[7..0] RAM. */
        uint64_t pkt_lmacts_sbe        : 8;  /**< [ 15:  8](R/W1C/H) Single-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_nici_sbe          : 2;  /**< [ 17: 16](R/W1C/H) Single-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [ 18: 18](R/W1C/H) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t plut_p2x_sbe          : 1;  /**< [ 19: 19](R/W1C/H) Single-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t plut_sdma_sbe         : 1;  /**< [ 20: 20](R/W1C/H) Single-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t sdma_sbe              : 1;  /**< [ 21: 21](R/W1C/H) Single-bit ECC error detected on SDMA RAM. */
        uint64_t reserved_22_23        : 2;
        uint64_t pkt_lmac_dbe          : 8;  /**< [ 31: 24](R/W1C/H) Double-bit ECC error detected on PKT_LMAC[7..0] RAM. */
        uint64_t pkt_lmacts_dbe        : 8;  /**< [ 39: 32](R/W1C/H) Double-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_nici_dbe          : 2;  /**< [ 41: 40](R/W1C/H) Double-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 42: 42](R/W1C/H) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t plut_p2x_dbe          : 1;  /**< [ 43: 43](R/W1C/H) Double-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t plut_sdma_dbe         : 1;  /**< [ 44: 44](R/W1C/H) Double-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t sdma_dbe              : 1;  /**< [ 45: 45](R/W1C/H) Double-bit ECC error detected on SDMA RAM. */
        uint64_t reserved_46_47        : 2;
        uint64_t runt_pkt              : 1;  /**< [ 48: 48](R/W1C/H) Runt packet received and captured. */
        uint64_t hts_exists            : 1;  /**< [ 49: 49](R/W1C/H) A token received from the SDE had the HTS flag set. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_int_en_w1c_s cn; */
};
typedef union bdk_tns_rdma_nb_int_en_w1c bdk_tns_rdma_nb_int_en_w1c_t;

#define BDK_TNS_RDMA_NB_INT_EN_W1C BDK_TNS_RDMA_NB_INT_EN_W1C_FUNC()
static inline uint64_t BDK_TNS_RDMA_NB_INT_EN_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_INT_EN_W1C_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842042000130ll;
    __bdk_csr_fatal("TNS_RDMA_NB_INT_EN_W1C", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_INT_EN_W1C bdk_tns_rdma_nb_int_en_w1c_t
#define bustype_BDK_TNS_RDMA_NB_INT_EN_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_INT_EN_W1C "TNS_RDMA_NB_INT_EN_W1C"
#define device_bar_BDK_TNS_RDMA_NB_INT_EN_W1C 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_INT_EN_W1C 0
#define arguments_BDK_TNS_RDMA_NB_INT_EN_W1C -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_int_en_w1s
 *
 * TNS RDMA Interrupt Enable (Read/Write-1-Set) Register
 * RDMA Interrupt Enable Register.
 */
union bdk_tns_rdma_nb_int_en_w1s
{
    uint64_t u;
    struct bdk_tns_rdma_nb_int_en_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t hts_exists            : 1;  /**< [ 49: 49](R/W1S/H) A token received from the SDE had the HTS flag set. */
        uint64_t runt_pkt              : 1;  /**< [ 48: 48](R/W1S/H) Runt packet received and captured. */
        uint64_t reserved_46_47        : 2;
        uint64_t sdma_dbe              : 1;  /**< [ 45: 45](R/W1S/H) Double-bit ECC error detected on SDMA RAM. */
        uint64_t plut_sdma_dbe         : 1;  /**< [ 44: 44](R/W1S/H) Double-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t plut_p2x_dbe          : 1;  /**< [ 43: 43](R/W1S/H) Double-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 42: 42](R/W1S/H) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_nici_dbe          : 2;  /**< [ 41: 40](R/W1S/H) Double-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lmacts_dbe        : 8;  /**< [ 39: 32](R/W1S/H) Double-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_lmac_dbe          : 8;  /**< [ 31: 24](R/W1S/H) Double-bit ECC error detected on PKT_LMAC[7..0] RAM */
        uint64_t reserved_22_23        : 2;
        uint64_t sdma_sbe              : 1;  /**< [ 21: 21](R/W1S/H) Single-bit ECC error detected on SDMA RAM. */
        uint64_t plut_sdma_sbe         : 1;  /**< [ 20: 20](R/W1S/H) Single-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t plut_p2x_sbe          : 1;  /**< [ 19: 19](R/W1S/H) Single-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [ 18: 18](R/W1S/H) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_nici_sbe          : 2;  /**< [ 17: 16](R/W1S/H) Single-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lmacts_sbe        : 8;  /**< [ 15:  8](R/W1S/H) Single-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_lmac_sbe          : 8;  /**< [  7:  0](R/W1S/H) Single-bit ECC error detected on PKT_LMAC[7..0] RAM. */
#else /* Word 0 - Little Endian */
        uint64_t pkt_lmac_sbe          : 8;  /**< [  7:  0](R/W1S/H) Single-bit ECC error detected on PKT_LMAC[7..0] RAM. */
        uint64_t pkt_lmacts_sbe        : 8;  /**< [ 15:  8](R/W1S/H) Single-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_nici_sbe          : 2;  /**< [ 17: 16](R/W1S/H) Single-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [ 18: 18](R/W1S/H) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t plut_p2x_sbe          : 1;  /**< [ 19: 19](R/W1S/H) Single-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t plut_sdma_sbe         : 1;  /**< [ 20: 20](R/W1S/H) Single-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t sdma_sbe              : 1;  /**< [ 21: 21](R/W1S/H) Single-bit ECC error detected on SDMA RAM. */
        uint64_t reserved_22_23        : 2;
        uint64_t pkt_lmac_dbe          : 8;  /**< [ 31: 24](R/W1S/H) Double-bit ECC error detected on PKT_LMAC[7..0] RAM */
        uint64_t pkt_lmacts_dbe        : 8;  /**< [ 39: 32](R/W1S/H) Double-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_nici_dbe          : 2;  /**< [ 41: 40](R/W1S/H) Double-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 42: 42](R/W1S/H) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t plut_p2x_dbe          : 1;  /**< [ 43: 43](R/W1S/H) Double-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t plut_sdma_dbe         : 1;  /**< [ 44: 44](R/W1S/H) Double-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t sdma_dbe              : 1;  /**< [ 45: 45](R/W1S/H) Double-bit ECC error detected on SDMA RAM. */
        uint64_t reserved_46_47        : 2;
        uint64_t runt_pkt              : 1;  /**< [ 48: 48](R/W1S/H) Runt packet received and captured. */
        uint64_t hts_exists            : 1;  /**< [ 49: 49](R/W1S/H) A token received from the SDE had the HTS flag set. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_int_en_w1s_s cn; */
};
typedef union bdk_tns_rdma_nb_int_en_w1s bdk_tns_rdma_nb_int_en_w1s_t;

#define BDK_TNS_RDMA_NB_INT_EN_W1S BDK_TNS_RDMA_NB_INT_EN_W1S_FUNC()
static inline uint64_t BDK_TNS_RDMA_NB_INT_EN_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_INT_EN_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842042000120ll;
    __bdk_csr_fatal("TNS_RDMA_NB_INT_EN_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_INT_EN_W1S bdk_tns_rdma_nb_int_en_w1s_t
#define bustype_BDK_TNS_RDMA_NB_INT_EN_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_INT_EN_W1S "TNS_RDMA_NB_INT_EN_W1S"
#define device_bar_BDK_TNS_RDMA_NB_INT_EN_W1S 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_INT_EN_W1S 0
#define arguments_BDK_TNS_RDMA_NB_INT_EN_W1S -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_int_fen_w1c
 *
 * TNS RDMA Interrupt First Enable (Read/Write-1-Clear) Register
 * RDMA Interrupt First Enable Register.
 */
union bdk_tns_rdma_nb_int_fen_w1c
{
    uint64_t u;
    struct bdk_tns_rdma_nb_int_fen_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t hts_exists            : 1;  /**< [ 49: 49](R/W1C) A token received from the SDE had the HTS flag set. */
        uint64_t runt_pkt              : 1;  /**< [ 48: 48](R/W1C) Runt packet received and captured. */
        uint64_t reserved_46_47        : 2;
        uint64_t sdma_dbe              : 1;  /**< [ 45: 45](R/W1C) Double-bit ECC error detected on SDMA RAM. */
        uint64_t plut_sdma_dbe         : 1;  /**< [ 44: 44](R/W1C) Double-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t plut_p2x_dbe          : 1;  /**< [ 43: 43](R/W1C) Double-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 42: 42](R/W1C) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_nici_dbe          : 2;  /**< [ 41: 40](R/W1C) Double-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lmacts_dbe        : 8;  /**< [ 39: 32](R/W1C) Double-bit ECC error detected on PKT_LMACTS[1..0] RAM. */
        uint64_t pkt_lmac_dbe          : 8;  /**< [ 31: 24](R/W1C) Double-bit ECC error detected on PKT_LMAC[7..0] RAM. */
        uint64_t reserved_22_23        : 2;
        uint64_t sdma_sbe              : 1;  /**< [ 21: 21](R/W1C) Single-bit ECC error detected on SDMA RAM. */
        uint64_t plut_sdma_sbe         : 1;  /**< [ 20: 20](R/W1C) Single-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t plut_p2x_sbe          : 1;  /**< [ 19: 19](R/W1C) Single-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [ 18: 18](R/W1C) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_nici_sbe          : 2;  /**< [ 17: 16](R/W1C) Single-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lmacts_sbe        : 8;  /**< [ 15:  8](R/W1C) Single-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_lmac_sbe          : 8;  /**< [  7:  0](R/W1C) Single-bit ECC error detected on PKT_LMAC[7..0] RAM. */
#else /* Word 0 - Little Endian */
        uint64_t pkt_lmac_sbe          : 8;  /**< [  7:  0](R/W1C) Single-bit ECC error detected on PKT_LMAC[7..0] RAM. */
        uint64_t pkt_lmacts_sbe        : 8;  /**< [ 15:  8](R/W1C) Single-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_nici_sbe          : 2;  /**< [ 17: 16](R/W1C) Single-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [ 18: 18](R/W1C) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t plut_p2x_sbe          : 1;  /**< [ 19: 19](R/W1C) Single-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t plut_sdma_sbe         : 1;  /**< [ 20: 20](R/W1C) Single-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t sdma_sbe              : 1;  /**< [ 21: 21](R/W1C) Single-bit ECC error detected on SDMA RAM. */
        uint64_t reserved_22_23        : 2;
        uint64_t pkt_lmac_dbe          : 8;  /**< [ 31: 24](R/W1C) Double-bit ECC error detected on PKT_LMAC[7..0] RAM. */
        uint64_t pkt_lmacts_dbe        : 8;  /**< [ 39: 32](R/W1C) Double-bit ECC error detected on PKT_LMACTS[1..0] RAM. */
        uint64_t pkt_nici_dbe          : 2;  /**< [ 41: 40](R/W1C) Double-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 42: 42](R/W1C) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t plut_p2x_dbe          : 1;  /**< [ 43: 43](R/W1C) Double-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t plut_sdma_dbe         : 1;  /**< [ 44: 44](R/W1C) Double-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t sdma_dbe              : 1;  /**< [ 45: 45](R/W1C) Double-bit ECC error detected on SDMA RAM. */
        uint64_t reserved_46_47        : 2;
        uint64_t runt_pkt              : 1;  /**< [ 48: 48](R/W1C) Runt packet received and captured. */
        uint64_t hts_exists            : 1;  /**< [ 49: 49](R/W1C) A token received from the SDE had the HTS flag set. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_int_fen_w1c_s cn; */
};
typedef union bdk_tns_rdma_nb_int_fen_w1c bdk_tns_rdma_nb_int_fen_w1c_t;

#define BDK_TNS_RDMA_NB_INT_FEN_W1C BDK_TNS_RDMA_NB_INT_FEN_W1C_FUNC()
static inline uint64_t BDK_TNS_RDMA_NB_INT_FEN_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_INT_FEN_W1C_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842042000160ll;
    __bdk_csr_fatal("TNS_RDMA_NB_INT_FEN_W1C", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_INT_FEN_W1C bdk_tns_rdma_nb_int_fen_w1c_t
#define bustype_BDK_TNS_RDMA_NB_INT_FEN_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_INT_FEN_W1C "TNS_RDMA_NB_INT_FEN_W1C"
#define device_bar_BDK_TNS_RDMA_NB_INT_FEN_W1C 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_INT_FEN_W1C 0
#define arguments_BDK_TNS_RDMA_NB_INT_FEN_W1C -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_int_fen_w1s
 *
 * TNS RDMA Interrupt First Enable (Read/Write-1-Set) Register
 * RDMA Interrupt First Enable Register.
 */
union bdk_tns_rdma_nb_int_fen_w1s
{
    uint64_t u;
    struct bdk_tns_rdma_nb_int_fen_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t hts_exists            : 1;  /**< [ 49: 49](R/W1S) A token received from the SDE had the HTS flag set. */
        uint64_t runt_pkt              : 1;  /**< [ 48: 48](R/W1S) Runt packet received and captured. */
        uint64_t reserved_46_47        : 2;
        uint64_t sdma_dbe              : 1;  /**< [ 45: 45](R/W1S) Double-bit ECC error detected on SDMA RAM. */
        uint64_t plut_sdma_dbe         : 1;  /**< [ 44: 44](R/W1S) Double-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t plut_p2x_dbe          : 1;  /**< [ 43: 43](R/W1S) Double-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 42: 42](R/W1S) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_nici_dbe          : 2;  /**< [ 41: 40](R/W1S) Double-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lmacts_dbe        : 8;  /**< [ 39: 32](R/W1S) Double-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_lmac_dbe          : 8;  /**< [ 31: 24](R/W1S) Double-bit ECC error detected on PKT_LMAC[7..0] RAM. */
        uint64_t reserved_22_23        : 2;
        uint64_t sdma_sbe              : 1;  /**< [ 21: 21](R/W1S) Single-bit ECC error detected on SDMA RAM. */
        uint64_t plut_sdma_sbe         : 1;  /**< [ 20: 20](R/W1S) Single-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t plut_p2x_sbe          : 1;  /**< [ 19: 19](R/W1S) Single-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [ 18: 18](R/W1S) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_nici_sbe          : 2;  /**< [ 17: 16](R/W1S) Single-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lmacts_sbe        : 8;  /**< [ 15:  8](R/W1S) Single-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_lmac_sbe          : 8;  /**< [  7:  0](R/W1S) Single-bit ECC error detected on PKT_LMAC[7..0] RAM. */
#else /* Word 0 - Little Endian */
        uint64_t pkt_lmac_sbe          : 8;  /**< [  7:  0](R/W1S) Single-bit ECC error detected on PKT_LMAC[7..0] RAM. */
        uint64_t pkt_lmacts_sbe        : 8;  /**< [ 15:  8](R/W1S) Single-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_nici_sbe          : 2;  /**< [ 17: 16](R/W1S) Single-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [ 18: 18](R/W1S) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t plut_p2x_sbe          : 1;  /**< [ 19: 19](R/W1S) Single-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t plut_sdma_sbe         : 1;  /**< [ 20: 20](R/W1S) Single-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t sdma_sbe              : 1;  /**< [ 21: 21](R/W1S) Single-bit ECC error detected on SDMA RAM. */
        uint64_t reserved_22_23        : 2;
        uint64_t pkt_lmac_dbe          : 8;  /**< [ 31: 24](R/W1S) Double-bit ECC error detected on PKT_LMAC[7..0] RAM. */
        uint64_t pkt_lmacts_dbe        : 8;  /**< [ 39: 32](R/W1S) Double-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_nici_dbe          : 2;  /**< [ 41: 40](R/W1S) Double-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 42: 42](R/W1S) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t plut_p2x_dbe          : 1;  /**< [ 43: 43](R/W1S) Double-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t plut_sdma_dbe         : 1;  /**< [ 44: 44](R/W1S) Double-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t sdma_dbe              : 1;  /**< [ 45: 45](R/W1S) Double-bit ECC error detected on SDMA RAM. */
        uint64_t reserved_46_47        : 2;
        uint64_t runt_pkt              : 1;  /**< [ 48: 48](R/W1S) Runt packet received and captured. */
        uint64_t hts_exists            : 1;  /**< [ 49: 49](R/W1S) A token received from the SDE had the HTS flag set. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_int_fen_w1s_s cn; */
};
typedef union bdk_tns_rdma_nb_int_fen_w1s bdk_tns_rdma_nb_int_fen_w1s_t;

#define BDK_TNS_RDMA_NB_INT_FEN_W1S BDK_TNS_RDMA_NB_INT_FEN_W1S_FUNC()
static inline uint64_t BDK_TNS_RDMA_NB_INT_FEN_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_INT_FEN_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842042000150ll;
    __bdk_csr_fatal("TNS_RDMA_NB_INT_FEN_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_INT_FEN_W1S bdk_tns_rdma_nb_int_fen_w1s_t
#define bustype_BDK_TNS_RDMA_NB_INT_FEN_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_INT_FEN_W1S "TNS_RDMA_NB_INT_FEN_W1S"
#define device_bar_BDK_TNS_RDMA_NB_INT_FEN_W1S 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_INT_FEN_W1S 0
#define arguments_BDK_TNS_RDMA_NB_INT_FEN_W1S -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_int_fstat
 *
 * TNS RDMA Interrupt First Status Register
 * RDMA Interrupt First Status Register.
 */
union bdk_tns_rdma_nb_int_fstat
{
    uint64_t u;
    struct bdk_tns_rdma_nb_int_fstat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t hts_exists            : 1;  /**< [ 49: 49](RO/H) A token received from the SDE had the HTS flag set. */
        uint64_t runt_pkt              : 1;  /**< [ 48: 48](RO/H) Runt packet received and captured. */
        uint64_t reserved_46_47        : 2;
        uint64_t sdma_dbe              : 1;  /**< [ 45: 45](RO/H) Double-bit ECC error detected on SDMA RAM. */
        uint64_t plut_sdma_dbe         : 1;  /**< [ 44: 44](RO/H) Double-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t plut_p2x_dbe          : 1;  /**< [ 43: 43](RO/H) Double-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 42: 42](RO/H) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_nici_dbe          : 2;  /**< [ 41: 40](RO/H) Double-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lmacts_dbe        : 8;  /**< [ 39: 32](RO/H) Double-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_lmac_dbe          : 8;  /**< [ 31: 24](RO/H) Double-bit ECC error detected on PKT_LMAC[7..0] RAM. */
        uint64_t reserved_22_23        : 2;
        uint64_t sdma_sbe              : 1;  /**< [ 21: 21](RO/H) Single-bit ECC error detected on SDMA RAM. */
        uint64_t plut_sdma_sbe         : 1;  /**< [ 20: 20](RO/H) Single-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t plut_p2x_sbe          : 1;  /**< [ 19: 19](RO/H) Single-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [ 18: 18](RO/H) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_nici_sbe          : 2;  /**< [ 17: 16](RO/H) Single-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lmacts_sbe        : 8;  /**< [ 15:  8](RO/H) Single-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_lmac_sbe          : 8;  /**< [  7:  0](RO/H) Single-bit ECC error detected on PKT_LMAC[7..0] RAM. */
#else /* Word 0 - Little Endian */
        uint64_t pkt_lmac_sbe          : 8;  /**< [  7:  0](RO/H) Single-bit ECC error detected on PKT_LMAC[7..0] RAM. */
        uint64_t pkt_lmacts_sbe        : 8;  /**< [ 15:  8](RO/H) Single-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_nici_sbe          : 2;  /**< [ 17: 16](RO/H) Single-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [ 18: 18](RO/H) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t plut_p2x_sbe          : 1;  /**< [ 19: 19](RO/H) Single-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t plut_sdma_sbe         : 1;  /**< [ 20: 20](RO/H) Single-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t sdma_sbe              : 1;  /**< [ 21: 21](RO/H) Single-bit ECC error detected on SDMA RAM. */
        uint64_t reserved_22_23        : 2;
        uint64_t pkt_lmac_dbe          : 8;  /**< [ 31: 24](RO/H) Double-bit ECC error detected on PKT_LMAC[7..0] RAM. */
        uint64_t pkt_lmacts_dbe        : 8;  /**< [ 39: 32](RO/H) Double-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_nici_dbe          : 2;  /**< [ 41: 40](RO/H) Double-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 42: 42](RO/H) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t plut_p2x_dbe          : 1;  /**< [ 43: 43](RO/H) Double-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t plut_sdma_dbe         : 1;  /**< [ 44: 44](RO/H) Double-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t sdma_dbe              : 1;  /**< [ 45: 45](RO/H) Double-bit ECC error detected on SDMA RAM. */
        uint64_t reserved_46_47        : 2;
        uint64_t runt_pkt              : 1;  /**< [ 48: 48](RO/H) Runt packet received and captured. */
        uint64_t hts_exists            : 1;  /**< [ 49: 49](RO/H) A token received from the SDE had the HTS flag set. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_int_fstat_s cn; */
};
typedef union bdk_tns_rdma_nb_int_fstat bdk_tns_rdma_nb_int_fstat_t;

#define BDK_TNS_RDMA_NB_INT_FSTAT BDK_TNS_RDMA_NB_INT_FSTAT_FUNC()
static inline uint64_t BDK_TNS_RDMA_NB_INT_FSTAT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_INT_FSTAT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842042000140ll;
    __bdk_csr_fatal("TNS_RDMA_NB_INT_FSTAT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_INT_FSTAT bdk_tns_rdma_nb_int_fstat_t
#define bustype_BDK_TNS_RDMA_NB_INT_FSTAT BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_INT_FSTAT "TNS_RDMA_NB_INT_FSTAT"
#define device_bar_BDK_TNS_RDMA_NB_INT_FSTAT 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_INT_FSTAT 0
#define arguments_BDK_TNS_RDMA_NB_INT_FSTAT -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_int_stat_w1c
 *
 * TNS RDMA Interrupt Status (Read/Write-1-Clear) Register
 * RDMA Interrupt Status Register.
 */
union bdk_tns_rdma_nb_int_stat_w1c
{
    uint64_t u;
    struct bdk_tns_rdma_nb_int_stat_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t hts_exists            : 1;  /**< [ 49: 49](R/W1C/H) A token received from the SDE had the HTS flag set. */
        uint64_t runt_pkt              : 1;  /**< [ 48: 48](R/W1C/H) Runt packet received and captured. */
        uint64_t reserved_46_47        : 2;
        uint64_t sdma_dbe              : 1;  /**< [ 45: 45](R/W1C/H) Double-bit ECC error detected on SDMA RAM. */
        uint64_t plut_sdma_dbe         : 1;  /**< [ 44: 44](R/W1C/H) Double-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t plut_p2x_dbe          : 1;  /**< [ 43: 43](R/W1C/H) Double-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 42: 42](R/W1C/H) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_nici_dbe          : 2;  /**< [ 41: 40](R/W1C/H) Double-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lmacts_dbe        : 8;  /**< [ 39: 32](R/W1C/H) Double-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_lmac_dbe          : 8;  /**< [ 31: 24](R/W1C/H) Double-bit ECC error detected on PKT_LMAC[7..0] RAM */
        uint64_t reserved_22_23        : 2;
        uint64_t sdma_sbe              : 1;  /**< [ 21: 21](R/W1C/H) Single-bit ECC error detected on SDMA RAM. */
        uint64_t plut_sdma_sbe         : 1;  /**< [ 20: 20](R/W1C/H) Single-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t plut_p2x_sbe          : 1;  /**< [ 19: 19](R/W1C/H) Single-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [ 18: 18](R/W1C/H) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_nici_sbe          : 2;  /**< [ 17: 16](R/W1C/H) Single-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lmacts_sbe        : 8;  /**< [ 15:  8](R/W1C/H) Single-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_lmac_sbe          : 8;  /**< [  7:  0](R/W1C/H) Single-bit ECC error detected on PKT_LMAC[7..0] RAM. */
#else /* Word 0 - Little Endian */
        uint64_t pkt_lmac_sbe          : 8;  /**< [  7:  0](R/W1C/H) Single-bit ECC error detected on PKT_LMAC[7..0] RAM. */
        uint64_t pkt_lmacts_sbe        : 8;  /**< [ 15:  8](R/W1C/H) Single-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_nici_sbe          : 2;  /**< [ 17: 16](R/W1C/H) Single-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [ 18: 18](R/W1C/H) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t plut_p2x_sbe          : 1;  /**< [ 19: 19](R/W1C/H) Single-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t plut_sdma_sbe         : 1;  /**< [ 20: 20](R/W1C/H) Single-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t sdma_sbe              : 1;  /**< [ 21: 21](R/W1C/H) Single-bit ECC error detected on SDMA RAM. */
        uint64_t reserved_22_23        : 2;
        uint64_t pkt_lmac_dbe          : 8;  /**< [ 31: 24](R/W1C/H) Double-bit ECC error detected on PKT_LMAC[7..0] RAM */
        uint64_t pkt_lmacts_dbe        : 8;  /**< [ 39: 32](R/W1C/H) Double-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_nici_dbe          : 2;  /**< [ 41: 40](R/W1C/H) Double-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 42: 42](R/W1C/H) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t plut_p2x_dbe          : 1;  /**< [ 43: 43](R/W1C/H) Double-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t plut_sdma_dbe         : 1;  /**< [ 44: 44](R/W1C/H) Double-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t sdma_dbe              : 1;  /**< [ 45: 45](R/W1C/H) Double-bit ECC error detected on SDMA RAM. */
        uint64_t reserved_46_47        : 2;
        uint64_t runt_pkt              : 1;  /**< [ 48: 48](R/W1C/H) Runt packet received and captured. */
        uint64_t hts_exists            : 1;  /**< [ 49: 49](R/W1C/H) A token received from the SDE had the HTS flag set. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_int_stat_w1c_s cn; */
};
typedef union bdk_tns_rdma_nb_int_stat_w1c bdk_tns_rdma_nb_int_stat_w1c_t;

#define BDK_TNS_RDMA_NB_INT_STAT_W1C BDK_TNS_RDMA_NB_INT_STAT_W1C_FUNC()
static inline uint64_t BDK_TNS_RDMA_NB_INT_STAT_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_INT_STAT_W1C_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842042000110ll;
    __bdk_csr_fatal("TNS_RDMA_NB_INT_STAT_W1C", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_INT_STAT_W1C bdk_tns_rdma_nb_int_stat_w1c_t
#define bustype_BDK_TNS_RDMA_NB_INT_STAT_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_INT_STAT_W1C "TNS_RDMA_NB_INT_STAT_W1C"
#define device_bar_BDK_TNS_RDMA_NB_INT_STAT_W1C 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_INT_STAT_W1C 0
#define arguments_BDK_TNS_RDMA_NB_INT_STAT_W1C -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_int_stat_w1s
 *
 * TNS RDMA Interrupt Status (Read/Write-1-Set) Register
 * RDMA Interrupt Status Register.
 */
union bdk_tns_rdma_nb_int_stat_w1s
{
    uint64_t u;
    struct bdk_tns_rdma_nb_int_stat_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t hts_exists            : 1;  /**< [ 49: 49](R/W1S/H) A token received from the SDE had the HTS flag set. */
        uint64_t runt_pkt              : 1;  /**< [ 48: 48](R/W1S/H) Runt packet received and captured. */
        uint64_t reserved_46_47        : 2;
        uint64_t sdma_dbe              : 1;  /**< [ 45: 45](R/W1S/H) Double-bit ECC error detected on SDMA RAM. */
        uint64_t plut_sdma_dbe         : 1;  /**< [ 44: 44](R/W1S/H) Double-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t plut_p2x_dbe          : 1;  /**< [ 43: 43](R/W1S/H) Double-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 42: 42](R/W1S/H) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_nici_dbe          : 2;  /**< [ 41: 40](R/W1S/H) Double-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lmacts_dbe        : 8;  /**< [ 39: 32](R/W1S/H) Double-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_lmac_dbe          : 8;  /**< [ 31: 24](R/W1S/H) Double-bit ECC error detected on PKT_LMAC[7..0] RAM. */
        uint64_t reserved_22_23        : 2;
        uint64_t sdma_sbe              : 1;  /**< [ 21: 21](R/W1S/H) Single-bit ECC error detected on SDMA RAM. */
        uint64_t plut_sdma_sbe         : 1;  /**< [ 20: 20](R/W1S/H) Single-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t plut_p2x_sbe          : 1;  /**< [ 19: 19](R/W1S/H) Single-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [ 18: 18](R/W1S/H) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_nici_sbe          : 2;  /**< [ 17: 16](R/W1S/H) Single-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lmacts_sbe        : 8;  /**< [ 15:  8](R/W1S/H) Single-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_lmac_sbe          : 8;  /**< [  7:  0](R/W1S/H) Single-bit ECC error detected on PKT_LMAC[7..0] RAM. */
#else /* Word 0 - Little Endian */
        uint64_t pkt_lmac_sbe          : 8;  /**< [  7:  0](R/W1S/H) Single-bit ECC error detected on PKT_LMAC[7..0] RAM. */
        uint64_t pkt_lmacts_sbe        : 8;  /**< [ 15:  8](R/W1S/H) Single-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_nici_sbe          : 2;  /**< [ 17: 16](R/W1S/H) Single-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [ 18: 18](R/W1S/H) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t plut_p2x_sbe          : 1;  /**< [ 19: 19](R/W1S/H) Single-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t plut_sdma_sbe         : 1;  /**< [ 20: 20](R/W1S/H) Single-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t sdma_sbe              : 1;  /**< [ 21: 21](R/W1S/H) Single-bit ECC error detected on SDMA RAM. */
        uint64_t reserved_22_23        : 2;
        uint64_t pkt_lmac_dbe          : 8;  /**< [ 31: 24](R/W1S/H) Double-bit ECC error detected on PKT_LMAC[7..0] RAM. */
        uint64_t pkt_lmacts_dbe        : 8;  /**< [ 39: 32](R/W1S/H) Double-bit ECC error detected on PKT_LMACTS[7..0] RAM. */
        uint64_t pkt_nici_dbe          : 2;  /**< [ 41: 40](R/W1S/H) Double-bit ECC error detected on PKT_NICI[1..0] RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 42: 42](R/W1S/H) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t plut_p2x_dbe          : 1;  /**< [ 43: 43](R/W1S/H) Double-bit ECC error detected on PLUT_P2X RAM. */
        uint64_t plut_sdma_dbe         : 1;  /**< [ 44: 44](R/W1S/H) Double-bit ECC error detected on PLUT_SDMA RAM. */
        uint64_t sdma_dbe              : 1;  /**< [ 45: 45](R/W1S/H) Double-bit ECC error detected on SDMA RAM. */
        uint64_t reserved_46_47        : 2;
        uint64_t runt_pkt              : 1;  /**< [ 48: 48](R/W1S/H) Runt packet received and captured. */
        uint64_t hts_exists            : 1;  /**< [ 49: 49](R/W1S/H) A token received from the SDE had the HTS flag set. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_int_stat_w1s_s cn; */
};
typedef union bdk_tns_rdma_nb_int_stat_w1s bdk_tns_rdma_nb_int_stat_w1s_t;

#define BDK_TNS_RDMA_NB_INT_STAT_W1S BDK_TNS_RDMA_NB_INT_STAT_W1S_FUNC()
static inline uint64_t BDK_TNS_RDMA_NB_INT_STAT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_INT_STAT_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842042000100ll;
    __bdk_csr_fatal("TNS_RDMA_NB_INT_STAT_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_INT_STAT_W1S bdk_tns_rdma_nb_int_stat_w1s_t
#define bustype_BDK_TNS_RDMA_NB_INT_STAT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_INT_STAT_W1S "TNS_RDMA_NB_INT_STAT_W1S"
#define device_bar_BDK_TNS_RDMA_NB_INT_STAT_W1S 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_INT_STAT_W1S 0
#define arguments_BDK_TNS_RDMA_NB_INT_STAT_W1S -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_lmac#_rpkt_sz
 *
 * TNS RDMA LMAC Runt Packet Size Register
 */
union bdk_tns_rdma_nb_lmacx_rpkt_sz
{
    uint64_t u;
    struct bdk_tns_rdma_nb_lmacx_rpkt_sz_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t bytes                 : 8;  /**< [  7:  0](R/W) Hardware will drop packets arriving from the LMAC if the size is
                                                                 less than or equal to the programmed value.
                                                                 Packets received from the LMAC with size greater than this will be passed to the
                                                                 network switch for processing.
                                                                 Packets with a size that is equal or less will be marked as runt, dropped, and counted.
                                                                 The prepended timestamp (if present) is not counted when determining the
                                                                 size of an arriving packet.
                                                                 Dropped runt packets are counted at TNS_RDMA_NB_RUNT_CNT(0..7). */
#else /* Word 0 - Little Endian */
        uint64_t bytes                 : 8;  /**< [  7:  0](R/W) Hardware will drop packets arriving from the LMAC if the size is
                                                                 less than or equal to the programmed value.
                                                                 Packets received from the LMAC with size greater than this will be passed to the
                                                                 network switch for processing.
                                                                 Packets with a size that is equal or less will be marked as runt, dropped, and counted.
                                                                 The prepended timestamp (if present) is not counted when determining the
                                                                 size of an arriving packet.
                                                                 Dropped runt packets are counted at TNS_RDMA_NB_RUNT_CNT(0..7). */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_lmacx_rpkt_sz_s cn; */
};
typedef union bdk_tns_rdma_nb_lmacx_rpkt_sz bdk_tns_rdma_nb_lmacx_rpkt_sz_t;

static inline uint64_t BDK_TNS_RDMA_NB_LMACX_RPKT_SZ(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_LMACX_RPKT_SZ(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=7))
        return 0x842042000a00ll + 0x10ll * ((a) & 0x7);
    __bdk_csr_fatal("TNS_RDMA_NB_LMACX_RPKT_SZ", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_LMACX_RPKT_SZ(a) bdk_tns_rdma_nb_lmacx_rpkt_sz_t
#define bustype_BDK_TNS_RDMA_NB_LMACX_RPKT_SZ(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_LMACX_RPKT_SZ(a) "TNS_RDMA_NB_LMACX_RPKT_SZ"
#define device_bar_BDK_TNS_RDMA_NB_LMACX_RPKT_SZ(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_LMACX_RPKT_SZ(a) (a)
#define arguments_BDK_TNS_RDMA_NB_LMACX_RPKT_SZ(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_lmac_plut#
 *
 * TNS RDMA LMAC Port LUT Registers
 * Translates the arriving LMAC physical port number to an 8-bit logical port number.
 * Some physical to logical aliasing will occur as there are more physical
 * ports than the 8-bit logical port width allows:
 *   * 256 NIC channels
 *   * 8 LMAC ports
 *   * 1 Loopback port
 * Use of logical port numbers 137 through 255 may result in unintended behavior.
 *
 * During operation, hardware only performs reads from this table and addresses this table as:
 * Address = {BGX(1),LMAC(2)}
 */
union bdk_tns_rdma_nb_lmac_plutx
{
    uint64_t u;
    struct bdk_tns_rdma_nb_lmac_plutx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t logical_port          : 8;  /**< [  7:  0](R/W/H) Logical port number for the specified LMAC physical port number. */
#else /* Word 0 - Little Endian */
        uint64_t logical_port          : 8;  /**< [  7:  0](R/W/H) Logical port number for the specified LMAC physical port number. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_lmac_plutx_s cn; */
};
typedef union bdk_tns_rdma_nb_lmac_plutx bdk_tns_rdma_nb_lmac_plutx_t;

static inline uint64_t BDK_TNS_RDMA_NB_LMAC_PLUTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_LMAC_PLUTX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=7))
        return 0x842042002000ll + 0x10ll * ((a) & 0x7);
    __bdk_csr_fatal("TNS_RDMA_NB_LMAC_PLUTX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_LMAC_PLUTX(a) bdk_tns_rdma_nb_lmac_plutx_t
#define bustype_BDK_TNS_RDMA_NB_LMAC_PLUTX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_LMAC_PLUTX(a) "TNS_RDMA_NB_LMAC_PLUTX"
#define device_bar_BDK_TNS_RDMA_NB_LMAC_PLUTX(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_LMAC_PLUTX(a) (a)
#define arguments_BDK_TNS_RDMA_NB_LMAC_PLUTX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_loopback_plut
 *
 * TNS RDMA Loopback Port LUT Register
 * Translates the arriving loopback physical port number to an 8-bit logical port number.
 * Some physical to logical aliasing will occur as there are more physical
 * ports than the 8-bit logical port width allows:
 *   * 256 NIC channels
 *   * 8 LMAC ports
 *   * 1 Loopback port
 * Use of logical port numbers 137 through 255 may result in unintended behavior.
 */
union bdk_tns_rdma_nb_loopback_plut
{
    uint64_t u;
    struct bdk_tns_rdma_nb_loopback_plut_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t logical_port          : 8;  /**< [  7:  0](R/W/H) Logical port number for the loopback physical port number. */
#else /* Word 0 - Little Endian */
        uint64_t logical_port          : 8;  /**< [  7:  0](R/W/H) Logical port number for the loopback physical port number. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_loopback_plut_s cn; */
};
typedef union bdk_tns_rdma_nb_loopback_plut bdk_tns_rdma_nb_loopback_plut_t;

#define BDK_TNS_RDMA_NB_LOOPBACK_PLUT BDK_TNS_RDMA_NB_LOOPBACK_PLUT_FUNC()
static inline uint64_t BDK_TNS_RDMA_NB_LOOPBACK_PLUT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_LOOPBACK_PLUT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842042002080ll;
    __bdk_csr_fatal("TNS_RDMA_NB_LOOPBACK_PLUT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_LOOPBACK_PLUT bdk_tns_rdma_nb_loopback_plut_t
#define bustype_BDK_TNS_RDMA_NB_LOOPBACK_PLUT BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_LOOPBACK_PLUT "TNS_RDMA_NB_LOOPBACK_PLUT"
#define device_bar_BDK_TNS_RDMA_NB_LOOPBACK_PLUT 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_LOOPBACK_PLUT 0
#define arguments_BDK_TNS_RDMA_NB_LOOPBACK_PLUT -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_lp_plut#
 *
 * TNS RDMA Logical to Physical Port LUT Registers
 * Translates the 8-bit logical port number to a 4-bit physical port, indicating
 * the physical port on which the packet was originally received.
 * This table must be programmed to reverse map the contents of the following Tables:
 *   * TNS_NIC_PLUT(0..255)
 *   * TNS_LMAC_PLUT(0..7)
 *   * TNS_LOOPBACK_PLUT
 * Values have the meaning as defined in TNS_PHYS_PORT_E.
 * Rows 137 through 255 are unused.
 */
union bdk_tns_rdma_nb_lp_plutx
{
    uint64_t u;
    struct bdk_tns_rdma_nb_lp_plutx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t physical_port         : 4;  /**< [  3:  0](R/W/H) Physical port number associated with the logical port number. */
#else /* Word 0 - Little Endian */
        uint64_t physical_port         : 4;  /**< [  3:  0](R/W/H) Physical port number associated with the logical port number. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_lp_plutx_s cn; */
};
typedef union bdk_tns_rdma_nb_lp_plutx bdk_tns_rdma_nb_lp_plutx_t;

static inline uint64_t BDK_TNS_RDMA_NB_LP_PLUTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_LP_PLUTX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=255))
        return 0x842042003000ll + 0x10ll * ((a) & 0xff);
    __bdk_csr_fatal("TNS_RDMA_NB_LP_PLUTX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_LP_PLUTX(a) bdk_tns_rdma_nb_lp_plutx_t
#define bustype_BDK_TNS_RDMA_NB_LP_PLUTX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_LP_PLUTX(a) "TNS_RDMA_NB_LP_PLUTX"
#define device_bar_BDK_TNS_RDMA_NB_LP_PLUTX(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_LP_PLUTX(a) (a)
#define arguments_BDK_TNS_RDMA_NB_LP_PLUTX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_nic_c_cdt_pnd#
 *
 * INTERNAL: TNS RDMA NIC Channel Credit Message Pending Register
 */
union bdk_tns_rdma_nb_nic_c_cdt_pndx
{
    uint64_t u;
    struct bdk_tns_rdma_nb_nic_c_cdt_pndx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](RO/H) A credit return message is pending to be sent for the channel. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](RO/H) A credit return message is pending to be sent for the channel. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_nic_c_cdt_pndx_s cn; */
};
typedef union bdk_tns_rdma_nb_nic_c_cdt_pndx bdk_tns_rdma_nb_nic_c_cdt_pndx_t;

static inline uint64_t BDK_TNS_RDMA_NB_NIC_C_CDT_PNDX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_NIC_C_CDT_PNDX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x842042004200ll + 0x10ll * ((a) & 0x3);
    __bdk_csr_fatal("TNS_RDMA_NB_NIC_C_CDT_PNDX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_NIC_C_CDT_PNDX(a) bdk_tns_rdma_nb_nic_c_cdt_pndx_t
#define bustype_BDK_TNS_RDMA_NB_NIC_C_CDT_PNDX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_NIC_C_CDT_PNDX(a) "TNS_RDMA_NB_NIC_C_CDT_PNDX"
#define device_bar_BDK_TNS_RDMA_NB_NIC_C_CDT_PNDX(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_NIC_C_CDT_PNDX(a) (a)
#define arguments_BDK_TNS_RDMA_NB_NIC_C_CDT_PNDX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_nic_plut#
 *
 * TNS RDMA NIC Port LUT Registers
 * Translates the arriving NIC channel to an 8-bit logical port number.
 * Some physical to logical aliasing will occur as there are more physical
 * ports than the 8-bit logical port width allows:
 *   * 256 NIC channels
 *   * 8 LMAC ports
 *   * 1 Loopback port
 * Use of logical port numbers 137 through 255 may result in unintended behavior.
 *
 * During operation, hardware only performs reads from this table and addresses this table as:
 * Address = {NICI(1),channel(7)}
 */
union bdk_tns_rdma_nb_nic_plutx
{
    uint64_t u;
    struct bdk_tns_rdma_nb_nic_plutx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t logical_port          : 8;  /**< [  7:  0](R/W/H) Logical port number for the specified NIC channel. */
#else /* Word 0 - Little Endian */
        uint64_t logical_port          : 8;  /**< [  7:  0](R/W/H) Logical port number for the specified NIC channel. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_nic_plutx_s cn; */
};
typedef union bdk_tns_rdma_nb_nic_plutx bdk_tns_rdma_nb_nic_plutx_t;

static inline uint64_t BDK_TNS_RDMA_NB_NIC_PLUTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_NIC_PLUTX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=255))
        return 0x842042001000ll + 0x10ll * ((a) & 0xff);
    __bdk_csr_fatal("TNS_RDMA_NB_NIC_PLUTX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_NIC_PLUTX(a) bdk_tns_rdma_nb_nic_plutx_t
#define bustype_BDK_TNS_RDMA_NB_NIC_PLUTX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_NIC_PLUTX(a) "TNS_RDMA_NB_NIC_PLUTX"
#define device_bar_BDK_TNS_RDMA_NB_NIC_PLUTX(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_NIC_PLUTX(a) (a)
#define arguments_BDK_TNS_RDMA_NB_NIC_PLUTX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_nici#_rpkt_sz
 *
 * TNS RDMA NICI Runt Packet Size Register
 */
union bdk_tns_rdma_nb_nicix_rpkt_sz
{
    uint64_t u;
    struct bdk_tns_rdma_nb_nicix_rpkt_sz_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t bytes                 : 8;  /**< [  7:  0](R/W) Packets received from NICI with size greater than this will be passed to the
                                                                 network switch for processing.
                                                                 Hardware will flag packets arriving from the NICI if the size is
                                                                 less than or equal to the programmed value.
                                                                 Flagged runt packets are counted at TNS_RDMA_NB_RUNT_CNT(8..9). */
#else /* Word 0 - Little Endian */
        uint64_t bytes                 : 8;  /**< [  7:  0](R/W) Packets received from NICI with size greater than this will be passed to the
                                                                 network switch for processing.
                                                                 Hardware will flag packets arriving from the NICI if the size is
                                                                 less than or equal to the programmed value.
                                                                 Flagged runt packets are counted at TNS_RDMA_NB_RUNT_CNT(8..9). */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_nicix_rpkt_sz_s cn; */
};
typedef union bdk_tns_rdma_nb_nicix_rpkt_sz bdk_tns_rdma_nb_nicix_rpkt_sz_t;

static inline uint64_t BDK_TNS_RDMA_NB_NICIX_RPKT_SZ(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_NICIX_RPKT_SZ(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=1))
        return 0x842042000a80ll + 0x10ll * ((a) & 0x1);
    __bdk_csr_fatal("TNS_RDMA_NB_NICIX_RPKT_SZ", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_NICIX_RPKT_SZ(a) bdk_tns_rdma_nb_nicix_rpkt_sz_t
#define bustype_BDK_TNS_RDMA_NB_NICIX_RPKT_SZ(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_NICIX_RPKT_SZ(a) "TNS_RDMA_NB_NICIX_RPKT_SZ"
#define device_bar_BDK_TNS_RDMA_NB_NICIX_RPKT_SZ(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_NICIX_RPKT_SZ(a) (a)
#define arguments_BDK_TNS_RDMA_NB_NICIX_RPKT_SZ(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_parser
 *
 * INTERNAL: TNS RDMA PARSER Status Register
 *
 * Parser to RDMA status register.
 */
union bdk_tns_rdma_nb_parser
{
    uint64_t u;
    struct bdk_tns_rdma_nb_parser_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t fc                    : 1;  /**< [  0:  0](RO/H) Flow control status from parser. 0 = XOFF. */
#else /* Word 0 - Little Endian */
        uint64_t fc                    : 1;  /**< [  0:  0](RO/H) Flow control status from parser. 0 = XOFF. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_parser_s cn; */
};
typedef union bdk_tns_rdma_nb_parser bdk_tns_rdma_nb_parser_t;

#define BDK_TNS_RDMA_NB_PARSER BDK_TNS_RDMA_NB_PARSER_FUNC()
static inline uint64_t BDK_TNS_RDMA_NB_PARSER_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_PARSER_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X))
        return 0x842042004900ll;
    __bdk_csr_fatal("TNS_RDMA_NB_PARSER", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_PARSER bdk_tns_rdma_nb_parser_t
#define bustype_BDK_TNS_RDMA_NB_PARSER BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_PARSER "TNS_RDMA_NB_PARSER"
#define device_bar_BDK_TNS_RDMA_NB_PARSER 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_PARSER 0
#define arguments_BDK_TNS_RDMA_NB_PARSER -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_path_enable
 *
 * TNS RDMA Path Enable Register
 * When 1, allows the RDMA to accept packets and return credits;
 * when 0, resets state and does not allow receiving of packets from the indicated port.
 */
union bdk_tns_rdma_nb_path_enable
{
    uint64_t u;
    struct bdk_tns_rdma_nb_path_enable_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t nici1_bp              : 1;  /**< [ 19: 19](R/W) When 1, allows back pressure information to be sent to NICI1.
                                                                 When 0, resets state and does not send back pressure information to NICI1. */
        uint64_t nici0_bp              : 1;  /**< [ 18: 18](R/W) When 1, allows back pressure information to be sent to NICI0.
                                                                 When 0, resets state and does not send back pressure information to NICI0. */
        uint64_t bgx1_bp               : 1;  /**< [ 17: 17](R/W) When 1, allows back pressure information to be sent to BGX1.
                                                                 When 0, resets state and does not send back pressure information to BGX1. */
        uint64_t bgx0_bp               : 1;  /**< [ 16: 16](R/W) When 1, allows back pressure information to be sent to BGX0.
                                                                 When 0, resets state and does not send back pressure information to BGX0. */
        uint64_t reserved_11_15        : 5;
        uint64_t loopback              : 1;  /**< [ 10: 10](R/W) When 1, allows packets to be received from loopback and credits to be returned.
                                                                 When 0, resets state and does not allow receiving of packets from the port. */
        uint64_t nici1                 : 1;  /**< [  9:  9](R/W) When 1, allows packets to be received from NICI1 and credits to be returned.
                                                                 When 0, resets state and does not allow receiving of packets from the port. */
        uint64_t nici0                 : 1;  /**< [  8:  8](R/W) When 1, allows packets to be received from NICI0 and credits to be returned.
                                                                 When 0, resets state and does not allow receiving of packets from the port. */
        uint64_t lmac                  : 8;  /**< [  7:  0](R/W) For each bit:
                                                                 When 1, allows packets to be received from the LMAC.
                                                                 When 0, resets state and does not allow receiving of packets from the port. */
#else /* Word 0 - Little Endian */
        uint64_t lmac                  : 8;  /**< [  7:  0](R/W) For each bit:
                                                                 When 1, allows packets to be received from the LMAC.
                                                                 When 0, resets state and does not allow receiving of packets from the port. */
        uint64_t nici0                 : 1;  /**< [  8:  8](R/W) When 1, allows packets to be received from NICI0 and credits to be returned.
                                                                 When 0, resets state and does not allow receiving of packets from the port. */
        uint64_t nici1                 : 1;  /**< [  9:  9](R/W) When 1, allows packets to be received from NICI1 and credits to be returned.
                                                                 When 0, resets state and does not allow receiving of packets from the port. */
        uint64_t loopback              : 1;  /**< [ 10: 10](R/W) When 1, allows packets to be received from loopback and credits to be returned.
                                                                 When 0, resets state and does not allow receiving of packets from the port. */
        uint64_t reserved_11_15        : 5;
        uint64_t bgx0_bp               : 1;  /**< [ 16: 16](R/W) When 1, allows back pressure information to be sent to BGX0.
                                                                 When 0, resets state and does not send back pressure information to BGX0. */
        uint64_t bgx1_bp               : 1;  /**< [ 17: 17](R/W) When 1, allows back pressure information to be sent to BGX1.
                                                                 When 0, resets state and does not send back pressure information to BGX1. */
        uint64_t nici0_bp              : 1;  /**< [ 18: 18](R/W) When 1, allows back pressure information to be sent to NICI0.
                                                                 When 0, resets state and does not send back pressure information to NICI0. */
        uint64_t nici1_bp              : 1;  /**< [ 19: 19](R/W) When 1, allows back pressure information to be sent to NICI1.
                                                                 When 0, resets state and does not send back pressure information to NICI1. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_path_enable_s cn; */
};
typedef union bdk_tns_rdma_nb_path_enable bdk_tns_rdma_nb_path_enable_t;

#define BDK_TNS_RDMA_NB_PATH_ENABLE BDK_TNS_RDMA_NB_PATH_ENABLE_FUNC()
static inline uint64_t BDK_TNS_RDMA_NB_PATH_ENABLE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_PATH_ENABLE_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842042000aa0ll;
    __bdk_csr_fatal("TNS_RDMA_NB_PATH_ENABLE", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_PATH_ENABLE bdk_tns_rdma_nb_path_enable_t
#define bustype_BDK_TNS_RDMA_NB_PATH_ENABLE BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_PATH_ENABLE "TNS_RDMA_NB_PATH_ENABLE"
#define device_bar_BDK_TNS_RDMA_NB_PATH_ENABLE 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_PATH_ENABLE 0
#define arguments_BDK_TNS_RDMA_NB_PATH_ENABLE -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_perf_cntrl#
 *
 * INTERNAL: RDMA Performance Counter Control Register
 *
 * Performance counter control register.
 */
union bdk_tns_rdma_nb_perf_cntrlx
{
    uint64_t u;
    struct bdk_tns_rdma_nb_perf_cntrlx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t frozen                : 1;  /**< [ 31: 31](RO/H) Indicates that the counter is frozen (i.e one shot event occurred) and remains
                                                                 frozen until the clear bit written. */
        uint64_t clear                 : 1;  /**< [ 30: 30](WO/H) Writing 1 to this bit generates a hardware pulse that clears the
                                                                 TNS_RDMA_NB_PERF and field FROZEN of this register. The bit remains
                                                                 asserted continuously until 0 is written. */
        uint64_t enable                : 1;  /**< [ 29: 29](R/W) Enable the counter. This bit is set to 1 to use the corresponding counter. */
        uint64_t global_stop           : 1;  /**< [ 28: 28](R/W) This bit has two functions which are differentiated by the
                                                                 register number relative to the counter group.  For the
                                                                 zeroth (first) control register of the counter group,
                                                                 writing a 1 to this bit stops all the counters in the
                                                                 group of four counters. For the second control register of
                                                                 the counter group, writing a 1 to this bit globally enables
                                                                 all counters in the group. For all other control registers
                                                                 within the group, this bit is undefined. */
        uint64_t reserved_27           : 1;
        uint64_t mode                  : 3;  /**< [ 26: 24](R/W) Performance counter mode.

                                                                 Bit\<24\>:
                                                                 1 = Event counted SEL0.
                                                                 0 = Event counted SEL0 & SEL1 & SEL2.

                                                                 Bits\<26:25\>:
                                                                 0x0 = Pos edge.
                                                                 0x1 = Neg edge.
                                                                 0x2 = Level.
                                                                 0x3 = One shot. */
        uint64_t sel2                  : 8;  /**< [ 23: 16](R/W) Performance counter event select, third mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
        uint64_t sel1                  : 8;  /**< [ 15:  8](R/W) Performance counter event select, second mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
        uint64_t sel0                  : 8;  /**< [  7:  0](R/W) Performance counter event select, first mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
#else /* Word 0 - Little Endian */
        uint64_t sel0                  : 8;  /**< [  7:  0](R/W) Performance counter event select, first mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
        uint64_t sel1                  : 8;  /**< [ 15:  8](R/W) Performance counter event select, second mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
        uint64_t sel2                  : 8;  /**< [ 23: 16](R/W) Performance counter event select, third mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
        uint64_t mode                  : 3;  /**< [ 26: 24](R/W) Performance counter mode.

                                                                 Bit\<24\>:
                                                                 1 = Event counted SEL0.
                                                                 0 = Event counted SEL0 & SEL1 & SEL2.

                                                                 Bits\<26:25\>:
                                                                 0x0 = Pos edge.
                                                                 0x1 = Neg edge.
                                                                 0x2 = Level.
                                                                 0x3 = One shot. */
        uint64_t reserved_27           : 1;
        uint64_t global_stop           : 1;  /**< [ 28: 28](R/W) This bit has two functions which are differentiated by the
                                                                 register number relative to the counter group.  For the
                                                                 zeroth (first) control register of the counter group,
                                                                 writing a 1 to this bit stops all the counters in the
                                                                 group of four counters. For the second control register of
                                                                 the counter group, writing a 1 to this bit globally enables
                                                                 all counters in the group. For all other control registers
                                                                 within the group, this bit is undefined. */
        uint64_t enable                : 1;  /**< [ 29: 29](R/W) Enable the counter. This bit is set to 1 to use the corresponding counter. */
        uint64_t clear                 : 1;  /**< [ 30: 30](WO/H) Writing 1 to this bit generates a hardware pulse that clears the
                                                                 TNS_RDMA_NB_PERF and field FROZEN of this register. The bit remains
                                                                 asserted continuously until 0 is written. */
        uint64_t frozen                : 1;  /**< [ 31: 31](RO/H) Indicates that the counter is frozen (i.e one shot event occurred) and remains
                                                                 frozen until the clear bit written. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_perf_cntrlx_s cn; */
};
typedef union bdk_tns_rdma_nb_perf_cntrlx bdk_tns_rdma_nb_perf_cntrlx_t;

static inline uint64_t BDK_TNS_RDMA_NB_PERF_CNTRLX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_PERF_CNTRLX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X) && (a<=3))
        return 0x842042000300ll + 0x10ll * ((a) & 0x3);
    __bdk_csr_fatal("TNS_RDMA_NB_PERF_CNTRLX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_PERF_CNTRLX(a) bdk_tns_rdma_nb_perf_cntrlx_t
#define bustype_BDK_TNS_RDMA_NB_PERF_CNTRLX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_PERF_CNTRLX(a) "TNS_RDMA_NB_PERF_CNTRLX"
#define device_bar_BDK_TNS_RDMA_NB_PERF_CNTRLX(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_PERF_CNTRLX(a) (a)
#define arguments_BDK_TNS_RDMA_NB_PERF_CNTRLX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_perf_status#
 *
 * INTERNAL: RDMA Performance Counter Status Register
 *
 * Performance counter status register.
 */
union bdk_tns_rdma_nb_perf_statusx
{
    uint64_t u;
    struct bdk_tns_rdma_nb_perf_statusx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Event counter */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Event counter */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_perf_statusx_s cn; */
};
typedef union bdk_tns_rdma_nb_perf_statusx bdk_tns_rdma_nb_perf_statusx_t;

static inline uint64_t BDK_TNS_RDMA_NB_PERF_STATUSX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_PERF_STATUSX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X) && (a<=3))
        return 0x842042000340ll + 0x10ll * ((a) & 0x3);
    __bdk_csr_fatal("TNS_RDMA_NB_PERF_STATUSX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_PERF_STATUSX(a) bdk_tns_rdma_nb_perf_statusx_t
#define bustype_BDK_TNS_RDMA_NB_PERF_STATUSX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_PERF_STATUSX(a) "TNS_RDMA_NB_PERF_STATUSX"
#define device_bar_BDK_TNS_RDMA_NB_PERF_STATUSX(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_PERF_STATUSX(a) (a)
#define arguments_BDK_TNS_RDMA_NB_PERF_STATUSX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_rpkt_data#
 *
 * TNS RDMA Runt Packet Data Logging Register
 * Stores the first 256 bytes of a runt packet.
 * The first 8 bytes are stored in the DATA0 register in network order.
 * The data in this register is valid only if TNS_RDMA_NB_INT_STAT_W1S[RUNT_PKT] was
 * set by hardware.
 * The data in this register is valid only up to the byte length indicated by
 * TNS_RDMA_NB_RPKT_INFO[SIZE].
 */
union bdk_tns_rdma_nb_rpkt_datax
{
    uint64_t u;
    struct bdk_tns_rdma_nb_rpkt_datax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](RO/H) Captured packet data. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](RO/H) Captured packet data. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_rpkt_datax_s cn; */
};
typedef union bdk_tns_rdma_nb_rpkt_datax bdk_tns_rdma_nb_rpkt_datax_t;

static inline uint64_t BDK_TNS_RDMA_NB_RPKT_DATAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_RPKT_DATAX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=31))
        return 0x842042000600ll + 0x10ll * ((a) & 0x1f);
    __bdk_csr_fatal("TNS_RDMA_NB_RPKT_DATAX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_RPKT_DATAX(a) bdk_tns_rdma_nb_rpkt_datax_t
#define bustype_BDK_TNS_RDMA_NB_RPKT_DATAX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_RPKT_DATAX(a) "TNS_RDMA_NB_RPKT_DATAX"
#define device_bar_BDK_TNS_RDMA_NB_RPKT_DATAX(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_RPKT_DATAX(a) (a)
#define arguments_BDK_TNS_RDMA_NB_RPKT_DATAX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_rpkt_info
 *
 * TNS RDMA Runt Packet Information Logging Register
 * Information about the packet captured to the Runt Packet Data Logging Register.
 * The data in this register is valid only if TNS_RDMA_NB_INT_STAT_W1S[RUNT_PKT] was
 * set by hardware.
 */
union bdk_tns_rdma_nb_rpkt_info
{
    uint64_t u;
    struct bdk_tns_rdma_nb_rpkt_info_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t logical_port          : 8;  /**< [ 19: 12](RO/H) Captured packet source logical port. Only valid if PHYSICAL_PORT is NICI0 or NICI1. */
        uint64_t physical_port         : 4;  /**< [ 11:  8](RO/H) Captured packet source physical port as enumerated by TNS_PHYS_PORT_E. */
        uint64_t size                  : 8;  /**< [  7:  0](RO/H) Captured packet byte length. */
#else /* Word 0 - Little Endian */
        uint64_t size                  : 8;  /**< [  7:  0](RO/H) Captured packet byte length. */
        uint64_t physical_port         : 4;  /**< [ 11:  8](RO/H) Captured packet source physical port as enumerated by TNS_PHYS_PORT_E. */
        uint64_t logical_port          : 8;  /**< [ 19: 12](RO/H) Captured packet source logical port. Only valid if PHYSICAL_PORT is NICI0 or NICI1. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_rpkt_info_s cn; */
};
typedef union bdk_tns_rdma_nb_rpkt_info bdk_tns_rdma_nb_rpkt_info_t;

#define BDK_TNS_RDMA_NB_RPKT_INFO BDK_TNS_RDMA_NB_RPKT_INFO_FUNC()
static inline uint64_t BDK_TNS_RDMA_NB_RPKT_INFO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_RPKT_INFO_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842042000800ll;
    __bdk_csr_fatal("TNS_RDMA_NB_RPKT_INFO", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_RPKT_INFO bdk_tns_rdma_nb_rpkt_info_t
#define bustype_BDK_TNS_RDMA_NB_RPKT_INFO BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_RPKT_INFO "TNS_RDMA_NB_RPKT_INFO"
#define device_bar_BDK_TNS_RDMA_NB_RPKT_INFO 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_RPKT_INFO 0
#define arguments_BDK_TNS_RDMA_NB_RPKT_INFO -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_nb_runt_cnt#
 *
 * TNS RDMA Runt Counter Register
 * Runt packets and bytes received by the physical port.
 * All fields have roll over counters.
 */
union bdk_tns_rdma_nb_runt_cntx
{
    uint64_t u;
    struct bdk_tns_rdma_nb_runt_cntx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t bytes                 : 16; /**< [ 23:  8](R/W/H) Runt packet bytes seen. */
        uint64_t packets               : 8;  /**< [  7:  0](R/W/H) Runt packets seen. */
#else /* Word 0 - Little Endian */
        uint64_t packets               : 8;  /**< [  7:  0](R/W/H) Runt packets seen. */
        uint64_t bytes                 : 16; /**< [ 23:  8](R/W/H) Runt packet bytes seen. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nb_runt_cntx_s cn; */
};
typedef union bdk_tns_rdma_nb_runt_cntx bdk_tns_rdma_nb_runt_cntx_t;

static inline uint64_t BDK_TNS_RDMA_NB_RUNT_CNTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NB_RUNT_CNTX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=9))
        return 0x842042000400ll + 0x10ll * ((a) & 0xf);
    __bdk_csr_fatal("TNS_RDMA_NB_RUNT_CNTX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NB_RUNT_CNTX(a) bdk_tns_rdma_nb_runt_cntx_t
#define bustype_BDK_TNS_RDMA_NB_RUNT_CNTX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NB_RUNT_CNTX(a) "TNS_RDMA_NB_RUNT_CNTX"
#define device_bar_BDK_TNS_RDMA_NB_RUNT_CNTX(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_RDMA_NB_RUNT_CNTX(a) (a)
#define arguments_BDK_TNS_RDMA_NB_RUNT_CNTX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_rdma_nic_cdt_rtn
 *
 * INTERNAL: TNS RDMA NIC Channel Credit Return Register
 *
 * Force a credit return message to the NIC.
 */
union bdk_tns_rdma_nic_cdt_rtn
{
    uint64_t u;
    struct bdk_tns_rdma_nic_cdt_rtn_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t valid                 : 1;  /**< [ 31: 31](R/W/H) Valid.
                                                                 Hardware will clear this field upon the successful transmission of a channel
                                                                 credit message to the NIC using this CSR.
                                                                 Software must verify this field is 0 before setting this bit. */
        uint64_t reserved_16_30        : 15;
        uint64_t pages                 : 4;  /**< [ 15: 12](R/W) Quantity of 256-byte pages. 0 = 16 pages, 1 = 1 page, 2 = 2 pages, etc. */
        uint64_t intf                  : 1;  /**< [ 11: 11](R/W) NIC interface. */
        uint64_t channel               : 7;  /**< [ 10:  4](R/W) NIC channel. */
        uint64_t reserved_1_3          : 3;
        uint64_t eop                   : 1;  /**< [  0:  0](R/W) Send EOP flag. */
#else /* Word 0 - Little Endian */
        uint64_t eop                   : 1;  /**< [  0:  0](R/W) Send EOP flag. */
        uint64_t reserved_1_3          : 3;
        uint64_t channel               : 7;  /**< [ 10:  4](R/W) NIC channel. */
        uint64_t intf                  : 1;  /**< [ 11: 11](R/W) NIC interface. */
        uint64_t pages                 : 4;  /**< [ 15: 12](R/W) Quantity of 256-byte pages. 0 = 16 pages, 1 = 1 page, 2 = 2 pages, etc. */
        uint64_t reserved_16_30        : 15;
        uint64_t valid                 : 1;  /**< [ 31: 31](R/W/H) Valid.
                                                                 Hardware will clear this field upon the successful transmission of a channel
                                                                 credit message to the NIC using this CSR.
                                                                 Software must verify this field is 0 before setting this bit. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_nic_cdt_rtn_s cn; */
};
typedef union bdk_tns_rdma_nic_cdt_rtn bdk_tns_rdma_nic_cdt_rtn_t;

#define BDK_TNS_RDMA_NIC_CDT_RTN BDK_TNS_RDMA_NIC_CDT_RTN_FUNC()
static inline uint64_t BDK_TNS_RDMA_NIC_CDT_RTN_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_NIC_CDT_RTN_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000001a30ll;
    __bdk_csr_fatal("TNS_RDMA_NIC_CDT_RTN", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_NIC_CDT_RTN bdk_tns_rdma_nic_cdt_rtn_t
#define bustype_BDK_TNS_RDMA_NIC_CDT_RTN BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_NIC_CDT_RTN "TNS_RDMA_NIC_CDT_RTN"
#define device_bar_BDK_TNS_RDMA_NIC_CDT_RTN 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_NIC_CDT_RTN 0
#define arguments_BDK_TNS_RDMA_NIC_CDT_RTN -1,-1,-1,-1

/**
 * Register (NCB) tns_rdma_perf_cntrl#
 *
 * INTERNAL: RDMA Performance Counter Control Register
 *
 * Performance counter control register.
 */
union bdk_tns_rdma_perf_cntrlx
{
    uint64_t u;
    struct bdk_tns_rdma_perf_cntrlx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t frozen                : 1;  /**< [ 31: 31](RO/H) Indicates that the counter is frozen (i.e one shot event occurred) and remains
                                                                 frozen until the clear bit written. */
        uint64_t clear                 : 1;  /**< [ 30: 30](WO/H) Writing 1 to this bit generates a hardware pulse that clears the
                                                                 TNS_RDMA_PERF and field FROZEN of this register. The bit remains
                                                                 asserted continuously until 0 is written. */
        uint64_t enable                : 1;  /**< [ 29: 29](R/W) Enable the counter. This bit is set to 1 to use the corresponding counter. */
        uint64_t global_stop           : 1;  /**< [ 28: 28](R/W) This bit has two functions which are differentiated by the
                                                                 register number relative to the counter group.  For the
                                                                 zeroth (first) control register of the counter group,
                                                                 writing a 1 to this bit stops all the counters in the
                                                                 group of four counters. For the second control register of
                                                                 the counter group, writing a 1 to this bit globally enables
                                                                 all counters in the group. For all other control registers
                                                                 within the group, this bit is undefined. */
        uint64_t reserved_27           : 1;
        uint64_t mode                  : 3;  /**< [ 26: 24](R/W) Performance counter mode.

                                                                 Bit\<24\>:
                                                                 1 = Event counted SEL0.
                                                                 0 = Event counted SEL0 & SEL1 & SEL2.

                                                                 Bits\<26:25\>:
                                                                 0x0 = Pos edge.
                                                                 0x1 = Neg edge.
                                                                 0x2 = Level.
                                                                 0x3 = One shot. */
        uint64_t sel2                  : 8;  /**< [ 23: 16](R/W) Performance counter event select, third mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
        uint64_t sel1                  : 8;  /**< [ 15:  8](R/W) Performance counter event select, second mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
        uint64_t sel0                  : 8;  /**< [  7:  0](R/W) Performance counter event select, first mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
#else /* Word 0 - Little Endian */
        uint64_t sel0                  : 8;  /**< [  7:  0](R/W) Performance counter event select, first mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
        uint64_t sel1                  : 8;  /**< [ 15:  8](R/W) Performance counter event select, second mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
        uint64_t sel2                  : 8;  /**< [ 23: 16](R/W) Performance counter event select, third mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
        uint64_t mode                  : 3;  /**< [ 26: 24](R/W) Performance counter mode.

                                                                 Bit\<24\>:
                                                                 1 = Event counted SEL0.
                                                                 0 = Event counted SEL0 & SEL1 & SEL2.

                                                                 Bits\<26:25\>:
                                                                 0x0 = Pos edge.
                                                                 0x1 = Neg edge.
                                                                 0x2 = Level.
                                                                 0x3 = One shot. */
        uint64_t reserved_27           : 1;
        uint64_t global_stop           : 1;  /**< [ 28: 28](R/W) This bit has two functions which are differentiated by the
                                                                 register number relative to the counter group.  For the
                                                                 zeroth (first) control register of the counter group,
                                                                 writing a 1 to this bit stops all the counters in the
                                                                 group of four counters. For the second control register of
                                                                 the counter group, writing a 1 to this bit globally enables
                                                                 all counters in the group. For all other control registers
                                                                 within the group, this bit is undefined. */
        uint64_t enable                : 1;  /**< [ 29: 29](R/W) Enable the counter. This bit is set to 1 to use the corresponding counter. */
        uint64_t clear                 : 1;  /**< [ 30: 30](WO/H) Writing 1 to this bit generates a hardware pulse that clears the
                                                                 TNS_RDMA_PERF and field FROZEN of this register. The bit remains
                                                                 asserted continuously until 0 is written. */
        uint64_t frozen                : 1;  /**< [ 31: 31](RO/H) Indicates that the counter is frozen (i.e one shot event occurred) and remains
                                                                 frozen until the clear bit written. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_perf_cntrlx_s cn; */
};
typedef union bdk_tns_rdma_perf_cntrlx bdk_tns_rdma_perf_cntrlx_t;

static inline uint64_t BDK_TNS_RDMA_PERF_CNTRLX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_PERF_CNTRLX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X) && (a<=3))
        return 0x842000001900ll + 0x10ll * ((a) & 0x3);
    __bdk_csr_fatal("TNS_RDMA_PERF_CNTRLX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_PERF_CNTRLX(a) bdk_tns_rdma_perf_cntrlx_t
#define bustype_BDK_TNS_RDMA_PERF_CNTRLX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_PERF_CNTRLX(a) "TNS_RDMA_PERF_CNTRLX"
#define device_bar_BDK_TNS_RDMA_PERF_CNTRLX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_PERF_CNTRLX(a) (a)
#define arguments_BDK_TNS_RDMA_PERF_CNTRLX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_rdma_perf_status#
 *
 * INTERNAL: RDMA Performance Counter Status Register
 *
 * Performance counter status register.
 */
union bdk_tns_rdma_perf_statusx
{
    uint64_t u;
    struct bdk_tns_rdma_perf_statusx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Event counter */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Event counter */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_rdma_perf_statusx_s cn; */
};
typedef union bdk_tns_rdma_perf_statusx bdk_tns_rdma_perf_statusx_t;

static inline uint64_t BDK_TNS_RDMA_PERF_STATUSX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_RDMA_PERF_STATUSX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X) && (a<=3))
        return 0x842000001940ll + 0x10ll * ((a) & 0x3);
    __bdk_csr_fatal("TNS_RDMA_PERF_STATUSX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_RDMA_PERF_STATUSX(a) bdk_tns_rdma_perf_statusx_t
#define bustype_BDK_TNS_RDMA_PERF_STATUSX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_RDMA_PERF_STATUSX(a) "TNS_RDMA_PERF_STATUSX"
#define device_bar_BDK_TNS_RDMA_PERF_STATUSX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_RDMA_PERF_STATUSX(a) (a)
#define arguments_BDK_TNS_RDMA_PERF_STATUSX(a) (a),-1,-1,-1

/**
 * Register (NCB32b) tns_sde_parser_cfg_sde_spare_w0
 *
 * INTERNAL: TNS SDE PARSER CFG SDE SPARE W0 Register
 *
 * Spare register with default signature value 0x10FEDCBA98765432 after reset.
 */
union bdk_tns_sde_parser_cfg_sde_spare_w0
{
    uint32_t u;
    struct bdk_tns_sde_parser_cfg_sde_spare_w0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t spare_x0              : 32; /**< [ 31:  0](R/W) Spare field. */
#else /* Word 0 - Little Endian */
        uint32_t spare_x0              : 32; /**< [ 31:  0](R/W) Spare field. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_sde_parser_cfg_sde_spare_w0_s cn; */
};
typedef union bdk_tns_sde_parser_cfg_sde_spare_w0 bdk_tns_sde_parser_cfg_sde_spare_w0_t;

#define BDK_TNS_SDE_PARSER_CFG_SDE_SPARE_W0 BDK_TNS_SDE_PARSER_CFG_SDE_SPARE_W0_FUNC()
static inline uint64_t BDK_TNS_SDE_PARSER_CFG_SDE_SPARE_W0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_SDE_PARSER_CFG_SDE_SPARE_W0_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842068740000ll;
    __bdk_csr_fatal("TNS_SDE_PARSER_CFG_SDE_SPARE_W0", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_SDE_PARSER_CFG_SDE_SPARE_W0 bdk_tns_sde_parser_cfg_sde_spare_w0_t
#define bustype_BDK_TNS_SDE_PARSER_CFG_SDE_SPARE_W0 BDK_CSR_TYPE_NCB32b
#define basename_BDK_TNS_SDE_PARSER_CFG_SDE_SPARE_W0 "TNS_SDE_PARSER_CFG_SDE_SPARE_W0"
#define device_bar_BDK_TNS_SDE_PARSER_CFG_SDE_SPARE_W0 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_SDE_PARSER_CFG_SDE_SPARE_W0 0
#define arguments_BDK_TNS_SDE_PARSER_CFG_SDE_SPARE_W0 -1,-1,-1,-1

/**
 * Register (NCB32b) tns_sde_parser_cfg_sde_spare_w1
 *
 * INTERNAL: TNS SDE PARSER CFG SDE SPARE W1 Register
 *
 * Continuation of structure defined in TNS_SDE_PARSER_CFG_SDE_SPARE_W0
 */
union bdk_tns_sde_parser_cfg_sde_spare_w1
{
    uint32_t u;
    struct bdk_tns_sde_parser_cfg_sde_spare_w1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t spare_x1              : 32; /**< [ 31:  0](R/W) Continuation of field SPARE_X0. */
#else /* Word 0 - Little Endian */
        uint32_t spare_x1              : 32; /**< [ 31:  0](R/W) Continuation of field SPARE_X0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_sde_parser_cfg_sde_spare_w1_s cn; */
};
typedef union bdk_tns_sde_parser_cfg_sde_spare_w1 bdk_tns_sde_parser_cfg_sde_spare_w1_t;

#define BDK_TNS_SDE_PARSER_CFG_SDE_SPARE_W1 BDK_TNS_SDE_PARSER_CFG_SDE_SPARE_W1_FUNC()
static inline uint64_t BDK_TNS_SDE_PARSER_CFG_SDE_SPARE_W1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_SDE_PARSER_CFG_SDE_SPARE_W1_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842068740004ll;
    __bdk_csr_fatal("TNS_SDE_PARSER_CFG_SDE_SPARE_W1", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_SDE_PARSER_CFG_SDE_SPARE_W1 bdk_tns_sde_parser_cfg_sde_spare_w1_t
#define bustype_BDK_TNS_SDE_PARSER_CFG_SDE_SPARE_W1 BDK_CSR_TYPE_NCB32b
#define basename_BDK_TNS_SDE_PARSER_CFG_SDE_SPARE_W1 "TNS_SDE_PARSER_CFG_SDE_SPARE_W1"
#define device_bar_BDK_TNS_SDE_PARSER_CFG_SDE_SPARE_W1 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_SDE_PARSER_CFG_SDE_SPARE_W1 0
#define arguments_BDK_TNS_SDE_PARSER_CFG_SDE_SPARE_W1 -1,-1,-1,-1

/**
 * Register (NCB32b) tns_se_tcam_table_spare_w0
 *
 * INTERNAL: TNS SE TCAM TABLE SPARE W0 Register
 *
 * --
 */
union bdk_tns_se_tcam_table_spare_w0
{
    uint32_t u;
    struct bdk_tns_se_tcam_table_spare_w0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t xp_se_spare_x0        : 32; /**< [ 31:  0](R/W) Spare register with an SE debug signature 0x0FEDCBA987654321 */
#else /* Word 0 - Little Endian */
        uint32_t xp_se_spare_x0        : 32; /**< [ 31:  0](R/W) Spare register with an SE debug signature 0x0FEDCBA987654321 */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_se_tcam_table_spare_w0_s cn; */
};
typedef union bdk_tns_se_tcam_table_spare_w0 bdk_tns_se_tcam_table_spare_w0_t;

#define BDK_TNS_SE_TCAM_TABLE_SPARE_W0 BDK_TNS_SE_TCAM_TABLE_SPARE_W0_FUNC()
static inline uint64_t BDK_TNS_SE_TCAM_TABLE_SPARE_W0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_SE_TCAM_TABLE_SPARE_W0_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842052200040ll;
    __bdk_csr_fatal("TNS_SE_TCAM_TABLE_SPARE_W0", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_SE_TCAM_TABLE_SPARE_W0 bdk_tns_se_tcam_table_spare_w0_t
#define bustype_BDK_TNS_SE_TCAM_TABLE_SPARE_W0 BDK_CSR_TYPE_NCB32b
#define basename_BDK_TNS_SE_TCAM_TABLE_SPARE_W0 "TNS_SE_TCAM_TABLE_SPARE_W0"
#define device_bar_BDK_TNS_SE_TCAM_TABLE_SPARE_W0 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_SE_TCAM_TABLE_SPARE_W0 0
#define arguments_BDK_TNS_SE_TCAM_TABLE_SPARE_W0 -1,-1,-1,-1

/**
 * Register (NCB32b) tns_se_tcam_table_spare_w1
 *
 * INTERNAL: TNS SE TCAM TABLE SPARE W1 Register
 *
 * Continuation of structure defined in TNS_SE_TCAM_TABLE_SPARE_W0
 */
union bdk_tns_se_tcam_table_spare_w1
{
    uint32_t u;
    struct bdk_tns_se_tcam_table_spare_w1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t xp_se_spare_x1        : 32; /**< [ 31:  0](R/W) Continuation of field XP_SE_SPARE_X0. */
#else /* Word 0 - Little Endian */
        uint32_t xp_se_spare_x1        : 32; /**< [ 31:  0](R/W) Continuation of field XP_SE_SPARE_X0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_se_tcam_table_spare_w1_s cn; */
};
typedef union bdk_tns_se_tcam_table_spare_w1 bdk_tns_se_tcam_table_spare_w1_t;

#define BDK_TNS_SE_TCAM_TABLE_SPARE_W1 BDK_TNS_SE_TCAM_TABLE_SPARE_W1_FUNC()
static inline uint64_t BDK_TNS_SE_TCAM_TABLE_SPARE_W1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_SE_TCAM_TABLE_SPARE_W1_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842052200044ll;
    __bdk_csr_fatal("TNS_SE_TCAM_TABLE_SPARE_W1", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_SE_TCAM_TABLE_SPARE_W1 bdk_tns_se_tcam_table_spare_w1_t
#define bustype_BDK_TNS_SE_TCAM_TABLE_SPARE_W1 BDK_CSR_TYPE_NCB32b
#define basename_BDK_TNS_SE_TCAM_TABLE_SPARE_W1 "TNS_SE_TCAM_TABLE_SPARE_W1"
#define device_bar_BDK_TNS_SE_TCAM_TABLE_SPARE_W1 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_SE_TCAM_TABLE_SPARE_W1 0
#define arguments_BDK_TNS_SE_TCAM_TABLE_SPARE_W1 -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_cap
 *
 * TNS TDMA Capabilities Register
 */
union bdk_tns_tdma_cap
{
    uint64_t u;
    struct bdk_tns_tdma_cap_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t switch_capable        : 1;  /**< [  0:  0](RO/H) When 1, indicates this device is capable of performing network switching functions.
                                                                 Internal:
                                                                 This field comes from the rst_fus__tns_cripple pin. */
#else /* Word 0 - Little Endian */
        uint64_t switch_capable        : 1;  /**< [  0:  0](RO/H) When 1, indicates this device is capable of performing network switching functions.
                                                                 Internal:
                                                                 This field comes from the rst_fus__tns_cripple pin. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_cap_s cn; */
};
typedef union bdk_tns_tdma_cap bdk_tns_tdma_cap_t;

#define BDK_TNS_TDMA_CAP BDK_TNS_TDMA_CAP_FUNC()
static inline uint64_t BDK_TNS_TDMA_CAP_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_CAP_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000400ll;
    __bdk_csr_fatal("TNS_TDMA_CAP", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_CAP bdk_tns_tdma_cap_t
#define bustype_BDK_TNS_TDMA_CAP BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_CAP "TNS_TDMA_CAP"
#define device_bar_BDK_TNS_TDMA_CAP 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_CAP 0
#define arguments_BDK_TNS_TDMA_CAP -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_cnt#
 *
 * TNS TDMA Transmit Counter Register
 * Packets and bytes transmitted by the physical port.
 * All fields have roll over counters.
 * Register number enumerated by TNS_PHYS_PORT_E.
 */
union bdk_tns_tdma_cntx
{
    uint64_t u;
    struct bdk_tns_tdma_cntx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_60_63        : 4;
        uint64_t bytes                 : 36; /**< [ 59: 24](R/W/H) Packet bytes. */
        uint64_t packets               : 24; /**< [ 23:  0](R/W/H) Packets. */
#else /* Word 0 - Little Endian */
        uint64_t packets               : 24; /**< [ 23:  0](R/W/H) Packets. */
        uint64_t bytes                 : 36; /**< [ 59: 24](R/W/H) Packet bytes. */
        uint64_t reserved_60_63        : 4;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_cntx_s cn; */
};
typedef union bdk_tns_tdma_cntx bdk_tns_tdma_cntx_t;

static inline uint64_t BDK_TNS_TDMA_CNTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_CNTX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=9))
        return 0x842000000600ll + 0x10ll * ((a) & 0xf);
    __bdk_csr_fatal("TNS_TDMA_CNTX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_CNTX(a) bdk_tns_tdma_cntx_t
#define bustype_BDK_TNS_TDMA_CNTX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_CNTX(a) "TNS_TDMA_CNTX"
#define device_bar_BDK_TNS_TDMA_CNTX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_CNTX(a) (a)
#define arguments_BDK_TNS_TDMA_CNTX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_cnt_bytes#
 *
 * TNS TDMA Transmit Counter Register
 * Bytes transmitted by the physical port. All fields have roll over counters. Register
 * number enumerated by TNS_PHYS_PORT_E.
 */
union bdk_tns_tdma_cnt_bytesx
{
    uint64_t u;
    struct bdk_tns_tdma_cnt_bytesx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t bytes                 : 48; /**< [ 47:  0](R/W/H) Packet bytes. */
#else /* Word 0 - Little Endian */
        uint64_t bytes                 : 48; /**< [ 47:  0](R/W/H) Packet bytes. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_cnt_bytesx_s cn; */
};
typedef union bdk_tns_tdma_cnt_bytesx bdk_tns_tdma_cnt_bytesx_t;

static inline uint64_t BDK_TNS_TDMA_CNT_BYTESX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_CNT_BYTESX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X) && (a<=9))
        return 0x842000000780ll + 8ll * ((a) & 0xf);
    __bdk_csr_fatal("TNS_TDMA_CNT_BYTESX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_CNT_BYTESX(a) bdk_tns_tdma_cnt_bytesx_t
#define bustype_BDK_TNS_TDMA_CNT_BYTESX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_CNT_BYTESX(a) "TNS_TDMA_CNT_BYTESX"
#define device_bar_BDK_TNS_TDMA_CNT_BYTESX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_CNT_BYTESX(a) (a)
#define arguments_BDK_TNS_TDMA_CNT_BYTESX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_cnt_pkts#
 *
 * TNS TDMA Transmit Counter Register
 * Packets transmitted by the physical port. All fields have roll over
 * counters. Register number enumerated by TNS_PHYS_PORT_E.
 */
union bdk_tns_tdma_cnt_pktsx
{
    uint64_t u;
    struct bdk_tns_tdma_cnt_pktsx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t packets               : 36; /**< [ 35:  0](R/W/H) Packets. */
#else /* Word 0 - Little Endian */
        uint64_t packets               : 36; /**< [ 35:  0](R/W/H) Packets. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_cnt_pktsx_s cn; */
};
typedef union bdk_tns_tdma_cnt_pktsx bdk_tns_tdma_cnt_pktsx_t;

static inline uint64_t BDK_TNS_TDMA_CNT_PKTSX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_CNT_PKTSX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X) && (a<=9))
        return 0x842000000700ll + 8ll * ((a) & 0xf);
    __bdk_csr_fatal("TNS_TDMA_CNT_PKTSX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_CNT_PKTSX(a) bdk_tns_tdma_cnt_pktsx_t
#define bustype_BDK_TNS_TDMA_CNT_PKTSX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_CNT_PKTSX(a) "TNS_TDMA_CNT_PKTSX"
#define device_bar_BDK_TNS_TDMA_CNT_PKTSX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_CNT_PKTSX(a) (a)
#define arguments_BDK_TNS_TDMA_CNT_PKTSX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_config
 *
 * TNS TDMA Configuration Register
 */
union bdk_tns_tdma_config
{
    uint64_t u;
    struct bdk_tns_tdma_config_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t bypass1_ena           : 1;  /**< [  9:  9](R/W) BGX1 \<-\> NICI1 Bypass Enable.
                                                                 Packet and back pressure information are passed directly between NIC Interface 1 and BGX1.
                                                                 Software must guarantee that no packets are in flight from/to BGX1/NICI1 when this bit is
                                                                 flipped.

                                                                 Internal:
                                                                 This field can be set only if TNS_TDMA_CAP[SWITCH_CAPABLE] is set. */
        uint64_t bypass0_ena           : 1;  /**< [  8:  8](R/W) BGX0 \<-\> NICI0 Bypass Enable.
                                                                 Packet and back pressure information are passed directly between NIC Interface 0 and BGX0.
                                                                 Software must guarantee that no packets are in flight from/to BGX0/NICI0 when this bit is
                                                                 flipped.

                                                                 Internal:
                                                                 This field can be set only if TNS_TDMA_CAP[SWITCH_CAPABLE] is set. */
        uint64_t reserved_5_7          : 3;
        uint64_t csr_access_ena        : 1;  /**< [  4:  4](R/W) Enable access to network switch registers.
                                                                 Internal:
                                                                 This field can be set only if TNS_TDMA_CAP[SWITCH_CAPABLE] is set. */
        uint64_t reserved_2_3          : 2;
        uint64_t clk_2x_ena            : 1;  /**< [  1:  1](R/W) Enable fast clock.
                                                                 Internal:
                                                                 Enable conditional clock to non-bypass memories.
                                                                 This field can be set only if TNS_TDMA_CAP[SWITCH_CAPABLE] is set. */
        uint64_t clk_ena               : 1;  /**< [  0:  0](R/W) Enable slow clock.
                                                                 Internal:
                                                                 Enable conditional clock to non-bypass logic.
                                                                 This field can be set only if TNS_TDMA_CAP[SWITCH_CAPABLE] is set.
                                                                 This field has no effect unless CLK_2X_ENA is set. */
#else /* Word 0 - Little Endian */
        uint64_t clk_ena               : 1;  /**< [  0:  0](R/W) Enable slow clock.
                                                                 Internal:
                                                                 Enable conditional clock to non-bypass logic.
                                                                 This field can be set only if TNS_TDMA_CAP[SWITCH_CAPABLE] is set.
                                                                 This field has no effect unless CLK_2X_ENA is set. */
        uint64_t clk_2x_ena            : 1;  /**< [  1:  1](R/W) Enable fast clock.
                                                                 Internal:
                                                                 Enable conditional clock to non-bypass memories.
                                                                 This field can be set only if TNS_TDMA_CAP[SWITCH_CAPABLE] is set. */
        uint64_t reserved_2_3          : 2;
        uint64_t csr_access_ena        : 1;  /**< [  4:  4](R/W) Enable access to network switch registers.
                                                                 Internal:
                                                                 This field can be set only if TNS_TDMA_CAP[SWITCH_CAPABLE] is set. */
        uint64_t reserved_5_7          : 3;
        uint64_t bypass0_ena           : 1;  /**< [  8:  8](R/W) BGX0 \<-\> NICI0 Bypass Enable.
                                                                 Packet and back pressure information are passed directly between NIC Interface 0 and BGX0.
                                                                 Software must guarantee that no packets are in flight from/to BGX0/NICI0 when this bit is
                                                                 flipped.

                                                                 Internal:
                                                                 This field can be set only if TNS_TDMA_CAP[SWITCH_CAPABLE] is set. */
        uint64_t bypass1_ena           : 1;  /**< [  9:  9](R/W) BGX1 \<-\> NICI1 Bypass Enable.
                                                                 Packet and back pressure information are passed directly between NIC Interface 1 and BGX1.
                                                                 Software must guarantee that no packets are in flight from/to BGX1/NICI1 when this bit is
                                                                 flipped.

                                                                 Internal:
                                                                 This field can be set only if TNS_TDMA_CAP[SWITCH_CAPABLE] is set. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_config_s cn; */
};
typedef union bdk_tns_tdma_config bdk_tns_tdma_config_t;

#define BDK_TNS_TDMA_CONFIG BDK_TNS_TDMA_CONFIG_FUNC()
static inline uint64_t BDK_TNS_TDMA_CONFIG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_CONFIG_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000200ll;
    __bdk_csr_fatal("TNS_TDMA_CONFIG", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_CONFIG bdk_tns_tdma_config_t
#define bustype_BDK_TNS_TDMA_CONFIG BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_CONFIG "TNS_TDMA_CONFIG"
#define device_bar_BDK_TNS_TDMA_CONFIG 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_CONFIG 0
#define arguments_BDK_TNS_TDMA_CONFIG -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_dbg_cdt_ctl
 *
 * INTERNAL: TNS TDMA Debug Credit Control Register
 *
 * This register provides debug control of packet transmission.
 */
union bdk_tns_tdma_dbg_cdt_ctl
{
    uint64_t u;
    struct bdk_tns_tdma_dbg_cdt_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t lmac_skid_cdts_inc    : 8;  /**< [ 31: 24](WO/H) Each write to this field increments the count of skid credits to the LMACs. */
        uint64_t lmac_fifo_cdts_inc    : 8;  /**< [ 23: 16](WO/H) Each write to this field increments the count of FIFO credits to the LMACs. */
        uint64_t lmac_skid_cdts_dec    : 8;  /**< [ 15:  8](WO/H) Each write to this field decrements the count of skid credits to the LMACs. */
        uint64_t lmac_fifo_cdts_dec    : 8;  /**< [  7:  0](WO/H) Each write to this field decrements the count of FIFO credits to the LMACs. */
#else /* Word 0 - Little Endian */
        uint64_t lmac_fifo_cdts_dec    : 8;  /**< [  7:  0](WO/H) Each write to this field decrements the count of FIFO credits to the LMACs. */
        uint64_t lmac_skid_cdts_dec    : 8;  /**< [ 15:  8](WO/H) Each write to this field decrements the count of skid credits to the LMACs. */
        uint64_t lmac_fifo_cdts_inc    : 8;  /**< [ 23: 16](WO/H) Each write to this field increments the count of FIFO credits to the LMACs. */
        uint64_t lmac_skid_cdts_inc    : 8;  /**< [ 31: 24](WO/H) Each write to this field increments the count of skid credits to the LMACs. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_dbg_cdt_ctl_s cn; */
};
typedef union bdk_tns_tdma_dbg_cdt_ctl bdk_tns_tdma_dbg_cdt_ctl_t;

#define BDK_TNS_TDMA_DBG_CDT_CTL BDK_TNS_TDMA_DBG_CDT_CTL_FUNC()
static inline uint64_t BDK_TNS_TDMA_DBG_CDT_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_DBG_CDT_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000a10ll;
    __bdk_csr_fatal("TNS_TDMA_DBG_CDT_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_DBG_CDT_CTL bdk_tns_tdma_dbg_cdt_ctl_t
#define bustype_BDK_TNS_TDMA_DBG_CDT_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_DBG_CDT_CTL "TNS_TDMA_DBG_CDT_CTL"
#define device_bar_BDK_TNS_TDMA_DBG_CDT_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_DBG_CDT_CTL 0
#define arguments_BDK_TNS_TDMA_DBG_CDT_CTL -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_dbg_lmac#_config
 *
 * INTERNAL: TNS TDMA Debug LMAC Config Register
 *
 * This register provides debug control of TDMA functionality.
 */
union bdk_tns_tdma_dbg_lmacx_config
{
    uint64_t u;
    struct bdk_tns_tdma_dbg_lmacx_config_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t start_occ             : 8;  /**< [ 23: 16](R/W) To guarantee outbound packet data can match the line rate of incoming cut-through packets,
                                                                 packet data is stored in the FIFO buffer until either a packet EOP is pushed to the FIFO
                                                                 or the quantity of data in the FIFO reaches this amount.
                                                                 This field must be equal or less than EARLY_FULL_OCC. */
        uint64_t reserved_8_15         : 8;
        uint64_t early_full_occ        : 8;  /**< [  7:  0](R/W) When the outbound packet buffer occupancy reaches this point the FIFO will present
                                                                 a full indication to stop the packet pipeline from sending data across the shared async
                                                                 boundary. */
#else /* Word 0 - Little Endian */
        uint64_t early_full_occ        : 8;  /**< [  7:  0](R/W) When the outbound packet buffer occupancy reaches this point the FIFO will present
                                                                 a full indication to stop the packet pipeline from sending data across the shared async
                                                                 boundary. */
        uint64_t reserved_8_15         : 8;
        uint64_t start_occ             : 8;  /**< [ 23: 16](R/W) To guarantee outbound packet data can match the line rate of incoming cut-through packets,
                                                                 packet data is stored in the FIFO buffer until either a packet EOP is pushed to the FIFO
                                                                 or the quantity of data in the FIFO reaches this amount.
                                                                 This field must be equal or less than EARLY_FULL_OCC. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_dbg_lmacx_config_s cn; */
};
typedef union bdk_tns_tdma_dbg_lmacx_config bdk_tns_tdma_dbg_lmacx_config_t;

static inline uint64_t BDK_TNS_TDMA_DBG_LMACX_CONFIG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_DBG_LMACX_CONFIG(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=7))
        return 0x842000000b00ll + 0x10ll * ((a) & 0x7);
    __bdk_csr_fatal("TNS_TDMA_DBG_LMACX_CONFIG", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_DBG_LMACX_CONFIG(a) bdk_tns_tdma_dbg_lmacx_config_t
#define bustype_BDK_TNS_TDMA_DBG_LMACX_CONFIG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_DBG_LMACX_CONFIG(a) "TNS_TDMA_DBG_LMACX_CONFIG"
#define device_bar_BDK_TNS_TDMA_DBG_LMACX_CONFIG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_DBG_LMACX_CONFIG(a) (a)
#define arguments_BDK_TNS_TDMA_DBG_LMACX_CONFIG(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_dbg_lmac#_status1
 *
 * INTERNAL: TNS TDMA Debug LMAC Status1 Register
 *
 * This register provides debug status of TDMA functionality.
 */
union bdk_tns_tdma_dbg_lmacx_status1
{
    uint64_t u;
    struct bdk_tns_tdma_dbg_lmacx_status1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t fifo_occ              : 8;  /**< [ 31: 24](RO/H) Packet data FIFO occupancy.
                                                                 Each entry in the FIFO represents 1 16-byte flit. */
        uint64_t reserved_21_23        : 3;
        uint64_t skid_cdts             : 5;  /**< [ 20: 16](RO/H) Skid credits available towards LMAC.
                                                                 Each credit represents 1 16-byte flit. */
        uint64_t reserved_14_15        : 2;
        uint64_t fifo_cdts             : 14; /**< [ 13:  0](RO/H) FIFO credits consumed towards the LMAC.
                                                                 Each credit represents 1 16-byte flit. */
#else /* Word 0 - Little Endian */
        uint64_t fifo_cdts             : 14; /**< [ 13:  0](RO/H) FIFO credits consumed towards the LMAC.
                                                                 Each credit represents 1 16-byte flit. */
        uint64_t reserved_14_15        : 2;
        uint64_t skid_cdts             : 5;  /**< [ 20: 16](RO/H) Skid credits available towards LMAC.
                                                                 Each credit represents 1 16-byte flit. */
        uint64_t reserved_21_23        : 3;
        uint64_t fifo_occ              : 8;  /**< [ 31: 24](RO/H) Packet data FIFO occupancy.
                                                                 Each entry in the FIFO represents 1 16-byte flit. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_dbg_lmacx_status1_s cn; */
};
typedef union bdk_tns_tdma_dbg_lmacx_status1 bdk_tns_tdma_dbg_lmacx_status1_t;

static inline uint64_t BDK_TNS_TDMA_DBG_LMACX_STATUS1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_DBG_LMACX_STATUS1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=7))
        return 0x842000000c00ll + 0x10ll * ((a) & 0x7);
    __bdk_csr_fatal("TNS_TDMA_DBG_LMACX_STATUS1", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_DBG_LMACX_STATUS1(a) bdk_tns_tdma_dbg_lmacx_status1_t
#define bustype_BDK_TNS_TDMA_DBG_LMACX_STATUS1(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_DBG_LMACX_STATUS1(a) "TNS_TDMA_DBG_LMACX_STATUS1"
#define device_bar_BDK_TNS_TDMA_DBG_LMACX_STATUS1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_DBG_LMACX_STATUS1(a) (a)
#define arguments_BDK_TNS_TDMA_DBG_LMACX_STATUS1(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_dbg_nici#_config
 *
 * INTERNAL: TNS TDMA Debug NICI Config Register
 *
 * This register provides debug control of TDMA functionality.
 */
union bdk_tns_tdma_dbg_nicix_config
{
    uint64_t u;
    struct bdk_tns_tdma_dbg_nicix_config_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t early_full_occ        : 8;  /**< [  7:  0](R/W) When the outbound packet buffer occupancy reaches this point the FIFO will present
                                                                 a full indication to stop the packet pipeline from sending data across the shared async
                                                                 boundary. */
#else /* Word 0 - Little Endian */
        uint64_t early_full_occ        : 8;  /**< [  7:  0](R/W) When the outbound packet buffer occupancy reaches this point the FIFO will present
                                                                 a full indication to stop the packet pipeline from sending data across the shared async
                                                                 boundary. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_dbg_nicix_config_s cn; */
};
typedef union bdk_tns_tdma_dbg_nicix_config bdk_tns_tdma_dbg_nicix_config_t;

static inline uint64_t BDK_TNS_TDMA_DBG_NICIX_CONFIG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_DBG_NICIX_CONFIG(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=1))
        return 0x842000000b80ll + 0x10ll * ((a) & 0x1);
    __bdk_csr_fatal("TNS_TDMA_DBG_NICIX_CONFIG", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_DBG_NICIX_CONFIG(a) bdk_tns_tdma_dbg_nicix_config_t
#define bustype_BDK_TNS_TDMA_DBG_NICIX_CONFIG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_DBG_NICIX_CONFIG(a) "TNS_TDMA_DBG_NICIX_CONFIG"
#define device_bar_BDK_TNS_TDMA_DBG_NICIX_CONFIG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_DBG_NICIX_CONFIG(a) (a)
#define arguments_BDK_TNS_TDMA_DBG_NICIX_CONFIG(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_ecc_ctl
 *
 * TNS TDMA ECC Control Register
 * This register can be used to disable ECC data correction, insert ECC errors.
 * Fields *ECC_DIS disable SBE data correction. If ECC_DIS is 0x1, then no data correction is
 * performed but errors will still be reported.
 * Fields *ECC_FLIP_SYND flip the syndrome\<1:0\> bits to generate 1-bit/2-bit error for testing.
 * * 0x0 = normal operation.
 * * 0x1 = SBE on bit\<0\>.
 * * 0x2 = SBE on bit\<1\>.
 * * 0x3 = DBE on bits\<1:0\>.
 */
union bdk_tns_tdma_ecc_ctl
{
    uint64_t u;
    struct bdk_tns_tdma_ecc_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_43_63        : 21;
        uint64_t vmem_ecc_dis          : 1;  /**< [ 42: 42](R/W) Disable ECC data correction for MSIX VMEM. */
        uint64_t nici_ecc_dis          : 2;  /**< [ 41: 40](R/W) Disable ECC data correction for NICI FIFOs. */
        uint64_t lmac_ecc_dis          : 8;  /**< [ 39: 32](R/W) Disable ECC data correction for LMAC FIFOs.
                                                                 Bit [32] applies to all BGX0-bound (LMAC0-LMAC3) packets.
                                                                 Bit [33] applies to all BGX1-bound (LMAC4-LMAC7) packets.
                                                                 Bits [39:34] are reserved and should not be used. */
        uint64_t reserved_22_31        : 10;
        uint64_t vmem_ecc_flip_synd    : 2;  /**< [ 21: 20](R/W) Flip syndrome for all data written to MSIX VMEM. */
        uint64_t nici1_ecc_flip_synd   : 2;  /**< [ 19: 18](R/W) Flip syndrome for all data written to NICI1 packet path FIFOs. */
        uint64_t nici0_ecc_flip_synd   : 2;  /**< [ 17: 16](R/W) Flip syndrome for all data written to NICI0 packet path FIFOs. */
        uint64_t lmac7_ecc_flip_synd   : 2;  /**< [ 15: 14](R/W) This field is reserved and should not be written. */
        uint64_t lmac6_ecc_flip_synd   : 2;  /**< [ 13: 12](R/W) This field is reserved and should not be written. */
        uint64_t lmac5_ecc_flip_synd   : 2;  /**< [ 11: 10](R/W) This field is reserved and should not be written. */
        uint64_t lmac4_ecc_flip_synd   : 2;  /**< [  9:  8](R/W) This field is reserved and should not be written. */
        uint64_t lmac3_ecc_flip_synd   : 2;  /**< [  7:  6](R/W) This field is reserved and should not be written. */
        uint64_t lmac2_ecc_flip_synd   : 2;  /**< [  5:  4](R/W) This field is reserved and should not be written. */
        uint64_t lmac1_ecc_flip_synd   : 2;  /**< [  3:  2](R/W) Flip syndrome for all data written to BGX1 (LMAC4-LMAC7) packet path FIFOs. */
        uint64_t lmac0_ecc_flip_synd   : 2;  /**< [  1:  0](R/W) Flip syndrome for all data written to BGX0 (LMAC0-LMAC3) packet path FIFOs. */
#else /* Word 0 - Little Endian */
        uint64_t lmac0_ecc_flip_synd   : 2;  /**< [  1:  0](R/W) Flip syndrome for all data written to BGX0 (LMAC0-LMAC3) packet path FIFOs. */
        uint64_t lmac1_ecc_flip_synd   : 2;  /**< [  3:  2](R/W) Flip syndrome for all data written to BGX1 (LMAC4-LMAC7) packet path FIFOs. */
        uint64_t lmac2_ecc_flip_synd   : 2;  /**< [  5:  4](R/W) This field is reserved and should not be written. */
        uint64_t lmac3_ecc_flip_synd   : 2;  /**< [  7:  6](R/W) This field is reserved and should not be written. */
        uint64_t lmac4_ecc_flip_synd   : 2;  /**< [  9:  8](R/W) This field is reserved and should not be written. */
        uint64_t lmac5_ecc_flip_synd   : 2;  /**< [ 11: 10](R/W) This field is reserved and should not be written. */
        uint64_t lmac6_ecc_flip_synd   : 2;  /**< [ 13: 12](R/W) This field is reserved and should not be written. */
        uint64_t lmac7_ecc_flip_synd   : 2;  /**< [ 15: 14](R/W) This field is reserved and should not be written. */
        uint64_t nici0_ecc_flip_synd   : 2;  /**< [ 17: 16](R/W) Flip syndrome for all data written to NICI0 packet path FIFOs. */
        uint64_t nici1_ecc_flip_synd   : 2;  /**< [ 19: 18](R/W) Flip syndrome for all data written to NICI1 packet path FIFOs. */
        uint64_t vmem_ecc_flip_synd    : 2;  /**< [ 21: 20](R/W) Flip syndrome for all data written to MSIX VMEM. */
        uint64_t reserved_22_31        : 10;
        uint64_t lmac_ecc_dis          : 8;  /**< [ 39: 32](R/W) Disable ECC data correction for LMAC FIFOs.
                                                                 Bit [32] applies to all BGX0-bound (LMAC0-LMAC3) packets.
                                                                 Bit [33] applies to all BGX1-bound (LMAC4-LMAC7) packets.
                                                                 Bits [39:34] are reserved and should not be used. */
        uint64_t nici_ecc_dis          : 2;  /**< [ 41: 40](R/W) Disable ECC data correction for NICI FIFOs. */
        uint64_t vmem_ecc_dis          : 1;  /**< [ 42: 42](R/W) Disable ECC data correction for MSIX VMEM. */
        uint64_t reserved_43_63        : 21;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_ecc_ctl_s cn; */
};
typedef union bdk_tns_tdma_ecc_ctl bdk_tns_tdma_ecc_ctl_t;

#define BDK_TNS_TDMA_ECC_CTL BDK_TNS_TDMA_ECC_CTL_FUNC()
static inline uint64_t BDK_TNS_TDMA_ECC_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_ECC_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000800ll;
    __bdk_csr_fatal("TNS_TDMA_ECC_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_ECC_CTL bdk_tns_tdma_ecc_ctl_t
#define bustype_BDK_TNS_TDMA_ECC_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_ECC_CTL "TNS_TDMA_ECC_CTL"
#define device_bar_BDK_TNS_TDMA_ECC_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_ECC_CTL 0
#define arguments_BDK_TNS_TDMA_ECC_CTL -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_ecc_err_stat
 *
 * TNS TDMA ECC Error Status Register
 * This register logs information to help debug ECC errors.
 */
union bdk_tns_tdma_ecc_err_stat
{
    uint64_t u;
    struct bdk_tns_tdma_ecc_err_stat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t syndrome              : 9;  /**< [ 16:  8](RO/H) Error syndrome. */
        uint64_t reserved_7            : 1;
        uint64_t address               : 7;  /**< [  6:  0](RO/H) Address of ECC error. */
#else /* Word 0 - Little Endian */
        uint64_t address               : 7;  /**< [  6:  0](RO/H) Address of ECC error. */
        uint64_t reserved_7            : 1;
        uint64_t syndrome              : 9;  /**< [ 16:  8](RO/H) Error syndrome. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_ecc_err_stat_s cn; */
};
typedef union bdk_tns_tdma_ecc_err_stat bdk_tns_tdma_ecc_err_stat_t;

#define BDK_TNS_TDMA_ECC_ERR_STAT BDK_TNS_TDMA_ECC_ERR_STAT_FUNC()
static inline uint64_t BDK_TNS_TDMA_ECC_ERR_STAT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_ECC_ERR_STAT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000810ll;
    __bdk_csr_fatal("TNS_TDMA_ECC_ERR_STAT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_ECC_ERR_STAT bdk_tns_tdma_ecc_err_stat_t
#define bustype_BDK_TNS_TDMA_ECC_ERR_STAT BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_ECC_ERR_STAT "TNS_TDMA_ECC_ERR_STAT"
#define device_bar_BDK_TNS_TDMA_ECC_ERR_STAT 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_ECC_ERR_STAT 0
#define arguments_BDK_TNS_TDMA_ECC_ERR_STAT -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_eco
 *
 * INTERNAL: TNS TDMA ECO Register
 *
 * ECO register.
 */
union bdk_tns_tdma_eco
{
    uint64_t u;
    struct bdk_tns_tdma_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t rst1                  : 8;  /**< [ 15:  8](R/W) Reset to 1 spare bits */
        uint64_t rst0                  : 8;  /**< [  7:  0](R/W) Reset to 0 spare bits */
#else /* Word 0 - Little Endian */
        uint64_t rst0                  : 8;  /**< [  7:  0](R/W) Reset to 0 spare bits */
        uint64_t rst1                  : 8;  /**< [ 15:  8](R/W) Reset to 1 spare bits */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_eco_s cn; */
};
typedef union bdk_tns_tdma_eco bdk_tns_tdma_eco_t;

#define BDK_TNS_TDMA_ECO BDK_TNS_TDMA_ECO_FUNC()
static inline uint64_t BDK_TNS_TDMA_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_ECO_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000f00ll;
    __bdk_csr_fatal("TNS_TDMA_ECO", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_ECO bdk_tns_tdma_eco_t
#define bustype_BDK_TNS_TDMA_ECO BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_ECO "TNS_TDMA_ECO"
#define device_bar_BDK_TNS_TDMA_ECO 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_ECO 0
#define arguments_BDK_TNS_TDMA_ECO -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_int_en_w1c
 *
 * TNS TDMA Interrupt Enable (Read/Write-1-Clear) Register
 * TDMA Interrupt Enable Register.
 */
union bdk_tns_tdma_int_en_w1c
{
    uint64_t u;
    struct bdk_tns_tdma_int_en_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_23_63        : 41;
        uint64_t vmem_dbe              : 1;  /**< [ 22: 22](R/W1C/H) Double-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t nici_dbe              : 2;  /**< [ 21: 20](R/W1C/H) Double-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t lmac_dbe              : 8;  /**< [ 19: 12](R/W1C/H) Double-bit ECC error detected on LMAC[7..0] RAM. */
        uint64_t reserved_11           : 1;
        uint64_t vmem_sbe              : 1;  /**< [ 10: 10](R/W1C/H) Single-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t nici_sbe              : 2;  /**< [  9:  8](R/W1C/H) Single-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t lmac_sbe              : 8;  /**< [  7:  0](R/W1C/H) Single-bit ECC error detected on LMAC[7..0] RAM. */
#else /* Word 0 - Little Endian */
        uint64_t lmac_sbe              : 8;  /**< [  7:  0](R/W1C/H) Single-bit ECC error detected on LMAC[7..0] RAM. */
        uint64_t nici_sbe              : 2;  /**< [  9:  8](R/W1C/H) Single-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t vmem_sbe              : 1;  /**< [ 10: 10](R/W1C/H) Single-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t reserved_11           : 1;
        uint64_t lmac_dbe              : 8;  /**< [ 19: 12](R/W1C/H) Double-bit ECC error detected on LMAC[7..0] RAM. */
        uint64_t nici_dbe              : 2;  /**< [ 21: 20](R/W1C/H) Double-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t vmem_dbe              : 1;  /**< [ 22: 22](R/W1C/H) Double-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t reserved_23_63        : 41;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_int_en_w1c_s cn; */
};
typedef union bdk_tns_tdma_int_en_w1c bdk_tns_tdma_int_en_w1c_t;

#define BDK_TNS_TDMA_INT_EN_W1C BDK_TNS_TDMA_INT_EN_W1C_FUNC()
static inline uint64_t BDK_TNS_TDMA_INT_EN_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_INT_EN_W1C_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000130ll;
    __bdk_csr_fatal("TNS_TDMA_INT_EN_W1C", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_INT_EN_W1C bdk_tns_tdma_int_en_w1c_t
#define bustype_BDK_TNS_TDMA_INT_EN_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_INT_EN_W1C "TNS_TDMA_INT_EN_W1C"
#define device_bar_BDK_TNS_TDMA_INT_EN_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_INT_EN_W1C 0
#define arguments_BDK_TNS_TDMA_INT_EN_W1C -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_int_en_w1s
 *
 * TNS TDMA Interrupt Enable (Read/Write-1-Set) Register
 * TDMA Interrupt Enable Register.
 */
union bdk_tns_tdma_int_en_w1s
{
    uint64_t u;
    struct bdk_tns_tdma_int_en_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_23_63        : 41;
        uint64_t vmem_dbe              : 1;  /**< [ 22: 22](R/W1S/H) Double-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t nici_dbe              : 2;  /**< [ 21: 20](R/W1S/H) Double-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t lmac_dbe              : 8;  /**< [ 19: 12](R/W1S/H) Double-bit ECC error detected on LMAC[7..0] RAM. */
        uint64_t reserved_11           : 1;
        uint64_t vmem_sbe              : 1;  /**< [ 10: 10](R/W1S/H) Single-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t nici_sbe              : 2;  /**< [  9:  8](R/W1S/H) Single-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t lmac_sbe              : 8;  /**< [  7:  0](R/W1S/H) Single-bit ECC error detected on LMAC[7..0] RAM. */
#else /* Word 0 - Little Endian */
        uint64_t lmac_sbe              : 8;  /**< [  7:  0](R/W1S/H) Single-bit ECC error detected on LMAC[7..0] RAM. */
        uint64_t nici_sbe              : 2;  /**< [  9:  8](R/W1S/H) Single-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t vmem_sbe              : 1;  /**< [ 10: 10](R/W1S/H) Single-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t reserved_11           : 1;
        uint64_t lmac_dbe              : 8;  /**< [ 19: 12](R/W1S/H) Double-bit ECC error detected on LMAC[7..0] RAM. */
        uint64_t nici_dbe              : 2;  /**< [ 21: 20](R/W1S/H) Double-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t vmem_dbe              : 1;  /**< [ 22: 22](R/W1S/H) Double-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t reserved_23_63        : 41;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_int_en_w1s_s cn; */
};
typedef union bdk_tns_tdma_int_en_w1s bdk_tns_tdma_int_en_w1s_t;

#define BDK_TNS_TDMA_INT_EN_W1S BDK_TNS_TDMA_INT_EN_W1S_FUNC()
static inline uint64_t BDK_TNS_TDMA_INT_EN_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_INT_EN_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000120ll;
    __bdk_csr_fatal("TNS_TDMA_INT_EN_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_INT_EN_W1S bdk_tns_tdma_int_en_w1s_t
#define bustype_BDK_TNS_TDMA_INT_EN_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_INT_EN_W1S "TNS_TDMA_INT_EN_W1S"
#define device_bar_BDK_TNS_TDMA_INT_EN_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_INT_EN_W1S 0
#define arguments_BDK_TNS_TDMA_INT_EN_W1S -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_int_fen_w1c
 *
 * TNS TDMA Interrupt First Enable (Read/Write-1-Clear) Register
 * TDMA Interrupt First Enable Register.
 */
union bdk_tns_tdma_int_fen_w1c
{
    uint64_t u;
    struct bdk_tns_tdma_int_fen_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_23_63        : 41;
        uint64_t vmem_dbe              : 1;  /**< [ 22: 22](R/W1C) Double-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t nici_dbe              : 2;  /**< [ 21: 20](R/W1C) Double-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t lmac_dbe              : 8;  /**< [ 19: 12](R/W1C) Double-bit ECC error detected on LMAC[7..0] RAM. */
        uint64_t reserved_11           : 1;
        uint64_t vmem_sbe              : 1;  /**< [ 10: 10](R/W1C) Single-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t nici_sbe              : 2;  /**< [  9:  8](R/W1C) Single-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t lmac_sbe              : 8;  /**< [  7:  0](R/W1C) Single-bit ECC error detected on LMAC[7..0] RAM. */
#else /* Word 0 - Little Endian */
        uint64_t lmac_sbe              : 8;  /**< [  7:  0](R/W1C) Single-bit ECC error detected on LMAC[7..0] RAM. */
        uint64_t nici_sbe              : 2;  /**< [  9:  8](R/W1C) Single-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t vmem_sbe              : 1;  /**< [ 10: 10](R/W1C) Single-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t reserved_11           : 1;
        uint64_t lmac_dbe              : 8;  /**< [ 19: 12](R/W1C) Double-bit ECC error detected on LMAC[7..0] RAM. */
        uint64_t nici_dbe              : 2;  /**< [ 21: 20](R/W1C) Double-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t vmem_dbe              : 1;  /**< [ 22: 22](R/W1C) Double-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t reserved_23_63        : 41;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_int_fen_w1c_s cn; */
};
typedef union bdk_tns_tdma_int_fen_w1c bdk_tns_tdma_int_fen_w1c_t;

#define BDK_TNS_TDMA_INT_FEN_W1C BDK_TNS_TDMA_INT_FEN_W1C_FUNC()
static inline uint64_t BDK_TNS_TDMA_INT_FEN_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_INT_FEN_W1C_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000160ll;
    __bdk_csr_fatal("TNS_TDMA_INT_FEN_W1C", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_INT_FEN_W1C bdk_tns_tdma_int_fen_w1c_t
#define bustype_BDK_TNS_TDMA_INT_FEN_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_INT_FEN_W1C "TNS_TDMA_INT_FEN_W1C"
#define device_bar_BDK_TNS_TDMA_INT_FEN_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_INT_FEN_W1C 0
#define arguments_BDK_TNS_TDMA_INT_FEN_W1C -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_int_fen_w1s
 *
 * TNS TDMA Interrupt First Enable (Read/Write-1-Set) Register
 * TDMA Interrupt First Enable Register.
 */
union bdk_tns_tdma_int_fen_w1s
{
    uint64_t u;
    struct bdk_tns_tdma_int_fen_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_23_63        : 41;
        uint64_t vmem_dbe              : 1;  /**< [ 22: 22](R/W1S) Double-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t nici_dbe              : 2;  /**< [ 21: 20](R/W1S) Double-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t lmac_dbe              : 8;  /**< [ 19: 12](R/W1S) Double-bit ECC error detected on LMAC[7..0] RAM. */
        uint64_t reserved_11           : 1;
        uint64_t vmem_sbe              : 1;  /**< [ 10: 10](R/W1S) Single-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t nici_sbe              : 2;  /**< [  9:  8](R/W1S) Single-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t lmac_sbe              : 8;  /**< [  7:  0](R/W1S) Single-bit ECC error detected on LMAC[7..0] RAM. */
#else /* Word 0 - Little Endian */
        uint64_t lmac_sbe              : 8;  /**< [  7:  0](R/W1S) Single-bit ECC error detected on LMAC[7..0] RAM. */
        uint64_t nici_sbe              : 2;  /**< [  9:  8](R/W1S) Single-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t vmem_sbe              : 1;  /**< [ 10: 10](R/W1S) Single-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t reserved_11           : 1;
        uint64_t lmac_dbe              : 8;  /**< [ 19: 12](R/W1S) Double-bit ECC error detected on LMAC[7..0] RAM. */
        uint64_t nici_dbe              : 2;  /**< [ 21: 20](R/W1S) Double-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t vmem_dbe              : 1;  /**< [ 22: 22](R/W1S) Double-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t reserved_23_63        : 41;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_int_fen_w1s_s cn; */
};
typedef union bdk_tns_tdma_int_fen_w1s bdk_tns_tdma_int_fen_w1s_t;

#define BDK_TNS_TDMA_INT_FEN_W1S BDK_TNS_TDMA_INT_FEN_W1S_FUNC()
static inline uint64_t BDK_TNS_TDMA_INT_FEN_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_INT_FEN_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000150ll;
    __bdk_csr_fatal("TNS_TDMA_INT_FEN_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_INT_FEN_W1S bdk_tns_tdma_int_fen_w1s_t
#define bustype_BDK_TNS_TDMA_INT_FEN_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_INT_FEN_W1S "TNS_TDMA_INT_FEN_W1S"
#define device_bar_BDK_TNS_TDMA_INT_FEN_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_INT_FEN_W1S 0
#define arguments_BDK_TNS_TDMA_INT_FEN_W1S -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_int_fstat
 *
 * TNS TDMA Interrupt First Status Register
 * TDMA Interrupt First Status Register.
 */
union bdk_tns_tdma_int_fstat
{
    uint64_t u;
    struct bdk_tns_tdma_int_fstat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_23_63        : 41;
        uint64_t vmem_dbe              : 1;  /**< [ 22: 22](RO/H) Double-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t nici_dbe              : 2;  /**< [ 21: 20](RO/H) Double-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t lmac_dbe              : 8;  /**< [ 19: 12](RO/H) Double-bit ECC error detected on LMAC[7..0] RAM. */
        uint64_t reserved_11           : 1;
        uint64_t vmem_sbe              : 1;  /**< [ 10: 10](RO/H) Single-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t nici_sbe              : 2;  /**< [  9:  8](RO/H) Single-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t lmac_sbe              : 8;  /**< [  7:  0](RO/H) Single-bit ECC error detected on LMAC[7..0] RAM. */
#else /* Word 0 - Little Endian */
        uint64_t lmac_sbe              : 8;  /**< [  7:  0](RO/H) Single-bit ECC error detected on LMAC[7..0] RAM. */
        uint64_t nici_sbe              : 2;  /**< [  9:  8](RO/H) Single-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t vmem_sbe              : 1;  /**< [ 10: 10](RO/H) Single-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t reserved_11           : 1;
        uint64_t lmac_dbe              : 8;  /**< [ 19: 12](RO/H) Double-bit ECC error detected on LMAC[7..0] RAM. */
        uint64_t nici_dbe              : 2;  /**< [ 21: 20](RO/H) Double-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t vmem_dbe              : 1;  /**< [ 22: 22](RO/H) Double-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t reserved_23_63        : 41;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_int_fstat_s cn; */
};
typedef union bdk_tns_tdma_int_fstat bdk_tns_tdma_int_fstat_t;

#define BDK_TNS_TDMA_INT_FSTAT BDK_TNS_TDMA_INT_FSTAT_FUNC()
static inline uint64_t BDK_TNS_TDMA_INT_FSTAT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_INT_FSTAT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000140ll;
    __bdk_csr_fatal("TNS_TDMA_INT_FSTAT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_INT_FSTAT bdk_tns_tdma_int_fstat_t
#define bustype_BDK_TNS_TDMA_INT_FSTAT BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_INT_FSTAT "TNS_TDMA_INT_FSTAT"
#define device_bar_BDK_TNS_TDMA_INT_FSTAT 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_INT_FSTAT 0
#define arguments_BDK_TNS_TDMA_INT_FSTAT -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_int_stat_w1c
 *
 * TNS TDMA Interrupt Status (Read/Write-1-Clear) Register
 * TDMA Interrupt Status Register.
 */
union bdk_tns_tdma_int_stat_w1c
{
    uint64_t u;
    struct bdk_tns_tdma_int_stat_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_23_63        : 41;
        uint64_t vmem_dbe              : 1;  /**< [ 22: 22](R/W1C/H) Double-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t nici_dbe              : 2;  /**< [ 21: 20](R/W1C/H) Double-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t lmac_dbe              : 8;  /**< [ 19: 12](R/W1C/H) Double-bit ECC error detected on LMAC[7..0] RAM. */
        uint64_t reserved_11           : 1;
        uint64_t vmem_sbe              : 1;  /**< [ 10: 10](R/W1C/H) Single-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t nici_sbe              : 2;  /**< [  9:  8](R/W1C/H) Single-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t lmac_sbe              : 8;  /**< [  7:  0](R/W1C/H) Single-bit ECC error detected on LMAC[7..0] RAM. */
#else /* Word 0 - Little Endian */
        uint64_t lmac_sbe              : 8;  /**< [  7:  0](R/W1C/H) Single-bit ECC error detected on LMAC[7..0] RAM. */
        uint64_t nici_sbe              : 2;  /**< [  9:  8](R/W1C/H) Single-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t vmem_sbe              : 1;  /**< [ 10: 10](R/W1C/H) Single-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t reserved_11           : 1;
        uint64_t lmac_dbe              : 8;  /**< [ 19: 12](R/W1C/H) Double-bit ECC error detected on LMAC[7..0] RAM. */
        uint64_t nici_dbe              : 2;  /**< [ 21: 20](R/W1C/H) Double-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t vmem_dbe              : 1;  /**< [ 22: 22](R/W1C/H) Double-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t reserved_23_63        : 41;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_int_stat_w1c_s cn; */
};
typedef union bdk_tns_tdma_int_stat_w1c bdk_tns_tdma_int_stat_w1c_t;

#define BDK_TNS_TDMA_INT_STAT_W1C BDK_TNS_TDMA_INT_STAT_W1C_FUNC()
static inline uint64_t BDK_TNS_TDMA_INT_STAT_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_INT_STAT_W1C_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000110ll;
    __bdk_csr_fatal("TNS_TDMA_INT_STAT_W1C", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_INT_STAT_W1C bdk_tns_tdma_int_stat_w1c_t
#define bustype_BDK_TNS_TDMA_INT_STAT_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_INT_STAT_W1C "TNS_TDMA_INT_STAT_W1C"
#define device_bar_BDK_TNS_TDMA_INT_STAT_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_INT_STAT_W1C 0
#define arguments_BDK_TNS_TDMA_INT_STAT_W1C -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_int_stat_w1s
 *
 * TNS TDMA Interrupt Status (Read/Write-1-Set) Register
 * TDMA Interrupt Status Register.
 */
union bdk_tns_tdma_int_stat_w1s
{
    uint64_t u;
    struct bdk_tns_tdma_int_stat_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_23_63        : 41;
        uint64_t vmem_dbe              : 1;  /**< [ 22: 22](R/W1S/H) Double-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t nici_dbe              : 2;  /**< [ 21: 20](R/W1S/H) Double-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t lmac_dbe              : 8;  /**< [ 19: 12](R/W1S/H) Double-bit ECC error detected on LMAC[7..0] RAM. */
        uint64_t reserved_11           : 1;
        uint64_t vmem_sbe              : 1;  /**< [ 10: 10](R/W1S/H) Single-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t nici_sbe              : 2;  /**< [  9:  8](R/W1S/H) Single-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t lmac_sbe              : 8;  /**< [  7:  0](R/W1S/H) Single-bit ECC error detected on LMAC[7..0] RAM. */
#else /* Word 0 - Little Endian */
        uint64_t lmac_sbe              : 8;  /**< [  7:  0](R/W1S/H) Single-bit ECC error detected on LMAC[7..0] RAM. */
        uint64_t nici_sbe              : 2;  /**< [  9:  8](R/W1S/H) Single-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t vmem_sbe              : 1;  /**< [ 10: 10](R/W1S/H) Single-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t reserved_11           : 1;
        uint64_t lmac_dbe              : 8;  /**< [ 19: 12](R/W1S/H) Double-bit ECC error detected on LMAC[7..0] RAM. */
        uint64_t nici_dbe              : 2;  /**< [ 21: 20](R/W1S/H) Double-bit ECC error detected on NICI[1..0] RAM. */
        uint64_t vmem_dbe              : 1;  /**< [ 22: 22](R/W1S/H) Double-bit ECC error detected on MSIX VMEM RAM. */
        uint64_t reserved_23_63        : 41;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_int_stat_w1s_s cn; */
};
typedef union bdk_tns_tdma_int_stat_w1s bdk_tns_tdma_int_stat_w1s_t;

#define BDK_TNS_TDMA_INT_STAT_W1S BDK_TNS_TDMA_INT_STAT_W1S_FUNC()
static inline uint64_t BDK_TNS_TDMA_INT_STAT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_INT_STAT_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000100ll;
    __bdk_csr_fatal("TNS_TDMA_INT_STAT_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_INT_STAT_W1S bdk_tns_tdma_int_stat_w1s_t
#define bustype_BDK_TNS_TDMA_INT_STAT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_INT_STAT_W1S "TNS_TDMA_INT_STAT_W1S"
#define device_bar_BDK_TNS_TDMA_INT_STAT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_INT_STAT_W1S 0
#define arguments_BDK_TNS_TDMA_INT_STAT_W1S -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_lmac#_config
 *
 * TNS TDMA LMAC Config Register
 * This register provides control of TDMA functionality.
 */
union bdk_tns_tdma_lmacx_config
{
    uint64_t u;
    struct bdk_tns_tdma_lmacx_config_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t fifo_cdts             : 14; /**< [ 13:  0](R/W) Initial credits available for sending data to the LMAC.
                                                                 Each credit represents 1 16-byte flit towards the LMAC.
                                                                 This field must be configured to be less than or equal to the configured FIFO
                                                                 size of the destination LMAC.
                                                                 Software may not change this field while packets are flowing towards the LMAC. */
#else /* Word 0 - Little Endian */
        uint64_t fifo_cdts             : 14; /**< [ 13:  0](R/W) Initial credits available for sending data to the LMAC.
                                                                 Each credit represents 1 16-byte flit towards the LMAC.
                                                                 This field must be configured to be less than or equal to the configured FIFO
                                                                 size of the destination LMAC.
                                                                 Software may not change this field while packets are flowing towards the LMAC. */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_lmacx_config_s cn; */
};
typedef union bdk_tns_tdma_lmacx_config bdk_tns_tdma_lmacx_config_t;

static inline uint64_t BDK_TNS_TDMA_LMACX_CONFIG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_LMACX_CONFIG(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=7))
        return 0x842000000300ll + 0x10ll * ((a) & 0x7);
    __bdk_csr_fatal("TNS_TDMA_LMACX_CONFIG", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_LMACX_CONFIG(a) bdk_tns_tdma_lmacx_config_t
#define bustype_BDK_TNS_TDMA_LMACX_CONFIG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_LMACX_CONFIG(a) "TNS_TDMA_LMACX_CONFIG"
#define device_bar_BDK_TNS_TDMA_LMACX_CONFIG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_LMACX_CONFIG(a) (a)
#define arguments_BDK_TNS_TDMA_LMACX_CONFIG(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_config1
 *
 * TNS TDMA Configuration Register
 * General configuration register.
 */
union bdk_tns_tdma_nb_config1
{
    uint64_t u;
    struct bdk_tns_tdma_nb_config1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t master_en             : 1;  /**< [ 63: 63](R/W/H) Allows packet data to be stored in the packet memory.
                                                                 To reset the data path, TNS_RDMA_NB_PATH_ENABLE, TNS_RDMA_NB_CONFIG[MASTER_EN],
                                                                 and this field must all be cleared before performing hardware auto-initialization.
                                                                 Usage of hardware AUTO_INIT will clear this field.

                                                                 Internal:
                                                                 Enables page pointers from the FPM to be allocated to RDMA for use. */
        uint64_t drain_pkts            : 11; /**< [ 62: 52](R/W) Discard packets destined towards a physical port.
                                                                 Rather than transmit a packet on its physical port the TDMA will drop the packet.
                                                                 The decision to drain a packet is made on a packet boundary.
                                                                 A packet that is in progress when this field is set will be allowed to complete
                                                                 transmission.
                                                                 The bit positions correspond to the enumeration as defined in TNS_PHYS_PORT_E. */
        uint64_t auto_init             : 1;  /**< [ 51: 51](R/W/H) Initiate hardware auto-initialization of TNS.
                                                                 To begin initialization, software writes a 1 to this field.
                                                                 Upon completion of auto-initialization, hardware will clear this field
                                                                 and will also set TNS_TDMA_NB_STATUS[INIT_DONE].

                                                                 Internal:
                                                                 Fills TDMA FPM to desired depth.
                                                                 Clears TDMA PRC counters to 0x0. */
        uint64_t reserved_50           : 1;
        uint64_t pm_depth              : 2;  /**< [ 49: 48](R/W) Set the usable size of the Packet Memory.
                                                                 0x0 = Use full packet memory.
                                                                 0x1 = Use 1/2 packet memory.
                                                                 0x2 = Use 1/4 packet memory.
                                                                 0x3 = Use 1/8 packet memory.
                                                                 AUTO_INIT must be performed after changing this field.

                                                                 Internal:
                                                                 TNS has a 3MB packet memory. So...
                                                                 0x0 = 3MB.
                                                                 0x1 = 1.5MB.
                                                                 0x2 = 768kB.
                                                                 0x3 = 384kB. */
        uint64_t reserved_46_47        : 2;
        uint64_t nici1_pknd            : 6;  /**< [ 45: 40](R/W) Port kind for packets destined to NICI1. */
        uint64_t reserved_38_39        : 2;
        uint64_t nici0_pknd            : 6;  /**< [ 37: 32](R/W) Port kind for packets destined to NICI0. */
        uint64_t txq_qmap_link_up      : 16; /**< [ 31: 16](R/W) Advertise to the TxQ's QMAP logic that a physical port link is available to
                                                                 transmit packets.
                                                                 The bit positions correspond to the enumeration as defined in TNS_PHYS_PORT_E.
                                                                 Bit positions not enumerated are undefined.
                                                                 When changing the value in this field, software must also at the same time
                                                                 set TXQ_EQ_LINK_UP to match the value being written here. */
        uint64_t txq_eq_link_up        : 16; /**< [ 15:  0](R/W) Advertise to the TxQ's enqueue logic that a physical port link is available to
                                                                 transmit packets.
                                                                 The bit positions correspond to the enumeration as defined in TNS_PHYS_PORT_E.
                                                                 Bit positions not enumerated are undefined.
                                                                 When changing the value in this field, software must also at the same time
                                                                 set TXQ_QMAP_LINK_UP to match the value being written here. */
#else /* Word 0 - Little Endian */
        uint64_t txq_eq_link_up        : 16; /**< [ 15:  0](R/W) Advertise to the TxQ's enqueue logic that a physical port link is available to
                                                                 transmit packets.
                                                                 The bit positions correspond to the enumeration as defined in TNS_PHYS_PORT_E.
                                                                 Bit positions not enumerated are undefined.
                                                                 When changing the value in this field, software must also at the same time
                                                                 set TXQ_QMAP_LINK_UP to match the value being written here. */
        uint64_t txq_qmap_link_up      : 16; /**< [ 31: 16](R/W) Advertise to the TxQ's QMAP logic that a physical port link is available to
                                                                 transmit packets.
                                                                 The bit positions correspond to the enumeration as defined in TNS_PHYS_PORT_E.
                                                                 Bit positions not enumerated are undefined.
                                                                 When changing the value in this field, software must also at the same time
                                                                 set TXQ_EQ_LINK_UP to match the value being written here. */
        uint64_t nici0_pknd            : 6;  /**< [ 37: 32](R/W) Port kind for packets destined to NICI0. */
        uint64_t reserved_38_39        : 2;
        uint64_t nici1_pknd            : 6;  /**< [ 45: 40](R/W) Port kind for packets destined to NICI1. */
        uint64_t reserved_46_47        : 2;
        uint64_t pm_depth              : 2;  /**< [ 49: 48](R/W) Set the usable size of the Packet Memory.
                                                                 0x0 = Use full packet memory.
                                                                 0x1 = Use 1/2 packet memory.
                                                                 0x2 = Use 1/4 packet memory.
                                                                 0x3 = Use 1/8 packet memory.
                                                                 AUTO_INIT must be performed after changing this field.

                                                                 Internal:
                                                                 TNS has a 3MB packet memory. So...
                                                                 0x0 = 3MB.
                                                                 0x1 = 1.5MB.
                                                                 0x2 = 768kB.
                                                                 0x3 = 384kB. */
        uint64_t reserved_50           : 1;
        uint64_t auto_init             : 1;  /**< [ 51: 51](R/W/H) Initiate hardware auto-initialization of TNS.
                                                                 To begin initialization, software writes a 1 to this field.
                                                                 Upon completion of auto-initialization, hardware will clear this field
                                                                 and will also set TNS_TDMA_NB_STATUS[INIT_DONE].

                                                                 Internal:
                                                                 Fills TDMA FPM to desired depth.
                                                                 Clears TDMA PRC counters to 0x0. */
        uint64_t drain_pkts            : 11; /**< [ 62: 52](R/W) Discard packets destined towards a physical port.
                                                                 Rather than transmit a packet on its physical port the TDMA will drop the packet.
                                                                 The decision to drain a packet is made on a packet boundary.
                                                                 A packet that is in progress when this field is set will be allowed to complete
                                                                 transmission.
                                                                 The bit positions correspond to the enumeration as defined in TNS_PHYS_PORT_E. */
        uint64_t master_en             : 1;  /**< [ 63: 63](R/W/H) Allows packet data to be stored in the packet memory.
                                                                 To reset the data path, TNS_RDMA_NB_PATH_ENABLE, TNS_RDMA_NB_CONFIG[MASTER_EN],
                                                                 and this field must all be cleared before performing hardware auto-initialization.
                                                                 Usage of hardware AUTO_INIT will clear this field.

                                                                 Internal:
                                                                 Enables page pointers from the FPM to be allocated to RDMA for use. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_config1_s cn; */
};
typedef union bdk_tns_tdma_nb_config1 bdk_tns_tdma_nb_config1_t;

#define BDK_TNS_TDMA_NB_CONFIG1 BDK_TNS_TDMA_NB_CONFIG1_FUNC()
static inline uint64_t BDK_TNS_TDMA_NB_CONFIG1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_CONFIG1_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842041000200ll;
    __bdk_csr_fatal("TNS_TDMA_NB_CONFIG1", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_CONFIG1 bdk_tns_tdma_nb_config1_t
#define bustype_BDK_TNS_TDMA_NB_CONFIG1 BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_CONFIG1 "TNS_TDMA_NB_CONFIG1"
#define device_bar_BDK_TNS_TDMA_NB_CONFIG1 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_CONFIG1 0
#define arguments_BDK_TNS_TDMA_NB_CONFIG1 -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_config2
 *
 * INTERNAL: TNS TDMA Configuration Register
 *
 * General configuration register.
 */
union bdk_tns_tdma_nb_config2
{
    uint64_t u;
    struct bdk_tns_tdma_nb_config2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t sst_req_inc           : 1;  /**< [ 63: 63](R/W) Designated value of the INC field within a SST read or write request. */
        uint64_t reserved_62           : 1;
        uint64_t sst_endian            : 2;  /**< [ 61: 60](R/W) Byte swapping of CSR data when accessing the SST blocks.
                                                                 0x0 = ABCDEFGH (no swap).
                                                                 0x1 = EFGHABCD (swap 32-bit chunk within 64-bit word).
                                                                 0x2 = DCBAHGFE (swap bytes within 32-bit chunk).
                                                                 0x3 = HGFEDCBA (swap 32-bit chunks within 64-bit word and swap bytes within chunk). */
        uint64_t reserved_0_59         : 60;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_59         : 60;
        uint64_t sst_endian            : 2;  /**< [ 61: 60](R/W) Byte swapping of CSR data when accessing the SST blocks.
                                                                 0x0 = ABCDEFGH (no swap).
                                                                 0x1 = EFGHABCD (swap 32-bit chunk within 64-bit word).
                                                                 0x2 = DCBAHGFE (swap bytes within 32-bit chunk).
                                                                 0x3 = HGFEDCBA (swap 32-bit chunks within 64-bit word and swap bytes within chunk). */
        uint64_t reserved_62           : 1;
        uint64_t sst_req_inc           : 1;  /**< [ 63: 63](R/W) Designated value of the INC field within a SST read or write request. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_config2_s cn; */
};
typedef union bdk_tns_tdma_nb_config2 bdk_tns_tdma_nb_config2_t;

#define BDK_TNS_TDMA_NB_CONFIG2 BDK_TNS_TDMA_NB_CONFIG2_FUNC()
static inline uint64_t BDK_TNS_TDMA_NB_CONFIG2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_CONFIG2_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842041000210ll;
    __bdk_csr_fatal("TNS_TDMA_NB_CONFIG2", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_CONFIG2 bdk_tns_tdma_nb_config2_t
#define bustype_BDK_TNS_TDMA_NB_CONFIG2 BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_CONFIG2 "TNS_TDMA_NB_CONFIG2"
#define device_bar_BDK_TNS_TDMA_NB_CONFIG2 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_CONFIG2 0
#define arguments_BDK_TNS_TDMA_NB_CONFIG2 -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_dbg_config1
 *
 * INTERNAL: TNS TDMA Debug Config1 Register
 *
 * This register provides debug control of TDMA functionality.
 */
union bdk_tns_tdma_nb_dbg_config1
{
    uint64_t u;
    struct bdk_tns_tdma_nb_dbg_config1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t cutthru_chk           : 1;  /**< [ 43: 43](R/W) Enable cut-thru packet checks.
                                                                 When set, the TDMA performs additional checks to avoid reading
                                                                 too far in to the page pointer link list if the sequence number of
                                                                 the packet to be transmitted matches the sequence number of the
                                                                 packet currently being received on the physical source port on which
                                                                 the packet to be transmitted had arrived.
                                                                 For each port where CUTTHRU_CHK is set and the corresponding
                                                                 *_CUTTHRU_EN field is 0, the data path will operate in a
                                                                 store-and-forward mode, stopping packet transmission if the packet
                                                                 being transmitted appears to be in receipt.
                                                                 When this field is 0, the TDMA packet checks are disabled and the
                                                                 data path will walk the packet link list until the packet's EOP
                                                                 is reached.
                                                                 In order to prevent unnecessary stalling during packet
                                                                 transmission, this field should be 0 when the TNS Parser or TxQ
                                                                 is configured for all ports to operate in a store-and-forward mode.
                                                                 This field has no effect on those TDMA ports where the associated
                                                                 *_CUTTHRU_EN field is set. */
        uint64_t lb_cutthru_en         : 1;  /**< [ 42: 42](R/W) Enable cut-thru packet checks and transmission on the internal
                                                                 loopback bus.
                                                                 When set, the TDMA performs packet checks to avoid reading
                                                                 too far in to the page pointer link list if the sequence number of
                                                                 the packet to be transmitted matches the sequence number of the
                                                                 packet currently being received on the physical source port on which
                                                                 the packet to be transmitted had arrived (or is arriving).
                                                                 Setting this bit turns on the cut-through packet checks for the
                                                                 internal loopback path that otherwise would be enabled by CUTTHRU_CHK,
                                                                 with the added benefit of allowing cut-through packet transmission
                                                                 on the internal loopback bus for packets that enter the TDMA.
                                                                 This bit must be set if the TNS is to operate in cut-through mode.
                                                                 If the TNS is operating in a store-and-forward mode this bit should
                                                                 be cleared to prevent unnecessary stalling during packet transmission
                                                                 due to the cut-through packet checks possibly determining the packet
                                                                 to be transmitted is currently being received. */
        uint64_t lmac_cutthru_en       : 1;  /**< [ 41: 41](R/W) Enable cut-thru packet checks and transmission towards the LMAC ports.
                                                                 When set, the TDMA performs packet checks to avoid reading
                                                                 too far in to the page pointer link list if the sequence number of
                                                                 the packet to be transmitted matches the sequence number of the
                                                                 packet currently being received on the physical source port on which
                                                                 the packet to be transmitted had arrived (or is arriving).
                                                                 Setting this bit turns on the cut-through packet checks for
                                                                 LMAC-destined packets that otherwise would be enabled by CUTTHRU_CHK,
                                                                 with the added benefit of allowing cut-through packet transmission
                                                                 towards the LMACs for packets that enter the TDMA.
                                                                 This bit must be set if the TNS is to operate in cut-through mode.
                                                                 If the TNS is operating in a store-and-forward mode this bit should
                                                                 be cleared to prevent unnecessary stalling during packet transmission
                                                                 due to the cut-through packet checks possibly determining the packet
                                                                 to be transmitted is currently being received. */
        uint64_t nic_cutthru_en        : 1;  /**< [ 40: 40](R/W) Enable cut-thru packet checks and transmission towards the NIC.
                                                                 When set, the TDMA performs packet checks to avoid reading
                                                                 too far in to the page pointer link list if the sequence number of
                                                                 the packet to be transmitted matches the sequence number of the
                                                                 packet currently being received on the physical source port on which
                                                                 the packet to be transmitted had arrived (or is arriving).
                                                                 Setting this bit turns on the cut-through packet checks for
                                                                 NIC-destined packets that otherwise would be enabled by CUTTHRU_CHK,
                                                                 with the added benefit of allowing cut-through packet transmission
                                                                 towards the NIC for packets that enter the TDMA.
                                                                 This bit must be set if the TNS is to operate in cut-through mode.
                                                                 If the TNS is operating in a store-and-forward mode this bit should
                                                                 be cleared to prevent unnecessary stalling during packet transmission
                                                                 due to the cut-through packet checks possibly determining the packet
                                                                 to be transmitted is currently being received. */
        uint64_t reserved_37_39        : 3;
        uint64_t lb_init_cdts          : 5;  /**< [ 36: 32](R/W) The flow of data from the TDMA to the RDMA along the internal loopback path is
                                                                 metered by credits.
                                                                 Each credit represents the transfer of a 32-byte flit.
                                                                 A maximum of 16 (decimal) credits is allowed.
                                                                 A minimum of 2 credits is required for proper operation. */
        uint64_t reserved_29_31        : 3;
        uint64_t txq_drop_req_thresh   : 5;  /**< [ 28: 24](R/W) Requests to drop packets are received from the TxQ.
                                                                 Arriving requests can take one of two paths:
                                                                 _ 1) For a single-copy packet the request is pushed to a 16-entry FIFO
                                                                 _    in the Link List walker logic.
                                                                 _ 2) For a multiple-copy packet the request is pushed to a 16-entry FIFO
                                                                 _    in the Page Reference Count logic.
                                                                 If the occupancy of either of these FIFOs reaches the value programmed in this field
                                                                 the data path will assert flow control to the TxQ to prevent additional drop requests
                                                                 from arriving. */
        uint64_t reserved_21_23        : 3;
        uint64_t p2x_tkn_sch_thresh    : 5;  /**< [ 20: 16](R/W) Each of the 8 BGX LMAC ports has a FIFO for receiving transmit request tokens from
                                                                 the port's per-priority Token FIFOs.
                                                                 Each LMAC FIFO can store 8 tokens.
                                                                 This value indicates the number of tokens at which the FIFO will stop pulling tokens
                                                                 from the port's per-priority Token FIFOs. */
        uint64_t reserved_13_15        : 3;
        uint64_t lb_tkn_sch_thresh     : 5;  /**< [ 12:  8](R/W) The internal loopback path has a FIFO for receiving tokens from the TxQ block.
                                                                 The FIFO can store 8 tokens.
                                                                 This value indicates the number of tokens at which the port available signal to
                                                                 the TxQ is to be de-asserted.
                                                                 The value includes tokens in the FIFO as well as the in-flight tokens
                                                                 (schedule received but token not yet received). */
        uint64_t reserved_5_7          : 3;
        uint64_t x2p_tkn_sch_thresh    : 5;  /**< [  4:  0](R/W) Both NIC Interfaces have a FIFO for receiving tokens from the TxQ block.
                                                                 Each FIFO can store 8 tokens.
                                                                 This value indicates the number of tokens at which the port available signal to
                                                                 the TxQ is to be de-asserted.
                                                                 The value includes tokens in the FIFO as well as the in-flight tokens
                                                                 (schedule received but token not yet received). */
#else /* Word 0 - Little Endian */
        uint64_t x2p_tkn_sch_thresh    : 5;  /**< [  4:  0](R/W) Both NIC Interfaces have a FIFO for receiving tokens from the TxQ block.
                                                                 Each FIFO can store 8 tokens.
                                                                 This value indicates the number of tokens at which the port available signal to
                                                                 the TxQ is to be de-asserted.
                                                                 The value includes tokens in the FIFO as well as the in-flight tokens
                                                                 (schedule received but token not yet received). */
        uint64_t reserved_5_7          : 3;
        uint64_t lb_tkn_sch_thresh     : 5;  /**< [ 12:  8](R/W) The internal loopback path has a FIFO for receiving tokens from the TxQ block.
                                                                 The FIFO can store 8 tokens.
                                                                 This value indicates the number of tokens at which the port available signal to
                                                                 the TxQ is to be de-asserted.
                                                                 The value includes tokens in the FIFO as well as the in-flight tokens
                                                                 (schedule received but token not yet received). */
        uint64_t reserved_13_15        : 3;
        uint64_t p2x_tkn_sch_thresh    : 5;  /**< [ 20: 16](R/W) Each of the 8 BGX LMAC ports has a FIFO for receiving transmit request tokens from
                                                                 the port's per-priority Token FIFOs.
                                                                 Each LMAC FIFO can store 8 tokens.
                                                                 This value indicates the number of tokens at which the FIFO will stop pulling tokens
                                                                 from the port's per-priority Token FIFOs. */
        uint64_t reserved_21_23        : 3;
        uint64_t txq_drop_req_thresh   : 5;  /**< [ 28: 24](R/W) Requests to drop packets are received from the TxQ.
                                                                 Arriving requests can take one of two paths:
                                                                 _ 1) For a single-copy packet the request is pushed to a 16-entry FIFO
                                                                 _    in the Link List walker logic.
                                                                 _ 2) For a multiple-copy packet the request is pushed to a 16-entry FIFO
                                                                 _    in the Page Reference Count logic.
                                                                 If the occupancy of either of these FIFOs reaches the value programmed in this field
                                                                 the data path will assert flow control to the TxQ to prevent additional drop requests
                                                                 from arriving. */
        uint64_t reserved_29_31        : 3;
        uint64_t lb_init_cdts          : 5;  /**< [ 36: 32](R/W) The flow of data from the TDMA to the RDMA along the internal loopback path is
                                                                 metered by credits.
                                                                 Each credit represents the transfer of a 32-byte flit.
                                                                 A maximum of 16 (decimal) credits is allowed.
                                                                 A minimum of 2 credits is required for proper operation. */
        uint64_t reserved_37_39        : 3;
        uint64_t nic_cutthru_en        : 1;  /**< [ 40: 40](R/W) Enable cut-thru packet checks and transmission towards the NIC.
                                                                 When set, the TDMA performs packet checks to avoid reading
                                                                 too far in to the page pointer link list if the sequence number of
                                                                 the packet to be transmitted matches the sequence number of the
                                                                 packet currently being received on the physical source port on which
                                                                 the packet to be transmitted had arrived (or is arriving).
                                                                 Setting this bit turns on the cut-through packet checks for
                                                                 NIC-destined packets that otherwise would be enabled by CUTTHRU_CHK,
                                                                 with the added benefit of allowing cut-through packet transmission
                                                                 towards the NIC for packets that enter the TDMA.
                                                                 This bit must be set if the TNS is to operate in cut-through mode.
                                                                 If the TNS is operating in a store-and-forward mode this bit should
                                                                 be cleared to prevent unnecessary stalling during packet transmission
                                                                 due to the cut-through packet checks possibly determining the packet
                                                                 to be transmitted is currently being received. */
        uint64_t lmac_cutthru_en       : 1;  /**< [ 41: 41](R/W) Enable cut-thru packet checks and transmission towards the LMAC ports.
                                                                 When set, the TDMA performs packet checks to avoid reading
                                                                 too far in to the page pointer link list if the sequence number of
                                                                 the packet to be transmitted matches the sequence number of the
                                                                 packet currently being received on the physical source port on which
                                                                 the packet to be transmitted had arrived (or is arriving).
                                                                 Setting this bit turns on the cut-through packet checks for
                                                                 LMAC-destined packets that otherwise would be enabled by CUTTHRU_CHK,
                                                                 with the added benefit of allowing cut-through packet transmission
                                                                 towards the LMACs for packets that enter the TDMA.
                                                                 This bit must be set if the TNS is to operate in cut-through mode.
                                                                 If the TNS is operating in a store-and-forward mode this bit should
                                                                 be cleared to prevent unnecessary stalling during packet transmission
                                                                 due to the cut-through packet checks possibly determining the packet
                                                                 to be transmitted is currently being received. */
        uint64_t lb_cutthru_en         : 1;  /**< [ 42: 42](R/W) Enable cut-thru packet checks and transmission on the internal
                                                                 loopback bus.
                                                                 When set, the TDMA performs packet checks to avoid reading
                                                                 too far in to the page pointer link list if the sequence number of
                                                                 the packet to be transmitted matches the sequence number of the
                                                                 packet currently being received on the physical source port on which
                                                                 the packet to be transmitted had arrived (or is arriving).
                                                                 Setting this bit turns on the cut-through packet checks for the
                                                                 internal loopback path that otherwise would be enabled by CUTTHRU_CHK,
                                                                 with the added benefit of allowing cut-through packet transmission
                                                                 on the internal loopback bus for packets that enter the TDMA.
                                                                 This bit must be set if the TNS is to operate in cut-through mode.
                                                                 If the TNS is operating in a store-and-forward mode this bit should
                                                                 be cleared to prevent unnecessary stalling during packet transmission
                                                                 due to the cut-through packet checks possibly determining the packet
                                                                 to be transmitted is currently being received. */
        uint64_t cutthru_chk           : 1;  /**< [ 43: 43](R/W) Enable cut-thru packet checks.
                                                                 When set, the TDMA performs additional checks to avoid reading
                                                                 too far in to the page pointer link list if the sequence number of
                                                                 the packet to be transmitted matches the sequence number of the
                                                                 packet currently being received on the physical source port on which
                                                                 the packet to be transmitted had arrived.
                                                                 For each port where CUTTHRU_CHK is set and the corresponding
                                                                 *_CUTTHRU_EN field is 0, the data path will operate in a
                                                                 store-and-forward mode, stopping packet transmission if the packet
                                                                 being transmitted appears to be in receipt.
                                                                 When this field is 0, the TDMA packet checks are disabled and the
                                                                 data path will walk the packet link list until the packet's EOP
                                                                 is reached.
                                                                 In order to prevent unnecessary stalling during packet
                                                                 transmission, this field should be 0 when the TNS Parser or TxQ
                                                                 is configured for all ports to operate in a store-and-forward mode.
                                                                 This field has no effect on those TDMA ports where the associated
                                                                 *_CUTTHRU_EN field is set. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    struct bdk_tns_tdma_nb_dbg_config1_cn88xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_43_63        : 21;
        uint64_t lb_cutthru_en         : 1;  /**< [ 42: 42](R/W) Enable cut-thru packet checks and transmission on the internal
                                                                 loopback bus.
                                                                 When set, the TDMA performs packet checks to avoid reading
                                                                 too far in to the page pointer link list if the sequence number of
                                                                 the packet to be transmitted matches the sequence number of the
                                                                 packet currently being received on the physical source port on which
                                                                 the packet to be transmitted had arrived (or is arriving).
                                                                 Setting this bit turns on the cut-through packet checks for the
                                                                 internal loopback path that otherwise would be enabled by CUTTHRU_CHK,
                                                                 with the added benefit of allowing cut-through packet transmission
                                                                 on the internal loopback bus for packets that enter the TDMA.
                                                                 This bit must be set if the TNS is to operate in cut-through mode.
                                                                 If the TNS is operating in a store-and-forward mode this bit should
                                                                 be cleared to prevent unnecessary stalling during packet transmission
                                                                 due to the cut-through packet checks possibly determining the packet
                                                                 to be transmitted is currently being received. */
        uint64_t lmac_cutthru_en       : 1;  /**< [ 41: 41](R/W) Enable cut-thru packet checks and transmission towards the LMAC ports.
                                                                 When set, the TDMA performs packet checks to avoid reading
                                                                 too far in to the page pointer link list if the sequence number of
                                                                 the packet to be transmitted matches the sequence number of the
                                                                 packet currently being received on the physical source port on which
                                                                 the packet to be transmitted had arrived (or is arriving).
                                                                 Setting this bit turns on the cut-through packet checks for
                                                                 LMAC-destined packets that otherwise would be enabled by CUTTHRU_CHK,
                                                                 with the added benefit of allowing cut-through packet transmission
                                                                 towards the LMACs for packets that enter the TDMA.
                                                                 This bit must be set if the TNS is to operate in cut-through mode.
                                                                 If the TNS is operating in a store-and-forward mode this bit should
                                                                 be cleared to prevent unnecessary stalling during packet transmission
                                                                 due to the cut-through packet checks possibly determining the packet
                                                                 to be transmitted is currently being received. */
        uint64_t nic_cutthru_en        : 1;  /**< [ 40: 40](R/W) Enable cut-thru packet checks and transmission towards the NIC.
                                                                 When set, the TDMA performs packet checks to avoid reading
                                                                 too far in to the page pointer link list if the sequence number of
                                                                 the packet to be transmitted matches the sequence number of the
                                                                 packet currently being received on the physical source port on which
                                                                 the packet to be transmitted had arrived (or is arriving).
                                                                 Setting this bit turns on the cut-through packet checks for
                                                                 NIC-destined packets that otherwise would be enabled by CUTTHRU_CHK,
                                                                 with the added benefit of allowing cut-through packet transmission
                                                                 towards the NIC for packets that enter the TDMA.
                                                                 This bit must be set if the TNS is to operate in cut-through mode.
                                                                 If the TNS is operating in a store-and-forward mode this bit should
                                                                 be cleared to prevent unnecessary stalling during packet transmission
                                                                 due to the cut-through packet checks possibly determining the packet
                                                                 to be transmitted is currently being received. */
        uint64_t reserved_37_39        : 3;
        uint64_t lb_init_cdts          : 5;  /**< [ 36: 32](R/W) The flow of data from the TDMA to the RDMA along the internal loopback path is
                                                                 metered by credits.
                                                                 Each credit represents the transfer of a 32-byte flit.
                                                                 A maximum of 16 (decimal) credits is allowed.
                                                                 A minimum of 2 credits is required for proper operation. */
        uint64_t reserved_29_31        : 3;
        uint64_t txq_drop_req_thresh   : 5;  /**< [ 28: 24](R/W) Requests to drop packets are received from the TxQ.
                                                                 Arriving requests can take one of two paths:
                                                                 _ 1) For a single-copy packet the request is pushed to a 16-entry FIFO
                                                                 _    in the Link List walker logic.
                                                                 _ 2) For a multiple-copy packet the request is pushed to a 16-entry FIFO
                                                                 _    in the Page Reference Count logic.
                                                                 If the occupancy of either of these FIFOs reaches the value programmed in this field
                                                                 the data path will assert flow control to the TxQ to prevent additional drop requests
                                                                 from arriving. */
        uint64_t reserved_21_23        : 3;
        uint64_t p2x_tkn_sch_thresh    : 5;  /**< [ 20: 16](R/W) Each of the 8 BGX LMAC ports has a FIFO for receiving transmit request tokens from
                                                                 the port's per-priority Token FIFOs.
                                                                 Each LMAC FIFO can store 8 tokens.
                                                                 This value indicates the number of tokens at which the FIFO will stop pulling tokens
                                                                 from the port's per-priority Token FIFOs. */
        uint64_t reserved_13_15        : 3;
        uint64_t lb_tkn_sch_thresh     : 5;  /**< [ 12:  8](R/W) The internal loopback path has a FIFO for receiving tokens from the TxQ block.
                                                                 The FIFO can store 8 tokens.
                                                                 This value indicates the number of tokens at which the port available signal to
                                                                 the TxQ is to be de-asserted.
                                                                 The value includes tokens in the FIFO as well as the in-flight tokens
                                                                 (schedule received but token not yet received). */
        uint64_t reserved_5_7          : 3;
        uint64_t x2p_tkn_sch_thresh    : 5;  /**< [  4:  0](R/W) Both NIC Interfaces have a FIFO for receiving tokens from the TxQ block.
                                                                 Each FIFO can store 8 tokens.
                                                                 This value indicates the number of tokens at which the port available signal to
                                                                 the TxQ is to be de-asserted.
                                                                 The value includes tokens in the FIFO as well as the in-flight tokens
                                                                 (schedule received but token not yet received). */
#else /* Word 0 - Little Endian */
        uint64_t x2p_tkn_sch_thresh    : 5;  /**< [  4:  0](R/W) Both NIC Interfaces have a FIFO for receiving tokens from the TxQ block.
                                                                 Each FIFO can store 8 tokens.
                                                                 This value indicates the number of tokens at which the port available signal to
                                                                 the TxQ is to be de-asserted.
                                                                 The value includes tokens in the FIFO as well as the in-flight tokens
                                                                 (schedule received but token not yet received). */
        uint64_t reserved_5_7          : 3;
        uint64_t lb_tkn_sch_thresh     : 5;  /**< [ 12:  8](R/W) The internal loopback path has a FIFO for receiving tokens from the TxQ block.
                                                                 The FIFO can store 8 tokens.
                                                                 This value indicates the number of tokens at which the port available signal to
                                                                 the TxQ is to be de-asserted.
                                                                 The value includes tokens in the FIFO as well as the in-flight tokens
                                                                 (schedule received but token not yet received). */
        uint64_t reserved_13_15        : 3;
        uint64_t p2x_tkn_sch_thresh    : 5;  /**< [ 20: 16](R/W) Each of the 8 BGX LMAC ports has a FIFO for receiving transmit request tokens from
                                                                 the port's per-priority Token FIFOs.
                                                                 Each LMAC FIFO can store 8 tokens.
                                                                 This value indicates the number of tokens at which the FIFO will stop pulling tokens
                                                                 from the port's per-priority Token FIFOs. */
        uint64_t reserved_21_23        : 3;
        uint64_t txq_drop_req_thresh   : 5;  /**< [ 28: 24](R/W) Requests to drop packets are received from the TxQ.
                                                                 Arriving requests can take one of two paths:
                                                                 _ 1) For a single-copy packet the request is pushed to a 16-entry FIFO
                                                                 _    in the Link List walker logic.
                                                                 _ 2) For a multiple-copy packet the request is pushed to a 16-entry FIFO
                                                                 _    in the Page Reference Count logic.
                                                                 If the occupancy of either of these FIFOs reaches the value programmed in this field
                                                                 the data path will assert flow control to the TxQ to prevent additional drop requests
                                                                 from arriving. */
        uint64_t reserved_29_31        : 3;
        uint64_t lb_init_cdts          : 5;  /**< [ 36: 32](R/W) The flow of data from the TDMA to the RDMA along the internal loopback path is
                                                                 metered by credits.
                                                                 Each credit represents the transfer of a 32-byte flit.
                                                                 A maximum of 16 (decimal) credits is allowed.
                                                                 A minimum of 2 credits is required for proper operation. */
        uint64_t reserved_37_39        : 3;
        uint64_t nic_cutthru_en        : 1;  /**< [ 40: 40](R/W) Enable cut-thru packet checks and transmission towards the NIC.
                                                                 When set, the TDMA performs packet checks to avoid reading
                                                                 too far in to the page pointer link list if the sequence number of
                                                                 the packet to be transmitted matches the sequence number of the
                                                                 packet currently being received on the physical source port on which
                                                                 the packet to be transmitted had arrived (or is arriving).
                                                                 Setting this bit turns on the cut-through packet checks for
                                                                 NIC-destined packets that otherwise would be enabled by CUTTHRU_CHK,
                                                                 with the added benefit of allowing cut-through packet transmission
                                                                 towards the NIC for packets that enter the TDMA.
                                                                 This bit must be set if the TNS is to operate in cut-through mode.
                                                                 If the TNS is operating in a store-and-forward mode this bit should
                                                                 be cleared to prevent unnecessary stalling during packet transmission
                                                                 due to the cut-through packet checks possibly determining the packet
                                                                 to be transmitted is currently being received. */
        uint64_t lmac_cutthru_en       : 1;  /**< [ 41: 41](R/W) Enable cut-thru packet checks and transmission towards the LMAC ports.
                                                                 When set, the TDMA performs packet checks to avoid reading
                                                                 too far in to the page pointer link list if the sequence number of
                                                                 the packet to be transmitted matches the sequence number of the
                                                                 packet currently being received on the physical source port on which
                                                                 the packet to be transmitted had arrived (or is arriving).
                                                                 Setting this bit turns on the cut-through packet checks for
                                                                 LMAC-destined packets that otherwise would be enabled by CUTTHRU_CHK,
                                                                 with the added benefit of allowing cut-through packet transmission
                                                                 towards the LMACs for packets that enter the TDMA.
                                                                 This bit must be set if the TNS is to operate in cut-through mode.
                                                                 If the TNS is operating in a store-and-forward mode this bit should
                                                                 be cleared to prevent unnecessary stalling during packet transmission
                                                                 due to the cut-through packet checks possibly determining the packet
                                                                 to be transmitted is currently being received. */
        uint64_t lb_cutthru_en         : 1;  /**< [ 42: 42](R/W) Enable cut-thru packet checks and transmission on the internal
                                                                 loopback bus.
                                                                 When set, the TDMA performs packet checks to avoid reading
                                                                 too far in to the page pointer link list if the sequence number of
                                                                 the packet to be transmitted matches the sequence number of the
                                                                 packet currently being received on the physical source port on which
                                                                 the packet to be transmitted had arrived (or is arriving).
                                                                 Setting this bit turns on the cut-through packet checks for the
                                                                 internal loopback path that otherwise would be enabled by CUTTHRU_CHK,
                                                                 with the added benefit of allowing cut-through packet transmission
                                                                 on the internal loopback bus for packets that enter the TDMA.
                                                                 This bit must be set if the TNS is to operate in cut-through mode.
                                                                 If the TNS is operating in a store-and-forward mode this bit should
                                                                 be cleared to prevent unnecessary stalling during packet transmission
                                                                 due to the cut-through packet checks possibly determining the packet
                                                                 to be transmitted is currently being received. */
        uint64_t reserved_43_63        : 21;
#endif /* Word 0 - End */
    } cn88xxp1;
    /* struct bdk_tns_tdma_nb_dbg_config1_s cn88xxp2; */
};
typedef union bdk_tns_tdma_nb_dbg_config1 bdk_tns_tdma_nb_dbg_config1_t;

#define BDK_TNS_TDMA_NB_DBG_CONFIG1 BDK_TNS_TDMA_NB_DBG_CONFIG1_FUNC()
static inline uint64_t BDK_TNS_TDMA_NB_DBG_CONFIG1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_DBG_CONFIG1_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842041000c00ll;
    __bdk_csr_fatal("TNS_TDMA_NB_DBG_CONFIG1", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_DBG_CONFIG1 bdk_tns_tdma_nb_dbg_config1_t
#define bustype_BDK_TNS_TDMA_NB_DBG_CONFIG1 BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_DBG_CONFIG1 "TNS_TDMA_NB_DBG_CONFIG1"
#define device_bar_BDK_TNS_TDMA_NB_DBG_CONFIG1 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_DBG_CONFIG1 0
#define arguments_BDK_TNS_TDMA_NB_DBG_CONFIG1 -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_dbg_config2
 *
 * INTERNAL: TNS TDMA Debug Config2 Register
 *
 * This register provides debug control of TDMA functionality.
 */
union bdk_tns_tdma_nb_dbg_config2
{
    uint64_t u;
    struct bdk_tns_tdma_nb_dbg_config2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t sst_retry_count       : 20; /**< [ 19:  0](R/W) Read and write requests to the SDE, SE, and TxQ sub-blocks may sometimes timeout due
                                                                 to hardware having priority over software access.
                                                                 The design will attempt to retry a timed out request the number of times specified in
                                                                 this field before eventually timing out and setting
                                                                 TNS_TDMA_NB_INT_STAT_W1C[SST_REQ_TIMEOUT]. */
#else /* Word 0 - Little Endian */
        uint64_t sst_retry_count       : 20; /**< [ 19:  0](R/W) Read and write requests to the SDE, SE, and TxQ sub-blocks may sometimes timeout due
                                                                 to hardware having priority over software access.
                                                                 The design will attempt to retry a timed out request the number of times specified in
                                                                 this field before eventually timing out and setting
                                                                 TNS_TDMA_NB_INT_STAT_W1C[SST_REQ_TIMEOUT]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_dbg_config2_s cn; */
};
typedef union bdk_tns_tdma_nb_dbg_config2 bdk_tns_tdma_nb_dbg_config2_t;

#define BDK_TNS_TDMA_NB_DBG_CONFIG2 BDK_TNS_TDMA_NB_DBG_CONFIG2_FUNC()
static inline uint64_t BDK_TNS_TDMA_NB_DBG_CONFIG2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_DBG_CONFIG2_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842041000c10ll;
    __bdk_csr_fatal("TNS_TDMA_NB_DBG_CONFIG2", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_DBG_CONFIG2 bdk_tns_tdma_nb_dbg_config2_t
#define bustype_BDK_TNS_TDMA_NB_DBG_CONFIG2 BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_DBG_CONFIG2 "TNS_TDMA_NB_DBG_CONFIG2"
#define device_bar_BDK_TNS_TDMA_NB_DBG_CONFIG2 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_DBG_CONFIG2 0
#define arguments_BDK_TNS_TDMA_NB_DBG_CONFIG2 -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_dbg_cx_full
 *
 * INTERNAL: TNS TDMA Debug CX Full Level Control Register
 *
 * This register provides debug control of FIFO full.
 * Async FIFOs assert an early full indication when occupancies reach the values
 * below.
 */
union bdk_tns_tdma_nb_dbg_cx_full
{
    uint64_t u;
    struct bdk_tns_tdma_nb_dbg_cx_full_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t lmac_pkt              : 5;  /**< [ 12:  8](R/W) Packet data to LMACs. */
        uint64_t reserved_5_7          : 3;
        uint64_t nic_pkt               : 5;  /**< [  4:  0](R/W) Packet data to NIC. */
#else /* Word 0 - Little Endian */
        uint64_t nic_pkt               : 5;  /**< [  4:  0](R/W) Packet data to NIC. */
        uint64_t reserved_5_7          : 3;
        uint64_t lmac_pkt              : 5;  /**< [ 12:  8](R/W) Packet data to LMACs. */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_dbg_cx_full_s cn; */
};
typedef union bdk_tns_tdma_nb_dbg_cx_full bdk_tns_tdma_nb_dbg_cx_full_t;

#define BDK_TNS_TDMA_NB_DBG_CX_FULL BDK_TNS_TDMA_NB_DBG_CX_FULL_FUNC()
static inline uint64_t BDK_TNS_TDMA_NB_DBG_CX_FULL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_DBG_CX_FULL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842041000c40ll;
    __bdk_csr_fatal("TNS_TDMA_NB_DBG_CX_FULL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_DBG_CX_FULL bdk_tns_tdma_nb_dbg_cx_full_t
#define bustype_BDK_TNS_TDMA_NB_DBG_CX_FULL BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_DBG_CX_FULL "TNS_TDMA_NB_DBG_CX_FULL"
#define device_bar_BDK_TNS_TDMA_NB_DBG_CX_FULL 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_DBG_CX_FULL 0
#define arguments_BDK_TNS_TDMA_NB_DBG_CX_FULL -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_dbg_cx_occ
 *
 * INTERNAL: TNS TDMA Debug CX FIFO Occupancy Status Register
 *
 * Async FIFO occupancies.
 */
union bdk_tns_tdma_nb_dbg_cx_occ
{
    uint64_t u;
    struct bdk_tns_tdma_nb_dbg_cx_occ_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t lmac_pkt              : 5;  /**< [ 12:  8](RO/H) Data sending to LMACs. */
        uint64_t reserved_5_7          : 3;
        uint64_t nic_pkt               : 5;  /**< [  4:  0](RO/H) Data sending to NIC. */
#else /* Word 0 - Little Endian */
        uint64_t nic_pkt               : 5;  /**< [  4:  0](RO/H) Data sending to NIC. */
        uint64_t reserved_5_7          : 3;
        uint64_t lmac_pkt              : 5;  /**< [ 12:  8](RO/H) Data sending to LMACs. */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_dbg_cx_occ_s cn; */
};
typedef union bdk_tns_tdma_nb_dbg_cx_occ bdk_tns_tdma_nb_dbg_cx_occ_t;

#define BDK_TNS_TDMA_NB_DBG_CX_OCC BDK_TNS_TDMA_NB_DBG_CX_OCC_FUNC()
static inline uint64_t BDK_TNS_TDMA_NB_DBG_CX_OCC_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_DBG_CX_OCC_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842041000c50ll;
    __bdk_csr_fatal("TNS_TDMA_NB_DBG_CX_OCC", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_DBG_CX_OCC bdk_tns_tdma_nb_dbg_cx_occ_t
#define bustype_BDK_TNS_TDMA_NB_DBG_CX_OCC BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_DBG_CX_OCC "TNS_TDMA_NB_DBG_CX_OCC"
#define device_bar_BDK_TNS_TDMA_NB_DBG_CX_OCC 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_DBG_CX_OCC 0
#define arguments_BDK_TNS_TDMA_NB_DBG_CX_OCC -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_dbg_lmac#_config1
 *
 * INTERNAL: TNS TDMA Debug LMAC Config1 Register
 */
union bdk_tns_tdma_nb_dbg_lmacx_config1
{
    uint64_t u;
    struct bdk_tns_tdma_nb_dbg_lmacx_config1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t tkn_sch_thresh        : 5;  /**< [  4:  0](R/W) Each LMAC path has 16 FIFOs for receiving tokens from the TxQ block
                                                                 on a per-priority basis.
                                                                 Each LMAC priority FIFO can store 8 tokens.
                                                                 This value indicates the number of tokens at which point EBP XOFF for the priority
                                                                 will be asserted to the TxQ.
                                                                 The value includes tokens in the FIFO as well as the in-flight tokens
                                                                 (schedule received but token not yet received).
                                                                 A value larger than 8 will be interpreted as 8.
                                                                 A value of 0 will assert XOFF for all priorities of the LMAC. */
#else /* Word 0 - Little Endian */
        uint64_t tkn_sch_thresh        : 5;  /**< [  4:  0](R/W) Each LMAC path has 16 FIFOs for receiving tokens from the TxQ block
                                                                 on a per-priority basis.
                                                                 Each LMAC priority FIFO can store 8 tokens.
                                                                 This value indicates the number of tokens at which point EBP XOFF for the priority
                                                                 will be asserted to the TxQ.
                                                                 The value includes tokens in the FIFO as well as the in-flight tokens
                                                                 (schedule received but token not yet received).
                                                                 A value larger than 8 will be interpreted as 8.
                                                                 A value of 0 will assert XOFF for all priorities of the LMAC. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_dbg_lmacx_config1_s cn; */
};
typedef union bdk_tns_tdma_nb_dbg_lmacx_config1 bdk_tns_tdma_nb_dbg_lmacx_config1_t;

static inline uint64_t BDK_TNS_TDMA_NB_DBG_LMACX_CONFIG1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_DBG_LMACX_CONFIG1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=7))
        return 0x842041000c80ll + 0x10ll * ((a) & 0x7);
    __bdk_csr_fatal("TNS_TDMA_NB_DBG_LMACX_CONFIG1", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_DBG_LMACX_CONFIG1(a) bdk_tns_tdma_nb_dbg_lmacx_config1_t
#define bustype_BDK_TNS_TDMA_NB_DBG_LMACX_CONFIG1(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_DBG_LMACX_CONFIG1(a) "TNS_TDMA_NB_DBG_LMACX_CONFIG1"
#define device_bar_BDK_TNS_TDMA_NB_DBG_LMACX_CONFIG1(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_DBG_LMACX_CONFIG1(a) (a)
#define arguments_BDK_TNS_TDMA_NB_DBG_LMACX_CONFIG1(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_ecc_ctl
 *
 * TNS TDMA ECC Control Register
 * This register can be used to disable ECC data correction, insert ECC errors.
 * Fields *ECC_DIS disable SBE data correction. If ECC_DIS is 0x1, then no data correction is
 * performed but errors will still be reported.
 * Fields *ECC_FLIP_SYND flip the syndrome\<1:0\> bits to generate 1-bit/2-bit error for testing.
 * * 0x0 = normal operation.
 * * 0x1 = SBE on bit\<0\>.
 * * 0x2 = SBE on bit\<1\>.
 * * 0x3 = DBE on bits\<1:0\>.
 */
union bdk_tns_tdma_nb_ecc_ctl
{
    uint64_t u;
    struct bdk_tns_tdma_nb_ecc_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t pm_ecc_dis            : 1;  /**< [ 39: 39](R/W) Disable ECC data correction for PM RAM. */
        uint64_t prc_ecc_dis           : 1;  /**< [ 38: 38](R/W) Disable ECC data correction for PRC RAM. */
        uint64_t ll_ecc_dis            : 1;  /**< [ 37: 37](R/W) Disable ECC data correction for LL RAM. */
        uint64_t fpm_ecc_dis           : 1;  /**< [ 36: 36](R/W) Disable ECC data correction for FPM RAM. */
        uint64_t pkt_lb_ecc_dis        : 1;  /**< [ 35: 35](R/W) Disable ECC data correction for PKT_LB RAM. */
        uint64_t pkt_x2p_ecc_dis       : 1;  /**< [ 34: 34](R/W) Disable ECC data correction for PKT_X2P RAM. */
        uint64_t pkt_p2x_data_ecc_dis  : 1;  /**< [ 33: 33](R/W) Disable ECC data correction for PKT_P2X_DATA RAM. */
        uint64_t pkt_p2x_tkn_ecc_dis   : 1;  /**< [ 32: 32](R/W) Disable ECC data correction for PKT_P2X_TKN RAM. */
        uint64_t reserved_14_31        : 18;
        uint64_t prc_ecc_flip_synd     : 2;  /**< [ 13: 12](R/W) Flip syndrome for all data written to PRC RAM. */
        uint64_t ll_ecc_flip_synd      : 2;  /**< [ 11: 10](R/W) Flip syndrome for all data written to LL RAM. */
        uint64_t fpm_ecc_flip_synd     : 2;  /**< [  9:  8](R/W) Flip syndrome for all data written to FPM RAM. */
        uint64_t pkt_lb_ecc_flip_synd  : 2;  /**< [  7:  6](R/W) Flip syndrome for all data written to PKT_LB RAM. */
        uint64_t pkt_x2p_ecc_flip_synd : 2;  /**< [  5:  4](R/W) Flip syndrome for all data written to PKT_X2P RAM. */
        uint64_t pkt_p2x_data_ecc_flip_synd : 2;/**< [  3:  2](R/W) Flip syndrome for all data written to PKT_P2X_DATA RAM. */
        uint64_t pkt_p2x_tkn_ecc_flip_synd : 2;/**< [  1:  0](R/W) Flip syndrome for all data written to PKT_P2X_TKN RAM. */
#else /* Word 0 - Little Endian */
        uint64_t pkt_p2x_tkn_ecc_flip_synd : 2;/**< [  1:  0](R/W) Flip syndrome for all data written to PKT_P2X_TKN RAM. */
        uint64_t pkt_p2x_data_ecc_flip_synd : 2;/**< [  3:  2](R/W) Flip syndrome for all data written to PKT_P2X_DATA RAM. */
        uint64_t pkt_x2p_ecc_flip_synd : 2;  /**< [  5:  4](R/W) Flip syndrome for all data written to PKT_X2P RAM. */
        uint64_t pkt_lb_ecc_flip_synd  : 2;  /**< [  7:  6](R/W) Flip syndrome for all data written to PKT_LB RAM. */
        uint64_t fpm_ecc_flip_synd     : 2;  /**< [  9:  8](R/W) Flip syndrome for all data written to FPM RAM. */
        uint64_t ll_ecc_flip_synd      : 2;  /**< [ 11: 10](R/W) Flip syndrome for all data written to LL RAM. */
        uint64_t prc_ecc_flip_synd     : 2;  /**< [ 13: 12](R/W) Flip syndrome for all data written to PRC RAM. */
        uint64_t reserved_14_31        : 18;
        uint64_t pkt_p2x_tkn_ecc_dis   : 1;  /**< [ 32: 32](R/W) Disable ECC data correction for PKT_P2X_TKN RAM. */
        uint64_t pkt_p2x_data_ecc_dis  : 1;  /**< [ 33: 33](R/W) Disable ECC data correction for PKT_P2X_DATA RAM. */
        uint64_t pkt_x2p_ecc_dis       : 1;  /**< [ 34: 34](R/W) Disable ECC data correction for PKT_X2P RAM. */
        uint64_t pkt_lb_ecc_dis        : 1;  /**< [ 35: 35](R/W) Disable ECC data correction for PKT_LB RAM. */
        uint64_t fpm_ecc_dis           : 1;  /**< [ 36: 36](R/W) Disable ECC data correction for FPM RAM. */
        uint64_t ll_ecc_dis            : 1;  /**< [ 37: 37](R/W) Disable ECC data correction for LL RAM. */
        uint64_t prc_ecc_dis           : 1;  /**< [ 38: 38](R/W) Disable ECC data correction for PRC RAM. */
        uint64_t pm_ecc_dis            : 1;  /**< [ 39: 39](R/W) Disable ECC data correction for PM RAM. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_ecc_ctl_s cn; */
};
typedef union bdk_tns_tdma_nb_ecc_ctl bdk_tns_tdma_nb_ecc_ctl_t;

#define BDK_TNS_TDMA_NB_ECC_CTL BDK_TNS_TDMA_NB_ECC_CTL_FUNC()
static inline uint64_t BDK_TNS_TDMA_NB_ECC_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_ECC_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842041000800ll;
    __bdk_csr_fatal("TNS_TDMA_NB_ECC_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_ECC_CTL bdk_tns_tdma_nb_ecc_ctl_t
#define bustype_BDK_TNS_TDMA_NB_ECC_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_ECC_CTL "TNS_TDMA_NB_ECC_CTL"
#define device_bar_BDK_TNS_TDMA_NB_ECC_CTL 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_ECC_CTL 0
#define arguments_BDK_TNS_TDMA_NB_ECC_CTL -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_ecc_err_stat
 *
 * TNS TDMA ECC Error Status Register
 * This register logs information to help debug ECC errors.
 */
union bdk_tns_tdma_nb_ecc_err_stat
{
    uint64_t u;
    struct bdk_tns_tdma_nb_ecc_err_stat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_27_63        : 37;
        uint64_t syndrome              : 11; /**< [ 26: 16](RO/H) Error syndrome. */
        uint64_t address               : 16; /**< [ 15:  0](RO/H) Address of ECC error. */
#else /* Word 0 - Little Endian */
        uint64_t address               : 16; /**< [ 15:  0](RO/H) Address of ECC error. */
        uint64_t syndrome              : 11; /**< [ 26: 16](RO/H) Error syndrome. */
        uint64_t reserved_27_63        : 37;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_ecc_err_stat_s cn; */
};
typedef union bdk_tns_tdma_nb_ecc_err_stat bdk_tns_tdma_nb_ecc_err_stat_t;

#define BDK_TNS_TDMA_NB_ECC_ERR_STAT BDK_TNS_TDMA_NB_ECC_ERR_STAT_FUNC()
static inline uint64_t BDK_TNS_TDMA_NB_ECC_ERR_STAT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_ECC_ERR_STAT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842041000810ll;
    __bdk_csr_fatal("TNS_TDMA_NB_ECC_ERR_STAT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_ECC_ERR_STAT bdk_tns_tdma_nb_ecc_err_stat_t
#define bustype_BDK_TNS_TDMA_NB_ECC_ERR_STAT BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_ECC_ERR_STAT "TNS_TDMA_NB_ECC_ERR_STAT"
#define device_bar_BDK_TNS_TDMA_NB_ECC_ERR_STAT 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_ECC_ERR_STAT 0
#define arguments_BDK_TNS_TDMA_NB_ECC_ERR_STAT -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_eco
 *
 * INTERNAL: TNS TDMA ECO Register
 *
 * ECO register.
 */
union bdk_tns_tdma_nb_eco
{
    uint64_t u;
    struct bdk_tns_tdma_nb_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t rst1                  : 8;  /**< [ 15:  8](R/W) Reset to 1 spare bits */
        uint64_t rst0                  : 8;  /**< [  7:  0](R/W) Reset to 0 spare bits */
#else /* Word 0 - Little Endian */
        uint64_t rst0                  : 8;  /**< [  7:  0](R/W) Reset to 0 spare bits */
        uint64_t rst1                  : 8;  /**< [ 15:  8](R/W) Reset to 1 spare bits */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_eco_s cn; */
};
typedef union bdk_tns_tdma_nb_eco bdk_tns_tdma_nb_eco_t;

#define BDK_TNS_TDMA_NB_ECO BDK_TNS_TDMA_NB_ECO_FUNC()
static inline uint64_t BDK_TNS_TDMA_NB_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_ECO_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842041002000ll;
    __bdk_csr_fatal("TNS_TDMA_NB_ECO", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_ECO bdk_tns_tdma_nb_eco_t
#define bustype_BDK_TNS_TDMA_NB_ECO BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_ECO "TNS_TDMA_NB_ECO"
#define device_bar_BDK_TNS_TDMA_NB_ECO 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_ECO 0
#define arguments_BDK_TNS_TDMA_NB_ECO -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_fpm_acc#
 *
 * INTERNAL: TNS TDMA Free Page Manager Access Registers
 *
 * Provides the ability for software to access the TDMA Free Page Manager FIFO memory.
 * The FPM consists of 1536 120-bit words.
 * Each 120-bit word stores 8 14-bit page pointers.
 *
 * To write data to a piece of a memory word software must write the entire word, 8 bytes at a
 * time,
 * starting with the least significant bits at 0x...00 and incrementing sequentially up
 * to 0x...10.
 */
union bdk_tns_tdma_nb_fpm_accx
{
    uint64_t u;
    struct bdk_tns_tdma_nb_fpm_accx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Data. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Data. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_fpm_accx_s cn; */
};
typedef union bdk_tns_tdma_nb_fpm_accx bdk_tns_tdma_nb_fpm_accx_t;

static inline uint64_t BDK_TNS_TDMA_NB_FPM_ACCX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_FPM_ACCX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3071))
        return 0x842041010000ll + 0x10ll * ((a) & 0xfff);
    __bdk_csr_fatal("TNS_TDMA_NB_FPM_ACCX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_FPM_ACCX(a) bdk_tns_tdma_nb_fpm_accx_t
#define bustype_BDK_TNS_TDMA_NB_FPM_ACCX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_FPM_ACCX(a) "TNS_TDMA_NB_FPM_ACCX"
#define device_bar_BDK_TNS_TDMA_NB_FPM_ACCX(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_FPM_ACCX(a) (a)
#define arguments_BDK_TNS_TDMA_NB_FPM_ACCX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_fpm_mod
 *
 * INTERNAL: TNS TDMA Free Page Manager Modify Register
 *
 * Allows software to pop or push a bundle of 8 page pointers from/to the TDMA Free Page
 * Manager FIFO memory.
 * Software may only set the POP or PUSH fields during initialization, before setting
 * TNS_TDMA_NB_CONFIG[MASTER_EN].
 * If performing a PUSH, software must guarantee that all pages in the bundle at the FPM
 * address indicated by the write pointer do not already exist in the FPM.
 */
union bdk_tns_tdma_nb_fpm_mod
{
    uint64_t u;
    struct bdk_tns_tdma_nb_fpm_mod_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pop                   : 1;  /**< [ 63: 63](WO/H) Pop a bundle of 8 page pointers from the FPM FIFO and discard the pointers.
                                                                 Increments TNS_TDMA_NB_FPM_STATUS[RPTR].
                                                                 Hardware guards against popping from an empty FIFO.
                                                                 Hardware will clear this field to 0x0 upon a successful bundle pop. */
        uint64_t push                  : 1;  /**< [ 62: 62](WO/H) Push a bundle of 8 page pointers to the FPM FIFO by including the data located at
                                                                 TNS_TDMA_NB_FPM_STATUS[WPTR].
                                                                 Increments TNS_TDMA_NB_FPM_STATUS[WPTR].
                                                                 Hardware guards against pushing to a full FIFO.
                                                                 Hardware will clear this field to 0x0 upon a successful bundle push. */
        uint64_t reserved_0_61         : 62;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_61         : 62;
        uint64_t push                  : 1;  /**< [ 62: 62](WO/H) Push a bundle of 8 page pointers to the FPM FIFO by including the data located at
                                                                 TNS_TDMA_NB_FPM_STATUS[WPTR].
                                                                 Increments TNS_TDMA_NB_FPM_STATUS[WPTR].
                                                                 Hardware guards against pushing to a full FIFO.
                                                                 Hardware will clear this field to 0x0 upon a successful bundle push. */
        uint64_t pop                   : 1;  /**< [ 63: 63](WO/H) Pop a bundle of 8 page pointers from the FPM FIFO and discard the pointers.
                                                                 Increments TNS_TDMA_NB_FPM_STATUS[RPTR].
                                                                 Hardware guards against popping from an empty FIFO.
                                                                 Hardware will clear this field to 0x0 upon a successful bundle pop. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_fpm_mod_s cn; */
};
typedef union bdk_tns_tdma_nb_fpm_mod bdk_tns_tdma_nb_fpm_mod_t;

#define BDK_TNS_TDMA_NB_FPM_MOD BDK_TNS_TDMA_NB_FPM_MOD_FUNC()
static inline uint64_t BDK_TNS_TDMA_NB_FPM_MOD_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_FPM_MOD_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842041001010ll;
    __bdk_csr_fatal("TNS_TDMA_NB_FPM_MOD", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_FPM_MOD bdk_tns_tdma_nb_fpm_mod_t
#define bustype_BDK_TNS_TDMA_NB_FPM_MOD BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_FPM_MOD "TNS_TDMA_NB_FPM_MOD"
#define device_bar_BDK_TNS_TDMA_NB_FPM_MOD 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_FPM_MOD 0
#define arguments_BDK_TNS_TDMA_NB_FPM_MOD -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_fpm_status
 *
 * INTERNAL: TNS TDMA Free Page Manager Status Register
 */
union bdk_tns_tdma_nb_fpm_status
{
    uint64_t u;
    struct bdk_tns_tdma_nb_fpm_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_35_63        : 29;
        uint64_t rptr                  : 11; /**< [ 34: 24](RO/H) FPM FIFO read pointer. */
        uint64_t reserved_23           : 1;
        uint64_t wptr                  : 11; /**< [ 22: 12](RO/H) FPM FIFO write pointer. */
        uint64_t reserved_11           : 1;
        uint64_t occ                   : 11; /**< [ 10:  0](RO/H) FPM FIFO bundle occupancy.
                                                                 Indicates the number of 8-page pointer bundles in the FPM FIFO. */
#else /* Word 0 - Little Endian */
        uint64_t occ                   : 11; /**< [ 10:  0](RO/H) FPM FIFO bundle occupancy.
                                                                 Indicates the number of 8-page pointer bundles in the FPM FIFO. */
        uint64_t reserved_11           : 1;
        uint64_t wptr                  : 11; /**< [ 22: 12](RO/H) FPM FIFO write pointer. */
        uint64_t reserved_23           : 1;
        uint64_t rptr                  : 11; /**< [ 34: 24](RO/H) FPM FIFO read pointer. */
        uint64_t reserved_35_63        : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_fpm_status_s cn; */
};
typedef union bdk_tns_tdma_nb_fpm_status bdk_tns_tdma_nb_fpm_status_t;

#define BDK_TNS_TDMA_NB_FPM_STATUS BDK_TNS_TDMA_NB_FPM_STATUS_FUNC()
static inline uint64_t BDK_TNS_TDMA_NB_FPM_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_FPM_STATUS_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842041001000ll;
    __bdk_csr_fatal("TNS_TDMA_NB_FPM_STATUS", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_FPM_STATUS bdk_tns_tdma_nb_fpm_status_t
#define bustype_BDK_TNS_TDMA_NB_FPM_STATUS BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_FPM_STATUS "TNS_TDMA_NB_FPM_STATUS"
#define device_bar_BDK_TNS_TDMA_NB_FPM_STATUS 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_FPM_STATUS 0
#define arguments_BDK_TNS_TDMA_NB_FPM_STATUS -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_int_en_w1c
 *
 * TNS TDMA Interrupt Enable (Read/Write-1-Clear) Register
 * TDMA Interrupt Enable Register.
 */
union bdk_tns_tdma_nb_int_en_w1c
{
    uint64_t u;
    struct bdk_tns_tdma_nb_int_en_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t sst_seq_err           : 1;  /**< [ 21: 21](R/W1C/H) A CSR request to the SST blocks experienced a fatal protocol sequence error. */
        uint64_t sst_req_timeout       : 1;  /**< [ 20: 20](R/W1C/H) A CSR request to the SST blocks timed out. */
        uint64_t sst_addr_err          : 1;  /**< [ 19: 19](R/W1C/H) A CSR request to the SST blocks was directed to an invalid address. */
        uint64_t prc_urw_zero          : 1;  /**< [ 18: 18](R/W1C/H) A PRC counter was inappropriately decremented to zero by the URW. */
        uint64_t prc_rollunder         : 1;  /**< [ 17: 17](R/W1C/H) A PRC counter rolled under. */
        uint64_t prc_rollover          : 1;  /**< [ 16: 16](R/W1C/H) A PRC counter rolled over. */
        uint64_t pm_dbe                : 1;  /**< [ 15: 15](R/W1C/H) Double-bit ECC error detected on PM RAM. */
        uint64_t prc_dbe               : 1;  /**< [ 14: 14](R/W1C/H) Double-bit ECC error detected on PRC RAM. */
        uint64_t ll_dbe                : 1;  /**< [ 13: 13](R/W1C/H) Double-bit ECC error detected on LL RAM. */
        uint64_t fpm_dbe               : 1;  /**< [ 12: 12](R/W1C/H) Double-bit ECC error detected on FPM RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 11: 11](R/W1C/H) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_x2p_dbe           : 1;  /**< [ 10: 10](R/W1C/H) Double-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_p2x_data_dbe      : 1;  /**< [  9:  9](R/W1C/H) Double-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_p2x_tkn_dbe       : 1;  /**< [  8:  8](R/W1C/H) Double-bit ECC error detected on PKT_P2X_TKN RAM. */
        uint64_t pm_sbe                : 1;  /**< [  7:  7](R/W1C/H) Single-bit ECC error detected on PM RAM. */
        uint64_t prc_sbe               : 1;  /**< [  6:  6](R/W1C/H) Single-bit ECC error detected on PRC RAM. */
        uint64_t ll_sbe                : 1;  /**< [  5:  5](R/W1C/H) Single-bit ECC error detected on LL RAM. */
        uint64_t fpm_sbe               : 1;  /**< [  4:  4](R/W1C/H) Single-bit ECC error detected on FPM RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [  3:  3](R/W1C/H) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_x2p_sbe           : 1;  /**< [  2:  2](R/W1C/H) Single-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_p2x_data_sbe      : 1;  /**< [  1:  1](R/W1C/H) Single-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_p2x_tkn_sbe       : 1;  /**< [  0:  0](R/W1C/H) Single-bit ECC error detected on PKT_P2X_TKN RAM. */
#else /* Word 0 - Little Endian */
        uint64_t pkt_p2x_tkn_sbe       : 1;  /**< [  0:  0](R/W1C/H) Single-bit ECC error detected on PKT_P2X_TKN RAM. */
        uint64_t pkt_p2x_data_sbe      : 1;  /**< [  1:  1](R/W1C/H) Single-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_x2p_sbe           : 1;  /**< [  2:  2](R/W1C/H) Single-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [  3:  3](R/W1C/H) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t fpm_sbe               : 1;  /**< [  4:  4](R/W1C/H) Single-bit ECC error detected on FPM RAM. */
        uint64_t ll_sbe                : 1;  /**< [  5:  5](R/W1C/H) Single-bit ECC error detected on LL RAM. */
        uint64_t prc_sbe               : 1;  /**< [  6:  6](R/W1C/H) Single-bit ECC error detected on PRC RAM. */
        uint64_t pm_sbe                : 1;  /**< [  7:  7](R/W1C/H) Single-bit ECC error detected on PM RAM. */
        uint64_t pkt_p2x_tkn_dbe       : 1;  /**< [  8:  8](R/W1C/H) Double-bit ECC error detected on PKT_P2X_TKN RAM. */
        uint64_t pkt_p2x_data_dbe      : 1;  /**< [  9:  9](R/W1C/H) Double-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_x2p_dbe           : 1;  /**< [ 10: 10](R/W1C/H) Double-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 11: 11](R/W1C/H) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t fpm_dbe               : 1;  /**< [ 12: 12](R/W1C/H) Double-bit ECC error detected on FPM RAM. */
        uint64_t ll_dbe                : 1;  /**< [ 13: 13](R/W1C/H) Double-bit ECC error detected on LL RAM. */
        uint64_t prc_dbe               : 1;  /**< [ 14: 14](R/W1C/H) Double-bit ECC error detected on PRC RAM. */
        uint64_t pm_dbe                : 1;  /**< [ 15: 15](R/W1C/H) Double-bit ECC error detected on PM RAM. */
        uint64_t prc_rollover          : 1;  /**< [ 16: 16](R/W1C/H) A PRC counter rolled over. */
        uint64_t prc_rollunder         : 1;  /**< [ 17: 17](R/W1C/H) A PRC counter rolled under. */
        uint64_t prc_urw_zero          : 1;  /**< [ 18: 18](R/W1C/H) A PRC counter was inappropriately decremented to zero by the URW. */
        uint64_t sst_addr_err          : 1;  /**< [ 19: 19](R/W1C/H) A CSR request to the SST blocks was directed to an invalid address. */
        uint64_t sst_req_timeout       : 1;  /**< [ 20: 20](R/W1C/H) A CSR request to the SST blocks timed out. */
        uint64_t sst_seq_err           : 1;  /**< [ 21: 21](R/W1C/H) A CSR request to the SST blocks experienced a fatal protocol sequence error. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_int_en_w1c_s cn; */
};
typedef union bdk_tns_tdma_nb_int_en_w1c bdk_tns_tdma_nb_int_en_w1c_t;

#define BDK_TNS_TDMA_NB_INT_EN_W1C BDK_TNS_TDMA_NB_INT_EN_W1C_FUNC()
static inline uint64_t BDK_TNS_TDMA_NB_INT_EN_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_INT_EN_W1C_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842041000130ll;
    __bdk_csr_fatal("TNS_TDMA_NB_INT_EN_W1C", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_INT_EN_W1C bdk_tns_tdma_nb_int_en_w1c_t
#define bustype_BDK_TNS_TDMA_NB_INT_EN_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_INT_EN_W1C "TNS_TDMA_NB_INT_EN_W1C"
#define device_bar_BDK_TNS_TDMA_NB_INT_EN_W1C 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_INT_EN_W1C 0
#define arguments_BDK_TNS_TDMA_NB_INT_EN_W1C -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_int_en_w1s
 *
 * TNS TDMA Interrupt Enable (Read/Write-1-Set) Register
 * TDMA Interrupt Enable Register.
 */
union bdk_tns_tdma_nb_int_en_w1s
{
    uint64_t u;
    struct bdk_tns_tdma_nb_int_en_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t sst_seq_err           : 1;  /**< [ 21: 21](R/W1S/H) A CSR request to the SST blocks experienced a fatal protocol sequence error. */
        uint64_t sst_req_timeout       : 1;  /**< [ 20: 20](R/W1S/H) A CSR request to the SST blocks timed out. */
        uint64_t sst_addr_err          : 1;  /**< [ 19: 19](R/W1S/H) A CSR request to the SST blocks was directed to an invalid address. */
        uint64_t prc_urw_zero          : 1;  /**< [ 18: 18](R/W1S/H) A PRC counter was inappropriately decremented to zero by the URW. */
        uint64_t prc_rollunder         : 1;  /**< [ 17: 17](R/W1S/H) A PRC counter rolled under. */
        uint64_t prc_rollover          : 1;  /**< [ 16: 16](R/W1S/H) A PRC counter rolled over. */
        uint64_t pm_dbe                : 1;  /**< [ 15: 15](R/W1S/H) Double-bit ECC error detected on PM RAM. */
        uint64_t prc_dbe               : 1;  /**< [ 14: 14](R/W1S/H) Double-bit ECC error detected on PRC RAM. */
        uint64_t ll_dbe                : 1;  /**< [ 13: 13](R/W1S/H) Double-bit ECC error detected on LL RAM. */
        uint64_t fpm_dbe               : 1;  /**< [ 12: 12](R/W1S/H) Double-bit ECC error detected on FPM RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 11: 11](R/W1S/H) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_x2p_dbe           : 1;  /**< [ 10: 10](R/W1S/H) Double-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_p2x_data_dbe      : 1;  /**< [  9:  9](R/W1S/H) Double-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_p2x_tkn_dbe       : 1;  /**< [  8:  8](R/W1S/H) Double-bit ECC error detected on PKT_P2X_TKN RAM. */
        uint64_t pm_sbe                : 1;  /**< [  7:  7](R/W1S/H) Single-bit ECC error detected on PM RAM. */
        uint64_t prc_sbe               : 1;  /**< [  6:  6](R/W1S/H) Single-bit ECC error detected on PRC RAM. */
        uint64_t ll_sbe                : 1;  /**< [  5:  5](R/W1S/H) Single-bit ECC error detected on LL RAM. */
        uint64_t fpm_sbe               : 1;  /**< [  4:  4](R/W1S/H) Single-bit ECC error detected on FPM RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [  3:  3](R/W1S/H) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_x2p_sbe           : 1;  /**< [  2:  2](R/W1S/H) Single-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_p2x_data_sbe      : 1;  /**< [  1:  1](R/W1S/H) Single-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_p2x_tkn_sbe       : 1;  /**< [  0:  0](R/W1S/H) Single-bit ECC error detected on PKT_P2X_TKN RAM. */
#else /* Word 0 - Little Endian */
        uint64_t pkt_p2x_tkn_sbe       : 1;  /**< [  0:  0](R/W1S/H) Single-bit ECC error detected on PKT_P2X_TKN RAM. */
        uint64_t pkt_p2x_data_sbe      : 1;  /**< [  1:  1](R/W1S/H) Single-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_x2p_sbe           : 1;  /**< [  2:  2](R/W1S/H) Single-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [  3:  3](R/W1S/H) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t fpm_sbe               : 1;  /**< [  4:  4](R/W1S/H) Single-bit ECC error detected on FPM RAM. */
        uint64_t ll_sbe                : 1;  /**< [  5:  5](R/W1S/H) Single-bit ECC error detected on LL RAM. */
        uint64_t prc_sbe               : 1;  /**< [  6:  6](R/W1S/H) Single-bit ECC error detected on PRC RAM. */
        uint64_t pm_sbe                : 1;  /**< [  7:  7](R/W1S/H) Single-bit ECC error detected on PM RAM. */
        uint64_t pkt_p2x_tkn_dbe       : 1;  /**< [  8:  8](R/W1S/H) Double-bit ECC error detected on PKT_P2X_TKN RAM. */
        uint64_t pkt_p2x_data_dbe      : 1;  /**< [  9:  9](R/W1S/H) Double-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_x2p_dbe           : 1;  /**< [ 10: 10](R/W1S/H) Double-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 11: 11](R/W1S/H) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t fpm_dbe               : 1;  /**< [ 12: 12](R/W1S/H) Double-bit ECC error detected on FPM RAM. */
        uint64_t ll_dbe                : 1;  /**< [ 13: 13](R/W1S/H) Double-bit ECC error detected on LL RAM. */
        uint64_t prc_dbe               : 1;  /**< [ 14: 14](R/W1S/H) Double-bit ECC error detected on PRC RAM. */
        uint64_t pm_dbe                : 1;  /**< [ 15: 15](R/W1S/H) Double-bit ECC error detected on PM RAM. */
        uint64_t prc_rollover          : 1;  /**< [ 16: 16](R/W1S/H) A PRC counter rolled over. */
        uint64_t prc_rollunder         : 1;  /**< [ 17: 17](R/W1S/H) A PRC counter rolled under. */
        uint64_t prc_urw_zero          : 1;  /**< [ 18: 18](R/W1S/H) A PRC counter was inappropriately decremented to zero by the URW. */
        uint64_t sst_addr_err          : 1;  /**< [ 19: 19](R/W1S/H) A CSR request to the SST blocks was directed to an invalid address. */
        uint64_t sst_req_timeout       : 1;  /**< [ 20: 20](R/W1S/H) A CSR request to the SST blocks timed out. */
        uint64_t sst_seq_err           : 1;  /**< [ 21: 21](R/W1S/H) A CSR request to the SST blocks experienced a fatal protocol sequence error. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_int_en_w1s_s cn; */
};
typedef union bdk_tns_tdma_nb_int_en_w1s bdk_tns_tdma_nb_int_en_w1s_t;

#define BDK_TNS_TDMA_NB_INT_EN_W1S BDK_TNS_TDMA_NB_INT_EN_W1S_FUNC()
static inline uint64_t BDK_TNS_TDMA_NB_INT_EN_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_INT_EN_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842041000120ll;
    __bdk_csr_fatal("TNS_TDMA_NB_INT_EN_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_INT_EN_W1S bdk_tns_tdma_nb_int_en_w1s_t
#define bustype_BDK_TNS_TDMA_NB_INT_EN_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_INT_EN_W1S "TNS_TDMA_NB_INT_EN_W1S"
#define device_bar_BDK_TNS_TDMA_NB_INT_EN_W1S 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_INT_EN_W1S 0
#define arguments_BDK_TNS_TDMA_NB_INT_EN_W1S -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_int_fen_w1c
 *
 * TNS TDMA Interrupt First Enable (Read/Write-1-Clear) Register
 * TDMA Interrupt First Enable Register.
 */
union bdk_tns_tdma_nb_int_fen_w1c
{
    uint64_t u;
    struct bdk_tns_tdma_nb_int_fen_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t sst_seq_err           : 1;  /**< [ 21: 21](R/W1C) A CSR request to the SST blocks experienced a fatal protocol sequence error. */
        uint64_t sst_req_timeout       : 1;  /**< [ 20: 20](R/W1C) A CSR request to the SST blocks timed out. */
        uint64_t sst_addr_err          : 1;  /**< [ 19: 19](R/W1C) A CSR request to the SST blocks was directed to an invalid address. */
        uint64_t prc_urw_zero          : 1;  /**< [ 18: 18](R/W1C) A PRC counter was inappropriately decremented to zero by the URW. */
        uint64_t prc_rollunder         : 1;  /**< [ 17: 17](R/W1C) A PRC counter rolled under. */
        uint64_t prc_rollover          : 1;  /**< [ 16: 16](R/W1C) A PRC counter rolled over. */
        uint64_t pm_dbe                : 1;  /**< [ 15: 15](R/W1C) Double-bit ECC error detected on PM RAM. */
        uint64_t prc_dbe               : 1;  /**< [ 14: 14](R/W1C) Double-bit ECC error detected on PRC RAM. */
        uint64_t ll_dbe                : 1;  /**< [ 13: 13](R/W1C) Double-bit ECC error detected on LL RAM. */
        uint64_t fpm_dbe               : 1;  /**< [ 12: 12](R/W1C) Double-bit ECC error detected on FPM RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 11: 11](R/W1C) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_x2p_dbe           : 1;  /**< [ 10: 10](R/W1C) Double-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_p2x_data_dbe      : 1;  /**< [  9:  9](R/W1C) Double-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_p2x_tkn_dbe       : 1;  /**< [  8:  8](R/W1C) Double-bit ECC error detected on PKT_P2X_TKN RAM. */
        uint64_t pm_sbe                : 1;  /**< [  7:  7](R/W1C) Single-bit ECC error detected on PM RAM. */
        uint64_t prc_sbe               : 1;  /**< [  6:  6](R/W1C) Single-bit ECC error detected on PRC RAM. */
        uint64_t ll_sbe                : 1;  /**< [  5:  5](R/W1C) Single-bit ECC error detected on LL RAM. */
        uint64_t fpm_sbe               : 1;  /**< [  4:  4](R/W1C) Single-bit ECC error detected on FPM RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [  3:  3](R/W1C) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_x2p_sbe           : 1;  /**< [  2:  2](R/W1C) Single-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_p2x_data_sbe      : 1;  /**< [  1:  1](R/W1C) Single-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_p2x_tkn_sbe       : 1;  /**< [  0:  0](R/W1C) Single-bit ECC error detected on PKT_P2X_TKN RAM. */
#else /* Word 0 - Little Endian */
        uint64_t pkt_p2x_tkn_sbe       : 1;  /**< [  0:  0](R/W1C) Single-bit ECC error detected on PKT_P2X_TKN RAM. */
        uint64_t pkt_p2x_data_sbe      : 1;  /**< [  1:  1](R/W1C) Single-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_x2p_sbe           : 1;  /**< [  2:  2](R/W1C) Single-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [  3:  3](R/W1C) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t fpm_sbe               : 1;  /**< [  4:  4](R/W1C) Single-bit ECC error detected on FPM RAM. */
        uint64_t ll_sbe                : 1;  /**< [  5:  5](R/W1C) Single-bit ECC error detected on LL RAM. */
        uint64_t prc_sbe               : 1;  /**< [  6:  6](R/W1C) Single-bit ECC error detected on PRC RAM. */
        uint64_t pm_sbe                : 1;  /**< [  7:  7](R/W1C) Single-bit ECC error detected on PM RAM. */
        uint64_t pkt_p2x_tkn_dbe       : 1;  /**< [  8:  8](R/W1C) Double-bit ECC error detected on PKT_P2X_TKN RAM. */
        uint64_t pkt_p2x_data_dbe      : 1;  /**< [  9:  9](R/W1C) Double-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_x2p_dbe           : 1;  /**< [ 10: 10](R/W1C) Double-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 11: 11](R/W1C) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t fpm_dbe               : 1;  /**< [ 12: 12](R/W1C) Double-bit ECC error detected on FPM RAM. */
        uint64_t ll_dbe                : 1;  /**< [ 13: 13](R/W1C) Double-bit ECC error detected on LL RAM. */
        uint64_t prc_dbe               : 1;  /**< [ 14: 14](R/W1C) Double-bit ECC error detected on PRC RAM. */
        uint64_t pm_dbe                : 1;  /**< [ 15: 15](R/W1C) Double-bit ECC error detected on PM RAM. */
        uint64_t prc_rollover          : 1;  /**< [ 16: 16](R/W1C) A PRC counter rolled over. */
        uint64_t prc_rollunder         : 1;  /**< [ 17: 17](R/W1C) A PRC counter rolled under. */
        uint64_t prc_urw_zero          : 1;  /**< [ 18: 18](R/W1C) A PRC counter was inappropriately decremented to zero by the URW. */
        uint64_t sst_addr_err          : 1;  /**< [ 19: 19](R/W1C) A CSR request to the SST blocks was directed to an invalid address. */
        uint64_t sst_req_timeout       : 1;  /**< [ 20: 20](R/W1C) A CSR request to the SST blocks timed out. */
        uint64_t sst_seq_err           : 1;  /**< [ 21: 21](R/W1C) A CSR request to the SST blocks experienced a fatal protocol sequence error. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_int_fen_w1c_s cn; */
};
typedef union bdk_tns_tdma_nb_int_fen_w1c bdk_tns_tdma_nb_int_fen_w1c_t;

#define BDK_TNS_TDMA_NB_INT_FEN_W1C BDK_TNS_TDMA_NB_INT_FEN_W1C_FUNC()
static inline uint64_t BDK_TNS_TDMA_NB_INT_FEN_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_INT_FEN_W1C_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842041000160ll;
    __bdk_csr_fatal("TNS_TDMA_NB_INT_FEN_W1C", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_INT_FEN_W1C bdk_tns_tdma_nb_int_fen_w1c_t
#define bustype_BDK_TNS_TDMA_NB_INT_FEN_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_INT_FEN_W1C "TNS_TDMA_NB_INT_FEN_W1C"
#define device_bar_BDK_TNS_TDMA_NB_INT_FEN_W1C 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_INT_FEN_W1C 0
#define arguments_BDK_TNS_TDMA_NB_INT_FEN_W1C -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_int_fen_w1s
 *
 * TNS TDMA Interrupt First Enable (Read/Write-1-Set) Register
 * TDMA Interrupt First Enable Register.
 */
union bdk_tns_tdma_nb_int_fen_w1s
{
    uint64_t u;
    struct bdk_tns_tdma_nb_int_fen_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t sst_seq_err           : 1;  /**< [ 21: 21](R/W1S) A CSR request to the SST blocks experienced a fatal protocol sequence error. */
        uint64_t sst_req_timeout       : 1;  /**< [ 20: 20](R/W1S) A CSR request to the SST blocks timed out. */
        uint64_t sst_addr_err          : 1;  /**< [ 19: 19](R/W1S) A CSR request to the SST blocks was directed to an invalid address. */
        uint64_t prc_urw_zero          : 1;  /**< [ 18: 18](R/W1S) A PRC counter was inappropriately decremented to zero by the URW. */
        uint64_t prc_rollunder         : 1;  /**< [ 17: 17](R/W1S) A PRC counter rolled under. */
        uint64_t prc_rollover          : 1;  /**< [ 16: 16](R/W1S) A PRC counter rolled over. */
        uint64_t pm_dbe                : 1;  /**< [ 15: 15](R/W1S) Double-bit ECC error detected on PM RAM. */
        uint64_t prc_dbe               : 1;  /**< [ 14: 14](R/W1S) Double-bit ECC error detected on PRC RAM. */
        uint64_t ll_dbe                : 1;  /**< [ 13: 13](R/W1S) Double-bit ECC error detected on LL RAM. */
        uint64_t fpm_dbe               : 1;  /**< [ 12: 12](R/W1S) Double-bit ECC error detected on FPM RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 11: 11](R/W1S) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_x2p_dbe           : 1;  /**< [ 10: 10](R/W1S) Double-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_p2x_data_dbe      : 1;  /**< [  9:  9](R/W1S) Double-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_p2x_tkn_dbe       : 1;  /**< [  8:  8](R/W1S) Double-bit ECC error detected on PKT_P2X_TKN RAM. */
        uint64_t pm_sbe                : 1;  /**< [  7:  7](R/W1S) Single-bit ECC error detected on PM RAM. */
        uint64_t prc_sbe               : 1;  /**< [  6:  6](R/W1S) Single-bit ECC error detected on PRC RAM. */
        uint64_t ll_sbe                : 1;  /**< [  5:  5](R/W1S) Single-bit ECC error detected on LL RAM. */
        uint64_t fpm_sbe               : 1;  /**< [  4:  4](R/W1S) Single-bit ECC error detected on FPM RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [  3:  3](R/W1S) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_x2p_sbe           : 1;  /**< [  2:  2](R/W1S) Single-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_p2x_data_sbe      : 1;  /**< [  1:  1](R/W1S) Single-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_p2x_tkn_sbe       : 1;  /**< [  0:  0](R/W1S) Single-bit ECC error detected on PKT_P2X_TKN RAM. */
#else /* Word 0 - Little Endian */
        uint64_t pkt_p2x_tkn_sbe       : 1;  /**< [  0:  0](R/W1S) Single-bit ECC error detected on PKT_P2X_TKN RAM. */
        uint64_t pkt_p2x_data_sbe      : 1;  /**< [  1:  1](R/W1S) Single-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_x2p_sbe           : 1;  /**< [  2:  2](R/W1S) Single-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [  3:  3](R/W1S) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t fpm_sbe               : 1;  /**< [  4:  4](R/W1S) Single-bit ECC error detected on FPM RAM. */
        uint64_t ll_sbe                : 1;  /**< [  5:  5](R/W1S) Single-bit ECC error detected on LL RAM. */
        uint64_t prc_sbe               : 1;  /**< [  6:  6](R/W1S) Single-bit ECC error detected on PRC RAM. */
        uint64_t pm_sbe                : 1;  /**< [  7:  7](R/W1S) Single-bit ECC error detected on PM RAM. */
        uint64_t pkt_p2x_tkn_dbe       : 1;  /**< [  8:  8](R/W1S) Double-bit ECC error detected on PKT_P2X_TKN RAM. */
        uint64_t pkt_p2x_data_dbe      : 1;  /**< [  9:  9](R/W1S) Double-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_x2p_dbe           : 1;  /**< [ 10: 10](R/W1S) Double-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 11: 11](R/W1S) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t fpm_dbe               : 1;  /**< [ 12: 12](R/W1S) Double-bit ECC error detected on FPM RAM. */
        uint64_t ll_dbe                : 1;  /**< [ 13: 13](R/W1S) Double-bit ECC error detected on LL RAM. */
        uint64_t prc_dbe               : 1;  /**< [ 14: 14](R/W1S) Double-bit ECC error detected on PRC RAM. */
        uint64_t pm_dbe                : 1;  /**< [ 15: 15](R/W1S) Double-bit ECC error detected on PM RAM. */
        uint64_t prc_rollover          : 1;  /**< [ 16: 16](R/W1S) A PRC counter rolled over. */
        uint64_t prc_rollunder         : 1;  /**< [ 17: 17](R/W1S) A PRC counter rolled under. */
        uint64_t prc_urw_zero          : 1;  /**< [ 18: 18](R/W1S) A PRC counter was inappropriately decremented to zero by the URW. */
        uint64_t sst_addr_err          : 1;  /**< [ 19: 19](R/W1S) A CSR request to the SST blocks was directed to an invalid address. */
        uint64_t sst_req_timeout       : 1;  /**< [ 20: 20](R/W1S) A CSR request to the SST blocks timed out. */
        uint64_t sst_seq_err           : 1;  /**< [ 21: 21](R/W1S) A CSR request to the SST blocks experienced a fatal protocol sequence error. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_int_fen_w1s_s cn; */
};
typedef union bdk_tns_tdma_nb_int_fen_w1s bdk_tns_tdma_nb_int_fen_w1s_t;

#define BDK_TNS_TDMA_NB_INT_FEN_W1S BDK_TNS_TDMA_NB_INT_FEN_W1S_FUNC()
static inline uint64_t BDK_TNS_TDMA_NB_INT_FEN_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_INT_FEN_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842041000150ll;
    __bdk_csr_fatal("TNS_TDMA_NB_INT_FEN_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_INT_FEN_W1S bdk_tns_tdma_nb_int_fen_w1s_t
#define bustype_BDK_TNS_TDMA_NB_INT_FEN_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_INT_FEN_W1S "TNS_TDMA_NB_INT_FEN_W1S"
#define device_bar_BDK_TNS_TDMA_NB_INT_FEN_W1S 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_INT_FEN_W1S 0
#define arguments_BDK_TNS_TDMA_NB_INT_FEN_W1S -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_int_fstat
 *
 * TNS TDMA Interrupt First Status Register
 * TDMA Interrupt First Status Register.
 */
union bdk_tns_tdma_nb_int_fstat
{
    uint64_t u;
    struct bdk_tns_tdma_nb_int_fstat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t sst_seq_err           : 1;  /**< [ 21: 21](RO/H) A CSR request to the SST blocks experienced a fatal protocol sequence error. */
        uint64_t sst_req_timeout       : 1;  /**< [ 20: 20](RO/H) A CSR request to the SST blocks timed out. */
        uint64_t sst_addr_err          : 1;  /**< [ 19: 19](RO/H) A CSR request to the SST blocks was directed to an invalid address. */
        uint64_t prc_urw_zero          : 1;  /**< [ 18: 18](RO/H) A PRC counter was inappropriately decremented to zero by the URW. */
        uint64_t prc_rollunder         : 1;  /**< [ 17: 17](RO/H) A PRC counter rolled under. */
        uint64_t prc_rollover          : 1;  /**< [ 16: 16](RO/H) A PRC counter rolled over. */
        uint64_t pm_dbe                : 1;  /**< [ 15: 15](RO/H) Double-bit ECC error detected on PM RAM. */
        uint64_t prc_dbe               : 1;  /**< [ 14: 14](RO/H) Double-bit ECC error detected on PRC RAM. */
        uint64_t ll_dbe                : 1;  /**< [ 13: 13](RO/H) Double-bit ECC error detected on LL RAM. */
        uint64_t fpm_dbe               : 1;  /**< [ 12: 12](RO/H) Double-bit ECC error detected on FPM RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 11: 11](RO/H) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_x2p_dbe           : 1;  /**< [ 10: 10](RO/H) Double-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_p2x_data_dbe      : 1;  /**< [  9:  9](RO/H) Double-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_p2x_tkn_dbe       : 1;  /**< [  8:  8](RO/H) Double-bit ECC error detected on PKT_P2X_TKN RAM. */
        uint64_t pm_sbe                : 1;  /**< [  7:  7](RO/H) Single-bit ECC error detected on PM RAM. */
        uint64_t prc_sbe               : 1;  /**< [  6:  6](RO/H) Single-bit ECC error detected on PRC RAM. */
        uint64_t ll_sbe                : 1;  /**< [  5:  5](RO/H) Single-bit ECC error detected on LL RAM. */
        uint64_t fpm_sbe               : 1;  /**< [  4:  4](RO/H) Single-bit ECC error detected on FPM RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [  3:  3](RO/H) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_x2p_sbe           : 1;  /**< [  2:  2](RO/H) Single-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_p2x_data_sbe      : 1;  /**< [  1:  1](RO/H) Single-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_p2x_tkn_sbe       : 1;  /**< [  0:  0](RO/H) Single-bit ECC error detected on PKT_P2X_TKN RAM. */
#else /* Word 0 - Little Endian */
        uint64_t pkt_p2x_tkn_sbe       : 1;  /**< [  0:  0](RO/H) Single-bit ECC error detected on PKT_P2X_TKN RAM. */
        uint64_t pkt_p2x_data_sbe      : 1;  /**< [  1:  1](RO/H) Single-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_x2p_sbe           : 1;  /**< [  2:  2](RO/H) Single-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [  3:  3](RO/H) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t fpm_sbe               : 1;  /**< [  4:  4](RO/H) Single-bit ECC error detected on FPM RAM. */
        uint64_t ll_sbe                : 1;  /**< [  5:  5](RO/H) Single-bit ECC error detected on LL RAM. */
        uint64_t prc_sbe               : 1;  /**< [  6:  6](RO/H) Single-bit ECC error detected on PRC RAM. */
        uint64_t pm_sbe                : 1;  /**< [  7:  7](RO/H) Single-bit ECC error detected on PM RAM. */
        uint64_t pkt_p2x_tkn_dbe       : 1;  /**< [  8:  8](RO/H) Double-bit ECC error detected on PKT_P2X_TKN RAM. */
        uint64_t pkt_p2x_data_dbe      : 1;  /**< [  9:  9](RO/H) Double-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_x2p_dbe           : 1;  /**< [ 10: 10](RO/H) Double-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 11: 11](RO/H) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t fpm_dbe               : 1;  /**< [ 12: 12](RO/H) Double-bit ECC error detected on FPM RAM. */
        uint64_t ll_dbe                : 1;  /**< [ 13: 13](RO/H) Double-bit ECC error detected on LL RAM. */
        uint64_t prc_dbe               : 1;  /**< [ 14: 14](RO/H) Double-bit ECC error detected on PRC RAM. */
        uint64_t pm_dbe                : 1;  /**< [ 15: 15](RO/H) Double-bit ECC error detected on PM RAM. */
        uint64_t prc_rollover          : 1;  /**< [ 16: 16](RO/H) A PRC counter rolled over. */
        uint64_t prc_rollunder         : 1;  /**< [ 17: 17](RO/H) A PRC counter rolled under. */
        uint64_t prc_urw_zero          : 1;  /**< [ 18: 18](RO/H) A PRC counter was inappropriately decremented to zero by the URW. */
        uint64_t sst_addr_err          : 1;  /**< [ 19: 19](RO/H) A CSR request to the SST blocks was directed to an invalid address. */
        uint64_t sst_req_timeout       : 1;  /**< [ 20: 20](RO/H) A CSR request to the SST blocks timed out. */
        uint64_t sst_seq_err           : 1;  /**< [ 21: 21](RO/H) A CSR request to the SST blocks experienced a fatal protocol sequence error. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_int_fstat_s cn; */
};
typedef union bdk_tns_tdma_nb_int_fstat bdk_tns_tdma_nb_int_fstat_t;

#define BDK_TNS_TDMA_NB_INT_FSTAT BDK_TNS_TDMA_NB_INT_FSTAT_FUNC()
static inline uint64_t BDK_TNS_TDMA_NB_INT_FSTAT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_INT_FSTAT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842041000140ll;
    __bdk_csr_fatal("TNS_TDMA_NB_INT_FSTAT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_INT_FSTAT bdk_tns_tdma_nb_int_fstat_t
#define bustype_BDK_TNS_TDMA_NB_INT_FSTAT BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_INT_FSTAT "TNS_TDMA_NB_INT_FSTAT"
#define device_bar_BDK_TNS_TDMA_NB_INT_FSTAT 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_INT_FSTAT 0
#define arguments_BDK_TNS_TDMA_NB_INT_FSTAT -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_int_stat_w1c
 *
 * TNS TDMA Interrupt Status (Read/Write-1-Clear) Register
 * TDMA Interrupt Status Register.
 */
union bdk_tns_tdma_nb_int_stat_w1c
{
    uint64_t u;
    struct bdk_tns_tdma_nb_int_stat_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t sst_seq_err           : 1;  /**< [ 21: 21](R/W1C/H) A CSR request to the SST blocks experienced a fatal protocol sequence error. */
        uint64_t sst_req_timeout       : 1;  /**< [ 20: 20](R/W1C/H) A CSR request to the SST blocks timed out. */
        uint64_t sst_addr_err          : 1;  /**< [ 19: 19](R/W1C/H) A CSR request to the SST blocks was directed to an invalid address. */
        uint64_t prc_urw_zero          : 1;  /**< [ 18: 18](R/W1C/H) A PRC counter was inappropriately decremented to zero by the URW. */
        uint64_t prc_rollunder         : 1;  /**< [ 17: 17](R/W1C/H) A PRC counter rolled under. */
        uint64_t prc_rollover          : 1;  /**< [ 16: 16](R/W1C/H) A PRC counter rolled over. */
        uint64_t pm_dbe                : 1;  /**< [ 15: 15](R/W1C/H) Double-bit ECC error detected on PM RAM. */
        uint64_t prc_dbe               : 1;  /**< [ 14: 14](R/W1C/H) Double-bit ECC error detected on PRC RAM. */
        uint64_t ll_dbe                : 1;  /**< [ 13: 13](R/W1C/H) Double-bit ECC error detected on LL RAM. */
        uint64_t fpm_dbe               : 1;  /**< [ 12: 12](R/W1C/H) Double-bit ECC error detected on FPM RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 11: 11](R/W1C/H) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_x2p_dbe           : 1;  /**< [ 10: 10](R/W1C/H) Double-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_p2x_data_dbe      : 1;  /**< [  9:  9](R/W1C/H) Double-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_p2x_tkn_dbe       : 1;  /**< [  8:  8](R/W1C/H) Double-bit ECC error detected on PKT_P2X_TKN RAM. */
        uint64_t pm_sbe                : 1;  /**< [  7:  7](R/W1C/H) Single-bit ECC error detected on PM RAM. */
        uint64_t prc_sbe               : 1;  /**< [  6:  6](R/W1C/H) Single-bit ECC error detected on PRC RAM. */
        uint64_t ll_sbe                : 1;  /**< [  5:  5](R/W1C/H) Single-bit ECC error detected on LL RAM. */
        uint64_t fpm_sbe               : 1;  /**< [  4:  4](R/W1C/H) Single-bit ECC error detected on FPM RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [  3:  3](R/W1C/H) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_x2p_sbe           : 1;  /**< [  2:  2](R/W1C/H) Single-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_p2x_data_sbe      : 1;  /**< [  1:  1](R/W1C/H) Single-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_p2x_tkn_sbe       : 1;  /**< [  0:  0](R/W1C/H) Single-bit ECC error detected on PKT_P2X_TKN RAM. */
#else /* Word 0 - Little Endian */
        uint64_t pkt_p2x_tkn_sbe       : 1;  /**< [  0:  0](R/W1C/H) Single-bit ECC error detected on PKT_P2X_TKN RAM. */
        uint64_t pkt_p2x_data_sbe      : 1;  /**< [  1:  1](R/W1C/H) Single-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_x2p_sbe           : 1;  /**< [  2:  2](R/W1C/H) Single-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [  3:  3](R/W1C/H) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t fpm_sbe               : 1;  /**< [  4:  4](R/W1C/H) Single-bit ECC error detected on FPM RAM. */
        uint64_t ll_sbe                : 1;  /**< [  5:  5](R/W1C/H) Single-bit ECC error detected on LL RAM. */
        uint64_t prc_sbe               : 1;  /**< [  6:  6](R/W1C/H) Single-bit ECC error detected on PRC RAM. */
        uint64_t pm_sbe                : 1;  /**< [  7:  7](R/W1C/H) Single-bit ECC error detected on PM RAM. */
        uint64_t pkt_p2x_tkn_dbe       : 1;  /**< [  8:  8](R/W1C/H) Double-bit ECC error detected on PKT_P2X_TKN RAM. */
        uint64_t pkt_p2x_data_dbe      : 1;  /**< [  9:  9](R/W1C/H) Double-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_x2p_dbe           : 1;  /**< [ 10: 10](R/W1C/H) Double-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 11: 11](R/W1C/H) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t fpm_dbe               : 1;  /**< [ 12: 12](R/W1C/H) Double-bit ECC error detected on FPM RAM. */
        uint64_t ll_dbe                : 1;  /**< [ 13: 13](R/W1C/H) Double-bit ECC error detected on LL RAM. */
        uint64_t prc_dbe               : 1;  /**< [ 14: 14](R/W1C/H) Double-bit ECC error detected on PRC RAM. */
        uint64_t pm_dbe                : 1;  /**< [ 15: 15](R/W1C/H) Double-bit ECC error detected on PM RAM. */
        uint64_t prc_rollover          : 1;  /**< [ 16: 16](R/W1C/H) A PRC counter rolled over. */
        uint64_t prc_rollunder         : 1;  /**< [ 17: 17](R/W1C/H) A PRC counter rolled under. */
        uint64_t prc_urw_zero          : 1;  /**< [ 18: 18](R/W1C/H) A PRC counter was inappropriately decremented to zero by the URW. */
        uint64_t sst_addr_err          : 1;  /**< [ 19: 19](R/W1C/H) A CSR request to the SST blocks was directed to an invalid address. */
        uint64_t sst_req_timeout       : 1;  /**< [ 20: 20](R/W1C/H) A CSR request to the SST blocks timed out. */
        uint64_t sst_seq_err           : 1;  /**< [ 21: 21](R/W1C/H) A CSR request to the SST blocks experienced a fatal protocol sequence error. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_int_stat_w1c_s cn; */
};
typedef union bdk_tns_tdma_nb_int_stat_w1c bdk_tns_tdma_nb_int_stat_w1c_t;

#define BDK_TNS_TDMA_NB_INT_STAT_W1C BDK_TNS_TDMA_NB_INT_STAT_W1C_FUNC()
static inline uint64_t BDK_TNS_TDMA_NB_INT_STAT_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_INT_STAT_W1C_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842041000110ll;
    __bdk_csr_fatal("TNS_TDMA_NB_INT_STAT_W1C", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_INT_STAT_W1C bdk_tns_tdma_nb_int_stat_w1c_t
#define bustype_BDK_TNS_TDMA_NB_INT_STAT_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_INT_STAT_W1C "TNS_TDMA_NB_INT_STAT_W1C"
#define device_bar_BDK_TNS_TDMA_NB_INT_STAT_W1C 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_INT_STAT_W1C 0
#define arguments_BDK_TNS_TDMA_NB_INT_STAT_W1C -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_int_stat_w1s
 *
 * TNS TDMA Interrupt Status (Read/Write-1-Set) Register
 * TDMA Interrupt Status Register.
 */
union bdk_tns_tdma_nb_int_stat_w1s
{
    uint64_t u;
    struct bdk_tns_tdma_nb_int_stat_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t sst_seq_err           : 1;  /**< [ 21: 21](R/W1S/H) A CSR request to the SST blocks experienced a fatal protocol sequence error. */
        uint64_t sst_req_timeout       : 1;  /**< [ 20: 20](R/W1S/H) A CSR request to the SST blocks timed out. */
        uint64_t sst_addr_err          : 1;  /**< [ 19: 19](R/W1S/H) A CSR request to the SST blocks was directed to an invalid address. */
        uint64_t prc_urw_zero          : 1;  /**< [ 18: 18](R/W1S/H) A PRC counter was inappropriately decremented to zero by the URW. */
        uint64_t prc_rollunder         : 1;  /**< [ 17: 17](R/W1S/H) A PRC counter rolled under. */
        uint64_t prc_rollover          : 1;  /**< [ 16: 16](R/W1S/H) A PRC counter rolled over. */
        uint64_t pm_dbe                : 1;  /**< [ 15: 15](R/W1S/H) Double-bit ECC error detected on PM RAM. */
        uint64_t prc_dbe               : 1;  /**< [ 14: 14](R/W1S/H) Double-bit ECC error detected on PRC RAM. */
        uint64_t ll_dbe                : 1;  /**< [ 13: 13](R/W1S/H) Double-bit ECC error detected on LL RAM. */
        uint64_t fpm_dbe               : 1;  /**< [ 12: 12](R/W1S/H) Double-bit ECC error detected on FPM RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 11: 11](R/W1S/H) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_x2p_dbe           : 1;  /**< [ 10: 10](R/W1S/H) Double-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_p2x_data_dbe      : 1;  /**< [  9:  9](R/W1S/H) Double-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_p2x_tkn_dbe       : 1;  /**< [  8:  8](R/W1S/H) Double-bit ECC error detected on PKT_P2X_TKN RAM. */
        uint64_t pm_sbe                : 1;  /**< [  7:  7](R/W1S/H) Single-bit ECC error detected on PM RAM. */
        uint64_t prc_sbe               : 1;  /**< [  6:  6](R/W1S/H) Single-bit ECC error detected on PRC RAM. */
        uint64_t ll_sbe                : 1;  /**< [  5:  5](R/W1S/H) Single-bit ECC error detected on LL RAM. */
        uint64_t fpm_sbe               : 1;  /**< [  4:  4](R/W1S/H) Single-bit ECC error detected on FPM RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [  3:  3](R/W1S/H) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t pkt_x2p_sbe           : 1;  /**< [  2:  2](R/W1S/H) Single-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_p2x_data_sbe      : 1;  /**< [  1:  1](R/W1S/H) Single-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_p2x_tkn_sbe       : 1;  /**< [  0:  0](R/W1S/H) Single-bit ECC error detected on PKT_P2X_TKN RAM. */
#else /* Word 0 - Little Endian */
        uint64_t pkt_p2x_tkn_sbe       : 1;  /**< [  0:  0](R/W1S/H) Single-bit ECC error detected on PKT_P2X_TKN RAM. */
        uint64_t pkt_p2x_data_sbe      : 1;  /**< [  1:  1](R/W1S/H) Single-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_x2p_sbe           : 1;  /**< [  2:  2](R/W1S/H) Single-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_lb_sbe            : 1;  /**< [  3:  3](R/W1S/H) Single-bit ECC error detected on PKT_LB RAM. */
        uint64_t fpm_sbe               : 1;  /**< [  4:  4](R/W1S/H) Single-bit ECC error detected on FPM RAM. */
        uint64_t ll_sbe                : 1;  /**< [  5:  5](R/W1S/H) Single-bit ECC error detected on LL RAM. */
        uint64_t prc_sbe               : 1;  /**< [  6:  6](R/W1S/H) Single-bit ECC error detected on PRC RAM. */
        uint64_t pm_sbe                : 1;  /**< [  7:  7](R/W1S/H) Single-bit ECC error detected on PM RAM. */
        uint64_t pkt_p2x_tkn_dbe       : 1;  /**< [  8:  8](R/W1S/H) Double-bit ECC error detected on PKT_P2X_TKN RAM. */
        uint64_t pkt_p2x_data_dbe      : 1;  /**< [  9:  9](R/W1S/H) Double-bit ECC error detected on PKT_P2X_DATA RAM. */
        uint64_t pkt_x2p_dbe           : 1;  /**< [ 10: 10](R/W1S/H) Double-bit ECC error detected on PKT_X2P RAM. */
        uint64_t pkt_lb_dbe            : 1;  /**< [ 11: 11](R/W1S/H) Double-bit ECC error detected on PKT_LB RAM. */
        uint64_t fpm_dbe               : 1;  /**< [ 12: 12](R/W1S/H) Double-bit ECC error detected on FPM RAM. */
        uint64_t ll_dbe                : 1;  /**< [ 13: 13](R/W1S/H) Double-bit ECC error detected on LL RAM. */
        uint64_t prc_dbe               : 1;  /**< [ 14: 14](R/W1S/H) Double-bit ECC error detected on PRC RAM. */
        uint64_t pm_dbe                : 1;  /**< [ 15: 15](R/W1S/H) Double-bit ECC error detected on PM RAM. */
        uint64_t prc_rollover          : 1;  /**< [ 16: 16](R/W1S/H) A PRC counter rolled over. */
        uint64_t prc_rollunder         : 1;  /**< [ 17: 17](R/W1S/H) A PRC counter rolled under. */
        uint64_t prc_urw_zero          : 1;  /**< [ 18: 18](R/W1S/H) A PRC counter was inappropriately decremented to zero by the URW. */
        uint64_t sst_addr_err          : 1;  /**< [ 19: 19](R/W1S/H) A CSR request to the SST blocks was directed to an invalid address. */
        uint64_t sst_req_timeout       : 1;  /**< [ 20: 20](R/W1S/H) A CSR request to the SST blocks timed out. */
        uint64_t sst_seq_err           : 1;  /**< [ 21: 21](R/W1S/H) A CSR request to the SST blocks experienced a fatal protocol sequence error. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_int_stat_w1s_s cn; */
};
typedef union bdk_tns_tdma_nb_int_stat_w1s bdk_tns_tdma_nb_int_stat_w1s_t;

#define BDK_TNS_TDMA_NB_INT_STAT_W1S BDK_TNS_TDMA_NB_INT_STAT_W1S_FUNC()
static inline uint64_t BDK_TNS_TDMA_NB_INT_STAT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_INT_STAT_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842041000100ll;
    __bdk_csr_fatal("TNS_TDMA_NB_INT_STAT_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_INT_STAT_W1S bdk_tns_tdma_nb_int_stat_w1s_t
#define bustype_BDK_TNS_TDMA_NB_INT_STAT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_INT_STAT_W1S "TNS_TDMA_NB_INT_STAT_W1S"
#define device_bar_BDK_TNS_TDMA_NB_INT_STAT_W1S 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_INT_STAT_W1S 0
#define arguments_BDK_TNS_TDMA_NB_INT_STAT_W1S -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_ll_acc#
 *
 * INTERNAL: TNS TDMA Link List Access Registers
 *
 * Provides the ability for software to access the TDMA Link List memory.
 * The LL consists of 12288 28-bit words.
 * The contents of each word is:
 * _ [27]    = SOP flag. This page contains the packet SOP. This page is a Header page.
 * _ [26]    = EOP flag. This page contains the packet EOP.
 * _ [25:12] = Next page. Only valid if EOP flag not set.
 * _ [11:8]  = Error code.
 * _ [7:0]   = Valid page bytes. 0 = 256 bytes.
 */
union bdk_tns_tdma_nb_ll_accx
{
    uint64_t u;
    struct bdk_tns_tdma_nb_ll_accx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_28_63        : 36;
        uint64_t data                  : 28; /**< [ 27:  0](R/W/H) Data. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 28; /**< [ 27:  0](R/W/H) Data. */
        uint64_t reserved_28_63        : 36;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_ll_accx_s cn; */
};
typedef union bdk_tns_tdma_nb_ll_accx bdk_tns_tdma_nb_ll_accx_t;

static inline uint64_t BDK_TNS_TDMA_NB_LL_ACCX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_LL_ACCX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=12287))
        return 0x842041040000ll + 0x10ll * ((a) & 0x3fff);
    __bdk_csr_fatal("TNS_TDMA_NB_LL_ACCX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_LL_ACCX(a) bdk_tns_tdma_nb_ll_accx_t
#define bustype_BDK_TNS_TDMA_NB_LL_ACCX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_LL_ACCX(a) "TNS_TDMA_NB_LL_ACCX"
#define device_bar_BDK_TNS_TDMA_NB_LL_ACCX(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_LL_ACCX(a) (a)
#define arguments_BDK_TNS_TDMA_NB_LL_ACCX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_lmac#_c_cdt_cfg
 *
 * TNS TDMA LMAC Channel Credit Config Register
 * Control use of channel credits for packet transmission on a per-LMAC basis.
 */
union bdk_tns_tdma_nb_lmacx_c_cdt_cfg
{
    uint64_t u;
    struct bdk_tns_tdma_nb_lmacx_c_cdt_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t use_cdts              : 1;  /**< [ 16: 16](R/W) 0 = Use EBP Xon/Xoff back pressure for per-priority LMAC scheduling.
                                                                     A packet may be scheduled for transmission as long as the LMAC is not
                                                                     indicating Xoff for the packet's priority.
                                                                 1 = Use channel credits for LMAC scheduling, giving all priorities equal weight.
                                                                     A packet may be scheduled for transmission as long as
                                                                     TNS_TDMA_NB_LMAC(0..7)_C_CDT_STAT[CONSUMED_CDTS] is less than CDT_LIMIT. */
        uint64_t reserved_10_15        : 6;
        uint64_t cdt_limit             : 10; /**< [  9:  0](R/W) Credit consumption limit at which packets will no longer be scheduled for
                                                                 transmission to the LMAC.
                                                                 Credits are consumed as the TDMA prepares the scheduled packet's data for
                                                                 transmission to the LMAC.
                                                                 Credits are returned by the LMAC when the packet is transmitted on the line.
                                                                 Each credit represents 16 bytes of packet data.
                                                                 Values above 0xA0 should be avoided in order to meet the 802.1Qbb skid requirement
                                                                 and to avoid unnecessarily sending data that could
                                                                 A low credit limit will allow the pipe between the TDMA packet scheduler
                                                                 and the LMAC to be less congested, and therefore more likely to meet the skid
                                                                 requirement, but could lead to decreased performance. */
#else /* Word 0 - Little Endian */
        uint64_t cdt_limit             : 10; /**< [  9:  0](R/W) Credit consumption limit at which packets will no longer be scheduled for
                                                                 transmission to the LMAC.
                                                                 Credits are consumed as the TDMA prepares the scheduled packet's data for
                                                                 transmission to the LMAC.
                                                                 Credits are returned by the LMAC when the packet is transmitted on the line.
                                                                 Each credit represents 16 bytes of packet data.
                                                                 Values above 0xA0 should be avoided in order to meet the 802.1Qbb skid requirement
                                                                 and to avoid unnecessarily sending data that could
                                                                 A low credit limit will allow the pipe between the TDMA packet scheduler
                                                                 and the LMAC to be less congested, and therefore more likely to meet the skid
                                                                 requirement, but could lead to decreased performance. */
        uint64_t reserved_10_15        : 6;
        uint64_t use_cdts              : 1;  /**< [ 16: 16](R/W) 0 = Use EBP Xon/Xoff back pressure for per-priority LMAC scheduling.
                                                                     A packet may be scheduled for transmission as long as the LMAC is not
                                                                     indicating Xoff for the packet's priority.
                                                                 1 = Use channel credits for LMAC scheduling, giving all priorities equal weight.
                                                                     A packet may be scheduled for transmission as long as
                                                                     TNS_TDMA_NB_LMAC(0..7)_C_CDT_STAT[CONSUMED_CDTS] is less than CDT_LIMIT. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_lmacx_c_cdt_cfg_s cn; */
};
typedef union bdk_tns_tdma_nb_lmacx_c_cdt_cfg bdk_tns_tdma_nb_lmacx_c_cdt_cfg_t;

static inline uint64_t BDK_TNS_TDMA_NB_LMACX_C_CDT_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_LMACX_C_CDT_CFG(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=7))
        return 0x842041000900ll + 0x10ll * ((a) & 0x7);
    __bdk_csr_fatal("TNS_TDMA_NB_LMACX_C_CDT_CFG", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_LMACX_C_CDT_CFG(a) bdk_tns_tdma_nb_lmacx_c_cdt_cfg_t
#define bustype_BDK_TNS_TDMA_NB_LMACX_C_CDT_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_LMACX_C_CDT_CFG(a) "TNS_TDMA_NB_LMACX_C_CDT_CFG"
#define device_bar_BDK_TNS_TDMA_NB_LMACX_C_CDT_CFG(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_LMACX_C_CDT_CFG(a) (a)
#define arguments_BDK_TNS_TDMA_NB_LMACX_C_CDT_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_lmac#_c_cdt_stat
 *
 * TNS TDMA LMAC Channel Credit Status Register
 */
union bdk_tns_tdma_nb_lmacx_c_cdt_stat
{
    uint64_t u;
    struct bdk_tns_tdma_nb_lmacx_c_cdt_stat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t cdts_consumed         : 10; /**< [  9:  0](RO/H) Current number of 16-byte credits consumed for packet transmission to the LMAC.
                                                                 Hardware updates this field regardless of TNS_TDMA_NB_LMAC(0..7)_C_CDT_CFG[USE_CDTS]. */
#else /* Word 0 - Little Endian */
        uint64_t cdts_consumed         : 10; /**< [  9:  0](RO/H) Current number of 16-byte credits consumed for packet transmission to the LMAC.
                                                                 Hardware updates this field regardless of TNS_TDMA_NB_LMAC(0..7)_C_CDT_CFG[USE_CDTS]. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_lmacx_c_cdt_stat_s cn; */
};
typedef union bdk_tns_tdma_nb_lmacx_c_cdt_stat bdk_tns_tdma_nb_lmacx_c_cdt_stat_t;

static inline uint64_t BDK_TNS_TDMA_NB_LMACX_C_CDT_STAT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_LMACX_C_CDT_STAT(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=7))
        return 0x842041000980ll + 0x10ll * ((a) & 0x7);
    __bdk_csr_fatal("TNS_TDMA_NB_LMACX_C_CDT_STAT", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_LMACX_C_CDT_STAT(a) bdk_tns_tdma_nb_lmacx_c_cdt_stat_t
#define bustype_BDK_TNS_TDMA_NB_LMACX_C_CDT_STAT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_LMACX_C_CDT_STAT(a) "TNS_TDMA_NB_LMACX_C_CDT_STAT"
#define device_bar_BDK_TNS_TDMA_NB_LMACX_C_CDT_STAT(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_LMACX_C_CDT_STAT(a) (a)
#define arguments_BDK_TNS_TDMA_NB_LMACX_C_CDT_STAT(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_lmac#_ebp_stat
 *
 * TNS TDMA LMAC EBP Status Register
 */
union bdk_tns_tdma_nb_lmacx_ebp_stat
{
    uint64_t u;
    struct bdk_tns_tdma_nb_lmacx_ebp_stat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t bp                    : 16; /**< [ 15:  0](RO/H) Back pressure status presented to TxQ for priorities 15..0. XOFF = 1. */
#else /* Word 0 - Little Endian */
        uint64_t bp                    : 16; /**< [ 15:  0](RO/H) Back pressure status presented to TxQ for priorities 15..0. XOFF = 1. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_lmacx_ebp_stat_s cn; */
};
typedef union bdk_tns_tdma_nb_lmacx_ebp_stat bdk_tns_tdma_nb_lmacx_ebp_stat_t;

static inline uint64_t BDK_TNS_TDMA_NB_LMACX_EBP_STAT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_LMACX_EBP_STAT(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=7))
        return 0x842041000a00ll + 0x10ll * ((a) & 0x7);
    __bdk_csr_fatal("TNS_TDMA_NB_LMACX_EBP_STAT", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_LMACX_EBP_STAT(a) bdk_tns_tdma_nb_lmacx_ebp_stat_t
#define bustype_BDK_TNS_TDMA_NB_LMACX_EBP_STAT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_LMACX_EBP_STAT(a) "TNS_TDMA_NB_LMACX_EBP_STAT"
#define device_bar_BDK_TNS_TDMA_NB_LMACX_EBP_STAT(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_LMACX_EBP_STAT(a) (a)
#define arguments_BDK_TNS_TDMA_NB_LMACX_EBP_STAT(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_page_rd_cnt#
 *
 * INTERNAL: TNS TDMA Memory Pages Read Counter Register
 */
union bdk_tns_tdma_nb_page_rd_cntx
{
    uint64_t u;
    struct bdk_tns_tdma_nb_page_rd_cntx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t pages                 : 32; /**< [ 31:  0](R/W/H) Packet memory pages accessed by the physical port.
                                                                 This field is a roll over counter.
                                                                 Register number enumerated by TNS_PHYS_PORT_E.
                                                                 Register number 11 corresponds to pages accessed due to drops and multiple copy (e.g.
                                                                 multicast) clearing.
                                                                 Multiple copy clearing is performed for all multiple copy packets to return pages to the
                                                                 free list.
                                                                 Multiple copy packets will be counted by each physical port that transmits the packet, as
                                                                 well as register 11 when the multiple copy is cleared. */
#else /* Word 0 - Little Endian */
        uint64_t pages                 : 32; /**< [ 31:  0](R/W/H) Packet memory pages accessed by the physical port.
                                                                 This field is a roll over counter.
                                                                 Register number enumerated by TNS_PHYS_PORT_E.
                                                                 Register number 11 corresponds to pages accessed due to drops and multiple copy (e.g.
                                                                 multicast) clearing.
                                                                 Multiple copy clearing is performed for all multiple copy packets to return pages to the
                                                                 free list.
                                                                 Multiple copy packets will be counted by each physical port that transmits the packet, as
                                                                 well as register 11 when the multiple copy is cleared. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_page_rd_cntx_s cn; */
};
typedef union bdk_tns_tdma_nb_page_rd_cntx bdk_tns_tdma_nb_page_rd_cntx_t;

static inline uint64_t BDK_TNS_TDMA_NB_PAGE_RD_CNTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_PAGE_RD_CNTX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=11))
        return 0x842041000700ll + 0x10ll * ((a) & 0xf);
    __bdk_csr_fatal("TNS_TDMA_NB_PAGE_RD_CNTX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_PAGE_RD_CNTX(a) bdk_tns_tdma_nb_page_rd_cntx_t
#define bustype_BDK_TNS_TDMA_NB_PAGE_RD_CNTX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_PAGE_RD_CNTX(a) "TNS_TDMA_NB_PAGE_RD_CNTX"
#define device_bar_BDK_TNS_TDMA_NB_PAGE_RD_CNTX(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_PAGE_RD_CNTX(a) (a)
#define arguments_BDK_TNS_TDMA_NB_PAGE_RD_CNTX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_page_src_cnt#
 *
 * TNS TDMA Source Page Counter Register
 * This register shows total counts of pages used for storing packet headers and bodies
 * from various different physical source ports, as enumerated by TNS_PHYS_PORT_E.
 * All fields have roll over counters.
 */
union bdk_tns_tdma_nb_page_src_cntx
{
    uint64_t u;
    struct bdk_tns_tdma_nb_page_src_cntx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t head                  : 32; /**< [ 63: 32](R/W/H) Pages used to store packet headers. */
        uint64_t body                  : 32; /**< [ 31:  0](R/W/H) Pages used to store packet bodies. */
#else /* Word 0 - Little Endian */
        uint64_t body                  : 32; /**< [ 31:  0](R/W/H) Pages used to store packet bodies. */
        uint64_t head                  : 32; /**< [ 63: 32](R/W/H) Pages used to store packet headers. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_page_src_cntx_s cn; */
};
typedef union bdk_tns_tdma_nb_page_src_cntx bdk_tns_tdma_nb_page_src_cntx_t;

static inline uint64_t BDK_TNS_TDMA_NB_PAGE_SRC_CNTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_PAGE_SRC_CNTX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=10))
        return 0x842041000500ll + 0x10ll * ((a) & 0xf);
    __bdk_csr_fatal("TNS_TDMA_NB_PAGE_SRC_CNTX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_PAGE_SRC_CNTX(a) bdk_tns_tdma_nb_page_src_cntx_t
#define bustype_BDK_TNS_TDMA_NB_PAGE_SRC_CNTX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_PAGE_SRC_CNTX(a) "TNS_TDMA_NB_PAGE_SRC_CNTX"
#define device_bar_BDK_TNS_TDMA_NB_PAGE_SRC_CNTX(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_PAGE_SRC_CNTX(a) (a)
#define arguments_BDK_TNS_TDMA_NB_PAGE_SRC_CNTX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_pages_used
 *
 * TNS TDMA Pages Used Counter Register
 */
union bdk_tns_tdma_nb_pages_used
{
    uint64_t u;
    struct bdk_tns_tdma_nb_pages_used_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t cnt                   : 14; /**< [ 13:  0](RO/H) Number of pages currently used to store packet data.
                                                                 Values range from 0 through 12288 (0x3000) when the entire packet memory is used.
                                                                 The number of avilable pages can be constrained by TNS_TDMA_NB_CONFIG1[PM_DEPTH]. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 14; /**< [ 13:  0](RO/H) Number of pages currently used to store packet data.
                                                                 Values range from 0 through 12288 (0x3000) when the entire packet memory is used.
                                                                 The number of avilable pages can be constrained by TNS_TDMA_NB_CONFIG1[PM_DEPTH]. */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_pages_used_s cn; */
};
typedef union bdk_tns_tdma_nb_pages_used bdk_tns_tdma_nb_pages_used_t;

#define BDK_TNS_TDMA_NB_PAGES_USED BDK_TNS_TDMA_NB_PAGES_USED_FUNC()
static inline uint64_t BDK_TNS_TDMA_NB_PAGES_USED_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_PAGES_USED_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x8420410005c0ll;
    __bdk_csr_fatal("TNS_TDMA_NB_PAGES_USED", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_PAGES_USED bdk_tns_tdma_nb_pages_used_t
#define bustype_BDK_TNS_TDMA_NB_PAGES_USED BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_PAGES_USED "TNS_TDMA_NB_PAGES_USED"
#define device_bar_BDK_TNS_TDMA_NB_PAGES_USED 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_PAGES_USED 0
#define arguments_BDK_TNS_TDMA_NB_PAGES_USED -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_perf_cntrl#
 *
 * INTERNAL: TDMA Performance Counter Control Register
 *
 * Performance counter control register.
 */
union bdk_tns_tdma_nb_perf_cntrlx
{
    uint64_t u;
    struct bdk_tns_tdma_nb_perf_cntrlx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t frozen                : 1;  /**< [ 31: 31](RO/H) Indicates that the counter is frozen (i.e one shot event occurred) and remains
                                                                 frozen until the clear bit written. */
        uint64_t clear                 : 1;  /**< [ 30: 30](WO/H) Writing 1 to this bit generates a hardware pulse that clears the
                                                                 TNS_TDMA_NB_PERF and field FROZEN of this register. The bit remains
                                                                 asserted continuously until 0 is written. */
        uint64_t enable                : 1;  /**< [ 29: 29](R/W) Enable the counter. This bit is set to 1 to use the corresponding counter. */
        uint64_t global_stop           : 1;  /**< [ 28: 28](R/W) This bit has two functions which are differentiated by the
                                                                 register number relative to the counter group.  For the
                                                                 zeroth (first) control register of the counter group,
                                                                 writing a 1 to this bit stops all the counters in the
                                                                 group of four counters. For the second control register of
                                                                 the counter group, writing a 1 to this bit globally enables
                                                                 all counters in the group. For all other control registers
                                                                 within the group, this bit is undefined. */
        uint64_t reserved_27           : 1;
        uint64_t mode                  : 3;  /**< [ 26: 24](R/W) Performance counter mode.

                                                                 Bit\<24\>:
                                                                 1 = Event counted SEL0.
                                                                 0 = Event counted SEL0 & SEL1 & SEL2.

                                                                 Bits\<26:25\>:
                                                                 0x0 = Pos edge.
                                                                 0x1 = Neg edge.
                                                                 0x2 = Level.
                                                                 0x3 = One shot. */
        uint64_t sel2                  : 8;  /**< [ 23: 16](R/W) Performance counter event select, third mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
        uint64_t sel1                  : 8;  /**< [ 15:  8](R/W) Performance counter event select, second mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
        uint64_t sel0                  : 8;  /**< [  7:  0](R/W) Performance counter event select, first mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
#else /* Word 0 - Little Endian */
        uint64_t sel0                  : 8;  /**< [  7:  0](R/W) Performance counter event select, first mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
        uint64_t sel1                  : 8;  /**< [ 15:  8](R/W) Performance counter event select, second mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
        uint64_t sel2                  : 8;  /**< [ 23: 16](R/W) Performance counter event select, third mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
        uint64_t mode                  : 3;  /**< [ 26: 24](R/W) Performance counter mode.

                                                                 Bit\<24\>:
                                                                 1 = Event counted SEL0.
                                                                 0 = Event counted SEL0 & SEL1 & SEL2.

                                                                 Bits\<26:25\>:
                                                                 0x0 = Pos edge.
                                                                 0x1 = Neg edge.
                                                                 0x2 = Level.
                                                                 0x3 = One shot. */
        uint64_t reserved_27           : 1;
        uint64_t global_stop           : 1;  /**< [ 28: 28](R/W) This bit has two functions which are differentiated by the
                                                                 register number relative to the counter group.  For the
                                                                 zeroth (first) control register of the counter group,
                                                                 writing a 1 to this bit stops all the counters in the
                                                                 group of four counters. For the second control register of
                                                                 the counter group, writing a 1 to this bit globally enables
                                                                 all counters in the group. For all other control registers
                                                                 within the group, this bit is undefined. */
        uint64_t enable                : 1;  /**< [ 29: 29](R/W) Enable the counter. This bit is set to 1 to use the corresponding counter. */
        uint64_t clear                 : 1;  /**< [ 30: 30](WO/H) Writing 1 to this bit generates a hardware pulse that clears the
                                                                 TNS_TDMA_NB_PERF and field FROZEN of this register. The bit remains
                                                                 asserted continuously until 0 is written. */
        uint64_t frozen                : 1;  /**< [ 31: 31](RO/H) Indicates that the counter is frozen (i.e one shot event occurred) and remains
                                                                 frozen until the clear bit written. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_perf_cntrlx_s cn; */
};
typedef union bdk_tns_tdma_nb_perf_cntrlx bdk_tns_tdma_nb_perf_cntrlx_t;

static inline uint64_t BDK_TNS_TDMA_NB_PERF_CNTRLX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_PERF_CNTRLX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X) && (a<=3))
        return 0x842041000b00ll + 0x10ll * ((a) & 0x3);
    __bdk_csr_fatal("TNS_TDMA_NB_PERF_CNTRLX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_PERF_CNTRLX(a) bdk_tns_tdma_nb_perf_cntrlx_t
#define bustype_BDK_TNS_TDMA_NB_PERF_CNTRLX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_PERF_CNTRLX(a) "TNS_TDMA_NB_PERF_CNTRLX"
#define device_bar_BDK_TNS_TDMA_NB_PERF_CNTRLX(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_PERF_CNTRLX(a) (a)
#define arguments_BDK_TNS_TDMA_NB_PERF_CNTRLX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_perf_status#
 *
 * INTERNAL: TDMA Performance Counter Status Register
 *
 * Performance counter status register.
 */
union bdk_tns_tdma_nb_perf_statusx
{
    uint64_t u;
    struct bdk_tns_tdma_nb_perf_statusx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Event counter */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Event counter */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_perf_statusx_s cn; */
};
typedef union bdk_tns_tdma_nb_perf_statusx bdk_tns_tdma_nb_perf_statusx_t;

static inline uint64_t BDK_TNS_TDMA_NB_PERF_STATUSX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_PERF_STATUSX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X) && (a<=3))
        return 0x842041000b40ll + 0x10ll * ((a) & 0x3);
    __bdk_csr_fatal("TNS_TDMA_NB_PERF_STATUSX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_PERF_STATUSX(a) bdk_tns_tdma_nb_perf_statusx_t
#define bustype_BDK_TNS_TDMA_NB_PERF_STATUSX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_PERF_STATUSX(a) "TNS_TDMA_NB_PERF_STATUSX"
#define device_bar_BDK_TNS_TDMA_NB_PERF_STATUSX(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_PERF_STATUSX(a) (a)
#define arguments_BDK_TNS_TDMA_NB_PERF_STATUSX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_prc_acc#
 *
 * INTERNAL: TNS TDMA Page Reference Count Access Registers
 *
 * Provides the ability for software to access the TDMA Page Reference Count memory.
 * The PRC consists of 12288 29-bit words.
 * The contents of each word is:
 * _ [28:25] = Source Port. Enumerated by TNS_PHYS_PORT_E.
 * _ [24:18] = Source Channel/Traffic Class.
 * _           Source Ports 0-7: {3'h0, Traffic Class(4)}
 * _           Source Ports 8-9: Source Channel(7)
 * _           Source Port   10: Unused
 * _ [17]    = Global Multicast Pool used.
 * _ [16]    = Shared Pool used.
 * _ [15:0]  = Page Reference Count. Number of times a page will be sent/dropped before being
 * _           returned to the free list.
 */
union bdk_tns_tdma_nb_prc_accx
{
    uint64_t u;
    struct bdk_tns_tdma_nb_prc_accx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_29_63        : 35;
        uint64_t data                  : 29; /**< [ 28:  0](R/W/H) Data. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 29; /**< [ 28:  0](R/W/H) Data. */
        uint64_t reserved_29_63        : 35;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_prc_accx_s cn; */
};
typedef union bdk_tns_tdma_nb_prc_accx bdk_tns_tdma_nb_prc_accx_t;

static inline uint64_t BDK_TNS_TDMA_NB_PRC_ACCX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_PRC_ACCX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=12287))
        return 0x842041080000ll + 0x10ll * ((a) & 0x3fff);
    __bdk_csr_fatal("TNS_TDMA_NB_PRC_ACCX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_PRC_ACCX(a) bdk_tns_tdma_nb_prc_accx_t
#define bustype_BDK_TNS_TDMA_NB_PRC_ACCX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_PRC_ACCX(a) "TNS_TDMA_NB_PRC_ACCX"
#define device_bar_BDK_TNS_TDMA_NB_PRC_ACCX(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_PRC_ACCX(a) (a)
#define arguments_BDK_TNS_TDMA_NB_PRC_ACCX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_prc_err
 *
 * TNS TDMA PRC Error Register
 */
union bdk_tns_tdma_nb_prc_err
{
    uint64_t u;
    struct bdk_tns_tdma_nb_prc_err_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t address               : 14; /**< [ 13:  0](RO/H) Captured address for PRC_ROLLOVER, PRC_ROLLUNDER, and PRC_URW_ZERO TNS_TDMA_NB_INT_STAT_W1S errors. */
#else /* Word 0 - Little Endian */
        uint64_t address               : 14; /**< [ 13:  0](RO/H) Captured address for PRC_ROLLOVER, PRC_ROLLUNDER, and PRC_URW_ZERO TNS_TDMA_NB_INT_STAT_W1S errors. */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_prc_err_s cn; */
};
typedef union bdk_tns_tdma_nb_prc_err bdk_tns_tdma_nb_prc_err_t;

#define BDK_TNS_TDMA_NB_PRC_ERR BDK_TNS_TDMA_NB_PRC_ERR_FUNC()
static inline uint64_t BDK_TNS_TDMA_NB_PRC_ERR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_PRC_ERR_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842041000820ll;
    __bdk_csr_fatal("TNS_TDMA_NB_PRC_ERR", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_PRC_ERR bdk_tns_tdma_nb_prc_err_t
#define bustype_BDK_TNS_TDMA_NB_PRC_ERR BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_PRC_ERR "TNS_TDMA_NB_PRC_ERR"
#define device_bar_BDK_TNS_TDMA_NB_PRC_ERR 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_PRC_ERR 0
#define arguments_BDK_TNS_TDMA_NB_PRC_ERR -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_status
 *
 * TNS TDMA Status Register
 * General status register.
 */
union bdk_tns_tdma_nb_status
{
    uint64_t u;
    struct bdk_tns_tdma_nb_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t init_done             : 1;  /**< [ 51: 51](RO/H) Set to 1 by hardware upon completion of auto-initialization.
                                                                 Cleared to 0 when software initiates hardware auto-initialization
                                                                 by writing to TNS_TDMA_NB_CONFIG[AUTO_INIT]. */
        uint64_t reserved_0_50         : 51;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_50         : 51;
        uint64_t init_done             : 1;  /**< [ 51: 51](RO/H) Set to 1 by hardware upon completion of auto-initialization.
                                                                 Cleared to 0 when software initiates hardware auto-initialization
                                                                 by writing to TNS_TDMA_NB_CONFIG[AUTO_INIT]. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_status_s cn; */
};
typedef union bdk_tns_tdma_nb_status bdk_tns_tdma_nb_status_t;

#define BDK_TNS_TDMA_NB_STATUS BDK_TNS_TDMA_NB_STATUS_FUNC()
static inline uint64_t BDK_TNS_TDMA_NB_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_STATUS_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842041000400ll;
    __bdk_csr_fatal("TNS_TDMA_NB_STATUS", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_STATUS bdk_tns_tdma_nb_status_t
#define bustype_BDK_TNS_TDMA_NB_STATUS BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_STATUS "TNS_TDMA_NB_STATUS"
#define device_bar_BDK_TNS_TDMA_NB_STATUS 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_STATUS 0
#define arguments_BDK_TNS_TDMA_NB_STATUS -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_strip_lmac#_xph
 *
 * TNS TDMA Strip to-LMAC Packet XPH Configuration Register
 */
union bdk_tns_tdma_nb_strip_lmacx_xph
{
    uint64_t u;
    struct bdk_tns_tdma_nb_strip_lmacx_xph_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t lmac                  : 1;  /**< [  0:  0](R/W) Strip and discard the 24-byte internal XPH packet header (if present) from packets during
                                                                 transmission to the LMAC. */
#else /* Word 0 - Little Endian */
        uint64_t lmac                  : 1;  /**< [  0:  0](R/W) Strip and discard the 24-byte internal XPH packet header (if present) from packets during
                                                                 transmission to the LMAC. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_strip_lmacx_xph_s cn; */
};
typedef union bdk_tns_tdma_nb_strip_lmacx_xph bdk_tns_tdma_nb_strip_lmacx_xph_t;

static inline uint64_t BDK_TNS_TDMA_NB_STRIP_LMACX_XPH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_STRIP_LMACX_XPH(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=7))
        return 0x842041000280ll + 0x10ll * ((a) & 0x7);
    __bdk_csr_fatal("TNS_TDMA_NB_STRIP_LMACX_XPH", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_STRIP_LMACX_XPH(a) bdk_tns_tdma_nb_strip_lmacx_xph_t
#define bustype_BDK_TNS_TDMA_NB_STRIP_LMACX_XPH(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_STRIP_LMACX_XPH(a) "TNS_TDMA_NB_STRIP_LMACX_XPH"
#define device_bar_BDK_TNS_TDMA_NB_STRIP_LMACX_XPH(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_STRIP_LMACX_XPH(a) (a)
#define arguments_BDK_TNS_TDMA_NB_STRIP_LMACX_XPH(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_strip_nic_xph#
 *
 * TNS TDMA Strip to-NIC Packet XPH Configuration Register
 */
union bdk_tns_tdma_nb_strip_nic_xphx
{
    uint64_t u;
    struct bdk_tns_tdma_nb_strip_nic_xphx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t chan                  : 64; /**< [ 63:  0](R/W) Strip and discard the 24-byte internal XPH packet header (if present) from packets during
                                                                 transmission to the NIC. */
#else /* Word 0 - Little Endian */
        uint64_t chan                  : 64; /**< [ 63:  0](R/W) Strip and discard the 24-byte internal XPH packet header (if present) from packets during
                                                                 transmission to the NIC. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_strip_nic_xphx_s cn; */
};
typedef union bdk_tns_tdma_nb_strip_nic_xphx bdk_tns_tdma_nb_strip_nic_xphx_t;

static inline uint64_t BDK_TNS_TDMA_NB_STRIP_NIC_XPHX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_STRIP_NIC_XPHX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x842041000240ll + 0x10ll * ((a) & 0x3);
    __bdk_csr_fatal("TNS_TDMA_NB_STRIP_NIC_XPHX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_STRIP_NIC_XPHX(a) bdk_tns_tdma_nb_strip_nic_xphx_t
#define bustype_BDK_TNS_TDMA_NB_STRIP_NIC_XPHX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_STRIP_NIC_XPHX(a) "TNS_TDMA_NB_STRIP_NIC_XPHX"
#define device_bar_BDK_TNS_TDMA_NB_STRIP_NIC_XPHX(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_STRIP_NIC_XPHX(a) (a)
#define arguments_BDK_TNS_TDMA_NB_STRIP_NIC_XPHX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_nb_truncate#_len
 *
 * TNS TDMA Truncate Length Configuration Register
 */
union bdk_tns_tdma_nb_truncatex_len
{
    uint64_t u;
    struct bdk_tns_tdma_nb_truncatex_len_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t length                : 9;  /**< [  8:  0](R/W) For designated packets, truncate packet to the specified length
                                                                 during transmission.
                                                                 Valid values are 0 through 256 (decimal).
                                                                 A value in this field larger than 256 will be interpreted as 256.
                                                                 No truncate will occur if set to 0x0.
                                                                 The truncate length applies to the bytes which are after the packet's
                                                                 24-byte XPH header, if present. */
#else /* Word 0 - Little Endian */
        uint64_t length                : 9;  /**< [  8:  0](R/W) For designated packets, truncate packet to the specified length
                                                                 during transmission.
                                                                 Valid values are 0 through 256 (decimal).
                                                                 A value in this field larger than 256 will be interpreted as 256.
                                                                 No truncate will occur if set to 0x0.
                                                                 The truncate length applies to the bytes which are after the packet's
                                                                 24-byte XPH header, if present. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_nb_truncatex_len_s cn; */
};
typedef union bdk_tns_tdma_nb_truncatex_len bdk_tns_tdma_nb_truncatex_len_t;

static inline uint64_t BDK_TNS_TDMA_NB_TRUNCATEX_LEN(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_NB_TRUNCATEX_LEN(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=10))
        return 0x842041000300ll + 0x10ll * ((a) & 0xf);
    __bdk_csr_fatal("TNS_TDMA_NB_TRUNCATEX_LEN", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_NB_TRUNCATEX_LEN(a) bdk_tns_tdma_nb_truncatex_len_t
#define bustype_BDK_TNS_TDMA_NB_TRUNCATEX_LEN(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_NB_TRUNCATEX_LEN(a) "TNS_TDMA_NB_TRUNCATEX_LEN"
#define device_bar_BDK_TNS_TDMA_NB_TRUNCATEX_LEN(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TDMA_NB_TRUNCATEX_LEN(a) (a)
#define arguments_BDK_TNS_TDMA_NB_TRUNCATEX_LEN(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_perf_cntrl#
 *
 * INTERNAL: TDMA Performance Counter Control Register
 *
 * Performance counter control register.
 */
union bdk_tns_tdma_perf_cntrlx
{
    uint64_t u;
    struct bdk_tns_tdma_perf_cntrlx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t frozen                : 1;  /**< [ 31: 31](RO/H) Indicates that the counter is frozen (i.e one shot event occurred) and remains
                                                                 frozen until the clear bit written. */
        uint64_t clear                 : 1;  /**< [ 30: 30](WO/H) Writing 1 to this bit generates a hardware pulse that clears the
                                                                 TNS_TDMA_PERF and field FROZEN of this register. The bit remains
                                                                 asserted continuously until 0 is written. */
        uint64_t enable                : 1;  /**< [ 29: 29](R/W) Enable the counter. This bit is set to 1 to use the corresponding counter. */
        uint64_t global_stop           : 1;  /**< [ 28: 28](R/W) This bit has two functions which are differentiated by the
                                                                 register number relative to the counter group.  For the
                                                                 zeroth (first) control register of the counter group,
                                                                 writing a 1 to this bit stops all the counters in the
                                                                 group of four counters. For the second control register of
                                                                 the counter group, writing a 1 to this bit globally enables
                                                                 all counters in the group. For all other control registers
                                                                 within the group, this bit is undefined. */
        uint64_t bank_select           : 1;  /**< [ 27: 27](R/W) Selection of event bank, where bank 0 corresponds to events [0..256)
                                                                 and bank 1 corresponds to events [256..512). */
        uint64_t mode                  : 3;  /**< [ 26: 24](R/W) Performance counter mode.

                                                                 Bit\<24\>:
                                                                 1 = Event counted SEL0 | SEL1 | SEL2.
                                                                 0 = Event counted SEL0 & SEL1 & SEL2.

                                                                 Bits\<26:25\>:
                                                                 0x0 = Pos edge.
                                                                 0x1 = Neg edge.
                                                                 0x2 = Level.
                                                                 0x3 = One shot. */
        uint64_t sel2                  : 8;  /**< [ 23: 16](R/W) Performance counter event select, third mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
        uint64_t sel1                  : 8;  /**< [ 15:  8](R/W) Performance counter event select, second mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
        uint64_t sel0                  : 8;  /**< [  7:  0](R/W) Performance counter event select, first mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
#else /* Word 0 - Little Endian */
        uint64_t sel0                  : 8;  /**< [  7:  0](R/W) Performance counter event select, first mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
        uint64_t sel1                  : 8;  /**< [ 15:  8](R/W) Performance counter event select, second mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
        uint64_t sel2                  : 8;  /**< [ 23: 16](R/W) Performance counter event select, third mux.
                                                                 Internal:
                                                                 For details of mapping of events to selects, see tns.perf. */
        uint64_t mode                  : 3;  /**< [ 26: 24](R/W) Performance counter mode.

                                                                 Bit\<24\>:
                                                                 1 = Event counted SEL0 | SEL1 | SEL2.
                                                                 0 = Event counted SEL0 & SEL1 & SEL2.

                                                                 Bits\<26:25\>:
                                                                 0x0 = Pos edge.
                                                                 0x1 = Neg edge.
                                                                 0x2 = Level.
                                                                 0x3 = One shot. */
        uint64_t bank_select           : 1;  /**< [ 27: 27](R/W) Selection of event bank, where bank 0 corresponds to events [0..256)
                                                                 and bank 1 corresponds to events [256..512). */
        uint64_t global_stop           : 1;  /**< [ 28: 28](R/W) This bit has two functions which are differentiated by the
                                                                 register number relative to the counter group.  For the
                                                                 zeroth (first) control register of the counter group,
                                                                 writing a 1 to this bit stops all the counters in the
                                                                 group of four counters. For the second control register of
                                                                 the counter group, writing a 1 to this bit globally enables
                                                                 all counters in the group. For all other control registers
                                                                 within the group, this bit is undefined. */
        uint64_t enable                : 1;  /**< [ 29: 29](R/W) Enable the counter. This bit is set to 1 to use the corresponding counter. */
        uint64_t clear                 : 1;  /**< [ 30: 30](WO/H) Writing 1 to this bit generates a hardware pulse that clears the
                                                                 TNS_TDMA_PERF and field FROZEN of this register. The bit remains
                                                                 asserted continuously until 0 is written. */
        uint64_t frozen                : 1;  /**< [ 31: 31](RO/H) Indicates that the counter is frozen (i.e one shot event occurred) and remains
                                                                 frozen until the clear bit written. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_perf_cntrlx_s cn; */
};
typedef union bdk_tns_tdma_perf_cntrlx bdk_tns_tdma_perf_cntrlx_t;

static inline uint64_t BDK_TNS_TDMA_PERF_CNTRLX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_PERF_CNTRLX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X) && (a<=3))
        return 0x842000000900ll + 0x10ll * ((a) & 0x3);
    __bdk_csr_fatal("TNS_TDMA_PERF_CNTRLX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_PERF_CNTRLX(a) bdk_tns_tdma_perf_cntrlx_t
#define bustype_BDK_TNS_TDMA_PERF_CNTRLX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_PERF_CNTRLX(a) "TNS_TDMA_PERF_CNTRLX"
#define device_bar_BDK_TNS_TDMA_PERF_CNTRLX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_PERF_CNTRLX(a) (a)
#define arguments_BDK_TNS_TDMA_PERF_CNTRLX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_perf_status#
 *
 * INTERNAL: RDMA Performance Counter Status Register
 *
 * Performance counter status register.
 */
union bdk_tns_tdma_perf_statusx
{
    uint64_t u;
    struct bdk_tns_tdma_perf_statusx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Event counter */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Event counter */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_perf_statusx_s cn; */
};
typedef union bdk_tns_tdma_perf_statusx bdk_tns_tdma_perf_statusx_t;

static inline uint64_t BDK_TNS_TDMA_PERF_STATUSX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_PERF_STATUSX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X) && (a<=3))
        return 0x842000000940ll + 0x10ll * ((a) & 0x3);
    __bdk_csr_fatal("TNS_TDMA_PERF_STATUSX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_PERF_STATUSX(a) bdk_tns_tdma_perf_statusx_t
#define bustype_BDK_TNS_TDMA_PERF_STATUSX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_PERF_STATUSX(a) "TNS_TDMA_PERF_STATUSX"
#define device_bar_BDK_TNS_TDMA_PERF_STATUSX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_PERF_STATUSX(a) (a)
#define arguments_BDK_TNS_TDMA_PERF_STATUSX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_pkt_x2p_cntrs#
 *
 * INTERNAL: Bypassed X2P Packet State Register
 *
 * NICI X2P packet transmission state.
 */
union bdk_tns_tdma_pkt_x2p_cntrsx
{
    uint64_t u;
    struct bdk_tns_tdma_pkt_x2p_cntrsx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_31_63        : 33;
        uint64_t req_pending_cnt       : 7;  /**< [ 30: 24](RO/H) Request pending count.
                                                                 Packet data in request FIFO that needs to have a request sent.
                                                                 Requests that have not yet been sent due to request credits being exhausted.
                                                                 This value ranges from 0 through 80.
                                                                 Each entry in the packet data FIFO represents up to 16 bytes of data. */
        uint64_t reserved_21_23        : 3;
        uint64_t req_credits           : 5;  /**< [ 20: 16](RO/H) Request credits. Ranges from 0 through 16. Each credit represents a request
                                                                 to send up to a 16-byte piece of packet data to the NICI. */
        uint64_t reserved_8_15         : 8;
        uint64_t fifo_cnt              : 8;  /**< [  7:  0](RO/H) Packet data FIFO occupancy for NICI.
                                                                 Ranges from 0 through 96. */
#else /* Word 0 - Little Endian */
        uint64_t fifo_cnt              : 8;  /**< [  7:  0](RO/H) Packet data FIFO occupancy for NICI.
                                                                 Ranges from 0 through 96. */
        uint64_t reserved_8_15         : 8;
        uint64_t req_credits           : 5;  /**< [ 20: 16](RO/H) Request credits. Ranges from 0 through 16. Each credit represents a request
                                                                 to send up to a 16-byte piece of packet data to the NICI. */
        uint64_t reserved_21_23        : 3;
        uint64_t req_pending_cnt       : 7;  /**< [ 30: 24](RO/H) Request pending count.
                                                                 Packet data in request FIFO that needs to have a request sent.
                                                                 Requests that have not yet been sent due to request credits being exhausted.
                                                                 This value ranges from 0 through 80.
                                                                 Each entry in the packet data FIFO represents up to 16 bytes of data. */
        uint64_t reserved_31_63        : 33;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_pkt_x2p_cntrsx_s cn; */
};
typedef union bdk_tns_tdma_pkt_x2p_cntrsx bdk_tns_tdma_pkt_x2p_cntrsx_t;

static inline uint64_t BDK_TNS_TDMA_PKT_X2P_CNTRSX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_PKT_X2P_CNTRSX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X) && (a<=1))
        return 0x842000000d00ll + 0x10ll * ((a) & 0x1);
    __bdk_csr_fatal("TNS_TDMA_PKT_X2P_CNTRSX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_PKT_X2P_CNTRSX(a) bdk_tns_tdma_pkt_x2p_cntrsx_t
#define bustype_BDK_TNS_TDMA_PKT_X2P_CNTRSX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_PKT_X2P_CNTRSX(a) "TNS_TDMA_PKT_X2P_CNTRSX"
#define device_bar_BDK_TNS_TDMA_PKT_X2P_CNTRSX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_PKT_X2P_CNTRSX(a) (a)
#define arguments_BDK_TNS_TDMA_PKT_X2P_CNTRSX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_reset_ctl
 *
 * TNS TDMA Reset Control Register
 * Allows software to reset individual components of the network switch.
 */
union bdk_tns_tdma_reset_ctl
{
    uint64_t u;
    struct bdk_tns_tdma_reset_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t sde_urw3_d            : 1;  /**< [ 39: 39](R/W) Reset SDE URW3 (D). */
        uint64_t sde_urw3_c            : 1;  /**< [ 38: 38](R/W) Reset SDE URW3 (C). */
        uint64_t sde_urw2_d            : 1;  /**< [ 37: 37](R/W) Reset SDE URW2 (D). */
        uint64_t sde_urw2_c            : 1;  /**< [ 36: 36](R/W) Reset SDE URW2 (C). */
        uint64_t sde_urw1_d            : 1;  /**< [ 35: 35](R/W) Reset SDE URW1 (D). */
        uint64_t sde_urw1_c            : 1;  /**< [ 34: 34](R/W) Reset SDE URW1 (C). */
        uint64_t sde_cnt_d             : 1;  /**< [ 33: 33](R/W) Reset SDE CNT (D). */
        uint64_t sde_cnt_c             : 1;  /**< [ 32: 32](R/W) Reset SDE CNT (C). */
        uint64_t sde_lde1_d            : 1;  /**< [ 31: 31](R/W) Reset SDE LDE1 (D). */
        uint64_t sde_lde1_c            : 1;  /**< [ 30: 30](R/W) Reset SDE LDE1 (C). */
        uint64_t sde_lde0_d            : 1;  /**< [ 29: 29](R/W) Reset SDE LDE0 (D). */
        uint64_t sde_lde0_c            : 1;  /**< [ 28: 28](R/W) Reset SDE LDE0 (C). */
        uint64_t sde_isme_d            : 1;  /**< [ 27: 27](R/W) Reset SDE ISME (D). */
        uint64_t sde_isme_c            : 1;  /**< [ 26: 26](R/W) Reset SDE ISME (C). */
        uint64_t sde_mre_d             : 1;  /**< [ 25: 25](R/W) Reset SDE MRE (D). */
        uint64_t sde_mre_c             : 1;  /**< [ 24: 24](R/W) Reset SDE MRE (C). */
        uint64_t sde_hdbf_d            : 1;  /**< [ 23: 23](R/W) Reset SDE HDBF (D). */
        uint64_t sde_hdbf_c            : 1;  /**< [ 22: 22](R/W) Reset SDE HDBF (C). */
        uint64_t sde_parser_d          : 1;  /**< [ 21: 21](R/W) Reset SDE PARSER (D). */
        uint64_t sde_parser_c          : 1;  /**< [ 20: 20](R/W) Reset SDE PARSER (C). */
        uint64_t txq_tbc_d             : 1;  /**< [ 19: 19](R/W) Reset TXQ TBC (D). */
        uint64_t txq_tbc_c             : 1;  /**< [ 18: 18](R/W) Reset TXQ TBC (C). */
        uint64_t txq_qac_d             : 1;  /**< [ 17: 17](R/W) Reset TXQ QAC (D). */
        uint64_t txq_qac_c             : 1;  /**< [ 16: 16](R/W) Reset TXQ QAC (C). */
        uint64_t txq_dq_d              : 1;  /**< [ 15: 15](R/W) Reset TXQ DQ (D). */
        uint64_t txq_dq_c              : 1;  /**< [ 14: 14](R/W) Reset TXQ DQ (C). */
        uint64_t txq_eq_d              : 1;  /**< [ 13: 13](R/W) Reset TXQ EQ (D). */
        uint64_t txq_eq_c              : 1;  /**< [ 12: 12](R/W) Reset TXQ EQ (C). */
        uint64_t se_ctl_d              : 1;  /**< [ 11: 11](R/W) Reset SE CTL (D). */
        uint64_t se_ctl_c              : 1;  /**< [ 10: 10](R/W) Reset SE CTL (C). */
        uint64_t se_age_d              : 1;  /**< [  9:  9](R/W) Reset SE AGE (D). */
        uint64_t se_age_c              : 1;  /**< [  8:  8](R/W) Reset SE AGE (C). */
        uint64_t se_tcam_d             : 1;  /**< [  7:  7](R/W) Reset SE TCAM (D). */
        uint64_t se_tcam_c             : 1;  /**< [  6:  6](R/W) Reset SE TCAM (C). */
        uint64_t se_sram_d             : 1;  /**< [  5:  5](R/W) Reset SE SRAM (D). */
        uint64_t se_sram_c             : 1;  /**< [  4:  4](R/W) Reset SE SRAM (C). */
        uint64_t reserved_2_3          : 2;
        uint64_t rdma                  : 1;  /**< [  1:  1](R/W) Reset RDMA packet switch path. */
        uint64_t tdma                  : 1;  /**< [  0:  0](R/W) Reset TDMA packet switch path. */
#else /* Word 0 - Little Endian */
        uint64_t tdma                  : 1;  /**< [  0:  0](R/W) Reset TDMA packet switch path. */
        uint64_t rdma                  : 1;  /**< [  1:  1](R/W) Reset RDMA packet switch path. */
        uint64_t reserved_2_3          : 2;
        uint64_t se_sram_c             : 1;  /**< [  4:  4](R/W) Reset SE SRAM (C). */
        uint64_t se_sram_d             : 1;  /**< [  5:  5](R/W) Reset SE SRAM (D). */
        uint64_t se_tcam_c             : 1;  /**< [  6:  6](R/W) Reset SE TCAM (C). */
        uint64_t se_tcam_d             : 1;  /**< [  7:  7](R/W) Reset SE TCAM (D). */
        uint64_t se_age_c              : 1;  /**< [  8:  8](R/W) Reset SE AGE (C). */
        uint64_t se_age_d              : 1;  /**< [  9:  9](R/W) Reset SE AGE (D). */
        uint64_t se_ctl_c              : 1;  /**< [ 10: 10](R/W) Reset SE CTL (C). */
        uint64_t se_ctl_d              : 1;  /**< [ 11: 11](R/W) Reset SE CTL (D). */
        uint64_t txq_eq_c              : 1;  /**< [ 12: 12](R/W) Reset TXQ EQ (C). */
        uint64_t txq_eq_d              : 1;  /**< [ 13: 13](R/W) Reset TXQ EQ (D). */
        uint64_t txq_dq_c              : 1;  /**< [ 14: 14](R/W) Reset TXQ DQ (C). */
        uint64_t txq_dq_d              : 1;  /**< [ 15: 15](R/W) Reset TXQ DQ (D). */
        uint64_t txq_qac_c             : 1;  /**< [ 16: 16](R/W) Reset TXQ QAC (C). */
        uint64_t txq_qac_d             : 1;  /**< [ 17: 17](R/W) Reset TXQ QAC (D). */
        uint64_t txq_tbc_c             : 1;  /**< [ 18: 18](R/W) Reset TXQ TBC (C). */
        uint64_t txq_tbc_d             : 1;  /**< [ 19: 19](R/W) Reset TXQ TBC (D). */
        uint64_t sde_parser_c          : 1;  /**< [ 20: 20](R/W) Reset SDE PARSER (C). */
        uint64_t sde_parser_d          : 1;  /**< [ 21: 21](R/W) Reset SDE PARSER (D). */
        uint64_t sde_hdbf_c            : 1;  /**< [ 22: 22](R/W) Reset SDE HDBF (C). */
        uint64_t sde_hdbf_d            : 1;  /**< [ 23: 23](R/W) Reset SDE HDBF (D). */
        uint64_t sde_mre_c             : 1;  /**< [ 24: 24](R/W) Reset SDE MRE (C). */
        uint64_t sde_mre_d             : 1;  /**< [ 25: 25](R/W) Reset SDE MRE (D). */
        uint64_t sde_isme_c            : 1;  /**< [ 26: 26](R/W) Reset SDE ISME (C). */
        uint64_t sde_isme_d            : 1;  /**< [ 27: 27](R/W) Reset SDE ISME (D). */
        uint64_t sde_lde0_c            : 1;  /**< [ 28: 28](R/W) Reset SDE LDE0 (C). */
        uint64_t sde_lde0_d            : 1;  /**< [ 29: 29](R/W) Reset SDE LDE0 (D). */
        uint64_t sde_lde1_c            : 1;  /**< [ 30: 30](R/W) Reset SDE LDE1 (C). */
        uint64_t sde_lde1_d            : 1;  /**< [ 31: 31](R/W) Reset SDE LDE1 (D). */
        uint64_t sde_cnt_c             : 1;  /**< [ 32: 32](R/W) Reset SDE CNT (C). */
        uint64_t sde_cnt_d             : 1;  /**< [ 33: 33](R/W) Reset SDE CNT (D). */
        uint64_t sde_urw1_c            : 1;  /**< [ 34: 34](R/W) Reset SDE URW1 (C). */
        uint64_t sde_urw1_d            : 1;  /**< [ 35: 35](R/W) Reset SDE URW1 (D). */
        uint64_t sde_urw2_c            : 1;  /**< [ 36: 36](R/W) Reset SDE URW2 (C). */
        uint64_t sde_urw2_d            : 1;  /**< [ 37: 37](R/W) Reset SDE URW2 (D). */
        uint64_t sde_urw3_c            : 1;  /**< [ 38: 38](R/W) Reset SDE URW3 (C). */
        uint64_t sde_urw3_d            : 1;  /**< [ 39: 39](R/W) Reset SDE URW3 (D). */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_reset_ctl_s cn; */
};
typedef union bdk_tns_tdma_reset_ctl bdk_tns_tdma_reset_ctl_t;

#define BDK_TNS_TDMA_RESET_CTL BDK_TNS_TDMA_RESET_CTL_FUNC()
static inline uint64_t BDK_TNS_TDMA_RESET_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_RESET_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000210ll;
    __bdk_csr_fatal("TNS_TDMA_RESET_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_RESET_CTL bdk_tns_tdma_reset_ctl_t
#define bustype_BDK_TNS_TDMA_RESET_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_RESET_CTL "TNS_TDMA_RESET_CTL"
#define device_bar_BDK_TNS_TDMA_RESET_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_RESET_CTL 0
#define arguments_BDK_TNS_TDMA_RESET_CTL -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_spare
 *
 * INTERNAL: TNS TDMA Spare Register
 *
 * Spare register.
 */
union bdk_tns_tdma_spare
{
    uint64_t u;
    struct bdk_tns_tdma_spare_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t spare                 : 64; /**< [ 63:  0](R/W) spare bits */
#else /* Word 0 - Little Endian */
        uint64_t spare                 : 64; /**< [ 63:  0](R/W) spare bits */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_spare_s cn; */
};
typedef union bdk_tns_tdma_spare bdk_tns_tdma_spare_t;

#define BDK_TNS_TDMA_SPARE BDK_TNS_TDMA_SPARE_FUNC()
static inline uint64_t BDK_TNS_TDMA_SPARE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_SPARE_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000e00ll;
    __bdk_csr_fatal("TNS_TDMA_SPARE", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_SPARE bdk_tns_tdma_spare_t
#define bustype_BDK_TNS_TDMA_SPARE BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_SPARE "TNS_TDMA_SPARE"
#define device_bar_BDK_TNS_TDMA_SPARE 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_SPARE 0
#define arguments_BDK_TNS_TDMA_SPARE -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_sst_acc_cmd
 *
 * TNS TDMA SST Indirect CSR Access Command Register
 */
union bdk_tns_tdma_sst_acc_cmd
{
    uint64_t u;
    struct bdk_tns_tdma_sst_acc_cmd_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_38_63        : 26;
        uint64_t go                    : 1;  /**< [ 37: 37](R/W/H) Perform read or write command. This bit is self-clearing upon request completion. */
        uint64_t op                    : 1;  /**< [ 36: 36](R/W) Operation type. 0 = Write. 1 = Read. */
        uint64_t size                  : 4;  /**< [ 35: 32](R/W) Transaction size, quantities of 32-bit words.
                                                                 0x0 = 16 words.
                                                                 0x1 = 1 word.
                                                                 0x2 = 2 words.
                                                                 0x3 = 3 words.
                                                                 ...
                                                                 0xf = 15 words. */
        uint64_t addr                  : 30; /**< [ 31:  2](R/W) 4-byte aligned address. */
        uint64_t reserved_0_1          : 2;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_1          : 2;
        uint64_t addr                  : 30; /**< [ 31:  2](R/W) 4-byte aligned address. */
        uint64_t size                  : 4;  /**< [ 35: 32](R/W) Transaction size, quantities of 32-bit words.
                                                                 0x0 = 16 words.
                                                                 0x1 = 1 word.
                                                                 0x2 = 2 words.
                                                                 0x3 = 3 words.
                                                                 ...
                                                                 0xf = 15 words. */
        uint64_t op                    : 1;  /**< [ 36: 36](R/W) Operation type. 0 = Write. 1 = Read. */
        uint64_t go                    : 1;  /**< [ 37: 37](R/W/H) Perform read or write command. This bit is self-clearing upon request completion. */
        uint64_t reserved_38_63        : 26;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_sst_acc_cmd_s cn; */
};
typedef union bdk_tns_tdma_sst_acc_cmd bdk_tns_tdma_sst_acc_cmd_t;

#define BDK_TNS_TDMA_SST_ACC_CMD BDK_TNS_TDMA_SST_ACC_CMD_FUNC()
static inline uint64_t BDK_TNS_TDMA_SST_ACC_CMD_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_SST_ACC_CMD_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000270ll;
    __bdk_csr_fatal("TNS_TDMA_SST_ACC_CMD", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_SST_ACC_CMD bdk_tns_tdma_sst_acc_cmd_t
#define bustype_BDK_TNS_TDMA_SST_ACC_CMD BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_SST_ACC_CMD "TNS_TDMA_SST_ACC_CMD"
#define device_bar_BDK_TNS_TDMA_SST_ACC_CMD 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_SST_ACC_CMD 0
#define arguments_BDK_TNS_TDMA_SST_ACC_CMD -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_sst_acc_rdat#
 *
 * TNS TDMA SST Indirect CSR Access Read Data Register
 */
union bdk_tns_tdma_sst_acc_rdatx
{
    uint64_t u;
    struct bdk_tns_tdma_sst_acc_rdatx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](RO/H) Read data.
                                                                 Valid only if command issued was a read request and TNS_TDMA_SST_ACC_STAT[CMD_DONE] is set
                                                                 and TNS_TDMA_SST_ACC_STAT[ERROR] is clear. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](RO/H) Read data.
                                                                 Valid only if command issued was a read request and TNS_TDMA_SST_ACC_STAT[CMD_DONE] is set
                                                                 and TNS_TDMA_SST_ACC_STAT[ERROR] is clear. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_sst_acc_rdatx_s cn; */
};
typedef union bdk_tns_tdma_sst_acc_rdatx bdk_tns_tdma_sst_acc_rdatx_t;

static inline uint64_t BDK_TNS_TDMA_SST_ACC_RDATX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_SST_ACC_RDATX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=7))
        return 0x842000000480ll + 0x10ll * ((a) & 0x7);
    __bdk_csr_fatal("TNS_TDMA_SST_ACC_RDATX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_SST_ACC_RDATX(a) bdk_tns_tdma_sst_acc_rdatx_t
#define bustype_BDK_TNS_TDMA_SST_ACC_RDATX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_SST_ACC_RDATX(a) "TNS_TDMA_SST_ACC_RDATX"
#define device_bar_BDK_TNS_TDMA_SST_ACC_RDATX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_SST_ACC_RDATX(a) (a)
#define arguments_BDK_TNS_TDMA_SST_ACC_RDATX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_sst_acc_stat
 *
 * TNS TDMA SST Indirect CSR Access Status Register
 */
union bdk_tns_tdma_sst_acc_stat
{
    uint64_t u;
    struct bdk_tns_tdma_sst_acc_stat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t error                 : 1;  /**< [  1:  1](RO/H) Command completed with error. */
        uint64_t cmd_done              : 1;  /**< [  0:  0](RO/H) Command issued by TNS_TDMA_SST_ACC_CMD has completed. */
#else /* Word 0 - Little Endian */
        uint64_t cmd_done              : 1;  /**< [  0:  0](RO/H) Command issued by TNS_TDMA_SST_ACC_CMD has completed. */
        uint64_t error                 : 1;  /**< [  1:  1](RO/H) Command completed with error. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_sst_acc_stat_s cn; */
};
typedef union bdk_tns_tdma_sst_acc_stat bdk_tns_tdma_sst_acc_stat_t;

#define BDK_TNS_TDMA_SST_ACC_STAT BDK_TNS_TDMA_SST_ACC_STAT_FUNC()
static inline uint64_t BDK_TNS_TDMA_SST_ACC_STAT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_SST_ACC_STAT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000470ll;
    __bdk_csr_fatal("TNS_TDMA_SST_ACC_STAT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_SST_ACC_STAT bdk_tns_tdma_sst_acc_stat_t
#define bustype_BDK_TNS_TDMA_SST_ACC_STAT BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_SST_ACC_STAT "TNS_TDMA_SST_ACC_STAT"
#define device_bar_BDK_TNS_TDMA_SST_ACC_STAT 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_SST_ACC_STAT 0
#define arguments_BDK_TNS_TDMA_SST_ACC_STAT -1,-1,-1,-1

/**
 * Register (NCB) tns_tdma_sst_acc_wdat#
 *
 * TNS TDMA SST Indirect CSR Access Write Data Register
 * Write data used during a write request issued via TNS_TDMA_SST_ACC_CMD.
 * The first data word is located at [31:0] of TNS_TDMA_SST_ACC_WDAT[0].
 */
union bdk_tns_tdma_sst_acc_wdatx
{
    uint64_t u;
    struct bdk_tns_tdma_sst_acc_wdatx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Write data. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Write data. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_sst_acc_wdatx_s cn; */
};
typedef union bdk_tns_tdma_sst_acc_wdatx bdk_tns_tdma_sst_acc_wdatx_t;

static inline uint64_t BDK_TNS_TDMA_SST_ACC_WDATX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_SST_ACC_WDATX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=7))
        return 0x842000000280ll + 0x10ll * ((a) & 0x7);
    __bdk_csr_fatal("TNS_TDMA_SST_ACC_WDATX", 1, a, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_SST_ACC_WDATX(a) bdk_tns_tdma_sst_acc_wdatx_t
#define bustype_BDK_TNS_TDMA_SST_ACC_WDATX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_SST_ACC_WDATX(a) "TNS_TDMA_SST_ACC_WDATX"
#define device_bar_BDK_TNS_TDMA_SST_ACC_WDATX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_SST_ACC_WDATX(a) (a)
#define arguments_BDK_TNS_TDMA_SST_ACC_WDATX(a) (a),-1,-1,-1

/**
 * Register (NCB) tns_tdma_status
 *
 * TNS TDMA Status Register
 */
union bdk_tns_tdma_status
{
    uint64_t u;
    struct bdk_tns_tdma_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t pcc_busy              : 1;  /**< [  0:  0](RO/H) When 1, indicates the PCC MSI-X table is currently in-use by hardware.
                                                                 CSR and memory transactions are prohibited until this bit becomes 0.
                                                                 Upon power-on this bit will be 1 as the PCC performs auto-initialization. */
#else /* Word 0 - Little Endian */
        uint64_t pcc_busy              : 1;  /**< [  0:  0](RO/H) When 1, indicates the PCC MSI-X table is currently in-use by hardware.
                                                                 CSR and memory transactions are prohibited until this bit becomes 0.
                                                                 Upon power-on this bit will be 1 as the PCC performs auto-initialization. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_tdma_status_s cn; */
};
typedef union bdk_tns_tdma_status bdk_tns_tdma_status_t;

#define BDK_TNS_TDMA_STATUS BDK_TNS_TDMA_STATUS_FUNC()
static inline uint64_t BDK_TNS_TDMA_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TDMA_STATUS_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842000000410ll;
    __bdk_csr_fatal("TNS_TDMA_STATUS", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TDMA_STATUS bdk_tns_tdma_status_t
#define bustype_BDK_TNS_TDMA_STATUS BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TDMA_STATUS "TNS_TDMA_STATUS"
#define device_bar_BDK_TNS_TDMA_STATUS 0x0 /* PF_BAR0 */
#define busnum_BDK_TNS_TDMA_STATUS 0
#define arguments_BDK_TNS_TDMA_STATUS -1,-1,-1,-1

/**
 * Register (NCB) tns_txq_eq_cfg_spare
 *
 * INTERNAL: TNS TXQ EQ CFG SPARE Register
 *
 * Spare register with default signature value 0x210FEDCBA9876543 after reset.
 */
union bdk_tns_txq_eq_cfg_spare
{
    uint64_t u;
    struct bdk_tns_txq_eq_cfg_spare_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t spare_x1              : 32; /**< [ 63: 32](R/W) Spare field high. */
        uint64_t spare_x0              : 32; /**< [ 31:  0](R/W) Spare field low. */
#else /* Word 0 - Little Endian */
        uint64_t spare_x0              : 32; /**< [ 31:  0](R/W) Spare field low. */
        uint64_t spare_x1              : 32; /**< [ 63: 32](R/W) Spare field high. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tns_txq_eq_cfg_spare_s cn; */
};
typedef union bdk_tns_txq_eq_cfg_spare bdk_tns_txq_eq_cfg_spare_t;

#define BDK_TNS_TXQ_EQ_CFG_SPARE BDK_TNS_TXQ_EQ_CFG_SPARE_FUNC()
static inline uint64_t BDK_TNS_TXQ_EQ_CFG_SPARE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TNS_TXQ_EQ_CFG_SPARE_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x842078e84910ll;
    __bdk_csr_fatal("TNS_TXQ_EQ_CFG_SPARE", 0, 0, 0, 0, 0);
}

#define typedef_BDK_TNS_TXQ_EQ_CFG_SPARE bdk_tns_txq_eq_cfg_spare_t
#define bustype_BDK_TNS_TXQ_EQ_CFG_SPARE BDK_CSR_TYPE_NCB
#define basename_BDK_TNS_TXQ_EQ_CFG_SPARE "TNS_TXQ_EQ_CFG_SPARE"
#define device_bar_BDK_TNS_TXQ_EQ_CFG_SPARE 0x2 /* PF_BAR2 */
#define busnum_BDK_TNS_TXQ_EQ_CFG_SPARE 0
#define arguments_BDK_TNS_TXQ_EQ_CFG_SPARE -1,-1,-1,-1

#endif /* __BDK_CSRS_TNS_H__ */
