#ifndef __BDK_CSRS_RFOE_H__
#define __BDK_CSRS_RFOE_H__
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
 * OcteonTX RFOE.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration rfoe_order_info_type_e
 *
 * RoE orderInfoType Enumeration
 * Enumerates the types of RoE header field orderInfo.
 */
#define BDK_RFOE_ORDER_INFO_TYPE_E_SEQNUM (0)
#define BDK_RFOE_ORDER_INFO_TYPE_E_TIMESTAMP (1)

/**
 * Enumeration rfoe_rx_fd_state_e
 *
 * RoE 0xfd Symbol Assembly State Enumeration
 * Enumerates FD state.
 */
#define BDK_RFOE_RX_FD_STATE_E_FD_BUSY (3)
#define BDK_RFOE_RX_FD_STATE_E_FD_ERR (1)
#define BDK_RFOE_RX_FD_STATE_E_FD_IDLE (2)
#define BDK_RFOE_RX_FD_STATE_E_FD_START (0)

/**
 * Enumeration rfoe_rx_pkt_err_e
 *
 * RFOE Receive Packet Error Enumeration
 */
#define BDK_RFOE_RX_PKT_ERR_E_RE_FCS (7)
#define BDK_RFOE_RX_PKT_ERR_E_RE_FCS_RCV (8)
#define BDK_RFOE_RX_PKT_ERR_E_RE_JABBER (2)
#define BDK_RFOE_RX_PKT_ERR_E_RE_NONE (0)
#define BDK_RFOE_RX_PKT_ERR_E_RE_PARTIAL (1)
#define BDK_RFOE_RX_PKT_ERR_E_RE_RX_CTL (0xb)
#define BDK_RFOE_RX_PKT_ERR_E_RE_SKIP (0xc)
#define BDK_RFOE_RX_PKT_ERR_E_RE_TERMINATE (9)

/**
 * Structure rfoe_cstm_hdr_addr_s
 *
 * RFOE Custom Header Address Structure
 * RoE subtype 0xfc packets and custom header
 * ingress Ethertype packets use this structure format when specifying write
 * addresses.
 */
union bdk_rfoe_cstm_hdr_addr_s
{
    uint64_t u;
    struct bdk_rfoe_cstm_hdr_addr_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t target_mem            : 1;  /**< [ 63: 63] Specifies the target memory for the address.
                                                                 0 = SMEM.
                                                                 1 = LLC/DRAM. */
        uint64_t reserved_62           : 1;
        uint64_t cmd_type              : 2;  /**< [ 61: 60] Command type for LLC/DRAM writes. The write operations are
                                                                 enumerated by MHBW_PNB_WR_CMD_E.

                                                                 Note:
                                                                 * transfer to BPHY SMEM ignore this field.
                                                                 * Unaligned or partial cacheline writes always use
                                                                 MHBW_PNB_WR_CMD_E::STP.

                                                                 Internal:
                                                                 Notes:
                                                                 *BPHY DDR Hardware DMA replaces this field with STP for unaligned cache line
                                                                 starts. All transfers for this burst will be STP.
                                                                 *BPHY DDR Hardware DMA replaces this field with STP for the last transfer in a burst if unaligned. */
        uint64_t reserved_59           : 1;
        uint64_t dswap                 : 3;  /**< [ 58: 56] The byte swap mode for DMA to LLC/DRAM. Enumerated in MHBW_PNB_DSWAP_E.
                                                                 DMA to BPHY SMEM ignores this field. */
        uint64_t reserved_53_55        : 3;
        uint64_t start_addr            : 53; /**< [ 52:  0] Specifies the byte address of the start of the write DMA.
                                                                 The address must be 128-bit aligned, i.e., bits[3:0] must be 0. */
#else /* Word 0 - Little Endian */
        uint64_t start_addr            : 53; /**< [ 52:  0] Specifies the byte address of the start of the write DMA.
                                                                 The address must be 128-bit aligned, i.e., bits[3:0] must be 0. */
        uint64_t reserved_53_55        : 3;
        uint64_t dswap                 : 3;  /**< [ 58: 56] The byte swap mode for DMA to LLC/DRAM. Enumerated in MHBW_PNB_DSWAP_E.
                                                                 DMA to BPHY SMEM ignores this field. */
        uint64_t reserved_59           : 1;
        uint64_t cmd_type              : 2;  /**< [ 61: 60] Command type for LLC/DRAM writes. The write operations are
                                                                 enumerated by MHBW_PNB_WR_CMD_E.

                                                                 Note:
                                                                 * transfer to BPHY SMEM ignore this field.
                                                                 * Unaligned or partial cacheline writes always use
                                                                 MHBW_PNB_WR_CMD_E::STP.

                                                                 Internal:
                                                                 Notes:
                                                                 *BPHY DDR Hardware DMA replaces this field with STP for unaligned cache line
                                                                 starts. All transfers for this burst will be STP.
                                                                 *BPHY DDR Hardware DMA replaces this field with STP for the last transfer in a burst if unaligned. */
        uint64_t reserved_62           : 1;
        uint64_t target_mem            : 1;  /**< [ 63: 63] Specifies the target memory for the address.
                                                                 0 = SMEM.
                                                                 1 = LLC/DRAM. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoe_cstm_hdr_addr_s_s cn; */
};

/**
 * Structure rfoe_fd_cstm_hdr_s
 *
 * RFOE 0xfd Subtype Custom Header Structure
 * RoE packets with subtype 0xfd use this custom header structure.
 * Internal:
 * For ordering, words are in the packet header at x2p in {w1,w0} order.
 */
union bdk_rfoe_fd_cstm_hdr_s
{
    uint64_t u[2];
    struct bdk_rfoe_fd_cstm_hdr_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_96_127       : 32;
        uint64_t antenna               : 8;  /**< [ 95: 88] Antenna number.
                                                                 Internal:
                                                                 Hardware does not use this field other than to report status in PSW & logger messages. */
        uint64_t symbol                : 8;  /**< [ 87: 80] Symbol number.
                                                                 Internal:
                                                                 Hardware does not use this field other than to report status in PSW & logger messages. */
        uint64_t sos                   : 1;  /**< [ 79: 79] Start of symbol flag. Indicates first packet for current symbol.
                                                                 Internal:
                                                                 Hardware uses this for control and error checking for 0xfd subtype */
        uint64_t eos                   : 1;  /**< [ 78: 78] End of symbol flag. Indicates last packet for current symbol.
                                                                 Internal:
                                                                 Hardware uses this for control and error checking for 0xfd subtype */
        uint64_t reserved_64_77        : 14;
#else /* Word 1 - Little Endian */
        uint64_t reserved_64_77        : 14;
        uint64_t eos                   : 1;  /**< [ 78: 78] End of symbol flag. Indicates last packet for current symbol.
                                                                 Internal:
                                                                 Hardware uses this for control and error checking for 0xfd subtype */
        uint64_t sos                   : 1;  /**< [ 79: 79] Start of symbol flag. Indicates first packet for current symbol.
                                                                 Internal:
                                                                 Hardware uses this for control and error checking for 0xfd subtype */
        uint64_t symbol                : 8;  /**< [ 87: 80] Symbol number.
                                                                 Internal:
                                                                 Hardware does not use this field other than to report status in PSW & logger messages. */
        uint64_t antenna               : 8;  /**< [ 95: 88] Antenna number.
                                                                 Internal:
                                                                 Hardware does not use this field other than to report status in PSW & logger messages. */
        uint64_t reserved_96_127       : 32;
#endif /* Word 1 - End */
    } s;
    /* struct bdk_rfoe_fd_cstm_hdr_s_s cn9; */
    struct bdk_rfoe_fd_cstm_hdr_s_cnf95xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t marvell_timestamp     : 32; /**< [127: 96] Arrival timestamp, formatted according to RFOE_MARVELL_TIMESTAMP_S.
                                                                 Internal:
                                                                 TX - Sampled value from the psm__rfoe_time_bus.  BFN, SF, TICK.
                                                                 RX - Unused from packet unless header is written. */
        uint64_t antenna               : 8;  /**< [ 95: 88] Antenna number.
                                                                 Internal:
                                                                 Hardware does not use this field other than to report status in PSW & logger messages. */
        uint64_t symbol                : 8;  /**< [ 87: 80] Symbol number.
                                                                 Internal:
                                                                 Hardware does not use this field other than to report status in PSW & logger messages. */
        uint64_t sos                   : 1;  /**< [ 79: 79] Start of symbol flag. Indicates first packet for current symbol.
                                                                 Internal:
                                                                 Hardware uses this for control and error checking for 0xfd subtype */
        uint64_t eos                   : 1;  /**< [ 78: 78] End of symbol flag. Indicates last packet for current symbol.
                                                                 Internal:
                                                                 Hardware uses this for control and error checking for 0xfd subtype */
        uint64_t reserved_64_77        : 14;
#else /* Word 1 - Little Endian */
        uint64_t reserved_64_77        : 14;
        uint64_t eos                   : 1;  /**< [ 78: 78] End of symbol flag. Indicates last packet for current symbol.
                                                                 Internal:
                                                                 Hardware uses this for control and error checking for 0xfd subtype */
        uint64_t sos                   : 1;  /**< [ 79: 79] Start of symbol flag. Indicates first packet for current symbol.
                                                                 Internal:
                                                                 Hardware uses this for control and error checking for 0xfd subtype */
        uint64_t symbol                : 8;  /**< [ 87: 80] Symbol number.
                                                                 Internal:
                                                                 Hardware does not use this field other than to report status in PSW & logger messages. */
        uint64_t antenna               : 8;  /**< [ 95: 88] Antenna number.
                                                                 Internal:
                                                                 Hardware does not use this field other than to report status in PSW & logger messages. */
        uint64_t marvell_timestamp     : 32; /**< [127: 96] Arrival timestamp, formatted according to RFOE_MARVELL_TIMESTAMP_S.
                                                                 Internal:
                                                                 TX - Sampled value from the psm__rfoe_time_bus.  BFN, SF, TICK.
                                                                 RX - Unused from packet unless header is written. */
#endif /* Word 1 - End */
    } cnf95xxp1;
    struct bdk_rfoe_fd_cstm_hdr_s_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t rfoe_timestamp        : 32; /**< [127: 96] Arrival timestamp, formatted according to RFOE_TIMESTAMP_S.
                                                                 Internal:
                                                                 TX - Sampled value from the psm__rfoe_time_bus.  BFN, SF, TICK.
                                                                 RX - Unused from packet unless header is written. */
        uint64_t antenna               : 8;  /**< [ 95: 88] Antenna number.
                                                                 Internal:
                                                                 Hardware does not use this field other than to report status in PSW & logger messages. */
        uint64_t symbol                : 8;  /**< [ 87: 80] Symbol number.
                                                                 Internal:
                                                                 Hardware does not use this field other than to report status in PSW & logger messages. */
        uint64_t sos                   : 1;  /**< [ 79: 79] Start of symbol flag. Indicates first packet for current symbol.
                                                                 Internal:
                                                                 Hardware uses this for control and error checking for 0xfd subtype */
        uint64_t eos                   : 1;  /**< [ 78: 78] End of symbol flag. Indicates last packet for current symbol.
                                                                 Internal:
                                                                 Hardware uses this for control and error checking for 0xfd subtype */
        uint64_t reserved_64_77        : 14;
#else /* Word 1 - Little Endian */
        uint64_t reserved_64_77        : 14;
        uint64_t eos                   : 1;  /**< [ 78: 78] End of symbol flag. Indicates last packet for current symbol.
                                                                 Internal:
                                                                 Hardware uses this for control and error checking for 0xfd subtype */
        uint64_t sos                   : 1;  /**< [ 79: 79] Start of symbol flag. Indicates first packet for current symbol.
                                                                 Internal:
                                                                 Hardware uses this for control and error checking for 0xfd subtype */
        uint64_t symbol                : 8;  /**< [ 87: 80] Symbol number.
                                                                 Internal:
                                                                 Hardware does not use this field other than to report status in PSW & logger messages. */
        uint64_t antenna               : 8;  /**< [ 95: 88] Antenna number.
                                                                 Internal:
                                                                 Hardware does not use this field other than to report status in PSW & logger messages. */
        uint64_t rfoe_timestamp        : 32; /**< [127: 96] Arrival timestamp, formatted according to RFOE_TIMESTAMP_S.
                                                                 Internal:
                                                                 TX - Sampled value from the psm__rfoe_time_bus.  BFN, SF, TICK.
                                                                 RX - Unused from packet unless header is written. */
#endif /* Word 1 - End */
    } cnf95xxp2;
};

/**
 * Structure rfoe_marvell_timestamp_s
 *
 * RFOE Custom Marvell Timestamp Structure
 * Specifies fields in Marvell timestamp.
 */
union bdk_rfoe_marvell_timestamp_s
{
    uint32_t u;
    struct bdk_rfoe_marvell_timestamp_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t bfn                   : 12; /**< [ 31: 20] Basic frame number. */
        uint32_t sf                    : 4;  /**< [ 19: 16] Subframe number. */
        uint32_t time_tick             : 16; /**< [ 15:  0] Time tick. */
#else /* Word 0 - Little Endian */
        uint32_t time_tick             : 16; /**< [ 15:  0] Time tick. */
        uint32_t sf                    : 4;  /**< [ 19: 16] Subframe number. */
        uint32_t bfn                   : 12; /**< [ 31: 20] Basic frame number. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoe_marvell_timestamp_s_s cn; */
};

/**
 * Structure rfoe_packet_status_s
 *
 * RFOE Packet Status Structure
 */
union bdk_rfoe_packet_status_s
{
    uint64_t u[2];
    struct bdk_rfoe_packet_status_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_62_63        : 2;
        uint64_t lmac_id               : 2;  /**< [ 61: 60] LMAC identifier from MAC that received the packet. */
        uint64_t orderinfo_status      : 1;  /**< [ 59: 59] Sequence number and timestamp check status:
                                                                 0 = Failed checks.
                                                                 1 = Passed checks.

                                                                 Notes:
                                                                 * CHI ignored.  CHI has no seqnum or timestamp.
                                                                 * ALT_PKT  ignored.  ALT_PKT has no seqnum or timestamp.
                                                                 * RoE 0xfd subtype. AND of all segment results. If any segments fail, this will be 0.

                                                                 Internal:
                                                                 CHI and ALT_PKT types always set [ORDERINFO_STATUS] */
        uint64_t jd_target_mem         : 1;  /**< [ 58: 58] Job descriptor pointer target memory.
                                                                 0 = SMEM.
                                                                 1 = LLC/DRAM.
                                                                 If RoE subtype=0xfc, there is no job descriptor and this will be 0x0. */
        uint64_t jd_ptr                : 53; /**< [ 57:  5] Pointer to job descriptor used by this packet/symbol.
                                                                 * All except RoE subtype=0xfc, job descriptor pointer corresponding to this packet status
                                                                 * If RoE subtype=0xfc, this will be 0x0. */
        uint64_t dma_error             : 1;  /**< [  4:  4] DMA or header processing error. Possible errors include:
                                                                 * Late aperture failure.
                                                                 * Attempted to write past the end of the buffer.
                                                                 * RoE length field did not match incoming packet. */
        uint64_t pkt_err_sts           : 4;  /**< [  3:  0] Packet error status, enumerated by RFOE_RX_PKT_ERR_E.
                                                                 Internal:
                                                                 Packet Error Status from x2p err field.  0 = no error detected. Values enumerated in
                                                                 x2p2_p2x2_defs::x2p2_pkt_err_t */
#else /* Word 0 - Little Endian */
        uint64_t pkt_err_sts           : 4;  /**< [  3:  0] Packet error status, enumerated by RFOE_RX_PKT_ERR_E.
                                                                 Internal:
                                                                 Packet Error Status from x2p err field.  0 = no error detected. Values enumerated in
                                                                 x2p2_p2x2_defs::x2p2_pkt_err_t */
        uint64_t dma_error             : 1;  /**< [  4:  4] DMA or header processing error. Possible errors include:
                                                                 * Late aperture failure.
                                                                 * Attempted to write past the end of the buffer.
                                                                 * RoE length field did not match incoming packet. */
        uint64_t jd_ptr                : 53; /**< [ 57:  5] Pointer to job descriptor used by this packet/symbol.
                                                                 * All except RoE subtype=0xfc, job descriptor pointer corresponding to this packet status
                                                                 * If RoE subtype=0xfc, this will be 0x0. */
        uint64_t jd_target_mem         : 1;  /**< [ 58: 58] Job descriptor pointer target memory.
                                                                 0 = SMEM.
                                                                 1 = LLC/DRAM.
                                                                 If RoE subtype=0xfc, there is no job descriptor and this will be 0x0. */
        uint64_t orderinfo_status      : 1;  /**< [ 59: 59] Sequence number and timestamp check status:
                                                                 0 = Failed checks.
                                                                 1 = Passed checks.

                                                                 Notes:
                                                                 * CHI ignored.  CHI has no seqnum or timestamp.
                                                                 * ALT_PKT  ignored.  ALT_PKT has no seqnum or timestamp.
                                                                 * RoE 0xfd subtype. AND of all segment results. If any segments fail, this will be 0.

                                                                 Internal:
                                                                 CHI and ALT_PKT types always set [ORDERINFO_STATUS] */
        uint64_t lmac_id               : 2;  /**< [ 61: 60] LMAC identifier from MAC that received the packet. */
        uint64_t reserved_62_63        : 2;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_96_127       : 32;
        uint64_t fd_antid              : 8;  /**< [ 95: 88] For RoE subtype=0xfd packets, this is the RFOE_FD_CSTM_HDR_S[ANTENNA]
                                                                 field from the custom header. For other packets, this field is
                                                                 reserved.

                                                                 Internal:
                                                                 - Others: 0. */
        uint64_t fd_symbol             : 8;  /**< [ 87: 80] For RoE subtype=0xfd packets, this is the RFOE_FD_CSTM_HDR_S[SYMBOL]
                                                                 field from the custom header. For other packets, this field is
                                                                 reserved.

                                                                 Internal:
                                                                 - Others: 0. */
        uint64_t roe_flowid            : 8;  /**< [ 79: 72] Flowid field extracted from RoE packet header. Undefined for CHI and ALT_PKT
                                                                 packets.

                                                                 Internal:
                                                                 - CHI packets: value from RX_DIRECTION_CTL(first EtherType match)[FLOWID].
                                                                 - ALT_PKT packets: value from RX_DIRECTION_CTL(3)[FLOWID]. */
        uint64_t roe_subtype           : 8;  /**< [ 71: 64] RoE subtype field. Value is undefined for CHI, ALT_PKT, and Transparent packets.
                                                                 Internal:
                                                                 - CHI packets: value will be the upper byte of length field.  Packet byte 14.
                                                                 - ALT_PKT: value will be the first byte of payload.   Packet byte 14.
                                                                 - TRANSPARENT: value will be the first byte of payload.   Packet byte 14. */
#else /* Word 1 - Little Endian */
        uint64_t roe_subtype           : 8;  /**< [ 71: 64] RoE subtype field. Value is undefined for CHI, ALT_PKT, and Transparent packets.
                                                                 Internal:
                                                                 - CHI packets: value will be the upper byte of length field.  Packet byte 14.
                                                                 - ALT_PKT: value will be the first byte of payload.   Packet byte 14.
                                                                 - TRANSPARENT: value will be the first byte of payload.   Packet byte 14. */
        uint64_t roe_flowid            : 8;  /**< [ 79: 72] Flowid field extracted from RoE packet header. Undefined for CHI and ALT_PKT
                                                                 packets.

                                                                 Internal:
                                                                 - CHI packets: value from RX_DIRECTION_CTL(first EtherType match)[FLOWID].
                                                                 - ALT_PKT packets: value from RX_DIRECTION_CTL(3)[FLOWID]. */
        uint64_t fd_symbol             : 8;  /**< [ 87: 80] For RoE subtype=0xfd packets, this is the RFOE_FD_CSTM_HDR_S[SYMBOL]
                                                                 field from the custom header. For other packets, this field is
                                                                 reserved.

                                                                 Internal:
                                                                 - Others: 0. */
        uint64_t fd_antid              : 8;  /**< [ 95: 88] For RoE subtype=0xfd packets, this is the RFOE_FD_CSTM_HDR_S[ANTENNA]
                                                                 field from the custom header. For other packets, this field is
                                                                 reserved.

                                                                 Internal:
                                                                 - Others: 0. */
        uint64_t reserved_96_127       : 32;
#endif /* Word 1 - End */
    } s;
    /* struct bdk_rfoe_packet_status_s_s cn9; */
    struct bdk_rfoe_packet_status_s_cnf95xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_62_63        : 2;
        uint64_t lmac_id               : 2;  /**< [ 61: 60] LMAC identifier from MAC that received the packet. */
        uint64_t orderinfo_status      : 1;  /**< [ 59: 59] Sequence number and timestamp check status:
                                                                 0 = Failed checks.
                                                                 1 = Passed checks.

                                                                 Notes:
                                                                 * CHI ignored.  CHI has no seqnum or timestamp.
                                                                 * ALT_PKT  ignored.  ALT_PKT has no seqnum or timestamp.
                                                                 * RoE 0xfd subtype. AND of all segment results. If any segments fail, this will be 0.

                                                                 Internal:
                                                                 CHI and ALT_PKT types always set [ORDERINFO_STATUS] */
        uint64_t jd_target_mem         : 1;  /**< [ 58: 58] Job descriptor pointer target memory.
                                                                 0 = SMEM.
                                                                 1 = LLC/DRAM.
                                                                 If RoE subtype=0xfc, there is no job descriptor and this will be 0x0. */
        uint64_t jd_ptr                : 53; /**< [ 57:  5] Pointer to job descriptor used by this packet/symbol.
                                                                 * All except RoE subtype=0xfc, job descriptor pointer corresponding to this packet status
                                                                 * If RoE subtype=0xfc, this will be 0x0. */
        uint64_t dma_error             : 1;  /**< [  4:  4] DMA or header processing error. Possible errors include:
                                                                 * Late aperture failure.
                                                                 * Attempted to write past the end of the buffer.
                                                                 * RoE length field did not match incoming packet. */
        uint64_t pkt_err_sts           : 4;  /**< [  3:  0] Packet error status, enumerated by RFOE_RX_PKT_ERR_E.
                                                                 Internal:
                                                                 Packet Error Status from x2p err field.  0 = no error detected. Values enumerated in
                                                                 x2p2_p2x2_defs::x2p2_pkt_err_t */
#else /* Word 0 - Little Endian */
        uint64_t pkt_err_sts           : 4;  /**< [  3:  0] Packet error status, enumerated by RFOE_RX_PKT_ERR_E.
                                                                 Internal:
                                                                 Packet Error Status from x2p err field.  0 = no error detected. Values enumerated in
                                                                 x2p2_p2x2_defs::x2p2_pkt_err_t */
        uint64_t dma_error             : 1;  /**< [  4:  4] DMA or header processing error. Possible errors include:
                                                                 * Late aperture failure.
                                                                 * Attempted to write past the end of the buffer.
                                                                 * RoE length field did not match incoming packet. */
        uint64_t jd_ptr                : 53; /**< [ 57:  5] Pointer to job descriptor used by this packet/symbol.
                                                                 * All except RoE subtype=0xfc, job descriptor pointer corresponding to this packet status
                                                                 * If RoE subtype=0xfc, this will be 0x0. */
        uint64_t jd_target_mem         : 1;  /**< [ 58: 58] Job descriptor pointer target memory.
                                                                 0 = SMEM.
                                                                 1 = LLC/DRAM.
                                                                 If RoE subtype=0xfc, there is no job descriptor and this will be 0x0. */
        uint64_t orderinfo_status      : 1;  /**< [ 59: 59] Sequence number and timestamp check status:
                                                                 0 = Failed checks.
                                                                 1 = Passed checks.

                                                                 Notes:
                                                                 * CHI ignored.  CHI has no seqnum or timestamp.
                                                                 * ALT_PKT  ignored.  ALT_PKT has no seqnum or timestamp.
                                                                 * RoE 0xfd subtype. AND of all segment results. If any segments fail, this will be 0.

                                                                 Internal:
                                                                 CHI and ALT_PKT types always set [ORDERINFO_STATUS] */
        uint64_t lmac_id               : 2;  /**< [ 61: 60] LMAC identifier from MAC that received the packet. */
        uint64_t reserved_62_63        : 2;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t marvell_timestamp     : 32; /**< [127: 96] Timestamp sampled at packet arrival, formatted as
                                                                 RFOE_MARVELL_TIMESTAMP_S. Sampled at SOP in header processing.
                                                                 For 0xfd subtype, it is sampled at SOP of the EOS packet. */
        uint64_t fd_antid              : 8;  /**< [ 95: 88] For RoE subtype=0xfd packets, this is the RFOE_FD_CSTM_HDR_S[ANTENNA]
                                                                 field from the custom header. For other packets, this field is
                                                                 reserved.

                                                                 Internal:
                                                                 - Others: 0. */
        uint64_t fd_symbol             : 8;  /**< [ 87: 80] For RoE subtype=0xfd packets, this is the RFOE_FD_CSTM_HDR_S[SYMBOL]
                                                                 field from the custom header. For other packets, this field is
                                                                 reserved.

                                                                 Internal:
                                                                 - Others: 0. */
        uint64_t roe_flowid            : 8;  /**< [ 79: 72] Flowid field extracted from RoE packet header. Undefined for CHI and ALT_PKT
                                                                 packets.

                                                                 Internal:
                                                                 - CHI packets: value from RX_DIRECTION_CTL(first EtherType match)[FLOWID].
                                                                 - ALT_PKT packets: value from RX_DIRECTION_CTL(3)[FLOWID]. */
        uint64_t roe_subtype           : 8;  /**< [ 71: 64] RoE subtype field. Value is undefined for CHI, ALT_PKT, and Transparent packets.
                                                                 Internal:
                                                                 - CHI packets: value will be the upper byte of length field.  Packet byte 14.
                                                                 - ALT_PKT: value will be the first byte of payload.   Packet byte 14.
                                                                 - TRANSPARENT: value will be the first byte of payload.   Packet byte 14. */
#else /* Word 1 - Little Endian */
        uint64_t roe_subtype           : 8;  /**< [ 71: 64] RoE subtype field. Value is undefined for CHI, ALT_PKT, and Transparent packets.
                                                                 Internal:
                                                                 - CHI packets: value will be the upper byte of length field.  Packet byte 14.
                                                                 - ALT_PKT: value will be the first byte of payload.   Packet byte 14.
                                                                 - TRANSPARENT: value will be the first byte of payload.   Packet byte 14. */
        uint64_t roe_flowid            : 8;  /**< [ 79: 72] Flowid field extracted from RoE packet header. Undefined for CHI and ALT_PKT
                                                                 packets.

                                                                 Internal:
                                                                 - CHI packets: value from RX_DIRECTION_CTL(first EtherType match)[FLOWID].
                                                                 - ALT_PKT packets: value from RX_DIRECTION_CTL(3)[FLOWID]. */
        uint64_t fd_symbol             : 8;  /**< [ 87: 80] For RoE subtype=0xfd packets, this is the RFOE_FD_CSTM_HDR_S[SYMBOL]
                                                                 field from the custom header. For other packets, this field is
                                                                 reserved.

                                                                 Internal:
                                                                 - Others: 0. */
        uint64_t fd_antid              : 8;  /**< [ 95: 88] For RoE subtype=0xfd packets, this is the RFOE_FD_CSTM_HDR_S[ANTENNA]
                                                                 field from the custom header. For other packets, this field is
                                                                 reserved.

                                                                 Internal:
                                                                 - Others: 0. */
        uint64_t marvell_timestamp     : 32; /**< [127: 96] Timestamp sampled at packet arrival, formatted as
                                                                 RFOE_MARVELL_TIMESTAMP_S. Sampled at SOP in header processing.
                                                                 For 0xfd subtype, it is sampled at SOP of the EOS packet. */
#endif /* Word 1 - End */
    } cnf95xxp1;
    struct bdk_rfoe_packet_status_s_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_62_63        : 2;
        uint64_t lmac_id               : 2;  /**< [ 61: 60] LMAC identifier from MAC that received the packet. */
        uint64_t orderinfo_status      : 1;  /**< [ 59: 59] Sequence number and timestamp check status:
                                                                 0 = Failed checks.
                                                                 1 = Passed checks.

                                                                 Notes:
                                                                 * CHI ignored.  CHI has no seqnum or timestamp.
                                                                 * ALT_PKT  ignored.  ALT_PKT has no seqnum or timestamp.
                                                                 * RoE 0xfd subtype. AND of all segment results. If any segments fail, this will be 0.

                                                                 Internal:
                                                                 CHI and ALT_PKT types always set [ORDERINFO_STATUS] */
        uint64_t jd_target_mem         : 1;  /**< [ 58: 58] Job descriptor pointer target memory.
                                                                 0 = SMEM.
                                                                 1 = LLC/DRAM.
                                                                 If RoE subtype=0xfc, there is no job descriptor and this will be 0x0. */
        uint64_t jd_ptr                : 53; /**< [ 57:  5] Pointer to job descriptor used by this packet/symbol.
                                                                 * All except RoE subtype=0xfc, job descriptor pointer corresponding to this packet status
                                                                 * If RoE subtype=0xfc, this will be 0x0. */
        uint64_t dma_error             : 1;  /**< [  4:  4] DMA or header processing error. Possible errors include:
                                                                 * Late aperture failure.
                                                                 * Attempted to write past the end of the buffer.
                                                                 * RoE length field did not match incoming packet. */
        uint64_t pkt_err_sts           : 4;  /**< [  3:  0] Packet error status, enumerated by RFOE_RX_PKT_ERR_E.
                                                                 Internal:
                                                                 Packet Error Status from x2p err field.  0 = no error detected. Values enumerated in
                                                                 x2p2_p2x2_defs::x2p2_pkt_err_t */
#else /* Word 0 - Little Endian */
        uint64_t pkt_err_sts           : 4;  /**< [  3:  0] Packet error status, enumerated by RFOE_RX_PKT_ERR_E.
                                                                 Internal:
                                                                 Packet Error Status from x2p err field.  0 = no error detected. Values enumerated in
                                                                 x2p2_p2x2_defs::x2p2_pkt_err_t */
        uint64_t dma_error             : 1;  /**< [  4:  4] DMA or header processing error. Possible errors include:
                                                                 * Late aperture failure.
                                                                 * Attempted to write past the end of the buffer.
                                                                 * RoE length field did not match incoming packet. */
        uint64_t jd_ptr                : 53; /**< [ 57:  5] Pointer to job descriptor used by this packet/symbol.
                                                                 * All except RoE subtype=0xfc, job descriptor pointer corresponding to this packet status
                                                                 * If RoE subtype=0xfc, this will be 0x0. */
        uint64_t jd_target_mem         : 1;  /**< [ 58: 58] Job descriptor pointer target memory.
                                                                 0 = SMEM.
                                                                 1 = LLC/DRAM.
                                                                 If RoE subtype=0xfc, there is no job descriptor and this will be 0x0. */
        uint64_t orderinfo_status      : 1;  /**< [ 59: 59] Sequence number and timestamp check status:
                                                                 0 = Failed checks.
                                                                 1 = Passed checks.

                                                                 Notes:
                                                                 * CHI ignored.  CHI has no seqnum or timestamp.
                                                                 * ALT_PKT  ignored.  ALT_PKT has no seqnum or timestamp.
                                                                 * RoE 0xfd subtype. AND of all segment results. If any segments fail, this will be 0.

                                                                 Internal:
                                                                 CHI and ALT_PKT types always set [ORDERINFO_STATUS] */
        uint64_t lmac_id               : 2;  /**< [ 61: 60] LMAC identifier from MAC that received the packet. */
        uint64_t reserved_62_63        : 2;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t rfoe_timestamp        : 32; /**< [127: 96] Timestamp sampled at packet arrival, formatted as
                                                                 RFOE_TIMESTAMP_S. Sampled at SOP in header processing.
                                                                 For 0xfd subtype, it is sampled at SOP of the EOS packet. */
        uint64_t fd_antid              : 8;  /**< [ 95: 88] For RoE subtype=0xfd packets, this is the RFOE_FD_CSTM_HDR_S[ANTENNA]
                                                                 field from the custom header. For other packets, this field is
                                                                 reserved.

                                                                 Internal:
                                                                 - Others: 0. */
        uint64_t fd_symbol             : 8;  /**< [ 87: 80] For RoE subtype=0xfd packets, this is the RFOE_FD_CSTM_HDR_S[SYMBOL]
                                                                 field from the custom header. For other packets, this field is
                                                                 reserved.

                                                                 Internal:
                                                                 - Others: 0. */
        uint64_t roe_flowid            : 8;  /**< [ 79: 72] Flowid field extracted from RoE packet header. Undefined for CHI and ALT_PKT
                                                                 packets.

                                                                 Internal:
                                                                 - CHI packets: value from RX_DIRECTION_CTL(first EtherType match)[FLOWID].
                                                                 - ALT_PKT packets: value from RX_DIRECTION_CTL(3)[FLOWID]. */
        uint64_t roe_subtype           : 8;  /**< [ 71: 64] RoE subtype field. Value is undefined for CHI, ALT_PKT, and Transparent packets.
                                                                 Internal:
                                                                 - CHI packets: value will be the upper byte of length field.  Packet byte 14.
                                                                 - ALT_PKT: value will be the first byte of payload.   Packet byte 14.
                                                                 - TRANSPARENT: value will be the first byte of payload.   Packet byte 14. */
#else /* Word 1 - Little Endian */
        uint64_t roe_subtype           : 8;  /**< [ 71: 64] RoE subtype field. Value is undefined for CHI, ALT_PKT, and Transparent packets.
                                                                 Internal:
                                                                 - CHI packets: value will be the upper byte of length field.  Packet byte 14.
                                                                 - ALT_PKT: value will be the first byte of payload.   Packet byte 14.
                                                                 - TRANSPARENT: value will be the first byte of payload.   Packet byte 14. */
        uint64_t roe_flowid            : 8;  /**< [ 79: 72] Flowid field extracted from RoE packet header. Undefined for CHI and ALT_PKT
                                                                 packets.

                                                                 Internal:
                                                                 - CHI packets: value from RX_DIRECTION_CTL(first EtherType match)[FLOWID].
                                                                 - ALT_PKT packets: value from RX_DIRECTION_CTL(3)[FLOWID]. */
        uint64_t fd_symbol             : 8;  /**< [ 87: 80] For RoE subtype=0xfd packets, this is the RFOE_FD_CSTM_HDR_S[SYMBOL]
                                                                 field from the custom header. For other packets, this field is
                                                                 reserved.

                                                                 Internal:
                                                                 - Others: 0. */
        uint64_t fd_antid              : 8;  /**< [ 95: 88] For RoE subtype=0xfd packets, this is the RFOE_FD_CSTM_HDR_S[ANTENNA]
                                                                 field from the custom header. For other packets, this field is
                                                                 reserved.

                                                                 Internal:
                                                                 - Others: 0. */
        uint64_t rfoe_timestamp        : 32; /**< [127: 96] Timestamp sampled at packet arrival, formatted as
                                                                 RFOE_TIMESTAMP_S. Sampled at SOP in header processing.
                                                                 For 0xfd subtype, it is sampled at SOP of the EOS packet. */
#endif /* Word 1 - End */
    } cnf95xxp2;
};

/**
 * Structure rfoe_timestamp_s
 *
 * RFOE Custom Timestamp Structure
 * Specifies fields in RFOE timestamp.
 */
union bdk_rfoe_timestamp_s
{
    uint32_t u;
    struct bdk_rfoe_timestamp_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t bfn                   : 12; /**< [ 31: 20] Basic frame number. */
        uint32_t sf                    : 4;  /**< [ 19: 16] Subframe number. */
        uint32_t time_tick             : 16; /**< [ 15:  0] Time tick. */
#else /* Word 0 - Little Endian */
        uint32_t time_tick             : 16; /**< [ 15:  0] Time tick. */
        uint32_t sf                    : 4;  /**< [ 19: 16] Subframe number. */
        uint32_t bfn                   : 12; /**< [ 31: 20] Basic frame number. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoe_timestamp_s_s cn; */
};

