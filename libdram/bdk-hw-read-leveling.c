/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libdram.h"

#include "bdk-dram-init.h"

static void
update_rlevel_rank_struct(bdk_lmcx_rlevel_rankx_t *lmc_rlevel_rank,
                          int byte, int delay)
{
    int RLEVEL_BYTE_BITS = CN8_OR_CN9(6, 7);
    uint64_t RLEVEL_BYTE_MSK = ((1UL << RLEVEL_BYTE_BITS) - 1);
    uint64_t temp_rlevel_ranks;

    if (byte >= 0 && byte <= 8) {
	temp_rlevel_ranks = lmc_rlevel_rank->u & ~(RLEVEL_BYTE_MSK << (RLEVEL_BYTE_BITS * byte));
	temp_rlevel_ranks |= ((delay & RLEVEL_BYTE_MSK) << (RLEVEL_BYTE_BITS * byte));
	lmc_rlevel_rank->u = temp_rlevel_ranks;
    }
}

int
get_rlevel_rank_struct(bdk_lmcx_rlevel_rankx_t *lmc_rlevel_rank, int byte)
{
    int RLEVEL_BYTE_BITS = CN8_OR_CN9(6, 7);
    uint64_t RLEVEL_BYTE_MSK = ((1UL << RLEVEL_BYTE_BITS) - 1);
    int delay = 0;

    if (byte >= 0 && byte <= 8) {
	delay = ((lmc_rlevel_rank->u) >> (RLEVEL_BYTE_BITS * byte)) & RLEVEL_BYTE_MSK;
    }
    return delay;
}

static uint64_t
octeontx_read_rlevel_dbg(bdk_node_t node, int ddr_interface_num, int idx)
{
    //DRAM_CSR_MODIFY(c, node, BDK_LMCX_RLEVEL_CTL(ddr_interface_num), c.s.byte = idx);
    BDK_CSR_MODIFY(c, node, BDK_LMCX_RLEVEL_CTL(ddr_interface_num), c.s.byte = idx); // FIXME: CSR verb?

    BDK_CSR_READ(node, BDK_LMCX_RLEVEL_CTL(ddr_interface_num));
    BDK_CSR_INIT(rlevel_dbg, node, BDK_LMCX_RLEVEL_DBG(ddr_interface_num));
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return rlevel_dbg.s.bitmask;

    // else do 128-bit mask handling for CN9XXX...
    // do this by trying to reduce the 128 bits to 64 bits that contains all the 1's
    BDK_CSR_INIT(rlevel_dbg2, node, BDK_LMCX_RLEVEL_DBG2(ddr_interface_num));
    uint64_t mask  = rlevel_dbg.s.bitmask;
    uint64_t mask2 = rlevel_dbg2.s.bitmask;
    int fsb = __builtin_ffsl(mask);
    if (mask == 0)
        return mask2;
    else if ((mask2 == 0) || (fsb == 1))
        return mask;
    else {
        VB_PRT(VBL_DEV2, "N%d.LMC%d: RL DBG BM: byte %d: %016lx.%016lx fsb=%d\n",
                          node, ddr_interface_num, idx, mask2, mask, fsb);
        return (mask >> (fsb - 1)) | (mask2 << (64 - (fsb - 1)));
    }
}

/*
 * Apply a filter to the BITMASK results returned from Octeon
 * read-leveling to determine the most likely delay result.  This
 * computed delay may be used to qualify the delay result returned by
 * Octeon. Accumulate an error penalty for invalid characteristics of
 * the bitmask so that they can be used to select the most reliable
 * results.
 *
 * The algorithm searches for the largest contiguous MASK within a
 * maximum RANGE of bits beginning with the MSB.
 *
 * 1. a MASK with a WIDTH less than 4 will be penalized
 * 2. Bubbles in the bitmask that occur before or after the MASK
 *    will be penalized
 * 3. If there are no trailing bubbles then extra bits that occur
 *    beyond the maximum RANGE will be penalized.
 *
 *   +++++++++++++++++++++++++++++++++++++++++++++++++++
 *   +                                                 +
 *   +   e.g. bitmask = 27B00                          +
 *   +                                                 +
 *   +   63                  +--- mstart           0   +
 *   +   |                   |                     |   +
 *   +   |         +---------+     +--- fb         |   +
 *   +   |         |  range  |     |               |   +
 *   +   V         V         V     V               V   +
 *   +                                                 +
 *   +   0 0 ... 1 0 0 1 1 1 1 0 1 1 0 0 0 0 0 0 0 0   +
 *   +                                                 +
 *   +           ^     ^     ^                         +
 *   +           |     | mask|                         +
 *   +     lb ---+     +-----+                         +
 *   +                  width                          +
 *   +                                                 +
 *   +++++++++++++++++++++++++++++++++++++++++++++++++++
 */

#define DEFAULT_MASKRANGE_BITS  6

static int
validate_rlevel_bitmask(rlevel_bitmask_t *rlevel_bitmask_p)
{
    int i;
    int errors  = 0;
    uint64_t mask = 0;      /* Used in 64-bit comparisons */
    int8_t  mstart = 0;
    uint8_t width = 0;
    uint8_t firstbit = 0;
    uint8_t lastbit = 0;
    uint8_t bubble = 0;
    uint8_t tbubble = 0;
    uint8_t blank = 0;
    uint8_t narrow = 0;
    uint8_t trailing = 0;
    uint64_t bitmask = rlevel_bitmask_p->bm;
    uint8_t extras = 0;
    uint8_t toolong = 0;
    uint64_t temp;
    int is_cn8xxx = !!bdk_is_model(OCTEONTX_CN8XXX);

    int MASKRANGE_BITS = DEFAULT_MASKRANGE_BITS;
    int NARROW_LIMIT = MASKRANGE_BITS - 2;
    if (!is_cn8xxx) {
        MASKRANGE_BITS *= 2; // bitmasks are double size on T93
        NARROW_LIMIT   *= 2; // limits are double size on T93 also
        NARROW_LIMIT -= 1; // but give NARROW a little slack ...
    }
    uint64_t MASKRANGE = (1UL << MASKRANGE_BITS) - 1;


    if (bitmask == 0) {
	blank += RLEVEL_BITMASK_BLANK_ERROR;
    } else {

	/* Look for fb, the first bit */
        temp = bitmask;
        while (!(temp & 1)) {
            firstbit++;
            temp >>= 1;
        }

	/* Look for lb, the last bit */
        lastbit = firstbit;
        while ((temp >>= 1))
            lastbit++;

	/* Start with the max range to try to find the largest mask within the bitmask data */
        width = MASKRANGE_BITS;
        for (mask = MASKRANGE; mask > 0; mask >>= 1, --width) {
	    for (mstart = lastbit - width + 1; mstart >= firstbit; --mstart) {
                temp = mask << mstart;
		if ((bitmask & temp) == temp)
                    goto done_now;
	    }
        }
    done_now:
        /* look for any more contiguous 1's to the right of mstart */
        if (width == MASKRANGE_BITS) { // only when maximum mask
            while ((bitmask >> (mstart - 1)) & 1) { // slide right over more 1's
                --mstart;
                extras++; // count the number of extra bits
            }
        }

        /* Penalize any extra 1's beyond the maximum desired mask */
        if (extras > 0)
            toolong = RLEVEL_BITMASK_TOOLONG_ERROR * ((1 << extras) - 1);

	/* Detect if bitmask is too narrow. */
	if (width < NARROW_LIMIT)
	    narrow = (NARROW_LIMIT - width) * RLEVEL_BITMASK_NARROW_ERROR;

	/* detect leading bubble bits, that is, any 0's between first and mstart */
        temp = bitmask >> (firstbit + 1);
        i = mstart - firstbit - 1;
        while (--i >= 0) {
	    if ((temp & 1) == 0)
		bubble += RLEVEL_BITMASK_BUBBLE_BITS_ERROR;
            temp >>= 1;
        }

        temp = bitmask >> (mstart + width + extras);
        i = lastbit - (mstart + width + extras - 1);
        while (--i >= 0) {
            if (temp & 1) { /* Detect 1 bits after the trailing end of the mask, including last. */
                trailing += RLEVEL_BITMASK_TRAILING_BITS_ERROR;
            } else { /* Detect trailing bubble bits, that is, any 0's between end-of-mask and last */
		tbubble  += RLEVEL_BITMASK_BUBBLE_BITS_ERROR;
            }
            temp >>= 1;
        }
    }

    errors = blank + narrow + toolong; // for CN9XXX, only major errors
    if (is_cn8xxx)
        errors += bubble + tbubble + trailing; // add in the others for CN8XXX

    /* Pass out useful statistics */
    rlevel_bitmask_p->mstart = mstart;
    rlevel_bitmask_p->width  = width;

    VB_PRT(VBL_DEV3, "bm:%08lx mask:%02lx, width:%2u, mstart:%2d, fb:%2u, lb:%2u"
           " (bu:%2d, tb:%2d, bl:%2d, n:%2d, t:%2d, x:%2d) errors:%3d %s\n",
           (unsigned long) bitmask, mask, width, mstart,
           firstbit, lastbit, bubble, tbubble, blank, narrow,
           trailing, toolong, errors, (errors) ? "=> invalid" : "");

    return errors;
}

/**
 * Functions for DDR4 init. Internal use only.
 */

#define DEBUG_VALIDATE_BITMASK 0
#if DEBUG_VALIDATE_BITMASK
#define debug_bitmask_print ddr_print
#else
#define debug_bitmask_print(...)
#endif

static int
compute_rlevel_delay(uint8_t mstart, uint8_t width,
                          bdk_lmcx_rlevel_ctl_t rlevel_ctl)
{
    int delay;

    //debug_bitmask_print("  offset_en:%d", rlevel_ctl.cn8.offset_en);

    if (rlevel_ctl.s.offset_en) {
	delay = max(mstart, mstart + width - 1 - rlevel_ctl.s.offset);
    } else {
	/* if (rlevel_ctl.s.offset) { */ /* Experimental */
	if (0) {
	    delay = max(mstart + rlevel_ctl.s.offset, mstart + 1);
	    /* Insure that the offset delay falls within the bitmask */
	    delay = min(delay, mstart + width - 1);
	} else {
	    delay = (width - 1) / 2 + mstart; /* Round down */
	    /* delay = (width/2) + mstart; */  /* Round up */
	}
    }

    return delay;
}

static void unpack_rlevel_settings(int ddr_interface_bytemask, int ecc_ena,
				   rlevel_byte_data_t *rlevel_byte,
				   bdk_lmcx_rlevel_rankx_t lmc_rlevel_rank)
{
    int i;
    if ((ddr_interface_bytemask & 0xff) == 0xff) {
	if (ecc_ena) {
            for (i = 4; i < 8; i++) {
                rlevel_byte[i+1].delay = get_rlevel_rank_struct(&lmc_rlevel_rank, i);
            }
            rlevel_byte[4].delay = get_rlevel_rank_struct(&lmc_rlevel_rank, 8);
	} else {
            for (i = 4; i < 8; i++)
                rlevel_byte[i].delay = get_rlevel_rank_struct(&lmc_rlevel_rank, i);
	}
    } else {
        for (i = 4; i < 9; i++)
            rlevel_byte[i].delay = get_rlevel_rank_struct(&lmc_rlevel_rank, i);
    }
    for (i = 0; i < 4; i++)
        rlevel_byte[i].delay = get_rlevel_rank_struct(&lmc_rlevel_rank, i);
}

static void pack_rlevel_settings(int ddr_interface_bytemask, int ecc_ena,
				 rlevel_byte_data_t *rlevel_byte,
				 bdk_lmcx_rlevel_rankx_t *final_rlevel_rank)
{
    bdk_lmcx_rlevel_rankx_t lmc_rlevel_rank = *final_rlevel_rank;
    int i;

    if ((ddr_interface_bytemask & 0xff) == 0xff) {
	if (ecc_ena) {
            for (i = 4; i < 8; i++) {
                update_rlevel_rank_struct(&lmc_rlevel_rank, i, rlevel_byte[i+1].delay);
            }
            update_rlevel_rank_struct(&lmc_rlevel_rank, 8, rlevel_byte[4].delay);
	} else {
            for (i = 4; i < 8; i++)
                update_rlevel_rank_struct(&lmc_rlevel_rank, i, rlevel_byte[i].delay);
	}
    } else {
        for (i = 4; i < 9; i++)
            update_rlevel_rank_struct(&lmc_rlevel_rank, i, rlevel_byte[i].delay);
    }
    for (i = 0; i < 4; i++)
        update_rlevel_rank_struct(&lmc_rlevel_rank, i, rlevel_byte[i].delay);

    *final_rlevel_rank = lmc_rlevel_rank;
}

/* Delay trend: constant=0, decreasing=-1, increasing=1 */
static int calc_delay_trend(int v)
{
    if (v == 0)
	return (0);
    if (v < 0)
	return (-1);
    return 1;
}

/* Evaluate delay sequence across the whole range of byte delays while
** keeping track of the overall delay trend, increasing or decreasing.
** If the trend changes charge an error amount to the score.
*/

// NOTE: "max_adj_delay_inc" argument is, by default, 2 for DDR4

static int nonsequential_delays(rlevel_byte_data_t *rlevel_byte,
				int start, int end, int max_adj_delay_inc)
{
    int error = 0;
    int delay_trend, prev_trend = 0;
    int byte_idx;
    int delay_inc;
    int delay_diff;
    int byte_err;

    for (byte_idx = start; byte_idx < end; ++byte_idx) {
        byte_err = 0;

	delay_diff = rlevel_byte[byte_idx+1].delay - rlevel_byte[byte_idx].delay;
	delay_trend = calc_delay_trend(delay_diff);

	debug_bitmask_print("Byte %d: %2d, Byte %d: %2d, delay_trend: %2d, prev_trend: %2d",
			    byte_idx+0, rlevel_byte[byte_idx+0].delay,
			    byte_idx+1, rlevel_byte[byte_idx+1].delay,
			    delay_trend, prev_trend);

        /* Increment error each time the trend changes to the opposite direction.
         */
	if ((prev_trend != 0) && (delay_trend != 0) && (prev_trend != delay_trend)) {
	    byte_err += RLEVEL_NONSEQUENTIAL_DELAY_ERROR;
	    prev_trend = delay_trend;
	    debug_bitmask_print(" => Nonsequential byte delay");
	}

	delay_inc = _abs(delay_diff); // how big was the delay change, if any

        /* Even if the trend did not change to the opposite direction, check for
           the magnitude of the change, and scale the penalty by the amount that
           the size is larger than the provided limit.
         */
	if ((max_adj_delay_inc != 0) && (delay_inc > max_adj_delay_inc)) {
	    byte_err += (delay_inc - max_adj_delay_inc) * RLEVEL_ADJACENT_DELAY_ERROR;
	    debug_bitmask_print(" => Adjacent delay error");
	}

	debug_bitmask_print("\n");
	if (delay_trend != 0)
	    prev_trend = delay_trend;

        rlevel_byte[byte_idx+1].sqerrs = byte_err;
        error += byte_err;
    }
    return error;
}




