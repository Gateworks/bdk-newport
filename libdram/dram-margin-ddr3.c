/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libbdk-arch/bdk-csrs-mcc.h"
#include "libdram.h"
#include "dram-internal.h"

extern dram_verbosity_t dram_verbosity;

// set this to 1 to shorten the testing to exit when all byte lanes have errors
// having this at 0 forces the testing to take place over the entire range every iteration,
// hopefully ensuring an even load on the memory subsystem
#define EXIT_WHEN_ALL_LANES_HAVE_ERRORS 0

#define DEFAULT_TEST_BURSTS 5 // FIXME: this is what works so far...// FIXME was 7
int dram_margin_use_bursts = DEFAULT_TEST_BURSTS;

// dram_tune_rank_offset is used to offset the second area used in testing.
//
// If only a single-rank DIMM, the offset will be 256MB from the start of the first area,
//  which is more than enough for the restricted looping/address range actually tested...
//
// If a 2-rank DIMM, the offset will be the size of a rank's address space, so the effect
//  will be to have the first and second areas in different ranks on the same DIMM.
//
// So, we default this to single-rank, and it will be overridden when 2-ranks are detected.
//

// FIXME: ASSUME that we have DIMMS no less than 4GB in size

// offset to first area that avoids any boot stuff in low range (below 256MB)
#define AREA_BASE_OFFSET (1ULL << 28) // bit 28 always ON

// offset to duplicate area; may coincide with rank 1 base address for 2-rank 4GB DIMM
#define AREA_DUPE_OFFSET (1ULL << 31) // bit 31 always ON

// defaults to DUPE, but will be set elsewhere to offset to next RANK if multi-rank DIMM
extern uint64_t dram_tune_rank_offset;

// defaults to 0, but will be set elsewhere to the address offset to next DIMM if multi-slot
extern uint64_t dram_tune_dimm_offset;

// flag to indicate multi-ranks
static int dram_tune_rank_ena = 0;

// rank mask for current configuration
static int dram_tune_rank_mask;

// risk assessment counts
static int low_risk_count, needs_review_count;

// Utility routines
int is_dac_delta_low_risk(int orig, int maxm, int minm, int limit)
{
    //return (min(_abs(maxm - orig), _abs(orig - minm)) >= limit);
    if ((orig > maxm) || (orig < minm)) return 0; // not inside window, report problem
    return (min((maxm - orig), (orig - minm)) >= limit);
}

// cores to use
#define DEFAULT_USE_CORES 44   // FIXME: was (1 << CORE_BITS)
static int dram_tune_use_cores = DEFAULT_USE_CORES; // max cores to use, override available
static int dram_tune_max_cores; // max cores available on a node
#define CORE_SHIFT 22          // offset into rank_address passed to testing code


#define DEFAULT_MARGIN_EXT_GRAN 1 // sample for errors every N values
// NOTE: These are the values for both Range 1 and Range 2.
//       They are programmed along with the range "bit" which decides.
#define MIN_INDEX_MARGIN_EXT 0
#define MAX_INDEX_MARGIN_EXT 0x32
int dram_margin_ext_gran = DEFAULT_MARGIN_EXT_GRAN;

typedef struct {
    int index_start[4][9];
    int index_count[4][9];
    uint64_t index_windows [4][9];
    int index_best_start[4][9];
    int index_best_count[4][9];
} range_data_t;

typedef struct {
    range_data_t ranges[2];
} lmc_data_t;

static lmc_data_t these_lmcs[4];

#define LAST_BYTE 8
#define RANGE1 0
#define RANGE2 1

static int
get_computed_vref(bdk_node_t node, int lmc, int rankx/*, int maybe*/)
{
    uint64_t mpr_data[3];
    ddr4_mpr_read(node, lmc, rankx, /*page*/2, /*loc*/1, mpr_data);
    return (int)((mpr_data[0] & 0x00FE) >> 1);
}

extern uint64_t test_dram_byte_rank_errs[4][4]; // [lmc][rank]

