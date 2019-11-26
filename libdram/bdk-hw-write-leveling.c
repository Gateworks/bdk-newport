/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libdram.h"

#include "bdk-dram-init.h"

#define WLOOP_RETRIES_DEFAULT 5

#define WLEVEL_BYTE_BITS 5
#define WLEVEL_BYTE_MSK  ((1UL << 5) - 1)

void
update_wlevel_rank_struct(bdk_lmcx_wlevel_rankx_t *lmc_wlevel_rank,
                          int byte, int delay)
{
    bdk_lmcx_wlevel_rankx_t temp_wlevel_rank;
    if (byte >= 0 && byte <= 8) {
	temp_wlevel_rank.u = lmc_wlevel_rank->u;
	temp_wlevel_rank.u &= ~(WLEVEL_BYTE_MSK << (WLEVEL_BYTE_BITS * byte));
	temp_wlevel_rank.u |= ((delay & WLEVEL_BYTE_MSK) << (WLEVEL_BYTE_BITS * byte));
	lmc_wlevel_rank->u = temp_wlevel_rank.u;
    }
}

int
get_wlevel_rank_struct(bdk_lmcx_wlevel_rankx_t *lmc_wlevel_rank, int byte)
{
    int delay = 0;
    if (byte >= 0 && byte <= 8) {
	delay = ((lmc_wlevel_rank->u) >> (WLEVEL_BYTE_BITS * byte)) & WLEVEL_BYTE_MSK;
    }
    return delay;
}

void Get_HW_WR_Leveling_Overrides(dram_init_data_t *init_data,
                                  dram_overrides_t *overrides)
{
    const char *s;
    int dram_width =                        init_data->refs.dram_width;
    int disable_sequential_delay_check =    overrides->init.disable_sequential_delay_check;
    hw_wr_leveling_overrides_t *hw_wr_leveling_overrides = &overrides->hw_wlevel;

    hw_wr_leveling_overrides->ddr_wlevel_roundup = 0;
    if ((s = lookup_env_parameter("ddr_wlevel_roundup")) != NULL) {
        hw_wr_leveling_overrides->ddr_wlevel_roundup = strtoul(s, NULL, 0);
    }

    hw_wr_leveling_overrides->ddr_wlevel_printall = (dram_is_verbose(VBL_DEV2)); // FIXME?
    if ((s = lookup_env_parameter("ddr_wlevel_printall")) != NULL) {
        hw_wr_leveling_overrides->ddr_wlevel_printall = strtoul(s, NULL, 0);
    }

    // default T8X to disable when RL sequential delay check is disabled
    // FIXME? disable validity checking on CN9XXX initially
    hw_wr_leveling_overrides->disable_hwl_validity =
        CN8_OR_CN9(disable_sequential_delay_check, 1);
    if ((s = lookup_env_parameter("ddr_disable_hwl_validity")) != NULL) {
        hw_wr_leveling_overrides->disable_hwl_validity = !!strtoul(s, NULL, 0);
    }

    hw_wr_leveling_overrides->default_wlevel_rtt_nom = ddr4_rttnom_40ohm;
    if ((s = lookup_env_parameter("ddr_wlevel_rtt_nom")) != NULL) {
        hw_wr_leveling_overrides->default_wlevel_rtt_nom = strtoul(s, NULL, 0);
    }

    if (bdk_is_model(OCTEONTX_CN8XXX)) { // only CN8XXX has the CSR field for this
        if ((s = lookup_env_parameter("ddr_match_wlevel_rtt_nom")) != NULL) {
            hw_wr_leveling_overrides->match_wlevel_rtt_nom = !!strtoul(s, NULL, 0);
        }
    }

    // allow overrides of OR_DIS and BITMASK in WLEVEL_CTL CSR
    hw_wr_leveling_overrides->ddr_wlevel_ctl_or_dis = 1;
    if ((s = lookup_env_parameter("ddr_wlevel_ctl_or_dis")) != NULL) {
        hw_wr_leveling_overrides->ddr_wlevel_ctl_or_dis = !!strtoul(s, NULL, 0);
    }
    int default_bitmask = (dram_width == 4) ? 0x0F : 0xFF;
    hw_wr_leveling_overrides->ddr_wlevel_ctl_bitmask = default_bitmask;
    if ((s = lookup_env_parameter("ddr_wlevel_ctl_bitmask")) != NULL) {
        hw_wr_leveling_overrides->ddr_wlevel_ctl_bitmask = strtoul(s, NULL, 0);
    }
}

/*
// entry = 1 is valid, entry = 0 is invalid
static int
validity_matrix[4][4] = {[0] {1,1,1,0},  // valid pairs when cv == 0: 0,0 + 0,1 + 0,2 == "7"
			 [1] {0,1,1,1},  // valid pairs when cv == 1: 1,1 + 1,2 + 1,3 == "E"
			 [2] {1,0,1,1},  // valid pairs when cv == 2: 2,2 + 2,3 + 2,0 == "D"
			 [3] {1,1,0,1}}; // valid pairs when cv == 3: 3,3 + 3,0 + 3,1 == "B"
*/

static int validate_seq(int *wl, int *seq)
{
    int seqx; // sequence index, step through the sequence array
    int bitnum;
    seqx = 0;
    while (seq[seqx+1] >= 0) { // stop on next seq entry == -1
	// but now, check current versus next
        /*
          ORIGINAL CODE:
          if ( !validity_matrix [wl[seq[seqx]]] [wl[seq[seqx+1]]] )
              return 1;
        */
	bitnum = (wl[seq[seqx]] << 2) | wl[seq[seqx+1]];
	if (!((1 << bitnum) & 0xBDE7)) // magic validity number (see matrix above)
	    return 1;

	seqx++;
    }
    return 0;
}