void
Get_HW_Read_Leveling_Overrides(bdk_node_t node, int ddr_interface_num,
                               dram_init_data_t *init_data,
                               dram_overrides_t *overrides)
{
    const char *s;
    int spd_rdimm =         init_data->refs.spd_rdimm;
    int dimm_count =        init_data->refs.dimm_count;
    int num_ranks =         init_data->refs.num_ranks;
    hw_rd_leveling_overrides_t *hw_rd_leveling_overrides = &overrides->hw_rlevel;
    const ddr_custom_config_t *custom_lmc_config = &init_data->ddr_configuration->custom_lmc_config;

    if ((s = lookup_env_parameter("ddr_disable_rank_majority")) != NULL) {
        hw_rd_leveling_overrides->disable_rank_majority = !!strtoul(s, NULL, 0);
    }

    hw_rd_leveling_overrides->disable_rl_pbm_counting = CN8_OR_CN9(0, 1);
    if ((s = lookup_env_parameter("ddr_disable_rl_pbm_counting")) != NULL) {
        hw_rd_leveling_overrides->disable_rl_pbm_counting = !!strtoul(s, NULL, 0);
    }

    hw_rd_leveling_overrides->rlevel_separate_ab = DEFAULT_RLEVEL_SEPARATE_AB;
    if ((s = lookup_env_parameter("ddr_rlevel_separate_ab")) != NULL) {
        hw_rd_leveling_overrides->rlevel_separate_ab = !!strtoul(s, NULL, 0);
    }

#if PERFECT_BITMASK_COUNTING
    if (!hw_rd_leveling_overrides->disable_rl_pbm_counting) {
        hw_rd_leveling_overrides->pbm_lowsum_limit = 5;
        // FIXME: TODO: RODT skipping for CN9XXX if/when needed; change selections...
        if (bdk_is_model(OCTEONTX_CN8XXX)) {
            hw_rd_leveling_overrides->pbm_rodt_skip =
                (1U << ddr4_rodt_ctl_240_ohm) | (1U << ddr4_rodt_ctl_34_ohm);
        }
        if ((s = lookup_env_parameter("ddr_pbm_lowsum_limit")) != NULL) {
            hw_rd_leveling_overrides->pbm_lowsum_limit = strtoul(s, NULL, 0);
        }
        if ((s = lookup_env_parameter("ddr_pbm_rodt_skip")) != NULL) {
            hw_rd_leveling_overrides->pbm_rodt_skip = strtoul(s, NULL, 0);
        }
    }
#endif /* PERFECT_BITMASK_COUNTING */

    bdk_lmcx_rlevel_ctl_t rlevel_ctl;
    rlevel_ctl.u = BDK_CSR_READ(node, BDK_LMCX_RLEVEL_CTL(ddr_interface_num));

    int value = 1;
    if ((s = lookup_env_parameter("ddr_rlevel_delay_unload")) != NULL) {
        value = !!strtoul(s, NULL, 0);
    }
    rlevel_ctl.s.delay_unload_0 = value;
    rlevel_ctl.s.delay_unload_1 = value;
    rlevel_ctl.s.delay_unload_2 = value;
    rlevel_ctl.s.delay_unload_3 = value;

    // default to 1 to get best bitmasks on all
    rlevel_ctl.s.or_dis = 1;
    if ((s = lookup_env_parameter("ddr_rlevel_or_dis")) != NULL) {
        rlevel_ctl.s.or_dis = !!strtoul(s, NULL, 0);
    }
    rlevel_ctl.s.bitmask = 0xff; // should work in 32b mode also
    if ((s = lookup_env_parameter("ddr_rlevel_ctl_bitmask")) != NULL) {
        rlevel_ctl.s.bitmask = strtoul(s, NULL, 0);
    }

    debug_print("N%d.LMC%d: RLEVEL_CTL: or_dis=%d, bitmask=0x%02x\n",
                node, ddr_interface_num,
                rlevel_ctl.s.or_dis, rlevel_ctl.s.bitmask);

    hw_rd_leveling_overrides->rlevel_comp_offset = (spd_rdimm)
        ? custom_lmc_config->rlevel_comp_offset_rdimm
        : custom_lmc_config->rlevel_comp_offset_udimm;
    if ((s = lookup_env_parameter("ddr_rlevel_comp_offset")) != NULL) {
        hw_rd_leveling_overrides->rlevel_comp_offset = strtoul(s, NULL, 0);
    }

    if ((s = lookup_env_parameter("ddr_rlevel_offset")) != NULL) {
        rlevel_ctl.s.offset   = strtoul(s, NULL, 0);
    }
    if ((s = lookup_env_parameter("ddr_rlevel_offset_en")) != NULL) {
        rlevel_ctl.s.offset_en   = strtoul(s, NULL, 0);
    }
    if ((s = lookup_env_parameter("ddr_rlevel_ctl")) != NULL) {
        rlevel_ctl.u   = strtoul(s, NULL, 0);
    }

    hw_rd_leveling_overrides->rlevel_ctl = rlevel_ctl.u;

    // do this here so we can look at final RLEVEL_CTL[offset] setting...
    hw_rd_leveling_overrides->enable_rldelay_bump = 0; // FIXME: default 0 for CN9XXX
    if (bdk_is_model(OCTEONTX_CN8XXX)) {
        hw_rd_leveling_overrides->enable_rldelay_bump = (bdk_is_model(OCTEONTX_CN81XX)) ? 1 : 3;
    }
    if ((s = lookup_env_parameter("ddr_enable_rldelay_bump")) != NULL) {
        // also use this as test mask bits
        hw_rd_leveling_overrides->enable_rldelay_bump = strtoul(s, NULL, 0);
    }

    if (hw_rd_leveling_overrides->enable_rldelay_bump != 0) {
        hw_rd_leveling_overrides->rldelay_bump_incr = (rlevel_ctl.s.offset == 1) ? -1 : 1;
    }

    hw_rd_leveling_overrides->rlevel_debug_loops = 1;
    if (bdk_is_platform(BDK_PLATFORM_ASIM))
        hw_rd_leveling_overrides->rlevel_debug_loops = 0;
    if ((s = lookup_env_parameter("ddr%d_rlevel_debug_loops", ddr_interface_num)) != NULL) {
        hw_rd_leveling_overrides->rlevel_debug_loops = strtoul(s, NULL, 0);
    }

    int ddr_rtt_nom_auto = init_data->terms.ddr_rtt_nom_auto;
    if ((s = lookup_env_parameter("ddr_rtt_nom_auto")) != NULL) {
        ddr_rtt_nom_auto = !!strtoul(s, NULL, 0);
    }
    init_data->terms.ddr_rtt_nom_auto = ddr_rtt_nom_auto;

    int rlevel_samples = custom_lmc_config->rlevel_average_loops;
    if (rlevel_samples == 0) {
        rlevel_samples = RLEVEL_SAMPLES_DEFAULT;
        if ((dimm_count == 1) || (num_ranks == 1)) // up the samples for these cases
            rlevel_samples = rlevel_samples * 2 + 1;
    }
    if ((s = lookup_env_parameter("ddr_rlevel_average")) != NULL) {
        rlevel_samples = strtoul(s, NULL, 0);
    }
    hw_rd_leveling_overrides->rlevel_samples = rlevel_samples;

    int ddr_rlevel_compute = custom_lmc_config->rlevel_compute;
    if ((s = lookup_env_parameter("ddr_rlevel_compute")) != NULL) {
        ddr_rlevel_compute = strtoul(s, NULL, 0);
    }
    hw_rd_leveling_overrides->ddr_rlevel_compute = ddr_rlevel_compute;

    /* The purpose for the indexed table is to sort the settings
    ** by the ohm value to simplify the testing when incrementing
    ** through the settings.  (index => ohms) 1=120, 2=60, 3=40,
    ** 4=30, 5=20 */
    int min_rtt_nom_idx = (custom_lmc_config->min_rtt_nom_idx == 0) ? 1 : custom_lmc_config->min_rtt_nom_idx;
    int max_rtt_nom_idx = (custom_lmc_config->max_rtt_nom_idx == 0) ? 5 : custom_lmc_config->max_rtt_nom_idx;

    int min_rodt_ctl = (custom_lmc_config->min_rodt_ctl == 0) ? 1 : custom_lmc_config->min_rodt_ctl;
    int max_rodt_ctl = (custom_lmc_config->max_rodt_ctl == 0) ? 5 : custom_lmc_config->max_rodt_ctl;

    if ((s = lookup_env_parameter("ddr_min_rodt_ctl")) != NULL) {
        min_rodt_ctl = strtoul(s, NULL, 0);
    }
    if ((s = lookup_env_parameter("ddr_max_rodt_ctl")) != NULL) {
        max_rodt_ctl = strtoul(s, NULL, 0);
    }
    if ((s = lookup_env_parameter("ddr_min_rtt_nom_idx")) != NULL) {
        min_rtt_nom_idx = strtoul(s, NULL, 0);
    }
    if ((s = lookup_env_parameter("ddr_max_rtt_nom_idx")) != NULL) {
        max_rtt_nom_idx = strtoul(s, NULL, 0);
    }
    hw_rd_leveling_overrides->min_rodt_ctl = min_rodt_ctl;
    hw_rd_leveling_overrides->max_rodt_ctl = max_rodt_ctl;
    hw_rd_leveling_overrides->min_rtt_nom_idx = min_rtt_nom_idx;
    hw_rd_leveling_overrides->max_rtt_nom_idx = max_rtt_nom_idx;

    int maximum_adjacent_rlevel_delay_increment = custom_lmc_config->maximum_adjacent_rlevel_delay_increment;
    if ((s = lookup_env_parameter("ddr_maximum_adjacent_rlevel_delay_increment")) != NULL) {
        maximum_adjacent_rlevel_delay_increment = strtoul(s, NULL, 0);
    }
    hw_rd_leveling_overrides->maximum_adjacent_rlevel_delay_increment = maximum_adjacent_rlevel_delay_increment;

    hw_rd_leveling_overrides->override_compensation = 0;
    if ((s = lookup_env_parameter("ddr__ptune")) != NULL) {
        hw_rd_leveling_overrides->saved_ddr__ptune = strtoul(s, NULL, 0);
        hw_rd_leveling_overrides->override_compensation = 1;
    }
    if ((s = lookup_env_parameter("ddr__ntune")) != NULL) {
        hw_rd_leveling_overrides->saved_ddr__ntune = strtoul(s, NULL, 0);
        hw_rd_leveling_overrides->override_compensation = 1;
    }
}


#ifdef ENABLE_CUSTOM_RLEVEL_TABLE

int
Set_Hard_Coded_RD_LVL_Settings(bdk_node_t node, int ddr_interface_num,
                               dram_init_data_t *init_data)
{
    char part_number[21];
    int i;
    bdk_lmcx_rlevel_rankx_t lmc_rlevel_rank;
    int rank_mask =         init_data->refs.rank_mask;
    uint64_t ddr_hertz =    init_data->refs.ddr_hertz;
    int disable_hw_read_lvl = 0;
    const ddr_custom_config_t *custom_lmc_config = &init_data->ddr_configruation->custom_lmc_config;

    /* Check for hard-coded read-leveling settings */
    get_dimm_part_number(part_number, node, &dimm_config_table[0], 0);
    for (rankx = 0; rankx < 4; rankx++) {
        if (!(rank_mask & (1 << rankx)))
            continue;

        lmc_rlevel_rank.u = BDK_CSR_READ(node, BDK_LMCX_RLEVEL_RANKX(ddr_interface_num, rankx));

        i = 0;
        while (custom_lmc_config->rlevel_table[i].part != NULL) {
            debug_print("DIMM part number:\"%s\", SPD: \"%s\"\n", custom_lmc_config->rlevel_table[i].part, part_number);
            if ((strcmp(part_number, custom_lmc_config->rlevel_table[i].part) == 0)
                && (_abs(custom_lmc_config->rlevel_table[i].speed - 2*ddr_hertz/(1000*1000)) < 10 ))
            {
                ddr_print("Using hard-coded read leveling for DIMM part number: \"%s\"\n", part_number);
                lmc_rlevel_rank.u = custom_lmc_config->rlevel_table[i].rlevel_rank[ddr_interface_num][rankx];
                DRAM_CSR_WRITE(node, BDK_LMCX_RLEVEL_RANKX(ddr_interface_num, rankx), lmc_rlevel_rank.u);
                lmc_rlevel_rank.u = BDK_CSR_READ(node, BDK_LMCX_RLEVEL_RANKX(ddr_interface_num, rankx));
                display_RL(node, ddr_interface_num, lmc_rlevel_rank, rankx);

                //rlevel_debug_loops = 0; /* Disable h/w read-leveling */
                disable_hw_read_lvl = 1;
                break;
            }
            ++i;
        }
    }

    return (disable_hw_read_lvl) ? 1 : 0;
}
#endif /* ENABLE_CUSTOM_RLEVEL_TABLE */

static int
wait_for_rlevel_status_complete(bdk_node_t node, int ddr_interface_num, int rankx)
{
    int is_cn8xxx = bdk_is_model(OCTEONTX_CN8XXX);
    int result = 0;
    int status;

    if (bdk_is_platform(BDK_PLATFORM_ASIM))
        return 0;

    uint64_t timeout_usec = 1000000;
    uint64_t done =
        bdk_clock_get_count(BDK_CLOCK_TIME) + (uint64_t)timeout_usec *
        bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME) / 1000000;

    while (1) {
        if (is_cn8xxx) {
            bdk_lmcx_rlevel_rankx_t rlevel_rankx;
            rlevel_rankx.u = BDK_CSR_READ(node, BDK_LMCX_RLEVEL_RANKX(ddr_interface_num, rankx));
            status = rlevel_rankx.s.status & 3;
        } else {
            bdk_lmcx_rlevel_ctl_t rlevel_ctl;
            rlevel_ctl.u = BDK_CSR_READ(node, BDK_LMCX_RLEVEL_CTL(ddr_interface_num));
            status = (rlevel_ctl.u >> (40 + (rankx * 2))) & 3;
        }
        if (status == 3)
            break;
        else if (bdk_clock_get_count(BDK_CLOCK_TIME) > done) {
            result = -1;
            break;
        } else
            bdk_thread_yield();
    } /* while (1) */

    if (result) {
        error_print("N%d.LMC%d: Timeout waiting for Read-leveling sequence on rank %d\n",
                    node, ddr_interface_num, rankx);
    }
    return result;
}

