/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

// Process the SPD data and store in a structure for later use

#include <bdk.h>
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libbdk-arch/bdk-csrs-mio_fus.h"
#include "libdram.h"

#include "bdk-dram-init.h"

static unsigned char ddr4_rodt_ohms     [RODT_OHMS_COUNT     ] = {  0,  40,  60, 80, 120, 240, 34, 48 };
static unsigned char ddr4_rtt_nom_ohms  [RTT_NOM_OHMS_COUNT  ] = {  0,  60, 120, 40, 240,  48, 80, 34 };
static unsigned char ddr4_rtt_nom_table [RTT_NOM_TABLE_COUNT ] = {  0,   4,   2,  6,   1,   5,  3,  7 };
static unsigned char ddr4_rtt_wr_ohms   [RTT_WR_OHMS_COUNT   ] = {  0, 120, 240, 99,  80 }; // setting HiZ ohms to 99 for computed vref
static unsigned char ddr4_dic_ohms      [DIC_OHMS_COUNT      ] = { 34,  48 };
static short         ddr4_drive_strength[DRIVE_STRENGTH_COUNT] = {  0,   0, 26, 30, 34, 40, 48, 68, 0,0,0,0,0,0,0 };
static short         ddr4_dqx_strength  [DRIVE_STRENGTH_COUNT] = {  0,  24, 27, 30, 34, 40, 48, 60, 0,0,0,0,0,0,0 };

// these are for CN9XXX, and are filled in dynamically
static unsigned char ddr4_rodt_ohms_cn9 [RODT_OHMS_COUNT     ] = {  0,  34, 40, 50, 67, 100, 200,  0 };
static short         ddr4_drive_str_cn9 [DRIVE_STRENGTH_COUNT] = {  0,  21, 24, 27, 30, 36, 44,  0, 0,0,0,0,0,0,0 };
static short         ddr4_dqx_str_cn9   [DRIVE_STRENGTH_COUNT] = {  0,  20, 22, 25, 29, 34, 40, 50, 0,0,0,0,0,0,0 };

/*static*/ impedence_values_t ddr4_impedence_values = {
    .rodt_ohms             =  ddr4_rodt_ohms     ,
    .rtt_nom_ohms          =  ddr4_rtt_nom_ohms  ,
    .rtt_nom_table         =  ddr4_rtt_nom_table ,
    .rtt_wr_ohms           =  ddr4_rtt_wr_ohms   ,
    .dic_ohms              =  ddr4_dic_ohms      ,
    .drive_strength        =  ddr4_drive_strength,
    .dqx_strength          =  ddr4_dqx_strength  ,
};

#if ALLOW_BY_RANK_INIT

void Setup_By_Rank_ODT_Config(bdk_node_t node, const ddr_configuration_t *ddr_configuration)
{
    const char *s;
    // Do ODT settings changes which work best for 2R-1S configs
    ddr_print("DDR4: 2R-1S special BY-RANK init ODT settings updated\n");

    // setup for modifying config table values - 2 ranks and 1 DIMM
    dimm_odt_config_t *odt_config = (dimm_odt_config_t *)&ddr_configuration->odt_2rank_config[0];

    int by_rank_rodt = ddr4_rodt_ctl_48_ohm; // original was 80, first try was 60
    if ((s = lookup_env_parameter("ddr_by_rank_rodt")) != NULL) {
        by_rank_rodt = strtoul(s, NULL, 0);
    }
    odt_config->rodt_ctl = /*RODT_CTL*/ by_rank_rodt;

    // this is for MODEREG_PARAMS1 fields
    // fetch the original settings
    bdk_lmcx_modereg_params1_t modereg_params1;
    modereg_params1.u = odt_config->modereg_params1.u;

    int by_rank_wr = ddr4_rttwr_80ohm; // originals were 240
    if ((s = lookup_env_parameter("ddr_by_rank_wr")) != NULL) {
        by_rank_wr = strtoul(s, NULL, 0);
    }

    // change specific settings here...
    INSRT_WR(&modereg_params1.u, /*rank*/00, by_rank_wr);
    INSRT_WR(&modereg_params1.u, /*rank*/01, by_rank_wr);

    // save final settings
    odt_config->modereg_params1.u = modereg_params1.u;

    // this is for MODEREG_PARAMS2 fields
    // fetch the original settings
    bdk_lmcx_modereg_params2_t modereg_params2;
    modereg_params2.u = odt_config->modereg_params2.u;

    int by_rank_park = ddr4_rttpark_none; // originals were 120
    if ((s = lookup_env_parameter("ddr_by_rank_park")) != NULL) {
        by_rank_park = strtoul(s, NULL, 0);
    }

    // change specific settings here...
    //modereg_params2.s.rtt_park_00 = by_rank_park;
    //modereg_params2.s.rtt_park_01 = by_rank_park;
    INSRT_PARK(&modereg_params2.u, /*rank*/00, by_rank_park);
    INSRT_PARK(&modereg_params2.u, /*rank*/01, by_rank_park);

    // save final settings
    odt_config->modereg_params2.u = modereg_params2.u;
}

#endif

