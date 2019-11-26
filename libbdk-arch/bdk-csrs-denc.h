#ifndef __BDK_CSRS_DENC_H__
#define __BDK_CSRS_DENC_H__
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
 * OcteonTX DENC.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Structure denc_common_cfg_s
 *
 * DENC Common Job Configuration Structure
 * This structure defines the format of the first word of the job
 * configuration for all DENC jobs.
 */
union bdk_denc_common_cfg_s
{
    uint64_t u;
    struct bdk_denc_common_cfg_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t dw                    : 8;  /**< [ 39: 32] The number of data words per task. For [TASK_TYPE] = 0x0-0x6, this field
                                                                 indicates the number of 64 bit words of data for each task. The
                                                                 setting depends on the [TASK_TYPE] as follows:
                                                                 * [TASK_TYPE] = 0x1-0x5: [DW] = 2.
                                                                 * [TASK_TYPE] = 0x6: [DW] should be set depending on the number of bits to
                                                                 be encoded.

                                                                 For [TASK_TYPE] = 0x0, this field is ignored. */
        uint64_t reserved_28_31        : 4;
        uint64_t tw                    : 4;  /**< [ 27: 24] The number of configuration words per task.

                                                                 For the following task types, the per-task configuration words should
                                                                 be included as part of the job configuration.
                                                                 * [TASK_TYPE] = 0: [TW] = 8.

                                                                 For the following task types, the per-task configuration words should
                                                                 be included in the read DMA input, with the configuration for each
                                                                 task located immediately before the input data for that task.
                                                                 * [TASK_TYPE] = 0x1, 0x4, or 0x6: [TW] = 6.
                                                                 * [TASK_TYPE] = 0x2: [TW] = 7.
                                                                 * [TASK_TYPE] = 0x3 or 0x5: [TW] = 2. */
        uint64_t reserved_22_23        : 2;
        uint64_t jw                    : 6;  /**< [ 21: 16] The number of general job configuration words remaining in the job
                                                                 descriptor. The value depends on the [TASK_TYPE] as follows:
                                                                 * [TASK_TYPE] = 0x0, 0x1, 0x4, or 0x6: [JW] = 0.
                                                                 * [TASK_TYPE] = 0x2: [JW] = 0x2D.
                                                                 * [TASK_TYPE] = 0x3: [JW] = 0xF.
                                                                 * [TASK_TYPE] = 0x5: [JW] = 0x2. */
        uint64_t reserved_14_15        : 2;
        uint64_t num_tasks             : 6;  /**< [ 13:  8] The number of tasks in the job.

                                                                 * [TASK_TYPE] = 0x0 supports [1,16] tasks per job.
                                                                 * [TASK_TYPE] = 0x1 or 0x4 supports [1,32] tasks per job.
                                                                 * [TASK_TYPE] = 0x3 or 0x5, each DCI is a task, so this
                                                                 field should be the number of DCI for the job.
                                                                 * All other task types (0x2, 0x6) only support one task per job. */
        uint64_t reserved_6_7          : 2;
        uint64_t task_type             : 4;  /**< [  5:  2] The task type.
                                                                 In LTE mode ([MODE]=0):
                                                                 0x0 = PDSCH, PMCH, or PCH.
                                                                 0x1 = PBCH, or E-PDCCH without RE-mapping.
                                                                 0x2 = E-PDCCH with RE-mapping.
                                                                 0x3 = PDCCH.
                                                                 0x4 = R-PDCCH without cross-interleaving.
                                                                 0x5 = R-PDCCH with cross-interleaving.
                                                                 0x6 = Convolutional coding general mode (CC-GM).

                                                                 0x7-0xF = Reserved. */
        uint64_t mode                  : 2;  /**< [  1:  0] PHY mode:
                                                                 0x0 = LTE mode.

                                                                 0x1-0x3 = Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t mode                  : 2;  /**< [  1:  0] PHY mode:
                                                                 0x0 = LTE mode.

                                                                 0x1-0x3 = Reserved. */
        uint64_t task_type             : 4;  /**< [  5:  2] The task type.
                                                                 In LTE mode ([MODE]=0):
                                                                 0x0 = PDSCH, PMCH, or PCH.
                                                                 0x1 = PBCH, or E-PDCCH without RE-mapping.
                                                                 0x2 = E-PDCCH with RE-mapping.
                                                                 0x3 = PDCCH.
                                                                 0x4 = R-PDCCH without cross-interleaving.
                                                                 0x5 = R-PDCCH with cross-interleaving.
                                                                 0x6 = Convolutional coding general mode (CC-GM).

                                                                 0x7-0xF = Reserved. */
        uint64_t reserved_6_7          : 2;
        uint64_t num_tasks             : 6;  /**< [ 13:  8] The number of tasks in the job.

                                                                 * [TASK_TYPE] = 0x0 supports [1,16] tasks per job.
                                                                 * [TASK_TYPE] = 0x1 or 0x4 supports [1,32] tasks per job.
                                                                 * [TASK_TYPE] = 0x3 or 0x5, each DCI is a task, so this
                                                                 field should be the number of DCI for the job.
                                                                 * All other task types (0x2, 0x6) only support one task per job. */
        uint64_t reserved_14_15        : 2;
        uint64_t jw                    : 6;  /**< [ 21: 16] The number of general job configuration words remaining in the job
                                                                 descriptor. The value depends on the [TASK_TYPE] as follows:
                                                                 * [TASK_TYPE] = 0x0, 0x1, 0x4, or 0x6: [JW] = 0.
                                                                 * [TASK_TYPE] = 0x2: [JW] = 0x2D.
                                                                 * [TASK_TYPE] = 0x3: [JW] = 0xF.
                                                                 * [TASK_TYPE] = 0x5: [JW] = 0x2. */
        uint64_t reserved_22_23        : 2;
        uint64_t tw                    : 4;  /**< [ 27: 24] The number of configuration words per task.

                                                                 For the following task types, the per-task configuration words should
                                                                 be included as part of the job configuration.
                                                                 * [TASK_TYPE] = 0: [TW] = 8.

                                                                 For the following task types, the per-task configuration words should
                                                                 be included in the read DMA input, with the configuration for each
                                                                 task located immediately before the input data for that task.
                                                                 * [TASK_TYPE] = 0x1, 0x4, or 0x6: [TW] = 6.
                                                                 * [TASK_TYPE] = 0x2: [TW] = 7.
                                                                 * [TASK_TYPE] = 0x3 or 0x5: [TW] = 2. */
        uint64_t reserved_28_31        : 4;
        uint64_t dw                    : 8;  /**< [ 39: 32] The number of data words per task. For [TASK_TYPE] = 0x0-0x6, this field
                                                                 indicates the number of 64 bit words of data for each task. The
                                                                 setting depends on the [TASK_TYPE] as follows:
                                                                 * [TASK_TYPE] = 0x1-0x5: [DW] = 2.
                                                                 * [TASK_TYPE] = 0x6: [DW] should be set depending on the number of bits to
                                                                 be encoded.

                                                                 For [TASK_TYPE] = 0x0, this field is ignored. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_denc_common_cfg_s_s cn9; */
    /* struct bdk_denc_common_cfg_s_s cnf95xxp1; */
    struct bdk_denc_common_cfg_s_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t dw                    : 8;  /**< [ 39: 32] The number of data words per task. For [TASK_TYPE] = 0x0-0x6, this field
                                                                 indicates the number of 64-bit words of data for each task. The
                                                                 setting depends on the [TASK_TYPE] as follows:
                                                                 * [TASK_TYPE] = 0x1-0x5: [DW] = 0x2.
                                                                 * [TASK_TYPE] = 0x6: [DW] should be set depending on the number of bits to
                                                                 be encoded.

                                                                 For [TASK_TYPE] = 0x0, this field is ignored. */
        uint64_t reserved_28_31        : 4;
        uint64_t tw                    : 4;  /**< [ 27: 24] The number of configuration words per task.

                                                                 For the following task types, the per-task configuration words should
                                                                 be included as part of the job configuration.
                                                                 * [TASK_TYPE] = 0x0: [TW] = 0x8.

                                                                 For the following task types, the per-task configuration words should
                                                                 be included in the read DMA input, with the configuration for each
                                                                 task located immediately before the input data for that task.
                                                                 * [TASK_TYPE] = 0x1, 0x4, or 0x6: [TW] = 0x6.
                                                                 * [TASK_TYPE] = 0x2: [TW] = 0x7.
                                                                 * [TASK_TYPE] = 0x3 or 0x5: [TW] = 0x2. */
        uint64_t reserved_22_23        : 2;
        uint64_t jw                    : 6;  /**< [ 21: 16] The number of general job configuration words remaining in the job
                                                                 descriptor. The value depends on the [TASK_TYPE] as follows:
                                                                 * [TASK_TYPE] = 0x0, 0x1, 0x4, or 0x6: [JW] = 0x0.
                                                                 * [TASK_TYPE] = 0x2: [JW] = 0x2D.
                                                                 * [TASK_TYPE] = 0x3: [JW] = 0xF.
                                                                 * [TASK_TYPE] = 0x5: [JW] = 0x2. */
        uint64_t reserved_14_15        : 2;
        uint64_t num_tasks             : 6;  /**< [ 13:  8] The number of tasks in the job.

                                                                 * [TASK_TYPE] = 0x0 supports [1,16] tasks per job.
                                                                 * [TASK_TYPE] = 0x1 or 0x4 supports [1,32] tasks per job.
                                                                 * [TASK_TYPE] = 0x3 or 0x5, each DCI is a task, so this
                                                                 field should be the number of DCI for the job.
                                                                 * All other task types (0x2, 0x6) only support one task per job. */
        uint64_t reserved_6_7          : 2;
        uint64_t task_type             : 4;  /**< [  5:  2] The task type.
                                                                 In LTE mode ([MODE] = 0):
                                                                 0x0 = PDSCH, PMCH, or PCH.
                                                                 0x1 = PBCH, or E-PDCCH without RE-mapping.
                                                                 0x2 = E-PDCCH with RE-mapping.
                                                                 0x3 = PDCCH.
                                                                 0x4 = R-PDCCH without cross-interleaving.
                                                                 0x5 = R-PDCCH with cross-interleaving.
                                                                 0x6 = Convolutional coding general mode (CC-GM).

                                                                 0x7-0xF = Reserved. */
        uint64_t mode                  : 2;  /**< [  1:  0] PHY mode:
                                                                 0x0 = LTE mode.

                                                                 0x1-0x3 = Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t mode                  : 2;  /**< [  1:  0] PHY mode:
                                                                 0x0 = LTE mode.

                                                                 0x1-0x3 = Reserved. */
        uint64_t task_type             : 4;  /**< [  5:  2] The task type.
                                                                 In LTE mode ([MODE] = 0):
                                                                 0x0 = PDSCH, PMCH, or PCH.
                                                                 0x1 = PBCH, or E-PDCCH without RE-mapping.
                                                                 0x2 = E-PDCCH with RE-mapping.
                                                                 0x3 = PDCCH.
                                                                 0x4 = R-PDCCH without cross-interleaving.
                                                                 0x5 = R-PDCCH with cross-interleaving.
                                                                 0x6 = Convolutional coding general mode (CC-GM).

                                                                 0x7-0xF = Reserved. */
        uint64_t reserved_6_7          : 2;
        uint64_t num_tasks             : 6;  /**< [ 13:  8] The number of tasks in the job.

                                                                 * [TASK_TYPE] = 0x0 supports [1,16] tasks per job.
                                                                 * [TASK_TYPE] = 0x1 or 0x4 supports [1,32] tasks per job.
                                                                 * [TASK_TYPE] = 0x3 or 0x5, each DCI is a task, so this
                                                                 field should be the number of DCI for the job.
                                                                 * All other task types (0x2, 0x6) only support one task per job. */
        uint64_t reserved_14_15        : 2;
        uint64_t jw                    : 6;  /**< [ 21: 16] The number of general job configuration words remaining in the job
                                                                 descriptor. The value depends on the [TASK_TYPE] as follows:
                                                                 * [TASK_TYPE] = 0x0, 0x1, 0x4, or 0x6: [JW] = 0x0.
                                                                 * [TASK_TYPE] = 0x2: [JW] = 0x2D.
                                                                 * [TASK_TYPE] = 0x3: [JW] = 0xF.
                                                                 * [TASK_TYPE] = 0x5: [JW] = 0x2. */
        uint64_t reserved_22_23        : 2;
        uint64_t tw                    : 4;  /**< [ 27: 24] The number of configuration words per task.

                                                                 For the following task types, the per-task configuration words should
                                                                 be included as part of the job configuration.
                                                                 * [TASK_TYPE] = 0x0: [TW] = 0x8.

                                                                 For the following task types, the per-task configuration words should
                                                                 be included in the read DMA input, with the configuration for each
                                                                 task located immediately before the input data for that task.
                                                                 * [TASK_TYPE] = 0x1, 0x4, or 0x6: [TW] = 0x6.
                                                                 * [TASK_TYPE] = 0x2: [TW] = 0x7.
                                                                 * [TASK_TYPE] = 0x3 or 0x5: [TW] = 0x2. */
        uint64_t reserved_28_31        : 4;
        uint64_t dw                    : 8;  /**< [ 39: 32] The number of data words per task. For [TASK_TYPE] = 0x0-0x6, this field
                                                                 indicates the number of 64-bit words of data for each task. The
                                                                 setting depends on the [TASK_TYPE] as follows:
                                                                 * [TASK_TYPE] = 0x1-0x5: [DW] = 0x2.
                                                                 * [TASK_TYPE] = 0x6: [DW] should be set depending on the number of bits to
                                                                 be encoded.

                                                                 For [TASK_TYPE] = 0x0, this field is ignored. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } cnf95xxp2;
    /* struct bdk_denc_common_cfg_s_cnf95xxp2 loki; */
};

/**
 * Structure denc_epdcch_dci_cfg_s
 *
 * DENC E-PDCCH with RE Mapping Per-DCI Configuration Structure
 * This structure defines the per-DCI configuration for E-PDCCH tasks with RE
 * Mapping ([TASK_TYPE] = 0x2).
 */
union bdk_denc_epdcch_dci_cfg_s
{
    uint64_t u[7];
    struct bdk_denc_epdcch_dci_cfg_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_56_63        : 8;
        uint64_t start                 : 4;  /**< [ 55: 52] Resource mapping for this EPDCCH starts from the [START] symbol and
                                                                 continues until the last symbol in the second slot. Valid range is
                                                                 [0:13]. */
        uint64_t reserved_46_51        : 6;
        uint64_t rm_e                  : 14; /**< [ 45: 32] The size of the output after rate matching.

                                                                 The size should be set to 2 x 9 x N_ECCE_EREG x N_EPDCCH_ECCE, where
                                                                 N_ECCE_EREG is the number of EREGs per ECCE (either 4 or 8), and
                                                                 N_EPDCCH_ECCE is the number of ECCEs per EPDCCH.  For example, with 8
                                                                 ECCEs and 4 EREGs per ECCE, [RM_E] = 2 x 9 x 4 x 8 = 576.

                                                                 This size assumes that there are 9 REs per EREG. DENC automatically
                                                                 reduces the rate-matched size accordingly when an EREG has fewer than
                                                                 9 REs. */
        uint64_t crc_msk_en            : 1;  /**< [ 31: 31] When set to 0, no CRC scrambling is performed.

                                                                 When set to 1, the computed CRC is scrambled by XORing it with
                                                                 [CRC_MASK]. This only applies when [BYPS_CRC]=0.

                                                                 Should be set to 1 for PBCH and E-PDCCH use cases. */
        uint64_t byps_crc              : 1;  /**< [ 30: 30] When set to 0, append a 16 bit CRC with polynomial g_CRC16.

                                                                 When set to 1, no CRC is appended. */
        uint64_t reserved_27_29        : 3;
        uint64_t k                     : 10; /**< [ 26: 17] The size (in bits) of the input block to the encoder, including the
                                                                 CRC.

                                                                 Note that if DENC is calculating the CRC ([BYPS_CRC]=0), then the actual
                                                                 read DMA input only contains ([K] - 16) bits. */
        uint64_t enable                : 1;  /**< [ 16: 16] When set to 0, all output bits for this task are forced to zero.
                                                                 When set to 1, enable normal processing. */
        uint64_t reserved_0_15         : 16;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_15         : 16;
        uint64_t enable                : 1;  /**< [ 16: 16] When set to 0, all output bits for this task are forced to zero.
                                                                 When set to 1, enable normal processing. */
        uint64_t k                     : 10; /**< [ 26: 17] The size (in bits) of the input block to the encoder, including the
                                                                 CRC.

                                                                 Note that if DENC is calculating the CRC ([BYPS_CRC]=0), then the actual
                                                                 read DMA input only contains ([K] - 16) bits. */
        uint64_t reserved_27_29        : 3;
        uint64_t byps_crc              : 1;  /**< [ 30: 30] When set to 0, append a 16 bit CRC with polynomial g_CRC16.

                                                                 When set to 1, no CRC is appended. */
        uint64_t crc_msk_en            : 1;  /**< [ 31: 31] When set to 0, no CRC scrambling is performed.

                                                                 When set to 1, the computed CRC is scrambled by XORing it with
                                                                 [CRC_MASK]. This only applies when [BYPS_CRC]=0.

                                                                 Should be set to 1 for PBCH and E-PDCCH use cases. */
        uint64_t rm_e                  : 14; /**< [ 45: 32] The size of the output after rate matching.

                                                                 The size should be set to 2 x 9 x N_ECCE_EREG x N_EPDCCH_ECCE, where
                                                                 N_ECCE_EREG is the number of EREGs per ECCE (either 4 or 8), and
                                                                 N_EPDCCH_ECCE is the number of ECCEs per EPDCCH.  For example, with 8
                                                                 ECCEs and 4 EREGs per ECCE, [RM_E] = 2 x 9 x 4 x 8 = 576.

                                                                 This size assumes that there are 9 REs per EREG. DENC automatically
                                                                 reduces the rate-matched size accordingly when an EREG has fewer than
                                                                 9 REs. */
        uint64_t reserved_46_51        : 6;
        uint64_t start                 : 4;  /**< [ 55: 52] Resource mapping for this EPDCCH starts from the [START] symbol and
                                                                 continues until the last symbol in the second slot. Valid range is
                                                                 [0:13]. */
        uint64_t reserved_56_63        : 8;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_127          : 1;
        uint64_t c_init                : 31; /**< [126: 96] The initialization value, C_init, for the scrambler. */
        uint64_t reserved_94_95        : 2;
        uint64_t gain                  : 14; /**< [ 93: 80] eDCI gain. The gain applied to the modulated symbols. */
        uint64_t crc_msk               : 16; /**< [ 79: 64] CRC mask used to scramble CRC when [CRC_MSK_EN] = 1. */
#else /* Word 1 - Little Endian */
        uint64_t crc_msk               : 16; /**< [ 79: 64] CRC mask used to scramble CRC when [CRC_MSK_EN] = 1. */
        uint64_t gain                  : 14; /**< [ 93: 80] eDCI gain. The gain applied to the modulated symbols. */
        uint64_t reserved_94_95        : 2;
        uint64_t c_init                : 31; /**< [126: 96] The initialization value, C_init, for the scrambler. */
        uint64_t reserved_127          : 1;
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t reserved_144_191      : 48;
        uint64_t edci                  : 16; /**< [143:128] The eDCI number used to tag all modulated symbols associated with this
                                                                 eDCI. */
#else /* Word 2 - Little Endian */
        uint64_t edci                  : 16; /**< [143:128] The eDCI number used to tag all modulated symbols associated with this
                                                                 eDCI. */
        uint64_t reserved_144_191      : 48;
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t ereg_w0               : 64; /**< [255:192] Bits [63:0] of the EREG_indicator array.

                                                                 If EREG_indicator\<k\> = 1, then the k-th EREG can be used by this eDCI,
                                                                 where:

                                                                 _ k = 16j + m,

                                                                 _ j = 0,..., 15 (maximum of 16 RBs per EPDCCH set).

                                                                 _ m = 0,..., 15 (16 EREGs per RB).

                                                                 I.e., bit (16j+m) maps to the m-th EREG in the j-th RB. */
#else /* Word 3 - Little Endian */
        uint64_t ereg_w0               : 64; /**< [255:192] Bits [63:0] of the EREG_indicator array.

                                                                 If EREG_indicator\<k\> = 1, then the k-th EREG can be used by this eDCI,
                                                                 where:

                                                                 _ k = 16j + m,

                                                                 _ j = 0,..., 15 (maximum of 16 RBs per EPDCCH set).

                                                                 _ m = 0,..., 15 (16 EREGs per RB).

                                                                 I.e., bit (16j+m) maps to the m-th EREG in the j-th RB. */
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t ereg_w1               : 64; /**< [319:256] Bits [127:64] of EREG_indicator. See [EREG_W0]. */
#else /* Word 4 - Little Endian */
        uint64_t ereg_w1               : 64; /**< [319:256] Bits [127:64] of EREG_indicator. See [EREG_W0]. */
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t ereg_w2               : 64; /**< [383:320] Bits [191:128] of EREG_indicator. See [EREG_W0]. */
#else /* Word 5 - Little Endian */
        uint64_t ereg_w2               : 64; /**< [383:320] Bits [191:128] of EREG_indicator. See [EREG_W0]. */
#endif /* Word 5 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 6 - Big Endian */
        uint64_t ereg_w3               : 64; /**< [447:384] Bits [255:192] of EREG_indicator. See [EREG_W0]. */
#else /* Word 6 - Little Endian */
        uint64_t ereg_w3               : 64; /**< [447:384] Bits [255:192] of EREG_indicator. See [EREG_W0]. */
#endif /* Word 6 - End */
    } s;
    /* struct bdk_denc_epdcch_dci_cfg_s_s cn9; */
    /* struct bdk_denc_epdcch_dci_cfg_s_s cnf95xxp1; */
    struct bdk_denc_epdcch_dci_cfg_s_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_56_63        : 8;
        uint64_t start                 : 4;  /**< [ 55: 52] Resource mapping for this EPDCCH starts from the [START] symbol and
                                                                 continues until the last symbol in the second slot. Valid range is
                                                                 [0x0, 0xD]. */
        uint64_t reserved_46_51        : 6;
        uint64_t rm_e                  : 14; /**< [ 45: 32] The size of the output after rate matching.

                                                                 The size should be set to 2 x 9 x N_ECCE_EREG x N_EPDCCH_ECCE, where
                                                                 N_ECCE_EREG is the number of EREGs per ECCE (either 4 or 8), and
                                                                 N_EPDCCH_ECCE is the number of ECCEs per EPDCCH.  For example, with 8
                                                                 ECCEs and 4 EREGs per ECCE, [RM_E] = 2 x 9 x 4 x 8 = 0x240.

                                                                 This size assumes that there are 9 REs per EREG. DENC automatically
                                                                 reduces the rate-matched size accordingly when an EREG has fewer than
                                                                 9 REs. */
        uint64_t crc_msk_en            : 1;  /**< [ 31: 31] When set to 0, no CRC scrambling is performed.

                                                                 When set to 1, the computed CRC is scrambled by XORing it with
                                                                 [CRC_MASK]. This only applies when [BYPS_CRC] = 0.

                                                                 Should be set to 1 for PBCH and E-PDCCH use cases. */
        uint64_t byps_crc              : 1;  /**< [ 30: 30] When set to 0, append a 16-bit CRC with polynomial g_CRC16.

                                                                 When set to 1, no CRC is appended. */
        uint64_t reserved_27_29        : 3;
        uint64_t k                     : 10; /**< [ 26: 17] The size (in bits) of the input block to the encoder, including the
                                                                 CRC.

                                                                 Note that if DENC is calculating the CRC ([BYPS_CRC] = 0), then the actual
                                                                 read DMA input only contains ([K] - 16) bits. */
        uint64_t enable                : 1;  /**< [ 16: 16] When set to 0, all output bits for this task are forced to zero.
                                                                 When set to 1, enable normal processing. */
        uint64_t reserved_0_15         : 16;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_15         : 16;
        uint64_t enable                : 1;  /**< [ 16: 16] When set to 0, all output bits for this task are forced to zero.
                                                                 When set to 1, enable normal processing. */
        uint64_t k                     : 10; /**< [ 26: 17] The size (in bits) of the input block to the encoder, including the
                                                                 CRC.

                                                                 Note that if DENC is calculating the CRC ([BYPS_CRC] = 0), then the actual
                                                                 read DMA input only contains ([K] - 16) bits. */
        uint64_t reserved_27_29        : 3;
        uint64_t byps_crc              : 1;  /**< [ 30: 30] When set to 0, append a 16-bit CRC with polynomial g_CRC16.

                                                                 When set to 1, no CRC is appended. */
        uint64_t crc_msk_en            : 1;  /**< [ 31: 31] When set to 0, no CRC scrambling is performed.

                                                                 When set to 1, the computed CRC is scrambled by XORing it with
                                                                 [CRC_MASK]. This only applies when [BYPS_CRC] = 0.

                                                                 Should be set to 1 for PBCH and E-PDCCH use cases. */
        uint64_t rm_e                  : 14; /**< [ 45: 32] The size of the output after rate matching.

                                                                 The size should be set to 2 x 9 x N_ECCE_EREG x N_EPDCCH_ECCE, where
                                                                 N_ECCE_EREG is the number of EREGs per ECCE (either 4 or 8), and
                                                                 N_EPDCCH_ECCE is the number of ECCEs per EPDCCH.  For example, with 8
                                                                 ECCEs and 4 EREGs per ECCE, [RM_E] = 2 x 9 x 4 x 8 = 0x240.

                                                                 This size assumes that there are 9 REs per EREG. DENC automatically
                                                                 reduces the rate-matched size accordingly when an EREG has fewer than
                                                                 9 REs. */
        uint64_t reserved_46_51        : 6;
        uint64_t start                 : 4;  /**< [ 55: 52] Resource mapping for this EPDCCH starts from the [START] symbol and
                                                                 continues until the last symbol in the second slot. Valid range is
                                                                 [0x0, 0xD]. */
        uint64_t reserved_56_63        : 8;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_127          : 1;
        uint64_t c_init                : 31; /**< [126: 96] The initialization value, C_init, for the scrambler. */
        uint64_t reserved_94_95        : 2;
        uint64_t gain                  : 14; /**< [ 93: 80] eDCI gain. The gain applied to the modulated symbols. */
        uint64_t crc_msk               : 16; /**< [ 79: 64] CRC mask used to scramble CRC when [CRC_MSK_EN] = 1. */
#else /* Word 1 - Little Endian */
        uint64_t crc_msk               : 16; /**< [ 79: 64] CRC mask used to scramble CRC when [CRC_MSK_EN] = 1. */
        uint64_t gain                  : 14; /**< [ 93: 80] eDCI gain. The gain applied to the modulated symbols. */
        uint64_t reserved_94_95        : 2;
        uint64_t c_init                : 31; /**< [126: 96] The initialization value, C_init, for the scrambler. */
        uint64_t reserved_127          : 1;
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t reserved_144_191      : 48;
        uint64_t edci                  : 16; /**< [143:128] The eDCI number used to tag all modulated symbols associated with this
                                                                 eDCI. */
#else /* Word 2 - Little Endian */
        uint64_t edci                  : 16; /**< [143:128] The eDCI number used to tag all modulated symbols associated with this
                                                                 eDCI. */
        uint64_t reserved_144_191      : 48;
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t ereg_w0               : 64; /**< [255:192] Bits [63:0] of the EREG_indicator array.

                                                                 If EREG_indicator\<k\> = 1, then the k-th EREG can be used by this eDCI,
                                                                 where:

                                                                 _ k = 16j + m,

                                                                 _ j = 0,..., 15 (maximum of 16 RBs per EPDCCH set).

                                                                 _ m = 0,..., 15 (16 EREGs per RB).

                                                                 I.e., bit (16j+m) maps to the m-th EREG in the j-th RB. */
#else /* Word 3 - Little Endian */
        uint64_t ereg_w0               : 64; /**< [255:192] Bits [63:0] of the EREG_indicator array.

                                                                 If EREG_indicator\<k\> = 1, then the k-th EREG can be used by this eDCI,
                                                                 where:

                                                                 _ k = 16j + m,

                                                                 _ j = 0,..., 15 (maximum of 16 RBs per EPDCCH set).

                                                                 _ m = 0,..., 15 (16 EREGs per RB).

                                                                 I.e., bit (16j+m) maps to the m-th EREG in the j-th RB. */
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t ereg_w1               : 64; /**< [319:256] Bits [127:64] of EREG_indicator. See [EREG_W0]. */
#else /* Word 4 - Little Endian */
        uint64_t ereg_w1               : 64; /**< [319:256] Bits [127:64] of EREG_indicator. See [EREG_W0]. */
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t ereg_w2               : 64; /**< [383:320] Bits [191:128] of EREG_indicator. See [EREG_W0]. */
#else /* Word 5 - Little Endian */
        uint64_t ereg_w2               : 64; /**< [383:320] Bits [191:128] of EREG_indicator. See [EREG_W0]. */
