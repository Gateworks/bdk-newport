/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/* $Revision: 102369 $ */

#include <bdk.h>
#include "libbdk-arch/bdk-csrs-l2c.h"
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libdram.h"
#include "dram-internal.h"
#include "bdk-dram-init.h"

/* Define DDR_DEBUG to debug the DDR interface.  This also enables the
** output necessary for review by Marvell International Ltd. */
/* #define DDR_DEBUG */


static int global_ddr_clock_initialized = 0;
static int global_ddr_memory_preserved  = 0;

uint64_t global_scramble_cfg0[4];
uint64_t global_scramble_cfg1[4];
uint64_t global_scramble_cfg2[4];

/*
 * SDRAM Physical Address on CN8XXX (figure 6-2 from the HRM)
 *                                                                   7 6    3 2   0
 * +---------+----+----------------------+---------------+--------+---+------+-----+
 * |  Dimm   |Rank|         Row          |      Col      |  Bank  | C |  Col | Bus |
 * +---------+----+----------------------+---------------+--------+---+------+-----+
 *     |    ^   |            |          ^        |           |      |
 *   0 or 1 |   |       12-18 bits      |      6-8 bits      |    1 or 2 bits
 *    bit   | 0 or 1 bit           LMC_CONFIG[ROW_LSB]+X     |    (X=1 or 2, resp)
 *          |                                                |
 *   LMC_CONFIG[PBANK_LSB]+X                               3 or 4 bits
 *
 *    Bus     = Selects the byte on the 72-bit DDR bus
 *    Col     = Column Address for the memory part (10-12 bits)
 *    C       = Selects the LMC that services the reference
 *              (2 bits for 4 LMC mode, 1 bit for 2 LMC mode; X=width)
 *    Bank    = Bank Address for the memory part (DDR4=3 or 4 bits)
 *    Row     = Row Address for the memory part (12-18 bits)
 *    Rank    = Optional Rank Address for dual-rank DIMMs
 *              (present when LMC_CONFIG[RANK_ENA] is set)
 *    Dimm    = Optional DIMM address (preseent with more than 1 DIMM)
 */


/**
 * Divide and round results to the nearest integer.
 *
 * @param dividend
 * @param divisor
 *
 * @return
 */
uint64_t divide_nint(uint64_t dividend, uint64_t divisor)
{
    uint64_t quotent, remainder;
    quotent   = dividend / divisor;
    remainder = dividend % divisor;
    return quotent + ((remainder * 2) >= divisor);
}

/* Sometimes the pass/fail results for all possible delay settings
 * determined by the read-leveling sequence is too forgiving.  This
 * usually occurs for DCLK speeds below 300 MHz. As a result the
 * passing range is exaggerated. This function accepts the bitmask
 * results from the sequence and truncates the passing range to a
 * reasonable range and recomputes the proper deskew setting.
 */

/* Default ODT config must disable ODT */
/* Must be const (read only) so that the structure is in flash */
const dimm_odt_config_t disable_odt_config[] = {
	/* DDR4 needs an additional field in the struct (odt_mask2) */
	/* DIMMS   ODT_ENA ODT_MASK   ODT_MASK1      ODT_MASK2     QS_DIC RODT_CTL */
	/* =====   ======= ========   =========      =========     ====== ======== */
	/*   1 */ {   0,    0x0000,   {.u = 0x0000}, {.u = 0x0000},    0,   0x0000  },
	/*   2 */ {   0,    0x0000,   {.u = 0x0000}, {.u = 0x0000},    0,   0x0000  },
	/*   3 */ {   0,    0x0000,   {.u = 0x0000}, {.u = 0x0000},    0,   0x0000  },
	/*   4 */ {   0,    0x0000,   {.u = 0x0000}, {.u = 0x0000},    0,   0x0000  },
};
/* Memory controller setup function */
static int init_octeon_dram_interface(bdk_node_t node,
				      const ddr_configuration_t *ddr_configuration,
				      uint32_t ddr_hertz,
				      uint32_t cpu_hertz,
				      uint32_t ddr_ref_hertz,
				      int board_type,
				      int board_rev_maj,
				      int board_rev_min,
				      int ddr_interface_num,
				      uint32_t ddr_interface_mask)
{
    int mem_size_mbytes = 0;
    int lmc_restart_retries = 0;
#define DEFAULT_RESTART_RETRIES 3
    int lmc_restart_retries_limit = DEFAULT_RESTART_RETRIES;

    const char *s;
    if ((s = lookup_env_parameter("ddr_timing_hertz")) != NULL)
	ddr_hertz = strtoul(s, NULL, 0);
    if ((s = lookup_env_parameter("ddr_restart_retries_limit")) != NULL)
        lmc_restart_retries_limit = strtoul(s, NULL, 0);

 restart_lmc_init:

    /* Poke the watchdog timer so it doesn't expire during DRAM init */
    bdk_watchdog_poke();

    mem_size_mbytes =
        init_octeontx_ddr_interface(node, ddr_configuration,
                                    ddr_hertz, cpu_hertz, ddr_ref_hertz,
                                    board_type, board_rev_maj, board_rev_min,
                                    ddr_interface_num, ddr_interface_mask);

    if (mem_size_mbytes == 0) { // means restart is possible
        if (lmc_restart_retries < lmc_restart_retries_limit) {
            lmc_restart_retries++;
            ddr_print("N%d.LMC%d Configuration problem: attempting LMC reset and init restart %d\n",
                        node, ddr_interface_num, lmc_restart_retries);
            // re-assert RESET first, as that is the assumption of the init code
            if (!ddr_memory_preserved(node)) {
                do_lmc_ddr_reset(node, ddr_interface_num, LMC_RESET_ASSERT);
            }
            goto restart_lmc_init;
        } else {
            if (lmc_restart_retries_limit > 0) {
                error_print("INFO: N%d.LMC%d Configuration: fatal problem remains after %d LMC init retries - Resetting node.\n",
                            node, ddr_interface_num, lmc_restart_retries);
                bdk_wait_usec(500000);
                bdk_reset_chip(node);
            } else {
                mem_size_mbytes = -1; // no restart
            }
        }
    } /* if (mem_size_mbytes == 0) */

    if (mem_size_mbytes < 0) { // means restart is IMPOSSIBLE
        error_print("N%d.LMC%d Configuration FAILED!\n", node, ddr_interface_num);
    } else {
#if 0 // NEWPORT
        error_print("N%d.LMC%d Configuration Completed: %d MB\n",
                    node, ddr_interface_num, mem_size_mbytes);
#endif
    }
    return mem_size_mbytes;
}

static void set_ddr_memory_preserved(bdk_node_t node)
{
    global_ddr_memory_preserved |= 0x1 << node;
}
int ddr_memory_preserved(bdk_node_t node)
{
    return (global_ddr_memory_preserved & (0x1 << node)) != 0;
}
uint64_t get_scramble_cfg0(bdk_node_t node, int lmc)
{
    return global_scramble_cfg0[lmc];
}
uint64_t get_scramble_cfg1(bdk_node_t node, int lmc)
{
    return global_scramble_cfg1[lmc];
}
uint64_t get_scramble_cfg2(bdk_node_t node, int lmc)
{
    return global_scramble_cfg2[lmc];
}

void perform_ddr_init_sequence(bdk_node_t node, int rank_mask,
				       int ddr_interface_num)
{
    const char *s;
    int ddr_init_loops = 1;
    int rankx;

    if ((s = lookup_env_parameter("ddr%d_init_loops", ddr_interface_num)) != NULL)
	ddr_init_loops = strtoul(s, NULL, 0);

    while (ddr_init_loops--) {
	for (rankx = 0; rankx < 8; rankx++) {
	    if (!(rank_mask & (1 << rankx)))
		continue;

            perform_octeontx_ddr_sequence(node, (1 << rankx),
                                          ddr_interface_num, 0); /* power-up/init */

	    bdk_wait_usec(1000);   /* Wait a while. */

	    if ((s = lookup_env_parameter("ddr_sequence1")) != NULL) {
		int sequence1;
		sequence1 = strtoul(s, NULL, 0);
		perform_octeontx_ddr_sequence(node, (1 << rankx),
					      ddr_interface_num, sequence1);
	    }

	    if ((s = lookup_env_parameter("ddr_sequence2")) != NULL) {
		int sequence2;
		sequence2 = strtoul(s, NULL, 0);
		perform_octeontx_ddr_sequence(node, (1 << rankx),
					      ddr_interface_num, sequence2);
	    }
	}
    }
}

static void set_ddr_clock_initialized(bdk_node_t node, int ddr_interface, int inited_flag)
{
	int bit = node * 8 + ddr_interface;
	if (inited_flag)
		global_ddr_clock_initialized |= (0x1 << bit);
	else
		global_ddr_clock_initialized &= ~(0x1 << bit);
}
static int ddr_clock_initialized(bdk_node_t node, int ddr_interface)
{
	int bit = node * 8 + ddr_interface;
	return (!!(global_ddr_clock_initialized & (0x1 << bit)));
}


static void
octeontx_lmc_dreset_init (bdk_node_t node, int ddr_interface_num)
{
    /*
     * This is the embodiment of the 6.9.4 LMC DRESET Initialization section below.
     *
     * The remainder of this section describes the sequence for LMCn.
     *
     * 1. If not done already, write LMC(0..3)_DLL_CTL2 to its reset value
     *    (except without changing the LMC(0..3)_DLL_CTL2[INTF_EN] value from
     *    that set in the prior Step 3), including LMC(0..3)_DLL_CTL2[DRESET] = 1.

     * 2. Without changing any other LMC(0..3)_DLL_CTL2 fields, write
     *    LMC(0..3)_DLL_CTL2[DLL_BRINGUP] = 1.
     * 3. Read LMC(0..3)_DLL_CTL2 and wait for the result.
     * 4. Wait for a minimum of 10 LMC CK cycles.
     * 5. Without changing any other fields in LMC(0..3)_DLL_CTL2, write
     *    LMC(0..3)_DLL_CTL2[QUAD_DLL_ENA] = 1.
     *    LMC(0..3)_DLL_CTL2[QUAD_DLL_ENA] must not change after this point
     *    without restarting the LMCn DRESET initialization sequence.
     * 6. Read LMC(0..3)_DLL_CTL2 and wait for the result.
     * 7. Wait a minimum of 10 us.
     * 8. Without changing any other fields in LMC(0..3)_DLL_CTL2, write
     *    LMC(0..3)_DLL_CTL2[DLL_BRINGUP] = 0.
     *    LMC(0..3)_DLL_CTL2[DLL_BRINGUP] must not change after this point
     *    without restarting the LMCn DRESET initialization sequence.
     * 9. Read LMC(0..3)_DLL_CTL2 and wait for the result.
     * 10. Without changing any other fields in LMC(0..3)_DLL_CTL2, write
     *    LMC(0..3)_DLL_CTL2[DRESET] = 0.
     *    LMC(0..3)_DLL_CTL2[DRESET] must not change after this point without
     *    restarting the LMCn DRESET initialization sequence.
     *
     *    After completing LMCn DRESET initialization, all LMC CSRs may be
     *    accessed.  Prior to completing LMC DRESET initialization, only
     *    LMC(0..3)_DDR_PLL_CTL, LMC(0..3)_DLL_CTL2, LMC(0..3)_RESET_CTL, and
     *    LMC(0..3)_COMP_CTL2 LMC CSRs can be accessed.
     */
    // HRM-CN9XXX Section 7.9.4

    DRAM_CSR_MODIFY(c, node, BDK_LMCX_DLL_CTL2(ddr_interface_num),
                    c.s.dll_bringup = 1);
    BDK_CSR_READ(node, BDK_LMCX_DLL_CTL2(ddr_interface_num));
    bdk_wait_usec(1);

    DRAM_CSR_MODIFY(c, node, BDK_LMCX_DLL_CTL2(ddr_interface_num),
                    c.s.quad_dll_ena = 1);
    BDK_CSR_READ(node, BDK_LMCX_DLL_CTL2(ddr_interface_num));
    bdk_wait_usec(10);

    DRAM_CSR_MODIFY(c, node, BDK_LMCX_DLL_CTL2(ddr_interface_num),
                    c.s.dll_bringup = 0);
    BDK_CSR_READ(node, BDK_LMCX_DLL_CTL2(ddr_interface_num));
    bdk_wait_usec(1); // FIXME: maybe needed on CN9XXX???

    DRAM_CSR_MODIFY(c, node, BDK_LMCX_DLL_CTL2(ddr_interface_num),
                    c.s.dreset = 0);
    BDK_CSR_READ(node, BDK_LMCX_DLL_CTL2(ddr_interface_num));

    /*
     * NEW STEP - necessary for O73, O78 P2.0, O75, and T88 P2.0
     * McBuggin: #24821
     *
     * 11. Wait for a minimum of 10 LMC CK cycles.
     */

    bdk_wait_usec(1);
}