static int Validate_HW_WL_Settings(bdk_node_t node,
                                    int ddr_interface_num,
                                    bdk_lmcx_wlevel_rankx_t *lmc_wlevel_rank,
                                    int ecc_ena)
{
    int wl[9], byte, errors;

    // arrange the sequences for the DIMM geometries
    int useq[] = { 0,1,2,3,8,4,5,6,7,-1 }; // UDIMM: index 0 has byte 0, etc, ECC in middle
    int rseq1[] = { 8,3,2,1,0,-1 }; // RDIMM: index 0 is ECC, then go down
    int rseq2[] = { 4,5,6,7,-1 }; // RDIMM: index 0 has byte 4, then go up
    int useqno[] = { 0,1,2,3,4,5,6,7,-1 }; // UDIMM: index 0 has byte 0, etc, no ECC
    int rseq1no[] = { 3,2,1,0,-1 }; // RDIMM: index 0 is byte 3, then go down, no ECC

    // in the CSR, bytes 0-7 are always data, byte 8 is ECC
    for (byte = 0; byte < 8+ecc_ena; byte++) {
        wl[byte] = (get_wlevel_rank_struct(lmc_wlevel_rank, byte) >> 1) & 3; // preprocess :-)
    }

    errors = 0;
    if (__bdk_dram_is_rdimm(node, 0) != 0) { // RDIMM order
        errors  = validate_seq(wl, (ecc_ena) ? rseq1 : rseq1no);
        errors += validate_seq(wl, rseq2);
    }
    else { // UDIMM order
        errors  = validate_seq(wl, (ecc_ena) ? useq : useqno);
    }

    return errors;
}


static uint64_t octeontx_read_wlevel_dbg(bdk_node_t node, int ddr_interface_num, int byte)
{
    bdk_lmcx_wlevel_dbg_t wlevel_dbg;

    wlevel_dbg.u = 0;
    wlevel_dbg.s.byte = byte;

    DRAM_CSR_WRITE(node, BDK_LMCX_WLEVEL_DBG(ddr_interface_num), wlevel_dbg.u);
    BDK_CSR_READ(node, BDK_LMCX_WLEVEL_DBG(ddr_interface_num));

    wlevel_dbg.u = BDK_CSR_READ(node, BDK_LMCX_WLEVEL_DBG(ddr_interface_num));
    return wlevel_dbg.s.bitmask;
}

// HRM-CN9XXX 7.9.11
static void
Perform_Write_Leveling_on_Rank(bdk_node_t node,
                               int ddr_interface_num,
                               dram_init_data_t *init_data,
                               hw_wr_level_data_t *hw_wr_level_data,
                               int rankx)
{
    int ecc_ena =                               init_data->refs.use_ecc;
    int ddr_interface_bytemask =                init_data->refs.ddr_interface_bytemask;
    bdk_lmcx_wlevel_ctl_t *wlevel_ctl =         &hw_wr_level_data->wlevel_ctl;
    bdk_lmcx_wlevel_rankx_t *lmc_wlevel_rank =  &hw_wr_level_data->lmc_wlevel_rank;
    int *wlevel_bitmask =                       hw_wr_level_data->wlevel_bitmask;
    int wlevel_bitmask_errors = 0;
    int byte_idx;

    // HRM-CN9XXX 7.9.11.1
    // FIXME: nothing?

    // HRM-CN9XXX 7.9.11.2
    /* Clear write-level delays */
    DRAM_CSR_WRITE(node, BDK_LMCX_WLEVEL_RANKX(ddr_interface_num, rankx), 0UL);

#if HWL_BY_BYTE // FIXME???

    /* Make a separate pass for each byte to reduce power. */
    for (byte_idx = 0; byte_idx < (8+ecc_ena); ++byte_idx) {

        if (!(ddr_interface_bytemask & (1 << byte_idx)))
            continue;

        wlevel_ctl->s.lanemask = (1<<byte_idx);

        DRAM_CSR_WRITE(node, BDK_LMCX_WLEVEL_CTL(ddr_interface_num), wlevel_ctl->u);

        /* Read and write values back in order to update the
           status field. This insures that we read the updated
           values after write-leveling has completed. */
        DRAM_CSR_WRITE(node, BDK_LMCX_WLEVEL_RANKX(ddr_interface_num, rankx),
               BDK_CSR_READ(node, BDK_LMCX_WLEVEL_RANKX(ddr_interface_num, rankx)));

        perform_octeontx_ddr_sequence(node, (1 << rankx), ddr_interface_num, 6); /* write-leveling */

        if (!bdk_is_platform(BDK_PLATFORM_ASIM) &&
                BDK_CSR_WAIT_FOR_FIELD(node, BDK_LMCX_WLEVEL_RANKX(ddr_interface_num, rankx), status, ==, 3, 1000000))
        {
            error_print("ERROR: Timeout waiting for WLEVEL\n");
        }
        lmc_wlevel_rank->u = BDK_CSR_READ(node, BDK_LMCX_WLEVEL_RANKX(ddr_interface_num, rankx));

        wlevel_bitmask[byte_idx] = octeontx_read_wlevel_dbg(node, ddr_interface_num, byte_idx);
        if (wlevel_bitmask[byte_idx] == 0)
            ++wlevel_bitmask_errors;
    } /* for (byte_idx=0; byte_idx<(8+ecc_ena); ++byte_idx) */

    wlevel_ctl->s.lanemask = /*0x1ff*/ddr_interface_bytemask; // restore for RL
    DRAM_CSR_WRITE(node, BDK_LMCX_WLEVEL_CTL(ddr_interface_num), wlevel_ctl->u);

#else /* HWL_BY_BYTE */

    // HRM-CN9XXX 7.9.11.3
    // do all the byte-lanes at the same time
    wlevel_ctl->s.lanemask = /*0x1ff*/ddr_interface_bytemask; // FIXME?
    DRAM_CSR_WRITE(node, BDK_LMCX_WLEVEL_CTL(ddr_interface_num), wlevel_ctl->u);

    /* Read and write values back in order to update the
       status field. This insures that we read the updated
       values after write-leveling has completed. */
    DRAM_CSR_WRITE(node, BDK_LMCX_WLEVEL_RANKX(ddr_interface_num, rankx),
               BDK_CSR_READ(node, BDK_LMCX_WLEVEL_RANKX(ddr_interface_num, rankx)));

    // HRM-CN9XXX 7.9.11.4
    perform_octeontx_ddr_sequence(node, (1 << rankx), ddr_interface_num, 6); /* write-leveling */

    // HRM-CN9XXX 7.9.11.5
    if (!bdk_is_platform(BDK_PLATFORM_ASIM) &&
        BDK_CSR_WAIT_FOR_FIELD(node, BDK_LMCX_WLEVEL_RANKX(ddr_interface_num, rankx),
                   status, ==, 3, 1000000))
    {
        error_print("ERROR: Timeout waiting for WLEVEL\n");
    }

    lmc_wlevel_rank->u = BDK_CSR_READ(node, BDK_LMCX_WLEVEL_RANKX(ddr_interface_num, rankx));

    for (byte_idx = 0; byte_idx < (8+ecc_ena); ++byte_idx) {
        if (!(ddr_interface_bytemask & (1 << byte_idx)))
            continue;

        wlevel_bitmask[byte_idx] = octeontx_read_wlevel_dbg(node, ddr_interface_num, byte_idx);
        if (wlevel_bitmask[byte_idx] == 0)
            ++wlevel_bitmask_errors;
    } /* for (byte_idx=0; byte_idx<(8+ecc_ena); ++byte_idx) */

#endif /* HWL_BY_BYTE */

    hw_wr_level_data->wlevel_bitmask_errors = wlevel_bitmask_errors;
}