#endif /* Word 5 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 6 - Big Endian */
        uint64_t ereg_w3               : 64; /**< [447:384] Bits [255:192] of EREG_indicator. See [EREG_W0]. */
#else /* Word 6 - Little Endian */
        uint64_t ereg_w3               : 64; /**< [447:384] Bits [255:192] of EREG_indicator. See [EREG_W0]. */
#endif /* Word 6 - End */
    } cnf95xxp2;
    /* struct bdk_denc_epdcch_dci_cfg_s_cnf95xxp2 loki; */
};

/**
 * Structure denc_epdcch_gen_cfg_s
 *
 * DENC E-PDCCH General Configuration Structure
 * This structure defines general configuration parameters for E-PDCCH tasks
 * with RE mapping ([TASK_TYPE] = 0x2).
 *
 * The job configuration section of the job descriptor should include one
 * instance of this structure, followed by 42 x 64-bit words for the RE mask.
 *
 * Note there can only be one task in an E-PDCCH job.
 */
union bdk_denc_epdcch_gen_cfg_s
{
    uint64_t u[3];
    struct bdk_denc_epdcch_gen_cfg_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_62_63        : 2;
        uint64_t aqpsk                 : 14; /**< [ 61: 48] The scaling factor {a}QPSK. Note that each modulated symbol is scaled
                                                                 by its associated DCI gain and then [AQPSK]. */
        uint64_t null_ind              : 16; /**< [ 47: 32] For null modulated symbols, DENC will produce \<0,0\> outputs, tagged
                                                                 with this NULL indicator. */
        uint64_t in_by_o               : 2;  /**< [ 31: 30] Input data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t in_bi_o               : 1;  /**< [ 29: 29] Input data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t nrb                   : 5;  /**< [ 28: 24] The number of RBs to which EPDCCHs of this task with be mapped.  Must be in the range [1,16]. */
        uint64_t reserved_23           : 1;
        uint64_t edci                  : 7;  /**< [ 22: 16] The number of eDCIs within this set to process for this task. Must be
                                                                 in the range [1,64]. */
        uint64_t task_id               : 16; /**< [ 15:  0] Each task in a job should have a unique ID. */
#else /* Word 0 - Little Endian */
        uint64_t task_id               : 16; /**< [ 15:  0] Each task in a job should have a unique ID. */
        uint64_t edci                  : 7;  /**< [ 22: 16] The number of eDCIs within this set to process for this task. Must be
                                                                 in the range [1,64]. */
        uint64_t reserved_23           : 1;
        uint64_t nrb                   : 5;  /**< [ 28: 24] The number of RBs to which EPDCCHs of this task with be mapped.  Must be in the range [1,16]. */
        uint64_t in_bi_o               : 1;  /**< [ 29: 29] Input data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t in_by_o               : 2;  /**< [ 31: 30] Input data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t null_ind              : 16; /**< [ 47: 32] For null modulated symbols, DENC will produce \<0,0\> outputs, tagged
                                                                 with this NULL indicator. */
        uint64_t aqpsk                 : 14; /**< [ 61: 48] The scaling factor {a}QPSK. Note that each modulated symbol is scaled
                                                                 by its associated DCI gain and then [AQPSK]. */
        uint64_t reserved_62_63        : 2;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_114_127      : 14;
        uint64_t pattern_15            : 3;  /**< [113:111] Index into the REG pattern table for RB15. See [PATTERN_0]. */
        uint64_t pattern_14            : 3;  /**< [110:108] Index into the REG pattern table for RB14. See [PATTERN_0]. */
        uint64_t pattern_13            : 3;  /**< [107:105] Index into the REG pattern table for RB13. See [PATTERN_0]. */
        uint64_t pattern_12            : 3;  /**< [104:102] Index into the REG pattern table for RB12. See [PATTERN_0]. */
        uint64_t pattern_11            : 3;  /**< [101: 99] Index into the REG pattern table for RB11. See [PATTERN_0]. */
        uint64_t pattern_10            : 3;  /**< [ 98: 96] Index into the REG pattern table for RB10. See [PATTERN_0]. */
        uint64_t reserved_94_95        : 2;
        uint64_t pattern_9             : 3;  /**< [ 93: 91] Index into the REG pattern table for RB9. See [PATTERN_0]. */
        uint64_t pattern_8             : 3;  /**< [ 90: 88] Index into the REG pattern table for RB8. See [PATTERN_0]. */
        uint64_t pattern_7             : 3;  /**< [ 87: 85] Index into the REG pattern table for RB7. See [PATTERN_0]. */
        uint64_t pattern_6             : 3;  /**< [ 84: 82] Index into the REG pattern table for RB6. See [PATTERN_0]. */
        uint64_t pattern_5             : 3;  /**< [ 81: 79] Index into the REG pattern table for RB5. See [PATTERN_0]. */
        uint64_t pattern_4             : 3;  /**< [ 78: 76] Index into the REG pattern table for RB4. See [PATTERN_0]. */
        uint64_t pattern_3             : 3;  /**< [ 75: 73] Index into the REG pattern table for RB3. See [PATTERN_0]. */
        uint64_t pattern_2             : 3;  /**< [ 72: 70] Index into the REG pattern table for RB2. See [PATTERN_0]. */
        uint64_t pattern_1             : 3;  /**< [ 69: 67] Index into the REG pattern table for RB1. See [PATTERN_0]. */
        uint64_t pattern_0             : 3;  /**< [ 66: 64] Index into the REG pattern table for RB0. The pattern table contains
                                                                 patterns for five different CP modes. By default, the five patterns
                                                                 are:
                                                                 0x0 = Normal CP.
                                                                 0x1 = Special sub-frame 3, 4, 8, 9 with normal CP.
                                                                 0x2 = Special sub-frame 1, 2, 6, 7 with normal CP.
                                                                 0x3 = Extended CP.
                                                                 0x4 = Special sub-frame 1, 2, 3, 5, 6 with extended CP.

                                                                 The pattern table is accessible via DENC(0..1)_TC_STATIC_EPDCCH_REG(0..65). */
#else /* Word 1 - Little Endian */
        uint64_t pattern_0             : 3;  /**< [ 66: 64] Index into the REG pattern table for RB0. The pattern table contains
                                                                 patterns for five different CP modes. By default, the five patterns
                                                                 are:
                                                                 0x0 = Normal CP.
                                                                 0x1 = Special sub-frame 3, 4, 8, 9 with normal CP.
                                                                 0x2 = Special sub-frame 1, 2, 6, 7 with normal CP.
                                                                 0x3 = Extended CP.
                                                                 0x4 = Special sub-frame 1, 2, 3, 5, 6 with extended CP.

                                                                 The pattern table is accessible via DENC(0..1)_TC_STATIC_EPDCCH_REG(0..65). */
        uint64_t pattern_1             : 3;  /**< [ 69: 67] Index into the REG pattern table for RB1. See [PATTERN_0]. */
        uint64_t pattern_2             : 3;  /**< [ 72: 70] Index into the REG pattern table for RB2. See [PATTERN_0]. */
        uint64_t pattern_3             : 3;  /**< [ 75: 73] Index into the REG pattern table for RB3. See [PATTERN_0]. */
        uint64_t pattern_4             : 3;  /**< [ 78: 76] Index into the REG pattern table for RB4. See [PATTERN_0]. */
        uint64_t pattern_5             : 3;  /**< [ 81: 79] Index into the REG pattern table for RB5. See [PATTERN_0]. */
        uint64_t pattern_6             : 3;  /**< [ 84: 82] Index into the REG pattern table for RB6. See [PATTERN_0]. */
        uint64_t pattern_7             : 3;  /**< [ 87: 85] Index into the REG pattern table for RB7. See [PATTERN_0]. */
        uint64_t pattern_8             : 3;  /**< [ 90: 88] Index into the REG pattern table for RB8. See [PATTERN_0]. */
        uint64_t pattern_9             : 3;  /**< [ 93: 91] Index into the REG pattern table for RB9. See [PATTERN_0]. */
        uint64_t reserved_94_95        : 2;
        uint64_t pattern_10            : 3;  /**< [ 98: 96] Index into the REG pattern table for RB10. See [PATTERN_0]. */
        uint64_t pattern_11            : 3;  /**< [101: 99] Index into the REG pattern table for RB11. See [PATTERN_0]. */
        uint64_t pattern_12            : 3;  /**< [104:102] Index into the REG pattern table for RB12. See [PATTERN_0]. */
        uint64_t pattern_13            : 3;  /**< [107:105] Index into the REG pattern table for RB13. See [PATTERN_0]. */
        uint64_t pattern_14            : 3;  /**< [110:108] Index into the REG pattern table for RB14. See [PATTERN_0]. */
        uint64_t pattern_15            : 3;  /**< [113:111] Index into the REG pattern table for RB15. See [PATTERN_0]. */
        uint64_t reserved_114_127      : 14;
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t reserved_128_191      : 64;
#else /* Word 2 - Little Endian */
        uint64_t reserved_128_191      : 64;
#endif /* Word 2 - End */
    } s;
    /* struct bdk_denc_epdcch_gen_cfg_s_s cn9; */
    /* struct bdk_denc_epdcch_gen_cfg_s_s cnf95xxp1; */
    struct bdk_denc_epdcch_gen_cfg_s_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_62_63        : 2;
        uint64_t aqpsk                 : 14; /**< [ 61: 48] The scaling factor {a}QPSK. Note that each modulated symbol is scaled
                                                                 by its associated DCI gain and then [AQPSK]. */
        uint64_t null_ind              : 16; /**< [ 47: 32] For null modulated symbols, DENC will produce \<0,0\> outputs, tagged
                                                                 with this NULL indicator. */
        uint64_t in_by_o               : 2;  /**< [ 31: 30] Input data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t in_bi_o               : 1;  /**< [ 29: 29] Input data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t nrb                   : 5;  /**< [ 28: 24] The number of RBs to which EPDCCHs of this task with be mapped.  Must be in the range [0x1, 0x10]. */
        uint64_t reserved_23           : 1;
        uint64_t edci                  : 7;  /**< [ 22: 16] The number of eDCIs within this set to process for this task. Must be
                                                                 in the range [0x1, 0x40]. */
        uint64_t task_id               : 16; /**< [ 15:  0] Each task in a job should have a unique ID. */
#else /* Word 0 - Little Endian */
        uint64_t task_id               : 16; /**< [ 15:  0] Each task in a job should have a unique ID. */
        uint64_t edci                  : 7;  /**< [ 22: 16] The number of eDCIs within this set to process for this task. Must be
                                                                 in the range [0x1, 0x40]. */
        uint64_t reserved_23           : 1;
        uint64_t nrb                   : 5;  /**< [ 28: 24] The number of RBs to which EPDCCHs of this task with be mapped.  Must be in the range [0x1, 0x10]. */
        uint64_t in_bi_o               : 1;  /**< [ 29: 29] Input data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t in_by_o               : 2;  /**< [ 31: 30] Input data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t null_ind              : 16; /**< [ 47: 32] For null modulated symbols, DENC will produce \<0,0\> outputs, tagged
                                                                 with this NULL indicator. */
        uint64_t aqpsk                 : 14; /**< [ 61: 48] The scaling factor {a}QPSK. Note that each modulated symbol is scaled
                                                                 by its associated DCI gain and then [AQPSK]. */
        uint64_t reserved_62_63        : 2;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_114_127      : 14;
        uint64_t pattern_15            : 3;  /**< [113:111] Index into the REG pattern table for RB15. See [PATTERN_0]. */
        uint64_t pattern_14            : 3;  /**< [110:108] Index into the REG pattern table for RB14. See [PATTERN_0]. */
        uint64_t pattern_13            : 3;  /**< [107:105] Index into the REG pattern table for RB13. See [PATTERN_0]. */
        uint64_t pattern_12            : 3;  /**< [104:102] Index into the REG pattern table for RB12. See [PATTERN_0]. */
        uint64_t pattern_11            : 3;  /**< [101: 99] Index into the REG pattern table for RB11. See [PATTERN_0]. */
        uint64_t pattern_10            : 3;  /**< [ 98: 96] Index into the REG pattern table for RB10. See [PATTERN_0]. */
        uint64_t reserved_94_95        : 2;
        uint64_t pattern_9             : 3;  /**< [ 93: 91] Index into the REG pattern table for RB9. See [PATTERN_0]. */
        uint64_t pattern_8             : 3;  /**< [ 90: 88] Index into the REG pattern table for RB8. See [PATTERN_0]. */
        uint64_t pattern_7             : 3;  /**< [ 87: 85] Index into the REG pattern table for RB7. See [PATTERN_0]. */
        uint64_t pattern_6             : 3;  /**< [ 84: 82] Index into the REG pattern table for RB6. See [PATTERN_0]. */
        uint64_t pattern_5             : 3;  /**< [ 81: 79] Index into the REG pattern table for RB5. See [PATTERN_0]. */
        uint64_t pattern_4             : 3;  /**< [ 78: 76] Index into the REG pattern table for RB4. See [PATTERN_0]. */
        uint64_t pattern_3             : 3;  /**< [ 75: 73] Index into the REG pattern table for RB3. See [PATTERN_0]. */
        uint64_t pattern_2             : 3;  /**< [ 72: 70] Index into the REG pattern table for RB2. See [PATTERN_0]. */
        uint64_t pattern_1             : 3;  /**< [ 69: 67] Index into the REG pattern table for RB1. See [PATTERN_0]. */
        uint64_t pattern_0             : 3;  /**< [ 66: 64] Index into the REG pattern table for RB0. The pattern table contains
                                                                 patterns for five different CP modes. By default, the five patterns
                                                                 are:
                                                                 0x0 = Normal CP.
                                                                 0x1 = Special sub-frame 3, 4, 8, 9 with normal CP.
                                                                 0x2 = Special sub-frame 1, 2, 6, 7 with normal CP.
                                                                 0x3 = Extended CP.
                                                                 0x4 = Special sub-frame 1, 2, 3, 5, 6 with extended CP.

                                                                 The pattern table is accessible via DENC()_TC_STATIC_EPDCCH_REG(0..65). */
#else /* Word 1 - Little Endian */
        uint64_t pattern_0             : 3;  /**< [ 66: 64] Index into the REG pattern table for RB0. The pattern table contains
                                                                 patterns for five different CP modes. By default, the five patterns
                                                                 are:
                                                                 0x0 = Normal CP.
                                                                 0x1 = Special sub-frame 3, 4, 8, 9 with normal CP.
                                                                 0x2 = Special sub-frame 1, 2, 6, 7 with normal CP.
                                                                 0x3 = Extended CP.
                                                                 0x4 = Special sub-frame 1, 2, 3, 5, 6 with extended CP.

                                                                 The pattern table is accessible via DENC()_TC_STATIC_EPDCCH_REG(0..65). */
        uint64_t pattern_1             : 3;  /**< [ 69: 67] Index into the REG pattern table for RB1. See [PATTERN_0]. */
        uint64_t pattern_2             : 3;  /**< [ 72: 70] Index into the REG pattern table for RB2. See [PATTERN_0]. */
        uint64_t pattern_3             : 3;  /**< [ 75: 73] Index into the REG pattern table for RB3. See [PATTERN_0]. */
        uint64_t pattern_4             : 3;  /**< [ 78: 76] Index into the REG pattern table for RB4. See [PATTERN_0]. */
        uint64_t pattern_5             : 3;  /**< [ 81: 79] Index into the REG pattern table for RB5. See [PATTERN_0]. */
        uint64_t pattern_6             : 3;  /**< [ 84: 82] Index into the REG pattern table for RB6. See [PATTERN_0]. */
        uint64_t pattern_7             : 3;  /**< [ 87: 85] Index into the REG pattern table for RB7. See [PATTERN_0]. */
        uint64_t pattern_8             : 3;  /**< [ 90: 88] Index into the REG pattern table for RB8. See [PATTERN_0]. */
        uint64_t pattern_9             : 3;  /**< [ 93: 91] Index into the REG pattern table for RB9. See [PATTERN_0]. */
        uint64_t reserved_94_95        : 2;
        uint64_t pattern_10            : 3;  /**< [ 98: 96] Index into the REG pattern table for RB10. See [PATTERN_0]. */
        uint64_t pattern_11            : 3;  /**< [101: 99] Index into the REG pattern table for RB11. See [PATTERN_0]. */
        uint64_t pattern_12            : 3;  /**< [104:102] Index into the REG pattern table for RB12. See [PATTERN_0]. */
        uint64_t pattern_13            : 3;  /**< [107:105] Index into the REG pattern table for RB13. See [PATTERN_0]. */
        uint64_t pattern_14            : 3;  /**< [110:108] Index into the REG pattern table for RB14. See [PATTERN_0]. */
        uint64_t pattern_15            : 3;  /**< [113:111] Index into the REG pattern table for RB15. See [PATTERN_0]. */
        uint64_t reserved_114_127      : 14;
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t reserved_128_191      : 64;
#else /* Word 2 - Little Endian */
        uint64_t reserved_128_191      : 64;
#endif /* Word 2 - End */
    } cnf95xxp2;
    /* struct bdk_denc_epdcch_gen_cfg_s_cnf95xxp2 loki; */
};

/**
 * Structure denc_generic_task_cfg_s
 *
 * DENC Generic Task Configuration Structure
 * This structure defines the per-task configuration for the following task
 * types:
 * * PBCH/E-PDCCH without RE Mapping ([TASK_TYPE] = 0x1).
 * * R-PDCCH without Cross Interleaving ([TASK_TYPE] = 0x4).
 * * Generic CC tasks ([TASK_TYPE] = 0x6).
 */
union bdk_denc_generic_task_cfg_s
{
    uint64_t u[6];
    struct bdk_denc_generic_task_cfg_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t out_by_o              : 2;  /**< [ 63: 62] Output data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t out_bi_o              : 1;  /**< [ 61: 61] Output data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t in_by_o               : 2;  /**< [ 60: 59] Input data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t in_bi_o               : 1;  /**< [ 58: 58] Input data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t reserved_56_57        : 2;
        uint64_t crc_select            : 3;  /**< [ 55: 53] Select which CRC polynomial to use:
                                                                 0x0: CRC8.
                                                                 0x1: CRC16.
                                                                 0x2: CRC24A.
                                                                 0x3: CRC24B. */
        uint64_t byps_seg              : 1;  /**< [ 52: 52] When set to 0, the output is segmented, with extra padding inserted.
                                                                 See [SEG_PAD] for more details.

                                                                 When set to 1, the output bits are written contiguously with no extra
                                                                 padding inserted to segment the output. */
        uint64_t byps_scram            : 1;  /**< [ 51: 51] When set to 0, perform scrambling on the output.
                                                                 When set to 1, no scrambling is done. */
        uint64_t byps_rm               : 1;  /**< [ 50: 50] When set to 0, perform rate matching.
                                                                 When set to 1, no rate matching, and no scrambling are performed. The
                                                                 output size is 3*[K] bits. */
        uint64_t qm                    : 4;  /**< [ 49: 46] Modulation order:
                                                                 0x1 = BPSK.
                                                                 0x2 = QPSK.
                                                                 0x4 = 16-QAM.
                                                                 0x6 = 64-QAM.
                                                                 0x8 = 256-QAM.
                                                                 0xA = 1024-QAM.

                                                                 Must be set to 2 for PBCH and E-PDCCH. */
        uint64_t rm_e                  : 14; /**< [ 45: 32] The size of the output after rate matching.

                                                                 PBCH:
                                                                 * 1920 for normal CP.
                                                                 * 1728 for extended CP.

                                                                 For E-PDCCH DCI, there must be 72 bits per ECCE.
                                                                 E.g., For 8 ECCEs, [RM_E] = 8 x 72 = 576.

                                                                 For R-PDCCH, any value in [1, 0x3FFF]. */
        uint64_t crc_msk_en            : 1;  /**< [ 31: 31] When set to 0, no CRC scrambling is performed.

                                                                 When set to 1, the computed CRC is scrambled by XORing it with
                                                                 [CRC_MSK]. This only applies when [BYPS_CRC]=0.

                                                                 Should be set to 1 for PBCH and E-PDCCH use cases. */
        uint64_t byps_crc              : 1;  /**< [ 30: 30] When set to 0, append a 16 bit CRC with polynomial g_CRC16.

                                                                 When set to 1, no CRC is appended. */
        uint64_t k                     : 13; /**< [ 29: 17] The size (in bits) of the input block to the encoder, including the
                                                                 CRC.

                                                                 Note that if DENC is calculating the CRC ([BYPS_CRC]=0), then the actual
                                                                 read DMA input only contains ([K] - 16) bits.

                                                                 For PBCH mode, K must be set to 40 bits. */
        uint64_t enable                : 1;  /**< [ 16: 16] When set to 0, all output bits for this task are forced to zero.
                                                                 When set to 1, enable normal processing. */
        uint64_t task_id               : 16; /**< [ 15:  0] Each task in a job should have a unique ID. */
#else /* Word 0 - Little Endian */
        uint64_t task_id               : 16; /**< [ 15:  0] Each task in a job should have a unique ID. */
        uint64_t enable                : 1;  /**< [ 16: 16] When set to 0, all output bits for this task are forced to zero.
                                                                 When set to 1, enable normal processing. */
        uint64_t k                     : 13; /**< [ 29: 17] The size (in bits) of the input block to the encoder, including the
                                                                 CRC.

                                                                 Note that if DENC is calculating the CRC ([BYPS_CRC]=0), then the actual
                                                                 read DMA input only contains ([K] - 16) bits.

                                                                 For PBCH mode, K must be set to 40 bits. */
        uint64_t byps_crc              : 1;  /**< [ 30: 30] When set to 0, append a 16 bit CRC with polynomial g_CRC16.

                                                                 When set to 1, no CRC is appended. */
        uint64_t crc_msk_en            : 1;  /**< [ 31: 31] When set to 0, no CRC scrambling is performed.

                                                                 When set to 1, the computed CRC is scrambled by XORing it with
                                                                 [CRC_MSK]. This only applies when [BYPS_CRC]=0.

                                                                 Should be set to 1 for PBCH and E-PDCCH use cases. */
        uint64_t rm_e                  : 14; /**< [ 45: 32] The size of the output after rate matching.

                                                                 PBCH:
                                                                 * 1920 for normal CP.
                                                                 * 1728 for extended CP.

                                                                 For E-PDCCH DCI, there must be 72 bits per ECCE.
                                                                 E.g., For 8 ECCEs, [RM_E] = 8 x 72 = 576.

                                                                 For R-PDCCH, any value in [1, 0x3FFF]. */
        uint64_t qm                    : 4;  /**< [ 49: 46] Modulation order:
                                                                 0x1 = BPSK.
                                                                 0x2 = QPSK.
                                                                 0x4 = 16-QAM.
                                                                 0x6 = 64-QAM.
                                                                 0x8 = 256-QAM.
                                                                 0xA = 1024-QAM.

                                                                 Must be set to 2 for PBCH and E-PDCCH. */
        uint64_t byps_rm               : 1;  /**< [ 50: 50] When set to 0, perform rate matching.
                                                                 When set to 1, no rate matching, and no scrambling are performed. The
                                                                 output size is 3*[K] bits. */
        uint64_t byps_scram            : 1;  /**< [ 51: 51] When set to 0, perform scrambling on the output.
                                                                 When set to 1, no scrambling is done. */
        uint64_t byps_seg              : 1;  /**< [ 52: 52] When set to 0, the output is segmented, with extra padding inserted.
                                                                 See [SEG_PAD] for more details.

                                                                 When set to 1, the output bits are written contiguously with no extra
                                                                 padding inserted to segment the output. */
        uint64_t crc_select            : 3;  /**< [ 55: 53] Select which CRC polynomial to use:
                                                                 0x0: CRC8.
                                                                 0x1: CRC16.
                                                                 0x2: CRC24A.
                                                                 0x3: CRC24B. */
        uint64_t reserved_56_57        : 2;
        uint64_t in_bi_o               : 1;  /**< [ 58: 58] Input data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t in_by_o               : 2;  /**< [ 60: 59] Input data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t out_bi_o              : 1;  /**< [ 61: 61] Output data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t out_by_o              : 2;  /**< [ 63: 62] Output data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_127          : 1;
        uint64_t c_init                : 31; /**< [126: 96] The initialization value, C_init, for the scrambler. */
        uint64_t symb_align            : 2;  /**< [ 95: 94] Select the aligment and interleaving for output bits.
                                                                 0x0: Bypass mode. Bits are written consecutively, with no per-symbol
                                                                 alignment.
                                                                 0x1: Byte alignment for [QM] \< 10. Every [QM] bits are aligned to a byte
                                                                 boundary.
                                                                 0x2: Interleaved byte alignment for [QM] = 10. For each symbol, the five
                                                                 even bits are packed in one byte, and the five odd bits are packed
                                                                 in the next byte.
                                                                 0x3: Consecutive byte alignment for [QM] = 10. For each symbol, bits 0-4
                                                                 are written in one byte and bits 5-9 are written in the next
                                                                 subsequent byte. */
        uint64_t reserved_88_93        : 6;
        uint64_t crc_msk               : 24; /**< [ 87: 64] CRC mask used to scramble CRC when [CRC_MSK_EN] = 1. */
#else /* Word 1 - Little Endian */
        uint64_t crc_msk               : 24; /**< [ 87: 64] CRC mask used to scramble CRC when [CRC_MSK_EN] = 1. */
        uint64_t reserved_88_93        : 6;
        uint64_t symb_align            : 2;  /**< [ 95: 94] Select the aligment and interleaving for output bits.
                                                                 0x0: Bypass mode. Bits are written consecutively, with no per-symbol
                                                                 alignment.
                                                                 0x1: Byte alignment for [QM] \< 10. Every [QM] bits are aligned to a byte
                                                                 boundary.
                                                                 0x2: Interleaved byte alignment for [QM] = 10. For each symbol, the five
                                                                 even bits are packed in one byte, and the five odd bits are packed
                                                                 in the next byte.
                                                                 0x3: Consecutive byte alignment for [QM] = 10. For each symbol, bits 0-4
                                                                 are written in one byte and bits 5-9 are written in the next
                                                                 subsequent byte. */
        uint64_t c_init                : 31; /**< [126: 96] The initialization value, C_init, for the scrambler. */
        uint64_t reserved_127          : 1;
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t reserved_189_191      : 3;
        uint64_t seg3_syms             : 13; /**< [188:176] See [SEG_PAD] */
        uint64_t reserved_173_175      : 3;
        uint64_t seg2_syms             : 13; /**< [172:160] See [SEG_PAD] */
        uint64_t reserved_157_159      : 3;
        uint64_t seg1_syms             : 13; /**< [156:144] See [SEG_PAD] */
        uint64_t reserved_141_143      : 3;
        uint64_t seg0_syms             : 13; /**< [140:128] See [SEG_PAD] */
#else /* Word 2 - Little Endian */
        uint64_t seg0_syms             : 13; /**< [140:128] See [SEG_PAD] */
        uint64_t reserved_141_143      : 3;
        uint64_t seg1_syms             : 13; /**< [156:144] See [SEG_PAD] */
        uint64_t reserved_157_159      : 3;
        uint64_t seg2_syms             : 13; /**< [172:160] See [SEG_PAD] */
        uint64_t reserved_173_175      : 3;
        uint64_t seg3_syms             : 13; /**< [188:176] See [SEG_PAD] */
        uint64_t reserved_189_191      : 3;
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t reserved_253_255      : 3;
        uint64_t seg7_syms             : 13; /**< [252:240] See [SEG_PAD] */
        uint64_t reserved_237_239      : 3;
        uint64_t seg6_syms             : 13; /**< [236:224] See [SEG_PAD] */
        uint64_t reserved_221_223      : 3;
        uint64_t seg5_syms             : 13; /**< [220:208] See [SEG_PAD] */
        uint64_t reserved_205_207      : 3;
        uint64_t seg4_syms             : 13; /**< [204:192] See [SEG_PAD] */
#else /* Word 3 - Little Endian */
        uint64_t seg4_syms             : 13; /**< [204:192] See [SEG_PAD] */
        uint64_t reserved_205_207      : 3;
        uint64_t seg5_syms             : 13; /**< [220:208] See [SEG_PAD] */
        uint64_t reserved_221_223      : 3;
        uint64_t seg6_syms             : 13; /**< [236:224] See [SEG_PAD] */
        uint64_t reserved_237_239      : 3;
        uint64_t seg7_syms             : 13; /**< [252:240] See [SEG_PAD] */
        uint64_t reserved_253_255      : 3;
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t reserved_317_319      : 3;
        uint64_t seg11_syms            : 13; /**< [316:304] See [SEG_PAD] */
        uint64_t reserved_301_303      : 3;
        uint64_t seg10_syms            : 13; /**< [300:288] See [SEG_PAD] */
        uint64_t reserved_285_287      : 3;
        uint64_t seg9_syms             : 13; /**< [284:272] See [SEG_PAD] */
        uint64_t reserved_269_271      : 3;
        uint64_t seg8_syms             : 13; /**< [268:256] See [SEG_PAD] */
#else /* Word 4 - Little Endian */
        uint64_t seg8_syms             : 13; /**< [268:256] See [SEG_PAD] */
        uint64_t reserved_269_271      : 3;
        uint64_t seg9_syms             : 13; /**< [284:272] See [SEG_PAD] */
        uint64_t reserved_285_287      : 3;
        uint64_t seg10_syms            : 13; /**< [300:288] See [SEG_PAD] */
        uint64_t reserved_301_303      : 3;
        uint64_t seg11_syms            : 13; /**< [316:304] See [SEG_PAD] */
        uint64_t reserved_317_319      : 3;
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t reserved_376_383      : 8;
        uint64_t sym_per_seg           : 24; /**< [375:352] When [SEG_PAD]=1, specifies the total number of symbols in all
                                                                 segments.  Each segment is padded to this size.

                                                                 Note that when [SEG_PAD]=1 and [SYMB_ALIGN]=0, [SYM_PER_SEG] must be
                                                                 set such that ([QM] x [SYM_PER_SEG]) % 128 = 0.

                                                                 When [SEG_PAD]=1 and [SYMB_ALIGN]=1, [SYM_PER_SEG] must be
                                                                 set such that (8 x [SYM_PER_SEG]) % 128 = 0.

                                                                 When [SEG_PAD]=1 and [SYMB_ALIGN]=2 or 3, [SYM_PER_SEG] must be
                                                                 set such that (16 x [SYM_PER_SEG]) % 128 = 0. */
        uint64_t seg_pad               : 1;  /**< [351:351] Segment padding mode:
                                                                 0: Pad each segment to the next multiple of 128-bit words after
                                                                 writing [SEGx_SYMS].
                                                                 1: Pad all segments to contain a total of [SYM_PER_SEG] symbols.
                                                                 See [SYM_PER_SEG] for more details. */
        uint64_t reserved_349_350      : 2;
        uint64_t seg13_syms            : 13; /**< [348:336] See [SEG_PAD] */
        uint64_t reserved_333_335      : 3;
        uint64_t seg12_syms            : 13; /**< [332:320] See [SEG_PAD] */
#else /* Word 5 - Little Endian */
        uint64_t seg12_syms            : 13; /**< [332:320] See [SEG_PAD] */
        uint64_t reserved_333_335      : 3;
        uint64_t seg13_syms            : 13; /**< [348:336] See [SEG_PAD] */
        uint64_t reserved_349_350      : 2;
        uint64_t seg_pad               : 1;  /**< [351:351] Segment padding mode:
                                                                 0: Pad each segment to the next multiple of 128-bit words after
                                                                 writing [SEGx_SYMS].
                                                                 1: Pad all segments to contain a total of [SYM_PER_SEG] symbols.
                                                                 See [SYM_PER_SEG] for more details. */
        uint64_t sym_per_seg           : 24; /**< [375:352] When [SEG_PAD]=1, specifies the total number of symbols in all
                                                                 segments.  Each segment is padded to this size.

                                                                 Note that when [SEG_PAD]=1 and [SYMB_ALIGN]=0, [SYM_PER_SEG] must be
                                                                 set such that ([QM] x [SYM_PER_SEG]) % 128 = 0.

                                                                 When [SEG_PAD]=1 and [SYMB_ALIGN]=1, [SYM_PER_SEG] must be
                                                                 set such that (8 x [SYM_PER_SEG]) % 128 = 0.

                                                                 When [SEG_PAD]=1 and [SYMB_ALIGN]=2 or 3, [SYM_PER_SEG] must be
                                                                 set such that (16 x [SYM_PER_SEG]) % 128 = 0. */
        uint64_t reserved_376_383      : 8;
#endif /* Word 5 - End */
    } s;
    /* struct bdk_denc_generic_task_cfg_s_s cn9; */
    /* struct bdk_denc_generic_task_cfg_s_s cnf95xxp1; */
    struct bdk_denc_generic_task_cfg_s_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t out_by_o              : 2;  /**< [ 63: 62] Output data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t out_bi_o              : 1;  /**< [ 61: 61] Output data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t in_by_o               : 2;  /**< [ 60: 59] Input data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t in_bi_o               : 1;  /**< [ 58: 58] Input data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t reserved_56_57        : 2;
        uint64_t crc_select            : 3;  /**< [ 55: 53] Select which CRC polynomial to use:
                                                                 0x0: CRC8.
                                                                 0x1: CRC16.
                                                                 0x2: CRC24A.
                                                                 0x3: CRC24B. */
        uint64_t byps_seg              : 1;  /**< [ 52: 52] When set to 0, the output is segmented, with extra padding inserted.
                                                                 See [SEG_PAD] for more details.

                                                                 When set to 1, the output bits are written contiguously with no extra
                                                                 padding inserted to segment the output. */
        uint64_t byps_scram            : 1;  /**< [ 51: 51] When set to 0, perform scrambling on the output.
                                                                 When set to 1, no scrambling is done. */
        uint64_t byps_rm               : 1;  /**< [ 50: 50] When set to 0, perform rate matching.
                                                                 When set to 1, no rate matching and no scrambling are performed. The
                                                                 output size is 3 * [K] bits. */
        uint64_t qm                    : 4;  /**< [ 49: 46] Modulation order:
                                                                 0x1 = BPSK.
                                                                 0x2 = QPSK.
                                                                 0x4 = 16-QAM.
                                                                 0x6 = 64-QAM.
                                                                 0x8 = 256-QAM.
                                                                 0xA = 1024-QAM.

                                                                 Must be set to 0x2 for PBCH and E-PDCCH. */
        uint64_t rm_e                  : 14; /**< [ 45: 32] The size of the output after rate matching.

                                                                 PBCH:
                                                                 * 0x780 for normal CP.
                                                                 * 0x6c0 for extended CP.

                                                                 For E-PDCCH DCI, there must be 72 bits per ECCE.
                                                                 E.g., For 8 ECCEs, [RM_E] = 8 x 72 = 0x240.

                                                                 For R-PDCCH, any value in [0x1, 0x3FFF]. */
        uint64_t crc_msk_en            : 1;  /**< [ 31: 31] When set to 0, no CRC scrambling is performed.

                                                                 When set to 1, the computed CRC is scrambled by XORing it with
                                                                 [CRC_MSK]. This only applies when [BYPS_CRC] = 0.

                                                                 Should be set to 1 for PBCH and E-PDCCH use cases. */
        uint64_t byps_crc              : 1;  /**< [ 30: 30] When set to 0, append a 16-bit CRC with polynomial g_CRC16.

                                                                 When set to 1, no CRC is appended. */
        uint64_t k                     : 13; /**< [ 29: 17] The size (in bits) of the input block to the encoder, including the
                                                                 CRC.

                                                                 Note that if DENC is calculating the CRC ([BYPS_CRC] = 0), then the actual
                                                                 read DMA input only contains ([K] - 16) bits.

                                                                 For PBCH mode, [K] must be set to 0x28 bits. */
        uint64_t enable                : 1;  /**< [ 16: 16] When set to 0, all output bits for this task are forced to zero.
                                                                 When set to 1, enable normal processing. */
        uint64_t task_id               : 16; /**< [ 15:  0] Each task in a job should have a unique ID. */
