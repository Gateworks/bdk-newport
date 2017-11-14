/***********************license start***********************************
* Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
* reserved.
*
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*
*   * Neither the name of Cavium Inc. nor the names of
*     its contributors may be used to endorse or promote products
*     derived from this software without specific prior written
*     permission.
*
* This Software, including technical data, may be subject to U.S. export
* control laws, including the U.S. Export Administration Act and its
* associated regulations, and may be subject to export or import
* regulations in other countries.
*
* TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
* AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
* WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
* TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
* REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
* DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
* OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
* PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
* QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
* ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
***********************license end**************************************/
#include <bdk.h>
#include "dram-internal.h"

extern dram_verbosity_t dram_verbosity;

static  int64_t dram_margin_threads_done;
static uint64_t dram_margin_threads_errs;
static uint64_t dram_margin_lmc_errs[4];

#if 0
/*
 * Suggested testing patterns.
 */
static const uint64_t test_pattern_2[] = {
    0xFFFFFFFFFFFFFFFFULL,
    0xAAAAAAAAAAAAAAAAULL,
    0xFFFFFFFFFFFFFFFFULL,
    0xAAAAAAAAAAAAAAAAULL,
    0x5555555555555555ULL,
    0xAAAAAAAAAAAAAAAAULL,
    0xFFFFFFFFFFFFFFFFULL,
    0xAAAAAAAAAAAAAAAAULL,
    0xFFFFFFFFFFFFFFFFULL,
    0x5555555555555555ULL,
    0xFFFFFFFFFFFFFFFFULL,
    0x5555555555555555ULL,
    0xAAAAAAAAAAAAAAAAULL,
    0x5555555555555555ULL,
    0xFFFFFFFFFFFFFFFFULL,
    0x5555555555555555ULL,
};
 /*
 *  or possibly
 */
static const uint64_t test_pattern_3[] = {
    0xFDFDFDFDFDFDFDFDULL,
    0x8787878787878787ULL,
    0xFEFEFEFEFEFEFEFEULL,
    0xC3C3C3C3C3C3C3C3ULL,
    0x7F7F7F7F7F7F7F7FULL,
    0xE1E1E1E1E1E1E1E1ULL,
    0xBFBFBFBFBFBFBFBFULL,
    0xF0F0F0F0F0F0F0F0ULL,
    0xDFDFDFDFDFDFDFDFULL,
    0x7878787878787878ULL,
    0xEFEFEFEFEFEFEFEFULL,
    0x3C3C3C3C3C3C3C3CULL,
    0xF7F7F7F7F7F7F7F7ULL,
    0x1E1E1E1E1E1E1E1EULL,
    0xFBFBFBFBFBFBFBFBULL,
    0x0F0F0F0F0F0F0F0FULL,
};

static const uint64_t test_pattern_1[] = {
    0xAAAAAAAAAAAAAAAAULL,
    0x5555555555555555ULL,
    0xAAAAAAAAAAAAAAAAULL,
    0x5555555555555555ULL,
    0xAAAAAAAAAAAAAAAAULL,
    0x5555555555555555ULL,
    0xAAAAAAAAAAAAAAAAULL,
    0x5555555555555555ULL,
    0xAAAAAAAAAAAAAAAAULL,
    0x5555555555555555ULL,
    0xAAAAAAAAAAAAAAAAULL,
    0x5555555555555555ULL,
    0xAAAAAAAAAAAAAAAAULL,
    0x5555555555555555ULL,
    0xAAAAAAAAAAAAAAAAULL,
    0x5555555555555555ULL,
#if 0 // only need a cacheline size
    0xAAAAAAAAAAAAAAAAULL,
    0x5555555555555555ULL,
    0xAAAAAAAAAAAAAAAAULL,
    0x5555555555555555ULL,
    0xAAAAAAAAAAAAAAAAULL,
    0x5555555555555555ULL,
    0xAAAAAAAAAAAAAAAAULL,
    0x5555555555555555ULL,
    0xAAAAAAAAAAAAAAAAULL,
    0x5555555555555555ULL,
    0xAAAAAAAAAAAAAAAAULL,
    0x5555555555555555ULL,
    0xAAAAAAAAAAAAAAAAULL,
    0x5555555555555555ULL,
    0xAAAAAAAAAAAAAAAAULL,
    0x5555555555555555ULL,
#endif
};

// setup default for test pattern array
static const uint64_t *dram_tune_test_pattern = test_pattern_1;
#endif

// set this to 1 to shorten the testing to exit when all byte lanes have errors
// having this at 0 forces the testing to take place over the entire range every iteration,
// hopefully ensuring an even load on the memory subsystem 
#define EXIT_WHEN_ALL_LANES_HAVE_ERRORS 0

#define DEFAULT_TEST_BURSTS 5 // FIXME: this is what works so far...// FIXME was 7
int dram_margin_use_bursts = DEFAULT_TEST_BURSTS;

// dram_tune_rank_offset is used to offset the second area used in test_dram_mem_xor.
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
static uint64_t dram_tune_rank_offset = AREA_DUPE_OFFSET; // default

