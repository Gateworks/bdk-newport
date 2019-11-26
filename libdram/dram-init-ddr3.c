/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-l2c_tad.h"
#include "libbdk-arch/bdk-csrs-mio_fus.h"
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libdram.h"
#include "bdk-dram-init.h"

// Set to 1 to use the feature whenever possible automatically.
// When 0, however, the feature is still available, and it can
// be enabled via envvar override "ddr_enable_write_deskew=1".
#define ENABLE_WRITE_DESKEW_DEFAULT 0
#define ENABLE_COMPUTED_VREF_ADJUSTMENT 1
#define DAC_OVERRIDE_EARLY  0
#undef ENABLE_CUSTOM_RLEVEL_TABLE

static dram_init_data_t __dram_init_global_variables[DDR_CFG_T_MAX_LMCS];
static dram_overrides_t __dram_init_global_overrides[DDR_CFG_T_MAX_LMCS];

//Initialize data structure
dram_init_data_t *libdram_get_init_data(int lmc)
{
    dram_init_data_t *init_data = &__dram_init_global_variables[lmc];
    memset(init_data, 0, sizeof(dram_init_data_t));
    return init_data;
}

//Initialize data structure
dram_overrides_t *libdram_get_overrides(int lmc)
{
    dram_overrides_t *overrides = &__dram_init_global_overrides[lmc];
    memset(overrides, 0, sizeof(dram_overrides_t));
    return overrides;
}

#define SCALING_FACTOR (1000)
#define Dprintf debug_print // make this "ddr_print" for extra debug output below
static int compute_Vref_1slot_2rank(int rtt_wr, int rtt_park, int dqx_ctl,
                                    int rank_count, int dram_connection)
{
    uint64_t Reff_s;
    uint64_t Rser_s = (dram_connection) ? 0 : 15;
    uint64_t Vdd = 1200;
    uint64_t Vref;
    //uint64_t Vl;
    uint64_t rtt_wr_s = (((rtt_wr == 0) || (rtt_wr == 99)) ? 1*1024*1024 : rtt_wr); // 99 == HiZ
    uint64_t rtt_park_s = (((rtt_park == 0) || ((rank_count == 1) && (rtt_wr != 0))) ? 1*1024*1024 : rtt_park);
    uint64_t dqx_ctl_s = (dqx_ctl == 0 ? 1*1024*1024 : dqx_ctl);
    int Vref_value;
    uint64_t Rangepc = 6000; // range1 base is 60%
    uint64_t Vrefpc;
    int Vref_range = 0;

    Dprintf("rtt_wr = %d, rtt_park = %d, dqx_ctl = %d\n", rtt_wr, rtt_park, dqx_ctl);
    Dprintf("rtt_wr_s = %d, rtt_park_s = %d, dqx_ctl_s = %d\n", rtt_wr_s, rtt_park_s, dqx_ctl_s);

    Reff_s = divide_nint((rtt_wr_s * rtt_park_s) , (rtt_wr_s + rtt_park_s));
    Dprintf("Reff_s = %d\n", Reff_s);

    //Vl = (((Rser_s + dqx_ctl_s) * SCALING_FACTOR) / (Rser_s + dqx_ctl_s + Reff_s)) * Vdd / SCALING_FACTOR;
    //printf("Vl = %d\n", Vl);

    Vref = (((Rser_s + dqx_ctl_s) * SCALING_FACTOR) / (Rser_s + dqx_ctl_s + Reff_s)) + SCALING_FACTOR;
    Dprintf("Vref = %d\n", Vref);

    Vref = (Vref * Vdd) / 2 / SCALING_FACTOR;
    Dprintf("Vref = %d\n", Vref);

    Vrefpc = (Vref * 100 * 100) / Vdd;
    Dprintf("Vrefpc = %d\n", Vrefpc);

    if (Vrefpc < Rangepc) { // < range1 base, use range2
	Vref_range = 1 << 6; // set bit A6 for range2
	Rangepc = 4500; // range2 base is 45%
    }

    Vref_value = divide_nint(Vrefpc - Rangepc, 65);
    if (Vref_value < 0)
	Vref_value = Vref_range; // set to base of range as lowest value
    else
	Vref_value |= Vref_range;
    Dprintf("Vref_value = %d (0x%02x)\n", Vref_value, Vref_value);

    debug_print("rtt_wr:%d, rtt_park:%d, dqx_ctl:%d, Vref_value:%d (0x%x)\n",
           rtt_wr, rtt_park, dqx_ctl, Vref_value, Vref_value);

    return Vref_value;
}

