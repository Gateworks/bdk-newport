#ifndef __BDK_CSRS_NIC_H__
#define __BDK_CSRS_NIC_H__
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
 * OcteonTX NIC.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration nic_bar_e
 *
 * NIC Base-Address Register Enumeration
 * Enumerates the base-address registers.
 */
#define BDK_NIC_BAR_E_NIC_PF_BAR0 (0x843000000000ll)
#define BDK_NIC_BAR_E_NIC_PF_BAR0_SIZE 0x40000000ull
#define BDK_NIC_BAR_E_NIC_PF_BAR4 (0x843060000000ll)
#define BDK_NIC_BAR_E_NIC_PF_BAR4_SIZE 0x100000ull
#define BDK_NIC_BAR_E_NIC_VFX_BAR0(a) (0x8430a0000000ll + 0x200000ll * (a))
#define BDK_NIC_BAR_E_NIC_VFX_BAR0_SIZE 0x200000ull
#define BDK_NIC_BAR_E_NIC_VFX_BAR4(a) (0x8430e0000000ll + 0x200000ll * (a))
#define BDK_NIC_BAR_E_NIC_VFX_BAR4_SIZE 0x200000ull

/**
 * Enumeration nic_chan_e
 *
 * NIC Channel Number Enumeration
 * Enumerates the receive and transmit channels, and values of NIC_CQE_RX_S[CHAN].
 * NIC only uses the subset of this enumeration that is enumerated by NIC_CHAN_IDX_E.
 *
 * Internal:
 * P2X/X2P channel enumeration for t81, t83, ...
 */
#define BDK_NIC_CHAN_E_BGXX_LMACX_CHX(a,b,c) (0x800 + 0x100 * (a) + 0x10 * (b) + (c))
#define BDK_NIC_CHAN_E_DPI_CHX(a) (0x400 + (a))
#define BDK_NIC_CHAN_E_LBKX_CHX(a,b) (0 + 0x100 * (a) + (b))
#define BDK_NIC_CHAN_E_PKO_NULL (0xfff)
#define BDK_NIC_CHAN_E_RX(a) (0 + 0x100 * (a))

/**
 * Enumeration nic_chan_idx_e
 *
 * NIC Channel Index Enumeration
 * Enumerates the internal RX/TX channels, and the index of NIC_PF_CHAN()_TX_CFG,
 * NIC_PF_CHAN()_RX_CFG, NIC_PF_CHAN()_SW_XOFF and NIC_PF_CHAN()_CREDIT.
 */
#define BDK_NIC_CHAN_IDX_E_BGXX_LMACX_CHX(a,b,c) (0 + 0x20 * (a) + 8 * (b) + (c))
#define BDK_NIC_CHAN_IDX_E_LBKX_CHX_CN81XX(a,b) (0x48 + 0x40 * (a) + (b))
#define BDK_NIC_CHAN_IDX_E_LBKX_CHX_CN83XX(a,b) (0x80 + 0x40 * (a) + (b))
#define BDK_NIC_CHAN_IDX_E_RGXX_LMACX_CHX(a,b,c) (0x40 + 0x20 * (a) + 8 * (b) + (c))

/**
 * Enumeration nic_cpi_alg_e
 *
 * NIC CPI Algorithm Enumeration
 * Enumerates the values of NIC_PF_CHAN()_RX_CFG[CPI_ALG].
 */
#define BDK_NIC_CPI_ALG_E_DIFF (3)
#define BDK_NIC_CPI_ALG_E_NONE (0)
#define BDK_NIC_CPI_ALG_E_VLAN (1)
#define BDK_NIC_CPI_ALG_E_VLAN16 (2)

/**
 * Enumeration nic_cqe_send_status_e
 *
 * NIC CQE Send Status Enumeration
 * Enumerates send status codes for NIC_CQE_SEND_S[SEND_STATUS].
 */
#define BDK_NIC_CQE_SEND_STATUS_E_CK_DERR (0x8a)
#define BDK_NIC_CQE_SEND_STATUS_E_CK_PERR (0x8b)
#define BDK_NIC_CQE_SEND_STATUS_E_DATA_FAULT (0x84)
#define BDK_NIC_CQE_SEND_STATUS_E_DESC_FAULT (0x10)
#define BDK_NIC_CQE_SEND_STATUS_E_DESC_SEQUENCE_ERR (0x8c)
#define BDK_NIC_CQE_SEND_STATUS_E_GOOD (0)
#define BDK_NIC_CQE_SEND_STATUS_E_HDR_CONS_ERR (0x11)
#define BDK_NIC_CQE_SEND_STATUS_E_IMM_SIZE_OFLOW (0x80)
#define BDK_NIC_CQE_SEND_STATUS_E_LOCK_VIOL (0x83)
#define BDK_NIC_CQE_SEND_STATUS_E_MAX_SIZE_VIOL (0x13)
#define BDK_NIC_CQE_SEND_STATUS_E_MEM_FAULT (0x87)
#define BDK_NIC_CQE_SEND_STATUS_E_SUBDC_ERR (0x12)
#define BDK_NIC_CQE_SEND_STATUS_E_TSTMP_CONFLICT (0x85)
#define BDK_NIC_CQE_SEND_STATUS_E_TSTMP_TIMEOUT (0x86)

/**
 * Enumeration nic_cqe_type_e
 *
 * NIC Completion-Queue Entry Type Enumeration
 * Enumerates CQE types, e.g. see NIC_CQE_SEND_S[CQE_TYPE].
 */
#define BDK_NIC_CQE_TYPE_E_INVALID (0)
#define BDK_NIC_CQE_TYPE_E_RX (2)
#define BDK_NIC_CQE_TYPE_E_RX_SPLT (3)
#define BDK_NIC_CQE_TYPE_E_SEND (8)
#define BDK_NIC_CQE_TYPE_E_SEND_PTP (9)

/**
 * Enumeration nic_errlev_e
 *
 * NIC Error Level Enumeration
 * Enumerates the values of NIC_CQE_RX_S[ERRLEV].
 */
#define BDK_NIC_ERRLEV_E_L2 (1)
#define BDK_NIC_ERRLEV_E_L3 (2)
#define BDK_NIC_ERRLEV_E_L4 (3)
#define BDK_NIC_ERRLEV_E_LE (4)
#define BDK_NIC_ERRLEV_E_LF (5)
#define BDK_NIC_ERRLEV_E_RE (0)

/**
 * Enumeration nic_errop_e
 *
 * NIC Error Opcode Enumeration
 * Enumerates the values of NIC_CQE_RX_S[ERROP].
 */
#define BDK_NIC_ERROP_E_IP_CHK (0x42)
#define BDK_NIC_ERROP_E_IP_HOP (0x45)
#define BDK_NIC_ERROP_E_IP_MAL (0x43)
#define BDK_NIC_ERROP_E_IP_MALD (0x44)
#define BDK_NIC_ERROP_E_IP_NOT (0x41)
#define BDK_NIC_ERROP_E_L2_LENMISM (0x27)
#define BDK_NIC_ERROP_E_L2_MAL (0x24)
#define BDK_NIC_ERROP_E_L2_OVERSIZE (0x25)
#define BDK_NIC_ERROP_E_L2_PCLP (0x28)
#define BDK_NIC_ERROP_E_L2_UNDERSIZE (0x26)
#define BDK_NIC_ERROP_E_L3_ICRC (0x46)
#define BDK_NIC_ERROP_E_L3_PCLP (0x47)
#define BDK_NIC_ERROP_E_L4_CHK (0x62)
#define BDK_NIC_ERROP_E_L4_MAL (0x61)
#define BDK_NIC_ERROP_E_L4_PCLP (0x67)
#define BDK_NIC_ERROP_E_L4_PORT (0x64)
#define BDK_NIC_ERROP_E_PREL2_ERR (0x1f)
#define BDK_NIC_ERROP_E_RBDR_TRUNC (0x70)
#define BDK_NIC_ERROP_E_RE_FCS (7)
#define BDK_NIC_ERROP_E_RE_JABBER (2)
#define BDK_NIC_ERROP_E_RE_NONE (0)
#define BDK_NIC_ERROP_E_RE_PARTIAL (1)
#define BDK_NIC_ERROP_E_RE_RX_CTL (0xb)
#define BDK_NIC_ERROP_E_RE_TERMINATE (9)
#define BDK_NIC_ERROP_E_TCP_FLAG (0x65)
#define BDK_NIC_ERROP_E_TCP_OFFSET (0x66)
#define BDK_NIC_ERROP_E_TUN_MAL (0x1d)
#define BDK_NIC_ERROP_E_TUN_PCLP (0x1e)
#define BDK_NIC_ERROP_E_UDP_LEN (0x63)

/**
 * Enumeration nic_ethertype_e
 *
 * NIC Ethertypes Enumeration
 * Enumerates the standard Ethertype values.
 */
#define BDK_NIC_ETHERTYPE_E_ARP (0x806)
#define BDK_NIC_ETHERTYPE_E_CNM (0x22e9)
#define BDK_NIC_ETHERTYPE_E_IP (0x800)
#define BDK_NIC_ETHERTYPE_E_IP6 (0x86dd)
#define BDK_NIC_ETHERTYPE_E_MPLS_8847 (0x8847)
#define BDK_NIC_ETHERTYPE_E_MPLS_8848 (0x8848)
#define BDK_NIC_ETHERTYPE_E_REVARP (0x8035)
#define BDK_NIC_ETHERTYPE_E_ROCE (0x8915)
#define BDK_NIC_ETHERTYPE_E_VLAN (0x8100)
#define BDK_NIC_ETHERTYPE_E_VLAN_88A8 (0x88a8)
#define BDK_NIC_ETHERTYPE_E_VLAN_9100 (0x9100)
#define BDK_NIC_ETHERTYPE_E_VLAN_9200 (0x9200)
#define BDK_NIC_ETHERTYPE_E_VLAN_9300 (0x9300)

/**
 * Enumeration nic_etype_alg_e
 *
 * NIC Ethertype Algorithm Enumeration
 * Enumerates the values of NIC_PF_RX_ETYPE()[ALG].
 */
#define BDK_NIC_ETYPE_ALG_E_ENDPARSE (2)
#define BDK_NIC_ETYPE_ALG_E_NONE (0)
#define BDK_NIC_ETYPE_ALG_E_SKIP (1)
#define BDK_NIC_ETYPE_ALG_E_VLAN (3)
#define BDK_NIC_ETYPE_ALG_E_VLAN_STRIP (4)

/**
 * Enumeration nic_intf_block_e
 *
 * NIC Interface Block ID Enumeration
 * Enumerates the interface blocks, corresponding to the upper four bits of NIC_CHAN_E,
 * and enumerates the values of NIC_PF_INTF()_BP_CFG[BP_ID] and NIC_PF_RX_WRR_CFG()[SLOT*].
 * NIC only uses the subset enumerated by NIC_INTF_E.
 */
#define BDK_NIC_INTF_BLOCK_E_BGXX(a) (8 + (a))
#define BDK_NIC_INTF_BLOCK_E_DPI (4)
#define BDK_NIC_INTF_BLOCK_E_LBKX(a) (0 + (a))
#define BDK_NIC_INTF_BLOCK_E_RX(a) (0 + (a))

/**
 * Enumeration nic_intf_e
 *
 * NIC Interface Enumeration
 * Enumerates the internal interfaces, and indexes of NIC_PF_INTF()_SEND_CFG and
 * NIC_PF_INTF()_BP_CFG.
 */
#define BDK_NIC_INTF_E_BGXX(a) (0 + (a))
#define BDK_NIC_INTF_E_LBKX_CN81XX(a) (3 + (a))
#define BDK_NIC_INTF_E_LBKX_CN83XX(a) (4 + (a))
#define BDK_NIC_INTF_E_RGXX(a) (2 + (a))

/**
 * Enumeration nic_ipproto_e
 *
 * NIC IP Protocol Enumeration
 * Enumerates the IPv4 protocol and IPv6 next-header values.
 */
#define BDK_NIC_IPPROTO_E_AH (0x33)
#define BDK_NIC_IPPROTO_E_DEST (0x3c)
#define BDK_NIC_IPPROTO_E_ESP (0x32)
#define BDK_NIC_IPPROTO_E_FRAG (0x2c)
#define BDK_NIC_IPPROTO_E_GRE (0x2f)
#define BDK_NIC_IPPROTO_E_HOP_BY_HOP (0)
#define BDK_NIC_IPPROTO_E_IP4 (4)
#define BDK_NIC_IPPROTO_E_IP6 (0x29)
#define BDK_NIC_IPPROTO_E_IPCOMP (0x6c)
#define BDK_NIC_IPPROTO_E_ROUTING (0x2b)
#define BDK_NIC_IPPROTO_E_TCP (6)
#define BDK_NIC_IPPROTO_E_UDP (0x11)

/**
 * Enumeration nic_l3type_e
 *
 * NIC Layer 3 Type Enumeration
 * Enumerates the values of NIC_CQE_RX_S[L3TY].
 */
#define BDK_NIC_L3TYPE_E_ET_STOP (0xd)
#define BDK_NIC_L3TYPE_E_GRH (1)
#define BDK_NIC_L3TYPE_E_IP4 (4)
#define BDK_NIC_L3TYPE_E_IP4_OPT (5)
#define BDK_NIC_L3TYPE_E_IP6 (6)
#define BDK_NIC_L3TYPE_E_IP6_OPT (7)
#define BDK_NIC_L3TYPE_E_NONE (0)
#define BDK_NIC_L3TYPE_E_OTHER (0xe)

/**
 * Enumeration nic_l4type_e
 *
 * NIC Layer 4 Type Enumeration
 * Enumerates the values of NIC_CQE_RX_S[L4TY].
 */
#define BDK_NIC_L4TYPE_E_BTH (5)
#define BDK_NIC_L4TYPE_E_GRE (7)
#define BDK_NIC_L4TYPE_E_IPCOMP (3)
#define BDK_NIC_L4TYPE_E_IPFRAG (2)
#define BDK_NIC_L4TYPE_E_IPSEC_ESP (1)
#define BDK_NIC_L4TYPE_E_NONE (0)
#define BDK_NIC_L4TYPE_E_NVGRE (0xc)
#define BDK_NIC_L4TYPE_E_OTHER (0xe)
#define BDK_NIC_L4TYPE_E_SCTP (6)
#define BDK_NIC_L4TYPE_E_TCP (4)
#define BDK_NIC_L4TYPE_E_UDP (8)
#define BDK_NIC_L4TYPE_E_UDP_BTH (0xb)
#define BDK_NIC_L4TYPE_E_UDP_GENEVE (9)
#define BDK_NIC_L4TYPE_E_UDP_VXLAN (0xa)

/**
 * Enumeration nic_lbk_rx_conn_e
 *
 * NIC Loopback Receive Connection Enumeration
 * Specifies which LBK block connects to NIC's internal NIC_INTF_E::LBK()
 * receive interface. Values enumerated by NIC_INTF_BLOCK_E::LBK().
 */
#define BDK_NIC_LBK_RX_CONN_E_LBKX_CN81XX(a) (0 + (a))
#define BDK_NIC_LBK_RX_CONN_E_LBKX_CN83XX(a) (2 + (a))

/**
 * Enumeration nic_lbk_tx_conn_e
 *
 * NIC Loopback Transmit Connection Enumeration
 * Specifies which LBK block connects to NIC's internal NIC_INTF_E::LBK()
 * transmit interface. Values enumerated by NIC_INTF_BLOCK_E::LBK().
 */
#define BDK_NIC_LBK_TX_CONN_E_LBKX_CN81XX(a) (0 + (a))
#define BDK_NIC_LBK_TX_CONN_E_LBKX_CN83XX(a) (1 + 2 * (a))

/**
 * Enumeration nic_lmac_e
 *
 * NIC LMAC Enumeration
 * Enumerates the index of NIC_PF_LMAC()_CFG, NIC_PF_LMAC()_CFG2, NIC_PF_LMAC()_SW_XOFF
 * and NIC_PF_LMAC()_CREDIT.
 *
 * Internal:
 * Also enumerates the index of NIC_PF_SW_SYNC_PIPE()_CQ_CNTS and
 * NIC_PF_SW_SYNC_PIPE()_PKT_CNTS.
 */
#define BDK_NIC_LMAC_E_BGXX_LMACX(a,b) (0 + 4 * (a) + (b))
#define BDK_NIC_LMAC_E_LBKX_CN81XX(a) (9 + (a))
#define BDK_NIC_LMAC_E_LBKX_CN83XX(a) (0x10 + (a))
#define BDK_NIC_LMAC_E_RGXX_LMACX(a,b) (8 + 4 * (a) + (b))

/**
 * Enumeration nic_pf_int_vec_e
 *
 * NIC PF MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_NIC_PF_INT_VEC_E_ECC0_DBE (1)
#define BDK_NIC_PF_INT_VEC_E_ECC0_SBE (0)
#define BDK_NIC_PF_INT_VEC_E_ECC1_DBE (3)
#define BDK_NIC_PF_INT_VEC_E_ECC1_SBE (2)
#define BDK_NIC_PF_INT_VEC_E_ECC2_DBE (5)
#define BDK_NIC_PF_INT_VEC_E_ECC2_SBE (4)
#define BDK_NIC_PF_INT_VEC_E_ECC3_DBE (7)
#define BDK_NIC_PF_INT_VEC_E_ECC3_SBE (6)
#define BDK_NIC_PF_INT_VEC_E_MBOXX(a) (8 + (a))

/**
 * Enumeration nic_rss_alg_e
 *
 * NIC RSS Algorithm Enumeration
 * Enumerates the values of NIC_CQE_RX_S[RSS_ALG].
 */
#define BDK_NIC_RSS_ALG_E_GRE_IP (6)
#define BDK_NIC_RSS_ALG_E_INNER_GRE_IP (0xc)
#define BDK_NIC_RSS_ALG_E_INNER_IP (8)
#define BDK_NIC_RSS_ALG_E_INNER_ROCE (0xd)
#define BDK_NIC_RSS_ALG_E_INNER_SCTP_IP (0xb)
#define BDK_NIC_RSS_ALG_E_INNER_TCP_IP (9)
#define BDK_NIC_RSS_ALG_E_INNER_UDP_IP (0xa)
#define BDK_NIC_RSS_ALG_E_IP (2)
#define BDK_NIC_RSS_ALG_E_NONE (0)
#define BDK_NIC_RSS_ALG_E_PORT (1)
#define BDK_NIC_RSS_ALG_E_ROCE (7)
#define BDK_NIC_RSS_ALG_E_SCTP_IP (5)
#define BDK_NIC_RSS_ALG_E_TCP_IP (3)
#define BDK_NIC_RSS_ALG_E_UDP_IP (4)

/**
 * Enumeration nic_send_ckl4_e
 *
 * NIC Send Checksum L4 Enumeration
 * Enumerates the different L4 checksum algorithms for NIC_SEND_HDR_S[CKL4].
 */
#define BDK_NIC_SEND_CKL4_E_NONE (0)
#define BDK_NIC_SEND_CKL4_E_TCP (2)
#define BDK_NIC_SEND_CKL4_E_UDP (1)

/**
 * Enumeration nic_send_crcalg_e
 *
 * NIC Send-CRC Algorithm Enumeration
 * Enumerates the CRC algorithm used, see NIC_SEND_CRC_S[ALG].
 */
#define BDK_NIC_SEND_CRCALG_E_CKSUM (3)
#define BDK_NIC_SEND_CRCALG_E_CRC32 (0)
#define BDK_NIC_SEND_CRCALG_E_CRC32C (1)
#define BDK_NIC_SEND_CRCALG_E_ICRC (2)

/**
 * Enumeration nic_send_ld_type_e
 *
 * NIC Send Load Type Enumeration
 * Enumerates the load transaction types for reading segment bytes specified by
 * NIC_SEND_GATHER_S[LD_TYPE].
 */
#define BDK_NIC_SEND_LD_TYPE_E_LDD (0)
#define BDK_NIC_SEND_LD_TYPE_E_LDT (1)
#define BDK_NIC_SEND_LD_TYPE_E_LDWB (2)

/**
 * Enumeration nic_send_memalg_e
 *
 * NIC Send Memory-Modify Algorithm Enumeration
 * Enumerates the algorithms for modifying memory, see NIC_SEND_MEM_S[ALG].
 */
#define BDK_NIC_SEND_MEMALG_E_ADD (8)
#define BDK_NIC_SEND_MEMALG_E_ADDLEN (0xa)
#define BDK_NIC_SEND_MEMALG_E_SET (0)
#define BDK_NIC_SEND_MEMALG_E_SUB (9)
#define BDK_NIC_SEND_MEMALG_E_SUBLEN (0xb)

/**
 * Enumeration nic_send_memdsz_e
 *
 * NIC Send Memory-Data Size Enumeration
 * Enumerates the datum size for modifying memory, see NIC_SEND_MEM_S[DSZ].
 */
#define BDK_NIC_SEND_MEMDSZ_E_B16 (2)
#define BDK_NIC_SEND_MEMDSZ_E_B32 (1)
#define BDK_NIC_SEND_MEMDSZ_E_B64 (0)
#define BDK_NIC_SEND_MEMDSZ_E_B8 (3)

/**
 * Enumeration nic_send_subdc_e
 *
 * NIC Send Subdescriptor Operation Enumeration
 * Enumerates the send subdescriptor codes.
 */
#define BDK_NIC_SEND_SUBDC_E_CRC (2)
#define BDK_NIC_SEND_SUBDC_E_EOD (0xf)
#define BDK_NIC_SEND_SUBDC_E_GATHER (4)
#define BDK_NIC_SEND_SUBDC_E_HDR (1)
#define BDK_NIC_SEND_SUBDC_E_IMM (3)
#define BDK_NIC_SEND_SUBDC_E_INVALID (0)
#define BDK_NIC_SEND_SUBDC_E_MEM (5)
#define BDK_NIC_SEND_SUBDC_E_SOD (0xe)

/**
 * Enumeration nic_stat_rq_e
 *
 * NIC RQ Statistics Enumeration
 * Enumerates the index of NIC_PF_QS()_RQ()_STAT() and NIC_QS()_RQ()_STAT().
 */
#define BDK_NIC_STAT_RQ_E_OCTS (0)
#define BDK_NIC_STAT_RQ_E_PKTS (1)

/**
 * Enumeration nic_stat_sq_e
 *
 * NIC SQ Statistics Enumeration
 * Enumerates the index of NIC_PF_QS()_SQ()_STAT() and NIC_QS()_SQ()_STAT().
 */
#define BDK_NIC_STAT_SQ_E_OCTS (0)
#define BDK_NIC_STAT_SQ_E_PKTS (1)

/**
 * Enumeration nic_stat_vnic_rx_e
 *
 * NIC VNIC Receive Statistics Enumeration
 * Enumerates the index of NIC_PF_VNIC()_RX_STAT() and NIC_VNIC()_RX_STAT().
 * Internal:
 * INTERNAL: The following were defined for Octeon but are not included here:
 * RX_FRAG - Number of non-dropped packets with length \< minimum and FCS error
 * RX_UNDERSZ - Number of non-dropped packets with length \< minimum and no FCS error.
 * RX_JABBER - Number of non-dropped packets with length \> maximum and FCS error.
 * RX_OVERSZ - Number of non-dropped packets with length \> maximum and no FCS error.
 * RX_H1TO63 - Number of non-dropped 1 to 63 byte packets. Includes any timestamps, RX headers
 * and excludes FCS.
 * RX_H64TO127 - Number of non-dropped 64 to 127 byte packets.
 * RX_H128TO255 - Number of non-dropped 128 to 255 byte packets.
 * RX_H256TO511 - Number of non-dropped 256 to 511 byte packets.
 * RX_H512TO1023 - Number of non-dropped 512 to 1023 byte packets.
 * RX_H1024TO1518 - Number of non-dropped 1024 to 1518 byte packets.
 * RX_H1519 - Number of non-dropped 1519 byte and above packets.
 */
#define BDK_NIC_STAT_VNIC_RX_E_RX_BCAST (2)
#define BDK_NIC_STAT_VNIC_RX_E_RX_DRP_BCAST (0xa)
#define BDK_NIC_STAT_VNIC_RX_E_RX_DRP_L3BCAST (0xc)
#define BDK_NIC_STAT_VNIC_RX_E_RX_DRP_L3MCAST (0xd)
#define BDK_NIC_STAT_VNIC_RX_E_RX_DRP_MCAST (0xb)
#define BDK_NIC_STAT_VNIC_RX_E_RX_FCS (8)
#define BDK_NIC_STAT_VNIC_RX_E_RX_L2ERR (9)
#define BDK_NIC_STAT_VNIC_RX_E_RX_MCAST (3)
#define BDK_NIC_STAT_VNIC_RX_E_RX_OCTS (0)
#define BDK_NIC_STAT_VNIC_RX_E_RX_ORUN (6)
#define BDK_NIC_STAT_VNIC_RX_E_RX_ORUN_OCTS (7)
#define BDK_NIC_STAT_VNIC_RX_E_RX_RED (4)
#define BDK_NIC_STAT_VNIC_RX_E_RX_RED_OCTS (5)
#define BDK_NIC_STAT_VNIC_RX_E_RX_UCAST (1)

/**
 * Enumeration nic_stat_vnic_tx_e
 *
 * NIC VNIC Transmit Statistics Enumeration
 * Enumerates the index of NIC_PF_VNIC()_TX_STAT() and NIC_VNIC()_TX_STAT().
 */
#define BDK_NIC_STAT_VNIC_TX_E_TX_BCAST (2)
#define BDK_NIC_STAT_VNIC_TX_E_TX_DROP (4)
#define BDK_NIC_STAT_VNIC_TX_E_TX_MCAST (3)
#define BDK_NIC_STAT_VNIC_TX_E_TX_OCTS (0)
#define BDK_NIC_STAT_VNIC_TX_E_TX_UCAST (1)

/**
 * Enumeration nic_vf_int_vec_e
 *
 * NIC VF MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_NIC_VF_INT_VEC_E_CQX(a) (0 + (a))
#define BDK_NIC_VF_INT_VEC_E_MISC (0x12)
#define BDK_NIC_VF_INT_VEC_E_QS_ERR (0x13)
#define BDK_NIC_VF_INT_VEC_E_RBDRX(a) (0x10 + (a))
#define BDK_NIC_VF_INT_VEC_E_SQX(a) (8 + (a))

/**
 * Structure nic_cqe_rx2_s
 *
 * NIC CQE Receive Tunneling Extension Structure
 * Format of receive completion queue entry tunneling extension. This extension structure is
 * inserted at word 6 of a CQE, immediately following the NIC_CQE_RX_S.
 */
union bdk_nic_cqe_rx2_s
{
    uint64_t u;
    struct bdk_nic_cqe_rx2_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t vv_i                  : 1;  /**< [ 63: 63] Same as NIC_CQE_RX_S[VV], but for the inner layer. */
        uint64_t vv_gone_i             : 1;  /**< [ 62: 62] Same as NIC_CQE_RX_S[VV_GONE], but for the inner layer. */
        uint64_t vs_i                  : 1;  /**< [ 61: 61] Same as NIC_CQE_RX_S[VS], but for the inner layer. */
        uint64_t vs_gone_i             : 1;  /**< [ 60: 60] Same as NIC_CQE_RX_S[VS_GONE], but for the inner layer. */
        uint64_t reserved_57_59        : 3;
        uint64_t l2e_i                 : 1;  /**< [ 56: 56] Indicates a L2 Ethernet layer was detected on the inner layer of a tunneled
                                                                 packet. */
        uint64_t lfty                  : 4;  /**< [ 55: 52] Same as NIC_CQE_RX_S[L4TY], but for the inner layer. */
        uint64_t lety                  : 4;  /**< [ 51: 48] Same as NIC_CQE_RX_S[L3TY], but for the inner layer. */
        uint64_t vvptr_i               : 8;  /**< [ 47: 40] Same as NIC_CQE_RX_S[VVPTR], but for the inner layer. */
        uint64_t vsptr_i               : 8;  /**< [ 39: 32] Same as NIC_CQE_RX_S[VSPTR], but for the inner layer. */
        uint64_t reserved_16_31        : 16;
        uint64_t leptr                 : 8;  /**< [ 15:  8] Same as NIC_CQE_RX_S[L3PTR], but for the inner layer. */
        uint64_t lfptr                 : 8;  /**< [  7:  0] Same as NIC_CQE_RX_S[L4PTR], but for the inner layer. */
#else /* Word 0 - Little Endian */
        uint64_t lfptr                 : 8;  /**< [  7:  0] Same as NIC_CQE_RX_S[L4PTR], but for the inner layer. */
        uint64_t leptr                 : 8;  /**< [ 15:  8] Same as NIC_CQE_RX_S[L3PTR], but for the inner layer. */
        uint64_t reserved_16_31        : 16;
        uint64_t vsptr_i               : 8;  /**< [ 39: 32] Same as NIC_CQE_RX_S[VSPTR], but for the inner layer. */
        uint64_t vvptr_i               : 8;  /**< [ 47: 40] Same as NIC_CQE_RX_S[VVPTR], but for the inner layer. */
        uint64_t lety                  : 4;  /**< [ 51: 48] Same as NIC_CQE_RX_S[L3TY], but for the inner layer. */
        uint64_t lfty                  : 4;  /**< [ 55: 52] Same as NIC_CQE_RX_S[L4TY], but for the inner layer. */
        uint64_t l2e_i                 : 1;  /**< [ 56: 56] Indicates a L2 Ethernet layer was detected on the inner layer of a tunneled
                                                                 packet. */
        uint64_t reserved_57_59        : 3;
        uint64_t vs_gone_i             : 1;  /**< [ 60: 60] Same as NIC_CQE_RX_S[VS_GONE], but for the inner layer. */
        uint64_t vs_i                  : 1;  /**< [ 61: 61] Same as NIC_CQE_RX_S[VS], but for the inner layer. */
        uint64_t vv_gone_i             : 1;  /**< [ 62: 62] Same as NIC_CQE_RX_S[VV_GONE], but for the inner layer. */
        uint64_t vv_i                  : 1;  /**< [ 63: 63] Same as NIC_CQE_RX_S[VV], but for the inner layer. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_cqe_rx2_s_s cn; */
};

/**
 * Structure nic_cqe_rx_s
 *
 * NIC CQE Receive Structure
 * Format of receive completion queue entry.
 */
union bdk_nic_cqe_rx_s
{
    uint64_t u[6];
    struct bdk_nic_cqe_rx_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cqe_type              : 4;  /**< [ 63: 60] Completion queue entry type (NIC_CQE_TYPE_E::RX, or NIC_CQE_TYPE_E::RX_SPLT). */
        uint64_t stdn_fault            : 1;  /**< [ 59: 59] STDN fault detected during the data writes to memory. */
        uint64_t reserved_58           : 1;
        uint64_t rq_qs                 : 7;  /**< [ 57: 51] Indicates the RQ's QS. */
        uint64_t rq_idx                : 3;  /**< [ 50: 48] Indicates the RQ inside the QS. */
        uint64_t reserved_36_47        : 12;
        uint64_t rss_alg               : 4;  /**< [ 35: 32] RSS algorithm used. Enumerated by NIC_RSS_ALG_E. */
        uint64_t reserved_28_31        : 4;
        uint64_t rb_cnt                : 4;  /**< [ 27: 24] Number of RB pointers in the CQ entry. Each entry is a 8 byte structure. */
        uint64_t vv                    : 1;  /**< [ 23: 23] Indicates one or more VLANs were found in the packet. Unpredictable when [ERRLEV] \<= L2. */
        uint64_t vv_gone               : 1;  /**< [ 22: 22] Indicates the first VLAN in network order was stripped from the packet data and written to
                                                                 [VLAN_TCI]. This field is zero when [VV]=0 or [VS_GONE]=1. */
        uint64_t vs                    : 1;  /**< [ 21: 21] Indicates a second VLAN was found in the packet. This field is zero when [VV]=0, and
                                                                 unpredictable when [ERRLEV] \<= L2. */
        uint64_t vs_gone               : 1;  /**< [ 20: 20] Indicates the second VLAN in network order was stripped from the packet data and written
                                                                 to [VLAN_TCI]. This field is zero when [VS]=0 or [VV_GONE]=1. */
        uint64_t l4ty                  : 4;  /**< [ 19: 16] Layer 4 type. Indicates the layer 4 header type, enumerated by
                                                                 NIC_L4TYPE_E. This field is zero unless L4 parsing sets it, and is unpredictable
                                                                 when [ERRLEV] \<= L4. */
        uint64_t l3ty                  : 4;  /**< [ 15: 12] Layer 3 type. Indicates the layer 3 header type, enumerated by
                                                                 NIC_L3TYPE_E. This field is zero unless L3 parsing sets it, and is unpredictable
                                                                 when [ERRLEV] \<= L3. */
        uint64_t l2e                   : 1;  /**< [ 11: 11] Layer 2 exists. Indicates that Ethernet layer was parsed. This field is zero when L2 is
                                                                 not parsed, and unpredictable when [ERRLEV] \<= RE. */
        uint64_t errlev                : 3;  /**< [ 10:  8] Error level. Normally zero, but when errors are detected contains the lowest protocol
                                                                 layer containing an error, and [ERROP] will indicate the precise error reason. Enumerated
                                                                 with NIC_ERRLEV_E.

                                                                 Note pseudo-code often refers to for example '[ERRLEV] \<= L3', this is a shorthand for
                                                                 'all errors at L3 and below', that is, [ERRLEV] == (RE or L2 or L3) and [ERROP] !=0, but
                                                                 is not true when [ERRLEV] == (NONE nor L4) nor when [ERROP] == 0 (no error at all). */
        uint64_t errop                 : 8;  /**< [  7:  0] Error opcode. Normally zero, but contains a (nonzero) exception opcode enumerated by
                                                                 NIC_ERROP_E when [ERRLEV] is nonzero. */
#else /* Word 0 - Little Endian */
        uint64_t errop                 : 8;  /**< [  7:  0] Error opcode. Normally zero, but contains a (nonzero) exception opcode enumerated by
                                                                 NIC_ERROP_E when [ERRLEV] is nonzero. */
        uint64_t errlev                : 3;  /**< [ 10:  8] Error level. Normally zero, but when errors are detected contains the lowest protocol
                                                                 layer containing an error, and [ERROP] will indicate the precise error reason. Enumerated
                                                                 with NIC_ERRLEV_E.

                                                                 Note pseudo-code often refers to for example '[ERRLEV] \<= L3', this is a shorthand for
                                                                 'all errors at L3 and below', that is, [ERRLEV] == (RE or L2 or L3) and [ERROP] !=0, but
                                                                 is not true when [ERRLEV] == (NONE nor L4) nor when [ERROP] == 0 (no error at all). */
        uint64_t l2e                   : 1;  /**< [ 11: 11] Layer 2 exists. Indicates that Ethernet layer was parsed. This field is zero when L2 is
                                                                 not parsed, and unpredictable when [ERRLEV] \<= RE. */
        uint64_t l3ty                  : 4;  /**< [ 15: 12] Layer 3 type. Indicates the layer 3 header type, enumerated by
                                                                 NIC_L3TYPE_E. This field is zero unless L3 parsing sets it, and is unpredictable
                                                                 when [ERRLEV] \<= L3. */
        uint64_t l4ty                  : 4;  /**< [ 19: 16] Layer 4 type. Indicates the layer 4 header type, enumerated by
                                                                 NIC_L4TYPE_E. This field is zero unless L4 parsing sets it, and is unpredictable
                                                                 when [ERRLEV] \<= L4. */
        uint64_t vs_gone               : 1;  /**< [ 20: 20] Indicates the second VLAN in network order was stripped from the packet data and written
                                                                 to [VLAN_TCI]. This field is zero when [VS]=0 or [VV_GONE]=1. */
        uint64_t vs                    : 1;  /**< [ 21: 21] Indicates a second VLAN was found in the packet. This field is zero when [VV]=0, and
                                                                 unpredictable when [ERRLEV] \<= L2. */
        uint64_t vv_gone               : 1;  /**< [ 22: 22] Indicates the first VLAN in network order was stripped from the packet data and written to
                                                                 [VLAN_TCI]. This field is zero when [VV]=0 or [VS_GONE]=1. */
        uint64_t vv                    : 1;  /**< [ 23: 23] Indicates one or more VLANs were found in the packet. Unpredictable when [ERRLEV] \<= L2. */
        uint64_t rb_cnt                : 4;  /**< [ 27: 24] Number of RB pointers in the CQ entry. Each entry is a 8 byte structure. */
        uint64_t reserved_28_31        : 4;
        uint64_t rss_alg               : 4;  /**< [ 35: 32] RSS algorithm used. Enumerated by NIC_RSS_ALG_E. */
        uint64_t reserved_36_47        : 12;
        uint64_t rq_idx                : 3;  /**< [ 50: 48] Indicates the RQ inside the QS. */
        uint64_t rq_qs                 : 7;  /**< [ 57: 51] Indicates the RQ's QS. */
        uint64_t reserved_58           : 1;
        uint64_t stdn_fault            : 1;  /**< [ 59: 59] STDN fault detected during the data writes to memory. */
        uint64_t cqe_type              : 4;  /**< [ 63: 60] Completion queue entry type (NIC_CQE_TYPE_E::RX, or NIC_CQE_TYPE_E::RX_SPLT). */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t len                   : 16; /**< [127:112] The number of bytes in the packet and written to the CQE/RB. Bytes stripped (VLAN etc) if
                                                                 any are not included. */
        uint64_t l2ptr                 : 8;  /**< [111:104] Pointer to the first byte of L2 relative to the first byte of packet data written to
                                                                 memory. Unpredictable when [ERRLEV] \<= RE. */
        uint64_t l3ptr                 : 8;  /**< [103: 96] Pointer to the first byte of L3 relative to the first byte of packet data written to
                                                                 memory. Unpredictable when [ERRLEV] \<= L2. */
        uint64_t l4ptr                 : 8;  /**< [ 95: 88] Pointer to the first byte of L4 relative to the first byte of packet data written to
                                                                 memory. Unpredictable when [ERRLEV] \<= L3. */
        uint64_t size_cqd              : 8;  /**< [ 87: 80] Size of CQ data. Number of packet bytes written to the CQ, either due to
                                                                 NIC_QS()_RQ_GEN_CFG[CQ_HDR_COPY] or the packet being smaller than
                                                                 NIC_QS()_RQ_GEN_CFG[CQ_PKT_SIZE]. */
        uint64_t apad                  : 3;  /**< [ 79: 77] Number of alignment bytes added before data in CQE and RB. */
        uint64_t reserved_76           : 1;
        uint64_t chan                  : 12; /**< [ 75: 64] Logical channel the packet arrived from, enumerated by NIC_CHAN_E. */
#else /* Word 1 - Little Endian */
        uint64_t chan                  : 12; /**< [ 75: 64] Logical channel the packet arrived from, enumerated by NIC_CHAN_E. */
        uint64_t reserved_76           : 1;
        uint64_t apad                  : 3;  /**< [ 79: 77] Number of alignment bytes added before data in CQE and RB. */
        uint64_t size_cqd              : 8;  /**< [ 87: 80] Size of CQ data. Number of packet bytes written to the CQ, either due to
                                                                 NIC_QS()_RQ_GEN_CFG[CQ_HDR_COPY] or the packet being smaller than
                                                                 NIC_QS()_RQ_GEN_CFG[CQ_PKT_SIZE]. */
        uint64_t l4ptr                 : 8;  /**< [ 95: 88] Pointer to the first byte of L4 relative to the first byte of packet data written to
                                                                 memory. Unpredictable when [ERRLEV] \<= L3. */
        uint64_t l3ptr                 : 8;  /**< [103: 96] Pointer to the first byte of L3 relative to the first byte of packet data written to
                                                                 memory. Unpredictable when [ERRLEV] \<= L2. */
        uint64_t l2ptr                 : 8;  /**< [111:104] Pointer to the first byte of L2 relative to the first byte of packet data written to
                                                                 memory. Unpredictable when [ERRLEV] \<= RE. */
        uint64_t len                   : 16; /**< [127:112] The number of bytes in the packet and written to the CQE/RB. Bytes stripped (VLAN etc) if
                                                                 any are not included. */
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t rss_tag               : 32; /**< [191:160] Computed RSS tag value. This field is zero when [RSS_ALG] == NIC_RSS_ALG_E::NONE (0). */
        uint64_t vlan_tci              : 16; /**< [159:144] Stripped VLAN tag control information. Unpredictable when [VV_GONE] and [VS_GONE] are
                                                                 clear.  Field is stored in LE byte order.

                                                                 Internal:
                                                                 Hardware zeros when unpredictable, though software must not rely on this. */
        uint64_t vvptr                 : 8;  /**< [143:136] Pointer to first VLAN. If [VV] set, [VV_GONE] clear, the first byte of the first VLAN's
                                                                 Ethertype. If [VV] set, [VV_GONE] set, the first byte after the stripped VLAN.
                                                                 Unpredictable if [VV] clear.

                                                                 Internal:
                                                                 Hardware zeros when unpredictable, though software
                                                                 must not rely on this. */
        uint64_t vsptr                 : 8;  /**< [135:128] Pointer to second VLAN. If [VS] set, [VS_GONE] clear, the first byte of the second VLAN's
                                                                 Ethertype. If [VS] set, [VS_GONE] set, the first byte after the stripped VLAN.
                                                                 Unpredictable if [VS] clear.

                                                                 Internal:
                                                                 Hardware zeros when unpredictable, though software
                                                                 must not rely on this. */
#else /* Word 2 - Little Endian */
        uint64_t vsptr                 : 8;  /**< [135:128] Pointer to second VLAN. If [VS] set, [VS_GONE] clear, the first byte of the second VLAN's
                                                                 Ethertype. If [VS] set, [VS_GONE] set, the first byte after the stripped VLAN.
                                                                 Unpredictable if [VS] clear.

                                                                 Internal:
                                                                 Hardware zeros when unpredictable, though software
                                                                 must not rely on this. */
        uint64_t vvptr                 : 8;  /**< [143:136] Pointer to first VLAN. If [VV] set, [VV_GONE] clear, the first byte of the first VLAN's
                                                                 Ethertype. If [VV] set, [VV_GONE] set, the first byte after the stripped VLAN.
                                                                 Unpredictable if [VV] clear.

                                                                 Internal:
                                                                 Hardware zeros when unpredictable, though software
                                                                 must not rely on this. */
        uint64_t vlan_tci              : 16; /**< [159:144] Stripped VLAN tag control information. Unpredictable when [VV_GONE] and [VS_GONE] are
                                                                 clear.  Field is stored in LE byte order.

                                                                 Internal:
                                                                 Hardware zeros when unpredictable, though software must not rely on this. */
        uint64_t rss_tag               : 32; /**< [191:160] Computed RSS tag value. This field is zero when [RSS_ALG] == NIC_RSS_ALG_E::NONE (0). */
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t rbsz3                 : 16; /**< [255:240] Size of RB 6. */
        uint64_t rbsz2                 : 16; /**< [239:224] Size of RB 4. */
        uint64_t rbsz1                 : 16; /**< [223:208] Size of RB 2. */
        uint64_t rbsz0                 : 16; /**< [207:192] Size of RB 0. Number of bytes written to the first RB, or hardware 0x0 and software
                                                                 reserved if none written to this RB.

                                                                 Internal:
                                                                 Fields are laid out so that on a litte-
                                                                 endian machine a uint16_t array can hit all 12 RBSZs. */
#else /* Word 3 - Little Endian */
        uint64_t rbsz0                 : 16; /**< [207:192] Size of RB 0. Number of bytes written to the first RB, or hardware 0x0 and software
                                                                 reserved if none written to this RB.

                                                                 Internal:
                                                                 Fields are laid out so that on a litte-
                                                                 endian machine a uint16_t array can hit all 12 RBSZs. */
        uint64_t rbsz1                 : 16; /**< [223:208] Size of RB 2. */
        uint64_t rbsz2                 : 16; /**< [239:224] Size of RB 4. */
        uint64_t rbsz3                 : 16; /**< [255:240] Size of RB 6. */
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t rbsz7                 : 16; /**< [319:304] Size of RB 6. */
        uint64_t rbsz6                 : 16; /**< [303:288] Size of RB 4. */
        uint64_t rbsz5                 : 16; /**< [287:272] Size of RB 2. */
        uint64_t rbsz4                 : 16; /**< [271:256] Size of RB 0. Number of bytes written to the first RB, or 0x0 if none written to this RB. */
#else /* Word 4 - Little Endian */
        uint64_t rbsz4                 : 16; /**< [271:256] Size of RB 0. Number of bytes written to the first RB, or 0x0 if none written to this RB. */
        uint64_t rbsz5                 : 16; /**< [287:272] Size of RB 2. */
        uint64_t rbsz6                 : 16; /**< [303:288] Size of RB 4. */
        uint64_t rbsz7                 : 16; /**< [319:304] Size of RB 6. */
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t rbsz11                : 16; /**< [383:368] Size of RB 6. */
        uint64_t rbsz10                : 16; /**< [367:352] Size of RB 4. */
        uint64_t rbsz9                 : 16; /**< [351:336] Size of RB 2. */
        uint64_t rbsz8                 : 16; /**< [335:320] Size of RB 0. Number of bytes written to the first RB, or 0x0 if none written to this RB. */
#else /* Word 5 - Little Endian */
        uint64_t rbsz8                 : 16; /**< [335:320] Size of RB 0. Number of bytes written to the first RB, or 0x0 if none written to this RB. */
        uint64_t rbsz9                 : 16; /**< [351:336] Size of RB 2. */
        uint64_t rbsz10                : 16; /**< [367:352] Size of RB 4. */
        uint64_t rbsz11                : 16; /**< [383:368] Size of RB 6. */
#endif /* Word 5 - End */
    } s;
    /* struct bdk_nic_cqe_rx_s_s cn; */
};

/**
 * Structure nic_cqe_send_s
 *
 * NIC CQE Send Structure
 * Format of send completion queue entry.
 */
union bdk_nic_cqe_send_s
{
    uint64_t u[2];
    struct bdk_nic_cqe_send_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cqe_type              : 4;  /**< [ 63: 60] Completion queue entry type (NIC_CQE_TYPE_E::SEND or NIC_CQE_TYPE_E::SEND_PTP). */
        uint64_t reserved_56_59        : 4;
        uint64_t sqe_ptr               : 16; /**< [ 55: 40] SQ entry pointer\<19:4\>. Address bits \<3:0\> are always 0. */
        uint64_t reserved_26_39        : 14;
        uint64_t sq_qs                 : 7;  /**< [ 25: 19] Indicates the send queue's QS. */
        uint64_t sq_idx                : 3;  /**< [ 18: 16] Indicates the send queue's index inside the QS. */
        uint64_t reserved_8_15         : 8;
        uint64_t send_status           : 8;  /**< [  7:  0] Send completion status enumerated by NIC_CQE_SEND_STATUS_E. */
#else /* Word 0 - Little Endian */
        uint64_t send_status           : 8;  /**< [  7:  0] Send completion status enumerated by NIC_CQE_SEND_STATUS_E. */
        uint64_t reserved_8_15         : 8;
        uint64_t sq_idx                : 3;  /**< [ 18: 16] Indicates the send queue's index inside the QS. */
        uint64_t sq_qs                 : 7;  /**< [ 25: 19] Indicates the send queue's QS. */
        uint64_t reserved_26_39        : 14;
        uint64_t sqe_ptr               : 16; /**< [ 55: 40] SQ entry pointer\<19:4\>. Address bits \<3:0\> are always 0. */
        uint64_t reserved_56_59        : 4;
        uint64_t cqe_type              : 4;  /**< [ 63: 60] Completion queue entry type (NIC_CQE_TYPE_E::SEND or NIC_CQE_TYPE_E::SEND_PTP). */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t ptp_timestamp         : 64; /**< [127: 64] PTP timestamp value. Valid when [CQE_TYPE]=NIC_CQE_TYPE_E::SEND_PTP. */
#else /* Word 1 - Little Endian */
        uint64_t ptp_timestamp         : 64; /**< [127: 64] PTP timestamp value. Valid when [CQE_TYPE]=NIC_CQE_TYPE_E::SEND_PTP. */
#endif /* Word 1 - End */
    } s;
    struct bdk_nic_cqe_send_s_cn
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cqe_type              : 4;  /**< [ 63: 60] Completion queue entry type (NIC_CQE_TYPE_E::SEND or NIC_CQE_TYPE_E::SEND_PTP). */
        uint64_t reserved_56_59        : 4;
        uint64_t sqe_ptr               : 16; /**< [ 55: 40] SQ entry pointer\<19:4\>. Address bits \<3:0\> are always 0. */
        uint64_t reserved_36_39        : 4;
        uint64_t reserved_26_35        : 10;
        uint64_t sq_qs                 : 7;  /**< [ 25: 19] Indicates the send queue's QS. */
        uint64_t sq_idx                : 3;  /**< [ 18: 16] Indicates the send queue's index inside the QS. */
        uint64_t reserved_8_15         : 8;
        uint64_t send_status           : 8;  /**< [  7:  0] Send completion status enumerated by NIC_CQE_SEND_STATUS_E. */
#else /* Word 0 - Little Endian */
        uint64_t send_status           : 8;  /**< [  7:  0] Send completion status enumerated by NIC_CQE_SEND_STATUS_E. */
        uint64_t reserved_8_15         : 8;
        uint64_t sq_idx                : 3;  /**< [ 18: 16] Indicates the send queue's index inside the QS. */
        uint64_t sq_qs                 : 7;  /**< [ 25: 19] Indicates the send queue's QS. */
        uint64_t reserved_26_35        : 10;
        uint64_t reserved_36_39        : 4;
        uint64_t sqe_ptr               : 16; /**< [ 55: 40] SQ entry pointer\<19:4\>. Address bits \<3:0\> are always 0. */
        uint64_t reserved_56_59        : 4;
        uint64_t cqe_type              : 4;  /**< [ 63: 60] Completion queue entry type (NIC_CQE_TYPE_E::SEND or NIC_CQE_TYPE_E::SEND_PTP). */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t ptp_timestamp         : 64; /**< [127: 64] PTP timestamp value. Valid when [CQE_TYPE]=NIC_CQE_TYPE_E::SEND_PTP. */
#else /* Word 1 - Little Endian */
        uint64_t ptp_timestamp         : 64; /**< [127: 64] PTP timestamp value. Valid when [CQE_TYPE]=NIC_CQE_TYPE_E::SEND_PTP. */
#endif /* Word 1 - End */
    } cn;
};

/**
 * Structure nic_rbdr_entry_s
 *
 * NIC Receive-Buffer Descriptor-Ring Entry Structure
 * Receive buffer descriptor ring entry.
 */
union bdk_nic_rbdr_entry_s
{
    uint64_t u;
    struct bdk_nic_rbdr_entry_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 42; /**< [ 48:  7] Starting IOVA of receive data buffer. */
        uint64_t reserved_0_6          : 7;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_6          : 7;
        uint64_t addr                  : 42; /**< [ 48:  7] Starting IOVA of receive data buffer. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_rbdr_entry_s_s cn; */
};

/**
 * Structure nic_send_crc_s
 *
 * NIC Send-CRC Subdescriptor Structure
 * The Send CRC subdescriptor specifies a CRC calculation be performed during transmission. See
 * Custom Checksum.
 * There may be up to two NIC_SEND_CRC_Ss per packet send descriptor. NIC_SEND_CRC_S constraints:
 * NIC_SEND_CRC_S subdescriptors must precede all NIC_SEND_GATHER_S, NIC_SEND_IMM_S and
 * NIC_SEND_MEM_S subdescriptors in the send descriptor.
 *
 * NIC_SEND_CRC_S subdescriptors must follow the same order as their checksum and insert regions
 * in the packet, i.e. the checksum and insert regions of a NIC_SEND_CRC_S must come after the
 * checksum and insert regions of a preceding NIC_SEND_CRC_S.
 *
 * If NIC_SEND_HDR_S[CKL3] is set, the bytes covered or inserted by each individual
 * NIC_SEND_CRC_S must entirely reside within the L3 payload, i.e. they must follow the IPv4
 * header bytes (including any options).
 * the bytes covered or inserted by the CRC must not overlap the IPv4 header bytes (including any
 * options). The IPv4 header bytes (and options) start at byte NIC_SEND_HDR_S[L3PTR] in the
 * packet in this case.
 *
 * If NIC_SEND_HDR_S[CKL4] is nonzero, the bytes covered or inserted by each individual
 * NIC_SEND_CRC_S CRC must entirely reside within the L4 payload. The L4 (TCP/UDP) header
 * starts at byte NIC_SEND_HDR_S[L4PTR] in the packet in this case, and the L4 payload follows
 * the L4 header. In this case, the NIC will appear to calculate the L4 checksum last, after it
 * has completed all NIC_SEND_CRC_S CRCs.
 */
union bdk_nic_send_crc_s
{
    uint64_t u[2];
    struct bdk_nic_send_crc_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t subdc                 : 4;  /**< [ 63: 60] Subdescriptor code. Indicates send CRC. Enumerated by NIC_SEND_SUBDC_E::CRC. */
        uint64_t alg                   : 2;  /**< [ 59: 58] CRC algorithm. See NIC_SEND_CRCALG_E. */
        uint64_t reserved_48_57        : 10;
        uint64_t insert                : 16; /**< [ 47: 32] Byte position relative to the first packet byte at which to insert the first byte of the
                                                                 calculated CRC. NIC does not allocate bytes as it inserts the CRC result into the packet,
                                                                 it overwrites four pre-supplied packet bytes using NIC_SEND_GATHER_S or NIC_SEND_IMM_S.
                                                                 The insertion point may not be within the start/size region of another NIC_SEND_CRC_S. */
        uint64_t start                 : 16; /**< [ 31: 16] Byte position relative to the first packet byte at which to start the checksum. */
        uint64_t size                  : 16; /**< [ 15:  0] Length of checksum region, must not be zero. The region is contiguous in packet bytes
                                                                 [START] through [START]+[SIZE]-1. Note that these covered reconstructed bytes need not be
                                                                 contiguous in L2/DRAM -- they can straddle any number of NIC_SEND_GATHER_S subdescriptors. */
#else /* Word 0 - Little Endian */
        uint64_t size                  : 16; /**< [ 15:  0] Length of checksum region, must not be zero. The region is contiguous in packet bytes
                                                                 [START] through [START]+[SIZE]-1. Note that these covered reconstructed bytes need not be
                                                                 contiguous in L2/DRAM -- they can straddle any number of NIC_SEND_GATHER_S subdescriptors. */
        uint64_t start                 : 16; /**< [ 31: 16] Byte position relative to the first packet byte at which to start the checksum. */
        uint64_t insert                : 16; /**< [ 47: 32] Byte position relative to the first packet byte at which to insert the first byte of the
                                                                 calculated CRC. NIC does not allocate bytes as it inserts the CRC result into the packet,
                                                                 it overwrites four pre-supplied packet bytes using NIC_SEND_GATHER_S or NIC_SEND_IMM_S.
                                                                 The insertion point may not be within the start/size region of another NIC_SEND_CRC_S. */
        uint64_t reserved_48_57        : 10;
        uint64_t alg                   : 2;  /**< [ 59: 58] CRC algorithm. See NIC_SEND_CRCALG_E. */
        uint64_t subdc                 : 4;  /**< [ 63: 60] Subdescriptor code. Indicates send CRC. Enumerated by NIC_SEND_SUBDC_E::CRC. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_96_127       : 32;
        uint64_t iv                    : 32; /**< [ 95: 64] Initial value of the checksum, valid only if it is nonzero. If [ALG] = CKSUM, then only
                                                                 bits \<15:0\> in big-endian format are valid. */
#else /* Word 1 - Little Endian */
        uint64_t iv                    : 32; /**< [ 95: 64] Initial value of the checksum, valid only if it is nonzero. If [ALG] = CKSUM, then only
                                                                 bits \<15:0\> in big-endian format are valid. */
        uint64_t reserved_96_127       : 32;
#endif /* Word 1 - End */
    } s;
    /* struct bdk_nic_send_crc_s_s cn; */
};

/**
 * Structure nic_send_gather_s
 *
 * NIC Send-Gather Subdescriptor Structure
 * The send gather subdescriptor requests a contiguous segment of bytes be transmitted. See Send
 * Gather. There may be multiple NIC_SEND_GATHER_Ss in each NIC send descriptor. A
 * NIC_SEND_GATHER_S is ignored in a NIC send descriptor if the sum of all prior
 * NIC_SEND_GATHER_S[SIZE]s and NIC_SEND_IMM_S[SIZE]s meets or exceeds NIC_SEND_HDR_S[TOTAL].
 */
union bdk_nic_send_gather_s
{
    uint64_t u[2];
    struct bdk_nic_send_gather_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t subdc                 : 4;  /**< [ 63: 60] Subdescriptor code. Indicates send gather. Enumerated by NIC_SEND_SUBDC_E::GATHER. */
        uint64_t ld_type               : 2;  /**< [ 59: 58] Specifies load transaction type to use for reading segment bytes. Enumerated by
                                                                 NIC_SEND_LD_TYPE_E. */
        uint64_t reserved_16_57        : 42;
        uint64_t size                  : 16; /**< [ 15:  0] Size of segment, in bytes. [SIZE] must be nonzero, else the subdescriptor is ignored. */
#else /* Word 0 - Little Endian */
        uint64_t size                  : 16; /**< [ 15:  0] Size of segment, in bytes. [SIZE] must be nonzero, else the subdescriptor is ignored. */
        uint64_t reserved_16_57        : 42;
        uint64_t ld_type               : 2;  /**< [ 59: 58] Specifies load transaction type to use for reading segment bytes. Enumerated by
                                                                 NIC_SEND_LD_TYPE_E. */
        uint64_t subdc                 : 4;  /**< [ 63: 60] Subdescriptor code. Indicates send gather. Enumerated by NIC_SEND_SUBDC_E::GATHER. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_113_127      : 15;
        uint64_t addr                  : 49; /**< [112: 64] Address. IOVA of the first byte of packet data in the buffer. */
#else /* Word 1 - Little Endian */
        uint64_t addr                  : 49; /**< [112: 64] Address. IOVA of the first byte of packet data in the buffer. */
        uint64_t reserved_113_127      : 15;
#endif /* Word 1 - End */
    } s;
    /* struct bdk_nic_send_gather_s_s cn; */
};

/**
 * Structure nic_send_hdr_s
 *
 * NIC Send-Header Subdescriptor Structure
 * The send header is the first subdescriptor of every send descriptor.
 */
union bdk_nic_send_hdr_s
{
    uint64_t u[2];
    struct bdk_nic_send_hdr_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t subdc                 : 4;  /**< [ 63: 60] Subdescriptor code. Indicates send header. Enumerated by NIC_SEND_SUBDC_E::HDR. */
        uint64_t tso                   : 1;  /**< [ 59: 59] TCP segmentation offload. Ignored and treated as clear when NIC_PF_TSO_CFG[ENABLE] is
                                                                 clear. When set along with NIC_PF_TSO_CFG[ENABLE], the send descriptor is for a TCP
                                                                 segmentation
                                                                 operation to send one or more packets of a TCP flow, and the related [TSO_*] fields are
                                                                 valid.
                                                                 TSO can be tunneled or non-tunneled as follows:
                                                                 * If [LFPTR] is nonzero, TSO is tunneled. [LEPTR] and [LFPTR] must point to the inner IP
                                                                 and TCP headers, respectively, [L3PTR] must point to the outer IP, and [L4PTR] just point
                                                                 to the tunneling header (e.g. UDP or GRE).
                                                                 * If [LFPTR] is zero, TSO is non-tunneled. [L3PTR] and [L4PTR] must point to the IP and
                                                                 TCP headers, respectively. */
        uint64_t pnc                   : 1;  /**< [ 58: 58] Post normal completion. If set, a CQE is created with NIC_CQE_SEND_S[CQE_TYPE] =
                                                                 NIC_CQE_TYPE_E::SEND when the send descriptor's operation completes normally with no
                                                                 error. If [TSO] is set, a CQE is created when the send operation completes for all TSO
                                                                 segments.

                                                                 If clear, no CQE is added on normal completion.

                                                                 Note that a CQE is always added if the send operation terminates with an error after the
                                                                 packet is scheduled; except for NIC_CQE_SEND_STATUS_E::LOCK_VIOL, where a CQE is
                                                                 determined  by NIC_PF_QS()_CFG[LOCK_VIOL_CQE_ENA].

                                                                 NIC will not add a CQE for this send descriptor until after it has completed all L2/DRAM
                                                                 fetches that service all prior NIC_SEND_GATHER_S subdescriptors, and it has fetched all
                                                                 subdescriptors in the send descriptor. If NIC_SEND_MEM_S[WMEM]=1, NIC also will not post
                                                                 the CQE until all NIC_SEND_MEM_S subdescriptors in the descriptor complete and commit. */
        uint64_t ds                    : 1;  /**< [ 57: 57] Don't send. If set, NIC hardware will not send the packet bytes to the interface; however
                                                                 it will still perform any NIC_SEND_MEM_S operations. */
        uint64_t tstmp                 : 1;  /**< [ 56: 56] PTP timestamp. When this is set, [DS] is clear, [TSO] is clear and
                                                                 NIC_PF_QS()_CFG[SEND_TSTMP_ENA]
                                                                 is set, a CQE of NIC_CQE_SEND_S[CQE_TYPE] = NIC_CQE_TYPE_E::SEND_PTP is posted when the
                                                                 packet is transmitted by the targeted Ethernet port. NIC_CQE_SEND_S[PTP_TIMESTAMP] is set
                                                                 to the packet's timestamp. The posted NIC_CQE_TYPE_E::SEND_PTP CQ entry is asynchronous
                                                                 relative to NIC_CQE_TYPE_E::SEND CQ entries in the same CQ.

                                                                 If this bit is set along with [PNC], two entries are posted to the CQ. The first CQ entry
                                                                 is posted with NIC_CQE_SEND_S[CQE_TYPE] = NIC_CQE_TYPE_E::SEND when the send descriptor's
                                                                 operation is done as described above. The second CQ entry is posted with
                                                                 NIC_CQE_SEND_S[CQE_TYPE] = NIC_CQE_TYPE_E::SEND_PTP when the packet's timestamp is
                                                                 captured or times out.

                                                                 Only one timestamp operation may be outstanding at once for a given Ethernet port.
                                                                 Ignored when [DS] is set, [TSO] is set or NIC_PF_QS()_CFG[SEND_TSTMP_ENA] is clear. */
        uint64_t subdcnt               : 8;  /**< [ 55: 48] Subdescriptor count. Number of 128-bit subdescriptors following the send header
                                                                 subdescriptor, including immediate data. Must be between 1 and 255, thus the maximum send
                                                                 descriptor size is 256 subdescriptors (4KB). */
        uint64_t ckl4                  : 2;  /**< [ 47: 46] Checksum L4, enumerated by NIC_SEND_CKL4_E. If nonzero (not NONE):
                                                                 * NIC hardware calculates the Layer 4 TCP/UDP checksum for the packet and inserts it
                                                                 into the packet, as described in L4 Checksum.
                                                                 * [L4PTR] selects the first byte of the L4 header, and [L3PTR] must indicate the location
                                                                 of the immediately proceeding and adjacent L3 header.
                                                                 * The L4 length field must not require more than [TOTAL] bytes in the packet.
                                                                 * When NIC_SEND_CRC_S are present, the bytes covered or inserted by NIC_SEND_CRC_S must
                                                                 all reside in the L4 payload. Conceptually, NIC processes NIC_SEND_CRC_S before L4
                                                                 checksums when both are present. */
        uint64_t ckl3                  : 1;  /**< [ 45: 45] Checksum L3. If set, NIC hardware calculates the IPv4 header checksum and inserts it into
                                                                 the packet, as described in L4 checksum. When set, [L3PTR] selects the location of the
                                                                 first byte of the L3 header and no L3 header bytes selected by [L3PTR] can overlap with
                                                                 any bytes covered or inserted by NIC_SEND_CRC_S CRCs. When [CKL3] is set, [L3PTR] must
                                                                 point to a valid IPv4 header. */
        uint64_t cklf                  : 2;  /**< [ 44: 43] Inner checksum L4, enumerated by NIC_SEND_CKL4_E. Similar to [CKL4] but for inner L4. */
        uint64_t ckle                  : 1;  /**< [ 42: 42] Inner checksum L3. Similar to [CKL3] but for inner IP. */
        uint64_t reserved_40_41        : 2;
        uint64_t l4ptr                 : 8;  /**< [ 39: 32] Layer 4 offset. Specifies the location of the first byte of the TCP/UDP header for L4
                                                                 checksumming and/or TSO.
                                                                 The Layer 4 header must be exactly [L4PTR] bytes from the beginning of the
                                                                 packet. Software might populate this field for forwarded packets from a computation based
                                                                 off NIC_CQE_RX_S[L4PTR], which is the IP location computed by NIC when the packet is
                                                                 parsed. When [L4PTR] is used for any of [CKL4], [TSO] calculations/modifications, no L4
                                                                 header bytes indicated by [L4PTR] can overlap with any bytes covered by or inserted by
                                                                 NIC_SEND_CRC_S CRCs (but the subsequent L4 payload bytes can overlap with the
                                                                 NIC_SEND_CRC_S CRC bytes). */
        uint64_t l3ptr                 : 8;  /**< [ 31: 24] Layer 3 IP offset. Specifies the location of the first byte of the IP packet for
                                                                 L3 checksum, L4 checksum and/or TSO. (See [CKL3], [CKL4], [TSO].) The IP packet
                                                                 must be exactly [L3PTR] bytes from the beginning of the packet. Software might
                                                                 populate this field for forwarded packets from a computation based off
                                                                 NIC_CQE_RX_S[L3PTR], which is the IP location computed by NIC when the packet is
                                                                 parsed. When [L3PTR] is used for any of [CKL3], [CKL4], [TSO]
                                                                 calculations/modifications, then no L3 nor L2 header bytes indicated by [L3PTR]
                                                                 can overlap with any bytes covered by or inserted by NIC_SEND_CRC_S CRCs. */
        uint64_t reserved_20_23        : 4;
        uint64_t total                 : 20; /**< [ 19:  0] Total byte count. Must be greater than 0. For a non-TSO descriptor, the total number of
                                                                 bytes to
                                                                 send, including zero pad (if any), and should not exceed the lesser of 9212 (9216 minus 4
                                                                 byte FCS) or NIC_PF_LMAC()_CFG2[MAX_PKT_SIZE].

                                                                 For a TSO send descriptor, the total TCP payload size plus the size of the first packet's
                                                                 L2, L3 and
                                                                 L4 headers. In other words, the total TCP data payload size is [TOTAL] - [TSO_SB].

                                                                 [TOTAL] does not include any of the outside FCS bytes that BGX may append to the
                                                                 packet(s). NIC zero pads the packet when [TOTAL] is larger than the sum of all
                                                                 NIC_SEND_GATHER_S[SIZE]s and NIC_SEND_IMM_S[SIZE]s in the descriptor, or when the packet
                                                                 is less than the minimum size for the interface. */
#else /* Word 0 - Little Endian */
        uint64_t total                 : 20; /**< [ 19:  0] Total byte count. Must be greater than 0. For a non-TSO descriptor, the total number of
                                                                 bytes to
                                                                 send, including zero pad (if any), and should not exceed the lesser of 9212 (9216 minus 4
                                                                 byte FCS) or NIC_PF_LMAC()_CFG2[MAX_PKT_SIZE].

                                                                 For a TSO send descriptor, the total TCP payload size plus the size of the first packet's
                                                                 L2, L3 and
                                                                 L4 headers. In other words, the total TCP data payload size is [TOTAL] - [TSO_SB].

                                                                 [TOTAL] does not include any of the outside FCS bytes that BGX may append to the
                                                                 packet(s). NIC zero pads the packet when [TOTAL] is larger than the sum of all
                                                                 NIC_SEND_GATHER_S[SIZE]s and NIC_SEND_IMM_S[SIZE]s in the descriptor, or when the packet
                                                                 is less than the minimum size for the interface. */
        uint64_t reserved_20_23        : 4;
        uint64_t l3ptr                 : 8;  /**< [ 31: 24] Layer 3 IP offset. Specifies the location of the first byte of the IP packet for
                                                                 L3 checksum, L4 checksum and/or TSO. (See [CKL3], [CKL4], [TSO].) The IP packet
                                                                 must be exactly [L3PTR] bytes from the beginning of the packet. Software might
                                                                 populate this field for forwarded packets from a computation based off
                                                                 NIC_CQE_RX_S[L3PTR], which is the IP location computed by NIC when the packet is
                                                                 parsed. When [L3PTR] is used for any of [CKL3], [CKL4], [TSO]
                                                                 calculations/modifications, then no L3 nor L2 header bytes indicated by [L3PTR]
                                                                 can overlap with any bytes covered by or inserted by NIC_SEND_CRC_S CRCs. */
        uint64_t l4ptr                 : 8;  /**< [ 39: 32] Layer 4 offset. Specifies the location of the first byte of the TCP/UDP header for L4
                                                                 checksumming and/or TSO.
                                                                 The Layer 4 header must be exactly [L4PTR] bytes from the beginning of the
                                                                 packet. Software might populate this field for forwarded packets from a computation based
                                                                 off NIC_CQE_RX_S[L4PTR], which is the IP location computed by NIC when the packet is
                                                                 parsed. When [L4PTR] is used for any of [CKL4], [TSO] calculations/modifications, no L4
                                                                 header bytes indicated by [L4PTR] can overlap with any bytes covered by or inserted by
                                                                 NIC_SEND_CRC_S CRCs (but the subsequent L4 payload bytes can overlap with the
                                                                 NIC_SEND_CRC_S CRC bytes). */
        uint64_t reserved_40_41        : 2;
        uint64_t ckle                  : 1;  /**< [ 42: 42] Inner checksum L3. Similar to [CKL3] but for inner IP. */
        uint64_t cklf                  : 2;  /**< [ 44: 43] Inner checksum L4, enumerated by NIC_SEND_CKL4_E. Similar to [CKL4] but for inner L4. */
        uint64_t ckl3                  : 1;  /**< [ 45: 45] Checksum L3. If set, NIC hardware calculates the IPv4 header checksum and inserts it into
                                                                 the packet, as described in L4 checksum. When set, [L3PTR] selects the location of the
                                                                 first byte of the L3 header and no L3 header bytes selected by [L3PTR] can overlap with
                                                                 any bytes covered or inserted by NIC_SEND_CRC_S CRCs. When [CKL3] is set, [L3PTR] must
                                                                 point to a valid IPv4 header. */
        uint64_t ckl4                  : 2;  /**< [ 47: 46] Checksum L4, enumerated by NIC_SEND_CKL4_E. If nonzero (not NONE):
                                                                 * NIC hardware calculates the Layer 4 TCP/UDP checksum for the packet and inserts it
                                                                 into the packet, as described in L4 Checksum.
                                                                 * [L4PTR] selects the first byte of the L4 header, and [L3PTR] must indicate the location
                                                                 of the immediately proceeding and adjacent L3 header.
                                                                 * The L4 length field must not require more than [TOTAL] bytes in the packet.
                                                                 * When NIC_SEND_CRC_S are present, the bytes covered or inserted by NIC_SEND_CRC_S must
                                                                 all reside in the L4 payload. Conceptually, NIC processes NIC_SEND_CRC_S before L4
                                                                 checksums when both are present. */
        uint64_t subdcnt               : 8;  /**< [ 55: 48] Subdescriptor count. Number of 128-bit subdescriptors following the send header
                                                                 subdescriptor, including immediate data. Must be between 1 and 255, thus the maximum send
                                                                 descriptor size is 256 subdescriptors (4KB). */
        uint64_t tstmp                 : 1;  /**< [ 56: 56] PTP timestamp. When this is set, [DS] is clear, [TSO] is clear and
                                                                 NIC_PF_QS()_CFG[SEND_TSTMP_ENA]
                                                                 is set, a CQE of NIC_CQE_SEND_S[CQE_TYPE] = NIC_CQE_TYPE_E::SEND_PTP is posted when the
                                                                 packet is transmitted by the targeted Ethernet port. NIC_CQE_SEND_S[PTP_TIMESTAMP] is set
                                                                 to the packet's timestamp. The posted NIC_CQE_TYPE_E::SEND_PTP CQ entry is asynchronous
                                                                 relative to NIC_CQE_TYPE_E::SEND CQ entries in the same CQ.

                                                                 If this bit is set along with [PNC], two entries are posted to the CQ. The first CQ entry
                                                                 is posted with NIC_CQE_SEND_S[CQE_TYPE] = NIC_CQE_TYPE_E::SEND when the send descriptor's
                                                                 operation is done as described above. The second CQ entry is posted with
                                                                 NIC_CQE_SEND_S[CQE_TYPE] = NIC_CQE_TYPE_E::SEND_PTP when the packet's timestamp is
                                                                 captured or times out.

                                                                 Only one timestamp operation may be outstanding at once for a given Ethernet port.
                                                                 Ignored when [DS] is set, [TSO] is set or NIC_PF_QS()_CFG[SEND_TSTMP_ENA] is clear. */
        uint64_t ds                    : 1;  /**< [ 57: 57] Don't send. If set, NIC hardware will not send the packet bytes to the interface; however
                                                                 it will still perform any NIC_SEND_MEM_S operations. */
        uint64_t pnc                   : 1;  /**< [ 58: 58] Post normal completion. If set, a CQE is created with NIC_CQE_SEND_S[CQE_TYPE] =
                                                                 NIC_CQE_TYPE_E::SEND when the send descriptor's operation completes normally with no
                                                                 error. If [TSO] is set, a CQE is created when the send operation completes for all TSO
                                                                 segments.

                                                                 If clear, no CQE is added on normal completion.

                                                                 Note that a CQE is always added if the send operation terminates with an error after the
                                                                 packet is scheduled; except for NIC_CQE_SEND_STATUS_E::LOCK_VIOL, where a CQE is
                                                                 determined  by NIC_PF_QS()_CFG[LOCK_VIOL_CQE_ENA].

                                                                 NIC will not add a CQE for this send descriptor until after it has completed all L2/DRAM
                                                                 fetches that service all prior NIC_SEND_GATHER_S subdescriptors, and it has fetched all
                                                                 subdescriptors in the send descriptor. If NIC_SEND_MEM_S[WMEM]=1, NIC also will not post
                                                                 the CQE until all NIC_SEND_MEM_S subdescriptors in the descriptor complete and commit. */
        uint64_t tso                   : 1;  /**< [ 59: 59] TCP segmentation offload. Ignored and treated as clear when NIC_PF_TSO_CFG[ENABLE] is
                                                                 clear. When set along with NIC_PF_TSO_CFG[ENABLE], the send descriptor is for a TCP
                                                                 segmentation
                                                                 operation to send one or more packets of a TCP flow, and the related [TSO_*] fields are
                                                                 valid.
                                                                 TSO can be tunneled or non-tunneled as follows:
                                                                 * If [LFPTR] is nonzero, TSO is tunneled. [LEPTR] and [LFPTR] must point to the inner IP
                                                                 and TCP headers, respectively, [L3PTR] must point to the outer IP, and [L4PTR] just point
                                                                 to the tunneling header (e.g. UDP or GRE).
                                                                 * If [LFPTR] is zero, TSO is non-tunneled. [L3PTR] and [L4PTR] must point to the IP and
                                                                 TCP headers, respectively. */
        uint64_t subdc                 : 4;  /**< [ 63: 60] Subdescriptor code. Indicates send header. Enumerated by NIC_SEND_SUBDC_E::HDR. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_104_127      : 24;
        uint64_t lfptr                 : 8;  /**< [103: 96] Inner layer 4 offset. Specifies the location of the first byte of the TCP/UDP header for
                                                                 LF checksumming and/or tunneled TSO. Similar to [L4PTR], but specifies the location of the
                                                                 first byte of inner the TCP/UDP header for inner L4 checksumming and tunneled TSO, as
                                                                 directed by [CKLF], [TSO]. If [CKLF] and [CKL4] are both nonzero, then [LFPTR] must be \>
                                                                 [L4PTR] + 20. */
        uint64_t leptr                 : 8;  /**< [ 95: 88] Inner layer 3 IP offset. Specifies the location of the first byte of the IP packet for LE
                                                                 checksum, LF checksum and/or tunneled TSO. Similar to [L3PTR] but for inner IP as directed
                                                                 by [CKLE], [CKLF], [TSO]. If [CKLE] and [CKL3] are set, then [LEPTR] must be \> [L3PTR] +
                                                                 20. */
        uint64_t tso_sb                : 8;  /**< [ 87: 80] Start bytes when [TSO] set. Location of the start byte of the TCP message payload (i.e.
                                                                 the size of the headers preceding the payload). Must be nonzero and less than [TOTAL],
                                                                 else the send descriptor is treated as non-TSO. */
        uint64_t reserved_78_79        : 2;
        uint64_t tso_mps               : 14; /**< [ 77: 64] When [TSO] set, maximum payload size in bytes per packet (a.k.a. maximum TCP segment
                                                                 size). The maximum TSO packet size is [TSO_SB] + [TSO_MPS], which should not exceed the
                                                                 lesser of 9212 bytes or NIC_PF_LMAC()_CFG2[MAX_PKT_SIZE]. Must be nonzero, else the send
                                                                 descriptor is treated as non-TSO.
                                                                 Must be greater than 256 to support maximum [TOTAL] value of 2**20 - 1 (the number of
                                                                 TSO segments must be less than 4094). */
#else /* Word 1 - Little Endian */
        uint64_t tso_mps               : 14; /**< [ 77: 64] When [TSO] set, maximum payload size in bytes per packet (a.k.a. maximum TCP segment
                                                                 size). The maximum TSO packet size is [TSO_SB] + [TSO_MPS], which should not exceed the
                                                                 lesser of 9212 bytes or NIC_PF_LMAC()_CFG2[MAX_PKT_SIZE]. Must be nonzero, else the send
                                                                 descriptor is treated as non-TSO.
                                                                 Must be greater than 256 to support maximum [TOTAL] value of 2**20 - 1 (the number of
                                                                 TSO segments must be less than 4094). */
        uint64_t reserved_78_79        : 2;
        uint64_t tso_sb                : 8;  /**< [ 87: 80] Start bytes when [TSO] set. Location of the start byte of the TCP message payload (i.e.
                                                                 the size of the headers preceding the payload). Must be nonzero and less than [TOTAL],
                                                                 else the send descriptor is treated as non-TSO. */
        uint64_t leptr                 : 8;  /**< [ 95: 88] Inner layer 3 IP offset. Specifies the location of the first byte of the IP packet for LE
                                                                 checksum, LF checksum and/or tunneled TSO. Similar to [L3PTR] but for inner IP as directed
                                                                 by [CKLE], [CKLF], [TSO]. If [CKLE] and [CKL3] are set, then [LEPTR] must be \> [L3PTR] +
                                                                 20. */
        uint64_t lfptr                 : 8;  /**< [103: 96] Inner layer 4 offset. Specifies the location of the first byte of the TCP/UDP header for
                                                                 LF checksumming and/or tunneled TSO. Similar to [L4PTR], but specifies the location of the
                                                                 first byte of inner the TCP/UDP header for inner L4 checksumming and tunneled TSO, as
                                                                 directed by [CKLF], [TSO]. If [CKLF] and [CKL4] are both nonzero, then [LFPTR] must be \>
                                                                 [L4PTR] + 20. */
        uint64_t reserved_104_127      : 24;
#endif /* Word 1 - End */
    } s;
    /* struct bdk_nic_send_hdr_s_s cn; */
};

/**
 * Structure nic_send_imm_s
 *
 * NIC Send Immediate Subdescriptor Structure
 * The send immediate subdescriptor requests that bytes immediately following this NIC_SEND_IMM_S
 * in the NIC send descriptor are to be included in the packet. The next subdescriptor following
 * this NIC_SEND_IMM_S (when one exists) will follow the immediate bytes, after rounding up to be
 * a multiple of 16 bytes.
 *
 * There may be multiple NIC_SEND_IMM_Ss in one NIC send descriptor. A NIC_SEND_IMM_S is ignored
 * in a NIC send descriptor if the sum of all prior NIC_SEND_GATHER_S[SIZE]s and
 * NIC_SEND_IMM_S[SIZE]s meets or exceeds NIC_SEND_HDR_S[TOTAL].
 */
union bdk_nic_send_imm_s
{
    uint64_t u[2];
    struct bdk_nic_send_imm_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t subdc                 : 4;  /**< [ 63: 60] Subdescriptor code. Indicates Send Immediate. Enumerated by NIC_SEND_SUBDC_E::IMM. */
        uint64_t reserved_12_59        : 48;
        uint64_t size                  : 12; /**< [ 11:  0] Size of immediate data in bytes immediately following this subdescriptor, including the
                                                                 first 8 bytes in the [DATA] field. Size must be between 1 and 4072, and the total send
                                                                 descriptor size cannot exceed 4096 bytes. The next subdescriptor will follow SIZE+8 bytes
                                                                 later, rounded up to the next 16-byte aligned boundary. The subdescriptor is ignored if
                                                                 SIZE is 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t size                  : 12; /**< [ 11:  0] Size of immediate data in bytes immediately following this subdescriptor, including the
                                                                 first 8 bytes in the [DATA] field. Size must be between 1 and 4072, and the total send
                                                                 descriptor size cannot exceed 4096 bytes. The next subdescriptor will follow SIZE+8 bytes
                                                                 later, rounded up to the next 16-byte aligned boundary. The subdescriptor is ignored if
                                                                 SIZE is 0x0. */
        uint64_t reserved_12_59        : 48;
        uint64_t subdc                 : 4;  /**< [ 63: 60] Subdescriptor code. Indicates Send Immediate. Enumerated by NIC_SEND_SUBDC_E::IMM. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t data                  : 64; /**< [127: 64] First 8 bytes of immediate data. */
#else /* Word 1 - Little Endian */
        uint64_t data                  : 64; /**< [127: 64] First 8 bytes of immediate data. */
#endif /* Word 1 - End */
    } s;
    /* struct bdk_nic_send_imm_s_s cn; */
};

/**
 * Structure nic_send_mem_s
 *
 * NIC Send-Memory Subdescriptor Structure
 * The send memory subdescriptor atomically sets, increments or decrements a memory location. NIC
 * will not initiate the memory update for this subdescriptor until after it has processed all
 * other subdescriptors for the packet and all L2/DRAM fetches that service all NIC_SEND_GATHER_S
 * subdescriptors.
 *
 * The atomic memory operation is big-endian if NIC_PF_QS()_CFG[BE] is set and little-endian
 * otherwise.
 *
 * Performance is best if a memory decrement by one is used rather than any other memory
 * set/increment/decrement. (Less internal bus bandwidth is used with memory decrements by one.)
 * NIC performance may be impacted if a send descriptor has more than 4 NIC_SEND_MEM_S
 * subdescriptors.
 *
 * When a NIC_SEND_HDR_S[TSO] is set, NIC executes the NIC_SEND_MEM_S only while processing the
 * last TSO segment, after processing prior segments.
 *
 * NIC_SEND_MEM_S subdescriptors must precede all NIC_SEND_GATHER_S and NIC_SEND_IMM_S
 * subdescriptors in the send descriptor.
 *
 * Internal:
 * This constraint simplifies NIC_SEND_MEM_S handling for TSO.
 */
union bdk_nic_send_mem_s
{
    uint64_t u[2];
    struct bdk_nic_send_mem_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t subdc                 : 4;  /**< [ 63: 60] Subdescriptor code. Indicates Send Memory. Enumerated by NIC_SEND_SUBDC_E::MEM. */
        uint64_t alg                   : 4;  /**< [ 59: 56] Adder algorithm. How to modify the memory location, for example by setting or atomically
                                                                 incrementing. Enumerated by NIC_SEND_MEMALG_E. */
        uint64_t dsz                   : 2;  /**< [ 55: 54] Memory data size. The size of the word in memory, enumerated by NIC_SEND_MEMDSZ_E. */
        uint64_t wmem                  : 1;  /**< [ 53: 53] Wait for memory operation to be committed before posting to the CQ, e.g. when
                                                                 NIC_SEND_HDR_S[PNC] is set. When clear, the memory operation may complete after the CQE is
                                                                 added and potentially after software has begun servicing the CQE. */
        uint64_t reserved_32_52        : 21;
        uint64_t offset                : 32; /**< [ 31:  0] Adder offset. Constant value to add or subtract or set. If the count being modified is to
                                                                 represent the true packet size, then the offset would represent the CRC and pad bytes
                                                                 appended to the packet.

                                                                 Internal:
                                                                 Note IOB hardware has a special encoding for atomic
                                                                 increment/decrement, therefore a change of +/- one is twice as IOB bandwidth efficient as
                                                                 adding/subtracting other values. */
#else /* Word 0 - Little Endian */
        uint64_t offset                : 32; /**< [ 31:  0] Adder offset. Constant value to add or subtract or set. If the count being modified is to
                                                                 represent the true packet size, then the offset would represent the CRC and pad bytes
                                                                 appended to the packet.

                                                                 Internal:
                                                                 Note IOB hardware has a special encoding for atomic
                                                                 increment/decrement, therefore a change of +/- one is twice as IOB bandwidth efficient as
                                                                 adding/subtracting other values. */
        uint64_t reserved_32_52        : 21;
        uint64_t wmem                  : 1;  /**< [ 53: 53] Wait for memory operation to be committed before posting to the CQ, e.g. when
                                                                 NIC_SEND_HDR_S[PNC] is set. When clear, the memory operation may complete after the CQE is
                                                                 added and potentially after software has begun servicing the CQE. */
        uint64_t dsz                   : 2;  /**< [ 55: 54] Memory data size. The size of the word in memory, enumerated by NIC_SEND_MEMDSZ_E. */
        uint64_t alg                   : 4;  /**< [ 59: 56] Adder algorithm. How to modify the memory location, for example by setting or atomically
                                                                 incrementing. Enumerated by NIC_SEND_MEMALG_E. */
        uint64_t subdc                 : 4;  /**< [ 63: 60] Subdescriptor code. Indicates Send Memory. Enumerated by NIC_SEND_SUBDC_E::MEM. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_113_127      : 15;
        uint64_t addr                  : 49; /**< [112: 64] Address. IOVA to be modified. ADDR must be naturally aligned to the size specified in DSZ. */
#else /* Word 1 - Little Endian */
        uint64_t addr                  : 49; /**< [112: 64] Address. IOVA to be modified. ADDR must be naturally aligned to the size specified in DSZ. */
        uint64_t reserved_113_127      : 15;
#endif /* Word 1 - End */
    } s;
    /* struct bdk_nic_send_mem_s_s cn; */
};

/**
 * Register (NCB) nic_pf_bist0_status
 *
 * NIC Memory BIST 0 Status Register
 * This register reports memory BIST status. Each bit corresponds to a different RAM; 0 = pass, 1
 * = fail.
 *
 * Internal:
 * Bits in each field are enumerated by NIC_PF_ECC0_FLIP0.
 */
union bdk_nic_pf_bist0_status
{
    uint64_t u;
    struct bdk_nic_pf_bist0_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t blk3                  : 32; /**< [ 63: 32](RO/H) BIST status for group 0 block 3 memories. */
        uint64_t blk2                  : 16; /**< [ 31: 16](RO/H) BIST status for group 0 block 2 memories. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](RO/H) BIST status for group 0 block 1 memories. */
        uint64_t blk0                  : 8;  /**< [  7:  0](RO/H) BIST status for group 0 block 0 memories. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 8;  /**< [  7:  0](RO/H) BIST status for group 0 block 0 memories. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](RO/H) BIST status for group 0 block 1 memories. */
        uint64_t blk2                  : 16; /**< [ 31: 16](RO/H) BIST status for group 0 block 2 memories. */
        uint64_t blk3                  : 32; /**< [ 63: 32](RO/H) BIST status for group 0 block 3 memories. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_bist0_status_s cn; */
};
typedef union bdk_nic_pf_bist0_status bdk_nic_pf_bist0_status_t;

#define BDK_NIC_PF_BIST0_STATUS BDK_NIC_PF_BIST0_STATUS_FUNC()
static inline uint64_t BDK_NIC_PF_BIST0_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_BIST0_STATUS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000001280ll;
    __bdk_csr_fatal("NIC_PF_BIST0_STATUS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_BIST0_STATUS bdk_nic_pf_bist0_status_t
#define bustype_BDK_NIC_PF_BIST0_STATUS BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_BIST0_STATUS "NIC_PF_BIST0_STATUS"
#define device_bar_BDK_NIC_PF_BIST0_STATUS 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_BIST0_STATUS 0
#define arguments_BDK_NIC_PF_BIST0_STATUS -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_bist1_status
 *
 * NIC Memory BIST 1 Status Register
 * See NIC_PF_BIST0_STATUS.
 */
union bdk_nic_pf_bist1_status
{
    uint64_t u;
    struct bdk_nic_pf_bist1_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](RO/H) BIST status for group 1 block 1 memories. */
        uint64_t blk0                  : 24; /**< [ 23:  0](RO/H) BIST status for group 1 block 0 memories. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](RO/H) BIST status for group 1 block 0 memories. */
        uint64_t blk1                  : 16; /**< [ 39: 24](RO/H) BIST status for group 1 block 1 memories. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_bist1_status_s cn; */
};
typedef union bdk_nic_pf_bist1_status bdk_nic_pf_bist1_status_t;

#define BDK_NIC_PF_BIST1_STATUS BDK_NIC_PF_BIST1_STATUS_FUNC()
static inline uint64_t BDK_NIC_PF_BIST1_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_BIST1_STATUS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000001288ll;
    __bdk_csr_fatal("NIC_PF_BIST1_STATUS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_BIST1_STATUS bdk_nic_pf_bist1_status_t
#define bustype_BDK_NIC_PF_BIST1_STATUS BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_BIST1_STATUS "NIC_PF_BIST1_STATUS"
#define device_bar_BDK_NIC_PF_BIST1_STATUS 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_BIST1_STATUS 0
#define arguments_BDK_NIC_PF_BIST1_STATUS -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_bist2_status
 *
 * NIC Memory BIST 2 Status Register
 * See NIC_PF_BIST0_STATUS.
 */
union bdk_nic_pf_bist2_status
{
    uint64_t u;
    struct bdk_nic_pf_bist2_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t blk0                  : 50; /**< [ 49:  0](RO/H) BIST status for group 2 block 0 memories. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 50; /**< [ 49:  0](RO/H) BIST status for group 2 block 0 memories. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_bist2_status_s cn; */
};
typedef union bdk_nic_pf_bist2_status bdk_nic_pf_bist2_status_t;

#define BDK_NIC_PF_BIST2_STATUS BDK_NIC_PF_BIST2_STATUS_FUNC()
static inline uint64_t BDK_NIC_PF_BIST2_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_BIST2_STATUS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000001290ll;
    __bdk_csr_fatal("NIC_PF_BIST2_STATUS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_BIST2_STATUS bdk_nic_pf_bist2_status_t
#define bustype_BDK_NIC_PF_BIST2_STATUS BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_BIST2_STATUS "NIC_PF_BIST2_STATUS"
#define device_bar_BDK_NIC_PF_BIST2_STATUS 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_BIST2_STATUS 0
#define arguments_BDK_NIC_PF_BIST2_STATUS -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_bist3_status
 *
 * NIC Memory BIST 3 Status Register
 * See NIC_PF_BIST0_STATUS.
 */
union bdk_nic_pf_bist3_status
{
    uint64_t u;
    struct bdk_nic_pf_bist3_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](RO/H) BIST status for group 3 block 1 memories. */
        uint64_t blk0                  : 24; /**< [ 23:  0](RO/H) BIST status for group 3 block 0 memories. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](RO/H) BIST status for group 3 block 0 memories. */
        uint64_t blk1                  : 16; /**< [ 39: 24](RO/H) BIST status for group 3 block 1 memories. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_bist3_status_s cn; */
};
typedef union bdk_nic_pf_bist3_status bdk_nic_pf_bist3_status_t;

#define BDK_NIC_PF_BIST3_STATUS BDK_NIC_PF_BIST3_STATUS_FUNC()
static inline uint64_t BDK_NIC_PF_BIST3_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_BIST3_STATUS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000001298ll;
    __bdk_csr_fatal("NIC_PF_BIST3_STATUS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_BIST3_STATUS bdk_nic_pf_bist3_status_t
#define bustype_BDK_NIC_PF_BIST3_STATUS BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_BIST3_STATUS "NIC_PF_BIST3_STATUS"
#define device_bar_BDK_NIC_PF_BIST3_STATUS 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_BIST3_STATUS 0
#define arguments_BDK_NIC_PF_BIST3_STATUS -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_bist4_status
 *
 * NIC Memory BIST 4 Status Register
 */
union bdk_nic_pf_bist4_status
{
    uint64_t u;
    struct bdk_nic_pf_bist4_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t mcam                  : 3;  /**< [  2:  0](RO/H) MCAM BIST status signals. */
#else /* Word 0 - Little Endian */
        uint64_t mcam                  : 3;  /**< [  2:  0](RO/H) MCAM BIST status signals. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_bist4_status_s cn; */
};
typedef union bdk_nic_pf_bist4_status bdk_nic_pf_bist4_status_t;

#define BDK_NIC_PF_BIST4_STATUS BDK_NIC_PF_BIST4_STATUS_FUNC()
static inline uint64_t BDK_NIC_PF_BIST4_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_BIST4_STATUS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x8430000012a0ll;
    __bdk_csr_fatal("NIC_PF_BIST4_STATUS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_BIST4_STATUS bdk_nic_pf_bist4_status_t
#define bustype_BDK_NIC_PF_BIST4_STATUS BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_BIST4_STATUS "NIC_PF_BIST4_STATUS"
#define device_bar_BDK_NIC_PF_BIST4_STATUS 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_BIST4_STATUS 0
#define arguments_BDK_NIC_PF_BIST4_STATUS -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_bp_cfg
 *
 * NIC PF Backpressure/RED Configuration Register
 */
union bdk_nic_pf_bp_cfg
{
    uint64_t u;
    struct bdk_nic_pf_bp_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t bp_poll_ena           : 1;  /**< [  6:  6](R/W) This bit enables the backpressure polling loop. */
        uint64_t bp_poll_dly           : 6;  /**< [  5:  0](R/W) Number of cycles between polling the various RQ resources for backpressure updates.
                                                                 Increasing values decrease power. Zero cause the BP polling to operation at the fastest
                                                                 possible speed, one indicates a level computation every other cycle, etc. */
#else /* Word 0 - Little Endian */
        uint64_t bp_poll_dly           : 6;  /**< [  5:  0](R/W) Number of cycles between polling the various RQ resources for backpressure updates.
                                                                 Increasing values decrease power. Zero cause the BP polling to operation at the fastest
                                                                 possible speed, one indicates a level computation every other cycle, etc. */
        uint64_t bp_poll_ena           : 1;  /**< [  6:  6](R/W) This bit enables the backpressure polling loop. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_bp_cfg_s cn; */
};
typedef union bdk_nic_pf_bp_cfg bdk_nic_pf_bp_cfg_t;

#define BDK_NIC_PF_BP_CFG BDK_NIC_PF_BP_CFG_FUNC()
static inline uint64_t BDK_NIC_PF_BP_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_BP_CFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000000080ll;
    __bdk_csr_fatal("NIC_PF_BP_CFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_BP_CFG bdk_nic_pf_bp_cfg_t
#define bustype_BDK_NIC_PF_BP_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_BP_CFG "NIC_PF_BP_CFG"
#define device_bar_BDK_NIC_PF_BP_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_BP_CFG 0
#define arguments_BDK_NIC_PF_BP_CFG -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_cfg
 *
 * NIC General Configuration Register
 */
union bdk_nic_pf_cfg
{
    uint64_t u;
    struct bdk_nic_pf_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t test_mode             : 1;  /**< [  1:  1](R/W) Enable test mode. Must be clear during normal operation in order to prevent a VF from
                                                                 corrupting the operation of other VFs. When clear, writes to all CQ, SQ and RBDR ring
                                                                 pointers (head, tail, debug) are ignored (WI). When set, writing to the ring
                                                                 pointers is enabled. */
        uint64_t ena                   : 1;  /**< [  0:  0](R/W) Enable NIC block.
                                                                 Internal:
                                                                 Used to enable conditional SCLK. */
#else /* Word 0 - Little Endian */
        uint64_t ena                   : 1;  /**< [  0:  0](R/W) Enable NIC block.
                                                                 Internal:
                                                                 Used to enable conditional SCLK. */
        uint64_t test_mode             : 1;  /**< [  1:  1](R/W) Enable test mode. Must be clear during normal operation in order to prevent a VF from
                                                                 corrupting the operation of other VFs. When clear, writes to all CQ, SQ and RBDR ring
                                                                 pointers (head, tail, debug) are ignored (WI). When set, writing to the ring
                                                                 pointers is enabled. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_cfg_s cn; */
};
typedef union bdk_nic_pf_cfg bdk_nic_pf_cfg_t;

#define BDK_NIC_PF_CFG BDK_NIC_PF_CFG_FUNC()
static inline uint64_t BDK_NIC_PF_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_CFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000000000ll;
    __bdk_csr_fatal("NIC_PF_CFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_CFG bdk_nic_pf_cfg_t
#define bustype_BDK_NIC_PF_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_CFG "NIC_PF_CFG"
#define device_bar_BDK_NIC_PF_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_CFG 0
#define arguments_BDK_NIC_PF_CFG -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_chan#_credit
 *
 * NIC Channel Credit Registers
 * Configures channel credits. Fields are the same as NIC_PF_LMAC()_CREDIT, though the
 * credits apply to a channel rather than an LMAC.
 * Enumerated by NIC_CHAN_IDX_E.
 */
union bdk_nic_pf_chanx_credit
{
    uint64_t u;
    struct bdk_nic_pf_chanx_credit_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t cc_unit_cnt           : 20; /**< [ 31: 12](R/W/H) Channel-credit unit count. This value, plus 1 MTU, represents the maximum outstanding
                                                                 aggregate channel credit units for this LMAC. A credit unit is 16 bytes.  Note that this
                                                                 20-bit field represents a
                                                                 signed value that decrements towards zero as credits are used. Packets are not allowed to
                                                                 flow when the count is less than zero. As such, the most significant bit should normally
                                                                 be programmed as zero (positive count). This gives a maximum value for this field of 2^19
                                                                 - 1.

                                                                 In order to prevent blocking between BGX LMACs, [CC_ENABLE] should be set to 1 and
                                                                 [CC_UNIT_CNT] should be less than

                                                                 _     ((LMAC TX buffer size in BGX) - (MTU excluding FCS))/16

                                                                 The LMAC TX buffer size is defined by BGX()_CMR_TX_LMACS[LMACS]. For example, if
                                                                 BGX()_CMR_TX_LMACS[LMACS]=0x4 (12 KB per LMAC) and the LMAC's MTU excluding FCS
                                                                 is 9212 bytes (9216 minus 4 byte FCS), then [CC_UNIT_CNT] should be \< (12288 - 9212)/16 =
                                                                 192.

                                                                 For LBK LMACs, [CC_ENABLE] must be set and [CC_UNIT_CNT] must be less than

                                                                 _     (LBK_FIFO_SIZE - (MTU excluding FCS))/16

                                                                 where LBK_FIFO_SIZE = 12288 bytes. */
        uint64_t cc_packet_cnt         : 10; /**< [ 11:  2](R/W/H) Channel-credit packet count. This value, plus 1, represents the maximum outstanding
                                                                 aggregate packet count for this LMAC. Note that this 10-bit field represents a signed
                                                                 value that decrements towards zero as credits are used. Packets are not allowed to flow
                                                                 when the count is less than zero. As such the most significant bit should normally be
                                                                 programmed as zero (positive count). This gives a maximum value for this field of 2^9 - 1. */
        uint64_t cc_enable             : 1;  /**< [  1:  1](R/W) Channel-credit enable. Enables [CC_UNIT_CNT] and [CC_PACKET_CNT] aggregate credit processing. */
        uint64_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0            : 1;
        uint64_t cc_enable             : 1;  /**< [  1:  1](R/W) Channel-credit enable. Enables [CC_UNIT_CNT] and [CC_PACKET_CNT] aggregate credit processing. */
        uint64_t cc_packet_cnt         : 10; /**< [ 11:  2](R/W/H) Channel-credit packet count. This value, plus 1, represents the maximum outstanding
                                                                 aggregate packet count for this LMAC. Note that this 10-bit field represents a signed
                                                                 value that decrements towards zero as credits are used. Packets are not allowed to flow
                                                                 when the count is less than zero. As such the most significant bit should normally be
                                                                 programmed as zero (positive count). This gives a maximum value for this field of 2^9 - 1. */
        uint64_t cc_unit_cnt           : 20; /**< [ 31: 12](R/W/H) Channel-credit unit count. This value, plus 1 MTU, represents the maximum outstanding
                                                                 aggregate channel credit units for this LMAC. A credit unit is 16 bytes.  Note that this
                                                                 20-bit field represents a
                                                                 signed value that decrements towards zero as credits are used. Packets are not allowed to
                                                                 flow when the count is less than zero. As such, the most significant bit should normally
                                                                 be programmed as zero (positive count). This gives a maximum value for this field of 2^19
                                                                 - 1.

                                                                 In order to prevent blocking between BGX LMACs, [CC_ENABLE] should be set to 1 and
                                                                 [CC_UNIT_CNT] should be less than

                                                                 _     ((LMAC TX buffer size in BGX) - (MTU excluding FCS))/16

                                                                 The LMAC TX buffer size is defined by BGX()_CMR_TX_LMACS[LMACS]. For example, if
                                                                 BGX()_CMR_TX_LMACS[LMACS]=0x4 (12 KB per LMAC) and the LMAC's MTU excluding FCS
                                                                 is 9212 bytes (9216 minus 4 byte FCS), then [CC_UNIT_CNT] should be \< (12288 - 9212)/16 =
                                                                 192.

                                                                 For LBK LMACs, [CC_ENABLE] must be set and [CC_UNIT_CNT] must be less than

                                                                 _     (LBK_FIFO_SIZE - (MTU excluding FCS))/16

                                                                 where LBK_FIFO_SIZE = 12288 bytes. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_chanx_credit_s cn8; */
    /* struct bdk_nic_pf_chanx_credit_s cn81xx; */
    struct bdk_nic_pf_chanx_credit_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t cc_unit_cnt           : 20; /**< [ 31: 12](R/W/H) Channel-credit unit count. This value, plus 1 MTU, represents the maximum outstanding
                                                                 aggregate channel credit units for this LMAC. A credit unit is 16 bytes.  Note that this
                                                                 20-bit field represents a
                                                                 signed value that decrements towards zero as credits are used. Packets are not allowed to
                                                                 flow when the count is less than zero. As such, the most significant bit should normally
                                                                 be programmed as zero (positive count). This gives a maximum value for this field of 2^19
                                                                 - 1.

                                                                 In order to prevent blocking between BGX LMACs, [CC_ENABLE] should be set to 1 and
                                                                 [CC_UNIT_CNT] should be less than

                                                                 _     ((LMAC TX buffer size in BGX) - (MTU excluding FCS))/16

                                                                 The LMAC TX buffer size is defined by BGX()_CMR_TX_LMACS[LMACS]. For example, if
                                                                 BGX()_CMR_TX_LMACS[LMACS]=0x4 (12 KB per LMAC) and the LMAC's MTU excluding FCS
                                                                 is 9212 bytes (9216 minus 4 byte FCS), then [CC_UNIT_CNT] should be \< (12288 - 9212)/16 =
                                                                 192.

                                                                 For LBK LMACs, the recommended configuration is [CC_ENABLE] = 1 and [CC_UNIT_CNT] = 512.

                                                                 Internal:
                                                                 LBK value allows for 80 Gbps loopback data rate with 800ns round trip latency:

                                                                 _ Minimum LBK in-flight data = 80*800 = 64Kbits = 512 credit units.

                                                                 Note: maximum LBK in-fligh data = min + MTU. */
        uint64_t cc_packet_cnt         : 10; /**< [ 11:  2](R/W/H) Channel-credit packet count. This value, plus 1, represents the maximum outstanding
                                                                 aggregate packet count for this LMAC. Note that this 10-bit field represents a signed
                                                                 value that decrements towards zero as credits are used. Packets are not allowed to flow
                                                                 when the count is less than zero. As such the most significant bit should normally be
                                                                 programmed as zero (positive count). This gives a maximum value for this field of 2^9 - 1. */
        uint64_t cc_enable             : 1;  /**< [  1:  1](R/W) Channel-credit enable. Enables [CC_UNIT_CNT] and [CC_PACKET_CNT] aggregate credit processing. */
        uint64_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0            : 1;
        uint64_t cc_enable             : 1;  /**< [  1:  1](R/W) Channel-credit enable. Enables [CC_UNIT_CNT] and [CC_PACKET_CNT] aggregate credit processing. */
        uint64_t cc_packet_cnt         : 10; /**< [ 11:  2](R/W/H) Channel-credit packet count. This value, plus 1, represents the maximum outstanding
                                                                 aggregate packet count for this LMAC. Note that this 10-bit field represents a signed
                                                                 value that decrements towards zero as credits are used. Packets are not allowed to flow
                                                                 when the count is less than zero. As such the most significant bit should normally be
                                                                 programmed as zero (positive count). This gives a maximum value for this field of 2^9 - 1. */
        uint64_t cc_unit_cnt           : 20; /**< [ 31: 12](R/W/H) Channel-credit unit count. This value, plus 1 MTU, represents the maximum outstanding
                                                                 aggregate channel credit units for this LMAC. A credit unit is 16 bytes.  Note that this
                                                                 20-bit field represents a
                                                                 signed value that decrements towards zero as credits are used. Packets are not allowed to
                                                                 flow when the count is less than zero. As such, the most significant bit should normally
                                                                 be programmed as zero (positive count). This gives a maximum value for this field of 2^19
                                                                 - 1.

                                                                 In order to prevent blocking between BGX LMACs, [CC_ENABLE] should be set to 1 and
                                                                 [CC_UNIT_CNT] should be less than

                                                                 _     ((LMAC TX buffer size in BGX) - (MTU excluding FCS))/16

                                                                 The LMAC TX buffer size is defined by BGX()_CMR_TX_LMACS[LMACS]. For example, if
                                                                 BGX()_CMR_TX_LMACS[LMACS]=0x4 (12 KB per LMAC) and the LMAC's MTU excluding FCS
                                                                 is 9212 bytes (9216 minus 4 byte FCS), then [CC_UNIT_CNT] should be \< (12288 - 9212)/16 =
                                                                 192.

                                                                 For LBK LMACs, the recommended configuration is [CC_ENABLE] = 1 and [CC_UNIT_CNT] = 512.

                                                                 Internal:
                                                                 LBK value allows for 80 Gbps loopback data rate with 800ns round trip latency:

                                                                 _ Minimum LBK in-flight data = 80*800 = 64Kbits = 512 credit units.

                                                                 Note: maximum LBK in-fligh data = min + MTU. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_pf_chanx_credit bdk_nic_pf_chanx_credit_t;

static inline uint64_t BDK_NIC_PF_CHANX_CREDIT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_CHANX_CREDIT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=95))
        return 0x843000460000ll + 8ll * ((a) & 0x7f);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=255))
        return 0x843000460000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("NIC_PF_CHANX_CREDIT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_CHANX_CREDIT(a) bdk_nic_pf_chanx_credit_t
#define bustype_BDK_NIC_PF_CHANX_CREDIT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_CHANX_CREDIT(a) "NIC_PF_CHANX_CREDIT"
#define device_bar_BDK_NIC_PF_CHANX_CREDIT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_CHANX_CREDIT(a) (a)
#define arguments_BDK_NIC_PF_CHANX_CREDIT(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_chan#_rx_bp_cfg
 *
 * NIC Channel Receive Backpressure Configuration Registers
 */
union bdk_nic_pf_chanx_rx_bp_cfg
{
    uint64_t u;
    struct bdk_nic_pf_chanx_rx_bp_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ena                   : 1;  /**< [ 63: 63](R/W) This bit is set to enable backpressure for this channel. */
        uint64_t reserved_8_62         : 55;
        uint64_t bpid                  : 8;  /**< [  7:  0](R/W) BPID used for RX channel backpressure. */
#else /* Word 0 - Little Endian */
        uint64_t bpid                  : 8;  /**< [  7:  0](R/W) BPID used for RX channel backpressure. */
        uint64_t reserved_8_62         : 55;
        uint64_t ena                   : 1;  /**< [ 63: 63](R/W) This bit is set to enable backpressure for this channel. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_chanx_rx_bp_cfg_s cn8; */
    struct bdk_nic_pf_chanx_rx_bp_cfg_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ena                   : 1;  /**< [ 63: 63](R/W) This bit is set to enable backpressure for this channel. */
        uint64_t reserved_8_62         : 55;
        uint64_t reserved_7            : 1;
        uint64_t bpid                  : 7;  /**< [  6:  0](R/W) BPID used for RX channel backpressure. */
#else /* Word 0 - Little Endian */
        uint64_t bpid                  : 7;  /**< [  6:  0](R/W) BPID used for RX channel backpressure. */
        uint64_t reserved_7            : 1;
        uint64_t reserved_8_62         : 55;
        uint64_t ena                   : 1;  /**< [ 63: 63](R/W) This bit is set to enable backpressure for this channel. */
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_nic_pf_chanx_rx_bp_cfg_s cn83xx; */
};
typedef union bdk_nic_pf_chanx_rx_bp_cfg bdk_nic_pf_chanx_rx_bp_cfg_t;

static inline uint64_t BDK_NIC_PF_CHANX_RX_BP_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_CHANX_RX_BP_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=95))
        return 0x843000480000ll + 8ll * ((a) & 0x7f);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=255))
        return 0x843000480000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("NIC_PF_CHANX_RX_BP_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_CHANX_RX_BP_CFG(a) bdk_nic_pf_chanx_rx_bp_cfg_t
#define bustype_BDK_NIC_PF_CHANX_RX_BP_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_CHANX_RX_BP_CFG(a) "NIC_PF_CHANX_RX_BP_CFG"
#define device_bar_BDK_NIC_PF_CHANX_RX_BP_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_CHANX_RX_BP_CFG(a) (a)
#define arguments_BDK_NIC_PF_CHANX_RX_BP_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_chan#_rx_cfg
 *
 * NIC Channel Receive Configuration Registers
 */
union bdk_nic_pf_chanx_rx_cfg
{
    uint64_t u;
    struct bdk_nic_pf_chanx_rx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cpi_alg               : 2;  /**< [ 63: 62](R/W) Algorithm used in CPI calculation. Enumerated by NIC_CPI_ALG_E. */
        uint64_t reserved_59_61        : 3;
        uint64_t cpi_base              : 11; /**< [ 58: 48](R/W) Base index into NIC_PF_CPI()_CFG. */
        uint64_t reserved_0_47         : 48;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_47         : 48;
        uint64_t cpi_base              : 11; /**< [ 58: 48](R/W) Base index into NIC_PF_CPI()_CFG. */
        uint64_t reserved_59_61        : 3;
        uint64_t cpi_alg               : 2;  /**< [ 63: 62](R/W) Algorithm used in CPI calculation. Enumerated by NIC_CPI_ALG_E. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_chanx_rx_cfg_s cn8; */
    struct bdk_nic_pf_chanx_rx_cfg_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cpi_alg               : 2;  /**< [ 63: 62](R/W) Algorithm used in CPI calculation. Enumerated by NIC_CPI_ALG_E. */
        uint64_t reserved_59_61        : 3;
        uint64_t reserved_57_58        : 2;
        uint64_t cpi_base              : 9;  /**< [ 56: 48](R/W) Base index into NIC_PF_CPI()_CFG. */
        uint64_t reserved_0_47         : 48;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_47         : 48;
        uint64_t cpi_base              : 9;  /**< [ 56: 48](R/W) Base index into NIC_PF_CPI()_CFG. */
        uint64_t reserved_57_58        : 2;
        uint64_t reserved_59_61        : 3;
        uint64_t cpi_alg               : 2;  /**< [ 63: 62](R/W) Algorithm used in CPI calculation. Enumerated by NIC_CPI_ALG_E. */
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_nic_pf_chanx_rx_cfg_s cn83xx; */
};
typedef union bdk_nic_pf_chanx_rx_cfg bdk_nic_pf_chanx_rx_cfg_t;

static inline uint64_t BDK_NIC_PF_CHANX_RX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_CHANX_RX_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=95))
        return 0x843000420000ll + 8ll * ((a) & 0x7f);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=255))
        return 0x843000420000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("NIC_PF_CHANX_RX_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_CHANX_RX_CFG(a) bdk_nic_pf_chanx_rx_cfg_t
#define bustype_BDK_NIC_PF_CHANX_RX_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_CHANX_RX_CFG(a) "NIC_PF_CHANX_RX_CFG"
#define device_bar_BDK_NIC_PF_CHANX_RX_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_CHANX_RX_CFG(a) (a)
#define arguments_BDK_NIC_PF_CHANX_RX_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_chan#_sw_xoff
 *
 * NIC Channel Software-Controlled XOFF Registers
 * Index enumerated by NIC_CHAN_IDX_E.
 */
union bdk_nic_pf_chanx_sw_xoff
{
    uint64_t u;
    struct bdk_nic_pf_chanx_sw_xoff_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t bp_xoff               : 1;  /**< [  1:  1](RO/H) Backpressure XOFF. When set, indicates that this channel is being backpressured, and NIC
                                                                 will not send packets on the channel is NIC_PF_CHAN()_TX_CFG[BP_ENA] is also set. */
        uint64_t sw_xoff               : 1;  /**< [  0:  0](R/W) Software XOFF. When set, this channel does not send traffic. */
#else /* Word 0 - Little Endian */
        uint64_t sw_xoff               : 1;  /**< [  0:  0](R/W) Software XOFF. When set, this channel does not send traffic. */
        uint64_t bp_xoff               : 1;  /**< [  1:  1](RO/H) Backpressure XOFF. When set, indicates that this channel is being backpressured, and NIC
                                                                 will not send packets on the channel is NIC_PF_CHAN()_TX_CFG[BP_ENA] is also set. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_chanx_sw_xoff_s cn; */
};
typedef union bdk_nic_pf_chanx_sw_xoff bdk_nic_pf_chanx_sw_xoff_t;

static inline uint64_t BDK_NIC_PF_CHANX_SW_XOFF(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_CHANX_SW_XOFF(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=95))
        return 0x843000440000ll + 8ll * ((a) & 0x7f);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=255))
        return 0x843000440000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("NIC_PF_CHANX_SW_XOFF", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_CHANX_SW_XOFF(a) bdk_nic_pf_chanx_sw_xoff_t
#define bustype_BDK_NIC_PF_CHANX_SW_XOFF(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_CHANX_SW_XOFF(a) "NIC_PF_CHANX_SW_XOFF"
#define device_bar_BDK_NIC_PF_CHANX_SW_XOFF(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_CHANX_SW_XOFF(a) (a)
#define arguments_BDK_NIC_PF_CHANX_SW_XOFF(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_chan#_tx_cfg
 *
 * NIC Channel Transmit Configuration Registers
 * Index enumerated by NIC_CHAN_IDX_E.
 */
union bdk_nic_pf_chanx_tx_cfg
{
    uint64_t u;
    struct bdk_nic_pf_chanx_tx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t bp_ena                : 1;  /**< [  0:  0](R/W) Enables listening for backpressure on this channel. */
#else /* Word 0 - Little Endian */
        uint64_t bp_ena                : 1;  /**< [  0:  0](R/W) Enables listening for backpressure on this channel. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_chanx_tx_cfg_s cn; */
};
typedef union bdk_nic_pf_chanx_tx_cfg bdk_nic_pf_chanx_tx_cfg_t;

static inline uint64_t BDK_NIC_PF_CHANX_TX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_CHANX_TX_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=95))
        return 0x843000400000ll + 8ll * ((a) & 0x7f);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=255))
        return 0x843000400000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("NIC_PF_CHANX_TX_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_CHANX_TX_CFG(a) bdk_nic_pf_chanx_tx_cfg_t
#define bustype_BDK_NIC_PF_CHANX_TX_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_CHANX_TX_CFG(a) "NIC_PF_CHANX_TX_CFG"
#define device_bar_BDK_NIC_PF_CHANX_TX_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_CHANX_TX_CFG(a) (a)
#define arguments_BDK_NIC_PF_CHANX_TX_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_const
 *
 * NIC PF Constants Register
 * This register contains constants for software discovery.
 */
union bdk_nic_pf_const
{
    uint64_t u;
    struct bdk_nic_pf_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_56_63        : 8;
        uint64_t intfs                 : 4;  /**< [ 55: 52](RO) Number of interfaces enumerated by NIC_INTF_E. */
        uint64_t lmacs                 : 8;  /**< [ 51: 44](RO) Number of LMACs enumerated by NIC_LMAC_E. */
        uint64_t channels              : 12; /**< [ 43: 32](RO) Number of channels enumerated by NIC_CHAN_IDX_E. */
        uint64_t num_lbk               : 4;  /**< [ 31: 28](RO) Number of LBK interfaces enumerated in NIC_INTF_E. */
        uint64_t num_bgx_rgx           : 4;  /**< [ 27: 24](RO) Number of BGX/RGX interfaces enumerated in NIC_INTF_E. */
        uint64_t rgx_map               : 8;  /**< [ 23: 16](RO) Bit map indexed by NIC_INTF_BLOCK_E::BGX() specifying which of the [NUM_BGX_RGX] instances
                                                                 are RGX; bit 0 for BGX 0, bit 1 for BGX 1, etc. Per bit: 0=BGX, 1=RGX. */
        uint64_t lbk_lmac_channels     : 8;  /**< [ 15:  8](RO) Number of channels supported by NIC per LBK interface/LMAC. */
        uint64_t bgx_lmac_channels     : 8;  /**< [  7:  0](RO) Number of channels supported by NIC per BGX/RGX LMAC. */
#else /* Word 0 - Little Endian */
        uint64_t bgx_lmac_channels     : 8;  /**< [  7:  0](RO) Number of channels supported by NIC per BGX/RGX LMAC. */
        uint64_t lbk_lmac_channels     : 8;  /**< [ 15:  8](RO) Number of channels supported by NIC per LBK interface/LMAC. */
        uint64_t rgx_map               : 8;  /**< [ 23: 16](RO) Bit map indexed by NIC_INTF_BLOCK_E::BGX() specifying which of the [NUM_BGX_RGX] instances
                                                                 are RGX; bit 0 for BGX 0, bit 1 for BGX 1, etc. Per bit: 0=BGX, 1=RGX. */
        uint64_t num_bgx_rgx           : 4;  /**< [ 27: 24](RO) Number of BGX/RGX interfaces enumerated in NIC_INTF_E. */
        uint64_t num_lbk               : 4;  /**< [ 31: 28](RO) Number of LBK interfaces enumerated in NIC_INTF_E. */
        uint64_t channels              : 12; /**< [ 43: 32](RO) Number of channels enumerated by NIC_CHAN_IDX_E. */
        uint64_t lmacs                 : 8;  /**< [ 51: 44](RO) Number of LMACs enumerated by NIC_LMAC_E. */
        uint64_t intfs                 : 4;  /**< [ 55: 52](RO) Number of interfaces enumerated by NIC_INTF_E. */
        uint64_t reserved_56_63        : 8;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_const_s cn; */
};
typedef union bdk_nic_pf_const bdk_nic_pf_const_t;

#define BDK_NIC_PF_CONST BDK_NIC_PF_CONST_FUNC()
static inline uint64_t BDK_NIC_PF_CONST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_CONST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000000020ll;
    __bdk_csr_fatal("NIC_PF_CONST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_CONST bdk_nic_pf_const_t
#define bustype_BDK_NIC_PF_CONST BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_CONST "NIC_PF_CONST"
#define device_bar_BDK_NIC_PF_CONST 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_CONST 0
#define arguments_BDK_NIC_PF_CONST -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_const1
 *
 * NIC PF Constants 1 Register
 * This register contains constants for software discovery.
 */
union bdk_nic_pf_const1
{
    uint64_t u;
    struct bdk_nic_pf_const1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t mcam_entries          : 12; /**< [ 23: 12](RO) Number of MCAM entries. For backward compatibility, a value of 0 represents 192. */
        uint64_t vnics                 : 12; /**< [ 11:  0](RO) Number of VNICs/VFs/QSes. */
#else /* Word 0 - Little Endian */
        uint64_t vnics                 : 12; /**< [ 11:  0](RO) Number of VNICs/VFs/QSes. */
        uint64_t mcam_entries          : 12; /**< [ 23: 12](RO) Number of MCAM entries. For backward compatibility, a value of 0 represents 192. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_const1_s cn; */
};
typedef union bdk_nic_pf_const1 bdk_nic_pf_const1_t;

#define BDK_NIC_PF_CONST1 BDK_NIC_PF_CONST1_FUNC()
static inline uint64_t BDK_NIC_PF_CONST1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_CONST1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000000028ll;
    __bdk_csr_fatal("NIC_PF_CONST1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_CONST1 bdk_nic_pf_const1_t
#define bustype_BDK_NIC_PF_CONST1 BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_CONST1 "NIC_PF_CONST1"
#define device_bar_BDK_NIC_PF_CONST1 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_CONST1 0
#define arguments_BDK_NIC_PF_CONST1 -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_cpi#_cfg
 *
 * NIC CPI Table Registers
 */
union bdk_nic_pf_cpix_cfg
{
    uint64_t u;
    struct bdk_nic_pf_cpix_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t mpi_alg               : 1;  /**< [ 63: 63](R/W) MPI algorithm. When set, the index into the NIC_PF_MPI()_CFG register is generated off
                                                                 the MCAM lookup. */
        uint64_t reserved_20_62        : 43;
        uint64_t padd                  : 4;  /**< [ 19: 16](R/W) Port to channel adder for calculating NIC_CQE_RX_S[CHAN]. */
        uint64_t reserved_0_15         : 16;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_15         : 16;
        uint64_t padd                  : 4;  /**< [ 19: 16](R/W) Port to channel adder for calculating NIC_CQE_RX_S[CHAN]. */
        uint64_t reserved_20_62        : 43;
        uint64_t mpi_alg               : 1;  /**< [ 63: 63](R/W) MPI algorithm. When set, the index into the NIC_PF_MPI()_CFG register is generated off
                                                                 the MCAM lookup. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_cpix_cfg_s cn; */
};
typedef union bdk_nic_pf_cpix_cfg bdk_nic_pf_cpix_cfg_t;

static inline uint64_t BDK_NIC_PF_CPIX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_CPIX_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=511))
        return 0x843000200000ll + 8ll * ((a) & 0x1ff);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=2047))
        return 0x843000200000ll + 8ll * ((a) & 0x7ff);
    __bdk_csr_fatal("NIC_PF_CPIX_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_CPIX_CFG(a) bdk_nic_pf_cpix_cfg_t
#define bustype_BDK_NIC_PF_CPIX_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_CPIX_CFG(a) "NIC_PF_CPIX_CFG"
#define device_bar_BDK_NIC_PF_CPIX_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_CPIX_CFG(a) (a)
#define arguments_BDK_NIC_PF_CPIX_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_cq_avg_cfg
 *
 * NIC PF CQ Averaging Configuration Register
 */
union bdk_nic_pf_cq_avg_cfg
{
    uint64_t u;
    struct bdk_nic_pf_cq_avg_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_21_63        : 43;
        uint64_t avg_en                : 1;  /**< [ 20: 20](R/W) QoS averaging enable. When set, compute average buffer levels. When clear, do not compute
                                                                 averages and save a few mW of power. */
        uint64_t lvl_dly               : 6;  /**< [ 19: 14](R/W) Levelizer delay. See [AVG_DLY]. Must be \>= 2 when [AVG_EN] is set. */
        uint64_t avg_dly               : 14; /**< [ 13:  0](R/W) Average-queue-size delay. Must be nonzero when [AVG_EN] is set. The moving average
                                                                 calculation for each CQ is performed every 1024 * ([AVG_DLY]+1) * ([LVL_DLY]+1)
                                                                 coprocessor clocks. Note the minimum value of 6144 cycles implies that at 50 M
                                                                 packets/sec, and a coprocessor clock of 800 MHz, approximately 400 packets may arrive
                                                                 between average calculations.

                                                                 Larger [LVL_DLY] and [AVG_DLY] values cause the moving averages of all CQ levels to track
                                                                 changes in the actual free space more slowly. Larger NIC_QS()_CQ()_CFG[AVG_CON] values
                                                                 causes a specific CQ to track more slowly, but only affects an individual CQ level, rather
                                                                 than all. */
#else /* Word 0 - Little Endian */
        uint64_t avg_dly               : 14; /**< [ 13:  0](R/W) Average-queue-size delay. Must be nonzero when [AVG_EN] is set. The moving average
                                                                 calculation for each CQ is performed every 1024 * ([AVG_DLY]+1) * ([LVL_DLY]+1)
                                                                 coprocessor clocks. Note the minimum value of 6144 cycles implies that at 50 M
                                                                 packets/sec, and a coprocessor clock of 800 MHz, approximately 400 packets may arrive
                                                                 between average calculations.

                                                                 Larger [LVL_DLY] and [AVG_DLY] values cause the moving averages of all CQ levels to track
                                                                 changes in the actual free space more slowly. Larger NIC_QS()_CQ()_CFG[AVG_CON] values
                                                                 causes a specific CQ to track more slowly, but only affects an individual CQ level, rather
                                                                 than all. */
        uint64_t lvl_dly               : 6;  /**< [ 19: 14](R/W) Levelizer delay. See [AVG_DLY]. Must be \>= 2 when [AVG_EN] is set. */
        uint64_t avg_en                : 1;  /**< [ 20: 20](R/W) QoS averaging enable. When set, compute average buffer levels. When clear, do not compute
                                                                 averages and save a few mW of power. */
        uint64_t reserved_21_63        : 43;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_cq_avg_cfg_s cn; */
};
typedef union bdk_nic_pf_cq_avg_cfg bdk_nic_pf_cq_avg_cfg_t;

#define BDK_NIC_PF_CQ_AVG_CFG BDK_NIC_PF_CQ_AVG_CFG_FUNC()
static inline uint64_t BDK_NIC_PF_CQ_AVG_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_CQ_AVG_CFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x8430000000c0ll;
    __bdk_csr_fatal("NIC_PF_CQ_AVG_CFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_CQ_AVG_CFG bdk_nic_pf_cq_avg_cfg_t
#define bustype_BDK_NIC_PF_CQ_AVG_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_CQ_AVG_CFG "NIC_PF_CQ_AVG_CFG"
#define device_bar_BDK_NIC_PF_CQ_AVG_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_CQ_AVG_CFG 0
#define arguments_BDK_NIC_PF_CQ_AVG_CFG -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_cqm_cfg
 *
 * NIC PF CQM Configuration Register
 */
union bdk_nic_pf_cqm_cfg
{
    uint64_t u;
    struct bdk_nic_pf_cqm_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t drop_level            : 16; /**< [ 15:  0](R/W) Drop level. The minimum available CQ space before all packets for the CQ
                                                                 are dropped. This value can be increased to insure that once a packet has
                                                                 been accepted, it will not get truncated due to buffer exhaustion.

                                                                 Must be 0x80 when any CQ is sized for 256 entries (NIC_QS()_CQ()_CFG[QSIZE]
                                                                 = 0x7). The reset value should be used otherwise. */
#else /* Word 0 - Little Endian */
        uint64_t drop_level            : 16; /**< [ 15:  0](R/W) Drop level. The minimum available CQ space before all packets for the CQ
                                                                 are dropped. This value can be increased to insure that once a packet has
                                                                 been accepted, it will not get truncated due to buffer exhaustion.

                                                                 Must be 0x80 when any CQ is sized for 256 entries (NIC_QS()_CQ()_CFG[QSIZE]
                                                                 = 0x7). The reset value should be used otherwise. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_cqm_cfg_s cn; */
};
typedef union bdk_nic_pf_cqm_cfg bdk_nic_pf_cqm_cfg_t;

#define BDK_NIC_PF_CQM_CFG BDK_NIC_PF_CQM_CFG_FUNC()
static inline uint64_t BDK_NIC_PF_CQM_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_CQM_CFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x8430000000a0ll;
    __bdk_csr_fatal("NIC_PF_CQM_CFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_CQM_CFG bdk_nic_pf_cqm_cfg_t
#define bustype_BDK_NIC_PF_CQM_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_CQM_CFG "NIC_PF_CQM_CFG"
#define device_bar_BDK_NIC_PF_CQM_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_CQM_CFG 0
#define arguments_BDK_NIC_PF_CQM_CFG -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_cqm_test
 *
 * INTERNAL: NIC CQM Test Register
 */
union bdk_nic_pf_cqm_test
{
    uint64_t u;
    struct bdk_nic_pf_cqm_test_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = cqe_gnt_cont: Stall grant to REB for continuation cache lines of a CQE.
                                                                 \<62\> = cqe_gnt_first: Stall grant to REB & SEB for first cache line of a CQE.
                                                                 \<61\> = cqe_req: Stall CQE write requests from REB & SEB.
                                                                 \<60\> = intr: Stall CQ interrupts to CSI. */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = bp_cfg3.
                                                                   \<21:20\> = bp_cfg2.
                                                                   \<19:18\> = bp_cfg1.
                                                                   \<17:16\> = bp_cfg0. */
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
                                                                   \<23:22\> = bp_cfg3.
                                                                   \<21:20\> = bp_cfg2.
                                                                   \<19:18\> = bp_cfg1.
                                                                   \<17:16\> = bp_cfg0. */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = cqe_gnt_cont: Stall grant to REB for continuation cache lines of a CQE.
                                                                 \<62\> = cqe_gnt_first: Stall grant to REB & SEB for first cache line of a CQE.
                                                                 \<61\> = cqe_req: Stall CQE write requests from REB & SEB.
                                                                 \<60\> = intr: Stall CQ interrupts to CSI. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_cqm_test_s cn; */
};
typedef union bdk_nic_pf_cqm_test bdk_nic_pf_cqm_test_t;

#define BDK_NIC_PF_CQM_TEST BDK_NIC_PF_CQM_TEST_FUNC()
static inline uint64_t BDK_NIC_PF_CQM_TEST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_CQM_TEST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x8430000000d0ll;
    __bdk_csr_fatal("NIC_PF_CQM_TEST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_CQM_TEST bdk_nic_pf_cqm_test_t
#define bustype_BDK_NIC_PF_CQM_TEST BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_CQM_TEST "NIC_PF_CQM_TEST"
#define device_bar_BDK_NIC_PF_CQM_TEST 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_CQM_TEST 0
#define arguments_BDK_NIC_PF_CQM_TEST -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_csi_test
 *
 * INTERNAL: NIC CSI Test Register
 */
union bdk_nic_pf_csi_test
{
    uint64_t u;
    struct bdk_nic_pf_csi_test_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = Reserved.
                                                                 \<61\> = Reserved.
                                                                 \<60\> = pib_stall. */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = bp_cfg3.
                                                                   \<21:20\> = bp_cfg2.
                                                                   \<19:18\> = bp_cfg1.
                                                                   \<17:16\> = bp_cfg0. */
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
                                                                   \<23:22\> = bp_cfg3.
                                                                   \<21:20\> = bp_cfg2.
                                                                   \<19:18\> = bp_cfg1.
                                                                   \<17:16\> = bp_cfg0. */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = Reserved.
                                                                 \<61\> = Reserved.
                                                                 \<60\> = pib_stall. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_csi_test_s cn; */
};
typedef union bdk_nic_pf_csi_test bdk_nic_pf_csi_test_t;

#define BDK_NIC_PF_CSI_TEST BDK_NIC_PF_CSI_TEST_FUNC()
static inline uint64_t BDK_NIC_PF_CSI_TEST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_CSI_TEST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x8430000000f0ll;
    __bdk_csr_fatal("NIC_PF_CSI_TEST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_CSI_TEST bdk_nic_pf_csi_test_t
#define bustype_BDK_NIC_PF_CSI_TEST BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_CSI_TEST "NIC_PF_CSI_TEST"
#define device_bar_BDK_NIC_PF_CSI_TEST 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_CSI_TEST 0
#define arguments_BDK_NIC_PF_CSI_TEST -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc0_cdis
 *
 * NIC Memory ECC 0 Correction Disable Register
 * This register can be used to disable ECC correction for testing. Each bit that is set disables
 * ECC correction on read operations from a corresponding RAM.
 */
union bdk_nic_pf_ecc0_cdis
{
    uint64_t u;
    struct bdk_nic_pf_ecc0_cdis_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W) Syndrome flip for group 0 block 3 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<31\>  =
                                                                 nic_l.core.reb.nic_reb_core.nic_reb_stdn_buffer.nic_reb_fifo_256x128.nic_reb_fifo
                                                                 mem_256x128.
                                                                   \<30\>  = nic_l.core.reb.nic_reb_core.nic_reb_resp_fifo.data_fifo.nic_reb_fifomem.
                                                                   \<29:20\>  =
                                                                 nic_l.core.reb.nic_reb_core.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_cq_pi
                                                                 peline.cq_main_body_fifo.nic_reb_fifo_16x128.nic_reb_fifomem_16x128.
                                                                   \<19:10\>  =
                                                                 nic_l.core.reb.nic_reb_core.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_ncx_f
                                                                 ifo.nic_reb_fifo_no_rd_lat.nic_reb_fifo.nic_reb_fifomem.
                                                                   \<9:0\>  = nic_l.core.reb.nic_reb_core.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_datap
                                                                 ath_fifo.nic_reb_fifo_bulk.nic_reb_fifomem. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W) Syndrome flip for group 0 block 2 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<15:0\> = Reserved. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W) Syndrome flip for group 0 block 1 memories.
                                                                 Internal:
                                                                 CSI memories:
                                                                   \<7:0\> = Reserved.
                                                                   \<4\>   = nic_l.core.csi.rpi.vfi.int_mem_mem.
                                                                   \<3\>   = nic_l.core.csi.rpi.msix_pmem.
                                                                   \<2\>   = nic_l.core.csi.rpi.msix_vmem.
                                                                   \<1\>   = nic_l.core.csi.mbox.mbox_mem_mem.
                                                                   \<0\>   = nic_l.core.csi.bcast.bcast_mem_mem. */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W) Syndrome flip for group 0 block 0 memories.
                                                                 Internal:
                                                                 CQM memories:
                                                                   \<7:2\> = Reserved.
                                                                   \<1\>   = nic_l.core.cqm.cin.cq_timer.cq_timer_mem.
                                                                   \<0\>   = nic_l.core.cqm.cin.cq.cq_mem. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W) Syndrome flip for group 0 block 0 memories.
                                                                 Internal:
                                                                 CQM memories:
                                                                   \<7:2\> = Reserved.
                                                                   \<1\>   = nic_l.core.cqm.cin.cq_timer.cq_timer_mem.
                                                                   \<0\>   = nic_l.core.cqm.cin.cq.cq_mem. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W) Syndrome flip for group 0 block 1 memories.
                                                                 Internal:
                                                                 CSI memories:
                                                                   \<7:0\> = Reserved.
                                                                   \<4\>   = nic_l.core.csi.rpi.vfi.int_mem_mem.
                                                                   \<3\>   = nic_l.core.csi.rpi.msix_pmem.
                                                                   \<2\>   = nic_l.core.csi.rpi.msix_vmem.
                                                                   \<1\>   = nic_l.core.csi.mbox.mbox_mem_mem.
                                                                   \<0\>   = nic_l.core.csi.bcast.bcast_mem_mem. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W) Syndrome flip for group 0 block 2 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<15:0\> = Reserved. */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W) Syndrome flip for group 0 block 3 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<31\>  =
                                                                 nic_l.core.reb.nic_reb_core.nic_reb_stdn_buffer.nic_reb_fifo_256x128.nic_reb_fifo
                                                                 mem_256x128.
                                                                   \<30\>  = nic_l.core.reb.nic_reb_core.nic_reb_resp_fifo.data_fifo.nic_reb_fifomem.
                                                                   \<29:20\>  =
                                                                 nic_l.core.reb.nic_reb_core.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_cq_pi
                                                                 peline.cq_main_body_fifo.nic_reb_fifo_16x128.nic_reb_fifomem_16x128.
                                                                   \<19:10\>  =
                                                                 nic_l.core.reb.nic_reb_core.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_ncx_f
                                                                 ifo.nic_reb_fifo_no_rd_lat.nic_reb_fifo.nic_reb_fifomem.
                                                                   \<9:0\>  = nic_l.core.reb.nic_reb_core.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_datap
                                                                 ath_fifo.nic_reb_fifo_bulk.nic_reb_fifomem. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc0_cdis_s cn8; */
    /* struct bdk_nic_pf_ecc0_cdis_s cn81xx; */
    struct bdk_nic_pf_ecc0_cdis_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W) Syndrome flip for group 0 block 3 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<31\>  =
                                                                 nic_l.nic_l1.reb.nic_reb_stdn_buffer.nic_reb_fifo_256x128.nic_reb_fifo
                                                                 mem_256x128.
                                                                   \<30\>  = nic_l.nic_l1.reb.bp_fifo.memory.
                                                                   \<29\>  = nic_l.nic_l1.reb.pknd_fifo.memory.
                                                                   \<28\>  = nic_l.nic_l1.reb.hdrs_fifo.memory.
                                                                   \<27\>  = nic_l.nic_l1.reb.qpset_cqonly_resp_fifo.memory.
                                                                   \<26\>  = nic_l.nic_l1.reb.qpset_resp_fifo.memory.
                                                                   \<25:18\> = Reserved.
                                                                   \<17:0\>  = All memories in "pipeline" blocks aliased together
                                                                 nic_l.nic_l1.reb.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_cq_pi
                                                                 peline.cq_main_body_fifo.nic_reb_fifo_16x128.nic_reb_fifomem_16x128.
                                                                   \<17:0\>  = All memories in "pipeline" blocks aliased together
                                                                 nic_l.nic_l1.reb.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_ncx_f
                                                                 ifo.nic_reb_fifo_no_rd_lat.nic_reb_fifo.nic_reb_fifomem.
                                                                   \<17:0\>  = All memories in "pipeline" blocks aliased together
                                                                 nic_l.nic_l1.reb.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_datap
                                                                 ath_fifo.nic_reb_fifo_bulk.nic_reb_fifomem. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W) Syndrome flip for group 0 block 2 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<15:0\> = Reserved. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W) Syndrome flip for group 0 block 1 memories.
                                                                 Internal:
                                                                 CSI memories:
                                                                   \<7:0\> = Reserved.
                                                                   \<4\>   = nic_l.nic_l2.csi.rpi.vfi.int_mem_mem.
                                                                   \<3\>   = nic_l.nic_l2.csi.rpi.msix_pmem.
                                                                   \<2\>   = nic_l.nic_l2.csi.rpi.msix_vmem.
                                                                   \<1\>   = nic_l.nic_l2.csi.mbox.mbox_mem_mem.
                                                                   \<0\>   = nic_l.nic_l2.csi.bcast.bcast_mem_mem. */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W) Syndrome flip for group 0 block 0 memories.
                                                                 Internal:
                                                                 CQM memories:
                                                                   \<7:2\> = Reserved.
                                                                   \<1\>   = nic_l.nic_l2.cqm.cin.cq_timer.cq_timer_mem.
                                                                   \<0\>   = nic_l.nic_l2.cqm.cin.cq.cq_mem. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W) Syndrome flip for group 0 block 0 memories.
                                                                 Internal:
                                                                 CQM memories:
                                                                   \<7:2\> = Reserved.
                                                                   \<1\>   = nic_l.nic_l2.cqm.cin.cq_timer.cq_timer_mem.
                                                                   \<0\>   = nic_l.nic_l2.cqm.cin.cq.cq_mem. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W) Syndrome flip for group 0 block 1 memories.
                                                                 Internal:
                                                                 CSI memories:
                                                                   \<7:0\> = Reserved.
                                                                   \<4\>   = nic_l.nic_l2.csi.rpi.vfi.int_mem_mem.
                                                                   \<3\>   = nic_l.nic_l2.csi.rpi.msix_pmem.
                                                                   \<2\>   = nic_l.nic_l2.csi.rpi.msix_vmem.
                                                                   \<1\>   = nic_l.nic_l2.csi.mbox.mbox_mem_mem.
                                                                   \<0\>   = nic_l.nic_l2.csi.bcast.bcast_mem_mem. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W) Syndrome flip for group 0 block 2 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<15:0\> = Reserved. */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W) Syndrome flip for group 0 block 3 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<31\>  =
                                                                 nic_l.nic_l1.reb.nic_reb_stdn_buffer.nic_reb_fifo_256x128.nic_reb_fifo
                                                                 mem_256x128.
                                                                   \<30\>  = nic_l.nic_l1.reb.bp_fifo.memory.
                                                                   \<29\>  = nic_l.nic_l1.reb.pknd_fifo.memory.
                                                                   \<28\>  = nic_l.nic_l1.reb.hdrs_fifo.memory.
                                                                   \<27\>  = nic_l.nic_l1.reb.qpset_cqonly_resp_fifo.memory.
                                                                   \<26\>  = nic_l.nic_l1.reb.qpset_resp_fifo.memory.
                                                                   \<25:18\> = Reserved.
                                                                   \<17:0\>  = All memories in "pipeline" blocks aliased together
                                                                 nic_l.nic_l1.reb.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_cq_pi
                                                                 peline.cq_main_body_fifo.nic_reb_fifo_16x128.nic_reb_fifomem_16x128.
                                                                   \<17:0\>  = All memories in "pipeline" blocks aliased together
                                                                 nic_l.nic_l1.reb.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_ncx_f
                                                                 ifo.nic_reb_fifo_no_rd_lat.nic_reb_fifo.nic_reb_fifomem.
                                                                   \<17:0\>  = All memories in "pipeline" blocks aliased together
                                                                 nic_l.nic_l1.reb.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_datap
                                                                 ath_fifo.nic_reb_fifo_bulk.nic_reb_fifomem. */
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_pf_ecc0_cdis bdk_nic_pf_ecc0_cdis_t;

#define BDK_NIC_PF_ECC0_CDIS BDK_NIC_PF_ECC0_CDIS_FUNC()
static inline uint64_t BDK_NIC_PF_ECC0_CDIS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC0_CDIS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000001100ll;
    __bdk_csr_fatal("NIC_PF_ECC0_CDIS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC0_CDIS bdk_nic_pf_ecc0_cdis_t
#define bustype_BDK_NIC_PF_ECC0_CDIS BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC0_CDIS "NIC_PF_ECC0_CDIS"
#define device_bar_BDK_NIC_PF_ECC0_CDIS 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC0_CDIS 0
#define arguments_BDK_NIC_PF_ECC0_CDIS -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc0_dbe_ena_w1c
 *
 * NIC ECC 0 Double-bit Error Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_nic_pf_ecc0_dbe_ena_w1c
{
    uint64_t u;
    struct bdk_nic_pf_ecc0_dbe_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W1C/H) Reads or clears enable for NIC_PF_ECC0_DBE_INT[BLK3]. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W1C/H) Reads or clears enable for NIC_PF_ECC0_DBE_INT[BLK2]. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W1C/H) Reads or clears enable for NIC_PF_ECC0_DBE_INT[BLK1]. */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W1C/H) Reads or clears enable for NIC_PF_ECC0_DBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W1C/H) Reads or clears enable for NIC_PF_ECC0_DBE_INT[BLK0]. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W1C/H) Reads or clears enable for NIC_PF_ECC0_DBE_INT[BLK1]. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W1C/H) Reads or clears enable for NIC_PF_ECC0_DBE_INT[BLK2]. */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W1C/H) Reads or clears enable for NIC_PF_ECC0_DBE_INT[BLK3]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc0_dbe_ena_w1c_s cn; */
};
typedef union bdk_nic_pf_ecc0_dbe_ena_w1c bdk_nic_pf_ecc0_dbe_ena_w1c_t;

#define BDK_NIC_PF_ECC0_DBE_ENA_W1C BDK_NIC_PF_ECC0_DBE_ENA_W1C_FUNC()
static inline uint64_t BDK_NIC_PF_ECC0_DBE_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC0_DBE_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002110ll;
    __bdk_csr_fatal("NIC_PF_ECC0_DBE_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC0_DBE_ENA_W1C bdk_nic_pf_ecc0_dbe_ena_w1c_t
#define bustype_BDK_NIC_PF_ECC0_DBE_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC0_DBE_ENA_W1C "NIC_PF_ECC0_DBE_ENA_W1C"
#define device_bar_BDK_NIC_PF_ECC0_DBE_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC0_DBE_ENA_W1C 0
#define arguments_BDK_NIC_PF_ECC0_DBE_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc0_dbe_ena_w1s
 *
 * NIC ECC 0 Single-bit Error Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_nic_pf_ecc0_dbe_ena_w1s
{
    uint64_t u;
    struct bdk_nic_pf_ecc0_dbe_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W1S/H) Reads or sets enable for NIC_PF_ECC0_DBE_INT[BLK3]. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W1S/H) Reads or sets enable for NIC_PF_ECC0_DBE_INT[BLK2]. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W1S/H) Reads or sets enable for NIC_PF_ECC0_DBE_INT[BLK1]. */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W1S/H) Reads or sets enable for NIC_PF_ECC0_DBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W1S/H) Reads or sets enable for NIC_PF_ECC0_DBE_INT[BLK0]. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W1S/H) Reads or sets enable for NIC_PF_ECC0_DBE_INT[BLK1]. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W1S/H) Reads or sets enable for NIC_PF_ECC0_DBE_INT[BLK2]. */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W1S/H) Reads or sets enable for NIC_PF_ECC0_DBE_INT[BLK3]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc0_dbe_ena_w1s_s cn; */
};
typedef union bdk_nic_pf_ecc0_dbe_ena_w1s bdk_nic_pf_ecc0_dbe_ena_w1s_t;

#define BDK_NIC_PF_ECC0_DBE_ENA_W1S BDK_NIC_PF_ECC0_DBE_ENA_W1S_FUNC()
static inline uint64_t BDK_NIC_PF_ECC0_DBE_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC0_DBE_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002118ll;
    __bdk_csr_fatal("NIC_PF_ECC0_DBE_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC0_DBE_ENA_W1S bdk_nic_pf_ecc0_dbe_ena_w1s_t
#define bustype_BDK_NIC_PF_ECC0_DBE_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC0_DBE_ENA_W1S "NIC_PF_ECC0_DBE_ENA_W1S"
#define device_bar_BDK_NIC_PF_ECC0_DBE_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC0_DBE_ENA_W1S 0
#define arguments_BDK_NIC_PF_ECC0_DBE_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc0_dbe_int
 *
 * NIC ECC 0 Double-bit Error Interrupt Register
 * Reports double-bit errors detected in internal RAM. Each bit corresponds to a different RAM: 0
 * = pass, 1 = fail.
 *
 * Internal:
 * Bits in each field are enumerated by NIC_PF_ECC0_FLIP0.
 */
union bdk_nic_pf_ecc0_dbe_int
{
    uint64_t u;
    struct bdk_nic_pf_ecc0_dbe_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W1C/H) RAM error on group 0 block 3 memories. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W1C/H) RAM error on group 0 block 2 memories. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W1C/H) RAM error on group 0 block 1 memories. */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W1C/H) RAM error on group 0 block 0 memories. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W1C/H) RAM error on group 0 block 0 memories. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W1C/H) RAM error on group 0 block 1 memories. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W1C/H) RAM error on group 0 block 2 memories. */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W1C/H) RAM error on group 0 block 3 memories. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc0_dbe_int_s cn; */
};
typedef union bdk_nic_pf_ecc0_dbe_int bdk_nic_pf_ecc0_dbe_int_t;

#define BDK_NIC_PF_ECC0_DBE_INT BDK_NIC_PF_ECC0_DBE_INT_FUNC()
static inline uint64_t BDK_NIC_PF_ECC0_DBE_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC0_DBE_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002100ll;
    __bdk_csr_fatal("NIC_PF_ECC0_DBE_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC0_DBE_INT bdk_nic_pf_ecc0_dbe_int_t
#define bustype_BDK_NIC_PF_ECC0_DBE_INT BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC0_DBE_INT "NIC_PF_ECC0_DBE_INT"
#define device_bar_BDK_NIC_PF_ECC0_DBE_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC0_DBE_INT 0
#define arguments_BDK_NIC_PF_ECC0_DBE_INT -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc0_dbe_int_w1s
 *
 * NIC ECC 0 Double-bit Error Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_nic_pf_ecc0_dbe_int_w1s
{
    uint64_t u;
    struct bdk_nic_pf_ecc0_dbe_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W1S/H) Reads or sets NIC_PF_ECC0_DBE_INT[BLK3]. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W1S/H) Reads or sets NIC_PF_ECC0_DBE_INT[BLK2]. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W1S/H) Reads or sets NIC_PF_ECC0_DBE_INT[BLK1]. */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W1S/H) Reads or sets NIC_PF_ECC0_DBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W1S/H) Reads or sets NIC_PF_ECC0_DBE_INT[BLK0]. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W1S/H) Reads or sets NIC_PF_ECC0_DBE_INT[BLK1]. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W1S/H) Reads or sets NIC_PF_ECC0_DBE_INT[BLK2]. */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W1S/H) Reads or sets NIC_PF_ECC0_DBE_INT[BLK3]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc0_dbe_int_w1s_s cn; */
};
typedef union bdk_nic_pf_ecc0_dbe_int_w1s bdk_nic_pf_ecc0_dbe_int_w1s_t;

#define BDK_NIC_PF_ECC0_DBE_INT_W1S BDK_NIC_PF_ECC0_DBE_INT_W1S_FUNC()
static inline uint64_t BDK_NIC_PF_ECC0_DBE_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC0_DBE_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002108ll;
    __bdk_csr_fatal("NIC_PF_ECC0_DBE_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC0_DBE_INT_W1S bdk_nic_pf_ecc0_dbe_int_w1s_t
#define bustype_BDK_NIC_PF_ECC0_DBE_INT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC0_DBE_INT_W1S "NIC_PF_ECC0_DBE_INT_W1S"
#define device_bar_BDK_NIC_PF_ECC0_DBE_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC0_DBE_INT_W1S 0
#define arguments_BDK_NIC_PF_ECC0_DBE_INT_W1S -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc0_flip0
 *
 * NIC Memory ECC 0 Flip 0 Register
 * This register allows inserting ECC errors for testing. Each bit that is set flips bit \<0\> on
 * writes to a corresponding RAM to test single-bit or double-bit error handling.
 */
union bdk_nic_pf_ecc0_flip0
{
    uint64_t u;
    struct bdk_nic_pf_ecc0_flip0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W) Syndrome flip for group 0 block 3 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<31\>  =
                                                                 nic_l.core.reb.nic_reb_core.nic_reb_stdn_buffer.nic_reb_fifo_256x128.nic_reb_fifo
                                                                 mem_256x128.
                                                                   \<30\>  = nic_l.core.reb.nic_reb_core.nic_reb_resp_fifo.data_fifo.nic_reb_fifomem.
                                                                   \<29:20\>  =
                                                                 nic_l.core.reb.nic_reb_core.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_cq_pi
                                                                 peline.cq_main_body_fifo.nic_reb_fifo_16x128.nic_reb_fifomem_16x128.
                                                                   \<19:10\>  =
                                                                 nic_l.core.reb.nic_reb_core.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_ncx_f
                                                                 ifo.nic_reb_fifo_no_rd_lat.nic_reb_fifo.nic_reb_fifomem.
                                                                   \<9:0\>  = nic_l.core.reb.nic_reb_core.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_datap
                                                                 ath_fifo.nic_reb_fifo_bulk.nic_reb_fifomem. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W) Syndrome flip for group 0 block 2 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<15:0\> = Reserved. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W) Syndrome flip for group 0 block 1 memories.
                                                                 Internal:
                                                                 CSI memories:
                                                                   \<7:0\> = Reserved.
                                                                   \<4\>   = nic_l.core.csi.rpi.vfi.int_mem_mem.
                                                                   \<3\>   = nic_l.core.csi.rpi.msix_pmem.
                                                                   \<2\>   = nic_l.core.csi.rpi.msix_vmem.
                                                                   \<1\>   = nic_l.core.csi.mbox.mbox_mem_mem.
                                                                   \<0\>   = nic_l.core.csi.bcast.bcast_mem_mem. */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W) Syndrome flip for group 0 block 0 memories.
                                                                 Internal:
                                                                 CQM memories:
                                                                   \<7:2\> = Reserved.
                                                                   \<1\>   = nic_l.core.cqm.cin.cq_timer.cq_timer_mem.
                                                                   \<0\>   = nic_l.core.cqm.cin.cq.cq_mem. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W) Syndrome flip for group 0 block 0 memories.
                                                                 Internal:
                                                                 CQM memories:
                                                                   \<7:2\> = Reserved.
                                                                   \<1\>   = nic_l.core.cqm.cin.cq_timer.cq_timer_mem.
                                                                   \<0\>   = nic_l.core.cqm.cin.cq.cq_mem. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W) Syndrome flip for group 0 block 1 memories.
                                                                 Internal:
                                                                 CSI memories:
                                                                   \<7:0\> = Reserved.
                                                                   \<4\>   = nic_l.core.csi.rpi.vfi.int_mem_mem.
                                                                   \<3\>   = nic_l.core.csi.rpi.msix_pmem.
                                                                   \<2\>   = nic_l.core.csi.rpi.msix_vmem.
                                                                   \<1\>   = nic_l.core.csi.mbox.mbox_mem_mem.
                                                                   \<0\>   = nic_l.core.csi.bcast.bcast_mem_mem. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W) Syndrome flip for group 0 block 2 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<15:0\> = Reserved. */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W) Syndrome flip for group 0 block 3 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<31\>  =
                                                                 nic_l.core.reb.nic_reb_core.nic_reb_stdn_buffer.nic_reb_fifo_256x128.nic_reb_fifo
                                                                 mem_256x128.
                                                                   \<30\>  = nic_l.core.reb.nic_reb_core.nic_reb_resp_fifo.data_fifo.nic_reb_fifomem.
                                                                   \<29:20\>  =
                                                                 nic_l.core.reb.nic_reb_core.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_cq_pi
                                                                 peline.cq_main_body_fifo.nic_reb_fifo_16x128.nic_reb_fifomem_16x128.
                                                                   \<19:10\>  =
                                                                 nic_l.core.reb.nic_reb_core.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_ncx_f
                                                                 ifo.nic_reb_fifo_no_rd_lat.nic_reb_fifo.nic_reb_fifomem.
                                                                   \<9:0\>  = nic_l.core.reb.nic_reb_core.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_datap
                                                                 ath_fifo.nic_reb_fifo_bulk.nic_reb_fifomem. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc0_flip0_s cn8; */
    /* struct bdk_nic_pf_ecc0_flip0_s cn81xx; */
    struct bdk_nic_pf_ecc0_flip0_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W) Syndrome flip for group 0 block 3 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<31\>  =
                                                                 nic_l.nic_l1.reb.nic_reb_stdn_buffer.nic_reb_fifo_256x128.nic_reb_fifo
                                                                 mem_256x128.
                                                                   \<30\>  = nic_l.nic_l1.reb.bp_fifo.memory.
                                                                   \<29\>  = nic_l.nic_l1.reb.pknd_fifo.memory.
                                                                   \<28\>  = nic_l.nic_l1.reb.hdrs_fifo.memory.
                                                                   \<27\>  = nic_l.nic_l1.reb.qpset_cqonly_resp_fifo.memory.
                                                                   \<26\>  = nic_l.nic_l1.reb.qpset_resp_fifo.memory.
                                                                   \<25:18\> = Reserved.
                                                                   \<17:0\>  = All memories in "pipeline" blocks aliased together
                                                                 nic_l.nic_l1.reb.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_cq_pi
                                                                 peline.cq_main_body_fifo.nic_reb_fifo_16x128.nic_reb_fifomem_16x128.
                                                                   \<17:0\>  = All memories in "pipeline" blocks aliased together
                                                                 nic_l.nic_l1.reb.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_ncx_f
                                                                 ifo.nic_reb_fifo_no_rd_lat.nic_reb_fifo.nic_reb_fifomem.
                                                                   \<17:0\>  = All memories in "pipeline" blocks aliased together
                                                                 nic_l.nic_l1.reb.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_datap
                                                                 ath_fifo.nic_reb_fifo_bulk.nic_reb_fifomem. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W) Syndrome flip for group 0 block 2 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<15:0\> = Reserved. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W) Syndrome flip for group 0 block 1 memories.
                                                                 Internal:
                                                                 CSI memories:
                                                                   \<7:0\> = Reserved.
                                                                   \<4\>   = nic_l.nic_l2.csi.rpi.vfi.int_mem_mem.
                                                                   \<3\>   = nic_l.nic_l2.csi.rpi.msix_pmem.
                                                                   \<2\>   = nic_l.nic_l2.csi.rpi.msix_vmem.
                                                                   \<1\>   = nic_l.nic_l2.csi.mbox.mbox_mem_mem.
                                                                   \<0\>   = nic_l.nic_l2.csi.bcast.bcast_mem_mem. */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W) Syndrome flip for group 0 block 0 memories.
                                                                 Internal:
                                                                 CQM memories:
                                                                   \<7:2\> = Reserved.
                                                                   \<1\>   = nic_l.nic_l2.cqm.cin.cq_timer.cq_timer_mem.
                                                                   \<0\>   = nic_l.nic_l2.cqm.cin.cq.cq_mem. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W) Syndrome flip for group 0 block 0 memories.
                                                                 Internal:
                                                                 CQM memories:
                                                                   \<7:2\> = Reserved.
                                                                   \<1\>   = nic_l.nic_l2.cqm.cin.cq_timer.cq_timer_mem.
                                                                   \<0\>   = nic_l.nic_l2.cqm.cin.cq.cq_mem. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W) Syndrome flip for group 0 block 1 memories.
                                                                 Internal:
                                                                 CSI memories:
                                                                   \<7:0\> = Reserved.
                                                                   \<4\>   = nic_l.nic_l2.csi.rpi.vfi.int_mem_mem.
                                                                   \<3\>   = nic_l.nic_l2.csi.rpi.msix_pmem.
                                                                   \<2\>   = nic_l.nic_l2.csi.rpi.msix_vmem.
                                                                   \<1\>   = nic_l.nic_l2.csi.mbox.mbox_mem_mem.
                                                                   \<0\>   = nic_l.nic_l2.csi.bcast.bcast_mem_mem. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W) Syndrome flip for group 0 block 2 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<15:0\> = Reserved. */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W) Syndrome flip for group 0 block 3 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<31\>  =
                                                                 nic_l.nic_l1.reb.nic_reb_stdn_buffer.nic_reb_fifo_256x128.nic_reb_fifo
                                                                 mem_256x128.
                                                                   \<30\>  = nic_l.nic_l1.reb.bp_fifo.memory.
                                                                   \<29\>  = nic_l.nic_l1.reb.pknd_fifo.memory.
                                                                   \<28\>  = nic_l.nic_l1.reb.hdrs_fifo.memory.
                                                                   \<27\>  = nic_l.nic_l1.reb.qpset_cqonly_resp_fifo.memory.
                                                                   \<26\>  = nic_l.nic_l1.reb.qpset_resp_fifo.memory.
                                                                   \<25:18\> = Reserved.
                                                                   \<17:0\>  = All memories in "pipeline" blocks aliased together
                                                                 nic_l.nic_l1.reb.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_cq_pi
                                                                 peline.cq_main_body_fifo.nic_reb_fifo_16x128.nic_reb_fifomem_16x128.
                                                                   \<17:0\>  = All memories in "pipeline" blocks aliased together
                                                                 nic_l.nic_l1.reb.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_ncx_f
                                                                 ifo.nic_reb_fifo_no_rd_lat.nic_reb_fifo.nic_reb_fifomem.
                                                                   \<17:0\>  = All memories in "pipeline" blocks aliased together
                                                                 nic_l.nic_l1.reb.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_datap
                                                                 ath_fifo.nic_reb_fifo_bulk.nic_reb_fifomem. */
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_pf_ecc0_flip0 bdk_nic_pf_ecc0_flip0_t;

#define BDK_NIC_PF_ECC0_FLIP0 BDK_NIC_PF_ECC0_FLIP0_FUNC()
static inline uint64_t BDK_NIC_PF_ECC0_FLIP0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC0_FLIP0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000001000ll;
    __bdk_csr_fatal("NIC_PF_ECC0_FLIP0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC0_FLIP0 bdk_nic_pf_ecc0_flip0_t
#define bustype_BDK_NIC_PF_ECC0_FLIP0 BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC0_FLIP0 "NIC_PF_ECC0_FLIP0"
#define device_bar_BDK_NIC_PF_ECC0_FLIP0 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC0_FLIP0 0
#define arguments_BDK_NIC_PF_ECC0_FLIP0 -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc0_flip1
 *
 * NIC Memory ECC 0 Flip 1 Register
 * This register allows inserting ECC errors for testing. Each bit that is set flips bit \<1\> on
 * writes to a corresponding RAM to test single-bit or double-bit error handling.
 */
union bdk_nic_pf_ecc0_flip1
{
    uint64_t u;
    struct bdk_nic_pf_ecc0_flip1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W) Syndrome flip for group 0 block 3 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<31\>  =
                                                                 nic_l.core.reb.nic_reb_core.nic_reb_stdn_buffer.nic_reb_fifo_256x128.nic_reb_fifo
                                                                 mem_256x128.
                                                                   \<30\>  = nic_l.core.reb.nic_reb_core.nic_reb_resp_fifo.data_fifo.nic_reb_fifomem.
                                                                   \<29:20\>  =
                                                                 nic_l.core.reb.nic_reb_core.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_cq_pi
                                                                 peline.cq_main_body_fifo.nic_reb_fifo_16x128.nic_reb_fifomem_16x128.
                                                                   \<19:10\>  =
                                                                 nic_l.core.reb.nic_reb_core.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_ncx_f
                                                                 ifo.nic_reb_fifo_no_rd_lat.nic_reb_fifo.nic_reb_fifomem.
                                                                   \<9:0\>  = nic_l.core.reb.nic_reb_core.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_datap
                                                                 ath_fifo.nic_reb_fifo_bulk.nic_reb_fifomem. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W) Syndrome flip for group 0 block 2 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<15:0\> = Reserved. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W) Syndrome flip for group 0 block 1 memories.
                                                                 Internal:
                                                                 CSI memories:
                                                                   \<7:0\> = Reserved.
                                                                   \<4\>   = nic_l.core.csi.rpi.vfi.int_mem_mem.
                                                                   \<3\>   = nic_l.core.csi.rpi.msix_pmem.
                                                                   \<2\>   = nic_l.core.csi.rpi.msix_vmem.
                                                                   \<1\>   = nic_l.core.csi.mbox.mbox_mem_mem.
                                                                   \<0\>   = nic_l.core.csi.bcast.bcast_mem_mem. */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W) Syndrome flip for group 0 block 0 memories.
                                                                 Internal:
                                                                 CQM memories:
                                                                   \<7:2\> = Reserved.
                                                                   \<1\>   = nic_l.core.cqm.cin.cq_timer.cq_timer_mem.
                                                                   \<0\>   = nic_l.core.cqm.cin.cq.cq_mem. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W) Syndrome flip for group 0 block 0 memories.
                                                                 Internal:
                                                                 CQM memories:
                                                                   \<7:2\> = Reserved.
                                                                   \<1\>   = nic_l.core.cqm.cin.cq_timer.cq_timer_mem.
                                                                   \<0\>   = nic_l.core.cqm.cin.cq.cq_mem. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W) Syndrome flip for group 0 block 1 memories.
                                                                 Internal:
                                                                 CSI memories:
                                                                   \<7:0\> = Reserved.
                                                                   \<4\>   = nic_l.core.csi.rpi.vfi.int_mem_mem.
                                                                   \<3\>   = nic_l.core.csi.rpi.msix_pmem.
                                                                   \<2\>   = nic_l.core.csi.rpi.msix_vmem.
                                                                   \<1\>   = nic_l.core.csi.mbox.mbox_mem_mem.
                                                                   \<0\>   = nic_l.core.csi.bcast.bcast_mem_mem. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W) Syndrome flip for group 0 block 2 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<15:0\> = Reserved. */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W) Syndrome flip for group 0 block 3 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<31\>  =
                                                                 nic_l.core.reb.nic_reb_core.nic_reb_stdn_buffer.nic_reb_fifo_256x128.nic_reb_fifo
                                                                 mem_256x128.
                                                                   \<30\>  = nic_l.core.reb.nic_reb_core.nic_reb_resp_fifo.data_fifo.nic_reb_fifomem.
                                                                   \<29:20\>  =
                                                                 nic_l.core.reb.nic_reb_core.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_cq_pi
                                                                 peline.cq_main_body_fifo.nic_reb_fifo_16x128.nic_reb_fifomem_16x128.
                                                                   \<19:10\>  =
                                                                 nic_l.core.reb.nic_reb_core.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_ncx_f
                                                                 ifo.nic_reb_fifo_no_rd_lat.nic_reb_fifo.nic_reb_fifomem.
                                                                   \<9:0\>  = nic_l.core.reb.nic_reb_core.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_datap
                                                                 ath_fifo.nic_reb_fifo_bulk.nic_reb_fifomem. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc0_flip1_s cn8; */
    /* struct bdk_nic_pf_ecc0_flip1_s cn81xx; */
    struct bdk_nic_pf_ecc0_flip1_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W) Syndrome flip for group 0 block 3 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<31\>  =
                                                                 nic_l.nic_l1.reb.nic_reb_stdn_buffer.nic_reb_fifo_256x128.nic_reb_fifo
                                                                 mem_256x128.
                                                                   \<30\>  = nic_l.nic_l1.reb.bp_fifo.memory.
                                                                   \<29\>  = nic_l.nic_l1.reb.pknd_fifo.memory.
                                                                   \<28\>  = nic_l.nic_l1.reb.hdrs_fifo.memory.
                                                                   \<27\>  = nic_l.nic_l1.reb.qpset_cqonly_resp_fifo.memory.
                                                                   \<26\>  = nic_l.nic_l1.reb.qpset_resp_fifo.memory.
                                                                   \<25:18\> = Reserved.
                                                                   \<17:0\>  = All memories in "pipeline" blocks aliased together
                                                                 nic_l.nic_l1.reb.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_cq_pi
                                                                 peline.cq_main_body_fifo.nic_reb_fifo_16x128.nic_reb_fifomem_16x128.
                                                                   \<17:0\>  = All memories in "pipeline" blocks aliased together
                                                                 nic_l.nic_l1.reb.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_ncx_f
                                                                 ifo.nic_reb_fifo_no_rd_lat.nic_reb_fifo.nic_reb_fifomem.
                                                                   \<17:0\>  = All memories in "pipeline" blocks aliased together
                                                                 nic_l.nic_l1.reb.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_datap
                                                                 ath_fifo.nic_reb_fifo_bulk.nic_reb_fifomem. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W) Syndrome flip for group 0 block 2 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<15:0\> = Reserved. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W) Syndrome flip for group 0 block 1 memories.
                                                                 Internal:
                                                                 CSI memories:
                                                                   \<7:0\> = Reserved.
                                                                   \<4\>   = nic_l.nic_l2.csi.rpi.vfi.int_mem_mem.
                                                                   \<3\>   = nic_l.nic_l2.csi.rpi.msix_pmem.
                                                                   \<2\>   = nic_l.nic_l2.csi.rpi.msix_vmem.
                                                                   \<1\>   = nic_l.nic_l2.csi.mbox.mbox_mem_mem.
                                                                   \<0\>   = nic_l.nic_l2.csi.bcast.bcast_mem_mem. */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W) Syndrome flip for group 0 block 0 memories.
                                                                 Internal:
                                                                 CQM memories:
                                                                   \<7:2\> = Reserved.
                                                                   \<1\>   = nic_l.nic_l2.cqm.cin.cq_timer.cq_timer_mem.
                                                                   \<0\>   = nic_l.nic_l2.cqm.cin.cq.cq_mem. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W) Syndrome flip for group 0 block 0 memories.
                                                                 Internal:
                                                                 CQM memories:
                                                                   \<7:2\> = Reserved.
                                                                   \<1\>   = nic_l.nic_l2.cqm.cin.cq_timer.cq_timer_mem.
                                                                   \<0\>   = nic_l.nic_l2.cqm.cin.cq.cq_mem. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W) Syndrome flip for group 0 block 1 memories.
                                                                 Internal:
                                                                 CSI memories:
                                                                   \<7:0\> = Reserved.
                                                                   \<4\>   = nic_l.nic_l2.csi.rpi.vfi.int_mem_mem.
                                                                   \<3\>   = nic_l.nic_l2.csi.rpi.msix_pmem.
                                                                   \<2\>   = nic_l.nic_l2.csi.rpi.msix_vmem.
                                                                   \<1\>   = nic_l.nic_l2.csi.mbox.mbox_mem_mem.
                                                                   \<0\>   = nic_l.nic_l2.csi.bcast.bcast_mem_mem. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W) Syndrome flip for group 0 block 2 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<15:0\> = Reserved. */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W) Syndrome flip for group 0 block 3 memories.
                                                                 Internal:
                                                                 REB memories:
                                                                   \<31\>  =
                                                                 nic_l.nic_l1.reb.nic_reb_stdn_buffer.nic_reb_fifo_256x128.nic_reb_fifo
                                                                 mem_256x128.
                                                                   \<30\>  = nic_l.nic_l1.reb.bp_fifo.memory.
                                                                   \<29\>  = nic_l.nic_l1.reb.pknd_fifo.memory.
                                                                   \<28\>  = nic_l.nic_l1.reb.hdrs_fifo.memory.
                                                                   \<27\>  = nic_l.nic_l1.reb.qpset_cqonly_resp_fifo.memory.
                                                                   \<26\>  = nic_l.nic_l1.reb.qpset_resp_fifo.memory.
                                                                   \<25:18\> = Reserved.
                                                                   \<17:0\>  = All memories in "pipeline" blocks aliased together
                                                                 nic_l.nic_l1.reb.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_cq_pi
                                                                 peline.cq_main_body_fifo.nic_reb_fifo_16x128.nic_reb_fifomem_16x128.
                                                                   \<17:0\>  = All memories in "pipeline" blocks aliased together
                                                                 nic_l.nic_l1.reb.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_ncx_f
                                                                 ifo.nic_reb_fifo_no_rd_lat.nic_reb_fifo.nic_reb_fifomem.
                                                                   \<17:0\>  = All memories in "pipeline" blocks aliased together
                                                                 nic_l.nic_l1.reb.reb_pipeline{7..0}.nic_reb_data_proc.nic_reb_datap
                                                                 ath_fifo.nic_reb_fifo_bulk.nic_reb_fifomem. */
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_pf_ecc0_flip1 bdk_nic_pf_ecc0_flip1_t;

#define BDK_NIC_PF_ECC0_FLIP1 BDK_NIC_PF_ECC0_FLIP1_FUNC()
static inline uint64_t BDK_NIC_PF_ECC0_FLIP1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC0_FLIP1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000001080ll;
    __bdk_csr_fatal("NIC_PF_ECC0_FLIP1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC0_FLIP1 bdk_nic_pf_ecc0_flip1_t
#define bustype_BDK_NIC_PF_ECC0_FLIP1 BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC0_FLIP1 "NIC_PF_ECC0_FLIP1"
#define device_bar_BDK_NIC_PF_ECC0_FLIP1 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC0_FLIP1 0
#define arguments_BDK_NIC_PF_ECC0_FLIP1 -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc0_sbe_ena_w1c
 *
 * NIC ECC 0 Single-bit Error Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_nic_pf_ecc0_sbe_ena_w1c
{
    uint64_t u;
    struct bdk_nic_pf_ecc0_sbe_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W1C/H) Reads or clears enable for NIC_PF_ECC0_SBE_INT[BLK3]. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W1C/H) Reads or clears enable for NIC_PF_ECC0_SBE_INT[BLK2]. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W1C/H) Reads or clears enable for NIC_PF_ECC0_SBE_INT[BLK1]. */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W1C/H) Reads or clears enable for NIC_PF_ECC0_SBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W1C/H) Reads or clears enable for NIC_PF_ECC0_SBE_INT[BLK0]. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W1C/H) Reads or clears enable for NIC_PF_ECC0_SBE_INT[BLK1]. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W1C/H) Reads or clears enable for NIC_PF_ECC0_SBE_INT[BLK2]. */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W1C/H) Reads or clears enable for NIC_PF_ECC0_SBE_INT[BLK3]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc0_sbe_ena_w1c_s cn; */
};
typedef union bdk_nic_pf_ecc0_sbe_ena_w1c bdk_nic_pf_ecc0_sbe_ena_w1c_t;

#define BDK_NIC_PF_ECC0_SBE_ENA_W1C BDK_NIC_PF_ECC0_SBE_ENA_W1C_FUNC()
static inline uint64_t BDK_NIC_PF_ECC0_SBE_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC0_SBE_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002010ll;
    __bdk_csr_fatal("NIC_PF_ECC0_SBE_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC0_SBE_ENA_W1C bdk_nic_pf_ecc0_sbe_ena_w1c_t
#define bustype_BDK_NIC_PF_ECC0_SBE_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC0_SBE_ENA_W1C "NIC_PF_ECC0_SBE_ENA_W1C"
#define device_bar_BDK_NIC_PF_ECC0_SBE_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC0_SBE_ENA_W1C 0
#define arguments_BDK_NIC_PF_ECC0_SBE_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc0_sbe_ena_w1s
 *
 * NIC ECC 0 Single-bit Error Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_nic_pf_ecc0_sbe_ena_w1s
{
    uint64_t u;
    struct bdk_nic_pf_ecc0_sbe_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W1S/H) Reads or sets enable for NIC_PF_ECC0_SBE_INT[BLK3]. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W1S/H) Reads or sets enable for NIC_PF_ECC0_SBE_INT[BLK2]. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W1S/H) Reads or sets enable for NIC_PF_ECC0_SBE_INT[BLK1]. */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W1S/H) Reads or sets enable for NIC_PF_ECC0_SBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W1S/H) Reads or sets enable for NIC_PF_ECC0_SBE_INT[BLK0]. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W1S/H) Reads or sets enable for NIC_PF_ECC0_SBE_INT[BLK1]. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W1S/H) Reads or sets enable for NIC_PF_ECC0_SBE_INT[BLK2]. */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W1S/H) Reads or sets enable for NIC_PF_ECC0_SBE_INT[BLK3]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc0_sbe_ena_w1s_s cn; */
};
typedef union bdk_nic_pf_ecc0_sbe_ena_w1s bdk_nic_pf_ecc0_sbe_ena_w1s_t;

#define BDK_NIC_PF_ECC0_SBE_ENA_W1S BDK_NIC_PF_ECC0_SBE_ENA_W1S_FUNC()
static inline uint64_t BDK_NIC_PF_ECC0_SBE_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC0_SBE_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002018ll;
    __bdk_csr_fatal("NIC_PF_ECC0_SBE_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC0_SBE_ENA_W1S bdk_nic_pf_ecc0_sbe_ena_w1s_t
#define bustype_BDK_NIC_PF_ECC0_SBE_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC0_SBE_ENA_W1S "NIC_PF_ECC0_SBE_ENA_W1S"
#define device_bar_BDK_NIC_PF_ECC0_SBE_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC0_SBE_ENA_W1S 0
#define arguments_BDK_NIC_PF_ECC0_SBE_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc0_sbe_int
 *
 * NIC ECC 0 Single-bit Error Interrupt Register
 * Reports single-bit errors detected in internal RAM. Each bit corresponds to a different RAM: 0
 * = pass, 1 = fail.
 *
 * Internal:
 * Bits in each field are enumerated by NIC_PF_ECC0_FLIP0.
 */
union bdk_nic_pf_ecc0_sbe_int
{
    uint64_t u;
    struct bdk_nic_pf_ecc0_sbe_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W1C/H) RAM error on group 0 block 3 memories. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W1C/H) RAM error on group 0 block 2 memories. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W1C/H) RAM error on group 0 block 1 memories. */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W1C/H) RAM error on group 0 block 0 memories. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W1C/H) RAM error on group 0 block 0 memories. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W1C/H) RAM error on group 0 block 1 memories. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W1C/H) RAM error on group 0 block 2 memories. */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W1C/H) RAM error on group 0 block 3 memories. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc0_sbe_int_s cn; */
};
typedef union bdk_nic_pf_ecc0_sbe_int bdk_nic_pf_ecc0_sbe_int_t;

#define BDK_NIC_PF_ECC0_SBE_INT BDK_NIC_PF_ECC0_SBE_INT_FUNC()
static inline uint64_t BDK_NIC_PF_ECC0_SBE_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC0_SBE_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002000ll;
    __bdk_csr_fatal("NIC_PF_ECC0_SBE_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC0_SBE_INT bdk_nic_pf_ecc0_sbe_int_t
#define bustype_BDK_NIC_PF_ECC0_SBE_INT BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC0_SBE_INT "NIC_PF_ECC0_SBE_INT"
#define device_bar_BDK_NIC_PF_ECC0_SBE_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC0_SBE_INT 0
#define arguments_BDK_NIC_PF_ECC0_SBE_INT -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc0_sbe_int_w1s
 *
 * NIC ECC 0 Single-bit Error Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_nic_pf_ecc0_sbe_int_w1s
{
    uint64_t u;
    struct bdk_nic_pf_ecc0_sbe_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W1S/H) Reads or sets NIC_PF_ECC0_SBE_INT[BLK3]. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W1S/H) Reads or sets NIC_PF_ECC0_SBE_INT[BLK2]. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W1S/H) Reads or sets NIC_PF_ECC0_SBE_INT[BLK1]. */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W1S/H) Reads or sets NIC_PF_ECC0_SBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 8;  /**< [  7:  0](R/W1S/H) Reads or sets NIC_PF_ECC0_SBE_INT[BLK0]. */
        uint64_t blk1                  : 8;  /**< [ 15:  8](R/W1S/H) Reads or sets NIC_PF_ECC0_SBE_INT[BLK1]. */
        uint64_t blk2                  : 16; /**< [ 31: 16](R/W1S/H) Reads or sets NIC_PF_ECC0_SBE_INT[BLK2]. */
        uint64_t blk3                  : 32; /**< [ 63: 32](R/W1S/H) Reads or sets NIC_PF_ECC0_SBE_INT[BLK3]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc0_sbe_int_w1s_s cn; */
};
typedef union bdk_nic_pf_ecc0_sbe_int_w1s bdk_nic_pf_ecc0_sbe_int_w1s_t;

#define BDK_NIC_PF_ECC0_SBE_INT_W1S BDK_NIC_PF_ECC0_SBE_INT_W1S_FUNC()
static inline uint64_t BDK_NIC_PF_ECC0_SBE_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC0_SBE_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002008ll;
    __bdk_csr_fatal("NIC_PF_ECC0_SBE_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC0_SBE_INT_W1S bdk_nic_pf_ecc0_sbe_int_w1s_t
#define bustype_BDK_NIC_PF_ECC0_SBE_INT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC0_SBE_INT_W1S "NIC_PF_ECC0_SBE_INT_W1S"
#define device_bar_BDK_NIC_PF_ECC0_SBE_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC0_SBE_INT_W1S 0
#define arguments_BDK_NIC_PF_ECC0_SBE_INT_W1S -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc1_cdis
 *
 * NIC Memory ECC 1 Correction Disable Register
 * See NIC_PF_ECC0_CDIS.
 */
union bdk_nic_pf_ecc1_cdis
{
    uint64_t u;
    struct bdk_nic_pf_ecc1_cdis_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 1 block 1 memories.
                                                                 Internal:
                                                                 RRM memories:
                                                                   \<15:7\> = Reserved.
                                                                   \<6\> = nic_l.core.rrm.nic_rrm_ptrcache.nic_rrm_ptrfifox16.nic_rrm_ptrmem.
                                                                   \<5\> = nic_l.core.rrm.nic_rrm_ncx_rsp_fifo.nic_rrm_fifo_512x86.nic_rrm_fifomem_512x86.
                                                                   \<4\> = nic_l.core.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_shadow_regs.
                                                                   \<3\> = nic_l.core.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_regs.
                                                                   \<2\> = Reserved.
                                                                   \<1\> = Reserved.
                                                                   \<0\> = nic_l.core.rrm.nic_rrm_rbdr_wrap.status1_regs. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 1 block 0 memories.
                                                                 Internal:
                                                                 RQM memories:
                                                                   \<23:20\> = Reserved.
                                                                   \<19:17\> = nic_l.core.rqm.nic_rqm_rq_wrap.mcam_wrap.mram_ecc.loop{2..0}.mem
                                                                   \<16\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_mpi_cfg_regs.
                                                                   \<15\> = nic_l.core.rqm.nic_rqm_rq_wrap.pf_qs_rq_cfg_regs.
                                                                   \<14\> = nic_l.core.rqm.nic_rqm_rq_wrap.qs_rq_gen_cfg_regs.
                                                                   \<13:11\> = nic_l.core.rqm.nic_rqm_stat_wrap.nic_rqm_stat_r_mod_w.r_mod_w_regs_{2..0}.
                                                                   \<10\> = nic_l.core.rqm.nic_rqm_bp_wrap.pf_chan_bp_cfg_regs.
                                                                   \<9\>  = nic_l.core.rqm.nic_rqm_bp_wrap.pf_qs_rq_bp_cfg_regs.
                                                                   \<8\>  = nic_l.core.rqm.nic_rqm_bp_wrap.pf_qs_rq_drop_cfg_regs.
                                                                   \<7:3\>  = nic_l.core.rqm.nic_rqm_rss_wrap.vnic_rss_key{4..0}_regs.
                                                                   \<2\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_chan_rx_cfg_regs.
                                                                   \<1\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_rssi_rq_regs.
                                                                   \<0\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_cpi_cfg_regs. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 1 block 0 memories.
                                                                 Internal:
                                                                 RQM memories:
                                                                   \<23:20\> = Reserved.
                                                                   \<19:17\> = nic_l.core.rqm.nic_rqm_rq_wrap.mcam_wrap.mram_ecc.loop{2..0}.mem
                                                                   \<16\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_mpi_cfg_regs.
                                                                   \<15\> = nic_l.core.rqm.nic_rqm_rq_wrap.pf_qs_rq_cfg_regs.
                                                                   \<14\> = nic_l.core.rqm.nic_rqm_rq_wrap.qs_rq_gen_cfg_regs.
                                                                   \<13:11\> = nic_l.core.rqm.nic_rqm_stat_wrap.nic_rqm_stat_r_mod_w.r_mod_w_regs_{2..0}.
                                                                   \<10\> = nic_l.core.rqm.nic_rqm_bp_wrap.pf_chan_bp_cfg_regs.
                                                                   \<9\>  = nic_l.core.rqm.nic_rqm_bp_wrap.pf_qs_rq_bp_cfg_regs.
                                                                   \<8\>  = nic_l.core.rqm.nic_rqm_bp_wrap.pf_qs_rq_drop_cfg_regs.
                                                                   \<7:3\>  = nic_l.core.rqm.nic_rqm_rss_wrap.vnic_rss_key{4..0}_regs.
                                                                   \<2\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_chan_rx_cfg_regs.
                                                                   \<1\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_rssi_rq_regs.
                                                                   \<0\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_cpi_cfg_regs. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 1 block 1 memories.
                                                                 Internal:
                                                                 RRM memories:
                                                                   \<15:7\> = Reserved.
                                                                   \<6\> = nic_l.core.rrm.nic_rrm_ptrcache.nic_rrm_ptrfifox16.nic_rrm_ptrmem.
                                                                   \<5\> = nic_l.core.rrm.nic_rrm_ncx_rsp_fifo.nic_rrm_fifo_512x86.nic_rrm_fifomem_512x86.
                                                                   \<4\> = nic_l.core.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_shadow_regs.
                                                                   \<3\> = nic_l.core.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_regs.
                                                                   \<2\> = Reserved.
                                                                   \<1\> = Reserved.
                                                                   \<0\> = nic_l.core.rrm.nic_rrm_rbdr_wrap.status1_regs. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc1_cdis_s cn8; */
    /* struct bdk_nic_pf_ecc1_cdis_s cn81xx; */
    struct bdk_nic_pf_ecc1_cdis_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 1 block 1 memories.
                                                                 Internal:
                                                                 RRM memories:
                                                                   \<15:7\> = Reserved.
                                                                   \<6\> = nic_l.nic_l2.rrm.nic_rrm_ptrcache.nic_rrm_ptrfifox64.nic_rrm_ptrmem.
                                                                   \<5\> = nic_l.nic_l2.rrm.nic_rrm_ncx_rsp_fifo.nic_rrm_fifo_512x86.nic_rrm_fifomem_512x86.
                                                                   \<4\> = nic_l.nic_l2.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_shadow_regs.
                                                                   \<3\> = nic_l.nic_l2.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_regs.
                                                                   \<2\> = Reserved.
                                                                   \<1\> = Reserved.
                                                                   \<0\> = nic_l.nic_l2.rrm.nic_rrm_rbdr_wrap.status1_regs. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 1 block 0 memories.
                                                                 Internal:
                                                                 RQM memories:
                                                                   \<23:21\> = Reserved.
                                                                   \<20\> = nic_l.nic_l2.nic_reb_x2p.nic_reb_resp_fifo.data_fifo.nic_reb_fifomem.
                                                                   \<19:17\> = nic_l.nic_l2.rqm.nic_rqm_rq_wrap.mcam_wrap.mram_ecc.loop{2..0}.mem
                                                                   \<16\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_mpi_cfg_regs.
                                                                   \<15\> = nic_l.nic_l2.rqm.nic_rqm_rq_wrap.pf_qs_rq_cfg_regs.
                                                                   \<14\> = nic_l.nic_l2.rqm.nic_rqm_rq_wrap.qs_rq_gen_cfg_regs.
                                                                   \<13:11\> = nic_l.nic_l2.rqm.nic_rqm_stat_wrap.nic_rqm_stat_r_mod_w.r_mod_w_regs_{2..0}.
                                                                   \<10\> = nic_l.nic_l2.rqm.nic_rqm_bp_wrap.pf_chan_bp_cfg_regs.
                                                                   \<9\>  = nic_l.nic_l2.rqm.nic_rqm_bp_wrap.pf_qs_rq_bp_cfg_regs.
                                                                   \<8\>  = nic_l.nic_l2.rqm.nic_rqm_bp_wrap.pf_qs_rq_drop_cfg_regs.
                                                                   \<7:3\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.vnic_rss_key{4..0}_regs.
                                                                   \<2\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_chan_rx_cfg_regs.
                                                                   \<1\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_rssi_rq_regs.
                                                                   \<0\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_cpi_cfg_regs. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 1 block 0 memories.
                                                                 Internal:
                                                                 RQM memories:
                                                                   \<23:21\> = Reserved.
                                                                   \<20\> = nic_l.nic_l2.nic_reb_x2p.nic_reb_resp_fifo.data_fifo.nic_reb_fifomem.
                                                                   \<19:17\> = nic_l.nic_l2.rqm.nic_rqm_rq_wrap.mcam_wrap.mram_ecc.loop{2..0}.mem
                                                                   \<16\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_mpi_cfg_regs.
                                                                   \<15\> = nic_l.nic_l2.rqm.nic_rqm_rq_wrap.pf_qs_rq_cfg_regs.
                                                                   \<14\> = nic_l.nic_l2.rqm.nic_rqm_rq_wrap.qs_rq_gen_cfg_regs.
                                                                   \<13:11\> = nic_l.nic_l2.rqm.nic_rqm_stat_wrap.nic_rqm_stat_r_mod_w.r_mod_w_regs_{2..0}.
                                                                   \<10\> = nic_l.nic_l2.rqm.nic_rqm_bp_wrap.pf_chan_bp_cfg_regs.
                                                                   \<9\>  = nic_l.nic_l2.rqm.nic_rqm_bp_wrap.pf_qs_rq_bp_cfg_regs.
                                                                   \<8\>  = nic_l.nic_l2.rqm.nic_rqm_bp_wrap.pf_qs_rq_drop_cfg_regs.
                                                                   \<7:3\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.vnic_rss_key{4..0}_regs.
                                                                   \<2\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_chan_rx_cfg_regs.
                                                                   \<1\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_rssi_rq_regs.
                                                                   \<0\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_cpi_cfg_regs. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 1 block 1 memories.
                                                                 Internal:
                                                                 RRM memories:
                                                                   \<15:7\> = Reserved.
                                                                   \<6\> = nic_l.nic_l2.rrm.nic_rrm_ptrcache.nic_rrm_ptrfifox64.nic_rrm_ptrmem.
                                                                   \<5\> = nic_l.nic_l2.rrm.nic_rrm_ncx_rsp_fifo.nic_rrm_fifo_512x86.nic_rrm_fifomem_512x86.
                                                                   \<4\> = nic_l.nic_l2.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_shadow_regs.
                                                                   \<3\> = nic_l.nic_l2.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_regs.
                                                                   \<2\> = Reserved.
                                                                   \<1\> = Reserved.
                                                                   \<0\> = nic_l.nic_l2.rrm.nic_rrm_rbdr_wrap.status1_regs. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_pf_ecc1_cdis bdk_nic_pf_ecc1_cdis_t;

#define BDK_NIC_PF_ECC1_CDIS BDK_NIC_PF_ECC1_CDIS_FUNC()
static inline uint64_t BDK_NIC_PF_ECC1_CDIS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC1_CDIS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000001108ll;
    __bdk_csr_fatal("NIC_PF_ECC1_CDIS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC1_CDIS bdk_nic_pf_ecc1_cdis_t
#define bustype_BDK_NIC_PF_ECC1_CDIS BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC1_CDIS "NIC_PF_ECC1_CDIS"
#define device_bar_BDK_NIC_PF_ECC1_CDIS 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC1_CDIS 0
#define arguments_BDK_NIC_PF_ECC1_CDIS -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc1_dbe_ena_w1c
 *
 * NIC ECC 1 Double-bit Error Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_nic_pf_ecc1_dbe_ena_w1c
{
    uint64_t u;
    struct bdk_nic_pf_ecc1_dbe_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1C/H) Reads or clears enable for NIC_PF_ECC1_DBE_INT[BLK1]. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1C/H) Reads or clears enable for NIC_PF_ECC1_DBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1C/H) Reads or clears enable for NIC_PF_ECC1_DBE_INT[BLK0]. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1C/H) Reads or clears enable for NIC_PF_ECC1_DBE_INT[BLK1]. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc1_dbe_ena_w1c_s cn; */
};
typedef union bdk_nic_pf_ecc1_dbe_ena_w1c bdk_nic_pf_ecc1_dbe_ena_w1c_t;

#define BDK_NIC_PF_ECC1_DBE_ENA_W1C BDK_NIC_PF_ECC1_DBE_ENA_W1C_FUNC()
static inline uint64_t BDK_NIC_PF_ECC1_DBE_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC1_DBE_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002310ll;
    __bdk_csr_fatal("NIC_PF_ECC1_DBE_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC1_DBE_ENA_W1C bdk_nic_pf_ecc1_dbe_ena_w1c_t
#define bustype_BDK_NIC_PF_ECC1_DBE_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC1_DBE_ENA_W1C "NIC_PF_ECC1_DBE_ENA_W1C"
#define device_bar_BDK_NIC_PF_ECC1_DBE_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC1_DBE_ENA_W1C 0
#define arguments_BDK_NIC_PF_ECC1_DBE_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc1_dbe_ena_w1s
 *
 * NIC ECC 1 Single-bit Error Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_nic_pf_ecc1_dbe_ena_w1s
{
    uint64_t u;
    struct bdk_nic_pf_ecc1_dbe_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1S/H) Reads or sets enable for NIC_PF_ECC1_DBE_INT[BLK1]. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1S/H) Reads or sets enable for NIC_PF_ECC1_DBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1S/H) Reads or sets enable for NIC_PF_ECC1_DBE_INT[BLK0]. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1S/H) Reads or sets enable for NIC_PF_ECC1_DBE_INT[BLK1]. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc1_dbe_ena_w1s_s cn; */
};
typedef union bdk_nic_pf_ecc1_dbe_ena_w1s bdk_nic_pf_ecc1_dbe_ena_w1s_t;

#define BDK_NIC_PF_ECC1_DBE_ENA_W1S BDK_NIC_PF_ECC1_DBE_ENA_W1S_FUNC()
static inline uint64_t BDK_NIC_PF_ECC1_DBE_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC1_DBE_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002318ll;
    __bdk_csr_fatal("NIC_PF_ECC1_DBE_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC1_DBE_ENA_W1S bdk_nic_pf_ecc1_dbe_ena_w1s_t
#define bustype_BDK_NIC_PF_ECC1_DBE_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC1_DBE_ENA_W1S "NIC_PF_ECC1_DBE_ENA_W1S"
#define device_bar_BDK_NIC_PF_ECC1_DBE_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC1_DBE_ENA_W1S 0
#define arguments_BDK_NIC_PF_ECC1_DBE_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc1_dbe_int
 *
 * NIC ECC 1 Double-bit Error Interrupt Register
 * Reports double-bit errors detected in internal RAM. Each bit corresponds to a different RAM: 0
 * = pass, 1 = fail.
 *
 * Internal:
 * Bits in each field are enumerated by NIC_PF_ECC1_FLIP0.
 */
union bdk_nic_pf_ecc1_dbe_int
{
    uint64_t u;
    struct bdk_nic_pf_ecc1_dbe_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1C/H) RAM error on group 1 block 1 memories. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1C/H) RAM error on group 1 block 0 memories. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1C/H) RAM error on group 1 block 0 memories. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1C/H) RAM error on group 1 block 1 memories. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc1_dbe_int_s cn; */
};
typedef union bdk_nic_pf_ecc1_dbe_int bdk_nic_pf_ecc1_dbe_int_t;

#define BDK_NIC_PF_ECC1_DBE_INT BDK_NIC_PF_ECC1_DBE_INT_FUNC()
static inline uint64_t BDK_NIC_PF_ECC1_DBE_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC1_DBE_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002300ll;
    __bdk_csr_fatal("NIC_PF_ECC1_DBE_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC1_DBE_INT bdk_nic_pf_ecc1_dbe_int_t
#define bustype_BDK_NIC_PF_ECC1_DBE_INT BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC1_DBE_INT "NIC_PF_ECC1_DBE_INT"
#define device_bar_BDK_NIC_PF_ECC1_DBE_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC1_DBE_INT 0
#define arguments_BDK_NIC_PF_ECC1_DBE_INT -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc1_dbe_int_w1s
 *
 * NIC ECC 1 Double-bit Error Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_nic_pf_ecc1_dbe_int_w1s
{
    uint64_t u;
    struct bdk_nic_pf_ecc1_dbe_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1S/H) Reads or sets NIC_PF_ECC1_DBE_INT[BLK1]. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1S/H) Reads or sets NIC_PF_ECC1_DBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1S/H) Reads or sets NIC_PF_ECC1_DBE_INT[BLK0]. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1S/H) Reads or sets NIC_PF_ECC1_DBE_INT[BLK1]. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc1_dbe_int_w1s_s cn; */
};
typedef union bdk_nic_pf_ecc1_dbe_int_w1s bdk_nic_pf_ecc1_dbe_int_w1s_t;

#define BDK_NIC_PF_ECC1_DBE_INT_W1S BDK_NIC_PF_ECC1_DBE_INT_W1S_FUNC()
static inline uint64_t BDK_NIC_PF_ECC1_DBE_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC1_DBE_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002308ll;
    __bdk_csr_fatal("NIC_PF_ECC1_DBE_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC1_DBE_INT_W1S bdk_nic_pf_ecc1_dbe_int_w1s_t
#define bustype_BDK_NIC_PF_ECC1_DBE_INT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC1_DBE_INT_W1S "NIC_PF_ECC1_DBE_INT_W1S"
#define device_bar_BDK_NIC_PF_ECC1_DBE_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC1_DBE_INT_W1S 0
#define arguments_BDK_NIC_PF_ECC1_DBE_INT_W1S -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc1_flip0
 *
 * NIC Memory ECC 1 Flip 0 Register
 * See NIC_PF_ECC0_FLIP0.
 */
union bdk_nic_pf_ecc1_flip0
{
    uint64_t u;
    struct bdk_nic_pf_ecc1_flip0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 1 block 1 memories.
                                                                 Internal:
                                                                 RRM memories:
                                                                   \<15:7\> = Reserved.
                                                                   \<6\> = nic_l.core.rrm.nic_rrm_ptrcache.nic_rrm_ptrfifox16.nic_rrm_ptrmem.
                                                                   \<5\> = nic_l.core.rrm.nic_rrm_ncx_rsp_fifo.nic_rrm_fifo_512x86.nic_rrm_fifomem_512x86.
                                                                   \<4\> = nic_l.core.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_shadow_regs.
                                                                   \<3\> = nic_l.core.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_regs.
                                                                   \<2\> = Reserved.
                                                                   \<1\> = Reserved.
                                                                   \<0\> = nic_l.core.rrm.nic_rrm_rbdr_wrap.status1_regs. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 1 block 0 memories.
                                                                 Internal:
                                                                 RQM memories:
                                                                   \<23:20\> = Reserved.
                                                                   \<19:17\> = nic_l.core.rqm.nic_rqm_rq_wrap.mcam_wrap.mram_ecc.loop{2..0}.mem
                                                                   \<16\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_mpi_cfg_regs.
                                                                   \<15\> = nic_l.core.rqm.nic_rqm_rq_wrap.pf_qs_rq_cfg_regs.
                                                                   \<14\> = nic_l.core.rqm.nic_rqm_rq_wrap.qs_rq_gen_cfg_regs.
                                                                   \<13:11\> = nic_l.core.rqm.nic_rqm_stat_wrap.nic_rqm_stat_r_mod_w.r_mod_w_regs_{2..0}.
                                                                   \<10\> = nic_l.core.rqm.nic_rqm_bp_wrap.pf_chan_bp_cfg_regs.
                                                                   \<9\>  = nic_l.core.rqm.nic_rqm_bp_wrap.pf_qs_rq_bp_cfg_regs.
                                                                   \<8\>  = nic_l.core.rqm.nic_rqm_bp_wrap.pf_qs_rq_drop_cfg_regs.
                                                                   \<7:3\>  = nic_l.core.rqm.nic_rqm_rss_wrap.vnic_rss_key{4..0}_regs.
                                                                   \<2\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_chan_rx_cfg_regs.
                                                                   \<1\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_rssi_rq_regs.
                                                                   \<0\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_cpi_cfg_regs. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 1 block 0 memories.
                                                                 Internal:
                                                                 RQM memories:
                                                                   \<23:20\> = Reserved.
                                                                   \<19:17\> = nic_l.core.rqm.nic_rqm_rq_wrap.mcam_wrap.mram_ecc.loop{2..0}.mem
                                                                   \<16\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_mpi_cfg_regs.
                                                                   \<15\> = nic_l.core.rqm.nic_rqm_rq_wrap.pf_qs_rq_cfg_regs.
                                                                   \<14\> = nic_l.core.rqm.nic_rqm_rq_wrap.qs_rq_gen_cfg_regs.
                                                                   \<13:11\> = nic_l.core.rqm.nic_rqm_stat_wrap.nic_rqm_stat_r_mod_w.r_mod_w_regs_{2..0}.
                                                                   \<10\> = nic_l.core.rqm.nic_rqm_bp_wrap.pf_chan_bp_cfg_regs.
                                                                   \<9\>  = nic_l.core.rqm.nic_rqm_bp_wrap.pf_qs_rq_bp_cfg_regs.
                                                                   \<8\>  = nic_l.core.rqm.nic_rqm_bp_wrap.pf_qs_rq_drop_cfg_regs.
                                                                   \<7:3\>  = nic_l.core.rqm.nic_rqm_rss_wrap.vnic_rss_key{4..0}_regs.
                                                                   \<2\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_chan_rx_cfg_regs.
                                                                   \<1\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_rssi_rq_regs.
                                                                   \<0\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_cpi_cfg_regs. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 1 block 1 memories.
                                                                 Internal:
                                                                 RRM memories:
                                                                   \<15:7\> = Reserved.
                                                                   \<6\> = nic_l.core.rrm.nic_rrm_ptrcache.nic_rrm_ptrfifox16.nic_rrm_ptrmem.
                                                                   \<5\> = nic_l.core.rrm.nic_rrm_ncx_rsp_fifo.nic_rrm_fifo_512x86.nic_rrm_fifomem_512x86.
                                                                   \<4\> = nic_l.core.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_shadow_regs.
                                                                   \<3\> = nic_l.core.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_regs.
                                                                   \<2\> = Reserved.
                                                                   \<1\> = Reserved.
                                                                   \<0\> = nic_l.core.rrm.nic_rrm_rbdr_wrap.status1_regs. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc1_flip0_s cn8; */
    /* struct bdk_nic_pf_ecc1_flip0_s cn81xx; */
    struct bdk_nic_pf_ecc1_flip0_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 1 block 1 memories.
                                                                 Internal:
                                                                 RRM memories:
                                                                   \<15:7\> = Reserved.
                                                                   \<6\> = nic_l.nic_l2.rrm.nic_rrm_ptrcache.nic_rrm_ptrfifox64.nic_rrm_ptrmem.
                                                                   \<5\> = nic_l.nic_l2.rrm.nic_rrm_ncx_rsp_fifo.nic_rrm_fifo_512x86.nic_rrm_fifomem_512x86.
                                                                   \<4\> = nic_l.nic_l2.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_shadow_regs.
                                                                   \<3\> = nic_l.nic_l2.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_regs.
                                                                   \<2\> = Reserved.
                                                                   \<1\> = Reserved.
                                                                   \<0\> = nic_l.nic_l2.rrm.nic_rrm_rbdr_wrap.status1_regs. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 1 block 0 memories.
                                                                 Internal:
                                                                 RQM memories:
                                                                   \<23:21\> = Reserved.
                                                                   \<20\> = nic_l.nic_l2.nic_reb_x2p.nic_reb_resp_fifo.data_fifo.nic_reb_fifomem.
                                                                   \<19:17\> = nic_l.nic_l2.rqm.nic_rqm_rq_wrap.mcam_wrap.mram_ecc.loop{2..0}.mem
                                                                   \<16\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_mpi_cfg_regs.
                                                                   \<15\> = nic_l.nic_l2.rqm.nic_rqm_rq_wrap.pf_qs_rq_cfg_regs.
                                                                   \<14\> = nic_l.nic_l2.rqm.nic_rqm_rq_wrap.qs_rq_gen_cfg_regs.
                                                                   \<13:11\> = nic_l.nic_l2.rqm.nic_rqm_stat_wrap.nic_rqm_stat_r_mod_w.r_mod_w_regs_{2..0}.
                                                                   \<10\> = nic_l.nic_l2.rqm.nic_rqm_bp_wrap.pf_chan_bp_cfg_regs.
                                                                   \<9\>  = nic_l.nic_l2.rqm.nic_rqm_bp_wrap.pf_qs_rq_bp_cfg_regs.
                                                                   \<8\>  = nic_l.nic_l2.rqm.nic_rqm_bp_wrap.pf_qs_rq_drop_cfg_regs.
                                                                   \<7:3\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.vnic_rss_key{4..0}_regs.
                                                                   \<2\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_chan_rx_cfg_regs.
                                                                   \<1\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_rssi_rq_regs.
                                                                   \<0\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_cpi_cfg_regs. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 1 block 0 memories.
                                                                 Internal:
                                                                 RQM memories:
                                                                   \<23:21\> = Reserved.
                                                                   \<20\> = nic_l.nic_l2.nic_reb_x2p.nic_reb_resp_fifo.data_fifo.nic_reb_fifomem.
                                                                   \<19:17\> = nic_l.nic_l2.rqm.nic_rqm_rq_wrap.mcam_wrap.mram_ecc.loop{2..0}.mem
                                                                   \<16\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_mpi_cfg_regs.
                                                                   \<15\> = nic_l.nic_l2.rqm.nic_rqm_rq_wrap.pf_qs_rq_cfg_regs.
                                                                   \<14\> = nic_l.nic_l2.rqm.nic_rqm_rq_wrap.qs_rq_gen_cfg_regs.
                                                                   \<13:11\> = nic_l.nic_l2.rqm.nic_rqm_stat_wrap.nic_rqm_stat_r_mod_w.r_mod_w_regs_{2..0}.
                                                                   \<10\> = nic_l.nic_l2.rqm.nic_rqm_bp_wrap.pf_chan_bp_cfg_regs.
                                                                   \<9\>  = nic_l.nic_l2.rqm.nic_rqm_bp_wrap.pf_qs_rq_bp_cfg_regs.
                                                                   \<8\>  = nic_l.nic_l2.rqm.nic_rqm_bp_wrap.pf_qs_rq_drop_cfg_regs.
                                                                   \<7:3\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.vnic_rss_key{4..0}_regs.
                                                                   \<2\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_chan_rx_cfg_regs.
                                                                   \<1\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_rssi_rq_regs.
                                                                   \<0\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_cpi_cfg_regs. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 1 block 1 memories.
                                                                 Internal:
                                                                 RRM memories:
                                                                   \<15:7\> = Reserved.
                                                                   \<6\> = nic_l.nic_l2.rrm.nic_rrm_ptrcache.nic_rrm_ptrfifox64.nic_rrm_ptrmem.
                                                                   \<5\> = nic_l.nic_l2.rrm.nic_rrm_ncx_rsp_fifo.nic_rrm_fifo_512x86.nic_rrm_fifomem_512x86.
                                                                   \<4\> = nic_l.nic_l2.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_shadow_regs.
                                                                   \<3\> = nic_l.nic_l2.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_regs.
                                                                   \<2\> = Reserved.
                                                                   \<1\> = Reserved.
                                                                   \<0\> = nic_l.nic_l2.rrm.nic_rrm_rbdr_wrap.status1_regs. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_pf_ecc1_flip0 bdk_nic_pf_ecc1_flip0_t;

#define BDK_NIC_PF_ECC1_FLIP0 BDK_NIC_PF_ECC1_FLIP0_FUNC()
static inline uint64_t BDK_NIC_PF_ECC1_FLIP0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC1_FLIP0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000001008ll;
    __bdk_csr_fatal("NIC_PF_ECC1_FLIP0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC1_FLIP0 bdk_nic_pf_ecc1_flip0_t
#define bustype_BDK_NIC_PF_ECC1_FLIP0 BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC1_FLIP0 "NIC_PF_ECC1_FLIP0"
#define device_bar_BDK_NIC_PF_ECC1_FLIP0 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC1_FLIP0 0
#define arguments_BDK_NIC_PF_ECC1_FLIP0 -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc1_flip1
 *
 * NIC Memory ECC 1 Flip 1 Register
 * See NIC_PF_ECC0_FLIP1.
 */
union bdk_nic_pf_ecc1_flip1
{
    uint64_t u;
    struct bdk_nic_pf_ecc1_flip1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 1 block 1 memories.
                                                                 Internal:
                                                                 RRM memories:
                                                                   \<15:7\> = Reserved.
                                                                   \<6\> = nic_l.core.rrm.nic_rrm_ptrcache.nic_rrm_ptrfifox16.nic_rrm_ptrmem.
                                                                   \<5\> = nic_l.core.rrm.nic_rrm_ncx_rsp_fifo.nic_rrm_fifo_512x86.nic_rrm_fifomem_512x86.
                                                                   \<4\> = nic_l.core.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_shadow_regs.
                                                                   \<3\> = nic_l.core.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_regs.
                                                                   \<2\> = Reserved.
                                                                   \<1\> = Reserved.
                                                                   \<0\> = nic_l.core.rrm.nic_rrm_rbdr_wrap.status1_regs. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 1 block 0 memories.
                                                                 Internal:
                                                                 RQM memories:
                                                                   \<23:20\> = Reserved.
                                                                   \<19:17\> = nic_l.core.rqm.nic_rqm_rq_wrap.mcam_wrap.mram_ecc.loop{2..0}.mem
                                                                   \<16\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_mpi_cfg_regs.
                                                                   \<15\> = nic_l.core.rqm.nic_rqm_rq_wrap.pf_qs_rq_cfg_regs.
                                                                   \<14\> = nic_l.core.rqm.nic_rqm_rq_wrap.qs_rq_gen_cfg_regs.
                                                                   \<13:11\> = nic_l.core.rqm.nic_rqm_stat_wrap.nic_rqm_stat_r_mod_w.r_mod_w_regs_{2..0}.
                                                                   \<10\> = nic_l.core.rqm.nic_rqm_bp_wrap.pf_chan_bp_cfg_regs.
                                                                   \<9\>  = nic_l.core.rqm.nic_rqm_bp_wrap.pf_qs_rq_bp_cfg_regs.
                                                                   \<8\>  = nic_l.core.rqm.nic_rqm_bp_wrap.pf_qs_rq_drop_cfg_regs.
                                                                   \<7:3\>  = nic_l.core.rqm.nic_rqm_rss_wrap.vnic_rss_key{4..0}_regs.
                                                                   \<2\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_chan_rx_cfg_regs.
                                                                   \<1\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_rssi_rq_regs.
                                                                   \<0\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_cpi_cfg_regs. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 1 block 0 memories.
                                                                 Internal:
                                                                 RQM memories:
                                                                   \<23:20\> = Reserved.
                                                                   \<19:17\> = nic_l.core.rqm.nic_rqm_rq_wrap.mcam_wrap.mram_ecc.loop{2..0}.mem
                                                                   \<16\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_mpi_cfg_regs.
                                                                   \<15\> = nic_l.core.rqm.nic_rqm_rq_wrap.pf_qs_rq_cfg_regs.
                                                                   \<14\> = nic_l.core.rqm.nic_rqm_rq_wrap.qs_rq_gen_cfg_regs.
                                                                   \<13:11\> = nic_l.core.rqm.nic_rqm_stat_wrap.nic_rqm_stat_r_mod_w.r_mod_w_regs_{2..0}.
                                                                   \<10\> = nic_l.core.rqm.nic_rqm_bp_wrap.pf_chan_bp_cfg_regs.
                                                                   \<9\>  = nic_l.core.rqm.nic_rqm_bp_wrap.pf_qs_rq_bp_cfg_regs.
                                                                   \<8\>  = nic_l.core.rqm.nic_rqm_bp_wrap.pf_qs_rq_drop_cfg_regs.
                                                                   \<7:3\>  = nic_l.core.rqm.nic_rqm_rss_wrap.vnic_rss_key{4..0}_regs.
                                                                   \<2\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_chan_rx_cfg_regs.
                                                                   \<1\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_rssi_rq_regs.
                                                                   \<0\>  = nic_l.core.rqm.nic_rqm_rss_wrap.nic_pf_cpi_cfg_regs. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 1 block 1 memories.
                                                                 Internal:
                                                                 RRM memories:
                                                                   \<15:7\> = Reserved.
                                                                   \<6\> = nic_l.core.rrm.nic_rrm_ptrcache.nic_rrm_ptrfifox16.nic_rrm_ptrmem.
                                                                   \<5\> = nic_l.core.rrm.nic_rrm_ncx_rsp_fifo.nic_rrm_fifo_512x86.nic_rrm_fifomem_512x86.
                                                                   \<4\> = nic_l.core.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_shadow_regs.
                                                                   \<3\> = nic_l.core.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_regs.
                                                                   \<2\> = Reserved.
                                                                   \<1\> = Reserved.
                                                                   \<0\> = nic_l.core.rrm.nic_rrm_rbdr_wrap.status1_regs. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc1_flip1_s cn8; */
    /* struct bdk_nic_pf_ecc1_flip1_s cn81xx; */
    struct bdk_nic_pf_ecc1_flip1_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 1 block 1 memories.
                                                                 Internal:
                                                                 RRM memories:
                                                                   \<15:7\> = Reserved.
                                                                   \<6\> = nic_l.nic_l2.rrm.nic_rrm_ptrcache.nic_rrm_ptrfifox64.nic_rrm_ptrmem.
                                                                   \<5\> = nic_l.nic_l2.rrm.nic_rrm_ncx_rsp_fifo.nic_rrm_fifo_512x86.nic_rrm_fifomem_512x86.
                                                                   \<4\> = nic_l.nic_l2.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_shadow_regs.
                                                                   \<3\> = nic_l.nic_l2.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_regs.
                                                                   \<2\> = Reserved.
                                                                   \<1\> = Reserved.
                                                                   \<0\> = nic_l.nic_l2.rrm.nic_rrm_rbdr_wrap.status1_regs. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 1 block 0 memories.
                                                                 Internal:
                                                                 RQM memories:
                                                                   \<23:21\> = Reserved.
                                                                   \<20\> = nic_l.nic_l2.nic_reb_x2p.nic_reb_resp_fifo.data_fifo.nic_reb_fifomem.
                                                                   \<19:17\> = nic_l.nic_l2.rqm.nic_rqm_rq_wrap.mcam_wrap.mram_ecc.loop{2..0}.mem
                                                                   \<16\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_mpi_cfg_regs.
                                                                   \<15\> = nic_l.nic_l2.rqm.nic_rqm_rq_wrap.pf_qs_rq_cfg_regs.
                                                                   \<14\> = nic_l.nic_l2.rqm.nic_rqm_rq_wrap.qs_rq_gen_cfg_regs.
                                                                   \<13:11\> = nic_l.nic_l2.rqm.nic_rqm_stat_wrap.nic_rqm_stat_r_mod_w.r_mod_w_regs_{2..0}.
                                                                   \<10\> = nic_l.nic_l2.rqm.nic_rqm_bp_wrap.pf_chan_bp_cfg_regs.
                                                                   \<9\>  = nic_l.nic_l2.rqm.nic_rqm_bp_wrap.pf_qs_rq_bp_cfg_regs.
                                                                   \<8\>  = nic_l.nic_l2.rqm.nic_rqm_bp_wrap.pf_qs_rq_drop_cfg_regs.
                                                                   \<7:3\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.vnic_rss_key{4..0}_regs.
                                                                   \<2\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_chan_rx_cfg_regs.
                                                                   \<1\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_rssi_rq_regs.
                                                                   \<0\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_cpi_cfg_regs. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 1 block 0 memories.
                                                                 Internal:
                                                                 RQM memories:
                                                                   \<23:21\> = Reserved.
                                                                   \<20\> = nic_l.nic_l2.nic_reb_x2p.nic_reb_resp_fifo.data_fifo.nic_reb_fifomem.
                                                                   \<19:17\> = nic_l.nic_l2.rqm.nic_rqm_rq_wrap.mcam_wrap.mram_ecc.loop{2..0}.mem
                                                                   \<16\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_mpi_cfg_regs.
                                                                   \<15\> = nic_l.nic_l2.rqm.nic_rqm_rq_wrap.pf_qs_rq_cfg_regs.
                                                                   \<14\> = nic_l.nic_l2.rqm.nic_rqm_rq_wrap.qs_rq_gen_cfg_regs.
                                                                   \<13:11\> = nic_l.nic_l2.rqm.nic_rqm_stat_wrap.nic_rqm_stat_r_mod_w.r_mod_w_regs_{2..0}.
                                                                   \<10\> = nic_l.nic_l2.rqm.nic_rqm_bp_wrap.pf_chan_bp_cfg_regs.
                                                                   \<9\>  = nic_l.nic_l2.rqm.nic_rqm_bp_wrap.pf_qs_rq_bp_cfg_regs.
                                                                   \<8\>  = nic_l.nic_l2.rqm.nic_rqm_bp_wrap.pf_qs_rq_drop_cfg_regs.
                                                                   \<7:3\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.vnic_rss_key{4..0}_regs.
                                                                   \<2\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_chan_rx_cfg_regs.
                                                                   \<1\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_rssi_rq_regs.
                                                                   \<0\>  = nic_l.nic_l2.rqm.nic_rqm_rss_wrap.nic_pf_cpi_cfg_regs. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 1 block 1 memories.
                                                                 Internal:
                                                                 RRM memories:
                                                                   \<15:7\> = Reserved.
                                                                   \<6\> = nic_l.nic_l2.rrm.nic_rrm_ptrcache.nic_rrm_ptrfifox64.nic_rrm_ptrmem.
                                                                   \<5\> = nic_l.nic_l2.rrm.nic_rrm_ncx_rsp_fifo.nic_rrm_fifo_512x86.nic_rrm_fifomem_512x86.
                                                                   \<4\> = nic_l.nic_l2.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_shadow_regs.
                                                                   \<3\> = nic_l.nic_l2.rrm.nic_rrm_rbdr_wrap.nic_rrm_r_mod_w_block.r_mod_w_regs.
                                                                   \<2\> = Reserved.
                                                                   \<1\> = Reserved.
                                                                   \<0\> = nic_l.nic_l2.rrm.nic_rrm_rbdr_wrap.status1_regs. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_pf_ecc1_flip1 bdk_nic_pf_ecc1_flip1_t;

#define BDK_NIC_PF_ECC1_FLIP1 BDK_NIC_PF_ECC1_FLIP1_FUNC()
static inline uint64_t BDK_NIC_PF_ECC1_FLIP1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC1_FLIP1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000001088ll;
    __bdk_csr_fatal("NIC_PF_ECC1_FLIP1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC1_FLIP1 bdk_nic_pf_ecc1_flip1_t
#define bustype_BDK_NIC_PF_ECC1_FLIP1 BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC1_FLIP1 "NIC_PF_ECC1_FLIP1"
#define device_bar_BDK_NIC_PF_ECC1_FLIP1 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC1_FLIP1 0
#define arguments_BDK_NIC_PF_ECC1_FLIP1 -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc1_sbe_ena_w1c
 *
 * NIC ECC 1 Single-bit Error Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_nic_pf_ecc1_sbe_ena_w1c
{
    uint64_t u;
    struct bdk_nic_pf_ecc1_sbe_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1C/H) Reads or clears enable for NIC_PF_ECC1_SBE_INT[BLK1]. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1C/H) Reads or clears enable for NIC_PF_ECC1_SBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1C/H) Reads or clears enable for NIC_PF_ECC1_SBE_INT[BLK0]. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1C/H) Reads or clears enable for NIC_PF_ECC1_SBE_INT[BLK1]. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc1_sbe_ena_w1c_s cn; */
};
typedef union bdk_nic_pf_ecc1_sbe_ena_w1c bdk_nic_pf_ecc1_sbe_ena_w1c_t;

#define BDK_NIC_PF_ECC1_SBE_ENA_W1C BDK_NIC_PF_ECC1_SBE_ENA_W1C_FUNC()
static inline uint64_t BDK_NIC_PF_ECC1_SBE_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC1_SBE_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002210ll;
    __bdk_csr_fatal("NIC_PF_ECC1_SBE_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC1_SBE_ENA_W1C bdk_nic_pf_ecc1_sbe_ena_w1c_t
#define bustype_BDK_NIC_PF_ECC1_SBE_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC1_SBE_ENA_W1C "NIC_PF_ECC1_SBE_ENA_W1C"
#define device_bar_BDK_NIC_PF_ECC1_SBE_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC1_SBE_ENA_W1C 0
#define arguments_BDK_NIC_PF_ECC1_SBE_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc1_sbe_ena_w1s
 *
 * NIC ECC 1 Single-bit Error Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_nic_pf_ecc1_sbe_ena_w1s
{
    uint64_t u;
    struct bdk_nic_pf_ecc1_sbe_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1S/H) Reads or sets enable for NIC_PF_ECC1_SBE_INT[BLK1]. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1S/H) Reads or sets enable for NIC_PF_ECC1_SBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1S/H) Reads or sets enable for NIC_PF_ECC1_SBE_INT[BLK0]. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1S/H) Reads or sets enable for NIC_PF_ECC1_SBE_INT[BLK1]. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc1_sbe_ena_w1s_s cn; */
};
typedef union bdk_nic_pf_ecc1_sbe_ena_w1s bdk_nic_pf_ecc1_sbe_ena_w1s_t;

#define BDK_NIC_PF_ECC1_SBE_ENA_W1S BDK_NIC_PF_ECC1_SBE_ENA_W1S_FUNC()
static inline uint64_t BDK_NIC_PF_ECC1_SBE_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC1_SBE_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002218ll;
    __bdk_csr_fatal("NIC_PF_ECC1_SBE_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC1_SBE_ENA_W1S bdk_nic_pf_ecc1_sbe_ena_w1s_t
#define bustype_BDK_NIC_PF_ECC1_SBE_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC1_SBE_ENA_W1S "NIC_PF_ECC1_SBE_ENA_W1S"
#define device_bar_BDK_NIC_PF_ECC1_SBE_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC1_SBE_ENA_W1S 0
#define arguments_BDK_NIC_PF_ECC1_SBE_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc1_sbe_int
 *
 * NIC ECC 1 Single-bit Error Interrupt Register
 * Reports single-bit errors detected in internal RAM. Each bit corresponds to a different RAM: 0
 * = pass, 1 = fail.
 *
 * Internal:
 * Bits in each field are enumerated by NIC_PF_ECC1_FLIP0.
 */
union bdk_nic_pf_ecc1_sbe_int
{
    uint64_t u;
    struct bdk_nic_pf_ecc1_sbe_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1C/H) RAM error on group 1 block 1 memories. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1C/H) RAM error on group 1 block 0 memories. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1C/H) RAM error on group 1 block 0 memories. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1C/H) RAM error on group 1 block 1 memories. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc1_sbe_int_s cn; */
};
typedef union bdk_nic_pf_ecc1_sbe_int bdk_nic_pf_ecc1_sbe_int_t;

#define BDK_NIC_PF_ECC1_SBE_INT BDK_NIC_PF_ECC1_SBE_INT_FUNC()
static inline uint64_t BDK_NIC_PF_ECC1_SBE_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC1_SBE_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002200ll;
    __bdk_csr_fatal("NIC_PF_ECC1_SBE_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC1_SBE_INT bdk_nic_pf_ecc1_sbe_int_t
#define bustype_BDK_NIC_PF_ECC1_SBE_INT BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC1_SBE_INT "NIC_PF_ECC1_SBE_INT"
#define device_bar_BDK_NIC_PF_ECC1_SBE_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC1_SBE_INT 0
#define arguments_BDK_NIC_PF_ECC1_SBE_INT -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc1_sbe_int_w1s
 *
 * NIC ECC 1 Single-bit Error Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_nic_pf_ecc1_sbe_int_w1s
{
    uint64_t u;
    struct bdk_nic_pf_ecc1_sbe_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1S/H) Reads or sets NIC_PF_ECC1_SBE_INT[BLK1]. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1S/H) Reads or sets NIC_PF_ECC1_SBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1S/H) Reads or sets NIC_PF_ECC1_SBE_INT[BLK0]. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1S/H) Reads or sets NIC_PF_ECC1_SBE_INT[BLK1]. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc1_sbe_int_w1s_s cn; */
};
typedef union bdk_nic_pf_ecc1_sbe_int_w1s bdk_nic_pf_ecc1_sbe_int_w1s_t;

#define BDK_NIC_PF_ECC1_SBE_INT_W1S BDK_NIC_PF_ECC1_SBE_INT_W1S_FUNC()
static inline uint64_t BDK_NIC_PF_ECC1_SBE_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC1_SBE_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002208ll;
    __bdk_csr_fatal("NIC_PF_ECC1_SBE_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC1_SBE_INT_W1S bdk_nic_pf_ecc1_sbe_int_w1s_t
#define bustype_BDK_NIC_PF_ECC1_SBE_INT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC1_SBE_INT_W1S "NIC_PF_ECC1_SBE_INT_W1S"
#define device_bar_BDK_NIC_PF_ECC1_SBE_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC1_SBE_INT_W1S 0
#define arguments_BDK_NIC_PF_ECC1_SBE_INT_W1S -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc2_cdis
 *
 * NIC Memory ECC 2 Correction Disable Register
 * See NIC_PF_ECC0_CDIS.
 */
union bdk_nic_pf_ecc2_cdis
{
    uint64_t u;
    struct bdk_nic_pf_ecc2_cdis_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t blk0                  : 50; /**< [ 49:  0](R/W) Syndrome flip for group 2 block 0 memories.
                                                                 Internal:
                                                                 SEB memories.
                                                                 \<49:22\> = Reserved.
                                                                 \<21\>    = nic.nic_u.nic_u1.seb.mem.dmem.tso_crc.
                                                                 \<20\>    = nic.nic_u.nic_u1.seb.mem.dmem.simm.
                                                                 \<19\>    = nic.nic_u.nic_u1.seb.mem.dmem.sgth.
                                                                 \<18\>    = nic.nic_u.nic_u1.seb.mem.dmem.dsze.
                                                                 \<17\>    = nic.nic_u.nic_u1.seb.mem.dmem.lock_data.
                                                                 \<16\>    = nic.nic_u.nic_u1.seb.mem.dmem.lock_be
                                                                 \<15\>    = nic.nic_u.nic_u1.seb.mem.imem.crc_drf.
                                                                 \<14\>    = nic.nic_u.nic_u1.seb.mem.imem.smem_drf.
                                                                 \<13\>    = nic.nic_u.nic_u1.seb.ctx.lctx_dw0_drf.
                                                                 \<12\>    = nic.nic_u.nic_u1.seb.ctx.lctx_dw1_drf.
                                                                 \<11\>    = nic.nic_u.nic_u1.seb.ctx.eod_drf.
                                                                 \<10\>    = nic.nic_u.nic_u1.seb.ctx.gctx_drf.
                                                                 \<9:8\>   = nic.nic_u.nic_u1.seb.smc.smem_cq_context{1..0}.smem_cq_ctx.
                                                                 \<7\>     = nic.nic_u.nic_u1.seb.smc.smem_cq_stdn.
                                                                 \<6\>     = nic.nic_u.nic_u1.seb.ncx_intf.sgth_cmd.
                                                                 \<5:4\>   = nic.nic_u.nic_u1.seb.p2x_intf.tx_fifo_mem{1..0}.tx_fifo.
                                                                 \<3:2\>   = nic.nic_u.nic_u1.seb.p2x_intf.tx_fifo_mem{1..0}.p2x_sop_hdr.
                                                                 \<1:0\>   = nic.nic_u.nic_u1.seb.p2x_intf.tx_fifo_mem{1..0}.p2x_eop_hdr. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 50; /**< [ 49:  0](R/W) Syndrome flip for group 2 block 0 memories.
                                                                 Internal:
                                                                 SEB memories.
                                                                 \<49:22\> = Reserved.
                                                                 \<21\>    = nic.nic_u.nic_u1.seb.mem.dmem.tso_crc.
                                                                 \<20\>    = nic.nic_u.nic_u1.seb.mem.dmem.simm.
                                                                 \<19\>    = nic.nic_u.nic_u1.seb.mem.dmem.sgth.
                                                                 \<18\>    = nic.nic_u.nic_u1.seb.mem.dmem.dsze.
                                                                 \<17\>    = nic.nic_u.nic_u1.seb.mem.dmem.lock_data.
                                                                 \<16\>    = nic.nic_u.nic_u1.seb.mem.dmem.lock_be
                                                                 \<15\>    = nic.nic_u.nic_u1.seb.mem.imem.crc_drf.
                                                                 \<14\>    = nic.nic_u.nic_u1.seb.mem.imem.smem_drf.
                                                                 \<13\>    = nic.nic_u.nic_u1.seb.ctx.lctx_dw0_drf.
                                                                 \<12\>    = nic.nic_u.nic_u1.seb.ctx.lctx_dw1_drf.
                                                                 \<11\>    = nic.nic_u.nic_u1.seb.ctx.eod_drf.
                                                                 \<10\>    = nic.nic_u.nic_u1.seb.ctx.gctx_drf.
                                                                 \<9:8\>   = nic.nic_u.nic_u1.seb.smc.smem_cq_context{1..0}.smem_cq_ctx.
                                                                 \<7\>     = nic.nic_u.nic_u1.seb.smc.smem_cq_stdn.
                                                                 \<6\>     = nic.nic_u.nic_u1.seb.ncx_intf.sgth_cmd.
                                                                 \<5:4\>   = nic.nic_u.nic_u1.seb.p2x_intf.tx_fifo_mem{1..0}.tx_fifo.
                                                                 \<3:2\>   = nic.nic_u.nic_u1.seb.p2x_intf.tx_fifo_mem{1..0}.p2x_sop_hdr.
                                                                 \<1:0\>   = nic.nic_u.nic_u1.seb.p2x_intf.tx_fifo_mem{1..0}.p2x_eop_hdr. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc2_cdis_s cn; */
};
typedef union bdk_nic_pf_ecc2_cdis bdk_nic_pf_ecc2_cdis_t;

#define BDK_NIC_PF_ECC2_CDIS BDK_NIC_PF_ECC2_CDIS_FUNC()
static inline uint64_t BDK_NIC_PF_ECC2_CDIS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC2_CDIS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000001110ll;
    __bdk_csr_fatal("NIC_PF_ECC2_CDIS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC2_CDIS bdk_nic_pf_ecc2_cdis_t
#define bustype_BDK_NIC_PF_ECC2_CDIS BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC2_CDIS "NIC_PF_ECC2_CDIS"
#define device_bar_BDK_NIC_PF_ECC2_CDIS 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC2_CDIS 0
#define arguments_BDK_NIC_PF_ECC2_CDIS -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc2_dbe_ena_w1c
 *
 * NIC ECC 2 Double-bit Error Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_nic_pf_ecc2_dbe_ena_w1c
{
    uint64_t u;
    struct bdk_nic_pf_ecc2_dbe_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t blk0                  : 50; /**< [ 49:  0](R/W1C/H) Reads or clears enable for NIC_PF_ECC2_DBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 50; /**< [ 49:  0](R/W1C/H) Reads or clears enable for NIC_PF_ECC2_DBE_INT[BLK0]. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc2_dbe_ena_w1c_s cn; */
};
typedef union bdk_nic_pf_ecc2_dbe_ena_w1c bdk_nic_pf_ecc2_dbe_ena_w1c_t;

#define BDK_NIC_PF_ECC2_DBE_ENA_W1C BDK_NIC_PF_ECC2_DBE_ENA_W1C_FUNC()
static inline uint64_t BDK_NIC_PF_ECC2_DBE_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC2_DBE_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002510ll;
    __bdk_csr_fatal("NIC_PF_ECC2_DBE_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC2_DBE_ENA_W1C bdk_nic_pf_ecc2_dbe_ena_w1c_t
#define bustype_BDK_NIC_PF_ECC2_DBE_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC2_DBE_ENA_W1C "NIC_PF_ECC2_DBE_ENA_W1C"
#define device_bar_BDK_NIC_PF_ECC2_DBE_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC2_DBE_ENA_W1C 0
#define arguments_BDK_NIC_PF_ECC2_DBE_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc2_dbe_ena_w1s
 *
 * NIC ECC 2 Single-bit Error Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_nic_pf_ecc2_dbe_ena_w1s
{
    uint64_t u;
    struct bdk_nic_pf_ecc2_dbe_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t blk0                  : 50; /**< [ 49:  0](R/W1S/H) Reads or sets enable for NIC_PF_ECC2_DBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 50; /**< [ 49:  0](R/W1S/H) Reads or sets enable for NIC_PF_ECC2_DBE_INT[BLK0]. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc2_dbe_ena_w1s_s cn; */
};
typedef union bdk_nic_pf_ecc2_dbe_ena_w1s bdk_nic_pf_ecc2_dbe_ena_w1s_t;

#define BDK_NIC_PF_ECC2_DBE_ENA_W1S BDK_NIC_PF_ECC2_DBE_ENA_W1S_FUNC()
static inline uint64_t BDK_NIC_PF_ECC2_DBE_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC2_DBE_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002518ll;
    __bdk_csr_fatal("NIC_PF_ECC2_DBE_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC2_DBE_ENA_W1S bdk_nic_pf_ecc2_dbe_ena_w1s_t
#define bustype_BDK_NIC_PF_ECC2_DBE_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC2_DBE_ENA_W1S "NIC_PF_ECC2_DBE_ENA_W1S"
#define device_bar_BDK_NIC_PF_ECC2_DBE_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC2_DBE_ENA_W1S 0
#define arguments_BDK_NIC_PF_ECC2_DBE_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc2_dbe_int
 *
 * NIC ECC 2 Double-bit Error Interrupt Register
 * Reports double-bit errors detected in internal RAM. Each bit corresponds to a different RAM: 0
 * = pass, 1 = fail.
 *
 * Internal:
 * Bits in each field are enumerated by NIC_PF_ECC2_FLIP0.
 */
union bdk_nic_pf_ecc2_dbe_int
{
    uint64_t u;
    struct bdk_nic_pf_ecc2_dbe_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t blk0                  : 50; /**< [ 49:  0](R/W1C/H) RAM error on group 2 block 0 memories. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 50; /**< [ 49:  0](R/W1C/H) RAM error on group 2 block 0 memories. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc2_dbe_int_s cn; */
};
typedef union bdk_nic_pf_ecc2_dbe_int bdk_nic_pf_ecc2_dbe_int_t;

#define BDK_NIC_PF_ECC2_DBE_INT BDK_NIC_PF_ECC2_DBE_INT_FUNC()
static inline uint64_t BDK_NIC_PF_ECC2_DBE_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC2_DBE_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002500ll;
    __bdk_csr_fatal("NIC_PF_ECC2_DBE_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC2_DBE_INT bdk_nic_pf_ecc2_dbe_int_t
#define bustype_BDK_NIC_PF_ECC2_DBE_INT BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC2_DBE_INT "NIC_PF_ECC2_DBE_INT"
#define device_bar_BDK_NIC_PF_ECC2_DBE_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC2_DBE_INT 0
#define arguments_BDK_NIC_PF_ECC2_DBE_INT -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc2_dbe_int_w1s
 *
 * NIC ECC 2 Double-bit Error Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_nic_pf_ecc2_dbe_int_w1s
{
    uint64_t u;
    struct bdk_nic_pf_ecc2_dbe_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t blk0                  : 50; /**< [ 49:  0](R/W1S/H) Reads or sets NIC_PF_ECC2_DBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 50; /**< [ 49:  0](R/W1S/H) Reads or sets NIC_PF_ECC2_DBE_INT[BLK0]. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc2_dbe_int_w1s_s cn; */
};
typedef union bdk_nic_pf_ecc2_dbe_int_w1s bdk_nic_pf_ecc2_dbe_int_w1s_t;

#define BDK_NIC_PF_ECC2_DBE_INT_W1S BDK_NIC_PF_ECC2_DBE_INT_W1S_FUNC()
static inline uint64_t BDK_NIC_PF_ECC2_DBE_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC2_DBE_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002508ll;
    __bdk_csr_fatal("NIC_PF_ECC2_DBE_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC2_DBE_INT_W1S bdk_nic_pf_ecc2_dbe_int_w1s_t
#define bustype_BDK_NIC_PF_ECC2_DBE_INT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC2_DBE_INT_W1S "NIC_PF_ECC2_DBE_INT_W1S"
#define device_bar_BDK_NIC_PF_ECC2_DBE_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC2_DBE_INT_W1S 0
#define arguments_BDK_NIC_PF_ECC2_DBE_INT_W1S -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc2_flip0
 *
 * NIC Memory ECC 2 Flip 0 Register
 * See NIC_PF_ECC0_FLIP0.
 */
union bdk_nic_pf_ecc2_flip0
{
    uint64_t u;
    struct bdk_nic_pf_ecc2_flip0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t blk0                  : 50; /**< [ 49:  0](R/W) Syndrome flip for group 2 block 0 memories.
                                                                 Internal:
                                                                 SEB memories.
                                                                 \<49:22\> = Reserved.
                                                                 \<21\>    = nic.nic_u.nic_u1.seb.mem.dmem.tso_crc.
                                                                 \<20\>    = nic.nic_u.nic_u1.seb.mem.dmem.simm.
                                                                 \<19\>    = nic.nic_u.nic_u1.seb.mem.dmem.sgth.
                                                                 \<18\>    = nic.nic_u.nic_u1.seb.mem.dmem.dsze.
                                                                 \<17\>    = nic.nic_u.nic_u1.seb.mem.dmem.lock_data.
                                                                 \<16\>    = nic.nic_u.nic_u1.seb.mem.dmem.lock_be
                                                                 \<15\>    = nic.nic_u.nic_u1.seb.mem.imem.crc_drf.
                                                                 \<14\>    = nic.nic_u.nic_u1.seb.mem.imem.smem_drf.
                                                                 \<13\>    = nic.nic_u.nic_u1.seb.ctx.lctx_dw0_drf.
                                                                 \<12\>    = nic.nic_u.nic_u1.seb.ctx.lctx_dw1_drf.
                                                                 \<11\>    = nic.nic_u.nic_u1.seb.ctx.eod_drf.
                                                                 \<10\>    = nic.nic_u.nic_u1.seb.ctx.gctx_drf.
                                                                 \<9:8\>   = nic.nic_u.nic_u1.seb.smc.smem_cq_context{1..0}.smem_cq_ctx.
                                                                 \<7\>     = nic.nic_u.nic_u1.seb.smc.smem_cq_stdn.
                                                                 \<6\>     = nic.nic_u.nic_u1.seb.ncx_intf.sgth_cmd.
                                                                 \<5:4\>   = nic.nic_u.nic_u1.seb.p2x_intf.tx_fifo_mem{1..0}.tx_fifo.
                                                                 \<3:2\>   = nic.nic_u.nic_u1.seb.p2x_intf.tx_fifo_mem{1..0}.p2x_sop_hdr.
                                                                 \<1:0\>   = nic.nic_u.nic_u1.seb.p2x_intf.tx_fifo_mem{1..0}.p2x_eop_hdr. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 50; /**< [ 49:  0](R/W) Syndrome flip for group 2 block 0 memories.
                                                                 Internal:
                                                                 SEB memories.
                                                                 \<49:22\> = Reserved.
                                                                 \<21\>    = nic.nic_u.nic_u1.seb.mem.dmem.tso_crc.
                                                                 \<20\>    = nic.nic_u.nic_u1.seb.mem.dmem.simm.
                                                                 \<19\>    = nic.nic_u.nic_u1.seb.mem.dmem.sgth.
                                                                 \<18\>    = nic.nic_u.nic_u1.seb.mem.dmem.dsze.
                                                                 \<17\>    = nic.nic_u.nic_u1.seb.mem.dmem.lock_data.
                                                                 \<16\>    = nic.nic_u.nic_u1.seb.mem.dmem.lock_be
                                                                 \<15\>    = nic.nic_u.nic_u1.seb.mem.imem.crc_drf.
                                                                 \<14\>    = nic.nic_u.nic_u1.seb.mem.imem.smem_drf.
                                                                 \<13\>    = nic.nic_u.nic_u1.seb.ctx.lctx_dw0_drf.
                                                                 \<12\>    = nic.nic_u.nic_u1.seb.ctx.lctx_dw1_drf.
                                                                 \<11\>    = nic.nic_u.nic_u1.seb.ctx.eod_drf.
                                                                 \<10\>    = nic.nic_u.nic_u1.seb.ctx.gctx_drf.
                                                                 \<9:8\>   = nic.nic_u.nic_u1.seb.smc.smem_cq_context{1..0}.smem_cq_ctx.
                                                                 \<7\>     = nic.nic_u.nic_u1.seb.smc.smem_cq_stdn.
                                                                 \<6\>     = nic.nic_u.nic_u1.seb.ncx_intf.sgth_cmd.
                                                                 \<5:4\>   = nic.nic_u.nic_u1.seb.p2x_intf.tx_fifo_mem{1..0}.tx_fifo.
                                                                 \<3:2\>   = nic.nic_u.nic_u1.seb.p2x_intf.tx_fifo_mem{1..0}.p2x_sop_hdr.
                                                                 \<1:0\>   = nic.nic_u.nic_u1.seb.p2x_intf.tx_fifo_mem{1..0}.p2x_eop_hdr. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc2_flip0_s cn; */
};
typedef union bdk_nic_pf_ecc2_flip0 bdk_nic_pf_ecc2_flip0_t;

#define BDK_NIC_PF_ECC2_FLIP0 BDK_NIC_PF_ECC2_FLIP0_FUNC()
static inline uint64_t BDK_NIC_PF_ECC2_FLIP0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC2_FLIP0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000001010ll;
    __bdk_csr_fatal("NIC_PF_ECC2_FLIP0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC2_FLIP0 bdk_nic_pf_ecc2_flip0_t
#define bustype_BDK_NIC_PF_ECC2_FLIP0 BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC2_FLIP0 "NIC_PF_ECC2_FLIP0"
#define device_bar_BDK_NIC_PF_ECC2_FLIP0 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC2_FLIP0 0
#define arguments_BDK_NIC_PF_ECC2_FLIP0 -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc2_flip1
 *
 * NIC Memory ECC 2 Flip 1 Register
 * See NIC_PF_ECC0_FLIP1.
 */
union bdk_nic_pf_ecc2_flip1
{
    uint64_t u;
    struct bdk_nic_pf_ecc2_flip1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t blk0                  : 50; /**< [ 49:  0](R/W) Syndrome flip for group 2 block 0 memories.
                                                                 Internal:
                                                                 SEB memories.
                                                                 \<49:22\> = Reserved.
                                                                 \<21\>    = nic.nic_u.nic_u1.seb.mem.dmem.tso_crc.
                                                                 \<20\>    = nic.nic_u.nic_u1.seb.mem.dmem.simm.
                                                                 \<19\>    = nic.nic_u.nic_u1.seb.mem.dmem.sgth.
                                                                 \<18\>    = nic.nic_u.nic_u1.seb.mem.dmem.dsze.
                                                                 \<17\>    = nic.nic_u.nic_u1.seb.mem.dmem.lock_data.
                                                                 \<16\>    = nic.nic_u.nic_u1.seb.mem.dmem.lock_be
                                                                 \<15\>    = nic.nic_u.nic_u1.seb.mem.imem.crc_drf.
                                                                 \<14\>    = nic.nic_u.nic_u1.seb.mem.imem.smem_drf.
                                                                 \<13\>    = nic.nic_u.nic_u1.seb.ctx.lctx_dw0_drf.
                                                                 \<12\>    = nic.nic_u.nic_u1.seb.ctx.lctx_dw1_drf.
                                                                 \<11\>    = nic.nic_u.nic_u1.seb.ctx.eod_drf.
                                                                 \<10\>    = nic.nic_u.nic_u1.seb.ctx.gctx_drf.
                                                                 \<9:8\>   = nic.nic_u.nic_u1.seb.smc.smem_cq_context{1..0}.smem_cq_ctx.
                                                                 \<7\>     = nic.nic_u.nic_u1.seb.smc.smem_cq_stdn.
                                                                 \<6\>     = nic.nic_u.nic_u1.seb.ncx_intf.sgth_cmd.
                                                                 \<5:4\>   = nic.nic_u.nic_u1.seb.p2x_intf.tx_fifo_mem{1..0}.tx_fifo.
                                                                 \<3:2\>   = nic.nic_u.nic_u1.seb.p2x_intf.tx_fifo_mem{1..0}.p2x_sop_hdr.
                                                                 \<1:0\>   = nic.nic_u.nic_u1.seb.p2x_intf.tx_fifo_mem{1..0}.p2x_eop_hdr. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 50; /**< [ 49:  0](R/W) Syndrome flip for group 2 block 0 memories.
                                                                 Internal:
                                                                 SEB memories.
                                                                 \<49:22\> = Reserved.
                                                                 \<21\>    = nic.nic_u.nic_u1.seb.mem.dmem.tso_crc.
                                                                 \<20\>    = nic.nic_u.nic_u1.seb.mem.dmem.simm.
                                                                 \<19\>    = nic.nic_u.nic_u1.seb.mem.dmem.sgth.
                                                                 \<18\>    = nic.nic_u.nic_u1.seb.mem.dmem.dsze.
                                                                 \<17\>    = nic.nic_u.nic_u1.seb.mem.dmem.lock_data.
                                                                 \<16\>    = nic.nic_u.nic_u1.seb.mem.dmem.lock_be
                                                                 \<15\>    = nic.nic_u.nic_u1.seb.mem.imem.crc_drf.
                                                                 \<14\>    = nic.nic_u.nic_u1.seb.mem.imem.smem_drf.
                                                                 \<13\>    = nic.nic_u.nic_u1.seb.ctx.lctx_dw0_drf.
                                                                 \<12\>    = nic.nic_u.nic_u1.seb.ctx.lctx_dw1_drf.
                                                                 \<11\>    = nic.nic_u.nic_u1.seb.ctx.eod_drf.
                                                                 \<10\>    = nic.nic_u.nic_u1.seb.ctx.gctx_drf.
                                                                 \<9:8\>   = nic.nic_u.nic_u1.seb.smc.smem_cq_context{1..0}.smem_cq_ctx.
                                                                 \<7\>     = nic.nic_u.nic_u1.seb.smc.smem_cq_stdn.
                                                                 \<6\>     = nic.nic_u.nic_u1.seb.ncx_intf.sgth_cmd.
                                                                 \<5:4\>   = nic.nic_u.nic_u1.seb.p2x_intf.tx_fifo_mem{1..0}.tx_fifo.
                                                                 \<3:2\>   = nic.nic_u.nic_u1.seb.p2x_intf.tx_fifo_mem{1..0}.p2x_sop_hdr.
                                                                 \<1:0\>   = nic.nic_u.nic_u1.seb.p2x_intf.tx_fifo_mem{1..0}.p2x_eop_hdr. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc2_flip1_s cn; */
};
typedef union bdk_nic_pf_ecc2_flip1 bdk_nic_pf_ecc2_flip1_t;

#define BDK_NIC_PF_ECC2_FLIP1 BDK_NIC_PF_ECC2_FLIP1_FUNC()
static inline uint64_t BDK_NIC_PF_ECC2_FLIP1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC2_FLIP1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000001090ll;
    __bdk_csr_fatal("NIC_PF_ECC2_FLIP1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC2_FLIP1 bdk_nic_pf_ecc2_flip1_t
#define bustype_BDK_NIC_PF_ECC2_FLIP1 BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC2_FLIP1 "NIC_PF_ECC2_FLIP1"
#define device_bar_BDK_NIC_PF_ECC2_FLIP1 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC2_FLIP1 0
#define arguments_BDK_NIC_PF_ECC2_FLIP1 -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc2_sbe_ena_w1c
 *
 * NIC ECC 2 Single-bit Error Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_nic_pf_ecc2_sbe_ena_w1c
{
    uint64_t u;
    struct bdk_nic_pf_ecc2_sbe_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t blk0                  : 50; /**< [ 49:  0](R/W1C/H) Reads or clears enable for NIC_PF_ECC2_SBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 50; /**< [ 49:  0](R/W1C/H) Reads or clears enable for NIC_PF_ECC2_SBE_INT[BLK0]. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc2_sbe_ena_w1c_s cn; */
};
typedef union bdk_nic_pf_ecc2_sbe_ena_w1c bdk_nic_pf_ecc2_sbe_ena_w1c_t;

#define BDK_NIC_PF_ECC2_SBE_ENA_W1C BDK_NIC_PF_ECC2_SBE_ENA_W1C_FUNC()
static inline uint64_t BDK_NIC_PF_ECC2_SBE_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC2_SBE_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002410ll;
    __bdk_csr_fatal("NIC_PF_ECC2_SBE_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC2_SBE_ENA_W1C bdk_nic_pf_ecc2_sbe_ena_w1c_t
#define bustype_BDK_NIC_PF_ECC2_SBE_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC2_SBE_ENA_W1C "NIC_PF_ECC2_SBE_ENA_W1C"
#define device_bar_BDK_NIC_PF_ECC2_SBE_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC2_SBE_ENA_W1C 0
#define arguments_BDK_NIC_PF_ECC2_SBE_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc2_sbe_ena_w1s
 *
 * NIC ECC 2 Single-bit Error Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_nic_pf_ecc2_sbe_ena_w1s
{
    uint64_t u;
    struct bdk_nic_pf_ecc2_sbe_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t blk0                  : 50; /**< [ 49:  0](R/W1S/H) Reads or sets enable for NIC_PF_ECC2_SBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 50; /**< [ 49:  0](R/W1S/H) Reads or sets enable for NIC_PF_ECC2_SBE_INT[BLK0]. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc2_sbe_ena_w1s_s cn; */
};
typedef union bdk_nic_pf_ecc2_sbe_ena_w1s bdk_nic_pf_ecc2_sbe_ena_w1s_t;

#define BDK_NIC_PF_ECC2_SBE_ENA_W1S BDK_NIC_PF_ECC2_SBE_ENA_W1S_FUNC()
static inline uint64_t BDK_NIC_PF_ECC2_SBE_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC2_SBE_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002418ll;
    __bdk_csr_fatal("NIC_PF_ECC2_SBE_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC2_SBE_ENA_W1S bdk_nic_pf_ecc2_sbe_ena_w1s_t
#define bustype_BDK_NIC_PF_ECC2_SBE_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC2_SBE_ENA_W1S "NIC_PF_ECC2_SBE_ENA_W1S"
#define device_bar_BDK_NIC_PF_ECC2_SBE_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC2_SBE_ENA_W1S 0
#define arguments_BDK_NIC_PF_ECC2_SBE_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc2_sbe_int
 *
 * NIC ECC 2 Single-bit Error Interrupt Register
 * Reports single-bit errors detected in internal RAM. Each bit corresponds to a different RAM: 0
 * = pass, 1 = fail.
 *
 * Internal:
 * Bits in each field are enumerated by NIC_PF_ECC2_FLIP0.
 */
union bdk_nic_pf_ecc2_sbe_int
{
    uint64_t u;
    struct bdk_nic_pf_ecc2_sbe_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t blk0                  : 50; /**< [ 49:  0](R/W1C/H) RAM error on group 2 block 0 memories. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 50; /**< [ 49:  0](R/W1C/H) RAM error on group 2 block 0 memories. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc2_sbe_int_s cn; */
};
typedef union bdk_nic_pf_ecc2_sbe_int bdk_nic_pf_ecc2_sbe_int_t;

#define BDK_NIC_PF_ECC2_SBE_INT BDK_NIC_PF_ECC2_SBE_INT_FUNC()
static inline uint64_t BDK_NIC_PF_ECC2_SBE_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC2_SBE_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002400ll;
    __bdk_csr_fatal("NIC_PF_ECC2_SBE_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC2_SBE_INT bdk_nic_pf_ecc2_sbe_int_t
#define bustype_BDK_NIC_PF_ECC2_SBE_INT BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC2_SBE_INT "NIC_PF_ECC2_SBE_INT"
#define device_bar_BDK_NIC_PF_ECC2_SBE_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC2_SBE_INT 0
#define arguments_BDK_NIC_PF_ECC2_SBE_INT -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc2_sbe_int_w1s
 *
 * NIC ECC 2 Single-bit Error Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_nic_pf_ecc2_sbe_int_w1s
{
    uint64_t u;
    struct bdk_nic_pf_ecc2_sbe_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t blk0                  : 50; /**< [ 49:  0](R/W1S/H) Reads or sets NIC_PF_ECC2_SBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 50; /**< [ 49:  0](R/W1S/H) Reads or sets NIC_PF_ECC2_SBE_INT[BLK0]. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc2_sbe_int_w1s_s cn; */
};
typedef union bdk_nic_pf_ecc2_sbe_int_w1s bdk_nic_pf_ecc2_sbe_int_w1s_t;

#define BDK_NIC_PF_ECC2_SBE_INT_W1S BDK_NIC_PF_ECC2_SBE_INT_W1S_FUNC()
static inline uint64_t BDK_NIC_PF_ECC2_SBE_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC2_SBE_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002408ll;
    __bdk_csr_fatal("NIC_PF_ECC2_SBE_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC2_SBE_INT_W1S bdk_nic_pf_ecc2_sbe_int_w1s_t
#define bustype_BDK_NIC_PF_ECC2_SBE_INT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC2_SBE_INT_W1S "NIC_PF_ECC2_SBE_INT_W1S"
#define device_bar_BDK_NIC_PF_ECC2_SBE_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC2_SBE_INT_W1S 0
#define arguments_BDK_NIC_PF_ECC2_SBE_INT_W1S -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc3_cdis
 *
 * NIC Memory ECC 3 Correction Disable Register
 * See NIC_PF_ECC0_CDIS.
 */
union bdk_nic_pf_ecc3_cdis
{
    uint64_t u;
    struct bdk_nic_pf_ecc3_cdis_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 3 block 1 memories.
                                                                 Internal:
                                                                 SQM memories:
                                                                   \<15:12\> = Reserved.
                                                                   \<11\> = nic.nic_u.nic_u1.sqm.dse.send.tsopn_mem.
                                                                   \<10\> = nic.nic_u.nic_u1.sqm.dpe.arb.sq_arb_mem_mem.
                                                                   \<9\>  = nic.nic_u.nic_u1.sqm.ctl.sq.sq_mem_mem.
                                                                   \<8\>  = nic.nic_u.nic_u1.sqm.ctl.sq.qs_mem.
                                                                   \<7\>  = Reserved.
                                                                   \<6\>  = nic.nic_u.nic_u1.sqm.ctl.vnic.vnic_mem_mem.
                                                                   \<5\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.dpe_blk.fetch_op_fifo_dpr.
                                                                   \<4\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<3\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.dse_blk.fetch_op_fifo_dpr.
                                                                   \<2\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<1\>  = nic.nic_u.nic_u1.sqm.mqm.qsmem_mem.
                                                                   \<0\>  = nic.nic_u.nic_u1.sqm.mqm.mdmem_mem. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 3 block 0 memories.
                                                                 Internal:
                                                                 SPS memories:

                                                                   \<23:18\> = Reserved
                                                                   \<17\> = nic.nic_u.nic_u2.sps.sqm_intf.mem.sqcfgmem.
                                                                   \<16\> = nic.nic_u.nic_u2.sps.tl3.mem.tl4_stsmem.
                                                                   \<15:10\> = Reserved
                                                                   \<9\>  = nic.nic_u.nic_u2.sps.tl3.mem.pirmem.
                                                                   \<8\>  = nic.nic_u.nic_u2.sps.tl3.mem.rtmem.
                                                                   \<7\>  = nic.nic_u.nic_u2.sps.tl3.mem.tl3_stsmem.
                                                                   \<6\>  = nic.nic_u.nic_u2.sps.tl3.mem.stdmem.
                                                                   \<5\>  = nic.nic_u.nic_u2.sps.tl3.mem.ccdtmem.
                                                                   \<4\>  = nic.nic_u.nic_u2.sps.tl3.mem.lcdtmem.
                                                                   \<3\>  = Reserved
                                                                   \<2\>  = nic.nic_u.nic_u2.sps.tl2.mem.rtmem.
                                                                   \<1\>  = nic.nic_u.nic_u2.sps.tl2.mem.stsmem.
                                                                   \<0\>  = nic.nic_u.nic_u2.sps.tl2.mem.stdmem. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 3 block 0 memories.
                                                                 Internal:
                                                                 SPS memories:

                                                                   \<23:18\> = Reserved
                                                                   \<17\> = nic.nic_u.nic_u2.sps.sqm_intf.mem.sqcfgmem.
                                                                   \<16\> = nic.nic_u.nic_u2.sps.tl3.mem.tl4_stsmem.
                                                                   \<15:10\> = Reserved
                                                                   \<9\>  = nic.nic_u.nic_u2.sps.tl3.mem.pirmem.
                                                                   \<8\>  = nic.nic_u.nic_u2.sps.tl3.mem.rtmem.
                                                                   \<7\>  = nic.nic_u.nic_u2.sps.tl3.mem.tl3_stsmem.
                                                                   \<6\>  = nic.nic_u.nic_u2.sps.tl3.mem.stdmem.
                                                                   \<5\>  = nic.nic_u.nic_u2.sps.tl3.mem.ccdtmem.
                                                                   \<4\>  = nic.nic_u.nic_u2.sps.tl3.mem.lcdtmem.
                                                                   \<3\>  = Reserved
                                                                   \<2\>  = nic.nic_u.nic_u2.sps.tl2.mem.rtmem.
                                                                   \<1\>  = nic.nic_u.nic_u2.sps.tl2.mem.stsmem.
                                                                   \<0\>  = nic.nic_u.nic_u2.sps.tl2.mem.stdmem. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 3 block 1 memories.
                                                                 Internal:
                                                                 SQM memories:
                                                                   \<15:12\> = Reserved.
                                                                   \<11\> = nic.nic_u.nic_u1.sqm.dse.send.tsopn_mem.
                                                                   \<10\> = nic.nic_u.nic_u1.sqm.dpe.arb.sq_arb_mem_mem.
                                                                   \<9\>  = nic.nic_u.nic_u1.sqm.ctl.sq.sq_mem_mem.
                                                                   \<8\>  = nic.nic_u.nic_u1.sqm.ctl.sq.qs_mem.
                                                                   \<7\>  = Reserved.
                                                                   \<6\>  = nic.nic_u.nic_u1.sqm.ctl.vnic.vnic_mem_mem.
                                                                   \<5\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.dpe_blk.fetch_op_fifo_dpr.
                                                                   \<4\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<3\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.dse_blk.fetch_op_fifo_dpr.
                                                                   \<2\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<1\>  = nic.nic_u.nic_u1.sqm.mqm.qsmem_mem.
                                                                   \<0\>  = nic.nic_u.nic_u1.sqm.mqm.mdmem_mem. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc3_cdis_s cn8; */
    /* struct bdk_nic_pf_ecc3_cdis_s cn81xx; */
    struct bdk_nic_pf_ecc3_cdis_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 3 block 1 memories.
                                                                 Internal:
                                                                 SQM memories:
                                                                   \<15:13\> = Reserved.
                                                                   \<12\> = nic.nic_u.nic_u1.sqm.mqm.mdmem2_mem.
                                                                   \<11\> = nic.nic_u.nic_u1.sqm.dse.send.tsopn_mem.
                                                                   \<10\> = nic.nic_u.nic_u1.sqm.dpe.arb.sq_arb_mem_mem.
                                                                   \<9\>  = nic.nic_u.nic_u1.sqm.ctl.sq.sq_mem_mem.
                                                                   \<8\>  = nic.nic_u.nic_u1.sqm.ctl.sq.qs_mem.
                                                                   \<7\>  = Reserved.
                                                                   \<6\>  = nic.nic_u.nic_u1.sqm.ctl.vnic.vnic_mem_mem.
                                                                   \<5\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.dpe_blk.fetch_op_fifo_dpr.
                                                                   \<4\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<3\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.dse_blk.fetch_op_fifo_dpr.
                                                                   \<2\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<1\>  = nic.nic_u.nic_u1.sqm.mqm.qsmem_mem.
                                                                   \<0\>  = nic.nic_u.nic_u1.sqm.mqm.mdmem_mem. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 3 block 0 memories.
                                                                 Internal:
                                                                 SPS memories:

                                                                   \<23:18\> = Reserved
                                                                   \<17\> = nic.nic_u.nic_u2.sps.sqm_intf.mem.sqcfgmem.
                                                                   \<16\> = nic.nic_u.nic_u2.sps.tl3.mem.tl4_stsmem.
                                                                   \<15:10\> = Reserved
                                                                   \<9\>  = nic.nic_u.nic_u2.sps.tl3.mem.pirmem.
                                                                   \<8\>  = nic.nic_u.nic_u2.sps.tl3.mem.rtmem.
                                                                   \<7\>  = nic.nic_u.nic_u2.sps.tl3.mem.tl3_stsmem.
                                                                   \<6\>  = nic.nic_u.nic_u2.sps.tl3.mem.stdmem.
                                                                   \<5\>  = nic.nic_u.nic_u2.sps.tl3.mem.ccdtmem.
                                                                   \<4\>  = nic.nic_u.nic_u2.sps.tl3.mem.lcdtmem.
                                                                   \<3\>  = Reserved
                                                                   \<2\>  = nic.nic_u.nic_u2.sps.tl2.mem.rtmem.
                                                                   \<1\>  = nic.nic_u.nic_u2.sps.tl2.mem.stsmem.
                                                                   \<0\>  = nic.nic_u.nic_u2.sps.tl2.mem.stdmem. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 3 block 0 memories.
                                                                 Internal:
                                                                 SPS memories:

                                                                   \<23:18\> = Reserved
                                                                   \<17\> = nic.nic_u.nic_u2.sps.sqm_intf.mem.sqcfgmem.
                                                                   \<16\> = nic.nic_u.nic_u2.sps.tl3.mem.tl4_stsmem.
                                                                   \<15:10\> = Reserved
                                                                   \<9\>  = nic.nic_u.nic_u2.sps.tl3.mem.pirmem.
                                                                   \<8\>  = nic.nic_u.nic_u2.sps.tl3.mem.rtmem.
                                                                   \<7\>  = nic.nic_u.nic_u2.sps.tl3.mem.tl3_stsmem.
                                                                   \<6\>  = nic.nic_u.nic_u2.sps.tl3.mem.stdmem.
                                                                   \<5\>  = nic.nic_u.nic_u2.sps.tl3.mem.ccdtmem.
                                                                   \<4\>  = nic.nic_u.nic_u2.sps.tl3.mem.lcdtmem.
                                                                   \<3\>  = Reserved
                                                                   \<2\>  = nic.nic_u.nic_u2.sps.tl2.mem.rtmem.
                                                                   \<1\>  = nic.nic_u.nic_u2.sps.tl2.mem.stsmem.
                                                                   \<0\>  = nic.nic_u.nic_u2.sps.tl2.mem.stdmem. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 3 block 1 memories.
                                                                 Internal:
                                                                 SQM memories:
                                                                   \<15:13\> = Reserved.
                                                                   \<12\> = nic.nic_u.nic_u1.sqm.mqm.mdmem2_mem.
                                                                   \<11\> = nic.nic_u.nic_u1.sqm.dse.send.tsopn_mem.
                                                                   \<10\> = nic.nic_u.nic_u1.sqm.dpe.arb.sq_arb_mem_mem.
                                                                   \<9\>  = nic.nic_u.nic_u1.sqm.ctl.sq.sq_mem_mem.
                                                                   \<8\>  = nic.nic_u.nic_u1.sqm.ctl.sq.qs_mem.
                                                                   \<7\>  = Reserved.
                                                                   \<6\>  = nic.nic_u.nic_u1.sqm.ctl.vnic.vnic_mem_mem.
                                                                   \<5\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.dpe_blk.fetch_op_fifo_dpr.
                                                                   \<4\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<3\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.dse_blk.fetch_op_fifo_dpr.
                                                                   \<2\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<1\>  = nic.nic_u.nic_u1.sqm.mqm.qsmem_mem.
                                                                   \<0\>  = nic.nic_u.nic_u1.sqm.mqm.mdmem_mem. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_pf_ecc3_cdis bdk_nic_pf_ecc3_cdis_t;

#define BDK_NIC_PF_ECC3_CDIS BDK_NIC_PF_ECC3_CDIS_FUNC()
static inline uint64_t BDK_NIC_PF_ECC3_CDIS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC3_CDIS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000001118ll;
    __bdk_csr_fatal("NIC_PF_ECC3_CDIS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC3_CDIS bdk_nic_pf_ecc3_cdis_t
#define bustype_BDK_NIC_PF_ECC3_CDIS BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC3_CDIS "NIC_PF_ECC3_CDIS"
#define device_bar_BDK_NIC_PF_ECC3_CDIS 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC3_CDIS 0
#define arguments_BDK_NIC_PF_ECC3_CDIS -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc3_dbe_ena_w1c
 *
 * NIC ECC 3 Double-bit Error Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_nic_pf_ecc3_dbe_ena_w1c
{
    uint64_t u;
    struct bdk_nic_pf_ecc3_dbe_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1C/H) Reads or clears enable for NIC_PF_ECC3_DBE_INT[BLK1]. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1C/H) Reads or clears enable for NIC_PF_ECC3_DBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1C/H) Reads or clears enable for NIC_PF_ECC3_DBE_INT[BLK0]. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1C/H) Reads or clears enable for NIC_PF_ECC3_DBE_INT[BLK1]. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc3_dbe_ena_w1c_s cn; */
};
typedef union bdk_nic_pf_ecc3_dbe_ena_w1c bdk_nic_pf_ecc3_dbe_ena_w1c_t;

#define BDK_NIC_PF_ECC3_DBE_ENA_W1C BDK_NIC_PF_ECC3_DBE_ENA_W1C_FUNC()
static inline uint64_t BDK_NIC_PF_ECC3_DBE_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC3_DBE_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002710ll;
    __bdk_csr_fatal("NIC_PF_ECC3_DBE_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC3_DBE_ENA_W1C bdk_nic_pf_ecc3_dbe_ena_w1c_t
#define bustype_BDK_NIC_PF_ECC3_DBE_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC3_DBE_ENA_W1C "NIC_PF_ECC3_DBE_ENA_W1C"
#define device_bar_BDK_NIC_PF_ECC3_DBE_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC3_DBE_ENA_W1C 0
#define arguments_BDK_NIC_PF_ECC3_DBE_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc3_dbe_ena_w1s
 *
 * NIC ECC 3 Single-bit Error Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_nic_pf_ecc3_dbe_ena_w1s
{
    uint64_t u;
    struct bdk_nic_pf_ecc3_dbe_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1S/H) Reads or sets enable for NIC_PF_ECC3_DBE_INT[BLK1]. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1S/H) Reads or sets enable for NIC_PF_ECC3_DBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1S/H) Reads or sets enable for NIC_PF_ECC3_DBE_INT[BLK0]. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1S/H) Reads or sets enable for NIC_PF_ECC3_DBE_INT[BLK1]. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc3_dbe_ena_w1s_s cn; */
};
typedef union bdk_nic_pf_ecc3_dbe_ena_w1s bdk_nic_pf_ecc3_dbe_ena_w1s_t;

#define BDK_NIC_PF_ECC3_DBE_ENA_W1S BDK_NIC_PF_ECC3_DBE_ENA_W1S_FUNC()
static inline uint64_t BDK_NIC_PF_ECC3_DBE_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC3_DBE_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002718ll;
    __bdk_csr_fatal("NIC_PF_ECC3_DBE_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC3_DBE_ENA_W1S bdk_nic_pf_ecc3_dbe_ena_w1s_t
#define bustype_BDK_NIC_PF_ECC3_DBE_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC3_DBE_ENA_W1S "NIC_PF_ECC3_DBE_ENA_W1S"
#define device_bar_BDK_NIC_PF_ECC3_DBE_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC3_DBE_ENA_W1S 0
#define arguments_BDK_NIC_PF_ECC3_DBE_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc3_dbe_int
 *
 * NIC ECC 3 Double-bit Error Interrupt Register
 * Reports double-bit errors detected in internal RAM. Each bit corresponds to a different RAM: 0
 * = pass, 1 = fail.
 *
 * Internal:
 * Bits in each field are enumerated by NIC_PF_ECC3_FLIP0.
 */
union bdk_nic_pf_ecc3_dbe_int
{
    uint64_t u;
    struct bdk_nic_pf_ecc3_dbe_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1C/H) RAM error on group 3 block 1 memories. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1C/H) RAM error on group 3 block 0 memories. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1C/H) RAM error on group 3 block 0 memories. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1C/H) RAM error on group 3 block 1 memories. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc3_dbe_int_s cn; */
};
typedef union bdk_nic_pf_ecc3_dbe_int bdk_nic_pf_ecc3_dbe_int_t;

#define BDK_NIC_PF_ECC3_DBE_INT BDK_NIC_PF_ECC3_DBE_INT_FUNC()
static inline uint64_t BDK_NIC_PF_ECC3_DBE_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC3_DBE_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002700ll;
    __bdk_csr_fatal("NIC_PF_ECC3_DBE_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC3_DBE_INT bdk_nic_pf_ecc3_dbe_int_t
#define bustype_BDK_NIC_PF_ECC3_DBE_INT BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC3_DBE_INT "NIC_PF_ECC3_DBE_INT"
#define device_bar_BDK_NIC_PF_ECC3_DBE_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC3_DBE_INT 0
#define arguments_BDK_NIC_PF_ECC3_DBE_INT -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc3_dbe_int_w1s
 *
 * NIC ECC 3 Double-bit Error Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_nic_pf_ecc3_dbe_int_w1s
{
    uint64_t u;
    struct bdk_nic_pf_ecc3_dbe_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1S/H) Reads or sets NIC_PF_ECC3_DBE_INT[BLK1]. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1S/H) Reads or sets NIC_PF_ECC3_DBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1S/H) Reads or sets NIC_PF_ECC3_DBE_INT[BLK0]. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1S/H) Reads or sets NIC_PF_ECC3_DBE_INT[BLK1]. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc3_dbe_int_w1s_s cn; */
};
typedef union bdk_nic_pf_ecc3_dbe_int_w1s bdk_nic_pf_ecc3_dbe_int_w1s_t;

#define BDK_NIC_PF_ECC3_DBE_INT_W1S BDK_NIC_PF_ECC3_DBE_INT_W1S_FUNC()
static inline uint64_t BDK_NIC_PF_ECC3_DBE_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC3_DBE_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002708ll;
    __bdk_csr_fatal("NIC_PF_ECC3_DBE_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC3_DBE_INT_W1S bdk_nic_pf_ecc3_dbe_int_w1s_t
#define bustype_BDK_NIC_PF_ECC3_DBE_INT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC3_DBE_INT_W1S "NIC_PF_ECC3_DBE_INT_W1S"
#define device_bar_BDK_NIC_PF_ECC3_DBE_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC3_DBE_INT_W1S 0
#define arguments_BDK_NIC_PF_ECC3_DBE_INT_W1S -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc3_flip0
 *
 * NIC Memory ECC 3 Flip 0 Register
 * See NIC_PF_ECC0_FLIP0.
 */
union bdk_nic_pf_ecc3_flip0
{
    uint64_t u;
    struct bdk_nic_pf_ecc3_flip0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 3 block 1 memories.
                                                                 Internal:
                                                                 SQM memories:
                                                                   \<15:12\> = Reserved.
                                                                   \<11\> = nic.nic_u.nic_u1.sqm.dse.send.tsopn_mem.
                                                                   \<10\> = nic.nic_u.nic_u1.sqm.dpe.arb.sq_arb_mem_mem.
                                                                   \<9\>  = nic.nic_u.nic_u1.sqm.ctl.sq.sq_mem_mem.
                                                                   \<8\>  = nic.nic_u.nic_u1.sqm.ctl.sq.qs_mem.
                                                                   \<7\>  = Reserved.
                                                                   \<6\>  = nic.nic_u.nic_u1.sqm.ctl.vnic.vnic_mem_mem.
                                                                   \<5\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.dpe_blk.fetch_op_fifo_dpr.
                                                                   \<4\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<3\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.dse_blk.fetch_op_fifo_dpr.
                                                                   \<2\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<1\>  = nic.nic_u.nic_u1.sqm.mqm.qsmem_mem.
                                                                   \<0\>  = nic.nic_u.nic_u1.sqm.mqm.mdmem_mem. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 3 block 0 memories.
                                                                 Internal:
                                                                 SPS memories:

                                                                   \<23:18\> = Reserved
                                                                   \<17\> = nic.nic_u.nic_u2.sps.sqm_intf.mem.sqcfgmem.
                                                                   \<16\> = nic.nic_u.nic_u2.sps.tl3.mem.tl4_stsmem.
                                                                   \<15:10\> = Reserved
                                                                   \<9\>  = nic.nic_u.nic_u2.sps.tl3.mem.pirmem.
                                                                   \<8\>  = nic.nic_u.nic_u2.sps.tl3.mem.rtmem.
                                                                   \<7\>  = nic.nic_u.nic_u2.sps.tl3.mem.tl3_stsmem.
                                                                   \<6\>  = nic.nic_u.nic_u2.sps.tl3.mem.stdmem.
                                                                   \<5\>  = nic.nic_u.nic_u2.sps.tl3.mem.ccdtmem.
                                                                   \<4\>  = nic.nic_u.nic_u2.sps.tl3.mem.lcdtmem.
                                                                   \<3\>  = Reserved
                                                                   \<2\>  = nic.nic_u.nic_u2.sps.tl2.mem.rtmem.
                                                                   \<1\>  = nic.nic_u.nic_u2.sps.tl2.mem.stsmem.
                                                                   \<0\>  = nic.nic_u.nic_u2.sps.tl2.mem.stdmem. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 3 block 0 memories.
                                                                 Internal:
                                                                 SPS memories:

                                                                   \<23:18\> = Reserved
                                                                   \<17\> = nic.nic_u.nic_u2.sps.sqm_intf.mem.sqcfgmem.
                                                                   \<16\> = nic.nic_u.nic_u2.sps.tl3.mem.tl4_stsmem.
                                                                   \<15:10\> = Reserved
                                                                   \<9\>  = nic.nic_u.nic_u2.sps.tl3.mem.pirmem.
                                                                   \<8\>  = nic.nic_u.nic_u2.sps.tl3.mem.rtmem.
                                                                   \<7\>  = nic.nic_u.nic_u2.sps.tl3.mem.tl3_stsmem.
                                                                   \<6\>  = nic.nic_u.nic_u2.sps.tl3.mem.stdmem.
                                                                   \<5\>  = nic.nic_u.nic_u2.sps.tl3.mem.ccdtmem.
                                                                   \<4\>  = nic.nic_u.nic_u2.sps.tl3.mem.lcdtmem.
                                                                   \<3\>  = Reserved
                                                                   \<2\>  = nic.nic_u.nic_u2.sps.tl2.mem.rtmem.
                                                                   \<1\>  = nic.nic_u.nic_u2.sps.tl2.mem.stsmem.
                                                                   \<0\>  = nic.nic_u.nic_u2.sps.tl2.mem.stdmem. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 3 block 1 memories.
                                                                 Internal:
                                                                 SQM memories:
                                                                   \<15:12\> = Reserved.
                                                                   \<11\> = nic.nic_u.nic_u1.sqm.dse.send.tsopn_mem.
                                                                   \<10\> = nic.nic_u.nic_u1.sqm.dpe.arb.sq_arb_mem_mem.
                                                                   \<9\>  = nic.nic_u.nic_u1.sqm.ctl.sq.sq_mem_mem.
                                                                   \<8\>  = nic.nic_u.nic_u1.sqm.ctl.sq.qs_mem.
                                                                   \<7\>  = Reserved.
                                                                   \<6\>  = nic.nic_u.nic_u1.sqm.ctl.vnic.vnic_mem_mem.
                                                                   \<5\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.dpe_blk.fetch_op_fifo_dpr.
                                                                   \<4\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<3\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.dse_blk.fetch_op_fifo_dpr.
                                                                   \<2\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<1\>  = nic.nic_u.nic_u1.sqm.mqm.qsmem_mem.
                                                                   \<0\>  = nic.nic_u.nic_u1.sqm.mqm.mdmem_mem. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc3_flip0_s cn8; */
    /* struct bdk_nic_pf_ecc3_flip0_s cn81xx; */
    struct bdk_nic_pf_ecc3_flip0_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 3 block 1 memories.
                                                                 Internal:
                                                                 SQM memories:
                                                                   \<15:13\> = Reserved.
                                                                   \<12\> = nic.nic_u.nic_u1.sqm.mqm.mdmem2_mem.
                                                                   \<11\> = nic.nic_u.nic_u1.sqm.dse.send.tsopn_mem.
                                                                   \<10\> = nic.nic_u.nic_u1.sqm.dpe.arb.sq_arb_mem_mem.
                                                                   \<9\>  = nic.nic_u.nic_u1.sqm.ctl.sq.sq_mem_mem.
                                                                   \<8\>  = nic.nic_u.nic_u1.sqm.ctl.sq.qs_mem.
                                                                   \<7\>  = Reserved.
                                                                   \<6\>  = nic.nic_u.nic_u1.sqm.ctl.vnic.vnic_mem_mem.
                                                                   \<5\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.dpe_blk.fetch_op_fifo_dpr.
                                                                   \<4\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<3\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.dse_blk.fetch_op_fifo_dpr.
                                                                   \<2\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<1\>  = nic.nic_u.nic_u1.sqm.mqm.qsmem_mem.
                                                                   \<0\>  = nic.nic_u.nic_u1.sqm.mqm.mdmem_mem. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 3 block 0 memories.
                                                                 Internal:
                                                                 SPS memories:

                                                                   \<23:18\> = Reserved
                                                                   \<17\> = nic.nic_u.nic_u2.sps.sqm_intf.mem.sqcfgmem.
                                                                   \<16\> = nic.nic_u.nic_u2.sps.tl3.mem.tl4_stsmem.
                                                                   \<15:10\> = Reserved
                                                                   \<9\>  = nic.nic_u.nic_u2.sps.tl3.mem.pirmem.
                                                                   \<8\>  = nic.nic_u.nic_u2.sps.tl3.mem.rtmem.
                                                                   \<7\>  = nic.nic_u.nic_u2.sps.tl3.mem.tl3_stsmem.
                                                                   \<6\>  = nic.nic_u.nic_u2.sps.tl3.mem.stdmem.
                                                                   \<5\>  = nic.nic_u.nic_u2.sps.tl3.mem.ccdtmem.
                                                                   \<4\>  = nic.nic_u.nic_u2.sps.tl3.mem.lcdtmem.
                                                                   \<3\>  = Reserved
                                                                   \<2\>  = nic.nic_u.nic_u2.sps.tl2.mem.rtmem.
                                                                   \<1\>  = nic.nic_u.nic_u2.sps.tl2.mem.stsmem.
                                                                   \<0\>  = nic.nic_u.nic_u2.sps.tl2.mem.stdmem. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 3 block 0 memories.
                                                                 Internal:
                                                                 SPS memories:

                                                                   \<23:18\> = Reserved
                                                                   \<17\> = nic.nic_u.nic_u2.sps.sqm_intf.mem.sqcfgmem.
                                                                   \<16\> = nic.nic_u.nic_u2.sps.tl3.mem.tl4_stsmem.
                                                                   \<15:10\> = Reserved
                                                                   \<9\>  = nic.nic_u.nic_u2.sps.tl3.mem.pirmem.
                                                                   \<8\>  = nic.nic_u.nic_u2.sps.tl3.mem.rtmem.
                                                                   \<7\>  = nic.nic_u.nic_u2.sps.tl3.mem.tl3_stsmem.
                                                                   \<6\>  = nic.nic_u.nic_u2.sps.tl3.mem.stdmem.
                                                                   \<5\>  = nic.nic_u.nic_u2.sps.tl3.mem.ccdtmem.
                                                                   \<4\>  = nic.nic_u.nic_u2.sps.tl3.mem.lcdtmem.
                                                                   \<3\>  = Reserved
                                                                   \<2\>  = nic.nic_u.nic_u2.sps.tl2.mem.rtmem.
                                                                   \<1\>  = nic.nic_u.nic_u2.sps.tl2.mem.stsmem.
                                                                   \<0\>  = nic.nic_u.nic_u2.sps.tl2.mem.stdmem. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 3 block 1 memories.
                                                                 Internal:
                                                                 SQM memories:
                                                                   \<15:13\> = Reserved.
                                                                   \<12\> = nic.nic_u.nic_u1.sqm.mqm.mdmem2_mem.
                                                                   \<11\> = nic.nic_u.nic_u1.sqm.dse.send.tsopn_mem.
                                                                   \<10\> = nic.nic_u.nic_u1.sqm.dpe.arb.sq_arb_mem_mem.
                                                                   \<9\>  = nic.nic_u.nic_u1.sqm.ctl.sq.sq_mem_mem.
                                                                   \<8\>  = nic.nic_u.nic_u1.sqm.ctl.sq.qs_mem.
                                                                   \<7\>  = Reserved.
                                                                   \<6\>  = nic.nic_u.nic_u1.sqm.ctl.vnic.vnic_mem_mem.
                                                                   \<5\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.dpe_blk.fetch_op_fifo_dpr.
                                                                   \<4\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<3\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.dse_blk.fetch_op_fifo_dpr.
                                                                   \<2\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<1\>  = nic.nic_u.nic_u1.sqm.mqm.qsmem_mem.
                                                                   \<0\>  = nic.nic_u.nic_u1.sqm.mqm.mdmem_mem. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_pf_ecc3_flip0 bdk_nic_pf_ecc3_flip0_t;

#define BDK_NIC_PF_ECC3_FLIP0 BDK_NIC_PF_ECC3_FLIP0_FUNC()
static inline uint64_t BDK_NIC_PF_ECC3_FLIP0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC3_FLIP0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000001018ll;
    __bdk_csr_fatal("NIC_PF_ECC3_FLIP0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC3_FLIP0 bdk_nic_pf_ecc3_flip0_t
#define bustype_BDK_NIC_PF_ECC3_FLIP0 BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC3_FLIP0 "NIC_PF_ECC3_FLIP0"
#define device_bar_BDK_NIC_PF_ECC3_FLIP0 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC3_FLIP0 0
#define arguments_BDK_NIC_PF_ECC3_FLIP0 -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc3_flip1
 *
 * NIC Memory ECC 3 Flip 1 Register
 * See NIC_PF_ECC0_FLIP1.
 */
union bdk_nic_pf_ecc3_flip1
{
    uint64_t u;
    struct bdk_nic_pf_ecc3_flip1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 3 block 1 memories.
                                                                 Internal:
                                                                 SQM memories:
                                                                   \<15:12\> = Reserved.
                                                                   \<11\> = nic.nic_u.nic_u1.sqm.dse.send.tsopn_mem.
                                                                   \<10\> = nic.nic_u.nic_u1.sqm.dpe.arb.sq_arb_mem_mem.
                                                                   \<9\>  = nic.nic_u.nic_u1.sqm.ctl.sq.sq_mem_mem.
                                                                   \<8\>  = nic.nic_u.nic_u1.sqm.ctl.sq.qs_mem.
                                                                   \<7\>  = Reserved.
                                                                   \<6\>  = nic.nic_u.nic_u1.sqm.ctl.vnic.vnic_mem_mem.
                                                                   \<5\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.dpe_blk.fetch_op_fifo_dpr.
                                                                   \<4\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<3\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.dse_blk.fetch_op_fifo_dpr.
                                                                   \<2\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<1\>  = nic.nic_u.nic_u1.sqm.mqm.qsmem_mem.
                                                                   \<0\>  = nic.nic_u.nic_u1.sqm.mqm.mdmem_mem. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 3 block 0 memories.
                                                                 Internal:
                                                                 SPS memories:

                                                                   \<23:18\> = Reserved
                                                                   \<17\> = nic.nic_u.nic_u2.sps.sqm_intf.mem.sqcfgmem.
                                                                   \<16\> = nic.nic_u.nic_u2.sps.tl3.mem.tl4_stsmem.
                                                                   \<15:10\> = Reserved
                                                                   \<9\>  = nic.nic_u.nic_u2.sps.tl3.mem.pirmem.
                                                                   \<8\>  = nic.nic_u.nic_u2.sps.tl3.mem.rtmem.
                                                                   \<7\>  = nic.nic_u.nic_u2.sps.tl3.mem.tl3_stsmem.
                                                                   \<6\>  = nic.nic_u.nic_u2.sps.tl3.mem.stdmem.
                                                                   \<5\>  = nic.nic_u.nic_u2.sps.tl3.mem.ccdtmem.
                                                                   \<4\>  = nic.nic_u.nic_u2.sps.tl3.mem.lcdtmem.
                                                                   \<3\>  = Reserved
                                                                   \<2\>  = nic.nic_u.nic_u2.sps.tl2.mem.rtmem.
                                                                   \<1\>  = nic.nic_u.nic_u2.sps.tl2.mem.stsmem.
                                                                   \<0\>  = nic.nic_u.nic_u2.sps.tl2.mem.stdmem. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 3 block 0 memories.
                                                                 Internal:
                                                                 SPS memories:

                                                                   \<23:18\> = Reserved
                                                                   \<17\> = nic.nic_u.nic_u2.sps.sqm_intf.mem.sqcfgmem.
                                                                   \<16\> = nic.nic_u.nic_u2.sps.tl3.mem.tl4_stsmem.
                                                                   \<15:10\> = Reserved
                                                                   \<9\>  = nic.nic_u.nic_u2.sps.tl3.mem.pirmem.
                                                                   \<8\>  = nic.nic_u.nic_u2.sps.tl3.mem.rtmem.
                                                                   \<7\>  = nic.nic_u.nic_u2.sps.tl3.mem.tl3_stsmem.
                                                                   \<6\>  = nic.nic_u.nic_u2.sps.tl3.mem.stdmem.
                                                                   \<5\>  = nic.nic_u.nic_u2.sps.tl3.mem.ccdtmem.
                                                                   \<4\>  = nic.nic_u.nic_u2.sps.tl3.mem.lcdtmem.
                                                                   \<3\>  = Reserved
                                                                   \<2\>  = nic.nic_u.nic_u2.sps.tl2.mem.rtmem.
                                                                   \<1\>  = nic.nic_u.nic_u2.sps.tl2.mem.stsmem.
                                                                   \<0\>  = nic.nic_u.nic_u2.sps.tl2.mem.stdmem. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 3 block 1 memories.
                                                                 Internal:
                                                                 SQM memories:
                                                                   \<15:12\> = Reserved.
                                                                   \<11\> = nic.nic_u.nic_u1.sqm.dse.send.tsopn_mem.
                                                                   \<10\> = nic.nic_u.nic_u1.sqm.dpe.arb.sq_arb_mem_mem.
                                                                   \<9\>  = nic.nic_u.nic_u1.sqm.ctl.sq.sq_mem_mem.
                                                                   \<8\>  = nic.nic_u.nic_u1.sqm.ctl.sq.qs_mem.
                                                                   \<7\>  = Reserved.
                                                                   \<6\>  = nic.nic_u.nic_u1.sqm.ctl.vnic.vnic_mem_mem.
                                                                   \<5\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.dpe_blk.fetch_op_fifo_dpr.
                                                                   \<4\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<3\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.dse_blk.fetch_op_fifo_dpr.
                                                                   \<2\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<1\>  = nic.nic_u.nic_u1.sqm.mqm.qsmem_mem.
                                                                   \<0\>  = nic.nic_u.nic_u1.sqm.mqm.mdmem_mem. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc3_flip1_s cn8; */
    /* struct bdk_nic_pf_ecc3_flip1_s cn81xx; */
    struct bdk_nic_pf_ecc3_flip1_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 3 block 1 memories.
                                                                 Internal:
                                                                 SQM memories:
                                                                   \<15:13\> = Reserved.
                                                                   \<12\> = nic.nic_u.nic_u1.sqm.mqm.mdmem2_mem.
                                                                   \<11\> = nic.nic_u.nic_u1.sqm.dse.send.tsopn_mem.
                                                                   \<10\> = nic.nic_u.nic_u1.sqm.dpe.arb.sq_arb_mem_mem.
                                                                   \<9\>  = nic.nic_u.nic_u1.sqm.ctl.sq.sq_mem_mem.
                                                                   \<8\>  = nic.nic_u.nic_u1.sqm.ctl.sq.qs_mem.
                                                                   \<7\>  = Reserved.
                                                                   \<6\>  = nic.nic_u.nic_u1.sqm.ctl.vnic.vnic_mem_mem.
                                                                   \<5\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.dpe_blk.fetch_op_fifo_dpr.
                                                                   \<4\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<3\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.dse_blk.fetch_op_fifo_dpr.
                                                                   \<2\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<1\>  = nic.nic_u.nic_u1.sqm.mqm.qsmem_mem.
                                                                   \<0\>  = nic.nic_u.nic_u1.sqm.mqm.mdmem_mem. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 3 block 0 memories.
                                                                 Internal:
                                                                 SPS memories:

                                                                   \<23:18\> = Reserved
                                                                   \<17\> = nic.nic_u.nic_u2.sps.sqm_intf.mem.sqcfgmem.
                                                                   \<16\> = nic.nic_u.nic_u2.sps.tl3.mem.tl4_stsmem.
                                                                   \<15:10\> = Reserved
                                                                   \<9\>  = nic.nic_u.nic_u2.sps.tl3.mem.pirmem.
                                                                   \<8\>  = nic.nic_u.nic_u2.sps.tl3.mem.rtmem.
                                                                   \<7\>  = nic.nic_u.nic_u2.sps.tl3.mem.tl3_stsmem.
                                                                   \<6\>  = nic.nic_u.nic_u2.sps.tl3.mem.stdmem.
                                                                   \<5\>  = nic.nic_u.nic_u2.sps.tl3.mem.ccdtmem.
                                                                   \<4\>  = nic.nic_u.nic_u2.sps.tl3.mem.lcdtmem.
                                                                   \<3\>  = Reserved
                                                                   \<2\>  = nic.nic_u.nic_u2.sps.tl2.mem.rtmem.
                                                                   \<1\>  = nic.nic_u.nic_u2.sps.tl2.mem.stsmem.
                                                                   \<0\>  = nic.nic_u.nic_u2.sps.tl2.mem.stdmem. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W) Syndrome flip for group 3 block 0 memories.
                                                                 Internal:
                                                                 SPS memories:

                                                                   \<23:18\> = Reserved
                                                                   \<17\> = nic.nic_u.nic_u2.sps.sqm_intf.mem.sqcfgmem.
                                                                   \<16\> = nic.nic_u.nic_u2.sps.tl3.mem.tl4_stsmem.
                                                                   \<15:10\> = Reserved
                                                                   \<9\>  = nic.nic_u.nic_u2.sps.tl3.mem.pirmem.
                                                                   \<8\>  = nic.nic_u.nic_u2.sps.tl3.mem.rtmem.
                                                                   \<7\>  = nic.nic_u.nic_u2.sps.tl3.mem.tl3_stsmem.
                                                                   \<6\>  = nic.nic_u.nic_u2.sps.tl3.mem.stdmem.
                                                                   \<5\>  = nic.nic_u.nic_u2.sps.tl3.mem.ccdtmem.
                                                                   \<4\>  = nic.nic_u.nic_u2.sps.tl3.mem.lcdtmem.
                                                                   \<3\>  = Reserved
                                                                   \<2\>  = nic.nic_u.nic_u2.sps.tl2.mem.rtmem.
                                                                   \<1\>  = nic.nic_u.nic_u2.sps.tl2.mem.stsmem.
                                                                   \<0\>  = nic.nic_u.nic_u2.sps.tl2.mem.stdmem. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W) Syndrome flip for group 3 block 1 memories.
                                                                 Internal:
                                                                 SQM memories:
                                                                   \<15:13\> = Reserved.
                                                                   \<12\> = nic.nic_u.nic_u1.sqm.mqm.mdmem2_mem.
                                                                   \<11\> = nic.nic_u.nic_u1.sqm.dse.send.tsopn_mem.
                                                                   \<10\> = nic.nic_u.nic_u1.sqm.dpe.arb.sq_arb_mem_mem.
                                                                   \<9\>  = nic.nic_u.nic_u1.sqm.ctl.sq.sq_mem_mem.
                                                                   \<8\>  = nic.nic_u.nic_u1.sqm.ctl.sq.qs_mem.
                                                                   \<7\>  = Reserved.
                                                                   \<6\>  = nic.nic_u.nic_u1.sqm.ctl.vnic.vnic_mem_mem.
                                                                   \<5\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.dpe_blk.fetch_op_fifo_dpr.
                                                                   \<4\>  = nic.nic_u.nic_u1.sqm.dpe.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<3\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.dse_blk.fetch_op_fifo_dpr.
                                                                   \<2\>  = nic.nic_u.nic_u1.sqm.dse.fetch.fetch.fetch_data_fifo_dpr.
                                                                   \<1\>  = nic.nic_u.nic_u1.sqm.mqm.qsmem_mem.
                                                                   \<0\>  = nic.nic_u.nic_u1.sqm.mqm.mdmem_mem. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_pf_ecc3_flip1 bdk_nic_pf_ecc3_flip1_t;

#define BDK_NIC_PF_ECC3_FLIP1 BDK_NIC_PF_ECC3_FLIP1_FUNC()
static inline uint64_t BDK_NIC_PF_ECC3_FLIP1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC3_FLIP1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000001098ll;
    __bdk_csr_fatal("NIC_PF_ECC3_FLIP1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC3_FLIP1 bdk_nic_pf_ecc3_flip1_t
#define bustype_BDK_NIC_PF_ECC3_FLIP1 BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC3_FLIP1 "NIC_PF_ECC3_FLIP1"
#define device_bar_BDK_NIC_PF_ECC3_FLIP1 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC3_FLIP1 0
#define arguments_BDK_NIC_PF_ECC3_FLIP1 -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc3_sbe_ena_w1c
 *
 * NIC ECC 3 Single-bit Error Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_nic_pf_ecc3_sbe_ena_w1c
{
    uint64_t u;
    struct bdk_nic_pf_ecc3_sbe_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1C/H) Reads or clears enable for NIC_PF_ECC3_SBE_INT[BLK1]. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1C/H) Reads or clears enable for NIC_PF_ECC3_SBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1C/H) Reads or clears enable for NIC_PF_ECC3_SBE_INT[BLK0]. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1C/H) Reads or clears enable for NIC_PF_ECC3_SBE_INT[BLK1]. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc3_sbe_ena_w1c_s cn; */
};
typedef union bdk_nic_pf_ecc3_sbe_ena_w1c bdk_nic_pf_ecc3_sbe_ena_w1c_t;

#define BDK_NIC_PF_ECC3_SBE_ENA_W1C BDK_NIC_PF_ECC3_SBE_ENA_W1C_FUNC()
static inline uint64_t BDK_NIC_PF_ECC3_SBE_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC3_SBE_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002610ll;
    __bdk_csr_fatal("NIC_PF_ECC3_SBE_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC3_SBE_ENA_W1C bdk_nic_pf_ecc3_sbe_ena_w1c_t
#define bustype_BDK_NIC_PF_ECC3_SBE_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC3_SBE_ENA_W1C "NIC_PF_ECC3_SBE_ENA_W1C"
#define device_bar_BDK_NIC_PF_ECC3_SBE_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC3_SBE_ENA_W1C 0
#define arguments_BDK_NIC_PF_ECC3_SBE_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc3_sbe_ena_w1s
 *
 * NIC ECC 3 Single-bit Error Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_nic_pf_ecc3_sbe_ena_w1s
{
    uint64_t u;
    struct bdk_nic_pf_ecc3_sbe_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1S/H) Reads or sets enable for NIC_PF_ECC3_SBE_INT[BLK1]. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1S/H) Reads or sets enable for NIC_PF_ECC3_SBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1S/H) Reads or sets enable for NIC_PF_ECC3_SBE_INT[BLK0]. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1S/H) Reads or sets enable for NIC_PF_ECC3_SBE_INT[BLK1]. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc3_sbe_ena_w1s_s cn; */
};
typedef union bdk_nic_pf_ecc3_sbe_ena_w1s bdk_nic_pf_ecc3_sbe_ena_w1s_t;

#define BDK_NIC_PF_ECC3_SBE_ENA_W1S BDK_NIC_PF_ECC3_SBE_ENA_W1S_FUNC()
static inline uint64_t BDK_NIC_PF_ECC3_SBE_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC3_SBE_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002618ll;
    __bdk_csr_fatal("NIC_PF_ECC3_SBE_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC3_SBE_ENA_W1S bdk_nic_pf_ecc3_sbe_ena_w1s_t
#define bustype_BDK_NIC_PF_ECC3_SBE_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC3_SBE_ENA_W1S "NIC_PF_ECC3_SBE_ENA_W1S"
#define device_bar_BDK_NIC_PF_ECC3_SBE_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC3_SBE_ENA_W1S 0
#define arguments_BDK_NIC_PF_ECC3_SBE_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc3_sbe_int
 *
 * NIC ECC 3 Single-bit Error Interrupt Register
 * Reports single-bit errors detected in internal RAM. Each bit corresponds to a different RAM: 0
 * = pass, 1 = fail.
 *
 * Internal:
 * Bits in each field are enumerated by NIC_PF_ECC3_FLIP0.
 */
union bdk_nic_pf_ecc3_sbe_int
{
    uint64_t u;
    struct bdk_nic_pf_ecc3_sbe_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1C/H) RAM error on group 3 block 1 memories. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1C/H) RAM error on group 3 block 0 memories. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1C/H) RAM error on group 3 block 0 memories. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1C/H) RAM error on group 3 block 1 memories. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc3_sbe_int_s cn; */
};
typedef union bdk_nic_pf_ecc3_sbe_int bdk_nic_pf_ecc3_sbe_int_t;

#define BDK_NIC_PF_ECC3_SBE_INT BDK_NIC_PF_ECC3_SBE_INT_FUNC()
static inline uint64_t BDK_NIC_PF_ECC3_SBE_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC3_SBE_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002600ll;
    __bdk_csr_fatal("NIC_PF_ECC3_SBE_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC3_SBE_INT bdk_nic_pf_ecc3_sbe_int_t
#define bustype_BDK_NIC_PF_ECC3_SBE_INT BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC3_SBE_INT "NIC_PF_ECC3_SBE_INT"
#define device_bar_BDK_NIC_PF_ECC3_SBE_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC3_SBE_INT 0
#define arguments_BDK_NIC_PF_ECC3_SBE_INT -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_ecc3_sbe_int_w1s
 *
 * NIC ECC 3 Single-bit Error Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_nic_pf_ecc3_sbe_int_w1s
{
    uint64_t u;
    struct bdk_nic_pf_ecc3_sbe_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1S/H) Reads or sets NIC_PF_ECC3_SBE_INT[BLK1]. */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1S/H) Reads or sets NIC_PF_ECC3_SBE_INT[BLK0]. */
#else /* Word 0 - Little Endian */
        uint64_t blk0                  : 24; /**< [ 23:  0](R/W1S/H) Reads or sets NIC_PF_ECC3_SBE_INT[BLK0]. */
        uint64_t blk1                  : 16; /**< [ 39: 24](R/W1S/H) Reads or sets NIC_PF_ECC3_SBE_INT[BLK1]. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_ecc3_sbe_int_w1s_s cn; */
};
typedef union bdk_nic_pf_ecc3_sbe_int_w1s bdk_nic_pf_ecc3_sbe_int_w1s_t;

#define BDK_NIC_PF_ECC3_SBE_INT_W1S BDK_NIC_PF_ECC3_SBE_INT_W1S_FUNC()
static inline uint64_t BDK_NIC_PF_ECC3_SBE_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECC3_SBE_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000002608ll;
    __bdk_csr_fatal("NIC_PF_ECC3_SBE_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECC3_SBE_INT_W1S bdk_nic_pf_ecc3_sbe_int_w1s_t
#define bustype_BDK_NIC_PF_ECC3_SBE_INT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECC3_SBE_INT_W1S "NIC_PF_ECC3_SBE_INT_W1S"
#define device_bar_BDK_NIC_PF_ECC3_SBE_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECC3_SBE_INT_W1S 0
#define arguments_BDK_NIC_PF_ECC3_SBE_INT_W1S -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_eco0
 *
 * INTERNAL: ECO 0 Register
 */
union bdk_nic_pf_eco0
{
    uint64_t u;
    struct bdk_nic_pf_eco0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_eco0_s cn; */
};
typedef union bdk_nic_pf_eco0 bdk_nic_pf_eco0_t;

#define BDK_NIC_PF_ECO0 BDK_NIC_PF_ECO0_FUNC()
static inline uint64_t BDK_NIC_PF_ECO0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECO0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000003000ll;
    __bdk_csr_fatal("NIC_PF_ECO0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECO0 bdk_nic_pf_eco0_t
#define bustype_BDK_NIC_PF_ECO0 BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECO0 "NIC_PF_ECO0"
#define device_bar_BDK_NIC_PF_ECO0 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECO0 0
#define arguments_BDK_NIC_PF_ECO0 -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_eco1
 *
 * INTERNAL: ECO 1 Register
 */
union bdk_nic_pf_eco1
{
    uint64_t u;
    struct bdk_nic_pf_eco1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_eco1_s cn; */
};
typedef union bdk_nic_pf_eco1 bdk_nic_pf_eco1_t;

#define BDK_NIC_PF_ECO1 BDK_NIC_PF_ECO1_FUNC()
static inline uint64_t BDK_NIC_PF_ECO1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECO1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000003010ll;
    __bdk_csr_fatal("NIC_PF_ECO1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECO1 bdk_nic_pf_eco1_t
#define bustype_BDK_NIC_PF_ECO1 BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECO1 "NIC_PF_ECO1"
#define device_bar_BDK_NIC_PF_ECO1 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECO1 0
#define arguments_BDK_NIC_PF_ECO1 -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_eco2
 *
 * INTERNAL: ECO 2 Register
 */
union bdk_nic_pf_eco2
{
    uint64_t u;
    struct bdk_nic_pf_eco2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_eco2_s cn; */
};
typedef union bdk_nic_pf_eco2 bdk_nic_pf_eco2_t;

#define BDK_NIC_PF_ECO2 BDK_NIC_PF_ECO2_FUNC()
static inline uint64_t BDK_NIC_PF_ECO2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECO2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000003020ll;
    __bdk_csr_fatal("NIC_PF_ECO2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECO2 bdk_nic_pf_eco2_t
#define bustype_BDK_NIC_PF_ECO2 BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECO2 "NIC_PF_ECO2"
#define device_bar_BDK_NIC_PF_ECO2 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECO2 0
#define arguments_BDK_NIC_PF_ECO2 -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_eco3
 *
 * INTERNAL: ECO 3 Register
 */
union bdk_nic_pf_eco3
{
    uint64_t u;
    struct bdk_nic_pf_eco3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_eco3_s cn; */
};
typedef union bdk_nic_pf_eco3 bdk_nic_pf_eco3_t;

#define BDK_NIC_PF_ECO3 BDK_NIC_PF_ECO3_FUNC()
static inline uint64_t BDK_NIC_PF_ECO3_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECO3_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000003030ll;
    __bdk_csr_fatal("NIC_PF_ECO3", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECO3 bdk_nic_pf_eco3_t
#define bustype_BDK_NIC_PF_ECO3 BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECO3 "NIC_PF_ECO3"
#define device_bar_BDK_NIC_PF_ECO3 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECO3 0
#define arguments_BDK_NIC_PF_ECO3 -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_eco4
 *
 * INTERNAL: ECO 4 Register
 */
union bdk_nic_pf_eco4
{
    uint64_t u;
    struct bdk_nic_pf_eco4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_eco4_s cn; */
};
typedef union bdk_nic_pf_eco4 bdk_nic_pf_eco4_t;

#define BDK_NIC_PF_ECO4 BDK_NIC_PF_ECO4_FUNC()
static inline uint64_t BDK_NIC_PF_ECO4_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECO4_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000003040ll;
    __bdk_csr_fatal("NIC_PF_ECO4", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECO4 bdk_nic_pf_eco4_t
#define bustype_BDK_NIC_PF_ECO4 BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECO4 "NIC_PF_ECO4"
#define device_bar_BDK_NIC_PF_ECO4 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECO4 0
#define arguments_BDK_NIC_PF_ECO4 -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_eco5
 *
 * INTERNAL: ECO 5 Register
 */
union bdk_nic_pf_eco5
{
    uint64_t u;
    struct bdk_nic_pf_eco5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_eco5_s cn; */
};
typedef union bdk_nic_pf_eco5 bdk_nic_pf_eco5_t;

#define BDK_NIC_PF_ECO5 BDK_NIC_PF_ECO5_FUNC()
static inline uint64_t BDK_NIC_PF_ECO5_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_ECO5_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000003050ll;
    __bdk_csr_fatal("NIC_PF_ECO5", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_ECO5 bdk_nic_pf_eco5_t
#define bustype_BDK_NIC_PF_ECO5 BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_ECO5 "NIC_PF_ECO5"
#define device_bar_BDK_NIC_PF_ECO5 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_ECO5 0
#define arguments_BDK_NIC_PF_ECO5 -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_int_timer_cfg
 *
 * NIC Interrupt-Timer Configuration Register
 */
union bdk_nic_pf_int_timer_cfg
{
    uint64_t u;
    struct bdk_nic_pf_int_timer_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t clk_per_int_tick      : 24; /**< [ 23:  0](R/W) Specifies tick period for the CQ interrupt timers in NIC_QS()_CQ()_STATUS2[GLOBAL_TIME].
                                                                 The number of coprocessor-clock cycles per tick is 16*[CLK_PER_INT_TICK]. */
#else /* Word 0 - Little Endian */
        uint64_t clk_per_int_tick      : 24; /**< [ 23:  0](R/W) Specifies tick period for the CQ interrupt timers in NIC_QS()_CQ()_STATUS2[GLOBAL_TIME].
                                                                 The number of coprocessor-clock cycles per tick is 16*[CLK_PER_INT_TICK]. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_int_timer_cfg_s cn; */
};
typedef union bdk_nic_pf_int_timer_cfg bdk_nic_pf_int_timer_cfg_t;

#define BDK_NIC_PF_INT_TIMER_CFG BDK_NIC_PF_INT_TIMER_CFG_FUNC()
static inline uint64_t BDK_NIC_PF_INT_TIMER_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_INT_TIMER_CFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000000030ll;
    __bdk_csr_fatal("NIC_PF_INT_TIMER_CFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_INT_TIMER_CFG bdk_nic_pf_int_timer_cfg_t
#define bustype_BDK_NIC_PF_INT_TIMER_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_INT_TIMER_CFG "NIC_PF_INT_TIMER_CFG"
#define device_bar_BDK_NIC_PF_INT_TIMER_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_INT_TIMER_CFG 0
#define arguments_BDK_NIC_PF_INT_TIMER_CFG -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_intf#_bp_cfg
 *
 * NIC Interface Backpressure Configuration Registers
 * Configures backpressure on the NIC receive interface. Index enumerated by NIC_INTF_E.
 */
union bdk_nic_pf_intfx_bp_cfg
{
    uint64_t u;
    struct bdk_nic_pf_intfx_bp_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t bp_ena                : 1;  /**< [ 63: 63](R/W) This bit is used to enable the BP bus for this interface. */
        uint64_t reserved_5_62         : 58;
        uint64_t bp_type               : 1;  /**< [  4:  4](RO/H) Specifies backpressure type: 0=BGX, 1=LBK. */
        uint64_t bp_id                 : 4;  /**< [  3:  0](RO/H) Backpressure block ID for the NIC receive interface. Enumerated by NIC_INTF_BLOCK_E.
                                                                 Internal:
                                                                 Specifies upper 4 bits of X2P channel ID. */
#else /* Word 0 - Little Endian */
        uint64_t bp_id                 : 4;  /**< [  3:  0](RO/H) Backpressure block ID for the NIC receive interface. Enumerated by NIC_INTF_BLOCK_E.
                                                                 Internal:
                                                                 Specifies upper 4 bits of X2P channel ID. */
        uint64_t bp_type               : 1;  /**< [  4:  4](RO/H) Specifies backpressure type: 0=BGX, 1=LBK. */
        uint64_t reserved_5_62         : 58;
        uint64_t bp_ena                : 1;  /**< [ 63: 63](R/W) This bit is used to enable the BP bus for this interface. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_intfx_bp_cfg_s cn; */
};
typedef union bdk_nic_pf_intfx_bp_cfg bdk_nic_pf_intfx_bp_cfg_t;

static inline uint64_t BDK_NIC_PF_INTFX_BP_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_INTFX_BP_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=3))
        return 0x843000005000ll + 8ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=5))
        return 0x843000005000ll + 8ll * ((a) & 0x7);
    __bdk_csr_fatal("NIC_PF_INTFX_BP_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_INTFX_BP_CFG(a) bdk_nic_pf_intfx_bp_cfg_t
#define bustype_BDK_NIC_PF_INTFX_BP_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_INTFX_BP_CFG(a) "NIC_PF_INTFX_BP_CFG"
#define device_bar_BDK_NIC_PF_INTFX_BP_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_INTFX_BP_CFG(a) (a)
#define arguments_BDK_NIC_PF_INTFX_BP_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_intf#_send_cfg
 *
 * NIC Interface Send Configuration Registers
 * Configures the NIC send interface. Index enumerated by NIC_INTF_E.
 */
union bdk_nic_pf_intfx_send_cfg
{
    uint64_t u;
    struct bdk_nic_pf_intfx_send_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t tstmp_wd_period       : 4;  /**< [ 19: 16](R/W) Timestamp watchdog timeout count. The timeout period is 4*(2^[TSTMP_WD_PERIOD]) timer
                                                                 ticks, where each tick is 1024 coprocessor-clock cycles: 0 = 4 ticks, 1 = 8 tick, ...
                                                                 15 = 131072 ticks. If NIC sends a packet with NIC_SEND_HDR_S[TSTMP] = 1 and the
                                                                 packet is not transmitted by the targeted Ethernet port within the timeout period, a
                                                                 CQ entry is posted with NIC_CQE_SEND_S[CQE_TYPE] = NIC_CQE_TYPE_E::SEND_PTP and
                                                                 NIC_CQE_SEND_S[SEND_STATUS] = NIC_CQE_SEND_STATUS_E::TSTMP_TIMEOUT.

                                                                 The timeout period in nanoseconds must be larger than:
                                                                 _  8*(LMAC TX buffer size)/(LMAC Gbits/s data rate) + 10000

                                                                 Where LMAC is the slowest link on this NIC send interface.  The LMAC TX buffer size
                                                                 is defined by BGX()_CMR_TX_LMACS[LMACS]. For example, if
                                                                 BGX()_CMR_TX_LMACS[LMACS]=0x4 (12 KB per LMAC) and the lowest LMAC data rate is 0.1
                                                                 Gbits/s, the timeout period must be \> 8*(12*1024)/0.1 + 10000 ~= 1,000,000 ns. */
        uint64_t reserved_14_15        : 2;
        uint64_t l2ptr                 : 6;  /**< [ 13:  8](R/W) Layer 2 Offset. Specifies the location of the first byte of the L2 (Ethernet) header for
                                                                 all packets sent on the associated NIC interface. NIC examines the L2 header to
                                                                 determine the packet type (unicast, broadcast or multicast) for updating the VNIC transmit
                                                                 statistics. */
        uint64_t reserved_0_7          : 8;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_7          : 8;
        uint64_t l2ptr                 : 6;  /**< [ 13:  8](R/W) Layer 2 Offset. Specifies the location of the first byte of the L2 (Ethernet) header for
                                                                 all packets sent on the associated NIC interface. NIC examines the L2 header to
                                                                 determine the packet type (unicast, broadcast or multicast) for updating the VNIC transmit
                                                                 statistics. */
        uint64_t reserved_14_15        : 2;
        uint64_t tstmp_wd_period       : 4;  /**< [ 19: 16](R/W) Timestamp watchdog timeout count. The timeout period is 4*(2^[TSTMP_WD_PERIOD]) timer
                                                                 ticks, where each tick is 1024 coprocessor-clock cycles: 0 = 4 ticks, 1 = 8 tick, ...
                                                                 15 = 131072 ticks. If NIC sends a packet with NIC_SEND_HDR_S[TSTMP] = 1 and the
                                                                 packet is not transmitted by the targeted Ethernet port within the timeout period, a
                                                                 CQ entry is posted with NIC_CQE_SEND_S[CQE_TYPE] = NIC_CQE_TYPE_E::SEND_PTP and
                                                                 NIC_CQE_SEND_S[SEND_STATUS] = NIC_CQE_SEND_STATUS_E::TSTMP_TIMEOUT.

                                                                 The timeout period in nanoseconds must be larger than:
                                                                 _  8*(LMAC TX buffer size)/(LMAC Gbits/s data rate) + 10000

                                                                 Where LMAC is the slowest link on this NIC send interface.  The LMAC TX buffer size
                                                                 is defined by BGX()_CMR_TX_LMACS[LMACS]. For example, if
                                                                 BGX()_CMR_TX_LMACS[LMACS]=0x4 (12 KB per LMAC) and the lowest LMAC data rate is 0.1
                                                                 Gbits/s, the timeout period must be \> 8*(12*1024)/0.1 + 10000 ~= 1,000,000 ns. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_intfx_send_cfg_s cn; */
};
typedef union bdk_nic_pf_intfx_send_cfg bdk_nic_pf_intfx_send_cfg_t;

static inline uint64_t BDK_NIC_PF_INTFX_SEND_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_INTFX_SEND_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=3))
        return 0x843000004000ll + 8ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=5))
        return 0x843000004000ll + 8ll * ((a) & 0x7);
    __bdk_csr_fatal("NIC_PF_INTFX_SEND_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_INTFX_SEND_CFG(a) bdk_nic_pf_intfx_send_cfg_t
#define bustype_BDK_NIC_PF_INTFX_SEND_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_INTFX_SEND_CFG(a) "NIC_PF_INTFX_SEND_CFG"
#define device_bar_BDK_NIC_PF_INTFX_SEND_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_INTFX_SEND_CFG(a) (a)
#define arguments_BDK_NIC_PF_INTFX_SEND_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_lmac#_cfg
 *
 * NIC LMAC Configuration Registers
 * Index enumerated by NIC_LMAC_E.
 */
union bdk_nic_pf_lmacx_cfg
{
    uint64_t u;
    struct bdk_nic_pf_lmacx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_15_63        : 49;
        uint64_t adjust                : 7;  /**< [ 14:  8](R/W) Signed 4-byte adjustment to all scheduler decisions to account for per packet overhead.
                                                                 Reset of 6 (24 bytes) corresponds to 8 byte preamble, 12 byte IFG, 4 byte FCS. */
        uint64_t reserved_6_7          : 2;
        uint64_t min_pkt_size          : 4;  /**< [  5:  2](R/W) Minimum packet size as a multiple of 4 bytes, excluding FCS potentially appended outside
                                                                 NIC by BGX. If a send descriptor specifies sending a smaller packet than this value, NIC
                                                                 zero pads the packet to this length. */
        uint64_t reserved_0_1          : 2;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_1          : 2;
        uint64_t min_pkt_size          : 4;  /**< [  5:  2](R/W) Minimum packet size as a multiple of 4 bytes, excluding FCS potentially appended outside
                                                                 NIC by BGX. If a send descriptor specifies sending a smaller packet than this value, NIC
                                                                 zero pads the packet to this length. */
        uint64_t reserved_6_7          : 2;
        uint64_t adjust                : 7;  /**< [ 14:  8](R/W) Signed 4-byte adjustment to all scheduler decisions to account for per packet overhead.
                                                                 Reset of 6 (24 bytes) corresponds to 8 byte preamble, 12 byte IFG, 4 byte FCS. */
        uint64_t reserved_15_63        : 49;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_lmacx_cfg_s cn; */
};
typedef union bdk_nic_pf_lmacx_cfg bdk_nic_pf_lmacx_cfg_t;

static inline uint64_t BDK_NIC_PF_LMACX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_LMACX_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=9))
        return 0x843000240000ll + 8ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=17))
        return 0x843000240000ll + 8ll * ((a) & 0x1f);
    __bdk_csr_fatal("NIC_PF_LMACX_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_LMACX_CFG(a) bdk_nic_pf_lmacx_cfg_t
#define bustype_BDK_NIC_PF_LMACX_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_LMACX_CFG(a) "NIC_PF_LMACX_CFG"
#define device_bar_BDK_NIC_PF_LMACX_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_LMACX_CFG(a) (a)
#define arguments_BDK_NIC_PF_LMACX_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_lmac#_cfg2
 *
 * NIC LMAC Configuration Registers
 * Index enumerated by NIC_LMAC_E.
 */
union bdk_nic_pf_lmacx_cfg2
{
    uint64_t u;
    struct bdk_nic_pf_lmacx_cfg2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t max_pkt_size          : 14; /**< [ 13:  0](R/W) Maximum packet size in bytes, excluding FCS potentially appended outside NIC by BGX.
                                                                 Must not be less than the minimum packet size (4*NIC_PF_LMAC()_CFG[MIN_PKT_SIZE]), and
                                                                 should not exceed 9212 (9216 minus 4 byte FCS). If a send descriptor specifies sending a
                                                                 larger packet than this value, NIC drops the packet and posts a CQE with
                                                                 NIC_CQE_SEND_STATUS_E::MAX_SIZE_VIOL. */
#else /* Word 0 - Little Endian */
        uint64_t max_pkt_size          : 14; /**< [ 13:  0](R/W) Maximum packet size in bytes, excluding FCS potentially appended outside NIC by BGX.
                                                                 Must not be less than the minimum packet size (4*NIC_PF_LMAC()_CFG[MIN_PKT_SIZE]), and
                                                                 should not exceed 9212 (9216 minus 4 byte FCS). If a send descriptor specifies sending a
                                                                 larger packet than this value, NIC drops the packet and posts a CQE with
                                                                 NIC_CQE_SEND_STATUS_E::MAX_SIZE_VIOL. */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_lmacx_cfg2_s cn; */
};
typedef union bdk_nic_pf_lmacx_cfg2 bdk_nic_pf_lmacx_cfg2_t;

static inline uint64_t BDK_NIC_PF_LMACX_CFG2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_LMACX_CFG2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=9))
        return 0x843000240100ll + 8ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=17))
        return 0x843000240100ll + 8ll * ((a) & 0x1f);
    __bdk_csr_fatal("NIC_PF_LMACX_CFG2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_LMACX_CFG2(a) bdk_nic_pf_lmacx_cfg2_t
#define bustype_BDK_NIC_PF_LMACX_CFG2(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_LMACX_CFG2(a) "NIC_PF_LMACX_CFG2"
#define device_bar_BDK_NIC_PF_LMACX_CFG2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_LMACX_CFG2(a) (a)
#define arguments_BDK_NIC_PF_LMACX_CFG2(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_lmac#_credit
 *
 * NIC LMAC Credit Registers
 * Index enumerated by NIC_LMAC_E.
 */
union bdk_nic_pf_lmacx_credit
{
    uint64_t u;
    struct bdk_nic_pf_lmacx_credit_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t cc_unit_cnt           : 20; /**< [ 31: 12](R/W/H) Channel-credit unit count. This value, plus 1 MTU, represents the maximum outstanding
                                                                 aggregate channel credit units for this LMAC. A credit unit is 16 bytes.  Note that this
                                                                 20-bit field represents a
                                                                 signed value that decrements towards zero as credits are used. Packets are not allowed to
                                                                 flow when the count is less than zero. As such, the most significant bit should normally
                                                                 be programmed as zero (positive count). This gives a maximum value for this field of 2^19
                                                                 - 1.

                                                                 In order to prevent blocking between BGX LMACs, [CC_ENABLE] should be set to 1 and
                                                                 [CC_UNIT_CNT] should be less than

                                                                 _     ((LMAC TX buffer size in BGX) - (MTU excluding FCS))/16

                                                                 The LMAC TX buffer size is defined by BGX()_CMR_TX_LMACS[LMACS]. For example, if
                                                                 BGX()_CMR_TX_LMACS[LMACS]=0x4 (12 KB per LMAC) and the LMAC's MTU excluding FCS
                                                                 is 9212 bytes (9216 minus 4 byte FCS), then [CC_UNIT_CNT] should be \< (12288 - 9212)/16 =
                                                                 192.

                                                                 For LBK LMACs, [CC_ENABLE] must be set and [CC_UNIT_CNT] must be less than

                                                                 _     (LBK_FIFO_SIZE - (MTU excluding FCS))/16

                                                                 where LBK_FIFO_SIZE = 12288 bytes. */
        uint64_t cc_packet_cnt         : 10; /**< [ 11:  2](R/W/H) Channel-credit packet count. This value, plus 1, represents the maximum outstanding
                                                                 aggregate packet count for this LMAC. Note that this 10-bit field represents a signed
                                                                 value that decrements towards zero as credits are used. Packets are not allowed to flow
                                                                 when the count is less than zero. As such the most significant bit should normally be
                                                                 programmed as zero (positive count). This gives a maximum value for this field of 2^9 - 1. */
        uint64_t cc_enable             : 1;  /**< [  1:  1](R/W) Channel-credit enable. Enables [CC_UNIT_CNT] and [CC_PACKET_CNT] aggregate credit processing. */
        uint64_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0            : 1;
        uint64_t cc_enable             : 1;  /**< [  1:  1](R/W) Channel-credit enable. Enables [CC_UNIT_CNT] and [CC_PACKET_CNT] aggregate credit processing. */
        uint64_t cc_packet_cnt         : 10; /**< [ 11:  2](R/W/H) Channel-credit packet count. This value, plus 1, represents the maximum outstanding
                                                                 aggregate packet count for this LMAC. Note that this 10-bit field represents a signed
                                                                 value that decrements towards zero as credits are used. Packets are not allowed to flow
                                                                 when the count is less than zero. As such the most significant bit should normally be
                                                                 programmed as zero (positive count). This gives a maximum value for this field of 2^9 - 1. */
        uint64_t cc_unit_cnt           : 20; /**< [ 31: 12](R/W/H) Channel-credit unit count. This value, plus 1 MTU, represents the maximum outstanding
                                                                 aggregate channel credit units for this LMAC. A credit unit is 16 bytes.  Note that this
                                                                 20-bit field represents a
                                                                 signed value that decrements towards zero as credits are used. Packets are not allowed to
                                                                 flow when the count is less than zero. As such, the most significant bit should normally
                                                                 be programmed as zero (positive count). This gives a maximum value for this field of 2^19
                                                                 - 1.

                                                                 In order to prevent blocking between BGX LMACs, [CC_ENABLE] should be set to 1 and
                                                                 [CC_UNIT_CNT] should be less than

                                                                 _     ((LMAC TX buffer size in BGX) - (MTU excluding FCS))/16

                                                                 The LMAC TX buffer size is defined by BGX()_CMR_TX_LMACS[LMACS]. For example, if
                                                                 BGX()_CMR_TX_LMACS[LMACS]=0x4 (12 KB per LMAC) and the LMAC's MTU excluding FCS
                                                                 is 9212 bytes (9216 minus 4 byte FCS), then [CC_UNIT_CNT] should be \< (12288 - 9212)/16 =
                                                                 192.

                                                                 For LBK LMACs, [CC_ENABLE] must be set and [CC_UNIT_CNT] must be less than

                                                                 _     (LBK_FIFO_SIZE - (MTU excluding FCS))/16

                                                                 where LBK_FIFO_SIZE = 12288 bytes. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_lmacx_credit_s cn8; */
    /* struct bdk_nic_pf_lmacx_credit_s cn81xx; */
    struct bdk_nic_pf_lmacx_credit_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t cc_unit_cnt           : 20; /**< [ 31: 12](R/W/H) Channel-credit unit count. This value, plus 1 MTU, represents the maximum outstanding
                                                                 aggregate channel credit units for this LMAC. A credit unit is 16 bytes.  Note that this
                                                                 20-bit field represents a
                                                                 signed value that decrements towards zero as credits are used. Packets are not allowed to
                                                                 flow when the count is less than zero. As such, the most significant bit should normally
                                                                 be programmed as zero (positive count). This gives a maximum value for this field of 2^19
                                                                 - 1.

                                                                 In order to prevent blocking between BGX LMACs, [CC_ENABLE] should be set to 1 and
                                                                 [CC_UNIT_CNT] should be less than

                                                                 _     ((LMAC TX buffer size in BGX) - (MTU excluding FCS))/16

                                                                 The LMAC TX buffer size is defined by BGX()_CMR_TX_LMACS[LMACS]. For example, if
                                                                 BGX()_CMR_TX_LMACS[LMACS]=0x4 (12 KB per LMAC) and the LMAC's MTU excluding FCS
                                                                 is 9212 bytes (9216 minus 4 byte FCS), then [CC_UNIT_CNT] should be \< (12288 - 9212)/16 =
                                                                 192.

                                                                 For LBK LMACs, the recommended configuration is [CC_ENABLE] = 1 and [CC_UNIT_CNT] = 512.

                                                                 Internal:
                                                                 LBK value allows for 80 Gbps loopback data rate with 800ns round trip latency:

                                                                 _ Minimum LBK in-flight data = 80*800 = 64Kbits = 512 credit units.

                                                                 Note: maximum LBK in-fligh data = min + MTU. */
        uint64_t cc_packet_cnt         : 10; /**< [ 11:  2](R/W/H) Channel-credit packet count. This value, plus 1, represents the maximum outstanding
                                                                 aggregate packet count for this LMAC. Note that this 10-bit field represents a signed
                                                                 value that decrements towards zero as credits are used. Packets are not allowed to flow
                                                                 when the count is less than zero. As such the most significant bit should normally be
                                                                 programmed as zero (positive count). This gives a maximum value for this field of 2^9 - 1. */
        uint64_t cc_enable             : 1;  /**< [  1:  1](R/W) Channel-credit enable. Enables [CC_UNIT_CNT] and [CC_PACKET_CNT] aggregate credit processing. */
        uint64_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0            : 1;
        uint64_t cc_enable             : 1;  /**< [  1:  1](R/W) Channel-credit enable. Enables [CC_UNIT_CNT] and [CC_PACKET_CNT] aggregate credit processing. */
        uint64_t cc_packet_cnt         : 10; /**< [ 11:  2](R/W/H) Channel-credit packet count. This value, plus 1, represents the maximum outstanding
                                                                 aggregate packet count for this LMAC. Note that this 10-bit field represents a signed
                                                                 value that decrements towards zero as credits are used. Packets are not allowed to flow
                                                                 when the count is less than zero. As such the most significant bit should normally be
                                                                 programmed as zero (positive count). This gives a maximum value for this field of 2^9 - 1. */
        uint64_t cc_unit_cnt           : 20; /**< [ 31: 12](R/W/H) Channel-credit unit count. This value, plus 1 MTU, represents the maximum outstanding
                                                                 aggregate channel credit units for this LMAC. A credit unit is 16 bytes.  Note that this
                                                                 20-bit field represents a
                                                                 signed value that decrements towards zero as credits are used. Packets are not allowed to
                                                                 flow when the count is less than zero. As such, the most significant bit should normally
                                                                 be programmed as zero (positive count). This gives a maximum value for this field of 2^19
                                                                 - 1.

                                                                 In order to prevent blocking between BGX LMACs, [CC_ENABLE] should be set to 1 and
                                                                 [CC_UNIT_CNT] should be less than

                                                                 _     ((LMAC TX buffer size in BGX) - (MTU excluding FCS))/16

                                                                 The LMAC TX buffer size is defined by BGX()_CMR_TX_LMACS[LMACS]. For example, if
                                                                 BGX()_CMR_TX_LMACS[LMACS]=0x4 (12 KB per LMAC) and the LMAC's MTU excluding FCS
                                                                 is 9212 bytes (9216 minus 4 byte FCS), then [CC_UNIT_CNT] should be \< (12288 - 9212)/16 =
                                                                 192.

                                                                 For LBK LMACs, the recommended configuration is [CC_ENABLE] = 1 and [CC_UNIT_CNT] = 512.

                                                                 Internal:
                                                                 LBK value allows for 80 Gbps loopback data rate with 800ns round trip latency:

                                                                 _ Minimum LBK in-flight data = 80*800 = 64Kbits = 512 credit units.

                                                                 Note: maximum LBK in-fligh data = min + MTU. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_pf_lmacx_credit bdk_nic_pf_lmacx_credit_t;

static inline uint64_t BDK_NIC_PF_LMACX_CREDIT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_LMACX_CREDIT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=9))
        return 0x843000244000ll + 8ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=17))
        return 0x843000244000ll + 8ll * ((a) & 0x1f);
    __bdk_csr_fatal("NIC_PF_LMACX_CREDIT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_LMACX_CREDIT(a) bdk_nic_pf_lmacx_credit_t
#define bustype_BDK_NIC_PF_LMACX_CREDIT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_LMACX_CREDIT(a) "NIC_PF_LMACX_CREDIT"
#define device_bar_BDK_NIC_PF_LMACX_CREDIT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_LMACX_CREDIT(a) (a)
#define arguments_BDK_NIC_PF_LMACX_CREDIT(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_lmac#_sw_xoff
 *
 * NIC LMAC Software Controlled XOFF Registers
 * Index enumerated by NIC_LMAC_E.
 */
union bdk_nic_pf_lmacx_sw_xoff
{
    uint64_t u;
    struct bdk_nic_pf_lmacx_sw_xoff_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t sw_xoff               : 1;  /**< [  0:  0](R/W) Software XOFF. When set, this LMAC does not send traffic. */
#else /* Word 0 - Little Endian */
        uint64_t sw_xoff               : 1;  /**< [  0:  0](R/W) Software XOFF. When set, this LMAC does not send traffic. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_lmacx_sw_xoff_s cn; */
};
typedef union bdk_nic_pf_lmacx_sw_xoff bdk_nic_pf_lmacx_sw_xoff_t;

static inline uint64_t BDK_NIC_PF_LMACX_SW_XOFF(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_LMACX_SW_XOFF(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=9))
        return 0x843000242000ll + 8ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=17))
        return 0x843000242000ll + 8ll * ((a) & 0x1f);
    __bdk_csr_fatal("NIC_PF_LMACX_SW_XOFF", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_LMACX_SW_XOFF(a) bdk_nic_pf_lmacx_sw_xoff_t
#define bustype_BDK_NIC_PF_LMACX_SW_XOFF(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_LMACX_SW_XOFF(a) "NIC_PF_LMACX_SW_XOFF"
#define device_bar_BDK_NIC_PF_LMACX_SW_XOFF(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_LMACX_SW_XOFF(a) (a)
#define arguments_BDK_NIC_PF_LMACX_SW_XOFF(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_mbox_ena_w1c#
 *
 * NIC PF Mailbox Enable Clear Registers
 * This register clears interrupt enable bits.
 */
union bdk_nic_pf_mbox_ena_w1cx
{
    uint64_t u;
    struct bdk_nic_pf_mbox_ena_w1cx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for NIC_PF_MBOX_INT(0)[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for NIC_PF_MBOX_INT(0)[MBOX]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_mbox_ena_w1cx_s cn; */
};
typedef union bdk_nic_pf_mbox_ena_w1cx bdk_nic_pf_mbox_ena_w1cx_t;

static inline uint64_t BDK_NIC_PF_MBOX_ENA_W1CX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_MBOX_ENA_W1CX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a==0))
        return 0x843000000450ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("NIC_PF_MBOX_ENA_W1CX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_MBOX_ENA_W1CX(a) bdk_nic_pf_mbox_ena_w1cx_t
#define bustype_BDK_NIC_PF_MBOX_ENA_W1CX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_MBOX_ENA_W1CX(a) "NIC_PF_MBOX_ENA_W1CX"
#define device_bar_BDK_NIC_PF_MBOX_ENA_W1CX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_MBOX_ENA_W1CX(a) (a)
#define arguments_BDK_NIC_PF_MBOX_ENA_W1CX(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_mbox_ena_w1s#
 *
 * NIC PF Mailbox Enable Set Registers
 * This register sets interrupt enable bits.
 */
union bdk_nic_pf_mbox_ena_w1sx
{
    uint64_t u;
    struct bdk_nic_pf_mbox_ena_w1sx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for NIC_PF_MBOX_INT(0)[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for NIC_PF_MBOX_INT(0)[MBOX]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_mbox_ena_w1sx_s cn; */
};
typedef union bdk_nic_pf_mbox_ena_w1sx bdk_nic_pf_mbox_ena_w1sx_t;

static inline uint64_t BDK_NIC_PF_MBOX_ENA_W1SX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_MBOX_ENA_W1SX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a==0))
        return 0x843000000470ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("NIC_PF_MBOX_ENA_W1SX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_MBOX_ENA_W1SX(a) bdk_nic_pf_mbox_ena_w1sx_t
#define bustype_BDK_NIC_PF_MBOX_ENA_W1SX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_MBOX_ENA_W1SX(a) "NIC_PF_MBOX_ENA_W1SX"
#define device_bar_BDK_NIC_PF_MBOX_ENA_W1SX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_MBOX_ENA_W1SX(a) (a)
#define arguments_BDK_NIC_PF_MBOX_ENA_W1SX(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_mbox_int#
 *
 * NIC PF Mailbox Interrupt Registers
 */
union bdk_nic_pf_mbox_intx
{
    uint64_t u;
    struct bdk_nic_pf_mbox_intx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1C/H) One interrupt bit per VF, e.g. NIC_PF_MBOX_INT(0)[MBOX\<5\>] for VF 5.
                                                                 Each bit is set when the associated NIC_VF()_PF_MBOX(1) register is written.
                                                                 Bits corresponding to unimplemented VFs (above bit 7) are never set by hardware. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1C/H) One interrupt bit per VF, e.g. NIC_PF_MBOX_INT(0)[MBOX\<5\>] for VF 5.
                                                                 Each bit is set when the associated NIC_VF()_PF_MBOX(1) register is written.
                                                                 Bits corresponding to unimplemented VFs (above bit 7) are never set by hardware. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_mbox_intx_s cn8; */
    /* struct bdk_nic_pf_mbox_intx_s cn81xx; */
    struct bdk_nic_pf_mbox_intx_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1C/H) One interrupt bit per VF, e.g. NIC_PF_MBOX_INT(0)[MBOX\<5\>] for VF 5.
                                                                 Each bit is set when the associated NIC_VF()_PF_MBOX(1) register is written.
                                                                 Bits corresponding to unimplemented VFs (above bit 31) are never set by hardware. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1C/H) One interrupt bit per VF, e.g. NIC_PF_MBOX_INT(0)[MBOX\<5\>] for VF 5.
                                                                 Each bit is set when the associated NIC_VF()_PF_MBOX(1) register is written.
                                                                 Bits corresponding to unimplemented VFs (above bit 31) are never set by hardware. */
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_pf_mbox_intx bdk_nic_pf_mbox_intx_t;

static inline uint64_t BDK_NIC_PF_MBOX_INTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_MBOX_INTX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a==0))
        return 0x843000000410ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("NIC_PF_MBOX_INTX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_MBOX_INTX(a) bdk_nic_pf_mbox_intx_t
#define bustype_BDK_NIC_PF_MBOX_INTX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_MBOX_INTX(a) "NIC_PF_MBOX_INTX"
#define device_bar_BDK_NIC_PF_MBOX_INTX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_MBOX_INTX(a) (a)
#define arguments_BDK_NIC_PF_MBOX_INTX(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_mbox_int_w1s#
 *
 * NIC PF Mailbox Interrupt Set Registers
 * This register sets interrupt bits.
 */
union bdk_nic_pf_mbox_int_w1sx
{
    uint64_t u;
    struct bdk_nic_pf_mbox_int_w1sx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1S/H) Reads or sets NIC_PF_MBOX_INT(0)[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1S/H) Reads or sets NIC_PF_MBOX_INT(0)[MBOX]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_mbox_int_w1sx_s cn; */
};
typedef union bdk_nic_pf_mbox_int_w1sx bdk_nic_pf_mbox_int_w1sx_t;

static inline uint64_t BDK_NIC_PF_MBOX_INT_W1SX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_MBOX_INT_W1SX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a==0))
        return 0x843000000430ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("NIC_PF_MBOX_INT_W1SX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_MBOX_INT_W1SX(a) bdk_nic_pf_mbox_int_w1sx_t
#define bustype_BDK_NIC_PF_MBOX_INT_W1SX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_MBOX_INT_W1SX(a) "NIC_PF_MBOX_INT_W1SX"
#define device_bar_BDK_NIC_PF_MBOX_INT_W1SX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_MBOX_INT_W1SX(a) (a)
#define arguments_BDK_NIC_PF_MBOX_INT_W1SX(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_mcam#_ena
 *
 * NIC MCAM Enable Registers
 * This register enables the corresponding ECAM entry number.
 */
union bdk_nic_pf_mcamx_ena
{
    uint64_t u;
    struct bdk_nic_pf_mcamx_ena_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t valid                 : 1;  /**< [ 63: 63](R/W) Valid. */
        uint64_t reserved_0_62         : 63;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_62         : 63;
        uint64_t valid                 : 1;  /**< [ 63: 63](R/W) Valid. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_mcamx_ena_s cn; */
};
typedef union bdk_nic_pf_mcamx_ena bdk_nic_pf_mcamx_ena_t;

static inline uint64_t BDK_NIC_PF_MCAMX_ENA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_MCAMX_ENA(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=191))
        return 0x843000100000ll + 0x10ll * ((a) & 0xff);
    __bdk_csr_fatal("NIC_PF_MCAMX_ENA", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_MCAMX_ENA(a) bdk_nic_pf_mcamx_ena_t
#define bustype_BDK_NIC_PF_MCAMX_ENA(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_MCAMX_ENA(a) "NIC_PF_MCAMX_ENA"
#define device_bar_BDK_NIC_PF_MCAMX_ENA(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_MCAMX_ENA(a) (a)
#define arguments_BDK_NIC_PF_MCAMX_ENA(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_mcam#_m#_data
 *
 * NIC MCAM Data Registers
 * This register specifies the ternary match data for the corresponding ECAM entry
 * number.
 */
union bdk_nic_pf_mcamx_mx_data
{
    uint64_t u;
    struct bdk_nic_pf_mcamx_mx_data_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t mcam_data1            : 24; /**< [ 47: 24](R/W) See description for [MCAM_DATA0]. */
        uint64_t mcam_data0            : 24; /**< [ 23:  0](R/W) Comparison ternary data. The meaning of each data bit uses the
                                                                 NIC_RX_MCAM_SFIELD_S structure.

                                                                 The field value is ternary, where each bit matches as follows:

                                                                 _ [MCAM_DATA1]\<n\>=0, [MCAM_DATA0]\<n\>=0: Always match; data\<n\> don't care.
                                                                 _ [MCAM_DATA1]\<n\>=0, [MCAM_DATA0]\<n\>=1: Match when data\<n\> == 0.
                                                                 _ [MCAM_DATA1]\<n\>=1, [MCAM_DATA0]\<n\>=0: Match when data\<n\> == 1.
                                                                 _ [MCAM_DATA1]\<n\>=1, [MCAM_DATA0]\<n\>=1: Reserved.

                                                                 Note hardware does not allow the "reserved" combination to get written to the MCAM.

                                                                 _ NIC_PF_MCAM()_M(0)_DATA() corresponds to NIC_RX_MCAM_SFIELD_S\<23:0\>.
                                                                 _ NIC_PF_MCAM()_M(1)_DATA() corresponds to NIC_RX_MCAM_SFIELD_S\<47:24\>.
                                                                 _ NIC_PF_MCAM()_M(2)_DATA() corresponds to NIC_RX_MCAM_SFIELD_S\<71:48\>.
                                                                 _ NIC_PF_MCAM()_M(3)_DATA() corresponds to NIC_RX_MCAM_SFIELD_S\<95:72\>.
                                                                 _ NIC_PF_MCAM()_M(4)_DATA() corresponds to NIC_RX_MCAM_SFIELD_S\<119:96\>.
                                                                 _ NIC_PF_MCAM()_M(5)_DATA() corresponds to NIC_RX_MCAM_SFIELD_S\<143:120\>. */
#else /* Word 0 - Little Endian */
        uint64_t mcam_data0            : 24; /**< [ 23:  0](R/W) Comparison ternary data. The meaning of each data bit uses the
                                                                 NIC_RX_MCAM_SFIELD_S structure.

                                                                 The field value is ternary, where each bit matches as follows:

                                                                 _ [MCAM_DATA1]\<n\>=0, [MCAM_DATA0]\<n\>=0: Always match; data\<n\> don't care.
                                                                 _ [MCAM_DATA1]\<n\>=0, [MCAM_DATA0]\<n\>=1: Match when data\<n\> == 0.
                                                                 _ [MCAM_DATA1]\<n\>=1, [MCAM_DATA0]\<n\>=0: Match when data\<n\> == 1.
                                                                 _ [MCAM_DATA1]\<n\>=1, [MCAM_DATA0]\<n\>=1: Reserved.

                                                                 Note hardware does not allow the "reserved" combination to get written to the MCAM.

                                                                 _ NIC_PF_MCAM()_M(0)_DATA() corresponds to NIC_RX_MCAM_SFIELD_S\<23:0\>.
                                                                 _ NIC_PF_MCAM()_M(1)_DATA() corresponds to NIC_RX_MCAM_SFIELD_S\<47:24\>.
                                                                 _ NIC_PF_MCAM()_M(2)_DATA() corresponds to NIC_RX_MCAM_SFIELD_S\<71:48\>.
                                                                 _ NIC_PF_MCAM()_M(3)_DATA() corresponds to NIC_RX_MCAM_SFIELD_S\<95:72\>.
                                                                 _ NIC_PF_MCAM()_M(4)_DATA() corresponds to NIC_RX_MCAM_SFIELD_S\<119:96\>.
                                                                 _ NIC_PF_MCAM()_M(5)_DATA() corresponds to NIC_RX_MCAM_SFIELD_S\<143:120\>. */
        uint64_t mcam_data1            : 24; /**< [ 47: 24](R/W) See description for [MCAM_DATA0]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_mcamx_mx_data_s cn; */
};
typedef union bdk_nic_pf_mcamx_mx_data bdk_nic_pf_mcamx_mx_data_t;

static inline uint64_t BDK_NIC_PF_MCAMX_MX_DATA(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_MCAMX_MX_DATA(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && ((a<=191) && (b<=5)))
        return 0x843000110000ll + 0x40ll * ((a) & 0xff) + 8ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_PF_MCAMX_MX_DATA", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_MCAMX_MX_DATA(a,b) bdk_nic_pf_mcamx_mx_data_t
#define bustype_BDK_NIC_PF_MCAMX_MX_DATA(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_MCAMX_MX_DATA(a,b) "NIC_PF_MCAMX_MX_DATA"
#define device_bar_BDK_NIC_PF_MCAMX_MX_DATA(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_MCAMX_MX_DATA(a,b) (a)
#define arguments_BDK_NIC_PF_MCAMX_MX_DATA(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_pf_mcam_ctrl
 *
 * NIC MCAM Control Register
 * This register controls the MCAM.
 */
union bdk_nic_pf_mcam_ctrl
{
    uint64_t u;
    struct bdk_nic_pf_mcam_ctrl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t ena_scrub             : 1;  /**< [  0:  0](R/W) Enable MCAM ECC scrubber.
                                                                 When the scrubber detects a SBE in the MCAM, it writes the corrected data back to this
                                                                 row.
                                                                 When the scrubber detects a DBE in the MCAM, it writes all 0x0s to disable this line. */
#else /* Word 0 - Little Endian */
        uint64_t ena_scrub             : 1;  /**< [  0:  0](R/W) Enable MCAM ECC scrubber.
                                                                 When the scrubber detects a SBE in the MCAM, it writes the corrected data back to this
                                                                 row.
                                                                 When the scrubber detects a DBE in the MCAM, it writes all 0x0s to disable this line. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_mcam_ctrl_s cn; */
};
typedef union bdk_nic_pf_mcam_ctrl bdk_nic_pf_mcam_ctrl_t;

#define BDK_NIC_PF_MCAM_CTRL BDK_NIC_PF_MCAM_CTRL_FUNC()
static inline uint64_t BDK_NIC_PF_MCAM_CTRL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_MCAM_CTRL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000120000ll;
    __bdk_csr_fatal("NIC_PF_MCAM_CTRL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_MCAM_CTRL bdk_nic_pf_mcam_ctrl_t
#define bustype_BDK_NIC_PF_MCAM_CTRL BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_MCAM_CTRL "NIC_PF_MCAM_CTRL"
#define device_bar_BDK_NIC_PF_MCAM_CTRL 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_MCAM_CTRL 0
#define arguments_BDK_NIC_PF_MCAM_CTRL -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_mpi#_cfg
 *
 * NIC MPI Table Registers
 */
union bdk_nic_pf_mpix_cfg
{
    uint64_t u;
    struct bdk_nic_pf_mpix_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_29_63        : 35;
        uint64_t vnic                  : 5;  /**< [ 28: 24](R/W) VNIC receiving this channel, and determines which RSS algorithms are enabled using
                                                                 NIC_VNIC()_RSS_CFG. */
        uint64_t rss_size              : 4;  /**< [ 23: 20](R/W) Bits of RSS hash to add in RSSI calculation.
                                                                 0x0 = RSS is disabled.
                                                                 0x1 = RSSI_ADDER\<0\> included in RSSI.
                                                                 0x2 = RSSI_ADDER\<1:0\> included in RSSI.
                                                                 0x3 = RSSI_ADDER\<2:0\> included in RSSI.
                                                                 0x4 = RSSI_ADDER\<3:0\> included in RSSI.
                                                                 0x5 = RSSI_ADDER\<4:0\> included in RSSI.
                                                                 0x6 = RSSI_ADDER\<5:0\> included in RSSI.
                                                                 0x7 = RSSI_ADDER\<6:0\> included in RSSI.
                                                                 0x8 = RSSI_ADDER\<7:0\> included in RSSI.
                                                                 0x9-0xF = Reserved.

                                                                 RSSI_ADDER\<7:0\> = RSS_TAG\<7:0\> ^ RSS_TAG\<15:8\> ^ RSS_TAG\<23:16\> ^ RSS_TAG\<31:24\>. */
        uint64_t reserved_10_19        : 10;
        uint64_t rssi_base             : 10; /**< [  9:  0](R/W) Base index into NIC_PF_RSSI()_RQ. */
#else /* Word 0 - Little Endian */
        uint64_t rssi_base             : 10; /**< [  9:  0](R/W) Base index into NIC_PF_RSSI()_RQ. */
        uint64_t reserved_10_19        : 10;
        uint64_t rss_size              : 4;  /**< [ 23: 20](R/W) Bits of RSS hash to add in RSSI calculation.
                                                                 0x0 = RSS is disabled.
                                                                 0x1 = RSSI_ADDER\<0\> included in RSSI.
                                                                 0x2 = RSSI_ADDER\<1:0\> included in RSSI.
                                                                 0x3 = RSSI_ADDER\<2:0\> included in RSSI.
                                                                 0x4 = RSSI_ADDER\<3:0\> included in RSSI.
                                                                 0x5 = RSSI_ADDER\<4:0\> included in RSSI.
                                                                 0x6 = RSSI_ADDER\<5:0\> included in RSSI.
                                                                 0x7 = RSSI_ADDER\<6:0\> included in RSSI.
                                                                 0x8 = RSSI_ADDER\<7:0\> included in RSSI.
                                                                 0x9-0xF = Reserved.

                                                                 RSSI_ADDER\<7:0\> = RSS_TAG\<7:0\> ^ RSS_TAG\<15:8\> ^ RSS_TAG\<23:16\> ^ RSS_TAG\<31:24\>. */
        uint64_t vnic                  : 5;  /**< [ 28: 24](R/W) VNIC receiving this channel, and determines which RSS algorithms are enabled using
                                                                 NIC_VNIC()_RSS_CFG. */
        uint64_t reserved_29_63        : 35;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_mpix_cfg_s cn8; */
    struct bdk_nic_pf_mpix_cfg_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_31_63        : 33;
        uint64_t reserved_27_30        : 4;
        uint64_t vnic                  : 3;  /**< [ 26: 24](R/W) VNIC receiving this channel, and determines which RSS algorithms are enabled using
                                                                 NIC_VNIC()_RSS_CFG. */
        uint64_t rss_size              : 4;  /**< [ 23: 20](R/W) Bits of RSS hash to add in RSSI calculation.
                                                                 0x0 = RSS is disabled.
                                                                 0x1 = RSSI_ADDER\<0\> included in RSSI.
                                                                 0x2 = RSSI_ADDER\<1:0\> included in RSSI.
                                                                 0x3 = RSSI_ADDER\<2:0\> included in RSSI.
                                                                 0x4 = RSSI_ADDER\<3:0\> included in RSSI.
                                                                 0x5 = RSSI_ADDER\<4:0\> included in RSSI.
                                                                 0x6 = RSSI_ADDER\<5:0\> included in RSSI.
                                                                 0x7 = RSSI_ADDER\<6:0\> included in RSSI.
                                                                 0x8 = RSSI_ADDER\<7:0\> included in RSSI.
                                                                 0x9-0xF = Reserved.

                                                                 RSSI_ADDER\<7:0\> = RSS_TAG\<7:0\> ^ RSS_TAG\<15:8\> ^ RSS_TAG\<23:16\> ^ RSS_TAG\<31:24\>. */
        uint64_t reserved_16_19        : 4;
        uint64_t reserved_12_15        : 4;
        uint64_t reserved_8_11         : 4;
        uint64_t rssi_base             : 8;  /**< [  7:  0](R/W) Base index into NIC_PF_RSSI()_RQ. */
#else /* Word 0 - Little Endian */
        uint64_t rssi_base             : 8;  /**< [  7:  0](R/W) Base index into NIC_PF_RSSI()_RQ. */
        uint64_t reserved_8_11         : 4;
        uint64_t reserved_12_15        : 4;
        uint64_t reserved_16_19        : 4;
        uint64_t rss_size              : 4;  /**< [ 23: 20](R/W) Bits of RSS hash to add in RSSI calculation.
                                                                 0x0 = RSS is disabled.
                                                                 0x1 = RSSI_ADDER\<0\> included in RSSI.
                                                                 0x2 = RSSI_ADDER\<1:0\> included in RSSI.
                                                                 0x3 = RSSI_ADDER\<2:0\> included in RSSI.
                                                                 0x4 = RSSI_ADDER\<3:0\> included in RSSI.
                                                                 0x5 = RSSI_ADDER\<4:0\> included in RSSI.
                                                                 0x6 = RSSI_ADDER\<5:0\> included in RSSI.
                                                                 0x7 = RSSI_ADDER\<6:0\> included in RSSI.
                                                                 0x8 = RSSI_ADDER\<7:0\> included in RSSI.
                                                                 0x9-0xF = Reserved.

                                                                 RSSI_ADDER\<7:0\> = RSS_TAG\<7:0\> ^ RSS_TAG\<15:8\> ^ RSS_TAG\<23:16\> ^ RSS_TAG\<31:24\>. */
        uint64_t vnic                  : 3;  /**< [ 26: 24](R/W) VNIC receiving this channel, and determines which RSS algorithms are enabled using
                                                                 NIC_VNIC()_RSS_CFG. */
        uint64_t reserved_27_30        : 4;
        uint64_t reserved_31_63        : 33;
#endif /* Word 0 - End */
    } cn81xx;
    struct bdk_nic_pf_mpix_cfg_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_31_63        : 33;
        uint64_t reserved_29_30        : 2;
        uint64_t vnic                  : 5;  /**< [ 28: 24](R/W) VNIC receiving this channel, and determines which RSS algorithms are enabled using
                                                                 NIC_VNIC()_RSS_CFG. */
        uint64_t rss_size              : 4;  /**< [ 23: 20](R/W) Bits of RSS hash to add in RSSI calculation.
                                                                 0x0 = RSS is disabled.
                                                                 0x1 = RSSI_ADDER\<0\> included in RSSI.
                                                                 0x2 = RSSI_ADDER\<1:0\> included in RSSI.
                                                                 0x3 = RSSI_ADDER\<2:0\> included in RSSI.
                                                                 0x4 = RSSI_ADDER\<3:0\> included in RSSI.
                                                                 0x5 = RSSI_ADDER\<4:0\> included in RSSI.
                                                                 0x6 = RSSI_ADDER\<5:0\> included in RSSI.
                                                                 0x7 = RSSI_ADDER\<6:0\> included in RSSI.
                                                                 0x8 = RSSI_ADDER\<7:0\> included in RSSI.
                                                                 0x9-0xF = Reserved.

                                                                 RSSI_ADDER\<7:0\> = RSS_TAG\<7:0\> ^ RSS_TAG\<15:8\> ^ RSS_TAG\<23:16\> ^ RSS_TAG\<31:24\>. */
        uint64_t reserved_16_19        : 4;
        uint64_t reserved_12_15        : 4;
        uint64_t reserved_10_11        : 2;
        uint64_t rssi_base             : 10; /**< [  9:  0](R/W) Base index into NIC_PF_RSSI()_RQ. */
#else /* Word 0 - Little Endian */
        uint64_t rssi_base             : 10; /**< [  9:  0](R/W) Base index into NIC_PF_RSSI()_RQ. */
        uint64_t reserved_10_11        : 2;
        uint64_t reserved_12_15        : 4;
        uint64_t reserved_16_19        : 4;
        uint64_t rss_size              : 4;  /**< [ 23: 20](R/W) Bits of RSS hash to add in RSSI calculation.
                                                                 0x0 = RSS is disabled.
                                                                 0x1 = RSSI_ADDER\<0\> included in RSSI.
                                                                 0x2 = RSSI_ADDER\<1:0\> included in RSSI.
                                                                 0x3 = RSSI_ADDER\<2:0\> included in RSSI.
                                                                 0x4 = RSSI_ADDER\<3:0\> included in RSSI.
                                                                 0x5 = RSSI_ADDER\<4:0\> included in RSSI.
                                                                 0x6 = RSSI_ADDER\<5:0\> included in RSSI.
                                                                 0x7 = RSSI_ADDER\<6:0\> included in RSSI.
                                                                 0x8 = RSSI_ADDER\<7:0\> included in RSSI.
                                                                 0x9-0xF = Reserved.

                                                                 RSSI_ADDER\<7:0\> = RSS_TAG\<7:0\> ^ RSS_TAG\<15:8\> ^ RSS_TAG\<23:16\> ^ RSS_TAG\<31:24\>. */
        uint64_t vnic                  : 5;  /**< [ 28: 24](R/W) VNIC receiving this channel, and determines which RSS algorithms are enabled using
                                                                 NIC_VNIC()_RSS_CFG. */
        uint64_t reserved_29_30        : 2;
        uint64_t reserved_31_63        : 33;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_pf_mpix_cfg bdk_nic_pf_mpix_cfg_t;

static inline uint64_t BDK_NIC_PF_MPIX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_MPIX_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=511))
        return 0x843000210000ll + 8ll * ((a) & 0x1ff);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=2047))
        return 0x843000210000ll + 8ll * ((a) & 0x7ff);
    __bdk_csr_fatal("NIC_PF_MPIX_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_MPIX_CFG(a) bdk_nic_pf_mpix_cfg_t
#define bustype_BDK_NIC_PF_MPIX_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_MPIX_CFG(a) "NIC_PF_MPIX_CFG"
#define device_bar_BDK_NIC_PF_MPIX_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_MPIX_CFG(a) (a)
#define arguments_BDK_NIC_PF_MPIX_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_msix_pba#
 *
 * NIC PF MSI-X Pending-Bit-Array Registers
 * This register is the MSI-X PBA table, the bit number is indexed by the NIC_PF_INT_VEC_E
 * enumeration.
 */
union bdk_nic_pf_msix_pbax
{
    uint64_t u;
    struct bdk_nic_pf_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated NIC_PF_MSIX_VEC()_CTL, enumerated by
                                                                 NIC_PF_INT_VEC_E.
                                                                 Bits that have no associated NIC_PF_INT_VEC_E are zero. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated NIC_PF_MSIX_VEC()_CTL, enumerated by
                                                                 NIC_PF_INT_VEC_E.
                                                                 Bits that have no associated NIC_PF_INT_VEC_E are zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_msix_pbax_s cn; */
};
typedef union bdk_nic_pf_msix_pbax bdk_nic_pf_msix_pbax_t;

static inline uint64_t BDK_NIC_PF_MSIX_PBAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_MSIX_PBAX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a==0))
        return 0x8430600f0000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("NIC_PF_MSIX_PBAX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_MSIX_PBAX(a) bdk_nic_pf_msix_pbax_t
#define bustype_BDK_NIC_PF_MSIX_PBAX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_MSIX_PBAX(a) "NIC_PF_MSIX_PBAX"
#define device_bar_BDK_NIC_PF_MSIX_PBAX(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_NIC_PF_MSIX_PBAX(a) (a)
#define arguments_BDK_NIC_PF_MSIX_PBAX(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_msix_vec#_addr
 *
 * NIC PF MSI-X Vector-Table Address Registers
 * This register is the MSI-X vector table, indexed by the NIC_PF_INT_VEC_E enumeration.
 */
union bdk_nic_pf_msix_vecx_addr
{
    uint64_t u;
    struct bdk_nic_pf_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's NIC_PF_MSIX_VEC()_ADDR, NIC_PF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of NIC_PF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_NIC_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's NIC_PF_MSIX_VEC()_ADDR, NIC_PF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of NIC_PF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_NIC_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_msix_vecx_addr_s cn; */
};
typedef union bdk_nic_pf_msix_vecx_addr bdk_nic_pf_msix_vecx_addr_t;

static inline uint64_t BDK_NIC_PF_MSIX_VECX_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_MSIX_VECX_ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=8))
        return 0x843060000000ll + 0x10ll * ((a) & 0xf);
    __bdk_csr_fatal("NIC_PF_MSIX_VECX_ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_MSIX_VECX_ADDR(a) bdk_nic_pf_msix_vecx_addr_t
#define bustype_BDK_NIC_PF_MSIX_VECX_ADDR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_MSIX_VECX_ADDR(a) "NIC_PF_MSIX_VECX_ADDR"
#define device_bar_BDK_NIC_PF_MSIX_VECX_ADDR(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_NIC_PF_MSIX_VECX_ADDR(a) (a)
#define arguments_BDK_NIC_PF_MSIX_VECX_ADDR(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_msix_vec#_ctl
 *
 * NIC PF MSI-X Vector-Table Control and Data Registers
 * This register is the MSI-X vector table, indexed by the NIC_PF_INT_VEC_E enumeration.
 */
union bdk_nic_pf_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_nic_pf_msix_vecx_ctl_s
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
    /* struct bdk_nic_pf_msix_vecx_ctl_s cn; */
};
typedef union bdk_nic_pf_msix_vecx_ctl bdk_nic_pf_msix_vecx_ctl_t;

static inline uint64_t BDK_NIC_PF_MSIX_VECX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_MSIX_VECX_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=8))
        return 0x843060000008ll + 0x10ll * ((a) & 0xf);
    __bdk_csr_fatal("NIC_PF_MSIX_VECX_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_MSIX_VECX_CTL(a) bdk_nic_pf_msix_vecx_ctl_t
#define bustype_BDK_NIC_PF_MSIX_VECX_CTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_MSIX_VECX_CTL(a) "NIC_PF_MSIX_VECX_CTL"
#define device_bar_BDK_NIC_PF_MSIX_VECX_CTL(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_NIC_PF_MSIX_VECX_CTL(a) (a)
#define arguments_BDK_NIC_PF_MSIX_VECX_CTL(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_pir_cfg
 *
 * NIC PIR Configuration Register
 */
union bdk_nic_pf_pir_cfg
{
    uint64_t u;
    struct bdk_nic_pf_pir_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t tick_rate             : 12; /**< [ 11:  0](R/W) Number of coprocessor clocks between replenishing TL3 shaper tokens. Zero disables the
                                                                 timer, must be nonzero if NIC transmit is to be used. The supported minimum number is 256
                                                                 for CN81XX.
                                                                 (Two entries get replenished in 1 heartbeat. It takes 256 cycles to replenish all 64 TL3
                                                                 entries.) */
#else /* Word 0 - Little Endian */
        uint64_t tick_rate             : 12; /**< [ 11:  0](R/W) Number of coprocessor clocks between replenishing TL3 shaper tokens. Zero disables the
                                                                 timer, must be nonzero if NIC transmit is to be used. The supported minimum number is 256
                                                                 for CN81XX.
                                                                 (Two entries get replenished in 1 heartbeat. It takes 256 cycles to replenish all 64 TL3
                                                                 entries.) */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_pir_cfg_s cn8; */
    /* struct bdk_nic_pf_pir_cfg_s cn81xx; */
    struct bdk_nic_pf_pir_cfg_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t tick_rate             : 12; /**< [ 11:  0](R/W) Number of coprocessor clocks between replenishing TL3 shaper tokens. Zero disables the
                                                                 timer, must be nonzero if NIC transmit is to be used. The supported minimum number is 256
                                                                 for t81.
                                                                 (Two entries get replenished in 1 heartbeat. It takes 256 cycles to replenish all 64 TL3
                                                                 entries.) */
#else /* Word 0 - Little Endian */
        uint64_t tick_rate             : 12; /**< [ 11:  0](R/W) Number of coprocessor clocks between replenishing TL3 shaper tokens. Zero disables the
                                                                 timer, must be nonzero if NIC transmit is to be used. The supported minimum number is 256
                                                                 for t81.
                                                                 (Two entries get replenished in 1 heartbeat. It takes 256 cycles to replenish all 64 TL3
                                                                 entries.) */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_pf_pir_cfg bdk_nic_pf_pir_cfg_t;

#define BDK_NIC_PF_PIR_CFG BDK_NIC_PF_PIR_CFG_FUNC()
static inline uint64_t BDK_NIC_PF_PIR_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_PIR_CFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000700000ll;
    __bdk_csr_fatal("NIC_PF_PIR_CFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_PIR_CFG bdk_nic_pf_pir_cfg_t
#define bustype_BDK_NIC_PF_PIR_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_PIR_CFG "NIC_PF_PIR_CFG"
#define device_bar_BDK_NIC_PF_PIR_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_PIR_CFG 0
#define arguments_BDK_NIC_PF_PIR_CFG -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_pkind#_cfg
 *
 * NIC Pkind Configuration Registers
 */
union bdk_nic_pf_pkindx_cfg
{
    uint64_t u;
    struct bdk_nic_pf_pkindx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dext_abs              : 1;  /**< [ 63: 63](R/W) 0 = DEXT position is relative to start of L2 (and thus is adjusted by [HDR_SL]).
                                                                 1 = DEXT position is absolute. */
        uint64_t dext_sl               : 7;  /**< [ 62: 56](R/W) Number of 2-byte words between start of packet or start of L2 (see [DEXT_ABS]). */
        uint64_t reserved_42_55        : 14;
        uint64_t hdr_sl                : 5;  /**< [ 41: 37](R/W) Header skip length. Number of 2-byte words parser should skip between the start of the
                                                                 packet and the Ethernet address. For BGX, should be 0x4 if a timestamp is present; see
                                                                 also BGX()_SMU()_RX_FRM_CTL[PTP_MODE]. */
        uint64_t reserved_34_36        : 3;
        uint64_t lenerr_en             : 1;  /**< [ 33: 33](R/W) L2 length error check enable. Check if frame was received with L2 length error, see
                                                                 NIC_ERROP_E::L2_LENMISM. */
        uint64_t reserved_32           : 1;
        uint64_t maxlen                : 16; /**< [ 31: 16](R/W) Byte count for max-sized frame check. See NIC_ERROP_E::L2_OVERSIZE. This length must
                                                                 include any timstamps or NIC_CQE_RX_S, and any VLANs which may be stripped. FCS bytes are
                                                                 not included. Set to all-ones to disable this check. */
        uint64_t minlen                : 16; /**< [ 15:  0](R/W) Byte count for min-sized frame check. See NIC_ERROP_E::L2_UNDERSIZE. Set to zero to
                                                                 disable this check. */
#else /* Word 0 - Little Endian */
        uint64_t minlen                : 16; /**< [ 15:  0](R/W) Byte count for min-sized frame check. See NIC_ERROP_E::L2_UNDERSIZE. Set to zero to
                                                                 disable this check. */
        uint64_t maxlen                : 16; /**< [ 31: 16](R/W) Byte count for max-sized frame check. See NIC_ERROP_E::L2_OVERSIZE. This length must
                                                                 include any timstamps or NIC_CQE_RX_S, and any VLANs which may be stripped. FCS bytes are
                                                                 not included. Set to all-ones to disable this check. */
        uint64_t reserved_32           : 1;
        uint64_t lenerr_en             : 1;  /**< [ 33: 33](R/W) L2 length error check enable. Check if frame was received with L2 length error, see
                                                                 NIC_ERROP_E::L2_LENMISM. */
        uint64_t reserved_34_36        : 3;
        uint64_t hdr_sl                : 5;  /**< [ 41: 37](R/W) Header skip length. Number of 2-byte words parser should skip between the start of the
                                                                 packet and the Ethernet address. For BGX, should be 0x4 if a timestamp is present; see
                                                                 also BGX()_SMU()_RX_FRM_CTL[PTP_MODE]. */
        uint64_t reserved_42_55        : 14;
        uint64_t dext_sl               : 7;  /**< [ 62: 56](R/W) Number of 2-byte words between start of packet or start of L2 (see [DEXT_ABS]). */
        uint64_t dext_abs              : 1;  /**< [ 63: 63](R/W) 0 = DEXT position is relative to start of L2 (and thus is adjusted by [HDR_SL]).
                                                                 1 = DEXT position is absolute. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_pkindx_cfg_s cn; */
};
typedef union bdk_nic_pf_pkindx_cfg bdk_nic_pf_pkindx_cfg_t;

static inline uint64_t BDK_NIC_PF_PKINDX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_PKINDX_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=15))
        return 0x843000000600ll + 8ll * ((a) & 0xf);
    __bdk_csr_fatal("NIC_PF_PKINDX_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_PKINDX_CFG(a) bdk_nic_pf_pkindx_cfg_t
#define bustype_BDK_NIC_PF_PKINDX_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_PKINDX_CFG(a) "NIC_PF_PKINDX_CFG"
#define device_bar_BDK_NIC_PF_PKINDX_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_PKINDX_CFG(a) (a)
#define arguments_BDK_NIC_PF_PKINDX_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_qs#_cfg
 *
 * NIC Queue Set-Configuration Registers
 */
union bdk_nic_pf_qsx_cfg
{
    uint64_t u;
    struct bdk_nic_pf_qsx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t ena                   : 1;  /**< [ 31: 31](R/W) Enable QS. */
        uint64_t reserved_27_30        : 4;
        uint64_t sq_ins_ena            : 1;  /**< [ 26: 26](R/W) SQ data insertion enable. When set, insert NIC_PF_QS()_SQ()_CFG[SQ_INS_DATA]
                                                                 into transmitted packets. */
        uint64_t sq_ins_pos            : 6;  /**< [ 25: 20](R/W) SQ data insertion position. When [SQ_INS_ENA] is set, the byte number in the transmitted
                                                                 packet at which to insert the least significant byte of
                                                                 NIC_PF_QS()_SQ()_CFG[SQ_INS_DATA]. Bytes are numbered in little endian form,
                                                                 with byte 0 the first byte onto the wire. */
        uint64_t lock_ena              : 1;  /**< [ 19: 19](R/W) Lockdown enable. When set, the NIC_PF_QS()_LOCK() registers can be used to lock
                                                                 down one of more bytes in packets transmitted by the QS. */
        uint64_t lock_viol_cqe_ena     : 1;  /**< [ 18: 18](R/W) Enable generation of NIC_CQE_SEND_S[SEND_STATUS] = NIC_CQE_SEND_STATUS_E::LOCK_VIOL. */
        uint64_t send_tstmp_ena        : 1;  /**< [ 17: 17](R/W) Send timestamp enable. When set, the QS is allowed to send packets with NIC_SEND_HDR_S[TSTMP]=1. */
        uint64_t be                    : 1;  /**< [ 16: 16](R/W) Big-endian mode. Specifies big-endian for data structures in L2C/DRAM that are accessed by
                                                                 the QS.

                                                                 When set, all data structures are in byte invariant big-endian format (BE8) with the
                                                                 following ordering within each 64-bit word: \<63:56\> at byte address 0, \<55:48\> at address
                                                                 1, ..., \<7:0\> at address 0x7.

                                                                 When clear, all data structures are in byte invariant little-endian format (LE8) with the
                                                                 following ordering within each 64-bit word: \<7:0\> at byte address 0, \<15:8\> at address 1,
                                                                 ..., \<63:56\> at address 0x7.

                                                                 The affected data structures are:
                                                                 * Receive buffer descriptor: NIC_RBDR_ENTRY_S.
                                                                 * All send subdescriptors: NIC_SEND_*_S.
                                                                 * All CQ entries, i.e. all structures starting with  NIC_CQE_RX_S and NIC_CQE_SEND_S,
                                                                 excluding any packet data embedded in these structures.
                                                                 Note that this bit does not affect the byte ordering of packet data, which is treated as a
                                                                 byte stream transmitted by incrementing byte address. The same byte ordering is also used
                                                                 for packet data that may be embedded in CQ entries that start with NIC_CQE_RX_S, or
                                                                 immediate data in or following NIC_SEND_IMM_S. */
        uint64_t reserved_5_15         : 11;
        uint64_t vnic                  : 5;  /**< [  4:  0](R/W) VNIC to which this QS is assigned. If this QS is a VNIC, then must be set to the QS number. */
#else /* Word 0 - Little Endian */
        uint64_t vnic                  : 5;  /**< [  4:  0](R/W) VNIC to which this QS is assigned. If this QS is a VNIC, then must be set to the QS number. */
        uint64_t reserved_5_15         : 11;
        uint64_t be                    : 1;  /**< [ 16: 16](R/W) Big-endian mode. Specifies big-endian for data structures in L2C/DRAM that are accessed by
                                                                 the QS.

                                                                 When set, all data structures are in byte invariant big-endian format (BE8) with the
                                                                 following ordering within each 64-bit word: \<63:56\> at byte address 0, \<55:48\> at address
                                                                 1, ..., \<7:0\> at address 0x7.

                                                                 When clear, all data structures are in byte invariant little-endian format (LE8) with the
                                                                 following ordering within each 64-bit word: \<7:0\> at byte address 0, \<15:8\> at address 1,
                                                                 ..., \<63:56\> at address 0x7.

                                                                 The affected data structures are:
                                                                 * Receive buffer descriptor: NIC_RBDR_ENTRY_S.
                                                                 * All send subdescriptors: NIC_SEND_*_S.
                                                                 * All CQ entries, i.e. all structures starting with  NIC_CQE_RX_S and NIC_CQE_SEND_S,
                                                                 excluding any packet data embedded in these structures.
                                                                 Note that this bit does not affect the byte ordering of packet data, which is treated as a
                                                                 byte stream transmitted by incrementing byte address. The same byte ordering is also used
                                                                 for packet data that may be embedded in CQ entries that start with NIC_CQE_RX_S, or
                                                                 immediate data in or following NIC_SEND_IMM_S. */
        uint64_t send_tstmp_ena        : 1;  /**< [ 17: 17](R/W) Send timestamp enable. When set, the QS is allowed to send packets with NIC_SEND_HDR_S[TSTMP]=1. */
        uint64_t lock_viol_cqe_ena     : 1;  /**< [ 18: 18](R/W) Enable generation of NIC_CQE_SEND_S[SEND_STATUS] = NIC_CQE_SEND_STATUS_E::LOCK_VIOL. */
        uint64_t lock_ena              : 1;  /**< [ 19: 19](R/W) Lockdown enable. When set, the NIC_PF_QS()_LOCK() registers can be used to lock
                                                                 down one of more bytes in packets transmitted by the QS. */
        uint64_t sq_ins_pos            : 6;  /**< [ 25: 20](R/W) SQ data insertion position. When [SQ_INS_ENA] is set, the byte number in the transmitted
                                                                 packet at which to insert the least significant byte of
                                                                 NIC_PF_QS()_SQ()_CFG[SQ_INS_DATA]. Bytes are numbered in little endian form,
                                                                 with byte 0 the first byte onto the wire. */
        uint64_t sq_ins_ena            : 1;  /**< [ 26: 26](R/W) SQ data insertion enable. When set, insert NIC_PF_QS()_SQ()_CFG[SQ_INS_DATA]
                                                                 into transmitted packets. */
        uint64_t reserved_27_30        : 4;
        uint64_t ena                   : 1;  /**< [ 31: 31](R/W) Enable QS. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_qsx_cfg_s cn8; */
    struct bdk_nic_pf_qsx_cfg_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t ena                   : 1;  /**< [ 31: 31](R/W) Enable QS. */
        uint64_t reserved_27_30        : 4;
        uint64_t sq_ins_ena            : 1;  /**< [ 26: 26](R/W) SQ data insertion enable. When set, insert NIC_PF_QS()_SQ()_CFG[SQ_INS_DATA]
                                                                 into transmitted packets. */
        uint64_t sq_ins_pos            : 6;  /**< [ 25: 20](R/W) SQ data insertion position. When [SQ_INS_ENA] is set, the byte number in the transmitted
                                                                 packet at which to insert the least significant byte of
                                                                 NIC_PF_QS()_SQ()_CFG[SQ_INS_DATA]. Bytes are numbered in little endian form,
                                                                 with byte 0 the first byte onto the wire. */
        uint64_t lock_ena              : 1;  /**< [ 19: 19](R/W) Lockdown enable. When set, the NIC_PF_QS()_LOCK() registers can be used to lock
                                                                 down one of more bytes in packets transmitted by the QS. */
        uint64_t lock_viol_cqe_ena     : 1;  /**< [ 18: 18](R/W) Enable generation of NIC_CQE_SEND_S[SEND_STATUS] = NIC_CQE_SEND_STATUS_E::LOCK_VIOL. */
        uint64_t send_tstmp_ena        : 1;  /**< [ 17: 17](R/W) Send timestamp enable. When set, the QS is allowed to send packets with NIC_SEND_HDR_S[TSTMP]=1. */
        uint64_t be                    : 1;  /**< [ 16: 16](R/W) Big-endian mode. Specifies big-endian for data structures in L2C/DRAM that are accessed by
                                                                 the QS.

                                                                 When set, all data structures are in byte invariant big-endian format (BE8) with the
                                                                 following ordering within each 64-bit word: \<63:56\> at byte address 0, \<55:48\> at address
                                                                 1, ..., \<7:0\> at address 0x7.

                                                                 When clear, all data structures are in byte invariant little-endian format (LE8) with the
                                                                 following ordering within each 64-bit word: \<7:0\> at byte address 0, \<15:8\> at address 1,
                                                                 ..., \<63:56\> at address 0x7.

                                                                 The affected data structures are:
                                                                 * Receive buffer descriptor: NIC_RBDR_ENTRY_S.
                                                                 * All send subdescriptors: NIC_SEND_*_S.
                                                                 * All CQ entries, i.e. all structures starting with  NIC_CQE_RX_S and NIC_CQE_SEND_S,
                                                                 excluding any packet data embedded in these structures.
                                                                 Note that this bit does not affect the byte ordering of packet data, which is treated as a
                                                                 byte stream transmitted by incrementing byte address. The same byte ordering is also used
                                                                 for packet data that may be embedded in CQ entries that start with NIC_CQE_RX_S, or
                                                                 immediate data in or following NIC_SEND_IMM_S. */
        uint64_t reserved_7_15         : 9;
        uint64_t reserved_3_6          : 4;
        uint64_t vnic                  : 3;  /**< [  2:  0](R/W) VNIC to which this QS is assigned. If this QS is a VNIC, then must be set to the QS number. */
#else /* Word 0 - Little Endian */
        uint64_t vnic                  : 3;  /**< [  2:  0](R/W) VNIC to which this QS is assigned. If this QS is a VNIC, then must be set to the QS number. */
        uint64_t reserved_3_6          : 4;
        uint64_t reserved_7_15         : 9;
        uint64_t be                    : 1;  /**< [ 16: 16](R/W) Big-endian mode. Specifies big-endian for data structures in L2C/DRAM that are accessed by
                                                                 the QS.

                                                                 When set, all data structures are in byte invariant big-endian format (BE8) with the
                                                                 following ordering within each 64-bit word: \<63:56\> at byte address 0, \<55:48\> at address
                                                                 1, ..., \<7:0\> at address 0x7.

                                                                 When clear, all data structures are in byte invariant little-endian format (LE8) with the
                                                                 following ordering within each 64-bit word: \<7:0\> at byte address 0, \<15:8\> at address 1,
                                                                 ..., \<63:56\> at address 0x7.

                                                                 The affected data structures are:
                                                                 * Receive buffer descriptor: NIC_RBDR_ENTRY_S.
                                                                 * All send subdescriptors: NIC_SEND_*_S.
                                                                 * All CQ entries, i.e. all structures starting with  NIC_CQE_RX_S and NIC_CQE_SEND_S,
                                                                 excluding any packet data embedded in these structures.
                                                                 Note that this bit does not affect the byte ordering of packet data, which is treated as a
                                                                 byte stream transmitted by incrementing byte address. The same byte ordering is also used
                                                                 for packet data that may be embedded in CQ entries that start with NIC_CQE_RX_S, or
                                                                 immediate data in or following NIC_SEND_IMM_S. */
        uint64_t send_tstmp_ena        : 1;  /**< [ 17: 17](R/W) Send timestamp enable. When set, the QS is allowed to send packets with NIC_SEND_HDR_S[TSTMP]=1. */
        uint64_t lock_viol_cqe_ena     : 1;  /**< [ 18: 18](R/W) Enable generation of NIC_CQE_SEND_S[SEND_STATUS] = NIC_CQE_SEND_STATUS_E::LOCK_VIOL. */
        uint64_t lock_ena              : 1;  /**< [ 19: 19](R/W) Lockdown enable. When set, the NIC_PF_QS()_LOCK() registers can be used to lock
                                                                 down one of more bytes in packets transmitted by the QS. */
        uint64_t sq_ins_pos            : 6;  /**< [ 25: 20](R/W) SQ data insertion position. When [SQ_INS_ENA] is set, the byte number in the transmitted
                                                                 packet at which to insert the least significant byte of
                                                                 NIC_PF_QS()_SQ()_CFG[SQ_INS_DATA]. Bytes are numbered in little endian form,
                                                                 with byte 0 the first byte onto the wire. */
        uint64_t sq_ins_ena            : 1;  /**< [ 26: 26](R/W) SQ data insertion enable. When set, insert NIC_PF_QS()_SQ()_CFG[SQ_INS_DATA]
                                                                 into transmitted packets. */
        uint64_t reserved_27_30        : 4;
        uint64_t ena                   : 1;  /**< [ 31: 31](R/W) Enable QS. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn81xx;
    struct bdk_nic_pf_qsx_cfg_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t ena                   : 1;  /**< [ 31: 31](R/W) Enable QS. */
        uint64_t reserved_27_30        : 4;
        uint64_t sq_ins_ena            : 1;  /**< [ 26: 26](R/W) SQ data insertion enable. When set, insert NIC_PF_QS()_SQ()_CFG[SQ_INS_DATA]
                                                                 into transmitted packets. */
        uint64_t sq_ins_pos            : 6;  /**< [ 25: 20](R/W) SQ data insertion position. When [SQ_INS_ENA] is set, the byte number in the transmitted
                                                                 packet at which to insert the least significant byte of
                                                                 NIC_PF_QS()_SQ()_CFG[SQ_INS_DATA]. Bytes are numbered in little endian form,
                                                                 with byte 0 the first byte onto the wire. */
        uint64_t lock_ena              : 1;  /**< [ 19: 19](R/W) Lockdown enable. When set, the NIC_PF_QS()_LOCK() registers can be used to lock
                                                                 down one of more bytes in packets transmitted by the QS. */
        uint64_t lock_viol_cqe_ena     : 1;  /**< [ 18: 18](R/W) Enable generation of NIC_CQE_SEND_S[SEND_STATUS] = NIC_CQE_SEND_STATUS_E::LOCK_VIOL. */
        uint64_t send_tstmp_ena        : 1;  /**< [ 17: 17](R/W) Send timestamp enable. When set, the QS is allowed to send packets with NIC_SEND_HDR_S[TSTMP]=1. */
        uint64_t be                    : 1;  /**< [ 16: 16](R/W) Big-endian mode. Specifies big-endian for data structures in L2C/DRAM that are accessed by
                                                                 the QS.

                                                                 When set, all data structures are in byte invariant big-endian format (BE8) with the
                                                                 following ordering within each 64-bit word: \<63:56\> at byte address 0, \<55:48\> at address
                                                                 1, ..., \<7:0\> at address 0x7.

                                                                 When clear, all data structures are in byte invariant little-endian format (LE8) with the
                                                                 following ordering within each 64-bit word: \<7:0\> at byte address 0, \<15:8\> at address 1,
                                                                 ..., \<63:56\> at address 0x7.

                                                                 The affected data structures are:
                                                                 * Receive buffer descriptor: NIC_RBDR_ENTRY_S.
                                                                 * All send subdescriptors: NIC_SEND_*_S.
                                                                 * All CQ entries, i.e. all structures starting with  NIC_CQE_RX_S and NIC_CQE_SEND_S,
                                                                 excluding any packet data embedded in these structures.
                                                                 Note that this bit does not affect the byte ordering of packet data, which is treated as a
                                                                 byte stream transmitted by incrementing byte address. The same byte ordering is also used
                                                                 for packet data that may be embedded in CQ entries that start with NIC_CQE_RX_S, or
                                                                 immediate data in or following NIC_SEND_IMM_S. */
        uint64_t reserved_7_15         : 9;
        uint64_t reserved_5_6          : 2;
        uint64_t vnic                  : 5;  /**< [  4:  0](R/W) VNIC to which this QS is assigned. If this QS is a VNIC, then must be set to the QS number. */
#else /* Word 0 - Little Endian */
        uint64_t vnic                  : 5;  /**< [  4:  0](R/W) VNIC to which this QS is assigned. If this QS is a VNIC, then must be set to the QS number. */
        uint64_t reserved_5_6          : 2;
        uint64_t reserved_7_15         : 9;
        uint64_t be                    : 1;  /**< [ 16: 16](R/W) Big-endian mode. Specifies big-endian for data structures in L2C/DRAM that are accessed by
                                                                 the QS.

                                                                 When set, all data structures are in byte invariant big-endian format (BE8) with the
                                                                 following ordering within each 64-bit word: \<63:56\> at byte address 0, \<55:48\> at address
                                                                 1, ..., \<7:0\> at address 0x7.

                                                                 When clear, all data structures are in byte invariant little-endian format (LE8) with the
                                                                 following ordering within each 64-bit word: \<7:0\> at byte address 0, \<15:8\> at address 1,
                                                                 ..., \<63:56\> at address 0x7.

                                                                 The affected data structures are:
                                                                 * Receive buffer descriptor: NIC_RBDR_ENTRY_S.
                                                                 * All send subdescriptors: NIC_SEND_*_S.
                                                                 * All CQ entries, i.e. all structures starting with  NIC_CQE_RX_S and NIC_CQE_SEND_S,
                                                                 excluding any packet data embedded in these structures.
                                                                 Note that this bit does not affect the byte ordering of packet data, which is treated as a
                                                                 byte stream transmitted by incrementing byte address. The same byte ordering is also used
                                                                 for packet data that may be embedded in CQ entries that start with NIC_CQE_RX_S, or
                                                                 immediate data in or following NIC_SEND_IMM_S. */
        uint64_t send_tstmp_ena        : 1;  /**< [ 17: 17](R/W) Send timestamp enable. When set, the QS is allowed to send packets with NIC_SEND_HDR_S[TSTMP]=1. */
        uint64_t lock_viol_cqe_ena     : 1;  /**< [ 18: 18](R/W) Enable generation of NIC_CQE_SEND_S[SEND_STATUS] = NIC_CQE_SEND_STATUS_E::LOCK_VIOL. */
        uint64_t lock_ena              : 1;  /**< [ 19: 19](R/W) Lockdown enable. When set, the NIC_PF_QS()_LOCK() registers can be used to lock
                                                                 down one of more bytes in packets transmitted by the QS. */
        uint64_t sq_ins_pos            : 6;  /**< [ 25: 20](R/W) SQ data insertion position. When [SQ_INS_ENA] is set, the byte number in the transmitted
                                                                 packet at which to insert the least significant byte of
                                                                 NIC_PF_QS()_SQ()_CFG[SQ_INS_DATA]. Bytes are numbered in little endian form,
                                                                 with byte 0 the first byte onto the wire. */
        uint64_t sq_ins_ena            : 1;  /**< [ 26: 26](R/W) SQ data insertion enable. When set, insert NIC_PF_QS()_SQ()_CFG[SQ_INS_DATA]
                                                                 into transmitted packets. */
        uint64_t reserved_27_30        : 4;
        uint64_t ena                   : 1;  /**< [ 31: 31](R/W) Enable QS. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_pf_qsx_cfg bdk_nic_pf_qsx_cfg_t;

static inline uint64_t BDK_NIC_PF_QSX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_QSX_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=7))
        return 0x843020010000ll + 0x200000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x843020010000ll + 0x200000ll * ((a) & 0x1f);
    __bdk_csr_fatal("NIC_PF_QSX_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_QSX_CFG(a) bdk_nic_pf_qsx_cfg_t
#define bustype_BDK_NIC_PF_QSX_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_QSX_CFG(a) "NIC_PF_QSX_CFG"
#define device_bar_BDK_NIC_PF_QSX_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_QSX_CFG(a) (a)
#define arguments_BDK_NIC_PF_QSX_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_qs#_lock#
 *
 * NIC PF VNIC Lockdown Registers
 */
union bdk_nic_pf_qsx_lockx
{
    uint64_t u;
    struct bdk_nic_pf_qsx_lockx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t bit_ena               : 32; /**< [ 63: 32](R/W) Lockdown bit enable. Each set bit indicates that the transmitted packet's corresponding
                                                                 bit number will be compared against [DATA]. */
        uint64_t data                  : 32; /**< [ 31:  0](R/W) Lockdown data. If corresponding [BIT_ENA] is set and NIC_PF_QS()_CFG[LOCK_ENA] is
                                                                 set, outbound packet data must match the [DATA] bit or the packet will be dropped. Bytes
                                                                 are numbered in little endian form, with byte 0 the first byte onto the wire:
                                                                 _ If LOCK(0)[BIT_ENA]\<7:0\> set, LOCK(0)[DATA]\<7:0\> = packet byte 0.
                                                                 _ If LOCK(0)[BIT_ENA]\<15:8\> set, LOCK(0)[DATA]\<15:8\> = packet byte 1.
                                                                 _ If LOCK(0)[BIT_ENA]\<23:6\> set, LOCK(0)[DATA]\<23:16\> = packet byte 2.
                                                                 _ ...
                                                                 _ If LOCK(1)[BIT_ENA]\<7:0\> set, LOCK(1)[DATA]\<7:0\> = packet byte 4.
                                                                 _ ...
                                                                 _ If LOCK(23)[BIT_ENA]\<31:24\> set, LOCK(23)[DATA]\<31:24\> = packet byte 95. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 32; /**< [ 31:  0](R/W) Lockdown data. If corresponding [BIT_ENA] is set and NIC_PF_QS()_CFG[LOCK_ENA] is
                                                                 set, outbound packet data must match the [DATA] bit or the packet will be dropped. Bytes
                                                                 are numbered in little endian form, with byte 0 the first byte onto the wire:
                                                                 _ If LOCK(0)[BIT_ENA]\<7:0\> set, LOCK(0)[DATA]\<7:0\> = packet byte 0.
                                                                 _ If LOCK(0)[BIT_ENA]\<15:8\> set, LOCK(0)[DATA]\<15:8\> = packet byte 1.
                                                                 _ If LOCK(0)[BIT_ENA]\<23:6\> set, LOCK(0)[DATA]\<23:16\> = packet byte 2.
                                                                 _ ...
                                                                 _ If LOCK(1)[BIT_ENA]\<7:0\> set, LOCK(1)[DATA]\<7:0\> = packet byte 4.
                                                                 _ ...
                                                                 _ If LOCK(23)[BIT_ENA]\<31:24\> set, LOCK(23)[DATA]\<31:24\> = packet byte 95. */
        uint64_t bit_ena               : 32; /**< [ 63: 32](R/W) Lockdown bit enable. Each set bit indicates that the transmitted packet's corresponding
                                                                 bit number will be compared against [DATA]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_qsx_lockx_s cn; */
};
typedef union bdk_nic_pf_qsx_lockx bdk_nic_pf_qsx_lockx_t;

static inline uint64_t BDK_NIC_PF_QSX_LOCKX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_QSX_LOCKX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=23)))
        return 0x843020006000ll + 0x200000ll * ((a) & 0x7) + 8ll * ((b) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=23)))
        return 0x843020006000ll + 0x200000ll * ((a) & 0x1f) + 8ll * ((b) & 0x1f);
    __bdk_csr_fatal("NIC_PF_QSX_LOCKX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_QSX_LOCKX(a,b) bdk_nic_pf_qsx_lockx_t
#define bustype_BDK_NIC_PF_QSX_LOCKX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_QSX_LOCKX(a,b) "NIC_PF_QSX_LOCKX"
#define device_bar_BDK_NIC_PF_QSX_LOCKX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_QSX_LOCKX(a,b) (a)
#define arguments_BDK_NIC_PF_QSX_LOCKX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_pf_qs#_rq#_bp_cfg
 *
 * NIC Receive-Queue Backpressure Configuration Registers
 */
union bdk_nic_pf_qsx_rqx_bp_cfg
{
    uint64_t u;
    struct bdk_nic_pf_qsx_rqx_bp_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t rbdr_bp_ena           : 1;  /**< [ 63: 63](R/W) Enables BP based off the RBDR levels of the Start and Continue Rings. */
        uint64_t cq_bp_ena             : 1;  /**< [ 62: 62](R/W) Enables BP based off the CQ level. */
        uint64_t reserved_24_61        : 38;
        uint64_t rbdr_bp               : 8;  /**< [ 23: 16](R/W) Threshold level for backpressuring channel, in units of 1/256th of RBDR level. */
        uint64_t cq_bp                 : 8;  /**< [ 15:  8](R/W) Threshold level for backpressuring channel, in units of 1/256th of CQ level. */
        uint64_t bpid                  : 8;  /**< [  7:  0](R/W) BPID used for RX channel backpressure. */
#else /* Word 0 - Little Endian */
        uint64_t bpid                  : 8;  /**< [  7:  0](R/W) BPID used for RX channel backpressure. */
        uint64_t cq_bp                 : 8;  /**< [ 15:  8](R/W) Threshold level for backpressuring channel, in units of 1/256th of CQ level. */
        uint64_t rbdr_bp               : 8;  /**< [ 23: 16](R/W) Threshold level for backpressuring channel, in units of 1/256th of RBDR level. */
        uint64_t reserved_24_61        : 38;
        uint64_t cq_bp_ena             : 1;  /**< [ 62: 62](R/W) Enables BP based off the CQ level. */
        uint64_t rbdr_bp_ena           : 1;  /**< [ 63: 63](R/W) Enables BP based off the RBDR levels of the Start and Continue Rings. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_qsx_rqx_bp_cfg_s cn8; */
    struct bdk_nic_pf_qsx_rqx_bp_cfg_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t rbdr_bp_ena           : 1;  /**< [ 63: 63](R/W) Enables BP based off the RBDR levels of the Start and Continue Rings. */
        uint64_t cq_bp_ena             : 1;  /**< [ 62: 62](R/W) Enables BP based off the CQ level. */
        uint64_t reserved_24_61        : 38;
        uint64_t rbdr_bp               : 8;  /**< [ 23: 16](R/W) Threshold level for backpressuring channel, in units of 1/256th of RBDR level. */
        uint64_t cq_bp                 : 8;  /**< [ 15:  8](R/W) Threshold level for backpressuring channel, in units of 1/256th of CQ level. */
        uint64_t reserved_7            : 1;
        uint64_t bpid                  : 7;  /**< [  6:  0](R/W) BPID used for RX channel backpressure. */
#else /* Word 0 - Little Endian */
        uint64_t bpid                  : 7;  /**< [  6:  0](R/W) BPID used for RX channel backpressure. */
        uint64_t reserved_7            : 1;
        uint64_t cq_bp                 : 8;  /**< [ 15:  8](R/W) Threshold level for backpressuring channel, in units of 1/256th of CQ level. */
        uint64_t rbdr_bp               : 8;  /**< [ 23: 16](R/W) Threshold level for backpressuring channel, in units of 1/256th of RBDR level. */
        uint64_t reserved_24_61        : 38;
        uint64_t cq_bp_ena             : 1;  /**< [ 62: 62](R/W) Enables BP based off the CQ level. */
        uint64_t rbdr_bp_ena           : 1;  /**< [ 63: 63](R/W) Enables BP based off the RBDR levels of the Start and Continue Rings. */
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_nic_pf_qsx_rqx_bp_cfg_s cn83xx; */
};
typedef union bdk_nic_pf_qsx_rqx_bp_cfg bdk_nic_pf_qsx_rqx_bp_cfg_t;

static inline uint64_t BDK_NIC_PF_QSX_RQX_BP_CFG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_QSX_RQX_BP_CFG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x843020010500ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x843020010500ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_PF_QSX_RQX_BP_CFG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_QSX_RQX_BP_CFG(a,b) bdk_nic_pf_qsx_rqx_bp_cfg_t
#define bustype_BDK_NIC_PF_QSX_RQX_BP_CFG(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_QSX_RQX_BP_CFG(a,b) "NIC_PF_QSX_RQX_BP_CFG"
#define device_bar_BDK_NIC_PF_QSX_RQX_BP_CFG(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_QSX_RQX_BP_CFG(a,b) (a)
#define arguments_BDK_NIC_PF_QSX_RQX_BP_CFG(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_pf_qs#_rq#_cfg
 *
 * NIC Receive Queue Configuration Registers
 * Used by the PF to map shared resources to a Receive Queue.
 */
union bdk_nic_pf_qsx_rqx_cfg
{
    uint64_t u;
    struct bdk_nic_pf_qsx_rqx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t tcp_off               : 1;  /**< [ 63: 63](R/W) Reserved.
                                                                 Internal:
                                                                 Reserved for future use - Overrides NIC_QS()_RQ()_CFG[TCP_ENA]. */
        uint64_t reserved_29_62        : 34;
        uint64_t strip_pre_l2          : 1;  /**< [ 28: 28](R/W) All bytes that come before the SA/DA of the L2 Layer are stripped not saved in the RBDR buffer. */
        uint64_t caching               : 2;  /**< [ 27: 26](R/W) Select the style of write to the L2C.
                                                                 0x0 = Writes of RBDR data will not allocate into the L2C.
                                                                 0x1 = All writes of RBDR data are allocated into the L2C.
                                                                 0x2 = First aligned cache block is allocated into the L2C. All remaining cache
                                                                 blocks are not allocated.
                                                                 0x3 = First two aligned cache blocks are allocated into the L2C. All remaining
                                                                 cache blocks are not allocated. */
        uint64_t reserved_24_25        : 2;
        uint64_t cq_qs                 : 5;  /**< [ 23: 19](R/W) CQ's QS for this RQ. The CQ's QS must be assigned to the same VNIC as the RQ's QS. */
        uint64_t cq_idx                : 3;  /**< [ 18: 16](R/W) CQ within [CQ_QS] for this RQ. */
        uint64_t reserved_14_15        : 2;
        uint64_t rbdr_cont_qs          : 5;  /**< [ 13:  9](R/W) QS portion of RBDR to use for continue buffers. */
        uint64_t rbdr_cont_idx         : 1;  /**< [  8:  8](R/W) Index within QS of RBDR to use for continue buffers. */
        uint64_t reserved_6_7          : 2;
        uint64_t rbdr_strt_qs          : 5;  /**< [  5:  1](R/W) QS portion of RBDR to use used for first buffer. */
        uint64_t rbdr_strt_idx         : 1;  /**< [  0:  0](R/W) Index within OQ of RBDR to use for first buffer. */
#else /* Word 0 - Little Endian */
        uint64_t rbdr_strt_idx         : 1;  /**< [  0:  0](R/W) Index within OQ of RBDR to use for first buffer. */
        uint64_t rbdr_strt_qs          : 5;  /**< [  5:  1](R/W) QS portion of RBDR to use used for first buffer. */
        uint64_t reserved_6_7          : 2;
        uint64_t rbdr_cont_idx         : 1;  /**< [  8:  8](R/W) Index within QS of RBDR to use for continue buffers. */
        uint64_t rbdr_cont_qs          : 5;  /**< [ 13:  9](R/W) QS portion of RBDR to use for continue buffers. */
        uint64_t reserved_14_15        : 2;
        uint64_t cq_idx                : 3;  /**< [ 18: 16](R/W) CQ within [CQ_QS] for this RQ. */
        uint64_t cq_qs                 : 5;  /**< [ 23: 19](R/W) CQ's QS for this RQ. The CQ's QS must be assigned to the same VNIC as the RQ's QS. */
        uint64_t reserved_24_25        : 2;
        uint64_t caching               : 2;  /**< [ 27: 26](R/W) Select the style of write to the L2C.
                                                                 0x0 = Writes of RBDR data will not allocate into the L2C.
                                                                 0x1 = All writes of RBDR data are allocated into the L2C.
                                                                 0x2 = First aligned cache block is allocated into the L2C. All remaining cache
                                                                 blocks are not allocated.
                                                                 0x3 = First two aligned cache blocks are allocated into the L2C. All remaining
                                                                 cache blocks are not allocated. */
        uint64_t strip_pre_l2          : 1;  /**< [ 28: 28](R/W) All bytes that come before the SA/DA of the L2 Layer are stripped not saved in the RBDR buffer. */
        uint64_t reserved_29_62        : 34;
        uint64_t tcp_off               : 1;  /**< [ 63: 63](R/W) Reserved.
                                                                 Internal:
                                                                 Reserved for future use - Overrides NIC_QS()_RQ()_CFG[TCP_ENA]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_qsx_rqx_cfg_s cn8; */
    struct bdk_nic_pf_qsx_rqx_cfg_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t tcp_off               : 1;  /**< [ 63: 63](R/W) Reserved.
                                                                 Internal:
                                                                 Reserved for future use - Overrides NIC_QS()_RQ()_CFG[TCP_ENA]. */
        uint64_t reserved_29_62        : 34;
        uint64_t strip_pre_l2          : 1;  /**< [ 28: 28](R/W) All bytes that come before the SA/DA of the L2 Layer are stripped not saved in the RBDR buffer. */
        uint64_t caching               : 2;  /**< [ 27: 26](R/W) Select the style of write to the L2C.
                                                                 0x0 = Writes of RBDR data will not allocate into the L2C.
                                                                 0x1 = All writes of RBDR data are allocated into the L2C.
                                                                 0x2 = First aligned cache block is allocated into the L2C. All remaining cache
                                                                 blocks are not allocated.
                                                                 0x3 = First two aligned cache blocks are allocated into the L2C. All remaining
                                                                 cache blocks are not allocated. */
        uint64_t reserved_22_25        : 4;
        uint64_t cq_qs                 : 3;  /**< [ 21: 19](R/W) CQ's QS for this RQ. The CQ's QS must be assigned to the same VNIC as the RQ's QS. */
        uint64_t cq_idx                : 3;  /**< [ 18: 16](R/W) CQ within [CQ_QS] for this RQ. */
        uint64_t reserved_12_15        : 4;
        uint64_t rbdr_cont_qs          : 3;  /**< [ 11:  9](R/W) QS portion of RBDR to use for continue buffers. */
        uint64_t rbdr_cont_idx         : 1;  /**< [  8:  8](R/W) Index within QS of RBDR to use for continue buffers. */
        uint64_t reserved_4_7          : 4;
        uint64_t rbdr_strt_qs          : 3;  /**< [  3:  1](R/W) QS portion of RBDR to use used for first buffer. */
        uint64_t rbdr_strt_idx         : 1;  /**< [  0:  0](R/W) Index within OQ of RBDR to use for first buffer. */
#else /* Word 0 - Little Endian */
        uint64_t rbdr_strt_idx         : 1;  /**< [  0:  0](R/W) Index within OQ of RBDR to use for first buffer. */
        uint64_t rbdr_strt_qs          : 3;  /**< [  3:  1](R/W) QS portion of RBDR to use used for first buffer. */
        uint64_t reserved_4_7          : 4;
        uint64_t rbdr_cont_idx         : 1;  /**< [  8:  8](R/W) Index within QS of RBDR to use for continue buffers. */
        uint64_t rbdr_cont_qs          : 3;  /**< [ 11:  9](R/W) QS portion of RBDR to use for continue buffers. */
        uint64_t reserved_12_15        : 4;
        uint64_t cq_idx                : 3;  /**< [ 18: 16](R/W) CQ within [CQ_QS] for this RQ. */
        uint64_t cq_qs                 : 3;  /**< [ 21: 19](R/W) CQ's QS for this RQ. The CQ's QS must be assigned to the same VNIC as the RQ's QS. */
        uint64_t reserved_22_25        : 4;
        uint64_t caching               : 2;  /**< [ 27: 26](R/W) Select the style of write to the L2C.
                                                                 0x0 = Writes of RBDR data will not allocate into the L2C.
                                                                 0x1 = All writes of RBDR data are allocated into the L2C.
                                                                 0x2 = First aligned cache block is allocated into the L2C. All remaining cache
                                                                 blocks are not allocated.
                                                                 0x3 = First two aligned cache blocks are allocated into the L2C. All remaining
                                                                 cache blocks are not allocated. */
        uint64_t strip_pre_l2          : 1;  /**< [ 28: 28](R/W) All bytes that come before the SA/DA of the L2 Layer are stripped not saved in the RBDR buffer. */
        uint64_t reserved_29_62        : 34;
        uint64_t tcp_off               : 1;  /**< [ 63: 63](R/W) Reserved.
                                                                 Internal:
                                                                 Reserved for future use - Overrides NIC_QS()_RQ()_CFG[TCP_ENA]. */
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_nic_pf_qsx_rqx_cfg_s cn83xx; */
};
typedef union bdk_nic_pf_qsx_rqx_cfg bdk_nic_pf_qsx_rqx_cfg_t;

static inline uint64_t BDK_NIC_PF_QSX_RQX_CFG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_QSX_RQX_CFG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x843020010400ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x843020010400ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_PF_QSX_RQX_CFG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_QSX_RQX_CFG(a,b) bdk_nic_pf_qsx_rqx_cfg_t
#define bustype_BDK_NIC_PF_QSX_RQX_CFG(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_QSX_RQX_CFG(a,b) "NIC_PF_QSX_RQX_CFG"
#define device_bar_BDK_NIC_PF_QSX_RQX_CFG(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_QSX_RQX_CFG(a,b) (a)
#define arguments_BDK_NIC_PF_QSX_RQX_CFG(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_pf_qs#_rq#_drop_cfg
 *
 * NIC Receive-Queue Drop Configuration Registers
 */
union bdk_nic_pf_qsx_rqx_drop_cfg
{
    uint64_t u;
    struct bdk_nic_pf_qsx_rqx_drop_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t rbdr_red              : 1;  /**< [ 63: 63](R/W) Enable RBDR RED drop between PASS and DROP levels. */
        uint64_t cq_red                : 1;  /**< [ 62: 62](R/W) Enable CQ RED drop between PASS and DROP levels. */
        uint64_t reserved_48_61        : 14;
        uint64_t rbdr_pass             : 8;  /**< [ 47: 40](R/W) Threshold level for RED accepting packets, in units of 1/256th of RBDR level.
                                                                 0xff represents a full RBDR, 0x0 represents an empty RBDR.
                                                                 If the RBDR level is greater \>= to this value then the packet is received.
                                                                 If the RBDR level is less that this value but \>= [RBDR_DROP] value then the packet is in
                                                                 the RED zone
                                                                 If the RBDR level is \< [RBDR_DROP], then the packet is dropped. */
        uint64_t rbdr_drop             : 8;  /**< [ 39: 32](R/W) Threshold level for RED dropping packets, in units of 1/256th of RBDR level. See
                                                                 [RBDR_PASS]
                                                                 for more details. */
        uint64_t reserved_24_31        : 8;
        uint64_t cq_pass               : 8;  /**< [ 23: 16](R/W) Threshold level for RED accepting packets, in units of 1/256th of CQ level.
                                                                 0xff represents an empty CQ, 0x0 represents a full CQ.
                                                                 If the CQ level is greater \>= to this value then the packet is received.
                                                                 If the CQ level is less that this value but \>= [CQ_DROP] then the packet is in the
                                                                 RED zone
                                                                 If the CQ level is \< [CQ_DROP], then the packet is dropped. */
        uint64_t cq_drop               : 8;  /**< [ 15:  8](R/W) Threshold level for RED dropping packets, in units of 1/256th of CQ level. See [CQ_PASS]
                                                                 for
                                                                 more details. */
        uint64_t reserved_0_7          : 8;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_7          : 8;
        uint64_t cq_drop               : 8;  /**< [ 15:  8](R/W) Threshold level for RED dropping packets, in units of 1/256th of CQ level. See [CQ_PASS]
                                                                 for
                                                                 more details. */
        uint64_t cq_pass               : 8;  /**< [ 23: 16](R/W) Threshold level for RED accepting packets, in units of 1/256th of CQ level.
                                                                 0xff represents an empty CQ, 0x0 represents a full CQ.
                                                                 If the CQ level is greater \>= to this value then the packet is received.
                                                                 If the CQ level is less that this value but \>= [CQ_DROP] then the packet is in the
                                                                 RED zone
                                                                 If the CQ level is \< [CQ_DROP], then the packet is dropped. */
        uint64_t reserved_24_31        : 8;
        uint64_t rbdr_drop             : 8;  /**< [ 39: 32](R/W) Threshold level for RED dropping packets, in units of 1/256th of RBDR level. See
                                                                 [RBDR_PASS]
                                                                 for more details. */
        uint64_t rbdr_pass             : 8;  /**< [ 47: 40](R/W) Threshold level for RED accepting packets, in units of 1/256th of RBDR level.
                                                                 0xff represents a full RBDR, 0x0 represents an empty RBDR.
                                                                 If the RBDR level is greater \>= to this value then the packet is received.
                                                                 If the RBDR level is less that this value but \>= [RBDR_DROP] value then the packet is in
                                                                 the RED zone
                                                                 If the RBDR level is \< [RBDR_DROP], then the packet is dropped. */
        uint64_t reserved_48_61        : 14;
        uint64_t cq_red                : 1;  /**< [ 62: 62](R/W) Enable CQ RED drop between PASS and DROP levels. */
        uint64_t rbdr_red              : 1;  /**< [ 63: 63](R/W) Enable RBDR RED drop between PASS and DROP levels. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_qsx_rqx_drop_cfg_s cn; */
};
typedef union bdk_nic_pf_qsx_rqx_drop_cfg bdk_nic_pf_qsx_rqx_drop_cfg_t;

static inline uint64_t BDK_NIC_PF_QSX_RQX_DROP_CFG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_QSX_RQX_DROP_CFG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x843020010420ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x843020010420ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_PF_QSX_RQX_DROP_CFG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_QSX_RQX_DROP_CFG(a,b) bdk_nic_pf_qsx_rqx_drop_cfg_t
#define bustype_BDK_NIC_PF_QSX_RQX_DROP_CFG(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_QSX_RQX_DROP_CFG(a,b) "NIC_PF_QSX_RQX_DROP_CFG"
#define device_bar_BDK_NIC_PF_QSX_RQX_DROP_CFG(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_QSX_RQX_DROP_CFG(a,b) (a)
#define arguments_BDK_NIC_PF_QSX_RQX_DROP_CFG(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_pf_qs#_rq#_stat#
 *
 * NIC PF Receive-Queue Statistics Registers
 * The third dimension indicates which statistic, and is enumerated by NIC_STAT_RQ_E.
 */
union bdk_nic_pf_qsx_rqx_statx
{
    uint64_t u;
    struct bdk_nic_pf_qsx_rqx_statx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) Statistic value. See also NIC_QS()_RQ()_STAT() for a read-only alias of this field. */
#else /* Word 0 - Little Endian */
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) Statistic value. See also NIC_QS()_RQ()_STAT() for a read-only alias of this field. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_qsx_rqx_statx_s cn; */
};
typedef union bdk_nic_pf_qsx_rqx_statx bdk_nic_pf_qsx_rqx_statx_t;

static inline uint64_t BDK_NIC_PF_QSX_RQX_STATX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_QSX_RQX_STATX(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7) && (c<=1)))
        return 0x843020010600ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7) + 8ll * ((c) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7) && (c<=1)))
        return 0x843020010600ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7) + 8ll * ((c) & 0x1);
    __bdk_csr_fatal("NIC_PF_QSX_RQX_STATX", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_QSX_RQX_STATX(a,b,c) bdk_nic_pf_qsx_rqx_statx_t
#define bustype_BDK_NIC_PF_QSX_RQX_STATX(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_QSX_RQX_STATX(a,b,c) "NIC_PF_QSX_RQX_STATX"
#define device_bar_BDK_NIC_PF_QSX_RQX_STATX(a,b,c) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_QSX_RQX_STATX(a,b,c) (a)
#define arguments_BDK_NIC_PF_QSX_RQX_STATX(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB) nic_pf_qs#_sq#_cfg
 *
 * NIC Send-Queue Configuration Registers
 */
union bdk_nic_pf_qsx_sqx_cfg
{
    uint64_t u;
    struct bdk_nic_pf_qsx_sqx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t sq_ins_data           : 16; /**< [ 47: 32](R/W) SQ insertion data.If NIC_PF_QS()_CFG[SQ_INS_ENA] is set, this is the data inserted
                                                                 in every packet transmitted by the SQ, as follows:
                                                                 * [SQ_INS_DATA]\<7:0\> = packet byte NIC_PF_QS()_CFG[SQ_INS_POS]
                                                                 * [SQ_INS_DATA]\<15:8\> = packet byte NIC_PF_QS()_CFG[SQ_INS_POS]+1 */
        uint64_t reserved_8_31         : 24;
        uint64_t cq_qs                 : 5;  /**< [  7:  3](R/W) CQ's QS for this SQ. The CQ's QS must be assigned to the same VNIC as the SQ's QS.
                                                                 Must be less than 8. */
        uint64_t cq_idx                : 3;  /**< [  2:  0](R/W) CQ within [CQ_QS] for this SQ. */
#else /* Word 0 - Little Endian */
        uint64_t cq_idx                : 3;  /**< [  2:  0](R/W) CQ within [CQ_QS] for this SQ. */
        uint64_t cq_qs                 : 5;  /**< [  7:  3](R/W) CQ's QS for this SQ. The CQ's QS must be assigned to the same VNIC as the SQ's QS.
                                                                 Must be less than 8. */
        uint64_t reserved_8_31         : 24;
        uint64_t sq_ins_data           : 16; /**< [ 47: 32](R/W) SQ insertion data.If NIC_PF_QS()_CFG[SQ_INS_ENA] is set, this is the data inserted
                                                                 in every packet transmitted by the SQ, as follows:
                                                                 * [SQ_INS_DATA]\<7:0\> = packet byte NIC_PF_QS()_CFG[SQ_INS_POS]
                                                                 * [SQ_INS_DATA]\<15:8\> = packet byte NIC_PF_QS()_CFG[SQ_INS_POS]+1 */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_qsx_sqx_cfg_s cn8; */
    struct bdk_nic_pf_qsx_sqx_cfg_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t sq_ins_data           : 16; /**< [ 47: 32](R/W) SQ insertion data.If NIC_PF_QS()_CFG[SQ_INS_ENA] is set, this is the data inserted
                                                                 in every packet transmitted by the SQ, as follows:
                                                                 * [SQ_INS_DATA]\<7:0\> = packet byte NIC_PF_QS()_CFG[SQ_INS_POS]
                                                                 * [SQ_INS_DATA]\<15:8\> = packet byte NIC_PF_QS()_CFG[SQ_INS_POS]+1 */
        uint64_t reserved_8_31         : 24;
        uint64_t reserved_6_7          : 2;
        uint64_t cq_qs                 : 3;  /**< [  5:  3](R/W) CQ's QS for this SQ. The CQ's QS must be assigned to the same VNIC as the SQ's QS.
                                                                 Must be less than 8. */
        uint64_t cq_idx                : 3;  /**< [  2:  0](R/W) CQ within [CQ_QS] for this SQ. */
#else /* Word 0 - Little Endian */
        uint64_t cq_idx                : 3;  /**< [  2:  0](R/W) CQ within [CQ_QS] for this SQ. */
        uint64_t cq_qs                 : 3;  /**< [  5:  3](R/W) CQ's QS for this SQ. The CQ's QS must be assigned to the same VNIC as the SQ's QS.
                                                                 Must be less than 8. */
        uint64_t reserved_6_7          : 2;
        uint64_t reserved_8_31         : 24;
        uint64_t sq_ins_data           : 16; /**< [ 47: 32](R/W) SQ insertion data.If NIC_PF_QS()_CFG[SQ_INS_ENA] is set, this is the data inserted
                                                                 in every packet transmitted by the SQ, as follows:
                                                                 * [SQ_INS_DATA]\<7:0\> = packet byte NIC_PF_QS()_CFG[SQ_INS_POS]
                                                                 * [SQ_INS_DATA]\<15:8\> = packet byte NIC_PF_QS()_CFG[SQ_INS_POS]+1 */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } cn81xx;
    struct bdk_nic_pf_qsx_sqx_cfg_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t sq_ins_data           : 16; /**< [ 47: 32](R/W) SQ insertion data.If NIC_PF_QS()_CFG[SQ_INS_ENA] is set, this is the data inserted
                                                                 in every packet transmitted by the SQ, as follows:
                                                                 * [SQ_INS_DATA]\<7:0\> = packet byte NIC_PF_QS()_CFG[SQ_INS_POS]
                                                                 * [SQ_INS_DATA]\<15:8\> = packet byte NIC_PF_QS()_CFG[SQ_INS_POS]+1 */
        uint64_t reserved_8_31         : 24;
        uint64_t cq_qs                 : 5;  /**< [  7:  3](R/W) CQ's QS for this SQ. The CQ's QS must be assigned to the same VNIC as the SQ's QS.
                                                                 Must be less than 32. */
        uint64_t cq_idx                : 3;  /**< [  2:  0](R/W) CQ within [CQ_QS] for this SQ. */
#else /* Word 0 - Little Endian */
        uint64_t cq_idx                : 3;  /**< [  2:  0](R/W) CQ within [CQ_QS] for this SQ. */
        uint64_t cq_qs                 : 5;  /**< [  7:  3](R/W) CQ's QS for this SQ. The CQ's QS must be assigned to the same VNIC as the SQ's QS.
                                                                 Must be less than 32. */
        uint64_t reserved_8_31         : 24;
        uint64_t sq_ins_data           : 16; /**< [ 47: 32](R/W) SQ insertion data.If NIC_PF_QS()_CFG[SQ_INS_ENA] is set, this is the data inserted
                                                                 in every packet transmitted by the SQ, as follows:
                                                                 * [SQ_INS_DATA]\<7:0\> = packet byte NIC_PF_QS()_CFG[SQ_INS_POS]
                                                                 * [SQ_INS_DATA]\<15:8\> = packet byte NIC_PF_QS()_CFG[SQ_INS_POS]+1 */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_pf_qsx_sqx_cfg bdk_nic_pf_qsx_sqx_cfg_t;

static inline uint64_t BDK_NIC_PF_QSX_SQX_CFG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_QSX_SQX_CFG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x843020010c00ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x843020010c00ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_PF_QSX_SQX_CFG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_QSX_SQX_CFG(a,b) bdk_nic_pf_qsx_sqx_cfg_t
#define bustype_BDK_NIC_PF_QSX_SQX_CFG(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_QSX_SQX_CFG(a,b) "NIC_PF_QSX_SQX_CFG"
#define device_bar_BDK_NIC_PF_QSX_SQX_CFG(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_QSX_SQX_CFG(a,b) (a)
#define arguments_BDK_NIC_PF_QSX_SQX_CFG(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_pf_qs#_sq#_cfg2
 *
 * NIC Send-Queue Configuration Registers 2
 */
union bdk_nic_pf_qsx_sqx_cfg2
{
    uint64_t u;
    struct bdk_nic_pf_qsx_sqx_cfg2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t tl4                   : 8;  /**< [  7:  0](R/W) TL4 index. Must point to the unique TL4 that will service this traffic, and
                                                                 NIC_PF_TL4()_CFG[SQ_QS]/NIC_PF_TL4()_CFG[SQ_IDX] must point back to this SQ. As the VF
                                                                 controls
                                                                 NIC_QS()_SQ()_CFG[ENA], these pointers should be valid even for non-enabled SQs.
                                                                 Must be less than 64. */
#else /* Word 0 - Little Endian */
        uint64_t tl4                   : 8;  /**< [  7:  0](R/W) TL4 index. Must point to the unique TL4 that will service this traffic, and
                                                                 NIC_PF_TL4()_CFG[SQ_QS]/NIC_PF_TL4()_CFG[SQ_IDX] must point back to this SQ. As the VF
                                                                 controls
                                                                 NIC_QS()_SQ()_CFG[ENA], these pointers should be valid even for non-enabled SQs.
                                                                 Must be less than 64. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_qsx_sqx_cfg2_s cn8; */
    struct bdk_nic_pf_qsx_sqx_cfg2_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t reserved_6_7          : 2;
        uint64_t tl4                   : 6;  /**< [  5:  0](R/W) TL4 index. Must point to the unique TL4 that will service this traffic, and
                                                                 NIC_PF_TL4()_CFG[SQ_QS]/NIC_PF_TL4()_CFG[SQ_IDX] must point back to this SQ. As the VF
                                                                 controls
                                                                 NIC_QS()_SQ()_CFG[ENA], these pointers should be valid even for non-enabled SQs.
                                                                 Must be less than 64. */
#else /* Word 0 - Little Endian */
        uint64_t tl4                   : 6;  /**< [  5:  0](R/W) TL4 index. Must point to the unique TL4 that will service this traffic, and
                                                                 NIC_PF_TL4()_CFG[SQ_QS]/NIC_PF_TL4()_CFG[SQ_IDX] must point back to this SQ. As the VF
                                                                 controls
                                                                 NIC_QS()_SQ()_CFG[ENA], these pointers should be valid even for non-enabled SQs.
                                                                 Must be less than 64. */
        uint64_t reserved_6_7          : 2;
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } cn81xx;
    struct bdk_nic_pf_qsx_sqx_cfg2_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t tl4                   : 8;  /**< [  7:  0](R/W) TL4 index. Must point to the unique TL4 that will service this traffic, and
                                                                 NIC_PF_TL4()_CFG[SQ_QS]/NIC_PF_TL4()_CFG[SQ_IDX] must point back to this SQ. As the VF
                                                                 controls
                                                                 NIC_QS()_SQ()_CFG[ENA], these pointers should be valid even for non-enabled SQs.
                                                                 Must be less than 256. */
#else /* Word 0 - Little Endian */
        uint64_t tl4                   : 8;  /**< [  7:  0](R/W) TL4 index. Must point to the unique TL4 that will service this traffic, and
                                                                 NIC_PF_TL4()_CFG[SQ_QS]/NIC_PF_TL4()_CFG[SQ_IDX] must point back to this SQ. As the VF
                                                                 controls
                                                                 NIC_QS()_SQ()_CFG[ENA], these pointers should be valid even for non-enabled SQs.
                                                                 Must be less than 256. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_pf_qsx_sqx_cfg2 bdk_nic_pf_qsx_sqx_cfg2_t;

static inline uint64_t BDK_NIC_PF_QSX_SQX_CFG2(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_QSX_SQX_CFG2(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x843020010c08ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x843020010c08ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_PF_QSX_SQX_CFG2", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_QSX_SQX_CFG2(a,b) bdk_nic_pf_qsx_sqx_cfg2_t
#define bustype_BDK_NIC_PF_QSX_SQX_CFG2(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_QSX_SQX_CFG2(a,b) "NIC_PF_QSX_SQX_CFG2"
#define device_bar_BDK_NIC_PF_QSX_SQX_CFG2(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_QSX_SQX_CFG2(a,b) (a)
#define arguments_BDK_NIC_PF_QSX_SQX_CFG2(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_pf_qs#_sq#_stat#
 *
 * NIC PF Send-Queue Statistics Registers
 * The third dimension indicates which statistic, and is enumerated by NIC_STAT_SQ_E.
 */
union bdk_nic_pf_qsx_sqx_statx
{
    uint64_t u;
    struct bdk_nic_pf_qsx_sqx_statx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) Statistic value. See also NIC_QS()_SQ()_STAT() for a read-only alias of this field. */
#else /* Word 0 - Little Endian */
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) Statistic value. See also NIC_QS()_SQ()_STAT() for a read-only alias of this field. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_qsx_sqx_statx_s cn; */
};
typedef union bdk_nic_pf_qsx_sqx_statx bdk_nic_pf_qsx_sqx_statx_t;

static inline uint64_t BDK_NIC_PF_QSX_SQX_STATX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_QSX_SQX_STATX(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7) && (c<=1)))
        return 0x843020010d00ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7) + 8ll * ((c) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7) && (c<=1)))
        return 0x843020010d00ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7) + 8ll * ((c) & 0x1);
    __bdk_csr_fatal("NIC_PF_QSX_SQX_STATX", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_QSX_SQX_STATX(a,b,c) bdk_nic_pf_qsx_sqx_statx_t
#define bustype_BDK_NIC_PF_QSX_SQX_STATX(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_QSX_SQX_STATX(a,b,c) "NIC_PF_QSX_SQX_STATX"
#define device_bar_BDK_NIC_PF_QSX_SQX_STATX(a,b,c) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_QSX_SQX_STATX(a,b,c) (a)
#define arguments_BDK_NIC_PF_QSX_SQX_STATX(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB) nic_pf_rqm_test
 *
 * INTERNAL: NIC RQM Test Register
 */
union bdk_nic_pf_rqm_test
{
    uint64_t u;
    struct bdk_nic_pf_rqm_test_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = rqm_drop_intr_stall.
                                                                 \<61\> = reb1_cq_stall.
                                                                 \<60\> = reb0_cq_stall. */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = bp_cfg3.
                                                                   \<21:20\> = bp_cfg2.
                                                                   \<19:18\> = bp_cfg1.
                                                                   \<17:16\> = bp_cfg0. */
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
                                                                   \<23:22\> = bp_cfg3.
                                                                   \<21:20\> = bp_cfg2.
                                                                   \<19:18\> = bp_cfg1.
                                                                   \<17:16\> = bp_cfg0. */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = rqm_drop_intr_stall.
                                                                 \<61\> = reb1_cq_stall.
                                                                 \<60\> = reb0_cq_stall. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_rqm_test_s cn; */
};
typedef union bdk_nic_pf_rqm_test bdk_nic_pf_rqm_test_t;

#define BDK_NIC_PF_RQM_TEST BDK_NIC_PF_RQM_TEST_FUNC()
static inline uint64_t BDK_NIC_PF_RQM_TEST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_RQM_TEST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000000098ll;
    __bdk_csr_fatal("NIC_PF_RQM_TEST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_RQM_TEST bdk_nic_pf_rqm_test_t
#define bustype_BDK_NIC_PF_RQM_TEST BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_RQM_TEST "NIC_PF_RQM_TEST"
#define device_bar_BDK_NIC_PF_RQM_TEST 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_RQM_TEST 0
#define arguments_BDK_NIC_PF_RQM_TEST -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_rrm_avg_cfg
 *
 * NIC PF RBDR-Averaging Configuration Register
 */
union bdk_nic_pf_rrm_avg_cfg
{
    uint64_t u;
    struct bdk_nic_pf_rrm_avg_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_21_63        : 43;
        uint64_t avg_en                : 1;  /**< [ 20: 20](R/W) QoS averaging enable. When set, compute average buffer levels. When clear, do not compute
                                                                 averages and save a few mW of power. */
        uint64_t lvl_dly               : 6;  /**< [ 19: 14](R/W) Levelizer delay. See [AVG_DLY]. Must be nonzero when [AVG_EN] is set. */
        uint64_t avg_dly               : 14; /**< [ 13:  0](R/W) Average-queue-size delay. Must be nonzero when [AVG_EN] is set. The moving average
                                                                 calculation for each RBDR is performed every 1024 * ([AVG_DLY]+1) * ([LVL_DLY]+1)
                                                                 coprocessor clocks. Note the minimum value of 8192 cycles implies that at 50 M
                                                                 packets/sec, and a coprocessor clock of 800 MHz, approximately 250 packets may arrive
                                                                 between average calculations.

                                                                 Larger [LVL_DLY] and [AVG_DLY] values cause the moving averages of all RBDR levels to
                                                                 track changes in the actual free space more slowly. Larger NIC_QS()_RBDR()_CFG[AVG_CON]
                                                                 values causes a specific RBDR to track more slowly, but only affects an individual RBDR
                                                                 level, rather than all. */
#else /* Word 0 - Little Endian */
        uint64_t avg_dly               : 14; /**< [ 13:  0](R/W) Average-queue-size delay. Must be nonzero when [AVG_EN] is set. The moving average
                                                                 calculation for each RBDR is performed every 1024 * ([AVG_DLY]+1) * ([LVL_DLY]+1)
                                                                 coprocessor clocks. Note the minimum value of 8192 cycles implies that at 50 M
                                                                 packets/sec, and a coprocessor clock of 800 MHz, approximately 250 packets may arrive
                                                                 between average calculations.

                                                                 Larger [LVL_DLY] and [AVG_DLY] values cause the moving averages of all RBDR levels to
                                                                 track changes in the actual free space more slowly. Larger NIC_QS()_RBDR()_CFG[AVG_CON]
                                                                 values causes a specific RBDR to track more slowly, but only affects an individual RBDR
                                                                 level, rather than all. */
        uint64_t lvl_dly               : 6;  /**< [ 19: 14](R/W) Levelizer delay. See [AVG_DLY]. Must be nonzero when [AVG_EN] is set. */
        uint64_t avg_en                : 1;  /**< [ 20: 20](R/W) QoS averaging enable. When set, compute average buffer levels. When clear, do not compute
                                                                 averages and save a few mW of power. */
        uint64_t reserved_21_63        : 43;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_rrm_avg_cfg_s cn; */
};
typedef union bdk_nic_pf_rrm_avg_cfg bdk_nic_pf_rrm_avg_cfg_t;

#define BDK_NIC_PF_RRM_AVG_CFG BDK_NIC_PF_RRM_AVG_CFG_FUNC()
static inline uint64_t BDK_NIC_PF_RRM_AVG_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_RRM_AVG_CFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x8430000000c8ll;
    __bdk_csr_fatal("NIC_PF_RRM_AVG_CFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_RRM_AVG_CFG bdk_nic_pf_rrm_avg_cfg_t
#define bustype_BDK_NIC_PF_RRM_AVG_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_RRM_AVG_CFG "NIC_PF_RRM_AVG_CFG"
#define device_bar_BDK_NIC_PF_RRM_AVG_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_RRM_AVG_CFG 0
#define arguments_BDK_NIC_PF_RRM_AVG_CFG -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_rrm_cfg
 *
 * NIC PF RRM Configuration Register
 */
union bdk_nic_pf_rrm_cfg
{
    uint64_t u;
    struct bdk_nic_pf_rrm_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_19_63        : 45;
        uint64_t drop_level            : 19; /**< [ 18:  0](R/W) Drop level. The minimum FIFO level before all packets for the RBDR are dropped.  This
                                                                 value can be increased to insure that once a packet has been "accepted", it will not get
                                                                 truncated due to buffer exhaustion. */
#else /* Word 0 - Little Endian */
        uint64_t drop_level            : 19; /**< [ 18:  0](R/W) Drop level. The minimum FIFO level before all packets for the RBDR are dropped.  This
                                                                 value can be increased to insure that once a packet has been "accepted", it will not get
                                                                 truncated due to buffer exhaustion. */
        uint64_t reserved_19_63        : 45;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_rrm_cfg_s cn; */
};
typedef union bdk_nic_pf_rrm_cfg bdk_nic_pf_rrm_cfg_t;

#define BDK_NIC_PF_RRM_CFG BDK_NIC_PF_RRM_CFG_FUNC()
static inline uint64_t BDK_NIC_PF_RRM_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_RRM_CFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000000088ll;
    __bdk_csr_fatal("NIC_PF_RRM_CFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_RRM_CFG bdk_nic_pf_rrm_cfg_t
#define bustype_BDK_NIC_PF_RRM_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_RRM_CFG "NIC_PF_RRM_CFG"
#define device_bar_BDK_NIC_PF_RRM_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_RRM_CFG 0
#define arguments_BDK_NIC_PF_RRM_CFG -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_rrm_test
 *
 * INTERNAL: NIC RRM Test Register
 */
union bdk_nic_pf_rrm_test
{
    uint64_t u;
    struct bdk_nic_pf_rrm_test_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = rrm_ncb_req_stall.
                                                                 \<61\> = rrm_ncb_rsp_stall.
                                                                 \<60\> = rrm_intr_fifo. */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = bp_cfg3.
                                                                   \<21:20\> = bp_cfg2.
                                                                   \<19:18\> = bp_cfg1.
                                                                   \<17:16\> = bp_cfg0. */
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
                                                                   \<23:22\> = bp_cfg3.
                                                                   \<21:20\> = bp_cfg2.
                                                                   \<19:18\> = bp_cfg1.
                                                                   \<17:16\> = bp_cfg0. */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = rrm_ncb_req_stall.
                                                                 \<61\> = rrm_ncb_rsp_stall.
                                                                 \<60\> = rrm_intr_fifo. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_rrm_test_s cn; */
};
typedef union bdk_nic_pf_rrm_test bdk_nic_pf_rrm_test_t;

#define BDK_NIC_PF_RRM_TEST BDK_NIC_PF_RRM_TEST_FUNC()
static inline uint64_t BDK_NIC_PF_RRM_TEST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_RRM_TEST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000000090ll;
    __bdk_csr_fatal("NIC_PF_RRM_TEST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_RRM_TEST bdk_nic_pf_rrm_test_t
#define bustype_BDK_NIC_PF_RRM_TEST BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_RRM_TEST "NIC_PF_RRM_TEST"
#define device_bar_BDK_NIC_PF_RRM_TEST 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_RRM_TEST 0
#define arguments_BDK_NIC_PF_RRM_TEST -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_rssi#_rq
 *
 * NIC RSSI Indirection Receive Queue Registers
 * The RSSI table is used to distribute RSS hashes to compute which RQ receives a packet.
 */
union bdk_nic_pf_rssix_rq
{
    uint64_t u;
    struct bdk_nic_pf_rssix_rq_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t rq_qs                 : 5;  /**< [  7:  3](R/W) RQ's QS. */
        uint64_t rq_idx                : 3;  /**< [  2:  0](R/W) RQ within [RQ_QS]. */
#else /* Word 0 - Little Endian */
        uint64_t rq_idx                : 3;  /**< [  2:  0](R/W) RQ within [RQ_QS]. */
        uint64_t rq_qs                 : 5;  /**< [  7:  3](R/W) RQ's QS. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_rssix_rq_s cn8; */
    struct bdk_nic_pf_rssix_rq_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t reserved_6_9          : 4;
        uint64_t rq_qs                 : 3;  /**< [  5:  3](R/W) RQ's QS. */
        uint64_t rq_idx                : 3;  /**< [  2:  0](R/W) RQ within [RQ_QS]. */
#else /* Word 0 - Little Endian */
        uint64_t rq_idx                : 3;  /**< [  2:  0](R/W) RQ within [RQ_QS]. */
        uint64_t rq_qs                 : 3;  /**< [  5:  3](R/W) RQ's QS. */
        uint64_t reserved_6_9          : 4;
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } cn81xx;
    struct bdk_nic_pf_rssix_rq_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t reserved_8_9          : 2;
        uint64_t rq_qs                 : 5;  /**< [  7:  3](R/W) RQ's QS. */
        uint64_t rq_idx                : 3;  /**< [  2:  0](R/W) RQ within [RQ_QS]. */
#else /* Word 0 - Little Endian */
        uint64_t rq_idx                : 3;  /**< [  2:  0](R/W) RQ within [RQ_QS]. */
        uint64_t rq_qs                 : 5;  /**< [  7:  3](R/W) RQ's QS. */
        uint64_t reserved_8_9          : 2;
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_pf_rssix_rq bdk_nic_pf_rssix_rq_t;

static inline uint64_t BDK_NIC_PF_RSSIX_RQ(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_RSSIX_RQ(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=255))
        return 0x843000220000ll + 8ll * ((a) & 0xff);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1023))
        return 0x843000220000ll + 8ll * ((a) & 0x3ff);
    __bdk_csr_fatal("NIC_PF_RSSIX_RQ", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_RSSIX_RQ(a) bdk_nic_pf_rssix_rq_t
#define bustype_BDK_NIC_PF_RSSIX_RQ(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_RSSIX_RQ(a) "NIC_PF_RSSIX_RQ"
#define device_bar_BDK_NIC_PF_RSSIX_RQ(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_RSSIX_RQ(a) (a)
#define arguments_BDK_NIC_PF_RSSIX_RQ(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_rx_bp_state#
 *
 * NIC RBDR Backpressure State Registers
 */
union bdk_nic_pf_rx_bp_statex
{
    uint64_t u;
    struct bdk_nic_pf_rx_bp_statex_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t bp_state              : 64; /**< [ 63:  0](RO/H) Interface backpressure state bit: 1=XOFF, 0=XON. Does not reflect channel backpressure
                                                                 software overrides by NIC_PF_RX_CHAN_BP_SW()[BP_SW] and NIC_PF_RX_CHAN_BP_DIS()[BP_DIS]. */
#else /* Word 0 - Little Endian */
        uint64_t bp_state              : 64; /**< [ 63:  0](RO/H) Interface backpressure state bit: 1=XOFF, 0=XON. Does not reflect channel backpressure
                                                                 software overrides by NIC_PF_RX_CHAN_BP_SW()[BP_SW] and NIC_PF_RX_CHAN_BP_DIS()[BP_DIS]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_rx_bp_statex_s cn; */
};
typedef union bdk_nic_pf_rx_bp_statex bdk_nic_pf_rx_bp_statex_t;

static inline uint64_t BDK_NIC_PF_RX_BP_STATEX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_RX_BP_STATEX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=1))
        return 0x843000000340ll + 8ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x843000000340ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("NIC_PF_RX_BP_STATEX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_RX_BP_STATEX(a) bdk_nic_pf_rx_bp_statex_t
#define bustype_BDK_NIC_PF_RX_BP_STATEX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_RX_BP_STATEX(a) "NIC_PF_RX_BP_STATEX"
#define device_bar_BDK_NIC_PF_RX_BP_STATEX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_RX_BP_STATEX(a) (a)
#define arguments_BDK_NIC_PF_RX_BP_STATEX(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_rx_bpid_state#
 *
 * NIC Backpressure ID State Registers
 * Internal:
 * Renamed from NIC_PF_RBDR_BP_STATE() in 88XX.
 */
union bdk_nic_pf_rx_bpid_statex
{
    uint64_t u;
    struct bdk_nic_pf_rx_bpid_statex_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t bpid_state            : 64; /**< [ 63:  0](RO/H) Backpressure state bit per BPID: 1=XOFF, 0=XON.
                                                                 Reflects the channel backpressure component that is calculated off the RQ's RBDR and CQ
                                                                 level comparisons using registers NIC_PF_QS()_RQ()_BP_CFG and NIC_PF_CHAN()_RX_BP_CFG. */
#else /* Word 0 - Little Endian */
        uint64_t bpid_state            : 64; /**< [ 63:  0](RO/H) Backpressure state bit per BPID: 1=XOFF, 0=XON.
                                                                 Reflects the channel backpressure component that is calculated off the RQ's RBDR and CQ
                                                                 level comparisons using registers NIC_PF_QS()_RQ()_BP_CFG and NIC_PF_CHAN()_RX_BP_CFG. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_rx_bpid_statex_s cn; */
};
typedef union bdk_nic_pf_rx_bpid_statex bdk_nic_pf_rx_bpid_statex_t;

static inline uint64_t BDK_NIC_PF_RX_BPID_STATEX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_RX_BPID_STATEX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=1))
        return 0x843000000240ll + 8ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x843000000240ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("NIC_PF_RX_BPID_STATEX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_RX_BPID_STATEX(a) bdk_nic_pf_rx_bpid_statex_t
#define bustype_BDK_NIC_PF_RX_BPID_STATEX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_RX_BPID_STATEX(a) "NIC_PF_RX_BPID_STATEX"
#define device_bar_BDK_NIC_PF_RX_BPID_STATEX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_RX_BPID_STATEX(a) (a)
#define arguments_BDK_NIC_PF_RX_BPID_STATEX(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_rx_cfg
 *
 * NIC Receive Configuration Register
 */
union bdk_nic_pf_rx_cfg
{
    uint64_t u;
    struct bdk_nic_pf_rx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t cqe_rx2_disable       : 1;  /**< [  0:  0](RAZ) Always 0. NIC_CQE_RX2_S extension in CQM RX messages is always enabled. */
#else /* Word 0 - Little Endian */
        uint64_t cqe_rx2_disable       : 1;  /**< [  0:  0](RAZ) Always 0. NIC_CQE_RX2_S extension in CQM RX messages is always enabled. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_rx_cfg_s cn; */
};
typedef union bdk_nic_pf_rx_cfg bdk_nic_pf_rx_cfg_t;

#define BDK_NIC_PF_RX_CFG BDK_NIC_PF_RX_CFG_FUNC()
static inline uint64_t BDK_NIC_PF_RX_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_RX_CFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x8430000005d0ll;
    __bdk_csr_fatal("NIC_PF_RX_CFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_RX_CFG bdk_nic_pf_rx_cfg_t
#define bustype_BDK_NIC_PF_RX_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_RX_CFG "NIC_PF_RX_CFG"
#define device_bar_BDK_NIC_PF_RX_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_RX_CFG 0
#define arguments_BDK_NIC_PF_RX_CFG -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_rx_chan_bp_dis#
 *
 * NIC Receive Channel Backpressure Disable Registers
 * Internal:
 * Renamed from NIC_PF_INTF()_BP_DIS() in 88XX.
 */
union bdk_nic_pf_rx_chan_bp_disx
{
    uint64_t u;
    struct bdk_nic_pf_rx_chan_bp_disx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t bp_dis                : 64; /**< [ 63:  0](R/W) Backpressure disable bit per channel. Bit index enumerated by NIC_CHAN_IDX_E. Setting a
                                                                 bit forces RX backpressure state for that channel to XON. */
#else /* Word 0 - Little Endian */
        uint64_t bp_dis                : 64; /**< [ 63:  0](R/W) Backpressure disable bit per channel. Bit index enumerated by NIC_CHAN_IDX_E. Setting a
                                                                 bit forces RX backpressure state for that channel to XON. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_rx_chan_bp_disx_s cn; */
};
typedef union bdk_nic_pf_rx_chan_bp_disx bdk_nic_pf_rx_chan_bp_disx_t;

static inline uint64_t BDK_NIC_PF_RX_CHAN_BP_DISX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_RX_CHAN_BP_DISX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=1))
        return 0x843000000800ll + 8ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x843000000800ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("NIC_PF_RX_CHAN_BP_DISX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_RX_CHAN_BP_DISX(a) bdk_nic_pf_rx_chan_bp_disx_t
#define bustype_BDK_NIC_PF_RX_CHAN_BP_DISX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_RX_CHAN_BP_DISX(a) "NIC_PF_RX_CHAN_BP_DISX"
#define device_bar_BDK_NIC_PF_RX_CHAN_BP_DISX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_RX_CHAN_BP_DISX(a) (a)
#define arguments_BDK_NIC_PF_RX_CHAN_BP_DISX(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_rx_chan_bp_sw#
 *
 * NIC Receive Channel Backpressure Software Force Registers
 * Internal:
 * Renamed from NIC_PF_INTF()_BP_SW() in 88XX.
 */
union bdk_nic_pf_rx_chan_bp_swx
{
    uint64_t u;
    struct bdk_nic_pf_rx_chan_bp_swx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t bp_sw                 : 64; /**< [ 63:  0](R/W) Backpressure software force bit per channel. Bit index enumerated by NIC_CHAN_IDX_E.
                                                                 Setting a
                                                                 bit forces RX backpressure state for that channel to XOFF. */
#else /* Word 0 - Little Endian */
        uint64_t bp_sw                 : 64; /**< [ 63:  0](R/W) Backpressure software force bit per channel. Bit index enumerated by NIC_CHAN_IDX_E.
                                                                 Setting a
                                                                 bit forces RX backpressure state for that channel to XOFF. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_rx_chan_bp_swx_s cn; */
};
typedef union bdk_nic_pf_rx_chan_bp_swx bdk_nic_pf_rx_chan_bp_swx_t;

static inline uint64_t BDK_NIC_PF_RX_CHAN_BP_SWX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_RX_CHAN_BP_SWX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=1))
        return 0x843000000840ll + 8ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x843000000840ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("NIC_PF_RX_CHAN_BP_SWX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_RX_CHAN_BP_SWX(a) bdk_nic_pf_rx_chan_bp_swx_t
#define bustype_BDK_NIC_PF_RX_CHAN_BP_SWX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_RX_CHAN_BP_SWX(a) "NIC_PF_RX_CHAN_BP_SWX"
#define device_bar_BDK_NIC_PF_RX_CHAN_BP_SWX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_RX_CHAN_BP_SWX(a) (a)
#define arguments_BDK_NIC_PF_RX_CHAN_BP_SWX(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_rx_etype#
 *
 * NIC Receive Ethertype Registers
 */
union bdk_nic_pf_rx_etypex
{
    uint64_t u;
    struct bdk_nic_pf_rx_etypex_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t advance               : 3;  /**< [ 21: 19](R/W) Number of 16-bit words (note: not bytes) to advance parse by, excluding the etype word,
                                                                 when the Ethertype is matched. */
        uint64_t alg                   : 3;  /**< [ 18: 16](R/W) Ethertype action, enumerated by NIC_ETYPE_ALG_E. If nonzero, enables matching against
                                                                 this Ethertype watcher, and the action to be taken on a match. */
        uint64_t etype                 : 16; /**< [ 15:  0](R/W) Ethertype to match this rule against if [ALG] is nonzero. If multiple registers have
                                                                 [ALG] nonzero and have the same [ETYPE], all fields in this register must have identical
                                                                 values or the results are undefined. Some of the standard Ethertypes are enumerated by
                                                                 NIC_ETHERTYPE_E. */
#else /* Word 0 - Little Endian */
        uint64_t etype                 : 16; /**< [ 15:  0](R/W) Ethertype to match this rule against if [ALG] is nonzero. If multiple registers have
                                                                 [ALG] nonzero and have the same [ETYPE], all fields in this register must have identical
                                                                 values or the results are undefined. Some of the standard Ethertypes are enumerated by
                                                                 NIC_ETHERTYPE_E. */
        uint64_t alg                   : 3;  /**< [ 18: 16](R/W) Ethertype action, enumerated by NIC_ETYPE_ALG_E. If nonzero, enables matching against
                                                                 this Ethertype watcher, and the action to be taken on a match. */
        uint64_t advance               : 3;  /**< [ 21: 19](R/W) Number of 16-bit words (note: not bytes) to advance parse by, excluding the etype word,
                                                                 when the Ethertype is matched. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_rx_etypex_s cn; */
};
typedef union bdk_nic_pf_rx_etypex bdk_nic_pf_rx_etypex_t;

static inline uint64_t BDK_NIC_PF_RX_ETYPEX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_RX_ETYPEX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x843000000500ll + 8ll * ((a) & 0x7);
    __bdk_csr_fatal("NIC_PF_RX_ETYPEX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_RX_ETYPEX(a) bdk_nic_pf_rx_etypex_t
#define bustype_BDK_NIC_PF_RX_ETYPEX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_RX_ETYPEX(a) "NIC_PF_RX_ETYPEX"
#define device_bar_BDK_NIC_PF_RX_ETYPEX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_RX_ETYPEX(a) (a)
#define arguments_BDK_NIC_PF_RX_ETYPEX(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_rx_geneve_def
 *
 * NIC Receive GENEVE Control Register
 */
union bdk_nic_pf_rx_geneve_def
{
    uint64_t u;
    struct bdk_nic_pf_rx_geneve_def_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ena                   : 1;  /**< [ 63: 63](R/W) Enables the parsing of GENEVE headers. */
        uint64_t reserved_16_62        : 47;
        uint64_t udp_port_num          : 16; /**< [ 15:  0](R/W) UDP destination port number that indicates a GENEVE header. */
#else /* Word 0 - Little Endian */
        uint64_t udp_port_num          : 16; /**< [ 15:  0](R/W) UDP destination port number that indicates a GENEVE header. */
        uint64_t reserved_16_62        : 47;
        uint64_t ena                   : 1;  /**< [ 63: 63](R/W) Enables the parsing of GENEVE headers. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_rx_geneve_def_s cn; */
};
typedef union bdk_nic_pf_rx_geneve_def bdk_nic_pf_rx_geneve_def_t;

#define BDK_NIC_PF_RX_GENEVE_DEF BDK_NIC_PF_RX_GENEVE_DEF_FUNC()
static inline uint64_t BDK_NIC_PF_RX_GENEVE_DEF_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_RX_GENEVE_DEF_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000000580ll;
    __bdk_csr_fatal("NIC_PF_RX_GENEVE_DEF", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_RX_GENEVE_DEF bdk_nic_pf_rx_geneve_def_t
#define bustype_BDK_NIC_PF_RX_GENEVE_DEF BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_RX_GENEVE_DEF "NIC_PF_RX_GENEVE_DEF"
#define device_bar_BDK_NIC_PF_RX_GENEVE_DEF 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_RX_GENEVE_DEF 0
#define arguments_BDK_NIC_PF_RX_GENEVE_DEF -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_rx_geneve_prot_def
 *
 * NIC Receive GENEVE Protocol Definition Register
 */
union bdk_nic_pf_rx_geneve_prot_def
{
    uint64_t u;
    struct bdk_nic_pf_rx_geneve_prot_def_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ena_ipv6              : 1;  /**< [ 63: 63](R/W) Enables the [IPV6_PROT] value. */
        uint64_t ena_ipv4              : 1;  /**< [ 62: 62](R/W) Enables the [IPV4_PROT] value. */
        uint64_t ena_et                : 1;  /**< [ 61: 61](R/W) Enables the [ET_PROT] value. */
        uint64_t reserved_48_60        : 13;
        uint64_t ipv6_prot             : 16; /**< [ 47: 32](R/W) Protocol number to define the next layer of the packet is an inner IPv6 layer. */
        uint64_t ipv4_prot             : 16; /**< [ 31: 16](R/W) Protocol number to define the next layer of the packet is an inner IPv4 layer. */
        uint64_t et_prot               : 16; /**< [ 15:  0](R/W) Protocol number to define the next layer of the packet is an inner Ethernet layer. */
#else /* Word 0 - Little Endian */
        uint64_t et_prot               : 16; /**< [ 15:  0](R/W) Protocol number to define the next layer of the packet is an inner Ethernet layer. */
        uint64_t ipv4_prot             : 16; /**< [ 31: 16](R/W) Protocol number to define the next layer of the packet is an inner IPv4 layer. */
        uint64_t ipv6_prot             : 16; /**< [ 47: 32](R/W) Protocol number to define the next layer of the packet is an inner IPv6 layer. */
        uint64_t reserved_48_60        : 13;
        uint64_t ena_et                : 1;  /**< [ 61: 61](R/W) Enables the [ET_PROT] value. */
        uint64_t ena_ipv4              : 1;  /**< [ 62: 62](R/W) Enables the [IPV4_PROT] value. */
        uint64_t ena_ipv6              : 1;  /**< [ 63: 63](R/W) Enables the [IPV6_PROT] value. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_rx_geneve_prot_def_s cn; */
};
typedef union bdk_nic_pf_rx_geneve_prot_def bdk_nic_pf_rx_geneve_prot_def_t;

#define BDK_NIC_PF_RX_GENEVE_PROT_DEF BDK_NIC_PF_RX_GENEVE_PROT_DEF_FUNC()
static inline uint64_t BDK_NIC_PF_RX_GENEVE_PROT_DEF_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_RX_GENEVE_PROT_DEF_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000000588ll;
    __bdk_csr_fatal("NIC_PF_RX_GENEVE_PROT_DEF", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_RX_GENEVE_PROT_DEF bdk_nic_pf_rx_geneve_prot_def_t
#define bustype_BDK_NIC_PF_RX_GENEVE_PROT_DEF BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_RX_GENEVE_PROT_DEF "NIC_PF_RX_GENEVE_PROT_DEF"
#define device_bar_BDK_NIC_PF_RX_GENEVE_PROT_DEF 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_RX_GENEVE_PROT_DEF 0
#define arguments_BDK_NIC_PF_RX_GENEVE_PROT_DEF -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_rx_nvgre_prot_def
 *
 * NIC Receive NVGRE Protocol Definition Register
 */
union bdk_nic_pf_rx_nvgre_prot_def
{
    uint64_t u;
    struct bdk_nic_pf_rx_nvgre_prot_def_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ena_ipv6              : 1;  /**< [ 63: 63](R/W) Enables the [IPV6_PROT] value. */
        uint64_t ena_ipv4              : 1;  /**< [ 62: 62](R/W) Enables the [IPV4_PROT] value. */
        uint64_t ena_et                : 1;  /**< [ 61: 61](R/W) Enables the [ET_PROT] value. */
        uint64_t reserved_48_60        : 13;
        uint64_t ipv6_prot             : 16; /**< [ 47: 32](R/W) Protocol number to define the next layer of the packet is an inner IPv6 layer. */
        uint64_t ipv4_prot             : 16; /**< [ 31: 16](R/W) Protocol number to define the next layer of the packet is an inner IPv4 layer. */
        uint64_t et_prot               : 16; /**< [ 15:  0](R/W) Protocol number to define the next layer of the packet is an inner Ethernet layer. */
#else /* Word 0 - Little Endian */
        uint64_t et_prot               : 16; /**< [ 15:  0](R/W) Protocol number to define the next layer of the packet is an inner Ethernet layer. */
        uint64_t ipv4_prot             : 16; /**< [ 31: 16](R/W) Protocol number to define the next layer of the packet is an inner IPv4 layer. */
        uint64_t ipv6_prot             : 16; /**< [ 47: 32](R/W) Protocol number to define the next layer of the packet is an inner IPv6 layer. */
        uint64_t reserved_48_60        : 13;
        uint64_t ena_et                : 1;  /**< [ 61: 61](R/W) Enables the [ET_PROT] value. */
        uint64_t ena_ipv4              : 1;  /**< [ 62: 62](R/W) Enables the [IPV4_PROT] value. */
        uint64_t ena_ipv6              : 1;  /**< [ 63: 63](R/W) Enables the [IPV6_PROT] value. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_rx_nvgre_prot_def_s cn; */
};
typedef union bdk_nic_pf_rx_nvgre_prot_def bdk_nic_pf_rx_nvgre_prot_def_t;

#define BDK_NIC_PF_RX_NVGRE_PROT_DEF BDK_NIC_PF_RX_NVGRE_PROT_DEF_FUNC()
static inline uint64_t BDK_NIC_PF_RX_NVGRE_PROT_DEF_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_RX_NVGRE_PROT_DEF_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000000598ll;
    __bdk_csr_fatal("NIC_PF_RX_NVGRE_PROT_DEF", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_RX_NVGRE_PROT_DEF bdk_nic_pf_rx_nvgre_prot_def_t
#define bustype_BDK_NIC_PF_RX_NVGRE_PROT_DEF BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_RX_NVGRE_PROT_DEF "NIC_PF_RX_NVGRE_PROT_DEF"
#define device_bar_BDK_NIC_PF_RX_NVGRE_PROT_DEF 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_RX_NVGRE_PROT_DEF 0
#define arguments_BDK_NIC_PF_RX_NVGRE_PROT_DEF -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_rx_rocev2_def
 *
 * INTERNAL: NIC Receive RoCEv2 Control Register
 *
 * This register defines and enables RoCE version 2 parsing.
 * Internal:
 * Unused register.
 */
union bdk_nic_pf_rx_rocev2_def
{
    uint64_t u;
    struct bdk_nic_pf_rx_rocev2_def_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ena                   : 1;  /**< [ 63: 63](R/W) Enables the detection of RoCEv2 headers. */
        uint64_t reserved_16_62        : 47;
        uint64_t udp_port_num          : 16; /**< [ 15:  0](R/W) UDP destination port number that indicates a RoCEv2 header. */
#else /* Word 0 - Little Endian */
        uint64_t udp_port_num          : 16; /**< [ 15:  0](R/W) UDP destination port number that indicates a RoCEv2 header. */
        uint64_t reserved_16_62        : 47;
        uint64_t ena                   : 1;  /**< [ 63: 63](R/W) Enables the detection of RoCEv2 headers. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_rx_rocev2_def_s cn; */
};
typedef union bdk_nic_pf_rx_rocev2_def bdk_nic_pf_rx_rocev2_def_t;

#define BDK_NIC_PF_RX_ROCEV2_DEF BDK_NIC_PF_RX_ROCEV2_DEF_FUNC()
static inline uint64_t BDK_NIC_PF_RX_ROCEV2_DEF_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_RX_ROCEV2_DEF_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x8430000005c0ll;
    __bdk_csr_fatal("NIC_PF_RX_ROCEV2_DEF", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_RX_ROCEV2_DEF bdk_nic_pf_rx_rocev2_def_t
#define bustype_BDK_NIC_PF_RX_ROCEV2_DEF BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_RX_ROCEV2_DEF "NIC_PF_RX_ROCEV2_DEF"
#define device_bar_BDK_NIC_PF_RX_ROCEV2_DEF 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_RX_ROCEV2_DEF 0
#define arguments_BDK_NIC_PF_RX_ROCEV2_DEF -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_rx_vxlan_def#
 *
 * NIC Receive VXLAN Control Register
 */
union bdk_nic_pf_rx_vxlan_defx
{
    uint64_t u;
    struct bdk_nic_pf_rx_vxlan_defx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ena                   : 1;  /**< [ 63: 63](R/W) Enables the detection of VXLAN headers. */
        uint64_t reserved_16_62        : 47;
        uint64_t udp_port_num          : 16; /**< [ 15:  0](R/W) UDP destination port number that indicates a VXLAN header to enable tunneling into the
                                                                 inner layers
                                                                 for further parsing. */
#else /* Word 0 - Little Endian */
        uint64_t udp_port_num          : 16; /**< [ 15:  0](R/W) UDP destination port number that indicates a VXLAN header to enable tunneling into the
                                                                 inner layers
                                                                 for further parsing. */
        uint64_t reserved_16_62        : 47;
        uint64_t ena                   : 1;  /**< [ 63: 63](R/W) Enables the detection of VXLAN headers. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_rx_vxlan_defx_s cn; */
};
typedef union bdk_nic_pf_rx_vxlan_defx bdk_nic_pf_rx_vxlan_defx_t;

static inline uint64_t BDK_NIC_PF_RX_VXLAN_DEFX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_RX_VXLAN_DEFX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=1))
        return 0x8430000005a0ll + 8ll * ((a) & 0x1);
    __bdk_csr_fatal("NIC_PF_RX_VXLAN_DEFX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_RX_VXLAN_DEFX(a) bdk_nic_pf_rx_vxlan_defx_t
#define bustype_BDK_NIC_PF_RX_VXLAN_DEFX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_RX_VXLAN_DEFX(a) "NIC_PF_RX_VXLAN_DEFX"
#define device_bar_BDK_NIC_PF_RX_VXLAN_DEFX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_RX_VXLAN_DEFX(a) (a)
#define arguments_BDK_NIC_PF_RX_VXLAN_DEFX(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_rx_vxlan_prot_def
 *
 * NIC Receive VXLAN Protocol Definition Register
 */
union bdk_nic_pf_rx_vxlan_prot_def
{
    uint64_t u;
    struct bdk_nic_pf_rx_vxlan_prot_def_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ena_ipv6              : 1;  /**< [ 63: 63](R/W) Enables the [IPV6_PROT] value ([ENA_PROT] must be also set). */
        uint64_t ena_ipv4              : 1;  /**< [ 62: 62](R/W) Enables the [IPV4_PROT] value ([ENA_PROT] must be also set). */
        uint64_t ena_et                : 1;  /**< [ 61: 61](R/W) Enables the [ET_PROT] value ([ENA_PROT] must be also set). */
        uint64_t ena_prot              : 1;  /**< [ 60: 60](R/W) This enables protocol field checking inside the VXLAN header. */
        uint64_t reserved_40_59        : 20;
        uint64_t ipv6_prot             : 8;  /**< [ 39: 32](R/W) Protocol number to definite the next layer of the packet is an inner IPv6 layer. */
        uint64_t reserved_24_31        : 8;
        uint64_t ipv4_prot             : 8;  /**< [ 23: 16](R/W) Protocol number to definite the next layer of the packet is an inner IPv4 layer. */
        uint64_t reserved_8_15         : 8;
        uint64_t et_prot               : 8;  /**< [  7:  0](R/W) Protocol number to definite the next layer of the packet is an inner Ethernet layer. */
#else /* Word 0 - Little Endian */
        uint64_t et_prot               : 8;  /**< [  7:  0](R/W) Protocol number to definite the next layer of the packet is an inner Ethernet layer. */
        uint64_t reserved_8_15         : 8;
        uint64_t ipv4_prot             : 8;  /**< [ 23: 16](R/W) Protocol number to definite the next layer of the packet is an inner IPv4 layer. */
        uint64_t reserved_24_31        : 8;
        uint64_t ipv6_prot             : 8;  /**< [ 39: 32](R/W) Protocol number to definite the next layer of the packet is an inner IPv6 layer. */
        uint64_t reserved_40_59        : 20;
        uint64_t ena_prot              : 1;  /**< [ 60: 60](R/W) This enables protocol field checking inside the VXLAN header. */
        uint64_t ena_et                : 1;  /**< [ 61: 61](R/W) Enables the [ET_PROT] value ([ENA_PROT] must be also set). */
        uint64_t ena_ipv4              : 1;  /**< [ 62: 62](R/W) Enables the [IPV4_PROT] value ([ENA_PROT] must be also set). */
        uint64_t ena_ipv6              : 1;  /**< [ 63: 63](R/W) Enables the [IPV6_PROT] value ([ENA_PROT] must be also set). */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_rx_vxlan_prot_def_s cn; */
};
typedef union bdk_nic_pf_rx_vxlan_prot_def bdk_nic_pf_rx_vxlan_prot_def_t;

#define BDK_NIC_PF_RX_VXLAN_PROT_DEF BDK_NIC_PF_RX_VXLAN_PROT_DEF_FUNC()
static inline uint64_t BDK_NIC_PF_RX_VXLAN_PROT_DEF_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_RX_VXLAN_PROT_DEF_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x8430000005b0ll;
    __bdk_csr_fatal("NIC_PF_RX_VXLAN_PROT_DEF", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_RX_VXLAN_PROT_DEF bdk_nic_pf_rx_vxlan_prot_def_t
#define bustype_BDK_NIC_PF_RX_VXLAN_PROT_DEF BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_RX_VXLAN_PROT_DEF "NIC_PF_RX_VXLAN_PROT_DEF"
#define device_bar_BDK_NIC_PF_RX_VXLAN_PROT_DEF 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_RX_VXLAN_PROT_DEF 0
#define arguments_BDK_NIC_PF_RX_VXLAN_PROT_DEF -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_rx_wrr_cfg#
 *
 * NIC Receive Weighted Round Robin Configuration Registers
 */
union bdk_nic_pf_rx_wrr_cfgx
{
    uint64_t u;
    struct bdk_nic_pf_rx_wrr_cfgx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t slot15                : 4;  /**< [ 63: 60](R/W) See [SLOT0]. */
        uint64_t slot14                : 4;  /**< [ 59: 56](R/W) See [SLOT0]. */
        uint64_t slot13                : 4;  /**< [ 55: 52](R/W) See [SLOT0]. */
        uint64_t slot12                : 4;  /**< [ 51: 48](R/W) See [SLOT0]. */
        uint64_t slot11                : 4;  /**< [ 47: 44](R/W) See [SLOT0]. */
        uint64_t slot10                : 4;  /**< [ 43: 40](R/W) See [SLOT0]. */
        uint64_t slot9                 : 4;  /**< [ 39: 36](R/W) See [SLOT0]. */
        uint64_t slot8                 : 4;  /**< [ 35: 32](R/W) See [SLOT0]. */
        uint64_t slot7                 : 4;  /**< [ 31: 28](R/W) See [SLOT0]. */
        uint64_t slot6                 : 4;  /**< [ 27: 24](R/W) See [SLOT0]. */
        uint64_t slot5                 : 4;  /**< [ 23: 20](R/W) See [SLOT0]. */
        uint64_t slot4                 : 4;  /**< [ 19: 16](R/W) See [SLOT0]. */
        uint64_t slot3                 : 4;  /**< [ 15: 12](R/W) See [SLOT0]. */
        uint64_t slot2                 : 4;  /**< [ 11:  8](R/W) See [SLOT0]. */
        uint64_t slot1                 : 4;  /**< [  7:  4](R/W) See [SLOT0]. */
        uint64_t slot0                 : 4;  /**< [  3:  0](R/W) NIC RX supports a WRR prioritizing of traffic received from the different receive interfaces.
                                                                 when there is over subscription to the NCB drain.
                                                                 There are a total of 32 "slots" which can be assigned to favor an interface. If the
                                                                 slot does not match an active interface, then
                                                                 data is processed in a round-robin fashion. Default setting does not match any receive
                                                                 interface, so all slots default to RR arbitration.
                                                                 Enumerated by NIC_INTF_BLOCK_E.

                                                                 Internal:
                                                                 Specifies upper 4 bits of X2P channel ID. */
#else /* Word 0 - Little Endian */
        uint64_t slot0                 : 4;  /**< [  3:  0](R/W) NIC RX supports a WRR prioritizing of traffic received from the different receive interfaces.
                                                                 when there is over subscription to the NCB drain.
                                                                 There are a total of 32 "slots" which can be assigned to favor an interface. If the
                                                                 slot does not match an active interface, then
                                                                 data is processed in a round-robin fashion. Default setting does not match any receive
                                                                 interface, so all slots default to RR arbitration.
                                                                 Enumerated by NIC_INTF_BLOCK_E.

                                                                 Internal:
                                                                 Specifies upper 4 bits of X2P channel ID. */
        uint64_t slot1                 : 4;  /**< [  7:  4](R/W) See [SLOT0]. */
        uint64_t slot2                 : 4;  /**< [ 11:  8](R/W) See [SLOT0]. */
        uint64_t slot3                 : 4;  /**< [ 15: 12](R/W) See [SLOT0]. */
        uint64_t slot4                 : 4;  /**< [ 19: 16](R/W) See [SLOT0]. */
        uint64_t slot5                 : 4;  /**< [ 23: 20](R/W) See [SLOT0]. */
        uint64_t slot6                 : 4;  /**< [ 27: 24](R/W) See [SLOT0]. */
        uint64_t slot7                 : 4;  /**< [ 31: 28](R/W) See [SLOT0]. */
        uint64_t slot8                 : 4;  /**< [ 35: 32](R/W) See [SLOT0]. */
        uint64_t slot9                 : 4;  /**< [ 39: 36](R/W) See [SLOT0]. */
        uint64_t slot10                : 4;  /**< [ 43: 40](R/W) See [SLOT0]. */
        uint64_t slot11                : 4;  /**< [ 47: 44](R/W) See [SLOT0]. */
        uint64_t slot12                : 4;  /**< [ 51: 48](R/W) See [SLOT0]. */
        uint64_t slot13                : 4;  /**< [ 55: 52](R/W) See [SLOT0]. */
        uint64_t slot14                : 4;  /**< [ 59: 56](R/W) See [SLOT0]. */
        uint64_t slot15                : 4;  /**< [ 63: 60](R/W) See [SLOT0]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_rx_wrr_cfgx_s cn; */
};
typedef union bdk_nic_pf_rx_wrr_cfgx bdk_nic_pf_rx_wrr_cfgx_t;

static inline uint64_t BDK_NIC_PF_RX_WRR_CFGX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_RX_WRR_CFGX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=1))
        return 0x843000000180ll + 8ll * ((a) & 0x1);
    __bdk_csr_fatal("NIC_PF_RX_WRR_CFGX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_RX_WRR_CFGX(a) bdk_nic_pf_rx_wrr_cfgx_t
#define bustype_BDK_NIC_PF_RX_WRR_CFGX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_RX_WRR_CFGX(a) "NIC_PF_RX_WRR_CFGX"
#define device_bar_BDK_NIC_PF_RX_WRR_CFGX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_RX_WRR_CFGX(a) (a)
#define arguments_BDK_NIC_PF_RX_WRR_CFGX(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_seb_test
 *
 * INTERNAL: NIC SEB Test Register
 */
union bdk_nic_pf_seb_test
{
    uint64_t u;
    struct bdk_nic_pf_seb_test_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = seb_interface_1_stall.
                                                                 \<61\> = seb_interface_0_stall.
                                                                 \<60\> = seb_fifo_stall. */
        uint64_t reserved_25_59        : 35;
        uint64_t timeout_tick_test     : 1;  /**< [ 24: 24](R/W) Enable timeout testing. For diagnostic use only.
                                                                 Internal:
                                                                 Once the bit is set, it reduces the number of co-processor cycles from 1024
                                                                 cycles to 1 co-processor cycle corresponding to the
                                                                 NIC_PF_INTF()_SEND_CFG[TSTMP_WD_PERIOD]. */
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = bp_cfg3.
                                                                   \<21:20\> = bp_cfg2.
                                                                   \<19:18\> = bp_cfg1.
                                                                   \<17:16\> = bp_cfg0. */
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
                                                                   \<23:22\> = bp_cfg3.
                                                                   \<21:20\> = bp_cfg2.
                                                                   \<19:18\> = bp_cfg1.
                                                                   \<17:16\> = bp_cfg0. */
        uint64_t timeout_tick_test     : 1;  /**< [ 24: 24](R/W) Enable timeout testing. For diagnostic use only.
                                                                 Internal:
                                                                 Once the bit is set, it reduces the number of co-processor cycles from 1024
                                                                 cycles to 1 co-processor cycle corresponding to the
                                                                 NIC_PF_INTF()_SEND_CFG[TSTMP_WD_PERIOD]. */
        uint64_t reserved_25_59        : 35;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = seb_interface_1_stall.
                                                                 \<61\> = seb_interface_0_stall.
                                                                 \<60\> = seb_fifo_stall. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_seb_test_s cn; */
};
typedef union bdk_nic_pf_seb_test bdk_nic_pf_seb_test_t;

#define BDK_NIC_PF_SEB_TEST BDK_NIC_PF_SEB_TEST_FUNC()
static inline uint64_t BDK_NIC_PF_SEB_TEST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_SEB_TEST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x8430000000e0ll;
    __bdk_csr_fatal("NIC_PF_SEB_TEST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_SEB_TEST bdk_nic_pf_seb_test_t
#define bustype_BDK_NIC_PF_SEB_TEST BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_SEB_TEST "NIC_PF_SEB_TEST"
#define device_bar_BDK_NIC_PF_SEB_TEST 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_SEB_TEST 0
#define arguments_BDK_NIC_PF_SEB_TEST -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_send_cfg
 *
 * NIC Send Configuration Registers
 * Configures the NIC send side for all the interfaces enumerated by NIC_INTF_E.
 */
union bdk_nic_pf_send_cfg
{
    uint64_t u;
    struct bdk_nic_pf_send_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t cut_disable           : 1;  /**< [  0:  0](R/W) Send cut-through context disable. Used for debug, should be clear for normal operation. */
#else /* Word 0 - Little Endian */
        uint64_t cut_disable           : 1;  /**< [  0:  0](R/W) Send cut-through context disable. Used for debug, should be clear for normal operation. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_send_cfg_s cn; */
};
typedef union bdk_nic_pf_send_cfg bdk_nic_pf_send_cfg_t;

#define BDK_NIC_PF_SEND_CFG BDK_NIC_PF_SEND_CFG_FUNC()
static inline uint64_t BDK_NIC_PF_SEND_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_SEND_CFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000004800ll;
    __bdk_csr_fatal("NIC_PF_SEND_CFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_SEND_CFG bdk_nic_pf_send_cfg_t
#define bustype_BDK_NIC_PF_SEND_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_SEND_CFG "NIC_PF_SEND_CFG"
#define device_bar_BDK_NIC_PF_SEND_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_SEND_CFG 0
#define arguments_BDK_NIC_PF_SEND_CFG -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_soft_reset
 *
 * NIC Soft Reset Register
 */
union bdk_nic_pf_soft_reset
{
    uint64_t u;
    struct bdk_nic_pf_soft_reset_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t reset                 : 1;  /**< [  0:  0](WO) Write 1 to reset the NIC block. Software must ensure the following before writing 1:
                                                                 * NIC_PF_CFG[ENA] = 1.
                                                                 * All NIC queues (CQ, SQ, RQ, RBDR) are idle.
                                                                 * Transmit FIFO is empty, i.e. NIC_PF_TX_FIFO_STATUS[COUNT] = 0.
                                                                 * NIC send and receive interfaces are quiesced.
                                                                 * NIC has no outstanding interrupts.

                                                                 Note that this operation resets all NIC registers, including MSI-X registers
                                                                 (NIC_PF_MSIX_*, NIC_VF()_MSIX_*) and PCC config space registers (PCCBR_NIC_*, PCCPF_NIC_*,
                                                                 PCCVF_NIC_*). */
#else /* Word 0 - Little Endian */
        uint64_t reset                 : 1;  /**< [  0:  0](WO) Write 1 to reset the NIC block. Software must ensure the following before writing 1:
                                                                 * NIC_PF_CFG[ENA] = 1.
                                                                 * All NIC queues (CQ, SQ, RQ, RBDR) are idle.
                                                                 * Transmit FIFO is empty, i.e. NIC_PF_TX_FIFO_STATUS[COUNT] = 0.
                                                                 * NIC send and receive interfaces are quiesced.
                                                                 * NIC has no outstanding interrupts.

                                                                 Note that this operation resets all NIC registers, including MSI-X registers
                                                                 (NIC_PF_MSIX_*, NIC_VF()_MSIX_*) and PCC config space registers (PCCBR_NIC_*, PCCPF_NIC_*,
                                                                 PCCVF_NIC_*). */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_soft_reset_s cn; */
};
typedef union bdk_nic_pf_soft_reset bdk_nic_pf_soft_reset_t;

#define BDK_NIC_PF_SOFT_RESET BDK_NIC_PF_SOFT_RESET_FUNC()
static inline uint64_t BDK_NIC_PF_SOFT_RESET_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_SOFT_RESET_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000000050ll;
    __bdk_csr_fatal("NIC_PF_SOFT_RESET", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_SOFT_RESET bdk_nic_pf_soft_reset_t
#define bustype_BDK_NIC_PF_SOFT_RESET BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_SOFT_RESET "NIC_PF_SOFT_RESET"
#define device_bar_BDK_NIC_PF_SOFT_RESET 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_SOFT_RESET 0
#define arguments_BDK_NIC_PF_SOFT_RESET -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_sqm_test1
 *
 * INTERNAL: NIC SQM Test 1 Register
 */
union bdk_nic_pf_sqm_test1
{
    uint64_t u;
    struct bdk_nic_pf_sqm_test1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = sq_vnic_stat_stall.
                                                                 \<61\> = sq_door_stall.
                                                                 \<60\> = sq_int_set_fifo_stall. */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = bp_cfg3.
                                                                   \<21:20\> = bp_cfg2.
                                                                   \<19:18\> = bp_cfg1.
                                                                   \<17:16\> = bp_cfg0. */
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
                                                                   \<23:22\> = bp_cfg3.
                                                                   \<21:20\> = bp_cfg2.
                                                                   \<19:18\> = bp_cfg1.
                                                                   \<17:16\> = bp_cfg0. */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = sq_vnic_stat_stall.
                                                                 \<61\> = sq_door_stall.
                                                                 \<60\> = sq_int_set_fifo_stall. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_sqm_test1_s cn; */
};
typedef union bdk_nic_pf_sqm_test1 bdk_nic_pf_sqm_test1_t;

#define BDK_NIC_PF_SQM_TEST1 BDK_NIC_PF_SQM_TEST1_FUNC()
static inline uint64_t BDK_NIC_PF_SQM_TEST1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_SQM_TEST1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000000100ll;
    __bdk_csr_fatal("NIC_PF_SQM_TEST1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_SQM_TEST1 bdk_nic_pf_sqm_test1_t
#define bustype_BDK_NIC_PF_SQM_TEST1 BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_SQM_TEST1 "NIC_PF_SQM_TEST1"
#define device_bar_BDK_NIC_PF_SQM_TEST1 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_SQM_TEST1 0
#define arguments_BDK_NIC_PF_SQM_TEST1 -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_sqm_test2
 *
 * INTERNAL: NIC SQM Test 2 Register
 */
union bdk_nic_pf_sqm_test2
{
    uint64_t u;
    struct bdk_nic_pf_sqm_test2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = mqm_fill_ack_stall.
                                                                 \<62\> = mqm_send_cmd_stall.
                                                                 \<61\> = mqm_sch_req_stall.
                                                                 \<60\> = mqm_mdq_update_stall. */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = bp_cfg3.
                                                                   \<21:20\> = bp_cfg2.
                                                                   \<19:18\> = bp_cfg1.
                                                                   \<17:16\> = bp_cfg0. */
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
                                                                   \<23:22\> = bp_cfg3.
                                                                   \<21:20\> = bp_cfg2.
                                                                   \<19:18\> = bp_cfg1.
                                                                   \<17:16\> = bp_cfg0. */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = mqm_fill_ack_stall.
                                                                 \<62\> = mqm_send_cmd_stall.
                                                                 \<61\> = mqm_sch_req_stall.
                                                                 \<60\> = mqm_mdq_update_stall. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_sqm_test2_s cn; */
};
typedef union bdk_nic_pf_sqm_test2 bdk_nic_pf_sqm_test2_t;

#define BDK_NIC_PF_SQM_TEST2 BDK_NIC_PF_SQM_TEST2_FUNC()
static inline uint64_t BDK_NIC_PF_SQM_TEST2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_SQM_TEST2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000000108ll;
    __bdk_csr_fatal("NIC_PF_SQM_TEST2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_SQM_TEST2 bdk_nic_pf_sqm_test2_t
#define bustype_BDK_NIC_PF_SQM_TEST2 BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_SQM_TEST2 "NIC_PF_SQM_TEST2"
#define device_bar_BDK_NIC_PF_SQM_TEST2 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_SQM_TEST2 0
#define arguments_BDK_NIC_PF_SQM_TEST2 -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_status
 *
 * NIC General Status Register
 */
union bdk_nic_pf_status
{
    uint64_t u;
    struct bdk_nic_pf_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t blk_busy              : 10; /**< [  9:  0](RO/H) If nonzero, block is not ready for configuration.
                                                                 Internal:
                                                                 Each bit corresponds to a
                                                                 subblock:
                                                                 \<9\> = Reserved.
                                                                 \<8\> = Reserved.
                                                                 \<7\> = nic_sqm.
                                                                 \<6\> = nic_sps.
                                                                 \<5\> = nic_seb.
                                                                 \<4\> = nic_rrm.
                                                                 \<3\> = nic_rqm.
                                                                 \<2\> = nic_reb.
                                                                 \<1\> = nic_csi.
                                                                 \<0\> = nic_cqm. */
#else /* Word 0 - Little Endian */
        uint64_t blk_busy              : 10; /**< [  9:  0](RO/H) If nonzero, block is not ready for configuration.
                                                                 Internal:
                                                                 Each bit corresponds to a
                                                                 subblock:
                                                                 \<9\> = Reserved.
                                                                 \<8\> = Reserved.
                                                                 \<7\> = nic_sqm.
                                                                 \<6\> = nic_sps.
                                                                 \<5\> = nic_seb.
                                                                 \<4\> = nic_rrm.
                                                                 \<3\> = nic_rqm.
                                                                 \<2\> = nic_reb.
                                                                 \<1\> = nic_csi.
                                                                 \<0\> = nic_cqm. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_status_s cn; */
};
typedef union bdk_nic_pf_status bdk_nic_pf_status_t;

#define BDK_NIC_PF_STATUS BDK_NIC_PF_STATUS_FUNC()
static inline uint64_t BDK_NIC_PF_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_STATUS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000000010ll;
    __bdk_csr_fatal("NIC_PF_STATUS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_STATUS bdk_nic_pf_status_t
#define bustype_BDK_NIC_PF_STATUS BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_STATUS "NIC_PF_STATUS"
#define device_bar_BDK_NIC_PF_STATUS 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_STATUS 0
#define arguments_BDK_NIC_PF_STATUS -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_sw_sync_pipe#_cq_cnts
 *
 * INTERNAL: NIC Software Sync Pipline CQ Counter Registers
 *
 * For diagnostic use only for debug of the  NIC_PF_SW_SYNC_RX[SW_RX_SYNC] function. Index
 * enumerated by NIC_LMAC_E.
 */
union bdk_nic_pf_sw_sync_pipex_cq_cnts
{
    uint64_t u;
    struct bdk_nic_pf_sw_sync_pipex_cq_cnts_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t out_cnt               : 32; /**< [ 63: 32](RO/H) Running count at output of machine. */
        uint64_t in_cnt                : 32; /**< [ 31:  0](RO/H) Running count at input of machine. */
#else /* Word 0 - Little Endian */
        uint64_t in_cnt                : 32; /**< [ 31:  0](RO/H) Running count at input of machine. */
        uint64_t out_cnt               : 32; /**< [ 63: 32](RO/H) Running count at output of machine. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_sw_sync_pipex_cq_cnts_s cn; */
};
typedef union bdk_nic_pf_sw_sync_pipex_cq_cnts bdk_nic_pf_sw_sync_pipex_cq_cnts_t;

static inline uint64_t BDK_NIC_PF_SW_SYNC_PIPEX_CQ_CNTS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_SW_SYNC_PIPEX_CQ_CNTS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=9))
        return 0x843000490300ll + 8ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=17))
        return 0x843000490300ll + 8ll * ((a) & 0x1f);
    __bdk_csr_fatal("NIC_PF_SW_SYNC_PIPEX_CQ_CNTS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_SW_SYNC_PIPEX_CQ_CNTS(a) bdk_nic_pf_sw_sync_pipex_cq_cnts_t
#define bustype_BDK_NIC_PF_SW_SYNC_PIPEX_CQ_CNTS(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_SW_SYNC_PIPEX_CQ_CNTS(a) "NIC_PF_SW_SYNC_PIPEX_CQ_CNTS"
#define device_bar_BDK_NIC_PF_SW_SYNC_PIPEX_CQ_CNTS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_SW_SYNC_PIPEX_CQ_CNTS(a) (a)
#define arguments_BDK_NIC_PF_SW_SYNC_PIPEX_CQ_CNTS(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_sw_sync_pipe#_pkt_cnts
 *
 * INTERNAL: NIC Software Sync Pipeline Packet Counter Registers
 *
 * For diagnostic use only for debug of the  NIC_PF_SW_SYNC_RX[SW_RX_SYNC] function. Index
 * enumerated by NIC_LMAC_E.
 */
union bdk_nic_pf_sw_sync_pipex_pkt_cnts
{
    uint64_t u;
    struct bdk_nic_pf_sw_sync_pipex_pkt_cnts_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t out_cnt               : 32; /**< [ 63: 32](RO/H) Running count at output of machine. */
        uint64_t in_cnt                : 32; /**< [ 31:  0](RO/H) Running count at input of machine. */
#else /* Word 0 - Little Endian */
        uint64_t in_cnt                : 32; /**< [ 31:  0](RO/H) Running count at input of machine. */
        uint64_t out_cnt               : 32; /**< [ 63: 32](RO/H) Running count at output of machine. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_sw_sync_pipex_pkt_cnts_s cn; */
};
typedef union bdk_nic_pf_sw_sync_pipex_pkt_cnts bdk_nic_pf_sw_sync_pipex_pkt_cnts_t;

static inline uint64_t BDK_NIC_PF_SW_SYNC_PIPEX_PKT_CNTS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_SW_SYNC_PIPEX_PKT_CNTS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=9))
        return 0x843000490200ll + 8ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=17))
        return 0x843000490200ll + 8ll * ((a) & 0x1f);
    __bdk_csr_fatal("NIC_PF_SW_SYNC_PIPEX_PKT_CNTS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_SW_SYNC_PIPEX_PKT_CNTS(a) bdk_nic_pf_sw_sync_pipex_pkt_cnts_t
#define bustype_BDK_NIC_PF_SW_SYNC_PIPEX_PKT_CNTS(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_SW_SYNC_PIPEX_PKT_CNTS(a) "NIC_PF_SW_SYNC_PIPEX_PKT_CNTS"
#define device_bar_BDK_NIC_PF_SW_SYNC_PIPEX_PKT_CNTS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_SW_SYNC_PIPEX_PKT_CNTS(a) (a)
#define arguments_BDK_NIC_PF_SW_SYNC_PIPEX_PKT_CNTS(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_sw_sync_rx
 *
 * NIC Receive-Path Software Sync Register
 */
union bdk_nic_pf_sw_sync_rx
{
    uint64_t u;
    struct bdk_nic_pf_sw_sync_rx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t sw_rx_sync            : 1;  /**< [  0:  0](R/W) Software sets this bit to kick off a sync cycle on the RX path. This sync insures that all
                                                                 packets that were in flight are flushed out to memory. This can be used to assist in the
                                                                 tearing down of an active RQ. */
#else /* Word 0 - Little Endian */
        uint64_t sw_rx_sync            : 1;  /**< [  0:  0](R/W) Software sets this bit to kick off a sync cycle on the RX path. This sync insures that all
                                                                 packets that were in flight are flushed out to memory. This can be used to assist in the
                                                                 tearing down of an active RQ. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_sw_sync_rx_s cn; */
};
typedef union bdk_nic_pf_sw_sync_rx bdk_nic_pf_sw_sync_rx_t;

#define BDK_NIC_PF_SW_SYNC_RX BDK_NIC_PF_SW_SYNC_RX_FUNC()
static inline uint64_t BDK_NIC_PF_SW_SYNC_RX_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_SW_SYNC_RX_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000490000ll;
    __bdk_csr_fatal("NIC_PF_SW_SYNC_RX", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_SW_SYNC_RX bdk_nic_pf_sw_sync_rx_t
#define bustype_BDK_NIC_PF_SW_SYNC_RX BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_SW_SYNC_RX "NIC_PF_SW_SYNC_RX"
#define device_bar_BDK_NIC_PF_SW_SYNC_RX 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_SW_SYNC_RX 0
#define arguments_BDK_NIC_PF_SW_SYNC_RX -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_sw_sync_rx_done
 *
 * NIC Receive-Path Software Synchronization Register
 */
union bdk_nic_pf_sw_sync_rx_done
{
    uint64_t u;
    struct bdk_nic_pf_sw_sync_rx_done_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t sw_rx_sync_done       : 1;  /**< [  0:  0](RO/H) Set when NIC_PF_SW_SYNC_RX[SW_RX_SYNC] is set and all packets that were in flight before
                                                                 the sync has been flushed out to memory. */
#else /* Word 0 - Little Endian */
        uint64_t sw_rx_sync_done       : 1;  /**< [  0:  0](RO/H) Set when NIC_PF_SW_SYNC_RX[SW_RX_SYNC] is set and all packets that were in flight before
                                                                 the sync has been flushed out to memory. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_sw_sync_rx_done_s cn; */
};
typedef union bdk_nic_pf_sw_sync_rx_done bdk_nic_pf_sw_sync_rx_done_t;

#define BDK_NIC_PF_SW_SYNC_RX_DONE BDK_NIC_PF_SW_SYNC_RX_DONE_FUNC()
static inline uint64_t BDK_NIC_PF_SW_SYNC_RX_DONE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_SW_SYNC_RX_DONE_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000490008ll;
    __bdk_csr_fatal("NIC_PF_SW_SYNC_RX_DONE", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_SW_SYNC_RX_DONE bdk_nic_pf_sw_sync_rx_done_t
#define bustype_BDK_NIC_PF_SW_SYNC_RX_DONE BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_SW_SYNC_RX_DONE "NIC_PF_SW_SYNC_RX_DONE"
#define device_bar_BDK_NIC_PF_SW_SYNC_RX_DONE 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_SW_SYNC_RX_DONE 0
#define arguments_BDK_NIC_PF_SW_SYNC_RX_DONE -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_tcp_timer
 *
 * NIC TCP Timer Register
 */
union bdk_nic_pf_tcp_timer
{
    uint64_t u;
    struct bdk_nic_pf_tcp_timer_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ena                   : 1;  /**< [ 63: 63](R/W) TCP timer enable. When clear, [VF_COUNTER] and [DUR_COUNTER] are forced to 0 and timer
                                                                 events will not be posted. */
        uint64_t reserved_48_62        : 15;
        uint64_t duration              : 16; /**< [ 47: 32](R/W) Duration of the TCP timer as a multiple of 256 coprocessor-clock cycles. */
        uint64_t reserved_23_31        : 9;
        uint64_t vf_counter            : 7;  /**< [ 22: 16](RO/H) Periodic counter that increments by one whenever [DUR_COUNTER] wraps around. Enabled when
                                                                 [ENA] is set. */
        uint64_t dur_counter           : 16; /**< [ 15:  0](RO/H) Periodic counter that wraps around every [DURATION]*256 coprocessor-clock cycles. Enabled
                                                                 when [ENA] is set. */
#else /* Word 0 - Little Endian */
        uint64_t dur_counter           : 16; /**< [ 15:  0](RO/H) Periodic counter that wraps around every [DURATION]*256 coprocessor-clock cycles. Enabled
                                                                 when [ENA] is set. */
        uint64_t vf_counter            : 7;  /**< [ 22: 16](RO/H) Periodic counter that increments by one whenever [DUR_COUNTER] wraps around. Enabled when
                                                                 [ENA] is set. */
        uint64_t reserved_23_31        : 9;
        uint64_t duration              : 16; /**< [ 47: 32](R/W) Duration of the TCP timer as a multiple of 256 coprocessor-clock cycles. */
        uint64_t reserved_48_62        : 15;
        uint64_t ena                   : 1;  /**< [ 63: 63](R/W) TCP timer enable. When clear, [VF_COUNTER] and [DUR_COUNTER] are forced to 0 and timer
                                                                 events will not be posted. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_tcp_timer_s cn; */
};
typedef union bdk_nic_pf_tcp_timer bdk_nic_pf_tcp_timer_t;

#define BDK_NIC_PF_TCP_TIMER BDK_NIC_PF_TCP_TIMER_FUNC()
static inline uint64_t BDK_NIC_PF_TCP_TIMER_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_TCP_TIMER_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000000060ll;
    __bdk_csr_fatal("NIC_PF_TCP_TIMER", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_TCP_TIMER bdk_nic_pf_tcp_timer_t
#define bustype_BDK_NIC_PF_TCP_TIMER BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_TCP_TIMER "NIC_PF_TCP_TIMER"
#define device_bar_BDK_NIC_PF_TCP_TIMER 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_TCP_TIMER 0
#define arguments_BDK_NIC_PF_TCP_TIMER -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_tl2#_cfg
 *
 * NIC Traffic Limiter 2 Configuration Registers
 */
union bdk_nic_pf_tl2x_cfg
{
    uint64_t u;
    struct bdk_nic_pf_tl2x_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t rr_quantum            : 24; /**< [ 23:  0](R/W) Round-robin (DWRR) quantum. The weighted deficit round-robin quantum (24-bit unsigned
                                                                 integer). Specifies the amount of data to transmit in an arbitration round as a multiple
                                                                 of 4 bytes. The minimum value is MTU/4 + NIC_PF_LMAC()_CFG[ADJUST] (rounded up) when this
                                                                 transmit limiter is used; this is also the typical value for equal-weight arbitration. */
#else /* Word 0 - Little Endian */
        uint64_t rr_quantum            : 24; /**< [ 23:  0](R/W) Round-robin (DWRR) quantum. The weighted deficit round-robin quantum (24-bit unsigned
                                                                 integer). Specifies the amount of data to transmit in an arbitration round as a multiple
                                                                 of 4 bytes. The minimum value is MTU/4 + NIC_PF_LMAC()_CFG[ADJUST] (rounded up) when this
                                                                 transmit limiter is used; this is also the typical value for equal-weight arbitration. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_tl2x_cfg_s cn; */
};
typedef union bdk_nic_pf_tl2x_cfg bdk_nic_pf_tl2x_cfg_t;

static inline uint64_t BDK_NIC_PF_TL2X_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_TL2X_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=15))
        return 0x843000500000ll + 8ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x843000500000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("NIC_PF_TL2X_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_TL2X_CFG(a) bdk_nic_pf_tl2x_cfg_t
#define bustype_BDK_NIC_PF_TL2X_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_TL2X_CFG(a) "NIC_PF_TL2X_CFG"
#define device_bar_BDK_NIC_PF_TL2X_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_TL2X_CFG(a) (a)
#define arguments_BDK_NIC_PF_TL2X_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_tl2#_lmac
 *
 * NIC Traffic Limiter 2 LMAC Mapping Registers
 */
union bdk_nic_pf_tl2x_lmac
{
    uint64_t u;
    struct bdk_nic_pf_tl2x_lmac_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t lmac                  : 5;  /**< [  4:  0](R/W) The LMAC number to which this TL2 transmits. Enumerated by NIC_LMAC_E. */
#else /* Word 0 - Little Endian */
        uint64_t lmac                  : 5;  /**< [  4:  0](R/W) The LMAC number to which this TL2 transmits. Enumerated by NIC_LMAC_E. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_tl2x_lmac_s cn; */
};
typedef union bdk_nic_pf_tl2x_lmac bdk_nic_pf_tl2x_lmac_t;

static inline uint64_t BDK_NIC_PF_TL2X_LMAC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_TL2X_LMAC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=15))
        return 0x843000540000ll + 8ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x843000540000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("NIC_PF_TL2X_LMAC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_TL2X_LMAC(a) bdk_nic_pf_tl2x_lmac_t
#define bustype_BDK_NIC_PF_TL2X_LMAC(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_TL2X_LMAC(a) "NIC_PF_TL2X_LMAC"
#define device_bar_BDK_NIC_PF_TL2X_LMAC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_TL2X_LMAC(a) (a)
#define arguments_BDK_NIC_PF_TL2X_LMAC(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_tl2#_pri
 *
 * NIC Traffic Limiter 2 Priority Registers
 */
union bdk_nic_pf_tl2x_pri
{
    uint64_t u;
    struct bdk_nic_pf_tl2x_pri_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t rr_pri                : 4;  /**< [  3:  0](R/W) Round-robin priority. Zero is highest priority; values 10 and above are reserved. */
#else /* Word 0 - Little Endian */
        uint64_t rr_pri                : 4;  /**< [  3:  0](R/W) Round-robin priority. Zero is highest priority; values 10 and above are reserved. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_tl2x_pri_s cn; */
};
typedef union bdk_nic_pf_tl2x_pri bdk_nic_pf_tl2x_pri_t;

static inline uint64_t BDK_NIC_PF_TL2X_PRI(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_TL2X_PRI(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=15))
        return 0x843000520000ll + 8ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x843000520000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("NIC_PF_TL2X_PRI", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_TL2X_PRI(a) bdk_nic_pf_tl2x_pri_t
#define bustype_BDK_NIC_PF_TL2X_PRI(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_TL2X_PRI(a) "NIC_PF_TL2X_PRI"
#define device_bar_BDK_NIC_PF_TL2X_PRI(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_TL2X_PRI(a) (a)
#define arguments_BDK_NIC_PF_TL2X_PRI(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_tl2#_sh_status
 *
 * NIC Traffic Limiter 2 Shaper Status Registers
 */
union bdk_nic_pf_tl2x_sh_status
{
    uint64_t u;
    struct bdk_nic_pf_tl2x_sh_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_25_63        : 39;
        uint64_t rr_count              : 25; /**< [ 24:  0](R/W/H) Round-robin (DWRR) deficit counter. A 25-bit signed integer count. For diagnostic use. */
#else /* Word 0 - Little Endian */
        uint64_t rr_count              : 25; /**< [ 24:  0](R/W/H) Round-robin (DWRR) deficit counter. A 25-bit signed integer count. For diagnostic use. */
        uint64_t reserved_25_63        : 39;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_tl2x_sh_status_s cn; */
};
typedef union bdk_nic_pf_tl2x_sh_status bdk_nic_pf_tl2x_sh_status_t;

static inline uint64_t BDK_NIC_PF_TL2X_SH_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_TL2X_SH_STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=15))
        return 0x843000580000ll + 8ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x843000580000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("NIC_PF_TL2X_SH_STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_TL2X_SH_STATUS(a) bdk_nic_pf_tl2x_sh_status_t
#define bustype_BDK_NIC_PF_TL2X_SH_STATUS(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_TL2X_SH_STATUS(a) "NIC_PF_TL2X_SH_STATUS"
#define device_bar_BDK_NIC_PF_TL2X_SH_STATUS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_TL2X_SH_STATUS(a) (a)
#define arguments_BDK_NIC_PF_TL2X_SH_STATUS(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_tl3#_cfg
 *
 * NIC Traffic Limiter 3 Configuration Registers
 */
union bdk_nic_pf_tl3x_cfg
{
    uint64_t u;
    struct bdk_nic_pf_tl3x_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t rr_quantum            : 24; /**< [ 23:  0](R/W) Round-robin (DWRR) quantum. The weighted deficit round-robin quantum (24-bit unsigned
                                                                 integer). Specifies the amount of data to transmit in an arbitration round as a multiple
                                                                 of 4 bytes. The minimum value is MTU/4 + NIC_PF_LMAC()_CFG[ADJUST] (rounded up) when this
                                                                 transmit limiter is used; this is also the typical value for equal-weight arbitration. */
#else /* Word 0 - Little Endian */
        uint64_t rr_quantum            : 24; /**< [ 23:  0](R/W) Round-robin (DWRR) quantum. The weighted deficit round-robin quantum (24-bit unsigned
                                                                 integer). Specifies the amount of data to transmit in an arbitration round as a multiple
                                                                 of 4 bytes. The minimum value is MTU/4 + NIC_PF_LMAC()_CFG[ADJUST] (rounded up) when this
                                                                 transmit limiter is used; this is also the typical value for equal-weight arbitration. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_tl3x_cfg_s cn; */
};
typedef union bdk_nic_pf_tl3x_cfg bdk_nic_pf_tl3x_cfg_t;

static inline uint64_t BDK_NIC_PF_TL3X_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_TL3X_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=63))
        return 0x843000600000ll + 8ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=255))
        return 0x843000600000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("NIC_PF_TL3X_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_TL3X_CFG(a) bdk_nic_pf_tl3x_cfg_t
#define bustype_BDK_NIC_PF_TL3X_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_TL3X_CFG(a) "NIC_PF_TL3X_CFG"
#define device_bar_BDK_NIC_PF_TL3X_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_TL3X_CFG(a) (a)
#define arguments_BDK_NIC_PF_TL3X_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_tl3#_chan
 *
 * NIC Traffic Limiter 3 Channel Mapping Registers
 */
union bdk_nic_pf_tl3x_chan
{
    uint64_t u;
    struct bdk_nic_pf_tl3x_chan_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t chan                  : 7;  /**< [  6:  0](R/W) The channel-within-LMAC sending backpressure to this TL3. The LMAC is selected by
                                                                 NIC_PF_TL2()_LMAC[LMAC], indexed by the TL2 that pulls from this TL3 as selected by
                                                                 NIC_PF_TL3A()_CFG[TL3A].
                                                                 Must be less than 8 for a BGX LMAC or 24 for LBK. */
#else /* Word 0 - Little Endian */
        uint64_t chan                  : 7;  /**< [  6:  0](R/W) The channel-within-LMAC sending backpressure to this TL3. The LMAC is selected by
                                                                 NIC_PF_TL2()_LMAC[LMAC], indexed by the TL2 that pulls from this TL3 as selected by
                                                                 NIC_PF_TL3A()_CFG[TL3A].
                                                                 Must be less than 8 for a BGX LMAC or 24 for LBK. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_tl3x_chan_s cn8; */
    /* struct bdk_nic_pf_tl3x_chan_s cn81xx; */
    struct bdk_nic_pf_tl3x_chan_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t chan                  : 7;  /**< [  6:  0](R/W) The channel-within-LMAC sending backpressure to this TL3. The LMAC is selected by
                                                                 NIC_PF_TL2()_LMAC[LMAC], indexed by the TL2 that pulls from this TL3 as selected by
                                                                 NIC_PF_TL3A()_CFG[TL3A].
                                                                 Must be less than 8 for a BGX LMAC or 64 for LBK. */
#else /* Word 0 - Little Endian */
        uint64_t chan                  : 7;  /**< [  6:  0](R/W) The channel-within-LMAC sending backpressure to this TL3. The LMAC is selected by
                                                                 NIC_PF_TL2()_LMAC[LMAC], indexed by the TL2 that pulls from this TL3 as selected by
                                                                 NIC_PF_TL3A()_CFG[TL3A].
                                                                 Must be less than 8 for a BGX LMAC or 64 for LBK. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_pf_tl3x_chan bdk_nic_pf_tl3x_chan_t;

static inline uint64_t BDK_NIC_PF_TL3X_CHAN(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_TL3X_CHAN(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=63))
        return 0x843000620000ll + 8ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=255))
        return 0x843000620000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("NIC_PF_TL3X_CHAN", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_TL3X_CHAN(a) bdk_nic_pf_tl3x_chan_t
#define bustype_BDK_NIC_PF_TL3X_CHAN(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_TL3X_CHAN(a) "NIC_PF_TL3X_CHAN"
#define device_bar_BDK_NIC_PF_TL3X_CHAN(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_TL3X_CHAN(a) (a)
#define arguments_BDK_NIC_PF_TL3X_CHAN(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_tl3#_pir
 *
 * NIC Traffic Limiter 3 Peak Information Rate Registers
 */
union bdk_nic_pf_tl3x_pir
{
    uint64_t u;
    struct bdk_nic_pf_tl3x_pir_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t burst_exp             : 4;  /**< [ 39: 36](R/W) Burst exponent. The burst limit is specified as 1.[BURST_MANT] \<\< [BURST_EXP]. */
        uint64_t burst_mant            : 8;  /**< [ 35: 28](R/W) Burst mantissa. The burst limit is specified as 1.[BURST_MANT] \<\< [BURST_EXP]. */
        uint64_t reserved_17_27        : 11;
        uint64_t rate_div              : 4;  /**< [ 16: 13](R/W) Rate divider exponent. This 4-bit base-2 exponent is used to divide the credit rate by
                                                                 specifying the number of time-wheel turns required before the accumulator is increased.
                                                                 The rate count = (1 \<\< [RATE_DIV]). The supported range for [RATE_DIV] is 0 to 11.
                                                                 Programmed values greater than 11 are treated as 11. */
        uint64_t rate_exp              : 4;  /**< [ 12:  9](R/W) Rate exponent. The rate is specified as 1.[RATE_MANT] \<\< [RATE_EXP]. */
        uint64_t rate_mant             : 8;  /**< [  8:  1](R/W) Rate mantissa. The rate is specified as 1.[RATE_MANT] \<\< [RATE_EXP]. */
        uint64_t pir_ena               : 1;  /**< [  0:  0](R/W) Enable. Enables PIR shaping. */
#else /* Word 0 - Little Endian */
        uint64_t pir_ena               : 1;  /**< [  0:  0](R/W) Enable. Enables PIR shaping. */
        uint64_t rate_mant             : 8;  /**< [  8:  1](R/W) Rate mantissa. The rate is specified as 1.[RATE_MANT] \<\< [RATE_EXP]. */
        uint64_t rate_exp              : 4;  /**< [ 12:  9](R/W) Rate exponent. The rate is specified as 1.[RATE_MANT] \<\< [RATE_EXP]. */
        uint64_t rate_div              : 4;  /**< [ 16: 13](R/W) Rate divider exponent. This 4-bit base-2 exponent is used to divide the credit rate by
                                                                 specifying the number of time-wheel turns required before the accumulator is increased.
                                                                 The rate count = (1 \<\< [RATE_DIV]). The supported range for [RATE_DIV] is 0 to 11.
                                                                 Programmed values greater than 11 are treated as 11. */
        uint64_t reserved_17_27        : 11;
        uint64_t burst_mant            : 8;  /**< [ 35: 28](R/W) Burst mantissa. The burst limit is specified as 1.[BURST_MANT] \<\< [BURST_EXP]. */
        uint64_t burst_exp             : 4;  /**< [ 39: 36](R/W) Burst exponent. The burst limit is specified as 1.[BURST_MANT] \<\< [BURST_EXP]. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_tl3x_pir_s cn; */
};
typedef union bdk_nic_pf_tl3x_pir bdk_nic_pf_tl3x_pir_t;

static inline uint64_t BDK_NIC_PF_TL3X_PIR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_TL3X_PIR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=63))
        return 0x843000640000ll + 8ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=255))
        return 0x843000640000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("NIC_PF_TL3X_PIR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_TL3X_PIR(a) bdk_nic_pf_tl3x_pir_t
#define bustype_BDK_NIC_PF_TL3X_PIR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_TL3X_PIR(a) "NIC_PF_TL3X_PIR"
#define device_bar_BDK_NIC_PF_TL3X_PIR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_TL3X_PIR(a) (a)
#define arguments_BDK_NIC_PF_TL3X_PIR(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_tl3#_sh_status
 *
 * NIC Traffic Limiter 3 Shaper Status Registers
 */
union bdk_nic_pf_tl3x_sh_status
{
    uint64_t u;
    struct bdk_nic_pf_tl3x_sh_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_63           : 1;
        uint64_t pir_count             : 12; /**< [ 62: 51](R/W/H) Peak information rate tick count. This keeps track of the time-wheel turn for replenishing
                                                                 the PIR accumulator. */
        uint64_t pir_accum             : 26; /**< [ 50: 25](R/W/H) Peak information rate accumulator. Debug access to the live PIR accumulator. */
        uint64_t rr_count              : 25; /**< [ 24:  0](R/W/H) Round-robin (DWRR) deficit counter. A 25-bit signed integer count. For diagnostic use. */
#else /* Word 0 - Little Endian */
        uint64_t rr_count              : 25; /**< [ 24:  0](R/W/H) Round-robin (DWRR) deficit counter. A 25-bit signed integer count. For diagnostic use. */
        uint64_t pir_accum             : 26; /**< [ 50: 25](R/W/H) Peak information rate accumulator. Debug access to the live PIR accumulator. */
        uint64_t pir_count             : 12; /**< [ 62: 51](R/W/H) Peak information rate tick count. This keeps track of the time-wheel turn for replenishing
                                                                 the PIR accumulator. */
        uint64_t reserved_63           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_tl3x_sh_status_s cn; */
};
typedef union bdk_nic_pf_tl3x_sh_status bdk_nic_pf_tl3x_sh_status_t;

static inline uint64_t BDK_NIC_PF_TL3X_SH_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_TL3X_SH_STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=63))
        return 0x8430006a0000ll + 8ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=255))
        return 0x8430006a0000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("NIC_PF_TL3X_SH_STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_TL3X_SH_STATUS(a) bdk_nic_pf_tl3x_sh_status_t
#define bustype_BDK_NIC_PF_TL3X_SH_STATUS(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_TL3X_SH_STATUS(a) "NIC_PF_TL3X_SH_STATUS"
#define device_bar_BDK_NIC_PF_TL3X_SH_STATUS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_TL3X_SH_STATUS(a) (a)
#define arguments_BDK_NIC_PF_TL3X_SH_STATUS(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_tl3#_sw_xoff
 *
 * NIC Traffic Limiter 3 Software-Controlled XOFF Registers
 */
union bdk_nic_pf_tl3x_sw_xoff
{
    uint64_t u;
    struct bdk_nic_pf_tl3x_sw_xoff_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t ch_xoff               : 1;  /**< [  1:  1](RO/H) Channel XOFF. When set, this TL3 does not send traffic due to
                                                                 NIC_PF_CHAN()_SW_XOFF[SW_XOFF], channel backpressure, channel credits,
                                                                 NIC_PF_LMAC()_SW_XOFF[SW_XOFF], or LMAC backpressure. */
        uint64_t sw_xoff               : 1;  /**< [  0:  0](R/W) Software XOFF. When set, this TL3 does not send traffic. */
#else /* Word 0 - Little Endian */
        uint64_t sw_xoff               : 1;  /**< [  0:  0](R/W) Software XOFF. When set, this TL3 does not send traffic. */
        uint64_t ch_xoff               : 1;  /**< [  1:  1](RO/H) Channel XOFF. When set, this TL3 does not send traffic due to
                                                                 NIC_PF_CHAN()_SW_XOFF[SW_XOFF], channel backpressure, channel credits,
                                                                 NIC_PF_LMAC()_SW_XOFF[SW_XOFF], or LMAC backpressure. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_tl3x_sw_xoff_s cn; */
};
typedef union bdk_nic_pf_tl3x_sw_xoff bdk_nic_pf_tl3x_sw_xoff_t;

static inline uint64_t BDK_NIC_PF_TL3X_SW_XOFF(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_TL3X_SW_XOFF(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=63))
        return 0x843000660000ll + 8ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=255))
        return 0x843000660000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("NIC_PF_TL3X_SW_XOFF", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_TL3X_SW_XOFF(a) bdk_nic_pf_tl3x_sw_xoff_t
#define bustype_BDK_NIC_PF_TL3X_SW_XOFF(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_TL3X_SW_XOFF(a) "NIC_PF_TL3X_SW_XOFF"
#define device_bar_BDK_NIC_PF_TL3X_SW_XOFF(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_TL3X_SW_XOFF(a) (a)
#define arguments_BDK_NIC_PF_TL3X_SW_XOFF(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_tl3a#_cfg
 *
 * NIC Traffic Limiter 3 Aggregation Configuration Registers
 */
union bdk_nic_pf_tl3ax_cfg
{
    uint64_t u;
    struct bdk_nic_pf_tl3ax_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t tl3a                  : 6;  /**< [  5:  0](R/W) TL3 aggregation group. Index of TL2 that pulls from this TL3 group (TL3G), i.e. lowest
                                                                 numbered TL3G in this aggregation group. If this TL3G is not part of an aggregation group,
                                                                 TL3A must match the TL3G number (the index of this register). Resets to equal the index of
                                                                 this register. */
#else /* Word 0 - Little Endian */
        uint64_t tl3a                  : 6;  /**< [  5:  0](R/W) TL3 aggregation group. Index of TL2 that pulls from this TL3 group (TL3G), i.e. lowest
                                                                 numbered TL3G in this aggregation group. If this TL3G is not part of an aggregation group,
                                                                 TL3A must match the TL3G number (the index of this register). Resets to equal the index of
                                                                 this register. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_tl3ax_cfg_s cn8; */
    struct bdk_nic_pf_tl3ax_cfg_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t reserved_4_5          : 2;
        uint64_t tl3a                  : 4;  /**< [  3:  0](R/W) TL3 aggregation group. Index of TL2 that pulls from this TL3 group (TL3G), i.e. lowest
                                                                 numbered TL3G in this aggregation group. If this TL3G is not part of an aggregation group,
                                                                 TL3A must match the TL3G number (the index of this register). Resets to equal the index of
                                                                 this register. */
#else /* Word 0 - Little Endian */
        uint64_t tl3a                  : 4;  /**< [  3:  0](R/W) TL3 aggregation group. Index of TL2 that pulls from this TL3 group (TL3G), i.e. lowest
                                                                 numbered TL3G in this aggregation group. If this TL3G is not part of an aggregation group,
                                                                 TL3A must match the TL3G number (the index of this register). Resets to equal the index of
                                                                 this register. */
        uint64_t reserved_4_5          : 2;
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_nic_pf_tl3ax_cfg_s cn83xx; */
};
typedef union bdk_nic_pf_tl3ax_cfg bdk_nic_pf_tl3ax_cfg_t;

static inline uint64_t BDK_NIC_PF_TL3AX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_TL3AX_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=15))
        return 0x8430005f0000ll + 8ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x8430005f0000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("NIC_PF_TL3AX_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_TL3AX_CFG(a) bdk_nic_pf_tl3ax_cfg_t
#define bustype_BDK_NIC_PF_TL3AX_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_TL3AX_CFG(a) "NIC_PF_TL3AX_CFG"
#define device_bar_BDK_NIC_PF_TL3AX_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_TL3AX_CFG(a) (a)
#define arguments_BDK_NIC_PF_TL3AX_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_tl4#_cfg
 *
 * NIC Traffic Limiter 4 Configuration Registers
 */
union bdk_nic_pf_tl4x_cfg
{
    uint64_t u;
    struct bdk_nic_pf_tl4x_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t sq_qs                 : 5;  /**< [ 31: 27](R/W) The SQ's QS that are associated with this TL4. Must be less than 8. */
        uint64_t sq_idx                : 3;  /**< [ 26: 24](R/W) The SQ's index inside the QS which is associated with this TL4. */
        uint64_t reserved_0_23         : 24;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_23         : 24;
        uint64_t sq_idx                : 3;  /**< [ 26: 24](R/W) The SQ's index inside the QS which is associated with this TL4. */
        uint64_t sq_qs                 : 5;  /**< [ 31: 27](R/W) The SQ's QS that are associated with this TL4. Must be less than 8. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_tl4x_cfg_s cn8; */
    struct bdk_nic_pf_tl4x_cfg_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t reserved_30_31        : 2;
        uint64_t sq_qs                 : 3;  /**< [ 29: 27](R/W) The SQ's QS that are associated with this TL4. Must be less than 8. */
        uint64_t sq_idx                : 3;  /**< [ 26: 24](R/W) The SQ's index inside the QS which is associated with this TL4. */
        uint64_t reserved_0_23         : 24;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_23         : 24;
        uint64_t sq_idx                : 3;  /**< [ 26: 24](R/W) The SQ's index inside the QS which is associated with this TL4. */
        uint64_t sq_qs                 : 3;  /**< [ 29: 27](R/W) The SQ's QS that are associated with this TL4. Must be less than 8. */
        uint64_t reserved_30_31        : 2;
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn81xx;
    struct bdk_nic_pf_tl4x_cfg_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t sq_qs                 : 5;  /**< [ 31: 27](R/W) The SQ's QS that are associated with this TL4. Must be less than 32. */
        uint64_t sq_idx                : 3;  /**< [ 26: 24](R/W) The SQ's index inside the QS which is associated with this TL4. */
        uint64_t reserved_0_23         : 24;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_23         : 24;
        uint64_t sq_idx                : 3;  /**< [ 26: 24](R/W) The SQ's index inside the QS which is associated with this TL4. */
        uint64_t sq_qs                 : 5;  /**< [ 31: 27](R/W) The SQ's QS that are associated with this TL4. Must be less than 32. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_pf_tl4x_cfg bdk_nic_pf_tl4x_cfg_t;

static inline uint64_t BDK_NIC_PF_TL4X_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_TL4X_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=63))
        return 0x843000800000ll + 8ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=255))
        return 0x843000800000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("NIC_PF_TL4X_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_TL4X_CFG(a) bdk_nic_pf_tl4x_cfg_t
#define bustype_BDK_NIC_PF_TL4X_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_TL4X_CFG(a) "NIC_PF_TL4X_CFG"
#define device_bar_BDK_NIC_PF_TL4X_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_TL4X_CFG(a) (a)
#define arguments_BDK_NIC_PF_TL4X_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_tl4#_sw_xoff
 *
 * NIC Traffic Limiter 4 Software-Controlled XOFF Registers
 */
union bdk_nic_pf_tl4x_sw_xoff
{
    uint64_t u;
    struct bdk_nic_pf_tl4x_sw_xoff_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t sw_xoff               : 1;  /**< [  0:  0](R/W) Software XOFF. When set, this TL4 does not send traffic. */
#else /* Word 0 - Little Endian */
        uint64_t sw_xoff               : 1;  /**< [  0:  0](R/W) Software XOFF. When set, this TL4 does not send traffic. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_tl4x_sw_xoff_s cn; */
};
typedef union bdk_nic_pf_tl4x_sw_xoff bdk_nic_pf_tl4x_sw_xoff_t;

static inline uint64_t BDK_NIC_PF_TL4X_SW_XOFF(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_TL4X_SW_XOFF(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=63))
        return 0x843000820000ll + 8ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=255))
        return 0x843000820000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("NIC_PF_TL4X_SW_XOFF", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_TL4X_SW_XOFF(a) bdk_nic_pf_tl4x_sw_xoff_t
#define bustype_BDK_NIC_PF_TL4X_SW_XOFF(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_TL4X_SW_XOFF(a) "NIC_PF_TL4X_SW_XOFF"
#define device_bar_BDK_NIC_PF_TL4X_SW_XOFF(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_TL4X_SW_XOFF(a) (a)
#define arguments_BDK_NIC_PF_TL4X_SW_XOFF(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_tso_cfg
 *
 * NIC TCP Segmentation Offload Configuration Register
 */
union bdk_nic_pf_tso_cfg
{
    uint64_t u;
    struct bdk_nic_pf_tso_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 1;  /**< [ 63: 63](R/W) TCP segmentation offload enable. When clear, NIC ignores NIC_SEND_HDR_S[TSO] and treats
                                                                 all send descriptors as non-TSO. */
        uint64_t crc_enable            : 1;  /**< [ 62: 62](R/W) Enable NIC_SEND_CRC_S with TSO. When clear, NIC ignores NIC_SEND_CRC_S subdescriptors in a
                                                                 send descriptor with NIC_SEND_HDR_S[TSO]=1. */
        uint64_t reserved_44_61        : 18;
        uint64_t fsf                   : 12; /**< [ 43: 32](R/W) Modify the TCP header flags for the first TSO segmented packet by logical AND
                                                                 with this configuration.

                                                                 _ FLAGS_new = (FLAGS_original) AND [FSF]. */
        uint64_t reserved_28_31        : 4;
        uint64_t msf                   : 12; /**< [ 27: 16](R/W) Modify the TCP header flags for the middle TSO segmented packets by logical AND
                                                                 with this configuration.

                                                                 _ FLAGS_new = (FLAGS_original) AND [MSF]. */
        uint64_t reserved_12_15        : 4;
        uint64_t lsf                   : 12; /**< [ 11:  0](R/W) Modify the TCP header flags for the last TSO segmented packet by logical AND
                                                                 with this configuration.

                                                                 _ FLAGS_new = (FLAGS_original) AND [LSF]. */
#else /* Word 0 - Little Endian */
        uint64_t lsf                   : 12; /**< [ 11:  0](R/W) Modify the TCP header flags for the last TSO segmented packet by logical AND
                                                                 with this configuration.

                                                                 _ FLAGS_new = (FLAGS_original) AND [LSF]. */
        uint64_t reserved_12_15        : 4;
        uint64_t msf                   : 12; /**< [ 27: 16](R/W) Modify the TCP header flags for the middle TSO segmented packets by logical AND
                                                                 with this configuration.

                                                                 _ FLAGS_new = (FLAGS_original) AND [MSF]. */
        uint64_t reserved_28_31        : 4;
        uint64_t fsf                   : 12; /**< [ 43: 32](R/W) Modify the TCP header flags for the first TSO segmented packet by logical AND
                                                                 with this configuration.

                                                                 _ FLAGS_new = (FLAGS_original) AND [FSF]. */
        uint64_t reserved_44_61        : 18;
        uint64_t crc_enable            : 1;  /**< [ 62: 62](R/W) Enable NIC_SEND_CRC_S with TSO. When clear, NIC ignores NIC_SEND_CRC_S subdescriptors in a
                                                                 send descriptor with NIC_SEND_HDR_S[TSO]=1. */
        uint64_t enable                : 1;  /**< [ 63: 63](R/W) TCP segmentation offload enable. When clear, NIC ignores NIC_SEND_HDR_S[TSO] and treats
                                                                 all send descriptors as non-TSO. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_tso_cfg_s cn; */
};
typedef union bdk_nic_pf_tso_cfg bdk_nic_pf_tso_cfg_t;

#define BDK_NIC_PF_TSO_CFG BDK_NIC_PF_TSO_CFG_FUNC()
static inline uint64_t BDK_NIC_PF_TSO_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_TSO_CFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000000070ll;
    __bdk_csr_fatal("NIC_PF_TSO_CFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_TSO_CFG bdk_nic_pf_tso_cfg_t
#define bustype_BDK_NIC_PF_TSO_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_TSO_CFG "NIC_PF_TSO_CFG"
#define device_bar_BDK_NIC_PF_TSO_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_TSO_CFG 0
#define arguments_BDK_NIC_PF_TSO_CFG -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_tx_fifo_status
 *
 * NIC Interface Transmit FIFO Status Register
 */
union bdk_nic_pf_tx_fifo_status
{
    uint64_t u;
    struct bdk_nic_pf_tx_fifo_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t count                 : 11; /**< [ 10:  0](RO/H) Number of 128-bit entries in the TX FIFO. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 11; /**< [ 10:  0](RO/H) Number of 128-bit entries in the TX FIFO. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_tx_fifo_status_s cn; */
};
typedef union bdk_nic_pf_tx_fifo_status bdk_nic_pf_tx_fifo_status_t;

#define BDK_NIC_PF_TX_FIFO_STATUS BDK_NIC_PF_TX_FIFO_STATUS_FUNC()
static inline uint64_t BDK_NIC_PF_TX_FIFO_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_TX_FIFO_STATUS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x843000000700ll;
    __bdk_csr_fatal("NIC_PF_TX_FIFO_STATUS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_TX_FIFO_STATUS bdk_nic_pf_tx_fifo_status_t
#define bustype_BDK_NIC_PF_TX_FIFO_STATUS BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_TX_FIFO_STATUS "NIC_PF_TX_FIFO_STATUS"
#define device_bar_BDK_NIC_PF_TX_FIFO_STATUS 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_TX_FIFO_STATUS 0
#define arguments_BDK_NIC_PF_TX_FIFO_STATUS -1,-1,-1,-1

/**
 * Register (NCB) nic_pf_tx_lbk#_fifo_credit
 *
 * NIC Transmit LBK FIFO Credit Count Register
 */
union bdk_nic_pf_tx_lbkx_fifo_credit
{
    uint64_t u;
    struct bdk_nic_pf_tx_lbkx_fifo_credit_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t credit_cnt            : 10; /**< [  9:  0](R/W/H) Number of 128-bit entry LBK FIFO credits. This represents the maximum number of available
                                                                 credits per LBK interface. It is decremented towards zero as credits are used up. Packets
                                                                 are not allowed to flow, if the count value is equal to zero and a packet is scheduled to
                                                                 this interface. Note: This can be programmed to a maximum of 768 entries. */
#else /* Word 0 - Little Endian */
        uint64_t credit_cnt            : 10; /**< [  9:  0](R/W/H) Number of 128-bit entry LBK FIFO credits. This represents the maximum number of available
                                                                 credits per LBK interface. It is decremented towards zero as credits are used up. Packets
                                                                 are not allowed to flow, if the count value is equal to zero and a packet is scheduled to
                                                                 this interface. Note: This can be programmed to a maximum of 768 entries. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_tx_lbkx_fifo_credit_s cn; */
};
typedef union bdk_nic_pf_tx_lbkx_fifo_credit bdk_nic_pf_tx_lbkx_fifo_credit_t;

static inline uint64_t BDK_NIC_PF_TX_LBKX_FIFO_CREDIT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_TX_LBKX_FIFO_CREDIT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1))
        return 0x843000000710ll + 8ll * ((a) & 0x1);
    __bdk_csr_fatal("NIC_PF_TX_LBKX_FIFO_CREDIT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_TX_LBKX_FIFO_CREDIT(a) bdk_nic_pf_tx_lbkx_fifo_credit_t
#define bustype_BDK_NIC_PF_TX_LBKX_FIFO_CREDIT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_TX_LBKX_FIFO_CREDIT(a) "NIC_PF_TX_LBKX_FIFO_CREDIT"
#define device_bar_BDK_NIC_PF_TX_LBKX_FIFO_CREDIT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_TX_LBKX_FIFO_CREDIT(a) (a)
#define arguments_BDK_NIC_PF_TX_LBKX_FIFO_CREDIT(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_pf_vf#_mbox#
 *
 * NIC PF/VF Mailbox Registers
 */
union bdk_nic_pf_vfx_mboxx
{
    uint64_t u;
    struct bdk_nic_pf_vfx_mboxx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Mailbox data. These PF registers access the 16-byte-per-VF VF/PF mailbox
                                                                 RAM. Each corresponding VF may access the same storage using
                                                                 NIC_VF()_PF_MBOX(). MBOX(0) is typically used for PF to VF signaling, MBOX(1)
                                                                 for VF to PF. Writing NIC_PF_VF()_MBOX(0) (but not
                                                                 NIC_VF()_PF_MBOX(0)) will set the corresponding NIC_VF()_INT[MBOX] which
                                                                 if appropriately enabled will send an interrupt to the VF. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Mailbox data. These PF registers access the 16-byte-per-VF VF/PF mailbox
                                                                 RAM. Each corresponding VF may access the same storage using
                                                                 NIC_VF()_PF_MBOX(). MBOX(0) is typically used for PF to VF signaling, MBOX(1)
                                                                 for VF to PF. Writing NIC_PF_VF()_MBOX(0) (but not
                                                                 NIC_VF()_PF_MBOX(0)) will set the corresponding NIC_VF()_INT[MBOX] which
                                                                 if appropriately enabled will send an interrupt to the VF. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_vfx_mboxx_s cn; */
};
typedef union bdk_nic_pf_vfx_mboxx bdk_nic_pf_vfx_mboxx_t;

static inline uint64_t BDK_NIC_PF_VFX_MBOXX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_VFX_MBOXX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=1)))
        return 0x843020002030ll + 0x200000ll * ((a) & 0x7) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=1)))
        return 0x843020002030ll + 0x200000ll * ((a) & 0x1f) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("NIC_PF_VFX_MBOXX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_VFX_MBOXX(a,b) bdk_nic_pf_vfx_mboxx_t
#define bustype_BDK_NIC_PF_VFX_MBOXX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_VFX_MBOXX(a,b) "NIC_PF_VFX_MBOXX"
#define device_bar_BDK_NIC_PF_VFX_MBOXX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_VFX_MBOXX(a,b) (a)
#define arguments_BDK_NIC_PF_VFX_MBOXX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_pf_vnic#_rx_stat#
 *
 * NIC PF VNIC Receive Statistics Registers
 * The second dimension indicates which statistic, and is enumerated by NIC_STAT_VNIC_RX_E.
 */
union bdk_nic_pf_vnicx_rx_statx
{
    uint64_t u;
    struct bdk_nic_pf_vnicx_rx_statx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) Statistic value. See also NIC_VNIC()_RX_STAT() for a read-only alias of this field. */
#else /* Word 0 - Little Endian */
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) Statistic value. See also NIC_VNIC()_RX_STAT() for a read-only alias of this field. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_vnicx_rx_statx_s cn; */
};
typedef union bdk_nic_pf_vnicx_rx_statx bdk_nic_pf_vnicx_rx_statx_t;

static inline uint64_t BDK_NIC_PF_VNICX_RX_STATX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_VNICX_RX_STATX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=13)))
        return 0x843020004100ll + 0x200000ll * ((a) & 0x7) + 8ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=13)))
        return 0x843020004100ll + 0x200000ll * ((a) & 0x1f) + 8ll * ((b) & 0xf);
    __bdk_csr_fatal("NIC_PF_VNICX_RX_STATX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_VNICX_RX_STATX(a,b) bdk_nic_pf_vnicx_rx_statx_t
#define bustype_BDK_NIC_PF_VNICX_RX_STATX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_VNICX_RX_STATX(a,b) "NIC_PF_VNICX_RX_STATX"
#define device_bar_BDK_NIC_PF_VNICX_RX_STATX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_VNICX_RX_STATX(a,b) (a)
#define arguments_BDK_NIC_PF_VNICX_RX_STATX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_pf_vnic#_tx_stat#
 *
 * NIC PF VNIC Transmit Statistics Registers
 * The second dimension indicates which statistic, and is enumerated by NIC_STAT_VNIC_TX_E.
 */
union bdk_nic_pf_vnicx_tx_statx
{
    uint64_t u;
    struct bdk_nic_pf_vnicx_tx_statx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) Statistic value. See also NIC_VNIC()_TX_STAT() for a read-only alias of this field. */
#else /* Word 0 - Little Endian */
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) Statistic value. See also NIC_VNIC()_TX_STAT() for a read-only alias of this field. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_pf_vnicx_tx_statx_s cn; */
};
typedef union bdk_nic_pf_vnicx_tx_statx bdk_nic_pf_vnicx_tx_statx_t;

static inline uint64_t BDK_NIC_PF_VNICX_TX_STATX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_PF_VNICX_TX_STATX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=4)))
        return 0x843020004000ll + 0x200000ll * ((a) & 0x7) + 8ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=4)))
        return 0x843020004000ll + 0x200000ll * ((a) & 0x1f) + 8ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_PF_VNICX_TX_STATX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_PF_VNICX_TX_STATX(a,b) bdk_nic_pf_vnicx_tx_statx_t
#define bustype_BDK_NIC_PF_VNICX_TX_STATX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_PF_VNICX_TX_STATX(a,b) "NIC_PF_VNICX_TX_STATX"
#define device_bar_BDK_NIC_PF_VNICX_TX_STATX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_NIC_PF_VNICX_TX_STATX(a,b) (a)
#define arguments_BDK_NIC_PF_VNICX_TX_STATX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_cq#_base
 *
 * NIC Completion-Queue Base-Address Registers
 */
union bdk_nic_qsx_cqx_base
{
    uint64_t u;
    struct bdk_nic_qsx_cqx_base_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t base_addr             : 40; /**< [ 48:  9](R/W) Base IOVA \<48:9\> of CQ ring in DRAM (VA, IPA or PA depending on SMMU
                                                                 configuration). Address bits \<8:0\> are always 0. Writes are ignored when the CQ ring is
                                                                 enabled, i.e. NIC_QS()_CQ()_CFG[ENA]==1. */
        uint64_t reserved_0_8          : 9;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_8          : 9;
        uint64_t base_addr             : 40; /**< [ 48:  9](R/W) Base IOVA \<48:9\> of CQ ring in DRAM (VA, IPA or PA depending on SMMU
                                                                 configuration). Address bits \<8:0\> are always 0. Writes are ignored when the CQ ring is
                                                                 enabled, i.e. NIC_QS()_CQ()_CFG[ENA]==1. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_cqx_base_s cn; */
};
typedef union bdk_nic_qsx_cqx_base bdk_nic_qsx_cqx_base_t;

static inline uint64_t BDK_NIC_QSX_CQX_BASE(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_CQX_BASE(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x8430a0010420ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x8430a0010420ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_QSX_CQX_BASE", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_CQX_BASE(a,b) bdk_nic_qsx_cqx_base_t
#define bustype_BDK_NIC_QSX_CQX_BASE(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_CQX_BASE(a,b) "NIC_QSX_CQX_BASE"
#define device_bar_BDK_NIC_QSX_CQX_BASE(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_CQX_BASE(a,b) (a)
#define arguments_BDK_NIC_QSX_CQX_BASE(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_cq#_cfg
 *
 * NIC Completion-Queue Configuration Registers
 * Writes to all fields except for [ENA] are ignored when the CQ ring is enabled, i.e. [ENA]==1.
 */
union bdk_nic_qsx_cqx_cfg
{
    uint64_t u;
    struct bdk_nic_qsx_cqx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_43_63        : 21;
        uint64_t ena                   : 1;  /**< [ 42: 42](R/W/H) Enable CQ. Writing a 1 to this bit enables the CQ. Writing a 0 gracefully disables the CQ.
                                                                 Software can poll this bit for a 0 to determine if all hardware processing for this CQ has
                                                                 stopped. */
        uint64_t reset                 : 1;  /**< [ 41: 41](WO) CQ reset. Writing a 1 resets all the NIC_QS()_CQ()_* registers and internal
                                                                 state for this CQ with the exception of NIC_QS()_CQ()_CFG2. */
        uint64_t caching               : 1;  /**< [ 40: 40](R/W) Select the style of write to the L2C.
                                                                 0 = writes of CQE data will not allocate into the L2C.
                                                                 1 = writes of CQE data are allocated into the L2C. */
        uint64_t reserved_35_39        : 5;
        uint64_t qsize                 : 3;  /**< [ 34: 32](R/W) Specifies CQ ring size in entries of 512 bytes:
                                                                 0x0 = 1K entries.
                                                                 0x1 = 2K entries.
                                                                 0x2 = 4K entries.
                                                                 0x3 = 8K entries.
                                                                 0x4 = 16K entries.
                                                                 0x5 = 32K entries.
                                                                 0x6 = 64K entries.
                                                                 0x7 = 256 entries.

                                                                 Note that the usable size of the ring is the specified size minus 1 (HEAD==TAIL always
                                                                 means empty).

                                                                 The value 0x7 (256 entries) is only supported when the following conditions are met:
                                                                 * There are no SQs that feed the CQ.
                                                                 * All RQs that feed the CQ receive packets from a single LMAC.
                                                                 * NIC_PF_CQM_CFG[DROP_LEVEL] = 0x80. */
        uint64_t reserved_25_31        : 7;
        uint64_t avg_con               : 9;  /**< [ 24: 16](R/W) This value controls how much of each present average resource level is used to calculate
                                                                 the new resource level. The value is a number from 0 to 256, which represents
                                                                 [AVG_CON]/256
                                                                 of the average resource level that will be used in the calculation:

                                                                 next_LEVEL = ([AVG_CON]/256) * prev_LEVEL + (1-([AVG_CON]/256)) * count

                                                                 Note setting this value to zero will disable averaging, and always use the most immediate
                                                                 levels. NIC_PF_CQ_AVG_CFG[AVG_EN] must be set and NIC_PF_CQ_AVG_CFG[LVL_DLY] must be
                                                                 nonzero to globally enable averaging. NIC_PF_CQ_AVG_CFG[AVG_DLY] controls the periodicity
                                                                 of the level calculations. */
        uint64_t reserved_0_15         : 16;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_15         : 16;
        uint64_t avg_con               : 9;  /**< [ 24: 16](R/W) This value controls how much of each present average resource level is used to calculate
                                                                 the new resource level. The value is a number from 0 to 256, which represents
                                                                 [AVG_CON]/256
                                                                 of the average resource level that will be used in the calculation:

                                                                 next_LEVEL = ([AVG_CON]/256) * prev_LEVEL + (1-([AVG_CON]/256)) * count

                                                                 Note setting this value to zero will disable averaging, and always use the most immediate
                                                                 levels. NIC_PF_CQ_AVG_CFG[AVG_EN] must be set and NIC_PF_CQ_AVG_CFG[LVL_DLY] must be
                                                                 nonzero to globally enable averaging. NIC_PF_CQ_AVG_CFG[AVG_DLY] controls the periodicity
                                                                 of the level calculations. */
        uint64_t reserved_25_31        : 7;
        uint64_t qsize                 : 3;  /**< [ 34: 32](R/W) Specifies CQ ring size in entries of 512 bytes:
                                                                 0x0 = 1K entries.
                                                                 0x1 = 2K entries.
                                                                 0x2 = 4K entries.
                                                                 0x3 = 8K entries.
                                                                 0x4 = 16K entries.
                                                                 0x5 = 32K entries.
                                                                 0x6 = 64K entries.
                                                                 0x7 = 256 entries.

                                                                 Note that the usable size of the ring is the specified size minus 1 (HEAD==TAIL always
                                                                 means empty).

                                                                 The value 0x7 (256 entries) is only supported when the following conditions are met:
                                                                 * There are no SQs that feed the CQ.
                                                                 * All RQs that feed the CQ receive packets from a single LMAC.
                                                                 * NIC_PF_CQM_CFG[DROP_LEVEL] = 0x80. */
        uint64_t reserved_35_39        : 5;
        uint64_t caching               : 1;  /**< [ 40: 40](R/W) Select the style of write to the L2C.
                                                                 0 = writes of CQE data will not allocate into the L2C.
                                                                 1 = writes of CQE data are allocated into the L2C. */
        uint64_t reset                 : 1;  /**< [ 41: 41](WO) CQ reset. Writing a 1 resets all the NIC_QS()_CQ()_* registers and internal
                                                                 state for this CQ with the exception of NIC_QS()_CQ()_CFG2. */
        uint64_t ena                   : 1;  /**< [ 42: 42](R/W/H) Enable CQ. Writing a 1 to this bit enables the CQ. Writing a 0 gracefully disables the CQ.
                                                                 Software can poll this bit for a 0 to determine if all hardware processing for this CQ has
                                                                 stopped. */
        uint64_t reserved_43_63        : 21;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_cqx_cfg_s cn; */
};
typedef union bdk_nic_qsx_cqx_cfg bdk_nic_qsx_cqx_cfg_t;

static inline uint64_t BDK_NIC_QSX_CQX_CFG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_CQX_CFG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x8430a0010400ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x8430a0010400ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_QSX_CQX_CFG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_CQX_CFG(a,b) bdk_nic_qsx_cqx_cfg_t
#define bustype_BDK_NIC_QSX_CQX_CFG(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_CQX_CFG(a,b) "NIC_QSX_CQX_CFG"
#define device_bar_BDK_NIC_QSX_CQX_CFG(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_CQX_CFG(a,b) (a)
#define arguments_BDK_NIC_QSX_CQX_CFG(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_cq#_cfg2
 *
 * NIC Completion-Queue Configuration Registers
 */
union bdk_nic_qsx_cqx_cfg2
{
    uint64_t u;
    struct bdk_nic_qsx_cqx_cfg2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t int_timer_thr         : 8;  /**< [  7:  0](R/W) CQ interrupt timer threshold. Zero disables the interrupt timer
                                                                 This is not reset by NIC_QS()_CQ()_CFG[RESET].
                                                                 It is up to software write zero to this field to disable the interrupt timer before
                                                                 reseting the CQ. */
#else /* Word 0 - Little Endian */
        uint64_t int_timer_thr         : 8;  /**< [  7:  0](R/W) CQ interrupt timer threshold. Zero disables the interrupt timer
                                                                 This is not reset by NIC_QS()_CQ()_CFG[RESET].
                                                                 It is up to software write zero to this field to disable the interrupt timer before
                                                                 reseting the CQ. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_cqx_cfg2_s cn; */
};
typedef union bdk_nic_qsx_cqx_cfg2 bdk_nic_qsx_cqx_cfg2_t;

static inline uint64_t BDK_NIC_QSX_CQX_CFG2(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_CQX_CFG2(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x8430a0010408ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x8430a0010408ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_QSX_CQX_CFG2", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_CQX_CFG2(a,b) bdk_nic_qsx_cqx_cfg2_t
#define bustype_BDK_NIC_QSX_CQX_CFG2(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_CQX_CFG2(a,b) "NIC_QSX_CQX_CFG2"
#define device_bar_BDK_NIC_QSX_CQX_CFG2(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_CQX_CFG2(a,b) (a)
#define arguments_BDK_NIC_QSX_CQX_CFG2(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_cq#_debug
 *
 * NIC Completion-Queue Debug-Status Registers
 */
union bdk_nic_qsx_cqx_debug
{
    uint64_t u;
    struct bdk_nic_qsx_cqx_debug_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t tail_ptr              : 16; /**< [ 15:  0](R/W/H) CQ-engine pointer. Initialized to NIC_QS()_CQ()_TAIL[TAIL_PTR] when software
                                                                 writes that register. Advanced by hardware as completion messages are allocated. For
                                                                 diagnostic use only. Writes are ignored when NIC_PF_CFG[TEST_MODE] is clear. */
#else /* Word 0 - Little Endian */
        uint64_t tail_ptr              : 16; /**< [ 15:  0](R/W/H) CQ-engine pointer. Initialized to NIC_QS()_CQ()_TAIL[TAIL_PTR] when software
                                                                 writes that register. Advanced by hardware as completion messages are allocated. For
                                                                 diagnostic use only. Writes are ignored when NIC_PF_CFG[TEST_MODE] is clear. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_cqx_debug_s cn; */
};
typedef union bdk_nic_qsx_cqx_debug bdk_nic_qsx_cqx_debug_t;

static inline uint64_t BDK_NIC_QSX_CQX_DEBUG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_CQX_DEBUG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x8430a0010450ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x8430a0010450ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_QSX_CQX_DEBUG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_CQX_DEBUG(a,b) bdk_nic_qsx_cqx_debug_t
#define bustype_BDK_NIC_QSX_CQX_DEBUG(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_CQX_DEBUG(a,b) "NIC_QSX_CQX_DEBUG"
#define device_bar_BDK_NIC_QSX_CQX_DEBUG(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_CQX_DEBUG(a,b) (a)
#define arguments_BDK_NIC_QSX_CQX_DEBUG(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_cq#_door
 *
 * NIC Completion-Queue Doorbell Registers
 * Software writes to this register to notify hardware that one or more entries have been
 * dequeued from the CQ ring.
 */
union bdk_nic_qsx_cqx_door
{
    uint64_t u;
    struct bdk_nic_qsx_cqx_door_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t count                 : 16; /**< [ 15:  0](WO) Number of dequeued entries of 512 bytes. Hardware advances NIC_QS()_CQ()_HEAD[HEAD_PTR] by
                                                                 this value if the CQ is enabled. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 16; /**< [ 15:  0](WO) Number of dequeued entries of 512 bytes. Hardware advances NIC_QS()_CQ()_HEAD[HEAD_PTR] by
                                                                 this value if the CQ is enabled. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_cqx_door_s cn; */
};
typedef union bdk_nic_qsx_cqx_door bdk_nic_qsx_cqx_door_t;

static inline uint64_t BDK_NIC_QSX_CQX_DOOR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_CQX_DOOR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x8430a0010438ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x8430a0010438ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_QSX_CQX_DOOR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_CQX_DOOR(a,b) bdk_nic_qsx_cqx_door_t
#define bustype_BDK_NIC_QSX_CQX_DOOR(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_CQX_DOOR(a,b) "NIC_QSX_CQX_DOOR"
#define device_bar_BDK_NIC_QSX_CQX_DOOR(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_CQX_DOOR(a,b) (a)
#define arguments_BDK_NIC_QSX_CQX_DOOR(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_cq#_head
 *
 * NIC Completion-Queue Head Registers
 */
union bdk_nic_qsx_cqx_head
{
    uint64_t u;
    struct bdk_nic_qsx_cqx_head_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_25_63        : 39;
        uint64_t head_ptr              : 16; /**< [ 24:  9](R/W/H) Head pointer \<24:9\> of CQ ring relative to NIC_QS()_CQ()_BASE. Address bits
                                                                 \<8:0\> are always 0. This register is automatically updated when software writes to
                                                                 NIC_QS()_CQ()_DOOR. Writes are ignored when NIC_PF_CFG[TEST_MODE] is clear. */
        uint64_t reserved_0_8          : 9;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_8          : 9;
        uint64_t head_ptr              : 16; /**< [ 24:  9](R/W/H) Head pointer \<24:9\> of CQ ring relative to NIC_QS()_CQ()_BASE. Address bits
                                                                 \<8:0\> are always 0. This register is automatically updated when software writes to
                                                                 NIC_QS()_CQ()_DOOR. Writes are ignored when NIC_PF_CFG[TEST_MODE] is clear. */
        uint64_t reserved_25_63        : 39;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_cqx_head_s cn; */
};
typedef union bdk_nic_qsx_cqx_head bdk_nic_qsx_cqx_head_t;

static inline uint64_t BDK_NIC_QSX_CQX_HEAD(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_CQX_HEAD(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x8430a0010428ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x8430a0010428ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_QSX_CQX_HEAD", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_CQX_HEAD(a,b) bdk_nic_qsx_cqx_head_t
#define bustype_BDK_NIC_QSX_CQX_HEAD(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_CQX_HEAD(a,b) "NIC_QSX_CQX_HEAD"
#define device_bar_BDK_NIC_QSX_CQX_HEAD(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_CQX_HEAD(a,b) (a)
#define arguments_BDK_NIC_QSX_CQX_HEAD(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_cq#_status
 *
 * NIC Completion-Queue Status Registers
 */
union bdk_nic_qsx_cqx_status
{
    uint64_t u;
    struct bdk_nic_qsx_cqx_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_27_63        : 37;
        uint64_t cq_wr_full            : 1;  /**< [ 26: 26](RO/H) NIC has detected an error on this CQ. Write to CQ when full. The CQ is stopped when this
                                                                 bit is set; all receive packets for this CQ are discarded, but send packets for this CQ
                                                                 may continue transmission although no NIC_CQE_SEND_Ss will be created for them. In order
                                                                 to restart the CQ, software must first reset it by writing a 1 to
                                                                 NIC_QS()_CQ()_CFG[RESET], then reconfigure and re-enable the CQ. */
        uint64_t cq_wr_disable         : 1;  /**< [ 25: 25](RO/H) NIC has detected an error on this CQ. Write to CQ when disable. The CQ is stopped when
                                                                 this
                                                                 bit is set; all receive packets for this CQ are discarded, but send packets for this CQ
                                                                 may continue transmission although no NIC_CQE_SEND_Ss will be created for them. In order
                                                                 to restart the CQ, software must first reset it by writing a 1 to
                                                                 NIC_QS()_CQ()_CFG[RESET], then reconfigure and re-enable the CQ. */
        uint64_t cq_wr_fault           : 1;  /**< [ 24: 24](RO/H) NIC has detected an error on this CQ. Fault on CQ write response. The CQ is stopped when
                                                                 this
                                                                 bit is set; all receive packets for this CQ are discarded, but send packets for this CQ
                                                                 may continue transmission although no NIC_CQE_SEND_Ss will be created for them. In order
                                                                 to restart the CQ, software must first reset it by writing a 1 to
                                                                 NIC_QS()_CQ()_CFG[RESET], then reconfigure and re-enable the CQ. */
        uint64_t avg                   : 8;  /**< [ 23: 16](RO/H) Time averaged queue level for RED, 0x0 indicates full, in units of /256ths of queue size. */
        uint64_t qcount                : 16; /**< [ 15:  0](RO/H) Number of valid entries in the CQ. Computed by hardware from
                                                                 NIC_QS()_CQ()_CFG[QSIZE], NIC_QS()_CQ()_TAIL[TAIL_PTR] and
                                                                 NIC_QS()_CQ()_HEAD[HEAD_PTR]. */
#else /* Word 0 - Little Endian */
        uint64_t qcount                : 16; /**< [ 15:  0](RO/H) Number of valid entries in the CQ. Computed by hardware from
                                                                 NIC_QS()_CQ()_CFG[QSIZE], NIC_QS()_CQ()_TAIL[TAIL_PTR] and
                                                                 NIC_QS()_CQ()_HEAD[HEAD_PTR]. */
        uint64_t avg                   : 8;  /**< [ 23: 16](RO/H) Time averaged queue level for RED, 0x0 indicates full, in units of /256ths of queue size. */
        uint64_t cq_wr_fault           : 1;  /**< [ 24: 24](RO/H) NIC has detected an error on this CQ. Fault on CQ write response. The CQ is stopped when
                                                                 this
                                                                 bit is set; all receive packets for this CQ are discarded, but send packets for this CQ
                                                                 may continue transmission although no NIC_CQE_SEND_Ss will be created for them. In order
                                                                 to restart the CQ, software must first reset it by writing a 1 to
                                                                 NIC_QS()_CQ()_CFG[RESET], then reconfigure and re-enable the CQ. */
        uint64_t cq_wr_disable         : 1;  /**< [ 25: 25](RO/H) NIC has detected an error on this CQ. Write to CQ when disable. The CQ is stopped when
                                                                 this
                                                                 bit is set; all receive packets for this CQ are discarded, but send packets for this CQ
                                                                 may continue transmission although no NIC_CQE_SEND_Ss will be created for them. In order
                                                                 to restart the CQ, software must first reset it by writing a 1 to
                                                                 NIC_QS()_CQ()_CFG[RESET], then reconfigure and re-enable the CQ. */
        uint64_t cq_wr_full            : 1;  /**< [ 26: 26](RO/H) NIC has detected an error on this CQ. Write to CQ when full. The CQ is stopped when this
                                                                 bit is set; all receive packets for this CQ are discarded, but send packets for this CQ
                                                                 may continue transmission although no NIC_CQE_SEND_Ss will be created for them. In order
                                                                 to restart the CQ, software must first reset it by writing a 1 to
                                                                 NIC_QS()_CQ()_CFG[RESET], then reconfigure and re-enable the CQ. */
        uint64_t reserved_27_63        : 37;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_cqx_status_s cn; */
};
typedef union bdk_nic_qsx_cqx_status bdk_nic_qsx_cqx_status_t;

static inline uint64_t BDK_NIC_QSX_CQX_STATUS(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_CQX_STATUS(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x8430a0010440ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x8430a0010440ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_QSX_CQX_STATUS", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_CQX_STATUS(a,b) bdk_nic_qsx_cqx_status_t
#define bustype_BDK_NIC_QSX_CQX_STATUS(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_CQX_STATUS(a,b) "NIC_QSX_CQX_STATUS"
#define device_bar_BDK_NIC_QSX_CQX_STATUS(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_CQX_STATUS(a,b) (a)
#define arguments_BDK_NIC_QSX_CQX_STATUS(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_cq#_status2
 *
 * NIC Completion-Queue Status Registers 2
 */
union bdk_nic_qsx_cqx_status2
{
    uint64_t u;
    struct bdk_nic_qsx_cqx_status2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t timer_en              : 1;  /**< [ 31: 31](RO/H) Interrupt-timer enable for this CQ. This is set by a hardware background task when:
                                                                 NIC_QS()_CQ()_STATUS[QCOUNT] is not 0 and
                                                                 NIC_QS()_CQ()_CFG2[INT_TIMER_THR] is not 0. */
        uint64_t reserved_28_30        : 3;
        uint64_t global_time           : 12; /**< [ 27: 16](RO/H) Global time. A free-running timer that increments on each interrupt timer tick as
                                                                 configured by NIC_PF_INT_TIMER_CFG[CLK_PER_INT_TICK]. Wraps around at maximum value. Not a
                                                                 per CQ counter, just provided here for reference. */
        uint64_t reserved_12_15        : 4;
        uint64_t int_timer             : 12; /**< [ 11:  0](RO/H) CQ interrupt timer.
                                                                 Hardware sets [INT_TIMER] to the threshold value [GLOBAL_TIME] +
                                                                 NIC_QS()_CQ()_CFG2[INT_TIMER_THR] whenever one of the following occurs:
                                                                 * [TIMER_EN] goes from 0 to 1.
                                                                 * [GLOBAL_TIME] crosses [INT_TIMER] and [TIMER_EN] is 1.
                                                                 * NIC_VF()_INT[CQ] for this CQ is written with a 1 to clear and [TIMER_EN] is 1.
                                                                 * Software writes to NIC_QS()_CQ()_CFG2 and [TIMER_EN] is 1. */
#else /* Word 0 - Little Endian */
        uint64_t int_timer             : 12; /**< [ 11:  0](RO/H) CQ interrupt timer.
                                                                 Hardware sets [INT_TIMER] to the threshold value [GLOBAL_TIME] +
                                                                 NIC_QS()_CQ()_CFG2[INT_TIMER_THR] whenever one of the following occurs:
                                                                 * [TIMER_EN] goes from 0 to 1.
                                                                 * [GLOBAL_TIME] crosses [INT_TIMER] and [TIMER_EN] is 1.
                                                                 * NIC_VF()_INT[CQ] for this CQ is written with a 1 to clear and [TIMER_EN] is 1.
                                                                 * Software writes to NIC_QS()_CQ()_CFG2 and [TIMER_EN] is 1. */
        uint64_t reserved_12_15        : 4;
        uint64_t global_time           : 12; /**< [ 27: 16](RO/H) Global time. A free-running timer that increments on each interrupt timer tick as
                                                                 configured by NIC_PF_INT_TIMER_CFG[CLK_PER_INT_TICK]. Wraps around at maximum value. Not a
                                                                 per CQ counter, just provided here for reference. */
        uint64_t reserved_28_30        : 3;
        uint64_t timer_en              : 1;  /**< [ 31: 31](RO/H) Interrupt-timer enable for this CQ. This is set by a hardware background task when:
                                                                 NIC_QS()_CQ()_STATUS[QCOUNT] is not 0 and
                                                                 NIC_QS()_CQ()_CFG2[INT_TIMER_THR] is not 0. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_cqx_status2_s cn; */
};
typedef union bdk_nic_qsx_cqx_status2 bdk_nic_qsx_cqx_status2_t;

static inline uint64_t BDK_NIC_QSX_CQX_STATUS2(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_CQX_STATUS2(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x8430a0010448ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x8430a0010448ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_QSX_CQX_STATUS2", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_CQX_STATUS2(a,b) bdk_nic_qsx_cqx_status2_t
#define bustype_BDK_NIC_QSX_CQX_STATUS2(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_CQX_STATUS2(a,b) "NIC_QSX_CQX_STATUS2"
#define device_bar_BDK_NIC_QSX_CQX_STATUS2(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_CQX_STATUS2(a,b) (a)
#define arguments_BDK_NIC_QSX_CQX_STATUS2(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_cq#_tail
 *
 * NIC Completion-Queue Tail Registers
 */
union bdk_nic_qsx_cqx_tail
{
    uint64_t u;
    struct bdk_nic_qsx_cqx_tail_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_25_63        : 39;
        uint64_t tail_ptr              : 16; /**< [ 24:  9](R/W/H) Tail pointer \<24:9\> of CQ ring relative to NIC_QS()_CQ()_BASE. Address bits
                                                                 \<8:0\> are always 0. Hardware updates this register to notify software that one or more
                                                                 entries have been enqueued to the CQ ring. Writes are ignored when NIC_PF_CFG[TEST_MODE]
                                                                 is clear. */
        uint64_t reserved_0_8          : 9;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_8          : 9;
        uint64_t tail_ptr              : 16; /**< [ 24:  9](R/W/H) Tail pointer \<24:9\> of CQ ring relative to NIC_QS()_CQ()_BASE. Address bits
                                                                 \<8:0\> are always 0. Hardware updates this register to notify software that one or more
                                                                 entries have been enqueued to the CQ ring. Writes are ignored when NIC_PF_CFG[TEST_MODE]
                                                                 is clear. */
        uint64_t reserved_25_63        : 39;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_cqx_tail_s cn; */
};
typedef union bdk_nic_qsx_cqx_tail bdk_nic_qsx_cqx_tail_t;

static inline uint64_t BDK_NIC_QSX_CQX_TAIL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_CQX_TAIL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x8430a0010430ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x8430a0010430ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_QSX_CQX_TAIL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_CQX_TAIL(a,b) bdk_nic_qsx_cqx_tail_t
#define bustype_BDK_NIC_QSX_CQX_TAIL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_CQX_TAIL(a,b) "NIC_QSX_CQX_TAIL"
#define device_bar_BDK_NIC_QSX_CQX_TAIL(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_CQX_TAIL(a,b) (a)
#define arguments_BDK_NIC_QSX_CQX_TAIL(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_cq#_thresh
 *
 * NIC Completion-Queue Threshold Registers
 */
union bdk_nic_qsx_cqx_thresh
{
    uint64_t u;
    struct bdk_nic_qsx_cqx_thresh_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t thresh                : 16; /**< [ 15:  0](R/W) Queue-count threshold for CQ interrupt. When nonzero, the associated
                                                                 NIC_VF()_INT[CQ] interrupt bit is set when NIC_QS()_CQ()_STATUS[QCOUNT]
                                                                 crosses [THRESH], provided [THRESH] is nonzero. */
#else /* Word 0 - Little Endian */
        uint64_t thresh                : 16; /**< [ 15:  0](R/W) Queue-count threshold for CQ interrupt. When nonzero, the associated
                                                                 NIC_VF()_INT[CQ] interrupt bit is set when NIC_QS()_CQ()_STATUS[QCOUNT]
                                                                 crosses [THRESH], provided [THRESH] is nonzero. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_cqx_thresh_s cn; */
};
typedef union bdk_nic_qsx_cqx_thresh bdk_nic_qsx_cqx_thresh_t;

static inline uint64_t BDK_NIC_QSX_CQX_THRESH(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_CQX_THRESH(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x8430a0010410ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x8430a0010410ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_QSX_CQX_THRESH", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_CQX_THRESH(a,b) bdk_nic_qsx_cqx_thresh_t
#define bustype_BDK_NIC_QSX_CQX_THRESH(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_CQX_THRESH(a,b) "NIC_QSX_CQX_THRESH"
#define device_bar_BDK_NIC_QSX_CQX_THRESH(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_CQX_THRESH(a,b) (a)
#define arguments_BDK_NIC_QSX_CQX_THRESH(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_rbdr#_base
 *
 * NIC Receive-Buffer Descriptor-Ring Base-Address Registers
 */
union bdk_nic_qsx_rbdrx_base
{
    uint64_t u;
    struct bdk_nic_qsx_rbdrx_base_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t base_addr             : 42; /**< [ 48:  7](R/W) Base IOVA\<48:7\> of RBDR in DRAM (VA, IPA or PA depending on SMMU
                                                                 configuration). Address bits \<6:0\> are always 0. Writes are ignored when the RBDR is
                                                                 active, i.e.:
                                                                 _ NIC_QS()_RBDR()_CFG[ENA]==1, or
                                                                 _ NIC_QS()_RBDR()_HEAD[HEAD_PTR]!=NIC_QS()_RBDR()_TAIL[TAIL_PTR] */
        uint64_t reserved_0_6          : 7;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_6          : 7;
        uint64_t base_addr             : 42; /**< [ 48:  7](R/W) Base IOVA\<48:7\> of RBDR in DRAM (VA, IPA or PA depending on SMMU
                                                                 configuration). Address bits \<6:0\> are always 0. Writes are ignored when the RBDR is
                                                                 active, i.e.:
                                                                 _ NIC_QS()_RBDR()_CFG[ENA]==1, or
                                                                 _ NIC_QS()_RBDR()_HEAD[HEAD_PTR]!=NIC_QS()_RBDR()_TAIL[TAIL_PTR] */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_rbdrx_base_s cn; */
};
typedef union bdk_nic_qsx_rbdrx_base bdk_nic_qsx_rbdrx_base_t;

static inline uint64_t BDK_NIC_QSX_RBDRX_BASE(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_RBDRX_BASE(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=1)))
        return 0x8430a0010c20ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=1)))
        return 0x8430a0010c20ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x1);
    __bdk_csr_fatal("NIC_QSX_RBDRX_BASE", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_RBDRX_BASE(a,b) bdk_nic_qsx_rbdrx_base_t
#define bustype_BDK_NIC_QSX_RBDRX_BASE(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_RBDRX_BASE(a,b) "NIC_QSX_RBDRX_BASE"
#define device_bar_BDK_NIC_QSX_RBDRX_BASE(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_RBDRX_BASE(a,b) (a)
#define arguments_BDK_NIC_QSX_RBDRX_BASE(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_rbdr#_cfg
 *
 * NIC Receive-Buffer Descriptor-Ring Configuration Registers
 * Writes to all fields except [ENA] and [RESET] are ignored when the RBDR is active, i.e.:
 * _ [ENA]==1, or
 * _ or NIC_QS()_RBDR()_HEAD[HEAD_PTR]!=NIC_QS()_RBDR()_TAIL[TAIL_PTR]
 *
 * Furthermore, writes to [RESET] are ignored when [ENA]==1.
 */
union bdk_nic_qsx_rbdrx_cfg
{
    uint64_t u;
    struct bdk_nic_qsx_rbdrx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_45_63        : 19;
        uint64_t ena                   : 1;  /**< [ 44: 44](R/W) Enable RBDR. */
        uint64_t reset                 : 1;  /**< [ 43: 43](R/W) RBDR Reset. Writing a 1 resets all the NIC_QS()_RBDR()_* registers and internal
                                                                 state for this RBDR. Software clears after the reset sequence is complete. */
        uint64_t ldwb                  : 1;  /**< [ 42: 42](R/W) When reading RBDR entry cache lines, use LDWB transactions to invalidate the cache line. */
        uint64_t reserved_36_41        : 6;
        uint64_t qsize                 : 4;  /**< [ 35: 32](R/W) Specifies RBDR size in entries of 8 bytes, as follows:
                                                                 0x0 = 8K entries.
                                                                 0x1 = 16K entries.
                                                                 0x2 = 32K entries.
                                                                 0x3 = 64K entries.
                                                                 0x4 = 128K entries.
                                                                 0x5 = 256K entries.
                                                                 0x6 = 512K entries.
                                                                 else = Reserved.

                                                                 Note that the usable size of the ring is the specified size minus 1 (HEAD==TAIL always
                                                                 means empty). */
        uint64_t reserved_25_31        : 7;
        uint64_t avg_con               : 9;  /**< [ 24: 16](R/W) This value controls how much of each present average resource level is used to calculate
                                                                 the new resource level. The value is a number from 0 to 256, which represents
                                                                 [AVG_CON]/256
                                                                 of the average resource level that will be used in the calculation:

                                                                 next_LEVEL = ([AVG_CON]/256) * prev_LEVEL + (1-([AVG_CON]/256)) * count

                                                                 Note setting this value to zero will disable averaging, and always use the most immediate
                                                                 levels. NIC_PF_RRM_AVG_CFG[AVG_EN] must be set and NIC_PF_RRM_AVG_CFG[LVL_DLY] must be
                                                                 nonzero to globally enable averaging. NIC_PF_RRM_AVG_CFG[AVG_DLY] controls the periodicity
                                                                 of the level calculations. */
        uint64_t reserved_9_15         : 7;
        uint64_t lines                 : 9;  /**< [  8:  0](R/W) Size of buffers linked to this ring in 128-byte cache lines.
                                                                 0x0 is illegal and will get aliased to a setting of 0x1. */
#else /* Word 0 - Little Endian */
        uint64_t lines                 : 9;  /**< [  8:  0](R/W) Size of buffers linked to this ring in 128-byte cache lines.
                                                                 0x0 is illegal and will get aliased to a setting of 0x1. */
        uint64_t reserved_9_15         : 7;
        uint64_t avg_con               : 9;  /**< [ 24: 16](R/W) This value controls how much of each present average resource level is used to calculate
                                                                 the new resource level. The value is a number from 0 to 256, which represents
                                                                 [AVG_CON]/256
                                                                 of the average resource level that will be used in the calculation:

                                                                 next_LEVEL = ([AVG_CON]/256) * prev_LEVEL + (1-([AVG_CON]/256)) * count

                                                                 Note setting this value to zero will disable averaging, and always use the most immediate
                                                                 levels. NIC_PF_RRM_AVG_CFG[AVG_EN] must be set and NIC_PF_RRM_AVG_CFG[LVL_DLY] must be
                                                                 nonzero to globally enable averaging. NIC_PF_RRM_AVG_CFG[AVG_DLY] controls the periodicity
                                                                 of the level calculations. */
        uint64_t reserved_25_31        : 7;
        uint64_t qsize                 : 4;  /**< [ 35: 32](R/W) Specifies RBDR size in entries of 8 bytes, as follows:
                                                                 0x0 = 8K entries.
                                                                 0x1 = 16K entries.
                                                                 0x2 = 32K entries.
                                                                 0x3 = 64K entries.
                                                                 0x4 = 128K entries.
                                                                 0x5 = 256K entries.
                                                                 0x6 = 512K entries.
                                                                 else = Reserved.

                                                                 Note that the usable size of the ring is the specified size minus 1 (HEAD==TAIL always
                                                                 means empty). */
        uint64_t reserved_36_41        : 6;
        uint64_t ldwb                  : 1;  /**< [ 42: 42](R/W) When reading RBDR entry cache lines, use LDWB transactions to invalidate the cache line. */
        uint64_t reset                 : 1;  /**< [ 43: 43](R/W) RBDR Reset. Writing a 1 resets all the NIC_QS()_RBDR()_* registers and internal
                                                                 state for this RBDR. Software clears after the reset sequence is complete. */
        uint64_t ena                   : 1;  /**< [ 44: 44](R/W) Enable RBDR. */
        uint64_t reserved_45_63        : 19;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_rbdrx_cfg_s cn; */
};
typedef union bdk_nic_qsx_rbdrx_cfg bdk_nic_qsx_rbdrx_cfg_t;

static inline uint64_t BDK_NIC_QSX_RBDRX_CFG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_RBDRX_CFG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=1)))
        return 0x8430a0010c00ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=1)))
        return 0x8430a0010c00ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x1);
    __bdk_csr_fatal("NIC_QSX_RBDRX_CFG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_RBDRX_CFG(a,b) bdk_nic_qsx_rbdrx_cfg_t
#define bustype_BDK_NIC_QSX_RBDRX_CFG(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_RBDRX_CFG(a,b) "NIC_QSX_RBDRX_CFG"
#define device_bar_BDK_NIC_QSX_RBDRX_CFG(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_RBDRX_CFG(a,b) (a)
#define arguments_BDK_NIC_QSX_RBDRX_CFG(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_rbdr#_door
 *
 * NIC Receive-Buffer Descriptor-Ring Doorbell Registers
 * Software writes to this register to notify hardware that one or more entries have been
 * enqueued to the RBDR.
 */
union bdk_nic_qsx_rbdrx_door
{
    uint64_t u;
    struct bdk_nic_qsx_rbdrx_door_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_19_63        : 45;
        uint64_t count                 : 19; /**< [ 18:  0](WO) Number of enqueued entries of 8 bytes. Hardware advances NIC_QS()_RBDR()_TAIL[TAIL_PTR] by
                                                                 this value if the RBDR is enabled.

                                                                 The usable size of the ring is the size specified by NIC_QS()_RBDR()_CFG[QSIZE] minus 1.
                                                                 As such, a doorbell write that would make the ring go full or overflow is suppressed and
                                                                 treated as a doorbell error. Hardware stops the RBDR on a doorbell error and sets
                                                                 NIC_QS()_RBDR()_STATUS0[FIFO_STATE] = 0x3 (FAIL). */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 19; /**< [ 18:  0](WO) Number of enqueued entries of 8 bytes. Hardware advances NIC_QS()_RBDR()_TAIL[TAIL_PTR] by
                                                                 this value if the RBDR is enabled.

                                                                 The usable size of the ring is the size specified by NIC_QS()_RBDR()_CFG[QSIZE] minus 1.
                                                                 As such, a doorbell write that would make the ring go full or overflow is suppressed and
                                                                 treated as a doorbell error. Hardware stops the RBDR on a doorbell error and sets
                                                                 NIC_QS()_RBDR()_STATUS0[FIFO_STATE] = 0x3 (FAIL). */
        uint64_t reserved_19_63        : 45;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_rbdrx_door_s cn; */
};
typedef union bdk_nic_qsx_rbdrx_door bdk_nic_qsx_rbdrx_door_t;

static inline uint64_t BDK_NIC_QSX_RBDRX_DOOR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_RBDRX_DOOR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=1)))
        return 0x8430a0010c38ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=1)))
        return 0x8430a0010c38ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x1);
    __bdk_csr_fatal("NIC_QSX_RBDRX_DOOR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_RBDRX_DOOR(a,b) bdk_nic_qsx_rbdrx_door_t
#define bustype_BDK_NIC_QSX_RBDRX_DOOR(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_RBDRX_DOOR(a,b) "NIC_QSX_RBDRX_DOOR"
#define device_bar_BDK_NIC_QSX_RBDRX_DOOR(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_RBDRX_DOOR(a,b) (a)
#define arguments_BDK_NIC_QSX_RBDRX_DOOR(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_rbdr#_head
 *
 * NIC Receive-Buffer Descriptor-Ring Head Registers
 */
union bdk_nic_qsx_rbdrx_head
{
    uint64_t u;
    struct bdk_nic_qsx_rbdrx_head_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t head_ptr              : 19; /**< [ 21:  3](R/W/H) Head pointer \<21:3\> of RBDR in DRAM relative to NIC_QS()_RBDR()_BASE.
                                                                 Address bits \<2:0\> are always 0. Hardware updates this to notify software that one or more
                                                                 entries have been dequeued from the RBDR. Writes are ignored when NIC_PF_CFG[TEST_MODE] is
                                                                 clear. */
        uint64_t reserved_0_2          : 3;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_2          : 3;
        uint64_t head_ptr              : 19; /**< [ 21:  3](R/W/H) Head pointer \<21:3\> of RBDR in DRAM relative to NIC_QS()_RBDR()_BASE.
                                                                 Address bits \<2:0\> are always 0. Hardware updates this to notify software that one or more
                                                                 entries have been dequeued from the RBDR. Writes are ignored when NIC_PF_CFG[TEST_MODE] is
                                                                 clear. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_rbdrx_head_s cn; */
};
typedef union bdk_nic_qsx_rbdrx_head bdk_nic_qsx_rbdrx_head_t;

static inline uint64_t BDK_NIC_QSX_RBDRX_HEAD(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_RBDRX_HEAD(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=1)))
        return 0x8430a0010c28ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=1)))
        return 0x8430a0010c28ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x1);
    __bdk_csr_fatal("NIC_QSX_RBDRX_HEAD", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_RBDRX_HEAD(a,b) bdk_nic_qsx_rbdrx_head_t
#define bustype_BDK_NIC_QSX_RBDRX_HEAD(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_RBDRX_HEAD(a,b) "NIC_QSX_RBDRX_HEAD"
#define device_bar_BDK_NIC_QSX_RBDRX_HEAD(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_RBDRX_HEAD(a,b) (a)
#define arguments_BDK_NIC_QSX_RBDRX_HEAD(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_rbdr#_prefetch_status
 *
 * NIC Receive-Buffer Descriptor-Ring Buffer PreFetch Status Register
 */
union bdk_nic_qsx_rbdrx_prefetch_status
{
    uint64_t u;
    struct bdk_nic_qsx_rbdrx_prefetch_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t prefetch_returned_cnt : 32; /**< [ 63: 32](RO/H) This is the count of RBDR prefetch req cycles that have returned.
                                                                 Note, these values are free-running values that represent all prefetched return requests. */
        uint64_t prefetch_req_cnt      : 32; /**< [ 31:  0](RO/H) This is the count of RBDR prefetch req cycles that have been initiated.
                                                                 Note, these values are free-running values that represent all prefetched return requests. */
#else /* Word 0 - Little Endian */
        uint64_t prefetch_req_cnt      : 32; /**< [ 31:  0](RO/H) This is the count of RBDR prefetch req cycles that have been initiated.
                                                                 Note, these values are free-running values that represent all prefetched return requests. */
        uint64_t prefetch_returned_cnt : 32; /**< [ 63: 32](RO/H) This is the count of RBDR prefetch req cycles that have returned.
                                                                 Note, these values are free-running values that represent all prefetched return requests. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_rbdrx_prefetch_status_s cn; */
};
typedef union bdk_nic_qsx_rbdrx_prefetch_status bdk_nic_qsx_rbdrx_prefetch_status_t;

static inline uint64_t BDK_NIC_QSX_RBDRX_PREFETCH_STATUS(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_RBDRX_PREFETCH_STATUS(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=1)))
        return 0x8430a0010c50ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=1)))
        return 0x8430a0010c50ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x1);
    __bdk_csr_fatal("NIC_QSX_RBDRX_PREFETCH_STATUS", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_RBDRX_PREFETCH_STATUS(a,b) bdk_nic_qsx_rbdrx_prefetch_status_t
#define bustype_BDK_NIC_QSX_RBDRX_PREFETCH_STATUS(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_RBDRX_PREFETCH_STATUS(a,b) "NIC_QSX_RBDRX_PREFETCH_STATUS"
#define device_bar_BDK_NIC_QSX_RBDRX_PREFETCH_STATUS(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_RBDRX_PREFETCH_STATUS(a,b) (a)
#define arguments_BDK_NIC_QSX_RBDRX_PREFETCH_STATUS(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_rbdr#_status0
 *
 * NIC Receive-Buffer Descriptor-Ring Status 0 Registers
 */
union bdk_nic_qsx_rbdrx_status0
{
    uint64_t u;
    struct bdk_nic_qsx_rbdrx_status0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t fifo_state            : 2;  /**< [ 63: 62](RO/H) Current state of the RBDR FIFO. 00-Inactive, 01-Active, 10-Reset, 11-FAIL. The RBDR is
                                                                 stopped  when the state is FAIL and all received packets for it are discarded. In order to
                                                                 restart the RBDR, software must first reset it by writing a 1 to
                                                                 NIC_QS()_RBDR()_CFG[RESET], then reconfigure and re-enable the RBDR. */
        uint64_t reserved_55_61        : 7;
        uint64_t fifo_level            : 7;  /**< [ 54: 48](RO/H) Current level of the internal RBDR FIFO. */
        uint64_t reserved_43_47        : 5;
        uint64_t prefetch_head         : 19; /**< [ 42: 24](RO/H) The current hardware head pointer position after prefetch to the internal pointer cache. */
        uint64_t reserved_19_23        : 5;
        uint64_t qcount                : 19; /**< [ 18:  0](RO/H) Number of valid entries in the RBDR. Computed by hardware from
                                                                 NIC_QS()_RBDR()_CFG[QSIZE], NIC_QS()_RBDR()_TAIL[TAIL_PTR] and
                                                                 NIC_QS()_RBDR()_HEAD[HEAD_PTR]. */
#else /* Word 0 - Little Endian */
        uint64_t qcount                : 19; /**< [ 18:  0](RO/H) Number of valid entries in the RBDR. Computed by hardware from
                                                                 NIC_QS()_RBDR()_CFG[QSIZE], NIC_QS()_RBDR()_TAIL[TAIL_PTR] and
                                                                 NIC_QS()_RBDR()_HEAD[HEAD_PTR]. */
        uint64_t reserved_19_23        : 5;
        uint64_t prefetch_head         : 19; /**< [ 42: 24](RO/H) The current hardware head pointer position after prefetch to the internal pointer cache. */
        uint64_t reserved_43_47        : 5;
        uint64_t fifo_level            : 7;  /**< [ 54: 48](RO/H) Current level of the internal RBDR FIFO. */
        uint64_t reserved_55_61        : 7;
        uint64_t fifo_state            : 2;  /**< [ 63: 62](RO/H) Current state of the RBDR FIFO. 00-Inactive, 01-Active, 10-Reset, 11-FAIL. The RBDR is
                                                                 stopped  when the state is FAIL and all received packets for it are discarded. In order to
                                                                 restart the RBDR, software must first reset it by writing a 1 to
                                                                 NIC_QS()_RBDR()_CFG[RESET], then reconfigure and re-enable the RBDR. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_rbdrx_status0_s cn; */
};
typedef union bdk_nic_qsx_rbdrx_status0 bdk_nic_qsx_rbdrx_status0_t;

static inline uint64_t BDK_NIC_QSX_RBDRX_STATUS0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_RBDRX_STATUS0(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=1)))
        return 0x8430a0010c40ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=1)))
        return 0x8430a0010c40ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x1);
    __bdk_csr_fatal("NIC_QSX_RBDRX_STATUS0", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_RBDRX_STATUS0(a,b) bdk_nic_qsx_rbdrx_status0_t
#define bustype_BDK_NIC_QSX_RBDRX_STATUS0(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_RBDRX_STATUS0(a,b) "NIC_QSX_RBDRX_STATUS0"
#define device_bar_BDK_NIC_QSX_RBDRX_STATUS0(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_RBDRX_STATUS0(a,b) (a)
#define arguments_BDK_NIC_QSX_RBDRX_STATUS0(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_rbdr#_status1
 *
 * NIC Receive-Buffer Descriptor-Ring Status 1 Registers
 */
union bdk_nic_qsx_rbdrx_status1
{
    uint64_t u;
    struct bdk_nic_qsx_rbdrx_status1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t avg                   : 8;  /**< [  7:  0](RO/H) Time averaged queue level for RED, 0x0 indicates empty, in units of /256ths of queue size. */
#else /* Word 0 - Little Endian */
        uint64_t avg                   : 8;  /**< [  7:  0](RO/H) Time averaged queue level for RED, 0x0 indicates empty, in units of /256ths of queue size. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_rbdrx_status1_s cn; */
};
typedef union bdk_nic_qsx_rbdrx_status1 bdk_nic_qsx_rbdrx_status1_t;

static inline uint64_t BDK_NIC_QSX_RBDRX_STATUS1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_RBDRX_STATUS1(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=1)))
        return 0x8430a0010c48ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=1)))
        return 0x8430a0010c48ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x1);
    __bdk_csr_fatal("NIC_QSX_RBDRX_STATUS1", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_RBDRX_STATUS1(a,b) bdk_nic_qsx_rbdrx_status1_t
#define bustype_BDK_NIC_QSX_RBDRX_STATUS1(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_RBDRX_STATUS1(a,b) "NIC_QSX_RBDRX_STATUS1"
#define device_bar_BDK_NIC_QSX_RBDRX_STATUS1(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_RBDRX_STATUS1(a,b) (a)
#define arguments_BDK_NIC_QSX_RBDRX_STATUS1(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_rbdr#_tail
 *
 * NIC Receive-Buffer Descriptor-Ring Tail Registers
 */
union bdk_nic_qsx_rbdrx_tail
{
    uint64_t u;
    struct bdk_nic_qsx_rbdrx_tail_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t tail_ptr              : 19; /**< [ 21:  3](R/W/H) Tail pointer \<21:3\> of RBDR in DRAM relative to NIC_QS()_RBDR()_BASE.
                                                                 Address bits \<2:0\> are always 0. Automatically updated when software writes to the
                                                                 NIC_QS()_RBDR()_DOOR register. Writes are ignored when NIC_PF_CFG[TEST_MODE] is
                                                                 clear. */
        uint64_t reserved_0_2          : 3;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_2          : 3;
        uint64_t tail_ptr              : 19; /**< [ 21:  3](R/W/H) Tail pointer \<21:3\> of RBDR in DRAM relative to NIC_QS()_RBDR()_BASE.
                                                                 Address bits \<2:0\> are always 0. Automatically updated when software writes to the
                                                                 NIC_QS()_RBDR()_DOOR register. Writes are ignored when NIC_PF_CFG[TEST_MODE] is
                                                                 clear. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_rbdrx_tail_s cn; */
};
typedef union bdk_nic_qsx_rbdrx_tail bdk_nic_qsx_rbdrx_tail_t;

static inline uint64_t BDK_NIC_QSX_RBDRX_TAIL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_RBDRX_TAIL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=1)))
        return 0x8430a0010c30ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=1)))
        return 0x8430a0010c30ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x1);
    __bdk_csr_fatal("NIC_QSX_RBDRX_TAIL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_RBDRX_TAIL(a,b) bdk_nic_qsx_rbdrx_tail_t
#define bustype_BDK_NIC_QSX_RBDRX_TAIL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_RBDRX_TAIL(a,b) "NIC_QSX_RBDRX_TAIL"
#define device_bar_BDK_NIC_QSX_RBDRX_TAIL(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_RBDRX_TAIL(a,b) (a)
#define arguments_BDK_NIC_QSX_RBDRX_TAIL(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_rbdr#_thresh
 *
 * NIC Receive-Buffer Descriptor-Ring Threshold Registers
 */
union bdk_nic_qsx_rbdrx_thresh
{
    uint64_t u;
    struct bdk_nic_qsx_rbdrx_thresh_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_19_63        : 45;
        uint64_t thresh                : 19; /**< [ 18:  0](R/W) Queue-count threshold for RBDR interrupt. When nonzero, the associated
                                                                 NIC_VF()_INT[RBDR] interrupt bit is set when
                                                                 NIC_QS()_RBDR()_STATUS0[QCOUNT] crosses [THRESH]. */
#else /* Word 0 - Little Endian */
        uint64_t thresh                : 19; /**< [ 18:  0](R/W) Queue-count threshold for RBDR interrupt. When nonzero, the associated
                                                                 NIC_VF()_INT[RBDR] interrupt bit is set when
                                                                 NIC_QS()_RBDR()_STATUS0[QCOUNT] crosses [THRESH]. */
        uint64_t reserved_19_63        : 45;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_rbdrx_thresh_s cn; */
};
typedef union bdk_nic_qsx_rbdrx_thresh bdk_nic_qsx_rbdrx_thresh_t;

static inline uint64_t BDK_NIC_QSX_RBDRX_THRESH(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_RBDRX_THRESH(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=1)))
        return 0x8430a0010c10ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=1)))
        return 0x8430a0010c10ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x1);
    __bdk_csr_fatal("NIC_QSX_RBDRX_THRESH", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_RBDRX_THRESH(a,b) bdk_nic_qsx_rbdrx_thresh_t
#define bustype_BDK_NIC_QSX_RBDRX_THRESH(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_RBDRX_THRESH(a,b) "NIC_QSX_RBDRX_THRESH"
#define device_bar_BDK_NIC_QSX_RBDRX_THRESH(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_RBDRX_THRESH(a,b) (a)
#define arguments_BDK_NIC_QSX_RBDRX_THRESH(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_rq#_cfg
 *
 * NIC Receive-Queue Configuration Registers
 */
union bdk_nic_qsx_rqx_cfg
{
    uint64_t u;
    struct bdk_nic_qsx_rqx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t ena                   : 1;  /**< [  1:  1](R/W) Enable RQ. Writing a 1 to this bit enables the RQ. Writing a 0 gracefully disables the RQ.
                                                                 Software can poll this bit for a 0 to determine if all hardware processing for this RQ has
                                                                 stopped. */
        uint64_t tcp_ena               : 1;  /**< [  0:  0](R/W) Reserved.
                                                                 Internal:
                                                                 Reserved for future use - TCP reassembly enable. */
#else /* Word 0 - Little Endian */
        uint64_t tcp_ena               : 1;  /**< [  0:  0](R/W) Reserved.
                                                                 Internal:
                                                                 Reserved for future use - TCP reassembly enable. */
        uint64_t ena                   : 1;  /**< [  1:  1](R/W) Enable RQ. Writing a 1 to this bit enables the RQ. Writing a 0 gracefully disables the RQ.
                                                                 Software can poll this bit for a 0 to determine if all hardware processing for this RQ has
                                                                 stopped. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_rqx_cfg_s cn; */
};
typedef union bdk_nic_qsx_rqx_cfg bdk_nic_qsx_rqx_cfg_t;

static inline uint64_t BDK_NIC_QSX_RQX_CFG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_RQX_CFG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x8430a0010600ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x8430a0010600ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_QSX_RQX_CFG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_RQX_CFG(a,b) bdk_nic_qsx_rqx_cfg_t
#define bustype_BDK_NIC_QSX_RQX_CFG(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_RQX_CFG(a,b) "NIC_QSX_RQX_CFG"
#define device_bar_BDK_NIC_QSX_RQX_CFG(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_RQX_CFG(a,b) (a)
#define arguments_BDK_NIC_QSX_RQX_CFG(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_rq#_stat#
 *
 * NIC Receive-Queue Statistics Registers
 * The third dimension indicates which statistic, and is enumerated by NIC_STAT_RQ_E.
 */
union bdk_nic_qsx_rqx_statx
{
    uint64_t u;
    struct bdk_nic_qsx_rqx_statx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t stat                  : 48; /**< [ 47:  0](RO/H) Statistic value. See also NIC_PF_QS()_RQ()_STAT() for a writable alias of this field. */
#else /* Word 0 - Little Endian */
        uint64_t stat                  : 48; /**< [ 47:  0](RO/H) Statistic value. See also NIC_PF_QS()_RQ()_STAT() for a writable alias of this field. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_rqx_statx_s cn; */
};
typedef union bdk_nic_qsx_rqx_statx bdk_nic_qsx_rqx_statx_t;

static inline uint64_t BDK_NIC_QSX_RQX_STATX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_RQX_STATX(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7) && (c<=1)))
        return 0x8430a0010700ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7) + 8ll * ((c) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7) && (c<=1)))
        return 0x8430a0010700ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7) + 8ll * ((c) & 0x1);
    __bdk_csr_fatal("NIC_QSX_RQX_STATX", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_RQX_STATX(a,b,c) bdk_nic_qsx_rqx_statx_t
#define bustype_BDK_NIC_QSX_RQX_STATX(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_RQX_STATX(a,b,c) "NIC_QSX_RQX_STATX"
#define device_bar_BDK_NIC_QSX_RQX_STATX(a,b,c) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_RQX_STATX(a,b,c) (a)
#define arguments_BDK_NIC_QSX_RQX_STATX(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB) nic_qs#_rq_gen_cfg
 *
 * NIC VF Receive-Queue General Configuration Registers
 */
union bdk_nic_qsx_rq_gen_cfg
{
    uint64_t u;
    struct bdk_nic_qsx_rq_gen_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_27_63        : 37;
        uint64_t vlan_strip            : 2;  /**< [ 26: 25](R/W) Controls the stripping of any VLAN tags:
                                                                 0 = No strip.
                                                                 1 = Strip first VLAN if exists (NIC_CQE_RX_S[VV] set).
                                                                 2 = Strip second VLAN if exists (NIC_CQE_RX_S[VS] set).
                                                                 3 = Reserved. */
        uint64_t len_l4                : 1;  /**< [ 24: 24](R/W) Check length of L4. */
        uint64_t len_l3                : 1;  /**< [ 23: 23](R/W) Check length of IPv4/IPv6. */
        uint64_t dis_apad              : 1;  /**< [ 22: 22](R/W) When set, APAD alignment function is disabled and NIC_CQE_RX_S[APAD] is always 0x0. */
        uint64_t csum_l4               : 1;  /**< [ 21: 21](R/W) Compute checksum on TCP/UDP packets. */
        uint64_t ip6_udp_opt           : 1;  /**< [ 20: 20](R/W) IPv6/UDP checksum is optional. IPv4 allows an optional UDP checksum by sending the all-0s
                                                                 patterns. IPv6 outlaws this and the spec says to always check UDP checksum.
                                                                 0 = Spec compliant, do not allow optional code.
                                                                 1 = Treat IPv6 as IPv4; the all-0s pattern will cause a UDP checksum pass. */
        uint64_t splt_hdr_ena          : 1;  /**< [ 19: 19](R/W) When set, any packet with a valid header stack down to the end of the L4 layer has its
                                                                 header split into a separate RBDR buffer. */
        uint64_t cq_hdr_copy           : 1;  /**< [ 18: 18](R/W) If set, the header is copied into the CQE as well as existing in the packet buffer. The
                                                                 hardware will copy all defined headers. */
        uint64_t max_tcp_reass         : 2;  /**< [ 17: 16](R/W) Reserved.
                                                                 Internal:
                                                                 Reserved for future use - Maximum TCP reassembled packet:
                                                                 0x0 = 64Kbytes.
                                                                 0x1 = 256Kbytes.
                                                                 0x2-0x3 = Reserved. */
        uint64_t cq_pkt_size           : 8;  /**< [ 15:  8](R/W) Packet size in bytes. If a packet is smaller than this
                                                                 value, the entire packet is sent to the CQ buffer and no RB is used. Maximum number of
                                                                 bytes is 249, to allow for up to 7 byte alignment pad. */
        uint64_t later_skip            : 4;  /**< [  7:  4](R/W) Number of eight-byte words that are skipped at the beginning of other than the first RB
                                                                 for a packet. */
        uint64_t first_skip            : 4;  /**< [  3:  0](R/W) Number of eight-byte words that are skipped at the beginning of the first RB for a packet. */
#else /* Word 0 - Little Endian */
        uint64_t first_skip            : 4;  /**< [  3:  0](R/W) Number of eight-byte words that are skipped at the beginning of the first RB for a packet. */
        uint64_t later_skip            : 4;  /**< [  7:  4](R/W) Number of eight-byte words that are skipped at the beginning of other than the first RB
                                                                 for a packet. */
        uint64_t cq_pkt_size           : 8;  /**< [ 15:  8](R/W) Packet size in bytes. If a packet is smaller than this
                                                                 value, the entire packet is sent to the CQ buffer and no RB is used. Maximum number of
                                                                 bytes is 249, to allow for up to 7 byte alignment pad. */
        uint64_t max_tcp_reass         : 2;  /**< [ 17: 16](R/W) Reserved.
                                                                 Internal:
                                                                 Reserved for future use - Maximum TCP reassembled packet:
                                                                 0x0 = 64Kbytes.
                                                                 0x1 = 256Kbytes.
                                                                 0x2-0x3 = Reserved. */
        uint64_t cq_hdr_copy           : 1;  /**< [ 18: 18](R/W) If set, the header is copied into the CQE as well as existing in the packet buffer. The
                                                                 hardware will copy all defined headers. */
        uint64_t splt_hdr_ena          : 1;  /**< [ 19: 19](R/W) When set, any packet with a valid header stack down to the end of the L4 layer has its
                                                                 header split into a separate RBDR buffer. */
        uint64_t ip6_udp_opt           : 1;  /**< [ 20: 20](R/W) IPv6/UDP checksum is optional. IPv4 allows an optional UDP checksum by sending the all-0s
                                                                 patterns. IPv6 outlaws this and the spec says to always check UDP checksum.
                                                                 0 = Spec compliant, do not allow optional code.
                                                                 1 = Treat IPv6 as IPv4; the all-0s pattern will cause a UDP checksum pass. */
        uint64_t csum_l4               : 1;  /**< [ 21: 21](R/W) Compute checksum on TCP/UDP packets. */
        uint64_t dis_apad              : 1;  /**< [ 22: 22](R/W) When set, APAD alignment function is disabled and NIC_CQE_RX_S[APAD] is always 0x0. */
        uint64_t len_l3                : 1;  /**< [ 23: 23](R/W) Check length of IPv4/IPv6. */
        uint64_t len_l4                : 1;  /**< [ 24: 24](R/W) Check length of L4. */
        uint64_t vlan_strip            : 2;  /**< [ 26: 25](R/W) Controls the stripping of any VLAN tags:
                                                                 0 = No strip.
                                                                 1 = Strip first VLAN if exists (NIC_CQE_RX_S[VV] set).
                                                                 2 = Strip second VLAN if exists (NIC_CQE_RX_S[VS] set).
                                                                 3 = Reserved. */
        uint64_t reserved_27_63        : 37;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_rq_gen_cfg_s cn8; */
    struct bdk_nic_qsx_rq_gen_cfg_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_27_63        : 37;
        uint64_t vlan_strip            : 2;  /**< [ 26: 25](R/W) Controls the stripping of any VLAN tags:
                                                                 0 = No strip.
                                                                 1 = Strip first VLAN if exists (NIC_CQE_RX_S[VV] set).
                                                                 2 = Strip second VLAN if exists (NIC_CQE_RX_S[VS] set).
                                                                 3 = Reserved. */
        uint64_t len_l4                : 1;  /**< [ 24: 24](R/W) Check length of L4. */
        uint64_t len_l3                : 1;  /**< [ 23: 23](R/W) Check length of IPv4/IPv6. */
        uint64_t reserved_22           : 1;
        uint64_t csum_l4               : 1;  /**< [ 21: 21](R/W) Compute checksum on TCP/UDP packets. */
        uint64_t ip6_udp_opt           : 1;  /**< [ 20: 20](R/W) IPv6/UDP checksum is optional. IPv4 allows an optional UDP checksum by sending the all-0s
                                                                 patterns. IPv6 outlaws this and the spec says to always check UDP checksum.
                                                                 0 = Spec compliant, do not allow optional code.
                                                                 1 = Treat IPv6 as IPv4; the all-0s pattern will cause a UDP checksum pass. */
        uint64_t splt_hdr_ena          : 1;  /**< [ 19: 19](R/W) When set, any packet with a valid header stack down to the end of the L4 layer has its
                                                                 header split into a separate RBDR buffer. */
        uint64_t cq_hdr_copy           : 1;  /**< [ 18: 18](R/W) If set, the header is copied into the CQE as well as existing in the packet buffer. The
                                                                 hardware will copy all defined headers. */
        uint64_t max_tcp_reass         : 2;  /**< [ 17: 16](R/W) Reserved.
                                                                 Internal:
                                                                 Reserved for future use - Maximum TCP reassembled packet:
                                                                 0x0 = 64Kbytes.
                                                                 0x1 = 256Kbytes.
                                                                 0x2-0x3 = Reserved. */
        uint64_t cq_pkt_size           : 8;  /**< [ 15:  8](R/W) Packet size in bytes. If a packet is smaller than this
                                                                 value, the entire packet is sent to the CQ buffer and no RB is used. Maximum number of
                                                                 bytes is 249, to allow for up to 7 byte alignment pad. */
        uint64_t later_skip            : 4;  /**< [  7:  4](R/W) Number of eight-byte words that are skipped at the beginning of other than the first RB
                                                                 for a packet. */
        uint64_t first_skip            : 4;  /**< [  3:  0](R/W) Number of eight-byte words that are skipped at the beginning of the first RB for a packet. */
#else /* Word 0 - Little Endian */
        uint64_t first_skip            : 4;  /**< [  3:  0](R/W) Number of eight-byte words that are skipped at the beginning of the first RB for a packet. */
        uint64_t later_skip            : 4;  /**< [  7:  4](R/W) Number of eight-byte words that are skipped at the beginning of other than the first RB
                                                                 for a packet. */
        uint64_t cq_pkt_size           : 8;  /**< [ 15:  8](R/W) Packet size in bytes. If a packet is smaller than this
                                                                 value, the entire packet is sent to the CQ buffer and no RB is used. Maximum number of
                                                                 bytes is 249, to allow for up to 7 byte alignment pad. */
        uint64_t max_tcp_reass         : 2;  /**< [ 17: 16](R/W) Reserved.
                                                                 Internal:
                                                                 Reserved for future use - Maximum TCP reassembled packet:
                                                                 0x0 = 64Kbytes.
                                                                 0x1 = 256Kbytes.
                                                                 0x2-0x3 = Reserved. */
        uint64_t cq_hdr_copy           : 1;  /**< [ 18: 18](R/W) If set, the header is copied into the CQE as well as existing in the packet buffer. The
                                                                 hardware will copy all defined headers. */
        uint64_t splt_hdr_ena          : 1;  /**< [ 19: 19](R/W) When set, any packet with a valid header stack down to the end of the L4 layer has its
                                                                 header split into a separate RBDR buffer. */
        uint64_t ip6_udp_opt           : 1;  /**< [ 20: 20](R/W) IPv6/UDP checksum is optional. IPv4 allows an optional UDP checksum by sending the all-0s
                                                                 patterns. IPv6 outlaws this and the spec says to always check UDP checksum.
                                                                 0 = Spec compliant, do not allow optional code.
                                                                 1 = Treat IPv6 as IPv4; the all-0s pattern will cause a UDP checksum pass. */
        uint64_t csum_l4               : 1;  /**< [ 21: 21](R/W) Compute checksum on TCP/UDP packets. */
        uint64_t reserved_22           : 1;
        uint64_t len_l3                : 1;  /**< [ 23: 23](R/W) Check length of IPv4/IPv6. */
        uint64_t len_l4                : 1;  /**< [ 24: 24](R/W) Check length of L4. */
        uint64_t vlan_strip            : 2;  /**< [ 26: 25](R/W) Controls the stripping of any VLAN tags:
                                                                 0 = No strip.
                                                                 1 = Strip first VLAN if exists (NIC_CQE_RX_S[VV] set).
                                                                 2 = Strip second VLAN if exists (NIC_CQE_RX_S[VS] set).
                                                                 3 = Reserved. */
        uint64_t reserved_27_63        : 37;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_nic_qsx_rq_gen_cfg_s cn83xx; */
};
typedef union bdk_nic_qsx_rq_gen_cfg bdk_nic_qsx_rq_gen_cfg_t;

static inline uint64_t BDK_NIC_QSX_RQ_GEN_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_RQ_GEN_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=7))
        return 0x8430a0010010ll + 0x200000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x8430a0010010ll + 0x200000ll * ((a) & 0x1f);
    __bdk_csr_fatal("NIC_QSX_RQ_GEN_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_RQ_GEN_CFG(a) bdk_nic_qsx_rq_gen_cfg_t
#define bustype_BDK_NIC_QSX_RQ_GEN_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_RQ_GEN_CFG(a) "NIC_QSX_RQ_GEN_CFG"
#define device_bar_BDK_NIC_QSX_RQ_GEN_CFG(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_RQ_GEN_CFG(a) (a)
#define arguments_BDK_NIC_QSX_RQ_GEN_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_qs#_sq#_base
 *
 * NIC Send-Queue Base-Address Registers
 */
union bdk_nic_qsx_sqx_base
{
    uint64_t u;
    struct bdk_nic_qsx_sqx_base_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t base_addr             : 42; /**< [ 48:  7](R/W/H) Base IOVA\<48:7\> of SQ ring in DRAM (VA, IPA or PA depending on SMMU
                                                                 configuration). Address bits \<6:0\> are always 0. Writes are ignored when the SQ ring is
                                                                 not empty, i.e. NIC_QS()_SQ()_HEAD[HEAD_PTR]!=NIC_QS()_SQ()_TAIL[TAIL_PTR]. */
        uint64_t reserved_0_6          : 7;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_6          : 7;
        uint64_t base_addr             : 42; /**< [ 48:  7](R/W/H) Base IOVA\<48:7\> of SQ ring in DRAM (VA, IPA or PA depending on SMMU
                                                                 configuration). Address bits \<6:0\> are always 0. Writes are ignored when the SQ ring is
                                                                 not empty, i.e. NIC_QS()_SQ()_HEAD[HEAD_PTR]!=NIC_QS()_SQ()_TAIL[TAIL_PTR]. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_sqx_base_s cn; */
};
typedef union bdk_nic_qsx_sqx_base bdk_nic_qsx_sqx_base_t;

static inline uint64_t BDK_NIC_QSX_SQX_BASE(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_SQX_BASE(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x8430a0010820ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x8430a0010820ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_QSX_SQX_BASE", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_SQX_BASE(a,b) bdk_nic_qsx_sqx_base_t
#define bustype_BDK_NIC_QSX_SQX_BASE(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_SQX_BASE(a,b) "NIC_QSX_SQX_BASE"
#define device_bar_BDK_NIC_QSX_SQX_BASE(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_SQX_BASE(a,b) (a)
#define arguments_BDK_NIC_QSX_SQX_BASE(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_sq#_cfg
 *
 * NIC Send-Queue Configuration Registers
 * Writes to all fields except for [ENA] are ignored when the SQ ring is active, which is
 * generally when:
 * * NIC_QS()_SQ()_HEAD[HEAD_PTR]!=NIC_QS()_SQ()_TAIL[TAIL_PTR], and
 * * NIC_QS()_SQ()_STATUS[STOPPED]==0.
 */
union bdk_nic_qsx_sqx_cfg
{
    uint64_t u;
    struct bdk_nic_qsx_sqx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t cq_limit              : 8;  /**< [ 31: 24](R/W/H) Threshold level for suppressing packet send, in units of 1/256th of CQ level. 0xff
                                                                 represents an empty CQ ring, 0x0 represents a full ring. Packets will not be sent from the
                                                                 SQ if the available space in the associated CQ is less than the [CQ_LIMIT] value. */
        uint64_t reserved_20_23        : 4;
        uint64_t ena                   : 1;  /**< [ 19: 19](R/W/H) Enable SQ. Software can clear this bit at any time to disable the SQ, at which time
                                                                 hardware stops servicing the SQ and sets NIC_QS()_SQ()_STATUS[STOPPED] when
                                                                 done. */
        uint64_t reserved_18           : 1;
        uint64_t reset                 : 1;  /**< [ 17: 17](WO) SQ reset. Writing a 1 resets internal state for this SQ and the following registers:
                                                                 * NIC_PF_QS()_SQ()_STAT().
                                                                 * NIC_QS()_SQ()_CFG.
                                                                 * NIC_QS()_SQ()_THRESH.
                                                                 * NIC_QS()_SQ()_BASE.
                                                                 * NIC_QS()_SQ()_HEAD.
                                                                 * NIC_QS()_SQ()_TAIL.
                                                                 * NIC_QS()_SQ()_DOOR.
                                                                 * NIC_QS()_SQ()_STATUS.
                                                                 * NIC_QS()_SQ()_STAT(). */
        uint64_t ldwb                  : 1;  /**< [ 16: 16](R/W/H) When reading SQEs for a scheduled send packet that include the last byte of the SQE cache
                                                                 line, use LDWB transaction to invalidate the cache line. When set, software must reserve
                                                                 one cache line of unused SQEs in the SQ ring, i.e. SQ should be considered full when
                                                                 NIC_QS()_SQ()_STATUS[QCOUNT] equals the SQ ring size minus 8. */
        uint64_t reserved_11_15        : 5;
        uint64_t qsize                 : 3;  /**< [ 10:  8](R/W/H) Specifies SQ ring size in entries of 16 bytes:
                                                                 0x0 = 1K entries.
                                                                 0x1 = 2K entries.
                                                                 0x2 = 4K entries.
                                                                 0x3 = 8K entries.
                                                                 0x4 = 16K entries.
                                                                 0x5 = 32K entries.
                                                                 0x6 = 64K entries.
                                                                 0x7 = Reserved.

                                                                 Note that the usable size of the ring is the specified size minus 1 when [LDWB] is clear
                                                                 (HEAD==TAIL always means empty). If [LDWB] is set, the usable size of the ring is the
                                                                 specified size minus 8. */
        uint64_t reserved_0_7          : 8;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_7          : 8;
        uint64_t qsize                 : 3;  /**< [ 10:  8](R/W/H) Specifies SQ ring size in entries of 16 bytes:
                                                                 0x0 = 1K entries.
                                                                 0x1 = 2K entries.
                                                                 0x2 = 4K entries.
                                                                 0x3 = 8K entries.
                                                                 0x4 = 16K entries.
                                                                 0x5 = 32K entries.
                                                                 0x6 = 64K entries.
                                                                 0x7 = Reserved.

                                                                 Note that the usable size of the ring is the specified size minus 1 when [LDWB] is clear
                                                                 (HEAD==TAIL always means empty). If [LDWB] is set, the usable size of the ring is the
                                                                 specified size minus 8. */
        uint64_t reserved_11_15        : 5;
        uint64_t ldwb                  : 1;  /**< [ 16: 16](R/W/H) When reading SQEs for a scheduled send packet that include the last byte of the SQE cache
                                                                 line, use LDWB transaction to invalidate the cache line. When set, software must reserve
                                                                 one cache line of unused SQEs in the SQ ring, i.e. SQ should be considered full when
                                                                 NIC_QS()_SQ()_STATUS[QCOUNT] equals the SQ ring size minus 8. */
        uint64_t reset                 : 1;  /**< [ 17: 17](WO) SQ reset. Writing a 1 resets internal state for this SQ and the following registers:
                                                                 * NIC_PF_QS()_SQ()_STAT().
                                                                 * NIC_QS()_SQ()_CFG.
                                                                 * NIC_QS()_SQ()_THRESH.
                                                                 * NIC_QS()_SQ()_BASE.
                                                                 * NIC_QS()_SQ()_HEAD.
                                                                 * NIC_QS()_SQ()_TAIL.
                                                                 * NIC_QS()_SQ()_DOOR.
                                                                 * NIC_QS()_SQ()_STATUS.
                                                                 * NIC_QS()_SQ()_STAT(). */
        uint64_t reserved_18           : 1;
        uint64_t ena                   : 1;  /**< [ 19: 19](R/W/H) Enable SQ. Software can clear this bit at any time to disable the SQ, at which time
                                                                 hardware stops servicing the SQ and sets NIC_QS()_SQ()_STATUS[STOPPED] when
                                                                 done. */
        uint64_t reserved_20_23        : 4;
        uint64_t cq_limit              : 8;  /**< [ 31: 24](R/W/H) Threshold level for suppressing packet send, in units of 1/256th of CQ level. 0xff
                                                                 represents an empty CQ ring, 0x0 represents a full ring. Packets will not be sent from the
                                                                 SQ if the available space in the associated CQ is less than the [CQ_LIMIT] value. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_sqx_cfg_s cn; */
};
typedef union bdk_nic_qsx_sqx_cfg bdk_nic_qsx_sqx_cfg_t;

static inline uint64_t BDK_NIC_QSX_SQX_CFG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_SQX_CFG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x8430a0010800ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x8430a0010800ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_QSX_SQX_CFG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_SQX_CFG(a,b) bdk_nic_qsx_sqx_cfg_t
#define bustype_BDK_NIC_QSX_SQX_CFG(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_SQX_CFG(a,b) "NIC_QSX_SQX_CFG"
#define device_bar_BDK_NIC_QSX_SQX_CFG(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_SQX_CFG(a,b) (a)
#define arguments_BDK_NIC_QSX_SQX_CFG(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_sq#_debug
 *
 * NIC Send-Queue Debug-Status Registers
 */
union bdk_nic_qsx_sqx_debug
{
    uint64_t u;
    struct bdk_nic_qsx_sqx_debug_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t dpe_ptr               : 16; /**< [ 31: 16](R/W/H) Descriptor parse engine pointer. Initialized to NIC_QS()_SQ()_HEAD[HEAD_PTR]
                                                                 when software writes that register. Advanced as queued descriptors are parsed by hardware.
                                                                 For diagnostic use only. Writes are ignored when NIC_PF_CFG[TEST_MODE] is clear. */
        uint64_t dse_ptr               : 16; /**< [ 15:  0](R/W/H) Descriptor send engine pointer. Initialized to NIC_QS()_SQ()_HEAD[HEAD_PTR] when
                                                                 software writes that register. Advanced by hardware as send packets are scheduled. For
                                                                 diagnostic use only. Writes are ignored when NIC_PF_CFG[TEST_MODE] is clear. */
#else /* Word 0 - Little Endian */
        uint64_t dse_ptr               : 16; /**< [ 15:  0](R/W/H) Descriptor send engine pointer. Initialized to NIC_QS()_SQ()_HEAD[HEAD_PTR] when
                                                                 software writes that register. Advanced by hardware as send packets are scheduled. For
                                                                 diagnostic use only. Writes are ignored when NIC_PF_CFG[TEST_MODE] is clear. */
        uint64_t dpe_ptr               : 16; /**< [ 31: 16](R/W/H) Descriptor parse engine pointer. Initialized to NIC_QS()_SQ()_HEAD[HEAD_PTR]
                                                                 when software writes that register. Advanced as queued descriptors are parsed by hardware.
                                                                 For diagnostic use only. Writes are ignored when NIC_PF_CFG[TEST_MODE] is clear. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_sqx_debug_s cn; */
};
typedef union bdk_nic_qsx_sqx_debug bdk_nic_qsx_sqx_debug_t;

static inline uint64_t BDK_NIC_QSX_SQX_DEBUG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_SQX_DEBUG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x8430a0010848ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x8430a0010848ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_QSX_SQX_DEBUG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_SQX_DEBUG(a,b) bdk_nic_qsx_sqx_debug_t
#define bustype_BDK_NIC_QSX_SQX_DEBUG(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_SQX_DEBUG(a,b) "NIC_QSX_SQX_DEBUG"
#define device_bar_BDK_NIC_QSX_SQX_DEBUG(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_SQX_DEBUG(a,b) (a)
#define arguments_BDK_NIC_QSX_SQX_DEBUG(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_sq#_door
 *
 * NIC Send-Queue Doorbell Registers
 * Software writes to this register to notify hardware that one or more entries have been enqeued
 * to the SQ ring.
 */
union bdk_nic_qsx_sqx_door
{
    uint64_t u;
    struct bdk_nic_qsx_sqx_door_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t count                 : 16; /**< [ 15:  0](WO) Number of enqueued entries (subdescriptors) of 16 bytes. Hardware advances
                                                                 NIC_QS()_SQ()_TAIL[TAIL_PTR] by this value if the SQ is enabled.

                                                                 The usable size of the ring is the size specified by NIC_QS()_SQ()_CFG[QSIZE] minus 1. As
                                                                 such, a doorbell write that would make the ring go full or overflow is suppressed and
                                                                 treated as a doorbell error. Hardware sets NIC_QS()_SQ()_STATUS[SOFT_STOP] on a doorbell
                                                                 error, stops servicing the SQ and sets NIC_QS()_SQ()_STATUS[STOPPED] when the stop
                                                                 operation is done. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 16; /**< [ 15:  0](WO) Number of enqueued entries (subdescriptors) of 16 bytes. Hardware advances
                                                                 NIC_QS()_SQ()_TAIL[TAIL_PTR] by this value if the SQ is enabled.

                                                                 The usable size of the ring is the size specified by NIC_QS()_SQ()_CFG[QSIZE] minus 1. As
                                                                 such, a doorbell write that would make the ring go full or overflow is suppressed and
                                                                 treated as a doorbell error. Hardware sets NIC_QS()_SQ()_STATUS[SOFT_STOP] on a doorbell
                                                                 error, stops servicing the SQ and sets NIC_QS()_SQ()_STATUS[STOPPED] when the stop
                                                                 operation is done. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_sqx_door_s cn; */
};
typedef union bdk_nic_qsx_sqx_door bdk_nic_qsx_sqx_door_t;

static inline uint64_t BDK_NIC_QSX_SQX_DOOR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_SQX_DOOR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x8430a0010838ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x8430a0010838ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_QSX_SQX_DOOR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_SQX_DOOR(a,b) bdk_nic_qsx_sqx_door_t
#define bustype_BDK_NIC_QSX_SQX_DOOR(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_SQX_DOOR(a,b) "NIC_QSX_SQX_DOOR"
#define device_bar_BDK_NIC_QSX_SQX_DOOR(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_SQX_DOOR(a,b) (a)
#define arguments_BDK_NIC_QSX_SQX_DOOR(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_sq#_head
 *
 * NIC Send-Queue Head Registers
 */
union bdk_nic_qsx_sqx_head
{
    uint64_t u;
    struct bdk_nic_qsx_sqx_head_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t head_ptr              : 16; /**< [ 19:  4](R/W/H) Head pointer\<19:4\> of SQ ring in DRAM relative to NIC_QS()_SQ()_BASE. Address
                                                                 bits \<3:0\> are always 0. Hardware updates this register to notify software that one or
                                                                 more entries (subdescriptors) have been dequeued from the SQ ring. Writes are ignored when
                                                                 NIC_PF_CFG[TEST_MODE] is clear. */
        uint64_t reserved_0_3          : 4;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_3          : 4;
        uint64_t head_ptr              : 16; /**< [ 19:  4](R/W/H) Head pointer\<19:4\> of SQ ring in DRAM relative to NIC_QS()_SQ()_BASE. Address
                                                                 bits \<3:0\> are always 0. Hardware updates this register to notify software that one or
                                                                 more entries (subdescriptors) have been dequeued from the SQ ring. Writes are ignored when
                                                                 NIC_PF_CFG[TEST_MODE] is clear. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_sqx_head_s cn; */
};
typedef union bdk_nic_qsx_sqx_head bdk_nic_qsx_sqx_head_t;

static inline uint64_t BDK_NIC_QSX_SQX_HEAD(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_SQX_HEAD(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x8430a0010828ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x8430a0010828ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_QSX_SQX_HEAD", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_SQX_HEAD(a,b) bdk_nic_qsx_sqx_head_t
#define bustype_BDK_NIC_QSX_SQX_HEAD(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_SQX_HEAD(a,b) "NIC_QSX_SQX_HEAD"
#define device_bar_BDK_NIC_QSX_SQX_HEAD(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_SQX_HEAD(a,b) (a)
#define arguments_BDK_NIC_QSX_SQX_HEAD(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_sq#_stat#
 *
 * NIC Send-Queue Statistics Registers
 * The third dimension indicates which statistic, and is enumerated by NIC_STAT_SQ_E.
 */
union bdk_nic_qsx_sqx_statx
{
    uint64_t u;
    struct bdk_nic_qsx_sqx_statx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t stat                  : 48; /**< [ 47:  0](RO/H) Statistic value. See also NIC_PF_QS()_SQ()_STAT() for a writable alias of this field. */
#else /* Word 0 - Little Endian */
        uint64_t stat                  : 48; /**< [ 47:  0](RO/H) Statistic value. See also NIC_PF_QS()_SQ()_STAT() for a writable alias of this field. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_sqx_statx_s cn; */
};
typedef union bdk_nic_qsx_sqx_statx bdk_nic_qsx_sqx_statx_t;

static inline uint64_t BDK_NIC_QSX_SQX_STATX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_SQX_STATX(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7) && (c<=1)))
        return 0x8430a0010900ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7) + 8ll * ((c) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7) && (c<=1)))
        return 0x8430a0010900ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7) + 8ll * ((c) & 0x1);
    __bdk_csr_fatal("NIC_QSX_SQX_STATX", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_SQX_STATX(a,b,c) bdk_nic_qsx_sqx_statx_t
#define bustype_BDK_NIC_QSX_SQX_STATX(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_SQX_STATX(a,b,c) "NIC_QSX_SQX_STATX"
#define device_bar_BDK_NIC_QSX_SQX_STATX(a,b,c) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_SQX_STATX(a,b,c) (a)
#define arguments_BDK_NIC_QSX_SQX_STATX(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB) nic_qs#_sq#_status
 *
 * NIC Send-Queue Status Registers
 */
union bdk_nic_qsx_sqx_status
{
    uint64_t u;
    struct bdk_nic_qsx_sqx_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t stopped               : 1;  /**< [ 21: 21](RO/H) NIC has stopped servicing this SQ. This bit is set along with the associated
                                                                 NIC_VF()_INT[SQ\<a\>] interrupt after hardware sets [SEND_ERR], [DPE_ERR] and/or
                                                                 [SOFT_STOP]. Software can safely reset the SQ after this bit is set by writing a 1 to
                                                                 NIC_QS()_SQ()_CFG[RESET].

                                                                 Note that CQEs added by the SQ may be in flight when the SQ is stopped; software may need
                                                                 to wait up to 50us after this bit is set to ensure that no more CQEs from the SQ are added
                                                                 to the associated CQ. */
        uint64_t send_err              : 1;  /**< [ 20: 20](RO/H) Send error. NIC sets this bit along with NIC_VF()_INT[QS_ERR] when it detects an
                                                                 error on a packet scheduled from this SQ. When this bit is set, NIC stops servicing the SQ
                                                                 and sets [STOPPED] in this register when the stop operation done. A NIC_CQE_SEND_S is
                                                                 created with NIC_CQE_SEND_S[CQE_TYPE] = NIC_CQE_TYPE_E::SEND and nonzero
                                                                 NIC_CQE_SEND_S[SEND_STATUS] for every scheduled packet that has an error until the SQ is
                                                                 stopped. */
        uint64_t dpe_err               : 1;  /**< [ 19: 19](RO/H) Descriptor parsing engine error. NIC sets this bit along with NIC_VF()_INT[QS_ERR]
                                                                 when any of the following errors is detected on a send descriptor:
                                                                 * The first SQE of the send descriptor is not NIC_SEND_HDR_S,
                                                                 i.e. NIC_SEND_HDR_S[SUBDC] != NIC_SEND_SUBDC_E::HDR.
                                                                 * NIC_SEND_HDR_S[SUBDCNT] is 0.
                                                                 * NIC_SEND_HDR_S[TOTAL] is 0.

                                                                 When this bit is set, NIC stops servicing the SQ and sets [STOPPED] in this register when
                                                                 the stop operation done. A NIC_CQE_SEND_S is not created for a descriptor error that sets
                                                                 this bit. */
        uint64_t soft_stop             : 1;  /**< [ 18: 18](RO/H) SQ stop by software CSR access. Set by one of the following:
                                                                 * Software clears NIC_QS()_SQ()_CFG[ENA].
                                                                 * A write to NIC_QS()_SQ()_DOOR causes an error.

                                                                 When this bit is set, NIC stops servicing the SQ and sets [STOPPED] in this register when
                                                                 the stop operation done. */
        uint64_t reserved_16_17        : 2;
        uint64_t qcount                : 16; /**< [ 15:  0](RO/H) Number of valid entries in the SQ. Computed by hardware from
                                                                 NIC_QS()_SQ()_CFG[QSIZE], NIC_QS()_SQ()_TAIL[TAIL_PTR] and
                                                                 NIC_QS()_SQ()_HEAD[HEAD_PTR]. */
#else /* Word 0 - Little Endian */
        uint64_t qcount                : 16; /**< [ 15:  0](RO/H) Number of valid entries in the SQ. Computed by hardware from
                                                                 NIC_QS()_SQ()_CFG[QSIZE], NIC_QS()_SQ()_TAIL[TAIL_PTR] and
                                                                 NIC_QS()_SQ()_HEAD[HEAD_PTR]. */
        uint64_t reserved_16_17        : 2;
        uint64_t soft_stop             : 1;  /**< [ 18: 18](RO/H) SQ stop by software CSR access. Set by one of the following:
                                                                 * Software clears NIC_QS()_SQ()_CFG[ENA].
                                                                 * A write to NIC_QS()_SQ()_DOOR causes an error.

                                                                 When this bit is set, NIC stops servicing the SQ and sets [STOPPED] in this register when
                                                                 the stop operation done. */
        uint64_t dpe_err               : 1;  /**< [ 19: 19](RO/H) Descriptor parsing engine error. NIC sets this bit along with NIC_VF()_INT[QS_ERR]
                                                                 when any of the following errors is detected on a send descriptor:
                                                                 * The first SQE of the send descriptor is not NIC_SEND_HDR_S,
                                                                 i.e. NIC_SEND_HDR_S[SUBDC] != NIC_SEND_SUBDC_E::HDR.
                                                                 * NIC_SEND_HDR_S[SUBDCNT] is 0.
                                                                 * NIC_SEND_HDR_S[TOTAL] is 0.

                                                                 When this bit is set, NIC stops servicing the SQ and sets [STOPPED] in this register when
                                                                 the stop operation done. A NIC_CQE_SEND_S is not created for a descriptor error that sets
                                                                 this bit. */
        uint64_t send_err              : 1;  /**< [ 20: 20](RO/H) Send error. NIC sets this bit along with NIC_VF()_INT[QS_ERR] when it detects an
                                                                 error on a packet scheduled from this SQ. When this bit is set, NIC stops servicing the SQ
                                                                 and sets [STOPPED] in this register when the stop operation done. A NIC_CQE_SEND_S is
                                                                 created with NIC_CQE_SEND_S[CQE_TYPE] = NIC_CQE_TYPE_E::SEND and nonzero
                                                                 NIC_CQE_SEND_S[SEND_STATUS] for every scheduled packet that has an error until the SQ is
                                                                 stopped. */
        uint64_t stopped               : 1;  /**< [ 21: 21](RO/H) NIC has stopped servicing this SQ. This bit is set along with the associated
                                                                 NIC_VF()_INT[SQ\<a\>] interrupt after hardware sets [SEND_ERR], [DPE_ERR] and/or
                                                                 [SOFT_STOP]. Software can safely reset the SQ after this bit is set by writing a 1 to
                                                                 NIC_QS()_SQ()_CFG[RESET].

                                                                 Note that CQEs added by the SQ may be in flight when the SQ is stopped; software may need
                                                                 to wait up to 50us after this bit is set to ensure that no more CQEs from the SQ are added
                                                                 to the associated CQ. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_sqx_status_s cn; */
};
typedef union bdk_nic_qsx_sqx_status bdk_nic_qsx_sqx_status_t;

static inline uint64_t BDK_NIC_QSX_SQX_STATUS(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_SQX_STATUS(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x8430a0010840ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x8430a0010840ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_QSX_SQX_STATUS", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_SQX_STATUS(a,b) bdk_nic_qsx_sqx_status_t
#define bustype_BDK_NIC_QSX_SQX_STATUS(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_SQX_STATUS(a,b) "NIC_QSX_SQX_STATUS"
#define device_bar_BDK_NIC_QSX_SQX_STATUS(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_SQX_STATUS(a,b) (a)
#define arguments_BDK_NIC_QSX_SQX_STATUS(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_sq#_tail
 *
 * NIC Send-Queue Tail Registers
 */
union bdk_nic_qsx_sqx_tail
{
    uint64_t u;
    struct bdk_nic_qsx_sqx_tail_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t tail_ptr              : 16; /**< [ 19:  4](R/W/H) Tail pointer\<19:4\> of SQ ring in DRAM relative to NIC_QS()_SQ()_BASE. Address
                                                                 bits \<3:0\> are always 0. This register is automatically updated when software writes to
                                                                 NIC_QS()_SQ()_DOOR. Writes are ignored when NIC_PF_CFG[TEST_MODE] is clear. */
        uint64_t reserved_0_3          : 4;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_3          : 4;
        uint64_t tail_ptr              : 16; /**< [ 19:  4](R/W/H) Tail pointer\<19:4\> of SQ ring in DRAM relative to NIC_QS()_SQ()_BASE. Address
                                                                 bits \<3:0\> are always 0. This register is automatically updated when software writes to
                                                                 NIC_QS()_SQ()_DOOR. Writes are ignored when NIC_PF_CFG[TEST_MODE] is clear. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_sqx_tail_s cn; */
};
typedef union bdk_nic_qsx_sqx_tail bdk_nic_qsx_sqx_tail_t;

static inline uint64_t BDK_NIC_QSX_SQX_TAIL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_SQX_TAIL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x8430a0010830ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x8430a0010830ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_QSX_SQX_TAIL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_SQX_TAIL(a,b) bdk_nic_qsx_sqx_tail_t
#define bustype_BDK_NIC_QSX_SQX_TAIL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_SQX_TAIL(a,b) "NIC_QSX_SQX_TAIL"
#define device_bar_BDK_NIC_QSX_SQX_TAIL(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_SQX_TAIL(a,b) (a)
#define arguments_BDK_NIC_QSX_SQX_TAIL(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_qs#_sq#_thresh
 *
 * NIC Send-Queue Threshold Registers
 */
union bdk_nic_qsx_sqx_thresh
{
    uint64_t u;
    struct bdk_nic_qsx_sqx_thresh_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t thresh                : 16; /**< [ 15:  0](R/W/H) Queue-count threshold for SQ interrupt. When nonzero, the associated
                                                                 NIC_VF()_INT[SQ] interrupt bit is set when NIC_QS()_SQ()_STATUS[QCOUNT]
                                                                 crosses [THRESH]. */
#else /* Word 0 - Little Endian */
        uint64_t thresh                : 16; /**< [ 15:  0](R/W/H) Queue-count threshold for SQ interrupt. When nonzero, the associated
                                                                 NIC_VF()_INT[SQ] interrupt bit is set when NIC_QS()_SQ()_STATUS[QCOUNT]
                                                                 crosses [THRESH]. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_qsx_sqx_thresh_s cn; */
};
typedef union bdk_nic_qsx_sqx_thresh bdk_nic_qsx_sqx_thresh_t;

static inline uint64_t BDK_NIC_QSX_SQX_THRESH(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_QSX_SQX_THRESH(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=7)))
        return 0x8430a0010810ll + 0x200000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=7)))
        return 0x8430a0010810ll + 0x200000ll * ((a) & 0x1f) + 0x40000ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_QSX_SQX_THRESH", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_QSX_SQX_THRESH(a,b) bdk_nic_qsx_sqx_thresh_t
#define bustype_BDK_NIC_QSX_SQX_THRESH(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_QSX_SQX_THRESH(a,b) "NIC_QSX_SQX_THRESH"
#define device_bar_BDK_NIC_QSX_SQX_THRESH(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_QSX_SQX_THRESH(a,b) (a)
#define arguments_BDK_NIC_QSX_SQX_THRESH(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_vf#_cfg
 *
 * NIC VF Configuration Registers
 */
union bdk_nic_vfx_cfg
{
    uint64_t u;
    struct bdk_nic_vfx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t tcp_timer_int_ena     : 1;  /**< [  0:  0](R/W) TCP timer interrupt enable. When set along with NIC_PF_TCP_TIMER[ENA],
                                                                 NIC_VF()_INT[TCP_TIMER] is set every NIC_PF_TCP_TIMER[DURATION]*256*128
                                                                 coprocessor-clock
                                                                 cycles. */
#else /* Word 0 - Little Endian */
        uint64_t tcp_timer_int_ena     : 1;  /**< [  0:  0](R/W) TCP timer interrupt enable. When set along with NIC_PF_TCP_TIMER[ENA],
                                                                 NIC_VF()_INT[TCP_TIMER] is set every NIC_PF_TCP_TIMER[DURATION]*256*128
                                                                 coprocessor-clock
                                                                 cycles. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_vfx_cfg_s cn; */
};
typedef union bdk_nic_vfx_cfg bdk_nic_vfx_cfg_t;

static inline uint64_t BDK_NIC_VFX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_VFX_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=7))
        return 0x8430a0000020ll + 0x200000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x8430a0000020ll + 0x200000ll * ((a) & 0x1f);
    __bdk_csr_fatal("NIC_VFX_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_VFX_CFG(a) bdk_nic_vfx_cfg_t
#define bustype_BDK_NIC_VFX_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_VFX_CFG(a) "NIC_VFX_CFG"
#define device_bar_BDK_NIC_VFX_CFG(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_VFX_CFG(a) (a)
#define arguments_BDK_NIC_VFX_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_vf#_ena_w1c
 *
 * NIC VF Interrupt-Enable Clear Registers
 * This register clears interrupt enable bits.
 */
union bdk_nic_vfx_ena_w1c
{
    uint64_t u;
    struct bdk_nic_vfx_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t qs_err                : 1;  /**< [ 23: 23](R/W1C/H) Reads or clears enable for NIC_VF(0..7)_INT[QS_ERR]. */
        uint64_t mbox                  : 1;  /**< [ 22: 22](R/W1C/H) Reads or clears enable for NIC_VF(0..7)_INT[MBOX]. */
        uint64_t tcp_timer             : 1;  /**< [ 21: 21](R/W1C/H) Reads or clears enable for NIC_VF(0..7)_INT[TCP_TIMER]. */
        uint64_t vnic_drop             : 1;  /**< [ 20: 20](R/W1C/H) Reads or clears enable for NIC_VF(0..7)_INT[VNIC_DROP]. */
        uint64_t reserved_18_19        : 2;
        uint64_t rbdr                  : 2;  /**< [ 17: 16](R/W1C/H) Reads or clears enable for NIC_VF(0..7)_INT[RBDR]. */
        uint64_t sq                    : 8;  /**< [ 15:  8](R/W1C/H) Reads or clears enable for NIC_VF(0..7)_INT[SQ]. */
        uint64_t cq                    : 8;  /**< [  7:  0](R/W1C/H) Reads or clears enable for NIC_VF(0..7)_INT[CQ]. */
#else /* Word 0 - Little Endian */
        uint64_t cq                    : 8;  /**< [  7:  0](R/W1C/H) Reads or clears enable for NIC_VF(0..7)_INT[CQ]. */
        uint64_t sq                    : 8;  /**< [ 15:  8](R/W1C/H) Reads or clears enable for NIC_VF(0..7)_INT[SQ]. */
        uint64_t rbdr                  : 2;  /**< [ 17: 16](R/W1C/H) Reads or clears enable for NIC_VF(0..7)_INT[RBDR]. */
        uint64_t reserved_18_19        : 2;
        uint64_t vnic_drop             : 1;  /**< [ 20: 20](R/W1C/H) Reads or clears enable for NIC_VF(0..7)_INT[VNIC_DROP]. */
        uint64_t tcp_timer             : 1;  /**< [ 21: 21](R/W1C/H) Reads or clears enable for NIC_VF(0..7)_INT[TCP_TIMER]. */
        uint64_t mbox                  : 1;  /**< [ 22: 22](R/W1C/H) Reads or clears enable for NIC_VF(0..7)_INT[MBOX]. */
        uint64_t qs_err                : 1;  /**< [ 23: 23](R/W1C/H) Reads or clears enable for NIC_VF(0..7)_INT[QS_ERR]. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_vfx_ena_w1c_s cn8; */
    /* struct bdk_nic_vfx_ena_w1c_s cn81xx; */
    struct bdk_nic_vfx_ena_w1c_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t qs_err                : 1;  /**< [ 23: 23](R/W1C/H) Reads or clears enable for NIC_VF(0..31)_INT[QS_ERR]. */
        uint64_t mbox                  : 1;  /**< [ 22: 22](R/W1C/H) Reads or clears enable for NIC_VF(0..31)_INT[MBOX]. */
        uint64_t tcp_timer             : 1;  /**< [ 21: 21](R/W1C/H) Reads or clears enable for NIC_VF(0..31)_INT[TCP_TIMER]. */
        uint64_t vnic_drop             : 1;  /**< [ 20: 20](R/W1C/H) Reads or clears enable for NIC_VF(0..31)_INT[VNIC_DROP]. */
        uint64_t reserved_18_19        : 2;
        uint64_t rbdr                  : 2;  /**< [ 17: 16](R/W1C/H) Reads or clears enable for NIC_VF(0..31)_INT[RBDR]. */
        uint64_t sq                    : 8;  /**< [ 15:  8](R/W1C/H) Reads or clears enable for NIC_VF(0..31)_INT[SQ]. */
        uint64_t cq                    : 8;  /**< [  7:  0](R/W1C/H) Reads or clears enable for NIC_VF(0..31)_INT[CQ]. */
#else /* Word 0 - Little Endian */
        uint64_t cq                    : 8;  /**< [  7:  0](R/W1C/H) Reads or clears enable for NIC_VF(0..31)_INT[CQ]. */
        uint64_t sq                    : 8;  /**< [ 15:  8](R/W1C/H) Reads or clears enable for NIC_VF(0..31)_INT[SQ]. */
        uint64_t rbdr                  : 2;  /**< [ 17: 16](R/W1C/H) Reads or clears enable for NIC_VF(0..31)_INT[RBDR]. */
        uint64_t reserved_18_19        : 2;
        uint64_t vnic_drop             : 1;  /**< [ 20: 20](R/W1C/H) Reads or clears enable for NIC_VF(0..31)_INT[VNIC_DROP]. */
        uint64_t tcp_timer             : 1;  /**< [ 21: 21](R/W1C/H) Reads or clears enable for NIC_VF(0..31)_INT[TCP_TIMER]. */
        uint64_t mbox                  : 1;  /**< [ 22: 22](R/W1C/H) Reads or clears enable for NIC_VF(0..31)_INT[MBOX]. */
        uint64_t qs_err                : 1;  /**< [ 23: 23](R/W1C/H) Reads or clears enable for NIC_VF(0..31)_INT[QS_ERR]. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_vfx_ena_w1c bdk_nic_vfx_ena_w1c_t;

static inline uint64_t BDK_NIC_VFX_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_VFX_ENA_W1C(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=7))
        return 0x8430a0000240ll + 0x200000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x8430a0000240ll + 0x200000ll * ((a) & 0x1f);
    __bdk_csr_fatal("NIC_VFX_ENA_W1C", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_VFX_ENA_W1C(a) bdk_nic_vfx_ena_w1c_t
#define bustype_BDK_NIC_VFX_ENA_W1C(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_VFX_ENA_W1C(a) "NIC_VFX_ENA_W1C"
#define device_bar_BDK_NIC_VFX_ENA_W1C(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_VFX_ENA_W1C(a) (a)
#define arguments_BDK_NIC_VFX_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_vf#_ena_w1s
 *
 * NIC VF Interrupt-Enable Set Registers
 * This register sets interrupt enable bits.
 */
union bdk_nic_vfx_ena_w1s
{
    uint64_t u;
    struct bdk_nic_vfx_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t qs_err                : 1;  /**< [ 23: 23](R/W1S/H) Reads or sets enable for NIC_VF(0..7)_INT[QS_ERR]. */
        uint64_t mbox                  : 1;  /**< [ 22: 22](R/W1S/H) Reads or sets enable for NIC_VF(0..7)_INT[MBOX]. */
        uint64_t tcp_timer             : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets enable for NIC_VF(0..7)_INT[TCP_TIMER]. */
        uint64_t vnic_drop             : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets enable for NIC_VF(0..7)_INT[VNIC_DROP]. */
        uint64_t reserved_18_19        : 2;
        uint64_t rbdr                  : 2;  /**< [ 17: 16](R/W1S/H) Reads or sets enable for NIC_VF(0..7)_INT[RBDR]. */
        uint64_t sq                    : 8;  /**< [ 15:  8](R/W1S/H) Reads or sets enable for NIC_VF(0..7)_INT[SQ]. */
        uint64_t cq                    : 8;  /**< [  7:  0](R/W1S/H) Reads or sets enable for NIC_VF(0..7)_INT[CQ]. */
#else /* Word 0 - Little Endian */
        uint64_t cq                    : 8;  /**< [  7:  0](R/W1S/H) Reads or sets enable for NIC_VF(0..7)_INT[CQ]. */
        uint64_t sq                    : 8;  /**< [ 15:  8](R/W1S/H) Reads or sets enable for NIC_VF(0..7)_INT[SQ]. */
        uint64_t rbdr                  : 2;  /**< [ 17: 16](R/W1S/H) Reads or sets enable for NIC_VF(0..7)_INT[RBDR]. */
        uint64_t reserved_18_19        : 2;
        uint64_t vnic_drop             : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets enable for NIC_VF(0..7)_INT[VNIC_DROP]. */
        uint64_t tcp_timer             : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets enable for NIC_VF(0..7)_INT[TCP_TIMER]. */
        uint64_t mbox                  : 1;  /**< [ 22: 22](R/W1S/H) Reads or sets enable for NIC_VF(0..7)_INT[MBOX]. */
        uint64_t qs_err                : 1;  /**< [ 23: 23](R/W1S/H) Reads or sets enable for NIC_VF(0..7)_INT[QS_ERR]. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_vfx_ena_w1s_s cn8; */
    /* struct bdk_nic_vfx_ena_w1s_s cn81xx; */
    struct bdk_nic_vfx_ena_w1s_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t qs_err                : 1;  /**< [ 23: 23](R/W1S/H) Reads or sets enable for NIC_VF(0..31)_INT[QS_ERR]. */
        uint64_t mbox                  : 1;  /**< [ 22: 22](R/W1S/H) Reads or sets enable for NIC_VF(0..31)_INT[MBOX]. */
        uint64_t tcp_timer             : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets enable for NIC_VF(0..31)_INT[TCP_TIMER]. */
        uint64_t vnic_drop             : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets enable for NIC_VF(0..31)_INT[VNIC_DROP]. */
        uint64_t reserved_18_19        : 2;
        uint64_t rbdr                  : 2;  /**< [ 17: 16](R/W1S/H) Reads or sets enable for NIC_VF(0..31)_INT[RBDR]. */
        uint64_t sq                    : 8;  /**< [ 15:  8](R/W1S/H) Reads or sets enable for NIC_VF(0..31)_INT[SQ]. */
        uint64_t cq                    : 8;  /**< [  7:  0](R/W1S/H) Reads or sets enable for NIC_VF(0..31)_INT[CQ]. */
#else /* Word 0 - Little Endian */
        uint64_t cq                    : 8;  /**< [  7:  0](R/W1S/H) Reads or sets enable for NIC_VF(0..31)_INT[CQ]. */
        uint64_t sq                    : 8;  /**< [ 15:  8](R/W1S/H) Reads or sets enable for NIC_VF(0..31)_INT[SQ]. */
        uint64_t rbdr                  : 2;  /**< [ 17: 16](R/W1S/H) Reads or sets enable for NIC_VF(0..31)_INT[RBDR]. */
        uint64_t reserved_18_19        : 2;
        uint64_t vnic_drop             : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets enable for NIC_VF(0..31)_INT[VNIC_DROP]. */
        uint64_t tcp_timer             : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets enable for NIC_VF(0..31)_INT[TCP_TIMER]. */
        uint64_t mbox                  : 1;  /**< [ 22: 22](R/W1S/H) Reads or sets enable for NIC_VF(0..31)_INT[MBOX]. */
        uint64_t qs_err                : 1;  /**< [ 23: 23](R/W1S/H) Reads or sets enable for NIC_VF(0..31)_INT[QS_ERR]. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_vfx_ena_w1s bdk_nic_vfx_ena_w1s_t;

static inline uint64_t BDK_NIC_VFX_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_VFX_ENA_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=7))
        return 0x8430a0000260ll + 0x200000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x8430a0000260ll + 0x200000ll * ((a) & 0x1f);
    __bdk_csr_fatal("NIC_VFX_ENA_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_VFX_ENA_W1S(a) bdk_nic_vfx_ena_w1s_t
#define bustype_BDK_NIC_VFX_ENA_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_VFX_ENA_W1S(a) "NIC_VFX_ENA_W1S"
#define device_bar_BDK_NIC_VFX_ENA_W1S(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_VFX_ENA_W1S(a) (a)
#define arguments_BDK_NIC_VFX_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_vf#_int
 *
 * NIC VF Interrupt Registers
 */
union bdk_nic_vfx_int
{
    uint64_t u;
    struct bdk_nic_vfx_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t qs_err                : 1;  /**< [ 23: 23](R/W1C/H) Queue set error. Set when a CQ, SQ or RBDR in the QS has an error, as follows:
                                                                 * A completion queue's NIC_QS()_CQ()_STATUS[CQ_WR_FULL] bit is set.
                                                                 * A completion queue's NIC_QS()_CQ()_STATUS[CQ_WR_DISABLE] bit is set.
                                                                 * A completion queue's NIC_QS()_CQ()_STATUS[CQ_WR_FAULT] bit is set.
                                                                 * A send queue's NIC_QS()_SQ()_STATUS[SEND_ERR] or
                                                                 NIC_QS()_SQ()_STATUS[DPE_ERR] bit is set.
                                                                 * An RBDR's NIC_QS()_RBDR()_STATUS0[FIFO_STATE] field transitions to FAIL. */
        uint64_t mbox                  : 1;  /**< [ 22: 22](R/W1C/H) PF to VF mailbox interrupt. Set when the NIC_PF_VF(0..7)_MBOX(0) register is written. */
        uint64_t tcp_timer             : 1;  /**< [ 21: 21](R/W1C/H) TCP timer interrupt. Enabled when NIC_PF_TCP_TIMER[ENA] and
                                                                 NIC_VF()_CFG[TCP_TIMER_INT_ENA] are both set. Set every
                                                                 NIC_PF_TCP_TIMER[DURATION]*256*128 coprocessor cycles when enabled. */
        uint64_t vnic_drop             : 1;  /**< [ 20: 20](R/W1C/H) Packet dropped interrupt. Hardware sets this bit and generates an interrupt message when
                                                                 any packet has been dropped. This is intended for diagnostic use; typical production
                                                                 software will want this interrupt disabled.
                                                                 Note the interrupt is posted to the VNIC's base VF, i.e. the VF number that matches the
                                                                 dropped packet's VNIC number. For example, if NIC_PF_QS(2)_CFG[VNIC] = 1, then a dropped
                                                                 packet by QS 2 will set NIC_VF(1)_INT[VNIC_DROP]. */
        uint64_t reserved_18_19        : 2;
        uint64_t rbdr                  : 2;  /**< [ 17: 16](R/W1C/H) RBDR interrupt. One bit for each RBDR in the QS. Hardware sets each bit and generates
                                                                 an interrupt message under any of the following condition for its RBDR:
                                                                 * NIC_QS()_RBDR()_THRESH is nonzero and
                                                                 NIC_QS()_RBDR()_STATUS0[QCOUNT] crosses NIC_QS()_RBDR()_THRESH when
                                                                 hardware advances NIC_QS()_RBDR()_HEAD or NIC_QS()_RBDR()_TAIL.

                                                                 Subsequent interrupt messages are only generated after the bit has been cleared by
                                                                 software. */
        uint64_t sq                    : 8;  /**< [ 15:  8](R/W1C/H) Send queue interrupt. One bit for each SQ in the QS. Hardware sets each bit and generates
                                                                 an interrupt message under any of the following conditions for its send queue:
                                                                 * NIC_QS()_SQ()_THRESH is nonzero and NIC_QS()_SQ()_STATUS[QCOUNT]
                                                                 crosses NIC_QS()_SQ()_THRESH when hardware advances NIC_QS()_SQ()_HEAD
                                                                 or NIC_QS()_SQ()_TAIL.
                                                                 * NIC_QS()_SQ()_STATUS[STOPPED] is set.

                                                                 Subsequent interrupt messages are only generated after the bit has been cleared by
                                                                 software. */
        uint64_t cq                    : 8;  /**< [  7:  0](R/W1C/H) Completion queue interrupt. One bit for each CQ in the QS. Hardware sets each bit and
                                                                 generates an interrupt message under any of the following conditions for its completion
                                                                 queue:
                                                                 * NIC_QS()_CQ()_STATUS2[TIMER_EN]=1 and NIC_QS()_CQ()_STATUS2[GLOBAL_TIME] crosses
                                                                 NIC_QS()_CQ()_STATUS2[INT_TIMER].
                                                                 * NIC_QS()_CQ()_STATUS[QCOUNT] increases to equal NIC_QS()_CQ()_THRESH when hardware
                                                                 advances NIC_QS()_CQ()_TAIL.
                                                                 * NIC_QS()_CQ()_THRESH is nonzero and NIC_QS()_CQ()_STATUS[QCOUNT] \>=
                                                                 NIC_QS()_CQ()_THRESH when software writes a 1 to clear this bit.

                                                                 Subsequent interrupt messages are only generated after the bit has been cleared by
                                                                 software. */
#else /* Word 0 - Little Endian */
        uint64_t cq                    : 8;  /**< [  7:  0](R/W1C/H) Completion queue interrupt. One bit for each CQ in the QS. Hardware sets each bit and
                                                                 generates an interrupt message under any of the following conditions for its completion
                                                                 queue:
                                                                 * NIC_QS()_CQ()_STATUS2[TIMER_EN]=1 and NIC_QS()_CQ()_STATUS2[GLOBAL_TIME] crosses
                                                                 NIC_QS()_CQ()_STATUS2[INT_TIMER].
                                                                 * NIC_QS()_CQ()_STATUS[QCOUNT] increases to equal NIC_QS()_CQ()_THRESH when hardware
                                                                 advances NIC_QS()_CQ()_TAIL.
                                                                 * NIC_QS()_CQ()_THRESH is nonzero and NIC_QS()_CQ()_STATUS[QCOUNT] \>=
                                                                 NIC_QS()_CQ()_THRESH when software writes a 1 to clear this bit.

                                                                 Subsequent interrupt messages are only generated after the bit has been cleared by
                                                                 software. */
        uint64_t sq                    : 8;  /**< [ 15:  8](R/W1C/H) Send queue interrupt. One bit for each SQ in the QS. Hardware sets each bit and generates
                                                                 an interrupt message under any of the following conditions for its send queue:
                                                                 * NIC_QS()_SQ()_THRESH is nonzero and NIC_QS()_SQ()_STATUS[QCOUNT]
                                                                 crosses NIC_QS()_SQ()_THRESH when hardware advances NIC_QS()_SQ()_HEAD
                                                                 or NIC_QS()_SQ()_TAIL.
                                                                 * NIC_QS()_SQ()_STATUS[STOPPED] is set.

                                                                 Subsequent interrupt messages are only generated after the bit has been cleared by
                                                                 software. */
        uint64_t rbdr                  : 2;  /**< [ 17: 16](R/W1C/H) RBDR interrupt. One bit for each RBDR in the QS. Hardware sets each bit and generates
                                                                 an interrupt message under any of the following condition for its RBDR:
                                                                 * NIC_QS()_RBDR()_THRESH is nonzero and
                                                                 NIC_QS()_RBDR()_STATUS0[QCOUNT] crosses NIC_QS()_RBDR()_THRESH when
                                                                 hardware advances NIC_QS()_RBDR()_HEAD or NIC_QS()_RBDR()_TAIL.

                                                                 Subsequent interrupt messages are only generated after the bit has been cleared by
                                                                 software. */
        uint64_t reserved_18_19        : 2;
        uint64_t vnic_drop             : 1;  /**< [ 20: 20](R/W1C/H) Packet dropped interrupt. Hardware sets this bit and generates an interrupt message when
                                                                 any packet has been dropped. This is intended for diagnostic use; typical production
                                                                 software will want this interrupt disabled.
                                                                 Note the interrupt is posted to the VNIC's base VF, i.e. the VF number that matches the
                                                                 dropped packet's VNIC number. For example, if NIC_PF_QS(2)_CFG[VNIC] = 1, then a dropped
                                                                 packet by QS 2 will set NIC_VF(1)_INT[VNIC_DROP]. */
        uint64_t tcp_timer             : 1;  /**< [ 21: 21](R/W1C/H) TCP timer interrupt. Enabled when NIC_PF_TCP_TIMER[ENA] and
                                                                 NIC_VF()_CFG[TCP_TIMER_INT_ENA] are both set. Set every
                                                                 NIC_PF_TCP_TIMER[DURATION]*256*128 coprocessor cycles when enabled. */
        uint64_t mbox                  : 1;  /**< [ 22: 22](R/W1C/H) PF to VF mailbox interrupt. Set when the NIC_PF_VF(0..7)_MBOX(0) register is written. */
        uint64_t qs_err                : 1;  /**< [ 23: 23](R/W1C/H) Queue set error. Set when a CQ, SQ or RBDR in the QS has an error, as follows:
                                                                 * A completion queue's NIC_QS()_CQ()_STATUS[CQ_WR_FULL] bit is set.
                                                                 * A completion queue's NIC_QS()_CQ()_STATUS[CQ_WR_DISABLE] bit is set.
                                                                 * A completion queue's NIC_QS()_CQ()_STATUS[CQ_WR_FAULT] bit is set.
                                                                 * A send queue's NIC_QS()_SQ()_STATUS[SEND_ERR] or
                                                                 NIC_QS()_SQ()_STATUS[DPE_ERR] bit is set.
                                                                 * An RBDR's NIC_QS()_RBDR()_STATUS0[FIFO_STATE] field transitions to FAIL. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_vfx_int_s cn8; */
    /* struct bdk_nic_vfx_int_s cn81xx; */
    struct bdk_nic_vfx_int_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t qs_err                : 1;  /**< [ 23: 23](R/W1C/H) Queue set error. Set when a CQ, SQ or RBDR in the QS has an error, as follows:
                                                                 * A completion queue's NIC_QS()_CQ()_STATUS[CQ_WR_FULL] bit is set.
                                                                 * A completion queue's NIC_QS()_CQ()_STATUS[CQ_WR_DISABLE] bit is set.
                                                                 * A completion queue's NIC_QS()_CQ()_STATUS[CQ_WR_FAULT] bit is set.
                                                                 * A send queue's NIC_QS()_SQ()_STATUS[SEND_ERR] or
                                                                 NIC_QS()_SQ()_STATUS[DPE_ERR] bit is set.
                                                                 * An RBDR's NIC_QS()_RBDR()_STATUS0[FIFO_STATE] field transitions to FAIL. */
        uint64_t mbox                  : 1;  /**< [ 22: 22](R/W1C/H) PF to VF mailbox interrupt. Set when the NIC_PF_VF(0..31)_MBOX(0) register is written. */
        uint64_t tcp_timer             : 1;  /**< [ 21: 21](R/W1C/H) TCP timer interrupt. Enabled when NIC_PF_TCP_TIMER[ENA] and
                                                                 NIC_VF()_CFG[TCP_TIMER_INT_ENA] are both set. Set every
                                                                 NIC_PF_TCP_TIMER[DURATION]*256*128 coprocessor cycles when enabled. */
        uint64_t vnic_drop             : 1;  /**< [ 20: 20](R/W1C/H) Packet dropped interrupt. Hardware sets this bit and generates an interrupt message when
                                                                 any packet has been dropped. This is intended for diagnostic use; typical production
                                                                 software will want this interrupt disabled.
                                                                 Note the interrupt is posted to the VNIC's base VF, i.e. the VF number that matches the
                                                                 dropped packet's VNIC number. For example, if NIC_PF_QS(2)_CFG[VNIC] = 1, then a dropped
                                                                 packet by QS 2 will set NIC_VF(1)_INT[VNIC_DROP]. */
        uint64_t reserved_18_19        : 2;
        uint64_t rbdr                  : 2;  /**< [ 17: 16](R/W1C/H) RBDR interrupt. One bit for each RBDR in the QS. Hardware sets each bit and generates
                                                                 an interrupt message under any of the following condition for its RBDR:
                                                                 * NIC_QS()_RBDR()_THRESH is nonzero and
                                                                 NIC_QS()_RBDR()_STATUS0[QCOUNT] crosses NIC_QS()_RBDR()_THRESH when
                                                                 hardware advances NIC_QS()_RBDR()_HEAD or NIC_QS()_RBDR()_TAIL.

                                                                 Subsequent interrupt messages are only generated after the bit has been cleared by
                                                                 software. */
        uint64_t sq                    : 8;  /**< [ 15:  8](R/W1C/H) Send queue interrupt. One bit for each SQ in the QS. Hardware sets each bit and generates
                                                                 an interrupt message under any of the following conditions for its send queue:
                                                                 * NIC_QS()_SQ()_THRESH is nonzero and NIC_QS()_SQ()_STATUS[QCOUNT]
                                                                 crosses NIC_QS()_SQ()_THRESH when hardware advances NIC_QS()_SQ()_HEAD
                                                                 or NIC_QS()_SQ()_TAIL.
                                                                 * NIC_QS()_SQ()_STATUS[STOPPED] is set.

                                                                 Subsequent interrupt messages are only generated after the bit has been cleared by
                                                                 software. */
        uint64_t cq                    : 8;  /**< [  7:  0](R/W1C/H) Completion queue interrupt. One bit for each CQ in the QS. Hardware sets each bit and
                                                                 generates an interrupt message under any of the following conditions for its completion
                                                                 queue:
                                                                 * NIC_QS()_CQ()_STATUS2[TIMER_EN]=1 and NIC_QS()_CQ()_STATUS2[GLOBAL_TIME] crosses
                                                                 NIC_QS()_CQ()_STATUS2[INT_TIMER].
                                                                 * NIC_QS()_CQ()_STATUS[QCOUNT] increases to equal NIC_QS()_CQ()_THRESH when hardware
                                                                 advances NIC_QS()_CQ()_TAIL.
                                                                 * NIC_QS()_CQ()_THRESH is nonzero and NIC_QS()_CQ()_STATUS[QCOUNT] \>=
                                                                 NIC_QS()_CQ()_THRESH when software writes a 1 to clear this bit.

                                                                 Subsequent interrupt messages are only generated after the bit has been cleared by
                                                                 software. */
#else /* Word 0 - Little Endian */
        uint64_t cq                    : 8;  /**< [  7:  0](R/W1C/H) Completion queue interrupt. One bit for each CQ in the QS. Hardware sets each bit and
                                                                 generates an interrupt message under any of the following conditions for its completion
                                                                 queue:
                                                                 * NIC_QS()_CQ()_STATUS2[TIMER_EN]=1 and NIC_QS()_CQ()_STATUS2[GLOBAL_TIME] crosses
                                                                 NIC_QS()_CQ()_STATUS2[INT_TIMER].
                                                                 * NIC_QS()_CQ()_STATUS[QCOUNT] increases to equal NIC_QS()_CQ()_THRESH when hardware
                                                                 advances NIC_QS()_CQ()_TAIL.
                                                                 * NIC_QS()_CQ()_THRESH is nonzero and NIC_QS()_CQ()_STATUS[QCOUNT] \>=
                                                                 NIC_QS()_CQ()_THRESH when software writes a 1 to clear this bit.

                                                                 Subsequent interrupt messages are only generated after the bit has been cleared by
                                                                 software. */
        uint64_t sq                    : 8;  /**< [ 15:  8](R/W1C/H) Send queue interrupt. One bit for each SQ in the QS. Hardware sets each bit and generates
                                                                 an interrupt message under any of the following conditions for its send queue:
                                                                 * NIC_QS()_SQ()_THRESH is nonzero and NIC_QS()_SQ()_STATUS[QCOUNT]
                                                                 crosses NIC_QS()_SQ()_THRESH when hardware advances NIC_QS()_SQ()_HEAD
                                                                 or NIC_QS()_SQ()_TAIL.
                                                                 * NIC_QS()_SQ()_STATUS[STOPPED] is set.

                                                                 Subsequent interrupt messages are only generated after the bit has been cleared by
                                                                 software. */
        uint64_t rbdr                  : 2;  /**< [ 17: 16](R/W1C/H) RBDR interrupt. One bit for each RBDR in the QS. Hardware sets each bit and generates
                                                                 an interrupt message under any of the following condition for its RBDR:
                                                                 * NIC_QS()_RBDR()_THRESH is nonzero and
                                                                 NIC_QS()_RBDR()_STATUS0[QCOUNT] crosses NIC_QS()_RBDR()_THRESH when
                                                                 hardware advances NIC_QS()_RBDR()_HEAD or NIC_QS()_RBDR()_TAIL.

                                                                 Subsequent interrupt messages are only generated after the bit has been cleared by
                                                                 software. */
        uint64_t reserved_18_19        : 2;
        uint64_t vnic_drop             : 1;  /**< [ 20: 20](R/W1C/H) Packet dropped interrupt. Hardware sets this bit and generates an interrupt message when
                                                                 any packet has been dropped. This is intended for diagnostic use; typical production
                                                                 software will want this interrupt disabled.
                                                                 Note the interrupt is posted to the VNIC's base VF, i.e. the VF number that matches the
                                                                 dropped packet's VNIC number. For example, if NIC_PF_QS(2)_CFG[VNIC] = 1, then a dropped
                                                                 packet by QS 2 will set NIC_VF(1)_INT[VNIC_DROP]. */
        uint64_t tcp_timer             : 1;  /**< [ 21: 21](R/W1C/H) TCP timer interrupt. Enabled when NIC_PF_TCP_TIMER[ENA] and
                                                                 NIC_VF()_CFG[TCP_TIMER_INT_ENA] are both set. Set every
                                                                 NIC_PF_TCP_TIMER[DURATION]*256*128 coprocessor cycles when enabled. */
        uint64_t mbox                  : 1;  /**< [ 22: 22](R/W1C/H) PF to VF mailbox interrupt. Set when the NIC_PF_VF(0..31)_MBOX(0) register is written. */
        uint64_t qs_err                : 1;  /**< [ 23: 23](R/W1C/H) Queue set error. Set when a CQ, SQ or RBDR in the QS has an error, as follows:
                                                                 * A completion queue's NIC_QS()_CQ()_STATUS[CQ_WR_FULL] bit is set.
                                                                 * A completion queue's NIC_QS()_CQ()_STATUS[CQ_WR_DISABLE] bit is set.
                                                                 * A completion queue's NIC_QS()_CQ()_STATUS[CQ_WR_FAULT] bit is set.
                                                                 * A send queue's NIC_QS()_SQ()_STATUS[SEND_ERR] or
                                                                 NIC_QS()_SQ()_STATUS[DPE_ERR] bit is set.
                                                                 * An RBDR's NIC_QS()_RBDR()_STATUS0[FIFO_STATE] field transitions to FAIL. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_vfx_int bdk_nic_vfx_int_t;

static inline uint64_t BDK_NIC_VFX_INT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_VFX_INT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=7))
        return 0x8430a0000200ll + 0x200000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x8430a0000200ll + 0x200000ll * ((a) & 0x1f);
    __bdk_csr_fatal("NIC_VFX_INT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_VFX_INT(a) bdk_nic_vfx_int_t
#define bustype_BDK_NIC_VFX_INT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_VFX_INT(a) "NIC_VFX_INT"
#define device_bar_BDK_NIC_VFX_INT(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_VFX_INT(a) (a)
#define arguments_BDK_NIC_VFX_INT(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_vf#_int_w1s
 *
 * NIC VF Interrupt-Set Registers
 * This register sets interrupt bits.
 */
union bdk_nic_vfx_int_w1s
{
    uint64_t u;
    struct bdk_nic_vfx_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t qs_err                : 1;  /**< [ 23: 23](R/W1S/H) Reads or sets NIC_VF(0..7)_INT[QS_ERR]. */
        uint64_t mbox                  : 1;  /**< [ 22: 22](R/W1S/H) Reads or sets NIC_VF(0..7)_INT[MBOX]. */
        uint64_t tcp_timer             : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets NIC_VF(0..7)_INT[TCP_TIMER]. */
        uint64_t vnic_drop             : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets NIC_VF(0..7)_INT[VNIC_DROP]. */
        uint64_t reserved_18_19        : 2;
        uint64_t rbdr                  : 2;  /**< [ 17: 16](R/W1S/H) Reads or sets NIC_VF(0..7)_INT[RBDR]. */
        uint64_t sq                    : 8;  /**< [ 15:  8](R/W1S/H) Reads or sets NIC_VF(0..7)_INT[SQ]. */
        uint64_t cq                    : 8;  /**< [  7:  0](R/W1S/H) Reads or sets NIC_VF(0..7)_INT[CQ]. */
#else /* Word 0 - Little Endian */
        uint64_t cq                    : 8;  /**< [  7:  0](R/W1S/H) Reads or sets NIC_VF(0..7)_INT[CQ]. */
        uint64_t sq                    : 8;  /**< [ 15:  8](R/W1S/H) Reads or sets NIC_VF(0..7)_INT[SQ]. */
        uint64_t rbdr                  : 2;  /**< [ 17: 16](R/W1S/H) Reads or sets NIC_VF(0..7)_INT[RBDR]. */
        uint64_t reserved_18_19        : 2;
        uint64_t vnic_drop             : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets NIC_VF(0..7)_INT[VNIC_DROP]. */
        uint64_t tcp_timer             : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets NIC_VF(0..7)_INT[TCP_TIMER]. */
        uint64_t mbox                  : 1;  /**< [ 22: 22](R/W1S/H) Reads or sets NIC_VF(0..7)_INT[MBOX]. */
        uint64_t qs_err                : 1;  /**< [ 23: 23](R/W1S/H) Reads or sets NIC_VF(0..7)_INT[QS_ERR]. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_vfx_int_w1s_s cn8; */
    /* struct bdk_nic_vfx_int_w1s_s cn81xx; */
    struct bdk_nic_vfx_int_w1s_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t qs_err                : 1;  /**< [ 23: 23](R/W1S/H) Reads or sets NIC_VF(0..31)_INT[QS_ERR]. */
        uint64_t mbox                  : 1;  /**< [ 22: 22](R/W1S/H) Reads or sets NIC_VF(0..31)_INT[MBOX]. */
        uint64_t tcp_timer             : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets NIC_VF(0..31)_INT[TCP_TIMER]. */
        uint64_t vnic_drop             : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets NIC_VF(0..31)_INT[VNIC_DROP]. */
        uint64_t reserved_18_19        : 2;
        uint64_t rbdr                  : 2;  /**< [ 17: 16](R/W1S/H) Reads or sets NIC_VF(0..31)_INT[RBDR]. */
        uint64_t sq                    : 8;  /**< [ 15:  8](R/W1S/H) Reads or sets NIC_VF(0..31)_INT[SQ]. */
        uint64_t cq                    : 8;  /**< [  7:  0](R/W1S/H) Reads or sets NIC_VF(0..31)_INT[CQ]. */
#else /* Word 0 - Little Endian */
        uint64_t cq                    : 8;  /**< [  7:  0](R/W1S/H) Reads or sets NIC_VF(0..31)_INT[CQ]. */
        uint64_t sq                    : 8;  /**< [ 15:  8](R/W1S/H) Reads or sets NIC_VF(0..31)_INT[SQ]. */
        uint64_t rbdr                  : 2;  /**< [ 17: 16](R/W1S/H) Reads or sets NIC_VF(0..31)_INT[RBDR]. */
        uint64_t reserved_18_19        : 2;
        uint64_t vnic_drop             : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets NIC_VF(0..31)_INT[VNIC_DROP]. */
        uint64_t tcp_timer             : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets NIC_VF(0..31)_INT[TCP_TIMER]. */
        uint64_t mbox                  : 1;  /**< [ 22: 22](R/W1S/H) Reads or sets NIC_VF(0..31)_INT[MBOX]. */
        uint64_t qs_err                : 1;  /**< [ 23: 23](R/W1S/H) Reads or sets NIC_VF(0..31)_INT[QS_ERR]. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_nic_vfx_int_w1s bdk_nic_vfx_int_w1s_t;

static inline uint64_t BDK_NIC_VFX_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_VFX_INT_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=7))
        return 0x8430a0000220ll + 0x200000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x8430a0000220ll + 0x200000ll * ((a) & 0x1f);
    __bdk_csr_fatal("NIC_VFX_INT_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_VFX_INT_W1S(a) bdk_nic_vfx_int_w1s_t
#define bustype_BDK_NIC_VFX_INT_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_VFX_INT_W1S(a) "NIC_VFX_INT_W1S"
#define device_bar_BDK_NIC_VFX_INT_W1S(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_VFX_INT_W1S(a) (a)
#define arguments_BDK_NIC_VFX_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_vf#_msix_pba#
 *
 * NIC VF MSI-X Pending-Bit-Array Registers
 * This register is the MSI-X PBA table, the bit number is indexed by the NIC_VF_INT_VEC_E
 * enumeration.
 */
union bdk_nic_vfx_msix_pbax
{
    uint64_t u;
    struct bdk_nic_vfx_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated NIC_VF()_MSIX_VEC()_CTL, enumerated by
                                                                 NIC_VF_INT_VEC_E. Bits that have no associated NIC_VF_INT_VEC_E are zero. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated NIC_VF()_MSIX_VEC()_CTL, enumerated by
                                                                 NIC_VF_INT_VEC_E. Bits that have no associated NIC_VF_INT_VEC_E are zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_vfx_msix_pbax_s cn; */
};
typedef union bdk_nic_vfx_msix_pbax bdk_nic_vfx_msix_pbax_t;

static inline uint64_t BDK_NIC_VFX_MSIX_PBAX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_VFX_MSIX_PBAX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b==0)))
        return 0x8430e00f0000ll + 0x200000ll * ((a) & 0x7) + 8ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b==0)))
        return 0x8430e00f0000ll + 0x200000ll * ((a) & 0x1f) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("NIC_VFX_MSIX_PBAX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_VFX_MSIX_PBAX(a,b) bdk_nic_vfx_msix_pbax_t
#define bustype_BDK_NIC_VFX_MSIX_PBAX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_VFX_MSIX_PBAX(a,b) "NIC_VFX_MSIX_PBAX"
#define device_bar_BDK_NIC_VFX_MSIX_PBAX(a,b) 0x4 /* VF_BAR4 */
#define busnum_BDK_NIC_VFX_MSIX_PBAX(a,b) (a)
#define arguments_BDK_NIC_VFX_MSIX_PBAX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_vf#_msix_vec#_addr
 *
 * NIC VF MSI-X Vector-Table Address Registers
 * This register is the MSI-X vector table, indexed by the NIC_VF_INT_VEC_E enumeration.
 */
union bdk_nic_vfx_msix_vecx_addr
{
    uint64_t u;
    struct bdk_nic_vfx_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](RAZ) Secure vector. Zero as not supported on a per-vector basis for VFs; use
                                                                 PCCPF_NIC_VSEC_SCTL[MSIX_SEC] instead (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]). */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](RAZ) Secure vector. Zero as not supported on a per-vector basis for VFs; use
                                                                 PCCPF_NIC_VSEC_SCTL[MSIX_SEC] instead (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]). */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_vfx_msix_vecx_addr_s cn; */
};
typedef union bdk_nic_vfx_msix_vecx_addr bdk_nic_vfx_msix_vecx_addr_t;

static inline uint64_t BDK_NIC_VFX_MSIX_VECX_ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_VFX_MSIX_VECX_ADDR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=19)))
        return 0x8430e0000000ll + 0x200000ll * ((a) & 0x7) + 0x10ll * ((b) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=19)))
        return 0x8430e0000000ll + 0x200000ll * ((a) & 0x1f) + 0x10ll * ((b) & 0x1f);
    __bdk_csr_fatal("NIC_VFX_MSIX_VECX_ADDR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_VFX_MSIX_VECX_ADDR(a,b) bdk_nic_vfx_msix_vecx_addr_t
#define bustype_BDK_NIC_VFX_MSIX_VECX_ADDR(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_VFX_MSIX_VECX_ADDR(a,b) "NIC_VFX_MSIX_VECX_ADDR"
#define device_bar_BDK_NIC_VFX_MSIX_VECX_ADDR(a,b) 0x4 /* VF_BAR4 */
#define busnum_BDK_NIC_VFX_MSIX_VECX_ADDR(a,b) (a)
#define arguments_BDK_NIC_VFX_MSIX_VECX_ADDR(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_vf#_msix_vec#_ctl
 *
 * NIC VF MSI-X Vector-Table Control and Data Registers
 * This register is the MSI-X vector table, indexed by the NIC_VF_INT_VEC_E enumeration.
 */
union bdk_nic_vfx_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_nic_vfx_msix_vecx_ctl_s
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
    /* struct bdk_nic_vfx_msix_vecx_ctl_s cn; */
};
typedef union bdk_nic_vfx_msix_vecx_ctl bdk_nic_vfx_msix_vecx_ctl_t;

static inline uint64_t BDK_NIC_VFX_MSIX_VECX_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_VFX_MSIX_VECX_CTL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=19)))
        return 0x8430e0000008ll + 0x200000ll * ((a) & 0x7) + 0x10ll * ((b) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=19)))
        return 0x8430e0000008ll + 0x200000ll * ((a) & 0x1f) + 0x10ll * ((b) & 0x1f);
    __bdk_csr_fatal("NIC_VFX_MSIX_VECX_CTL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_VFX_MSIX_VECX_CTL(a,b) bdk_nic_vfx_msix_vecx_ctl_t
#define bustype_BDK_NIC_VFX_MSIX_VECX_CTL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_VFX_MSIX_VECX_CTL(a,b) "NIC_VFX_MSIX_VECX_CTL"
#define device_bar_BDK_NIC_VFX_MSIX_VECX_CTL(a,b) 0x4 /* VF_BAR4 */
#define busnum_BDK_NIC_VFX_MSIX_VECX_CTL(a,b) (a)
#define arguments_BDK_NIC_VFX_MSIX_VECX_CTL(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_vf#_pf_mbox#
 *
 * NIC VF/PF Mailbox Registers
 */
union bdk_nic_vfx_pf_mboxx
{
    uint64_t u;
    struct bdk_nic_vfx_pf_mboxx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Mailbox data. These VF registers access the 16-byte-per-VF VF/PF mailbox
                                                                 RAM. The PF may access the same storage using NIC_PF_VF()_MBOX(). MBOX(0) is
                                                                 typically used for PF to VF signaling, MBOX(1) for VF to PF. Writing
                                                                 NIC_VF()_PF_MBOX(1) (but not NIC_PF_VF()_MBOX(1)) will set the
                                                                 corresponding NIC_PF_MBOX_INT() bit, which if appropriately enabled will send an
                                                                 interrupt to the PF. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Mailbox data. These VF registers access the 16-byte-per-VF VF/PF mailbox
                                                                 RAM. The PF may access the same storage using NIC_PF_VF()_MBOX(). MBOX(0) is
                                                                 typically used for PF to VF signaling, MBOX(1) for VF to PF. Writing
                                                                 NIC_VF()_PF_MBOX(1) (but not NIC_PF_VF()_MBOX(1)) will set the
                                                                 corresponding NIC_PF_MBOX_INT() bit, which if appropriately enabled will send an
                                                                 interrupt to the PF. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_vfx_pf_mboxx_s cn; */
};
typedef union bdk_nic_vfx_pf_mboxx bdk_nic_vfx_pf_mboxx_t;

static inline uint64_t BDK_NIC_VFX_PF_MBOXX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_VFX_PF_MBOXX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=1)))
        return 0x8430a0000130ll + 0x200000ll * ((a) & 0x7) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=1)))
        return 0x8430a0000130ll + 0x200000ll * ((a) & 0x1f) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("NIC_VFX_PF_MBOXX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_VFX_PF_MBOXX(a,b) bdk_nic_vfx_pf_mboxx_t
#define bustype_BDK_NIC_VFX_PF_MBOXX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_VFX_PF_MBOXX(a,b) "NIC_VFX_PF_MBOXX"
#define device_bar_BDK_NIC_VFX_PF_MBOXX(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_VFX_PF_MBOXX(a,b) (a)
#define arguments_BDK_NIC_VFX_PF_MBOXX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_vnic#_rss_cfg
 *
 * NIC VNIC RSS Configuration Registers
 */
union bdk_nic_vnicx_rss_cfg
{
    uint64_t u;
    struct bdk_nic_vnicx_rss_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t rss_tun_nvgre         : 1;  /**< [ 11: 11](R/W) Enable NVGRE tunneling support. */
        uint64_t rss_tun_geneve        : 1;  /**< [ 10: 10](R/W) Enable GENEVE tunneling support. */
        uint64_t rss_tun_vxlan         : 1;  /**< [  9:  9](R/W) Enable VXLAN tunnel support. */
        uint64_t rss_l4_bidi           : 1;  /**< [  8:  8](R/W) Enable bidirectional flow symmetry RSS for the L4 TCP/UDP RSS layer. */
        uint64_t rss_l3_bidi           : 1;  /**< [  7:  7](R/W) Enable bidirectional flow symmetry RSS for the L3 IPV4, IPV6 RSS layer. */
        uint64_t rss_roce              : 1;  /**< [  6:  6](R/W) Reserved.
                                                                 Internal:
                                                                 Unused field. Old definition:
                                                                 Enable ROCE delivery, potentially resulting in setting NIC_CQE_RX_S[RSS_ALG] =
                                                                 NIC_RSS_ALG_E::ROCE. */
        uint64_t rss_l4etc             : 1;  /**< [  5:  5](R/W) Enable L4 extended RSS hashing, including GRE, potentially resulting in setting
                                                                 NIC_CQE_RX_S[RSS_ALG] = NIC_RSS_ALG_E::GRE_IP or NIC_RSS_ALG_E::INNER_GRE_IP. */
        uint64_t rss_udp               : 1;  /**< [  4:  4](R/W) Enable IP RSS hashing, potentially resulting in setting NIC_CQE_RX_S[RSS_ALG] =
                                                                 NIC_RSS_ALG_E::UDP_IP. */
        uint64_t rss_syn_dis           : 1;  /**< [  3:  3](R/W) Disable RSS on TCP SYN packets. If set, TCP packets with SYN & !ACK will have RSS disabled. */
        uint64_t rss_tcp               : 1;  /**< [  2:  2](R/W) Enable TCP RSS hashing, potentially resulting in setting NIC_CQE_RX_S[RSS_ALG] =
                                                                 NIC_RSS_ALG_E::TCP_IP. */
        uint64_t rss_ip                : 1;  /**< [  1:  1](R/W) Enable IPv4/6 RSS hashing, potentially resulting in setting NIC_CQE_RX_S[RSS_ALG] =
                                                                 NIC_RSS_ALG_E::IP. */
        uint64_t rss_l2etc             : 1;  /**< [  0:  0](R/W) Enable L2 extended RSS hashing, potentially resulting in setting NIC_CQE_RX_S[RSS_ALG] =
                                                                 NIC_RSS_ALG_E::PORT. */
#else /* Word 0 - Little Endian */
        uint64_t rss_l2etc             : 1;  /**< [  0:  0](R/W) Enable L2 extended RSS hashing, potentially resulting in setting NIC_CQE_RX_S[RSS_ALG] =
                                                                 NIC_RSS_ALG_E::PORT. */
        uint64_t rss_ip                : 1;  /**< [  1:  1](R/W) Enable IPv4/6 RSS hashing, potentially resulting in setting NIC_CQE_RX_S[RSS_ALG] =
                                                                 NIC_RSS_ALG_E::IP. */
        uint64_t rss_tcp               : 1;  /**< [  2:  2](R/W) Enable TCP RSS hashing, potentially resulting in setting NIC_CQE_RX_S[RSS_ALG] =
                                                                 NIC_RSS_ALG_E::TCP_IP. */
        uint64_t rss_syn_dis           : 1;  /**< [  3:  3](R/W) Disable RSS on TCP SYN packets. If set, TCP packets with SYN & !ACK will have RSS disabled. */
        uint64_t rss_udp               : 1;  /**< [  4:  4](R/W) Enable IP RSS hashing, potentially resulting in setting NIC_CQE_RX_S[RSS_ALG] =
                                                                 NIC_RSS_ALG_E::UDP_IP. */
        uint64_t rss_l4etc             : 1;  /**< [  5:  5](R/W) Enable L4 extended RSS hashing, including GRE, potentially resulting in setting
                                                                 NIC_CQE_RX_S[RSS_ALG] = NIC_RSS_ALG_E::GRE_IP or NIC_RSS_ALG_E::INNER_GRE_IP. */
        uint64_t rss_roce              : 1;  /**< [  6:  6](R/W) Reserved.
                                                                 Internal:
                                                                 Unused field. Old definition:
                                                                 Enable ROCE delivery, potentially resulting in setting NIC_CQE_RX_S[RSS_ALG] =
                                                                 NIC_RSS_ALG_E::ROCE. */
        uint64_t rss_l3_bidi           : 1;  /**< [  7:  7](R/W) Enable bidirectional flow symmetry RSS for the L3 IPV4, IPV6 RSS layer. */
        uint64_t rss_l4_bidi           : 1;  /**< [  8:  8](R/W) Enable bidirectional flow symmetry RSS for the L4 TCP/UDP RSS layer. */
        uint64_t rss_tun_vxlan         : 1;  /**< [  9:  9](R/W) Enable VXLAN tunnel support. */
        uint64_t rss_tun_geneve        : 1;  /**< [ 10: 10](R/W) Enable GENEVE tunneling support. */
        uint64_t rss_tun_nvgre         : 1;  /**< [ 11: 11](R/W) Enable NVGRE tunneling support. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_vnicx_rss_cfg_s cn; */
};
typedef union bdk_nic_vnicx_rss_cfg bdk_nic_vnicx_rss_cfg_t;

static inline uint64_t BDK_NIC_VNICX_RSS_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_VNICX_RSS_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=7))
        return 0x8430a00020e0ll + 0x200000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x8430a00020e0ll + 0x200000ll * ((a) & 0x1f);
    __bdk_csr_fatal("NIC_VNICX_RSS_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_VNICX_RSS_CFG(a) bdk_nic_vnicx_rss_cfg_t
#define bustype_BDK_NIC_VNICX_RSS_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_VNICX_RSS_CFG(a) "NIC_VNICX_RSS_CFG"
#define device_bar_BDK_NIC_VNICX_RSS_CFG(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_VNICX_RSS_CFG(a) (a)
#define arguments_BDK_NIC_VNICX_RSS_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) nic_vnic#_rss_key#
 *
 * NIC VNIC RSS Hash-Key Registers
 */
union bdk_nic_vnicx_rss_keyx
{
    uint64_t u;
    struct bdk_nic_vnicx_rss_keyx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t key                   : 64; /**< [ 63:  0](R/W) Eight bytes of 320-bit key for RSS hashing. Software must set this to a random
                                                                 secret value shared with the driver. If bidirectional flows are desired to land
                                                                 on the same queue then the key must be selected to have the 32 bits that start
                                                                 at the IP/port source key position match the 32 bits at the IP/port destination
                                                                 key position. */
#else /* Word 0 - Little Endian */
        uint64_t key                   : 64; /**< [ 63:  0](R/W) Eight bytes of 320-bit key for RSS hashing. Software must set this to a random
                                                                 secret value shared with the driver. If bidirectional flows are desired to land
                                                                 on the same queue then the key must be selected to have the 32 bits that start
                                                                 at the IP/port source key position match the 32 bits at the IP/port destination
                                                                 key position. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_vnicx_rss_keyx_s cn; */
};
typedef union bdk_nic_vnicx_rss_keyx bdk_nic_vnicx_rss_keyx_t;

static inline uint64_t BDK_NIC_VNICX_RSS_KEYX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_VNICX_RSS_KEYX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=4)))
        return 0x8430a0002200ll + 0x200000ll * ((a) & 0x7) + 8ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=4)))
        return 0x8430a0002200ll + 0x200000ll * ((a) & 0x1f) + 8ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_VNICX_RSS_KEYX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_VNICX_RSS_KEYX(a,b) bdk_nic_vnicx_rss_keyx_t
#define bustype_BDK_NIC_VNICX_RSS_KEYX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_VNICX_RSS_KEYX(a,b) "NIC_VNICX_RSS_KEYX"
#define device_bar_BDK_NIC_VNICX_RSS_KEYX(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_VNICX_RSS_KEYX(a,b) (a)
#define arguments_BDK_NIC_VNICX_RSS_KEYX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_vnic#_rx_stat#
 *
 * NIC VNIC Receive Statistics Registers
 * The second dimension indicates which statistic, and is enumerated by NIC_STAT_VNIC_RX_E.
 */
union bdk_nic_vnicx_rx_statx
{
    uint64_t u;
    struct bdk_nic_vnicx_rx_statx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t stat                  : 48; /**< [ 47:  0](RO/H) Statistic value. See also NIC_PF_VNIC()_RX_STAT() for a writable alias of this field. */
#else /* Word 0 - Little Endian */
        uint64_t stat                  : 48; /**< [ 47:  0](RO/H) Statistic value. See also NIC_PF_VNIC()_RX_STAT() for a writable alias of this field. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_vnicx_rx_statx_s cn; */
};
typedef union bdk_nic_vnicx_rx_statx bdk_nic_vnicx_rx_statx_t;

static inline uint64_t BDK_NIC_VNICX_RX_STATX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_VNICX_RX_STATX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=13)))
        return 0x8430a0004100ll + 0x200000ll * ((a) & 0x7) + 8ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=13)))
        return 0x8430a0004100ll + 0x200000ll * ((a) & 0x1f) + 8ll * ((b) & 0xf);
    __bdk_csr_fatal("NIC_VNICX_RX_STATX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_VNICX_RX_STATX(a,b) bdk_nic_vnicx_rx_statx_t
#define bustype_BDK_NIC_VNICX_RX_STATX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_VNICX_RX_STATX(a,b) "NIC_VNICX_RX_STATX"
#define device_bar_BDK_NIC_VNICX_RX_STATX(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_VNICX_RX_STATX(a,b) (a)
#define arguments_BDK_NIC_VNICX_RX_STATX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) nic_vnic#_tx_stat#
 *
 * NIC VNIC Transmit Statistics Registers
 * The second dimension indicates which statistic, and is enumerated by NIC_STAT_VNIC_TX_E.
 */
union bdk_nic_vnicx_tx_statx
{
    uint64_t u;
    struct bdk_nic_vnicx_tx_statx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t stat                  : 48; /**< [ 47:  0](RO/H) Statistic value. See also NIC_PF_VNIC()_TX_STAT() for a writable alias of this field. */
#else /* Word 0 - Little Endian */
        uint64_t stat                  : 48; /**< [ 47:  0](RO/H) Statistic value. See also NIC_PF_VNIC()_TX_STAT() for a writable alias of this field. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_nic_vnicx_tx_statx_s cn; */
};
typedef union bdk_nic_vnicx_tx_statx bdk_nic_vnicx_tx_statx_t;

static inline uint64_t BDK_NIC_VNICX_TX_STATX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NIC_VNICX_TX_STATX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=7) && (b<=4)))
        return 0x8430a0004000ll + 0x200000ll * ((a) & 0x7) + 8ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=4)))
        return 0x8430a0004000ll + 0x200000ll * ((a) & 0x1f) + 8ll * ((b) & 0x7);
    __bdk_csr_fatal("NIC_VNICX_TX_STATX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NIC_VNICX_TX_STATX(a,b) bdk_nic_vnicx_tx_statx_t
#define bustype_BDK_NIC_VNICX_TX_STATX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_NIC_VNICX_TX_STATX(a,b) "NIC_VNICX_TX_STATX"
#define device_bar_BDK_NIC_VNICX_TX_STATX(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_NIC_VNICX_TX_STATX(a,b) (a)
#define arguments_BDK_NIC_VNICX_TX_STATX(a,b) (a),(b),-1,-1

#endif /* __BDK_CSRS_NIC_H__ */