// defaults to 0, but will be set elsewhere to the address offset to next DIMM if multi-slot
static uint64_t dram_tune_dimm_offset = 0; // default

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

static int errs_by_bytelane(uint64_t xor)
{
    int errors = 0;
    int bybit = 1;
    uint64_t bymsk = 0xffULL; // start in byte lane 0

    while (xor != 0) {
	debug_print("ERROR(%03d): [0x%016lX] [0x%016lX]  expected 0x%016lX d1 %016lX d2 %016lX\n",
		    burst, p1, p2, v, d1, d2);
	if (xor & bymsk) { // error(s) in this lane
	    errors |= bybit; // set the byte error bit
	    xor &= ~bymsk; // clear byte lane in error bits
	}
	bymsk <<= 8; // move mask into next byte lane
	bybit <<= 1; // move bit into next byte position
    }
    return errors;
}

static int dram_margin_mem_xor(uint64_t p, uint64_t bitmask)
{
    uint64_t p1, p2, d1, d2;
    uint64_t v, v1;
    uint64_t p2offset = dram_tune_rank_offset; // FIXME?
    uint64_t datamask;
    uint64_t xor1, xor2;
    uint64_t i, j, k;
    uint64_t ii;
    int errors = 0;
    //uint64_t index;
    uint64_t pattern1 = bdk_rng_get_random64();
    uint64_t pattern2 = 0;
    int p1_rank = 0, p2_rank = 0;
    int errs_by_lmc[4] = { 0,0,0,0 }; // actually indexed by rank here...
    int rankx;

    if (dram_tune_rank_ena)
	p2_rank = 1; // multi-rank, p2 is always on it via p2offset
    
    // 2nd DIMM forces ranks up by 2
    if (dram_tune_dimm_offset && (p & dram_tune_dimm_offset)) {
	p1_rank += 2;
	p2_rank += 2;
    }

    // Byte lanes may be clear in the mask to indicate no testing on that lane.
    datamask = bitmask;

    /* Add offset to both test regions to not clobber boot stuff
     * when running from L2 for NAND boot.
     */
    p += AREA_BASE_OFFSET; // make sure base is out of the way of boot

#define II_INC (1ULL << 29)
#define II_MAX (1ULL << 31)
#define K_INC  (1ULL << 14)
#define K_MAX  (1ULL << 20)
#define J_INC  (1ULL <<  9)
#define J_MAX  (1ULL << 12)
#define I_INC  (1ULL <<  3)
#define I_MAX  (1ULL <<  7)

#if 0
    int ix;
    // add this loop to fill memory with the test pattern first
    // loops are ordered so that only entire cachelines are written 
    for (ii = 0; ii < II_MAX; ii += II_INC) { // extend the range of memory tested!!
	for (k = 0; k < K_MAX; k += K_INC) {
	    for (j = 0; j < J_MAX; j += J_INC) {
		p1 = p + ii + k + j;
		p2 = p1 + p2offset;
		for (i = 0, ix = 0; i < I_MAX; i += I_INC, ix++) {

		    v = dram_tune_test_pattern[ix];
		    v1 = v; // write the same thing to both areas

		    __bdk_dram_write64(p1 + i, v);
		    __bdk_dram_write64(p2 + i, v1);

		}
		BDK_CACHE_WBI_L2(p1);
		BDK_CACHE_WBI_L2(p2);
	    }
	}
    } /* for (ii = 0; ii < (1ULL << 31); ii += (1ULL << 29)) */
#endif

    BDK_PREFETCH(p           , BDK_CACHE_LINE_SIZE);
    BDK_PREFETCH(p + p2offset, BDK_CACHE_LINE_SIZE);

    // loops are ordered so that only a single 64-bit slot is written to each cacheline at one time,
    // then the cachelines are forced out; this should maximize read/write traffic
    for (ii = 0; ii < II_MAX; ii += II_INC) { // extend the range of memory tested!!
	for (k = 0; k < K_MAX; k += K_INC) {
	    for (i = 0; i < I_MAX; i += I_INC) {
		for (j = 0; j < J_MAX; j += J_INC) {

		    p1 = p + ii + k + j;
		    p2 = p1 + p2offset;

		    BDK_PREFETCH(p1 + J_INC, BDK_CACHE_LINE_SIZE);
		    BDK_PREFETCH(p2 + J_INC, BDK_CACHE_LINE_SIZE);
	    
		    v = pattern1 * (p1 + i);
		    v1 = v; // write the same thing to both areas

		    __bdk_dram_write64(p1 + i, v);
		    __bdk_dram_write64(p2 + i, v1);

		    BDK_CACHE_WBI_L2(p1);
		    BDK_CACHE_WBI_L2(p2);
		}
	    }
	}
    } /* for (ii = 0; ii < (1ULL << 31); ii += (1ULL << 29)) */

    BDK_DCACHE_INVALIDATE;

    /* Make a series of passes over the memory areas. */

    for (int burst = 0; burst < dram_margin_use_bursts; burst++)
    {
	uint64_t this_pattern = bdk_rng_get_random64();
	pattern2 ^= this_pattern;

        /* XOR the data with a random value, applying the change to both
         * memory areas.
         */
	BDK_PREFETCH(p           , BDK_CACHE_LINE_SIZE);
	BDK_PREFETCH(p + p2offset, BDK_CACHE_LINE_SIZE);

	for (ii = 0; ii < II_MAX; ii += II_INC) { // extend the range of memory tested!!
	    for (k = 0; k < K_MAX; k += K_INC) {
		for (i = 0; i < I_MAX; i += I_INC) { 
		    for (j = 0; j < J_MAX; j += J_INC) {

			p1 = p + ii + k + j;
			p2 = p1 + p2offset;

			BDK_PREFETCH(p1 + J_INC, BDK_CACHE_LINE_SIZE);
			BDK_PREFETCH(p2 + J_INC, BDK_CACHE_LINE_SIZE);
	    
			v  = __bdk_dram_read64(p1 + i) ^ this_pattern;
			v1 = __bdk_dram_read64(p2 + i) ^ this_pattern;

			__bdk_dram_write64(p1 + i, v);
			__bdk_dram_write64(p2 + i, v1);

			BDK_CACHE_WBI_L2(p1);
			BDK_CACHE_WBI_L2(p2);
		    }
		}
	    }
	} /* for (ii = 0; ii < (1ULL << 31); ii += (1ULL << 29)) */

        BDK_DCACHE_INVALIDATE;

	BDK_PREFETCH(p           , BDK_CACHE_LINE_SIZE);
	BDK_PREFETCH(p + p2offset, BDK_CACHE_LINE_SIZE);

        /* Look for differences in the areas. If there is a mismatch, reset
         * both memory locations with the same pattern. Failing to do so
         * means that on all subsequent passes the pair of locations remain
         * out of sync giving spurious errors.
         */
	// NOTE: change the loop order so that an entire cache line is compared at one time
	// NOTE: this is so that a read error that occurs *anywhere* on the cacheline will be caught,
	// NOTE: rather than comparing only 1 cacheline slot at a time, where an error on a different
	// NOTE: slot will be missed that time around
	// NOTE: Does the above make sense?

	for (ii = 0; ii < II_MAX; ii += II_INC) { // extend the range of memory tested!!
	    for (k = 0; k < K_MAX; k += K_INC) {
		for (j = 0; j < J_MAX; j += J_INC) {

		    p1 = p + ii + k + j;
		    p2 = p1 + p2offset;

		    BDK_PREFETCH(p1 + J_INC, BDK_CACHE_LINE_SIZE);
		    BDK_PREFETCH(p2 + J_INC, BDK_CACHE_LINE_SIZE);
	    
		    // process entire cachelines in the innermost loop
		    for (i = 0; i < I_MAX; i += I_INC) {

			v = ((p1 + i) * pattern1) ^ pattern2; // this should predict what we find...???
			d1 = __bdk_dram_read64(p1 + i);
			d2 = __bdk_dram_read64(p2 + i);

			//xor = ((d1 ^ v) | (d2 ^ v)) & datamask; // union of error bits only in active byte lanes
			xor1 = (d1 ^ v) & datamask;
			xor2 = (d2 ^ v) & datamask;

			// keep errors by rank
			if (xor1)
			    errs_by_lmc[p1_rank] |= errs_by_bytelane(xor1);
			if (xor2)
			    errs_by_lmc[p2_rank] |= errs_by_bytelane(xor2);
		    }
		    BDK_CACHE_WBI_L2(p1);
		    BDK_CACHE_WBI_L2(p2);
		}
	    }
	} /* for (ii = 0; ii < (1ULL << 31); ii += (1ULL << 29)) */
    } /* for (int burst = 0; burst < dram_margin_use_bursts; burst++) */

    // update the global LMC error states
    for (rankx = 0; rankx < 4; rankx++) {
	if (!(dram_tune_rank_mask & (1 << rankx)))
	    continue;
	if (errs_by_lmc[rankx]) {
	    errors |= errs_by_lmc[rankx]; // create a total errors mask by bytelane
#if 0
	    bdk_atomic_fetch_and_bset64(&dram_margin_lmc_errs[rankx], errs_by_lmc[rankx]);
#else
            // FIXME: this was done to avoid compilation problems...
	    __atomic_fetch_or(&dram_margin_lmc_errs[rankx], (uint64_t)errs_by_lmc[rankx], __ATOMIC_ACQ_REL);
#endif
	}
    }
    return errors;
}

