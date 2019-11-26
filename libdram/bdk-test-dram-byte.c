/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-l2c.h"
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libdram.h"
#include "dram-internal.h"

#include "libbdk-dram/bdk-ccs-addr-decode.h"

/////////////
// scheme to utilize a large number of rows without
// over-using a small number
//
// BASE needs to be high enough to not corrupt BDK
// LAST defines the total number of rows to be used
// TODO is how many rows to be done per call
// 
#define BASE_ROW  0x0800
#define LAST_ROW  0x1000
#define ROWS_TODO 32
/////////////

// NOTE: "mode" argument:
//         DBTRAIN_TEST: for testing using GP patterns, includes ECC
//         DBTRAIN_DBI:  for DBI deskew training behavior (use LFSR patterns)
//         DBTRAIN_LFSR: for testing using LFSR patterns, includes ECC
// NOTE: trust the caller to specify the correct/supported mode
//
// pass in explicit rank to test, not a phys addr...
int test_dram_byte_hw_rank(bdk_node_t node, int lmc, int rankx,
                           int mode, uint64_t *xor_data)
{
    int errors;

    uint64_t mpr_data0, mpr_data1;
    uint64_t bad_bits[2] = {0,0};

    int prank, lrank;
    int row, col;
    int save_or_dis;
    int byte;
    int bg, ba;

    static int cur_row = BASE_ROW;

    bdk_lmcx_rlevel_ctl_t rlevel_ctl;
    bdk_lmcx_dbtrain_ctl_t dbtrain_ctl;
    bdk_lmcx_config_t config;
    int mode32b;

    int bank_errs;
    int is_cn8xxx = bdk_is_model(OCTEONTX_CN8XXX);
    int use_lfsr = (mode == DBTRAIN_LFSR) || (mode == DBTRAIN_DBI); 

    config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(lmc));
    mode32b = config.s.mode32b;

    /* 1) Make sure that RLEVEL_CTL[OR_DIS] = 0.
    */
    rlevel_ctl.u = BDK_CSR_READ(node, BDK_LMCX_RLEVEL_CTL(lmc));
    save_or_dis = rlevel_ctl.s.or_dis;
    rlevel_ctl.s.or_dis = 0;    /* or_dis must be disabled for this sequence */
    DRAM_CSR_WRITE(node, BDK_LMCX_RLEVEL_CTL(lmc), rlevel_ctl.u);

    /* NOTE: this step done in the calling routine(s)
      3) Setup GENERAL_PURPOSE[0-2] registers with the data pattern of choice.
        a. GENERAL_PURPOSE0[DATA<63:0>] – sets the initial lower (rising edge) 64 bits of data.
        b. GENERAL_PURPOSE1[DATA<63:0>] – sets the initial upper (falling edge) 64 bits of data.
        c. GENERAL_PURPOSE2[DATA<15:0>] – sets the initial lower (rising edge <7:0>) and upper
           (falling edge <15:8>) ECC data.
     */

    errors = 0;
   
    VB_PRT(VBL_DEV2, "N%d: test_dram_byte_hw_rank: START at LMC%d rank %d\n",
           node, lmc, rankx);

    /* 7) Set PHY_CTL[PHY_RESET] = 1 (LMC automatically clears this as it’s a one-shot operation).
          This is to get into the habit of resetting PHY’s SILO to the original 0 location.
    */
    BDK_CSR_MODIFY(phy_ctl, node, BDK_LMCX_PHY_CTL(lmc),
		   phy_ctl.s.phy_reset = 1);

    /* Walk through a range of addresses on the given rank.
       Base outer loop on interating via the "row" param to DBTRAIN.
     */
    ba = 0;
    bg = 0;
    col = 0;
    lrank = 0;
    prank = rankx;

    /* 2) Setup the fields of the CSR DBTRAIN_CTL as follows:
        a. COL, ROW, BA, BG, PRANK points to the starting point of the address.
           You can just set them to all 0.
        b. RW_TRAIN – set this to 1.
        c. TCCD_L – set this to 0.
        d. READ_CMD_COUNT – instruct the sequence to the how many writes/reads.
           It is 5 bits field, so set to 31 of maximum # of r/w.
    */

    dbtrain_ctl.u = 0;

    if (is_cn8xxx) {
        dbtrain_ctl.cn83xx.column_a         = col;
        dbtrain_ctl.cn83xx.ba               = ba;
        dbtrain_ctl.cn83xx.bg               = bg;
        dbtrain_ctl.cn83xx.prank            = prank;
        dbtrain_ctl.cn83xx.lrank            = lrank; // FIXME?
        dbtrain_ctl.cn83xx.activate         = 1; // was: (mode == DBTRAIN_DBI);
        dbtrain_ctl.cn83xx.write_ena        = 1;
        dbtrain_ctl.cn83xx.read_cmd_count   = 31; // max count pass 5 bits
        dbtrain_ctl.cn83xx.cmd_count_ext    = 3;  // also 2 more bits
        dbtrain_ctl.cn83xx.rw_train         = 1;
        dbtrain_ctl.cn83xx.tccd_sel         = 1; // was: (mode == DBTRAIN_DBI);
        dbtrain_ctl.cn83xx.lfsr_pattern_sel = use_lfsr;
    }
    else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */ {
        dbtrain_ctl.cn9.column_a            = col;
        dbtrain_ctl.cn9.ba                  = ba;
        dbtrain_ctl.cn9.bg                  = bg;
        dbtrain_ctl.cn9.prank1              = prank;
        dbtrain_ctl.cn9.prank2              = prank;
        dbtrain_ctl.cn9.lrank               = lrank; // FIXME?
        dbtrain_ctl.cn9.activate            = 1; // was: (mode == DBTRAIN_DBI);
        dbtrain_ctl.cn9.write_ena           = 1;
        dbtrain_ctl.cn9.read_cmd_count      = 0x7F; // max count 7 bits
        dbtrain_ctl.cn9.rw_train            = 1;
        dbtrain_ctl.cn9.tccd_sel            = 1; // was: (mode == DBTRAIN_DBI);
        dbtrain_ctl.cn9.lfsr_pattern_sel    = use_lfsr;
    }

    for (row = 0; row < ROWS_TODO; row++) {

        int new_row = cur_row + row;

        if (is_cn8xxx)
            dbtrain_ctl.cn83xx.row_a = new_row;
        else
            dbtrain_ctl.cn9.row_a = new_row;
            

        VB_PRT(VBL_DEV3, "N%d: test_dram_byte_hw_rank: NEXT interation at LMC %d rank %d row %d\n",
               node, lmc, prank, new_row);

        bank_errs = 0;

        DRAM_CSR_WRITE(node, BDK_LMCX_DBTRAIN_CTL(lmc), dbtrain_ctl.u);

        VB_PRT(VBL_DEV3, "N%d.LMC%d: test_dram_byte_hw_rank: DBTRAIN: Pr:%d Lr:%d Bg:%d Ba:%d Row:%05x Col:%05x\n",
               node, lmc, prank, lrank, bg, ba, row, col);
        /*
          4) Kick off the sequence (SEQ_CTL[SEQ_SEL] = 14, SEQ_CTL[INIT_START] = 1).
          5) Poll on SEQ_CTL[SEQ_COMPLETE] for completion.
        */
        perform_octeontx_ddr_sequence(node, prank, lmc, 14); // RW_TRAINING

        /*
          6) Read MPR_DATA0 and MPR_DATA1 for results:
          a. MPR_DATA0[MPR_DATA<63:0>] – comparison results for DQ63:DQ0.
          (1 means MATCH, 0 means FAIL).
          b. MPR_DATA1[MPR_DATA<7:0>] – comparison results for ECC bit7:0.
        */
        mpr_data0 = BDK_CSR_READ(node, BDK_LMCX_MPR_DATA0(lmc));
        mpr_data1 = BDK_CSR_READ(node, BDK_LMCX_MPR_DATA1(lmc));

        /*
          7) Set PHY_CTL[PHY_RESET] = 1 (LMC automatically clears this as it’s a one-shot operation).
          This is to get into the habit of resetting PHY’s SILO to the original 0 location.
        */
        BDK_CSR_MODIFY(phy_ctl, node, BDK_LMCX_PHY_CTL(lmc),
                       phy_ctl.s.phy_reset = 1);

        if (mode == DBTRAIN_DBI)
            continue; // bypass any error checking or updating when DBI mode

        if (mode32b) {
            // 32-bit mode uses byte 4 [0:3] for ECC, data bits in [0:31],
            // and ECC is in [32:35]; so indicate MATCH for bits [36:63]
            mpr_data0 |= 0xFFFFFFF000000000ULL;
        }

        // data bytes
        if (~mpr_data0) {
            for (byte = 0; byte < 8; byte++) {
                if ((~mpr_data0 >> (8 * byte)) & 0xffUL)
                    bank_errs |= (1 << byte);
            }
            bad_bits[0] |= ~mpr_data0; // accumulate bad bits
        }

        if (!mode32b) { // only do if 64-bit mode, 32-bit ECC done above
            if (~mpr_data1 & 0xffUL) { // include ECC byte errors
                bank_errs |= (1 << 8);
                bad_bits[1] |= ~mpr_data1 & 0xffUL;
            }
        }

        errors |= bank_errs;

    } /* for (row = 0; row < rows_todo; row++) */

    cur_row += ROWS_TODO; 
    if ((cur_row + ROWS_TODO) >= LAST_ROW) // done all rows?
        cur_row = BASE_ROW; // start over at beginning next time

    rlevel_ctl.s.or_dis = save_or_dis;
    DRAM_CSR_WRITE(node, BDK_LMCX_RLEVEL_CTL(lmc), rlevel_ctl.u);

    if ((mode != DBTRAIN_DBI) && (xor_data != NULL)) { // send the bad bits back...
        xor_data[0] = bad_bits[0];
        xor_data[1] = bad_bits[1];
    }

    return errors;
}
