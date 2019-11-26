#ifndef __BDK_CSRS_RMAP_H__
#define __BDK_CSRS_RMAP_H__
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
 * OcteonTX RMAP.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Structure rmap_lte_mode_s
 *
 * RMAP LTE MODE Structure
 * This structure defines the format of the job configuration of RMAP jobs in LTE Mode.
 */
union bdk_rmap_lte_mode_s
{
    uint64_t u[4];
    struct bdk_rmap_lte_mode_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t phy_mode              : 1;  /**< [ 63: 63] This flag sets mode of operation. Must be set to 0 to indicate LTE mode. */
        uint64_t reserved_62           : 1;
        uint64_t tti_mode              : 2;  /**< [ 61: 60] TTI Mode:
                                                                 0x0 = normal 1ms TTI.
                                                                 0x1 = 7-OS sTTI.
                                                                 0x2 = 2/3-OS sTTI.
                                                                 0x3 = Flexible Symbol with no UCI. */
        uint64_t bypass_scrambler      : 1;  /**< [ 59: 59] If set to 1, bypass scrambling. */
        uint64_t bypass_modulator      : 1;  /**< [ 58: 58] If set to 1, bypass modulator/RS insertion and DFT. */
        uint64_t bypass_dft            : 1;  /**< [ 57: 57] If set to 1, bypass DFT. */
        uint64_t dft_standalone_flag   : 1;  /**< [ 56: 56] When set to 1, this flag sets the DFT engine as a standalone module. In this
                                                                 mode, both the functions before and after DFT/IDFT engine are bypassed.
                                                                 The DFT/IDFT result is DMAed directly to the output as in the one layer, no
                                                                 frequency hopping, allocation type 0 case.
                                                                 0x0 = used as non-standalone module in the RMAP chain.
                                                                 0x1 = used as standalone DFT/IDFT engine. */
        uint64_t bypass_data_uci_mux   : 1;  /**< [ 55: 55] If set to 1, Data_UCI multiplexer is bypassed. */
        uint64_t reserved_53_54        : 2;
        uint64_t num_rb                : 9;  /**< [ 52: 44] The total number of RBs in a subframe.
                                                                 If [RES_ALLC_TYPE] = 1, this is the sum of number of RBs for Set 0 and Set 1.
                                                                 For LTE, valid range is [1:108]. */
        uint64_t reserved_43           : 1;
        uint64_t num_layers            : 3;  /**< [ 42: 40] Number of layers for PUSCH channel:
                                                                 0x1 = 1 Layer.
                                                                 0x2 = 2 Layers. */
        uint64_t mod_order             : 4;  /**< [ 39: 36] Modulation order:
                                                                 0x2 = QPSK.
                                                                 0x4 = 16-QAM.
                                                                 0x6 = 64-QAM.
                                                                 0x8 = 256-QAM. */
        uint64_t num_scalar_qam        : 4;  /**< [ 35: 32] The number of bits the floating point modulation values are left shifted to produce
                                                                 the fixed point complex values. Valid range is [1,15]. */
        uint64_t dft_idft_flag         : 1;  /**< [ 31: 31] In DFT-only mode ([DFT_STANDALONE_FLAG] = 1), this flag sets the DFT or IDFT function:
                                                                   0x0 = DFT.
                                                                   0x1 = IDFT.
                                                                 When [DFT_STANDALONE_FLAG] = 0, [DFT_IDFT_FLAG] must be 0. */
        uint64_t reserved_30           : 1;
        uint64_t ndft_indx             : 6;  /**< [ 29: 24] Index to the NDFTs that are defined in the list of supported NDFTs.
                                                                 Valid range is [0,34].
                                                                   0x0 = NDFT = 12.
                                                                   0x1 = NDFT = 24.
                                                                   ....
                                                                   0x21 = NDFT = 1200.
                                                                   0x22 = NDFT = 1296.
                                                                   0x23 = NDFT = 1200.
                                                                   0x24 = NDFT = 1296. */
        uint64_t reserved_21_23        : 3;
        uint64_t rs_bits_last          : 5;  /**< [ 20: 16] This parameter controls the output scaling at the last stage of the DFT/IDFT.
                                                                 The DFT/IDFT output is right shifted by [RS_BITS_LAST]. Valid range is [15,19]. */
        uint64_t reserved_14_15        : 2;
        uint64_t g_prime               : 14; /**< [ 13:  0] Total number of coded symbols in the transport block.
                                                                 Total number of coded bits is [G_PRIME]*[NUM_LAYERS]*[MOD_ORDER].
                                                                 Valid range is [0, 15552] with the following condition:
                                                                 [G_PRIME] \<= [NUM_SYMB_PUSCH]*12*[NUM_RB]. */
#else /* Word 0 - Little Endian */
        uint64_t g_prime               : 14; /**< [ 13:  0] Total number of coded symbols in the transport block.
                                                                 Total number of coded bits is [G_PRIME]*[NUM_LAYERS]*[MOD_ORDER].
                                                                 Valid range is [0, 15552] with the following condition:
                                                                 [G_PRIME] \<= [NUM_SYMB_PUSCH]*12*[NUM_RB]. */
        uint64_t reserved_14_15        : 2;
        uint64_t rs_bits_last          : 5;  /**< [ 20: 16] This parameter controls the output scaling at the last stage of the DFT/IDFT.
                                                                 The DFT/IDFT output is right shifted by [RS_BITS_LAST]. Valid range is [15,19]. */
        uint64_t reserved_21_23        : 3;
        uint64_t ndft_indx             : 6;  /**< [ 29: 24] Index to the NDFTs that are defined in the list of supported NDFTs.
                                                                 Valid range is [0,34].
                                                                   0x0 = NDFT = 12.
                                                                   0x1 = NDFT = 24.
                                                                   ....
                                                                   0x21 = NDFT = 1200.
                                                                   0x22 = NDFT = 1296.
                                                                   0x23 = NDFT = 1200.
                                                                   0x24 = NDFT = 1296. */
        uint64_t reserved_30           : 1;
        uint64_t dft_idft_flag         : 1;  /**< [ 31: 31] In DFT-only mode ([DFT_STANDALONE_FLAG] = 1), this flag sets the DFT or IDFT function:
                                                                   0x0 = DFT.
                                                                   0x1 = IDFT.
                                                                 When [DFT_STANDALONE_FLAG] = 0, [DFT_IDFT_FLAG] must be 0. */
        uint64_t num_scalar_qam        : 4;  /**< [ 35: 32] The number of bits the floating point modulation values are left shifted to produce
                                                                 the fixed point complex values. Valid range is [1,15]. */
        uint64_t mod_order             : 4;  /**< [ 39: 36] Modulation order:
                                                                 0x2 = QPSK.
                                                                 0x4 = 16-QAM.
                                                                 0x6 = 64-QAM.
                                                                 0x8 = 256-QAM. */
        uint64_t num_layers            : 3;  /**< [ 42: 40] Number of layers for PUSCH channel:
                                                                 0x1 = 1 Layer.
                                                                 0x2 = 2 Layers. */
        uint64_t reserved_43           : 1;
        uint64_t num_rb                : 9;  /**< [ 52: 44] The total number of RBs in a subframe.
                                                                 If [RES_ALLC_TYPE] = 1, this is the sum of number of RBs for Set 0 and Set 1.
                                                                 For LTE, valid range is [1:108]. */
        uint64_t reserved_53_54        : 2;
        uint64_t bypass_data_uci_mux   : 1;  /**< [ 55: 55] If set to 1, Data_UCI multiplexer is bypassed. */
        uint64_t dft_standalone_flag   : 1;  /**< [ 56: 56] When set to 1, this flag sets the DFT engine as a standalone module. In this
                                                                 mode, both the functions before and after DFT/IDFT engine are bypassed.
                                                                 The DFT/IDFT result is DMAed directly to the output as in the one layer, no
                                                                 frequency hopping, allocation type 0 case.
                                                                 0x0 = used as non-standalone module in the RMAP chain.
                                                                 0x1 = used as standalone DFT/IDFT engine. */
        uint64_t bypass_dft            : 1;  /**< [ 57: 57] If set to 1, bypass DFT. */
        uint64_t bypass_modulator      : 1;  /**< [ 58: 58] If set to 1, bypass modulator/RS insertion and DFT. */
        uint64_t bypass_scrambler      : 1;  /**< [ 59: 59] If set to 1, bypass scrambling. */
        uint64_t tti_mode              : 2;  /**< [ 61: 60] TTI Mode:
                                                                 0x0 = normal 1ms TTI.
                                                                 0x1 = 7-OS sTTI.
                                                                 0x2 = 2/3-OS sTTI.
                                                                 0x3 = Flexible Symbol with no UCI. */
        uint64_t reserved_62           : 1;
        uint64_t phy_mode              : 1;  /**< [ 63: 63] This flag sets mode of operation. Must be set to 0 to indicate LTE mode. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_125_127      : 3;
        uint64_t stti_2os_ack_pos      : 1;  /**< [124:124] The symbol index for the ACK mapping in the case of two data symbols for
                                                                 [TTI_MODE] = 0x2 (2/3-OS sTTI):
                                                                 0x0 = ACK on symbol 0 and RI on symbol 1.
                                                                 0x1 = ACK on symbol l and RI on symbol 0.

                                                                 This field is ignored for [TTI_MODE] = 0x0,0x1,0x3. */
        uint64_t reserved_123          : 1;
        uint64_t ack_enc_cat           : 3;  /**< [122:120] ACK encoding category:
                                                                 0x0 = No ACK or if [TTI_MODE] = 0x3, number of input bits = 0.
                                                                 0x1 = O^ACK = 0x1, number of input bits = 1.
                                                                 0x2 = O^ACK = 0x1, ACK bundling with number of input bits = 1.
                                                                 0x3 = O^ACK = 0x2, number of input bits = 2.
                                                                 0x4 = O^ACK = 0x2, ACK bundling with number of input bits = 2.
                                                                 0x5 = 3 \<= O^ACK \<= 11, number of input bits = 32.
                                                                 0x6 = 11 \< O^ACK \<= 22, number of input bits = 64.
                                                                 0x7 = O^ACK \> 22, (encoder and repetition are bypassed). */
        uint64_t reserved_119          : 1;
        uint64_t ri_enc_cat            : 3;  /**< [118:116] RI encoding category:
                                                                 0x0 = no RI or if [TTI_MODE] = 0x3.
                                                                 0x1 = O^RI = 1.
                                                                 0x2 = O^RI = 2.
                                                                 0x3 = 3 \<= O^RI \<= 11.
                                                                 0x4 = 11 \< O^RI \<= 22.
                                                                 0x5 = O^RI \> 22 (encoder and repetition are bypassed).
                                                                 0x6-07 = Reserved. */
        uint64_t reserved_104_115      : 12;
        uint64_t num_symb_pusch        : 4;  /**< [103:100] Number of SC-FDMA symbols carrying PUSCH in a TTI. Used for UL-SCH channel interleaving.

                                                                 _ When [TTI_MODE] = 0x0 (1ms TTI) and [CP_MODE] = 1, valid range is [9,10].

                                                                 _ When [TTI_MODE] = 0x0 (1ms TTI) and [CP_MODE] = 0, valid range is [11,12].

                                                                 _ When [TTI_MODE] = 0x1 (7-OS TTI), valid range is [5,6].

                                                                 _ When [TTI_MODE] = 0x2 (2/3-OS sTTI), valid range is [1,2].

                                                                 _ When [TTI_MODE] = 0x3 (Flexible symbol), valid range is [1,12]. */
        uint64_t reserved_99           : 1;
        uint64_t cp_mode               : 1;  /**< [ 98: 98] CP type for normal TTI ([TTI_MODE] = 0x0).
                                                                 0x0 = Normal CP.
                                                                 0x1 = Extended CP.

                                                                 When[TTI_MODE] = 0x1,0x2,0x3, this field is ignored. */
        uint64_t reserved_97           : 1;
        uint64_t symb_byte_aligned     : 1;  /**< [ 96: 96] If set to 1, each [MOD_ORDER] bits are mapped to one byte. */
        uint64_t reserved_95           : 1;
        uint64_t scrambling_cinit      : 31; /**< [ 94: 64] Initial value of the second m-sequence of the scrambler. Valid range is [0, 2^31-1]. */
#else /* Word 1 - Little Endian */
        uint64_t scrambling_cinit      : 31; /**< [ 94: 64] Initial value of the second m-sequence of the scrambler. Valid range is [0, 2^31-1]. */
        uint64_t reserved_95           : 1;
        uint64_t symb_byte_aligned     : 1;  /**< [ 96: 96] If set to 1, each [MOD_ORDER] bits are mapped to one byte. */
        uint64_t reserved_97           : 1;
        uint64_t cp_mode               : 1;  /**< [ 98: 98] CP type for normal TTI ([TTI_MODE] = 0x0).
                                                                 0x0 = Normal CP.
                                                                 0x1 = Extended CP.

                                                                 When[TTI_MODE] = 0x1,0x2,0x3, this field is ignored. */
        uint64_t reserved_99           : 1;
        uint64_t num_symb_pusch        : 4;  /**< [103:100] Number of SC-FDMA symbols carrying PUSCH in a TTI. Used for UL-SCH channel interleaving.

                                                                 _ When [TTI_MODE] = 0x0 (1ms TTI) and [CP_MODE] = 1, valid range is [9,10].

                                                                 _ When [TTI_MODE] = 0x0 (1ms TTI) and [CP_MODE] = 0, valid range is [11,12].

                                                                 _ When [TTI_MODE] = 0x1 (7-OS TTI), valid range is [5,6].

                                                                 _ When [TTI_MODE] = 0x2 (2/3-OS sTTI), valid range is [1,2].

                                                                 _ When [TTI_MODE] = 0x3 (Flexible symbol), valid range is [1,12]. */
        uint64_t reserved_104_115      : 12;
        uint64_t ri_enc_cat            : 3;  /**< [118:116] RI encoding category:
                                                                 0x0 = no RI or if [TTI_MODE] = 0x3.
                                                                 0x1 = O^RI = 1.
                                                                 0x2 = O^RI = 2.
                                                                 0x3 = 3 \<= O^RI \<= 11.
                                                                 0x4 = 11 \< O^RI \<= 22.
                                                                 0x5 = O^RI \> 22 (encoder and repetition are bypassed).
                                                                 0x6-07 = Reserved. */
        uint64_t reserved_119          : 1;
        uint64_t ack_enc_cat           : 3;  /**< [122:120] ACK encoding category:
                                                                 0x0 = No ACK or if [TTI_MODE] = 0x3, number of input bits = 0.
                                                                 0x1 = O^ACK = 0x1, number of input bits = 1.
                                                                 0x2 = O^ACK = 0x1, ACK bundling with number of input bits = 1.
                                                                 0x3 = O^ACK = 0x2, number of input bits = 2.
                                                                 0x4 = O^ACK = 0x2, ACK bundling with number of input bits = 2.
                                                                 0x5 = 3 \<= O^ACK \<= 11, number of input bits = 32.
                                                                 0x6 = 11 \< O^ACK \<= 22, number of input bits = 64.
                                                                 0x7 = O^ACK \> 22, (encoder and repetition are bypassed). */
        uint64_t reserved_123          : 1;
        uint64_t stti_2os_ack_pos      : 1;  /**< [124:124] The symbol index for the ACK mapping in the case of two data symbols for
                                                                 [TTI_MODE] = 0x2 (2/3-OS sTTI):
                                                                 0x0 = ACK on symbol 0 and RI on symbol 1.
                                                                 0x1 = ACK on symbol l and RI on symbol 0.

                                                                 This field is ignored for [TTI_MODE] = 0x0,0x1,0x3. */
        uint64_t reserved_125_127      : 3;
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t reserved_190_191      : 2;
        uint64_t num_cqi_re            : 14; /**< [189:176] Number of CQI REs per layer. Valid range is [0,15552] with the condition that
                                                                 [NUM_CQI_RE] \<= [NM_SYMB_PUSCH] * [NUM_RB] * 12. */
        uint64_t reserved_173_175      : 3;
        uint64_t num_ri_re             : 13; /**< [172:160] Number of RI REs per layer (Q'RI). If Q'RI = 0, no RI bits are received. Valid
                                                                 range is [0, 5184] with the following constraints:

                                                                 _ When [RI_ENC_CAT] = 0x0 or [TTI_MODE] = 0x3, valid range is 0.

                                                                 _ When [RI_ENC_CAT] \>= 0x1 and [TTI_MODE] = 0x0, valid range is [1,48*[NUM_RB]].

                                                                 _ When [RI_ENC_CAT] \>= 0x1 and [TTI_MODE] = 0x1, valid range is [1,24*[NUM_RB]].

                                                                 _ When [RI_ENC_CAT] \>= 0x1 and [TTI_MODE] = 0x2, valid range is [1,12*[NUM_RB]]. */
        uint64_t reserved_157_159      : 3;
        uint64_t num_ack_re            : 13; /**< [156:144] Number of ACK REs per layer (Q'ACK). Valid range is [0,5184] with the following conditions:

                                                                 _ When Q_ACK = 0 no ACK bits are received.

                                                                 _ When [ACK_ENC_CAT] = 0 or [TTI_MODE] = 0x3, must be 0x0.

                                                                 _ When [ACK_ENC_CAT] \>= 0x1 and [TTI_MODE] = 0x0, valid range is [1,48*[NUM_RB]].

                                                                 _ When [ACK_ENC_CAT] \>= 0x1 and [TTI_MODE] = 0x1, valid range is [1,24*[NUM_RB]].

                                                                 _ When [ACK_ENC_CAT] \>= 0x1, [NMU_SYMB_PUSCH] = 0x2 and [TTI_MODE] = 0x2, valid
                                                                 range is [1,12*[NUM_RB]].

                                                                 _ When [ACK_ENC_CAT] \>= 0x1, [NMU_SYMB_PUSCH] = 0x1 and [TTI_MODE] = 0x2, valid
                                                                 range is [1, 12*[NUM_RB] - [NUM_RI_RE]]. */
        uint64_t reserved_139_143      : 5;
        uint64_t r_prime_mux           : 11; /**< [138:128] Size R'mux of the channel interleaver matrix. Valid range is [0,1296] with the
                                                                 condition that [R_PRIME_MUX] = 12 * [NUM_RB]. */
#else /* Word 2 - Little Endian */
        uint64_t r_prime_mux           : 11; /**< [138:128] Size R'mux of the channel interleaver matrix. Valid range is [0,1296] with the
                                                                 condition that [R_PRIME_MUX] = 12 * [NUM_RB]. */
        uint64_t reserved_139_143      : 5;
        uint64_t num_ack_re            : 13; /**< [156:144] Number of ACK REs per layer (Q'ACK). Valid range is [0,5184] with the following conditions:

                                                                 _ When Q_ACK = 0 no ACK bits are received.

                                                                 _ When [ACK_ENC_CAT] = 0 or [TTI_MODE] = 0x3, must be 0x0.

                                                                 _ When [ACK_ENC_CAT] \>= 0x1 and [TTI_MODE] = 0x0, valid range is [1,48*[NUM_RB]].

                                                                 _ When [ACK_ENC_CAT] \>= 0x1 and [TTI_MODE] = 0x1, valid range is [1,24*[NUM_RB]].

                                                                 _ When [ACK_ENC_CAT] \>= 0x1, [NMU_SYMB_PUSCH] = 0x2 and [TTI_MODE] = 0x2, valid
                                                                 range is [1,12*[NUM_RB]].

                                                                 _ When [ACK_ENC_CAT] \>= 0x1, [NMU_SYMB_PUSCH] = 0x1 and [TTI_MODE] = 0x2, valid
                                                                 range is [1, 12*[NUM_RB] - [NUM_RI_RE]]. */
        uint64_t reserved_157_159      : 3;
        uint64_t num_ri_re             : 13; /**< [172:160] Number of RI REs per layer (Q'RI). If Q'RI = 0, no RI bits are received. Valid
                                                                 range is [0, 5184] with the following constraints:

                                                                 _ When [RI_ENC_CAT] = 0x0 or [TTI_MODE] = 0x3, valid range is 0.

                                                                 _ When [RI_ENC_CAT] \>= 0x1 and [TTI_MODE] = 0x0, valid range is [1,48*[NUM_RB]].

                                                                 _ When [RI_ENC_CAT] \>= 0x1 and [TTI_MODE] = 0x1, valid range is [1,24*[NUM_RB]].

                                                                 _ When [RI_ENC_CAT] \>= 0x1 and [TTI_MODE] = 0x2, valid range is [1,12*[NUM_RB]]. */
        uint64_t reserved_173_175      : 3;
        uint64_t num_cqi_re            : 14; /**< [189:176] Number of CQI REs per layer. Valid range is [0,15552] with the condition that
                                                                 [NUM_CQI_RE] \<= [NM_SYMB_PUSCH] * [NUM_RB] * 12. */
        uint64_t reserved_190_191      : 2;
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t reserved_251_255      : 5;
        uint64_t data_bit_order        : 1;  /**< [250:250] This field selects bit order for data input.
                                                                 0x0 = MSB first within a byte.
                                                                 0x1 = LSB first within a byte. */
        uint64_t data_byte_order       : 2;  /**< [249:248] This field selects byte order for data input.
                                                                 0x0 = Little endian, byte 0 is bits 7..0.
                                                                 0x1 = Byte swapping within 64 bit words from little endian.
                                                                 0x2 = Byte swapping within 32 bit words from little endian.
                                                                 0x3 = Reserved. */
        uint64_t reserved_247          : 1;
        uint64_t cqi_bit_order         : 1;  /**< [246:246] This field selects bit order for CQI input.
                                                                 0x0 = MSB first within a byte.
                                                                 0x1 = LSB first within a byte. */
        uint64_t cqi_byte_order        : 2;  /**< [245:244] This field selects byte order for CQI input.
                                                                 0x0 = Little endian, byte 0 is bits 7..0.
                                                                 0x1 = Byte swapping within 64 bit words from little endian.
                                                                 0x2 = Byte swapping within 32 bit words from little endian.
                                                                 0x3 = Reserved. */
        uint64_t reserved_243          : 1;
        uint64_t ri_bit_order          : 1;  /**< [242:242] This field selects bit order for RI input.
                                                                 0x0 = MSB first within a byte.
                                                                 0x1 = LSB first within a byte. */
        uint64_t ri_byte_order         : 2;  /**< [241:240] This field selects byte order for RI input.
                                                                 0x0 = Little endian, byte 0 is bits 7..0.
                                                                 0x1 = Byte swapping within 64-bit words from little endian.
                                                                 0x2 = Byte swapping within 32-bit words from little endian.
                                                                 0x3 = Reserved. */
        uint64_t reserved_239          : 1;
        uint64_t ack_bit_order         : 1;  /**< [238:238] This field selects bit order for ACK input.
                                                                 0x0 = MSB first within a byte.
                                                                 0x1 = LSB first within a byte. */
        uint64_t ack_byte_order        : 2;  /**< [237:236] This field specifies byte order for ACK input.
                                                                 0x0 = Little endian, byte 0 is bits 7..0.
                                                                 0x1 = Byte swapping within 64-bit words from little endian.
                                                                 0x2 = Byte swapping within 32-bit words from little endian.
                                                                 0x3 = Reserved. */
        uint64_t reserved_234_235      : 2;
        uint64_t num_encoded_cqi_bits  : 18; /**< [233:216] The number of encoded CQI bits. When CQI is RM coded, this field must be 64.
                                                                 For convolutional code case, the recoded CQI bits can be fully rate-matched this
                                                                 field must be [NUM_LAYERS] * QCQI.

                                                                 _ When [NUM_CQI_RE] \> 0, valid range is [1, [NUM_CQI_RE] * [MOD_ORDER] *
                                                                 [NUM_LAYERS]] where [NUM_CQI_RE] * [MOD_ORDER] * [NUM_LAYERS] \<= 248832.

                                                                 _ When [NUM_CQI_RE] = 0, this field must be zero. */
        uint64_t reserved_214_215      : 2;
        uint64_t num_bundled_i         : 2;  /**< [213:212] Index to the scrambling sequence table for ACK bundling.
                                                                 [NUM_BUNDLED_I] = (N_bundled - 1) mod 4, where N_bundled is determined as
                                                                 described in Section 7.3 of R[3]. */
        uint64_t reserved_210_211      : 2;
        uint64_t res_alloc_type        : 1;  /**< [209:209] The resource allocation type:
                                                                 0x0 = Type 0.
                                                                 0x1 = Type 1. */
        uint64_t freq_hop_type         : 1;  /**< [208:208] Intra-subframe frequency hopping flag:
                                                                 0x0 = No intra-subframe frequency hopping.
                                                                 0x1 = Intra-subframe frequency hopping.
                                                                 When [RES_ALLOC_TYPE] = 1, this field must be zero. */
        uint64_t reserved_207          : 1;
        uint64_t length_rb_set0        : 7;  /**< [206:200] The length in terms of contiguously allocated resource blocks (L_CRBs_3_1) for set0.
                                                                 Valid range is [1, 108]. */
        uint64_t reserved_199          : 1;
        uint64_t length_rb_set1        : 7;  /**< [198:192] The length in terms of contiguously allocated resource blocks (L_CRBs_3_1) for set1.
                                                                 When [RES_ALLOC_TYPE] = 0x1, its valid range is [1, 108] with the condition that
                                                                 [LENGTH_RB_SET1] = [NUM_RB] - [LENGTH_RB_SET0].
                                                                 When [RES_ALLOC_TYPE] = 0x0, this field is ignored. */
#else /* Word 3 - Little Endian */
        uint64_t length_rb_set1        : 7;  /**< [198:192] The length in terms of contiguously allocated resource blocks (L_CRBs_3_1) for set1.
                                                                 When [RES_ALLOC_TYPE] = 0x1, its valid range is [1, 108] with the condition that
                                                                 [LENGTH_RB_SET1] = [NUM_RB] - [LENGTH_RB_SET0].
                                                                 When [RES_ALLOC_TYPE] = 0x0, this field is ignored. */
        uint64_t reserved_199          : 1;
        uint64_t length_rb_set0        : 7;  /**< [206:200] The length in terms of contiguously allocated resource blocks (L_CRBs_3_1) for set0.
                                                                 Valid range is [1, 108]. */
        uint64_t reserved_207          : 1;
        uint64_t freq_hop_type         : 1;  /**< [208:208] Intra-subframe frequency hopping flag:
                                                                 0x0 = No intra-subframe frequency hopping.
                                                                 0x1 = Intra-subframe frequency hopping.
                                                                 When [RES_ALLOC_TYPE] = 1, this field must be zero. */
        uint64_t res_alloc_type        : 1;  /**< [209:209] The resource allocation type:
                                                                 0x0 = Type 0.
                                                                 0x1 = Type 1. */
        uint64_t reserved_210_211      : 2;
        uint64_t num_bundled_i         : 2;  /**< [213:212] Index to the scrambling sequence table for ACK bundling.
                                                                 [NUM_BUNDLED_I] = (N_bundled - 1) mod 4, where N_bundled is determined as
                                                                 described in Section 7.3 of R[3]. */
        uint64_t reserved_214_215      : 2;
        uint64_t num_encoded_cqi_bits  : 18; /**< [233:216] The number of encoded CQI bits. When CQI is RM coded, this field must be 64.
                                                                 For convolutional code case, the recoded CQI bits can be fully rate-matched this
                                                                 field must be [NUM_LAYERS] * QCQI.

                                                                 _ When [NUM_CQI_RE] \> 0, valid range is [1, [NUM_CQI_RE] * [MOD_ORDER] *
                                                                 [NUM_LAYERS]] where [NUM_CQI_RE] * [MOD_ORDER] * [NUM_LAYERS] \<= 248832.

                                                                 _ When [NUM_CQI_RE] = 0, this field must be zero. */
        uint64_t reserved_234_235      : 2;
        uint64_t ack_byte_order        : 2;  /**< [237:236] This field specifies byte order for ACK input.
                                                                 0x0 = Little endian, byte 0 is bits 7..0.
                                                                 0x1 = Byte swapping within 64-bit words from little endian.
                                                                 0x2 = Byte swapping within 32-bit words from little endian.
                                                                 0x3 = Reserved. */
        uint64_t ack_bit_order         : 1;  /**< [238:238] This field selects bit order for ACK input.
                                                                 0x0 = MSB first within a byte.
                                                                 0x1 = LSB first within a byte. */
        uint64_t reserved_239          : 1;
        uint64_t ri_byte_order         : 2;  /**< [241:240] This field selects byte order for RI input.
                                                                 0x0 = Little endian, byte 0 is bits 7..0.
                                                                 0x1 = Byte swapping within 64-bit words from little endian.
                                                                 0x2 = Byte swapping within 32-bit words from little endian.
                                                                 0x3 = Reserved. */
        uint64_t ri_bit_order          : 1;  /**< [242:242] This field selects bit order for RI input.
                                                                 0x0 = MSB first within a byte.
                                                                 0x1 = LSB first within a byte. */
        uint64_t reserved_243          : 1;
        uint64_t cqi_byte_order        : 2;  /**< [245:244] This field selects byte order for CQI input.
                                                                 0x0 = Little endian, byte 0 is bits 7..0.
                                                                 0x1 = Byte swapping within 64 bit words from little endian.
                                                                 0x2 = Byte swapping within 32 bit words from little endian.
                                                                 0x3 = Reserved. */
        uint64_t cqi_bit_order         : 1;  /**< [246:246] This field selects bit order for CQI input.
                                                                 0x0 = MSB first within a byte.
                                                                 0x1 = LSB first within a byte. */
        uint64_t reserved_247          : 1;
        uint64_t data_byte_order       : 2;  /**< [249:248] This field selects byte order for data input.
                                                                 0x0 = Little endian, byte 0 is bits 7..0.
                                                                 0x1 = Byte swapping within 64 bit words from little endian.
                                                                 0x2 = Byte swapping within 32 bit words from little endian.
                                                                 0x3 = Reserved. */
        uint64_t data_bit_order        : 1;  /**< [250:250] This field selects bit order for data input.
                                                                 0x0 = MSB first within a byte.
                                                                 0x1 = LSB first within a byte. */
        uint64_t reserved_251_255      : 5;
#endif /* Word 3 - End */
    } s;
    /* struct bdk_rmap_lte_mode_s_s cn; */
};

