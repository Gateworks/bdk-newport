/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-l2c_tad.h"
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libbdk-arch/bdk-csrs-mcc.h"
#include "libbdk-arch/bdk-csrs-mio_fus.h"
#include "libdram.h"

#include "bdk-dram-init.h"

#define ENABLE_SLOT_CTL_ACCESS   0 // FIXME: needs 96XX changes to work there

void Get_DLL90_Settings(bdk_node_t node, int ddr_interface_num,
                        int *settings)
{
    int i;
    bdk_lmcx_dll_ctl3_t ddr_dll_ctl3;

    BDK_CSR_INIT(config, node, BDK_LMCX_CONFIG(ddr_interface_num));
    int start = 7 + config.s.ecc_ena;

    ddr_dll_ctl3.u = BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(ddr_interface_num));

    for (i = 0; i <= start; ++i) {

        SET_DDR_DLL_CTL3(dll90_byte_sel, i);
        DRAM_CSR_WRITE(node, BDK_LMCX_DLL_CTL3(ddr_interface_num), ddr_dll_ctl3.u);
        BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(ddr_interface_num));
        ddr_dll_ctl3.u = BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(ddr_interface_num));
        settings[i] = GET_DDR_DLL_CTL3(dll90_setting);
    }
}

void Process_DLL_Settings(bdk_node_t node, int ddr_interface_num,
                         const ddr_custom_config_t *custom_lmc_config)
{
    int i;
    int settings[9];

    BDK_CSR_INIT(config, node, BDK_LMCX_CONFIG(ddr_interface_num));
    int start = 7 + config.s.ecc_ena;

    Get_DLL90_Settings(node, ddr_interface_num, settings);

    if (dram_is_verbose(VBL_TME)) {
        printf("N%d.LMC%d: %-30s [%d:0] :", node, ddr_interface_num, "DLL90 Setting", start);
        for (i = start; i >= 0; i--) printf(" %5d", settings[i]);
        printf("\n");
    }

    // any custom DLL read or write offsets, install them
    // FIXME: no need to do these if we are going to auto-tune... ???

    process_custom_dll_offsets(node, ddr_interface_num, "ddr_dll_write_offset",
			       custom_lmc_config->dll_write_offset,
                               "ddr%d_dll_write_offset_byte%d", 1);
    process_custom_dll_offsets(node, ddr_interface_num, "ddr_dll_read_offset",
			       custom_lmc_config->dll_read_offset,
                               "ddr%d_dll_read_offset_byte%d",  2);
}

void
Perform_DLL_Encoding_and_WR_Deskew(bdk_node_t node,  int ddr_interface_num,
                                   dram_init_data_t *init_data,
                                   dram_overrides_t *overrides,
                                   const ddr_custom_config_t *custom_lmc_config)
{
    int rank_mask =                 init_data->refs.rank_mask;
    int spd_rdimm =                 init_data->refs.spd_rdimm;
    int disable_deskew_training =   overrides->init.disable_deskew_training;
    int enable_write_deskew =       overrides->init.enable_write_deskew;
    int enable_x4_hwl_adj =         overrides->init.enable_x4_hwl_adj;
    int i;

    if (spd_rdimm) { // display only for (L)RDIMMs

        // turn OFF parity mode if active for (L)RDIMMs just before MPR access
        // FIXME: only needed if parity mode might already be on!!!
        //Set_Parity_Mode(node, ddr_interface_num, init_data, overrides, /*OFF*/0);

        // display only MPR pages 0 and 2
        for (i = 0; i < 3; i += 2)
            Display_MPR_Page(node, rank_mask, ddr_interface_num, i);

        // turn parity mode back ON if active for (L)RDIMMs just after MPR access
        // FIXME: only needed if parity mode was already on!!!
        //Set_Parity_Mode(node, ddr_interface_num, init_data, overrides, /*ON*/1);
    }

    Process_DLL_Settings(node, ddr_interface_num, custom_lmc_config);

    // we want to train write bit-deskew here...
    if (! disable_deskew_training) {
        if (enable_write_deskew || enable_x4_hwl_adj) {
            ddr_print("N%d.LMC%d: WRITE BIT-DESKEW feature training begins.\n",
                      node, ddr_interface_num);
            Perform_Write_Deskew_Training(node, ddr_interface_num);
        } /* if (enable_write_deskew) */
    } /* if (! disable_deskew_training) */
}

