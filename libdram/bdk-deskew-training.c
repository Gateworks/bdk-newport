/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libdram.h"

#include "bdk-dram-init.h"

// to preserve (internal VREF) DAC settings for margining
dac_data_t final_dac_settings[4]; // by LMC

static deskew_counts_t deskew_training_results;

// when doing deskew read by-bit, bit 4=DAC maps to 9, bit 5=DBI maps to 8 in struct
static const uint8_t dsk_bit_seq[10] = {0,1,2,3,6,7,8,9,5,4};

static void
Get_Deskew_Settings_by_Byte(bdk_node_t node, int ddr_interface_num,
                            int rank, int byte_limit, deskew_data_t *dskdat)
{
    bdk_lmcx_phy_ctl_t phy_ctl;
    int byte_lane, bit_index;
    uint64_t gp0, gp1;
    int use_ecc = 1;

    // set the rank
    DRAM_CSR_MODIFY(mpr, node, BDK_LMCX_MR_MPR_CTL(ddr_interface_num),
                    mpr.s.mr_wr_rank = rank);

    phy_ctl.u = BDK_CSR_READ(node, BDK_LMCX_PHY_CTL(ddr_interface_num));
    phy_ctl.cn9.dsk_dbg_clk_scaler = 3;
    phy_ctl.cn9.dsk_dbg_wr_mode  = 0; // make sure we do reads
    phy_ctl.cn9.dsk_dbg_byte_rd  = 1; // make sure we do byte reads
    phy_ctl.cn9.dsk_dbg_offset   = 0; // clear offset
    phy_ctl.cn9.phy_reset        = 0; // make sure no reset

    if ((byte_limit == 4) || (byte_limit == 8)) {
        use_ecc = 0;
        if (byte_limit == 8)
            byte_limit = 9; // must still do 8 bytes even if skipping 4
    }

    for (byte_lane = 0; byte_lane < byte_limit; byte_lane += 1) {

        // disable only at start of chains, change byte_sel only then also
        phy_ctl.cn9.dsk_dbg_load_dis = ((byte_lane == 0) || (byte_lane == 5)) ? 0 : 1;
        phy_ctl.cn9.dsk_dbg_byte_sel = (byte_lane <= 4) ? 0 : 4; // set byte_sel to 0 or 4
        phy_ctl.cn9.dsk_dbg_start = 1;

        //DRAM_CSR_WRITE(node, BDK_LMCX_PHY_CTL(ddr_interface_num), phy_ctl.u);
        BDK_CSR_WRITE(node, BDK_LMCX_PHY_CTL(ddr_interface_num), phy_ctl.u); //FIXME: CSR verbosity?

        // poll for read sequence to complete
        do {
            phy_ctl.u = BDK_CSR_READ(node, BDK_LMCX_PHY_CTL(ddr_interface_num));
        } while (phy_ctl.cn9.dsk_dbg_rd_complete != 1);

        gp0 = BDK_CSR_READ(node, BDK_LMCX_GENERAL_PURPOSE0(ddr_interface_num));
        gp1 = BDK_CSR_READ(node, BDK_LMCX_GENERAL_PURPOSE1(ddr_interface_num));

        // record the data

        int dest_lane;
        if (use_ecc) {
            // map byte lanes: 0-3 -> 0-3; 4 -> 8; 5-8 -> 4-7
            dest_lane = (byte_lane == 4) ? 8 : (byte_lane > 4) ? (byte_lane - 1) : byte_lane;
        } else {
            if (byte_lane == 4) // skip bytelane 4 for non-ECC
                continue;
            // map byte lanes: 0-3 -> 0-3; 5-8 -> 4-7
            dest_lane = (byte_lane > 4) ? (byte_lane - 1) : byte_lane;
        }

        for (bit_index = 0; bit_index < 6; bit_index += 1) {
            dskdat->bytes[dest_lane].bits[bit_index] = (gp0 >> (bit_index * 10)) & 0x3FF;
        }
        for (bit_index = 0; bit_index < 4; bit_index += 1) { // do DBI(8) and DAC(9) too
            dskdat->bytes[dest_lane].bits[bit_index + 6] =
                (gp1 >> (bit_index * 10)) & ((bit_index == 3) ? 0xFF : 0x3FF); // DAC & FF
        }

    } /* for (byte_lane = 0; byte_lane < byte_limit; byte_lane++) */

}

/* Read Deskew Settings for DDR */
void
Get_Deskew_Settings(bdk_node_t node, int ddr_interface_num,
                    int rank, deskew_data_t *dskdat)
{
    bdk_lmcx_phy_ctl_t phy_ctl;
    bdk_lmcx_config_t  lmc_config;
    int bit_index;
    int byte_lane, byte_limit;
    int saved_wr_deskew_ena;
    int is_cn8xxx = !!bdk_is_model(OCTEONTX_CN8XXX);

    // save original WR_DESKEW_ENA setting, and disable it for read deskew reading
    saved_wr_deskew_ena = change_wr_deskew_ena(node, ddr_interface_num, 0);

    lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(ddr_interface_num));
    byte_limit = ((lmc_config.s.mode32b) ? 4 : 8) + lmc_config.s.ecc_ena;

    memset(dskdat, 0, sizeof(deskew_data_t));

    if (!is_cn8xxx) {
        Get_Deskew_Settings_by_Byte(node, ddr_interface_num, rank,
                                    byte_limit, dskdat);
    }
    else { // do it by bit...

        if (!is_cn8xxx) { // set the rank
            DRAM_CSR_MODIFY(mpr, node, BDK_LMCX_MR_MPR_CTL(ddr_interface_num),
                            mpr.s.mr_wr_rank = rank);
        }

        phy_ctl.u = BDK_CSR_READ(node, BDK_LMCX_PHY_CTL(ddr_interface_num));
        phy_ctl.s.dsk_dbg_clk_scaler = 3;
        if (!is_cn8xxx)
            phy_ctl.cn9.dsk_dbg_byte_rd = 0; // make sure we do bit reads

        for (byte_lane = 0; byte_lane < byte_limit; byte_lane++) {

            phy_ctl.s.dsk_dbg_byte_sel = byte_lane; // set byte lane

            for (bit_index = 0; bit_index < 10; ++bit_index) { // do DAC(9) and DBI(8) also

                // set bit number and start read sequence
                phy_ctl.s.dsk_dbg_bit_sel = dsk_bit_seq[bit_index];
                if (is_cn8xxx)
                    phy_ctl.cn83xx.dsk_dbg_rd_start = 1;
                else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */
                    phy_ctl.cn9.dsk_dbg_start = 1;
                DRAM_CSR_WRITE(node, BDK_LMCX_PHY_CTL(ddr_interface_num), phy_ctl.u);

                // poll for read sequence to complete
                do {
                    phy_ctl.u = BDK_CSR_READ(node, BDK_LMCX_PHY_CTL(ddr_interface_num));
                } while (phy_ctl.s.dsk_dbg_rd_complete != 1);

                // record the data
                dskdat->bytes[byte_lane].bits[bit_index] =
                    phy_ctl.s.dsk_dbg_rd_data & ((bit_index == 9) ? 0xFF : 0x3FF); // DAC & FF

            } /* for (bit_index = 0; bit_index < 10; ++bit_index) */
        } /* for (byte_lane = 0; byte_lane < byte_limit; byte_lane++) */

    } // end by bit...

    // restore original WR_DESKEW_ENA setting
    change_wr_deskew_ena(node, ddr_interface_num, saved_wr_deskew_ena);

    return;
}

static void get_rank_and_blank_strs(int rank, const char **rank_str, const char **blank_str)
{
    static const char *empty_str = "";
    static const char *b3_str = "   ";
    static const char *rank_strings[8] = {".R0", ".R1", ".R2", ".R3", ".Q3", ".Q4", ".XX", ".YY"};
    *rank_str  = (rank == -1) ? empty_str : rank_strings[rank & 7];
    *blank_str = (rank == -1) ? b3_str : empty_str;
}

static void
__Display_Deskew_Settings_Header(bdk_node_t node, int ddr_interface_num,
                                 int rank, int mode, int print_enable)
{
    int bit_index;
    int include_dqs1;
    char *mode_str = (mode == WR_DSK) ? "Write" : "Read ";

    const char *rank_str, *blank_str;
    get_rank_and_blank_strs(rank, &rank_str, &blank_str);

    BDK_CSR_INIT(lmc_config, node, BDK_LMCX_CONFIG(ddr_interface_num));
    BDK_CSR_INIT(phy_ctl, node, BDK_LMCX_PHY_CTL(ddr_interface_num));
    include_dqs1 = (bdk_is_model(OCTEONTX_CN9XXX) && 
                    !phy_ctl.s.dbi_mode_ena && 
                    !!lmc_config.s.mode_x4dev);

    printf("N%d.LMC%d%s: %s Deskew Settings:   Bit => %s :",
           node, ddr_interface_num, rank_str, mode_str, blank_str);

    if (include_dqs1)
        printf(" DQS1 ");

    for (bit_index = 7; bit_index >= 0; --bit_index)
        printf(" %3d  ", bit_index);

    printf("\n");
}

static void
__Display_Deskew_Settings_Bytelanes(bdk_node_t node, int ddr_interface_num, int rank,
                                    deskew_data_t *dskdat, int mode, int print_enable,
                                    char *print_str)
{
    int byte_lane;
    int bit_num, bit_last;
    uint16_t flags, deskew;
    bdk_lmcx_config_t lmc_config;
    int byte_limit;
    const char *fc = " ?-=+*#&";
    int is_mode32b;
    const char *rank_str, *blank_str;
    int flags_mask = (print_enable != VBL_FAE) ? 0 : 7; // if !FAE, no flags, else all
    int flags_or   = (print_enable != VBL_FAE) ? 1 : 0; // if !FAE, locked only, else none
    char *final_str = (print_str != NULL) ? print_str : "     ";

    get_rank_and_blank_strs(rank, &rank_str, &blank_str);

    lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(ddr_interface_num));
    is_mode32b = lmc_config.s.mode32b;
    int is_x4dev = !!lmc_config.s.mode_x4dev && !!bdk_is_model(OCTEONTX_CN9XXX);

    byte_limit = (is_mode32b ? 4 : 8) + lmc_config.s.ecc_ena;

    for (byte_lane = 0; byte_lane < byte_limit; byte_lane++) {

        printf("N%d.LMC%d%s: Bit Deskew Byte %d %s %s         :",
               node, ddr_interface_num, rank_str, byte_lane,
               final_str, blank_str);

        bit_last = 7 + is_x4dev;

        if (is_mode32b && (byte_lane == 4)) { // 32-bit mode, and ECC byte-lane
            bit_last = 3;
            // also, print empty cols for byte 4 bits 4-7
            printf("                        ");
        }

        flags = 1; // pretend it is locked for WR_DSK
        for (bit_num = bit_last; bit_num >= 0; --bit_num) {

            deskew = dskdat->bytes[byte_lane].bits[bit_num];
            if (mode == RD_DSK) {
                flags = (deskew & flags_mask) | flags_or;
                deskew >>= 3;
            }
            printf(" %3d %c", deskew, fc[flags^1]);
        } /* for (bit_num = 7; bit_num >= 0; --bit_num) */

        int errs = dskdat->bytes[byte_lane].bits[10] & flags_mask;
	if (errs != 0)
	    printf(" %c%c", (errs & 1) ? 'R' : ' ', (errs & 2) ? 'V' : ' ');

        printf("\n");

    } /* for (byte_lane = 0; byte_lane < byte_limit; byte_lane++) */
}

