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
#include "libbdk-dram/bdk-ccs-addr-decode.h"

// if enhanced verbosity levels are defined, use them
#if defined(VB_PRT)
#define ddr_print2(format, ...) VB_PRT(VBL_FAE,  format, ##__VA_ARGS__)
#define ddr_print3(format, ...) VB_PRT(VBL_TME,  format, ##__VA_ARGS__)
#define ddr_print4(format, ...) VB_PRT(VBL_DEV2, format, ##__VA_ARGS__)
#define ddr_print5(format, ...) VB_PRT(VBL_DEV3, format, ##__VA_ARGS__)
#else
#define ddr_print2 ddr_print
#define ddr_print3 ddr_print
#define ddr_print4 ddr_print
#define ddr_print5 ddr_print
#endif

static  int64_t test_dram_byte_threads_done;
static uint64_t test_dram_byte_threads_errs;

uint64_t test_dram_byte_lmc_errs[4];
uint64_t test_dram_byte_rank_errs[4][4];

// set this to 1 to shorten the testing to exit when all byte lanes have errors
// having this at 0 forces the testing to take place over the entire range every iteration,
// hopefully ensuring an even load on the memory subsystem
#define EXIT_WHEN_ALL_LANES_HAVE_ERRORS 0

#define DEFAULT_TEST_BURSTS 5 // FIXME: this is what works so far...// FIXME: was 7
int dram_tune_use_bursts = DEFAULT_TEST_BURSTS;

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
uint64_t dram_tune_rank_offset = AREA_DUPE_OFFSET; // default

// defaults to 0, but will be set elsewhere to the address offset to next DIMM if multi-slot
uint64_t dram_tune_dimm_offset = 0; // default

// define the increment used for the loops sweeping the DLL byte offset values
#define BYTE_OFFSET_INCR 3 // FIXME: make this tunable?


static int speed_bin_offset[3] = {25, 20, 15};
static int speed_bin_winlen[3] = {70, 60, 60};

static int
get_speed_bin(bdk_node_t node, int lmc)
{
    uint32_t mts_speed = (libdram_get_freq_from_pll(node, lmc) / 1000000) * 2;
    int ret = 0;

    // FIXME: is this reasonable speed "binning"?
    if (mts_speed >= 1700) {
	if (mts_speed >= 2000)
	    ret = 2;
	else
	    ret = 1;
    }

    ddr_print("N%d.LMC%d: %s: returning bin %d for MTS %d\n",
		node, lmc, __FUNCTION__, ret, mts_speed);

    return ret;
}

static int is_low_risk_offset(int speed_bin, int offset)
{
    return (_abs(offset) <= speed_bin_offset[speed_bin]);
}
static int is_low_risk_winlen(int speed_bin, int winlen)
{
    return (winlen >= speed_bin_winlen[speed_bin]);
}

#define LMCNO(addr, xbits) \
    (bdk_extract(addr, 7, xbits) ^ bdk_extract(addr, 20, xbits) ^ bdk_extract(addr, 12, xbits))

static int Get_LMC_Num_cn9xxx(uint64_t address, int xbits, int *rank)
{
    int node, lmc, dimm, prank;
    uint64_t lmcaddr;

    node = bdk_extract(address, 44, 2);
    lmcaddr = bdk_ccs_convert_pa_to_lmc(node, address);
    if (lmcaddr == (uint64_t)-1) {
        printf("%s: ASC Address Conversion Failed for 0x%012lX\n", __func__, address);
        lmc = 0; // FIXME?
        *rank = 0; // FIXME?
    } else {
        //bdk_dram_address_extract_info(lmcaddr, &node, &lmc, &dimm, &prank, &lrank, &bank, &row, &col);
        // FIXME: extract only the minimum info needed, ie LMC and rank
        lmc = bdk_extract(lmcaddr, 7, 2);
        BDK_CSR_INIT(lmcx_config, node, BDK_LMCX_CONFIG(lmc));
        int dimm_lsb    = 28 + lmcx_config.s.pbank_lsb + xbits;
        int dimm_width  = 40 - dimm_lsb;
        int prank_lsb   = dimm_lsb - lmcx_config.s.rank_ena;
        int prank_width = dimm_lsb - prank_lsb;

        dimm =  bdk_extract(lmcaddr, dimm_lsb, dimm_width);
        prank = bdk_extract(lmcaddr, prank_lsb, prank_width);
  
        *rank = (dimm * 2) + prank;
    }

    return lmc;
}

// define controling cache manipulation
#define ENABLE_FLUSHES     0
#define ENABLE_PREFETCHES  0

static int dram_tuning_mem_xor(bdk_node_t node, uint64_t p, uint64_t bitmask, int xbits)
{
    uint64_t p1, p2, d1, d2;
    uint64_t v, vpred;
    uint64_t p2offset = dram_tune_rank_offset; // FIXME?
    uint64_t datamask;
    uint64_t xor;
    uint64_t ii;
    uint64_t pattern1 = bdk_rng_get_random64();
    uint64_t pattern2 = 0;
    int tot_errors = 0;
    int errors;
    int errs_by_lmc[4] = { 0,0,0,0 };
    int errs_by_rank[4][4] = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}}; // [lmc][rank]
    int errs_by_byte[8] = { 0,0,0,0,0,0,0,0 };
    int lmc_mask = __bdk_dram_get_lmc_mask(node);
    int lmc;
    uint64_t vbase, vincr;
    int is_cn8xxx = bdk_is_model(OCTEONTX_CN8XXX);

    // Byte lanes may be clear in the mask to indicate no testing on that lane.
    datamask  = bitmask;

    /* Add offset to both test regions to not clobber boot stuff
     * when running from L2 for NAND boot.
     */
    p += AREA_BASE_OFFSET; // make sure base is out of the way of boot

    // move the multiplies outside the loop
    vbase = p * pattern1;
    vincr = 8 * pattern1;

#define II_INC (1ULL <<  3)
#define II_MAX (1ULL << 22) // stop where the core ID bits start

    // walk the memory areas by 8-byte words
    v = vbase;
    for (ii = 0; ii < II_MAX; ii += II_INC) {

	p1 = p + ii;
	p2 = p1 + p2offset;

	__bdk_dram_write64(p1, v);
	__bdk_dram_write64(p2, v);

        v += vincr;
    }
#if ENABLE_FLUSHES
    __bdk_dram_flush_to_mem_range(p           , p            + II_MAX);
    __bdk_dram_flush_to_mem_range(p + p2offset, p + p2offset + II_MAX);
    BDK_DCACHE_INVALIDATE;