// Write Voltage Margining
//
// NOTE: this is called once and does all LMCs
static void
margin_vref_ext(bdk_node_t node, int ddr_interface_64b)
{
    int lmc, num_lmcs = __bdk_dram_get_num_lmc(node);
    int lmc_mask = __bdk_dram_get_lmc_mask(node);
    int index;
    int start_index, end_index, incr_index;
    int rankx, rank_mask = dram_tune_rank_mask;

    int range;
    range_data_t *rdp;

    // NOTE: these need to be dimensioned
    uint64_t ops_sum[4], dclk_sum[4];
    uint64_t start_dram_dclk[4], stop_dram_dclk[4];
    uint64_t start_dram_ops[4], stop_dram_ops[4];
    uint64_t percent_x10;
    int errors;
    int tot_errors;
    int byte;

    // found a way to get the computed VREF from init
    int computed_vref_from_init[4][4]; // [lmc][rank]

    // get the computed VREFs from the active LMCs
    for (lmc = 0; lmc < num_lmcs; lmc++) {
        if (!(lmc_mask & (1 << lmc)))
            continue;
        for (rankx = 0; rankx < 4; rankx++) {
            if (!(rank_mask & (1 << rankx)))
                continue;
            computed_vref_from_init[lmc][rankx] = get_computed_vref(node, lmc, rankx/*, maybe_computed_vref*/);
        }
    }

    if (dram_margin_ext_gran != DEFAULT_MARGIN_EXT_GRAN) {
	ddr_print("N%d: Write Voltage Margining: changing sample granularity from %d to %d\n",
		  node, DEFAULT_MARGIN_EXT_GRAN, dram_margin_ext_gran);
    }
    // ensure sample is taken at the midway point if possible // FIXME?
    start_index = MIN_INDEX_MARGIN_EXT - (MIN_INDEX_MARGIN_EXT % dram_margin_ext_gran);
    end_index   = MAX_INDEX_MARGIN_EXT - (MAX_INDEX_MARGIN_EXT % dram_margin_ext_gran);
    incr_index  = dram_margin_ext_gran;

    memset(ops_sum,    0, sizeof(ops_sum));
    memset(dclk_sum,   0, sizeof(dclk_sum));

    memset(these_lmcs, 0, sizeof(these_lmcs));

    // construct the bytemask
    uint64_t bytemask = (ddr_interface_64b) ? 0xffffffffffffffffUL : 0x00000000ffffffffUL;

    ddr_print("N%d: Starting Margining tests for Write Voltage\n", node);

    // loop through the 2 ranges
    for (range = 0; range < 2; range++) {
	debug_print("N%d.LMC%d: Starting Range %d Testing\n", node, lmc, range+1);

	// now loop through selected legal values for the index...
	for (index = start_index; index <= end_index; index += incr_index) {

            // do the setup on the active LMC ranks
            for (lmc = 0; lmc < num_lmcs; lmc++) {
                if (!(lmc_mask & (1 << lmc)))
                    continue;

                // set VREF for this LMC and all its ranks
                for (rankx = 0; rankx < 4; rankx++) {
                    if (!(rank_mask & (1 << rankx)))
                        continue;
                    set_vref(node, lmc, rankx, range, index);
                }

                // record start cycle CSRs here for utilization measure
                start_dram_dclk[lmc] = BDK_CSR_READ(node, BDK_LMCX_DCLK_CNT(lmc));
                start_dram_ops[lmc]  = BDK_CSR_READ(node, BDK_LMCX_OPS_CNT(lmc));

            } /* for (lmc = 0; lmc < num_lmcs; lmc++) */

	    bdk_watchdog_poke();

	    // run the test(s)
	    // only 1 call should be enough, let the bursts, etc, control the load...
            tot_errors = run_dram_tuning_threads(node, num_lmcs, bytemask);
            if (tot_errors != 0) {
                VB_PRT(VBL_DEV2, "N%d: Threads for index %2d returned 0x%02x errors\n",
                       node, index, tot_errors);
            }

            // do the setup on the active LMC ranks
            for (lmc = 0; lmc < num_lmcs; lmc++) {
                if (!(lmc_mask & (1 << lmc)))
                    continue;

                rdp = &these_lmcs[lmc].ranges[range];

                // record stop cycle CSRs here for utilization measure
                stop_dram_dclk[lmc] = BDK_CSR_READ(node, BDK_LMCX_DCLK_CNT(lmc));
                stop_dram_ops[lmc]  = BDK_CSR_READ(node, BDK_LMCX_OPS_CNT(lmc));

                // accumulate...
                ops_sum[lmc]  += stop_dram_ops[lmc]  - start_dram_ops[lmc];
                dclk_sum[lmc] += stop_dram_dclk[lmc] - start_dram_dclk[lmc];

                // check errors by rank
                for (rankx = 0; rankx < 4; rankx++) {
                    if (!(rank_mask & (1 << rankx)))
                        continue;

                    errors = test_dram_byte_rank_errs[lmc][rankx];

                    for (byte = 0; byte < 8; byte++) {
                        rdp->index_windows[rankx][byte] <<= 1; // always put in a zero
                        if (errors & (1 << byte)) {
                            rdp->index_count[rankx][byte] = 0; // stop now always
                        } else { // no error in this byte lane
                            if (rdp->index_count[rankx][byte] == 0) { // first success, set run start
                                rdp->index_start[rankx][byte] = index;
                            }
                            rdp->index_count[rankx][byte] += incr_index; // bump run length

                            if (rdp->index_count[rankx][byte] > rdp->index_best_count[rankx][byte]) {
                                rdp->index_best_count[rankx][byte] = rdp->index_count[rankx][byte];
                                rdp->index_best_start[rankx][byte] = rdp->index_start[rankx][byte];
                            }
                            rdp->index_windows[rankx][byte] |= 1ULL; // for pass, put in a 1
                        }
                    } /* for (byte = 0; byte < 8; byte++) */

                    // only print when there are errors and verbose...
                    if (errors) {
                        VB_PRT(VBL_DEV2, "N%d.LMC%d.R%d: Write Voltage Margining Test %3d: errors 0x%02x\n",
                               node, lmc, rankx, index, errors);
                    }
                } /* for (rankx = 0; rankx < ??; rankx++) */

            } /* for (lmc = 0; lmc < num_lmcs; lmc++) */

	} /* for (index = start_index; index <= end_index; index += incr_index) */

    } /* for (range = 0; range < 2; range++) */

    // do the processing and printing on the active LMCs, ranks, then ranges
    for (lmc = 0; lmc < num_lmcs; lmc++) {
        if (!(lmc_mask & (1 << lmc)))
            continue;

        // now, organize the printout by rank, then range
        for (rankx = 0; rankx < 4; rankx++) {

            int combined_start[9];
            int combined_end[9];
            int start, last;
            int local_needs;

            if (!(rank_mask & (1 << rankx)))
                continue;

            printf("  \n");
            printf("N%d.LMC%d.R%d: Write Voltage Margining   : ", node, lmc, rankx);
            printf("    ECC/8 ");
            for (byte = 7; byte >= 0; byte--) {
                printf("   Byte %d ", byte);
            }
            printf(" \n");

            memset(combined_start, 0, sizeof(combined_start));
            memset(combined_end  , 0, sizeof(combined_end));

            for (range = 0; range < 2; range++) {

                int ranged_vref_from_init = computed_vref_from_init[lmc][rankx];
                if (range == RANGE2)
                    ranged_vref_from_init += 23;

                rdp = &these_lmcs[lmc].ranges[range];

                // FIXME FIXME
                // FIXME: borrow byte 3 values for ECC...
                rdp->index_best_start[rankx][8] = rdp->index_best_start[rankx][3];
                rdp->index_best_count[rankx][8] = rdp->index_best_count[rankx][3];

                for (byte = LAST_BYTE; byte >= 0; byte--) {
                    start = rdp->index_best_start[rankx][byte];
                    if (range == RANGE1) {
                        // combined end depends only on RANGE1 start + window length
                        last = start + rdp->index_best_count[rankx][byte] - incr_index;
                        combined_end[byte] = last; // range 1, just keep as-is
                    } else { // range 2, adjust down by 24, as 24 r2 maps to 0 r1
                        // combined start depends only on RANGE2 start relative to RANGE1
                        combined_start[byte] = start - 24;
                    }
                }

                // print the original values here for both
                // but for RANGE2, adjusted value may be too large
                printf("N%d.LMC%d.R%d: Range %d Original DAC%2s    : ", node, lmc, rankx, range+1,
                       (ranged_vref_from_init > 50) ? "**" : "  ");
                for (byte = LAST_BYTE; byte >= 0; byte--) {
                    printf("  %7d ", ranged_vref_from_init);
                }
                printf(" \n");

                // print the median values from the measured windows
                printf("N%d.LMC%d.R%d: Range %d Median DAC        : ", node, lmc, rankx, range+1);
                for (byte = LAST_BYTE; byte >= 0; byte--) {
                    index = rdp->index_best_start[rankx][byte] +
                        ((rdp->index_best_count[rankx][byte] - incr_index) / 2); // adj by incr
                    printf("  %7d ", index);
                }
                printf(" \n");

                // print the window sizes
                printf("N%d.LMC%d.R%d: Range %d Window Length     : ", node, lmc, rankx, range+1);
                for (byte = LAST_BYTE; byte >= 0; byte--) {
                    printf("  %7d ", rdp->index_best_count[rankx][byte] - incr_index);
                }
                printf(" \n");

                // print the window extents
                printf("N%d.LMC%d.R%d: Range %d Window Bounds     : ", node, lmc, rankx, range+1);
                for (byte = LAST_BYTE; byte >= 0; byte--) {
                    start = rdp->index_best_start[rankx][byte];
                    printf("%3d to %2d ", start,
                           start + rdp->index_best_count[rankx][byte] - incr_index);
                }
                printf(" \n");
#if 0
                // print the windows bit arrays
                printf("N%d.LMC%d.R%d: Range %d Window Bitmap      : ", node, lmc, rankx, range+1);
                for (byte = LAST_BYTE; byte >= 0; byte--) {
                    printf("  %07lx ", rdp->index_windows[rankx][byte]);
                }
                printf(" \n");
#endif
                if (ranged_vref_from_init > 50)
                    printf("** out of range.\n");

                printf(" \n"); // blank line after each range

            } /* for (range = 0; range < 2; range++) */

            //////////////// COMBINED printout comes last

            // print the original values (again)
            printf("N%d.LMC%d.R%d: Combined Original DAC     : ", node, lmc, rankx);
            for (byte = LAST_BYTE; byte >= 0; byte--) {
                printf("  %7d ", computed_vref_from_init[lmc][rankx]);
            }
            printf(" \n");

            // print the measured values
            printf("N%d.LMC%d.R%d: Combined Median DAC       : ", node, lmc, rankx);
            for (byte = LAST_BYTE; byte >= 0; byte--) {
                index = (combined_start[byte] + combined_end[byte]) / 2;
                printf("  %7d ", index);
            }
            printf(" \n");

            // print the combined window sizes
            printf("N%d.LMC%d.R%d: Combined Window Length    : ", node, lmc, rankx);
            for (byte = LAST_BYTE; byte >= 0; byte--) {
                printf("  %7d ", combined_end[byte] - combined_start[byte] + 1); // FIXME: is 1 correct always?
            }
            printf(" \n");

            // print the combined window extents
            local_needs = 0;
            printf("N%d.LMC%d.R%d: Combined Window Bounds    : ", node, lmc, rankx);
            for (byte = LAST_BYTE; byte >= 0; byte--) {
                int dac_min = combined_start[byte];
                int dac_max = combined_end[byte];
                // FIXME BELOW: 10 should be symbolic!!
                int is_low_risk = is_dac_delta_low_risk(computed_vref_from_init[lmc][rankx], dac_max, dac_min, 10);
                printf("%3d to %2d%c", combined_start[byte], combined_end[byte], (is_low_risk) ? ' ' : '<');
                if (is_low_risk)
                    low_risk_count++;
                else {
                    needs_review_count++;
                    local_needs++;
                }
            }
            printf(" %c\n", (local_needs) ? '?' : ' ');

            printf(" \n"); // blank line after combined

            // allow override of settings
            if (use_margin_settings) {
                // calc the average median DAC settings, since we now use only 1 per rank
                int sum = 0;
                for (byte = LAST_BYTE; byte >= 0; byte--)
                    sum += (combined_start[byte] + combined_end[byte]) / 2;
                set_vref(node, lmc, rankx, 0, (sum / (LAST_BYTE+1)));
                ddr_print(" \nN%d.LMC%d: Using Average (%d) of Combined Median DAC Settings\n",
                          node, lmc, (sum / (LAST_BYTE+1)));
            } else {
                // last step: use the computed VREF for restoring a working value
                set_vref(node, lmc, rankx, 0, computed_vref_from_init[lmc][rankx]); // range is in computed
            }

        } /* for (rankx = 0; rankx < 4; rankx++) */

        // finally, print the LMC utilization
        percent_x10 = ops_sum[lmc] * 1000 / dclk_sum[lmc];
        ddr_print(" \nN%d.LMC%d: ops %lu, cycles %lu, used %lu.%lu%%\n",
                  node, lmc, ops_sum[lmc], dclk_sum[lmc], percent_x10 / 10, percent_x10 % 10);

    } /* for (lmc = 0; lmc < num_lmcs; lmc++) */

}

