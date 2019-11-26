#ifndef __BDK_CSRS_PKI_H__
#define __BDK_CSRS_PKI_H__
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
 * OcteonTX PKI.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration pki_bar_e
 *
 * PKI Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_PKI_BAR_E_PKI_PF_BAR0 (0x86c000000000ll)
#define BDK_PKI_BAR_E_PKI_PF_BAR0_SIZE 0x1000000ull
#define BDK_PKI_BAR_E_PKI_PF_BAR4 (0x86c001000000ll)
#define BDK_PKI_BAR_E_PKI_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration pki_beltype_e
 *
 * PKI Backend Layer Type Enumeration
 * Enumerates the values for PKI_LTYPE()_MAP[BELTYPE].
 */
#define BDK_PKI_BELTYPE_E_IP4 (2)
#define BDK_PKI_BELTYPE_E_IP6 (3)
#define BDK_PKI_BELTYPE_E_MISC (1)
#define BDK_PKI_BELTYPE_E_NONE (0)
#define BDK_PKI_BELTYPE_E_SCTP (6)
#define BDK_PKI_BELTYPE_E_SNAP (7)
#define BDK_PKI_BELTYPE_E_TCP (4)
#define BDK_PKI_BELTYPE_E_UDP (5)

/**
 * Enumeration pki_chan_e
 *
 * PKI Channel Enumeration
 * Enumerates the value of PKI_WQE_S[CHAN]. Also used for PKO_L3_L2_SQ()_CHANNEL[CHANNEL].
 * Internal:
 * A subset of PKI_CHAN_E also enumerates the values of PKI_FEWQ_S[PORT] and PKI_BEWQ_S[PORT].
 */
#define BDK_PKI_CHAN_E_BGXX_LMACX_CHX(a,b,c) (0x800 + 0x100 * (a) + 0x10 * (b) + (c))
#define BDK_PKI_CHAN_E_DPI_CHX(a) (0x400 + (a))
#define BDK_PKI_CHAN_E_LBKX_CHX(a,b) (0 + 0x100 * (a) + (b))
#define BDK_PKI_CHAN_E_PKO_NULL (0xfff)
#define BDK_PKI_CHAN_E_RX(a) (0 + 0x100 * (a))

/**
 * Enumeration pki_errlev_e
 *
 * PKI Error Level Enumeration
 * Enumerates the value of PKI_WQE_S[ERRLEV].
 * Internal:
 * PKI_ERRLEV_E also enumerates the values of PKI_FEWQ_S[ERRLEV] and PKI_BEWQ_S[ERRLEV].
 */
#define BDK_PKI_ERRLEV_E_LA (1)
#define BDK_PKI_ERRLEV_E_LB (2)
#define BDK_PKI_ERRLEV_E_LC (3)
#define BDK_PKI_ERRLEV_E_LD (4)
#define BDK_PKI_ERRLEV_E_LE (5)
#define BDK_PKI_ERRLEV_E_LF (6)
#define BDK_PKI_ERRLEV_E_LG (7)
#define BDK_PKI_ERRLEV_E_RE (0)

/**
 * Enumeration pki_ethertype_e
 *
 * PKI Ethertypes Enumeration
 * Enumerates the standard Ethertype values.
 * Internal:
 * Only used by parse engine and software; opaque to PKI HW.
 */
#define BDK_PKI_ETHERTYPE_E_ARP (0x806)
#define BDK_PKI_ETHERTYPE_E_CNM (0x22e7)
#define BDK_PKI_ETHERTYPE_E_CNT (0x22e9)
#define BDK_PKI_ETHERTYPE_E_ETAG (0x893f)
#define BDK_PKI_ETHERTYPE_E_FCOE (0x8906)
#define BDK_PKI_ETHERTYPE_E_FCOE_INIT (0x8914)
#define BDK_PKI_ETHERTYPE_E_IP (0x800)
#define BDK_PKI_ETHERTYPE_E_IP6 (0x86dd)
#define BDK_PKI_ETHERTYPE_E_MPLS_8847 (0x8847)
#define BDK_PKI_ETHERTYPE_E_MPLS_8848 (0x8848)
#define BDK_PKI_ETHERTYPE_E_NSH (0x894f)
#define BDK_PKI_ETHERTYPE_E_REVARP (0x8035)
#define BDK_PKI_ETHERTYPE_E_ROCE (0x8915)
#define BDK_PKI_ETHERTYPE_E_TEBRIDGE (0x6558)
#define BDK_PKI_ETHERTYPE_E_VLAN (0x8100)
#define BDK_PKI_ETHERTYPE_E_VLAN_88A8 (0x88a8)
#define BDK_PKI_ETHERTYPE_E_VLAN_9100 (0x9100)
#define BDK_PKI_ETHERTYPE_E_VLAN_9200 (0x9200)
#define BDK_PKI_ETHERTYPE_E_VLAN_9300 (0x9300)

/**
 * Enumeration pki_int_vec_e
 *
 * PKI MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_PKI_INT_VEC_E_ALLOC_FLTX(a) (0xc + (a))
#define BDK_PKI_INT_VEC_E_CLX_ECC(a) (6 + (a))
#define BDK_PKI_INT_VEC_E_CLX_INT(a) (4 + (a))
#define BDK_PKI_INT_VEC_E_ECC0 (1)
#define BDK_PKI_INT_VEC_E_ECC1 (2)
#define BDK_PKI_INT_VEC_E_ECC2 (3)
#define BDK_PKI_INT_VEC_E_GEN (0)
#define BDK_PKI_INT_VEC_E_STRM_FLTX(a) (8 + (a))

/**
 * Enumeration pki_ipproto_e
 *
 * PKI IP Protocol Enumeration
 * Enumerates the IPv4 protocol and IPv6 next-header values.
 * Internal:
 * Only used by parse engine and software; opaque to PKI HW.
 */
#define BDK_PKI_IPPROTO_E_AH (0x33)
#define BDK_PKI_IPPROTO_E_DEST (0x3c)
#define BDK_PKI_IPPROTO_E_ESP (0x32)
#define BDK_PKI_IPPROTO_E_FRAG (0x2c)
#define BDK_PKI_IPPROTO_E_GRE (0x2f)
#define BDK_PKI_IPPROTO_E_HOP_BY_HOP (0)
#define BDK_PKI_IPPROTO_E_IP4 (4)
#define BDK_PKI_IPPROTO_E_IP6 (0x29)
#define BDK_PKI_IPPROTO_E_IPCOMP (0x6c)
#define BDK_PKI_IPPROTO_E_ROUTING (0x2b)
#define BDK_PKI_IPPROTO_E_SCTP (0x84)
#define BDK_PKI_IPPROTO_E_TCP (6)
#define BDK_PKI_IPPROTO_E_UDP (0x11)

/**
 * Enumeration pki_ltype_e
 *
 * PKI Layer Type Enumeration
 * Enumerates the values of PKI_WQE_S[LBTY], PKI_WQE_S[LCTY], PKI_WQE_S[LDTY],
 * PKI_WQE_S[LETY], PKI_WQE_S[LFTY] and PKI_WQE_S[LGTY].
 *
 * This table also recommends PKI_LTYPE()_MAP[BELTYPE] (PKI_BELTYPE_E) values
 * for each PKI_LTYPE_E, indicates which layers can hold the PKI_LTYPE_E,
 * and also indicates (in the descriptions) PKI_CL()_PCAM()_ACTION()[SETTY]
 * usage of the PKI_LTYPE_E.
 *
 * Internal:
 * PKI_LTYPE_E also enumerates the values of PKI_BEWQ_S[LBTY], PKI_BEWQ_S[LCTY],
 * PKI_BEWQ_S[LDTY], PKI_BEWQ_S[LETY], PKI_BEWQ_S[LFTY] and PKI_BEWQ_S[LGTY].
 */
#define BDK_PKI_LTYPE_E_ARP (6)
#define BDK_PKI_LTYPE_E_ENET (1)
#define BDK_PKI_LTYPE_E_GRE (0x14)
#define BDK_PKI_LTYPE_E_GTP (0x16)
#define BDK_PKI_LTYPE_E_IP4 (8)
#define BDK_PKI_LTYPE_E_IP4_OPT (9)
#define BDK_PKI_LTYPE_E_IP6 (0xa)
#define BDK_PKI_LTYPE_E_IP6_OPT (0xb)
#define BDK_PKI_LTYPE_E_IPCOMP (0xe)
#define BDK_PKI_LTYPE_E_IPFRAG (0xd)
#define BDK_PKI_LTYPE_E_IPSEC_ESP (0xc)
#define BDK_PKI_LTYPE_E_NONE (0)
#define BDK_PKI_LTYPE_E_NVGRE (0x15)
#define BDK_PKI_LTYPE_E_RARP (7)
#define BDK_PKI_LTYPE_E_SCTP (0x12)
#define BDK_PKI_LTYPE_E_SNAP_PAYLD (5)
#define BDK_PKI_LTYPE_E_SW28 (0x1c)
#define BDK_PKI_LTYPE_E_SW29 (0x1d)
#define BDK_PKI_LTYPE_E_SW30 (0x1e)
#define BDK_PKI_LTYPE_E_SW31 (0x1f)
#define BDK_PKI_LTYPE_E_TCP (0x10)
#define BDK_PKI_LTYPE_E_UDP (0x11)
#define BDK_PKI_LTYPE_E_UDP_GENEVE (0x17)
#define BDK_PKI_LTYPE_E_UDP_VXLAN (0x13)
#define BDK_PKI_LTYPE_E_VLAN (2)

/**
 * Enumeration pki_opcode_e
 *
 * PKI Error Opcode Enumeration
 * Enumerates the value of PKI_WQE_S[OPCODE].
 * Internal:
 * PKI_OPCODE_E also enumerates the values of PKI_FEWQ_S[OPCODE] and PKI_BEWQ_S[OPCODE].
 */
#define BDK_PKI_OPCODE_E_IP_CHK (0x42)
#define BDK_PKI_OPCODE_E_IP_HOP (0x45)
#define BDK_PKI_OPCODE_E_IP_MAL (0x43)
#define BDK_PKI_OPCODE_E_IP_MALD (0x44)
#define BDK_PKI_OPCODE_E_IP_NOT (0x41)
#define BDK_PKI_OPCODE_E_L2_FRAGMENT (0x20)
#define BDK_PKI_OPCODE_E_L2_LENMISM (0x27)
#define BDK_PKI_OPCODE_E_L2_MAL (0x24)
#define BDK_PKI_OPCODE_E_L2_OVERRUN (0x21)
#define BDK_PKI_OPCODE_E_L2_OVERSIZE (0x25)
#define BDK_PKI_OPCODE_E_L2_PFCS (0x22)
#define BDK_PKI_OPCODE_E_L2_PUNY (0x23)
#define BDK_PKI_OPCODE_E_L2_UNDERSIZE (0x26)
#define BDK_PKI_OPCODE_E_L4_CHK (0x62)
#define BDK_PKI_OPCODE_E_L4_LEN (0x63)
#define BDK_PKI_OPCODE_E_L4_MAL (0x61)
#define BDK_PKI_OPCODE_E_L4_PORT (0x64)
#define BDK_PKI_OPCODE_E_RE_BUFS_OFLOW (0x16)
#define BDK_PKI_OPCODE_E_RE_DMAPKT (0xf)
#define BDK_PKI_OPCODE_E_RE_FCS (7)
#define BDK_PKI_OPCODE_E_RE_FCS_RCV (8)
#define BDK_PKI_OPCODE_E_RE_JABBER (2)
#define BDK_PKI_OPCODE_E_RE_MEMOUT (0x15)
#define BDK_PKI_OPCODE_E_RE_NONE (0)
#define BDK_PKI_OPCODE_E_RE_PARTIAL (1)
#define BDK_PKI_OPCODE_E_RE_PKIPAR (0x13)
#define BDK_PKI_OPCODE_E_RE_PKIPCAM (0x14)
#define BDK_PKI_OPCODE_E_RE_RX_CTL (0xb)
#define BDK_PKI_OPCODE_E_RE_SKIP (0xc)
#define BDK_PKI_OPCODE_E_RE_TERMINATE (9)
#define BDK_PKI_OPCODE_E_TCP_FLAG (0x65)

/**
 * Enumeration pki_pcam_term_e
 *
 * PKI PCAM Term Enumeration
 * Enumerates the virtual-CAM type for the PKI_CL()_PCAM()_TERM()[TERM] field.
 *
 * In the table below:
 * * 'MATCH' refers to PKI_CL()_PCAM()_MATCH().
 * * 'ACTION' refers to PKI_CL()_PCAM()_ACTION() for the PCAM entry that matches.
 * * The 'Bank' column indicates which PCAM bank must contain the match data.
 * * The 'Adv' column indicates if PKI_CL()_PCAM()_ACTION()[ADVANCE] may be nonzero;
 *   'No' indicates ADVANCE must be zero; 'Yes' indicates ADVANCE may be nonzero;
 *   otherwise indicates the typical ADVANCE value(s).
 * * The 'PMC' column indicates if PKI_CL()_PCAM()_ACTION()[PMC] may be nonzero.
 *   PMC is typically 0x0.
 * * The 'SETTY' column indicates if PKI_CL()_PCAM()_ACTION()[SETTY] may be nonzero,
 *   and if so either which values it may take or which WQE pointer field and type
 *   field will be set to the SETTY value when SETTY!=NONE (0). For example, LFTY
 *   indicates that if PKI_CL()_PCAM()_ACTION()[SETTY]!=NONE then PKI_WQE_S[LFTY] will
 *   be set to PKI_CL()_PCAM()_ACTION()[SETTY] and PKI_WQE_S[LFPTR] will be set to the
 *   current parse point.
 * * The description indicates the meaning of each data bit programmed with
 *   PKI_CL()_PCAM()_MATCH().  MATCH bits which are indicated as reserved must be
 *   programmed to always match (don't cares) when programming PKI_CL()_PCAM()_MATCH().
 *
 * Internal:
 * Only used by parse engine and software; opaque to PKI HW.
 *
 * The PCAM is banked for alternating accesses, so the bank
 * must toggle between each parse engine access for maximum performance.
 */
#define BDK_PKI_PCAM_TERM_E_DMACH (0xa)
#define BDK_PKI_PCAM_TERM_E_DMACL (0xb)
#define BDK_PKI_PCAM_TERM_E_DSA (0x13)
#define BDK_PKI_PCAM_TERM_E_ETHTYPE0 (0x18)
#define BDK_PKI_PCAM_TERM_E_ETHTYPE1 (0x19)
#define BDK_PKI_PCAM_TERM_E_ETHTYPE2 (0x1a)
#define BDK_PKI_PCAM_TERM_E_ETHTYPE3 (0x1b)
#define BDK_PKI_PCAM_TERM_E_GLORT (0x12)
#define BDK_PKI_PCAM_TERM_E_HIGIG (5)
#define BDK_PKI_PCAM_TERM_E_HIGIGD (4)
#define BDK_PKI_PCAM_TERM_E_IL3_FLAGS (0x2b)
#define BDK_PKI_PCAM_TERM_E_L2_CUSTOM (2)
#define BDK_PKI_PCAM_TERM_E_L3_DIPHH (0x24)
#define BDK_PKI_PCAM_TERM_E_L3_DIPLL (0x27)
#define BDK_PKI_PCAM_TERM_E_L3_DIPMH (0x25)
#define BDK_PKI_PCAM_TERM_E_L3_DIPML (0x26)
#define BDK_PKI_PCAM_TERM_E_L3_FLAGS (0x23)
#define BDK_PKI_PCAM_TERM_E_L3_SIPHH (0x1f)
#define BDK_PKI_PCAM_TERM_E_L3_SIPLL (0x22)
#define BDK_PKI_PCAM_TERM_E_L3_SIPMH (0x20)
#define BDK_PKI_PCAM_TERM_E_L3_SIPML (0x21)
#define BDK_PKI_PCAM_TERM_E_L4_PORT (0x30)
#define BDK_PKI_PCAM_TERM_E_L4_SPORT (0x2f)
#define BDK_PKI_PCAM_TERM_E_LD_VNI (0x28)
#define BDK_PKI_PCAM_TERM_E_LF_SPI (0x2e)
#define BDK_PKI_PCAM_TERM_E_LG_CUSTOM (0x39)
#define BDK_PKI_PCAM_TERM_E_MPLS0 (0x1e)
#define BDK_PKI_PCAM_TERM_E_NONE (0)
#define BDK_PKI_PCAM_TERM_E_SMACH (8)
#define BDK_PKI_PCAM_TERM_E_SMACL (9)

/**
 * Enumeration pki_qpgqos_e
 *
 * PKI QPG QoS Algorithm Enumeration
 * Enumerates the values of PKI_CL()_STYLE()_ALG[QPG_QOS].
 * Internal:
 * Only used by parse engine and software; opaque to PKI HW.
 */
#define BDK_PKI_QPGQOS_E_DIFF (4)
#define BDK_PKI_QPGQOS_E_DSA_SRC (3)
#define BDK_PKI_QPGQOS_E_HIGIG (5)
#define BDK_PKI_QPGQOS_E_MPLS (2)
#define BDK_PKI_QPGQOS_E_NONE (0)
#define BDK_PKI_QPGQOS_E_VLAN (1)

/**
 * Enumeration pki_reasm_e
 *
 * PKI Reassembly Enumeration
 * Enumerates the values of the reassembly-ID map.
 */
#define BDK_PKI_REASM_E_DPI_REASM (2)
#define BDK_PKI_REASM_E_LBK_NIC_REASM (1)
#define BDK_PKI_REASM_E_LBK_PKO_REASM (0)
#define BDK_PKI_REASM_E_MAC_REASMX(a) (0 + (a))
#define BDK_PKI_REASM_E_NUM_REASM (0x13)

/**
 * Enumeration pki_udpport_e
 *
 * PKI IP UDP Port Enumeration
 * Enumerates the IP UDP port values.
 * Internal:
 * Only used by parse engine and software; opaque to PKI HW.
 */
#define BDK_PKI_UDPPORT_E_GENEVE (0x17c1)
#define BDK_PKI_UDPPORT_E_GTPC (0x84b)
#define BDK_PKI_UDPPORT_E_GTPP (0xd3a)
#define BDK_PKI_UDPPORT_E_GTPU (0x868)
#define BDK_PKI_UDPPORT_E_RESERVED (0)
#define BDK_PKI_UDPPORT_E_ROCE (0x12b7)
#define BDK_PKI_UDPPORT_E_VXLAN (0x12b5)
#define BDK_PKI_UDPPORT_E_VXLAN_GPE (0x12b6)

/**
 * Enumeration pki_vxlangpeprot_e
 *
 * PKI VXLAN GPE Protocol Enumeration
 * Enumerates the VXLAN GPE next protocol values.
 * Internal:
 * Only used by parse engine and software; opaque to PKI HW.
 */
#define BDK_PKI_VXLANGPEPROT_E_ETHERNET (3)
#define BDK_PKI_VXLANGPEPROT_E_IP4 (1)
#define BDK_PKI_VXLANGPEPROT_E_IP6 (2)
#define BDK_PKI_VXLANGPEPROT_E_MPLS (5)
#define BDK_PKI_VXLANGPEPROT_E_NSH (4)
#define BDK_PKI_VXLANGPEPROT_E_RESERVED (0)

/**
 * Structure pki_bewq_s
 *
 * INTERNAL: PKI Back-end WQE Structure
 *
 * This structure describes the handoff structure between an IPE parse engine and PKI
 * back-end, and how the field is modified to create PKI_WQE_S. The fields names are
 * generally similar to PKI_WQE_S; see the respective PKI_WQE_S field definitions for
 * more information.
 */
union bdk_pki_bewq_s
{
    uint64_t u[16];
    struct bdk_pki_bewq_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t node                  : 2;  /**< [ 63: 62] BE opaque pass-through to WQE. */
        uint64_t reserved_60_61        : 2;
        uint64_t aura                  : 12; /**< [ 59: 48] PKI_WQE_S[AURA] is normally calculated solely by PKI BE, but if
                                                                 PKI_CL()_STYLE()_CFG[QPG_DIS_AURA] is set, PKI_WQE_S[AURA] is [AURA]. */
        uint64_t reserved_47           : 1;
        uint64_t apad                  : 3;  /**< [ 46: 44] BE pass-through to WQE; BE uses to determine packet write data alignment. */
        uint64_t port                  : 12; /**< [ 43: 32] BE uses to compute WQE[CHAN]. */
        uint64_t fcsptr                : 8;  /**< [ 31: 24] Indicates to BE byte location at which BE will start FCS
                                                                 calculation. Parse engine should load from PKI_CL()_PKIND()_SKIP[FCS_SKIP]. */
        uint64_t style                 : 8;  /**< [ 23: 16] BE pass-through to WQE; BE uses for final-style CSR lookup. */
        uint64_t reserved_6_15         : 10;
        uint64_t pknd                  : 6;  /**< [  5:  0] BE opaque pass-through to WQE. */
#else /* Word 0 - Little Endian */
        uint64_t pknd                  : 6;  /**< [  5:  0] BE opaque pass-through to WQE. */
        uint64_t reserved_6_15         : 10;
        uint64_t style                 : 8;  /**< [ 23: 16] BE pass-through to WQE; BE uses for final-style CSR lookup. */
        uint64_t fcsptr                : 8;  /**< [ 31: 24] Indicates to BE byte location at which BE will start FCS
                                                                 calculation. Parse engine should load from PKI_CL()_PKIND()_SKIP[FCS_SKIP]. */
        uint64_t port                  : 12; /**< [ 43: 32] BE uses to compute WQE[CHAN]. */
        uint64_t apad                  : 3;  /**< [ 46: 44] BE pass-through to WQE; BE uses to determine packet write data alignment. */
        uint64_t reserved_47           : 1;
        uint64_t aura                  : 12; /**< [ 59: 48] PKI_WQE_S[AURA] is normally calculated solely by PKI BE, but if
                                                                 PKI_CL()_STYLE()_CFG[QPG_DIS_AURA] is set, PKI_WQE_S[AURA] is [AURA]. */
        uint64_t reserved_60_61        : 2;
        uint64_t node                  : 2;  /**< [ 63: 62] BE opaque pass-through to WQE. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t len                   : 16; /**< [127:112] BE ignores, and creates WQE[LEN] with complete packet length. */
        uint64_t reserved_108_111      : 4;
        uint64_t grp                   : 10; /**< [107: 98] PKI_WQE_S[GRP] is normally calculated solely by PKI BE. But if
                                                                 PKI_CL()_STYLE()_CFG[QPG_DIS_GRP] is set, PKI_WQE_S[GRP] is [GRP]. */
        uint64_t tt                    : 2;  /**< [ 97: 96] BE opaque pass-through to WQE. */
        uint64_t tag                   : 32; /**< [ 95: 64] PKI_WQE_S[TAG]\<31:16\> = [TAG]\<31:16\>.

                                                                 PKI_WQE_S[TAG]\<15:0\> = [TAG]\<15:0\> ^ F
                                                                 if (PKI_CL()_STYLE()_CFG2[TAG_MASKEN])
                                                                    PKI_WQE_S[TAG]\<15:0\> &= ~PKI_STYLE()_TAG_MASK[MASK];

                                                                 Where F is a function of various optional hw_tuple_tag()'s and
                                                                 hw_mask_tag(). See PKI_WQE_S[TAG]. */
#else /* Word 1 - Little Endian */
        uint64_t tag                   : 32; /**< [ 95: 64] PKI_WQE_S[TAG]\<31:16\> = [TAG]\<31:16\>.

                                                                 PKI_WQE_S[TAG]\<15:0\> = [TAG]\<15:0\> ^ F
                                                                 if (PKI_CL()_STYLE()_CFG2[TAG_MASKEN])
                                                                    PKI_WQE_S[TAG]\<15:0\> &= ~PKI_STYLE()_TAG_MASK[MASK];

                                                                 Where F is a function of various optional hw_tuple_tag()'s and
                                                                 hw_mask_tag(). See PKI_WQE_S[TAG]. */
        uint64_t tt                    : 2;  /**< [ 97: 96] BE opaque pass-through to WQE. */
        uint64_t grp                   : 10; /**< [107: 98] PKI_WQE_S[GRP] is normally calculated solely by PKI BE. But if
                                                                 PKI_CL()_STYLE()_CFG[QPG_DIS_GRP] is set, PKI_WQE_S[GRP] is [GRP]. */
        uint64_t reserved_108_111      : 4;
        uint64_t len                   : 16; /**< [127:112] BE ignores, and creates WQE[LEN] with complete packet length. */
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t sw                    : 1;  /**< [191:191] BE opaque pass-through to WQE. */
        uint64_t lgty                  : 5;  /**< [190:186] BE pass-through; BE uses for tagging/checksum. */
        uint64_t lfty                  : 5;  /**< [185:181] BE pass-through; BE uses for tagging/checksum. */
        uint64_t lety                  : 5;  /**< [180:176] BE pass-through; BE uses for tagging/checksum. */
        uint64_t ldty                  : 5;  /**< [175:171] BE pass-through; BE uses for tagging/checksum. */
        uint64_t lcty                  : 5;  /**< [170:166] BE pass-through; BE uses for tagging/checksum. */
        uint64_t lbty                  : 5;  /**< [165:161] BE pass-through; BE uses for tagging/checksum. */
        uint64_t lae                   : 1;  /**< [160:160] BE pass-through; BE uses for tagging/checksum. */
        uint64_t reserved_152_159      : 8;
        uint64_t vv                    : 1;  /**< [151:151] BE opaque pass-through to WQE. */
        uint64_t vs                    : 1;  /**< [150:150] BE opaque pass-through to WQE. */
        uint64_t sh                    : 1;  /**< [149:149] BE pass-through; BE uses for statistics. */
        uint64_t pf                    : 4;  /**< [148:145] BE opaque pass-through to WQE. */
        uint64_t l3fr                  : 1;  /**< [144:144] BE opaque pass-through to WQE. */
        uint64_t l3b                   : 1;  /**< [143:143] BE pass-through; BE uses for statistics. */
        uint64_t l3m                   : 1;  /**< [142:142] BE pass-through; BE uses for statistics. */
        uint64_t l2b                   : 1;  /**< [141:141] BE pass-through; BE uses for statistics. */
        uint64_t l2m                   : 1;  /**< [140:140] BE pass-through; BE uses for statistics. */
        uint64_t raw                   : 1;  /**< [139:139] BE pass-through; BE uses for statistics. */
        uint64_t errlev                : 3;  /**< [138:136] Pre-BE error state, which BE overrides on a BE error. */
        uint64_t opcode                : 8;  /**< [135:128] Pre-BE error state, which BE overrides on a BE error. */
#else /* Word 2 - Little Endian */
        uint64_t opcode                : 8;  /**< [135:128] Pre-BE error state, which BE overrides on a BE error. */
        uint64_t errlev                : 3;  /**< [138:136] Pre-BE error state, which BE overrides on a BE error. */
        uint64_t raw                   : 1;  /**< [139:139] BE pass-through; BE uses for statistics. */
        uint64_t l2m                   : 1;  /**< [140:140] BE pass-through; BE uses for statistics. */
        uint64_t l2b                   : 1;  /**< [141:141] BE pass-through; BE uses for statistics. */
        uint64_t l3m                   : 1;  /**< [142:142] BE pass-through; BE uses for statistics. */
        uint64_t l3b                   : 1;  /**< [143:143] BE pass-through; BE uses for statistics. */
        uint64_t l3fr                  : 1;  /**< [144:144] BE opaque pass-through to WQE. */
        uint64_t pf                    : 4;  /**< [148:145] BE opaque pass-through to WQE. */
        uint64_t sh                    : 1;  /**< [149:149] BE pass-through; BE uses for statistics. */
        uint64_t vs                    : 1;  /**< [150:150] BE opaque pass-through to WQE. */
        uint64_t vv                    : 1;  /**< [151:151] BE opaque pass-through to WQE. */
        uint64_t reserved_152_159      : 8;
        uint64_t lae                   : 1;  /**< [160:160] BE pass-through; BE uses for tagging/checksum. */
        uint64_t lbty                  : 5;  /**< [165:161] BE pass-through; BE uses for tagging/checksum. */
        uint64_t lcty                  : 5;  /**< [170:166] BE pass-through; BE uses for tagging/checksum. */
        uint64_t ldty                  : 5;  /**< [175:171] BE pass-through; BE uses for tagging/checksum. */
        uint64_t lety                  : 5;  /**< [180:176] BE pass-through; BE uses for tagging/checksum. */
        uint64_t lfty                  : 5;  /**< [185:181] BE pass-through; BE uses for tagging/checksum. */
        uint64_t lgty                  : 5;  /**< [190:186] BE pass-through; BE uses for tagging/checksum. */
        uint64_t sw                    : 1;  /**< [191:191] BE opaque pass-through to WQE. */
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t cfg                   : 32; /**< [255:224] BE input value of PKI_CL()_STYLE()_CFG\<31:0\>. BE then replaces with SIZE/ADDR. */
        uint64_t cfg2                  : 32; /**< [223:192] BE input value of PKI_CL()_STYLE()_CFG2\<31:0\>. BE then replaces with SIZE/ADDR. */
#else /* Word 3 - Little Endian */
        uint64_t cfg2                  : 32; /**< [223:192] BE input value of PKI_CL()_STYLE()_CFG2\<31:0\>. BE then replaces with SIZE/ADDR. */
        uint64_t cfg                   : 32; /**< [255:224] BE input value of PKI_CL()_STYLE()_CFG\<31:0\>. BE then replaces with SIZE/ADDR. */
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t vlptr                 : 8;  /**< [319:312] BE pass-through; BE uses for tagging. */
        uint64_t lgptr                 : 8;  /**< [311:304] BE pass-through; BE uses for tagging/checksum. */
        uint64_t lfptr                 : 8;  /**< [303:296] BE pass-through; BE uses for tagging/checksum. */
        uint64_t leptr                 : 8;  /**< [295:288] BE pass-through; BE uses for tagging/checksum. */
        uint64_t ldptr                 : 8;  /**< [287:280] BE pass-through; BE uses for tagging/checksum. */
        uint64_t lcptr                 : 8;  /**< [279:272] BE pass-through; BE uses for tagging/checksum. */
        uint64_t lbptr                 : 8;  /**< [271:264] BE pass-through; BE uses for tagging/checksum. */
        uint64_t laptr                 : 8;  /**< [263:256] BE pass-through; BE uses for tagging/checksum. */
#else /* Word 4 - Little Endian */
        uint64_t laptr                 : 8;  /**< [263:256] BE pass-through; BE uses for tagging/checksum. */
        uint64_t lbptr                 : 8;  /**< [271:264] BE pass-through; BE uses for tagging/checksum. */
        uint64_t lcptr                 : 8;  /**< [279:272] BE pass-through; BE uses for tagging/checksum. */
        uint64_t ldptr                 : 8;  /**< [287:280] BE pass-through; BE uses for tagging/checksum. */
        uint64_t leptr                 : 8;  /**< [295:288] BE pass-through; BE uses for tagging/checksum. */
        uint64_t lfptr                 : 8;  /**< [303:296] BE pass-through; BE uses for tagging/checksum. */
        uint64_t lgptr                 : 8;  /**< [311:304] BE pass-through; BE uses for tagging/checksum. */
        uint64_t vlptr                 : 8;  /**< [319:312] BE pass-through; BE uses for tagging. */
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t reserved_320_383      : 64;
#else /* Word 5 - Little Endian */
        uint64_t reserved_320_383      : 64;
#endif /* Word 5 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 6 - Big Endian */
        uint64_t reserved_384_447      : 64;
#else /* Word 6 - Little Endian */
        uint64_t reserved_384_447      : 64;
#endif /* Word 6 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 7 - Big Endian */
        uint64_t reserved_448_511      : 64;
#else /* Word 7 - Little Endian */
        uint64_t reserved_448_511      : 64;
#endif /* Word 7 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 8 - Big Endian */
        uint64_t reserved_512_575      : 64;
#else /* Word 8 - Little Endian */
        uint64_t reserved_512_575      : 64;
#endif /* Word 8 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 9 - Big Endian */
        uint64_t reserved_576_639      : 64;
#else /* Word 9 - Little Endian */
        uint64_t reserved_576_639      : 64;
#endif /* Word 9 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 10 - Big Endian */
        uint64_t reserved_640_703      : 64;
#else /* Word 10 - Little Endian */
        uint64_t reserved_640_703      : 64;
#endif /* Word 10 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 11 - Big Endian */
        uint64_t reserved_704_767      : 64;
#else /* Word 11 - Little Endian */
        uint64_t reserved_704_767      : 64;
#endif /* Word 11 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 12 - Big Endian */
        uint64_t reserved_768_831      : 64;
#else /* Word 12 - Little Endian */
        uint64_t reserved_768_831      : 64;
#endif /* Word 12 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 13 - Big Endian */
        uint64_t reserved_832_895      : 64;
#else /* Word 13 - Little Endian */
        uint64_t reserved_832_895      : 64;
#endif /* Word 13 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 14 - Big Endian */
        uint64_t reserved_896_959      : 64;
#else /* Word 14 - Little Endian */
        uint64_t reserved_896_959      : 64;
#endif /* Word 14 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 15 - Big Endian */
        uint64_t reserved_960_1023     : 64;
#else /* Word 15 - Little Endian */
        uint64_t reserved_960_1023     : 64;
#endif /* Word 15 - End */
    } s;
    /* struct bdk_pki_bewq_s_s cn; */
};

/**
 * Structure pki_buflink_s
 *
 * PKI Buffer Link Structure
 * PKI and PKO can link packet segments together with this PKI_BUFLINK_S. When multiple
 * packet segments are linked, a valid PKI_BUFLINK_S is present 16 bytes before the first
 * byte of any earlier segment. The last segment linked does not have a next segment,
 * and must be preceded by 16 bytes of valid L2/DRAM where the PKI_BUFLINK_S normally
 * exists, but need not have a valid PKI_BUFLINK_S in the space. CPU software
 * or PKO hardware may read, but effectively should not use, this "invalid
 * PKI_BUFLINK_S".
 *
 * PKI_BUFLINK_S's are not required be naturally aligned (to 128-bits) in L2/DRAM,
 * though the last segments and corresponding PKI_BUFLINK_S's
 * that PKI creates for packet input are naturally-aligned.
 */
union bdk_pki_buflink_s
{
    uint64_t u[2];
    struct bdk_pki_buflink_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t sw                    : 32; /**< [ 63: 32] Reserved for software use. PKI hardware writes as 0x0, and PKI ignores on reads. */
        uint64_t i                     : 1;  /**< [ 31: 31] Invert free. PKI writes zero to this bit. PKO optionally uses this bit to control FPA
                                                                 buffer returns. See PKO_SEND_HDR_S[DF,II].

                                                                 On a PKO SEND, PKO frees the surrounding buffer to FPA when:
                                                                    PKO_SEND_HDR_S[DF] XOR (NOT PKO_SEND_HDR_S[II] AND [I])
                                                                 is zero.

                                                                 PKO naturally aligns [ADDR] to 128 bytes before sending it to FPA as part of
                                                                 the buffer free. An FPA naturally-aligned pool is recommended, though opaque
                                                                 pool mode may also be possible. Refer to the FPA Chapter.

                                                                 PKO frees the buffer to PKO_SEND_LINK_S[AURA]. (See PKO_SEND_FREE_S[AURA].)

                                                                 PKO will not free [ADDR] to FPA until after it has finished reading
                                                                 this segment (and the PKI_BUFLINK_S that precedes this segment in
                                                                 the buffer, if necessary) from the buffer.
                                                                 Provided the path of descriptors from the DQ through PKO to an output FIFO is
                                                                 unmodified between the descriptors (as should normally be the case, but it is
                                                                 possible for software to change the path), PKO also will not free
                                                                 [ADDR] to FPA until after it has completed all L2/DRAM reads related
                                                                 to processing any PKO_SEND_GATHER_S and any PKO_SEND_LINK_S in any
                                                                 other descriptor enqueued earlier in the same DQ. PKO may free [ADDR] in any
                                                                 order with respect to any processing of any descriptor that is in a
                                                                 different DQ. PKO may create the FPA
                                                                 free for [ADDR] in any order relative to any other PKO FPA
                                                                 frees needed to process this or any other PKO SEND descriptor,
                                                                 and in any order relative to any FPA frees/allocates needed for DQ DRAM
                                                                 buffering, and in any order relative to any FPA aura count
                                                                 updates needed to process a PKO_SEND_AURA_S subdescriptor in this
                                                                 or any other PKO SEND. The FPA free may occur in any order relative to any
                                                                 L2/DRAM updates or any work queue add needed to process this or
                                                                 any other PKO SEND. */
        uint64_t reserved_16_30        : 15;
        uint64_t size                  : 16; /**< [ 15:  0] Size of the buffer/segment.

                                                                 The [SIZE] created by PKI always indicates the number of bytes available
                                                                 in the buffer. Except for the last linked buffer, [SIZE] is also exactly
                                                                 the number of bytes of packet data in the segment and the buffer.
                                                                 For the last segment created by PKI, [SIZE] will be larger than the
                                                                 number of valid packet bytes in the segment/buffer unless the packet
                                                                 data ends exactly at the end of the buffer.

                                                                 In the PKO case, if more than [SIZE] bytes are needed to reach
                                                                 PKO_SEND_HDR_S[TOTAL] packet data bytes, PKO continues fetching packet
                                                                 data from the next segment described by the PKI_BUFLINK_S that must
                                                                 reside in the 16 L2/DRAM bytes prior to [ADDR]. Let priorbytes = the
                                                                 sum of PKO_SEND_LINK_S[SIZE], all PKO_SEND_GATHER_S[SIZE]'s, and all
                                                                 PKO_SEND_IMM_S[SIZE]'s in this descriptor, plus the sum of all prior
                                                                 PKI_BUFLINK_S[SIZE]'s linked by the PKO_SEND_LINK_S. PKO does not
                                                                 reference nor use this PKI_BUFLINK_S segment when
                                                                 priorbytes \>= PKO_SEND_HDR_S[TOTAL]. Otherwise, the
                                                                 number of bytes PKO uses from this PKI_BUFLINK_S segment is:

                                                                 _    min(PKO_SEND_HDR_S[TOTAL]-priorbytes, [SIZE])

                                                                 The sum of any PKO_SEND_IMM_S[SIZE]'s, PKO_SEND_GATHER_S[SIZE]'s, and
                                                                 PKO_SEND_LINK_S[SIZE]'s in the PKO Send descriptor plus any
                                                                 PKI_BUFLINK_S[SIZE]'s linked by any PKO_SEND_LINK_S must equal or
                                                                 exceed PKO_SEND_HDR_S[TOTAL]. */
#else /* Word 0 - Little Endian */
        uint64_t size                  : 16; /**< [ 15:  0] Size of the buffer/segment.

                                                                 The [SIZE] created by PKI always indicates the number of bytes available
                                                                 in the buffer. Except for the last linked buffer, [SIZE] is also exactly
                                                                 the number of bytes of packet data in the segment and the buffer.
                                                                 For the last segment created by PKI, [SIZE] will be larger than the
                                                                 number of valid packet bytes in the segment/buffer unless the packet
                                                                 data ends exactly at the end of the buffer.

                                                                 In the PKO case, if more than [SIZE] bytes are needed to reach
                                                                 PKO_SEND_HDR_S[TOTAL] packet data bytes, PKO continues fetching packet
                                                                 data from the next segment described by the PKI_BUFLINK_S that must
                                                                 reside in the 16 L2/DRAM bytes prior to [ADDR]. Let priorbytes = the
                                                                 sum of PKO_SEND_LINK_S[SIZE], all PKO_SEND_GATHER_S[SIZE]'s, and all
                                                                 PKO_SEND_IMM_S[SIZE]'s in this descriptor, plus the sum of all prior
                                                                 PKI_BUFLINK_S[SIZE]'s linked by the PKO_SEND_LINK_S. PKO does not
                                                                 reference nor use this PKI_BUFLINK_S segment when
                                                                 priorbytes \>= PKO_SEND_HDR_S[TOTAL]. Otherwise, the
                                                                 number of bytes PKO uses from this PKI_BUFLINK_S segment is:

                                                                 _    min(PKO_SEND_HDR_S[TOTAL]-priorbytes, [SIZE])

                                                                 The sum of any PKO_SEND_IMM_S[SIZE]'s, PKO_SEND_GATHER_S[SIZE]'s, and
                                                                 PKO_SEND_LINK_S[SIZE]'s in the PKO Send descriptor plus any
                                                                 PKI_BUFLINK_S[SIZE]'s linked by any PKO_SEND_LINK_S must equal or
                                                                 exceed PKO_SEND_HDR_S[TOTAL]. */
        uint64_t reserved_16_30        : 15;
        uint64_t i                     : 1;  /**< [ 31: 31] Invert free. PKI writes zero to this bit. PKO optionally uses this bit to control FPA
                                                                 buffer returns. See PKO_SEND_HDR_S[DF,II].

                                                                 On a PKO SEND, PKO frees the surrounding buffer to FPA when:
                                                                    PKO_SEND_HDR_S[DF] XOR (NOT PKO_SEND_HDR_S[II] AND [I])
                                                                 is zero.

                                                                 PKO naturally aligns [ADDR] to 128 bytes before sending it to FPA as part of
                                                                 the buffer free. An FPA naturally-aligned pool is recommended, though opaque
                                                                 pool mode may also be possible. Refer to the FPA Chapter.

                                                                 PKO frees the buffer to PKO_SEND_LINK_S[AURA]. (See PKO_SEND_FREE_S[AURA].)

                                                                 PKO will not free [ADDR] to FPA until after it has finished reading
                                                                 this segment (and the PKI_BUFLINK_S that precedes this segment in
                                                                 the buffer, if necessary) from the buffer.
                                                                 Provided the path of descriptors from the DQ through PKO to an output FIFO is
                                                                 unmodified between the descriptors (as should normally be the case, but it is
                                                                 possible for software to change the path), PKO also will not free
                                                                 [ADDR] to FPA until after it has completed all L2/DRAM reads related
                                                                 to processing any PKO_SEND_GATHER_S and any PKO_SEND_LINK_S in any
                                                                 other descriptor enqueued earlier in the same DQ. PKO may free [ADDR] in any
                                                                 order with respect to any processing of any descriptor that is in a
                                                                 different DQ. PKO may create the FPA
                                                                 free for [ADDR] in any order relative to any other PKO FPA
                                                                 frees needed to process this or any other PKO SEND descriptor,
                                                                 and in any order relative to any FPA frees/allocates needed for DQ DRAM
                                                                 buffering, and in any order relative to any FPA aura count
                                                                 updates needed to process a PKO_SEND_AURA_S subdescriptor in this
                                                                 or any other PKO SEND. The FPA free may occur in any order relative to any
                                                                 L2/DRAM updates or any work queue add needed to process this or
                                                                 any other PKO SEND. */
        uint64_t sw                    : 32; /**< [ 63: 32] Reserved for software use. PKI hardware writes as 0x0, and PKI ignores on reads. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t addr                  : 64; /**< [127: 64] Address. ADDR is the IOVA L2/DRAM address of the first byte of packet data in
                                                                 the buffer/segment. The 16 bytes prior to [ADDR] must always be valid readable L2/DRAM
                                                                 locations, and must contain a valid PKI_BUFLINK_S if the remaining packet bytes do
                                                                 not fit in the [SIZE] bytes available in this buffer/segment.

                                                                 All valid [ADDR]'s created by PKI are naturally-aligned to 128-bits.  Bits
                                                                 \<63:49\> are a sign extension of bit \<48\>. PKI associates the stream ID
                                                                 PKI_QPG_TBLB()[STRM] for all references based off [ADDR].

                                                                 In the PKO case, PKO_PF_VF()_GMCTL[STRM] for the virtual function is the stream ID
                                                                 used for all references based off of [ADDR]. If PKO_PF_VF()_GMCTL[BE] is set for
                                                                 this VF, the next-buffer pointer inside the structure that [ADDR] points to is
                                                                 big-endian, else little-endian.

                                                                 The packet data pointed to is byte-invariant and endian settings do not matter. */
#else /* Word 1 - Little Endian */
        uint64_t addr                  : 64; /**< [127: 64] Address. ADDR is the IOVA L2/DRAM address of the first byte of packet data in
                                                                 the buffer/segment. The 16 bytes prior to [ADDR] must always be valid readable L2/DRAM
                                                                 locations, and must contain a valid PKI_BUFLINK_S if the remaining packet bytes do
                                                                 not fit in the [SIZE] bytes available in this buffer/segment.

                                                                 All valid [ADDR]'s created by PKI are naturally-aligned to 128-bits.  Bits
                                                                 \<63:49\> are a sign extension of bit \<48\>. PKI associates the stream ID
                                                                 PKI_QPG_TBLB()[STRM] for all references based off [ADDR].

                                                                 In the PKO case, PKO_PF_VF()_GMCTL[STRM] for the virtual function is the stream ID
                                                                 used for all references based off of [ADDR]. If PKO_PF_VF()_GMCTL[BE] is set for
                                                                 this VF, the next-buffer pointer inside the structure that [ADDR] points to is
                                                                 big-endian, else little-endian.

                                                                 The packet data pointed to is byte-invariant and endian settings do not matter. */
#endif /* Word 1 - End */
    } s;
    /* struct bdk_pki_buflink_s_s cn; */
};

/**
 * Structure pki_fewq_s
 *
 * INTERNAL: PKI Front-end WQE Structure
 *
 * This structure describes the handoff structure between the PKI front end and IPE
 * parse engine code. The fields are similar to PKI_WQE_S.
 */
union bdk_pki_fewq_s
{
    uint64_t u[3];
    struct bdk_pki_fewq_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t port                  : 12; /**< [ 43: 32] FE initializes to port packet was received from. */
        uint64_t reserved_6_31         : 26;
        uint64_t pknd                  : 6;  /**< [  5:  0] FE initializes to pkind packet was received on. */
#else /* Word 0 - Little Endian */
        uint64_t pknd                  : 6;  /**< [  5:  0] FE initializes to pkind packet was received on. */
        uint64_t reserved_6_31         : 26;
        uint64_t port                  : 12; /**< [ 43: 32] FE initializes to port packet was received from. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t len                   : 16; /**< [127:112] FE initializes with packet header length, values 0-256. */
        uint64_t reserved_64_111       : 48;
#else /* Word 1 - Little Endian */
        uint64_t reserved_64_111       : 48;
        uint64_t len                   : 16; /**< [127:112] FE initializes with packet header length, values 0-256. */
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t reserved_139_191      : 53;
        uint64_t errlev                : 3;  /**< [138:136] FE sets if receive error, otherwise 0x0. */
        uint64_t opcode                : 8;  /**< [135:128] FE sets if receive error, otherwise 0x0. */
#else /* Word 2 - Little Endian */
        uint64_t opcode                : 8;  /**< [135:128] FE sets if receive error, otherwise 0x0. */
        uint64_t errlev                : 3;  /**< [138:136] FE sets if receive error, otherwise 0x0. */
        uint64_t reserved_139_191      : 53;
#endif /* Word 2 - End */
    } s;
    /* struct bdk_pki_fewq_s_s cn; */
};

/**
 * Structure pki_inst_hdr_s
 *
 * PKI Instruction Header Structure
 * This structure defines the optional instruction header.
 *
 * When present, a PKI_INST_HDR_S is always stored in memory in big-endian
 * byte order. That is, in the memory byte stream, the first byte memory byte
 * always contains PKI_INST_HDR_S\<63:56\>, the second memory byte always contains
 * PKI_INST_HDR_S\<53:48\>, etc.
 *
 * Internal:
 * Parse engine, software, and external hardware may use this external definition,
 * but it is opaque to PKI HW.
 */
union bdk_pki_inst_hdr_s
{
    uint64_t u;
    struct bdk_pki_inst_hdr_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t w                     : 1;  /**< [ 63: 63] Indicates wider PKI_INST_HDR_S.
                                                                 0 = The PKI_INST_HDR_S is two bytes.
                                                                 1 = The PKI_INST_HDR_S is four or eight bytes. */
        uint64_t raw                   : 1;  /**< [ 62: 62] When set, PKI_WQE_S[RAW] will be set and statistics will accumulate in
                                                                 PKI_STAT()_STAT2 and the packet will never be dropped due to RED unless
                                                                 PKI_CL()_STYLE()_CFG[RAWDRP] is set. */
        uint64_t utag                  : 1;  /**< [ 61: 61] When set, PKI will use PKI_INST_HDR_S [TAG] to compute PKI_WQE_S[TAG].

                                                                 Must be 0 when PKI_INST_HDR_S[W] = 0. */
        uint64_t uqpg                  : 1;  /**< [ 60: 60] When set, PKI will use PKI_INST_HDR_S [QPG] to compute the QPG and indirectly
                                                                 PKI_WQE_S[AURA] and PKI_WQE_S[GRP].

                                                                 Must be 0 when PKI_INST_HDR_S[W] = 0. */
        uint64_t reserved_59           : 1;
        uint64_t pm                    : 3;  /**< [ 58: 56] The mode used to parse the packet, as an encoded value. The legal values are:
                                                                   0x0 = Parse starting at Layer A (Ethernet dest+src, Higig/Fulcrum/DSA).
                                                                   0x1 = Parse starting at Layer B (Ethertype/VLAN, MPLS/ARP/REVARP/SNAP).
                                                                   0x2 = Parse starting at Layer C (Outer IP).
                                                                   0x7 = Parse none and error check none of layers A-G.
                                                                   _ else = reserved.

                                                                 If most or all parsing stages are skipped, then PKI will have little input in
                                                                 the scheduling information loaded into the PKI_WQE_S. PKI_INST_HDR_S[QPG],
                                                                 PKI_INST_HDR_S[TT], and PKI_INST_HDR_S[TAG] may be of use to specify this
                                                                 scheduling information. In this case PKI_STYLE()_WQ2 and PKI_STYLE()_WQ4 may be
                                                                 used to force the decoded information in PKI_WQE_S WORD 2 and WORD 4. */
        uint64_t sl                    : 8;  /**< [ 55: 48] The number of bytes in the PKI_INST_HDR_S and number of bytes to advance to find the next
                                                                 parse item.

                                                                 The following bullets describe the minimum PKI_INST_HDR_S size and, thus, the minimum SL
                                                                 values for a packet:

                                                                 * When PKI_INST_HDR_S [UTAG] = 1, the PKI_INST_HDR_S must be eight bytes, so SL must be
                                                                 eight or more.

                                                                 * When PKI_INST_HDR_S[W] = 1 and PKI_INST_HDR_S [UTAG] = 0, the PKI_INST_HDR_S must be
                                                                 four bytes or more, so SL must be four or more.

                                                                 * When PKI_INST_HDR_S[W] = 0, the PKI_INST_HDR_S may be as small as two bytes, so SL must
                                                                 be two or more.

                                                                 The sum of PKI_INST_HDR_S[SL] and other advances is subject to restrictions as described
                                                                 elsewhere. */
        uint64_t utt                   : 1;  /**< [ 47: 47] When set, PKI uses PKI_INST_HDR_S[TT] to compute PKI_WQE_S[TT].

                                                                 This field is not present unless PKI_INST_HDR_S[W] is set. */
        uint64_t tt                    : 2;  /**< [ 46: 45] When PKI_INST_HDR_S [UTT] and PKI_INST_HDR_S[W] are set, PKI_INST_HDR_S[TT] is
                                                                 used to compute PKI_WQE_S[TT].

                                                                 This field is not present unless PKI_INST_HDR_S[W] is set. */
        uint64_t reserved_43_44        : 2;
        uint64_t qpg                   : 11; /**< [ 42: 32] When PKI_INST_HDR_S[UQPG] and PKI_INST_HDR_S[W] are set, PKI_INST_HDR_S [QPG] is
                                                                 used to indirectly compute PKI_WQE_S[AURA] and PKI_WQE_S[GRP].

                                                                 This field is not present unless PKI_INST_HDR_S[W] is set.

                                                                 The QPG table is generally allocated by software. As the QPG index points into this
                                                                 software allocated table, it is recommended that external components allow the
                                                                 PKI_INST_HDR_S[QPG] values they send to based off a programmable base (perhaps from a CSR
                                                                 inside that component) instead of hard-coding the base. */
        uint64_t tag                   : 32; /**< [ 31:  0] When PKI_INST_HDR_S[UTAG] and PKI_INST_HDR_S[W] are set, PKI_INST_HDR_S[TAG] is
                                                                 used to compute PKI_WQE_S[TAG].

                                                                 This field is not present unless PKI_INST_HDR_S [UTAG] is set. */
#else /* Word 0 - Little Endian */
        uint64_t tag                   : 32; /**< [ 31:  0] When PKI_INST_HDR_S[UTAG] and PKI_INST_HDR_S[W] are set, PKI_INST_HDR_S[TAG] is
                                                                 used to compute PKI_WQE_S[TAG].

                                                                 This field is not present unless PKI_INST_HDR_S [UTAG] is set. */
        uint64_t qpg                   : 11; /**< [ 42: 32] When PKI_INST_HDR_S[UQPG] and PKI_INST_HDR_S[W] are set, PKI_INST_HDR_S [QPG] is
                                                                 used to indirectly compute PKI_WQE_S[AURA] and PKI_WQE_S[GRP].

                                                                 This field is not present unless PKI_INST_HDR_S[W] is set.

                                                                 The QPG table is generally allocated by software. As the QPG index points into this
                                                                 software allocated table, it is recommended that external components allow the
                                                                 PKI_INST_HDR_S[QPG] values they send to based off a programmable base (perhaps from a CSR
                                                                 inside that component) instead of hard-coding the base. */
        uint64_t reserved_43_44        : 2;
        uint64_t tt                    : 2;  /**< [ 46: 45] When PKI_INST_HDR_S [UTT] and PKI_INST_HDR_S[W] are set, PKI_INST_HDR_S[TT] is
                                                                 used to compute PKI_WQE_S[TT].

                                                                 This field is not present unless PKI_INST_HDR_S[W] is set. */
        uint64_t utt                   : 1;  /**< [ 47: 47] When set, PKI uses PKI_INST_HDR_S[TT] to compute PKI_WQE_S[TT].

                                                                 This field is not present unless PKI_INST_HDR_S[W] is set. */
        uint64_t sl                    : 8;  /**< [ 55: 48] The number of bytes in the PKI_INST_HDR_S and number of bytes to advance to find the next
                                                                 parse item.

                                                                 The following bullets describe the minimum PKI_INST_HDR_S size and, thus, the minimum SL
                                                                 values for a packet:

                                                                 * When PKI_INST_HDR_S [UTAG] = 1, the PKI_INST_HDR_S must be eight bytes, so SL must be
                                                                 eight or more.

                                                                 * When PKI_INST_HDR_S[W] = 1 and PKI_INST_HDR_S [UTAG] = 0, the PKI_INST_HDR_S must be
                                                                 four bytes or more, so SL must be four or more.

                                                                 * When PKI_INST_HDR_S[W] = 0, the PKI_INST_HDR_S may be as small as two bytes, so SL must
                                                                 be two or more.

                                                                 The sum of PKI_INST_HDR_S[SL] and other advances is subject to restrictions as described
                                                                 elsewhere. */
        uint64_t pm                    : 3;  /**< [ 58: 56] The mode used to parse the packet, as an encoded value. The legal values are:
                                                                   0x0 = Parse starting at Layer A (Ethernet dest+src, Higig/Fulcrum/DSA).
                                                                   0x1 = Parse starting at Layer B (Ethertype/VLAN, MPLS/ARP/REVARP/SNAP).
                                                                   0x2 = Parse starting at Layer C (Outer IP).
                                                                   0x7 = Parse none and error check none of layers A-G.
                                                                   _ else = reserved.

                                                                 If most or all parsing stages are skipped, then PKI will have little input in
                                                                 the scheduling information loaded into the PKI_WQE_S. PKI_INST_HDR_S[QPG],
                                                                 PKI_INST_HDR_S[TT], and PKI_INST_HDR_S[TAG] may be of use to specify this
                                                                 scheduling information. In this case PKI_STYLE()_WQ2 and PKI_STYLE()_WQ4 may be
                                                                 used to force the decoded information in PKI_WQE_S WORD 2 and WORD 4. */
        uint64_t reserved_59           : 1;
        uint64_t uqpg                  : 1;  /**< [ 60: 60] When set, PKI will use PKI_INST_HDR_S [QPG] to compute the QPG and indirectly
                                                                 PKI_WQE_S[AURA] and PKI_WQE_S[GRP].

                                                                 Must be 0 when PKI_INST_HDR_S[W] = 0. */
        uint64_t utag                  : 1;  /**< [ 61: 61] When set, PKI will use PKI_INST_HDR_S [TAG] to compute PKI_WQE_S[TAG].

                                                                 Must be 0 when PKI_INST_HDR_S[W] = 0. */
        uint64_t raw                   : 1;  /**< [ 62: 62] When set, PKI_WQE_S[RAW] will be set and statistics will accumulate in
                                                                 PKI_STAT()_STAT2 and the packet will never be dropped due to RED unless
                                                                 PKI_CL()_STYLE()_CFG[RAWDRP] is set. */
        uint64_t w                     : 1;  /**< [ 63: 63] Indicates wider PKI_INST_HDR_S.
                                                                 0 = The PKI_INST_HDR_S is two bytes.
                                                                 1 = The PKI_INST_HDR_S is four or eight bytes. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_inst_hdr_s_s cn; */
};

/**
 * Structure pki_wqe_s
 *
 * PKI Work-Queue Entry Structure
 * This section is a description of each field in WORD0 - WORD4 of the work-queue entry.
 */
union bdk_pki_wqe_s
{
    uint64_t u[16];
    struct bdk_pki_wqe_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t node                  : 2;  /**< [ 63: 62] Node number on which the packet arrived.
                                                                 Internal:
                                                                 This is needed by software; do not remove on single-node parts. */
        uint64_t reserved_60_61        : 2;
        uint64_t aura                  : 12; /**< [ 59: 48] The guest-aura computed for the packet. PKI sets [AURA] to
                                                                 PKI_QPG_TBL(q)[GAURA], where q is the QPG computed for the
                                                                 packet (see the parser document).

                                                                 Internal:
                                                                 q is PKI_BEWQ_S[CFG\<10:0\>]. [AURA] is normally calculated solely by PKI BE,
                                                                 but if PKI_CL()_STYLE()_CFG[QPG_DIS_AURA] is set, [AURA] is PKI_BEWQ_S[AURA]. */
        uint64_t reserved_47           : 1;
        uint64_t apad                  : 3;  /**< [ 46: 44] Number of bytes of alignment padding that were applied. The pad is calculated by
                                                                 the following algorithm:

                                                                 \<pre\>
                                                                 void pki_calc_alignment_pad() {
                                                                   // Note only LC and LE may contain IP headers,
                                                                   // thus only LC/LE is used below.
                                                                   if ([ERRLEV] \<= LC)
                                                                      [APAD] = 0..7;  // Undefined
                                                                   else if ([LCTY]==IP6*) // Outer IP.ver == 6
                                                                      [APAD] = (8 - [LCPTR]) & 0x7;
                                                                   else if ([LETY]==IP6*) // Inner IP.ver == 6
                                                                      [APAD] = (8 - [LEPTR]) & 0x7;
                                                                   else if ([LCTY]!=NONE)
                                                                      [APAD] = (4 - [LCPTR]) & 0x7;
                                                                   else
                                                                      [APAD] = PKI_CL()_STYLE()_ALG[APAD_NIP];
                                                                 }
                                                                 \</pre\>

                                                                 Internal:
                                                                 The pad is calculated by the parse engine.

                                                                 [APAD] is PKI_BEWQ_S[APAD]. */
        uint64_t chan                  : 12; /**< [ 43: 32] The logical channel that the packet arrived from, enumerated by PKI_CHAN_E.

                                                                 PKI computes channel numbers as follows:
                                                                 \<pre\>
                                                                  port = PKI-port or pre-QPG PKI_CHAN_E (from the physical interface)
                                                                  [CHAN] = port + (PKI_CL()_STYLE()_CFG[QPG_DIS_PADD] ? 0 : PKI_QPG_TBL(q)[PADD]);
                                                                 \</pre\>

                                                                 where q is the QPG is computed for the packet (see the parser document).

                                                                 Internal:
                                                                 port in the [CHAN] pseudocode above is PKI_BEWQ_S[PORT] and probably
                                                                 also PKI_FEWQ_S[PORT]. q in the pseudocode above is PKI_BEWQ_S[CFG]\<10:0\>.

                                                                 PKI HW does: [CHAN] = PKI_BEWQ_S[PORT] +
                                                                        (PKI_BEWQ_S[CFG\<18\>] ? 0 : PKI_QPG_TBL(PKI_BEWQ_S[CFG\<10:0\>])[PADD]) */
        uint64_t bufs                  : 8;  /**< [ 31: 24] Number of data buffers used to store the packet data, never zero. For example,
                                                                 the value will be 0x1 if PKI_STYLE()_BUF[DIS_WQ_DAT]=0 and all of the data fit
                                                                 into a combined buffer comprising the work queue entry and first data
                                                                 buffer. [BUFS] will also be 0x1 if PKI_STYLE()_BUF[DIS_WQ_DAT]=1 and only a
                                                                 single data buffer was created.

                                                                 Internal:
                                                                 [BUFS] is computed solely by PKI BE HW. */
        uint64_t style                 : 8;  /**< [ 23: 16] The last 8-bit STYLE produced by the parser for the packet. The low 6 bits are the FINAL
                                                                 STYLE, which is used to index the PKI_CL*_STYLE* (i.e. PKI_CL*_SMEM*) and
                                                                 PKI_STYLE* CSRs.

                                                                 Internal:
                                                                 [STYLE] is PKI_BEWQ_S[STYLE]. */
        uint64_t reserved_6_15         : 10;
        uint64_t pknd                  : 6;  /**< [  5:  0] Pkind computed by the inbound interface for the packet.
                                                                 Internal:
                                                                 [PKND] is PKI_BEWQ_S[PKND] and probably also PKI_FEWQ_S[PKND]. */
#else /* Word 0 - Little Endian */
        uint64_t pknd                  : 6;  /**< [  5:  0] Pkind computed by the inbound interface for the packet.
                                                                 Internal:
                                                                 [PKND] is PKI_BEWQ_S[PKND] and probably also PKI_FEWQ_S[PKND]. */
        uint64_t reserved_6_15         : 10;
        uint64_t style                 : 8;  /**< [ 23: 16] The last 8-bit STYLE produced by the parser for the packet. The low 6 bits are the FINAL
                                                                 STYLE, which is used to index the PKI_CL*_STYLE* (i.e. PKI_CL*_SMEM*) and
                                                                 PKI_STYLE* CSRs.

                                                                 Internal:
                                                                 [STYLE] is PKI_BEWQ_S[STYLE]. */
        uint64_t bufs                  : 8;  /**< [ 31: 24] Number of data buffers used to store the packet data, never zero. For example,
                                                                 the value will be 0x1 if PKI_STYLE()_BUF[DIS_WQ_DAT]=0 and all of the data fit
                                                                 into a combined buffer comprising the work queue entry and first data
                                                                 buffer. [BUFS] will also be 0x1 if PKI_STYLE()_BUF[DIS_WQ_DAT]=1 and only a
                                                                 single data buffer was created.

                                                                 Internal:
                                                                 [BUFS] is computed solely by PKI BE HW. */
        uint64_t chan                  : 12; /**< [ 43: 32] The logical channel that the packet arrived from, enumerated by PKI_CHAN_E.

                                                                 PKI computes channel numbers as follows:
                                                                 \<pre\>
                                                                  port = PKI-port or pre-QPG PKI_CHAN_E (from the physical interface)
                                                                  [CHAN] = port + (PKI_CL()_STYLE()_CFG[QPG_DIS_PADD] ? 0 : PKI_QPG_TBL(q)[PADD]);
                                                                 \</pre\>

                                                                 where q is the QPG is computed for the packet (see the parser document).

                                                                 Internal:
                                                                 port in the [CHAN] pseudocode above is PKI_BEWQ_S[PORT] and probably
                                                                 also PKI_FEWQ_S[PORT]. q in the pseudocode above is PKI_BEWQ_S[CFG]\<10:0\>.

                                                                 PKI HW does: [CHAN] = PKI_BEWQ_S[PORT] +
                                                                        (PKI_BEWQ_S[CFG\<18\>] ? 0 : PKI_QPG_TBL(PKI_BEWQ_S[CFG\<10:0\>])[PADD]) */
        uint64_t apad                  : 3;  /**< [ 46: 44] Number of bytes of alignment padding that were applied. The pad is calculated by
                                                                 the following algorithm:

                                                                 \<pre\>
                                                                 void pki_calc_alignment_pad() {
                                                                   // Note only LC and LE may contain IP headers,
                                                                   // thus only LC/LE is used below.
                                                                   if ([ERRLEV] \<= LC)
                                                                      [APAD] = 0..7;  // Undefined
                                                                   else if ([LCTY]==IP6*) // Outer IP.ver == 6
                                                                      [APAD] = (8 - [LCPTR]) & 0x7;
                                                                   else if ([LETY]==IP6*) // Inner IP.ver == 6
                                                                      [APAD] = (8 - [LEPTR]) & 0x7;
                                                                   else if ([LCTY]!=NONE)
                                                                      [APAD] = (4 - [LCPTR]) & 0x7;
                                                                   else
                                                                      [APAD] = PKI_CL()_STYLE()_ALG[APAD_NIP];
                                                                 }
                                                                 \</pre\>

                                                                 Internal:
                                                                 The pad is calculated by the parse engine.

                                                                 [APAD] is PKI_BEWQ_S[APAD]. */
        uint64_t reserved_47           : 1;
        uint64_t aura                  : 12; /**< [ 59: 48] The guest-aura computed for the packet. PKI sets [AURA] to
                                                                 PKI_QPG_TBL(q)[GAURA], where q is the QPG computed for the
                                                                 packet (see the parser document).

                                                                 Internal:
                                                                 q is PKI_BEWQ_S[CFG\<10:0\>]. [AURA] is normally calculated solely by PKI BE,
                                                                 but if PKI_CL()_STYLE()_CFG[QPG_DIS_AURA] is set, [AURA] is PKI_BEWQ_S[AURA]. */
        uint64_t reserved_60_61        : 2;
        uint64_t node                  : 2;  /**< [ 63: 62] Node number on which the packet arrived.
                                                                 Internal:
                                                                 This is needed by software; do not remove on single-node parts. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t len                   : 16; /**< [127:112] Total number of bytes of packet data, from 1 to nearly 2^16. The total
                                                                 packet length includes all the packet bytes, except that the CRC field is
                                                                 discarded when PKI_CL()_STYLE()_CFG[FCS_STRIP] = 1. (If
                                                                 PKI_CL()_STYLE()_CFG[FCS_STRIP] = 0, both [LEN] and the stored packet
                                                                 include the CRC bytes.)

                                                                 If [ERRLEV,OPCODE] = PKI_ERRLEV_E::RE,PKI_OPCODE_E::RE_MEMOUT, [LEN] will
                                                                 have the total number of packet bytes written to memory but some of these
                                                                 bytes will have been overwritten to the same buffer.

                                                                 See also the [ERRLEV,OPCODE] = PKI_ERRLEV_E::LA,PKI_OPCODE_E::L2_PUNY exception
                                                                 case.

                                                                 PKI hardware supports packets that are as large as (2^16 - 64) bytes
                                                                 on the external interface. [LEN] can be larger than the number of bytes
                                                                 on the external interface if the MAC adds bytes to the input packet
                                                                 (e.g. BGX()_SMU()_RX_FRM_CTL[PTP_MODE]).

                                                                 Internal:
                                                                 [LEN] is calculated solely by PKI BE. */
        uint64_t reserved_108_111      : 4;
        uint64_t grp                   : 10; /**< [107: 98] The SSO guest-group number used for the packet's ADD_WORK. One of
                                                                 PKI_QPG_TBL(q)[GRP_OK,GRP_BAD], possibly with low [TAG] bits added
                                                                 to it (see PKI_QPG_TBL(q)[GRPTAG_OK,GRPTAG_BAD] and
                                                                 PKI_CL()_STYLE()_CFG[QPG_DIS_GRPTAG]). The OK's are used when
                                                                 both [ERRLEV,OPCODE] are zero (i.e. RE/RE_NONE), else the BAD's are used.
                                                                 q is the QPG computed for the packet (see the parser document).

                                                                 [GRP]\<9:8\> is always zero.

                                                                 Internal:
                                                                 q is PKI_BEWQ_S[CFG\<10:0\>].

                                                                 [GRP] is normally calculated solely by PKI BE. But if
                                                                 PKI_CL()_STYLE()_CFG[QPG_DIS_GRP] is set, [GRP] is PKI_BEWQ_S[GRP]. */
        uint64_t tt                    : 2;  /**< [ 97: 96] The initial tag type for the packet's SSO ADD_WORK. Enumerated with SSO_TT_E
                                                                 (UNTAGGED, ORDERED, or ATOMIC). Calculated as follows:

                                                                 \<pre\>
                                                                 void calculate_tt(uint style, pki_inst_hdr) {
                                                                    if (PKI_CL()_PKIND()_CFG[pkind][INST_HDR]
                                                                             && PKI_INST_HDR_S[W]
                                                                             && PKI_INST_HDR_S[UTT]) {
                                                                       [TT] = PKI_INST_HDR_S[TT];
                                                                    }
                                                                    else {
                                                                       [TT] = PKI_CL()_STYLE()_ALG[TT];
                                                                    }
                                                                 }
                                                                 \</pre\>

                                                                 Internal:
                                                                 [TT] is calculated by the parse engine.

                                                                 [TT] is PKI_BEWQ_S[TT]. */
        uint64_t tag                   : 32; /**< [ 95: 64] The initial tag for the work-queue entry.
                                                                 Internal:
                                                                 A combination of hardware and microcode creates [TAG]. Microcode
                                                                 computes PKI_BEWQ_S[TAG]. Hardware creates the final [TAG] as
                                                                 follows:

                                                                 [TAG]\<31:16\> = PKI_BEWQ_S[TAG]\<31:16\>.

                                                                 [TAG]\<15:0\> = PKI_BEWQ_S[TAG]\<15:0\> ^ F
                                                                 if (PKI_CL()_STYLE()_CFG2[TAG_MASKEN])
                                                                    [TAG]\<15:0\> &= ~PKI_STYLE()_TAG_MASK[MASK];

                                                                 Where F is a function of various optional hw_tuple_tag()'s and
                                                                 hw_mask_tag() - see below.

                                                                 pseudocode:

                                                                 void calculate_tag(uint style, int pkt_len, packet) {
                                                                  if (WQE[ERRLEV]\<=LA && WQE[OPCODE]!=NONE) { //Done by PBE PLC
                                                                   WQE[TAG] = 0xFFFFFFFF;
                                                                  }
                                                                  else if (PKI_CL(0..3)_PKIND(0..63)_CFG[pkind][INST_HDR] //Done by UCode
                                                                        && PKI_INST_HDR[UTAG]) {
                                                                   WQE[TAG] = PKI_INST_HDR[TAG];
                                                                  }
                                                                  else {  // Done by combination of UCode and PBE PLC
                                                                   uint32 tag = 0;
                                                                   uint16 crc = 0;
                                                                   crc = crc ^ hw_lb_to_lg_tag(style, packet); // hw_lb_to_lg_tag done by UCode
                                                                   // hw_tuple_tag done by hardware, UCode will clear
                                                                   // PKI_CL(0..3)_STYLE(0..63)_CFG2[style][TAG_SRC_LX]
                                                                   // and [PKI_CL(0..3)_STYLE(0..63)_CFG2[style][TAG_DST_LX] to disable
                                                                   // this XOR if tag is set by INST_HDR
                                                                   crc = crc ^ hw_tuple_tag(style, packet, LC);
                                                                   crc = crc ^ hw_tuple_tag(style, packet, LD);
                                                                   crc = crc ^ hw_tuple_tag(style, packet, LE);
                                                                   crc = crc ^ hw_tuple_tag(style, packet, LF);
                                                                   // hw_mask_tag done by hardware, UCode will clear
                                                                   // (PKI_CL(0..3)_STYLE(0..63)_CFG2[style].TAG_INC[mask])
                                                                   // to disable this XOR if tag is set by INST_HDR
                                                                   tag\<15:0\> = crc ^ hw_mask_tag(style, pkt_len, packet);
                                                                   if (PKI_CL(0..3)_STYLE(0..63)_CFG2[TAG_MASKEN])
                                                                    tag\<15:0\> = tag\<15:0\> & ~PKI_STYLE(0..63)_TAG_MASK[style]; // done by hardware
                                                                   if (PKI_CL(0..3)_STYLE(0..63)_ALG[style][TAG_PRT]) // UCODE sets tag\<27:16\>
                                                                    tag\<27:16\> = PKI_FEWQ_S/PKI_BEWQ_S[PORT]; // set by UCODE
                                                                   else
                                                                    tag\<27:16\> = 0xFFF;
                                                                   WQE[TAG] = tag;
                                                                  }
                                                                 } */
#else /* Word 1 - Little Endian */
        uint64_t tag                   : 32; /**< [ 95: 64] The initial tag for the work-queue entry.
                                                                 Internal:
                                                                 A combination of hardware and microcode creates [TAG]. Microcode
                                                                 computes PKI_BEWQ_S[TAG]. Hardware creates the final [TAG] as
                                                                 follows:

                                                                 [TAG]\<31:16\> = PKI_BEWQ_S[TAG]\<31:16\>.

                                                                 [TAG]\<15:0\> = PKI_BEWQ_S[TAG]\<15:0\> ^ F
                                                                 if (PKI_CL()_STYLE()_CFG2[TAG_MASKEN])
                                                                    [TAG]\<15:0\> &= ~PKI_STYLE()_TAG_MASK[MASK];

                                                                 Where F is a function of various optional hw_tuple_tag()'s and
                                                                 hw_mask_tag() - see below.

                                                                 pseudocode:

                                                                 void calculate_tag(uint style, int pkt_len, packet) {
                                                                  if (WQE[ERRLEV]\<=LA && WQE[OPCODE]!=NONE) { //Done by PBE PLC
                                                                   WQE[TAG] = 0xFFFFFFFF;
                                                                  }
                                                                  else if (PKI_CL(0..3)_PKIND(0..63)_CFG[pkind][INST_HDR] //Done by UCode
                                                                        && PKI_INST_HDR[UTAG]) {
                                                                   WQE[TAG] = PKI_INST_HDR[TAG];
                                                                  }
                                                                  else {  // Done by combination of UCode and PBE PLC
                                                                   uint32 tag = 0;
                                                                   uint16 crc = 0;
                                                                   crc = crc ^ hw_lb_to_lg_tag(style, packet); // hw_lb_to_lg_tag done by UCode
                                                                   // hw_tuple_tag done by hardware, UCode will clear
                                                                   // PKI_CL(0..3)_STYLE(0..63)_CFG2[style][TAG_SRC_LX]
                                                                   // and [PKI_CL(0..3)_STYLE(0..63)_CFG2[style][TAG_DST_LX] to disable
                                                                   // this XOR if tag is set by INST_HDR
                                                                   crc = crc ^ hw_tuple_tag(style, packet, LC);
                                                                   crc = crc ^ hw_tuple_tag(style, packet, LD);
                                                                   crc = crc ^ hw_tuple_tag(style, packet, LE);
                                                                   crc = crc ^ hw_tuple_tag(style, packet, LF);
                                                                   // hw_mask_tag done by hardware, UCode will clear
                                                                   // (PKI_CL(0..3)_STYLE(0..63)_CFG2[style].TAG_INC[mask])
                                                                   // to disable this XOR if tag is set by INST_HDR
                                                                   tag\<15:0\> = crc ^ hw_mask_tag(style, pkt_len, packet);
                                                                   if (PKI_CL(0..3)_STYLE(0..63)_CFG2[TAG_MASKEN])
                                                                    tag\<15:0\> = tag\<15:0\> & ~PKI_STYLE(0..63)_TAG_MASK[style]; // done by hardware
                                                                   if (PKI_CL(0..3)_STYLE(0..63)_ALG[style][TAG_PRT]) // UCODE sets tag\<27:16\>
                                                                    tag\<27:16\> = PKI_FEWQ_S/PKI_BEWQ_S[PORT]; // set by UCODE
                                                                   else
                                                                    tag\<27:16\> = 0xFFF;
                                                                   WQE[TAG] = tag;
                                                                  }
                                                                 } */
        uint64_t tt                    : 2;  /**< [ 97: 96] The initial tag type for the packet's SSO ADD_WORK. Enumerated with SSO_TT_E
                                                                 (UNTAGGED, ORDERED, or ATOMIC). Calculated as follows:

                                                                 \<pre\>
                                                                 void calculate_tt(uint style, pki_inst_hdr) {
                                                                    if (PKI_CL()_PKIND()_CFG[pkind][INST_HDR]
                                                                             && PKI_INST_HDR_S[W]
                                                                             && PKI_INST_HDR_S[UTT]) {
                                                                       [TT] = PKI_INST_HDR_S[TT];
                                                                    }
                                                                    else {
                                                                       [TT] = PKI_CL()_STYLE()_ALG[TT];
                                                                    }
                                                                 }
                                                                 \</pre\>

                                                                 Internal:
                                                                 [TT] is calculated by the parse engine.

                                                                 [TT] is PKI_BEWQ_S[TT]. */
        uint64_t grp                   : 10; /**< [107: 98] The SSO guest-group number used for the packet's ADD_WORK. One of
                                                                 PKI_QPG_TBL(q)[GRP_OK,GRP_BAD], possibly with low [TAG] bits added
                                                                 to it (see PKI_QPG_TBL(q)[GRPTAG_OK,GRPTAG_BAD] and
                                                                 PKI_CL()_STYLE()_CFG[QPG_DIS_GRPTAG]). The OK's are used when
                                                                 both [ERRLEV,OPCODE] are zero (i.e. RE/RE_NONE), else the BAD's are used.
                                                                 q is the QPG computed for the packet (see the parser document).

                                                                 [GRP]\<9:8\> is always zero.

                                                                 Internal:
                                                                 q is PKI_BEWQ_S[CFG\<10:0\>].

                                                                 [GRP] is normally calculated solely by PKI BE. But if
                                                                 PKI_CL()_STYLE()_CFG[QPG_DIS_GRP] is set, [GRP] is PKI_BEWQ_S[GRP]. */
        uint64_t reserved_108_111      : 4;
        uint64_t len                   : 16; /**< [127:112] Total number of bytes of packet data, from 1 to nearly 2^16. The total
                                                                 packet length includes all the packet bytes, except that the CRC field is
                                                                 discarded when PKI_CL()_STYLE()_CFG[FCS_STRIP] = 1. (If
                                                                 PKI_CL()_STYLE()_CFG[FCS_STRIP] = 0, both [LEN] and the stored packet
                                                                 include the CRC bytes.)

                                                                 If [ERRLEV,OPCODE] = PKI_ERRLEV_E::RE,PKI_OPCODE_E::RE_MEMOUT, [LEN] will
                                                                 have the total number of packet bytes written to memory but some of these
                                                                 bytes will have been overwritten to the same buffer.

                                                                 See also the [ERRLEV,OPCODE] = PKI_ERRLEV_E::LA,PKI_OPCODE_E::L2_PUNY exception
                                                                 case.

                                                                 PKI hardware supports packets that are as large as (2^16 - 64) bytes
                                                                 on the external interface. [LEN] can be larger than the number of bytes
                                                                 on the external interface if the MAC adds bytes to the input packet
                                                                 (e.g. BGX()_SMU()_RX_FRM_CTL[PTP_MODE]).

                                                                 Internal:
                                                                 [LEN] is calculated solely by PKI BE. */
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t sw                    : 1;  /**< [191:191] Reserved for software use. [SW] will be set when corresponding
                                                                 PKI_STYLE()_WQ2[DATA]\<63\> is set, but this is not recommended.

                                                                 Internal:
                                                                 [SW] = PKI_BEWQ_S[SW] | PKI_STYLE()_WQ2\<63\>

                                                                 Microcode could set this bit, but doesn't currently. */
        uint64_t lgty                  : 5;  /**< [190:186] Custom header type parsed after normal C, D, E, or F layer parsing.
                                                                 Enumerated by PKI_LTYPE_E. (See the parser document.)

                                                                 [LGTY] is set to a nonzero action[SETTY] on a PCAM hit with PCAM data
                                                                 extracted from a base plus PKI_CL()_PKIND()_LG_CUSTOM[OFFSET] in the
                                                                 following circumstances:

                                                                 _ When PKI_CL()_PKIND()_CFG[LG_CUSTOM_LAYER]=1 and [LCTY]!=PKI_LTYPE_E::NONE,
                                                                 with [LCPTR] as base

                                                                 _ When PKI_CL()_PKIND()_CFG[LG_CUSTOM_LAYER]=2 and [LDTY]!=PKI_LTYPE_E::NONE,
                                                                 with [LDPTR] as base

                                                                 _ When PKI_CL()_PKIND()_CFG[LG_CUSTOM_LAYER]=3 and [LETY]!=PKI_LTYPE_E::NONE,
                                                                 with [LEPTR] as base

                                                                 _ When PKI_CL()_PKIND()_CFG[LG_CUSTOM_LAYER]=4 and [LFTY]!=PKI_LTYPE_E::NONE,
                                                                 with [LFPTR] as base

                                                                 [LGTY] is 0x0 (PKI_LTYPE_E::NONE) unless set after normal C, D, E, or F
                                                                 layer parsing via PKI_CL()_PCAM()_ACTION()[SETTY]. [LGTY] is unpredictable
                                                                 when [ERRLEV] \<= LG. [LGTY] bits are always set when corresponding
                                                                 PKI_STYLE()_WQ2\<62:58\> bits are set.

                                                                 Internal:
                                                                 [LGTY] = PKI_BEWQ_S[LGTY] | PKI_STYLE()_WQ2\<62:58\> */
        uint64_t lfty                  : 5;  /**< [185:181] Layer F header type parsed, often corresponding to layer 4 (UDP/TCP).
                                                                 Enumerated by PKI_LTYPE_E. (See the parser document.)

                                                                 _ The parse engine can set [LFTY] to PKI_LTYPE_E::IPFRAG during
                                                                 Layer E processing when it finds that the inner IP packet is fragmented.

                                                                 _ The parse engine can also set [LFTY] to one of PKI_LTYPE_E::IPCOMP,
                                                                 IPSEC_ESP (ESP or AH), GRE, UDP, SCTP, TCP during Layer F processing
                                                                 when it finds the corresponding protocol.

                                                                 [LFTY] is 0x0 (PKI_LTYPE_E::NONE) unless Layer E or F parsing sets it.
                                                                 [LFTY] is unpredictable when [ERRLEV] \<= LF. [LFTY] bits are always set
                                                                 when corresponding PKI_STYLE()_WQ2\<57:53\> bits are set.

                                                                 Internal:
                                                                 [LFTY] = PKI_BEWQ_S[LFTY] | PKI_STYLE()_WQ2\<57:53\> */
        uint64_t lety                  : 5;  /**< [180:176] Layer E header type parsed, often corresponding to inner IP. Enumerated
                                                                 by PKI_LTYPE_E. See also [LEPTR]. (See the parser document.)

                                                                 _ The parse engine can set [LETY] to one of PKI_LTYPE_E::IP4, IP4_OPT,
                                                                 IP6, IP6_OPT during Layer E processing when it finds the corresponding
                                                                 protocol. The parse engine will only do this when [LDTY] is one of
                                                                 PKI_LTYPE_E::UDP_GENEVE, UDP_VXLAN, or NVGRE.

                                                                 [LETY] is 0x0 (PKI_LTYPE_E::NONE) unless Layer E parsing sets it.
                                                                 [LETY] is unpredictable when [ERRLEV] \<= LE. [LETY] bits are always set
                                                                 when corresponding PKI_STYLE()_WQ2\<52:48\> bits are set.

                                                                 Internal:
                                                                 [LETY] = PKI_BEWQ_S[LETY] | PKI_STYLE()_WQ2\<52:48\> */
        uint64_t ldty                  : 5;  /**< [175:171] Layer D header typed parsed, typically corresponding to a virtualization
                                                                 header. Enumerated by PKI_LTYPE_E. See also [LDPTR]. (See the
                                                                 parser document.)

                                                                 _ The parse engine can set [LDTY] to PKI_LTYPE_E::IPFRAG during
                                                                 Layer C processing when it finds that the outer IP packet is fragmented.

                                                                 _ The parse engine can also set [LDTY] to one of PKI_LTYPE_E::UDP_GENEVE,
                                                                 UDP_VXLAN, NVGRE during Layer D processing when it finds the corresponding
                                                                 protocol.

                                                                 [LDTY] is 0x0 (PKI_LTYPE_E::NONE) unless Layer C or D parsing sets it.
                                                                 [LDTY] is unpredictable when [ERRLEV] \<= LD. [LDTY] bits are always set
                                                                 when corresponding PKI_STYLE()_WQ2\<47:43\> bits are set.

                                                                 Internal:
                                                                 [LDTY] = PKI_BEWQ_S[LDTY] | PKI_STYLE()_WQ2\<47:43\> */
        uint64_t lcty                  : 5;  /**< [170:166] Layer C header type parsed, typically corresponding to outer IP. Enumerated by
                                                                 PKI_LTYPE_E. See also [LCPTR]. (See the parser document.)

                                                                 _ The parse engine can set [LCTY] to one of PKI_LTYPE_E::IP4, IP4_OPT,
                                                                 IP6, IP6_OPT during Layer C parsing when it finds the corresponding
                                                                 protocol.

                                                                 _ The parse engine can set [LCTY] to PKI_LTYPE_E::IPv4, ARP,
                                                                 RARP, or SNAP_PAYLD during layer B parsing when it finds MPLS, ARP,
                                                                 RARP, or SNAP without IP, respectively.

                                                                 [LCTY] is 0x0 (PKI_LTYPE_E::NONE) unless Layer B or C parsing sets it.
                                                                 [LCTY] is unpredictable when [ERRLEV] \<= LC. [LCTY] bits are always set
                                                                 when corresponding PKI_STYLE()_WQ2\<42:38\> bits are set.

                                                                 Internal:
                                                                 [LCTY] = PKI_BEWQ_S[LCTY] | PKI_STYLE()_WQ2\<42:38\> */
        uint64_t lbty                  : 5;  /**< [165:161] Layer B (non-VLAN) protocol type parsed. Enumerated by PKI_LTYPE_E. See
                                                                 also [LBPTR]. (See the parser document. For VLAN, see [VV,VS,VLPTR].)

                                                                 _ The parse engine sets [LBTY] to action[SETTY] on a
                                                                 PKI_PCAM_TERM_E::ETHTYPE0..3 PCAM hit when action[SETTY]!=PKI_LTYPE_E::VLAN.

                                                                 [LBTY] is 0x0 (PKI_LTYPE_E::NONE) unless Layer B PCAM parsing sets it via
                                                                 PKI_CL()_PCAM()_ACTION()[SETTY]. [LBTY] is unpredictable when
                                                                 [ERRLEV] \<= LB. [LBTY] bits are always set when corresponding
                                                                 PKI_STYLE()_WQ2\<37:33\> bits are set.

                                                                 Internal:
                                                                 [LBTY] = PKI_BEWQ_S[LBTY] | PKI_STYLE()_WQ2\<37:33\> */
        uint64_t lae                   : 1;  /**< [160:160] Indicates that Layer A Ethernet was parsed, typically used to indicate Layer 2
                                                                 parsing.

                                                                 [LAE] is clear when L2 is not parsed, and it unpredictable when [ERRLEV] = LA.
                                                                 [LAE] is always set when PKI_STYLE()_WQ2\<32\> is set.

                                                                 Internal:
                                                                 [LAE] = PKI_BEWQ_S[LAE] | PKI_STYLE()_WQ2\<32\> */
        uint64_t reserved_152_159      : 8;
        uint64_t vv                    : 1;  /**< [151:151] One or more VLAN fields were found in the L2 HDR for the packet. This bit
                                                                 asserts when in skip-to-L2 mode and the PCAM lookup indicated a VLAN flow
                                                                 (PKI_CL()_PCAM()_TERM()[TERM] = ETHTYPE0..3, DSA, or GLORT matched with the
                                                                 corresponding PKI_CL()_PCAM()_ACTION()[SETTY] = VLAN.

                                                                 [VV] is clear when [LAE] is clear (before ORing PKI_STYLE()_WQ2\<32\> to [LAE]).
                                                                 [VV] is unpredictable when [ERRLEV] \<= LA. [VV] is always set when
                                                                 PKI_STYLE()_WQ2\<23\> is set.

                                                                 Internal:
                                                                 [VV] = PKI_BEWQ_S[VV] | PKI_STYLE()_WQ2\<23\> */
        uint64_t vs                    : 1;  /**< [150:150] Multiple VLAN fields were found in the L2 HDR for the packet, with 'found' as
                                                                 described under [VV]. VLAN fields can be found in ordinary VLAN headers,
                                                                 GLORT, or DSA.

                                                                 [VS] is clear when [VV]=0 (before ORing PKI_STYLE()_WQ2\<23\> to [VV]).
                                                                 [VS] is unpredictable when [ERRLEV] \<= LA. [VS] is always set when
                                                                 PKI_STYLE()_WQ2\<22\> is set.

                                                                 Internal:
                                                                 [VS] = PKI_BEWQ_S[VS] | PKI_STYLE()_WQ2\<22\> */
        uint64_t sh                    : 1;  /**< [149:149] PKI BE incremented special-handling statistics.

                                                                 [SH] is set when PKI_STYLE()_WQ2\<21\> is set.

                                                                 Internal:
                                                                 [SH] = PKI_BEWQ_S[SH] | PKI_STYLE()_WQ2\<21\>

                                                                 Microcode is capable of setting this field, but does not at present. */
        uint64_t pf4                   : 1;  /**< [148:148] Opaque to PKI hardware. Software may wish to use this bit to indicate a particular
                                                                 protocol.

                                                                 PKI sets [PF4] to indicate that a PCAM entry set flag 4, otherwise clear unless
                                                                 set by a PCAM action, and unpredictable if the data fed into that PCAM match is
                                                                 unpredictable such as due to a L2 data error.

                                                                 [PF3] is always set when PKI_STYLE()_WQ2\<20\> is set.

                                                                 Internal:
                                                                 [PF4] = PKI_BEWQ_S[PF4] | PKI_STYLE()_WQ2\<20\> */
        uint64_t pf3                   : 1;  /**< [147:147] Opaque to PKI hardware. Software may wish to use this bit to indicate a particular
                                                                 protocol.

                                                                 PKI sets [PF3] to indicate that a PCAM entry set flag 3, otherwise clear unless
                                                                 set by a PCAM action, and unpredictable if the data fed into that PCAM match is
                                                                 unpredictable such as due to a L2 data error.

                                                                 [PF3] is always set when PKI_STYLE()_WQ2\<19\> is set.

                                                                 Internal:
                                                                 [PF3] = PKI_BEWQ_S[PF3] | PKI_STYLE()_WQ2\<19\> */
        uint64_t pf2                   : 1;  /**< [146:146] Opaque to PKI hardware. Software may wish to use this bit to indicate a particular
                                                                 protocol.

                                                                 PKI sets [PF2] to indicate that a PCAM entry set flag 2, otherwise clear unless
                                                                 set by a PCAM action, and unpredictable if the data fed into that PCAM match is
                                                                 unpredictable such as due to a L2 data error.

                                                                 [PF2] is always set when PKI_STYLE()_WQ2\<18\> is set.

                                                                 Internal:
                                                                 [PF2] = PKI_BEWQ_S[PF2] | PKI_STYLE()_WQ2\<18\> */
        uint64_t pf1                   : 1;  /**< [145:145] Opaque to PKI hardware. Software may wish to use this bit to indicate a particular
                                                                 protocol.

                                                                 PKI sets [PF1] to indicate that a PCAM entry set flag 1, otherwise clear unless
                                                                 set by a PCAM action, and unpredictable if the data fed into that PCAM match is
                                                                 unpredictable such as due to a L2 data error.

                                                                 [PF1] is always set when PKI_STYLE()_WQ2\<17\> is set.

                                                                 Internal:
                                                                 [PF1] = PKI_BEWQ_S[PF1] | PKI_STYLE()_WQ2\<17\> */
        uint64_t l3fr                  : 1;  /**< [144:144] Set when the outer IP (Layer C) indicates a fragment.

                                                                 For IPv4, parse engine sets this bit when either the MF bit is set or the offset
                                                                 field is nonzero.

                                                                 For IPv6, parse engine sets this bit is set when the initial next header value is
                                                                 fragmentation (i.e. 44).

                                                                 [L3FR] is clear when [LCTY] is not an IP4 nor IP6 type (before ORing
                                                                 PKI_STYLE()_WQ2\<42:38\> to [LCTY]). [L3FR] is unpredictable when [ERRLEV] \<= LC.
                                                                 [L3FR] is always set when PKI_STYLE()_WQ2\<16\> is set.

                                                                 Internal:
                                                                 [L3FR] = PKI_BEWQ_S[L3FR] | PKI_STYLE()_WQ2\<16\> */
        uint64_t l3b                   : 1;  /**< [143:143] Set when the outer IP4 indicates broadcast, i.e. the destination address is all
                                                                 ones. Broadcast is not defined for IPv6.

                                                                 [L3B] is clear when [LCTY] is not an IP4 type (before ORing
                                                                 PKI_STYLE()_WQ2\<42:38\> to [LCTY]). [L3B] is unpredictable when [ERRLEV] \<= LC.
                                                                 [L3B] is always set when PKI_STYLE()_WQ2\<15\> is set.

                                                                 Internal:
                                                                 [L3B] = PKI_BEWQ_S[L3B] | PKI_STYLE()_WQ2\<15\> */
        uint64_t l3m                   : 1;  /**< [142:142] Set when the outer IP indicates multicast, i.e. the IPv4 destination address
                                                                 \<31:28\> = 0xE, or the IPv6 MSB of the 128-bit destination address = 0xFF.

                                                                 [L3M] is clear when [LCTY] is not an IP4 nor IP6 type (before ORing
                                                                 PKI_STYLE()_WQ2\<42:38\> to [LCTY]). [L3M] is unpredictable when [ERRLEV] \<= LC.
                                                                 [L3M] is always set when PKI_STYLE()_WQ2\<14\> is set.

                                                                 Internal:
                                                                 [L3M] = PKI_BEWQ_S[L3M] | PKI_STYLE()_WQ2\<14\> */
        uint64_t l2b                   : 1;  /**< [141:141] Set when the packet's destination MAC address field in the L2 HDR is the
                                                                 broadcast address (i.e. all 1s).

                                                                 [L2B] is clear when [LAE] is clear (before ORing PKI_STYLE()_WQ2\<32\> to [LAE]).
                                                                 [L2B] is unpredictable when [ERRLEV] \<= LB. [L2B] is always set when PKI_STYLE()_WQ2\<13\>
                                                                 is set.

                                                                 Internal:
                                                                 [L2B] = PKI_BEWQ_S[L2B] | PKI_STYLE()_WQ2\<13\> */
        uint64_t l2m                   : 1;  /**< [140:140] Set when the packet's destination MAC address field in the L2 HDR is a multicast
                                                                 address (i.e. the LSB of the first byte of the destination MAC is set, and
                                                                 the address is not a broadcast address - see [L2B]).

                                                                 [L2M] is clear when [LAE] is clear (before ORing PKI_STYLE()_WQ2\<32\> to [LAE]).
                                                                 [L2M] is unpredictable when [ERRLEV] \<= LB. [L2M] is always set when PKI_STYLE()_WQ2\<12\>
                                                                 is set.

                                                                 Internal:
                                                                 [L2M] = PKI_BEWQ_S[L2M] | PKI_STYLE()_WQ2\<12\> */
        uint64_t raw                   : 1;  /**< [139:139] Raw packet, for unique statistics and drop handling.

                                                                 [RAW] is set when PKI_INST_HDR_S[RAW] is set and parsed. [RAW] is unpredictable
                                                                 when [ERRLEV] \<= LB. [RAW] is always set when PKI_STYLE()_WQ2\<11\> is set.

                                                                 Internal:
                                                                 [RAW] = PKI_BEWQ_S[RAW] | PKI_STYLE()_WQ2\<11\>. */
        uint64_t errlev                : 3;  /**< [138:136] Normally zero, but when errors are detected contains the lowest protocol layer
                                                                 containing an error, and [OPCODE] will indicate the precise error
                                                                 reason. Enumerated by PKI_ERRLEV_E. PKI_STYLE()_WQ2\<10:8\> may modify [ERRLEV]
                                                                 (before hardware error checks).

                                                                 Note that these descriptions often refers to e.g. 'PKI_WQE_S[ERRLEV] \<= LC';
                                                                 this is a shorthand for 'all errors at LC and below', that is more precisely,
                                                                 '[ERRLEV] = (RE or LB or LC) and [OPCODE] != 0x0'. This is not true when
                                                                 [ERRLEV] = (NONE nor LD nor LE nor LF), nor when [OPCODE] = 0x0 (no error at
                                                                 all).

                                                                 Internal:
                                                                 Calculated by microcode and possibly modified by the PKI BE. [ERRLEV] may
                                                                 (or may not) be PKI_BEWQ_S[ERRLEV]. PKI_ERRLEV_E describes which are done
                                                                 by microcode, and which by hardware. */
        uint64_t opcode                : 8;  /**< [135:128] Normally zero, but when nonzero and [ERRLEV] is nonzero, contains an exception
                                                                 opcode enumerated by PKI_OPCODE_E. PKI_STYLE()_WQ2\<7:0\> may modify [OPCODE]
                                                                 (before hardware error checks).

                                                                 [OPCODE]\<i\> will generally be set when PKI_STYLE()_WQ2[DATA]\<i\> is set.

                                                                 Internal:
                                                                 Calculated by microcode and possibly modified by the PKI BE. [OPCODE] may
                                                                 (or may not) be PKI_BEWQ_S[OPCODE]. PKI_OPCODE_E describes which are done
                                                                 by microcode, and which by hardware. */
#else /* Word 2 - Little Endian */
        uint64_t opcode                : 8;  /**< [135:128] Normally zero, but when nonzero and [ERRLEV] is nonzero, contains an exception
                                                                 opcode enumerated by PKI_OPCODE_E. PKI_STYLE()_WQ2\<7:0\> may modify [OPCODE]
                                                                 (before hardware error checks).

                                                                 [OPCODE]\<i\> will generally be set when PKI_STYLE()_WQ2[DATA]\<i\> is set.

                                                                 Internal:
                                                                 Calculated by microcode and possibly modified by the PKI BE. [OPCODE] may
                                                                 (or may not) be PKI_BEWQ_S[OPCODE]. PKI_OPCODE_E describes which are done
                                                                 by microcode, and which by hardware. */
        uint64_t errlev                : 3;  /**< [138:136] Normally zero, but when errors are detected contains the lowest protocol layer
                                                                 containing an error, and [OPCODE] will indicate the precise error
                                                                 reason. Enumerated by PKI_ERRLEV_E. PKI_STYLE()_WQ2\<10:8\> may modify [ERRLEV]
                                                                 (before hardware error checks).

                                                                 Note that these descriptions often refers to e.g. 'PKI_WQE_S[ERRLEV] \<= LC';
                                                                 this is a shorthand for 'all errors at LC and below', that is more precisely,
                                                                 '[ERRLEV] = (RE or LB or LC) and [OPCODE] != 0x0'. This is not true when
                                                                 [ERRLEV] = (NONE nor LD nor LE nor LF), nor when [OPCODE] = 0x0 (no error at
                                                                 all).

                                                                 Internal:
                                                                 Calculated by microcode and possibly modified by the PKI BE. [ERRLEV] may
                                                                 (or may not) be PKI_BEWQ_S[ERRLEV]. PKI_ERRLEV_E describes which are done
                                                                 by microcode, and which by hardware. */
        uint64_t raw                   : 1;  /**< [139:139] Raw packet, for unique statistics and drop handling.

                                                                 [RAW] is set when PKI_INST_HDR_S[RAW] is set and parsed. [RAW] is unpredictable
                                                                 when [ERRLEV] \<= LB. [RAW] is always set when PKI_STYLE()_WQ2\<11\> is set.

                                                                 Internal:
                                                                 [RAW] = PKI_BEWQ_S[RAW] | PKI_STYLE()_WQ2\<11\>. */
        uint64_t l2m                   : 1;  /**< [140:140] Set when the packet's destination MAC address field in the L2 HDR is a multicast
                                                                 address (i.e. the LSB of the first byte of the destination MAC is set, and
                                                                 the address is not a broadcast address - see [L2B]).

                                                                 [L2M] is clear when [LAE] is clear (before ORing PKI_STYLE()_WQ2\<32\> to [LAE]).
                                                                 [L2M] is unpredictable when [ERRLEV] \<= LB. [L2M] is always set when PKI_STYLE()_WQ2\<12\>
                                                                 is set.

                                                                 Internal:
                                                                 [L2M] = PKI_BEWQ_S[L2M] | PKI_STYLE()_WQ2\<12\> */
        uint64_t l2b                   : 1;  /**< [141:141] Set when the packet's destination MAC address field in the L2 HDR is the
                                                                 broadcast address (i.e. all 1s).

                                                                 [L2B] is clear when [LAE] is clear (before ORing PKI_STYLE()_WQ2\<32\> to [LAE]).
                                                                 [L2B] is unpredictable when [ERRLEV] \<= LB. [L2B] is always set when PKI_STYLE()_WQ2\<13\>
                                                                 is set.

                                                                 Internal:
                                                                 [L2B] = PKI_BEWQ_S[L2B] | PKI_STYLE()_WQ2\<13\> */
        uint64_t l3m                   : 1;  /**< [142:142] Set when the outer IP indicates multicast, i.e. the IPv4 destination address
                                                                 \<31:28\> = 0xE, or the IPv6 MSB of the 128-bit destination address = 0xFF.

                                                                 [L3M] is clear when [LCTY] is not an IP4 nor IP6 type (before ORing
                                                                 PKI_STYLE()_WQ2\<42:38\> to [LCTY]). [L3M] is unpredictable when [ERRLEV] \<= LC.
                                                                 [L3M] is always set when PKI_STYLE()_WQ2\<14\> is set.

                                                                 Internal:
                                                                 [L3M] = PKI_BEWQ_S[L3M] | PKI_STYLE()_WQ2\<14\> */
        uint64_t l3b                   : 1;  /**< [143:143] Set when the outer IP4 indicates broadcast, i.e. the destination address is all
                                                                 ones. Broadcast is not defined for IPv6.

                                                                 [L3B] is clear when [LCTY] is not an IP4 type (before ORing
                                                                 PKI_STYLE()_WQ2\<42:38\> to [LCTY]). [L3B] is unpredictable when [ERRLEV] \<= LC.
                                                                 [L3B] is always set when PKI_STYLE()_WQ2\<15\> is set.

                                                                 Internal:
                                                                 [L3B] = PKI_BEWQ_S[L3B] | PKI_STYLE()_WQ2\<15\> */
        uint64_t l3fr                  : 1;  /**< [144:144] Set when the outer IP (Layer C) indicates a fragment.

                                                                 For IPv4, parse engine sets this bit when either the MF bit is set or the offset
                                                                 field is nonzero.

                                                                 For IPv6, parse engine sets this bit is set when the initial next header value is
                                                                 fragmentation (i.e. 44).

                                                                 [L3FR] is clear when [LCTY] is not an IP4 nor IP6 type (before ORing
                                                                 PKI_STYLE()_WQ2\<42:38\> to [LCTY]). [L3FR] is unpredictable when [ERRLEV] \<= LC.
                                                                 [L3FR] is always set when PKI_STYLE()_WQ2\<16\> is set.

                                                                 Internal:
                                                                 [L3FR] = PKI_BEWQ_S[L3FR] | PKI_STYLE()_WQ2\<16\> */
        uint64_t pf1                   : 1;  /**< [145:145] Opaque to PKI hardware. Software may wish to use this bit to indicate a particular
                                                                 protocol.

                                                                 PKI sets [PF1] to indicate that a PCAM entry set flag 1, otherwise clear unless
                                                                 set by a PCAM action, and unpredictable if the data fed into that PCAM match is
                                                                 unpredictable such as due to a L2 data error.

                                                                 [PF1] is always set when PKI_STYLE()_WQ2\<17\> is set.

                                                                 Internal:
                                                                 [PF1] = PKI_BEWQ_S[PF1] | PKI_STYLE()_WQ2\<17\> */
        uint64_t pf2                   : 1;  /**< [146:146] Opaque to PKI hardware. Software may wish to use this bit to indicate a particular
                                                                 protocol.

                                                                 PKI sets [PF2] to indicate that a PCAM entry set flag 2, otherwise clear unless
                                                                 set by a PCAM action, and unpredictable if the data fed into that PCAM match is
                                                                 unpredictable such as due to a L2 data error.

                                                                 [PF2] is always set when PKI_STYLE()_WQ2\<18\> is set.

                                                                 Internal:
                                                                 [PF2] = PKI_BEWQ_S[PF2] | PKI_STYLE()_WQ2\<18\> */
        uint64_t pf3                   : 1;  /**< [147:147] Opaque to PKI hardware. Software may wish to use this bit to indicate a particular
                                                                 protocol.

                                                                 PKI sets [PF3] to indicate that a PCAM entry set flag 3, otherwise clear unless
                                                                 set by a PCAM action, and unpredictable if the data fed into that PCAM match is
                                                                 unpredictable such as due to a L2 data error.

                                                                 [PF3] is always set when PKI_STYLE()_WQ2\<19\> is set.

                                                                 Internal:
                                                                 [PF3] = PKI_BEWQ_S[PF3] | PKI_STYLE()_WQ2\<19\> */
        uint64_t pf4                   : 1;  /**< [148:148] Opaque to PKI hardware. Software may wish to use this bit to indicate a particular
                                                                 protocol.

                                                                 PKI sets [PF4] to indicate that a PCAM entry set flag 4, otherwise clear unless
                                                                 set by a PCAM action, and unpredictable if the data fed into that PCAM match is
                                                                 unpredictable such as due to a L2 data error.

                                                                 [PF3] is always set when PKI_STYLE()_WQ2\<20\> is set.

                                                                 Internal:
                                                                 [PF4] = PKI_BEWQ_S[PF4] | PKI_STYLE()_WQ2\<20\> */
        uint64_t sh                    : 1;  /**< [149:149] PKI BE incremented special-handling statistics.

                                                                 [SH] is set when PKI_STYLE()_WQ2\<21\> is set.

                                                                 Internal:
                                                                 [SH] = PKI_BEWQ_S[SH] | PKI_STYLE()_WQ2\<21\>

                                                                 Microcode is capable of setting this field, but does not at present. */
        uint64_t vs                    : 1;  /**< [150:150] Multiple VLAN fields were found in the L2 HDR for the packet, with 'found' as
                                                                 described under [VV]. VLAN fields can be found in ordinary VLAN headers,
                                                                 GLORT, or DSA.

                                                                 [VS] is clear when [VV]=0 (before ORing PKI_STYLE()_WQ2\<23\> to [VV]).
                                                                 [VS] is unpredictable when [ERRLEV] \<= LA. [VS] is always set when
                                                                 PKI_STYLE()_WQ2\<22\> is set.

                                                                 Internal:
                                                                 [VS] = PKI_BEWQ_S[VS] | PKI_STYLE()_WQ2\<22\> */
        uint64_t vv                    : 1;  /**< [151:151] One or more VLAN fields were found in the L2 HDR for the packet. This bit
                                                                 asserts when in skip-to-L2 mode and the PCAM lookup indicated a VLAN flow
                                                                 (PKI_CL()_PCAM()_TERM()[TERM] = ETHTYPE0..3, DSA, or GLORT matched with the
                                                                 corresponding PKI_CL()_PCAM()_ACTION()[SETTY] = VLAN.

                                                                 [VV] is clear when [LAE] is clear (before ORing PKI_STYLE()_WQ2\<32\> to [LAE]).
                                                                 [VV] is unpredictable when [ERRLEV] \<= LA. [VV] is always set when
                                                                 PKI_STYLE()_WQ2\<23\> is set.

                                                                 Internal:
                                                                 [VV] = PKI_BEWQ_S[VV] | PKI_STYLE()_WQ2\<23\> */
        uint64_t reserved_152_159      : 8;
        uint64_t lae                   : 1;  /**< [160:160] Indicates that Layer A Ethernet was parsed, typically used to indicate Layer 2
                                                                 parsing.

                                                                 [LAE] is clear when L2 is not parsed, and it unpredictable when [ERRLEV] = LA.
                                                                 [LAE] is always set when PKI_STYLE()_WQ2\<32\> is set.

                                                                 Internal:
                                                                 [LAE] = PKI_BEWQ_S[LAE] | PKI_STYLE()_WQ2\<32\> */
        uint64_t lbty                  : 5;  /**< [165:161] Layer B (non-VLAN) protocol type parsed. Enumerated by PKI_LTYPE_E. See
                                                                 also [LBPTR]. (See the parser document. For VLAN, see [VV,VS,VLPTR].)

                                                                 _ The parse engine sets [LBTY] to action[SETTY] on a
                                                                 PKI_PCAM_TERM_E::ETHTYPE0..3 PCAM hit when action[SETTY]!=PKI_LTYPE_E::VLAN.

                                                                 [LBTY] is 0x0 (PKI_LTYPE_E::NONE) unless Layer B PCAM parsing sets it via
                                                                 PKI_CL()_PCAM()_ACTION()[SETTY]. [LBTY] is unpredictable when
                                                                 [ERRLEV] \<= LB. [LBTY] bits are always set when corresponding
                                                                 PKI_STYLE()_WQ2\<37:33\> bits are set.

                                                                 Internal:
                                                                 [LBTY] = PKI_BEWQ_S[LBTY] | PKI_STYLE()_WQ2\<37:33\> */
        uint64_t lcty                  : 5;  /**< [170:166] Layer C header type parsed, typically corresponding to outer IP. Enumerated by
                                                                 PKI_LTYPE_E. See also [LCPTR]. (See the parser document.)

                                                                 _ The parse engine can set [LCTY] to one of PKI_LTYPE_E::IP4, IP4_OPT,
                                                                 IP6, IP6_OPT during Layer C parsing when it finds the corresponding
                                                                 protocol.

                                                                 _ The parse engine can set [LCTY] to PKI_LTYPE_E::IPv4, ARP,
                                                                 RARP, or SNAP_PAYLD during layer B parsing when it finds MPLS, ARP,
                                                                 RARP, or SNAP without IP, respectively.

                                                                 [LCTY] is 0x0 (PKI_LTYPE_E::NONE) unless Layer B or C parsing sets it.
                                                                 [LCTY] is unpredictable when [ERRLEV] \<= LC. [LCTY] bits are always set
                                                                 when corresponding PKI_STYLE()_WQ2\<42:38\> bits are set.

                                                                 Internal:
                                                                 [LCTY] = PKI_BEWQ_S[LCTY] | PKI_STYLE()_WQ2\<42:38\> */
        uint64_t ldty                  : 5;  /**< [175:171] Layer D header typed parsed, typically corresponding to a virtualization
                                                                 header. Enumerated by PKI_LTYPE_E. See also [LDPTR]. (See the
                                                                 parser document.)

                                                                 _ The parse engine can set [LDTY] to PKI_LTYPE_E::IPFRAG during
                                                                 Layer C processing when it finds that the outer IP packet is fragmented.

                                                                 _ The parse engine can also set [LDTY] to one of PKI_LTYPE_E::UDP_GENEVE,
                                                                 UDP_VXLAN, NVGRE during Layer D processing when it finds the corresponding
                                                                 protocol.

                                                                 [LDTY] is 0x0 (PKI_LTYPE_E::NONE) unless Layer C or D parsing sets it.
                                                                 [LDTY] is unpredictable when [ERRLEV] \<= LD. [LDTY] bits are always set
                                                                 when corresponding PKI_STYLE()_WQ2\<47:43\> bits are set.

                                                                 Internal:
                                                                 [LDTY] = PKI_BEWQ_S[LDTY] | PKI_STYLE()_WQ2\<47:43\> */
        uint64_t lety                  : 5;  /**< [180:176] Layer E header type parsed, often corresponding to inner IP. Enumerated
                                                                 by PKI_LTYPE_E. See also [LEPTR]. (See the parser document.)

                                                                 _ The parse engine can set [LETY] to one of PKI_LTYPE_E::IP4, IP4_OPT,
                                                                 IP6, IP6_OPT during Layer E processing when it finds the corresponding
                                                                 protocol. The parse engine will only do this when [LDTY] is one of
                                                                 PKI_LTYPE_E::UDP_GENEVE, UDP_VXLAN, or NVGRE.

                                                                 [LETY] is 0x0 (PKI_LTYPE_E::NONE) unless Layer E parsing sets it.
                                                                 [LETY] is unpredictable when [ERRLEV] \<= LE. [LETY] bits are always set
                                                                 when corresponding PKI_STYLE()_WQ2\<52:48\> bits are set.

                                                                 Internal:
                                                                 [LETY] = PKI_BEWQ_S[LETY] | PKI_STYLE()_WQ2\<52:48\> */
        uint64_t lfty                  : 5;  /**< [185:181] Layer F header type parsed, often corresponding to layer 4 (UDP/TCP).
                                                                 Enumerated by PKI_LTYPE_E. (See the parser document.)

                                                                 _ The parse engine can set [LFTY] to PKI_LTYPE_E::IPFRAG during
                                                                 Layer E processing when it finds that the inner IP packet is fragmented.

                                                                 _ The parse engine can also set [LFTY] to one of PKI_LTYPE_E::IPCOMP,
                                                                 IPSEC_ESP (ESP or AH), GRE, UDP, SCTP, TCP during Layer F processing
                                                                 when it finds the corresponding protocol.

                                                                 [LFTY] is 0x0 (PKI_LTYPE_E::NONE) unless Layer E or F parsing sets it.
                                                                 [LFTY] is unpredictable when [ERRLEV] \<= LF. [LFTY] bits are always set
                                                                 when corresponding PKI_STYLE()_WQ2\<57:53\> bits are set.

                                                                 Internal:
                                                                 [LFTY] = PKI_BEWQ_S[LFTY] | PKI_STYLE()_WQ2\<57:53\> */
        uint64_t lgty                  : 5;  /**< [190:186] Custom header type parsed after normal C, D, E, or F layer parsing.
                                                                 Enumerated by PKI_LTYPE_E. (See the parser document.)

                                                                 [LGTY] is set to a nonzero action[SETTY] on a PCAM hit with PCAM data
                                                                 extracted from a base plus PKI_CL()_PKIND()_LG_CUSTOM[OFFSET] in the
                                                                 following circumstances:

                                                                 _ When PKI_CL()_PKIND()_CFG[LG_CUSTOM_LAYER]=1 and [LCTY]!=PKI_LTYPE_E::NONE,
                                                                 with [LCPTR] as base

                                                                 _ When PKI_CL()_PKIND()_CFG[LG_CUSTOM_LAYER]=2 and [LDTY]!=PKI_LTYPE_E::NONE,
                                                                 with [LDPTR] as base

                                                                 _ When PKI_CL()_PKIND()_CFG[LG_CUSTOM_LAYER]=3 and [LETY]!=PKI_LTYPE_E::NONE,
                                                                 with [LEPTR] as base

                                                                 _ When PKI_CL()_PKIND()_CFG[LG_CUSTOM_LAYER]=4 and [LFTY]!=PKI_LTYPE_E::NONE,
                                                                 with [LFPTR] as base

                                                                 [LGTY] is 0x0 (PKI_LTYPE_E::NONE) unless set after normal C, D, E, or F
                                                                 layer parsing via PKI_CL()_PCAM()_ACTION()[SETTY]. [LGTY] is unpredictable
                                                                 when [ERRLEV] \<= LG. [LGTY] bits are always set when corresponding
                                                                 PKI_STYLE()_WQ2\<62:58\> bits are set.

                                                                 Internal:
                                                                 [LGTY] = PKI_BEWQ_S[LGTY] | PKI_STYLE()_WQ2\<62:58\> */
        uint64_t sw                    : 1;  /**< [191:191] Reserved for software use. [SW] will be set when corresponding
                                                                 PKI_STYLE()_WQ2[DATA]\<63\> is set, but this is not recommended.

                                                                 Internal:
                                                                 [SW] = PKI_BEWQ_S[SW] | PKI_STYLE()_WQ2\<63\>

                                                                 Microcode could set this bit, but doesn't currently. */
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t addr                  : 64; /**< [255:192] Address of the first buffer pointer. When PKI_STYLE()_BUF[DIS_WQ_DAT]=0, ADDR
                                                                 points to the first byte of packet data saved into the work queue entry's
                                                                 buffer. When PKI_STYLE()_BUF[DIS_WQ_DAT]=1, ADDR points to a the first data
                                                                 buffer.

                                                                 [ADDR]\<63:49\> are a sign extension of bit \<48\>. PKI associates the stream ID
                                                                 PKI_QPG_TBLB()[STRM] for all references based off [ADDR].

                                                                 PKI BE solely computes this field. */
#else /* Word 3 - Little Endian */
        uint64_t addr                  : 64; /**< [255:192] Address of the first buffer pointer. When PKI_STYLE()_BUF[DIS_WQ_DAT]=0, ADDR
                                                                 points to the first byte of packet data saved into the work queue entry's
                                                                 buffer. When PKI_STYLE()_BUF[DIS_WQ_DAT]=1, ADDR points to a the first data
                                                                 buffer.

                                                                 [ADDR]\<63:49\> are a sign extension of bit \<48\>. PKI associates the stream ID
                                                                 PKI_QPG_TBLB()[STRM] for all references based off [ADDR].

                                                                 PKI BE solely computes this field. */
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t vlptr                 : 8;  /**< [319:312] Byte pointer two bytes before the first byte of the VLAN ID field
                                                                 (e.g. to the two bytes containing the value PKI_ETHERTYPE_E::VLAN) for
                                                                 the first or second VLAN. Can point to ordinary VLAN, GLORT, or
                                                                 DSA headers.

                                                                 Parse engine computes this field, setting it 0x0 when [VV] = 0, and
                                                                 unpredictable when [ERRLEV] = LA.  If [VS] = 1, PKI_CL()_STYLE()_ALG[WQE_VS]
                                                                 selects which of the two VLAN ID fields (FIRST_VLAN_PTR or LAST_VLAN_PTR)
                                                                 is pointed to here.

                                                                 _ if PKI_CL()_STYLE()_ALG[WQE_VS] = 0, FIRST_VLAN_PTR is selected.

                                                                 _ if PKI_CL()_STYLE()_ALG[WQE_VS] = 1, LAST_VLAN_PTR is selected.

                                                                 PKI BE sets this field when PKI_STYLE()_WQ4[DATA]\<63:56\> are set. */
        uint64_t lgptr                 : 8;  /**< [311:304] Byte pointer to the start of Layer G relative to the start of the packet.
                                                                 See [LGTY].

                                                                 _ When PKI_CL()_PKIND()_CFG[LG_CUSTOM_LAYER]=1 and the parse engine sets
                                                                 [LGTY] during layer C parsing (lookup data relative to [LCPTR]), [LGPTR]
                                                                 is the DPTR after updated by any PKI_PCAM_TERM_E::L3_FLAGS PCAM hit.

                                                                 _ When PKI_CL()_PKIND()_CFG[LG_CUSTOM_LAYER]=2 and the parse engine sets
                                                                 [LGTY] during layer D parsing (lookup data relative to [LDPTR]), [LGPTR]
                                                                 is the DPTR after updated by any PKI_PCAM_TERM_E::LD_VNI PCAM hit. If no
                                                                 PKI_PCAM_TERM_E::LD_VNI PCAM updates the DPTR, [LGPTR] will point just
                                                                 after the Geneve, VXLAN / VXLAN GPE, or GRE header.

                                                                 _ When PKI_CL()_PKIND()_CFG[LG_CUSTOM_LAYER]=3 and the parse engine sets
                                                                 [LGTY] during layer E parsing (lookup data relative to [LEPTR]), [LGPTR]
                                                                 is the DPTR after updated by any PKI_PCAM_TERM_E::IL3_FLAGS PCAM hit.

                                                                 _ When PKI_CL()_PKIND()_CFG[LG_CUSTOM_LAYER]=4 and the parse engine sets
                                                                 [LGTY] during layer G parsing (lookup data relative to [LFPTR]), [LGPTR]
                                                                 is the DPTR after all non-Layer-G parsing.

                                                                 Parse engine computes this field, setting it 0x0 when [LGTY] = NONE, and
                                                                 unpredictable when [ERRLEV] \<= LG.

                                                                 PKI BE sets this field when PKI_STYLE()_WQ4[DATA]\<55:48\> are set. */
        uint64_t lfptr                 : 8;  /**< [303:296] Byte pointer to the start of Layer F relative to the start of the packet.
                                                                 See [LFTY].

                                                                 _ When the parse engine sets [LFTY] to PKI_LTYPE_E::IPFRAG during Layer E
                                                                 parsing, [LFPTR] points to the inner IPv4 header or 8 bytes past the IPv6
                                                                 fragmentation extension header.

                                                                 _ When the parse engine sets [LFTY] to one of PKI_LTYPE_E::IPCOMP,
                                                                 IPSEC_ESP (ESP or AH), GRE, UDP, SCTP, TCP during Layer F processing,
                                                                 [LDPTR] points to the corresponding header.

                                                                 Parse engine computes this field, setting it 0x0 when [LFTY] = NONE, and
                                                                 unpredictable when [ERRLEV] \<= LF.

                                                                 PKI BE sets this field when PKI_STYLE()_WQ4[DATA]\<47:40\> are set. */
        uint64_t leptr                 : 8;  /**< [295:288] Byte pointer to the start of Layer E relative to the start of the packet.
                                                                 See [LETY].

                                                                 _ When the parse engine sets [LETY] during Layer E parsing (IP4, IP4_OPT,
                                                                 IP6, IP6_OPT), [LEPTR] is the DPTR at the beginning of Layer E
                                                                 parsing (which should be the beginning of the inner IP header).

                                                                 Parse engine computes this field, setting it 0x0 when [LETY] = NONE, and
                                                                 unpredictable when [ERRLEV] \<= LE.

                                                                 PKI BE sets this field when PKI_STYLE()_WQ4[DATA]\<39:32\> are set. */
        uint64_t ldptr                 : 8;  /**< [287:280] Byte pointer to the start of Layer D relative to the start of the packet.
                                                                 See [LDTY].

                                                                 _ When the parse engine sets [LDTY] to PKI_LTYPE_E::IPFRAG during Layer C
                                                                 parsing, [LDPTR] points to the outer IPv4 header or 8 bytes past the IPv6
                                                                 fragmentation extension header.

                                                                 _ When the parse engine sets [LDTY] to PKI_LTYPE_E::UDP_GENEVE or
                                                                 PKI_LTYPE_E::UDP_VXLAN during layer D parsing, [LDPTR] points to the UDP
                                                                 header prior to the Geneve/VXLAN/VXLANGPE header.

                                                                 _ When the parse engine sets [LDTY] to PKI_LTYPE_E::NVGRE, [LDPTR] points
                                                                 to the GRE header.

                                                                 Parse engine computes this field, setting it 0x0 when [LDTY] = NONE, and
                                                                 unpredictable when [ERRLEV] \<= LD.

                                                                 PKI BE sets this field when PKI_STYLE()_WQ4[DATA]\<31:24\> are set. */
        uint64_t lcptr                 : 8;  /**< [279:272] Byte pointer to the start of Layer C relative to the start of the packet.
                                                                 See [LCTY].

                                                                 _ When the parse engine sets [LCTY] during Layer B parsing (MPLS, ARP,
                                                                 REVARP, SNAP_PAYLD), [LCPTR] points immediately after the last parsed
                                                                 Ethertype.

                                                                 _ When the parse engine sets [LCTY] during Layer C parsing (IP4, IP4_OPT,
                                                                 IP6, IP6_OPT), [LCPTR] is the DPTR at the beginning of Layer C
                                                                 parsing (which should be the beginning of the IP header).

                                                                 Parse engine computes this field, setting it 0x0 when [LCTY] = NONE, and
                                                                 unpredictable when [ERRLEV] \<= LC.

                                                                 PKI BE sets this field when PKI_STYLE()_WQ4[DATA]\<23:16\> are set. */
        uint64_t lbptr                 : 8;  /**< [271:264] Byte pointer to the start of Layer B relative to the start of the packet.
                                                                 Byte pointer to the start of (non-VLAN) Layer B relative to the start of
                                                                 the packet. See [LBTY]. For VLAN, see [VV,VS,VLPTR].

                                                                 _ The parse engine sets [LBPTR] to the beginning of the ethertype
                                                                 field used for the PKI_PCAM_TERM_E::ETHTYPE0..3 lookup when it sets
                                                                 [LBTY].

                                                                 Parse engine computes this field, setting it 0x0 when [LBTY] = NONE, and
                                                                 unpredictable when [ERRLEV] \<= LB.

                                                                 PKI BE sets this field when PKI_STYLE()_WQ4[DATA]\<15:8\> are set. */
        uint64_t laptr                 : 8;  /**< [263:256] Byte pointer to the start of the Ethernet header (i.e. the start of
                                                                 the Ethernet destination address) relative to the start of the packet
                                                                 when [LAE] is set.

                                                                 Parse engine computes this field, setting it 0x0 when [LAE] is clear, and
                                                                 unpredictable when [ERRLEV] \<= LA.

                                                                 PKI BE sets this field when PKI_STYLE()_WQ4[DATA]\<7:0\> are set. */
#else /* Word 4 - Little Endian */
        uint64_t laptr                 : 8;  /**< [263:256] Byte pointer to the start of the Ethernet header (i.e. the start of
                                                                 the Ethernet destination address) relative to the start of the packet
                                                                 when [LAE] is set.

                                                                 Parse engine computes this field, setting it 0x0 when [LAE] is clear, and
                                                                 unpredictable when [ERRLEV] \<= LA.

                                                                 PKI BE sets this field when PKI_STYLE()_WQ4[DATA]\<7:0\> are set. */
        uint64_t lbptr                 : 8;  /**< [271:264] Byte pointer to the start of Layer B relative to the start of the packet.
                                                                 Byte pointer to the start of (non-VLAN) Layer B relative to the start of
                                                                 the packet. See [LBTY]. For VLAN, see [VV,VS,VLPTR].

                                                                 _ The parse engine sets [LBPTR] to the beginning of the ethertype
                                                                 field used for the PKI_PCAM_TERM_E::ETHTYPE0..3 lookup when it sets
                                                                 [LBTY].

                                                                 Parse engine computes this field, setting it 0x0 when [LBTY] = NONE, and
                                                                 unpredictable when [ERRLEV] \<= LB.

                                                                 PKI BE sets this field when PKI_STYLE()_WQ4[DATA]\<15:8\> are set. */
        uint64_t lcptr                 : 8;  /**< [279:272] Byte pointer to the start of Layer C relative to the start of the packet.
                                                                 See [LCTY].

                                                                 _ When the parse engine sets [LCTY] during Layer B parsing (MPLS, ARP,
                                                                 REVARP, SNAP_PAYLD), [LCPTR] points immediately after the last parsed
                                                                 Ethertype.

                                                                 _ When the parse engine sets [LCTY] during Layer C parsing (IP4, IP4_OPT,
                                                                 IP6, IP6_OPT), [LCPTR] is the DPTR at the beginning of Layer C
                                                                 parsing (which should be the beginning of the IP header).

                                                                 Parse engine computes this field, setting it 0x0 when [LCTY] = NONE, and
                                                                 unpredictable when [ERRLEV] \<= LC.

                                                                 PKI BE sets this field when PKI_STYLE()_WQ4[DATA]\<23:16\> are set. */
        uint64_t ldptr                 : 8;  /**< [287:280] Byte pointer to the start of Layer D relative to the start of the packet.
                                                                 See [LDTY].

                                                                 _ When the parse engine sets [LDTY] to PKI_LTYPE_E::IPFRAG during Layer C
                                                                 parsing, [LDPTR] points to the outer IPv4 header or 8 bytes past the IPv6
                                                                 fragmentation extension header.

                                                                 _ When the parse engine sets [LDTY] to PKI_LTYPE_E::UDP_GENEVE or
                                                                 PKI_LTYPE_E::UDP_VXLAN during layer D parsing, [LDPTR] points to the UDP
                                                                 header prior to the Geneve/VXLAN/VXLANGPE header.

                                                                 _ When the parse engine sets [LDTY] to PKI_LTYPE_E::NVGRE, [LDPTR] points
                                                                 to the GRE header.

                                                                 Parse engine computes this field, setting it 0x0 when [LDTY] = NONE, and
                                                                 unpredictable when [ERRLEV] \<= LD.

                                                                 PKI BE sets this field when PKI_STYLE()_WQ4[DATA]\<31:24\> are set. */
        uint64_t leptr                 : 8;  /**< [295:288] Byte pointer to the start of Layer E relative to the start of the packet.
                                                                 See [LETY].

                                                                 _ When the parse engine sets [LETY] during Layer E parsing (IP4, IP4_OPT,
                                                                 IP6, IP6_OPT), [LEPTR] is the DPTR at the beginning of Layer E
                                                                 parsing (which should be the beginning of the inner IP header).

                                                                 Parse engine computes this field, setting it 0x0 when [LETY] = NONE, and
                                                                 unpredictable when [ERRLEV] \<= LE.

                                                                 PKI BE sets this field when PKI_STYLE()_WQ4[DATA]\<39:32\> are set. */
        uint64_t lfptr                 : 8;  /**< [303:296] Byte pointer to the start of Layer F relative to the start of the packet.
                                                                 See [LFTY].

                                                                 _ When the parse engine sets [LFTY] to PKI_LTYPE_E::IPFRAG during Layer E
                                                                 parsing, [LFPTR] points to the inner IPv4 header or 8 bytes past the IPv6
                                                                 fragmentation extension header.

                                                                 _ When the parse engine sets [LFTY] to one of PKI_LTYPE_E::IPCOMP,
                                                                 IPSEC_ESP (ESP or AH), GRE, UDP, SCTP, TCP during Layer F processing,
                                                                 [LDPTR] points to the corresponding header.

                                                                 Parse engine computes this field, setting it 0x0 when [LFTY] = NONE, and
                                                                 unpredictable when [ERRLEV] \<= LF.

                                                                 PKI BE sets this field when PKI_STYLE()_WQ4[DATA]\<47:40\> are set. */
        uint64_t lgptr                 : 8;  /**< [311:304] Byte pointer to the start of Layer G relative to the start of the packet.
                                                                 See [LGTY].

                                                                 _ When PKI_CL()_PKIND()_CFG[LG_CUSTOM_LAYER]=1 and the parse engine sets
                                                                 [LGTY] during layer C parsing (lookup data relative to [LCPTR]), [LGPTR]
                                                                 is the DPTR after updated by any PKI_PCAM_TERM_E::L3_FLAGS PCAM hit.

                                                                 _ When PKI_CL()_PKIND()_CFG[LG_CUSTOM_LAYER]=2 and the parse engine sets
                                                                 [LGTY] during layer D parsing (lookup data relative to [LDPTR]), [LGPTR]
                                                                 is the DPTR after updated by any PKI_PCAM_TERM_E::LD_VNI PCAM hit. If no
                                                                 PKI_PCAM_TERM_E::LD_VNI PCAM updates the DPTR, [LGPTR] will point just
                                                                 after the Geneve, VXLAN / VXLAN GPE, or GRE header.

                                                                 _ When PKI_CL()_PKIND()_CFG[LG_CUSTOM_LAYER]=3 and the parse engine sets
                                                                 [LGTY] during layer E parsing (lookup data relative to [LEPTR]), [LGPTR]
                                                                 is the DPTR after updated by any PKI_PCAM_TERM_E::IL3_FLAGS PCAM hit.

                                                                 _ When PKI_CL()_PKIND()_CFG[LG_CUSTOM_LAYER]=4 and the parse engine sets
                                                                 [LGTY] during layer G parsing (lookup data relative to [LFPTR]), [LGPTR]
                                                                 is the DPTR after all non-Layer-G parsing.

                                                                 Parse engine computes this field, setting it 0x0 when [LGTY] = NONE, and
                                                                 unpredictable when [ERRLEV] \<= LG.

                                                                 PKI BE sets this field when PKI_STYLE()_WQ4[DATA]\<55:48\> are set. */
        uint64_t vlptr                 : 8;  /**< [319:312] Byte pointer two bytes before the first byte of the VLAN ID field
                                                                 (e.g. to the two bytes containing the value PKI_ETHERTYPE_E::VLAN) for
                                                                 the first or second VLAN. Can point to ordinary VLAN, GLORT, or
                                                                 DSA headers.

                                                                 Parse engine computes this field, setting it 0x0 when [VV] = 0, and
                                                                 unpredictable when [ERRLEV] = LA.  If [VS] = 1, PKI_CL()_STYLE()_ALG[WQE_VS]
                                                                 selects which of the two VLAN ID fields (FIRST_VLAN_PTR or LAST_VLAN_PTR)
                                                                 is pointed to here.

                                                                 _ if PKI_CL()_STYLE()_ALG[WQE_VS] = 0, FIRST_VLAN_PTR is selected.

                                                                 _ if PKI_CL()_STYLE()_ALG[WQE_VS] = 1, LAST_VLAN_PTR is selected.

                                                                 PKI BE sets this field when PKI_STYLE()_WQ4[DATA]\<63:56\> are set. */
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t size                  : 16; /**< [383:368] Size of the first buffer pointer. When the packet data fits in a single buffer,
                                                                 SIZE represents the number of bytes in the buffer and may be larger than [LEN].

                                                                 PKI BE solely computes this field. */
        uint64_t dwd                   : 1;  /**< [367:367] Indicates [ADDR] points to a different buffer than the buffer containing the
                                                                 WQE, from value of PKI_STYLE()_BUF[DIS_WQ_DAT].

                                                                 PKI BE solely computes this field. */
        uint64_t reserved_320_366      : 47;
#else /* Word 5 - Little Endian */
        uint64_t reserved_320_366      : 47;
        uint64_t dwd                   : 1;  /**< [367:367] Indicates [ADDR] points to a different buffer than the buffer containing the
                                                                 WQE, from value of PKI_STYLE()_BUF[DIS_WQ_DAT].

                                                                 PKI BE solely computes this field. */
        uint64_t size                  : 16; /**< [383:368] Size of the first buffer pointer. When the packet data fits in a single buffer,
                                                                 SIZE represents the number of bytes in the buffer and may be larger than [LEN].

                                                                 PKI BE solely computes this field. */
#endif /* Word 5 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 6 - Big Endian */
        uint64_t w6                    : 64; /**< [447:384] Packet data may use this word. */
#else /* Word 6 - Little Endian */
        uint64_t w6                    : 64; /**< [447:384] Packet data may use this word. */
#endif /* Word 6 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 7 - Big Endian */
        uint64_t w7                    : 64; /**< [511:448] Packet data may use this word. */
#else /* Word 7 - Little Endian */
        uint64_t w7                    : 64; /**< [511:448] Packet data may use this word. */
#endif /* Word 7 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 8 - Big Endian */
        uint64_t w8                    : 64; /**< [575:512] Packet data may use this word. */
#else /* Word 8 - Little Endian */
        uint64_t w8                    : 64; /**< [575:512] Packet data may use this word. */
#endif /* Word 8 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 9 - Big Endian */
        uint64_t w9                    : 64; /**< [639:576] Packet data may use this word. */
#else /* Word 9 - Little Endian */
        uint64_t w9                    : 64; /**< [639:576] Packet data may use this word. */
#endif /* Word 9 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 10 - Big Endian */
        uint64_t w10                   : 64; /**< [703:640] Packet data may use this word. */
#else /* Word 10 - Little Endian */
        uint64_t w10                   : 64; /**< [703:640] Packet data may use this word. */
#endif /* Word 10 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 11 - Big Endian */
        uint64_t w11                   : 64; /**< [767:704] Packet data may use this word. */
#else /* Word 11 - Little Endian */
        uint64_t w11                   : 64; /**< [767:704] Packet data may use this word. */
#endif /* Word 11 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 12 - Big Endian */
        uint64_t w12                   : 64; /**< [831:768] Packet data may use this word. */
#else /* Word 12 - Little Endian */
        uint64_t w12                   : 64; /**< [831:768] Packet data may use this word. */
#endif /* Word 12 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 13 - Big Endian */
        uint64_t w13                   : 64; /**< [895:832] Packet data may use this word. */
#else /* Word 13 - Little Endian */
        uint64_t w13                   : 64; /**< [895:832] Packet data may use this word. */
#endif /* Word 13 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 14 - Big Endian */
        uint64_t w14                   : 64; /**< [959:896] Packet data may use this word. */
#else /* Word 14 - Little Endian */
        uint64_t w14                   : 64; /**< [959:896] Packet data may use this word. */
#endif /* Word 14 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 15 - Big Endian */
        uint64_t w15                   : 64; /**< [1023:960] Packet data may use this word. */
#else /* Word 15 - Little Endian */
        uint64_t w15                   : 64; /**< [1023:960] Packet data may use this word. */
#endif /* Word 15 - End */
    } s;
    /* struct bdk_pki_wqe_s_s cn; */
};

/**
 * Register (NCB) pki_active0
 *
 * PKI Active 0 Register
 */
union bdk_pki_active0
{
    uint64_t u;
    struct bdk_pki_active0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t pcc_active            : 1;  /**< [  2:  2](RO/H) PBE FPC and FPA bus active. For diagnostic use only; software should use PKI_SFT_RST[ACTIVE]. */
        uint64_t pfe_pib_active        : 1;  /**< [  1:  1](RO/H) PBE FPC and FPA bus active. For diagnostic use only; software should use PKI_SFT_RST[ACTIVE]. */
        uint64_t ptag_active           : 1;  /**< [  0:  0](RO/H) PTAG active. For diagnostic use only; software should use PKI_SFT_RST[ACTIVE]. */
#else /* Word 0 - Little Endian */
        uint64_t ptag_active           : 1;  /**< [  0:  0](RO/H) PTAG active. For diagnostic use only; software should use PKI_SFT_RST[ACTIVE]. */
        uint64_t pfe_pib_active        : 1;  /**< [  1:  1](RO/H) PBE FPC and FPA bus active. For diagnostic use only; software should use PKI_SFT_RST[ACTIVE]. */
        uint64_t pcc_active            : 1;  /**< [  2:  2](RO/H) PBE FPC and FPA bus active. For diagnostic use only; software should use PKI_SFT_RST[ACTIVE]. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_active0_s cn; */
};
typedef union bdk_pki_active0 bdk_pki_active0_t;

#define BDK_PKI_ACTIVE0 BDK_PKI_ACTIVE0_FUNC()
static inline uint64_t BDK_PKI_ACTIVE0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ACTIVE0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000220ll;
    __bdk_csr_fatal("PKI_ACTIVE0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ACTIVE0 bdk_pki_active0_t
#define bustype_BDK_PKI_ACTIVE0 BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ACTIVE0 "PKI_ACTIVE0"
#define device_bar_BDK_PKI_ACTIVE0 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ACTIVE0 0
#define arguments_BDK_PKI_ACTIVE0 -1,-1,-1,-1

/**
 * Register (NCB) pki_active1
 *
 * PKI Active 1 Register
 */
union bdk_pki_active1
{
    uint64_t u;
    struct bdk_pki_active1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t pib_active            : 1;  /**< [  4:  4](RO/H) PBE PIB active. For diagnostic use only; software should use PKI_SFT_RST[ACTIVE]. */
        uint64_t fpc_active            : 1;  /**< [  3:  3](RO/H) PBE FPC and FPA bus active. For diagnostic use only; software should use PKI_SFT_RST[ACTIVE]. */
        uint64_t iobp_active           : 1;  /**< [  2:  2](RO/H) PBE PMW and IOBP bus active. For diagnostic use only; software should use PKI_SFT_RST[ACTIVE]. */
        uint64_t sws_active            : 1;  /**< [  1:  1](RO/H) PBE SWS active. For diagnostic use only; software should use PKI_SFT_RST[ACTIVE]. */
        uint64_t pbtag_active          : 1;  /**< [  0:  0](RO/H) PBE pbtags active. For diagnostic use only; software should use PKI_SFT_RST[ACTIVE]. */
#else /* Word 0 - Little Endian */
        uint64_t pbtag_active          : 1;  /**< [  0:  0](RO/H) PBE pbtags active. For diagnostic use only; software should use PKI_SFT_RST[ACTIVE]. */
        uint64_t sws_active            : 1;  /**< [  1:  1](RO/H) PBE SWS active. For diagnostic use only; software should use PKI_SFT_RST[ACTIVE]. */
        uint64_t iobp_active           : 1;  /**< [  2:  2](RO/H) PBE PMW and IOBP bus active. For diagnostic use only; software should use PKI_SFT_RST[ACTIVE]. */
        uint64_t fpc_active            : 1;  /**< [  3:  3](RO/H) PBE FPC and FPA bus active. For diagnostic use only; software should use PKI_SFT_RST[ACTIVE]. */
        uint64_t pib_active            : 1;  /**< [  4:  4](RO/H) PBE PIB active. For diagnostic use only; software should use PKI_SFT_RST[ACTIVE]. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_active1_s cn; */
};
typedef union bdk_pki_active1 bdk_pki_active1_t;

#define BDK_PKI_ACTIVE1 BDK_PKI_ACTIVE1_FUNC()
static inline uint64_t BDK_PKI_ACTIVE1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ACTIVE1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000230ll;
    __bdk_csr_fatal("PKI_ACTIVE1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ACTIVE1 bdk_pki_active1_t
#define bustype_BDK_PKI_ACTIVE1 BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ACTIVE1 "PKI_ACTIVE1"
#define device_bar_BDK_PKI_ACTIVE1 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ACTIVE1 0
#define arguments_BDK_PKI_ACTIVE1 -1,-1,-1,-1

/**
 * Register (NCB) pki_active2
 *
 * PKI Active 2 Register
 */
union bdk_pki_active2
{
    uint64_t u;
    struct bdk_pki_active2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t pix_active            : 6;  /**< [  5:  0](RO/H) PIX control, ICG active and PIB active. For diagnostic use only; software should use
                                                                 PKI_SFT_RST[ACTIVE]. */
#else /* Word 0 - Little Endian */
        uint64_t pix_active            : 6;  /**< [  5:  0](RO/H) PIX control, ICG active and PIB active. For diagnostic use only; software should use
                                                                 PKI_SFT_RST[ACTIVE]. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_active2_s cn; */
};
typedef union bdk_pki_active2 bdk_pki_active2_t;

#define BDK_PKI_ACTIVE2 BDK_PKI_ACTIVE2_FUNC()
static inline uint64_t BDK_PKI_ACTIVE2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ACTIVE2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000240ll;
    __bdk_csr_fatal("PKI_ACTIVE2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ACTIVE2 bdk_pki_active2_t
#define bustype_BDK_PKI_ACTIVE2 BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ACTIVE2 "PKI_ACTIVE2"
#define device_bar_BDK_PKI_ACTIVE2 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ACTIVE2 0
#define arguments_BDK_PKI_ACTIVE2 -1,-1,-1,-1

/**
 * Register (NCB) pki_alloc_flt#_int
 *
 * PKI FPA Allocate Fault Interrupt Registers
 * This register is indexed by the faulting stream ID \<7:6\>.
 */
union bdk_pki_alloc_fltx_int
{
    uint64_t u;
    struct bdk_pki_alloc_fltx_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t strm_id               : 64; /**< [ 63:  0](R/W1C/H) FPA allocate fault. Each bit is set when the corresponding stream ID \<5:0\> receives
                                                                 a fault from the FPA bus following a pointer allocate request. */
#else /* Word 0 - Little Endian */
        uint64_t strm_id               : 64; /**< [ 63:  0](R/W1C/H) FPA allocate fault. Each bit is set when the corresponding stream ID \<5:0\> receives
                                                                 a fault from the FPA bus following a pointer allocate request. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_alloc_fltx_int_s cn; */
};
typedef union bdk_pki_alloc_fltx_int bdk_pki_alloc_fltx_int_t;

static inline uint64_t BDK_PKI_ALLOC_FLTX_INT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ALLOC_FLTX_INT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x86c000000900ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("PKI_ALLOC_FLTX_INT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ALLOC_FLTX_INT(a) bdk_pki_alloc_fltx_int_t
#define bustype_BDK_PKI_ALLOC_FLTX_INT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ALLOC_FLTX_INT(a) "PKI_ALLOC_FLTX_INT"
#define device_bar_BDK_PKI_ALLOC_FLTX_INT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ALLOC_FLTX_INT(a) (a)
#define arguments_BDK_PKI_ALLOC_FLTX_INT(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_alloc_flt#_int_ena_w1c
 *
 * PKI FPA Allocate Fault Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_pki_alloc_fltx_int_ena_w1c
{
    uint64_t u;
    struct bdk_pki_alloc_fltx_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t strm_id               : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for PKI_ALLOC_FLT(0..3)_INT[STRM_ID]. */
#else /* Word 0 - Little Endian */
        uint64_t strm_id               : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for PKI_ALLOC_FLT(0..3)_INT[STRM_ID]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_alloc_fltx_int_ena_w1c_s cn; */
};
typedef union bdk_pki_alloc_fltx_int_ena_w1c bdk_pki_alloc_fltx_int_ena_w1c_t;

static inline uint64_t BDK_PKI_ALLOC_FLTX_INT_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ALLOC_FLTX_INT_ENA_W1C(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x86c000000940ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("PKI_ALLOC_FLTX_INT_ENA_W1C", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ALLOC_FLTX_INT_ENA_W1C(a) bdk_pki_alloc_fltx_int_ena_w1c_t
#define bustype_BDK_PKI_ALLOC_FLTX_INT_ENA_W1C(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ALLOC_FLTX_INT_ENA_W1C(a) "PKI_ALLOC_FLTX_INT_ENA_W1C"
#define device_bar_BDK_PKI_ALLOC_FLTX_INT_ENA_W1C(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ALLOC_FLTX_INT_ENA_W1C(a) (a)
#define arguments_BDK_PKI_ALLOC_FLTX_INT_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_alloc_flt#_int_ena_w1s
 *
 * PKI FPA Allocate Fault Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_pki_alloc_fltx_int_ena_w1s
{
    uint64_t u;
    struct bdk_pki_alloc_fltx_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t strm_id               : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for PKI_ALLOC_FLT(0..3)_INT[STRM_ID]. */
#else /* Word 0 - Little Endian */
        uint64_t strm_id               : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for PKI_ALLOC_FLT(0..3)_INT[STRM_ID]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_alloc_fltx_int_ena_w1s_s cn; */
};
typedef union bdk_pki_alloc_fltx_int_ena_w1s bdk_pki_alloc_fltx_int_ena_w1s_t;

static inline uint64_t BDK_PKI_ALLOC_FLTX_INT_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ALLOC_FLTX_INT_ENA_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x86c000000960ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("PKI_ALLOC_FLTX_INT_ENA_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ALLOC_FLTX_INT_ENA_W1S(a) bdk_pki_alloc_fltx_int_ena_w1s_t
#define bustype_BDK_PKI_ALLOC_FLTX_INT_ENA_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ALLOC_FLTX_INT_ENA_W1S(a) "PKI_ALLOC_FLTX_INT_ENA_W1S"
#define device_bar_BDK_PKI_ALLOC_FLTX_INT_ENA_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ALLOC_FLTX_INT_ENA_W1S(a) (a)
#define arguments_BDK_PKI_ALLOC_FLTX_INT_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_alloc_flt#_int_w1s
 *
 * PKI FPA Allocate Fault Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_pki_alloc_fltx_int_w1s
{
    uint64_t u;
    struct bdk_pki_alloc_fltx_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t strm_id               : 64; /**< [ 63:  0](R/W1S/H) Reads or sets PKI_ALLOC_FLT(0..3)_INT[STRM_ID]. */
#else /* Word 0 - Little Endian */
        uint64_t strm_id               : 64; /**< [ 63:  0](R/W1S/H) Reads or sets PKI_ALLOC_FLT(0..3)_INT[STRM_ID]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_alloc_fltx_int_w1s_s cn; */
};
typedef union bdk_pki_alloc_fltx_int_w1s bdk_pki_alloc_fltx_int_w1s_t;

static inline uint64_t BDK_PKI_ALLOC_FLTX_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ALLOC_FLTX_INT_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x86c000000920ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("PKI_ALLOC_FLTX_INT_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ALLOC_FLTX_INT_W1S(a) bdk_pki_alloc_fltx_int_w1s_t
#define bustype_BDK_PKI_ALLOC_FLTX_INT_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ALLOC_FLTX_INT_W1S(a) "PKI_ALLOC_FLTX_INT_W1S"
#define device_bar_BDK_PKI_ALLOC_FLTX_INT_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ALLOC_FLTX_INT_W1S(a) (a)
#define arguments_BDK_PKI_ALLOC_FLTX_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_alloc_flt_debug
 *
 * PKI Alloc Fault Debug Register
 */
union bdk_pki_alloc_flt_debug
{
    uint64_t u;
    struct bdk_pki_alloc_flt_debug_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_29_63        : 35;
        uint64_t valid                 : 1;  /**< [ 28: 28](R/W/H) PKI sets this bit and loads these fields when a pointer allocation returns with
                                                                 fault. Once set, this bit will prevent any further updates to this register by
                                                                 PKI. Software must clear this bit in order for PKI to log any further debug
                                                                 information on fault events. */
        uint64_t gmid                  : 16; /**< [ 27: 12](R/W/H) GMID used for the pointer request that returned a fault. */
        uint64_t aura                  : 12; /**< [ 11:  0](R/W/H) Guest-aura used for the pointer request that returned a fault. */
#else /* Word 0 - Little Endian */
        uint64_t aura                  : 12; /**< [ 11:  0](R/W/H) Guest-aura used for the pointer request that returned a fault. */
        uint64_t gmid                  : 16; /**< [ 27: 12](R/W/H) GMID used for the pointer request that returned a fault. */
        uint64_t valid                 : 1;  /**< [ 28: 28](R/W/H) PKI sets this bit and loads these fields when a pointer allocation returns with
                                                                 fault. Once set, this bit will prevent any further updates to this register by
                                                                 PKI. Software must clear this bit in order for PKI to log any further debug
                                                                 information on fault events. */
        uint64_t reserved_29_63        : 35;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_alloc_flt_debug_s cn; */
};
typedef union bdk_pki_alloc_flt_debug bdk_pki_alloc_flt_debug_t;

#define BDK_PKI_ALLOC_FLT_DEBUG BDK_PKI_ALLOC_FLT_DEBUG_FUNC()
static inline uint64_t BDK_PKI_ALLOC_FLT_DEBUG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ALLOC_FLT_DEBUG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000a00ll;
    __bdk_csr_fatal("PKI_ALLOC_FLT_DEBUG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ALLOC_FLT_DEBUG bdk_pki_alloc_flt_debug_t
#define bustype_BDK_PKI_ALLOC_FLT_DEBUG BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ALLOC_FLT_DEBUG "PKI_ALLOC_FLT_DEBUG"
#define device_bar_BDK_PKI_ALLOC_FLT_DEBUG 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ALLOC_FLT_DEBUG 0
#define arguments_BDK_PKI_ALLOC_FLT_DEBUG -1,-1,-1,-1

/**
 * Register (NCB) pki_aura#_cfg
 *
 * PKI Aura Configuration Register
 * This register configures aura backpressure, etc. It is indexed by VHAURA.
 */
union bdk_pki_aurax_cfg
{
    uint64_t u;
    struct bdk_pki_aurax_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t ena_bp                : 1;  /**< [ 16: 16](R/W) Enable asserting backpressure on BPID when maximum DROP level exceeded. See also
                                                                 FPA_AURA()_POOL_LEVELS[RED_ENA] and FPA_AURA()_CNT_LEVELS[RED_ENA]. */
        uint64_t reserved_10_15        : 6;
        uint64_t bpid                  : 10; /**< [  9:  0](R/W) Bpid to assert backpressure on. Values must be 0 to 511. */
#else /* Word 0 - Little Endian */
        uint64_t bpid                  : 10; /**< [  9:  0](R/W) Bpid to assert backpressure on. Values must be 0 to 511. */
        uint64_t reserved_10_15        : 6;
        uint64_t ena_bp                : 1;  /**< [ 16: 16](R/W) Enable asserting backpressure on BPID when maximum DROP level exceeded. See also
                                                                 FPA_AURA()_POOL_LEVELS[RED_ENA] and FPA_AURA()_CNT_LEVELS[RED_ENA]. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_aurax_cfg_s cn; */
};
typedef union bdk_pki_aurax_cfg bdk_pki_aurax_cfg_t;

static inline uint64_t BDK_PKI_AURAX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_AURAX_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=511))
        return 0x86c000900000ll + 8ll * ((a) & 0x1ff);
    __bdk_csr_fatal("PKI_AURAX_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_AURAX_CFG(a) bdk_pki_aurax_cfg_t
#define bustype_BDK_PKI_AURAX_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_AURAX_CFG(a) "PKI_AURAX_CFG"
#define device_bar_BDK_PKI_AURAX_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_AURAX_CFG(a) (a)
#define arguments_BDK_PKI_AURAX_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_bist_status0
 *
 * PKI BIST Results 0 Register
 * This register indicates BIST status.
 */
union bdk_pki_bist_status0
{
    uint64_t u;
    struct bdk_pki_bist_status0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_34_63        : 30;
        uint64_t bist                  : 34; /**< [ 33:  0](RO/H) BIST results. Hardware sets a bit in BIST for memory that fails BIST.
                                                                 Internal:
                                                                 This register collects status for PKI_PFE.
                                                                 \<33\> = PSTAT_MEM2.
                                                                 \<32\> = PSTAT_MEM1.
                                                                 \<31\> = PSTAT_MEM0.
                                                                 \<30\> = INB_ERRS.
                                                                 \<29\> = INB OCTS.
                                                                 \<28\> = INB PKTS.
                                                                 \<27\> = LD FIF.
                                                                 \<26\> = PBE STATE.
                                                                 \<25\> = WADR STATE.
                                                                 \<24\> = NXT PTAG.
                                                                 \<23\> = CUR PTAG.
                                                                 \<22\> = X2P FIF.
                                                                 \<21\> = DROP FIF.
                                                                 \<20\> = NXT BLK.
                                                                 \<19..16\> = KMEM.
                                                                 \<15..0\> = ASM BUFF. */
#else /* Word 0 - Little Endian */
        uint64_t bist                  : 34; /**< [ 33:  0](RO/H) BIST results. Hardware sets a bit in BIST for memory that fails BIST.
                                                                 Internal:
                                                                 This register collects status for PKI_PFE.
                                                                 \<33\> = PSTAT_MEM2.
                                                                 \<32\> = PSTAT_MEM1.
                                                                 \<31\> = PSTAT_MEM0.
                                                                 \<30\> = INB_ERRS.
                                                                 \<29\> = INB OCTS.
                                                                 \<28\> = INB PKTS.
                                                                 \<27\> = LD FIF.
                                                                 \<26\> = PBE STATE.
                                                                 \<25\> = WADR STATE.
                                                                 \<24\> = NXT PTAG.
                                                                 \<23\> = CUR PTAG.
                                                                 \<22\> = X2P FIF.
                                                                 \<21\> = DROP FIF.
                                                                 \<20\> = NXT BLK.
                                                                 \<19..16\> = KMEM.
                                                                 \<15..0\> = ASM BUFF. */
        uint64_t reserved_34_63        : 30;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_bist_status0_s cn; */
};
typedef union bdk_pki_bist_status0 bdk_pki_bist_status0_t;

#define BDK_PKI_BIST_STATUS0 BDK_PKI_BIST_STATUS0_FUNC()
static inline uint64_t BDK_PKI_BIST_STATUS0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_BIST_STATUS0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000080ll;
    __bdk_csr_fatal("PKI_BIST_STATUS0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_BIST_STATUS0 bdk_pki_bist_status0_t
#define bustype_BDK_PKI_BIST_STATUS0 BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_BIST_STATUS0 "PKI_BIST_STATUS0"
#define device_bar_BDK_PKI_BIST_STATUS0 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_BIST_STATUS0 0
#define arguments_BDK_PKI_BIST_STATUS0 -1,-1,-1,-1

/**
 * Register (NCB) pki_bist_status1
 *
 * PKI BIST Results 1 Register
 * This register indicates BIST status.
 */
union bdk_pki_bist_status1
{
    uint64_t u;
    struct bdk_pki_bist_status1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_29_63        : 35;
        uint64_t bist                  : 29; /**< [ 28:  0](RO/H) BIST results. Hardware sets a bit in BIST for memory that fails BIST.
                                                                 Internal:
                                                                 This
                                                                 register collects status for PKI_PBE.
                                                                 \<28\> = NCBWQE_MEM.
                                                                 \<27..26\> = NCB_MEM.
                                                                 \<25\> = DSTATS_MEM0.
                                                                 \<24\> = DSTATS_MEM1.
                                                                 \<23\> = DSTATS_MEM2.
                                                                 \<22\> = DSTATS_MEM3.
                                                                 \<21\> = DSTATS_MEM4.
                                                                 \<20\> = STATS_MEM0.
                                                                 \<19\> = STATS_MEM1.
                                                                 \<18\> = STATS_MEM2.
                                                                 \<17\> = STATS_MEM3.
                                                                 \<16\> = SWS.
                                                                 \<15\> = WQEOUT.
                                                                 \<14\> = DOA.
                                                                 \<13\> = BPID.
                                                                 \<12:10\> = Reserved.
                                                                 \<9\> = PLC.
                                                                 \<8\> = PKTWQ.
                                                                 \<7\> = Reserved.
                                                                 \<6\> = STRM.
                                                                 \<5\> = TAG.
                                                                 \<4\> = Reserved.
                                                                 \<3\> = CHAN.
                                                                 \<2\> = PBTAG.
                                                                 \<1\> = STYLEWQ.
                                                                 \<0\> = QPG. */
#else /* Word 0 - Little Endian */
        uint64_t bist                  : 29; /**< [ 28:  0](RO/H) BIST results. Hardware sets a bit in BIST for memory that fails BIST.
                                                                 Internal:
                                                                 This
                                                                 register collects status for PKI_PBE.
                                                                 \<28\> = NCBWQE_MEM.
                                                                 \<27..26\> = NCB_MEM.
                                                                 \<25\> = DSTATS_MEM0.
                                                                 \<24\> = DSTATS_MEM1.
                                                                 \<23\> = DSTATS_MEM2.
                                                                 \<22\> = DSTATS_MEM3.
                                                                 \<21\> = DSTATS_MEM4.
                                                                 \<20\> = STATS_MEM0.
                                                                 \<19\> = STATS_MEM1.
                                                                 \<18\> = STATS_MEM2.
                                                                 \<17\> = STATS_MEM3.
                                                                 \<16\> = SWS.
                                                                 \<15\> = WQEOUT.
                                                                 \<14\> = DOA.
                                                                 \<13\> = BPID.
                                                                 \<12:10\> = Reserved.
                                                                 \<9\> = PLC.
                                                                 \<8\> = PKTWQ.
                                                                 \<7\> = Reserved.
                                                                 \<6\> = STRM.
                                                                 \<5\> = TAG.
                                                                 \<4\> = Reserved.
                                                                 \<3\> = CHAN.
                                                                 \<2\> = PBTAG.
                                                                 \<1\> = STYLEWQ.
                                                                 \<0\> = QPG. */
        uint64_t reserved_29_63        : 35;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_bist_status1_s cn; */
};
typedef union bdk_pki_bist_status1 bdk_pki_bist_status1_t;

#define BDK_PKI_BIST_STATUS1 BDK_PKI_BIST_STATUS1_FUNC()
static inline uint64_t BDK_PKI_BIST_STATUS1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_BIST_STATUS1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000088ll;
    __bdk_csr_fatal("PKI_BIST_STATUS1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_BIST_STATUS1 bdk_pki_bist_status1_t
#define bustype_BDK_PKI_BIST_STATUS1 BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_BIST_STATUS1 "PKI_BIST_STATUS1"
#define device_bar_BDK_PKI_BIST_STATUS1 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_BIST_STATUS1 0
#define arguments_BDK_PKI_BIST_STATUS1 -1,-1,-1,-1

/**
 * Register (NCB) pki_bist_status2
 *
 * PKI BIST Results 2 Register
 * This register indicates BIST status.
 */
union bdk_pki_bist_status2
{
    uint64_t u;
    struct bdk_pki_bist_status2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_25_63        : 39;
        uint64_t bist                  : 25; /**< [ 24:  0](RO/H) BIST results. Hardware sets a bit in BIST for memory that fails BIST.
                                                                 Internal:
                                                                 This
                                                                 register collects status for PKI_PIX (verif/vkits/pki/pki_mem_info_table.sv).
                                                                 24     = IMEM.
                                                                 23..20 = Reserved.
                                                                 19     = IPEC1 / IPEs 10 .. 19 (RegFile + DMEM).
                                                                 18     = IPEC1 / IPEs  0 ..  9 (RegFile + DMEM).
                                                                 17     = IPEC0 / IPEs 10 .. 19 (RegFile + DMEM).
                                                                 16     = IPEC0 / IPEs  0 ..  9 (RegFile + DMEM).
                                                                 15..13 = Reserved.
                                                                 14..12 = IPEC SMEM.
                                                                 11..10 = Reserved.
                                                                 9..8   = IPEC PCAM ECC.
                                                                 7..6   = Reserved.
                                                                 5..4   = IPEC PCAM RES.
                                                                 3..2   = Reserved.
                                                                 1..0   = IPEC PCAM CAM. */
#else /* Word 0 - Little Endian */
        uint64_t bist                  : 25; /**< [ 24:  0](RO/H) BIST results. Hardware sets a bit in BIST for memory that fails BIST.
                                                                 Internal:
                                                                 This
                                                                 register collects status for PKI_PIX (verif/vkits/pki/pki_mem_info_table.sv).
                                                                 24     = IMEM.
                                                                 23..20 = Reserved.
                                                                 19     = IPEC1 / IPEs 10 .. 19 (RegFile + DMEM).
                                                                 18     = IPEC1 / IPEs  0 ..  9 (RegFile + DMEM).
                                                                 17     = IPEC0 / IPEs 10 .. 19 (RegFile + DMEM).
                                                                 16     = IPEC0 / IPEs  0 ..  9 (RegFile + DMEM).
                                                                 15..13 = Reserved.
                                                                 14..12 = IPEC SMEM.
                                                                 11..10 = Reserved.
                                                                 9..8   = IPEC PCAM ECC.
                                                                 7..6   = Reserved.
                                                                 5..4   = IPEC PCAM RES.
                                                                 3..2   = Reserved.
                                                                 1..0   = IPEC PCAM CAM. */
        uint64_t reserved_25_63        : 39;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_bist_status2_s cn; */
};
typedef union bdk_pki_bist_status2 bdk_pki_bist_status2_t;

#define BDK_PKI_BIST_STATUS2 BDK_PKI_BIST_STATUS2_FUNC()
static inline uint64_t BDK_PKI_BIST_STATUS2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_BIST_STATUS2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000090ll;
    __bdk_csr_fatal("PKI_BIST_STATUS2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_BIST_STATUS2 bdk_pki_bist_status2_t
#define bustype_BDK_PKI_BIST_STATUS2 BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_BIST_STATUS2 "PKI_BIST_STATUS2"
#define device_bar_BDK_PKI_BIST_STATUS2 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_BIST_STATUS2 0
#define arguments_BDK_PKI_BIST_STATUS2 -1,-1,-1,-1

/**
 * Register (NCB) pki_bp_test0
 *
 * INTERNAL: PKI Backpressure Test Register 0
 */
union bdk_pki_bp_test0
{
    uint64_t u;
    struct bdk_pki_bp_test0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Limit the NCBO FIFO, backpressure the sending NCB csrs requests to PFE.
                                                                 \<62\> = Limit the RD FIFO, backpressure sending packet data to PBE.
                                                                 \<61\> = Limit the LD FIFO , backpressure scheduling packet headers to PIX.
                                                                 \<60\> = Limit the X2P FIFO, ultimately backpressuring X2P bus. */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = BP_CFG3.
                                                                   \<21:20\> = BP_CFG2.
                                                                   \<19:18\> = BP_CFG1.
                                                                   \<17:16\> = BP_CFG0. */
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
                                                                   \<23:22\> = BP_CFG3.
                                                                   \<21:20\> = BP_CFG2.
                                                                   \<19:18\> = BP_CFG1.
                                                                   \<17:16\> = BP_CFG0. */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Limit the NCBO FIFO, backpressure the sending NCB csrs requests to PFE.
                                                                 \<62\> = Limit the RD FIFO, backpressure sending packet data to PBE.
                                                                 \<61\> = Limit the LD FIFO , backpressure scheduling packet headers to PIX.
                                                                 \<60\> = Limit the X2P FIFO, ultimately backpressuring X2P bus. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_bp_test0_s cn; */
};
typedef union bdk_pki_bp_test0 bdk_pki_bp_test0_t;

#define BDK_PKI_BP_TEST0 BDK_PKI_BP_TEST0_FUNC()
static inline uint64_t BDK_PKI_BP_TEST0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_BP_TEST0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000250ll;
    __bdk_csr_fatal("PKI_BP_TEST0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_BP_TEST0 bdk_pki_bp_test0_t
#define bustype_BDK_PKI_BP_TEST0 BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_BP_TEST0 "PKI_BP_TEST0"
#define device_bar_BDK_PKI_BP_TEST0 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_BP_TEST0 0
#define arguments_BDK_PKI_BP_TEST0 -1,-1,-1,-1

/**
 * Register (NCB) pki_bp_test1
 *
 * INTERNAL: PKI Backpressure Test Register 1
 */
union bdk_pki_bp_test1
{
    uint64_t u;
    struct bdk_pki_bp_test1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Unused.
                                                                 \<62\> = Limit data flow start in PLC.
                                                                 \<61\> = Limit return of pointers from FPC back to PCE.
                                                                 \<60\> = Limit unload flow start in PCE. */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = BP_CFG3.
                                                                   \<21:20\> = BP_CFG2.
                                                                   \<19:18\> = BP_CFG1.
                                                                   \<17:16\> = BP_CFG0. */
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
                                                                   \<23:22\> = BP_CFG3.
                                                                   \<21:20\> = BP_CFG2.
                                                                   \<19:18\> = BP_CFG1.
                                                                   \<17:16\> = BP_CFG0. */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Unused.
                                                                 \<62\> = Limit data flow start in PLC.
                                                                 \<61\> = Limit return of pointers from FPC back to PCE.
                                                                 \<60\> = Limit unload flow start in PCE. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_bp_test1_s cn; */
};
typedef union bdk_pki_bp_test1 bdk_pki_bp_test1_t;

#define BDK_PKI_BP_TEST1 BDK_PKI_BP_TEST1_FUNC()
static inline uint64_t BDK_PKI_BP_TEST1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_BP_TEST1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000260ll;
    __bdk_csr_fatal("PKI_BP_TEST1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_BP_TEST1 bdk_pki_bp_test1_t
#define bustype_BDK_PKI_BP_TEST1 BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_BP_TEST1 "PKI_BP_TEST1"
#define device_bar_BDK_PKI_BP_TEST1 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_BP_TEST1 0
#define arguments_BDK_PKI_BP_TEST1 -1,-1,-1,-1

/**
 * Register (NCB) pki_bp_test2
 *
 * INTERNAL: PKI Backpressure Test Register 2
 */
union bdk_pki_bp_test2
{
    uint64_t u;
    struct bdk_pki_bp_test2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Limit the CLS from unloading.
                                                                 \<62\> = Limit the CLS from executing.
                                                                 \<61\> = Limit the timer expiration.
                                                                 \<60\> = Limit the schedule from schedule PFE requests. */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = BP_CFG3.
                                                                   \<21:20\> = BP_CFG2.
                                                                   \<19:18\> = BP_CFG1.
                                                                   \<17:16\> = BP_CFG0. */
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
                                                                   \<23:22\> = BP_CFG3.
                                                                   \<21:20\> = BP_CFG2.
                                                                   \<19:18\> = BP_CFG1.
                                                                   \<17:16\> = BP_CFG0. */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Limit the CLS from unloading.
                                                                 \<62\> = Limit the CLS from executing.
                                                                 \<61\> = Limit the timer expiration.
                                                                 \<60\> = Limit the schedule from schedule PFE requests. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_bp_test2_s cn; */
};
typedef union bdk_pki_bp_test2 bdk_pki_bp_test2_t;

#define BDK_PKI_BP_TEST2 BDK_PKI_BP_TEST2_FUNC()
static inline uint64_t BDK_PKI_BP_TEST2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_BP_TEST2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000270ll;
    __bdk_csr_fatal("PKI_BP_TEST2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_BP_TEST2 bdk_pki_bp_test2_t
#define bustype_BDK_PKI_BP_TEST2 BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_BP_TEST2 "PKI_BP_TEST2"
#define device_bar_BDK_PKI_BP_TEST2 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_BP_TEST2 0
#define arguments_BDK_PKI_BP_TEST2 -1,-1,-1,-1

/**
 * Register (NCB) pki_bpid#_state
 *
 * PKI Bpid State Register
 * This register shows the current bpid state for diagnostics.
 */
union bdk_pki_bpidx_state
{
    uint64_t u;
    struct bdk_pki_bpidx_state_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t xoff                  : 1;  /**< [  0:  0](RO/H) The corresponding bpid is being backpressured. */
#else /* Word 0 - Little Endian */
        uint64_t xoff                  : 1;  /**< [  0:  0](RO/H) The corresponding bpid is being backpressured. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_bpidx_state_s cn; */
};
typedef union bdk_pki_bpidx_state bdk_pki_bpidx_state_t;

static inline uint64_t BDK_PKI_BPIDX_STATE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_BPIDX_STATE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=511))
        return 0x86c000b00000ll + 8ll * ((a) & 0x1ff);
    __bdk_csr_fatal("PKI_BPIDX_STATE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_BPIDX_STATE(a) bdk_pki_bpidx_state_t
#define bustype_BDK_PKI_BPIDX_STATE(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_BPIDX_STATE(a) "PKI_BPIDX_STATE"
#define device_bar_BDK_PKI_BPIDX_STATE(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_BPIDX_STATE(a) (a)
#define arguments_BDK_PKI_BPIDX_STATE(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_buf_ctl
 *
 * PKI Buffer Control Register
 */
union bdk_pki_buf_ctl
{
    uint64_t u;
    struct bdk_pki_buf_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t fpa_wait              : 1;  /**< [ 10: 10](R/W) Policy when FPA runs out of buffers:
                                                                 0 = Drop the remainder of the packet requesting the buffer, and set
                                                                 PKI_WQE_S[ERRLEV,OPCODE] to PKI_ERRLEV_E::RE,PKI_OPCODE_E::RE_MEMOUT.
                                                                 1 = Wait until buffers become available, only dropping packets if buffering ahead of PKI
                                                                 fills. This may lead to head-of-line blocking of packets on other Auras. */
        uint64_t fpa_cac_dis           : 1;  /**< [  9:  9](R/W) Reserved. */
        uint64_t reserved_6_8          : 3;
        uint64_t pkt_off               : 1;  /**< [  5:  5](R/W) Packet buffer off. When this bit is set to 1, the PKI does not buffer the received packet
                                                                 data; when it is clear to 0, the PKI works normally, buffering the received packet data. */
        uint64_t reserved_3_4          : 2;
        uint64_t pbp_en                : 1;  /**< [  2:  2](R/W) Bpid enable. When set, enables the sending of bpid level backpressure to the input
                                                                 interface.
                                                                 The application should not de-assert this bit after asserting it. The receivers of this
                                                                 bit may have been put into backpressure mode and can only be released by PKI informing
                                                                 them that the backpressure has been released.

                                                                 Internal:
                                                                 Must be set for PKI HW to assert any output backpressure wires. */
        uint64_t reserved_1            : 1;
        uint64_t pki_en                : 1;  /**< [  0:  0](R/W) PKI enable. When set to 1, enables the operation of the PKI. When clear to 0, the PKI
                                                                 asserts backpressure on all ports.

                                                                 Internal:
                                                                 Suppresses grants to X2P, not BPID backpressure. */
#else /* Word 0 - Little Endian */
        uint64_t pki_en                : 1;  /**< [  0:  0](R/W) PKI enable. When set to 1, enables the operation of the PKI. When clear to 0, the PKI
                                                                 asserts backpressure on all ports.

                                                                 Internal:
                                                                 Suppresses grants to X2P, not BPID backpressure. */
        uint64_t reserved_1            : 1;
        uint64_t pbp_en                : 1;  /**< [  2:  2](R/W) Bpid enable. When set, enables the sending of bpid level backpressure to the input
                                                                 interface.
                                                                 The application should not de-assert this bit after asserting it. The receivers of this
                                                                 bit may have been put into backpressure mode and can only be released by PKI informing
                                                                 them that the backpressure has been released.

                                                                 Internal:
                                                                 Must be set for PKI HW to assert any output backpressure wires. */
        uint64_t reserved_3_4          : 2;
        uint64_t pkt_off               : 1;  /**< [  5:  5](R/W) Packet buffer off. When this bit is set to 1, the PKI does not buffer the received packet
                                                                 data; when it is clear to 0, the PKI works normally, buffering the received packet data. */
        uint64_t reserved_6_8          : 3;
        uint64_t fpa_cac_dis           : 1;  /**< [  9:  9](R/W) Reserved. */
        uint64_t fpa_wait              : 1;  /**< [ 10: 10](R/W) Policy when FPA runs out of buffers:
                                                                 0 = Drop the remainder of the packet requesting the buffer, and set
                                                                 PKI_WQE_S[ERRLEV,OPCODE] to PKI_ERRLEV_E::RE,PKI_OPCODE_E::RE_MEMOUT.
                                                                 1 = Wait until buffers become available, only dropping packets if buffering ahead of PKI
                                                                 fills. This may lead to head-of-line blocking of packets on other Auras. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_buf_ctl_s cn; */
};
typedef union bdk_pki_buf_ctl bdk_pki_buf_ctl_t;

#define BDK_PKI_BUF_CTL BDK_PKI_BUF_CTL_FUNC()
static inline uint64_t BDK_PKI_BUF_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_BUF_CTL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000100ll;
    __bdk_csr_fatal("PKI_BUF_CTL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_BUF_CTL bdk_pki_buf_ctl_t
#define bustype_BDK_PKI_BUF_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_BUF_CTL "PKI_BUF_CTL"
#define device_bar_BDK_PKI_BUF_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_BUF_CTL 0
#define arguments_BDK_PKI_BUF_CTL -1,-1,-1,-1

/**
 * Register (NCB) pki_chan#_cfg
 *
 * PKI Channel Configuration Register
 * This register configures each channel.
 */
union bdk_pki_chanx_cfg
{
    uint64_t u;
    struct bdk_pki_chanx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t imp                   : 1;  /**< [ 16: 16](RO/H) Implemented. This register is sparse (only indexes with values in PKI_CHAN_E are
                                                                 implemented).
                                                                 0 = This index is read only.
                                                                 1 = This index is read-write.

                                                                 Write to a non-implemented channel is ignored. Reading a non-implemented channel
                                                                 returns all zero data. */
        uint64_t reserved_10_15        : 6;
        uint64_t bpid                  : 10; /**< [  9:  0](R/W) Bpid from which to receive backpressure. Value must be 0 to 511. */
#else /* Word 0 - Little Endian */
        uint64_t bpid                  : 10; /**< [  9:  0](R/W) Bpid from which to receive backpressure. Value must be 0 to 511. */
        uint64_t reserved_10_15        : 6;
        uint64_t imp                   : 1;  /**< [ 16: 16](RO/H) Implemented. This register is sparse (only indexes with values in PKI_CHAN_E are
                                                                 implemented).
                                                                 0 = This index is read only.
                                                                 1 = This index is read-write.

                                                                 Write to a non-implemented channel is ignored. Reading a non-implemented channel
                                                                 returns all zero data. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_chanx_cfg_s cn; */
};
typedef union bdk_pki_chanx_cfg bdk_pki_chanx_cfg_t;

static inline uint64_t BDK_PKI_CHANX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CHANX_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=4095))
        return 0x86c000a00000ll + 8ll * ((a) & 0xfff);
    __bdk_csr_fatal("PKI_CHANX_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CHANX_CFG(a) bdk_pki_chanx_cfg_t
#define bustype_BDK_PKI_CHANX_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CHANX_CFG(a) "PKI_CHANX_CFG"
#define device_bar_BDK_PKI_CHANX_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CHANX_CFG(a) (a)
#define arguments_BDK_PKI_CHANX_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_cl#_ecc_ctl
 *
 * PKI Cluster ECC/Parity Control Registers
 * This register configures ECC. All of PKI_CL()_ECC_CTL must be configured identically.
 */
union bdk_pki_clx_ecc_ctl
{
    uint64_t u;
    struct bdk_pki_clx_ecc_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pcam_en               : 1;  /**< [ 63: 63](R/W) PCAM ECC scrubber and checking enable. PCAM_EN must be clear when reading or
                                                                 writing the PKI_PCAM_RESULT registers. */
        uint64_t reserved_57_62        : 6;
        uint64_t spare                 : 1;  /**< [ 56: 56](R/W) Spare bit. */
        uint64_t reserved_24_55        : 32;
        uint64_t pcam1_flip            : 2;  /**< [ 23: 22](R/W) PCAM1 flip syndrome bits on write. */
        uint64_t pcam0_flip            : 2;  /**< [ 21: 20](R/W) PCAM  flip syndrome bits on write. */
        uint64_t smem_flip             : 2;  /**< [ 19: 18](R/W) SMEM flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the KMEM ram to
                                                                 test single-bit or double-bit error handling. */
        uint64_t dmem_flip             : 1;  /**< [ 17: 17](R/W) DMEM flip parity. */
        uint64_t rf_flip               : 1;  /**< [ 16: 16](R/W) RF flip parity. */
        uint64_t reserved_5_15         : 11;
        uint64_t pcam1_cdis            : 1;  /**< [  4:  4](R/W) PCAM1 ECC correction disable. */
        uint64_t pcam0_cdis            : 1;  /**< [  3:  3](R/W) PCAM0 ECC correction disable. */
        uint64_t smem_cdis             : 1;  /**< [  2:  2](R/W) SMEM ECC correction disable. */
        uint64_t dmem_cdis             : 1;  /**< [  1:  1](R/W) DMEM parity poisoning disable. */
        uint64_t rf_cdis               : 1;  /**< [  0:  0](R/W) RF RAM parity poisoning disable. */
#else /* Word 0 - Little Endian */
        uint64_t rf_cdis               : 1;  /**< [  0:  0](R/W) RF RAM parity poisoning disable. */
        uint64_t dmem_cdis             : 1;  /**< [  1:  1](R/W) DMEM parity poisoning disable. */
        uint64_t smem_cdis             : 1;  /**< [  2:  2](R/W) SMEM ECC correction disable. */
        uint64_t pcam0_cdis            : 1;  /**< [  3:  3](R/W) PCAM0 ECC correction disable. */
        uint64_t pcam1_cdis            : 1;  /**< [  4:  4](R/W) PCAM1 ECC correction disable. */
        uint64_t reserved_5_15         : 11;
        uint64_t rf_flip               : 1;  /**< [ 16: 16](R/W) RF flip parity. */
        uint64_t dmem_flip             : 1;  /**< [ 17: 17](R/W) DMEM flip parity. */
        uint64_t smem_flip             : 2;  /**< [ 19: 18](R/W) SMEM flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the KMEM ram to
                                                                 test single-bit or double-bit error handling. */
        uint64_t pcam0_flip            : 2;  /**< [ 21: 20](R/W) PCAM  flip syndrome bits on write. */
        uint64_t pcam1_flip            : 2;  /**< [ 23: 22](R/W) PCAM1 flip syndrome bits on write. */
        uint64_t reserved_24_55        : 32;
        uint64_t spare                 : 1;  /**< [ 56: 56](R/W) Spare bit. */
        uint64_t reserved_57_62        : 6;
        uint64_t pcam_en               : 1;  /**< [ 63: 63](R/W) PCAM ECC scrubber and checking enable. PCAM_EN must be clear when reading or
                                                                 writing the PKI_PCAM_RESULT registers. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_ecc_ctl_s cn; */
};
typedef union bdk_pki_clx_ecc_ctl bdk_pki_clx_ecc_ctl_t;

static inline uint64_t BDK_PKI_CLX_ECC_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_ECC_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1))
        return 0x86c00000c020ll + 0x10000ll * ((a) & 0x1);
    __bdk_csr_fatal("PKI_CLX_ECC_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_ECC_CTL(a) bdk_pki_clx_ecc_ctl_t
#define bustype_BDK_PKI_CLX_ECC_CTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_ECC_CTL(a) "PKI_CLX_ECC_CTL"
#define device_bar_BDK_PKI_CLX_ECC_CTL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_ECC_CTL(a) (a)
#define arguments_BDK_PKI_CLX_ECC_CTL(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_cl#_ecc_int
 *
 * PKI Cluster ECC/Parity Interrupt Registers
 */
union bdk_pki_clx_ecc_int
{
    uint64_t u;
    struct bdk_pki_clx_ecc_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t pcam1_dbe             : 1;  /**< [  7:  7](R/W1C/H) PCAM1 ECC double-bit error. */
        uint64_t pcam1_sbe             : 1;  /**< [  6:  6](R/W1C/H) PCAM1 ECC single-bit error. */
        uint64_t pcam0_dbe             : 1;  /**< [  5:  5](R/W1C/H) PCAM0 ECC double-bit error. */
        uint64_t pcam0_sbe             : 1;  /**< [  4:  4](R/W1C/H) PCAM0 ECC single-bit error. */
        uint64_t smem_dbe              : 1;  /**< [  3:  3](R/W1C/H) SMEM ECC double-bit error. If
                                                                 SMEM_DBE is thrown, software may scrub the error by reloading PKI_CL()_SMEM(). */
        uint64_t smem_sbe              : 1;  /**< [  2:  2](R/W1C/H) SMEM ECC single-bit error. If
                                                                 SMEM_SBE is thrown, software may scrub the error by reloading PKI_CL()_SMEM(). */
        uint64_t dmem_perr             : 1;  /**< [  1:  1](R/W1C/H) DMEM parity error. */
        uint64_t rf_perr               : 1;  /**< [  0:  0](R/W1C/H) RF RAM parity error. */
#else /* Word 0 - Little Endian */
        uint64_t rf_perr               : 1;  /**< [  0:  0](R/W1C/H) RF RAM parity error. */
        uint64_t dmem_perr             : 1;  /**< [  1:  1](R/W1C/H) DMEM parity error. */
        uint64_t smem_sbe              : 1;  /**< [  2:  2](R/W1C/H) SMEM ECC single-bit error. If
                                                                 SMEM_SBE is thrown, software may scrub the error by reloading PKI_CL()_SMEM(). */
        uint64_t smem_dbe              : 1;  /**< [  3:  3](R/W1C/H) SMEM ECC double-bit error. If
                                                                 SMEM_DBE is thrown, software may scrub the error by reloading PKI_CL()_SMEM(). */
        uint64_t pcam0_sbe             : 1;  /**< [  4:  4](R/W1C/H) PCAM0 ECC single-bit error. */
        uint64_t pcam0_dbe             : 1;  /**< [  5:  5](R/W1C/H) PCAM0 ECC double-bit error. */
        uint64_t pcam1_sbe             : 1;  /**< [  6:  6](R/W1C/H) PCAM1 ECC single-bit error. */
        uint64_t pcam1_dbe             : 1;  /**< [  7:  7](R/W1C/H) PCAM1 ECC double-bit error. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_ecc_int_s cn; */
};
typedef union bdk_pki_clx_ecc_int bdk_pki_clx_ecc_int_t;

static inline uint64_t BDK_PKI_CLX_ECC_INT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_ECC_INT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1))
        return 0x86c00000c200ll + 0x10000ll * ((a) & 0x1);
    __bdk_csr_fatal("PKI_CLX_ECC_INT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_ECC_INT(a) bdk_pki_clx_ecc_int_t
#define bustype_BDK_PKI_CLX_ECC_INT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_ECC_INT(a) "PKI_CLX_ECC_INT"
#define device_bar_BDK_PKI_CLX_ECC_INT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_ECC_INT(a) (a)
#define arguments_BDK_PKI_CLX_ECC_INT(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_cl#_ecc_int_ena_w1c
 *
 * PKI Cluster ECC/Parity Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_pki_clx_ecc_int_ena_w1c
{
    uint64_t u;
    struct bdk_pki_clx_ecc_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t pcam1_dbe             : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for PKI_CL(0..1)_ECC_INT[PCAM1_DBE]. */
        uint64_t pcam1_sbe             : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for PKI_CL(0..1)_ECC_INT[PCAM1_SBE]. */
        uint64_t pcam0_dbe             : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for PKI_CL(0..1)_ECC_INT[PCAM0_DBE]. */
        uint64_t pcam0_sbe             : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for PKI_CL(0..1)_ECC_INT[PCAM0_SBE]. */
        uint64_t smem_dbe              : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for PKI_CL(0..1)_ECC_INT[SMEM_DBE]. */
        uint64_t smem_sbe              : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for PKI_CL(0..1)_ECC_INT[SMEM_SBE]. */
        uint64_t dmem_perr             : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for PKI_CL(0..1)_ECC_INT[DMEM_PERR]. */
        uint64_t rf_perr               : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for PKI_CL(0..1)_ECC_INT[RF_PERR]. */
#else /* Word 0 - Little Endian */
        uint64_t rf_perr               : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for PKI_CL(0..1)_ECC_INT[RF_PERR]. */
        uint64_t dmem_perr             : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for PKI_CL(0..1)_ECC_INT[DMEM_PERR]. */
        uint64_t smem_sbe              : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for PKI_CL(0..1)_ECC_INT[SMEM_SBE]. */
        uint64_t smem_dbe              : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for PKI_CL(0..1)_ECC_INT[SMEM_DBE]. */
        uint64_t pcam0_sbe             : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for PKI_CL(0..1)_ECC_INT[PCAM0_SBE]. */
        uint64_t pcam0_dbe             : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for PKI_CL(0..1)_ECC_INT[PCAM0_DBE]. */
        uint64_t pcam1_sbe             : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for PKI_CL(0..1)_ECC_INT[PCAM1_SBE]. */
        uint64_t pcam1_dbe             : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for PKI_CL(0..1)_ECC_INT[PCAM1_DBE]. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_ecc_int_ena_w1c_s cn; */
};
typedef union bdk_pki_clx_ecc_int_ena_w1c bdk_pki_clx_ecc_int_ena_w1c_t;

static inline uint64_t BDK_PKI_CLX_ECC_INT_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_ECC_INT_ENA_W1C(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1))
        return 0x86c00000c220ll + 0x10000ll * ((a) & 0x1);
    __bdk_csr_fatal("PKI_CLX_ECC_INT_ENA_W1C", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_ECC_INT_ENA_W1C(a) bdk_pki_clx_ecc_int_ena_w1c_t
#define bustype_BDK_PKI_CLX_ECC_INT_ENA_W1C(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_ECC_INT_ENA_W1C(a) "PKI_CLX_ECC_INT_ENA_W1C"
#define device_bar_BDK_PKI_CLX_ECC_INT_ENA_W1C(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_ECC_INT_ENA_W1C(a) (a)
#define arguments_BDK_PKI_CLX_ECC_INT_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_cl#_ecc_int_ena_w1s
 *
 * PKI Cluster ECC/Parity Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_pki_clx_ecc_int_ena_w1s
{
    uint64_t u;
    struct bdk_pki_clx_ecc_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t pcam1_dbe             : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for PKI_CL(0..1)_ECC_INT[PCAM1_DBE]. */
        uint64_t pcam1_sbe             : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for PKI_CL(0..1)_ECC_INT[PCAM1_SBE]. */
        uint64_t pcam0_dbe             : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for PKI_CL(0..1)_ECC_INT[PCAM0_DBE]. */
        uint64_t pcam0_sbe             : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for PKI_CL(0..1)_ECC_INT[PCAM0_SBE]. */
        uint64_t smem_dbe              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for PKI_CL(0..1)_ECC_INT[SMEM_DBE]. */
        uint64_t smem_sbe              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for PKI_CL(0..1)_ECC_INT[SMEM_SBE]. */
        uint64_t dmem_perr             : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for PKI_CL(0..1)_ECC_INT[DMEM_PERR]. */
        uint64_t rf_perr               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for PKI_CL(0..1)_ECC_INT[RF_PERR]. */
#else /* Word 0 - Little Endian */
        uint64_t rf_perr               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for PKI_CL(0..1)_ECC_INT[RF_PERR]. */
        uint64_t dmem_perr             : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for PKI_CL(0..1)_ECC_INT[DMEM_PERR]. */
        uint64_t smem_sbe              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for PKI_CL(0..1)_ECC_INT[SMEM_SBE]. */
        uint64_t smem_dbe              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for PKI_CL(0..1)_ECC_INT[SMEM_DBE]. */
        uint64_t pcam0_sbe             : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for PKI_CL(0..1)_ECC_INT[PCAM0_SBE]. */
        uint64_t pcam0_dbe             : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for PKI_CL(0..1)_ECC_INT[PCAM0_DBE]. */
        uint64_t pcam1_sbe             : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for PKI_CL(0..1)_ECC_INT[PCAM1_SBE]. */
        uint64_t pcam1_dbe             : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for PKI_CL(0..1)_ECC_INT[PCAM1_DBE]. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_ecc_int_ena_w1s_s cn; */
};
typedef union bdk_pki_clx_ecc_int_ena_w1s bdk_pki_clx_ecc_int_ena_w1s_t;

static inline uint64_t BDK_PKI_CLX_ECC_INT_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_ECC_INT_ENA_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1))
        return 0x86c00000c230ll + 0x10000ll * ((a) & 0x1);
    __bdk_csr_fatal("PKI_CLX_ECC_INT_ENA_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_ECC_INT_ENA_W1S(a) bdk_pki_clx_ecc_int_ena_w1s_t
#define bustype_BDK_PKI_CLX_ECC_INT_ENA_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_ECC_INT_ENA_W1S(a) "PKI_CLX_ECC_INT_ENA_W1S"
#define device_bar_BDK_PKI_CLX_ECC_INT_ENA_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_ECC_INT_ENA_W1S(a) (a)
#define arguments_BDK_PKI_CLX_ECC_INT_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_cl#_ecc_int_w1s
 *
 * PKI Cluster ECC/Parity Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_pki_clx_ecc_int_w1s
{
    uint64_t u;
    struct bdk_pki_clx_ecc_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t pcam1_dbe             : 1;  /**< [  7:  7](R/W1S/H) Reads or sets PKI_CL(0..1)_ECC_INT[PCAM1_DBE]. */
        uint64_t pcam1_sbe             : 1;  /**< [  6:  6](R/W1S/H) Reads or sets PKI_CL(0..1)_ECC_INT[PCAM1_SBE]. */
        uint64_t pcam0_dbe             : 1;  /**< [  5:  5](R/W1S/H) Reads or sets PKI_CL(0..1)_ECC_INT[PCAM0_DBE]. */
        uint64_t pcam0_sbe             : 1;  /**< [  4:  4](R/W1S/H) Reads or sets PKI_CL(0..1)_ECC_INT[PCAM0_SBE]. */
        uint64_t smem_dbe              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets PKI_CL(0..1)_ECC_INT[SMEM_DBE]. */
        uint64_t smem_sbe              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets PKI_CL(0..1)_ECC_INT[SMEM_SBE]. */
        uint64_t dmem_perr             : 1;  /**< [  1:  1](R/W1S/H) Reads or sets PKI_CL(0..1)_ECC_INT[DMEM_PERR]. */
        uint64_t rf_perr               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets PKI_CL(0..1)_ECC_INT[RF_PERR]. */
#else /* Word 0 - Little Endian */
        uint64_t rf_perr               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets PKI_CL(0..1)_ECC_INT[RF_PERR]. */
        uint64_t dmem_perr             : 1;  /**< [  1:  1](R/W1S/H) Reads or sets PKI_CL(0..1)_ECC_INT[DMEM_PERR]. */
        uint64_t smem_sbe              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets PKI_CL(0..1)_ECC_INT[SMEM_SBE]. */
        uint64_t smem_dbe              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets PKI_CL(0..1)_ECC_INT[SMEM_DBE]. */
        uint64_t pcam0_sbe             : 1;  /**< [  4:  4](R/W1S/H) Reads or sets PKI_CL(0..1)_ECC_INT[PCAM0_SBE]. */
        uint64_t pcam0_dbe             : 1;  /**< [  5:  5](R/W1S/H) Reads or sets PKI_CL(0..1)_ECC_INT[PCAM0_DBE]. */
        uint64_t pcam1_sbe             : 1;  /**< [  6:  6](R/W1S/H) Reads or sets PKI_CL(0..1)_ECC_INT[PCAM1_SBE]. */
        uint64_t pcam1_dbe             : 1;  /**< [  7:  7](R/W1S/H) Reads or sets PKI_CL(0..1)_ECC_INT[PCAM1_DBE]. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_ecc_int_w1s_s cn; */
};
typedef union bdk_pki_clx_ecc_int_w1s bdk_pki_clx_ecc_int_w1s_t;

static inline uint64_t BDK_PKI_CLX_ECC_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_ECC_INT_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1))
        return 0x86c00000c210ll + 0x10000ll * ((a) & 0x1);
    __bdk_csr_fatal("PKI_CLX_ECC_INT_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_ECC_INT_W1S(a) bdk_pki_clx_ecc_int_w1s_t
#define bustype_BDK_PKI_CLX_ECC_INT_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_ECC_INT_W1S(a) "PKI_CLX_ECC_INT_W1S"
#define device_bar_BDK_PKI_CLX_ECC_INT_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_ECC_INT_W1S(a) (a)
#define arguments_BDK_PKI_CLX_ECC_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_cl#_int
 *
 * PKI Cluster Interrupt Registers
 */
union bdk_pki_clx_int
{
    uint64_t u;
    struct bdk_pki_clx_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t iptint                : 1;  /**< [  3:  3](R/W1C/H) PCAM parse engine debug interrupt.
                                                                 Internal:
                                                                 Caused by TRAP or INTR parse engine state. */
        uint64_t sched_conf            : 1;  /**< [  2:  2](R/W1C/H) PCAM/SMEM internal port conflict. Internal error, should not occur.
                                                                 Internal:
                                                                 Parse engine mis-scheduled PCAM or SMEM ops with overlapping accesses. */
        uint64_t pcam_conf             : 2;  /**< [  1:  0](R/W1C/H) PCAM() match hit multiple rows, indicating either a soft error in the PCAM or a
                                                                 programming error in PKI_CL()_PCAM()_MATCH() or related registers.
                                                                 Once a conflict is detected, the PCAM state
                                                                 is unpredictable and is required to be fully reconfigured before further valid processing
                                                                 can take place. */
#else /* Word 0 - Little Endian */
        uint64_t pcam_conf             : 2;  /**< [  1:  0](R/W1C/H) PCAM() match hit multiple rows, indicating either a soft error in the PCAM or a
                                                                 programming error in PKI_CL()_PCAM()_MATCH() or related registers.
                                                                 Once a conflict is detected, the PCAM state
                                                                 is unpredictable and is required to be fully reconfigured before further valid processing
                                                                 can take place. */
        uint64_t sched_conf            : 1;  /**< [  2:  2](R/W1C/H) PCAM/SMEM internal port conflict. Internal error, should not occur.
                                                                 Internal:
                                                                 Parse engine mis-scheduled PCAM or SMEM ops with overlapping accesses. */
        uint64_t iptint                : 1;  /**< [  3:  3](R/W1C/H) PCAM parse engine debug interrupt.
                                                                 Internal:
                                                                 Caused by TRAP or INTR parse engine state. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_int_s cn; */
};
typedef union bdk_pki_clx_int bdk_pki_clx_int_t;

static inline uint64_t BDK_PKI_CLX_INT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_INT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1))
        return 0x86c00000c100ll + 0x10000ll * ((a) & 0x1);
    __bdk_csr_fatal("PKI_CLX_INT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_INT(a) bdk_pki_clx_int_t
#define bustype_BDK_PKI_CLX_INT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_INT(a) "PKI_CLX_INT"
#define device_bar_BDK_PKI_CLX_INT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_INT(a) (a)
#define arguments_BDK_PKI_CLX_INT(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_cl#_int_ena_w1c
 *
 * PKI Cluster Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_pki_clx_int_ena_w1c
{
    uint64_t u;
    struct bdk_pki_clx_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t iptint                : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for PKI_CL(0..1)_INT[IPTINT].
                                                                 Internal:
                                                                 Caused by TRAP or INTR parse engine state. */
        uint64_t sched_conf            : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for PKI_CL(0..1)_INT[SCHED_CONF].
                                                                 Internal:
                                                                 Parse engine mis-scheduled PCAM or SMEM ops with overlapping accesses. */
        uint64_t pcam_conf             : 2;  /**< [  1:  0](R/W1C/H) Reads or clears enable for PKI_CL(0..1)_INT[PCAM_CONF]. */
#else /* Word 0 - Little Endian */
        uint64_t pcam_conf             : 2;  /**< [  1:  0](R/W1C/H) Reads or clears enable for PKI_CL(0..1)_INT[PCAM_CONF]. */
        uint64_t sched_conf            : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for PKI_CL(0..1)_INT[SCHED_CONF].
                                                                 Internal:
                                                                 Parse engine mis-scheduled PCAM or SMEM ops with overlapping accesses. */
        uint64_t iptint                : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for PKI_CL(0..1)_INT[IPTINT].
                                                                 Internal:
                                                                 Caused by TRAP or INTR parse engine state. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_int_ena_w1c_s cn; */
};
typedef union bdk_pki_clx_int_ena_w1c bdk_pki_clx_int_ena_w1c_t;

static inline uint64_t BDK_PKI_CLX_INT_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_INT_ENA_W1C(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1))
        return 0x86c00000c120ll + 0x10000ll * ((a) & 0x1);
    __bdk_csr_fatal("PKI_CLX_INT_ENA_W1C", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_INT_ENA_W1C(a) bdk_pki_clx_int_ena_w1c_t
#define bustype_BDK_PKI_CLX_INT_ENA_W1C(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_INT_ENA_W1C(a) "PKI_CLX_INT_ENA_W1C"
#define device_bar_BDK_PKI_CLX_INT_ENA_W1C(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_INT_ENA_W1C(a) (a)
#define arguments_BDK_PKI_CLX_INT_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_cl#_int_ena_w1s
 *
 * PKI Cluster Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_pki_clx_int_ena_w1s
{
    uint64_t u;
    struct bdk_pki_clx_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t iptint                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for PKI_CL(0..1)_INT[IPTINT].
                                                                 Internal:
                                                                 Caused by TRAP or INTR parse engine state. */
        uint64_t sched_conf            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for PKI_CL(0..1)_INT[SCHED_CONF].
                                                                 Internal:
                                                                 Parse engine mis-scheduled PCAM or SMEM ops with overlapping accesses. */
        uint64_t pcam_conf             : 2;  /**< [  1:  0](R/W1S/H) Reads or sets enable for PKI_CL(0..1)_INT[PCAM_CONF]. */
#else /* Word 0 - Little Endian */
        uint64_t pcam_conf             : 2;  /**< [  1:  0](R/W1S/H) Reads or sets enable for PKI_CL(0..1)_INT[PCAM_CONF]. */
        uint64_t sched_conf            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for PKI_CL(0..1)_INT[SCHED_CONF].
                                                                 Internal:
                                                                 Parse engine mis-scheduled PCAM or SMEM ops with overlapping accesses. */
        uint64_t iptint                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for PKI_CL(0..1)_INT[IPTINT].
                                                                 Internal:
                                                                 Caused by TRAP or INTR parse engine state. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_int_ena_w1s_s cn; */
};
typedef union bdk_pki_clx_int_ena_w1s bdk_pki_clx_int_ena_w1s_t;

static inline uint64_t BDK_PKI_CLX_INT_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_INT_ENA_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1))
        return 0x86c00000c130ll + 0x10000ll * ((a) & 0x1);
    __bdk_csr_fatal("PKI_CLX_INT_ENA_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_INT_ENA_W1S(a) bdk_pki_clx_int_ena_w1s_t
#define bustype_BDK_PKI_CLX_INT_ENA_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_INT_ENA_W1S(a) "PKI_CLX_INT_ENA_W1S"
#define device_bar_BDK_PKI_CLX_INT_ENA_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_INT_ENA_W1S(a) (a)
#define arguments_BDK_PKI_CLX_INT_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_cl#_int_w1s
 *
 * PKI Cluster Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_pki_clx_int_w1s
{
    uint64_t u;
    struct bdk_pki_clx_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t iptint                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets PKI_CL(0..1)_INT[IPTINT].
                                                                 Internal:
                                                                 Caused by TRAP or INTR parse engine state. */
        uint64_t sched_conf            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets PKI_CL(0..1)_INT[SCHED_CONF].
                                                                 Internal:
                                                                 Parse engine mis-scheduled PCAM or SMEM ops with overlapping accesses. */
        uint64_t pcam_conf             : 2;  /**< [  1:  0](R/W1S/H) Reads or sets PKI_CL(0..1)_INT[PCAM_CONF]. */
#else /* Word 0 - Little Endian */
        uint64_t pcam_conf             : 2;  /**< [  1:  0](R/W1S/H) Reads or sets PKI_CL(0..1)_INT[PCAM_CONF]. */
        uint64_t sched_conf            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets PKI_CL(0..1)_INT[SCHED_CONF].
                                                                 Internal:
                                                                 Parse engine mis-scheduled PCAM or SMEM ops with overlapping accesses. */
        uint64_t iptint                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets PKI_CL(0..1)_INT[IPTINT].
                                                                 Internal:
                                                                 Caused by TRAP or INTR parse engine state. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_int_w1s_s cn; */
};
typedef union bdk_pki_clx_int_w1s bdk_pki_clx_int_w1s_t;

static inline uint64_t BDK_PKI_CLX_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_INT_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1))
        return 0x86c00000c110ll + 0x10000ll * ((a) & 0x1);
    __bdk_csr_fatal("PKI_CLX_INT_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_INT_W1S(a) bdk_pki_clx_int_w1s_t
#define bustype_BDK_PKI_CLX_INT_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_INT_W1S(a) "PKI_CLX_INT_W1S"
#define device_bar_BDK_PKI_CLX_INT_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_INT_W1S(a) (a)
#define arguments_BDK_PKI_CLX_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_cl#_pcam#_action#
 *
 * PKI PCAM Entry Action Registers
 * This register configures the result side of the PCAM. PKI hardware is opaque as to the use
 * of the 32 bits of CAM result.
 *
 * For each legal j and k, PKI_CL(i)_PCAM(j)_ACTION(k) must be configured identically for i=0..1.
 *
 * With the current parse engine code:
 *
 * Action performed based on PCAM lookup using the PKI_CL()_PCAM()_TERM() and
 * PKI_CL()_PCAM()_MATCH() registers.
 *
 * If lookup data matches no PCAM entries, then no action takes place. No matches indicates
 * normal parsing will continue.
 *
 * If data matches multiple PCAM entries, PKI_WQE_S[ERRLEV,OPCODE] of the processed packet may
 * be set to PKI_ERRLEV_E::RE,PKI_OPCODE_E::RE_PKIPCAM and the PKI_CL()_INT[PCAM_CONF] error
 * interrupt is signaled.  Once a conflict is detected, the PCAM state is unpredictable and is
 * required to be fully reconfigured before further valid processing can take place.
 */
union bdk_pki_clx_pcamx_actionx
{
    uint64_t u;
    struct bdk_pki_clx_pcamx_actionx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t rsvdrw31              : 1;  /**< [ 31: 31](R/W) Reserved. Must be zero. */
        uint64_t pmc                   : 7;  /**< [ 30: 24](R/W) Parse mode change. Where to resume parsing after applying the scan offset (if any) as bit
                                                                 mask of which parse engine steps to no longer process:

                                                                 _ \<0\> = LA (L2).
                                                                 _ \<1\> = LB (Custom).
                                                                 _ \<2\> = LC (L3).
                                                                 _ \<3\> = LD (Virt).
                                                                 _ \<4\> = LE (IL3).
                                                                 _ \<5\> = LF (L4).
                                                                 _ \<6\> = LG (Custom/Application-specific relative to C, D, E, or F).

                                                                 Typically PMC is 0x0 to indicate no parse mode change.  Must be zero for invalid
                                                                 entries, or for TERMs that do not allow a parse mode change as specified in the
                                                                 PMC column of the PKI_PCAM_TERM_E table.

                                                                 Typical values for PMC\<5:0\> are:
                                                                   0x0 = no change in parsing.
                                                                   0x1 = Skip further LA parsing; start LB parsing.
                                                                   0x3 = Skip further LA/LB parsing; start LC parsing.
                                                                   0x7 = Skip further LA-LC parsing; start LD parsing.
                                                                   0x38 = Skip LD, LE, LF parsing.
                                                                   0x3F = Skip all parsing; no further packet inspection.

                                                                 The typical use of PMC\<5:0\> being nonzero is for Ethertypes or custom headers
                                                                 to indicate non-IP follows that Ethertype/custom header. This corresponds to use
                                                                 only with PKI_PCAM_TERM_E::ETHTYPE0..3, and PKI_PCAM_TERM_E::L2_CUSTOM.

                                                                 Independently PMC\<6\> may be set to disable LG (LG_CUSTOM) parsing. */
        uint64_t style_add             : 8;  /**< [ 23: 16](R/W) Resulting interim style adder. If this CAM entry matches, the value to add to the current
                                                                 style (may wrap around through 256). Must be zero for invalid entries. */
        uint64_t pf                    : 3;  /**< [ 15: 13](R/W) Parse flag to set. Specifies the parse flag to set when entry matches, see PCAM actions
                                                                 may also specify setting one of four user flags in the generated work queue entry,
                                                                 PKI_WQE_S[PF1] through PKI_WQE_S[PF4]. These flags are not used by hardware; they are
                                                                 intended to
                                                                 indicate to software that exceptional handling may be required, such as the presence of an
                                                                 encrypted packet:

                                                                 _ 0x0 = no change.
                                                                 _ 0x1 = Set PKI_WQE_S[PF1].
                                                                 _ 0x2 = Set PKI_WQE_S[PF2].
                                                                 _ 0x3 = Set PKI_WQE_S[PF3].
                                                                 _ 0x4 = Set PKI_WQE_S[PF4].
                                                                 _ else = reserved.

                                                                 Must be zero for invalid entries. */
        uint64_t setty                 : 5;  /**< [ 12:  8](R/W) Set pointer type. If nonzero, indicates the layer type to be set as described under
                                                                 PKI_PCAM_TERM_E. Values are enumerated by PKI_LTYPE_E. Must be zero for invalid entries.
                                                                 The PKI_PCAM_TERM_E table enumerates legal/common SETTY values. */
        uint64_t advance               : 8;  /**< [  7:  0](R/W) Relative number of bytes to advance scan pointer when entry matches.
                                                                 Must be even. Must be zero for invalid entries and for TERMs that do not allow
                                                                 an advance as specified in the PKI_PCAM_TERM_E table. */
#else /* Word 0 - Little Endian */
        uint64_t advance               : 8;  /**< [  7:  0](R/W) Relative number of bytes to advance scan pointer when entry matches.
                                                                 Must be even. Must be zero for invalid entries and for TERMs that do not allow
                                                                 an advance as specified in the PKI_PCAM_TERM_E table. */
        uint64_t setty                 : 5;  /**< [ 12:  8](R/W) Set pointer type. If nonzero, indicates the layer type to be set as described under
                                                                 PKI_PCAM_TERM_E. Values are enumerated by PKI_LTYPE_E. Must be zero for invalid entries.
                                                                 The PKI_PCAM_TERM_E table enumerates legal/common SETTY values. */
        uint64_t pf                    : 3;  /**< [ 15: 13](R/W) Parse flag to set. Specifies the parse flag to set when entry matches, see PCAM actions
                                                                 may also specify setting one of four user flags in the generated work queue entry,
                                                                 PKI_WQE_S[PF1] through PKI_WQE_S[PF4]. These flags are not used by hardware; they are
                                                                 intended to
                                                                 indicate to software that exceptional handling may be required, such as the presence of an
                                                                 encrypted packet:

                                                                 _ 0x0 = no change.
                                                                 _ 0x1 = Set PKI_WQE_S[PF1].
                                                                 _ 0x2 = Set PKI_WQE_S[PF2].
                                                                 _ 0x3 = Set PKI_WQE_S[PF3].
                                                                 _ 0x4 = Set PKI_WQE_S[PF4].
                                                                 _ else = reserved.

                                                                 Must be zero for invalid entries. */
        uint64_t style_add             : 8;  /**< [ 23: 16](R/W) Resulting interim style adder. If this CAM entry matches, the value to add to the current
                                                                 style (may wrap around through 256). Must be zero for invalid entries. */
        uint64_t pmc                   : 7;  /**< [ 30: 24](R/W) Parse mode change. Where to resume parsing after applying the scan offset (if any) as bit
                                                                 mask of which parse engine steps to no longer process:

                                                                 _ \<0\> = LA (L2).
                                                                 _ \<1\> = LB (Custom).
                                                                 _ \<2\> = LC (L3).
                                                                 _ \<3\> = LD (Virt).
                                                                 _ \<4\> = LE (IL3).
                                                                 _ \<5\> = LF (L4).
                                                                 _ \<6\> = LG (Custom/Application-specific relative to C, D, E, or F).

                                                                 Typically PMC is 0x0 to indicate no parse mode change.  Must be zero for invalid
                                                                 entries, or for TERMs that do not allow a parse mode change as specified in the
                                                                 PMC column of the PKI_PCAM_TERM_E table.

                                                                 Typical values for PMC\<5:0\> are:
                                                                   0x0 = no change in parsing.
                                                                   0x1 = Skip further LA parsing; start LB parsing.
                                                                   0x3 = Skip further LA/LB parsing; start LC parsing.
                                                                   0x7 = Skip further LA-LC parsing; start LD parsing.
                                                                   0x38 = Skip LD, LE, LF parsing.
                                                                   0x3F = Skip all parsing; no further packet inspection.

                                                                 The typical use of PMC\<5:0\> being nonzero is for Ethertypes or custom headers
                                                                 to indicate non-IP follows that Ethertype/custom header. This corresponds to use
                                                                 only with PKI_PCAM_TERM_E::ETHTYPE0..3, and PKI_PCAM_TERM_E::L2_CUSTOM.

                                                                 Independently PMC\<6\> may be set to disable LG (LG_CUSTOM) parsing. */
        uint64_t rsvdrw31              : 1;  /**< [ 31: 31](R/W) Reserved. Must be zero. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_pcamx_actionx_s cn; */
};
typedef union bdk_pki_clx_pcamx_actionx bdk_pki_clx_pcamx_actionx_t;

static inline uint64_t BDK_PKI_CLX_PCAMX_ACTIONX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_PCAMX_ACTIONX(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=1) && (b<=1) && (c<=191)))
        return 0x86c000708000ll + 0x10000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1) + 8ll * ((c) & 0xff);
    __bdk_csr_fatal("PKI_CLX_PCAMX_ACTIONX", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_PCAMX_ACTIONX(a,b,c) bdk_pki_clx_pcamx_actionx_t
#define bustype_BDK_PKI_CLX_PCAMX_ACTIONX(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_PCAMX_ACTIONX(a,b,c) "PKI_CLX_PCAMX_ACTIONX"
#define device_bar_BDK_PKI_CLX_PCAMX_ACTIONX(a,b,c) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_PCAMX_ACTIONX(a,b,c) (a)
#define arguments_BDK_PKI_CLX_PCAMX_ACTIONX(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB) pki_cl#_pcam#_match#
 *
 * PKI PCAM Entry Data Match Registers
 * This register configures the match side of the PCAM. PKI hardware is opaque as to the use
 * of the 32 bits of CAM data.
 *
 * For each legal j and k, PKI_CL(i)_PCAM(j)_MATCH(k) must be configured identically for i=0..1.
 */
union bdk_pki_clx_pcamx_matchx
{
    uint64_t u;
    struct bdk_pki_clx_pcamx_matchx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data1                 : 32; /**< [ 63: 32](R/W) See [DATA0]. */
        uint64_t data0                 : 32; /**< [ 31:  0](R/W) The packet data to compare against. Bits may be ignored in comparison based on [DATA0] and
                                                                 [DATA1]. If the entry matches, PKI_CL()_PCAM()_ACTION() will determine the
                                                                 action to be taken. See PKI_PCAM_TERM_E for comparison bit definitions.
                                                                 The field value is ternary, where each bit matches as follows:

                                                                 _ [DATA1]\<n\>=0, [DATA0]\<n\>=0: Always match; data\<n\> don't care.
                                                                 _ [DATA1]\<n\>=0, [DATA0]\<n\>=1: Match when data\<n\> == 0.
                                                                 _ [DATA1]\<n\>=1, [DATA0]\<n\>=0: Match when data\<n\> == 1.
                                                                 _ [DATA1]\<n\>=1, [DATA0]\<n\>=1: Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t data0                 : 32; /**< [ 31:  0](R/W) The packet data to compare against. Bits may be ignored in comparison based on [DATA0] and
                                                                 [DATA1]. If the entry matches, PKI_CL()_PCAM()_ACTION() will determine the
                                                                 action to be taken. See PKI_PCAM_TERM_E for comparison bit definitions.
                                                                 The field value is ternary, where each bit matches as follows:

                                                                 _ [DATA1]\<n\>=0, [DATA0]\<n\>=0: Always match; data\<n\> don't care.
                                                                 _ [DATA1]\<n\>=0, [DATA0]\<n\>=1: Match when data\<n\> == 0.
                                                                 _ [DATA1]\<n\>=1, [DATA0]\<n\>=0: Match when data\<n\> == 1.
                                                                 _ [DATA1]\<n\>=1, [DATA0]\<n\>=1: Reserved. */
        uint64_t data1                 : 32; /**< [ 63: 32](R/W) See [DATA0]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_pcamx_matchx_s cn; */
};
typedef union bdk_pki_clx_pcamx_matchx bdk_pki_clx_pcamx_matchx_t;

static inline uint64_t BDK_PKI_CLX_PCAMX_MATCHX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_PCAMX_MATCHX(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=1) && (b<=1) && (c<=191)))
        return 0x86c000704000ll + 0x10000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1) + 8ll * ((c) & 0xff);
    __bdk_csr_fatal("PKI_CLX_PCAMX_MATCHX", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_PCAMX_MATCHX(a,b,c) bdk_pki_clx_pcamx_matchx_t
#define bustype_BDK_PKI_CLX_PCAMX_MATCHX(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_PCAMX_MATCHX(a,b,c) "PKI_CLX_PCAMX_MATCHX"
#define device_bar_BDK_PKI_CLX_PCAMX_MATCHX(a,b,c) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_PCAMX_MATCHX(a,b,c) (a)
#define arguments_BDK_PKI_CLX_PCAMX_MATCHX(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB) pki_cl#_pcam#_term#
 *
 * PKI PCAM Entry Term Match Registers
 * This register configures the match side of the PCAM. PKI hardware is opaque as to the use
 * of the 16 bits of CAM data; the split between TERM and STYLE is defined by the
 * parse engine.
 *
 * For each legal j and k, PKI_CL(i)_PCAM(j)_TERM(k) must be configured identically for i=0..1.
 */
union bdk_pki_clx_pcamx_termx
{
    uint64_t u;
    struct bdk_pki_clx_pcamx_termx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t valid                 : 1;  /**< [ 63: 63](R/W) Valid. */
        uint64_t reserved_48_62        : 15;
        uint64_t term1                 : 8;  /**< [ 47: 40](R/W) See [TERM0]. */
        uint64_t style1                : 8;  /**< [ 39: 32](R/W) See [STYLE0]. */
        uint64_t reserved_16_31        : 16;
        uint64_t term0                 : 8;  /**< [ 15:  8](R/W) Comparison type. Enumerated by PKI_PCAM_TERM_E. The field value is ternary, where each
                                                                 bit matches as follows:

                                                                 _ [TERM1]\<n\>=0, [TERM0]\<n\>=0: Always match; data\<n\> don't care.
                                                                 _ [TERM1]\<n\>=0, [TERM0]\<n\>=1: Match when data\<n\> == 0.
                                                                 _ [TERM1]\<n\>=1, [TERM0]\<n\>=0: Match when data\<n\> == 1.
                                                                 _ [TERM1]\<n\>=1, [TERM0]\<n\>=1: Reserved. */
        uint64_t style0                : 8;  /**< [  7:  0](R/W) Previous interim style. The style that must have been calculated by the port
                                                                 PKI_CL()_PKIND()_STYLE[STYLE] or as modified by previous CAM hits'
                                                                 PKI_CL()_PCAM()_ACTION()[STYLE_ADD]. This is used to form AND style matches.

                                                                 The field value is ternary, where each bit matches as follows:

                                                                 _ [STYLE1]\<n\>=0, [STYLE0]\<n\>=0: Always match; data\<n\> don't care.
                                                                 _ [STYLE1]\<n\>=0, [STYLE0]\<n\>=1: Match when data\<n\> == 0.
                                                                 _ [STYLE1]\<n\>=1, [STYLE0]\<n\>=0: Match when data\<n\> == 1.
                                                                 _ [STYLE1]\<n\>=1, [STYLE0]\<n\>=1: Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t style0                : 8;  /**< [  7:  0](R/W) Previous interim style. The style that must have been calculated by the port
                                                                 PKI_CL()_PKIND()_STYLE[STYLE] or as modified by previous CAM hits'
                                                                 PKI_CL()_PCAM()_ACTION()[STYLE_ADD]. This is used to form AND style matches.

                                                                 The field value is ternary, where each bit matches as follows:

                                                                 _ [STYLE1]\<n\>=0, [STYLE0]\<n\>=0: Always match; data\<n\> don't care.
                                                                 _ [STYLE1]\<n\>=0, [STYLE0]\<n\>=1: Match when data\<n\> == 0.
                                                                 _ [STYLE1]\<n\>=1, [STYLE0]\<n\>=0: Match when data\<n\> == 1.
                                                                 _ [STYLE1]\<n\>=1, [STYLE0]\<n\>=1: Reserved. */
        uint64_t term0                 : 8;  /**< [ 15:  8](R/W) Comparison type. Enumerated by PKI_PCAM_TERM_E. The field value is ternary, where each
                                                                 bit matches as follows:

                                                                 _ [TERM1]\<n\>=0, [TERM0]\<n\>=0: Always match; data\<n\> don't care.
                                                                 _ [TERM1]\<n\>=0, [TERM0]\<n\>=1: Match when data\<n\> == 0.
                                                                 _ [TERM1]\<n\>=1, [TERM0]\<n\>=0: Match when data\<n\> == 1.
                                                                 _ [TERM1]\<n\>=1, [TERM0]\<n\>=1: Reserved. */
        uint64_t reserved_16_31        : 16;
        uint64_t style1                : 8;  /**< [ 39: 32](R/W) See [STYLE0]. */
        uint64_t term1                 : 8;  /**< [ 47: 40](R/W) See [TERM0]. */
        uint64_t reserved_48_62        : 15;
        uint64_t valid                 : 1;  /**< [ 63: 63](R/W) Valid. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_pcamx_termx_s cn; */
};
typedef union bdk_pki_clx_pcamx_termx bdk_pki_clx_pcamx_termx_t;

static inline uint64_t BDK_PKI_CLX_PCAMX_TERMX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_PCAMX_TERMX(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=1) && (b<=1) && (c<=191)))
        return 0x86c000700000ll + 0x10000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1) + 8ll * ((c) & 0xff);
    __bdk_csr_fatal("PKI_CLX_PCAMX_TERMX", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_PCAMX_TERMX(a,b,c) bdk_pki_clx_pcamx_termx_t
#define bustype_BDK_PKI_CLX_PCAMX_TERMX(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_PCAMX_TERMX(a,b,c) "PKI_CLX_PCAMX_TERMX"
#define device_bar_BDK_PKI_CLX_PCAMX_TERMX(a,b,c) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_PCAMX_TERMX(a,b,c) (a)
#define arguments_BDK_PKI_CLX_PCAMX_TERMX(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB) pki_cl#_pkind#_cfg
 *
 * PKI Per-Pkind Configuration Registers
 * This register is inside PKI_CL()_PKIND()_KMEM(). These CSRs are used only by
 * the PKI parse engine.
 *
 * For each legal j, PKI_CL(i)_PKIND(j)_CFG must be configured identically for i=0..1.
 *
 * Internal:
 * The value of these CSRs do not directly influence PKI HW. But PKI HW supplies them to the
 * parse engine code for parsing/sequencing.
 */
union bdk_pki_clx_pkindx_cfg
{
    uint64_t u;
    struct bdk_pki_clx_pkindx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t rsvdrw15              : 5;  /**< [ 15: 11](R/W) Reserved. */
        uint64_t lg_custom_layer       : 3;  /**< [ 10:  8](R/W) Layer G custom match enable.
                                                                 0x0 = Disable custom LG header extraction
                                                                 0x1 = Enable custom LG header extraction after layer C.
                                                                 0x2 = Enable custom LG header extraction after layer D.
                                                                 0x3 = Enable custom LG header extraction after layer E.
                                                                 0x4 = Enable custom LG header extraction after layer F.
                                                                 0x5-0x7 = Reserved.

                                                                 Internal:
                                                                 Nonzero implemented only in software's parse engine code.

                                                                 [LG_CUSTOM_LAYER] must be clear if PKI_GBL_PEN[CLG_PEN] is clear. */
        uint64_t fcs_pres              : 1;  /**< [  7:  7](R/W) FCS present.
                                                                 0 = FCS not present. FCS may not be checked nor stripped.
                                                                 1 = FCS present; the last four bytes of the packet are part of the FCS and may not be
                                                                 considered part of a IP, TCP or other header for length error checks.

                                                                 When either PKI_CL()_STYLE()_CFG[FCS_CHK or FCS_STRIP] are set, the
                                                                 corresponding [FCS_PRES] must be set. */
        uint64_t mpls_en               : 1;  /**< [  6:  6](R/W) Enable MPLS parsing.
                                                                 0 = Any MPLS labels are ignored, but may be handled by custom Ethertype PCAM matchers.
                                                                 1 = MPLS label stacks are parsed and skipped over.

                                                                 Internal:
                                                                 [MPLS_EN] must be clear when PKI_GBL_PEN[MPLS_PEN] is clear. */
        uint64_t inst_hdr              : 1;  /**< [  5:  5](R/W) INST header. When set, a PKI_INST_HDR_S is present PKI_CL()_PKIND()_SKIP[INST_SKIP]
                                                                 bytes into the packet received by PKI. */
        uint64_t lg_custom             : 1;  /**< [  4:  4](R/W) Enable parsing LG_CUSTOM layers. */
        uint64_t fulc_en               : 1;  /**< [  3:  3](R/W) Enable Fulcrum tag parsing.

                                                                 0 = Any Fulcrum header is ignored.
                                                                 1 = Fulcrum header is parsed.

                                                                 [FULC_EN] must be clear when any of [HG_EN,HG2_EN,DSA_EN] are set.

                                                                 Internal:
                                                                 [FULC_EN] must be clear when PKI_GBL_PEN[FULC_PEN] is clear. */
        uint64_t dsa_en                : 1;  /**< [  2:  2](R/W) Enable DSA parsing.

                                                                 0 = Any DSA header is ignored.
                                                                 1 = DSA is parsed.

                                                                 [DSA_EN] must be clear when any of [HG_EN,HG2_EN,FULC_EN] are set.

                                                                 Internal:
                                                                 [DSA_EN] must be clear when PKI_GBL_PEN[DSA_PEN] is clear. */
        uint64_t hg2_en                : 1;  /**< [  1:  1](R/W) Enable HiGig 2 parsing.

                                                                 0 = Any HiGig2 header is ignored.
                                                                 1 = HiGig2 is parsed.

                                                                 [HG2_EN] must be clear when any of [HG_EN,FULC_EN,DSA_EN] is set.

                                                                 Internal:
                                                                 [HG2_EN] must be clear when PKI_GBL_PEN[HG_PEN] is clear. */
        uint64_t hg_en                 : 1;  /**< [  0:  0](R/W) Enable HiGig parsing.

                                                                 0 = Any HiGig header is ignored.
                                                                 1 = HiGig is parsed.

                                                                 [HG_EN] must be clear when any of [HG2_EN,FULC_EN,DSA_EN] is set.

                                                                 Internal:
                                                                 [HG_EN] must be clear when PKI_GBL_PEN[HG_PEN] is clear. */
#else /* Word 0 - Little Endian */
        uint64_t hg_en                 : 1;  /**< [  0:  0](R/W) Enable HiGig parsing.

                                                                 0 = Any HiGig header is ignored.
                                                                 1 = HiGig is parsed.

                                                                 [HG_EN] must be clear when any of [HG2_EN,FULC_EN,DSA_EN] is set.

                                                                 Internal:
                                                                 [HG_EN] must be clear when PKI_GBL_PEN[HG_PEN] is clear. */
        uint64_t hg2_en                : 1;  /**< [  1:  1](R/W) Enable HiGig 2 parsing.

                                                                 0 = Any HiGig2 header is ignored.
                                                                 1 = HiGig2 is parsed.

                                                                 [HG2_EN] must be clear when any of [HG_EN,FULC_EN,DSA_EN] is set.

                                                                 Internal:
                                                                 [HG2_EN] must be clear when PKI_GBL_PEN[HG_PEN] is clear. */
        uint64_t dsa_en                : 1;  /**< [  2:  2](R/W) Enable DSA parsing.

                                                                 0 = Any DSA header is ignored.
                                                                 1 = DSA is parsed.

                                                                 [DSA_EN] must be clear when any of [HG_EN,HG2_EN,FULC_EN] are set.

                                                                 Internal:
                                                                 [DSA_EN] must be clear when PKI_GBL_PEN[DSA_PEN] is clear. */
        uint64_t fulc_en               : 1;  /**< [  3:  3](R/W) Enable Fulcrum tag parsing.

                                                                 0 = Any Fulcrum header is ignored.
                                                                 1 = Fulcrum header is parsed.

                                                                 [FULC_EN] must be clear when any of [HG_EN,HG2_EN,DSA_EN] are set.

                                                                 Internal:
                                                                 [FULC_EN] must be clear when PKI_GBL_PEN[FULC_PEN] is clear. */
        uint64_t lg_custom             : 1;  /**< [  4:  4](R/W) Enable parsing LG_CUSTOM layers. */
        uint64_t inst_hdr              : 1;  /**< [  5:  5](R/W) INST header. When set, a PKI_INST_HDR_S is present PKI_CL()_PKIND()_SKIP[INST_SKIP]
                                                                 bytes into the packet received by PKI. */
        uint64_t mpls_en               : 1;  /**< [  6:  6](R/W) Enable MPLS parsing.
                                                                 0 = Any MPLS labels are ignored, but may be handled by custom Ethertype PCAM matchers.
                                                                 1 = MPLS label stacks are parsed and skipped over.

                                                                 Internal:
                                                                 [MPLS_EN] must be clear when PKI_GBL_PEN[MPLS_PEN] is clear. */
        uint64_t fcs_pres              : 1;  /**< [  7:  7](R/W) FCS present.
                                                                 0 = FCS not present. FCS may not be checked nor stripped.
                                                                 1 = FCS present; the last four bytes of the packet are part of the FCS and may not be
                                                                 considered part of a IP, TCP or other header for length error checks.

                                                                 When either PKI_CL()_STYLE()_CFG[FCS_CHK or FCS_STRIP] are set, the
                                                                 corresponding [FCS_PRES] must be set. */
        uint64_t lg_custom_layer       : 3;  /**< [ 10:  8](R/W) Layer G custom match enable.
                                                                 0x0 = Disable custom LG header extraction
                                                                 0x1 = Enable custom LG header extraction after layer C.
                                                                 0x2 = Enable custom LG header extraction after layer D.
                                                                 0x3 = Enable custom LG header extraction after layer E.
                                                                 0x4 = Enable custom LG header extraction after layer F.
                                                                 0x5-0x7 = Reserved.

                                                                 Internal:
                                                                 Nonzero implemented only in software's parse engine code.

                                                                 [LG_CUSTOM_LAYER] must be clear if PKI_GBL_PEN[CLG_PEN] is clear. */
        uint64_t rsvdrw15              : 5;  /**< [ 15: 11](R/W) Reserved. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_pkindx_cfg_s cn; */
};
typedef union bdk_pki_clx_pkindx_cfg bdk_pki_clx_pkindx_cfg_t;

static inline uint64_t BDK_PKI_CLX_PKINDX_CFG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_PKINDX_CFG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=1) && (b<=63)))
        return 0x86c000300040ll + 0x10000ll * ((a) & 0x1) + 0x100ll * ((b) & 0x3f);
    __bdk_csr_fatal("PKI_CLX_PKINDX_CFG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_PKINDX_CFG(a,b) bdk_pki_clx_pkindx_cfg_t
#define bustype_BDK_PKI_CLX_PKINDX_CFG(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_PKINDX_CFG(a,b) "PKI_CLX_PKINDX_CFG"
#define device_bar_BDK_PKI_CLX_PKINDX_CFG(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_PKINDX_CFG(a,b) (a)
#define arguments_BDK_PKI_CLX_PKINDX_CFG(a,b) (a),(b),-1,-1

/**
 * Register (NCB) pki_cl#_pkind#_kmem#
 *
 * PKI KMEM Registers
 * This register initializes the KMEM, which initializes the parse engine state for each
 * pkind. These CSRs are used only by the PKI parse engine.
 *
 * Inside the KMEM are the following parse engine registers. These registers are the
 * preferred access method for software:
 * * PKI_CL()_PKIND()_CFG.
 * * PKI_CL()_PKIND()_STYLE.
 * * PKI_CL()_PKIND()_SKIP.
 * * PKI_CL()_PKIND()_L2_CUSTOM.
 * * PKI_CL()_PKIND()_LG_CUSTOM.
 *
 * To avoid overlapping addresses, these aliases have address bit 20 set in contrast to
 * this register; the PKI address decoder ignores bit 20 when accessing
 * PKI_CL()_PKIND()_KMEM().
 *
 * Software must reload the PKI_CL()_PKIND()_KMEM() registers upon the detection of
 * PKI_ECC0_INT[KMEM_SBE] or PKI_ECC0_INT[KMEM_DBE].
 *
 * For each legal j and k value, PKI_CL(i)_PKIND(j)_KMEM(k) must be configured
 * identically for i=0..1.
 *
 * Internal:
 * The register initialization value for each PKIND and register number (plus 32 or 48
 * based on PKI_ICG()_CFG[MLO]). The other PKI_PKND* registers alias inside regions of
 * PKI_CL()_PKIND()_KMEM().
 *
 * The value of these CSRs do not directly influence PKI HW. But PKI HW supplies them
 * to the parse engine code for parsing/sequencing.
 */
union bdk_pki_clx_pkindx_kmemx
{
    uint64_t u;
    struct bdk_pki_clx_pkindx_kmemx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t data                  : 16; /**< [ 15:  0](R/W) RAM data at given address. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 16; /**< [ 15:  0](R/W) RAM data at given address. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_pkindx_kmemx_s cn; */
};
typedef union bdk_pki_clx_pkindx_kmemx bdk_pki_clx_pkindx_kmemx_t;

static inline uint64_t BDK_PKI_CLX_PKINDX_KMEMX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_PKINDX_KMEMX(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=1) && (b<=63) && (c<=15)))
        return 0x86c000200000ll + 0x10000ll * ((a) & 0x1) + 0x100ll * ((b) & 0x3f) + 8ll * ((c) & 0xf);
    __bdk_csr_fatal("PKI_CLX_PKINDX_KMEMX", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_PKINDX_KMEMX(a,b,c) bdk_pki_clx_pkindx_kmemx_t
#define bustype_BDK_PKI_CLX_PKINDX_KMEMX(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_PKINDX_KMEMX(a,b,c) "PKI_CLX_PKINDX_KMEMX"
#define device_bar_BDK_PKI_CLX_PKINDX_KMEMX(a,b,c) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_PKINDX_KMEMX(a,b,c) (a)
#define arguments_BDK_PKI_CLX_PKINDX_KMEMX(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB) pki_cl#_pkind#_l2_custom
 *
 * PKI Per-Pkind L2 Custom Extract Registers
 * This register is inside PKI_CL()_PKIND()_KMEM(). These CSRs are used only by
 * the PKI parse engine.
 *
 * For each legal j, PKI_CL(i)_PKIND(j)_L2_CUSTOM must be configured identically for i=0..1.
 *
 * Internal:
 * The value of these CSRs do not directly influence PKI HW. But PKI HW supplies them to the
 * parse engine code for parsing/sequencing.
 */
union bdk_pki_clx_pkindx_l2_custom
{
    uint64_t u;
    struct bdk_pki_clx_pkindx_l2_custom_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t valid                 : 1;  /**< [ 15: 15](R/W) Valid.
                                                                 0 = Disable custom L2 header extraction.
                                                                 1 = Enable custom L2 header extraction.

                                                                 Internal:
                                                                 [VALID] must be clear when PKI_GBL_PEN[CL2_PEN] is clear. */
        uint64_t rsvdrw14              : 7;  /**< [ 14:  8](R/W) Reserved. */
        uint64_t offset                : 8;  /**< [  7:  0](R/W) Scan offset. Pointer to first byte of 32-bit custom extraction header, as
                                                                 absolute number of bytes from beginning of packet. Must be even. If PTP_MODE,
                                                                 the 8-byte timestamp is prepended to the packet, and must be included in
                                                                 counting offset bytes. */
#else /* Word 0 - Little Endian */
        uint64_t offset                : 8;  /**< [  7:  0](R/W) Scan offset. Pointer to first byte of 32-bit custom extraction header, as
                                                                 absolute number of bytes from beginning of packet. Must be even. If PTP_MODE,
                                                                 the 8-byte timestamp is prepended to the packet, and must be included in
                                                                 counting offset bytes. */
        uint64_t rsvdrw14              : 7;  /**< [ 14:  8](R/W) Reserved. */
        uint64_t valid                 : 1;  /**< [ 15: 15](R/W) Valid.
                                                                 0 = Disable custom L2 header extraction.
                                                                 1 = Enable custom L2 header extraction.

                                                                 Internal:
                                                                 [VALID] must be clear when PKI_GBL_PEN[CL2_PEN] is clear. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_pkindx_l2_custom_s cn; */
};
typedef union bdk_pki_clx_pkindx_l2_custom bdk_pki_clx_pkindx_l2_custom_t;

static inline uint64_t BDK_PKI_CLX_PKINDX_L2_CUSTOM(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_PKINDX_L2_CUSTOM(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=1) && (b<=63)))
        return 0x86c000300058ll + 0x10000ll * ((a) & 0x1) + 0x100ll * ((b) & 0x3f);
    __bdk_csr_fatal("PKI_CLX_PKINDX_L2_CUSTOM", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_PKINDX_L2_CUSTOM(a,b) bdk_pki_clx_pkindx_l2_custom_t
#define bustype_BDK_PKI_CLX_PKINDX_L2_CUSTOM(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_PKINDX_L2_CUSTOM(a,b) "PKI_CLX_PKINDX_L2_CUSTOM"
#define device_bar_BDK_PKI_CLX_PKINDX_L2_CUSTOM(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_PKINDX_L2_CUSTOM(a,b) (a)
#define arguments_BDK_PKI_CLX_PKINDX_L2_CUSTOM(a,b) (a),(b),-1,-1

/**
 * Register (NCB) pki_cl#_pkind#_lg_custom
 *
 * PKI Per-Pkind LG Custom Extract Registers
 * This register is inside PKI_CL()_PKIND()_KMEM(). These CSRs are used only by
 * the PKI parse engine.
 *
 * For each legal j, PKI_CL(i)_PKIND(j)_LG_CUSTOM must be configured identically for i=0..1.
 *
 * Internal:
 * The value of these CSRs do not directly influence PKI HW. But PKI HW supplies them to the
 * parse engine code for parsing/sequencing.
 */
union bdk_pki_clx_pkindx_lg_custom
{
    uint64_t u;
    struct bdk_pki_clx_pkindx_lg_custom_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t offset                : 8;  /**< [  7:  0](R/W) Scan offset. Pointer to first byte of 32-bit custom extraction header, as
                                                                 relative number of bytes from PKI_WQE_S[LCPTR], PKI_WQE_S[LDPTR],
                                                                 PKI_WQE_S[LEPTR], PKI_WQE_S[LFPTR], as selected by
                                                                 PKI_CL()_PKIND()_CFG[LG_CUSTOM_LAYER]. Must be even.

                                                                 Internal:
                                                                 Support for LC/LD/LE added in software's parse engine code. */
#else /* Word 0 - Little Endian */
        uint64_t offset                : 8;  /**< [  7:  0](R/W) Scan offset. Pointer to first byte of 32-bit custom extraction header, as
                                                                 relative number of bytes from PKI_WQE_S[LCPTR], PKI_WQE_S[LDPTR],
                                                                 PKI_WQE_S[LEPTR], PKI_WQE_S[LFPTR], as selected by
                                                                 PKI_CL()_PKIND()_CFG[LG_CUSTOM_LAYER]. Must be even.

                                                                 Internal:
                                                                 Support for LC/LD/LE added in software's parse engine code. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_pkindx_lg_custom_s cn; */
};
typedef union bdk_pki_clx_pkindx_lg_custom bdk_pki_clx_pkindx_lg_custom_t;

static inline uint64_t BDK_PKI_CLX_PKINDX_LG_CUSTOM(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_PKINDX_LG_CUSTOM(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=1) && (b<=63)))
        return 0x86c000300060ll + 0x10000ll * ((a) & 0x1) + 0x100ll * ((b) & 0x3f);
    __bdk_csr_fatal("PKI_CLX_PKINDX_LG_CUSTOM", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_PKINDX_LG_CUSTOM(a,b) bdk_pki_clx_pkindx_lg_custom_t
#define bustype_BDK_PKI_CLX_PKINDX_LG_CUSTOM(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_PKINDX_LG_CUSTOM(a,b) "PKI_CLX_PKINDX_LG_CUSTOM"
#define device_bar_BDK_PKI_CLX_PKINDX_LG_CUSTOM(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_PKINDX_LG_CUSTOM(a,b) (a)
#define arguments_BDK_PKI_CLX_PKINDX_LG_CUSTOM(a,b) (a),(b),-1,-1

/**
 * Register (NCB) pki_cl#_pkind#_skip
 *
 * PKI Per-Pkind L2 Skip Registers
 * This register is inside PKI_CL()_PKIND()_KMEM(). These CSRs are used only by
 * the PKI parse engine.
 *
 * For each legal j, PKI_CL(i)_PKIND(j)_SKIP must be configured identically for i=0..1.
 *
 * Internal:
 * The value of these CSRs do not directly influence PKI HW. But PKI HW supplies them to the
 * parse engine code for parsing/sequencing.
 */
union bdk_pki_clx_pkindx_skip
{
    uint64_t u;
    struct bdk_pki_clx_pkindx_skip_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t fcs_skip              : 8;  /**< [ 15:  8](R/W) Skip amount from front of packet to first byte covered by FCS start. The skip must be
                                                                 even. If PTP_MODE, the 8-byte timestamp is prepended to the packet, and FCS_SKIP must be
                                                                 at least 8. */
        uint64_t inst_skip             : 8;  /**< [  7:  0](R/W) Skip amount from front of packet to begin parsing at. If
                                                                 PKI_CL()_PKIND()_CFG[INST_HDR] is set, points at the first byte of the
                                                                 instruction header. If INST_HDR is clear, points at the first byte to begin parsing at.
                                                                 The skip must be even. If PTP_MODE, the 8-byte timestamp is prepended to the packet, and
                                                                 INST_SKIP must be at least 8. */
#else /* Word 0 - Little Endian */
        uint64_t inst_skip             : 8;  /**< [  7:  0](R/W) Skip amount from front of packet to begin parsing at. If
                                                                 PKI_CL()_PKIND()_CFG[INST_HDR] is set, points at the first byte of the
                                                                 instruction header. If INST_HDR is clear, points at the first byte to begin parsing at.
                                                                 The skip must be even. If PTP_MODE, the 8-byte timestamp is prepended to the packet, and
                                                                 INST_SKIP must be at least 8. */
        uint64_t fcs_skip              : 8;  /**< [ 15:  8](R/W) Skip amount from front of packet to first byte covered by FCS start. The skip must be
                                                                 even. If PTP_MODE, the 8-byte timestamp is prepended to the packet, and FCS_SKIP must be
                                                                 at least 8. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_pkindx_skip_s cn; */
};
typedef union bdk_pki_clx_pkindx_skip bdk_pki_clx_pkindx_skip_t;

static inline uint64_t BDK_PKI_CLX_PKINDX_SKIP(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_PKINDX_SKIP(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=1) && (b<=63)))
        return 0x86c000300050ll + 0x10000ll * ((a) & 0x1) + 0x100ll * ((b) & 0x3f);
    __bdk_csr_fatal("PKI_CLX_PKINDX_SKIP", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_PKINDX_SKIP(a,b) bdk_pki_clx_pkindx_skip_t
#define bustype_BDK_PKI_CLX_PKINDX_SKIP(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_PKINDX_SKIP(a,b) "PKI_CLX_PKINDX_SKIP"
#define device_bar_BDK_PKI_CLX_PKINDX_SKIP(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_PKINDX_SKIP(a,b) (a)
#define arguments_BDK_PKI_CLX_PKINDX_SKIP(a,b) (a),(b),-1,-1

/**
 * Register (NCB) pki_cl#_pkind#_style
 *
 * PKI Per-Pkind Initial Style Registers
 * This register is inside PKI_CL()_PKIND()_KMEM(). These CSRs are used only by
 * the PKI parse engine.
 *
 * For each legal j, PKI_CL(i)_PKIND(j)_STYLE must be configured identically for i=0..1.
 *
 * Internal:
 * The value of these CSRs do not directly influence PKI HW. But PKI HW supplies them to the
 * parse engine code for parsing/sequencing.
 */
union bdk_pki_clx_pkindx_style
{
    uint64_t u;
    struct bdk_pki_clx_pkindx_style_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t rsvdrw15              : 1;  /**< [ 15: 15](R/W) Reserved. */
        uint64_t pm                    : 7;  /**< [ 14:  8](R/W) Initial parse mode. Bit mask of which steps the parse engine should perform, refer
                                                                 to Parse Mode:
                                                                 _ \<0\> = LA - Layer A (Ethernet dest+src, Higig/Fulcrum/DSA).
                                                                 _ \<1\> = LB - Layer B (Ethertype/VLAN, MPLS/ARP/REVARP/SNAP).
                                                                 _ \<2\> = LC - Layer C (Outer IPv4 or IPv6).
                                                                 _ \<3\> = LD - Layer D (Geneve/VXLAN/VXLANGPE/NVGRE).
                                                                 _ \<4\> = LE - Layer E (Inner IPv4 or IPv6).
                                                                 _ \<5\> = LF - Layer F (UDP, TCP, SCTP, IPCOMP, IPSEC ESP/AH, GRE).
                                                                 _ \<6\> = LG - Layer G (Custom/Application).

                                                                 The legal values are:

                                                                 _ 0x0 = Parse LA..LG.
                                                                 _ 0x1 = Parse LB..LG.
                                                                 _ 0x3 = Parse LC..LG.
                                                                 _ 0x7F = Parse none and error check none of LA..LG.
                                                                 _ else = Reserved.

                                                                 Internal:
                                                                 The following are additional constraints:

                                                                 _ [PM]\<2\> (i.e. [PM\<LC\>]) must be set when PKI_GBL_PEN[L3_PEN] is set
                                                                 _ [PM]\<3\> (i.e. [PM\<LD\>]) must be set when PKI_GBL_PEN[VIRT_PEN] is set
                                                                 _ [PM]\<4\> (i.e. [PM\<LE\>]) must be set when PKI_GBL_PEN[IL3_PEN] is set
                                                                 _ [PM]\<5\> (i.e. [PM\<LF\>]) must be set when PKI_GBL_PEN[L4_PEN] is set
                                                                 _ [PM]\<6\> (i.e. [PM\<LG\>]) must be set when PKI_GBL_PEN[CLG_PEN] is set */
        uint64_t style                 : 8;  /**< [  7:  0](R/W) Initial style. Initial style number for packets on this port, will remain as final style
                                                                 if no PCAM entries match the packet. Note only 64 final styles exist, the upper two bits
                                                                 will only be used for PCAM matching. */
#else /* Word 0 - Little Endian */
        uint64_t style                 : 8;  /**< [  7:  0](R/W) Initial style. Initial style number for packets on this port, will remain as final style
                                                                 if no PCAM entries match the packet. Note only 64 final styles exist, the upper two bits
                                                                 will only be used for PCAM matching. */
        uint64_t pm                    : 7;  /**< [ 14:  8](R/W) Initial parse mode. Bit mask of which steps the parse engine should perform, refer
                                                                 to Parse Mode:
                                                                 _ \<0\> = LA - Layer A (Ethernet dest+src, Higig/Fulcrum/DSA).
                                                                 _ \<1\> = LB - Layer B (Ethertype/VLAN, MPLS/ARP/REVARP/SNAP).
                                                                 _ \<2\> = LC - Layer C (Outer IPv4 or IPv6).
                                                                 _ \<3\> = LD - Layer D (Geneve/VXLAN/VXLANGPE/NVGRE).
                                                                 _ \<4\> = LE - Layer E (Inner IPv4 or IPv6).
                                                                 _ \<5\> = LF - Layer F (UDP, TCP, SCTP, IPCOMP, IPSEC ESP/AH, GRE).
                                                                 _ \<6\> = LG - Layer G (Custom/Application).

                                                                 The legal values are:

                                                                 _ 0x0 = Parse LA..LG.
                                                                 _ 0x1 = Parse LB..LG.
                                                                 _ 0x3 = Parse LC..LG.
                                                                 _ 0x7F = Parse none and error check none of LA..LG.
                                                                 _ else = Reserved.

                                                                 Internal:
                                                                 The following are additional constraints:

                                                                 _ [PM]\<2\> (i.e. [PM\<LC\>]) must be set when PKI_GBL_PEN[L3_PEN] is set
                                                                 _ [PM]\<3\> (i.e. [PM\<LD\>]) must be set when PKI_GBL_PEN[VIRT_PEN] is set
                                                                 _ [PM]\<4\> (i.e. [PM\<LE\>]) must be set when PKI_GBL_PEN[IL3_PEN] is set
                                                                 _ [PM]\<5\> (i.e. [PM\<LF\>]) must be set when PKI_GBL_PEN[L4_PEN] is set
                                                                 _ [PM]\<6\> (i.e. [PM\<LG\>]) must be set when PKI_GBL_PEN[CLG_PEN] is set */
        uint64_t rsvdrw15              : 1;  /**< [ 15: 15](R/W) Reserved. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_pkindx_style_s cn; */
};
typedef union bdk_pki_clx_pkindx_style bdk_pki_clx_pkindx_style_t;

static inline uint64_t BDK_PKI_CLX_PKINDX_STYLE(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_PKINDX_STYLE(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=1) && (b<=63)))
        return 0x86c000300048ll + 0x10000ll * ((a) & 0x1) + 0x100ll * ((b) & 0x3f);
    __bdk_csr_fatal("PKI_CLX_PKINDX_STYLE", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_PKINDX_STYLE(a,b) bdk_pki_clx_pkindx_style_t
#define bustype_BDK_PKI_CLX_PKINDX_STYLE(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_PKINDX_STYLE(a,b) "PKI_CLX_PKINDX_STYLE"
#define device_bar_BDK_PKI_CLX_PKINDX_STYLE(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_PKINDX_STYLE(a,b) (a)
#define arguments_BDK_PKI_CLX_PKINDX_STYLE(a,b) (a),(b),-1,-1

/**
 * Register (NCB) pki_cl#_smem#
 *
 * PKI SMEM Registers
 * This register initializes the SMEM, which configures the parse engine. These CSRs
 * are used by the PKI parse engine and other PKI hardware.
 *
 * Inside the SMEM are the following parse engine registers. These registers are the
 * preferred access method for software:
 * * PKI_CL()_STYLE()_CFG
 * * PKI_CL()_STYLE()_CFG2
 * * PKI_CL()_STYLE()_ALG
 *
 * To avoid overlapping addresses, these aliases have address bit 20 set in contrast to
 * this register; the PKI address decoder ignores bit 20 when accessing
 * PKI_CL()_SMEM().
 *
 * Software must reload the PKI_CL()_SMEM() registers upon the detection of
 * PKI_CL()_ECC_INT[SMEM_SBE] or PKI_CL()_ECC_INT[SMEM_DBE].
 *
 * For each legal j, PKI_CL(i)_SMEM(j) must be configured identically for i=0..1.
 *
 * Internal:
 * The value of these CSRs do not directly influence PKI HW, but the parse engine code
 * gets them, and the parse engine code will typically indirectly construct
 * PKI_BEWQ_S[CFG,CFG2] from them. So not very indirectly, some of these CSRs influence
 * PKI HW.
 */
union bdk_pki_clx_smemx
{
    uint64_t u;
    struct bdk_pki_clx_smemx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t data                  : 32; /**< [ 31:  0](R/W) RAM data at given address. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 32; /**< [ 31:  0](R/W) RAM data at given address. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_smemx_s cn; */
};
typedef union bdk_pki_clx_smemx bdk_pki_clx_smemx_t;

static inline uint64_t BDK_PKI_CLX_SMEMX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_SMEMX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=1) && (b<=2047)))
        return 0x86c000400000ll + 0x10000ll * ((a) & 0x1) + 8ll * ((b) & 0x7ff);
    __bdk_csr_fatal("PKI_CLX_SMEMX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_SMEMX(a,b) bdk_pki_clx_smemx_t
#define bustype_BDK_PKI_CLX_SMEMX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_SMEMX(a,b) "PKI_CLX_SMEMX"
#define device_bar_BDK_PKI_CLX_SMEMX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_SMEMX(a,b) (a)
#define arguments_BDK_PKI_CLX_SMEMX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) pki_cl#_start
 *
 * PKI Cluster Start Registers
 * This register configures a cluster. All of PKI_CL()_START must be programmed identically.
 */
union bdk_pki_clx_start
{
    uint64_t u;
    struct bdk_pki_clx_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t start                 : 11; /**< [ 10:  0](R/W) Cluster start offset. \<1:0\> must be zero. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t start                 : 11; /**< [ 10:  0](R/W) Cluster start offset. \<1:0\> must be zero. For diagnostic use only. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_start_s cn; */
};
typedef union bdk_pki_clx_start bdk_pki_clx_start_t;

static inline uint64_t BDK_PKI_CLX_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1))
        return 0x86c00000c030ll + 0x10000ll * ((a) & 0x1);
    __bdk_csr_fatal("PKI_CLX_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_START(a) bdk_pki_clx_start_t
#define bustype_BDK_PKI_CLX_START(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_START(a) "PKI_CLX_START"
#define device_bar_BDK_PKI_CLX_START(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_START(a) (a)
#define arguments_BDK_PKI_CLX_START(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_cl#_style#_alg
 *
 * PKI Per-Style Algorithm Configuration Registers
 * This register is inside PKI_CL()_SMEM(). These CSRs are used only by
 * the PKI parse engine.
 *
 * For each legal j, PKI_CL(i)_STYLE(j)_ALG must be configured identically for i=0..1.
 *
 * Internal:
 * The value of these CSRs do not directly influence PKI HW. But PKI HW supplies them
 * to the parse engine code.
 */
union bdk_pki_clx_stylex_alg
{
    uint64_t u;
    struct bdk_pki_clx_stylex_alg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t tt                    : 2;  /**< [ 31: 30](R/W) SSO tag type to schedule to, enumerated by SSO_TT_E. */
        uint64_t apad_nip              : 3;  /**< [ 29: 27](R/W) Value for PKI_WQE_S[APAD] when packet is not IP. */
        uint64_t qpg_qos               : 3;  /**< [ 26: 24](R/W) Algorithm to select QoS field in QPG calculation. Enumerated by PKI_QPGQOS_E. */
        uint64_t qpg_port_sh           : 3;  /**< [ 23: 21](R/W) Number of bits to shift port number in QPG calculation. */
        uint64_t qpg_port_msb          : 4;  /**< [ 20: 17](R/W) MSB to take from port number in QPG calculation.
                                                                 0 = Exclude port number from QPG.
                                                                 4 = Include port\<3:0\>.
                                                                 8 = Include port\<7:0\>.
                                                                 _ All other values reserved. */
        uint64_t rsvdrw16              : 6;  /**< [ 16: 11](R/W) Reserved. */
        uint64_t tag_vni               : 1;  /**< [ 10: 10](R/W) When NVGRE/VXLAN/VXLANGPE/GENEVE is found, include VNI in tag generation. When NVGRE is
                                                                 found, include VSID. */
        uint64_t tag_gtp               : 1;  /**< [  9:  9](R/W) When GTP is parsed, include GTP's TEID in tag generation.

                                                                 The GTP PKI_PCAM_TERM_E::L4_PORT PCAM entry must have
                                                                 PKI_CL()_PCAM()_ACTION()[SETTY,ADVANCE]
                                                                 be PKI_LTYPE_E::GTP,8 (ADVANCE needs to skip over the UDP header). */
        uint64_t tag_spi               : 1;  /**< [  8:  8](R/W) Include AH/ESP/GRE in tag generation.
                                                                 0 = Exclude AH/ESP/GRE in tag generation.
                                                                 1 = If IP SEC is parsed, include AH/ESP SPI field in tag generation, or if GRE
                                                                 found, include GRE call number in tag generation. */
        uint64_t tag_syn               : 1;  /**< [  7:  7](R/W) Exclude source address for TCP SYN packets.
                                                                 0 = Include source address if TAG_SRC_* used.
                                                                 1 = Exclude source address for TCP packets with SYN & !ACK, even if TAG_SRC_* set. */
        uint64_t tag_pctl              : 1;  /**< [  6:  6](R/W) Include final IPv4 protocol or IPv6 next header in tag generation. */
        uint64_t tag_vs1               : 1;  /**< [  5:  5](R/W) When VLAN stacking is parsed, include second (network order) VLAN in tuple tag generation. */
        uint64_t tag_vs0               : 1;  /**< [  4:  4](R/W) When VLAN stacking is parsed, include first (network order) VLAN in tuple tag generation. */
        uint64_t tag_vlan              : 1;  /**< [  3:  3](R/W) Reserved. */
        uint64_t tag_mpls0             : 1;  /**< [  2:  2](R/W) Reserved. */
        uint64_t tag_prt               : 1;  /**< [  1:  1](R/W) Include interface port in tag hash. */
        uint64_t wqe_vs                : 1;  /**< [  0:  0](R/W) Which VLAN to put into PKI_WQE_S[VLPTR] when VLAN stacking.
                                                                 0 = Use the first (in network order) VLAN or DSA VID.
                                                                 1 = Use the second (in network order) VLAN. */
#else /* Word 0 - Little Endian */
        uint64_t wqe_vs                : 1;  /**< [  0:  0](R/W) Which VLAN to put into PKI_WQE_S[VLPTR] when VLAN stacking.
                                                                 0 = Use the first (in network order) VLAN or DSA VID.
                                                                 1 = Use the second (in network order) VLAN. */
        uint64_t tag_prt               : 1;  /**< [  1:  1](R/W) Include interface port in tag hash. */
        uint64_t tag_mpls0             : 1;  /**< [  2:  2](R/W) Reserved. */
        uint64_t tag_vlan              : 1;  /**< [  3:  3](R/W) Reserved. */
        uint64_t tag_vs0               : 1;  /**< [  4:  4](R/W) When VLAN stacking is parsed, include first (network order) VLAN in tuple tag generation. */
        uint64_t tag_vs1               : 1;  /**< [  5:  5](R/W) When VLAN stacking is parsed, include second (network order) VLAN in tuple tag generation. */
        uint64_t tag_pctl              : 1;  /**< [  6:  6](R/W) Include final IPv4 protocol or IPv6 next header in tag generation. */
        uint64_t tag_syn               : 1;  /**< [  7:  7](R/W) Exclude source address for TCP SYN packets.
                                                                 0 = Include source address if TAG_SRC_* used.
                                                                 1 = Exclude source address for TCP packets with SYN & !ACK, even if TAG_SRC_* set. */
        uint64_t tag_spi               : 1;  /**< [  8:  8](R/W) Include AH/ESP/GRE in tag generation.
                                                                 0 = Exclude AH/ESP/GRE in tag generation.
                                                                 1 = If IP SEC is parsed, include AH/ESP SPI field in tag generation, or if GRE
                                                                 found, include GRE call number in tag generation. */
        uint64_t tag_gtp               : 1;  /**< [  9:  9](R/W) When GTP is parsed, include GTP's TEID in tag generation.

                                                                 The GTP PKI_PCAM_TERM_E::L4_PORT PCAM entry must have
                                                                 PKI_CL()_PCAM()_ACTION()[SETTY,ADVANCE]
                                                                 be PKI_LTYPE_E::GTP,8 (ADVANCE needs to skip over the UDP header). */
        uint64_t tag_vni               : 1;  /**< [ 10: 10](R/W) When NVGRE/VXLAN/VXLANGPE/GENEVE is found, include VNI in tag generation. When NVGRE is
                                                                 found, include VSID. */
        uint64_t rsvdrw16              : 6;  /**< [ 16: 11](R/W) Reserved. */
        uint64_t qpg_port_msb          : 4;  /**< [ 20: 17](R/W) MSB to take from port number in QPG calculation.
                                                                 0 = Exclude port number from QPG.
                                                                 4 = Include port\<3:0\>.
                                                                 8 = Include port\<7:0\>.
                                                                 _ All other values reserved. */
        uint64_t qpg_port_sh           : 3;  /**< [ 23: 21](R/W) Number of bits to shift port number in QPG calculation. */
        uint64_t qpg_qos               : 3;  /**< [ 26: 24](R/W) Algorithm to select QoS field in QPG calculation. Enumerated by PKI_QPGQOS_E. */
        uint64_t apad_nip              : 3;  /**< [ 29: 27](R/W) Value for PKI_WQE_S[APAD] when packet is not IP. */
        uint64_t tt                    : 2;  /**< [ 31: 30](R/W) SSO tag type to schedule to, enumerated by SSO_TT_E. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_stylex_alg_s cn; */
};
typedef union bdk_pki_clx_stylex_alg bdk_pki_clx_stylex_alg_t;

static inline uint64_t BDK_PKI_CLX_STYLEX_ALG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_STYLEX_ALG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=1) && (b<=63)))
        return 0x86c000501000ll + 0x10000ll * ((a) & 0x1) + 8ll * ((b) & 0x3f);
    __bdk_csr_fatal("PKI_CLX_STYLEX_ALG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_STYLEX_ALG(a,b) bdk_pki_clx_stylex_alg_t
#define bustype_BDK_PKI_CLX_STYLEX_ALG(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_STYLEX_ALG(a,b) "PKI_CLX_STYLEX_ALG"
#define device_bar_BDK_PKI_CLX_STYLEX_ALG(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_STYLEX_ALG(a,b) (a)
#define arguments_BDK_PKI_CLX_STYLEX_ALG(a,b) (a),(b),-1,-1

/**
 * Register (NCB) pki_cl#_style#_cfg
 *
 * PKI Per-Style Configuration Registers
 * This register is inside PKI_CL()_SMEM(). These CSRs are used by
 * the PKI parse engine and other PKI hardware.
 *
 * For each legal j, PKI_CL(i)_STYLE(j)_CFG must be configured identically for i=0..1.
 *
 * Internal:
 * The value of these CSRs do not directly influence PKI HW, but the parse engine code
 * gets them, and the parse engine code will typically indirectly construct
 * PKI_BEWQ_S[CFG] from them. So not very indirectly, these CSRs influence PKI HW.
 */
union bdk_pki_clx_stylex_cfg
{
    uint64_t u;
    struct bdk_pki_clx_stylex_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t rsvdrw31              : 1;  /**< [ 31: 31](R/W) Reserved.
                                                                 Internal:
                                                                 Parse engine only passes along field RSVDRW31, and doesn't otherwise use it. */
        uint64_t ip6_udp_opt           : 1;  /**< [ 30: 30](R/W) IPv6/UDP checksum is optional. IPv4 allows an optional UDP checksum by sending the all-0s
                                                                 patterns. IPv6 outlaws this and the spec says to always check UDP checksum.
                                                                 0 = Spec compliant, do not allow optional code.
                                                                 1 = Treat IPv6 as IPv4; the all-0s pattern will cause a UDP checksum pass.

                                                                 Internal:
                                                                 Parse engine only passes along field IP6_UDP_OPT, and doesn't otherwise use it. */
        uint64_t lenerr_en             : 1;  /**< [ 29: 29](R/W) L2 length error check enable. When set, the hardware checks that the number of packet
                                                                 bytes following the L2 length field (excluding FCS) is at least as large as the L2
                                                                 length field value whenever the Ethertype / L2 length field is \<= 1535.

                                                                 The PKI L2 length check assumes that the packet received by PKI contains a trailing FCS
                                                                 when
                                                                 the PKI_CL()_PKIND()_CFG[FCS_PRES] for the pkind of the packet is set.

                                                                 Internal:
                                                                 The parse engine clears this bit in PKI_BEWQ_S[CFG] when SNAP length checks
                                                                 are not appropriate. */
        uint64_t lenerr_eqpad          : 1;  /**< [ 28: 28](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Parse engine only passes along field LENERR_EQPAD, and doesn't otherwise use it. */
        uint64_t minmax_sel            : 1;  /**< [ 27: 27](R/W) Selects which PKI_FRM_LEN_CHK() register is used for this pkind for MINERR and MAXERR
                                                                 checks.
                                                                 0 = use PKI_FRM_LEN_CHK(0).
                                                                 1 = use PKI_FRM_LEN_CHK(1).

                                                                 Internal:
                                                                 Parse engine only passes along field MINMAX_SEL, and doesn't otherwise use it. */
        uint64_t maxerr_en             : 1;  /**< [ 26: 26](R/W) Max frame error check enable. See PKI_FRM_LEN_CHK()[MAXLEN], [MINMAX_SEL],
                                                                 PKI_OPCODE_E::L2_OVERSIZE,L2_OVERRUN, PKI_ERRLEV_E::LA, and PKI_WQE_S[ERRLEV,OPCODE].

                                                                 Internal:
                                                                 Parse engine only passes along field MAXERR_EN, and doesn't otherwise use it. */
        uint64_t minerr_en             : 1;  /**< [ 25: 25](R/W) Min frame error check enable. See PKI_FRM_LEN_CHK()[MINLEN], [MINMAX_SEL],
                                                                 PKI_OPCODE_E::L2_UNDERSIZE,L2_FRAGMENT, PKI_ERRLEV_E::LA, and PKI_WQE_S[ERRLEV,OPCODE].

                                                                 Internal:
                                                                 Parse engine only passes along field MINERR_EN, and doesn't otherwise use it. */
        uint64_t qpg_dis_grptag        : 1;  /**< [ 24: 24](R/W) Disable computing group using PKI_WQE_S[TAG]. See PKI_WQE_S[GRP].
                                                                 Internal:
                                                                 Parse engine only passes along field QPG_DIS_GRPTAG, and doesn't otherwise use it. */
        uint64_t fcs_strip             : 1;  /**< [ 23: 23](R/W) Strip L2 FCS bytes from packet, decrease PKI_WQE_S[LEN] by 4 bytes. Corresponding
                                                                 PKI_CL()_PKIND()_CFG[FCS_PRES] must be set when [FCS_STRIP] is set.

                                                                 See the PKI_OPCODE_E::L2_PUNY exception case.

                                                                 Internal:
                                                                 Parse engine only passes along field FCS_STRIP, and doesn't otherwise use it.

                                                                 The microcode doesn't need to clear [FCS_STRIP] in PKI_BEWQ_S[CFG] when
                                                                 a PKI_OPCODE_E::L2_PUNY occurs. PKI BE hardware will not decrement PKI_WQE_S[LEN]
                                                                 when it would end up zero or negative. */
        uint64_t fcs_chk               : 1;  /**< [ 22: 22](R/W) FCS checking enabled. Corresponding PKI_CL()_PKIND()_CFG[FCS_PRES] must be set
                                                                 when [FCS_CHK] is set. See PKI_OPCODE_E::L2_PFCS,L2_FRAGMENT,L2_OVERRUN,
                                                                 PKI_ERRLEV_E::LA, and PKI_WQE_S[ERRLEV,OPCODE].

                                                                 Internal:
                                                                 Parse engine only passes along field FCS_CHK, and doesn't otherwise use it. */
        uint64_t rawdrp                : 1;  /**< [ 21: 21](R/W) Allow RAW packet drop.
                                                                 0 = Never drop packets with PKI_WQE_S[RAW] set.
                                                                 1 = Allow the PKI to drop RAW packets based on PKI_QPG_TBLB()[ENA_RED/ENA_DROP].

                                                                 Internal:
                                                                 Parse engine only passes along field RAWDRP, and doesn't otherwise use it. */
        uint64_t drop                  : 1;  /**< [ 20: 20](R/W) Force packet dropping.
                                                                 0 = Drop packet based on PKI_QPG_TBLB()[ENA_RED/ENA_DROP].
                                                                 1 = Always drop the packet. Overrides [NODROP], [RAWDRP].

                                                                 Internal:
                                                                 Parse engine only passes along field DROP, and doesn't otherwise use it. */
        uint64_t nodrop                : 1;  /**< [ 19: 19](R/W) Disable QoS packet drop.
                                                                 0 = Allowed to drop packet based on PKI_QPG_TBLB()[ENA_RED/ENA_DROP].
                                                                 1 = Never drop the packet. Overrides [RAWDRP].

                                                                 Internal:
                                                                 Parse engine only passes along field NODROP, and doesn't otherwise use it. */
        uint64_t qpg_dis_padd          : 1;  /**< [ 18: 18](R/W) Disable computing port adder by QPG algorithm. See PKI_WQE_S[CHAN].
                                                                 Internal:
                                                                 Parse engine only passes along field QPG_DIS_PADD, and doesn't otherwise use it. */
        uint64_t qpg_dis_grp           : 1;  /**< [ 17: 17](R/W) Disable computing group by QPG algorithm.
                                                                 Internal:
                                                                 Parse engine uses [QPG_DIS_GRP] only for custom pass 1 PKI workaround for limited
                                                                 applications,
                                                                 which makes WQE[GRP]\<5:0\> a function of WQE[TAG] for IPv4/UDP/TCP.
                                                                 Parse engine passes along field QPG_DIS_GRP unmodified.

                                                                 [QPG_DIS_GRP] should normally always be clear.

                                                                 PKI_WQE_S[GRP] is normally calculated solely by PKI HW. But if
                                                                 [QPG_DIS_GRP] is set, PKI_WQE_S[GRP] is PKI_BEWQ_S[GRP]. */
        uint64_t qpg_dis_aura          : 1;  /**< [ 16: 16](R/W) Disable computing aura by QPG algorithm.

                                                                 [QPG_DIS_AURA] should normally always be clear.

                                                                 Internal:
                                                                 Parse engine only passes along field QPG_DIS_AURA, and doesn't otherwise use it.
                                                                 PKI_WQE_S[AURA] is normally calculated solely by PKI BE, but if [QPG_DIS_AURA] is set,
                                                                 PKI_WQE_S[AURA] is PKI_BEWQ_S[AURA]. */
        uint64_t rsvdrw15              : 5;  /**< [ 15: 11](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Parse engine code may corrupt PKI_BEWQ_S[CFG]\<15:11\> during QPG calculations.
                                                                 See [QPG_BASE]. Effectively, PKI_BEWQ_S[CFG]\<15:11\> is unpredictable. */
        uint64_t qpg_base              : 11; /**< [ 10:  0](R/W) Base index into PKI_QPG_TBL().
                                                                 Internal:
                                                                 The parse engine typically starts with [QPG_BASE], performs the
                                                                 QPG add in place, and passes the result through to PKI_BEWQ_S[CFG]. The
                                                                 port shift and carry from the add may corrupt PKI_BEWQ_S[CFG]\<15:11\>. */
#else /* Word 0 - Little Endian */
        uint64_t qpg_base              : 11; /**< [ 10:  0](R/W) Base index into PKI_QPG_TBL().
                                                                 Internal:
                                                                 The parse engine typically starts with [QPG_BASE], performs the
                                                                 QPG add in place, and passes the result through to PKI_BEWQ_S[CFG]. The
                                                                 port shift and carry from the add may corrupt PKI_BEWQ_S[CFG]\<15:11\>. */
        uint64_t rsvdrw15              : 5;  /**< [ 15: 11](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Parse engine code may corrupt PKI_BEWQ_S[CFG]\<15:11\> during QPG calculations.
                                                                 See [QPG_BASE]. Effectively, PKI_BEWQ_S[CFG]\<15:11\> is unpredictable. */
        uint64_t qpg_dis_aura          : 1;  /**< [ 16: 16](R/W) Disable computing aura by QPG algorithm.

                                                                 [QPG_DIS_AURA] should normally always be clear.

                                                                 Internal:
                                                                 Parse engine only passes along field QPG_DIS_AURA, and doesn't otherwise use it.
                                                                 PKI_WQE_S[AURA] is normally calculated solely by PKI BE, but if [QPG_DIS_AURA] is set,
                                                                 PKI_WQE_S[AURA] is PKI_BEWQ_S[AURA]. */
        uint64_t qpg_dis_grp           : 1;  /**< [ 17: 17](R/W) Disable computing group by QPG algorithm.
                                                                 Internal:
                                                                 Parse engine uses [QPG_DIS_GRP] only for custom pass 1 PKI workaround for limited
                                                                 applications,
                                                                 which makes WQE[GRP]\<5:0\> a function of WQE[TAG] for IPv4/UDP/TCP.
                                                                 Parse engine passes along field QPG_DIS_GRP unmodified.

                                                                 [QPG_DIS_GRP] should normally always be clear.

                                                                 PKI_WQE_S[GRP] is normally calculated solely by PKI HW. But if
                                                                 [QPG_DIS_GRP] is set, PKI_WQE_S[GRP] is PKI_BEWQ_S[GRP]. */
        uint64_t qpg_dis_padd          : 1;  /**< [ 18: 18](R/W) Disable computing port adder by QPG algorithm. See PKI_WQE_S[CHAN].
                                                                 Internal:
                                                                 Parse engine only passes along field QPG_DIS_PADD, and doesn't otherwise use it. */
        uint64_t nodrop                : 1;  /**< [ 19: 19](R/W) Disable QoS packet drop.
                                                                 0 = Allowed to drop packet based on PKI_QPG_TBLB()[ENA_RED/ENA_DROP].
                                                                 1 = Never drop the packet. Overrides [RAWDRP].

                                                                 Internal:
                                                                 Parse engine only passes along field NODROP, and doesn't otherwise use it. */
        uint64_t drop                  : 1;  /**< [ 20: 20](R/W) Force packet dropping.
                                                                 0 = Drop packet based on PKI_QPG_TBLB()[ENA_RED/ENA_DROP].
                                                                 1 = Always drop the packet. Overrides [NODROP], [RAWDRP].

                                                                 Internal:
                                                                 Parse engine only passes along field DROP, and doesn't otherwise use it. */
        uint64_t rawdrp                : 1;  /**< [ 21: 21](R/W) Allow RAW packet drop.
                                                                 0 = Never drop packets with PKI_WQE_S[RAW] set.
                                                                 1 = Allow the PKI to drop RAW packets based on PKI_QPG_TBLB()[ENA_RED/ENA_DROP].

                                                                 Internal:
                                                                 Parse engine only passes along field RAWDRP, and doesn't otherwise use it. */
        uint64_t fcs_chk               : 1;  /**< [ 22: 22](R/W) FCS checking enabled. Corresponding PKI_CL()_PKIND()_CFG[FCS_PRES] must be set
                                                                 when [FCS_CHK] is set. See PKI_OPCODE_E::L2_PFCS,L2_FRAGMENT,L2_OVERRUN,
                                                                 PKI_ERRLEV_E::LA, and PKI_WQE_S[ERRLEV,OPCODE].

                                                                 Internal:
                                                                 Parse engine only passes along field FCS_CHK, and doesn't otherwise use it. */
        uint64_t fcs_strip             : 1;  /**< [ 23: 23](R/W) Strip L2 FCS bytes from packet, decrease PKI_WQE_S[LEN] by 4 bytes. Corresponding
                                                                 PKI_CL()_PKIND()_CFG[FCS_PRES] must be set when [FCS_STRIP] is set.

                                                                 See the PKI_OPCODE_E::L2_PUNY exception case.

                                                                 Internal:
                                                                 Parse engine only passes along field FCS_STRIP, and doesn't otherwise use it.

                                                                 The microcode doesn't need to clear [FCS_STRIP] in PKI_BEWQ_S[CFG] when
                                                                 a PKI_OPCODE_E::L2_PUNY occurs. PKI BE hardware will not decrement PKI_WQE_S[LEN]
                                                                 when it would end up zero or negative. */
        uint64_t qpg_dis_grptag        : 1;  /**< [ 24: 24](R/W) Disable computing group using PKI_WQE_S[TAG]. See PKI_WQE_S[GRP].
                                                                 Internal:
                                                                 Parse engine only passes along field QPG_DIS_GRPTAG, and doesn't otherwise use it. */
        uint64_t minerr_en             : 1;  /**< [ 25: 25](R/W) Min frame error check enable. See PKI_FRM_LEN_CHK()[MINLEN], [MINMAX_SEL],
                                                                 PKI_OPCODE_E::L2_UNDERSIZE,L2_FRAGMENT, PKI_ERRLEV_E::LA, and PKI_WQE_S[ERRLEV,OPCODE].

                                                                 Internal:
                                                                 Parse engine only passes along field MINERR_EN, and doesn't otherwise use it. */
        uint64_t maxerr_en             : 1;  /**< [ 26: 26](R/W) Max frame error check enable. See PKI_FRM_LEN_CHK()[MAXLEN], [MINMAX_SEL],
                                                                 PKI_OPCODE_E::L2_OVERSIZE,L2_OVERRUN, PKI_ERRLEV_E::LA, and PKI_WQE_S[ERRLEV,OPCODE].

                                                                 Internal:
                                                                 Parse engine only passes along field MAXERR_EN, and doesn't otherwise use it. */
        uint64_t minmax_sel            : 1;  /**< [ 27: 27](R/W) Selects which PKI_FRM_LEN_CHK() register is used for this pkind for MINERR and MAXERR
                                                                 checks.
                                                                 0 = use PKI_FRM_LEN_CHK(0).
                                                                 1 = use PKI_FRM_LEN_CHK(1).

                                                                 Internal:
                                                                 Parse engine only passes along field MINMAX_SEL, and doesn't otherwise use it. */
        uint64_t lenerr_eqpad          : 1;  /**< [ 28: 28](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Parse engine only passes along field LENERR_EQPAD, and doesn't otherwise use it. */
        uint64_t lenerr_en             : 1;  /**< [ 29: 29](R/W) L2 length error check enable. When set, the hardware checks that the number of packet
                                                                 bytes following the L2 length field (excluding FCS) is at least as large as the L2
                                                                 length field value whenever the Ethertype / L2 length field is \<= 1535.

                                                                 The PKI L2 length check assumes that the packet received by PKI contains a trailing FCS
                                                                 when
                                                                 the PKI_CL()_PKIND()_CFG[FCS_PRES] for the pkind of the packet is set.

                                                                 Internal:
                                                                 The parse engine clears this bit in PKI_BEWQ_S[CFG] when SNAP length checks
                                                                 are not appropriate. */
        uint64_t ip6_udp_opt           : 1;  /**< [ 30: 30](R/W) IPv6/UDP checksum is optional. IPv4 allows an optional UDP checksum by sending the all-0s
                                                                 patterns. IPv6 outlaws this and the spec says to always check UDP checksum.
                                                                 0 = Spec compliant, do not allow optional code.
                                                                 1 = Treat IPv6 as IPv4; the all-0s pattern will cause a UDP checksum pass.

                                                                 Internal:
                                                                 Parse engine only passes along field IP6_UDP_OPT, and doesn't otherwise use it. */
        uint64_t rsvdrw31              : 1;  /**< [ 31: 31](R/W) Reserved.
                                                                 Internal:
                                                                 Parse engine only passes along field RSVDRW31, and doesn't otherwise use it. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_stylex_cfg_s cn; */
};
typedef union bdk_pki_clx_stylex_cfg bdk_pki_clx_stylex_cfg_t;

static inline uint64_t BDK_PKI_CLX_STYLEX_CFG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_STYLEX_CFG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=1) && (b<=63)))
        return 0x86c000500000ll + 0x10000ll * ((a) & 0x1) + 8ll * ((b) & 0x3f);
    __bdk_csr_fatal("PKI_CLX_STYLEX_CFG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_STYLEX_CFG(a,b) bdk_pki_clx_stylex_cfg_t
#define bustype_BDK_PKI_CLX_STYLEX_CFG(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_STYLEX_CFG(a,b) "PKI_CLX_STYLEX_CFG"
#define device_bar_BDK_PKI_CLX_STYLEX_CFG(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_STYLEX_CFG(a,b) (a)
#define arguments_BDK_PKI_CLX_STYLEX_CFG(a,b) (a),(b),-1,-1

/**
 * Register (NCB) pki_cl#_style#_cfg2
 *
 * PKI Per-Style Configuration 2 Registers
 * This register is inside PKI_CL()_SMEM(). These CSRs are used by
 * the PKI parse engine and other PKI hardware.
 *
 * For each legal j, PKI_CL(i)_STYLE(j)_CFG2 must be configured identically for i=0..1.
 *
 * Internal:
 * The value of these CSRs do not directly influence PKI HW, but the parse engine code
 * gets them, and the parse engine code will typically indirectly construct
 * PKI_BEWQ_S[CFG2] from them. So not very indirectly, these CSRs influence PKI HW.
 */
union bdk_pki_clx_stylex_cfg2
{
    uint64_t u;
    struct bdk_pki_clx_stylex_cfg2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t tag_inc               : 4;  /**< [ 31: 28](R/W) Include masked tags using PKI_TAG_INC()_MASK. Each bit indicates to include the
                                                                 corresponding PKI_TAG_INC()_MASK range. See also PKI_TAG_INC()_CTL
                                                                 and PKI_WQE_S[TAG].

                                                                 Internal:
                                                                 The parse engine must clear these bits if the BE is not to compute the tag, e.g. when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t rsvdrw27              : 3;  /**< [ 27: 25](R/W) Reserved.
                                                                 Internal:
                                                                 Parse engine only passes along field RSVDRW27, and doesn't otherwise use it. */
        uint64_t tag_masken            : 1;  /**< [ 24: 24](R/W) When set, apply PKI_STYLE()_TAG_MASK to computed tag. See PKI_WQE_S[TAG].
                                                                 Internal:
                                                                 The parse engine must clear this bit if the BE is not to compute the tag, e.g. when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_src_lg            : 1;  /**< [ 23: 23](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Description from before when TAG_SRC_LG became reserved:

                                                                 The parse engine must clear this bit for PKI BE for TCP packets with SYN flag set
                                                                 and ACK flag clear when PKI_CL()_STYLE()_ALG[TAG_SYN] set, or when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_src_lf            : 1;  /**< [ 22: 22](R/W) When set, PKI hardware includes the (inner or outer) IPv4/IPv6 TCP/UDP/SCTP
                                                                 source port in tuple tag generation when PKI_LTYPE(PKI_WQE_S[LFTY])_MAP[BELTYPE]
                                                                 equals any of PKI_BELTYPE_E::TCP,UDP,SCTP. PKI_WQE_S[LFPTR] points to the
                                                                 TCP/UDP/SCTP header in this case. In an IP-in-IP case, [TAG_SRC_LF] refers
                                                                 to the inner IPv4/IPv6 TCP/UDP/SCTP, else the outer/only IPv4/IPv6 TCP/UDP/SCTP.
                                                                 See PKI_WQE_S[TAG].

                                                                 Internal:
                                                                 The parse engine must clear this bit for PKI BE for TCP packets with SYN flag set
                                                                 and ACK flag clear when PKI_CL()_STYLE()_ALG[TAG_SYN] is set, or when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_src_le            : 1;  /**< [ 21: 21](R/W) When set, PKI hardware includes the inner IPv4/IPv6 source address (in an
                                                                 IP-in-IP case) in tuple tag generation when PKI_LTYPE(PKI_WQE_S[LETY])_MAP[BELTYPE]
                                                                 equals either of PKI_BELTYPE_E::IP4,IP6. PKI_WQE_S[LEPTR] points to the inner
                                                                 IPv4/IPv6 header in this case. See PKI_WQE_S[TAG].

                                                                 Internal:
                                                                 The parse engine must clear this bit for PKI BE for TCP packets with SYN flag set
                                                                 and ACK flag clear when PKI_CL()_STYLE()_ALG[TAG_SYN] is set, or when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_src_ld            : 1;  /**< [ 20: 20](R/W) When set, PKI hardware includes the outer IPv4/IPv6 UDP source port (in an
                                                                 IP-in-IP case) in tuple tag generation when PKI_LTYPE(PKI_WQE_S[LDTY])_MAP[BELTYPE]
                                                                 equals PKI_BELTYPE_E::UDP. PKI_WQE_S[LDPTR] points to the UDP header in this case.
                                                                 See PKI_WQE_S[TAG].

                                                                 Internal:
                                                                 The parse engine must clear this bit for PKI BE for TCP packets with SYN flag set
                                                                 and ACK flag clear when PKI_CL()_STYLE()_ALG[TAG_SYN] is set, or when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_src_lc            : 1;  /**< [ 19: 19](R/W) When set, PKI hardware includes the outermost IPv4/IPv6 source address
                                                                 in tuple tag generation when PKI_LTYPE(PKI_WQE_S[LCTY])_MAP[BELTYPE]
                                                                 equals either of PKI_BELTYPE_E::IP4,IP6. PKI_WQE_S[LCPTR] points to the
                                                                 IPv4/IPv6 header in this case. See PKI_WQE_S[TAG].

                                                                 Internal:
                                                                 The parse engine must clear this bit for PKI BE for TCP packets with SYN flag set
                                                                 and ACK flag clear when PKI_CL()_STYLE()_ALG[TAG_SYN] is set, or when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_src_lb            : 1;  /**< [ 18: 18](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Description from before when TAG_SRC_LB became reserved:

                                                                 The parse engine must clear this bit for PKI BE for TCP packets with SYN flag set
                                                                 and ACK flag clear when PKI_CL()_STYLE()_ALG[TAG_SYN] is set, or when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_dst_lg            : 1;  /**< [ 17: 17](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Description from before when TAG_DST_LG became reserved:

                                                                 The parse engine must clear this bit if the BE is not to compute the tag, e.g. when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_dst_lf            : 1;  /**< [ 16: 16](R/W) When set, PKI hardware includes the (inner or outer) IPv4/IPv6 TCP/UDP/SCTP
                                                                 destination port in tuple tag generation when PKI_LTYPE(PKI_WQE_S[LFTY])_MAP[BELTYPE]
                                                                 equals any of PKI_BELTYPE_E::TCP,UDP,SCTP. PKI_WQE_S[LFPTR] points to the
                                                                 TCP/UDP/SCTP header in this case. In an IP-in-IP case, [TAG_DST_LF] refers
                                                                 to the inner IPv4/IPv6 TCP/UDP/SCTP, else the outer/only IPv4/IPv6 TCP/UDP/SCTP.
                                                                 See PKI_WQE_S[TAG].

                                                                 Internal:
                                                                 The parse engine must clear this bit if the BE is not to compute the tag, e.g. when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_dst_le            : 1;  /**< [ 15: 15](R/W) When set, PKI hardware includes the inner IPv4/IPv6 destination address (in an
                                                                 IP-in-IP case) in tuple tag generation when PKI_LTYPE(PKI_WQE_S[LETY])_MAP[BELTYPE]
                                                                 equals either of PKI_BELTYPE_E::IP4,IP6. PKI_WQE_S[LEPTR] points to the inner
                                                                 IPv4/IPv6 header in this case. See PKI_WQE_S[TAG].

                                                                 Internal:
                                                                 The parse engine must clear this bit if the BE is not to compute the tag, e.g. when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_dst_ld            : 1;  /**< [ 14: 14](R/W) When set, PKI hardware includes the outer IPv4/IPv6 UDP destination port (in an
                                                                 IP-in-IP case) in tuple tag generation when PKI_LTYPE(PKI_WQE_S[LDTY])_MAP[BELTYPE]
                                                                 equals PKI_BELTYPE_E::UDP. PKI_WQE_S[LDPTR] points to the UDP header in this case.
                                                                 See PKI_WQE_S[TAG].

                                                                 Internal:
                                                                 The parse engine must clear this bit if the BE is not to compute the tag, e.g. when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_dst_lc            : 1;  /**< [ 13: 13](R/W) When set, PKI hardware includes the outermost IPv4/IPv6 destination address
                                                                 in tuple tag generation when PKI_LTYPE(PKI_WQE_S[LCTY])_MAP[BELTYPE]
                                                                 equals either of PKI_BELTYPE_E::IP4,IP6. PKI_WQE_S[LCPTR] points to the
                                                                 IPv4/IPv6 header in this case. See PKI_WQE_S[TAG].

                                                                 Internal:
                                                                 The parse engine must clear this bit if the BE is not to compute the tag, e.g. when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_dst_lb            : 1;  /**< [ 12: 12](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Description from before when TAG_DST_LB became reserved:

                                                                 The parse engine must clear this bit if the BE is not to compute the tag, e.g. when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t len_lg                : 1;  /**< [ 11: 11](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Parse engine only passes along field LEN_LG, and doesn't otherwise use it. */
        uint64_t len_lf                : 1;  /**< [ 10: 10](R/W) When set, PKI hardware performs an (inner or outer) IPv4/IPv6 TCP/UDP/SCTP
                                                                 PKI_OPCODE_E::L4_LEN check when PKI_LTYPE(PKI_WQE_S[LFTY])_MAP[BELTYPE]
                                                                 equals any of PKI_BELTYPE_E::TCP,UDP,SCTP. PKI_WQE_S[LFPTR] points to the
                                                                 TCP/UDP/SCTP header in this case. In an IP-in-IP case, [LEN_LF] refers
                                                                 to the inner IPv4/IPv6 TCP/UDP/SCTP, else the outer/only IPv4/IPv6 TCP/UDP/SCTP.
                                                                 See PKI_WQE_S[ERRLEV,OPCODE] and PKI_ERRLEV_E::LF.

                                                                 Internal:
                                                                 Parse engine only passes along field LEN_LF, and doesn't otherwise use it. */
        uint64_t len_le                : 1;  /**< [  9:  9](R/W) When set, PKI hardware performs an inner IPv4/IPv6 PKI_OPCODE_E::IP_MALD check (in an
                                                                 IP-in-IP case) when PKI_LTYPE(PKI_WQE_S[LETY])_MAP[BELTYPE] equals either of
                                                                 PKI_BELTYPE_E::IP4,IP6. PKI_WQE_S[LEPTR] points to the inner IPv4/IPv6 header in this
                                                                 case. See PKI_WQE_S[ERRLEV,OPCODE] and PKI_ERRLEV_E::LE.

                                                                 Internal:
                                                                 Parse engine only passes along field LEN_LE, and doesn't otherwise use it. */
        uint64_t len_ld                : 1;  /**< [  8:  8](R/W) When set, PKI hardware performs an outer IPv4/IPv6 UDP PKI_OPCODE_E::L4_LEN
                                                                 check (in an IP-in-IP case) when PKI_LTYPE(PKI_WQE_S[LDTY])_MAP[BELTYPE]
                                                                 equals PKI_BELTYPE_E::UDP. PKI_WQE_S[LDPTR] points to the UDP header in this case.
                                                                 See PKI_WQE_S[ERRLEV,OPCODE] and PKI_ERRLEV_E::LD.

                                                                 Internal:
                                                                 Parse engine only passes along field LEN_LD, and doesn't otherwise use it. */
        uint64_t len_lc                : 1;  /**< [  7:  7](R/W) When set, PKI hardware performs an outermost IPv4/IPv6 PKI_OPCODE_E::IP_MALD
                                                                 check when PKI_LTYPE(PKI_WQE_S[LCTY])_MAP[BELTYPE] equals either of
                                                                 PKI_BELTYPE_E::IP4,IP6. PKI_WQE_S[LCPTR] points to the IPv4/IPv6 header in this
                                                                 case. See PKI_WQE_S[ERRLEV,OPCODE] and PKI_ERRLEV_E::LC.

                                                                 Internal:
                                                                 Parse engine only passes along field LEN_LC, and doesn't otherwise use it. */
        uint64_t len_lb                : 1;  /**< [  6:  6](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Parse engine only passes along field LEN_LB, and doesn't otherwise use it. */
        uint64_t csum_lg               : 1;  /**< [  5:  5](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Parse engine only passes along field CSUM_LG, and doesn't otherwise use it. */
        uint64_t csum_lf               : 1;  /**< [  4:  4](R/W) When set, PKI hardware performs an (inner or outer) IPv4/IPv6 TCP/UDP/SCTP
                                                                 PKI_OPCODE_E::L4_CHK check when PKI_LTYPE(PKI_WQE_S[LFTY])_MAP[BELTYPE]
                                                                 equals any of PKI_BELTYPE_E::TCP,UDP,SCTP. PKI_WQE_S[LFPTR] points to the
                                                                 TCP/UDP/SCTP header in this case. In an IP-in-IP case, [CSUM_LF] refers
                                                                 to the inner IPv4/IPv6 TCP/UDP/SCTP, else the outer/only IPv4/IPv6 TCP/UDP/SCTP.
                                                                 See PKI_WQE_S[ERRLEV,OPCODE] and PKI_ERRLEV_E::LF.

                                                                 Internal:
                                                                 Parse engine only passes along field CSUM_LF, and doesn't otherwise use it. */
        uint64_t csum_le               : 1;  /**< [  3:  3](R/W) When set, PKI hardware performs an inner IPv4/IPv6 PKI_OPCODE_E::IP_CHK check (in an
                                                                 IP-in-IP case) when PKI_LTYPE(PKI_WQE_S[LETY])_MAP[BELTYPE] equals either of
                                                                 PKI_BELTYPE_E::IP4,IP6. PKI_WQE_S[LEPTR] points to the inner IPv4/IPv6 header in this
                                                                 case. See PKI_WQE_S[ERRLEV,OPCODE] and PKI_ERRLEV_E::LE.

                                                                 Internal:
                                                                 Parse engine only passes along field CSUM_LE, and doesn't otherwise use it. */
        uint64_t csum_ld               : 1;  /**< [  2:  2](R/W) When set, PKI hardware performs an outer IPv4/IPv6 UDP PKI_OPCODE_E::L4_CHK
                                                                 check (in an IP-in-IP case) when PKI_LTYPE(PKI_WQE_S[LDTY])_MAP[BELTYPE]
                                                                 equals PKI_BELTYPE_E::UDP. PKI_WQE_S[LDPTR] points to the UDP header in this case.
                                                                 See PKI_WQE_S[ERRLEV,OPCODE] and PKI_ERRLEV_E::LD.

                                                                 Internal:
                                                                 Parse engine only passes along field CSUM_LD, and doesn't otherwise use it. */
        uint64_t csum_lc               : 1;  /**< [  1:  1](R/W) When set, PKI hardware performs an outermost IPv4/IPv6 PKI_OPCODE_E::IP_CHK
                                                                 check when PKI_LTYPE(PKI_WQE_S[LCTY])_MAP[BELTYPE] equals either of
                                                                 PKI_BELTYPE_E::IP4,IP6. PKI_WQE_S[LCPTR] points to the IPv4/IPv6 header in this
                                                                 case. See PKI_WQE_S[ERRLEV,OPCODE] and PKI_ERRLEV_E::LC.

                                                                 Internal:
                                                                 Parse engine only passes along field CSUM_LC, and doesn't otherwise use it. */
        uint64_t csum_lb               : 1;  /**< [  0:  0](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Microcode replaces this bit with PKI_CL()_PKIND()_CFG[FCS_PRES]. PKI BE hardware uses it
                                                                 for length calculation using fcs_pres_size.

                                                                 where fcs_pres_size = (PKI_CL()_PKIND()_CFG[FCS_PRES]? 4 : 0). */
#else /* Word 0 - Little Endian */
        uint64_t csum_lb               : 1;  /**< [  0:  0](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Microcode replaces this bit with PKI_CL()_PKIND()_CFG[FCS_PRES]. PKI BE hardware uses it
                                                                 for length calculation using fcs_pres_size.

                                                                 where fcs_pres_size = (PKI_CL()_PKIND()_CFG[FCS_PRES]? 4 : 0). */
        uint64_t csum_lc               : 1;  /**< [  1:  1](R/W) When set, PKI hardware performs an outermost IPv4/IPv6 PKI_OPCODE_E::IP_CHK
                                                                 check when PKI_LTYPE(PKI_WQE_S[LCTY])_MAP[BELTYPE] equals either of
                                                                 PKI_BELTYPE_E::IP4,IP6. PKI_WQE_S[LCPTR] points to the IPv4/IPv6 header in this
                                                                 case. See PKI_WQE_S[ERRLEV,OPCODE] and PKI_ERRLEV_E::LC.

                                                                 Internal:
                                                                 Parse engine only passes along field CSUM_LC, and doesn't otherwise use it. */
        uint64_t csum_ld               : 1;  /**< [  2:  2](R/W) When set, PKI hardware performs an outer IPv4/IPv6 UDP PKI_OPCODE_E::L4_CHK
                                                                 check (in an IP-in-IP case) when PKI_LTYPE(PKI_WQE_S[LDTY])_MAP[BELTYPE]
                                                                 equals PKI_BELTYPE_E::UDP. PKI_WQE_S[LDPTR] points to the UDP header in this case.
                                                                 See PKI_WQE_S[ERRLEV,OPCODE] and PKI_ERRLEV_E::LD.

                                                                 Internal:
                                                                 Parse engine only passes along field CSUM_LD, and doesn't otherwise use it. */
        uint64_t csum_le               : 1;  /**< [  3:  3](R/W) When set, PKI hardware performs an inner IPv4/IPv6 PKI_OPCODE_E::IP_CHK check (in an
                                                                 IP-in-IP case) when PKI_LTYPE(PKI_WQE_S[LETY])_MAP[BELTYPE] equals either of
                                                                 PKI_BELTYPE_E::IP4,IP6. PKI_WQE_S[LEPTR] points to the inner IPv4/IPv6 header in this
                                                                 case. See PKI_WQE_S[ERRLEV,OPCODE] and PKI_ERRLEV_E::LE.

                                                                 Internal:
                                                                 Parse engine only passes along field CSUM_LE, and doesn't otherwise use it. */
        uint64_t csum_lf               : 1;  /**< [  4:  4](R/W) When set, PKI hardware performs an (inner or outer) IPv4/IPv6 TCP/UDP/SCTP
                                                                 PKI_OPCODE_E::L4_CHK check when PKI_LTYPE(PKI_WQE_S[LFTY])_MAP[BELTYPE]
                                                                 equals any of PKI_BELTYPE_E::TCP,UDP,SCTP. PKI_WQE_S[LFPTR] points to the
                                                                 TCP/UDP/SCTP header in this case. In an IP-in-IP case, [CSUM_LF] refers
                                                                 to the inner IPv4/IPv6 TCP/UDP/SCTP, else the outer/only IPv4/IPv6 TCP/UDP/SCTP.
                                                                 See PKI_WQE_S[ERRLEV,OPCODE] and PKI_ERRLEV_E::LF.

                                                                 Internal:
                                                                 Parse engine only passes along field CSUM_LF, and doesn't otherwise use it. */
        uint64_t csum_lg               : 1;  /**< [  5:  5](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Parse engine only passes along field CSUM_LG, and doesn't otherwise use it. */
        uint64_t len_lb                : 1;  /**< [  6:  6](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Parse engine only passes along field LEN_LB, and doesn't otherwise use it. */
        uint64_t len_lc                : 1;  /**< [  7:  7](R/W) When set, PKI hardware performs an outermost IPv4/IPv6 PKI_OPCODE_E::IP_MALD
                                                                 check when PKI_LTYPE(PKI_WQE_S[LCTY])_MAP[BELTYPE] equals either of
                                                                 PKI_BELTYPE_E::IP4,IP6. PKI_WQE_S[LCPTR] points to the IPv4/IPv6 header in this
                                                                 case. See PKI_WQE_S[ERRLEV,OPCODE] and PKI_ERRLEV_E::LC.

                                                                 Internal:
                                                                 Parse engine only passes along field LEN_LC, and doesn't otherwise use it. */
        uint64_t len_ld                : 1;  /**< [  8:  8](R/W) When set, PKI hardware performs an outer IPv4/IPv6 UDP PKI_OPCODE_E::L4_LEN
                                                                 check (in an IP-in-IP case) when PKI_LTYPE(PKI_WQE_S[LDTY])_MAP[BELTYPE]
                                                                 equals PKI_BELTYPE_E::UDP. PKI_WQE_S[LDPTR] points to the UDP header in this case.
                                                                 See PKI_WQE_S[ERRLEV,OPCODE] and PKI_ERRLEV_E::LD.

                                                                 Internal:
                                                                 Parse engine only passes along field LEN_LD, and doesn't otherwise use it. */
        uint64_t len_le                : 1;  /**< [  9:  9](R/W) When set, PKI hardware performs an inner IPv4/IPv6 PKI_OPCODE_E::IP_MALD check (in an
                                                                 IP-in-IP case) when PKI_LTYPE(PKI_WQE_S[LETY])_MAP[BELTYPE] equals either of
                                                                 PKI_BELTYPE_E::IP4,IP6. PKI_WQE_S[LEPTR] points to the inner IPv4/IPv6 header in this
                                                                 case. See PKI_WQE_S[ERRLEV,OPCODE] and PKI_ERRLEV_E::LE.

                                                                 Internal:
                                                                 Parse engine only passes along field LEN_LE, and doesn't otherwise use it. */
        uint64_t len_lf                : 1;  /**< [ 10: 10](R/W) When set, PKI hardware performs an (inner or outer) IPv4/IPv6 TCP/UDP/SCTP
                                                                 PKI_OPCODE_E::L4_LEN check when PKI_LTYPE(PKI_WQE_S[LFTY])_MAP[BELTYPE]
                                                                 equals any of PKI_BELTYPE_E::TCP,UDP,SCTP. PKI_WQE_S[LFPTR] points to the
                                                                 TCP/UDP/SCTP header in this case. In an IP-in-IP case, [LEN_LF] refers
                                                                 to the inner IPv4/IPv6 TCP/UDP/SCTP, else the outer/only IPv4/IPv6 TCP/UDP/SCTP.
                                                                 See PKI_WQE_S[ERRLEV,OPCODE] and PKI_ERRLEV_E::LF.

                                                                 Internal:
                                                                 Parse engine only passes along field LEN_LF, and doesn't otherwise use it. */
        uint64_t len_lg                : 1;  /**< [ 11: 11](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Parse engine only passes along field LEN_LG, and doesn't otherwise use it. */
        uint64_t tag_dst_lb            : 1;  /**< [ 12: 12](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Description from before when TAG_DST_LB became reserved:

                                                                 The parse engine must clear this bit if the BE is not to compute the tag, e.g. when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_dst_lc            : 1;  /**< [ 13: 13](R/W) When set, PKI hardware includes the outermost IPv4/IPv6 destination address
                                                                 in tuple tag generation when PKI_LTYPE(PKI_WQE_S[LCTY])_MAP[BELTYPE]
                                                                 equals either of PKI_BELTYPE_E::IP4,IP6. PKI_WQE_S[LCPTR] points to the
                                                                 IPv4/IPv6 header in this case. See PKI_WQE_S[TAG].

                                                                 Internal:
                                                                 The parse engine must clear this bit if the BE is not to compute the tag, e.g. when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_dst_ld            : 1;  /**< [ 14: 14](R/W) When set, PKI hardware includes the outer IPv4/IPv6 UDP destination port (in an
                                                                 IP-in-IP case) in tuple tag generation when PKI_LTYPE(PKI_WQE_S[LDTY])_MAP[BELTYPE]
                                                                 equals PKI_BELTYPE_E::UDP. PKI_WQE_S[LDPTR] points to the UDP header in this case.
                                                                 See PKI_WQE_S[TAG].

                                                                 Internal:
                                                                 The parse engine must clear this bit if the BE is not to compute the tag, e.g. when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_dst_le            : 1;  /**< [ 15: 15](R/W) When set, PKI hardware includes the inner IPv4/IPv6 destination address (in an
                                                                 IP-in-IP case) in tuple tag generation when PKI_LTYPE(PKI_WQE_S[LETY])_MAP[BELTYPE]
                                                                 equals either of PKI_BELTYPE_E::IP4,IP6. PKI_WQE_S[LEPTR] points to the inner
                                                                 IPv4/IPv6 header in this case. See PKI_WQE_S[TAG].

                                                                 Internal:
                                                                 The parse engine must clear this bit if the BE is not to compute the tag, e.g. when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_dst_lf            : 1;  /**< [ 16: 16](R/W) When set, PKI hardware includes the (inner or outer) IPv4/IPv6 TCP/UDP/SCTP
                                                                 destination port in tuple tag generation when PKI_LTYPE(PKI_WQE_S[LFTY])_MAP[BELTYPE]
                                                                 equals any of PKI_BELTYPE_E::TCP,UDP,SCTP. PKI_WQE_S[LFPTR] points to the
                                                                 TCP/UDP/SCTP header in this case. In an IP-in-IP case, [TAG_DST_LF] refers
                                                                 to the inner IPv4/IPv6 TCP/UDP/SCTP, else the outer/only IPv4/IPv6 TCP/UDP/SCTP.
                                                                 See PKI_WQE_S[TAG].

                                                                 Internal:
                                                                 The parse engine must clear this bit if the BE is not to compute the tag, e.g. when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_dst_lg            : 1;  /**< [ 17: 17](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Description from before when TAG_DST_LG became reserved:

                                                                 The parse engine must clear this bit if the BE is not to compute the tag, e.g. when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_src_lb            : 1;  /**< [ 18: 18](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Description from before when TAG_SRC_LB became reserved:

                                                                 The parse engine must clear this bit for PKI BE for TCP packets with SYN flag set
                                                                 and ACK flag clear when PKI_CL()_STYLE()_ALG[TAG_SYN] is set, or when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_src_lc            : 1;  /**< [ 19: 19](R/W) When set, PKI hardware includes the outermost IPv4/IPv6 source address
                                                                 in tuple tag generation when PKI_LTYPE(PKI_WQE_S[LCTY])_MAP[BELTYPE]
                                                                 equals either of PKI_BELTYPE_E::IP4,IP6. PKI_WQE_S[LCPTR] points to the
                                                                 IPv4/IPv6 header in this case. See PKI_WQE_S[TAG].

                                                                 Internal:
                                                                 The parse engine must clear this bit for PKI BE for TCP packets with SYN flag set
                                                                 and ACK flag clear when PKI_CL()_STYLE()_ALG[TAG_SYN] is set, or when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_src_ld            : 1;  /**< [ 20: 20](R/W) When set, PKI hardware includes the outer IPv4/IPv6 UDP source port (in an
                                                                 IP-in-IP case) in tuple tag generation when PKI_LTYPE(PKI_WQE_S[LDTY])_MAP[BELTYPE]
                                                                 equals PKI_BELTYPE_E::UDP. PKI_WQE_S[LDPTR] points to the UDP header in this case.
                                                                 See PKI_WQE_S[TAG].

                                                                 Internal:
                                                                 The parse engine must clear this bit for PKI BE for TCP packets with SYN flag set
                                                                 and ACK flag clear when PKI_CL()_STYLE()_ALG[TAG_SYN] is set, or when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_src_le            : 1;  /**< [ 21: 21](R/W) When set, PKI hardware includes the inner IPv4/IPv6 source address (in an
                                                                 IP-in-IP case) in tuple tag generation when PKI_LTYPE(PKI_WQE_S[LETY])_MAP[BELTYPE]
                                                                 equals either of PKI_BELTYPE_E::IP4,IP6. PKI_WQE_S[LEPTR] points to the inner
                                                                 IPv4/IPv6 header in this case. See PKI_WQE_S[TAG].

                                                                 Internal:
                                                                 The parse engine must clear this bit for PKI BE for TCP packets with SYN flag set
                                                                 and ACK flag clear when PKI_CL()_STYLE()_ALG[TAG_SYN] is set, or when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_src_lf            : 1;  /**< [ 22: 22](R/W) When set, PKI hardware includes the (inner or outer) IPv4/IPv6 TCP/UDP/SCTP
                                                                 source port in tuple tag generation when PKI_LTYPE(PKI_WQE_S[LFTY])_MAP[BELTYPE]
                                                                 equals any of PKI_BELTYPE_E::TCP,UDP,SCTP. PKI_WQE_S[LFPTR] points to the
                                                                 TCP/UDP/SCTP header in this case. In an IP-in-IP case, [TAG_SRC_LF] refers
                                                                 to the inner IPv4/IPv6 TCP/UDP/SCTP, else the outer/only IPv4/IPv6 TCP/UDP/SCTP.
                                                                 See PKI_WQE_S[TAG].

                                                                 Internal:
                                                                 The parse engine must clear this bit for PKI BE for TCP packets with SYN flag set
                                                                 and ACK flag clear when PKI_CL()_STYLE()_ALG[TAG_SYN] is set, or when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_src_lg            : 1;  /**< [ 23: 23](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Description from before when TAG_SRC_LG became reserved:

                                                                 The parse engine must clear this bit for PKI BE for TCP packets with SYN flag set
                                                                 and ACK flag clear when PKI_CL()_STYLE()_ALG[TAG_SYN] set, or when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t tag_masken            : 1;  /**< [ 24: 24](R/W) When set, apply PKI_STYLE()_TAG_MASK to computed tag. See PKI_WQE_S[TAG].
                                                                 Internal:
                                                                 The parse engine must clear this bit if the BE is not to compute the tag, e.g. when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t rsvdrw27              : 3;  /**< [ 27: 25](R/W) Reserved.
                                                                 Internal:
                                                                 Parse engine only passes along field RSVDRW27, and doesn't otherwise use it. */
        uint64_t tag_inc               : 4;  /**< [ 31: 28](R/W) Include masked tags using PKI_TAG_INC()_MASK. Each bit indicates to include the
                                                                 corresponding PKI_TAG_INC()_MASK range. See also PKI_TAG_INC()_CTL
                                                                 and PKI_WQE_S[TAG].

                                                                 Internal:
                                                                 The parse engine must clear these bits if the BE is not to compute the tag, e.g. when
                                                                 PKI_INST_HDR_S[UTAG] is set. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clx_stylex_cfg2_s cn; */
};
typedef union bdk_pki_clx_stylex_cfg2 bdk_pki_clx_stylex_cfg2_t;

static inline uint64_t BDK_PKI_CLX_STYLEX_CFG2(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLX_STYLEX_CFG2(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=1) && (b<=63)))
        return 0x86c000500800ll + 0x10000ll * ((a) & 0x1) + 8ll * ((b) & 0x3f);
    __bdk_csr_fatal("PKI_CLX_STYLEX_CFG2", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CLX_STYLEX_CFG2(a,b) bdk_pki_clx_stylex_cfg2_t
#define bustype_BDK_PKI_CLX_STYLEX_CFG2(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLX_STYLEX_CFG2(a,b) "PKI_CLX_STYLEX_CFG2"
#define device_bar_BDK_PKI_CLX_STYLEX_CFG2(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLX_STYLEX_CFG2(a,b) (a)
#define arguments_BDK_PKI_CLX_STYLEX_CFG2(a,b) (a),(b),-1,-1

/**
 * Register (NCB) pki_clken
 *
 * PKI Clock Enable Register
 */
union bdk_pki_clken
{
    uint64_t u;
    struct bdk_pki_clken_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t clken                 : 1;  /**< [  0:  0](R/W) Controls the conditional clocking within PKI.
                                                                 0 = Allow hardware to control the clocks.
                                                                 1 = Force the clocks to be always on. */
#else /* Word 0 - Little Endian */
        uint64_t clken                 : 1;  /**< [  0:  0](R/W) Controls the conditional clocking within PKI.
                                                                 0 = Allow hardware to control the clocks.
                                                                 1 = Force the clocks to be always on. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_clken_s cn; */
};
typedef union bdk_pki_clken bdk_pki_clken_t;

#define BDK_PKI_CLKEN BDK_PKI_CLKEN_FUNC()
static inline uint64_t BDK_PKI_CLKEN_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CLKEN_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000410ll;
    __bdk_csr_fatal("PKI_CLKEN", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CLKEN bdk_pki_clken_t
#define bustype_BDK_PKI_CLKEN BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CLKEN "PKI_CLKEN"
#define device_bar_BDK_PKI_CLKEN 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CLKEN 0
#define arguments_BDK_PKI_CLKEN -1,-1,-1,-1

/**
 * Register (NCB) pki_const
 *
 * PKI Constants Register
 * This register contains constants for software discovery.
 */
union bdk_pki_const
{
    uint64_t u;
    struct bdk_pki_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t fstyles               : 16; /**< [ 63: 48](RO) Number of final styles implemented. E.g. depth of PKI_STYLE()_WQ2. */
        uint64_t pknds                 : 16; /**< [ 47: 32](RO) Number of PKINDs implemented. */
        uint64_t bpid                  : 16; /**< [ 31: 16](RO) Number of BPIDs implemented. */
        uint64_t auras                 : 16; /**< [ 15:  0](RO) Number of auras implemented. */
#else /* Word 0 - Little Endian */
        uint64_t auras                 : 16; /**< [ 15:  0](RO) Number of auras implemented. */
        uint64_t bpid                  : 16; /**< [ 31: 16](RO) Number of BPIDs implemented. */
        uint64_t pknds                 : 16; /**< [ 47: 32](RO) Number of PKINDs implemented. */
        uint64_t fstyles               : 16; /**< [ 63: 48](RO) Number of final styles implemented. E.g. depth of PKI_STYLE()_WQ2. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_const_s cn; */
};
typedef union bdk_pki_const bdk_pki_const_t;

#define BDK_PKI_CONST BDK_PKI_CONST_FUNC()
static inline uint64_t BDK_PKI_CONST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CONST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000000ll;
    __bdk_csr_fatal("PKI_CONST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CONST bdk_pki_const_t
#define bustype_BDK_PKI_CONST BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CONST "PKI_CONST"
#define device_bar_BDK_PKI_CONST 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CONST 0
#define arguments_BDK_PKI_CONST -1,-1,-1,-1

/**
 * Register (NCB) pki_const1
 *
 * PKI Constants Register 1
 * This register contains constants for software discovery.
 */
union bdk_pki_const1
{
    uint64_t u;
    struct bdk_pki_const1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t pcams                 : 8;  /**< [ 23: 16](RO) Number of PCAMs per clusters. */
        uint64_t ipes                  : 8;  /**< [ 15:  8](RO) Number of IPEs per clusters. */
        uint64_t cls                   : 8;  /**< [  7:  0](RO) Number of clusters. */
#else /* Word 0 - Little Endian */
        uint64_t cls                   : 8;  /**< [  7:  0](RO) Number of clusters. */
        uint64_t ipes                  : 8;  /**< [ 15:  8](RO) Number of IPEs per clusters. */
        uint64_t pcams                 : 8;  /**< [ 23: 16](RO) Number of PCAMs per clusters. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_const1_s cn; */
};
typedef union bdk_pki_const1 bdk_pki_const1_t;

#define BDK_PKI_CONST1 BDK_PKI_CONST1_FUNC()
static inline uint64_t BDK_PKI_CONST1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CONST1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000008ll;
    __bdk_csr_fatal("PKI_CONST1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CONST1 bdk_pki_const1_t
#define bustype_BDK_PKI_CONST1 BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CONST1 "PKI_CONST1"
#define device_bar_BDK_PKI_CONST1 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CONST1 0
#define arguments_BDK_PKI_CONST1 -1,-1,-1,-1

/**
 * Register (NCB) pki_const2
 *
 * PKI Constants Register 2
 * This register contains constants for software discovery.
 */
union bdk_pki_const2
{
    uint64_t u;
    struct bdk_pki_const2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t stats                 : 16; /**< [ 63: 48](RO) Number of wide statistics. E.g. depth of PKI_STAT()_HIST0. */
        uint64_t dstats                : 16; /**< [ 47: 32](RO) Number of deep statistics. E.g. depth of PKI_DSTAT()_STAT0. */
        uint64_t qpgs                  : 16; /**< [ 31: 16](RO) Number of QPGs. E.g. depth of PKI_QPG_TBL(). */
        uint64_t pcam_ents             : 16; /**< [ 15:  0](RO) Number of PCAM entries per PCAM. E.g. depth of final index of PKI_CL()_PCAM()_MATCH(). */
#else /* Word 0 - Little Endian */
        uint64_t pcam_ents             : 16; /**< [ 15:  0](RO) Number of PCAM entries per PCAM. E.g. depth of final index of PKI_CL()_PCAM()_MATCH(). */
        uint64_t qpgs                  : 16; /**< [ 31: 16](RO) Number of QPGs. E.g. depth of PKI_QPG_TBL(). */
        uint64_t dstats                : 16; /**< [ 47: 32](RO) Number of deep statistics. E.g. depth of PKI_DSTAT()_STAT0. */
        uint64_t stats                 : 16; /**< [ 63: 48](RO) Number of wide statistics. E.g. depth of PKI_STAT()_HIST0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_const2_s cn; */
};
typedef union bdk_pki_const2 bdk_pki_const2_t;

#define BDK_PKI_CONST2 BDK_PKI_CONST2_FUNC()
static inline uint64_t BDK_PKI_CONST2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CONST2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000010ll;
    __bdk_csr_fatal("PKI_CONST2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CONST2 bdk_pki_const2_t
#define bustype_BDK_PKI_CONST2 BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CONST2 "PKI_CONST2"
#define device_bar_BDK_PKI_CONST2 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CONST2 0
#define arguments_BDK_PKI_CONST2 -1,-1,-1,-1

/**
 * Register (NCB) pki_const3
 *
 * PKI Constants Register 3
 * This register contains constants for software discovery.
 */
union bdk_pki_const3
{
    uint64_t u;
    struct bdk_pki_const3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_const3_s cn; */
};
typedef union bdk_pki_const3 bdk_pki_const3_t;

#define BDK_PKI_CONST3 BDK_PKI_CONST3_FUNC()
static inline uint64_t BDK_PKI_CONST3_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_CONST3_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000018ll;
    __bdk_csr_fatal("PKI_CONST3", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_CONST3 bdk_pki_const3_t
#define bustype_BDK_PKI_CONST3 BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_CONST3 "PKI_CONST3"
#define device_bar_BDK_PKI_CONST3 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_CONST3 0
#define arguments_BDK_PKI_CONST3 -1,-1,-1,-1

/**
 * Register (NCB) pki_dbg_crdts
 *
 * INTERNAL: PKI Credit Count Debug Register
 */
union bdk_pki_dbg_crdts
{
    uint64_t u;
    struct bdk_pki_dbg_crdts_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t x2p_crdts             : 6;  /**< [  5:  0](RO/H) PKI available credit counts that are not visible via OCLA debug. */
#else /* Word 0 - Little Endian */
        uint64_t x2p_crdts             : 6;  /**< [  5:  0](RO/H) PKI available credit counts that are not visible via OCLA debug. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_dbg_crdts_s cn; */
};
typedef union bdk_pki_dbg_crdts bdk_pki_dbg_crdts_t;

#define BDK_PKI_DBG_CRDTS BDK_PKI_DBG_CRDTS_FUNC()
static inline uint64_t BDK_PKI_DBG_CRDTS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_DBG_CRDTS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000fff090ll;
    __bdk_csr_fatal("PKI_DBG_CRDTS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_DBG_CRDTS bdk_pki_dbg_crdts_t
#define bustype_BDK_PKI_DBG_CRDTS BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_DBG_CRDTS "PKI_DBG_CRDTS"
#define device_bar_BDK_PKI_DBG_CRDTS 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_DBG_CRDTS 0
#define arguments_BDK_PKI_DBG_CRDTS -1,-1,-1,-1

/**
 * Register (NCB) pki_dstat#_stat0
 *
 * PKI Packets Deep Statistic Registers
 * This register contains statistics indexed by PKI_QPG_TBLB()[DSTAT_ID].
 */
union bdk_pki_dstatx_stat0
{
    uint64_t u;
    struct bdk_pki_dstatx_stat0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t pkts                  : 32; /**< [ 31:  0](R/W/H) Number of non-dropped packets processed by PKI.
                                                                 The corresponding wide statistic is PKI_STAT()_STAT0. */
#else /* Word 0 - Little Endian */
        uint64_t pkts                  : 32; /**< [ 31:  0](R/W/H) Number of non-dropped packets processed by PKI.
                                                                 The corresponding wide statistic is PKI_STAT()_STAT0. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_dstatx_stat0_s cn; */
};
typedef union bdk_pki_dstatx_stat0 bdk_pki_dstatx_stat0_t;

static inline uint64_t BDK_PKI_DSTATX_STAT0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_DSTATX_STAT0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1023))
        return 0x86c000c00000ll + 0x40ll * ((a) & 0x3ff);
    __bdk_csr_fatal("PKI_DSTATX_STAT0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_DSTATX_STAT0(a) bdk_pki_dstatx_stat0_t
#define bustype_BDK_PKI_DSTATX_STAT0(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_DSTATX_STAT0(a) "PKI_DSTATX_STAT0"
#define device_bar_BDK_PKI_DSTATX_STAT0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_DSTATX_STAT0(a) (a)
#define arguments_BDK_PKI_DSTATX_STAT0(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_dstat#_stat1
 *
 * PKI Octets Deep Statistic Registers
 * This register contains statistics indexed by PKI_QPG_TBLB()[DSTAT_ID].
 */
union bdk_pki_dstatx_stat1
{
    uint64_t u;
    struct bdk_pki_dstatx_stat1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t octs                  : 40; /**< [ 39:  0](R/W/H) Number of non-dropped octets received by PKI (good and bad).
                                                                 The corresponding wide statistic is PKI_STAT()_STAT1.
                                                                 The octet count reflects PKI_WQE_S[LEN]. */
#else /* Word 0 - Little Endian */
        uint64_t octs                  : 40; /**< [ 39:  0](R/W/H) Number of non-dropped octets received by PKI (good and bad).
                                                                 The corresponding wide statistic is PKI_STAT()_STAT1.
                                                                 The octet count reflects PKI_WQE_S[LEN]. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_dstatx_stat1_s cn; */
};
typedef union bdk_pki_dstatx_stat1 bdk_pki_dstatx_stat1_t;

static inline uint64_t BDK_PKI_DSTATX_STAT1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_DSTATX_STAT1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1023))
        return 0x86c000c00008ll + 0x40ll * ((a) & 0x3ff);
    __bdk_csr_fatal("PKI_DSTATX_STAT1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_DSTATX_STAT1(a) bdk_pki_dstatx_stat1_t
#define bustype_BDK_PKI_DSTATX_STAT1(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_DSTATX_STAT1(a) "PKI_DSTATX_STAT1"
#define device_bar_BDK_PKI_DSTATX_STAT1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_DSTATX_STAT1(a) (a)
#define arguments_BDK_PKI_DSTATX_STAT1(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_dstat#_stat2
 *
 * PKI Error Packets Deep Statistic Registers
 * This register contains statistics indexed by PKI_QPG_TBLB()[DSTAT_ID].
 */
union bdk_pki_dstatx_stat2
{
    uint64_t u;
    struct bdk_pki_dstatx_stat2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t err_pkts              : 32; /**< [ 31:  0](R/W/H) Number of packets with errors, including length \< minimum, length \> maximum, FCS
                                                                 errors, or PKI_WQE_S[ERRLEV] = RE or L2.
                                                                 This corresponds to a sum across the wide statistics PKI_STAT()_STAT7, PKI_STAT()_STAT7,
                                                                 PKI_STAT()_STAT8, PKI_STAT()_STAT9, PKI_STAT()_STAT10, PKI_STAT()_STAT11, and
                                                                 PKI_STAT()_STAT12. */
#else /* Word 0 - Little Endian */
        uint64_t err_pkts              : 32; /**< [ 31:  0](R/W/H) Number of packets with errors, including length \< minimum, length \> maximum, FCS
                                                                 errors, or PKI_WQE_S[ERRLEV] = RE or L2.
                                                                 This corresponds to a sum across the wide statistics PKI_STAT()_STAT7, PKI_STAT()_STAT7,
                                                                 PKI_STAT()_STAT8, PKI_STAT()_STAT9, PKI_STAT()_STAT10, PKI_STAT()_STAT11, and
                                                                 PKI_STAT()_STAT12. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_dstatx_stat2_s cn; */
};
typedef union bdk_pki_dstatx_stat2 bdk_pki_dstatx_stat2_t;

static inline uint64_t BDK_PKI_DSTATX_STAT2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_DSTATX_STAT2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1023))
        return 0x86c000c00010ll + 0x40ll * ((a) & 0x3ff);
    __bdk_csr_fatal("PKI_DSTATX_STAT2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_DSTATX_STAT2(a) bdk_pki_dstatx_stat2_t
#define bustype_BDK_PKI_DSTATX_STAT2(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_DSTATX_STAT2(a) "PKI_DSTATX_STAT2"
#define device_bar_BDK_PKI_DSTATX_STAT2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_DSTATX_STAT2(a) (a)
#define arguments_BDK_PKI_DSTATX_STAT2(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_dstat#_stat3
 *
 * PKI Dropped Packets Deep Statistic Registers
 * This register contains statistics indexed by PKI_QPG_TBLB()[DSTAT_ID].
 */
union bdk_pki_dstatx_stat3
{
    uint64_t u;
    struct bdk_pki_dstatx_stat3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t drp_pkts              : 32; /**< [ 31:  0](R/W/H) Inbound packets dropped by RED, buffer exhaustion, or PKI_CL()_STYLE()_CFG[DROP].
                                                                 The corresponding wide statistic is PKI_STAT()_STAT3. */
#else /* Word 0 - Little Endian */
        uint64_t drp_pkts              : 32; /**< [ 31:  0](R/W/H) Inbound packets dropped by RED, buffer exhaustion, or PKI_CL()_STYLE()_CFG[DROP].
                                                                 The corresponding wide statistic is PKI_STAT()_STAT3. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_dstatx_stat3_s cn; */
};
typedef union bdk_pki_dstatx_stat3 bdk_pki_dstatx_stat3_t;

static inline uint64_t BDK_PKI_DSTATX_STAT3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_DSTATX_STAT3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1023))
        return 0x86c000c00018ll + 0x40ll * ((a) & 0x3ff);
    __bdk_csr_fatal("PKI_DSTATX_STAT3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_DSTATX_STAT3(a) bdk_pki_dstatx_stat3_t
#define bustype_BDK_PKI_DSTATX_STAT3(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_DSTATX_STAT3(a) "PKI_DSTATX_STAT3"
#define device_bar_BDK_PKI_DSTATX_STAT3(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_DSTATX_STAT3(a) (a)
#define arguments_BDK_PKI_DSTATX_STAT3(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_dstat#_stat4
 *
 * PKI Dropped Octets Deep Statistic Registers
 * This register contains statistics indexed by PKI_QPG_TBLB()[DSTAT_ID].
 */
union bdk_pki_dstatx_stat4
{
    uint64_t u;
    struct bdk_pki_dstatx_stat4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t drp_octs              : 40; /**< [ 39:  0](R/W/H) Inbound octets dropped by RED, buffer exhaustion, or PKI_CL()_STYLE()_CFG[DROP].
                                                                 The corresponding wide statistic is PKI_STAT()_STAT4. */
#else /* Word 0 - Little Endian */
        uint64_t drp_octs              : 40; /**< [ 39:  0](R/W/H) Inbound octets dropped by RED, buffer exhaustion, or PKI_CL()_STYLE()_CFG[DROP].
                                                                 The corresponding wide statistic is PKI_STAT()_STAT4. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_dstatx_stat4_s cn; */
};
typedef union bdk_pki_dstatx_stat4 bdk_pki_dstatx_stat4_t;

static inline uint64_t BDK_PKI_DSTATX_STAT4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_DSTATX_STAT4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1023))
        return 0x86c000c00020ll + 0x40ll * ((a) & 0x3ff);
    __bdk_csr_fatal("PKI_DSTATX_STAT4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_DSTATX_STAT4(a) bdk_pki_dstatx_stat4_t
#define bustype_BDK_PKI_DSTATX_STAT4(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_DSTATX_STAT4(a) "PKI_DSTATX_STAT4"
#define device_bar_BDK_PKI_DSTATX_STAT4(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_DSTATX_STAT4(a) (a)
#define arguments_BDK_PKI_DSTATX_STAT4(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_ecc0_ctl
 *
 * PKI ECC 0 Control Register
 * This register allows inserting ECC errors for testing.
 */
union bdk_pki_ecc0_ctl
{
    uint64_t u;
    struct bdk_pki_ecc0_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t ldfif_flip            : 2;  /**< [ 23: 22](R/W) LDFIF RAM flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the LDFIF ram
                                                                 to test single-bit or double-bit error handling. */
        uint64_t ldfif_cdis            : 1;  /**< [ 21: 21](R/W) LDFIF RAM ECC correction disable. */
        uint64_t pbe_flip              : 2;  /**< [ 20: 19](R/W) PBE state RAM flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the PBE
                                                                 ram to test single-bit or double-bit error handling. */
        uint64_t pbe_cdis              : 1;  /**< [ 18: 18](R/W) PBE state RAM ECC correction disable. */
        uint64_t wadr_flip             : 2;  /**< [ 17: 16](R/W) WADR RAM flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the WADR ram
                                                                 to test single-bit or double-bit error handling. */
        uint64_t wadr_cdis             : 1;  /**< [ 15: 15](R/W) WADR RAM ECC correction disable. */
        uint64_t nxtptag_flip          : 2;  /**< [ 14: 13](R/W) NXTPTAG RAM flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the NXTPTAG
                                                                 ram to test single-bit or double-bit error handling. */
        uint64_t nxtptag_cdis          : 1;  /**< [ 12: 12](R/W) NXTPTAG RAM ECC correction disable. */
        uint64_t curptag_flip          : 2;  /**< [ 11: 10](R/W) CURPTAG RAM flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the CURPTAG
                                                                 ram to test single-bit or double-bit error handling. */
        uint64_t curptag_cdis          : 1;  /**< [  9:  9](R/W) CURPTAG RAM ECC correction disable. */
        uint64_t nxtblk_flip           : 2;  /**< [  8:  7](R/W) NXTBLK RAM flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the NXTBLK
                                                                 ram to test single-bit or double-bit error handling. */
        uint64_t nxtblk_cdis           : 1;  /**< [  6:  6](R/W) NXTBLK RAM ECC correction disable. */
        uint64_t kmem_flip             : 2;  /**< [  5:  4](R/W) KMEM RAM flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the KMEM ram
                                                                 to test single-bit or double-bit error handling. */
        uint64_t kmem_cdis             : 1;  /**< [  3:  3](R/W) KMEM RAM ECC correction disable. */
        uint64_t asm_flip              : 2;  /**< [  2:  1](R/W) ASM RAM flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the ASM ram to
                                                                 test single-bit or double-bit error handling. */
        uint64_t asm_cdis              : 1;  /**< [  0:  0](R/W) ASM RAM ECC correction disable. */
#else /* Word 0 - Little Endian */
        uint64_t asm_cdis              : 1;  /**< [  0:  0](R/W) ASM RAM ECC correction disable. */
        uint64_t asm_flip              : 2;  /**< [  2:  1](R/W) ASM RAM flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the ASM ram to
                                                                 test single-bit or double-bit error handling. */
        uint64_t kmem_cdis             : 1;  /**< [  3:  3](R/W) KMEM RAM ECC correction disable. */
        uint64_t kmem_flip             : 2;  /**< [  5:  4](R/W) KMEM RAM flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the KMEM ram
                                                                 to test single-bit or double-bit error handling. */
        uint64_t nxtblk_cdis           : 1;  /**< [  6:  6](R/W) NXTBLK RAM ECC correction disable. */
        uint64_t nxtblk_flip           : 2;  /**< [  8:  7](R/W) NXTBLK RAM flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the NXTBLK
                                                                 ram to test single-bit or double-bit error handling. */
        uint64_t curptag_cdis          : 1;  /**< [  9:  9](R/W) CURPTAG RAM ECC correction disable. */
        uint64_t curptag_flip          : 2;  /**< [ 11: 10](R/W) CURPTAG RAM flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the CURPTAG
                                                                 ram to test single-bit or double-bit error handling. */
        uint64_t nxtptag_cdis          : 1;  /**< [ 12: 12](R/W) NXTPTAG RAM ECC correction disable. */
        uint64_t nxtptag_flip          : 2;  /**< [ 14: 13](R/W) NXTPTAG RAM flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the NXTPTAG
                                                                 ram to test single-bit or double-bit error handling. */
        uint64_t wadr_cdis             : 1;  /**< [ 15: 15](R/W) WADR RAM ECC correction disable. */
        uint64_t wadr_flip             : 2;  /**< [ 17: 16](R/W) WADR RAM flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the WADR ram
                                                                 to test single-bit or double-bit error handling. */
        uint64_t pbe_cdis              : 1;  /**< [ 18: 18](R/W) PBE state RAM ECC correction disable. */
        uint64_t pbe_flip              : 2;  /**< [ 20: 19](R/W) PBE state RAM flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the PBE
                                                                 ram to test single-bit or double-bit error handling. */
        uint64_t ldfif_cdis            : 1;  /**< [ 21: 21](R/W) LDFIF RAM ECC correction disable. */
        uint64_t ldfif_flip            : 2;  /**< [ 23: 22](R/W) LDFIF RAM flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the LDFIF ram
                                                                 to test single-bit or double-bit error handling. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_ecc0_ctl_s cn; */
};
typedef union bdk_pki_ecc0_ctl bdk_pki_ecc0_ctl_t;

#define BDK_PKI_ECC0_CTL BDK_PKI_ECC0_CTL_FUNC()
static inline uint64_t BDK_PKI_ECC0_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ECC0_CTL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000060ll;
    __bdk_csr_fatal("PKI_ECC0_CTL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ECC0_CTL bdk_pki_ecc0_ctl_t
#define bustype_BDK_PKI_ECC0_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ECC0_CTL "PKI_ECC0_CTL"
#define device_bar_BDK_PKI_ECC0_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ECC0_CTL 0
#define arguments_BDK_PKI_ECC0_CTL -1,-1,-1,-1

/**
 * Register (NCB) pki_ecc0_int
 *
 * PKI ECC 0 Interrupt Register
 */
union bdk_pki_ecc0_int
{
    uint64_t u;
    struct bdk_pki_ecc0_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t ldfif_dbe             : 1;  /**< [ 15: 15](R/W1C/H) LDFIF ECC double-bit error. */
        uint64_t ldfif_sbe             : 1;  /**< [ 14: 14](R/W1C/H) LDFIF ECC single-bit error. */
        uint64_t pbe_dbe               : 1;  /**< [ 13: 13](R/W1C/H) PBE ECC double-bit error. */
        uint64_t pbe_sbe               : 1;  /**< [ 12: 12](R/W1C/H) PBE ECC single-bit error. */
        uint64_t wadr_dbe              : 1;  /**< [ 11: 11](R/W1C/H) WADR ECC double-bit error. */
        uint64_t wadr_sbe              : 1;  /**< [ 10: 10](R/W1C/H) WADR ECC single-bit error. */
        uint64_t nxtptag_dbe           : 1;  /**< [  9:  9](R/W1C/H) NXTPTAG ECC double-bit error. */
        uint64_t nxtptag_sbe           : 1;  /**< [  8:  8](R/W1C/H) NXTPTAG ECC single-bit error. */
        uint64_t curptag_dbe           : 1;  /**< [  7:  7](R/W1C/H) CURPTAG ECC double-bit error. */
        uint64_t curptag_sbe           : 1;  /**< [  6:  6](R/W1C/H) CURPTAG ECC single-bit error. */
        uint64_t nxtblk_dbe            : 1;  /**< [  5:  5](R/W1C/H) NXTBLK ECC double-bit error. */
        uint64_t nxtblk_sbe            : 1;  /**< [  4:  4](R/W1C/H) NXTBLK ECC single-bit error. */
        uint64_t kmem_dbe              : 1;  /**< [  3:  3](R/W1C/H) KMEM ECC double-bit error. If KMEM_DBE is
                                                                 thrown, software may scrub the error by reloading PKI_CL()_PKIND()_KMEM(). */
        uint64_t kmem_sbe              : 1;  /**< [  2:  2](R/W1C/H) KMEM ECC single-bit error. If KMEM_SBE is
                                                                 thrown, software may scrub the error by reloading PKI_CL()_PKIND()_KMEM(). */
        uint64_t asm_dbe               : 1;  /**< [  1:  1](R/W1C/H) ASM ECC double-bit error. */
        uint64_t asm_sbe               : 1;  /**< [  0:  0](R/W1C/H) ASM ECC single-bit error. */
#else /* Word 0 - Little Endian */
        uint64_t asm_sbe               : 1;  /**< [  0:  0](R/W1C/H) ASM ECC single-bit error. */
        uint64_t asm_dbe               : 1;  /**< [  1:  1](R/W1C/H) ASM ECC double-bit error. */
        uint64_t kmem_sbe              : 1;  /**< [  2:  2](R/W1C/H) KMEM ECC single-bit error. If KMEM_SBE is
                                                                 thrown, software may scrub the error by reloading PKI_CL()_PKIND()_KMEM(). */
        uint64_t kmem_dbe              : 1;  /**< [  3:  3](R/W1C/H) KMEM ECC double-bit error. If KMEM_DBE is
                                                                 thrown, software may scrub the error by reloading PKI_CL()_PKIND()_KMEM(). */
        uint64_t nxtblk_sbe            : 1;  /**< [  4:  4](R/W1C/H) NXTBLK ECC single-bit error. */
        uint64_t nxtblk_dbe            : 1;  /**< [  5:  5](R/W1C/H) NXTBLK ECC double-bit error. */
        uint64_t curptag_sbe           : 1;  /**< [  6:  6](R/W1C/H) CURPTAG ECC single-bit error. */
        uint64_t curptag_dbe           : 1;  /**< [  7:  7](R/W1C/H) CURPTAG ECC double-bit error. */
        uint64_t nxtptag_sbe           : 1;  /**< [  8:  8](R/W1C/H) NXTPTAG ECC single-bit error. */
        uint64_t nxtptag_dbe           : 1;  /**< [  9:  9](R/W1C/H) NXTPTAG ECC double-bit error. */
        uint64_t wadr_sbe              : 1;  /**< [ 10: 10](R/W1C/H) WADR ECC single-bit error. */
        uint64_t wadr_dbe              : 1;  /**< [ 11: 11](R/W1C/H) WADR ECC double-bit error. */
        uint64_t pbe_sbe               : 1;  /**< [ 12: 12](R/W1C/H) PBE ECC single-bit error. */
        uint64_t pbe_dbe               : 1;  /**< [ 13: 13](R/W1C/H) PBE ECC double-bit error. */
        uint64_t ldfif_sbe             : 1;  /**< [ 14: 14](R/W1C/H) LDFIF ECC single-bit error. */
        uint64_t ldfif_dbe             : 1;  /**< [ 15: 15](R/W1C/H) LDFIF ECC double-bit error. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_ecc0_int_s cn; */
};
typedef union bdk_pki_ecc0_int bdk_pki_ecc0_int_t;

#define BDK_PKI_ECC0_INT BDK_PKI_ECC0_INT_FUNC()
static inline uint64_t BDK_PKI_ECC0_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ECC0_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000840ll;
    __bdk_csr_fatal("PKI_ECC0_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ECC0_INT bdk_pki_ecc0_int_t
#define bustype_BDK_PKI_ECC0_INT BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ECC0_INT "PKI_ECC0_INT"
#define device_bar_BDK_PKI_ECC0_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ECC0_INT 0
#define arguments_BDK_PKI_ECC0_INT -1,-1,-1,-1

/**
 * Register (NCB) pki_ecc0_int_ena_w1c
 *
 * PKI ECC 0 Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_pki_ecc0_int_ena_w1c
{
    uint64_t u;
    struct bdk_pki_ecc0_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t ldfif_dbe             : 1;  /**< [ 15: 15](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[LDFIF_DBE]. */
        uint64_t ldfif_sbe             : 1;  /**< [ 14: 14](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[LDFIF_SBE]. */
        uint64_t pbe_dbe               : 1;  /**< [ 13: 13](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[PBE_DBE]. */
        uint64_t pbe_sbe               : 1;  /**< [ 12: 12](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[PBE_SBE]. */
        uint64_t wadr_dbe              : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[WADR_DBE]. */
        uint64_t wadr_sbe              : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[WADR_SBE]. */
        uint64_t nxtptag_dbe           : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[NXTPTAG_DBE]. */
        uint64_t nxtptag_sbe           : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[NXTPTAG_SBE]. */
        uint64_t curptag_dbe           : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[CURPTAG_DBE]. */
        uint64_t curptag_sbe           : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[CURPTAG_SBE]. */
        uint64_t nxtblk_dbe            : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[NXTBLK_DBE]. */
        uint64_t nxtblk_sbe            : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[NXTBLK_SBE]. */
        uint64_t kmem_dbe              : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[KMEM_DBE]. */
        uint64_t kmem_sbe              : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[KMEM_SBE]. */
        uint64_t asm_dbe               : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[ASM_DBE]. */
        uint64_t asm_sbe               : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[ASM_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t asm_sbe               : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[ASM_SBE]. */
        uint64_t asm_dbe               : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[ASM_DBE]. */
        uint64_t kmem_sbe              : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[KMEM_SBE]. */
        uint64_t kmem_dbe              : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[KMEM_DBE]. */
        uint64_t nxtblk_sbe            : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[NXTBLK_SBE]. */
        uint64_t nxtblk_dbe            : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[NXTBLK_DBE]. */
        uint64_t curptag_sbe           : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[CURPTAG_SBE]. */
        uint64_t curptag_dbe           : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[CURPTAG_DBE]. */
        uint64_t nxtptag_sbe           : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[NXTPTAG_SBE]. */
        uint64_t nxtptag_dbe           : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[NXTPTAG_DBE]. */
        uint64_t wadr_sbe              : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[WADR_SBE]. */
        uint64_t wadr_dbe              : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[WADR_DBE]. */
        uint64_t pbe_sbe               : 1;  /**< [ 12: 12](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[PBE_SBE]. */
        uint64_t pbe_dbe               : 1;  /**< [ 13: 13](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[PBE_DBE]. */
        uint64_t ldfif_sbe             : 1;  /**< [ 14: 14](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[LDFIF_SBE]. */
        uint64_t ldfif_dbe             : 1;  /**< [ 15: 15](R/W1C/H) Reads or clears enable for PKI_ECC0_INT[LDFIF_DBE]. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_ecc0_int_ena_w1c_s cn; */
};
typedef union bdk_pki_ecc0_int_ena_w1c bdk_pki_ecc0_int_ena_w1c_t;

#define BDK_PKI_ECC0_INT_ENA_W1C BDK_PKI_ECC0_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_PKI_ECC0_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ECC0_INT_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000860ll;
    __bdk_csr_fatal("PKI_ECC0_INT_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ECC0_INT_ENA_W1C bdk_pki_ecc0_int_ena_w1c_t
#define bustype_BDK_PKI_ECC0_INT_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ECC0_INT_ENA_W1C "PKI_ECC0_INT_ENA_W1C"
#define device_bar_BDK_PKI_ECC0_INT_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ECC0_INT_ENA_W1C 0
#define arguments_BDK_PKI_ECC0_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) pki_ecc0_int_ena_w1s
 *
 * PKI ECC 0 Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_pki_ecc0_int_ena_w1s
{
    uint64_t u;
    struct bdk_pki_ecc0_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t ldfif_dbe             : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[LDFIF_DBE]. */
        uint64_t ldfif_sbe             : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[LDFIF_SBE]. */
        uint64_t pbe_dbe               : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[PBE_DBE]. */
        uint64_t pbe_sbe               : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[PBE_SBE]. */
        uint64_t wadr_dbe              : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[WADR_DBE]. */
        uint64_t wadr_sbe              : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[WADR_SBE]. */
        uint64_t nxtptag_dbe           : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[NXTPTAG_DBE]. */
        uint64_t nxtptag_sbe           : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[NXTPTAG_SBE]. */
        uint64_t curptag_dbe           : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[CURPTAG_DBE]. */
        uint64_t curptag_sbe           : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[CURPTAG_SBE]. */
        uint64_t nxtblk_dbe            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[NXTBLK_DBE]. */
        uint64_t nxtblk_sbe            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[NXTBLK_SBE]. */
        uint64_t kmem_dbe              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[KMEM_DBE]. */
        uint64_t kmem_sbe              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[KMEM_SBE]. */
        uint64_t asm_dbe               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[ASM_DBE]. */
        uint64_t asm_sbe               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[ASM_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t asm_sbe               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[ASM_SBE]. */
        uint64_t asm_dbe               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[ASM_DBE]. */
        uint64_t kmem_sbe              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[KMEM_SBE]. */
        uint64_t kmem_dbe              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[KMEM_DBE]. */
        uint64_t nxtblk_sbe            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[NXTBLK_SBE]. */
        uint64_t nxtblk_dbe            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[NXTBLK_DBE]. */
        uint64_t curptag_sbe           : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[CURPTAG_SBE]. */
        uint64_t curptag_dbe           : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[CURPTAG_DBE]. */
        uint64_t nxtptag_sbe           : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[NXTPTAG_SBE]. */
        uint64_t nxtptag_dbe           : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[NXTPTAG_DBE]. */
        uint64_t wadr_sbe              : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[WADR_SBE]. */
        uint64_t wadr_dbe              : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[WADR_DBE]. */
        uint64_t pbe_sbe               : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[PBE_SBE]. */
        uint64_t pbe_dbe               : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[PBE_DBE]. */
        uint64_t ldfif_sbe             : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[LDFIF_SBE]. */
        uint64_t ldfif_dbe             : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets enable for PKI_ECC0_INT[LDFIF_DBE]. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_ecc0_int_ena_w1s_s cn; */
};
typedef union bdk_pki_ecc0_int_ena_w1s bdk_pki_ecc0_int_ena_w1s_t;

#define BDK_PKI_ECC0_INT_ENA_W1S BDK_PKI_ECC0_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_PKI_ECC0_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ECC0_INT_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000870ll;
    __bdk_csr_fatal("PKI_ECC0_INT_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ECC0_INT_ENA_W1S bdk_pki_ecc0_int_ena_w1s_t
#define bustype_BDK_PKI_ECC0_INT_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ECC0_INT_ENA_W1S "PKI_ECC0_INT_ENA_W1S"
#define device_bar_BDK_PKI_ECC0_INT_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ECC0_INT_ENA_W1S 0
#define arguments_BDK_PKI_ECC0_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) pki_ecc0_int_w1s
 *
 * PKI ECC 0 Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_pki_ecc0_int_w1s
{
    uint64_t u;
    struct bdk_pki_ecc0_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t ldfif_dbe             : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets PKI_ECC0_INT[LDFIF_DBE]. */
        uint64_t ldfif_sbe             : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets PKI_ECC0_INT[LDFIF_SBE]. */
        uint64_t pbe_dbe               : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets PKI_ECC0_INT[PBE_DBE]. */
        uint64_t pbe_sbe               : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets PKI_ECC0_INT[PBE_SBE]. */
        uint64_t wadr_dbe              : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets PKI_ECC0_INT[WADR_DBE]. */
        uint64_t wadr_sbe              : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets PKI_ECC0_INT[WADR_SBE]. */
        uint64_t nxtptag_dbe           : 1;  /**< [  9:  9](R/W1S/H) Reads or sets PKI_ECC0_INT[NXTPTAG_DBE]. */
        uint64_t nxtptag_sbe           : 1;  /**< [  8:  8](R/W1S/H) Reads or sets PKI_ECC0_INT[NXTPTAG_SBE]. */
        uint64_t curptag_dbe           : 1;  /**< [  7:  7](R/W1S/H) Reads or sets PKI_ECC0_INT[CURPTAG_DBE]. */
        uint64_t curptag_sbe           : 1;  /**< [  6:  6](R/W1S/H) Reads or sets PKI_ECC0_INT[CURPTAG_SBE]. */
        uint64_t nxtblk_dbe            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets PKI_ECC0_INT[NXTBLK_DBE]. */
        uint64_t nxtblk_sbe            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets PKI_ECC0_INT[NXTBLK_SBE]. */
        uint64_t kmem_dbe              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets PKI_ECC0_INT[KMEM_DBE]. */
        uint64_t kmem_sbe              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets PKI_ECC0_INT[KMEM_SBE]. */
        uint64_t asm_dbe               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets PKI_ECC0_INT[ASM_DBE]. */
        uint64_t asm_sbe               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets PKI_ECC0_INT[ASM_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t asm_sbe               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets PKI_ECC0_INT[ASM_SBE]. */
        uint64_t asm_dbe               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets PKI_ECC0_INT[ASM_DBE]. */
        uint64_t kmem_sbe              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets PKI_ECC0_INT[KMEM_SBE]. */
        uint64_t kmem_dbe              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets PKI_ECC0_INT[KMEM_DBE]. */
        uint64_t nxtblk_sbe            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets PKI_ECC0_INT[NXTBLK_SBE]. */
        uint64_t nxtblk_dbe            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets PKI_ECC0_INT[NXTBLK_DBE]. */
        uint64_t curptag_sbe           : 1;  /**< [  6:  6](R/W1S/H) Reads or sets PKI_ECC0_INT[CURPTAG_SBE]. */
        uint64_t curptag_dbe           : 1;  /**< [  7:  7](R/W1S/H) Reads or sets PKI_ECC0_INT[CURPTAG_DBE]. */
        uint64_t nxtptag_sbe           : 1;  /**< [  8:  8](R/W1S/H) Reads or sets PKI_ECC0_INT[NXTPTAG_SBE]. */
        uint64_t nxtptag_dbe           : 1;  /**< [  9:  9](R/W1S/H) Reads or sets PKI_ECC0_INT[NXTPTAG_DBE]. */
        uint64_t wadr_sbe              : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets PKI_ECC0_INT[WADR_SBE]. */
        uint64_t wadr_dbe              : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets PKI_ECC0_INT[WADR_DBE]. */
        uint64_t pbe_sbe               : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets PKI_ECC0_INT[PBE_SBE]. */
        uint64_t pbe_dbe               : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets PKI_ECC0_INT[PBE_DBE]. */
        uint64_t ldfif_sbe             : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets PKI_ECC0_INT[LDFIF_SBE]. */
        uint64_t ldfif_dbe             : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets PKI_ECC0_INT[LDFIF_DBE]. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_ecc0_int_w1s_s cn; */
};
typedef union bdk_pki_ecc0_int_w1s bdk_pki_ecc0_int_w1s_t;

#define BDK_PKI_ECC0_INT_W1S BDK_PKI_ECC0_INT_W1S_FUNC()
static inline uint64_t BDK_PKI_ECC0_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ECC0_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000850ll;
    __bdk_csr_fatal("PKI_ECC0_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ECC0_INT_W1S bdk_pki_ecc0_int_w1s_t
#define bustype_BDK_PKI_ECC0_INT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ECC0_INT_W1S "PKI_ECC0_INT_W1S"
#define device_bar_BDK_PKI_ECC0_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ECC0_INT_W1S 0
#define arguments_BDK_PKI_ECC0_INT_W1S -1,-1,-1,-1

/**
 * Register (NCB) pki_ecc1_ctl
 *
 * PKI ECC 1 Control Register
 * This register allows inserting ECC errors for testing.
 */
union bdk_pki_ecc1_ctl
{
    uint64_t u;
    struct bdk_pki_ecc1_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_57_63        : 7;
        uint64_t ncbwqe_flip           : 2;  /**< [ 56: 55](R/W) NCB WQE flip syndrome bits on write. */
        uint64_t ncbwqe_cdis           : 1;  /**< [ 54: 54](R/W) NCB WQE ECC correction disable. */
        uint64_t ncb_flip              : 2;  /**< [ 53: 52](R/W) NCB flip syndrome bits on write. */
        uint64_t ncb_cdis              : 1;  /**< [ 51: 51](R/W) NCB ECC correction disable. */
        uint64_t sws_flip              : 2;  /**< [ 50: 49](R/W) SWS flip syndrome bits on write. */
        uint64_t sws_cdis              : 1;  /**< [ 48: 48](R/W) SWS ECC correction disable. */
        uint64_t wqeout_flip           : 2;  /**< [ 47: 46](R/W) WQEOUT flip syndrome bits on write. */
        uint64_t wqeout_cdis           : 1;  /**< [ 45: 45](R/W) WQEOUT ECC correction disable. */
        uint64_t doa_flip              : 2;  /**< [ 44: 43](R/W) DOA flip syndrome bits on write. */
        uint64_t doa_cdis              : 1;  /**< [ 42: 42](R/W) DOA ECC correction disable. */
        uint64_t bpid_flip             : 2;  /**< [ 41: 40](R/W) BPID flip syndrome bits on write. */
        uint64_t bpid_cdis             : 1;  /**< [ 39: 39](R/W) BPID ECC correction disable. */
        uint64_t reserved_30_38        : 9;
        uint64_t plc_flip              : 2;  /**< [ 29: 28](R/W) PLC flip syndrome bits on write. */
        uint64_t plc_cdis              : 1;  /**< [ 27: 27](R/W) PLC ECC correction disable. */
        uint64_t pktwq_flip            : 2;  /**< [ 26: 25](R/W) PKTWQ flip syndrome bits on write. */
        uint64_t pktwq_cdis            : 1;  /**< [ 24: 24](R/W) PKTWQ ECC correction disable. */
        uint64_t strm_flip             : 2;  /**< [ 23: 22](R/W) STRM flip syndrome bits on write. */
        uint64_t strm_cdis             : 1;  /**< [ 21: 21](R/W) STRM ECC correction disable. */
        uint64_t stylewq2_flip         : 2;  /**< [ 20: 19](R/W) STYLEWQ2 flip syndrome bits on write. */
        uint64_t stylewq2_cdis         : 1;  /**< [ 18: 18](R/W) STYLEWQ2 ECC correction disable. */
        uint64_t tag_flip              : 2;  /**< [ 17: 16](R/W) TAG flip syndrome bits on write. */
        uint64_t tag_cdis              : 1;  /**< [ 15: 15](R/W) TAG ECC correction disable. */
        uint64_t reserved_12_14        : 3;
        uint64_t chan_flip             : 2;  /**< [ 11: 10](R/W) CHAN flip syndrome bits on write. */
        uint64_t chan_cdis             : 1;  /**< [  9:  9](R/W) CHAN ECC correction disable. */
        uint64_t pbtag_flip            : 2;  /**< [  8:  7](R/W) PBTAG flip syndrome bits on write. */
        uint64_t pbtag_cdis            : 1;  /**< [  6:  6](R/W) PBTAG ECC correction disable. */
        uint64_t stylewq_flip          : 2;  /**< [  5:  4](R/W) STYLEWQ flip syndrome bits on write. */
        uint64_t stylewq_cdis          : 1;  /**< [  3:  3](R/W) STYLEWQ ECC correction disable. */
        uint64_t qpg_flip              : 2;  /**< [  2:  1](R/W) QPG flip syndrome bits on write. */
        uint64_t qpg_cdis              : 1;  /**< [  0:  0](R/W) QPG ECC correction disable. */
#else /* Word 0 - Little Endian */
        uint64_t qpg_cdis              : 1;  /**< [  0:  0](R/W) QPG ECC correction disable. */
        uint64_t qpg_flip              : 2;  /**< [  2:  1](R/W) QPG flip syndrome bits on write. */
        uint64_t stylewq_cdis          : 1;  /**< [  3:  3](R/W) STYLEWQ ECC correction disable. */
        uint64_t stylewq_flip          : 2;  /**< [  5:  4](R/W) STYLEWQ flip syndrome bits on write. */
        uint64_t pbtag_cdis            : 1;  /**< [  6:  6](R/W) PBTAG ECC correction disable. */
        uint64_t pbtag_flip            : 2;  /**< [  8:  7](R/W) PBTAG flip syndrome bits on write. */
        uint64_t chan_cdis             : 1;  /**< [  9:  9](R/W) CHAN ECC correction disable. */
        uint64_t chan_flip             : 2;  /**< [ 11: 10](R/W) CHAN flip syndrome bits on write. */
        uint64_t reserved_12_14        : 3;
        uint64_t tag_cdis              : 1;  /**< [ 15: 15](R/W) TAG ECC correction disable. */
        uint64_t tag_flip              : 2;  /**< [ 17: 16](R/W) TAG flip syndrome bits on write. */
        uint64_t stylewq2_cdis         : 1;  /**< [ 18: 18](R/W) STYLEWQ2 ECC correction disable. */
        uint64_t stylewq2_flip         : 2;  /**< [ 20: 19](R/W) STYLEWQ2 flip syndrome bits on write. */
        uint64_t strm_cdis             : 1;  /**< [ 21: 21](R/W) STRM ECC correction disable. */
        uint64_t strm_flip             : 2;  /**< [ 23: 22](R/W) STRM flip syndrome bits on write. */
        uint64_t pktwq_cdis            : 1;  /**< [ 24: 24](R/W) PKTWQ ECC correction disable. */
        uint64_t pktwq_flip            : 2;  /**< [ 26: 25](R/W) PKTWQ flip syndrome bits on write. */
        uint64_t plc_cdis              : 1;  /**< [ 27: 27](R/W) PLC ECC correction disable. */
        uint64_t plc_flip              : 2;  /**< [ 29: 28](R/W) PLC flip syndrome bits on write. */
        uint64_t reserved_30_38        : 9;
        uint64_t bpid_cdis             : 1;  /**< [ 39: 39](R/W) BPID ECC correction disable. */
        uint64_t bpid_flip             : 2;  /**< [ 41: 40](R/W) BPID flip syndrome bits on write. */
        uint64_t doa_cdis              : 1;  /**< [ 42: 42](R/W) DOA ECC correction disable. */
        uint64_t doa_flip              : 2;  /**< [ 44: 43](R/W) DOA flip syndrome bits on write. */
        uint64_t wqeout_cdis           : 1;  /**< [ 45: 45](R/W) WQEOUT ECC correction disable. */
        uint64_t wqeout_flip           : 2;  /**< [ 47: 46](R/W) WQEOUT flip syndrome bits on write. */
        uint64_t sws_cdis              : 1;  /**< [ 48: 48](R/W) SWS ECC correction disable. */
        uint64_t sws_flip              : 2;  /**< [ 50: 49](R/W) SWS flip syndrome bits on write. */
        uint64_t ncb_cdis              : 1;  /**< [ 51: 51](R/W) NCB ECC correction disable. */
        uint64_t ncb_flip              : 2;  /**< [ 53: 52](R/W) NCB flip syndrome bits on write. */
        uint64_t ncbwqe_cdis           : 1;  /**< [ 54: 54](R/W) NCB WQE ECC correction disable. */
        uint64_t ncbwqe_flip           : 2;  /**< [ 56: 55](R/W) NCB WQE flip syndrome bits on write. */
        uint64_t reserved_57_63        : 7;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_ecc1_ctl_s cn; */
};
typedef union bdk_pki_ecc1_ctl bdk_pki_ecc1_ctl_t;

#define BDK_PKI_ECC1_CTL BDK_PKI_ECC1_CTL_FUNC()
static inline uint64_t BDK_PKI_ECC1_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ECC1_CTL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000068ll;
    __bdk_csr_fatal("PKI_ECC1_CTL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ECC1_CTL bdk_pki_ecc1_ctl_t
#define bustype_BDK_PKI_ECC1_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ECC1_CTL "PKI_ECC1_CTL"
#define device_bar_BDK_PKI_ECC1_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ECC1_CTL 0
#define arguments_BDK_PKI_ECC1_CTL -1,-1,-1,-1

/**
 * Register (NCB) pki_ecc1_int
 *
 * PKI ECC 1 Interrupt Register
 */
union bdk_pki_ecc1_int
{
    uint64_t u;
    struct bdk_pki_ecc1_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_38_63        : 26;
        uint64_t ncbwqe_dbe            : 1;  /**< [ 37: 37](R/W1C/H) NCB WQE HDR ECC double-bit error. */
        uint64_t ncbwqe_sbe            : 1;  /**< [ 36: 36](R/W1C/H) NCB WQE HDR ECC single-bit error. */
        uint64_t ncb_dbe               : 1;  /**< [ 35: 35](R/W1C/H) NCB MEM ECC double-bit error. */
        uint64_t ncb_sbe               : 1;  /**< [ 34: 34](R/W1C/H) NCB MEM ECC single-bit error. */
        uint64_t sws_dbe               : 1;  /**< [ 33: 33](R/W1C/H) PLC ECC double-bit error. */
        uint64_t sws_sbe               : 1;  /**< [ 32: 32](R/W1C/H) PLC ECC single-bit error. */
        uint64_t wqeout_dbe            : 1;  /**< [ 31: 31](R/W1C/H) PLC ECC double-bit error. */
        uint64_t wqeout_sbe            : 1;  /**< [ 30: 30](R/W1C/H) PLC ECC single-bit error. */
        uint64_t doa_dbe               : 1;  /**< [ 29: 29](R/W1C/H) PLC ECC double-bit error. */
        uint64_t doa_sbe               : 1;  /**< [ 28: 28](R/W1C/H) PLC ECC single-bit error. */
        uint64_t bpid_dbe              : 1;  /**< [ 27: 27](R/W1C/H) PLC ECC double-bit error. */
        uint64_t bpid_sbe              : 1;  /**< [ 26: 26](R/W1C/H) PLC ECC single-bit error. */
        uint64_t reserved_20_25        : 6;
        uint64_t plc_dbe               : 1;  /**< [ 19: 19](R/W1C/H) PLC ECC double-bit error. */
        uint64_t plc_sbe               : 1;  /**< [ 18: 18](R/W1C/H) PLC ECC single-bit error. */
        uint64_t pktwq_dbe             : 1;  /**< [ 17: 17](R/W1C/H) PKTWQ ECC double-bit error. */
        uint64_t pktwq_sbe             : 1;  /**< [ 16: 16](R/W1C/H) PKTWQ ECC single-bit error. */
        uint64_t reserved_14_15        : 2;
        uint64_t strm_dbe              : 1;  /**< [ 13: 13](R/W1C/H) STRM ECC double-bit error. */
        uint64_t strm_sbe              : 1;  /**< [ 12: 12](R/W1C/H) STRM ECC single-bit error. */
        uint64_t tag_dbe               : 1;  /**< [ 11: 11](R/W1C/H) TAG ECC double-bit error. */
        uint64_t tag_sbe               : 1;  /**< [ 10: 10](R/W1C/H) TAG ECC single-bit error. */
        uint64_t reserved_8_9          : 2;
        uint64_t chan_dbe              : 1;  /**< [  7:  7](R/W1C/H) CHAN ECC double-bit error. */
        uint64_t chan_sbe              : 1;  /**< [  6:  6](R/W1C/H) CHAN ECC single-bit error. */
        uint64_t pbtag_dbe             : 1;  /**< [  5:  5](R/W1C/H) PBTAG ECC double-bit error. */
        uint64_t pbtag_sbe             : 1;  /**< [  4:  4](R/W1C/H) PBTAG ECC single-bit error. */
        uint64_t stylewq_dbe           : 1;  /**< [  3:  3](R/W1C/H) STYLEWQ ECC double-bit error. */
        uint64_t stylewq_sbe           : 1;  /**< [  2:  2](R/W1C/H) STYLEWQ ECC single-bit error. */
        uint64_t qpg_dbe               : 1;  /**< [  1:  1](R/W1C/H) QPG ECC double-bit error. */
        uint64_t qpg_sbe               : 1;  /**< [  0:  0](R/W1C/H) QPG ECC single-bit error. */
#else /* Word 0 - Little Endian */
        uint64_t qpg_sbe               : 1;  /**< [  0:  0](R/W1C/H) QPG ECC single-bit error. */
        uint64_t qpg_dbe               : 1;  /**< [  1:  1](R/W1C/H) QPG ECC double-bit error. */
        uint64_t stylewq_sbe           : 1;  /**< [  2:  2](R/W1C/H) STYLEWQ ECC single-bit error. */
        uint64_t stylewq_dbe           : 1;  /**< [  3:  3](R/W1C/H) STYLEWQ ECC double-bit error. */
        uint64_t pbtag_sbe             : 1;  /**< [  4:  4](R/W1C/H) PBTAG ECC single-bit error. */
        uint64_t pbtag_dbe             : 1;  /**< [  5:  5](R/W1C/H) PBTAG ECC double-bit error. */
        uint64_t chan_sbe              : 1;  /**< [  6:  6](R/W1C/H) CHAN ECC single-bit error. */
        uint64_t chan_dbe              : 1;  /**< [  7:  7](R/W1C/H) CHAN ECC double-bit error. */
        uint64_t reserved_8_9          : 2;
        uint64_t tag_sbe               : 1;  /**< [ 10: 10](R/W1C/H) TAG ECC single-bit error. */
        uint64_t tag_dbe               : 1;  /**< [ 11: 11](R/W1C/H) TAG ECC double-bit error. */
        uint64_t strm_sbe              : 1;  /**< [ 12: 12](R/W1C/H) STRM ECC single-bit error. */
        uint64_t strm_dbe              : 1;  /**< [ 13: 13](R/W1C/H) STRM ECC double-bit error. */
        uint64_t reserved_14_15        : 2;
        uint64_t pktwq_sbe             : 1;  /**< [ 16: 16](R/W1C/H) PKTWQ ECC single-bit error. */
        uint64_t pktwq_dbe             : 1;  /**< [ 17: 17](R/W1C/H) PKTWQ ECC double-bit error. */
        uint64_t plc_sbe               : 1;  /**< [ 18: 18](R/W1C/H) PLC ECC single-bit error. */
        uint64_t plc_dbe               : 1;  /**< [ 19: 19](R/W1C/H) PLC ECC double-bit error. */
        uint64_t reserved_20_25        : 6;
        uint64_t bpid_sbe              : 1;  /**< [ 26: 26](R/W1C/H) PLC ECC single-bit error. */
        uint64_t bpid_dbe              : 1;  /**< [ 27: 27](R/W1C/H) PLC ECC double-bit error. */
        uint64_t doa_sbe               : 1;  /**< [ 28: 28](R/W1C/H) PLC ECC single-bit error. */
        uint64_t doa_dbe               : 1;  /**< [ 29: 29](R/W1C/H) PLC ECC double-bit error. */
        uint64_t wqeout_sbe            : 1;  /**< [ 30: 30](R/W1C/H) PLC ECC single-bit error. */
        uint64_t wqeout_dbe            : 1;  /**< [ 31: 31](R/W1C/H) PLC ECC double-bit error. */
        uint64_t sws_sbe               : 1;  /**< [ 32: 32](R/W1C/H) PLC ECC single-bit error. */
        uint64_t sws_dbe               : 1;  /**< [ 33: 33](R/W1C/H) PLC ECC double-bit error. */
        uint64_t ncb_sbe               : 1;  /**< [ 34: 34](R/W1C/H) NCB MEM ECC single-bit error. */
        uint64_t ncb_dbe               : 1;  /**< [ 35: 35](R/W1C/H) NCB MEM ECC double-bit error. */
        uint64_t ncbwqe_sbe            : 1;  /**< [ 36: 36](R/W1C/H) NCB WQE HDR ECC single-bit error. */
        uint64_t ncbwqe_dbe            : 1;  /**< [ 37: 37](R/W1C/H) NCB WQE HDR ECC double-bit error. */
        uint64_t reserved_38_63        : 26;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_ecc1_int_s cn; */
};
typedef union bdk_pki_ecc1_int bdk_pki_ecc1_int_t;

#define BDK_PKI_ECC1_INT BDK_PKI_ECC1_INT_FUNC()
static inline uint64_t BDK_PKI_ECC1_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ECC1_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000880ll;
    __bdk_csr_fatal("PKI_ECC1_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ECC1_INT bdk_pki_ecc1_int_t
#define bustype_BDK_PKI_ECC1_INT BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ECC1_INT "PKI_ECC1_INT"
#define device_bar_BDK_PKI_ECC1_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ECC1_INT 0
#define arguments_BDK_PKI_ECC1_INT -1,-1,-1,-1

/**
 * Register (NCB) pki_ecc1_int_ena_w1c
 *
 * PKI ECC 1 Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_pki_ecc1_int_ena_w1c
{
    uint64_t u;
    struct bdk_pki_ecc1_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_38_63        : 26;
        uint64_t ncbwqe_dbe            : 1;  /**< [ 37: 37](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[NCBWQE_DBE]. */
        uint64_t ncbwqe_sbe            : 1;  /**< [ 36: 36](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[NCBWQE_SBE]. */
        uint64_t ncb_dbe               : 1;  /**< [ 35: 35](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[NCB_DBE]. */
        uint64_t ncb_sbe               : 1;  /**< [ 34: 34](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[NCB_SBE]. */
        uint64_t sws_dbe               : 1;  /**< [ 33: 33](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[SWS_DBE]. */
        uint64_t sws_sbe               : 1;  /**< [ 32: 32](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[SWS_SBE]. */
        uint64_t wqeout_dbe            : 1;  /**< [ 31: 31](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[WQEOUT_DBE]. */
        uint64_t wqeout_sbe            : 1;  /**< [ 30: 30](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[WQEOUT_SBE]. */
        uint64_t doa_dbe               : 1;  /**< [ 29: 29](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[DOA_DBE]. */
        uint64_t doa_sbe               : 1;  /**< [ 28: 28](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[DOA_SBE]. */
        uint64_t bpid_dbe              : 1;  /**< [ 27: 27](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[BPID_DBE]. */
        uint64_t bpid_sbe              : 1;  /**< [ 26: 26](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[BPID_SBE]. */
        uint64_t reserved_20_25        : 6;
        uint64_t plc_dbe               : 1;  /**< [ 19: 19](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[PLC_DBE]. */
        uint64_t plc_sbe               : 1;  /**< [ 18: 18](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[PLC_SBE]. */
        uint64_t pktwq_dbe             : 1;  /**< [ 17: 17](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[PKTWQ_DBE]. */
        uint64_t pktwq_sbe             : 1;  /**< [ 16: 16](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[PKTWQ_SBE]. */
        uint64_t reserved_14_15        : 2;
        uint64_t strm_dbe              : 1;  /**< [ 13: 13](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[STRM_DBE]. */
        uint64_t strm_sbe              : 1;  /**< [ 12: 12](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[STRM_SBE]. */
        uint64_t tag_dbe               : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[TAG_DBE]. */
        uint64_t tag_sbe               : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[TAG_SBE]. */
        uint64_t reserved_8_9          : 2;
        uint64_t chan_dbe              : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[CHAN_DBE]. */
        uint64_t chan_sbe              : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[CHAN_SBE]. */
        uint64_t pbtag_dbe             : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[PBTAG_DBE]. */
        uint64_t pbtag_sbe             : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[PBTAG_SBE]. */
        uint64_t stylewq_dbe           : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[STYLEWQ_DBE]. */
        uint64_t stylewq_sbe           : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[STYLEWQ_SBE]. */
        uint64_t qpg_dbe               : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[QPG_DBE]. */
        uint64_t qpg_sbe               : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[QPG_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t qpg_sbe               : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[QPG_SBE]. */
        uint64_t qpg_dbe               : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[QPG_DBE]. */
        uint64_t stylewq_sbe           : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[STYLEWQ_SBE]. */
        uint64_t stylewq_dbe           : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[STYLEWQ_DBE]. */
        uint64_t pbtag_sbe             : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[PBTAG_SBE]. */
        uint64_t pbtag_dbe             : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[PBTAG_DBE]. */
        uint64_t chan_sbe              : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[CHAN_SBE]. */
        uint64_t chan_dbe              : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[CHAN_DBE]. */
        uint64_t reserved_8_9          : 2;
        uint64_t tag_sbe               : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[TAG_SBE]. */
        uint64_t tag_dbe               : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[TAG_DBE]. */
        uint64_t strm_sbe              : 1;  /**< [ 12: 12](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[STRM_SBE]. */
        uint64_t strm_dbe              : 1;  /**< [ 13: 13](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[STRM_DBE]. */
        uint64_t reserved_14_15        : 2;
        uint64_t pktwq_sbe             : 1;  /**< [ 16: 16](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[PKTWQ_SBE]. */
        uint64_t pktwq_dbe             : 1;  /**< [ 17: 17](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[PKTWQ_DBE]. */
        uint64_t plc_sbe               : 1;  /**< [ 18: 18](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[PLC_SBE]. */
        uint64_t plc_dbe               : 1;  /**< [ 19: 19](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[PLC_DBE]. */
        uint64_t reserved_20_25        : 6;
        uint64_t bpid_sbe              : 1;  /**< [ 26: 26](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[BPID_SBE]. */
        uint64_t bpid_dbe              : 1;  /**< [ 27: 27](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[BPID_DBE]. */
        uint64_t doa_sbe               : 1;  /**< [ 28: 28](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[DOA_SBE]. */
        uint64_t doa_dbe               : 1;  /**< [ 29: 29](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[DOA_DBE]. */
        uint64_t wqeout_sbe            : 1;  /**< [ 30: 30](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[WQEOUT_SBE]. */
        uint64_t wqeout_dbe            : 1;  /**< [ 31: 31](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[WQEOUT_DBE]. */
        uint64_t sws_sbe               : 1;  /**< [ 32: 32](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[SWS_SBE]. */
        uint64_t sws_dbe               : 1;  /**< [ 33: 33](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[SWS_DBE]. */
        uint64_t ncb_sbe               : 1;  /**< [ 34: 34](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[NCB_SBE]. */
        uint64_t ncb_dbe               : 1;  /**< [ 35: 35](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[NCB_DBE]. */
        uint64_t ncbwqe_sbe            : 1;  /**< [ 36: 36](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[NCBWQE_SBE]. */
        uint64_t ncbwqe_dbe            : 1;  /**< [ 37: 37](R/W1C/H) Reads or clears enable for PKI_ECC1_INT[NCBWQE_DBE]. */
        uint64_t reserved_38_63        : 26;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_ecc1_int_ena_w1c_s cn; */
};
typedef union bdk_pki_ecc1_int_ena_w1c bdk_pki_ecc1_int_ena_w1c_t;

#define BDK_PKI_ECC1_INT_ENA_W1C BDK_PKI_ECC1_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_PKI_ECC1_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ECC1_INT_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c0000008a0ll;
    __bdk_csr_fatal("PKI_ECC1_INT_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ECC1_INT_ENA_W1C bdk_pki_ecc1_int_ena_w1c_t
#define bustype_BDK_PKI_ECC1_INT_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ECC1_INT_ENA_W1C "PKI_ECC1_INT_ENA_W1C"
#define device_bar_BDK_PKI_ECC1_INT_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ECC1_INT_ENA_W1C 0
#define arguments_BDK_PKI_ECC1_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) pki_ecc1_int_ena_w1s
 *
 * PKI ECC 1 Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_pki_ecc1_int_ena_w1s
{
    uint64_t u;
    struct bdk_pki_ecc1_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_38_63        : 26;
        uint64_t ncbwqe_dbe            : 1;  /**< [ 37: 37](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[NCBWQE_DBE]. */
        uint64_t ncbwqe_sbe            : 1;  /**< [ 36: 36](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[NCBWQE_SBE]. */
        uint64_t ncb_dbe               : 1;  /**< [ 35: 35](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[NCB_DBE]. */
        uint64_t ncb_sbe               : 1;  /**< [ 34: 34](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[NCB_SBE]. */
        uint64_t sws_dbe               : 1;  /**< [ 33: 33](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[SWS_DBE]. */
        uint64_t sws_sbe               : 1;  /**< [ 32: 32](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[SWS_SBE]. */
        uint64_t wqeout_dbe            : 1;  /**< [ 31: 31](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[WQEOUT_DBE]. */
        uint64_t wqeout_sbe            : 1;  /**< [ 30: 30](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[WQEOUT_SBE]. */
        uint64_t doa_dbe               : 1;  /**< [ 29: 29](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[DOA_DBE]. */
        uint64_t doa_sbe               : 1;  /**< [ 28: 28](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[DOA_SBE]. */
        uint64_t bpid_dbe              : 1;  /**< [ 27: 27](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[BPID_DBE]. */
        uint64_t bpid_sbe              : 1;  /**< [ 26: 26](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[BPID_SBE]. */
        uint64_t reserved_20_25        : 6;
        uint64_t plc_dbe               : 1;  /**< [ 19: 19](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[PLC_DBE]. */
        uint64_t plc_sbe               : 1;  /**< [ 18: 18](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[PLC_SBE]. */
        uint64_t pktwq_dbe             : 1;  /**< [ 17: 17](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[PKTWQ_DBE]. */
        uint64_t pktwq_sbe             : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[PKTWQ_SBE]. */
        uint64_t reserved_14_15        : 2;
        uint64_t strm_dbe              : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[STRM_DBE]. */
        uint64_t strm_sbe              : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[STRM_SBE]. */
        uint64_t tag_dbe               : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[TAG_DBE]. */
        uint64_t tag_sbe               : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[TAG_SBE]. */
        uint64_t reserved_8_9          : 2;
        uint64_t chan_dbe              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[CHAN_DBE]. */
        uint64_t chan_sbe              : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[CHAN_SBE]. */
        uint64_t pbtag_dbe             : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[PBTAG_DBE]. */
        uint64_t pbtag_sbe             : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[PBTAG_SBE]. */
        uint64_t stylewq_dbe           : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[STYLEWQ_DBE]. */
        uint64_t stylewq_sbe           : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[STYLEWQ_SBE]. */
        uint64_t qpg_dbe               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[QPG_DBE]. */
        uint64_t qpg_sbe               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[QPG_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t qpg_sbe               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[QPG_SBE]. */
        uint64_t qpg_dbe               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[QPG_DBE]. */
        uint64_t stylewq_sbe           : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[STYLEWQ_SBE]. */
        uint64_t stylewq_dbe           : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[STYLEWQ_DBE]. */
        uint64_t pbtag_sbe             : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[PBTAG_SBE]. */
        uint64_t pbtag_dbe             : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[PBTAG_DBE]. */
        uint64_t chan_sbe              : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[CHAN_SBE]. */
        uint64_t chan_dbe              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[CHAN_DBE]. */
        uint64_t reserved_8_9          : 2;
        uint64_t tag_sbe               : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[TAG_SBE]. */
        uint64_t tag_dbe               : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[TAG_DBE]. */
        uint64_t strm_sbe              : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[STRM_SBE]. */
        uint64_t strm_dbe              : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[STRM_DBE]. */
        uint64_t reserved_14_15        : 2;
        uint64_t pktwq_sbe             : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[PKTWQ_SBE]. */
        uint64_t pktwq_dbe             : 1;  /**< [ 17: 17](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[PKTWQ_DBE]. */
        uint64_t plc_sbe               : 1;  /**< [ 18: 18](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[PLC_SBE]. */
        uint64_t plc_dbe               : 1;  /**< [ 19: 19](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[PLC_DBE]. */
        uint64_t reserved_20_25        : 6;
        uint64_t bpid_sbe              : 1;  /**< [ 26: 26](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[BPID_SBE]. */
        uint64_t bpid_dbe              : 1;  /**< [ 27: 27](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[BPID_DBE]. */
        uint64_t doa_sbe               : 1;  /**< [ 28: 28](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[DOA_SBE]. */
        uint64_t doa_dbe               : 1;  /**< [ 29: 29](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[DOA_DBE]. */
        uint64_t wqeout_sbe            : 1;  /**< [ 30: 30](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[WQEOUT_SBE]. */
        uint64_t wqeout_dbe            : 1;  /**< [ 31: 31](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[WQEOUT_DBE]. */
        uint64_t sws_sbe               : 1;  /**< [ 32: 32](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[SWS_SBE]. */
        uint64_t sws_dbe               : 1;  /**< [ 33: 33](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[SWS_DBE]. */
        uint64_t ncb_sbe               : 1;  /**< [ 34: 34](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[NCB_SBE]. */
        uint64_t ncb_dbe               : 1;  /**< [ 35: 35](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[NCB_DBE]. */
        uint64_t ncbwqe_sbe            : 1;  /**< [ 36: 36](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[NCBWQE_SBE]. */
        uint64_t ncbwqe_dbe            : 1;  /**< [ 37: 37](R/W1S/H) Reads or sets enable for PKI_ECC1_INT[NCBWQE_DBE]. */
        uint64_t reserved_38_63        : 26;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_ecc1_int_ena_w1s_s cn; */
};
typedef union bdk_pki_ecc1_int_ena_w1s bdk_pki_ecc1_int_ena_w1s_t;

#define BDK_PKI_ECC1_INT_ENA_W1S BDK_PKI_ECC1_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_PKI_ECC1_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ECC1_INT_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c0000008b0ll;
    __bdk_csr_fatal("PKI_ECC1_INT_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ECC1_INT_ENA_W1S bdk_pki_ecc1_int_ena_w1s_t
#define bustype_BDK_PKI_ECC1_INT_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ECC1_INT_ENA_W1S "PKI_ECC1_INT_ENA_W1S"
#define device_bar_BDK_PKI_ECC1_INT_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ECC1_INT_ENA_W1S 0
#define arguments_BDK_PKI_ECC1_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) pki_ecc1_int_w1s
 *
 * PKI ECC 1 Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_pki_ecc1_int_w1s
{
    uint64_t u;
    struct bdk_pki_ecc1_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_38_63        : 26;
        uint64_t ncbwqe_dbe            : 1;  /**< [ 37: 37](R/W1S/H) Reads or sets PKI_ECC1_INT[NCBWQE_DBE]. */
        uint64_t ncbwqe_sbe            : 1;  /**< [ 36: 36](R/W1S/H) Reads or sets PKI_ECC1_INT[NCBWQE_SBE]. */
        uint64_t ncb_dbe               : 1;  /**< [ 35: 35](R/W1S/H) Reads or sets PKI_ECC1_INT[NCB_DBE]. */
        uint64_t ncb_sbe               : 1;  /**< [ 34: 34](R/W1S/H) Reads or sets PKI_ECC1_INT[NCB_SBE]. */
        uint64_t sws_dbe               : 1;  /**< [ 33: 33](R/W1S/H) Reads or sets PKI_ECC1_INT[SWS_DBE]. */
        uint64_t sws_sbe               : 1;  /**< [ 32: 32](R/W1S/H) Reads or sets PKI_ECC1_INT[SWS_SBE]. */
        uint64_t wqeout_dbe            : 1;  /**< [ 31: 31](R/W1S/H) Reads or sets PKI_ECC1_INT[WQEOUT_DBE]. */
        uint64_t wqeout_sbe            : 1;  /**< [ 30: 30](R/W1S/H) Reads or sets PKI_ECC1_INT[WQEOUT_SBE]. */
        uint64_t doa_dbe               : 1;  /**< [ 29: 29](R/W1S/H) Reads or sets PKI_ECC1_INT[DOA_DBE]. */
        uint64_t doa_sbe               : 1;  /**< [ 28: 28](R/W1S/H) Reads or sets PKI_ECC1_INT[DOA_SBE]. */
        uint64_t bpid_dbe              : 1;  /**< [ 27: 27](R/W1S/H) Reads or sets PKI_ECC1_INT[BPID_DBE]. */
        uint64_t bpid_sbe              : 1;  /**< [ 26: 26](R/W1S/H) Reads or sets PKI_ECC1_INT[BPID_SBE]. */
        uint64_t reserved_20_25        : 6;
        uint64_t plc_dbe               : 1;  /**< [ 19: 19](R/W1S/H) Reads or sets PKI_ECC1_INT[PLC_DBE]. */
        uint64_t plc_sbe               : 1;  /**< [ 18: 18](R/W1S/H) Reads or sets PKI_ECC1_INT[PLC_SBE]. */
        uint64_t pktwq_dbe             : 1;  /**< [ 17: 17](R/W1S/H) Reads or sets PKI_ECC1_INT[PKTWQ_DBE]. */
        uint64_t pktwq_sbe             : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets PKI_ECC1_INT[PKTWQ_SBE]. */
        uint64_t reserved_14_15        : 2;
        uint64_t strm_dbe              : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets PKI_ECC1_INT[STRM_DBE]. */
        uint64_t strm_sbe              : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets PKI_ECC1_INT[STRM_SBE]. */
        uint64_t tag_dbe               : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets PKI_ECC1_INT[TAG_DBE]. */
        uint64_t tag_sbe               : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets PKI_ECC1_INT[TAG_SBE]. */
        uint64_t reserved_8_9          : 2;
        uint64_t chan_dbe              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets PKI_ECC1_INT[CHAN_DBE]. */
        uint64_t chan_sbe              : 1;  /**< [  6:  6](R/W1S/H) Reads or sets PKI_ECC1_INT[CHAN_SBE]. */
        uint64_t pbtag_dbe             : 1;  /**< [  5:  5](R/W1S/H) Reads or sets PKI_ECC1_INT[PBTAG_DBE]. */
        uint64_t pbtag_sbe             : 1;  /**< [  4:  4](R/W1S/H) Reads or sets PKI_ECC1_INT[PBTAG_SBE]. */
        uint64_t stylewq_dbe           : 1;  /**< [  3:  3](R/W1S/H) Reads or sets PKI_ECC1_INT[STYLEWQ_DBE]. */
        uint64_t stylewq_sbe           : 1;  /**< [  2:  2](R/W1S/H) Reads or sets PKI_ECC1_INT[STYLEWQ_SBE]. */
        uint64_t qpg_dbe               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets PKI_ECC1_INT[QPG_DBE]. */
        uint64_t qpg_sbe               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets PKI_ECC1_INT[QPG_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t qpg_sbe               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets PKI_ECC1_INT[QPG_SBE]. */
        uint64_t qpg_dbe               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets PKI_ECC1_INT[QPG_DBE]. */
        uint64_t stylewq_sbe           : 1;  /**< [  2:  2](R/W1S/H) Reads or sets PKI_ECC1_INT[STYLEWQ_SBE]. */
        uint64_t stylewq_dbe           : 1;  /**< [  3:  3](R/W1S/H) Reads or sets PKI_ECC1_INT[STYLEWQ_DBE]. */
        uint64_t pbtag_sbe             : 1;  /**< [  4:  4](R/W1S/H) Reads or sets PKI_ECC1_INT[PBTAG_SBE]. */
        uint64_t pbtag_dbe             : 1;  /**< [  5:  5](R/W1S/H) Reads or sets PKI_ECC1_INT[PBTAG_DBE]. */
        uint64_t chan_sbe              : 1;  /**< [  6:  6](R/W1S/H) Reads or sets PKI_ECC1_INT[CHAN_SBE]. */
        uint64_t chan_dbe              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets PKI_ECC1_INT[CHAN_DBE]. */
        uint64_t reserved_8_9          : 2;
        uint64_t tag_sbe               : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets PKI_ECC1_INT[TAG_SBE]. */
        uint64_t tag_dbe               : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets PKI_ECC1_INT[TAG_DBE]. */
        uint64_t strm_sbe              : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets PKI_ECC1_INT[STRM_SBE]. */
        uint64_t strm_dbe              : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets PKI_ECC1_INT[STRM_DBE]. */
        uint64_t reserved_14_15        : 2;
        uint64_t pktwq_sbe             : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets PKI_ECC1_INT[PKTWQ_SBE]. */
        uint64_t pktwq_dbe             : 1;  /**< [ 17: 17](R/W1S/H) Reads or sets PKI_ECC1_INT[PKTWQ_DBE]. */
        uint64_t plc_sbe               : 1;  /**< [ 18: 18](R/W1S/H) Reads or sets PKI_ECC1_INT[PLC_SBE]. */
        uint64_t plc_dbe               : 1;  /**< [ 19: 19](R/W1S/H) Reads or sets PKI_ECC1_INT[PLC_DBE]. */
        uint64_t reserved_20_25        : 6;
        uint64_t bpid_sbe              : 1;  /**< [ 26: 26](R/W1S/H) Reads or sets PKI_ECC1_INT[BPID_SBE]. */
        uint64_t bpid_dbe              : 1;  /**< [ 27: 27](R/W1S/H) Reads or sets PKI_ECC1_INT[BPID_DBE]. */
        uint64_t doa_sbe               : 1;  /**< [ 28: 28](R/W1S/H) Reads or sets PKI_ECC1_INT[DOA_SBE]. */
        uint64_t doa_dbe               : 1;  /**< [ 29: 29](R/W1S/H) Reads or sets PKI_ECC1_INT[DOA_DBE]. */
        uint64_t wqeout_sbe            : 1;  /**< [ 30: 30](R/W1S/H) Reads or sets PKI_ECC1_INT[WQEOUT_SBE]. */
        uint64_t wqeout_dbe            : 1;  /**< [ 31: 31](R/W1S/H) Reads or sets PKI_ECC1_INT[WQEOUT_DBE]. */
        uint64_t sws_sbe               : 1;  /**< [ 32: 32](R/W1S/H) Reads or sets PKI_ECC1_INT[SWS_SBE]. */
        uint64_t sws_dbe               : 1;  /**< [ 33: 33](R/W1S/H) Reads or sets PKI_ECC1_INT[SWS_DBE]. */
        uint64_t ncb_sbe               : 1;  /**< [ 34: 34](R/W1S/H) Reads or sets PKI_ECC1_INT[NCB_SBE]. */
        uint64_t ncb_dbe               : 1;  /**< [ 35: 35](R/W1S/H) Reads or sets PKI_ECC1_INT[NCB_DBE]. */
        uint64_t ncbwqe_sbe            : 1;  /**< [ 36: 36](R/W1S/H) Reads or sets PKI_ECC1_INT[NCBWQE_SBE]. */
        uint64_t ncbwqe_dbe            : 1;  /**< [ 37: 37](R/W1S/H) Reads or sets PKI_ECC1_INT[NCBWQE_DBE]. */
        uint64_t reserved_38_63        : 26;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_ecc1_int_w1s_s cn; */
};
typedef union bdk_pki_ecc1_int_w1s bdk_pki_ecc1_int_w1s_t;

#define BDK_PKI_ECC1_INT_W1S BDK_PKI_ECC1_INT_W1S_FUNC()
static inline uint64_t BDK_PKI_ECC1_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ECC1_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000890ll;
    __bdk_csr_fatal("PKI_ECC1_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ECC1_INT_W1S bdk_pki_ecc1_int_w1s_t
#define bustype_BDK_PKI_ECC1_INT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ECC1_INT_W1S "PKI_ECC1_INT_W1S"
#define device_bar_BDK_PKI_ECC1_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ECC1_INT_W1S 0
#define arguments_BDK_PKI_ECC1_INT_W1S -1,-1,-1,-1

/**
 * Register (NCB) pki_ecc2_ctl
 *
 * PKI ECC 2 Control Register
 * This register allows inserting ECC errors for testing.
 */
union bdk_pki_ecc2_ctl
{
    uint64_t u;
    struct bdk_pki_ecc2_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t imem_flip             : 2;  /**< [  2:  1](R/W) KMEM flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the KMEM ram to
                                                                 test single-bit or double-bit error handling. */
        uint64_t imem_cdis             : 1;  /**< [  0:  0](R/W) IMEM ECC correction disable. */
#else /* Word 0 - Little Endian */
        uint64_t imem_cdis             : 1;  /**< [  0:  0](R/W) IMEM ECC correction disable. */
        uint64_t imem_flip             : 2;  /**< [  2:  1](R/W) KMEM flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the KMEM ram to
                                                                 test single-bit or double-bit error handling. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_ecc2_ctl_s cn; */
};
typedef union bdk_pki_ecc2_ctl bdk_pki_ecc2_ctl_t;

#define BDK_PKI_ECC2_CTL BDK_PKI_ECC2_CTL_FUNC()
static inline uint64_t BDK_PKI_ECC2_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ECC2_CTL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000070ll;
    __bdk_csr_fatal("PKI_ECC2_CTL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ECC2_CTL bdk_pki_ecc2_ctl_t
#define bustype_BDK_PKI_ECC2_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ECC2_CTL "PKI_ECC2_CTL"
#define device_bar_BDK_PKI_ECC2_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ECC2_CTL 0
#define arguments_BDK_PKI_ECC2_CTL -1,-1,-1,-1

/**
 * Register (NCB) pki_ecc2_int
 *
 * PKI ECC 2 Interrupt Register
 */
union bdk_pki_ecc2_int
{
    uint64_t u;
    struct bdk_pki_ecc2_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t imem_dbe              : 1;  /**< [  1:  1](R/W1C/H) IMEM ECC double-bit error. If IMEM_DBE is
                                                                 thrown, software may scrub the error by reloading PKI_IMEM(). */
        uint64_t imem_sbe              : 1;  /**< [  0:  0](R/W1C/H) IMEM ECC single-bit error. If IMEM_SBE is
                                                                 thrown, software may scrub the error by reloading PKI_IMEM(). */
#else /* Word 0 - Little Endian */
        uint64_t imem_sbe              : 1;  /**< [  0:  0](R/W1C/H) IMEM ECC single-bit error. If IMEM_SBE is
                                                                 thrown, software may scrub the error by reloading PKI_IMEM(). */
        uint64_t imem_dbe              : 1;  /**< [  1:  1](R/W1C/H) IMEM ECC double-bit error. If IMEM_DBE is
                                                                 thrown, software may scrub the error by reloading PKI_IMEM(). */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_ecc2_int_s cn; */
};
typedef union bdk_pki_ecc2_int bdk_pki_ecc2_int_t;

#define BDK_PKI_ECC2_INT BDK_PKI_ECC2_INT_FUNC()
static inline uint64_t BDK_PKI_ECC2_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ECC2_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c0000008c0ll;
    __bdk_csr_fatal("PKI_ECC2_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ECC2_INT bdk_pki_ecc2_int_t
#define bustype_BDK_PKI_ECC2_INT BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ECC2_INT "PKI_ECC2_INT"
#define device_bar_BDK_PKI_ECC2_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ECC2_INT 0
#define arguments_BDK_PKI_ECC2_INT -1,-1,-1,-1

/**
 * Register (NCB) pki_ecc2_int_ena_w1c
 *
 * PKI ECC 2 Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_pki_ecc2_int_ena_w1c
{
    uint64_t u;
    struct bdk_pki_ecc2_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t imem_dbe              : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for PKI_ECC2_INT[IMEM_DBE]. */
        uint64_t imem_sbe              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for PKI_ECC2_INT[IMEM_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t imem_sbe              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for PKI_ECC2_INT[IMEM_SBE]. */
        uint64_t imem_dbe              : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for PKI_ECC2_INT[IMEM_DBE]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_ecc2_int_ena_w1c_s cn; */
};
typedef union bdk_pki_ecc2_int_ena_w1c bdk_pki_ecc2_int_ena_w1c_t;

#define BDK_PKI_ECC2_INT_ENA_W1C BDK_PKI_ECC2_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_PKI_ECC2_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ECC2_INT_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c0000008e0ll;
    __bdk_csr_fatal("PKI_ECC2_INT_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ECC2_INT_ENA_W1C bdk_pki_ecc2_int_ena_w1c_t
#define bustype_BDK_PKI_ECC2_INT_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ECC2_INT_ENA_W1C "PKI_ECC2_INT_ENA_W1C"
#define device_bar_BDK_PKI_ECC2_INT_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ECC2_INT_ENA_W1C 0
#define arguments_BDK_PKI_ECC2_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) pki_ecc2_int_ena_w1s
 *
 * PKI ECC 2 Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_pki_ecc2_int_ena_w1s
{
    uint64_t u;
    struct bdk_pki_ecc2_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t imem_dbe              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for PKI_ECC2_INT[IMEM_DBE]. */
        uint64_t imem_sbe              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for PKI_ECC2_INT[IMEM_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t imem_sbe              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for PKI_ECC2_INT[IMEM_SBE]. */
        uint64_t imem_dbe              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for PKI_ECC2_INT[IMEM_DBE]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_ecc2_int_ena_w1s_s cn; */
};
typedef union bdk_pki_ecc2_int_ena_w1s bdk_pki_ecc2_int_ena_w1s_t;

#define BDK_PKI_ECC2_INT_ENA_W1S BDK_PKI_ECC2_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_PKI_ECC2_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ECC2_INT_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c0000008f0ll;
    __bdk_csr_fatal("PKI_ECC2_INT_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ECC2_INT_ENA_W1S bdk_pki_ecc2_int_ena_w1s_t
#define bustype_BDK_PKI_ECC2_INT_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ECC2_INT_ENA_W1S "PKI_ECC2_INT_ENA_W1S"
#define device_bar_BDK_PKI_ECC2_INT_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ECC2_INT_ENA_W1S 0
#define arguments_BDK_PKI_ECC2_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) pki_ecc2_int_w1s
 *
 * PKI ECC 2 Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_pki_ecc2_int_w1s
{
    uint64_t u;
    struct bdk_pki_ecc2_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t imem_dbe              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets PKI_ECC2_INT[IMEM_DBE]. */
        uint64_t imem_sbe              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets PKI_ECC2_INT[IMEM_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t imem_sbe              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets PKI_ECC2_INT[IMEM_SBE]. */
        uint64_t imem_dbe              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets PKI_ECC2_INT[IMEM_DBE]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_ecc2_int_w1s_s cn; */
};
typedef union bdk_pki_ecc2_int_w1s bdk_pki_ecc2_int_w1s_t;

#define BDK_PKI_ECC2_INT_W1S BDK_PKI_ECC2_INT_W1S_FUNC()
static inline uint64_t BDK_PKI_ECC2_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ECC2_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c0000008d0ll;
    __bdk_csr_fatal("PKI_ECC2_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ECC2_INT_W1S bdk_pki_ecc2_int_w1s_t
#define bustype_BDK_PKI_ECC2_INT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ECC2_INT_W1S "PKI_ECC2_INT_W1S"
#define device_bar_BDK_PKI_ECC2_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ECC2_INT_W1S 0
#define arguments_BDK_PKI_ECC2_INT_W1S -1,-1,-1,-1

/**
 * Register (NCB) pki_frm_len_chk#
 *
 * PKI Frame Length Check Registers
 * Internal:
 * INTERNAL: This doesn't virtualize well, but we don't anticipate many sizes.
 */
union bdk_pki_frm_len_chkx
{
    uint64_t u;
    struct bdk_pki_frm_len_chkx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t maxlen                : 16; /**< [ 31: 16](R/W) Byte count for max-sized frame check. See PKI_CL()_STYLE()_CFG[MAXERR_EN,MINMAX_SEL],
                                                                 PKI_OPCODE_E::L2_OVERSIZE,L2_OVERRUN, PKI_ERRLEV_E::LA, and PKI_WQE_S[ERRLEV,OPCODE].

                                                                 When BGX()_SMU()_RX_FRM_CTL[PTP_MODE] is set, BGX adds an extra 8B timestamp onto
                                                                 the front of every packet sent to PKI. Thus, [MAXLEN] should be increased by 8
                                                                 when BGX()_SMU()_RX_FRM_CTL[PTP_MODE] is set. */
        uint64_t minlen                : 16; /**< [ 15:  0](R/W) Byte count for min-sized frame check. See PKI_CL()_STYLE()_CFG[MINERR_EN,MINMAX_SEL],
                                                                 PKI_OPCODE_E::L2_UNDERSIZE,L2_FRAGMENT, PKI_ERRLEV_E::LA, and PKI_WQE_S[ERRLEV,OPCODE].

                                                                 When BGX()_SMU()_RX_FRM_CTL[PTP_MODE] is set, BGX adds an extra 8B timestamp onto
                                                                 the front of every packet sent to PKI. Thus, [MINLEN] should be increased by 8
                                                                 when BGX()_SMU()_RX_FRM_CTL[PTP_MODE] is set. */
#else /* Word 0 - Little Endian */
        uint64_t minlen                : 16; /**< [ 15:  0](R/W) Byte count for min-sized frame check. See PKI_CL()_STYLE()_CFG[MINERR_EN,MINMAX_SEL],
                                                                 PKI_OPCODE_E::L2_UNDERSIZE,L2_FRAGMENT, PKI_ERRLEV_E::LA, and PKI_WQE_S[ERRLEV,OPCODE].

                                                                 When BGX()_SMU()_RX_FRM_CTL[PTP_MODE] is set, BGX adds an extra 8B timestamp onto
                                                                 the front of every packet sent to PKI. Thus, [MINLEN] should be increased by 8
                                                                 when BGX()_SMU()_RX_FRM_CTL[PTP_MODE] is set. */
        uint64_t maxlen                : 16; /**< [ 31: 16](R/W) Byte count for max-sized frame check. See PKI_CL()_STYLE()_CFG[MAXERR_EN,MINMAX_SEL],
                                                                 PKI_OPCODE_E::L2_OVERSIZE,L2_OVERRUN, PKI_ERRLEV_E::LA, and PKI_WQE_S[ERRLEV,OPCODE].

                                                                 When BGX()_SMU()_RX_FRM_CTL[PTP_MODE] is set, BGX adds an extra 8B timestamp onto
                                                                 the front of every packet sent to PKI. Thus, [MAXLEN] should be increased by 8
                                                                 when BGX()_SMU()_RX_FRM_CTL[PTP_MODE] is set. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_frm_len_chkx_s cn; */
};
typedef union bdk_pki_frm_len_chkx bdk_pki_frm_len_chkx_t;

static inline uint64_t BDK_PKI_FRM_LEN_CHKX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_FRM_LEN_CHKX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1))
        return 0x86c000004000ll + 8ll * ((a) & 0x1);
    __bdk_csr_fatal("PKI_FRM_LEN_CHKX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_FRM_LEN_CHKX(a) bdk_pki_frm_len_chkx_t
#define bustype_BDK_PKI_FRM_LEN_CHKX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_FRM_LEN_CHKX(a) "PKI_FRM_LEN_CHKX"
#define device_bar_BDK_PKI_FRM_LEN_CHKX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_FRM_LEN_CHKX(a) (a)
#define arguments_BDK_PKI_FRM_LEN_CHKX(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_gbl_pen
 *
 * INTERNAL: PKI Global Parser Enable Register
 *
 * This register contains global configuration information that applies to all
 * pkinds. The values are opaque to PKI HW.
 *
 * This is intended for communication between the higher-level software SDK, and the
 * SDK code that loads PKI_IMEM() with the parse engine code.  This allows the loader to
 * appropriately select the parse engine code with only those features required, so that
 * performance will be optimized.
 *
 * Internal:
 * This CSR has no direct hardware effect. It is for strictly for software use.
 */
union bdk_pki_gbl_pen
{
    uint64_t u;
    struct bdk_pki_gbl_pen_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t rsvdrw63              : 54; /**< [ 63: 10](R/W) Reserved. */
        uint64_t virt_pen              : 1;  /**< [  9:  9](R/W) Virtualization parsing enable.
                                                                 0 = VXLAN/VXLANGPE/NVGRE/GENEVE is never used in any style. This enables internal power
                                                                 and latency reductions.
                                                                 1 = VXLAN/VXLANGPE/NVGRE/GENEVE parsing may be used.

                                                                 See [L3_PEN] for supported [L3_PEN,VIRT_PEN,IL3_PEN,L4_PEN,CLG_PEN] combinations. */
        uint64_t clg_pen               : 1;  /**< [  8:  8](R/W) Custom LG parsing enable.
                                                                 0 = Custom LG is never used in any style; i.e. PKI_CL()_PKIND()_CFG[LG_CUSTOM_LAYER]
                                                                 is zero for all indices. This enables internal power and latency reductions.
                                                                 1 = Custom LG parsing may be used.

                                                                 See [L3_PEN] for supported [L3_PEN,VIRT_PEN,IL3_PEN,L4_PEN,CLG_PEN] combinations. */
        uint64_t cl2_pen               : 1;  /**< [  7:  7](R/W) Custom L2 parsing enable.
                                                                 0 = Custom L2 is never used in any style; i.e. PKI_CL()_PKIND()_L2_CUSTOM[VALID]
                                                                 is zero for all indices. This enables internal power and latency reductions.
                                                                 1 = Custom L2 parsing may be used. */
        uint64_t l4_pen                : 1;  /**< [  6:  6](R/W) L4 parsing enable.
                                                                 0 = L4 parsing is never used in any style. This enables internal power and latency
                                                                 reductions.
                                                                 1 = L4 parsing may be used.

                                                                 See [L3_PEN] for supported [L3_PEN], [VIRT_PEN], [IL3_PEN], [L4_PEN,CLG_PEN] combinations. */
        uint64_t il3_pen               : 1;  /**< [  5:  5](R/W) L3 inner parsing enable. Must be zero if L3_PEN is zero.
                                                                 0 = L3 inner parsing is never used in any style. This enables internal power and latency
                                                                 reductions.
                                                                 1 = L3 inner (IP-in-IP) parsing may be used.

                                                                 See [L3_PEN] for supported [L3_PEN], [VIRT_PEN], [IL3_PEN], [L4_PEN,CLG_PEN] combinations. */
        uint64_t l3_pen                : 1;  /**< [  4:  4](R/W) L3 parsing enable.
                                                                 0 = L3 parsing is never used in any style. This enables internal power and latency
                                                                 reductions.
                                                                 1 = L3 parsing may be used.

                                                                 The supported [L3_PEN], [VIRT_PEN], [IL3_PEN], [L4_PEN,CLG_PEN] combinations are:

                                                                 \<pre\>
                                                                 L3_PEN VIRT_PEN IL3_PEN L4_PEN CLG_PEN
                                                                 --------------------------------------
                                                                   1       1        1      1       1
                                                                   0       0        0      0       1
                                                                   0       0        0      0       0
                                                                 \</pre\> */
        uint64_t mpls_pen              : 1;  /**< [  3:  3](R/W) MPLS parsing enable.
                                                                 0 = MPLS parsing is never used in any style; i.e. PKI_CL()_PKIND()_CFG[MPLS_EN]
                                                                 is zero for all indices. This enables internal power and latency reductions.
                                                                 1 = MPLS parsing may be used. */
        uint64_t fulc_pen              : 1;  /**< [  2:  2](R/W) Fulcrum parsing enable.
                                                                 0 = Fulcrum parsing is never used in any style; i.e.
                                                                 PKI_CL()_PKIND()_CFG[FULC_EN] is zero for all indices. This enables internal
                                                                 power and latency reductions.
                                                                 1 = Fulcrum parsing may be used. */
        uint64_t dsa_pen               : 1;  /**< [  1:  1](R/W) DSA parsing enable. Must be zero if HG_PEN is set.
                                                                 0 = DSA parsing is never used in any style; i.e. PKI_CL()_PKIND()_CFG[DSA_EN] is
                                                                 zero for all indices. This enables internal power and latency reductions.
                                                                 1 = DSA parsing may be used. */
        uint64_t hg_pen                : 1;  /**< [  0:  0](R/W) HiGig parsing enable. Must be zero if DSA_PEN is set.
                                                                 0 = HiGig parsing is never used in any style; i.e. PKI_CL()_PKIND()_CFG[HG2_EN,
                                                                 HG_EN] are zero for all indices. This enables internal power and latency reductions.
                                                                 1 = HiGig parsing may be used. */
#else /* Word 0 - Little Endian */
        uint64_t hg_pen                : 1;  /**< [  0:  0](R/W) HiGig parsing enable. Must be zero if DSA_PEN is set.
                                                                 0 = HiGig parsing is never used in any style; i.e. PKI_CL()_PKIND()_CFG[HG2_EN,
                                                                 HG_EN] are zero for all indices. This enables internal power and latency reductions.
                                                                 1 = HiGig parsing may be used. */
        uint64_t dsa_pen               : 1;  /**< [  1:  1](R/W) DSA parsing enable. Must be zero if HG_PEN is set.
                                                                 0 = DSA parsing is never used in any style; i.e. PKI_CL()_PKIND()_CFG[DSA_EN] is
                                                                 zero for all indices. This enables internal power and latency reductions.
                                                                 1 = DSA parsing may be used. */
        uint64_t fulc_pen              : 1;  /**< [  2:  2](R/W) Fulcrum parsing enable.
                                                                 0 = Fulcrum parsing is never used in any style; i.e.
                                                                 PKI_CL()_PKIND()_CFG[FULC_EN] is zero for all indices. This enables internal
                                                                 power and latency reductions.
                                                                 1 = Fulcrum parsing may be used. */
        uint64_t mpls_pen              : 1;  /**< [  3:  3](R/W) MPLS parsing enable.
                                                                 0 = MPLS parsing is never used in any style; i.e. PKI_CL()_PKIND()_CFG[MPLS_EN]
                                                                 is zero for all indices. This enables internal power and latency reductions.
                                                                 1 = MPLS parsing may be used. */
        uint64_t l3_pen                : 1;  /**< [  4:  4](R/W) L3 parsing enable.
                                                                 0 = L3 parsing is never used in any style. This enables internal power and latency
                                                                 reductions.
                                                                 1 = L3 parsing may be used.

                                                                 The supported [L3_PEN], [VIRT_PEN], [IL3_PEN], [L4_PEN,CLG_PEN] combinations are:

                                                                 \<pre\>
                                                                 L3_PEN VIRT_PEN IL3_PEN L4_PEN CLG_PEN
                                                                 --------------------------------------
                                                                   1       1        1      1       1
                                                                   0       0        0      0       1
                                                                   0       0        0      0       0
                                                                 \</pre\> */
        uint64_t il3_pen               : 1;  /**< [  5:  5](R/W) L3 inner parsing enable. Must be zero if L3_PEN is zero.
                                                                 0 = L3 inner parsing is never used in any style. This enables internal power and latency
                                                                 reductions.
                                                                 1 = L3 inner (IP-in-IP) parsing may be used.

                                                                 See [L3_PEN] for supported [L3_PEN], [VIRT_PEN], [IL3_PEN], [L4_PEN,CLG_PEN] combinations. */
        uint64_t l4_pen                : 1;  /**< [  6:  6](R/W) L4 parsing enable.
                                                                 0 = L4 parsing is never used in any style. This enables internal power and latency
                                                                 reductions.
                                                                 1 = L4 parsing may be used.

                                                                 See [L3_PEN] for supported [L3_PEN], [VIRT_PEN], [IL3_PEN], [L4_PEN,CLG_PEN] combinations. */
        uint64_t cl2_pen               : 1;  /**< [  7:  7](R/W) Custom L2 parsing enable.
                                                                 0 = Custom L2 is never used in any style; i.e. PKI_CL()_PKIND()_L2_CUSTOM[VALID]
                                                                 is zero for all indices. This enables internal power and latency reductions.
                                                                 1 = Custom L2 parsing may be used. */
        uint64_t clg_pen               : 1;  /**< [  8:  8](R/W) Custom LG parsing enable.
                                                                 0 = Custom LG is never used in any style; i.e. PKI_CL()_PKIND()_CFG[LG_CUSTOM_LAYER]
                                                                 is zero for all indices. This enables internal power and latency reductions.
                                                                 1 = Custom LG parsing may be used.

                                                                 See [L3_PEN] for supported [L3_PEN,VIRT_PEN,IL3_PEN,L4_PEN,CLG_PEN] combinations. */
        uint64_t virt_pen              : 1;  /**< [  9:  9](R/W) Virtualization parsing enable.
                                                                 0 = VXLAN/VXLANGPE/NVGRE/GENEVE is never used in any style. This enables internal power
                                                                 and latency reductions.
                                                                 1 = VXLAN/VXLANGPE/NVGRE/GENEVE parsing may be used.

                                                                 See [L3_PEN] for supported [L3_PEN,VIRT_PEN,IL3_PEN,L4_PEN,CLG_PEN] combinations. */
        uint64_t rsvdrw63              : 54; /**< [ 63: 10](R/W) Reserved. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_gbl_pen_s cn; */
};
typedef union bdk_pki_gbl_pen bdk_pki_gbl_pen_t;

#define BDK_PKI_GBL_PEN BDK_PKI_GBL_PEN_FUNC()
static inline uint64_t BDK_PKI_GBL_PEN_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_GBL_PEN_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000200ll;
    __bdk_csr_fatal("PKI_GBL_PEN", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_GBL_PEN bdk_pki_gbl_pen_t
#define bustype_BDK_PKI_GBL_PEN BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_GBL_PEN "PKI_GBL_PEN"
#define device_bar_BDK_PKI_GBL_PEN 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_GBL_PEN 0
#define arguments_BDK_PKI_GBL_PEN -1,-1,-1,-1

/**
 * Register (NCB) pki_gen_int
 *
 * PKI General Interrupt Register
 */
union bdk_pki_gen_int
{
    uint64_t u;
    struct bdk_pki_gen_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t bufs_oflow            : 1;  /**< [  9:  9](R/W1C/H) Set when PKI receives a packet that exceeds 256 buffers. */
        uint64_t pkt_size_oflow        : 1;  /**< [  8:  8](R/W1C/H) Set when PKI receives a packet that exceeds 64 KB. */
        uint64_t x2p_req_ofl           : 1;  /**< [  7:  7](R/W1C/H) Set when a device attempts to have more than the allocated requests outstanding to PKI. */
        uint64_t drp_noavail           : 1;  /**< [  6:  6](R/W1C/H) Set when packet dropped due to no FPA pointers available for the aura the packet
                                                                 requested. */
        uint64_t dat                   : 1;  /**< [  5:  5](R/W1C/H) Set when data arrives before a SOP for the same reassembly ID for a packet. The first
                                                                 detected
                                                                 error associated with bits [DAT,SOP,EOP] of this register is only set here. A new bit can
                                                                 be set when the previous reported bit is cleared. */
        uint64_t eop                   : 1;  /**< [  4:  4](R/W1C/H) Set when an EOP is followed by an EOP for the same reassembly ID for a packet. The first
                                                                 detected error associated with bits [DAT,EOP,SOP] of this register is only set here. A new
                                                                 bit can be set when the previous reported bit is cleared. Also see PKI_PKT_ERR. */
        uint64_t sop                   : 1;  /**< [  3:  3](R/W1C/H) Set when a SOP is followed by an SOP for the same reassembly ID for a packet. The first
                                                                 detected error associated with bits [DAT,EOP,SOP] of this register is only set here. A new
                                                                 bit can be set when the previous reported bit is cleared. Also see PKI_PKT_ERR. */
        uint64_t bckprs                : 1;  /**< [  2:  2](R/W1C/H) PKI asserted backpressure. Set when PKI was unable to accept the next valid data from
                                                                 BGX/DPI/ILK etc. over X2P due to all internal resources being used up, and PKI will
                                                                 backpressure X2P. */
        uint64_t crcerr                : 1;  /**< [  1:  1](R/W1C/H) PKI calculated bad CRC in the L2 frame. */
        uint64_t pktdrp                : 1;  /**< [  0:  0](R/W1C/H) Packet dropped due to QOS. If the QOS algorithm decides to drop a packet, PKI asserts this
                                                                 interrupt. */
#else /* Word 0 - Little Endian */
        uint64_t pktdrp                : 1;  /**< [  0:  0](R/W1C/H) Packet dropped due to QOS. If the QOS algorithm decides to drop a packet, PKI asserts this
                                                                 interrupt. */
        uint64_t crcerr                : 1;  /**< [  1:  1](R/W1C/H) PKI calculated bad CRC in the L2 frame. */
        uint64_t bckprs                : 1;  /**< [  2:  2](R/W1C/H) PKI asserted backpressure. Set when PKI was unable to accept the next valid data from
                                                                 BGX/DPI/ILK etc. over X2P due to all internal resources being used up, and PKI will
                                                                 backpressure X2P. */
        uint64_t sop                   : 1;  /**< [  3:  3](R/W1C/H) Set when a SOP is followed by an SOP for the same reassembly ID for a packet. The first
                                                                 detected error associated with bits [DAT,EOP,SOP] of this register is only set here. A new
                                                                 bit can be set when the previous reported bit is cleared. Also see PKI_PKT_ERR. */
        uint64_t eop                   : 1;  /**< [  4:  4](R/W1C/H) Set when an EOP is followed by an EOP for the same reassembly ID for a packet. The first
                                                                 detected error associated with bits [DAT,EOP,SOP] of this register is only set here. A new
                                                                 bit can be set when the previous reported bit is cleared. Also see PKI_PKT_ERR. */
        uint64_t dat                   : 1;  /**< [  5:  5](R/W1C/H) Set when data arrives before a SOP for the same reassembly ID for a packet. The first
                                                                 detected
                                                                 error associated with bits [DAT,SOP,EOP] of this register is only set here. A new bit can
                                                                 be set when the previous reported bit is cleared. */
        uint64_t drp_noavail           : 1;  /**< [  6:  6](R/W1C/H) Set when packet dropped due to no FPA pointers available for the aura the packet
                                                                 requested. */
        uint64_t x2p_req_ofl           : 1;  /**< [  7:  7](R/W1C/H) Set when a device attempts to have more than the allocated requests outstanding to PKI. */
        uint64_t pkt_size_oflow        : 1;  /**< [  8:  8](R/W1C/H) Set when PKI receives a packet that exceeds 64 KB. */
        uint64_t bufs_oflow            : 1;  /**< [  9:  9](R/W1C/H) Set when PKI receives a packet that exceeds 256 buffers. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_gen_int_s cn; */
};
typedef union bdk_pki_gen_int bdk_pki_gen_int_t;

#define BDK_PKI_GEN_INT BDK_PKI_GEN_INT_FUNC()
static inline uint64_t BDK_PKI_GEN_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_GEN_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000800ll;
    __bdk_csr_fatal("PKI_GEN_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_GEN_INT bdk_pki_gen_int_t
#define bustype_BDK_PKI_GEN_INT BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_GEN_INT "PKI_GEN_INT"
#define device_bar_BDK_PKI_GEN_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_GEN_INT 0
#define arguments_BDK_PKI_GEN_INT -1,-1,-1,-1

/**
 * Register (NCB) pki_gen_int_ena_w1c
 *
 * PKI General Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_pki_gen_int_ena_w1c
{
    uint64_t u;
    struct bdk_pki_gen_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t bufs_oflow            : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for PKI_GEN_INT[BUFS_OFLOW]. */
        uint64_t pkt_size_oflow        : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for PKI_GEN_INT[PKT_SIZE_OFLOW]. */
        uint64_t x2p_req_ofl           : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for PKI_GEN_INT[X2P_REQ_OFL]. */
        uint64_t drp_noavail           : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for PKI_GEN_INT[DRP_NOAVAIL]. */
        uint64_t dat                   : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for PKI_GEN_INT[DAT]. */
        uint64_t eop                   : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for PKI_GEN_INT[EOP]. */
        uint64_t sop                   : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for PKI_GEN_INT[SOP]. */
        uint64_t bckprs                : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for PKI_GEN_INT[BCKPRS]. */
        uint64_t crcerr                : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for PKI_GEN_INT[CRCERR]. */
        uint64_t pktdrp                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for PKI_GEN_INT[PKTDRP]. */
#else /* Word 0 - Little Endian */
        uint64_t pktdrp                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for PKI_GEN_INT[PKTDRP]. */
        uint64_t crcerr                : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for PKI_GEN_INT[CRCERR]. */
        uint64_t bckprs                : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for PKI_GEN_INT[BCKPRS]. */
        uint64_t sop                   : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for PKI_GEN_INT[SOP]. */
        uint64_t eop                   : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for PKI_GEN_INT[EOP]. */
        uint64_t dat                   : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for PKI_GEN_INT[DAT]. */
        uint64_t drp_noavail           : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for PKI_GEN_INT[DRP_NOAVAIL]. */
        uint64_t x2p_req_ofl           : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for PKI_GEN_INT[X2P_REQ_OFL]. */
        uint64_t pkt_size_oflow        : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for PKI_GEN_INT[PKT_SIZE_OFLOW]. */
        uint64_t bufs_oflow            : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for PKI_GEN_INT[BUFS_OFLOW]. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_gen_int_ena_w1c_s cn; */
};
typedef union bdk_pki_gen_int_ena_w1c bdk_pki_gen_int_ena_w1c_t;

#define BDK_PKI_GEN_INT_ENA_W1C BDK_PKI_GEN_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_PKI_GEN_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_GEN_INT_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000820ll;
    __bdk_csr_fatal("PKI_GEN_INT_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_GEN_INT_ENA_W1C bdk_pki_gen_int_ena_w1c_t
#define bustype_BDK_PKI_GEN_INT_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_GEN_INT_ENA_W1C "PKI_GEN_INT_ENA_W1C"
#define device_bar_BDK_PKI_GEN_INT_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_GEN_INT_ENA_W1C 0
#define arguments_BDK_PKI_GEN_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) pki_gen_int_ena_w1s
 *
 * PKI General Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_pki_gen_int_ena_w1s
{
    uint64_t u;
    struct bdk_pki_gen_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t bufs_oflow            : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for PKI_GEN_INT[BUFS_OFLOW]. */
        uint64_t pkt_size_oflow        : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for PKI_GEN_INT[PKT_SIZE_OFLOW]. */
        uint64_t x2p_req_ofl           : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for PKI_GEN_INT[X2P_REQ_OFL]. */
        uint64_t drp_noavail           : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for PKI_GEN_INT[DRP_NOAVAIL]. */
        uint64_t dat                   : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for PKI_GEN_INT[DAT]. */
        uint64_t eop                   : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for PKI_GEN_INT[EOP]. */
        uint64_t sop                   : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for PKI_GEN_INT[SOP]. */
        uint64_t bckprs                : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for PKI_GEN_INT[BCKPRS]. */
        uint64_t crcerr                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for PKI_GEN_INT[CRCERR]. */
        uint64_t pktdrp                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for PKI_GEN_INT[PKTDRP]. */
#else /* Word 0 - Little Endian */
        uint64_t pktdrp                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for PKI_GEN_INT[PKTDRP]. */
        uint64_t crcerr                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for PKI_GEN_INT[CRCERR]. */
        uint64_t bckprs                : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for PKI_GEN_INT[BCKPRS]. */
        uint64_t sop                   : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for PKI_GEN_INT[SOP]. */
        uint64_t eop                   : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for PKI_GEN_INT[EOP]. */
        uint64_t dat                   : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for PKI_GEN_INT[DAT]. */
        uint64_t drp_noavail           : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for PKI_GEN_INT[DRP_NOAVAIL]. */
        uint64_t x2p_req_ofl           : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for PKI_GEN_INT[X2P_REQ_OFL]. */
        uint64_t pkt_size_oflow        : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for PKI_GEN_INT[PKT_SIZE_OFLOW]. */
        uint64_t bufs_oflow            : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for PKI_GEN_INT[BUFS_OFLOW]. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_gen_int_ena_w1s_s cn; */
};
typedef union bdk_pki_gen_int_ena_w1s bdk_pki_gen_int_ena_w1s_t;

#define BDK_PKI_GEN_INT_ENA_W1S BDK_PKI_GEN_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_PKI_GEN_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_GEN_INT_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000830ll;
    __bdk_csr_fatal("PKI_GEN_INT_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_GEN_INT_ENA_W1S bdk_pki_gen_int_ena_w1s_t
#define bustype_BDK_PKI_GEN_INT_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_GEN_INT_ENA_W1S "PKI_GEN_INT_ENA_W1S"
#define device_bar_BDK_PKI_GEN_INT_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_GEN_INT_ENA_W1S 0
#define arguments_BDK_PKI_GEN_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) pki_gen_int_w1s
 *
 * PKI General Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_pki_gen_int_w1s
{
    uint64_t u;
    struct bdk_pki_gen_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t bufs_oflow            : 1;  /**< [  9:  9](R/W1S/H) Reads or sets PKI_GEN_INT[BUFS_OFLOW]. */
        uint64_t pkt_size_oflow        : 1;  /**< [  8:  8](R/W1S/H) Reads or sets PKI_GEN_INT[PKT_SIZE_OFLOW]. */
        uint64_t x2p_req_ofl           : 1;  /**< [  7:  7](R/W1S/H) Reads or sets PKI_GEN_INT[X2P_REQ_OFL]. */
        uint64_t drp_noavail           : 1;  /**< [  6:  6](R/W1S/H) Reads or sets PKI_GEN_INT[DRP_NOAVAIL]. */
        uint64_t dat                   : 1;  /**< [  5:  5](R/W1S/H) Reads or sets PKI_GEN_INT[DAT]. */
        uint64_t eop                   : 1;  /**< [  4:  4](R/W1S/H) Reads or sets PKI_GEN_INT[EOP]. */
        uint64_t sop                   : 1;  /**< [  3:  3](R/W1S/H) Reads or sets PKI_GEN_INT[SOP]. */
        uint64_t bckprs                : 1;  /**< [  2:  2](R/W1S/H) Reads or sets PKI_GEN_INT[BCKPRS]. */
        uint64_t crcerr                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets PKI_GEN_INT[CRCERR]. */
        uint64_t pktdrp                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets PKI_GEN_INT[PKTDRP]. */
#else /* Word 0 - Little Endian */
        uint64_t pktdrp                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets PKI_GEN_INT[PKTDRP]. */
        uint64_t crcerr                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets PKI_GEN_INT[CRCERR]. */
        uint64_t bckprs                : 1;  /**< [  2:  2](R/W1S/H) Reads or sets PKI_GEN_INT[BCKPRS]. */
        uint64_t sop                   : 1;  /**< [  3:  3](R/W1S/H) Reads or sets PKI_GEN_INT[SOP]. */
        uint64_t eop                   : 1;  /**< [  4:  4](R/W1S/H) Reads or sets PKI_GEN_INT[EOP]. */
        uint64_t dat                   : 1;  /**< [  5:  5](R/W1S/H) Reads or sets PKI_GEN_INT[DAT]. */
        uint64_t drp_noavail           : 1;  /**< [  6:  6](R/W1S/H) Reads or sets PKI_GEN_INT[DRP_NOAVAIL]. */
        uint64_t x2p_req_ofl           : 1;  /**< [  7:  7](R/W1S/H) Reads or sets PKI_GEN_INT[X2P_REQ_OFL]. */
        uint64_t pkt_size_oflow        : 1;  /**< [  8:  8](R/W1S/H) Reads or sets PKI_GEN_INT[PKT_SIZE_OFLOW]. */
        uint64_t bufs_oflow            : 1;  /**< [  9:  9](R/W1S/H) Reads or sets PKI_GEN_INT[BUFS_OFLOW]. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_gen_int_w1s_s cn; */
};
typedef union bdk_pki_gen_int_w1s bdk_pki_gen_int_w1s_t;

#define BDK_PKI_GEN_INT_W1S BDK_PKI_GEN_INT_W1S_FUNC()
static inline uint64_t BDK_PKI_GEN_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_GEN_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000810ll;
    __bdk_csr_fatal("PKI_GEN_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_GEN_INT_W1S bdk_pki_gen_int_w1s_t
#define bustype_BDK_PKI_GEN_INT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_GEN_INT_W1S "PKI_GEN_INT_W1S"
#define device_bar_BDK_PKI_GEN_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_GEN_INT_W1S 0
#define arguments_BDK_PKI_GEN_INT_W1S -1,-1,-1,-1

/**
 * Register (NCB) pki_icg#_cfg
 *
 * PKI Cluster Group Control Register
 * This register configures the cluster group.
 */
union bdk_pki_icgx_cfg
{
    uint64_t u;
    struct bdk_pki_icgx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t maxipe_use            : 5;  /**< [ 52: 48](R/W) Reserved. Must be 0x14.
                                                                 Internal:
                                                                 Maximum number of IPEs to use in each cluster for this ICG. For diagnostic use
                                                                 only. Allows reducing the number of IPEs available for debug, characterization,
                                                                 repair, etc. Must be between 1 and PKI_CONST1[IPES] (20). Normally, PKI will
                                                                 have all 20 IPEs available in a cluster for packet processing, other values will
                                                                 decrease performance. */
        uint64_t reserved_36_47        : 12;
        uint64_t clusters              : 4;  /**< [ 35: 32](R/W) Bit-mask of clusters in this cluster group. A given cluster can only be enabled
                                                                 in a single cluster group. Behavior is undefined for an ICG which receives
                                                                 traffic with a [CLUSTERS] of 0x0. ICG(0)'s entry resets to 0x3, all other
                                                                 entries to 0x0. Valid values of [CLUSTERS] are 0x0-0x3. */
        uint64_t reserved_27_31        : 5;
        uint64_t release_rqd           : 1;  /**< [ 26: 26](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Release required. For diagnostic use only.
                                                                 0 = Release of r64 to r95 will occur immediately, no release microop is needed.
                                                                 1 = Release will wait until release microop executes. */
        uint64_t mlo                   : 1;  /**< [ 25: 25](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Memory low bypass enable. For diagnostic use only.
                                                                 0 = KMEM specifies contents of r48 to r63. The parse engine code expects this setting.
                                                                 1 = KMEM specifies contents of r32 to r47. This may be desirable when PKIENA=0 to allow
                                                                 direct control over the back end. */
        uint64_t pena                  : 1;  /**< [ 24: 24](R/W) Parse enable. Must be set after PKI has been initialized and PKI_IMEM() loaded.
                                                                 0 = IPE transitions from start directly to done without executing a sequence, and the KMEM
                                                                 bits effectively are copied through to the WQ.
                                                                 1 = Normal parse engine operation. */
        uint64_t timer                 : 12; /**< [ 23: 12](RO/H) Current hold-off timer. Enables even spreading of cluster utilization over time;
                                                                 while [TIMER] is nonzero, a cluster in this group will not start parsing. When a
                                                                 cluster in this group starts parsing, [TIMER] is set to [DELAY], and decrements
                                                                 every coprocessor-clock. [TIMER] is zeroed if all clusters in this group are
                                                                 idle. */
        uint64_t delay                 : 12; /**< [ 11:  0](R/W) Delay between cluster starts, as described under [TIMER]. If 0x0, a cluster can
                                                                 start at any time relative to other clusters. [DELAY] should typically be
                                                                 the average observed parser latency by loading with the parsing
                                                                 delay divided by the number of clusters in this cluster group which will
                                                                 typically be 800 divided by the population count of [CLUSTERS]
                                                                 (800/PKI_CONST1[CLS]). The smallest useful nonzero value is 0xA0,
                                                                 corresponding to the minimum number of cycles needed to fill one cluster with
                                                                 packets.

                                                                 Internal:
                                                                 The number 800 above was chosen as a typical production parse engine code
                                                                 length with some additional instruction growth. */
#else /* Word 0 - Little Endian */
        uint64_t delay                 : 12; /**< [ 11:  0](R/W) Delay between cluster starts, as described under [TIMER]. If 0x0, a cluster can
                                                                 start at any time relative to other clusters. [DELAY] should typically be
                                                                 the average observed parser latency by loading with the parsing
                                                                 delay divided by the number of clusters in this cluster group which will
                                                                 typically be 800 divided by the population count of [CLUSTERS]
                                                                 (800/PKI_CONST1[CLS]). The smallest useful nonzero value is 0xA0,
                                                                 corresponding to the minimum number of cycles needed to fill one cluster with
                                                                 packets.

                                                                 Internal:
                                                                 The number 800 above was chosen as a typical production parse engine code
                                                                 length with some additional instruction growth. */
        uint64_t timer                 : 12; /**< [ 23: 12](RO/H) Current hold-off timer. Enables even spreading of cluster utilization over time;
                                                                 while [TIMER] is nonzero, a cluster in this group will not start parsing. When a
                                                                 cluster in this group starts parsing, [TIMER] is set to [DELAY], and decrements
                                                                 every coprocessor-clock. [TIMER] is zeroed if all clusters in this group are
                                                                 idle. */
        uint64_t pena                  : 1;  /**< [ 24: 24](R/W) Parse enable. Must be set after PKI has been initialized and PKI_IMEM() loaded.
                                                                 0 = IPE transitions from start directly to done without executing a sequence, and the KMEM
                                                                 bits effectively are copied through to the WQ.
                                                                 1 = Normal parse engine operation. */
        uint64_t mlo                   : 1;  /**< [ 25: 25](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Memory low bypass enable. For diagnostic use only.
                                                                 0 = KMEM specifies contents of r48 to r63. The parse engine code expects this setting.
                                                                 1 = KMEM specifies contents of r32 to r47. This may be desirable when PKIENA=0 to allow
                                                                 direct control over the back end. */
        uint64_t release_rqd           : 1;  /**< [ 26: 26](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Release required. For diagnostic use only.
                                                                 0 = Release of r64 to r95 will occur immediately, no release microop is needed.
                                                                 1 = Release will wait until release microop executes. */
        uint64_t reserved_27_31        : 5;
        uint64_t clusters              : 4;  /**< [ 35: 32](R/W) Bit-mask of clusters in this cluster group. A given cluster can only be enabled
                                                                 in a single cluster group. Behavior is undefined for an ICG which receives
                                                                 traffic with a [CLUSTERS] of 0x0. ICG(0)'s entry resets to 0x3, all other
                                                                 entries to 0x0. Valid values of [CLUSTERS] are 0x0-0x3. */
        uint64_t reserved_36_47        : 12;
        uint64_t maxipe_use            : 5;  /**< [ 52: 48](R/W) Reserved. Must be 0x14.
                                                                 Internal:
                                                                 Maximum number of IPEs to use in each cluster for this ICG. For diagnostic use
                                                                 only. Allows reducing the number of IPEs available for debug, characterization,
                                                                 repair, etc. Must be between 1 and PKI_CONST1[IPES] (20). Normally, PKI will
                                                                 have all 20 IPEs available in a cluster for packet processing, other values will
                                                                 decrease performance. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_icgx_cfg_s cn; */
};
typedef union bdk_pki_icgx_cfg bdk_pki_icgx_cfg_t;

static inline uint64_t BDK_PKI_ICGX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_ICGX_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x86c00000a000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("PKI_ICGX_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_ICGX_CFG(a) bdk_pki_icgx_cfg_t
#define bustype_BDK_PKI_ICGX_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_ICGX_CFG(a) "PKI_ICGX_CFG"
#define device_bar_BDK_PKI_ICGX_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_ICGX_CFG(a) (a)
#define arguments_BDK_PKI_ICGX_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_imem#
 *
 * PKI Cluster IMEM Registers
 */
union bdk_pki_imemx
{
    uint64_t u;
    struct bdk_pki_imemx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Parse engine instruction word. Software must reload PKI_IMEM() upon the detection
                                                                 of PKI_ECC2_INT[IMEM_SBE] or PKI_ECC2_INT[IMEM_DBE] errors. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Parse engine instruction word. Software must reload PKI_IMEM() upon the detection
                                                                 of PKI_ECC2_INT[IMEM_SBE] or PKI_ECC2_INT[IMEM_DBE] errors. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_imemx_s cn; */
};
typedef union bdk_pki_imemx bdk_pki_imemx_t;

static inline uint64_t BDK_PKI_IMEMX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_IMEMX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=2047))
        return 0x86c000100000ll + 8ll * ((a) & 0x7ff);
    __bdk_csr_fatal("PKI_IMEMX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_IMEMX(a) bdk_pki_imemx_t
#define bustype_BDK_PKI_IMEMX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_IMEMX(a) "PKI_IMEMX"
#define device_bar_BDK_PKI_IMEMX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_IMEMX(a) (a)
#define arguments_BDK_PKI_IMEMX(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_ltype#_map
 *
 * PKI Backend Layer Map Register
 * This register is the layer type map, indexed by PKI_LTYPE_E.
 */
union bdk_pki_ltypex_map
{
    uint64_t u;
    struct bdk_pki_ltypex_map_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t beltype               : 3;  /**< [  2:  0](R/W) For each given PKI_LTYPE_E, the protocol type backend hardware should assume
                                                                 this layer type corresponds to. Enumerated by PKI_BELTYPE_E. The recommended
                                                                 settings for each register index (PKI_LTYPE_E) are shown in the PKI_LTYPE_E
                                                                 table. */
#else /* Word 0 - Little Endian */
        uint64_t beltype               : 3;  /**< [  2:  0](R/W) For each given PKI_LTYPE_E, the protocol type backend hardware should assume
                                                                 this layer type corresponds to. Enumerated by PKI_BELTYPE_E. The recommended
                                                                 settings for each register index (PKI_LTYPE_E) are shown in the PKI_LTYPE_E
                                                                 table. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_ltypex_map_s cn; */
};
typedef union bdk_pki_ltypex_map bdk_pki_ltypex_map_t;

static inline uint64_t BDK_PKI_LTYPEX_MAP(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_LTYPEX_MAP(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x86c000005000ll + 8ll * ((a) & 0x1f);
    __bdk_csr_fatal("PKI_LTYPEX_MAP", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_LTYPEX_MAP(a) bdk_pki_ltypex_map_t
#define bustype_BDK_PKI_LTYPEX_MAP(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_LTYPEX_MAP(a) "PKI_LTYPEX_MAP"
#define device_bar_BDK_PKI_LTYPEX_MAP(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_LTYPEX_MAP(a) (a)
#define arguments_BDK_PKI_LTYPEX_MAP(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_msix_pba#
 *
 * PKI MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table; the bit number is indexed by the PKI_INT_VEC_E
 * enumeration.
 */
union bdk_pki_msix_pbax
{
    uint64_t u;
    struct bdk_pki_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated PKI_MSIX_VEC()_CTL, enumerated by
                                                                 PKI_INT_VEC_E. Bits that have no associated PKI_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated PKI_MSIX_VEC()_CTL, enumerated by
                                                                 PKI_INT_VEC_E. Bits that have no associated PKI_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_msix_pbax_s cn; */
};
typedef union bdk_pki_msix_pbax bdk_pki_msix_pbax_t;

static inline uint64_t BDK_PKI_MSIX_PBAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_MSIX_PBAX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x86c0010f0000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("PKI_MSIX_PBAX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_MSIX_PBAX(a) bdk_pki_msix_pbax_t
#define bustype_BDK_PKI_MSIX_PBAX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_MSIX_PBAX(a) "PKI_MSIX_PBAX"
#define device_bar_BDK_PKI_MSIX_PBAX(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_PKI_MSIX_PBAX(a) (a)
#define arguments_BDK_PKI_MSIX_PBAX(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_msix_vec#_addr
 *
 * PKI MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the PKI_INT_VEC_E enumeration.
 */
union bdk_pki_msix_vecx_addr
{
    uint64_t u;
    struct bdk_pki_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 =  This vector's PKI_MSIX_VEC()_ADDR, PKI_MSIX_VEC()_CTL, and corresponding
                                                                 bit of PKI_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_PKI_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if
                                                                 [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 =  This vector's PKI_MSIX_VEC()_ADDR, PKI_MSIX_VEC()_CTL, and corresponding
                                                                 bit of PKI_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_PKI_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if
                                                                 [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_msix_vecx_addr_s cn; */
};
typedef union bdk_pki_msix_vecx_addr bdk_pki_msix_vecx_addr_t;

static inline uint64_t BDK_PKI_MSIX_VECX_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_MSIX_VECX_ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=15))
        return 0x86c001000000ll + 0x10ll * ((a) & 0xf);
    __bdk_csr_fatal("PKI_MSIX_VECX_ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_MSIX_VECX_ADDR(a) bdk_pki_msix_vecx_addr_t
#define bustype_BDK_PKI_MSIX_VECX_ADDR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_MSIX_VECX_ADDR(a) "PKI_MSIX_VECX_ADDR"
#define device_bar_BDK_PKI_MSIX_VECX_ADDR(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_PKI_MSIX_VECX_ADDR(a) (a)
#define arguments_BDK_PKI_MSIX_VECX_ADDR(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_msix_vec#_ctl
 *
 * PKI MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the PKI_INT_VEC_E enumeration.
 */
union bdk_pki_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_pki_msix_vecx_ctl_s
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
    /* struct bdk_pki_msix_vecx_ctl_s cn; */
};
typedef union bdk_pki_msix_vecx_ctl bdk_pki_msix_vecx_ctl_t;

static inline uint64_t BDK_PKI_MSIX_VECX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_MSIX_VECX_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=15))
        return 0x86c001000008ll + 0x10ll * ((a) & 0xf);
    __bdk_csr_fatal("PKI_MSIX_VECX_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_MSIX_VECX_CTL(a) bdk_pki_msix_vecx_ctl_t
#define bustype_BDK_PKI_MSIX_VECX_CTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_MSIX_VECX_CTL(a) "PKI_MSIX_VECX_CTL"
#define device_bar_BDK_PKI_MSIX_VECX_CTL(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_PKI_MSIX_VECX_CTL(a) (a)
#define arguments_BDK_PKI_MSIX_VECX_CTL(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_pbe_eco
 *
 * INTERNAL: PKI PBE ECO Register
 */
union bdk_pki_pbe_eco
{
    uint64_t u;
    struct bdk_pki_pbe_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pbe_eco_s cn; */
};
typedef union bdk_pki_pbe_eco bdk_pki_pbe_eco_t;

#define BDK_PKI_PBE_ECO BDK_PKI_PBE_ECO_FUNC()
static inline uint64_t BDK_PKI_PBE_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PBE_ECO_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000710ll;
    __bdk_csr_fatal("PKI_PBE_ECO", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PBE_ECO bdk_pki_pbe_eco_t
#define bustype_BDK_PKI_PBE_ECO BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PBE_ECO "PKI_PBE_ECO"
#define device_bar_BDK_PKI_PBE_ECO 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PBE_ECO 0
#define arguments_BDK_PKI_PBE_ECO -1,-1,-1,-1

/**
 * Register (NCB) pki_pbe_fxa_result
 *
 * INTERNAL: PKI PBE FXA Result Register
 *
 * For diagnostic use only.
 * Reads of this register will indicate whether or not FPA has returned a pointer back
 * to PKI and, if so, the values that were returned. A write to this register with any
 * data value will clear the VALID field. This will indicate to PKI that software has
 * consumed the values associated with the most recently returned pointer information
 * set. It is recommended that software write to this register prior to each write of
 * PKI_PBE_XFR_REQUEST.
 */
union bdk_pki_pbe_fxa_result
{
    uint64_t u;
    struct bdk_pki_pbe_fxa_result_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t valid                 : 1;  /**< [ 63: 63](R/W/H) If set, indicates that remaining fields within this register are valid to be
                                                                 read by software. */
        uint64_t fault                 : 1;  /**< [ 62: 62](R/W/H) The value of FAULT returned by FPA.  Indicates an illegal combination of GMID/GAURA
                                                                 during the request for a pointer. */
        uint64_t avail                 : 1;  /**< [ 61: 61](R/W/H) The value of AVAIL returned by FPA as part of a pointer return. */
        uint64_t red                   : 1;  /**< [ 60: 60](R/W/H) The value of RED returned by FPA as part of a pointer return. */
        uint64_t reserved_46_59        : 14;
        uint64_t rsvd_ptr              : 4;  /**< [ 45: 42](R/W/H) Reserved for future pointer growth. */
        uint64_t pointer               : 42; /**< [ 41:  0](R/W/H) Defines the 128-byte aligned pointer returned by FPA.  So pointer\<48:7\>. */
#else /* Word 0 - Little Endian */
        uint64_t pointer               : 42; /**< [ 41:  0](R/W/H) Defines the 128-byte aligned pointer returned by FPA.  So pointer\<48:7\>. */
        uint64_t rsvd_ptr              : 4;  /**< [ 45: 42](R/W/H) Reserved for future pointer growth. */
        uint64_t reserved_46_59        : 14;
        uint64_t red                   : 1;  /**< [ 60: 60](R/W/H) The value of RED returned by FPA as part of a pointer return. */
        uint64_t avail                 : 1;  /**< [ 61: 61](R/W/H) The value of AVAIL returned by FPA as part of a pointer return. */
        uint64_t fault                 : 1;  /**< [ 62: 62](R/W/H) The value of FAULT returned by FPA.  Indicates an illegal combination of GMID/GAURA
                                                                 during the request for a pointer. */
        uint64_t valid                 : 1;  /**< [ 63: 63](R/W/H) If set, indicates that remaining fields within this register are valid to be
                                                                 read by software. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pbe_fxa_result_s cn; */
};
typedef union bdk_pki_pbe_fxa_result bdk_pki_pbe_fxa_result_t;

#define BDK_PKI_PBE_FXA_RESULT BDK_PKI_PBE_FXA_RESULT_FUNC()
static inline uint64_t BDK_PKI_PBE_FXA_RESULT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PBE_FXA_RESULT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000fff008ll;
    __bdk_csr_fatal("PKI_PBE_FXA_RESULT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PBE_FXA_RESULT bdk_pki_pbe_fxa_result_t
#define bustype_BDK_PKI_PBE_FXA_RESULT BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PBE_FXA_RESULT "PKI_PBE_FXA_RESULT"
#define device_bar_BDK_PKI_PBE_FXA_RESULT 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PBE_FXA_RESULT 0
#define arguments_BDK_PKI_PBE_FXA_RESULT -1,-1,-1,-1

/**
 * Register (NCB) pki_pbe_lwa_inject_hi
 *
 * INTERNAL: PKI PBE LWA Inject High Register
 *
 * For diagnostic use only.
 * A write to this register will prepare some of the control fields needed to initiate
 * a long work add request so SSO.  The request will not be made until both
 * PKI_PBE_LWA_INJECT_LO and PKI_PBE_LWA_INJECT_HI have been written as a pair.  It is
 * recommended to write PKI_PBE_LWA_INJECT_HI as the second of the two writes.
 * A read of this register is 0x0 for all bits except \<0\> which indicates if
 * a previous request is pending (SSO has not yet granted PKI's LWA request).
 */
union bdk_pki_pbe_lwa_inject_hi
{
    uint64_t u;
    struct bdk_pki_pbe_lwa_inject_hi_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t gmid                  : 16; /**< [ 47: 32](WO) Bus GMID field for the request when written.  Reads as 0. */
        uint64_t tag_msbs              : 31; /**< [ 31:  1](WO) Bus TAG\<31:1\> field for the request when written.
                                                                 Reads as 0. */
        uint64_t tag_lsb_busy          : 1;  /**< [  0:  0](R/W/H) Internal:
                                                                 Bus TAG\<0\> field for the request when written.
                                                                 On a read, if set, this bit indicates that a previous LWA
                                                                 request is pending (SSO has not yet given a grant for the
                                                                 request). */
#else /* Word 0 - Little Endian */
        uint64_t tag_lsb_busy          : 1;  /**< [  0:  0](R/W/H) Internal:
                                                                 Bus TAG\<0\> field for the request when written.
                                                                 On a read, if set, this bit indicates that a previous LWA
                                                                 request is pending (SSO has not yet given a grant for the
                                                                 request). */
        uint64_t tag_msbs              : 31; /**< [ 31:  1](WO) Bus TAG\<31:1\> field for the request when written.
                                                                 Reads as 0. */
        uint64_t gmid                  : 16; /**< [ 47: 32](WO) Bus GMID field for the request when written.  Reads as 0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pbe_lwa_inject_hi_s cn; */
};
typedef union bdk_pki_pbe_lwa_inject_hi bdk_pki_pbe_lwa_inject_hi_t;

#define BDK_PKI_PBE_LWA_INJECT_HI BDK_PKI_PBE_LWA_INJECT_HI_FUNC()
static inline uint64_t BDK_PKI_PBE_LWA_INJECT_HI_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PBE_LWA_INJECT_HI_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000fff028ll;
    __bdk_csr_fatal("PKI_PBE_LWA_INJECT_HI", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PBE_LWA_INJECT_HI bdk_pki_pbe_lwa_inject_hi_t
#define bustype_BDK_PKI_PBE_LWA_INJECT_HI BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PBE_LWA_INJECT_HI "PKI_PBE_LWA_INJECT_HI"
#define device_bar_BDK_PKI_PBE_LWA_INJECT_HI 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PBE_LWA_INJECT_HI 0
#define arguments_BDK_PKI_PBE_LWA_INJECT_HI -1,-1,-1,-1

/**
 * Register (NCB) pki_pbe_lwa_inject_lo
 *
 * INTERNAL: PKI PBE LWA Inject Low Register
 *
 * For diagnostic use only.
 * A write to this register will prepare some of the control fields needed to initiate
 * a long work add request so SSO.  The request will not be made until both
 * PKI_PBE_LWA_INJECT_LO and PKI_PBE_LWA_INJECT_HI have been written as a pair.  It is
 * recommended to write PKI_PBE_LWA_INJECT_HI as the second of the two writes.
 * A read of this register is 0x0 for all bits except \<0\> which indicates if
 * a previous request is pending (SSO has not yet granted PKI's LWA request).
 */
union bdk_pki_pbe_lwa_inject_lo
{
    uint64_t u;
    struct bdk_pki_pbe_lwa_inject_lo_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ttype                 : 2;  /**< [ 63: 62](WO) Bus ttype field for request when written.  Reads as 0. */
        uint64_t reserved_61           : 1;
        uint64_t lwa                   : 1;  /**< [ 60: 60](WO) Bus LWA field for request when written.  Reads as 0. */
        uint64_t ggrp                  : 10; /**< [ 59: 50](WO) Bus GGRP field for request when written.  Reads as 0. */
        uint64_t reserved_46_49        : 4;
        uint64_t wqp_msbs              : 45; /**< [ 45:  1](WO) Bus WQP\<48:4\> field for the LWA request to SSO when written.
                                                                 Reads as 0. */
        uint64_t wqp_lsb_busy          : 1;  /**< [  0:  0](R/W/H) Internal:
                                                                 Bus WQP\<3\> field for the LWA request to SSO when written.
                                                                 On a read, if set, this bit indicates that a previous LWA
                                                                 request is pending (SSO has not yet given a grant for the
                                                                 request). */
#else /* Word 0 - Little Endian */
        uint64_t wqp_lsb_busy          : 1;  /**< [  0:  0](R/W/H) Internal:
                                                                 Bus WQP\<3\> field for the LWA request to SSO when written.
                                                                 On a read, if set, this bit indicates that a previous LWA
                                                                 request is pending (SSO has not yet given a grant for the
                                                                 request). */
        uint64_t wqp_msbs              : 45; /**< [ 45:  1](WO) Bus WQP\<48:4\> field for the LWA request to SSO when written.
                                                                 Reads as 0. */
        uint64_t reserved_46_49        : 4;
        uint64_t ggrp                  : 10; /**< [ 59: 50](WO) Bus GGRP field for request when written.  Reads as 0. */
        uint64_t lwa                   : 1;  /**< [ 60: 60](WO) Bus LWA field for request when written.  Reads as 0. */
        uint64_t reserved_61           : 1;
        uint64_t ttype                 : 2;  /**< [ 63: 62](WO) Bus ttype field for request when written.  Reads as 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pbe_lwa_inject_lo_s cn; */
};
typedef union bdk_pki_pbe_lwa_inject_lo bdk_pki_pbe_lwa_inject_lo_t;

#define BDK_PKI_PBE_LWA_INJECT_LO BDK_PKI_PBE_LWA_INJECT_LO_FUNC()
static inline uint64_t BDK_PKI_PBE_LWA_INJECT_LO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PBE_LWA_INJECT_LO_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000fff020ll;
    __bdk_csr_fatal("PKI_PBE_LWA_INJECT_LO", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PBE_LWA_INJECT_LO bdk_pki_pbe_lwa_inject_lo_t
#define bustype_BDK_PKI_PBE_LWA_INJECT_LO BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PBE_LWA_INJECT_LO "PKI_PBE_LWA_INJECT_LO"
#define device_bar_BDK_PKI_PBE_LWA_INJECT_LO 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PBE_LWA_INJECT_LO 0
#define arguments_BDK_PKI_PBE_LWA_INJECT_LO -1,-1,-1,-1

/**
 * Register (NCB) pki_pbe_pce_flush_detect
 *
 * PKI Flush Detection Register
 */
union bdk_pki_pbe_pce_flush_detect
{
    uint64_t u;
    struct bdk_pki_pbe_pce_flush_detect_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t flush_state           : 2;  /**< [  1:  0](RO/H) Flush state. Will read as 0x0 when flush detection is completed.

                                                                 This allows software to synchronize with hardware when reconfiguring
                                                                 PKI_STRM()_CFG[GMID].  After writing the last entry to be modified in
                                                                 PKI_STRM()_CFG as part of a reconfiguration sequence, software must wait until
                                                                 [FLUSH_STATE] reads 0x0 to know that no packet writes are outstanding to the old
                                                                 stream. */
#else /* Word 0 - Little Endian */
        uint64_t flush_state           : 2;  /**< [  1:  0](RO/H) Flush state. Will read as 0x0 when flush detection is completed.

                                                                 This allows software to synchronize with hardware when reconfiguring
                                                                 PKI_STRM()_CFG[GMID].  After writing the last entry to be modified in
                                                                 PKI_STRM()_CFG as part of a reconfiguration sequence, software must wait until
                                                                 [FLUSH_STATE] reads 0x0 to know that no packet writes are outstanding to the old
                                                                 stream. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pbe_pce_flush_detect_s cn; */
};
typedef union bdk_pki_pbe_pce_flush_detect bdk_pki_pbe_pce_flush_detect_t;

#define BDK_PKI_PBE_PCE_FLUSH_DETECT BDK_PKI_PBE_PCE_FLUSH_DETECT_FUNC()
static inline uint64_t BDK_PKI_PBE_PCE_FLUSH_DETECT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PBE_PCE_FLUSH_DETECT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000fff080ll;
    __bdk_csr_fatal("PKI_PBE_PCE_FLUSH_DETECT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PBE_PCE_FLUSH_DETECT bdk_pki_pbe_pce_flush_detect_t
#define bustype_BDK_PKI_PBE_PCE_FLUSH_DETECT BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PBE_PCE_FLUSH_DETECT "PKI_PBE_PCE_FLUSH_DETECT"
#define device_bar_BDK_PKI_PBE_PCE_FLUSH_DETECT 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PBE_PCE_FLUSH_DETECT 0
#define arguments_BDK_PKI_PBE_PCE_FLUSH_DETECT -1,-1,-1,-1

/**
 * Register (NCB) pki_pbe_x2p_bp_inject
 *
 * INTERNAL: PKI PBE X2P Backpressure Injection Register
 */
union bdk_pki_pbe_x2p_bp_inject
{
    uint64_t u;
    struct bdk_pki_pbe_x2p_bp_inject_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 1;  /**< [ 63: 63](R/W) Enable injection mode. For diagnostic use only.
                                                                 If set, during X2P_BP cycling of backpressure information, the
                                                                 PKI hardware will override a single channel's backpressure value
                                                                 with [VALUE] during the X2P_BP transfer cycle defined by [CHANNEL]. */
        uint64_t reserved_13_62        : 50;
        uint64_t value                 : 1;  /**< [ 12: 12](R/W) Backpressure value. */
        uint64_t channel               : 12; /**< [ 11:  0](R/W) [CHANNEL]\<11:8\> defines the CHAN_ID on the X2P_BP interface
                                                                 that will be affected by this logic. The remaining bits of
                                                                 [CHANNEL] define which channel within the targeted device
                                                                 will have its backpressure value overridden with [VALUE]. */
#else /* Word 0 - Little Endian */
        uint64_t channel               : 12; /**< [ 11:  0](R/W) [CHANNEL]\<11:8\> defines the CHAN_ID on the X2P_BP interface
                                                                 that will be affected by this logic. The remaining bits of
                                                                 [CHANNEL] define which channel within the targeted device
                                                                 will have its backpressure value overridden with [VALUE]. */
        uint64_t value                 : 1;  /**< [ 12: 12](R/W) Backpressure value. */
        uint64_t reserved_13_62        : 50;
        uint64_t enable                : 1;  /**< [ 63: 63](R/W) Enable injection mode. For diagnostic use only.
                                                                 If set, during X2P_BP cycling of backpressure information, the
                                                                 PKI hardware will override a single channel's backpressure value
                                                                 with [VALUE] during the X2P_BP transfer cycle defined by [CHANNEL]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pbe_x2p_bp_inject_s cn; */
};
typedef union bdk_pki_pbe_x2p_bp_inject bdk_pki_pbe_x2p_bp_inject_t;

#define BDK_PKI_PBE_X2P_BP_INJECT BDK_PKI_PBE_X2P_BP_INJECT_FUNC()
static inline uint64_t BDK_PKI_PBE_X2P_BP_INJECT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PBE_X2P_BP_INJECT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000280ll;
    __bdk_csr_fatal("PKI_PBE_X2P_BP_INJECT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PBE_X2P_BP_INJECT bdk_pki_pbe_x2p_bp_inject_t
#define bustype_BDK_PKI_PBE_X2P_BP_INJECT BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PBE_X2P_BP_INJECT "PKI_PBE_X2P_BP_INJECT"
#define device_bar_BDK_PKI_PBE_X2P_BP_INJECT 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PBE_X2P_BP_INJECT 0
#define arguments_BDK_PKI_PBE_X2P_BP_INJECT -1,-1,-1,-1

/**
 * Register (NCB) pki_pbe_xfr_inject
 *
 * INTERNAL: PKI PBE XFR Inject Register
 *
 * For diagnostic use only.
 * A write to this register will initiate a pointer request using the fields shown below.
 * A read of this register is 0x0 for all bits except \<0\> which indicates if
 * a previous request is pending (FPA has not yet granted PKI's XFR request).
 */
union bdk_pki_pbe_xfr_inject
{
    uint64_t u;
    struct bdk_pki_pbe_xfr_inject_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_34_63        : 30;
        uint64_t red                   : 1;  /**< [ 33: 33](WO) RED field for request when written.  Reads as 0. */
        uint64_t drop                  : 1;  /**< [ 32: 32](WO) DROP field for request when written.  Reads as 0. */
        uint64_t gmid                  : 16; /**< [ 31: 16](WO) GMID field for request when written.  Reads as 0. */
        uint64_t gaura_msbs            : 15; /**< [ 15:  1](WO) GAURA\<15:1\> field for request when written.  Reads as 0. */
        uint64_t gaura_lsb_busy        : 1;  /**< [  0:  0](R/W/H) Internal:
                                                                 GAURA\<0\> field for request when written.  On reads, if set, this bit
                                                                 indicates a previously initiated request is still waiting for grant. */
#else /* Word 0 - Little Endian */
        uint64_t gaura_lsb_busy        : 1;  /**< [  0:  0](R/W/H) Internal:
                                                                 GAURA\<0\> field for request when written.  On reads, if set, this bit
                                                                 indicates a previously initiated request is still waiting for grant. */
        uint64_t gaura_msbs            : 15; /**< [ 15:  1](WO) GAURA\<15:1\> field for request when written.  Reads as 0. */
        uint64_t gmid                  : 16; /**< [ 31: 16](WO) GMID field for request when written.  Reads as 0. */
        uint64_t drop                  : 1;  /**< [ 32: 32](WO) DROP field for request when written.  Reads as 0. */
        uint64_t red                   : 1;  /**< [ 33: 33](WO) RED field for request when written.  Reads as 0. */
        uint64_t reserved_34_63        : 30;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pbe_xfr_inject_s cn; */
};
typedef union bdk_pki_pbe_xfr_inject bdk_pki_pbe_xfr_inject_t;

#define BDK_PKI_PBE_XFR_INJECT BDK_PKI_PBE_XFR_INJECT_FUNC()
static inline uint64_t BDK_PKI_PBE_XFR_INJECT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PBE_XFR_INJECT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000fff000ll;
    __bdk_csr_fatal("PKI_PBE_XFR_INJECT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PBE_XFR_INJECT bdk_pki_pbe_xfr_inject_t
#define bustype_BDK_PKI_PBE_XFR_INJECT BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PBE_XFR_INJECT "PKI_PBE_XFR_INJECT"
#define device_bar_BDK_PKI_PBE_XFR_INJECT 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PBE_XFR_INJECT 0
#define arguments_BDK_PKI_PBE_XFR_INJECT -1,-1,-1,-1

/**
 * Register (NCB) pki_pbe_xpd_inject_hi
 *
 * INTERNAL: PKI PBE XPD Inject High Register
 *
 * For diagnostic use only.
 * A write to this register will prepare some of the control fields needed to initiate
 * a pointer deallocate request.  The request will not be made until both
 * PKI_PBE_XPD_INJECT_LO and PKI_PBE_XPD_INJECT_HI have been written as a pair.  It is
 * recommended to write PKI_PBE_XPD_INJECT_HI as the second of the two writes.
 * A read of this register is 0x0 for all bits except \<0\> which indicate if
 * a previous deallocate is pending (FPA has not yet granted PKI's XPD request).
 */
union bdk_pki_pbe_xpd_inject_hi
{
    uint64_t u;
    struct bdk_pki_pbe_xpd_inject_hi_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t gmid                  : 16; /**< [ 63: 48](WO) GMID field for request when written.  Reads as 0. */
        uint64_t reserved_38_47        : 10;
        uint64_t abs                   : 1;  /**< [ 37: 37](WO) ABS field for request when written.  Reads as 0. */
        uint64_t sub                   : 1;  /**< [ 36: 36](WO) SUB field for request when written.  Reads as 0. */
        uint64_t reserved_33_35        : 3;
        uint64_t value                 : 17; /**< [ 32: 16](WO) VALUE field for request when written.  Reads as 0. */
        uint64_t gaura_msbs            : 15; /**< [ 15:  1](WO) GAURA\<15:1\> field for the request when written.  Reads as 0. */
        uint64_t gaura_lsb_busy        : 1;  /**< [  0:  0](R/W/H) Internal:
                                                                 GAURA\<0\> field for the request when written.
                                                                 On a read, if set, this bit indicates that a previous deallocate
                                                                 request is pending (FPA has not yet given a grant for the request). */
#else /* Word 0 - Little Endian */
        uint64_t gaura_lsb_busy        : 1;  /**< [  0:  0](R/W/H) Internal:
                                                                 GAURA\<0\> field for the request when written.
                                                                 On a read, if set, this bit indicates that a previous deallocate
                                                                 request is pending (FPA has not yet given a grant for the request). */
        uint64_t gaura_msbs            : 15; /**< [ 15:  1](WO) GAURA\<15:1\> field for the request when written.  Reads as 0. */
        uint64_t value                 : 17; /**< [ 32: 16](WO) VALUE field for request when written.  Reads as 0. */
        uint64_t reserved_33_35        : 3;
        uint64_t sub                   : 1;  /**< [ 36: 36](WO) SUB field for request when written.  Reads as 0. */
        uint64_t abs                   : 1;  /**< [ 37: 37](WO) ABS field for request when written.  Reads as 0. */
        uint64_t reserved_38_47        : 10;
        uint64_t gmid                  : 16; /**< [ 63: 48](WO) GMID field for request when written.  Reads as 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pbe_xpd_inject_hi_s cn; */
};
typedef union bdk_pki_pbe_xpd_inject_hi bdk_pki_pbe_xpd_inject_hi_t;

#define BDK_PKI_PBE_XPD_INJECT_HI BDK_PKI_PBE_XPD_INJECT_HI_FUNC()
static inline uint64_t BDK_PKI_PBE_XPD_INJECT_HI_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PBE_XPD_INJECT_HI_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000fff018ll;
    __bdk_csr_fatal("PKI_PBE_XPD_INJECT_HI", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PBE_XPD_INJECT_HI bdk_pki_pbe_xpd_inject_hi_t
#define bustype_BDK_PKI_PBE_XPD_INJECT_HI BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PBE_XPD_INJECT_HI "PKI_PBE_XPD_INJECT_HI"
#define device_bar_BDK_PKI_PBE_XPD_INJECT_HI 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PBE_XPD_INJECT_HI 0
#define arguments_BDK_PKI_PBE_XPD_INJECT_HI -1,-1,-1,-1

/**
 * Register (NCB) pki_pbe_xpd_inject_lo
 *
 * INTERNAL: PKI PBE XPD Inject Low Register
 *
 * For diagnostic use only.
 * A write to this register will prepare some of the control fields needed to initiate
 * a pointer deallocate request.  The request will not be made until both
 * PKI_PBE_XPD_INJECT_LO and PKI_PBE_XPD_INJECT_HI have been written as a pair.  It is
 * recommended to write PKI_PBE_XPD_INJECT_HI as the second of the two writes.
 * A read of this register is 0x0 for all bits except \<0\> which indicates if
 * a previous deallocate is pending (FPA has not yet granted PKI's XPD request).
 */
union bdk_pki_pbe_xpd_inject_lo
{
    uint64_t u;
    struct bdk_pki_pbe_xpd_inject_lo_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dmode                 : 2;  /**< [ 63: 62](WO) Defines DMODE field for request when written.  Reads as 0. */
        uint64_t reserved_42_61        : 20;
        uint64_t pointer_msbs          : 41; /**< [ 41:  1](WO) Defines pointer\<48:8\> for request when written.  Reads as 0. */
        uint64_t pointer_lsb_busy      : 1;  /**< [  0:  0](R/W/H) Internal:
                                                                 Defines pointer\<7\> for request when written.
                                                                 On a read, if set, this bit indicates that a previous deallocate
                                                                 request is pending (FPA has not yet given a grant for the request). */
#else /* Word 0 - Little Endian */
        uint64_t pointer_lsb_busy      : 1;  /**< [  0:  0](R/W/H) Internal:
                                                                 Defines pointer\<7\> for request when written.
                                                                 On a read, if set, this bit indicates that a previous deallocate
                                                                 request is pending (FPA has not yet given a grant for the request). */
        uint64_t pointer_msbs          : 41; /**< [ 41:  1](WO) Defines pointer\<48:8\> for request when written.  Reads as 0. */
        uint64_t reserved_42_61        : 20;
        uint64_t dmode                 : 2;  /**< [ 63: 62](WO) Defines DMODE field for request when written.  Reads as 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pbe_xpd_inject_lo_s cn; */
};
typedef union bdk_pki_pbe_xpd_inject_lo bdk_pki_pbe_xpd_inject_lo_t;

#define BDK_PKI_PBE_XPD_INJECT_LO BDK_PKI_PBE_XPD_INJECT_LO_FUNC()
static inline uint64_t BDK_PKI_PBE_XPD_INJECT_LO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PBE_XPD_INJECT_LO_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000fff010ll;
    __bdk_csr_fatal("PKI_PBE_XPD_INJECT_LO", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PBE_XPD_INJECT_LO bdk_pki_pbe_xpd_inject_lo_t
#define bustype_BDK_PKI_PBE_XPD_INJECT_LO BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PBE_XPD_INJECT_LO "PKI_PBE_XPD_INJECT_LO"
#define device_bar_BDK_PKI_PBE_XPD_INJECT_LO 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PBE_XPD_INJECT_LO 0
#define arguments_BDK_PKI_PBE_XPD_INJECT_LO -1,-1,-1,-1

/**
 * Register (NCB) pki_pcam_lookup
 *
 * PKI PCAM Lookup Register
 * For diagnostic use only, this register performs a PCAM lookup against the provided
 * cluster and PCAM instance and loads results into PKI_PCAM_RESULT.
 */
union bdk_pki_pcam_lookup
{
    uint64_t u;
    struct bdk_pki_pcam_lookup_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_54_63        : 10;
        uint64_t cl                    : 2;  /**< [ 53: 52](R/W) Cluster number within which to lookup. */
        uint64_t reserved_49_51        : 3;
        uint64_t pcam                  : 1;  /**< [ 48: 48](R/W) PCAM number within which to lookup. */
        uint64_t term                  : 8;  /**< [ 47: 40](R/W) Term value to lookup. */
        uint64_t style                 : 8;  /**< [ 39: 32](R/W) Style value to lookup. */
        uint64_t data                  : 32; /**< [ 31:  0](R/W) Data to lookup. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 32; /**< [ 31:  0](R/W) Data to lookup. */
        uint64_t style                 : 8;  /**< [ 39: 32](R/W) Style value to lookup. */
        uint64_t term                  : 8;  /**< [ 47: 40](R/W) Term value to lookup. */
        uint64_t pcam                  : 1;  /**< [ 48: 48](R/W) PCAM number within which to lookup. */
        uint64_t reserved_49_51        : 3;
        uint64_t cl                    : 2;  /**< [ 53: 52](R/W) Cluster number within which to lookup. */
        uint64_t reserved_54_63        : 10;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pcam_lookup_s cn; */
};
typedef union bdk_pki_pcam_lookup bdk_pki_pcam_lookup_t;

#define BDK_PKI_PCAM_LOOKUP BDK_PKI_PCAM_LOOKUP_FUNC()
static inline uint64_t BDK_PKI_PCAM_LOOKUP_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PCAM_LOOKUP_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000500ll;
    __bdk_csr_fatal("PKI_PCAM_LOOKUP", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PCAM_LOOKUP bdk_pki_pcam_lookup_t
#define bustype_BDK_PKI_PCAM_LOOKUP BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PCAM_LOOKUP "PKI_PCAM_LOOKUP"
#define device_bar_BDK_PKI_PCAM_LOOKUP 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PCAM_LOOKUP 0
#define arguments_BDK_PKI_PCAM_LOOKUP -1,-1,-1,-1

/**
 * Register (NCB) pki_pcam_result
 *
 * PKI PCAM Result Register
 * For diagnostic use only, this register returns PCAM results for the most recent write to
 * PKI_PCAM_LOOKUP. The read will stall until the lookup is completed.
 * PKI_CL()_ECC_CTL[PCAM_EN] must be clear before accessing this register.  Read stall
 * is implemented by delaying the PKI_PCAM_LOOKUP write acknowledge until the PCAM is
 * free and the lookup can be issued.
 */
union bdk_pki_pcam_result
{
    uint64_t u;
    struct bdk_pki_pcam_result_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t conflict              : 1;  /**< [ 63: 63](RO/H) Conflict. The lookup resulted in multiple entries matching PKI_PCAM_LOOKUP[DATA], [TERM]
                                                                 and [STYLE], or zero if no conflict. */
        uint64_t reserved_41_62        : 22;
        uint64_t match                 : 1;  /**< [ 40: 40](RO/H) Resulting match. */
        uint64_t entry                 : 8;  /**< [ 39: 32](RO/H) Resulting matching entry number, unpredictable unless [MATCH] set and [CONFLICT] is clear. */
        uint64_t result                : 32; /**< [ 31:  0](RO/H) Resulting data from matching line's PKI_CL()_PCAM()_ACTION(), or zero if no
                                                                 match. Unpredictable unless [CONFLICT] is clear. */
#else /* Word 0 - Little Endian */
        uint64_t result                : 32; /**< [ 31:  0](RO/H) Resulting data from matching line's PKI_CL()_PCAM()_ACTION(), or zero if no
                                                                 match. Unpredictable unless [CONFLICT] is clear. */
        uint64_t entry                 : 8;  /**< [ 39: 32](RO/H) Resulting matching entry number, unpredictable unless [MATCH] set and [CONFLICT] is clear. */
        uint64_t match                 : 1;  /**< [ 40: 40](RO/H) Resulting match. */
        uint64_t reserved_41_62        : 22;
        uint64_t conflict              : 1;  /**< [ 63: 63](RO/H) Conflict. The lookup resulted in multiple entries matching PKI_PCAM_LOOKUP[DATA], [TERM]
                                                                 and [STYLE], or zero if no conflict. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pcam_result_s cn; */
};
typedef union bdk_pki_pcam_result bdk_pki_pcam_result_t;

#define BDK_PKI_PCAM_RESULT BDK_PKI_PCAM_RESULT_FUNC()
static inline uint64_t BDK_PKI_PCAM_RESULT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PCAM_RESULT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000510ll;
    __bdk_csr_fatal("PKI_PCAM_RESULT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PCAM_RESULT bdk_pki_pcam_result_t
#define bustype_BDK_PKI_PCAM_RESULT BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PCAM_RESULT "PKI_PCAM_RESULT"
#define device_bar_BDK_PKI_PCAM_RESULT 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PCAM_RESULT 0
#define arguments_BDK_PKI_PCAM_RESULT -1,-1,-1,-1

/**
 * Register (NCB) pki_pfe_diag
 *
 * INTERNAL: PKI PFE Diagnostic Register
 */
union bdk_pki_pfe_diag
{
    uint64_t u;
    struct bdk_pki_pfe_diag_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t bad_rid               : 1;  /**< [  0:  0](R/W1C/H) Asserted when PFE sees and drops an X2P transaction with a RID \> 95. */
#else /* Word 0 - Little Endian */
        uint64_t bad_rid               : 1;  /**< [  0:  0](R/W1C/H) Asserted when PFE sees and drops an X2P transaction with a RID \> 95. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pfe_diag_s cn; */
};
typedef union bdk_pki_pfe_diag bdk_pki_pfe_diag_t;

#define BDK_PKI_PFE_DIAG BDK_PKI_PFE_DIAG_FUNC()
static inline uint64_t BDK_PKI_PFE_DIAG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PFE_DIAG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000560ll;
    __bdk_csr_fatal("PKI_PFE_DIAG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PFE_DIAG bdk_pki_pfe_diag_t
#define bustype_BDK_PKI_PFE_DIAG BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PFE_DIAG "PKI_PFE_DIAG"
#define device_bar_BDK_PKI_PFE_DIAG 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PFE_DIAG 0
#define arguments_BDK_PKI_PFE_DIAG -1,-1,-1,-1

/**
 * Register (NCB) pki_pfe_eco
 *
 * INTERNAL: PKI PFE ECO Register
 */
union bdk_pki_pfe_eco
{
    uint64_t u;
    struct bdk_pki_pfe_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pfe_eco_s cn; */
};
typedef union bdk_pki_pfe_eco bdk_pki_pfe_eco_t;

#define BDK_PKI_PFE_ECO BDK_PKI_PFE_ECO_FUNC()
static inline uint64_t BDK_PKI_PFE_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PFE_ECO_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000720ll;
    __bdk_csr_fatal("PKI_PFE_ECO", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PFE_ECO bdk_pki_pfe_eco_t
#define bustype_BDK_PKI_PFE_ECO BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PFE_ECO "PKI_PFE_ECO"
#define device_bar_BDK_PKI_PFE_ECO 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PFE_ECO 0
#define arguments_BDK_PKI_PFE_ECO -1,-1,-1,-1

/**
 * Register (NCB) pki_pix_clken
 *
 * INTERNAL: PKI PIX Conditional Clock Enable Register
 */
union bdk_pki_pix_clken
{
    uint64_t u;
    struct bdk_pki_pix_clken_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t mech                  : 1;  /**< [ 16: 16](R/W) When set, force the conditional clocks on for mech. */
        uint64_t reserved_4_15         : 12;
        uint64_t cls                   : 4;  /**< [  3:  0](R/W) When set, force the conditional clocks on for this cluster. */
#else /* Word 0 - Little Endian */
        uint64_t cls                   : 4;  /**< [  3:  0](R/W) When set, force the conditional clocks on for this cluster. */
        uint64_t reserved_4_15         : 12;
        uint64_t mech                  : 1;  /**< [ 16: 16](R/W) When set, force the conditional clocks on for mech. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pix_clken_s cn; */
};
typedef union bdk_pki_pix_clken bdk_pki_pix_clken_t;

#define BDK_PKI_PIX_CLKEN BDK_PKI_PIX_CLKEN_FUNC()
static inline uint64_t BDK_PKI_PIX_CLKEN_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PIX_CLKEN_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000600ll;
    __bdk_csr_fatal("PKI_PIX_CLKEN", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PIX_CLKEN bdk_pki_pix_clken_t
#define bustype_BDK_PKI_PIX_CLKEN BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PIX_CLKEN "PKI_PIX_CLKEN"
#define device_bar_BDK_PKI_PIX_CLKEN 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PIX_CLKEN 0
#define arguments_BDK_PKI_PIX_CLKEN -1,-1,-1,-1

/**
 * Register (NCB) pki_pix_diag
 *
 * INTERNAL: PKI PIX Diagnostic Register
 */
union bdk_pki_pix_diag
{
    uint64_t u;
    struct bdk_pki_pix_diag_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t nosched               : 4;  /**< [  3:  0](R/W1C/H) Asserted when PFE requests an ICG with no enabled CLUSTERS. */
#else /* Word 0 - Little Endian */
        uint64_t nosched               : 4;  /**< [  3:  0](R/W1C/H) Asserted when PFE requests an ICG with no enabled CLUSTERS. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pix_diag_s cn; */
};
typedef union bdk_pki_pix_diag bdk_pki_pix_diag_t;

#define BDK_PKI_PIX_DIAG BDK_PKI_PIX_DIAG_FUNC()
static inline uint64_t BDK_PKI_PIX_DIAG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PIX_DIAG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000580ll;
    __bdk_csr_fatal("PKI_PIX_DIAG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PIX_DIAG bdk_pki_pix_diag_t
#define bustype_BDK_PKI_PIX_DIAG BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PIX_DIAG "PKI_PIX_DIAG"
#define device_bar_BDK_PKI_PIX_DIAG 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PIX_DIAG 0
#define arguments_BDK_PKI_PIX_DIAG -1,-1,-1,-1

/**
 * Register (NCB) pki_pix_eco
 *
 * INTERNAL: PKI PIX ECO Register
 */
union bdk_pki_pix_eco
{
    uint64_t u;
    struct bdk_pki_pix_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pix_eco_s cn; */
};
typedef union bdk_pki_pix_eco bdk_pki_pix_eco_t;

#define BDK_PKI_PIX_ECO BDK_PKI_PIX_ECO_FUNC()
static inline uint64_t BDK_PKI_PIX_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PIX_ECO_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000700ll;
    __bdk_csr_fatal("PKI_PIX_ECO", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PIX_ECO bdk_pki_pix_eco_t
#define bustype_BDK_PKI_PIX_ECO BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PIX_ECO "PKI_PIX_ECO"
#define device_bar_BDK_PKI_PIX_ECO 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PIX_ECO 0
#define arguments_BDK_PKI_PIX_ECO -1,-1,-1,-1

/**
 * Register (NCB) pki_pkind#_icgsel
 *
 * PKI Per-Pkind Cluster Group Select Register
 */
union bdk_pki_pkindx_icgsel
{
    uint64_t u;
    struct bdk_pki_pkindx_icgsel_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t icg                   : 2;  /**< [  1:  0](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Cluster group that will service traffic on this pkind. See also PKI_ICG()_CFG, the
                                                                 register to which this field indexes. */
#else /* Word 0 - Little Endian */
        uint64_t icg                   : 2;  /**< [  1:  0](R/W) Reserved. Must be zero.
                                                                 Internal:
                                                                 Cluster group that will service traffic on this pkind. See also PKI_ICG()_CFG, the
                                                                 register to which this field indexes. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pkindx_icgsel_s cn; */
};
typedef union bdk_pki_pkindx_icgsel bdk_pki_pkindx_icgsel_t;

static inline uint64_t BDK_PKI_PKINDX_ICGSEL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PKINDX_ICGSEL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000010000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_PKINDX_ICGSEL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PKINDX_ICGSEL(a) bdk_pki_pkindx_icgsel_t
#define bustype_BDK_PKI_PKINDX_ICGSEL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PKINDX_ICGSEL(a) "PKI_PKINDX_ICGSEL"
#define device_bar_BDK_PKI_PKINDX_ICGSEL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PKINDX_ICGSEL(a) (a)
#define arguments_BDK_PKI_PKINDX_ICGSEL(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_pknd#_inb_stat0
 *
 * PKI Inbound Packets Statistic Registers
 * This register counts inbound statistics, indexed by pkind.
 */
union bdk_pki_pkndx_inb_stat0
{
    uint64_t u;
    struct bdk_pki_pkndx_inb_stat0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t pkts                  : 48; /**< [ 47:  0](R/W/H) Number of packets without errors received by PKI. */
#else /* Word 0 - Little Endian */
        uint64_t pkts                  : 48; /**< [ 47:  0](R/W/H) Number of packets without errors received by PKI. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pkndx_inb_stat0_s cn; */
};
typedef union bdk_pki_pkndx_inb_stat0 bdk_pki_pkndx_inb_stat0_t;

static inline uint64_t BDK_PKI_PKNDX_INB_STAT0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PKNDX_INB_STAT0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000f00000ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_PKNDX_INB_STAT0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PKNDX_INB_STAT0(a) bdk_pki_pkndx_inb_stat0_t
#define bustype_BDK_PKI_PKNDX_INB_STAT0(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PKNDX_INB_STAT0(a) "PKI_PKNDX_INB_STAT0"
#define device_bar_BDK_PKI_PKNDX_INB_STAT0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PKNDX_INB_STAT0(a) (a)
#define arguments_BDK_PKI_PKNDX_INB_STAT0(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_pknd#_inb_stat1
 *
 * PKI Inbound Octets Statistic Registers
 * This register counts inbound statistics, indexed by pkind.
 */
union bdk_pki_pkndx_inb_stat1
{
    uint64_t u;
    struct bdk_pki_pkndx_inb_stat1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t octs                  : 48; /**< [ 47:  0](R/W/H) Total number of octets from all packets received by PKI. */
#else /* Word 0 - Little Endian */
        uint64_t octs                  : 48; /**< [ 47:  0](R/W/H) Total number of octets from all packets received by PKI. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pkndx_inb_stat1_s cn; */
};
typedef union bdk_pki_pkndx_inb_stat1 bdk_pki_pkndx_inb_stat1_t;

static inline uint64_t BDK_PKI_PKNDX_INB_STAT1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PKNDX_INB_STAT1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000f00008ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_PKNDX_INB_STAT1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PKNDX_INB_STAT1(a) bdk_pki_pkndx_inb_stat1_t
#define bustype_BDK_PKI_PKNDX_INB_STAT1(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PKNDX_INB_STAT1(a) "PKI_PKNDX_INB_STAT1"
#define device_bar_BDK_PKI_PKNDX_INB_STAT1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PKNDX_INB_STAT1(a) (a)
#define arguments_BDK_PKI_PKNDX_INB_STAT1(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_pknd#_inb_stat2
 *
 * PKI Inbound Errors Statistic Registers
 * This register counts inbound statistics, indexed by pkind.
 */
union bdk_pki_pkndx_inb_stat2
{
    uint64_t u;
    struct bdk_pki_pkndx_inb_stat2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t errs                  : 48; /**< [ 47:  0](R/W/H) Number of packets with errors received by PKI. */
#else /* Word 0 - Little Endian */
        uint64_t errs                  : 48; /**< [ 47:  0](R/W/H) Number of packets with errors received by PKI. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pkndx_inb_stat2_s cn; */
};
typedef union bdk_pki_pkndx_inb_stat2 bdk_pki_pkndx_inb_stat2_t;

static inline uint64_t BDK_PKI_PKNDX_INB_STAT2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PKNDX_INB_STAT2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000f00010ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_PKNDX_INB_STAT2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PKNDX_INB_STAT2(a) bdk_pki_pkndx_inb_stat2_t
#define bustype_BDK_PKI_PKNDX_INB_STAT2(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PKNDX_INB_STAT2(a) "PKI_PKNDX_INB_STAT2"
#define device_bar_BDK_PKI_PKNDX_INB_STAT2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PKNDX_INB_STAT2(a) (a)
#define arguments_BDK_PKI_PKNDX_INB_STAT2(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_pkt_err
 *
 * PKI Packet Error Register
 */
union bdk_pki_pkt_err
{
    uint64_t u;
    struct bdk_pki_pkt_err_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t reasm                 : 7;  /**< [  6:  0](RO/H) When PKI_GEN_INT[DAT,SOP,EOP] is set, this field latches the failing reassembly number
                                                                 associated with the error. */
#else /* Word 0 - Little Endian */
        uint64_t reasm                 : 7;  /**< [  6:  0](RO/H) When PKI_GEN_INT[DAT,SOP,EOP] is set, this field latches the failing reassembly number
                                                                 associated with the error. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pkt_err_s cn; */
};
typedef union bdk_pki_pkt_err bdk_pki_pkt_err_t;

#define BDK_PKI_PKT_ERR BDK_PKI_PKT_ERR_FUNC()
static inline uint64_t BDK_PKI_PKT_ERR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PKT_ERR_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000030ll;
    __bdk_csr_fatal("PKI_PKT_ERR", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PKT_ERR bdk_pki_pkt_err_t
#define bustype_BDK_PKI_PKT_ERR BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PKT_ERR "PKI_PKT_ERR"
#define device_bar_BDK_PKI_PKT_ERR 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PKT_ERR 0
#define arguments_BDK_PKI_PKT_ERR -1,-1,-1,-1

/**
 * Register (NCB) pki_pstat_cfg
 *
 * INTERNAL: PKI Performance Statistics Configuration Register
 *
 * This register configures the performance statistics logic.
 */
union bdk_pki_pstat_cfg
{
    uint64_t u;
    struct bdk_pki_pstat_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t mode                  : 1;  /**< [ 12: 12](R/W) Select which pipelines are used for latency sampling:

                                                                 0 = The following PBE pipes are sampled:
                                                                   * PKI_PSTATA_STAT(0) etc. sample FPA request latency.
                                                                   * PKI_PSTATA_STAT(1) etc. sample PFE to PBE transfer latency.
                                                                   * PKI_PSTATA_STAT(2) etc. sample store commit latency.

                                                                 1 = The following PFE pipes are sampled:
                                                                   * PKI_PSTATA_STAT(0) etc. sample packet load time.
                                                                   * PKI_PSTATA_STAT(1) etc. sample PIX scheduling time.
                                                                   * PKI_PSTATA_STAT(2) etc. sample PIX processing time. */
        uint64_t gran2                 : 4;  /**< [ 11:  8](R/W) Granularity 2. Number of bits to left-shift count inputs to counter 2. */
        uint64_t gran1                 : 4;  /**< [  7:  4](R/W) Granularity 1. Number of bits to left-shift count inputs to counter 1. */
        uint64_t gran0                 : 4;  /**< [  3:  0](R/W) Granularity 0. Number of bits to left-shift count inputs to counter 0. */
#else /* Word 0 - Little Endian */
        uint64_t gran0                 : 4;  /**< [  3:  0](R/W) Granularity 0. Number of bits to left-shift count inputs to counter 0. */
        uint64_t gran1                 : 4;  /**< [  7:  4](R/W) Granularity 1. Number of bits to left-shift count inputs to counter 1. */
        uint64_t gran2                 : 4;  /**< [ 11:  8](R/W) Granularity 2. Number of bits to left-shift count inputs to counter 2. */
        uint64_t mode                  : 1;  /**< [ 12: 12](R/W) Select which pipelines are used for latency sampling:

                                                                 0 = The following PBE pipes are sampled:
                                                                   * PKI_PSTATA_STAT(0) etc. sample FPA request latency.
                                                                   * PKI_PSTATA_STAT(1) etc. sample PFE to PBE transfer latency.
                                                                   * PKI_PSTATA_STAT(2) etc. sample store commit latency.

                                                                 1 = The following PFE pipes are sampled:
                                                                   * PKI_PSTATA_STAT(0) etc. sample packet load time.
                                                                   * PKI_PSTATA_STAT(1) etc. sample PIX scheduling time.
                                                                   * PKI_PSTATA_STAT(2) etc. sample PIX processing time. */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pstat_cfg_s cn; */
};
typedef union bdk_pki_pstat_cfg bdk_pki_pstat_cfg_t;

#define BDK_PKI_PSTAT_CFG BDK_PKI_PSTAT_CFG_FUNC()
static inline uint64_t BDK_PKI_PSTAT_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PSTAT_CFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000f14200ll;
    __bdk_csr_fatal("PKI_PSTAT_CFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PSTAT_CFG bdk_pki_pstat_cfg_t
#define bustype_BDK_PKI_PSTAT_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PSTAT_CFG "PKI_PSTAT_CFG"
#define device_bar_BDK_PKI_PSTAT_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PSTAT_CFG 0
#define arguments_BDK_PKI_PSTAT_CFG -1,-1,-1,-1

/**
 * Register (NCB) pki_pstat_cntr
 *
 * INTERNAL: PKI Performance Statistics Counter Register
 */
union bdk_pki_pstat_cntr
{
    uint64_t u;
    struct bdk_pki_pstat_cntr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cntr                  : 64; /**< [ 63:  0](R/W/H) Number of coprocessor-clock cycles over which to sample performance statistics. */
#else /* Word 0 - Little Endian */
        uint64_t cntr                  : 64; /**< [ 63:  0](R/W/H) Number of coprocessor-clock cycles over which to sample performance statistics. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pstat_cntr_s cn; */
};
typedef union bdk_pki_pstat_cntr bdk_pki_pstat_cntr_t;

#define BDK_PKI_PSTAT_CNTR BDK_PKI_PSTAT_CNTR_FUNC()
static inline uint64_t BDK_PKI_PSTAT_CNTR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PSTAT_CNTR_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000f14208ll;
    __bdk_csr_fatal("PKI_PSTAT_CNTR", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PSTAT_CNTR bdk_pki_pstat_cntr_t
#define bustype_BDK_PKI_PSTAT_CNTR BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PSTAT_CNTR "PKI_PSTAT_CNTR"
#define device_bar_BDK_PKI_PSTAT_CNTR 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PSTAT_CNTR 0
#define arguments_BDK_PKI_PSTAT_CNTR -1,-1,-1,-1

/**
 * Register (NCB) pki_pstata_stat#
 *
 * INTERNAL: PKI Performance Statistics Average Registers
 *
 * This register holds statistics for the chosen metrics.
 * See PKI_PSTAT_CFG[MODE] for the meaning of each index.
 */
union bdk_pki_pstata_statx
{
    uint64_t u;
    struct bdk_pki_pstata_statx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](R/W/H) Accumulated sum of latencies of the selected statistic. */
#else /* Word 0 - Little Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](R/W/H) Accumulated sum of latencies of the selected statistic. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pstata_statx_s cn; */
};
typedef union bdk_pki_pstata_statx bdk_pki_pstata_statx_t;

static inline uint64_t BDK_PKI_PSTATA_STATX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PSTATA_STATX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=2))
        return 0x86c000f14000ll + 0x20ll * ((a) & 0x3);
    __bdk_csr_fatal("PKI_PSTATA_STATX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PSTATA_STATX(a) bdk_pki_pstata_statx_t
#define bustype_BDK_PKI_PSTATA_STATX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PSTATA_STATX(a) "PKI_PSTATA_STATX"
#define device_bar_BDK_PKI_PSTATA_STATX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PSTATA_STATX(a) (a)
#define arguments_BDK_PKI_PSTATA_STATX(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_pstatb_stat#
 *
 * INTERNAL: PKI Performance Statistics Sampled Registers
 *
 * This register holds statistics for the chosen metrics.
 * See PKI_PSTAT_CFG[MODE] for the meaning of each index.
 */
union bdk_pki_pstatb_statx
{
    uint64_t u;
    struct bdk_pki_pstatb_statx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](R/W/H) Number of packets sampled for the selected statistic. */
#else /* Word 0 - Little Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](R/W/H) Number of packets sampled for the selected statistic. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pstatb_statx_s cn; */
};
typedef union bdk_pki_pstatb_statx bdk_pki_pstatb_statx_t;

static inline uint64_t BDK_PKI_PSTATB_STATX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PSTATB_STATX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=2))
        return 0x86c000f14008ll + 0x20ll * ((a) & 0x3);
    __bdk_csr_fatal("PKI_PSTATB_STATX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PSTATB_STATX(a) bdk_pki_pstatb_statx_t
#define bustype_BDK_PKI_PSTATB_STATX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PSTATB_STATX(a) "PKI_PSTATB_STATX"
#define device_bar_BDK_PKI_PSTATB_STATX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PSTATB_STATX(a) (a)
#define arguments_BDK_PKI_PSTATB_STATX(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_pstatc_stat#
 *
 * INTERNAL: PKI Performance Statistics Minimum/Maximum Registers
 *
 * This register holds statistics for the chosen metrics.
 * See PKI_PSTAT_CFG[MODE] for the meaning of each index.
 */
union bdk_pki_pstatc_statx
{
    uint64_t u;
    struct bdk_pki_pstatc_statx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_43_63        : 21;
        uint64_t ov                    : 1;  /**< [ 42: 42](R/W/H) Statistic counter overflowed. */
        uint64_t max_lat               : 21; /**< [ 41: 21](R/W/H) Maximum value of statistic. */
        uint64_t min_lat               : 21; /**< [ 20:  0](R/W/H) Minimum value of statistic. */
#else /* Word 0 - Little Endian */
        uint64_t min_lat               : 21; /**< [ 20:  0](R/W/H) Minimum value of statistic. */
        uint64_t max_lat               : 21; /**< [ 41: 21](R/W/H) Maximum value of statistic. */
        uint64_t ov                    : 1;  /**< [ 42: 42](R/W/H) Statistic counter overflowed. */
        uint64_t reserved_43_63        : 21;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_pstatc_statx_s cn; */
};
typedef union bdk_pki_pstatc_statx bdk_pki_pstatc_statx_t;

static inline uint64_t BDK_PKI_PSTATC_STATX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PSTATC_STATX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=2))
        return 0x86c000f14010ll + 0x20ll * ((a) & 0x3);
    __bdk_csr_fatal("PKI_PSTATC_STATX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PSTATC_STATX(a) bdk_pki_pstatc_statx_t
#define bustype_BDK_PKI_PSTATC_STATX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PSTATC_STATX(a) "PKI_PSTATC_STATX"
#define device_bar_BDK_PKI_PSTATC_STATX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PSTATC_STATX(a) (a)
#define arguments_BDK_PKI_PSTATC_STATX(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_ptag_avail
 *
 * PKI PTAG Available Register
 * For diagnostic use only.
 * Internal:
 * This register configures tag management. It is
 * suggested that this register only be written when PKI_BUF_CTL[PKI_EN] is clear and
 * must not be reconfigured without soft resetting PKI. While PKI is tolerant of
 * changes to this register and programming restrictions are not necessary for the
 * general case, the suggestion is to simplify verification. Therefore do not put other
 * fields into this register unless the same constraint applies. When the number of
 * tags available increases, PKI will simply have more resources. When the number of
 * tags available decreases, PKI will use less resources and may begin to assert BP if
 * the current tags in use exceeds the programmed value.
 */
union bdk_pki_ptag_avail
{
    uint64_t u;
    struct bdk_pki_ptag_avail_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t avail                 : 8;  /**< [  7:  0](R/W) Number of ptags available for use. Decreasing the number of ptags will reduce
                                                                 the number of packets waiting for parsing, which will lead to sooner
                                                                 backpressure/packet drop, but will decrease the small-packet latency of PKI by
                                                                 reducing buffer-bloat. AVAIL must be at least as great as the number of
                                                                 reassembly-IDs used by the system intends to use or the PTAGS can be exhausted
                                                                 and PKI will hang. */
#else /* Word 0 - Little Endian */
        uint64_t avail                 : 8;  /**< [  7:  0](R/W) Number of ptags available for use. Decreasing the number of ptags will reduce
                                                                 the number of packets waiting for parsing, which will lead to sooner
                                                                 backpressure/packet drop, but will decrease the small-packet latency of PKI by
                                                                 reducing buffer-bloat. AVAIL must be at least as great as the number of
                                                                 reassembly-IDs used by the system intends to use or the PTAGS can be exhausted
                                                                 and PKI will hang. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_ptag_avail_s cn; */
};
typedef union bdk_pki_ptag_avail bdk_pki_ptag_avail_t;

#define BDK_PKI_PTAG_AVAIL BDK_PKI_PTAG_AVAIL_FUNC()
static inline uint64_t BDK_PKI_PTAG_AVAIL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_PTAG_AVAIL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000130ll;
    __bdk_csr_fatal("PKI_PTAG_AVAIL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_PTAG_AVAIL bdk_pki_ptag_avail_t
#define bustype_BDK_PKI_PTAG_AVAIL BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_PTAG_AVAIL "PKI_PTAG_AVAIL"
#define device_bar_BDK_PKI_PTAG_AVAIL 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_PTAG_AVAIL 0
#define arguments_BDK_PKI_PTAG_AVAIL -1,-1,-1,-1

/**
 * Register (NCB) pki_qpg_tbl#
 *
 * PKI QPG Table Registers
 * These registers are used by PKI BE to indirectly calculate the Portadd/Aura/Group
 * from the Diffsrv, HiGig or VLAN information as described in QPG. See also
 * PKI_QPG_TBLB().
 */
union bdk_pki_qpg_tblx
{
    uint64_t u;
    struct bdk_pki_qpg_tblx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_60_63        : 4;
        uint64_t padd                  : 12; /**< [ 59: 48](R/W) Port to channel adder for calculating PKI_WQE_S[CHAN]. */
        uint64_t grptag_ok             : 3;  /**< [ 47: 45](R/W) Number of PKI_WQE_S[TAG] bits to add into PKI_WQE_S[GRP] if no error is detected. */
        uint64_t reserved_42_44        : 3;
        uint64_t grp_ok                : 10; /**< [ 41: 32](R/W) SSO guest-group to schedule packet to and to load PKI_WQE_S[GRP] with if no error is
                                                                 detected.

                                                                 PKI_STRM()_CFG[GMID] is the GMID associated with [GRP_OK]. For a successful SSO add-work
                                                                 request, SSO_PF_MAP() must map [GRP_OK] and PKI_STRM()_CFG[GMID] as valid. */
        uint64_t grptag_bad            : 3;  /**< [ 31: 29](R/W) Number of PKI_WQE_S[TAG] bits to add into PKI_WQE_S[GRP] if an error is detected. */
        uint64_t reserved_26_28        : 3;
        uint64_t grp_bad               : 10; /**< [ 25: 16](R/W) SSO guest-group to schedule packet to and to load PKI_WQE_S[GRP] with if an
                                                                 error is detected.

                                                                 PKI_STRM()_CFG[GMID] is the GMID associated with [GRP_BAD]. For a successful SSO add-work
                                                                 request, SSO_PF_MAP() must map [GRP_BAD] and PKI_STRM()_CFG[GMID] as valid. */
        uint64_t reserved_12_15        : 4;
        uint64_t gaura                 : 12; /**< [ 11:  0](R/W) Guest-aura for QOS calculations and loading into PKI_WQE_S[AURA].

                                                                 PKI_STRM()_CFG[GMID] is the GMID associated with [GAURA]. For successful FPA requests,
                                                                 FPA_PF_MAP() must map [GAURA] and PKI_STRM()_CFG[GMID] as valid. */
#else /* Word 0 - Little Endian */
        uint64_t gaura                 : 12; /**< [ 11:  0](R/W) Guest-aura for QOS calculations and loading into PKI_WQE_S[AURA].

                                                                 PKI_STRM()_CFG[GMID] is the GMID associated with [GAURA]. For successful FPA requests,
                                                                 FPA_PF_MAP() must map [GAURA] and PKI_STRM()_CFG[GMID] as valid. */
        uint64_t reserved_12_15        : 4;
        uint64_t grp_bad               : 10; /**< [ 25: 16](R/W) SSO guest-group to schedule packet to and to load PKI_WQE_S[GRP] with if an
                                                                 error is detected.

                                                                 PKI_STRM()_CFG[GMID] is the GMID associated with [GRP_BAD]. For a successful SSO add-work
                                                                 request, SSO_PF_MAP() must map [GRP_BAD] and PKI_STRM()_CFG[GMID] as valid. */
        uint64_t reserved_26_28        : 3;
        uint64_t grptag_bad            : 3;  /**< [ 31: 29](R/W) Number of PKI_WQE_S[TAG] bits to add into PKI_WQE_S[GRP] if an error is detected. */
        uint64_t grp_ok                : 10; /**< [ 41: 32](R/W) SSO guest-group to schedule packet to and to load PKI_WQE_S[GRP] with if no error is
                                                                 detected.

                                                                 PKI_STRM()_CFG[GMID] is the GMID associated with [GRP_OK]. For a successful SSO add-work
                                                                 request, SSO_PF_MAP() must map [GRP_OK] and PKI_STRM()_CFG[GMID] as valid. */
        uint64_t reserved_42_44        : 3;
        uint64_t grptag_ok             : 3;  /**< [ 47: 45](R/W) Number of PKI_WQE_S[TAG] bits to add into PKI_WQE_S[GRP] if no error is detected. */
        uint64_t padd                  : 12; /**< [ 59: 48](R/W) Port to channel adder for calculating PKI_WQE_S[CHAN]. */
        uint64_t reserved_60_63        : 4;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_qpg_tblx_s cn; */
};
typedef union bdk_pki_qpg_tblx bdk_pki_qpg_tblx_t;

static inline uint64_t BDK_PKI_QPG_TBLX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_QPG_TBLX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=2047))
        return 0x86c000800000ll + 8ll * ((a) & 0x7ff);
    __bdk_csr_fatal("PKI_QPG_TBLX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_QPG_TBLX(a) bdk_pki_qpg_tblx_t
#define bustype_BDK_PKI_QPG_TBLX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_QPG_TBLX(a) "PKI_QPG_TBLX"
#define device_bar_BDK_PKI_QPG_TBLX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_QPG_TBLX(a) (a)
#define arguments_BDK_PKI_QPG_TBLX(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_qpg_tblb#
 *
 * PKI QPG Table Registers 2
 * This register configures the QPG table. See also PKI_QPG_TBL().
 */
union bdk_pki_qpg_tblbx
{
    uint64_t u;
    struct bdk_pki_qpg_tblbx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t pkt_add               : 2;  /**< [ 31: 30](R/W) Specifies what to add to FPA_VHAURA()_CNT when PKI enqueues a packet:
                                                                   0x0 = zero.
                                                                   0x1 = one.
                                                                   0x2 = The number of FPA buffers allocated; i.e. if PKI_STYLE()_BUF[DIS_WQ_DAT]
                                                                   is set, PKI_WQE_S[BUFS]+1, else PKI_WQE_S[BUFS].
                                                                   0x3 = PKI_WQE_S[LEN] (i.e. the packet length). */
        uint64_t ena_red               : 1;  /**< [ 29: 29](R/W) Enable RED drop between PASS and DROP levels. See also
                                                                 FPA_AURA()_POOL_LEVELS[RED_ENA] and FPA_AURA()_CNT_LEVELS[RED_ENA]. */
        uint64_t ena_drop              : 1;  /**< [ 28: 28](R/W) Enable tail drop when maximum DROP level exceeded. See also
                                                                 FPA_AURA()_POOL_LEVELS[DROP] and FPA_AURA()_CNT_LEVELS[DROP]. */
        uint64_t reserved_24_27        : 4;
        uint64_t strm                  : 8;  /**< [ 23: 16](R/W) Stream identifier bits \<7:0\>.

                                                                 Also indexes PKI_STRM()_CFG. PKI_STRM()_CFG[GMID] is needed to use
                                                                 PKI_QPG_TBL()[GRP_OK,GRP_BAD,LAURA]. */
        uint64_t reserved_10_15        : 6;
        uint64_t dstat_id              : 10; /**< [  9:  0](R/W) Deep statistic bucket to use for traffic to this QPG. This determines which
                                                                 index of PKI_DSTAT()_STAT0..PKI_DSTAT()_STAT4 will increment. Additionally, if
                                                                 PKI_STAT_CTL[MODE] = 0x2, then DSTAT_ID values 0-63 will increment
                                                                 PKI_STAT()_STAT0..PKI_STAT()_STAT18 and PKI_STAT()_HIST0..PKI_STAT()_HIST6. */
#else /* Word 0 - Little Endian */
        uint64_t dstat_id              : 10; /**< [  9:  0](R/W) Deep statistic bucket to use for traffic to this QPG. This determines which
                                                                 index of PKI_DSTAT()_STAT0..PKI_DSTAT()_STAT4 will increment. Additionally, if
                                                                 PKI_STAT_CTL[MODE] = 0x2, then DSTAT_ID values 0-63 will increment
                                                                 PKI_STAT()_STAT0..PKI_STAT()_STAT18 and PKI_STAT()_HIST0..PKI_STAT()_HIST6. */
        uint64_t reserved_10_15        : 6;
        uint64_t strm                  : 8;  /**< [ 23: 16](R/W) Stream identifier bits \<7:0\>.

                                                                 Also indexes PKI_STRM()_CFG. PKI_STRM()_CFG[GMID] is needed to use
                                                                 PKI_QPG_TBL()[GRP_OK,GRP_BAD,LAURA]. */
        uint64_t reserved_24_27        : 4;
        uint64_t ena_drop              : 1;  /**< [ 28: 28](R/W) Enable tail drop when maximum DROP level exceeded. See also
                                                                 FPA_AURA()_POOL_LEVELS[DROP] and FPA_AURA()_CNT_LEVELS[DROP]. */
        uint64_t ena_red               : 1;  /**< [ 29: 29](R/W) Enable RED drop between PASS and DROP levels. See also
                                                                 FPA_AURA()_POOL_LEVELS[RED_ENA] and FPA_AURA()_CNT_LEVELS[RED_ENA]. */
        uint64_t pkt_add               : 2;  /**< [ 31: 30](R/W) Specifies what to add to FPA_VHAURA()_CNT when PKI enqueues a packet:
                                                                   0x0 = zero.
                                                                   0x1 = one.
                                                                   0x2 = The number of FPA buffers allocated; i.e. if PKI_STYLE()_BUF[DIS_WQ_DAT]
                                                                   is set, PKI_WQE_S[BUFS]+1, else PKI_WQE_S[BUFS].
                                                                   0x3 = PKI_WQE_S[LEN] (i.e. the packet length). */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_qpg_tblbx_s cn; */
};
typedef union bdk_pki_qpg_tblbx bdk_pki_qpg_tblbx_t;

static inline uint64_t BDK_PKI_QPG_TBLBX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_QPG_TBLBX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=2047))
        return 0x86c000820000ll + 8ll * ((a) & 0x7ff);
    __bdk_csr_fatal("PKI_QPG_TBLBX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_QPG_TBLBX(a) bdk_pki_qpg_tblbx_t
#define bustype_BDK_PKI_QPG_TBLBX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_QPG_TBLBX(a) "PKI_QPG_TBLBX"
#define device_bar_BDK_PKI_QPG_TBLBX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_QPG_TBLBX(a) (a)
#define arguments_BDK_PKI_QPG_TBLBX(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_reasm_sop#
 *
 * PKI Reassembly ID SOP Register
 */
union bdk_pki_reasm_sopx
{
    uint64_t u;
    struct bdk_pki_reasm_sopx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t sop                   : 64; /**< [ 63:  0](RO/H) When set, a SOP was detected on a reassembly ID. When clear, a SOP has not yet been
                                                                 received, or an EOP was received on the reassembly ID. The total number of available
                                                                 reassembly IDs is described with the PKI_REASM_E::NUM_REASM enumeration. Not all
                                                                 bits are implemented. Only PKI_REASM_SOP(0)[SOP]\<18:0\>
                                                                 will be nonzero in this implementation. */
#else /* Word 0 - Little Endian */
        uint64_t sop                   : 64; /**< [ 63:  0](RO/H) When set, a SOP was detected on a reassembly ID. When clear, a SOP has not yet been
                                                                 received, or an EOP was received on the reassembly ID. The total number of available
                                                                 reassembly IDs is described with the PKI_REASM_E::NUM_REASM enumeration. Not all
                                                                 bits are implemented. Only PKI_REASM_SOP(0)[SOP]\<18:0\>
                                                                 will be nonzero in this implementation. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_reasm_sopx_s cn; */
};
typedef union bdk_pki_reasm_sopx bdk_pki_reasm_sopx_t;

static inline uint64_t BDK_PKI_REASM_SOPX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_REASM_SOPX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1))
        return 0x86c000006000ll + 8ll * ((a) & 0x1);
    __bdk_csr_fatal("PKI_REASM_SOPX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_REASM_SOPX(a) bdk_pki_reasm_sopx_t
#define bustype_BDK_PKI_REASM_SOPX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_REASM_SOPX(a) "PKI_REASM_SOPX"
#define device_bar_BDK_PKI_REASM_SOPX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_REASM_SOPX(a) (a)
#define arguments_BDK_PKI_REASM_SOPX(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_req_wgt
 *
 * PKI Request Weight Register
 * This register controls the round-robin weights between each PKI requestor. For diagnostic
 * tuning only.
 */
union bdk_pki_req_wgt
{
    uint64_t u;
    struct bdk_pki_req_wgt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t wgt8                  : 4;  /**< [ 35: 32](R/W) Reserved. */
        uint64_t wgt7                  : 4;  /**< [ 31: 28](R/W) Reserved. */
        uint64_t wgt6                  : 4;  /**< [ 27: 24](R/W) Weight for BGX3. */
        uint64_t wgt5                  : 4;  /**< [ 23: 20](R/W) Weight for BGX2. */
        uint64_t wgt4                  : 4;  /**< [ 19: 16](R/W) Weight for BGX1. */
        uint64_t wgt3                  : 4;  /**< [ 15: 12](R/W) Weight for BGX0. */
        uint64_t wgt2                  : 4;  /**< [ 11:  8](R/W) Weight for DPI. */
        uint64_t wgt1                  : 4;  /**< [  7:  4](R/W) Weight for LBK1. */
        uint64_t wgt0                  : 4;  /**< [  3:  0](R/W) Weight for LBK0. */
#else /* Word 0 - Little Endian */
        uint64_t wgt0                  : 4;  /**< [  3:  0](R/W) Weight for LBK0. */
        uint64_t wgt1                  : 4;  /**< [  7:  4](R/W) Weight for LBK1. */
        uint64_t wgt2                  : 4;  /**< [ 11:  8](R/W) Weight for DPI. */
        uint64_t wgt3                  : 4;  /**< [ 15: 12](R/W) Weight for BGX0. */
        uint64_t wgt4                  : 4;  /**< [ 19: 16](R/W) Weight for BGX1. */
        uint64_t wgt5                  : 4;  /**< [ 23: 20](R/W) Weight for BGX2. */
        uint64_t wgt6                  : 4;  /**< [ 27: 24](R/W) Weight for BGX3. */
        uint64_t wgt7                  : 4;  /**< [ 31: 28](R/W) Reserved. */
        uint64_t wgt8                  : 4;  /**< [ 35: 32](R/W) Reserved. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_req_wgt_s cn; */
};
typedef union bdk_pki_req_wgt bdk_pki_req_wgt_t;

#define BDK_PKI_REQ_WGT BDK_PKI_REQ_WGT_FUNC()
static inline uint64_t BDK_PKI_REQ_WGT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_REQ_WGT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000120ll;
    __bdk_csr_fatal("PKI_REQ_WGT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_REQ_WGT bdk_pki_req_wgt_t
#define bustype_BDK_PKI_REQ_WGT BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_REQ_WGT "PKI_REQ_WGT"
#define device_bar_BDK_PKI_REQ_WGT 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_REQ_WGT 0
#define arguments_BDK_PKI_REQ_WGT -1,-1,-1,-1

/**
 * Register (NCB) pki_sft_rst
 *
 * PKI Soft Reset Register
 * Internal:
 * Allows soft reset. See bug18607, PKI_SFT_RST definition, for further definition
 * (http://mcbuggin.caveonetworks.com/bug/18607).
 */
union bdk_pki_sft_rst
{
    uint64_t u;
    struct bdk_pki_sft_rst_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t busy                  : 1;  /**< [ 63: 63](RO/H) When set, PKI is busy completing reset. No access except the reading of this bit should
                                                                 occur to the PKI until this is clear.

                                                                 Internal:
                                                                 The BUSY bit for this implementation is a placeholder and is not required to be
                                                                 implemented in HW. The soft reset pulse is short enough that we can guarantee
                                                                 that reset will complete below a subsequent RSL reference can be made. It is
                                                                 still useful for this bit to exist in case that property every changes and the
                                                                 reset requires a longer duration. For this implementation, software will check
                                                                 the bit which will always report not BUSY allowing software to proceed with its
                                                                 flow. */
        uint64_t reserved_33_62        : 30;
        uint64_t active                : 1;  /**< [ 32: 32](RO/H) When set, PKI is actively processing packet traffic. It is recommended that software wait
                                                                 until ACTIVE is clear before setting RST.

                                                                 Internal:
                                                                 ACTIVE is an OR of PKI_ACTIVE0..2. */
        uint64_t reserved_1_31         : 31;
        uint64_t rst                   : 1;  /**< [  0:  0](R/W1/H) Reset. When set to 1 by software, PKI will produce an internal reset pulse. */
#else /* Word 0 - Little Endian */
        uint64_t rst                   : 1;  /**< [  0:  0](R/W1/H) Reset. When set to 1 by software, PKI will produce an internal reset pulse. */
        uint64_t reserved_1_31         : 31;
        uint64_t active                : 1;  /**< [ 32: 32](RO/H) When set, PKI is actively processing packet traffic. It is recommended that software wait
                                                                 until ACTIVE is clear before setting RST.

                                                                 Internal:
                                                                 ACTIVE is an OR of PKI_ACTIVE0..2. */
        uint64_t reserved_33_62        : 30;
        uint64_t busy                  : 1;  /**< [ 63: 63](RO/H) When set, PKI is busy completing reset. No access except the reading of this bit should
                                                                 occur to the PKI until this is clear.

                                                                 Internal:
                                                                 The BUSY bit for this implementation is a placeholder and is not required to be
                                                                 implemented in HW. The soft reset pulse is short enough that we can guarantee
                                                                 that reset will complete below a subsequent RSL reference can be made. It is
                                                                 still useful for this bit to exist in case that property every changes and the
                                                                 reset requires a longer duration. For this implementation, software will check
                                                                 the bit which will always report not BUSY allowing software to proceed with its
                                                                 flow. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_sft_rst_s cn; */
};
typedef union bdk_pki_sft_rst bdk_pki_sft_rst_t;

#define BDK_PKI_SFT_RST BDK_PKI_SFT_RST_FUNC()
static inline uint64_t BDK_PKI_SFT_RST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_SFT_RST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000020ll;
    __bdk_csr_fatal("PKI_SFT_RST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_SFT_RST bdk_pki_sft_rst_t
#define bustype_BDK_PKI_SFT_RST BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_SFT_RST "PKI_SFT_RST"
#define device_bar_BDK_PKI_SFT_RST 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_SFT_RST 0
#define arguments_BDK_PKI_SFT_RST -1,-1,-1,-1

/**
 * Register (NCB) pki_stat#_hist0
 *
 * PKI Histogram 0 Statistic Registers
 */
union bdk_pki_statx_hist0
{
    uint64_t u;
    struct bdk_pki_statx_hist0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t h1to63                : 48; /**< [ 47:  0](R/W/H) Number of non-dropped 1 to 63 byte packets. Packet length includes FCS and any prepended
                                                                 PTP timestamp. */
#else /* Word 0 - Little Endian */
        uint64_t h1to63                : 48; /**< [ 47:  0](R/W/H) Number of non-dropped 1 to 63 byte packets. Packet length includes FCS and any prepended
                                                                 PTP timestamp. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_hist0_s cn; */
};
typedef union bdk_pki_statx_hist0 bdk_pki_statx_hist0_t;

static inline uint64_t BDK_PKI_STATX_HIST0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_HIST0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e00000ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_HIST0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_HIST0(a) bdk_pki_statx_hist0_t
#define bustype_BDK_PKI_STATX_HIST0(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_HIST0(a) "PKI_STATX_HIST0"
#define device_bar_BDK_PKI_STATX_HIST0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_HIST0(a) (a)
#define arguments_BDK_PKI_STATX_HIST0(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_hist1
 *
 * PKI Histogram 1 Statistic Registers
 */
union bdk_pki_statx_hist1
{
    uint64_t u;
    struct bdk_pki_statx_hist1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t h64to127              : 48; /**< [ 47:  0](R/W/H) Number of non-dropped 64 to 127 byte packets. */
#else /* Word 0 - Little Endian */
        uint64_t h64to127              : 48; /**< [ 47:  0](R/W/H) Number of non-dropped 64 to 127 byte packets. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_hist1_s cn; */
};
typedef union bdk_pki_statx_hist1 bdk_pki_statx_hist1_t;

static inline uint64_t BDK_PKI_STATX_HIST1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_HIST1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e00008ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_HIST1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_HIST1(a) bdk_pki_statx_hist1_t
#define bustype_BDK_PKI_STATX_HIST1(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_HIST1(a) "PKI_STATX_HIST1"
#define device_bar_BDK_PKI_STATX_HIST1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_HIST1(a) (a)
#define arguments_BDK_PKI_STATX_HIST1(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_hist2
 *
 * PKI Histogram 2 Statistic Registers
 */
union bdk_pki_statx_hist2
{
    uint64_t u;
    struct bdk_pki_statx_hist2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t h128to255             : 48; /**< [ 47:  0](R/W/H) Number of non-dropped 128 to 255 byte packets. */
#else /* Word 0 - Little Endian */
        uint64_t h128to255             : 48; /**< [ 47:  0](R/W/H) Number of non-dropped 128 to 255 byte packets. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_hist2_s cn; */
};
typedef union bdk_pki_statx_hist2 bdk_pki_statx_hist2_t;

static inline uint64_t BDK_PKI_STATX_HIST2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_HIST2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e00010ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_HIST2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_HIST2(a) bdk_pki_statx_hist2_t
#define bustype_BDK_PKI_STATX_HIST2(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_HIST2(a) "PKI_STATX_HIST2"
#define device_bar_BDK_PKI_STATX_HIST2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_HIST2(a) (a)
#define arguments_BDK_PKI_STATX_HIST2(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_hist3
 *
 * PKI Histogram 3 Statistic Registers
 */
union bdk_pki_statx_hist3
{
    uint64_t u;
    struct bdk_pki_statx_hist3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t h256to511             : 48; /**< [ 47:  0](R/W/H) Number of non-dropped 256 to 511 byte packets. */
#else /* Word 0 - Little Endian */
        uint64_t h256to511             : 48; /**< [ 47:  0](R/W/H) Number of non-dropped 256 to 511 byte packets. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_hist3_s cn; */
};
typedef union bdk_pki_statx_hist3 bdk_pki_statx_hist3_t;

static inline uint64_t BDK_PKI_STATX_HIST3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_HIST3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e00018ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_HIST3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_HIST3(a) bdk_pki_statx_hist3_t
#define bustype_BDK_PKI_STATX_HIST3(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_HIST3(a) "PKI_STATX_HIST3"
#define device_bar_BDK_PKI_STATX_HIST3(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_HIST3(a) (a)
#define arguments_BDK_PKI_STATX_HIST3(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_hist4
 *
 * PKI Histogram 4 Statistic Registers
 */
union bdk_pki_statx_hist4
{
    uint64_t u;
    struct bdk_pki_statx_hist4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t h512to1023            : 48; /**< [ 47:  0](R/W/H) Number of non-dropped 512 to 1023 byte packets. */
#else /* Word 0 - Little Endian */
        uint64_t h512to1023            : 48; /**< [ 47:  0](R/W/H) Number of non-dropped 512 to 1023 byte packets. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_hist4_s cn; */
};
typedef union bdk_pki_statx_hist4 bdk_pki_statx_hist4_t;

static inline uint64_t BDK_PKI_STATX_HIST4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_HIST4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e00020ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_HIST4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_HIST4(a) bdk_pki_statx_hist4_t
#define bustype_BDK_PKI_STATX_HIST4(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_HIST4(a) "PKI_STATX_HIST4"
#define device_bar_BDK_PKI_STATX_HIST4(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_HIST4(a) (a)
#define arguments_BDK_PKI_STATX_HIST4(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_hist5
 *
 * PKI Histogram 5 Statistic Registers
 */
union bdk_pki_statx_hist5
{
    uint64_t u;
    struct bdk_pki_statx_hist5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t h1024to1518           : 48; /**< [ 47:  0](R/W/H) Number of non-dropped 1024 to 1518 byte packets. */
#else /* Word 0 - Little Endian */
        uint64_t h1024to1518           : 48; /**< [ 47:  0](R/W/H) Number of non-dropped 1024 to 1518 byte packets. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_hist5_s cn; */
};
typedef union bdk_pki_statx_hist5 bdk_pki_statx_hist5_t;

static inline uint64_t BDK_PKI_STATX_HIST5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_HIST5(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e00028ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_HIST5", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_HIST5(a) bdk_pki_statx_hist5_t
#define bustype_BDK_PKI_STATX_HIST5(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_HIST5(a) "PKI_STATX_HIST5"
#define device_bar_BDK_PKI_STATX_HIST5(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_HIST5(a) (a)
#define arguments_BDK_PKI_STATX_HIST5(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_hist6
 *
 * PKI Histogram 6 Statistic Registers
 */
union bdk_pki_statx_hist6
{
    uint64_t u;
    struct bdk_pki_statx_hist6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t h1519                 : 48; /**< [ 47:  0](R/W/H) Number of non-dropped 1519 byte and above packets. */
#else /* Word 0 - Little Endian */
        uint64_t h1519                 : 48; /**< [ 47:  0](R/W/H) Number of non-dropped 1519 byte and above packets. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_hist6_s cn; */
};
typedef union bdk_pki_statx_hist6 bdk_pki_statx_hist6_t;

static inline uint64_t BDK_PKI_STATX_HIST6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_HIST6(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e00030ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_HIST6", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_HIST6(a) bdk_pki_statx_hist6_t
#define bustype_BDK_PKI_STATX_HIST6(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_HIST6(a) "PKI_STATX_HIST6"
#define device_bar_BDK_PKI_STATX_HIST6(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_HIST6(a) (a)
#define arguments_BDK_PKI_STATX_HIST6(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_stat0
 *
 * PKI Packets Statistic Registers
 */
union bdk_pki_statx_stat0
{
    uint64_t u;
    struct bdk_pki_statx_stat0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t pkts                  : 48; /**< [ 47:  0](R/W/H) Number of non-dropped packets processed by PKI. */
#else /* Word 0 - Little Endian */
        uint64_t pkts                  : 48; /**< [ 47:  0](R/W/H) Number of non-dropped packets processed by PKI. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_stat0_s cn; */
};
typedef union bdk_pki_statx_stat0 bdk_pki_statx_stat0_t;

static inline uint64_t BDK_PKI_STATX_STAT0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_STAT0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e00038ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_STAT0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_STAT0(a) bdk_pki_statx_stat0_t
#define bustype_BDK_PKI_STATX_STAT0(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_STAT0(a) "PKI_STATX_STAT0"
#define device_bar_BDK_PKI_STATX_STAT0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_STAT0(a) (a)
#define arguments_BDK_PKI_STATX_STAT0(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_stat1
 *
 * PKI Octets Statistic Registers
 */
union bdk_pki_statx_stat1
{
    uint64_t u;
    struct bdk_pki_statx_stat1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t octs                  : 48; /**< [ 47:  0](R/W/H) Number of non-dropped octets received by PKI (good and bad). */
#else /* Word 0 - Little Endian */
        uint64_t octs                  : 48; /**< [ 47:  0](R/W/H) Number of non-dropped octets received by PKI (good and bad). */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_stat1_s cn; */
};
typedef union bdk_pki_statx_stat1 bdk_pki_statx_stat1_t;

static inline uint64_t BDK_PKI_STATX_STAT1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_STAT1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e00040ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_STAT1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_STAT1(a) bdk_pki_statx_stat1_t
#define bustype_BDK_PKI_STATX_STAT1(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_STAT1(a) "PKI_STATX_STAT1"
#define device_bar_BDK_PKI_STATX_STAT1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_STAT1(a) (a)
#define arguments_BDK_PKI_STATX_STAT1(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_stat10
 *
 * PKI Jabber Statistic Registers
 */
union bdk_pki_statx_stat10
{
    uint64_t u;
    struct bdk_pki_statx_stat10_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t jabber                : 48; /**< [ 47:  0](R/W/H) Number of non-dropped packets with length \> maximum and FCS error. */
#else /* Word 0 - Little Endian */
        uint64_t jabber                : 48; /**< [ 47:  0](R/W/H) Number of non-dropped packets with length \> maximum and FCS error. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_stat10_s cn; */
};
typedef union bdk_pki_statx_stat10 bdk_pki_statx_stat10_t;

static inline uint64_t BDK_PKI_STATX_STAT10(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_STAT10(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e00088ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_STAT10", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_STAT10(a) bdk_pki_statx_stat10_t
#define bustype_BDK_PKI_STATX_STAT10(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_STAT10(a) "PKI_STATX_STAT10"
#define device_bar_BDK_PKI_STATX_STAT10(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_STAT10(a) (a)
#define arguments_BDK_PKI_STATX_STAT10(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_stat11
 *
 * PKI Oversize Statistic Registers
 */
union bdk_pki_statx_stat11
{
    uint64_t u;
    struct bdk_pki_statx_stat11_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t oversz                : 48; /**< [ 47:  0](R/W/H) Number of non-dropped packets with length \> maximum and no FCS error. */
#else /* Word 0 - Little Endian */
        uint64_t oversz                : 48; /**< [ 47:  0](R/W/H) Number of non-dropped packets with length \> maximum and no FCS error. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_stat11_s cn; */
};
typedef union bdk_pki_statx_stat11 bdk_pki_statx_stat11_t;

static inline uint64_t BDK_PKI_STATX_STAT11(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_STAT11(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e00090ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_STAT11", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_STAT11(a) bdk_pki_statx_stat11_t
#define bustype_BDK_PKI_STATX_STAT11(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_STAT11(a) "PKI_STATX_STAT11"
#define device_bar_BDK_PKI_STATX_STAT11(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_STAT11(a) (a)
#define arguments_BDK_PKI_STATX_STAT11(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_stat12
 *
 * PKI L2 Error Statistic Registers
 */
union bdk_pki_statx_stat12
{
    uint64_t u;
    struct bdk_pki_statx_stat12_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t l2err                 : 48; /**< [ 47:  0](R/W/H) Number of non-dropped packets with receive errors (PKI_WQE_S[ERRLEV]==RE or L2) not
                                                                 covered by
                                                                 more specific length or FCS statistic error registers. */
#else /* Word 0 - Little Endian */
        uint64_t l2err                 : 48; /**< [ 47:  0](R/W/H) Number of non-dropped packets with receive errors (PKI_WQE_S[ERRLEV]==RE or L2) not
                                                                 covered by
                                                                 more specific length or FCS statistic error registers. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_stat12_s cn; */
};
typedef union bdk_pki_statx_stat12 bdk_pki_statx_stat12_t;

static inline uint64_t BDK_PKI_STATX_STAT12(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_STAT12(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e00098ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_STAT12", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_STAT12(a) bdk_pki_statx_stat12_t
#define bustype_BDK_PKI_STATX_STAT12(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_STAT12(a) "PKI_STATX_STAT12"
#define device_bar_BDK_PKI_STATX_STAT12(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_STAT12(a) (a)
#define arguments_BDK_PKI_STATX_STAT12(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_stat13
 *
 * PKI Special Statistic Registers
 */
union bdk_pki_statx_stat13
{
    uint64_t u;
    struct bdk_pki_statx_stat13_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t spec                  : 48; /**< [ 47:  0](R/W/H) Number of non-dropped packets with special handling (WEQ[SH] set). For profiling
                                                                 and diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t spec                  : 48; /**< [ 47:  0](R/W/H) Number of non-dropped packets with special handling (WEQ[SH] set). For profiling
                                                                 and diagnostic use only. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_stat13_s cn; */
};
typedef union bdk_pki_statx_stat13 bdk_pki_statx_stat13_t;

static inline uint64_t BDK_PKI_STATX_STAT13(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_STAT13(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e000a0ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_STAT13", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_STAT13(a) bdk_pki_statx_stat13_t
#define bustype_BDK_PKI_STATX_STAT13(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_STAT13(a) "PKI_STATX_STAT13"
#define device_bar_BDK_PKI_STATX_STAT13(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_STAT13(a) (a)
#define arguments_BDK_PKI_STATX_STAT13(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_stat14
 *
 * PKI Dropped L2 Broadcast Statistic Registers
 */
union bdk_pki_statx_stat14
{
    uint64_t u;
    struct bdk_pki_statx_stat14_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t drp_bcast             : 48; /**< [ 47:  0](R/W/H) Number of packets with L2 broadcast DMAC that were dropped by RED, buffer exhaustion, or
                                                                 PKI_CL()_STYLE()_CFG[DROP]. See PKI_WQE_S[L2B] for the definition of L2 broadcast. */
#else /* Word 0 - Little Endian */
        uint64_t drp_bcast             : 48; /**< [ 47:  0](R/W/H) Number of packets with L2 broadcast DMAC that were dropped by RED, buffer exhaustion, or
                                                                 PKI_CL()_STYLE()_CFG[DROP]. See PKI_WQE_S[L2B] for the definition of L2 broadcast. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_stat14_s cn; */
};
typedef union bdk_pki_statx_stat14 bdk_pki_statx_stat14_t;

static inline uint64_t BDK_PKI_STATX_STAT14(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_STAT14(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e000a8ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_STAT14", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_STAT14(a) bdk_pki_statx_stat14_t
#define bustype_BDK_PKI_STATX_STAT14(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_STAT14(a) "PKI_STATX_STAT14"
#define device_bar_BDK_PKI_STATX_STAT14(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_STAT14(a) (a)
#define arguments_BDK_PKI_STATX_STAT14(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_stat15
 *
 * PKI Dropped L2 Multicast Statistic Registers
 */
union bdk_pki_statx_stat15
{
    uint64_t u;
    struct bdk_pki_statx_stat15_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t drp_mcast             : 48; /**< [ 47:  0](R/W/H) Number of packets with L2 multicast DMAC that were dropped by RED, buffer exhaustion, or
                                                                 PKI_CL()_STYLE()_CFG[DROP]. See PKI_WQE_S[L2M] for the definition of L2 multicast. */
#else /* Word 0 - Little Endian */
        uint64_t drp_mcast             : 48; /**< [ 47:  0](R/W/H) Number of packets with L2 multicast DMAC that were dropped by RED, buffer exhaustion, or
                                                                 PKI_CL()_STYLE()_CFG[DROP]. See PKI_WQE_S[L2M] for the definition of L2 multicast. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_stat15_s cn; */
};
typedef union bdk_pki_statx_stat15 bdk_pki_statx_stat15_t;

static inline uint64_t BDK_PKI_STATX_STAT15(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_STAT15(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e000b0ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_STAT15", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_STAT15(a) bdk_pki_statx_stat15_t
#define bustype_BDK_PKI_STATX_STAT15(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_STAT15(a) "PKI_STATX_STAT15"
#define device_bar_BDK_PKI_STATX_STAT15(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_STAT15(a) (a)
#define arguments_BDK_PKI_STATX_STAT15(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_stat16
 *
 * PKI Dropped L3 Broadcast Statistic Registers
 */
union bdk_pki_statx_stat16
{
    uint64_t u;
    struct bdk_pki_statx_stat16_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t drp_bcast             : 48; /**< [ 47:  0](R/W/H) Number of packets with IPv4 L3 broadcast destination address that were dropped due to RED
                                                                 or buffer exhaustion. See PKI_WQE_S[L3B] for the definition of L2 multicast. */
#else /* Word 0 - Little Endian */
        uint64_t drp_bcast             : 48; /**< [ 47:  0](R/W/H) Number of packets with IPv4 L3 broadcast destination address that were dropped due to RED
                                                                 or buffer exhaustion. See PKI_WQE_S[L3B] for the definition of L2 multicast. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_stat16_s cn; */
};
typedef union bdk_pki_statx_stat16 bdk_pki_statx_stat16_t;

static inline uint64_t BDK_PKI_STATX_STAT16(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_STAT16(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e000b8ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_STAT16", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_STAT16(a) bdk_pki_statx_stat16_t
#define bustype_BDK_PKI_STATX_STAT16(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_STAT16(a) "PKI_STATX_STAT16"
#define device_bar_BDK_PKI_STATX_STAT16(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_STAT16(a) (a)
#define arguments_BDK_PKI_STATX_STAT16(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_stat17
 *
 * PKI Dropped L3 Multicast Statistic Registers
 */
union bdk_pki_statx_stat17
{
    uint64_t u;
    struct bdk_pki_statx_stat17_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t drp_mcast             : 48; /**< [ 47:  0](R/W/H) Number of packets with IPv4 or IPv6 L3 multicast destination address that were dropped due
                                                                 to RED or buffer exhaustion. See PKI_WQE_S[L3M] for the definition of L3 multicast. */
#else /* Word 0 - Little Endian */
        uint64_t drp_mcast             : 48; /**< [ 47:  0](R/W/H) Number of packets with IPv4 or IPv6 L3 multicast destination address that were dropped due
                                                                 to RED or buffer exhaustion. See PKI_WQE_S[L3M] for the definition of L3 multicast. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_stat17_s cn; */
};
typedef union bdk_pki_statx_stat17 bdk_pki_statx_stat17_t;

static inline uint64_t BDK_PKI_STATX_STAT17(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_STAT17(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e000c0ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_STAT17", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_STAT17(a) bdk_pki_statx_stat17_t
#define bustype_BDK_PKI_STATX_STAT17(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_STAT17(a) "PKI_STATX_STAT17"
#define device_bar_BDK_PKI_STATX_STAT17(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_STAT17(a) (a)
#define arguments_BDK_PKI_STATX_STAT17(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_stat18
 *
 * PKI Dropped Special Statistic Registers
 */
union bdk_pki_statx_stat18
{
    uint64_t u;
    struct bdk_pki_statx_stat18_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t drp_spec              : 48; /**< [ 47:  0](R/W/H) Number of packets dropped with special handling (PKI_WQE_S[SH] set). For
                                                                 profiling and diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t drp_spec              : 48; /**< [ 47:  0](R/W/H) Number of packets dropped with special handling (PKI_WQE_S[SH] set). For
                                                                 profiling and diagnostic use only. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_stat18_s cn; */
};
typedef union bdk_pki_statx_stat18 bdk_pki_statx_stat18_t;

static inline uint64_t BDK_PKI_STATX_STAT18(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_STAT18(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e000c8ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_STAT18", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_STAT18(a) bdk_pki_statx_stat18_t
#define bustype_BDK_PKI_STATX_STAT18(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_STAT18(a) "PKI_STATX_STAT18"
#define device_bar_BDK_PKI_STATX_STAT18(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_STAT18(a) (a)
#define arguments_BDK_PKI_STATX_STAT18(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_stat2
 *
 * PKI Raw Packets Statistic Registers
 */
union bdk_pki_statx_stat2
{
    uint64_t u;
    struct bdk_pki_statx_stat2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t raw                   : 48; /**< [ 47:  0](R/W/H) Number of non-dropped packets with PKI_WQE_S[RAW] set. */
#else /* Word 0 - Little Endian */
        uint64_t raw                   : 48; /**< [ 47:  0](R/W/H) Number of non-dropped packets with PKI_WQE_S[RAW] set. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_stat2_s cn; */
};
typedef union bdk_pki_statx_stat2 bdk_pki_statx_stat2_t;

static inline uint64_t BDK_PKI_STATX_STAT2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_STAT2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e00048ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_STAT2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_STAT2(a) bdk_pki_statx_stat2_t
#define bustype_BDK_PKI_STATX_STAT2(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_STAT2(a) "PKI_STATX_STAT2"
#define device_bar_BDK_PKI_STATX_STAT2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_STAT2(a) (a)
#define arguments_BDK_PKI_STATX_STAT2(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_stat3
 *
 * PKI Dropped Packets Statistic Registers
 */
union bdk_pki_statx_stat3
{
    uint64_t u;
    struct bdk_pki_statx_stat3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t drp_pkts              : 48; /**< [ 47:  0](R/W/H) Inbound packets dropped by RED, buffer exhaustion, or PKI_CL()_STYLE()_CFG[DROP]. */
#else /* Word 0 - Little Endian */
        uint64_t drp_pkts              : 48; /**< [ 47:  0](R/W/H) Inbound packets dropped by RED, buffer exhaustion, or PKI_CL()_STYLE()_CFG[DROP]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_stat3_s cn; */
};
typedef union bdk_pki_statx_stat3 bdk_pki_statx_stat3_t;

static inline uint64_t BDK_PKI_STATX_STAT3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_STAT3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e00050ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_STAT3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_STAT3(a) bdk_pki_statx_stat3_t
#define bustype_BDK_PKI_STATX_STAT3(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_STAT3(a) "PKI_STATX_STAT3"
#define device_bar_BDK_PKI_STATX_STAT3(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_STAT3(a) (a)
#define arguments_BDK_PKI_STATX_STAT3(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_stat4
 *
 * PKI Dropped Octets Statistic Registers
 */
union bdk_pki_statx_stat4
{
    uint64_t u;
    struct bdk_pki_statx_stat4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t drp_octs              : 48; /**< [ 47:  0](R/W/H) Inbound octets dropped by RED, buffer exhaustion, or PKI_CL()_STYLE()_CFG[DROP]. */
#else /* Word 0 - Little Endian */
        uint64_t drp_octs              : 48; /**< [ 47:  0](R/W/H) Inbound octets dropped by RED, buffer exhaustion, or PKI_CL()_STYLE()_CFG[DROP]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_stat4_s cn; */
};
typedef union bdk_pki_statx_stat4 bdk_pki_statx_stat4_t;

static inline uint64_t BDK_PKI_STATX_STAT4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_STAT4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e00058ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_STAT4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_STAT4(a) bdk_pki_statx_stat4_t
#define bustype_BDK_PKI_STATX_STAT4(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_STAT4(a) "PKI_STATX_STAT4"
#define device_bar_BDK_PKI_STATX_STAT4(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_STAT4(a) (a)
#define arguments_BDK_PKI_STATX_STAT4(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_stat5
 *
 * PKI L2 Broadcast Statistic Registers
 */
union bdk_pki_statx_stat5
{
    uint64_t u;
    struct bdk_pki_statx_stat5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t bcast                 : 48; /**< [ 47:  0](R/W/H) Number of non-dropped L2 broadcast packets. Does not include multicast packets. See
                                                                 PKI_WQE_S[L2B] for the definition of L2 broadcast. */
#else /* Word 0 - Little Endian */
        uint64_t bcast                 : 48; /**< [ 47:  0](R/W/H) Number of non-dropped L2 broadcast packets. Does not include multicast packets. See
                                                                 PKI_WQE_S[L2B] for the definition of L2 broadcast. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_stat5_s cn; */
};
typedef union bdk_pki_statx_stat5 bdk_pki_statx_stat5_t;

static inline uint64_t BDK_PKI_STATX_STAT5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_STAT5(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e00060ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_STAT5", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_STAT5(a) bdk_pki_statx_stat5_t
#define bustype_BDK_PKI_STATX_STAT5(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_STAT5(a) "PKI_STATX_STAT5"
#define device_bar_BDK_PKI_STATX_STAT5(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_STAT5(a) (a)
#define arguments_BDK_PKI_STATX_STAT5(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_stat6
 *
 * PKI L2 Multicast Statistic Registers
 */
union bdk_pki_statx_stat6
{
    uint64_t u;
    struct bdk_pki_statx_stat6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t mcast                 : 48; /**< [ 47:  0](R/W/H) Number of non-dropped L2 multicast packets. Does not include broadcast packets. See
                                                                 PKI_WQE_S[L2M] for the definition of L2 multicast. */
#else /* Word 0 - Little Endian */
        uint64_t mcast                 : 48; /**< [ 47:  0](R/W/H) Number of non-dropped L2 multicast packets. Does not include broadcast packets. See
                                                                 PKI_WQE_S[L2M] for the definition of L2 multicast. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_stat6_s cn; */
};
typedef union bdk_pki_statx_stat6 bdk_pki_statx_stat6_t;

static inline uint64_t BDK_PKI_STATX_STAT6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_STAT6(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e00068ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_STAT6", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_STAT6(a) bdk_pki_statx_stat6_t
#define bustype_BDK_PKI_STATX_STAT6(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_STAT6(a) "PKI_STATX_STAT6"
#define device_bar_BDK_PKI_STATX_STAT6(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_STAT6(a) (a)
#define arguments_BDK_PKI_STATX_STAT6(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_stat7
 *
 * PKI FCS Statistic Registers
 */
union bdk_pki_statx_stat7
{
    uint64_t u;
    struct bdk_pki_statx_stat7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t fcs                   : 48; /**< [ 47:  0](R/W/H) Number of non-dropped packets with an FCS opcode error, excluding fragments or overruns. */
#else /* Word 0 - Little Endian */
        uint64_t fcs                   : 48; /**< [ 47:  0](R/W/H) Number of non-dropped packets with an FCS opcode error, excluding fragments or overruns. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_stat7_s cn; */
};
typedef union bdk_pki_statx_stat7 bdk_pki_statx_stat7_t;

static inline uint64_t BDK_PKI_STATX_STAT7(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_STAT7(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e00070ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_STAT7", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_STAT7(a) bdk_pki_statx_stat7_t
#define bustype_BDK_PKI_STATX_STAT7(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_STAT7(a) "PKI_STATX_STAT7"
#define device_bar_BDK_PKI_STATX_STAT7(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_STAT7(a) (a)
#define arguments_BDK_PKI_STATX_STAT7(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_stat8
 *
 * PKI Frac Statistic Registers
 */
union bdk_pki_statx_stat8
{
    uint64_t u;
    struct bdk_pki_statx_stat8_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t frag                  : 48; /**< [ 47:  0](R/W/H) Number of non-dropped packets with length \< minimum and FCS error */
#else /* Word 0 - Little Endian */
        uint64_t frag                  : 48; /**< [ 47:  0](R/W/H) Number of non-dropped packets with length \< minimum and FCS error */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_stat8_s cn; */
};
typedef union bdk_pki_statx_stat8 bdk_pki_statx_stat8_t;

static inline uint64_t BDK_PKI_STATX_STAT8(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_STAT8(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e00078ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_STAT8", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_STAT8(a) bdk_pki_statx_stat8_t
#define bustype_BDK_PKI_STATX_STAT8(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_STAT8(a) "PKI_STATX_STAT8"
#define device_bar_BDK_PKI_STATX_STAT8(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_STAT8(a) (a)
#define arguments_BDK_PKI_STATX_STAT8(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat#_stat9
 *
 * PKI Undersize Statistic Registers
 */
union bdk_pki_statx_stat9
{
    uint64_t u;
    struct bdk_pki_statx_stat9_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t undersz               : 48; /**< [ 47:  0](R/W/H) Number of non-dropped packets with length \< minimum and no FCS error. */
#else /* Word 0 - Little Endian */
        uint64_t undersz               : 48; /**< [ 47:  0](R/W/H) Number of non-dropped packets with length \< minimum and no FCS error. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_statx_stat9_s cn; */
};
typedef union bdk_pki_statx_stat9 bdk_pki_statx_stat9_t;

static inline uint64_t BDK_PKI_STATX_STAT9(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STATX_STAT9(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000e00080ll + 0x100ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STATX_STAT9", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STATX_STAT9(a) bdk_pki_statx_stat9_t
#define bustype_BDK_PKI_STATX_STAT9(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STATX_STAT9(a) "PKI_STATX_STAT9"
#define device_bar_BDK_PKI_STATX_STAT9(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STATX_STAT9(a) (a)
#define arguments_BDK_PKI_STATX_STAT9(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_stat_ctl
 *
 * PKI Stat Control Register
 * This register controls how the PKI statistics counters are handled.
 */
union bdk_pki_stat_ctl
{
    uint64_t u;
    struct bdk_pki_stat_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t mode                  : 2;  /**< [  1:  0](R/W) The PKI_STAT*_X registers can be indexed either by port kind (pkind), or final style.
                                                                 (Does not apply to the PKI_STAT_INB* nor PKI_DSTAT_* registers.)

                                                                 _ 0x0 = X represents the packet's pkind.
                                                                 _ 0x1 = X represents the low 6-bits of packet's final style.
                                                                 _ 0x2 = X represents the packet's PKI_QPG_TBLB()[DSTAT_ID].
                                                                   PKI_STAT()_STAT0..PKI_STAT()_STAT18 and PKI_STAT()_HIST0..PKI_STAT()_HIST6 will only
                                                                   be incremented if the DSTAT_ID is less than 64; i.e. fits in the index of the
                                                                   PKI_STAT()_STAT0 etc.
                                                                 _ 0x3 = Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t mode                  : 2;  /**< [  1:  0](R/W) The PKI_STAT*_X registers can be indexed either by port kind (pkind), or final style.
                                                                 (Does not apply to the PKI_STAT_INB* nor PKI_DSTAT_* registers.)

                                                                 _ 0x0 = X represents the packet's pkind.
                                                                 _ 0x1 = X represents the low 6-bits of packet's final style.
                                                                 _ 0x2 = X represents the packet's PKI_QPG_TBLB()[DSTAT_ID].
                                                                   PKI_STAT()_STAT0..PKI_STAT()_STAT18 and PKI_STAT()_HIST0..PKI_STAT()_HIST6 will only
                                                                   be incremented if the DSTAT_ID is less than 64; i.e. fits in the index of the
                                                                   PKI_STAT()_STAT0 etc.
                                                                 _ 0x3 = Reserved. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_stat_ctl_s cn; */
};
typedef union bdk_pki_stat_ctl bdk_pki_stat_ctl_t;

#define BDK_PKI_STAT_CTL BDK_PKI_STAT_CTL_FUNC()
static inline uint64_t BDK_PKI_STAT_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STAT_CTL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000110ll;
    __bdk_csr_fatal("PKI_STAT_CTL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STAT_CTL bdk_pki_stat_ctl_t
#define bustype_BDK_PKI_STAT_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STAT_CTL "PKI_STAT_CTL"
#define device_bar_BDK_PKI_STAT_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STAT_CTL 0
#define arguments_BDK_PKI_STAT_CTL -1,-1,-1,-1

/**
 * Register (NCB) pki_strm#_cfg
 *
 * PKI Stream ID Configuration Register
 * This register configures each stream. PKO indexes this array with
 * PKI_QPG_TBLB()[STRM].
 */
union bdk_pki_strmx_cfg
{
    uint64_t u;
    struct bdk_pki_strmx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t gmid                  : 16; /**< [ 15:  0](R/W) Guest machine identifier. The GMID to send to FPA for all
                                                                 buffer allocations/frees, or to SSO for all submit work operations related to
                                                                 PKI_QPG_TBL()[LAURA,GRP_OK,GRP_BAD].
                                                                 Must be nonzero or FPA/SSO will drop requests; see FPA_PF_MAP() and SSO_PF_MAP().

                                                                 To reconfigure see PKI_PBE_PCE_FLUSH_DETECT[FLUSH_STATE]. */
#else /* Word 0 - Little Endian */
        uint64_t gmid                  : 16; /**< [ 15:  0](R/W) Guest machine identifier. The GMID to send to FPA for all
                                                                 buffer allocations/frees, or to SSO for all submit work operations related to
                                                                 PKI_QPG_TBL()[LAURA,GRP_OK,GRP_BAD].
                                                                 Must be nonzero or FPA/SSO will drop requests; see FPA_PF_MAP() and SSO_PF_MAP().

                                                                 To reconfigure see PKI_PBE_PCE_FLUSH_DETECT[FLUSH_STATE]. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_strmx_cfg_s cn; */
};
typedef union bdk_pki_strmx_cfg bdk_pki_strmx_cfg_t;

static inline uint64_t BDK_PKI_STRMX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STRMX_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=255))
        return 0x86c000840000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("PKI_STRMX_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STRMX_CFG(a) bdk_pki_strmx_cfg_t
#define bustype_BDK_PKI_STRMX_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STRMX_CFG(a) "PKI_STRMX_CFG"
#define device_bar_BDK_PKI_STRMX_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STRMX_CFG(a) (a)
#define arguments_BDK_PKI_STRMX_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_strm_flt#_int
 *
 * PKI Stream Fault Interrupt Registers
 * This register is indexed by the faulting stream ID \<7:6\>.
 */
union bdk_pki_strm_fltx_int
{
    uint64_t u;
    struct bdk_pki_strm_fltx_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t strm_id               : 64; /**< [ 63:  0](R/W1C/H) NCB store fault. Each bit is set when the corresponding stream ID \<5:0\> receives
                                                                 a store fault from the NCB bus. */
#else /* Word 0 - Little Endian */
        uint64_t strm_id               : 64; /**< [ 63:  0](R/W1C/H) NCB store fault. Each bit is set when the corresponding stream ID \<5:0\> receives
                                                                 a store fault from the NCB bus. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_strm_fltx_int_s cn; */
};
typedef union bdk_pki_strm_fltx_int bdk_pki_strm_fltx_int_t;

static inline uint64_t BDK_PKI_STRM_FLTX_INT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STRM_FLTX_INT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x86c000000980ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("PKI_STRM_FLTX_INT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STRM_FLTX_INT(a) bdk_pki_strm_fltx_int_t
#define bustype_BDK_PKI_STRM_FLTX_INT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STRM_FLTX_INT(a) "PKI_STRM_FLTX_INT"
#define device_bar_BDK_PKI_STRM_FLTX_INT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STRM_FLTX_INT(a) (a)
#define arguments_BDK_PKI_STRM_FLTX_INT(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_strm_flt#_int_ena_w1c
 *
 * PKI Stream Fault Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_pki_strm_fltx_int_ena_w1c
{
    uint64_t u;
    struct bdk_pki_strm_fltx_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t strm_id               : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for PKI_STRM_FLT(0..3)_INT[STRM_ID]. */
#else /* Word 0 - Little Endian */
        uint64_t strm_id               : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for PKI_STRM_FLT(0..3)_INT[STRM_ID]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_strm_fltx_int_ena_w1c_s cn; */
};
typedef union bdk_pki_strm_fltx_int_ena_w1c bdk_pki_strm_fltx_int_ena_w1c_t;

static inline uint64_t BDK_PKI_STRM_FLTX_INT_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STRM_FLTX_INT_ENA_W1C(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x86c0000009c0ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("PKI_STRM_FLTX_INT_ENA_W1C", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STRM_FLTX_INT_ENA_W1C(a) bdk_pki_strm_fltx_int_ena_w1c_t
#define bustype_BDK_PKI_STRM_FLTX_INT_ENA_W1C(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STRM_FLTX_INT_ENA_W1C(a) "PKI_STRM_FLTX_INT_ENA_W1C"
#define device_bar_BDK_PKI_STRM_FLTX_INT_ENA_W1C(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STRM_FLTX_INT_ENA_W1C(a) (a)
#define arguments_BDK_PKI_STRM_FLTX_INT_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_strm_flt#_int_ena_w1s
 *
 * PKI Stream Fault Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_pki_strm_fltx_int_ena_w1s
{
    uint64_t u;
    struct bdk_pki_strm_fltx_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t strm_id               : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for PKI_STRM_FLT(0..3)_INT[STRM_ID]. */
#else /* Word 0 - Little Endian */
        uint64_t strm_id               : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for PKI_STRM_FLT(0..3)_INT[STRM_ID]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_strm_fltx_int_ena_w1s_s cn; */
};
typedef union bdk_pki_strm_fltx_int_ena_w1s bdk_pki_strm_fltx_int_ena_w1s_t;

static inline uint64_t BDK_PKI_STRM_FLTX_INT_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STRM_FLTX_INT_ENA_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x86c0000009e0ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("PKI_STRM_FLTX_INT_ENA_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STRM_FLTX_INT_ENA_W1S(a) bdk_pki_strm_fltx_int_ena_w1s_t
#define bustype_BDK_PKI_STRM_FLTX_INT_ENA_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STRM_FLTX_INT_ENA_W1S(a) "PKI_STRM_FLTX_INT_ENA_W1S"
#define device_bar_BDK_PKI_STRM_FLTX_INT_ENA_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STRM_FLTX_INT_ENA_W1S(a) (a)
#define arguments_BDK_PKI_STRM_FLTX_INT_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_strm_flt#_int_w1s
 *
 * PKI Stream Fault Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_pki_strm_fltx_int_w1s
{
    uint64_t u;
    struct bdk_pki_strm_fltx_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t strm_id               : 64; /**< [ 63:  0](R/W1S/H) Reads or sets PKI_STRM_FLT(0..3)_INT[STRM_ID]. */
#else /* Word 0 - Little Endian */
        uint64_t strm_id               : 64; /**< [ 63:  0](R/W1S/H) Reads or sets PKI_STRM_FLT(0..3)_INT[STRM_ID]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_strm_fltx_int_w1s_s cn; */
};
typedef union bdk_pki_strm_fltx_int_w1s bdk_pki_strm_fltx_int_w1s_t;

static inline uint64_t BDK_PKI_STRM_FLTX_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STRM_FLTX_INT_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x86c0000009a0ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("PKI_STRM_FLTX_INT_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STRM_FLTX_INT_W1S(a) bdk_pki_strm_fltx_int_w1s_t
#define bustype_BDK_PKI_STRM_FLTX_INT_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STRM_FLTX_INT_W1S(a) "PKI_STRM_FLTX_INT_W1S"
#define device_bar_BDK_PKI_STRM_FLTX_INT_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STRM_FLTX_INT_W1S(a) (a)
#define arguments_BDK_PKI_STRM_FLTX_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_style#_buf
 *
 * PKI Per-Style Buffer Configuration Register
 * This register configures the PKI BE skip amounts and other information.
 * It is indexed by final style, PKI_WQE_S[STYLE]\<5:0\>.
 *
 * Internal:
 * This CSR is really indexed by PKI_BEWQ_S[STYLE]\<5:0\>, which should match
 * PKI_WQE_S[STYLE]\<5:0\>.
 */
union bdk_pki_stylex_buf
{
    uint64_t u;
    struct bdk_pki_stylex_buf_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t wqe_bend              : 1;  /**< [ 32: 32](R/W) WQE header big-endian. Changes write operations of PKI_WQE_S and PKI_BUFLINK_S
                                                                 to L2C to be big-endian. Does not change the data, which is properly endian
                                                                 neutral (as ARM is byte-invariant). Also does not change the PKI_INST_HDR_S
                                                                 format in memory. */
        uint64_t wqe_hsz               : 2;  /**< [ 31: 30](R/W) Work queue header size:
                                                                 0x0 = WORD0..5, standard PKI_WQE_S.
                                                                 0x1 = Reserved.
                                                                 0x2 = Reserved.
                                                                 0x3 = Reserved.

                                                                 Selects which parse engine words are transferred to the PKI BE. If a word is not
                                                                 transferred and the word will reach memory (FIRST_SKIP is greater than that word
                                                                 number), then the final WQE memory word will be zero, not the parse engine register
                                                                 contents. */
        uint64_t wqe_skip              : 2;  /**< [ 29: 28](R/W) WQE start offset. The number of 128-byte cache lines to skip between the buffer
                                                                 pointer and WORD0 of the work-queue entry.

                                                                 If [DIS_WQ_DAT]=1, legal values must satisfy:
                                                                   * [MB_SIZE] \>= (PKI_STYLE()_BUF[WQE_SKIP] * (128/8)) + 18

                                                                 If [DIS_WQ_DAT]=0, legal values must satisfy:
                                                                   * ([WQE_SKIP] * (128/8)) + 6 \<= [FIRST_SKIP], to ensure the minimum of six
                                                                     work-queue entry words will fit within [FIRST_SKIP]. */
        uint64_t first_skip            : 6;  /**< [ 27: 22](R/W) The number of eight-byte words from the top of the first MBUF that the PKI
                                                                 stores the next pointer.

                                                                 [FIRST_SKIP] must be even, so the [FIRST_SKIP] distance must be a multiple
                                                                 of 16 bytes.

                                                                 If [DIS_WQ_DAT]=1, legal values must satisfy:
                                                                   * [FIRST_SKIP] \<= PKI_STYLE()_BUF[MB_SIZE] - 18.

                                                                 If [DIS_WQ_DAT]=0, legal values must satisfy:
                                                                   * [FIRST_SKIP] \<= PKI_STYLE()_BUF[MB_SIZE] - 18.
                                                                   * ([WQE_SKIP] * (128/8)) + X \<= [FIRST_SKIP].
                                                                   _ X must be at least 0x6 to ensure the minimum of six work-queue entry words. */
        uint64_t later_skip            : 6;  /**< [ 21: 16](R/W) The number of eight-byte words from the top of any MBUF that is not the first
                                                                 MBUF that PKI writes the next-pointer to.

                                                                 [LATER_SKIP] must be even, so the [LATER_SKIP] distance must be a multiple
                                                                 of 16 bytes.

                                                                 Legal [LATER_SKIP] values are even numbers 0 to PKI_STYLE()_BUF[MB_SIZE] - 18. */
        uint64_t opc_mode              : 2;  /**< [ 15: 14](R/W) Select the style of write to the L2C.
                                                                 0x0 = all packet data and next-buffer pointers are written through to memory.
                                                                 0x1 = all packet data and next-buffer pointers are written into the cache.
                                                                 0x2 = the first aligned cache block holding the WQE and/or front packet data are written
                                                                 to
                                                                 the L2 cache. All remaining cache blocks are not written to the L2 cache.
                                                                 0x3 = the first two aligned cache blocks holding the WQE and front packet data are written
                                                                 to the L2 cache. All remaining cache blocks are not written to the L2 cache. */
        uint64_t dis_wq_dat            : 1;  /**< [ 13: 13](R/W) Separate first data buffer from the work queue entry.
                                                                 0 = The packet link pointer will be at word [FIRST_SKIP] immediately followed by packet
                                                                 data, in the same buffer as the work queue entry.
                                                                 1 = The packet link pointer will be at word [FIRST_SKIP] in a new buffer separate from the
                                                                 work queue entry. Words following the WQE in the same cache line will be zeroed, other
                                                                 lines in the buffer will not be modified and will retain stale data (from the buffer's
                                                                 previous use). This setting may decrease the peak PKI performance by up to half on small
                                                                 packets. */
        uint64_t mb_size               : 13; /**< [ 12:  0](R/W) The number of eight-byte words between the start of a buffer and the last word
                                                                 that PKI may write into that buffer. The total amount of data stored by PKI into
                                                                 the buffer will be MB_SIZE minus FIRST_SKIP or LATER_SKIP.

                                                                 [MB_SIZE] must be even, so the [MB_SIZE] distance must be a multiple
                                                                 of 16 bytes.

                                                                 Legal [MB_SIZE] values are even numbers in the range of 32 to 4096. This must be
                                                                 less than or equal to the maximum size of every free page in every FPA pool this
                                                                 style may use.

                                                                 If [DIS_WQ_DAT]=1, legal values must satisfy:
                                                                   * MB_SIZE \>= (PKI_STYLE()_BUF[WQE_SKIP] * (128/8)) + 18
                                                                   * MB_SIZE \>= PKI_STYLE()_BUF[FIRST_SKIP] + 18.
                                                                   * MB_SIZE \>= PKI_STYLE()_BUF[LATER_SKIP] + 18.

                                                                 If [DIS_WQ_DAT]=0, legal values must satisfy:
                                                                   * MB_SIZE \>= PKI_STYLE()_BUF[FIRST_SKIP] + 18.
                                                                   * MB_SIZE \>= PKI_STYLE()_BUF[LATER_SKIP] + 18. */
#else /* Word 0 - Little Endian */
        uint64_t mb_size               : 13; /**< [ 12:  0](R/W) The number of eight-byte words between the start of a buffer and the last word
                                                                 that PKI may write into that buffer. The total amount of data stored by PKI into
                                                                 the buffer will be MB_SIZE minus FIRST_SKIP or LATER_SKIP.

                                                                 [MB_SIZE] must be even, so the [MB_SIZE] distance must be a multiple
                                                                 of 16 bytes.

                                                                 Legal [MB_SIZE] values are even numbers in the range of 32 to 4096. This must be
                                                                 less than or equal to the maximum size of every free page in every FPA pool this
                                                                 style may use.

                                                                 If [DIS_WQ_DAT]=1, legal values must satisfy:
                                                                   * MB_SIZE \>= (PKI_STYLE()_BUF[WQE_SKIP] * (128/8)) + 18
                                                                   * MB_SIZE \>= PKI_STYLE()_BUF[FIRST_SKIP] + 18.
                                                                   * MB_SIZE \>= PKI_STYLE()_BUF[LATER_SKIP] + 18.

                                                                 If [DIS_WQ_DAT]=0, legal values must satisfy:
                                                                   * MB_SIZE \>= PKI_STYLE()_BUF[FIRST_SKIP] + 18.
                                                                   * MB_SIZE \>= PKI_STYLE()_BUF[LATER_SKIP] + 18. */
        uint64_t dis_wq_dat            : 1;  /**< [ 13: 13](R/W) Separate first data buffer from the work queue entry.
                                                                 0 = The packet link pointer will be at word [FIRST_SKIP] immediately followed by packet
                                                                 data, in the same buffer as the work queue entry.
                                                                 1 = The packet link pointer will be at word [FIRST_SKIP] in a new buffer separate from the
                                                                 work queue entry. Words following the WQE in the same cache line will be zeroed, other
                                                                 lines in the buffer will not be modified and will retain stale data (from the buffer's
                                                                 previous use). This setting may decrease the peak PKI performance by up to half on small
                                                                 packets. */
        uint64_t opc_mode              : 2;  /**< [ 15: 14](R/W) Select the style of write to the L2C.
                                                                 0x0 = all packet data and next-buffer pointers are written through to memory.
                                                                 0x1 = all packet data and next-buffer pointers are written into the cache.
                                                                 0x2 = the first aligned cache block holding the WQE and/or front packet data are written
                                                                 to
                                                                 the L2 cache. All remaining cache blocks are not written to the L2 cache.
                                                                 0x3 = the first two aligned cache blocks holding the WQE and front packet data are written
                                                                 to the L2 cache. All remaining cache blocks are not written to the L2 cache. */
        uint64_t later_skip            : 6;  /**< [ 21: 16](R/W) The number of eight-byte words from the top of any MBUF that is not the first
                                                                 MBUF that PKI writes the next-pointer to.

                                                                 [LATER_SKIP] must be even, so the [LATER_SKIP] distance must be a multiple
                                                                 of 16 bytes.

                                                                 Legal [LATER_SKIP] values are even numbers 0 to PKI_STYLE()_BUF[MB_SIZE] - 18. */
        uint64_t first_skip            : 6;  /**< [ 27: 22](R/W) The number of eight-byte words from the top of the first MBUF that the PKI
                                                                 stores the next pointer.

                                                                 [FIRST_SKIP] must be even, so the [FIRST_SKIP] distance must be a multiple
                                                                 of 16 bytes.

                                                                 If [DIS_WQ_DAT]=1, legal values must satisfy:
                                                                   * [FIRST_SKIP] \<= PKI_STYLE()_BUF[MB_SIZE] - 18.

                                                                 If [DIS_WQ_DAT]=0, legal values must satisfy:
                                                                   * [FIRST_SKIP] \<= PKI_STYLE()_BUF[MB_SIZE] - 18.
                                                                   * ([WQE_SKIP] * (128/8)) + X \<= [FIRST_SKIP].
                                                                   _ X must be at least 0x6 to ensure the minimum of six work-queue entry words. */
        uint64_t wqe_skip              : 2;  /**< [ 29: 28](R/W) WQE start offset. The number of 128-byte cache lines to skip between the buffer
                                                                 pointer and WORD0 of the work-queue entry.

                                                                 If [DIS_WQ_DAT]=1, legal values must satisfy:
                                                                   * [MB_SIZE] \>= (PKI_STYLE()_BUF[WQE_SKIP] * (128/8)) + 18

                                                                 If [DIS_WQ_DAT]=0, legal values must satisfy:
                                                                   * ([WQE_SKIP] * (128/8)) + 6 \<= [FIRST_SKIP], to ensure the minimum of six
                                                                     work-queue entry words will fit within [FIRST_SKIP]. */
        uint64_t wqe_hsz               : 2;  /**< [ 31: 30](R/W) Work queue header size:
                                                                 0x0 = WORD0..5, standard PKI_WQE_S.
                                                                 0x1 = Reserved.
                                                                 0x2 = Reserved.
                                                                 0x3 = Reserved.

                                                                 Selects which parse engine words are transferred to the PKI BE. If a word is not
                                                                 transferred and the word will reach memory (FIRST_SKIP is greater than that word
                                                                 number), then the final WQE memory word will be zero, not the parse engine register
                                                                 contents. */
        uint64_t wqe_bend              : 1;  /**< [ 32: 32](R/W) WQE header big-endian. Changes write operations of PKI_WQE_S and PKI_BUFLINK_S
                                                                 to L2C to be big-endian. Does not change the data, which is properly endian
                                                                 neutral (as ARM is byte-invariant). Also does not change the PKI_INST_HDR_S
                                                                 format in memory. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_stylex_buf_s cn; */
};
typedef union bdk_pki_stylex_buf bdk_pki_stylex_buf_t;

static inline uint64_t BDK_PKI_STYLEX_BUF(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STYLEX_BUF(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000024000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STYLEX_BUF", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STYLEX_BUF(a) bdk_pki_stylex_buf_t
#define bustype_BDK_PKI_STYLEX_BUF(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STYLEX_BUF(a) "PKI_STYLEX_BUF"
#define device_bar_BDK_PKI_STYLEX_BUF(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STYLEX_BUF(a) (a)
#define arguments_BDK_PKI_STYLEX_BUF(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_style#_tag_mask
 *
 * PKI Per-Style Tag Generation Mask Registers
 * This register configures the PKI BE tag algorithm.
 * It is indexed by final style, PKI_WQE_S[STYLE]\<5:0\>.
 *
 * Internal:
 * This CSR is really indexed by PKI_BEWQ_S[STYLE]\<5:0\>, which should match
 * PKI_WQE_S[STYLE]\<5:0\>.
 */
union bdk_pki_stylex_tag_mask
{
    uint64_t u;
    struct bdk_pki_stylex_tag_mask_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t mask                  : 16; /**< [ 15:  0](R/W) When set, each bit excludes corresponding bit of the tuple computed tag from being
                                                                 included in the final tag. PKI_CL()_STYLE()_CFG2 [TAG_MASKEN] must be set. Does
                                                                 not affect tags from packets with a PKI_INST_HDR_S when PKI_INST_HDR_S[UTAG] is set. */
#else /* Word 0 - Little Endian */
        uint64_t mask                  : 16; /**< [ 15:  0](R/W) When set, each bit excludes corresponding bit of the tuple computed tag from being
                                                                 included in the final tag. PKI_CL()_STYLE()_CFG2 [TAG_MASKEN] must be set. Does
                                                                 not affect tags from packets with a PKI_INST_HDR_S when PKI_INST_HDR_S[UTAG] is set. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_stylex_tag_mask_s cn; */
};
typedef union bdk_pki_stylex_tag_mask bdk_pki_stylex_tag_mask_t;

static inline uint64_t BDK_PKI_STYLEX_TAG_MASK(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STYLEX_TAG_MASK(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000021000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STYLEX_TAG_MASK", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STYLEX_TAG_MASK(a) bdk_pki_stylex_tag_mask_t
#define bustype_BDK_PKI_STYLEX_TAG_MASK(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STYLEX_TAG_MASK(a) "PKI_STYLEX_TAG_MASK"
#define device_bar_BDK_PKI_STYLEX_TAG_MASK(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STYLEX_TAG_MASK(a) (a)
#define arguments_BDK_PKI_STYLEX_TAG_MASK(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_style#_tag_sel
 *
 * PKI Per-Style Configuration 2 Registers
 * This register configures the PKI BE tag algorithm.
 * It is indexed by final style, PKI_WQE_S[STYLE]\<5:0\>.
 *
 * Internal:
 * This CSR is really indexed by PKI_BEWQ_S[STYLE]\<5:0\>, which should match
 * PKI_WQE_S[STYLE]\<5:0\>.
 */
union bdk_pki_stylex_tag_sel
{
    uint64_t u;
    struct bdk_pki_stylex_tag_sel_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_27_63        : 37;
        uint64_t tag_idx3              : 3;  /**< [ 26: 24](R/W) Index for TAG_INC\<3\>. */
        uint64_t reserved_19_23        : 5;
        uint64_t tag_idx2              : 3;  /**< [ 18: 16](R/W) Index for TAG_INC\<2\>. */
        uint64_t reserved_11_15        : 5;
        uint64_t tag_idx1              : 3;  /**< [ 10:  8](R/W) Index for TAG_INC\<1\>. */
        uint64_t reserved_3_7          : 5;
        uint64_t tag_idx0              : 3;  /**< [  2:  0](R/W) Index for TAG_INC\<0\>. This value is multiplied by 4 to index into PKI_TAG_INC()_MASK.
                                                                 See PKI_WQE_S[TAG]. */
#else /* Word 0 - Little Endian */
        uint64_t tag_idx0              : 3;  /**< [  2:  0](R/W) Index for TAG_INC\<0\>. This value is multiplied by 4 to index into PKI_TAG_INC()_MASK.
                                                                 See PKI_WQE_S[TAG]. */
        uint64_t reserved_3_7          : 5;
        uint64_t tag_idx1              : 3;  /**< [ 10:  8](R/W) Index for TAG_INC\<1\>. */
        uint64_t reserved_11_15        : 5;
        uint64_t tag_idx2              : 3;  /**< [ 18: 16](R/W) Index for TAG_INC\<2\>. */
        uint64_t reserved_19_23        : 5;
        uint64_t tag_idx3              : 3;  /**< [ 26: 24](R/W) Index for TAG_INC\<3\>. */
        uint64_t reserved_27_63        : 37;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_stylex_tag_sel_s cn; */
};
typedef union bdk_pki_stylex_tag_sel bdk_pki_stylex_tag_sel_t;

static inline uint64_t BDK_PKI_STYLEX_TAG_SEL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STYLEX_TAG_SEL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000020000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STYLEX_TAG_SEL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STYLEX_TAG_SEL(a) bdk_pki_stylex_tag_sel_t
#define bustype_BDK_PKI_STYLEX_TAG_SEL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STYLEX_TAG_SEL(a) "PKI_STYLEX_TAG_SEL"
#define device_bar_BDK_PKI_STYLEX_TAG_SEL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STYLEX_TAG_SEL(a) (a)
#define arguments_BDK_PKI_STYLEX_TAG_SEL(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_style#_wq2
 *
 * PKI Per-Style WQ Word 2 Registers
 * This register configures the PKI BE WQE generation.
 * It is indexed by final style, PKI_WQE_S[STYLE]\<5:0\>.
 *
 * Internal:
 * This CSR is really indexed by PKI_BEWQ_S[STYLE]\<5:0\>, which should match
 * PKI_WQE_S[STYLE]\<5:0\>.
 */
union bdk_pki_stylex_wq2
{
    uint64_t u;
    struct bdk_pki_stylex_wq2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Data for WQ2\<63:0\>. This is ORed over any parser calculated WQ2\<63:0\> fields,
                                                                 and is used to emulate as if the parser set a WQ field such as
                                                                 PKI_WQE_S[PF1]. PKI_INST_HDR_S packets may also want to use this mode to set
                                                                 PKI_WQE_S[LCTY] to IP when PKI parsing IP is disabled. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Data for WQ2\<63:0\>. This is ORed over any parser calculated WQ2\<63:0\> fields,
                                                                 and is used to emulate as if the parser set a WQ field such as
                                                                 PKI_WQE_S[PF1]. PKI_INST_HDR_S packets may also want to use this mode to set
                                                                 PKI_WQE_S[LCTY] to IP when PKI parsing IP is disabled. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_stylex_wq2_s cn; */
};
typedef union bdk_pki_stylex_wq2 bdk_pki_stylex_wq2_t;

static inline uint64_t BDK_PKI_STYLEX_WQ2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STYLEX_WQ2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000022000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STYLEX_WQ2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STYLEX_WQ2(a) bdk_pki_stylex_wq2_t
#define bustype_BDK_PKI_STYLEX_WQ2(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STYLEX_WQ2(a) "PKI_STYLEX_WQ2"
#define device_bar_BDK_PKI_STYLEX_WQ2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STYLEX_WQ2(a) (a)
#define arguments_BDK_PKI_STYLEX_WQ2(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_style#_wq4
 *
 * PKI Per-Style WQ Word 4 Registers
 * This register configures the PKI BE WQE generation.
 * It is indexed by final style, PKI_WQE_S[STYLE]\<5:0\>.
 *
 * Internal:
 * This CSR is really indexed by PKI_BEWQ_S[STYLE]\<5:0\>, which should match
 * PKI_WQE_S[STYLE]\<5:0\>.
 */
union bdk_pki_stylex_wq4
{
    uint64_t u;
    struct bdk_pki_stylex_wq4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Data for WQ4\<63:0\>. This is ORed over any parser calculated WQ4\<63:0\> fields,
                                                                 and is used to emulate as if the parser set a WQ pointer field. PKI_INST_HDR_S
                                                                 packets may also want to use this mode to set PKI_WQE_S[LCPTR] to the start of
                                                                 IP when PKI parsing IP is disabled. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Data for WQ4\<63:0\>. This is ORed over any parser calculated WQ4\<63:0\> fields,
                                                                 and is used to emulate as if the parser set a WQ pointer field. PKI_INST_HDR_S
                                                                 packets may also want to use this mode to set PKI_WQE_S[LCPTR] to the start of
                                                                 IP when PKI parsing IP is disabled. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_stylex_wq4_s cn; */
};
typedef union bdk_pki_stylex_wq4 bdk_pki_stylex_wq4_t;

static inline uint64_t BDK_PKI_STYLEX_WQ4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_STYLEX_WQ4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x86c000023000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("PKI_STYLEX_WQ4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_STYLEX_WQ4(a) bdk_pki_stylex_wq4_t
#define bustype_BDK_PKI_STYLEX_WQ4(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_STYLEX_WQ4(a) "PKI_STYLEX_WQ4"
#define device_bar_BDK_PKI_STYLEX_WQ4(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_STYLEX_WQ4(a) (a)
#define arguments_BDK_PKI_STYLEX_WQ4(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_tag_inc#_ctl
 *
 * PKI Tag Inclusion Control Registers
 */
union bdk_pki_tag_incx_ctl
{
    uint64_t u;
    struct bdk_pki_tag_incx_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t ptr_sel               : 4;  /**< [ 11:  8](R/W) Which pointer to use for the bitmask in PKI_TAG_INC()_MASK.
                                                                 0x0 = Absolute from start of packet.
                                                                 0x1-0x7 = Reserved.
                                                                 0x8 = Relative to start of PKI_WQE_S[LAPTR]. LAPTR must be valid (see
                                                                 PKI_WQE_S[LAPTR]) or mask is ignored.
                                                                 0x9 = Relative to start of PKI_WQE_S[LBPTR]. LBPTR must be valid (see
                                                                 PKI_WQE_S[LBPTR]) or mask is ignored.
                                                                 0xA = Relative to start of PKI_WQE_S[LCPTR]. LCPTR must be valid (see
                                                                 PKI_WQE_S[LCPTR]) or mask is ignored.
                                                                 0xB = Relative to start of PKI_WQE_S[LDPTR]. LDPTR must be valid (see
                                                                 PKI_WQE_S[LDPTR]) or mask is ignored.
                                                                 0xC = Relative to start of PKI_WQE_S[LEPTR]. LEPTR must be valid (see
                                                                 PKI_WQE_S[LEPTR]) or mask is ignored.
                                                                 0xD = Relative to start of PKI_WQE_S[LFPTR]. LFPTR must be valid (see
                                                                 PKI_WQE_S[LFPTR]) or mask is ignored.
                                                                 0xE = Relative to start of PKI_WQE_S[LGPTR]. LGPTR must be valid (see
                                                                 PKI_WQE_S[LGPTR]) or mask is ignored.
                                                                 0xF = Relative to start of PKI_WQE_S[VLPTR]. VLPTR must be valid (see
                                                                 PKI_WQE_S[VLPTR]) or mask is ignored.

                                                                 Internal:
                                                                 Note excluding 0x0, the encoding matches the byte number to read from PKI_WQE_S WORD4. */
        uint64_t offset                : 8;  /**< [  7:  0](R/W) Offset for PKI_TAG_INC()_MASK. Number of bytes to add to the selected pointer before
                                                                 applying the mask. */
#else /* Word 0 - Little Endian */
        uint64_t offset                : 8;  /**< [  7:  0](R/W) Offset for PKI_TAG_INC()_MASK. Number of bytes to add to the selected pointer before
                                                                 applying the mask. */
        uint64_t ptr_sel               : 4;  /**< [ 11:  8](R/W) Which pointer to use for the bitmask in PKI_TAG_INC()_MASK.
                                                                 0x0 = Absolute from start of packet.
                                                                 0x1-0x7 = Reserved.
                                                                 0x8 = Relative to start of PKI_WQE_S[LAPTR]. LAPTR must be valid (see
                                                                 PKI_WQE_S[LAPTR]) or mask is ignored.
                                                                 0x9 = Relative to start of PKI_WQE_S[LBPTR]. LBPTR must be valid (see
                                                                 PKI_WQE_S[LBPTR]) or mask is ignored.
                                                                 0xA = Relative to start of PKI_WQE_S[LCPTR]. LCPTR must be valid (see
                                                                 PKI_WQE_S[LCPTR]) or mask is ignored.
                                                                 0xB = Relative to start of PKI_WQE_S[LDPTR]. LDPTR must be valid (see
                                                                 PKI_WQE_S[LDPTR]) or mask is ignored.
                                                                 0xC = Relative to start of PKI_WQE_S[LEPTR]. LEPTR must be valid (see
                                                                 PKI_WQE_S[LEPTR]) or mask is ignored.
                                                                 0xD = Relative to start of PKI_WQE_S[LFPTR]. LFPTR must be valid (see
                                                                 PKI_WQE_S[LFPTR]) or mask is ignored.
                                                                 0xE = Relative to start of PKI_WQE_S[LGPTR]. LGPTR must be valid (see
                                                                 PKI_WQE_S[LGPTR]) or mask is ignored.
                                                                 0xF = Relative to start of PKI_WQE_S[VLPTR]. VLPTR must be valid (see
                                                                 PKI_WQE_S[VLPTR]) or mask is ignored.

                                                                 Internal:
                                                                 Note excluding 0x0, the encoding matches the byte number to read from PKI_WQE_S WORD4. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_tag_incx_ctl_s cn; */
};
typedef union bdk_pki_tag_incx_ctl bdk_pki_tag_incx_ctl_t;

static inline uint64_t BDK_PKI_TAG_INCX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_TAG_INCX_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x86c000007000ll + 8ll * ((a) & 0x1f);
    __bdk_csr_fatal("PKI_TAG_INCX_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_TAG_INCX_CTL(a) bdk_pki_tag_incx_ctl_t
#define bustype_BDK_PKI_TAG_INCX_CTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_TAG_INCX_CTL(a) "PKI_TAG_INCX_CTL"
#define device_bar_BDK_PKI_TAG_INCX_CTL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_TAG_INCX_CTL(a) (a)
#define arguments_BDK_PKI_TAG_INCX_CTL(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_tag_inc#_mask
 *
 * PKI Tag Inclusion Mask Registers
 */
union bdk_pki_tag_incx_mask
{
    uint64_t u;
    struct bdk_pki_tag_incx_mask_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t en                    : 64; /**< [ 63:  0](R/W) Include byte in mask-tag algorithm. Each [EN] bit corresponds to enabling a byte
                                                                 in the data stream, for 64 consecutive bytes in total. Which array index is used
                                                                 is controlled by PKI_TAG_INC()_CTL as described in PKI_WQE_S[TAG]. */
#else /* Word 0 - Little Endian */
        uint64_t en                    : 64; /**< [ 63:  0](R/W) Include byte in mask-tag algorithm. Each [EN] bit corresponds to enabling a byte
                                                                 in the data stream, for 64 consecutive bytes in total. Which array index is used
                                                                 is controlled by PKI_TAG_INC()_CTL as described in PKI_WQE_S[TAG]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_tag_incx_mask_s cn; */
};
typedef union bdk_pki_tag_incx_mask bdk_pki_tag_incx_mask_t;

static inline uint64_t BDK_PKI_TAG_INCX_MASK(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_TAG_INCX_MASK(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x86c000008000ll + 8ll * ((a) & 0x1f);
    __bdk_csr_fatal("PKI_TAG_INCX_MASK", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_TAG_INCX_MASK(a) bdk_pki_tag_incx_mask_t
#define bustype_BDK_PKI_TAG_INCX_MASK(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_TAG_INCX_MASK(a) "PKI_TAG_INCX_MASK"
#define device_bar_BDK_PKI_TAG_INCX_MASK(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_TAG_INCX_MASK(a) (a)
#define arguments_BDK_PKI_TAG_INCX_MASK(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_tag_secret
 *
 * PKI Initial-Value Register
 * The source and destination initial values (IVs) in tag generation provide a mechanism for
 * seeding with a random initialization value to reduce cache collision attacks.
 */
union bdk_pki_tag_secret
{
    uint64_t u;
    struct bdk_pki_tag_secret_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dst6                  : 16; /**< [ 63: 48](R/W) Secret for the destination tuple IPv6 tag CRC calculation. Typically identical to SRC6 to
                                                                 ensure tagging is symmetric between source/destination flows. Typically different from DST
                                                                 for maximum security. */
        uint64_t src6                  : 16; /**< [ 47: 32](R/W) Secret for the source tuple IPv6 tag CRC calculation. Typically different from SRC for
                                                                 maximum security. */
        uint64_t dst                   : 16; /**< [ 31: 16](R/W) Secret for the destination tuple tag CRC calculation. Typically identical to SRC to
                                                                 ensure tagging is symmetric between source/destination flows. */
        uint64_t src                   : 16; /**< [ 15:  0](R/W) Secret for the source tuple tag CRC calculation. */
#else /* Word 0 - Little Endian */
        uint64_t src                   : 16; /**< [ 15:  0](R/W) Secret for the source tuple tag CRC calculation. */
        uint64_t dst                   : 16; /**< [ 31: 16](R/W) Secret for the destination tuple tag CRC calculation. Typically identical to SRC to
                                                                 ensure tagging is symmetric between source/destination flows. */
        uint64_t src6                  : 16; /**< [ 47: 32](R/W) Secret for the source tuple IPv6 tag CRC calculation. Typically different from SRC for
                                                                 maximum security. */
        uint64_t dst6                  : 16; /**< [ 63: 48](R/W) Secret for the destination tuple IPv6 tag CRC calculation. Typically identical to SRC6 to
                                                                 ensure tagging is symmetric between source/destination flows. Typically different from DST
                                                                 for maximum security. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_tag_secret_s cn; */
};
typedef union bdk_pki_tag_secret bdk_pki_tag_secret_t;

#define BDK_PKI_TAG_SECRET BDK_PKI_TAG_SECRET_FUNC()
static inline uint64_t BDK_PKI_TAG_SECRET_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_TAG_SECRET_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000430ll;
    __bdk_csr_fatal("PKI_TAG_SECRET", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_TAG_SECRET bdk_pki_tag_secret_t
#define bustype_BDK_PKI_TAG_SECRET BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_TAG_SECRET "PKI_TAG_SECRET"
#define device_bar_BDK_PKI_TAG_SECRET 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_TAG_SECRET 0
#define arguments_BDK_PKI_TAG_SECRET -1,-1,-1,-1

/**
 * Register (NCB) pki_x2p_ctl
 *
 * INTERNAL: PKI X2P Control Insertion and Activation Register
 */
union bdk_pki_x2p_ctl
{
    uint64_t u;
    struct bdk_pki_x2p_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_34_63        : 30;
        uint64_t sop_busy              : 1;  /**< [ 33: 33](R/W/H) X2P SOP signal.
                                                                 Internal:
                                                                 X2P SOP signal for inject packet, when written.
                                                                 On a read, if set, this bit indicates that X2P FIFO is full -
                                                                 Do not inject new packet. */
        uint64_t eop                   : 1;  /**< [ 32: 32](WO) X2P EOP signal. */
        uint64_t reserved_28_31        : 4;
        uint64_t pnum                  : 12; /**< [ 27: 16](WO) X2P PNUM signal. */
        uint64_t reserved_14_15        : 2;
        uint64_t pknd                  : 6;  /**< [ 13:  8](WO) X2P PKND signal. */
        uint64_t perr                  : 4;  /**< [  7:  4](WO) X2P packet error signal. */
        uint64_t bval                  : 4;  /**< [  3:  0](WO) X2P BVAL signal. */
#else /* Word 0 - Little Endian */
        uint64_t bval                  : 4;  /**< [  3:  0](WO) X2P BVAL signal. */
        uint64_t perr                  : 4;  /**< [  7:  4](WO) X2P packet error signal. */
        uint64_t pknd                  : 6;  /**< [ 13:  8](WO) X2P PKND signal. */
        uint64_t reserved_14_15        : 2;
        uint64_t pnum                  : 12; /**< [ 27: 16](WO) X2P PNUM signal. */
        uint64_t reserved_28_31        : 4;
        uint64_t eop                   : 1;  /**< [ 32: 32](WO) X2P EOP signal. */
        uint64_t sop_busy              : 1;  /**< [ 33: 33](R/W/H) X2P SOP signal.
                                                                 Internal:
                                                                 X2P SOP signal for inject packet, when written.
                                                                 On a read, if set, this bit indicates that X2P FIFO is full -
                                                                 Do not inject new packet. */
        uint64_t reserved_34_63        : 30;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_x2p_ctl_s cn; */
};
typedef union bdk_pki_x2p_ctl bdk_pki_x2p_ctl_t;

#define BDK_PKI_X2P_CTL BDK_PKI_X2P_CTL_FUNC()
static inline uint64_t BDK_PKI_X2P_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_X2P_CTL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000160ll;
    __bdk_csr_fatal("PKI_X2P_CTL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_X2P_CTL bdk_pki_x2p_ctl_t
#define bustype_BDK_PKI_X2P_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_X2P_CTL "PKI_X2P_CTL"
#define device_bar_BDK_PKI_X2P_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_X2P_CTL 0
#define arguments_BDK_PKI_X2P_CTL -1,-1,-1,-1

/**
 * Register (NCB) pki_x2p_dat#
 *
 * INTERNAL: PKI X2P Data Insertion Register
 */
union bdk_pki_x2p_datx
{
    uint64_t u;
    struct bdk_pki_x2p_datx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](WO) X2P data to insert.
                                                                 Internal:
                                                                 DAT0: Maps to the x2p big endian bus x2p.data\<63:0\>.
                                                                 DAT1: Maps to the x2p big endian bus x2p.data\<127:64\>. */
#else /* Word 0 - Little Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](WO) X2P data to insert.
                                                                 Internal:
                                                                 DAT0: Maps to the x2p big endian bus x2p.data\<63:0\>.
                                                                 DAT1: Maps to the x2p big endian bus x2p.data\<127:64\>. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_x2p_datx_s cn; */
};
typedef union bdk_pki_x2p_datx bdk_pki_x2p_datx_t;

static inline uint64_t BDK_PKI_X2P_DATX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_X2P_DATX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1))
        return 0x86c000000140ll + 8ll * ((a) & 0x1);
    __bdk_csr_fatal("PKI_X2P_DATX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_X2P_DATX(a) bdk_pki_x2p_datx_t
#define bustype_BDK_PKI_X2P_DATX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_X2P_DATX(a) "PKI_X2P_DATX"
#define device_bar_BDK_PKI_X2P_DATX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_X2P_DATX(a) (a)
#define arguments_BDK_PKI_X2P_DATX(a) (a),-1,-1,-1

/**
 * Register (NCB) pki_x2p_req_ofl
 *
 * PKI X2P Request Overflow Error Register
 */
union bdk_pki_x2p_req_ofl
{
    uint64_t u;
    struct bdk_pki_x2p_req_ofl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t x2p_did               : 4;  /**< [  3:  0](RO/H) When PKI_GEN_INT[X2P_REQ_OFL] is set, this field latches the X2P device id number which
                                                                 attempted to overflow the allowed outstanding requests to PKI. */
#else /* Word 0 - Little Endian */
        uint64_t x2p_did               : 4;  /**< [  3:  0](RO/H) When PKI_GEN_INT[X2P_REQ_OFL] is set, this field latches the X2P device id number which
                                                                 attempted to overflow the allowed outstanding requests to PKI. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pki_x2p_req_ofl_s cn; */
};
typedef union bdk_pki_x2p_req_ofl bdk_pki_x2p_req_ofl_t;

#define BDK_PKI_X2P_REQ_OFL BDK_PKI_X2P_REQ_OFL_FUNC()
static inline uint64_t BDK_PKI_X2P_REQ_OFL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PKI_X2P_REQ_OFL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x86c000000038ll;
    __bdk_csr_fatal("PKI_X2P_REQ_OFL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PKI_X2P_REQ_OFL bdk_pki_x2p_req_ofl_t
#define bustype_BDK_PKI_X2P_REQ_OFL BDK_CSR_TYPE_NCB
#define basename_BDK_PKI_X2P_REQ_OFL "PKI_X2P_REQ_OFL"
#define device_bar_BDK_PKI_X2P_REQ_OFL 0x0 /* PF_BAR0 */
#define busnum_BDK_PKI_X2P_REQ_OFL 0
#define arguments_BDK_PKI_X2P_REQ_OFL -1,-1,-1,-1

#endif /* __BDK_CSRS_PKI_H__ */