void
Display_Deskew_Settings(bdk_node_t node, int ddr_interface_num, int rank,
                        deskew_data_t *dskdat, int mode, int print_enable,
                        char *print_str)
{
    if (!print_enable || !dram_is_verbose(print_enable)) return;

    __Display_Deskew_Settings_Header(node, ddr_interface_num,
                                     rank, mode, print_enable);

    __Display_Deskew_Settings_Bytelanes(node, ddr_interface_num, rank,
                                        dskdat, mode, print_enable,
                                        print_str);

    return;
}

static void
Overwrite_Read_Deskew_Settings(bdk_node_t node, int ddr_interface_num,
                         int rank, deskew_data_t *dskdat)
{
    bdk_lmcx_phy_ctl_t phy_ctl;
    bdk_lmcx_config_t  lmc_config;

    int bit_num, byte_lane, byte_limit;
    uint64_t csr_data;
    int is_cn8xxx = !!bdk_is_model(OCTEONTX_CN8XXX);

    lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(ddr_interface_num));
    byte_limit = ((lmc_config.s.mode32b) ? 4 : 8) + lmc_config.s.ecc_ena;

    phy_ctl.u = BDK_CSR_READ(node, BDK_LMCX_PHY_CTL(ddr_interface_num));

    phy_ctl.s.phy_reset            = 0;
    if (is_cn8xxx)
        phy_ctl.cn83xx.dsk_dbg_num_bits_sel = 1;
    phy_ctl.s.dsk_dbg_offset       = 0;
    phy_ctl.s.dsk_dbg_clk_scaler   = 3;

    phy_ctl.s.dsk_dbg_wr_mode      = 1;
    phy_ctl.s.dsk_dbg_load_dis     = 0;
    phy_ctl.s.dsk_dbg_overwrt_ena  = 0;

    phy_ctl.s.phy_dsk_reset        = 0;

    DRAM_CSR_WRITE(node, BDK_LMCX_PHY_CTL(ddr_interface_num), phy_ctl.u);
    BDK_CSR_READ(node, BDK_LMCX_PHY_CTL(ddr_interface_num));

    if (byte_limit == 8)
        byte_limit = 9; // must ALWAYS write 8+ECC lanes even for non-ECC

    for (byte_lane = 0; byte_lane < byte_limit; byte_lane++) {
        int source_lane = byte_lane;
        if (!is_cn8xxx) {
            // map byte lanes: 0-3 -> 0-3; 4 -> 8; 5-8 -> 4-7
            // for non-ECC, byte-lane 8 data is DNC
            source_lane = (byte_lane == 4) ? 8 : (byte_lane > 4) ? (byte_lane - 1) : byte_lane;
        }

        csr_data = 0;

	for (bit_num = 0; bit_num < 9; ++bit_num) { // we cannot ignore DBI

            // fetch input and adjust
            uint64_t bits = (dskdat->bytes[source_lane].bits[bit_num] >> 3) & 0x7F;

            /****
            // lmc_general_purpose0.data[6:0]    // DQ0
            // lmc_general_purpose0.data[13:7]   // DQ1
            // lmc_general_purpose0.data[20:14]  // DQ2
            // lmc_general_purpose0.data[27:21]  // DQ3
            // lmc_general_purpose0.data[34:28]  // DQ4
            // lmc_general_purpose0.data[41:35]  // DQ5
            // lmc_general_purpose0.data[48:42]  // DQ6
            // lmc_general_purpose0.data[55:49]  // DQ7
            // lmc_general_purpose0.data[62:56]  // DBI
            ****/
            csr_data |= (bits << (7 * bit_num));

        } /* for (bit_num = 0; bit_num < 9; ++bit_num) */

        // update GP0 with the bit data for this byte lane
        DRAM_CSR_WRITE(node, BDK_LMCX_GENERAL_PURPOSE0(ddr_interface_num), csr_data);
        BDK_CSR_READ(node, BDK_LMCX_GENERAL_PURPOSE0(ddr_interface_num));

        // select the byte-lane and start the deskew load sequence
        phy_ctl.s.dsk_dbg_byte_sel = (!is_cn8xxx) ? ((byte_lane <= 4) ? 0 : 4) : byte_lane;

        if (is_cn8xxx)
            phy_ctl.cn83xx.dsk_dbg_rd_start = 1;
        else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */
            phy_ctl.cn9.dsk_dbg_start = 1;
        DRAM_CSR_WRITE(node, BDK_LMCX_PHY_CTL(ddr_interface_num), phy_ctl.u);

        // poll for write sequence to complete
        do {
            bdk_wait_usec(100);
            phy_ctl.u = BDK_CSR_READ(node, BDK_LMCX_PHY_CTL(ddr_interface_num));
        } while (phy_ctl.s.dsk_dbg_rd_complete != 1);

    } /* for (byte_lane = 0; byte_lane < byte_limit; byte_lane++) */

    // tell phy to use the new settings
    phy_ctl.s.dsk_dbg_overwrt_ena = 1;
    if (is_cn8xxx)
        phy_ctl.cn83xx.dsk_dbg_rd_start = 0;
    else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */
        phy_ctl.cn9.dsk_dbg_start = 0;
    DRAM_CSR_WRITE(node, BDK_LMCX_PHY_CTL(ddr_interface_num), phy_ctl.u);

    if (!is_cn8xxx) {
        DRAM_CSR_MODIFY(mpr, node, BDK_LMCX_MR_MPR_CTL(ddr_interface_num),
                        mpr.s.mr_wr_rank = rank);
        BDK_CSR_READ(node, BDK_LMCX_MR_MPR_CTL(ddr_interface_num));
        DRAM_CSR_MODIFY(ctl3, node, BDK_LMCX_DLL_CTL3(ddr_interface_num),
                        ctl3.s.rd_deskew_mem_ld = 1);
        BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(ddr_interface_num));
    }

    phy_ctl.s.dsk_dbg_wr_mode = 0;
    phy_ctl.s.dsk_dbg_overwrt_ena = 0;
    DRAM_CSR_WRITE(node, BDK_LMCX_PHY_CTL(ddr_interface_num), phy_ctl.u);

    return;
}

/*
 * Take "num_samples" in "dskdat" and return the averages in "dskavg"
 */
void
deskew_sum_and_average(bdk_node_t node, int ddr_interface_num, int num_samples, 
                       deskew_data_t *dskdat, deskew_data_t *dskavg)
{
    bdk_lmcx_config_t  lmc_config;
    int sample, byte_lane, bit_num;
    int byte_limit;

    lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(ddr_interface_num));
    byte_limit = ((lmc_config.s.mode32b) ? 4 : 8) + lmc_config.s.ecc_ena;

    memset((void *)dskavg, 0, sizeof(deskew_data_t));

    // sum the samples
    for (sample = 0; sample < num_samples; sample++) {
        for (byte_lane = 0; byte_lane < byte_limit; byte_lane++) {
            for (bit_num = 0; bit_num < 9; ++bit_num) { // include DBI!
                dskavg->bytes[byte_lane].bits[bit_num] +=
                    (dskdat[sample].bytes[byte_lane].bits[bit_num] >> 3); // remove flags
            }
        }
    }

    // average the samples
    for (byte_lane = 0; byte_lane < byte_limit; byte_lane++) {
        for (bit_num = 0; bit_num < 9; ++bit_num) { // include DBI!
            dskavg->bytes[byte_lane].bits[bit_num] /= num_samples;
            dskavg->bytes[byte_lane].bits[bit_num] <<= 3; // create clear flags
            dskavg->bytes[byte_lane].bits[bit_num] |= 1; // set LOCK
        }
    }

}

#if ALLOW_BY_RANK_INIT
void
process_by_rank_dac(bdk_node_t node, int ddr_interface_num,
                    int rank_mask, dac_data_t *dacdat)
{
    bdk_lmcx_config_t  lmc_config;
    int rankx, byte_lane;
    int byte_limit;
    int rank_count;
    dac_data_t dacsum;
    int lane_probs;

    lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(ddr_interface_num));
    byte_limit = ((lmc_config.s.mode32b) ? 4 : 8) + lmc_config.s.ecc_ena;

    memset((void *)&dacsum, 0, sizeof(dacsum));
    rank_count = 0;
    lane_probs = 0;

    for (rankx = 0; rankx < 2; rankx++) {
        if (! (rank_mask & (1 << rankx)))
            continue;
        rank_count++;

        display_DAC_DBI_settings(node, ddr_interface_num, rankx, /*dac*/1,
                                 lmc_config.s.ecc_ena, &dacdat[rankx].bytes[0],
                                 "By-Ranks VREF");
        // sum
        for (byte_lane = 0; byte_lane < byte_limit; byte_lane++) {
            if (rank_count == 2) {
                int ranks_diff = _abs((dacsum.bytes[byte_lane] - dacdat[rankx].bytes[byte_lane]));
                if (ranks_diff > 19) { // FIXME: is 19 a good number?
                    lane_probs |= (1 << byte_lane);
                }
            }
            dacsum.bytes[byte_lane] += dacdat[rankx].bytes[byte_lane];
        }
    }

    // average
    for (byte_lane = 0; byte_lane < byte_limit; byte_lane++) {
        dacsum.bytes[byte_lane] /= rank_count; // FIXME: nint?
    }

    display_DAC_DBI_settings(node, ddr_interface_num, -1/*rank*/, /*dac*/1, lmc_config.s.ecc_ena,
                             &dacsum.bytes[0], "All-Rank VREF");

    if (lane_probs) {
        ddr_print("N%d.LMC%d: All-Rank VREF DAC Problem Bytelane(s): 0x%03x\n",
              node, ddr_interface_num, lane_probs);
    }

    // finally, write the averaged DAC values
    for (byte_lane = 0; byte_lane < byte_limit; byte_lane++) {
        load_dac_override(node, ddr_interface_num, dacsum.bytes[byte_lane], byte_lane);
    }
}