void Setup_SLOT_CTL_ACCESS(bdk_node_t node, int ddr_interface_num)
{
#if ENABLE_SLOT_CTL_ACCESS
    bdk_lmcx_slot_ctl0_t lmc_slot_ctl0;
    bdk_lmcx_slot_ctl1_t lmc_slot_ctl1;
    bdk_lmcx_slot_ctl2_t lmc_slot_ctl2;
    bdk_lmcx_slot_ctl3_t lmc_slot_ctl3;

    lmc_slot_ctl0.u = BDK_CSR_READ(node, BDK_LMCX_SLOT_CTL0(ddr_interface_num));
    lmc_slot_ctl1.u = BDK_CSR_READ(node, BDK_LMCX_SLOT_CTL1(ddr_interface_num));
    lmc_slot_ctl2.u = BDK_CSR_READ(node, BDK_LMCX_SLOT_CTL2(ddr_interface_num));
    lmc_slot_ctl3.u = BDK_CSR_READ(node, BDK_LMCX_SLOT_CTL3(ddr_interface_num));

    ddr_print("%-45s : 0x%016lx\n", "LMC_SLOT_CTL0", lmc_slot_ctl0.u);
    ddr_print("%-45s : 0x%016lx\n", "LMC_SLOT_CTL1", lmc_slot_ctl1.u);
    ddr_print("%-45s : 0x%016lx\n", "LMC_SLOT_CTL2", lmc_slot_ctl2.u);
    ddr_print("%-45s : 0x%016lx\n", "LMC_SLOT_CTL3", lmc_slot_ctl3.u);

    // for now, look only for SLOT_CTL1 envvar for override of contents
    if ((s = lookup_env_parameter("ddr%d_slot_ctl1", ddr_interface_num)) != NULL) {
        int slot_ctl1_incr = strtoul(s, NULL, 0);
        // validate the value
        if ((slot_ctl1_incr < 0) || (slot_ctl1_incr > 3)) { // allow 0 for printing only
            error_print("ddr%d_slot_ctl1 illegal value (%d); must be 0-3\n",
                ddr_interface_num, slot_ctl1_incr);
        }
        else {

#define INCR(csr, chip, field, incr)  \
    csr.chip.field = (csr.chip.field < (64 - incr)) ? (csr.chip.field + incr) : 63

            // only print original when we are changing it!
            if (slot_ctl1_incr)
                ddr_print("%-45s : 0x%016lx\n", "LMC_SLOT_CTL1", lmc_slot_ctl1.u);

            // modify all the SLOT_CTL1 fields by the increment, for now...
            // but make sure the value will not overflow!!!
            INCR(lmc_slot_ctl1, s, r2r_xrank_init, slot_ctl1_incr);
            INCR(lmc_slot_ctl1, s, r2w_xrank_init, slot_ctl1_incr);
            INCR(lmc_slot_ctl1, s, w2r_xrank_init, slot_ctl1_incr);
            INCR(lmc_slot_ctl1, s, w2w_xrank_init, slot_ctl1_incr);
            DRAM_CSR_WRITE(node, BDK_LMCX_SLOT_CTL1(ddr_interface_num), lmc_slot_ctl1.u);
            lmc_slot_ctl1.u = BDK_CSR_READ(node, BDK_LMCX_SLOT_CTL1(ddr_interface_num));

            // always print when we are changing it!
            printf("%-45s : 0x%016lx\n", "LMC_SLOT_CTL1", lmc_slot_ctl1.u);
        }
    }
#endif /* ENABLE_SLOT_CTL_ACCESS */
}