static int
Set_DDR_PLL_Speed(bdk_node_t node, uint32_t ddr_hertz,
                  uint32_t ddr_ref_hertz, uint32_t ddr_interface_mask)
{
    const char *s;
    int loop_interface_num;
    bdk_lmcx_ddr_pll_ctl_t ddr_pll_ctl;

    if (bdk_is_model(OCTEONTX_CN8XXX)) {
        /* CLKF = (DCLK * (CLKR+1) * EN(1, 2, 3, 4, 5, 6, 7, 8, 10, 12))/DREF - 1 */
        int en_idx, save_en_idx, best_en_idx=0;
        uint64_t clkf, clkr, max_clkf = 127;
        uint64_t best_clkf=0, best_clkr=0;
        uint64_t best_pll_MHz = 0;
        uint64_t pll_MHz;
        uint64_t min_pll_MHz = 800;
        uint64_t max_pll_MHz = 5000;
        uint64_t error;
        uint64_t best_error;
        uint64_t best_calculated_ddr_hertz = 0;
        uint64_t calculated_ddr_hertz = 0;
        uint64_t orig_ddr_hertz = ddr_hertz;
        static const int _en[] = {1, 2, 3, 4, 5, 6, 7, 8, 10, 12};
        int override_pll_settings;
        int new_bwadj;


        error = best_error = ddr_hertz;  /* Init to max error */

        ddr_print("DDR Reference Hertz = %d\n", ddr_ref_hertz);

        while (best_error == ddr_hertz) {

            for (clkr = 0; clkr < 4; ++clkr) {
                for (en_idx=sizeof(_en)/sizeof(int)-1; en_idx>=0; --en_idx) {
                    save_en_idx = en_idx;
                    clkf = ((ddr_hertz) * (clkr+1) * (_en[save_en_idx]));
                    clkf = divide_nint(clkf, ddr_ref_hertz) - 1;
                    pll_MHz = ddr_ref_hertz * (clkf+1) / (clkr+1) / 1000000;
                    calculated_ddr_hertz = ddr_ref_hertz * (clkf + 1) / ((clkr + 1) * (_en[save_en_idx]));
                    error = ddr_hertz - calculated_ddr_hertz;

                    if ((pll_MHz < min_pll_MHz) || (pll_MHz > max_pll_MHz)) continue;
                    if (clkf > max_clkf) continue; /* PLL requires clkf to be limited */
                    if (_abs(error) > _abs(best_error)) continue;

                    VB_PRT(VBL_TME, "clkr: %2lu, en[%d]: %2d, clkf: %4lu, pll_MHz: %4lu, ddr_hertz: %8lu, error: %8ld\n",
                           clkr, save_en_idx, _en[save_en_idx], clkf, pll_MHz, calculated_ddr_hertz, error);

                    /* Favor the highest PLL frequency. */
                    if ((_abs(error) < _abs(best_error)) || (pll_MHz > best_pll_MHz)) {
                        best_pll_MHz = pll_MHz;
                        best_calculated_ddr_hertz = calculated_ddr_hertz;
                        best_error = error;
                        best_clkr = clkr;
                        best_clkf = clkf;
                        best_en_idx = save_en_idx;
                    }
                }
            }

            override_pll_settings = 0;

            if ((s = lookup_env_parameter("ddr_pll_clkr")) != NULL) {
                best_clkr = strtoul(s, NULL, 0);
                override_pll_settings = 1;
            }
            if ((s = lookup_env_parameter("ddr_pll_clkf")) != NULL) {
                best_clkf = strtoul(s, NULL, 0);
                override_pll_settings = 1;
            }
            if ((s = lookup_env_parameter("ddr_pll_en_idx")) != NULL) {
                best_en_idx = strtoul(s, NULL, 0);
                override_pll_settings = 1;
            }

            if (override_pll_settings) {
                best_pll_MHz = ddr_ref_hertz * (best_clkf+1) / (best_clkr+1) / 1000000;
                best_calculated_ddr_hertz = ddr_ref_hertz * (best_clkf + 1) / ((best_clkr + 1) * (_en[best_en_idx]));
                best_error = ddr_hertz - best_calculated_ddr_hertz;
            }

            ddr_print("clkr: %2lu, en[%d]: %2d, clkf: %4lu, pll_MHz: %4lu, ddr_hertz: %8lu, error: %8ld <==\n",
                      best_clkr, best_en_idx, _en[best_en_idx], best_clkf, best_pll_MHz,
                      best_calculated_ddr_hertz, best_error);

            /* Try lowering the frequency if we can't get a working configuration */
            if (best_error == ddr_hertz) {
                if (ddr_hertz < orig_ddr_hertz - 10000000)
                    break;
                ddr_hertz -= 1000000;
                best_error = ddr_hertz;
            }

        } /* while (best_error == ddr_hertz) */

        if (best_error == ddr_hertz) {
            error_print("ERROR: Can not compute a legal DDR clock speed configuration.\n");
            return(-1);
        }

        new_bwadj = (best_clkf + 1) / 10;
        VB_PRT(VBL_TME, "bwadj: %2d\n", new_bwadj);

        if ((s = lookup_env_parameter("ddr_pll_bwadj")) != NULL) {
            new_bwadj = strtoul(s, NULL, 0);
            VB_PRT(VBL_TME, "bwadj: %2d\n", new_bwadj);
        }

        /*
         * 3. Without changing any other LMC(0..1)_DDR_PLL_CTL values, write
         *    LMC(0..1)_DDR_PLL_CTL[CLKF, CLKR] with a value that gives a desired DDR
         *    PLL speed.
         */
        for (loop_interface_num = 0; loop_interface_num < 2; ++loop_interface_num) {
            if ((ddr_interface_mask & (1 << loop_interface_num)) == 0)
                continue;

            // make sure we preserve any settings already there
            ddr_pll_ctl.u = BDK_CSR_READ(node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num));
            ddr_print("LMC%d: DDR_PLL_CTL                             : 0x%016lx\n",
                      loop_interface_num, ddr_pll_ctl.u);

            ddr_pll_ctl.cn83xx.ddr_ps_en = best_en_idx;
            ddr_pll_ctl.cn83xx.clkf = best_clkf;
            ddr_pll_ctl.cn83xx.clkr = best_clkr;
            ddr_pll_ctl.cn83xx.reset_n = 0;
            ddr_pll_ctl.cn83xx.bwadj = new_bwadj;

            DRAM_CSR_WRITE(node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num), ddr_pll_ctl.u);
            ddr_print("LMC%d: DDR_PLL_CTL                             : 0x%016lx\n",
                      loop_interface_num, ddr_pll_ctl.u);
        }
        for (loop_interface_num = 0; loop_interface_num < 4; ++loop_interface_num) {
            if ((ddr_interface_mask & (1 << loop_interface_num)) == 0)
                continue;

            /*
             * 4. Read LMC0_DDR_PLL_CTL and wait for the result.
             * 5. Wait a minimum of 3 us.
             * 6. Write LMC0_DDR_PLL_CTL[RESET_N] = 1 without changing any other
             *    LMC0_DDR_PLL_CTL values.
             * 7. Read LMC0_DDR_PLL_CTL and wait for the result.
             * 8. Wait a minimum of 25 us.
             */

            BDK_CSR_READ(node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num));
            bdk_wait_usec(3);          /* Wait 3 us */
            DRAM_CSR_MODIFY(c, node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num),
                            c.cn83xx.reset_n = 1);
            BDK_CSR_READ(node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num));
            bdk_wait_usec(25);          /* Wait 25 us */

        } /* for (loop_interface_num = 0; loop_interface_num < 4; ++loop_interface_num) */
    }

    int force_cn9_calc = 0;
    if ((s = lookup_env_parameter("ddr_force_cn9_calc")) != NULL) {
	force_cn9_calc = !!strtoul(s, NULL, 0);
    }
    
    // HRM-CN9XXX Section 7.9.2.3-13

    if (bdk_is_model(OCTEONTX_CN9XXX) || force_cn9_calc) {

        /* 7.15 CK Speed Programming

           The LMC CK speed is determined by the DDR PLL speed and the post-scalar divider.
           The DDR PLL multiplies the received PLL_REF_CLK or DDRn_ALT_REF_CLK_P/N.
           The DDR PLL speed must reside between 1.6 GHz and 5.0 GHz.

           If PLL_REF_CLK is used:

               DDR PLL speed (MHz) = (LMC*_DDR_PLL_CTL[CLKF] x 100) / LMC*_DDR_PLL_CTL[PREDIV]

           The LMC CK speed is a divide-down of the DDR PLL output:

               LMC CK speed (MHz) = DDR PLL Speed (MHz) / LMC*_DDR_PLL_CTL[POSTDIV]

           Speed       Data Rate      [CLKF]    [PREDIV] [POSTDIV]
           Grade

           1600 MT/s   800/1600 MT/s   96 (0x60)  3     0x1 (divide by 4)
           1866 MT/s   933/1867 MT/s  112 (0x70)  3     0x1 (divide by 4)
           2133 MT/s  1067/2133 MT/s  128 (0x80)  3     0x1 (divide by 4)
           2400 MT/s  1200/2400 MT/s  144 (0x90)  3     0x1 (divide by 4)
           2666 MT/s  1333/2667 MT/s  160 (0xA0)  3     0x1 (divide by 4)
           2933 MT/s  1467/2933 MT/s  176 (0xB0)  3     0x1 (divide by 4)
           3200 MT/s  1600/3200 MT/s   96 (0x60)  3     0x0 (divide by 2)
        */

#define PLL_MAX 6000   // in MHz
#define PLL_MIN 3000   // in MHz
#define REFCLK  100    // in MHz

        int clkf, prediv, postdiv, actual_postdiv;
        int ddr_pll_speed, lmc_ck_speed;
        int best_pll_speed, best_ck_speed, best_clkf, best_prediv;
        int best_postdiv, best_actual_postdiv;
        int best_err, new_err, calc_mts;

        int mts = (ddr_hertz / 1000000) * 2;
        int count = 0;

        // limit prediv to just div1 on chips with PLL race condition possible
        int max_prediv = (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) ||
                          bdk_is_model(OCTEONTX_CNF95XX_PASS1_X)) ? 1 : 3;

        best_pll_speed = 0;
        best_prediv = max_prediv + 1;
        best_err = 100;

        for (actual_postdiv = 0; actual_postdiv < 4; actual_postdiv += 1) {

            postdiv = (1 << (actual_postdiv + 1));

            for (prediv = max_prediv; prediv >= 1; prediv -= 1) {

                for (clkf = 1; clkf < 512; clkf += 1) {

                    ddr_pll_speed = divide_nint(clkf * REFCLK, prediv);
                    if ((ddr_pll_speed > PLL_MAX) || (ddr_pll_speed < PLL_MIN))
                        continue;

                    lmc_ck_speed = divide_nint(ddr_pll_speed, postdiv);
                    calc_mts = 2 * lmc_ck_speed;

                    new_err = mts - calc_mts;
                    if (new_err < 0) // ignore all overclocks
                        continue;

                    if ((new_err < best_err) ||
                        ((new_err == best_err) &&
                         ((ddr_pll_speed > best_pll_speed) || (prediv < best_prediv))))
                    {
                        best_err = new_err;
                        best_pll_speed = ddr_pll_speed;
                        best_ck_speed = lmc_ck_speed;
                        best_clkf = clkf;
                        best_prediv = prediv;
                        best_postdiv = postdiv;
                        best_actual_postdiv = actual_postdiv;
                        count += 1;
                    }
                } /* for (clkf = 1; clkf < 512; clkf += 1) */
            } /* for (prediv = max_prediv; prediv >= 1; prediv -= 1) */
        } /* for (actual_postdiv = 0; actual_postdiv < 4; actual_postdiv += 1) */

        if (count <= 0) {
            printf("ERROR: NO matches for MT/s %d\n", mts);
            return (-1);
        } else if (dram_is_verbose(VBL_FAE)) {
            //ddr_print("Total matches for MT/s %d: %d\n", mts, count);
            ddr_print("MT/s %4d, lmc_ck_speed %4d, ddr_pll_speed %4d, clkf %3d(0x%02x), prediv %2d, postdiv %2d, best_err %d\n",
                      mts, best_ck_speed, best_pll_speed, best_clkf, best_clkf, best_prediv, best_postdiv, best_err);
            ddr_print("Best settings: CLKF 0x%x, PREDIV %d, POSTDIV %d\n", best_clkf, best_prediv, best_actual_postdiv);
       }

        if (force_cn9_calc)
            return 0;

        // only on LMC0 if 1-LMC mode, else on LMC0 & maybe LMC1 if appropriate
        for (loop_interface_num = 0; loop_interface_num < 2; ++loop_interface_num) {
            if ((ddr_interface_mask & (1 << loop_interface_num)) == 0)
                continue;

            // make sure we preserve any settings already there
            ddr_pll_ctl.u = BDK_CSR_READ(node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num));
            ddr_print("LMC%d: %-39s : 0x%016lx\n", loop_interface_num, "DDR_PLL_CTL (orig)", ddr_pll_ctl.u);

            // HRM-CN9XXX Section 7.9.2.3
            /* Section 7.9 describes the LMC CK initialization sequence.
              1. Write [CLKF], [POSTDIV], [PREDIV], [DCLK_INVERT]. LMC0 should set
                 [DCLK_INVERT] to 0, LMC1 should set it to 1.
              2. Write 0 to PD, 1 to [UPDATE], 1 to [PLL_RESET], 1 to [PS_RESET].
              3. Wait 500 ref clock cycles (5us).
              4. Write 0 to [PLL_RESET].
              5. Wait 2000 ref clock cycles (20us).
              6. Write 0x3 to [PLL_SEL]. LMCs not bringing up the PLL need to write 0x3 to
                 [PLL_SEL] to receive the phase-shifted PLL output
              7. Write 0 to [PS_RESET].
              8. Wait 2 ref clock cycles (20ns).
              9. Write 1 to [PHY_DCOK], wait 20us before bringing up the DDR interface.
            */
            ddr_pll_ctl.cn9.clkf       = best_clkf;
            ddr_pll_ctl.cn9.postdiv    = best_actual_postdiv;
            ddr_pll_ctl.cn9.prediv     = best_prediv;
            //ddr_pll_ctl.cn9.dclk_invert = loop_interface_num; // FIXME? already done in 6.9.2.2
            DRAM_CSR_WRITE(node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num), ddr_pll_ctl.u);

            // HRM-CN9XXX Section 7.9.2.4
            ddr_pll_ctl.cn9.pd         = 0;
            ddr_pll_ctl.cn9.pll_reset  = 1;
            ddr_pll_ctl.cn9.ps_reset   = 1;
            ddr_pll_ctl.cn9.update     = 1; // VERIF does this here, not in 7.9.2.5
            DRAM_CSR_WRITE(node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num), ddr_pll_ctl.u);

            // HRM-CN9XXX Section 7.9.2.5
            // nothing now (see above 7.9.2.4)

            // HRM-CN9XXX Section 7.9.2.6
            bdk_wait_usec(5);

            // HRM-CN9XXX Section 7.9.2.7
            ddr_pll_ctl.cn9.pll_reset  = 0;
            ddr_pll_ctl.cn9.update     = 0; // from VERIF code
            DRAM_CSR_WRITE(node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num), ddr_pll_ctl.u);

            // HRM-CN9XXX Section 7.9.2.8
            // HRM DDR_PLL_CTL CSR description step 5
            bdk_wait_usec(20);

            // HRM DDR_PLL_CTL CSR description step 6
            ddr_pll_ctl.cn9.pll_sel    = 3;
            DRAM_CSR_WRITE(node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num), ddr_pll_ctl.u);

            // HRM-CN9XXX Section 7.9.2.9
            // HRM DDR_PLL_CTL CSR description step 7
            ddr_pll_ctl.cn9.ps_reset   = 0;
            DRAM_CSR_WRITE(node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num), ddr_pll_ctl.u);

            // HRM-CN9XXX Section 7.9.2.10
            BDK_CSR_READ(node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num));
        } /* for (loop_interface_num = 0; loop_interface_num < 2; ++loop_interface_num) */

        // on all active LMCs
        for (loop_interface_num = 0; loop_interface_num < 4; ++loop_interface_num) {
            if ((ddr_interface_mask & (1 << loop_interface_num)) == 0)
                continue;

            // HRM-CN9XXX Section 7.9.2.11
            ddr_pll_ctl.u = BDK_CSR_READ(node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num));
            ddr_pll_ctl.cn9.pll_sel    = 3;
            DRAM_CSR_WRITE(node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num), ddr_pll_ctl.u);

            // HRM-CN9XXX Section 7.9.2.12
            BDK_CSR_READ(node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num));

            ddr_print("LMC%d: %-39s : 0x%016lx\n", loop_interface_num, "DDR_PLL_CTL (new)", ddr_pll_ctl.u);

            // HRM-CN9XXX Section 7.9.2.13
            // Initial programming of LMC(0..2)_CTL for BRINGUP is set to all 0s;
            // that means Conservative Mode for WRCMD and RDRSP fields below.
            // At some future time we will want to set the following fields:
            //    DCLK_MUL with approp setting for multiplier
            //    WRCMD_CLK_XING_MODE set to AUTO (2)
            //    RDF_CNT set to RNDUP(DDR_clock_frequency (MHz) / 50)
            //    RDRSP_CLK_XING_MODE set to AUTO (3)
            bdk_lmcx_ctl_t lmc_ctl;
            lmc_ctl.u = 0;
            //lmc_ctl.s.cond_rclk_dis = 1; // FIXME? DEBUG ONLY?
            DRAM_CSR_WRITE(node, BDK_LMCX_CTL(loop_interface_num), lmc_ctl.u);

        } /* for (loop_interface_num = 0; loop_interface_num < 4; ++loop_interface_num) */
    } /* if (bdk_is_model(OCTEONTX_CN9XXX) || force_cn9_calc) */

    return 0;
}


