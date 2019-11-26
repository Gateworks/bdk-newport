/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libdram.h"

#include "bdk-dram-init.h"

#define ALLOW_WRITE_DESKEW 1
#if ALLOW_WRITE_DESKEW

static deskew_rank_t deskew_history[4];

int
change_wr_deskew_ena(bdk_node_t node, int ddr_interface_num, int new_state)
{
    bdk_lmcx_dll_ctl3_t ddr_dll_ctl3;
    int saved_wr_deskew_ena;

    // return original WR_DESKEW_ENA setting
    ddr_dll_ctl3.u = BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(ddr_interface_num));
    saved_wr_deskew_ena = !!GET_DDR_DLL_CTL3(wr_deskew_ena);
    if (saved_wr_deskew_ena != !!new_state) { // write it only when changing it
        SET_DDR_DLL_CTL3(wr_deskew_ena, !!new_state);
        DRAM_CSR_WRITE(node, BDK_LMCX_DLL_CTL3(ddr_interface_num), ddr_dll_ctl3.u);
    }
    return saved_wr_deskew_ena;
}

static void
do_write_deskew_op(bdk_node_t node, int ddr_interface_num,
                   int op, int byte_sel, int ena)
{
    bdk_lmcx_dll_ctl3_t ddr_dll_ctl3;

    ddr_dll_ctl3.u = BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(ddr_interface_num));
    SET_DDR_DLL_CTL3(bit_select,    op);
    SET_DDR_DLL_CTL3(byte_sel,      byte_sel);
    SET_DDR_DLL_CTL3(wr_deskew_ena, ena);
    if (bdk_is_model(OCTEONTX_CN9XXX))
        ddr_dll_ctl3.cn9.wr_deskew_mem_sel = ena;
    DRAM_CSR_WRITE(node, BDK_LMCX_DLL_CTL3(ddr_interface_num),	ddr_dll_ctl3.u);

    ddr_dll_ctl3.u = BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(ddr_interface_num));
}

static void
set_write_deskew_offset(bdk_node_t node, int ddr_interface_num,
                        int bit_sel, int byte_sel, int offset)
{
    bdk_lmcx_dll_ctl3_t ddr_dll_ctl3;

    ddr_dll_ctl3.u = BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(ddr_interface_num));
    SET_DDR_DLL_CTL3(bit_select, bit_sel);
    SET_DDR_DLL_CTL3(byte_sel,   byte_sel);
    SET_DDR_DLL_CTL3(offset,     offset);
    DRAM_CSR_WRITE(node, BDK_LMCX_DLL_CTL3(ddr_interface_num),	ddr_dll_ctl3.u);

    ddr_dll_ctl3.u = BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(ddr_interface_num));
    SET_DDR_DLL_CTL3(wr_deskew_ld, 1); // one-shot
    DRAM_CSR_WRITE(node, BDK_LMCX_DLL_CTL3(ddr_interface_num),	ddr_dll_ctl3.u);

    ddr_dll_ctl3.u = BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(ddr_interface_num));
}

static void
Update_Write_Deskew_Settings(bdk_node_t node, int ddr_interface_num,
                             int rank, deskew_data_t *dskdat)
{
    bdk_lmcx_config_t lmc_config;
    int bit_num;
    int byte_lane, byte_limit;

    lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(ddr_interface_num));
    byte_limit = ((lmc_config.s.mode32b) ? 4 : 8) + lmc_config.s.ecc_ena;

    for (byte_lane = 0; byte_lane < byte_limit; byte_lane++) {
	for (bit_num = 0; bit_num <= 7; ++bit_num) {

            set_write_deskew_offset(node, ddr_interface_num, bit_num, byte_lane + 1,
                                    dskdat->bytes[byte_lane].bits[bit_num]);

        } /* for (bit_num = 0; bit_num <= 7; ++bit_num) */
    } /* for (byte_lane = 0; byte_lane < byte_limit; byte_lane++) */

    // for CN9XXX, now we tell it which rank we are writing to, and do it
    if (bdk_is_model(OCTEONTX_CN9XXX)) {
        DRAM_CSR_MODIFY(mpr, node, BDK_LMCX_MR_MPR_CTL(ddr_interface_num),
                        mpr.s.mr_wr_rank = rank);        

        DRAM_CSR_MODIFY(c, node, BDK_LMCX_DLL_CTL3(ddr_interface_num),
                        c.s.wr_deskew_mem_ld = 1); // one-shot
    }

    return;
}