#undef II_INC
#undef II_MAX



// cores to use
#define DEFAULT_USE_CORES 44   // FIXME: was (1 << CORE_BITS)
static int dram_tune_use_cores = DEFAULT_USE_CORES; // max cores to use, override available
static int dram_tune_max_cores; // max cores available on a node
#define CORE_SHIFT 22          // offset into rank_address passed to testing code

typedef void (*__dram_tuning_thread_t)(int arg, void *arg1);

typedef struct
{
    bdk_node_t node;
    int64_t num_lmcs;
    uint64_t byte_mask;
} test_dram_byte_info_t;

static void dram_margin_thread(int arg, void *arg1)
{
    test_dram_byte_info_t *test_info = arg1;
    int core = arg;
    uint64_t errs;
    bdk_node_t node = test_info->node;
    int lmc;

    lmc = test_info->num_lmcs; // FIXME: hack

    uint64_t base_address = (lmc << 7); // run all cores on the same LMC
    uint64_t bytemask = test_info->byte_mask;

    /* Figure out our work memory range.
     *
     * Note: base_address above just provides the physical offset which determines
     * specific LMC portions of the address space and does not have the node bits set.
     */
    base_address  = bdk_numa_get_address(node, base_address); // map to node
    base_address |= (core << CORE_SHIFT); // also put full core into address
    if (dram_tune_dimm_offset) { // if multi-slot in some way, choose a DIMM for the core
	base_address |= (core & 1) ? dram_tune_dimm_offset : 0;
    }

    debug_print("Node %d, core %d, Testing area 1 at 0x%011lx, area 2 at 0x%011lx\n",
		node, core, base_address + AREA_BASE_OFFSET,
		base_address + AREA_BASE_OFFSET + dram_tune_rank_offset);

    errs = dram_margin_mem_xor(base_address, bytemask);

    /* Report that we're done */
    debug_print("Core %d on LMC %d node %d done with test_dram_byte with 0x%lx errs\n",
	      core, lmc, node, errs);

    if (errs) {
	bdk_atomic_fetch_and_bset64_nosync(&dram_margin_threads_errs, errs);
	// next is done already in the thread
	//bdk_atomic_fetch_and_bset64_nosync(&dram_margin_lmc_errs[rankx], errs);
    }

    bdk_atomic_add64_nosync(&dram_margin_threads_done, 1);

    return;
}