int
Run_Bitmask_Interpretation(bdk_node_t node, int ddr_interface_num,
                           dram_init_data_t *init_data,
                           dram_overrides_t *overrides,
                           rlevel_struct_t *rlevel,
                           int rodt_ctl, int rankx)
{
    bdk_lmcx_rlevel_rankx_t lmc_rlevel_rank;
    int ecc_ena =                   init_data->refs.use_ecc;
    int spd_rdimm =                 init_data->refs.spd_rdimm;
    int ddr_interface_bytemask =    init_data->refs.ddr_interface_bytemask;
    int rlevel_bitmask_errors = 0;
    int byte_idx;
    int disable_rl_pbm_counting =   overrides->hw_rlevel.disable_rl_pbm_counting;
    int rlevel_separate_ab =        overrides->hw_rlevel.rlevel_separate_ab;

    rlevel_bitmask_t *rlevel_bitmask = rlevel->rlevel_data.rlevel_bitmask;

    lmc_rlevel_rank.u = BDK_CSR_READ(node, BDK_LMCX_RLEVEL_RANKX(ddr_interface_num, rankx));

    // rlevel_separate_ab - process A-side vs B-side separately
    // NOTE: This will always work, but requires running read-leveling twice.
    //       It may be needed if an RDIMM register does not support inversion,
    //       which would cause "change_rdimm_mpr_pattern()" to fail.
    if (rlevel_separate_ab && spd_rdimm) {
        bdk_lmcx_rlevel_rankx_t lmc_rlevel_rank_aside;
        bdk_lmcx_modereg_params0_t lmc_modereg_params0;

        /* A-side */
        lmc_modereg_params0.u = BDK_CSR_READ(node, BDK_LMCX_MODEREG_PARAMS0(ddr_interface_num));
        lmc_modereg_params0.s.mprloc = 0; /* MPR Page 0 Location 0 */
        DRAM_CSR_WRITE(node, BDK_LMCX_MODEREG_PARAMS0(ddr_interface_num), lmc_modereg_params0.u);

        /* Clear read-level delays */
        DRAM_CSR_WRITE(node, BDK_LMCX_RLEVEL_RANKX(ddr_interface_num, rankx), 0);

        /* read-leveling */
        perform_octeontx_ddr_sequence(node, (1 << rankx), ddr_interface_num, 1);
        wait_for_rlevel_status_complete(node, ddr_interface_num, rankx);
        lmc_rlevel_rank.u = BDK_CSR_READ(node, BDK_LMCX_RLEVEL_RANKX(ddr_interface_num, rankx));

        lmc_rlevel_rank_aside.u = lmc_rlevel_rank.u;

        for (byte_idx = 0; byte_idx < 4; byte_idx++) // byte-lanes 0-3
            rlevel_bitmask[byte_idx].bm =
                octeontx_read_rlevel_dbg(node, ddr_interface_num, byte_idx);

        rlevel_bitmask[8].bm = // byte-lane 8
            octeontx_read_rlevel_dbg(node, ddr_interface_num, 8);
        /* A-side complete */

        /* B-side */
        lmc_modereg_params0.u = BDK_CSR_READ(node, BDK_LMCX_MODEREG_PARAMS0(ddr_interface_num));
        lmc_modereg_params0.s.mprloc = 3; /* MPR Page 0 Location 3 */
        DRAM_CSR_WRITE(node, BDK_LMCX_MODEREG_PARAMS0(ddr_interface_num), lmc_modereg_params0.u);

        /* Clear read-level delays */
        DRAM_CSR_WRITE(node, BDK_LMCX_RLEVEL_RANKX(ddr_interface_num, rankx), 0);

        /* read-leveling */
        perform_octeontx_ddr_sequence(node, (1 << rankx), ddr_interface_num, 1);
        wait_for_rlevel_status_complete(node, ddr_interface_num, rankx);
        lmc_rlevel_rank.u = BDK_CSR_READ(node, BDK_LMCX_RLEVEL_RANKX(ddr_interface_num, rankx));

        for (byte_idx = 4; byte_idx < 8; byte_idx++) // byte-lanes 4-7
            rlevel_bitmask[byte_idx].bm =
                octeontx_read_rlevel_dbg(node, ddr_interface_num, byte_idx);
        /* B-side complete */

        for (byte_idx = 0; byte_idx < 4; byte_idx++) {
            update_rlevel_rank_struct(&lmc_rlevel_rank, byte_idx,
                                      get_rlevel_rank_struct(&lmc_rlevel_rank_aside, byte_idx));
        }
        update_rlevel_rank_struct(&lmc_rlevel_rank, 8,
                                  get_rlevel_rank_struct(&lmc_rlevel_rank_aside, 8));
        /* ECC A-side */

        lmc_modereg_params0.u = BDK_CSR_READ(node, BDK_LMCX_MODEREG_PARAMS0(ddr_interface_num));
        lmc_modereg_params0.s.mprloc = 0; /* MPR Page 0 Location 0 */
        DRAM_CSR_WRITE(node, BDK_LMCX_MODEREG_PARAMS0(ddr_interface_num), lmc_modereg_params0.u);

    } /* if (rlevel_separate_ab && spd_rdimm) */
    else {
        /* Clear read-level delays */
        DRAM_CSR_WRITE(node, BDK_LMCX_RLEVEL_RANKX(ddr_interface_num, rankx), 0);

        /* read-leveling */
        perform_octeontx_ddr_sequence(node, (1 << rankx), ddr_interface_num, 1);
        wait_for_rlevel_status_complete(node, ddr_interface_num, rankx);
        lmc_rlevel_rank.u = BDK_CSR_READ(node, BDK_LMCX_RLEVEL_RANKX(ddr_interface_num, rankx));

        for (byte_idx = 0; byte_idx < (8+ecc_ena); ++byte_idx) {
            if (ddr_interface_bytemask & (1 << byte_idx)) {
                rlevel_bitmask[byte_idx].bm =
                    octeontx_read_rlevel_dbg(node, ddr_interface_num, byte_idx);
            }
        }
    }

    /*
     * Evaluate the quality of the read-leveling delays from the bitmasks.
     * Also save off a software computed read-leveling mask that may be
     * used later to qualify the delay results from Octeon.
     */
    for (byte_idx = 0; byte_idx < (8+ecc_ena); ++byte_idx) {
        int bmerr;
        if (!(ddr_interface_bytemask & (1 << byte_idx)))
            continue;
        bmerr = validate_rlevel_bitmask(&(rlevel_bitmask[byte_idx]));
        rlevel_bitmask[byte_idx].errs = bmerr;
        rlevel_bitmask_errors += bmerr;

#if PERFECT_BITMASK_COUNTING
        if (!disable_rl_pbm_counting) {
            int pbm_rodt_skip = overrides->hw_rlevel.pbm_rodt_skip;
            perfect_counts_t *rank_perfect_counts, *rodt_perfect_counts;
            rank_perfect_counts = rlevel->rlevel_data.rank_perfect_counts;
            rodt_perfect_counts = &(rlevel->rlevel_data.rodt_perfect_counts);
            if (!bmerr) { // count only the "perfect" bitmasks
                // FIXME: for now, simple filtering: do NOT count PBMs for RODTs in skip mask
                if ((1U << rodt_ctl) & pbm_rodt_skip)
                    continue;
                // FIXME: could optimize this a bit?
                int delay = get_rlevel_rank_struct(&lmc_rlevel_rank, byte_idx);
                if (rank_perfect_counts[rankx].count[byte_idx][delay] < 255)
                    rank_perfect_counts[rankx].count[byte_idx][delay] += 1;
                rank_perfect_counts[rankx].mask[byte_idx] |= (1UL << delay);
                if (rodt_perfect_counts->count[byte_idx][delay] < 255)
                    rodt_perfect_counts->count[byte_idx][delay] += 1;
                rodt_perfect_counts->mask[byte_idx] |= (1UL << delay);
            }
        }
#endif /* PERFECT_BITMASK_COUNTING */

    } /* for (byte_idx = 0; byte_idx < (8+ecc_ena); ++byte_idx) */

    /* Set delays for unused bytes to match byte 0. */
    for (byte_idx = 1; byte_idx < 9; ++byte_idx) {
        if (ddr_interface_bytemask & (1 << byte_idx))
            continue;
        update_rlevel_rank_struct(&lmc_rlevel_rank, byte_idx,
                                  get_rlevel_rank_struct(&lmc_rlevel_rank, 0));
    }

    /* Save a copy of the byte delays in physical
       order for sequential evaluation. */
    unpack_rlevel_settings(ddr_interface_bytemask, ecc_ena,
                           rlevel->rlevel_data.rlevel_byte, lmc_rlevel_rank);

    return rlevel_bitmask_errors;

} // end bitmask interpretation block

int Calculate_NonSequential_Errors(dram_init_data_t *init_data,
                                    dram_overrides_t *overrides,
                                    rlevel_struct_t *rlevel)
{
    int maximum_adjacent_rlevel_delay_increment = overrides->hw_rlevel.maximum_adjacent_rlevel_delay_increment;
    int ddr_interface_bytemask =    init_data->refs.ddr_interface_bytemask;
    int spd_dimm_type =             init_data->refs.spd_dimm_type;
    int ecc_ena =                   init_data->refs.use_ecc;
    int rlevel_nonseq_errors = 0;
    int reg_adj_delay_limit = CN8_OR_CN9(1, 5); // adjust for RL delay bits // FIXME: CN9 speed-relative?

    rlevel_byte_data_t *rlevel_byte = rlevel->rlevel_data.rlevel_byte;

    if ((ddr_interface_bytemask & 0xff) == 0xff) {
        /* Evaluate delay sequence across the whole range of bytes for standard dimms. */
        if ((spd_dimm_type == 1) || (spd_dimm_type == 5)) { /* 1=RDIMM, 5=Mini-RDIMM */

            // compute delay diff from ECC (byte 4) to byte 5, ie across Register
            int register_adjacent_delay = _abs(rlevel_byte[4].delay - rlevel_byte[5].delay);

            /* Registered dimm topology routes from the center. */
            rlevel_nonseq_errors +=
                nonsequential_delays(rlevel_byte, 0, 3+ecc_ena,
                                     maximum_adjacent_rlevel_delay_increment);
            rlevel_nonseq_errors +=
                nonsequential_delays(rlevel_byte, 5, 7+ecc_ena,
                                     maximum_adjacent_rlevel_delay_increment);
            // byte 5 sqerrs never gets cleared for RDIMMs
            rlevel_byte[5].sqerrs = 0;

            /* Assess proximity of bytes on opposite sides of register */
            if (register_adjacent_delay > reg_adj_delay_limit) {
                int adj_err = (register_adjacent_delay - reg_adj_delay_limit) * RLEVEL_ADJACENT_DELAY_ERROR;
                // update error total
                rlevel_nonseq_errors += adj_err;

                // update ECC (byte 4) error
                rlevel_byte[4].sqerrs += adj_err;
            }
        }
        if ((spd_dimm_type == 2) || (spd_dimm_type == 6)) { /* 2=UDIMM, 6=Mini-UDIMM */
            /* Unbuffered dimm topology routes from end to end. */
            // BUT...
            // there may be a big gap between the ECC byte and byte 4, so break it up...
            rlevel_nonseq_errors +=
                nonsequential_delays(rlevel_byte, 0, 3+ecc_ena,
                                     maximum_adjacent_rlevel_delay_increment);
            rlevel_nonseq_errors +=
                nonsequential_delays(rlevel_byte, 5, 7+ecc_ena,
                                     maximum_adjacent_rlevel_delay_increment);
        }
    } else {
        rlevel_nonseq_errors +=
            nonsequential_delays(rlevel_byte, 0, 3+ecc_ena,
                                 maximum_adjacent_rlevel_delay_increment);
    }

    return rlevel_nonseq_errors;
}

int
Calculate_RD_Leveling_Errors(bdk_node_t node, int ddr_interface_num,
                             dram_init_data_t *init_data,
                             dram_overrides_t *overrides,
                             rlevel_struct_t *rlevel,
                             int rlevel_bitmask_errors,
                             int rankx)
{
    int repetition;
    int max_non_seq_repetitions = 1;

    int ecc_ena =                           init_data->refs.use_ecc;
    int dram_width =                        init_data->refs.dram_width;
    int ddr_interface_bytemask =            init_data->refs.ddr_interface_bytemask;
    int disable_sequential_delay_check =    overrides->init.disable_sequential_delay_check;
    int ddr_rlevel_compute =                overrides->hw_rlevel.ddr_rlevel_compute;
    int rlevel_samples =                    overrides->hw_rlevel.rlevel_samples;
    rlevel_byte_data_t *rlevel_byte =       rlevel->rlevel_data.rlevel_byte;
    rlevel_bitmask_t *rlevel_bitmask =      rlevel->rlevel_data.rlevel_bitmask;
    int rlevel_nonseq_errors = 0;
    int rlevel_rank_errors = 0;


    bdk_lmcx_rlevel_rankx_t lmc_rlevel_rank;
    bdk_lmcx_rlevel_ctl_t rlevel_ctl;

    lmc_rlevel_rank.u = BDK_CSR_READ(node, BDK_LMCX_RLEVEL_RANKX(ddr_interface_num, rankx));
    rlevel_ctl.u = overrides->hw_rlevel.rlevel_ctl;

    if (ddr_rlevel_compute)
        max_non_seq_repetitions = 2;

    for (repetition = 0; repetition < max_non_seq_repetitions; repetition++) {
        rlevel_nonseq_errors  = 0;


        if (!disable_sequential_delay_check && !(dram_width == 16)) {
            rlevel_nonseq_errors = Calculate_NonSequential_Errors(init_data, overrides, rlevel);

        } /* if (! disable_sequential_delay_check) */

        rlevel_rank_errors = rlevel_bitmask_errors + rlevel_nonseq_errors;

        // print original sample here only if we are not really averaging or picking best
        // also do not print if we were redoing the NONSEQ score for using COMPUTED
        if (repetition == 0 && ((rlevel_samples < 2) || dram_is_verbose(VBL_DEV2))) {
            display_RL_BM(node, ddr_interface_num, rankx, rlevel_bitmask, ecc_ena);
            display_RL_BM_scores(node, ddr_interface_num, rankx, rlevel_bitmask, ecc_ena);
            display_RL_SEQ_scores(node, ddr_interface_num, rankx, rlevel_byte, ecc_ena);
            display_RL_with_score(node, ddr_interface_num, lmc_rlevel_rank, rankx, rlevel_rank_errors);
        }

        if (ddr_rlevel_compute) {
            if (repetition == 0) {
                int byte_idx;
                for (byte_idx = 0; byte_idx < (8+ecc_ena); ++byte_idx) {
                    if (!(ddr_interface_bytemask & (1 << byte_idx)))
                        continue;
                    update_rlevel_rank_struct(&lmc_rlevel_rank, byte_idx,
                                              compute_rlevel_delay(rlevel_bitmask[byte_idx].mstart,
                                                                   rlevel_bitmask[byte_idx].width,
                                                                   rlevel_ctl));
                }

                /* Override the copy of byte delays with the computed results. */
                unpack_rlevel_settings(ddr_interface_bytemask, ecc_ena, rlevel_byte, lmc_rlevel_rank);

            } else {
                /* now print this if already printed the original sample */
                if ((rlevel_samples < 2) || dram_is_verbose(VBL_DEV2)) {
                    display_RL_with_computed(node, ddr_interface_num,
                                             lmc_rlevel_rank, rankx,
                                             rlevel_rank_errors);
                }
            }
        }
    }

    return rlevel_rank_errors;
}