static void margin_vref_int(bdk_node_t node, int ddr_interface_64b);

#define USE_L2_WAYS_LIMIT 0 // non-zero to enable L2 ways limiting

/*
 * Common margining tool for Read and Write Voltage
 */

// arg do_write - 1 = write, 0 = read
static int
perform_margining_vref_common(bdk_node_t node, int do_write)
{
    int ddr_interface_64b;
    int save_ecc_ena[4];
    bdk_lmcx_config_t lmc_config;
    int lmc, num_lmcs = __bdk_dram_get_num_lmc(node);
    int lmc_mask = __bdk_dram_get_lmc_mask(node);
    int num_active_lmcs = __builtin_popcount(lmc_mask);
    int is_cn9xxx = bdk_is_model(OCTEONTX_CN9XXX);
    const char *s;
#if USE_L2_WAYS_LIMIT
    int ways, ways_print = 0;
#endif
    int loops = 1, loop;
    char *mode_str = (do_write) ? "Write" : "Read";
    uint64_t orig_coremask;

    // clear the global counts
    low_risk_count = 0;
    needs_review_count = 0;

    // consult LMC_CONFIG contents for various information
    // FIXME? consult LMC0 only
    BDK_CSR_INIT(lmcx_config, node, BDK_LMCX_CONFIG(0));
    ddr_interface_64b = !lmcx_config.s.mode32b;
    dram_tune_rank_mask = lmcx_config.s.init_status;
    ddr_print("N%d: %s: rank_mask 0x%01x\n", node, __FUNCTION__, dram_tune_rank_mask);

    if (lmcx_config.s.rank_ena) { // replace the default offset when there is more than 1 rank...
	dram_tune_rank_offset = ((1ull << (28 + lmcx_config.s.pbank_lsb - 1)) * num_active_lmcs);
	ddr_print("N%d: %s: changing rank offset to 0x%lx\n", node, __FUNCTION__, dram_tune_rank_offset);
	dram_tune_rank_ena = 1;
    }
    if (dram_tune_rank_mask & 0x0c) { // bit 2 or 3 set indicates 2 DIMMs
	dram_tune_dimm_offset = ((1ull << (28 + lmcx_config.s.pbank_lsb)) * num_active_lmcs);
	ddr_print("N%d: %s: changing dimm offset to 0x%lx\n",
		  node, __FUNCTION__, dram_tune_dimm_offset);
    }

    // enable any non-running cores on this node
    orig_coremask = bdk_get_running_coremask(node);
    ddr_print("N%d: %s: Starting cores (mask was 0x%lx)\n",
	      node, __FUNCTION__, orig_coremask);
    bdk_init_cores(node, ~0ULL & ~orig_coremask);
    dram_tune_max_cores = bdk_get_num_running_cores(node);

    // but use only a certain number of cores, at most what is available
    if ((s = getenv("ddr_tune_use_cores")) != NULL) {
	dram_tune_use_cores = strtoul(s, NULL, 0);
	if (dram_tune_use_cores <= 0) // allow 0 or negative to mean all
	    dram_tune_use_cores = dram_tune_max_cores;
    }
    if (dram_tune_use_cores > dram_tune_max_cores)
	dram_tune_use_cores = dram_tune_max_cores;

    // see if we want to do the tuning more than once per LMC...
    if ((s = getenv("ddr_margin_use_loops"))) {
	loops = strtoul(s, NULL, 0);
    }

#if 0
    // FIXME: need to do this for both ext/write and int/read types
    // see if we want to change the granularity of the byte_offset sampling
    if ((s = getenv("ddr_margin_use_gran"))) {
	dram_margin_use_gran = strtoul(s, NULL, 0);
    }
#endif

    // allow override of the test repeats (bursts) per thread create
    if ((s = getenv("ddr_margin_use_bursts")) != NULL) {
        dram_margin_use_bursts = strtoul(s, NULL, 10);
    }

#if 0
    // allow override of the test pattern
    // FIXME: a bit simplistic...
    if ((s = getenv("ddr_tune_use_pattern")) != NULL) {
	int patno = strtoul(s, NULL, 10);
	if (patno == 2)
	    dram_tune_test_pattern = test_pattern_2;
	else if (patno == 3)
	    dram_tune_test_pattern = test_pattern_3;
	else // all other values use default
	    dram_tune_test_pattern = test_pattern_1;
    }
#endif

    // print current working values
    ddr_print("N%d: %s: started %d cores, use %d cores, use %d bursts.\n",
	      node, __FUNCTION__, dram_tune_max_cores, dram_tune_use_cores, dram_margin_use_bursts);

#if USE_L2_WAYS_LIMIT
    // see if L2 ways are limited
    if ((s = lookup_env_parameter("limit_l2_ways")) != NULL) {
	ways = strtoul(s, NULL, 10);
	ways_print = 1;
    } else {
	ways = bdk_l2c_get_num_assoc(node);
    }
#endif

#if USE_L2_WAYS_LIMIT
    /* Disable l2 sets for DRAM testing */
    limit_l2_ways(node, 0, ways_print);
#endif

    // NOTE: we disable ECC on all LMCs first, then do the testing, then re-enable ECC on all
    // NOTE: when we disable/enable individually, we get extraneous ECC error reports
    // NOTE: I think this is because of the use of cache PREFETCH in the lowest level code

    for (lmc = 0; lmc < num_lmcs; lmc++) {
        if (!(lmc_mask & (1 << lmc)))
            continue;

	// do setup for each active LMC
	debug_print("N%d: %s: disable ECC on LMC %d.\n", node, __FUNCTION__, lmc);

	/* Disable ECC for DRAM tests */
	lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(lmc));
	save_ecc_ena[lmc] = lmc_config.s.ecc_ena;
	lmc_config.s.ecc_ena = 0;
	DRAM_CSR_WRITE(node, BDK_LMCX_CONFIG(lmc), lmc_config.u);
	lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(lmc));

        if (is_cn9xxx) {
                bdk_dram_lmc_map_t lmc_map = bdk_dram_get_lmc_map(node, lmc);
                // disable the "ECC Checker" if we are doing ECC
                BDK_CSR_MODIFY(d, node, BDK_MCCX_LMCOEX_CFG(lmc_map.mcc, lmc_map.lmcoe),
                               d.s.dram_ecc_ena = 0);
        }
    } /* for (lmc = 0; lmc < num_lmcs; lmc++) */

    printf("  \n");
    printf("-------------------------------------\n");
    printf("N%d: Starting %s Voltage Margining.\n", node, mode_str);
    printf("  \n");

    // FIXME: for now, loop here to show what happens multiple times
    for (loop = 0; loop < loops; loop++) {

        /* Perform margining write or read voltage */
        if (do_write)
            margin_vref_ext(node, ddr_interface_64b); // ext = write
        else
            margin_vref_int(node, ddr_interface_64b); // int = read

    } /* for (loop = 0; loop < loops; loop++) */

    // print the Summary line(s) here
    printf("  \n");
    printf("N%d: %s Voltage Margining Summary  %s : %s ", node, mode_str,
	   (do_write) ? "" : " ",
	   (needs_review_count > 0) ? "Needs Review" : "Low Risk");

    if (needs_review_count > 0)
	printf("(%d)", needs_review_count);
    printf("\n");
    printf("-------------------------------------\n");
    printf("  \n");

    // perform cleanup on all active LMCs
    for (lmc = 0; lmc < num_lmcs; lmc++) {
        if (!(lmc_mask & (1 << lmc)))
            continue;

	debug_print("N%d: %s: re-enabling ECC on LMC %d.\n", node, __FUNCTION__, lmc);

	/* Restore ECC for DRAM tests */
	lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(lmc));
	lmc_config.s.ecc_ena = save_ecc_ena[lmc];
	DRAM_CSR_WRITE(node, BDK_LMCX_CONFIG(lmc), lmc_config.u);
	lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(lmc));

        if (is_cn9xxx) {
            bdk_dram_lmc_map_t lmc_map = bdk_dram_get_lmc_map(node, lmc);
            // enable the "ECC Checker" if we were doing ECC
            BDK_CSR_MODIFY(d, node, BDK_MCCX_LMCOEX_CFG(lmc_map.mcc, lmc_map.lmcoe),
                           d.s.dram_ecc_ena = save_ecc_ena[lmc]);
        }
    } /* for (lmc = 0; lmc < num_lmcs; lmc++) */

    // finish up...