/**
 * Register (RSL) rfoe#_ab#_control
 *
 * RFOE Control Register
 */
union bdk_rfoex_abx_control
{
    uint64_t u;
    struct bdk_rfoex_abx_control_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t jobid2                : 16; /**< [ 63: 48](R/W/H) Job ID for slot 2. */
        uint64_t jobid1                : 16; /**< [ 47: 32](R/W/H) Job ID for slot 1. */
        uint64_t jobid0                : 16; /**< [ 31: 16](R/W/H) Job ID for slot 0. */
        uint64_t reserved_3_15         : 13;
        uint64_t start2                : 1;  /**< [  2:  2](R/W/H) Start processing job in slot 2. */
        uint64_t start1                : 1;  /**< [  1:  1](R/W/H) Start processing job in slot 1. */
        uint64_t start0                : 1;  /**< [  0:  0](R/W/H) Start processing job in slot 0. */
#else /* Word 0 - Little Endian */
        uint64_t start0                : 1;  /**< [  0:  0](R/W/H) Start processing job in slot 0. */
        uint64_t start1                : 1;  /**< [  1:  1](R/W/H) Start processing job in slot 1. */
        uint64_t start2                : 1;  /**< [  2:  2](R/W/H) Start processing job in slot 2. */
        uint64_t reserved_3_15         : 13;
        uint64_t jobid0                : 16; /**< [ 31: 16](R/W/H) Job ID for slot 0. */
        uint64_t jobid1                : 16; /**< [ 47: 32](R/W/H) Job ID for slot 1. */
        uint64_t jobid2                : 16; /**< [ 63: 48](R/W/H) Job ID for slot 2. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_abx_control_s cn; */
};
typedef union bdk_rfoex_abx_control bdk_rfoex_abx_control_t;

static inline uint64_t BDK_RFOEX_ABX_CONTROL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_ABX_CONTROL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=1)))
        return 0x87e043d00000ll + 0x80000ll * ((a) & 0x1) + 0x8000ll * ((b) & 0x1);
    __bdk_csr_fatal("RFOEX_ABX_CONTROL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_ABX_CONTROL(a,b) bdk_rfoex_abx_control_t
#define bustype_BDK_RFOEX_ABX_CONTROL(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_ABX_CONTROL(a,b) "RFOEX_ABX_CONTROL"
#define busnum_BDK_RFOEX_ABX_CONTROL(a,b) (a)
#define arguments_BDK_RFOEX_ABX_CONTROL(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_ab#_scratch
 *
 * INTERNAL: Scratch Register
 *
 * Scratch register.
 */
union bdk_rfoex_abx_scratch
{
    uint64_t u;
    struct bdk_rfoex_abx_scratch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Scratch data. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Scratch data. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_abx_scratch_s cn; */
};
typedef union bdk_rfoex_abx_scratch bdk_rfoex_abx_scratch_t;

static inline uint64_t BDK_RFOEX_ABX_SCRATCH(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_ABX_SCRATCH(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=1)))
        return 0x87e043d00080ll + 0x80000ll * ((a) & 0x1) + 0x8000ll * ((b) & 0x1);
    __bdk_csr_fatal("RFOEX_ABX_SCRATCH", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_ABX_SCRATCH(a,b) bdk_rfoex_abx_scratch_t
#define bustype_BDK_RFOEX_ABX_SCRATCH(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_ABX_SCRATCH(a,b) "RFOEX_ABX_SCRATCH"
#define busnum_BDK_RFOEX_ABX_SCRATCH(a,b) (a)
#define arguments_BDK_RFOEX_ABX_SCRATCH(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_ab#_slot#_configuration
 *
 * RFOE AB Job Configuration Register
 * This register space contains the RFOE job configuration data.
 *
 * Software should not write this register directly, but instead use this
 * format when writing the job configuration section of the job descriptor.
 */
union bdk_rfoex_abx_slotx_configuration
{
    uint64_t u;
    struct bdk_rfoex_abx_slotx_configuration_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_63           : 1;
        uint64_t custom_timestamp_insert : 1;/**< [ 62: 62](R/W) When RFOE()_AB()_SLOT()_CONFIGURATION[PKT_MODE] = 2,
                                                                 when set to 1, for 0xFD subtype,
                                                                 TX inserts custom timestamp into custom header field. */
        uint64_t orderinfo_insert      : 1;  /**< [ 61: 61](R/W) When RFOE()_AB()_SLOT()_CONFIGURATION[PKT_MODE] = 2,
                                                                 when set to 1, for all subtypes,
                                                                 TX inserts seqnum/timestamp into orderInfo field. */
        uint64_t eos                   : 1;  /**< [ 60: 60](R/W) End of symbol flag. Indicates last packet for current symbol. This field is
                                                                 inserted into RoE header for subtype=0xFD and when
                                                                 RFOE()_AB()_SLOT()_CONFIGURATION[PKT_MODE] = 2. */
        uint64_t sos                   : 1;  /**< [ 59: 59](R/W) Start of symbol flag. Indicates first packet for current symbol. This field is
                                                                 inserted into RoE header for subtype=0xFD and when
                                                                 RFOE()_AB()_SLOT()_CONFIGURATION[PKT_MODE] = 2. */
        uint64_t symbol                : 8;  /**< [ 58: 51](R/W) Symbol number to insert into RoE header for subtype=0xFD and when
                                                                 RFOE()_AB()_SLOT()_CONFIGURATION[PKT_MODE] = 2. */
        uint64_t antenna               : 8;  /**< [ 50: 43](R/W) Antenna number to insert into RoE header for subtype=0xFD and when
                                                                 RFOE()_AB()_SLOT()_CONFIGURATION[PKT_MODE] = 2. */
        uint64_t orderinfooffset       : 5;  /**< [ 42: 38](R/W) Byte offset of RoE orderInfo field within header. Used when [PKT_MODE] = 2 to
                                                                 allow RFOE to replace orderInfo field. */
        uint64_t orderinfotype         : 1;  /**< [ 37: 37](R/W) Format for IEEE P1914.3/D3.0 orderInfo enumerated by RFOE_ORDER_INFO_TYPE_E.
                                                                 0 = indicates seqNum is used.
                                                                 1 = indicates timeStamp is used. */
        uint64_t sample_width_sat_bypass : 1;/**< [ 36: 36](R/W) Bypass sample saturation.
                                                                 0 = Perform symmetric saturation to [SAMPLE_WIDTH].
                                                                 1 = Bypass saturation.
                                                                 o If [SAMPLE_WIDTH_OPTION]=0, use the [SAMPLE_WIDTH] most significant
                                                                 bits of the input sample.
                                                                 o If [SAMPLE_WIDTH_OPTION]=1, the rounded value is truncated instead
                                                                 of saturating.

                                                                 Internal:
                                                                 Same as rfif_dl_sample_width.v definition. */
        uint64_t sample_width_option   : 1;  /**< [ 35: 35](R/W) Sample width conversion mode:
                                                                 0: Y = SATn(X).
                                                                 1: Y = SATn(ROUND(X)).

                                                                 SATn(X) is saturation to the range [-2^(n-1)+1, 2^(n-1)-1].

                                                                 ROUND(X) is symmetric rounding, defined as:
                                                                 _ ROUND(X) = (X + 2^(m-1)) \>\> m, if X \>= 0.
                                                                 _ ROUND(X) = -((-X + 2^(m-1)) \>\> m), if X \< 0.
                                                                 _ where m = 16 - n, and when m=0, 2^(0-1) = 0.

                                                                 n is the sample bit width specified by [SAMPLE_WIDTH].

                                                                 Note that the saturation operation can be bypassed by setting
                                                                 [SAMPLE_WIDTH_SAT_BYPASS]=1.

                                                                 Internal:
                                                                 Select sample conversion mode.  Same as rfif_dl_sample_width.v definition */
        uint64_t sample_width          : 5;  /**< [ 34: 30](R/W) For SAMPLE_MODE=1, width in bits of I/Q samples in transmitted RoE
                                                                 packet. Samples read from memory are always assume to have 16-bit I
                                                                 and 16-bit Q components. */
        uint64_t sample_mode           : 1;  /**< [ 29: 29](R/W) Enable sample mode. When set to 1, I/Q samples in the packet are
                                                                 read as 16-bit I/Q values, and converted to [SAMPLE_WIDTH] bits, as
                                                                 per [SAMPLE_WIDTH_OPTION]. Otherwise, samples are written to memory
                                                                 with no conversions. */
        uint64_t lmacid                : 2;  /**< [ 28: 27](R/W) LMAC destination ID. Must select an enabled LMAC on which to send the
                                                                 packet. */
        uint64_t subtype               : 8;  /**< [ 26: 19](R/W) RoE subtype. */
        uint64_t flowid                : 8;  /**< [ 18: 11](R/W) FLOWID for the FLOWID field in the RoE packet header. */
        uint64_t etype_sel             : 3;  /**< [ 10:  8](R/W) When [PKT_MODE]=1, selects which RFOE()_TX_HDR_ETHERTYPE() register
                                                                 provides the Ethertype field to insert in the Ethernet header. Ignored
                                                                 when [PKT_MODE] != 1. */
        uint64_t sa_sel                : 3;  /**< [  7:  5](R/W) When [PKT_MODE]=1, selects which RFOE()_TX_HDR_SA() register
                                                                 provides the source DMAC address to insert in the Ethernet header. Ignored
                                                                 when [PKT_MODE] != 1. */
        uint64_t da_sel                : 3;  /**< [  4:  2](R/W) When [PKT_MODE]=1, selects which RFOE()_TX_HDR_DA() register
                                                                 provides the destination DMAC address to insert in the Ethernet header. Ignored
                                                                 when [PKT_MODE] != 1. */
        uint64_t pkt_mode              : 2;  /**< [  1:  0](R/W) Packet mode.
                                                                 0x0 = Transparent mode (1 pointer in job descriptor).
                                                                       This mode is used for control packet transmit.
                                                                       Hardware does not access the Sequence Number configuration table.
                                                                 0x1 = Packet DMA with Ethernet header built from RFOE()_TX_HDR_*
                                                                       registers. This mode is used for Antenna symbol data transmit.
                                                                       Hardware updates the Sequence Number configuration table accordingly.
                                                                 0x2 = First DMA contains Ethernet, RoE header, Custom header and rbMap.
                                                                       Second DMA contains sample data.
                                                                       This mode is used for Antenna symbol data transmit.
                                                                       Hardware updates the Sequence Number configuration table accordingly.
                                                                 0x3 = Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t pkt_mode              : 2;  /**< [  1:  0](R/W) Packet mode.
                                                                 0x0 = Transparent mode (1 pointer in job descriptor).
                                                                       This mode is used for control packet transmit.
                                                                       Hardware does not access the Sequence Number configuration table.
                                                                 0x1 = Packet DMA with Ethernet header built from RFOE()_TX_HDR_*
                                                                       registers. This mode is used for Antenna symbol data transmit.
                                                                       Hardware updates the Sequence Number configuration table accordingly.
                                                                 0x2 = First DMA contains Ethernet, RoE header, Custom header and rbMap.
                                                                       Second DMA contains sample data.
                                                                       This mode is used for Antenna symbol data transmit.
                                                                       Hardware updates the Sequence Number configuration table accordingly.
                                                                 0x3 = Reserved. */
        uint64_t da_sel                : 3;  /**< [  4:  2](R/W) When [PKT_MODE]=1, selects which RFOE()_TX_HDR_DA() register
                                                                 provides the destination DMAC address to insert in the Ethernet header. Ignored
                                                                 when [PKT_MODE] != 1. */
        uint64_t sa_sel                : 3;  /**< [  7:  5](R/W) When [PKT_MODE]=1, selects which RFOE()_TX_HDR_SA() register
                                                                 provides the source DMAC address to insert in the Ethernet header. Ignored
                                                                 when [PKT_MODE] != 1. */
        uint64_t etype_sel             : 3;  /**< [ 10:  8](R/W) When [PKT_MODE]=1, selects which RFOE()_TX_HDR_ETHERTYPE() register
                                                                 provides the Ethertype field to insert in the Ethernet header. Ignored
                                                                 when [PKT_MODE] != 1. */
        uint64_t flowid                : 8;  /**< [ 18: 11](R/W) FLOWID for the FLOWID field in the RoE packet header. */
        uint64_t subtype               : 8;  /**< [ 26: 19](R/W) RoE subtype. */
        uint64_t lmacid                : 2;  /**< [ 28: 27](R/W) LMAC destination ID. Must select an enabled LMAC on which to send the
                                                                 packet. */
        uint64_t sample_mode           : 1;  /**< [ 29: 29](R/W) Enable sample mode. When set to 1, I/Q samples in the packet are
                                                                 read as 16-bit I/Q values, and converted to [SAMPLE_WIDTH] bits, as
                                                                 per [SAMPLE_WIDTH_OPTION]. Otherwise, samples are written to memory
                                                                 with no conversions. */
        uint64_t sample_width          : 5;  /**< [ 34: 30](R/W) For SAMPLE_MODE=1, width in bits of I/Q samples in transmitted RoE
                                                                 packet. Samples read from memory are always assume to have 16-bit I
                                                                 and 16-bit Q components. */
        uint64_t sample_width_option   : 1;  /**< [ 35: 35](R/W) Sample width conversion mode:
                                                                 0: Y = SATn(X).
                                                                 1: Y = SATn(ROUND(X)).

                                                                 SATn(X) is saturation to the range [-2^(n-1)+1, 2^(n-1)-1].

                                                                 ROUND(X) is symmetric rounding, defined as:
                                                                 _ ROUND(X) = (X + 2^(m-1)) \>\> m, if X \>= 0.
                                                                 _ ROUND(X) = -((-X + 2^(m-1)) \>\> m), if X \< 0.
                                                                 _ where m = 16 - n, and when m=0, 2^(0-1) = 0.

                                                                 n is the sample bit width specified by [SAMPLE_WIDTH].

                                                                 Note that the saturation operation can be bypassed by setting
                                                                 [SAMPLE_WIDTH_SAT_BYPASS]=1.

                                                                 Internal:
                                                                 Select sample conversion mode.  Same as rfif_dl_sample_width.v definition */
        uint64_t sample_width_sat_bypass : 1;/**< [ 36: 36](R/W) Bypass sample saturation.
                                                                 0 = Perform symmetric saturation to [SAMPLE_WIDTH].
                                                                 1 = Bypass saturation.
                                                                 o If [SAMPLE_WIDTH_OPTION]=0, use the [SAMPLE_WIDTH] most significant
                                                                 bits of the input sample.
                                                                 o If [SAMPLE_WIDTH_OPTION]=1, the rounded value is truncated instead
                                                                 of saturating.

                                                                 Internal:
                                                                 Same as rfif_dl_sample_width.v definition. */
        uint64_t orderinfotype         : 1;  /**< [ 37: 37](R/W) Format for IEEE P1914.3/D3.0 orderInfo enumerated by RFOE_ORDER_INFO_TYPE_E.
                                                                 0 = indicates seqNum is used.
                                                                 1 = indicates timeStamp is used. */
        uint64_t orderinfooffset       : 5;  /**< [ 42: 38](R/W) Byte offset of RoE orderInfo field within header. Used when [PKT_MODE] = 2 to
                                                                 allow RFOE to replace orderInfo field. */
        uint64_t antenna               : 8;  /**< [ 50: 43](R/W) Antenna number to insert into RoE header for subtype=0xFD and when
                                                                 RFOE()_AB()_SLOT()_CONFIGURATION[PKT_MODE] = 2. */
        uint64_t symbol                : 8;  /**< [ 58: 51](R/W) Symbol number to insert into RoE header for subtype=0xFD and when
                                                                 RFOE()_AB()_SLOT()_CONFIGURATION[PKT_MODE] = 2. */
        uint64_t sos                   : 1;  /**< [ 59: 59](R/W) Start of symbol flag. Indicates first packet for current symbol. This field is
                                                                 inserted into RoE header for subtype=0xFD and when
                                                                 RFOE()_AB()_SLOT()_CONFIGURATION[PKT_MODE] = 2. */
        uint64_t eos                   : 1;  /**< [ 60: 60](R/W) End of symbol flag. Indicates last packet for current symbol. This field is
                                                                 inserted into RoE header for subtype=0xFD and when
                                                                 RFOE()_AB()_SLOT()_CONFIGURATION[PKT_MODE] = 2. */
        uint64_t orderinfo_insert      : 1;  /**< [ 61: 61](R/W) When RFOE()_AB()_SLOT()_CONFIGURATION[PKT_MODE] = 2,
                                                                 when set to 1, for all subtypes,
                                                                 TX inserts seqnum/timestamp into orderInfo field. */
        uint64_t custom_timestamp_insert : 1;/**< [ 62: 62](R/W) When RFOE()_AB()_SLOT()_CONFIGURATION[PKT_MODE] = 2,
                                                                 when set to 1, for 0xFD subtype,
                                                                 TX inserts custom timestamp into custom header field. */
        uint64_t reserved_63           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_abx_slotx_configuration_s cn; */
};
typedef union bdk_rfoex_abx_slotx_configuration bdk_rfoex_abx_slotx_configuration_t;

static inline uint64_t BDK_RFOEX_ABX_SLOTX_CONFIGURATION(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_ABX_SLOTX_CONFIGURATION(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=1) && (c<=2)))
        return 0x87e043d02000ll + 0x80000ll * ((a) & 0x1) + 0x8000ll * ((b) & 0x1) + 0x2000ll * ((c) & 0x3);
    __bdk_csr_fatal("RFOEX_ABX_SLOTX_CONFIGURATION", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_RFOEX_ABX_SLOTX_CONFIGURATION(a,b,c) bdk_rfoex_abx_slotx_configuration_t
#define bustype_BDK_RFOEX_ABX_SLOTX_CONFIGURATION(a,b,c) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_ABX_SLOTX_CONFIGURATION(a,b,c) "RFOEX_ABX_SLOTX_CONFIGURATION"
#define busnum_BDK_RFOEX_ABX_SLOTX_CONFIGURATION(a,b,c) (a)
#define arguments_BDK_RFOEX_ABX_SLOTX_CONFIGURATION(a,b,c) (a),(b),(c),-1

/**
 * Register (RSL) rfoe#_ab#_slot#_configuration1
 *
 * RFOE AB Job Configuration Register
 * This register space contains the RFOE job configuration data.
 *
 * Software should not write this register directly, but instead use this
 * format when writing the job configuration section of the job descriptor.
 */
union bdk_rfoex_abx_slotx_configuration1
{
    uint64_t u;
    struct bdk_rfoex_abx_slotx_configuration1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t sof_mode              : 2;  /**< [ 63: 62](R/W) SOF bit setting in the Orderinfo Timestamp.
                                                                 This is used when RFOE()_AB()_SLOT()_CONFIGURATION[ORDERINFOTYPE]=1 and
                                                                 RFOE()_AB()_SLOT()_CONFIGURATION[ORDERINFO_INSERT]=1.
                                                                 0x0 = Sample SoF from the timer bus from PSM.
                                                                 0x1 = Sets SoF=0 in the orderInfo timestamp field.
                                                                 0x2 = Reserved.
                                                                 0x3 = Sets SoF=1 in the orderInfo timestamp field. */
        uint64_t reserved_61           : 1;
        uint64_t presentation_time_offset : 29;/**< [ 60: 32](R/W) Presentation time offset is used when RFOE()_AB()_SLOT()_CONFIGURATION[ORDERINFOTYPE]=1.
                                                                 Presentation time offset is added to value of current timebus.tod and the resultant value
                                                                 sent out in the RoE header.

                                                                 _ Bits [60:37] indicate integer nanoseconds.

                                                                 _ Bits [36:32] indicate fractional nanoseconds.

                                                                 See IEEE P1914.3/D3. */
        uint64_t hdr_len               : 8;  /**< [ 31: 24](R/W) Header length in number of bytes. When [PKT_MODE]=0x2, indicates the number of header bytes
                                                                 contained in the read DMA data. */
        uint64_t pkt_len               : 16; /**< [ 23:  8](R/W) The packet length.
                                                                 * When [PKT_MODE]=0x0, the number of bytes to read from the memory.

                                                                 * When [PKT_MODE]=0x1 or 0x2, the number of samples to read from
                                                                 memory. Samples in memory are always 32 bits, with 16-bit I and
                                                                 16-bit Q components. In this case, [PKT_LEN] must be a multiple of 4. */
        uint64_t rbmap_bytes           : 8;  /**< [  7:  0](R/W) Reserved.
                                                                 Internal:
                                                                 When RFOE()_AB()_SLOT()_CONFIGURATION[PKT_MODE]=1, interpret the
                                                                 first [RBMAP_BYTES] as an RoE rbMap. The bytes will be byte-swapped,
                                                                 and the [RBMAP_BYTES] will be zero-padded.

                                                                 Feature not implemented in a meaningful way for t95 pass 1, so making
                                                                 this reserved. */
#else /* Word 0 - Little Endian */
        uint64_t rbmap_bytes           : 8;  /**< [  7:  0](R/W) Reserved.
                                                                 Internal:
                                                                 When RFOE()_AB()_SLOT()_CONFIGURATION[PKT_MODE]=1, interpret the
                                                                 first [RBMAP_BYTES] as an RoE rbMap. The bytes will be byte-swapped,
                                                                 and the [RBMAP_BYTES] will be zero-padded.

                                                                 Feature not implemented in a meaningful way for t95 pass 1, so making
                                                                 this reserved. */
        uint64_t pkt_len               : 16; /**< [ 23:  8](R/W) The packet length.
                                                                 * When [PKT_MODE]=0x0, the number of bytes to read from the memory.

                                                                 * When [PKT_MODE]=0x1 or 0x2, the number of samples to read from
                                                                 memory. Samples in memory are always 32 bits, with 16-bit I and
                                                                 16-bit Q components. In this case, [PKT_LEN] must be a multiple of 4. */
        uint64_t hdr_len               : 8;  /**< [ 31: 24](R/W) Header length in number of bytes. When [PKT_MODE]=0x2, indicates the number of header bytes
                                                                 contained in the read DMA data. */
        uint64_t presentation_time_offset : 29;/**< [ 60: 32](R/W) Presentation time offset is used when RFOE()_AB()_SLOT()_CONFIGURATION[ORDERINFOTYPE]=1.
                                                                 Presentation time offset is added to value of current timebus.tod and the resultant value
                                                                 sent out in the RoE header.

                                                                 _ Bits [60:37] indicate integer nanoseconds.

                                                                 _ Bits [36:32] indicate fractional nanoseconds.

                                                                 See IEEE P1914.3/D3. */
        uint64_t reserved_61           : 1;
        uint64_t sof_mode              : 2;  /**< [ 63: 62](R/W) SOF bit setting in the Orderinfo Timestamp.
                                                                 This is used when RFOE()_AB()_SLOT()_CONFIGURATION[ORDERINFOTYPE]=1 and
                                                                 RFOE()_AB()_SLOT()_CONFIGURATION[ORDERINFO_INSERT]=1.
                                                                 0x0 = Sample SoF from the timer bus from PSM.
                                                                 0x1 = Sets SoF=0 in the orderInfo timestamp field.
                                                                 0x2 = Reserved.
                                                                 0x3 = Sets SoF=1 in the orderInfo timestamp field. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_abx_slotx_configuration1_s cn9; */
    struct bdk_rfoex_abx_slotx_configuration1_cnf95xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_61_63        : 3;
        uint64_t presentation_time_offset : 29;/**< [ 60: 32](R/W) Presentation time offset is used when RFOE()_AB()_SLOT()_CONFIGURATION[ORDERINFOTYPE]=1.
                                                                 Presentation time offset is added to value of current timebus.tod and the resultant value
                                                                 sent out in the RoE header.

                                                                 _ Bits [60:37] indicate integer nanoseconds.

                                                                 _ Bits [36:32] indicate fractional nanoseconds.

                                                                 See IEEE P1914.3/D3. */
        uint64_t hdr_len               : 8;  /**< [ 31: 24](R/W) Header length in number of bytes. When [PKT_MODE]=0x2, indicates the number of header bytes
                                                                 contained in the read DMA data. */
        uint64_t pkt_len               : 16; /**< [ 23:  8](R/W) The packet length.
                                                                 * When [PKT_MODE]=0x0, the number of bytes to read from the memory.

                                                                 * When [PKT_MODE]=0x1 or 0x2, the number of samples to read from
                                                                 memory. Samples in memory are always 32 bits, with 16-bit I and
                                                                 16-bit Q components. In this case, [PKT_LEN] must be a multiple of 4. */
        uint64_t rbmap_bytes           : 8;  /**< [  7:  0](R/W) Reserved.
                                                                 Internal:
                                                                 When RFOE()_AB()_SLOT()_CONFIGURATION[PKT_MODE]=1, interpret the
                                                                 first [RBMAP_BYTES] as an RoE rbMap. The bytes will be byte-swapped,
                                                                 and the [RBMAP_BYTES] will be zero-padded.

                                                                 Feature not implemented in a meaningful way for t95 pass 1, so making
                                                                 this reserved. */
#else /* Word 0 - Little Endian */
        uint64_t rbmap_bytes           : 8;  /**< [  7:  0](R/W) Reserved.
                                                                 Internal:
                                                                 When RFOE()_AB()_SLOT()_CONFIGURATION[PKT_MODE]=1, interpret the
                                                                 first [RBMAP_BYTES] as an RoE rbMap. The bytes will be byte-swapped,
                                                                 and the [RBMAP_BYTES] will be zero-padded.

                                                                 Feature not implemented in a meaningful way for t95 pass 1, so making
                                                                 this reserved. */
        uint64_t pkt_len               : 16; /**< [ 23:  8](R/W) The packet length.
                                                                 * When [PKT_MODE]=0x0, the number of bytes to read from the memory.

                                                                 * When [PKT_MODE]=0x1 or 0x2, the number of samples to read from
                                                                 memory. Samples in memory are always 32 bits, with 16-bit I and
                                                                 16-bit Q components. In this case, [PKT_LEN] must be a multiple of 4. */
        uint64_t hdr_len               : 8;  /**< [ 31: 24](R/W) Header length in number of bytes. When [PKT_MODE]=0x2, indicates the number of header bytes
                                                                 contained in the read DMA data. */
        uint64_t presentation_time_offset : 29;/**< [ 60: 32](R/W) Presentation time offset is used when RFOE()_AB()_SLOT()_CONFIGURATION[ORDERINFOTYPE]=1.
                                                                 Presentation time offset is added to value of current timebus.tod and the resultant value
                                                                 sent out in the RoE header.

                                                                 _ Bits [60:37] indicate integer nanoseconds.

                                                                 _ Bits [36:32] indicate fractional nanoseconds.

                                                                 See IEEE P1914.3/D3. */
        uint64_t reserved_61_63        : 3;
#endif /* Word 0 - End */
    } cnf95xxp1;
    struct bdk_rfoex_abx_slotx_configuration1_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t sof_mode              : 2;  /**< [ 63: 62](R/W) SOF bit setting in the Orderinfo Timestamp.
                                                                 This is used when RFOE()_AB()_SLOT()_CONFIGURATION[ORDERINFOTYPE]=1 and
                                                                 RFOE()_AB()_SLOT()_CONFIGURATION[ORDERINFO_INSERT]=1.
                                                                 0x0 = Sample SoF from the timer bus from PSM.
                                                                 0x1 = Sets SoF=0 in the orderInfo timestamp field.
                                                                 0x2 = Reserved.
                                                                 0x3 = Sets SoF=1 in the orderInfo timestamp field. */
        uint64_t reserved_61           : 1;
        uint64_t presentation_time_offset : 29;/**< [ 60: 32](R/W) Presentation time offset is used when RFOE()_AB()_SLOT()_CONFIGURATION[ORDERINFOTYPE]=1.
                                                                 Presentation time offset is added to value of current timebus.tod and the resultant value
                                                                 sent out in the RoE header.

                                                                 _ Bits [60:37] indicate integer nanoseconds.

                                                                 _ Bits [36:32] indicate fractional nanoseconds.

                                                                 See IEEE P1914.3/D3. */
        uint64_t hdr_len               : 8;  /**< [ 31: 24](R/W) Header length in number of bytes. When [PKT_MODE]=0x2, indicates the number of header bytes
                                                                 contained in the read DMA data. */
        uint64_t pkt_len               : 16; /**< [ 23:  8](R/W) The packet length.
                                                                 * When [PKT_MODE]=0x0, the number of bytes to read from the memory.

                                                                 * When [PKT_MODE]=0x1 or 0x2, the number of samples to read from
                                                                 memory. Samples in memory are always 32 bits, with 16-bit I and
                                                                 16-bit Q components. In this case, [PKT_LEN] must be a multiple of 4. */
        uint64_t rbmap_bytes           : 8;  /**< [  7:  0](R/W) When RFOE()_AB()_SLOT()_CONFIGURATION[PKT_MODE]=1, read the
                                                                 [RBMAP_BYTES] from the read DMA, and insert as-is, and then
                                                                 read sample data at the next 128-bit boundary. */
#else /* Word 0 - Little Endian */
        uint64_t rbmap_bytes           : 8;  /**< [  7:  0](R/W) When RFOE()_AB()_SLOT()_CONFIGURATION[PKT_MODE]=1, read the
                                                                 [RBMAP_BYTES] from the read DMA, and insert as-is, and then
                                                                 read sample data at the next 128-bit boundary. */
        uint64_t pkt_len               : 16; /**< [ 23:  8](R/W) The packet length.
                                                                 * When [PKT_MODE]=0x0, the number of bytes to read from the memory.

                                                                 * When [PKT_MODE]=0x1 or 0x2, the number of samples to read from
                                                                 memory. Samples in memory are always 32 bits, with 16-bit I and
                                                                 16-bit Q components. In this case, [PKT_LEN] must be a multiple of 4. */
        uint64_t hdr_len               : 8;  /**< [ 31: 24](R/W) Header length in number of bytes. When [PKT_MODE]=0x2, indicates the number of header bytes
                                                                 contained in the read DMA data. */
        uint64_t presentation_time_offset : 29;/**< [ 60: 32](R/W) Presentation time offset is used when RFOE()_AB()_SLOT()_CONFIGURATION[ORDERINFOTYPE]=1.
                                                                 Presentation time offset is added to value of current timebus.tod and the resultant value
                                                                 sent out in the RoE header.

                                                                 _ Bits [60:37] indicate integer nanoseconds.

                                                                 _ Bits [36:32] indicate fractional nanoseconds.

                                                                 See IEEE P1914.3/D3. */
        uint64_t reserved_61           : 1;
        uint64_t sof_mode              : 2;  /**< [ 63: 62](R/W) SOF bit setting in the Orderinfo Timestamp.
                                                                 This is used when RFOE()_AB()_SLOT()_CONFIGURATION[ORDERINFOTYPE]=1 and
                                                                 RFOE()_AB()_SLOT()_CONFIGURATION[ORDERINFO_INSERT]=1.
                                                                 0x0 = Sample SoF from the timer bus from PSM.
                                                                 0x1 = Sets SoF=0 in the orderInfo timestamp field.
                                                                 0x2 = Reserved.
                                                                 0x3 = Sets SoF=1 in the orderInfo timestamp field. */
#endif /* Word 0 - End */
    } cnf95xxp2;
};
typedef union bdk_rfoex_abx_slotx_configuration1 bdk_rfoex_abx_slotx_configuration1_t;