void
Perform_Read_Leveling_for_an_RTT_NOM_value(bdk_node_t node,  int ddr_interface_num,
                                           dram_init_data_t *init_data,
                                           dram_overrides_t *overrides,
                                           rlevel_struct_t *rlevel)
{
    int rank_mask =                     init_data->refs.rank_mask;
    int ecc_ena =                       init_data->refs.use_ecc;
    int ddr_interface_bytemask =        init_data->refs.ddr_interface_bytemask;
    int dyn_rtt_nom_mask =              init_data->terms.dyn_rtt_nom_mask;
    int default_rodt_ctl =              init_data->terms.default_rodt_ctl;
    impedence_values_t *imp_values =    init_data->imp_values;

    int rlevel_samples =                overrides->hw_rlevel.rlevel_samples;
    int max_rtt_nom_idx =               overrides->hw_rlevel.max_rtt_nom_idx;
    int min_rtt_nom_idx =               overrides->hw_rlevel.min_rtt_nom_idx;
    int max_rodt_ctl =                  overrides->hw_rlevel.max_rodt_ctl;
    int min_rodt_ctl =                  overrides->hw_rlevel.min_rodt_ctl;
    int disable_rl_pbm_counting =       overrides->hw_rlevel.disable_rl_pbm_counting;

    int print_nom_ohms;
    int rtt_idx;
    int rodt_ctl;
    int rtt_nom;
    int rankx;
    int rlevel_rodt_errors = 0;
    bdk_lmcx_modereg_params1_t lmc_modereg_params1;
    bdk_lmcx_comp_ctl2_t lmc_comp_ctl2;
    bdk_lmcx_rlevel_rankx_t lmc_rlevel_rank;
    rlevel_scoreboard_t *rlevel_scoreboard;
    rlevel_scoreboard = &(rlevel->rlevel_scoreboard);

    lmc_modereg_params1.u = BDK_CSR_READ(node, BDK_LMCX_MODEREG_PARAMS1(ddr_interface_num));

    for (rtt_idx = min_rtt_nom_idx; rtt_idx <= max_rtt_nom_idx; ++rtt_idx) {
        rtt_nom = imp_values->rtt_nom_table[rtt_idx];

        /* When the read ODT mask is zero the dyn_rtt_nom_mask is
           zero than RTT_NOM will not be changing during
           read-leveling.  Since the value is fixed we only need
           to test it once. */
        if (dyn_rtt_nom_mask == 0) {
            print_nom_ohms = -1; // flag not to print NOM ohms
            /* if (rtt_idx != min_rtt_nom_idx)
                continue; */
        }
        else {
            for (int i = 0; i < 4; i++) {
                if (dyn_rtt_nom_mask & (1 << i))
                    INSRT_NOM(&lmc_modereg_params1.u, i, rtt_nom);
            }
            // FIXME? rank 0 ohms always for the printout?
            print_nom_ohms = imp_values->rtt_nom_ohms[EXTR_NOM(lmc_modereg_params1.u, 0)];
        }

        DRAM_CSR_WRITE(node, BDK_LMCX_MODEREG_PARAMS1(ddr_interface_num), lmc_modereg_params1.u);
        if ((print_nom_ohms >= 0) && dram_is_verbose(VBL_TME)) {
            int rtt_noms[4];
            for (int i = 0; i < 4; i++)
                rtt_noms[i] = EXTR_NOM(lmc_modereg_params1.u, i);
            printf("\n");
            printf("RTT_NOM     %3d, %3d, %3d, %3d ohms           :  %x,%x,%x,%x\n",
                   imp_values->rtt_nom_ohms[rtt_noms[3]],
                   imp_values->rtt_nom_ohms[rtt_noms[2]],
                   imp_values->rtt_nom_ohms[rtt_noms[1]],
                   imp_values->rtt_nom_ohms[rtt_noms[0]],
                   rtt_noms[3], rtt_noms[2], rtt_noms[1], rtt_noms[0]);
        }
        perform_ddr_init_sequence(node, rank_mask, ddr_interface_num);

        // Try RANK outside RODT to rearrange the output...
        for (rankx = 0; rankx < 4; rankx++) {
            int byte_idx;

            int sample_loops, max_samples;
            int rlevel_rank_errors, rlevel_bitmask_errors; //, rlevel_nonseq_errors;
            int rlevel_best_rank_score;

            //consolidate byte and bitmask data
            rlevel_byte_data_t *rlevel_byte;
            rlevel_bitmask_t *rlevel_bitmask;
            rlevel_byte = rlevel->rlevel_data.rlevel_byte;
            rlevel_bitmask = rlevel->rlevel_data.rlevel_bitmask;

            if (!(rank_mask & (1 << rankx)))
                continue;

            for (rodt_ctl = max_rodt_ctl; rodt_ctl >= min_rodt_ctl; --rodt_ctl) {
                rlevel_best_rank_score = DEFAULT_BEST_RANK_SCORE;
                rlevel_rodt_errors = 0;

                lmc_comp_ctl2.u = BDK_CSR_READ(node, BDK_LMCX_COMP_CTL2(ddr_interface_num));
                lmc_comp_ctl2.s.rodt_ctl = rodt_ctl;
                DRAM_CSR_WRITE(node, BDK_LMCX_COMP_CTL2(ddr_interface_num), lmc_comp_ctl2.u);
                lmc_comp_ctl2.u = BDK_CSR_READ(node, BDK_LMCX_COMP_CTL2(ddr_interface_num));
                bdk_wait_usec(1); /* Give it a little time to take affect */

                VB_PRT(VBL_DEV2, "%-45s : 0x%x (%d ohms)\n", "Read ODT_CTL",
                       lmc_comp_ctl2.s.rodt_ctl, imp_values->rodt_ohms[lmc_comp_ctl2.s.rodt_ctl]);

                memset(rlevel_byte, 0, sizeof(rlevel_byte_data_t)*9);

#if PERFECT_BITMASK_COUNTING
                if (!disable_rl_pbm_counting) {
                    memset(&rlevel->rlevel_data.rodt_perfect_counts, 0, sizeof(perfect_counts_t));
                }
#endif /* PERFECT_BITMASK_COUNTING */

                // when iter RODT is the target RODT, take more samples...
                max_samples = rlevel_samples;
                if (rodt_ctl == default_rodt_ctl)
                    max_samples += rlevel_samples + 1;

	bdk_lmcx_rlevel_ctl_t           rlevel_ctl;
	bdk_lmcx_modereg_params0_t lmc_modereg_params0;
	int pattern;
	for (pattern = 1; pattern < 3; pattern++) {
		rlevel_ctl.u = BDK_CSR_READ(node, BDK_LMCX_RLEVEL_CTL(ddr_interface_num));
		lmc_modereg_params0.u = BDK_CSR_READ(node, BDK_LMCX_MODEREG_PARAMS0(ddr_interface_num));
		switch (pattern) {
			case 0:
				rlevel_ctl.s.pattern = 0x55;
				lmc_modereg_params0.s.mprloc = 0; /* MPR Page 0 Location 1, Pattern = 0x55  */
				break;
			case 1:
				rlevel_ctl.s.pattern = 0x33;
				lmc_modereg_params0.s.mprloc = 1; /* MPR Page 0 Location 1, Pattern = 0x33 */
				break;
			case 2:
				rlevel_ctl.s.pattern = 0x0f;
				lmc_modereg_params0.s.mprloc = 2; /* MPR Page 0 Location 2, Pattern = 0x0f */
				break;
		}
		VB_PRT(VBL_DEV2, "Set pattern to 0x%02x, mprloc = %i\n", rlevel_ctl.s.pattern, lmc_modereg_params0.s.mprloc);

		DRAM_CSR_WRITE(node, BDK_LMCX_RLEVEL_CTL(ddr_interface_num), rlevel_ctl.u);
		DRAM_CSR_WRITE(node, BDK_LMCX_MODEREG_PARAMS0(ddr_interface_num), lmc_modereg_params0.u);

		max_samples = 4;

                for (sample_loops = 0; sample_loops < max_samples; sample_loops++) {
                    rlevel_bitmask_errors = 0;

                    //Zero out bitmask structure
                    memset(rlevel_bitmask, 0, sizeof(rlevel_bitmask_t)*9);

                    rlevel_bitmask_errors =
                        Run_Bitmask_Interpretation(node, ddr_interface_num, init_data,
                                                   overrides, rlevel, rodt_ctl, rankx);

                    rlevel_rank_errors =
                        Calculate_RD_Leveling_Errors(node, ddr_interface_num, init_data,
                                                     overrides, rlevel, rlevel_bitmask_errors, rankx);

                    // if it is a better (lower) score, then  keep it
                    if (rlevel_rank_errors < rlevel_best_rank_score) {
                        rlevel_best_rank_score = rlevel_rank_errors;

                        // save the new best delays and best errors
                        for (byte_idx = 0; byte_idx < (8+ecc_ena); ++byte_idx) {
                            rlevel_byte[byte_idx].best = rlevel_byte[byte_idx].delay;
                            rlevel_byte[byte_idx].bestsq = rlevel_byte[byte_idx].sqerrs;

                            // save bitmasks and their scores as well
                            // xlate UNPACKED index to PACKED index to get from rlevel_bitmask
                            VB_PRT(VBL_DEV3, "SAVE: bitmask[%d] to byte[%d]\n",
                                   XUP(byte_idx, !!ecc_ena), byte_idx);
                            rlevel_byte[byte_idx].bm     = rlevel_bitmask[XUP(byte_idx, !!ecc_ena)].bm;
                            rlevel_byte[byte_idx].bmerrs = rlevel_bitmask[XUP(byte_idx, !!ecc_ena)].errs;
                        }
                    }
                    rlevel_rodt_errors += rlevel_rank_errors;

                } /* for (sample_loops = 0; sample_loops < max_samples; sample_loops++) */
	}
                /* We recorded the best score across the averaging loops */
                rlevel_scoreboard->scoreboard[rtt_nom][rodt_ctl][rankx].score = rlevel_best_rank_score;

                /* Restore the delays from the best fields that go with the best score */
                for (byte_idx = 0; byte_idx < 9; ++byte_idx) {
                    rlevel_byte[byte_idx].delay = rlevel_byte[byte_idx].best;
                    rlevel_byte[byte_idx].sqerrs = rlevel_byte[byte_idx].bestsq;
                }

                lmc_rlevel_rank.u = BDK_CSR_READ(node, BDK_LMCX_RLEVEL_RANKX(ddr_interface_num, rankx));
                pack_rlevel_settings(ddr_interface_bytemask, ecc_ena, rlevel_byte, &lmc_rlevel_rank);

                if (rlevel_samples > 1) {
                    // restore the "best" bitmasks and their scores for printing
                    for (byte_idx = 0; byte_idx < 9; ++byte_idx) {
                        if ((ddr_interface_bytemask & (1 << byte_idx)) == 0)
                            continue;
                        // xlate PACKED index to UNPACKED index to get from rlevel_byte
                        VB_PRT(VBL_DEV3, "RESTORE: byte[%d] to bitmask[%d]\n",
                               XPU(byte_idx, !!ecc_ena), byte_idx);
                        rlevel_bitmask[byte_idx].bm   = rlevel_byte[XPU(byte_idx, !!ecc_ena)].bm;
                        rlevel_bitmask[byte_idx].errs = rlevel_byte[XPU(byte_idx, !!ecc_ena)].bmerrs;
                    }
                    // print bitmasks/scores here only for DEV // FIXME? lower VBL?
                    if (dram_is_verbose(VBL_DEV2)) {
                        display_RL_BM(node, ddr_interface_num, rankx, rlevel_bitmask, ecc_ena);
                        display_RL_BM_scores(node, ddr_interface_num, rankx, rlevel_bitmask, ecc_ena);
                        display_RL_SEQ_scores(node, ddr_interface_num, rankx, rlevel_byte, ecc_ena);

                        display_RL_with_RODT(node, ddr_interface_num, lmc_rlevel_rank, rankx,
                                             rlevel_scoreboard->scoreboard[rtt_nom][rodt_ctl][rankx].score,
                                             print_nom_ohms, imp_values->rodt_ohms[rodt_ctl],
                                             WITH_RODT_BESTSCORE);
                        ddr_print("-----------\n");
                    }
                } /* if (rlevel_samples > 1) */

                rlevel_scoreboard->scoreboard[rtt_nom][rodt_ctl][rankx].setting = lmc_rlevel_rank.u;

#if PERFECT_BITMASK_COUNTING
                // print out the PBMs for the current RODT
                if (!disable_rl_pbm_counting) {
#if PRINT_PERFECT_COUNTS
                    int pbm_rodt_skip = overrides->hw_rlevel.pbm_rodt_skip;
                    perfect_counts_t *rodt_perfect_counts;
                    rodt_perfect_counts = &(rlevel->rlevel_data.rodt_perfect_counts);

                    // FIXME: change verbosity level after debug complete...

                    for (int byte_idx = 0; byte_idx < 9; byte_idx++) {
                        if ((1U << rodt_ctl) & pbm_rodt_skip) // FIXME: PBM skip for RODTs in mask
                            continue;
                        uint64_t temp_mask = rodt_perfect_counts->mask[byte_idx];
                        int num_values = __builtin_popcountl(temp_mask);
                        int i = __builtin_ffsl(temp_mask) - 1;

                        VB_PRT(VBL_DEV2, "N%d.LMC%d.R%d: PERFECT: RODT %3d: Byte %d: mask 0x%02lx (%d): ",
                               node, ddr_interface_num, rankx,
                               imp_values->rodt_ohms[rodt_ctl],
                               byte_idx, temp_mask >> i, num_values);
                        while (temp_mask != 0) {
                            i = __builtin_ffsl(temp_mask) - 1;
                            VB_PRT(VBL_DEV2, "%2d(%2d) ", i, rodt_perfect_counts->count[byte_idx][i]);
                            temp_mask &= ~(1UL << i);
                        } /* while (temp_mask != 0) */
                        VB_PRT(VBL_DEV2, "\n");
                    }
#endif /* PRINT_PERFECT_COUNTS */
                }
#endif /* PERFECT_BITMASK_COUNTING */

            } /* for (rodt_ctl = max_rodt_ctl; rodt_ctl >= min_rodt_ctl; --rodt_ctl) */
        } /* for (rankx = 0; rankx < 4; rankx++) */

    } /*  for (rtt_idx=min_rtt_nom_idx; rtt_idx<max_rtt_nom_idx; ++rtt_idx) */
}

void
Evaluate_RLEVEL_Scoreboard_for_AUTO_Settings(bdk_node_t node, int ddr_interface_num,
                                            dram_init_data_t *init_data,
                                            dram_overrides_t *overrides,
                                            rlevel_scoreboard_t *rlevel_scoreboard)
{
    int dyn_rtt_nom_mask =      init_data->terms.dyn_rtt_nom_mask;
    uint8_t *default_rtt_nom =  init_data->terms.default_rtt_nom;
    int ddr_rtt_nom_auto =      init_data->terms.ddr_rtt_nom_auto;
    int ddr_rodt_ctl_auto =     init_data->terms.ddr_rodt_ctl_auto;
    int default_rodt_ctl =      init_data->terms.default_rodt_ctl;
    int rank_mask =             init_data->refs.rank_mask;
    impedence_values_t *imp_values =  init_data->imp_values;

    int min_rtt_nom_idx =       overrides->hw_rlevel.min_rtt_nom_idx;
    int max_rtt_nom_idx =       overrides->hw_rlevel.max_rtt_nom_idx;
    int min_rodt_ctl =          overrides->hw_rlevel.min_rodt_ctl;
    int max_rodt_ctl =          overrides->hw_rlevel.max_rodt_ctl;
    bdk_lmcx_modereg_params1_t lmc_modereg_params1;
    int rtt_idx;
    int rtt_nom;
    int rodt_ctl;
    int rodt_score;
    int rankx;
    int best_rodt_score = DEFAULT_BEST_RANK_SCORE; /* Start with an arbitrarily high score */
    int auto_rodt_ctl = 0;
    int auto_rtt_nom  = 0;
    int i;

    VB_PRT(VBL_DEV, "Evaluating Read-Leveling Scoreboard for AUTO settings.\n");
    for (rtt_idx = min_rtt_nom_idx; rtt_idx <= max_rtt_nom_idx; ++rtt_idx) {
        rtt_nom = imp_values->rtt_nom_table[rtt_idx];

        /* When the read ODT mask is zero the dyn_rtt_nom_mask is
           zero than RTT_NOM will not be changing during
           read-leveling.  Since the value is fixed we only need
           to test it once. */
        /* if ((dyn_rtt_nom_mask == 0) && (rtt_idx != min_rtt_nom_idx))
           continue; */

        for (rodt_ctl = max_rodt_ctl; rodt_ctl >= min_rodt_ctl; --rodt_ctl) {
            rodt_score = 0;
            for (rankx = 0; rankx < 4; rankx++) {
                if (!(rank_mask & (1 << rankx)))
                    continue;
                debug_print("rlevel_scoreboard[rtt_nom=%d][rodt_ctl=%d][rankx=%d].score:%d\n",
                    rtt_nom, rodt_ctl, rankx, rlevel_scoreboard->scoreboard[rtt_nom][rodt_ctl][rankx].score);
                rodt_score += rlevel_scoreboard->scoreboard[rtt_nom][rodt_ctl][rankx].score;
            }
            // FIXME: do we need to skip RODT rows here, like we do below in the by-RANK settings?

            /* When using automatic ODT settings use the ODT
               settings associated with the best score for
               all of the tested ODT combinations. */

            if ((rodt_score < best_rodt_score) || // always take lower score, OR
                ((rodt_score == best_rodt_score) && // take same score if RODT ohms are higher
                 (imp_values->rodt_ohms[rodt_ctl] > imp_values->rodt_ohms[auto_rodt_ctl])))
            {
                debug_print("AUTO: new best score for rodt:%d (%3d), new score:%d, previous score:%d\n",
                        rodt_ctl, imp_values->rodt_ohms[rodt_ctl], rodt_score, best_rodt_score);
                best_rodt_score = rodt_score;
                auto_rodt_ctl   = rodt_ctl;
                auto_rtt_nom    = rtt_nom;
            }
        } /* for (rodt_ctl=max_rodt_ctl; rodt_ctl>=min_rodt_ctl; --rodt_ctl) */
    } /* for (rtt_idx=min_rtt_nom_idx; rtt_idx<=max_rtt_nom_idx; ++rtt_idx) */

    lmc_modereg_params1.u = BDK_CSR_READ(node, BDK_LMCX_MODEREG_PARAMS1(ddr_interface_num));

    if (ddr_rtt_nom_auto) {
        /* Store the automatically set RTT_NOM value */
        for (i = 0; i < 4; i++) {
            if (dyn_rtt_nom_mask & (1 << i))
                INSRT_NOM(&lmc_modereg_params1.u, i, auto_rtt_nom);
        }
    }
    else {
        /* restore the manual settings to the register */
        for (i = 0; i < 4; i++) {
            INSRT_NOM(&lmc_modereg_params1.u, i, default_rtt_nom[i]);
        }
    }

    int rtt_noms[4], rtt_wrs[4], rtt_dics[4];
    for (i = 0; i < 4; i++) {
        rtt_noms[i] = EXTR_NOM(lmc_modereg_params1.u, i);
        rtt_wrs[i]  = EXTR_WR(lmc_modereg_params1.u, i);
        rtt_dics[i] = EXTR_DIC(lmc_modereg_params1.u, i);
    }

    DRAM_CSR_WRITE(node, BDK_LMCX_MODEREG_PARAMS1(ddr_interface_num), lmc_modereg_params1.u);
    VB_PRT(VBL_DEV, "RTT_NOM     %3d, %3d, %3d, %3d ohms           :  %x,%x,%x,%x\n",
           imp_values->rtt_nom_ohms[rtt_noms[3]],
           imp_values->rtt_nom_ohms[rtt_noms[2]],
           imp_values->rtt_nom_ohms[rtt_noms[1]],
           imp_values->rtt_nom_ohms[rtt_noms[0]],
           rtt_noms[3], rtt_noms[2], rtt_noms[1], rtt_noms[0]);

    VB_PRT(VBL_DEV, "RTT_WR      %3d, %3d, %3d, %3d ohms           :  %x,%x,%x,%x\n",
           imp_values->rtt_wr_ohms[rtt_wrs[3]],
           imp_values->rtt_wr_ohms[rtt_wrs[2]],
           imp_values->rtt_wr_ohms[rtt_wrs[1]],
           imp_values->rtt_wr_ohms[rtt_wrs[0]],
           rtt_wrs[3], rtt_wrs[2], rtt_wrs[1], rtt_wrs[0]);

    VB_PRT(VBL_DEV, "DIC         %3d, %3d, %3d, %3d ohms           :  %x,%x,%x,%x\n",
           imp_values->dic_ohms[rtt_dics[3]],
           imp_values->dic_ohms[rtt_dics[2]],
           imp_values->dic_ohms[rtt_dics[1]],
           imp_values->dic_ohms[rtt_dics[0]],
           rtt_dics[3], rtt_dics[2], rtt_dics[1], rtt_dics[0]);

    bdk_lmcx_modereg_params2_t lmc_modereg_params2;
    /*
     * We must read the CSR, and not depend on odt_config[odt_idx].modereg_params2,
     * since we could have overridden values with envvars.
     * NOTE: this corrects the printout, since the CSR is not written with the old values...
     */
    lmc_modereg_params2.u = BDK_CSR_READ(node, BDK_LMCX_MODEREG_PARAMS2(ddr_interface_num));

    int rtt_park[4];
    for (i = 0; i < 4; i++)
        rtt_park[i] = EXTR_PARK(lmc_modereg_params2.u, i);

    VB_PRT(VBL_DEV, "RTT_PARK    %3d, %3d, %3d, %3d ohms           :  %x,%x,%x,%x\n",
           imp_values->rtt_nom_ohms[rtt_park[3]],
           imp_values->rtt_nom_ohms[rtt_park[2]],
           imp_values->rtt_nom_ohms[rtt_park[1]],
           imp_values->rtt_nom_ohms[rtt_park[0]],
           rtt_park[3], rtt_park[2], rtt_park[1], rtt_park[0]);

    VB_PRT(VBL_DEV, "%-45s :  0x%x,0x%x,0x%x,0x%x\n", "VREF_RANGE",
           lmc_modereg_params2.s.vref_range_11,
           lmc_modereg_params2.s.vref_range_10,
           lmc_modereg_params2.s.vref_range_01,
           lmc_modereg_params2.s.vref_range_00);

    VB_PRT(VBL_DEV, "%-45s :  0x%x,0x%x,0x%x,0x%x\n", "VREF_VALUE",
           lmc_modereg_params2.s.vref_value_11,
           lmc_modereg_params2.s.vref_value_10,
           lmc_modereg_params2.s.vref_value_01,
           lmc_modereg_params2.s.vref_value_00);

    bdk_lmcx_comp_ctl2_t lmc_comp_ctl2;
    lmc_comp_ctl2.u = BDK_CSR_READ(node, BDK_LMCX_COMP_CTL2(ddr_interface_num));
    if (ddr_rodt_ctl_auto)
        lmc_comp_ctl2.s.rodt_ctl = auto_rodt_ctl;
    else
        lmc_comp_ctl2.s.rodt_ctl = default_rodt_ctl; // back to the original setting
    DRAM_CSR_WRITE(node, BDK_LMCX_COMP_CTL2(ddr_interface_num), lmc_comp_ctl2.u);
    lmc_comp_ctl2.u = BDK_CSR_READ(node, BDK_LMCX_COMP_CTL2(ddr_interface_num));
    VB_PRT(VBL_DEV, "%-45s : 0x%x (%d ohms)\n", "Read ODT_CTL",
          lmc_comp_ctl2.s.rodt_ctl, imp_values->rodt_ohms[lmc_comp_ctl2.s.rodt_ctl]);
}