void Clear_LMC_ECC_Errors(bdk_node_t node, int ddr_interface_num)
{
    if (bdk_is_model(OCTEONTX_CN8XXX)) {

        /* Clear any residual ECC errors */
        int num_tads = 1;
        int tad;

        DRAM_CSR_WRITE(node, BDK_LMCX_INT(ddr_interface_num), -1ULL);
        BDK_CSR_READ(node, BDK_LMCX_INT(ddr_interface_num));

        for (tad = 0; tad < num_tads; tad++)
            DRAM_CSR_WRITE(node, BDK_L2C_TADX_INT_W1C(tad),
                           BDK_CSR_READ(node, BDK_L2C_TADX_INT_W1C(tad)));

        ddr_print("%-45s : 0x%08lx\n", "LMC_INT",
                  BDK_CSR_READ(node, BDK_LMCX_INT(ddr_interface_num)));
    
    } else { // CN9XXX
        bdk_dram_lmc_map_t lmc_map = bdk_dram_get_lmc_map(node, ddr_interface_num);

        /* Clear ERR00-01 (SBE) and ERR02-03 (DBE) ECC errors in MCC */
        BDK_CSR_MODIFY(c, node, BDK_MCCX_LMCOEX_RAS_ERR00STATUS(lmc_map.mcc, lmc_map.lmcoe),
                       c.s.v = 1);
        BDK_CSR_MODIFY(c, node, BDK_MCCX_LMCOEX_RAS_ERR01STATUS(lmc_map.mcc, lmc_map.lmcoe),
                       c.s.v = 1);
        BDK_CSR_MODIFY(c, node, BDK_MCCX_LMCOEX_RAS_ERR02STATUS(lmc_map.mcc, lmc_map.lmcoe),
                       c.s.v = 1);
        BDK_CSR_MODIFY(c, node, BDK_MCCX_LMCOEX_RAS_ERR03STATUS(lmc_map.mcc, lmc_map.lmcoe),
                       c.s.v = 1);

        /* Clear ERR00 CRC/parity errors in LMC */
        BDK_CSR_MODIFY(c, node, BDK_LMCX_RAS_ERR00STATUS(ddr_interface_num),
                       c.s.v = 1);

        // FIXME: do we need/want any cache ECC error clearing?
    }
}

// Now we can enable scrambling if desired...
static void Setup_Scrambling_CN8XXX(bdk_node_t node, int ddr_interface_num, int use_scramble)
{
    bdk_lmcx_control_t lmc_control;
    bdk_lmcx_scramble_cfg0_t lmc_scramble_cfg0;
    bdk_lmcx_scramble_cfg1_t lmc_scramble_cfg1;
    bdk_lmcx_scramble_cfg2_t lmc_scramble_cfg2;
    bdk_lmcx_ns_ctl_t lmc_ns_ctl;
    const char *s;

    // read current contents
    lmc_control.u = BDK_CSR_READ(node, BDK_LMCX_CONTROL(ddr_interface_num));
    lmc_scramble_cfg0.u = BDK_CSR_READ(node, BDK_LMCX_SCRAMBLE_CFG0(ddr_interface_num)); // data
    lmc_scramble_cfg1.u = BDK_CSR_READ(node, BDK_LMCX_SCRAMBLE_CFG1(ddr_interface_num)); // address
    lmc_scramble_cfg2.u = BDK_CSR_READ(node, BDK_LMCX_SCRAMBLE_CFG2(ddr_interface_num)); // data
    lmc_ns_ctl.u = BDK_CSR_READ(node, BDK_LMCX_NS_CTL(ddr_interface_num));

    // enable all scrambling if configured in board file
    if (use_scramble) {
        // We cannot preserve scramble masks across RESETs, so do this always
        /* Use random values when scrambling is configured */
        lmc_scramble_cfg1.u = bdk_rng_get_random64(); // CFG1 is the address scramble mask
        lmc_scramble_cfg0.u = bdk_rng_get_random64();
        lmc_scramble_cfg2.u = bdk_rng_get_random64();
        lmc_ns_ctl.s.ns_scramble_dis = 0;
        lmc_ns_ctl.s.adr_offset = 0;
        lmc_control.s.scramble_ena = 1;
    }

    // let everything be overrideable, either all LMCs or by specific LMC...
    if ((s = lookup_env_parameter_ull("ddr%d_scramble_cfg0", ddr_interface_num)) == NULL)
        s = lookup_env_parameter_ull("ddr_scramble_cfg0");
    if (s != NULL) {
        lmc_scramble_cfg0.u = strtoull(s, NULL, 0);
        lmc_control.s.scramble_ena = 1;
    }
    if ((s = lookup_env_parameter_ull("ddr%d_scramble_cfg1", ddr_interface_num)) == NULL)
        s = lookup_env_parameter_ull("ddr_scramble_cfg1");
    if (s != NULL) {
        lmc_scramble_cfg1.u = strtoull(s, NULL, 0);
        lmc_control.s.scramble_ena = 1;
    }
    if ((s = lookup_env_parameter_ull("ddr%d_scramble_cfg2", ddr_interface_num)) == NULL)
        s = lookup_env_parameter_ull("ddr_scramble_cfg2");
    if (s != NULL) {
        lmc_scramble_cfg2.u = strtoull(s, NULL, 0);
        lmc_control.s.scramble_ena = 1;
    }
    if ((s = lookup_env_parameter_ull("ddr%d_ns_ctl", ddr_interface_num)) == NULL)
        s = lookup_env_parameter_ull("ddr_ns_ctl");
    if (s != NULL) {
        lmc_ns_ctl.u = strtoull(s, NULL, 0);
    }

    // now print and write the configuration...
    ddr_print("N%d.LMC%d: LMC_SCRAMBLE_CFG0:   0x%016lx\n", node, ddr_interface_num, lmc_scramble_cfg0.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_SCRAMBLE_CFG0(ddr_interface_num), lmc_scramble_cfg0.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_GENERAL_PURPOSE0(ddr_interface_num), lmc_scramble_cfg0.u); // data

    ddr_print("N%d.LMC%d: LMC_SCRAMBLE_CFG1:   0x%016lx\n", node, ddr_interface_num, lmc_scramble_cfg1.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_SCRAMBLE_CFG1(ddr_interface_num), lmc_scramble_cfg1.u);

    ddr_print("N%d.LMC%d: LMC_SCRAMBLE_CFG2:   0x%016lx\n", node, ddr_interface_num, lmc_scramble_cfg2.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_SCRAMBLE_CFG2(ddr_interface_num), lmc_scramble_cfg2.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_GENERAL_PURPOSE1(ddr_interface_num), lmc_scramble_cfg2.u); // data

    ddr_print("N%d.LMC%d: LMC_NS_CTL:          0x%016lx\n", node, ddr_interface_num, lmc_ns_ctl.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_NS_CTL(ddr_interface_num), lmc_ns_ctl.u);

    DRAM_CSR_WRITE(node, BDK_LMCX_CONTROL(ddr_interface_num), lmc_control.u);
}