static int compute_Vref_2slot_2rank(int rtt_wr, int rtt_park_00, int rtt_park_01,
                                    int dqx_ctl, int rtt_nom, int dram_connection)
{
    uint64_t Rser = (dram_connection) ? 0 : 15;
    uint64_t Vdd = 1200;
    //uint64_t Vref;
    uint64_t Vl, Vlp, Vcm;
    uint64_t Rd0, Rd1, Rpullup;
    uint64_t rtt_wr_s = (((rtt_wr == 0) || (rtt_wr == 99)) ? 1*1024*1024 : rtt_wr); // 99 == HiZ
    uint64_t rtt_park_00_s = (rtt_park_00 == 0 ? 1*1024*1024 : rtt_park_00);
    uint64_t rtt_park_01_s = (rtt_park_01 == 0 ? 1*1024*1024 : rtt_park_01);
    uint64_t dqx_ctl_s = (dqx_ctl == 0 ? 1*1024*1024 : dqx_ctl);
    uint64_t rtt_nom_s = (rtt_nom == 0 ? 1*1024*1024 : rtt_nom);
    int Vref_value;
    uint64_t Rangepc = 6000; // range1 base is 60%
    uint64_t Vrefpc;
    int Vref_range = 0;

    // Rd0 = (RTT_NOM /*parallel*/ RTT_WR) + Rser = ((RTT_NOM * RTT_WR) / (RTT_NOM + RTT_WR)) + Rser
    Rd0 = divide_nint((rtt_nom_s * rtt_wr_s), (rtt_nom_s + rtt_wr_s)) + Rser;
    //printf("Rd0 = %ld\n", Rd0);

    // Rd1 = (RTT_PARK_00 /*parallel*/ RTT_PARK_01) + Rser = ((RTT_PARK_00 * RTT_PARK_01) / (RTT_PARK_00 + RTT_PARK_01)) + Rser
    Rd1 = divide_nint((rtt_park_00_s * rtt_park_01_s), (rtt_park_00_s + rtt_park_01_s)) + Rser;
    //printf("Rd1 = %ld\n", Rd1);

    // Rpullup = Rd0 /*parallel*/ Rd1 = (Rd0 * Rd1) / (Rd0 + Rd1)
    Rpullup = divide_nint((Rd0 * Rd1), (Rd0 + Rd1));
    //printf("Rpullup = %ld\n", Rpullup);

    // Vl = (DQX_CTL / (DQX_CTL + Rpullup)) * 1.2
    Vl = divide_nint((dqx_ctl_s * Vdd), (dqx_ctl_s + Rpullup));
    //printf("Vl = %ld\n", Vl);

    // Vlp = ((Rser / Rd0) * (1.2 - Vl)) + Vl
    Vlp = divide_nint((Rser * (Vdd - Vl)), Rd0) + Vl;
    //printf("Vlp = %ld\n", Vlp);

    // Vcm = (Vlp + 1.2) / 2
    Vcm = divide_nint((Vlp + Vdd), 2);
    //printf("Vcm = %ld\n", Vcm);

    // Vrefpc = (Vcm / 1.2) * 100
    Vrefpc = divide_nint((Vcm * 100 * 100), Vdd);
    //printf("Vrefpc = %ld\n", Vrefpc);

    if (Vrefpc < Rangepc) { // < range1 base, use range2
	Vref_range = 1 << 6; // set bit A6 for range2
	Rangepc = 4500; // range2 base is 45%
    }

    Vref_value = divide_nint(Vrefpc - Rangepc, 65);
    if (Vref_value < 0)
	Vref_value = Vref_range; // set to base of range as lowest value
    else
	Vref_value |= Vref_range;
    //printf("Vref_value = %d (0x%02x)\n", Vref_value, Vref_value);

    debug_print("rtt_wr:%d, rtt_park_00:%d, rtt_park_01:%d, dqx_ctl:%d, rtt_nom:%d, Vref_value:%d (0x%x)\n",
	   rtt_wr, rtt_park_00, rtt_park_01, dqx_ctl, rtt_nom, Vref_value, Vref_value);

    return Vref_value;
}