static inline uint64_t BDK_RFOEX_ABX_SLOTX_CONFIGURATION1(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_ABX_SLOTX_CONFIGURATION1(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=1) && (c<=2)))
        return 0x87e043d02008ll + 0x80000ll * ((a) & 0x1) + 0x8000ll * ((b) & 0x1) + 0x2000ll * ((c) & 0x3);
    __bdk_csr_fatal("RFOEX_ABX_SLOTX_CONFIGURATION1", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_RFOEX_ABX_SLOTX_CONFIGURATION1(a,b,c) bdk_rfoex_abx_slotx_configuration1_t
#define bustype_BDK_RFOEX_ABX_SLOTX_CONFIGURATION1(a,b,c) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_ABX_SLOTX_CONFIGURATION1(a,b,c) "RFOEX_ABX_SLOTX_CONFIGURATION1"
#define busnum_BDK_RFOEX_ABX_SLOTX_CONFIGURATION1(a,b,c) (a)
#define arguments_BDK_RFOEX_ABX_SLOTX_CONFIGURATION1(a,b,c) (a),(b),(c),-1

/**
 * Register (RSL) rfoe#_active_pc
 *
 * RFOE Active PC  Register
 * This register counts the conditional clocks for power management.
 */
union bdk_rfoex_active_pc
{
    uint64_t u;
    struct bdk_rfoex_active_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Count of conditional clock cycles since reset. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Count of conditional clock cycles since reset. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_active_pc_s cn; */
};
typedef union bdk_rfoex_active_pc bdk_rfoex_active_pc_t;

static inline uint64_t BDK_RFOEX_ACTIVE_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_ACTIVE_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01100ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_ACTIVE_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_ACTIVE_PC(a) bdk_rfoex_active_pc_t
#define bustype_BDK_RFOEX_ACTIVE_PC(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_ACTIVE_PC(a) "RFOEX_ACTIVE_PC"
#define busnum_BDK_RFOEX_ACTIVE_PC(a) (a)
#define arguments_BDK_RFOEX_ACTIVE_PC(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_eco
 *
 * INTERNAL: RFOE ECO Register
 */
union bdk_rfoex_eco
{
    uint64_t u;
    struct bdk_rfoex_eco_s
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
    /* struct bdk_rfoex_eco_s cn; */
};
typedef union bdk_rfoex_eco bdk_rfoex_eco_t;

static inline uint64_t BDK_RFOEX_ECO(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_ECO(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d008f0ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_ECO", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_ECO(a) bdk_rfoex_eco_t
#define bustype_BDK_RFOEX_ECO(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_ECO(a) "RFOEX_ECO"
#define busnum_BDK_RFOEX_ECO(a) (a)
#define arguments_BDK_RFOEX_ECO(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_apert_ddr_max
 *
 * RFOE RX Aperture DDR Maximum Register
 * Maximum IOVA for DMA of RX packets.
 */
union bdk_rfoex_rx_apert_ddr_max
{
    uint64_t u;
    struct bdk_rfoex_rx_apert_ddr_max_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 53; /**< [ 52:  0](R/W) Highest allowed IOVA for DMA of RX packets. If
                                                                 RFOE()_RX_APERT_DDR_MAX_ENA[ENABLE]=1, then DMA to LLC/DRAM is only allowed
                                                                 to IOVAs less than or equal to [ADDR]. Must be aligned to end of cache line--
                                                                 bottom seven bits ADDR\<6:0\> must be 0x7F. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 53; /**< [ 52:  0](R/W) Highest allowed IOVA for DMA of RX packets. If
                                                                 RFOE()_RX_APERT_DDR_MAX_ENA[ENABLE]=1, then DMA to LLC/DRAM is only allowed
                                                                 to IOVAs less than or equal to [ADDR]. Must be aligned to end of cache line--
                                                                 bottom seven bits ADDR\<6:0\> must be 0x7F. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_apert_ddr_max_s cn; */
};
typedef union bdk_rfoex_rx_apert_ddr_max bdk_rfoex_rx_apert_ddr_max_t;

static inline uint64_t BDK_RFOEX_RX_APERT_DDR_MAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_APERT_DDR_MAX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01838ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_APERT_DDR_MAX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_APERT_DDR_MAX(a) bdk_rfoex_rx_apert_ddr_max_t
#define bustype_BDK_RFOEX_RX_APERT_DDR_MAX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_APERT_DDR_MAX(a) "RFOEX_RX_APERT_DDR_MAX"
#define busnum_BDK_RFOEX_RX_APERT_DDR_MAX(a) (a)
#define arguments_BDK_RFOEX_RX_APERT_DDR_MAX(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_apert_ddr_max_ena
 *
 * RFOE RX Aperture LLC/DRAM Maximum Address Enable Register
 * Enable LLC/DRAM maximum aperture check.
 */
union bdk_rfoex_rx_apert_ddr_max_ena
{
    uint64_t u;
    struct bdk_rfoex_rx_apert_ddr_max_ena_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 1;  /**< [ 63: 63](R/W) Enable LLC/DRAM maximum aperture check. */
        uint64_t reserved_0_62         : 63;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_62         : 63;
        uint64_t enable                : 1;  /**< [ 63: 63](R/W) Enable LLC/DRAM maximum aperture check. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_apert_ddr_max_ena_s cn; */
};
typedef union bdk_rfoex_rx_apert_ddr_max_ena bdk_rfoex_rx_apert_ddr_max_ena_t;

static inline uint64_t BDK_RFOEX_RX_APERT_DDR_MAX_ENA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_APERT_DDR_MAX_ENA(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01858ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_APERT_DDR_MAX_ENA", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_APERT_DDR_MAX_ENA(a) bdk_rfoex_rx_apert_ddr_max_ena_t
#define bustype_BDK_RFOEX_RX_APERT_DDR_MAX_ENA(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_APERT_DDR_MAX_ENA(a) "RFOEX_RX_APERT_DDR_MAX_ENA"
#define busnum_BDK_RFOEX_RX_APERT_DDR_MAX_ENA(a) (a)
#define arguments_BDK_RFOEX_RX_APERT_DDR_MAX_ENA(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_apert_ddr_min
 *
 * RFOE RX Aperture LLC/DRAM Minimum Address Register
 * Minimum IOVA for DMA of RX packets.
 */
union bdk_rfoex_rx_apert_ddr_min
{
    uint64_t u;
    struct bdk_rfoex_rx_apert_ddr_min_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 53; /**< [ 52:  0](R/W) Lowest allowed IOVA for DMA of RX packets. If
                                                                 RFOE()_RX_APERT_DDR_MIN_ENA[ENABLE]=1, then DMA to LLC/DRAM
                                                                 is only allowed to IOVAs greater than or equal to [ADDR]. Must be 128-bit
                                                                 aligned. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 53; /**< [ 52:  0](R/W) Lowest allowed IOVA for DMA of RX packets. If
                                                                 RFOE()_RX_APERT_DDR_MIN_ENA[ENABLE]=1, then DMA to LLC/DRAM
                                                                 is only allowed to IOVAs greater than or equal to [ADDR]. Must be 128-bit
                                                                 aligned. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_apert_ddr_min_s cn; */
};
typedef union bdk_rfoex_rx_apert_ddr_min bdk_rfoex_rx_apert_ddr_min_t;

static inline uint64_t BDK_RFOEX_RX_APERT_DDR_MIN(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_APERT_DDR_MIN(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01830ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_APERT_DDR_MIN", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_APERT_DDR_MIN(a) bdk_rfoex_rx_apert_ddr_min_t
#define bustype_BDK_RFOEX_RX_APERT_DDR_MIN(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_APERT_DDR_MIN(a) "RFOEX_RX_APERT_DDR_MIN"
#define busnum_BDK_RFOEX_RX_APERT_DDR_MIN(a) (a)
#define arguments_BDK_RFOEX_RX_APERT_DDR_MIN(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_apert_ddr_min_ena
 *
 * RFOE RX Aperture LLC/DRAM Minimum Address Enable Register
 * Enable LLC/DRAM minimum aperture check.
 */
union bdk_rfoex_rx_apert_ddr_min_ena
{
    uint64_t u;
    struct bdk_rfoex_rx_apert_ddr_min_ena_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 1;  /**< [ 63: 63](R/W) Enable LLC/DRAM minimum aperture check. */
        uint64_t reserved_0_62         : 63;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_62         : 63;
        uint64_t enable                : 1;  /**< [ 63: 63](R/W) Enable LLC/DRAM minimum aperture check. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_apert_ddr_min_ena_s cn; */
};
typedef union bdk_rfoex_rx_apert_ddr_min_ena bdk_rfoex_rx_apert_ddr_min_ena_t;

static inline uint64_t BDK_RFOEX_RX_APERT_DDR_MIN_ENA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_APERT_DDR_MIN_ENA(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01850ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_APERT_DDR_MIN_ENA", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_APERT_DDR_MIN_ENA(a) bdk_rfoex_rx_apert_ddr_min_ena_t
#define bustype_BDK_RFOEX_RX_APERT_DDR_MIN_ENA(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_APERT_DDR_MIN_ENA(a) "RFOEX_RX_APERT_DDR_MIN_ENA"
#define busnum_BDK_RFOEX_RX_APERT_DDR_MIN_ENA(a) (a)
#define arguments_BDK_RFOEX_RX_APERT_DDR_MIN_ENA(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_apert_smem_max
 *
 * RFOE RX Aperture SMEM Maximum Address Register
 * Maximum address for SMEM DMA of RX packets.
 */
union bdk_rfoex_rx_apert_smem_max
{
    uint64_t u;
    struct bdk_rfoex_rx_apert_smem_max_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_25_63        : 39;
        uint64_t addr                  : 25; /**< [ 24:  0](R/W) Highest allowed SMEM byte address for DMA of RX packets. If
                                                                 RFOE()_RX_APERT_SMEM_MAX_ENA[ENABLE]=1, then DMA to SMEM must have
                                                                 an address less than or equal to [ADDR]. The bottom four bits
                                                                 ADDR\<3:0\> must be 0xF. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 25; /**< [ 24:  0](R/W) Highest allowed SMEM byte address for DMA of RX packets. If
                                                                 RFOE()_RX_APERT_SMEM_MAX_ENA[ENABLE]=1, then DMA to SMEM must have
                                                                 an address less than or equal to [ADDR]. The bottom four bits
                                                                 ADDR\<3:0\> must be 0xF. */
        uint64_t reserved_25_63        : 39;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_apert_smem_max_s cn; */
};
typedef union bdk_rfoex_rx_apert_smem_max bdk_rfoex_rx_apert_smem_max_t;

static inline uint64_t BDK_RFOEX_RX_APERT_SMEM_MAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_APERT_SMEM_MAX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01828ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_APERT_SMEM_MAX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_APERT_SMEM_MAX(a) bdk_rfoex_rx_apert_smem_max_t
#define bustype_BDK_RFOEX_RX_APERT_SMEM_MAX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_APERT_SMEM_MAX(a) "RFOEX_RX_APERT_SMEM_MAX"
#define busnum_BDK_RFOEX_RX_APERT_SMEM_MAX(a) (a)
#define arguments_BDK_RFOEX_RX_APERT_SMEM_MAX(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_apert_smem_max_ena
 *
 * RFOE RX Aperture SMEM Maximum Address Enable Register
 * Enable SMEM maximum aperture check.
 */
union bdk_rfoex_rx_apert_smem_max_ena
{
    uint64_t u;
    struct bdk_rfoex_rx_apert_smem_max_ena_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 1;  /**< [ 63: 63](R/W) Enable SMEM maximum aperture check. */
        uint64_t reserved_0_62         : 63;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_62         : 63;
        uint64_t enable                : 1;  /**< [ 63: 63](R/W) Enable SMEM maximum aperture check. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_apert_smem_max_ena_s cn; */
};
typedef union bdk_rfoex_rx_apert_smem_max_ena bdk_rfoex_rx_apert_smem_max_ena_t;

static inline uint64_t BDK_RFOEX_RX_APERT_SMEM_MAX_ENA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_APERT_SMEM_MAX_ENA(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01848ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_APERT_SMEM_MAX_ENA", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_APERT_SMEM_MAX_ENA(a) bdk_rfoex_rx_apert_smem_max_ena_t
#define bustype_BDK_RFOEX_RX_APERT_SMEM_MAX_ENA(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_APERT_SMEM_MAX_ENA(a) "RFOEX_RX_APERT_SMEM_MAX_ENA"
#define busnum_BDK_RFOEX_RX_APERT_SMEM_MAX_ENA(a) (a)
#define arguments_BDK_RFOEX_RX_APERT_SMEM_MAX_ENA(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_apert_smem_min
 *
 * RFOE RX Aperture SMEM Minimum Address Register
 * Minimum address for SMEM DMA of RX packets.
 */
union bdk_rfoex_rx_apert_smem_min
{
    uint64_t u;
    struct bdk_rfoex_rx_apert_smem_min_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_25_63        : 39;
        uint64_t addr                  : 25; /**< [ 24:  0](R/W) Lowest allowed SMEM byte address for DMA of RX packets. If
                                                                 RFOE()_RX_APERT_SMEM_MIN_ENA[ENABLE]=1, then DMA to SMEM must have
                                                                 an address greater than or equal to [ADDR]. Must be 128-bit
                                                                 aligned. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 25; /**< [ 24:  0](R/W) Lowest allowed SMEM byte address for DMA of RX packets. If
                                                                 RFOE()_RX_APERT_SMEM_MIN_ENA[ENABLE]=1, then DMA to SMEM must have
                                                                 an address greater than or equal to [ADDR]. Must be 128-bit
                                                                 aligned. */
        uint64_t reserved_25_63        : 39;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_apert_smem_min_s cn; */
};
typedef union bdk_rfoex_rx_apert_smem_min bdk_rfoex_rx_apert_smem_min_t;

static inline uint64_t BDK_RFOEX_RX_APERT_SMEM_MIN(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_APERT_SMEM_MIN(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01820ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_APERT_SMEM_MIN", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_APERT_SMEM_MIN(a) bdk_rfoex_rx_apert_smem_min_t
#define bustype_BDK_RFOEX_RX_APERT_SMEM_MIN(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_APERT_SMEM_MIN(a) "RFOEX_RX_APERT_SMEM_MIN"
#define busnum_BDK_RFOEX_RX_APERT_SMEM_MIN(a) (a)
#define arguments_BDK_RFOEX_RX_APERT_SMEM_MIN(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_apert_smem_min_ena
 *
 * RFOE RX Aperture SMEM Minimum Address Enable Register
 * Enable minimum SMEM aperture check.
 */
union bdk_rfoex_rx_apert_smem_min_ena
{
    uint64_t u;
    struct bdk_rfoex_rx_apert_smem_min_ena_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 1;  /**< [ 63: 63](R/W) Enable SMEM minimum aperture check. */
        uint64_t reserved_0_62         : 63;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_62         : 63;
        uint64_t enable                : 1;  /**< [ 63: 63](R/W) Enable SMEM minimum aperture check. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_apert_smem_min_ena_s cn; */
};
typedef union bdk_rfoex_rx_apert_smem_min_ena bdk_rfoex_rx_apert_smem_min_ena_t;

static inline uint64_t BDK_RFOEX_RX_APERT_SMEM_MIN_ENA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_APERT_SMEM_MIN_ENA(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01840ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_APERT_SMEM_MIN_ENA", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_APERT_SMEM_MIN_ENA(a) bdk_rfoex_rx_apert_smem_min_ena_t
#define bustype_BDK_RFOEX_RX_APERT_SMEM_MIN_ENA(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_APERT_SMEM_MIN_ENA(a) "RFOEX_RX_APERT_SMEM_MIN_ENA"
#define busnum_BDK_RFOEX_RX_APERT_SMEM_MIN_ENA(a) (a)
#define arguments_BDK_RFOEX_RX_APERT_SMEM_MIN_ENA(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_cfg
 *
 * RFOE_RX General Configuration Register
 * General receive configuration.
 */
union bdk_rfoex_rx_cfg
{
    uint64_t u;
    struct bdk_rfoex_rx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_21_63        : 43;
        uint64_t logger_hp             : 1;  /**< [ 20: 20](R/W) Logger writes are sent with high priority. */
        uint64_t wr_hp                 : 4;  /**< [ 19: 16](R/W) Write priority. One bit per LMAC. If a bit is set, writes associated
                                                                 with the given LMAC are marked high priority. Otherwise writes are
                                                                 low-priority. Does not apply to logger writes. */
        uint64_t reserved_3_15         : 13;
        uint64_t calibrate_x2p         : 1;  /**< [  2:  2](R/W) Calibrate X2P bus. Writing this bit from zero to one starts a calibration cycle.
                                                                 Software may then monitor the RFOE()_RX_STATUS[CALIBRATE_DONE] bit for completion,
                                                                 and clear this bit.
                                                                 * Initialization sequence must calibrate X2P.
                                                                 * Must calibrate only during post-reset initialization sequence while
                                                                 RFOE_RX_CTRL[DATA_PKT_RX_EN]==0.
                                                                 * Must be 0 when RFOE_RX_CTRL[DATA_PKT_RX_EN]==1.

                                                                 Internal:
                                                                 Calibration defines the x2p grant to response latency.  Response latency is determined
                                                                 by CGX latency, which is a fixed value--it never changes. */
        uint64_t force_intf_clk_en     : 1;  /**< [  1:  1](R/W) Force the conditional clocks on interface signals between blocks. For diagnostic use only. */
        uint64_t force_cond_clk_en     : 1;  /**< [  0:  0](R/W) Force the conditional clocks active within the block. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t force_cond_clk_en     : 1;  /**< [  0:  0](R/W) Force the conditional clocks active within the block. For diagnostic use only. */
        uint64_t force_intf_clk_en     : 1;  /**< [  1:  1](R/W) Force the conditional clocks on interface signals between blocks. For diagnostic use only. */
        uint64_t calibrate_x2p         : 1;  /**< [  2:  2](R/W) Calibrate X2P bus. Writing this bit from zero to one starts a calibration cycle.
                                                                 Software may then monitor the RFOE()_RX_STATUS[CALIBRATE_DONE] bit for completion,
                                                                 and clear this bit.
                                                                 * Initialization sequence must calibrate X2P.
                                                                 * Must calibrate only during post-reset initialization sequence while
                                                                 RFOE_RX_CTRL[DATA_PKT_RX_EN]==0.
                                                                 * Must be 0 when RFOE_RX_CTRL[DATA_PKT_RX_EN]==1.

                                                                 Internal:
                                                                 Calibration defines the x2p grant to response latency.  Response latency is determined
                                                                 by CGX latency, which is a fixed value--it never changes. */
        uint64_t reserved_3_15         : 13;
        uint64_t wr_hp                 : 4;  /**< [ 19: 16](R/W) Write priority. One bit per LMAC. If a bit is set, writes associated
                                                                 with the given LMAC are marked high priority. Otherwise writes are
                                                                 low-priority. Does not apply to logger writes. */
        uint64_t logger_hp             : 1;  /**< [ 20: 20](R/W) Logger writes are sent with high priority. */
        uint64_t reserved_21_63        : 43;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_cfg_s cn9; */
    /* struct bdk_rfoex_rx_cfg_s cnf95xxp1; */
    struct bdk_rfoex_rx_cfg_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_21_63        : 43;
        uint64_t logger_hp             : 1;  /**< [ 20: 20](R/W) Logger writes are sent with high priority. */
        uint64_t wr_hp                 : 4;  /**< [ 19: 16](R/W) Write priority. One bit per LMAC. If a bit is set, writes associated
                                                                 with the given LMAC are marked high priority. Otherwise writes are
                                                                 low-priority. Does not apply to logger writes. */
        uint64_t reserved_3_15         : 13;
        uint64_t calibrate_x2p         : 1;  /**< [  2:  2](R/W) Calibrate X2P bus. Writing this bit from zero to one starts a calibration cycle.
                                                                 Software may then monitor the RFOE()_RX_STATUS[CALIBRATE_DONE] bit for completion,
                                                                 and clear this bit.
                                                                 * Initialization sequence must calibrate X2P.
                                                                 * Must calibrate only during post-reset initialization sequence while
                                                                 RFOE()_RX_CTRL[DATA_PKT_RX_EN]==0.
                                                                 * Must be 0 when RFOE()_RX_CTRL[DATA_PKT_RX_EN]==1.

                                                                 Internal:
                                                                 Calibration defines the x2p grant to response latency.  Response latency is determined
                                                                 by CGX latency, which is a fixed value--it never changes. */
        uint64_t force_intf_clk_en     : 1;  /**< [  1:  1](R/W) Force the conditional clocks on interface signals between blocks. For diagnostic use only. */
        uint64_t force_cond_clk_en     : 1;  /**< [  0:  0](R/W) Force the conditional clocks active within the block. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t force_cond_clk_en     : 1;  /**< [  0:  0](R/W) Force the conditional clocks active within the block. For diagnostic use only. */
        uint64_t force_intf_clk_en     : 1;  /**< [  1:  1](R/W) Force the conditional clocks on interface signals between blocks. For diagnostic use only. */
        uint64_t calibrate_x2p         : 1;  /**< [  2:  2](R/W) Calibrate X2P bus. Writing this bit from zero to one starts a calibration cycle.
                                                                 Software may then monitor the RFOE()_RX_STATUS[CALIBRATE_DONE] bit for completion,
                                                                 and clear this bit.
                                                                 * Initialization sequence must calibrate X2P.
                                                                 * Must calibrate only during post-reset initialization sequence while
                                                                 RFOE()_RX_CTRL[DATA_PKT_RX_EN]==0.
                                                                 * Must be 0 when RFOE()_RX_CTRL[DATA_PKT_RX_EN]==1.

                                                                 Internal:
                                                                 Calibration defines the x2p grant to response latency.  Response latency is determined
                                                                 by CGX latency, which is a fixed value--it never changes. */
        uint64_t reserved_3_15         : 13;
        uint64_t wr_hp                 : 4;  /**< [ 19: 16](R/W) Write priority. One bit per LMAC. If a bit is set, writes associated
                                                                 with the given LMAC are marked high priority. Otherwise writes are
                                                                 low-priority. Does not apply to logger writes. */
        uint64_t logger_hp             : 1;  /**< [ 20: 20](R/W) Logger writes are sent with high priority. */
        uint64_t reserved_21_63        : 43;
#endif /* Word 0 - End */
    } cnf95xxp2;
};
typedef union bdk_rfoex_rx_cfg bdk_rfoex_rx_cfg_t;

static inline uint64_t BDK_RFOEX_RX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01008ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_CFG(a) bdk_rfoex_rx_cfg_t
#define bustype_BDK_RFOEX_RX_CFG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_CFG(a) "RFOEX_RX_CFG"
#define busnum_BDK_RFOEX_RX_CFG(a) (a)
#define arguments_BDK_RFOEX_RX_CFG(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_cgx_octs_stat#
 *
 * RFOE RX Received Byte Statistic Register
 * Number of octets received from CGX on enabled interface
 * (RFOE()_RX_CTRL[DATA_PKT_RX_EN]=1). Per LMAC.
 *
 * Internal:
 * Bytes received on x2p pkt_bus interface:
 * input x2p2_p2x2_defs::x2p2_bus_t cgx__rfoe_x2p_pkt_bus).
 * Normally 16B per transfer.
 * On EOP can have less.  EOP byte count determined by x2p bval field.
 * Does not include bytes shunted by RFOE()_RX_CTRL[DATA_PKT_RX_EN] = 0.
 */
union bdk_rfoex_rx_cgx_octs_statx
{
    uint64_t u;
    struct bdk_rfoex_rx_cgx_octs_statx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) Number of octets received from CGX. Wraps to zero at 2^48.
                                                                 Excludes RFOE()_RX_ERROR_INT[MALFORMED_X2P_PKT] bytes.
                                                                 Excludes bytes received when RX is disabled by RFOE()_RX_CTRL[DATA_PKT_RX_EN]=0. */
#else /* Word 0 - Little Endian */
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) Number of octets received from CGX. Wraps to zero at 2^48.
                                                                 Excludes RFOE()_RX_ERROR_INT[MALFORMED_X2P_PKT] bytes.
                                                                 Excludes bytes received when RX is disabled by RFOE()_RX_CTRL[DATA_PKT_RX_EN]=0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_cgx_octs_statx_s cn; */
};
typedef union bdk_rfoex_rx_cgx_octs_statx bdk_rfoex_rx_cgx_octs_statx_t;

static inline uint64_t BDK_RFOEX_RX_CGX_OCTS_STATX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_CGX_OCTS_STATX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=3)))
        return 0x87e043d01de0ll + 0x80000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    __bdk_csr_fatal("RFOEX_RX_CGX_OCTS_STATX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_CGX_OCTS_STATX(a,b) bdk_rfoex_rx_cgx_octs_statx_t
#define bustype_BDK_RFOEX_RX_CGX_OCTS_STATX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_CGX_OCTS_STATX(a,b) "RFOEX_RX_CGX_OCTS_STATX"
#define busnum_BDK_RFOEX_RX_CGX_OCTS_STATX(a,b) (a)
#define arguments_BDK_RFOEX_RX_CGX_OCTS_STATX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_rx_cgx_pkt_stat#
 *
 * RFOE RX  Packet Received  Count Statistic Register
 * Number of packets received from MAC on enabled interface
 * (RFOE()_RX_CTRL[DATA_PKT_RX_EN]=1). One for each source LMAC.
 *
 * Internal:
 * Packets received on x2p pkt_bus interface:
 *   input x2p2_p2x2_defs::x2p2_bus_t cgx__rfoe_x2p_pkt_bus.
 * Does not include packets shunted by RFOE()_RX_CTRL[DATA_PKT_RX_EN] = 0.
 */
union bdk_rfoex_rx_cgx_pkt_statx
{
    uint64_t u;
    struct bdk_rfoex_rx_cgx_pkt_statx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) The counter value, increments on EOP transfers. Wraps to zero at 2^48.
                                                                 Excludes  RFOE()_RX_ERROR_INT[MALFORMED_X2P_PKT] packets.
                                                                 Excludes packets received when RX is disabled by RFOE()_RX_CTRL[DATA_PKT_RX_EN]=0 . */
#else /* Word 0 - Little Endian */
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) The counter value, increments on EOP transfers. Wraps to zero at 2^48.
                                                                 Excludes  RFOE()_RX_ERROR_INT[MALFORMED_X2P_PKT] packets.
                                                                 Excludes packets received when RX is disabled by RFOE()_RX_CTRL[DATA_PKT_RX_EN]=0 . */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_cgx_pkt_statx_s cn; */
};
typedef union bdk_rfoex_rx_cgx_pkt_statx bdk_rfoex_rx_cgx_pkt_statx_t;

static inline uint64_t BDK_RFOEX_RX_CGX_PKT_STATX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_CGX_PKT_STATX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=3)))
        return 0x87e043d01dc0ll + 0x80000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    __bdk_csr_fatal("RFOEX_RX_CGX_PKT_STATX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_CGX_PKT_STATX(a,b) bdk_rfoex_rx_cgx_pkt_statx_t
#define bustype_BDK_RFOEX_RX_CGX_PKT_STATX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_CGX_PKT_STATX(a,b) "RFOEX_RX_CGX_PKT_STATX"
#define busnum_BDK_RFOEX_RX_CGX_PKT_STATX(a,b) (a)
#define arguments_BDK_RFOEX_RX_CGX_PKT_STATX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_rx_cgxif_bp_test
 *
 * INTERNAL: RFOE RX  CGXIF Back Pressure Test Register
 *
 * Internal:
 * Turns off x2p grand when generating back pressure.
 */
union bdk_rfoex_rx_cgxif_bp_test
{
    uint64_t u;
    struct bdk_rfoex_rx_cgxif_bp_test_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 Prevents arb from granting.
                                                                 \<63\> = lmac3
                                                                 \<62\> = lmac2
                                                                 \<61\> = lmac1
                                                                 \<60\> = lmac0 */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                 \<23:22\> = lmac3
                                                                 \<21:20\> = lmac2
                                                                 \<19:18\> = lmac1
                                                                 \<17:16\> = lmac0 */
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
                                                                 \<23:22\> = lmac3
                                                                 \<21:20\> = lmac2
                                                                 \<19:18\> = lmac1
                                                                 \<17:16\> = lmac0 */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 Prevents arb from granting.
                                                                 \<63\> = lmac3
                                                                 \<62\> = lmac2
                                                                 \<61\> = lmac1
                                                                 \<60\> = lmac0 */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_cgxif_bp_test_s cn; */
};
typedef union bdk_rfoex_rx_cgxif_bp_test bdk_rfoex_rx_cgxif_bp_test_t;

static inline uint64_t BDK_RFOEX_RX_CGXIF_BP_TEST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_CGXIF_BP_TEST(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01f00ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_CGXIF_BP_TEST", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_CGXIF_BP_TEST(a) bdk_rfoex_rx_cgxif_bp_test_t
#define bustype_BDK_RFOEX_RX_CGXIF_BP_TEST(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_CGXIF_BP_TEST(a) "RFOEX_RX_CGXIF_BP_TEST"
#define busnum_BDK_RFOEX_RX_CGXIF_BP_TEST(a) (a)
#define arguments_BDK_RFOEX_RX_CGXIF_BP_TEST(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_ctrl
 *
 * RFOE RX Control Register
 * Control and status for doing BPHY/RFIF reset sequences.
 */
union bdk_rfoex_rx_ctrl
{
    uint64_t u;
    struct bdk_rfoex_rx_ctrl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t rx_idle               : 1;  /**< [  1:  1](RO/H) When [DATA_PKT_RX_EN] = 0, [RX_IDLE]=1 indicates no in-flight RX
                                                                 packets and any new RX packets will be discarded. [RX_IDLE] = 1
                                                                 indicates that it is safe to do a BPHY and/or RFIF reset.
                                                                 For the reset domains:
                                                                 * BPHY domain DMA can still be active, but a BPHY reset will reset all these transactions.
                                                                 * RFIF domain is discarding all traffic.
                                                                 * Once [RX_IDLE] is set, it will stay set until [DATA_PKT_RX_EN] is set by software.
                                                                 [RX_IDLE] should be ignored when [DATA_PKT_RX_EN] = 1. */
        uint64_t data_pkt_rx_en        : 1;  /**< [  0:  0](R/W) Enable RX traffic.  Software must write to 1 to enable RX traffic.

                                                                 When [DATA_PKT_RX_EN] transitions from 1 to 0, RFOE completes any
                                                                 in-flight RX packets. At the next packet boundary, RFOE will set
                                                                 [RX_IDLE] and begin discarding any subsequent packets.

                                                                 When [DATA_PKT_RX_EN] transitions from 0 to 1, RFOE will continue to
                                                                 discard any in-flight packets and begin normal reception at the next
                                                                 start-of-packet boundary from CGX. */
#else /* Word 0 - Little Endian */
        uint64_t data_pkt_rx_en        : 1;  /**< [  0:  0](R/W) Enable RX traffic.  Software must write to 1 to enable RX traffic.

                                                                 When [DATA_PKT_RX_EN] transitions from 1 to 0, RFOE completes any
                                                                 in-flight RX packets. At the next packet boundary, RFOE will set
                                                                 [RX_IDLE] and begin discarding any subsequent packets.

                                                                 When [DATA_PKT_RX_EN] transitions from 0 to 1, RFOE will continue to
                                                                 discard any in-flight packets and begin normal reception at the next
                                                                 start-of-packet boundary from CGX. */
        uint64_t rx_idle               : 1;  /**< [  1:  1](RO/H) When [DATA_PKT_RX_EN] = 0, [RX_IDLE]=1 indicates no in-flight RX
                                                                 packets and any new RX packets will be discarded. [RX_IDLE] = 1
                                                                 indicates that it is safe to do a BPHY and/or RFIF reset.
                                                                 For the reset domains:
                                                                 * BPHY domain DMA can still be active, but a BPHY reset will reset all these transactions.
                                                                 * RFIF domain is discarding all traffic.
                                                                 * Once [RX_IDLE] is set, it will stay set until [DATA_PKT_RX_EN] is set by software.
                                                                 [RX_IDLE] should be ignored when [DATA_PKT_RX_EN] = 1. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_ctrl_s cn; */
};
typedef union bdk_rfoex_rx_ctrl bdk_rfoex_rx_ctrl_t;

static inline uint64_t BDK_RFOEX_RX_CTRL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_CTRL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01018ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_CTRL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_CTRL(a) bdk_rfoex_rx_ctrl_t
#define bustype_BDK_RFOEX_RX_CTRL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_CTRL(a) "RFOEX_RX_CTRL"
#define busnum_BDK_RFOEX_RX_CTRL(a) (a)
#define arguments_BDK_RFOEX_RX_CTRL(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_direction_ctl#
 *
 * RFOE RX Direction Control Registers
 * These registers control how packets received from CGX are routed and processed.
 *
 * Incoming packets search for these registers in-order to find the first one
 * with a matching [ETHERTYPE] and [VALID] = 1. The first match determines how
 * the packet is routed.
 *
 * The last register ({b} = 3) determines the routing for any packet with no
 * other match. Packets that have no match in 0..2 are handled in a transparent
 * manner as defined by the configuration selected by RFOE()_RX_IND_FT()_CFG.
 */
union bdk_rfoex_rx_direction_ctlx
{
    uint64_t u;
    struct bdk_rfoex_rx_direction_ctlx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_29_63        : 35;
        uint64_t valid                 : 1;  /**< [ 28: 28](R/W) Entry is valid. If [VALID] = 0, the register is ignored, except for the
                                                                 last register ({b} = 3) which ignores this field. */
        uint64_t ethertype             : 16; /**< [ 27: 12](R/W) EtherType to match against incoming packet from CGX.
                                                                 * For the last register ({b} = 3) this field is a don't care and all
                                                                 EtherTypes match (if they haven't already matched one of the other
                                                                 registers). */
        uint64_t reserved_9_11         : 3;
        uint64_t dma_type              : 1;  /**< [  8:  8](R/W) Determines how RFOE process the packet.
                                                                 0 = Normal DMA Processing for RoE or Ethernet packets.
                                                                 1 = Custom Header Ingress (CHI).
                                                                 Ignored for {b} = 3. */
        uint64_t flowid                : 8;  /**< [  7:  0](R/W) FlowID for configuration lookup when processing non-RoE packets. Non-RoE:
                                                                 *[DMA_TYPE] = 1, or
                                                                 *When default entry 3 is selected (no EtherType match in {0},{1}, or P{2}.

                                                                 For RoE packets ([DMA_TYPE]=0), FlowID is extracted
                                                                 from RoE header. */
#else /* Word 0 - Little Endian */
        uint64_t flowid                : 8;  /**< [  7:  0](R/W) FlowID for configuration lookup when processing non-RoE packets. Non-RoE:
                                                                 *[DMA_TYPE] = 1, or
                                                                 *When default entry 3 is selected (no EtherType match in {0},{1}, or P{2}.

                                                                 For RoE packets ([DMA_TYPE]=0), FlowID is extracted
                                                                 from RoE header. */
        uint64_t dma_type              : 1;  /**< [  8:  8](R/W) Determines how RFOE process the packet.
                                                                 0 = Normal DMA Processing for RoE or Ethernet packets.
                                                                 1 = Custom Header Ingress (CHI).
                                                                 Ignored for {b} = 3. */
        uint64_t reserved_9_11         : 3;
        uint64_t ethertype             : 16; /**< [ 27: 12](R/W) EtherType to match against incoming packet from CGX.
                                                                 * For the last register ({b} = 3) this field is a don't care and all
                                                                 EtherTypes match (if they haven't already matched one of the other
                                                                 registers). */
        uint64_t valid                 : 1;  /**< [ 28: 28](R/W) Entry is valid. If [VALID] = 0, the register is ignored, except for the
                                                                 last register ({b} = 3) which ignores this field. */
        uint64_t reserved_29_63        : 35;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_direction_ctlx_s cn; */
};
typedef union bdk_rfoex_rx_direction_ctlx bdk_rfoex_rx_direction_ctlx_t;

static inline uint64_t BDK_RFOEX_RX_DIRECTION_CTLX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_DIRECTION_CTLX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=3)))
        return 0x87e043d01800ll + 0x80000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    __bdk_csr_fatal("RFOEX_RX_DIRECTION_CTLX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_DIRECTION_CTLX(a,b) bdk_rfoex_rx_direction_ctlx_t
#define bustype_BDK_RFOEX_RX_DIRECTION_CTLX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_DIRECTION_CTLX(a,b) "RFOEX_RX_DIRECTION_CTLX"
#define busnum_BDK_RFOEX_RX_DIRECTION_CTLX(a,b) (a)
#define arguments_BDK_RFOEX_RX_DIRECTION_CTLX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_rx_dma_complete_stat#
 *
 * RFOE RX  DMA Completion Statistic Register
 * Number of DMA commands completed, indicated by requesting to send a JCA. One for each source LMAC.
 * * 0xFD: All responses for all packets segments have been received, plus  PSW and JDW responses.
 * * Others: All responses for DMA have been received, plus PSW and JDW responses.
 *
 * Does not include packet logger request/responses.
 *
 * Does not count completions for RFOE()_RX_IND_JDT_CFG0[JCA_ENABLE]==0.
 */
union bdk_rfoex_rx_dma_complete_statx
{
    uint64_t u;
    struct bdk_rfoex_rx_dma_complete_statx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) The counter value. Wraps to zero at 2^48. */
#else /* Word 0 - Little Endian */
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) The counter value. Wraps to zero at 2^48. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_dma_complete_statx_s cn; */
};
typedef union bdk_rfoex_rx_dma_complete_statx bdk_rfoex_rx_dma_complete_statx_t;

static inline uint64_t BDK_RFOEX_RX_DMA_COMPLETE_STATX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_DMA_COMPLETE_STATX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=3)))
        return 0x87e043d01da0ll + 0x80000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    __bdk_csr_fatal("RFOEX_RX_DMA_COMPLETE_STATX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_DMA_COMPLETE_STATX(a,b) bdk_rfoex_rx_dma_complete_statx_t
#define bustype_BDK_RFOEX_RX_DMA_COMPLETE_STATX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_DMA_COMPLETE_STATX(a,b) "RFOEX_RX_DMA_COMPLETE_STATX"
#define busnum_BDK_RFOEX_RX_DMA_COMPLETE_STATX(a,b) (a)
#define arguments_BDK_RFOEX_RX_DMA_COMPLETE_STATX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_rx_dma_jca_bp_test
 *
 * INTERNAL: RFOE RX  DMA and JCA Back Pressure Test Register
 *
 * Internal:
 * Applies back pressure to JCA and DMA paths
 */
union bdk_rfoex_rx_dma_jca_bp_test
{
    uint64_t u;
    struct bdk_rfoex_rx_dma_jca_bp_test_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 Prevents arb from granting.
                                                                 \<63\> = Unused
                                                                 \<62\> = Unused
                                                                 \<61\> = tx_jca at RX-TX arbitration point to PSM. Holds request while BP is asserted
                                                                 \<60\> = rx jca at RX-TX arbitration point to PSM. Holds request while BP is asserted */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                 \<23:22\> = Unused
                                                                 \<21:20\> = Unused
                                                                 \<19:18\> = tx_jca at RX-TX arbitration point to PSM. Holds request while BP is asserted
                                                                 \<17:16\> = rx jca at RX-TX arbitration point to PSM. Holds request while BP is asserted */
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
                                                                 \<23:22\> = Unused
                                                                 \<21:20\> = Unused
                                                                 \<19:18\> = tx_jca at RX-TX arbitration point to PSM. Holds request while BP is asserted
                                                                 \<17:16\> = rx jca at RX-TX arbitration point to PSM. Holds request while BP is asserted */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 Prevents arb from granting.
                                                                 \<63\> = Unused
                                                                 \<62\> = Unused
                                                                 \<61\> = tx_jca at RX-TX arbitration point to PSM. Holds request while BP is asserted
                                                                 \<60\> = rx jca at RX-TX arbitration point to PSM. Holds request while BP is asserted */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_dma_jca_bp_test_s cn; */
};
typedef union bdk_rfoex_rx_dma_jca_bp_test bdk_rfoex_rx_dma_jca_bp_test_t;

static inline uint64_t BDK_RFOEX_RX_DMA_JCA_BP_TEST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_DMA_JCA_BP_TEST(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01f08ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_DMA_JCA_BP_TEST", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_DMA_JCA_BP_TEST(a) bdk_rfoex_rx_dma_jca_bp_test_t
#define bustype_BDK_RFOEX_RX_DMA_JCA_BP_TEST(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_DMA_JCA_BP_TEST(a) "RFOEX_RX_DMA_JCA_BP_TEST"
#define busnum_BDK_RFOEX_RX_DMA_JCA_BP_TEST(a) (a)
#define arguments_BDK_RFOEX_RX_DMA_JCA_BP_TEST(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_dma_octs_stat#
 *
 * RFOE RX Packet DMA Byte Statistic Register
 * Number of octets written to memory. Since RFOE DMA writes are always 16B, this
 * counter increments by 16 for every write. Counter wraps to zero at 2^48.
 * One counter per LMAC. Does not include packet logger bytes.
 * Includes all bytes from packet DMA, including PSW and JDW.  Since all writes are 128-bit aligned,
 * counts are always incremented by 16 bytes.
 */
union bdk_rfoex_rx_dma_octs_statx
{
    uint64_t u;
    struct bdk_rfoex_rx_dma_octs_statx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) Number of octets written. Wraps to zero at 2^48. */
#else /* Word 0 - Little Endian */
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) Number of octets written. Wraps to zero at 2^48. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_dma_octs_statx_s cn; */
};
typedef union bdk_rfoex_rx_dma_octs_statx bdk_rfoex_rx_dma_octs_statx_t;

