/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-l2c_tad.h"
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libdram.h"
#include "bdk-dram-init.h"

#define VREF_RANGE1_LIMIT 0x33 // range1 is valid for 0x00 - 0x32
#define VREF_RANGE2_LIMIT 0x18 // range2 is valid for 0x00 - 0x17
// full window is valid for 0x00 to 0x4A
// let 0x00 - 0x17 be range2, 0x18 - 0x4a be range 1
#define VREF_LIMIT        (VREF_RANGE1_LIMIT + VREF_RANGE2_LIMIT)
#define VREF_FINAL        (VREF_LIMIT - 1)

static const char *wl_status_strings[] = { "(e)", "   ", "   ", "(1)" };

//Overrides
void Get_SW_WLEVEL_Overrides(int ddr_interface_num,
                            dram_init_data_t *init_data,
                            dram_overrides_t *overrides)
{
    sw_wr_leveling_overrides_t *sw_wlevel_ovr = &overrides->sw_wlevel;
    const ddr_custom_config_t *custom_lmc_config = &init_data->ddr_configuration->custom_lmc_config;
    const char *s;

    sw_wlevel_ovr->sw_wlevel_enable = 1;
    if ((s = lookup_env_parameter("ddr_software_wlevel")) != NULL) {
        sw_wlevel_ovr->sw_wlevel_enable = strtoul(s, NULL, 0);
    }

    // get the config, maybe set the override; this is used only in computing the external VREF
    sw_wlevel_ovr->dram_connection = custom_lmc_config->dram_connection;
    if ((s = lookup_env_parameter("ddr%d_dram_connection", ddr_interface_num)) != NULL) {
        sw_wlevel_ovr->dram_connection = !!strtoul(s, NULL, 0);
    }

    /* Get the measured_vref setting from the config, check for an override... */
    /* NOTE: measured_vref=1 (ON) means force use of MEASURED Vref... */
    sw_wlevel_ovr->measured_vref_flag = custom_lmc_config->measured_vref;
    if ((s = lookup_env_parameter("ddr_measured_vref")) != NULL) {
        sw_wlevel_ovr->measured_vref_flag = !!strtoul(s, NULL, 0);
    }
}