static int dram_margin_use_xor2 = 0; // default to mem_xor code

static int
run_dram_margin_threads(bdk_node_t node, int lmc, uint64_t bytemask)
{
    test_dram_byte_info_t dram_margin_info;
    test_dram_byte_info_t *test_info = &dram_margin_info;
    int total_count = 0;
    __dram_tuning_thread_t thread_p = dram_margin_thread;

    test_info->node = node;
    test_info->num_lmcs = lmc; // FIXME: hack
    test_info->byte_mask = bytemask;

    // init some global data
    bdk_atomic_set64(&dram_margin_threads_done, 0);
    bdk_atomic_set64((int64_t *)&dram_margin_threads_errs, 0);

    // NOTE: really clearing these on a rank basis...
    // the threads will update them as needed
    bdk_atomic_set64((int64_t *)&dram_margin_lmc_errs[0], 0);
    bdk_atomic_set64((int64_t *)&dram_margin_lmc_errs[1], 0);
    bdk_atomic_set64((int64_t *)&dram_margin_lmc_errs[2], 0);
    bdk_atomic_set64((int64_t *)&dram_margin_lmc_errs[3], 0);
    BDK_MB;

    /* Start threads for cores on the node */
    if (bdk_numa_exists(node)) {
	debug_print("Starting %d threads for test_dram_byte\n", dram_tune_use_cores);
	for (int core = 0; core < dram_tune_use_cores; core++) {
	    if (bdk_thread_create(node, 0, thread_p, core, (void *)test_info, 0)) {
		bdk_error("Failed to create thread %d for test_dram_byte\n", core);
	    } else {
		total_count++;
	    }
	}
    }

    /* Wait for threads to finish */
    while (bdk_atomic_get64(&dram_margin_threads_done) < total_count)
	bdk_thread_yield();

    // NOTE: this is the summary of errors across all LMCs
    return (int)bdk_atomic_get64((int64_t *)&dram_margin_threads_errs);
}

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

static lmc_data_t this_lmc;

#define LAST_BYTE 8
#define RANGE1 0
#define RANGE2 1

static int
get_computed_vref(bdk_node_t node, int lmc, int rankx, int maybe)
{
    // must get dimm_count and rank_count from CSR
    BDK_CSR_INIT(lmc_config, node, BDK_LMCX_CONFIG(lmc));
    int dimm_count = (lmc_config.s.init_status & 0x0c) ? 2 : 1;
    int rank_count = (lmc_config.s.rank_ena) ? 2 : 1;
    //int is_stacked_die = 0; // FIXME: HOW do we get this information HERE?

    // call it twice, varying "is_stacked_die", and see what happens
    int not_stacked = compute_vref_value(node, lmc, rankx, dimm_count,
					 rank_count, &ddr4_impedence_values,
					 /* not_stacked */0);
    int stacked = compute_vref_value(node, lmc, rankx, dimm_count,
				     rank_count, &ddr4_impedence_values,
				     /* stacked */1);
    int ret = maybe; // default to what was last written to the LMC VREF

    if (stacked != not_stacked) { // not equal, make sure 1 of the 2 matches "maybe"
	if (stacked == maybe)
	    ret = stacked;
	else if (not_stacked == maybe)
	    ret = not_stacked;
	else { // problem - did not match either???
	    printf("+++ DEBUG: N%d.LMC%d.R%d: compute_vref_values %d and %d did not match %d\n",
		      node, lmc, rankx, stacked, not_stacked, maybe);
	}
    } else { // equal, so either should match "maybe"
	if (not_stacked != maybe) {
	    printf("+++ DEBUG: N%d.LMC%d.R%d: compute_vref_value %d did not match %d\n",
		      node, lmc, rankx, not_stacked, maybe);
	}
    }

    debug_print("+++ DEBUG: N%d.LMC%d.R%d: using %d for exernal VREF\n",
		node, lmc, rankx, ret);

    return ret;
}