#endif

    /* Make a series of passes over the memory areas. */

    for (int burst = 0; burst < dram_tune_use_bursts; burst++)
    {
	uint64_t this_pattern = bdk_rng_get_random64();
	pattern2 ^= this_pattern;

        /* XOR the data with a random value, applying the change to both
         * memory areas.
         */
#if ENABLE_PREFETCHES
	BDK_PREFETCH(p           , BDK_CACHE_LINE_SIZE);
	BDK_PREFETCH(p + p2offset, BDK_CACHE_LINE_SIZE);
#endif
	for (ii = 0; ii < II_MAX; ii += II_INC) { // FIXME? extend the range of memory tested!!

	    p1 = p + ii;
	    p2 = p1 + p2offset;

	    d1 = __bdk_dram_read64(p1) ^ this_pattern;
	    d2 = __bdk_dram_read64(p2) ^ this_pattern;

	    __bdk_dram_write64(p1, d1);
	    __bdk_dram_write64(p2, d2);

	}
#if ENABLE_FLUSHES
	__bdk_dram_flush_to_mem_range(p           , p            + II_MAX);
	__bdk_dram_flush_to_mem_range(p + p2offset, p + p2offset + II_MAX);
        BDK_DCACHE_INVALIDATE;
#endif
        /* Look for differences in the areas. If there is a mismatch, reset
         * both memory locations with the same pattern. Failing to do so
         * means that on all subsequent passes the pair of locations remain
         * out of sync giving spurious errors.
         */
#if ENABLE_PREFETCHES
	BDK_PREFETCH(p           , BDK_CACHE_LINE_SIZE);
	BDK_PREFETCH(p + p2offset, BDK_CACHE_LINE_SIZE);
#endif
        vpred = vbase;

	for (ii = 0; ii < II_MAX; ii += II_INC) {

	    p1 = p + ii;
	    p2 = p1 + p2offset;

	    v = vpred ^ pattern2; // this should predict what we find...
	    d1 = __bdk_dram_read64(p1);
	    d2 = __bdk_dram_read64(p2);
            vpred += vincr;

            int byno, rank;
	    uint64_t bymsk;
	    xor = (d1 ^ v) & datamask; // union of error bits only in active byte lanes
	    if (xor) { // errors
                if (is_cn8xxx)
                    lmc = bdk_dram_address_extract_lmc_rank_cn8xxx(p1, xbits, &rank);
                else
                    lmc = Get_LMC_Num_cn9xxx(p1, xbits, &rank);
                byno = 0; // start in bit 0
                bymsk = 0xffULL; // start in byte lane 0
                errors = 0;
                debug_print("ERROR(%03d): [0x%016lX] expected 0x%016lX d1 %016lX\n",
                            burst, p1, v, d1);
                while (xor != 0) {
                    if (xor & bymsk) { // error(s) in this lane
                        errors |= (1 << byno); // set the byte error bit
                        xor &= ~bymsk; // clear byte lane in error bits
                        errs_by_byte[byno] |= (1 << lmc);
                    }
                    bymsk <<= 8; // move mask into next byte lane
                    byno += 1; // move bit into next byte position
                } /* while (xor != 0) */
                errs_by_lmc[lmc] |= errors; // set the byte error bits in the LMCs errors
                errs_by_rank[lmc][rank] |= errors; // set the byte error bits in the LMCs ranks errors
                tot_errors |= errors;
	    } /* if (xor) */
	    xor = (d2 ^ v) & datamask; // union of error bits only in active byte lanes
	    if (xor) { // errors
                if (is_cn8xxx)
                    lmc = bdk_dram_address_extract_lmc_rank_cn8xxx(p2, xbits, &rank);
                else
                    lmc = Get_LMC_Num_cn9xxx(p2, xbits, &rank);
                byno = 0; // start in bit 0
                bymsk = 0xffULL; // start in byte lane 0
                errors = 0;
                debug_print("ERROR(%03d): [0x%016lX] expected 0x%016lX d2 %016lX\n",
                            burst, p2, v, d2);
                while (xor != 0) {
                    if (xor & bymsk) { // error(s) in this lane
                        errors |= (1 << byno); // set the byte error bit
                        xor &= ~bymsk; // clear byte lane in error bits
                        errs_by_byte[byno] |= (1 << lmc);
                    }
                    bymsk <<= 8; // move mask into next byte lane
                    byno += 1; // move bit into next byte position
                } /* while (xor != 0) */
                errs_by_lmc[lmc] |= errors; // set the byte error bits in the LMCs errors
                errs_by_rank[lmc][rank] |= errors; // set the byte error bits in the LMCs ranks errors
                tot_errors |= errors;
	    } /* if (xor) */
            // process the errors by byte number - if found on all LMCs, remove from the test mask
            for (byno = 0; byno < 8; byno++) {
                if (errs_by_byte[byno] == lmc_mask) {
                    datamask &= ~(0xffULL << (byno * 8));
                    if (!datamask)
                        goto finish_up;
                }
            }
	} /* for (ii = 0; ii < II_MAX; ii += II_INC) */
    } /* for (int burst = 0; burst < dram_tune_use_bursts; burst++) */

 finish_up:
    // update the global LMC error states
    for (lmc = 0; lmc < 4; lmc++) {
	if (errs_by_lmc[lmc]) {
	    bdk_atomic_fetch_and_bset64_nosync(&test_dram_byte_lmc_errs[lmc], errs_by_lmc[lmc]);

            for (int rankx = 0; rankx < 4; rankx++) { // FIXME? worry about rank_mask?
                if (errs_by_rank[lmc][rankx]) {
                    bdk_atomic_fetch_and_bset64_nosync(&test_dram_byte_rank_errs[lmc][rankx], errs_by_rank[lmc][rankx]);
                }
            }
	}
    }

    return tot_errors;
}

// cores to use
#define DEFAULT_USE_CORES 44   // FIXME: was (1 << CORE_BITS)
int dram_tune_use_cores = DEFAULT_USE_CORES; // max cores to use, override available
int dram_tune_max_cores; // max cores available on a node
#define CORE_SHIFT 22          // FIXME: offset into rank_address passed to test_dram_byte

typedef void (*__dram_tuning_thread_t)(int arg, void *arg1);

typedef struct
{
    bdk_node_t node;
    int64_t num_lmcs;
    uint64_t byte_mask;
} test_dram_byte_info_t;

static void dram_tuning_thread(int arg, void *arg1)
{
    test_dram_byte_info_t *test_info = arg1;
    int core = arg;
    uint64_t errs;
    bdk_node_t node = test_info->node;
    int num_lmcs = test_info->num_lmcs;
    //int lmc = core % num_lmcs;

    uint64_t base_address = 0; //
    uint64_t bytemask = test_info->byte_mask;

    /* Figure out our work memory range.
     *
     * Note: base_address above just provides the physical offset which determines
     * specific portions of the address space and does not have the node bits set.
     */
    base_address  = bdk_numa_get_address(node, base_address); // map to node
    base_address |= (core << CORE_SHIFT); // FIXME: also put full core into address
    if (dram_tune_dimm_offset) { // if multi-slot in some way, choose a DIMM for the core
	base_address |= (core & 1) ? dram_tune_dimm_offset : 0;
    }

    debug_print("Node %d, core %d, Testing area 1 at 0x%011llx, area 2 at 0x%011llx\n",
                node, core, base_address + AREA_BASE_OFFSET,
                base_address + AREA_BASE_OFFSET + dram_tune_rank_offset);

    errs = dram_tuning_mem_xor(node, base_address, bytemask, (num_lmcs >> 1)); // 4->2, 2->1, 1->0

    /* Report that we're done */
    debug_print("Core %d on node %d done with test_dram_byte with 0x%lx errs\n",
	      core, node, errs);

    if (errs) {
	bdk_atomic_fetch_and_bset64_nosync(&test_dram_byte_threads_errs, errs);
	// FIXME: this will have been done already in the called test routine
	//bdk_atomic_fetch_and_bset64_nosync(&test_dram_byte_lmc_errs[lmc], errs);
    }

    bdk_atomic_add64_nosync(&test_dram_byte_threads_done, 1);

    return;
}

