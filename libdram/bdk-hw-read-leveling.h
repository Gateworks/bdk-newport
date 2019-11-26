/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

#define RLEVEL_BITMASK_TRAILING_BITS_ERROR      5
#define RLEVEL_BITMASK_BUBBLE_BITS_ERROR        11 // FIXME? now less than TOOLONG
#define RLEVEL_BITMASK_NARROW_ERROR             6
#define RLEVEL_BITMASK_BLANK_ERROR              100
#define RLEVEL_BITMASK_TOOLONG_ERROR            12

// Set to 1 to process DDR4 RDIMM read-leveling via separate sides (A and B)
#define DEFAULT_RLEVEL_SEPARATE_AB 0

#define PERFECT_BITMASK_COUNTING   1
#define PRINT_PERFECT_COUNTS       PERFECT_BITMASK_COUNTING && 1

#if PERFECT_BITMASK_COUNTING
typedef struct {
    uint8_t count[9][64]; // 8+ECC by 64 values
    uint64_t mask[9];     // 8+ECC, bitmask of perfect delays
} perfect_counts_t;
#endif /* PERFECT_BITMASK_COUNTING */

typedef struct {
    uint64_t setting;
    int      score;
} rlevel_scores_t;

typedef struct {
    rlevel_scores_t scoreboard[RTT_NOM_OHMS_COUNT][RODT_OHMS_COUNT][4];
} rlevel_scoreboard_t;

typedef struct {
    int rank_score;
    int rank_rtt_nom;
    int rank_ctl;
    int rank_ohms;
    int rankx;
} rlevel_best_settings_t;

typedef struct {
    int count_more;
    int count_same;
    int count_less;
    int rank_more;
    int rank_same;
    int rank_less;
} rlevel_best_byte_count_results_t;

typedef struct {
    rlevel_byte_data_t rlevel_byte[9];
    rlevel_bitmask_t rlevel_bitmask[9];
#if PERFECT_BITMASK_COUNTING
    perfect_counts_t rank_perfect_counts[4];
    perfect_counts_t rodt_perfect_counts;
#endif /* PERFECT_BITMASK_COUNTING */
} hw_rlevel_data_t;

typedef struct {
    rlevel_scoreboard_t rlevel_scoreboard;
    rlevel_best_settings_t best;
    rlevel_best_byte_count_results_t count_results;
    hw_rlevel_data_t rlevel_data;
    int dimm_rank_mask;
    int rodt_row_skip_mask;
    int MAX_RANK_SCORE;
#if PERFECT_BITMASK_COUNTING
    int new_byte;
#endif /* PERFECT_BITMASK_COUNTING */
} rlevel_struct_t;

extern void
Perform_Read_Leveling(bdk_node_t node, int ddr_interface_num,
                      dram_init_data_t *init_data,
                      dram_overrides_t *overrides);