////////////////// this is the start of the BEST ROW SCORE LOOP
uint64_t
Find_RLEVEL_Best_Row_Score(bdk_node_t node, int ddr_interface_num,
                           dram_init_data_t *init_data,
                           dram_overrides_t *overrides,
                           rlevel_struct_t *rlevel, int rankx)
{
    int orankx;
    int next_score;
    int rtt_idx;
    int rodt_ctl;
    int rtt_nom;
    int min_rtt_nom_idx =               overrides->hw_rlevel.min_rtt_nom_idx;
    int max_rtt_nom_idx =               overrides->hw_rlevel.max_rtt_nom_idx;
    int min_rodt_ctl =                  overrides->hw_rlevel.min_rodt_ctl;
    int max_rodt_ctl =                  overrides->hw_rlevel.max_rodt_ctl;
    //?int dyn_rtt_nom_mask =              init_data->terms.dyn_rtt_nom_mask;
    impedence_values_t *imp_values =    init_data->imp_values;
    bdk_lmcx_rlevel_ctl_t lmc_rlevel_rank;

    rlevel_best_settings_t *best;
    rlevel_scoreboard_t *rlevel_scoreboard;
    best = &(rlevel->best);
    rlevel_scoreboard = &(rlevel->rlevel_scoreboard);
    int dimm_rank_mask = rlevel->dimm_rank_mask;
    int rodt_row_skip_mask = rlevel->rodt_row_skip_mask;

    lmc_rlevel_rank.u = BDK_CSR_READ(node, BDK_LMCX_RLEVEL_RANKX(ddr_interface_num, rankx));

    for (rtt_idx = min_rtt_nom_idx; rtt_idx <= max_rtt_nom_idx; ++rtt_idx) {
        rtt_nom = imp_values->rtt_nom_table[rtt_idx];

        /* When the read ODT mask is zero the dyn_rtt_nom_mask is
           zero than RTT_NOM will not be changing during
           read-leveling.  Since the value is fixed we only need
           to test it once. */
        /* if ((dyn_rtt_nom_mask == 0) && (rtt_idx != min_rtt_nom_idx))
           continue; */

        debug_print("N%d.LMC%d.R%d: starting RTT_NOM %d\n",
                node, ddr_interface_num, rankx, rtt_nom);

        for (rodt_ctl = max_rodt_ctl; rodt_ctl >= min_rodt_ctl; --rodt_ctl) {
            int next_ohms = imp_values->rodt_ohms[rodt_ctl];

            // skip RODT rows in mask, but *NOT* rows with too high a score;
            // we will not use the skipped ones for printing or evaluating, but
            // we need to allow all the non-skipped ones to be candidates for "best"
            if (((1 << rodt_ctl) & rodt_row_skip_mask) != 0) {
                for (orankx = 0; orankx < 4; orankx++) {
                    if ((dimm_rank_mask & (1 << orankx))) {
                        next_score = rlevel_scoreboard->scoreboard[rtt_nom][rodt_ctl][orankx].score;
                        debug_print("N%d.LMC%d.R%d: SKIPPING rank %d rodt:%d (%d) with rank_score:%d\n",
                                    node, ddr_interface_num, rankx, orankx, rodt_ctl, next_ohms, next_score);
                    }
                }
                continue;
            }
            for (orankx = 0; orankx < 4; orankx++) { // this is ROFFIX-0528
                if (!(dimm_rank_mask & (1 << orankx))) // stay on the same DIMM
                    continue;

                next_score = rlevel_scoreboard->scoreboard[rtt_nom][rodt_ctl][orankx].score;

                if (next_score > best->rank_score) // always skip a higher score
                    continue;
                if (next_score == best->rank_score) { // if scores are equal
                    if (next_ohms < best->rank_ohms) // always skip lower ohms
                        continue;
                    if (next_ohms == best->rank_ohms) { // if same ohms
                        if (orankx != rankx) // always skip the other rank(s)
                            continue;
                    }
                    // else next_ohms are greater, always choose it
                }
                // else next_score is less than current best, so always choose it
                VB_PRT(VBL_DEV2, "N%d.LMC%d.R%d: new best score: rank %d, rodt %d(%3d), new best %d, previous best %d(%d)\n",
                                        node, ddr_interface_num, rankx, orankx, rodt_ctl, next_ohms, next_score,
                                        best->rank_score, best->rank_ohms);
                best->rank_score     = next_score;
                best->rank_rtt_nom   = rtt_nom;
                //best_rank_nom_ohms  = rtt_nom_ohms;
                best->rank_ctl       = rodt_ctl;
                best->rank_ohms      = next_ohms;
                best->rankx          = orankx;
                lmc_rlevel_rank.u    = rlevel_scoreboard->scoreboard[rtt_nom][rodt_ctl][orankx].setting;

            } /* for (int orankx = 0; orankx < 4; orankx++) */
        } /* for (rodt_ctl = max_rodt_ctl; rodt_ctl >= min_rodt_ctl; --rodt_ctl) */
    } /* for (rtt_idx = min_rtt_nom_idx; rtt_idx <= max_rtt_nom_idx; ++rtt_idx) */

    return lmc_rlevel_rank.u;
}
////////////////// this is the end of the BEST ROW SCORE LOOP



////////////////// this is the start of the PRINT LOOP
void RLEVEL_Print_Loop(bdk_node_t node, int ddr_interface_num,
                       dram_init_data_t *init_data,
                       dram_overrides_t *overrides,
                       rlevel_struct_t *rlevel, int rankx)
{
    int min_rtt_nom_idx =               overrides->hw_rlevel.min_rtt_nom_idx;
    int max_rtt_nom_idx =               overrides->hw_rlevel.max_rtt_nom_idx;
    int min_rodt_ctl =                  overrides->hw_rlevel.min_rodt_ctl;
    int max_rodt_ctl =                  overrides->hw_rlevel.max_rodt_ctl;
    int dyn_rtt_nom_mask =              init_data->terms.dyn_rtt_nom_mask;
    impedence_values_t *imp_values =    init_data->imp_values;
    int print_nom_ohms;
    int rtt_idx, rodt_ctl, rtt_nom;

    rlevel_best_settings_t *best =              &(rlevel->best);
    rlevel_scoreboard_t *rlevel_scoreboard =    &(rlevel->rlevel_scoreboard);
    int dimm_rank_mask =                        rlevel->dimm_rank_mask;
    int rodt_row_skip_mask =                    rlevel->rodt_row_skip_mask;
    int MAX_RANK_SCORE =                        rlevel->MAX_RANK_SCORE;

    // for pass & 1 == 0, count or print current rank, pass & 1 == 1 count or print other rank(s)
    // for pass > 1, do not count, just print
    // this is done because we want to show each ranks RODT values together, not interlaced

    // keep separate counts for ranks - pass & 1 == 0 target rank, pass & 1 == 1 other rank on DIMM
    int mask_skipped[2] = {0,0};
    int score_skipped[2] = {0,0};
    int selected_rows[2] = {0,0};
    int zero_scores[2] = {0,0};

    for (int pass = 0; pass < 4; pass++ ) {
        for (int orankx = 0; orankx < 4; orankx++) {
            if (!(dimm_rank_mask & (1 << orankx))) // stay on the same DIMM
                continue;

            if ((((pass & 1) == 0) && (orankx != rankx)) || (((pass & 1) == 1) && (orankx == rankx)))
                continue;

            for (rtt_idx = min_rtt_nom_idx; rtt_idx <= max_rtt_nom_idx; ++rtt_idx) {
                rtt_nom = imp_values->rtt_nom_table[rtt_idx];
                if (dyn_rtt_nom_mask == 0) {
                    print_nom_ohms = -1;
                    /* if (rtt_idx != min_rtt_nom_idx)
                       continue; */
                }
                else {
                    print_nom_ohms = imp_values->rtt_nom_ohms[rtt_nom];
                }

                // cycle through all the RODT values...
                for (rodt_ctl = max_rodt_ctl; rodt_ctl >= min_rodt_ctl; --rodt_ctl) {
                    bdk_lmcx_rlevel_rankx_t temp_rlevel_rank;
                    int temp_score = rlevel_scoreboard->scoreboard[rtt_nom][rodt_ctl][orankx].score;
                    temp_rlevel_rank.u = rlevel_scoreboard->scoreboard[rtt_nom][rodt_ctl][orankx].setting;

                    // skip RODT rows in mask, or rows with too high a score;
                    // we will not use them for printing or evaluating...

                    int skip_row;
                    if ((1 << rodt_ctl) & rodt_row_skip_mask) {
                        skip_row = WITH_RODT_SKIPPING;
                        if (pass < 2) ++mask_skipped[pass];
                    }
                    else if (temp_score > MAX_RANK_SCORE) {
                        skip_row = WITH_RODT_SKIPPING;
                        if (pass < 2) ++score_skipped[pass];
                    }
                    else {
                        skip_row = WITH_RODT_BLANK;
                        if (pass < 2) {
                            ++selected_rows[pass];
                            if (temp_score == 0)
                                ++zero_scores[pass];
                        }
                    }

                    // identify and print the BEST ROW when it comes up
                    if ((skip_row == WITH_RODT_BLANK) &&
                        (best->rankx == orankx) &&
                        (best->rank_rtt_nom == rtt_nom) &&
                        (best->rank_ctl == rodt_ctl))
                    {
                        skip_row = WITH_RODT_BESTROW;
                    }
                    if (pass >= 2) {
                        if (dram_is_verbose(VBL_DEV2) ||
                            (dram_is_verbose(VBL_DEV) && ((selected_rows[0] + selected_rows[1]) < 15)))
                        {
                            display_RL_with_RODT(node, ddr_interface_num, temp_rlevel_rank,
                                                 orankx, temp_score, print_nom_ohms,
                                                 imp_values->rodt_ohms[rodt_ctl], skip_row);
                        }
                    }
                } /* for (rodt_ctl = max_rodt_ctl; rodt_ctl >= min_rodt_ctl; --rodt_ctl) */
            } /* for (rtt_idx=min_rtt_nom_idx; rtt_idx<=max_rtt_nom_idx; ++rtt_idx) */
        } /* for (int orankx = 0; orankx < 4; orankx++) { */

        // at the end of pass 1, print the counts...
        if (pass == 1) {
            VB_PRT(VBL_TME, "N%d.LMC%d.R%d: RLROWS: selected %d+%d, zero_scores %d+%d, mask_skipped %d+%d, score_skipped %d+%d\n",
                   node, ddr_interface_num, rankx,
                   selected_rows[0], selected_rows[1], zero_scores[0], zero_scores[1],
                   mask_skipped[0], mask_skipped[1], score_skipped[0], score_skipped[1]);
        }

    } /* for (int pass = 0; pass < 4; pass++ ) */

}

#if PERFECT_BITMASK_COUNTING