// NOTE: only call this for DIMMs with 1 or 2 ranks, not 4.
int
__compute_vref_value(bdk_node_t node, int ddr_interface_num, int rankx,
                     int dimm_count, int rank_count, impedence_values_t * imp_values,
                     int is_stacked_die, int dram_connection)
{
    int computed_final_vref_value = 0;
    int enable_adjust = ENABLE_COMPUTED_VREF_ADJUSTMENT;
    const char *s;

    // allow some overrides...
    if ((s = getenv("ddr_adjust_computed_vref")) != NULL) {
	enable_adjust = !!strtoul(s, NULL, 0);
        if (!enable_adjust)
            ddr_print("N%d.LMC%d.R%d: DISABLE adjustment of computed VREF\n",
                      node, ddr_interface_num, rankx);
    }
    if ((s = getenv("ddr_set_computed_vref")) != NULL) {
        int new_vref = strtoul(s, NULL, 0);
        ddr_print("N%d.LMC%d.R%d: OVERRIDE computed VREF to 0x%x (%d)\n",
                  node, ddr_interface_num, rankx, new_vref, new_vref);
	return new_vref;
    }

    /* Calculate an alternative to the measured Vref value,
       but only for configurations we know how to...*/
    // We have code for 2-rank DIMMs in both 1-slot or 2-slot configs,
    // and can use the 2-rank 1-slot code for 1-rank DIMMs in 1-slot configs
    // and can use the 2-rank 2-slot code for 1-rank DIMMs in 2-slot configs.

    int rtt_wr, dqx_ctl, rtt_nom, index;
    bdk_lmcx_modereg_params1_t lmc_modereg_params1;
    bdk_lmcx_modereg_params2_t lmc_modereg_params2;
    bdk_lmcx_comp_ctl2_t comp_ctl2;

    lmc_modereg_params1.u = BDK_CSR_READ(node, BDK_LMCX_MODEREG_PARAMS1(ddr_interface_num));
    lmc_modereg_params2.u = BDK_CSR_READ(node, BDK_LMCX_MODEREG_PARAMS2(ddr_interface_num));
    comp_ctl2.u = BDK_CSR_READ(node, BDK_LMCX_COMP_CTL2(ddr_interface_num));
    dqx_ctl = imp_values->dqx_strength[comp_ctl2.s.dqx_ctl];

    // WR always comes from the current rank
    index = EXTR_WR(lmc_modereg_params1.u, rankx);
    rtt_wr  = imp_values->rtt_wr_ohms [index];

    // separate calculations for 1 vs 2 DIMMs per LMC
    if (dimm_count == 1) {
	// PARK comes from this rank if 1-rank, otherwise other rank
	index = EXTR_PARK(lmc_modereg_params2.u, (rankx ^ (rank_count - 1)));
	int rtt_park   = imp_values->rtt_nom_ohms[index];
	computed_final_vref_value =
            compute_Vref_1slot_2rank(rtt_wr, rtt_park, dqx_ctl,
                                     rank_count, dram_connection);
    } else {
	// get both PARK values from the other DIMM
	index = EXTR_PARK(lmc_modereg_params2.u, (rankx ^ 0x02));
	int rtt_park_00 = imp_values->rtt_nom_ohms[index];
	index = EXTR_PARK(lmc_modereg_params2.u, (rankx ^ 0x03));
	int rtt_park_01 = imp_values->rtt_nom_ohms[index];

	// NOM comes from this rank if 1-rank, otherwise other rank
	index   = EXTR_NOM(lmc_modereg_params1.u, (rankx ^ (rank_count - 1)));
	rtt_nom = imp_values->rtt_nom_ohms[index];
	computed_final_vref_value =
            compute_Vref_2slot_2rank(rtt_wr, rtt_park_00, rtt_park_01,
                                     dqx_ctl, rtt_nom, dram_connection);
    }

    if (enable_adjust) {
        int saved_final_vref_value = computed_final_vref_value;
	BDK_CSR_INIT(lmc_config, node, BDK_LMCX_CONFIG(ddr_interface_num));
	/*
	  New computed Vref = existing computed Vref – X

	  The value of X is depending on different conditions. Both #122 and #139 are 2Rx4 RDIMM,
	  while #124 is stacked die 2Rx4, so I conclude the results into two conditions:

	  1. Stacked Die: 2Rx4
	     1-slot: offset = 7. i, e New computed Vref = existing computed Vref – 7
	     2-slot: offset = 6

          2. Regular: 2Rx4
             1-slot: offset = 3
	     2-slot:  offset = 2
	*/
	// we know we never get called unless DDR4, so test just the other conditions
	if((!!__bdk_dram_is_rdimm(node, 0)) &&
	   (rank_count == 2) &&
	   (lmc_config.s.mode_x4dev))
	{ // it must first be RDIMM and 2-rank and x4
	    if (is_stacked_die) { // now do according to stacked die or not...
		computed_final_vref_value -= (dimm_count == 1) ? 7 : 6;
	    } else {
		computed_final_vref_value -= (dimm_count == 1) ? 3 : 2;
	    }
            // we have adjusted it, so print it out if verbosity is right
            VB_PRT(VBL_TME, "N%d.LMC%d.R%d: adjusting computed vref from %2d (0x%02x) to %2d (0x%02x)\n",
                   node, ddr_interface_num, rankx,
                   saved_final_vref_value, saved_final_vref_value,
                   computed_final_vref_value, computed_final_vref_value);
	}
    }

    return computed_final_vref_value;
}

