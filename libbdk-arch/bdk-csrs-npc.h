#ifndef __BDK_CSRS_NPC_H__
#define __BDK_CSRS_NPC_H__
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
 * Cavium NPC.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration npc_errlev_e
 *
 * NPC Error Level Enumeration
 * Enumerates the lowest protocol layer containing an error.
 */
#define BDK_NPC_ERRLEV_E_LA (1)
#define BDK_NPC_ERRLEV_E_LB (2)
#define BDK_NPC_ERRLEV_E_LC (3)
#define BDK_NPC_ERRLEV_E_LD (4)
#define BDK_NPC_ERRLEV_E_LE (5)
#define BDK_NPC_ERRLEV_E_LF (6)
#define BDK_NPC_ERRLEV_E_LG (7)
#define BDK_NPC_ERRLEV_E_LH (8)
#define BDK_NPC_ERRLEV_E_NIX (0xf)
#define BDK_NPC_ERRLEV_E_RX(a) (0 + (a))
#define BDK_NPC_ERRLEV_E_RE (0)

/**
 * Enumeration npc_intf_e
 *
 * NPC Interface Enumeration
 * Enumerates the NPC interfaces.
 */
#define BDK_NPC_INTF_E_NIXX_RX(a) (0 + 2 * (a))
#define BDK_NPC_INTF_E_NIXX_TX(a) (1 + 2 * (a))

/**
 * Enumeration npc_lid_e
 *
 * NPC Layer ID Enumeration
 * Enumerates layers parsed by NPC.
 */
#define BDK_NPC_LID_E_LA (0)
#define BDK_NPC_LID_E_LB (1)
#define BDK_NPC_LID_E_LC (2)
#define BDK_NPC_LID_E_LD (3)
#define BDK_NPC_LID_E_LE (4)
#define BDK_NPC_LID_E_LF (5)
#define BDK_NPC_LID_E_LG (6)
#define BDK_NPC_LID_E_LH (7)

/**
 * Enumeration npc_lkupop_e
 *
 * NPC Lookup Operation Enumeration
 * Enumerates the lookup operation for NPC_AF_LKUP_CTL[OP].
 */
#define BDK_NPC_LKUPOP_E_KEY (1)
#define BDK_NPC_LKUPOP_E_PKT (0)

/**
 * Enumeration npc_mcamkeyw_e
 *
 * NPC MCAM Search Key Width Enumeration
 */
#define BDK_NPC_MCAMKEYW_E_X1 (0)
#define BDK_NPC_MCAMKEYW_E_X2 (1)
#define BDK_NPC_MCAMKEYW_E_X4 (2)

/**
 * Structure npc_layer_info_s
 *
 * NPC Layer Parse Information Structure
 * This structure specifies the format of NPC_RESULT_S[LA,LB,...,LH].
 */
union bdk_npc_layer_info_s
{
    uint32_t u;
    struct bdk_npc_layer_info_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t ltype                 : 4;  /**< [ 19: 16] Software defined layer type, e.g. Ethernet, IPv4, IPv6, UDP, etc. Zero
                                                                 means the layer was not parsed. */
        uint32_t flags                 : 8;  /**< [ 15:  8] Software defined flag bits for the layer. Typically used to indicates
                                                                 extensions to a layer, e.g. Ethernet tags, IPv6 extensions, etc. */
        uint32_t lptr                  : 8;  /**< [  7:  0] Layer pointer. Byte offset from packet start to first byte of layer. */
#else /* Word 0 - Little Endian */
        uint32_t lptr                  : 8;  /**< [  7:  0] Layer pointer. Byte offset from packet start to first byte of layer. */
        uint32_t flags                 : 8;  /**< [ 15:  8] Software defined flag bits for the layer. Typically used to indicates
                                                                 extensions to a layer, e.g. Ethernet tags, IPv6 extensions, etc. */
        uint32_t ltype                 : 4;  /**< [ 19: 16] Software defined layer type, e.g. Ethernet, IPv4, IPv6, UDP, etc. Zero
                                                                 means the layer was not parsed. */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_layer_info_s_s cn; */
};

/**
 * Structure npc_layer_kex_s
 *
 * NPC Layer MCAM Search Key Extract Structure
 * This structure specifies the format of each of the
 * NPC_PARSE_KEX_S[LA,LB,...,LH] fields. It contains the subset of
 * NPC_LAYER_INFO_S fields that can be included in the MCAM search key.
 * See NPC_PARSE_KEX_S and NPC_AF_INTF()_KEX_CFG.
 */
union bdk_npc_layer_kex_s
{
    uint32_t u;
    struct bdk_npc_layer_kex_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_12_31        : 20;
        uint32_t ltype                 : 4;  /**< [ 11:  8] Software defined layer type, e.g. Ethernet, IPv4, IPv6, UDP, etc. Zero
                                                                 means the layer was not parsed. */
        uint32_t flags                 : 8;  /**< [  7:  0] Software defined flag bits for the layer. Typically used to indicates
                                                                 extensions to a layer, e.g. Ethernet tags, IPv6 extensions, etc. */
#else /* Word 0 - Little Endian */
        uint32_t flags                 : 8;  /**< [  7:  0] Software defined flag bits for the layer. Typically used to indicates
                                                                 extensions to a layer, e.g. Ethernet tags, IPv6 extensions, etc. */
        uint32_t ltype                 : 4;  /**< [ 11:  8] Software defined layer type, e.g. Ethernet, IPv4, IPv6, UDP, etc. Zero
                                                                 means the layer was not parsed. */
        uint32_t reserved_12_31        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_layer_kex_s_s cn; */
};

/**
 * Structure npc_mcam_key_x1_s
 *
 * NPC MCAM Search Key X1 Structure
 * This structure specifies the MCAM search key format used by an interface
 * when NPC_AF_INTF()_KEX_CFG[KEYW] = NPC_MCAMKEYW_E::X1.
 */
union bdk_npc_mcam_key_x1_s
{
    uint64_t u[3];
    struct bdk_npc_mcam_key_x1_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t intf                  : 2;  /**< [  1:  0] NPC interface enumerated by NPC_INTF_E. */
#else /* Word 0 - Little Endian */
        uint64_t intf                  : 2;  /**< [  1:  0] NPC interface enumerated by NPC_INTF_E. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t kw0                   : 64; /**< [127: 64] Key word 0. */
#else /* Word 1 - Little Endian */
        uint64_t kw0                   : 64; /**< [127: 64] Key word 0. */
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t reserved_176_191      : 16;
        uint64_t kw1                   : 48; /**< [175:128] Key word 1. */
#else /* Word 2 - Little Endian */
        uint64_t kw1                   : 48; /**< [175:128] Key word 1. */
        uint64_t reserved_176_191      : 16;
#endif /* Word 2 - End */
    } s;
    /* struct bdk_npc_mcam_key_x1_s_s cn; */
};

/**
 * Structure npc_mcam_key_x2_s
 *
 * NPC MCAM Search Key X2 Structure
 * This structure specifies the MCAM search key format used by an interface
 * when NPC_AF_INTF()_KEX_CFG[KEYW] = NPC_MCAMKEYW_E::X2.
 */
union bdk_npc_mcam_key_x2_s
{
    uint64_t u[5];
    struct bdk_npc_mcam_key_x2_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t intf                  : 2;  /**< [  1:  0] NPC interface enumerated by NPC_INTF_E. */
#else /* Word 0 - Little Endian */
        uint64_t intf                  : 2;  /**< [  1:  0] NPC interface enumerated by NPC_INTF_E. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t kw0                   : 64; /**< [127: 64] Key word 0. */
#else /* Word 1 - Little Endian */
        uint64_t kw0                   : 64; /**< [127: 64] Key word 0. */
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t kw1                   : 64; /**< [191:128] Key word 1. */
#else /* Word 2 - Little Endian */
        uint64_t kw1                   : 64; /**< [191:128] Key word 1. */
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t kw2                   : 64; /**< [255:192] Key word 2. */
#else /* Word 3 - Little Endian */
        uint64_t kw2                   : 64; /**< [255:192] Key word 2. */
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t reserved_288_319      : 32;
        uint64_t kw3                   : 32; /**< [287:256] Key word 3. */
#else /* Word 4 - Little Endian */
        uint64_t kw3                   : 32; /**< [287:256] Key word 3. */
        uint64_t reserved_288_319      : 32;
#endif /* Word 4 - End */
    } s;
    /* struct bdk_npc_mcam_key_x2_s_s cn; */
};

/**
 * Structure npc_mcam_key_x4_s
 *
 * NPC MCAM Search Key X4 Structure
 * This structure specifies the MCAM search key format used by an interface
 * when NPC_AF_INTF()_KEX_CFG[KEYW] = NPC_MCAMKEYW_E::X4.
 */
union bdk_npc_mcam_key_x4_s
{
    uint64_t u[8];
    struct bdk_npc_mcam_key_x4_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t intf                  : 2;  /**< [  1:  0] NPC interface enumerated by NPC_INTF_E. */
#else /* Word 0 - Little Endian */
        uint64_t intf                  : 2;  /**< [  1:  0] NPC interface enumerated by NPC_INTF_E. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t kw0                   : 64; /**< [127: 64] Key word 0. */
#else /* Word 1 - Little Endian */
        uint64_t kw0                   : 64; /**< [127: 64] Key word 0. */
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t kw1                   : 64; /**< [191:128] Key word 1. */
#else /* Word 2 - Little Endian */
        uint64_t kw1                   : 64; /**< [191:128] Key word 1. */
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t kw2                   : 64; /**< [255:192] Key word 2. */
#else /* Word 3 - Little Endian */
        uint64_t kw2                   : 64; /**< [255:192] Key word 2. */
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t kw3                   : 64; /**< [319:256] Key word 3. */
#else /* Word 4 - Little Endian */
        uint64_t kw3                   : 64; /**< [319:256] Key word 3. */
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t kw4                   : 64; /**< [383:320] Key word 4. */
#else /* Word 5 - Little Endian */
        uint64_t kw4                   : 64; /**< [383:320] Key word 4. */
#endif /* Word 5 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 6 - Big Endian */
        uint64_t kw5                   : 64; /**< [447:384] Key word 5. */
#else /* Word 6 - Little Endian */
        uint64_t kw5                   : 64; /**< [447:384] Key word 5. */
#endif /* Word 6 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 7 - Big Endian */
        uint64_t kw6                   : 64; /**< [511:448] Key word 6. */
#else /* Word 7 - Little Endian */
        uint64_t kw6                   : 64; /**< [511:448] Key word 6. */
#endif /* Word 7 - End */
    } s;
    /* struct bdk_npc_mcam_key_x4_s_s cn; */
};

/**
 * Structure npc_parse_kex_s
 *
 * NPC Parse Key Extract Structure
 * This structure contains the subset of NPC_RESULT_S fields that can be included
 * in the MCAM search key. See NPC_AF_INTF()_KEX_CFG.
 */
union bdk_npc_parse_kex_s
{
    uint64_t u[2];
    struct bdk_npc_parse_kex_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t lc                    : 12; /**< [ 63: 52] Layer C parse information. Format specified by NPC_LAYER_KEX_S. */
        uint64_t lb                    : 12; /**< [ 51: 40] Layer B parse information. Format specified by NPC_LAYER_KEX_S. */
        uint64_t la                    : 12; /**< [ 39: 28] Layer A parse information. Format specified by NPC_LAYER_KEX_S. */
        uint64_t l3b                   : 1;  /**< [ 27: 27] See NPC_RESULT_S[L3B]. */
        uint64_t l3m                   : 1;  /**< [ 26: 26] See NPC_RESULT_S[L3M]. */
        uint64_t l2b                   : 1;  /**< [ 25: 25] See NPC_RESULT_S[L2B]. */
        uint64_t l2m                   : 1;  /**< [ 24: 24] See NPC_RESULT_S[L2M]. */
        uint64_t errcode               : 8;  /**< [ 23: 16] See NPC_RESULT_S[ERRCODE]. */
        uint64_t errlev                : 4;  /**< [ 15: 12] See NPC_RESULT_S[ERRLEV]. */
        uint64_t chan                  : 12; /**< [ 11:  0] Logical channel the packet arrived from. */
#else /* Word 0 - Little Endian */
        uint64_t chan                  : 12; /**< [ 11:  0] Logical channel the packet arrived from. */
        uint64_t errlev                : 4;  /**< [ 15: 12] See NPC_RESULT_S[ERRLEV]. */
        uint64_t errcode               : 8;  /**< [ 23: 16] See NPC_RESULT_S[ERRCODE]. */
        uint64_t l2m                   : 1;  /**< [ 24: 24] See NPC_RESULT_S[L2M]. */
        uint64_t l2b                   : 1;  /**< [ 25: 25] See NPC_RESULT_S[L2B]. */
        uint64_t l3m                   : 1;  /**< [ 26: 26] See NPC_RESULT_S[L3M]. */
        uint64_t l3b                   : 1;  /**< [ 27: 27] See NPC_RESULT_S[L3B]. */
        uint64_t la                    : 12; /**< [ 39: 28] Layer A parse information. Format specified by NPC_LAYER_KEX_S. */
        uint64_t lb                    : 12; /**< [ 51: 40] Layer B parse information. Format specified by NPC_LAYER_KEX_S. */
        uint64_t lc                    : 12; /**< [ 63: 52] Layer C parse information. Format specified by NPC_LAYER_KEX_S. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_124_127      : 4;
        uint64_t lh                    : 12; /**< [123:112] Layer H parse information. Format specified by NPC_LAYER_KEX_S. */
        uint64_t lg                    : 12; /**< [111:100] Layer G parse information. Format specified by NPC_LAYER_KEX_S. */
        uint64_t lf                    : 12; /**< [ 99: 88] Layer F parse information. Format specified by NPC_LAYER_KEX_S. */
        uint64_t le                    : 12; /**< [ 87: 76] Layer E parse information. Format specified by NPC_LAYER_KEX_S. */
        uint64_t ld                    : 12; /**< [ 75: 64] Layer D parse information. Format specified by NPC_LAYER_KEX_S. */
#else /* Word 1 - Little Endian */
        uint64_t ld                    : 12; /**< [ 75: 64] Layer D parse information. Format specified by NPC_LAYER_KEX_S. */
        uint64_t le                    : 12; /**< [ 87: 76] Layer E parse information. Format specified by NPC_LAYER_KEX_S. */
        uint64_t lf                    : 12; /**< [ 99: 88] Layer F parse information. Format specified by NPC_LAYER_KEX_S. */
        uint64_t lg                    : 12; /**< [111:100] Layer G parse information. Format specified by NPC_LAYER_KEX_S. */
        uint64_t lh                    : 12; /**< [123:112] Layer H parse information. Format specified by NPC_LAYER_KEX_S. */
        uint64_t reserved_124_127      : 4;
#endif /* Word 1 - End */
    } s;
    /* struct bdk_npc_parse_kex_s_s cn; */
};

/**
 * Structure npc_result_s
 *
 * NPC Result Structure
 * This structure contains a packet's parse and flow identification information.
 */
union bdk_npc_result_s
{
    uint64_t u[6];
    struct bdk_npc_result_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t eoh_ptr               : 8;  /**< [ 43: 36] End of header pointer. Byte offset from packet start to first byte after
                                                                 last parsed layer. */
        uint64_t l3b                   : 1;  /**< [ 35: 35] Set when the outer IP4 indicates broadcast, i.e. the destination address is all
                                                                 ones. Broadcast is not defined for IPv6. */
        uint64_t l3m                   : 1;  /**< [ 34: 34] Set when the outer IP indicates multicast, i.e. the IPv4 destination address
                                                                 \<31:28\> = 0xE, or the IPv6 MSB of the 128-bit destination address = 0xFF. */
        uint64_t l2b                   : 1;  /**< [ 33: 33] Set when the packet's destination MAC address field in the outer L2 header
                                                                 is the broadcast address (i.e. all 1s). */
        uint64_t l2m                   : 1;  /**< [ 32: 32] Set when the packet's destination MAC address field in the outer L2 header
                                                                 is a multicast address (i.e. the LSB of the first byte of the destination
                                                                 MAC is set, and the address is not a broadcast address - see [L2B]). */
        uint64_t errcode               : 8;  /**< [ 31: 24] When zero, indicates no error. When nonzero, contains a software defined
                                                                 opcode identifying the error reason, [ERRLEV] specifies the lowest protocol
                                                                 layer containing the eror, and software should ignore all parse information
                                                                 for layers higher than [ERRLEV], e.g. ignore [LF], [LG] and [LH] when
                                                                 [ERRCODE] is nonzero and [ERRLEV]=NPC_ERRLEV_E::LE. */
        uint64_t errlev                : 4;  /**< [ 23: 20] When [ERRCODE] is nonzero, specifies the lowest protocol layer containing
                                                                 an error, and [ERRCODE] indicates the error reason. Enumerated by
                                                                 NPC_ERRLEV_E. */
        uint64_t chan                  : 12; /**< [ 19:  8] Logical channel the packet arrived from. This is the channel or port
                                                                 number on which NIX received the packet, optionally adjusted by a
                                                                 port to channel adder using the CPI algorithm. See
                                                                 NPC_AF_PKIND()_CPI_DEF()[ENA]. */
        uint64_t pkind                 : 6;  /**< [  7:  2] Packet's port kind supplied by the NIX interface. */
        uint64_t intf                  : 2;  /**< [  1:  0] NPC interface enumerated by NPC_INTF_E. */
#else /* Word 0 - Little Endian */
        uint64_t intf                  : 2;  /**< [  1:  0] NPC interface enumerated by NPC_INTF_E. */
        uint64_t pkind                 : 6;  /**< [  7:  2] Packet's port kind supplied by the NIX interface. */
        uint64_t chan                  : 12; /**< [ 19:  8] Logical channel the packet arrived from. This is the channel or port
                                                                 number on which NIX received the packet, optionally adjusted by a
                                                                 port to channel adder using the CPI algorithm. See
                                                                 NPC_AF_PKIND()_CPI_DEF()[ENA]. */
        uint64_t errlev                : 4;  /**< [ 23: 20] When [ERRCODE] is nonzero, specifies the lowest protocol layer containing
                                                                 an error, and [ERRCODE] indicates the error reason. Enumerated by
                                                                 NPC_ERRLEV_E. */
        uint64_t errcode               : 8;  /**< [ 31: 24] When zero, indicates no error. When nonzero, contains a software defined
                                                                 opcode identifying the error reason, [ERRLEV] specifies the lowest protocol
                                                                 layer containing the eror, and software should ignore all parse information
                                                                 for layers higher than [ERRLEV], e.g. ignore [LF], [LG] and [LH] when
                                                                 [ERRCODE] is nonzero and [ERRLEV]=NPC_ERRLEV_E::LE. */
        uint64_t l2m                   : 1;  /**< [ 32: 32] Set when the packet's destination MAC address field in the outer L2 header
                                                                 is a multicast address (i.e. the LSB of the first byte of the destination
                                                                 MAC is set, and the address is not a broadcast address - see [L2B]). */
        uint64_t l2b                   : 1;  /**< [ 33: 33] Set when the packet's destination MAC address field in the outer L2 header
                                                                 is the broadcast address (i.e. all 1s). */
        uint64_t l3m                   : 1;  /**< [ 34: 34] Set when the outer IP indicates multicast, i.e. the IPv4 destination address
                                                                 \<31:28\> = 0xE, or the IPv6 MSB of the 128-bit destination address = 0xFF. */
        uint64_t l3b                   : 1;  /**< [ 35: 35] Set when the outer IP4 indicates broadcast, i.e. the destination address is all
                                                                 ones. Broadcast is not defined for IPv6. */
        uint64_t eoh_ptr               : 8;  /**< [ 43: 36] End of header pointer. Byte offset from packet start to first byte after
                                                                 last parsed layer. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t action                : 64; /**< [127: 64] Match action from MCAM. Format is NIX_RX_ACTION_S for RX packet
                                                                 ([INTF]=NPC_INTF_E::NIX(n)_RX), NIX_TX_ACTION_S for TX packet
                                                                 ([INTF]=NPC_INTF_E::NIX(n)_TX). */
#else /* Word 1 - Little Endian */
        uint64_t action                : 64; /**< [127: 64] Match action from MCAM. Format is NIX_RX_ACTION_S for RX packet
                                                                 ([INTF]=NPC_INTF_E::NIX(n)_RX), NIX_TX_ACTION_S for TX packet
                                                                 ([INTF]=NPC_INTF_E::NIX(n)_TX). */
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t vtag_action           : 64; /**< [191:128] Match Vtag action from MCAM. Format is NIX_RX_VTAG_ACTION_S for RX
                                                                 packet ([INTF]=NPC_INTF_E::NIX(n)_RX), NIX_TX_VTAG_ACTION_S for TX
                                                                 packet ([INTF]=NPC_INTF_E::NIX(n)_TX). */
#else /* Word 2 - Little Endian */
        uint64_t vtag_action           : 64; /**< [191:128] Match Vtag action from MCAM. Format is NIX_RX_VTAG_ACTION_S for RX
                                                                 packet ([INTF]=NPC_INTF_E::NIX(n)_RX), NIX_TX_VTAG_ACTION_S for TX
                                                                 packet ([INTF]=NPC_INTF_E::NIX(n)_TX). */
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t reserved_252_255      : 4;
        uint64_t lc                    : 20; /**< [251:232] Layer C parse information. Format specified by NPC_LAYER_INFO_S. */
        uint64_t lb                    : 20; /**< [231:212] Layer B parse information. Format specified by NPC_LAYER_INFO_S. */
        uint64_t la                    : 20; /**< [211:192] Layer A parse information. Format specified by NPC_LAYER_INFO_S. */
#else /* Word 3 - Little Endian */
        uint64_t la                    : 20; /**< [211:192] Layer A parse information. Format specified by NPC_LAYER_INFO_S. */
        uint64_t lb                    : 20; /**< [231:212] Layer B parse information. Format specified by NPC_LAYER_INFO_S. */
        uint64_t lc                    : 20; /**< [251:232] Layer C parse information. Format specified by NPC_LAYER_INFO_S. */
        uint64_t reserved_252_255      : 4;
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t reserved_316_319      : 4;
        uint64_t lf                    : 20; /**< [315:296] Layer F parse information. Format specified by NPC_LAYER_INFO_S. */
        uint64_t le                    : 20; /**< [295:276] Layer E parse information. Format specified by NPC_LAYER_INFO_S. */
        uint64_t ld                    : 20; /**< [275:256] Layer D parse information. Format specified by NPC_LAYER_INFO_S. */
#else /* Word 4 - Little Endian */
        uint64_t ld                    : 20; /**< [275:256] Layer D parse information. Format specified by NPC_LAYER_INFO_S. */
        uint64_t le                    : 20; /**< [295:276] Layer E parse information. Format specified by NPC_LAYER_INFO_S. */
        uint64_t lf                    : 20; /**< [315:296] Layer F parse information. Format specified by NPC_LAYER_INFO_S. */
        uint64_t reserved_316_319      : 4;
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t reserved_360_383      : 24;
        uint64_t lh                    : 20; /**< [359:340] Layer H parse information. Format specified by NPC_LAYER_INFO_S. */
        uint64_t lg                    : 20; /**< [339:320] Layer G parse information. Format specified by NPC_LAYER_INFO_S. */
#else /* Word 5 - Little Endian */
        uint64_t lg                    : 20; /**< [339:320] Layer G parse information. Format specified by NPC_LAYER_INFO_S. */
        uint64_t lh                    : 20; /**< [359:340] Layer H parse information. Format specified by NPC_LAYER_INFO_S. */
        uint64_t reserved_360_383      : 24;
#endif /* Word 5 - End */
    } s;
    /* struct bdk_npc_result_s_s cn; */
};