#else /* Word 0 - Little Endian */
        uint64_t task_id               : 16; /**< [ 15:  0] Each task in a job should have a unique ID. */
        uint64_t enable                : 1;  /**< [ 16: 16] When set to 0, all output bits for this task are forced to zero.
                                                                 When set to 1, enable normal processing. */
        uint64_t k                     : 13; /**< [ 29: 17] The size (in bits) of the input block to the encoder, including the
                                                                 CRC.

                                                                 Note that if DENC is calculating the CRC ([BYPS_CRC] = 0), then the actual
                                                                 read DMA input only contains ([K] - 16) bits.

                                                                 For PBCH mode, [K] must be set to 0x28 bits. */
        uint64_t byps_crc              : 1;  /**< [ 30: 30] When set to 0, append a 16-bit CRC with polynomial g_CRC16.

                                                                 When set to 1, no CRC is appended. */
        uint64_t crc_msk_en            : 1;  /**< [ 31: 31] When set to 0, no CRC scrambling is performed.

                                                                 When set to 1, the computed CRC is scrambled by XORing it with
                                                                 [CRC_MSK]. This only applies when [BYPS_CRC] = 0.

                                                                 Should be set to 1 for PBCH and E-PDCCH use cases. */
        uint64_t rm_e                  : 14; /**< [ 45: 32] The size of the output after rate matching.

                                                                 PBCH:
                                                                 * 0x780 for normal CP.
                                                                 * 0x6c0 for extended CP.

                                                                 For E-PDCCH DCI, there must be 72 bits per ECCE.
                                                                 E.g., For 8 ECCEs, [RM_E] = 8 x 72 = 0x240.

                                                                 For R-PDCCH, any value in [0x1, 0x3FFF]. */
        uint64_t qm                    : 4;  /**< [ 49: 46] Modulation order:
                                                                 0x1 = BPSK.
                                                                 0x2 = QPSK.
                                                                 0x4 = 16-QAM.
                                                                 0x6 = 64-QAM.
                                                                 0x8 = 256-QAM.
                                                                 0xA = 1024-QAM.

                                                                 Must be set to 0x2 for PBCH and E-PDCCH. */
        uint64_t byps_rm               : 1;  /**< [ 50: 50] When set to 0, perform rate matching.
                                                                 When set to 1, no rate matching and no scrambling are performed. The
                                                                 output size is 3 * [K] bits. */
        uint64_t byps_scram            : 1;  /**< [ 51: 51] When set to 0, perform scrambling on the output.
                                                                 When set to 1, no scrambling is done. */
        uint64_t byps_seg              : 1;  /**< [ 52: 52] When set to 0, the output is segmented, with extra padding inserted.
                                                                 See [SEG_PAD] for more details.

                                                                 When set to 1, the output bits are written contiguously with no extra
                                                                 padding inserted to segment the output. */
        uint64_t crc_select            : 3;  /**< [ 55: 53] Select which CRC polynomial to use:
                                                                 0x0: CRC8.
                                                                 0x1: CRC16.
                                                                 0x2: CRC24A.
                                                                 0x3: CRC24B. */
        uint64_t reserved_56_57        : 2;
        uint64_t in_bi_o               : 1;  /**< [ 58: 58] Input data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t in_by_o               : 2;  /**< [ 60: 59] Input data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t out_bi_o              : 1;  /**< [ 61: 61] Output data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t out_by_o              : 2;  /**< [ 63: 62] Output data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_127          : 1;
        uint64_t c_init                : 31; /**< [126: 96] The initialization value, C_init, for the scrambler. */
        uint64_t symb_align            : 2;  /**< [ 95: 94] Select the aligment and interleaving for output bits.
                                                                 0x0: Bypass mode. Bits are written consecutively, with no per-symbol
                                                                 alignment.
                                                                 0x1: Byte alignment for [QM] \< 0xA. Every [QM] bits are aligned to a byte
                                                                 boundary.
                                                                 0x2: Interleaved byte alignment for [QM] = 0xA. For each symbol, the five
                                                                 even bits are packed in one byte, and the five odd bits are packed
                                                                 in the next byte.
                                                                 0x3: Consecutive byte alignment for [QM] = 0xA. For each symbol, bits 0-4
                                                                 are written in one byte and bits 5-9 are written in the next byte. */
        uint64_t reserved_88_93        : 6;
        uint64_t crc_msk               : 24; /**< [ 87: 64] CRC mask used to scramble CRC when [CRC_MSK_EN] = 1. */
#else /* Word 1 - Little Endian */
        uint64_t crc_msk               : 24; /**< [ 87: 64] CRC mask used to scramble CRC when [CRC_MSK_EN] = 1. */
        uint64_t reserved_88_93        : 6;
        uint64_t symb_align            : 2;  /**< [ 95: 94] Select the aligment and interleaving for output bits.
                                                                 0x0: Bypass mode. Bits are written consecutively, with no per-symbol
                                                                 alignment.
                                                                 0x1: Byte alignment for [QM] \< 0xA. Every [QM] bits are aligned to a byte
                                                                 boundary.
                                                                 0x2: Interleaved byte alignment for [QM] = 0xA. For each symbol, the five
                                                                 even bits are packed in one byte, and the five odd bits are packed
                                                                 in the next byte.
                                                                 0x3: Consecutive byte alignment for [QM] = 0xA. For each symbol, bits 0-4
                                                                 are written in one byte and bits 5-9 are written in the next byte. */
        uint64_t c_init                : 31; /**< [126: 96] The initialization value, C_init, for the scrambler. */
        uint64_t reserved_127          : 1;
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t reserved_189_191      : 3;
        uint64_t seg3_syms             : 13; /**< [188:176] See [SEG_PAD] */
        uint64_t reserved_173_175      : 3;
        uint64_t seg2_syms             : 13; /**< [172:160] See [SEG_PAD] */
        uint64_t reserved_157_159      : 3;
        uint64_t seg1_syms             : 13; /**< [156:144] See [SEG_PAD] */
        uint64_t reserved_141_143      : 3;
        uint64_t seg0_syms             : 13; /**< [140:128] See [SEG_PAD] */
#else /* Word 2 - Little Endian */
        uint64_t seg0_syms             : 13; /**< [140:128] See [SEG_PAD] */
        uint64_t reserved_141_143      : 3;
        uint64_t seg1_syms             : 13; /**< [156:144] See [SEG_PAD] */
        uint64_t reserved_157_159      : 3;
        uint64_t seg2_syms             : 13; /**< [172:160] See [SEG_PAD] */
        uint64_t reserved_173_175      : 3;
        uint64_t seg3_syms             : 13; /**< [188:176] See [SEG_PAD] */
        uint64_t reserved_189_191      : 3;
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t reserved_253_255      : 3;
        uint64_t seg7_syms             : 13; /**< [252:240] See [SEG_PAD] */
        uint64_t reserved_237_239      : 3;
        uint64_t seg6_syms             : 13; /**< [236:224] See [SEG_PAD] */
        uint64_t reserved_221_223      : 3;
        uint64_t seg5_syms             : 13; /**< [220:208] See [SEG_PAD] */
        uint64_t reserved_205_207      : 3;
        uint64_t seg4_syms             : 13; /**< [204:192] See [SEG_PAD] */
#else /* Word 3 - Little Endian */
        uint64_t seg4_syms             : 13; /**< [204:192] See [SEG_PAD] */
        uint64_t reserved_205_207      : 3;
        uint64_t seg5_syms             : 13; /**< [220:208] See [SEG_PAD] */
        uint64_t reserved_221_223      : 3;
        uint64_t seg6_syms             : 13; /**< [236:224] See [SEG_PAD] */
        uint64_t reserved_237_239      : 3;
        uint64_t seg7_syms             : 13; /**< [252:240] See [SEG_PAD] */
        uint64_t reserved_253_255      : 3;
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t reserved_317_319      : 3;
        uint64_t seg11_syms            : 13; /**< [316:304] See [SEG_PAD] */
        uint64_t reserved_301_303      : 3;
        uint64_t seg10_syms            : 13; /**< [300:288] See [SEG_PAD] */
        uint64_t reserved_285_287      : 3;
        uint64_t seg9_syms             : 13; /**< [284:272] See [SEG_PAD] */
        uint64_t reserved_269_271      : 3;
        uint64_t seg8_syms             : 13; /**< [268:256] See [SEG_PAD] */
#else /* Word 4 - Little Endian */
        uint64_t seg8_syms             : 13; /**< [268:256] See [SEG_PAD] */
        uint64_t reserved_269_271      : 3;
        uint64_t seg9_syms             : 13; /**< [284:272] See [SEG_PAD] */
        uint64_t reserved_285_287      : 3;
        uint64_t seg10_syms            : 13; /**< [300:288] See [SEG_PAD] */
        uint64_t reserved_301_303      : 3;
        uint64_t seg11_syms            : 13; /**< [316:304] See [SEG_PAD] */
        uint64_t reserved_317_319      : 3;
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t reserved_376_383      : 8;
        uint64_t sym_per_seg           : 24; /**< [375:352] When [SEG_PAD] = 1, specifies the total number of symbols in all
                                                                 segments.  Each segment is padded to this size.

                                                                 Note that when [SEG_PAD] = 1 and [SYMB_ALIGN] = 0x0, [SYM_PER_SEG] must be
                                                                 set such that ([QM] x [SYM_PER_SEG]) % 128 = 0.

                                                                 When [SEG_PAD] = 1 and [SYMB_ALIGN] = 0x1, [SYM_PER_SEG] must be
                                                                 set such that (8 x [SYM_PER_SEG]) % 128 = 0.

                                                                 When [SEG_PAD] = 1 and [SYMB_ALIGN] = 0x2 or 0x3, [SYM_PER_SEG] must be
                                                                 set such that (16 x [SYM_PER_SEG]) % 128 = 0. */
        uint64_t seg_pad               : 1;  /**< [351:351] Segment padding mode:
                                                                 0: Pad each segment to the next multiple of 128-bit words after
                                                                 writing [SEGx_SYMS].
                                                                 1: Pad all segments to contain a total of [SYM_PER_SEG] symbols.
                                                                 See [SYM_PER_SEG] for more details. */
        uint64_t reserved_349_350      : 2;
        uint64_t seg13_syms            : 13; /**< [348:336] See [SEG_PAD] */
        uint64_t reserved_333_335      : 3;
        uint64_t seg12_syms            : 13; /**< [332:320] See [SEG_PAD] */
#else /* Word 5 - Little Endian */
        uint64_t seg12_syms            : 13; /**< [332:320] See [SEG_PAD] */
        uint64_t reserved_333_335      : 3;
        uint64_t seg13_syms            : 13; /**< [348:336] See [SEG_PAD] */
        uint64_t reserved_349_350      : 2;
        uint64_t seg_pad               : 1;  /**< [351:351] Segment padding mode:
                                                                 0: Pad each segment to the next multiple of 128-bit words after
                                                                 writing [SEGx_SYMS].
                                                                 1: Pad all segments to contain a total of [SYM_PER_SEG] symbols.
                                                                 See [SYM_PER_SEG] for more details. */
        uint64_t sym_per_seg           : 24; /**< [375:352] When [SEG_PAD] = 1, specifies the total number of symbols in all
                                                                 segments.  Each segment is padded to this size.

                                                                 Note that when [SEG_PAD] = 1 and [SYMB_ALIGN] = 0x0, [SYM_PER_SEG] must be
                                                                 set such that ([QM] x [SYM_PER_SEG]) % 128 = 0.

                                                                 When [SEG_PAD] = 1 and [SYMB_ALIGN] = 0x1, [SYM_PER_SEG] must be
                                                                 set such that (8 x [SYM_PER_SEG]) % 128 = 0.

                                                                 When [SEG_PAD] = 1 and [SYMB_ALIGN] = 0x2 or 0x3, [SYM_PER_SEG] must be
                                                                 set such that (16 x [SYM_PER_SEG]) % 128 = 0. */
        uint64_t reserved_376_383      : 8;
#endif /* Word 5 - End */
    } cnf95xxp2;
    /* struct bdk_denc_generic_task_cfg_s_cnf95xxp2 loki; */
};

/**
 * Structure denc_pdcch_dci_cfg_s
 *
 * DENC PDCCH Per-DCI Configuration Structure
 * This structure defines the per-DCI configuration for the following task
 * types:
 * * PDCCH ([TASK_TYPE] = 0x3)
 * * R-PDCCH with Cross Interleaving ([TASK_TYPE] = 0x5)
 */
union bdk_denc_pdcch_dci_cfg_s
{
    uint64_t u[2];
    struct bdk_denc_pdcch_dci_cfg_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cce                   : 7;  /**< [ 63: 57] CCE index. Valid range is [0,87]. */
        uint64_t reserved_46_56        : 11;
        uint64_t rm_e                  : 14; /**< [ 45: 32] The size of the output after rate matching.

                                                                 For PDCCH DCI, there must be 72 bits per CCE.
                                                                 E.g., For 8 CCEs, [RM_E] = 8 x 72 = 576.

                                                                 For R-PDCCH, any value in [1, 0x3FFF]. */
        uint64_t crc_msk_en            : 1;  /**< [ 31: 31] When set to 0, no CRC scrambling is performed.

                                                                 When set to 1, the computed CRC is scrambled by XORing it with
                                                                 [CRC_MASK]. This only applies when [BYPS_CRC]=0.

                                                                 Should be set to 1 for PBCH and E-PDCCH use cases. */
        uint64_t byps_crc              : 1;  /**< [ 30: 30] When set to 0, append a 16 bit CRC with polynomial g_CRC16.

                                                                 When set to 1, no CRC is appended. */
        uint64_t reserved_27_29        : 3;
        uint64_t k                     : 10; /**< [ 26: 17] The size (in bits) of the input block to the encoder, including the
                                                                 CRC.

                                                                 Note that if DENC is calculating the CRC ([BYPS_CRC]=0), then the actual
                                                                 read DMA input only contains ([K] - 16) bits. */
        uint64_t enable                : 1;  /**< [ 16: 16] When set to 0, all output bits for this task are forced to zero.
                                                                 When set to 1, enable normal processing. */
        uint64_t reserved_0_15         : 16;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_15         : 16;
        uint64_t enable                : 1;  /**< [ 16: 16] When set to 0, all output bits for this task are forced to zero.
                                                                 When set to 1, enable normal processing. */
        uint64_t k                     : 10; /**< [ 26: 17] The size (in bits) of the input block to the encoder, including the
                                                                 CRC.

                                                                 Note that if DENC is calculating the CRC ([BYPS_CRC]=0), then the actual
                                                                 read DMA input only contains ([K] - 16) bits. */
        uint64_t reserved_27_29        : 3;
        uint64_t byps_crc              : 1;  /**< [ 30: 30] When set to 0, append a 16 bit CRC with polynomial g_CRC16.

                                                                 When set to 1, no CRC is appended. */
        uint64_t crc_msk_en            : 1;  /**< [ 31: 31] When set to 0, no CRC scrambling is performed.

                                                                 When set to 1, the computed CRC is scrambled by XORing it with
                                                                 [CRC_MASK]. This only applies when [BYPS_CRC]=0.

                                                                 Should be set to 1 for PBCH and E-PDCCH use cases. */
        uint64_t rm_e                  : 14; /**< [ 45: 32] The size of the output after rate matching.

                                                                 For PDCCH DCI, there must be 72 bits per CCE.
                                                                 E.g., For 8 CCEs, [RM_E] = 8 x 72 = 576.

                                                                 For R-PDCCH, any value in [1, 0x3FFF]. */
        uint64_t reserved_46_56        : 11;
        uint64_t cce                   : 7;  /**< [ 63: 57] CCE index. Valid range is [0,87]. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_94_127       : 34;
        uint64_t gain                  : 14; /**< [ 93: 80] DCI gain. The gain applied to the modulated symbols for this DCI. */
        uint64_t crc_msk               : 16; /**< [ 79: 64] CRC mask used to scramble CRC when [CRC_MSK_EN] = 1. */
#else /* Word 1 - Little Endian */
        uint64_t crc_msk               : 16; /**< [ 79: 64] CRC mask used to scramble CRC when [CRC_MSK_EN] = 1. */
        uint64_t gain                  : 14; /**< [ 93: 80] DCI gain. The gain applied to the modulated symbols for this DCI. */
        uint64_t reserved_94_127       : 34;
#endif /* Word 1 - End */
    } s;
    /* struct bdk_denc_pdcch_dci_cfg_s_s cn9; */
    /* struct bdk_denc_pdcch_dci_cfg_s_s cnf95xxp1; */
    struct bdk_denc_pdcch_dci_cfg_s_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cce                   : 7;  /**< [ 63: 57] CCE index. Valid range is [0x0, 0x57]. */
        uint64_t reserved_46_56        : 11;
        uint64_t rm_e                  : 14; /**< [ 45: 32] The size of the output after rate matching.

                                                                 For PDCCH DCI, there must be 72 bits per CCE.
                                                                 E.g., For 8 CCEs, [RM_E] = 8 x 72 = 0x240.

                                                                 For R-PDCCH, any value in [0x1, 0x3FFF]. */
        uint64_t crc_msk_en            : 1;  /**< [ 31: 31] When set to 0, no CRC scrambling is performed.

                                                                 When set to 1, the computed CRC is scrambled by XORing it with
                                                                 [CRC_MASK]. This only applies when [BYPS_CRC] = 0.

                                                                 Should be set to 1 for PBCH and E-PDCCH use cases. */
        uint64_t byps_crc              : 1;  /**< [ 30: 30] When set to 0, append a 16-bit CRC with polynomial g_CRC16.

                                                                 When set to 1, no CRC is appended. */
        uint64_t reserved_27_29        : 3;
        uint64_t k                     : 10; /**< [ 26: 17] The size (in bits) of the input block to the encoder, including the
                                                                 CRC.

                                                                 Note that if DENC is calculating the CRC ([BYPS_CRC] = 0), then the actual
                                                                 read DMA input only contains ([K] - 16) bits. */
        uint64_t enable                : 1;  /**< [ 16: 16] When set to 0, all output bits for this task are forced to zero.
                                                                 When set to 1, enable normal processing. */
        uint64_t reserved_0_15         : 16;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_15         : 16;
        uint64_t enable                : 1;  /**< [ 16: 16] When set to 0, all output bits for this task are forced to zero.
                                                                 When set to 1, enable normal processing. */
        uint64_t k                     : 10; /**< [ 26: 17] The size (in bits) of the input block to the encoder, including the
                                                                 CRC.

                                                                 Note that if DENC is calculating the CRC ([BYPS_CRC] = 0), then the actual
                                                                 read DMA input only contains ([K] - 16) bits. */
        uint64_t reserved_27_29        : 3;
        uint64_t byps_crc              : 1;  /**< [ 30: 30] When set to 0, append a 16-bit CRC with polynomial g_CRC16.

                                                                 When set to 1, no CRC is appended. */
        uint64_t crc_msk_en            : 1;  /**< [ 31: 31] When set to 0, no CRC scrambling is performed.

                                                                 When set to 1, the computed CRC is scrambled by XORing it with
                                                                 [CRC_MASK]. This only applies when [BYPS_CRC] = 0.

                                                                 Should be set to 1 for PBCH and E-PDCCH use cases. */
        uint64_t rm_e                  : 14; /**< [ 45: 32] The size of the output after rate matching.

                                                                 For PDCCH DCI, there must be 72 bits per CCE.
                                                                 E.g., For 8 CCEs, [RM_E] = 8 x 72 = 0x240.

                                                                 For R-PDCCH, any value in [0x1, 0x3FFF]. */
        uint64_t reserved_46_56        : 11;
        uint64_t cce                   : 7;  /**< [ 63: 57] CCE index. Valid range is [0x0, 0x57]. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_94_127       : 34;
        uint64_t gain                  : 14; /**< [ 93: 80] DCI gain. The gain applied to the modulated symbols for this DCI. */
        uint64_t crc_msk               : 16; /**< [ 79: 64] CRC mask used to scramble CRC when [CRC_MSK_EN] = 1. */
#else /* Word 1 - Little Endian */
        uint64_t crc_msk               : 16; /**< [ 79: 64] CRC mask used to scramble CRC when [CRC_MSK_EN] = 1. */
        uint64_t gain                  : 14; /**< [ 93: 80] DCI gain. The gain applied to the modulated symbols for this DCI. */
        uint64_t reserved_94_127       : 34;
#endif /* Word 1 - End */
    } cnf95xxp2;
    /* struct bdk_denc_pdcch_dci_cfg_s_cnf95xxp2 loki; */
};

/**
 * Structure denc_pdcch_gen_cfg_s
 *
 * DENC PDCCH General Configuration Structure
 * This structure defines general configuration parameters for PDCCH tasks
 * ([TASK_TYPE] = 0x3).
 *
 * The job configuration section of the job descriptor should include one
 * instance of this structure.
 *
 * Note there can only be one task in a PDCCH job.
 */