static inline uint64_t BDK_RFOEX_RX_DMA_OCTS_STATX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_DMA_OCTS_STATX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=3)))
        return 0x87e043d01d80ll + 0x80000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    __bdk_csr_fatal("RFOEX_RX_DMA_OCTS_STATX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_DMA_OCTS_STATX(a,b) bdk_rfoex_rx_dma_octs_statx_t
#define bustype_BDK_RFOEX_RX_DMA_OCTS_STATX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_DMA_OCTS_STATX(a,b) "RFOEX_RX_DMA_OCTS_STATX"
#define busnum_BDK_RFOEX_RX_DMA_OCTS_STATX(a,b) (a)
#define arguments_BDK_RFOEX_RX_DMA_OCTS_STATX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_rx_dma_pkt_stat#
 *
 * RFOE RX Packet DMA Packet Count Statistic Register
 * Number of packets written to memory. One for each source LMAC.
 */
union bdk_rfoex_rx_dma_pkt_statx
{
    uint64_t u;
    struct bdk_rfoex_rx_dma_pkt_statx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) The counter value. Wraps to zero at 2^48. */
#else /* Word 0 - Little Endian */
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) The counter value. Wraps to zero at 2^48. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_dma_pkt_statx_s cn; */
};
typedef union bdk_rfoex_rx_dma_pkt_statx bdk_rfoex_rx_dma_pkt_statx_t;

static inline uint64_t BDK_RFOEX_RX_DMA_PKT_STATX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_DMA_PKT_STATX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=3)))
        return 0x87e043d01d60ll + 0x80000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    __bdk_csr_fatal("RFOEX_RX_DMA_PKT_STATX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_DMA_PKT_STATX(a,b) bdk_rfoex_rx_dma_pkt_statx_t
#define bustype_BDK_RFOEX_RX_DMA_PKT_STATX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_DMA_PKT_STATX(a,b) "RFOEX_RX_DMA_PKT_STATX"
#define busnum_BDK_RFOEX_RX_DMA_PKT_STATX(a,b) (a)
#define arguments_BDK_RFOEX_RX_DMA_PKT_STATX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_rx_error_ena_w1c
 *
 * RFOE OrderInfo Interrupt Error Message Enable Clear Registers
 * This register clears interrupt enable bits.
 */
union bdk_rfoex_rx_error_ena_w1c
{
    uint64_t u;
    struct bdk_rfoex_rx_error_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t wrrsp_nfat            : 1;  /**< [ 12: 12](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[WRRSP_NFAT].
                                                                 Internal:
                                                                 Should never occur. Including for completeness */
        uint64_t wrrsp_fat             : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[WRRSP_FAT]. */
        uint64_t fc_psm_opcode         : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[FC_PSM_OPCODE]. */
        uint64_t malformed_x2p_pkt     : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[MALFORMED_X2P_PKT]. */
        uint64_t reserved_8            : 1;
        uint64_t fd_malformed          : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[FD_MALFORMED]. */
        uint64_t fd_state              : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[FD_STATE]. */
        uint64_t nxm                   : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[NXM]. */
        uint64_t clean_aperture        : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[CLEAN_APERTURE]. */
        uint64_t dirty_aperture        : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[DIRTY_APERTURE]. */
        uint64_t buf_overflow          : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[BUF_OVERFLOW]. */
        uint64_t len_miscomp           : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[LEN_MISCOMP].
                                                                 Internal:
                                                                 RX Header processing expects \> 48B. */
        uint64_t len_abnorm            : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[LEN_ABNORM].
                                                                 Internal:
                                                                 RX Header processing expects \> 48B. P1914 note--  RoE payload must be \>= 64B. */
#else /* Word 0 - Little Endian */
        uint64_t len_abnorm            : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[LEN_ABNORM].
                                                                 Internal:
                                                                 RX Header processing expects \> 48B. P1914 note--  RoE payload must be \>= 64B. */
        uint64_t len_miscomp           : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[LEN_MISCOMP].
                                                                 Internal:
                                                                 RX Header processing expects \> 48B. */
        uint64_t buf_overflow          : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[BUF_OVERFLOW]. */
        uint64_t dirty_aperture        : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[DIRTY_APERTURE]. */
        uint64_t clean_aperture        : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[CLEAN_APERTURE]. */
        uint64_t nxm                   : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[NXM]. */
        uint64_t fd_state              : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[FD_STATE]. */
        uint64_t fd_malformed          : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[FD_MALFORMED]. */
        uint64_t reserved_8            : 1;
        uint64_t malformed_x2p_pkt     : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[MALFORMED_X2P_PKT]. */
        uint64_t fc_psm_opcode         : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[FC_PSM_OPCODE]. */
        uint64_t wrrsp_fat             : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[WRRSP_FAT]. */
        uint64_t wrrsp_nfat            : 1;  /**< [ 12: 12](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ERROR_INT[WRRSP_NFAT].
                                                                 Internal:
                                                                 Should never occur. Including for completeness */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_error_ena_w1c_s cn; */
};
typedef union bdk_rfoex_rx_error_ena_w1c bdk_rfoex_rx_error_ena_w1c_t;

static inline uint64_t BDK_RFOEX_RX_ERROR_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_ERROR_ENA_W1C(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01ea0ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_ERROR_ENA_W1C", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_ERROR_ENA_W1C(a) bdk_rfoex_rx_error_ena_w1c_t
#define bustype_BDK_RFOEX_RX_ERROR_ENA_W1C(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_ERROR_ENA_W1C(a) "RFOEX_RX_ERROR_ENA_W1C"
#define busnum_BDK_RFOEX_RX_ERROR_ENA_W1C(a) (a)
#define arguments_BDK_RFOEX_RX_ERROR_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_error_ena_w1s
 *
 * RFOE OrderInfo Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_rfoex_rx_error_ena_w1s
{
    uint64_t u;
    struct bdk_rfoex_rx_error_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t wrrsp_nfat            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[WRRSP_NFAT].
                                                                 Internal:
                                                                 Should never occur. Including for completeness */
        uint64_t wrrsp_fat             : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[WRRSP_FAT]. */
        uint64_t fc_psm_opcode         : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[FC_PSM_OPCODE]. */
        uint64_t malformed_x2p_pkt     : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[MALFORMED_X2P_PKT]. */
        uint64_t reserved_8            : 1;
        uint64_t fd_malformed          : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[FD_MALFORMED]. */
        uint64_t fd_state              : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[FD_STATE]. */
        uint64_t nxm                   : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[NXM]. */
        uint64_t clean_aperture        : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[CLEAN_APERTURE]. */
        uint64_t dirty_aperture        : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[DIRTY_APERTURE]. */
        uint64_t buf_overflow          : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[BUF_OVERFLOW]. */
        uint64_t len_miscomp           : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[LEN_MISCOMP].
                                                                 Internal:
                                                                 RX Header processing expects \> 48B. */
        uint64_t len_abnorm            : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[LEN_ABNORM].
                                                                 Internal:
                                                                 RX Header processing expects \> 48B. P1914 note--  RoE payload must be \>= 64B. */
#else /* Word 0 - Little Endian */
        uint64_t len_abnorm            : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[LEN_ABNORM].
                                                                 Internal:
                                                                 RX Header processing expects \> 48B. P1914 note--  RoE payload must be \>= 64B. */
        uint64_t len_miscomp           : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[LEN_MISCOMP].
                                                                 Internal:
                                                                 RX Header processing expects \> 48B. */
        uint64_t buf_overflow          : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[BUF_OVERFLOW]. */
        uint64_t dirty_aperture        : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[DIRTY_APERTURE]. */
        uint64_t clean_aperture        : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[CLEAN_APERTURE]. */
        uint64_t nxm                   : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[NXM]. */
        uint64_t fd_state              : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[FD_STATE]. */
        uint64_t fd_malformed          : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[FD_MALFORMED]. */
        uint64_t reserved_8            : 1;
        uint64_t malformed_x2p_pkt     : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[MALFORMED_X2P_PKT]. */
        uint64_t fc_psm_opcode         : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[FC_PSM_OPCODE]. */
        uint64_t wrrsp_fat             : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[WRRSP_FAT]. */
        uint64_t wrrsp_nfat            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ERROR_INT[WRRSP_NFAT].
                                                                 Internal:
                                                                 Should never occur. Including for completeness */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_error_ena_w1s_s cn; */
};
typedef union bdk_rfoex_rx_error_ena_w1s bdk_rfoex_rx_error_ena_w1s_t;

static inline uint64_t BDK_RFOEX_RX_ERROR_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_ERROR_ENA_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01e98ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_ERROR_ENA_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_ERROR_ENA_W1S(a) bdk_rfoex_rx_error_ena_w1s_t
#define bustype_BDK_RFOEX_RX_ERROR_ENA_W1S(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_ERROR_ENA_W1S(a) "RFOEX_RX_ERROR_ENA_W1S"
#define busnum_BDK_RFOEX_RX_ERROR_ENA_W1S(a) (a)
#define arguments_BDK_RFOEX_RX_ERROR_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_error_info0
 *
 * RFOE Error Interrupt Information Register
 * Error information for normal interrupts.
 */
union bdk_rfoex_rx_error_info0
{
    uint64_t u;
    struct bdk_rfoex_rx_error_info0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_58_63        : 6;
        uint64_t clean_aperture_lmac_id : 2; /**< [ 57: 56](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[CLEAN_APERTURE] */
        uint64_t clean_aperture_flowid : 8;  /**< [ 55: 48](RO/H) FLOWID for first error that set RFOE()_RX_ERROR_INT[CLEAN_APERTURE] */
        uint64_t reserved_46_47        : 2;
        uint64_t dirty_aperture_lmac_id : 2; /**< [ 45: 44](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[DIRTY_APERTURE] */
        uint64_t dirty_aperture_flowid : 8;  /**< [ 43: 36](RO/H) FLOWID for first error that set RFOE()_RX_ERROR_INT[DIRTY_APERTURE] */
        uint64_t reserved_34_35        : 2;
        uint64_t buf_overflow_lmac_id  : 2;  /**< [ 33: 32](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[BUF_OVERFLOW] */
        uint64_t buf_overflow_flowid   : 8;  /**< [ 31: 24](RO/H) FLOWID for first error that set RFOE()_RX_ERROR_INT[BUF_OVERFLOW] */
        uint64_t reserved_22_23        : 2;
        uint64_t len_miscomp_lmac_id   : 2;  /**< [ 21: 20](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[LEN_MISCOMP] */
        uint64_t len_miscomp_flowid    : 8;  /**< [ 19: 12](RO/H) FLOWID for first error that set RFOE()_RX_ERROR_INT[LEN_MISCOMP] */
        uint64_t reserved_10_11        : 2;
        uint64_t len_abnorm_lmac_id    : 2;  /**< [  9:  8](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[LEN_ABNORM] */
        uint64_t len_abnorm_flowid     : 8;  /**< [  7:  0](RO/H) FLOWID for first error that set RFOE()_RX_ERROR_INT[LEN_ABNORM] */
#else /* Word 0 - Little Endian */
        uint64_t len_abnorm_flowid     : 8;  /**< [  7:  0](RO/H) FLOWID for first error that set RFOE()_RX_ERROR_INT[LEN_ABNORM] */
        uint64_t len_abnorm_lmac_id    : 2;  /**< [  9:  8](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[LEN_ABNORM] */
        uint64_t reserved_10_11        : 2;
        uint64_t len_miscomp_flowid    : 8;  /**< [ 19: 12](RO/H) FLOWID for first error that set RFOE()_RX_ERROR_INT[LEN_MISCOMP] */
        uint64_t len_miscomp_lmac_id   : 2;  /**< [ 21: 20](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[LEN_MISCOMP] */
        uint64_t reserved_22_23        : 2;
        uint64_t buf_overflow_flowid   : 8;  /**< [ 31: 24](RO/H) FLOWID for first error that set RFOE()_RX_ERROR_INT[BUF_OVERFLOW] */
        uint64_t buf_overflow_lmac_id  : 2;  /**< [ 33: 32](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[BUF_OVERFLOW] */
        uint64_t reserved_34_35        : 2;
        uint64_t dirty_aperture_flowid : 8;  /**< [ 43: 36](RO/H) FLOWID for first error that set RFOE()_RX_ERROR_INT[DIRTY_APERTURE] */
        uint64_t dirty_aperture_lmac_id : 2; /**< [ 45: 44](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[DIRTY_APERTURE] */
        uint64_t reserved_46_47        : 2;
        uint64_t clean_aperture_flowid : 8;  /**< [ 55: 48](RO/H) FLOWID for first error that set RFOE()_RX_ERROR_INT[CLEAN_APERTURE] */
        uint64_t clean_aperture_lmac_id : 2; /**< [ 57: 56](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[CLEAN_APERTURE] */
        uint64_t reserved_58_63        : 6;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_error_info0_s cn; */
};
typedef union bdk_rfoex_rx_error_info0 bdk_rfoex_rx_error_info0_t;

static inline uint64_t BDK_RFOEX_RX_ERROR_INFO0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_ERROR_INFO0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01ec0ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_ERROR_INFO0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_ERROR_INFO0(a) bdk_rfoex_rx_error_info0_t
#define bustype_BDK_RFOEX_RX_ERROR_INFO0(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_ERROR_INFO0(a) "RFOEX_RX_ERROR_INFO0"
#define busnum_BDK_RFOEX_RX_ERROR_INFO0(a) (a)
#define arguments_BDK_RFOEX_RX_ERROR_INFO0(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_error_info1
 *
 * RFOE Error Interrupt Information Register
 * Error information for errors reported in RFOE()_RX_ERROR_INT.
 */
union bdk_rfoex_rx_error_info1
{
    uint64_t u;
    struct bdk_rfoex_rx_error_info1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_58_63        : 6;
        uint64_t fc_psm_opcode_lmac_id : 2;  /**< [ 57: 56](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[FC_PSM_OPCODE]. */
        uint64_t fc_psm_opcode_flowid  : 8;  /**< [ 55: 48](RO/H) FLOWID for first error that set RFOE()_RX_ERROR_INT[FC_PSM_OPCODE]. */
        uint64_t reserved_46_47        : 2;
        uint64_t malformed_x2p_pkt_lmac_id : 2;/**< [ 45: 44](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[MALFORMED_X2P_PKT]. */
        uint64_t malformed_x2p_pkt_flowid : 8;/**< [ 43: 36](RO/H) FLOWID for first error that set RFOE()_RX_ERROR_INT[MALFORMED_X2P_PKT]. */
        uint64_t reserved_34_35        : 2;
        uint64_t fd_malformed_lmac_id  : 2;  /**< [ 33: 32](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[FD_MALFORMED]. */
        uint64_t fd_malformed_flowid   : 8;  /**< [ 31: 24](RO/H) FLOWID for first error that set RFOE()_RX_ERROR_INT[FD_MALFORMED]. */
        uint64_t reserved_22_23        : 2;
        uint64_t fd_state_lmac_id      : 2;  /**< [ 21: 20](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[FD_STATE]. */
        uint64_t fd_state_flowid       : 8;  /**< [ 19: 12](RO/H) FLOWID for first error that set RFOE()_RX_ERROR_INT[FD_STATE]. */
        uint64_t reserved_11           : 1;
        uint64_t nxm_logger            : 1;  /**< [ 10: 10](RO/H) Logger write request caused first error that set RFOE()_RX_ERROR_INT[NXM]. */
        uint64_t nxm_lmac_id           : 2;  /**< [  9:  8](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[NXM].  Invalid when [NXM_LOGGER]=1.
                                                                 Internal:
                                                                 Should be 0 when [NXM_LOGGER] = 1. */
        uint64_t reserved_7            : 1;
        uint64_t wrrsp_nfat_logger     : 1;  /**< [  6:  6](RO/H) Logger write request caused first error that set RFOE()_RX_ERROR_INT[WRRSP_NFAT]. */
        uint64_t wrrsp_nfat_lmac_id    : 2;  /**< [  5:  4](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[WRRSP_NFAT].  Invalid when
                                                                 [WRRSP_NFAT_LOGGER]==1.

                                                                 Internal:
                                                                 Should be 0 when [WRRSP_NFAT_LOGGER] = 1. */
        uint64_t reserved_3            : 1;
        uint64_t wrrsp_fat_logger      : 1;  /**< [  2:  2](RO/H) Logger write request caused first error that set RFOE()_RX_ERROR_INT[WRRSP_FAT]. */
        uint64_t wrrsp_fat_lmac_id     : 2;  /**< [  1:  0](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[WRRSP_FAT].  Invalid when [WRRSP_FAT_LOGGER]=1.
                                                                 Internal:
                                                                 Should be 0 when [WRRSP_FAT_LOGGER] = 1. */
#else /* Word 0 - Little Endian */
        uint64_t wrrsp_fat_lmac_id     : 2;  /**< [  1:  0](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[WRRSP_FAT].  Invalid when [WRRSP_FAT_LOGGER]=1.
                                                                 Internal:
                                                                 Should be 0 when [WRRSP_FAT_LOGGER] = 1. */
        uint64_t wrrsp_fat_logger      : 1;  /**< [  2:  2](RO/H) Logger write request caused first error that set RFOE()_RX_ERROR_INT[WRRSP_FAT]. */
        uint64_t reserved_3            : 1;
        uint64_t wrrsp_nfat_lmac_id    : 2;  /**< [  5:  4](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[WRRSP_NFAT].  Invalid when
                                                                 [WRRSP_NFAT_LOGGER]==1.

                                                                 Internal:
                                                                 Should be 0 when [WRRSP_NFAT_LOGGER] = 1. */
        uint64_t wrrsp_nfat_logger     : 1;  /**< [  6:  6](RO/H) Logger write request caused first error that set RFOE()_RX_ERROR_INT[WRRSP_NFAT]. */
        uint64_t reserved_7            : 1;
        uint64_t nxm_lmac_id           : 2;  /**< [  9:  8](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[NXM].  Invalid when [NXM_LOGGER]=1.
                                                                 Internal:
                                                                 Should be 0 when [NXM_LOGGER] = 1. */
        uint64_t nxm_logger            : 1;  /**< [ 10: 10](RO/H) Logger write request caused first error that set RFOE()_RX_ERROR_INT[NXM]. */
        uint64_t reserved_11           : 1;
        uint64_t fd_state_flowid       : 8;  /**< [ 19: 12](RO/H) FLOWID for first error that set RFOE()_RX_ERROR_INT[FD_STATE]. */
        uint64_t fd_state_lmac_id      : 2;  /**< [ 21: 20](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[FD_STATE]. */
        uint64_t reserved_22_23        : 2;
        uint64_t fd_malformed_flowid   : 8;  /**< [ 31: 24](RO/H) FLOWID for first error that set RFOE()_RX_ERROR_INT[FD_MALFORMED]. */
        uint64_t fd_malformed_lmac_id  : 2;  /**< [ 33: 32](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[FD_MALFORMED]. */
        uint64_t reserved_34_35        : 2;
        uint64_t malformed_x2p_pkt_flowid : 8;/**< [ 43: 36](RO/H) FLOWID for first error that set RFOE()_RX_ERROR_INT[MALFORMED_X2P_PKT]. */
        uint64_t malformed_x2p_pkt_lmac_id : 2;/**< [ 45: 44](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[MALFORMED_X2P_PKT]. */
        uint64_t reserved_46_47        : 2;
        uint64_t fc_psm_opcode_flowid  : 8;  /**< [ 55: 48](RO/H) FLOWID for first error that set RFOE()_RX_ERROR_INT[FC_PSM_OPCODE]. */
        uint64_t fc_psm_opcode_lmac_id : 2;  /**< [ 57: 56](RO/H) LMAC for first error that set RFOE()_RX_ERROR_INT[FC_PSM_OPCODE]. */
        uint64_t reserved_58_63        : 6;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_error_info1_s cn; */
};
typedef union bdk_rfoex_rx_error_info1 bdk_rfoex_rx_error_info1_t;

static inline uint64_t BDK_RFOEX_RX_ERROR_INFO1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_ERROR_INFO1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01ec8ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_ERROR_INFO1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_ERROR_INFO1(a) bdk_rfoex_rx_error_info1_t
#define bustype_BDK_RFOEX_RX_ERROR_INFO1(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_ERROR_INFO1(a) "RFOEX_RX_ERROR_INFO1"
#define busnum_BDK_RFOEX_RX_ERROR_INFO1(a) (a)
#define arguments_BDK_RFOEX_RX_ERROR_INFO1(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_error_int
 *
 * RFOE Error Interrupt Register
 * These registers record normal errors across the RFOE RX
 * When a miscompare occurs, the LMAC, FLOWID is recorded in the following register.
 * RFOE()_RX_ERROR_INFO0 or RFOE()_RX_ERROR_INFO1.
 *
 * When an error occurs, RFOE sends  message to PSM defined by
 * RFOE()_RX_ERROR_PSM_MSG_W1,RFOE()_RX_ERROR_PSM_MSG_W0
 */
union bdk_rfoex_rx_error_int
{
    uint64_t u;
    struct bdk_rfoex_rx_error_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t wrrsp_nfat            : 1;  /**< [ 12: 12](R/W1C/H) Write response returned a non-fatal non-NXM error.
                                                                 Internal:
                                                                 Should never occur. Including for completeness */
        uint64_t wrrsp_fat             : 1;  /**< [ 11: 11](R/W1C/H) Write response returned a fatal non-NXM error. */
        uint64_t fc_psm_opcode         : 1;  /**< [ 10: 10](R/W1C/H) Received RoE packet, 0xfc subtype with a PSM command carrying a disabled OPCODE.
                                                                 Bit is set when RoE subtype 0xfc received with PSM command OPCODE is not enabled in
                                                                 RFOE()_RX_FC_PSM_OPCODE_ENA. */
        uint64_t malformed_x2p_pkt     : 1;  /**< [  9:  9](R/W1C/H) Corrupted packet arrived from MAC:
                                                                 *Missing SOP: a flit arrived that was not preceded by SOP.
                                                                 *Unexpected SOP: an SOP flit received while still processing a packet (no EOP for previous packet).
                                                                 Something bad happened in receive path to cause bad packets. */
        uint64_t reserved_8            : 1;
        uint64_t fd_malformed          : 1;  /**< [  7:  7](R/W1C/H) 0xFD subtype SOS received for a MBT entry that is already busy:
                                                                 *Packet is dropped.
                                                                 *0xFD packets using the same MBT entry through EOS are dropped.
                                                                 *0xFD packets already received and in memory for the MBT entry are ignored.
                                                                 Packet data will be overwritten on next usage of the buffer.

                                                                 0xFD subtype received, but no SOS received for that MBT entry.
                                                                 *Packet is dropped.
                                                                 *0xFD packets using the same MBT entry through EOS are dropped. */
        uint64_t fd_state              : 1;  /**< [  6:  6](R/W1C/H) At SOP a non 0xFD subtype is received for an MBT entry that is being used to assemble a symbol.
                                                                 New packet is dropped, and assembly continues for the symbol. */
        uint64_t nxm                   : 1;  /**< [  5:  5](R/W1C/H) Attempt to write to invalid SMEM address (i.e., address beyond current
                                                                 SMEM size). Writes to invalid addresses were dropped. Note that this
                                                                 may result from either a packet write or a logger write, see
                                                                 RFOE()_RX_ERROR_INFO1[NXM_LOGGER]. */
        uint64_t clean_aperture        : 1;  /**< [  4:  4](R/W1C/H) For ROE 0xFC subtype and CHI packets. Starting address is outside of the
                                                                 MIN_APERTURE, MAX_APERTURE.
                                                                 When this happens:
                                                                 *Packet is cleanly dropped.
                                                                 *No data from packet is written to memory.
                                                                 *No JCA message. */
        uint64_t dirty_aperture        : 1;  /**< [  3:  3](R/W1C/H) For ROE 0xfc subtype and CHI packets. DMA started if the packet but packet
                                                                 length caused the DMA operation to go outside of the MAX_APERTURE.
                                                                 When this happens:
                                                                 *All flits from the packet beyond the MAX_APERTURE are dropped.
                                                                 *Packet status/logger sets the RFOE_PACKET_STATUS_S.DMA_ERROR bit.
                                                                 *Normal Completion JCA message is sent at EOP. */
        uint64_t buf_overflow          : 1;  /**< [  2:  2](R/W1C/H) DMA operation of ROE type to a memory buffer exceeded the size of the buffer programmed in
                                                                 RFOE()_RX_IND_MBT_CFG[BUF_SIZE]. When this happens:
                                                                 *All flits from the packet beyond the buf_size limit are dropped.
                                                                 *Packet status/logger sets the RFOE_PACKET_STATUS_S.DMA_ERROR bit.
                                                                 *Normal Completion JCA message is sent at EOP. */
        uint64_t len_miscomp           : 1;  /**< [  1:  1](R/W1C/H) Length field in packet header does not match payload.  For packets using DMA:
                                                                 * CHI packet header length field does not match data length.
                                                                 * ROE others. Length field does not match payload.
                                                                 * Transparent, ALT: no length check for [LEN_MISCOMP].

                                                                 Internal:
                                                                 RX Header processing expects \> 48B. */
        uint64_t len_abnorm            : 1;  /**< [  0:  0](R/W1C/H) Total packet length \<= 48 bytes. Packet is dropped.  Total length at x2p must be \> 48B.
                                                                 Internal:
                                                                 RX Header processing expects \> 48B. P1914 note--  RoE payload must be \>= 64B. */
#else /* Word 0 - Little Endian */
        uint64_t len_abnorm            : 1;  /**< [  0:  0](R/W1C/H) Total packet length \<= 48 bytes. Packet is dropped.  Total length at x2p must be \> 48B.
                                                                 Internal:
                                                                 RX Header processing expects \> 48B. P1914 note--  RoE payload must be \>= 64B. */
        uint64_t len_miscomp           : 1;  /**< [  1:  1](R/W1C/H) Length field in packet header does not match payload.  For packets using DMA:
                                                                 * CHI packet header length field does not match data length.
                                                                 * ROE others. Length field does not match payload.
                                                                 * Transparent, ALT: no length check for [LEN_MISCOMP].

                                                                 Internal:
                                                                 RX Header processing expects \> 48B. */
        uint64_t buf_overflow          : 1;  /**< [  2:  2](R/W1C/H) DMA operation of ROE type to a memory buffer exceeded the size of the buffer programmed in
                                                                 RFOE()_RX_IND_MBT_CFG[BUF_SIZE]. When this happens:
                                                                 *All flits from the packet beyond the buf_size limit are dropped.
                                                                 *Packet status/logger sets the RFOE_PACKET_STATUS_S.DMA_ERROR bit.
                                                                 *Normal Completion JCA message is sent at EOP. */
        uint64_t dirty_aperture        : 1;  /**< [  3:  3](R/W1C/H) For ROE 0xfc subtype and CHI packets. DMA started if the packet but packet
                                                                 length caused the DMA operation to go outside of the MAX_APERTURE.
                                                                 When this happens:
                                                                 *All flits from the packet beyond the MAX_APERTURE are dropped.
                                                                 *Packet status/logger sets the RFOE_PACKET_STATUS_S.DMA_ERROR bit.
                                                                 *Normal Completion JCA message is sent at EOP. */
        uint64_t clean_aperture        : 1;  /**< [  4:  4](R/W1C/H) For ROE 0xFC subtype and CHI packets. Starting address is outside of the
                                                                 MIN_APERTURE, MAX_APERTURE.
                                                                 When this happens:
                                                                 *Packet is cleanly dropped.
                                                                 *No data from packet is written to memory.
                                                                 *No JCA message. */
        uint64_t nxm                   : 1;  /**< [  5:  5](R/W1C/H) Attempt to write to invalid SMEM address (i.e., address beyond current
                                                                 SMEM size). Writes to invalid addresses were dropped. Note that this
                                                                 may result from either a packet write or a logger write, see
                                                                 RFOE()_RX_ERROR_INFO1[NXM_LOGGER]. */
        uint64_t fd_state              : 1;  /**< [  6:  6](R/W1C/H) At SOP a non 0xFD subtype is received for an MBT entry that is being used to assemble a symbol.
                                                                 New packet is dropped, and assembly continues for the symbol. */
        uint64_t fd_malformed          : 1;  /**< [  7:  7](R/W1C/H) 0xFD subtype SOS received for a MBT entry that is already busy:
                                                                 *Packet is dropped.
                                                                 *0xFD packets using the same MBT entry through EOS are dropped.
                                                                 *0xFD packets already received and in memory for the MBT entry are ignored.
                                                                 Packet data will be overwritten on next usage of the buffer.

                                                                 0xFD subtype received, but no SOS received for that MBT entry.
                                                                 *Packet is dropped.
                                                                 *0xFD packets using the same MBT entry through EOS are dropped. */
        uint64_t reserved_8            : 1;
        uint64_t malformed_x2p_pkt     : 1;  /**< [  9:  9](R/W1C/H) Corrupted packet arrived from MAC:
                                                                 *Missing SOP: a flit arrived that was not preceded by SOP.
                                                                 *Unexpected SOP: an SOP flit received while still processing a packet (no EOP for previous packet).
                                                                 Something bad happened in receive path to cause bad packets. */
        uint64_t fc_psm_opcode         : 1;  /**< [ 10: 10](R/W1C/H) Received RoE packet, 0xfc subtype with a PSM command carrying a disabled OPCODE.
                                                                 Bit is set when RoE subtype 0xfc received with PSM command OPCODE is not enabled in
                                                                 RFOE()_RX_FC_PSM_OPCODE_ENA. */
        uint64_t wrrsp_fat             : 1;  /**< [ 11: 11](R/W1C/H) Write response returned a fatal non-NXM error. */
        uint64_t wrrsp_nfat            : 1;  /**< [ 12: 12](R/W1C/H) Write response returned a non-fatal non-NXM error.
                                                                 Internal:
                                                                 Should never occur. Including for completeness */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_error_int_s cn; */
};
typedef union bdk_rfoex_rx_error_int bdk_rfoex_rx_error_int_t;

static inline uint64_t BDK_RFOEX_RX_ERROR_INT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_ERROR_INT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01e90ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_ERROR_INT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_ERROR_INT(a) bdk_rfoex_rx_error_int_t
#define bustype_BDK_RFOEX_RX_ERROR_INT(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_ERROR_INT(a) "RFOEX_RX_ERROR_INT"
#define busnum_BDK_RFOEX_RX_ERROR_INT(a) (a)
#define arguments_BDK_RFOEX_RX_ERROR_INT(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_error_int_w1s
 *
 * RFOE OrderInfo Interrupt  Error Interrupt Set Registers
 * This register sets interrupt bits.
 */
union bdk_rfoex_rx_error_int_w1s
{
    uint64_t u;
    struct bdk_rfoex_rx_error_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t wrrsp_nfat            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[WRRSP_NFAT].
                                                                 Internal:
                                                                 Should never occur. Including for completeness */
        uint64_t wrrsp_fat             : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[WRRSP_FAT]. */
        uint64_t fc_psm_opcode         : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[FC_PSM_OPCODE]. */
        uint64_t malformed_x2p_pkt     : 1;  /**< [  9:  9](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[MALFORMED_X2P_PKT]. */
        uint64_t reserved_8            : 1;
        uint64_t fd_malformed          : 1;  /**< [  7:  7](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[FD_MALFORMED]. */
        uint64_t fd_state              : 1;  /**< [  6:  6](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[FD_STATE]. */
        uint64_t nxm                   : 1;  /**< [  5:  5](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[NXM]. */
        uint64_t clean_aperture        : 1;  /**< [  4:  4](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[CLEAN_APERTURE]. */
        uint64_t dirty_aperture        : 1;  /**< [  3:  3](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[DIRTY_APERTURE]. */
        uint64_t buf_overflow          : 1;  /**< [  2:  2](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[BUF_OVERFLOW]. */
        uint64_t len_miscomp           : 1;  /**< [  1:  1](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[LEN_MISCOMP].
                                                                 Internal:
                                                                 RX Header processing expects \> 48B. */
        uint64_t len_abnorm            : 1;  /**< [  0:  0](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[LEN_ABNORM].
                                                                 Internal:
                                                                 RX Header processing expects \> 48B. P1914 note--  RoE payload must be \>= 64B. */
#else /* Word 0 - Little Endian */
        uint64_t len_abnorm            : 1;  /**< [  0:  0](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[LEN_ABNORM].
                                                                 Internal:
                                                                 RX Header processing expects \> 48B. P1914 note--  RoE payload must be \>= 64B. */
        uint64_t len_miscomp           : 1;  /**< [  1:  1](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[LEN_MISCOMP].
                                                                 Internal:
                                                                 RX Header processing expects \> 48B. */
        uint64_t buf_overflow          : 1;  /**< [  2:  2](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[BUF_OVERFLOW]. */
        uint64_t dirty_aperture        : 1;  /**< [  3:  3](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[DIRTY_APERTURE]. */
        uint64_t clean_aperture        : 1;  /**< [  4:  4](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[CLEAN_APERTURE]. */
        uint64_t nxm                   : 1;  /**< [  5:  5](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[NXM]. */
        uint64_t fd_state              : 1;  /**< [  6:  6](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[FD_STATE]. */
        uint64_t fd_malformed          : 1;  /**< [  7:  7](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[FD_MALFORMED]. */
        uint64_t reserved_8            : 1;
        uint64_t malformed_x2p_pkt     : 1;  /**< [  9:  9](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[MALFORMED_X2P_PKT]. */
        uint64_t fc_psm_opcode         : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[FC_PSM_OPCODE]. */
        uint64_t wrrsp_fat             : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[WRRSP_FAT]. */
        uint64_t wrrsp_nfat            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets RFOE(0..1)_RX_ERROR_INT[WRRSP_NFAT].
                                                                 Internal:
                                                                 Should never occur. Including for completeness */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_error_int_w1s_s cn; */
};
typedef union bdk_rfoex_rx_error_int_w1s bdk_rfoex_rx_error_int_w1s_t;

static inline uint64_t BDK_RFOEX_RX_ERROR_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_ERROR_INT_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01ea8ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_ERROR_INT_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_ERROR_INT_W1S(a) bdk_rfoex_rx_error_int_w1s_t
#define bustype_BDK_RFOEX_RX_ERROR_INT_W1S(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_ERROR_INT_W1S(a) "RFOEX_RX_ERROR_INT_W1S"
#define busnum_BDK_RFOEX_RX_ERROR_INT_W1S(a) (a)
#define arguments_BDK_RFOEX_RX_ERROR_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_error_psm_msg_w0
 *
 * RFOE OrderInfo Interrupt Message w0  Register
 * JCA word 0 message to send on enabled orderInfo error.
 */
union bdk_rfoex_rx_error_psm_msg_w0
{
    uint64_t u;
    struct bdk_rfoex_rx_error_psm_msg_w0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t w0                    : 64; /**< [ 63:  0](R/W) w0 of JCA message */
#else /* Word 0 - Little Endian */
        uint64_t w0                    : 64; /**< [ 63:  0](R/W) w0 of JCA message */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_error_psm_msg_w0_s cn; */
};
typedef union bdk_rfoex_rx_error_psm_msg_w0 bdk_rfoex_rx_error_psm_msg_w0_t;

static inline uint64_t BDK_RFOEX_RX_ERROR_PSM_MSG_W0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_ERROR_PSM_MSG_W0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01eb0ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_ERROR_PSM_MSG_W0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_ERROR_PSM_MSG_W0(a) bdk_rfoex_rx_error_psm_msg_w0_t
#define bustype_BDK_RFOEX_RX_ERROR_PSM_MSG_W0(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_ERROR_PSM_MSG_W0(a) "RFOEX_RX_ERROR_PSM_MSG_W0"
#define busnum_BDK_RFOEX_RX_ERROR_PSM_MSG_W0(a) (a)
#define arguments_BDK_RFOEX_RX_ERROR_PSM_MSG_W0(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_error_psm_msg_w1
 *
 * RFOE Error Interrupt Message w1 Register
 * JCA word 1 message to send on enabled  error.
 */
union bdk_rfoex_rx_error_psm_msg_w1
{
    uint64_t u;
    struct bdk_rfoex_rx_error_psm_msg_w1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t w1                    : 64; /**< [ 63:  0](R/W) w1 of JCA message */
#else /* Word 0 - Little Endian */
        uint64_t w1                    : 64; /**< [ 63:  0](R/W) w1 of JCA message */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_error_psm_msg_w1_s cn; */
};
typedef union bdk_rfoex_rx_error_psm_msg_w1 bdk_rfoex_rx_error_psm_msg_w1_t;

static inline uint64_t BDK_RFOEX_RX_ERROR_PSM_MSG_W1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_ERROR_PSM_MSG_W1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01eb8ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_ERROR_PSM_MSG_W1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_ERROR_PSM_MSG_W1(a) bdk_rfoex_rx_error_psm_msg_w1_t
#define bustype_BDK_RFOEX_RX_ERROR_PSM_MSG_W1(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_ERROR_PSM_MSG_W1(a) "RFOEX_RX_ERROR_PSM_MSG_W1"
#define busnum_BDK_RFOEX_RX_ERROR_PSM_MSG_W1(a) (a)
#define arguments_BDK_RFOEX_RX_ERROR_PSM_MSG_W1(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_fc_psm_opcode_ena
 *
 * RFOE RX RoE FC PSM Opcode Enable Register
 * Per opcode enable.   If  RFOE()_RX_FC_PSM_OPCODE_ENA(OPCODE) == 0, then PSM MSG[OPCODE]
 * is disabled and the packet will dropped.
 */
union bdk_rfoex_rx_fc_psm_opcode_ena
{
    uint64_t u;
    struct bdk_rfoex_rx_fc_psm_opcode_ena_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ena                   : 64; /**< [ 63:  0](R/W) Opcode enables. */
#else /* Word 0 - Little Endian */
        uint64_t ena                   : 64; /**< [ 63:  0](R/W) Opcode enables. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_fc_psm_opcode_ena_s cn; */
};
typedef union bdk_rfoex_rx_fc_psm_opcode_ena bdk_rfoex_rx_fc_psm_opcode_ena_t;

static inline uint64_t BDK_RFOEX_RX_FC_PSM_OPCODE_ENA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_FC_PSM_OPCODE_ENA(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01880ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_FC_PSM_OPCODE_ENA", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_FC_PSM_OPCODE_ENA(a) bdk_rfoex_rx_fc_psm_opcode_ena_t
#define bustype_BDK_RFOEX_RX_FC_PSM_OPCODE_ENA(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_FC_PSM_OPCODE_ENA(a) "RFOEX_RX_FC_PSM_OPCODE_ENA"
#define busnum_BDK_RFOEX_RX_FC_PSM_OPCODE_ENA(a) (a)
#define arguments_BDK_RFOEX_RX_FC_PSM_OPCODE_ENA(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_fd_reset
 *
 * RFOE RX Sync State Register
 * Reset the 0xFD subtype reassembly state per MBT_IDX.
 * _  mbt_index = bit.
 *
 * Writes of bit = 1 resets the reassembly state for that MBT_IDX.
 * Must only be used when the RFOE()_RX_IND_FT()_CFG[ENABLE] must be 0 for all MBT_IDXes.
 * Used as part of the rx_sync sequence.
 */
union bdk_rfoex_rx_fd_reset
{
    uint64_t u;
    struct bdk_rfoex_rx_fd_reset_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reset                 : 64; /**< [ 63:  0](WO) Bit-mask of MBT_IDX. For each bit:
                                                                 0 = Don't reset FD state.
                                                                 1 =  Reset the FD state */
#else /* Word 0 - Little Endian */
        uint64_t reset                 : 64; /**< [ 63:  0](WO) Bit-mask of MBT_IDX. For each bit:
                                                                 0 = Don't reset FD state.
                                                                 1 =  Reset the FD state */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_fd_reset_s cn; */
};
typedef union bdk_rfoex_rx_fd_reset bdk_rfoex_rx_fd_reset_t;

static inline uint64_t BDK_RFOEX_RX_FD_RESET(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_FD_RESET(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01770ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_FD_RESET", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_FD_RESET(a) bdk_rfoex_rx_fd_reset_t
#define bustype_BDK_RFOEX_RX_FD_RESET(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_FD_RESET(a) "RFOEX_RX_FD_RESET"
#define busnum_BDK_RFOEX_RX_FD_RESET(a) (a)
#define arguments_BDK_RFOEX_RX_FD_RESET(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_fd_sos_drop_stat
 *
 * RFOE RX FD subtype pre-SOS Packet Drop Statistic Register
 * Count of packets of 0xfd subtype dropped waiting for SOS (start of
 * symbol).  These can occur when a flow is reconfigured while receiving a
 * symbol.  RFOE drops the segments until it finds the start of a symbol and
 * then starts DMA at the beginning of the new symbol.
 */
union bdk_rfoex_rx_fd_sos_drop_stat
{
    uint64_t u;
    struct bdk_rfoex_rx_fd_sos_drop_stat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) The counter value. Wraps to zero at 2^48. */
#else /* Word 0 - Little Endian */
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) The counter value. Wraps to zero at 2^48. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_fd_sos_drop_stat_s cn; */
};
typedef union bdk_rfoex_rx_fd_sos_drop_stat bdk_rfoex_rx_fd_sos_drop_stat_t;

static inline uint64_t BDK_RFOEX_RX_FD_SOS_DROP_STAT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_FD_SOS_DROP_STAT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01d30ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_FD_SOS_DROP_STAT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_FD_SOS_DROP_STAT(a) bdk_rfoex_rx_fd_sos_drop_stat_t
#define bustype_BDK_RFOEX_RX_FD_SOS_DROP_STAT(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_FD_SOS_DROP_STAT(a) "RFOEX_RX_FD_SOS_DROP_STAT"
#define busnum_BDK_RFOEX_RX_FD_SOS_DROP_STAT(a) (a)
#define arguments_BDK_RFOEX_RX_FD_SOS_DROP_STAT(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_fd_state#
 *
 * RFOE RX Sync State Register
 * Debug register for FD_STATE.
 * Internal:
 * Indicates the 0xfd reassembly state for each MBT_IDX
 * FD reassembly state is a 2 bit state enumerated by RFOE_RX_FD_STATE_E.
 *
 * FD_STATE{b}(MBT_IDX%32+1:MBT_IDX%32):
 */
union bdk_rfoex_rx_fd_statex
{
    uint64_t u;
    struct bdk_rfoex_rx_fd_statex_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t state                 : 64; /**< [ 63:  0](RO/H) 2 bit state value for reassembly state. */
#else /* Word 0 - Little Endian */
        uint64_t state                 : 64; /**< [ 63:  0](RO/H) 2 bit state value for reassembly state. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_fd_statex_s cn; */
};
typedef union bdk_rfoex_rx_fd_statex bdk_rfoex_rx_fd_statex_t;

static inline uint64_t BDK_RFOEX_RX_FD_STATEX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_FD_STATEX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=1)))
        return 0x87e043d01760ll + 0x80000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_FD_STATEX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_FD_STATEX(a,b) bdk_rfoex_rx_fd_statex_t