int
run_dram_tuning_threads(bdk_node_t node, int num_lmcs, uint64_t bytemask)
{
    test_dram_byte_info_t test_dram_byte_info;
    test_dram_byte_info_t *test_info = &test_dram_byte_info;
    int total_count = 0;
    __dram_tuning_thread_t thread_p = dram_tuning_thread;

    test_info->node = node;
    test_info->num_lmcs = num_lmcs;
    test_info->byte_mask = bytemask;

    // init some global data
    bdk_atomic_set64(&test_dram_byte_threads_done, 0);
    bdk_atomic_set64((int64_t *)&test_dram_byte_threads_errs, 0);

    // clear the global LMC error states
    for (int lmc = 0; lmc < 4; lmc++) {
        bdk_atomic_set64((int64_t *)&test_dram_byte_lmc_errs[lmc], 0);

        for (int rankx = 0; rankx < 4; rankx++) { // FIXME? worry about rank_mask?
            bdk_atomic_set64((int64_t *)&test_dram_byte_rank_errs[lmc][rankx], 0);
        }
    }

    /* Start threads for cores on the node */
    if (bdk_numa_exists(node)) {
	//ddr_print("Starting %d threads for test_dram_byte\n", dram_tune_use_cores);
	for (int core = 0; core < dram_tune_use_cores; core++) {
	    if (bdk_thread_create(node, 0, thread_p, core, (void *)test_info, 0)) {
		bdk_error("Failed to create thread %d for test_dram_byte\n", core);
	    } else {
                //bdk_wait_usec(1000000); // FIXME: debug only
		total_count++;
	    }
	}
    }

#if 0
    /* Wait for threads to finish */
    while (bdk_atomic_get64(&test_dram_byte_threads_done) < total_count)
	bdk_thread_yield();
#else
#define TIMEOUT_SECS 5  // FIXME: long enough so a pass for a given setting will not print
        /* Wait for threads to finish, with progress */
        int cur_count;
        uint64_t cur_time;
        uint64_t period = bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME) * TIMEOUT_SECS; // FIXME?
        uint64_t timeout = bdk_clock_get_count(BDK_CLOCK_TIME) + period;
        do {
            bdk_thread_yield();
            cur_count = bdk_atomic_get64(&test_dram_byte_threads_done);
            cur_time = bdk_clock_get_count(BDK_CLOCK_TIME);
            if (cur_time >= timeout) {
                printf("Waiting for %d cores\n", total_count - cur_count);
                timeout = cur_time + period;
            }
        } while (cur_count < total_count);
#endif

    // NOTE: this is the summary of errors across all LMCs
    return (int)bdk_atomic_get64((int64_t *)&test_dram_byte_threads_errs);
}

/* These variables count the number of ECC errors. They should only be accessed atomically */
extern int64_t __bdk_dram_ecc_single_bit_errors[];
extern int64_t __bdk_dram_ecc_double_bit_errors[];


#define DEFAULT_SAMPLE_GRAN 3 // sample for errors every N offset values
int dram_tune_use_gran = DEFAULT_SAMPLE_GRAN;