int initialize_ddr_clock(bdk_node_t node,
			 const ddr_configuration_t *ddr_configuration,
                         uint32_t cpu_hertz,
                         uint32_t ddr_hertz,
                         uint32_t ddr_ref_hertz,
                         int ddr_interface_num,
                         uint32_t ddr_interface_mask
                         )
{
    const char *s;

    if (ddr_clock_initialized(node, ddr_interface_num))
        return 0;

    if (!ddr_clock_initialized(node, 0)) { /* Do this once */
        int lmc, preserving_mem, active_lmcs;
        bdk_lmcx_reset_ctl_t reset_ctl;

        /* Check to see if all of memory is to be preserved and set global flag */
        preserving_mem = 0;
        active_lmcs = 0;
        for (lmc = 0; lmc < 4; lmc++) {
            if ((ddr_interface_mask & (1 << lmc)) == 0)
                continue;
            active_lmcs += 1;
            reset_ctl.u = BDK_CSR_READ(node, BDK_LMCX_RESET_CTL(lmc));
            if (bdk_is_model(OCTEONTX_CN8XXX)) {
                if (reset_ctl.cn8.ddr3psv == 1) {
                    /* Re-initialize flags */
                    reset_ctl.cn8.ddr3pwarm = 0;
                    reset_ctl.cn8.ddr3psoft = 0;
                    reset_ctl.cn8.ddr3psv   = 0;
                    preserving_mem += 1;
                }
            }
            else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */ {
                if (reset_ctl.cn9.ddr4psv == 1) {
                    /* Re-initialize flags */
                    reset_ctl.cn9.ddr4pdomain = 0; // force SW to re-init elsewhere later
                    reset_ctl.cn9.ddr4psv     = 0; // clear so HW can maybe set it (again) later
                    if (reset_ctl.cn9.training_completed) {
                        preserving_mem += 1;
                        reset_ctl.cn9.training_completed = 0; // will be set again later usually
                    } else {
                        ddr_print("N%d.LMC%d: NOT Preserving memory: Training incomplete\n",
                                  node, lmc);
                    }
                }
            }
            DRAM_CSR_WRITE(node, BDK_LMCX_RESET_CTL(lmc), reset_ctl.u);
        } /* for (lmc = 0; lmc < 4; lmc++) */

        // FIXME: on CN9xxx, we might have some LMCs preserving, and some not???
        if (preserving_mem == active_lmcs) { // do NOT preserve unless all LMCs have done it
            ddr_print("N%d.LMC%d: Preserving memory\n", node, ddr_interface_num);
            set_ddr_memory_preserved(node);
        }
    } /* if (!ddr_clock_initialized(node, 0)) */

    { // block begin
        bdk_lmcx_ddr_pll_ctl_t ddr_pll_ctl;
        int loop_interface_num;

        /*
         * 6.9 LMC Initialization Sequence
         *
         * There are 14 parts to the LMC initialization procedure:
         *
         * 1. LMC interface enable initialization
         *
         * 2. DDR PLL initialization
         *
         * 3. LMC CK initialization
         *
         * 4. LMC DRESET initialization
         *
         * 5. LMC CK local initialization
         *
         * 6. LMC RESET initialization
         *
         * 7. Early LMC initialization
         *
         * 8. LMC offset training
         *
         * 9. LMC internal Vref training
         *
         * 10. LMC deskew training
         *
         * 11. LMC write leveling
         *
         * 12. LMC read leveling
         *
         * 13. DRAM Vref Training for DDR4
	 *
         * 14. Final LMC initialization
         *
         * CN88XX supports two modes:
         *
         * - two-LMC mode: both LMCs 2/3 must not be enabled
         *   (LMC2/3_DLL_CTL2[DRESET] must be set to 1 and LMC2/3_DLL_CTL2[INTF_EN]
         *   must be set to 0) and both LMCs 0/1 must be enabled).
         *
         * - four-LMC mode: all four LMCs 0..3 must be enabled.
         *
         * Steps 4 and 6..14 should each be performed for each enabled LMC (either
         * twice or four times). Steps 1..3 and 5 are more global in nature and
         * each must be executed exactly once (not once per LMC) each time the
         *  DDR PLL changes or is first brought up. Steps 1..3 and 5 need not be
         * performed if the DDR PLL is stable.
         *
         * Generally, the steps are performed in order. The exception is that the
         * CK local initialization (step 5) must be performed after some DRESET
         * initializations (step 4) and before other DRESET initializations when
         * the DDR PLL is brought up or changed. (The CK local initialization
         * uses information from some LMCs to bring up the other local CKs.) The
         * following text describes these ordering requirements in more detail.
         *
         * Following any chip reset, the DDR PLL must be brought up, and all 14
         * steps should be executed. Subsequently, it is possible to execute only
         * steps 4 and 6..14, or to execute only steps 8..14.
         *
         * The remainder of this section covers these initialization steps in
         * sequence.
         */

        if (ddr_interface_num == 0) { /* Do this once */
            bdk_lmcx_dll_ctl2_t	dll_ctl2;

            // HRM-CN9XXX Section 7.9.1
            /*
             * 6.9.1 LMC Interface-Enable Initialization
             *
             * LMC interface-enable initialization (Step 1) must be performed only
             * once, not once per LMC in four-LMC mode. This step is not required
	     * in two-LMC mode.
	     *
             * Perform the following three substeps for the LMC interface-enable
             * initialization:
             *
             * 1. Without changing any other LMC2_DLL_CTL2 fields (LMC(0..3)_DLL_CTL2
             *    should be at their reset values after Step 1), write
             *    LMC2_DLL_CTL2[INTF_EN] = 1 if four-LMC mode is desired.
             *
             * 2. Without changing any other LMC3_DLL_CTL2 fields, write
             *    LMC3_DLL_CTL2[INTF_EN] = 1 if four-LMC mode is desired.
             *
             * 3. Read LMC2_DLL_CTL2 and wait for the result.
             *
             * The LMC2_DLL_CTL2[INTF_EN] and LMC3_DLL_CTL2[INTF_EN] values should
             * not be changed by software from this point.
             *
             */

            // HRM-CN9XXX Section 7.9.1.1
	    /* Set DDR_PLL_CTL[pll_sel] = 0 for all active LMCs on 96XX,
               and set the other fields to their default reset values... */
            if (bdk_is_model(OCTEONTX_CN9XXX)) {
                bdk_lmcx_ddr_pll_ctl_t	ddr_pll_ctl;
                for (loop_interface_num = 0; loop_interface_num < 4; ++loop_interface_num) {
                    if ((ddr_interface_mask & (1 << loop_interface_num)) == 0)
                        continue;

                    ddr_pll_ctl.u = 0;

                    // set these reset values
                    ddr_pll_ctl.cn9.pll_sel  = 1; // use the actual RESET value
                    ddr_pll_ctl.cn9.prediv   = 3;
                    ddr_pll_ctl.cn9.pd       = 1;
                    ddr_pll_ctl.cn9.ps_reset = 1;
                    ddr_pll_ctl.cn9.clkf     = 0x60;

                    DRAM_CSR_WRITE(node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num), ddr_pll_ctl.u);
                    BDK_CSR_READ(node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num));
                }
            }

            // HRM-CN9XXX Section 7.9.1.3
	    /* Put all LMCs into DRESET here; these are the reset values... */
            for (loop_interface_num = 0; loop_interface_num < 4; ++loop_interface_num) {
                if ((ddr_interface_mask & (1 << loop_interface_num)) == 0)
                    continue;

                dll_ctl2.u = BDK_CSR_READ(node, BDK_LMCX_DLL_CTL2(loop_interface_num));

                dll_ctl2.s.byp_setting          = 0;
                dll_ctl2.s.byp_sel              = 0;
                dll_ctl2.s.quad_dll_ena         = 0;
                dll_ctl2.s.dreset               = 1;
                dll_ctl2.s.dll_bringup          = 0;
                dll_ctl2.s.intf_en              = 0;

                DRAM_CSR_WRITE(node, BDK_LMCX_DLL_CTL2(loop_interface_num), dll_ctl2.u);
            }

	    /* Do *NOT* touch LMC0 INTF_EN setting on 81XX/83XX, set it to 0. */
            /* But we do have to set LMC1 INTF_EN=1 on 83XX if we want it active... */
            /* Note that 81xx has only LMC0 so the mask should reflect that. */
            /* On 96XX, we need to set INTF_EN for *ALL* LMCs if present/populated */

            // HRM-CN9XXX Section 7.9.1.3 continued
            int loop_interface_start = 0; // default to CN9XXX, start with LMC0
            if (bdk_is_model(OCTEONTX_CN8XXX)) // for CN8XXX, start with LMC1
                 loop_interface_start = 1;

            for (loop_interface_num = loop_interface_start;
                 loop_interface_num < 4; ++loop_interface_num) {
                if ((ddr_interface_mask & (1 << loop_interface_num)) == 0)
                    continue;

                DRAM_CSR_MODIFY(c, node, BDK_LMCX_DLL_CTL2(loop_interface_num),
				c.s.intf_en = 1);
                BDK_CSR_READ(node, BDK_LMCX_DLL_CTL2(loop_interface_num));
            }

            // HRM-CN9XXX Section 7.9.2
            /*
             * 6.9.2 DDR PLL Initialization
             *
             * DDR PLL initialization (Step 2) must be performed for each chip reset
             * and whenever the DDR clock speed changes. This step needs to be
             * performed only once, not once per LMC.
             *
             * Perform the following eight substeps to initialize the DDR PLL:
             *
             * 1. If not done already, write all fields in LMC(0..1)_DDR_PLL_CTL and
             *    LMC(0..1)_DLL_CTL2 to their reset values, including:
             *
             * .. LMC0_DDR_PLL_CTL[DDR_DIV_RESET] = 1
             * .. LMC0_DLL_CTL2[DRESET] = 1
             *
             * This substep is not necessary after a chip reset.
             *
             */

            ddr_pll_ctl.u = BDK_CSR_READ(node, BDK_LMCX_DDR_PLL_CTL(0));

            // allow override of LMC0 desired setting for DCLK_INVERT
            int ddr0_dclk_invert = 0;
            if ((s = lookup_env_parameter("ddr0_set_dclk_invert")) != NULL) {
                ddr0_dclk_invert = !!strtoul(s, NULL, 0);
                ddr_print("LMC0: override DDR_PLL_CTL[dclk_invert] to %d\n",
                          ddr0_dclk_invert);
            }

            // HRM-CN9XXX Section 7.9.2.1
            //  NOTE: DLL_CTL reset values are set above in step 7.9.1.3
            if (bdk_is_model(OCTEONTX_CN8XXX)) {
                ddr_pll_ctl.cn83xx.reset_n           = 0;
                ddr_pll_ctl.cn83xx.ddr_div_reset     = 1;
                ddr_pll_ctl.cn83xx.phy_dcok          = 0;
                ddr_pll_ctl.cn83xx.dclk_invert       = ddr0_dclk_invert;
            }
            else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */ {
                ddr_pll_ctl.cn9.pll_reset            = 0;
                ddr_pll_ctl.cn9.phy_dcok             = 0;
                ddr_pll_ctl.cn9.dclk_invert          = ddr0_dclk_invert;
            }

            // always write LMC0 CSR, it must be active
            DRAM_CSR_WRITE(node, BDK_LMCX_DDR_PLL_CTL(0), ddr_pll_ctl.u);
            ddr_print("%-45s : 0x%016lx\n", "LMC0: DDR_PLL_CTL", ddr_pll_ctl.u);

            // only when LMC1 is active
            // NOTE: 81xx has only 1 LMC, and 83xx/9xxx can operate in 1-LMC mode
            if (ddr_interface_mask & 0x2) {
                /* DEFAULT: Toggle dclk_invert from LMC0 */
                int ddr1_dclk_invert = ddr0_dclk_invert ^ 1;

                // allow override of LMC1 desired setting for DCLK_INVERT
                if ((s = lookup_env_parameter("ddr1_set_dclk_invert")) != NULL) {
                    ddr1_dclk_invert = !!strtoul(s, NULL, 0);
                    ddr_print("LMC1: override DDR_PLL_CTL[dclk_invert] to %d\n",
                              ddr1_dclk_invert);
                }

                if (bdk_is_model(OCTEONTX_CN8XXX))
                    ddr_pll_ctl.cn83xx.dclk_invert       = ddr1_dclk_invert;
                else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */
                    ddr_pll_ctl.cn9.dclk_invert          = ddr1_dclk_invert;

                // always write LMC1 CSR when it is active
                DRAM_CSR_WRITE(node, BDK_LMCX_DDR_PLL_CTL(1), ddr_pll_ctl.u);
                ddr_print("%-45s : 0x%016lx\n", "LMC1: DDR_PLL_CTL", ddr_pll_ctl.u);
            }

#if 0
            // HRM-CN9XXX Section 7.9.2.2
            /*
             * 2. If the current DRAM contents are not preserved (see
             *    LMC(0..3)_RESET_ CTL[DDR3PSV]), this is also an appropriate time to
             *    assert the RESET# pin of the DDR3/DDR4 DRAM parts. If desired, write
             *    LMC0_RESET_ CTL[DDR3RST] = 0 without modifying any other
             *    LMC0_RESET_CTL fields to assert the DDR_RESET_L pin. No action is
             *    required here to assert DDR_RESET_L following a chip reset. Refer to
             *    Section 6.9.6. Do this for all enabled LMCs.
             */
            if (!ddr_memory_preserved(node)) {
                for (loop_interface_num = 0; loop_interface_num < 4; ++loop_interface_num) {
                    if ((ddr_interface_mask & (1 << loop_interface_num)) == 0)
                        continue;

                    do_lmc_ddr_reset(node, loop_interface_num, LMC_RESET_ASSERT);
                }
            }
#endif
            /*
             * 3. Without changing any other LMC0_DDR_PLL_CTL values, write LMC0_DDR_
             *    PLL_CTL[CLKF] with a value that gives a desired DDR PLL speed. The
             *    LMC0_DDR_PLL_CTL[CLKF] value should be selected in conjunction with
             *    the post-scalar divider values for LMC (LMC0_DDR_PLL_CTL[DDR_PS_EN])
             *    so that the desired LMC CK speeds are is produced (all enabled LMCs
             *    must run the same speed). Section 5.14 describes
             *    LMC0_DDR_PLL_CTL[CLKF] and LMC0_DDR_PLL_CTL[DDR_PS_EN] programmings
             *    that produce the desired LMC CK speed. Section 6.9.3 describes LMC CK
             *    initialization, which can be done separately from the DDR PLL
             *    initialization described in this section.
             *
             * The LMC0_DDR_PLL_CTL[CLKF] value must not change after this point
             * without restarting this SDRAM PLL initialization sequence.
             */
            // HRM-CN9XXX Section 7.9.2.3-13
            if (Set_DDR_PLL_Speed(node, ddr_hertz, ddr_ref_hertz, ddr_interface_mask) != 0)
                return (-1);

            for (loop_interface_num = 0; loop_interface_num < 4; ++loop_interface_num) {
                if ((ddr_interface_mask & (1 << loop_interface_num)) == 0)
                    continue;
                // HRM-CN9XXX Section 7.9.3
		/*
		 * 6.9.3 LMC CK Initialization
		 *
		 * DDR PLL initialization must be completed prior to starting LMC CK
		 * initialization.
		 *
		 * Perform the following substeps to initialize the LMC CK. Perform
		 * substeps 1..3 for both LMC0 and LMC1.
		 *
		 * 1. Without changing any other LMC(0..3)_DDR_PLL_CTL values, write
		 *    LMC(0..3)_DDR_PLL_CTL[DDR_DIV_RESET] = 1 and
		 *    LMC(0..3)_DDR_PLL_CTL[DDR_PS_EN] with the appropriate value to get the
		 *    desired LMC CK speed. Section 5.14 discusses CLKF and DDR_PS_EN
		 *    programmings.  The LMC(0..3)_DDR_PLL_CTL[DDR_PS_EN] must not change
		 *    after this point without restarting this LMC CK initialization
		 *    sequence.
		 * 2. Without changing any other fields in LMC(0..3)_DDR_PLL_CTL, write
		 *    LMC(0..3)_DDR_PLL_CTL[DDR4_MODE] = 0.
		 * 3. Read LMC(0..3)_DDR_PLL_CTL and wait for the result.
		 * 4. Wait a minimum of 1 us.
		 * 5. Without changing any other fields in LMC(0..3)_DDR_PLL_CTL, write
		 *    LMC(0..3)_DDR_PLL_CTL[PHY_DCOK] = 1.
		 * 6. Read LMC(0..3)_DDR_PLL_CTL and wait for the result.
		 * 7. Wait a minimum of 20 us.
		 * 8. Without changing any other LMC(0..3)_COMP_CTL2 values, write
		 *    LMC(0..3)_COMP_CTL2[CK_CTL,CONTROL_CTL,CMD_CTL] to the desired
		 *    DDR*_CK_*_P control and command signals drive strength.
		 */
                if (bdk_is_model(OCTEONTX_CN8XXX)) {
                    DRAM_CSR_MODIFY(c, node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num),
                                    c.cn83xx.ddr_div_reset = 1);

                    DRAM_CSR_MODIFY(c, node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num),
                                    c.cn83xx.ddr4_mode = 1);

                    BDK_CSR_READ(node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num));

                    bdk_wait_usec(1);          /* Wait 1 us */

                    DRAM_CSR_MODIFY(c, node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num),
                                    c.cn83xx.phy_dcok = 1);
                }
                else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */ {

                    // HRM-CN9XXX Section 7.9.3.1
                    DRAM_CSR_MODIFY(c, node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num),
                                    c.cn9.phy_dcok = 1);
                }
                // HRM-CN9XXX Section 7.9.3.2
		BDK_CSR_READ(node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num));
                // HRM-CN9XXX Section 7.9.3.3
		bdk_wait_usec(20);          /* Wait 20 us */

		{
                    // HRM-CN8XXX Section 6.9.3.8
                    // HRM-CN9XXX Section 7.9.3.4
		    bdk_lmcx_comp_ctl2_t comp_ctl2;
		    const ddr_custom_config_t *custom_lmc_config = &ddr_configuration->custom_lmc_config;

		    comp_ctl2.u = BDK_CSR_READ(node, BDK_LMCX_COMP_CTL2(loop_interface_num));

                    // set reasonable defaults
                    comp_ctl2.s.dqx_ctl = CN8_OR_CN9(ddr4_dqx_driver_34_ohm, ddr4_dqx_driver_34_ohm_cn9);
		    comp_ctl2.s.rodt_ctl = CN8_OR_CN9(ddr4_rodt_ctl_60_ohm, ddr4_rodt_ctl_67_ohm_cn9); /* 60 or 67 ohm */
                    if (bdk_is_model(OCTEONTX_CN9XXX)) {
                        comp_ctl2.s.cmd_odt_ctl = ddr4_rodt_ctl_100_ohm_cn9;
                        if ((s = lookup_env_parameter("ddr_cmd_odt_ctl")) != NULL) {
                            comp_ctl2.s.cmd_odt_ctl  = strtoul(s, NULL, 0);
                        }
                    }

                    // also reasonable defaults
                    int driver_default = CN8_OR_CN9(ddr4_driver_34_ohm, ddr4_driver_30_ohm_cn9);

                    // override with configuration-specific values...
                    comp_ctl2.s.ck_ctl = driver_default; /* Default 34 or 30 ohm */
                    if (custom_lmc_config->ck_ctl != 0)
                        comp_ctl2.s.ck_ctl  = custom_lmc_config->ck_ctl;

                    comp_ctl2.s.cmd_ctl = driver_default; /* Default 34 or 30 ohm */
                    if (custom_lmc_config->cmd_ctl != 0)
                        comp_ctl2.s.cmd_ctl = custom_lmc_config->cmd_ctl;

                    comp_ctl2.s.control_ctl = driver_default; /* Default 34 or 30 ohm */
                    if (custom_lmc_config->ctl_ctl != 0)
                        comp_ctl2.s.control_ctl = custom_lmc_config->ctl_ctl;

		    // These need to be done here, not later in Step 6.9.7.
		    // NOTE: these are/will be specific to a chip; for now, set to 0
		    // should we provide overrides for these?
		    comp_ctl2.s.ntune_offset    = 0;
		    comp_ctl2.s.ptune_offset    = 0;

		    // now do any overrides...
		    if ((s = lookup_env_parameter("ddr_ck_ctl")) != NULL) {
			comp_ctl2.s.ck_ctl  = strtoul(s, NULL, 0);
		    }
		    if ((s = lookup_env_parameter("ddr_cmd_ctl")) != NULL) {
			comp_ctl2.s.cmd_ctl  = strtoul(s, NULL, 0);
		    }
		    if ((s = lookup_env_parameter("ddr_control_ctl")) != NULL) {
			comp_ctl2.s.control_ctl  = strtoul(s, NULL, 0);
		    }

		    DRAM_CSR_WRITE(node, BDK_LMCX_COMP_CTL2(loop_interface_num), comp_ctl2.u);
                    // HRM-CN9XXX Section 7.9.3.5
                    bdk_wait_usec(2); // 200 ns
		}

                // HRM-CN8XXX Section 6.9.3.8
		/*
		 * 9. Read LMC(0..3)_DDR_PLL_CTL and wait for the result.
		 * 10. Wait a minimum of 200 ns.
		 * 11. Without changing any other LMC(0..3)_DDR_PLL_CTL values, write
		 *     LMC(0..3)_DDR_PLL_CTL[DDR_DIV_RESET] = 0.
		 * 12. Read LMC(0..3)_DDR_PLL_CTL and wait for the result.
		 * 13. Wait a minimum of 200 ns.
		 */

		BDK_CSR_READ(node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num));

		bdk_wait_usec(1);          /* Wait 1 us */

                if (bdk_is_model(OCTEONTX_CN8XXX)) {
                    DRAM_CSR_MODIFY(c, node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num),
                                    c.cn83xx.ddr_div_reset = 0);
                    BDK_CSR_READ(node, BDK_LMCX_DDR_PLL_CTL(loop_interface_num));
                    bdk_wait_usec(1);          /* Wait 1 us */
                }

	    } /* for (loop_interface_num = 0; loop_interface_num < 4; ++loop_interface_num) */

        }  /* if (ddr_interface_num == 0) */ /* Do this once */

        if (ddr_interface_num == 0) { /* Do this once */
            bdk_lmcx_dll_ctl3_t ddr_dll_ctl3;

            /*
             * 6.9.4 LMC DRESET Initialization
             *
             * All of the DDR PLL, LMC global CK, and LMC interface enable
             * initializations must be completed prior to starting this LMC DRESET
             * initialization (Step 4).
             *
             * This LMC DRESET step is done for all enabled LMCs.
             */

            if (bdk_is_model(OCTEONTX_CN8XXX)) {
                // For CN8XXX:
                /* There are special constraints on the ordering of DRESET initialization
                 * (Steps 4) and CK local initialization (Step 5) whenever CK local
                 * initialization must be executed.  CK local initialization must be
                 * executed whenever the DDR PLL is being brought up (for each chip reset
                 * and whenever the DDR clock speed changes).
                 *
                 * When Step 5 must be executed in the two-LMC mode case:
                 * - LMC0 DRESET initialization must occur before Step 5.
                 * - LMC1 DRESET initialization must occur after Step 5.
                 *
                 * When Step 5 must be executed in the four-LMC mode case:
                 * - LMC2 and LMC3 DRESET initialization must occur before Step 5.
                 * - LMC0 and LMC1 DRESET initialization must occur after Step 5.
                 */

                if ((ddr_interface_mask == 0x1) || (ddr_interface_mask == 0x3)) {
                    /* ONE-LMC MODE FOR 81XX AND 83XX BEFORE STEP 5 */
                    /* TWO-LMC MODE BEFORE STEP 5 */
                    octeontx_lmc_dreset_init(node, 0);

                } else if (ddr_interface_mask == 0xf) {
                    /* FOUR-LMC MODE BEFORE STEP 5 */
                    octeontx_lmc_dreset_init(node, 2);
                    octeontx_lmc_dreset_init(node, 3);
                }
            }
            else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */ {

                // HRM-CN9XXX Section 7.9.4
                for (loop_interface_num = 0; loop_interface_num < 4; ++loop_interface_num) {
                    if (ddr_interface_mask & (1 << loop_interface_num))
                        octeontx_lmc_dreset_init(node, loop_interface_num);
                } /* for (loop_interface_num = 0; loop_interface_num < 4; ++loop_interface_num) */
            }

            if (bdk_is_model(OCTEONTX_CN8XXX)) {
                /*
                 * 6.9.5 LMC CK Local Initialization
                 *
                 * All of DDR PLL, LMC global CK, and LMC interface-enable
                 * initializations must be completed prior to starting this LMC CK local
                 * initialization (Step 5).
                 *
                 * LMC CK Local initialization must be performed for each chip reset and
                 * whenever the DDR clock speed changes. This step needs to be performed
                 * only once, not once per LMC.
                 *
                 * There are special constraints on the ordering of DRESET initialization
                 * (Steps 4) and CK local initialization (Step 5) whenever CK local
                 * initialization must be executed.  CK local initialization must be
                 * executed whenever the DDR PLL is being brought up (for each chip reset
                 * and whenever the DDR clock speed changes).
                 *
                 * When Step 5 must be executed in the two-LMC mode case:
                 * - LMC0 DRESET initialization must occur before Step 5.
                 * - LMC1 DRESET initialization must occur after Step 5.
                 *
                 * When Step 5 must be executed in the four-LMC mode case:
                 * - LMC2 and LMC3 DRESET initialization must occur before Step 5.
                 * - LMC0 and LMC1 DRESET initialization must occur after Step 5.
                 *
                 * LMC CK local initialization is different depending on whether two-LMC
                 * or four-LMC modes are desired.
                 */

                if (ddr_interface_mask == 0x3) {
                    /*
                     * 6.9.5.1 LMC CK Local Initialization for Two-LMC Mode
                     *
                     * 1. Write LMC0_DLL_CTL3 to its reset value. (Note that
                     *    LMC0_DLL_CTL3[DLL_90_BYTE_SEL] = 0x2 .. 0x8 should also work.)
                     */

                    ddr_dll_ctl3.u = 0;
                    ddr_dll_ctl3.s.dclk90_recal_dis = 1;
                    ddr_dll_ctl3.s.dll90_byte_sel = 1;
                    DRAM_CSR_WRITE(node, BDK_LMCX_DLL_CTL3(0),	ddr_dll_ctl3.u);

                    /*
                     * 2. Read LMC0_DLL_CTL3 and wait for the result.
                     */

                    BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(0));

                    /*
                     * 3. Without changing any other fields in LMC0_DLL_CTL3, write
                     *    LMC0_DLL_CTL3[DCLK90_FWD] = 1.  Writing LMC0_DLL_CTL3[DCLK90_FWD] = 1
                     *    causes clock-delay information to be forwarded from LMC0 to LMC1.
                     */

                    ddr_dll_ctl3.s.dclk90_fwd = 1;
                    DRAM_CSR_WRITE(node, BDK_LMCX_DLL_CTL3(0),	ddr_dll_ctl3.u);

                    /*
                     * 4. Read LMC0_DLL_CTL3 and wait for the result.
                     */

                    BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(0));
                } /* if (ddr_interface_mask == 0x3) */

                if (ddr_interface_mask == 0xf) {
                    /*
                     * 6.9.5.2 LMC CK Local Initialization for Four-LMC Mode
                     *
                     * 1. Write LMC2_DLL_CTL3 to its reset value except
                     *    LMC2_DLL_CTL3[DLL90_BYTE_SEL] = 0x7.
                     */

                    ddr_dll_ctl3.u = 0;
                    ddr_dll_ctl3.s.dclk90_recal_dis = 1;
                    ddr_dll_ctl3.s.dll90_byte_sel = 7;
                    DRAM_CSR_WRITE(node, BDK_LMCX_DLL_CTL3(2),	ddr_dll_ctl3.u);

                    /*
                     * 2. Write LMC3_DLL_CTL3 to its reset value except
                     *    LMC3_DLL_CTL3[DLL90_BYTE_SEL] = 0x0.
                     */

                    ddr_dll_ctl3.u = 0;
                    ddr_dll_ctl3.s.dclk90_recal_dis = 1;
                    ddr_dll_ctl3.s.dll90_byte_sel = 0; /* HRM wants 0, not 2 */
                    DRAM_CSR_WRITE(node, BDK_LMCX_DLL_CTL3(3),	ddr_dll_ctl3.u); /* HRM wants LMC3 */

                    /*
                     * 3. Read LMC3_DLL_CTL3 and wait for the result.
                     */

                    BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(3));

                    /*
                     * 4. Without changing any other fields in LMC2_DLL_CTL3, write
                     *    LMC2_DLL_CTL3[DCLK90_FWD] = 1 and LMC2_DLL_CTL3[DCLK90_RECAL_DIS] = 1.
                     *    Writing LMC2_DLL_CTL3[DCLK90_FWD] = 1 causes LMC 2 to forward
                     *    clock-delay information to LMC0. Setting
                     *    LMC2_DLL_CTL3[DCLK90_RECAL_DIS] to 1 prevents LMC2 from periodically
                     *    recalibrating this delay information.
                     */

                    DRAM_CSR_MODIFY(c, node, BDK_LMCX_DLL_CTL3(2),
                                    c.s.dclk90_fwd = 1;
                                    c.s.dclk90_recal_dis = 1);

                    /*
                     * 5. Without changing any other fields in LMC3_DLL_CTL3, write
                     *    LMC3_DLL_CTL3[DCLK90_FWD] = 1 and LMC3_DLL_CTL3[DCLK90_RECAL_DIS] = 1.
                     *    Writing LMC3_DLL_CTL3[DCLK90_FWD] = 1 causes LMC3 to forward
                     *    clock-delay information to LMC1. Setting
                     *    LMC3_DLL_CTL3[DCLK90_RECAL_DIS] to 1 prevents LMC3 from periodically
                     *    recalibrating this delay information.
                     */

                    DRAM_CSR_MODIFY(c, node, BDK_LMCX_DLL_CTL3(3),
                                    c.s.dclk90_fwd = 1;
                                    c.s.dclk90_recal_dis = 1);

                    /*
                     * 6. Read LMC3_DLL_CTL3 and wait for the result.
                     */

                    BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(3));
                } /* if (ddr_interface_mask == 0xf) */

                /* ONE-LMC MODE AFTER STEP 5 - NOTHING */

                /* TWO-LMC MODE AFTER STEP 5 */
                if (ddr_interface_mask == 0x3) {
                    octeontx_lmc_dreset_init(node, 1);
                }

                /* FOUR-LMC MODE AFTER STEP 5 */
                if (ddr_interface_mask == 0xf) {
                    octeontx_lmc_dreset_init(node, 0);
                    octeontx_lmc_dreset_init(node, 1);

                    /* Enable periodic recalibration of DDR90 delay line in. */
                    DRAM_CSR_MODIFY(c, node, BDK_LMCX_DLL_CTL3(0),
                                    c.s.dclk90_recal_dis = 0);
                    DRAM_CSR_MODIFY(c, node, BDK_LMCX_DLL_CTL3(1),
                                    c.s.dclk90_recal_dis = 0);
                }

                /* Enable the trim circuit on the appropriate channels to
                   adjust the DDR clock duty cycle for chips that support
                   it. */
                bdk_lmcx_phy_ctl_t lmc_phy_ctl;
                int loop_interface_num;

                for (loop_interface_num = 0; loop_interface_num < 4; ++loop_interface_num) {
                    if ((ddr_interface_mask & (1 << loop_interface_num)) == 0)
                        continue;

                    lmc_phy_ctl.u = BDK_CSR_READ(node, BDK_LMCX_PHY_CTL(loop_interface_num));
                    lmc_phy_ctl.cn83xx.lv_mode = (~loop_interface_num) & 1; /* Odd LMCs = 0, Even LMCs = 1 */

                    ddr_print("LMC%d: PHY_CTL                                 : 0x%016lx\n",
                              loop_interface_num, lmc_phy_ctl.u);
                    DRAM_CSR_WRITE(node, BDK_LMCX_PHY_CTL(loop_interface_num), lmc_phy_ctl.u);
                }
            } /* if (bdk_is_model(OCTEONTX_CN8XXX)) */

            /* Enable fine tune mode, etc for all LMCs */
            for (int lmc = 0; lmc < 4; ++lmc) {
                if ((ddr_interface_mask & (1 << lmc)) == 0)
                    continue;
                ddr_dll_ctl3.u = BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(lmc));
                ddr_dll_ctl3.s.fine_tune_mode = 1;
                if (bdk_is_model(OCTEONTX_CN9XXX)) {
                    ddr_dll_ctl3.cn9.wr_deskew_mem_sel = 1; // even if wrdsk is not enabled
                }
                DRAM_CSR_WRITE(node, BDK_LMCX_DLL_CTL3(lmc), ddr_dll_ctl3.u);
            }

        } /* Do this once */
    } // block end

    set_ddr_clock_initialized(node, ddr_interface_num, 1);
    return(0);
}
///////////////////////////////////////////////////////////
// start of DBI switchover