/**
 * Structure rmap_nr_mode_s
 *
 * RMAP 5G-NR MODE Word0 Structure
 * This structure defines the format of the job configuration for all RMAP
 * jobs when in NR Mode.
 */
union bdk_rmap_nr_mode_s
{
    uint64_t u[7];
    struct bdk_rmap_nr_mode_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t phy_mode              : 1;  /**< [ 63: 63] This flag sets mode of operation. It must be set to 1 to indicate NR mode. */
        uint64_t reserved_60_62        : 3;
        uint64_t bypass_scrambler      : 1;  /**< [ 59: 59] If set to 1, bypass scrambling. */
        uint64_t bypass_modulator      : 1;  /**< [ 58: 58] If set to 1, modulator/RS insertion and DFT are bypassed. When
                                                                 [BYPASS_MODULATOR] = 1, [RS_INSERTION_ENABLE] must be  0 and [BYPASS_DFT] must
                                                                 be 1. */
        uint64_t bypass_dft            : 1;  /**< [ 57: 57] DFT bypass.  If set to 1, DFT is bypassed.
                                                                 This field must be set to 0 for DFT-s-OFDM and it must be 1 for CP-OFDM. */
        uint64_t dft_standalone_flag   : 1;  /**< [ 56: 56] When set to 1, this flag sets the DFT engine as a standalone module. In this mode, both the
                                                                 functions before and after DFT/IDFT engine are bypassed.
                                                                 The DFT/IDFT result is DMAed directly to the output as in the one layer, no
                                                                 frequency hopping, allocation type 0 case.
                                                                 0x0 = used as non-standalone module in the RMAP chain.
                                                                 0x1 = used as standalone DFT/IDFT engine. */
        uint64_t reserved_53_55        : 3;
        uint64_t num_rb                : 9;  /**< [ 52: 44] The total number of RBs in a subframe. Valid range is [1,275]. */
        uint64_t reserved_43           : 1;
        uint64_t num_layers            : 3;  /**< [ 42: 40] Number of layers for PUSCH channel.
                                                                 0x1 = 1 Layer (DFT-s-OFDM and CP-OFDM).
                                                                 0x2 = 2 Layers (CP-OFDM only).
                                                                 0x4 = 3 Layers (CP-OFDM only).
                                                                 0x6 = 4 Layers (CP-OFDM only).
                                                                 Other values = Reserved. */
        uint64_t mod_order             : 4;  /**< [ 39: 36] Modulation order:
                                                                 0x1 = {pi}/2 BPSK (5G-NR DFT-s-OFDM only).
                                                                 0x2 = QPSK.
                                                                 0x4 = 16-QAM.
                                                                 0x6 = 64-QAM.
                                                                 0x8 = 256-QAM. */
        uint64_t num_scalar_qam        : 4;  /**< [ 35: 32] The number of bits the floating point modulation values are left shifted to produce
                                                                 the fixed point complex values. Valid range is [1,14]. */
        uint64_t dft_idft_flag         : 1;  /**< [ 31: 31] In DFT-only mode ([DFT_STANDALONE_FLAG] = 1), this flag sets the DFT or IDFT function
                                                                 0x0 = DFT.
                                                                 0x1 = IDFT.

                                                                 When [DFT_STANDALONE_FLAG] = 0, [DFT_IDFT_FLAG] must be zero. */
        uint64_t reserved_30           : 1;
        uint64_t ndft_indx             : 6;  /**< [ 29: 24] Index for the NDFT as defined in the list of supported NDFTs.
                                                                 Valid range is [0, 52]:
                                                                 0x0: NDFT = 12.
                                                                 0x1: NDFT = 24.
                                                                 ...
                                                                 0x21: NDFT = 1200.
                                                                 0x22: NDFT = 1296.
                                                                 0x23: NDFT = 1440.
                                                                 ...
                                                                 0x34: NDFT = 3240. */
        uint64_t reserved_21_23        : 3;
        uint64_t rs_bits_last          : 5;  /**< [ 20: 16] This parameter controls the output scaling at the last stage of the DFT/IDFT.
                                                                 The DFT/IDFT output is right shifted by [RS_BITS_LAST].
                                                                 Valid range is [15,19]. */
        uint64_t reserved_0_15         : 16;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_15         : 16;
        uint64_t rs_bits_last          : 5;  /**< [ 20: 16] This parameter controls the output scaling at the last stage of the DFT/IDFT.
                                                                 The DFT/IDFT output is right shifted by [RS_BITS_LAST].
                                                                 Valid range is [15,19]. */
        uint64_t reserved_21_23        : 3;
        uint64_t ndft_indx             : 6;  /**< [ 29: 24] Index for the NDFT as defined in the list of supported NDFTs.
                                                                 Valid range is [0, 52]:
                                                                 0x0: NDFT = 12.
                                                                 0x1: NDFT = 24.
                                                                 ...
                                                                 0x21: NDFT = 1200.
                                                                 0x22: NDFT = 1296.
                                                                 0x23: NDFT = 1440.
                                                                 ...
                                                                 0x34: NDFT = 3240. */
        uint64_t reserved_30           : 1;
        uint64_t dft_idft_flag         : 1;  /**< [ 31: 31] In DFT-only mode ([DFT_STANDALONE_FLAG] = 1), this flag sets the DFT or IDFT function
                                                                 0x0 = DFT.
                                                                 0x1 = IDFT.

                                                                 When [DFT_STANDALONE_FLAG] = 0, [DFT_IDFT_FLAG] must be zero. */
        uint64_t num_scalar_qam        : 4;  /**< [ 35: 32] The number of bits the floating point modulation values are left shifted to produce
                                                                 the fixed point complex values. Valid range is [1,14]. */
        uint64_t mod_order             : 4;  /**< [ 39: 36] Modulation order:
                                                                 0x1 = {pi}/2 BPSK (5G-NR DFT-s-OFDM only).
                                                                 0x2 = QPSK.
                                                                 0x4 = 16-QAM.
                                                                 0x6 = 64-QAM.
                                                                 0x8 = 256-QAM. */
        uint64_t num_layers            : 3;  /**< [ 42: 40] Number of layers for PUSCH channel.
                                                                 0x1 = 1 Layer (DFT-s-OFDM and CP-OFDM).
                                                                 0x2 = 2 Layers (CP-OFDM only).
                                                                 0x4 = 3 Layers (CP-OFDM only).
                                                                 0x6 = 4 Layers (CP-OFDM only).
                                                                 Other values = Reserved. */
        uint64_t reserved_43           : 1;
        uint64_t num_rb                : 9;  /**< [ 52: 44] The total number of RBs in a subframe. Valid range is [1,275]. */
        uint64_t reserved_53_55        : 3;
        uint64_t dft_standalone_flag   : 1;  /**< [ 56: 56] When set to 1, this flag sets the DFT engine as a standalone module. In this mode, both the
                                                                 functions before and after DFT/IDFT engine are bypassed.
                                                                 The DFT/IDFT result is DMAed directly to the output as in the one layer, no
                                                                 frequency hopping, allocation type 0 case.
                                                                 0x0 = used as non-standalone module in the RMAP chain.
                                                                 0x1 = used as standalone DFT/IDFT engine. */
        uint64_t bypass_dft            : 1;  /**< [ 57: 57] DFT bypass.  If set to 1, DFT is bypassed.
                                                                 This field must be set to 0 for DFT-s-OFDM and it must be 1 for CP-OFDM. */
        uint64_t bypass_modulator      : 1;  /**< [ 58: 58] If set to 1, modulator/RS insertion and DFT are bypassed. When
                                                                 [BYPASS_MODULATOR] = 1, [RS_INSERTION_ENABLE] must be  0 and [BYPASS_DFT] must
                                                                 be 1. */
        uint64_t bypass_scrambler      : 1;  /**< [ 59: 59] If set to 1, bypass scrambling. */
        uint64_t reserved_60_62        : 3;
        uint64_t phy_mode              : 1;  /**< [ 63: 63] This flag sets mode of operation. It must be set to 1 to indicate NR mode. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_115_127      : 13;
        uint64_t ack_enc_cat           : 3;  /**< [114:112] ACK encoding category:
                                                                 0x0: No ACK or if  [RS_CAT] = 2 (DMRS).
                                                                 0x1: number of ACK bits = 1.
                                                                 0x2: number of ACK bits = 2.
                                                                 0x3: number of ACK bits = [3,11].
                                                                 0x4: number of ACK bits \>= 12. */
        uint64_t reserved_107_111      : 5;
        uint64_t csi1_enc_cat          : 3;  /**< [106:104] The type of CSI1 bits :
                                                                 0x0: no CSI1 or if  [RS_CAT] = 2 (DMRS).
                                                                 0x1: number of CSI1 bits = 1.
                                                                 0x2: number of CSI1 bits = 2.
                                                                 0x3: number of CSI1 bits = [3,11].
                                                                 0x4: number of CSI1 bits \>= 12. */
        uint64_t reserved_99_103       : 5;
        uint64_t csi2_enc_cat          : 3;  /**< [ 98: 96] The type of CSI2 bits:
                                                                 0x0: no CSI2 or if  [RS_CAT] = 2 (DMRS).
                                                                 0x1: number of CSI2 bits = 1.
                                                                 0x2: number of CSI2 bits = 2.
                                                                 0x3: number of CSI2 bits = [3,11].
                                                                 0x4: number of CSI2 bits \>= 12. */
        uint64_t reserved_91_95        : 5;
        uint64_t ack_rsv_d_re          : 11; /**< [ 90: 80] The step size for the ACK reserved REs in the case of [ACK_ENC_CAT]  = 1 or 2. */
        uint64_t reserved_76_79        : 4;
        uint64_t ack_rsv_m_re          : 12; /**< [ 75: 64] The number of REs reserved for ACK bits in the case of [ACK_ENC_CAT] = 1 or 2. */
#else /* Word 1 - Little Endian */
        uint64_t ack_rsv_m_re          : 12; /**< [ 75: 64] The number of REs reserved for ACK bits in the case of [ACK_ENC_CAT] = 1 or 2. */
        uint64_t reserved_76_79        : 4;
        uint64_t ack_rsv_d_re          : 11; /**< [ 90: 80] The step size for the ACK reserved REs in the case of [ACK_ENC_CAT]  = 1 or 2. */
        uint64_t reserved_91_95        : 5;
        uint64_t csi2_enc_cat          : 3;  /**< [ 98: 96] The type of CSI2 bits:
                                                                 0x0: no CSI2 or if  [RS_CAT] = 2 (DMRS).
                                                                 0x1: number of CSI2 bits = 1.
                                                                 0x2: number of CSI2 bits = 2.
                                                                 0x3: number of CSI2 bits = [3,11].
                                                                 0x4: number of CSI2 bits \>= 12. */
        uint64_t reserved_99_103       : 5;
        uint64_t csi1_enc_cat          : 3;  /**< [106:104] The type of CSI1 bits :
                                                                 0x0: no CSI1 or if  [RS_CAT] = 2 (DMRS).
                                                                 0x1: number of CSI1 bits = 1.
                                                                 0x2: number of CSI1 bits = 2.
                                                                 0x3: number of CSI1 bits = [3,11].
                                                                 0x4: number of CSI1 bits \>= 12. */
        uint64_t reserved_107_111      : 5;
        uint64_t ack_enc_cat           : 3;  /**< [114:112] ACK encoding category:
                                                                 0x0: No ACK or if  [RS_CAT] = 2 (DMRS).
                                                                 0x1: number of ACK bits = 1.
                                                                 0x2: number of ACK bits = 2.
                                                                 0x3: number of ACK bits = [3,11].
                                                                 0x4: number of ACK bits \>= 12. */
        uint64_t reserved_115_127      : 13;
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t reserved_191          : 1;
        uint64_t ack_d_re              : 11; /**< [190:180] The symbol-wise step size in RE for the ACK bits. */
        uint64_t ack_m_re              : 12; /**< [179:168] The symbol-wise number of REs for the ACK bits. When [ACK_ENC_CAT] = 0, this field must be 0. */
        uint64_t reserved_167          : 1;
        uint64_t ack_bit_offset        : 7;  /**< [166:160] Start bit offset in the first 128-bit word after input bit processing block of
                                                                 Section 2.5.2.1.

                                                                 _ When [ACK_ENC_CAT] = 0x1, valid range is {0}.

                                                                 _ When [ACK_ENC_CAT] = 0x2, valid range is {0, [MOD_ORDER], 2*[MOD_ORDER]}.

                                                                 _ When [ACK_ENC_CAT] = 0x3, valid range is [0,31].

                                                                 _ When [ACK_ENC_CAT] = 0x4, valid range is [0,127].

                                                                 _ When [ACK_ENC_CAT] = 0 or [ACK_M_RE] = 0, this field is ignored. */
        uint64_t reserved_159          : 1;
        uint64_t csi1_d_re             : 11; /**< [158:148] The symbol-wise step size in RE for the CSI1 bits. */
        uint64_t csi1_m_re             : 12; /**< [147:136] The symbol-wise number of REs for the CSI1 bits. When [CSI1_ENC_CAT] = 0, this field must be 0. */
        uint64_t reserved_135          : 1;
        uint64_t csi1_bit_offset       : 7;  /**< [134:128] Start bit offset in the first 128-bit word after input bit processing block of Section 2.5.2.1.

                                                                 _ When [CSI1_ENC_CAT] = 0x1, valid range is {0}.

                                                                 _ When [CSI1_ENC_CAT] = 0x2, valid range is {0, [MOD_ORDER], 2*[MOD_ORDER]}.

                                                                 _ When [CSI1_ENC_CAT] = 0x3, valid range is [0,31].

                                                                 _ When [CSI1_ENC_CAT] = 0x4, valid range is [0,127].

                                                                 _ When [CSI1_ENC_CAT] = 0 or [CSI1_M_RE] = 0, this field is ignored. */
#else /* Word 2 - Little Endian */
        uint64_t csi1_bit_offset       : 7;  /**< [134:128] Start bit offset in the first 128-bit word after input bit processing block of Section 2.5.2.1.

                                                                 _ When [CSI1_ENC_CAT] = 0x1, valid range is {0}.

                                                                 _ When [CSI1_ENC_CAT] = 0x2, valid range is {0, [MOD_ORDER], 2*[MOD_ORDER]}.

                                                                 _ When [CSI1_ENC_CAT] = 0x3, valid range is [0,31].

                                                                 _ When [CSI1_ENC_CAT] = 0x4, valid range is [0,127].

                                                                 _ When [CSI1_ENC_CAT] = 0 or [CSI1_M_RE] = 0, this field is ignored. */
        uint64_t reserved_135          : 1;
        uint64_t csi1_m_re             : 12; /**< [147:136] The symbol-wise number of REs for the CSI1 bits. When [CSI1_ENC_CAT] = 0, this field must be 0. */
        uint64_t csi1_d_re             : 11; /**< [158:148] The symbol-wise step size in RE for the CSI1 bits. */
        uint64_t reserved_159          : 1;
        uint64_t ack_bit_offset        : 7;  /**< [166:160] Start bit offset in the first 128-bit word after input bit processing block of
                                                                 Section 2.5.2.1.

                                                                 _ When [ACK_ENC_CAT] = 0x1, valid range is {0}.

                                                                 _ When [ACK_ENC_CAT] = 0x2, valid range is {0, [MOD_ORDER], 2*[MOD_ORDER]}.

                                                                 _ When [ACK_ENC_CAT] = 0x3, valid range is [0,31].

                                                                 _ When [ACK_ENC_CAT] = 0x4, valid range is [0,127].

                                                                 _ When [ACK_ENC_CAT] = 0 or [ACK_M_RE] = 0, this field is ignored. */
        uint64_t reserved_167          : 1;
        uint64_t ack_m_re              : 12; /**< [179:168] The symbol-wise number of REs for the ACK bits. When [ACK_ENC_CAT] = 0, this field must be 0. */
        uint64_t ack_d_re              : 11; /**< [190:180] The symbol-wise step size in RE for the ACK bits. */
        uint64_t reserved_191          : 1;
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t reserved_255          : 1;
        uint64_t csi2_d_re             : 11; /**< [254:244] The symbol-wise step size in RE for the CSI2 bits. */
        uint64_t csi2_m_re             : 12; /**< [243:232] The symbol-wise number of REs for the CSI2 bits. When [CSI2_ENC_CAT] = 0, this field must be 0. */
        uint64_t reserved_231          : 1;
        uint64_t csi2_bit_offset       : 7;  /**< [230:224] Start bit offset in the first 128-bit word after input bit processing block.

                                                                 _ When [CSI2_ENC_CAT] = 0x1, valid range is {0}.

                                                                 _ When [CSI2_ENC_CAT] = 0x2, valid range is {0, [MOD_ORDER], 2*[MOD_ORDER]}.

                                                                 _ When [CSI2_ENC_CAT] = 0x3, valid range is [0,31].

                                                                 _ When [CSI2_ENC_CAT] = 0x4, valid range is [0,127].

                                                                 _ When [CSI2_ENC_CAT] = 0 or [CSI2_M_RE] = 0, this field is ignored. */
        uint64_t reserved_223          : 1;
        uint64_t ack_crc               : 1;  /**< [222:222] CRC value for ACK RE when [ACK_ENC_CAT] = [0,3] or  when [ACK_ENC_CAT] = 4 and
                                                                 [ACK_REENC_MODE] = 0. */
        uint64_t csi1_crc              : 1;  /**< [221:221] CRC value for CSI1 RE when [CSI1_ENC_CAT] = [0,3] or when [CSI1_ENC_CAT] = 4 and
                                                                 [CSI1_REENC_MODE] = 0. */
        uint64_t csi2_crc              : 1;  /**< [220:220] CRC value for CSI2 RE when [CSI2_ENC_CAT] = [0,3] or  when[CSI1_ENC_CAT] = 4 and
                                                                 [CSI1_REENC_MODE] = 0. */
        uint64_t ack_reenc_mode        : 1;  /**< [219:219] Bit packing mode for the reencoded ACK bits:
                                                                 0x0 = plain bit stream of reencoded data bits packed one-by-one.
                                                                 0x1 = CRC tagged in each [MOD_ORDER] with tagged CRC of 0 (CRC OK) or 1 (CRC NOK).

                                                                 This field is valid only when [ACK_ENC_CAT] = 4 and is ignored otherwise. */
        uint64_t csi1_reenc_mode       : 1;  /**< [218:218] Bit packing mode for the reencoded CSI1 bits:
                                                                 0x0 = plain bit stream of reencoded data bits packed one-by-one.
                                                                 0x1 = CRC tagged in each [MOD_ORDER] with tagged CRC of 0 (CRC OK) or 1 (CRC NOK).

                                                                 This field is valid only when [CSI1_ENC_CAT] = 4 and is ignored otherwise. */
        uint64_t csi2_reenc_mode       : 1;  /**< [217:217] Bit packing mode for the reencoded CSI2 bits:
                                                                 0x0 = plain bit stream of reencoded data bits packed one-by-one.
                                                                 0x1 = CRC tagged in each [MOD_ORDER] with tagged CRC of 0 (CRC OK) or 1 (CRC NOK).

                                                                 This field is valid only when [CSI2_ENC_CAT] = 4 and is ignored otherwise. */
        uint64_t data_reenc_mode       : 1;  /**< [216:216] Bit packing mode for the reencoded data bits:
                                                                 0x0 = plain bit stream of reencoded data bits packed one-by-one.
                                                                 0x1 = CRC tagged in each [MOD_ORDER] with tagged CRC of 0 (CRC OK) or 1 (CRC NOK). */
        uint64_t reserved_212_215      : 4;
        uint64_t data_m_re             : 12; /**< [211:200] The symbol-wise number of REs for the data bits. */
        uint64_t reserved_199          : 1;
        uint64_t data_bit_offset       : 7;  /**< [198:192] Start bit offset in the first 128-bit word of data bits. Valid range is [0,127].
                                                                 This field is ignored when [DATA_M_RE] = 0. */
#else /* Word 3 - Little Endian */
        uint64_t data_bit_offset       : 7;  /**< [198:192] Start bit offset in the first 128-bit word of data bits. Valid range is [0,127].
                                                                 This field is ignored when [DATA_M_RE] = 0. */
        uint64_t reserved_199          : 1;
        uint64_t data_m_re             : 12; /**< [211:200] The symbol-wise number of REs for the data bits. */
        uint64_t reserved_212_215      : 4;
        uint64_t data_reenc_mode       : 1;  /**< [216:216] Bit packing mode for the reencoded data bits:
                                                                 0x0 = plain bit stream of reencoded data bits packed one-by-one.
                                                                 0x1 = CRC tagged in each [MOD_ORDER] with tagged CRC of 0 (CRC OK) or 1 (CRC NOK). */
        uint64_t csi2_reenc_mode       : 1;  /**< [217:217] Bit packing mode for the reencoded CSI2 bits:
                                                                 0x0 = plain bit stream of reencoded data bits packed one-by-one.
                                                                 0x1 = CRC tagged in each [MOD_ORDER] with tagged CRC of 0 (CRC OK) or 1 (CRC NOK).

                                                                 This field is valid only when [CSI2_ENC_CAT] = 4 and is ignored otherwise. */
        uint64_t csi1_reenc_mode       : 1;  /**< [218:218] Bit packing mode for the reencoded CSI1 bits:
                                                                 0x0 = plain bit stream of reencoded data bits packed one-by-one.
                                                                 0x1 = CRC tagged in each [MOD_ORDER] with tagged CRC of 0 (CRC OK) or 1 (CRC NOK).

                                                                 This field is valid only when [CSI1_ENC_CAT] = 4 and is ignored otherwise. */
        uint64_t ack_reenc_mode        : 1;  /**< [219:219] Bit packing mode for the reencoded ACK bits:
                                                                 0x0 = plain bit stream of reencoded data bits packed one-by-one.
                                                                 0x1 = CRC tagged in each [MOD_ORDER] with tagged CRC of 0 (CRC OK) or 1 (CRC NOK).

                                                                 This field is valid only when [ACK_ENC_CAT] = 4 and is ignored otherwise. */
        uint64_t csi2_crc              : 1;  /**< [220:220] CRC value for CSI2 RE when [CSI2_ENC_CAT] = [0,3] or  when[CSI1_ENC_CAT] = 4 and
                                                                 [CSI1_REENC_MODE] = 0. */
        uint64_t csi1_crc              : 1;  /**< [221:221] CRC value for CSI1 RE when [CSI1_ENC_CAT] = [0,3] or when [CSI1_ENC_CAT] = 4 and
                                                                 [CSI1_REENC_MODE] = 0. */
        uint64_t ack_crc               : 1;  /**< [222:222] CRC value for ACK RE when [ACK_ENC_CAT] = [0,3] or  when [ACK_ENC_CAT] = 4 and
                                                                 [ACK_REENC_MODE] = 0. */
        uint64_t reserved_223          : 1;
        uint64_t csi2_bit_offset       : 7;  /**< [230:224] Start bit offset in the first 128-bit word after input bit processing block.

                                                                 _ When [CSI2_ENC_CAT] = 0x1, valid range is {0}.

                                                                 _ When [CSI2_ENC_CAT] = 0x2, valid range is {0, [MOD_ORDER], 2*[MOD_ORDER]}.

                                                                 _ When [CSI2_ENC_CAT] = 0x3, valid range is [0,31].

                                                                 _ When [CSI2_ENC_CAT] = 0x4, valid range is [0,127].

                                                                 _ When [CSI2_ENC_CAT] = 0 or [CSI2_M_RE] = 0, this field is ignored. */
        uint64_t reserved_231          : 1;
        uint64_t csi2_m_re             : 12; /**< [243:232] The symbol-wise number of REs for the CSI2 bits. When [CSI2_ENC_CAT] = 0, this field must be 0. */
        uint64_t csi2_d_re             : 11; /**< [254:244] The symbol-wise step size in RE for the CSI2 bits. */
        uint64_t reserved_255          : 1;
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t reserved_312_319      : 8;
        uint64_t scrambling_offset     : 24; /**< [311:288] Starting bit location of scrambling sequences in number of bits beyond the
                                                                 initial 1600 bits from the sequence generator.
                                                                 Scrambling sequence is applied starting from (1600+[SCRAMBLING_OFFSET])-th bit.
                                                                 e.g. the first symbol job must set this value as 0 while the second symbol job
                                                                 must set this value as
                                                                 [MOD_ORDER]*[NUM_LAYERS]*(number of non-RS symbols in symbol 0). */
        uint64_t reserved_287          : 1;
        uint64_t scrambling_cinit      : 31; /**< [286:256] Initial value of the second m-sequence of the scrambler. See section 7.2 of [R1].
                                                                 Valid range is [0, 2^31-1]. */
#else /* Word 4 - Little Endian */
        uint64_t scrambling_cinit      : 31; /**< [286:256] Initial value of the second m-sequence of the scrambler. See section 7.2 of [R1].
                                                                 Valid range is [0, 2^31-1]. */
        uint64_t reserved_287          : 1;
        uint64_t scrambling_offset     : 24; /**< [311:288] Starting bit location of scrambling sequences in number of bits beyond the
                                                                 initial 1600 bits from the sequence generator.
                                                                 Scrambling sequence is applied starting from (1600+[SCRAMBLING_OFFSET])-th bit.
                                                                 e.g. the first symbol job must set this value as 0 while the second symbol job
                                                                 must set this value as
                                                                 [MOD_ORDER]*[NUM_LAYERS]*(number of non-RS symbols in symbol 0). */
        uint64_t reserved_312_319      : 8;
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t rs_insertion_enable   : 1;  /**< [383:383] This flag controls RS insertion:
                                                                 0x0 = Disable (all RS insertion related parameters are ignored).
                                                                 0x1 = Enable RS Insertion. */
        uint64_t reserved_382          : 1;
        uint64_t rs_cat                : 2;  /**< [381:380] Category type for the reference symbols (RS):
                                                                 0x0 = PTRS for CP-OFDM.
                                                                 0x1 = PTRS for DFT-s-OFDM.
                                                                 0x2 = DMRS for CP-OFDM.
                                                                 0x3 = Reserved. */
        uint64_t reserved_379          : 1;
        uint64_t rs_mapping_type       : 3;  /**< [378:376] Mapping type for each RS category.

                                                                 When [RS_CAT] = 0 (PTRS for CP-OFDM):
                                                                 0x0 for distributed PTRS in PRB.
                                                                 0x1 for distributed PTRS in VRB.
                                                                 0x2 for localized PTRS.

                                                                 When [RS_CAT] = 1 (PTRS for DFT-s-OFDM):
                                                                 _ Valid range is [0,4] when [MODE_ORDER] = 1.
                                                                 _ Valid range is [0,5] when [MODE_ORDER] \>=2.

                                                                 When [RS_CAT] = 2 (DMRS for CP-OFDM), valid range is [0,7]. */
        uint64_t ptrs_dfts_ofdm_delta  : 1;  /**< [375:375] Delta {0,1} of the PTRS allocation for the DFT-s-OFDM case when [RS_CAT] = 1 and
                                                                 [RS_MAPPING_TYPE] = 5. */
        uint64_t reserved_373_374      : 2;
        uint64_t ptrs_dist_start_rb_idx : 9; /**< [372:364] The start RB index of PUSCH allocation. Valid range is [0,274]. */
        uint64_t reserved_362_363      : 2;
        uint64_t ptrs_dist_rb_offset_0 : 2;  /**< [361:360] RB offset of the PTRS allocation for the CP-OFDM case. Valid range
                                                                 is [0, [PTRS_DIST_RB_STEP]-1]. */
        uint64_t reserved_358_359      : 2;
        uint64_t ptrs_dist_rb_offset_1 : 2;  /**< [357:356] RB offset of the PTRS allocation for the CP-OFDM case. This field is valid only
                                                                 when [RS_CAT] = 0 and [RS_MAPPING_TYPE] = 1. Valid range is [0, [PTRS_DIST_RB_STEP]-1]. */
        uint64_t reserved_355          : 1;
        uint64_t ptrs_dist_rb_step     : 3;  /**< [354:352] RB step of PTRS allocation for CP-OFDM case. Valid range is {2,4}. */
        uint64_t reserved_351          : 1;
        uint64_t ptrs_dist_vrb_bundle_size : 3;/**< [350:348] L, VRB bundle size. Valid range is {2,4}. */
        uint64_t reserved_347          : 1;
        uint64_t ptrs_dist_num_ports   : 3;  /**< [346:344] The total number of antenna ports in the CP-OFDM case. It is only valid for CP-OFDM.
                                                                 Valid range is [1,6]. */
        uint64_t ptrs_dist_re_offset_0 : 4;  /**< [343:340] RE offset of the PTRS for CP-OFDM case for antenna port 0. This field is set
                                                                 according to Table 6.4.1.2.2.1-1 of [R6].

                                                                 _ k_ref^RE[i] in {0,...,11} valid for i = 0,1,...,[PTRS_DIST_NUM_PORTS]-1.

                                                                 _ k_ref^RE[i] \< k_ref^RE[i+1] for i=0,1,...,[PTRS_DIST_NUM_PORTS]-2. */
        uint64_t ptrs_dist_re_offset_1 : 4;  /**< [339:336] RE offset of the PTRS for CP-OFDM case for antenna port 1. See
                                                                 [PTRS_DIST_RE_OFFSET_0]. */
        uint64_t ptrs_dist_re_offset_2 : 4;  /**< [335:332] RE offset of the PTRS for CP-OFDM case for antenna port 2. See
                                                                 [PTRS_DIST_RE_OFFSET_0]. */
        uint64_t ptrs_dist_re_offset_3 : 4;  /**< [331:328] RE offset of the PTRS for CP-OFDM case for antenna port 3. See
                                                                 [PTRS_DIST_RE_OFFSET_0]. */
        uint64_t ptrs_dist_re_offset_4 : 4;  /**< [327:324] RE offset of the PTRS for CP-OFDM case for antenna port 4. See
                                                                 [PTRS_DIST_RE_OFFSET_0]. */
        uint64_t ptrs_dist_re_offset_5 : 4;  /**< [323:320] RE offset of the PTRS for CP-OFDM case for antenna port 5. See
                                                                 [PTRS_DIST_RE_OFFSET_0]. */
#else /* Word 5 - Little Endian */
        uint64_t ptrs_dist_re_offset_5 : 4;  /**< [323:320] RE offset of the PTRS for CP-OFDM case for antenna port 5. See
                                                                 [PTRS_DIST_RE_OFFSET_0]. */
        uint64_t ptrs_dist_re_offset_4 : 4;  /**< [327:324] RE offset of the PTRS for CP-OFDM case for antenna port 4. See
                                                                 [PTRS_DIST_RE_OFFSET_0]. */
        uint64_t ptrs_dist_re_offset_3 : 4;  /**< [331:328] RE offset of the PTRS for CP-OFDM case for antenna port 3. See
                                                                 [PTRS_DIST_RE_OFFSET_0]. */
        uint64_t ptrs_dist_re_offset_2 : 4;  /**< [335:332] RE offset of the PTRS for CP-OFDM case for antenna port 2. See
                                                                 [PTRS_DIST_RE_OFFSET_0]. */
        uint64_t ptrs_dist_re_offset_1 : 4;  /**< [339:336] RE offset of the PTRS for CP-OFDM case for antenna port 1. See
                                                                 [PTRS_DIST_RE_OFFSET_0]. */
        uint64_t ptrs_dist_re_offset_0 : 4;  /**< [343:340] RE offset of the PTRS for CP-OFDM case for antenna port 0. This field is set
                                                                 according to Table 6.4.1.2.2.1-1 of [R6].

                                                                 _ k_ref^RE[i] in {0,...,11} valid for i = 0,1,...,[PTRS_DIST_NUM_PORTS]-1.

                                                                 _ k_ref^RE[i] \< k_ref^RE[i+1] for i=0,1,...,[PTRS_DIST_NUM_PORTS]-2. */
        uint64_t ptrs_dist_num_ports   : 3;  /**< [346:344] The total number of antenna ports in the CP-OFDM case. It is only valid for CP-OFDM.
                                                                 Valid range is [1,6]. */
        uint64_t reserved_347          : 1;
        uint64_t ptrs_dist_vrb_bundle_size : 3;/**< [350:348] L, VRB bundle size. Valid range is {2,4}. */
        uint64_t reserved_351          : 1;
        uint64_t ptrs_dist_rb_step     : 3;  /**< [354:352] RB step of PTRS allocation for CP-OFDM case. Valid range is {2,4}. */
        uint64_t reserved_355          : 1;
        uint64_t ptrs_dist_rb_offset_1 : 2;  /**< [357:356] RB offset of the PTRS allocation for the CP-OFDM case. This field is valid only
                                                                 when [RS_CAT] = 0 and [RS_MAPPING_TYPE] = 1. Valid range is [0, [PTRS_DIST_RB_STEP]-1]. */
        uint64_t reserved_358_359      : 2;
        uint64_t ptrs_dist_rb_offset_0 : 2;  /**< [361:360] RB offset of the PTRS allocation for the CP-OFDM case. Valid range
                                                                 is [0, [PTRS_DIST_RB_STEP]-1]. */
        uint64_t reserved_362_363      : 2;
        uint64_t ptrs_dist_start_rb_idx : 9; /**< [372:364] The start RB index of PUSCH allocation. Valid range is [0,274]. */
        uint64_t reserved_373_374      : 2;
        uint64_t ptrs_dfts_ofdm_delta  : 1;  /**< [375:375] Delta {0,1} of the PTRS allocation for the DFT-s-OFDM case when [RS_CAT] = 1 and
                                                                 [RS_MAPPING_TYPE] = 5. */
        uint64_t rs_mapping_type       : 3;  /**< [378:376] Mapping type for each RS category.

                                                                 When [RS_CAT] = 0 (PTRS for CP-OFDM):
                                                                 0x0 for distributed PTRS in PRB.
                                                                 0x1 for distributed PTRS in VRB.
                                                                 0x2 for localized PTRS.

                                                                 When [RS_CAT] = 1 (PTRS for DFT-s-OFDM):
                                                                 _ Valid range is [0,4] when [MODE_ORDER] = 1.
                                                                 _ Valid range is [0,5] when [MODE_ORDER] \>=2.

                                                                 When [RS_CAT] = 2 (DMRS for CP-OFDM), valid range is [0,7]. */
        uint64_t reserved_379          : 1;
        uint64_t rs_cat                : 2;  /**< [381:380] Category type for the reference symbols (RS):
                                                                 0x0 = PTRS for CP-OFDM.
                                                                 0x1 = PTRS for DFT-s-OFDM.
                                                                 0x2 = DMRS for CP-OFDM.
                                                                 0x3 = Reserved. */
        uint64_t reserved_382          : 1;
        uint64_t rs_insertion_enable   : 1;  /**< [383:383] This flag controls RS insertion:
                                                                 0x0 = Disable (all RS insertion related parameters are ignored).
                                                                 0x1 = Enable RS Insertion. */
#endif /* Word 5 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 6 - Big Endian */
        uint64_t reserved_444_447      : 4;
        uint64_t ptrs_loc_re_offset_0  : 12; /**< [443:432] Offset of REs for each group of PTRS insertion in the case of
                                                                 localized allocation. This field is only valid for R16 of CP-OFDM.

                                                                 Valid range is [0,3299] and the following condition must be satisfied:

                                                                 _ If ([PTRS_LOC_RE_LENGTH_1] \> 0) [PTRS_LOC_RE_OFFSET_1] \> [PTRS_LOC_RE_OFFSET_0]. */
        uint64_t reserved_428_431      : 4;
        uint64_t ptrs_loc_re_offset_1  : 12; /**< [427:416] Offset of REs for each group of PTRS insertion in the case of localized
                                                                 allocation. This field is only valid for R16 of CP-OFDM.
                                                                 Valid range is [0,3299].

                                                                 If ([PTRS_LOC_RE_LENGTH_1] \> 0) [PTRS_LOC_RE_OFFSET_1] \> [PTRS_LOC_RE_OFFSET_0]. */
        uint64_t reserved_409_415      : 7;
        uint64_t ptrs_loc_re_length_0  : 9;  /**< [408:400] RE Length in each burst of PTRS for localized PTRS allocation in CP-OFDM.
                                                                 Valid range is [1,511] with the following conditions:

                                                                 "   [PTRS_LOC_RE_OFFSET_0] + [PTRS_LOC_RE_LENGTH_0] \<= 12 * [NUM_RB].
                                                                    If ([PTRS_LOC_RE_OFFSET_1] \> 0)
                                                                       [PTRS_LOC_RE_OFFSET_0] + [PTRS_LOC_RE_LENGTH_0] \<= [PTRS_LOC_RE_OFFSET_1]." */
        uint64_t reserved_393_399      : 7;
        uint64_t ptrs_loc_re_length_1  : 9;  /**< [392:384] RE Length in each burst of PTRS for localized PTRS allocation in CP-OFDM.
                                                                 Valid range is [0,511] with the following condition

                                                                 _ [PTRS_LOC_RE_OFFSET_1] + [PTRS_LOC_RE_LENGTH_1] \<= 12 * [NUM_RB]. */
#else /* Word 6 - Little Endian */
        uint64_t ptrs_loc_re_length_1  : 9;  /**< [392:384] RE Length in each burst of PTRS for localized PTRS allocation in CP-OFDM.
                                                                 Valid range is [0,511] with the following condition

                                                                 _ [PTRS_LOC_RE_OFFSET_1] + [PTRS_LOC_RE_LENGTH_1] \<= 12 * [NUM_RB]. */
        uint64_t reserved_393_399      : 7;
        uint64_t ptrs_loc_re_length_0  : 9;  /**< [408:400] RE Length in each burst of PTRS for localized PTRS allocation in CP-OFDM.
                                                                 Valid range is [1,511] with the following conditions:

                                                                 "   [PTRS_LOC_RE_OFFSET_0] + [PTRS_LOC_RE_LENGTH_0] \<= 12 * [NUM_RB].
                                                                    If ([PTRS_LOC_RE_OFFSET_1] \> 0)
                                                                       [PTRS_LOC_RE_OFFSET_0] + [PTRS_LOC_RE_LENGTH_0] \<= [PTRS_LOC_RE_OFFSET_1]." */
        uint64_t reserved_409_415      : 7;
        uint64_t ptrs_loc_re_offset_1  : 12; /**< [427:416] Offset of REs for each group of PTRS insertion in the case of localized
                                                                 allocation. This field is only valid for R16 of CP-OFDM.
                                                                 Valid range is [0,3299].

                                                                 If ([PTRS_LOC_RE_LENGTH_1] \> 0) [PTRS_LOC_RE_OFFSET_1] \> [PTRS_LOC_RE_OFFSET_0]. */
        uint64_t reserved_428_431      : 4;
        uint64_t ptrs_loc_re_offset_0  : 12; /**< [443:432] Offset of REs for each group of PTRS insertion in the case of
                                                                 localized allocation. This field is only valid for R16 of CP-OFDM.

                                                                 Valid range is [0,3299] and the following condition must be satisfied:

                                                                 _ If ([PTRS_LOC_RE_LENGTH_1] \> 0) [PTRS_LOC_RE_OFFSET_1] \> [PTRS_LOC_RE_OFFSET_0]. */
        uint64_t reserved_444_447      : 4;
#endif /* Word 6 - End */
    } s;
    /* struct bdk_rmap_nr_mode_s_s cn; */
};

