/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libdram.h"
#include "dram-internal.h"
/**
 * Load a "odt_*rank_config" structure
 *
 * @param cfg    Config to fill
 * @param ranks  Number of ranks we're loading (1,2,4)
 * @param node   Node we're loading for
 * @param dimm   Which DIMM this is for
 * @param lmc    Which LMC this is for
 */
static void load_rank_data(dram_config_t *cfg, int ranks, int num_dimms, int lmc, bdk_node_t node)
{
    /* Get a pointer to the structure we are filling */
    dimm_odt_config_t *c;
    switch (ranks)
    {
        case 1:
            c = &cfg->config[lmc].odt_1rank_config[num_dimms - 1];
            break;
        case 2:
            c = &cfg->config[lmc].odt_2rank_config[num_dimms - 1];
            break;
        case 4:
            c = &cfg->config[lmc].odt_4rank_config[num_dimms - 1];
            break;
        default:
            bdk_fatal("Unexpected number of ranks\n");
            break;
    }

    /* Fill the global items */
    c->dqx_ctl    = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_DQX_CTL,      ranks, num_dimms, lmc, node);
    c->wodt_mask  = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_WODT_MASK,    ranks, num_dimms, lmc, node);

    /* Fill the per rank items */
    int rank = 0;

    for (rank = 0; rank < 4; rank++) {
        if (bdk_is_model(OCTEONTX_CN8XXX)) {
            int pasr, asr, srt;
            pasr = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_MODE1_PASR,    ranks, num_dimms, rank, lmc, node);
            asr  = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_MODE1_ASR,     ranks, num_dimms, rank, lmc, node);
            srt  = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_MODE1_SRT,     ranks, num_dimms, rank, lmc, node);
            INSRT_PASR(&c->modereg_params1.u, rank, pasr);
            INSRT_ASR (&c->modereg_params1.u, rank, asr);
            INSRT_SRT (&c->modereg_params1.u, rank, srt);
        }
        int wr, dic, nom;
        wr  = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_MODE1_RTT_WR,  ranks, num_dimms, rank, lmc, node);
        dic = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_MODE1_DIC,     ranks, num_dimms, rank, lmc, node);
        nom = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_MODE1_RTT_NOM, ranks, num_dimms, rank, lmc, node);
        INSRT_WR (&c->modereg_params1.u, rank, wr);
        INSRT_DIC(&c->modereg_params1.u, rank, dic);
        INSRT_NOM(&c->modereg_params1.u, rank, nom);
    }

    int imp = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_MODE1_DB_OUTPUT_IMPEDANCE, ranks, num_dimms, lmc, node);
    if (bdk_is_model(OCTEONTX_CN8XXX))
        c->modereg_params1.cn83xx.db_output_impedance  = imp;
    else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */
        c->modereg_params1.cn9.db_output_impedance     = imp;

    rank = 0;
    c->modereg_params2.s.rtt_park_00          = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_MODE2_RTT_PARK,   ranks, num_dimms, rank, lmc, node);
    c->modereg_params2.s.vref_value_00        = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_MODE2_VREF_VALUE, ranks, num_dimms, rank, lmc, node);
    c->modereg_params2.s.vref_range_00        = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_MODE2_VREF_RANGE, ranks, num_dimms, rank, lmc, node);
    c->modereg_params2.s.vrefdq_train_en      = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_MODE2_VREFDQ_TRAIN_EN, ranks, num_dimms, lmc, node);
    rank = 1;
    c->modereg_params2.s.rtt_park_01          = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_MODE2_RTT_PARK,   ranks, num_dimms, rank, lmc, node);
    c->modereg_params2.s.vref_value_01        = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_MODE2_VREF_VALUE, ranks, num_dimms, rank, lmc, node);
    c->modereg_params2.s.vref_range_01        = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_MODE2_VREF_RANGE, ranks, num_dimms, rank, lmc, node);
    rank = 2;
    c->modereg_params2.s.rtt_park_10          = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_MODE2_RTT_PARK,   ranks, num_dimms, rank, lmc, node);
    c->modereg_params2.s.vref_value_10        = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_MODE2_VREF_VALUE, ranks, num_dimms, rank, lmc, node);
    c->modereg_params2.s.vref_range_10        = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_MODE2_VREF_RANGE, ranks, num_dimms, rank, lmc, node);
    rank = 3;
    c->modereg_params2.s.rtt_park_11          = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_MODE2_RTT_PARK,   ranks, num_dimms, rank, lmc, node);
    c->modereg_params2.s.vref_value_11        = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_MODE2_VREF_VALUE, ranks, num_dimms, rank, lmc, node);
    c->modereg_params2.s.vref_range_11        = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_MODE2_VREF_RANGE, ranks, num_dimms, rank, lmc, node);

    /* Fill more global items */
    c->rodt_ctl      = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_RODT_CTL,     ranks, num_dimms, lmc, node);
    c->rodt_mask     = bdk_config_get_int(BDK_CONFIG_DDR_RANKS_RODT_MASK,    ranks, num_dimms, lmc, node);
}