int
compute_vref_value(bdk_node_t node, int ddr_interface_num, int rankx,
                   dram_init_data_t *init_data, dram_overrides_t *overrides)
{
    int dimm_count =                  init_data->refs.dimm_count;
    int is_stacked_die =              init_data->spd.is_stacked_die;
    int num_ranks =                   init_data->refs.num_ranks;
    impedence_values_t *imp_values =  init_data->imp_values;
    int dram_connection =             overrides->sw_wlevel.dram_connection;

    return __compute_vref_value(node, ddr_interface_num, rankx, dimm_count,
                                num_ranks, imp_values, is_stacked_die,
                                dram_connection);
}

char *printable_rank_spec(int num_ranks, int dram_width, int spd_package)
{
    static char buffer[8];
    int die_count = ((spd_package >> 4) & 7) + 1;

    if (spd_package & 0x80) { // non-monolithic
        if ((spd_package & 3) == 2) { // 3DS
            snprintf(buffer, 8, "%dS%dRx%d", num_ranks, die_count, dram_width);
        } else { // MLS
            char hchar = (die_count == 2) ? 'D' : 'Q';
            snprintf(buffer, 8, "%d%cRx%d", num_ranks, hchar, dram_width);
        }
    } else {
        snprintf(buffer, 8, "%dRx%d", num_ranks, dram_width);
    }
    return buffer;
}

/* Check to see if any custom offset values are provided */
static int is_dll_offset_provided(const int8_t *dll_offset_table)
{
    int i;
    if (dll_offset_table != NULL) {
	for (i=0; i<9; ++i) {
	    if (dll_offset_table[i] != 0)
		return (1);
	}
    }
    return (0);
}

unsigned short load_dll_offset(bdk_node_t node, int ddr_interface_num,
			       int dll_offset_mode, int byte_offset, int byte)
{
    bdk_lmcx_dll_ctl3_t ddr_dll_ctl3;
    /* byte_sel:
       0x1 = byte 0, ..., 0x9 = byte 8
       0xA = all bytes */
    int byte_sel = (byte == 10) ? byte : byte + 1;

    // offset field has different lengths and sign bit positions on the different chips
    int offset_shift = CN8_OR_CN9(6, 8);
    int offset_mask = (1 << offset_shift) - 1;
    int new_offset = (_abs(byte_offset) & offset_mask) | (_sign(byte_offset) << offset_shift);

    ddr_dll_ctl3.u = BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(ddr_interface_num));    

    SET_DDR_DLL_CTL3(mode_sel, dll_offset_mode);
    SET_DDR_DLL_CTL3(offset, new_offset);
    SET_DDR_DLL_CTL3(byte_sel, byte_sel);
    DRAM_CSR_WRITE(node, BDK_LMCX_DLL_CTL3(ddr_interface_num),	ddr_dll_ctl3.u);
    ddr_dll_ctl3.u = BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(ddr_interface_num));

    SET_DDR_DLL_CTL3(load_offset, 1);
    DRAM_CSR_WRITE(node, BDK_LMCX_DLL_CTL3(ddr_interface_num),	ddr_dll_ctl3.u);
    ddr_dll_ctl3.u = BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(ddr_interface_num));

    return ((unsigned short) GET_DDR_DLL_CTL3(offset));
}

