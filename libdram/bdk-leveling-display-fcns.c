/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libdram.h"

#include "bdk-dram-init.h"

// control
#define SKIP_SKIPPING 1

/////////////////// These are the RLEVEL settings display routines

void
do_display_RL(bdk_node_t node, int ddr_interface_num,
              bdk_lmcx_rlevel_rankx_t lmc_rlevel_rank,
              int rank, int flags, int score)
{
    char score_buf[16];

    if (!dram_is_verbose(VBL_NORM))
        return;

    BDK_CSR_INIT(config, node, BDK_LMCX_CONFIG(ddr_interface_num));
    int start = 7 + config.s.ecc_ena;

    if (flags & WITH_SCORE)
	snprintf(score_buf, sizeof(score_buf), "(%d)", score);
    else {
	score_buf[0] = ' '; score_buf[1] = 0;
    }

    char *msg_buf;
    char hex_buf[20];
    if (flags & WITH_AVERAGE) {
	msg_buf = "  DELAY AVERAGES  ";
    } else if (flags & WITH_FINAL) {
	msg_buf = "  FINAL SETTINGS  ";
    } else if (flags & WITH_COMPUTE) {
	msg_buf = "  COMPUTED DELAYS ";
    } else {
	snprintf(hex_buf, sizeof(hex_buf), "0x%016lX", lmc_rlevel_rank.u);
	msg_buf = hex_buf;
    }

    bdk_lmcx_rlevel_rankx_t rlevel_rank = lmc_rlevel_rank;
    int status = lmc_rlevel_rank.s.status; // default to 8XXX
    if (bdk_is_model(OCTEONTX_CN9XXX)) { // on T96, status is in different CSR
        BDK_CSR_INIT(rlevel_ctl, node, BDK_LMCX_RLEVEL_CTL(ddr_interface_num));
        status = (rlevel_ctl.u >> (40 + (2 * rank))) & 3;
    }
    printf("N%d.LMC%d.R%d: Rlevel Rank 0x%x, %s  :",
           node, ddr_interface_num, rank, status, msg_buf);
    for (int i = start; i >= 0; i--) printf(" %5d", get_rlevel_rank_struct(&rlevel_rank, i));
    printf(" %s\n", score_buf);
}

static const char *with_rodt_canned_msgs[4] = { "          ", "SKIPPING  ", "BEST ROW  ", "BEST SCORE" };

void
__display_RL_with_RODT(bdk_node_t node, int ddr_interface_num,
                       bdk_lmcx_rlevel_rankx_t lmc_rlevel_rank, int rank, int score,
                       int nom_ohms, int rodt_ohms, int flag)
{
    const char *msg_buf;
    char set_buf[20];

    if (!dram_is_verbose(VBL_TME))
        return;

    BDK_CSR_INIT(config, node, BDK_LMCX_CONFIG(ddr_interface_num));
    int start = 7 + config.s.ecc_ena;

#if SKIP_SKIPPING
    if (flag == WITH_RODT_SKIPPING) return;
#endif
    msg_buf = with_rodt_canned_msgs[flag];
    if (nom_ohms < 0) {
        snprintf(set_buf, sizeof(set_buf), "    RODT %3d    ", rodt_ohms);
    } else {
        snprintf(set_buf, sizeof(set_buf), "NOM %3d RODT %3d", nom_ohms, rodt_ohms);
    }

    bdk_lmcx_rlevel_rankx_t rlevel_rank = lmc_rlevel_rank;
    printf("N%d.LMC%d.R%d: Rlevel %s   %s  :",
           node, ddr_interface_num, rank, set_buf, msg_buf);
    for (int i = start; i >= 0; i--) printf(" %5d", get_rlevel_rank_struct(&rlevel_rank, i));
    printf(" (%d)\n", score);

    // FIXME: does this help make the output a little easier to focus?
    if (flag == WITH_RODT_BESTSCORE) {
        VB_PRT(VBL_DEV, "-----------\n");
    }
}


// pretty-print bitmask adjuster
// Used mask of 0x0ff to always print a trailing 0,
// but we need to use all the digits for longer bitmasks
// which happen on CN9XXX.
static uint64_t
PPBM(uint64_t bm)
{
    if (bm != 0ul) {
        while ((bm & 0x00ful) == 0ul)
            bm >>= 4;
    }
    return bm;
}