void
Process_Perfect_Bitmasks(bdk_node_t node,  int ddr_interface_num,
                         dram_init_data_t *init_data,
                         dram_overrides_t *overrides,
                         rlevel_struct_t *rlevel, int rankx,
                         int byte_idx, int new_byte)
{
    perfect_counts_t *rank_perfect_counts =     rlevel->rlevel_data.rank_perfect_counts;
    int pbm_lowsum_limit =                      overrides->hw_rlevel.pbm_lowsum_limit;

    // Look at counts for "perfect" bitmasks (PBMs) if we had any for this byte-lane.
    uint64_t value_mask = rank_perfect_counts[rankx].mask[byte_idx];
    uint64_t temp_mask;
    int disable_rlv_bump_this_byte = 0;

    if (value_mask != 0) {
        int i, delay_count, delay_value;
        int num_values = __builtin_popcountl(value_mask);
        int sum_counts = 0;
        temp_mask = value_mask;
        i = __builtin_ffsl(temp_mask) - 1;
        VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: PERFECT: Byte %d: mask 0x%02lx (%d): ",
               node, ddr_interface_num, rankx, byte_idx, value_mask >> i,
               num_values);
        while (temp_mask != 0) {
            i = __builtin_ffsl(temp_mask) - 1;
            delay_count = rank_perfect_counts[rankx].count[byte_idx][i];
            if (!delay_count) { // FIXME: error check!!! should NOT == 0
                bdk_error("\nERROR: delay %d has no PBMs! Ignoring!\n", i);
                value_mask &= ~(1UL << i); // turn it OFF in master
            } else {
                sum_counts += delay_count;
                VB_PRT(VBL_DEV, "%2d(%2d) ", i, delay_count);
            }
            temp_mask &= ~(1UL << i);
        } /* while (temp_mask != 0) */

        delay_value = __builtin_ffsl(value_mask) - 1;
        delay_count = rank_perfect_counts[rankx].count[byte_idx][delay_value];

        i = (value_mask >> delay_value) & 0x1F; // overkill, normally only 1-4 bits

        // if sum_counts is small, treat as special and use NEW_BYTE
        if (sum_counts < pbm_lowsum_limit) {
            VB_PRT(VBL_DEV, ": LOWSUM (%2d), choose ORIG ", sum_counts);
            i = 99; // treat as special...
        }

        switch (i) {

            case 0x01 /* 00001b */:
                // allow BUMP
                break;

            case 0x1B /* 11011b */:
            case 0x13 /* 10011b */:
            case 0x0B /* 01011b */:
            case 0x03 /* 00011b */:
                delay_value += 1; // take the second
                disable_rlv_bump_this_byte = 1; // allow no BUMP
                break;

            case 0x1D /* 11101b */:
            case 0x15 /* 10101b */:
            case 0x0D /* 01101b */:
            case 0x05 /* 00101b */:
                if ((delay_count >= 5) || (sum_counts <= 5)) // test count of lowest and all
                    delay_value += 1; // take the hole
                else
                    delay_value += 2; // take the next set
                disable_rlv_bump_this_byte = 1; // allow no BUMP
                break;

            case 0x1F /* 11111b */:
            case 0x0F /* 01111b */:
            case 0x17 /* 10111b */:
            case 0x07 /* 00111b */:
                {
                    int second, third;
                    delay_value += 1; // move to the second
                    second = rank_perfect_counts[rankx].count[byte_idx][delay_value];
                    third = rank_perfect_counts[rankx].count[byte_idx][delay_value+1];
                    if ((4 * delay_count) < (second + third)) {
                        if ((second > (2 * (delay_count + third))) &&
                            (delay_count > (2 * third))) // FIXME? was 5; maybe this is enough?
                        {
                            VB_PRT(VBL_DEV, ": TOP4 ");
                            disable_rlv_bump_this_byte = 1; // allow no BUMP
                        } else {
                            VB_PRT(VBL_DEV, ": TOP2 ");
                        }
                    } else {
                        // if delay_count >= 20% of total, still choose second but allow NO bump
                        VB_PRT(VBL_DEV, ": TOP3 ");
                        disable_rlv_bump_this_byte = 1; // allow no BUMP
                    }
                }
                break;

            default: // all others...
                VB_PRT(VBL_DEV, ": ABNORMAL, choose ORIG");
                /* FALL THRU */

            case 99: // special
                delay_value = new_byte; // FIXME: choose original choice?
                disable_rlv_bump_this_byte = 1; // allow no BUMP
                break;
        }
        delay_count = rank_perfect_counts[rankx].count[byte_idx][delay_value];

        // finish printing here...
        VB_PRT(VBL_DEV, ": USING %2d (%2d) D%d\n", delay_value,
               delay_count, disable_rlv_bump_this_byte);
        new_byte = delay_value; // override with best PBM choice
    } /* if (value_mask != 0) */
    else {
        // FIXME: remove or increase VBL for this output...
        VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: PERFECT: Byte %d: ZERO PBMs, USING %d\n",
               node, ddr_interface_num, rankx, byte_idx, new_byte);
        disable_rlv_bump_this_byte = 1; // prevent ODD bump, rely on original

    } /* if (value_mask != 0) */

    // Pass back anything that might have changed to Find_Best_Byte()
    rlevel->new_byte = new_byte;
    overrides->hw_rlevel.disable_rlv_bump_this_byte = disable_rlv_bump_this_byte;
}
#endif /* PERFECT_BITMASK_COUNTING */

////////////////// this is the start of the BEST BYTE COUNTING LOOP

// NOTE: we do this next loop separately from above, because we count relative to "best_byte"
// which may have been modified by the above averaging operation...
//
// Also, the above only moves toward the average by +- 1, so that we will always have a count
// of at least 1 for the original best byte, even if all the others are further away and not counted;
// this ensures we will go back to the original if no others are counted...
// FIXME: this could cause issue if the range of values for a byte-lane are too disparate...


void Best_Byte_Counting(bdk_node_t node, int ddr_interface_num,
                        dram_init_data_t *init_data,
                        dram_overrides_t *overrides,
                        rlevel_struct_t *rlevel, int best_byte,
                        int byte_idx, int rankx)
{
    int min_rtt_nom_idx =               overrides->hw_rlevel.min_rtt_nom_idx;
    int max_rtt_nom_idx =               overrides->hw_rlevel.max_rtt_nom_idx;
    int min_rodt_ctl =                  overrides->hw_rlevel.min_rodt_ctl;
    int max_rodt_ctl =                  overrides->hw_rlevel.max_rodt_ctl;
    int disable_rank_majority =         overrides->hw_rlevel.disable_rank_majority;
    impedence_values_t *imp_values =    init_data->imp_values;
    //?int dyn_rtt_nom_mask =              init_data->terms.dyn_rtt_nom_mask;
    int rodt_row_skip_mask =            rlevel->rodt_row_skip_mask;
    int MAX_RANK_SCORE =                rlevel->MAX_RANK_SCORE;
    int dimm_rank_mask =                rlevel->dimm_rank_mask;
    rlevel_scoreboard_t *rlevel_scoreboard = &(rlevel->rlevel_scoreboard);
    rlevel_best_byte_count_results_t *count_results = &(rlevel->count_results);
    int rtt_idx, rodt_ctl, rtt_nom;
    int temp_byte;

    for (rtt_idx = min_rtt_nom_idx; rtt_idx <= max_rtt_nom_idx; ++rtt_idx) {
        rtt_nom = imp_values->rtt_nom_table[rtt_idx];

        /* if ((dyn_rtt_nom_mask == 0) && (rtt_idx != min_rtt_nom_idx))
           continue; */

        for (rodt_ctl = max_rodt_ctl; rodt_ctl >= min_rodt_ctl; --rodt_ctl) {
            bdk_lmcx_rlevel_rankx_t temp_rlevel_rank;
            int temp_score;
            for (int orankx = 0; orankx < 4; orankx++) { // count over all the ranks
                if (!(dimm_rank_mask & (1 << orankx))) // stay on the same DIMM
                    continue;
                temp_score = rlevel_scoreboard->scoreboard[rtt_nom][rodt_ctl][orankx].score;
                // skip RODT rows in mask, or rows with too high a score;
                // we will not use them for printing or evaluating...
                if (((1 << rodt_ctl) & rodt_row_skip_mask) ||
                    (temp_score > MAX_RANK_SCORE))
                {
                    continue;
                }
                temp_rlevel_rank.u = rlevel_scoreboard->scoreboard[rtt_nom][rodt_ctl][orankx].setting;
                temp_byte = get_rlevel_rank_struct(&temp_rlevel_rank, byte_idx);

                if (temp_byte == 0) // do not count it if illegal
                    continue;
                else if (temp_byte == best_byte)
                    count_results->count_same++;
                else if (temp_byte == best_byte - 1)
                    count_results->count_less++;
                else if (temp_byte == best_byte + 1)
                    count_results->count_more++;
                // else do not count anything more than 1 away from the best

                if (disable_rank_majority) // no rank counting if disabled
                    continue;
                // FIXME? count is relative to best_byte; should it be rank-based?
                if (orankx != rankx) // rank counts only on main rank
                    continue;
                else if (temp_byte == best_byte)
                    count_results->rank_same++;
                else if (temp_byte == best_byte - 1)
                    count_results->rank_less++;
                else if (temp_byte == best_byte + 1)
                    count_results->rank_more++;
            } /* for (int orankx = 0; orankx < 4; orankx++) */
        } /* for (rodt_ctl = max_rodt_ctl; rodt_ctl >= min_rodt_ctl; --rodt_ctl) */
    } /* for (rtt_idx=min_rtt_nom_idx; rtt_idx<=max_rtt_nom_idx; ++rtt_idx) */
}
////////////////// this is the end of the BEST BYTE COUNTING LOOP

////////////////// this is the start of the BEST BYTE LOOP

void Find_Best_Byte(bdk_node_t node, int ddr_interface_num,
                    dram_init_data_t *init_data,
                    dram_overrides_t *overrides,
                    rlevel_struct_t *rlevel,
                    bdk_lmcx_rlevel_rankx_t *lmc_rlevel_rank,
                    int rankx)
{
    int min_rtt_nom_idx =                   overrides->hw_rlevel.min_rtt_nom_idx;
    int max_rtt_nom_idx =                   overrides->hw_rlevel.max_rtt_nom_idx;
    int min_rodt_ctl =                      overrides->hw_rlevel.min_rodt_ctl;
    int max_rodt_ctl =                      overrides->hw_rlevel.max_rodt_ctl;
    int disable_rank_majority =             overrides->hw_rlevel.disable_rank_majority;
    int disable_sequential_delay_check =    overrides->init.disable_sequential_delay_check;
    int enable_rldelay_bump =               overrides->hw_rlevel.enable_rldelay_bump;
    int rldelay_bump_incr =                 overrides->hw_rlevel.rldelay_bump_incr;
    int disable_rl_pbm_counting =           overrides->hw_rlevel.disable_rl_pbm_counting;
    int disable_rlv_bump_this_byte = 0;
    int ecc_ena =                           init_data->refs.use_ecc;
    int dimm_count =                        init_data->refs.dimm_count;
    //?int dyn_rtt_nom_mask =                  init_data->terms.dyn_rtt_nom_mask;
    impedence_values_t *imp_values =         init_data->imp_values;
    int MAX_RANK_SCORE =                    rlevel->MAX_RANK_SCORE;
    int rodt_row_skip_mask =                rlevel->rodt_row_skip_mask;
    int dimm_rank_mask =                    rlevel->dimm_rank_mask;
    rlevel_scoreboard_t *rlevel_scoreboard = &(rlevel->rlevel_scoreboard);
    int rtt_idx, rodt_ctl, rtt_nom;
    int neigh_diff = CN8_OR_CN9(2, 5); // CN9 has wider RL delay range

    // now evaluate which bytes need adjusting
    int best_byte, new_byte, temp_byte, orig_best_byte;

    int rank_best_bytes[9]; // collect the new byte values; first init with current best for neighbor use
    for (int byte_idx = 0; byte_idx < 8+ecc_ena; byte_idx++) {
        rank_best_bytes[byte_idx] = get_rlevel_rank_struct(lmc_rlevel_rank, byte_idx);
    }

    for (int byte_idx = 0; byte_idx < 8+ecc_ena; byte_idx++) {
        best_byte = orig_best_byte = rank_best_bytes[byte_idx];

        ////////////////// this is the start of the BEST BYTE AVERAGING LOOP

        // validate the initial "best" byte by looking at the average of the unskipped byte-column entries
        // we want to do this before we go further, so we can try to start with a better initial value
        // this is the so-called "BESTBUY" patch set
        int sum = 0, count = 0;

        for (rtt_idx = min_rtt_nom_idx; rtt_idx <= max_rtt_nom_idx; ++rtt_idx) {
            rtt_nom = imp_values->rtt_nom_table[rtt_idx];

            /* if ((dyn_rtt_nom_mask == 0) && (rtt_idx != min_rtt_nom_idx))
               continue; */

            for (rodt_ctl = max_rodt_ctl; rodt_ctl >= min_rodt_ctl; --rodt_ctl) {
                bdk_lmcx_rlevel_rankx_t temp_rlevel_rank;
                int temp_score;
                for (int orankx = 0; orankx < 4; orankx++) { // average over all the ranks
                    if (!(dimm_rank_mask & (1 << orankx))) // stay on the same DIMM
                        continue;
                    temp_score = rlevel_scoreboard->scoreboard[rtt_nom][rodt_ctl][orankx].score;
                    // skip RODT rows in mask, or rows with too high a score;
                    // we will not use them for printing or evaluating...

                    if (!((1 << rodt_ctl) & rodt_row_skip_mask) &&
                        (temp_score <= MAX_RANK_SCORE))
                    {
                        temp_rlevel_rank.u = rlevel_scoreboard->scoreboard[rtt_nom][rodt_ctl][orankx].setting;
                        temp_byte = get_rlevel_rank_struct(&temp_rlevel_rank, byte_idx);
                        sum += temp_byte;
                        count++;
                    }
                } /* for (int orankx = 0; orankx < 4; orankx++) */
            } /* for (rodt_ctl = max_rodt_ctl; rodt_ctl >= min_rodt_ctl; --rodt_ctl) */
        } /* for (rtt_idx=min_rtt_nom_idx; rtt_idx<=max_rtt_nom_idx; ++rtt_idx) */

        ////////////////// this is the end of the BEST BYTE AVERAGING LOOP


        int avg_byte = (int)divide_nint(sum, count); // FIXME: validate count and sum??
        int avg_diff = best_byte - avg_byte;
        new_byte = best_byte;
        if (avg_diff != 0) {
            if ((avg_diff >= -2) && (avg_diff <= 2))
                new_byte = best_byte + ((avg_diff > 0) ? -1 : 1); // bump toward avg
            else
                new_byte = avg_byte; // use average!! // FIXME? is this workable?
        }

        VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: STARTED: Byte %d: best %d is different by %d from average %d, using %d.\n",
                node, ddr_interface_num, rankx,
                byte_idx, best_byte, avg_diff, avg_byte, new_byte);
        best_byte = new_byte;

        // At this point best_byte is either:
        // 1. the original byte-column value from the best scoring RODT row, OR
        // 2. that value bumped toward the average of all the byte-column values
        //
        // best_byte will not change from here on...

        rlevel_best_byte_count_results_t *count_results = &rlevel->count_results;
        memset(count_results, 0, sizeof(rlevel_best_byte_count_results_t));

        Best_Byte_Counting(node, ddr_interface_num, init_data, overrides, rlevel,
                            best_byte, byte_idx, rankx);

        VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: COUNTED: Byte %d: orig %d now %d, more %d same %d less %d (%d/%d/%d)\n",
               node, ddr_interface_num, rankx,  byte_idx, orig_best_byte, best_byte,
               count_results->count_more, count_results->count_same, count_results->count_less,
               count_results->rank_more, count_results->rank_same, count_results->rank_less);

        // choose the new byte value
        // we need to check that there is no gap greater than "neigh_diff" between adjacent bytes
        //  (adjacency depends on DIMM type)
        // use the neighbor value to help decide
        // initially, the rank_best_bytes[] will contain values from the chosen lowest score rank
        new_byte = 0;

        // neighbor is index-1 unless we are index 0 or index 8 (ECC)
        int neighbor = (byte_idx == 8) ? 3 : ((byte_idx == 0) ? 1 : byte_idx - 1);
        int neigh_byte = rank_best_bytes[neighbor];

        // can go up or down or stay the same, so look at a numeric average to help
        new_byte = divide_nint(((count_results->count_more * (best_byte + 1)) +
                    (count_results->count_same * (best_byte + 0)) +
                    (count_results->count_less * (best_byte - 1))),
                       max(1, (count_results->count_more + count_results->count_same + count_results->count_less)));

        // use neighbor to help choose with average, unless neighbor may be too far away,
        // but not for byte 0 or byte 4
        if (((byte_idx != 0) && (byte_idx != 4)) &&
            (_abs(neigh_byte - new_byte) > neigh_diff) &&
            !disable_sequential_delay_check)
        {
            int avg_pick = new_byte;
            if ((new_byte - best_byte) != 0)
                new_byte = best_byte; // back to best, average did not get better
            else // avg was the same, still too far, now move it towards the neighbor
                new_byte += (neigh_byte > new_byte) ? 1 : -1;

            VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: AVERAGE: Byte %d: neighbor %d too different %d from average %d, picking %d.\n",
                    node, ddr_interface_num, rankx,
                    byte_idx, neighbor, neigh_byte, avg_pick, new_byte);
        }

        // NOTE:
        // For now, we let the neighbor processing above trump the new simple majority processing here.
        // This is mostly because we have seen no smoking gun for a neighbor bad choice (yet?).
        // Also note that we will ALWAYS be using byte 0 majority, because of the if clause above.
        else {
            // majority is dependent on the counts, which are relative to best_byte, so start there
            int maj_byte = best_byte;
            if ((count_results->count_more > count_results->count_same) &&
                (count_results->count_more > count_results->count_less))
            {
                maj_byte++;
            }
            else if ((count_results->count_less > count_results->count_same) &&
                     (count_results->count_less > count_results->count_more))
            {
                maj_byte--;
            }
            if (maj_byte != new_byte) {
                // print only when majority choice is different from average
                VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: MAJORTY: Byte %d: picking majority of %d over average %d.\n",
                        node, ddr_interface_num, rankx,
                        byte_idx, maj_byte, new_byte);
                new_byte = maj_byte;
            }
            else {
                VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: AVERAGE: Byte %d: picking average of %d.\n",
                    node, ddr_interface_num, rankx,
                    byte_idx, new_byte);
            }

            if (!disable_rank_majority) {
                // rank majority is dependent on the rank counts, which are relative to best_byte,
                // so start there, and adjust according to the rank counts majority
                int rank_maj = best_byte;
                if ((count_results->rank_more > count_results->rank_same) &&
                        (count_results->rank_more > count_results->rank_less)) {
                    rank_maj++;
                }
                else if ((count_results->rank_less > count_results->rank_same) &&
                        (count_results->rank_less > count_results->rank_more)) {
                    rank_maj--;
                }
                int rank_sum = count_results->rank_more + count_results->rank_same + count_results->rank_less;

                // now, let rank majority possibly rule over the current new_byte however we got it
                if (rank_maj != new_byte) { // only if different
                    // Here is where we decide whether to completely apply RANK_MAJORITY or not
                    if (rank_maj < new_byte) { // ignore if less than
                        VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: RANKMAJ: Byte %d: LESS: NOT using %d over %d.\n",
                               node, ddr_interface_num, rankx,
                               byte_idx, rank_maj, new_byte);
                    } else
                    // FIXME: For the moment, we do it ONLY when running 2-slot configs
                    // FIXME? or when rank_sum is big enough?
                    if ((dimm_count > 1) || (rank_sum > 2)) {
                        // print only when rank majority choice is selected
                        VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: RANKMAJ: Byte %d: picking %d over %d.\n",
                               node, ddr_interface_num, rankx,
                               byte_idx, rank_maj, new_byte);
                        new_byte = rank_maj;
                    } else { // FIXME: print some info when we could have chosen RANKMAJ but did not
                        VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: RANKMAJ: Byte %d: NOT using %d over %d (best=%d,sum=%d).\n",
                               node, ddr_interface_num, rankx,
                               byte_idx, rank_maj, new_byte,
                               best_byte, rank_sum);
                    }
                }
            } /* if (!disable_rank_majority) */
        }

        uint64_t mask = 0;