#define bustype_BDK_RFOEX_RX_FD_STATEX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_FD_STATEX(a,b) "RFOEX_RX_FD_STATEX"
#define busnum_BDK_RFOEX_RX_FD_STATEX(a,b) (a)
#define arguments_BDK_RFOEX_RX_FD_STATEX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_rx_ft_enable_drop_stat
 *
 * RFOE RX Flow Table Enable Packet Drop Statistic Register
 * Count of packets dropped because RFOE()_RX_IND_FT()_CFG[ENABLE]=0.
 */
union bdk_rfoex_rx_ft_enable_drop_stat
{
    uint64_t u;
    struct bdk_rfoex_rx_ft_enable_drop_stat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) The counter value. Wraps to zero at 2^48. */
#else /* Word 0 - Little Endian */
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) The counter value. Wraps to zero at 2^48. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_ft_enable_drop_stat_s cn; */
};
typedef union bdk_rfoex_rx_ft_enable_drop_stat bdk_rfoex_rx_ft_enable_drop_stat_t;

static inline uint64_t BDK_RFOEX_RX_FT_ENABLE_DROP_STAT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_FT_ENABLE_DROP_STAT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01d28ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_FT_ENABLE_DROP_STAT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_FT_ENABLE_DROP_STAT(a) bdk_rfoex_rx_ft_enable_drop_stat_t
#define bustype_BDK_RFOEX_RX_FT_ENABLE_DROP_STAT(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_FT_ENABLE_DROP_STAT(a) "RFOEX_RX_FT_ENABLE_DROP_STAT"
#define busnum_BDK_RFOEX_RX_FT_ENABLE_DROP_STAT(a) (a)
#define arguments_BDK_RFOEX_RX_FT_ENABLE_DROP_STAT(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_ind_ft#_cfg
 *
 * RFOE RX Indirect Flow Table Configuration Register
 * Flow table configuration for LMAC {b}.
 *
 * This register indirectly accesses a flow configuration table with 256
 * entries.
 *
 * Reads and writes to this register access the table entry specified by
 * RFOE()_RX_INDIRECT_INDEX[INDEX].
 *
 * Incoming packets from LMAC {b} index the flow table using either the flow
 * ID extracted from an RoE header, or using
 * RFOE()_RX_DIRECTION_CTL()[FLOWID].
 */
union bdk_rfoex_rx_ind_ftx_cfg
{
    uint64_t u;
    struct bdk_rfoex_rx_ind_ftx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_15_63        : 49;
        uint64_t enable                : 1;  /**< [ 14: 14](R/W) Enable this flow. Drop packets when clear. */
        uint64_t mbt_idx               : 6;  /**< [ 13:  8](R/W) Pointer to RFOE()_RX_IND_MBT_CFG, RFOE()_RX_IND_MBT_ADDR for DMA write buffer configurations. */
        uint64_t flow_idx              : 8;  /**< [  7:  0](R/W) Pointer to RFOE()_RX_IND_JDT memories for job descriptor and flow configuration. */
#else /* Word 0 - Little Endian */
        uint64_t flow_idx              : 8;  /**< [  7:  0](R/W) Pointer to RFOE()_RX_IND_JDT memories for job descriptor and flow configuration. */
        uint64_t mbt_idx               : 6;  /**< [ 13:  8](R/W) Pointer to RFOE()_RX_IND_MBT_CFG, RFOE()_RX_IND_MBT_ADDR for DMA write buffer configurations. */
        uint64_t enable                : 1;  /**< [ 14: 14](R/W) Enable this flow. Drop packets when clear. */
        uint64_t reserved_15_63        : 49;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_ind_ftx_cfg_s cn; */
};
typedef union bdk_rfoex_rx_ind_ftx_cfg bdk_rfoex_rx_ind_ftx_cfg_t;

static inline uint64_t BDK_RFOEX_RX_IND_FTX_CFG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_IND_FTX_CFG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=3)))
        return 0x87e043d01c00ll + 0x80000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    __bdk_csr_fatal("RFOEX_RX_IND_FTX_CFG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_IND_FTX_CFG(a,b) bdk_rfoex_rx_ind_ftx_cfg_t
#define bustype_BDK_RFOEX_RX_IND_FTX_CFG(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_IND_FTX_CFG(a,b) "RFOEX_RX_IND_FTX_CFG"
#define busnum_BDK_RFOEX_RX_IND_FTX_CFG(a,b) (a)
#define arguments_BDK_RFOEX_RX_IND_FTX_CFG(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_rx_ind_jdt_cfg0
 *
 * RFOE RX Indirect Job Descriptor Table Configuration Zero Register
 * Job descriptor table, configuration register zero. This table determines
 * the format and location of job descriptors produced for incoming packets,
 * and controls some parameters of how packets are written to memory.
 *
 * This register indirectly accesses a table of 256 entries.
 *
 * Reads and writes to this register access the table entry specified by
 * RFOE()_RX_INDIRECT_INDEX[INDEX].
 *
 * Incoming packets select an JDT entry based on
 * RFOE()_RX_IND_FT()_CFG[FLOW_IDX].
 */
union bdk_rfoex_rx_ind_jdt_cfg0
{
    uint64_t u;
    struct bdk_rfoex_rx_ind_jdt_cfg0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t target_mem            : 1;  /**< [ 63: 63](R/W) Specifies the target memory for the address for the DMA's job descriptor write (JDW):
                                                                  0 = SMEM.
                                                                  1 = LLC/DRAM. */
        uint64_t reserved_62           : 1;
        uint64_t cmd_type              : 2;  /**< [ 61: 60](R/W) Deprecated.  Hardware does not use.
                                                                 Internal:
                                                                 Specifies the CMD_TYPE used by the JDW.  Used for the GAA write field dmat.
                                                                 Enumerated by MHBW_PNB_WR_CMD_E. */
        uint64_t reserved_59           : 1;
        uint64_t dswap                 : 3;  /**< [ 58: 56](R/W) The byte swap mode for JDW to LLC/DRAM. JDW to BPHY SMEM ignores this field.
                                                                 Enumerated by MHBW_PNB_DSWAP_E. */
        uint64_t reserved_55           : 1;
        uint64_t pkt_offset            : 3;  /**< [ 54: 52](R/W) Packet offset in units of 128-bits. DMA operation starts at START_ADDDR + [PKT_OFFSET]*16 bytes.
                                                                 Must be \<= 4. If [PKT_STATUS_WRITE]=1, must be \> 0 or the packet
                                                                 status write will over-write the packet data.

                                                                 Internal:
                                                                 Hardware should support values 5..7, but can't guarantee behavior. */
        uint64_t reserved_51           : 1;
        uint64_t jdw_enable            : 1;  /**< [ 50: 50](R/W) Enable JDW updates of job descriptor in memory.
                                                                 0 = Do not update job descriptor in memory.
                                                                 1 = Update job descriptor in memory.
                                                                 Used for standard ROE & 0xFD subtype ROE packets. Ignored by
                                                                 ROE subtype 0xFC. 0xFC subtype never writes the JD. */
        uint64_t pkt_status_write      : 1;  /**< [ 49: 49](R/W) When set, RFOE will write an RFOE_PACKET_STATUS_S header at the start
                                                                 of each buffer. */
        uint64_t jca_enable            : 1;  /**< [ 48: 48](R/W) Enable job completion action. When set, RFOE sends a JCA message on
                                                                 completion of each packet, or on the last segment for 0xFD subtype
                                                                 packets. */
        uint64_t num_jd                : 16; /**< [ 47: 32](R/W) Number of job descriptors in this circular buffer. Total size of the
                                                                 buffer is [NUM_JD]*[JD_SIZE]*8 bytes. Must be greater than 0.

                                                                 Internal:
                                                                 Hardware interprets [NUM_JD]=0 the same as [NUM_JD]=1.  [NUM_JD]=0 is nonsensical. */
        uint64_t jd_rd_offset          : 4;  /**< [ 31: 28](R/W) Location of read DMA descriptor within each job descriptor, in units
                                                                 of 8 bytes.
                                                                 * Must be less than [JD_SIZE]-1.
                                                                 * ([JD_RD_OFFSET]*8)+RFOE()_RX_IND_JDT_PTR[PTR] must be 128-bit aligned. */
        uint64_t jd_size               : 4;  /**< [ 27: 24](R/W) Size of each job descriptor, in units of 8 bytes. Must be even (i.e.,
                                                                 total size must be a multiple of 16 bytes). */
        uint64_t reserved_20_23        : 4;
        uint64_t sample_width          : 8;  /**< [ 19: 12](R/W) For [SAMPLE_MODE]=1, defines width in bits of I an Q samples in the packet
                                                                 data. */
        uint64_t sample_mode           : 1;  /**< [ 11: 11](R/W) Interpret RoE samples. When set, interpret the data following rbMap
                                                                 bytes as I,Q samples, and expand each [SAMPLE_WIDTH] I/Q sample to a 16-bit sample. */
        uint64_t sample_mode_width_option : 1;/**< [ 10: 10](R/W) I/Q sample format. When [SAMPLE_MODE]=1, this determines how samples
                                                                 are expanded to 16 bits.
                                                                 0 = Sign-extend left.
                                                                 1 = Zero pad right. */
        uint64_t transparent_mode      : 1;  /**< [  9:  9](R/W) Transparently write packet data to memory with no transformations.
                                                                 Overrides settings for [HEADER_DMA_MODE], [RBMAP_BYTES], and
                                                                 [SAMPLE_MODE]. RoE 0xFC subtype are never transparent and ignores this field. */
        uint64_t header_dma_mode       : 1;  /**< [  8:  8](R/W) Write header bytes out to memory if [HEADER_DMA_MODE] = 1.  Ignored when [TRANSPARENT_MODE] = 1. */
        uint64_t rbmap_bytes           : 8;  /**< [  7:  0](R/W) Number of rbMap bytes following the RoE header.
                                                                 For ROE subtype == 0xFD, rbmap_bytes are only in first segment. SOS segment only.
                                                                 *Transparent mode: ignored.  Transparent packets do not have rbMap.
                                                                 *RoE 0xFC subtype: ignored.  0xFC packets do not have rbMap. */
#else /* Word 0 - Little Endian */
        uint64_t rbmap_bytes           : 8;  /**< [  7:  0](R/W) Number of rbMap bytes following the RoE header.
                                                                 For ROE subtype == 0xFD, rbmap_bytes are only in first segment. SOS segment only.
                                                                 *Transparent mode: ignored.  Transparent packets do not have rbMap.
                                                                 *RoE 0xFC subtype: ignored.  0xFC packets do not have rbMap. */
        uint64_t header_dma_mode       : 1;  /**< [  8:  8](R/W) Write header bytes out to memory if [HEADER_DMA_MODE] = 1.  Ignored when [TRANSPARENT_MODE] = 1. */
        uint64_t transparent_mode      : 1;  /**< [  9:  9](R/W) Transparently write packet data to memory with no transformations.
                                                                 Overrides settings for [HEADER_DMA_MODE], [RBMAP_BYTES], and
                                                                 [SAMPLE_MODE]. RoE 0xFC subtype are never transparent and ignores this field. */
        uint64_t sample_mode_width_option : 1;/**< [ 10: 10](R/W) I/Q sample format. When [SAMPLE_MODE]=1, this determines how samples
                                                                 are expanded to 16 bits.
                                                                 0 = Sign-extend left.
                                                                 1 = Zero pad right. */
        uint64_t sample_mode           : 1;  /**< [ 11: 11](R/W) Interpret RoE samples. When set, interpret the data following rbMap
                                                                 bytes as I,Q samples, and expand each [SAMPLE_WIDTH] I/Q sample to a 16-bit sample. */
        uint64_t sample_width          : 8;  /**< [ 19: 12](R/W) For [SAMPLE_MODE]=1, defines width in bits of I an Q samples in the packet
                                                                 data. */
        uint64_t reserved_20_23        : 4;
        uint64_t jd_size               : 4;  /**< [ 27: 24](R/W) Size of each job descriptor, in units of 8 bytes. Must be even (i.e.,
                                                                 total size must be a multiple of 16 bytes). */
        uint64_t jd_rd_offset          : 4;  /**< [ 31: 28](R/W) Location of read DMA descriptor within each job descriptor, in units
                                                                 of 8 bytes.
                                                                 * Must be less than [JD_SIZE]-1.
                                                                 * ([JD_RD_OFFSET]*8)+RFOE()_RX_IND_JDT_PTR[PTR] must be 128-bit aligned. */
        uint64_t num_jd                : 16; /**< [ 47: 32](R/W) Number of job descriptors in this circular buffer. Total size of the
                                                                 buffer is [NUM_JD]*[JD_SIZE]*8 bytes. Must be greater than 0.

                                                                 Internal:
                                                                 Hardware interprets [NUM_JD]=0 the same as [NUM_JD]=1.  [NUM_JD]=0 is nonsensical. */
        uint64_t jca_enable            : 1;  /**< [ 48: 48](R/W) Enable job completion action. When set, RFOE sends a JCA message on
                                                                 completion of each packet, or on the last segment for 0xFD subtype
                                                                 packets. */
        uint64_t pkt_status_write      : 1;  /**< [ 49: 49](R/W) When set, RFOE will write an RFOE_PACKET_STATUS_S header at the start
                                                                 of each buffer. */
        uint64_t jdw_enable            : 1;  /**< [ 50: 50](R/W) Enable JDW updates of job descriptor in memory.
                                                                 0 = Do not update job descriptor in memory.
                                                                 1 = Update job descriptor in memory.
                                                                 Used for standard ROE & 0xFD subtype ROE packets. Ignored by
                                                                 ROE subtype 0xFC. 0xFC subtype never writes the JD. */
        uint64_t reserved_51           : 1;
        uint64_t pkt_offset            : 3;  /**< [ 54: 52](R/W) Packet offset in units of 128-bits. DMA operation starts at START_ADDDR + [PKT_OFFSET]*16 bytes.
                                                                 Must be \<= 4. If [PKT_STATUS_WRITE]=1, must be \> 0 or the packet
                                                                 status write will over-write the packet data.

                                                                 Internal:
                                                                 Hardware should support values 5..7, but can't guarantee behavior. */
        uint64_t reserved_55           : 1;
        uint64_t dswap                 : 3;  /**< [ 58: 56](R/W) The byte swap mode for JDW to LLC/DRAM. JDW to BPHY SMEM ignores this field.
                                                                 Enumerated by MHBW_PNB_DSWAP_E. */
        uint64_t reserved_59           : 1;
        uint64_t cmd_type              : 2;  /**< [ 61: 60](R/W) Deprecated.  Hardware does not use.
                                                                 Internal:
                                                                 Specifies the CMD_TYPE used by the JDW.  Used for the GAA write field dmat.
                                                                 Enumerated by MHBW_PNB_WR_CMD_E. */
        uint64_t reserved_62           : 1;
        uint64_t target_mem            : 1;  /**< [ 63: 63](R/W) Specifies the target memory for the address for the DMA's job descriptor write (JDW):
                                                                  0 = SMEM.
                                                                  1 = LLC/DRAM. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_ind_jdt_cfg0_s cn; */
};
typedef union bdk_rfoex_rx_ind_jdt_cfg0 bdk_rfoex_rx_ind_jdt_cfg0_t;

static inline uint64_t BDK_RFOEX_RX_IND_JDT_CFG0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_IND_JDT_CFG0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01c40ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_IND_JDT_CFG0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_IND_JDT_CFG0(a) bdk_rfoex_rx_ind_jdt_cfg0_t
#define bustype_BDK_RFOEX_RX_IND_JDT_CFG0(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_IND_JDT_CFG0(a) "RFOEX_RX_IND_JDT_CFG0"
#define busnum_BDK_RFOEX_RX_IND_JDT_CFG0(a) (a)
#define arguments_BDK_RFOEX_RX_IND_JDT_CFG0(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_ind_jdt_cfg1
 *
 * RFOE RX Job Descriptor Table Configuration One Register
 * Job descriptor table, additional configuration register one. This table determines
 * some details of IEE P1914.3/D3.0 sequence number tracking.
 *
 * This register indirectly accesses a table of 256 entries.
 *
 * Reads and writes to this register access the table entry specified by
 * RFOE()_RX_INDIRECT_INDEX[INDEX].
 *
 * Incoming packets select an JDT entry based on
 * RFOE()_RX_IND_FT()_CFG[FLOW_IDX].
 */
union bdk_rfoex_rx_ind_jdt_cfg1
{
    uint64_t u;
    struct bdk_rfoex_rx_ind_jdt_cfg1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_43_63        : 21;
        uint64_t pinc_prop             : 3;  /**< [ 42: 40](R/W) P1914D3 Table 4-3 seqNum configuration */
        uint64_t reserved_39           : 1;
        uint64_t qinc_prop             : 3;  /**< [ 38: 36](R/W) P1914D3 Table 4-3 seqNum configuration */
        uint64_t reserved_33_35        : 3;
        uint64_t order_info_type       : 1;  /**< [ 32: 32](R/W) Order info type enumerated by RFOE_ORDER_INFO_TYPE_E.
                                                                 0 = seqNum.
                                                                 1 = timeStamp.
                                                                 See IEEE P1914.3/D3. */
        uint64_t reserved_29_31        : 3;
        uint64_t accept_time_window    : 29; /**< [ 28:  0](R/W) Accept time window used when [ORDER_INFO_TYPE]=1.
                                                                 See IEEE P1914.3/D3. */
#else /* Word 0 - Little Endian */
        uint64_t accept_time_window    : 29; /**< [ 28:  0](R/W) Accept time window used when [ORDER_INFO_TYPE]=1.
                                                                 See IEEE P1914.3/D3. */
        uint64_t reserved_29_31        : 3;
        uint64_t order_info_type       : 1;  /**< [ 32: 32](R/W) Order info type enumerated by RFOE_ORDER_INFO_TYPE_E.
                                                                 0 = seqNum.
                                                                 1 = timeStamp.
                                                                 See IEEE P1914.3/D3. */
        uint64_t reserved_33_35        : 3;
        uint64_t qinc_prop             : 3;  /**< [ 38: 36](R/W) P1914D3 Table 4-3 seqNum configuration */
        uint64_t reserved_39           : 1;
        uint64_t pinc_prop             : 3;  /**< [ 42: 40](R/W) P1914D3 Table 4-3 seqNum configuration */
        uint64_t reserved_43_63        : 21;
#endif /* Word 0 - End */
    } s;
    struct bdk_rfoex_rx_ind_jdt_cfg1_cn
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_57_63        : 7;
        uint64_t reserved_52_56        : 5;
        uint64_t reserved_49_51        : 3;
        uint64_t reserved_44_48        : 5;
        uint64_t reserved_43           : 1;
        uint64_t pinc_prop             : 3;  /**< [ 42: 40](R/W) P1914D3 Table 4-3 seqNum configuration */
        uint64_t reserved_39           : 1;
        uint64_t qinc_prop             : 3;  /**< [ 38: 36](R/W) P1914D3 Table 4-3 seqNum configuration */
        uint64_t reserved_33_35        : 3;
        uint64_t order_info_type       : 1;  /**< [ 32: 32](R/W) Order info type enumerated by RFOE_ORDER_INFO_TYPE_E.
                                                                 0 = seqNum.
                                                                 1 = timeStamp.
                                                                 See IEEE P1914.3/D3. */
        uint64_t reserved_29_31        : 3;
        uint64_t accept_time_window    : 29; /**< [ 28:  0](R/W) Accept time window used when [ORDER_INFO_TYPE]=1.
                                                                 See IEEE P1914.3/D3. */
#else /* Word 0 - Little Endian */
        uint64_t accept_time_window    : 29; /**< [ 28:  0](R/W) Accept time window used when [ORDER_INFO_TYPE]=1.
                                                                 See IEEE P1914.3/D3. */
        uint64_t reserved_29_31        : 3;
        uint64_t order_info_type       : 1;  /**< [ 32: 32](R/W) Order info type enumerated by RFOE_ORDER_INFO_TYPE_E.
                                                                 0 = seqNum.
                                                                 1 = timeStamp.
                                                                 See IEEE P1914.3/D3. */
        uint64_t reserved_33_35        : 3;
        uint64_t qinc_prop             : 3;  /**< [ 38: 36](R/W) P1914D3 Table 4-3 seqNum configuration */
        uint64_t reserved_39           : 1;
        uint64_t pinc_prop             : 3;  /**< [ 42: 40](R/W) P1914D3 Table 4-3 seqNum configuration */
        uint64_t reserved_43           : 1;
        uint64_t reserved_44_48        : 5;
        uint64_t reserved_49_51        : 3;
        uint64_t reserved_52_56        : 5;
        uint64_t reserved_57_63        : 7;
#endif /* Word 0 - End */
    } cn;
};
typedef union bdk_rfoex_rx_ind_jdt_cfg1 bdk_rfoex_rx_ind_jdt_cfg1_t;

static inline uint64_t BDK_RFOEX_RX_IND_JDT_CFG1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_IND_JDT_CFG1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01c48ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_IND_JDT_CFG1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_IND_JDT_CFG1(a) bdk_rfoex_rx_ind_jdt_cfg1_t
#define bustype_BDK_RFOEX_RX_IND_JDT_CFG1(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_IND_JDT_CFG1(a) "RFOEX_RX_IND_JDT_CFG1"
#define busnum_BDK_RFOEX_RX_IND_JDT_CFG1(a) (a)
#define arguments_BDK_RFOEX_RX_IND_JDT_CFG1(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_ind_jdt_psm_w0
 *
 * RFOE RX Job Descriptor Table PSM CMD Word0 Register
 * Job descriptor table, PSM command word.
 *
 * RFOE()_RX_IND_JDT_PSM_W0 and RFOE()_RX_IND_JDT_PSM_W1 store a 128-bit PSM
 * command that is submitted when an RX packet arrives, and
 * RFOE()_RX_IND_JDT_CFG0[JCA_ENABLE]=1.
 *
 * In addition, RFOE replaces some fields when the ROE packet subtype is not 0xFC.
 *
 * If the OPCODE is PSM_OPCODE_E::PSM_OP_ADDJOB or PSM_OPCODE_E::PSM_OP_CONTJOB, then RFOE
 * replaces PSM_CMD_ADDJOB_S[TMEM] with RFOE()_RX_IND_JDT_CFG0[TARGET_MEM], replaces
 * PSM_CMD_ADDJOB_S[JOBPTR] with a pointer to the job descriptor allocated
 * from the job descriptor buffer, and replaces PSM_CMD_ADDJOB_S[JOBTAG] with a
 * calculated jobtag defined by
 * RFOE()_RX_JCA_ADDJOB_JOBTAG.
 *
 * If the OPCODE is PSM_OPCODE_E::PSM_OP_ADDWORK, then RFOE will  replace
 * PSM_CMD_ADDWORK_S[WQEPTR] with a pointer to the job descriptor allocated
 * from the job descriptor buffer.
 *
 * For other OPCODE values, RFOE does no replacements for fields defined in the PSM CMD words.
 *
 * This register indirectly accesses a table of 256 entries.
 *
 * Reads and writes to this register access the table entry specified by
 * RFOE()_RX_INDIRECT_INDEX[INDEX].
 *
 * Incoming packets select an JDT entry based on
 * RFOE()_RX_IND_FT()_CFG[FLOW_IDX].
 */
union bdk_rfoex_rx_ind_jdt_psm_w0
{
    uint64_t u;
    struct bdk_rfoex_rx_ind_jdt_psm_w0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t w0                    : 64; /**< [ 63:  0](R/W) PSM command word 0. See PSM_CMD_* structure definitions. */
#else /* Word 0 - Little Endian */
        uint64_t w0                    : 64; /**< [ 63:  0](R/W) PSM command word 0. See PSM_CMD_* structure definitions. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_ind_jdt_psm_w0_s cn; */
};
typedef union bdk_rfoex_rx_ind_jdt_psm_w0 bdk_rfoex_rx_ind_jdt_psm_w0_t;

static inline uint64_t BDK_RFOEX_RX_IND_JDT_PSM_W0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_IND_JDT_PSM_W0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01c58ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_IND_JDT_PSM_W0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_IND_JDT_PSM_W0(a) bdk_rfoex_rx_ind_jdt_psm_w0_t
#define bustype_BDK_RFOEX_RX_IND_JDT_PSM_W0(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_IND_JDT_PSM_W0(a) "RFOEX_RX_IND_JDT_PSM_W0"
#define busnum_BDK_RFOEX_RX_IND_JDT_PSM_W0(a) (a)
#define arguments_BDK_RFOEX_RX_IND_JDT_PSM_W0(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_ind_jdt_psm_w1
 *
 * RFOE RX Job Descriptor Table PSM CMD Word1 Register
 * See RFOE()_RX_IND_JDT_PSM_W0.
 */
union bdk_rfoex_rx_ind_jdt_psm_w1
{
    uint64_t u;
    struct bdk_rfoex_rx_ind_jdt_psm_w1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t w1                    : 64; /**< [ 63:  0](R/W) PSM command word 1. See PSM_CMD_* structure definitions. */
#else /* Word 0 - Little Endian */
        uint64_t w1                    : 64; /**< [ 63:  0](R/W) PSM command word 1. See PSM_CMD_* structure definitions. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_ind_jdt_psm_w1_s cn; */
};
typedef union bdk_rfoex_rx_ind_jdt_psm_w1 bdk_rfoex_rx_ind_jdt_psm_w1_t;

static inline uint64_t BDK_RFOEX_RX_IND_JDT_PSM_W1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_IND_JDT_PSM_W1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01c60ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_IND_JDT_PSM_W1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_IND_JDT_PSM_W1(a) bdk_rfoex_rx_ind_jdt_psm_w1_t
#define bustype_BDK_RFOEX_RX_IND_JDT_PSM_W1(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_IND_JDT_PSM_W1(a) "RFOEX_RX_IND_JDT_PSM_W1"
#define busnum_BDK_RFOEX_RX_IND_JDT_PSM_W1(a) (a)
#define arguments_BDK_RFOEX_RX_IND_JDT_PSM_W1(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_ind_jdt_ptr
 *
 * RFOE RX Job Descriptor Table Pointer Register
 * Job descriptor table, job descriptor pointer register. This table
 * configures the location of job descriptors to submit when receiving packets.
 *
 * This register indirectly accesses a table of 256 entries.
 *
 * Reads and writes to this register access the table entry specified by
 * RFOE()_RX_INDIRECT_INDEX[INDEX].
 *
 * Incoming packets select an JDT entry based on
 * RFOE()_RX_IND_FT()_CFG[FLOW_IDX].
 */
union bdk_rfoex_rx_ind_jdt_ptr
{
    uint64_t u;
    struct bdk_rfoex_rx_ind_jdt_ptr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ptr                   : 53; /**< [ 52:  0](R/W) Byte address of first job descriptor in job descriptor buffer.
                                                                 * [PTR]+(RFOE()_RX_IND_JDT_CFG0[JD_RD_OFFSET]*8) must be 128-bit aligned. */
#else /* Word 0 - Little Endian */
        uint64_t ptr                   : 53; /**< [ 52:  0](R/W) Byte address of first job descriptor in job descriptor buffer.
                                                                 * [PTR]+(RFOE()_RX_IND_JDT_CFG0[JD_RD_OFFSET]*8) must be 128-bit aligned. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_ind_jdt_ptr_s cn; */
};
typedef union bdk_rfoex_rx_ind_jdt_ptr bdk_rfoex_rx_ind_jdt_ptr_t;