/**
 * Register (RVU_PF_BAR0) npc_af_active_pc
 *
 * NPC Interrupt-Timer Configuration Register
 */
union bdk_npc_af_active_pc
{
    uint64_t u;
    struct bdk_npc_af_active_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t active_pc             : 64; /**< [ 63:  0](R/W/H) This register increments on every coprocessor-clock cycle that the NPC conditional clocks
                                                                 are enabled. */
#else /* Word 0 - Little Endian */
        uint64_t active_pc             : 64; /**< [ 63:  0](R/W/H) This register increments on every coprocessor-clock cycle that the NPC conditional clocks
                                                                 are enabled. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_active_pc_s cn; */
};
typedef union bdk_npc_af_active_pc bdk_npc_af_active_pc_t;

#define BDK_NPC_AF_ACTIVE_PC BDK_NPC_AF_ACTIVE_PC_FUNC()
static inline uint64_t BDK_NPC_AF_ACTIVE_PC_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_ACTIVE_PC_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x850060000010ll;
    __bdk_csr_fatal("NPC_AF_ACTIVE_PC", 0, 0, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_ACTIVE_PC bdk_npc_af_active_pc_t
#define bustype_BDK_NPC_AF_ACTIVE_PC BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_ACTIVE_PC "NPC_AF_ACTIVE_PC"
#define device_bar_BDK_NPC_AF_ACTIVE_PC 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_ACTIVE_PC 0
#define arguments_BDK_NPC_AF_ACTIVE_PC -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_blk_rst
 *
 * NPC AF Block Reset Register
 */
union bdk_npc_af_blk_rst
{
    uint64_t u;
    struct bdk_npc_af_blk_rst_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t busy                  : 1;  /**< [ 63: 63](RO/H) When one, the block is busy completing reset. No access except the reading of
                                                                 this bit should occur to the block until this is clear. */
        uint64_t reserved_1_62         : 62;
        uint64_t rst                   : 1;  /**< [  0:  0](WO/H) Write one to reset the block, except for privileged AF registers in PF BAR0
                                                                 (TIM_PRIV_*). Software must ensure that all block activity is quiesced before
                                                                 writing 1. */
#else /* Word 0 - Little Endian */
        uint64_t rst                   : 1;  /**< [  0:  0](WO/H) Write one to reset the block, except for privileged AF registers in PF BAR0
                                                                 (TIM_PRIV_*). Software must ensure that all block activity is quiesced before
                                                                 writing 1. */
        uint64_t reserved_1_62         : 62;
        uint64_t busy                  : 1;  /**< [ 63: 63](RO/H) When one, the block is busy completing reset. No access except the reading of
                                                                 this bit should occur to the block until this is clear. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_blk_rst_s cn; */
};
typedef union bdk_npc_af_blk_rst bdk_npc_af_blk_rst_t;

#define BDK_NPC_AF_BLK_RST BDK_NPC_AF_BLK_RST_FUNC()
static inline uint64_t BDK_NPC_AF_BLK_RST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_BLK_RST_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x850060000040ll;
    __bdk_csr_fatal("NPC_AF_BLK_RST", 0, 0, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_BLK_RST bdk_npc_af_blk_rst_t
#define bustype_BDK_NPC_AF_BLK_RST BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_BLK_RST "NPC_AF_BLK_RST"
#define device_bar_BDK_NPC_AF_BLK_RST 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_BLK_RST 0
#define arguments_BDK_NPC_AF_BLK_RST -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_cfg
 *
 * NPC AF General Configuration Register
 */
union bdk_npc_af_cfg
{
    uint64_t u;
    struct bdk_npc_af_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t cclk_force            : 1;  /**< [  2:  2](R/W) Force conditional clocks to be always enabled. For diagnostic use only. */
        uint64_t reserved_0_1          : 2;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_1          : 2;
        uint64_t cclk_force            : 1;  /**< [  2:  2](R/W) Force conditional clocks to be always enabled. For diagnostic use only. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_cfg_s cn; */
};
typedef union bdk_npc_af_cfg bdk_npc_af_cfg_t;

#define BDK_NPC_AF_CFG BDK_NPC_AF_CFG_FUNC()
static inline uint64_t BDK_NPC_AF_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_CFG_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x850060000000ll;
    __bdk_csr_fatal("NPC_AF_CFG", 0, 0, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_CFG bdk_npc_af_cfg_t
#define bustype_BDK_NPC_AF_CFG BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_CFG "NPC_AF_CFG"
#define device_bar_BDK_NPC_AF_CFG 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_CFG 0
#define arguments_BDK_NPC_AF_CFG -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_const
 *
 * NPC AF Constants Register
 * This register contains constants for software discovery.
 */
union bdk_npc_af_const
{
    uint64_t u;
    struct bdk_npc_af_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t match_stats           : 16; /**< [ 63: 48](RAZ) Number of NPC_AF_MATCH_STAT() counters. */
        uint64_t mcam_banks            : 4;  /**< [ 47: 44](RO) Number of MCAM banks. */
        uint64_t mcam_bank_depth       : 16; /**< [ 43: 28](RO) MCAM bank depth. */
        uint64_t reserved_26_27        : 2;
        uint64_t mcam_bank_width       : 10; /**< [ 25: 16](RO) MCAM bank width. Combined number of nonreserved bits in
                                                                 NPC_AF_MCAME(0)_BANK(0)_CAM(0)_W0, NPC_AF_MCAME(0)_BANK(0)_CAM(0)_W1 and
                                                                 NPC_AF_MCAME(0)_BANK(0)_CAM(0)_INTF. */
        uint64_t reserved_13_15        : 3;
        uint64_t kpus                  : 5;  /**< [ 12:  8](RO) Number of KPUs. */
        uint64_t lids                  : 4;  /**< [  7:  4](RO) Number of layer IDs enumerated by NPC_LID_E. This is the maximum number of
                                                                 protocol layers captured by NPC. */
        uint64_t intfs                 : 4;  /**< [  3:  0](RO) Number of interfaces enumerated by NPC_INTF_E. */
#else /* Word 0 - Little Endian */
        uint64_t intfs                 : 4;  /**< [  3:  0](RO) Number of interfaces enumerated by NPC_INTF_E. */
        uint64_t lids                  : 4;  /**< [  7:  4](RO) Number of layer IDs enumerated by NPC_LID_E. This is the maximum number of
                                                                 protocol layers captured by NPC. */
        uint64_t kpus                  : 5;  /**< [ 12:  8](RO) Number of KPUs. */
        uint64_t reserved_13_15        : 3;
        uint64_t mcam_bank_width       : 10; /**< [ 25: 16](RO) MCAM bank width. Combined number of nonreserved bits in
                                                                 NPC_AF_MCAME(0)_BANK(0)_CAM(0)_W0, NPC_AF_MCAME(0)_BANK(0)_CAM(0)_W1 and
                                                                 NPC_AF_MCAME(0)_BANK(0)_CAM(0)_INTF. */
        uint64_t reserved_26_27        : 2;
        uint64_t mcam_bank_depth       : 16; /**< [ 43: 28](RO) MCAM bank depth. */
        uint64_t mcam_banks            : 4;  /**< [ 47: 44](RO) Number of MCAM banks. */
        uint64_t match_stats           : 16; /**< [ 63: 48](RAZ) Number of NPC_AF_MATCH_STAT() counters. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_const_s cn; */
};
typedef union bdk_npc_af_const bdk_npc_af_const_t;

#define BDK_NPC_AF_CONST BDK_NPC_AF_CONST_FUNC()
static inline uint64_t BDK_NPC_AF_CONST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_CONST_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x850060000020ll;
    __bdk_csr_fatal("NPC_AF_CONST", 0, 0, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_CONST bdk_npc_af_const_t
#define bustype_BDK_NPC_AF_CONST BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_CONST "NPC_AF_CONST"
#define device_bar_BDK_NPC_AF_CONST 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_CONST 0
#define arguments_BDK_NPC_AF_CONST -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_const1
 *
 * NPC AF Constants 1 Register
 * This register contains constants for software discovery.
 */
union bdk_npc_af_const1
{
    uint64_t u;
    struct bdk_npc_af_const1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t pkinds                : 8;  /**< [ 19: 12](RO) Number of port kinds. */
        uint64_t kpu_entries           : 12; /**< [ 11:  0](RO) Number of entries per KPU. */
#else /* Word 0 - Little Endian */
        uint64_t kpu_entries           : 12; /**< [ 11:  0](RO) Number of entries per KPU. */
        uint64_t pkinds                : 8;  /**< [ 19: 12](RO) Number of port kinds. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_const1_s cn; */
};
typedef union bdk_npc_af_const1 bdk_npc_af_const1_t;

#define BDK_NPC_AF_CONST1 BDK_NPC_AF_CONST1_FUNC()
static inline uint64_t BDK_NPC_AF_CONST1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_CONST1_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x850060000030ll;
    __bdk_csr_fatal("NPC_AF_CONST1", 0, 0, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_CONST1 bdk_npc_af_const1_t
#define bustype_BDK_NPC_AF_CONST1 BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_CONST1 "NPC_AF_CONST1"
#define device_bar_BDK_NPC_AF_CONST1 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_CONST1 0
#define arguments_BDK_NPC_AF_CONST1 -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_cpi#_cfg
 *
 * NPC AF Channel Parse Index Table Registers
 */
union bdk_npc_af_cpix_cfg
{
    uint64_t u;
    struct bdk_npc_af_cpix_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t padd                  : 4;  /**< [  3:  0](R/W) Port to channel adder for calculating NPC_RESULT_S[CHAN]. */
#else /* Word 0 - Little Endian */
        uint64_t padd                  : 4;  /**< [  3:  0](R/W) Port to channel adder for calculating NPC_RESULT_S[CHAN]. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_cpix_cfg_s cn; */
};
typedef union bdk_npc_af_cpix_cfg bdk_npc_af_cpix_cfg_t;

static inline uint64_t BDK_NPC_AF_CPIX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_CPIX_CFG(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1023))
        return 0x850060200000ll + 8ll * ((a) & 0x3ff);
    __bdk_csr_fatal("NPC_AF_CPIX_CFG", 1, a, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_CPIX_CFG(a) bdk_npc_af_cpix_cfg_t
#define bustype_BDK_NPC_AF_CPIX_CFG(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_CPIX_CFG(a) "NPC_AF_CPIX_CFG"
#define device_bar_BDK_NPC_AF_CPIX_CFG(a) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_CPIX_CFG(a) (a)
#define arguments_BDK_NPC_AF_CPIX_CFG(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_dbg_ctl
 *
 * NPC AF Debug Control Register
 * This register controls the capture of debug information in NPC_AF_KPU()_DBG,
 * NPC_AF_MCAM_DBG, NPC_AF_DBG_DATA() and NPC_AF_DBG_RESULT().
 */
union bdk_npc_af_dbg_ctl
{
    uint64_t u;
    struct bdk_npc_af_dbg_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t intf_dbg              : 4;  /**< [  5:  2](R/W) Interface debug enables. Bits enumerated by NPC_INTF_E. When a bit is set, debug
                                                                 information is captured for packets from the associated interface. */
        uint64_t lkup_dbg              : 1;  /**< [  1:  1](R/W) Software lookup debug enable. When set, debug information is captured for NPC
                                                                 lookups that software initiates by setting NPC_AF_LKUP_CTL[EXEC]. */
        uint64_t continuous            : 1;  /**< [  0:  0](R/W) Continuous mode. When clear, hardware will stop debug capture stops after
                                                                 the first packet/lookup that sets NPC_AF_DBG_STATUS[DONE]. When set,
                                                                 hardware will continuously capture debug information. */
#else /* Word 0 - Little Endian */
        uint64_t continuous            : 1;  /**< [  0:  0](R/W) Continuous mode. When clear, hardware will stop debug capture stops after
                                                                 the first packet/lookup that sets NPC_AF_DBG_STATUS[DONE]. When set,
                                                                 hardware will continuously capture debug information. */
        uint64_t lkup_dbg              : 1;  /**< [  1:  1](R/W) Software lookup debug enable. When set, debug information is captured for NPC
                                                                 lookups that software initiates by setting NPC_AF_LKUP_CTL[EXEC]. */
        uint64_t intf_dbg              : 4;  /**< [  5:  2](R/W) Interface debug enables. Bits enumerated by NPC_INTF_E. When a bit is set, debug
                                                                 information is captured for packets from the associated interface. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_dbg_ctl_s cn; */
};
typedef union bdk_npc_af_dbg_ctl bdk_npc_af_dbg_ctl_t;

#define BDK_NPC_AF_DBG_CTL BDK_NPC_AF_DBG_CTL_FUNC()
static inline uint64_t BDK_NPC_AF_DBG_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_DBG_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x850063000000ll;
    __bdk_csr_fatal("NPC_AF_DBG_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_DBG_CTL bdk_npc_af_dbg_ctl_t
#define bustype_BDK_NPC_AF_DBG_CTL BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_DBG_CTL "NPC_AF_DBG_CTL"
#define device_bar_BDK_NPC_AF_DBG_CTL 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_DBG_CTL 0
#define arguments_BDK_NPC_AF_DBG_CTL -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_dbg_data#
 *
 * NPC AF Debug Data Registers
 * This register contains packet header data for the last packet/lookup  for which
 * debug information is captured by NPC_AF_DBG_CTL[INTF_DBG,LKUP_DBG].
 */
union bdk_npc_af_dbg_datax
{
    uint64_t u;
    struct bdk_npc_af_dbg_datax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](RO/H) Debug data. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](RO/H) Debug data. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_dbg_datax_s cn; */
};
typedef union bdk_npc_af_dbg_datax bdk_npc_af_dbg_datax_t;

static inline uint64_t BDK_NPC_AF_DBG_DATAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_DBG_DATAX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=31))
        return 0x850063001400ll + 0x10ll * ((a) & 0x1f);
    __bdk_csr_fatal("NPC_AF_DBG_DATAX", 1, a, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_DBG_DATAX(a) bdk_npc_af_dbg_datax_t
#define bustype_BDK_NPC_AF_DBG_DATAX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_DBG_DATAX(a) "NPC_AF_DBG_DATAX"
#define device_bar_BDK_NPC_AF_DBG_DATAX(a) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_DBG_DATAX(a) (a)
#define arguments_BDK_NPC_AF_DBG_DATAX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_dbg_result#
 *
 * NPC AF Debug Result Registers
 * This register contains packet result data with format NPC_RESULT_S, for the
 * last packet/lookup for which debug information is captured by
 * NPC_AF_DBG_CTL[INTF_DBG,LKUP_DBG].
 */
union bdk_npc_af_dbg_resultx
{
    uint64_t u;
    struct bdk_npc_af_dbg_resultx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](RO/H) Debug data. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](RO/H) Debug data. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_dbg_resultx_s cn; */
};
typedef union bdk_npc_af_dbg_resultx bdk_npc_af_dbg_resultx_t;

static inline uint64_t BDK_NPC_AF_DBG_RESULTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_DBG_RESULTX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=5))
        return 0x850063001800ll + 0x10ll * ((a) & 0x7);
    __bdk_csr_fatal("NPC_AF_DBG_RESULTX", 1, a, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_DBG_RESULTX(a) bdk_npc_af_dbg_resultx_t
#define bustype_BDK_NPC_AF_DBG_RESULTX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_DBG_RESULTX(a) "NPC_AF_DBG_RESULTX"
#define device_bar_BDK_NPC_AF_DBG_RESULTX(a) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_DBG_RESULTX(a) (a)
#define arguments_BDK_NPC_AF_DBG_RESULTX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_dbg_status
 *
 * NPC AF Debug Status Register
 * This register controls the capture of debug information in NPC_AF_KPU()_DBG,
 * NPC_AF_MCAM_DBG, NPC_AF_LKUP_DATA() and NPC_AF_LKUP_RESULT().
 */
union bdk_npc_af_dbg_status
{
    uint64_t u;
    struct bdk_npc_af_dbg_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t done                  : 1;  /**< [  0:  0](R/W1C/H) Debug capture done. Hardware sets this bit after it has captured debug
                                                                 information in NPC_AF_KPU()_DBG, NPC_AF_MCAM_DBG, NPC_AF_DBG_RESULT() and
                                                                 NPC_AF_DBG_DATA(). If NPC_AF_DBG_CTL[CONTINUOUS] is clear and this bit is
                                                                 set, new debug information will not be captured until software writes one
                                                                 to clear this bit. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 1;  /**< [  0:  0](R/W1C/H) Debug capture done. Hardware sets this bit after it has captured debug
                                                                 information in NPC_AF_KPU()_DBG, NPC_AF_MCAM_DBG, NPC_AF_DBG_RESULT() and
                                                                 NPC_AF_DBG_DATA(). If NPC_AF_DBG_CTL[CONTINUOUS] is clear and this bit is
                                                                 set, new debug information will not be captured until software writes one
                                                                 to clear this bit. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_dbg_status_s cn; */
};
typedef union bdk_npc_af_dbg_status bdk_npc_af_dbg_status_t;

#define BDK_NPC_AF_DBG_STATUS BDK_NPC_AF_DBG_STATUS_FUNC()
static inline uint64_t BDK_NPC_AF_DBG_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_DBG_STATUS_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x850063000010ll;
    __bdk_csr_fatal("NPC_AF_DBG_STATUS", 0, 0, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_DBG_STATUS bdk_npc_af_dbg_status_t
#define bustype_BDK_NPC_AF_DBG_STATUS BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_DBG_STATUS "NPC_AF_DBG_STATUS"
#define device_bar_BDK_NPC_AF_DBG_STATUS 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_DBG_STATUS 0
#define arguments_BDK_NPC_AF_DBG_STATUS -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_dv_fc_scratch
 *
 * AF INTERNAL: NPC Scratch Register
 *
 * Internal:
 * This register is for internal DV purpose.
 */
union bdk_npc_af_dv_fc_scratch
{
    uint64_t u;
    struct bdk_npc_af_dv_fc_scratch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t it                    : 64; /**< [ 63:  0](R/W) Internal:
                                                                 This set of bits are specified for DV only. */
#else /* Word 0 - Little Endian */
        uint64_t it                    : 64; /**< [ 63:  0](R/W) Internal:
                                                                 This set of bits are specified for DV only. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_dv_fc_scratch_s cn; */
};
typedef union bdk_npc_af_dv_fc_scratch bdk_npc_af_dv_fc_scratch_t;

#define BDK_NPC_AF_DV_FC_SCRATCH BDK_NPC_AF_DV_FC_SCRATCH_FUNC()
static inline uint64_t BDK_NPC_AF_DV_FC_SCRATCH_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_DV_FC_SCRATCH_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x850060000060ll;
    __bdk_csr_fatal("NPC_AF_DV_FC_SCRATCH", 0, 0, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_DV_FC_SCRATCH bdk_npc_af_dv_fc_scratch_t
#define bustype_BDK_NPC_AF_DV_FC_SCRATCH BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_DV_FC_SCRATCH "NPC_AF_DV_FC_SCRATCH"
#define device_bar_BDK_NPC_AF_DV_FC_SCRATCH 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_DV_FC_SCRATCH 0
#define arguments_BDK_NPC_AF_DV_FC_SCRATCH -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_eco0
 *
 * INTERNAL: ECO 0 Register
 */
union bdk_npc_af_eco0
{
    uint64_t u;
    struct bdk_npc_af_eco0_s
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
    /* struct bdk_npc_af_eco0_s cn; */
};
typedef union bdk_npc_af_eco0 bdk_npc_af_eco0_t;

#define BDK_NPC_AF_ECO0 BDK_NPC_AF_ECO0_FUNC()
static inline uint64_t BDK_NPC_AF_ECO0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_ECO0_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x850060000200ll;
    __bdk_csr_fatal("NPC_AF_ECO0", 0, 0, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_ECO0 bdk_npc_af_eco0_t
#define bustype_BDK_NPC_AF_ECO0 BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_ECO0 "NPC_AF_ECO0"
#define device_bar_BDK_NPC_AF_ECO0 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_ECO0 0
#define arguments_BDK_NPC_AF_ECO0 -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_ikpu_err_ctl
 *
 * NPC AF Initial KPU Error Control Registers
 * Similar to NPC_AF_KPU()_ERR_CTL, but specifies values captured in
 * NPC_RESULT_S[ERRLEV,ERRCODE] for errors detected by the PKIND-based initial
 * actions from NPC_AF_PKIND()_ACTION0 and NPC_AF_PKIND()_ACTION1.
 * [DP_OFFSET_ERRCODE] from this register is never used.
 */
union bdk_npc_af_ikpu_err_ctl
{
    uint64_t u;
    struct bdk_npc_af_ikpu_err_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_28_63        : 36;
        uint64_t var_len_offset_errcode : 8; /**< [ 27: 20](R/W) Variable length offset error code. Value captured in NPC_RESULT_S[ERRCODE]
                                                                 when a required variable offset byte as defined by
                                                                 NPC_AF_KPU()_ENTRY()_ACTION0[VAR_LEN_OFFSET], if any, is beyond the end of
                                                                 packet's header (smaller of 256 bytes or end of packet). */
        uint64_t ptr_advance_errcode   : 8;  /**< [ 19: 12](R/W) Pointer advance error code. Value captured in NPC_RESULT_S[ERRCODE] when
                                                                 the computed pointer advance value (ptr_advance + var_len_advance, as
                                                                 defined for NPC_AF_KPU()_ENTRY()_ACTION0[VAR_LEN_OFFSET]) points beyond the
                                                                 end of packet, or points to a byte offset greater than 255. */
        uint64_t dp_offset_errcode     : 8;  /**< [ 11:  4](R/W) Decision point offset error code. Value captured in NPC_RESULT_S[ERRCODE]
                                                                 when at least one byte of a decision point from the previous
                                                                 non-bypassed KPU is beyond the end of packet's header (smaller of 256 bytes
                                                                 or end of packet).

                                                                 Note that this error is captured by the KPU which would have extracted the
                                                                 decision point data from the previous non-bypassed KPU, i.e. when the
                                                                 following conditions are true:
                                                                 * NPC_AF_KPU()_ENTRY()_ACTION0[PARSE_DONE] is clear.
                                                                 * NPC_AF_KPU()_CFG[ENA] is set.
                                                                 * Remaining NPC_AF_KPU()_ENTRY()_ACTION0[BYP_COUNT] after decrementing by the
                                                                 number of bypassed KPUs is zero.
                                                                 * At least one decision point byte (specified by
                                                                 NPC_AF_KPU()_ENTRY()_ACTION1[DP*_OFFSET] from the previous non-bypassed KPU)
                                                                 is beyond the end of packet's header. */
        uint64_t errlev                : 4;  /**< [  3:  0](R/W) Value captured in NPC_RESULT_S[ERRLEV] when an error specified by other
                                                                 fields in this register is detected. A capture for any of these errors
                                                                 terminates the header parse and sets NPC_AF_KPU()_ENTRY()_ACTION0[PARSE_DONE].
                                                                 The error capture priority is as follows (highest to lowest):
                                                                 * [VAR_LEN_OFFSET_ERRCODE] in current KPU.
                                                                 * [PTR_ADVANCE_ERRCODE] in current KPU.
                                                                 * [DP_OFFSET_ERRCODE] in next non-bypassed KPU. */
#else /* Word 0 - Little Endian */
        uint64_t errlev                : 4;  /**< [  3:  0](R/W) Value captured in NPC_RESULT_S[ERRLEV] when an error specified by other
                                                                 fields in this register is detected. A capture for any of these errors
                                                                 terminates the header parse and sets NPC_AF_KPU()_ENTRY()_ACTION0[PARSE_DONE].
                                                                 The error capture priority is as follows (highest to lowest):
                                                                 * [VAR_LEN_OFFSET_ERRCODE] in current KPU.
                                                                 * [PTR_ADVANCE_ERRCODE] in current KPU.
                                                                 * [DP_OFFSET_ERRCODE] in next non-bypassed KPU. */
        uint64_t dp_offset_errcode     : 8;  /**< [ 11:  4](R/W) Decision point offset error code. Value captured in NPC_RESULT_S[ERRCODE]
                                                                 when at least one byte of a decision point from the previous
                                                                 non-bypassed KPU is beyond the end of packet's header (smaller of 256 bytes
                                                                 or end of packet).

                                                                 Note that this error is captured by the KPU which would have extracted the
                                                                 decision point data from the previous non-bypassed KPU, i.e. when the
                                                                 following conditions are true:
                                                                 * NPC_AF_KPU()_ENTRY()_ACTION0[PARSE_DONE] is clear.
                                                                 * NPC_AF_KPU()_CFG[ENA] is set.
                                                                 * Remaining NPC_AF_KPU()_ENTRY()_ACTION0[BYP_COUNT] after decrementing by the
                                                                 number of bypassed KPUs is zero.
                                                                 * At least one decision point byte (specified by
                                                                 NPC_AF_KPU()_ENTRY()_ACTION1[DP*_OFFSET] from the previous non-bypassed KPU)
                                                                 is beyond the end of packet's header. */
        uint64_t ptr_advance_errcode   : 8;  /**< [ 19: 12](R/W) Pointer advance error code. Value captured in NPC_RESULT_S[ERRCODE] when
                                                                 the computed pointer advance value (ptr_advance + var_len_advance, as
                                                                 defined for NPC_AF_KPU()_ENTRY()_ACTION0[VAR_LEN_OFFSET]) points beyond the
                                                                 end of packet, or points to a byte offset greater than 255. */
        uint64_t var_len_offset_errcode : 8; /**< [ 27: 20](R/W) Variable length offset error code. Value captured in NPC_RESULT_S[ERRCODE]
                                                                 when a required variable offset byte as defined by
                                                                 NPC_AF_KPU()_ENTRY()_ACTION0[VAR_LEN_OFFSET], if any, is beyond the end of
                                                                 packet's header (smaller of 256 bytes or end of packet). */
        uint64_t reserved_28_63        : 36;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_ikpu_err_ctl_s cn; */
};
typedef union bdk_npc_af_ikpu_err_ctl bdk_npc_af_ikpu_err_ctl_t;

#define BDK_NPC_AF_IKPU_ERR_CTL BDK_NPC_AF_IKPU_ERR_CTL_FUNC()
static inline uint64_t BDK_NPC_AF_IKPU_ERR_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_IKPU_ERR_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x850063000080ll;
    __bdk_csr_fatal("NPC_AF_IKPU_ERR_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_IKPU_ERR_CTL bdk_npc_af_ikpu_err_ctl_t
#define bustype_BDK_NPC_AF_IKPU_ERR_CTL BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_IKPU_ERR_CTL "NPC_AF_IKPU_ERR_CTL"
#define device_bar_BDK_NPC_AF_IKPU_ERR_CTL 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_IKPU_ERR_CTL 0
#define arguments_BDK_NPC_AF_IKPU_ERR_CTL -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_intf#_cfg
 *
 * NPC AF Interface Configuration Registers
 */
union bdk_npc_af_intfx_cfg
{
    uint64_t u;
    struct bdk_npc_af_intfx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t tbd                   : 64; /**< [ 63:  0](R/W) TBD.
                                                                 Internal:
                                                                 FIXME. */
#else /* Word 0 - Little Endian */
        uint64_t tbd                   : 64; /**< [ 63:  0](R/W) TBD.
                                                                 Internal:
                                                                 FIXME. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_intfx_cfg_s cn; */
};
typedef union bdk_npc_af_intfx_cfg bdk_npc_af_intfx_cfg_t;

static inline uint64_t BDK_NPC_AF_INTFX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_INTFX_CFG(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x850060001000ll + 0x100ll * ((a) & 0x1);
    __bdk_csr_fatal("NPC_AF_INTFX_CFG", 1, a, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_INTFX_CFG(a) bdk_npc_af_intfx_cfg_t
#define bustype_BDK_NPC_AF_INTFX_CFG(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_INTFX_CFG(a) "NPC_AF_INTFX_CFG"
#define device_bar_BDK_NPC_AF_INTFX_CFG(a) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_INTFX_CFG(a) (a)
#define arguments_BDK_NPC_AF_INTFX_CFG(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_intf#_kex_cfg
 *
 * NPC AF Interface Key Extract Configuration Registers
 */
union bdk_npc_af_intfx_kex_cfg
{
    uint64_t u;
    struct bdk_npc_af_intfx_kex_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_35_63        : 29;
        uint64_t keyw                  : 3;  /**< [ 34: 32](R/W) MCAM search key width selection for the interface. Enumerated by NPC_MCAMKEYW_E. */
        uint64_t reserved_31           : 1;
        uint64_t parse_nibble_ena      : 31; /**< [ 30:  0](R/W) Parse key extract nibble enable. Enable bit for each nibble in
                                                                 NPC_PARSE_KEX_S to be included in the MCAM search key: bit 0 for
                                                                 NPC_PARSE_KEX_S[CHAN\<3:0\>], bit 1 for NPC_PARSE_KEX_S[CHAN\<7:4\>], ..., bit
                                                                 30 for NPC_PARSE_KEX_S[LH\<11..8\>]. The extracted nibbles are concatenated
                                                                 and and written to NPC_MCAM_KEY_X*_S, with the first extracted nibble
                                                                 written to the least significant nibble of the key (NPC_MCAM_KEY_X*_S[KW0\<3:0\>]). */
#else /* Word 0 - Little Endian */
        uint64_t parse_nibble_ena      : 31; /**< [ 30:  0](R/W) Parse key extract nibble enable. Enable bit for each nibble in
                                                                 NPC_PARSE_KEX_S to be included in the MCAM search key: bit 0 for
                                                                 NPC_PARSE_KEX_S[CHAN\<3:0\>], bit 1 for NPC_PARSE_KEX_S[CHAN\<7:4\>], ..., bit
                                                                 30 for NPC_PARSE_KEX_S[LH\<11..8\>]. The extracted nibbles are concatenated
                                                                 and and written to NPC_MCAM_KEY_X*_S, with the first extracted nibble
                                                                 written to the least significant nibble of the key (NPC_MCAM_KEY_X*_S[KW0\<3:0\>]). */
        uint64_t reserved_31           : 1;
        uint64_t keyw                  : 3;  /**< [ 34: 32](R/W) MCAM search key width selection for the interface. Enumerated by NPC_MCAMKEYW_E. */
        uint64_t reserved_35_63        : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_intfx_kex_cfg_s cn; */
};
typedef union bdk_npc_af_intfx_kex_cfg bdk_npc_af_intfx_kex_cfg_t;

static inline uint64_t BDK_NPC_AF_INTFX_KEX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_INTFX_KEX_CFG(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x850060001010ll + 0x100ll * ((a) & 0x1);
    __bdk_csr_fatal("NPC_AF_INTFX_KEX_CFG", 1, a, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_INTFX_KEX_CFG(a) bdk_npc_af_intfx_kex_cfg_t
#define bustype_BDK_NPC_AF_INTFX_KEX_CFG(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_INTFX_KEX_CFG(a) "NPC_AF_INTFX_KEX_CFG"
#define device_bar_BDK_NPC_AF_INTFX_KEX_CFG(a) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_INTFX_KEX_CFG(a) (a)
#define arguments_BDK_NPC_AF_INTFX_KEX_CFG(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_intf#_ldata#_flags#_cfg
 *
 * NPC AF Interface Layer Data Flags Configuration Registers
 * These registers control the extraction of layer data (LDATA) into the MCAM search key for each
 * interface based on the FLAGS\<3:0\> bits of two layers selected by NPC_AF_KEX_LDATA()_FLAGS_CFG.
 */
union bdk_npc_af_intfx_ldatax_flagsx_cfg
{
    uint64_t u;
    struct bdk_npc_af_intfx_ldatax_flagsx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t bytesm1               : 4;  /**< [ 19: 16](R/W) LDATA size in bytes minus 1. 0=1 byte; 1=2 bytes, ..., 15=16 bytes. */
        uint64_t hdr_offset            : 8;  /**< [ 15:  8](R/W) Header offset. See NPC_AF_INTF()_LID()_LT()_LD()_CFG[HDR_OFFSET]. */
        uint64_t ena                   : 1;  /**< [  7:  7](R/W) LDATA extract enable. */
        uint64_t reserved_6            : 1;
        uint64_t key_offset            : 6;  /**< [  5:  0](R/W) Key offset. Starting byte offset of LDATA in the MCAM search key.
                                                                 For example, an key offset of 5 means the first LDATA byte is
                                                                 written to NPC_MCAM_KEY_X*_S[KW0\<47:40\>]. */
#else /* Word 0 - Little Endian */
        uint64_t key_offset            : 6;  /**< [  5:  0](R/W) Key offset. Starting byte offset of LDATA in the MCAM search key.
                                                                 For example, an key offset of 5 means the first LDATA byte is
                                                                 written to NPC_MCAM_KEY_X*_S[KW0\<47:40\>]. */
        uint64_t reserved_6            : 1;
        uint64_t ena                   : 1;  /**< [  7:  7](R/W) LDATA extract enable. */
        uint64_t hdr_offset            : 8;  /**< [ 15:  8](R/W) Header offset. See NPC_AF_INTF()_LID()_LT()_LD()_CFG[HDR_OFFSET]. */
        uint64_t bytesm1               : 4;  /**< [ 19: 16](R/W) LDATA size in bytes minus 1. 0=1 byte; 1=2 bytes, ..., 15=16 bytes. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_intfx_ldatax_flagsx_cfg_s cn; */
};
typedef union bdk_npc_af_intfx_ldatax_flagsx_cfg bdk_npc_af_intfx_ldatax_flagsx_cfg_t;

static inline uint64_t BDK_NPC_AF_INTFX_LDATAX_FLAGSX_CFG(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_INTFX_LDATAX_FLAGSX_CFG(unsigned long a, unsigned long b, unsigned long c)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1) && (c<=15)))
        return 0x850060980000ll + 0x10000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1) + 8ll * ((c) & 0xf);
    __bdk_csr_fatal("NPC_AF_INTFX_LDATAX_FLAGSX_CFG", 3, a, b, c, 0);
}

#define typedef_BDK_NPC_AF_INTFX_LDATAX_FLAGSX_CFG(a,b,c) bdk_npc_af_intfx_ldatax_flagsx_cfg_t
#define bustype_BDK_NPC_AF_INTFX_LDATAX_FLAGSX_CFG(a,b,c) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_INTFX_LDATAX_FLAGSX_CFG(a,b,c) "NPC_AF_INTFX_LDATAX_FLAGSX_CFG"
#define device_bar_BDK_NPC_AF_INTFX_LDATAX_FLAGSX_CFG(a,b,c) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_INTFX_LDATAX_FLAGSX_CFG(a,b,c) (a)
#define arguments_BDK_NPC_AF_INTFX_LDATAX_FLAGSX_CFG(a,b,c) (a),(b),(c),-1

/**
 * Register (RVU_PF_BAR0) npc_af_intf#_lid#_lt#_ld#_cfg
 *
 * NPC AF Interface Layer Data Extract Configuration Registers
 * These registers control the extraction of layer data (LDATA) into the MCAM search key for each
 * interface. Up to two LDATA fields can be extracted per layer (LID(0..7) indexed by NPC_LID_E),
 * with up to 16 bytes per LDATA field. For each layer, the corresponding
 * NPC_LAYER_INFO_S[LTYPE] value in NPC_RESULT_S is used as the LTYPE(0..15) index and select the
 * associated LDATA(0..1) registers.
 *
 * NPC_LAYER_INFO_S[LTYPE]=0x0 means the corresponding layer not parsed (invalid), so
 * software should keep NPC_AF_INTF()_LID()_LT(0)_LD()_CFG[ENA] clear to disable extraction.
 * when LTYPE is zero.
 */
union bdk_npc_af_intfx_lidx_ltx_ldx_cfg
{
    uint64_t u;
    struct bdk_npc_af_intfx_lidx_ltx_ldx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t bytesm1               : 4;  /**< [ 19: 16](R/W) LDATA size in bytes minus 1. 0=1 byte; 1=2 bytes, ..., 15=16 bytes. */
        uint64_t hdr_offset            : 8;  /**< [ 15:  8](R/W) Header offset. Starting byte offset of LDATA relative to the start
                                                                 of the matching layer (NPC_LAYER_INFO_S[LPTR]).

                                                                 If any LDATA byte specified by [HDR_OFFSET] and [BYTESM1] is beyond the end
                                                                 of packet's header (smaller of 256 bytes or end of packet), a byte value of
                                                                 zero is used. */
        uint64_t ena                   : 1;  /**< [  7:  7](R/W) LDATA extract enable. */
        uint64_t flags_ena             : 1;  /**< [  6:  6](R/W) Enable FLAGS based extraction. Ignored unless the register's layer
                                                                 ID (LID index) matches NPC_AF_KEX_LDATA()_FLAGS_CFG[LID]. */
        uint64_t key_offset            : 6;  /**< [  5:  0](R/W) Key offset. Starting byte offset of LDATA in the MCAM search key.
                                                                 For example, an key offset of 5 means the first LDATA byte is
                                                                 written to NPC_MCAM_KEY_X*_S[KW0\<47:40\>].
                                                                 Software must ensure that the LDATA bytes specified by [KEY_OFFSET] and
                                                                 [BYTESM1] are within key width selected by NPC_AF_INTF()_KEX_CFG[KEYW].

                                                                 Internal:
                                                                 Hardware drops LDATA bytes beyond the key width. */
#else /* Word 0 - Little Endian */
        uint64_t key_offset            : 6;  /**< [  5:  0](R/W) Key offset. Starting byte offset of LDATA in the MCAM search key.
                                                                 For example, an key offset of 5 means the first LDATA byte is
                                                                 written to NPC_MCAM_KEY_X*_S[KW0\<47:40\>].
                                                                 Software must ensure that the LDATA bytes specified by [KEY_OFFSET] and
                                                                 [BYTESM1] are within key width selected by NPC_AF_INTF()_KEX_CFG[KEYW].

                                                                 Internal:
                                                                 Hardware drops LDATA bytes beyond the key width. */
        uint64_t flags_ena             : 1;  /**< [  6:  6](R/W) Enable FLAGS based extraction. Ignored unless the register's layer
                                                                 ID (LID index) matches NPC_AF_KEX_LDATA()_FLAGS_CFG[LID]. */
        uint64_t ena                   : 1;  /**< [  7:  7](R/W) LDATA extract enable. */
        uint64_t hdr_offset            : 8;  /**< [ 15:  8](R/W) Header offset. Starting byte offset of LDATA relative to the start
                                                                 of the matching layer (NPC_LAYER_INFO_S[LPTR]).

                                                                 If any LDATA byte specified by [HDR_OFFSET] and [BYTESM1] is beyond the end
                                                                 of packet's header (smaller of 256 bytes or end of packet), a byte value of
                                                                 zero is used. */
        uint64_t bytesm1               : 4;  /**< [ 19: 16](R/W) LDATA size in bytes minus 1. 0=1 byte; 1=2 bytes, ..., 15=16 bytes. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_intfx_lidx_ltx_ldx_cfg_s cn; */
};
typedef union bdk_npc_af_intfx_lidx_ltx_ldx_cfg bdk_npc_af_intfx_lidx_ltx_ldx_cfg_t;

static inline uint64_t BDK_NPC_AF_INTFX_LIDX_LTX_LDX_CFG(unsigned long a, unsigned long b, unsigned long c, unsigned long d) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_INTFX_LIDX_LTX_LDX_CFG(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=7) && (c<=15) && (d<=1)))
        return 0x850060900000ll + 0x10000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x7) + 0x20ll * ((c) & 0xf) + 8ll * ((d) & 0x1);
    __bdk_csr_fatal("NPC_AF_INTFX_LIDX_LTX_LDX_CFG", 4, a, b, c, d);
}

#define typedef_BDK_NPC_AF_INTFX_LIDX_LTX_LDX_CFG(a,b,c,d) bdk_npc_af_intfx_lidx_ltx_ldx_cfg_t
#define bustype_BDK_NPC_AF_INTFX_LIDX_LTX_LDX_CFG(a,b,c,d) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_INTFX_LIDX_LTX_LDX_CFG(a,b,c,d) "NPC_AF_INTFX_LIDX_LTX_LDX_CFG"
#define device_bar_BDK_NPC_AF_INTFX_LIDX_LTX_LDX_CFG(a,b,c,d) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_INTFX_LIDX_LTX_LDX_CFG(a,b,c,d) (a)
#define arguments_BDK_NPC_AF_INTFX_LIDX_LTX_LDX_CFG(a,b,c,d) (a),(b),(c),(d)

/**
 * Register (RVU_PF_BAR0) npc_af_intf#_miss_act
 *
 * NPC AF Interface MCAM Miss Action Data Registers
 * When a combination of NPC_AF_MCAME()_BANK()_CAM()_* and
 * NPC_AF_MCAME()_BANK()_CFG[ENA] yields an MCAM miss for a packet, this
 * register specifies the packet's match action captured in NPC_RESULT_S[ACTION].
 */
union bdk_npc_af_intfx_miss_act
{
    uint64_t u;
    struct bdk_npc_af_intfx_miss_act_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t action                : 64; /**< [ 63:  0](R/W) Match action. Format is NIX_RX_ACTION_S for RX packet, NIX_TX_ACTION_S for
                                                                 TX packet. */
#else /* Word 0 - Little Endian */
        uint64_t action                : 64; /**< [ 63:  0](R/W) Match action. Format is NIX_RX_ACTION_S for RX packet, NIX_TX_ACTION_S for
                                                                 TX packet. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_intfx_miss_act_s cn; */
};
typedef union bdk_npc_af_intfx_miss_act bdk_npc_af_intfx_miss_act_t;

static inline uint64_t BDK_NPC_AF_INTFX_MISS_ACT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_INTFX_MISS_ACT(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x850061a00000ll + 0x10ll * ((a) & 0x1);
    __bdk_csr_fatal("NPC_AF_INTFX_MISS_ACT", 1, a, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_INTFX_MISS_ACT(a) bdk_npc_af_intfx_miss_act_t
#define bustype_BDK_NPC_AF_INTFX_MISS_ACT(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_INTFX_MISS_ACT(a) "NPC_AF_INTFX_MISS_ACT"
#define device_bar_BDK_NPC_AF_INTFX_MISS_ACT(a) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_INTFX_MISS_ACT(a) (a)
#define arguments_BDK_NPC_AF_INTFX_MISS_ACT(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_intf#_miss_tag_act
 *
 * NPC AF Interface MCAM Miss VTag Action Data Registers
 * When a combination of NPC_AF_MCAME()_BANK()_CAM()_* and
 * NPC_AF_MCAME()_BANK()_CFG[ENA] yields an MCAM miss for a packet, this
 * register specifies the packet's match Vtag action captured in
 * NPC_RESULT_S[VTAG_ACTION].
 */
union bdk_npc_af_intfx_miss_tag_act
{
    uint64_t u;
    struct bdk_npc_af_intfx_miss_tag_act_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t vtag_action           : 64; /**< [ 63:  0](R/W) Match Vtag action. Format is NIX_RX_VTAG_ACTION_S for RX packet,
                                                                 NIX_TX_VTAG_ACTION_S for TX packet. */
#else /* Word 0 - Little Endian */
        uint64_t vtag_action           : 64; /**< [ 63:  0](R/W) Match Vtag action. Format is NIX_RX_VTAG_ACTION_S for RX packet,
                                                                 NIX_TX_VTAG_ACTION_S for TX packet. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_intfx_miss_tag_act_s cn; */
};
typedef union bdk_npc_af_intfx_miss_tag_act bdk_npc_af_intfx_miss_tag_act_t;

static inline uint64_t BDK_NPC_AF_INTFX_MISS_TAG_ACT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_INTFX_MISS_TAG_ACT(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x850061b00008ll + 0x10ll * ((a) & 0x1);
    __bdk_csr_fatal("NPC_AF_INTFX_MISS_TAG_ACT", 1, a, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_INTFX_MISS_TAG_ACT(a) bdk_npc_af_intfx_miss_tag_act_t
#define bustype_BDK_NPC_AF_INTFX_MISS_TAG_ACT(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_INTFX_MISS_TAG_ACT(a) "NPC_AF_INTFX_MISS_TAG_ACT"
#define device_bar_BDK_NPC_AF_INTFX_MISS_TAG_ACT(a) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_INTFX_MISS_TAG_ACT(a) (a)
#define arguments_BDK_NPC_AF_INTFX_MISS_TAG_ACT(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_intf#_stat
 *
 * NPC AF Interface Statistics Registers
 * Statistics per interface. Index enumerated by NPC_INTF_E
 */
union bdk_npc_af_intfx_stat
{
    uint64_t u;
    struct bdk_npc_af_intfx_stat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t count                 : 48; /**< [ 47:  0](R/W/H) Number of packets processed from the associated interface. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 48; /**< [ 47:  0](R/W/H) Number of packets processed from the associated interface. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_intfx_stat_s cn; */
};
typedef union bdk_npc_af_intfx_stat bdk_npc_af_intfx_stat_t;

static inline uint64_t BDK_NPC_AF_INTFX_STAT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_INTFX_STAT(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x850062000800ll + 0x10ll * ((a) & 0x1);
    __bdk_csr_fatal("NPC_AF_INTFX_STAT", 1, a, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_INTFX_STAT(a) bdk_npc_af_intfx_stat_t
#define bustype_BDK_NPC_AF_INTFX_STAT(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_INTFX_STAT(a) "NPC_AF_INTFX_STAT"
#define device_bar_BDK_NPC_AF_INTFX_STAT(a) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_INTFX_STAT(a) (a)
#define arguments_BDK_NPC_AF_INTFX_STAT(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_kcam_scrub_ctl
 *
 * NPC AF KCAM Scrub Control Register
 */
union bdk_npc_af_kcam_scrub_ctl
{
    uint64_t u;
    struct bdk_npc_af_kcam_scrub_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t toth                  : 4;  /**< [ 19: 16](R/W) CAM scrubber timeout threshold. The timeout timer increments by one each
                                                                 coprocessor-clock cycle, and a single scrub cycle is issued to all CAM's as soon
                                                                 as a timeout occurs when the timer reaches the threshold 2^([TOTH]).
                                                                 The maximum timeout threshold is 2^15 and minimum is every cycle. */
        uint64_t reserved_1_15         : 15;
        uint64_t ena                   : 1;  /**< [  0:  0](R/W) When set enables the CAM scrubber. */
#else /* Word 0 - Little Endian */
        uint64_t ena                   : 1;  /**< [  0:  0](R/W) When set enables the CAM scrubber. */
        uint64_t reserved_1_15         : 15;
        uint64_t toth                  : 4;  /**< [ 19: 16](R/W) CAM scrubber timeout threshold. The timeout timer increments by one each
                                                                 coprocessor-clock cycle, and a single scrub cycle is issued to all CAM's as soon
                                                                 as a timeout occurs when the timer reaches the threshold 2^([TOTH]).
                                                                 The maximum timeout threshold is 2^15 and minimum is every cycle. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_kcam_scrub_ctl_s cn; */
};
typedef union bdk_npc_af_kcam_scrub_ctl bdk_npc_af_kcam_scrub_ctl_t;

#define BDK_NPC_AF_KCAM_SCRUB_CTL BDK_NPC_AF_KCAM_SCRUB_CTL_FUNC()
static inline uint64_t BDK_NPC_AF_KCAM_SCRUB_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_KCAM_SCRUB_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x8500600000b0ll;
    __bdk_csr_fatal("NPC_AF_KCAM_SCRUB_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_KCAM_SCRUB_CTL bdk_npc_af_kcam_scrub_ctl_t
#define bustype_BDK_NPC_AF_KCAM_SCRUB_CTL BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_KCAM_SCRUB_CTL "NPC_AF_KCAM_SCRUB_CTL"
#define device_bar_BDK_NPC_AF_KCAM_SCRUB_CTL 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_KCAM_SCRUB_CTL 0
#define arguments_BDK_NPC_AF_KCAM_SCRUB_CTL -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_kex_ldata#_flags_cfg
 *
 * NPC AF Key Extract Layer Data Flags Configuration Register
 */
union bdk_npc_af_kex_ldatax_flags_cfg
{
    uint64_t u;
    struct bdk_npc_af_kex_ldatax_flags_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t lid                   : 3;  /**< [  2:  0](R/W) Layer ID selected for FLAGS based data extraction. The data
                                                                 extraction is based on the NPC_AF_INTF()_LDATA()_FLAGS()_CFG with
                                                                 matching LDATA index.
                                                                 Enumerated by NPC_LID_E. */
#else /* Word 0 - Little Endian */
        uint64_t lid                   : 3;  /**< [  2:  0](R/W) Layer ID selected for FLAGS based data extraction. The data
                                                                 extraction is based on the NPC_AF_INTF()_LDATA()_FLAGS()_CFG with
                                                                 matching LDATA index.
                                                                 Enumerated by NPC_LID_E. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_kex_ldatax_flags_cfg_s cn; */
};
typedef union bdk_npc_af_kex_ldatax_flags_cfg bdk_npc_af_kex_ldatax_flags_cfg_t;

static inline uint64_t BDK_NPC_AF_KEX_LDATAX_FLAGS_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_KEX_LDATAX_FLAGS_CFG(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x850060000800ll + 8ll * ((a) & 0x1);
    __bdk_csr_fatal("NPC_AF_KEX_LDATAX_FLAGS_CFG", 1, a, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_KEX_LDATAX_FLAGS_CFG(a) bdk_npc_af_kex_ldatax_flags_cfg_t
#define bustype_BDK_NPC_AF_KEX_LDATAX_FLAGS_CFG(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_KEX_LDATAX_FLAGS_CFG(a) "NPC_AF_KEX_LDATAX_FLAGS_CFG"
#define device_bar_BDK_NPC_AF_KEX_LDATAX_FLAGS_CFG(a) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_KEX_LDATAX_FLAGS_CFG(a) (a)
#define arguments_BDK_NPC_AF_KEX_LDATAX_FLAGS_CFG(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_kpu#_cfg
 *
 * NPC AF KPU Configuration Registers
 */
union bdk_npc_af_kpux_cfg
{
    uint64_t u;
    struct bdk_npc_af_kpux_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t ena                   : 1;  /**< [  0:  0](R/W) KPU enable. When clear, the KPU is bypassed, such that packet header data
                                                                 and parse state are directly passed through to the next KPU, or in the case
                                                                 of KPU15 to the key extract processing stage. */
#else /* Word 0 - Little Endian */
        uint64_t ena                   : 1;  /**< [  0:  0](R/W) KPU enable. When clear, the KPU is bypassed, such that packet header data
                                                                 and parse state are directly passed through to the next KPU, or in the case
                                                                 of KPU15 to the key extract processing stage. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_kpux_cfg_s cn; */
};
typedef union bdk_npc_af_kpux_cfg bdk_npc_af_kpux_cfg_t;

static inline uint64_t BDK_NPC_AF_KPUX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_KPUX_CFG(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=15))
        return 0x850060000500ll + 8ll * ((a) & 0xf);
    __bdk_csr_fatal("NPC_AF_KPUX_CFG", 1, a, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_KPUX_CFG(a) bdk_npc_af_kpux_cfg_t
#define bustype_BDK_NPC_AF_KPUX_CFG(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_KPUX_CFG(a) "NPC_AF_KPUX_CFG"
#define device_bar_BDK_NPC_AF_KPUX_CFG(a) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_KPUX_CFG(a) (a)
#define arguments_BDK_NPC_AF_KPUX_CFG(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_kpu#_dbg
 *
 * NPC AF KPU Debug Registers
 * This register contains information for the last packet/lookup for which debug
 * is enabled by NPC_AF_DBG_CTL[INTF_DBG,LKUP_DBG].
 */
union bdk_npc_af_kpux_dbg
{
    uint64_t u;
    struct bdk_npc_af_kpux_dbg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t byp                   : 1;  /**< [  8:  8](RO/H) Set if KPU was bypassed due to NPC_AF_KPU()_ENTRY()_ACTION0[PARSE_DONE] set or
                                                                 non-zero NPC_AF_KPU()_ENTRY()_ACTION0[BYP_COUNT] in a previous stage. */
        uint64_t hit_entry             : 8;  /**< [  7:  0](RO/H) KPU hit entry index. Valid when [BYP] is clear. */
#else /* Word 0 - Little Endian */
        uint64_t hit_entry             : 8;  /**< [  7:  0](RO/H) KPU hit entry index. Valid when [BYP] is clear. */
        uint64_t byp                   : 1;  /**< [  8:  8](RO/H) Set if KPU was bypassed due to NPC_AF_KPU()_ENTRY()_ACTION0[PARSE_DONE] set or
                                                                 non-zero NPC_AF_KPU()_ENTRY()_ACTION0[BYP_COUNT] in a previous stage. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_kpux_dbg_s cn; */
};
typedef union bdk_npc_af_kpux_dbg bdk_npc_af_kpux_dbg_t;

static inline uint64_t BDK_NPC_AF_KPUX_DBG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_KPUX_DBG(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=15))
        return 0x850063000020ll + 0x100ll * ((a) & 0xf);
    __bdk_csr_fatal("NPC_AF_KPUX_DBG", 1, a, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_KPUX_DBG(a) bdk_npc_af_kpux_dbg_t
#define bustype_BDK_NPC_AF_KPUX_DBG(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_KPUX_DBG(a) "NPC_AF_KPUX_DBG"
#define device_bar_BDK_NPC_AF_KPUX_DBG(a) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_KPUX_DBG(a) (a)
#define arguments_BDK_NPC_AF_KPUX_DBG(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_kpu#_entry#_action0
 *
 * NPC AF KPU Entry Action Data 0 Registers
 * When a KPU's search data matches a KPU CAM entry in
 * NPC_AF_KPU()_ENTRY()_CAM(), the corresponding entry action in
 * NPC_AF_KPU()_ENTRY()_ACTION0 and NPC_AF_KPU()_ENTRY()_ACTION1 specifies the
 * next state and operations to perform before exiting the KPU.
 */
union bdk_npc_af_kpux_entryx_action0
{
    uint64_t u;
    struct bdk_npc_af_kpux_entryx_action0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_57_63        : 7;
        uint64_t byp_count             : 3;  /**< [ 56: 54](R/W) Bypass count. When nonzero, specifies the number of enabled KPUs to be
                                                                 bypassed. For example, if the bypass count is two in the matching entry for
                                                                 KPU 3, NPC_AF_KPU(4,6,7)_CFG[ENA] = 1 and NPC_AF_KPU(5)_CFG[ENA] = 0, then:
                                                                 * KPUs 4 and 6 are bypassed.
                                                                 * The matching entry's [NEXT_STATE] and
                                                                 NPC_AF_KPU()_ENTRY()_ACTION1[DP*_OFFSET] in KPU 3 are used for the lookup in
                                                                 KPU 7. */
        uint64_t capture_ena           : 1;  /**< [ 53: 53](R/W) Layer capture enable. When set, layer information is captured in
                                                                 NPC_RESULT_S. When clear, layer information is not captured by the KPU. */
        uint64_t parse_done            : 1;  /**< [ 52: 52](R/W) Parse done. When set, terminate parse after this KPU and bypass subsequent KPUs. */
        uint64_t next_state            : 8;  /**< [ 51: 44](R/W) Search value for ternary comparison with the next KPU's
                                                                 NPC_AF_KPU()_ENTRY()_CAM()[STATE]. */
        uint64_t reserved_43           : 1;
        uint64_t capture_lid           : 3;  /**< [ 42: 40](R/W) Capture layer ID. Specifies the layer for which information is captured in
                                                                 NPC_RESULT_S. Enumerated by NPC_LID_E. */
        uint64_t capture_ltype         : 4;  /**< [ 39: 36](R/W) Capture layer type. When [CAPTURE_ENA] is set, specifies
                                                                 NPC_LAYER_INFO_S[LTYPE] value captured in the approprate layer within
                                                                 NPC_RESULT_S. */
        uint64_t capture_flags         : 8;  /**< [ 35: 28](R/W) Capture flags. When nonzero, specifies which NPC_LAYER_INFO_S[FLAGS] bits
                                                                 to set in the approprate layer within
                                                                 NPC_RESULT_S, as follows:
                                                                 _ NPC_LAYER_INFO_S[FLAGS] |= [CAPTURE_FLAGS]

                                                                 Note that flags are captured irrespective of the [CAPTURE_ENA] value. */
        uint64_t ptr_advance           : 8;  /**< [ 27: 20](R/W) Pointer advance. Fixed value added to NPC_RESULT_S[EOH_PTR]. See also [VAR_LEN_OFFSET]. */
        uint64_t var_len_offset        : 8;  /**< [ 19: 12](R/W) Variable length byte offset. When [VAR_LEN_MASK] is nonzero, byte offset
                                                                 from current header pointer of the packet byte that supplies a variable
                                                                 pointer advance value.

                                                                 The pointer advance algorithm is as follows:

                                                                 \<pre\>
                                                                 var_len_byte = packet byte at (NPC_RESULT_S[EOH_PTR] + [VAR_LEN_OFFSET]);
                                                                 masked_var_len_byte = var_len_byte & [VAR_LEN_MASK];

                                                                 if ([VAR_LEN_RIGHT])
                                                                    var_len_advance = masked_var_len_byte \>\> [VAR_LEN_SHIFT];
                                                                 else
                                                                    var_len_advance = masked_var_len_byte \<\< [VAR_LEN_SHIFT];

                                                                 NPC_RESULT_S[EOH_PTR] += ([PTR_ADVANCE] + var_len_advance);
                                                                 \</pre\> */
        uint64_t var_len_mask          : 8;  /**< [ 11:  4](R/W) Variable length mask. See [VAR_LEN_OFFSET]. */
        uint64_t var_len_right         : 1;  /**< [  3:  3](R/W) Variable length shift direction.
                                                                 0 = Left shift.
                                                                 1 = Right shift. */
        uint64_t var_len_shift         : 3;  /**< [  2:  0](R/W) Variable length shift size in bits. See [VAR_LEN_OFFSET]. */
#else /* Word 0 - Little Endian */
        uint64_t var_len_shift         : 3;  /**< [  2:  0](R/W) Variable length shift size in bits. See [VAR_LEN_OFFSET]. */
        uint64_t var_len_right         : 1;  /**< [  3:  3](R/W) Variable length shift direction.
                                                                 0 = Left shift.
                                                                 1 = Right shift. */
        uint64_t var_len_mask          : 8;  /**< [ 11:  4](R/W) Variable length mask. See [VAR_LEN_OFFSET]. */
        uint64_t var_len_offset        : 8;  /**< [ 19: 12](R/W) Variable length byte offset. When [VAR_LEN_MASK] is nonzero, byte offset
                                                                 from current header pointer of the packet byte that supplies a variable
                                                                 pointer advance value.

                                                                 The pointer advance algorithm is as follows:

                                                                 \<pre\>
                                                                 var_len_byte = packet byte at (NPC_RESULT_S[EOH_PTR] + [VAR_LEN_OFFSET]);
                                                                 masked_var_len_byte = var_len_byte & [VAR_LEN_MASK];

                                                                 if ([VAR_LEN_RIGHT])
                                                                    var_len_advance = masked_var_len_byte \>\> [VAR_LEN_SHIFT];
                                                                 else
                                                                    var_len_advance = masked_var_len_byte \<\< [VAR_LEN_SHIFT];

                                                                 NPC_RESULT_S[EOH_PTR] += ([PTR_ADVANCE] + var_len_advance);
                                                                 \</pre\> */
        uint64_t ptr_advance           : 8;  /**< [ 27: 20](R/W) Pointer advance. Fixed value added to NPC_RESULT_S[EOH_PTR]. See also [VAR_LEN_OFFSET]. */
        uint64_t capture_flags         : 8;  /**< [ 35: 28](R/W) Capture flags. When nonzero, specifies which NPC_LAYER_INFO_S[FLAGS] bits
                                                                 to set in the approprate layer within
                                                                 NPC_RESULT_S, as follows:
                                                                 _ NPC_LAYER_INFO_S[FLAGS] |= [CAPTURE_FLAGS]

                                                                 Note that flags are captured irrespective of the [CAPTURE_ENA] value. */
        uint64_t capture_ltype         : 4;  /**< [ 39: 36](R/W) Capture layer type. When [CAPTURE_ENA] is set, specifies
                                                                 NPC_LAYER_INFO_S[LTYPE] value captured in the approprate layer within
                                                                 NPC_RESULT_S. */
        uint64_t capture_lid           : 3;  /**< [ 42: 40](R/W) Capture layer ID. Specifies the layer for which information is captured in
                                                                 NPC_RESULT_S. Enumerated by NPC_LID_E. */
        uint64_t reserved_43           : 1;
        uint64_t next_state            : 8;  /**< [ 51: 44](R/W) Search value for ternary comparison with the next KPU's
                                                                 NPC_AF_KPU()_ENTRY()_CAM()[STATE]. */
        uint64_t parse_done            : 1;  /**< [ 52: 52](R/W) Parse done. When set, terminate parse after this KPU and bypass subsequent KPUs. */
        uint64_t capture_ena           : 1;  /**< [ 53: 53](R/W) Layer capture enable. When set, layer information is captured in
                                                                 NPC_RESULT_S. When clear, layer information is not captured by the KPU. */
        uint64_t byp_count             : 3;  /**< [ 56: 54](R/W) Bypass count. When nonzero, specifies the number of enabled KPUs to be
                                                                 bypassed. For example, if the bypass count is two in the matching entry for
                                                                 KPU 3, NPC_AF_KPU(4,6,7)_CFG[ENA] = 1 and NPC_AF_KPU(5)_CFG[ENA] = 0, then:
                                                                 * KPUs 4 and 6 are bypassed.
                                                                 * The matching entry's [NEXT_STATE] and
                                                                 NPC_AF_KPU()_ENTRY()_ACTION1[DP*_OFFSET] in KPU 3 are used for the lookup in
                                                                 KPU 7. */
        uint64_t reserved_57_63        : 7;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_kpux_entryx_action0_s cn; */
};
typedef union bdk_npc_af_kpux_entryx_action0 bdk_npc_af_kpux_entryx_action0_t;

static inline uint64_t BDK_NPC_AF_KPUX_ENTRYX_ACTION0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_KPUX_ENTRYX_ACTION0(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=15) && (b<=127)))
        return 0x850060100020ll + 0x4000ll * ((a) & 0xf) + 0x40ll * ((b) & 0x7f);
    __bdk_csr_fatal("NPC_AF_KPUX_ENTRYX_ACTION0", 2, a, b, 0, 0);
}

#define typedef_BDK_NPC_AF_KPUX_ENTRYX_ACTION0(a,b) bdk_npc_af_kpux_entryx_action0_t
#define bustype_BDK_NPC_AF_KPUX_ENTRYX_ACTION0(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_KPUX_ENTRYX_ACTION0(a,b) "NPC_AF_KPUX_ENTRYX_ACTION0"
#define device_bar_BDK_NPC_AF_KPUX_ENTRYX_ACTION0(a,b) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_KPUX_ENTRYX_ACTION0(a,b) (a)
#define arguments_BDK_NPC_AF_KPUX_ENTRYX_ACTION0(a,b) (a),(b),-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_kpu#_entry#_action1
 *
 * NPC AF KPU Entry Action Data 0 Registers
 * See NPC_AF_KPU()_ENTRY()_ACTION0.
 */
union bdk_npc_af_kpux_entryx_action1
{
    uint64_t u;
    struct bdk_npc_af_kpux_entryx_action1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t errlev                : 4;  /**< [ 35: 32](R/W) Error level. Ignored when [ERRCODE] is zero. Otherwise, value is captured
                                                                 in NPC_RESULT_S[ERRLEV], indicating the protocol layer containing the
                                                                 error.  Enumerated by NPC_ERRLEV_E. */
        uint64_t errcode               : 8;  /**< [ 31: 24](R/W) Error code. Ignored when zero. When nonzero, [ERRCODE] is captured in
                                                                 NPC_RESULT_S[ERRCODE] and [ERRLEV] is captured in NPC_RESULT_S[ERRLEV] */
        uint64_t dp2_offset            : 8;  /**< [ 23: 16](R/W) Decision point 2 offset to next KPU. See [DP0_OFFSET]. */
        uint64_t dp1_offset            : 8;  /**< [ 15:  8](R/W) Decision point 1 offset to next KPU. See [DP0_OFFSET]. */
        uint64_t dp0_offset            : 8;  /**< [  7:  0](R/W) Decision point 0 offset to next KPU. Byte offset relative to the
                                                                 updated NPC_RESULT_S[EOH_PTR] value of the two packet bytes used for
                                                                 ternary comparison with the next KPU's
                                                                 NPC_AF_KPU()_ENTRY()_CAM()[DP0_DATA]. */
#else /* Word 0 - Little Endian */
        uint64_t dp0_offset            : 8;  /**< [  7:  0](R/W) Decision point 0 offset to next KPU. Byte offset relative to the
                                                                 updated NPC_RESULT_S[EOH_PTR] value of the two packet bytes used for
                                                                 ternary comparison with the next KPU's
                                                                 NPC_AF_KPU()_ENTRY()_CAM()[DP0_DATA]. */
        uint64_t dp1_offset            : 8;  /**< [ 15:  8](R/W) Decision point 1 offset to next KPU. See [DP0_OFFSET]. */
        uint64_t dp2_offset            : 8;  /**< [ 23: 16](R/W) Decision point 2 offset to next KPU. See [DP0_OFFSET]. */
        uint64_t errcode               : 8;  /**< [ 31: 24](R/W) Error code. Ignored when zero. When nonzero, [ERRCODE] is captured in
                                                                 NPC_RESULT_S[ERRCODE] and [ERRLEV] is captured in NPC_RESULT_S[ERRLEV] */
        uint64_t errlev                : 4;  /**< [ 35: 32](R/W) Error level. Ignored when [ERRCODE] is zero. Otherwise, value is captured
                                                                 in NPC_RESULT_S[ERRLEV], indicating the protocol layer containing the
                                                                 error.  Enumerated by NPC_ERRLEV_E. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_kpux_entryx_action1_s cn; */
};
typedef union bdk_npc_af_kpux_entryx_action1 bdk_npc_af_kpux_entryx_action1_t;

static inline uint64_t BDK_NPC_AF_KPUX_ENTRYX_ACTION1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_KPUX_ENTRYX_ACTION1(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=15) && (b<=127)))
        return 0x850060100028ll + 0x4000ll * ((a) & 0xf) + 0x40ll * ((b) & 0x7f);
    __bdk_csr_fatal("NPC_AF_KPUX_ENTRYX_ACTION1", 2, a, b, 0, 0);
}

#define typedef_BDK_NPC_AF_KPUX_ENTRYX_ACTION1(a,b) bdk_npc_af_kpux_entryx_action1_t
#define bustype_BDK_NPC_AF_KPUX_ENTRYX_ACTION1(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_KPUX_ENTRYX_ACTION1(a,b) "NPC_AF_KPUX_ENTRYX_ACTION1"
#define device_bar_BDK_NPC_AF_KPUX_ENTRYX_ACTION1(a,b) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_KPUX_ENTRYX_ACTION1(a,b) (a)
#define arguments_BDK_NPC_AF_KPUX_ENTRYX_ACTION1(a,b) (a),(b),-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_kpu#_entry#_cam#
 *
 * NPC AF KPU Entry CAM Registers
 * KPU comparison ternary data. The field values in
 * NPC_AF_KPU()_ENTRY()_CAM() are ternary, where  each data bit of the
 * search key matches as follows:
 * _ [CAM(1)]\<n\>=0, [CAM(0)]\<n\>=0: Always match; search key data\<n\> don't care.
 * _ [CAM(1)]\<n\>=0, [CAM(0)]\<n\>=1: Match when search key data\<n\> == 0.
 * _ [CAM(1)]\<n\>=1, [CAM(0)]\<n\>=0: Match when search key data\<n\> == 1.
 * _ [CAM(1)]\<n\>=1, [CAM(0)]\<n\>=1: Reserved.
 *
 * The reserved combination is not allowed. Hardware suppresses any write to
 * CAM(0) or CAM(1) that would result in the reserved combination for any CAM bit.
 *
 * Software must program a default entry for each KPU, e.g. by programming each
 * KPU's last entry {b} (NPC_AF_KPU()_ENTRY({b})_CAM()) to always match all
 * bits.
 */
union bdk_npc_af_kpux_entryx_camx
{
    uint64_t u;
    struct bdk_npc_af_kpux_entryx_camx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_56_63        : 8;
        uint64_t state                 : 8;  /**< [ 55: 48](R/W) Current parse state. */
        uint64_t dp2_data              : 16; /**< [ 47: 32](R/W) Decision point 2 data. */
        uint64_t dp1_data              : 16; /**< [ 31: 16](R/W) Decision point 1 data. */
        uint64_t dp0_data              : 16; /**< [ 15:  0](R/W) Decision point 0 data. */
#else /* Word 0 - Little Endian */
        uint64_t dp0_data              : 16; /**< [ 15:  0](R/W) Decision point 0 data. */
        uint64_t dp1_data              : 16; /**< [ 31: 16](R/W) Decision point 1 data. */
        uint64_t dp2_data              : 16; /**< [ 47: 32](R/W) Decision point 2 data. */
        uint64_t state                 : 8;  /**< [ 55: 48](R/W) Current parse state. */
        uint64_t reserved_56_63        : 8;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_kpux_entryx_camx_s cn; */
};
typedef union bdk_npc_af_kpux_entryx_camx bdk_npc_af_kpux_entryx_camx_t;

static inline uint64_t BDK_NPC_AF_KPUX_ENTRYX_CAMX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_KPUX_ENTRYX_CAMX(unsigned long a, unsigned long b, unsigned long c)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=15) && (b<=127) && (c<=1)))
        return 0x850060100000ll + 0x4000ll * ((a) & 0xf) + 0x40ll * ((b) & 0x7f) + 8ll * ((c) & 0x1);
    __bdk_csr_fatal("NPC_AF_KPUX_ENTRYX_CAMX", 3, a, b, c, 0);
}