#if PERFECT_BITMASK_COUNTING
        if (!disable_rl_pbm_counting) {
            Process_Perfect_Bitmasks(node, ddr_interface_num, init_data, overrides, rlevel,
                                     rankx, byte_idx, new_byte);
            //Update new_byte in case Process_Perfect_Bitmasks() found a better value
            //Note: Only usable when PERFECT_BITMASK_COUNTING enabled
            new_byte = rlevel->new_byte;
            disable_rlv_bump_this_byte = overrides->hw_rlevel.disable_rlv_bump_this_byte;
            mask = rlevel->rlevel_data.rank_perfect_counts[rankx].mask[byte_idx];
        }
#endif /* PERFECT_BITMASK_COUNTING */

        // optionally bump the delay value
        if (enable_rldelay_bump  && !disable_rlv_bump_this_byte) {
            if ((new_byte & enable_rldelay_bump) == enable_rldelay_bump) {
                int bump_value = new_byte + rldelay_bump_incr;
                VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: RLVBUMP: Byte %d: CHANGING %d to %d (%s)\n",
                       node, ddr_interface_num, rankx, byte_idx,
                       new_byte, bump_value,
                       (mask & (1 << bump_value))?"PBM":"NOPBM");
                new_byte = bump_value;
            }
        }

        // last checks for count-related purposes
        if ((new_byte == best_byte) &&
            (count_results->count_more > 0) && (count_results->count_less == 0))
        {
            if (disable_rlv_bump_this_byte) {
                // we really should NOT take best_byte + 1, if it is already "pinned"
                VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: CADJMOR: Byte %d: NOT changing %d to %d\n",
                       node, ddr_interface_num, rankx, byte_idx, new_byte, best_byte + 1);
            } else {
                // we really should take best_byte + 1
                VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: CADJMOR: Byte %d: CHANGING %d to %d\n",
                       node, ddr_interface_num, rankx, byte_idx, new_byte, best_byte + 1);
                new_byte = best_byte + 1;
            }
        } else if ((new_byte < best_byte) && (count_results->count_same > 0)) {
            if (disable_rlv_bump_this_byte) {
                // we really should NOT take best_byte, if it is already "pinned"
                VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: CADJSAM: Byte %d: NOT changing %d to %d\n",
                       node, ddr_interface_num, rankx, byte_idx, new_byte, best_byte);
            } else {
                // we really should take best_byte
                VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: CADJSAM: Byte %d: CHANGING %d to %d\n",
                       node, ddr_interface_num, rankx, byte_idx, new_byte, best_byte);
                new_byte = best_byte;
            }
        } else if (new_byte > best_byte) {
            if ((new_byte == (best_byte + 1)) &&
                ((count_results->count_less * 9) >= (count_results->count_same + count_results->count_more)) &&
                ((count_results->count_more * 9) <  (count_results->count_same + count_results->count_less)))
            {
                // only choose best_byte if count_less >= 10% of total
                // and count_more < 10% of total
                VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: CADJLE4: Byte %d: CHANGING %d to %d\n",
                       node, ddr_interface_num, rankx, byte_idx, new_byte, best_byte);
                new_byte = best_byte;
            }
            else if ((new_byte >= (best_byte + 2)) &&
                     ((count_results->count_more > 0) || (count_results->count_same > 0)))
            {
                VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: CADJLE2: Byte %d: CHANGING %d to %d\n",
                       node, ddr_interface_num, rankx, byte_idx, new_byte, best_byte + 1);
                new_byte = best_byte + 1;
            }
        }

        VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: SUMMARY: Byte %d: orig %d now %d, more %d same %d less %d, using %d\n",
               node, ddr_interface_num, rankx,byte_idx, orig_best_byte, best_byte,
               count_results->count_more, count_results->count_same,
               count_results->count_less, new_byte);

        // update the byte with the new value (NOTE: orig value in the CSR may not be current "best")
        update_rlevel_rank_struct(lmc_rlevel_rank, byte_idx, new_byte);

        rank_best_bytes[byte_idx] = new_byte; // save new best for neighbor use

    } /* for (byte_idx = 0; byte_idx < 8+ecc_ena; byte_idx++) */

}
////////////////// this is the end of the BEST BYTE LOOP

int Get_rodt_row_skip_mask(dram_init_data_t *init_data, int is_stacked_die)
{
    int rodt_row_skip_mask = 0;
    int num_ranks = init_data->refs.num_ranks;

    // just add specific RODT rows to the skip mask for DDR4 at this time...

    if (bdk_is_model(OCTEONTX_CN8XXX)) { // FIXME? any for CN9?
        // skip RODT row 34 and 40 ohms for all DDR4 types
        rodt_row_skip_mask |= (1 << ddr4_rodt_ctl_34_ohm) | (1 << ddr4_rodt_ctl_40_ohm);

        // do not skip RODT row 40 or 48 ohm when ddr_hertz is above 1075 MHz
        uint64_t ddr_hertz = init_data->refs.ddr_hertz;
        if (ddr_hertz > 1075000000) {
            rodt_row_skip_mask &= ~(1 << ddr4_rodt_ctl_40_ohm); // noskip RODT row 40 ohms
            rodt_row_skip_mask &= ~(1 << ddr4_rodt_ctl_48_ohm); // noskip RODT row 48 ohms
        }

        // do not skip RODT row 48 ohm for 2Rx4 stacked die DIMMs
        int dram_width = init_data->refs.dram_width;
        if ((is_stacked_die) && (num_ranks == 2) && (dram_width == 4)) {
            rodt_row_skip_mask &= ~(1 << ddr4_rodt_ctl_48_ohm); // noskip RODT row 48 ohms
        }

        // leave all rows eligible when we have mini-DIMMs...
        int spd_dimm_type = init_data->refs.spd_dimm_type;
        if ((spd_dimm_type == 5) || (spd_dimm_type == 6)) {
            rodt_row_skip_mask = 0;
        }

        // leave all rows eligible when we have a 2-slot 1-rank config
        int dimm_count = init_data->refs.dimm_count;
        if ((dimm_count == 2) && (num_ranks == 1)) {
            rodt_row_skip_mask = 0;
        }
    } else { // CN9XXX
        // skip RODT row 34 ohms for all DDR4 types
        /* rodt_row_skip_mask |= (1 << ddr4_rodt_ctl_34_ohm_cn9); */
    }

    return rodt_row_skip_mask;
}

void Evaluate_RLEVEL_Settings(bdk_node_t node,
                            int ddr_interface_num,
                            dram_init_data_t *init_data,
                            dram_overrides_t *overrides,
                            rlevel_struct_t *rlevel)
{
    /* Evaluation block */
    int dimm_count =        init_data->refs.dimm_count;
    int num_ranks =         init_data->refs.num_ranks;
    int rank_mask =         init_data->refs.rank_mask;
    int ecc_ena =           init_data->refs.use_ecc;
    int is_stacked_die =    init_data->spd.is_stacked_die;
    bdk_lmcx_rlevel_rankx_t lmc_rlevel_rank;
    int rankx;

    rlevel->rodt_row_skip_mask = Get_rodt_row_skip_mask(init_data, is_stacked_die);
    rlevel_scoreboard_t *rlevel_scoreboard = &(rlevel->rlevel_scoreboard);

    Evaluate_RLEVEL_Scoreboard_for_AUTO_Settings(node, ddr_interface_num, init_data,
                                                overrides, rlevel_scoreboard);

    ////////////////// this is the start of the RANK MAJOR LOOP

    for (rankx = 0; rankx < 4; rankx++) {
        rlevel_best_settings_t *best = &rlevel->best;

        best->rank_score = DEFAULT_BEST_RANK_SCORE; /* Start with an arbitrarily high score */
        best->rank_rtt_nom = 0;
        //best->rank_nom_ohms = 0;
        best->rank_ctl = 0;
        best->rank_ohms = 0;
        best->rankx = 0;

        if (!(rank_mask & (1 << rankx)))
            continue;

        /* Use the delays associated with the best score for each individual rank */
        VB_PRT(VBL_TME, "Evaluating Read-Leveling Scoreboard for Rank %d settings.\n", rankx);

        // some of the rank-related loops below need to operate only on the ranks of a single DIMM,
        // so create a mask for their use here
        int dimm_rank_mask;
        if (num_ranks == 4)
            dimm_rank_mask = rank_mask; // should be 1111
        else {
            dimm_rank_mask = rank_mask & 3; // should be 01 or 11
            if (rankx >= 2)
                dimm_rank_mask <<= 2; // doing a rank on the second DIMM, should be 0100 or 1100
        }
        debug_print("DIMM rank mask: 0x%x, rank mask: 0x%x, rankx: %d\n", dimm_rank_mask, rank_mask, rankx);

        rlevel->dimm_rank_mask = dimm_rank_mask;

        lmc_rlevel_rank.u =
            Find_RLEVEL_Best_Row_Score(node, ddr_interface_num, init_data,
                                        overrides, rlevel, rankx);

        // DANGER, Will Robinson!! Abort now if we did not find a best score at all...
        if (best->rank_score == DEFAULT_BEST_RANK_SCORE) {
            error_print("N%d.LMC%d.R%d: WARNING: no best rank score found - resetting node...\n",
                node, ddr_interface_num, rankx);
            bdk_wait_usec(500000);
            bdk_reset_chip(node);
        }

        // FIXME: relative now, but still arbitrary...
        // halve the range if 2 DIMMs unless they are single rank...
        int MAX_RANK_SCORE = best->rank_score;
        MAX_RANK_SCORE += (MAX_RANK_SCORE_LIMIT / ((num_ranks > 1) ? dimm_count : 1));
        rlevel->MAX_RANK_SCORE = MAX_RANK_SCORE;

        if (!ecc_ena) {
            //lmc_rlevel_rank.cn83xx.byte8 = lmc_rlevel_rank.cn83xx.byte0; /* ECC is not used */
            update_rlevel_rank_struct(&lmc_rlevel_rank, 8,
                                      get_rlevel_rank_struct(&lmc_rlevel_rank, 0));
        }

        // at the end, write the best row settings to the current rank
        DRAM_CSR_WRITE(node, BDK_LMCX_RLEVEL_RANKX(ddr_interface_num, rankx), lmc_rlevel_rank.u);
        lmc_rlevel_rank.u = BDK_CSR_READ(node, BDK_LMCX_RLEVEL_RANKX(ddr_interface_num, rankx));

        bdk_lmcx_rlevel_rankx_t saved_rlevel_rank;
        saved_rlevel_rank.u = lmc_rlevel_rank.u;

        RLEVEL_Print_Loop(node, ddr_interface_num, init_data, overrides, rlevel, rankx);

        Find_Best_Byte(node, ddr_interface_num, init_data, overrides, rlevel, &lmc_rlevel_rank, rankx);

        if (saved_rlevel_rank.u != lmc_rlevel_rank.u) {
            DRAM_CSR_WRITE(node, BDK_LMCX_RLEVEL_RANKX(ddr_interface_num, rankx), lmc_rlevel_rank.u);
            lmc_rlevel_rank.u = BDK_CSR_READ(node, BDK_LMCX_RLEVEL_RANKX(ddr_interface_num, rankx));
            debug_print("Adjusting Read-Leveling per-RANK settings.\n");
        }
        else {
            debug_print("Not Adjusting Read-Leveling per-RANK settings.\n");
        }
        display_RL_with_final(node, ddr_interface_num, lmc_rlevel_rank, rankx);

        if ((rank_mask & 0x0F) != 0x0F) { // if there are unused entries to be filled
            const uint8_t urm[3][4] = { [0]={0x0e, 0, 0, 0}, [1]={4, 8, 0, 0}, [2]={2, 0, 8, 0} };
            int msk = urm[rank_mask >> 1][rankx];
            for (int rx = 1; rx < 4; rx++) {
                if (msk & (1 << rx)) {
                    VB_PRT(VBL_DEV, "N%d.LMC%d.R%d: writing RLEVEL_RANK unused entry R%d.\n",
                           node, ddr_interface_num, rankx, rx);
                    DRAM_CSR_WRITE(node, BDK_LMCX_RLEVEL_RANKX(ddr_interface_num, rx), lmc_rlevel_rank.u);
                }
            }
        }
        VB_PRT(VBL_TME, "-----------\n");

    } /* for (rankx = 0; rankx < 4; rankx++) */
}  /* Evaluation block */

////////////////// this is the end of the RANK MAJOR LOOP