static int
auto_set_dll_offset(bdk_node_t node, int dll_offset_mode,
		    int num_lmcs, int ddr_interface_64b,
		    int do_tune)
{
    int byte_offset;
    //unsigned short result[9];
    int byte;
    int16_t byte_delay_start[4][9];
    int16_t byte_delay_count[4][9];
    uint64_t byte_delay_windows [4][9];
    int16_t byte_delay_best_start[4][9];
    int16_t byte_delay_best_count[4][9];
    //int this_rodt;
    uint64_t ops_sum[4], dclk_sum[4];
    uint64_t start_dram_dclk[4], stop_dram_dclk[4];
    uint64_t start_dram_ops[4], stop_dram_ops[4];
    int errors, tot_errors;
    int lmc;
    char *mode_str = (dll_offset_mode == 2) ? "Read" : "Write";
    int mode_is_read = (dll_offset_mode == 2);
    char *mode_blk = (dll_offset_mode == 2) ? " " : "";
    int start_offset, end_offset, incr_offset;

    int speed_bin = get_speed_bin(node, 0); // FIXME: just get from LMC0?
    int low_risk_count = 0, needs_review_count = 0, local_needs;
    int tune_dll_bias = 0;
    int lmc_mask = __bdk_dram_get_lmc_mask(node);
    const char *s;
    // DLL offsets are 6-bits + sign on CN8, 8-bits + sign on CN9
    int max_byte_offset = CN8_OR_CN9(63, ((dll_offset_mode == 2) ? 255 : 63)); // FIXME?
    int min_byte_offset = -max_byte_offset;

    ddr_print("N%d: auto_set_dll_offset: speed bin %d\n", node, speed_bin);

    if (dram_tune_use_gran != DEFAULT_SAMPLE_GRAN) {
	ddr_print2("N%d: Changing sample granularity from %d to %d\n",
		  node, DEFAULT_SAMPLE_GRAN, dram_tune_use_gran);
    }
    // ensure sample is taken at 0
    start_offset = min_byte_offset - (min_byte_offset % dram_tune_use_gran);
    end_offset   = max_byte_offset - (max_byte_offset % dram_tune_use_gran);
    incr_offset  = dram_tune_use_gran;

    memset(ops_sum, 0, sizeof(ops_sum));
    memset(dclk_sum, 0, sizeof(dclk_sum));
    memset(byte_delay_start, 0, sizeof(byte_delay_start));
    memset(byte_delay_count, 0, sizeof(byte_delay_count));
    memset(byte_delay_windows,  0, sizeof(byte_delay_windows));
    memset(byte_delay_best_start, 0, sizeof(byte_delay_best_start));
    memset(byte_delay_best_count, 0, sizeof(byte_delay_best_count));

    // FIXME? consult LMC0 only
    BDK_CSR_INIT(lmcx_config, node, BDK_LMCX_CONFIG(0));
    if (lmcx_config.s.rank_ena) { // replace the default offset when there is more than 1 rank...
	dram_tune_rank_offset = 1ull << (28 + lmcx_config.s.pbank_lsb - lmcx_config.s.rank_ena + (num_lmcs/2));
	ddr_print2("N%d: Tuning multiple ranks per DIMM (rank offset 0x%lx).\n", node, dram_tune_rank_offset);
    }
    if (lmcx_config.s.init_status & 0x0c) { // bit 2 or 3 set indicates 2 DIMMs
	dram_tune_dimm_offset = 1ull << (28 + lmcx_config.s.pbank_lsb + (num_lmcs/2));
	ddr_print2("N%d: Tuning multiple DIMMs per channel (DIMM offset 0x%lx)\n", node, dram_tune_dimm_offset);
    }

    // allow override of the test repeats (bursts) per thread create
    if ((s = getenv("ddr_tune_dll_bias")) != NULL) {
        tune_dll_bias = strtoul(s, NULL, 10);
    }

    // FIXME? do this for LMC0 only
    //BDK_CSR_INIT(comp_ctl2, node, BDK_LMCX_COMP_CTL2(0));
    //this_rodt = comp_ctl2.s.rodt_ctl;

    // construct the bytemask
    int bytes_todo = (ddr_interface_64b) ? 0xff : 0x0f;
    uint64_t bytemask = 0;
    for (byte = 0; byte < 8; ++byte) {
	if (bytes_todo & (1 << byte)) {
	    bytemask |= 0xfful << (8*byte); // set the bytes bits in the bytemask
	}
    } /* for (byte = 0; byte < 8; ++byte) */

    // now loop through selected legal values for the DLL byte offset...

    for (byte_offset = start_offset; byte_offset <= end_offset; byte_offset += incr_offset) {

	// do the setup on active LMCs
	for (lmc = 0; lmc < num_lmcs; lmc++) {
            if (!(lmc_mask & (1 << lmc)))
                continue;
	    change_dll_offset_enable(node, lmc, 0);

	    // set all byte lanes at once
	    load_dll_offset(node, lmc, dll_offset_mode, byte_offset, 0x0A /*ALL*/);
	    // but then clear the ECC byte lane so it should be neutral for the test...
	    load_dll_offset(node, lmc, dll_offset_mode, 0, 8);

	    change_dll_offset_enable(node, lmc, 1);

	    // record start cycle CSRs here for utilization measure
	    start_dram_dclk[lmc] = BDK_CSR_READ(node, BDK_LMCX_DCLK_CNT(lmc));
	    start_dram_ops[lmc]  = BDK_CSR_READ(node, BDK_LMCX_OPS_CNT(lmc));
	} /* for (lmc = 0; lmc < num_lmcs; lmc++) */

	bdk_watchdog_poke();

	// run the test(s)
	// only 1 call should be enough, let the bursts, etc, control the load...
        ddr_print5("N%d: Running threads for byte_offset %d\n", node, byte_offset);
	tot_errors = run_dram_tuning_threads(node, num_lmcs, bytemask);
	if (tot_errors != 0)
            ddr_print4("N%d: Threads for byte_offset %d returned 0x%02x errors\n",
                       node, byte_offset, tot_errors);

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

	    // check errors by byte, but not ECC
	    for (byte = 0; byte < 8; ++byte) {
		if (!(bytes_todo & (1 << byte))) // is this byte lane to be done
		    continue; // no

		byte_delay_windows[lmc][byte] <<= 1; // always put in a zero
		if (errors & (1 << byte)) { // yes, an error in this byte lane
		    byte_delay_count[lmc][byte] = 0; // stop now always
		} else { // no error in this byte lane
		    if (byte_delay_count[lmc][byte] == 0) { // first success, set run start
			byte_delay_start[lmc][byte] = byte_offset;
		    }
		    byte_delay_count[lmc][byte] += incr_offset; // bump run length

		    if (byte_delay_count[lmc][byte] > byte_delay_best_count[lmc][byte]) {
			byte_delay_best_count[lmc][byte] = byte_delay_count[lmc][byte];
			byte_delay_best_start[lmc][byte] = byte_delay_start[lmc][byte];
		    }
		    byte_delay_windows[lmc][byte] |= 1ULL; // for pass, put in a 1
		}
	    } /* for (byte = 0; byte < 8; ++byte) */

	    // only print when there are errors and verbose...
	    if (errors) {
		debug_print("DLL %s Offset Test %3d: errors 0x%x\n",
			    mode_str, byte_offset, errors);
	    }
	} /* for (lmc = 0; lmc < num_lmcs; lmc++) */

    } /* for (byte_offset = start_offset; byte_offset < end_offset; byte_offset += incr_offset) */

    // done with testing, load up and/or print out the offsets we found...

    // only when margining...
    if (!do_tune) {
	printf("  \n");
	printf("-------------------------------------\n");
	printf("N%d: Starting %s Timing Margining.\n", node, mode_str);
	printf("  \n");
    } /* if (!do_tune) */

    if (do_tune && tune_dll_bias) {
        ddr_print("N%d: LMC %s DLL Offsets BIASED by %d\n",
                  node, mode_str, tune_dll_bias);
    }

    for (lmc = 0; lmc < num_lmcs; lmc++) {
        if (!(lmc_mask & (1 << lmc)))
            continue;

	// FIXME FIXME
	// FIXME: this just makes ECC always show 0
	byte_delay_best_start[lmc][8] = start_offset;
	byte_delay_best_count[lmc][8] = end_offset - start_offset + incr_offset;

	// disable offsets while we load...
	change_dll_offset_enable(node, lmc, 0);

	// only when margining...
	if (!do_tune) {
	    // print the heading
	    printf("  \n");
	    printf("N%d.LMC%d: %s Timing Margin     %s : ",
                   node, lmc, mode_str, mode_blk);
	    printf("     ECC/8 ");
	    for (byte = 7; byte >= 0; byte--) {
		printf("    Byte %d ", byte);
	    }
	    printf("\n");
	} /* if (!do_tune) */

	// print and load the offset values
	// print the windows bit arrays
	// only when margining...
	if (!do_tune) {
            printf("N%d.LMC%d: DLL %s Offset Amount %s : ",
                   node, lmc, mode_str, mode_blk);
        } else {
            ddr_print("N%d.LMC%d: SW DLL %s Offset Amount %s : ",
                      node, lmc, mode_str, mode_blk);
        }
        local_needs = 0;
	for (byte = 8; byte >= 0; --byte) { // print in "normal" reverse index order

	    int count = byte_delay_best_count[lmc][byte];
	    if (count == 0)
		count = incr_offset; // should make non-tested ECC byte come out 0

	    byte_offset =  byte_delay_best_start[lmc][byte] +
		((count - incr_offset) / 2); // adj by incr

            byte_offset += tune_dll_bias; // only non-zero when DLL biasing
            if (byte_offset > end_offset)
                byte_offset = end_offset;
            else if (byte_offset < start_offset)
                byte_offset = start_offset;

	    if (!do_tune) { // do counting and special flag if margining
                int will_need_review = !is_low_risk_winlen(speed_bin, (count - incr_offset)) &&
		                       !is_low_risk_offset(speed_bin, byte_offset);

                printf("%10d%c", byte_offset, (will_need_review) ? '<' :' ');

		if (will_need_review) {
		    needs_review_count++;
                    local_needs++;
                } else
		    low_risk_count++;
	    } else { // if just tuning, make the printout less lengthy
                ddr_print("%5d ", byte_offset);
            }

            // for any READ, or WRITE with override, use the new ones
	    if (mode_is_read || use_margin_settings)
		load_dll_offset(node, lmc, dll_offset_mode, byte_offset, byte);
	    else // for WRITE with no override, always store 0 as default
                load_dll_offset(node, lmc, dll_offset_mode, 0, byte);

	}
	if (!do_tune) {
            printf(" %c\n", (local_needs) ? '?' : ' ');
        } else {
            ddr_print("\n");
        }

	// re-enable the offsets now that we are done loading
	change_dll_offset_enable(node, lmc, 1);

	// only when margining...
	if (!do_tune) {
	    // print the window sizes
            local_needs = 0;
	    printf("N%d.LMC%d: DLL %s Window Length %s : ", node, lmc, mode_str, mode_blk);
	    for (byte = 8; byte >= 0; --byte) { // print in "normal" reverse index order
		int count = byte_delay_best_count[lmc][byte];
		if (count == 0)
		    count = incr_offset; // should make non-tested ECC byte come out 0

		// do this again since the "needs review" test is an AND...
		byte_offset =  byte_delay_best_start[lmc][byte] +
		    ((count - incr_offset) / 2); // adj by incr

		int will_need_review = !is_low_risk_winlen(speed_bin, (count - incr_offset)) &&
		    !is_low_risk_offset(speed_bin, byte_offset);
                local_needs += will_need_review;

		printf("%10d%c", count - incr_offset, (will_need_review) ? '<' :' ');
	    }
	    printf(" %c\n", (local_needs) ? '?' : ' ');

	    // print the window extents
	    printf("N%d.LMC%d: DLL %s Window Bounds %s : ", node, lmc, mode_str, mode_blk);
	    for (byte = 8; byte >= 0; --byte) { // print in "normal" reverse index order
		int start = byte_delay_best_start[lmc][byte];
		int count = byte_delay_best_count[lmc][byte];
		if (count == 0)
		    count = incr_offset; // should make non-tested ECC byte come out 0
		printf(" [%4d:%3d]", start, start + count - incr_offset);
	    }
	    printf("\n");
#if 0
	    // FIXME: should have a way to force these out...
	    // print the windows bit arrays
	    printf("N%d.LMC%d: DLL %s Window Bitmap%s : ", node, lmc, mode_str, mode_blk);
	    for (byte = 8; byte >= 0; --byte) { // print in "normal" reverse index order
		printf("%010lx ", byte_delay_windows[lmc][byte]);
	    }
	    printf("\n");
#endif
	} /* if (!do_tune) */
    } /* for (lmc = 0; lmc < num_lmcs; lmc++) */

    // only when margining...
    if (!do_tune) {
	// print the Summary line(s) here
	printf("  \n");
	printf("N%d: %s Timing Margining Summary : %s ", node, mode_str,
	       (needs_review_count > 0) ? "Needs Review" : "Low Risk");
	if (needs_review_count > 0)
	    printf("(%d)", needs_review_count);
	printf("\n");

	// FIXME??? want to print here: "N0: %s Offsets have been applied already"

	printf("-------------------------------------\n");
	printf("  \n");
    } /* if (!do_tune) */

    // FIXME: we probably want this only when doing verbose...
    // finally, print the utilizations all together
    for (lmc = 0; lmc < num_lmcs; lmc++) {
        if (!(lmc_mask & (1 << lmc)))
            continue;
	uint64_t percent_x10 = ops_sum[lmc] * 1000 / dclk_sum[lmc];
	ddr_print2("N%d.LMC%d: ops %lu, cycles %lu, used %lu.%lu%%\n",
		  node, lmc, ops_sum[lmc], dclk_sum[lmc], percent_x10 / 10, percent_x10 % 10);
    } /* for (lmc = 0; lmc < num_lmcs; lmc++) */

    // FIXME: only when verbose, or only when there are errors?
    // run the test one last time
    // print whether there are errors or not, but only when verbose...
    bdk_watchdog_poke();
    debug_print("N%d: %s: Start running test one last time\n", node, __FUNCTION__);
    tot_errors = run_dram_tuning_threads(node, num_lmcs, bytemask);
    debug_print("N%d: %s: Finished running test one last time\n", node, __FUNCTION__);
    if (tot_errors)
	ddr_print2("%s Timing Final Test: errors 0x%x\n", mode_str, tot_errors);

    return (do_tune) ? tot_errors : !!(needs_review_count > 0);
}