#define typedef_BDK_NPC_AF_KPUX_ENTRYX_CAMX(a,b,c) bdk_npc_af_kpux_entryx_camx_t
#define bustype_BDK_NPC_AF_KPUX_ENTRYX_CAMX(a,b,c) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_KPUX_ENTRYX_CAMX(a,b,c) "NPC_AF_KPUX_ENTRYX_CAMX"
#define device_bar_BDK_NPC_AF_KPUX_ENTRYX_CAMX(a,b,c) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_KPUX_ENTRYX_CAMX(a,b,c) (a)
#define arguments_BDK_NPC_AF_KPUX_ENTRYX_CAMX(a,b,c) (a),(b),(c),-1

/**
 * Register (RVU_PF_BAR0) npc_af_kpu#_entry_dis#
 *
 * NPC AF KPU Entry Disable Registers
 * See NPC_AF_KPU()_ENTRY()_ACTION0.
 */
union bdk_npc_af_kpux_entry_disx
{
    uint64_t u;
    struct bdk_npc_af_kpux_entry_disx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dis                   : 64; /**< [ 63:  0](R/W) Entry disables. One bit per KPU entry; NPC_AF_KPU()_ENTRY_DIS(0)[DIS\<63:0\>] for
                                                                 entries 63-0, NPC_AF_KPU()_ENTRY_DIS(1)[DIS\<63:0\>] for entries 127-64. Setting a
                                                                 bit disables the corresponding KPU entry, and clearing the bit enables the
                                                                 entry. */
#else /* Word 0 - Little Endian */
        uint64_t dis                   : 64; /**< [ 63:  0](R/W) Entry disables. One bit per KPU entry; NPC_AF_KPU()_ENTRY_DIS(0)[DIS\<63:0\>] for
                                                                 entries 63-0, NPC_AF_KPU()_ENTRY_DIS(1)[DIS\<63:0\>] for entries 127-64. Setting a
                                                                 bit disables the corresponding KPU entry, and clearing the bit enables the
                                                                 entry. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_kpux_entry_disx_s cn; */
};
typedef union bdk_npc_af_kpux_entry_disx bdk_npc_af_kpux_entry_disx_t;