void
process_by_rank_dsk(bdk_node_t node, int ddr_interface_num,
                    int rank_mask, deskew_data_t *dskdat)
{
    deskew_data_t dsksum;

    // sum the samples and then average
    deskew_sum_and_average(node, ddr_interface_num, 2, dskdat, &dsksum);

    // print the averaged values
    Display_Deskew_Settings(node, ddr_interface_num, -1/*rank*/, &dsksum, RD_DSK, VBL_TME, "BRAVG");

    // finally, (over-)write the averaged values
    Overwrite_Read_Deskew_Settings(node, ddr_interface_num, 0/*rank*/, &dsksum);

    // NOTE: DESKEW settings cannot be read after using the overwrite feature on CN8XXX!!!
}
#endif /* ALLOW_BY_RANK_INIT */

static int
Compare_and_Copy_Deskew_Settings(bdk_node_t node, int lmc, deskew_data_t *dsk1,
                                 deskew_data_t *dsk2, int copy_flag)
{
    int byte_lane, bit_num;
    int byte_limit;
    bdk_lmcx_config_t  lmc_config;
    int total_diff = 0;
    int ret = 0;

    lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(lmc));
    byte_limit = ((lmc_config.s.mode32b) ? 4 : 8) + lmc_config.s.ecc_ena;

    // compare settings
    for (byte_lane = 0; byte_lane < byte_limit; byte_lane++) { // do only data bytes
        for (bit_num = 0; bit_num < 8; ++bit_num) { // do all the bits
            uint16_t bit1, bit2, diff;

            // deskew delays are in bits 3-9, so we ignore the flags
            bit1 = (dsk1->bytes[byte_lane].bits[bit_num] >> 3) & 0x07F; 
            bit2 = (dsk2->bytes[byte_lane].bits[bit_num] >> 3) & 0x07F;

            // copy and count only when we have a mismatch
            diff = (bit1 > bit2) ? (bit1 - bit2) : (bit2 - bit1);
            if (diff) {
                if (copy_flag)
                    dsk2->bytes[byte_lane].bits[bit_num] = (bit1 << 3);
                total_diff += diff;
                ret++;
            }
        }
    }

    return ret;
}

static int
Validate_Read_Deskew_Training_rank(bdk_node_t node, int ddr_interface_num, int rank,
                                   deskew_counts_t *counts, int print_enable, char *print_str)
{
    int byte_lane, bit_index, nib_num;
    int16_t nib_min[2], nib_max[2];
    int byte_limit;
    deskew_data_t dskdat;
    static deskew_data_t dsklast;
    static int ranklast = -1;
    int16_t flags, deskew;
    int bit_last;
    int is_mode32b;
    int include_dqs1;
    int ret = 0;

    BDK_CSR_INIT(lmc_config, node, BDK_LMCX_CONFIG(ddr_interface_num));
    is_mode32b   = !!lmc_config.s.mode32b;
    byte_limit   = ((is_mode32b) ? 4 : 8) + lmc_config.s.ecc_ena;

    BDK_CSR_INIT(phy_ctl, node, BDK_LMCX_PHY_CTL(ddr_interface_num));
    include_dqs1 = (bdk_is_model(OCTEONTX_CN9XXX) && 
                    !phy_ctl.s.dbi_mode_ena && 
                    !!lmc_config.s.mode_x4dev);

    memset(counts, 0, sizeof(deskew_counts_t));

    Get_Deskew_Settings(node, ddr_interface_num, rank, &dskdat);

    for (byte_lane = 0; byte_lane < byte_limit; byte_lane++) {
        int16_t bl_mask = (1 << byte_lane);
        int byte_flags = 0;

        // FIXME: 8 was 7, do 8 for DQS1 "bit" inclusion
        bit_last = (is_mode32b && (byte_lane == 4)) ? 3 : (7 + include_dqs1); 

	nib_min[0] = 127; nib_min[1] = 127;
	nib_max[0] = 0;   nib_max[1] = 0;

        for (bit_index = bit_last; bit_index >= 0; --bit_index) {

	    flags = dskdat.bytes[byte_lane].bits[bit_index] & 7;
	    deskew = dskdat.bytes[byte_lane].bits[bit_index] >> 3;

            // check saturation bits
            if (flags & 6) {
                byte_flags |= (flags & 6);
                counts->saturated += 1;
            }

            // check lock bit
            if (! (flags & 1))
                counts->unlocked += 1;

            // determine nibble min/max
	    nib_num = (bit_index > 3) ? 1 : 0;
            nib_min[nib_num] = min(nib_min[nib_num], deskew);
            nib_max[nib_num] = max(nib_max[nib_num], deskew);

        } /* for (bit_index = bit_last; bit_index >= 0; --bit_index) */

        // check for saturation issues in the byte
        if (byte_flags & 4) counts->sat_hi |= bl_mask;
        if (byte_flags & 2) counts->sat_lo |= bl_mask;

        // Now look for nibble errors for this byte-lane:
        // 1. range error:  difference between max and min delays for a nibble
        // 2. bitval error: nibble max > high limit or nibble min < low limit
        
	// check nibble ranges
#define NIB_RANGE 33
#define NIB_DIFF(i) ((nib_max[(i)] - nib_min[(i)]) > NIB_RANGE)
	counts->nibrng_errs |= (NIB_DIFF(1) || NIB_DIFF(0)) ? bl_mask : 0;

	// check for bit value errors, ie < MIN_BITVAL or > MAX_BITVAL
        // FIXME? assume max always > MIN_BITVAL and min < MAX_BITVAL
#define NIB_MAX(i) ((nib_max[(i)]) > MAX_BITVAL)
#define NIB_MIN(i) ((nib_min[(i)]) < MIN_BITVAL)
	counts->val_hi |= (NIB_MAX(1) || NIB_MAX(0)) ? bl_mask : 0;
	counts->val_lo |= (NIB_MIN(1) || NIB_MIN(0)) ? bl_mask : 0;

        // set error flags for the byte-lane

        // range errors
        if ((counts->nibrng_errs & bl_mask) != 0)
            dskdat.bytes[byte_lane].bits[10] |= 1;

        // limits errors
        if (((counts->val_hi | counts->val_lo) & bl_mask) != 0) {
            dskdat.bytes[byte_lane].bits[10] |= 2;
            counts->limits += 1;
        }

    } /* for (byte_lane = 0; byte_lane < byte_limit; byte_lane++) */

    // display the settings from the struct which now includes byte-lane error flags
    Display_Deskew_Settings(node, ddr_interface_num, rank, &dskdat, RD_DSK, print_enable, print_str);

    if (bdk_is_model(OCTEONTX_CN9XXX)) {
        ret = Compare_and_Copy_Deskew_Settings(node, ddr_interface_num,
                                               &dskdat, &dsklast, 1/*copy*/);
        if ((ret > 0) && (rank == ranklast))
            VB_PRT(VBL_DEV2, "N%d.LMC%d.R%d: DESKEW: number of bits still changing = %2d\n",
                   node, ddr_interface_num, rank, ret);
        ranklast = rank;
    }

    return ret;
}

int
Validate_Read_Deskew_Training(bdk_node_t node, int ddr_interface_num, int rank_mask,
                              deskew_counts_t *counts, int print_enable, char *print_str)
{
    int ret = 0;

    // if CN9XXX, we can do read deskew by ranks, so print it that way
    if (bdk_is_model(OCTEONTX_CN9XXX)) {
        for (int rank = 0; rank < 4; rank++) {
            if (rank_mask & (1 << rank)) {
                ret = Validate_Read_Deskew_Training_rank(node, ddr_interface_num, rank,
                                                         counts, print_enable, print_str);
            }
        }
    } else {
        ret = Validate_Read_Deskew_Training_rank(node, ddr_interface_num, -1/* ?rank? */,
                                                 counts, print_enable, print_str);
    }
    return ret;
}

// Evaluate the DAC settings array
int evaluate_DAC_settings(int ddr_interface_64b, int ecc_ena, int *settings)
{
    int byte, dac;
    int last = (ddr_interface_64b) ? 7 : 3;
    int diff_limit = (bdk_is_model(OCTEONTX_CN8XXX)) ? 20 : 40/*was 30*/; // FIXME? bigger for CN9?

    // this looks only for DAC values that are out of a range;
    // let any EVEN go so long as it is within range...
    for (byte = (last+ecc_ena); byte >= 0; --byte) {
        dac  = settings[byte] & 0xff;
        for (int lane = (last+ecc_ena); lane >= 0; --lane) {
            int comp = settings[lane] & 0xff;
            if (_abs((dac - comp)) > diff_limit)
                return 1;
        }
    }
    return 0;
}

// HRM-CN9XXX 7.9.8
static void
Perform_Offset_Training(bdk_node_t node, int rank_mask, int ddr_interface_num)
{
    bdk_lmcx_phy_ctl_t lmc_phy_ctl;
    uint64_t orig_phy_ctl;
    const char *s;

    /*
     * 6.9.8 LMC Offset Training
     *
     * LMC requires input-receiver offset training.
     *
     * 1. Write LMC(0)_PHY_CTL[DAC_ON] = 1
     */
    // HRM-CN9XXX 7.9.8.1

    lmc_phy_ctl.u = BDK_CSR_READ(node, BDK_LMCX_PHY_CTL(ddr_interface_num));
    orig_phy_ctl = lmc_phy_ctl.u;
    lmc_phy_ctl.s.dac_on = 1;

    // allow full CSR override
    if ((s = lookup_env_parameter_ull("ddr_phy_ctl")) != NULL) {
        lmc_phy_ctl.u = strtoull(s, NULL, 0);
    }

    // do not print or write if CSR does not change...
    if (lmc_phy_ctl.u != orig_phy_ctl) {
        ddr_print("%-45s : 0x%016lx\n", "PHY_CTL", lmc_phy_ctl.u);
        DRAM_CSR_WRITE(node, BDK_LMCX_PHY_CTL(ddr_interface_num), lmc_phy_ctl.u);
    }

    /*
     * 2. Write LMC(0)_SEQ_CTL[SEQ_SEL] = 0x0B and
     *    LMC(0)_SEQ_CTL[INIT_START] = 1.
     * 3. Wait for LMC(0)_SEQ_CTL[SEQ_COMPLETE] to be set to 1.
     */
    // HRM-CN9XXX 7.9.8.2-3
    /* SEQ 0x0B = LMC Offset training sequence */
    perform_octeontx_ddr_sequence(node, rank_mask, ddr_interface_num, 0x0B);

}

static int
rankmask_to_rank(int mask)
{
    if (__builtin_popcount((mask & 0x0F)) != 1) {
        error_print("ERROR: rankmask_to_rank: ILLEGAL mask 0x%02x\n", mask);
        return -1; // FIXME? should we return error somehow?
    }
    int rank = (mask >> 1) & 7;
    if (rank == 4) rank = 3;
    return rank;
}