void Get_DDR_Overrides(bdk_node_t node, int ddr_interface_num,
                       dram_init_data_t *init_data,
                       dram_overrides_t *overrides)
{
    const ddr_custom_config_t *custom_lmc_config = &init_data->ddr_configuration->custom_lmc_config;
    ddr_overrides_t *ddr_overrides = &overrides->init;
    hw_wr_leveling_overrides_t *hw_wr_leveling_overrides = &overrides->hw_wlevel;
    const char *s;
    int is_cn9xxx = !!bdk_is_model(OCTEONTX_CN9XXX);

    //setup default settings for overrides
    // support match_wlevel_rtt_nom use only on CN8XXX
    hw_wr_leveling_overrides->match_wlevel_rtt_nom = (is_cn9xxx) ? 0 : 0/*only this*/;

    ddr_overrides->restart_if_dsk_incomplete = is_cn9xxx; // FIXME? force LMC restarts on CN9XXX

    ddr_overrides->disable_sequential_delay_check = custom_lmc_config->disable_sequential_delay_check;
    ddr_overrides->dbi_mode = custom_lmc_config->dbi_mode;
    ddr_overrides->parity_mode = custom_lmc_config->parity_mode;
    ddr_overrides->data_invert = custom_lmc_config->data_invert;
    ddr_overrides->use_scramble = custom_lmc_config->use_scramble;
    ddr_overrides->ddr_disable_chip_reset = 1;
    ddr_overrides->disable_deskew_training = 0;
    ddr_overrides->disable_stacked_die = 0;
    ddr_overrides->safe_ddr_flag = 0; /* Flag that indicates safe DDR settings should be used */

    /* Allow the Write bit-deskew feature to be enabled when desired. */
    // NOTE: CN8XXX pass 2.x only, 81xx, 83xx, 9xxx
    ddr_overrides->enable_write_deskew = ENABLE_WRITE_DESKEW_DEFAULT;

    // FIXME: default x4 HWL adjustment via write-deskew
    ddr_overrides->enable_x4_hwl_adj = 0; // was: (is_cn9xxx) ? 1 : 0;

    // FIXME: default by-rank init to ON unless CN9XXX
    ddr_overrides->enable_by_rank_init = (is_cn9xxx) ? 0 : ENABLE_BY_RANK_INIT_DEFAULT;
    ddr_overrides->num_ranks = 0;

    // CN9XXX is only DDR4, but some ODT details are different from CN8XXX DDR4...
    if (is_cn9xxx) {
        // change the table pointers for correct print-outs
        ddr4_impedence_values.rodt_ohms      = ddr4_rodt_ohms_cn9;
        ddr4_impedence_values.drive_strength = ddr4_drive_str_cn9;
        ddr4_impedence_values.dqx_strength   = ddr4_dqx_str_cn9;
    }

    // allow some overrides to be done via envvar

    // this one controls several things related to DIMM geometry: HWL and RL
    if ((s = lookup_env_parameter("ddr_disable_sequential_delay_check")) != NULL) {
        ddr_overrides->disable_sequential_delay_check = strtoul(s, NULL, 0);
    }

    // this one controls whether chip RESET is done, or LMC init restarted from step 6.9.6
    if ((s = lookup_env_parameter("ddr_restart_if_dsk_incomplete")) != NULL) {
        ddr_overrides->restart_if_dsk_incomplete = !!strtoul(s, NULL, 0);
    }
    // this one controls whether chip RESET is done, or LMC init restarted from step 6.9.6
    if ((s = lookup_env_parameter("ddr_disable_chip_reset")) != NULL) {
        ddr_overrides->ddr_disable_chip_reset = !!strtoul(s, NULL, 0);
    }
    // this one controls whether Deskew Training is performed
    if ((s = lookup_env_parameter("ddr_disable_deskew_training")) != NULL) {
        ddr_overrides->disable_deskew_training = !!strtoul(s, NULL, 0);
    }
    // this one is in Perform_Read_Deskew_Training and controls a preliminary delay
    ddr_overrides->deskew_validation_delay = DEFAULT_DESKEW_VALIDATION_DELAY;
    if ((s = lookup_env_parameter("ddr_deskew_validation_delay")) != NULL) {
        ddr_overrides->deskew_validation_delay = strtoul(s, NULL, 0);
    }
    // this one is in Perform_Read_Deskew_Training and controls lock retries
    ddr_overrides->default_lock_retry_limit = DEFAULT_LOCK_RETRY_LIMIT;
    if ((s = lookup_env_parameter("ddr_lock_retry_limit")) != NULL) {
        ddr_overrides->default_lock_retry_limit = strtoul(s, NULL, 0);
    }
    // this one controls whether stacked die status can affect processing
    // disabling it will affect computed vref adjustment, and rodt_row_skip_mask
    if ((s = lookup_env_parameter("ddr_disable_stacked_die")) != NULL) {
        ddr_overrides->disable_stacked_die = !!strtoul(s, NULL, 0);
    }
    // this one controls whether double-length VREF training is done;
    // it will default to a speed-related setting...
    if (is_cn9xxx) {
        if (init_data->refs.ddr_hertz >= 1466000000UL)
            ddr_overrides->double_vref_training = 1;
        if ((s = lookup_env_parameter("ddr_double_vref_training")) != NULL)
            ddr_overrides->double_vref_training = !!strtoul(s, NULL, 0);
    }

#if ALLOW_FORCE_2X_REFRESH
    // this one controls if we want to force 2X refresh
    if ((s = lookup_env_parameter("ddr_force_2x_refresh")) != NULL) {
        ddr_overrides->force_2x_refresh = !!strtoul(s, NULL, 0);
        if (ddr_overrides-> force_2x_refresh)
            ddr_print("N%d.LMC%d: Forcing 2X refresh\n", node, ddr_interface_num);
    }
#endif

    // setup/override for write bit-deskew feature
    // FIXME: allow override else take default setting
    if ((s = lookup_env_parameter("ddr_enable_write_deskew")) != NULL) {
        ddr_overrides->enable_write_deskew = !!strtoul(s, NULL, 0);
    }

    if (is_cn9xxx) { /* only allow CN9 to enable this */
        if ((s = lookup_env_parameter("ddr_enable_x4_hwl_adj")) != NULL) {
            ddr_overrides->enable_x4_hwl_adj = !!strtoul(s, NULL, 0);
        }
    }
    if ((s = lookup_env_parameter("ddr_safe")) != NULL) {
        ddr_overrides->safe_ddr_flag = !!strtoul(s, NULL, 0);
    }
    if (!is_cn9xxx) { /* only allow CN8 to enable this */
        if ((s = lookup_env_parameter("ddr_enable_by_rank_init")) != NULL) {
            ddr_overrides->enable_by_rank_init = !!strtoul(s, NULL, 0);
        }
    }
    if ((s = lookup_env_parameter("ddr_num_ranks")) != NULL) {
        ddr_overrides->num_ranks = strtoul(s, NULL, 0);
    }
    if ((s = lookup_env_parameter("ddr_dbi_mode")) != NULL) {
        ddr_overrides->dbi_mode = !!strtoul(s, NULL, 10);
    }
    if ((s = lookup_env_parameter("ddr_parity_mode")) != NULL) {
        ddr_overrides->parity_mode = !!strtoul(s, NULL, 10);
    }
    if ((s = lookup_env_parameter("ddr_data_invert")) != NULL) {
        ddr_overrides->data_invert = !!strtoul(s, NULL, 10);
    }
    if ((s = lookup_env_parameter("ddr_use_scramble")) != NULL) {
        ddr_overrides->use_scramble = strtoul(s, NULL, 10);
    }
}

int Get_DIMM_Setup_Data(bdk_node_t node,  int ddr_interface_num,
                        dram_init_data_t *init_data)
{
    const ddr_configuration_t *ddr_configuration =  init_data->ddr_configuration;
    const dimm_odt_config_t *odt_1rank_config =     ddr_configuration->odt_1rank_config;
    const dimm_odt_config_t *odt_2rank_config =     ddr_configuration->odt_2rank_config;
    const dimm_odt_config_t *odt_4rank_config =     ddr_configuration->odt_4rank_config;
    const ddr_custom_config_t *custom_lmc_config = &ddr_configuration->custom_lmc_config;
    const dimm_config_t *dimm_config_table =        ddr_configuration->dimm_config_table;
    uint64_t ddr_hertz = init_data->refs.ddr_hertz;
    uint32_t cpu_hertz = init_data->refs.cpu_hertz;
    int didx;
    int dimm_count = 0;
    int ddr_interface_64b = 1; /* THUNDER Default: 64bit interface width */

    if (dimm_config_table[0].spd_addr == 0 && !dimm_config_table[0].spd_ptr) {
        error_print("ERROR: No dimms specified in the dimm_config_table.\n");
        return (-1);
    }

    /*
    ** Walk the DRAM Socket Configuration Table to see what is installed.
    */
    for (didx = 0; didx < DDR_CFG_T_MAX_DIMMS; ++didx)
    {
        /* Check for lower DIMM socket populated */
        if (validate_dimm(node, &dimm_config_table[didx]) == 1) {
            // NOTE: DIMM info printing is now done later when more details are available
            ++dimm_count;
        }
        else {
            break;
        }       /* Finished when there is no lower DIMM */
    }

    initialize_ddr_clock(node,
                ddr_configuration,
                cpu_hertz,
                ddr_hertz,
                init_data->refs.ddr_ref_hertz,
                ddr_interface_num,
                init_data->refs.ddr_interface_mask);

    if (!odt_1rank_config)
        odt_1rank_config = disable_odt_config;
    if (!odt_2rank_config)
        odt_2rank_config = disable_odt_config;
    if (!odt_4rank_config)
        odt_4rank_config = disable_odt_config;

    if (dimm_count == 0) {
        error_print("ERROR: DIMM 0 not detected.\n");
        return(-1);
    }

    // look for 32-bit mode specified in the config
    if (custom_lmc_config->mode32b) {
        ddr_interface_64b = 0;
    }

    if (ddr_interface_64b == 0) { // check if 32-bit mode is bad
        if (!bdk_is_model(OCTEONTX_CN81XX)) {
            error_print("32-bit interface width is NOT supported for this Thunder model\n");
            ddr_interface_64b = 1; // force to 64-bit
        }
    }
    else { // check if 64-bit mode is bad
        if (bdk_is_model(OCTEONTX_CN81XX)) { // check the fuses on 81XX for forced 32-bit mode
            BDK_CSR_INIT(mio_fus_dat2, node, BDK_MIO_FUS_DAT2);
            if (mio_fus_dat2.s.lmc_mode32) {
                error_print("32-bit interface width is ONLY supported for this Thunder model\n");
                ddr_interface_64b = 0; // force to 32-bit
            }
        }
    }

    // finally, say we are in 32-bit mode when it has been validated
    if (ddr_interface_64b == 0) {
        ddr_print("N%d.LMC%d: Setting 32-bit data width\n",
                  node, ddr_interface_num);
    }

    //Set DDR interface as either 64 or 32 bit and number of DIMMs
    init_data->refs.ddr_interface_64b =     ddr_interface_64b;
    init_data->refs.dimm_count =            dimm_count;
    return 0;
}