static inline uint64_t BDK_NPC_AF_KPUX_ENTRY_DISX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_KPUX_ENTRY_DISX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=15) && (b<=1)))
        return 0x850060180000ll + 0x40ll * ((a) & 0xf) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("NPC_AF_KPUX_ENTRY_DISX", 2, a, b, 0, 0);
}

#define typedef_BDK_NPC_AF_KPUX_ENTRY_DISX(a,b) bdk_npc_af_kpux_entry_disx_t
#define bustype_BDK_NPC_AF_KPUX_ENTRY_DISX(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_KPUX_ENTRY_DISX(a,b) "NPC_AF_KPUX_ENTRY_DISX"
#define device_bar_BDK_NPC_AF_KPUX_ENTRY_DISX(a,b) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_KPUX_ENTRY_DISX(a,b) (a)
#define arguments_BDK_NPC_AF_KPUX_ENTRY_DISX(a,b) (a),(b),-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_kpu#_err_ctl
 *
 * NPC AF KPU Error Control Registers
 * This register specifies values captured in NPC_RESULT_S[ERRLEV,ERRCODE] when errors
 * are detected by a KPU.
 */
union bdk_npc_af_kpux_err_ctl
{
    uint64_t u;
    struct bdk_npc_af_kpux_err_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_28_63        : 36;
        uint64_t var_len_offset_errcode : 8; /**< [ 27: 20](R/W) Variable length offset error code. Value captured in NPC_RESULT_S[ERRCODE]
                                                                 when a required variable offset byte as defined by
                                                                 NPC_AF_KPU()_ENTRY()_ACTION0[VAR_LEN_OFFSET], if any, is beyond the end of
                                                                 packet's header (smaller of 256 bytes or end of packet). */
        uint64_t ptr_advance_errcode   : 8;  /**< [ 19: 12](R/W) Pointer advance error code. Value captured in NPC_RESULT_S[ERRCODE] when
                                                                 the computed pointer advance value (ptr_advance + var_len_advance, as
                                                                 defined for NPC_AF_KPU()_ENTRY()_ACTION0[VAR_LEN_OFFSET]) points beyond the
                                                                 end of packet, or points to a byte offset greater than 255. */
        uint64_t dp_offset_errcode     : 8;  /**< [ 11:  4](R/W) Decision point offset error code. Value captured in NPC_RESULT_S[ERRCODE]
                                                                 when at least one byte of a decision point from the previous
                                                                 non-bypassed KPU is beyond the end of packet's header (smaller of 256 bytes
                                                                 or end of packet).

                                                                 Note that this error is captured by the KPU which would have extracted the
                                                                 decision point data from the previous non-bypassed KPU, i.e. when the
                                                                 following conditions are true:
                                                                 * NPC_AF_KPU()_ENTRY()_ACTION0[PARSE_DONE] is clear.
                                                                 * NPC_AF_KPU()_CFG[ENA] is set.
                                                                 * Remaining NPC_AF_KPU()_ENTRY()_ACTION0[BYP_COUNT] after decrementing by the
                                                                 number of bypassed KPUs is zero.
                                                                 * At least one decision point byte (specified by
                                                                 NPC_AF_KPU()_ENTRY()_ACTION1[DP*_OFFSET] from the previous non-bypassed KPU)
                                                                 is beyond the end of packet's header. */
        uint64_t errlev                : 4;  /**< [  3:  0](R/W) Value captured in NPC_RESULT_S[ERRLEV] when an error specified by other
                                                                 fields in this register is detected. A capture for any of these errors
                                                                 terminates the header parse and sets NPC_AF_KPU()_ENTRY()_ACTION0[PARSE_DONE].
                                                                 The error capture priority is as follows (highest to lowest):
                                                                 * [VAR_LEN_OFFSET_ERRCODE] in current KPU.
                                                                 * [PTR_ADVANCE_ERRCODE] in current KPU.
                                                                 * [DP_OFFSET_ERRCODE] in next non-bypassed KPU. */
#else /* Word 0 - Little Endian */
        uint64_t errlev                : 4;  /**< [  3:  0](R/W) Value captured in NPC_RESULT_S[ERRLEV] when an error specified by other
                                                                 fields in this register is detected. A capture for any of these errors
                                                                 terminates the header parse and sets NPC_AF_KPU()_ENTRY()_ACTION0[PARSE_DONE].
                                                                 The error capture priority is as follows (highest to lowest):
                                                                 * [VAR_LEN_OFFSET_ERRCODE] in current KPU.
                                                                 * [PTR_ADVANCE_ERRCODE] in current KPU.
                                                                 * [DP_OFFSET_ERRCODE] in next non-bypassed KPU. */
        uint64_t dp_offset_errcode     : 8;  /**< [ 11:  4](R/W) Decision point offset error code. Value captured in NPC_RESULT_S[ERRCODE]
                                                                 when at least one byte of a decision point from the previous
                                                                 non-bypassed KPU is beyond the end of packet's header (smaller of 256 bytes
                                                                 or end of packet).

                                                                 Note that this error is captured by the KPU which would have extracted the
                                                                 decision point data from the previous non-bypassed KPU, i.e. when the
                                                                 following conditions are true:
                                                                 * NPC_AF_KPU()_ENTRY()_ACTION0[PARSE_DONE] is clear.
                                                                 * NPC_AF_KPU()_CFG[ENA] is set.
                                                                 * Remaining NPC_AF_KPU()_ENTRY()_ACTION0[BYP_COUNT] after decrementing by the
                                                                 number of bypassed KPUs is zero.
                                                                 * At least one decision point byte (specified by
                                                                 NPC_AF_KPU()_ENTRY()_ACTION1[DP*_OFFSET] from the previous non-bypassed KPU)
                                                                 is beyond the end of packet's header. */
        uint64_t ptr_advance_errcode   : 8;  /**< [ 19: 12](R/W) Pointer advance error code. Value captured in NPC_RESULT_S[ERRCODE] when
                                                                 the computed pointer advance value (ptr_advance + var_len_advance, as
                                                                 defined for NPC_AF_KPU()_ENTRY()_ACTION0[VAR_LEN_OFFSET]) points beyond the
                                                                 end of packet, or points to a byte offset greater than 255. */
        uint64_t var_len_offset_errcode : 8; /**< [ 27: 20](R/W) Variable length offset error code. Value captured in NPC_RESULT_S[ERRCODE]
                                                                 when a required variable offset byte as defined by
                                                                 NPC_AF_KPU()_ENTRY()_ACTION0[VAR_LEN_OFFSET], if any, is beyond the end of
                                                                 packet's header (smaller of 256 bytes or end of packet). */
        uint64_t reserved_28_63        : 36;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_kpux_err_ctl_s cn; */
};
typedef union bdk_npc_af_kpux_err_ctl bdk_npc_af_kpux_err_ctl_t;