// set all entries to the same value (used during training)
static void
Set_Write_Deskew_Settings(bdk_node_t node, int ddr_interface_num, int rank, int value)
{
    int bit_num;

    VB_PRT(VBL_DEV2, "N%d.LMC%d: SetWriteDeskew: WRITE %d\n", // FIXME? add in rank for T96
           node, ddr_interface_num, value);

    for (bit_num = 0; bit_num <= 7; ++bit_num) {
        set_write_deskew_offset(node, ddr_interface_num, bit_num, ALL_BYTES, value);
    } /* for (bit_num = 0; bit_num <= 7; ++bit_num) */

    // for CN9XXX, now we tell it which rank we are writing to, and do it
    if (bdk_is_model(OCTEONTX_CN9XXX)) {
        DRAM_CSR_MODIFY(mpr, node, BDK_LMCX_MR_MPR_CTL(ddr_interface_num),
                        mpr.s.mr_wr_rank = rank);        

        DRAM_CSR_MODIFY(c, node, BDK_LMCX_DLL_CTL3(ddr_interface_num),
                        c.s.wr_deskew_mem_ld = 1); // one-shot
    }

    return;
}

void
Neutral_Write_Deskew_Setup(bdk_node_t node, int ddr_interface_num, int rank_mask)
{
    // first: NO-OP, Select all bytes, Disable write bit-deskew
    ddr_print("N%d.LMC%d: NEUTRAL Write Deskew Setup: first: NOOP\n",
              node, ddr_interface_num);
    do_write_deskew_op(node, ddr_interface_num, BS_NOOP, ALL_BYTES, 0);

    // enable write bit-deskew and RESET the settings
    ddr_print("N%d.LMC%d: NEUTRAL Write Deskew Setup: wr_ena: RESET\n",
              node, ddr_interface_num);
    do_write_deskew_op(node, ddr_interface_num, BS_RESET, ALL_BYTES, 1);

    // for CN9XXX, now we tell it which ranks we are writing to, and do it
    if (bdk_is_model(OCTEONTX_CN9XXX)) {
        for (int rankx = 0; rankx < 4; rankx++) {
            if (!(rank_mask & (1 << rankx))) 
                continue;

            DRAM_CSR_MODIFY(mpr, node, BDK_LMCX_MR_MPR_CTL(ddr_interface_num),
                            mpr.s.mr_wr_rank = rankx);        

            DRAM_CSR_MODIFY(c, node, BDK_LMCX_DLL_CTL3(ddr_interface_num),
                            c.s.wr_deskew_mem_ld = 1); // one-shot
        }
    }

}