union bdk_denc_pdcch_gen_cfg_s
{
    uint64_t u[15];
    struct bdk_denc_pdcch_gen_cfg_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_63           : 1;
        uint64_t c_init                : 31; /**< [ 62: 32] The initialization value C_init for the scrambler. */
        uint64_t reserved_30_31        : 2;
        uint64_t byps_pdcch            : 1;  /**< [ 29: 29] Must be set to 0.
                                                                 Internal:
                                                                 When set to 1, encoded bits are streamed out in the same order DCIs
                                                                 have been fed in, and other PDCCH functionality is bypassed. */
        uint64_t reg_pat               : 5;  /**< [ 28: 24] Index into the REG order pattern table. Valid range is [0,8]. */
        uint64_t dci                   : 8;  /**< [ 23: 16] The number of DCI to multiplex. Valid range is [1,88]. */
        uint64_t task_id               : 16; /**< [ 15:  0] Each task in a job should have a unique ID. */
#else /* Word 0 - Little Endian */
        uint64_t task_id               : 16; /**< [ 15:  0] Each task in a job should have a unique ID. */
        uint64_t dci                   : 8;  /**< [ 23: 16] The number of DCI to multiplex. Valid range is [1,88]. */
        uint64_t reg_pat               : 5;  /**< [ 28: 24] Index into the REG order pattern table. Valid range is [0,8]. */
        uint64_t byps_pdcch            : 1;  /**< [ 29: 29] Must be set to 0.
                                                                 Internal:
                                                                 When set to 1, encoded bits are streamed out in the same order DCIs
                                                                 have been fed in, and other PDCCH functionality is bypassed. */
        uint64_t reserved_30_31        : 2;
        uint64_t c_init                : 31; /**< [ 62: 32] The initialization value C_init for the scrambler. */
        uint64_t reserved_63           : 1;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_122_127      : 6;
        uint64_t in_by_o               : 2;  /**< [121:120] Input data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t in_bi_o               : 1;  /**< [119:119] Input data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t nrb                   : 7;  /**< [118:112] The number of RBs to map PDCCH to. This is the N^DL_RB parameter in
                                                                 3GPP TS 36.211. Valid values are {6, 15, 25, 50, 75, 100}. */
        uint64_t reserved_110_111      : 2;
        uint64_t aqpsk                 : 14; /**< [109: 96] The scaling factor {a}QPSK. Note that each modulated symbol is scaled
                                                                 by its associated DCI gain and then AQPSK. */
        uint64_t pcell                 : 16; /**< [ 95: 80] The physical cell ID. This value is used during cyclic shifting. */
        uint64_t reserved_77_79        : 3;
        uint64_t byps_map              : 1;  /**< [ 76: 76] When set to 0, perform resource mapping.

                                                                 When set to 1, bypass resource element mapping. I/Q samples are output
                                                                 directly from modulation and gain scaling stage, and all symbols are
                                                                 written to thread 0. */
        uint64_t quad                  : 12; /**< [ 75: 64] The number of quadruplet symbols. */
#else /* Word 1 - Little Endian */
        uint64_t quad                  : 12; /**< [ 75: 64] The number of quadruplet symbols. */
        uint64_t byps_map              : 1;  /**< [ 76: 76] When set to 0, perform resource mapping.

                                                                 When set to 1, bypass resource element mapping. I/Q samples are output
                                                                 directly from modulation and gain scaling stage, and all symbols are
                                                                 written to thread 0. */
        uint64_t reserved_77_79        : 3;
        uint64_t pcell                 : 16; /**< [ 95: 80] The physical cell ID. This value is used during cyclic shifting. */
        uint64_t aqpsk                 : 14; /**< [109: 96] The scaling factor {a}QPSK. Note that each modulated symbol is scaled
                                                                 by its associated DCI gain and then AQPSK. */
        uint64_t reserved_110_111      : 2;
        uint64_t nrb                   : 7;  /**< [118:112] The number of RBs to map PDCCH to. This is the N^DL_RB parameter in
                                                                 3GPP TS 36.211. Valid values are {6, 15, 25, 50, 75, 100}. */
        uint64_t in_bi_o               : 1;  /**< [119:119] Input data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t in_by_o               : 2;  /**< [121:120] Input data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t reserved_122_127      : 6;
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t reg_mask0             : 64; /**< [191:128] Bits 0 to 63 of the REG mask for PDCCH mapping.

                                                                 REG_MASK\<M*k+j\> specifies the REG mask for resource element group
                                                                 (REG) M*k+j, where

                                                                 _ M is the number of REGs per RB,

                                                                 _ 0 \<= k \< [NRB], and

                                                                 _ 0 \<= j \<= M-1.

                                                                 If a bit is set to 1, then the corresponding REG is occupied by PCFICH
                                                                 or PHICH and shall not be used by PDCCH. */
#else /* Word 2 - Little Endian */
        uint64_t reg_mask0             : 64; /**< [191:128] Bits 0 to 63 of the REG mask for PDCCH mapping.

                                                                 REG_MASK\<M*k+j\> specifies the REG mask for resource element group
                                                                 (REG) M*k+j, where

                                                                 _ M is the number of REGs per RB,

                                                                 _ 0 \<= k \< [NRB], and

                                                                 _ 0 \<= j \<= M-1.

                                                                 If a bit is set to 1, then the corresponding REG is occupied by PCFICH
                                                                 or PHICH and shall not be used by PDCCH. */
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t reg_mask1             : 64; /**< [255:192] Bits 64 to 127 of REG_MASK. See [REG_MASK0]. */
#else /* Word 3 - Little Endian */
        uint64_t reg_mask1             : 64; /**< [255:192] Bits 64 to 127 of REG_MASK. See [REG_MASK0]. */
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t reg_mask2             : 64; /**< [319:256] Bits 128 to 191 of REG_MASK. See [REG_MASK0]. */
#else /* Word 4 - Little Endian */
        uint64_t reg_mask2             : 64; /**< [319:256] Bits 128 to 191 of REG_MASK. See [REG_MASK0]. */
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t reg_mask3             : 64; /**< [383:320] Bits 192 to 255 of REG_MASK. See [REG_MASK0]. */
#else /* Word 5 - Little Endian */
        uint64_t reg_mask3             : 64; /**< [383:320] Bits 192 to 255 of REG_MASK. See [REG_MASK0]. */
#endif /* Word 5 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 6 - Big Endian */
        uint64_t reg_mask4             : 64; /**< [447:384] Bits 256 to 319 of REG_MASK. See [REG_MASK0]. */
#else /* Word 6 - Little Endian */
        uint64_t reg_mask4             : 64; /**< [447:384] Bits 256 to 319 of REG_MASK. See [REG_MASK0]. */
#endif /* Word 6 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 7 - Big Endian */
        uint64_t reg_mask5             : 64; /**< [511:448] Bits 320 to 387 of REG_MASK. See [REG_MASK0]. */
#else /* Word 7 - Little Endian */
        uint64_t reg_mask5             : 64; /**< [511:448] Bits 320 to 387 of REG_MASK. See [REG_MASK0]. */
#endif /* Word 7 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 8 - Big Endian */
        uint64_t reg_mask6             : 64; /**< [575:512] Bits 388 to 447 of REG_MASK. See [REG_MASK0]. */
#else /* Word 8 - Little Endian */
        uint64_t reg_mask6             : 64; /**< [575:512] Bits 388 to 447 of REG_MASK. See [REG_MASK0]. */
#endif /* Word 8 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 9 - Big Endian */
        uint64_t reg_mask7             : 64; /**< [639:576] Bits 448 to 511 of REG_MASK. See [REG_MASK0]. */
#else /* Word 9 - Little Endian */
        uint64_t reg_mask7             : 64; /**< [639:576] Bits 448 to 511 of REG_MASK. See [REG_MASK0]. */
#endif /* Word 9 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 10 - Big Endian */
        uint64_t reg_mask8             : 64; /**< [703:640] Bits 512 to 575 of REG_MASK. See [REG_MASK0]. */
#else /* Word 10 - Little Endian */
        uint64_t reg_mask8             : 64; /**< [703:640] Bits 512 to 575 of REG_MASK. See [REG_MASK0]. */
#endif /* Word 10 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 11 - Big Endian */
        uint64_t reg_mask9             : 64; /**< [767:704] Bits 576 to 639 of REG_MASK. See [REG_MASK0]. */
#else /* Word 11 - Little Endian */
        uint64_t reg_mask9             : 64; /**< [767:704] Bits 576 to 639 of REG_MASK. See [REG_MASK0]. */
#endif /* Word 11 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 12 - Big Endian */
        uint64_t reg_mask10            : 64; /**< [831:768] Bits 640 to 703 of REG_MASK. See [REG_MASK0]. */
#else /* Word 12 - Little Endian */
        uint64_t reg_mask10            : 64; /**< [831:768] Bits 640 to 703 of REG_MASK. See [REG_MASK0]. */
#endif /* Word 12 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 13 - Big Endian */
        uint64_t reg_mask11            : 64; /**< [895:832] Bits 704 to 767 of REG_MASK. See [REG_MASK0]. */
#else /* Word 13 - Little Endian */
        uint64_t reg_mask11            : 64; /**< [895:832] Bits 704 to 767 of REG_MASK. See [REG_MASK0]. */
#endif /* Word 13 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 14 - Big Endian */
        uint64_t reserved_928_959      : 32;
        uint64_t reg_mask12            : 32; /**< [927:896] Bits 768 to 799 of REG_MASK. See [REG_MASK0]. */
#else /* Word 14 - Little Endian */
        uint64_t reg_mask12            : 32; /**< [927:896] Bits 768 to 799 of REG_MASK. See [REG_MASK0]. */
        uint64_t reserved_928_959      : 32;
#endif /* Word 14 - End */
    } s;
    /* struct bdk_denc_pdcch_gen_cfg_s_s cn9; */
    /* struct bdk_denc_pdcch_gen_cfg_s_s cnf95xxp1; */
    struct bdk_denc_pdcch_gen_cfg_s_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_63           : 1;
        uint64_t c_init                : 31; /**< [ 62: 32] The initialization value C_init for the scrambler. */
        uint64_t reserved_30_31        : 2;
        uint64_t byps_pdcch            : 1;  /**< [ 29: 29] Must be set to 0.
                                                                 Internal:
                                                                 When set to 1, encoded bits are streamed out in the same order DCIs
                                                                 have been fed in, and other PDCCH functionality is bypassed. */
        uint64_t reg_pat               : 5;  /**< [ 28: 24] Index into the REG order pattern table. Valid range is [0x0, 0x8]. */
        uint64_t dci                   : 8;  /**< [ 23: 16] The number of DCI to multiplex. Valid range is [0x1, 0x58]. */
        uint64_t task_id               : 16; /**< [ 15:  0] Each task in a job should have a unique ID. */
#else /* Word 0 - Little Endian */
        uint64_t task_id               : 16; /**< [ 15:  0] Each task in a job should have a unique ID. */
        uint64_t dci                   : 8;  /**< [ 23: 16] The number of DCI to multiplex. Valid range is [0x1, 0x58]. */
        uint64_t reg_pat               : 5;  /**< [ 28: 24] Index into the REG order pattern table. Valid range is [0x0, 0x8]. */
        uint64_t byps_pdcch            : 1;  /**< [ 29: 29] Must be set to 0.
                                                                 Internal:
                                                                 When set to 1, encoded bits are streamed out in the same order DCIs
                                                                 have been fed in, and other PDCCH functionality is bypassed. */
        uint64_t reserved_30_31        : 2;
        uint64_t c_init                : 31; /**< [ 62: 32] The initialization value C_init for the scrambler. */
        uint64_t reserved_63           : 1;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_122_127      : 6;
        uint64_t in_by_o               : 2;  /**< [121:120] Input data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t in_bi_o               : 1;  /**< [119:119] Input data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t nrb                   : 7;  /**< [118:112] The number of RBs to map PDCCH to. This is the N_DL_RB parameter in
                                                                 3GPP TS 36.211. Valid values are {0x6, 0xF, 0x19, 0x32, 0x4B, 0x64}. */
        uint64_t reserved_110_111      : 2;
        uint64_t aqpsk                 : 14; /**< [109: 96] The scaling factor {a}QPSK. Note that each modulated symbol is scaled
                                                                 by its associated DCI gain and then AQPSK. */
        uint64_t pcell                 : 16; /**< [ 95: 80] The physical cell ID. This value is used during cyclic shifting. */
        uint64_t reserved_77_79        : 3;
        uint64_t byps_map              : 1;  /**< [ 76: 76] When set to 0, perform resource mapping.

                                                                 When set to 1, bypass resource element mapping. I/Q samples are output
                                                                 directly from modulation and gain scaling stage, and all symbols are
                                                                 written to thread 0. */
        uint64_t quad                  : 12; /**< [ 75: 64] The number of quadruplet symbols. */
#else /* Word 1 - Little Endian */
        uint64_t quad                  : 12; /**< [ 75: 64] The number of quadruplet symbols. */
        uint64_t byps_map              : 1;  /**< [ 76: 76] When set to 0, perform resource mapping.

                                                                 When set to 1, bypass resource element mapping. I/Q samples are output
                                                                 directly from modulation and gain scaling stage, and all symbols are
                                                                 written to thread 0. */
        uint64_t reserved_77_79        : 3;
        uint64_t pcell                 : 16; /**< [ 95: 80] The physical cell ID. This value is used during cyclic shifting. */
        uint64_t aqpsk                 : 14; /**< [109: 96] The scaling factor {a}QPSK. Note that each modulated symbol is scaled
                                                                 by its associated DCI gain and then AQPSK. */
        uint64_t reserved_110_111      : 2;
        uint64_t nrb                   : 7;  /**< [118:112] The number of RBs to map PDCCH to. This is the N_DL_RB parameter in
                                                                 3GPP TS 36.211. Valid values are {0x6, 0xF, 0x19, 0x32, 0x4B, 0x64}. */
        uint64_t in_bi_o               : 1;  /**< [119:119] Input data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t in_by_o               : 2;  /**< [121:120] Input data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t reserved_122_127      : 6;
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t reg_mask0             : 64; /**< [191:128] Bits 0 to 63 of the REG mask for PDCCH mapping.

                                                                 REG mask bit \<M*k+j\> specifies the REG mask for resource element group
                                                                 (REG) M*k+j, where

                                                                 _ M is the number of REGs per RB,

                                                                 _ 0 \<= k \< [NRB], and

                                                                 _ 0 \<= j \<= M-1.

                                                                 If a bit is set to 1, then the corresponding REG is occupied by PCFICH
                                                                 or PHICH and shall not be used by PDCCH. */
#else /* Word 2 - Little Endian */
        uint64_t reg_mask0             : 64; /**< [191:128] Bits 0 to 63 of the REG mask for PDCCH mapping.

                                                                 REG mask bit \<M*k+j\> specifies the REG mask for resource element group
                                                                 (REG) M*k+j, where

                                                                 _ M is the number of REGs per RB,

                                                                 _ 0 \<= k \< [NRB], and

                                                                 _ 0 \<= j \<= M-1.

                                                                 If a bit is set to 1, then the corresponding REG is occupied by PCFICH
                                                                 or PHICH and shall not be used by PDCCH. */
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t reg_mask1             : 64; /**< [255:192] Bits 64 to 127 of the REG mask. See [REG_MASK0]. */
#else /* Word 3 - Little Endian */
        uint64_t reg_mask1             : 64; /**< [255:192] Bits 64 to 127 of the REG mask. See [REG_MASK0]. */
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t reg_mask2             : 64; /**< [319:256] Bits 128 to 191 of the REG mask. See [REG_MASK0]. */
#else /* Word 4 - Little Endian */
        uint64_t reg_mask2             : 64; /**< [319:256] Bits 128 to 191 of the REG mask. See [REG_MASK0]. */
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t reg_mask3             : 64; /**< [383:320] Bits 192 to 255 of the REG mask. See [REG_MASK0]. */
#else /* Word 5 - Little Endian */
        uint64_t reg_mask3             : 64; /**< [383:320] Bits 192 to 255 of the REG mask. See [REG_MASK0]. */
#endif /* Word 5 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 6 - Big Endian */
        uint64_t reg_mask4             : 64; /**< [447:384] Bits 256 to 319 of the REG mask. See [REG_MASK0]. */
#else /* Word 6 - Little Endian */
        uint64_t reg_mask4             : 64; /**< [447:384] Bits 256 to 319 of the REG mask. See [REG_MASK0]. */
#endif /* Word 6 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 7 - Big Endian */
        uint64_t reg_mask5             : 64; /**< [511:448] Bits 320 to 383 of the REG mask. See [REG_MASK0]. */
#else /* Word 7 - Little Endian */
        uint64_t reg_mask5             : 64; /**< [511:448] Bits 320 to 383 of the REG mask. See [REG_MASK0]. */
#endif /* Word 7 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 8 - Big Endian */
        uint64_t reg_mask6             : 64; /**< [575:512] Bits 384 to 447 of the REG mask. See [REG_MASK0]. */
#else /* Word 8 - Little Endian */
        uint64_t reg_mask6             : 64; /**< [575:512] Bits 384 to 447 of the REG mask. See [REG_MASK0]. */
#endif /* Word 8 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 9 - Big Endian */
        uint64_t reg_mask7             : 64; /**< [639:576] Bits 448 to 511 of the REG mask. See [REG_MASK0]. */
#else /* Word 9 - Little Endian */
        uint64_t reg_mask7             : 64; /**< [639:576] Bits 448 to 511 of the REG mask. See [REG_MASK0]. */
#endif /* Word 9 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 10 - Big Endian */
        uint64_t reg_mask8             : 64; /**< [703:640] Bits 512 to 575 of the REG mask. See [REG_MASK0]. */
#else /* Word 10 - Little Endian */
        uint64_t reg_mask8             : 64; /**< [703:640] Bits 512 to 575 of the REG mask. See [REG_MASK0]. */
#endif /* Word 10 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 11 - Big Endian */
        uint64_t reg_mask9             : 64; /**< [767:704] Bits 576 to 639 of the REG mask. See [REG_MASK0]. */
#else /* Word 11 - Little Endian */
        uint64_t reg_mask9             : 64; /**< [767:704] Bits 576 to 639 of the REG mask. See [REG_MASK0]. */
#endif /* Word 11 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 12 - Big Endian */
        uint64_t reg_mask10            : 64; /**< [831:768] Bits 640 to 703 of the REG mask. See [REG_MASK0]. */
#else /* Word 12 - Little Endian */
        uint64_t reg_mask10            : 64; /**< [831:768] Bits 640 to 703 of the REG mask. See [REG_MASK0]. */
#endif /* Word 12 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 13 - Big Endian */
        uint64_t reg_mask11            : 64; /**< [895:832] Bits 704 to 767 of the REG mask. See [REG_MASK0]. */
#else /* Word 13 - Little Endian */
        uint64_t reg_mask11            : 64; /**< [895:832] Bits 704 to 767 of the REG mask. See [REG_MASK0]. */
#endif /* Word 13 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 14 - Big Endian */
        uint64_t reserved_928_959      : 32;
        uint64_t reg_mask12            : 32; /**< [927:896] Bits 768 to 799 of the REG mask. See [REG_MASK0]. */
#else /* Word 14 - Little Endian */
        uint64_t reg_mask12            : 32; /**< [927:896] Bits 768 to 799 of the REG mask. See [REG_MASK0]. */
        uint64_t reserved_928_959      : 32;
#endif /* Word 14 - End */
    } cnf95xxp2;
    /* struct bdk_denc_pdcch_gen_cfg_s_cnf95xxp2 loki; */
};

/**
 * Structure denc_pdsch_task_cfg_s
 *
 * DENC PDSCH Task Configuration Structure
 * This structure defines the per-task configuration for PDSCH/PMCH/PCH tasks
 * ([TASK_TYPE] = 0x0).
 *
 * The job configuration section of the job descriptor should include one
 * instance of this structure for each task in the job.
 */