void change_dll_offset_enable(bdk_node_t node, int ddr_interface_num, int change)
{
    bdk_lmcx_dll_ctl3_t ddr_dll_ctl3;

    ddr_dll_ctl3.u = BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(ddr_interface_num));
    SET_DDR_DLL_CTL3(offset_ena, !!change);
    DRAM_CSR_WRITE(node, BDK_LMCX_DLL_CTL3(ddr_interface_num),	ddr_dll_ctl3.u);
    ddr_dll_ctl3.u = BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(ddr_interface_num));
}

void process_custom_dll_offsets(bdk_node_t node, int ddr_interface_num, const char *enable_str,
				       const int8_t *offsets, const char *byte_str, int mode)
{
    const char *s;
    int enabled;
    int provided;

    if ((s = lookup_env_parameter("%s", enable_str)) != NULL) {
	enabled = !!strtol(s, NULL, 0);
    } else
	enabled = -1;

    // enabled == -1: no override, do only configured offsets if provided
    // enabled ==  0: override OFF, do NOT do it even if configured offsets provided
    // enabled ==  1: override ON, do it for overrides plus configured offsets

    if (enabled == 0)
	return;

    provided = is_dll_offset_provided(offsets);

    if (enabled < 0 && !provided)
	return;

    int byte_offset;
    unsigned short offset[9] = {0};
    int byte;

    // offsets need to be disabled while loading
    change_dll_offset_enable(node, ddr_interface_num, 0);

    for (byte = 0; byte < 9; ++byte) {

	// always take the provided, if available
	byte_offset = (provided) ? offsets[byte] : 0;

	// then, if enabled, use any overrides present
	if (enabled > 0) {
	    if ((s = lookup_env_parameter(byte_str, ddr_interface_num, byte)) != NULL) {
                byte_offset = strtol(s, NULL, 0);
            }
	}
	offset[byte] = load_dll_offset(node, ddr_interface_num, mode, byte_offset, byte);
    }

    // re-enable offsets after loading
    change_dll_offset_enable(node, ddr_interface_num, 1);

    ddr_print("N%d.LMC%d: DLL %s Offset 8:0       :"
	      "  0x%02x  0x%02x  0x%02x  0x%02x  0x%02x  0x%02x  0x%02x  0x%02x  0x%02x\n",
	      node, ddr_interface_num, (mode == 2) ? "Read " : "Write",
	      offset[8], offset[7], offset[6], offset[5], offset[4],
	      offset[3], offset[2], offset[1], offset[0]);
}

int
set_zqcs_interval(bdk_node_t node, int ddr_interface_num, int new_interval)
{
    int old_interval;

    BDK_CSR_INIT(lmc_config, node, BDK_LMCX_CONFIG(ddr_interface_num));
    old_interval = lmc_config.s.ref_zqcs_int;
    lmc_config.s.ref_zqcs_int = new_interval;
    DRAM_CSR_WRITE(node, BDK_LMCX_CONFIG(ddr_interface_num), lmc_config.u);
    (void) BDK_CSR_READ(node, BDK_LMCX_CONFIG(ddr_interface_num));

    return old_interval;
}

uint64_t
hertz_to_psecs(uint64_t hertz)
{
    return divide_nint((uint64_t) 1000*1000*1000*1000, hertz); /* Clock in psecs */
}

#define DIVIDEND_SCALE 1000      /* Scale to avoid rounding error. */

uint64_t
psecs_to_mts(uint64_t psecs)
{
    return divide_nint(divide_nint((uint64_t)(2 * 1000000 * DIVIDEND_SCALE), psecs), DIVIDEND_SCALE);
}

#define WITHIN(v,b,m) (((v)>=((b)-(m)))&&((v)<=((b)+(m))))

// pretty-print version, only works with what comes from the SPD: tCKmin or tCKAVGmin
unsigned long
pretty_psecs_to_mts(uint64_t psecs)
{
    uint64_t ret = 0; // default to error
    if (WITHIN(psecs, 2500, 1))      ret = 800;
    else if (WITHIN(psecs, 1875, 1)) ret = 1066;
    else if (WITHIN(psecs, 1500, 1)) ret = 1333;
    else if (WITHIN(psecs, 1250, 1)) ret = 1600;
    else if (WITHIN(psecs, 1071, 1)) ret = 1866;
    else if (WITHIN(psecs, 937, 1))  ret = 2133;
    else if (WITHIN(psecs, 833, 1))  ret = 2400;
    else if (WITHIN(psecs, 750, 1))  ret = 2666;
    else if (WITHIN(psecs, 682, 1))  ret = 2933;
    else if (WITHIN(psecs, 625, 1))  ret = 3200;
    return ret;
}