#define USE_L2_WAYS_LIMIT 0 // non-zero to enable L2 ways limiting

/*
 * Automatically adjust the DLL offset for the data bytes
 */
int perform_dll_offset_tuning(bdk_node_t node, int dll_offset_mode, int do_tune)
{
    int ddr_interface_64b;
    int save_ecc_ena[4];
    bdk_lmcx_config_t lmc_config;
    int lmc, num_lmcs = __bdk_dram_get_num_lmc(node);
    int lmc_mask = __bdk_dram_get_lmc_mask(node);
    const char *s;
#if USE_L2_WAYS_LIMIT
    int ways, ways_print = 0;
#endif
    int loops = 1, loop;
    uint64_t orig_coremask;
    int errs = 0;
    int is_cn9xxx = bdk_is_model(OCTEONTX_CN9XXX);

    // enable any non-running cores on this node
    orig_coremask = bdk_get_running_coremask(node);
    ddr_print4("N%d: %s: Starting cores (mask was 0x%lx)\n",
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
    if ((s = getenv("ddr_tune_use_loops"))) {
	loops = strtoul(s, NULL, 0);
    }

    // see if we want to change the granularity of the byte_offset sampling
    if ((s = getenv("ddr_tune_use_gran"))) {
	dram_tune_use_gran = strtoul(s, NULL, 0);
    }

    // allow override of the test repeats (bursts) per thread create
    if ((s = getenv("ddr_tune_use_bursts")) != NULL) {
        dram_tune_use_bursts = strtoul(s, NULL, 10);
    }

    // print current working values
    ddr_print2("N%d: Tuning will use %d cores of max %d cores, and use %d repeats.\n",
		node, dram_tune_use_cores, dram_tune_max_cores,
		dram_tune_use_bursts);

#if USE_L2_WAYS_LIMIT
    // see if L2 ways are limited
    if ((s = lookup_env_parameter("limit_l2_ways")) != NULL) {
	ways = strtoul(s, NULL, 10);
	ways_print = 1;
    } else {
	ways = bdk_l2c_get_num_assoc(node);
    }
#endif

    // FIXME? get flag from LMC0 only
    lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(0));
    ddr_interface_64b = !lmc_config.s.mode32b;

    // do setup for each active LMC
    ddr_print2("N%d: %s: starting LMCs setup.\n", node, __FUNCTION__);
    for (lmc = 0; lmc < num_lmcs; lmc++) {
        if (!(lmc_mask & (1 << lmc)))
            continue;

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

#if USE_L2_WAYS_LIMIT
    /* Disable l2 sets for DRAM testing */
    limit_l2_ways(node, 0, ways_print);
#endif

    // testing is done on all LMCs simultaneously
    // FIXME: for now, loop here to show what happens multiple times
    for (loop = 0; loop < loops; loop++) {
        ddr_print2("N%d: Calling auto_set_dll_offset\n", node);
	/* Perform DLL offset tuning */
	errs = auto_set_dll_offset(node, dll_offset_mode, num_lmcs, ddr_interface_64b, do_tune);
    }

#if USE_L2_WAYS_LIMIT
    /* Restore the l2 set configuration */
    limit_l2_ways(node, ways, ways_print);
#endif

    // perform cleanup on all active LMCs
    ddr_print2("N%d: %s: starting LMCs cleanup.\n", node, __FUNCTION__);
    for (lmc = 0; lmc < num_lmcs; lmc++) {
        if (!(lmc_mask & (1 << lmc)))
            continue;

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

	// finally, see if there are any read offset overrides after tuning
        // FIXME: provide a way to do write offsets also??
        if (dll_offset_mode == 2) {
            for (int by = 0; by < 9; by++) {
                if ((s = lookup_env_parameter("ddr%d_tune_byte%d", lmc, by)) != NULL) {
                    int dllro = strtoul(s, NULL, 10);
                    change_dll_offset_enable(node, lmc, 0);
                    load_dll_offset(node, lmc, /* read */2, dllro, by);
                    change_dll_offset_enable(node, lmc, 1);
                }
            }
        }
    } /* for (lmc = 0; lmc < num_lmcs; lmc++) */

    // finish up...
    // put any cores on this node, that were not running at the start, back into reset

    // FIXME FIXME FIXME: get reset_cores to work!!!
#if 0
    uint64_t reset_coremask = bdk_get_running_coremask(node) & ~orig_coremask;
    if (reset_coremask) {
	ddr_print4("N%d: %s: Stopping cores 0x%lx\n", node, __FUNCTION__,
		  reset_coremask);
        extern uint64_t bdk_trace_enables;
        bdk_trace_enables |= 8;
	bdk_reset_cores(node, reset_coremask);
        bdk_trace_enables &= ~8;
    }
    else
#endif
    {
	ddr_print4("N%d: %s: leaving cores set to 0x%lx\n", node, __FUNCTION__,
		  orig_coremask);
    }

    return errs;

} /* perform_dll_offset_tuning */

/////////////////////////////////////////////////////////////////////////////////////////////

/////    HW-assist byte DLL offset tuning   //////

// setup defaults for byte test pattern array
// take these first two from the HRM section 6.9.13
static const uint64_t byte_pattern_0[] = {
    0xFFAAFFFFFF55FFFFULL, // GP0
    0x55555555AAAAAAAAULL, // GP1
    0xAA55AAAAULL,         // GP2
};
static const uint64_t byte_pattern_1[] = {
    0xFBF7EFDFBF7FFEFDULL, // GP0
    0x0F1E3C78F0E1C387ULL, // GP1
    0xF0E1BF7FULL,         // GP2
};
// this is from Andrew via LFSR with PRBS=0xFFFFAAAA
static const uint64_t byte_pattern_2[] = {
    0xEE55AADDEE55AADDULL, // GP0
    0x55AADDEE55AADDEEULL, // GP1
    0x55EEULL,             // GP2
};
// this is from Mike via LFSR with PRBS=0x4A519909
static const uint64_t byte_pattern_3[] = {
    0x0088CCEE0088CCEEULL, // GP0
    0xBB552211BB552211ULL, // GP1
    0xBB00ULL,             // GP2
};

static const uint64_t *byte_patterns[4] = {
    byte_pattern_0, byte_pattern_1, byte_pattern_2, byte_pattern_3
};
static uint32_t lfsr_patterns[4] = {
    0xFFFFAAAAUL, 0x06000000UL, 0xAAAAFFFFUL, 0x4A519909UL
};
#define NUM_PATTERNS 4

#define DEFAULT_BYTE_BURSTS 32 // FIXME: this is what what the longest test usually has
int dram_tune_byte_bursts = DEFAULT_BYTE_BURSTS;

static void
setup_hw_pattern(bdk_node_t node, int lmc, int pattern)
{
    const uint64_t *pattern_p = byte_patterns[pattern];
    /*
      3) Setup GENERAL_PURPOSE[0-2] registers with the data pattern of choice.
      a. GENERAL_PURPOSE0[DATA<63:0>] – sets the initial lower (rising edge) 64 bits of data.
      b. GENERAL_PURPOSE1[DATA<63:0>] – sets the initial upper (falling edge) 64 bits of data.
      c. GENERAL_PURPOSE2[DATA<15:0>] – sets the initial lower (rising edge <7:0>) and upper
      (falling edge <15:8>) ECC data.
    */
    DRAM_CSR_WRITE(node, BDK_LMCX_GENERAL_PURPOSE0(lmc), pattern_p[0]);
    DRAM_CSR_WRITE(node, BDK_LMCX_GENERAL_PURPOSE1(lmc), pattern_p[1]);
    DRAM_CSR_WRITE(node, BDK_LMCX_GENERAL_PURPOSE2(lmc), pattern_p[2]);
}

static void
setup_lfsr_pattern(bdk_node_t node, int lmc, int32_t pattern)
{
    uint32_t prbs;
    const char *s;

    if ((s = getenv("ddr_lfsr_prbs")) != NULL) {
        prbs = strtoul(s, NULL, 0);
    } else {
        if ((pattern >= 0) && (pattern < NUM_PATTERNS))
            prbs = lfsr_patterns[pattern];
        else
            prbs = pattern;
    }

    /*
      2) DBTRAIN_CTL[LFSR_PATTERN_SEL] = 1
         here data comes from the LFSR generating a PRBS pattern
         CHAR_CTL.EN = 0
         CHAR_CTL.SEL = 0; // for PRBS
         CHAR_CTL.DR = 1;
         CHAR_CTL.PRBS = setup for whatever type of PRBS to send
         CHAR_CTL.SKEW_ON = 1;
    */
    BDK_CSR_INIT(char_ctl, node, BDK_LMCX_CHAR_CTL(lmc));
    char_ctl.s.en      = 0;
    char_ctl.s.sel     = 0;
    char_ctl.s.dr      = 1;
    char_ctl.s.prbs    = prbs;
    char_ctl.s.skew_on = 1;
    DRAM_CSR_WRITE(node, BDK_LMCX_CHAR_CTL(lmc), char_ctl.u);
}

int
choose_best_hw_patterns(bdk_node_t node, int lmc, int mode)
{
    static const char *modes_str[4] = {"TEST", "DBI", "LFSR", "ERR"};
    int new_mode = mode;
    const char *s;
    int lfsr_enable = 1;

    switch (mode) {
    case DBTRAIN_TEST: // always choose LFSR as all chips support it
        if ((s = getenv("ddr_allow_lfsr"))) { // override?
            lfsr_enable = !!strtoul(s, NULL, 0);
        }
        if (lfsr_enable)
            new_mode = DBTRAIN_LFSR;
        break;
    case DBTRAIN_DBI: // possibly can allow LFSR use?
        break;
    case DBTRAIN_LFSR: // forced already
        break;
    default:
        ddr_print("ERROR: unknown HW assist mode %s\n", modes_str[mode]);
    }

    if (new_mode != mode)
        VB_PRT(VBL_DEV2, "choose_best_hw_patterns: changing mode %s to %s\n",
               modes_str[mode], modes_str[new_mode]);

    return new_mode;
}

int
run_best_hw_patterns_rank(bdk_node_t node, int lmc, int rankx,
                     int mode, uint64_t *xor_data)
{
    int pattern;
    int errs, errors = 0;
    uint64_t bad_bits[2];
    int use_lfsr;

    // FIXME? always choose LFSR if chip supports it???
    mode = choose_best_hw_patterns(node, lmc, mode);

    use_lfsr = ((mode == DBTRAIN_LFSR) || (mode == DBTRAIN_DBI));

    if (xor_data != NULL) {
        xor_data[0] = 0;
        xor_data[1] = 0;
    }

    for (pattern = 0; pattern < NUM_PATTERNS; pattern++) {
        if (use_lfsr)
            setup_lfsr_pattern(node, lmc, pattern);
        else
            setup_hw_pattern(node, lmc, pattern);

        errs = test_dram_byte_hw_rank(node, lmc, rankx, mode, bad_bits);

        VB_PRT(VBL_DEV2, "%s: %s %d at rank %d errors 0x%x\n",
               __FUNCTION__, (use_lfsr) ? "LFSR" : "PATTERN",
               pattern, rankx, errs);

        errors |= errs;
        if (xor_data != NULL) {
            xor_data[0] |= bad_bits[0];
            xor_data[1] |= bad_bits[1];
        }

    } /* for (pattern = 0; pattern < NUM_PATTERNS; pattern++) */

    return errors;
}

// on CN9xxx, set the DLL settings to offset the DLL90 values back to 0
#define CN9_DLL_BIAS_DLL90 1

void
hw_assist_test_dll_offset(bdk_node_t node, int dll_offset_mode,
                          int lmc, int bytelane)
{
    int byte_offset, new_best_offset[9];
    int rank_delay_start[4][9];
    int rank_delay_count[4][9];
    int rank_delay_best_start[4][9];
    int rank_delay_best_count[4][9];
    int errors[4], off_errors, tot_errors;
    int rank_mask, rankx;
    int pattern;
    int byte;
    char *mode_str = (dll_offset_mode == 2) ? "Read" : "Write";
    int pat_best_offset[9];
    int pat_beg, pat_end;
    int rank_beg, rank_end;
    int byte_lo, byte_hi;
    // FIXME? always choose LFSR if chip supports it???
    int mode = choose_best_hw_patterns(node, lmc, DBTRAIN_TEST);

    BDK_CSR_INIT(lmcx_config, node, BDK_LMCX_CONFIG(lmc));

    if (bytelane == 0x0A) { // all bytelanes
        byte_lo = 0;
        byte_hi = (lmcx_config.s.mode32b) ? 4 : 8; // check for 32-bit mode
    } else { // just 1
        byte_lo = byte_hi = bytelane;
    }

#if CN9_DLL_BIAS_DLL90
    // FIXME: on CN9xxx, use the DLL90 settings to bias DLL settings back to 0
    if (bdk_is_model(OCTEONTX_CN9XXX)) {
        int dll90_settings[9];
        Get_DLL90_Settings(node, lmc, dll90_settings);
        // copy/negate the DLL90 settings 
        for (byte = byte_hi; byte >= byte_lo; --byte) {
            new_best_offset[byte] = -dll90_settings[byte];
        } /* for (byte = byte_hi; byte >= byte_lo; --byte) */
        goto print_and_set;
    }
#endif /* CN9_DLL_BIAS_DLL90 */

    rank_mask = lmcx_config.s.init_status;

    // start of pattern loop
    // we do the set of tests for each pattern supplied...

    memset(new_best_offset, 0, sizeof(new_best_offset));
    for (pattern = 0; pattern < NUM_PATTERNS; pattern++) {

	memset(pat_best_offset, 0, sizeof(pat_best_offset));

        if (mode == DBTRAIN_TEST) {
            setup_hw_pattern(node, lmc, pattern);
        } else {
            setup_lfsr_pattern(node, lmc, pattern);
        }

	// now loop through all legal values for the DLL byte offset...

	tot_errors = 0;

	memset(rank_delay_count, 0, sizeof(rank_delay_count));
	memset(rank_delay_start, 0, sizeof(rank_delay_start));
	memset(rank_delay_best_count, 0, sizeof(rank_delay_best_count));
	memset(rank_delay_best_start, 0, sizeof(rank_delay_best_start));

        // DLL offsets are 6-bits + sign on CN8, 8-bits + sign on CN9
        int max_byte_offset = CN8_OR_CN9(63, 255);
        int min_byte_offset = -max_byte_offset;

	for (byte_offset = min_byte_offset; byte_offset <= max_byte_offset; byte_offset += BYTE_OFFSET_INCR) {

	    // do the setup on the active LMC
	    // set the bytelanes DLL offsets
	    change_dll_offset_enable(node, lmc, 0);
	    load_dll_offset(node, lmc, dll_offset_mode, byte_offset, bytelane); // FIXME? bytelane?
	    change_dll_offset_enable(node, lmc, 1);

	    bdk_watchdog_poke();

	    // run the test on each rank
	    // only 1 call per rank should be enough, let the bursts, loops, etc, control the load...

	    off_errors = 0; // errors for this byte_offset, all ranks

	    for (rankx = 0; rankx < 4; rankx++) {
                if (!(rank_mask & (1 << rankx)))
                    continue;

                // NOTE: return is a now a bitmask of the erroring bytelanes..
		errors[rankx] = test_dram_byte_hw_rank(node, lmc, rankx, mode, NULL);

                for (byte = byte_lo; byte <= byte_hi; byte++) { // do bytelane(s)

                    // check errors
                    if (errors[rankx] & (1 << byte)) { // yes, an error in the byte lane in this rank
                        off_errors |= (1 << byte);

                        ddr_print5("N%d.LMC%d.R%d: Bytelane %d DLL %s Offset Test %3d: errors 0x%x\n",
                                   node, lmc, rankx, bytelane, mode_str,
                                   byte_offset, errors[rankx]);

                        if (rank_delay_count[rankx][byte] > 0) { // had started run
                            ddr_print5("N%d.LMC%d.R%d: Bytelane %d DLL %s Offset Test %3d: stopping a run here\n",
                                       node, lmc, rankx, bytelane, mode_str, byte_offset);
                            rank_delay_count[rankx][byte] = 0;   // stop now
                        }
                        // FIXME: else had not started run - nothing else to do?
                    } else { // no error in the byte lane
                        if (rank_delay_count[rankx][byte] == 0) { // first success, set run start
                            ddr_print5("N%d.LMC%d.R%d: Bytelane %d DLL %s Offset Test %3d: starting a run here\n",
                                       node, lmc, rankx, bytelane, mode_str, byte_offset);
                            rank_delay_start[rankx][byte] = byte_offset;
                        }
                        rank_delay_count[rankx][byte] += BYTE_OFFSET_INCR; // bump run length

                        // is this now the biggest window?
                        if (rank_delay_count[rankx][byte] > rank_delay_best_count[rankx][byte]) {
                            rank_delay_best_count[rankx][byte] = rank_delay_count[rankx][byte];
                            rank_delay_best_start[rankx][byte] = rank_delay_start[rankx][byte];
                            debug_print("N%d.LMC%d.R%d: Bytelane %d DLL %s Offset Test %3d: updating best to %d/%d\n",
                                        node, lmc, rankx, bytelane, mode_str, byte_offset,
                                        rank_delay_best_start[rankx][byte], rank_delay_best_count[rankx][byte]);
                        }
                    }
                } /* for (byte = byte_lo; byte <= byte_hi; byte++) */
	    } /* for (rankx = 0; rankx < 4; rankx++) */

	    tot_errors |= off_errors;

	} /* for (byte_offset = min_byte_offset; byte_offset <= max_byte_offset; byte_offset += BYTE_OFFSET_INCR) */

        // set the bytelanes DLL offsets all back to 0
        change_dll_offset_enable(node, lmc, 0);
        load_dll_offset(node, lmc, dll_offset_mode, 0, bytelane);
        change_dll_offset_enable(node, lmc, 1);

	// now choose the best byte_offsets for this pattern according to the best windows of the tested ranks
        // calculate offset by constructing an average window from the rank windows
        for (byte = byte_lo; byte <= byte_hi; byte++) {

            pat_beg = -999;
            pat_end = 999;

            for (rankx = 0; rankx < 4; rankx++) {
                if (!(rank_mask & (1 << rankx)))
                    continue;

                rank_beg = rank_delay_best_start[rankx][byte];
                rank_end = rank_beg + rank_delay_best_count[rankx][byte] - BYTE_OFFSET_INCR;
                ddr_print5("N%d.LMC%d.R%d: Bytelane %d DLL %s Offset Test:  Rank Window %3d:%3d\n",
                           node, lmc, rankx, bytelane, mode_str, rank_beg, rank_end);
                pat_beg = max(pat_beg, rank_beg);
                pat_end = min(pat_end, rank_end);

            } /* for (rankx = 0; rankx < 4; rankx++) */

            pat_best_offset[byte] = (pat_end + pat_beg) / 2;

#if 0
            // FIXME: next print the window counts
            sprintf(sbuffer, "N%d.LMC%d Pattern %d: DLL %s Offset Count ",
                    node, lmc, pattern, mode_str);
            printf("%-45s : ", sbuffer);
            printf(" %3d", byte_delay_best_count);
            printf("\n");
#endif

            new_best_offset[byte] += pat_best_offset[byte]; // sum the pattern averages
        } /* for (byte = byte_lo; byte <= byte_hi; byte++) */

        // now print them on 1 line, descending order...
        ddr_print5("N%d.LMC%d: HW DLL %s Offset Pattern %d :",
                   node, lmc, mode_str, pattern);
        for (byte = byte_hi; byte >= byte_lo; --byte) {
            ddr_print5(" %4d", pat_best_offset[byte]);
        } /* for (byte = byte_lo; byte <= byte_hi; byte++) */
        ddr_print5("\n");

    } /* for (pattern = 0; pattern < NUM_PATTERNS; pattern++) */
    // end of pattern loop

    // calculate the settings 
    for (byte = byte_hi; byte >= byte_lo; --byte) { // print in decending byte index order
        new_best_offset[byte] = divide_nint(new_best_offset[byte], NUM_PATTERNS); // create the new average NINT
    } /* for (byte = byte_hi; byte >= byte_lo; --byte) */

    // now print and set
#if CN9_DLL_BIAS_DLL90
 print_and_set:
#endif /* CN9_DLL_BIAS_DLL90 */

    ddr_print("N%d.LMC%d: HW DLL %s Offset Tuning            : ",
              node, lmc, mode_str);

    change_dll_offset_enable(node, lmc, 0); // disable offsets while we load...

    for (byte = byte_hi; byte >= byte_lo; --byte) { // print in decending byte index order

        // print the best offsets from all patterns
        if (bytelane == 0x0A) // print just the offset of all the bytes
            ddr_print("%5d ", new_best_offset[byte]);
        else
            ddr_print("(byte %d) %4d ", byte, new_best_offset[byte]);

        // done with testing, load up the best offsets we found...
        load_dll_offset(node, lmc, dll_offset_mode, new_best_offset[byte], byte);
    } /* for (byte = byte_hi; byte >= byte_lo; --byte) */

    ddr_print("\n");
    change_dll_offset_enable(node, lmc, 1); // re-enable the offsets now that we are done loading
}

/*
 * Automatically adjust the DLL offset for the selected bytelane using hardware-assist
 */
int perform_HW_dll_offset_tuning(bdk_node_t node, int dll_offset_mode, int bytelane)
{
    int save_ecc_ena[4];
    bdk_lmcx_config_t lmc_config;
    int lmc, num_lmcs = __bdk_dram_get_num_lmc(node);
    int lmc_mask = __bdk_dram_get_lmc_mask(node);
    const char *s;
    //bdk_lmcx_comp_ctl2_t comp_ctl2;
    int loops = 1, loop;

    // see if we want to do the tuning more than once per LMC...
    if ((s = getenv("ddr_tune_ecc_loops"))) {
	loops = strtoul(s, NULL, 0);
    }

    // allow override of the test repeats (bursts)
    if ((s = getenv("ddr_tune_byte_bursts")) != NULL) {
        dram_tune_byte_bursts = strtoul(s, NULL, 10);
    }

    // print current working values
    ddr_print2("N%d: HW %s DLL Tuning for bytelane %d will use %d loops, and %d patterns.\n",
               node, (dll_offset_mode == 2) ?"Read":"Write", bytelane, loops, NUM_PATTERNS);

    // FIXME? get flag from LMC0 only
    lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(0));

    // do once for each active LMC

    for (lmc = 0; lmc < num_lmcs; lmc++) {

        if (!(lmc_mask & (1 << lmc)))
            continue;

	ddr_print4("N%d: HW Tuning: starting LMC%d bytelane %d tune.\n", node, lmc, bytelane);

	/* Enable ECC for the HW tests */
	// NOTE: we do enable ECC, but the HW tests used will not generate "visible" errors
	lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(lmc));
	save_ecc_ena[lmc] = lmc_config.s.ecc_ena;
	lmc_config.s.ecc_ena = 1;
	DRAM_CSR_WRITE(node, BDK_LMCX_CONFIG(lmc), lmc_config.u);
	lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(lmc));

	// testing is done on a single LMC at a time
	// FIXME: for now, loop here to show what happens multiple times
	for (loop = 0; loop < loops; loop++) {
	    /* Perform DLL offset tuning */
	    hw_assist_test_dll_offset(node, dll_offset_mode, lmc, bytelane);
	}

	// perform cleanup on active LMC
	ddr_print4("N%d: HW Tuning: finishing LMC%d bytelane %d tune.\n", node, lmc, bytelane);

	/* Restore ECC for DRAM tests */
	lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(lmc));
	lmc_config.s.ecc_ena = save_ecc_ena[lmc];
	DRAM_CSR_WRITE(node, BDK_LMCX_CONFIG(lmc), lmc_config.u);
	lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(lmc));

	// finally, see if there are any read offset overrides after tuning
	for (int by = 0; by < 9; by++) {
	    if ((s = lookup_env_parameter("ddr%d_tune_byte%d", lmc, by)) != NULL) {
		int dllro = strtoul(s, NULL, 10);
                change_dll_offset_enable(node, lmc, 0);
		load_dll_offset(node, lmc, dll_offset_mode, dllro, by);
                change_dll_offset_enable(node, lmc, 1);
	    }
	}
    } /* for (lmc = 0; lmc < num_lmcs; lmc++) */

    // finish up...

    return 0;

} /* perform_HW_dll_offset_tuning */