void
do_display_BM(bdk_node_t node, int ddr_interface_num,
              int rank, void *bm, int flags, int ecc_ena)
{
    int *bitmasks;
    rlevel_bitmask_t *rlevel_bitmask;
    rlevel_byte_data_t *rlevel_byte;
    int ecc = !!ecc_ena;
    int start = 7 + ecc;
    int i;

    if (!dram_is_verbose(VBL_NORM))
        return;

    switch(flags) {

    case WITH_WL_BITMASKS: // wlevel_bitmask array in PACKED index order, so just print them
        bitmasks = (int *)bm;
        printf("N%d.LMC%d.R%d: Wlevel Debug Bitmasks                 :",
               node, ddr_interface_num, rank);
        for (i = start; i >= 0; i--) printf(" %05x", bitmasks[i]);
        printf("\n");
        break;

    case WITH_RL_BITMASKS: // rlevel_bitmask array in PACKED index order, so just print them
        rlevel_bitmask = (rlevel_bitmask_t *)bm;
        printf("N%d.LMC%d.R%d: Rlevel Debug Bitmasks        %d:0      :",
               node, ddr_interface_num, rank, start);
        for (i = start; i >= 0; i--) printf(" %05lx", PPBM(rlevel_bitmask[i].bm));
        printf("\n");
        break;

    case WITH_RL_MASK_SCORES: // rlevel_bitmask array in PACKED index order, so just print them
        rlevel_bitmask = (rlevel_bitmask_t *)bm;
        printf("N%d.LMC%d.R%d: Rlevel Debug Bitmask Scores  %d:0      :",
               node, ddr_interface_num, rank, start);
        for (i = start; i >= 0; i--) printf(" %5d", rlevel_bitmask[i].errs);
        printf("\n");
        break;

    case WITH_RL_SEQ_SCORES: // rlevel_byte array in UNPACKED index order, so xlate and print them
        rlevel_byte = (rlevel_byte_data_t *)bm;
        printf("N%d.LMC%d.R%d: Rlevel Debug Non-seq Scores  %d:0      :",
               node, ddr_interface_num, rank, start);
        for (i = start; i >= 0; i--) printf(" %5d", rlevel_byte[XPU(i,ecc)].sqerrs);
        printf("\n");
        break;
    }
}

void
do_display_WL(bdk_node_t node, int ddr_interface_num,
              bdk_lmcx_wlevel_rankx_t lmc_wlevel_rank, int rank, int flags)
{
    char *msg_buf;
    char hex_buf[20];
    int vbl, i;

    if (!dram_is_verbose(VBL_NORM))
        return;

    BDK_CSR_INIT(config, node, BDK_LMCX_CONFIG(ddr_interface_num));
    int start = 7 + config.s.ecc_ena;

    if (flags & WITH_FINAL) {
	msg_buf = " HW FINAL SETTINGS ";
        vbl = VBL_NORM;
    } else {
	snprintf(hex_buf, sizeof(hex_buf), "0x%016lX", lmc_wlevel_rank.u);
	msg_buf = hex_buf;
        vbl = VBL_FAE;
    }

    if (!dram_is_verbose(vbl))
        return;

    bdk_lmcx_wlevel_rankx_t wlevel_rank = lmc_wlevel_rank;
    printf("N%d.LMC%d.R%d: Wlevel Rank 0x%x, %s : ",
           node, ddr_interface_num, rank, wlevel_rank.s.status, msg_buf);
    for (i = start; i >= 0; i--) printf(" %2d   ", get_wlevel_rank_struct(&wlevel_rank, i));
    printf("\n");
}

void
do_display_WL_PBM(bdk_node_t node, int ddr_interface_num,
                  bdk_lmcx_wlevel_rankx_t lmc_wlevel_rank,
                  int *bitmasks, int rank, int flags)
{
    char *msg_buf;
    char hex_buf[20];
    const char pbmstr[8] = "X|+*P#@$";
    int vbl, i, count, delay;

    if (!dram_is_verbose(VBL_NORM))
        return;

    BDK_CSR_INIT(config, node, BDK_LMCX_CONFIG(ddr_interface_num));
    int start = 7 + config.s.ecc_ena;

    if (flags & WITH_FINAL) {
	msg_buf = "  FINAL SETTINGS  ";
        vbl = VBL_NORM;
    } else {
	snprintf(hex_buf, sizeof(hex_buf), "0x%016lX", lmc_wlevel_rank.u);
	msg_buf = hex_buf;
        vbl = VBL_FAE;
    }

    if (!dram_is_verbose(vbl))
        return;

    printf("N%d.LMC%d.R%d: Wlevel Rank 0x%x, %s  : ",
           node, ddr_interface_num, rank,
           lmc_wlevel_rank.s.status, msg_buf);

    for (i = start; i >= 0; i--) {
        count = __builtin_popcount(bitmasks[i]) & 7;
        delay = get_wlevel_rank_struct(&lmc_wlevel_rank, i);
        printf(" %2d%c  ", delay, pbmstr[count]);
    }
    printf("\n");
}