/* first pattern example:
   GENERAL_PURPOSE0.DATA == 64'h00ff00ff00ff00ff;
   GENERAL_PURPOSE1.DATA == 64'h00ff00ff00ff00ff;
   GENERAL_PURPOSE0.DATA == 16'h0000;
*/
//const uint64_t dbi_pattern[3] = { 0x00ff00ff00ff00ffULL, 0x00ff00ff00ff00ffULL, 0x0000ULL };

// Perform switchover to DBI
void
dbi_switchover_interface(int node, int lmc,
                         dram_init_data_t *init_data,
                         dram_overrides_t *overrides)
{
    bdk_lmcx_modereg_params0_t modereg_params0;
    bdk_lmcx_modereg_params3_t modereg_params3;
    bdk_lmcx_phy_ctl_t phy_ctl;
    bdk_lmcx_config_t lmcx_config;
    int rankx;
    int errors;
    int dbi_settings[9], byte, unlocked, retries;
    int ecc_ena;
    int is_cn8xxx = bdk_is_model(OCTEONTX_CN8XXX);
    int rank_max = (is_cn8xxx) ? 1 : 4; // for T8X, just do rank 0
    int rank_mask = init_data->refs.rank_mask;
    int do_dbi = overrides->init.dbi_mode;

    if (!do_dbi)
        return;

    lmcx_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(lmc));
    ecc_ena = lmcx_config.s.ecc_ena;

    // FIXME: must filter out any non-supported configs
    //        ie, no x4 devices, no 81XX
    if ((lmcx_config.s.mode_x4dev == 1) || bdk_is_model(OCTEONTX_CN81XX)) {
        ddr_print("N%d.LMC%d: DBI switch-over: inappropriate device; IGNORING...\n",
                  node, lmc);
        return;
    }

    ddr_print("N%d.LMC%d: DBI Mode training starting with rank mask 0x%x\n",
	      node, lmc, rank_mask);

    /* 1. conduct the current init sequence as usual all the way
         after software write leveling.
     */
    //read_DAC_DBI_settings(node, lmc, 0/*rank*/, /*DBI*/0, dbi_settings);
    //display_DAC_DBI_settings(node, lmc, 0/*rank*/, /* DBI */0, ecc_ena, dbi_settings, " INIT");

   /* 2. set DBI related CSRs as below and issue MR write.
         MODEREG_PARAMS3.WR_DBI=1
         MODEREG_PARAMS3.RD_DBI=1
         PHY_CTL.DBI_MODE_ENA=1
    */
    modereg_params0.u = BDK_CSR_READ(node, BDK_LMCX_MODEREG_PARAMS0(lmc));

    modereg_params3.u = BDK_CSR_READ(node, BDK_LMCX_MODEREG_PARAMS3(lmc));
    modereg_params3.s.wr_dbi = 1;
    modereg_params3.s.rd_dbi = 1;
    DRAM_CSR_WRITE(node, BDK_LMCX_MODEREG_PARAMS3(lmc), modereg_params3.u);

    phy_ctl.u = BDK_CSR_READ(node, BDK_LMCX_PHY_CTL(lmc));
    phy_ctl.s.dbi_mode_ena = 1;
    DRAM_CSR_WRITE(node, BDK_LMCX_PHY_CTL(lmc), phy_ctl.u);

    /*
         There are two options for data to send.  Lets use (2), ie use LFSR:

        1) DBTRAIN_CTL[LFSR_PATTERN_SEL] = 0 (or for older chips where this does not exist)
           set data directly in these registers.  this will yield a clk/2 pattern:
           GENERAL_PURPOSE0.DATA == 64'h00ff00ff00ff00ff;
           GENERAL_PURPOSE1.DATA == 64'h00ff00ff00ff00ff;
           GENERAL_PURPOSE0.DATA == 16'h0000;

    DRAM_CSR_WRITE(node, BDK_LMCX_GENERAL_PURPOSE0(lmc), dbi_pattern[0]);
    DRAM_CSR_WRITE(node, BDK_LMCX_GENERAL_PURPOSE1(lmc), dbi_pattern[1]);
    DRAM_CSR_WRITE(node, BDK_LMCX_GENERAL_PURPOSE2(lmc), dbi_pattern[2]);

        2) DBTRAIN_CTL[LFSR_PATTERN_SEL] = 1
           here data comes from the LFSR generating a PRBS pattern
           CHAR_CTL.EN = 0
           CHAR_CTL.SEL = 0; // for PRBS
           CHAR_CTL.DR = 1;
           CHAR_CTL.PRBS = setup for whatever type of PRBS to send
           CHAR_CTL.SKEW_ON = 1;
    */

    /*
      3. adjust cas_latency (only necessary if RD_DBI is set).
         here is my code for doing this:

         if (csr_model.MODEREG_PARAMS3.RD_DBI.value == 1) begin
           case (csr_model.MODEREG_PARAMS0.CL.value)
             0,1,2,3,4: csr_model.MODEREG_PARAMS0.CL.value += 2; // CL 9-13 -> 11-15
             5: begin
                // CL=14, CWL=10,12 gets +2, CLW=11,14 gets +3
                if((csr_model.MODEREG_PARAMS0.CWL.value==1 || csr_model.MODEREG_PARAMS0.CWL.value==3))
                  csr_model.MODEREG_PARAMS0.CL.value = 7; // 14->16
                else
                  csr_model.MODEREG_PARAMS0.CL.value = 13; // 14->17
                end
             6: csr_model.MODEREG_PARAMS0.CL.value = 8; // 15->18
             7: csr_model.MODEREG_PARAMS0.CL.value = 14; // 16->19
             8: csr_model.MODEREG_PARAMS0.CL.value = 15; // 18->21
             9: begin     
                  if (csr_model.MODEREG_PARAMS3.GD.value == 0) begin                // 20->23
                    //csr_model.MODEREG_PARAMS0.CL_EXT.value = 0;
                    csr_model.MODEREG_PARAMS0.CL.value     = 5'hC;
                  end else begin                                                    // 20->22
                    //csr_model.MODEREG_PARAMS0.CL_EXT.value = 0;
                    csr_model.MODEREG_PARAMS0.CL.value     = 5'hA;
                  end
                end
           'hA: begin                                      // 22->26
                 //csr_model.MODEREG_PARAMS0.CL_EXT.value = 1;
                 csr_model.MODEREG_PARAMS0.CL.value     = 5'h11;
              end
           'hB: begin                                      // 24->28 
                 //csr_model.MODEREG_PARAMS0.CL_EXT.value = 1;
                 csr_model.MODEREG_PARAMS0.CL.value     = 5'h13; 
              end
             default:
             `cn_fatal(("Error mem_cfg (%s) CL (%d) with RD_DBI=1, I am not sure what to do.",
                        mem_cfg, csr_model.MODEREG_PARAMS3.RD_DBI.value))
           endcase
        end
    */

    if (modereg_params3.s.rd_dbi == 1) {
        int old_cl, new_cl, old_cwl;

        if (is_cn8xxx) {
            old_cl  = modereg_params0.cn8.cl;
            old_cwl = modereg_params0.cn8.cwl;
        } else {
	    old_cl  = modereg_params0.cn9.cl;
	    old_cwl = modereg_params0.cn9.cwl;
        }

        switch (old_cl) {
        case 0: case 1: case 2: case 3: case 4: new_cl = old_cl + 2; break; // 9-13->11-15
        // CL=14, CWL=10,12 gets +2, CLW=11,14 gets +3
        case 5:  new_cl = ((old_cwl == 1) || (old_cwl == 3)) ? 7 : 13; break;
        case 6:  new_cl =  8; break; // 15->18
        case 7:  new_cl = 14; break; // 16->19
        case 13: new_cl =  9; break; // 17->20
        case 8:  new_cl = 15; break; // 18->21
        case 14: new_cl = 10; break; // 19->22
        case 9:  new_cl = 12; break; // 20->23 // FIXME: if geardown, 20->22
        case 15: new_cl = 16; break; // 21->25
        case 10: new_cl = 17; break; // 22->26
        case 12: new_cl = 18; break; // 23->27
        case 11: new_cl = 19; break; // 24->28
        default:
            error_print("ERROR: Bad CL value (%d) for DBI switch-over.\n", old_cl);
            // FIXME: need to error exit here...
            old_cl = -1;
            new_cl = -1;
            break;
        }
#if 1
        // FIXME: new way to calculate
        static const uint8_t xlate_dbi_cl[24] = {
         // 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
            2, 3, 4, 5, 6, 7, 8,14,15,12,17,19,18, 9,10,16,
         // 10  11  12  13  14  15  16  17 
            20, 21, 22, 23, 23, 23, 23, 23
        };
        int xlate_cl = xlate_dbi_cl[old_cl];
        if ((old_cl == 5) && (old_cwl != 1) && (old_cwl != 3))
            xlate_cl = 13;
        VB_PRT(VBL_DEV, "N%d.LMC%d: DBI: MODEREG_PARAMS0[cl] xlate %d (new %d)\n",
               node, lmc, xlate_cl, new_cl);
#endif

        ddr_print("N%d.LMC%d: DBI switch-over: CL ADJ: old_cl 0x%x, old_cwl 0x%x, new_cl 0x%x.\n",
                  node, lmc, old_cl, old_cwl, new_cl);

        if (is_cn8xxx)
            modereg_params0.cn8.cl = new_cl;
        else
            modereg_params0.cn9.cl = new_cl;

        DRAM_CSR_WRITE(node, BDK_LMCX_MODEREG_PARAMS0(lmc), modereg_params0.u);
    }

    /*
      4. issue MRW to MR0 (CL) and MR5 (DBI), using LMC sequence SEQ_CTL[SEQ_SEL] = MRW.
     */
    // Use the default values, from the CSRs fields
    // also, do B-sides for RDIMMs...

    for (rankx = 0; rankx < rank_max; rankx++) {
        if (!(rank_mask & (1 << rankx)))
            continue;

        // for RDIMMs, B-side writes should get done automatically when the A-side is written
        ddr4_mrw(node, lmc, rankx, -1/*use_defaults*/, 0/*MRreg*/, 0 /*A-side*/); /* MR0 */
        ddr4_mrw(node, lmc, rankx, -1/*use_defaults*/, 5/*MRreg*/, 0 /*A-side*/); /* MR5 */

    } /* for (rankx = 0; rankx < 4; rankx++) */

    if (bdk_is_model(OCTEONTX_CN9XXX) && ddr_memory_preserved(node)) {
        ddr_print("N%d.LMC%d: DBI switch-over: TRAINING finished for memory preserve mode\n",
                  node, lmc);
        return;
    }

    /*
      5. conduct DBI bit deskew training via the General Purpose R/W sequence (dbtrain).
         may need to run this over and over to get a lock (I need up to 5 in simulation):
         SEQ_CTL[SEQ_SEL] = RW_TRAINING (15)
         DBTRAIN_CTL.CMD_COUNT_EXT = all 1's
         DBTRAIN_CTL.READ_CMD_COUNT = all 1's
         DBTRAIN_CTL.TCCD_SEL = set according to MODEREG_PARAMS3[TCCD_L]
         DBTRAIN_CTL.RW_TRAIN = 1
         DBTRAIN_CTL.READ_DQ_COUNT = dont care
         DBTRAIN_CTL.WRITE_ENA = 1;
         DBTRAIN_CTL.ACTIVATE = 1;
         DBTRAIN_CTL LRANK, PRANK, ROW_A, BG, BA, COLUMN_A = set to a valid address
     */

    // NOW - do the training
    ddr_print("N%d.LMC%d: DBI switch-over: TRAINING begins...\n",
              node, lmc);

    // disable writing this time around
    if (!is_cn8xxx)
        DRAM_CSR_MODIFY(ctl3, node, BDK_LMCX_DLL_CTL3(lmc),
                        ctl3.cn9.rd_deskew_mem_sel_dis = 1);

    for (rankx = 0; rankx < rank_max; rankx++) {
        if (!(rank_mask & (1 << rankx)))
            continue;

        // perform Read Deskew first
        int dsk_err = Perform_Read_Deskew_Training_rank(node, (1 << rankx), lmc, init_data, overrides, 0);
        if (dsk_err) {
            ddr_print("N%d.LMC%d.R%d: DBI switch-over: ERROR: problem during DESKEW: ret = %d\n",
                      node, lmc, rankx, dsk_err);
        }
        retries = 0;

restart_dbi_training:

        // NOTE: return is a bitmask of the erroring bytelanes - we only print it
        errors = run_best_hw_patterns_rank(node, lmc, rankx, DBTRAIN_DBI, NULL);

        ddr_print("N%d.LMC%d: DBI switch-over: TEST: rank %d, errors 0x%x.\n",
                  node, lmc, rankx, errors);

        // NEXT - check for locking
        unlocked = 0;
        read_DAC_DBI_settings(node, lmc, rankx, /*DBI*/0, dbi_settings);

        for (byte = 0; byte < (8+ecc_ena); byte++) {
            unlocked += (dbi_settings[byte] & 1) ^ 1;
        }

        if (unlocked > 0) {
            ddr_print("N%d.LMC%d: DBI switch-over: LOCK: %d still unlocked.\n",
                  node, lmc, unlocked);

            retries++;
            if (retries < 10) {
                goto restart_dbi_training;
            } else {
                ddr_print("N%d.LMC%d: DBI switch-over: LOCK: %d retries exhausted.\n",
                          node, lmc, retries);
            }
        }

        // record the updated settings to rank-specific memory
        if (!is_cn8xxx) {
            DRAM_CSR_MODIFY(ctl3, node, BDK_LMCX_DLL_CTL3(lmc),
                            ctl3.cn9.rd_deskew_mem_ld = 1);
            BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(lmc));
            DRAM_CSR_MODIFY(ctl3, node, BDK_LMCX_DLL_CTL3(lmc),
                            ctl3.cn9.rd_deskew_mem_ld = 0);
            BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(lmc));
        }

        // FIXME: print out the DBI settings array after each rank?
        display_DAC_DBI_settings(node, lmc, rankx, /* DBI */0,
                                 ecc_ena, dbi_settings, " RANK");

    } /* for (rankx = 0; rankx < rank_max; rankx++) */

    // re-enable writing when done
    if (!is_cn8xxx)
        DRAM_CSR_MODIFY(ctl3, node, BDK_LMCX_DLL_CTL3(lmc),
                        ctl3.cn9.rd_deskew_mem_sel_dis = 0);
}