void Set_Best_VREF(bdk_node_t node,
                    int ddr_interface_num,
                    dram_init_data_t *init_data,
                    sw_wr_leveling_overrides_t *sw_overrides,
                    sw_wr_data_t *sw_data,
                    int rankx,
                    int vref_value)
{
    int final_vref_value;
    int final_vref_range = 0;
    int best_vref_values_count =    sw_data->best_vref_values_count;
    int best_vref_values_start =    sw_data->best_vref_values_start;
    int computed_final_vref_value = sw_data->computed_final_vref_value;
    int measured_vref_flag =        sw_overrides->measured_vref_flag;
    int spd_lrdimm =                init_data->refs.spd_lrdimm;
    const char *s;

    if (vref_value < VREF_FINAL) {
        int vrange, vvalue;
        if (vref_value < VREF_RANGE2_LIMIT) {
            vrange = 1; vvalue = vref_value;
        }
        else {
            vrange = 0; vvalue = vref_value - VREF_RANGE2_LIMIT;
        }
        set_vref(node, ddr_interface_num, rankx,
                 vrange, vvalue);
    }
    else { /* if (vref_value < VREF_FINAL) */
        /* Print the final Vref value first. */

        /* Always print the computed first if its valid */
        if (computed_final_vref_value >= 0) {
            ddr_print("N%d.LMC%d.R%d: Vref %s Summary                 :"
                      "              %2d (0x%02x)\n",
                      node, ddr_interface_num, rankx,
                      (spd_lrdimm) ? "Provided" : "Computed",
                      computed_final_vref_value, computed_final_vref_value);
        }
        if (!measured_vref_flag) { // setup to use the computed
            best_vref_values_count = 1;
            final_vref_value = computed_final_vref_value;
        }
        else { // setup to use the measured
            if (best_vref_values_count > 0) {
                best_vref_values_count = max(best_vref_values_count, 2);
                final_vref_value = best_vref_values_start + divide_nint(best_vref_values_count - 1, 2);
                if (final_vref_value < VREF_RANGE2_LIMIT) {
                    final_vref_range = 1;
                }
                else {
                    final_vref_range = 0; final_vref_value -= VREF_RANGE2_LIMIT;
                }

                {
                    int vvlo = best_vref_values_start;
                    int vrlo;
                    if (vvlo < VREF_RANGE2_LIMIT) {
                        vrlo = 2;
                    } else {
                        vrlo = 1; vvlo -= VREF_RANGE2_LIMIT;
                    }

                    int vvhi = best_vref_values_start + best_vref_values_count - 1;
                    int vrhi;
                    if (vvhi < VREF_RANGE2_LIMIT) {
                        vrhi = 2;
                    } else {
                        vrhi = 1; vvhi -= VREF_RANGE2_LIMIT;
                    }
                    ddr_print("N%d.LMC%d.R%d: Vref Training Summary                 :"
                              "  0x%02x/%1d <----- 0x%02x/%1d -----> 0x%02x/%1d, range: %2d\n",
                              node, ddr_interface_num, rankx,
                              vvlo, vrlo,
                              final_vref_value, final_vref_range + 1,
                              vvhi, vrhi,
                              best_vref_values_count-1);
                }

            }
            else {
                /* If nothing passed use the default Vref value for this rank */
                bdk_lmcx_modereg_params2_t lmc_modereg_params2;
                lmc_modereg_params2.u = BDK_CSR_READ(node, BDK_LMCX_MODEREG_PARAMS2(ddr_interface_num));
                final_vref_value = (lmc_modereg_params2.u >> (rankx * 10 + 3)) & 0x3f;
                final_vref_range = (lmc_modereg_params2.u >> (rankx * 10 + 9)) & 0x01;

                ddr_print("N%d.LMC%d.R%d: Vref Using Default                    :"
                      "    %2d <----- %2d (0x%02x) -----> %2d, range%1d\n",
                      node, ddr_interface_num, rankx,
                                          final_vref_value, final_vref_value,
                      final_vref_value, final_vref_value, final_vref_range+1);
            }
        }

        // allow override
        if ((s = lookup_env_parameter("ddr%d_vref_value_%1d%1d",
                                      ddr_interface_num, !!(rankx&2), !!(rankx&1))) != NULL) {
            final_vref_value = strtoul(s, NULL, 0);
        }

        set_vref(node, ddr_interface_num, rankx, final_vref_range, final_vref_value);

    } /* if (vref_value < VREF_FINAL) */

    //sw_data->computed_final_vref_value =    computed_final_vref_value;
    sw_data->best_vref_values_count =       best_vref_values_count;
    sw_data->best_vref_values_start =       best_vref_values_start;
}


