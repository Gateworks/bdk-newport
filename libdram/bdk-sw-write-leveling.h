/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

// How is the DRAM connected: 0 = DIMM, 1 = discrete DRAM
// FIXME: gotta be global so we do not have to pass a new param
//int dram_connection;

typedef enum {
    WL_ESTIMATED = 0,   /* HW/SW wleveling failed. Results
                           estimated. */
    WL_HARDWARE  = 1,   /* H/W wleveling succeeded */
    WL_SOFTWARE  = 2,   /* S/W wleveling passed 2 contiguous
                           settings. */
    WL_SOFTWARE1 = 3,   /* S/W wleveling passed 1 marginal
                           setting. */
} sw_wl_status_t;

typedef struct{
    char best_vref_values_count;
    char best_vref_values_start;
    int computed_final_vref_value;
    int active_rank;
    int sw_wl_failed;
    int interfaces;
    sw_wl_status_t *byte_test_status;
    bdk_lmcx_wlevel_rankx_t lmc_wlevel_rank;
    hwl_alt_by_rank_t *hwl_alts;
} sw_wr_data_t;

extern int
Perform_Sofware_Write_Leveling(bdk_node_t node, int ddr_interface_num,
                               dram_init_data_t *init_data,
                               dram_overrides_t *overrides,
                               hw_wr_level_data_t *hw_wl_data);