static inline uint64_t BDK_NPC_AF_KPUX_ERR_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_KPUX_ERR_CTL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=15))
        return 0x8500630000a0ll + 0x100ll * ((a) & 0xf);
    __bdk_csr_fatal("NPC_AF_KPUX_ERR_CTL", 1, a, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_KPUX_ERR_CTL(a) bdk_npc_af_kpux_err_ctl_t
#define bustype_BDK_NPC_AF_KPUX_ERR_CTL(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_KPUX_ERR_CTL(a) "NPC_AF_KPUX_ERR_CTL"
#define device_bar_BDK_NPC_AF_KPUX_ERR_CTL(a) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_KPUX_ERR_CTL(a) (a)
#define arguments_BDK_NPC_AF_KPUX_ERR_CTL(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_lkup_ctl
 *
 * NPC AF Software Lookup Control Registers
 */
union bdk_npc_af_lkup_ctl
{
    uint64_t u;
    struct bdk_npc_af_lkup_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t exec                  : 1;  /**< [ 31: 31](R/W1S/H) Execute lookup. Writing a one to this bit initiates the lookup.
                                                                 Hardware writes the lookup result to NPC_AF_LKUP_RESULT() and clears this bit when done. */
        uint64_t op                    : 3;  /**< [ 30: 28](R/W) Lookup operation enumerated by NPC_LKUPOP_E. */
        uint64_t hdr_sizem1            : 8;  /**< [ 27: 20](R/W) Header size in bytes minus one when [OP] = NPC_LKUPOP_E::PKT and not used when
                                                                 [OP] = NPC_LKUPOP_E::KEY. */
        uint64_t chan                  : 12; /**< [ 19:  8](R/W) Packet's base channel number before CPI calculation if [OP] = NPC_LKUPOP_E::PKT.
                                                                 Must be zero if [OP] = NPC_LKUPOP_E::KEY. */
        uint64_t pkind                 : 6;  /**< [  7:  2](R/W) Packet's port kind valid if [OP] = NPC_LKUPOP_E::PKT. Must be zero if
                                                                 [OP] = NPC_LKUPOP_E::KEY. */
        uint64_t intf                  : 2;  /**< [  1:  0](R/W) NPC interface enumerated by NPC_INTF_E. */
#else /* Word 0 - Little Endian */
        uint64_t intf                  : 2;  /**< [  1:  0](R/W) NPC interface enumerated by NPC_INTF_E. */
        uint64_t pkind                 : 6;  /**< [  7:  2](R/W) Packet's port kind valid if [OP] = NPC_LKUPOP_E::PKT. Must be zero if
                                                                 [OP] = NPC_LKUPOP_E::KEY. */
        uint64_t chan                  : 12; /**< [ 19:  8](R/W) Packet's base channel number before CPI calculation if [OP] = NPC_LKUPOP_E::PKT.
                                                                 Must be zero if [OP] = NPC_LKUPOP_E::KEY. */
        uint64_t hdr_sizem1            : 8;  /**< [ 27: 20](R/W) Header size in bytes minus one when [OP] = NPC_LKUPOP_E::PKT and not used when
                                                                 [OP] = NPC_LKUPOP_E::KEY. */
        uint64_t op                    : 3;  /**< [ 30: 28](R/W) Lookup operation enumerated by NPC_LKUPOP_E. */
        uint64_t exec                  : 1;  /**< [ 31: 31](R/W1S/H) Execute lookup. Writing a one to this bit initiates the lookup.
                                                                 Hardware writes the lookup result to NPC_AF_LKUP_RESULT() and clears this bit when done. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_lkup_ctl_s cn; */
};
typedef union bdk_npc_af_lkup_ctl bdk_npc_af_lkup_ctl_t;

#define BDK_NPC_AF_LKUP_CTL BDK_NPC_AF_LKUP_CTL_FUNC()
static inline uint64_t BDK_NPC_AF_LKUP_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_LKUP_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x850062000000ll;
    __bdk_csr_fatal("NPC_AF_LKUP_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_LKUP_CTL bdk_npc_af_lkup_ctl_t
#define bustype_BDK_NPC_AF_LKUP_CTL BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_LKUP_CTL "NPC_AF_LKUP_CTL"
#define device_bar_BDK_NPC_AF_LKUP_CTL 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_LKUP_CTL 0
#define arguments_BDK_NPC_AF_LKUP_CTL -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_lkup_data#
 *
 * NPC AF Software Lookup Data Registers
 */
union bdk_npc_af_lkup_datax
{
    uint64_t u;
    struct bdk_npc_af_lkup_datax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Packet header or MCAM search key data for software lookup. See NPC_AF_LKUP_CTL[OP]. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Packet header or MCAM search key data for software lookup. See NPC_AF_LKUP_CTL[OP]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_lkup_datax_s cn; */
};
typedef union bdk_npc_af_lkup_datax bdk_npc_af_lkup_datax_t;

static inline uint64_t BDK_NPC_AF_LKUP_DATAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_LKUP_DATAX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=31))
        return 0x850062000200ll + 0x10ll * ((a) & 0x1f);
    __bdk_csr_fatal("NPC_AF_LKUP_DATAX", 1, a, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_LKUP_DATAX(a) bdk_npc_af_lkup_datax_t
#define bustype_BDK_NPC_AF_LKUP_DATAX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_LKUP_DATAX(a) "NPC_AF_LKUP_DATAX"
#define device_bar_BDK_NPC_AF_LKUP_DATAX(a) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_LKUP_DATAX(a) (a)
#define arguments_BDK_NPC_AF_LKUP_DATAX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_lkup_result#
 *
 * NPC AF Software Lookup Result Registers
 */
union bdk_npc_af_lkup_resultx
{
    uint64_t u;
    struct bdk_npc_af_lkup_resultx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](RO/H) Software lookup result data with format NPC_RESULT_S. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](RO/H) Software lookup result data with format NPC_RESULT_S. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_lkup_resultx_s cn; */
};
typedef union bdk_npc_af_lkup_resultx bdk_npc_af_lkup_resultx_t;

static inline uint64_t BDK_NPC_AF_LKUP_RESULTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_LKUP_RESULTX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=5))
        return 0x850062000400ll + 0x10ll * ((a) & 0x7);
    __bdk_csr_fatal("NPC_AF_LKUP_RESULTX", 1, a, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_LKUP_RESULTX(a) bdk_npc_af_lkup_resultx_t
#define bustype_BDK_NPC_AF_LKUP_RESULTX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_LKUP_RESULTX(a) "NPC_AF_LKUP_RESULTX"
#define device_bar_BDK_NPC_AF_LKUP_RESULTX(a) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_LKUP_RESULTX(a) (a)
#define arguments_BDK_NPC_AF_LKUP_RESULTX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_match_stat#
 *
 * NPC AF Match Statistics Registers
 */
union bdk_npc_af_match_statx
{
    uint64_t u;
    struct bdk_npc_af_match_statx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t count                 : 48; /**< [ 47:  0](R/W/H) Number of packets that hit MCAM entries whose
                                                                 NPC_AF_MCAME()_BANK()_STAT_ACT[STAT_SEL] select this register. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 48; /**< [ 47:  0](R/W/H) Number of packets that hit MCAM entries whose
                                                                 NPC_AF_MCAME()_BANK()_STAT_ACT[STAT_SEL] select this register. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_match_statx_s cn; */
};
typedef union bdk_npc_af_match_statx bdk_npc_af_match_statx_t;

static inline uint64_t BDK_NPC_AF_MATCH_STATX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_MATCH_STATX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=511))
        return 0x850061880008ll + 0x100ll * ((a) & 0x1ff);
    __bdk_csr_fatal("NPC_AF_MATCH_STATX", 1, a, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_MATCH_STATX(a) bdk_npc_af_match_statx_t
#define bustype_BDK_NPC_AF_MATCH_STATX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_MATCH_STATX(a) "NPC_AF_MATCH_STATX"
#define device_bar_BDK_NPC_AF_MATCH_STATX(a) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_MATCH_STATX(a) (a)
#define arguments_BDK_NPC_AF_MATCH_STATX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_mcam_bank#_hit#
 *
 * NPC AF MCAM Bank Hit Registers
 */
union bdk_npc_af_mcam_bankx_hitx
{
    uint64_t u;
    struct bdk_npc_af_mcam_bankx_hitx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hit                   : 64; /**< [ 63:  0](R/W1C/H) Entry hit.
                                                                 One bit per MCAM bank entry; NPC_AF_MCAM_BANK()_HIT(0)[HIT]\<63:0\> for entries 63-0,
                                                                 NPC_AF_MCAM_BANK()_HIT(1)[HIT]\<63:0\> for entries 127-64, etc. Hardware sets a bit
                                                                 when an MCAM lookup hits the corresponding bank entry, and clears a bit when
                                                                 software writes a one. If a lookup uses a wide (X2 or X4) search key, a hit only
                                                                 sets the bit for the first bank (bank 0 or 2 for the NPC_MCAM_KEY_X2_S search
                                                                 key format, bank 0 for the NPC_MCAM_KEY_X4_S format). */
#else /* Word 0 - Little Endian */
        uint64_t hit                   : 64; /**< [ 63:  0](R/W1C/H) Entry hit.
                                                                 One bit per MCAM bank entry; NPC_AF_MCAM_BANK()_HIT(0)[HIT]\<63:0\> for entries 63-0,
                                                                 NPC_AF_MCAM_BANK()_HIT(1)[HIT]\<63:0\> for entries 127-64, etc. Hardware sets a bit
                                                                 when an MCAM lookup hits the corresponding bank entry, and clears a bit when
                                                                 software writes a one. If a lookup uses a wide (X2 or X4) search key, a hit only
                                                                 sets the bit for the first bank (bank 0 or 2 for the NPC_MCAM_KEY_X2_S search
                                                                 key format, bank 0 for the NPC_MCAM_KEY_X4_S format). */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_mcam_bankx_hitx_s cn; */
};
typedef union bdk_npc_af_mcam_bankx_hitx bdk_npc_af_mcam_bankx_hitx_t;

static inline uint64_t BDK_NPC_AF_MCAM_BANKX_HITX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_MCAM_BANKX_HITX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=3) && (b<=15)))
        return 0x850061c80000ll + 0x100ll * ((a) & 0x3) + 0x10ll * ((b) & 0xf);
    __bdk_csr_fatal("NPC_AF_MCAM_BANKX_HITX", 2, a, b, 0, 0);
}