void Get_Delays_for_High_Order_Bits(bdk_node_t node,
                                    int ddr_interface_num,
                                    sw_wr_leveling_overrides_t *sw_overrides,
                                    sw_wr_data_t *sw_data,
                                    dram_init_data_t *init_data,
                                    int rankx)
{ // start parallel write-leveling block for delay high-order bits
    int errors = 0;
    int byte_delay[9];
    uint64_t bytemask;
    int bytes_todo;
    int byte;
    int delay;
    int interfaces;
    int measured_vref_flag =                    sw_overrides->measured_vref_flag;
    int active_rank =                           sw_data->active_rank;
    sw_wl_status_t *byte_test_status =          sw_data->byte_test_status;
    bdk_lmcx_wlevel_rankx_t *lmc_wlevel_rank =  &sw_data->lmc_wlevel_rank;
    int ddr_interface_64b =                     init_data->refs.ddr_interface_64b;
    int ddr_interface_bytemask =                init_data->refs.ddr_interface_bytemask;
    int bunk_enable =                           init_data->refs.bunk_enable;
    int pbank_lsb =                             init_data->spd.pbank_lsb;

    /* Determine address of DRAM to test for pass 1 of software write leveling. */
    interfaces = (bdk_is_model(OCTEONTX_CN8XXX)) ? sw_data->interfaces : 0;
    uint64_t rank_addr  = active_rank * (1ull << (pbank_lsb - bunk_enable + (interfaces/2)));

    VB_PRT(VBL_DEV2, "N%d.LMC%d.R%d: Active Rank %d Address: 0x%lx\n",
           node, ddr_interface_num, rankx, active_rank, rank_addr);

    bytes_todo = ddr_interface_bytemask;
    bytemask = ~0ULL; // start testing all 64-bits

    for (byte = 0; byte < 9; ++byte) {
        if (!(bytes_todo & (1 << byte))) {
            byte_delay[byte] = 0;
        }
        else {
            byte_delay[byte] = get_wlevel_rank_struct(lmc_wlevel_rank, byte);
        }
    } /* for (byte = 0; byte < 9; ++byte) */

#define WL_MIN_NO_ERRORS_COUNT 3  // FIXME? three passes without errors
    int no_errors_count = 0;

    // Change verbosity if using measured vs computed VREF
    // measured goes many times through SWL, but computed only once
    // so we want the EXHAUSTED messages at NORM for computed,
    // and at DEV2 for measured, just for completeness
    int vbl_local = (measured_vref_flag) ? VBL_DEV2 : VBL_NORM;
    uint64_t bad_bits[2];

    do {
        // write the current set of WL delays
        DRAM_CSR_WRITE(node, BDK_LMCX_WLEVEL_RANKX(ddr_interface_num, rankx), lmc_wlevel_rank->u);
        lmc_wlevel_rank->u = BDK_CSR_READ(node, BDK_LMCX_WLEVEL_RANKX(ddr_interface_num, rankx));

        //printf("%s: BDK_LMC(%d)_WLEVEL_RANK(%d): 0x%016lx\n", __func__, ddr_interface_num, rankx, lmc_wlevel_rank->u);

        bdk_watchdog_poke();

        // do the test
        errors = run_best_hw_patterns_rank(node, ddr_interface_num, rankx,
                                           DBTRAIN_TEST, bad_bits);
        errors &= bytes_todo; // keep only the ones we are still doing

        VB_PRT(VBL_DEV2, "N%d.LMC%d.R%d: S/W write-leveling TEST: returned 0x%x\n",
                           node, ddr_interface_num, rankx, errors);

        // remember, errors will not be returned for byte-lanes that have maxxed out...
        if (errors == 0) {
            no_errors_count++; // bump
            if (no_errors_count > 1) // bypass check/update completely
                continue; // to end of do-while
        }
        else
            no_errors_count = 0; // reset

        // check errors by byte
        for (byte = 0; byte < 9; ++byte) {
            if (!(bytes_todo & (1 << byte)))
                continue;

            delay = byte_delay[byte];
            if (errors & (1 << byte)) { // yes, an error in this byte lane
                debug_print("        byte %d delay %2d Errors\n", byte, delay);
                // since this byte had an error, we move to the next delay value, unless maxxed out
                delay += 8; // incr by 8 to do only delay high-order bits
                if (delay < 32) {
                    update_wlevel_rank_struct(lmc_wlevel_rank, byte, delay);
                    debug_print("        byte %d delay %2d New\n", byte, delay);
                    byte_delay[byte] = delay;
                }
                else { // reached max delay, maybe really done with this byte

                    hwl_alt_by_rank_t *hwl_alts = sw_data->hwl_alts;
                    if (!measured_vref_flag && // consider an alt only for computed VREF and
                            (hwl_alts[rankx].hwl_alt_mask & (1 << byte)))
                    { // if an alt exists...
                        int bad_delay = delay & 0x7; // just orig low-3 bits
                        delay = hwl_alts[rankx].hwl_alt_delay[byte]; // yes, use it
                        hwl_alts[rankx].hwl_alt_mask &= ~(1 << byte); // clear that flag
                        update_wlevel_rank_struct(lmc_wlevel_rank, byte, delay);
                        byte_delay[byte] = delay;
                        debug_print("        byte %d delay %2d ALTERNATE\n", byte, delay);
                        VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: SWL: Byte %d: %d FAIL, trying ALTERNATE %d\n",
                                                   node, ddr_interface_num, rankx, byte, bad_delay, delay);
                    } else {

                        unsigned bits_bad;
                        if (byte < 8) {
                            bytemask &= ~(0xffULL << (8*byte)); // test no longer, remove from byte mask
                            // If we are in 32-bit mode, duplicate the low 32-bits...
                            if (! ddr_interface_64b) {
                                bytemask &= 0x00000000ffffffffUL;
                                bytemask |= (bytemask << 32);
                            }
                            bits_bad = (unsigned)((bad_bits[0] >> (8 * byte)) & 0xffUL);
                            }
                        else {
                            bits_bad = (unsigned)(bad_bits[1] & 0xffUL);
                        }
                        bytes_todo &= ~(1 << byte); // remove from bytes to do
                        byte_test_status[byte] = WL_ESTIMATED; // make sure this is set for this case
                        debug_print("        byte %d delay %2d Exhausted\n", byte, delay);
                        VB_PRT(vbl_local, "N%d.LMC%d.R%d: SWL: Byte %d (0x%02x): delay %d EXHAUSTED \n",
                                       node, ddr_interface_num, rankx, byte, bits_bad, delay);
                    }
                }
            }
            else { // no error, stay with current delay, but keep testing it...
                debug_print("        byte %d delay %2d Passed\n", byte, delay);
                byte_test_status[byte] = WL_HARDWARE; // change status
            }
        } /* for (byte = 0; byte < 9; ++byte) */

    } while (no_errors_count < WL_MIN_NO_ERRORS_COUNT);

} // end parallel write-leveling block for delay high-order bits