// end of DBI switchover
///////////////////////////////////////////////////////////

uint32_t measure_octeon_ddr_clock(bdk_node_t node,
				  const ddr_configuration_t *ddr_configuration,
				  uint32_t cpu_hertz,
				  uint32_t ddr_hertz,
				  uint32_t ddr_ref_hertz,
				  int ddr_interface_num,
				  uint32_t ddr_interface_mask)
{
	uint64_t core_clocks;
	uint64_t ddr_clocks;
	uint64_t calc_ddr_hertz;

	if (ddr_configuration) {
	    if (initialize_ddr_clock(node, ddr_configuration,
				     cpu_hertz, ddr_hertz, ddr_ref_hertz,
				     ddr_interface_num, ddr_interface_mask) != 0)
		return 0;
	}

        if (bdk_is_platform(BDK_PLATFORM_ASIM)) {
            /* ASIM doesn't have a DDR clock, force the measurement to be correct  */
            calc_ddr_hertz = ddr_hertz;
            ddr_clocks = ddr_hertz;
        } else {
            /* Dynamically determine the DDR clock speed */
            core_clocks = bdk_clock_get_count(BDK_CLOCK_TIME);
            ddr_clocks = BDK_CSR_READ(node, BDK_LMCX_DCLK_CNT(ddr_interface_num));
            bdk_wait_usec(100000); /* 100ms */
            ddr_clocks = BDK_CSR_READ(node, BDK_LMCX_DCLK_CNT(ddr_interface_num)) - ddr_clocks;
            core_clocks = bdk_clock_get_count(BDK_CLOCK_TIME) - core_clocks;
            calc_ddr_hertz = ddr_clocks * bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME) / core_clocks;
        }

        if (ddr_interface_num < 2) { // FIXME: print only for LMCs with PLLs
            ddr_print("N%d.LMC%d: Measured DDR clock: %lu, cpu clock: %u, ddr clocks: %lu\n",
                      node, ddr_interface_num, calc_ddr_hertz, cpu_hertz, ddr_clocks);
        }

	/* Check for unreasonable settings. */
	if (calc_ddr_hertz == 0) {
	    error_print("N%d.LMC%d: DDR clock misconfigured, returning 0.\n",
                        node, ddr_interface_num);
	    //exit(1);
	}

	return calc_ddr_hertz;
}