// HRM-CN9XXX 7.9.9
static void
Perform_Internal_VREF_Training(bdk_node_t node, int rank_mask,
                               int ddr_interface_num,
                               dram_training_data_t *training)
{
    bdk_lmcx_dll_ctl3_t ddr_dll_ctl3;
    int *dac_settings = training->dac_settings;
    int read_rank = 0; // default for CN8XXX, when it is ignored

    // First, make sure all byte-lanes are out of VREF bypass mode
    ddr_dll_ctl3.u = BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(ddr_interface_num));

    ddr_dll_ctl3.s.byte_sel   = 0x0A; /* all byte-lanes */
    ddr_dll_ctl3.s.bit_select = 0x09; /* No-op */
    DRAM_CSR_WRITE(node, BDK_LMCX_DLL_CTL3(ddr_interface_num), ddr_dll_ctl3.u);

    ddr_dll_ctl3.s.bit_select = 0x0E; /* Vref bypass off. */
    DRAM_CSR_WRITE(node, BDK_LMCX_DLL_CTL3(ddr_interface_num), ddr_dll_ctl3.u);

    ddr_dll_ctl3.s.bit_select = 0x09; /* No-op */
    DRAM_CSR_WRITE(node, BDK_LMCX_DLL_CTL3(ddr_interface_num), ddr_dll_ctl3.u);

    /*
     * 6.9.9 LMC Internal Vref Training
     *
     * LMC requires input-reference-voltage training.
     *
     * 1. Write LMC(0)_EXT_CONFIG[VREFINT_SEQ_DESKEW] = 0.
     */

    /* Clear for Internal VREF Training sequence */
    // HRM-CN9XXX 7.9.9.1
    DRAM_CSR_MODIFY(ext, node, BDK_LMCX_EXT_CONFIG(ddr_interface_num),
                    ext.s.vrefint_seq_deskew = 0);

    VB_PRT(VBL_SEQ, "N%d.LMC%d: Performing LMC sequence: vrefint_seq_deskew = 0\n",
           node, ddr_interface_num);

    // HRM-CN9XXX 7.9.9.2-3
    if (bdk_is_model(OCTEONTX_CN9XXX)) {
        /* 2. To do a longer duration mode of Vref training, write
              LMC(0..2)_PHY_CTL[DOUBLE_VREF_TRAINING] = 1, otherwise it can be set
              to its default value of 0. */
        // FIXME: above already taken care of in the defaults and overrides

        /* 3. Write LMC(0..2)_MR_MPR_CTL[MR_WR_RANK] to select the desired rank
              when performing internal Vref training. Note that even though the Vref training
              sequence can be configured to read data from different ranks, there is only one
              buffer that stores the Vref settings from the last run of the sequence.
        */
        read_rank = rankmask_to_rank(rank_mask); // FIXME: assumes mask has only 1 rank in it
        DRAM_CSR_MODIFY(mpr, node, BDK_LMCX_MR_MPR_CTL(ddr_interface_num),
                        mpr.s.mr_wr_rank = read_rank);
    } /* if (bdk_is_model(OCTEONTX_CN9XXX)) */

    /*
     * 2. Write LMC(0)_SEQ_CTL[SEQ_SEL] = 0x0a and
     *    LMC(0)_SEQ_CTL[INIT_START] = 1.
     * 3. Wait for LMC(0)_SEQ_CTL[SEQ_COMPLETE] to be set to 1.
     */
    /* SEQ 0x0A = LMC Internal Vref Training when EXT_CONFIG[vrefint_seq_deskew] = 0. */
    // HRM-CN9XXX 7.9.9.4-5
    perform_octeontx_ddr_sequence(node, rank_mask, ddr_interface_num, 0x0A);

    // read and return the DAC values
    read_DAC_DBI_settings(node, ddr_interface_num, read_rank, /*DAC*/1, dac_settings);
}

#define dbg_avg(format, ...) VB_PRT(VBL_DEV2, format, ##__VA_ARGS__)
int process_samples_average(int16_t *bytes, int num_samples, int lmc, int lane_no)
{
    int i, savg, sadj, sum = 0, rng, ret, asum, trunc;
    int16_t smin = 32767, smax = -32768;
    int nmin, nmax;

    dbg_avg("DBG_AVG%d.%d: ", lmc, lane_no);

    for (i = 0; i < num_samples; i++) {
        sum += bytes[i];
        if (bytes[i] < smin) smin = bytes[i];
        if (bytes[i] > smax) smax = bytes[i];
        dbg_avg(" %3d", bytes[i]);
    }
    rng = smax - smin + 1;

    nmin = 0;
    nmax = 0;
    for (i = 0; i < num_samples; i++) {
        if (bytes[i] == smin) nmin += 1;
        if (bytes[i] == smax) nmax += 1;
    }
    dbg_avg(" (min=%3d/%d, max=%3d/%d, range=%2d, samples=%2d)",
            smin, nmin, smax, nmax, rng, num_samples);

    asum = sum - smin - smax;
    savg = divide_nint(sum * 10, num_samples);
    if (num_samples <= 2) {
        sadj = savg;
        trunc = sum / num_samples;
    } else {
        sadj = divide_nint(asum * 10, (num_samples - 2));
        trunc = asum / (num_samples - 2);
    }

    dbg_avg(" [%3d.%d, %3d.%d, %3d]", savg/10, savg%10, sadj/10, sadj%10, trunc);

    sadj = divide_nint(sadj, 10);
    if (trunc & 1)
        ret = trunc;
    else if (sadj & 1)
        ret = sadj;
    else
        ret = trunc + 1;

    dbg_avg(" -> %3d\n", ret);

    return ret;
}

unsigned int EXTR_DQS0_ADJ(uint64_t u, int x)
{
    return (unsigned int)((u >> (x*3+00)) & 0x7UL);
}

void INSRT_DQS0_ADJ(uint64_t *up, int x, int v)
{
    uint64_t u = *up;

    u &= ~((0x7UL) << (x*3+00));
    *up = (u | ((v & 0x7UL) << (x*3+00)));
    return;
}

#if 0
// TODO: keep this for future use!!!
static void RESET_PHY_CTL2_DQS0_ADJ(bdk_node_t node, int ddr_interface_num)
{
    BDK_CSR_INIT(phy_ctl2, node, BDK_LMCX_PHY_CTL2(ddr_interface_num));
    for (int byte = 0; byte <= 8; byte++) // do all byte lanes regardless
        INSRT_DQS0_ADJ(&phy_ctl2.u, byte, 4);
    DRAM_CSR_WRITE(node, BDK_LMCX_PHY_CTL2(ddr_interface_num), phy_ctl2.u);
}
#endif