static int roundup_wlevel_bitmask(int bitmask)
{
    int shifted_bitmask;
    int leader;
    int delay;

    for (leader = 0; leader < 8; ++leader) {
	shifted_bitmask = (bitmask >> leader);
	if ((shifted_bitmask & 1) == 0)
	    break;
    }

    for (/*leader=leader*/; leader < 16; ++leader) {
	shifted_bitmask = (bitmask >> (leader % 8));
	if (shifted_bitmask & 1)
	    break;
    }

    delay = (leader & 1) ? leader + 1 : leader;
    delay = delay % 8;

    return delay;
}

static int
find_WL_majority(wlevel_bitcnt_t *bc, int *msk, int *cnt, int *tie)
{
    int ix, num, ret;

    *msk = 0; // was: mc
    *cnt = 0; // was: xc
    *tie = -1; // was: tc
    ret = -1;

    for (ix = 0; ix < 8; ix++) {
        num = bc->bitcnt[ix];
        if (num > 0) { // only process positive counts
            // make a bitmask of all the indices with any count
            *msk |= (1 << ix);

            // find the max count; for ties, this will be the first max
            if (num > *cnt) { // new max?
                *cnt = num; // change max
                *tie = -1; // indicate no tie
                ret = ix; // change the index
            }
            else if (num == *cnt) {
                // its a tie, switch max to new, unless...
                if ((ix == 7) && (ret == 0)) { // leave ret 0
                    *tie = ix; // tie is new max
                } else {
                    *tie = ret; // tie is first max
                    ret = ix; // ret is new max
                }
            }
        }
    }
    return ret;
}

unsigned int EXTR_DQS1_ADJ(uint64_t u, int x)
{
    return (unsigned int)((u >> (x*3+27)) & 0x7UL);
}

void INSRT_DQS1_ADJ(uint64_t *up, int x, int v)
{
    uint64_t u = *up;

    u &= ~((0x7UL) << (x*3+27));
    *up = (u | ((v & 0x7UL) << (x*3+27)));
    return;
}