// NOTE: this is called once per LMC
static void
margin_vref_ext(bdk_node_t node, int lmc, int ddr_interface_64b)
{
    int index;
    int start_index, end_index, incr_index;
    int rankx, rank_mask = dram_tune_rank_mask;

    int range;
    range_data_t *rdp;

    // NOTE: these need not be dimensioned
    uint64_t ops_sum, dclk_sum;
    uint64_t start_dram_dclk, stop_dram_dclk;
    uint64_t start_dram_ops, stop_dram_ops;
    uint64_t percent_x10;
    int errors;
    //int tot_errors;
    int byte;

#if 1
    // before we sweep through the external VREF values,
    // sample the value that was last written during init,
    // and assume it was done via computation...
    // FIXME: this is a hack because we do not know "is_stacked_die"
    // FIXME: when we try to use compute_vref_value() later...
    int maybe_computed_vref;
    BDK_CSR_INIT(lmc_mr_mpr_ctl, node, BDK_LMCX_MR_MPR_CTL(lmc));
    maybe_computed_vref = lmc_mr_mpr_ctl.s.mr_wr_addr & 0x7f;
    debug_print("+++ DEBUG: N%d.LMC%d: MR_MPR_CTL[mr_wr_addr] returned %d\n",
		node, lmc, maybe_computed_vref);
#endif

    if (dram_margin_ext_gran != DEFAULT_MARGIN_EXT_GRAN) {
	ddr_print("N%d: Write Voltage Margining: changing sample granularity from %d to %d\n",
		  node, DEFAULT_MARGIN_EXT_GRAN, dram_margin_ext_gran);
    }
    // ensure sample is taken at the midway point if possible // FIXME?
    start_index = MIN_INDEX_MARGIN_EXT - (MIN_INDEX_MARGIN_EXT % dram_margin_ext_gran);
    end_index   = MAX_INDEX_MARGIN_EXT - (MAX_INDEX_MARGIN_EXT % dram_margin_ext_gran);
    incr_index  = dram_margin_ext_gran;

    ops_sum = 0;
    dclk_sum = 0;
    memset(&this_lmc, 0, sizeof(this_lmc)); // FIXME? make sure the struct is cleared

    // construct the bytemask
    uint64_t bytemask = (ddr_interface_64b) ? 0xffffffffffffffff : 0x00000000ffffffff;

    debug_print("N%d.LMC%d: Starting Margining tests for Write Voltage\n", node, lmc);

    // loop through the 2 ranges
    for (range = 0; range < 2; range++) {
	debug_print("N%d.LMC%d: Starting Range %d Testing\n", node, lmc, range+1);

	rdp = &this_lmc.ranges[range];

	// now loop through selected legal values for the index...
	for (index = start_index; index <= end_index; index += incr_index) {

	    // do the setup on the active LMC ranks
	    // load the VREF values per rank
	    for (rankx = 0; rankx < 4; rankx++) {
		if (!(rank_mask & (1 << rankx)))
		    continue;
		// set VREF for this LMC and all its ranks
		set_vref(node, lmc, rankx, range, index);
	    }

	    // record start cycle CSRs here for utilization measure
	    start_dram_dclk = BDK_CSR_READ(node, BDK_LMCX_DCLK_CNT(lmc));
	    start_dram_ops  = BDK_CSR_READ(node, BDK_LMCX_OPS_CNT(lmc));

	    bdk_watchdog_poke();

	    // run the test(s)
	    // only 1 call should be enough, let the bursts, etc, control the load...  
	    /*tot_errors =*/ run_dram_margin_threads(node, lmc, bytemask);

	    // record stop cycle CSRs here for utilization measure
	    stop_dram_dclk = BDK_CSR_READ(node, BDK_LMCX_DCLK_CNT(lmc));
	    stop_dram_ops  = BDK_CSR_READ(node, BDK_LMCX_OPS_CNT(lmc));

	    // accumulate...
	    ops_sum  += stop_dram_ops  - start_dram_ops;
	    dclk_sum += stop_dram_dclk - start_dram_dclk;

	    // check errors by rank
	    for (rankx = 0; rankx < 4; rankx++) {
		if (!(rank_mask & (1 << rankx)))
		    continue;

		errors = dram_margin_lmc_errs[rankx];

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
		    debug_print("N%d.LMC%d.R%d: Write Voltage Margining Test %3d: errors 0x%02x\n",
			      node, lmc, rankx, index, errors);
		}
	    } /* for (rankx = 0; rankx < ??; rankx++) */

	} /* for (index = start_index; index <= end_index; index += incr_index) */

    } /* for (range = 0; range < 2; range++) */

    // now, organize the printout by rank, then range
    for (rankx = 0; rankx < 4; rankx++) {

	int combined_start[9];
	int combined_end[9];
	int start, last;

	if (!(rank_mask & (1 << rankx)))
	    continue;

	printf("  \n");
	printf("N%d.LMC%d.R%d: Write Voltage Margining   : ", node, lmc, rankx);
	printf("    ECC/8 ");
	for (byte = 7; byte >= 0; byte--) {
	    printf("   Byte %d ", byte);
	}
	printf("\n");

	memset(combined_start, 0, sizeof(combined_start));
	memset(combined_end  , 0, sizeof(combined_end));

	// found a way to get the computed VREF from init
	int computed_vref_from_init = get_computed_vref(node, lmc, rankx,
							maybe_computed_vref);

	for (range = 0; range < 2; range++) {

	    int ranged_vref_from_init = computed_vref_from_init;
	    if (range == RANGE2)
		ranged_vref_from_init += 23;
		
	    rdp = &this_lmc.ranges[range];
	    
#if 1
	    // FIXME FIXME
	    // FIXME: borrow byte 3 values for ECC...
	    rdp->index_best_start[rankx][8] = rdp->index_best_start[rankx][3];
	    rdp->index_best_count[rankx][8] = rdp->index_best_count[rankx][3];
#endif

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
	    printf("N%d.LMC%d.R%d: Range %d Original DAC%2s    : ",
		   node, lmc, rankx, range+1,
		   (ranged_vref_from_init > 50) ? "**" : "  ");
	    for (byte = LAST_BYTE; byte >= 0; byte--) {
		printf("  %7d ", ranged_vref_from_init);
	    }
	    printf("\n");

	    // print the median values from the measured windows
	    printf("N%d.LMC%d.R%d: Range %d Median DAC        : ",
		   node, lmc, rankx, range+1);
	    for (byte = LAST_BYTE; byte >= 0; byte--) {
		index = rdp->index_best_start[rankx][byte] +
		    ((rdp->index_best_count[rankx][byte] - incr_index) / 2); // adj by incr
		printf("  %7d ", index);
	    }
	    printf("\n");

	    // print the window sizes
	    printf("N%d.LMC%d.R%d: Range %d Window Length     : ",
		   node, lmc, rankx, range+1);
	    for (byte = LAST_BYTE; byte >= 0; byte--) {
		printf("  %7d ", rdp->index_best_count[rankx][byte] - incr_index);
	    }
	    printf("\n");

	    // print the window extents
	    printf("N%d.LMC%d.R%d: Range %d Window Bounds     : ",
		   node, lmc, rankx, range+1);
	    for (byte = LAST_BYTE; byte >= 0; byte--) {
		start = rdp->index_best_start[rankx][byte];
		printf("%3d to %2d ", start,
		       start + rdp->index_best_count[rankx][byte] - incr_index);
	    }
	    printf("\n");
#if 0
	    // print the windows bit arrays
	    printf("N%d.LMC%d.R%d: Range %d Window Bitmap      : ",
		   node, lmc, rankx, range+1);
	    for (byte = LAST_BYTE; byte >= 0; byte--) {
		printf("  %07lx ", rdp->index_windows[rankx][byte]);
	    }
	    printf("\n");
#endif
	    if (ranged_vref_from_init > 50)
		printf("** out of range.\n");

	    printf("  \n"); // blank line after each range

	} /* for (range = 0; range < 2; range++) */

	//////////////// COMBINED printout comes last

	// print the original values (again)
	printf("N%d.LMC%d.R%d: Combined Original DAC     : ", node, lmc, rankx);
	for (byte = LAST_BYTE; byte >= 0; byte--) {
	    printf("  %7d ", computed_vref_from_init);
	}
	printf("\n");

	// print the measured values
	printf("N%d.LMC%d.R%d: Combined Median DAC       : ", node, lmc, rankx);
	for (byte = LAST_BYTE; byte >= 0; byte--) {
	    index = (combined_start[byte] + combined_end[byte]) / 2;
	    printf("  %7d ", index);
	}
	printf("\n");

	// print the combined window sizes
	printf("N%d.LMC%d.R%d: Combined Window Length    : ", node, lmc, rankx);
	for (byte = LAST_BYTE; byte >= 0; byte--) {
	    printf("  %7d ", combined_end[byte] - combined_start[byte] + 1); // FIXME: is 1 correct always?
	}
	printf("\n");

	// print the combined window extents
	printf("N%d.LMC%d.R%d: Combined Window Bounds    : ", node, lmc, rankx);
	for (byte = LAST_BYTE; byte >= 0; byte--) {
#if 0
	    printf("%3d to %2d ", combined_start[byte], combined_end[byte]);
#else
	{
	    int dac_min = combined_start[byte];
	    int dac_max = combined_end[byte];
	    int is_low_risk = is_dac_delta_low_risk(computed_vref_from_init, dac_max, dac_min, 10); // FIXME: 10 should be symbolic!!
	    printf("%3d to %2d%c", combined_start[byte], combined_end[byte], (is_low_risk) ? ' ' : '<');
	    if (is_low_risk)
		low_risk_count++;
	    else
		needs_review_count++;
	}
#endif
	}
	printf("\n");

	printf("  \n"); // blank line after combined

	// last step: use the computed VREF for restoring a working value
	set_vref(node, lmc, rankx, 0, computed_vref_from_init); // range is in computed

    } /* for (rankx = 0; rankx < 4; rankx++) */

    // finally, print the LMC utilization
    percent_x10 = ops_sum * 1000 / dclk_sum;
    ddr_print("\nN%d.LMC%d: ops %lu, cycles %lu, used %lu.%lu%%\n",
	   node, lmc, ops_sum, dclk_sum, percent_x10 / 10, percent_x10 % 10);

}