#define typedef_BDK_NPC_AF_MCAM_BANKX_HITX(a,b) bdk_npc_af_mcam_bankx_hitx_t
#define bustype_BDK_NPC_AF_MCAM_BANKX_HITX(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_MCAM_BANKX_HITX(a,b) "NPC_AF_MCAM_BANKX_HITX"
#define device_bar_BDK_NPC_AF_MCAM_BANKX_HITX(a,b) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_MCAM_BANKX_HITX(a,b) (a)
#define arguments_BDK_NPC_AF_MCAM_BANKX_HITX(a,b) (a),(b),-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_mcam_dbg
 *
 * NPC AF MCAM Debug Register
 * This register contains information for the last packet/lookup for which debug
 * is enabled by NPC_AF_DBG_CTL[INTF_DBG,LKUP_DBG].
 */
union bdk_npc_af_mcam_dbg
{
    uint64_t u;
    struct bdk_npc_af_mcam_dbg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t miss                  : 1;  /**< [ 16: 16](RO/H) MCAM miss. When set, [HIT_BANK] and [HIT_ENTRY] are not valid. */
        uint64_t reserved_14_15        : 2;
        uint64_t hit_bank              : 2;  /**< [ 13: 12](RO/H) MCAM hit bank index. */
        uint64_t reserved_10_11        : 2;
        uint64_t hit_entry             : 10; /**< [  9:  0](RO/H) MCAM hit entry index. */
#else /* Word 0 - Little Endian */
        uint64_t hit_entry             : 10; /**< [  9:  0](RO/H) MCAM hit entry index. */
        uint64_t reserved_10_11        : 2;
        uint64_t hit_bank              : 2;  /**< [ 13: 12](RO/H) MCAM hit bank index. */
        uint64_t reserved_14_15        : 2;
        uint64_t miss                  : 1;  /**< [ 16: 16](RO/H) MCAM miss. When set, [HIT_BANK] and [HIT_ENTRY] are not valid. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_mcam_dbg_s cn; */
};
typedef union bdk_npc_af_mcam_dbg bdk_npc_af_mcam_dbg_t;

#define BDK_NPC_AF_MCAM_DBG BDK_NPC_AF_MCAM_DBG_FUNC()
static inline uint64_t BDK_NPC_AF_MCAM_DBG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_MCAM_DBG_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x850063001000ll;
    __bdk_csr_fatal("NPC_AF_MCAM_DBG", 0, 0, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_MCAM_DBG bdk_npc_af_mcam_dbg_t
#define bustype_BDK_NPC_AF_MCAM_DBG BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_MCAM_DBG "NPC_AF_MCAM_DBG"
#define device_bar_BDK_NPC_AF_MCAM_DBG 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_MCAM_DBG 0
#define arguments_BDK_NPC_AF_MCAM_DBG -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_mcam_scrub_ctl
 *
 * NPC AF MCAM Scrub Control Register
 */
union bdk_npc_af_mcam_scrub_ctl
{
    uint64_t u;
    struct bdk_npc_af_mcam_scrub_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t toth                  : 4;  /**< [ 19: 16](R/W) CAM scrubber timeout threshold. The timeout timer increments by one each
                                                                 coprocessor-clock cycle, and a single scrub cycle is issued to all CAM's as soon
                                                                 as a timeout occurs when the timer reaches the threshold 2^([TOTH]).
                                                                 The maximum timeout threshold is 2^15 and minimum is every cycle. */
        uint64_t reserved_1_15         : 15;
        uint64_t ena                   : 1;  /**< [  0:  0](R/W) When set enables the CAM scrubber. */
#else /* Word 0 - Little Endian */
        uint64_t ena                   : 1;  /**< [  0:  0](R/W) When set enables the CAM scrubber. */
        uint64_t reserved_1_15         : 15;
        uint64_t toth                  : 4;  /**< [ 19: 16](R/W) CAM scrubber timeout threshold. The timeout timer increments by one each
                                                                 coprocessor-clock cycle, and a single scrub cycle is issued to all CAM's as soon
                                                                 as a timeout occurs when the timer reaches the threshold 2^([TOTH]).
                                                                 The maximum timeout threshold is 2^15 and minimum is every cycle. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_mcam_scrub_ctl_s cn; */
};
typedef union bdk_npc_af_mcam_scrub_ctl bdk_npc_af_mcam_scrub_ctl_t;

#define BDK_NPC_AF_MCAM_SCRUB_CTL BDK_NPC_AF_MCAM_SCRUB_CTL_FUNC()
static inline uint64_t BDK_NPC_AF_MCAM_SCRUB_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_MCAM_SCRUB_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x8500600000a0ll;
    __bdk_csr_fatal("NPC_AF_MCAM_SCRUB_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_MCAM_SCRUB_CTL bdk_npc_af_mcam_scrub_ctl_t
#define bustype_BDK_NPC_AF_MCAM_SCRUB_CTL BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_MCAM_SCRUB_CTL "NPC_AF_MCAM_SCRUB_CTL"
#define device_bar_BDK_NPC_AF_MCAM_SCRUB_CTL 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_MCAM_SCRUB_CTL 0
#define arguments_BDK_NPC_AF_MCAM_SCRUB_CTL -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_mcame#_bank#_action
 *
 * NPC AF MCAM Entry Bank Action Data Registers
 * Specifies a packet's match action captured in NPC_RESULT_S[ACTION].
 *
 * When an interface is configured to use the NPC_MCAM_KEY_X2_S search key
 * format (NPC_AF_INTF()_KEX_CFG[KEYW] = NPC_MCAMKEYW_E::X2),
 * * NPC_AF_MCAME()_BANK(0)_ACTION/_TAG_ACT/_STAT_ACT are used if the search key
 * matches NPC_AF_MCAME()_BANK(0..1)_CAM()_W*.
 * * NPC_AF_MCAME()_BANK(2)_ACTION/_TAG_ACT/_STAT_ACT are used if the search key
 * matches NPC_AF_MCAME()_BANK(2..3)_CAM()_W*.
 * * NPC_AF_MCAME()_BANK(1,3)_ACTION/_TAG_ACT/_STAT_ACT are not used.
 *
 * When an interface is configured to use the NPC_MCAM_KEY_X4_S search key
 * format (NPC_AF_INTF()_KEX_CFG[KEYW] = NPC_MCAMKEYW_E::X4):
 * * NPC_AF_MCAME()_BANK(0)_ACTION/_TAG_ACT/_STAT_ACT are used if the search key
 * matches NPC_AF_MCAME()_BANK(0..3)_CAM()_W*.
 * * NPC_AF_MCAME()_BANK(1..3)_ACTION/_TAG_ACT/_STAT_ACT are not used.
 */
union bdk_npc_af_mcamex_bankx_action
{
    uint64_t u;
    struct bdk_npc_af_mcamex_bankx_action_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t action                : 64; /**< [ 63:  0](R/W) Match action. Format is NIX_RX_ACTION_S for RX packet, NIX_TX_ACTION_S for
                                                                 TX packet. */
#else /* Word 0 - Little Endian */
        uint64_t action                : 64; /**< [ 63:  0](R/W) Match action. Format is NIX_RX_ACTION_S for RX packet, NIX_TX_ACTION_S for
                                                                 TX packet. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_mcamex_bankx_action_s cn; */
};
typedef union bdk_npc_af_mcamex_bankx_action bdk_npc_af_mcamex_bankx_action_t;

static inline uint64_t BDK_NPC_AF_MCAMEX_BANKX_ACTION(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_MCAMEX_BANKX_ACTION(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1023) && (b<=3)))
        return 0x850061900000ll + 0x100ll * ((a) & 0x3ff) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("NPC_AF_MCAMEX_BANKX_ACTION", 2, a, b, 0, 0);
}

#define typedef_BDK_NPC_AF_MCAMEX_BANKX_ACTION(a,b) bdk_npc_af_mcamex_bankx_action_t
#define bustype_BDK_NPC_AF_MCAMEX_BANKX_ACTION(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_MCAMEX_BANKX_ACTION(a,b) "NPC_AF_MCAMEX_BANKX_ACTION"
#define device_bar_BDK_NPC_AF_MCAMEX_BANKX_ACTION(a,b) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_MCAMEX_BANKX_ACTION(a,b) (a)
#define arguments_BDK_NPC_AF_MCAMEX_BANKX_ACTION(a,b) (a),(b),-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_mcame#_bank#_cam#_intf
 *
 * NPC AF MCAM Entry Bank CAM Data Interface Registers
 * MCAM comparison ternary data interface word. The field values in
 * NPC_AF_MCAME()_BANK()_CAM()_INTF, NPC_AF_MCAME()_BANK()_CAM()_W0 and
 * NPC_AF_MCAME()_BANK()_CAM()_W1 are ternary, where  each data bit of the
 * search key matches as follows:
 * _ [CAM(1)]\<n\>=0, [CAM(0)]\<n\>=0: Always match; search key data\<n\> don't care.
 * _ [CAM(1)]\<n\>=0, [CAM(0)]\<n\>=1: Match when search key data\<n\> == 0.
 * _ [CAM(1)]\<n\>=1, [CAM(0)]\<n\>=0: Match when search key data\<n\> == 1.
 * _ [CAM(1)]\<n\>=1, [CAM(0)]\<n\>=1: Reserved.
 *
 * The reserved combination is not allowed. Hardware suppresses any write to
 * CAM(0) or CAM(1) that would result in the reserved combination for any CAM bit.
 *
 * When an interface is configured to use the NPC_MCAM_KEY_X1_S search key
 * format (NPC_AF_INTF()_KEX_CFG[KEYW] = NPC_MCAMKEYW_E::X1), the four banks
 * of every MCAM entry are used as individual entries, each of which is
 * independently compared with the search key as follows:
 * _ NPC_AF_MCAME()_BANK()_CAM()_INTF[INTF] corresponds to NPC_MCAM_KEY_X1_S[INTF].
 * _ NPC_AF_MCAME()_BANK()_CAM()_W0[MD] corresponds to NPC_MCAM_KEY_X1_S[KW0].
 * _ NPC_AF_MCAME()_BANK()_CAM()_W1[MD] corresponds to NPC_MCAM_KEY_X1_S[KW1].
 *
 * When an interface is configured to use the NPC_MCAM_KEY_X2_S search key
 * format (NPC_AF_INTF()_KEX_CFG[KEYW] = NPC_MCAMKEYW_E::X2), banks 0-1 of
 * every MCAM entry are used as one double-wide entry, banks 2-3 as a second
 * double-wide entry, and each double-wide entry is independently compared
 * with the search key as follows:
 * _ NPC_AF_MCAME()_BANK(0,2)_CAM()_INTF[INTF] corresponds to NPC_MCAM_KEY_X2_S[INTF].
 * _ NPC_AF_MCAME()_BANK(0,2)_CAM()_W0[MD] corresponds to NPC_MCAM_KEY_X2_S[KW0].
 * _ NPC_AF_MCAME()_BANK(0,2)_CAM()_W1[MD] corresponds to NPC_MCAM_KEY_X2_S[KW1\<47:0\>].
 * _ NPC_AF_MCAME()_BANK(1,3)_CAM()_INTF[INTF] corresponds to NPC_MCAM_KEY_X2_S[INTF].
 * _ NPC_AF_MCAME()_BANK(1,3)_CAM()_W0[MD\<15:0\>] corresponds to NPC_MCAM_KEY_X2_S[KW1\<63:48\>].
 * _ NPC_AF_MCAME()_BANK(1,3)_CAM()_W0[MD\<63:16\>] corresponds to NPC_MCAM_KEY_X2_S[KW2\<47:0\>].
 * _ NPC_AF_MCAME()_BANK(1,3)_CAM()_W1[MD\<15:0\>] corresponds to NPC_MCAM_KEY_X2_S[KW2\<63:48\>].
 * _ NPC_AF_MCAME()_BANK(1,3)_CAM()_W1[MD\<47:16\>] corresponds to NPC_MCAM_KEY_X2_S[KW3\<31:0\>].
 *
 * When an interface is configured to use the NPC_MCAM_KEY_X4_S search key
 * format (NPC_AF_INTF()_KEX_CFG[KEYW] = NPC_MCAMKEYW_E::X4), the four banks of every MCAM entry
 * are used as a single quad-wide entry that is compared with the search key as follows:
 * _ NPC_AF_MCAME()_BANK(0)_CAM()_INTF[INTF] corresponds to NPC_MCAM_KEY_X4_S[INTF].
 * _ NPC_AF_MCAME()_BANK(0)_CAM()_W0[MD] corresponds to NPC_MCAM_KEY_X4_S[KW0].
 * _ NPC_AF_MCAME()_BANK(0)_CAM()_W1[MD] corresponds to NPC_MCAM_KEY_X4_S[KW1\<47:0\>].
 * _ NPC_AF_MCAME()_BANK(1)_CAM()_INTF[INTF] corresponds to NPC_MCAM_KEY_X4_S[INTF].
 * _ NPC_AF_MCAME()_BANK(1)_CAM()_W0[MD\<15:0\>] corresponds to NPC_MCAM_KEY_X4_S[KW1\<63:48\>].
 * _ NPC_AF_MCAME()_BANK(1)_CAM()_W0[MD\<63:16\>] corresponds to NPC_MCAM_KEY_X4_S[KW2\<47:0\>].
 * _ NPC_AF_MCAME()_BANK(1)_CAM()_W1[MD\<15:0\>] corresponds to NPC_MCAM_KEY_X4_S[KW2\<63:48\>].
 * _ NPC_AF_MCAME()_BANK(1)_CAM()_W1[MD\<47:16\>] corresponds to NPC_MCAM_KEY_X4_S[KW3\<31:0\>].
 * _ NPC_AF_MCAME()_BANK(2)_CAM()_INTF[INTF] corresponds to NPC_MCAM_KEY_X4_S[INTF].
 * _ NPC_AF_MCAME()_BANK(2)_CAM()_W0[MD\<31:0\>] corresponds to NPC_MCAM_KEY_X4_S[KW3\<63:32\>].
 * _ NPC_AF_MCAME()_BANK(2)_CAM()_W0[MD\<63:32\>] corresponds to NPC_MCAM_KEY_X4_S[KW4\<31:0\>].
 * _ NPC_AF_MCAME()_BANK(2)_CAM()_W1[MD\<31:0\>] corresponds to NPC_MCAM_KEY_X4_S[KW4\<63:32\>].
 * _ NPC_AF_MCAME()_BANK(2)_CAM()_W1[MD\<47:32\>] corresponds to NPC_MCAM_KEY_X4_S[KW5\<15:0\>].
 * _ NPC_AF_MCAME()_BANK(3)_CAM()_INTF[INTF] corresponds to NPC_MCAM_KEY_X4_S[INTF].
 * _ NPC_AF_MCAME()_BANK(3)_CAM()_W0[MD\<47:0\>] corresponds to NPC_MCAM_KEY_X4_S[KW5\<63:16\>].
 * _ NPC_AF_MCAME()_BANK(3)_CAM()_W0[MD\<63:48\>] corresponds to NPC_MCAM_KEY_X4_S[KW6\<15:0\>].
 * _ NPC_AF_MCAME()_BANK(3)_CAM()_W1[MD] corresponds to NPC_MCAM_KEY_X4_S[KW6\<63:16\>]
 *
 * Note that for the X2 and X4 formats, a wide entry will not match unless
 * the INTF fields from the associated two or four banks match the INTF
 * value from the search key.
 *
 * For the X1 and X2 formats, a match in a lower numbered bank takes priority over
 * a match in any higher numbered banks. Within each bank, the lowest numbered
 * matching entry takes priority over any higher numbered entry.
 */
union bdk_npc_af_mcamex_bankx_camx_intf
{
    uint64_t u;
    struct bdk_npc_af_mcamex_bankx_camx_intf_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t intf                  : 2;  /**< [  1:  0](R/W) NPC interface. Enumerated by NPC_INTF_E. */
#else /* Word 0 - Little Endian */
        uint64_t intf                  : 2;  /**< [  1:  0](R/W) NPC interface. Enumerated by NPC_INTF_E. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_mcamex_bankx_camx_intf_s cn; */
};
typedef union bdk_npc_af_mcamex_bankx_camx_intf bdk_npc_af_mcamex_bankx_camx_intf_t;

static inline uint64_t BDK_NPC_AF_MCAMEX_BANKX_CAMX_INTF(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_MCAMEX_BANKX_CAMX_INTF(unsigned long a, unsigned long b, unsigned long c)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1023) && (b<=3) && (c<=1)))
        return 0x850061000000ll + 0x400ll * ((a) & 0x3ff) + 0x40ll * ((b) & 0x3) + 8ll * ((c) & 0x1);
    __bdk_csr_fatal("NPC_AF_MCAMEX_BANKX_CAMX_INTF", 3, a, b, c, 0);
}

#define typedef_BDK_NPC_AF_MCAMEX_BANKX_CAMX_INTF(a,b,c) bdk_npc_af_mcamex_bankx_camx_intf_t
#define bustype_BDK_NPC_AF_MCAMEX_BANKX_CAMX_INTF(a,b,c) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_MCAMEX_BANKX_CAMX_INTF(a,b,c) "NPC_AF_MCAMEX_BANKX_CAMX_INTF"
#define device_bar_BDK_NPC_AF_MCAMEX_BANKX_CAMX_INTF(a,b,c) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_MCAMEX_BANKX_CAMX_INTF(a,b,c) (a)
#define arguments_BDK_NPC_AF_MCAMEX_BANKX_CAMX_INTF(a,b,c) (a),(b),(c),-1

/**
 * Register (RVU_PF_BAR0) npc_af_mcame#_bank#_cam#_w0
 *
 * NPC AF MCAM Entry Bank CAM Data Word 0 Registers
 * MCAM comparison ternary data word 0. See NPC_AF_MCAME()_BANK()_CAM()_INTF.
 */
union bdk_npc_af_mcamex_bankx_camx_w0
{
    uint64_t u;
    struct bdk_npc_af_mcamex_bankx_camx_w0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t md                    : 64; /**< [ 63:  0](R/W) Match data. */
#else /* Word 0 - Little Endian */
        uint64_t md                    : 64; /**< [ 63:  0](R/W) Match data. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_mcamex_bankx_camx_w0_s cn; */
};
typedef union bdk_npc_af_mcamex_bankx_camx_w0 bdk_npc_af_mcamex_bankx_camx_w0_t;

static inline uint64_t BDK_NPC_AF_MCAMEX_BANKX_CAMX_W0(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_MCAMEX_BANKX_CAMX_W0(unsigned long a, unsigned long b, unsigned long c)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1023) && (b<=3) && (c<=1)))
        return 0x850061000010ll + 0x400ll * ((a) & 0x3ff) + 0x40ll * ((b) & 0x3) + 8ll * ((c) & 0x1);
    __bdk_csr_fatal("NPC_AF_MCAMEX_BANKX_CAMX_W0", 3, a, b, c, 0);
}

#define typedef_BDK_NPC_AF_MCAMEX_BANKX_CAMX_W0(a,b,c) bdk_npc_af_mcamex_bankx_camx_w0_t
#define bustype_BDK_NPC_AF_MCAMEX_BANKX_CAMX_W0(a,b,c) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_MCAMEX_BANKX_CAMX_W0(a,b,c) "NPC_AF_MCAMEX_BANKX_CAMX_W0"
#define device_bar_BDK_NPC_AF_MCAMEX_BANKX_CAMX_W0(a,b,c) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_MCAMEX_BANKX_CAMX_W0(a,b,c) (a)
#define arguments_BDK_NPC_AF_MCAMEX_BANKX_CAMX_W0(a,b,c) (a),(b),(c),-1

/**
 * Register (RVU_PF_BAR0) npc_af_mcame#_bank#_cam#_w1
 *
 * NPC AF MCAM Entry Bank Data Word 1 Registers
 * MCAM comparison ternary data word 1. See NPC_AF_MCAME()_BANK()_CAM()_INTF.
 */
union bdk_npc_af_mcamex_bankx_camx_w1
{
    uint64_t u;
    struct bdk_npc_af_mcamex_bankx_camx_w1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t md                    : 48; /**< [ 47:  0](R/W) Match data. */
#else /* Word 0 - Little Endian */
        uint64_t md                    : 48; /**< [ 47:  0](R/W) Match data. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_mcamex_bankx_camx_w1_s cn; */
};
typedef union bdk_npc_af_mcamex_bankx_camx_w1 bdk_npc_af_mcamex_bankx_camx_w1_t;