int octeon_ddr_initialize(bdk_node_t node,
			  uint32_t cpu_hertz,
			  uint32_t ddr_hertz,
			  uint32_t ddr_ref_hertz,
			  uint32_t ddr_interface_mask,
			  const ddr_configuration_t *ddr_configuration,
			  uint32_t *measured_ddr_hertz,
			  int board_type,
			  int board_rev_maj,
			  int board_rev_min)
{
    uint32_t ddr_config_valid_mask = 0;
    int memsize_mbytes = 0;
    const char *s;
    int retval;
    int interface_index;
    uint32_t ddr_max_speed = 1200000000; /* needs to be this high for DDR4 on CN8XXX */
    uint32_t calc_ddr_hertz = -1;
    int allowed_diff = (((int)ddr_hertz / 100) * 5); // 5% of desired, for validation

#ifndef OCTEON_SDK_VERSION_STRING
# define OCTEON_SDK_VERSION_STRING "OCTEONTX Development Build"
#endif

    ddr_print("%s: $Revision: 102369 $\n", OCTEON_SDK_VERSION_STRING); // FIXME: verb?

    if (bdk_is_model(OCTEONTX_CN9XXX))
        ddr_max_speed = 1600000000; /* needs to be this high for DDR4 on CN9XXX */

    if (ddr_hertz > ddr_max_speed) {
	error_print("DDR clock speed %u exceeds maximum supported DDR speed,"
		    " reducing to %uHz\n", ddr_hertz, ddr_max_speed);
	ddr_hertz = ddr_max_speed;
    }

    if (bdk_is_model(OCTEONTX_CN8XXX) && (ddr_hertz > cpu_hertz)) {
	error_print("\nFATAL ERROR: DDR speed %u exceeds CPU speed %u, exiting...\n\n",
		    ddr_hertz, cpu_hertz);
        return -1;
    }

    // Do this earlier so we can return without doing unnecessary things...
    /* Check for DIMM 0 socket populated for each LMC present */
    for (interface_index = 0; interface_index < 4; ++interface_index) {
	if ((ddr_interface_mask & (1 << interface_index)) &&
	    (validate_dimm(node, &ddr_configuration[interface_index].dimm_config_table[0])) == 1)
	{
	    ddr_config_valid_mask |= (1 << interface_index);
	}
    }

    if (!ddr_config_valid_mask) {
	puts("ERROR: No valid DIMMs detected on any DDR interface.\n");
	return -1;
    }

    if (bdk_is_model(OCTEONTX_CN9XXX)) {
        // Validate that CN9XXX is in legal config
        switch (ddr_config_valid_mask) {
        case 1: // 001 LMC0
        case 3: // 011 LMC0 LMC1
        case 5: // 101 LMC0 LMC2
        case 7: // 111 LMC0 LMC1 LMC2
            break; // valid!
        default:
            // configuration error
            puts("ERROR: Invalid LMC configuration detected.\n");
            return -1;
        }
    } /* if (bdk_is_model(OCTEONTX_CN9XXX)) */

#if 1
    // allow BDK_TRACE override
    extern uint64_t bdk_trace_enables;
    if ((s = lookup_env_parameter("ddr_trace_enables")) != NULL)
        bdk_trace_enables |= strtoull(s, NULL, 0);
#endif

    /*
      rdf_cnt: Defines the sample point of the LMC response data in
      the DDR-clock/core-clock crossing.  For optimal
      performance set to 10 * (DDR-clock period/core-clock
      period) - 1.  To disable set to 0. All other values
      are reserved.
    */
    uint64_t rdf_cnt;

    /* It is more convenient to compute the ratio using clock
       frequencies rather than clock periods.
    */
    rdf_cnt = (((uint64_t) 10 * cpu_hertz) / ddr_hertz) - 1;
    rdf_cnt = rdf_cnt < 256 ? rdf_cnt : 255;

    // allow override
    if ((s = lookup_env_parameter("early_fill_count")) != NULL)
        rdf_cnt = strtoul(s, NULL, 0);

    ddr_print("%-45s : %ld, cpu_hertz: %u, ddr_hertz: %u\n", "EARLY FILL COUNT  ",
              rdf_cnt, cpu_hertz, ddr_hertz);

    if (bdk_is_model(OCTEONTX_CN8XXX)) {
        BDK_CSR_INIT(l2c_ctl, node, BDK_L2C_CTL);
        l2c_ctl.s.rdf_cnt = rdf_cnt;
        DRAM_CSR_WRITE(node, BDK_L2C_CTL, l2c_ctl.u);
    } /* if (bdk_is_model(OCTEONTX_CN8XXX)) */

    // FIXME: for now, do limiting only for CN8XXX
    if (bdk_is_model(OCTEONTX_CN8XXX)) {
        /* Check to see if we should limit the number of L2 ways. */
        if ((s = lookup_env_parameter("limit_l2_ways")) != NULL) {
            int ways = strtoul(s, NULL, 10);
            limit_l2_ways(node, ways, 1);
        }
    } /* if (bdk_is_model(OCTEONTX_CN8XXX)) */

    /* We measure the DDR frequency by counting DDR clocks.  We can
     * confirm or adjust the expected frequency as necessary.  We use
     * the measured frequency to make accurate timing calculations
     * used to configure the controller.
     */
    for (interface_index = 0; interface_index < 4; ++interface_index) {
	uint32_t tmp_hertz;
        int hertz_diff;

	if (! (ddr_config_valid_mask & (1 << interface_index)))
	    continue;

    try_again:
        // if we are CN8XXX and LMC0, we may want the alternate refclk of 100MHz
        if (bdk_is_model(OCTEONTX_CN8XXX) && (interface_index == 0)) {
            // if we are asking for 100 MHz refclk, we can only get it via alternate, so switch to it
            // if we are NOT asking for 100MHz, then reset to (assumed) 50MHz and go on
            DRAM_CSR_MODIFY(c, node, BDK_LMCX_DDR_PLL_CTL(0),
                            c.s.dclk_alt_refclk_sel = (ddr_ref_hertz == 100000000));
            bdk_wait_usec(1000); // wait 1 msec
        }

	tmp_hertz = measure_octeon_ddr_clock(node, &ddr_configuration[interface_index],
					     cpu_hertz, ddr_hertz, ddr_ref_hertz,
					     interface_index, ddr_config_valid_mask);

        hertz_diff = _abs((int)tmp_hertz - (int)ddr_hertz);

        // if we are CN8XXX and LMC0 and we are asked for 100 MHz refclk,
        // we must be sure it is available
        // If not, we print an error message, set to 50MHz, and go on...
        if (bdk_is_model(OCTEONTX_CN8XXX) && (interface_index == 0) && (ddr_ref_hertz == 100000000)) {
            // validate that the clock returned is close enough to the clock desired
            // FIXME: is 5% close enough?
            if (hertz_diff > allowed_diff) { // nope, diff is greater than allowed
                ddr_print("N%d.LMC0: DRAM init: requested 100 MHz refclk NOT FOUND\n", node);
                ddr_ref_hertz = bdk_clock_get_rate(node, BDK_CLOCK_MAIN_REF);
                set_ddr_clock_initialized(node, 0, 0); // clear the flag before trying again!!
                goto try_again;
            } else {
                ddr_print("N%d.LMC0: DRAM Init: requested 100 MHz refclk FOUND and SELECTED.\n", node);
            }
        }

	if ((tmp_hertz == 0) || // uh-oh, error return on measuring
            (hertz_diff > allowed_diff)) // or maybe bad PLL setup
        {
            // do not proceed any further, try a chip RESET to recover...
            error_print("INFO: N%d.LMC%d Clock configuration fatal problem - Resetting node.\n",
                        node, interface_index);
            bdk_wait_usec(500000);
            bdk_reset_chip(node);
            // NOT REACHED
        } else {
	    calc_ddr_hertz = tmp_hertz;
        }

        // once the PLL is programmed, we must set-up LMC_CTL on 9XXX
        if (bdk_is_model(OCTEONTX_CN9XXX)) {

#define RD_XING_DEFAULT_MODE 3 // 0 is CONSERVATIVE, 3 for AUTO, 2 for FIXED
#define WR_XING_DEFAULT_MODE 2 // 0 is CONSERVATIVE, 2 for AUTO, 1 for MANUAL

            int rd_clk_xing_mode = RD_XING_DEFAULT_MODE;
            int wr_clk_xing_mode = WR_XING_DEFAULT_MODE;
            if ((s = lookup_env_parameter("ddr_rd_clk_xing_mode")) != NULL)
                rd_clk_xing_mode = strtoul(s, NULL, 0);
            if ((s = lookup_env_parameter("ddr_wr_clk_xing_mode")) != NULL)
                wr_clk_xing_mode = strtoul(s, NULL, 0);

            BDK_CSR_INIT(lmc_ctl, node, BDK_LMCX_CTL(interface_index));

            // if either is CONSERVATIVE, must setup RDF_CNT, so do it always
            lmc_ctl.s.rdf_cnt = rdf_cnt;

            // calculate DCLK_MUL always also, even when both are CONSERVATIVE
            uint64_t dclk_mul = divide_roundup(ddr_hertz, 50000000UL);
            lmc_ctl.s.dclk_mul = dclk_mul;

            lmc_ctl.s.predictive_start = (rd_clk_xing_mode == 1) ? 1 : 0;
            lmc_ctl.s.rdrsp_clk_xing_mode = rd_clk_xing_mode;
            lmc_ctl.s.wrcmd_clk_xing_mode = wr_clk_xing_mode;

            VB_PRT(VBL_DEV, "N%d.LMC%d: CN9XXX: LMCX_CTL: RDF_CNT 0x%02lx, DCLK_MUL 0x%02lx, RD_MODE %d, WR_MODE %d\n",
                      node, interface_index, rdf_cnt, dclk_mul,
                      rd_clk_xing_mode, wr_clk_xing_mode);

            //lmc_ctl.s.cond_rclk_dis = 1; // FOR DEBUG ONLY

            DRAM_CSR_WRITE(node, BDK_LMCX_CTL(interface_index), lmc_ctl.u);
            ddr_print("N%d.LMC%d: %-36s : 0x%016lx\n", node, interface_index, "LMCX_CTL", lmc_ctl.u);

        } /* if (bdk_is_model(OCTEONTX_CN9XXX)) */

    } /* for (interface_index = 0; interface_index < 4; ++interface_index) */

    if (measured_ddr_hertz)
	*measured_ddr_hertz = calc_ddr_hertz;

    memsize_mbytes = 0;
    for (interface_index = 0; interface_index < 4; ++interface_index) {
	if (! (ddr_config_valid_mask & (1 << interface_index))) { // if LMC has no DIMMs found
            if (ddr_interface_mask & (1 << interface_index)) { // but the LMC is present
                for (int i = 0; i < DDR_CFG_T_MAX_DIMMS; i++) {
                    // check for slot presence
                    if (validate_dimm(node, &ddr_configuration[interface_index].dimm_config_table[i]) == 0)
                        printf("N%d.LMC%d.DIMM%d: Not Present\n", node, interface_index, i);
                }
                error_print("N%d.LMC%d Configuration Completed: 0 MB\n", node, interface_index);
            }
	    continue;
        }

        /* Configure using measured value */
	retval = init_octeon_dram_interface(node, &ddr_configuration[interface_index],
					    calc_ddr_hertz, cpu_hertz, ddr_ref_hertz,
					    board_type, board_rev_maj, board_rev_min,
					    interface_index, ddr_config_valid_mask);
	if (retval > 0) {
	    memsize_mbytes += retval;
#if 1
            // do HW-assisted DLL tuning here if CN9xxx and higher speeds, and not preserving
            if (bdk_is_model(OCTEONTX_CN9XXX) &&
                (calc_ddr_hertz >= 1333333333) &&
                !ddr_memory_preserved(node))
            {
                /* do Read DLL offset tuning for this LMC */
                hw_assist_test_dll_offset(node, 2/*READ*/, interface_index, 0x0A/*ALL*/);
            }
#endif
        } else if (retval < 0) {
	    memsize_mbytes = -1;
            break; // serious problem
        }
    }

    if (memsize_mbytes <= 0)
	/* All interfaces failed to initialize, so return error */
	return -1;

    // limit memory size if desired...
    if ((s = lookup_env_parameter("limit_dram_mbytes")) != NULL) {
	unsigned int mbytes = strtoul(s, NULL, 10);
	if (mbytes > 0) {
	    memsize_mbytes = mbytes;
	    printf("Limiting DRAM size to %d MBytes based on limit_dram_mbytes env. variable\n",
		   mbytes);
	}
    }

    return memsize_mbytes;
}