// HRM-CN9XXX 7.9.10 LMC Read Deskew Training
int
Perform_Read_Deskew_Training_rank(bdk_node_t node, int rank_mask, int ddr_interface_num,
                                  dram_init_data_t *init_data, dram_overrides_t *overrides,
                                  int print_flags)
{
    int unsaturated, locked, sw_locked;
    int sat_retries, sat_retries_limit;
    int lock_retries, lock_retries_total, lock_retries_limit;
    int print_last;
    int print_them_all;
    deskew_counts_t dsk_counts;
    int ecc_ena =                   init_data->refs.use_ecc;
    int deskew_validation_delay =   overrides->init.deskew_validation_delay;
    int default_lock_retry_limit =  overrides->init.default_lock_retry_limit;
    bdk_lmcx_phy_ctl_t phy_ctl;
    int changed, num_zero_changed, counting_zero_changed;
    int read_rank = 0;
    int16_t sat_hi, sat_lo;
    int ret = 0, ret_redo = 0;
    const char *rank_str, *blank_str;
    int is_cn9xxx = bdk_is_model(OCTEONTX_CN9XXX);
    static uint8_t adj_hi[8] = {4,0,1,2,3,4,4,4};   // seq 4 3 2 1 0 4 
    static uint8_t adj_lo[8] = {4,4,4,4,5,6,7,4};   // seq 4 5 6 7 4 

    read_rank = (is_cn9xxx) ? rankmask_to_rank(rank_mask) : -1; // FIXME: assumes mask has only 1 rank in it
    get_rank_and_blank_strs(read_rank, &rank_str, &blank_str);

    counting_zero_changed = is_cn9xxx; // only count for CN9XXX

    VB_PRT(VBL_FAE, "N%d.LMC%d%s: Performing Read Deskew Training.\n",
           node, ddr_interface_num, rank_str);

    sat_retries = 0;
    sat_retries_limit = DEFAULT_SAT_RETRY_LIMIT;

    lock_retries_total = 0;
    unsaturated = 0;
    print_last = VBL_FAE; // print the last one, FAE and above
    print_them_all = 0/* was VBL_DEV4*/; // set to DEV4 for printing all normal deskew attempts

    lock_retries_limit = default_lock_retry_limit;

    /*
     * 6.9.10 LMC Deskew Training
     *
     * LMC requires input-read-data deskew training.
     *
     * 1. Write LMC(0)_EXT_CONFIG[VREFINT_SEQ_DESKEW] = 1.
     */
    VB_PRT(VBL_SEQ, "N%d.LMC%d%s: Performing LMC sequence: Set vrefint_seq_deskew = 1\n",
           node, ddr_interface_num, rank_str);

    /* Set for Deskew Training sequence */
    // HRM-CN9XXX 7.9.10.1
    DRAM_CSR_MODIFY(ext_config, node, BDK_LMCX_EXT_CONFIG(ddr_interface_num),
                    ext_config.s.vrefint_seq_deskew = 1);

    // HRM-CN9XXX 7.9.10.2
    if (bdk_is_model(OCTEONTX_CN9XXX)) {
        /* 2. Write LMC(0..2)_MR_MPR_CTL[MR_WR_RANK] to select the desired rank
           when performing deskew training. */
        DRAM_CSR_MODIFY(mpr, node, BDK_LMCX_MR_MPR_CTL(ddr_interface_num),
                        mpr.s.mr_wr_rank = read_rank);
    }

    sat_hi = sat_lo = 0;
    BDK_CSR_INIT(phy_ctl2, node, BDK_LMCX_PHY_CTL2(ddr_interface_num));

    do { /* while (!unsaturated && (sat_retries < sat_retries_limit)) */
        int byte;

        // if needed for saturation, adjust deskew before doing RESET
        if (sat_hi) {
            for (byte = 0; byte < 8+ecc_ena; byte++) {
                if (sat_hi & (1 << byte)) {
                    int adj = EXTR_DQS0_ADJ(phy_ctl2.u, byte);
                    INSRT_DQS0_ADJ(&phy_ctl2.u, byte, adj_hi[adj]);
                }    
            }
        }
        if (sat_lo) {
            for (byte = 0; byte < 8+ecc_ena; byte++) {
                if (sat_lo & (1 << byte)) {
                    int adj = EXTR_DQS0_ADJ(phy_ctl2.u, byte);
                    INSRT_DQS0_ADJ(&phy_ctl2.u, byte, adj_lo[adj]);
                }    
            }
        }
        if (sat_hi || sat_lo) {
            VB_PRT(VBL_DEV, "N%d.LMC%d%s: DQS0_ADJ: PHY_CTL2[dqs0_dsk_adjX] [8:0]: ",
                   node, ddr_interface_num, rank_str);
            for (byte = 8; byte >= 0; byte--) VB_PRT(VBL_DEV, "%1d ", EXTR_DQS0_ADJ(phy_ctl2.u, byte));
            VB_PRT(VBL_DEV, "\n");
            DRAM_CSR_WRITE(node, BDK_LMCX_PHY_CTL2(ddr_interface_num), phy_ctl2.u);

            ret_redo = 1; // always force a full redo
        }

        phy_ctl.u = BDK_CSR_READ(node, BDK_LMCX_PHY_CTL(ddr_interface_num));
        phy_ctl.s.phy_dsk_reset = 1; /* RESET Deskew */
        BDK_CSR_WRITE(node, BDK_LMCX_PHY_CTL(ddr_interface_num), phy_ctl.u);
        BDK_CSR_READ(node, BDK_LMCX_PHY_CTL(ddr_interface_num)); // force write

	lock_retries = 0;
        num_zero_changed = 0;

        // do this just before starting the training loop
        phy_ctl.s.phy_dsk_reset = 0; /* Normal Deskew */
        BDK_CSR_WRITE(node, BDK_LMCX_PHY_CTL(ddr_interface_num), phy_ctl.u);
        BDK_CSR_READ(node, BDK_LMCX_PHY_CTL(ddr_interface_num)); // force write

    do_read_deskew_training:

        /*
         * 2. Write LMC(0)_SEQ_CTL[SEQ_SEL] = 0x0A and
         *    LMC(0)_SEQ_CTL[INIT_START] = 1.
         *
         * 3. Wait for LMC(0)_SEQ_CTL[SEQ_COMPLETE] to be set to 1.
         */
        // HRM-CN9XXX 7.9.10.3-4
        perform_octeontx_ddr_sequence(node, rank_mask, ddr_interface_num, 0x0A);

        // Moved this from Validate_Read_Deskew_Training
        /* Allow deskew results to stabilize before evaluating them. */
        bdk_wait_usec(deskew_validation_delay);

        // Now go look at lock and saturation status, and maybe print
        changed = Validate_Read_Deskew_Training_rank(node, ddr_interface_num, read_rank,
                                                     &dsk_counts, print_them_all, "PRDSK");

        unsaturated = (dsk_counts.saturated == 0);
	locked = (dsk_counts.unlocked == 0);
        sw_locked = 0;

	// only do locking retries if unsaturated, otherwise full SAT retry
	if (unsaturated) {
            if (counting_zero_changed) { // when attempting SW locking
                if (changed == 0) { // no changes this training seq
                    num_zero_changed += 1; // bump counter
                    sw_locked = (num_zero_changed > 4); 
                } else {
                    num_zero_changed = 0; // reset counter
                }
            }
	    if (!locked && !sw_locked) { // and not locked
		lock_retries++;
		lock_retries_total++;
		if (lock_retries <= lock_retries_limit) {
		    goto do_read_deskew_training;
		} else {
		    VB_PRT(VBL_TME, "N%d.LMC%d%s: LOCK RETRIES failed after %d retries (FAKESAT)\n",
                           node, ddr_interface_num, rank_str, lock_retries_limit);
                    unsaturated = 0; // FAKE saturation to try again from the start
		}
	    } else {
		if (lock_retries_total > 0) // only print if we did try
		    VB_PRT(VBL_TME, "N%d.LMC%d%s: LOCK RETRIES successful after %d retries (%cW)\n",
                           node, ddr_interface_num, rank_str, lock_retries, locked ? 'H' : 'S');
                break; // FIXME??? unsat AND locked
            }
	} /* if (unsaturated) */
        else { // if we have some deskew saturation, try adjusting
            // FIXME: change verbosity when debugged...
            if ((dsk_counts.sat_hi & dsk_counts.sat_lo) != 0) { // ERROR! common bytelane?
                VB_PRT(VBL_DEV, "N%d.LMC%d%s: SATURATION: ERROR: hi %03x, lo %03x\n",
                       node, ddr_interface_num, rank_str, dsk_counts.sat_hi, dsk_counts.sat_lo);
            } else {
                sat_hi = dsk_counts.sat_hi;
                sat_lo = dsk_counts.sat_lo;

                // FIXME: change verbosity when debugged...
                VB_PRT(VBL_DEV, "N%d.LMC%d%s: SATURATION: hi %03x, lo %03x\n",
                       node, ddr_interface_num, rank_str, dsk_counts.sat_hi, dsk_counts.sat_lo);
            }
        }

        ++sat_retries;

    } while (!unsaturated && (sat_retries < sat_retries_limit));

    /* Clear when done with Deskew Training sequence */
    // HRM-CN9XXX 7.9.10.1
    DRAM_CSR_MODIFY(ext_config, node, BDK_LMCX_EXT_CONFIG(ddr_interface_num),
                    ext_config.s.vrefint_seq_deskew = 0);

    VB_PRT(VBL_FAE, "N%d.LMC%d%s: Read Deskew Training %s. %d full-retries, %d lock-retries\n",
           node, ddr_interface_num, rank_str,
           (sat_retries >= sat_retries_limit) ? "Timed Out" : "Completed",
           sat_retries, lock_retries_total);

    // FIXME? add saturation to reasons for fault return - give it a chance via Internal VREF
    if (!locked && !sw_locked &&
        ((dsk_counts.nibrng_errs != 0) ||
         (dsk_counts.limits != 0) ||
         !unsaturated))
    {
        // FIXME: do we always want the printout when we have errors?
        print_last = VBL_NORM;
	ret = -1; // we did retry locally, they did not help
    }

    Validate_Read_Deskew_Training_rank(node, ddr_interface_num, read_rank, &dsk_counts, print_last, "SUMRY");

    // NOTE: we (currently) always print one last training validation before starting Read Leveling...

    // if not locked or saturation or nibble errors, return error rather than redo
    return (ret) ? ret : ((ret_redo) ? -2 : 0);
}

/*
 * Do all ranks, and allow any saturation adjustment to cause redo from the beginning
 */
int
Perform_Read_Deskew_Training_with_Adjust(bdk_node_t node, int rank_mask, int ddr_interface_num, 
                                         dram_init_data_t *init_data, dram_overrides_t *overrides,
                                         int print_flags)
{
    int ret;

 restart_deskew_training:

    ret = 0;

    for (int rank = 0; rank < 4; rank++) {
        if (rank_mask & (1 << rank)) {
            ret = Perform_Read_Deskew_Training_rank(node, (1 << rank), ddr_interface_num,
                                                    init_data, overrides, print_flags);

            // Check on return value, if bad, stop rank training and return error
            if (ret == -1)
                break;
            else if (ret == -2)
                goto restart_deskew_training;
        }
    }
    return ret;
}

#define MAX_DSK_SAMPLES      5
#define DEFAULT_DSK_SAMPLES  3

int
Perform_Read_Deskew_Training(bdk_node_t node, int rank_mask, int ddr_interface_num, 
                             dram_init_data_t *init_data, dram_overrides_t *overrides,
                             int print_flags)
{
    int ret;
    int num_dsk_samples = DEFAULT_DSK_SAMPLES;
    deskew_data_t dskdat[MAX_DSK_SAMPLES], dskavg;
    const char *s;

    // if CN9XXX, we can do read deskew by ranks, so run it that way
    if (bdk_is_model(OCTEONTX_CN9XXX)) {

        // allow override of number of samples
        if ((s = lookup_env_parameter_ull("ddr_dsk_samples")) != NULL) {
            num_dsk_samples = strtoull(s, NULL, 0);
            if ((num_dsk_samples < 1) || (num_dsk_samples > MAX_DSK_SAMPLES))
                num_dsk_samples = MAX_DSK_SAMPLES;
        }

    restart_deskew_training:

        VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: PRDT: Start ADJUST\n", node, ddr_interface_num, rank_mask); // FIXME? DEBUGGING ONLY

        // first, do all the ranks with adjustment of their common DQS0 if necessary
        ret = Perform_Read_Deskew_Training_with_Adjust(node, rank_mask, ddr_interface_num,
                                                       init_data, overrides, print_flags);
        // Check on return value, if bad, stop rank training and return error
        if (ret == -1)
            return ret;
        else if (ret == -2) // else try again
            goto restart_deskew_training;
        
        VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: PRDT: Done ADJUST\n", node, ddr_interface_num, rank_mask); // FIXME? DEBUGGING ONLY

        // next, do each rank separately
        for (int rank = 0; rank < 4; rank++) {
            if (!(rank_mask & (1 << rank)))
                continue;

            VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: PRDT: Start SAMPLING\n", node, ddr_interface_num, rank); // FIXME? DEBUGGING ONLY

            // first, read the current deskew for the rank and print as first sample
            Get_Deskew_Settings(node, ddr_interface_num, rank, &dskdat[0]);
            Display_Deskew_Settings(node, ddr_interface_num, rank, &dskdat[0], RD_DSK, VBL_DEV, "SAMPL");

            // next, do fresh deskews on the rank
            for (int sample = 1; sample < num_dsk_samples; sample++) {
                ret = Perform_Read_Deskew_Training_rank(node, (1 << rank), ddr_interface_num,
                                                        init_data, overrides, print_flags);
                // Check on return value, if bad, stop rank training and return error
                if (ret == -1)
                    return ret;
                else if (ret == -2)
                    goto restart_deskew_training;

                // read the final deskew for this sample and maybe print it
                Get_Deskew_Settings(node, ddr_interface_num, rank, &dskdat[sample]);
                Display_Deskew_Settings(node, ddr_interface_num, rank, &dskdat[sample], RD_DSK, VBL_DEV, "SAMPL");
            }

            VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: PRDT: Done SAMPLING\n", node, ddr_interface_num, rank); // FIXME? DEBUGGING ONLY

            // next, sum and average the deskew data for the current rank
            deskew_sum_and_average(node, ddr_interface_num, num_dsk_samples, dskdat, &dskavg);

            // finally, write the averaged DESKEW values
            Overwrite_Read_Deskew_Settings(node, ddr_interface_num, rank, &dskavg);

            VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: PRDT: Print AVERAGE\n", node, ddr_interface_num, rank); // FIXME? DEBUGGING ONLY
            // use TME for FINAL version verbosity
            Display_Deskew_Settings(node, ddr_interface_num, rank, &dskavg, RD_DSK, VBL_TME, "AVERG");

            // for debug, print out how many bits differed from the avg on each sample
            VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: DSK_AVG: avg diffs by sample: ",
                   node, ddr_interface_num, rank); // FIXME? DEBUGGING verbosity correct? 
            for (int sample = 0; sample < num_dsk_samples; sample++) {
                int num_diff =
                    Compare_and_Copy_Deskew_Settings(node, ddr_interface_num, &dskdat[sample],
                                                     &dskavg, 0/*compare only*/);
                VB_PRT(VBL_DEV, "%d, ", num_diff);
            }
            VB_PRT(VBL_DEV, "\n");
        } /* for (int rank = 0; rank < 4; rank++) */

    } else {
        ret = Perform_Read_Deskew_Training_rank(node, rank_mask, ddr_interface_num,
                                                init_data, overrides, print_flags);
    }
    return ret;
}