static void Read_Out_DIMM_DATA_From_SPD(bdk_node_t node,  int ddr_interface_num,
                                        dram_init_data_t *init_data,
                                        dram_overrides_t *overrides)
{
    int spd_addr;
    int spd_org;
    int spd_banks;
    int spd_rdimm;
    int spd_lrdimm;
    int spd_dimm_type;
    int spd_package = 0;
    int spd_rawcard = 0;
    int spd_rawcard_AorB = 0;
    int spd_rdimm_registers = 0;
    int spd_thermal_sensor = 0;
    int is_stacked_die = 0;
    int is_3ds_dimm = 0; // 3DS
    int lranks_per_prank = 1; // 3DS: logical ranks per package rank
    int lranks_bits = 0; // 3DS: logical ranks bits
    int die_capacity = 0; // in Mbits; only used for 3DS

    int disable_stacked_die = overrides->init.disable_stacked_die;
    int parity_mode = overrides->init.parity_mode;

    ddr_type_t ddr_type;
    int bank_bits = 0;
    impedence_values_t *imp_values;
    const char *dimm_type_name;

    spd_data_t *spd_settings = &init_data->spd;
    const dimm_config_t *dimm_config_table = init_data->ddr_configuration->dimm_config_table;
    const dimm_config_t *dimm_config = &dimm_config_table[0];

    /* ddr_type only indicates DDR4 or other */
    ddr_type = get_ddr_type(node, dimm_config);

    spd_dimm_type = get_dimm_module_type(node, dimm_config);

    int spd_module_type;
    int asymmetric;
    const char *signal_load[4] = {"", "MLS", "3DS", "RSV"};
    int die_count;

    imp_values = &ddr4_impedence_values;
    dimm_type_name = ddr4_dimm_types[spd_dimm_type];

    spd_addr =  read_spd(node, dimm_config, DDR4_SPD_ADDRESSING_ROW_COL_BITS);
    spd_org  =  read_spd(node, dimm_config, DDR4_SPD_MODULE_ORGANIZATION);
    spd_banks = 0xFF & read_spd(node, dimm_config, DDR4_SPD_DENSITY_BANKS);

    bank_bits = (2 + ((spd_banks >> 4) & 0x3)) + ((spd_banks >> 6) & 0x3);
    bank_bits = min((int)bank_bits, 4); /* Controller can only address 4 bits. */

    spd_package = 0XFF & read_spd(node, dimm_config, DDR4_SPD_PACKAGE_TYPE);
    die_count = ((spd_package >> 4) & 7) + 1;

    if (spd_package & 0x80) { // non-monolithic device
        int pkg = spd_package & 3;
        ddr_print("DDR4: Package Type 0x%02x (%s), %d die\n", spd_package,
                  signal_load[pkg], die_count);
        switch (pkg) {
        case 1: // MLS
            is_stacked_die = !disable_stacked_die;
            break;
        case 2: // 3DS aka single-load-stack
            is_3ds_dimm = 1;
            lranks_per_prank = die_count;
            // FIXME: should make sure it is only 2H or 4H or 8H?
            lranks_bits = lranks_per_prank >> 1;
            if (lranks_bits == 4)
                lranks_bits = 3;
            break;
        } /* switch (pkg) */
    } /* if non-monolithic */
    else if (spd_package != 0) {
        // FIXME: print non-zero monolithic device definition
        ddr_print("DDR4: Package Type MONOLITHIC: %d die, signal load %d\n",
                  ((spd_package >> 4) & 7) + 1, (spd_package & 3));
    }

    asymmetric = (spd_org >> 6) & 1;
    if (asymmetric) {
        int spd_secondary_pkg = read_spd(node, dimm_config,
                                         DDR4_SPD_SECONDARY_PACKAGE_TYPE);
        ddr_print("DDR4: Module Organization: ASYMMETRICAL: Secondary Package Type 0x%02x\n",
                  spd_secondary_pkg);
    }
    else {
        uint64_t bus_width = 8 << (0x07 & read_spd(node, dimm_config,
                                                   DDR4_SPD_MODULE_MEMORY_BUS_WIDTH));
        uint64_t ddr_width = 4 << ((spd_org >> 0) & 0x7);
        uint64_t module_cap;
        int shift = (spd_banks & 0x0F);
        die_capacity = (shift < 8) ? (256UL << shift) : ((12UL << (shift & 1)) << 10);
        ddr_print("DDR4: Module Organization: SYMMETRICAL: capacity per die %d %cbit\n",
                  (die_capacity > 512) ? (die_capacity >> 10) : die_capacity,
                  (die_capacity > 512) ? 'G' : 'M');
        module_cap = ((uint64_t)die_capacity << 20) / 8UL * bus_width / ddr_width *
            /* no. pkg ranks*/(1UL + ((spd_org >> 3) & 0x7));
        if (is_3ds_dimm) // is it 3DS?
            module_cap *= die_count;
        ddr_print("DDR4: Module Organization: SYMMETRICAL: capacity per module %ld GB\n",
                  module_cap >> 30);
    }

    spd_rawcard = 0xFF & read_spd(node, dimm_config, DDR4_SPD_REFERENCE_RAW_CARD);
    ddr_print("DDR4: Reference Raw Card 0x%02x \n", spd_rawcard);

    spd_module_type = read_spd(node, dimm_config, DDR4_SPD_KEY_BYTE_MODULE_TYPE);
    if (spd_module_type & 0x80) { // HYBRID module
        ddr_print("DDR4: HYBRID module, type %s\n",
                  ((spd_module_type & 0x70) == 0x10) ? "NVDIMM" : "UNKNOWN");
    }
    spd_thermal_sensor = read_spd(node, dimm_config, DDR4_SPD_MODULE_THERMAL_SENSOR);

    // RDIMMs include LRDIMMs
    spd_lrdimm = (spd_dimm_type == 4);
    spd_rdimm = (spd_dimm_type == 1) || (spd_dimm_type == 5) || (spd_dimm_type == 8) || spd_lrdimm;

    if (spd_rdimm) {
        uint16_t spd_mfgr_id, spd_register_rev, spd_mod_attr;
        static const uint16_t manu_ids[4] = { 0xb380, 0x3286, 0x9780, 0xb304 };
        static const char * manu_names[4] = { "IDT", "MONTAGE", "TI", "INPHI" };
        int mc;
        spd_mfgr_id = read_spd(node, dimm_config, DDR4_SPD_REGISTER_MANUFACTURER_ID_LSB) |
            (read_spd(node, dimm_config, DDR4_SPD_REGISTER_MANUFACTURER_ID_MSB) << 8);
        spd_register_rev = read_spd(node, dimm_config, DDR4_SPD_REGISTER_REVISION_NUMBER);
        for (mc = 0; mc < 4; mc++)
            if (manu_ids[mc] == spd_mfgr_id)
                break;
        ddr_print("DDR4: %sDIMM Register Manufacturer ID: %s, Revision: 0x%02x\n",
                  (spd_lrdimm) ? "LR" : "R", (mc >= 4) ? "UNKNOWN" : manu_names[mc],
                  spd_register_rev);

        // RAWCARD A or B must be bit 7=0 and bits 4-0 either 00000(A) or 00001(B)
        spd_rawcard_AorB = ((spd_rawcard & 0x9fUL) <= 1);

        // RDIMM Module Attributes
        spd_mod_attr = read_spd(node, dimm_config, DDR4_SPD_UDIMM_ADDR_MAPPING_FROM_EDGE);
        spd_rdimm_registers = ((1 << (spd_mod_attr & 3)) >> 1);
        ddr_print("DDR4: %sDIMM Module Attributes (0x%02x): Register Type DDR4RCD%02d, DRAM rows %d, Registers %d\n",
                  (spd_lrdimm) ? "LR" : "R", spd_mod_attr, (spd_mod_attr >> 4) + 1,
                  ((1 << ((spd_mod_attr >> 2) & 3)) >> 1), spd_rdimm_registers);

        if (spd_lrdimm) {
            lrdimm_process_spd(node, ddr_interface_num, &dimm_config_table[0]);
        }
    }

    if (spd_thermal_sensor & 0x80) {
        ddr_print("DDR4: SPD: Thermal Sensor PRESENT\n");
    }

    debug_print("spd_addr        : %#06x\n", spd_addr );
    debug_print("spd_org         : %#06x\n", spd_org );
    debug_print("spd_banks       : %#06x\n", spd_banks );

    //Set variables for spd_data_t
    spd_settings->dimm_type_name =      dimm_type_name;
    spd_settings->spd_addr =            spd_addr;
    spd_settings->spd_org =             spd_org;
    spd_settings->spd_banks =           spd_banks;
    spd_settings->bank_bits =           bank_bits;
    spd_settings->spd_package =         spd_package;
    spd_settings->spd_rawcard =         spd_rawcard;
    spd_settings->spd_thermal_sensor =  spd_thermal_sensor;
    spd_settings->spd_rdimm_registers = spd_rdimm_registers;
    spd_settings->spd_rawcard_AorB =    spd_rawcard_AorB;
    spd_settings->is_stacked_die =      is_stacked_die;
    spd_settings->is_3ds_dimm =         is_3ds_dimm; // 3DS
    spd_settings->lranks_per_prank =    lranks_per_prank; // 3DS: logical ranks per package rank
    spd_settings->lranks_bits =         lranks_bits; // 3DS: logical ranks bits
    spd_settings->die_capacity =        die_capacity; // in Mbits; only used for 3DS

    //Carry over variables from SPD settings into general reference settings
    init_data->imp_values =              imp_values;
    init_data->refs.spd_rdimm =          spd_rdimm;
    init_data->refs.spd_lrdimm =         spd_lrdimm;
    init_data->refs.spd_dimm_type =      spd_dimm_type;
    init_data->refs.ddr_type =           ddr_type;

    // Override enabled PARITY mode setting when (L)RDIMM,
    //  as the register (RCD) parity code is incomplete 
    if (spd_rdimm && parity_mode) {
        overrides->init.parity_mode = 0;
        ddr_print("N%d.LMC%d: PARITY: Disabled, not supported on (L)RDIMMs...\n",
                  node, ddr_interface_num);
    }
}