// simple first versions
// assume arg is ONLY low-order 16 bits
#define MAKE_ADR_SCRAMBLE(m) ((m) | ((m) << 16) | ((m) << 32) | ((m) << 48))
#define UNMAKE_ADR_SCRAMBLE(m) ((m) & 0x0000FFFFUL)

static void Setup_Scrambling_CN9XXX(bdk_node_t node, int ddr_interface_num, int use_scramble)
{
    bdk_lmcx_adr_scramble_t  lmc_adr_scramble;
    bdk_mccx_scramble_cfg0_t mcc_scramble_cfg0;
    bdk_mccx_scramble_cfg1_t mcc_scramble_cfg1;
    bdk_mccx_config_t mcc_config;
    bdk_dram_lmc_map_t lmc_map = bdk_dram_get_lmc_map(node, ddr_interface_num);
    uint64_t addr_mask16; // GP2 can only hold 16 bits for preserving ADR_SCRAMBLE
    int data_scramble = 0;
    const char *s;

    // read current contents
    lmc_adr_scramble.u  = BDK_CSR_READ(node, BDK_LMCX_ADR_SCRAMBLE(ddr_interface_num));
    addr_mask16 = UNMAKE_ADR_SCRAMBLE(lmc_adr_scramble.u); 
    mcc_scramble_cfg0.u = BDK_CSR_READ(node, BDK_MCCX_SCRAMBLE_CFG0(lmc_map.mcc));
    mcc_scramble_cfg1.u = BDK_CSR_READ(node, BDK_MCCX_SCRAMBLE_CFG1(lmc_map.mcc));
    mcc_config.u        = BDK_CSR_READ(node, BDK_MCCX_CONFIG(lmc_map.mcc));

    // create or recover scrambling if configured in board DTS file
    if (use_scramble) {
        if (!ddr_memory_preserved(node)) {
            /* Use random values when scrambling is configured at cold reset */
            mcc_scramble_cfg0.u = bdk_rng_get_random64();
            mcc_scramble_cfg1.u = bdk_rng_get_random64();
            addr_mask16  = bdk_rng_get_random64() & 0x0000FFFFUL; // use only low-order 16
            data_scramble = 1;
        } else { // warm reset, grab the values saved earlier
            mcc_scramble_cfg0.u = get_scramble_cfg0(node, ddr_interface_num);
            mcc_scramble_cfg1.u = get_scramble_cfg1(node, ddr_interface_num);
            addr_mask16  = get_scramble_cfg2(node, ddr_interface_num); // only 16 already
            data_scramble = 1;
        }
    }

    // let everything be overrideable, either all LMCs or by specific LMC...
    // UNLESS memory was preserved, then we MUST use the provided values
    if (!ddr_memory_preserved(node)) {
        if ((s = lookup_env_parameter_ull("ddr%d_scramble_cfg0", ddr_interface_num)) == NULL)
            s = lookup_env_parameter_ull("ddr_scramble_cfg0");
        if (s != NULL) {
            mcc_scramble_cfg0.u = strtoull(s, NULL, 0);
            data_scramble = 1;
        }
        if ((s = lookup_env_parameter_ull("ddr%d_scramble_cfg1", ddr_interface_num)) == NULL)
            s = lookup_env_parameter_ull("ddr_scramble_cfg1");
        if (s != NULL) {
            mcc_scramble_cfg1.u = strtoull(s, NULL, 0);
            data_scramble = 1;
        }
        // this allows address scrambling to be disabled independent of data scrambling
        //  by setting the address scramble mask to 0 via envvar
        if ((s = lookup_env_parameter_ull("ddr%d_adr_scramble", ddr_interface_num)) == NULL)
            s = lookup_env_parameter_ull("ddr_adr_scramble");
        if (s != NULL) {
            addr_mask16 = strtoull(s, NULL, 0) & 0x0000FFFFUL;
        }
        // this allows data scrambling to be disabled independent of address scrambling
        //  by setting BOTH data scramble masks to 0 via envvars
        if ((mcc_scramble_cfg0.u == 0UL) && (mcc_scramble_cfg1.u == 0UL))
            data_scramble = 0;
    }

    lmc_adr_scramble.u = MAKE_ADR_SCRAMBLE(addr_mask16);
    ddr_print("N%d.LMC%d: LMC_ADR_SCRAMBLE:   0x%016lx (0x%04lx)\n",
              node, ddr_interface_num, lmc_adr_scramble.u, addr_mask16);
    DRAM_CSR_WRITE(node, BDK_LMCX_ADR_SCRAMBLE(ddr_interface_num), lmc_adr_scramble.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_GENERAL_PURPOSE2(ddr_interface_num), addr_mask16);

    if (ddr_interface_num < 2) { // LMC2 shares MCC with LMC0, does not need doing

        ddr_print("N%d.LMC%d: MCC%d_SCRAMBLE_CFG0: 0x%016lx\n",
                  node, ddr_interface_num, lmc_map.mcc, mcc_scramble_cfg0.u);
        DRAM_CSR_WRITE(node, BDK_MCCX_SCRAMBLE_CFG0(lmc_map.mcc), mcc_scramble_cfg0.u);
        DRAM_CSR_WRITE(node, BDK_LMCX_GENERAL_PURPOSE0(ddr_interface_num), mcc_scramble_cfg0.u);

        ddr_print("N%d.LMC%d: MCC%d_SCRAMBLE_CFG1: 0x%016lx\n",
                  node, ddr_interface_num, lmc_map.mcc, mcc_scramble_cfg1.u);
        DRAM_CSR_WRITE(node, BDK_MCCX_SCRAMBLE_CFG1(lmc_map.mcc), mcc_scramble_cfg1.u);
        DRAM_CSR_WRITE(node, BDK_LMCX_GENERAL_PURPOSE1(ddr_interface_num), mcc_scramble_cfg1.u);

        if (data_scramble) {
            mcc_config.s.scramble_s_ena  = 1;
            mcc_config.s.scramble_ns_ena = 1;

            // only print and write CSR when enabling data scrambling
            ddr_print("N%d.LMC%d: MCC%d_CONFIG:        0x%016lx\n",
                      node, ddr_interface_num, lmc_map.mcc, mcc_config.u);
            DRAM_CSR_WRITE(node, BDK_MCCX_CONFIG(lmc_map.mcc), mcc_config.u);
        }
    }
}