static inline uint64_t BDK_RFOEX_RX_IND_JDT_PTR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_IND_JDT_PTR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01c50ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_IND_JDT_PTR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_IND_JDT_PTR(a) bdk_rfoex_rx_ind_jdt_ptr_t
#define bustype_BDK_RFOEX_RX_IND_JDT_PTR(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_IND_JDT_PTR(a) "RFOEX_RX_IND_JDT_PTR"
#define busnum_BDK_RFOEX_RX_IND_JDT_PTR(a) (a)
#define arguments_BDK_RFOEX_RX_IND_JDT_PTR(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_ind_jdt_seqnum_p_cfg
 *
 * RFOE RX Indirect Job Descriptor Table SeqNum P-Counter Configuration Register
 * Job descriptor table, seqNum p-counter configuration. This table
 * configures the IEEE P1914.3/D3.0 seqNum p-counter parameters.
 *
 * This register indirectly accesses a table of 256 entries.
 *
 * Reads and writes to this register access the table entry specified by
 * RFOE()_RX_INDIRECT_INDEX[INDEX].
 *
 * Incoming packets select an JDT entry based on
 * RFOE()_RX_IND_FT()_CFG[FLOW_IDX].
 */
union bdk_rfoex_rx_ind_jdt_seqnum_p_cfg
{
    uint64_t u;
    struct bdk_rfoex_rx_ind_jdt_seqnum_p_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pinc                  : 32; /**< [ 63: 32](R/W) Value to increment the p-counter by on each packet.
                                                                 The increment value must be less than RFOE()_RX_IND_SEQNUM_P_CFG[PMAX]. */
        uint64_t pmax                  : 32; /**< [ 31:  0](R/W) seqNum PMax. Maximum numerical value of the p-counter field. Requirements:
                                                                 *[PMAX] \> [PINC] when RFOE()_RX_IND_JDT_CFG1[PINC_PROP] == 1.
                                                                 *[PMAX] \>= Initial RFOE()_RX_IND_JDT_SEQNUM_STATE[PVAL].
                                                                 *[PMAX] \> Maximum RoE length field when RFOE()_RX_IND_JDT_CFG1[PINC_PROP] == 2.
                                                                 *[PMAX] \<= 3 when (RFOE()_RX_IND_JDT_CFG1[ORDER_INFO_TYPE] == TIMESTAMP). */
#else /* Word 0 - Little Endian */
        uint64_t pmax                  : 32; /**< [ 31:  0](R/W) seqNum PMax. Maximum numerical value of the p-counter field. Requirements:
                                                                 *[PMAX] \> [PINC] when RFOE()_RX_IND_JDT_CFG1[PINC_PROP] == 1.
                                                                 *[PMAX] \>= Initial RFOE()_RX_IND_JDT_SEQNUM_STATE[PVAL].
                                                                 *[PMAX] \> Maximum RoE length field when RFOE()_RX_IND_JDT_CFG1[PINC_PROP] == 2.
                                                                 *[PMAX] \<= 3 when (RFOE()_RX_IND_JDT_CFG1[ORDER_INFO_TYPE] == TIMESTAMP). */
        uint64_t pinc                  : 32; /**< [ 63: 32](R/W) Value to increment the p-counter by on each packet.
                                                                 The increment value must be less than RFOE()_RX_IND_SEQNUM_P_CFG[PMAX]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_ind_jdt_seqnum_p_cfg_s cn; */
};
typedef union bdk_rfoex_rx_ind_jdt_seqnum_p_cfg bdk_rfoex_rx_ind_jdt_seqnum_p_cfg_t;

static inline uint64_t BDK_RFOEX_RX_IND_JDT_SEQNUM_P_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_IND_JDT_SEQNUM_P_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01c68ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_IND_JDT_SEQNUM_P_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_IND_JDT_SEQNUM_P_CFG(a) bdk_rfoex_rx_ind_jdt_seqnum_p_cfg_t
#define bustype_BDK_RFOEX_RX_IND_JDT_SEQNUM_P_CFG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_IND_JDT_SEQNUM_P_CFG(a) "RFOEX_RX_IND_JDT_SEQNUM_P_CFG"
#define busnum_BDK_RFOEX_RX_IND_JDT_SEQNUM_P_CFG(a) (a)
#define arguments_BDK_RFOEX_RX_IND_JDT_SEQNUM_P_CFG(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_ind_jdt_seqnum_q_cfg
 *
 * RFOE RX Indirect Job Descriptor Table SeqNum Q-Counter Configuration Register
 * Job descriptor table, seqNum p-counter configuration. This table
 * configures the IEEE P1914.3/D3.0 seqNum q-counter parameters.
 *
 * This register indirectly accesses a table of 256 entries.
 *
 * Reads and writes to this register access the table entry specified by
 * RFOE()_RX_INDIRECT_INDEX[INDEX].
 *
 * Incoming packets select an JDT entry based on
 * RFOE()_RX_IND_FT()_CFG[FLOW_IDX].
 */
union bdk_rfoex_rx_ind_jdt_seqnum_q_cfg
{
    uint64_t u;
    struct bdk_rfoex_rx_ind_jdt_seqnum_q_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t qinc                  : 32; /**< [ 63: 32](R/W) Value to increment q-counter by on each p-counter wrap event.
                                                                 The increment value must be less than RFOE()_RX_IND_SEQNUM_Q_CFG[QMAX]. */
        uint64_t qmax                  : 32; /**< [ 31:  0](R/W) seqNum QMax. Maximum numerical value of the q-counter field. Requirements:
                                                                 * [QMAX] \> [QINC] when RFOE()_RX_IND_JDT_CFG1[QINC_PROP] == 1.
                                                                 * [QMAX] \>= Initial RFOE()_RX_IND_JDT_SEQNUM_STATE[QVAL].
                                                                 * [QMAX] should be 0 when RFOE()_RX_IND_JDT_CFG1[ORDER_INFO_TYPE] == TIMESTAMP. */
#else /* Word 0 - Little Endian */
        uint64_t qmax                  : 32; /**< [ 31:  0](R/W) seqNum QMax. Maximum numerical value of the q-counter field. Requirements:
                                                                 * [QMAX] \> [QINC] when RFOE()_RX_IND_JDT_CFG1[QINC_PROP] == 1.
                                                                 * [QMAX] \>= Initial RFOE()_RX_IND_JDT_SEQNUM_STATE[QVAL].
                                                                 * [QMAX] should be 0 when RFOE()_RX_IND_JDT_CFG1[ORDER_INFO_TYPE] == TIMESTAMP. */
        uint64_t qinc                  : 32; /**< [ 63: 32](R/W) Value to increment q-counter by on each p-counter wrap event.
                                                                 The increment value must be less than RFOE()_RX_IND_SEQNUM_Q_CFG[QMAX]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_ind_jdt_seqnum_q_cfg_s cn; */
};
typedef union bdk_rfoex_rx_ind_jdt_seqnum_q_cfg bdk_rfoex_rx_ind_jdt_seqnum_q_cfg_t;

static inline uint64_t BDK_RFOEX_RX_IND_JDT_SEQNUM_Q_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_IND_JDT_SEQNUM_Q_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01c70ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_IND_JDT_SEQNUM_Q_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_IND_JDT_SEQNUM_Q_CFG(a) bdk_rfoex_rx_ind_jdt_seqnum_q_cfg_t
#define bustype_BDK_RFOEX_RX_IND_JDT_SEQNUM_Q_CFG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_IND_JDT_SEQNUM_Q_CFG(a) "RFOEX_RX_IND_JDT_SEQNUM_Q_CFG"
#define busnum_BDK_RFOEX_RX_IND_JDT_SEQNUM_Q_CFG(a) (a)
#define arguments_BDK_RFOEX_RX_IND_JDT_SEQNUM_Q_CFG(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_ind_jdt_seqnum_state
 *
 * RFOE RX Job Descriptor Table SEQNUM STATE Register
 * Job descriptor table, seqNum state. This table
 * reports the current values of the IEEE P1914.3/D3.0 sequence numbers for
 * this flow.
 *
 * This register indirectly accesses a table of 256 entries.
 *
 * Reads and writes to this register access the table entry specified by
 * RFOE()_RX_INDIRECT_INDEX[INDEX].
 *
 * Incoming packets select an JDT entry based on
 * RFOE()_RX_IND_FT()_CFG[FLOW_IDX].
 */
union bdk_rfoex_rx_ind_jdt_seqnum_state
{
    uint64_t u;
    struct bdk_rfoex_rx_ind_jdt_seqnum_state_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pval                  : 32; /**< [ 63: 32](R/W/H) SeqNum p-counter value.
                                                                 The initial value must be less than or equal to RFOE()_RX_IND_JDT_SEQNUM_P_CFG[PMAX]. */
        uint64_t qval                  : 32; /**< [ 31:  0](R/W/H) SeqNum q-counter value.
                                                                 The initial value must be less than or equal to RFOE()_RX_IND_JDT_SEQNUM_Q_CFG[QMAX].
                                                                 Contents are valid for seqNum mode (RFOE()_RX_IND_JDT_CFG1[ORDER_INFO_TYPE] == SEQNUM).

                                                                 Internal:
                                                                 RFOE_RX_IND_JDT_CFG1[ORDER_INFO_TYPE] == TIMESTAMP, then QVAL will be 0. */
#else /* Word 0 - Little Endian */
        uint64_t qval                  : 32; /**< [ 31:  0](R/W/H) SeqNum q-counter value.
                                                                 The initial value must be less than or equal to RFOE()_RX_IND_JDT_SEQNUM_Q_CFG[QMAX].
                                                                 Contents are valid for seqNum mode (RFOE()_RX_IND_JDT_CFG1[ORDER_INFO_TYPE] == SEQNUM).

                                                                 Internal:
                                                                 RFOE_RX_IND_JDT_CFG1[ORDER_INFO_TYPE] == TIMESTAMP, then QVAL will be 0. */
        uint64_t pval                  : 32; /**< [ 63: 32](R/W/H) SeqNum p-counter value.
                                                                 The initial value must be less than or equal to RFOE()_RX_IND_JDT_SEQNUM_P_CFG[PMAX]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_ind_jdt_seqnum_state_s cn; */
};
typedef union bdk_rfoex_rx_ind_jdt_seqnum_state bdk_rfoex_rx_ind_jdt_seqnum_state_t;

static inline uint64_t BDK_RFOEX_RX_IND_JDT_SEQNUM_STATE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_IND_JDT_SEQNUM_STATE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01c80ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_IND_JDT_SEQNUM_STATE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_IND_JDT_SEQNUM_STATE(a) bdk_rfoex_rx_ind_jdt_seqnum_state_t
#define bustype_BDK_RFOEX_RX_IND_JDT_SEQNUM_STATE(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_IND_JDT_SEQNUM_STATE(a) "RFOEX_RX_IND_JDT_SEQNUM_STATE"
#define busnum_BDK_RFOEX_RX_IND_JDT_SEQNUM_STATE(a) (a)
#define arguments_BDK_RFOEX_RX_IND_JDT_SEQNUM_STATE(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_ind_jdt_state
 *
 * RFOE RX Job Descriptor Table State Register
 * Job descriptor table, next job descriptor state. This table tracks the
 * location of the next job descriptor for the given flow.
 *
 * This register indirectly accesses a table of 256 entries.
 *
 * Reads and writes to this register access the table entry specified by
 * RFOE()_RX_INDIRECT_INDEX[INDEX].
 *
 * Incoming packets select an JDT entry based on
 * RFOE()_RX_IND_FT()_CFG[FLOW_IDX].
 */
union bdk_rfoex_rx_ind_jdt_state
{
    uint64_t u;
    struct bdk_rfoex_rx_ind_jdt_state_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t nxt_jd                : 16; /**< [ 15:  0](R/W/H) Pointer to the next job descriptor in the circular buffer. */
#else /* Word 0 - Little Endian */
        uint64_t nxt_jd                : 16; /**< [ 15:  0](R/W/H) Pointer to the next job descriptor in the circular buffer. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_ind_jdt_state_s cn; */
};
typedef union bdk_rfoex_rx_ind_jdt_state bdk_rfoex_rx_ind_jdt_state_t;

static inline uint64_t BDK_RFOEX_RX_IND_JDT_STATE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_IND_JDT_STATE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01c78ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_IND_JDT_STATE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_IND_JDT_STATE(a) bdk_rfoex_rx_ind_jdt_state_t
#define bustype_BDK_RFOEX_RX_IND_JDT_STATE(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_IND_JDT_STATE(a) "RFOEX_RX_IND_JDT_STATE"
#define busnum_BDK_RFOEX_RX_IND_JDT_STATE(a) (a)
#define arguments_BDK_RFOEX_RX_IND_JDT_STATE(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_ind_mbt_addr
 *
 * RFOE RX Memory Buffer Table Address  Register
 * Memory buffer configuration table.
 *
 * This register indirectly accesses a table of 64 entries.
 *
 * Reads and writes to this register access the table entry specified by
 * RFOE()_RX_INDIRECT_INDEX[INDEX].
 *
 * Incoming packets select an MBT entry based on RFOE()_RX_IND_FT()_CFG[MBT_IDX].
 */
union bdk_rfoex_rx_ind_mbt_addr
{
    uint64_t u;
    struct bdk_rfoex_rx_ind_mbt_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t buf_addr              : 53; /**< [ 52:  0](R/W) Byte address of the start of the circular buffer for this MBT entry. Must:
                                                                 _ RFOE()_RX_IND_MBT_CFG[TARGET_MEM]==0 - 128-bit aligned--bottom four bits
                                                                 BUF_ADDR\<3:0\> must be 0x0.
                                                                 _ RFOE()_RX_IND_MBT_CFG[TARGET_MEM]==1 - Must be aligned to cache line--bottom seven bits
                                                                 BUF_ADDR\<6:0\> must be 0x00. */
#else /* Word 0 - Little Endian */
        uint64_t buf_addr              : 53; /**< [ 52:  0](R/W) Byte address of the start of the circular buffer for this MBT entry. Must:
                                                                 _ RFOE()_RX_IND_MBT_CFG[TARGET_MEM]==0 - 128-bit aligned--bottom four bits
                                                                 BUF_ADDR\<3:0\> must be 0x0.
                                                                 _ RFOE()_RX_IND_MBT_CFG[TARGET_MEM]==1 - Must be aligned to cache line--bottom seven bits
                                                                 BUF_ADDR\<6:0\> must be 0x00. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_ind_mbt_addr_s cn; */
};
typedef union bdk_rfoex_rx_ind_mbt_addr bdk_rfoex_rx_ind_mbt_addr_t;

static inline uint64_t BDK_RFOEX_RX_IND_MBT_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_IND_MBT_ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01c28ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_IND_MBT_ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_IND_MBT_ADDR(a) bdk_rfoex_rx_ind_mbt_addr_t
#define bustype_BDK_RFOEX_RX_IND_MBT_ADDR(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_IND_MBT_ADDR(a) "RFOEX_RX_IND_MBT_ADDR"
#define busnum_BDK_RFOEX_RX_IND_MBT_ADDR(a) (a)
#define arguments_BDK_RFOEX_RX_IND_MBT_ADDR(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_ind_mbt_cfg
 *
 * RFOE RX Indirect Memory Buffer Table Configuration Register
 * Memory buffer configuration table.
 *
 * This register indirectly accesses a table of 64 entries.
 *
 * Reads and writes to this register access the table entry specified by
 * RFOE()_RX_INDIRECT_INDEX[INDEX].
 *
 * Incoming packets select an MBT entry based on RFOE()_RX_IND_FT()_CFG[MBT_IDX].
 */
union bdk_rfoex_rx_ind_mbt_cfg
{
    uint64_t u;
    struct bdk_rfoex_rx_ind_mbt_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t target_mem            : 1;  /**< [ 63: 63](R/W) Specifies the target memory for the address.
                                                                 0 = SMEM.
                                                                 1 = LLC/DRAM. */
        uint64_t reserved_62           : 1;
        uint64_t cmd_type              : 2;  /**< [ 61: 60](R/W) Command type for LLC/DRAM writes, enumerated by MHBW_PNB_WR_CMD_E.

                                                                 Note:
                                                                 * Writes to BPHY SMEM ignore this field.
                                                                 * Unaligned or partial cacheline writes use MHBW_PNB_WR_CMD_E::STP.

                                                                 Internal:
                                                                 Notes:
                                                                 *BPHY DDR Hardware DMA replaces this field with STP for unaligned cache line
                                                                 starts. All transfers for this burst will be STP.
                                                                 *BPHY DDR Hardware DMA replaces this field with STP for the last transfer in a burst if unaligned. */
        uint64_t reserved_59           : 1;
        uint64_t dswap                 : 3;  /**< [ 58: 56](R/W) The byte swap mode for DMA to LLC/DRAM. Enumerated in MHBW_PNB_DSWAP_E.
                                                                 DMA to BPHY SMEM ignores this field. */
        uint64_t reserved_48_55        : 8;
        uint64_t nxt_buf               : 16; /**< [ 47: 32](R/W/H) Buffer number that the next packet will use to write DMA.
                                                                 Address of this buffer is [NXT_BUF]*[BUF_SIZE] + RFOE(0..1)_RX_IND_MBT_ADDR[BUF_ADDR]
                                                                 NXT_BUF is reset by BIST clear or writing 0. */
        uint64_t buf_size              : 16; /**< [ 31: 16](R/W) Size of each buffer, in units of 128 bits. Must:
                                                                 _ [BUF_SIZE] \<= 0x3FFF.
                                                                 _ [BUF_SIZE] \>= 0x0010.
                                                                 _ [TARGET_MEM]==1 - Must be aligned to cache line--bottom three bits
                                                                 BUF_SIZE\<2:0\> must be 0x0.

                                                                 Internal:
                                                                 Max of 0x3fff is job descriptor BLOCK_SIZE limit. */
        uint64_t num_buf               : 16; /**< [ 15:  0](R/W) Number of buffers in circular buffer. Must be greater than 0.
                                                                 Internal:
                                                                 Hardware interprets [NUM_BUF]=0 the same as [NUM_BUF]=1.  [NUM_BUF]=0 is nonsensical. */
#else /* Word 0 - Little Endian */
        uint64_t num_buf               : 16; /**< [ 15:  0](R/W) Number of buffers in circular buffer. Must be greater than 0.
                                                                 Internal:
                                                                 Hardware interprets [NUM_BUF]=0 the same as [NUM_BUF]=1.  [NUM_BUF]=0 is nonsensical. */
        uint64_t buf_size              : 16; /**< [ 31: 16](R/W) Size of each buffer, in units of 128 bits. Must:
                                                                 _ [BUF_SIZE] \<= 0x3FFF.
                                                                 _ [BUF_SIZE] \>= 0x0010.
                                                                 _ [TARGET_MEM]==1 - Must be aligned to cache line--bottom three bits
                                                                 BUF_SIZE\<2:0\> must be 0x0.

                                                                 Internal:
                                                                 Max of 0x3fff is job descriptor BLOCK_SIZE limit. */
        uint64_t nxt_buf               : 16; /**< [ 47: 32](R/W/H) Buffer number that the next packet will use to write DMA.
                                                                 Address of this buffer is [NXT_BUF]*[BUF_SIZE] + RFOE(0..1)_RX_IND_MBT_ADDR[BUF_ADDR]
                                                                 NXT_BUF is reset by BIST clear or writing 0. */
        uint64_t reserved_48_55        : 8;
        uint64_t dswap                 : 3;  /**< [ 58: 56](R/W) The byte swap mode for DMA to LLC/DRAM. Enumerated in MHBW_PNB_DSWAP_E.
                                                                 DMA to BPHY SMEM ignores this field. */
        uint64_t reserved_59           : 1;
        uint64_t cmd_type              : 2;  /**< [ 61: 60](R/W) Command type for LLC/DRAM writes, enumerated by MHBW_PNB_WR_CMD_E.

                                                                 Note:
                                                                 * Writes to BPHY SMEM ignore this field.
                                                                 * Unaligned or partial cacheline writes use MHBW_PNB_WR_CMD_E::STP.

                                                                 Internal:
                                                                 Notes:
                                                                 *BPHY DDR Hardware DMA replaces this field with STP for unaligned cache line
                                                                 starts. All transfers for this burst will be STP.
                                                                 *BPHY DDR Hardware DMA replaces this field with STP for the last transfer in a burst if unaligned. */
        uint64_t reserved_62           : 1;
        uint64_t target_mem            : 1;  /**< [ 63: 63](R/W) Specifies the target memory for the address.
                                                                 0 = SMEM.
                                                                 1 = LLC/DRAM. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_ind_mbt_cfg_s cn; */
};
typedef union bdk_rfoex_rx_ind_mbt_cfg bdk_rfoex_rx_ind_mbt_cfg_t;

static inline uint64_t BDK_RFOEX_RX_IND_MBT_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_IND_MBT_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01c20ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_IND_MBT_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_IND_MBT_CFG(a) bdk_rfoex_rx_ind_mbt_cfg_t
#define bustype_BDK_RFOEX_RX_IND_MBT_CFG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_IND_MBT_CFG(a) "RFOEX_RX_IND_MBT_CFG"
#define busnum_BDK_RFOEX_RX_IND_MBT_CFG(a) (a)
#define arguments_BDK_RFOEX_RX_IND_MBT_CFG(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_ind_mbt_seg_state
 *
 * RFOE RX Indirect Memory Buffer Table Segmentation Register
 * Memory buffer table segmentation configuration and state.
 *
 * This register indirectly accesses a table of 64 entries.
 *
 * Reads and writes to this register access the table entry specified by
 * RFOE()_RX_INDIRECT_INDEX[INDEX].
 *
 * Incoming packets select an MBT entry based on RFOE()_RX_IND_FT()_CFG[MBT_IDX].
 */
union bdk_rfoex_rx_ind_mbt_seg_state
{
    uint64_t u;
    struct bdk_rfoex_rx_ind_mbt_seg_state_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t orderinfo_status      : 1;  /**< [ 21: 21](R/W/H) Result of most recent orderInfo comparison.
                                                                 0 = Fail. Bad SeqNum or timestamp.
                                                                 1 = Pass. Good SeqNum or timestamp. */
        uint64_t dma_error             : 1;  /**< [ 20: 20](R/W/H) Error occurred during header processing or DMA. Possible errors
                                                                 include:
                                                                 * Late aperture failure.
                                                                 * Attempted to write past the end of the buffer (i.e., packet(s) larger
                                                                 than buffer size).
                                                                 * RoE length field didn't match incoming packet size. */
        uint64_t packet_status         : 4;  /**< [ 19: 16](R/W/H) Packet error status, enumerated by RFOE_RX_PKT_ERR_E. */
        uint64_t offset                : 16; /**< [ 15:  0](R/W/H) Offset within buffer where next segment will be stored, in units of
                                                                 128-bits. */
#else /* Word 0 - Little Endian */
        uint64_t offset                : 16; /**< [ 15:  0](R/W/H) Offset within buffer where next segment will be stored, in units of
                                                                 128-bits. */
        uint64_t packet_status         : 4;  /**< [ 19: 16](R/W/H) Packet error status, enumerated by RFOE_RX_PKT_ERR_E. */
        uint64_t dma_error             : 1;  /**< [ 20: 20](R/W/H) Error occurred during header processing or DMA. Possible errors
                                                                 include:
                                                                 * Late aperture failure.
                                                                 * Attempted to write past the end of the buffer (i.e., packet(s) larger
                                                                 than buffer size).
                                                                 * RoE length field didn't match incoming packet size. */
        uint64_t orderinfo_status      : 1;  /**< [ 21: 21](R/W/H) Result of most recent orderInfo comparison.
                                                                 0 = Fail. Bad SeqNum or timestamp.
                                                                 1 = Pass. Good SeqNum or timestamp. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_ind_mbt_seg_state_s cn; */
};
typedef union bdk_rfoex_rx_ind_mbt_seg_state bdk_rfoex_rx_ind_mbt_seg_state_t;

static inline uint64_t BDK_RFOEX_RX_IND_MBT_SEG_STATE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_IND_MBT_SEG_STATE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01c30ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_IND_MBT_SEG_STATE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_IND_MBT_SEG_STATE(a) bdk_rfoex_rx_ind_mbt_seg_state_t
#define bustype_BDK_RFOEX_RX_IND_MBT_SEG_STATE(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_IND_MBT_SEG_STATE(a) "RFOEX_RX_IND_MBT_SEG_STATE"
#define busnum_BDK_RFOEX_RX_IND_MBT_SEG_STATE(a) (a)
#define arguments_BDK_RFOEX_RX_IND_MBT_SEG_STATE(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_indirect_index
 *
 * RFOE RX Indirect Index Register
 * Index for reading and writing RFOE RX configuration tables.
 */
union bdk_rfoex_rx_indirect_index
{
    uint64_t u;
    struct bdk_rfoex_rx_indirect_index_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t index                 : 16; /**< [ 15:  0](R/W) Index used to select entry in RFOE()_RX_IND_* structures. */
#else /* Word 0 - Little Endian */
        uint64_t index                 : 16; /**< [ 15:  0](R/W) Index used to select entry in RFOE()_RX_IND_* structures. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_indirect_index_s cn; */
};
typedef union bdk_rfoex_rx_indirect_index bdk_rfoex_rx_indirect_index_t;

static inline uint64_t BDK_RFOEX_RX_INDIRECT_INDEX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_INDIRECT_INDEX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01bf8ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_INDIRECT_INDEX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_INDIRECT_INDEX(a) bdk_rfoex_rx_indirect_index_t
#define bustype_BDK_RFOEX_RX_INDIRECT_INDEX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_INDIRECT_INDEX(a) "RFOEX_RX_INDIRECT_INDEX"
#define busnum_BDK_RFOEX_RX_INDIRECT_INDEX(a) (a)
#define arguments_BDK_RFOEX_RX_INDIRECT_INDEX(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_jca_addjob_jobtag
 *
 * RFOE RX JCA ADDJOB Message Jobtag Configuration  Register
 * Defines value RFOE send for the PSM_CMD_ADDJOB_S[JOBTAG] and
 * PSM_CMD_CONTJOB_S[JOBTAG] values when sending new job commands to PSM.
 * Not used for ROE 0xfc subtypes.
 * For the command [JOBTAG]:
 * _ command[JOBTAG] = ([BASE] & (0xffff \<\< [MASK_WIDTH])) | ([COUNT] & ~(0xffff \<\< [MASK_WIDTH]))
 */
union bdk_rfoex_rx_jca_addjob_jobtag
{
    uint64_t u;
    struct bdk_rfoex_rx_jca_addjob_jobtag_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t count                 : 16; /**< [ 47: 32](R/W/H) Current counter value.  Increments on every non-0xfc subtype ADDJOB
                                                                 and CONTJOB command sent to PSM. Counter increment wraps to 0 when current [COUNT] == 0xFFFF. */
        uint64_t reserved_21_31        : 11;
        uint64_t mask_width            : 5;  /**< [ 20: 16](R/W) Number of bits from counter to insert into lower bits of JOBTAG. */
        uint64_t base                  : 16; /**< [ 15:  0](R/W) Constant value part of the JOBTAG. */
#else /* Word 0 - Little Endian */
        uint64_t base                  : 16; /**< [ 15:  0](R/W) Constant value part of the JOBTAG. */
        uint64_t mask_width            : 5;  /**< [ 20: 16](R/W) Number of bits from counter to insert into lower bits of JOBTAG. */
        uint64_t reserved_21_31        : 11;
        uint64_t count                 : 16; /**< [ 47: 32](R/W/H) Current counter value.  Increments on every non-0xfc subtype ADDJOB
                                                                 and CONTJOB command sent to PSM. Counter increment wraps to 0 when current [COUNT] == 0xFFFF. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_jca_addjob_jobtag_s cn; */
};
typedef union bdk_rfoex_rx_jca_addjob_jobtag bdk_rfoex_rx_jca_addjob_jobtag_t;

static inline uint64_t BDK_RFOEX_RX_JCA_ADDJOB_JOBTAG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_JCA_ADDJOB_JOBTAG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01030ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_JCA_ADDJOB_JOBTAG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_JCA_ADDJOB_JOBTAG(a) bdk_rfoex_rx_jca_addjob_jobtag_t
#define bustype_BDK_RFOEX_RX_JCA_ADDJOB_JOBTAG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_JCA_ADDJOB_JOBTAG(a) "RFOEX_RX_JCA_ADDJOB_JOBTAG"
#define busnum_BDK_RFOEX_RX_JCA_ADDJOB_JOBTAG(a) (a)
#define arguments_BDK_RFOEX_RX_JCA_ADDJOB_JOBTAG(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_orderinfo_fail_stat
 *
 * RFOE RX OrderInfo Fail  Statistic Register
 * Count of seqNum or timestamp (from RoE orderInfo field) failures. A failure is a
 * miscompare in seqNum or a time that is outside of the accepted time window.
 */
union bdk_rfoex_rx_orderinfo_fail_stat
{
    uint64_t u;
    struct bdk_rfoex_rx_orderinfo_fail_stat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) The counter value. Wraps to zero at 2^48. */
#else /* Word 0 - Little Endian */
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) The counter value. Wraps to zero at 2^48. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_orderinfo_fail_stat_s cn; */
};
typedef union bdk_rfoex_rx_orderinfo_fail_stat bdk_rfoex_rx_orderinfo_fail_stat_t;

static inline uint64_t BDK_RFOEX_RX_ORDERINFO_FAIL_STAT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_ORDERINFO_FAIL_STAT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01d40ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_ORDERINFO_FAIL_STAT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_ORDERINFO_FAIL_STAT(a) bdk_rfoex_rx_orderinfo_fail_stat_t
#define bustype_BDK_RFOEX_RX_ORDERINFO_FAIL_STAT(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_ORDERINFO_FAIL_STAT(a) "RFOEX_RX_ORDERINFO_FAIL_STAT"
#define busnum_BDK_RFOEX_RX_ORDERINFO_FAIL_STAT(a) (a)
#define arguments_BDK_RFOEX_RX_ORDERINFO_FAIL_STAT(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_ordinf_err_ena_w1c#
 *
 * RFOE RX OrderInfo Error Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_rfoex_rx_ordinf_err_ena_w1cx
{
    uint64_t u;
    struct bdk_rfoex_rx_ordinf_err_ena_w1cx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t orderinfo_miscompare  : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ORDINF_ERR_INT(0..3)[ORDERINFO_MISCOMPARE]. */
#else /* Word 0 - Little Endian */
        uint64_t orderinfo_miscompare  : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for RFOE(0..1)_RX_ORDINF_ERR_INT(0..3)[ORDERINFO_MISCOMPARE]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_ordinf_err_ena_w1cx_s cn; */
};
typedef union bdk_rfoex_rx_ordinf_err_ena_w1cx bdk_rfoex_rx_ordinf_err_ena_w1cx_t;

static inline uint64_t BDK_RFOEX_RX_ORDINF_ERR_ENA_W1CX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_ORDINF_ERR_ENA_W1CX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=3)))
        return 0x87e043d01e40ll + 0x80000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    __bdk_csr_fatal("RFOEX_RX_ORDINF_ERR_ENA_W1CX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_ORDINF_ERR_ENA_W1CX(a,b) bdk_rfoex_rx_ordinf_err_ena_w1cx_t
#define bustype_BDK_RFOEX_RX_ORDINF_ERR_ENA_W1CX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_ORDINF_ERR_ENA_W1CX(a,b) "RFOEX_RX_ORDINF_ERR_ENA_W1CX"
#define busnum_BDK_RFOEX_RX_ORDINF_ERR_ENA_W1CX(a,b) (a)
#define arguments_BDK_RFOEX_RX_ORDINF_ERR_ENA_W1CX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_rx_ordinf_err_ena_w1s#
 *
 * RFOE RX OrderInfo Error Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_rfoex_rx_ordinf_err_ena_w1sx
{
    uint64_t u;
    struct bdk_rfoex_rx_ordinf_err_ena_w1sx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t orderinfo_miscompare  : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ORDINF_ERR_INT(0..3)[ORDERINFO_MISCOMPARE]. */
#else /* Word 0 - Little Endian */
        uint64_t orderinfo_miscompare  : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for RFOE(0..1)_RX_ORDINF_ERR_INT(0..3)[ORDERINFO_MISCOMPARE]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_ordinf_err_ena_w1sx_s cn; */
};
typedef union bdk_rfoex_rx_ordinf_err_ena_w1sx bdk_rfoex_rx_ordinf_err_ena_w1sx_t;

static inline uint64_t BDK_RFOEX_RX_ORDINF_ERR_ENA_W1SX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_ORDINF_ERR_ENA_W1SX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=3)))
        return 0x87e043d01e20ll + 0x80000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    __bdk_csr_fatal("RFOEX_RX_ORDINF_ERR_ENA_W1SX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_ORDINF_ERR_ENA_W1SX(a,b) bdk_rfoex_rx_ordinf_err_ena_w1sx_t
#define bustype_BDK_RFOEX_RX_ORDINF_ERR_ENA_W1SX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_ORDINF_ERR_ENA_W1SX(a,b) "RFOEX_RX_ORDINF_ERR_ENA_W1SX"
#define busnum_BDK_RFOEX_RX_ORDINF_ERR_ENA_W1SX(a,b) (a)
#define arguments_BDK_RFOEX_RX_ORDINF_ERR_ENA_W1SX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_rx_ordinf_err_int#
 *
 * RFOE OrderInfo Error Interrupt Register
 * These registers record orderInfo miscompare for each flow.
 *
 * When an error occurs, RFOE sends message to PSM defined by
 * RFOE()_RX_ORDINF_PSM_MSG_W1, RFOE()_RX_ORDINF_PSM_MSG_W0.
 *
 * This is a bit-mask with one bit for each flow. The flow index for a given
 * bit is:
 *
 * _ flow index = bit + 64*{b}
 */
union bdk_rfoex_rx_ordinf_err_intx
{
    uint64_t u;
    struct bdk_rfoex_rx_ordinf_err_intx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t orderinfo_miscompare  : 64; /**< [ 63:  0](R/W1C/H) orderInfo.seqNum or orderInfo .timestamp miscompare from incoming RoE packet. */
#else /* Word 0 - Little Endian */
        uint64_t orderinfo_miscompare  : 64; /**< [ 63:  0](R/W1C/H) orderInfo.seqNum or orderInfo .timestamp miscompare from incoming RoE packet. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_ordinf_err_intx_s cn; */
};
typedef union bdk_rfoex_rx_ordinf_err_intx bdk_rfoex_rx_ordinf_err_intx_t;

static inline uint64_t BDK_RFOEX_RX_ORDINF_ERR_INTX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_ORDINF_ERR_INTX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=3)))
        return 0x87e043d01e00ll + 0x80000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    __bdk_csr_fatal("RFOEX_RX_ORDINF_ERR_INTX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_ORDINF_ERR_INTX(a,b) bdk_rfoex_rx_ordinf_err_intx_t
#define bustype_BDK_RFOEX_RX_ORDINF_ERR_INTX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_ORDINF_ERR_INTX(a,b) "RFOEX_RX_ORDINF_ERR_INTX"
#define busnum_BDK_RFOEX_RX_ORDINF_ERR_INTX(a,b) (a)
#define arguments_BDK_RFOEX_RX_ORDINF_ERR_INTX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_rx_ordinf_err_int_w1s#
 *
 * RFOE RX OrderInfo Error Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_rfoex_rx_ordinf_err_int_w1sx
{
    uint64_t u;
    struct bdk_rfoex_rx_ordinf_err_int_w1sx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t orderinfo_miscompare  : 64; /**< [ 63:  0](R/W1S/H) Reads or sets RFOE(0..1)_RX_ORDINF_ERR_INT(0..3)[ORDERINFO_MISCOMPARE]. */
#else /* Word 0 - Little Endian */
        uint64_t orderinfo_miscompare  : 64; /**< [ 63:  0](R/W1S/H) Reads or sets RFOE(0..1)_RX_ORDINF_ERR_INT(0..3)[ORDERINFO_MISCOMPARE]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_ordinf_err_int_w1sx_s cn; */
};
typedef union bdk_rfoex_rx_ordinf_err_int_w1sx bdk_rfoex_rx_ordinf_err_int_w1sx_t;

static inline uint64_t BDK_RFOEX_RX_ORDINF_ERR_INT_W1SX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_ORDINF_ERR_INT_W1SX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=3)))
        return 0x87e043d01e60ll + 0x80000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    __bdk_csr_fatal("RFOEX_RX_ORDINF_ERR_INT_W1SX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_ORDINF_ERR_INT_W1SX(a,b) bdk_rfoex_rx_ordinf_err_int_w1sx_t
#define bustype_BDK_RFOEX_RX_ORDINF_ERR_INT_W1SX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_ORDINF_ERR_INT_W1SX(a,b) "RFOEX_RX_ORDINF_ERR_INT_W1SX"
#define busnum_BDK_RFOEX_RX_ORDINF_ERR_INT_W1SX(a,b) (a)
#define arguments_BDK_RFOEX_RX_ORDINF_ERR_INT_W1SX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_rx_ordinf_psm_msg_w0
 *
 * RFOE RX Orderinfo Interrupt Message w0  Register
 * JCA word 0 message to send on enabled orderInfo error.
 */
union bdk_rfoex_rx_ordinf_psm_msg_w0
{
    uint64_t u;
    struct bdk_rfoex_rx_ordinf_psm_msg_w0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t w0                    : 64; /**< [ 63:  0](R/W) Word 0 of JCA message. */
#else /* Word 0 - Little Endian */
        uint64_t w0                    : 64; /**< [ 63:  0](R/W) Word 0 of JCA message. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_ordinf_psm_msg_w0_s cn; */
};
typedef union bdk_rfoex_rx_ordinf_psm_msg_w0 bdk_rfoex_rx_ordinf_psm_msg_w0_t;

static inline uint64_t BDK_RFOEX_RX_ORDINF_PSM_MSG_W0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_ORDINF_PSM_MSG_W0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01e80ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_ORDINF_PSM_MSG_W0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_ORDINF_PSM_MSG_W0(a) bdk_rfoex_rx_ordinf_psm_msg_w0_t
#define bustype_BDK_RFOEX_RX_ORDINF_PSM_MSG_W0(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_ORDINF_PSM_MSG_W0(a) "RFOEX_RX_ORDINF_PSM_MSG_W0"
#define busnum_BDK_RFOEX_RX_ORDINF_PSM_MSG_W0(a) (a)
#define arguments_BDK_RFOEX_RX_ORDINF_PSM_MSG_W0(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_ordinf_psm_msg_w1
 *
 * RFOE RX Orderinfo Interrupt Message w1 Register
 * JCA word 1 message to send on enabled orderInfo error.
 */
union bdk_rfoex_rx_ordinf_psm_msg_w1
{
    uint64_t u;
    struct bdk_rfoex_rx_ordinf_psm_msg_w1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t w1                    : 64; /**< [ 63:  0](R/W) Word 0 of JCA message. */
#else /* Word 0 - Little Endian */
        uint64_t w1                    : 64; /**< [ 63:  0](R/W) Word 0 of JCA message. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_ordinf_psm_msg_w1_s cn; */
};
typedef union bdk_rfoex_rx_ordinf_psm_msg_w1 bdk_rfoex_rx_ordinf_psm_msg_w1_t;

static inline uint64_t BDK_RFOEX_RX_ORDINF_PSM_MSG_W1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_ORDINF_PSM_MSG_W1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01e88ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_ORDINF_PSM_MSG_W1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_ORDINF_PSM_MSG_W1(a) bdk_rfoex_rx_ordinf_psm_msg_w1_t
#define bustype_BDK_RFOEX_RX_ORDINF_PSM_MSG_W1(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_ORDINF_PSM_MSG_W1(a) "RFOEX_RX_ORDINF_PSM_MSG_W1"
#define busnum_BDK_RFOEX_RX_ORDINF_PSM_MSG_W1(a) (a)
#define arguments_BDK_RFOEX_RX_ORDINF_PSM_MSG_W1(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_pkt_err_drop_stat
 *
 * RFOE RX Packet Error Packet Drop Statistic Register
 * Count of packets dropped for RFOE()_RX_ERROR_INT[CLEAN_APERTURE],
 * RFOE()_RX_ERROR_INT[LEN_ABNORM], RFOE()_RX_ERROR_INT[FD_MALFORMED], and
 * RFOE()_RX_ERROR_INT[FC_PSM_OPCODE], and RFOE()_RX_ERROR_INT[FD_STATE]
 */
union bdk_rfoex_rx_pkt_err_drop_stat
{
    uint64_t u;
    struct bdk_rfoex_rx_pkt_err_drop_stat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) The counter value. Wraps to zero at 2^48. */
#else /* Word 0 - Little Endian */
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) The counter value. Wraps to zero at 2^48. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_pkt_err_drop_stat_s cn; */
};
typedef union bdk_rfoex_rx_pkt_err_drop_stat bdk_rfoex_rx_pkt_err_drop_stat_t;