int Get_DDR_Addressing_Data(bdk_node_t node, int ddr_interface_num,
                            dram_init_data_t *init_data,
                            dram_overrides_t *overrides)
{
    const ddr_configuration_t *ddr_configuration = init_data->ddr_configuration;
    const dimm_config_t *dimm_config_table = ddr_configuration->dimm_config_table;
    const dimm_config_t *dimm_config = &dimm_config_table[0];

    int dimm_count =                init_data->refs.dimm_count;
    int ddr_interface_64b =         init_data->refs.ddr_interface_64b;

    int lranks_bits =               init_data->spd.lranks_bits;
    int lranks_per_prank =          init_data->spd.lranks_bits;
    int spd_addr =                  init_data->spd.spd_addr;
    int spd_org =                   init_data->spd.spd_org;
    int bank_bits =                 init_data->spd.bank_bits;
    int spd_package =               init_data->spd.spd_package;
    const char* dimm_type_name =    init_data->spd.dimm_type_name;

    int spd_ecc = get_dimm_ecc(node, dimm_config);
    int wlevel_loops;
    int fatal_error = 0;
    int i;
    uint32_t mem_size_mbytes = 0;
    const char *s;

    int row_bits = 12 + ((spd_addr >> 3) & 0x7);
    int col_bits =  9 + ((spd_addr >> 0) & 0x7);

    int num_ranks =  1 + ((spd_org >> 3) & 0x7);
    int dram_width = 4 << ((spd_org >> 0) & 0x7);
    int num_banks = 1 << bank_bits;

    if (overrides->init.num_ranks != 0) {
        num_ranks = overrides->init.num_ranks;
    }

#if ALLOW_BY_RANK_INIT
    int enable_by_rank_init = overrides->init.enable_by_rank_init;
    int spd_lrdimm = init_data->refs.spd_lrdimm;

    // FIXME: for now, we can only handle a DDR4 2rank-1slot config
    // FIXME: also, by-rank init does not work correctly if 32-bit mode...
    if (enable_by_rank_init &&
        ((dimm_count != 1)        ||
         (spd_lrdimm == 1)        || // exclude LRDIMM always
         (ddr_interface_64b != 1) ||
         (num_ranks != 2)))
    {
        enable_by_rank_init = 0;
    }
    overrides->init.enable_by_rank_init = enable_by_rank_init;

    if (enable_by_rank_init) {
        Setup_By_Rank_ODT_Config(node, ddr_configuration);
    }

#endif  /* ALLOW_BY_RANK_INIT */

    /* FIX
    ** Check that values are within some theoretical limits.
    ** col_bits(min) = row_lsb(min) - bank_bits(max) - bus_bits(max) = 14 - 3 - 4 = 7
    ** col_bits(max) = row_lsb(max) - bank_bits(min) - bus_bits(min) = 18 - 2 - 3 = 13
    */
    if ((col_bits > 13) || (col_bits < 7)) {
        error_print("Unsupported number of Col Bits: %d\n", col_bits);
        ++fatal_error;
    }

    /* FIX
    ** Check that values are within some theoretical limits.
    ** row_bits(min) = pbank_lsb(min) - row_lsb(max) - rank_bits = 26 - 18 - 1 = 7
    ** row_bits(max) = pbank_lsb(max) - row_lsb(min) - rank_bits = 33 - 14 - 1 = 18
    */
    if ((row_bits > 18) || (row_bits < 7)) {
        error_print("Unsupported number of Row Bits: %d\n", row_bits);
        ++fatal_error;
    }

    if (bdk_is_platform(BDK_PLATFORM_ASIM))
        wlevel_loops = 0;
    else { // FIXME: default CN9XXX to 5 write-leveling samples
        wlevel_loops = CN8_OR_CN9(WLEVEL_LOOPS_DEFAULT, 5);
        // accept generic or interface-specific override but not for ASIM...
        if ((s = lookup_env_parameter("ddr_wlevel_loops")) == NULL)
            s = lookup_env_parameter("ddr%d_wlevel_loops", ddr_interface_num);
        if (s != NULL) {
            wlevel_loops = strtoul(s, NULL, 0);
        }
    }

    int bunk_enable = (num_ranks > 1);

    int column_bits_start = 3;

    int row_lsb = column_bits_start + col_bits + bank_bits - (! ddr_interface_64b);
    debug_print("row_lsb = column_bits_start + col_bits + bank_bits = %d\n", row_lsb);

    int pbank_lsb = row_lsb + row_bits + bunk_enable;
    debug_print("pbank_lsb = row_lsb + row_bits + bunk_enable = %d\n", pbank_lsb);

    if (lranks_per_prank > 1) {
        pbank_lsb = row_lsb + row_bits + lranks_bits + bunk_enable;
        ddr_print("DDR4: 3DS: pbank_lsb = (%d row_lsb) + (%d row_bits) + (%d lranks_bits) + (%d bunk_enable) = %d\n",
                  row_lsb, row_bits, lranks_bits, bunk_enable, pbank_lsb);
    }

    mem_size_mbytes =  dimm_count * ((1ull << pbank_lsb) >> 20);
    if (num_ranks == 4) {
        /* Quad rank dimm capacity is equivalent to two dual-rank dimms. */
        mem_size_mbytes *= 2;
    }

    /* Mask with 1 bits set for for each active rank, allowing 2 bits per dimm.
    ** This makes later calculations simpler, as a variety of CSRs use this layout.
    ** This init needs to be updated for dual configs (ie non-identical DIMMs).
    ** Bit 0 = dimm0, rank 0
    ** Bit 1 = dimm0, rank 1
    ** Bit 2 = dimm1, rank 0
    ** Bit 3 = dimm1, rank 1
    ** ...
    */
    int rank_mask = (1 << num_ranks) - 1;

    if (dimm_count == 2)
        rank_mask |= ((rank_mask & 0x3) << 2);

    VB_PRT(VBL_DEV, "Summary: %d %s%s %s %s, row bits=%d, col bits=%d, bank bits=%d\n",
           dimm_count, dimm_type_name, (dimm_count > 1) ? "s" : "",
           printable_rank_spec(num_ranks, dram_width, spd_package),
           (spd_ecc) ? "ECC" : "non-ECC",
           row_bits, col_bits, bank_bits);

    // always print out the useful DIMM information...
    for (i = 0; i < DDR_CFG_T_MAX_DIMMS; i++) {
        if (i < dimm_count)
            report_dimm(node, &dimm_config_table[i], i, ddr_interface_num,
                        num_ranks, dram_width, mem_size_mbytes / dimm_count);
        else
            if (validate_dimm(node, &dimm_config_table[i]) == 0) // only if there is a slot
                printf("N%d.LMC%d.DIMM%d: Not Present\n", node, ddr_interface_num, i);
    }

    int print_init_data = 0;
    if (print_init_data) {
        printf("bunk_enable: %d\n", bunk_enable);
        printf("rank_mask: %d\n", rank_mask);
        printf("mem_size_mbytes: %d\n", mem_size_mbytes);
        printf("num_ranks: %d\n", num_ranks);
        printf("num_banks: %d\n", num_banks);
        printf("dram_width: %d\n", dram_width);
        printf("wlevel_loops: %d\n", wlevel_loops);
        printf("lranks_bits: %d\n", lranks_bits);
        printf("row_lsb: %d\n", row_lsb);
        printf("pbank_lsb: %d\n", pbank_lsb);
        printf("row_bits: %d\n", row_bits);
        printf("col_bits: %d\n", col_bits);

    }

    //Set Internal Register settings
    init_data->refs.bunk_enable =               bunk_enable;
    init_data->refs.rank_mask =                 rank_mask;
    init_data->refs.mem_size_mbytes =           mem_size_mbytes;
    init_data->refs.num_ranks =                 num_ranks;
    init_data->refs.num_banks =                 num_banks;
    init_data->refs.dram_width =                dram_width;
    init_data->refs.wlevel_loops =              wlevel_loops;
    init_data->refs.ddr_interface_64b =         ddr_interface_64b;

    init_data->spd.row_lsb =                    row_lsb;
    init_data->spd.pbank_lsb =                  pbank_lsb;
    init_data->spd.row_bits =                   row_bits;
    init_data->spd.col_bits =                   col_bits;
    init_data->spd.spd_ecc =                    spd_ecc;

    return fatal_error;
}