/**
 * Structure rmap_tc_lte_config_err_s
 *
 * RMAP TC LTE Mode Configuration Error Structure
 * When RMAP(0..1)_TC_ERROR[CORE_ERR] is set, this field indicates which
 * configuration parameter was set incorrectly. Each bit maps to a different error:
 */
union bdk_rmap_tc_lte_config_err_s
{
    uint64_t u;
    struct bdk_rmap_tc_lte_config_err_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t invalid_symb_byte_aligned : 1;/**< [ 19: 19] invalid range for symb_byte_aligned */
        uint64_t invalid_scrambling_init : 1;/**< [ 18: 18] invalid range for scrambling_init */
        uint64_t invalid_bypass_scrambling : 1;/**< [ 17: 17] invalid range for bypass_scrambling */
        uint64_t invalid_tti2_ack_pos  : 1;  /**< [ 16: 16] invalid range for tti2_ack_pos */
        uint64_t invalid_ttimode       : 1;  /**< [ 15: 15] invalid range for ttimode */
        uint64_t invalid_cp_mode       : 1;  /**< [ 14: 14] invalid range for cp_mode */
        uint64_t invalid_ri_enc_cat    : 1;  /**< [ 13: 13] invalid range for ri_enc_cat */
        uint64_t invalid_ack_enc_cat   : 1;  /**< [ 12: 12] invalid range for ack_enc_cat */
        uint64_t reserved_11           : 1;
        uint64_t invalid_r_prime_mux   : 1;  /**< [ 10: 10] invalid range for r_prime_mux */
        uint64_t invalid_q_prime_ack   : 1;  /**< [  9:  9] invalid range for q_prime_ack */
        uint64_t invalid_q_prime_ri    : 1;  /**< [  8:  8] invalid range for q_prime_ri */
        uint64_t invalid_q_prime_cqi   : 1;  /**< [  7:  7] invalid range for q_prime_cqi */
        uint64_t invalid_num_layers    : 1;  /**< [  6:  6] invalid range for num_layers */
        uint64_t invalid_mod_order     : 1;  /**< [  5:  5] invalid range for mod_order */
        uint64_t invalid_g_prime       : 1;  /**< [  4:  4] invalid range for g_prime */
        uint64_t r_prime_mux           : 1;  /**< [  3:  3] r_prime_mux * n_symb_pusch \<= (g_prime + ri_prime) */
        uint64_t invalid_n_symb_pusch  : 1;  /**< [  2:  2] invalid range for n_symb_pusch */
        uint64_t q_prim_ack            : 1;  /**< [  1:  1] q_prime_ack \<= r_prime_mux * 4 */
        uint64_t q_prim_ri             : 1;  /**< [  0:  0] q_prim_ri \<= r_prime_mux * 4 */
#else /* Word 0 - Little Endian */
        uint64_t q_prim_ri             : 1;  /**< [  0:  0] q_prim_ri \<= r_prime_mux * 4 */
        uint64_t q_prim_ack            : 1;  /**< [  1:  1] q_prime_ack \<= r_prime_mux * 4 */
        uint64_t invalid_n_symb_pusch  : 1;  /**< [  2:  2] invalid range for n_symb_pusch */
        uint64_t r_prime_mux           : 1;  /**< [  3:  3] r_prime_mux * n_symb_pusch \<= (g_prime + ri_prime) */
        uint64_t invalid_g_prime       : 1;  /**< [  4:  4] invalid range for g_prime */
        uint64_t invalid_mod_order     : 1;  /**< [  5:  5] invalid range for mod_order */
        uint64_t invalid_num_layers    : 1;  /**< [  6:  6] invalid range for num_layers */
        uint64_t invalid_q_prime_cqi   : 1;  /**< [  7:  7] invalid range for q_prime_cqi */
        uint64_t invalid_q_prime_ri    : 1;  /**< [  8:  8] invalid range for q_prime_ri */
        uint64_t invalid_q_prime_ack   : 1;  /**< [  9:  9] invalid range for q_prime_ack */
        uint64_t invalid_r_prime_mux   : 1;  /**< [ 10: 10] invalid range for r_prime_mux */
        uint64_t reserved_11           : 1;
        uint64_t invalid_ack_enc_cat   : 1;  /**< [ 12: 12] invalid range for ack_enc_cat */
        uint64_t invalid_ri_enc_cat    : 1;  /**< [ 13: 13] invalid range for ri_enc_cat */
        uint64_t invalid_cp_mode       : 1;  /**< [ 14: 14] invalid range for cp_mode */
        uint64_t invalid_ttimode       : 1;  /**< [ 15: 15] invalid range for ttimode */
        uint64_t invalid_tti2_ack_pos  : 1;  /**< [ 16: 16] invalid range for tti2_ack_pos */
        uint64_t invalid_bypass_scrambling : 1;/**< [ 17: 17] invalid range for bypass_scrambling */
        uint64_t invalid_scrambling_init : 1;/**< [ 18: 18] invalid range for scrambling_init */
        uint64_t invalid_symb_byte_aligned : 1;/**< [ 19: 19] invalid range for symb_byte_aligned */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmap_tc_lte_config_err_s_s cn; */
};