static void margin_vref_int(bdk_node_t node, int lmc, int ddr_interface_64b);

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
    if (lmcx_config.s.rank_ena) { // replace the default offset when there is more than 1 rank...
	dram_tune_rank_offset =
	    1ull << (28 + lmcx_config.s.pbank_lsb - lmcx_config.s.rank_ena + (num_lmcs/2));
	ddr_print("N%d: %s: changing rank offset to 0x%lx\n",
		  node, __FUNCTION__, dram_tune_rank_offset);
	dram_tune_rank_ena = 1;
    }
    dram_tune_rank_mask = lmcx_config.s.init_status;
    if (dram_tune_rank_mask & 0x0c) { // bit 2 or 3 set indicates 2 DIMMs
	dram_tune_dimm_offset = 1ull << (28 + lmcx_config.s.pbank_lsb + (num_lmcs/2));
	ddr_print("N%d: %s: changing dimm offset to 0x%lx\n",
		  node, __FUNCTION__, dram_tune_dimm_offset);
    }
    ddr_interface_64b = !lmc_config.s.mode32b;

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

    // allow override of the test mem_xor algorithm
    if ((s = getenv("ddr_margin_use_xor2")) != NULL) {
        dram_margin_use_xor2 = !!strtoul(s, NULL, 10);
    }

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

	// do setup for each active LMC
	debug_print("N%d: %s: disable ECC on LMC %d.\n", node, __FUNCTION__, lmc);

	/* Disable ECC for DRAM tests */
	lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(lmc));
	save_ecc_ena[lmc] = lmc_config.s.ecc_ena;
	lmc_config.s.ecc_ena = 0;
	DRAM_CSR_WRITE(node, BDK_LMCX_CONFIG(lmc), lmc_config.u);
	lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(lmc));
    } /* for (lmc = 0; lmc < num_lmcs; lmc++) */

    printf("  \n");
    printf("-------------------------------------\n");
    printf("N%d: Starting %s Voltage Margining.\n", node, mode_str);
    printf("  \n");

    for (lmc = 0; lmc < num_lmcs; lmc++) {
	// testing is done on a per LMC basis
	// FIXME: for now, loop here to show what happens multiple times
	for (loop = 0; loop < loops; loop++) {

	    /* Perform margining write or read voltage */
	    if (do_write)
		margin_vref_ext(node, lmc, ddr_interface_64b); // ext = write
	    else
		margin_vref_int(node, lmc, ddr_interface_64b); // int = read

	} /* for (loop = 0; loop < loops; loop++) */
    } /* for (lmc = 0; lmc < num_lmcs; lmc++) */

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
	debug_print("N%d: %s: re-enabling ECC on LMC %d.\n", node, __FUNCTION__, lmc);

	/* Restore ECC for DRAM tests */
	lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(lmc));
	lmc_config.s.ecc_ena = save_ecc_ena[lmc];
	DRAM_CSR_WRITE(node, BDK_LMCX_CONFIG(lmc), lmc_config.u);
	lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(lmc));

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