static inline uint64_t BDK_NPC_AF_MCAMEX_BANKX_CAMX_W1(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_MCAMEX_BANKX_CAMX_W1(unsigned long a, unsigned long b, unsigned long c)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1023) && (b<=3) && (c<=1)))
        return 0x850061000020ll + 0x400ll * ((a) & 0x3ff) + 0x40ll * ((b) & 0x3) + 8ll * ((c) & 0x1);
    __bdk_csr_fatal("NPC_AF_MCAMEX_BANKX_CAMX_W1", 3, a, b, c, 0);
}

#define typedef_BDK_NPC_AF_MCAMEX_BANKX_CAMX_W1(a,b,c) bdk_npc_af_mcamex_bankx_camx_w1_t
#define bustype_BDK_NPC_AF_MCAMEX_BANKX_CAMX_W1(a,b,c) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_MCAMEX_BANKX_CAMX_W1(a,b,c) "NPC_AF_MCAMEX_BANKX_CAMX_W1"
#define device_bar_BDK_NPC_AF_MCAMEX_BANKX_CAMX_W1(a,b,c) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_MCAMEX_BANKX_CAMX_W1(a,b,c) (a)
#define arguments_BDK_NPC_AF_MCAMEX_BANKX_CAMX_W1(a,b,c) (a),(b),(c),-1

/**
 * Register (RVU_PF_BAR0) npc_af_mcame#_bank#_cfg
 *
 * NPC AF MCAM Entry Bank Configuration Registers
 */
union bdk_npc_af_mcamex_bankx_cfg
{
    uint64_t u;
    struct bdk_npc_af_mcamex_bankx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t ena                   : 1;  /**< [  0:  0](R/W) Enable entry. When clear, the entry is disabled and may be safely modified
                                                                 by software. */
#else /* Word 0 - Little Endian */
        uint64_t ena                   : 1;  /**< [  0:  0](R/W) Enable entry. When clear, the entry is disabled and may be safely modified
                                                                 by software. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_mcamex_bankx_cfg_s cn; */
};
typedef union bdk_npc_af_mcamex_bankx_cfg bdk_npc_af_mcamex_bankx_cfg_t;

static inline uint64_t BDK_NPC_AF_MCAMEX_BANKX_CFG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_MCAMEX_BANKX_CFG(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1023) && (b<=3)))
        return 0x850061800000ll + 0x100ll * ((a) & 0x3ff) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("NPC_AF_MCAMEX_BANKX_CFG", 2, a, b, 0, 0);
}

#define typedef_BDK_NPC_AF_MCAMEX_BANKX_CFG(a,b) bdk_npc_af_mcamex_bankx_cfg_t
#define bustype_BDK_NPC_AF_MCAMEX_BANKX_CFG(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_MCAMEX_BANKX_CFG(a,b) "NPC_AF_MCAMEX_BANKX_CFG"
#define device_bar_BDK_NPC_AF_MCAMEX_BANKX_CFG(a,b) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_MCAMEX_BANKX_CFG(a,b) (a)
#define arguments_BDK_NPC_AF_MCAMEX_BANKX_CFG(a,b) (a),(b),-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_mcame#_bank#_stat_act
 *
 * NPC AF MCAM Entry Bank Statistics Action Registers
 * Used to optionally increment a NPC_AF_MATCH_STAT() counter when a packet
 * matches an MCAM entry. See also NPC_AF_MCAME()_BANK()_ACTION.
 */
union bdk_npc_af_mcamex_bankx_stat_act
{
    uint64_t u;
    struct bdk_npc_af_mcamex_bankx_stat_act_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t ena                   : 1;  /**< [  9:  9](R/W)  */
        uint64_t stat_sel              : 9;  /**< [  8:  0](R/W) Match statistics select. Valid when [ENA] is set. Index of NPC_AF_MATCH_STAT() to
                                                                 increment on a match to this MCAM entry. */
#else /* Word 0 - Little Endian */
        uint64_t stat_sel              : 9;  /**< [  8:  0](R/W) Match statistics select. Valid when [ENA] is set. Index of NPC_AF_MATCH_STAT() to
                                                                 increment on a match to this MCAM entry. */
        uint64_t ena                   : 1;  /**< [  9:  9](R/W)  */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_mcamex_bankx_stat_act_s cn; */
};
typedef union bdk_npc_af_mcamex_bankx_stat_act bdk_npc_af_mcamex_bankx_stat_act_t;

static inline uint64_t BDK_NPC_AF_MCAMEX_BANKX_STAT_ACT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_MCAMEX_BANKX_STAT_ACT(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1023) && (b<=3)))
        return 0x850061880000ll + 0x100ll * ((a) & 0x3ff) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("NPC_AF_MCAMEX_BANKX_STAT_ACT", 2, a, b, 0, 0);
}

#define typedef_BDK_NPC_AF_MCAMEX_BANKX_STAT_ACT(a,b) bdk_npc_af_mcamex_bankx_stat_act_t
#define bustype_BDK_NPC_AF_MCAMEX_BANKX_STAT_ACT(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_MCAMEX_BANKX_STAT_ACT(a,b) "NPC_AF_MCAMEX_BANKX_STAT_ACT"
#define device_bar_BDK_NPC_AF_MCAMEX_BANKX_STAT_ACT(a,b) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_MCAMEX_BANKX_STAT_ACT(a,b) (a)
#define arguments_BDK_NPC_AF_MCAMEX_BANKX_STAT_ACT(a,b) (a),(b),-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_mcame#_bank#_tag_act
 *
 * NPC AF MCAM Entry Bank VTag Action Data Registers
 * Specifies a packet's match Vtag action captured in NPC_RESULT_S[VTAG_ACTION].
 * See also NPC_AF_MCAME()_BANK()_ACTION.
 */
union bdk_npc_af_mcamex_bankx_tag_act
{
    uint64_t u;
    struct bdk_npc_af_mcamex_bankx_tag_act_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t vtag_action           : 64; /**< [ 63:  0](R/W) Match Vtag action. Format is NIX_RX_VTAG_ACTION_S for RX packet,
                                                                 NIX_TX_VTAG_ACTION_S for TX packet. */
#else /* Word 0 - Little Endian */
        uint64_t vtag_action           : 64; /**< [ 63:  0](R/W) Match Vtag action. Format is NIX_RX_VTAG_ACTION_S for RX packet,
                                                                 NIX_TX_VTAG_ACTION_S for TX packet. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_mcamex_bankx_tag_act_s cn; */
};
typedef union bdk_npc_af_mcamex_bankx_tag_act bdk_npc_af_mcamex_bankx_tag_act_t;

static inline uint64_t BDK_NPC_AF_MCAMEX_BANKX_TAG_ACT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_MCAMEX_BANKX_TAG_ACT(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1023) && (b<=3)))
        return 0x850061900008ll + 0x100ll * ((a) & 0x3ff) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("NPC_AF_MCAMEX_BANKX_TAG_ACT", 2, a, b, 0, 0);
}

#define typedef_BDK_NPC_AF_MCAMEX_BANKX_TAG_ACT(a,b) bdk_npc_af_mcamex_bankx_tag_act_t
#define bustype_BDK_NPC_AF_MCAMEX_BANKX_TAG_ACT(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_MCAMEX_BANKX_TAG_ACT(a,b) "NPC_AF_MCAMEX_BANKX_TAG_ACT"
#define device_bar_BDK_NPC_AF_MCAMEX_BANKX_TAG_ACT(a,b) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_MCAMEX_BANKX_TAG_ACT(a,b) (a)
#define arguments_BDK_NPC_AF_MCAMEX_BANKX_TAG_ACT(a,b) (a),(b),-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_pck_cfg
 *
 * NPC AF Protocol Check Configuration Register
 */
union bdk_npc_af_pck_cfg
{
    uint64_t u;
    struct bdk_npc_af_pck_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t oip4_cksum_errcode    : 8;  /**< [ 39: 32](R/W) Outer IPv4 checksum error code. See [OIP4_CKSUM]. */
        uint64_t iip4_cksum_errcode    : 8;  /**< [ 31: 24](R/W) Inner IPv4 checksum error code. See [IIP4_CKSUM]. */
        uint64_t reserved_8_23         : 16;
        uint64_t l2m                   : 1;  /**< [  7:  7](R/W) Enable setting of NPC_RESULT_S[L2M] when an outer L2 multicast address is
                                                                 detected. Software must program NPC_AF_PCK_DEF_OL2 to identify the outer L2 header
                                                                 before setting this bit. */
        uint64_t l2b                   : 1;  /**< [  6:  6](R/W) Enable setting of NPC_RESULT_S[L2B] when an outer L2 broadcast address is
                                                                 detected. Software must program NPC_AF_PCK_DEF_OL2 to identify the outer L2 header
                                                                 before setting this bit. */
        uint64_t l3m                   : 1;  /**< [  5:  5](R/W) Enable setting of NPC_RESULT_S[L3M] when an outer IP multicast address is
                                                                 detected. Software must program NPC_AF_PCK_DEF_OIP4 and NPC_AF_PCK_DEF_OIP6 to
                                                                 identify the outer IP header before setting this bit. */
        uint64_t l3b                   : 1;  /**< [  4:  4](R/W) Enable setting of NPC_RESULT_S[L3B] when an outer IP broadcast address is
                                                                 detected. Software must program NPC_AF_PCK_DEF_OIP4 and NPC_AF_PCK_DEF_OIP6 to
                                                                 identify the outer IP header before setting this bit. */
        uint64_t reserved_3            : 1;
        uint64_t oip4_cksum            : 1;  /**< [  2:  2](R/W) Enable outer IPv4 checksum validation.
                                                                 Software must program NPC_AF_PCK_DEF_OIP4 to identify the outer IPv4 header
                                                                 before setting this bit.

                                                                 If set and an outer IPv4 checksum error is detected:
                                                                 * If NPC_RESULT_S[ERRCODE]=0 or (NPC_RESULT_S[ERRLEV] \> (NPC_AF_PCK_DEF_OIP4[LID]+1)),
                                                                 hardware sets NPC_RESULT_S[ERRLEV] = NPC_AF_PCK_DEF_OIP4[LID]+1 and
                                                                 NPC_RESULT_S[ERRCODE] = [OIP4_CKSUM_ERRCODE].
                                                                 * Otherwise, the error is ignored. */
        uint64_t iip4_cksum            : 1;  /**< [  1:  1](R/W) Enable inner IPv4 checksum validation.
                                                                 Software must program NPC_AF_PCK_DEF_IIP4 to identify the inner IPv4 header before
                                                                 setting this bit.

                                                                 If set and an inner IPv4 checksum error is detected:
                                                                 * If NPC_RESULT_S[ERRCODE]=0 or ((NPC_RESULT_S[ERRLEV] \> NPC_AF_PCK_DEF_IIP4[LID]+1)),
                                                                 hardware sets NPC_RESULT_S[ERRLEV] = NPC_AF_PCK_DEF_IIP4[LID]+1 and
                                                                 NPC_RESULT_S[ERRCODE] = [IIP4_CKSUM_ERRCODE].
                                                                 * Otherwise, the error is ignored. */
        uint64_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0            : 1;
        uint64_t iip4_cksum            : 1;  /**< [  1:  1](R/W) Enable inner IPv4 checksum validation.
                                                                 Software must program NPC_AF_PCK_DEF_IIP4 to identify the inner IPv4 header before
                                                                 setting this bit.

                                                                 If set and an inner IPv4 checksum error is detected:
                                                                 * If NPC_RESULT_S[ERRCODE]=0 or ((NPC_RESULT_S[ERRLEV] \> NPC_AF_PCK_DEF_IIP4[LID]+1)),
                                                                 hardware sets NPC_RESULT_S[ERRLEV] = NPC_AF_PCK_DEF_IIP4[LID]+1 and
                                                                 NPC_RESULT_S[ERRCODE] = [IIP4_CKSUM_ERRCODE].
                                                                 * Otherwise, the error is ignored. */
        uint64_t oip4_cksum            : 1;  /**< [  2:  2](R/W) Enable outer IPv4 checksum validation.
                                                                 Software must program NPC_AF_PCK_DEF_OIP4 to identify the outer IPv4 header
                                                                 before setting this bit.

                                                                 If set and an outer IPv4 checksum error is detected:
                                                                 * If NPC_RESULT_S[ERRCODE]=0 or (NPC_RESULT_S[ERRLEV] \> (NPC_AF_PCK_DEF_OIP4[LID]+1)),
                                                                 hardware sets NPC_RESULT_S[ERRLEV] = NPC_AF_PCK_DEF_OIP4[LID]+1 and
                                                                 NPC_RESULT_S[ERRCODE] = [OIP4_CKSUM_ERRCODE].
                                                                 * Otherwise, the error is ignored. */
        uint64_t reserved_3            : 1;
        uint64_t l3b                   : 1;  /**< [  4:  4](R/W) Enable setting of NPC_RESULT_S[L3B] when an outer IP broadcast address is
                                                                 detected. Software must program NPC_AF_PCK_DEF_OIP4 and NPC_AF_PCK_DEF_OIP6 to
                                                                 identify the outer IP header before setting this bit. */
        uint64_t l3m                   : 1;  /**< [  5:  5](R/W) Enable setting of NPC_RESULT_S[L3M] when an outer IP multicast address is
                                                                 detected. Software must program NPC_AF_PCK_DEF_OIP4 and NPC_AF_PCK_DEF_OIP6 to
                                                                 identify the outer IP header before setting this bit. */
        uint64_t l2b                   : 1;  /**< [  6:  6](R/W) Enable setting of NPC_RESULT_S[L2B] when an outer L2 broadcast address is
                                                                 detected. Software must program NPC_AF_PCK_DEF_OL2 to identify the outer L2 header
                                                                 before setting this bit. */
        uint64_t l2m                   : 1;  /**< [  7:  7](R/W) Enable setting of NPC_RESULT_S[L2M] when an outer L2 multicast address is
                                                                 detected. Software must program NPC_AF_PCK_DEF_OL2 to identify the outer L2 header
                                                                 before setting this bit. */
        uint64_t reserved_8_23         : 16;
        uint64_t iip4_cksum_errcode    : 8;  /**< [ 31: 24](R/W) Inner IPv4 checksum error code. See [IIP4_CKSUM]. */
        uint64_t oip4_cksum_errcode    : 8;  /**< [ 39: 32](R/W) Outer IPv4 checksum error code. See [OIP4_CKSUM]. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_pck_cfg_s cn; */
};
typedef union bdk_npc_af_pck_cfg bdk_npc_af_pck_cfg_t;