void
Perform_Write_Deskew_Training(bdk_node_t node, int ddr_interface_num)
{
    deskew_data_t dskdat;
    int byte, bit_num;
    int dskval, rankx, rank_mask, active_ranks, errors, bit_errs;
    uint64_t hw_rank_offset;
    uint64_t bad_bits[2];
    uint64_t phys_addr;
    deskew_rank_t *dhp;
    int num_lmcs;

    BDK_CSR_INIT(lmcx_config, node, BDK_LMCX_CONFIG(ddr_interface_num));
    rank_mask = lmcx_config.s.init_status; // FIXME: is this right when we run?

    // this should be correct for 1 or 2 ranks, 1 or 2 DIMMs
    num_lmcs = (bdk_is_model(OCTEONTX_CN8XXX)) ? __bdk_dram_get_num_lmc(node) : 0;
    hw_rank_offset = 1ull << (28 + lmcx_config.s.pbank_lsb - lmcx_config.s.rank_ena + (num_lmcs/2));

    VB_PRT(VBL_FAE, "N%d.LMC%d: Performing Write Deskew Training.\n", node, ddr_interface_num);

    // first: NO-OP, Select all bytes, Disable write bit-deskew
    ddr_print("N%d.LMC%d: WriteDeskewConfig: first: NOOP\n", node, ddr_interface_num);
    do_write_deskew_op(node, ddr_interface_num, BS_NOOP, ALL_BYTES, 0);

    // enable write bit-deskew and RESET the settings
    ddr_print("N%d.LMC%d: WriteDeskewConfig: wr_ena: RESET\n", node, ddr_interface_num);
    do_write_deskew_op(node, ddr_interface_num, BS_RESET, ALL_BYTES, 1);

    memset(deskew_history, 0, sizeof(deskew_history));

    active_ranks = 0;
    for (rankx = 0; rankx < 4; rankx++) {

        if (!(rank_mask & (1 << rankx)))
            continue;
        dhp = &deskew_history[rankx];
        phys_addr = hw_rank_offset * active_ranks;
        active_ranks++;

        for (dskval = 0; dskval < 128; dskval += DSKVAL_INCR) {

            Set_Write_Deskew_Settings(node, ddr_interface_num, rankx, dskval);
            errors = run_best_hw_patterns_rank(node, ddr_interface_num, rankx,
                                               DBTRAIN_TEST, bad_bits);

            for (byte = 0; byte <= 8; byte++) { // do bytelane(s)

                // check errors
                bit_errs = ((byte == 8) ? bad_bits[1] : bad_bits[0] >> (8 * byte)) & 0xFFULL;

                VB_PRT(VBL_DEV2, "N%d.LMC%d.R%d: Byte %d Value %d: Address 0x%012lx errors 0x%x/0x%x\n",
                       node, ddr_interface_num, rankx, byte,
                       dskval, phys_addr, errors, bit_errs);

                for (bit_num = 0; bit_num <= 7; bit_num++) {
                    if (!(bit_errs & (1 << bit_num))) { // no bit_num error
                        if (dhp->bytes[byte].count[bit_num] == 0) { // first success, set run start
                            VB_PRT(VBL_DEV2, "N%d.LMC%d.R%d: Byte %d Bit %d Value %d: starting a run here\n",
                                   node, ddr_interface_num, rankx, byte, bit_num, dskval);
                            dhp->bytes[byte].start[bit_num] = dskval;
                        }
                        dhp->bytes[byte].count[bit_num] += DSKVAL_INCR; // bump run length

                        // is this now the biggest window?
                        if (dhp->bytes[byte].count[bit_num] > dhp->bytes[byte].best_count[bit_num]) {
                            dhp->bytes[byte].best_count[bit_num] = dhp->bytes[byte].count[bit_num];
                            dhp->bytes[byte].best_start[bit_num] = dhp->bytes[byte].start[bit_num];
                            VB_PRT(VBL_DEV2, "N%d.LMC%d.R%d: Byte %d Bit %d Value %d: updating best to %d/%d\n",
                                   node, ddr_interface_num, rankx, byte, bit_num, dskval,
                                   dhp->bytes[byte].best_start[bit_num],
                                   dhp->bytes[byte].best_count[bit_num]);
                        }
                    } else { // bit_num error
                        if (dhp->bytes[byte].count[bit_num] > 0) { // had started run
                            VB_PRT(VBL_DEV2, "N%d.LMC%d.R%d: Byte %d Bit %d Value %d: stopping a run here\n",
                                   node, ddr_interface_num, rankx, byte, bit_num, dskval);
                            dhp->bytes[byte].count[bit_num] = 0;   // stop now
                        }
                        // FIXME: else had not started run - nothing else to do?
                    }
                } /* for (bit_num = 0; bit_num <= 7; bit_num++) */
            } /* for (byte = 0; byte <= 8; byte++) */
        } /* for (dskval = 0; dskval < 128; dskval++) */

        // for CN9XXX we have a copy of write-deskew settings for each rank
        if (bdk_is_model(OCTEONTX_CN9XXX)) {

            for (byte = 0; byte <= 8; byte++) { // do bytelane(s)
                for (bit_num = 0; bit_num <= 7; bit_num++) { // do bits
                    int bit_beg, bit_end;
                    int rank_beg, rank_count, rank_end;

                    bit_beg = 0;
                    bit_end = 128;

                    rank_beg = dhp->bytes[byte].best_start[bit_num];
                    rank_count = dhp->bytes[byte].best_count[bit_num];

                    if (rank_count) {
                        rank_end = rank_beg + rank_count - DSKVAL_INCR;
                        bit_beg = max(bit_beg, rank_beg);
                        bit_end = min(bit_end, rank_end);
                    }

                    dskdat.bytes[byte].bits[bit_num] = (bit_end + bit_beg) / 2;

                } /* for (bit_num = 0; bit_num <= 7; bit_num++) */
            } /* for (byte = 0; byte <= 8; byte++) */

            // update the write bit-deskew settings with final settings
            ddr_print("N%d.LMC%d.R%d: WriteDeskewConfig: wr_ena: UPDATE\n",
                      node, ddr_interface_num, rankx);
            Update_Write_Deskew_Settings(node, ddr_interface_num, rankx, &dskdat);

            // display the write bit-deskew final settings
            Display_Deskew_Settings(node, ddr_interface_num, rankx, &dskdat, WR_DSK, VBL_NORM, "WRDSK");

        } /* if (bdk_is_model(OCTEONTX_CN9XXX)) */

    } /* for (rankx = 0; rankx < 4; rankx++) */

    // for CN8XXX we have only 1 copy of write-deskew settings for all ranks, so sum them
    if (bdk_is_model(OCTEONTX_CN8XXX)) {
        for (byte = 0; byte <= 8; byte++) { // do bytelane(s)

            for (bit_num = 0; bit_num <= 7; bit_num++) { // do bits
                int bit_beg, bit_end;

                bit_beg = 0;
                bit_end = 128;

                for (rankx = 0; rankx < 4; rankx++) { // merge ranks
                    int rank_beg, rank_end, rank_count;
                    if (!(rank_mask & (1 << rankx)))
                        continue;

                    dhp = &deskew_history[rankx];
                    rank_beg = dhp->bytes[byte].best_start[bit_num];
                    rank_count = dhp->bytes[byte].best_count[bit_num];

                    if (!rank_count) {
                        VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: Byte %d Bit %d: EMPTY\n",
                               node, ddr_interface_num, rankx, byte, bit_num);
                        continue;
                    }

                    bit_beg = max(bit_beg, rank_beg);
                    rank_end = rank_beg + rank_count - DSKVAL_INCR;
                    bit_end = min(bit_end, rank_end);

                } /* for (rankx = 0; rankx < 4; rankx++) */

                dskdat.bytes[byte].bits[bit_num] = (bit_end + bit_beg) / 2;

            } /* for (bit_num = 0; bit_num <= 7; bit_num++) */
        } /* for (byte = 0; byte <= 8; byte++) */

        // update the write bit-deskew settings with final settings
        ddr_print("N%d.LMC%d: WriteDeskewConfig: wr_ena: UPDATE\n",
                  node, ddr_interface_num);
        Update_Write_Deskew_Settings(node, ddr_interface_num, -1/*rank*/, &dskdat);

        // display the write bit-deskew final settings
        Display_Deskew_Settings(node, ddr_interface_num, -1/*rank*/, &dskdat, WR_DSK, VBL_NORM, "WRDSK");

    } /* if (bdk_is_model(OCTEONTX_CN8XXX)) */

    // last: NO-OP, Select all bytes, MUST leave write bit-deskew enabled
    ddr_print("N%d.LMC%d: WriteDeskewConfig: last: wr_ena: NOOP\n",
              node, ddr_interface_num);
    do_write_deskew_op(node, ddr_interface_num, BS_NOOP, ALL_BYTES, 1);
}

#else /* ALLOW_WRITE_DESKEW */
int
change_wr_deskew_ena(bdk_node_t node, int ddr_interface_num, int new_state)
{
    return 0;
}
void
Neutral_Write_Deskew_Setup(bdk_node_t node, int ddr_interface_num, int rank_mask)
{
}
void
Perform_Write_Deskew_Training(bdk_node_t node, int ddr_interface_num)
{
}

#endif /* ALLOW_WRITE_DESKEW */