// Read Voltage Margining
//
// NOTE: this is called once per LMC
static void
margin_vref_int(bdk_node_t node, int lmc, int ddr_interface_64b)
{
    int index;
    int start_index, end_index, incr_index;
    int rankx, rank_mask = dram_tune_rank_mask;

    // only need byte-lanes for internal VREF, not ranks or ranges
    int index_start[9];
    int index_count[9];
    uint64_t index_windows[9];
    int index_best_start[9];
    int index_best_count[9];

    // NOTE: these need not be dimensioned
    uint64_t ops_sum, dclk_sum;
    uint64_t start_dram_dclk, stop_dram_dclk;
    uint64_t start_dram_ops, stop_dram_ops;
    uint64_t percent_x10;
    int errors;
    //int tot_errors;
    int byte;

    if (dram_margin_int_gran != DEFAULT_MARGIN_INT_GRAN) {
	ddr_print("N%d: Margining: changing sample granularity from %d to %d\n",
		  node, DEFAULT_MARGIN_INT_GRAN, dram_margin_int_gran);
    }
    // ensure sample is taken at the midway point if possible // FIXME?
    incr_index  = dram_margin_int_gran;
    start_index = MIN_INDEX_MARGIN_INT - (MIN_INDEX_MARGIN_INT % dram_margin_int_gran);
    end_index   = MAX_INDEX_MARGIN_INT - (MAX_INDEX_MARGIN_INT % dram_margin_int_gran);

    ops_sum = 0;
    dclk_sum = 0;

    // construct the bytemask
    uint64_t bytemask = (ddr_interface_64b) ? 0xffffffffffffffff : 0x00000000ffffffff;

    ddr_print("N%d.LMC%d: Starting Margining tests for Read Voltage\n", node, lmc);

    int orig_dac_settings[9];
    read_DAC_DBI_settings(node, lmc, /*DAC*/1, orig_dac_settings);

    memset(index_start, 0, sizeof(index_start));
    memset(index_count, 0, sizeof(index_count));
    memset(index_windows,  0, sizeof(index_windows));
    memset(index_best_start, 0, sizeof(index_best_start));
    memset(index_best_count, 0, sizeof(index_best_count));

    // now loop through selected legal values for the index...
    for (index = start_index; index <= end_index; index += incr_index) {

	// do the setup on the active LMC (FIXME: not done by ranks?)
	// load the internal VREF values all at once
	load_dac_override(node, lmc, index, /*ALL*/0x0A);

	// record start cycle CSRs here for utilization measure
	start_dram_dclk = BDK_CSR_READ(node, BDK_LMCX_DCLK_CNT(lmc));
	start_dram_ops  = BDK_CSR_READ(node, BDK_LMCX_OPS_CNT(lmc));

	bdk_watchdog_poke();

	// run the test(s)
	// only 1 call should be enough, let the bursts, etc, control the load...  
	// NOTE: collects errors by rank on the given LMC
	/*tot_errors =*/ run_dram_margin_threads(node, lmc, bytemask);

	// record stop cycle CSRs here for utilization measure
	stop_dram_dclk = BDK_CSR_READ(node, BDK_LMCX_DCLK_CNT(lmc));
	stop_dram_ops  = BDK_CSR_READ(node, BDK_LMCX_OPS_CNT(lmc));

	// accumulate...
	ops_sum  += stop_dram_ops  - start_dram_ops;
	dclk_sum += stop_dram_dclk - start_dram_dclk;

	// sum the errors collected by rank into a single error mask
	// FIXME: can we use the return value from running the threads as the sum?
	errors = 0;
	for (rankx = 0; rankx < 4; rankx++) {
	    if (rank_mask & (1 << rankx))
		errors |= dram_margin_lmc_errs[rankx];
	} /* for (rankx = 0; rankx < 4; rankx++) */


	// now process the summed error mask
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

	// only print when there are errors and verbose...
	if (errors) {
	    debug_print("N%d.LMC%d: Margining test for Read Voltage: value %3d: errors 0x%02x\n",
			node, lmc, index, errors);
	    }

    } /* for (index = start_index; index <= end_index; index += incr_index) */

#if 1
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
#endif

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
    for (byte = 8; byte >= 0; byte--) {
#if 0
	printf("    %7d ", orig_dac_settings[byte]);
#else
	{
	    int dac_min = index_best_start[byte];
	    int dac_max = dac_min + index_best_count[byte] - incr_index;
	    // FIXME: limit of 15 should be symbolic, and maybe dependent on DDR type or DIMM type or??!!
	    int is_low_risk = is_dac_delta_low_risk(orig_dac_settings[byte], dac_max, dac_min, 15);
	    printf("    %7d%c", orig_dac_settings[byte], (is_low_risk) ? ' ' : '<');
	    if (is_low_risk)
		low_risk_count++;
	    else
		needs_review_count++;
	}
#endif
    }
    printf("\n");

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
    percent_x10 = ops_sum * 1000 / dclk_sum;
    ddr_print("\nN%d.LMC%d: ops %lu, cycles %lu, used %lu.%lu%%\n",
	   node, lmc, ops_sum, dclk_sum, percent_x10 / 10, percent_x10 % 10);

    // restore the original settings
    for (byte = 0; byte < 9; byte++)
	load_dac_override(node, lmc, orig_dac_settings[byte], byte);

}

/*
 * Margining tool for Write Voltage (DRAM External VREF)
 */
int perform_margin_write_voltage(bdk_node_t node)
{
    // CHECK: external/write voltage margining only for DDR4
    if (!__bdk_dram_is_ddr4(node, 0)) {
	printf("Write Voltage Margining not available for DDR3.\n");
	return -1;
    }

    return perform_margining_vref_common(node, /* write */1);
}
/*
 * Margining tool for Read Voltage (DRAM Internal VREF)
 */
int perform_margin_read_voltage(bdk_node_t node)
{
    // CHECK: internal/read voltage margining only for T88 pass 2.x
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS1_X)) {
	printf("Read Voltage Margining not available for THUNDER pass 1.x.\n");
	return -1;
    }

    return perform_margining_vref_common(node, /* read */0);
}