// HRM-CN9XXX 7.9.12
    /*
     * 6.9.12 LMC Read Leveling
     *
     * LMC supports an automatic read-leveling separately per byte-lane using
     * the DDR3 multipurpose register predefined pattern for system
     * calibration defined in the JEDEC DDR3 specifications.
     *
     * All of DDR PLL, LMC CK, and LMC DRESET, and early LMC initializations
     * must be completed prior to starting this LMC read-leveling sequence.
     *
     * Software could simply write the desired read-leveling values into
     * LMC(0)_RLEVEL_RANK(0..3). This section describes a sequence that uses
     * LMC's autoread-leveling capabilities.
     *
     * When LMC does the read-leveling sequence for a rank, it first enables
     * the DDR3 multipurpose register predefined pattern for system
     * calibration on the selected DRAM rank via a DDR3 MR3 write, then
     * executes 64 RD operations at different internal delay settings, then
     * disables the predefined pattern via another DDR3 MR3 write
     * operation. LMC determines the pass or fail of each of the 64 settings
     * independently for each byte lane, then writes appropriate
     * LMC(0)_RLEVEL_RANK(0..3)[BYTE*] values for the rank.
     *
     * After read-leveling for a rank, software can read the 64 pass/fail
     * indications for one byte lane via LMC(0)_RLEVEL_DBG[BITMASK]. Software
     * can observe all pass/fail results for all byte lanes in a rank via
     * separate read-leveling sequences on the rank with different
     * LMC(0)_RLEVEL_CTL[BYTE] values.
     *
     * The 64 pass/fail results will typically have failures for the low
     * delays, followed by a run of some passing settings, followed by more
     * failures in the remaining high delays.  LMC sets
     * LMC(0)_RLEVEL_RANK(0..3)[BYTE*] to one of the passing settings.
     * First, LMC selects the longest run of successes in the 64 results. (In
     * the unlikely event that there is more than one longest run, LMC
     * selects the first one.) Then if LMC(0)_RLEVEL_CTL[OFFSET_EN] = 1 and
     * the selected run has more than LMC(0)_RLEVEL_CTL[OFFSET] successes,
     * LMC selects the last passing setting in the run minus
     * LMC(0)_RLEVEL_CTL[OFFSET]. Otherwise LMC selects the middle setting in
     * the run (rounding earlier when necessary). We expect the read-leveling
     * sequence to produce good results with the reset values
     * LMC(0)_RLEVEL_CTL [OFFSET_EN]=1, LMC(0)_RLEVEL_CTL[OFFSET] = 2.
     *
     * The read-leveling sequence has the following steps:
     *
     * 1. Select desired LMC(0)_RLEVEL_CTL[OFFSET_EN,OFFSET,BYTE] settings.
     *    Do the remaining substeps 2-4 separately for each rank i with
     *    attached DRAM.
     *
     * 2. Without changing any other fields in LMC(0)_CONFIG,
     *
     *    o write LMC(0)_SEQ_CTL[SEQ_SEL] to select read-leveling
     *
     *    o write LMC(0)_CONFIG[RANKMASK] = (1 << i)
     *
     *    o write LMC(0)_SEQ_CTL[INIT_START] = 1
     *
     *    This initiates the previously-described read-leveling.
     *
     * 3. Wait until LMC(0)_RLEVEL_RANKi[STATUS] != 2
     *
     *    LMC will have updated LMC(0)_RLEVEL_RANKi[BYTE*] for all byte lanes
     *    at this point.
     *
     *    If ECC DRAM is not present (i.e. when DRAM is not attached to the
     *    DDR_CBS_0_* and DDR_CB<7:0> chip signals, or the DDR_DQS_<4>_* and
     *    DDR_DQ<35:32> chip signals), write LMC(0)_RLEVEL_RANK*[BYTE8] =
     *    LMC(0)_RLEVEL_RANK*[BYTE0]. Write LMC(0)_RLEVEL_RANK*[BYTE4] =
     *    LMC(0)_RLEVEL_RANK*[BYTE0].
     *
     * 4. If desired, consult LMC(0)_RLEVEL_DBG[BITMASK] and compare to
     *    LMC(0)_RLEVEL_RANKi[BYTE*] for the lane selected by
     *    LMC(0)_RLEVEL_CTL[BYTE]. If desired, modify LMC(0)_RLEVEL_CTL[BYTE]
     *    to a new value and repeat so that all BITMASKs can be observed.
     *
     * 5. Initialize LMC(0)_RLEVEL_RANK* values for all unused ranks.
     *
     *    Let rank i be a rank with attached DRAM.
     *
     *    For all ranks j that do not have attached DRAM, set
     *    LMC(0)_RLEVEL_RANKj = LMC(0)_RLEVEL_RANKi.
     *
     * This read-leveling sequence can help select the proper CN70XX ODT
     * resistance value (LMC(0)_COMP_CTL2[RODT_CTL]). A hardware-generated
     * LMC(0)_RLEVEL_RANKi[BYTEj] value (for a used byte lane j) that is
     * drastically different from a neighboring LMC(0)_RLEVEL_RANKi[BYTEk]
     * (for a used byte lane k) can indicate that the CN70XX ODT value is
     * bad. It is possible to simultaneously optimize both
     * LMC(0)_COMP_CTL2[RODT_CTL] and LMC(0)_RLEVEL_RANKn[BYTE*] values by
     * performing this read-leveling sequence for several
     * LMC(0)_COMP_CTL2[RODT_CTL] values and selecting the one with the best
     * LMC(0)_RLEVEL_RANKn[BYTE*] profile for the ranks.
     */
void Perform_Read_Leveling(bdk_node_t node, int ddr_interface_num,
                           dram_init_data_t *init_data,
                           dram_overrides_t *overrides)
{
    const ddr_custom_config_t *custom_lmc_config
        = &init_data->ddr_configuration->custom_lmc_config;

    Get_HW_Read_Leveling_Overrides(node, ddr_interface_num, init_data, overrides);

#pragma pack(push,4)
    bdk_lmcx_rlevel_rankx_t         lmc_rlevel_rank;
    bdk_lmcx_comp_ctl2_t            lmc_comp_ctl2;
    bdk_lmcx_rlevel_ctl_t           rlevel_ctl;
    bdk_lmcx_control_t              lmc_control;

    int rank_mask =                 init_data->refs.rank_mask;
    int spd_rdimm =                 init_data->refs.spd_rdimm;

    unsigned char save_ddr2t =      overrides->hw_rlevel.ddr_rlevel_2t;
    int rlevel_comp_offset =        overrides->hw_rlevel.rlevel_comp_offset;

    unsigned char rankx = 0;
    int saved_ddr__ptune, saved_ddr__ntune;
    int saved_int_zqcs_dis = 0;
    int i;
    const char *s;
    rlevel_struct_t rlevel;

#pragma pack(pop)

    //Clear structure
    memset(&rlevel, 0, sizeof(rlevel_struct_t));

    ddr_print("N%d.LMC%d: Performing Read-Leveling\n", node, ddr_interface_num);

    rlevel_ctl.u = overrides->hw_rlevel.rlevel_ctl;

    // HRM-CN9XXX 7.9.12.1
    rlevel_ctl.s.offset_en = custom_lmc_config->offset_en;
    rlevel_ctl.s.offset    = spd_rdimm
        ? custom_lmc_config->offset_rdimm
        : custom_lmc_config->offset_udimm;

    debug_print("N%d.LMC%d: RLEVEL_CTL: or_dis=%d, bitmask=0x%02x\n",
                node, ddr_interface_num,
                rlevel_ctl.s.or_dis, rlevel_ctl.s.bitmask);

    DRAM_CSR_WRITE(node, BDK_LMCX_RLEVEL_CTL(ddr_interface_num), rlevel_ctl.u);

    ddr_print("%-45s : 0x%016lx\n", "RLEVEL_CTL", rlevel_ctl.u);
    ddr_print("%-45s : %6d\n", "RLEVEL_OFFSET", rlevel_ctl.s.offset);
    ddr_print("%-45s : %6d\n", "RLEVEL_OFFSET_EN", rlevel_ctl.s.offset_en);

#ifdef ENABLE_CUSTOM_RLEVEL_TABLE
    if (custom_lmc_config->rlevel_table != NULL) {
        if (Set_Hard_Coded_RD_LVL_Settings(node, ddr_interface_num, init_data, custom_lmc_config))
            overrides->hw_rlevel.rlevel_debug_loops = 0; /* Disable h/w read-leveling */
    }
#endif /* ENABLE_CUSTOM_RLEVEL_TABLE */

    while (overrides->hw_rlevel.rlevel_debug_loops--) {
        /* Initialize the error scoreboard */
        memset(rlevel.rlevel_scoreboard.scoreboard, 0, sizeof(rlevel_scoreboard_t));

        lmc_comp_ctl2.u = BDK_CSR_READ(node, BDK_LMCX_COMP_CTL2(ddr_interface_num));
        saved_ddr__ptune = lmc_comp_ctl2.s.ddr__ptune;
        saved_ddr__ntune = lmc_comp_ctl2.s.ddr__ntune;

        overrides->hw_rlevel.saved_ddr__ptune = saved_ddr__ptune;
        overrides->hw_rlevel.saved_ddr__ntune = saved_ddr__ntune;

        ddr_print("%-45s : %d/%d\n", "Original DDR__PTUNE/DDR__NTUNE",
                      lmc_comp_ctl2.s.ddr__ptune, lmc_comp_ctl2.s.ddr__ntune);

        // save the current setting of LMCX_CONTROL[int_zqcs_dis]
        // we need to disable ZQCS during read-leveling
        lmc_control.u = BDK_CSR_READ(node, BDK_LMCX_CONTROL(ddr_interface_num));
        saved_int_zqcs_dis = lmc_control.s.int_zqcs_dis;
        lmc_control.s.int_zqcs_dis = 1; /* Disable ZQCS while doing HRL */
        DRAM_CSR_WRITE(node, BDK_LMCX_CONTROL(ddr_interface_num), lmc_control.u);

        /* Disable dynamic compensation settings */
        if (rlevel_comp_offset != 0) {
            lmc_comp_ctl2.s.ptune = saved_ddr__ptune;
            lmc_comp_ctl2.s.ntune = saved_ddr__ntune;

            /* Round up the ptune calculation to bias the odd cases toward ptune */
            lmc_comp_ctl2.s.ptune += divide_roundup(rlevel_comp_offset, 2);
            lmc_comp_ctl2.s.ntune -= rlevel_comp_offset/2;

            lmc_comp_ctl2.s.byp = 1; /* Enable bypass mode */
            DRAM_CSR_WRITE(node, BDK_LMCX_COMP_CTL2(ddr_interface_num), lmc_comp_ctl2.u);
            BDK_CSR_READ(node, BDK_LMCX_COMP_CTL2(ddr_interface_num));
            lmc_comp_ctl2.u = BDK_CSR_READ(node, BDK_LMCX_COMP_CTL2(ddr_interface_num)); /* Read again */
            ddr_print("%-45s : %d/%d\n", "New DDR__PTUNE/DDR__NTUNE",
                      lmc_comp_ctl2.s.ddr__ptune, lmc_comp_ctl2.s.ddr__ntune);
        }

        Perform_Read_Leveling_for_an_RTT_NOM_value(node, ddr_interface_num, init_data, overrides, &rlevel);

        /* Re-enable dynamic compensation settings. */
        if (rlevel_comp_offset != 0) {
            lmc_comp_ctl2.u = BDK_CSR_READ(node, BDK_LMCX_COMP_CTL2(ddr_interface_num));

            lmc_comp_ctl2.s.ptune = 0;
            lmc_comp_ctl2.s.ntune = 0;
            lmc_comp_ctl2.s.byp = 0; /* Disable bypass mode */
            DRAM_CSR_WRITE(node, BDK_LMCX_COMP_CTL2(ddr_interface_num), lmc_comp_ctl2.u);
            BDK_CSR_READ(node, BDK_LMCX_COMP_CTL2(ddr_interface_num)); /* Read once */

            lmc_comp_ctl2.u = BDK_CSR_READ(node, BDK_LMCX_COMP_CTL2(ddr_interface_num)); /* Read again */
            ddr_print("%-45s : %d/%d\n", "Restored DDR__PTUNE/DDR__NTUNE",
                      lmc_comp_ctl2.s.ddr__ptune, lmc_comp_ctl2.s.ddr__ntune);
        }

        // restore the previous setting of LMCX_CONTROL[int_zqcs_dis]...
        lmc_control.u = BDK_CSR_READ(node, BDK_LMCX_CONTROL(ddr_interface_num));
        lmc_control.s.int_zqcs_dis    = saved_int_zqcs_dis; /* Restore original setting */
        DRAM_CSR_WRITE(node, BDK_LMCX_CONTROL(ddr_interface_num), lmc_control.u);

        if (overrides->hw_rlevel.override_compensation) {
            lmc_comp_ctl2.s.ptune = saved_ddr__ptune;
            lmc_comp_ctl2.s.ntune = saved_ddr__ntune;

            lmc_control.u = BDK_CSR_READ(node, BDK_LMCX_CONTROL(ddr_interface_num));
            saved_int_zqcs_dis = lmc_control.s.int_zqcs_dis;
            lmc_control.s.int_zqcs_dis    = 1; /* Disable ZQCS while in bypass. */
            DRAM_CSR_WRITE(node, BDK_LMCX_CONTROL(ddr_interface_num), lmc_control.u);

            lmc_comp_ctl2.s.byp = 1; /* Enable bypass mode */
            DRAM_CSR_WRITE(node, BDK_LMCX_COMP_CTL2(ddr_interface_num), lmc_comp_ctl2.u);
            lmc_comp_ctl2.u = BDK_CSR_READ(node, BDK_LMCX_COMP_CTL2(ddr_interface_num)); /* Read again */

            ddr_print("%-45s : %d/%d\n", "PTUNE/NTUNE",
                      lmc_comp_ctl2.s.ptune, lmc_comp_ctl2.s.ntune);
        }

        Evaluate_RLEVEL_Settings(node, ddr_interface_num, init_data, overrides, &rlevel);

    } /* while(rlevel_debug_loops--) */

    lmc_control.s.ddr2t = save_ddr2t;
    DRAM_CSR_WRITE(node, BDK_LMCX_CONTROL(ddr_interface_num), lmc_control.u);
    lmc_control.u = BDK_CSR_READ(node, BDK_LMCX_CONTROL(ddr_interface_num));
    ddr_print("%-45s : %6d\n", "DDR2T", lmc_control.s.ddr2t); /* Display final 2T value */

    perform_ddr_init_sequence(node, rank_mask, ddr_interface_num);

    for (rankx = 0; rankx < 4;rankx++) {
        uint64_t value;
        int parameter_set = 0;
        if (!(rank_mask & (1 << rankx)))
            continue;

        lmc_rlevel_rank.u = BDK_CSR_READ(node, BDK_LMCX_RLEVEL_RANKX(ddr_interface_num, rankx));

        for (i = 0; i < 9; ++i) {
            if ((s = lookup_env_parameter("ddr%d_rlevel_rank%d_byte%d", ddr_interface_num, rankx, i)) != NULL) {
                parameter_set |= 1;
                value = strtoul(s, NULL, 0);

                update_rlevel_rank_struct(&lmc_rlevel_rank, i, value);
            }
        }

        if ((s = lookup_env_parameter_ull("ddr%d_rlevel_rank%d", ddr_interface_num, rankx)) != NULL) {
            parameter_set |= 1;
            value = strtoull(s, NULL, 0);
            lmc_rlevel_rank.u = value;
        }

        if (bdk_is_platform(BDK_PLATFORM_ASIM)) {
            parameter_set |= 1;
            for (int i = 0; i < 9; i++)
                update_rlevel_rank_struct(&lmc_rlevel_rank, i, 3);
        }

        if (parameter_set) {
            DRAM_CSR_WRITE(node, BDK_LMCX_RLEVEL_RANKX(ddr_interface_num, rankx), lmc_rlevel_rank.u);
            display_RL(node, ddr_interface_num, lmc_rlevel_rank, rankx);
        }
    }

#if 0
    // this is here just for output, to allow check of the Deskew settings one last time...
    int disable_deskew_training =   overrides->init.disable_deskew_training;
    if (!disable_deskew_training) {
        deskew_counts_t dsk_counts;
        VB_PRT(VBL_TME, "N%d.LMC%d: Check Deskew Settings before software Write-Leveling.\n",
            node, ddr_interface_num);
        Validate_Read_Deskew_Training(node, ddr_interface_num, rank_mask, &dsk_counts, VBL_TME, "B4SWL");
    }
#endif

    // Unlock deskew if the facility is enabled and the unlock_deskew envvar is 1
    Perform_Deskew_Unlock(node, ddr_interface_num, /*envvar*/1, init_data, overrides);
}
