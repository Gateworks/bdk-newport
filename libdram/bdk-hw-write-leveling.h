/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

// define how many HW WL samples to take for majority voting
// MUST BE odd!!
// assume there should only be 2 possible values that will show up,
// so treat ties as a problem!!!
#define WLEVEL_LOOPS_DEFAULT     11 // NOTE: do not change this without checking the code!!!

#define HWL_BY_BYTE 0 // FIXME? set to 1 to do HWL a byte at a time (seemed to work better earlier?)

// Find a HWL majority
typedef struct {
    int16_t bitcnt[8];
} wlevel_bitcnt_t;

typedef struct {
    wlevel_bitcnt_t bytecnt[9];
} wlevel_bytecnt_t;

typedef struct {
    uint16_t hwl_alt_mask; // mask of bytelanes with alternate
    uint16_t  hwl_alt_delay[9]; // bytelane alternate avail if mask=1
} hwl_alt_by_rank_t;

typedef struct {
    uint16_t dqs1_mask_up; // mask of bytelanes wanting UP adjustment
    uint16_t dqs1_mask_dn; // mask of bytelanes wanting DOWN adjustment
} hwl_dqs1_by_rank_t;

typedef struct {
    wlevel_bytecnt_t        wlevel_bytes[3];
    wlevel_bytecnt_t        wlevel_bytes_pbm[3];
    bdk_lmcx_wlevel_rankx_t lmc_wlevel_rank;
    bdk_lmcx_wlevel_ctl_t   wlevel_ctl;
    int                     wlevel_bitmask_errors;
    int                     wlevel_bitmask[9];
    hwl_alt_by_rank_t       hwl_alts[4];
    hwl_dqs1_by_rank_t      hwl_dqs1[4];
} hw_wr_level_data_t;

extern void
update_wlevel_rank_struct(bdk_lmcx_wlevel_rankx_t *lmc_wlevel_rank, int byte, int delay);

extern int
get_wlevel_rank_struct(bdk_lmcx_wlevel_rankx_t *lmc_wlevel_rank, int byte);

extern void
Run_HW_Write_Leveling(bdk_node_t node, int ddr_interface_num,
                      dram_init_data_t *init_data, dram_overrides_t *overrides,
                      hw_wr_level_data_t *hw_wr_level_data);