static inline uint64_t BDK_RFOEX_RX_PKT_ERR_DROP_STAT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_PKT_ERR_DROP_STAT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01d38ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_PKT_ERR_DROP_STAT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_PKT_ERR_DROP_STAT(a) bdk_rfoex_rx_pkt_err_drop_stat_t
#define bustype_BDK_RFOEX_RX_PKT_ERR_DROP_STAT(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_PKT_ERR_DROP_STAT(a) "RFOEX_RX_PKT_ERR_DROP_STAT"
#define busnum_BDK_RFOEX_RX_PKT_ERR_DROP_STAT(a) (a)
#define arguments_BDK_RFOEX_RX_PKT_ERR_DROP_STAT(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_pkt_logger_addr
 *
 * RFOE RX Packet Logger Buffer Addresss Register
 * Defines start address for packet log.
 */
union bdk_rfoex_rx_pkt_logger_addr
{
    uint64_t u;
    struct bdk_rfoex_rx_pkt_logger_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t start_addr            : 53; /**< [ 52:  0](R/W) Specifies the byte address of the start of the write DMA.
                                                                 * If RFOE()_RX_PKT_LOGGER_CFG[TARGET_MEM] = 0, the address  must be
                                                                 128-bit aligned (i.e., bits[3:0] must be 0).
                                                                 * If RFOE()_RX_PKT_LOGGER_CFG[TARGET_MEM] = 1, the address  must be
                                                                 128-byte aligned (i.e., bits[6:0] must be 0). */
#else /* Word 0 - Little Endian */
        uint64_t start_addr            : 53; /**< [ 52:  0](R/W) Specifies the byte address of the start of the write DMA.
                                                                 * If RFOE()_RX_PKT_LOGGER_CFG[TARGET_MEM] = 0, the address  must be
                                                                 128-bit aligned (i.e., bits[3:0] must be 0).
                                                                 * If RFOE()_RX_PKT_LOGGER_CFG[TARGET_MEM] = 1, the address  must be
                                                                 128-byte aligned (i.e., bits[6:0] must be 0). */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_pkt_logger_addr_s cn; */
};
typedef union bdk_rfoex_rx_pkt_logger_addr bdk_rfoex_rx_pkt_logger_addr_t;

static inline uint64_t BDK_RFOEX_RX_PKT_LOGGER_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_PKT_LOGGER_ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01020ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_PKT_LOGGER_ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_PKT_LOGGER_ADDR(a) bdk_rfoex_rx_pkt_logger_addr_t
#define bustype_BDK_RFOEX_RX_PKT_LOGGER_ADDR(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_PKT_LOGGER_ADDR(a) "RFOEX_RX_PKT_LOGGER_ADDR"
#define busnum_BDK_RFOEX_RX_PKT_LOGGER_ADDR(a) (a)
#define arguments_BDK_RFOEX_RX_PKT_LOGGER_ADDR(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_pkt_logger_cfg
 *
 * RFOE RX Packet Logger Buffer Configuration  Register
 * Defines configuration for packet logger circular buffer.
 */
union bdk_rfoex_rx_pkt_logger_cfg
{
    uint64_t u;
    struct bdk_rfoex_rx_pkt_logger_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t target_mem            : 1;  /**< [ 63: 63](R/W) Specifies the target memory for the log buffer.
                                                                 0 = SMEM.
                                                                 1 = LLC/DRAM. */
        uint64_t reserved_62           : 1;
        uint64_t cmd_type              : 2;  /**< [ 61: 60](R/W) Command type for LLC/DRAM write, as enumerated by MHBW_PNB_WR_CMD_E.

                                                                 Note:
                                                                 * Writes to BPHY SMEM ignore this field.
                                                                 * Unaligned or partial cacheline writes always use MHBW_PNB_WR_CMD_E::STP.

                                                                 Internal:
                                                                 Notes:
                                                                 *BPHY DDR Hardware DMA replaces this field with STP for unaligned cache line
                                                                 starts. All transfers for this burst will be STP.
                                                                 *BPHY DDR Hardware DMA replaces this field with STP for the last transfer in a burst if unaligned. */
        uint64_t reserved_59           : 1;
        uint64_t dswap                 : 3;  /**< [ 58: 56](R/W) The byte swap mode for DMA to LLC/DRAM. Enumerated in MHBW_PNB_DSWAP_E.
                                                                 DMA to BPHY SMEM ignores this field. */
        uint64_t reserved_37_55        : 19;
        uint64_t flush                 : 1;  /**< [ 36: 36](R/W/H) On a write with [FLUSH]=1, hardware flushes the internal packet log FIFO to
                                                                 memory. Hardware clears when flush operation completes as indicated by
                                                                 RFOE()_RX_STATUS[PKT_LOGGER_FLUSH_DONE] == 1. */
        uint64_t reserved_33_35        : 3;
        uint64_t enable                : 1;  /**< [ 32: 32](R/W) Enable receive packet logging.
                                                                 0 = Disabled.
                                                                 1 = Enable packet logging.

                                                                 When enabled, each RoE subtype 0xfd packet with EOS set generates a log
                                                                 entry. All other packets generate a log entry for each packet.

                                                                 Logger entries for packets already started will be completed and written
                                                                 normally.  If a flush is desired,
                                                                 write [FLUSH] = 1 to force all waiting entries to memory.

                                                                 Software should only change logger configuration when logger is idle, logger
                                                                 FIFO empty (ie. FLUSHed)  and [ENABLE] == 0. */
        uint64_t ddr_wait_cycles       : 12; /**< [ 31: 20](R/W) Used when [TARGET_MEM]=1.  No action when TMEM=0.
                                                                 Maximum time for coalescing log writes to LLC/DRAM. Up to 128 bytes of
                                                                 log entries are coalesced before writing to LLC/DRAM. After
                                                                 [DDR_WAIT_CYCLES]*16 cycles with no new log entries, any buffered
                                                                 entries are written to memory.

                                                                 The reset value of 0x80 results in a time of 2 us when BCLK is 1 GHz.

                                                                 Setting [DDR_WAIT_CYCLES]=0 disables the timer, and the logger will
                                                                 wait indefinitely to collect 128 bytes of log entries before writing
                                                                 to LLC/DRAM.

                                                                 Ignored when [TARGET_MEM]=0. */
        uint64_t reserved_17_19        : 3;
        uint64_t size                  : 17; /**< [ 16:  0](R/W) Total size of the log buffer in units of 128 bits.
                                                                 If RFOE()_RX_PKT_LOGGER_CFG[TARGET_MEM]=1, [SIZE] must be a multiple
                                                                 of 8 (i.e., the size must be a multiple of 128 bytes). */
#else /* Word 0 - Little Endian */
        uint64_t size                  : 17; /**< [ 16:  0](R/W) Total size of the log buffer in units of 128 bits.
                                                                 If RFOE()_RX_PKT_LOGGER_CFG[TARGET_MEM]=1, [SIZE] must be a multiple
                                                                 of 8 (i.e., the size must be a multiple of 128 bytes). */
        uint64_t reserved_17_19        : 3;
        uint64_t ddr_wait_cycles       : 12; /**< [ 31: 20](R/W) Used when [TARGET_MEM]=1.  No action when TMEM=0.
                                                                 Maximum time for coalescing log writes to LLC/DRAM. Up to 128 bytes of
                                                                 log entries are coalesced before writing to LLC/DRAM. After
                                                                 [DDR_WAIT_CYCLES]*16 cycles with no new log entries, any buffered
                                                                 entries are written to memory.

                                                                 The reset value of 0x80 results in a time of 2 us when BCLK is 1 GHz.

                                                                 Setting [DDR_WAIT_CYCLES]=0 disables the timer, and the logger will
                                                                 wait indefinitely to collect 128 bytes of log entries before writing
                                                                 to LLC/DRAM.

                                                                 Ignored when [TARGET_MEM]=0. */
        uint64_t enable                : 1;  /**< [ 32: 32](R/W) Enable receive packet logging.
                                                                 0 = Disabled.
                                                                 1 = Enable packet logging.

                                                                 When enabled, each RoE subtype 0xfd packet with EOS set generates a log
                                                                 entry. All other packets generate a log entry for each packet.

                                                                 Logger entries for packets already started will be completed and written
                                                                 normally.  If a flush is desired,
                                                                 write [FLUSH] = 1 to force all waiting entries to memory.

                                                                 Software should only change logger configuration when logger is idle, logger
                                                                 FIFO empty (ie. FLUSHed)  and [ENABLE] == 0. */
        uint64_t reserved_33_35        : 3;
        uint64_t flush                 : 1;  /**< [ 36: 36](R/W/H) On a write with [FLUSH]=1, hardware flushes the internal packet log FIFO to
                                                                 memory. Hardware clears when flush operation completes as indicated by
                                                                 RFOE()_RX_STATUS[PKT_LOGGER_FLUSH_DONE] == 1. */
        uint64_t reserved_37_55        : 19;
        uint64_t dswap                 : 3;  /**< [ 58: 56](R/W) The byte swap mode for DMA to LLC/DRAM. Enumerated in MHBW_PNB_DSWAP_E.
                                                                 DMA to BPHY SMEM ignores this field. */
        uint64_t reserved_59           : 1;
        uint64_t cmd_type              : 2;  /**< [ 61: 60](R/W) Command type for LLC/DRAM write, as enumerated by MHBW_PNB_WR_CMD_E.

                                                                 Note:
                                                                 * Writes to BPHY SMEM ignore this field.
                                                                 * Unaligned or partial cacheline writes always use MHBW_PNB_WR_CMD_E::STP.

                                                                 Internal:
                                                                 Notes:
                                                                 *BPHY DDR Hardware DMA replaces this field with STP for unaligned cache line
                                                                 starts. All transfers for this burst will be STP.
                                                                 *BPHY DDR Hardware DMA replaces this field with STP for the last transfer in a burst if unaligned. */
        uint64_t reserved_62           : 1;
        uint64_t target_mem            : 1;  /**< [ 63: 63](R/W) Specifies the target memory for the log buffer.
                                                                 0 = SMEM.
                                                                 1 = LLC/DRAM. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_pkt_logger_cfg_s cn; */
};
typedef union bdk_rfoex_rx_pkt_logger_cfg bdk_rfoex_rx_pkt_logger_cfg_t;

static inline uint64_t BDK_RFOEX_RX_PKT_LOGGER_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_PKT_LOGGER_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01028ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_PKT_LOGGER_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_PKT_LOGGER_CFG(a) bdk_rfoex_rx_pkt_logger_cfg_t
#define bustype_BDK_RFOEX_RX_PKT_LOGGER_CFG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_PKT_LOGGER_CFG(a) "RFOEX_RX_PKT_LOGGER_CFG"
#define busnum_BDK_RFOEX_RX_PKT_LOGGER_CFG(a) (a)
#define arguments_BDK_RFOEX_RX_PKT_LOGGER_CFG(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_scratch
 *
 * INTERNAL: Scratch Register
 *
 * Scratch register.
 */
union bdk_rfoex_rx_scratch
{
    uint64_t u;
    struct bdk_rfoex_rx_scratch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Scratch data. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Scratch data. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_scratch_s cn; */
};
typedef union bdk_rfoex_rx_scratch bdk_rfoex_rx_scratch_t;

