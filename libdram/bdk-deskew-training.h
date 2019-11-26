/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

#define ALL_BYTES 0x0A
#define BS_NOOP  0x09
#define BS_RESET 0x0F
#define BS_REUSE 0x0A

#define DSKVAL_INCR 4
#define DEFAULT_INTERNAL_VREF_TRAINING_LIMIT 3 // was 5

typedef struct {
    uint8_t count[8];
    uint8_t start[8];
    uint8_t best_count[8];
    uint8_t best_start[8];
} deskew_bytelane_t;
typedef struct {
    deskew_bytelane_t bytes[9];
} deskew_rank_t;

#define DEFAULT_DAC_SAMPLES 7 // originally was 5
#define DAC_RETRIES_LIMIT   2

#define MIN_BITVAL  17
#define MAX_BITVAL  99  // FIXME? was 110

#define DESKEW_TRAINING_FAILED_RESTART_POSSIBLE 0
#define DESKEW_TRAINING_COMPLETED 1

#define DEFAULT_SAT_RETRY_LIMIT    8
#define DEFAULT_LOCK_RETRY_LIMIT  40

#define DEFAULT_DESKEW_VALIDATION_DELAY 10000

typedef struct {
    int16_t bytes[DEFAULT_DAC_SAMPLES];
} bytelane_sample_t;

typedef struct {
    uint16_t bits[11]; // 8 bits + DAC + DBI + bytelane errs
} deskew_bytes_t;

typedef struct {
    deskew_bytes_t bytes[9];
} deskew_data_t;

typedef struct {
    bytelane_sample_t lanes[9];
    int dac_settings[9];
    int print_DAC_DBI_settings;
    int total_dac_eval_retries;
    int dac_eval_exhausted;
    int rank_mask;
#if ALLOW_BY_RANK_INIT
    int by_rank;
#endif
} dram_training_data_t;

extern void
Get_Deskew_Settings(bdk_node_t node, int ddr_interface_num, int rank, deskew_data_t *dskdat);

#if ALLOW_BY_RANK_INIT

extern void
process_by_rank_dac(bdk_node_t node, int ddr_interface_num,
                    int rank_mask, dac_data_t *dacdat);

extern void
process_by_rank_dsk(bdk_node_t node, int ddr_interface_num,
                    int rank_mask, deskew_data_t *dskdat);

#endif /* ALLOW_BY_RANK_INIT */

extern int
Validate_Read_Deskew_Training(bdk_node_t node, int ddr_interface_num, int rank_mask,
                              deskew_counts_t *counts, int print_enable, char *print_str);

// Evaluate the DAC settings array
extern int
evaluate_DAC_settings(int ddr_interface_64b, int ecc_ena, int *settings);

extern int
process_samples_average(int16_t *bytes, int num_samples, int lmc, int lane_no);

extern int
Perform_Read_Deskew_Training(bdk_node_t node, int rank_mask, int ddr_interface_num,
                             dram_init_data_t *init_data, dram_overrides_t *overrides,
                             int print_flags);

extern int
Perform_Read_Deskew_Training_rank(bdk_node_t node, int rank_mask,
                                  int ddr_interface_num,
                                  dram_init_data_t *init_data,
                                  dram_overrides_t *overrides,
                                  int print_flags);

extern void
Perform_Write_Deskew_Training(bdk_node_t node, int ddr_interface_num);

extern void
Neutral_Write_Deskew_Setup(bdk_node_t node, int ddr_interface_num, int rank_mask);

// Display_Deskew_Settings: mode parameter
#define RD_DSK  0
#define WR_DSK  1

extern void
Display_Deskew_Settings(bdk_node_t node, int ddr_interface_num, int rank,
                        deskew_data_t *dskdat, int mode, int print_enable,
                        char *print_str);

extern void
change_rdimm_mpr_pattern (bdk_node_t node, int rank_mask,
                          int ddr_interface_num, int dimm_count);

extern int
change_wr_deskew_ena(bdk_node_t node, int ddr_interface_num, int new_state);

extern int
Perform_DRAM_Training(bdk_node_t node,  int ddr_interface_num,
                      dram_init_data_t *init_data,
                      dram_overrides_t *overrides);
extern void
Modify_Read_Deskew(bdk_node_t node, int ddr_interface_num,
                   int rank, int mode, int value);
