/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#define DDR_CFG_T_MAX_LMCS 4

typedef struct {
    const dimm_odt_config_t *odt_config;    //In ddr_configuration_t
    uint8_t default_rtt_nom[4];
    uint8_t default_rodt_ctl;
    uint8_t dyn_rtt_nom_mask;
    uint8_t ddr_rtt_nom_auto;                   //was in ddr_configuration_t
    uint8_t ddr_rodt_ctl_auto;                  //was in ddr_configuration_t
    uint8_t odt_idx;
} termination_data_t;

typedef struct {
    uint64_t eclk_psecs;
    uint64_t tclk_psecs;
    uint64_t ddr_hertz;
    uint32_t cpu_hertz;
    uint32_t ddr_ref_hertz;
    uint32_t CL;
    uint32_t mem_size_mbytes;
    int16_t ddr_interface_bytemask;
    uint8_t ddr_interface_64b;
    uint8_t ddr_interface_mask;
    uint8_t rank_mask;
    uint8_t num_ranks;                      //Comes from ddr_overrides_t
    uint8_t num_banks;
    uint8_t dimm_count;
    uint8_t use_ecc;
    uint8_t bunk_enable;
    uint8_t dram_width;
    uint8_t spd_rdimm;
    uint8_t spd_lrdimm;
    uint8_t spd_dimm_type;
    uint8_t wlevel_loops;
    ddr_type_t ddr_type;                    //Comes from
} dram_config_reference_t;

//SPD Data decoded from SPD table
typedef struct {
    const char *dimm_type_name;
    uint32_t die_capacity;                   // in Mbits; only used for 3DS
    uint8_t spd_addr;
    uint8_t spd_org;
    uint8_t spd_banks;
    uint8_t spd_ecc;
    uint8_t spd_package;
    uint8_t spd_rawcard;
    uint8_t spd_thermal_sensor;
    uint8_t spd_rdimm_registers;
    uint8_t spd_rawcard_AorB;
    uint8_t is_stacked_die;
    uint8_t is_3ds_dimm;                    // 3DS
    uint8_t lranks_per_prank;               // 3DS: logical ranks per package rank
    uint8_t lranks_bits;                    // 3DS: logical ranks bits
    uint8_t pbank_lsb;
    uint8_t row_lsb;
    uint8_t row_bits;
    uint8_t col_bits;
    uint8_t bank_bits;
} spd_data_t;

typedef struct {
    int twr;
    int trcd;
    int trrd;
    int trp;
    int tras;
    int trc;
    int trfc;
    int twtr;
    int trtp;  /* quiet */
    int tfaw;
    int tAAmin;
    int tCKmin;
    int ddr4_tRRD_Lmin;
    int ddr4_tCCD_Lmin;
    int spd_addr_mirror;
} ddr_timing_data_t;

struct impedence_values_s {
    unsigned char *rodt_ohms;
    unsigned char *rtt_nom_ohms;
    unsigned char *rtt_nom_table;
    unsigned char *rtt_wr_ohms;
    unsigned char *dic_ohms;
    short         *drive_strength;
    short         *dqx_strength;
};
// this is already forward typedef'd...
// typedef struct impedence_values_s impedence_values_t;

/* DRAM Config Variables for Init */
struct dram_init_data_s {
    impedence_values_t          *imp_values;        //Impedence Ohm Vals
    const ddr_configuration_t   *ddr_configuration; //DRAM config info used by BDK
    termination_data_t          terms;              //Termination variables
    dram_config_reference_t     refs;               //Reference variables describing configuration
    spd_data_t                  spd;                //Data read from the SPD
    ddr_timing_data_t           timing;             //Timing variables
};
// this is already forward typedef'd...
// typedef struct dram_init_data_s dram_init_data_t;

struct ddr_overrides_s {
    int deskew_validation_delay;
    uint8_t restart_if_dsk_incomplete;
    uint8_t disable_sequential_delay_check;
    uint8_t ddr_disable_chip_reset;
    uint8_t disable_deskew_training;
    uint8_t disable_stacked_die;
    uint8_t force_2x_refresh;
    /* Allow the Write bit-deskew feature to be enabled when desired. */
    // NOTE: THUNDER pass 2.x only, 81xx, 83xx, and 9xxx
    uint8_t enable_write_deskew;
    uint8_t safe_ddr_flag;                  // Flag that indicates safe DDR settings should be used
    uint8_t enable_by_rank_init;            // FIXME: default by-rank ON
    uint8_t num_ranks;
    uint8_t default_lock_retry_limit;       // <<--- Global Variable?
    uint8_t double_vref_training;
    uint8_t enable_x4_hwl_adj;
    uint8_t dbi_mode;
    uint8_t parity_mode;
    uint8_t data_invert;
    uint8_t use_scramble;
};
// this is already forward typedef'd...
// typedef struct ddr_overrides_s ddr_overrides_t;

//Get HW WR Leveling Specific Overrides
typedef struct {
    uint8_t ddr_wlevel_roundup;
    uint8_t ddr_wlevel_printall;
    uint8_t disable_hwl_validity;
    uint8_t default_wlevel_rtt_nom;
    uint8_t match_wlevel_rtt_nom;
    uint8_t ddr_wlevel_ctl_or_dis;
    uint8_t ddr_wlevel_ctl_bitmask;
} hw_wr_leveling_overrides_t;


typedef struct {
    uint64_t rlevel_ctl;                            //In ddr_configuration_t? ctl_ctl?
    uint32_t pbm_rodt_skip;
    int16_t rldelay_bump_incr;
    uint8_t disable_rank_majority;
    uint8_t pbm_lowsum_limit;
    uint8_t ddr_rlevel_2t;
    uint8_t rlevel_comp_offset;                         //In ddr_configuration_t rlevel_comp_offset_udimm/rdimm
    uint8_t enable_rldelay_bump;
    uint8_t rlevel_debug_loops;                         //In ddr_configuration_t? rlevel_average_loops
    uint8_t rlevel_samples;
    uint8_t ddr_rlevel_compute;
    uint8_t min_rodt_ctl;                               //In ddr_configuration_t
    uint8_t max_rodt_ctl;                               //In ddr_configuration_t
    uint8_t min_rtt_nom_idx;                            //In ddr_configuration_t
    uint8_t max_rtt_nom_idx;                            //In ddr_configuration_t
    uint8_t maximum_adjacent_rlevel_delay_increment;    //In ddr_configuration_t
    uint8_t saved_ddr__ptune;
    uint8_t saved_ddr__ntune;
    uint8_t override_compensation;
    uint8_t disable_rlv_bump_this_byte;
    uint8_t disable_rl_pbm_counting;
    uint8_t rlevel_separate_ab;
} hw_rd_leveling_overrides_t;


typedef struct {
    uint8_t sw_wlevel_enable;
    uint8_t measured_vref_flag;
    uint8_t vref_value;
    uint8_t dram_connection;
} sw_wr_leveling_overrides_t;

/* DRAM Initialization Overrides */
struct dram_overrides_s{
    ddr_overrides_t             init;
    hw_wr_leveling_overrides_t  hw_wlevel;
    hw_rd_leveling_overrides_t  hw_rlevel;
    sw_wr_leveling_overrides_t  sw_wlevel;
};
// this is already forward typedef'd...
// typedef struct dram_overrides_s dram_overrides_t;