uint64_t
mts_to_hertz(uint64_t mts)
{
    return ((mts * 1000 * 1000) / 2);
}

int
init_octeontx_ddr_interface(bdk_node_t node, const ddr_configuration_t *ddr_configuration,
                            uint32_t ddr_hertz, uint32_t cpu_hertz, uint32_t ddr_ref_hertz,
                            int board_type, int board_rev_maj, int board_rev_min,
                            int ddr_interface_num, uint32_t ddr_interface_mask)
{
    const ddr_custom_config_t *custom_lmc_config = &ddr_configuration->custom_lmc_config;
    uint32_t mem_size_mbytes = 0;

    ddr_print("\nInitializing node %d DDR interface %d, DDR Clock %d, DDR Reference Clock %d\n",
              node, ddr_interface_num, ddr_hertz, ddr_ref_hertz);

    //initialize dram init variables and overrides structures and zero out all data
    dram_init_data_t *init_data = libdram_get_init_data(ddr_interface_num);
    dram_overrides_t *overrides = libdram_get_overrides(ddr_interface_num);
    hw_wr_level_data_t hw_wl_data;

    //set speeds
    init_data->refs.ddr_hertz = ddr_hertz;
    init_data->refs.cpu_hertz = cpu_hertz;
    init_data->refs.ddr_ref_hertz = ddr_ref_hertz;
    init_data->refs.ddr_interface_mask = ddr_interface_mask;

    //Add pointer to ddr_configuration structure
    init_data->ddr_configuration = ddr_configuration;

    //set default settings
    if (Setup_DRAM_Config(node, ddr_interface_num, init_data, overrides)) {
        return -1;
    }
    mem_size_mbytes = init_data->refs.mem_size_mbytes;

    // NOTE: we can do 8XXX init in same order as we need to do CN9XXX;
    // ie setup some CSRs, do the RESET, then finish up
    Perform_Early_LMC_Init(node, ddr_interface_num, init_data, overrides);

    if (Perform_LMC_RESET_Init(node, ddr_interface_num, init_data))
        return -1; //Fatal Error

    Finish_Early_LMC_Init(node, ddr_interface_num, init_data, overrides);

    if (bdk_is_model(OCTEONTX_CN8XXX) || !ddr_memory_preserved(node)) {
        // Offset, internal VREF, and Read Deskew trainings
        int training_result =
            Perform_DRAM_Training(node, ddr_interface_num, init_data, overrides);
        if (training_result == DESKEW_TRAINING_FAILED_RESTART_POSSIBLE)
            return training_result;

        // HW WR Leveling Data Structure for Getting a majority
        memset(&hw_wl_data, 0, sizeof(hw_wr_level_data_t));

        Run_HW_Write_Leveling(node, ddr_interface_num, init_data, overrides, &hw_wl_data);
        if (hw_wl_data.wlevel_bitmask_errors < 0)
            return -1;

        Perform_Read_Leveling(node, ddr_interface_num, init_data, overrides);
    }

    // Optionally switch over to DBI mode only for configurations that support it;
    // enabling the option can come from a board config file, or envvar override.
    dbi_switchover_interface(node, ddr_interface_num, init_data, overrides);

    if (bdk_is_model(OCTEONTX_CN8XXX) || !ddr_memory_preserved(node)) {
        int sw_wlevel_results =
            Perform_Sofware_Write_Leveling(node, ddr_interface_num, init_data,
                                           overrides, &hw_wl_data);
        if (sw_wlevel_results == 0)
            //Initialization failed but a reset is possible
            return 0;

        Perform_DLL_Encoding_and_WR_Deskew(node, ddr_interface_num, init_data,
                                           overrides, custom_lmc_config);
    }

    // turn parity mode ON if it is desired
    // FIXME: do this here so that MPR printing does not need to worry about it...
    Set_Parity_Mode(node, ddr_interface_num, init_data, overrides, /*ON*/1);

    Perform_Final_LMC_Init(node, ddr_interface_num, init_data, overrides);

    return(mem_size_mbytes);
}