static void
Find_Majority_WR_Level_Settings(bdk_node_t node,
                                int ddr_interface_num,
                                dram_init_data_t *init_data,
                                dram_overrides_t *overrides,
                                hw_wr_level_data_t *hw_wr_level_data,
                                int rankx,
                                int byte_idx)
{
    bdk_lmcx_wlevel_rankx_t *lmc_wlevel_rank = &hw_wr_level_data->lmc_wlevel_rank;
    int idx, pidx;
    int mskbits;
    int  msk,  cnt,  tie;
    int pmsk, pcnt, ptie;
    //int ecc_ena =            init_data->refs.use_ecc;
    int dram_width =            init_data->refs.dram_width;
    int enable_x4_hwl_adj =     overrides->init.enable_x4_hwl_adj;

    // If selected, record instances when to adjust DQS1 to "even out" x4 HWL
    if ((dram_width == 4) && enable_x4_hwl_adj) {
        int pidx0, pidx1;
        int idx0, idx1;

        // PBMs first
        pidx0 = find_WL_majority(&hw_wr_level_data->wlevel_bytes_pbm[0].bytecnt[byte_idx], &msk, &cnt, &tie);
        pidx1 = find_WL_majority(&hw_wr_level_data->wlevel_bytes_pbm[1].bytecnt[byte_idx], &pmsk, &pcnt, &ptie);
        VB_PRT(VBL_DEV2, "N%d.LMC%d.R%d: Byte %d: HWLX4: Pmaj0=%d, Pmaj1=%d\n",
               node, ddr_interface_num, rankx, byte_idx, pidx0, pidx1);
        // IBMs next
        idx0 = find_WL_majority(&hw_wr_level_data->wlevel_bytes[0].bytecnt[byte_idx], &msk, &cnt, &tie);
        idx1 = find_WL_majority(&hw_wr_level_data->wlevel_bytes[1].bytecnt[byte_idx], &pmsk, &pcnt, &ptie);
        VB_PRT(VBL_DEV2, "N%d.LMC%d.R%d: Byte %d: HWLX4: Imaj0=%d, Imaj1=%d\n",
               node, ddr_interface_num, rankx, byte_idx, idx0, idx1);

        // no PBMs, take IBMs
        if (pidx0 < 0) pidx0 = idx0;
        if (pidx1 < 0) pidx1 = idx1;

        // FIXME: what to do if either is (-1)?

        if ((pidx0 < 0) || (pidx1 < 0)) {
            VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: Byte %d: HWLX4: (maj0=%d) (maj1=%d): ERROR\n",
                   node, ddr_interface_num, rankx, byte_idx, pidx0, pidx1);
        } else {
            int dir = (pidx0 > pidx1) ? 1 : ((pidx0 < pidx1) ? -1 : 0);
            if ((pidx0 == 7) && (pidx1 == 0))
                dir = -dir;

            if (dir > 0)
                hw_wr_level_data->hwl_dqs1[rankx].dqs1_mask_up |= (1 << byte_idx); // set the mask
            else if (dir < 0)
                hw_wr_level_data->hwl_dqs1[rankx].dqs1_mask_dn |= (1 << byte_idx); // set the mask

            if (dir != 0) {
                VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: Byte %d: HWLX4: (maj0 %d) vs (maj1 %d): %s %s\n",
                       node, ddr_interface_num, rankx, byte_idx, pidx0, pidx1,
                       (pidx0 != pidx1) ? "ADJUST" : "IGNORE", (dir > 0) ? "UP" : ((dir < 0) ? "DOWN" : ""));
            }
        }
    } /* if ((dram_width == 4) && enable_x4_hwl_adj) */

    idx  = find_WL_majority(&hw_wr_level_data->wlevel_bytes[2].bytecnt[byte_idx], &msk, &cnt, &tie);
    pidx = find_WL_majority(&hw_wr_level_data->wlevel_bytes_pbm[2].bytecnt[byte_idx], &pmsk, &pcnt, &ptie);

    mskbits = (msk | pmsk);

    if (__builtin_popcount(mskbits) == 3) { // check for 3 candidates exactly
        switch (mskbits & 0xFF) { // pick the middle bit
        case 0xC1: idx = 7; break;
        case 0x83: idx = 0; break;
        default: idx = __builtin_ffs(mskbits); break;
        }
        msk = (1 << idx); // reset to no ALTs
        VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: Byte %d: HWL TRIPLE (0x%x): choosing %d",
               node, ddr_interface_num, rankx, byte_idx, mskbits, idx);
    } // else look at PBMs
    else if (pidx >= 0) { // there was at least 1 PBM

        VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: Byte %d: HWL PBM maj %d(%2d): ",
               node, ddr_interface_num, rankx, byte_idx, pidx, pcnt);
        if (idx >= 0)
            VB_PRT(VBL_DEV, "IBM maj %d(%2d): ", idx, cnt);

        // FIXME: leave for debugging, delete when not needed ;-}
        if (ptie >= 0) {
            VB_PRT(VBL_DEV, "PBM TIED %d with %d: ", pidx, ptie);
        }
        if (tie >= 0) {
            VB_PRT(VBL_DEV, "IBM TIED %d with %d: ", idx, tie);
        }

        // if there was NO PBM tie, or both PBM/IBM tied
        if (!(ptie >= 0) || ((ptie >= 0) && (tie >= 0))) {

            idx = pidx; // use PBM index
            cnt = pcnt; // and its count
            // leave the IBM mask
            VB_PRT(VBL_DEV, "PBM choose pmaj: ");

        } else { // PBM tie and no IBM tie

            if (idx < 0) { // no IBM maj, use all PBM
                VB_PRT(VBL_DEV, "no IBM maj: ");
                idx = pidx;
                msk = pmsk;
                cnt = pcnt;
            }
            else if (pidx != idx) { // see if PBM tied maj is not same as non-tied IBM maj
                // switching to PBM ALT, leave their index and count untouched
                pidx = ptie; // set PBM alt index
                VB_PRT(VBL_DEV, "switch to PBM alt %d: ", pidx);

            } else {
                VB_PRT(VBL_DEV, "PBM maj == IBM maj: ");
            }
        }

        // look for ALT with PBMs; use PBMs mask else leave mask from IBM
        if (pmsk & ~(1 << pidx)) {
            msk = pmsk;
            VB_PRT(VBL_DEV, "found PBM alt: ");
        } else {
            if (msk & ~(1 << pidx)) // check IBM for ALT possible
                VB_PRT(VBL_DEV, "using IBM alt: ");
        }
        VB_PRT(VBL_DEV, "USING pmaj %d(%d)", pidx, pcnt);

    } else { // no PBMs, just use IBM majority/alternate
        VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: Byte %d: HWL ZERO PBMs, using IBM maj %d(%d)",
               node, ddr_interface_num, rankx, byte_idx, idx, cnt);
    }

    // see if there was an alternate
    int alts = (msk & ~(1 << idx)); // take out the majority choice
    if (alts != 0) {
        for (int i = 0; i < 8; i++) {
            if (alts & (1 << i)) { // FIXME: could be done multiple times? bad if so
                hw_wr_level_data->hwl_alts[rankx].hwl_alt_mask |= (1 << byte_idx); // set the mask
                hw_wr_level_data->hwl_alts[rankx].hwl_alt_delay[byte_idx] = i; // record the value
                VB_PRT(VBL_DEV, ": ALT %d", i);
            }
        }
    }

    VB_PRT(VBL_DEV, "\n");

    // finally, update the byte-lane...
    update_wlevel_rank_struct(lmc_wlevel_rank, byte_idx, idx);
}

    /*
     * 6.9.11 LMC Write Leveling
     *
     * LMC supports an automatic write leveling like that described in the
     * JEDEC DDR3 specifications separately per byte-lane.
     *
     * All of DDR PLL, LMC CK, LMC DRESET, and early LMC initializations must
     * be completed prior to starting this LMC write-leveling sequence.
     *
     * There are many possible procedures that will write-level all the
     * attached DDR3 DRAM parts. One possibility is for software to simply
     * write the desired values into LMC(0)_WLEVEL_RANK(0..3). This section
     * describes one possible sequence that uses LMC's autowrite-leveling
     * capabilities.
     *
     * 1. If the DQS/DQ delays on the board may be more than the ADD/CMD
     *    delays, then ensure that LMC(0)_CONFIG[EARLY_DQX] is set at this
     *    point.
     *
     * Do the remaining steps 2-7 separately for each rank i with attached
     * DRAM.
     *
     * 2. Write LMC(0)_WLEVEL_RANKi = 0.
     *
     * 3. For ×8 parts:
     *
     *    Without changing any other fields in LMC(0)_WLEVEL_CTL, write
     *    LMC(0)_WLEVEL_CTL[LANEMASK] to select all byte lanes with attached
     *    DRAM.
     *
     *    For ×16 parts:
     *
     *    Without changing any other fields in LMC(0)_WLEVEL_CTL, write
     *    LMC(0)_WLEVEL_CTL[LANEMASK] to select all even byte lanes with
     *    attached DRAM.
     *
     * 4. Without changing any other fields in LMC(0)_CONFIG,
     *
     *    o write LMC(0)_SEQ_CTL[SEQ_SEL] to select write-leveling
     *
     *    o write LMC(0)_CONFIG[RANKMASK] = (1 << i)
     *
     *    o write LMC(0)_SEQ_CTL[INIT_START] = 1
     *
     *    LMC will initiate write-leveling at this point. Assuming
     *    LMC(0)_WLEVEL_CTL [SSET] = 0, LMC first enables write-leveling on
     *    the selected DRAM rank via a DDR3 MR1 write, then sequences through
     *    and accumulates write-leveling results for eight different delay
     *    settings twice, starting at a delay of zero in this case since
     *    LMC(0)_WLEVEL_RANKi[BYTE*<4:3>] = 0, increasing by 1/8 CK each
     *    setting, covering a total distance of one CK, then disables the
     *    write-leveling via another DDR3 MR1 write.
     *
     *    After the sequence through 16 delay settings is complete:
     *
     *    o LMC sets LMC(0)_WLEVEL_RANKi[STATUS] = 3
     *
     *    o LMC sets LMC(0)_WLEVEL_RANKi[BYTE*<2:0>] (for all ranks selected
     *      by LMC(0)_WLEVEL_CTL[LANEMASK]) to indicate the first write
     *      leveling result of 1 that followed result of 0 during the
     *      sequence, except that the LMC always writes
     *      LMC(0)_WLEVEL_RANKi[BYTE*<0>]=0.
     *
     *    o Software can read the eight write-leveling results from the first
     *      pass through the delay settings by reading
     *      LMC(0)_WLEVEL_DBG[BITMASK] (after writing
     *      LMC(0)_WLEVEL_DBG[BYTE]). (LMC does not retain the writeleveling
     *      results from the second pass through the eight delay
     *      settings. They should often be identical to the
     *      LMC(0)_WLEVEL_DBG[BITMASK] results, though.)
     *
     * 5. Wait until LMC(0)_WLEVEL_RANKi[STATUS] != 2.
     *
     *    LMC will have updated LMC(0)_WLEVEL_RANKi[BYTE*<2:0>] for all byte
     *    lanes selected by LMC(0)_WLEVEL_CTL[LANEMASK] at this point.
     *    LMC(0)_WLEVEL_RANKi[BYTE*<4:3>] will still be the value that
     *    software wrote in substep 2 above, which is 0.
     *
     * 6. For ×16 parts:
     *
     *    Without changing any other fields in LMC(0)_WLEVEL_CTL, write
     *    LMC(0)_WLEVEL_CTL[LANEMASK] to select all odd byte lanes with
     *    attached DRAM.
     *
     *    Repeat substeps 4 and 5 with this new LMC(0)_WLEVEL_CTL[LANEMASK]
     *    setting. Skip to substep 7 if this has already been done.
     *
     *    For ×8 parts:
     *
     *    Skip this substep. Go to substep 7.
     *
     * 7. Calculate LMC(0)_WLEVEL_RANKi[BYTE*<4:3>] settings for all byte
     *    lanes on all ranks with attached DRAM.
     *
     *    At this point, all byte lanes on rank i with attached DRAM should
     *    have been write-leveled, and LMC(0)_WLEVEL_RANKi[BYTE*<2:0>] has
     *    the result for each byte lane.
     *
     *    But note that the DDR3 write-leveling sequence will only determine
     *    the delay modulo the CK cycle time, and cannot determine how many
     *    additional CK cycles of delay are present. Software must calculate
     *    the number of CK cycles, or equivalently, the
     *    LMC(0)_WLEVEL_RANKi[BYTE*<4:3>] settings.
     *
     *    This BYTE*<4:3> calculation is system/board specific.
     *
     * Many techniques can be used to calculate write-leveling BYTE*<4:3> values,
     * including:
     *
     *    o Known values for some byte lanes.
     *
     *    o Relative values for some byte lanes relative to others.
     *
     *    For example, suppose lane X is likely to require a larger
     *    write-leveling delay than lane Y. A BYTEX<2:0> value that is much
     *    smaller than the BYTEY<2:0> value may then indicate that the
     *    required lane X delay wrapped into the next CK, so BYTEX<4:3>
     *    should be set to BYTEY<4:3>+1.
     *
     *    When ECC DRAM is not present (i.e. when DRAM is not attached to the
     *    DDR_CBS_0_* and DDR_CB<7:0> chip signals, or the DDR_DQS_<4>_* and
     *    DDR_DQ<35:32> chip signals), write LMC(0)_WLEVEL_RANK*[BYTE8] =
     *    LMC(0)_WLEVEL_RANK*[BYTE0], using the final calculated BYTE0 value.
     *    Write LMC(0)_WLEVEL_RANK*[BYTE4] = LMC(0)_WLEVEL_RANK*[BYTE0],
     *    using the final calculated BYTE0 value.
     *
     * 8. Initialize LMC(0)_WLEVEL_RANK* values for all unused ranks.
     *
     *    Let rank i be a rank with attached DRAM.
     *
     *    For all ranks j that do not have attached DRAM, set
     *    LMC(0)_WLEVEL_RANKj = LMC(0)_WLEVEL_RANKi.
     */