/**
 * Structure rmap_tc_nr_config_err_s
 *
 * RMAP TC NR Mode Configuration Error Structure
 * When RMAP(0..1)_TC_ERROR[CORE_ERR] is set, this field indicates which
 * configuration parameter was set incorrectly. Each bit maps to a different error:
 */
union bdk_rmap_tc_nr_config_err_s
{
    uint64_t u;
    struct bdk_rmap_tc_nr_config_err_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_41_63        : 23;
        uint64_t invalid_csi2_crc      : 1;  /**< [ 40: 40] invalid range for csi2_crc */
        uint64_t invalid_csi1_crc      : 1;  /**< [ 39: 39] invalid range for csi1_crc */
        uint64_t invalid_ack_crc       : 1;  /**< [ 38: 38] invalid range for ack_crc */
        uint64_t invalid_data_reenc_mode : 1;/**< [ 37: 37] invalid range for data_reenc_mode */
        uint64_t invalid_csi2_reenc_mode : 1;/**< [ 36: 36] invalid range for csi2_reenc_mode */
        uint64_t invalid_csi1_reenc_mode : 1;/**< [ 35: 35] invalid range for csi1_reenc_mode */
        uint64_t invalid_ack_reenc_mode : 1; /**< [ 34: 34] invalid range for ack_reenc_mode */
        uint64_t invalid_mod_order     : 1;  /**< [ 33: 33] invalid range for mod_order */
        uint64_t invalid_num_layers    : 1;  /**< [ 32: 32] invalid range for num_layers */
        uint64_t invalid_scrambling_offset : 1;/**< [ 31: 31] invalid range for scrambling_offset */
        uint64_t invalid_scrambling_init : 1;/**< [ 30: 30] invalid range for scrambling_init */
        uint64_t invalid_bypass_scrambler : 1;/**< [ 29: 29] invalid range for bypass_scrambler */
        uint64_t invalid_data_bit_offset : 1;/**< [ 28: 28] invalid range for data_bit_offset */
        uint64_t invalid_data_m_re     : 1;  /**< [ 27: 27] invalid range for data_m_re */
        uint64_t invalid_csi2_bit_offset : 1;/**< [ 26: 26] invalid range for csi2_bit_offset */
        uint64_t invalid_csi2_m_re     : 1;  /**< [ 25: 25] invalid range for csi2_m_re */
        uint64_t invalid_csi2_d_re     : 1;  /**< [ 24: 24] invalid range for csi2_d_re */
        uint64_t invalid_csi1_bit_offset : 1;/**< [ 23: 23] invalid range for csi1_bit_offset */
        uint64_t invalid_csi1_m_re     : 1;  /**< [ 22: 22] invalid range for csi1_m_re */
        uint64_t invalid_csi1_d_re     : 1;  /**< [ 21: 21] invalid range for csi1_d_re */
        uint64_t invalid_ack_bit_offset : 1; /**< [ 20: 20] invalid range for ack_bit_offset */
        uint64_t invalid_ack_m_re      : 1;  /**< [ 19: 19] invalid range for ack_m_re */
        uint64_t invalid_ack_d_re      : 1;  /**< [ 18: 18] invalid range for ack_d_re */
        uint64_t invalid_ack_rsv_m_re  : 1;  /**< [ 17: 17] invalid range for ack_rsv_m_re */
        uint64_t invalid_ack_rsv_d_re  : 1;  /**< [ 16: 16] invalid range for ack_rsv_d_re */
        uint64_t invalid_csi2_enc_cat  : 1;  /**< [ 15: 15] invalid range for csi2_enc_cat */
        uint64_t invalid_csi1_enc_cat  : 1;  /**< [ 14: 14] invalid range for csi1_enc_cat */
        uint64_t invalid_ack_enc_cat   : 1;  /**< [ 13: 13] invalid range for ack_enc_cat */
        uint64_t invalid_ptrs_dfts_ofdm_delta : 1;/**< [ 12: 12] invalid range for ptrs_dfts_ofdm_delta */
        uint64_t invalid_ptrs_loc_re_length : 1;/**< [ 11: 11] invalid range for ptrs_loc_re_length */
        uint64_t invalid_ptrs_loc_re_offset : 1;/**< [ 10: 10] invalid range for ptrs_loc_re_offset */
        uint64_t invalid_ptrs_dist_vrb_bun_size : 1;/**< [  9:  9] invalid range for ptrs_dist_vrb_bundle_size */
        uint64_t invalid_ptrs_dist_start_rb_idx : 1;/**< [  8:  8] invalid range for ptrs_dist_start_rb_idx */
        uint64_t invalid_ptrs_dist_num_ports : 1;/**< [  7:  7] invalid range for ptrs_dist_num_ports */
        uint64_t invalid_ptrs_dist_re_offset : 1;/**< [  6:  6] invalid range for ptrs_dist_re_offset */
        uint64_t invalid_ptrs_dist_rb_step : 1;/**< [  5:  5] invalid range for ptrs_dist_rb_step */
        uint64_t invalid_ptrs_dist_rb_offset : 1;/**< [  4:  4] invalid range for ptrs_dist_rb_offset */
        uint64_t invalid_num_rb_pusch  : 1;  /**< [  3:  3] invalid range for num_rb_pusch */
        uint64_t invalid_rs_mapping_type : 1;/**< [  2:  2] invalid range for rs_mapping_type */
        uint64_t invalid_rs_cat        : 1;  /**< [  1:  1] invalid range for rs_cat */
        uint64_t invalid_rs_insertion_enable : 1;/**< [  0:  0] invalid range for rs_insertion_enable */
#else /* Word 0 - Little Endian */
        uint64_t invalid_rs_insertion_enable : 1;/**< [  0:  0] invalid range for rs_insertion_enable */
        uint64_t invalid_rs_cat        : 1;  /**< [  1:  1] invalid range for rs_cat */
        uint64_t invalid_rs_mapping_type : 1;/**< [  2:  2] invalid range for rs_mapping_type */
        uint64_t invalid_num_rb_pusch  : 1;  /**< [  3:  3] invalid range for num_rb_pusch */
        uint64_t invalid_ptrs_dist_rb_offset : 1;/**< [  4:  4] invalid range for ptrs_dist_rb_offset */
        uint64_t invalid_ptrs_dist_rb_step : 1;/**< [  5:  5] invalid range for ptrs_dist_rb_step */
        uint64_t invalid_ptrs_dist_re_offset : 1;/**< [  6:  6] invalid range for ptrs_dist_re_offset */
        uint64_t invalid_ptrs_dist_num_ports : 1;/**< [  7:  7] invalid range for ptrs_dist_num_ports */
        uint64_t invalid_ptrs_dist_start_rb_idx : 1;/**< [  8:  8] invalid range for ptrs_dist_start_rb_idx */
        uint64_t invalid_ptrs_dist_vrb_bun_size : 1;/**< [  9:  9] invalid range for ptrs_dist_vrb_bundle_size */
        uint64_t invalid_ptrs_loc_re_offset : 1;/**< [ 10: 10] invalid range for ptrs_loc_re_offset */
        uint64_t invalid_ptrs_loc_re_length : 1;/**< [ 11: 11] invalid range for ptrs_loc_re_length */
        uint64_t invalid_ptrs_dfts_ofdm_delta : 1;/**< [ 12: 12] invalid range for ptrs_dfts_ofdm_delta */
        uint64_t invalid_ack_enc_cat   : 1;  /**< [ 13: 13] invalid range for ack_enc_cat */
        uint64_t invalid_csi1_enc_cat  : 1;  /**< [ 14: 14] invalid range for csi1_enc_cat */
        uint64_t invalid_csi2_enc_cat  : 1;  /**< [ 15: 15] invalid range for csi2_enc_cat */
        uint64_t invalid_ack_rsv_d_re  : 1;  /**< [ 16: 16] invalid range for ack_rsv_d_re */
        uint64_t invalid_ack_rsv_m_re  : 1;  /**< [ 17: 17] invalid range for ack_rsv_m_re */
        uint64_t invalid_ack_d_re      : 1;  /**< [ 18: 18] invalid range for ack_d_re */
        uint64_t invalid_ack_m_re      : 1;  /**< [ 19: 19] invalid range for ack_m_re */
        uint64_t invalid_ack_bit_offset : 1; /**< [ 20: 20] invalid range for ack_bit_offset */
        uint64_t invalid_csi1_d_re     : 1;  /**< [ 21: 21] invalid range for csi1_d_re */
        uint64_t invalid_csi1_m_re     : 1;  /**< [ 22: 22] invalid range for csi1_m_re */
        uint64_t invalid_csi1_bit_offset : 1;/**< [ 23: 23] invalid range for csi1_bit_offset */
        uint64_t invalid_csi2_d_re     : 1;  /**< [ 24: 24] invalid range for csi2_d_re */
        uint64_t invalid_csi2_m_re     : 1;  /**< [ 25: 25] invalid range for csi2_m_re */
        uint64_t invalid_csi2_bit_offset : 1;/**< [ 26: 26] invalid range for csi2_bit_offset */
        uint64_t invalid_data_m_re     : 1;  /**< [ 27: 27] invalid range for data_m_re */
        uint64_t invalid_data_bit_offset : 1;/**< [ 28: 28] invalid range for data_bit_offset */
        uint64_t invalid_bypass_scrambler : 1;/**< [ 29: 29] invalid range for bypass_scrambler */
        uint64_t invalid_scrambling_init : 1;/**< [ 30: 30] invalid range for scrambling_init */
        uint64_t invalid_scrambling_offset : 1;/**< [ 31: 31] invalid range for scrambling_offset */
        uint64_t invalid_num_layers    : 1;  /**< [ 32: 32] invalid range for num_layers */
        uint64_t invalid_mod_order     : 1;  /**< [ 33: 33] invalid range for mod_order */
        uint64_t invalid_ack_reenc_mode : 1; /**< [ 34: 34] invalid range for ack_reenc_mode */
        uint64_t invalid_csi1_reenc_mode : 1;/**< [ 35: 35] invalid range for csi1_reenc_mode */
        uint64_t invalid_csi2_reenc_mode : 1;/**< [ 36: 36] invalid range for csi2_reenc_mode */
        uint64_t invalid_data_reenc_mode : 1;/**< [ 37: 37] invalid range for data_reenc_mode */
        uint64_t invalid_ack_crc       : 1;  /**< [ 38: 38] invalid range for ack_crc */
        uint64_t invalid_csi1_crc      : 1;  /**< [ 39: 39] invalid range for csi1_crc */
        uint64_t invalid_csi2_crc      : 1;  /**< [ 40: 40] invalid range for csi2_crc */
        uint64_t reserved_41_63        : 23;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmap_tc_nr_config_err_s_s cn; */
};