unsigned short
load_dac_override(int node, int ddr_interface_num,
                  int dac_value, int byte)
{
    bdk_lmcx_dll_ctl3_t ddr_dll_ctl3;
    // single bytelanes incr by 1; A is for ALL
    int bytex = (byte == 0x0A) ? byte : byte + 1;

    ddr_dll_ctl3.u = BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(ddr_interface_num));

    SET_DDR_DLL_CTL3(byte_sel, bytex);
    if (bdk_is_model(OCTEONTX_CN8XXX))
        dac_value >>= 1; // on CN8, only 7-bit field, use MS bits
    SET_DDR_DLL_CTL3(offset, dac_value); 

    ddr_dll_ctl3.s.bit_select    = 0x9; /* No-op */
    DRAM_CSR_WRITE(node, BDK_LMCX_DLL_CTL3(ddr_interface_num), ddr_dll_ctl3.u);

    ddr_dll_ctl3.s.bit_select    = 0xC; /* Vref bypass setting load */
    DRAM_CSR_WRITE(node, BDK_LMCX_DLL_CTL3(ddr_interface_num), ddr_dll_ctl3.u);

    ddr_dll_ctl3.s.bit_select    = 0xD; /* Vref bypass on. */
    DRAM_CSR_WRITE(node, BDK_LMCX_DLL_CTL3(ddr_interface_num), ddr_dll_ctl3.u);

    ddr_dll_ctl3.s.bit_select    = 0x9; /* No-op */
    DRAM_CSR_WRITE(node, BDK_LMCX_DLL_CTL3(ddr_interface_num), ddr_dll_ctl3.u);

    BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(ddr_interface_num)); // flush writes

    return ((unsigned short) GET_DDR_DLL_CTL3(offset));
}

// arg dac_or_dbi is 1 for DAC, 0 for DBI
// returns 9 entries (bytelanes 0 through 8) in settings[]
// returns 0 if OK, -1 if a problem
int read_DAC_DBI_settings(int node, int ddr_interface_num, int rank,
                          int dac_or_dbi, int *settings)
{
    deskew_data_t dskdat;
    int byte_lane;
    int bit_num = (dac_or_dbi) ? 9/*DAC*/ : 8/*DBI*/;

    Get_Deskew_Settings(node, ddr_interface_num, rank, &dskdat);

    for (byte_lane = 0; byte_lane < 9; byte_lane += 1) { // always assume ECC is available
	settings[byte_lane] = dskdat.bytes[byte_lane].bits[bit_num];
    } /* for (byte_lane = 0; byte_lane <= 8; byte_lane += 1) */

    return 0;
}

// print out the DAC or DBI settings array
// arg dac_or_dbi is 1 for DAC, 0 for DBI
void display_DAC_DBI_settings(int node, int lmc, int rank, int dac_or_dbi,
                                int ecc_ena, int *settings, char *title)
{
    int byte;
    int flags;
    int deskew;
    const char *fc = " ?-=+*#&";

    const char *rank_str, *blank_str;
    get_rank_and_blank_strs(rank, &rank_str, &blank_str);

    ddr_print("N%d.LMC%d%s: %s %s %s Settings [%d:0] :",
              node, lmc, rank_str, blank_str, title,
              (dac_or_dbi)?"DAC":"DBI", 7+ecc_ena);

    for (byte = (7+ecc_ena); byte >= 0; --byte) { // FIXME: what about 32-bit mode?
        if (dac_or_dbi) { // DAC
            flags  = 1; // say its locked to get blank
            deskew = settings[byte] & 0xff;
        } else { // DBI
            flags  = settings[byte] & 7;
            deskew = (settings[byte] >> 3) & 0x7f;
        }
        ddr_print(" %3d %c", deskew, fc[flags^1]);
    }
    ddr_print("\n");
}

int Run_Offset_and_VREF_Training(bdk_node_t node,
                                 int ddr_interface_num,
                                 dram_init_data_t *init_data,
                                 dram_training_data_t *training)
{
    int ddr_interface_64b =         init_data->refs.ddr_interface_64b;
    int use_ecc =                   init_data->refs.use_ecc;
    int print_DAC_DBI_settings =    training->print_DAC_DBI_settings;
    int rankx =                     training->by_rank; // only used for printing!
    int rank_mask =                 training->rank_mask;
    int *dac_settings =             training->dac_settings;
    int dac_eval_retries = 0;

    for (dac_eval_retries = 0; dac_eval_retries < DAC_RETRIES_LIMIT; dac_eval_retries++) {

        /* 6.9.8 LMC Offset Training
           LMC requires input-receiver offset training. */
        Perform_Offset_Training(node, rank_mask, ddr_interface_num);

        /* 6.9.9 LMC Internal Vref Training
           LMC requires input-reference-voltage training. */
        Perform_Internal_VREF_Training(node, rank_mask, ddr_interface_num, training);

        // maybe display the DAC values for a sample
        if (dram_is_verbose(VBL_DEV) && print_DAC_DBI_settings) { // FIXME: DEBUGGING verbosity
            display_DAC_DBI_settings(node, ddr_interface_num, rankx/*rank*/, /*DAC*/1,
                                     use_ecc, dac_settings, "Internal VREF");
        }

        // evaluate the DAC settings and retry if any issues
        if (evaluate_DAC_settings(ddr_interface_64b, use_ecc, dac_settings)) {
            VB_PRT(VBL_DEV, "N%d.LMC%d: DDR4 internal VREF DAC settings inconsistent; retrying....\n",
                   node, ddr_interface_num); // FIXME? DEBUGGING verbosity correct? 
            training->total_dac_eval_retries += 1;
        } /* if (evaluate_DAC_settings(ddr_interface_64b, use_ecc, dac_settings)) */
        else
            break;

    } /* for (dac_eval_retries = 0; dac_eval_retries < DAC_RETRIES_LIMIT; dac_eval_retries++) */

    if (dac_eval_retries >= DAC_RETRIES_LIMIT) {
        training->dac_eval_exhausted += 1;
    } /* if (dac_eval_retries >= DAC_RETRIES_LIMIT) */

    return dac_eval_retries;
}

void Set_DAC_Overrides(bdk_node_t node, int ddr_interface_num,
                        int last_lane, int use_ecc, int *dac_settings)
{
    // allow override of any byte-lane internal VREF
    int overrode_vref_dac = 0;
    int vref_dac_bias = 0;
    int do_overwrite;
    int lane;
    const char *s;

    if ((s = lookup_env_parameter("ddr_vref_dac_bias")) != NULL) {
        vref_dac_bias = strtoull(s, NULL, 0);
        overrode_vref_dac = 1;
    }

    for (lane = 0; lane < last_lane; lane++) {
        do_overwrite = 0;
        if (vref_dac_bias != 0) {
            dac_settings[lane] += vref_dac_bias; // BIAS
            do_overwrite = 1;
        } else
        if ((s = lookup_env_parameter("ddr%d_vref_dac_byte%d", ddr_interface_num, lane)) != NULL) {
            dac_settings[lane] = strtoull(s, NULL, 0); // NEW
            overrode_vref_dac = 1;
            do_overwrite = 1;
        }
        if (do_overwrite) { // finally, write the new DAC value if necessary
            load_dac_override(node, ddr_interface_num, dac_settings[lane], lane);
        }
    }
    if (overrode_vref_dac) {
        display_DAC_DBI_settings(node, ddr_interface_num, 0/*rank*/, /*DAC*/1,
                                 use_ecc, dac_settings, "Override VREF");
    }
}


static void
Perform_Training_on_Rank_Mask_Part1(bdk_node_t node,
                                    int ddr_interface_num,
                                    dram_init_data_t *init_data,
                                    dram_overrides_t *overrides,
                                    dram_training_data_t *training)
{
    int dimm_count =                init_data->refs.dimm_count;
    int use_ecc =                   init_data->refs.use_ecc;
    int spd_rdimm =                 init_data->refs.spd_rdimm;
    int spd_lrdimm =                init_data->refs.spd_lrdimm;
    int rank_mask =                 training->rank_mask;
    const char *s;

    // HRM-CN9XXX Section 7.9.6.4-7
    // Bring DRAM out of self refresh, do powerup/init
    // NOTE: this is done earlier (in Finish_Early_LMC_Init) on CN9XXX
    if (!bdk_is_model(OCTEONTX_CN9XXX)) {
        Bring_Up_DRAM_for_Training(node, ddr_interface_num, rank_mask, init_data);
    }

    //  LRDIMM DB ZQCal Long pre-processing must be performed here,
    //  just after the powerup/init sequence.
    if (spd_lrdimm) {
        lrdimm_db_zqcal_long(node, ddr_interface_num);
    }

    if (spd_rdimm) {

        // disable parity generation if currently active
        Change_Parity_Generation(node, ddr_interface_num, init_data, overrides, /*OFF*/0);

        VB_PRT(VBL_FAE, "Starting RDIMM init sequence...\n");

        // DRAM MPR Initialization
        // NOTE: this must be done for all chips
        // HRM-CN9XXX 7.9.7
        change_rdimm_mpr_pattern(node, rank_mask, ddr_interface_num, dimm_count);

        VB_PRT(VBL_FAE, "Finished RDIMM init sequence.\n");

        // enable parity generation if currently active
        Change_Parity_Generation(node, ddr_interface_num, init_data, overrides, /*ON*/1);
    }

    // More LRDIMM pre-processing must be performed here, before Deskew Training et al..
    // in lrdimm mode, host write-leveling training needs to occur
    // before we can do PBA accesses, so run write leveling here
    // will need to run again below after we have setup some of the
    // values, but Denali requires that we run here
    if (spd_lrdimm) {

        int dac_settings[9];
        // read and maybe display the DAC values for a sample
        read_DAC_DBI_settings(node, ddr_interface_num, 0/*rank*/, /*DAC*/1, dac_settings);
        display_DAC_DBI_settings(node, ddr_interface_num, 0/*rank*/, /*DAC*/1,
                                 use_ecc, dac_settings, "INITIAL Internal VREF");

        // FIXME? do we need this, or is it only DENALI?
        // second step in LRDIMM init...
        int enable_pre_wl = 1; // FIXME? default to ON
        if ((s = lookup_env_parameter("ddr_enable_pre_wl")) != NULL) {
            enable_pre_wl = !!strtoul(s, NULL, 0);
        }
        if (enable_pre_wl) {
            ddr_print("N%d.LMC%d: LRDIMM: Enabling pre-training HWL.\n",
                      node, ddr_interface_num);
            lrdimm_db_pre_wl(node, ddr_interface_num, init_data);
        }

        // turn ON parity mode if active for LRDIMMs just before MREP training
        //Set_Parity_Mode(node, ddr_interface_num, init_data, /*ON*/1);

        // LRDIMM MREP training
        int mrep_ret =
            lrdimm_db_mrep_dwl_train(node, ddr_interface_num, init_data, MREP_MODE);

        // turn OFF parity mode if active for LRDIMMs just after MREP training, even if fail
        //Set_Parity_Mode(node, ddr_interface_num, init_data, /*OFF*/0);

        if (!mrep_ret) { // return 0 if a problem with MREP training...
            error_print("N%d.LMC%d: MREP training FAILED - aborting\n", node, ddr_interface_num);
            return /*0*/; // FIXMELATER
        }

        // LRDIMM MRD training
        if (!lrdimm_db_mrd_mwd_train(node, ddr_interface_num, init_data, MRD_MODE)) {
            error_print("N%d.LMC%d: MRD training FAILED - aborting\n", node, ddr_interface_num);
            return /*0*/; // FIXMELATER
        }

        // FIXME: check for any LMC errors so far
        if (bdk_is_model(OCTEONTX_CN8XXX))
            check_cn8xxx_lmc(node, ddr_interface_num, 0);
    }
}