union bdk_denc_pdsch_task_cfg_s
{
    uint64_t u[8];
    struct bdk_denc_pdsch_task_cfg_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_63           : 1;
        uint64_t in_by_o               : 2;  /**< [ 62: 61] Input data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t in_bi_o               : 1;  /**< [ 60: 60] Input data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t byps_cb_crc           : 1;  /**< [ 59: 59] This field only applies when [CB_MODE] = 1, and it is ignored otherwise.

                                                                 When set to 1, the code block CRC is bypassed and the input is assumed
                                                                 to contain the CB CRC.

                                                                 When set to 0, a 24-bit CB CRC is calculated using CRC24B and appended
                                                                 to the input. */
        uint64_t nl                    : 3;  /**< [ 58: 56] Number of layers the transport block will be mapped to. Valid range is
                                                                 [1,4].  For Tx Diversity use cases, [NL] must be set to 2 (even for
                                                                 four antenna port use cases). This is used in deriving the rate
                                                                 matching parameters. */
        uint64_t byps_rm               : 1;  /**< [ 55: 55] When set to 0, rate matching is performed and the output is [RM_E] bits
                                                                 long.

                                                                 When set to 1, rate matching is bypassed, and the output consists of
                                                                 3*[K] + 12 bits.

                                                                 Must be set to 0 when [CB_MODE] = 0. */
        uint64_t byps_rv               : 1;  /**< [ 54: 54] When set to 0, bit selection is performed by the core based on the
                                                                 redundancy version specified by [RV_IDX].

                                                                 When set to 1, the output bits start from offset 0 and bit selection
                                                                 is bypassed.

                                                                 This field must be set to 0 when [CB_MODE] = 0. This field is ignored
                                                                 when [BYPS_RM] = 1. */
        uint64_t rv_idx                : 2;  /**< [ 53: 52] Redundancy version index. */
        uint64_t payload               : 20; /**< [ 51: 32] The transport block payload size (in bits), not including the TB CRC.
                                                                 Valid range is [1,1046496]. */
        uint64_t filler                : 6;  /**< [ 31: 26] The number of filler bits. This value can only be nonzero for the
                                                                 first code block in a transport block. */
        uint64_t byps_crc              : 1;  /**< [ 25: 25] If set to 0, append 24-bit CRC calculated using CRC24A.

                                                                 If set to 1, assumes CRC is already present in input. */
        uint64_t cb_mode               : 1;  /**< [ 24: 24] If set to 1, operate in per-CB mode. This mode bypasses the following
                                                                 transport block processing functions:
                                                                 * transport block CRC addition.
                                                                 * code block segmentation.
                                                                 * code block concatenation.
                                                                 * scrambling.

                                                                 If set to 0, operate in per-TB mode. In this mode each job process an
                                                                 entire transport block with full functional coverage. */
        uint64_t num_cb                : 8;  /**< [ 23: 16] Number of code blocks in the transport block.  Valid range is [1,171]. */
        uint64_t task_id               : 16; /**< [ 15:  0] Each task in a job should have a unique ID. */
#else /* Word 0 - Little Endian */
        uint64_t task_id               : 16; /**< [ 15:  0] Each task in a job should have a unique ID. */
        uint64_t num_cb                : 8;  /**< [ 23: 16] Number of code blocks in the transport block.  Valid range is [1,171]. */
        uint64_t cb_mode               : 1;  /**< [ 24: 24] If set to 1, operate in per-CB mode. This mode bypasses the following
                                                                 transport block processing functions:
                                                                 * transport block CRC addition.
                                                                 * code block segmentation.
                                                                 * code block concatenation.
                                                                 * scrambling.

                                                                 If set to 0, operate in per-TB mode. In this mode each job process an
                                                                 entire transport block with full functional coverage. */
        uint64_t byps_crc              : 1;  /**< [ 25: 25] If set to 0, append 24-bit CRC calculated using CRC24A.

                                                                 If set to 1, assumes CRC is already present in input. */
        uint64_t filler                : 6;  /**< [ 31: 26] The number of filler bits. This value can only be nonzero for the
                                                                 first code block in a transport block. */
        uint64_t payload               : 20; /**< [ 51: 32] The transport block payload size (in bits), not including the TB CRC.
                                                                 Valid range is [1,1046496]. */
        uint64_t rv_idx                : 2;  /**< [ 53: 52] Redundancy version index. */
        uint64_t byps_rv               : 1;  /**< [ 54: 54] When set to 0, bit selection is performed by the core based on the
                                                                 redundancy version specified by [RV_IDX].

                                                                 When set to 1, the output bits start from offset 0 and bit selection
                                                                 is bypassed.

                                                                 This field must be set to 0 when [CB_MODE] = 0. This field is ignored
                                                                 when [BYPS_RM] = 1. */
        uint64_t byps_rm               : 1;  /**< [ 55: 55] When set to 0, rate matching is performed and the output is [RM_E] bits
                                                                 long.

                                                                 When set to 1, rate matching is bypassed, and the output consists of
                                                                 3*[K] + 12 bits.

                                                                 Must be set to 0 when [CB_MODE] = 0. */
        uint64_t nl                    : 3;  /**< [ 58: 56] Number of layers the transport block will be mapped to. Valid range is
                                                                 [1,4].  For Tx Diversity use cases, [NL] must be set to 2 (even for
                                                                 four antenna port use cases). This is used in deriving the rate
                                                                 matching parameters. */
        uint64_t byps_cb_crc           : 1;  /**< [ 59: 59] This field only applies when [CB_MODE] = 1, and it is ignored otherwise.

                                                                 When set to 1, the code block CRC is bypassed and the input is assumed
                                                                 to contain the CB CRC.

                                                                 When set to 0, a 24-bit CB CRC is calculated using CRC24B and appended
                                                                 to the input. */
        uint64_t in_bi_o               : 1;  /**< [ 60: 60] Input data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t in_by_o               : 2;  /**< [ 62: 61] Input data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t reserved_63           : 1;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t qm                    : 4;  /**< [127:124] Modulation order (Q_m):
                                                                 0x1 = BPSK.
                                                                 0x2 = QPSK.
                                                                 0x4 = 16-QAM.
                                                                 0x6 = 64-QAM.
                                                                 0x8 = 256-QAM.
                                                                 0xA = 1024-QAM. */
        uint64_t rm_e                  : 20; /**< [123:104] In per-TB mode ([CB_MODE] = 0), this is the rate-matched output size for
                                                                 the first CB:

                                                                 [RM_E] = [NL] * [QM] * floor( [G] / ([NL]*[QM]*[NUM_CB]) ).

                                                                 In per-CB mode ([CB_MODE] = 1), this is the rate-matched size for the CB
                                                                 to be processed. If [BYPS_RM]=1, this value must be equal to 3*[K] + 12. */
        uint64_t max_buf               : 20; /**< [103: 84] The maximum circular buffer size. This corresponds to floor(N_IR /
                                                                 [NUM_CB]). */
        uint64_t g                     : 20; /**< [ 83: 64] The total number of bits available for transmission of the transport
                                                                 block. */
#else /* Word 1 - Little Endian */
        uint64_t g                     : 20; /**< [ 83: 64] The total number of bits available for transmission of the transport
                                                                 block. */
        uint64_t max_buf               : 20; /**< [103: 84] The maximum circular buffer size. This corresponds to floor(N_IR /
                                                                 [NUM_CB]). */
        uint64_t rm_e                  : 20; /**< [123:104] In per-TB mode ([CB_MODE] = 0), this is the rate-matched output size for
                                                                 the first CB:

                                                                 [RM_E] = [NL] * [QM] * floor( [G] / ([NL]*[QM]*[NUM_CB]) ).

                                                                 In per-CB mode ([CB_MODE] = 1), this is the rate-matched size for the CB
                                                                 to be processed. If [BYPS_RM]=1, this value must be equal to 3*[K] + 12. */
        uint64_t qm                    : 4;  /**< [127:124] Modulation order (Q_m):
                                                                 0x1 = BPSK.
                                                                 0x2 = QPSK.
                                                                 0x4 = 16-QAM.
                                                                 0x6 = 64-QAM.
                                                                 0x8 = 256-QAM.
                                                                 0xA = 1024-QAM. */
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t reserved_191          : 1;
        uint64_t c_init                : 31; /**< [190:160] The initialization value C_init for the second m-sequence of the scrambler. */
        uint64_t reserved_157_159      : 3;
        uint64_t symb_align            : 2;  /**< [156:155] Select the aligment and interleaving for output bits.
                                                                 0x0: Bypass mode. Bits are written consecutively, with no per-symbol
                                                                 alignment.
                                                                 0x1: Byte alignment for [QM] \< 10. Every [QM] bits are aligned to a byte
                                                                 boundary.
                                                                 0x2: Interleaved byte alignment for [QM] = 10. For each symbol, the five
                                                                 even bits are packed in one byte, and the five odd bits are packed
                                                                 in the next byte.
                                                                 0x3: Consecutive byte alignment for [QM] = 10. For each symbol, bits 0-4
                                                                 are written in one byte and bits 5-9 are written in the next
                                                                 subsequent byte. */
        uint64_t out_by_o              : 2;  /**< [154:153] Output data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t out_bi_o              : 1;  /**< [152:152] Output data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t gamma                 : 8;  /**< [151:144] Rate matching parameter calculated as:

                                                                 _ [GAMMA] = ( [G] / ([NL]*[QM]) ) mod [NUM_CB]. */
        uint64_t byps_seg              : 1;  /**< [143:143] When set to 0, the output is segmented, with extra padding inserted.
                                                                 See [SEG_PAD] for more details.

                                                                 When set to 1, the output bits are written contiguously with no extra
                                                                 padding inserted to segment the output. */
        uint64_t reserved_142          : 1;
        uint64_t byps_scram            : 1;  /**< [141:141] When set to 0, perform scrambling.

                                                                 When set to 1, bypass scrambling.

                                                                 When [CB_MODE] = 1, scrambling is always bypassed and this flag is
                                                                 ignored. */
        uint64_t k                     : 13; /**< [140:128] Payload size, including CRC, of the first code block within the
                                                                 transport block.

                                                                 When [CB_MODE] = 1, this is the size including CRC of the code block
                                                                 being encoded by this task. */
#else /* Word 2 - Little Endian */
        uint64_t k                     : 13; /**< [140:128] Payload size, including CRC, of the first code block within the
                                                                 transport block.

                                                                 When [CB_MODE] = 1, this is the size including CRC of the code block
                                                                 being encoded by this task. */
        uint64_t byps_scram            : 1;  /**< [141:141] When set to 0, perform scrambling.

                                                                 When set to 1, bypass scrambling.

                                                                 When [CB_MODE] = 1, scrambling is always bypassed and this flag is
                                                                 ignored. */
        uint64_t reserved_142          : 1;
        uint64_t byps_seg              : 1;  /**< [143:143] When set to 0, the output is segmented, with extra padding inserted.
                                                                 See [SEG_PAD] for more details.

                                                                 When set to 1, the output bits are written contiguously with no extra
                                                                 padding inserted to segment the output. */
        uint64_t gamma                 : 8;  /**< [151:144] Rate matching parameter calculated as:

                                                                 _ [GAMMA] = ( [G] / ([NL]*[QM]) ) mod [NUM_CB]. */
        uint64_t out_bi_o              : 1;  /**< [152:152] Output data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t out_by_o              : 2;  /**< [154:153] Output data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t symb_align            : 2;  /**< [156:155] Select the aligment and interleaving for output bits.
                                                                 0x0: Bypass mode. Bits are written consecutively, with no per-symbol
                                                                 alignment.
                                                                 0x1: Byte alignment for [QM] \< 10. Every [QM] bits are aligned to a byte
                                                                 boundary.
                                                                 0x2: Interleaved byte alignment for [QM] = 10. For each symbol, the five
                                                                 even bits are packed in one byte, and the five odd bits are packed
                                                                 in the next byte.
                                                                 0x3: Consecutive byte alignment for [QM] = 10. For each symbol, bits 0-4
                                                                 are written in one byte and bits 5-9 are written in the next
                                                                 subsequent byte. */
        uint64_t reserved_157_159      : 3;
        uint64_t c_init                : 31; /**< [190:160] The initialization value C_init for the second m-sequence of the scrambler. */
        uint64_t reserved_191          : 1;
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t reserved_255          : 1;
        uint64_t seg3_syms_per_layer   : 15; /**< [254:240] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_239          : 1;
        uint64_t seg2_syms_per_layer   : 15; /**< [238:224] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_223          : 1;
        uint64_t seg1_syms_per_layer   : 15; /**< [222:208] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_207          : 1;
        uint64_t seg0_syms_per_layer   : 15; /**< [206:192] See [BYPS_SEG] and [SEG_PAD] for details. */
#else /* Word 3 - Little Endian */
        uint64_t seg0_syms_per_layer   : 15; /**< [206:192] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_207          : 1;
        uint64_t seg1_syms_per_layer   : 15; /**< [222:208] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_223          : 1;
        uint64_t seg2_syms_per_layer   : 15; /**< [238:224] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_239          : 1;
        uint64_t seg3_syms_per_layer   : 15; /**< [254:240] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_255          : 1;
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t reserved_319          : 1;
        uint64_t seg7_syms_per_layer   : 15; /**< [318:304] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_303          : 1;
        uint64_t seg6_syms_per_layer   : 15; /**< [302:288] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_287          : 1;
        uint64_t seg5_syms_per_layer   : 15; /**< [286:272] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_271          : 1;
        uint64_t seg4_syms_per_layer   : 15; /**< [270:256] See [BYPS_SEG] and [SEG_PAD] for details. */
#else /* Word 4 - Little Endian */
        uint64_t seg4_syms_per_layer   : 15; /**< [270:256] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_271          : 1;
        uint64_t seg5_syms_per_layer   : 15; /**< [286:272] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_287          : 1;
        uint64_t seg6_syms_per_layer   : 15; /**< [302:288] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_303          : 1;
        uint64_t seg7_syms_per_layer   : 15; /**< [318:304] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_319          : 1;
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t reserved_383          : 1;
        uint64_t seg11_syms_per_layer  : 15; /**< [382:368] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_367          : 1;
        uint64_t seg10_syms_per_layer  : 15; /**< [366:352] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_351          : 1;
        uint64_t seg9_syms_per_layer   : 15; /**< [350:336] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_335          : 1;
        uint64_t seg8_syms_per_layer   : 15; /**< [334:320] See [BYPS_SEG] and [SEG_PAD] for details. */
#else /* Word 5 - Little Endian */
        uint64_t seg8_syms_per_layer   : 15; /**< [334:320] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_335          : 1;
        uint64_t seg9_syms_per_layer   : 15; /**< [350:336] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_351          : 1;
        uint64_t seg10_syms_per_layer  : 15; /**< [366:352] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_367          : 1;
        uint64_t seg11_syms_per_layer  : 15; /**< [382:368] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_383          : 1;
#endif /* Word 5 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 6 - Big Endian */
        uint64_t reserved_440_447      : 8;
        uint64_t sym_per_layer         : 24; /**< [439:416] When [SEG_PAD]=1, specifies the total number of symbols in all segments.
                                                                 Each segment is padded to this size.

                                                                 Note that when [SEG_PAD]=1 and [SYMB_ALIGN]=0, [SYM_PER_LAYER] must be
                                                                 set such that ([QM] x [SYM_PER_LAYER]) % 128 = 0.

                                                                 When [SEG_PAD]=1 and [SYMB_ALIGN]=1, [SYM_PER_LAYER] must be
                                                                 set such that (8 x [SYM_PER_LAYER]) % 128 = 0.

                                                                 When [SEG_PAD]=1 and [SYMB_ALIGN]=2 or 3, [SYM_PER_LAYER] must be
                                                                 set such that (16 x [SYM_PER_LAYER]) % 128 = 0. */
        uint64_t seg_pad               : 1;  /**< [415:415] Segment padding mode:
                                                                 0: Pad each segment to the next multiple of 128 bit words after
                                                                 writing [SEGx_SYMS_PER_LAYER].
                                                                 1: Pad all segments to contain [SYM_PER_LAYER] symbols.
                                                                 See [SYM_PER_LAYER] for more details. */
        uint64_t seg13_syms_per_layer  : 15; /**< [414:400] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_399          : 1;
        uint64_t seg12_syms_per_layer  : 15; /**< [398:384] See [BYPS_SEG] and [SEG_PAD] for details. */
#else /* Word 6 - Little Endian */
        uint64_t seg12_syms_per_layer  : 15; /**< [398:384] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_399          : 1;
        uint64_t seg13_syms_per_layer  : 15; /**< [414:400] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t seg_pad               : 1;  /**< [415:415] Segment padding mode:
                                                                 0: Pad each segment to the next multiple of 128 bit words after
                                                                 writing [SEGx_SYMS_PER_LAYER].
                                                                 1: Pad all segments to contain [SYM_PER_LAYER] symbols.
                                                                 See [SYM_PER_LAYER] for more details. */
        uint64_t sym_per_layer         : 24; /**< [439:416] When [SEG_PAD]=1, specifies the total number of symbols in all segments.
                                                                 Each segment is padded to this size.

                                                                 Note that when [SEG_PAD]=1 and [SYMB_ALIGN]=0, [SYM_PER_LAYER] must be
                                                                 set such that ([QM] x [SYM_PER_LAYER]) % 128 = 0.

                                                                 When [SEG_PAD]=1 and [SYMB_ALIGN]=1, [SYM_PER_LAYER] must be
                                                                 set such that (8 x [SYM_PER_LAYER]) % 128 = 0.

                                                                 When [SEG_PAD]=1 and [SYMB_ALIGN]=2 or 3, [SYM_PER_LAYER] must be
                                                                 set such that (16 x [SYM_PER_LAYER]) % 128 = 0. */
        uint64_t reserved_440_447      : 8;
#endif /* Word 6 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 7 - Big Endian */
        uint64_t reserved_462_511      : 50;
        uint64_t num_rd0_wrds          : 14; /**< [461:448] Number of words to read from read DMA port 0 for this task. */
#else /* Word 7 - Little Endian */
        uint64_t num_rd0_wrds          : 14; /**< [461:448] Number of words to read from read DMA port 0 for this task. */
        uint64_t reserved_462_511      : 50;
#endif /* Word 7 - End */
    } s;
    /* struct bdk_denc_pdsch_task_cfg_s_s cn9; */
    /* struct bdk_denc_pdsch_task_cfg_s_s cnf95xxp1; */
    struct bdk_denc_pdsch_task_cfg_s_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_63           : 1;
        uint64_t in_by_o               : 2;  /**< [ 62: 61] Input data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t in_bi_o               : 1;  /**< [ 60: 60] Input data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t byps_cb_crc           : 1;  /**< [ 59: 59] This field only applies when [CB_MODE] = 1, and it is ignored otherwise.

                                                                 When set to 1, the code block CRC is bypassed and the input is assumed
                                                                 to contain the CB CRC.

                                                                 When set to 0, a 24-bit CB CRC is calculated using CRC24B and appended
                                                                 to the input. */
        uint64_t nl                    : 3;  /**< [ 58: 56] Number of layers the transport block will be mapped to. Valid range is
                                                                 [0x1, 0x4].  For Tx Diversity use cases, [NL] must be set to 0x2 (even for
                                                                 four antenna port use cases). This is used in deriving the rate
                                                                 matching parameters. */
        uint64_t byps_rm               : 1;  /**< [ 55: 55] When set to 0, rate matching is performed and the output is [RM_E] bits
                                                                 long.

                                                                 When set to 1, rate matching is bypassed, and the output consists of
                                                                 3 * [K] + 12 bits.

                                                                 Must be set to 0 when [CB_MODE] = 0. */
        uint64_t byps_rv               : 1;  /**< [ 54: 54] When set to 0, bit selection is performed by the core based on the
                                                                 redundancy version specified by [RV_IDX].

                                                                 When set to 1, the output bits start from offset 0 and bit selection
                                                                 is bypassed.

                                                                 This field must be set to 0 when [CB_MODE] = 0. This field is ignored
                                                                 when [BYPS_RM] = 1. */
        uint64_t rv_idx                : 2;  /**< [ 53: 52] Redundancy version index. */
        uint64_t payload               : 20; /**< [ 51: 32] The transport block payload size (in bits), not including the TB CRC.
                                                                 Valid range is [0x1, 0xFF7E0]. */
        uint64_t filler                : 6;  /**< [ 31: 26] The number of filler bits. This value can only be nonzero for the
                                                                 first code block in a transport block. */
        uint64_t byps_crc              : 1;  /**< [ 25: 25] If set to 0, append 24-bit CRC calculated using CRC24A.

                                                                 If set to 1, assumes CRC is already present in input. */
        uint64_t cb_mode               : 1;  /**< [ 24: 24] If set to 1, operate in per-CB mode. This mode bypasses the following
                                                                 transport block processing functions:
                                                                 * transport block CRC addition.
                                                                 * code block segmentation.
                                                                 * code block concatenation.
                                                                 * scrambling.

                                                                 If set to 0, operate in per-TB mode. In this mode each job process an
                                                                 entire transport block with full functional coverage. */
        uint64_t num_cb                : 8;  /**< [ 23: 16] Number of code blocks in the transport block.  Valid range is [0x1, 0xAB]. */
        uint64_t task_id               : 16; /**< [ 15:  0] Each task in a job should have a unique ID. */
#else /* Word 0 - Little Endian */
        uint64_t task_id               : 16; /**< [ 15:  0] Each task in a job should have a unique ID. */
        uint64_t num_cb                : 8;  /**< [ 23: 16] Number of code blocks in the transport block.  Valid range is [0x1, 0xAB]. */
        uint64_t cb_mode               : 1;  /**< [ 24: 24] If set to 1, operate in per-CB mode. This mode bypasses the following
                                                                 transport block processing functions:
                                                                 * transport block CRC addition.
                                                                 * code block segmentation.
                                                                 * code block concatenation.
                                                                 * scrambling.

                                                                 If set to 0, operate in per-TB mode. In this mode each job process an
                                                                 entire transport block with full functional coverage. */
        uint64_t byps_crc              : 1;  /**< [ 25: 25] If set to 0, append 24-bit CRC calculated using CRC24A.

                                                                 If set to 1, assumes CRC is already present in input. */
        uint64_t filler                : 6;  /**< [ 31: 26] The number of filler bits. This value can only be nonzero for the
                                                                 first code block in a transport block. */
        uint64_t payload               : 20; /**< [ 51: 32] The transport block payload size (in bits), not including the TB CRC.
                                                                 Valid range is [0x1, 0xFF7E0]. */
        uint64_t rv_idx                : 2;  /**< [ 53: 52] Redundancy version index. */
        uint64_t byps_rv               : 1;  /**< [ 54: 54] When set to 0, bit selection is performed by the core based on the
                                                                 redundancy version specified by [RV_IDX].

                                                                 When set to 1, the output bits start from offset 0 and bit selection
                                                                 is bypassed.

                                                                 This field must be set to 0 when [CB_MODE] = 0. This field is ignored
                                                                 when [BYPS_RM] = 1. */
        uint64_t byps_rm               : 1;  /**< [ 55: 55] When set to 0, rate matching is performed and the output is [RM_E] bits
                                                                 long.

                                                                 When set to 1, rate matching is bypassed, and the output consists of
                                                                 3 * [K] + 12 bits.

                                                                 Must be set to 0 when [CB_MODE] = 0. */
        uint64_t nl                    : 3;  /**< [ 58: 56] Number of layers the transport block will be mapped to. Valid range is
                                                                 [0x1, 0x4].  For Tx Diversity use cases, [NL] must be set to 0x2 (even for
                                                                 four antenna port use cases). This is used in deriving the rate
                                                                 matching parameters. */
        uint64_t byps_cb_crc           : 1;  /**< [ 59: 59] This field only applies when [CB_MODE] = 1, and it is ignored otherwise.

                                                                 When set to 1, the code block CRC is bypassed and the input is assumed
                                                                 to contain the CB CRC.

                                                                 When set to 0, a 24-bit CB CRC is calculated using CRC24B and appended
                                                                 to the input. */
        uint64_t in_bi_o               : 1;  /**< [ 60: 60] Input data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t in_by_o               : 2;  /**< [ 62: 61] Input data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t reserved_63           : 1;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t qm                    : 4;  /**< [127:124] Modulation order (Q_m):
                                                                 0x1 = BPSK.
                                                                 0x2 = QPSK.
                                                                 0x4 = 16-QAM.
                                                                 0x6 = 64-QAM.
                                                                 0x8 = 256-QAM.
                                                                 0xA = 1024-QAM. */
        uint64_t rm_e                  : 20; /**< [123:104] In per-TB mode ([CB_MODE] = 0), this is the rate-matched output size for
                                                                 the first CB:

                                                                 [RM_E] = [NL] * [QM] * floor( [G] / ([NL] * [QM] * [NUM_CB]) ).

                                                                 In per-CB mode ([CB_MODE] = 1), this is the rate-matched size for the CB
                                                                 to be processed. If [BYPS_RM] = 1, this value must be equal to 3 * [K] + 12. */
        uint64_t max_buf               : 20; /**< [103: 84] The maximum circular buffer size. This corresponds to floor(N_IR /
                                                                 [NUM_CB]). */
        uint64_t g                     : 20; /**< [ 83: 64] The total number of bits available for transmission of the transport
                                                                 block. */
#else /* Word 1 - Little Endian */
        uint64_t g                     : 20; /**< [ 83: 64] The total number of bits available for transmission of the transport
                                                                 block. */
        uint64_t max_buf               : 20; /**< [103: 84] The maximum circular buffer size. This corresponds to floor(N_IR /
                                                                 [NUM_CB]). */
        uint64_t rm_e                  : 20; /**< [123:104] In per-TB mode ([CB_MODE] = 0), this is the rate-matched output size for
                                                                 the first CB:

                                                                 [RM_E] = [NL] * [QM] * floor( [G] / ([NL] * [QM] * [NUM_CB]) ).

                                                                 In per-CB mode ([CB_MODE] = 1), this is the rate-matched size for the CB
                                                                 to be processed. If [BYPS_RM] = 1, this value must be equal to 3 * [K] + 12. */
        uint64_t qm                    : 4;  /**< [127:124] Modulation order (Q_m):
                                                                 0x1 = BPSK.
                                                                 0x2 = QPSK.
                                                                 0x4 = 16-QAM.
                                                                 0x6 = 64-QAM.
                                                                 0x8 = 256-QAM.
                                                                 0xA = 1024-QAM. */
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t reserved_191          : 1;
        uint64_t c_init                : 31; /**< [190:160] The initialization value C_init for the second m-sequence of the scrambler. */
        uint64_t reserved_157_159      : 3;
        uint64_t symb_align            : 2;  /**< [156:155] Select the aligment and interleaving for output bits.
                                                                 0x0: Bypass mode. Bits are written consecutively, with no per-symbol
                                                                 alignment.
                                                                 0x1: Byte alignment for [QM] \< 0xA. Every [QM] bits are aligned to a byte
                                                                 boundary.
                                                                 0x2: Interleaved byte alignment for [QM] = 0xA. For each symbol, the five
                                                                 even bits are packed in one byte, and the five odd bits are packed
                                                                 in the next byte.
                                                                 0x3: Consecutive byte alignment for [QM] = 0xA. For each symbol, bits 0-4
                                                                 are written in one byte and bits 5-9 are written in the
                                                                 subsequent byte. */
        uint64_t out_by_o              : 2;  /**< [154:153] Output data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t out_bi_o              : 1;  /**< [152:152] Output data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t gamma                 : 8;  /**< [151:144] Rate matching parameter calculated as:

                                                                 _ [GAMMA] = ( [G] / ([NL] * [QM]) ) mod [NUM_CB]. */
        uint64_t byps_seg              : 1;  /**< [143:143] When set to 0, the output is segmented, with extra padding inserted.
                                                                 See [SEG_PAD] for more details.

                                                                 When set to 1, the output bits are written contiguously with no extra
                                                                 padding inserted to segment the output. */
        uint64_t reserved_142          : 1;
        uint64_t byps_scram            : 1;  /**< [141:141] When set to 0, perform scrambling.

                                                                 When set to 1, bypass scrambling.

                                                                 When [CB_MODE] = 1, scrambling is always bypassed and this flag is
                                                                 ignored. */
        uint64_t k                     : 13; /**< [140:128] Payload size, including CRC, of the first code block within the
                                                                 transport block.

                                                                 When [CB_MODE] = 1, this is the size including CRC of the code block
                                                                 being encoded by this task. */
#else /* Word 2 - Little Endian */
        uint64_t k                     : 13; /**< [140:128] Payload size, including CRC, of the first code block within the
                                                                 transport block.

                                                                 When [CB_MODE] = 1, this is the size including CRC of the code block
                                                                 being encoded by this task. */
        uint64_t byps_scram            : 1;  /**< [141:141] When set to 0, perform scrambling.

                                                                 When set to 1, bypass scrambling.

                                                                 When [CB_MODE] = 1, scrambling is always bypassed and this flag is
                                                                 ignored. */
        uint64_t reserved_142          : 1;
        uint64_t byps_seg              : 1;  /**< [143:143] When set to 0, the output is segmented, with extra padding inserted.
                                                                 See [SEG_PAD] for more details.

                                                                 When set to 1, the output bits are written contiguously with no extra
                                                                 padding inserted to segment the output. */
        uint64_t gamma                 : 8;  /**< [151:144] Rate matching parameter calculated as:

                                                                 _ [GAMMA] = ( [G] / ([NL] * [QM]) ) mod [NUM_CB]. */
        uint64_t out_bi_o              : 1;  /**< [152:152] Output data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t out_by_o              : 2;  /**< [154:153] Output data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t symb_align            : 2;  /**< [156:155] Select the aligment and interleaving for output bits.
                                                                 0x0: Bypass mode. Bits are written consecutively, with no per-symbol
                                                                 alignment.
                                                                 0x1: Byte alignment for [QM] \< 0xA. Every [QM] bits are aligned to a byte
                                                                 boundary.
                                                                 0x2: Interleaved byte alignment for [QM] = 0xA. For each symbol, the five
                                                                 even bits are packed in one byte, and the five odd bits are packed
                                                                 in the next byte.
                                                                 0x3: Consecutive byte alignment for [QM] = 0xA. For each symbol, bits 0-4
                                                                 are written in one byte and bits 5-9 are written in the
                                                                 subsequent byte. */
        uint64_t reserved_157_159      : 3;
        uint64_t c_init                : 31; /**< [190:160] The initialization value C_init for the second m-sequence of the scrambler. */
        uint64_t reserved_191          : 1;
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t reserved_255          : 1;
        uint64_t seg3_syms_per_layer   : 15; /**< [254:240] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_239          : 1;
        uint64_t seg2_syms_per_layer   : 15; /**< [238:224] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_223          : 1;
        uint64_t seg1_syms_per_layer   : 15; /**< [222:208] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_207          : 1;
        uint64_t seg0_syms_per_layer   : 15; /**< [206:192] See [BYPS_SEG] and [SEG_PAD] for details. */
#else /* Word 3 - Little Endian */
        uint64_t seg0_syms_per_layer   : 15; /**< [206:192] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_207          : 1;
        uint64_t seg1_syms_per_layer   : 15; /**< [222:208] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_223          : 1;
        uint64_t seg2_syms_per_layer   : 15; /**< [238:224] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_239          : 1;
        uint64_t seg3_syms_per_layer   : 15; /**< [254:240] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_255          : 1;
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t reserved_319          : 1;
        uint64_t seg7_syms_per_layer   : 15; /**< [318:304] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_303          : 1;
        uint64_t seg6_syms_per_layer   : 15; /**< [302:288] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_287          : 1;
        uint64_t seg5_syms_per_layer   : 15; /**< [286:272] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_271          : 1;
        uint64_t seg4_syms_per_layer   : 15; /**< [270:256] See [BYPS_SEG] and [SEG_PAD] for details. */
#else /* Word 4 - Little Endian */
        uint64_t seg4_syms_per_layer   : 15; /**< [270:256] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_271          : 1;
        uint64_t seg5_syms_per_layer   : 15; /**< [286:272] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_287          : 1;
        uint64_t seg6_syms_per_layer   : 15; /**< [302:288] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_303          : 1;
        uint64_t seg7_syms_per_layer   : 15; /**< [318:304] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_319          : 1;
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t reserved_383          : 1;
        uint64_t seg11_syms_per_layer  : 15; /**< [382:368] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_367          : 1;
        uint64_t seg10_syms_per_layer  : 15; /**< [366:352] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_351          : 1;
        uint64_t seg9_syms_per_layer   : 15; /**< [350:336] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_335          : 1;
        uint64_t seg8_syms_per_layer   : 15; /**< [334:320] See [BYPS_SEG] and [SEG_PAD] for details. */
#else /* Word 5 - Little Endian */
        uint64_t seg8_syms_per_layer   : 15; /**< [334:320] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_335          : 1;
        uint64_t seg9_syms_per_layer   : 15; /**< [350:336] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_351          : 1;
        uint64_t seg10_syms_per_layer  : 15; /**< [366:352] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_367          : 1;
        uint64_t seg11_syms_per_layer  : 15; /**< [382:368] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_383          : 1;
#endif /* Word 5 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 6 - Big Endian */
        uint64_t reserved_440_447      : 8;
        uint64_t sym_per_layer         : 24; /**< [439:416] When [SEG_PAD] = 1, specifies the total number of symbols in all segments.
                                                                 Each segment is padded to this size.

                                                                 Note that when [SEG_PAD] = 1 and [SYMB_ALIGN] = 0x0, [SYM_PER_LAYER] must be
                                                                 set such that ([QM] x [SYM_PER_LAYER]) % 128 = 0.

                                                                 When [SEG_PAD] = 1 and [SYMB_ALIGN] = 0x1, [SYM_PER_LAYER] must be
                                                                 set such that (8 x [SYM_PER_LAYER]) % 128 = 0.

                                                                 When [SEG_PAD] = 1 and [SYMB_ALIGN] = 0x2 or 0x3, [SYM_PER_LAYER] must be
                                                                 set such that (16 x [SYM_PER_LAYER]) % 128 = 0. */
        uint64_t seg_pad               : 1;  /**< [415:415] Segment padding mode:
                                                                 0: Pad each segment to the next multiple of 128-bit words after
                                                                 writing [SEGx_SYMS_PER_LAYER].
                                                                 1: Pad all segments to contain [SYM_PER_LAYER] symbols.
                                                                 See [SYM_PER_LAYER] for more details. */
        uint64_t seg13_syms_per_layer  : 15; /**< [414:400] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_399          : 1;
        uint64_t seg12_syms_per_layer  : 15; /**< [398:384] See [BYPS_SEG] and [SEG_PAD] for details. */
#else /* Word 6 - Little Endian */
        uint64_t seg12_syms_per_layer  : 15; /**< [398:384] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t reserved_399          : 1;
        uint64_t seg13_syms_per_layer  : 15; /**< [414:400] See [BYPS_SEG] and [SEG_PAD] for details. */
        uint64_t seg_pad               : 1;  /**< [415:415] Segment padding mode:
                                                                 0: Pad each segment to the next multiple of 128-bit words after
                                                                 writing [SEGx_SYMS_PER_LAYER].
                                                                 1: Pad all segments to contain [SYM_PER_LAYER] symbols.
                                                                 See [SYM_PER_LAYER] for more details. */
        uint64_t sym_per_layer         : 24; /**< [439:416] When [SEG_PAD] = 1, specifies the total number of symbols in all segments.
                                                                 Each segment is padded to this size.

                                                                 Note that when [SEG_PAD] = 1 and [SYMB_ALIGN] = 0x0, [SYM_PER_LAYER] must be
                                                                 set such that ([QM] x [SYM_PER_LAYER]) % 128 = 0.

                                                                 When [SEG_PAD] = 1 and [SYMB_ALIGN] = 0x1, [SYM_PER_LAYER] must be
                                                                 set such that (8 x [SYM_PER_LAYER]) % 128 = 0.

                                                                 When [SEG_PAD] = 1 and [SYMB_ALIGN] = 0x2 or 0x3, [SYM_PER_LAYER] must be
                                                                 set such that (16 x [SYM_PER_LAYER]) % 128 = 0. */
        uint64_t reserved_440_447      : 8;
#endif /* Word 6 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 7 - Big Endian */
        uint64_t reserved_462_511      : 50;
        uint64_t num_rd0_wrds          : 14; /**< [461:448] Number of words to read from read DMA port 0 for this task. */
#else /* Word 7 - Little Endian */
        uint64_t num_rd0_wrds          : 14; /**< [461:448] Number of words to read from read DMA port 0 for this task. */
        uint64_t reserved_462_511      : 50;
#endif /* Word 7 - End */
    } cnf95xxp2;
    /* struct bdk_denc_pdsch_task_cfg_s_cnf95xxp2 loki; */
};

/**
 * Structure denc_rpdcch_gen_cfg_s
 *
 * DENC R-PDCCH General Configuration Structure
 * This structure defines general configuration parameters for R-PDCCH tasks
 * with cross-interleaving ([TASK_TYPE] = 0x5).
 *
 * The job configuration section of the job descriptor should include one
 * instance of this structure.
 *
 * Note there can only be one task in an R-PDCCH job.
 */