/**
 * Register (RSL) rmap#_control
 *
 * RMAP Control Register
 * This register is used to start RMAP HAB processing.
 */
union bdk_rmapx_control
{
    uint64_t u;
    struct bdk_rmapx_control_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t jobid2                : 16; /**< [ 63: 48](R/W/H) Job ID2 */
        uint64_t jobid1                : 16; /**< [ 47: 32](R/W/H) Job ID1 */
        uint64_t jobid0                : 16; /**< [ 31: 16](R/W/H) Job ID0 */
        uint64_t reserved_3_15         : 13;
        uint64_t start2                : 1;  /**< [  2:  2](R/W/H) Write 1 to start processing the job in configuration slot 2. This bit auto-clears.
                                                                 Writes are ignored when the configuration slot is busy (RMAP(0..1)_STATUS[STATUS2] = 1). */
        uint64_t start1                : 1;  /**< [  1:  1](R/W/H) Write 1 to start processing the job in configuration slot 1. This bit auto-clears.
                                                                 Writes are ignored when the configuration slot is busy (RMAP(0..1)_STATUS[STATUS1] = 1). */
        uint64_t start0                : 1;  /**< [  0:  0](R/W/H) Write 1 to start processing the job in configuration slot 0. This bit auto-clears.
                                                                 Writes are ignored when the configuration slot is busy (RMAP(0..1)_STATUS[STATUS0] = 1). */
#else /* Word 0 - Little Endian */
        uint64_t start0                : 1;  /**< [  0:  0](R/W/H) Write 1 to start processing the job in configuration slot 0. This bit auto-clears.
                                                                 Writes are ignored when the configuration slot is busy (RMAP(0..1)_STATUS[STATUS0] = 1). */
        uint64_t start1                : 1;  /**< [  1:  1](R/W/H) Write 1 to start processing the job in configuration slot 1. This bit auto-clears.
                                                                 Writes are ignored when the configuration slot is busy (RMAP(0..1)_STATUS[STATUS1] = 1). */
        uint64_t start2                : 1;  /**< [  2:  2](R/W/H) Write 1 to start processing the job in configuration slot 2. This bit auto-clears.
                                                                 Writes are ignored when the configuration slot is busy (RMAP(0..1)_STATUS[STATUS2] = 1). */
        uint64_t reserved_3_15         : 13;
        uint64_t jobid0                : 16; /**< [ 31: 16](R/W/H) Job ID0 */
        uint64_t jobid1                : 16; /**< [ 47: 32](R/W/H) Job ID1 */
        uint64_t jobid2                : 16; /**< [ 63: 48](R/W/H) Job ID2 */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_control_s cn; */
};
typedef union bdk_rmapx_control bdk_rmapx_control_t;

static inline uint64_t BDK_RMAPX_CONTROL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_CONTROL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043380000ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043380000ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_CONTROL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_CONTROL(a) bdk_rmapx_control_t
#define bustype_BDK_RMAPX_CONTROL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_CONTROL(a) "RMAPX_CONTROL"
#define busnum_BDK_RMAPX_CONTROL(a) (a)
#define arguments_BDK_RMAPX_CONTROL(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_eco
 *
 * INTERNAL: RMAP ECO Register
 */
union bdk_rmapx_eco
{
    uint64_t u;
    struct bdk_rmapx_eco_s
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
    /* struct bdk_rmapx_eco_s cn; */
};
typedef union bdk_rmapx_eco bdk_rmapx_eco_t;