// Now we can enable scrambling if desired...
static void Setup_Final_Scrambling(bdk_node_t node, int ddr_interface_num,
                                   dram_init_data_t *init_data,
                                   dram_overrides_t *overrides)
{
    /* Read the scramble setting from the config and see if we
       need to initialize scrambling */
    int use_scramble = overrides->init.use_scramble;

    if (use_scramble == 2)
        use_scramble = (bdk_trust_get_level() >= BDK_TRUST_LEVEL_SIGNED);

    if (use_scramble) {
        ddr_print("N%d.LMC%d: Setup_Final_Scrambling: %s scrambling\n",
                  node, ddr_interface_num,
                  (ddr_memory_preserved(node)) ? "restoring" : "starting");
    }

    // call these always, in case there are overrides to process...
    if (bdk_is_model(OCTEONTX_CN8XXX))
        Setup_Scrambling_CN8XXX(node, ddr_interface_num, use_scramble);
    else
        Setup_Scrambling_CN9XXX(node, ddr_interface_num, use_scramble);
}

void Perform_Deskew_Unlock(bdk_node_t node, int ddr_interface_num,
                                  int unlock_envvar,
                                  dram_init_data_t *init_data,
                                  dram_overrides_t *overrides)
{
#if ALLOW_DESKEW_UNLOCK

    // only allow 9XXX all passes
    if (bdk_is_model(OCTEONTX_CN9XXX)) {
        int dimm_count = init_data->refs.dimm_count;
        int num_ranks =  init_data->refs.num_ranks;
        int rank_mask =  init_data->refs.rank_mask;

        bdk_lmcx_phy_ctl_t phy_ctl;
        phy_ctl.u = BDK_CSR_READ(node, BDK_LMCX_PHY_CTL(ddr_interface_num));

        // if more than 1 rank/DIMM, then unlock the deskew to let it self-adjust...
        if ((dimm_count > 1) || (num_ranks > 1)) {
            if ((s = lookup_env_parameter("ddr_unlock_deskew")) != NULL) {
                int unlock = strtoul(s, NULL, 0);
                if (unlock == unlock_envvar) { // only when the envvar matches the arg
                    phy_ctl.s.phy_dsk_lock_en = 0;
                    DRAM_CSR_WRITE(node, BDK_LMCX_PHY_CTL(ddr_interface_num), phy_ctl.u);
                    BDK_CSR_READ(node, BDK_LMCX_PHY_CTL(ddr_interface_num));

                    ddr_print("N%d.LMC%d: Unlocking DESKEW at end of LMC init.\n",
                              node, ddr_interface_num);

                    for (int rankx = 0; rankx < 4; rankx++) {
                        deskew_data_t dskdat;
                        if (! (rank_mask & (1 << rankx)))
                            continue;
                        Get_Deskew_Settings(node, ddr_interface_num, rankx, &dskdat);
                        Display_Deskew_Settings(node, ddr_interface_num, rankx, &dskdat, RD_DSK, VBL_DEV, "DSKUN");
                    }
                }
            }
        }
    }
#endif /* ALLOW_DESKEW_UNLOCK */
}