#if USE_L2_WAYS_LIMIT
    /* Restore the l2 set configuration */
    limit_l2_ways(node, ways, ways_print);
#endif

    // put any cores on this node, that were not running at the start, back into reset
    uint64_t reset_coremask = bdk_get_running_coremask(node) & ~orig_coremask;
    if (reset_coremask) {
	ddr_print("N%d: %s: Stopping cores 0x%lx\n", node, __FUNCTION__,
		  reset_coremask);
	bdk_reset_cores(node, reset_coremask);
    } else {
	ddr_print("N%d: %s: leaving cores set to 0x%lx\n", node, __FUNCTION__,
		  orig_coremask);
    }

    return !!(needs_review_count > 0);

} /* perform_margining_vref_common */

//////////////////////////////////////////////////////

#define DEFAULT_MARGIN_INT_GRAN 5 // sample for errors every N values
#define MIN_INDEX_MARGIN_INT 0
#define MAX_INDEX_MARGIN_INT 0xFF
int dram_margin_int_gran = DEFAULT_MARGIN_INT_GRAN;

extern uint64_t test_dram_byte_lmc_errs[4];

// Read Voltage Margining
//
// NOTE: this is called once and does all LMCs
static void
margin_vref_int(bdk_node_t node, int ddr_interface_64b)
{
    int lmc, num_lmcs = __bdk_dram_get_num_lmc(node);
    int lmc_mask = __bdk_dram_get_lmc_mask(node);
    int index;
    int start_index, end_index, incr_index;
    //int rankx, rank_mask = dram_tune_rank_mask;

    // only need byte-lanes for internal VREF, not ranks or ranges
    typedef struct {
        int index_start[9];
        int index_count[9];
        int index_best_start[9];
        int index_best_count[9];
        uint64_t index_windows[9];
    } per_lmc_data_t;

    per_lmc_data_t all_lmcs_data[4];

    int *index_start;
    int *index_count;
    int *index_best_start;
    int *index_best_count;
    int *orig_dac_settings;
    uint64_t *index_windows;

    // NOTE: these need to be dimensioned
    uint64_t ops_sum[4], dclk_sum[4];
    uint64_t start_dram_dclk[4], stop_dram_dclk[4];
    uint64_t start_dram_ops[4], stop_dram_ops[4];

    uint64_t percent_x10;
    int errors;
    int tot_errors;
    int byte;
    int local_needs;

    if (dram_margin_int_gran != DEFAULT_MARGIN_INT_GRAN) {
	ddr_print("N%d: Margining: changing sample granularity from %d to %d\n",
		  node, DEFAULT_MARGIN_INT_GRAN, dram_margin_int_gran);
    }

    // ensure sample is taken at the midway point if possible // FIXME?
    incr_index  = dram_margin_int_gran;
    start_index = MIN_INDEX_MARGIN_INT - (MIN_INDEX_MARGIN_INT % dram_margin_int_gran);
    end_index   = MAX_INDEX_MARGIN_INT - (MAX_INDEX_MARGIN_INT % dram_margin_int_gran);

    memset(ops_sum, 0, sizeof(ops_sum));
    memset(dclk_sum, 0, sizeof(dclk_sum));

    // construct the bytemask
    uint64_t bytemask = (ddr_interface_64b) ? 0xffffffffffffffffUL : 0x00000000ffffffffUL;

    ddr_print("N%d: Starting Margining tests for Read Voltage\n", node);

    memset(all_lmcs_data, 0, sizeof(all_lmcs_data));

    // now loop through selected legal values for the index...
    for (index = start_index; index <= end_index; index += incr_index) {

	// do the setup on the active LMCs
        for (lmc = 0; lmc < num_lmcs; lmc++) {
            if (!(lmc_mask & (1 << lmc)))
                continue;

            // load the internal VREF values all at once
            load_dac_override(node, lmc, index, /*ALL*/0x0A);

            // record start cycle CSRs here for utilization measure
            start_dram_dclk[lmc] = BDK_CSR_READ(node, BDK_LMCX_DCLK_CNT(lmc));
            start_dram_ops[lmc]  = BDK_CSR_READ(node, BDK_LMCX_OPS_CNT(lmc));

        } /* for (lmc = 0; lmc < num_lmcs; lmc++) */

	bdk_watchdog_poke();

	// run the test(s)
	// only 1 call should be enough, let the bursts, etc, control the load...
	tot_errors = run_dram_tuning_threads(node, num_lmcs, bytemask);
	if (tot_errors > 0) {
            VB_PRT(VBL_DEV2, "N%d: Threads for index %2d returned 0x%02x errors\n",
                   node, index, tot_errors);
        }

	// do testing on the active LMCs
        for (lmc = 0; lmc < num_lmcs; lmc++) {
            if (!(lmc_mask & (1 << lmc)))
                continue;

            // record stop cycle CSRs here for utilization measure
            stop_dram_dclk[lmc] = BDK_CSR_READ(node, BDK_LMCX_DCLK_CNT(lmc));
            stop_dram_ops[lmc]  = BDK_CSR_READ(node, BDK_LMCX_OPS_CNT(lmc));

            // accumulate...
            ops_sum[lmc]  += stop_dram_ops[lmc]  - start_dram_ops[lmc];
            dclk_sum[lmc] += stop_dram_dclk[lmc] - start_dram_dclk[lmc];

            errors = test_dram_byte_lmc_errs[lmc];

            // setup pointers for this LMC
            index_start = all_lmcs_data[lmc].index_start;
            index_count = all_lmcs_data[lmc].index_count;
            index_best_start = all_lmcs_data[lmc].index_best_start;
            index_best_count = all_lmcs_data[lmc].index_best_count;
            index_windows = all_lmcs_data[lmc].index_windows;

            // now process the error mask
            for (byte = 0; byte < 8; byte++) {
                index_windows[byte] <<= 1; // always put in a zero
                if (errors & (1 << byte)) {
                    index_count[byte] = 0; // stop now always
                } else { // no error in this byte lane
                    if (index_count[byte] == 0) { // first success, set run start
                        index_start[byte] = index;
                    }
                    index_count[byte] += incr_index; // bump run length

                    if (index_count[byte] > index_best_count[byte]) {
                        index_best_count[byte] = index_count[byte];
                        index_best_start[byte] = index_start[byte];
                    }
                    index_windows[byte] |= 1ULL; // for pass, put in a 1
                }
            } /* for (byte = 0; byte < 8; byte++) */

            // only print when there are errors and very verbose...
            if (errors) {
                VB_PRT(VBL_DEV2, "N%d.LMC%d: Margining test for Read Voltage: value %3d: errors 0x%02x\n",
                       node, lmc, index, errors);
            }
        } /* for (lmc = 0; lmc < num_lmcs; lmc++) */

    } /* for (index = start_index; index <= end_index; index += incr_index) */

    // do processing on the active LMCs
    for (lmc = 0; lmc < num_lmcs; lmc++) {
        if (!(lmc_mask & (1 << lmc)))
            continue;

        // setup pointers for this LMC
        index_start = all_lmcs_data[lmc].index_start;
        index_count = all_lmcs_data[lmc].index_count;
        index_best_start = all_lmcs_data[lmc].index_best_start;
        index_best_count = all_lmcs_data[lmc].index_best_count;
        index_windows = all_lmcs_data[lmc].index_windows;

        orig_dac_settings = &final_dac_settings[lmc].bytes[0];

        // FIXME FIXME
        // FIXME: borrow ECC settings from the byte that most closely matches ECC orig DAC
        int min_diff = 1000, min_byte = 3; // FIXME: default to byte 3
        for (byte = 7; byte >= 0; byte--) {
            int diff = _abs(orig_dac_settings[8] - orig_dac_settings[byte]);
            if (diff < min_diff) { // only if closer to the ECC original DAC
                min_diff = diff;
                min_byte = byte;
            }
            if (diff == 0) // quit if it cannot be any closer
                break;
        }

        index_best_start[8] = index_best_start[min_byte];
        index_best_count[8] = index_best_count[min_byte];

        // print the LMC heading line
        printf("   \n"); // blank line first
        printf("N%d.LMC%d: Read Voltage Margining       : ", node, lmc);
        printf("      ECC/8 ");
        for (byte = 7; byte >= 0; byte--) {
            printf("     Byte %d ", byte);
        }
        printf("\n");

        // print the original values here
        printf("N%d.LMC%d: Original DAC Settings        : ", node, lmc);
        local_needs = 0;
        for (byte = 8; byte >= 0; byte--) {
            int dac_min = index_best_start[byte];
            int dac_max = dac_min + index_best_count[byte] - incr_index;
            // FIXME: limit of 15 should be symbolic, and maybe dependent on DDR type or DIMM type or??!!
            int is_low_risk = is_dac_delta_low_risk(orig_dac_settings[byte], dac_max, dac_min, 15);
            printf("    %7d%c", orig_dac_settings[byte], (is_low_risk) ? ' ' : '<');
            if (is_low_risk)
                low_risk_count++;
            else {
                needs_review_count++;
                local_needs++;
            }
        }
        printf(" %c\n", (local_needs) ? '?' : ' ');

        // print the median values from the measured windows
        printf("N%d.LMC%d: Median DAC Settings          : ", node, lmc);
        for (byte = 8; byte >= 0; byte--) {
            index = index_best_start[byte] +
                ((index_best_count[byte] - incr_index) / 2); // adj by incr
            printf("    %7d ", index);
        }
        printf("\n");

        // print the window sizes
        printf("N%d.LMC%d: Valid DAC Range              : ", node, lmc);
        for (byte = 8; byte >= 0; byte--) {
            printf("    %7d ", index_best_count[byte] - incr_index);
        }
        printf("\n");

        // print the window extents
        printf("N%d.LMC%d: Valid DAC Boundary           : ", node, lmc);
        for (byte = 8; byte >= 0; byte--) {
            int start = index_best_start[byte];
            printf(" %3d to %3d ", start,
                   start + index_best_count[byte] - incr_index);
        }
        printf("\n");

#if 0
        // print the windows bit arrays
        printf("N%d.LMC%d: Valid Window Bitmap          : ", node, lmc);
        for (byte = 8; byte >= 0; byte--) {
            printf("    %07lx ", index_windows[byte]);
        }
        printf("\n");
#endif

        // finally, print the LMC utilization
        percent_x10 = ops_sum[lmc] * 1000 / dclk_sum[lmc];
        ddr_print(" \nN%d.LMC%d: ops %lu, cycles %lu, used %lu.%lu%%\n",
                  node, lmc, ops_sum[lmc], dclk_sum[lmc], percent_x10 / 10, percent_x10 % 10);

        // allow override of settings
        if (use_margin_settings) {
            ddr_print(" \nN%d.LMC%d: Using Median DAC Settings\n", node, lmc);
            // store the median DAC settings
            for (byte = 0; byte < 9; byte++) {
                int new_setting = index_best_start[byte] + ((index_best_count[byte] - incr_index) / 2);
                load_dac_override(node, lmc, new_setting, byte);
            }
        } else {
            // restore the original settings
            for (byte = 0; byte < 9; byte++)
                load_dac_override(node, lmc, orig_dac_settings[byte], byte);
        }
    } /* for (lmc = 0; lmc < num_lmcs; lmc++) */

}

/*
 * Margining tool for Write Voltage (DRAM External VREF)
 */
int perform_margin_write_voltage(bdk_node_t node)
{
    return perform_margining_vref_common(node, /* write */1);
}
/*
 * Margining tool for Read Voltage (DRAM Internal VREF)
 */
int perform_margin_read_voltage(bdk_node_t node)
{
    return perform_margining_vref_common(node, /* read */0);
}