static inline uint64_t BDK_RMAPX_ECO(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_ECO(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043380008ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043380008ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_ECO", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_ECO(a) bdk_rmapx_eco_t
#define bustype_BDK_RMAPX_ECO(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_ECO(a) "RMAPX_ECO"
#define busnum_BDK_RMAPX_ECO(a) (a)
#define arguments_BDK_RMAPX_ECO(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_error_enable0
 *
 * RMAP Error Enable 0 Register
 * This register enables error reporting for RMAP(0..1)_ERROR_SOURCE0 register.
 */
union bdk_rmapx_error_enable0
{
    uint64_t u;
    struct bdk_rmapx_error_enable0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t rp1_of_en             : 1;  /**< [  5:  5](R/W) Read Port 1 Overflow Enable */
        uint64_t rp0_of_en             : 1;  /**< [  4:  4](R/W) Read Port 0 Overflow Enable */
        uint64_t reserved_2_3          : 2;
        uint64_t rp1_uf_en             : 1;  /**< [  1:  1](R/W) Read Port 1 Underflow Enable */
        uint64_t rp0_uf_en             : 1;  /**< [  0:  0](R/W) Read Port 0 Underflow Enable */
#else /* Word 0 - Little Endian */
        uint64_t rp0_uf_en             : 1;  /**< [  0:  0](R/W) Read Port 0 Underflow Enable */
        uint64_t rp1_uf_en             : 1;  /**< [  1:  1](R/W) Read Port 1 Underflow Enable */
        uint64_t reserved_2_3          : 2;
        uint64_t rp0_of_en             : 1;  /**< [  4:  4](R/W) Read Port 0 Overflow Enable */
        uint64_t rp1_of_en             : 1;  /**< [  5:  5](R/W) Read Port 1 Overflow Enable */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_error_enable0_s cn; */
};
typedef union bdk_rmapx_error_enable0 bdk_rmapx_error_enable0_t;

static inline uint64_t BDK_RMAPX_ERROR_ENABLE0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_ERROR_ENABLE0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043380040ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043380040ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_ERROR_ENABLE0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_ERROR_ENABLE0(a) bdk_rmapx_error_enable0_t
#define bustype_BDK_RMAPX_ERROR_ENABLE0(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_ERROR_ENABLE0(a) "RMAPX_ERROR_ENABLE0"
#define busnum_BDK_RMAPX_ERROR_ENABLE0(a) (a)
#define arguments_BDK_RMAPX_ERROR_ENABLE0(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_error_enable1
 *
 * RMAP Error Enable 1 Register
 * This register enables reporting of job configuration errors.
 */
union bdk_rmapx_error_enable1
{
    uint64_t u;
    struct bdk_rmapx_error_enable1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_34_63        : 30;
        uint64_t tc_event_en           : 1;  /**< [ 33: 33](R/W) Enable unexpected event reporting from TC core */
        uint64_t tc_error_en           : 1;  /**< [ 32: 32](R/W) Enable error reporting from TC core */
        uint64_t reserved_19_31        : 13;
        uint64_t total_re_err_en       : 1;  /**< [ 18: 18](R/W) Enable reporting of inconsistent total RE errors. */
        uint64_t r_prime_mux_err_en    : 1;  /**< [ 17: 17](R/W) Enable reporting of invalid R_PRIME_MUX settings. */
        uint64_t dft_idx_err1_en       : 1;  /**< [ 16: 16](R/W) Enable reporting for invalid combinations of NDFT_INDX and NUM_RB. */
        uint64_t dft_idx_err0_en       : 1;  /**< [ 15: 15](R/W) Enable reporting of invalid NDFT_INDX setting. */
        uint64_t rb_set_err_en         : 1;  /**< [ 14: 14](R/W) Enable reporting of invalid RB_SET0 and RB_SET1 combinations for allocation type 1. */
        uint64_t ri_cat_err_en         : 1;  /**< [ 13: 13](R/W) Enable reporting of invalid RI_ENC_CAT setting. */
        uint64_t ack_cat_err_en        : 1;  /**< [ 12: 12](R/W) Enable reporting of invalid ACK_ENC_CAT setting. */
        uint64_t num_layers_err_en     : 1;  /**< [ 11: 11](R/W) Enable reporting of invalid NUM_LAYERS setting. */
        uint64_t mod_order_err_en      : 1;  /**< [ 10: 10](R/W) Enable reporting of invalid MOD_ORDER setting. */
        uint64_t byte_order_err3_en    : 1;  /**< [  9:  9](R/W) Enable reporting of invalid ACK_BYTE_ORDER setting. */
        uint64_t byte_order_err2_en    : 1;  /**< [  8:  8](R/W) Enable reporting of invalid RI_BYTE_ORDER setting. */
        uint64_t byte_order_err1_en    : 1;  /**< [  7:  7](R/W) Enable reporting of invalid CQI_BYTE_ORDER setting. */
        uint64_t byte_order_err0_en    : 1;  /**< [  6:  6](R/W) Enable reporting of invalid DATA_BYTE_ORDER setting. */
        uint64_t ack_err1_en           : 1;  /**< [  5:  5](R/W) Enable reporting of non-zero NUM_ACK_RE with zero ACK_ENC_CAT. */
        uint64_t ack_err0_en           : 1;  /**< [  4:  4](R/W) Enable reporting of zero NUM_ACK_RE with non-zero ACK_ENC_CAT. */
        uint64_t ri_err1_en            : 1;  /**< [  3:  3](R/W) Enable reporting of non-zero NUM_RI_RE with zero RI_ENC_CAT. */
        uint64_t ri_err0_en            : 1;  /**< [  2:  2](R/W) Enable reporting of zero NUM_RI_RE with non-zero RI_ENC_CAT. */
        uint64_t cqi_err1_en           : 1;  /**< [  1:  1](R/W) Enable reporting of non-zero NUM_CQI_RE with zero NUM_ENCODED_CQI_BITS. */
        uint64_t cqi_err0_en           : 1;  /**< [  0:  0](R/W) Enable reporting of zero NUM_CQI_RE with non-zero NUM_ENCODED_CQI_BITS. */
#else /* Word 0 - Little Endian */
        uint64_t cqi_err0_en           : 1;  /**< [  0:  0](R/W) Enable reporting of zero NUM_CQI_RE with non-zero NUM_ENCODED_CQI_BITS. */
        uint64_t cqi_err1_en           : 1;  /**< [  1:  1](R/W) Enable reporting of non-zero NUM_CQI_RE with zero NUM_ENCODED_CQI_BITS. */
        uint64_t ri_err0_en            : 1;  /**< [  2:  2](R/W) Enable reporting of zero NUM_RI_RE with non-zero RI_ENC_CAT. */
        uint64_t ri_err1_en            : 1;  /**< [  3:  3](R/W) Enable reporting of non-zero NUM_RI_RE with zero RI_ENC_CAT. */
        uint64_t ack_err0_en           : 1;  /**< [  4:  4](R/W) Enable reporting of zero NUM_ACK_RE with non-zero ACK_ENC_CAT. */
        uint64_t ack_err1_en           : 1;  /**< [  5:  5](R/W) Enable reporting of non-zero NUM_ACK_RE with zero ACK_ENC_CAT. */
        uint64_t byte_order_err0_en    : 1;  /**< [  6:  6](R/W) Enable reporting of invalid DATA_BYTE_ORDER setting. */
        uint64_t byte_order_err1_en    : 1;  /**< [  7:  7](R/W) Enable reporting of invalid CQI_BYTE_ORDER setting. */
        uint64_t byte_order_err2_en    : 1;  /**< [  8:  8](R/W) Enable reporting of invalid RI_BYTE_ORDER setting. */
        uint64_t byte_order_err3_en    : 1;  /**< [  9:  9](R/W) Enable reporting of invalid ACK_BYTE_ORDER setting. */
        uint64_t mod_order_err_en      : 1;  /**< [ 10: 10](R/W) Enable reporting of invalid MOD_ORDER setting. */
        uint64_t num_layers_err_en     : 1;  /**< [ 11: 11](R/W) Enable reporting of invalid NUM_LAYERS setting. */
        uint64_t ack_cat_err_en        : 1;  /**< [ 12: 12](R/W) Enable reporting of invalid ACK_ENC_CAT setting. */
        uint64_t ri_cat_err_en         : 1;  /**< [ 13: 13](R/W) Enable reporting of invalid RI_ENC_CAT setting. */
        uint64_t rb_set_err_en         : 1;  /**< [ 14: 14](R/W) Enable reporting of invalid RB_SET0 and RB_SET1 combinations for allocation type 1. */
        uint64_t dft_idx_err0_en       : 1;  /**< [ 15: 15](R/W) Enable reporting of invalid NDFT_INDX setting. */
        uint64_t dft_idx_err1_en       : 1;  /**< [ 16: 16](R/W) Enable reporting for invalid combinations of NDFT_INDX and NUM_RB. */
        uint64_t r_prime_mux_err_en    : 1;  /**< [ 17: 17](R/W) Enable reporting of invalid R_PRIME_MUX settings. */
        uint64_t total_re_err_en       : 1;  /**< [ 18: 18](R/W) Enable reporting of inconsistent total RE errors. */
        uint64_t reserved_19_31        : 13;
        uint64_t tc_error_en           : 1;  /**< [ 32: 32](R/W) Enable error reporting from TC core */
        uint64_t tc_event_en           : 1;  /**< [ 33: 33](R/W) Enable unexpected event reporting from TC core */
        uint64_t reserved_34_63        : 30;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_error_enable1_s cn; */
};
typedef union bdk_rmapx_error_enable1 bdk_rmapx_error_enable1_t;

static inline uint64_t BDK_RMAPX_ERROR_ENABLE1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_ERROR_ENABLE1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043380048ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043380048ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_ERROR_ENABLE1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_ERROR_ENABLE1(a) bdk_rmapx_error_enable1_t
#define bustype_BDK_RMAPX_ERROR_ENABLE1(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_ERROR_ENABLE1(a) "RMAPX_ERROR_ENABLE1"
#define busnum_BDK_RMAPX_ERROR_ENABLE1(a) (a)
#define arguments_BDK_RMAPX_ERROR_ENABLE1(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_error_source0
 *
 * RMAP Error Source 0 Register
 * This is register contains information about read port overflows and underflows.
 */
union bdk_rmapx_error_source0
{
    uint64_t u;
    struct bdk_rmapx_error_source0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t rp0_jobid             : 16; /**< [ 31: 16](RO/H) Job ID for the job that caused either an underflow or overflow on port 0. */
        uint64_t reserved_6_15         : 10;
        uint64_t rp1_of                : 1;  /**< [  5:  5](R/W1C/H) Set to 1 when an overflow occurs on port 1. Cleared by a write to one. */
        uint64_t rp0_of                : 1;  /**< [  4:  4](R/W1C/H) Set to 1 when an overflow occurs on port 0. Cleared by a write to one. */
        uint64_t reserved_2_3          : 2;
        uint64_t rp1_uf                : 1;  /**< [  1:  1](R/W1C/H) Set to 1 when an underflow occurs on port 1. Cleared by a write to one. */
        uint64_t rp0_uf                : 1;  /**< [  0:  0](R/W1C/H) Set to 1 when an underflow occurs on port 0. Cleared by a write to one. */
#else /* Word 0 - Little Endian */
        uint64_t rp0_uf                : 1;  /**< [  0:  0](R/W1C/H) Set to 1 when an underflow occurs on port 0. Cleared by a write to one. */
        uint64_t rp1_uf                : 1;  /**< [  1:  1](R/W1C/H) Set to 1 when an underflow occurs on port 1. Cleared by a write to one. */
        uint64_t reserved_2_3          : 2;
        uint64_t rp0_of                : 1;  /**< [  4:  4](R/W1C/H) Set to 1 when an overflow occurs on port 0. Cleared by a write to one. */
        uint64_t rp1_of                : 1;  /**< [  5:  5](R/W1C/H) Set to 1 when an overflow occurs on port 1. Cleared by a write to one. */
        uint64_t reserved_6_15         : 10;
        uint64_t rp0_jobid             : 16; /**< [ 31: 16](RO/H) Job ID for the job that caused either an underflow or overflow on port 0. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_error_source0_s cn; */
};
typedef union bdk_rmapx_error_source0 bdk_rmapx_error_source0_t;

static inline uint64_t BDK_RMAPX_ERROR_SOURCE0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_ERROR_SOURCE0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043380030ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043380030ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_ERROR_SOURCE0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_ERROR_SOURCE0(a) bdk_rmapx_error_source0_t
#define bustype_BDK_RMAPX_ERROR_SOURCE0(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_ERROR_SOURCE0(a) "RMAPX_ERROR_SOURCE0"
#define busnum_BDK_RMAPX_ERROR_SOURCE0(a) (a)
#define arguments_BDK_RMAPX_ERROR_SOURCE0(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_error_source1
 *
 * RMAP Error Source 1 Register
 * This register contains information about job configuration errors.
 */
union bdk_rmapx_error_source1
{
    uint64_t u;
    struct bdk_rmapx_error_source1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_34_63        : 30;
        uint64_t tc_event              : 1;  /**< [ 33: 33](R/W1C/H) Unexpected event reported from TC core, examine its CSR to determine the sources.
                                                                 This signal is tied low inside TC1860 so it should never get signaled. */
        uint64_t tc_error              : 1;  /**< [ 32: 32](R/W1C/H) Error within multiplexing, interleaving and scrambling sub-block. See
                                                                 RMAP(0..1)_TC_ERROR for additional error information. */
        uint64_t reserved_21_31        : 11;
        uint64_t csi2_cat_err          : 1;  /**< [ 20: 20](R/W1C/H) Invalid CSI2_ENC_CAT setting. */
        uint64_t csi1_cat_err          : 1;  /**< [ 19: 19](R/W1C/H) Invalid CSI1_ENC_CAT setting. */
        uint64_t total_re_err          : 1;  /**< [ 18: 18](R/W1C/H) Inconsistent total RE detected - (R_PRIME_MUX x NUM_SYMB_PUSCH) != (G_PRIME + NUM_CQI_RE +
                                                                 NUM_RI_RE). */
        uint64_t r_prime_mux_err       : 1;  /**< [ 17: 17](R/W1C/H) Invalid R_PRIME_MUX setting. R_PRIME_MUX must be NUM_RB*3. */
        uint64_t dft_idx_err1          : 1;  /**< [ 16: 16](R/W1C/H) Invalid combination of DFT index and NUM_RB detected. The combination of
                                                                 NDFT_INDX and NUM_RB, valid combinations are listed in the DFT index table. */
        uint64_t dft_idx_err0          : 1;  /**< [ 15: 15](R/W1C/H) Invalid DFT_INDX setting. */
        uint64_t rb_set_err            : 1;  /**< [ 14: 14](R/W1C/H) Invalid combination of LENGTH_RB_SET0 and LENGTH_RB_SET1 for
                                                                 allocation type 1 - they must sum to NUM_RB. */
        uint64_t ri_cat_err            : 1;  /**< [ 13: 13](R/W1C/H) Invalid RI_ENC_CAT setting. */
        uint64_t ack_cat_err           : 1;  /**< [ 12: 12](R/W1C/H) Invalid ACT_ENC_CAT setting. */
        uint64_t num_layers_err        : 1;  /**< [ 11: 11](R/W1C/H) Invalid NUM_LAYERS setting. */
        uint64_t mod_order_err         : 1;  /**< [ 10: 10](R/W1C/H) Invalid MOD_ORDER setting. */
        uint64_t byte_order_err3       : 1;  /**< [  9:  9](R/W1C/H) Invalid ACK_BYTE_ORDER setting. */
        uint64_t byte_order_err2       : 1;  /**< [  8:  8](R/W1C/H) Invalid RI_BYTE_ORDER setting. */
        uint64_t byte_order_err1       : 1;  /**< [  7:  7](R/W1C/H) Invalid CQI_BYTE_ORDER setting. */
        uint64_t byte_order_err0       : 1;  /**< [  6:  6](R/W1C/H) Invalid DATA_BYTE_ORDER setting. */
        uint64_t ack_err1              : 1;  /**< [  5:  5](R/W1C/H) Inconsistent ACK parameters - ACK_ENC_CAT was zero but NUM_ACK_RE was
                                                                 not zero. */
        uint64_t ack_err0              : 1;  /**< [  4:  4](R/W1C/H) Inconsistent ACK parameters - NUM_ACK_RE was zero but ACK_ENC_CAT was
                                                                 not zero. */
        uint64_t ri_err1               : 1;  /**< [  3:  3](R/W1C/H) Inconsistent RI parameters - RI_ENC_CAT was zero but NUM_RI_RE was
                                                                 not zero. */
        uint64_t ri_err0               : 1;  /**< [  2:  2](R/W1C/H) Inconsistent RI parameters - NUM_RI_RE was zero but RI_ENC_CAT was not zero. */
        uint64_t cqi_err1              : 1;  /**< [  1:  1](R/W1C/H) Inconsistent CQI parameters - NUM_ENCODED_CQI_BITS was zero but NUM_CQI_RE was
                                                                 not zero. */
        uint64_t cqi_err0              : 1;  /**< [  0:  0](R/W1C/H) Inconsistent CQI parameters - NUM_CQI_RE was zero but NUM_ENCODED_CQI_BITS was
                                                                 not zero. */
#else /* Word 0 - Little Endian */
        uint64_t cqi_err0              : 1;  /**< [  0:  0](R/W1C/H) Inconsistent CQI parameters - NUM_CQI_RE was zero but NUM_ENCODED_CQI_BITS was
                                                                 not zero. */
        uint64_t cqi_err1              : 1;  /**< [  1:  1](R/W1C/H) Inconsistent CQI parameters - NUM_ENCODED_CQI_BITS was zero but NUM_CQI_RE was
                                                                 not zero. */
        uint64_t ri_err0               : 1;  /**< [  2:  2](R/W1C/H) Inconsistent RI parameters - NUM_RI_RE was zero but RI_ENC_CAT was not zero. */
        uint64_t ri_err1               : 1;  /**< [  3:  3](R/W1C/H) Inconsistent RI parameters - RI_ENC_CAT was zero but NUM_RI_RE was
                                                                 not zero. */
        uint64_t ack_err0              : 1;  /**< [  4:  4](R/W1C/H) Inconsistent ACK parameters - NUM_ACK_RE was zero but ACK_ENC_CAT was
                                                                 not zero. */
        uint64_t ack_err1              : 1;  /**< [  5:  5](R/W1C/H) Inconsistent ACK parameters - ACK_ENC_CAT was zero but NUM_ACK_RE was
                                                                 not zero. */
        uint64_t byte_order_err0       : 1;  /**< [  6:  6](R/W1C/H) Invalid DATA_BYTE_ORDER setting. */
        uint64_t byte_order_err1       : 1;  /**< [  7:  7](R/W1C/H) Invalid CQI_BYTE_ORDER setting. */
        uint64_t byte_order_err2       : 1;  /**< [  8:  8](R/W1C/H) Invalid RI_BYTE_ORDER setting. */
        uint64_t byte_order_err3       : 1;  /**< [  9:  9](R/W1C/H) Invalid ACK_BYTE_ORDER setting. */
        uint64_t mod_order_err         : 1;  /**< [ 10: 10](R/W1C/H) Invalid MOD_ORDER setting. */
        uint64_t num_layers_err        : 1;  /**< [ 11: 11](R/W1C/H) Invalid NUM_LAYERS setting. */
        uint64_t ack_cat_err           : 1;  /**< [ 12: 12](R/W1C/H) Invalid ACT_ENC_CAT setting. */
        uint64_t ri_cat_err            : 1;  /**< [ 13: 13](R/W1C/H) Invalid RI_ENC_CAT setting. */
        uint64_t rb_set_err            : 1;  /**< [ 14: 14](R/W1C/H) Invalid combination of LENGTH_RB_SET0 and LENGTH_RB_SET1 for
                                                                 allocation type 1 - they must sum to NUM_RB. */
        uint64_t dft_idx_err0          : 1;  /**< [ 15: 15](R/W1C/H) Invalid DFT_INDX setting. */
        uint64_t dft_idx_err1          : 1;  /**< [ 16: 16](R/W1C/H) Invalid combination of DFT index and NUM_RB detected. The combination of
                                                                 NDFT_INDX and NUM_RB, valid combinations are listed in the DFT index table. */
        uint64_t r_prime_mux_err       : 1;  /**< [ 17: 17](R/W1C/H) Invalid R_PRIME_MUX setting. R_PRIME_MUX must be NUM_RB*3. */
        uint64_t total_re_err          : 1;  /**< [ 18: 18](R/W1C/H) Inconsistent total RE detected - (R_PRIME_MUX x NUM_SYMB_PUSCH) != (G_PRIME + NUM_CQI_RE +
                                                                 NUM_RI_RE). */
        uint64_t csi1_cat_err          : 1;  /**< [ 19: 19](R/W1C/H) Invalid CSI1_ENC_CAT setting. */
        uint64_t csi2_cat_err          : 1;  /**< [ 20: 20](R/W1C/H) Invalid CSI2_ENC_CAT setting. */
        uint64_t reserved_21_31        : 11;
        uint64_t tc_error              : 1;  /**< [ 32: 32](R/W1C/H) Error within multiplexing, interleaving and scrambling sub-block. See
                                                                 RMAP(0..1)_TC_ERROR for additional error information. */
        uint64_t tc_event              : 1;  /**< [ 33: 33](R/W1C/H) Unexpected event reported from TC core, examine its CSR to determine the sources.
                                                                 This signal is tied low inside TC1860 so it should never get signaled. */
        uint64_t reserved_34_63        : 30;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_error_source1_s cn; */
};
typedef union bdk_rmapx_error_source1 bdk_rmapx_error_source1_t;

static inline uint64_t BDK_RMAPX_ERROR_SOURCE1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_ERROR_SOURCE1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043380038ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043380038ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_ERROR_SOURCE1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_ERROR_SOURCE1(a) bdk_rmapx_error_source1_t
#define bustype_BDK_RMAPX_ERROR_SOURCE1(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_ERROR_SOURCE1(a) "RMAPX_ERROR_SOURCE1"
#define busnum_BDK_RMAPX_ERROR_SOURCE1(a) (a)
#define arguments_BDK_RMAPX_ERROR_SOURCE1(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_jd0_cfg0
 *
 * RMAP Slot 0 Configuration Register 0
 * This register stores the 1st job configuration word for slot 0.
 */
union bdk_rmapx_jd0_cfg0
{
    uint64_t u;
    struct bdk_rmapx_jd0_cfg0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t phy_mode              : 1;  /**< [ 63: 63](R/W) LTE/NR Mode. 0 = LTE, 1 = NR. */
        uint64_t cfg0_data             : 63; /**< [ 62:  0](R/W) CFG0 Data */
#else /* Word 0 - Little Endian */
        uint64_t cfg0_data             : 63; /**< [ 62:  0](R/W) CFG0 Data */
        uint64_t phy_mode              : 1;  /**< [ 63: 63](R/W) LTE/NR Mode. 0 = LTE, 1 = NR. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_jd0_cfg0_s cn; */
};
typedef union bdk_rmapx_jd0_cfg0 bdk_rmapx_jd0_cfg0_t;

static inline uint64_t BDK_RMAPX_JD0_CFG0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_JD0_CFG0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043382000ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043382000ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_JD0_CFG0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_JD0_CFG0(a) bdk_rmapx_jd0_cfg0_t
#define bustype_BDK_RMAPX_JD0_CFG0(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_JD0_CFG0(a) "RMAPX_JD0_CFG0"
#define busnum_BDK_RMAPX_JD0_CFG0(a) (a)
#define arguments_BDK_RMAPX_JD0_CFG0(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_jd0_cfg1
 *
 * RMAP Slot 0 Configuration Register 1
 * This register stores the 2nd job configuration word for slot 0.
 */
union bdk_rmapx_jd0_cfg1
{
    uint64_t u;
    struct bdk_rmapx_jd0_cfg1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cfg1_data             : 64; /**< [ 63:  0](R/W) CFG1 Data */
#else /* Word 0 - Little Endian */
        uint64_t cfg1_data             : 64; /**< [ 63:  0](R/W) CFG1 Data */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_jd0_cfg1_s cn; */
};
typedef union bdk_rmapx_jd0_cfg1 bdk_rmapx_jd0_cfg1_t;

static inline uint64_t BDK_RMAPX_JD0_CFG1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_JD0_CFG1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043382008ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043382008ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_JD0_CFG1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_JD0_CFG1(a) bdk_rmapx_jd0_cfg1_t
#define bustype_BDK_RMAPX_JD0_CFG1(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_JD0_CFG1(a) "RMAPX_JD0_CFG1"
#define busnum_BDK_RMAPX_JD0_CFG1(a) (a)
#define arguments_BDK_RMAPX_JD0_CFG1(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_jd0_cfg2
 *
 * RMAP Slot 0 Configuration Register 2
 * This register stores the 3rd job configuration word for slot 0.
 */
union bdk_rmapx_jd0_cfg2
{
    uint64_t u;
    struct bdk_rmapx_jd0_cfg2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cfg2_data             : 64; /**< [ 63:  0](R/W) CFG2 Data */
#else /* Word 0 - Little Endian */
        uint64_t cfg2_data             : 64; /**< [ 63:  0](R/W) CFG2 Data */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_jd0_cfg2_s cn; */
};
typedef union bdk_rmapx_jd0_cfg2 bdk_rmapx_jd0_cfg2_t;

static inline uint64_t BDK_RMAPX_JD0_CFG2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_JD0_CFG2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043382010ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043382010ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_JD0_CFG2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_JD0_CFG2(a) bdk_rmapx_jd0_cfg2_t
#define bustype_BDK_RMAPX_JD0_CFG2(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_JD0_CFG2(a) "RMAPX_JD0_CFG2"
#define busnum_BDK_RMAPX_JD0_CFG2(a) (a)
#define arguments_BDK_RMAPX_JD0_CFG2(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_jd0_cfg3
 *
 * RMAP Slot 0 Configuration Register 3
 * This register stores the 4th job configuration word for slot 0.
 */
union bdk_rmapx_jd0_cfg3
{
    uint64_t u;
    struct bdk_rmapx_jd0_cfg3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cfg3_data             : 64; /**< [ 63:  0](R/W) CFG3 Data */
#else /* Word 0 - Little Endian */
        uint64_t cfg3_data             : 64; /**< [ 63:  0](R/W) CFG3 Data */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_jd0_cfg3_s cn; */
};
typedef union bdk_rmapx_jd0_cfg3 bdk_rmapx_jd0_cfg3_t;

static inline uint64_t BDK_RMAPX_JD0_CFG3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_JD0_CFG3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043382018ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043382018ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_JD0_CFG3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_JD0_CFG3(a) bdk_rmapx_jd0_cfg3_t
#define bustype_BDK_RMAPX_JD0_CFG3(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_JD0_CFG3(a) "RMAPX_JD0_CFG3"
#define busnum_BDK_RMAPX_JD0_CFG3(a) (a)
#define arguments_BDK_RMAPX_JD0_CFG3(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_jd0_cfg4
 *
 * RMAP Slot 0 Configuration Register 4
 * This register stores the 5th job configuration word for slot 0.
 */
union bdk_rmapx_jd0_cfg4
{
    uint64_t u;
    struct bdk_rmapx_jd0_cfg4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cfg4_data             : 64; /**< [ 63:  0](R/W) CFG4 Data */
#else /* Word 0 - Little Endian */
        uint64_t cfg4_data             : 64; /**< [ 63:  0](R/W) CFG4 Data */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_jd0_cfg4_s cn; */
};
typedef union bdk_rmapx_jd0_cfg4 bdk_rmapx_jd0_cfg4_t;

static inline uint64_t BDK_RMAPX_JD0_CFG4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_JD0_CFG4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043382020ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043382020ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_JD0_CFG4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_JD0_CFG4(a) bdk_rmapx_jd0_cfg4_t
#define bustype_BDK_RMAPX_JD0_CFG4(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_JD0_CFG4(a) "RMAPX_JD0_CFG4"
#define busnum_BDK_RMAPX_JD0_CFG4(a) (a)
#define arguments_BDK_RMAPX_JD0_CFG4(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_jd0_cfg5
 *
 * RMAP Slot 0 Configuration Register 5
 * This register stores the 6th job configuration word for slot 0.
 */
union bdk_rmapx_jd0_cfg5
{
    uint64_t u;
    struct bdk_rmapx_jd0_cfg5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cfg5_data             : 64; /**< [ 63:  0](R/W) CFG5 Data */
#else /* Word 0 - Little Endian */
        uint64_t cfg5_data             : 64; /**< [ 63:  0](R/W) CFG5 Data */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_jd0_cfg5_s cn; */
};
typedef union bdk_rmapx_jd0_cfg5 bdk_rmapx_jd0_cfg5_t;

static inline uint64_t BDK_RMAPX_JD0_CFG5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_JD0_CFG5(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043382028ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043382028ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_JD0_CFG5", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_JD0_CFG5(a) bdk_rmapx_jd0_cfg5_t
#define bustype_BDK_RMAPX_JD0_CFG5(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_JD0_CFG5(a) "RMAPX_JD0_CFG5"
#define busnum_BDK_RMAPX_JD0_CFG5(a) (a)
#define arguments_BDK_RMAPX_JD0_CFG5(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_jd0_cfg6
 *
 * RMAP Slot 0 Configuration Register 6
 * This register stores the 7th job configuration word for slot 0.
 */
union bdk_rmapx_jd0_cfg6
{
    uint64_t u;
    struct bdk_rmapx_jd0_cfg6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cfg6_data             : 64; /**< [ 63:  0](R/W) CFG6 Data */
#else /* Word 0 - Little Endian */
        uint64_t cfg6_data             : 64; /**< [ 63:  0](R/W) CFG6 Data */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_jd0_cfg6_s cn; */
};
typedef union bdk_rmapx_jd0_cfg6 bdk_rmapx_jd0_cfg6_t;

static inline uint64_t BDK_RMAPX_JD0_CFG6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_JD0_CFG6(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043382030ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043382030ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_JD0_CFG6", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_JD0_CFG6(a) bdk_rmapx_jd0_cfg6_t
#define bustype_BDK_RMAPX_JD0_CFG6(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_JD0_CFG6(a) "RMAPX_JD0_CFG6"
#define busnum_BDK_RMAPX_JD0_CFG6(a) (a)
#define arguments_BDK_RMAPX_JD0_CFG6(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_jd1_cfg0
 *
 * RMAP Slot 1 Configuration Register 0
 * This register stores the 1st job configuration word for slot 0.
 */
union bdk_rmapx_jd1_cfg0
{
    uint64_t u;
    struct bdk_rmapx_jd1_cfg0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t phy_mode              : 1;  /**< [ 63: 63](R/W) LTE/NR Mode. 0 = LTE, 1 = NR. */
        uint64_t cfg0_data             : 63; /**< [ 62:  0](R/W) CFG0 Data */
#else /* Word 0 - Little Endian */
        uint64_t cfg0_data             : 63; /**< [ 62:  0](R/W) CFG0 Data */
        uint64_t phy_mode              : 1;  /**< [ 63: 63](R/W) LTE/NR Mode. 0 = LTE, 1 = NR. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_jd1_cfg0_s cn; */
};
typedef union bdk_rmapx_jd1_cfg0 bdk_rmapx_jd1_cfg0_t;

static inline uint64_t BDK_RMAPX_JD1_CFG0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_JD1_CFG0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043384000ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043384000ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_JD1_CFG0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_JD1_CFG0(a) bdk_rmapx_jd1_cfg0_t
#define bustype_BDK_RMAPX_JD1_CFG0(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_JD1_CFG0(a) "RMAPX_JD1_CFG0"
#define busnum_BDK_RMAPX_JD1_CFG0(a) (a)
#define arguments_BDK_RMAPX_JD1_CFG0(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_jd1_cfg1
 *
 * RMAP Slot 1 Configuration Register 1
 * This register stores the 2nd job configuration word for slot 0.
 */
union bdk_rmapx_jd1_cfg1
{
    uint64_t u;
    struct bdk_rmapx_jd1_cfg1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cfg1_data             : 64; /**< [ 63:  0](R/W) CFG1 Data */
#else /* Word 0 - Little Endian */
        uint64_t cfg1_data             : 64; /**< [ 63:  0](R/W) CFG1 Data */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_jd1_cfg1_s cn; */
};
typedef union bdk_rmapx_jd1_cfg1 bdk_rmapx_jd1_cfg1_t;

static inline uint64_t BDK_RMAPX_JD1_CFG1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_JD1_CFG1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043384008ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043384008ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_JD1_CFG1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_JD1_CFG1(a) bdk_rmapx_jd1_cfg1_t
#define bustype_BDK_RMAPX_JD1_CFG1(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_JD1_CFG1(a) "RMAPX_JD1_CFG1"
#define busnum_BDK_RMAPX_JD1_CFG1(a) (a)
#define arguments_BDK_RMAPX_JD1_CFG1(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_jd1_cfg2
 *
 * RMAP Slot 1 Configuration Register 2
 * This register stores the 3rd job configuration word for slot 0.
 */
union bdk_rmapx_jd1_cfg2
{
    uint64_t u;
    struct bdk_rmapx_jd1_cfg2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cfg2_data             : 64; /**< [ 63:  0](R/W) CFG2 Data */
#else /* Word 0 - Little Endian */
        uint64_t cfg2_data             : 64; /**< [ 63:  0](R/W) CFG2 Data */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_jd1_cfg2_s cn; */
};
typedef union bdk_rmapx_jd1_cfg2 bdk_rmapx_jd1_cfg2_t;

static inline uint64_t BDK_RMAPX_JD1_CFG2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_JD1_CFG2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043384010ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043384010ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_JD1_CFG2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_JD1_CFG2(a) bdk_rmapx_jd1_cfg2_t
#define bustype_BDK_RMAPX_JD1_CFG2(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_JD1_CFG2(a) "RMAPX_JD1_CFG2"
#define busnum_BDK_RMAPX_JD1_CFG2(a) (a)
#define arguments_BDK_RMAPX_JD1_CFG2(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_jd1_cfg3
 *
 * RMAP Slot 1 Configuration Register 3
 * This register stores the 4th job configuration word for slot 0.
 */
union bdk_rmapx_jd1_cfg3
{
    uint64_t u;
    struct bdk_rmapx_jd1_cfg3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cfg3_data             : 64; /**< [ 63:  0](R/W) CFG3 Data */
#else /* Word 0 - Little Endian */
        uint64_t cfg3_data             : 64; /**< [ 63:  0](R/W) CFG3 Data */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_jd1_cfg3_s cn; */
};
typedef union bdk_rmapx_jd1_cfg3 bdk_rmapx_jd1_cfg3_t;

static inline uint64_t BDK_RMAPX_JD1_CFG3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_JD1_CFG3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043384018ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043384018ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_JD1_CFG3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_JD1_CFG3(a) bdk_rmapx_jd1_cfg3_t
#define bustype_BDK_RMAPX_JD1_CFG3(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_JD1_CFG3(a) "RMAPX_JD1_CFG3"
#define busnum_BDK_RMAPX_JD1_CFG3(a) (a)
#define arguments_BDK_RMAPX_JD1_CFG3(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_jd1_cfg4
 *
 * RMAP Slot 1 Configuration Register 4
 * This register stores the 5th job configuration word for slot 0.
 */
union bdk_rmapx_jd1_cfg4
{
    uint64_t u;
    struct bdk_rmapx_jd1_cfg4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cfg4_data             : 64; /**< [ 63:  0](R/W) CFG4 Data */
#else /* Word 0 - Little Endian */
        uint64_t cfg4_data             : 64; /**< [ 63:  0](R/W) CFG4 Data */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_jd1_cfg4_s cn; */
};
typedef union bdk_rmapx_jd1_cfg4 bdk_rmapx_jd1_cfg4_t;

static inline uint64_t BDK_RMAPX_JD1_CFG4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_JD1_CFG4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043384020ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043384020ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_JD1_CFG4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_JD1_CFG4(a) bdk_rmapx_jd1_cfg4_t
#define bustype_BDK_RMAPX_JD1_CFG4(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_JD1_CFG4(a) "RMAPX_JD1_CFG4"
#define busnum_BDK_RMAPX_JD1_CFG4(a) (a)
#define arguments_BDK_RMAPX_JD1_CFG4(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_jd1_cfg5
 *
 * RMAP Slot 1 Configuration Register 5
 * This register stores the 6th job configuration word for slot 0.
 */
union bdk_rmapx_jd1_cfg5
{
    uint64_t u;
    struct bdk_rmapx_jd1_cfg5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cfg5_data             : 64; /**< [ 63:  0](R/W) CFG5 Data */
#else /* Word 0 - Little Endian */
        uint64_t cfg5_data             : 64; /**< [ 63:  0](R/W) CFG5 Data */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_jd1_cfg5_s cn; */
};
typedef union bdk_rmapx_jd1_cfg5 bdk_rmapx_jd1_cfg5_t;

static inline uint64_t BDK_RMAPX_JD1_CFG5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_JD1_CFG5(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043384028ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043384028ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_JD1_CFG5", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_JD1_CFG5(a) bdk_rmapx_jd1_cfg5_t
#define bustype_BDK_RMAPX_JD1_CFG5(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_JD1_CFG5(a) "RMAPX_JD1_CFG5"
#define busnum_BDK_RMAPX_JD1_CFG5(a) (a)
#define arguments_BDK_RMAPX_JD1_CFG5(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_jd1_cfg6
 *
 * RMAP Slot 1 Configuration Register 6
 * This register stores the 7th job configuration word for slot 0.
 */
union bdk_rmapx_jd1_cfg6
{
    uint64_t u;
    struct bdk_rmapx_jd1_cfg6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cfg6_data             : 64; /**< [ 63:  0](R/W) CFG6 Data */
#else /* Word 0 - Little Endian */
        uint64_t cfg6_data             : 64; /**< [ 63:  0](R/W) CFG6 Data */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_jd1_cfg6_s cn; */
};
typedef union bdk_rmapx_jd1_cfg6 bdk_rmapx_jd1_cfg6_t;

static inline uint64_t BDK_RMAPX_JD1_CFG6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_JD1_CFG6(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043384030ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043384030ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_JD1_CFG6", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_JD1_CFG6(a) bdk_rmapx_jd1_cfg6_t
#define bustype_BDK_RMAPX_JD1_CFG6(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_JD1_CFG6(a) "RMAPX_JD1_CFG6"
#define busnum_BDK_RMAPX_JD1_CFG6(a) (a)
#define arguments_BDK_RMAPX_JD1_CFG6(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_jd2_cfg0
 *
 * RMAP Slot 2 Configuration Register 0
 * This register stores the 1st job configuration word for slot 0.
 */
union bdk_rmapx_jd2_cfg0
{
    uint64_t u;
    struct bdk_rmapx_jd2_cfg0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t phy_mode              : 1;  /**< [ 63: 63](R/W) LTE/NR Mode. 0 = LTE, 1 = NR. */
        uint64_t cfg0_data             : 63; /**< [ 62:  0](R/W) CFG0 Data */
#else /* Word 0 - Little Endian */
        uint64_t cfg0_data             : 63; /**< [ 62:  0](R/W) CFG0 Data */
        uint64_t phy_mode              : 1;  /**< [ 63: 63](R/W) LTE/NR Mode. 0 = LTE, 1 = NR. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_jd2_cfg0_s cn; */
};
typedef union bdk_rmapx_jd2_cfg0 bdk_rmapx_jd2_cfg0_t;

static inline uint64_t BDK_RMAPX_JD2_CFG0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_JD2_CFG0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043386000ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043386000ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_JD2_CFG0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_JD2_CFG0(a) bdk_rmapx_jd2_cfg0_t
#define bustype_BDK_RMAPX_JD2_CFG0(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_JD2_CFG0(a) "RMAPX_JD2_CFG0"
#define busnum_BDK_RMAPX_JD2_CFG0(a) (a)
#define arguments_BDK_RMAPX_JD2_CFG0(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_jd2_cfg1
 *
 * RMAP Slot 2 Configuration Register 1
 * This register stores the 2nd job configuration word for slot 0.
 */
union bdk_rmapx_jd2_cfg1
{
    uint64_t u;
    struct bdk_rmapx_jd2_cfg1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cfg1_data             : 64; /**< [ 63:  0](R/W) CFG1 Data */
#else /* Word 0 - Little Endian */
        uint64_t cfg1_data             : 64; /**< [ 63:  0](R/W) CFG1 Data */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_jd2_cfg1_s cn; */
};
typedef union bdk_rmapx_jd2_cfg1 bdk_rmapx_jd2_cfg1_t;

static inline uint64_t BDK_RMAPX_JD2_CFG1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_JD2_CFG1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043386008ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043386008ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_JD2_CFG1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_JD2_CFG1(a) bdk_rmapx_jd2_cfg1_t
#define bustype_BDK_RMAPX_JD2_CFG1(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_JD2_CFG1(a) "RMAPX_JD2_CFG1"
#define busnum_BDK_RMAPX_JD2_CFG1(a) (a)
#define arguments_BDK_RMAPX_JD2_CFG1(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_jd2_cfg2
 *
 * RMAP Slot 2 Configuration Register 2
 * This register stores the 3rd job configuration word for slot 0.
 */
union bdk_rmapx_jd2_cfg2
{
    uint64_t u;
    struct bdk_rmapx_jd2_cfg2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cfg2_data             : 64; /**< [ 63:  0](R/W) CFG2 Data */
#else /* Word 0 - Little Endian */
        uint64_t cfg2_data             : 64; /**< [ 63:  0](R/W) CFG2 Data */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_jd2_cfg2_s cn; */
};
typedef union bdk_rmapx_jd2_cfg2 bdk_rmapx_jd2_cfg2_t;

static inline uint64_t BDK_RMAPX_JD2_CFG2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_JD2_CFG2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043386010ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043386010ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_JD2_CFG2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_JD2_CFG2(a) bdk_rmapx_jd2_cfg2_t
#define bustype_BDK_RMAPX_JD2_CFG2(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_JD2_CFG2(a) "RMAPX_JD2_CFG2"
#define busnum_BDK_RMAPX_JD2_CFG2(a) (a)
#define arguments_BDK_RMAPX_JD2_CFG2(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_jd2_cfg3
 *
 * RMAP Slot 2 Configuration Register 3
 * This register stores the 4th job configuration word for slot 0.
 */
union bdk_rmapx_jd2_cfg3
{
    uint64_t u;
    struct bdk_rmapx_jd2_cfg3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cfg3_data             : 64; /**< [ 63:  0](R/W) CFG3 Data */
#else /* Word 0 - Little Endian */
        uint64_t cfg3_data             : 64; /**< [ 63:  0](R/W) CFG3 Data */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_jd2_cfg3_s cn; */
};
typedef union bdk_rmapx_jd2_cfg3 bdk_rmapx_jd2_cfg3_t;

static inline uint64_t BDK_RMAPX_JD2_CFG3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_JD2_CFG3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043386018ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043386018ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_JD2_CFG3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_JD2_CFG3(a) bdk_rmapx_jd2_cfg3_t
#define bustype_BDK_RMAPX_JD2_CFG3(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_JD2_CFG3(a) "RMAPX_JD2_CFG3"
#define busnum_BDK_RMAPX_JD2_CFG3(a) (a)
#define arguments_BDK_RMAPX_JD2_CFG3(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_jd2_cfg4
 *
 * RMAP Slot 2 Configuration Register 4
 * This register stores the 5th job configuration word for slot 0.
 */
union bdk_rmapx_jd2_cfg4
{
    uint64_t u;
    struct bdk_rmapx_jd2_cfg4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cfg4_data             : 64; /**< [ 63:  0](R/W) CFG4 Data */
#else /* Word 0 - Little Endian */
        uint64_t cfg4_data             : 64; /**< [ 63:  0](R/W) CFG4 Data */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_jd2_cfg4_s cn; */
};
typedef union bdk_rmapx_jd2_cfg4 bdk_rmapx_jd2_cfg4_t;

static inline uint64_t BDK_RMAPX_JD2_CFG4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_JD2_CFG4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043386020ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043386020ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_JD2_CFG4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_JD2_CFG4(a) bdk_rmapx_jd2_cfg4_t
#define bustype_BDK_RMAPX_JD2_CFG4(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_JD2_CFG4(a) "RMAPX_JD2_CFG4"
#define busnum_BDK_RMAPX_JD2_CFG4(a) (a)
#define arguments_BDK_RMAPX_JD2_CFG4(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_jd2_cfg5
 *
 * RMAP Slot 2 Configuration Register 5
 * This register stores the 6th job configuration word for slot 0.
 */
union bdk_rmapx_jd2_cfg5
{
    uint64_t u;
    struct bdk_rmapx_jd2_cfg5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cfg5_data             : 64; /**< [ 63:  0](R/W) CFG5 Data */
#else /* Word 0 - Little Endian */
        uint64_t cfg5_data             : 64; /**< [ 63:  0](R/W) CFG5 Data */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_jd2_cfg5_s cn; */
};
typedef union bdk_rmapx_jd2_cfg5 bdk_rmapx_jd2_cfg5_t;

static inline uint64_t BDK_RMAPX_JD2_CFG5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_JD2_CFG5(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043386028ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043386028ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_JD2_CFG5", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_JD2_CFG5(a) bdk_rmapx_jd2_cfg5_t
#define bustype_BDK_RMAPX_JD2_CFG5(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_JD2_CFG5(a) "RMAPX_JD2_CFG5"
#define busnum_BDK_RMAPX_JD2_CFG5(a) (a)
#define arguments_BDK_RMAPX_JD2_CFG5(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_jd2_cfg6
 *
 * RMAP Slot 2 Configuration Register 6
 * This register stores the 7th job configuration word for slot 0.
 */
union bdk_rmapx_jd2_cfg6
{
    uint64_t u;
    struct bdk_rmapx_jd2_cfg6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cfg6_data             : 64; /**< [ 63:  0](R/W) CFG6 Data */
#else /* Word 0 - Little Endian */
        uint64_t cfg6_data             : 64; /**< [ 63:  0](R/W) CFG6 Data */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_jd2_cfg6_s cn; */
};
typedef union bdk_rmapx_jd2_cfg6 bdk_rmapx_jd2_cfg6_t;

static inline uint64_t BDK_RMAPX_JD2_CFG6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_JD2_CFG6(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043386030ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043386030ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_JD2_CFG6", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_JD2_CFG6(a) bdk_rmapx_jd2_cfg6_t
#define bustype_BDK_RMAPX_JD2_CFG6(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_JD2_CFG6(a) "RMAPX_JD2_CFG6"
#define busnum_BDK_RMAPX_JD2_CFG6(a) (a)
#define arguments_BDK_RMAPX_JD2_CFG6(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_scratch
 *
 * INTERNAL: Scratch Register
 */
union bdk_rmapx_scratch
{
    uint64_t u;
    struct bdk_rmapx_scratch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Scratch data */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Scratch data */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_scratch_s cn; */
};
typedef union bdk_rmapx_scratch bdk_rmapx_scratch_t;

static inline uint64_t BDK_RMAPX_SCRATCH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_SCRATCH(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043380080ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043380080ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_SCRATCH", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_SCRATCH(a) bdk_rmapx_scratch_t
#define bustype_BDK_RMAPX_SCRATCH(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_SCRATCH(a) "RMAPX_SCRATCH"
#define busnum_BDK_RMAPX_SCRATCH(a) (a)
#define arguments_BDK_RMAPX_SCRATCH(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_status
 *
 * RMAP Status Register
 */
union bdk_rmapx_status
{
    uint64_t u;
    struct bdk_rmapx_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t ready                 : 1;  /**< [  4:  4](RO/H) Indicates if the RMAP is ready to receive next job. '1' = Ready for next job, '0' = Busy. */
        uint64_t reserved_3            : 1;
        uint64_t status2               : 1;  /**< [  2:  2](RO/H) Indicates if the RMAP is busy processing a job with CONFIGURATION 2.
                                                                 '0' = Ready for new job,
                                                                 '1' = Busy processing. */
        uint64_t status1               : 1;  /**< [  1:  1](RO/H) Indicates if the RMAP is busy processing a job with CONFIGURATION 1.
                                                                 '0' = Ready for new job,
                                                                 '1' = Busy processing. */
        uint64_t status0               : 1;  /**< [  0:  0](RO/H) Indicates if the RMAP is busy processing a job with CONFIGURATION 0.
                                                                 '0' = Ready for new job,
                                                                 '1' = Busy processing. */
#else /* Word 0 - Little Endian */
        uint64_t status0               : 1;  /**< [  0:  0](RO/H) Indicates if the RMAP is busy processing a job with CONFIGURATION 0.
                                                                 '0' = Ready for new job,
                                                                 '1' = Busy processing. */
        uint64_t status1               : 1;  /**< [  1:  1](RO/H) Indicates if the RMAP is busy processing a job with CONFIGURATION 1.
                                                                 '0' = Ready for new job,
                                                                 '1' = Busy processing. */
        uint64_t status2               : 1;  /**< [  2:  2](RO/H) Indicates if the RMAP is busy processing a job with CONFIGURATION 2.
                                                                 '0' = Ready for new job,
                                                                 '1' = Busy processing. */
        uint64_t reserved_3            : 1;
        uint64_t ready                 : 1;  /**< [  4:  4](RO/H) Indicates if the RMAP is ready to receive next job. '1' = Ready for next job, '0' = Busy. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_status_s cn; */
};
typedef union bdk_rmapx_status bdk_rmapx_status_t;

static inline uint64_t BDK_RMAPX_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043380018ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043380018ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_STATUS(a) bdk_rmapx_status_t
#define bustype_BDK_RMAPX_STATUS(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_STATUS(a) "RMAPX_STATUS"
#define busnum_BDK_RMAPX_STATUS(a) (a)
#define arguments_BDK_RMAPX_STATUS(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_tc_config_err_flags
 *
 * Multiplexing, Interleaving and Scrambling Configuration Error Register
 */
union bdk_rmapx_tc_config_err_flags
{
    uint64_t u;
    struct bdk_rmapx_tc_config_err_flags_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t config_err            : 64; /**< [ 63:  0](R/W) TC Config Error */
#else /* Word 0 - Little Endian */
        uint64_t config_err            : 64; /**< [ 63:  0](R/W) TC Config Error */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_tc_config_err_flags_s cn; */
};
typedef union bdk_rmapx_tc_config_err_flags bdk_rmapx_tc_config_err_flags_t;

static inline uint64_t BDK_RMAPX_TC_CONFIG_ERR_FLAGS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_TC_CONFIG_ERR_FLAGS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043381040ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043381040ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_TC_CONFIG_ERR_FLAGS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_TC_CONFIG_ERR_FLAGS(a) bdk_rmapx_tc_config_err_flags_t
#define bustype_BDK_RMAPX_TC_CONFIG_ERR_FLAGS(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_TC_CONFIG_ERR_FLAGS(a) "RMAPX_TC_CONFIG_ERR_FLAGS"
#define busnum_BDK_RMAPX_TC_CONFIG_ERR_FLAGS(a) (a)
#define arguments_BDK_RMAPX_TC_CONFIG_ERR_FLAGS(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_tc_error
 *
 * Multiplexing, Interleaving and Scrambling Error Register
 */
union bdk_rmapx_tc_error
{
    uint64_t u;
    struct bdk_rmapx_tc_error_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t core_err              : 1;  /**< [  8:  8](R/W1C/H) invalid configuration, the block is aborted. See RMAP(0..1)_TC_CONFIG_ERR_FLAGS. */
        uint64_t reserved_4_7          : 4;
        uint64_t ign_rd_acc            : 1;  /**< [  3:  3](R/W1C/H) ignored read access, already one read in progress */
        uint64_t inv_rd_acc            : 1;  /**< [  2:  2](R/W1C/H) invalid read access (out of range address). */
        uint64_t inv_wr_acc            : 1;  /**< [  1:  1](R/W1C/H) invalid write access (out of range address). */
        uint64_t inv_start_task        : 1;  /**< [  0:  0](R/W1C/H) invalid start task (core is already busy processing a task). Error bits,  a bit of "1"
                                                                 indicates an error, write "0" to clear. */
#else /* Word 0 - Little Endian */
        uint64_t inv_start_task        : 1;  /**< [  0:  0](R/W1C/H) invalid start task (core is already busy processing a task). Error bits,  a bit of "1"
                                                                 indicates an error, write "0" to clear. */
        uint64_t inv_wr_acc            : 1;  /**< [  1:  1](R/W1C/H) invalid write access (out of range address). */
        uint64_t inv_rd_acc            : 1;  /**< [  2:  2](R/W1C/H) invalid read access (out of range address). */
        uint64_t ign_rd_acc            : 1;  /**< [  3:  3](R/W1C/H) ignored read access, already one read in progress */
        uint64_t reserved_4_7          : 4;
        uint64_t core_err              : 1;  /**< [  8:  8](R/W1C/H) invalid configuration, the block is aborted. See RMAP(0..1)_TC_CONFIG_ERR_FLAGS. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_tc_error_s cn; */
};
typedef union bdk_rmapx_tc_error bdk_rmapx_tc_error_t;

static inline uint64_t BDK_RMAPX_TC_ERROR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_TC_ERROR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043381038ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043381038ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_TC_ERROR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_TC_ERROR(a) bdk_rmapx_tc_error_t
#define bustype_BDK_RMAPX_TC_ERROR(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_TC_ERROR(a) "RMAPX_TC_ERROR"
#define busnum_BDK_RMAPX_TC_ERROR(a) (a)
#define arguments_BDK_RMAPX_TC_ERROR(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_tc_error_mask
 *
 * Multiplexing, Interleaving and Scrambling Error Mask Register
 */
union bdk_rmapx_tc_error_mask
{
    uint64_t u;
    struct bdk_rmapx_tc_error_mask_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t error_mask            : 32; /**< [ 31:  0](R/W) The contents of RMAP(0..1)_TC_ERROR are masked with this register. When an
                                                                 error occurs, it is reported in RMAP(0..1)_ERROR_SOURCE1[TC_ERROR] only when
                                                                 the corresponding bit in ERROR_MASK is set to one. */
#else /* Word 0 - Little Endian */
        uint64_t error_mask            : 32; /**< [ 31:  0](R/W) The contents of RMAP(0..1)_TC_ERROR are masked with this register. When an
                                                                 error occurs, it is reported in RMAP(0..1)_ERROR_SOURCE1[TC_ERROR] only when
                                                                 the corresponding bit in ERROR_MASK is set to one. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_tc_error_mask_s cn; */
};
typedef union bdk_rmapx_tc_error_mask bdk_rmapx_tc_error_mask_t;

static inline uint64_t BDK_RMAPX_TC_ERROR_MASK(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_TC_ERROR_MASK(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043381030ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043381030ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_TC_ERROR_MASK", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_TC_ERROR_MASK(a) bdk_rmapx_tc_error_mask_t
#define bustype_BDK_RMAPX_TC_ERROR_MASK(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_TC_ERROR_MASK(a) "RMAPX_TC_ERROR_MASK"
#define busnum_BDK_RMAPX_TC_ERROR_MASK(a) (a)
#define arguments_BDK_RMAPX_TC_ERROR_MASK(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_tc_main_control
 *
 * Multiplexing, Interleaving and Scrambling Control Register
 * This register controls pipelining, error checks and clock
 * gating within the multiplexing, interleaving and scrambling sub-block.
 */
union bdk_rmapx_tc_main_control
{
    uint64_t u;
    struct bdk_rmapx_tc_main_control_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t chn_single_task_en    : 1;  /**< [  4:  4](R/W) Write 1 to disable pipelining when adjacent tasks have different
                                                                 channel modes. Note that this degrades throughput. */
        uint64_t phy_single_task_en    : 1;  /**< [  3:  3](R/W) Write 1 to disable pipelining when adjacent tasks have different
                                                                 PHY modes. Note that this degrades throughput. */
        uint64_t single_task_en        : 1;  /**< [  2:  2](R/W) Write 1 to disable all pipelining within the multiplexing,
                                                                 interleaving and scrambling sub-block. Note that this degrades throughput. */
        uint64_t dis_conf_chk          : 1;  /**< [  1:  1](R/W) Write 1 to disable job configuration parameter validation. When
                                                                 parameter validation is disabled, output is unpredictable for invalid
                                                                 configurations. */
        uint64_t clk_en                : 1;  /**< [  0:  0](R/W) Disables internal automatic clock gating when set to 1. */
#else /* Word 0 - Little Endian */
        uint64_t clk_en                : 1;  /**< [  0:  0](R/W) Disables internal automatic clock gating when set to 1. */
        uint64_t dis_conf_chk          : 1;  /**< [  1:  1](R/W) Write 1 to disable job configuration parameter validation. When
                                                                 parameter validation is disabled, output is unpredictable for invalid
                                                                 configurations. */
        uint64_t single_task_en        : 1;  /**< [  2:  2](R/W) Write 1 to disable all pipelining within the multiplexing,
                                                                 interleaving and scrambling sub-block. Note that this degrades throughput. */
        uint64_t phy_single_task_en    : 1;  /**< [  3:  3](R/W) Write 1 to disable pipelining when adjacent tasks have different
                                                                 PHY modes. Note that this degrades throughput. */
        uint64_t chn_single_task_en    : 1;  /**< [  4:  4](R/W) Write 1 to disable pipelining when adjacent tasks have different
                                                                 channel modes. Note that this degrades throughput. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    struct bdk_rmapx_tc_main_control_cn
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t reserved_5_31         : 27;
        uint64_t chn_single_task_en    : 1;  /**< [  4:  4](R/W) Write 1 to disable pipelining when adjacent tasks have different
                                                                 channel modes. Note that this degrades throughput. */
        uint64_t phy_single_task_en    : 1;  /**< [  3:  3](R/W) Write 1 to disable pipelining when adjacent tasks have different
                                                                 PHY modes. Note that this degrades throughput. */
        uint64_t single_task_en        : 1;  /**< [  2:  2](R/W) Write 1 to disable all pipelining within the multiplexing,
                                                                 interleaving and scrambling sub-block. Note that this degrades throughput. */
        uint64_t dis_conf_chk          : 1;  /**< [  1:  1](R/W) Write 1 to disable job configuration parameter validation. When
                                                                 parameter validation is disabled, output is unpredictable for invalid
                                                                 configurations. */
        uint64_t clk_en                : 1;  /**< [  0:  0](R/W) Disables internal automatic clock gating when set to 1. */
#else /* Word 0 - Little Endian */
        uint64_t clk_en                : 1;  /**< [  0:  0](R/W) Disables internal automatic clock gating when set to 1. */
        uint64_t dis_conf_chk          : 1;  /**< [  1:  1](R/W) Write 1 to disable job configuration parameter validation. When
                                                                 parameter validation is disabled, output is unpredictable for invalid
                                                                 configurations. */
        uint64_t single_task_en        : 1;  /**< [  2:  2](R/W) Write 1 to disable all pipelining within the multiplexing,
                                                                 interleaving and scrambling sub-block. Note that this degrades throughput. */
        uint64_t phy_single_task_en    : 1;  /**< [  3:  3](R/W) Write 1 to disable pipelining when adjacent tasks have different
                                                                 PHY modes. Note that this degrades throughput. */
        uint64_t chn_single_task_en    : 1;  /**< [  4:  4](R/W) Write 1 to disable pipelining when adjacent tasks have different
                                                                 channel modes. Note that this degrades throughput. */
        uint64_t reserved_5_31         : 27;
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn;
};
typedef union bdk_rmapx_tc_main_control bdk_rmapx_tc_main_control_t;

static inline uint64_t BDK_RMAPX_TC_MAIN_CONTROL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_TC_MAIN_CONTROL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043381010ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043381010ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_TC_MAIN_CONTROL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_TC_MAIN_CONTROL(a) bdk_rmapx_tc_main_control_t
#define bustype_BDK_RMAPX_TC_MAIN_CONTROL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_TC_MAIN_CONTROL(a) "RMAPX_TC_MAIN_CONTROL"
#define busnum_BDK_RMAPX_TC_MAIN_CONTROL(a) (a)
#define arguments_BDK_RMAPX_TC_MAIN_CONTROL(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_tc_main_reset
 *
 * Multiplexer, Interleaver, and Scrambler Reset Register
 */
union bdk_rmapx_tc_main_reset
{
    uint64_t u;
    struct bdk_rmapx_tc_main_reset_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t soft_reset            : 1;  /**< [  0:  0](R/W) Any write to this bit (either 0 or 1) causes a soft reset of the
                                                                 multiplexing, channel interleaving, and scrambling sub-block.
                                                                 A soft reset of the decoder core is performed if a write to this register is
                                                                 performed whatever the actual value (even if a 0x0) written to this register. The register
                                                                 is automatically de-asserted to low. If no clock is available when a software reset is
                                                                 generated, the idle signal goes low to indicate that a valid ck_work clock is required and
                                                                 the the software reset is postpone until the rising edge of ck_work. */
#else /* Word 0 - Little Endian */
        uint64_t soft_reset            : 1;  /**< [  0:  0](R/W) Any write to this bit (either 0 or 1) causes a soft reset of the
                                                                 multiplexing, channel interleaving, and scrambling sub-block.
                                                                 A soft reset of the decoder core is performed if a write to this register is
                                                                 performed whatever the actual value (even if a 0x0) written to this register. The register
                                                                 is automatically de-asserted to low. If no clock is available when a software reset is
                                                                 generated, the idle signal goes low to indicate that a valid ck_work clock is required and
                                                                 the the software reset is postpone until the rising edge of ck_work. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_tc_main_reset_s cn; */
};
typedef union bdk_rmapx_tc_main_reset bdk_rmapx_tc_main_reset_t;

static inline uint64_t BDK_RMAPX_TC_MAIN_RESET(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_TC_MAIN_RESET(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043381000ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043381000ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_TC_MAIN_RESET", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_TC_MAIN_RESET(a) bdk_rmapx_tc_main_reset_t
#define bustype_BDK_RMAPX_TC_MAIN_RESET(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_TC_MAIN_RESET(a) "RMAPX_TC_MAIN_RESET"
#define busnum_BDK_RMAPX_TC_MAIN_RESET(a) (a)
#define arguments_BDK_RMAPX_TC_MAIN_RESET(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_tc_main_start
 *
 * INTERNAL: TC Start Register
 *
 * TC1860 Main Start Register
 */
union bdk_rmapx_tc_main_start
{
    uint64_t u;
    struct bdk_rmapx_tc_main_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t start                 : 1;  /**< [  0:  0](R/W) Start bit. A write to this address indicates the start of a new task. The
                                                                 configuration
                                                                 written in base address 0x1100 is read for this task. The register is automatically de-
                                                                 asserted to low. */
#else /* Word 0 - Little Endian */
        uint64_t start                 : 1;  /**< [  0:  0](R/W) Start bit. A write to this address indicates the start of a new task. The
                                                                 configuration
                                                                 written in base address 0x1100 is read for this task. The register is automatically de-
                                                                 asserted to low. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_tc_main_start_s cn; */
};
typedef union bdk_rmapx_tc_main_start bdk_rmapx_tc_main_start_t;

static inline uint64_t BDK_RMAPX_TC_MAIN_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_TC_MAIN_START(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=1))
        return 0x87e043381008ll + 0x180000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=1))
        return 0x87e043381008ll + 0x180000ll * ((a) & 0x1);
    __bdk_csr_fatal("RMAPX_TC_MAIN_START", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_TC_MAIN_START(a) bdk_rmapx_tc_main_start_t
#define bustype_BDK_RMAPX_TC_MAIN_START(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_TC_MAIN_START(a) "RMAPX_TC_MAIN_START"
#define busnum_BDK_RMAPX_TC_MAIN_START(a) (a)
#define arguments_BDK_RMAPX_TC_MAIN_START(a) (a),-1,-1,-1

/**
 * Register (RSL) rmap#_tc_status#
 *
 * INTERNAL: TC Status Register
 *
 * TC1860 status register
 */
union bdk_rmapx_tc_statusx
{
    uint64_t u;
    struct bdk_rmapx_tc_statusx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t status                : 64; /**< [ 63:  0](RO) Status bits */
#else /* Word 0 - Little Endian */
        uint64_t status                : 64; /**< [ 63:  0](RO) Status bits */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rmapx_tc_statusx_s cn; */
};
typedef union bdk_rmapx_tc_statusx bdk_rmapx_tc_statusx_t;

static inline uint64_t BDK_RMAPX_TC_STATUSX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RMAPX_TC_STATUSX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=1) && (b<=1)))
        return 0x87e043381020ll + 0x180000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=1) && (b<=1)))
        return 0x87e043381020ll + 0x180000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("RMAPX_TC_STATUSX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RMAPX_TC_STATUSX(a,b) bdk_rmapx_tc_statusx_t
#define bustype_BDK_RMAPX_TC_STATUSX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_RMAPX_TC_STATUSX(a,b) "RMAPX_TC_STATUSX"
#define busnum_BDK_RMAPX_TC_STATUSX(a,b) (a)
#define arguments_BDK_RMAPX_TC_STATUSX(a,b) (a),(b),-1,-1

#endif /* __BDK_CSRS_RMAP_H__ */