union bdk_denc_rpdcch_gen_cfg_s
{
    uint64_t u[2];
    struct bdk_denc_rpdcch_gen_cfg_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_63           : 1;
        uint64_t c_init                : 31; /**< [ 62: 32] The initialization value C_init for the scrambler. */
        uint64_t reserved_30_31        : 2;
        uint64_t byps_rpdcch           : 1;  /**< [ 29: 29] Must be set to 0.
                                                                 Internal:
                                                                 When set to 1, encoded bits are streamed out in the same order DCIs
                                                                 have been fed in, and other R-PDCCH functionality is bypassed. */
        uint64_t reg_pat               : 5;  /**< [ 28: 24] Index into the REG order pattern table. Valid range is [0,8]. */
        uint64_t dci                   : 8;  /**< [ 23: 16] The number of DCI to multiplex. Valid range is [1,88]. */
        uint64_t task_id               : 16; /**< [ 15:  0] Each task in a job should have a unique ID. */
#else /* Word 0 - Little Endian */
        uint64_t task_id               : 16; /**< [ 15:  0] Each task in a job should have a unique ID. */
        uint64_t dci                   : 8;  /**< [ 23: 16] The number of DCI to multiplex. Valid range is [1,88]. */
        uint64_t reg_pat               : 5;  /**< [ 28: 24] Index into the REG order pattern table. Valid range is [0,8]. */
        uint64_t byps_rpdcch           : 1;  /**< [ 29: 29] Must be set to 0.
                                                                 Internal:
                                                                 When set to 1, encoded bits are streamed out in the same order DCIs
                                                                 have been fed in, and other R-PDCCH functionality is bypassed. */
        uint64_t reserved_30_31        : 2;
        uint64_t c_init                : 31; /**< [ 62: 32] The initialization value C_init for the scrambler. */
        uint64_t reserved_63           : 1;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_122_127      : 6;
        uint64_t in_by_o               : 2;  /**< [121:120] Input data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t in_bi_o               : 1;  /**< [119:119] Input data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t reserved_110_118      : 9;
        uint64_t aqpsk                 : 14; /**< [109: 96] The scaling factor {a}QPSK. Note that each modulated symbol is scaled
                                                                 by its associated DCI gain and then [AQPSK]. */
        uint64_t pcell                 : 16; /**< [ 95: 80] The physical cell ID. This value is used during cyclic shifting. */
        uint64_t reserved_77_79        : 3;
        uint64_t byps_map              : 1;  /**< [ 76: 76] Must be set to 1 for R-PDCCH jobs. */
        uint64_t quad                  : 12; /**< [ 75: 64] The number of quadruplet symbols. */
#else /* Word 1 - Little Endian */
        uint64_t quad                  : 12; /**< [ 75: 64] The number of quadruplet symbols. */
        uint64_t byps_map              : 1;  /**< [ 76: 76] Must be set to 1 for R-PDCCH jobs. */
        uint64_t reserved_77_79        : 3;
        uint64_t pcell                 : 16; /**< [ 95: 80] The physical cell ID. This value is used during cyclic shifting. */
        uint64_t aqpsk                 : 14; /**< [109: 96] The scaling factor {a}QPSK. Note that each modulated symbol is scaled
                                                                 by its associated DCI gain and then [AQPSK]. */
        uint64_t reserved_110_118      : 9;
        uint64_t in_bi_o               : 1;  /**< [119:119] Input data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t in_by_o               : 2;  /**< [121:120] Input data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t reserved_122_127      : 6;
#endif /* Word 1 - End */
    } s;
    /* struct bdk_denc_rpdcch_gen_cfg_s_s cn9; */
    /* struct bdk_denc_rpdcch_gen_cfg_s_s cnf95xxp1; */
    struct bdk_denc_rpdcch_gen_cfg_s_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_63           : 1;
        uint64_t c_init                : 31; /**< [ 62: 32] The initialization value C_init for the scrambler. */
        uint64_t reserved_30_31        : 2;
        uint64_t byps_rpdcch           : 1;  /**< [ 29: 29] Must be set to 0.
                                                                 Internal:
                                                                 When set to 1, encoded bits are streamed out in the same order DCIs
                                                                 have been fed in, and other R-PDCCH functionality is bypassed. */
        uint64_t reg_pat               : 5;  /**< [ 28: 24] Index into the REG order pattern table. Valid range is [0x0, 0x8]. */
        uint64_t dci                   : 8;  /**< [ 23: 16] The number of DCI to multiplex. Valid range is [0x1, 0x58]. */
        uint64_t task_id               : 16; /**< [ 15:  0] Each task in a job should have a unique ID. */
#else /* Word 0 - Little Endian */
        uint64_t task_id               : 16; /**< [ 15:  0] Each task in a job should have a unique ID. */
        uint64_t dci                   : 8;  /**< [ 23: 16] The number of DCI to multiplex. Valid range is [0x1, 0x58]. */
        uint64_t reg_pat               : 5;  /**< [ 28: 24] Index into the REG order pattern table. Valid range is [0x0, 0x8]. */
        uint64_t byps_rpdcch           : 1;  /**< [ 29: 29] Must be set to 0.
                                                                 Internal:
                                                                 When set to 1, encoded bits are streamed out in the same order DCIs
                                                                 have been fed in, and other R-PDCCH functionality is bypassed. */
        uint64_t reserved_30_31        : 2;
        uint64_t c_init                : 31; /**< [ 62: 32] The initialization value C_init for the scrambler. */
        uint64_t reserved_63           : 1;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_122_127      : 6;
        uint64_t in_by_o               : 2;  /**< [121:120] Input data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t in_bi_o               : 1;  /**< [119:119] Input data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t reserved_110_118      : 9;
        uint64_t aqpsk                 : 14; /**< [109: 96] The scaling factor {a}QPSK. Note that each modulated symbol is scaled
                                                                 by its associated DCI gain and then [AQPSK]. */
        uint64_t pcell                 : 16; /**< [ 95: 80] The physical cell ID. This value is used during cyclic shifting. */
        uint64_t reserved_77_79        : 3;
        uint64_t byps_map              : 1;  /**< [ 76: 76] Must be set to 1 for R-PDCCH jobs. */
        uint64_t quad                  : 12; /**< [ 75: 64] The number of quadruplet symbols. */
#else /* Word 1 - Little Endian */
        uint64_t quad                  : 12; /**< [ 75: 64] The number of quadruplet symbols. */
        uint64_t byps_map              : 1;  /**< [ 76: 76] Must be set to 1 for R-PDCCH jobs. */
        uint64_t reserved_77_79        : 3;
        uint64_t pcell                 : 16; /**< [ 95: 80] The physical cell ID. This value is used during cyclic shifting. */
        uint64_t aqpsk                 : 14; /**< [109: 96] The scaling factor {a}QPSK. Note that each modulated symbol is scaled
                                                                 by its associated DCI gain and then [AQPSK]. */
        uint64_t reserved_110_118      : 9;
        uint64_t in_bi_o               : 1;  /**< [119:119] Input data bit order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t in_by_o               : 2;  /**< [121:120] Input data byte order.  See Baseband PHY (BPHY): Data Packing section
                                                                 for details. */
        uint64_t reserved_122_127      : 6;
#endif /* Word 1 - End */
    } cnf95xxp2;
    /* struct bdk_denc_rpdcch_gen_cfg_s_cnf95xxp2 loki; */
};

/**
 * Register (RSL) denc#_control
 *
 * DENC Control Register
 */
union bdk_dencx_control
{
    uint64_t u;
    struct bdk_dencx_control_s
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
    /* struct bdk_dencx_control_s cn; */
};
typedef union bdk_dencx_control bdk_dencx_control_t;