/**
 * Load a DRAM configuration based on the current bdk-config settings
 *
 * @param node   Node the DRAM config is for
 *
 * @return Pointer to __libdram_global_cfg, a global structure. Returns NULL if bdk-config
 *         lacks information about DRAM.
 */
const dram_config_t *libdram_config_load(bdk_node_t node)
{
    dram_config_t *cfg = &__libdram_global_cfg;
    const int MAX_LMCS = sizeof(cfg->config) / sizeof(cfg->config[0]);

    /* Make all fields for the node default to zero */
    memset(cfg, 0, sizeof(dram_config_t));

    /* Fill the SPD data first as some parameters need to know the DRAM type
       to lookup the correct values */
    for (int lmc = 0; lmc < MAX_LMCS; lmc++)
    {
        for (int dimm = 0; dimm < DDR_CFG_T_MAX_DIMMS; dimm++)
        {
            int spd_addr = bdk_config_get_int(BDK_CONFIG_DDR_SPD_ADDR, dimm, lmc, node);
            if (spd_addr)
            {
                cfg->config[lmc].dimm_config_table[dimm].spd_addr = spd_addr;
            }
            else
            {
                int spd_size;
                const void *spd_data = bdk_config_get_blob(&spd_size, BDK_CONFIG_DDR_SPD_DATA, dimm, lmc, node);
                if (spd_data && spd_size)
                {
                    void *ptr = malloc(spd_size);
                    if (ptr)
                    {
                        memcpy(ptr, spd_data, spd_size);
                        cfg->config[lmc].dimm_config_table[dimm].spd_ptr = ptr;
                    }
                    else
                        bdk_error("Failed to allocate memory for SPD\n");
                }
            }
        }
    }

    /* Check that we know how to get DIMM information. If not, return failure */
    if (!cfg->config[0].dimm_config_table[0].spd_addr && !cfg->config[0].dimm_config_table[0].spd_ptr)
        return NULL;

    cfg->name = "Loaded from bdk-config";
    for (int lmc = 0; lmc < MAX_LMCS; lmc++)
    {
        for (int num_dimms = 1; num_dimms <= DDR_CFG_T_MAX_DIMMS; num_dimms++)
        {
            load_rank_data(cfg, 1, num_dimms, lmc, node);
            load_rank_data(cfg, 2, num_dimms, lmc, node);
            load_rank_data(cfg, 4, num_dimms, lmc, node);
        }

        ddr_configuration_t *c = &cfg->config[lmc];
        ddr_custom_config_t *custom = &c->custom_lmc_config;
        custom->min_rtt_nom_idx                 = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_MIN_RTT_NOM_IDX,     lmc, node);
        custom->max_rtt_nom_idx                 = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_MAX_RTT_NOM_IDX,     lmc, node);
        custom->min_rodt_ctl                    = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_MIN_RODT_CTL,        lmc, node);
        custom->max_rodt_ctl                    = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_MAX_RODT_CTL,        lmc, node);
        custom->ck_ctl                          = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_CK_CTL,              lmc, node);
        custom->cmd_ctl                         = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_CMD_CTL,             lmc, node);
        custom->ctl_ctl                         = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_CTL_CTL,             lmc, node);
        custom->min_cas_latency                 = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_MIN_CAS_LATENCY,     lmc, node);
        custom->offset_en                       = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_OFFSET_EN,           lmc, node);
        custom->offset_udimm                    = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_OFFSET,              "UDIMM", lmc, node);
        custom->offset_rdimm                    = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_OFFSET,              "RDIMM", lmc, node);
        custom->rlevel_compute                  = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_RLEVEL_COMPUTE,      lmc, node);
        custom->rlevel_comp_offset_udimm        = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_RLEVEL_COMP_OFFSET,  "UDIMM", lmc, node);
        custom->rlevel_comp_offset_rdimm        = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_RLEVEL_COMP_OFFSET,  "RDIMM", lmc, node);
        custom->ddr2t_udimm                     = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_DDR2T,               "UDIMM", lmc, node);
        custom->ddr2t_rdimm                     = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_DDR2T,               "RDIMM", lmc, node);
        custom->disable_sequential_delay_check  = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_DISABLE_SEQUENTIAL_DELAY_CHECK, lmc, node);
        custom->maximum_adjacent_rlevel_delay_increment
                                                = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_MAXIMUM_ADJACENT_RLEVEL_DELAY_INCREMENT, lmc, node);
        custom->parity                          = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_PARITY,          lmc, node);
        custom->fprch2                          = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_FPRCH2,          lmc, node);
        custom->mode32b                         = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_MODE32B,         lmc, node);
        custom->measured_vref                   = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_MEASURED_VREF,   lmc, node);
        custom->dram_connection                 = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_DRAM_CONNECTION, lmc, node);
        custom->dbi_mode                        = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_DBI_MODE,        lmc, node);
        custom->parity_mode                     = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_PARITY_MODE,     lmc, node);
        custom->data_invert                     = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_DATA_INVERT,     lmc, node);
        custom->use_scramble                    = bdk_config_get_int(BDK_CONFIG_DRAM_SCRAMBLE,              lmc, node);

        /* CN80XX only supports 32bit mode */
        if (bdk_is_altpkg(OCTEONTX_CN81XX))
            custom->mode32b = 1;

        /* Loop through 8 bytes, plus ecc byte */
        #define NUM_BYTES 9 /* Max bytes on LMC (8 plus ECC) */
        static int8_t dll_write_offset[NUM_BYTES];
        static int8_t dll_read_offset[NUM_BYTES];
        for (int b = 0; b < NUM_BYTES; b++)
        {
            dll_write_offset[b] = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_DLL_WRITE_OFFSET, b, lmc, node);
            dll_read_offset[b] = bdk_config_get_int(BDK_CONFIG_DDR_CUSTOM_DLL_READ_OFFSET,   b, lmc, node);
        }
        custom->dll_write_offset = dll_write_offset;
        custom->dll_read_offset = dll_read_offset;
    }

    int speed = bdk_config_get_int(BDK_CONFIG_DDR_SPEED, node);
    switch (speed)
    {
    	case 0: // AUTO
            cfg->ddr_clock_hertz = 0;
            break;
        case 666:
            cfg->ddr_clock_hertz = 333333333;
            break;
        case 1066:
            cfg->ddr_clock_hertz = 533333333;
            break;
        case 1333:
            cfg->ddr_clock_hertz = 666666666;
            break;
        case 1866:
        case 1880:
            if (bdk_is_model(OCTEONTX_CN8XXX))
                cfg->ddr_clock_hertz = 940000000;
            else
                cfg->ddr_clock_hertz = 933333333;
            break;
        case 2132:
        case 2133:
            if (bdk_is_model(OCTEONTX_CN8XXX))
                cfg->ddr_clock_hertz = 1050000000;
            else
                cfg->ddr_clock_hertz = 1066666666;
            break;
        case 2666:
            cfg->ddr_clock_hertz = 1333333333;
            break;
        case 2932:
        case 2933:
            cfg->ddr_clock_hertz = 1466666666;
            break;
        default:
            bdk_warn("Non-standard DRAM speed of %d MT/s\n", speed);
            // fall through
        case 800:
        case 1600:
        case 2100:
        case 2400:
        case 2650:
        case 3200:
            cfg->ddr_clock_hertz = (uint64_t)speed * 1000000 / 2;
            break;
    }

    return cfg;
};