void Get_DDR_Timing_Data_From_SPD(bdk_node_t node,
                            dram_init_data_t *init_data)
{
    int spd_rdimm =         init_data->refs.spd_rdimm;
    const dimm_config_t *dimm_config_table = init_data->ddr_configuration->dimm_config_table;
    const dimm_config_t *dimm_config = &dimm_config_table[0];
    int twr;
    int trcd;
    int trrd;
    int trp;
    int tras;
    int trc;
    int trfc;
    int twtr;
    int trtp = 0;  /* quiet */
    int tfaw;
    int tAAmin;

    int ddr4_tCKAVGmin = 0; /* quiet */
    int ddr4_tCKAVGmax = 0; /* quiet */
    int tCKmin;
    int ddr4_tRCDmin = 0; /* quiet */
    int ddr4_tRPmin = 0; /* quiet */
    int ddr4_tRASmin = 0; /* quiet */
    int ddr4_tRCmin = 0; /* quiet */
    int ddr4_tRFC1min = 0; /* quiet */
    int ddr4_tRFC2min = 0; /* quiet */
    int ddr4_tRFC4min = 0; /* quiet */
    int ddr4_tFAWmin = 0; /* quiet */
    int ddr4_tRRD_Smin = 0; /* quiet */
    int ddr4_tRRD_Lmin = 0;
    int ddr4_tCCD_Lmin = 0;
    int spd_addr_mirror;

    /* FTB values are two's complement ranging from +127 to -128. */
    typedef signed char SC_t;

    /* No other values for DDR4 MTB and FTB are specified at the
     * current time so don't bother reading them. Can't speculate how
     * new values will be represented.
     */
    int spdMTB = 125;
    int spdFTB = 1;

    tAAmin
        = spdMTB *        read_spd(node, dimm_config, DDR4_SPD_MIN_CAS_LATENCY_TAAMIN)
        + spdFTB * (SC_t) read_spd(node, dimm_config, DDR4_SPD_MIN_CAS_LATENCY_FINE_TAAMIN);

    ddr4_tCKAVGmin
        = spdMTB *        read_spd(node, dimm_config, DDR4_SPD_MINIMUM_CYCLE_TIME_TCKAVGMIN)
        + spdFTB * (SC_t) read_spd(node, dimm_config, DDR4_SPD_MIN_CYCLE_TIME_FINE_TCKAVGMIN);

    ddr4_tCKAVGmax
        = spdMTB *        read_spd(node, dimm_config, DDR4_SPD_MAXIMUM_CYCLE_TIME_TCKAVGMAX)
        + spdFTB * (SC_t) read_spd(node, dimm_config, DDR4_SPD_MAX_CYCLE_TIME_FINE_TCKAVGMAX);

    ddr4_tRCDmin
        = spdMTB *        read_spd(node, dimm_config, DDR4_SPD_MIN_RAS_CAS_DELAY_TRCDMIN)
        + spdFTB * (SC_t) read_spd(node, dimm_config, DDR4_SPD_MIN_RAS_TO_CAS_DELAY_FINE_TRCDMIN);

    ddr4_tRPmin
        = spdMTB *        read_spd(node, dimm_config, DDR4_SPD_MIN_ROW_PRECHARGE_DELAY_TRPMIN)
        + spdFTB * (SC_t) read_spd(node, dimm_config, DDR4_SPD_MIN_ROW_PRECHARGE_DELAY_FINE_TRPMIN);

    ddr4_tRASmin
        = spdMTB * (((read_spd(node, dimm_config, DDR4_SPD_UPPER_NIBBLES_TRAS_TRC) & 0xf) << 8)
                    + ( read_spd(node, dimm_config, DDR4_SPD_MIN_ACTIVE_PRECHARGE_LSB_TRASMIN) & 0xff));

    ddr4_tRCmin
        = spdMTB * ((((read_spd(node, dimm_config, DDR4_SPD_UPPER_NIBBLES_TRAS_TRC) >> 4) & 0xf) << 8)
                    + (  read_spd(node, dimm_config, DDR4_SPD_MIN_ACTIVE_REFRESH_LSB_TRCMIN) & 0xff))
        + spdFTB * (SC_t) read_spd(node, dimm_config, DDR4_SPD_MIN_ACT_TO_ACT_REFRESH_DELAY_FINE_TRCMIN);

    ddr4_tRFC1min
        = spdMTB * (((read_spd(node, dimm_config, DDR4_SPD_MIN_REFRESH_RECOVERY_MSB_TRFC1MIN) & 0xff) << 8)
                    + ( read_spd(node, dimm_config, DDR4_SPD_MIN_REFRESH_RECOVERY_LSB_TRFC1MIN) & 0xff));

    ddr4_tRFC2min
        = spdMTB * (((read_spd(node, dimm_config, DDR4_SPD_MIN_REFRESH_RECOVERY_MSB_TRFC2MIN) & 0xff) << 8)
                    + ( read_spd(node, dimm_config, DDR4_SPD_MIN_REFRESH_RECOVERY_LSB_TRFC2MIN) & 0xff));

    ddr4_tRFC4min
        = spdMTB * (((read_spd(node, dimm_config, DDR4_SPD_MIN_REFRESH_RECOVERY_MSB_TRFC4MIN) & 0xff) << 8)
                    + ( read_spd(node, dimm_config, DDR4_SPD_MIN_REFRESH_RECOVERY_LSB_TRFC4MIN) & 0xff));

    ddr4_tFAWmin
        = spdMTB * (((read_spd(node, dimm_config, DDR4_SPD_MIN_FOUR_ACTIVE_WINDOW_MSN_TFAWMIN) & 0xf) << 8)
                    + ( read_spd(node, dimm_config, DDR4_SPD_MIN_FOUR_ACTIVE_WINDOW_LSB_TFAWMIN) & 0xff));

    ddr4_tRRD_Smin
        = spdMTB *        read_spd(node, dimm_config, DDR4_SPD_MIN_ROW_ACTIVE_DELAY_SAME_TRRD_SMIN)
        + spdFTB * (SC_t) read_spd(node, dimm_config, DDR4_SPD_MIN_ACT_TO_ACT_DELAY_DIFF_FINE_TRRD_SMIN);

    ddr4_tRRD_Lmin
        = spdMTB *        read_spd(node, dimm_config, DDR4_SPD_MIN_ROW_ACTIVE_DELAY_DIFF_TRRD_LMIN)
        + spdFTB * (SC_t) read_spd(node, dimm_config, DDR4_SPD_MIN_ACT_TO_ACT_DELAY_SAME_FINE_TRRD_LMIN);

    ddr4_tCCD_Lmin
        = spdMTB *        read_spd(node, dimm_config, DDR4_SPD_MIN_CAS_TO_CAS_DELAY_TCCD_LMIN)
        + spdFTB * (SC_t) read_spd(node, dimm_config, DDR4_SPD_MIN_CAS_TO_CAS_DELAY_FINE_TCCD_LMIN);

    ddr_print("%-45s : %6d ps\n", "Medium Timebase (MTB)",          		   spdMTB);
    ddr_print("%-45s : %6d ps\n", "Fine Timebase   (FTB)",          		   spdFTB);

#define DDR4_TWR 15000
#define DDR4_TWTR_S 2500

    tCKmin	    = ddr4_tCKAVGmin;
    twr             = DDR4_TWR;
    trcd            = ddr4_tRCDmin;
    trrd            = ddr4_tRRD_Smin;
    trp             = ddr4_tRPmin;
    tras            = ddr4_tRASmin;
    trc             = ddr4_tRCmin;
    trfc            = ddr4_tRFC1min;
#if ALLOW_FORCE_2X_REFRESH
    if (force_2x_refresh)
        trfc = ddr4_tRFC2min;
#endif
    twtr            = DDR4_TWTR_S;
    tfaw            = ddr4_tFAWmin;

    if (spd_rdimm) {
        spd_addr_mirror = read_spd(node, dimm_config, DDR4_SPD_RDIMM_ADDR_MAPPING_FROM_REGISTER_TO_DRAM) & 0x1;
    }
    else {
        spd_addr_mirror = read_spd(node, dimm_config, DDR4_SPD_UDIMM_ADDR_MAPPING_FROM_EDGE) & 0x1;
    }
    debug_print("spd_addr_mirror : %#06x\n", spd_addr_mirror );

    ddr_print("%-45s : %6d ps (%ld MT/s)\n", "SDRAM Minimum Cycle Time (tCKAVGmin)",ddr4_tCKAVGmin,
              pretty_psecs_to_mts(ddr4_tCKAVGmin));
    ddr_print("%-45s : %6d ps\n", "SDRAM Maximum Cycle Time (tCKAVGmax)",          ddr4_tCKAVGmax);
    ddr_print("%-45s : %6d ps\n", "Minimum CAS Latency Time (tAAmin)",             tAAmin);
    ddr_print("%-45s : %6d ps\n", "Minimum RAS to CAS Delay Time (tRCDmin)",       ddr4_tRCDmin);
    ddr_print("%-45s : %6d ps\n", "Minimum Row Precharge Delay Time (tRPmin)",     ddr4_tRPmin);
    ddr_print("%-45s : %6d ps\n", "Minimum Active to Precharge Delay (tRASmin)",   ddr4_tRASmin);
    ddr_print("%-45s : %6d ps\n", "Minimum Active to Active/Refr. Delay (tRCmin)", ddr4_tRCmin);
    ddr_print("%-45s : %6d ps\n", "Minimum Refresh Recovery Delay (tRFC1min)",     ddr4_tRFC1min);
    ddr_print("%-45s : %6d ps\n", "Minimum Refresh Recovery Delay (tRFC2min)",     ddr4_tRFC2min);
    ddr_print("%-45s : %6d ps\n", "Minimum Refresh Recovery Delay (tRFC4min)",     ddr4_tRFC4min);
    ddr_print("%-45s : %6d ps\n", "Minimum Four Activate Window Time (tFAWmin)",   ddr4_tFAWmin);
    ddr_print("%-45s : %6d ps\n", "Minimum Act. to Act. Delay (tRRD_Smin)",        ddr4_tRRD_Smin);
    ddr_print("%-45s : %6d ps\n", "Minimum Act. to Act. Delay (tRRD_Lmin)",        ddr4_tRRD_Lmin);
    ddr_print("%-45s : %6d ps\n", "Minimum CAS to CAS Delay Time (tCCD_Lmin)",     ddr4_tCCD_Lmin);

    init_data->timing.twr =             twr;
    init_data->timing.trcd =            trcd;
    init_data->timing.trrd =            trrd;
    init_data->timing.trp =             trp;
    init_data->timing.tras =            tras;
    init_data->timing.trc =             trc;
    init_data->timing.trfc =            trfc;
    init_data->timing.twtr =            twtr;
    init_data->timing.trtp =            trtp;
    init_data->timing.tfaw =            tfaw;
    init_data->timing.tCKmin =          tCKmin;
    init_data->timing.ddr4_tRRD_Lmin =  ddr4_tRRD_Lmin;
    init_data->timing.ddr4_tCCD_Lmin =  ddr4_tCCD_Lmin;
    init_data->timing.spd_addr_mirror = spd_addr_mirror;
    init_data->timing.tAAmin =          tAAmin;
}