static void
Get_DAC_Samples_and_Average(bdk_node_t node,
                            int ddr_interface_num,
                            dram_init_data_t *init_data,
                            dram_overrides_t *overrides,
                            dram_training_data_t *training)
{
    int ddr_interface_64b =         init_data->refs.ddr_interface_64b;
    int use_ecc =                   init_data->refs.use_ecc;
    int *dac_settings =             training->dac_settings;
    int sample, lane;
    int last_lane = ((ddr_interface_64b) ? 8 : 4) + use_ecc;
    int num_dac_samples = DEFAULT_DAC_SAMPLES;

    training->total_dac_eval_retries = 0;
    training->dac_eval_exhausted = 0;

    // Gather num_dac_samples of DAC settings using the rank mask
    for (sample = 0; sample < num_dac_samples; sample++) {

        Run_Offset_and_VREF_Training(node, ddr_interface_num, init_data, training);

        if (training->dac_eval_exhausted) {
            VB_PRT(VBL_DEV, "N%d.LMC%d: DDR internal VREF DAC settings: total retries %d, exhausted %d\n",
                   node, ddr_interface_num, training->total_dac_eval_retries,
                   training->dac_eval_exhausted);
        }

        // Save sample DAC for later evaluation
        for (lane = 0; lane < last_lane; lane++) {
            training->lanes[lane].bytes[sample] = dac_settings[lane];
        }
    } /* for (sample = 0; sample < num_dac_samples; sample++) */

    // Average the samples
    for (lane = 0; lane < last_lane; lane++) {
        int16_t *byte0 = &training->lanes[lane].bytes[0];
        dac_settings[lane] = process_samples_average(byte0, num_dac_samples,
                                                     ddr_interface_num, lane);
    }
}

static void
Perform_Training_on_Rank_Mask_Part2(bdk_node_t node,
                                    int ddr_interface_num,
                                    dram_init_data_t *init_data,
                                    dram_overrides_t *overrides,
                                    dram_training_data_t *training)
{
    int ddr_interface_64b =         init_data->refs.ddr_interface_64b;
    int use_ecc =                   init_data->refs.use_ecc;
    int spd_lrdimm =                init_data->refs.spd_lrdimm;
    int dram_width =                init_data->refs.dram_width;
    int rank_mask =                 training->rank_mask;
    int *dac_settings =             training->dac_settings;
    int lane;
    int last_lane = ((ddr_interface_64b) ? 8 : 4) + use_ecc;

    // Init data structure to hold DEFAULT_DAC_SAMPLES for each lane
    for (lane = 0; lane < last_lane; lane++) {
        dac_settings[lane] = 127; // init all lanes to reset value
    }

    // Run the training multiple times and average results
    training->print_DAC_DBI_settings = 1;

    // We can do CN9XXX internal VREF by ranks, so...
    if (bdk_is_model(OCTEONTX_CN9XXX)) {
        int num_ranks_todo = __builtin_popcount(rank_mask);

        typedef struct {
            int16_t bytes[4]; // enough for 4 ranks
        } bytelane_ranks_t;
        typedef struct {
            bytelane_ranks_t lanes[9]; // all 9 bit-lanes
        } average_set_t;
        average_set_t averages;

        memset(&averages, 0, sizeof(average_set_t));
        
        // check for 1Rx4, and do special handling for the one rank;
        // that is, do sampling twice, once for DQ3 and once for DQ4,
        // and then average them together
        if ((num_ranks_todo == 1) && (dram_width == 4)) {
            VB_PRT(VBL_DEV, "N%d.LMC%d: 1Rx4 1DPC special internal VREF DAC handling\n",
                      node, ddr_interface_num); // FIXME? verbosity correct?
            training->rank_mask = 1; // only rank 0
            for (int set = 0; set < 2; set++) {
                // change the VREF sel: 0=DQ3, 1=DQ4
                DRAM_CSR_MODIFY(phy, node, BDK_LMCX_PHY_CTL(ddr_interface_num),
                                phy.cn9.rx_vref_sel = set);

                Get_DAC_Samples_and_Average(node, ddr_interface_num, init_data, overrides, training);
                display_DAC_DBI_settings(node, ddr_interface_num, set+4, /*DAC*/1,
                                         use_ecc, dac_settings, "DQx Aver VREF");

                // save the average of the DQx samples
                for (lane = 0; lane < last_lane; lane++) {
                    averages.lanes[lane].bytes[set] = dac_settings[lane];
                }
            } /* for (int set = 0; set < 2; set++) */
            // now average the DQx averages together
            for (lane = 0; lane < last_lane; lane++) {
                int16_t *byte0 = &averages.lanes[lane].bytes[0];
                dac_settings[lane] = process_samples_average(byte0, 2/*sets*/,
                                                             ddr_interface_num, lane);
            }
            // restore original CSR field setting for DQ3
            DRAM_CSR_MODIFY(phy, node, BDK_LMCX_PHY_CTL(ddr_interface_num),
                            phy.cn9.rx_vref_sel = 0);
        }
        else
        { // 2Rx? or multi-DIMM
            // do sampling once for each rank, then average them together
            int rank_count = 0;
            for (int rank = 0; rank < 4; rank++) {
                if (!(rank_mask & (1 << rank)))
                    continue;
                training->rank_mask = 1 << rank; // make a mask

                Get_DAC_Samples_and_Average(node, ddr_interface_num, init_data, overrides, training);
                display_DAC_DBI_settings(node, ddr_interface_num, rank, /*DAC*/1,
                                         use_ecc, dac_settings, "Rank Avg VREF");

                // save the rank average for later
                for (lane = 0; lane < last_lane; lane++) {
                    averages.lanes[lane].bytes[rank_count] = dac_settings[lane];
                }
                rank_count += 1; // update for next rank
            }
            // now average the rank averages together
            for (lane = 0; lane < last_lane; lane++) {
                int16_t *byte0 = &averages.lanes[lane].bytes[0];
                dac_settings[lane] = process_samples_average(byte0, rank_count,
                                                             ddr_interface_num, lane);
            }
        }
    } else { // is CN8XXX
        // do the sampling/averaging only once, as we cannot do it per rank
        Get_DAC_Samples_and_Average(node, ddr_interface_num, init_data, overrides, training);
    }

    training->rank_mask = rank_mask; // restore original rank_mask

    // last displayed info is channel average always
    display_DAC_DBI_settings(node, ddr_interface_num, -1/*rank*/, /*DAC*/1,
                             use_ecc, dac_settings, "Chan Avg VREF");

    // write the final DAC values
    for (lane = 0; lane < last_lane; lane++) {
        load_dac_override(node, ddr_interface_num, dac_settings[lane], lane);
    }

    // check for any envvar DAC overrides found
    Set_DAC_Overrides(node, ddr_interface_num, last_lane, use_ecc, dac_settings);

    // save for posterity... er, possible margining use...
    for (lane = 0; lane < last_lane; lane++) {
        final_dac_settings[ddr_interface_num].bytes[lane] = dac_settings[lane];
    }

    // More LRDIMM pre-processing must be performed here, before Deskew Training et al..
    if (spd_lrdimm) {

        // LRDIMM DWL training
        if (!lrdimm_db_mrep_dwl_train(node, ddr_interface_num, init_data, DWL_MODE)) {
            error_print("N%d.LMC%d: DWL training FAILED - aborting\n", node, ddr_interface_num);
            return /*0*/; // FIXMELATER
        }

        // LRDIMM MWD training
        if (!lrdimm_db_mrd_mwd_train(node, ddr_interface_num, init_data, MWD_MODE)) {
            error_print("N%d.LMC%d: MWD training FAILED - aborting\n", node, ddr_interface_num);
            return /*0*/; // FIXMELATER
        }

        // FIXME: check for any LMC errors so far
        if (bdk_is_model(OCTEONTX_CN8XXX))
            check_cn8xxx_lmc(node, ddr_interface_num, 0);
    }
}