static inline uint64_t BDK_DENCX_CONTROL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DENCX_CONTROL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=2))
        return 0x87e043480000ll + 0x8000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=2))
        return 0x87e043480000ll + 0x8000ll * ((a) & 0x3);
    __bdk_csr_fatal("DENCX_CONTROL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DENCX_CONTROL(a) bdk_dencx_control_t
#define bustype_BDK_DENCX_CONTROL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DENCX_CONTROL(a) "DENCX_CONTROL"
#define busnum_BDK_DENCX_CONTROL(a) (a)
#define arguments_BDK_DENCX_CONTROL(a) (a),-1,-1,-1

/**
 * Register (RSL) denc#_eco
 *
 * INTERNAL: DENC ECO Register
 */
union bdk_dencx_eco
{
    uint64_t u;
    struct bdk_dencx_eco_s
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
    /* struct bdk_dencx_eco_s cn; */
};
typedef union bdk_dencx_eco bdk_dencx_eco_t;

static inline uint64_t BDK_DENCX_ECO(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DENCX_ECO(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=2))
        return 0x87e043480008ll + 0x8000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=2))
        return 0x87e043480008ll + 0x8000ll * ((a) & 0x3);
    __bdk_csr_fatal("DENCX_ECO", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DENCX_ECO(a) bdk_dencx_eco_t
#define bustype_BDK_DENCX_ECO(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DENCX_ECO(a) "DENCX_ECO"
#define busnum_BDK_DENCX_ECO(a) (a)
#define arguments_BDK_DENCX_ECO(a) (a),-1,-1,-1

/**
 * Register (RSL) denc#_error_enable0
 *
 * Error Enable 0 Register
 * This register enables error reporting for read overflow/underflow errors.
 */
union bdk_dencx_error_enable0
{
    uint64_t u;
    struct bdk_dencx_error_enable0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t rp0_of_en             : 1;  /**< [  4:  4](R/W) Read port 0 overflow enable. */
        uint64_t reserved_1_3          : 3;
        uint64_t rp0_uf_en             : 1;  /**< [  0:  0](R/W) Read Port 0 underflow enable. */
#else /* Word 0 - Little Endian */
        uint64_t rp0_uf_en             : 1;  /**< [  0:  0](R/W) Read Port 0 underflow enable. */
        uint64_t reserved_1_3          : 3;
        uint64_t rp0_of_en             : 1;  /**< [  4:  4](R/W) Read port 0 overflow enable. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dencx_error_enable0_s cn; */
};
typedef union bdk_dencx_error_enable0 bdk_dencx_error_enable0_t;

static inline uint64_t BDK_DENCX_ERROR_ENABLE0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DENCX_ERROR_ENABLE0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=2))
        return 0x87e043480040ll + 0x8000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=2))
        return 0x87e043480040ll + 0x8000ll * ((a) & 0x3);
    __bdk_csr_fatal("DENCX_ERROR_ENABLE0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DENCX_ERROR_ENABLE0(a) bdk_dencx_error_enable0_t
#define bustype_BDK_DENCX_ERROR_ENABLE0(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DENCX_ERROR_ENABLE0(a) "DENCX_ERROR_ENABLE0"
#define busnum_BDK_DENCX_ERROR_ENABLE0(a) (a)
#define arguments_BDK_DENCX_ERROR_ENABLE0(a) (a),-1,-1,-1

/**
 * Register (RSL) denc#_error_source0
 *
 * DENC Error Source 0 Register
 * This register indicates the source of overflow/underflow errors.
 */
union bdk_dencx_error_source0
{
    uint64_t u;
    struct bdk_dencx_error_source0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t seg_jid               : 16; /**< [ 63: 48](RO/H) Job ID of the job which reported the segmentation overflow/underflow error. */
        uint64_t reserved_37_47        : 11;
        uint64_t seg_of                : 1;  /**< [ 36: 36](R/W1C/H) Write port segmentation overflow. */
        uint64_t reserved_33_35        : 3;
        uint64_t seg_uf                : 1;  /**< [ 32: 32](R/W1C/H) Write port segmentation underflow. */
        uint64_t rp0_jid               : 16; /**< [ 31: 16](RO/H) Job ID of the job which reported the overflow/underflow error on read
                                                                 port 0. */
        uint64_t reserved_5_15         : 11;
        uint64_t rp0_of                : 1;  /**< [  4:  4](R/W1C/H) Read port 0 overflow. */
        uint64_t reserved_1_3          : 3;
        uint64_t rp0_uf                : 1;  /**< [  0:  0](R/W1C/H) Read port 0 underflow. */
#else /* Word 0 - Little Endian */
        uint64_t rp0_uf                : 1;  /**< [  0:  0](R/W1C/H) Read port 0 underflow. */
        uint64_t reserved_1_3          : 3;
        uint64_t rp0_of                : 1;  /**< [  4:  4](R/W1C/H) Read port 0 overflow. */
        uint64_t reserved_5_15         : 11;
        uint64_t rp0_jid               : 16; /**< [ 31: 16](RO/H) Job ID of the job which reported the overflow/underflow error on read
                                                                 port 0. */
        uint64_t seg_uf                : 1;  /**< [ 32: 32](R/W1C/H) Write port segmentation underflow. */
        uint64_t reserved_33_35        : 3;
        uint64_t seg_of                : 1;  /**< [ 36: 36](R/W1C/H) Write port segmentation overflow. */
        uint64_t reserved_37_47        : 11;
        uint64_t seg_jid               : 16; /**< [ 63: 48](RO/H) Job ID of the job which reported the segmentation overflow/underflow error. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dencx_error_source0_s cn; */
};
typedef union bdk_dencx_error_source0 bdk_dencx_error_source0_t;

static inline uint64_t BDK_DENCX_ERROR_SOURCE0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DENCX_ERROR_SOURCE0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=2))
        return 0x87e043480030ll + 0x8000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=2))
        return 0x87e043480030ll + 0x8000ll * ((a) & 0x3);
    __bdk_csr_fatal("DENCX_ERROR_SOURCE0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DENCX_ERROR_SOURCE0(a) bdk_dencx_error_source0_t
#define bustype_BDK_DENCX_ERROR_SOURCE0(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DENCX_ERROR_SOURCE0(a) "DENCX_ERROR_SOURCE0"
#define busnum_BDK_DENCX_ERROR_SOURCE0(a) (a)
#define arguments_BDK_DENCX_ERROR_SOURCE0(a) (a),-1,-1,-1

/**
 * Register (RSL) denc#_hab_jcfg0_ram#_data
 *
 * DENC Job Configuration 0 RAM Register
 * This register range accesses the job configuration RAM for slot 0.
 */
union bdk_dencx_hab_jcfg0_ramx_data
{
    uint64_t u;
    struct bdk_dencx_hab_jcfg0_ramx_data_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t entry                 : 64; /**< [ 63:  0](R/W/H) Job configuration RAM entry. */
#else /* Word 0 - Little Endian */
        uint64_t entry                 : 64; /**< [ 63:  0](R/W/H) Job configuration RAM entry. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dencx_hab_jcfg0_ramx_data_s cn; */
};
typedef union bdk_dencx_hab_jcfg0_ramx_data bdk_dencx_hab_jcfg0_ramx_data_t;

static inline uint64_t BDK_DENCX_HAB_JCFG0_RAMX_DATA(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DENCX_HAB_JCFG0_RAMX_DATA(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=2) && (b<=255)))
        return 0x87e043482000ll + 0x8000ll * ((a) & 0x3) + 8ll * ((b) & 0xff);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=2) && (b<=255)))
        return 0x87e043482000ll + 0x8000ll * ((a) & 0x3) + 8ll * ((b) & 0xff);
    __bdk_csr_fatal("DENCX_HAB_JCFG0_RAMX_DATA", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_DENCX_HAB_JCFG0_RAMX_DATA(a,b) bdk_dencx_hab_jcfg0_ramx_data_t
#define bustype_BDK_DENCX_HAB_JCFG0_RAMX_DATA(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_DENCX_HAB_JCFG0_RAMX_DATA(a,b) "DENCX_HAB_JCFG0_RAMX_DATA"
#define busnum_BDK_DENCX_HAB_JCFG0_RAMX_DATA(a,b) (a)
#define arguments_BDK_DENCX_HAB_JCFG0_RAMX_DATA(a,b) (a),(b),-1,-1

/**
 * Register (RSL) denc#_hab_jcfg1_ram#_data
 *
 * DENC Job Configuration 1 RAM Register
 * This register range accesses the job configuration RAM for slot 1.
 */
union bdk_dencx_hab_jcfg1_ramx_data
{
    uint64_t u;
    struct bdk_dencx_hab_jcfg1_ramx_data_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t entry                 : 64; /**< [ 63:  0](R/W/H) Job configuration RAM entry. */
#else /* Word 0 - Little Endian */
        uint64_t entry                 : 64; /**< [ 63:  0](R/W/H) Job configuration RAM entry. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dencx_hab_jcfg1_ramx_data_s cn; */
};
typedef union bdk_dencx_hab_jcfg1_ramx_data bdk_dencx_hab_jcfg1_ramx_data_t;

static inline uint64_t BDK_DENCX_HAB_JCFG1_RAMX_DATA(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DENCX_HAB_JCFG1_RAMX_DATA(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=2) && (b<=255)))
        return 0x87e043484000ll + 0x8000ll * ((a) & 0x3) + 8ll * ((b) & 0xff);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=2) && (b<=255)))
        return 0x87e043484000ll + 0x8000ll * ((a) & 0x3) + 8ll * ((b) & 0xff);
    __bdk_csr_fatal("DENCX_HAB_JCFG1_RAMX_DATA", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_DENCX_HAB_JCFG1_RAMX_DATA(a,b) bdk_dencx_hab_jcfg1_ramx_data_t
#define bustype_BDK_DENCX_HAB_JCFG1_RAMX_DATA(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_DENCX_HAB_JCFG1_RAMX_DATA(a,b) "DENCX_HAB_JCFG1_RAMX_DATA"
#define busnum_BDK_DENCX_HAB_JCFG1_RAMX_DATA(a,b) (a)
#define arguments_BDK_DENCX_HAB_JCFG1_RAMX_DATA(a,b) (a),(b),-1,-1

/**
 * Register (RSL) denc#_hab_jcfg2_ram#_data
 *
 * DENC Job Configuration 2 RAM Register
 * This register range accesses the job configuration RAM for slot 2.
 */
union bdk_dencx_hab_jcfg2_ramx_data
{
    uint64_t u;
    struct bdk_dencx_hab_jcfg2_ramx_data_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t entry                 : 64; /**< [ 63:  0](R/W/H) Job configuration RAM entry. */
#else /* Word 0 - Little Endian */
        uint64_t entry                 : 64; /**< [ 63:  0](R/W/H) Job configuration RAM entry. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dencx_hab_jcfg2_ramx_data_s cn; */
};
typedef union bdk_dencx_hab_jcfg2_ramx_data bdk_dencx_hab_jcfg2_ramx_data_t;

static inline uint64_t BDK_DENCX_HAB_JCFG2_RAMX_DATA(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DENCX_HAB_JCFG2_RAMX_DATA(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=2) && (b<=255)))
        return 0x87e043486000ll + 0x8000ll * ((a) & 0x3) + 8ll * ((b) & 0xff);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=2) && (b<=255)))
        return 0x87e043486000ll + 0x8000ll * ((a) & 0x3) + 8ll * ((b) & 0xff);
    __bdk_csr_fatal("DENCX_HAB_JCFG2_RAMX_DATA", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_DENCX_HAB_JCFG2_RAMX_DATA(a,b) bdk_dencx_hab_jcfg2_ramx_data_t
#define bustype_BDK_DENCX_HAB_JCFG2_RAMX_DATA(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_DENCX_HAB_JCFG2_RAMX_DATA(a,b) "DENCX_HAB_JCFG2_RAMX_DATA"
#define busnum_BDK_DENCX_HAB_JCFG2_RAMX_DATA(a,b) (a)
#define arguments_BDK_DENCX_HAB_JCFG2_RAMX_DATA(a,b) (a),(b),-1,-1

/**
 * Register (RSL) denc#_scratch
 *
 * INTERNAL: Scratch Register
 *
 * Scratch register.
 */
union bdk_dencx_scratch
{
    uint64_t u;
    struct bdk_dencx_scratch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Scratch data. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Scratch data. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dencx_scratch_s cn; */
};
typedef union bdk_dencx_scratch bdk_dencx_scratch_t;

static inline uint64_t BDK_DENCX_SCRATCH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DENCX_SCRATCH(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=2))
        return 0x87e043480080ll + 0x8000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=2))
        return 0x87e043480080ll + 0x8000ll * ((a) & 0x3);
    __bdk_csr_fatal("DENCX_SCRATCH", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DENCX_SCRATCH(a) bdk_dencx_scratch_t
#define bustype_BDK_DENCX_SCRATCH(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DENCX_SCRATCH(a) "DENCX_SCRATCH"
#define busnum_BDK_DENCX_SCRATCH(a) (a)
#define arguments_BDK_DENCX_SCRATCH(a) (a),-1,-1,-1

/**
 * Register (RSL) denc#_status
 *
 * DENC Status Register
 */
union bdk_dencx_status
{
    uint64_t u;
    struct bdk_dencx_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t ready                 : 1;  /**< [  4:  4](RO/H) When set, the DENC HAB is ready to receive the next job. */
        uint64_t reserved_3            : 1;
        uint64_t cfg2_busy             : 1;  /**< [  2:  2](RO/H) When set, slot 2 is busy processing a job. */
        uint64_t cfg1_busy             : 1;  /**< [  1:  1](RO/H) When set, slot 1 is busy processing a job. */
        uint64_t cfg0_busy             : 1;  /**< [  0:  0](RO/H) When set, slot 0 is busy processing a job. */
#else /* Word 0 - Little Endian */
        uint64_t cfg0_busy             : 1;  /**< [  0:  0](RO/H) When set, slot 0 is busy processing a job. */
        uint64_t cfg1_busy             : 1;  /**< [  1:  1](RO/H) When set, slot 1 is busy processing a job. */
        uint64_t cfg2_busy             : 1;  /**< [  2:  2](RO/H) When set, slot 2 is busy processing a job. */
        uint64_t reserved_3            : 1;
        uint64_t ready                 : 1;  /**< [  4:  4](RO/H) When set, the DENC HAB is ready to receive the next job. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dencx_status_s cn; */
};
typedef union bdk_dencx_status bdk_dencx_status_t;

static inline uint64_t BDK_DENCX_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DENCX_STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=2))
        return 0x87e043480018ll + 0x8000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=2))
        return 0x87e043480018ll + 0x8000ll * ((a) & 0x3);
    __bdk_csr_fatal("DENCX_STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DENCX_STATUS(a) bdk_dencx_status_t
#define bustype_BDK_DENCX_STATUS(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DENCX_STATUS(a) "DENCX_STATUS"
#define busnum_BDK_DENCX_STATUS(a) (a)
#define arguments_BDK_DENCX_STATUS(a) (a),-1,-1,-1

/**
 * Register (RSL) denc#_tc_config_err_flags_reg
 *
 * DENC Task Configuration Error Flags Register
 * This register reports task configuration errors that occur when a
 * specified parameter value is outside the acceptable range.
 */
union bdk_dencx_tc_config_err_flags_reg
{
    uint64_t u;
    struct bdk_dencx_tc_config_err_flags_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t error_epdcch_res2     : 3;  /**< [ 63: 61](RO) reserved. */
        uint64_t reserved_45_60        : 16;
        uint64_t error_epdcch_res1     : 2;  /**< [ 44: 43](RO) reserved. */
        uint64_t reserved_39_42        : 4;
        uint64_t error_epdcch_res0     : 1;  /**< [ 38: 38](RO) reserved. */
        uint64_t reserved_36_37        : 2;
        uint64_t error_pdcch_res3      : 1;  /**< [ 35: 35](RO) reserved. */
        uint64_t reserved_32_34        : 3;
        uint64_t error_pdcch_res2      : 1;  /**< [ 31: 31](RO) reserved. */
        uint64_t reserved_29_30        : 2;
        uint64_t error_pdcch_res1      : 1;  /**< [ 28: 28](RO) reserved. */
        uint64_t reserved_26_27        : 2;
        uint64_t error_pdcch_res0      : 1;  /**< [ 25: 25](RO) reserved. */
        uint64_t error_pdsch_res3      : 1;  /**< [ 24: 24](RO) reserved. */
        uint64_t error23_pdsch         : 1;  /**< [ 23: 23](R/W/H) invalid range for nfiller [0..min(K-1,63)]. */
        uint64_t error_pdsch_res2      : 1;  /**< [ 22: 22](RO) reserved. */
        uint64_t reserved_13_21        : 9;
        uint64_t error_pdsch_res1      : 1;  /**< [ 12: 12](RO) reserved. */
        uint64_t reserved_6_11         : 6;
        uint64_t error5_pdsch          : 1;  /**< [  5:  5](R/W/H) invalid range for K [40..6144] */
        uint64_t reserved_3_4          : 2;
        uint64_t error_pdsch_res0      : 1;  /**< [  2:  2](RO) reserved. */
        uint64_t reserved_0_1          : 2;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_1          : 2;
        uint64_t error_pdsch_res0      : 1;  /**< [  2:  2](RO) reserved. */
        uint64_t reserved_3_4          : 2;
        uint64_t error5_pdsch          : 1;  /**< [  5:  5](R/W/H) invalid range for K [40..6144] */
        uint64_t reserved_6_11         : 6;
        uint64_t error_pdsch_res1      : 1;  /**< [ 12: 12](RO) reserved. */
        uint64_t reserved_13_21        : 9;
        uint64_t error_pdsch_res2      : 1;  /**< [ 22: 22](RO) reserved. */
        uint64_t error23_pdsch         : 1;  /**< [ 23: 23](R/W/H) invalid range for nfiller [0..min(K-1,63)]. */
        uint64_t error_pdsch_res3      : 1;  /**< [ 24: 24](RO) reserved. */
        uint64_t error_pdcch_res0      : 1;  /**< [ 25: 25](RO) reserved. */
        uint64_t reserved_26_27        : 2;
        uint64_t error_pdcch_res1      : 1;  /**< [ 28: 28](RO) reserved. */
        uint64_t reserved_29_30        : 2;
        uint64_t error_pdcch_res2      : 1;  /**< [ 31: 31](RO) reserved. */
        uint64_t reserved_32_34        : 3;
        uint64_t error_pdcch_res3      : 1;  /**< [ 35: 35](RO) reserved. */
        uint64_t reserved_36_37        : 2;
        uint64_t error_epdcch_res0     : 1;  /**< [ 38: 38](RO) reserved. */
        uint64_t reserved_39_42        : 4;
        uint64_t error_epdcch_res1     : 2;  /**< [ 44: 43](RO) reserved. */
        uint64_t reserved_45_60        : 16;
        uint64_t error_epdcch_res2     : 3;  /**< [ 63: 61](RO) reserved. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dencx_tc_config_err_flags_reg_s cn9; */
    struct bdk_dencx_tc_config_err_flags_reg_cnf95xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t error_epdcch_res2     : 3;  /**< [ 63: 61](RO) reserved. */
        uint64_t error60_epdcch        : 1;  /**< [ 60: 60](R/W/H) invalid range for ereg_pattern_idx15 [0..4]. */
        uint64_t error59_epdcch        : 1;  /**< [ 59: 59](R/W/H) invalid range for ereg_pattern_idx14 [0..4]. */
        uint64_t error58_epdcch        : 1;  /**< [ 58: 58](R/W/H) invalid range for ereg_pattern_idx13 [0..4]. */
        uint64_t error57_epdcch        : 1;  /**< [ 57: 57](R/W/H) invalid range for ereg_pattern_idx12 [0..4]. */
        uint64_t error56_epdcch        : 1;  /**< [ 56: 56](R/W/H) invalid range for ereg_pattern_idx11 [0..4]. */
        uint64_t error55_epdcch        : 1;  /**< [ 55: 55](R/W/H) invalid range for ereg_pattern_idx10 [0..4]. */
        uint64_t error54_epdcch        : 1;  /**< [ 54: 54](R/W/H) invalid range for ereg_pattern_idx9 [0..4]. */
        uint64_t error53_epdcch        : 1;  /**< [ 53: 53](R/W/H) invalid range for ereg_pattern_idx8 [0..4]. */
        uint64_t error52_epdcch        : 1;  /**< [ 52: 52](R/W/H) invalid range for ereg_pattern_idx7 [0..4]. */
        uint64_t error51_epdcch        : 1;  /**< [ 51: 51](R/W/H) invalid range for ereg_pattern_idx6 [0..4]. */
        uint64_t error50_epdcch        : 1;  /**< [ 50: 50](R/W/H) invalid range for ereg_pattern_idx5 [0..4]. */
        uint64_t error49_epdcch        : 1;  /**< [ 49: 49](R/W/H) invalid range for ereg_pattern_idx4 [0..4]. */
        uint64_t error48_epdcch        : 1;  /**< [ 48: 48](R/W/H) invalid range for ereg_pattern_idx3 [0..4]. */
        uint64_t error47_epdcch        : 1;  /**< [ 47: 47](R/W/H) invalid range for ereg_pattern_idx2 [0..4]. */
        uint64_t error46_epdcch        : 1;  /**< [ 46: 46](R/W/H) invalid range for ereg_pattern_idx1 [0..4]. */
        uint64_t error45_epdcch        : 1;  /**< [ 45: 45](R/W/H) invalid range for ereg_pattern_idx0 [0..4]. */
        uint64_t error_epdcch_res1     : 2;  /**< [ 44: 43](RO) reserved. */
        uint64_t error42_epdcch        : 1;  /**< [ 42: 42](R/W/H) invalid range for input_byte_order {0,1,2}. */
        uint64_t error41_epdcch        : 1;  /**< [ 41: 41](R/W/H) invalid range for input_bit_order {0,1}. */
        uint64_t error40_epdcch        : 1;  /**< [ 40: 40](R/W/H) invalid range for num_rbs [1..16]. */
        uint64_t error39_epdcch        : 1;  /**< [ 39: 39](R/W/H) invalid range for num_edci [1..64]. */
        uint64_t error_epdcch_res0     : 1;  /**< [ 38: 38](RO) reserved. */
        uint64_t error37_pdcch         : 1;  /**< [ 37: 37](R/W/H) invalid range for input_byte_order {0,1,2}. */
        uint64_t error36_pdcch         : 1;  /**< [ 36: 36](R/W/H) invalid range for input_bit_order {0,1}. */
        uint64_t error_pdcch_res3      : 1;  /**< [ 35: 35](RO) reserved. */
        uint64_t error34_pdcch         : 1;  /**< [ 34: 34](R/W/H) invalid range for num_rbs [6..100]. */
        uint64_t error33_pdcch         : 1;  /**< [ 33: 33](R/W/H) invalid range for reg_order_idx [0..31]. */
        uint64_t error32_pdcch         : 1;  /**< [ 32: 32](R/W/H) invalid range for bypass_reg_mapping {0,1}. */
        uint64_t error_pdcch_res2      : 1;  /**< [ 31: 31](RO) reserved. */
        uint64_t error30_pdcch         : 1;  /**< [ 30: 30](R/W/H) invalid range for m_quad [9..800]. */
        uint64_t error29_pdcch         : 1;  /**< [ 29: 29](R/W/H) invalid range for pcell_id [0..791]. */
        uint64_t error_pdcch_res1      : 1;  /**< [ 28: 28](RO) reserved. */
        uint64_t error27_pdcch         : 1;  /**< [ 27: 27](R/W/H) invalid range for bypass_pdcch_proc {0,1}. */
        uint64_t error26_pdcch         : 1;  /**< [ 26: 26](R/W/H) invalid range for num_dci [1..88]. */
        uint64_t error_pdcch_res0      : 1;  /**< [ 25: 25](RO) reserved. */
        uint64_t error_pdsch_res3      : 1;  /**< [ 24: 24](RO) reserved. */
        uint64_t error23_pdsch         : 1;  /**< [ 23: 23](R/W/H) invalid range for nfiller [0..min(K-1,63)]. */
        uint64_t error_pdsch_res2      : 1;  /**< [ 22: 22](RO) reserved. */
        uint64_t error21_pdsch         : 1;  /**< [ 21: 21](R/W/H) invalid range for bypass_scrambling {0,1}. */
        uint64_t error20_pdsch         : 1;  /**< [ 20: 20](R/W/H) invalid range for input_byte_order {0,1,2}. */
        uint64_t error19_pdsch         : 1;  /**< [ 19: 19](R/W/H) invalid range for input_bit_order {0,1}. */
        uint64_t error18_pdsch         : 1;  /**< [ 18: 18](R/W/H) invalid range for symb_byte_aligned {0,1,2,3}. */
        uint64_t error17_pdsch         : 1;  /**< [ 17: 17](R/W/H) invalid range for Qm {1,2,3,4,6,8,10}. */
        uint64_t error16_pdsch         : 1;  /**< [ 16: 16](R/W/H) invalid range for NL [1..4]. */
        uint64_t error15_pdsch         : 1;  /**< [ 15: 15](R/W/H) invalid range for gamma [0..C-1]. */
        uint64_t error14_pdsch         : 1;  /**< [ 14: 14](R/W/H) invalid range for E [1..2^20-1]. */
        uint64_t error13_pdsch         : 1;  /**< [ 13: 13](R/W/H) invalid range for G [1..2^20-1]. */
        uint64_t error_pdsch_res1      : 1;  /**< [ 12: 12](RO) reserved. */
        uint64_t error11_pdsch         : 1;  /**< [ 11: 11](R/W/H) invalid range for rvidx [0..3]. */
        uint64_t error10_pdsch         : 1;  /**< [ 10: 10](R/W/H) invalid range for bypass_rvidx {0,1}. */
        uint64_t error9_pdsch          : 1;  /**< [  9:  9](R/W/H) invalid range for bypass_rm {0,1}. */
        uint64_t error8_pdsch          : 1;  /**< [  8:  8](R/W/H) invalid range for bypass_cb_crc {0,1}. */
        uint64_t error7_pdsch          : 1;  /**< [  7:  7](R/W/H) invalid range for bypass_tb_proc {0,1}. */
        uint64_t error6_pdsch          : 1;  /**< [  6:  6](R/W/H) invalid range for bypass_tb_crc {0,1}. */
        uint64_t error5_pdsch          : 1;  /**< [  5:  5](R/W/H) invalid range for K [40..6144] */
        uint64_t error4_pdsch          : 1;  /**< [  4:  4](R/W/H) invalid range for A [1..1048552]. */
        uint64_t error3_pdsch          : 1;  /**< [  3:  3](R/W/H) invalid range for C [1..171]. */
        uint64_t error_pdsch_res0      : 1;  /**< [  2:  2](RO) reserved. */
        uint64_t error1                : 1;  /**< [  1:  1](R/W/H) payload block size error. */
        uint64_t error0                : 1;  /**< [  0:  0](R/W/H) Invalid channel mode. */
#else /* Word 0 - Little Endian */
        uint64_t error0                : 1;  /**< [  0:  0](R/W/H) Invalid channel mode. */
        uint64_t error1                : 1;  /**< [  1:  1](R/W/H) payload block size error. */
        uint64_t error_pdsch_res0      : 1;  /**< [  2:  2](RO) reserved. */
        uint64_t error3_pdsch          : 1;  /**< [  3:  3](R/W/H) invalid range for C [1..171]. */
        uint64_t error4_pdsch          : 1;  /**< [  4:  4](R/W/H) invalid range for A [1..1048552]. */
        uint64_t error5_pdsch          : 1;  /**< [  5:  5](R/W/H) invalid range for K [40..6144] */
        uint64_t error6_pdsch          : 1;  /**< [  6:  6](R/W/H) invalid range for bypass_tb_crc {0,1}. */
        uint64_t error7_pdsch          : 1;  /**< [  7:  7](R/W/H) invalid range for bypass_tb_proc {0,1}. */
        uint64_t error8_pdsch          : 1;  /**< [  8:  8](R/W/H) invalid range for bypass_cb_crc {0,1}. */
        uint64_t error9_pdsch          : 1;  /**< [  9:  9](R/W/H) invalid range for bypass_rm {0,1}. */
        uint64_t error10_pdsch         : 1;  /**< [ 10: 10](R/W/H) invalid range for bypass_rvidx {0,1}. */
        uint64_t error11_pdsch         : 1;  /**< [ 11: 11](R/W/H) invalid range for rvidx [0..3]. */
        uint64_t error_pdsch_res1      : 1;  /**< [ 12: 12](RO) reserved. */
        uint64_t error13_pdsch         : 1;  /**< [ 13: 13](R/W/H) invalid range for G [1..2^20-1]. */
        uint64_t error14_pdsch         : 1;  /**< [ 14: 14](R/W/H) invalid range for E [1..2^20-1]. */
        uint64_t error15_pdsch         : 1;  /**< [ 15: 15](R/W/H) invalid range for gamma [0..C-1]. */
        uint64_t error16_pdsch         : 1;  /**< [ 16: 16](R/W/H) invalid range for NL [1..4]. */
        uint64_t error17_pdsch         : 1;  /**< [ 17: 17](R/W/H) invalid range for Qm {1,2,3,4,6,8,10}. */
        uint64_t error18_pdsch         : 1;  /**< [ 18: 18](R/W/H) invalid range for symb_byte_aligned {0,1,2,3}. */
        uint64_t error19_pdsch         : 1;  /**< [ 19: 19](R/W/H) invalid range for input_bit_order {0,1}. */
        uint64_t error20_pdsch         : 1;  /**< [ 20: 20](R/W/H) invalid range for input_byte_order {0,1,2}. */
        uint64_t error21_pdsch         : 1;  /**< [ 21: 21](R/W/H) invalid range for bypass_scrambling {0,1}. */
        uint64_t error_pdsch_res2      : 1;  /**< [ 22: 22](RO) reserved. */
        uint64_t error23_pdsch         : 1;  /**< [ 23: 23](R/W/H) invalid range for nfiller [0..min(K-1,63)]. */
        uint64_t error_pdsch_res3      : 1;  /**< [ 24: 24](RO) reserved. */
        uint64_t error_pdcch_res0      : 1;  /**< [ 25: 25](RO) reserved. */
        uint64_t error26_pdcch         : 1;  /**< [ 26: 26](R/W/H) invalid range for num_dci [1..88]. */
        uint64_t error27_pdcch         : 1;  /**< [ 27: 27](R/W/H) invalid range for bypass_pdcch_proc {0,1}. */
        uint64_t error_pdcch_res1      : 1;  /**< [ 28: 28](RO) reserved. */
        uint64_t error29_pdcch         : 1;  /**< [ 29: 29](R/W/H) invalid range for pcell_id [0..791]. */
        uint64_t error30_pdcch         : 1;  /**< [ 30: 30](R/W/H) invalid range for m_quad [9..800]. */
        uint64_t error_pdcch_res2      : 1;  /**< [ 31: 31](RO) reserved. */
        uint64_t error32_pdcch         : 1;  /**< [ 32: 32](R/W/H) invalid range for bypass_reg_mapping {0,1}. */
        uint64_t error33_pdcch         : 1;  /**< [ 33: 33](R/W/H) invalid range for reg_order_idx [0..31]. */
        uint64_t error34_pdcch         : 1;  /**< [ 34: 34](R/W/H) invalid range for num_rbs [6..100]. */
        uint64_t error_pdcch_res3      : 1;  /**< [ 35: 35](RO) reserved. */
        uint64_t error36_pdcch         : 1;  /**< [ 36: 36](R/W/H) invalid range for input_bit_order {0,1}. */
        uint64_t error37_pdcch         : 1;  /**< [ 37: 37](R/W/H) invalid range for input_byte_order {0,1,2}. */
        uint64_t error_epdcch_res0     : 1;  /**< [ 38: 38](RO) reserved. */
        uint64_t error39_epdcch        : 1;  /**< [ 39: 39](R/W/H) invalid range for num_edci [1..64]. */
        uint64_t error40_epdcch        : 1;  /**< [ 40: 40](R/W/H) invalid range for num_rbs [1..16]. */
        uint64_t error41_epdcch        : 1;  /**< [ 41: 41](R/W/H) invalid range for input_bit_order {0,1}. */
        uint64_t error42_epdcch        : 1;  /**< [ 42: 42](R/W/H) invalid range for input_byte_order {0,1,2}. */
        uint64_t error_epdcch_res1     : 2;  /**< [ 44: 43](RO) reserved. */
        uint64_t error45_epdcch        : 1;  /**< [ 45: 45](R/W/H) invalid range for ereg_pattern_idx0 [0..4]. */
        uint64_t error46_epdcch        : 1;  /**< [ 46: 46](R/W/H) invalid range for ereg_pattern_idx1 [0..4]. */
        uint64_t error47_epdcch        : 1;  /**< [ 47: 47](R/W/H) invalid range for ereg_pattern_idx2 [0..4]. */
        uint64_t error48_epdcch        : 1;  /**< [ 48: 48](R/W/H) invalid range for ereg_pattern_idx3 [0..4]. */
        uint64_t error49_epdcch        : 1;  /**< [ 49: 49](R/W/H) invalid range for ereg_pattern_idx4 [0..4]. */
        uint64_t error50_epdcch        : 1;  /**< [ 50: 50](R/W/H) invalid range for ereg_pattern_idx5 [0..4]. */
        uint64_t error51_epdcch        : 1;  /**< [ 51: 51](R/W/H) invalid range for ereg_pattern_idx6 [0..4]. */
        uint64_t error52_epdcch        : 1;  /**< [ 52: 52](R/W/H) invalid range for ereg_pattern_idx7 [0..4]. */
        uint64_t error53_epdcch        : 1;  /**< [ 53: 53](R/W/H) invalid range for ereg_pattern_idx8 [0..4]. */
        uint64_t error54_epdcch        : 1;  /**< [ 54: 54](R/W/H) invalid range for ereg_pattern_idx9 [0..4]. */
        uint64_t error55_epdcch        : 1;  /**< [ 55: 55](R/W/H) invalid range for ereg_pattern_idx10 [0..4]. */
        uint64_t error56_epdcch        : 1;  /**< [ 56: 56](R/W/H) invalid range for ereg_pattern_idx11 [0..4]. */
        uint64_t error57_epdcch        : 1;  /**< [ 57: 57](R/W/H) invalid range for ereg_pattern_idx12 [0..4]. */
        uint64_t error58_epdcch        : 1;  /**< [ 58: 58](R/W/H) invalid range for ereg_pattern_idx13 [0..4]. */
        uint64_t error59_epdcch        : 1;  /**< [ 59: 59](R/W/H) invalid range for ereg_pattern_idx14 [0..4]. */
        uint64_t error60_epdcch        : 1;  /**< [ 60: 60](R/W/H) invalid range for ereg_pattern_idx15 [0..4]. */
        uint64_t error_epdcch_res2     : 3;  /**< [ 63: 61](RO) reserved. */
#endif /* Word 0 - End */
    } cnf95xxp1;
    struct bdk_dencx_tc_config_err_flags_reg_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_61_63        : 3;
        uint64_t invalid_ereg_pattern_idx15 : 1;/**< [ 60: 60](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_15] value. */
        uint64_t invalid_ereg_pattern_idx14 : 1;/**< [ 59: 59](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_14] value. */
        uint64_t invalid_ereg_pattern_idx13 : 1;/**< [ 58: 58](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_13] value. */
        uint64_t invalid_ereg_pattern_idx12 : 1;/**< [ 57: 57](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_12] value. */
        uint64_t invalid_ereg_pattern_idx11 : 1;/**< [ 56: 56](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_11] value. */
        uint64_t invalid_ereg_pattern_idx10 : 1;/**< [ 55: 55](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_10] value. */
        uint64_t invalid_ereg_pattern_idx9 : 1;/**< [ 54: 54](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_9] value. */
        uint64_t invalid_ereg_pattern_idx8 : 1;/**< [ 53: 53](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_8] value. */
        uint64_t invalid_ereg_pattern_idx7 : 1;/**< [ 52: 52](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_7] value. */
        uint64_t invalid_ereg_pattern_idx6 : 1;/**< [ 51: 51](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_6] value. */
        uint64_t invalid_ereg_pattern_idx5 : 1;/**< [ 50: 50](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_5] value. */
        uint64_t invalid_ereg_pattern_idx4 : 1;/**< [ 49: 49](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_4] value. */
        uint64_t invalid_ereg_pattern_idx3 : 1;/**< [ 48: 48](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_3] value. */
        uint64_t invalid_ereg_pattern_idx2 : 1;/**< [ 47: 47](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_2] value. */
        uint64_t invalid_ereg_pattern_idx1 : 1;/**< [ 46: 46](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_1] value. */
        uint64_t invalid_ereg_pattern_idx0 : 1;/**< [ 45: 45](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_0] value. */
        uint64_t reserved_43_44        : 2;
        uint64_t invalid_epdcch_in_by_o : 1; /**< [ 42: 42](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[IN_BY_O] value. */
        uint64_t invalid_epdcch_in_bi_o : 1; /**< [ 41: 41](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[IN_BI_O] value. */
        uint64_t invalid_epdcch_nrb    : 1;  /**< [ 40: 40](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[NRB] value. */
        uint64_t invalid_epdcch_edci   : 1;  /**< [ 39: 39](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[EDCI] value. */
        uint64_t reserved_38           : 1;
        uint64_t invalid_pdcch_in_by_o : 1;  /**< [ 37: 37](RO/H) Invalid DENC_PDCCH_GEN_CFG_S[IN_BY_O] value. */
        uint64_t invalid_pdcch_in_bi_o : 1;  /**< [ 36: 36](RO/H) Invalid DENC_PDCCH_GEN_CFG_S[IN_BI_O] value. */
        uint64_t reserved_35           : 1;
        uint64_t invalid_pdcch_nrb     : 1;  /**< [ 34: 34](RO/H) Invalid DENC_PDCCH_GEN_CFG_S[NRB] value. */
        uint64_t invalid_pdcch_reg_pat : 1;  /**< [ 33: 33](RO/H) Invalid DENC_PDCCH_GEN_CFG_S[REG_PAT] value. */
        uint64_t invalid_pdcch_byps_map : 1; /**< [ 32: 32](RO/H) Invalid DENC_PDCCH_GEN_CFG_S[BYPS_MAP] value. */
        uint64_t reserved_31           : 1;
        uint64_t invalid_pdcch_quad    : 1;  /**< [ 30: 30](RO/H) Invalid DENC_PDCCH_GEN_CFG_S[QUAD] value. */
        uint64_t invalid_pdcch_pcell   : 1;  /**< [ 29: 29](RO/H) Invalid DENC_PDCCH_GEN_CFG_S[PCELL] value. */
        uint64_t reserved_28           : 1;
        uint64_t invalid_pdcch_byps_pdcch : 1;/**< [ 27: 27](RO/H) Invalid DENC_PDCCH_GEN_CFG_S[BYPS_PDCCH] value. */
        uint64_t invalid_pdcch_dci     : 1;  /**< [ 26: 26](RO/H) Invalid DENC_PDCCH_GEN_CFG_S[DCI] value. */
        uint64_t reserved_22_25        : 4;
        uint64_t invalid_pdsch_byps_scram : 1;/**< [ 21: 21](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[BYPS_SCRAM] value. */
        uint64_t invalid_pdsch_in_by_o : 1;  /**< [ 20: 20](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[IN_BY_O] value. */
        uint64_t invalid_pdsch_in_bi_o : 1;  /**< [ 19: 19](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[IN_BI_O] value. */
        uint64_t invalid_pdsch_symb_align : 1;/**< [ 18: 18](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[SYMB_ALIGN] value. */
        uint64_t invalid_pdsch_qm      : 1;  /**< [ 17: 17](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[QM] value. */
        uint64_t invalid_pdsch_nl      : 1;  /**< [ 16: 16](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[NL] value. */
        uint64_t invalid_pdsch_gamma   : 1;  /**< [ 15: 15](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[GAMMA] value. */
        uint64_t invalid_pdsch_rm_e    : 1;  /**< [ 14: 14](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[RM_E] value. */
        uint64_t invalid_pdsch_g       : 1;  /**< [ 13: 13](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[G] value. */
        uint64_t reserved_12           : 1;
        uint64_t invalid_pdsch_rv_idx  : 1;  /**< [ 11: 11](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[RV_IDX] value. */
        uint64_t invalid_pdsch_byps_rv : 1;  /**< [ 10: 10](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[BYPS_RV] value. */
        uint64_t invalid_pdsch_byps_rm : 1;  /**< [  9:  9](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[BYPS_RM] value. */
        uint64_t invalid_pdsch_byps_cb_crc : 1;/**< [  8:  8](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[BYPS_CB_CRC] value. */
        uint64_t invalid_pdsch_cb_mode : 1;  /**< [  7:  7](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[CB_MODE] value. */
        uint64_t invalid_pdsch_byps_crc : 1; /**< [  6:  6](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[BYPS_CRC] value. */
        uint64_t reserved_5            : 1;
        uint64_t invalid_pdsch_payload : 1;  /**< [  4:  4](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[PAYLOAD] value. */
        uint64_t invalid_pdsch_num_cb  : 1;  /**< [  3:  3](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[NUM_CB] value. */
        uint64_t reserved_2            : 1;
        uint64_t invalid_pdsch_k       : 1;  /**< [  1:  1](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[K] value. */
        uint64_t invalid_task_type     : 1;  /**< [  0:  0](RO/H) Invalid DENC_COMMON_CFG_S[TASK_TYPE] value. */
#else /* Word 0 - Little Endian */
        uint64_t invalid_task_type     : 1;  /**< [  0:  0](RO/H) Invalid DENC_COMMON_CFG_S[TASK_TYPE] value. */
        uint64_t invalid_pdsch_k       : 1;  /**< [  1:  1](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[K] value. */
        uint64_t reserved_2            : 1;
        uint64_t invalid_pdsch_num_cb  : 1;  /**< [  3:  3](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[NUM_CB] value. */
        uint64_t invalid_pdsch_payload : 1;  /**< [  4:  4](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[PAYLOAD] value. */
        uint64_t reserved_5            : 1;
        uint64_t invalid_pdsch_byps_crc : 1; /**< [  6:  6](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[BYPS_CRC] value. */
        uint64_t invalid_pdsch_cb_mode : 1;  /**< [  7:  7](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[CB_MODE] value. */
        uint64_t invalid_pdsch_byps_cb_crc : 1;/**< [  8:  8](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[BYPS_CB_CRC] value. */
        uint64_t invalid_pdsch_byps_rm : 1;  /**< [  9:  9](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[BYPS_RM] value. */
        uint64_t invalid_pdsch_byps_rv : 1;  /**< [ 10: 10](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[BYPS_RV] value. */
        uint64_t invalid_pdsch_rv_idx  : 1;  /**< [ 11: 11](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[RV_IDX] value. */
        uint64_t reserved_12           : 1;
        uint64_t invalid_pdsch_g       : 1;  /**< [ 13: 13](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[G] value. */
        uint64_t invalid_pdsch_rm_e    : 1;  /**< [ 14: 14](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[RM_E] value. */
        uint64_t invalid_pdsch_gamma   : 1;  /**< [ 15: 15](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[GAMMA] value. */
        uint64_t invalid_pdsch_nl      : 1;  /**< [ 16: 16](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[NL] value. */
        uint64_t invalid_pdsch_qm      : 1;  /**< [ 17: 17](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[QM] value. */
        uint64_t invalid_pdsch_symb_align : 1;/**< [ 18: 18](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[SYMB_ALIGN] value. */
        uint64_t invalid_pdsch_in_bi_o : 1;  /**< [ 19: 19](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[IN_BI_O] value. */
        uint64_t invalid_pdsch_in_by_o : 1;  /**< [ 20: 20](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[IN_BY_O] value. */
        uint64_t invalid_pdsch_byps_scram : 1;/**< [ 21: 21](RO/H) Invalid DENC_PDSCH_TASK_CFG_S[BYPS_SCRAM] value. */
        uint64_t reserved_22_25        : 4;
        uint64_t invalid_pdcch_dci     : 1;  /**< [ 26: 26](RO/H) Invalid DENC_PDCCH_GEN_CFG_S[DCI] value. */
        uint64_t invalid_pdcch_byps_pdcch : 1;/**< [ 27: 27](RO/H) Invalid DENC_PDCCH_GEN_CFG_S[BYPS_PDCCH] value. */
        uint64_t reserved_28           : 1;
        uint64_t invalid_pdcch_pcell   : 1;  /**< [ 29: 29](RO/H) Invalid DENC_PDCCH_GEN_CFG_S[PCELL] value. */
        uint64_t invalid_pdcch_quad    : 1;  /**< [ 30: 30](RO/H) Invalid DENC_PDCCH_GEN_CFG_S[QUAD] value. */
        uint64_t reserved_31           : 1;
        uint64_t invalid_pdcch_byps_map : 1; /**< [ 32: 32](RO/H) Invalid DENC_PDCCH_GEN_CFG_S[BYPS_MAP] value. */
        uint64_t invalid_pdcch_reg_pat : 1;  /**< [ 33: 33](RO/H) Invalid DENC_PDCCH_GEN_CFG_S[REG_PAT] value. */
        uint64_t invalid_pdcch_nrb     : 1;  /**< [ 34: 34](RO/H) Invalid DENC_PDCCH_GEN_CFG_S[NRB] value. */
        uint64_t reserved_35           : 1;
        uint64_t invalid_pdcch_in_bi_o : 1;  /**< [ 36: 36](RO/H) Invalid DENC_PDCCH_GEN_CFG_S[IN_BI_O] value. */
        uint64_t invalid_pdcch_in_by_o : 1;  /**< [ 37: 37](RO/H) Invalid DENC_PDCCH_GEN_CFG_S[IN_BY_O] value. */
        uint64_t reserved_38           : 1;
        uint64_t invalid_epdcch_edci   : 1;  /**< [ 39: 39](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[EDCI] value. */
        uint64_t invalid_epdcch_nrb    : 1;  /**< [ 40: 40](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[NRB] value. */
        uint64_t invalid_epdcch_in_bi_o : 1; /**< [ 41: 41](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[IN_BI_O] value. */
        uint64_t invalid_epdcch_in_by_o : 1; /**< [ 42: 42](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[IN_BY_O] value. */
        uint64_t reserved_43_44        : 2;
        uint64_t invalid_ereg_pattern_idx0 : 1;/**< [ 45: 45](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_0] value. */
        uint64_t invalid_ereg_pattern_idx1 : 1;/**< [ 46: 46](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_1] value. */
        uint64_t invalid_ereg_pattern_idx2 : 1;/**< [ 47: 47](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_2] value. */
        uint64_t invalid_ereg_pattern_idx3 : 1;/**< [ 48: 48](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_3] value. */
        uint64_t invalid_ereg_pattern_idx4 : 1;/**< [ 49: 49](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_4] value. */
        uint64_t invalid_ereg_pattern_idx5 : 1;/**< [ 50: 50](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_5] value. */
        uint64_t invalid_ereg_pattern_idx6 : 1;/**< [ 51: 51](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_6] value. */
        uint64_t invalid_ereg_pattern_idx7 : 1;/**< [ 52: 52](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_7] value. */
        uint64_t invalid_ereg_pattern_idx8 : 1;/**< [ 53: 53](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_8] value. */
        uint64_t invalid_ereg_pattern_idx9 : 1;/**< [ 54: 54](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_9] value. */
        uint64_t invalid_ereg_pattern_idx10 : 1;/**< [ 55: 55](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_10] value. */
        uint64_t invalid_ereg_pattern_idx11 : 1;/**< [ 56: 56](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_11] value. */
        uint64_t invalid_ereg_pattern_idx12 : 1;/**< [ 57: 57](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_12] value. */
        uint64_t invalid_ereg_pattern_idx13 : 1;/**< [ 58: 58](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_13] value. */
        uint64_t invalid_ereg_pattern_idx14 : 1;/**< [ 59: 59](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_14] value. */
        uint64_t invalid_ereg_pattern_idx15 : 1;/**< [ 60: 60](RO/H) Invalid DENC_EPDCCH_GEN_CFG_S[PATTERN_15] value. */
        uint64_t reserved_61_63        : 3;
#endif /* Word 0 - End */
    } cnf95xxp2;
    /* struct bdk_dencx_tc_config_err_flags_reg_cnf95xxp2 loki; */
};
typedef union bdk_dencx_tc_config_err_flags_reg bdk_dencx_tc_config_err_flags_reg_t;

static inline uint64_t BDK_DENCX_TC_CONFIG_ERR_FLAGS_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DENCX_TC_CONFIG_ERR_FLAGS_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=2))
        return 0x87e043481040ll + 0x8000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=2))
        return 0x87e043481040ll + 0x8000ll * ((a) & 0x3);
    __bdk_csr_fatal("DENCX_TC_CONFIG_ERR_FLAGS_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DENCX_TC_CONFIG_ERR_FLAGS_REG(a) bdk_dencx_tc_config_err_flags_reg_t
#define bustype_BDK_DENCX_TC_CONFIG_ERR_FLAGS_REG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DENCX_TC_CONFIG_ERR_FLAGS_REG(a) "DENCX_TC_CONFIG_ERR_FLAGS_REG"
#define busnum_BDK_DENCX_TC_CONFIG_ERR_FLAGS_REG(a) (a)
#define arguments_BDK_DENCX_TC_CONFIG_ERR_FLAGS_REG(a) (a),-1,-1,-1

/**
 * Register (RSL) denc#_tc_config_reg#
 *
 * INTERNAL: TC Task Config Registers
 *
 * TC task config registers.
 */
union bdk_dencx_tc_config_regx
{
    uint64_t u;
    struct bdk_dencx_tc_config_regx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t entry                 : 64; /**< [ 63:  0](R/W) Config bits. */
#else /* Word 0 - Little Endian */
        uint64_t entry                 : 64; /**< [ 63:  0](R/W) Config bits. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dencx_tc_config_regx_s cn9; */
    /* struct bdk_dencx_tc_config_regx_s cnf95xxp1; */
    struct bdk_dencx_tc_config_regx_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t entry                 : 64; /**< [ 63:  0](R/W/H) Config bits. */
#else /* Word 0 - Little Endian */
        uint64_t entry                 : 64; /**< [ 63:  0](R/W/H) Config bits. */
#endif /* Word 0 - End */
    } cnf95xxp2;
    /* struct bdk_dencx_tc_config_regx_cnf95xxp2 loki; */
};
typedef union bdk_dencx_tc_config_regx bdk_dencx_tc_config_regx_t;