uint64_t Calculate_DDR_Clock_Rate(uint64_t tclk_psecs, int tCKmin, uint64_t eclk_psecs)
{
    /* When the cycle time is within 1 psec of the minimum accept it
       as a slight rounding error and adjust it to exactly the minimum
       cycle time. This avoids an unnecessary warning. */
    if (_abs(tclk_psecs - tCKmin) < 2)
        tclk_psecs = tCKmin;

    if (tclk_psecs < (uint64_t)tCKmin) {
        ddr_print("WARNING!!!!: DDR Clock Rate (tCLK: %ld) exceeds DIMM specifications (tCKmin: %ld)!!!!\n",
                    tclk_psecs, (uint64_t)tCKmin);
    }

    ddr_print("%-45s : %6lu ps\n", "DDR Clock Rate (tCLK)", tclk_psecs);
    ddr_print("%-45s : %6lu ps\n", "Core Clock Rate (eCLK)", eclk_psecs);

    return tclk_psecs;
}


void Print_DDR_Custom_Config_Info(const ddr_custom_config_t *custom_lmc_config, int spd_rdimm)
{

    ddr_print("\n------ Board Custom Configuration Settings ------\n");
    ddr_print("%-45s : %d\n", "MIN_RTT_NOM_IDX   ", custom_lmc_config->min_rtt_nom_idx);
    ddr_print("%-45s : %d\n", "MAX_RTT_NOM_IDX   ", custom_lmc_config->max_rtt_nom_idx);
    ddr_print("%-45s : %d\n", "MIN_RODT_CTL      ", custom_lmc_config->min_rodt_ctl);
    ddr_print("%-45s : %d\n", "MAX_RODT_CTL      ", custom_lmc_config->max_rodt_ctl);
    ddr_print("%-45s : %d\n", "MIN_CAS_LATENCY   ", custom_lmc_config->min_cas_latency);
    ddr_print("%-45s : %d\n", "OFFSET_EN         ", custom_lmc_config->offset_en);
    ddr_print("%-45s : %d\n", "OFFSET_UDIMM      ", custom_lmc_config->offset_udimm);
    ddr_print("%-45s : %d\n", "OFFSET_RDIMM      ", custom_lmc_config->offset_rdimm);
    ddr_print("%-45s : %d\n", "DDR_RTT_NOM_AUTO  ", custom_lmc_config->ddr_rtt_nom_auto);
    ddr_print("%-45s : %d\n", "DDR_RODT_CTL_AUTO ", custom_lmc_config->ddr_rodt_ctl_auto);
    if (spd_rdimm)
        ddr_print("%-45s : %d\n", "RLEVEL_COMP_OFFSET", custom_lmc_config->rlevel_comp_offset_rdimm);
    else
        ddr_print("%-45s : %d\n", "RLEVEL_COMP_OFFSET", custom_lmc_config->rlevel_comp_offset_udimm);
    ddr_print("%-45s : %d\n", "RLEVEL_COMPUTE    ", custom_lmc_config->rlevel_compute);
    ddr_print("%-45s : %d\n", "DDR2T_UDIMM       ", custom_lmc_config->ddr2t_udimm);
    ddr_print("%-45s : %d\n", "DDR2T_RDIMM       ", custom_lmc_config->ddr2t_rdimm);
    ddr_print("%-45s : %d\n", "FPRCH2            ", custom_lmc_config->fprch2);
    ddr_print("-------------------------------------------------\n");
}