#define BDK_NPC_AF_PCK_CFG BDK_NPC_AF_PCK_CFG_FUNC()
static inline uint64_t BDK_NPC_AF_PCK_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_PCK_CFG_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x850060000600ll;
    __bdk_csr_fatal("NPC_AF_PCK_CFG", 0, 0, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_PCK_CFG bdk_npc_af_pck_cfg_t
#define bustype_BDK_NPC_AF_PCK_CFG BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_PCK_CFG "NPC_AF_PCK_CFG"
#define device_bar_BDK_NPC_AF_PCK_CFG 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_PCK_CFG 0
#define arguments_BDK_NPC_AF_PCK_CFG -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_pck_def_iip4
 *
 * NPC AF Protocol Check Outer IPv4 Definition Register
 * Provides layer information used by the protocol checker to identify an inner IPv4 header.
 */
union bdk_npc_af_pck_def_iip4
{
    uint64_t u;
    struct bdk_npc_af_pck_def_iip4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t lid                   : 3;  /**< [ 10:  8](R/W) Layer ID. Enumerated by NPC_LID_E. */
        uint64_t ltype_match           : 4;  /**< [  7:  4](R/W) Layer type match value. Hardware detects a layer match when
                                                                 \<pre\>
                                                                 ([LTYPE_MATCH] & [LTYPE_MASK]) == (NPC_RESULT_S[LX[LTYPE]] & [LTYPE_MASK])
                                                                 \</pre\>

                                                                 where LX is one of LA, LB, ..., LH as selected by [LID]. */
        uint64_t ltype_mask            : 4;  /**< [  3:  0](R/W) Layer type mask. See [LTYPE_MATCH]. */
#else /* Word 0 - Little Endian */
        uint64_t ltype_mask            : 4;  /**< [  3:  0](R/W) Layer type mask. See [LTYPE_MATCH]. */
        uint64_t ltype_match           : 4;  /**< [  7:  4](R/W) Layer type match value. Hardware detects a layer match when
                                                                 \<pre\>
                                                                 ([LTYPE_MATCH] & [LTYPE_MASK]) == (NPC_RESULT_S[LX[LTYPE]] & [LTYPE_MASK])
                                                                 \</pre\>

                                                                 where LX is one of LA, LB, ..., LH as selected by [LID]. */
        uint64_t lid                   : 3;  /**< [ 10:  8](R/W) Layer ID. Enumerated by NPC_LID_E. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_pck_def_iip4_s cn; */
};
typedef union bdk_npc_af_pck_def_iip4 bdk_npc_af_pck_def_iip4_t;

#define BDK_NPC_AF_PCK_DEF_IIP4 BDK_NPC_AF_PCK_DEF_IIP4_FUNC()
static inline uint64_t BDK_NPC_AF_PCK_DEF_IIP4_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_PCK_DEF_IIP4_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x850060000640ll;
    __bdk_csr_fatal("NPC_AF_PCK_DEF_IIP4", 0, 0, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_PCK_DEF_IIP4 bdk_npc_af_pck_def_iip4_t
#define bustype_BDK_NPC_AF_PCK_DEF_IIP4 BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_PCK_DEF_IIP4 "NPC_AF_PCK_DEF_IIP4"
#define device_bar_BDK_NPC_AF_PCK_DEF_IIP4 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_PCK_DEF_IIP4 0
#define arguments_BDK_NPC_AF_PCK_DEF_IIP4 -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_pck_def_oip4
 *
 * NPC AF Protocol Check Outer IPv4 Definition Register
 * Provides layer information used by the protocol checker to identify an outer IPv4 header.
 */
union bdk_npc_af_pck_def_oip4
{
    uint64_t u;
    struct bdk_npc_af_pck_def_oip4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t lid                   : 3;  /**< [ 10:  8](R/W) Layer ID. Enumerated by NPC_LID_E. */
        uint64_t ltype_match           : 4;  /**< [  7:  4](R/W) Layer type match value. Hardware detects a layer match when
                                                                 \<pre\>
                                                                 ([LTYPE_MATCH] & [LTYPE_MASK]) == (NPC_RESULT_S[LX[LTYPE]] & [LTYPE_MASK])
                                                                 \</pre\>

                                                                 where LX is one of LA, LB, ..., LH as selected by [LID]. */
        uint64_t ltype_mask            : 4;  /**< [  3:  0](R/W) Layer type mask. See [LTYPE_MATCH]. */
#else /* Word 0 - Little Endian */
        uint64_t ltype_mask            : 4;  /**< [  3:  0](R/W) Layer type mask. See [LTYPE_MATCH]. */
        uint64_t ltype_match           : 4;  /**< [  7:  4](R/W) Layer type match value. Hardware detects a layer match when
                                                                 \<pre\>
                                                                 ([LTYPE_MATCH] & [LTYPE_MASK]) == (NPC_RESULT_S[LX[LTYPE]] & [LTYPE_MASK])
                                                                 \</pre\>

                                                                 where LX is one of LA, LB, ..., LH as selected by [LID]. */
        uint64_t lid                   : 3;  /**< [ 10:  8](R/W) Layer ID. Enumerated by NPC_LID_E. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_pck_def_oip4_s cn; */
};
typedef union bdk_npc_af_pck_def_oip4 bdk_npc_af_pck_def_oip4_t;

#define BDK_NPC_AF_PCK_DEF_OIP4 BDK_NPC_AF_PCK_DEF_OIP4_FUNC()
static inline uint64_t BDK_NPC_AF_PCK_DEF_OIP4_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_PCK_DEF_OIP4_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x850060000620ll;
    __bdk_csr_fatal("NPC_AF_PCK_DEF_OIP4", 0, 0, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_PCK_DEF_OIP4 bdk_npc_af_pck_def_oip4_t
#define bustype_BDK_NPC_AF_PCK_DEF_OIP4 BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_PCK_DEF_OIP4 "NPC_AF_PCK_DEF_OIP4"
#define device_bar_BDK_NPC_AF_PCK_DEF_OIP4 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_PCK_DEF_OIP4 0
#define arguments_BDK_NPC_AF_PCK_DEF_OIP4 -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_pck_def_oip6
 *
 * NPC AF Protocol Check Outer IPv4 Definition Register
 * Provides layer information used by the protocol checker to identify an outer
 * IPv6 header. [LID] must have the same value as NPC_AF_PCK_DEF_OIP4[LID].
 */
union bdk_npc_af_pck_def_oip6
{
    uint64_t u;
    struct bdk_npc_af_pck_def_oip6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t lid                   : 3;  /**< [ 10:  8](R/W) Layer ID. Enumerated by NPC_LID_E. */
        uint64_t ltype_match           : 4;  /**< [  7:  4](R/W) Layer type match value. Hardware detects a layer match when
                                                                 \<pre\>
                                                                 ([LTYPE_MATCH] & [LTYPE_MASK]) == (NPC_RESULT_S[LX[LTYPE]] & [LTYPE_MASK])
                                                                 \</pre\>

                                                                 where LX is one of LA, LB, ..., LH as selected by [LID]. */
        uint64_t ltype_mask            : 4;  /**< [  3:  0](R/W) Layer type mask. See [LTYPE_MATCH]. */
#else /* Word 0 - Little Endian */
        uint64_t ltype_mask            : 4;  /**< [  3:  0](R/W) Layer type mask. See [LTYPE_MATCH]. */
        uint64_t ltype_match           : 4;  /**< [  7:  4](R/W) Layer type match value. Hardware detects a layer match when
                                                                 \<pre\>
                                                                 ([LTYPE_MATCH] & [LTYPE_MASK]) == (NPC_RESULT_S[LX[LTYPE]] & [LTYPE_MASK])
                                                                 \</pre\>

                                                                 where LX is one of LA, LB, ..., LH as selected by [LID]. */
        uint64_t lid                   : 3;  /**< [ 10:  8](R/W) Layer ID. Enumerated by NPC_LID_E. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_pck_def_oip6_s cn; */
};
typedef union bdk_npc_af_pck_def_oip6 bdk_npc_af_pck_def_oip6_t;

#define BDK_NPC_AF_PCK_DEF_OIP6 BDK_NPC_AF_PCK_DEF_OIP6_FUNC()
static inline uint64_t BDK_NPC_AF_PCK_DEF_OIP6_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_PCK_DEF_OIP6_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x850060000630ll;
    __bdk_csr_fatal("NPC_AF_PCK_DEF_OIP6", 0, 0, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_PCK_DEF_OIP6 bdk_npc_af_pck_def_oip6_t
#define bustype_BDK_NPC_AF_PCK_DEF_OIP6 BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_PCK_DEF_OIP6 "NPC_AF_PCK_DEF_OIP6"
#define device_bar_BDK_NPC_AF_PCK_DEF_OIP6 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_PCK_DEF_OIP6 0
#define arguments_BDK_NPC_AF_PCK_DEF_OIP6 -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_pck_def_ol2
 *
 * NPC AF Protocol Check Outer L2 Definition Register
 * Provides layer information used by the protocol checker to identify an outer L2 header.
 */
union bdk_npc_af_pck_def_ol2
{
    uint64_t u;
    struct bdk_npc_af_pck_def_ol2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t lid                   : 3;  /**< [ 10:  8](R/W) Layer ID. Enumerated by NPC_LID_E. */
        uint64_t ltype_match           : 4;  /**< [  7:  4](R/W) Layer type match value. Hardware detects a layer match when
                                                                 \<pre\>
                                                                 ([LTYPE_MATCH] & [LTYPE_MASK]) == (NPC_RESULT_S[LX[LTYPE]] & [LTYPE_MASK])
                                                                 \</pre\>

                                                                 where LX is one of LA, LB, ..., LH as selected by [LID]. */
        uint64_t ltype_mask            : 4;  /**< [  3:  0](R/W) Layer type mask. See [LTYPE_MATCH]. */
#else /* Word 0 - Little Endian */
        uint64_t ltype_mask            : 4;  /**< [  3:  0](R/W) Layer type mask. See [LTYPE_MATCH]. */
        uint64_t ltype_match           : 4;  /**< [  7:  4](R/W) Layer type match value. Hardware detects a layer match when
                                                                 \<pre\>
                                                                 ([LTYPE_MATCH] & [LTYPE_MASK]) == (NPC_RESULT_S[LX[LTYPE]] & [LTYPE_MASK])
                                                                 \</pre\>

                                                                 where LX is one of LA, LB, ..., LH as selected by [LID]. */
        uint64_t lid                   : 3;  /**< [ 10:  8](R/W) Layer ID. Enumerated by NPC_LID_E. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_pck_def_ol2_s cn; */
};
typedef union bdk_npc_af_pck_def_ol2 bdk_npc_af_pck_def_ol2_t;

#define BDK_NPC_AF_PCK_DEF_OL2 BDK_NPC_AF_PCK_DEF_OL2_FUNC()
static inline uint64_t BDK_NPC_AF_PCK_DEF_OL2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_PCK_DEF_OL2_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x850060000610ll;
    __bdk_csr_fatal("NPC_AF_PCK_DEF_OL2", 0, 0, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_PCK_DEF_OL2 bdk_npc_af_pck_def_ol2_t
#define bustype_BDK_NPC_AF_PCK_DEF_OL2 BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_PCK_DEF_OL2 "NPC_AF_PCK_DEF_OL2"
#define device_bar_BDK_NPC_AF_PCK_DEF_OL2 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_PCK_DEF_OL2 0
#define arguments_BDK_NPC_AF_PCK_DEF_OL2 -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_pkind#_action0
 *
 * NPC AF Port Kind Action Data 0 Registers
 * NPC_AF_PKIND()_ACTION0 and NPC_AF_PKIND()_ACTION1 specify the initial parse state and
 * operations to perform before entering KPU 0.
 */
union bdk_npc_af_pkindx_action0
{
    uint64_t u;
    struct bdk_npc_af_pkindx_action0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_57_63        : 7;
        uint64_t byp_count             : 3;  /**< [ 56: 54](R/W) Bypass count. When nonzero, specifies the number of enabled KPUs to be
                                                                 bypassed. For example, if the bypass count is two in the matching entry for
                                                                 KPU 3, NPC_AF_KPU(4,6,7)_CFG[ENA] = 1 and NPC_AF_KPU(5)_CFG[ENA] = 0, then:
                                                                 * KPUs 4 and 6 are bypassed.
                                                                 * The matching entry's [NEXT_STATE] and
                                                                 NPC_AF_KPU()_ENTRY()_ACTION1[DP*_OFFSET] in KPU 3 are used for the lookup in
                                                                 KPU 7. */
        uint64_t capture_ena           : 1;  /**< [ 53: 53](R/W) Layer capture enable. When set, layer information is captured in
                                                                 NPC_RESULT_S. When clear, layer information is not captured by the KPU. */
        uint64_t parse_done            : 1;  /**< [ 52: 52](R/W) Parse done. When set, terminate parse after this KPU and bypass subsequent KPUs. */
        uint64_t next_state            : 8;  /**< [ 51: 44](R/W) Search value for ternary comparison with the next KPU's
                                                                 NPC_AF_KPU()_ENTRY()_CAM()[STATE]. */
        uint64_t reserved_43           : 1;
        uint64_t capture_lid           : 3;  /**< [ 42: 40](R/W) Capture layer ID. Specifies the layer for which information is captured in
                                                                 NPC_RESULT_S. Enumerated by NPC_LID_E. */
        uint64_t capture_ltype         : 4;  /**< [ 39: 36](R/W) Capture layer type. When [CAPTURE_ENA] is set, specifies
                                                                 NPC_LAYER_INFO_S[LTYPE] value captured in the approprate layer within
                                                                 NPC_RESULT_S. */
        uint64_t capture_flags         : 8;  /**< [ 35: 28](R/W) Capture flags. When nonzero, specifies which NPC_LAYER_INFO_S[FLAGS] bits
                                                                 to set in the approprate layer within
                                                                 NPC_RESULT_S, as follows:
                                                                 _ NPC_LAYER_INFO_S[FLAGS] |= [CAPTURE_FLAGS]

                                                                 Note that flags are captured irrespective of the [CAPTURE_ENA] value. */
        uint64_t ptr_advance           : 8;  /**< [ 27: 20](R/W) Pointer advance. Fixed value added to NPC_RESULT_S[EOH_PTR]. See also [VAR_LEN_OFFSET]. */
        uint64_t var_len_offset        : 8;  /**< [ 19: 12](R/W) Variable length byte offset. When [VAR_LEN_MASK] is nonzero, byte offset
                                                                 from current header pointer of the packet byte that supplies a variable
                                                                 pointer advance value.

                                                                 The pointer advance algorithm is as follows:

                                                                 \<pre\>
                                                                 var_len_byte = packet byte at (NPC_RESULT_S[EOH_PTR] + [VAR_LEN_OFFSET]);
                                                                 masked_var_len_byte = var_len_byte & [VAR_LEN_MASK];

                                                                 if ([VAR_LEN_RIGHT])
                                                                    var_len_advance = masked_var_len_byte \>\> [VAR_LEN_SHIFT];
                                                                 else
                                                                    var_len_advance = masked_var_len_byte \<\< [VAR_LEN_SHIFT];

                                                                 NPC_RESULT_S[EOH_PTR] += ([PTR_ADVANCE] + var_len_advance);
                                                                 \</pre\> */
        uint64_t var_len_mask          : 8;  /**< [ 11:  4](R/W) Variable length mask. See [VAR_LEN_OFFSET]. */
        uint64_t var_len_right         : 1;  /**< [  3:  3](R/W) Variable length shift direction.
                                                                 0 = Left shift.
                                                                 1 = Right shift. */
        uint64_t var_len_shift         : 3;  /**< [  2:  0](R/W) Variable length shift size in bits. See [VAR_LEN_OFFSET]. */
#else /* Word 0 - Little Endian */
        uint64_t var_len_shift         : 3;  /**< [  2:  0](R/W) Variable length shift size in bits. See [VAR_LEN_OFFSET]. */
        uint64_t var_len_right         : 1;  /**< [  3:  3](R/W) Variable length shift direction.
                                                                 0 = Left shift.
                                                                 1 = Right shift. */
        uint64_t var_len_mask          : 8;  /**< [ 11:  4](R/W) Variable length mask. See [VAR_LEN_OFFSET]. */
        uint64_t var_len_offset        : 8;  /**< [ 19: 12](R/W) Variable length byte offset. When [VAR_LEN_MASK] is nonzero, byte offset
                                                                 from current header pointer of the packet byte that supplies a variable
                                                                 pointer advance value.

                                                                 The pointer advance algorithm is as follows:

                                                                 \<pre\>
                                                                 var_len_byte = packet byte at (NPC_RESULT_S[EOH_PTR] + [VAR_LEN_OFFSET]);
                                                                 masked_var_len_byte = var_len_byte & [VAR_LEN_MASK];

                                                                 if ([VAR_LEN_RIGHT])
                                                                    var_len_advance = masked_var_len_byte \>\> [VAR_LEN_SHIFT];
                                                                 else
                                                                    var_len_advance = masked_var_len_byte \<\< [VAR_LEN_SHIFT];

                                                                 NPC_RESULT_S[EOH_PTR] += ([PTR_ADVANCE] + var_len_advance);
                                                                 \</pre\> */
        uint64_t ptr_advance           : 8;  /**< [ 27: 20](R/W) Pointer advance. Fixed value added to NPC_RESULT_S[EOH_PTR]. See also [VAR_LEN_OFFSET]. */
        uint64_t capture_flags         : 8;  /**< [ 35: 28](R/W) Capture flags. When nonzero, specifies which NPC_LAYER_INFO_S[FLAGS] bits
                                                                 to set in the approprate layer within
                                                                 NPC_RESULT_S, as follows:
                                                                 _ NPC_LAYER_INFO_S[FLAGS] |= [CAPTURE_FLAGS]

                                                                 Note that flags are captured irrespective of the [CAPTURE_ENA] value. */
        uint64_t capture_ltype         : 4;  /**< [ 39: 36](R/W) Capture layer type. When [CAPTURE_ENA] is set, specifies
                                                                 NPC_LAYER_INFO_S[LTYPE] value captured in the approprate layer within
                                                                 NPC_RESULT_S. */
        uint64_t capture_lid           : 3;  /**< [ 42: 40](R/W) Capture layer ID. Specifies the layer for which information is captured in
                                                                 NPC_RESULT_S. Enumerated by NPC_LID_E. */
        uint64_t reserved_43           : 1;
        uint64_t next_state            : 8;  /**< [ 51: 44](R/W) Search value for ternary comparison with the next KPU's
                                                                 NPC_AF_KPU()_ENTRY()_CAM()[STATE]. */
        uint64_t parse_done            : 1;  /**< [ 52: 52](R/W) Parse done. When set, terminate parse after this KPU and bypass subsequent KPUs. */
        uint64_t capture_ena           : 1;  /**< [ 53: 53](R/W) Layer capture enable. When set, layer information is captured in
                                                                 NPC_RESULT_S. When clear, layer information is not captured by the KPU. */
        uint64_t byp_count             : 3;  /**< [ 56: 54](R/W) Bypass count. When nonzero, specifies the number of enabled KPUs to be
                                                                 bypassed. For example, if the bypass count is two in the matching entry for
                                                                 KPU 3, NPC_AF_KPU(4,6,7)_CFG[ENA] = 1 and NPC_AF_KPU(5)_CFG[ENA] = 0, then:
                                                                 * KPUs 4 and 6 are bypassed.
                                                                 * The matching entry's [NEXT_STATE] and
                                                                 NPC_AF_KPU()_ENTRY()_ACTION1[DP*_OFFSET] in KPU 3 are used for the lookup in
                                                                 KPU 7. */
        uint64_t reserved_57_63        : 7;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_pkindx_action0_s cn; */
};
typedef union bdk_npc_af_pkindx_action0 bdk_npc_af_pkindx_action0_t;

static inline uint64_t BDK_NPC_AF_PKINDX_ACTION0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_PKINDX_ACTION0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=63))
        return 0x850060080000ll + 0x40ll * ((a) & 0x3f);
    __bdk_csr_fatal("NPC_AF_PKINDX_ACTION0", 1, a, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_PKINDX_ACTION0(a) bdk_npc_af_pkindx_action0_t
#define bustype_BDK_NPC_AF_PKINDX_ACTION0(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_PKINDX_ACTION0(a) "NPC_AF_PKINDX_ACTION0"
#define device_bar_BDK_NPC_AF_PKINDX_ACTION0(a) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_PKINDX_ACTION0(a) (a)
#define arguments_BDK_NPC_AF_PKINDX_ACTION0(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_pkind#_action1
 *
 * NPC AF Port Kind Action Data 1 Registers
 * NPC_AF_PKIND()_ACTION0 and NPC_AF_PKIND()_ACTION1 specify the initial parse state and
 * operations to perform before entering KPU 0.
 */
union bdk_npc_af_pkindx_action1
{
    uint64_t u;
    struct bdk_npc_af_pkindx_action1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t errlev                : 4;  /**< [ 35: 32](R/W) Error level. Ignored when [ERRCODE] is zero. Otherwise, value is captured
                                                                 in NPC_RESULT_S[ERRLEV], indicating the protocol layer containing the
                                                                 error.  Enumerated by NPC_ERRLEV_E. */
        uint64_t errcode               : 8;  /**< [ 31: 24](R/W) Error code. Ignored when zero. When nonzero, [ERRCODE] is captured in
                                                                 NPC_RESULT_S[ERRCODE] and [ERRLEV] is captured in NPC_RESULT_S[ERRLEV] */
        uint64_t dp2_offset            : 8;  /**< [ 23: 16](R/W) Decision point 2 offset to next KPU. See [DP0_OFFSET]. */
        uint64_t dp1_offset            : 8;  /**< [ 15:  8](R/W) Decision point 1 offset to next KPU. See [DP0_OFFSET]. */
        uint64_t dp0_offset            : 8;  /**< [  7:  0](R/W) Decision point 0 offset to next KPU. Byte offset relative to the
                                                                 updated NPC_RESULT_S[EOH_PTR] value of the two packet bytes used for
                                                                 ternary comparison with the next KPU's
                                                                 NPC_AF_KPU()_ENTRY()_CAM()[DP0_DATA]. */
#else /* Word 0 - Little Endian */
        uint64_t dp0_offset            : 8;  /**< [  7:  0](R/W) Decision point 0 offset to next KPU. Byte offset relative to the
                                                                 updated NPC_RESULT_S[EOH_PTR] value of the two packet bytes used for
                                                                 ternary comparison with the next KPU's
                                                                 NPC_AF_KPU()_ENTRY()_CAM()[DP0_DATA]. */
        uint64_t dp1_offset            : 8;  /**< [ 15:  8](R/W) Decision point 1 offset to next KPU. See [DP0_OFFSET]. */
        uint64_t dp2_offset            : 8;  /**< [ 23: 16](R/W) Decision point 2 offset to next KPU. See [DP0_OFFSET]. */
        uint64_t errcode               : 8;  /**< [ 31: 24](R/W) Error code. Ignored when zero. When nonzero, [ERRCODE] is captured in
                                                                 NPC_RESULT_S[ERRCODE] and [ERRLEV] is captured in NPC_RESULT_S[ERRLEV] */
        uint64_t errlev                : 4;  /**< [ 35: 32](R/W) Error level. Ignored when [ERRCODE] is zero. Otherwise, value is captured
                                                                 in NPC_RESULT_S[ERRLEV], indicating the protocol layer containing the
                                                                 error.  Enumerated by NPC_ERRLEV_E. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_pkindx_action1_s cn; */
};
typedef union bdk_npc_af_pkindx_action1 bdk_npc_af_pkindx_action1_t;

static inline uint64_t BDK_NPC_AF_PKINDX_ACTION1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_PKINDX_ACTION1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=63))
        return 0x850060080008ll + 0x40ll * ((a) & 0x3f);
    __bdk_csr_fatal("NPC_AF_PKINDX_ACTION1", 1, a, 0, 0, 0);
}

#define typedef_BDK_NPC_AF_PKINDX_ACTION1(a) bdk_npc_af_pkindx_action1_t
#define bustype_BDK_NPC_AF_PKINDX_ACTION1(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_PKINDX_ACTION1(a) "NPC_AF_PKINDX_ACTION1"
#define device_bar_BDK_NPC_AF_PKINDX_ACTION1(a) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_PKINDX_ACTION1(a) (a)
#define arguments_BDK_NPC_AF_PKINDX_ACTION1(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) npc_af_pkind#_cpi_def#
 *
 * NPC AF Port Kind Channel Parse Index Definition Registers
 * These registers specify the layer information and algorithm to compute a
 * packet's channel parse index (CPI), which provides a port to channel adder for
 * calculating NPC_RESULT_S[CHAN].
 *
 * There are two CPI definitions per port kind, allowing the CPI computation to
 * use two possible layer definitions in the parsed packet, e.g. DiffServ DSCP
 * from either IPv4 or IPv6 header.
 *
 * CPI pseudocode:
 * \<pre\>
 * for (i = 0; i \< 2; i++) {
 *    cpi_def = NPC_AF_PKIND()_CPI_DEF(i);
 *    LX = LA, LB, ..., or LH as selected by cpi_def[LID];
 *
 *    if (cpi_def[VALID]
 *        && ((cpi_def[LTYPE_MATCH] & cpi_def[LTYPE_MASK])
 *             == (NPC_RESULT_S[LX[LTYPE]] & cpi_def[LTYPE_MASK]))
 *        && ((cpi_def[FLAGS_MATCH] & cpi_def[FLAGS_MASK])
 *             == (NPC_RESULT_S[LX[FLAGS]] & cpi_def[FLAGS_MASK])))
 *    {
 *       // Found matching layer
 *       nibble_offset = (2*NPC_RESULT_S[LX[LPTR]]) + cpi_def[ADD_OFFSET];
 *       add_byte = byte at nibble_offset from start of packet;
 *       cpi_add = (add_byte & cpi_def[ADD_MASK]) \>\> cpi_def[ADD_SHIFT];
 *       cpi = cpi_def[CPI_BASE] + cpi_add;
 *       NPC_RESULT_S[CHAN] += NPC_AF_CPI(cpi)_CFG[PADD];
 *       break;
 *    }
 * }
 * \</pre\>
 */
union bdk_npc_af_pkindx_cpi_defx
{
    uint64_t u;
    struct bdk_npc_af_pkindx_cpi_defx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ena                   : 1;  /**< [ 63: 63](R/W) Enable port to channel adder. */
        uint64_t reserved_59_62        : 4;
        uint64_t lid                   : 3;  /**< [ 58: 56](R/W) Layer ID. Enumerated by NPC_LID_E. */
        uint64_t ltype_match           : 4;  /**< [ 55: 52](R/W) Layer type match value. */
        uint64_t ltype_mask            : 4;  /**< [ 51: 48](R/W) Layer type mask. */
        uint64_t flags_match           : 8;  /**< [ 47: 40](R/W) Layer flags match value. */
        uint64_t flags_mask            : 8;  /**< [ 39: 32](R/W) Layer flags mask. */
        uint64_t add_offset            : 8;  /**< [ 31: 24](R/W) Add nibble offset. Nibble offset of packet byte that supplies a CPI
                                                                 add value, relative to the start of the matching layer
                                                                 (NPC_LAYER_INFO_S[LPTR]). */
        uint64_t add_mask              : 8;  /**< [ 23: 16](R/W) Add mask. */
        uint64_t reserved_15           : 1;
        uint64_t add_shift             : 3;  /**< [ 14: 12](R/W) Add right shift. */
        uint64_t reserved_10_11        : 2;
        uint64_t cpi_base              : 10; /**< [  9:  0](R/W) Base index into NPC_AF_CPI()_CFG. */
#else /* Word 0 - Little Endian */
        uint64_t cpi_base              : 10; /**< [  9:  0](R/W) Base index into NPC_AF_CPI()_CFG. */
        uint64_t reserved_10_11        : 2;
        uint64_t add_shift             : 3;  /**< [ 14: 12](R/W) Add right shift. */
        uint64_t reserved_15           : 1;
        uint64_t add_mask              : 8;  /**< [ 23: 16](R/W) Add mask. */
        uint64_t add_offset            : 8;  /**< [ 31: 24](R/W) Add nibble offset. Nibble offset of packet byte that supplies a CPI
                                                                 add value, relative to the start of the matching layer
                                                                 (NPC_LAYER_INFO_S[LPTR]). */
        uint64_t flags_mask            : 8;  /**< [ 39: 32](R/W) Layer flags mask. */
        uint64_t flags_match           : 8;  /**< [ 47: 40](R/W) Layer flags match value. */
        uint64_t ltype_mask            : 4;  /**< [ 51: 48](R/W) Layer type mask. */
        uint64_t ltype_match           : 4;  /**< [ 55: 52](R/W) Layer type match value. */
        uint64_t lid                   : 3;  /**< [ 58: 56](R/W) Layer ID. Enumerated by NPC_LID_E. */
        uint64_t reserved_59_62        : 4;
        uint64_t ena                   : 1;  /**< [ 63: 63](R/W) Enable port to channel adder. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_npc_af_pkindx_cpi_defx_s cn; */
};
typedef union bdk_npc_af_pkindx_cpi_defx bdk_npc_af_pkindx_cpi_defx_t;

static inline uint64_t BDK_NPC_AF_PKINDX_CPI_DEFX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NPC_AF_PKINDX_CPI_DEFX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=63) && (b<=1)))
        return 0x850060080020ll + 0x40ll * ((a) & 0x3f) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("NPC_AF_PKINDX_CPI_DEFX", 2, a, b, 0, 0);
}

#define typedef_BDK_NPC_AF_PKINDX_CPI_DEFX(a,b) bdk_npc_af_pkindx_cpi_defx_t
#define bustype_BDK_NPC_AF_PKINDX_CPI_DEFX(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NPC_AF_PKINDX_CPI_DEFX(a,b) "NPC_AF_PKINDX_CPI_DEFX"
#define device_bar_BDK_NPC_AF_PKINDX_CPI_DEFX(a,b) 0x0 /* BAR0 */
#define busnum_BDK_NPC_AF_PKINDX_CPI_DEFX(a,b) (a)
#define arguments_BDK_NPC_AF_PKINDX_CPI_DEFX(a,b) (a),(b),-1,-1

#endif /* __BDK_CSRS_NPC_H__ */