static inline uint64_t BDK_DENCX_TC_CONFIG_REGX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DENCX_TC_CONFIG_REGX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=2) && (b<=44)))
        return 0x87e043481400ll + 0x8000ll * ((a) & 0x3) + 8ll * ((b) & 0x3f);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=2) && (b<=44)))
        return 0x87e043481400ll + 0x8000ll * ((a) & 0x3) + 8ll * ((b) & 0x3f);
    __bdk_csr_fatal("DENCX_TC_CONFIG_REGX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_DENCX_TC_CONFIG_REGX(a,b) bdk_dencx_tc_config_regx_t
#define bustype_BDK_DENCX_TC_CONFIG_REGX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_DENCX_TC_CONFIG_REGX(a,b) "DENCX_TC_CONFIG_REGX"
#define busnum_BDK_DENCX_TC_CONFIG_REGX(a,b) (a)
#define arguments_BDK_DENCX_TC_CONFIG_REGX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) denc#_tc_control_reg
 *
 * DENC Encoder Control Register
 * This register configures the internal DENC encoder core.
 */
union bdk_dencx_tc_control_reg
{
    uint64_t u;
    struct bdk_dencx_tc_control_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t single_task_chnl_en   : 1;  /**< [  4:  4](R/W) When set to 1, the core will wait until idle before accepting a new job with a different TASK_TYPE. */
        uint64_t single_task_phy_en    : 1;  /**< [  3:  3](R/W) When set to 1, the core will wait until idle before accepting a new job with a different PHY_MODE. */
        uint64_t single_task_en        : 1;  /**< [  2:  2](R/W) When set to 1, the core will always wait until idle before
                                                                 starting the next task. */
        uint64_t cfg_chk_dis           : 1;  /**< [  1:  1](R/W) When set to 1, disables configuration checks. Tasks with
                                                                 invalid configurations will still be processed. */
        uint64_t clk_gate_dis          : 1;  /**< [  0:  0](R/W) When set to 1, disables clock gating. */
#else /* Word 0 - Little Endian */
        uint64_t clk_gate_dis          : 1;  /**< [  0:  0](R/W) When set to 1, disables clock gating. */
        uint64_t cfg_chk_dis           : 1;  /**< [  1:  1](R/W) When set to 1, disables configuration checks. Tasks with
                                                                 invalid configurations will still be processed. */
        uint64_t single_task_en        : 1;  /**< [  2:  2](R/W) When set to 1, the core will always wait until idle before
                                                                 starting the next task. */
        uint64_t single_task_phy_en    : 1;  /**< [  3:  3](R/W) When set to 1, the core will wait until idle before accepting a new job with a different PHY_MODE. */
        uint64_t single_task_chnl_en   : 1;  /**< [  4:  4](R/W) When set to 1, the core will wait until idle before accepting a new job with a different TASK_TYPE. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dencx_tc_control_reg_s cn; */
};
typedef union bdk_dencx_tc_control_reg bdk_dencx_tc_control_reg_t;

static inline uint64_t BDK_DENCX_TC_CONTROL_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DENCX_TC_CONTROL_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=2))
        return 0x87e043481010ll + 0x8000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=2))
        return 0x87e043481010ll + 0x8000ll * ((a) & 0x3);
    __bdk_csr_fatal("DENCX_TC_CONTROL_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DENCX_TC_CONTROL_REG(a) bdk_dencx_tc_control_reg_t
#define bustype_BDK_DENCX_TC_CONTROL_REG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DENCX_TC_CONTROL_REG(a) "DENCX_TC_CONTROL_REG"
#define busnum_BDK_DENCX_TC_CONTROL_REG(a) (a)
#define arguments_BDK_DENCX_TC_CONTROL_REG(a) (a),-1,-1,-1

/**
 * Register (RSL) denc#_tc_error_mask_reg
 *
 * DENC Encoder Core Error Mask Register
 * This register enables internal encoder errors. Errors reported in
 * DENC()_TC_ERROR_REG will generate an error signal only when the
 * corresponding bit is set in DENC()_TC_ERROR_MASK_REG.
 */
union bdk_dencx_tc_error_mask_reg
{
    uint64_t u;
    struct bdk_dencx_tc_error_mask_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dencx_tc_error_mask_reg_s cn9; */
    struct bdk_dencx_tc_error_mask_reg_cnf95xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t reserved_12_31        : 20;
        uint64_t err_mask_pdcch        : 1;  /**< [ 11: 11](R/W) Error mask bit for PDCCH_ERR. */
        uint64_t err_mask_ramf_ra      : 1;  /**< [ 10: 10](R/W) Error mask bit for RAMF_RA_ERR. */
        uint64_t err_mask_ramf         : 1;  /**< [  9:  9](R/W) Error mask bit for RAMF_ERR. */
        uint64_t err_mask_inv_cfg      : 1;  /**< [  8:  8](R/W) Error mask bit for INV_CFG. */
        uint64_t err_mask_ramg         : 1;  /**< [  7:  7](R/W) Error mask bit for RAMG_ERR. */
        uint64_t err_mask_inv_mem_acc  : 1;  /**< [  6:  6](R/W) Error mask bit for INV_MEM_ACC. */
        uint64_t err_mask_static_wr_act : 1; /**< [  5:  5](R/W) Error mask bit for STATIC_WR_ACT. */
        uint64_t reserved_4            : 1;
        uint64_t err_mask_ign_read     : 1;  /**< [  3:  3](R/W) Error mask bit for IGN_READ. */
        uint64_t err_mask_inv_read     : 1;  /**< [  2:  2](R/W) Error mask bit for INV_READ. */
        uint64_t err_mask_inv_write    : 1;  /**< [  1:  1](R/W) Error mask bit for INV_WRITE. */
        uint64_t err_mask_inv_start    : 1;  /**< [  0:  0](R/W) Error mask bit for INV_START. */
#else /* Word 0 - Little Endian */
        uint64_t err_mask_inv_start    : 1;  /**< [  0:  0](R/W) Error mask bit for INV_START. */
        uint64_t err_mask_inv_write    : 1;  /**< [  1:  1](R/W) Error mask bit for INV_WRITE. */
        uint64_t err_mask_inv_read     : 1;  /**< [  2:  2](R/W) Error mask bit for INV_READ. */
        uint64_t err_mask_ign_read     : 1;  /**< [  3:  3](R/W) Error mask bit for IGN_READ. */
        uint64_t reserved_4            : 1;
        uint64_t err_mask_static_wr_act : 1; /**< [  5:  5](R/W) Error mask bit for STATIC_WR_ACT. */
        uint64_t err_mask_inv_mem_acc  : 1;  /**< [  6:  6](R/W) Error mask bit for INV_MEM_ACC. */
        uint64_t err_mask_ramg         : 1;  /**< [  7:  7](R/W) Error mask bit for RAMG_ERR. */
        uint64_t err_mask_inv_cfg      : 1;  /**< [  8:  8](R/W) Error mask bit for INV_CFG. */
        uint64_t err_mask_ramf         : 1;  /**< [  9:  9](R/W) Error mask bit for RAMF_ERR. */
        uint64_t err_mask_ramf_ra      : 1;  /**< [ 10: 10](R/W) Error mask bit for RAMF_RA_ERR. */
        uint64_t err_mask_pdcch        : 1;  /**< [ 11: 11](R/W) Error mask bit for PDCCH_ERR. */
        uint64_t reserved_12_31        : 20;
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cnf95xxp1;
    struct bdk_dencx_tc_error_mask_reg_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t err_mask              : 32; /**< [ 31:  0](R/W) Error mask bits. */
#else /* Word 0 - Little Endian */
        uint64_t err_mask              : 32; /**< [ 31:  0](R/W) Error mask bits. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cnf95xxp2;
    /* struct bdk_dencx_tc_error_mask_reg_cnf95xxp2 loki; */
};
typedef union bdk_dencx_tc_error_mask_reg bdk_dencx_tc_error_mask_reg_t;

static inline uint64_t BDK_DENCX_TC_ERROR_MASK_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DENCX_TC_ERROR_MASK_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=2))
        return 0x87e043481030ll + 0x8000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=2))
        return 0x87e043481030ll + 0x8000ll * ((a) & 0x3);
    __bdk_csr_fatal("DENCX_TC_ERROR_MASK_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DENCX_TC_ERROR_MASK_REG(a) bdk_dencx_tc_error_mask_reg_t
#define bustype_BDK_DENCX_TC_ERROR_MASK_REG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DENCX_TC_ERROR_MASK_REG(a) "DENCX_TC_ERROR_MASK_REG"
#define busnum_BDK_DENCX_TC_ERROR_MASK_REG(a) (a)
#define arguments_BDK_DENCX_TC_ERROR_MASK_REG(a) (a),-1,-1,-1

/**
 * Register (RSL) denc#_tc_error_reg
 *
 * DENC Encoder Error Register
 * This register reports various error conditions in the internal encoder.
 *
 * All errors reported in this register are reported as FATAL errors, and the
 * MHBW registers can be inspected to determine the job tag(s) associated with
 * the error(s).
 */
union bdk_dencx_tc_error_reg
{
    uint64_t u;
    struct bdk_dencx_tc_error_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t pdcch_err             : 1;  /**< [ 11: 11](R/W/H) PDCCH REG_MASK mapping algorithm error. */
        uint64_t ramf_ra_err           : 1;  /**< [ 10: 10](R/W/H) Read access error to REG_MASK memory F (memory empty). */
        uint64_t ramf_err              : 1;  /**< [  9:  9](R/W/H) Error in REG_MASK memory F (single error event). */
        uint64_t inv_cfg               : 1;  /**< [  8:  8](R/W/H) Invalid task configuration. Task aborted. */
        uint64_t ramg_err              : 1;  /**< [  7:  7](R/W/H) Error in REG_MASK memory G (single error event). */
        uint64_t inv_mem_acc           : 1;  /**< [  6:  6](R/W/H) Invalid access to reg_mask cfg memory while a CSR access is not done. */
        uint64_t static_wr_act         : 1;  /**< [  5:  5](R/W/H) Write to static register when core is active. */
        uint64_t reserved_4            : 1;
        uint64_t ign_read              : 1;  /**< [  3:  3](R/W/H) Ignored read access error -- one already in progress. */
        uint64_t inv_read              : 1;  /**< [  2:  2](R/W/H) Invalid read access error (out of address range). */
        uint64_t inv_write             : 1;  /**< [  1:  1](R/W/H) Invalid write access error (out of address range). */
        uint64_t inv_start             : 1;  /**< [  0:  0](R/W/H) Invalid start task error (core is busy). */
#else /* Word 0 - Little Endian */
        uint64_t inv_start             : 1;  /**< [  0:  0](R/W/H) Invalid start task error (core is busy). */
        uint64_t inv_write             : 1;  /**< [  1:  1](R/W/H) Invalid write access error (out of address range). */
        uint64_t inv_read              : 1;  /**< [  2:  2](R/W/H) Invalid read access error (out of address range). */
        uint64_t ign_read              : 1;  /**< [  3:  3](R/W/H) Ignored read access error -- one already in progress. */
        uint64_t reserved_4            : 1;
        uint64_t static_wr_act         : 1;  /**< [  5:  5](R/W/H) Write to static register when core is active. */
        uint64_t inv_mem_acc           : 1;  /**< [  6:  6](R/W/H) Invalid access to reg_mask cfg memory while a CSR access is not done. */
        uint64_t ramg_err              : 1;  /**< [  7:  7](R/W/H) Error in REG_MASK memory G (single error event). */
        uint64_t inv_cfg               : 1;  /**< [  8:  8](R/W/H) Invalid task configuration. Task aborted. */
        uint64_t ramf_err              : 1;  /**< [  9:  9](R/W/H) Error in REG_MASK memory F (single error event). */
        uint64_t ramf_ra_err           : 1;  /**< [ 10: 10](R/W/H) Read access error to REG_MASK memory F (memory empty). */
        uint64_t pdcch_err             : 1;  /**< [ 11: 11](R/W/H) PDCCH REG_MASK mapping algorithm error. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dencx_tc_error_reg_s cn9; */
    /* struct bdk_dencx_tc_error_reg_s cnf95xxp1; */
    struct bdk_dencx_tc_error_reg_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t pdcch_err             : 1;  /**< [ 11: 11](R/W1C/H) PDCCH REG_MASK mapping algorithm error. */
        uint64_t ramf_ra_err           : 1;  /**< [ 10: 10](R/W1C/H) Read access error to REG_MASK memory F (memory empty). */
        uint64_t ramf_err              : 1;  /**< [  9:  9](R/W1C/H) Error in REG_MASK memory F (single error event). */
        uint64_t inv_cfg               : 1;  /**< [  8:  8](R/W1C/H) Invalid task configuration. Task aborted. */
        uint64_t ramg_err              : 1;  /**< [  7:  7](R/W1C/H) Error in REG_MASK memory G (single error event). */
        uint64_t inv_mem_acc           : 1;  /**< [  6:  6](R/W1C/H) Invalid access to reg_mask cfg memory while a CSR access is not done. */
        uint64_t static_wr_act         : 1;  /**< [  5:  5](R/W1C/H) Write to static register when core is active. */
        uint64_t reserved_4            : 1;
        uint64_t ign_read              : 1;  /**< [  3:  3](R/W1C/H) Ignored read access error -- one already in progress. */
        uint64_t inv_read              : 1;  /**< [  2:  2](R/W1C/H) Invalid read access error (out of address range). */
        uint64_t inv_write             : 1;  /**< [  1:  1](R/W1C/H) Invalid write access error (out of address range). */
        uint64_t inv_start             : 1;  /**< [  0:  0](R/W1C/H) Invalid start task error (core is busy). */
#else /* Word 0 - Little Endian */
        uint64_t inv_start             : 1;  /**< [  0:  0](R/W1C/H) Invalid start task error (core is busy). */
        uint64_t inv_write             : 1;  /**< [  1:  1](R/W1C/H) Invalid write access error (out of address range). */
        uint64_t inv_read              : 1;  /**< [  2:  2](R/W1C/H) Invalid read access error (out of address range). */
        uint64_t ign_read              : 1;  /**< [  3:  3](R/W1C/H) Ignored read access error -- one already in progress. */
        uint64_t reserved_4            : 1;
        uint64_t static_wr_act         : 1;  /**< [  5:  5](R/W1C/H) Write to static register when core is active. */
        uint64_t inv_mem_acc           : 1;  /**< [  6:  6](R/W1C/H) Invalid access to reg_mask cfg memory while a CSR access is not done. */
        uint64_t ramg_err              : 1;  /**< [  7:  7](R/W1C/H) Error in REG_MASK memory G (single error event). */
        uint64_t inv_cfg               : 1;  /**< [  8:  8](R/W1C/H) Invalid task configuration. Task aborted. */
        uint64_t ramf_err              : 1;  /**< [  9:  9](R/W1C/H) Error in REG_MASK memory F (single error event). */
        uint64_t ramf_ra_err           : 1;  /**< [ 10: 10](R/W1C/H) Read access error to REG_MASK memory F (memory empty). */
        uint64_t pdcch_err             : 1;  /**< [ 11: 11](R/W1C/H) PDCCH REG_MASK mapping algorithm error. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cnf95xxp2;
    /* struct bdk_dencx_tc_error_reg_cnf95xxp2 loki; */
};
typedef union bdk_dencx_tc_error_reg bdk_dencx_tc_error_reg_t;

static inline uint64_t BDK_DENCX_TC_ERROR_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DENCX_TC_ERROR_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=2))
        return 0x87e043481038ll + 0x8000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=2))
        return 0x87e043481038ll + 0x8000ll * ((a) & 0x3);
    __bdk_csr_fatal("DENCX_TC_ERROR_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DENCX_TC_ERROR_REG(a) bdk_dencx_tc_error_reg_t
#define bustype_BDK_DENCX_TC_ERROR_REG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DENCX_TC_ERROR_REG(a) "DENCX_TC_ERROR_REG"
#define busnum_BDK_DENCX_TC_ERROR_REG(a) (a)
#define arguments_BDK_DENCX_TC_ERROR_REG(a) (a),-1,-1,-1

/**
 * Register (RSL) denc#_tc_main_reset_reg
 *
 * DENC Encoder Reset Register
 * This register provides a reset for the internal encoder core.
 */
union bdk_dencx_tc_main_reset_reg
{
    uint64_t u;
    struct bdk_dencx_tc_main_reset_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t soft_reset            : 1;  /**< [  0:  0](R/W/H) Any write to this register will reset the internal encoder core. */
#else /* Word 0 - Little Endian */
        uint64_t soft_reset            : 1;  /**< [  0:  0](R/W/H) Any write to this register will reset the internal encoder core. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dencx_tc_main_reset_reg_s cn; */
};
typedef union bdk_dencx_tc_main_reset_reg bdk_dencx_tc_main_reset_reg_t;

static inline uint64_t BDK_DENCX_TC_MAIN_RESET_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DENCX_TC_MAIN_RESET_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=2))
        return 0x87e043481000ll + 0x8000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=2))
        return 0x87e043481000ll + 0x8000ll * ((a) & 0x3);
    __bdk_csr_fatal("DENCX_TC_MAIN_RESET_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DENCX_TC_MAIN_RESET_REG(a) bdk_dencx_tc_main_reset_reg_t
#define bustype_BDK_DENCX_TC_MAIN_RESET_REG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DENCX_TC_MAIN_RESET_REG(a) "DENCX_TC_MAIN_RESET_REG"
#define busnum_BDK_DENCX_TC_MAIN_RESET_REG(a) (a)
#define arguments_BDK_DENCX_TC_MAIN_RESET_REG(a) (a),-1,-1,-1

/**
 * Register (RSL) denc#_tc_main_start_reg
 *
 * INTERNAL: TC Start Register
 *
 * TC start register.
 */
union bdk_dencx_tc_main_start_reg
{
    uint64_t u;
    struct bdk_dencx_tc_main_start_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t start                 : 1;  /**< [  0:  0](R/W/H) Start bit. */
#else /* Word 0 - Little Endian */
        uint64_t start                 : 1;  /**< [  0:  0](R/W/H) Start bit. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dencx_tc_main_start_reg_s cn; */
};
typedef union bdk_dencx_tc_main_start_reg bdk_dencx_tc_main_start_reg_t;

static inline uint64_t BDK_DENCX_TC_MAIN_START_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DENCX_TC_MAIN_START_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=2))
        return 0x87e043481008ll + 0x8000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=2))
        return 0x87e043481008ll + 0x8000ll * ((a) & 0x3);
    __bdk_csr_fatal("DENCX_TC_MAIN_START_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DENCX_TC_MAIN_START_REG(a) bdk_dencx_tc_main_start_reg_t
#define bustype_BDK_DENCX_TC_MAIN_START_REG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DENCX_TC_MAIN_START_REG(a) "DENCX_TC_MAIN_START_REG"
#define busnum_BDK_DENCX_TC_MAIN_START_REG(a) (a)
#define arguments_BDK_DENCX_TC_MAIN_START_REG(a) (a),-1,-1,-1

/**
 * Register (RSL) denc#_tc_mon_reg
 *
 * INTERNAL: TC Monitoring Registers
 *
 * TC mon registers.
 */
union bdk_dencx_tc_mon_reg
{
    uint64_t u;
    struct bdk_dencx_tc_mon_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t bus_val               : 16; /**< [ 15:  0](RO) Output bus monitoring values. */
#else /* Word 0 - Little Endian */
        uint64_t bus_val               : 16; /**< [ 15:  0](RO) Output bus monitoring values. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dencx_tc_mon_reg_s cn9; */
    /* struct bdk_dencx_tc_mon_reg_s cnf95xxp1; */
    struct bdk_dencx_tc_mon_reg_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t bus_val               : 16; /**< [ 15:  0](RO/H) Output bus monitoring values. */
#else /* Word 0 - Little Endian */
        uint64_t bus_val               : 16; /**< [ 15:  0](RO/H) Output bus monitoring values. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } cnf95xxp2;
    /* struct bdk_dencx_tc_mon_reg_cnf95xxp2 loki; */
};
typedef union bdk_dencx_tc_mon_reg bdk_dencx_tc_mon_reg_t;

static inline uint64_t BDK_DENCX_TC_MON_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DENCX_TC_MON_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=2))
        return 0x87e043481300ll + 0x8000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=2))
        return 0x87e043481300ll + 0x8000ll * ((a) & 0x3);
    __bdk_csr_fatal("DENCX_TC_MON_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DENCX_TC_MON_REG(a) bdk_dencx_tc_mon_reg_t
#define bustype_BDK_DENCX_TC_MON_REG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DENCX_TC_MON_REG(a) "DENCX_TC_MON_REG"
#define busnum_BDK_DENCX_TC_MON_REG(a) (a)
#define arguments_BDK_DENCX_TC_MON_REG(a) (a),-1,-1,-1

/**
 * Register (RSL) denc#_tc_static_epdcch_reg#
 *
 * TC Static E-PDCCH Config Registers
 * These registers store the EREG pattern table used for E-PDCCH symbol
 * mapping. The default values of these registers are configured for normal
 * usage in accordance with the 3GPP specifications, and there
 * should be no reason to change the default values in these registers.
 *
 * There are 5 EREG patterns corresponding to different CP modes. Each
 * pattern consists of 840 bits, and the 5 patterns are concatenated to form
 * a single vector of 4200 bits, stored in 66 x 64-bit registers.
 *
 * The combined pattern vector can be indexed as follows:
 *
 * _ vector[(840*i + 60*t + 5*(s+1) - 1):(840*i + 60*t + 5*s)] = P(i,t,s)
 *
 * Where i is the CP mode index [0,4], t is the OFDM symbol [0,13], and s is
 * the sub-carrier within the RB [0,11].
 *
 * The 5-bit pattern value selects between one of the 16 EREGs when set to a
 * value in the range [0,15], and values \> 15 indicate that no EREG is mapped
 * to that RE.
 *
 * At reset, the E-PDCCH EREG pattern table is loaded with the appropriate
 * patterns for 5 CP modes:
 * * 0x0 = Normal CP.
 * * 0x1 = Special sub-frame 3, 4, 8, 9 with normal CP.
 * * 0x2 = Special sub-frame 1, 2, 6, 7 with normal CP.
 * * 0x3 = Extended sub-frame.
 * * 0x4 = Special sub-frame 1, 2, 3, 5, 6 with extended CP.
 *
 * The DENC_EPDCCH_GEN_CFG_S[PATTERN_{0..15}] fields select one of the 5 CP
 * modes to use for each RB.
 *
 * These registers can only be written when DENC()_TC_STATUS0_REG[IDLE] = 1.
 *
 * Under normal usage, there should be no reason to
 * write these registers, either at start-up or at any other time.
 */
union bdk_dencx_tc_static_epdcch_regx
{
    uint64_t u;
    struct bdk_dencx_tc_static_epdcch_regx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t entry                 : 64; /**< [ 63:  0](R/W) EREG pattern vector bits. */
#else /* Word 0 - Little Endian */
        uint64_t entry                 : 64; /**< [ 63:  0](R/W) EREG pattern vector bits. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dencx_tc_static_epdcch_regx_s cn; */
};
typedef union bdk_dencx_tc_static_epdcch_regx bdk_dencx_tc_static_epdcch_regx_t;

static inline uint64_t BDK_DENCX_TC_STATIC_EPDCCH_REGX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DENCX_TC_STATIC_EPDCCH_REGX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=2) && (b<=65)))
        return 0x87e043481c00ll + 0x8000ll * ((a) & 0x3) + 8ll * ((b) & 0x7f);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=2) && (b<=65)))
        return 0x87e043481c00ll + 0x8000ll * ((a) & 0x3) + 8ll * ((b) & 0x7f);
    __bdk_csr_fatal("DENCX_TC_STATIC_EPDCCH_REGX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_DENCX_TC_STATIC_EPDCCH_REGX(a,b) bdk_dencx_tc_static_epdcch_regx_t
#define bustype_BDK_DENCX_TC_STATIC_EPDCCH_REGX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_DENCX_TC_STATIC_EPDCCH_REGX(a,b) "DENCX_TC_STATIC_EPDCCH_REGX"
#define busnum_BDK_DENCX_TC_STATIC_EPDCCH_REGX(a,b) (a)
#define arguments_BDK_DENCX_TC_STATIC_EPDCCH_REGX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) denc#_tc_static_pdcch_reg#
 *
 * DENC Static PDCCH Config Registers
 * These registers store information used for PDCCH resource mapping.
 *
 * Each entry contains one REG order sequence. Bits \<7:0\> store the number of
 * REG per RB. Bits \<47:8\> store the REG order sequence as an array of 20 x
 * 2-bit values (i.e., bits\<9:8\> stores the control symbol for the first REG,
 * bits\<11:10\> store the control symbol for the second REG, etc.).
 *
 * These registers can only be written when DENC()_TC_STATUS0_REG[IDLE] = 1.
 *
 * At reset, the REG order table is loaded with 9 default sequences which
 * are sufficient for supporting all functionality specified in 3GPP TS
 * 36.212. Under normal usage, there should be no reason to
 * write these registers, either at start-up or at any other time.
 */
union bdk_dencx_tc_static_pdcch_regx
{
    uint64_t u;
    struct bdk_dencx_tc_static_pdcch_regx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t entry                 : 64; /**< [ 63:  0](R/W) REG order sequence {b}. */
#else /* Word 0 - Little Endian */
        uint64_t entry                 : 64; /**< [ 63:  0](R/W) REG order sequence {b}. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dencx_tc_static_pdcch_regx_s cn; */
};
typedef union bdk_dencx_tc_static_pdcch_regx bdk_dencx_tc_static_pdcch_regx_t;

static inline uint64_t BDK_DENCX_TC_STATIC_PDCCH_REGX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DENCX_TC_STATIC_PDCCH_REGX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=2) && (b<=31)))
        return 0x87e043481800ll + 0x8000ll * ((a) & 0x3) + 8ll * ((b) & 0x1f);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=2) && (b<=31)))
        return 0x87e043481800ll + 0x8000ll * ((a) & 0x3) + 8ll * ((b) & 0x1f);
    __bdk_csr_fatal("DENCX_TC_STATIC_PDCCH_REGX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_DENCX_TC_STATIC_PDCCH_REGX(a,b) bdk_dencx_tc_static_pdcch_regx_t
#define bustype_BDK_DENCX_TC_STATIC_PDCCH_REGX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_DENCX_TC_STATIC_PDCCH_REGX(a,b) "DENCX_TC_STATIC_PDCCH_REGX"
#define busnum_BDK_DENCX_TC_STATIC_PDCCH_REGX(a,b) (a)
#define arguments_BDK_DENCX_TC_STATIC_PDCCH_REGX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) denc#_tc_status0_reg
 *
 * DENC Encoder Status Register
 * This register reports status from the internal encoder core.
 */
union bdk_dencx_tc_status0_reg
{
    uint64_t u;
    struct bdk_dencx_tc_status0_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t core_stat             : 32; /**< [ 63: 32](RO/H) reserved
                                                                 Internal:
                                                                 undocumented, core-dependent status bits. */
        uint64_t reserved_1_31         : 31;
        uint64_t idle                  : 1;  /**< [  0:  0](R/W/H) When set to 1, the encoder is idle. */
#else /* Word 0 - Little Endian */
        uint64_t idle                  : 1;  /**< [  0:  0](R/W/H) When set to 1, the encoder is idle. */
        uint64_t reserved_1_31         : 31;
        uint64_t core_stat             : 32; /**< [ 63: 32](RO/H) reserved
                                                                 Internal:
                                                                 undocumented, core-dependent status bits. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dencx_tc_status0_reg_s cn9; */
    /* struct bdk_dencx_tc_status0_reg_s cnf95xxp1; */
    struct bdk_dencx_tc_status0_reg_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t core_stat             : 32; /**< [ 63: 32](RO/H) Reserved.
                                                                 Internal:
                                                                 undocumented, core-dependent status bits. */
        uint64_t reserved_1_31         : 31;
        uint64_t idle                  : 1;  /**< [  0:  0](RO/H) When set to 1, the encoder is idle. */
#else /* Word 0 - Little Endian */
        uint64_t idle                  : 1;  /**< [  0:  0](RO/H) When set to 1, the encoder is idle. */
        uint64_t reserved_1_31         : 31;
        uint64_t core_stat             : 32; /**< [ 63: 32](RO/H) Reserved.
                                                                 Internal:
                                                                 undocumented, core-dependent status bits. */
#endif /* Word 0 - End */
    } cnf95xxp2;
    /* struct bdk_dencx_tc_status0_reg_cnf95xxp2 loki; */
};
typedef union bdk_dencx_tc_status0_reg bdk_dencx_tc_status0_reg_t;

static inline uint64_t BDK_DENCX_TC_STATUS0_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DENCX_TC_STATUS0_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=2))
        return 0x87e043481020ll + 0x8000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=2))
        return 0x87e043481020ll + 0x8000ll * ((a) & 0x3);
    __bdk_csr_fatal("DENCX_TC_STATUS0_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DENCX_TC_STATUS0_REG(a) bdk_dencx_tc_status0_reg_t
#define bustype_BDK_DENCX_TC_STATUS0_REG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DENCX_TC_STATUS0_REG(a) "DENCX_TC_STATUS0_REG"
#define busnum_BDK_DENCX_TC_STATUS0_REG(a) (a)
#define arguments_BDK_DENCX_TC_STATUS0_REG(a) (a),-1,-1,-1

/**
 * Register (RSL) denc#_tc_status1_reg
 *
 * INTERNAL: TC Status 1 Register
 *
 * TC status 1 register.
 */
union bdk_dencx_tc_status1_reg
{
    uint64_t u;
    struct bdk_dencx_tc_status1_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t core_stat             : 64; /**< [ 63:  0](RO/H) Core-dependent bits. */
#else /* Word 0 - Little Endian */
        uint64_t core_stat             : 64; /**< [ 63:  0](RO/H) Core-dependent bits. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dencx_tc_status1_reg_s cn; */
};
typedef union bdk_dencx_tc_status1_reg bdk_dencx_tc_status1_reg_t;

static inline uint64_t BDK_DENCX_TC_STATUS1_REG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DENCX_TC_STATUS1_REG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=2))
        return 0x87e043481028ll + 0x8000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=2))
        return 0x87e043481028ll + 0x8000ll * ((a) & 0x3);
    __bdk_csr_fatal("DENCX_TC_STATUS1_REG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DENCX_TC_STATUS1_REG(a) bdk_dencx_tc_status1_reg_t
#define bustype_BDK_DENCX_TC_STATUS1_REG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DENCX_TC_STATUS1_REG(a) "DENCX_TC_STATUS1_REG"
#define busnum_BDK_DENCX_TC_STATUS1_REG(a) (a)
#define arguments_BDK_DENCX_TC_STATUS1_REG(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_DENC_H__ */