int Calculate_CAS_Latency(bdk_node_t node,
                            dram_init_data_t *init_data)
{
    const ddr_configuration_t *ddr_configuration = init_data->ddr_configuration;
    const dimm_config_t *dimm_config_table = ddr_configuration->dimm_config_table;
    const dimm_config_t *dimm_config = &dimm_config_table[0];
    uint64_t tclk_psecs =       init_data->refs.tclk_psecs;
    int tAAmin =                init_data->timing.tAAmin;
    int tCKmin =                init_data->timing.tCKmin;
    uint32_t CL =               divide_roundup(tAAmin, tclk_psecs);
    uint32_t spd_cas_latency;
    uint32_t min_cas_latency =  ddr_configuration->custom_lmc_config.min_cas_latency;
    uint32_t max_cas_latency =  0;
    uint32_t override_cas_latency = 0;
    int base_CL;
    int i;
    const char *s;

    spd_cas_latency  = ((0xff & read_spd(node, dimm_config, DDR4_SPD_CAS_LATENCIES_BYTE0)) <<  0);
    spd_cas_latency |= ((0xff & read_spd(node, dimm_config, DDR4_SPD_CAS_LATENCIES_BYTE1)) <<  8);
    spd_cas_latency |= ((0xff & read_spd(node, dimm_config, DDR4_SPD_CAS_LATENCIES_BYTE2)) << 16);
    spd_cas_latency |= ((0xff & read_spd(node, dimm_config, DDR4_SPD_CAS_LATENCIES_BYTE3)) << 24);

    debug_print("spd_cas_latency : %#06x\n", spd_cas_latency );

    ddr_print("%-45s : %6d\n", "Desired CAS Latency", CL);

    if ((s = lookup_env_parameter("ddr_min_cas_latency")) != NULL) {
        min_cas_latency = strtoul(s, NULL, 0);
    }

    ddr_print("%-45s :", "CAS Latencies supported in DIMM");

    base_CL = 7;
    for (i = 0; i < 32; ++i) {
        if ((spd_cas_latency >> i) & 1) {
            ddr_print(" %d", i+base_CL);
            max_cas_latency = i+base_CL;
            if (min_cas_latency == 0)
                min_cas_latency = i+base_CL;
        }
    }
    ddr_print("\n");

    /* Use relaxed timing when running slower than the minimum
       supported speed.  Adjust timing to match the smallest supported
       CAS Latency. */
    if (CL < min_cas_latency) {
        uint64_t adjusted_tclk = tAAmin / min_cas_latency;
        CL = min_cas_latency;
        ddr_print("Slow clock speed. Adjusting timing: tClk = %lu, Adjusted tClk = %ld\n",
                  tclk_psecs, adjusted_tclk);
        tclk_psecs = adjusted_tclk;
        //init_data->refs.tclk_psecs = tclk_psecs;
    }

    if ((s = lookup_env_parameter("ddr_cas_latency")) != NULL) {
        override_cas_latency = strtoul(s, NULL, 0);
    }

    /* Make sure that the selected cas latency is legal */
    for (i=(CL-base_CL); i<32; ++i) {
        if ((spd_cas_latency >> i) & 1) {
            CL = i+base_CL;
            break;
        }
    }

    if (CL > max_cas_latency)
        CL = max_cas_latency;

    if (override_cas_latency != 0) {
        CL = override_cas_latency;
    }

    ddr_print("%-45s : %6d\n", "CAS Latency", CL);

    if ((CL * tCKmin) > 20000)
    {
        ddr_print("(CLactual * tCKmin) = %d exceeds 20 ns\n", (CL * tCKmin));
    }

    init_data->refs.CL =            CL;
    init_data->refs.tclk_psecs =    tclk_psecs;

    return CL;
}



