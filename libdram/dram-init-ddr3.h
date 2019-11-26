/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

extern void
perform_octeontx_ddr_sequence(bdk_node_t node, int rank_mask,
                              int ddr_interface_num, int sequence);

extern void
perform_ddr_init_sequence(bdk_node_t node, int rank_mask,
                          int ddr_interface_num);

extern int ddr_memory_preserved(bdk_node_t node);

extern uint64_t get_scramble_cfg0(bdk_node_t node, int lmc);
extern uint64_t get_scramble_cfg1(bdk_node_t node, int lmc);
extern uint64_t get_scramble_cfg2(bdk_node_t node, int lmc);

extern int
init_octeontx_ddr_interface(bdk_node_t node, const ddr_configuration_t *ddr_configuration,
                            uint32_t ddr_hertz, uint32_t cpu_hertz, uint32_t ddr_ref_hertz,
                            int board_type, int board_rev_maj, int board_rev_min,
                            int ddr_interface_num, uint32_t ddr_interface_mask);

extern void
set_vref(bdk_node_t node, int ddr_interface_num, int rank, int range, int value);

//Error Status for each Initialization routine

typedef enum {
    DRAM_INIT_ERROR_DIMMS_NOT_FOUND = -1,           //Either the config table is empty or no DIMM0
    DRAM_INIT_ERROR_ADDR_DATA_INVALID = -2,         //DIMM address (column and row) bits outside of expected range
    DRAM_INIT_ERROR_CONFIG_NOT_SUPPORTED = -3,      //DRAM not supported for this set up
    DRAM_INIT_ERROR_DESKEW_TRAINING_FAILED = -4,    //Deskew training failed restart board and retry
    DRAM_INIT_ERROR_HW_WRITE_LEVELING_FAILED = -5,  //Hardware Write Leveling did not complete correctly
} DRAM_INIT_STATUS_t;

extern int
__compute_vref_value(bdk_node_t node, int ddr_interface_num, int rankx,
                     int dimm_count, int rank_count, impedence_values_t * imp_values,
                     int is_stacked_die, int dram_connection);

extern int
compute_vref_value(bdk_node_t node, int ddr_interface_num, int rankx,
                   dram_init_data_t *init_data, dram_overrides_t *overrides);

extern unsigned short
load_dac_override(int node, int ddr_interface_num,
		  int dac_value, int byte);
extern int
read_DAC_DBI_settings(int node, int ddr_interface_num, int rank,
		      int dac_or_dbi, int *settings);
extern void
display_DAC_DBI_settings(int node, int ddr_interface_num, int rank,
                         int dac_or_dbi, int ecc_ena, int *settings, char *title);

extern void
Display_Full_MPR_Page_Location(bdk_node_t node, int ddr_interface_num,
                               int rank_mask, int page, int location);

#define RODT_OHMS_COUNT        8
#define RTT_NOM_OHMS_COUNT     8
#define RTT_NOM_TABLE_COUNT    8
#define RTT_WR_OHMS_COUNT      8
#define DIC_OHMS_COUNT         3
#define DRIVE_STRENGTH_COUNT  15

extern uint64_t hertz_to_psecs(uint64_t hertz);
extern uint64_t psecs_to_mts(uint64_t psecs);
extern uint64_t mts_to_hertz(uint64_t mts);
extern uint64_t pretty_psecs_to_mts(uint64_t psecs);

extern char *printable_rank_spec(int num_ranks, int dram_width, int spd_package);
extern int set_zqcs_interval(bdk_node_t node, int ddr_interface_num, int new_interval);