int Train_Channel(bdk_node_t node,  int ddr_interface_num,
                  dram_init_data_t *init_data,
                  dram_overrides_t *overrides,
                  dram_training_data_t *training)
{
    //int ddr_interface_64b =         init_data->refs.ddr_interface_64b;
    int restart_if_dsk_incomplete = overrides->init.restart_if_dsk_incomplete;
    int enable_write_deskew =       overrides->init.enable_write_deskew;
    int enable_x4_hwl_adj   =       overrides->init.enable_x4_hwl_adj;
    int rank_mask =                 training->rank_mask;

    int internal_retries = 0;
    int deskew_training_errors;

    Perform_Training_on_Rank_Mask_Part1(node, ddr_interface_num, init_data, overrides, training);

    for (internal_retries = 0; internal_retries < DEFAULT_INTERNAL_VREF_TRAINING_LIMIT; internal_retries++) {

        Perform_Training_on_Rank_Mask_Part2(node, ddr_interface_num, init_data, overrides, training);

        deskew_training_errors =
            Perform_Read_Deskew_Training(node, rank_mask, ddr_interface_num, init_data, overrides, 0);

        // All the Deskew lock and saturation retries (may) have been done,
        //  but we ended up with some sort of errors; so, as a last ditch effort,
        //  try again, starting with offset and internal Vref trainings...
        if (deskew_training_errors) {
            VB_PRT(VBL_FAE, "N%d.LMC%d: Deskew training results still unsettled - retrying internal Vref training (%d)\n",
                   node, ddr_interface_num, internal_retries);
        }
        else
            break; //Read Deskew Training ran clean drop out of retry loop

    } /*for (internal_retries = 0; internal_retries < DEFAULT_INTERNAL_VREF_TRAINING_LIMIT; internal_retries++) */

    if (internal_retries >= DEFAULT_INTERNAL_VREF_TRAINING_LIMIT) {
        if (restart_if_dsk_incomplete) {
            ddr_print("N%d.LMC%d: INFO: Deskew training incomplete - %d retries exhausted, Restarting LMC init...\n",
                  node, ddr_interface_num, internal_retries);
            return DESKEW_TRAINING_FAILED_RESTART_POSSIBLE; // 0 indicates restart possible...
        }
        VB_PRT(VBL_FAE, "N%d.LMC%d: Deskew training incomplete - %d retries exhausted, but continuing...\n",
               node, ddr_interface_num, internal_retries);
    }

    // print final deskew results for any debugging verbosity
    Validate_Read_Deskew_Training(node, ddr_interface_num, rank_mask, &deskew_training_results, VBL_NORM, "FINAL");

    // setup write bit-deskew if enabled...
    if (enable_write_deskew || enable_x4_hwl_adj) {
        ddr_print("N%d.LMC%d: WRITE BIT-DESKEW feature enabled - going NEUTRAL.\n",
                  node, ddr_interface_num);
        Neutral_Write_Deskew_Setup(node, ddr_interface_num, rank_mask);
    } /* if (enable_write_deskew) */

    return DESKEW_TRAINING_COMPLETED;
}

static int
Perform_Deskew_Init(bdk_node_t node,
                    int ddr_interface_num,
                    dram_init_data_t *init_data,
                    dram_overrides_t *overrides)
{
    int rank_mask =                 init_data->refs.rank_mask;
    int ddr_interface_64b =         init_data->refs.ddr_interface_64b;
    int use_ecc =                   init_data->refs.use_ecc;
    int enable_by_rank_init =       overrides->init.enable_by_rank_init;

    int lane;
    int last_lane = ((ddr_interface_64b) ? 8 : 4) + use_ecc;
    int training_result;

    dram_training_data_t training_data_structure;
    dram_training_data_t *training = &training_data_structure;

    memset(training, 0, sizeof(dram_training_data_t));

    //Init data structure to hold DEFAULT_DAC_SAMPLES for each lane
    for (lane = 0; lane < last_lane; lane++) {
        training->dac_settings[lane] = 127; // init all lanes to reset value
    }
    training->rank_mask = rank_mask; // set the full mask by default

#if ALLOW_BY_RANK_INIT
    if (enable_by_rank_init) {

        int saved_rank_mask;
        int by_rank = 0;
        deskew_data_t rank_dsk[2];
        dac_data_t rank_dac[2];

        saved_rank_mask = rank_mask;

        //Perform Training for one rank at a time, 2 max
        for (by_rank = 1; by_rank >= 0; by_rank--) {
            rank_mask = (1 << by_rank);

            // if the rank in question is not in the original mask don't test it
            if (! (rank_mask & saved_rank_mask))
                continue;
            // Once you have tested rank 0, use full rank mask for the last pass
            if (by_rank == 0)
                rank_mask = saved_rank_mask;

            training->by_rank = by_rank;
            training->rank_mask = rank_mask;

            ddr_print("\n>>>>> BY_RANK: starting rank %d with mask 0x%02x\n\n",
                      by_rank, rank_mask);

            training_result = Train_Channel(node, ddr_interface_num, init_data, overrides, training);
            if (training_result != DESKEW_TRAINING_COMPLETED)
                return training_result;

            
            read_DAC_DBI_settings(node, ddr_interface_num, by_rank, /*dac*/1, &rank_dac[by_rank].bytes[0]);
            Get_Deskew_Settings(node, ddr_interface_num, by_rank, &rank_dsk[by_rank]);
            ddr_print("\n>>>>> BY_RANK: ending rank %d\n\n", by_rank);
        }

        rank_mask = saved_rank_mask;
        perform_ddr_init_sequence(node, rank_mask, ddr_interface_num);

        process_by_rank_dac(node, ddr_interface_num, rank_mask, rank_dac);
        process_by_rank_dsk(node, ddr_interface_num, rank_mask, rank_dsk);

        // FIXME: set this to prevent later checking!!!
        overrides->init.disable_deskew_training = 1;

        ddr_print("\n>>>>> BY_RANK: FINISHED!!\n\n");
    }
    else {
        training_result = Train_Channel(node, ddr_interface_num, init_data, overrides, training);
    }
#else
    training_result = Train_Channel(node, ddr_interface_num, init_data, overrides, training);
#endif /* ALLOW_BY_RANK_INIT */

    return training_result;
}

void Perform_Disabled_Deskew_Init(bdk_node_t node,
                                int ddr_interface_num,
                                dram_init_data_t *init_data)
{
    int dimm_count =                init_data->refs.dimm_count;
    int rank_mask =                 init_data->refs.rank_mask;
    int use_ecc =                   init_data->refs.use_ecc;
    int spd_rdimm =                 init_data->refs.spd_rdimm;
    int spd_lrdimm =                init_data->refs.spd_lrdimm;
    int ddr_interface_64b =         init_data->refs.ddr_interface_64b;

    int lane;
    int last_lane = ((ddr_interface_64b) ? 8 : 4) + use_ecc;
    int dac_settings[9];

    // HRM-CN9XXX Section 7.9.6.4-7
    //Bring DRAM out of self refresh, do powerup/init
    Bring_Up_DRAM_for_Training(node, ddr_interface_num, rank_mask, init_data);

    //  LRDIMM DB ZQCal Long pre-processing must be performed here,
    //  just after the powerup/init sequence.
    if (spd_lrdimm) {
        lrdimm_db_zqcal_long(node, ddr_interface_num);
    }

    // NOTE: this must be done for pass 2.x and pass 1.x
    if (spd_rdimm) {
        VB_PRT(VBL_FAE, "Starting RDIMM init sequence...\n");
        change_rdimm_mpr_pattern(node, rank_mask, ddr_interface_num, dimm_count);
        VB_PRT(VBL_FAE, "Finished RDIMM init sequence.\n");
    }

    ddr_print("N%d.LMC%d: internal VREF Training disabled, leaving them in RESET.\n",
              node, ddr_interface_num);

    //Set overrides
    for (lane = 0; lane < last_lane; lane++) {
        dac_settings[lane] = 127; // init all lanes to reset value
    }
    Set_DAC_Overrides(node, ddr_interface_num, last_lane, use_ecc, dac_settings);

    ddr_print("N%d.LMC%d: Deskew Training disabled, printing settings before HWL.\n",
                  node, ddr_interface_num);

    // FIXME: treat this as the final DSK print from now on, and print if VBL_NORM or above
    // also, save the results of the original training
    Validate_Read_Deskew_Training(node, ddr_interface_num, rank_mask, &deskew_training_results, VBL_NORM, "PDDSK");

    // save for posterity... er, possible margining use...
    for (lane = 0; lane < last_lane; lane++) {
        final_dac_settings[ddr_interface_num].bytes[lane] = dac_settings[lane];
    }
}

void Run_ZQCS_Calibration(bdk_node_t node, int ddr_interface_num, uint64_t tclk_psecs)
{
    bdk_lmcx_config_t lmc_config;
    int save_ref_zqcs_int;
    uint64_t temp_delay_usecs;

    lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(ddr_interface_num));

    /* Temporarily select the minimum ZQCS interval and wait
       long enough for a few ZQCS calibrations to occur.  This
       should ensure that the calibration circuitry is
       stabilized before read/write leveling occurs. */
    save_ref_zqcs_int         = lmc_config.s.ref_zqcs_int;
    lmc_config.s.ref_zqcs_int = 1 | (32<<7); /* set smallest interval */

    DRAM_CSR_WRITE(node, BDK_LMCX_CONFIG(ddr_interface_num), lmc_config.u);
    BDK_CSR_READ(node, BDK_LMCX_CONFIG(ddr_interface_num));

    /* Compute an appropriate delay based on the current ZQCS
       interval. The delay should be long enough for the
       current ZQCS delay counter to expire plus ten of the
       minimum intarvals to ensure that some calibrations
       occur. */
    temp_delay_usecs = (((uint64_t)save_ref_zqcs_int >> 7)
                        * tclk_psecs * 100 * 512 * 128) / (10000*10000)
        + 10 * ((uint64_t)32 * tclk_psecs * 100 * 512 * 128) / (10000*10000);

    VB_PRT(VBL_FAE, "N%d.LMC%d: Waiting %ld usecs for ZQCS calibrations to start\n",
            node, ddr_interface_num, temp_delay_usecs);
    bdk_wait_usec(temp_delay_usecs);

    lmc_config.s.ref_zqcs_int = save_ref_zqcs_int; /* Restore computed interval */

    DRAM_CSR_WRITE(node, BDK_LMCX_CONFIG(ddr_interface_num), lmc_config.u);
    BDK_CSR_READ(node, BDK_LMCX_CONFIG(ddr_interface_num));
}

int
Perform_DRAM_Training(bdk_node_t node,  int ddr_interface_num,
                      dram_init_data_t *init_data,
                      dram_overrides_t *overrides)
{
    uint64_t tclk_psecs =           init_data->refs.tclk_psecs;
    int disable_deskew_training =   overrides->init.disable_deskew_training;
    int training_result = DESKEW_TRAINING_COMPLETED;

    if (disable_deskew_training) {
        Perform_Disabled_Deskew_Init(node, ddr_interface_num, init_data);
    }
    else {
        training_result = Perform_Deskew_Init(node, ddr_interface_num, init_data, overrides);
        if (training_result != DESKEW_TRAINING_COMPLETED)
            return training_result;
    }

    Run_ZQCS_Calibration(node, ddr_interface_num, tclk_psecs);

    return DESKEW_TRAINING_COMPLETED;
}