int Check_DIMM_Config(bdk_node_t node,
                        //const ddr_configuration_t *ddr_configuration,
                        dram_init_data_t *init_data)
{
    const ddr_custom_config_t *custom_lmc_config = &init_data->ddr_configuration->custom_lmc_config;
    int num_banks =         init_data->refs.num_banks;
    int num_ranks =         init_data->refs.num_ranks;
    int spd_rdimm =         init_data->refs.spd_rdimm;
    int tCKmin =            init_data->timing.tCKmin;
    int ddr_interface_64b = init_data->refs.ddr_interface_64b;
    int dram_width =        init_data->refs.dram_width;
    int spd_ecc =           init_data->spd.spd_ecc; //is ECC Supported by the DIMM
    int fatal_error = 0;
    int use_ecc = 1;
    int ddr_interface_bytemask;
    const char *s;

    /*
    ** Compute clock rates to the nearest picosecond.
    */
    uint64_t tclk_psecs = hertz_to_psecs(init_data->refs.ddr_hertz); /* Clock in psecs */
    uint64_t eclk_psecs = hertz_to_psecs(init_data->refs.cpu_hertz); /* Clock in psecs */

    /* When the cycle time is within 1 psec of the minimum accept it
       as a slight rounding error and adjust it to exactly the minimum
       cycle time. This avoids an unnecessary warning. */
    init_data->refs.tclk_psecs = Calculate_DDR_Clock_Rate(tclk_psecs, tCKmin, eclk_psecs);

    if ((s = lookup_env_parameter("ddr_use_ecc")) != NULL) {
        use_ecc = !!strtoul(s, NULL, 0);
    }
    use_ecc = use_ecc && spd_ecc;

    // FIXME? 81xx does diff from 70xx
    if (ddr_interface_64b) {
        ddr_interface_bytemask = (use_ecc ? 0x1ff : 0xff);
    } else {
        ddr_interface_bytemask = (use_ecc ? 0x01f : 0x0f);
    }

    ddr_print("DRAM Interface width: %d bits %s bytemask 0x%03x\n",
              ddr_interface_64b ? 64 : 32, use_ecc ? "+ECC" : "",
              ddr_interface_bytemask);

    //Display DRAM Config Info
    Print_DDR_Custom_Config_Info(custom_lmc_config, spd_rdimm);

    Calculate_CAS_Latency(node, init_data);

    if ((num_banks != 4) && (num_banks != 8) && (num_banks != 16))
    {
        error_print("Unsupported number of banks %d. Must be 4 or 8 or 16.\n", num_banks);
        ++fatal_error;
    }

    if ((num_ranks != 1) && (num_ranks != 2) && (num_ranks != 4))
    {
        error_print("Unsupported number of ranks: %d\n", num_ranks);
        ++fatal_error;
    }

    if (! bdk_is_model(OCTEONTX_CN81XX)) { // 9XXX or 83XX, but not 81XX
        if ((dram_width != 8) && (dram_width != 16) && (dram_width != 4)) {
            error_print("Unsupported SDRAM Width, x%d.  Must be x4, x8 or x16.\n", dram_width);
            ++fatal_error;
        }
    } else if ((dram_width != 8) && (dram_width != 16)) { // 81XX can only do x8 or x16
        error_print("Unsupported SDRAM Width, x%d.  Must be x8 or x16.\n", dram_width);
        ++fatal_error;
    }

    init_data->refs.ddr_interface_bytemask =    ddr_interface_bytemask;
    init_data->refs.use_ecc =                   use_ecc;

    return fatal_error;
}

int Setup_DRAM_Config(bdk_node_t node, int ddr_interface_num,
                      dram_init_data_t *init_data,
                      dram_overrides_t *overrides)
{
    int fatal_error = 0;

    //Get Overrides for basic set up
    Get_DDR_Overrides(node, ddr_interface_num, init_data, overrides);

    if (Get_DIMM_Setup_Data(node, ddr_interface_num, init_data)) {
        fatal_error++;
    }

    Read_Out_DIMM_DATA_From_SPD(node, ddr_interface_num, init_data, overrides);

    if (Get_DDR_Addressing_Data(node, ddr_interface_num, init_data, overrides)) {
        fatal_error++;
    }

    //Read out data from SPD and save timing info
    Get_DDR_Timing_Data_From_SPD(node, init_data);

    if (Check_DIMM_Config(node, init_data)) {
        fatal_error++;
    }

    int dimm_count =    init_data->refs.dimm_count;
    int num_ranks =     init_data->refs.num_ranks;
    int odt_idx =       dimm_count - 1;
    const dimm_odt_config_t *odt_config;
    const ddr_configuration_t *ddr_configuration = init_data->ddr_configuration;

    init_data->terms.odt_idx = odt_idx;

    switch (num_ranks) {
    case 1:
        odt_config = ddr_configuration->odt_1rank_config;
        break;
    case 2:
        odt_config = ddr_configuration->odt_2rank_config;
        break;
    case 4:
        odt_config = ddr_configuration->odt_4rank_config;
        break;
    default:
        odt_config = disable_odt_config; //lib_octeon_shared.c
        error_print("Unsupported number of ranks: %d\n", num_ranks);
        ++fatal_error;
        //return -1;
    }

    init_data->terms.odt_config =   odt_config;

    /*
    ** Bail out here if things are not copasetic.
    */
    if (fatal_error)
        return(-1);
    return 0;
}

