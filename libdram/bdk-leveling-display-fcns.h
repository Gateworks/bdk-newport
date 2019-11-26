#ifndef __BDK_LEVELING_DISPLAY_FCNS_H__
#define __BDK_LEVELING_DISPLAY_FCNS_H__
/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

// flag values
#define WITH_RODT_BLANK      0
#define WITH_RODT_SKIPPING   1
#define WITH_RODT_BESTROW    2
#define WITH_RODT_BESTSCORE  3

// flags for read and write Leveling
#define WITH_NOTHING 0
#define WITH_SCORE   1
#define WITH_AVERAGE 2
#define WITH_FINAL   4
#define WITH_COMPUTE 8

/////////////////// These are the RLEVEL settings display routines

extern void
do_display_RL(bdk_node_t node, int ddr_interface_num,
              bdk_lmcx_rlevel_rankx_t lmc_rlevel_rank,
              int rank, int flags, int score);

static inline void
display_RL(bdk_node_t node, int ddr_interface_num,
           bdk_lmcx_rlevel_rankx_t lmc_rlevel_rank, int rank)
{
    do_display_RL(node, ddr_interface_num, lmc_rlevel_rank, rank, 0, 0);
}

static inline void
display_RL_with_score(bdk_node_t node, int ddr_interface_num,
                      bdk_lmcx_rlevel_rankx_t lmc_rlevel_rank, int rank, int score)
{
    do_display_RL(node, ddr_interface_num, lmc_rlevel_rank, rank, 1, score);
}

static inline void
display_RL_with_final(bdk_node_t node, int ddr_interface_num,
                      bdk_lmcx_rlevel_rankx_t lmc_rlevel_rank, int rank)
{
    do_display_RL(node, ddr_interface_num, lmc_rlevel_rank, rank, 4, 0);
}

static inline void
display_RL_with_computed(bdk_node_t node, int ddr_interface_num,
                         bdk_lmcx_rlevel_rankx_t lmc_rlevel_rank, int rank, int score)
{
    do_display_RL(node, ddr_interface_num, lmc_rlevel_rank, rank, 9, score);
}

extern void
__display_RL_with_RODT(bdk_node_t node, int ddr_interface_num,
                       bdk_lmcx_rlevel_rankx_t lmc_rlevel_rank, int rank, int score,
                       int nom_ohms, int rodt_ohms, int flag);

static inline void
display_RL_with_RODT(bdk_node_t node, int ddr_interface_num,
                     bdk_lmcx_rlevel_rankx_t lmc_rlevel_rank, int rank, int score,
                     int nom_ohms, int rodt_ohms, int flag)
{
    __display_RL_with_RODT(node, ddr_interface_num, lmc_rlevel_rank, rank, score,
				 nom_ohms, rodt_ohms, flag);
}

// bitmask routines flag values
#define WITH_WL_BITMASKS      0
#define WITH_RL_BITMASKS      1
#define WITH_RL_MASK_SCORES   2
#define WITH_RL_SEQ_SCORES    3

extern void
do_display_BM(bdk_node_t node, int ddr_interface_num,
              int rank, void *bm, int flags, int ecc_ena);

static inline void
display_WL_BM(bdk_node_t node, int ddr_interface_num, int rank, int *bitmasks, int ecc_ena)
{
    do_display_BM(node, ddr_interface_num, rank, (void *)bitmasks, WITH_WL_BITMASKS, ecc_ena);
}

static inline void
display_RL_BM(bdk_node_t node, int ddr_interface_num, int rank,
              rlevel_bitmask_t *bitmasks, int ecc_ena)
{
    do_display_BM(node, ddr_interface_num, rank, (void *)bitmasks, WITH_RL_BITMASKS, ecc_ena);
}

static inline void
display_RL_BM_scores(bdk_node_t node, int ddr_interface_num, int rank,
                     rlevel_bitmask_t *bitmasks, int ecc_ena)
{
    do_display_BM(node, ddr_interface_num, rank, (void *)bitmasks, WITH_RL_MASK_SCORES, ecc_ena);
}

static inline void
display_RL_SEQ_scores(bdk_node_t node, int ddr_interface_num, int rank,
                      rlevel_byte_data_t *bytes, int ecc_ena)
{
    do_display_BM(node, ddr_interface_num, rank, (void *)bytes, WITH_RL_SEQ_SCORES, ecc_ena);
}

extern void
do_display_WL(bdk_node_t node, int ddr_interface_num,
              bdk_lmcx_wlevel_rankx_t lmc_wlevel_rank, int rank, int flags);

static inline void
display_WL(bdk_node_t node, int ddr_interface_num,
           bdk_lmcx_wlevel_rankx_t lmc_wlevel_rank, int rank)
{
    do_display_WL(node, ddr_interface_num, lmc_wlevel_rank, rank, WITH_NOTHING);
}

static inline void
display_WL_with_final(bdk_node_t node, int ddr_interface_num,
                      bdk_lmcx_wlevel_rankx_t lmc_wlevel_rank, int rank)
{
    do_display_WL(node, ddr_interface_num, lmc_wlevel_rank, rank, WITH_FINAL);
}

extern void
do_display_WL_PBM(bdk_node_t node, int ddr_interface_num,
                  bdk_lmcx_wlevel_rankx_t lmc_wlevel_rank,
                  int *bitmasks, int rank, int flags);

#endif /* __BDK_LEVELING_DISPLAY_FCNS_H__ */