static inline uint64_t BDK_RFOEX_RX_SCRATCH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_SCRATCH(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01000ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_SCRATCH", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_SCRATCH(a) bdk_rfoex_rx_scratch_t
#define bustype_BDK_RFOEX_RX_SCRATCH(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_SCRATCH(a) "RFOEX_RX_SCRATCH"
#define busnum_BDK_RFOEX_RX_SCRATCH(a) (a)
#define arguments_BDK_RFOEX_RX_SCRATCH(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_status
 *
 * RFOE RX General Status Register
 * General receive status.
 */
union bdk_rfoex_rx_status
{
    uint64_t u;
    struct bdk_rfoex_rx_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t pkt_logger_flush_done : 1;  /**< [ 49: 49](RO/H) Cleared on a write to RFOE()_RX_PKT_LOGGER_CFG[FLUSH]=1.  Set when the
                                                                 packet logger buffer has been flushed to memory.
                                                                 * Indicates that all logger write requests have been issued from RFOE.
                                                                 * Does not guarantee return of all commits. */
        uint64_t pkt_logger_tail_idx   : 17; /**< [ 48: 32](RO/H) Index for the next logger status write, in units of 16 bytes.
                                                                 * Newest logger entry is at ([PKT_LOGGER_TAIL_IDX]-1) mod RFOE(0..1)_RX_PKT_LOGGER_CFG[SIZE].
                                                                 * Address in memory is RFOE(0..1)_RX_PKT_LOGGER_ADDR +
                                                                 (([PKT_LOGGER_TAIL_IDX]-1) mod RFOE(0..1)_RX_PKT_LOGGER_CFG[SIZE])*16 bytes.
                                                                 * Newest is not valid after reset since nothing has been written to packet logger in memory. */
        uint64_t reserved_17_31        : 15;
        uint64_t calibrate_status      : 1;  /**< [ 16: 16](RO/H) X2P device calibration state bit per x2p interface.
                                                                 0 = Device inactive.
                                                                 1 = Device ready.

                                                                 Internal:
                                                                 a "Device Inactive" status means that the X2P agent did not respond to the calibration
                                                                 cycle.
                                                                 This is most likely caused because the X2P agents (CGX, LBK, etc) was in reset during the
                                                                 calibration cycle. */
        uint64_t reserved_11_15        : 5;
        uint64_t calibrate_done        : 1;  /**< [ 10: 10](RO/H) Calibrate cycle is complete. */
        uint64_t blk_active            : 10; /**< [  9:  0](RO/H) If nonzero, block is active.
                                                                 Internal:
                                                                 Each bit corresponds to a subblock:
                                                                 \<9:4\> = Reserved.
                                                                 \<3\> = CSR JCA.   the JCA path
                                                                 \<2\> = DMA.  Excludes responses. Those are tracked by free list.
                                                                 \<1\> = EHP.  Includes free list.
                                                                 \<0\> = CGXIF. */
#else /* Word 0 - Little Endian */
        uint64_t blk_active            : 10; /**< [  9:  0](RO/H) If nonzero, block is active.
                                                                 Internal:
                                                                 Each bit corresponds to a subblock:
                                                                 \<9:4\> = Reserved.
                                                                 \<3\> = CSR JCA.   the JCA path
                                                                 \<2\> = DMA.  Excludes responses. Those are tracked by free list.
                                                                 \<1\> = EHP.  Includes free list.
                                                                 \<0\> = CGXIF. */
        uint64_t calibrate_done        : 1;  /**< [ 10: 10](RO/H) Calibrate cycle is complete. */
        uint64_t reserved_11_15        : 5;
        uint64_t calibrate_status      : 1;  /**< [ 16: 16](RO/H) X2P device calibration state bit per x2p interface.
                                                                 0 = Device inactive.
                                                                 1 = Device ready.

                                                                 Internal:
                                                                 a "Device Inactive" status means that the X2P agent did not respond to the calibration
                                                                 cycle.
                                                                 This is most likely caused because the X2P agents (CGX, LBK, etc) was in reset during the
                                                                 calibration cycle. */
        uint64_t reserved_17_31        : 15;
        uint64_t pkt_logger_tail_idx   : 17; /**< [ 48: 32](RO/H) Index for the next logger status write, in units of 16 bytes.
                                                                 * Newest logger entry is at ([PKT_LOGGER_TAIL_IDX]-1) mod RFOE(0..1)_RX_PKT_LOGGER_CFG[SIZE].
                                                                 * Address in memory is RFOE(0..1)_RX_PKT_LOGGER_ADDR +
                                                                 (([PKT_LOGGER_TAIL_IDX]-1) mod RFOE(0..1)_RX_PKT_LOGGER_CFG[SIZE])*16 bytes.
                                                                 * Newest is not valid after reset since nothing has been written to packet logger in memory. */
        uint64_t pkt_logger_flush_done : 1;  /**< [ 49: 49](RO/H) Cleared on a write to RFOE()_RX_PKT_LOGGER_CFG[FLUSH]=1.  Set when the
                                                                 packet logger buffer has been flushed to memory.
                                                                 * Indicates that all logger write requests have been issued from RFOE.
                                                                 * Does not guarantee return of all commits. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_status_s cn9; */
    /* struct bdk_rfoex_rx_status_s cnf95xxp1; */
    struct bdk_rfoex_rx_status_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t pkt_logger_flush_done : 1;  /**< [ 49: 49](RO/H) Cleared on a write to RFOE()_RX_PKT_LOGGER_CFG[FLUSH]=1.  Set when the
                                                                 packet logger buffer has been flushed to memory.
                                                                 * Indicates that all logger write requests have been issued from RFOE.
                                                                 * Does not guarantee return of all commits. */
        uint64_t pkt_logger_tail_idx   : 17; /**< [ 48: 32](RO/H) Index for the next logger status write, in units of 16 bytes.
                                                                 * Newest logger entry is at ([PKT_LOGGER_TAIL_IDX]-1) mod RFOE(0..1)_RX_PKT_LOGGER_CFG[SIZE].
                                                                 * Address in memory is RFOE(0..1)_RX_PKT_LOGGER_ADDR +
                                                                 (([PKT_LOGGER_TAIL_IDX]-1) mod RFOE(0..1)_RX_PKT_LOGGER_CFG[SIZE])*16 bytes.
                                                                 * Newest is not valid after reset since nothing has been written to packet logger in memory. */
        uint64_t reserved_17_31        : 15;
        uint64_t calibrate_status      : 1;  /**< [ 16: 16](RO/H) Value is 0 on CNXXXX.  Use [CALIBRATE_DONE] to determine when calibration cycle is complete.
                                                                 Internal:
                                                                 Old - X2P device calibration state bit per x2p interface.
                                                                 0 = Device inactive.
                                                                 1 = Device ready.
                                                                 a "Device Inactive" status means that the X2P agent did not respond to the calibration
                                                                 cycle.
                                                                 This is most likely caused because the X2P agents (CGX, LBK, etc) was in reset during the
                                                                 calibration cycle. */
        uint64_t reserved_11_15        : 5;
        uint64_t calibrate_done        : 1;  /**< [ 10: 10](RO/H) Calibrate cycle is complete. */
        uint64_t blk_active            : 10; /**< [  9:  0](RO/H) If nonzero, block is active.
                                                                 Internal:
                                                                 Each bit corresponds to a subblock:
                                                                 \<9:4\> = Reserved.
                                                                 \<3\> = CSR JCA.   the JCA path
                                                                 \<2\> = DMA.  Excludes responses. Those are tracked by free list.
                                                                 \<1\> = EHP.  Includes free list.
                                                                 \<0\> = CGXIF. */
#else /* Word 0 - Little Endian */
        uint64_t blk_active            : 10; /**< [  9:  0](RO/H) If nonzero, block is active.
                                                                 Internal:
                                                                 Each bit corresponds to a subblock:
                                                                 \<9:4\> = Reserved.
                                                                 \<3\> = CSR JCA.   the JCA path
                                                                 \<2\> = DMA.  Excludes responses. Those are tracked by free list.
                                                                 \<1\> = EHP.  Includes free list.
                                                                 \<0\> = CGXIF. */
        uint64_t calibrate_done        : 1;  /**< [ 10: 10](RO/H) Calibrate cycle is complete. */
        uint64_t reserved_11_15        : 5;
        uint64_t calibrate_status      : 1;  /**< [ 16: 16](RO/H) Value is 0 on CNXXXX.  Use [CALIBRATE_DONE] to determine when calibration cycle is complete.
                                                                 Internal:
                                                                 Old - X2P device calibration state bit per x2p interface.
                                                                 0 = Device inactive.
                                                                 1 = Device ready.
                                                                 a "Device Inactive" status means that the X2P agent did not respond to the calibration
                                                                 cycle.
                                                                 This is most likely caused because the X2P agents (CGX, LBK, etc) was in reset during the
                                                                 calibration cycle. */
        uint64_t reserved_17_31        : 15;
        uint64_t pkt_logger_tail_idx   : 17; /**< [ 48: 32](RO/H) Index for the next logger status write, in units of 16 bytes.
                                                                 * Newest logger entry is at ([PKT_LOGGER_TAIL_IDX]-1) mod RFOE(0..1)_RX_PKT_LOGGER_CFG[SIZE].
                                                                 * Address in memory is RFOE(0..1)_RX_PKT_LOGGER_ADDR +
                                                                 (([PKT_LOGGER_TAIL_IDX]-1) mod RFOE(0..1)_RX_PKT_LOGGER_CFG[SIZE])*16 bytes.
                                                                 * Newest is not valid after reset since nothing has been written to packet logger in memory. */
        uint64_t pkt_logger_flush_done : 1;  /**< [ 49: 49](RO/H) Cleared on a write to RFOE()_RX_PKT_LOGGER_CFG[FLUSH]=1.  Set when the
                                                                 packet logger buffer has been flushed to memory.
                                                                 * Indicates that all logger write requests have been issued from RFOE.
                                                                 * Does not guarantee return of all commits. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } cnf95xxp2;
};
typedef union bdk_rfoex_rx_status bdk_rfoex_rx_status_t;

static inline uint64_t BDK_RFOEX_RX_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01010ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_STATUS(a) bdk_rfoex_rx_status_t
#define bustype_BDK_RFOEX_RX_STATUS(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_STATUS(a) "RFOEX_RX_STATUS"
#define busnum_BDK_RFOEX_RX_STATUS(a) (a)
#define arguments_BDK_RFOEX_RX_STATUS(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_sync_discard_counter
 *
 * RFOE RX SYNC Packet Discard Counter Statistic Register
 * Count number packets discarded as a result of an  RX sync drop.
 */
union bdk_rfoex_rx_sync_discard_counter
{
    uint64_t u;
    struct bdk_rfoex_rx_sync_discard_counter_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t stat                  : 64; /**< [ 63:  0](R/W/H) The counter value. Wraps to zero at 2^64. */
#else /* Word 0 - Little Endian */
        uint64_t stat                  : 64; /**< [ 63:  0](R/W/H) The counter value. Wraps to zero at 2^64. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_sync_discard_counter_s cn; */
};
typedef union bdk_rfoex_rx_sync_discard_counter bdk_rfoex_rx_sync_discard_counter_t;

static inline uint64_t BDK_RFOEX_RX_SYNC_DISCARD_COUNTER(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_SYNC_DISCARD_COUNTER(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d01d20ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_RX_SYNC_DISCARD_COUNTER", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_SYNC_DISCARD_COUNTER(a) bdk_rfoex_rx_sync_discard_counter_t
#define bustype_BDK_RFOEX_RX_SYNC_DISCARD_COUNTER(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_SYNC_DISCARD_COUNTER(a) "RFOEX_RX_SYNC_DISCARD_COUNTER"
#define busnum_BDK_RFOEX_RX_SYNC_DISCARD_COUNTER(a) (a)
#define arguments_BDK_RFOEX_RX_SYNC_DISCARD_COUNTER(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_rx_sync_flow#
 *
 * RFOE RX Sync Per Flow Antenna Identification Register
 * Identifies which RX flows are synchronized antenna flows.
 *
 * This is a bit-mask with one bit for each flow. The flow index for a given
 * bit is:
 *
 * _ flow index = bit + 64*{b}
 *
 * Set bits indicates synchronized antenna flows.
 */
union bdk_rfoex_rx_sync_flowx
{
    uint64_t u;
    struct bdk_rfoex_rx_sync_flowx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ant                   : 64; /**< [ 63:  0](R/W) Bit-mask indicated antenna flows. */
#else /* Word 0 - Little Endian */
        uint64_t ant                   : 64; /**< [ 63:  0](R/W) Bit-mask indicated antenna flows. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_sync_flowx_s cn; */
};
typedef union bdk_rfoex_rx_sync_flowx bdk_rfoex_rx_sync_flowx_t;

static inline uint64_t BDK_RFOEX_RX_SYNC_FLOWX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_SYNC_FLOWX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=3)))
        return 0x87e043d01700ll + 0x80000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    __bdk_csr_fatal("RFOEX_RX_SYNC_FLOWX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_SYNC_FLOWX(a,b) bdk_rfoex_rx_sync_flowx_t
#define bustype_BDK_RFOEX_RX_SYNC_FLOWX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_SYNC_FLOWX(a,b) "RFOEX_RX_SYNC_FLOWX"
#define busnum_BDK_RFOEX_RX_SYNC_FLOWX(a,b) (a)
#define arguments_BDK_RFOEX_RX_SYNC_FLOWX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_rx_sync_state#
 *
 * RFOE RX Sync State Register
 * Indicates the state of each RX antenna flow.
 *
 * This is a bit-mask with one bit for each flow. The flow index for a given
 * bit is:
 *
 * _ flow index = bit + 64*{b}
 *
 * Writes of 1 to bit will reset the state to DISABLED.
 * RFOE()_RX_IND_FT()_CFG[ENABLE] must be 0 for all FLOW_IDX being reset.
 */
union bdk_rfoex_rx_sync_statex
{
    uint64_t u;
    struct bdk_rfoex_rx_sync_statex_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t state                 : 64; /**< [ 63:  0](R/W1C/H) Bit-mask of antenna flow state. For each bit:
                                                                 0 = DISABLED antenna flow, all packets will be dropped. Drops are counted in
                                                                 RFOE()_RX_SYNC_DISCARD_COUNTER.
                                                                 1 = ENABLED antenna flow, allow incoming packets. */
#else /* Word 0 - Little Endian */
        uint64_t state                 : 64; /**< [ 63:  0](R/W1C/H) Bit-mask of antenna flow state. For each bit:
                                                                 0 = DISABLED antenna flow, all packets will be dropped. Drops are counted in
                                                                 RFOE()_RX_SYNC_DISCARD_COUNTER.
                                                                 1 = ENABLED antenna flow, allow incoming packets. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_rx_sync_statex_s cn; */
};
typedef union bdk_rfoex_rx_sync_statex bdk_rfoex_rx_sync_statex_t;

static inline uint64_t BDK_RFOEX_RX_SYNC_STATEX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_RX_SYNC_STATEX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=3)))
        return 0x87e043d01740ll + 0x80000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    __bdk_csr_fatal("RFOEX_RX_SYNC_STATEX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_RX_SYNC_STATEX(a,b) bdk_rfoex_rx_sync_statex_t
#define bustype_BDK_RFOEX_RX_SYNC_STATEX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_RX_SYNC_STATEX(a,b) "RFOEX_RX_SYNC_STATEX"
#define busnum_BDK_RFOEX_RX_SYNC_STATEX(a,b) (a)
#define arguments_BDK_RFOEX_RX_SYNC_STATEX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_tx_ctrl
 *
 * RFOE TX Control Register
 * Data path control and status for doing BPHY/RFIF reset sequences.
 */
union bdk_rfoex_tx_ctrl
{
    uint64_t u;
    struct bdk_rfoex_tx_ctrl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t force_intf_clk_en     : 1;  /**< [  2:  2](R/W) Force the clock enable on P2X interface signals between blocks. For diagnostic use only. */
        uint64_t tx_idle               : 1;  /**< [  1:  1](RO/H) Transmit path idle.
                                                                 When [DATA_PKT_TX_EN] = 0, [TX_IDLE] = 1 indicates that the in-flight packets are sent
                                                                 and that any new packets scheduled are discarded. [TX_IDLE]=1 means it's
                                                                 safe to do BPHY and/or RFIF reset. For the reset domains:
                                                                 * A BPHY reset will reset all pending transactions.
                                                                 * RFIF domain (CGX) can still be active, and a RFIF reset will reset all these transactions.
                                                                 *Once [TX_IDLE] is set, it will stay set until [DATA_PKT_TX_EN] is set to 0 by SW.
                                                                 [TX_IDLE] should be ignored when [DATA_PKT_TX_EN] == 1. */
        uint64_t data_pkt_tx_en        : 1;  /**< [  0:  0](R/W) Enable TX traffic.  Software must write to 1 to enable TX traffic.
                                                                 0 = RFOE discards packets transmit packets.
                                                                 1 = RFOE transmits packets to CGX.

                                                                 When [DATA_PKT_TX_EN] transitions from 1 to 0, RFOE completes any
                                                                 in-flight transmit packets. Once all in-flight packets are sent,
                                                                 RFOE sets [TX_IDLE], and discards and subsequent transmit packets. */
#else /* Word 0 - Little Endian */
        uint64_t data_pkt_tx_en        : 1;  /**< [  0:  0](R/W) Enable TX traffic.  Software must write to 1 to enable TX traffic.
                                                                 0 = RFOE discards packets transmit packets.
                                                                 1 = RFOE transmits packets to CGX.

                                                                 When [DATA_PKT_TX_EN] transitions from 1 to 0, RFOE completes any
                                                                 in-flight transmit packets. Once all in-flight packets are sent,
                                                                 RFOE sets [TX_IDLE], and discards and subsequent transmit packets. */
        uint64_t tx_idle               : 1;  /**< [  1:  1](RO/H) Transmit path idle.
                                                                 When [DATA_PKT_TX_EN] = 0, [TX_IDLE] = 1 indicates that the in-flight packets are sent
                                                                 and that any new packets scheduled are discarded. [TX_IDLE]=1 means it's
                                                                 safe to do BPHY and/or RFIF reset. For the reset domains:
                                                                 * A BPHY reset will reset all pending transactions.
                                                                 * RFIF domain (CGX) can still be active, and a RFIF reset will reset all these transactions.
                                                                 *Once [TX_IDLE] is set, it will stay set until [DATA_PKT_TX_EN] is set to 0 by SW.
                                                                 [TX_IDLE] should be ignored when [DATA_PKT_TX_EN] == 1. */
        uint64_t force_intf_clk_en     : 1;  /**< [  2:  2](R/W) Force the clock enable on P2X interface signals between blocks. For diagnostic use only. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_tx_ctrl_s cn9; */
    /* struct bdk_rfoex_tx_ctrl_s cnf95xxp1; */
    struct bdk_rfoex_tx_ctrl_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t force_intf_clk_en     : 1;  /**< [  2:  2](R/W) Force the clock enable on P2X interface signals between blocks. For diagnostic use only. */
        uint64_t tx_idle               : 1;  /**< [  1:  1](RO/H) Transmit path idle.
                                                                 When [DATA_PKT_TX_EN] = 0, [TX_IDLE] = 1 indicates that the in-flight packets are sent
                                                                 and that any new packets scheduled are discarded. [TX_IDLE]=1 means it's
                                                                 safe to do BPHY and/or RFIF reset. For the reset domains:
                                                                 * A BPHY reset will reset all pending transactions.
                                                                 * RFIF domain (CGX) can still be active, and a RFIF reset will reset all these transactions.
                                                                 *Once [TX_IDLE] is set, it will stay set until [DATA_PKT_TX_EN] is set to 0 by SW.
                                                                 [TX_IDLE] should be ignored when [DATA_PKT_TX_EN] == 1. */
        uint64_t data_pkt_tx_en        : 1;  /**< [  0:  0](R/W) Enable TX traffic.  Software must write to 1 [DATA_PKT_TX_LMAC_EN] and
                                                                  [DATA_PKT_TX_EN] to enable TX traffic.
                                                                 0 = RFOE discards packets transmit packets to all LMAC.
                                                                 1 = RFOE enables packet transmits to CGX.

                                                                 When [DATA_PKT_TX_EN] transitions from 1 to 0, RFOE completes any
                                                                 in-flight transmit packets. Once all in-flight packets are sent,
                                                                 RFOE sets [TX_IDLE], and discards and subsequent transmit packets. */
#else /* Word 0 - Little Endian */
        uint64_t data_pkt_tx_en        : 1;  /**< [  0:  0](R/W) Enable TX traffic.  Software must write to 1 [DATA_PKT_TX_LMAC_EN] and
                                                                  [DATA_PKT_TX_EN] to enable TX traffic.
                                                                 0 = RFOE discards packets transmit packets to all LMAC.
                                                                 1 = RFOE enables packet transmits to CGX.

                                                                 When [DATA_PKT_TX_EN] transitions from 1 to 0, RFOE completes any
                                                                 in-flight transmit packets. Once all in-flight packets are sent,
                                                                 RFOE sets [TX_IDLE], and discards and subsequent transmit packets. */
        uint64_t tx_idle               : 1;  /**< [  1:  1](RO/H) Transmit path idle.
                                                                 When [DATA_PKT_TX_EN] = 0, [TX_IDLE] = 1 indicates that the in-flight packets are sent
                                                                 and that any new packets scheduled are discarded. [TX_IDLE]=1 means it's
                                                                 safe to do BPHY and/or RFIF reset. For the reset domains:
                                                                 * A BPHY reset will reset all pending transactions.
                                                                 * RFIF domain (CGX) can still be active, and a RFIF reset will reset all these transactions.
                                                                 *Once [TX_IDLE] is set, it will stay set until [DATA_PKT_TX_EN] is set to 0 by SW.
                                                                 [TX_IDLE] should be ignored when [DATA_PKT_TX_EN] == 1. */
        uint64_t force_intf_clk_en     : 1;  /**< [  2:  2](R/W) Force the clock enable on P2X interface signals between blocks. For diagnostic use only. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } cnf95xxp2;
};
typedef union bdk_rfoex_tx_ctrl bdk_rfoex_tx_ctrl_t;

static inline uint64_t BDK_RFOEX_TX_CTRL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_TX_CTRL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d00f08ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_TX_CTRL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_TX_CTRL(a) bdk_rfoex_tx_ctrl_t
#define bustype_BDK_RFOEX_TX_CTRL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_TX_CTRL(a) "RFOEX_TX_CTRL"
#define busnum_BDK_RFOEX_TX_CTRL(a) (a)
#define arguments_BDK_RFOEX_TX_CTRL(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_tx_hdr_da#
 *
 * RFOE TX Ethernet Destination Address Register
 * Ethernet destination MAC address for TX packets sent with
 * RFOE()_AB()_SLOT()_CONFIGURATION[PKT_MODE]=0x1.
 *
 * The index {b} is selected by RFOE()_AB()_SLOT()_CONFIGURATION[DA_SEL].
 */
union bdk_rfoex_tx_hdr_dax
{
    uint64_t u;
    struct bdk_rfoex_tx_hdr_dax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t da                    : 48; /**< [ 47:  0](R/W) Destination Ethernet MAC address. The following ordering within the field \<7:0\>
                                                                 at byte address 0, \<15:8\> at address 1, ..., \<47:40\> at address 0x5.
                                                                 RFOE(0..1)_TX_HDR_DA[7:0] = byte 0 of Ethernet packet.
                                                                 ...
                                                                 RFOE(0..1)_TX_HDR_DA[47:40] = byte 5 of Ethernet packet. */
#else /* Word 0 - Little Endian */
        uint64_t da                    : 48; /**< [ 47:  0](R/W) Destination Ethernet MAC address. The following ordering within the field \<7:0\>
                                                                 at byte address 0, \<15:8\> at address 1, ..., \<47:40\> at address 0x5.
                                                                 RFOE(0..1)_TX_HDR_DA[7:0] = byte 0 of Ethernet packet.
                                                                 ...
                                                                 RFOE(0..1)_TX_HDR_DA[47:40] = byte 5 of Ethernet packet. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_tx_hdr_dax_s cn; */
};
typedef union bdk_rfoex_tx_hdr_dax bdk_rfoex_tx_hdr_dax_t;

static inline uint64_t BDK_RFOEX_TX_HDR_DAX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_TX_HDR_DAX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=7)))
        return 0x87e043d00800ll + 0x80000ll * ((a) & 0x1) + 8ll * ((b) & 0x7);
    __bdk_csr_fatal("RFOEX_TX_HDR_DAX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_TX_HDR_DAX(a,b) bdk_rfoex_tx_hdr_dax_t
#define bustype_BDK_RFOEX_TX_HDR_DAX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_TX_HDR_DAX(a,b) "RFOEX_TX_HDR_DAX"
#define busnum_BDK_RFOEX_TX_HDR_DAX(a,b) (a)
#define arguments_BDK_RFOEX_TX_HDR_DAX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_tx_hdr_ethertype#
 *
 * RFOE TX Ethernet EtherType Register
 * Ethernet header Ethertype field for TX packets sent with
 * RFOE()_AB()_SLOT()_CONFIGURATION[PKT_MODE]=1.
 *
 * The index {b} is selected by RFOE()_AB()_SLOT()_CONFIGURATION[ETYPE_SEL].
 */
union bdk_rfoex_tx_hdr_ethertypex
{
    uint64_t u;
    struct bdk_rfoex_tx_hdr_ethertypex_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t ethertype             : 16; /**< [ 15:  0](R/W) Ethernet Ethertype. The following ordering within the field ETHERTYPE\<7:0\> at
                                                                 byte address 0, ETHERTYPE\<15:8\> at byte address 1,
                                                                 RFOE(0..1)_TX_HDR_ETHERTYPE[7:0] = byte 12 of Ethernet packet.
                                                                 RFOE(0..1)_TX_HDR_ETHERTYPE[15:8] = byte 13 of Ethernet packet. */
#else /* Word 0 - Little Endian */
        uint64_t ethertype             : 16; /**< [ 15:  0](R/W) Ethernet Ethertype. The following ordering within the field ETHERTYPE\<7:0\> at
                                                                 byte address 0, ETHERTYPE\<15:8\> at byte address 1,
                                                                 RFOE(0..1)_TX_HDR_ETHERTYPE[7:0] = byte 12 of Ethernet packet.
                                                                 RFOE(0..1)_TX_HDR_ETHERTYPE[15:8] = byte 13 of Ethernet packet. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_tx_hdr_ethertypex_s cn; */
};
typedef union bdk_rfoex_tx_hdr_ethertypex bdk_rfoex_tx_hdr_ethertypex_t;

static inline uint64_t BDK_RFOEX_TX_HDR_ETHERTYPEX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_TX_HDR_ETHERTYPEX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=7)))
        return 0x87e043d00880ll + 0x80000ll * ((a) & 0x1) + 8ll * ((b) & 0x7);
    __bdk_csr_fatal("RFOEX_TX_HDR_ETHERTYPEX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_TX_HDR_ETHERTYPEX(a,b) bdk_rfoex_tx_hdr_ethertypex_t
#define bustype_BDK_RFOEX_TX_HDR_ETHERTYPEX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_TX_HDR_ETHERTYPEX(a,b) "RFOEX_TX_HDR_ETHERTYPEX"
#define busnum_BDK_RFOEX_TX_HDR_ETHERTYPEX(a,b) (a)
#define arguments_BDK_RFOEX_TX_HDR_ETHERTYPEX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_tx_hdr_sa#
 *
 * RFOE TX Ethernet Source Address Register
 * Ethernet source MAC address for TX packets sent with
 * RFOE()_AB()_SLOT()_CONFIGURATION[PKT_MODE]=0x1.
 *
 * The index {b} is selected by RFOE()_AB()_SLOT()_CONFIGURATION[SA_SEL].
 */
union bdk_rfoex_tx_hdr_sax
{
    uint64_t u;
    struct bdk_rfoex_tx_hdr_sax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t sa                    : 48; /**< [ 47:  0](R/W) Source Ethernet MAC address. The following ordering within the field \<7:0\>
                                                                 at byte address 0, \<15:8\> at address 1, ..., \<47:40\> at address 0x5.
                                                                 RFOE(0..1)_TX_HDR_SA[7:0] = byte 6 of Ethernet packet.
                                                                 ...
                                                                 RFOE(0..1)_TX_HDR_SA[47:40] = byte 11 of Ethernet packet. */
#else /* Word 0 - Little Endian */
        uint64_t sa                    : 48; /**< [ 47:  0](R/W) Source Ethernet MAC address. The following ordering within the field \<7:0\>
                                                                 at byte address 0, \<15:8\> at address 1, ..., \<47:40\> at address 0x5.
                                                                 RFOE(0..1)_TX_HDR_SA[7:0] = byte 6 of Ethernet packet.
                                                                 ...
                                                                 RFOE(0..1)_TX_HDR_SA[47:40] = byte 11 of Ethernet packet. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_tx_hdr_sax_s cn; */
};
typedef union bdk_rfoex_tx_hdr_sax bdk_rfoex_tx_hdr_sax_t;

static inline uint64_t BDK_RFOEX_TX_HDR_SAX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_TX_HDR_SAX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=7)))
        return 0x87e043d00840ll + 0x80000ll * ((a) & 0x1) + 8ll * ((b) & 0x7);
    __bdk_csr_fatal("RFOEX_TX_HDR_SAX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_TX_HDR_SAX(a,b) bdk_rfoex_tx_hdr_sax_t
#define bustype_BDK_RFOEX_TX_HDR_SAX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_TX_HDR_SAX(a,b) "RFOEX_TX_HDR_SAX"
#define busnum_BDK_RFOEX_TX_HDR_SAX(a,b) (a)
#define arguments_BDK_RFOEX_TX_HDR_SAX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_tx_ind_seqnum_p_cfg
 *
 * RFOE TX Indirect SeqNum P-Counter Configuration Register
 * Transmit .seqNum p-counter configuration.  Refer to IEEE P1914.3/D3.0
 * Table 4-3 for details on p-counter configuration.
 *
 * This register indirectly accesses a table of 256 entries with p-counter
 * configuration for each transmit flow.
 *
 * Reads and writes to this register access the table entry specified by
 * RFOE()_TX_INDIRECT_INDEX[INDEX].
 *
 * Packet transmissions access entries based on the flow specified by
 * RFOE()_AB()_SLOT()_CONFIGURATION[FLOW_PTR].
 */
union bdk_rfoex_tx_ind_seqnum_p_cfg
{
    uint64_t u;
    struct bdk_rfoex_tx_ind_seqnum_p_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pinc                  : 32; /**< [ 63: 32](R/W) SeqNumPInc. Value to increment p-counter by on every sent packet.
                                                                 The increment value must be less than RFOE_TX_IND_SEQNUM_P_CFG[PMAX]. */
        uint64_t pmax                  : 32; /**< [ 31:  0](R/W) SeqNumPMax. Maximum numerical value of the p-counter field. Requirements:
                                                                 * [PMAX] \> [PINC] when RFOE()_TX_IND_SEQNUM_PROP_CFG[PINC_PROP] == 1.
                                                                 * [PMAX] \>= Initial RFOE()_TX_IND_SEQNUM_STATE[PVAL].
                                                                 * [PMAX] \> Maximum RoE length field when RFOE()_TX_IND_SEQNUM_PROP_CFG[PINC_PROP] == 2.
                                                                 * [PMAX] \<= 3 when (RFOE()_AB()_SLOT()_CONFIGURATION[ORDERINFOTYPE] == TIMESTAMP) */
#else /* Word 0 - Little Endian */
        uint64_t pmax                  : 32; /**< [ 31:  0](R/W) SeqNumPMax. Maximum numerical value of the p-counter field. Requirements:
                                                                 * [PMAX] \> [PINC] when RFOE()_TX_IND_SEQNUM_PROP_CFG[PINC_PROP] == 1.
                                                                 * [PMAX] \>= Initial RFOE()_TX_IND_SEQNUM_STATE[PVAL].
                                                                 * [PMAX] \> Maximum RoE length field when RFOE()_TX_IND_SEQNUM_PROP_CFG[PINC_PROP] == 2.
                                                                 * [PMAX] \<= 3 when (RFOE()_AB()_SLOT()_CONFIGURATION[ORDERINFOTYPE] == TIMESTAMP) */
        uint64_t pinc                  : 32; /**< [ 63: 32](R/W) SeqNumPInc. Value to increment p-counter by on every sent packet.
                                                                 The increment value must be less than RFOE_TX_IND_SEQNUM_P_CFG[PMAX]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_tx_ind_seqnum_p_cfg_s cn; */
};
typedef union bdk_rfoex_tx_ind_seqnum_p_cfg bdk_rfoex_tx_ind_seqnum_p_cfg_t;

static inline uint64_t BDK_RFOEX_TX_IND_SEQNUM_P_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_TX_IND_SEQNUM_P_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d00c00ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_TX_IND_SEQNUM_P_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_TX_IND_SEQNUM_P_CFG(a) bdk_rfoex_tx_ind_seqnum_p_cfg_t
#define bustype_BDK_RFOEX_TX_IND_SEQNUM_P_CFG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_TX_IND_SEQNUM_P_CFG(a) "RFOEX_TX_IND_SEQNUM_P_CFG"
#define busnum_BDK_RFOEX_TX_IND_SEQNUM_P_CFG(a) (a)
#define arguments_BDK_RFOEX_TX_IND_SEQNUM_P_CFG(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_tx_ind_seqnum_prop_cfg
 *
 * RFOE TX Indirect SeqNum Property Configuration Register
 * Transmit .seqNum configuration.  Refer to IEEE P1914.3/D3.0
 * Table 4-3 for details on sequence number configuration.
 *
 * This register indirectly accesses a table of 256 entries with p-counter
 * configuration for each transmit flow.
 *
 * Reads and writes to this register access the table entry specified by
 * RFOE()_TX_INDIRECT_INDEX[INDEX].
 *
 * Packet transmissions access entries based on the flow specified by
 * RFOE()_AB()_SLOT()_CONFIGURATION[FLOW_PTR].
 */
union bdk_rfoex_tx_ind_seqnum_prop_cfg
{
    uint64_t u;
    struct bdk_rfoex_tx_ind_seqnum_prop_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t seqnum_rsvd           : 32; /**< [ 63: 32](R/W) Static value for reserved field. */
        uint64_t reserved_7_31         : 25;
        uint64_t pinc_prop             : 3;  /**< [  6:  4](R/W) SeqNumPIncProp:
                                                                 0x0 = No increment.
                                                                 0x1 = Increment p-counter by RFOE()_TX_IND_SEQNUM_P_CFG[PINC] on each
                                                                 sent packet.
                                                                 0x2 = Increment by the RoE payload size on every sent packet.
                                                                 0x3 - 0x7 = Reserved. */
        uint64_t reserved_3            : 1;
        uint64_t qinc_prop             : 3;  /**< [  2:  0](R/W) SeqNumQIncProp:
                                                                 0x0 = No increment.
                                                                 0x1 = Increment q-counter by RFOE()_TX_IND_SEQNUM_Q_CFG[QINC] on each
                                                                 sent packet.
                                                                 0x2 - 0x7 = Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t qinc_prop             : 3;  /**< [  2:  0](R/W) SeqNumQIncProp:
                                                                 0x0 = No increment.
                                                                 0x1 = Increment q-counter by RFOE()_TX_IND_SEQNUM_Q_CFG[QINC] on each
                                                                 sent packet.
                                                                 0x2 - 0x7 = Reserved. */
        uint64_t reserved_3            : 1;
        uint64_t pinc_prop             : 3;  /**< [  6:  4](R/W) SeqNumPIncProp:
                                                                 0x0 = No increment.
                                                                 0x1 = Increment p-counter by RFOE()_TX_IND_SEQNUM_P_CFG[PINC] on each
                                                                 sent packet.
                                                                 0x2 = Increment by the RoE payload size on every sent packet.
                                                                 0x3 - 0x7 = Reserved. */
        uint64_t reserved_7_31         : 25;
        uint64_t seqnum_rsvd           : 32; /**< [ 63: 32](R/W) Static value for reserved field. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_tx_ind_seqnum_prop_cfg_s cn; */
};
typedef union bdk_rfoex_tx_ind_seqnum_prop_cfg bdk_rfoex_tx_ind_seqnum_prop_cfg_t;

static inline uint64_t BDK_RFOEX_TX_IND_SEQNUM_PROP_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_TX_IND_SEQNUM_PROP_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d00c10ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_TX_IND_SEQNUM_PROP_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_TX_IND_SEQNUM_PROP_CFG(a) bdk_rfoex_tx_ind_seqnum_prop_cfg_t
#define bustype_BDK_RFOEX_TX_IND_SEQNUM_PROP_CFG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_TX_IND_SEQNUM_PROP_CFG(a) "RFOEX_TX_IND_SEQNUM_PROP_CFG"
#define busnum_BDK_RFOEX_TX_IND_SEQNUM_PROP_CFG(a) (a)
#define arguments_BDK_RFOEX_TX_IND_SEQNUM_PROP_CFG(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_tx_ind_seqnum_q_cfg
 *
 * RFOE TX Indirect SeqNum Q-Counter Configuration Register
 * Transmit .seqNum q-counter configuration.  Refer to IEEE P1914.3/D3.0
 * Table 4-3 for details on q-counter configuration.
 *
 * This register indirectly accesses a table of 256 entries with p-counter
 * configuration for each transmit flow.
 *
 * Reads and writes to this register access the table entry specified by
 * RFOE()_TX_INDIRECT_INDEX[INDEX].
 *
 * Packet transmissions access entries based on the flow specified by
 * RFOE()_AB()_SLOT()_CONFIGURATION[FLOW_PTR].
 */
union bdk_rfoex_tx_ind_seqnum_q_cfg
{
    uint64_t u;
    struct bdk_rfoex_tx_ind_seqnum_q_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t qinc                  : 32; /**< [ 63: 32](R/W) SeqNumQInc. Value to increment the q-counter by on every sent packet.
                                                                 The increment value must be less than RFOE_TX_IND_SEQNUM_Q_CFG[QMAX]. */
        uint64_t qmax                  : 32; /**< [ 31:  0](R/W) SeqNumQMax. Maximum numerical value of the q-counter field. */
#else /* Word 0 - Little Endian */
        uint64_t qmax                  : 32; /**< [ 31:  0](R/W) SeqNumQMax. Maximum numerical value of the q-counter field. */
        uint64_t qinc                  : 32; /**< [ 63: 32](R/W) SeqNumQInc. Value to increment the q-counter by on every sent packet.
                                                                 The increment value must be less than RFOE_TX_IND_SEQNUM_Q_CFG[QMAX]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_tx_ind_seqnum_q_cfg_s cn; */
};
typedef union bdk_rfoex_tx_ind_seqnum_q_cfg bdk_rfoex_tx_ind_seqnum_q_cfg_t;

static inline uint64_t BDK_RFOEX_TX_IND_SEQNUM_Q_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_TX_IND_SEQNUM_Q_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d00c08ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_TX_IND_SEQNUM_Q_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_TX_IND_SEQNUM_Q_CFG(a) bdk_rfoex_tx_ind_seqnum_q_cfg_t
#define bustype_BDK_RFOEX_TX_IND_SEQNUM_Q_CFG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_TX_IND_SEQNUM_Q_CFG(a) "RFOEX_TX_IND_SEQNUM_Q_CFG"
#define busnum_BDK_RFOEX_TX_IND_SEQNUM_Q_CFG(a) (a)
#define arguments_BDK_RFOEX_TX_IND_SEQNUM_Q_CFG(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_tx_ind_seqnum_state
 *
 * RFOE TX Job Descriptor Table  SEQNUM STATE Register
 * Transmit .seqNum configuration.  Refer to IEEE P1914.3/D3.0
 * Table 4-3 for details on RoE sequence numbers.
 *
 * This register indirectly accesses a table of 256 entries with p-counter
 * configuration for each transmit flow.
 *
 * Reads and writes to this register access the table entry specified by
 * RFOE()_TX_INDIRECT_INDEX[INDEX].
 *
 * Packet transmissions access entries based on the flow specified by
 * RFOE()_AB()_SLOT()_CONFIGURATION[FLOW_PTR].
 */
union bdk_rfoex_tx_ind_seqnum_state
{
    uint64_t u;
    struct bdk_rfoex_tx_ind_seqnum_state_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pval                  : 32; /**< [ 63: 32](R/W) Value of the p-counter.
                                                                 The initial value must be less than RFOE()_TX_IND_SEQNUM_P_CFG[PMAX] */
        uint64_t qval                  : 32; /**< [ 31:  0](R/W) Value of the q-counter.
                                                                 The initial value must be less than RFOE()_TX_IND_SEQNUM_Q_CFG[QMAX] */
#else /* Word 0 - Little Endian */
        uint64_t qval                  : 32; /**< [ 31:  0](R/W) Value of the q-counter.
                                                                 The initial value must be less than RFOE()_TX_IND_SEQNUM_Q_CFG[QMAX] */
        uint64_t pval                  : 32; /**< [ 63: 32](R/W) Value of the p-counter.
                                                                 The initial value must be less than RFOE()_TX_IND_SEQNUM_P_CFG[PMAX] */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_tx_ind_seqnum_state_s cn; */
};
typedef union bdk_rfoex_tx_ind_seqnum_state bdk_rfoex_tx_ind_seqnum_state_t;

static inline uint64_t BDK_RFOEX_TX_IND_SEQNUM_STATE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_TX_IND_SEQNUM_STATE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d00c18ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_TX_IND_SEQNUM_STATE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_TX_IND_SEQNUM_STATE(a) bdk_rfoex_tx_ind_seqnum_state_t
#define bustype_BDK_RFOEX_TX_IND_SEQNUM_STATE(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_TX_IND_SEQNUM_STATE(a) "RFOEX_TX_IND_SEQNUM_STATE"
#define busnum_BDK_RFOEX_TX_IND_SEQNUM_STATE(a) (a)
#define arguments_BDK_RFOEX_TX_IND_SEQNUM_STATE(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_tx_indirect_index
 *
 * RFOE TX Indirect Index Register
 * Index for reading and writing RFOE TX configuration tables.
 */
union bdk_rfoex_tx_indirect_index
{
    uint64_t u;
    struct bdk_rfoex_tx_indirect_index_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t index                 : 8;  /**< [  7:  0](R/W) Index used to select entry in RFOE()_TX_IND_* tables. */
#else /* Word 0 - Little Endian */
        uint64_t index                 : 8;  /**< [  7:  0](R/W) Index used to select entry in RFOE()_TX_IND_* tables. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_tx_indirect_index_s cn; */
};
typedef union bdk_rfoex_tx_indirect_index bdk_rfoex_tx_indirect_index_t;

static inline uint64_t BDK_RFOEX_TX_INDIRECT_INDEX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_TX_INDIRECT_INDEX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d00bf8ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_TX_INDIRECT_INDEX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_TX_INDIRECT_INDEX(a) bdk_rfoex_tx_indirect_index_t
#define bustype_BDK_RFOEX_TX_INDIRECT_INDEX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_TX_INDIRECT_INDEX(a) "RFOEX_TX_INDIRECT_INDEX"
#define busnum_BDK_RFOEX_TX_INDIRECT_INDEX(a) (a)
#define arguments_BDK_RFOEX_TX_INDIRECT_INDEX(a) (a),-1,-1,-1

/**
 * Register (RSL) rfoe#_tx_lmac_cfg#
 *
 * RFOE TX Packet LMAC Configuration Register
 * Configures channel credits per LMAC.
 */
union bdk_rfoex_tx_lmac_cfgx
{
    uint64_t u;
    struct bdk_rfoex_tx_lmac_cfgx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t cc_count_stat         : 12; /**< [ 31: 20](RO/H) Channel-credit current count status.
                                                                 This value represents the current Channel credits available for this LMAC.
                                                                 The value gets reloaded when [DATA_PKT_TX_LMAC_EN] is set to 1 and
                                                                 the value is reloaded after reset is deasserted.
                                                                 This value is valid when [CC_ENABLE] is 0x2 or 0x3. */
        uint64_t cc_count              : 12; /**< [ 19:  8](R/W) Channel-credit unit count. This value indicates the maximum credit units allowed for
                                                                 this LMAC. One credit unit is one flit (up to 16 Bytes max) on the P2X bus.
                                                                 Packets are not allowed to flow when the cuurent value of [CC_COUNT_STAT] is less
                                                                 than packet lenght.
                                                                 In order to prevent blocking between CGX LMACs, [CC_ENABLE] should be set to 0x2
                                                                 or 0x3 and [CC_COUNT] appropriately configured.
                                                                 The recommended configuration is based on the LMAC TX buffer size. The LMAC TX
                                                                 buffer size is defined by CGX()_CMR_TX_LMACS[LMACS]. For example, if
                                                                 CGX()_CMR_TX_LMACS[LMACS]=0x4 (16 KB per LMAC), then [CC_COUNT] = 0xfff.
                                                                 [CC_COUNT] cannot be changed after [CC_ENABLE] is set to 0x2 or 0x3.
                                                                 When [CC_ENABLE] is set to 0x2 or 0x3 and setting [CC_COUNT]=0 is nonsensical. */
        uint64_t reserved_3_7          : 5;
        uint64_t cc_enable             : 2;  /**< [  2:  1](R/W) Channel Credit Check enable. Enables [CC_COUNT] channel credit processing for
                                                                 packets destined to this LMAC.
                                                                 _ [CC_ENABLE]=0 - Channel Credit Check is disabled.
                                                                 _ [CC_ENABLE]=1 - Channel Credit Check is disabled.
                                                                 _ [CC_ENABLE]=2 - Channel Credit Check is enabled.
                                                                 _                 The transmit state machine checks the packet length against the [CC_COUNT_STAT].
                                                                 _                 If the current packet length is \<= [CC_COUNT_STAT], the packet is sent to CGX.
                                                                 _                 If the current packet length is \> [CC_COUNT_STAT], the transmit state machine
                                                                 _                 stalls and waits untill the required [CC_COUNT] is available before sending
                                                                 _                 the packet.
                                                                 _ [CC_ENABLE]=3 - Channel Credit Check is enabled.
                                                                 _                 The transmit state machine checks the packet length against the [CC_COUNT_STAT].
                                                                 _                 If the current packet length is \<= [CC_COUNT_STAT], the packet is sent to CGX.
                                                                 _                 If the current packet length is \> [CC_COUNT_STAT], the
                                                                 _                 transmit state machine drops the packet. */
        uint64_t data_pkt_tx_lmac_en   : 1;  /**< [  0:  0](R/W) Enable TX traffic to CGX LMAC.
                                                                 Software must write to 1 to [DATA_PKT_TX_LMAC_EN] and
                                                                 [DATA_PKT_TX_EN] = 1 to enable TX traffic to this LMAC.
                                                                 When [DATA_PKT_TX_LMAC_EN] = 0, RFOE discards transmit packets destined to this LMAC. */
#else /* Word 0 - Little Endian */
        uint64_t data_pkt_tx_lmac_en   : 1;  /**< [  0:  0](R/W) Enable TX traffic to CGX LMAC.
                                                                 Software must write to 1 to [DATA_PKT_TX_LMAC_EN] and
                                                                 [DATA_PKT_TX_EN] = 1 to enable TX traffic to this LMAC.
                                                                 When [DATA_PKT_TX_LMAC_EN] = 0, RFOE discards transmit packets destined to this LMAC. */
        uint64_t cc_enable             : 2;  /**< [  2:  1](R/W) Channel Credit Check enable. Enables [CC_COUNT] channel credit processing for
                                                                 packets destined to this LMAC.
                                                                 _ [CC_ENABLE]=0 - Channel Credit Check is disabled.
                                                                 _ [CC_ENABLE]=1 - Channel Credit Check is disabled.
                                                                 _ [CC_ENABLE]=2 - Channel Credit Check is enabled.
                                                                 _                 The transmit state machine checks the packet length against the [CC_COUNT_STAT].
                                                                 _                 If the current packet length is \<= [CC_COUNT_STAT], the packet is sent to CGX.
                                                                 _                 If the current packet length is \> [CC_COUNT_STAT], the transmit state machine
                                                                 _                 stalls and waits untill the required [CC_COUNT] is available before sending
                                                                 _                 the packet.
                                                                 _ [CC_ENABLE]=3 - Channel Credit Check is enabled.
                                                                 _                 The transmit state machine checks the packet length against the [CC_COUNT_STAT].
                                                                 _                 If the current packet length is \<= [CC_COUNT_STAT], the packet is sent to CGX.
                                                                 _                 If the current packet length is \> [CC_COUNT_STAT], the
                                                                 _                 transmit state machine drops the packet. */
        uint64_t reserved_3_7          : 5;
        uint64_t cc_count              : 12; /**< [ 19:  8](R/W) Channel-credit unit count. This value indicates the maximum credit units allowed for
                                                                 this LMAC. One credit unit is one flit (up to 16 Bytes max) on the P2X bus.
                                                                 Packets are not allowed to flow when the cuurent value of [CC_COUNT_STAT] is less
                                                                 than packet lenght.
                                                                 In order to prevent blocking between CGX LMACs, [CC_ENABLE] should be set to 0x2
                                                                 or 0x3 and [CC_COUNT] appropriately configured.
                                                                 The recommended configuration is based on the LMAC TX buffer size. The LMAC TX
                                                                 buffer size is defined by CGX()_CMR_TX_LMACS[LMACS]. For example, if
                                                                 CGX()_CMR_TX_LMACS[LMACS]=0x4 (16 KB per LMAC), then [CC_COUNT] = 0xfff.
                                                                 [CC_COUNT] cannot be changed after [CC_ENABLE] is set to 0x2 or 0x3.
                                                                 When [CC_ENABLE] is set to 0x2 or 0x3 and setting [CC_COUNT]=0 is nonsensical. */
        uint64_t cc_count_stat         : 12; /**< [ 31: 20](RO/H) Channel-credit current count status.
                                                                 This value represents the current Channel credits available for this LMAC.
                                                                 The value gets reloaded when [DATA_PKT_TX_LMAC_EN] is set to 1 and
                                                                 the value is reloaded after reset is deasserted.
                                                                 This value is valid when [CC_ENABLE] is 0x2 or 0x3. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_tx_lmac_cfgx_s cn; */
};
typedef union bdk_rfoex_tx_lmac_cfgx bdk_rfoex_tx_lmac_cfgx_t;

static inline uint64_t BDK_RFOEX_TX_LMAC_CFGX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_TX_LMAC_CFGX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX_PASS2_X) && ((a<=1) && (b<=3)))
        return 0x87e043d00f80ll + 0x80000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    __bdk_csr_fatal("RFOEX_TX_LMAC_CFGX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_TX_LMAC_CFGX(a,b) bdk_rfoex_tx_lmac_cfgx_t
#define bustype_BDK_RFOEX_TX_LMAC_CFGX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_TX_LMAC_CFGX(a,b) "RFOEX_TX_LMAC_CFGX"
#define busnum_BDK_RFOEX_TX_LMAC_CFGX(a,b) (a)
#define arguments_BDK_RFOEX_TX_LMAC_CFGX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_tx_octs_stat#
 *
 * RFOE TX Packet Statistic Register
 * Counts the number of octets sent. One counter per LMAC.
 */
union bdk_rfoex_tx_octs_statx
{
    uint64_t u;
    struct bdk_rfoex_tx_octs_statx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) Number of octets sent. This excludes the FCS bytes. Wraps to zero at 2^48. */
#else /* Word 0 - Little Endian */
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) Number of octets sent. This excludes the FCS bytes. Wraps to zero at 2^48. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_tx_octs_statx_s cn; */
};
typedef union bdk_rfoex_tx_octs_statx bdk_rfoex_tx_octs_statx_t;

static inline uint64_t BDK_RFOEX_TX_OCTS_STATX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_TX_OCTS_STATX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=3)))
        return 0x87e043d00f40ll + 0x80000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    __bdk_csr_fatal("RFOEX_TX_OCTS_STATX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_TX_OCTS_STATX(a,b) bdk_rfoex_tx_octs_statx_t
#define bustype_BDK_RFOEX_TX_OCTS_STATX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_TX_OCTS_STATX(a,b) "RFOEX_TX_OCTS_STATX"
#define busnum_BDK_RFOEX_TX_OCTS_STATX(a,b) (a)
#define arguments_BDK_RFOEX_TX_OCTS_STATX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_tx_pkt_drop_stat#
 *
 * RFOE TX Packet Dropped Statistic Register
 * Counts the number of packets dropped. One counter per LMAC.
 */
union bdk_rfoex_tx_pkt_drop_statx
{
    uint64_t u;
    struct bdk_rfoex_tx_pkt_drop_statx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) Number of packets dropped. Wraps to zero at 2^48. */
#else /* Word 0 - Little Endian */
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) Number of packets dropped. Wraps to zero at 2^48. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_tx_pkt_drop_statx_s cn; */
};
typedef union bdk_rfoex_tx_pkt_drop_statx bdk_rfoex_tx_pkt_drop_statx_t;

static inline uint64_t BDK_RFOEX_TX_PKT_DROP_STATX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_TX_PKT_DROP_STATX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX_PASS2_X) && ((a<=1) && (b<=3)))
        return 0x87e043d00f60ll + 0x80000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    __bdk_csr_fatal("RFOEX_TX_PKT_DROP_STATX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_TX_PKT_DROP_STATX(a,b) bdk_rfoex_tx_pkt_drop_statx_t
#define bustype_BDK_RFOEX_TX_PKT_DROP_STATX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_TX_PKT_DROP_STATX(a,b) "RFOEX_TX_PKT_DROP_STATX"
#define busnum_BDK_RFOEX_TX_PKT_DROP_STATX(a,b) (a)
#define arguments_BDK_RFOEX_TX_PKT_DROP_STATX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_tx_pkt_stat#
 *
 * RFOE TX Packet Statistic Register
 * Counts the number of packets sent. One counter per LMAC.
 */
union bdk_rfoex_tx_pkt_statx
{
    uint64_t u;
    struct bdk_rfoex_tx_pkt_statx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) Number of packets sent. Wraps to zero at 2^48. */
#else /* Word 0 - Little Endian */
        uint64_t stat                  : 48; /**< [ 47:  0](R/W/H) Number of packets sent. Wraps to zero at 2^48. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_tx_pkt_statx_s cn; */
};
typedef union bdk_rfoex_tx_pkt_statx bdk_rfoex_tx_pkt_statx_t;

static inline uint64_t BDK_RFOEX_TX_PKT_STATX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_TX_PKT_STATX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=3)))
        return 0x87e043d00f20ll + 0x80000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    __bdk_csr_fatal("RFOEX_TX_PKT_STATX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_TX_PKT_STATX(a,b) bdk_rfoex_tx_pkt_statx_t
#define bustype_BDK_RFOEX_TX_PKT_STATX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_TX_PKT_STATX(a,b) "RFOEX_TX_PKT_STATX"
#define busnum_BDK_RFOEX_TX_PKT_STATX(a,b) (a)
#define arguments_BDK_RFOEX_TX_PKT_STATX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) rfoe#_tx_scratch
 *
 * INTERNAL: Scratch Register
 *
 * Scratch register.
 */
union bdk_rfoex_tx_scratch
{
    uint64_t u;
    struct bdk_rfoex_tx_scratch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Scratch data. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Scratch data. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rfoex_tx_scratch_s cn; */
};
typedef union bdk_rfoex_tx_scratch bdk_rfoex_tx_scratch_t;

static inline uint64_t BDK_RFOEX_TX_SCRATCH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RFOEX_TX_SCRATCH(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043d00f00ll + 0x80000ll * ((a) & 0x1);
    __bdk_csr_fatal("RFOEX_TX_SCRATCH", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RFOEX_TX_SCRATCH(a) bdk_rfoex_tx_scratch_t
#define bustype_BDK_RFOEX_TX_SCRATCH(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RFOEX_TX_SCRATCH(a) "RFOEX_TX_SCRATCH"
#define busnum_BDK_RFOEX_TX_SCRATCH(a) (a)
#define arguments_BDK_RFOEX_TX_SCRATCH(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_RFOE_H__ */