/*
 * 6.9.14 Final LMC Initialization
 *
 * Early LMC initialization, LMC write-leveling, and LMC read-leveling
 * must be completed prior to starting this final LMC initialization.
 *
 * LMC hardware updates the LMC(0)_SLOT_CTL0, LMC(0)_SLOT_CTL1,
 * LMC(0)_SLOT_CTL2 CSRs with minimum values based on the selected
 * readleveling and write-leveling settings. Software should not write
 * the final LMC(0)_SLOT_CTL0, LMC(0)_SLOT_CTL1, and LMC(0)_SLOT_CTL2
 * values until after the final read-leveling and write-leveling settings
 * are written.
 *
 * Software must ensure the LMC(0)_SLOT_CTL0, LMC(0)_SLOT_CTL1, and
 * LMC(0)_SLOT_CTL2 CSR values are appropriate for this step. These CSRs
 * select the minimum gaps between read operations and write operations
 * of various types.
 *
 * Software must not reduce the values in these CSR fields below the
 * values previously selected by the LMC hardware (during write-leveling
 * and read-leveling steps above).
 *
 * All sections in this chapter may be used to derive proper settings for
 * these registers.
 *
 * For minimal read latency, L2C_CTL[EF_ENA,EF_CNT] should be programmed
 * properly. This should be done prior to the first read.
 */

void Perform_Final_LMC_Init(bdk_node_t node, int ddr_interface_num,
                                   dram_init_data_t *init_data,
                                   dram_overrides_t *overrides)
{
    //Setup SLOT_CTL Access if enabled
    Setup_SLOT_CTL_ACCESS(node, ddr_interface_num);

    //Clear any residual ECC errors caused by Training
    Clear_LMC_ECC_Errors(node, ddr_interface_num);

    //Setup scrambling if desired
    Setup_Final_Scrambling(node, ddr_interface_num, init_data, overrides);

    // Unlock deskew if the facility is enabled and the unlock_deskew envvar is 2
    Perform_Deskew_Unlock(node, ddr_interface_num, /*envvar*/2, init_data, overrides);
}