/*
 * 6.9.13 DRAM Vref Training for DDR4
 *
 * This includes software write-leveling
 */
// HRM-CN9XXX 7.9.11.6

int Perform_Sofware_Write_Leveling(bdk_node_t node,
                                    int ddr_interface_num,
                                    dram_init_data_t *init_data,
                                    dram_overrides_t *overrides,
                                    hw_wr_level_data_t *hw_wl_data)
{   // Software Write-Leveling block
    /* Try to determine/optimize write-level delays experimentally. */

    Get_SW_WLEVEL_Overrides(ddr_interface_num, init_data, overrides);
    sw_wr_leveling_overrides_t *sw_overrides = &overrides->sw_wlevel;

#pragma pack(push,1)
    bdk_lmcx_wlevel_rankx_t         lmc_wlevel_rank_hw_results;

    int rank_mask =                 init_data->refs.rank_mask;
    int bunk_enable =               init_data->refs.bunk_enable;
    int num_ranks =                 init_data->refs.num_ranks;
    int spd_lrdimm =                init_data->refs.spd_lrdimm;
    int use_ecc =                   init_data->refs.use_ecc;
    int ddr_interface_mask =        init_data->refs.ddr_interface_mask;
    int ddr_interface_bytemask =    init_data->refs.ddr_interface_bytemask;
    int pbank_lsb =                 init_data->spd.pbank_lsb;
    int wlevel_bitmask_errors =     hw_wl_data->wlevel_bitmask_errors;
    int sw_wlevel_enable =          sw_overrides->sw_wlevel_enable;
    int measured_vref_flag =        sw_overrides->measured_vref_flag;

    int ddr_disable_chip_reset = 1;
    const char *s;
    int byte;
    int rankx = 0;
    int i;
    int interfaces;

    //Init sofware write data structure
    sw_wr_data_t sw_data;

#pragma pack(pop)

    //Clear data structure
    memset(&sw_data, 0, sizeof(sw_wr_data_t));
    bdk_lmcx_wlevel_rankx_t *lmc_wlevel_rank = &sw_data.lmc_wlevel_rank;

    hwl_alt_by_rank_t *hwl_alts = hw_wl_data->hwl_alts;
    sw_data.hwl_alts = hwl_alts;

    /* We need to track absolute rank number, as well as how many
    ** active ranks we have.  Two single rank DIMMs show up as
    ** ranks 0 and 2, but only 2 ranks are active. */
    int active_rank = 0;

    sw_data.interfaces =  __builtin_popcount(ddr_interface_mask);
    interfaces = (bdk_is_model(OCTEONTX_CN8XXX)) ? sw_data.interfaces : 0;

    for (rankx = 0; rankx < 4; rankx++) {
        uint64_t rank_addr;
        int vref_value; //, final_vref_value, final_vref_range = 0;
        int start_vref_value = 0; //, computed_final_vref_value = -1;
        char vref_values_count;
        char vref_values_start;

        int bytes_failed = 0;
        sw_wl_status_t byte_test_status[9];
        sw_wl_status_t sw_wl_rank_status = WL_HARDWARE;
        int sw_wl_failed = 0;

        if (!sw_wlevel_enable)
            break;

        if (!(rank_mask & (1 << rankx)))
            continue;

        sw_data.computed_final_vref_value = -1;
        sw_data.sw_wl_failed = sw_wl_failed;
        sw_data.byte_test_status = byte_test_status;

        ddr_print("N%d.LMC%d.R%d: Performing Software Write-Leveling %s\n",
                  node, ddr_interface_num, rankx, "with H/W assist");

        if (spd_lrdimm) {
            // fetch VREF as provided in SPD
            sw_data.computed_final_vref_value =
                get_lrdimm_vref(node, ddr_interface_num, rankx);
        } else if (num_ranks != 4) {
            // always compute when we can...
            sw_data.computed_final_vref_value =
                compute_vref_value(node, ddr_interface_num, rankx,
                                   init_data, overrides);
        }
        if ((sw_data.computed_final_vref_value >= 0) && !measured_vref_flag) // but only use it if allowed
            start_vref_value = VREF_FINAL; // skip all the measured Vref processing, just the final setting

        /* Save off the h/w wl results */
        lmc_wlevel_rank_hw_results.u = BDK_CSR_READ(node, BDK_LMCX_WLEVEL_RANKX(ddr_interface_num, rankx));

        vref_values_count = 0;
        vref_values_start = 0;
        //best_vref_values_count = 0;
        //best_vref_values_start = 0;

        sw_data.best_vref_values_count = 0;
        sw_data.best_vref_values_start = 0;

        /* Loop one extra time using the Final Vref value. */
        for (vref_value = start_vref_value; vref_value < VREF_LIMIT; ++vref_value) {

            Set_Best_VREF(node, ddr_interface_num, init_data, sw_overrides, &sw_data, rankx, vref_value);

            lmc_wlevel_rank->u = lmc_wlevel_rank_hw_results.u; /* Restore the saved value */

            for (byte = 0; byte < 9; ++byte)
                byte_test_status[byte] = WL_ESTIMATED;

            if (wlevel_bitmask_errors == 0) {
                Get_Delays_for_High_Order_Bits(node, ddr_interface_num, sw_overrides, &sw_data, init_data, rankx);
            } /* if (wlevel_bitmask_errors == 0) */

            bytes_failed = 0;
            for (byte = 0; byte < 9; ++byte) {
                /* Don't accumulate errors for untested bytes. */
                if (!(ddr_interface_bytemask & (1 << byte)))
                    continue;
                bytes_failed += (byte_test_status[byte] == WL_ESTIMATED);
            }

             /* Vref training loop is only used for DDR4  */

            if (bytes_failed == 0) {
                if (vref_values_count == 0) {
                    vref_values_start = vref_value;
                }
                ++vref_values_count;
                if (vref_values_count > sw_data.best_vref_values_count) {
                    sw_data.best_vref_values_count = vref_values_count;
                    sw_data.best_vref_values_start = vref_values_start;
                    debug_print("N%d.LMC%d.R%d: Vref Training                    (%2d) :    0x%02x <----- ???? -----> 0x%02x\n",
                        node, ddr_interface_num,
                        rankx, vref_value, sw_data.best_vref_values_start,
                        sw_data.best_vref_values_start + sw_data.best_vref_values_count-1);
                }
            }
            else {
                vref_values_count = 0;
                debug_print("N%d.LMC%d.R%d: Vref Training                    (%2d) :    failed\n",
                node, ddr_interface_num, rankx, vref_value);
            }
        } /* for (vref_value=0; vref_value<VREF_LIMIT; ++vref_value) */

        /* Determine address of DRAM to test for pass 2 and final test of software write leveling. */
        rank_addr  = active_rank * (1ull << (pbank_lsb - bunk_enable + (interfaces/2)));
        if (bdk_is_model(OCTEONTX_CN8XXX))
            rank_addr |= (ddr_interface_num<<7); /* Map address into proper interface */
        rank_addr = bdk_numa_get_address(node, rank_addr);
        debug_print("N%d.LMC%d.R%d: Active Rank %d Address: 0x%lx\n",
            node, ddr_interface_num, rankx, active_rank, rank_addr);

        int errors;

        if (bytes_failed) {
            // FIXME? the big hammer, assume only LMC restart or chip reset will help
            ddr_print("N%d.LMC%d.R%d: S/W write-leveling pass 1 failed\n",
                  node, ddr_interface_num, rankx);
            sw_wl_failed = 1;
        }
        else { /* if (bytes_failed) */

            // SW WL pass 1 was OK, write the settings
            DRAM_CSR_WRITE(node, BDK_LMCX_WLEVEL_RANKX(ddr_interface_num, rankx), lmc_wlevel_rank->u);
            lmc_wlevel_rank->u = BDK_CSR_READ(node, BDK_LMCX_WLEVEL_RANKX(ddr_interface_num, rankx));

            // do validity check on the delay values by running the test 1 more time...
            // FIXME: we really need to check the ECC byte setting here as well,
            //        so we need to enable ECC for this test!!!
            // if there are any errors, claim SW WL failure

            // do the test
            errors = run_best_hw_patterns_rank(node, ddr_interface_num, rankx,
                                                       DBTRAIN_TEST, NULL);
            errors &= ddr_interface_bytemask;

            if (errors) {
                ddr_print("N%d.LMC%d.R%d: Wlevel Rank Final Test errors 0x%03x\n",
                          node, ddr_interface_num, rankx, errors);
                sw_wl_failed = 1;
            }
        } /* if (bytes_failed) */

        // FIXME? dump the WL settings, so we get more of a clue as to what happened where
        if (dram_is_verbose(VBL_NORM)) {
            printf("N%d.LMC%d.R%d: Wlevel Rank 0x%x, 0x%016lX  : ",
                   node, ddr_interface_num, rankx,
                   lmc_wlevel_rank->s.status, lmc_wlevel_rank->u);
            for (int i = 7+use_ecc; i >= 0; i--) {
                printf(" %2d%3s", get_wlevel_rank_struct(lmc_wlevel_rank, i),
                       wl_status_strings[byte_test_status[i]]);
            }
            printf(" %s\n", (sw_wl_rank_status == WL_HARDWARE) ? "" : "(s)");
        }

        // finally, check for fatal conditions: either chip reset right here, or return error flag
        if (((sw_data.best_vref_values_count == 0)) || sw_wl_failed) {
            if (!ddr_disable_chip_reset) { // do chip RESET
                error_print("N%d.LMC%d.R%d: INFO: Short memory test indicates a retry is needed. Resetting node...\n",
                            node, ddr_interface_num, rankx);
                bdk_wait_usec(500000);
                bdk_reset_chip(node);
            }
            else { // return error flag so LMC init can be retried...
                ddr_print("N%d.LMC%d.R%d: INFO: Short memory test indicates a retry is needed. Restarting LMC init...\n",
                          node, ddr_interface_num, rankx);
                return 0; // 0 indicates restart possible...
            }
        }

        active_rank++;
        sw_data.active_rank = active_rank;
    } /* for (rankx = 0; rankx < 4; rankx++) */

    // Finalize the write-leveling settings
    for (rankx = 0; rankx < 4;rankx++) {
        uint64_t value;
        int parameter_set = 0;
        if (!(rank_mask & (1 << rankx)))
            continue;

        lmc_wlevel_rank->u = BDK_CSR_READ(node, BDK_LMCX_WLEVEL_RANKX(ddr_interface_num, rankx));

        if (bdk_is_platform(BDK_PLATFORM_ASIM)) {
            parameter_set |= 1;
            lmc_wlevel_rank->u = 0;
        }

        for (i = 0; i < 9; ++i) {
            if ((s = lookup_env_parameter("ddr%d_wlevel_rank%d_byte%d", ddr_interface_num, rankx, i)) != NULL) {
                parameter_set |= 1;
                value = strtoul(s, NULL, 0);
                update_wlevel_rank_struct(lmc_wlevel_rank, i, value);
            }
        }

        if ((s = lookup_env_parameter_ull("ddr%d_wlevel_rank%d", ddr_interface_num, rankx)) != NULL) {
            parameter_set |= 1;
            value = strtoull(s, NULL, 0);
            lmc_wlevel_rank->u = value;
        }

        if (parameter_set) {
            DRAM_CSR_WRITE(node, BDK_LMCX_WLEVEL_RANKX(ddr_interface_num, rankx), lmc_wlevel_rank->u);
            lmc_wlevel_rank->u = BDK_CSR_READ(node, BDK_LMCX_WLEVEL_RANKX(ddr_interface_num, rankx));
            display_WL(node, ddr_interface_num, *lmc_wlevel_rank, rankx);
        }

        // HRM-CN9XXX 7.9.11.7
        // fill any unused (unpopulated) WLEVEL_RANKX CSRs
        if ((rank_mask & 0x0F) != 0x0F) { // if there are unused entries to be filled
            const uint8_t urm[3][4] = { [0]={0x0e, 0, 0, 0}, [1]={4, 8, 0, 0}, [2]={2, 0, 8, 0} };
            int msk = urm[rank_mask >> 1][rankx];
            for (int rx = 1; rx < 4; rx++) {
                if (msk & (1 << rx)) {
                    VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: writing WLEVEL_RANK unused entry R%d.\n",
                          node, ddr_interface_num, rankx, rx);
                    DRAM_CSR_WRITE(node, BDK_LMCX_WLEVEL_RANKX(ddr_interface_num, rx), lmc_wlevel_rank->u);
                }
            }
        }

    } /* for (rankx = 0; rankx < 4;rankx++) */

    return 1;
} // End Software Write-Leveling block