void Run_HW_Write_Leveling(bdk_node_t node,
                            int ddr_interface_num,
                            dram_init_data_t *init_data,
                            dram_overrides_t *overrides,
                            hw_wr_level_data_t *hw_wr_level_data)
{
    // Start HW write-leveling block

    //Configure Overrides
    Get_HW_WR_Leveling_Overrides(init_data, overrides);
    hw_wr_leveling_overrides_t *hw_wr_leveling_overrides = &overrides->hw_wlevel;

#pragma pack(push,1)

    bdk_lmcx_modereg_params1_t modereg_params1;
    int wlevel_loops =                      init_data->refs.wlevel_loops;
    int rank_mask =                         init_data->refs.rank_mask;
    int ddr_interface_bytemask =            init_data->refs.ddr_interface_bytemask;
    int ddr_interface_64b =                 init_data->refs.ddr_interface_64b;
    int dram_width =                        init_data->refs.dram_width;
    int ecc_ena =                           init_data->refs.use_ecc;
    int spd_rawcard_AorB =                  init_data->spd.spd_rawcard_AorB;
    int spd_dimm_type =                     init_data->refs.spd_dimm_type;
    int spd_rdimm =                         init_data->refs.spd_rdimm;
    impedence_values_t *imp_values =        init_data->imp_values;

    //overrides
    int disable_deskew_training =           overrides->init.disable_deskew_training;
    int enable_x4_hwl_adj =                 overrides->init.enable_x4_hwl_adj;

    int ddr_wlevel_roundup =                hw_wr_leveling_overrides->ddr_wlevel_roundup;
    int ddr_wlevel_printall =               hw_wr_leveling_overrides->ddr_wlevel_printall;

    // default to disable when RL sequential delay check is disabled
    int disable_hwl_validity =              hw_wr_leveling_overrides->disable_hwl_validity;
    int match_wlevel_rtt_nom =              hw_wr_leveling_overrides->match_wlevel_rtt_nom;
    int default_wlevel_rtt_nom =            hw_wr_leveling_overrides->default_wlevel_rtt_nom;

    int rankx = 0;
    int byte_idx;
    int wlevel_bitmask_errors = 0;

    int *wlevel_bitmask =                       hw_wr_level_data->wlevel_bitmask;
    bdk_lmcx_wlevel_rankx_t *lmc_wlevel_rank =  &hw_wr_level_data->lmc_wlevel_rank;
    bdk_lmcx_wlevel_ctl_t *wlevel_ctl =         &hw_wr_level_data->wlevel_ctl;
    int dram_x4_defaults = 1;

#pragma pack(pop)

    if (wlevel_loops)
        ddr_print("N%d.LMC%d: Performing Hardware Write-Leveling\n", node, ddr_interface_num);
    else {
        wlevel_bitmask_errors = 1; /* Force software write-leveling to run */
        ddr_print("N%d.LMC%d: Forcing software Write-Leveling\n", node, ddr_interface_num);
    }

    modereg_params1.u = BDK_CSR_READ(node, BDK_LMCX_MODEREG_PARAMS1(ddr_interface_num));

    // For DDR4, we touch WLEVEL_CTL fields OR_DIS or BITMASK here

    int default_or_dis  = 1;
    int default_bitmask = 0xFF;

    // when x4, use only the lower nibble bits
    if (dram_width == 4) {
        default_bitmask = 0x0F;
        VB_PRT(VBL_DEV, "N%d.LMC%d: WLEVEL_CTL: default bitmask is 0x%02x for DDR4 x4\n",
               node, ddr_interface_num, default_bitmask);
    }

    wlevel_ctl->u = BDK_CSR_READ(node, BDK_LMCX_WLEVEL_CTL(ddr_interface_num));
    wlevel_ctl->s.or_dis  = hw_wr_leveling_overrides->ddr_wlevel_ctl_or_dis;
    wlevel_ctl->s.bitmask = hw_wr_leveling_overrides->ddr_wlevel_ctl_bitmask;

    // only if not defaults
    if ((wlevel_ctl->s.or_dis != default_or_dis) || (wlevel_ctl->s.bitmask != default_bitmask)) {
        dram_x4_defaults = 0;
        ddr_print("N%d.LMC%d: WLEVEL_CTL: or_dis=%d, bitmask=0x%02x\n",
                  node, ddr_interface_num, wlevel_ctl->s.or_dis, wlevel_ctl->s.bitmask);
    }
    // always write
    DRAM_CSR_WRITE(node, BDK_LMCX_WLEVEL_CTL(ddr_interface_num), wlevel_ctl->u);

    memset(hw_wr_level_data->hwl_dqs1, 0, sizeof(hwl_dqs1_by_rank_t)*4);

    // Start the hardware write-leveling loop per rank
    for (rankx = 0; rankx < 4; rankx++) {

        if (!(rank_mask & (1 << rankx)))
            continue;

        // array to collect counts of byte-lane values
        // use only low-order 3 bits, so only values 0-7
        memset(hw_wr_level_data->wlevel_bytes, 0, sizeof(wlevel_bytecnt_t)*3);
        memset(hw_wr_level_data->wlevel_bytes_pbm, 0, sizeof(wlevel_bytecnt_t)*3);

        // restructure the looping so we can keep trying until we get the samples we want
        //for (int wloop = 0; wloop < wlevel_loops; wloop++) {
        int wloop;
        int wloop_retries; // retries per sample for HW-related issues with bitmasks or values
        int wloop_retries_total = 0;
        int wloop_retries_exhausted = 0;
        int wlevel_validity_errors;
        int wlevel_bitmask_errors_rank = 0;
        int wlevel_validity_errors_rank = 0;
        int rank_nom = 0;

        if (match_wlevel_rtt_nom) {
            rank_nom = EXTR_NOM(modereg_params1.u, rankx);

            ddr_print("N%d.LMC%d.R%d: Setting WLEVEL_CTL[rtt_nom] to %d (%d)\n",
                      node, ddr_interface_num, rankx, rank_nom,
                      imp_values->rtt_nom_ohms[rank_nom]);
        }

        wlevel_ctl->u = BDK_CSR_READ(node, BDK_LMCX_WLEVEL_CTL(ddr_interface_num));
        if (bdk_is_model(OCTEONTX_CN8XXX)) {
            wlevel_ctl->s.rtt_nom = (default_wlevel_rtt_nom > 0) ? (default_wlevel_rtt_nom - 1) : 7;
            if (match_wlevel_rtt_nom) {
                wlevel_ctl->s.rtt_nom = (rank_nom > 0) ? (rank_nom - 1) : 7;
            }
        }

        int sample_set, num_sample_sets = 1;
        if ((dram_width == 4) && dram_x4_defaults) {
            num_sample_sets = 2; // for CN8 and CN9
        }

        for (sample_set = 0; sample_set < num_sample_sets; sample_set += 1) {

            // take two sets of samples each with different bitmask
            if ((dram_width == 4) && dram_x4_defaults) {
                int16_t x4mask[2] = { 0x000F, 0x00F0 };
                wlevel_ctl->s.bitmask = x4mask[sample_set];
                VB_PRT(VBL_FAE, "N%d.LMC%d.R%d: WLEVEL_CTL: setting bitmask to 0x%02x for HWL samples\n",
                       node, ddr_interface_num, rankx, x4mask[sample_set]);
            }

            wloop = 0;
            wloop_retries = 0;

	    while (wloop < wlevel_loops) {

                wlevel_bitmask_errors = 0; /* Reset error counters */
                wlevel_validity_errors = 0;

                memset(wlevel_bitmask, 0, sizeof(*wlevel_bitmask));

                hw_wr_level_data->wlevel_bitmask_errors = wlevel_bitmask_errors;

                Perform_Write_Leveling_on_Rank(node, ddr_interface_num, init_data,
                                               hw_wr_level_data, rankx);
                wlevel_bitmask_errors = hw_wr_level_data->wlevel_bitmask_errors;

                // check validity only if no bitmask errors
                if (wlevel_bitmask_errors == 0) {
                    if (((spd_dimm_type == 1) || spd_rdimm) && // normal [L][RU]DIMM
                        (dram_width != 16)    &&
                        (ddr_interface_64b)   &&
                        !(disable_hwl_validity))
                        { // bypass if mini- or SO- or x16 or 32-bit or disabled
                            wlevel_validity_errors =
                                Validate_HW_WL_Settings(node, ddr_interface_num, lmc_wlevel_rank, ecc_ena);
                            wlevel_validity_errors_rank += (wlevel_validity_errors != 0);
                        }
                }
                else
                    wlevel_bitmask_errors_rank++;

                // before we print, if we had bitmask or validity errors, do a retry...
                if ((wlevel_bitmask_errors != 0) || (wlevel_validity_errors != 0)) {
                    // VBL must be high to show the bad bitmaps or delays here also
                    if (dram_is_verbose(VBL_DEV2)) {
                        if (ddr_wlevel_printall)
                            display_WL_BM(node, ddr_interface_num, rankx, wlevel_bitmask, ecc_ena);
                        do_display_WL_PBM(node, ddr_interface_num, *lmc_wlevel_rank,
                                          wlevel_bitmask, rankx, WITH_NOTHING);
                    }
                    if (wloop_retries < WLOOP_RETRIES_DEFAULT) {
                        wloop_retries++;
                        wloop_retries_total++;
                        // this printout is per-retry: only when VBL is high enough (DEV2?)
                        VB_PRT(VBL_DEV2, "N%d.LMC%d.R%d: H/W Write-Leveling had %s errors - retrying...\n",
                               node, ddr_interface_num, rankx,
                               (wlevel_bitmask_errors) ? "Bitmask" : "Validity");
                        continue; // this takes us back to the top without counting a sample
                    }
                    else { // ran out of retries for this sample
                        // retries exhausted, do not print at normal VBL
                        VB_PRT(VBL_DEV2, "N%d.LMC%d.R%d: H/W Write-Leveling issues: %s errors\n",
                               node, ddr_interface_num, rankx,
                               (wlevel_bitmask_errors) ? "Bitmask" : "Validity");
                        wloop_retries_exhausted++;
                    }
                }
                // no errors or exhausted retries, use this sample
                wloop_retries = 0; //reset for next sample

                // only print bitmasks when option selected
                if (ddr_wlevel_printall)
                    display_WL_BM(node, ddr_interface_num, rankx, wlevel_bitmask, ecc_ena);
                // always print the delays/PBM char
                do_display_WL_PBM(node, ddr_interface_num, *lmc_wlevel_rank,
                                  wlevel_bitmask, rankx, WITH_NOTHING);

                if (ddr_wlevel_roundup) { /* Round up odd bitmask delays */
                    for (byte_idx = 0; byte_idx < (8+ecc_ena); ++byte_idx) {
                        if (!(ddr_interface_bytemask & (1 << byte_idx)))
                            continue;
                        update_wlevel_rank_struct(lmc_wlevel_rank, byte_idx,
                                                  roundup_wlevel_bitmask(wlevel_bitmask[byte_idx]));
                    } /* for (byte_idx=0; byte_idx<(8+ecc_ena); ++byte_idx) */
                    DRAM_CSR_WRITE(node, BDK_LMCX_WLEVEL_RANKX(ddr_interface_num, rankx), lmc_wlevel_rank->u);
                    display_WL(node, ddr_interface_num, *lmc_wlevel_rank, rankx);
                }

                // OK, we have a decent sample, no bitmask or validity errors
                // count PBM/IBM only if we are taking multiple samples
                if (wlevel_loops > 1) {
                    for (byte_idx = 0; byte_idx < (8+ecc_ena); ++byte_idx) {
                        if (!(ddr_interface_bytemask & (1 << byte_idx)))
                            continue;
                        int ix = (get_wlevel_rank_struct(lmc_wlevel_rank, byte_idx)) & 7; // only values 0-7

                        // just count PBM and IBM separately, no bias
#define IS_PERFECT(c) (((c) >= 3) && ((c) <= 5))
/* #define IS_PERFECT(c) ((c) == 4) */
                        if (IS_PERFECT(__builtin_popcount(wlevel_bitmask[byte_idx]))) { // if perfect...
                            hw_wr_level_data->wlevel_bytes_pbm[sample_set].bytecnt[byte_idx].bitcnt[ix]++;
                            hw_wr_level_data->wlevel_bytes_pbm[2].bytecnt[byte_idx].bitcnt[ix]++;
                        } else {
                            hw_wr_level_data->wlevel_bytes[sample_set].bytecnt[byte_idx].bitcnt[ix]++; // imperfect...
                            hw_wr_level_data->wlevel_bytes[2].bytecnt[byte_idx].bitcnt[ix]++; // imperfect...
                        }
                    } /* for (byte_idx=0; byte_idx<(8+ecc_ena); ++byte_idx) */
                } /* if (wlevel_loops > 1) */

                wloop++; // if we get here, we have taken a decent sample

            } /* while (wloop < wlevel_loops) */
        } /* for (sample_set = 0; sample_set < num_sample_sets; sample_set += 1) */

        // if we did sample more than once, try to pick a majority vote
        if (wlevel_loops > 1) {

            // look for the majority in each byte-lane
            for (byte_idx = 0; byte_idx < (8+ecc_ena); ++byte_idx) {
                if (!(ddr_interface_bytemask & (1 << byte_idx)))
                    continue;

                Find_Majority_WR_Level_Settings(node, ddr_interface_num, init_data, overrides,
                                                hw_wr_level_data, rankx, byte_idx);
            } /* for (byte_idx=0; byte_idx<(8+ecc_ena); ++byte_idx) */

            DRAM_CSR_WRITE(node, BDK_LMCX_WLEVEL_RANKX(ddr_interface_num, rankx), lmc_wlevel_rank->u);
            display_WL_with_final(node, ddr_interface_num, *lmc_wlevel_rank, rankx);
            VB_PRT(VBL_FAE, "-----------\n"); // FIXME? verbosity?
        } /* if (wlevel_loops > 1) */

        // maybe print an error summary for the rank
        if ((wlevel_bitmask_errors_rank != 0) || (wlevel_validity_errors_rank != 0)) {
            VB_PRT(VBL_FAE, "N%d.LMC%d.R%d: H/W Write-Leveling errors - %d bitmask, %d validity, %d retries, %d exhausted\n",
                   node, ddr_interface_num, rankx,
                   wlevel_bitmask_errors_rank, wlevel_validity_errors_rank,
                   wloop_retries_total, wloop_retries_exhausted);
        }

    } /* for (rankx = 0; rankx < 4; rankx++) */

    // If selected, adjust DQS1 to "even out" x4 HWL
    if ((dram_width == 4) && enable_x4_hwl_adj) {
        // Check the DQS1 masks for possible use
        uint16_t mask_up = 0xFFFF, mask_dn = 0xFFFF;
        for (rankx = 0; rankx < 4; rankx++) {
            if (!(rank_mask & (1 << rankx)))
                continue;
            mask_up &= hw_wr_level_data->hwl_dqs1[rankx].dqs1_mask_up;
            mask_dn &= hw_wr_level_data->hwl_dqs1[rankx].dqs1_mask_dn;
            VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: HWL DQS1 Mask by rank: UP 0x%04x DN 0x%04x\n",
                   node, ddr_interface_num, rankx,
                   hw_wr_level_data->hwl_dqs1[rankx].dqs1_mask_up,
                   hw_wr_level_data->hwl_dqs1[rankx].dqs1_mask_dn);
        } /* for (rankx = 0; rankx < 4; rankx++) */

        VB_PRT(VBL_DEV, "N%d.LMC%d:    HWL DQS1 Mask Summary: UP 0x%04x DN 0x%04x\n",
               node, ddr_interface_num, mask_up, mask_dn);

        if ((mask_up != 0) || (mask_dn != 0)) { 
            int byte;
            BDK_CSR_INIT(phy_ctl2, node, BDK_LMCX_PHY_CTL2(ddr_interface_num));
            for (byte = 0; byte < 9; byte++) {
                if (mask_up & (1 << byte))
                    INSRT_DQS1_ADJ(&phy_ctl2.u, byte, EXTR_DQS1_ADJ(phy_ctl2.u, byte) + 1);
                else if (mask_dn & (1 << byte))
                    INSRT_DQS1_ADJ(&phy_ctl2.u, byte, EXTR_DQS1_ADJ(phy_ctl2.u, byte) - 1);
            }
            DRAM_CSR_WRITE(node, BDK_LMCX_PHY_CTL2(ddr_interface_num), phy_ctl2.u);

            VB_PRT(VBL_DEV, "N%d.LMC%d: HWLX4: PHY_CTL2[dqs1_wdsk_adjX] [8:0]: ", node, ddr_interface_num);
            for (byte = 8; byte >= 0; byte--) VB_PRT(VBL_DEV, "%1d ", EXTR_DQS1_ADJ(phy_ctl2.u, byte));
            VB_PRT(VBL_DEV, "\n");

            // FIXME: for now, just change PHY_CTL2 and move on; TODO: rerun HWL to see effect!!

        } /* if ((mask_up != 0) || (mask_dn != 0)) */
    } /* if ((dram_width == 4) && enable_x4_hwl_adj) */

    // At the end of HW Write Leveling, check on some things...
    if (! disable_deskew_training) {

        deskew_counts_t dsk_counts;
        int retry_count = 0;

        VB_PRT(VBL_FAE, "N%d.LMC%d: Check Deskew Settings before Read-Leveling.\n", node, ddr_interface_num);

        if (bdk_is_model(OCTEONTX_CN8XXX)) {
            do {
                Validate_Read_Deskew_Training(node, ddr_interface_num, rank_mask, &dsk_counts, VBL_FAE, "B4RLV");

                // only RAWCARD A or B will not benefit from retraining if there's only saturation
                // or any rawcard if there is a nibble error
                if ((!spd_rawcard_AorB && dsk_counts.saturated > 0) ||
                    ((dsk_counts.nibrng_errs != 0) || (dsk_counts.limits != 0)))
                {
                    retry_count++;
                    VB_PRT(VBL_FAE, "N%d.LMC%d: Deskew Status indicates saturation or nibble errors - retry %d Training.\n",
                           node, ddr_interface_num, retry_count);
                    Perform_Read_Deskew_Training(node, rank_mask, ddr_interface_num,
                                                 init_data, overrides, 0);
                } else
                    break;
            } while (retry_count < 5);
        }

        // print the last setting only if we had to do retries here
        if (retry_count > 0) {
            Validate_Read_Deskew_Training(node, ddr_interface_num, rank_mask, &dsk_counts, VBL_NORM, "RETRY");
        }

    } /* if (! disable_deskew_training) */

} // End HW write-leveling block



