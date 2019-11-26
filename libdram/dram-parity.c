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

// func: inject_parity_error
// injection of a parity error
/*static*/ void
inject_parity_error(bdk_node_t node, int lmc, int sel_value)
{
    // FIXME: this appears to be broken in 83xx
    bdk_lmcx_ecc_parity_test_t test;

    test.u = BDK_CSR_READ(node, BDK_LMCX_ECC_PARITY_TEST(lmc));
    test.s.ca_parity_sel = sel_value;
    test.s.ca_parity_corrupt_ena = 1;
    DRAM_CSR_WRITE(node, BDK_LMCX_ECC_PARITY_TEST(lmc), test.u);

    test.u = BDK_CSR_READ(node, BDK_LMCX_ECC_PARITY_TEST(lmc));
    ddr_print("N%d.LMC%d: PARITY: ERROR INJECTION: sel 0x%02x, corrupt_ena %d\n",
              node, lmc, test.s.ca_parity_sel, test.s.ca_parity_corrupt_ena);
}

// func: check_inject_parity_error
// check for injection of a parity error
/*static*/ void
check_inject_parity_error(bdk_node_t node, int lmc)
{
    // FIXME: this appears to be broken in 83xx
    bdk_lmcx_ecc_parity_test_t test;
    test.u = BDK_CSR_READ(node, BDK_LMCX_ECC_PARITY_TEST(lmc));
    ddr_print("N%d.LMC%d: PARITY: Checking ERROR INJECTION: sel 0x%02x, corrupt_ena %d\n",
              node, lmc, test.s.ca_parity_sel, test.s.ca_parity_corrupt_ena);

    // finally, check for DDR_ERR
    if (bdk_is_model(OCTEONTX_CN8XXX))
        check_cn8xxx_lmc(node, lmc, 0);
    else
        bdk_check_parity_errors_cn9xxx_lmc(node, lmc);
}

static void
write_MR5_with_defaults(bdk_node_t node, int lmc, int rank_mask)
{
    bdk_lmcx_mr_mpr_ctl_t lmc_mr_mpr_ctl;
    int rank;

    ddr_print("N%d.LMC%d: PARITY: Write MR5 to clear parity error\n",
              node, lmc);

    // FIXME: Do NOT fetch CSR, just zero all fields initially
    lmc_mr_mpr_ctl.u = 0;
    lmc_mr_mpr_ctl.s.mr_wr_use_default_value = 1;
    lmc_mr_mpr_ctl.s.mr_wr_sel  = 5;

    for (rank = 0; rank < 4; rank++) {

        if (! (rank_mask & (1 << rank))) continue;

        lmc_mr_mpr_ctl.s.mr_wr_rank = rank;

        DRAM_CSR_WRITE(node, BDK_LMCX_MR_MPR_CTL(lmc), lmc_mr_mpr_ctl.u);
        BDK_CSR_READ(node, BDK_LMCX_MR_MPR_CTL(lmc));

        perform_octeontx_ddr_sequence(node, (1 << rank), lmc, 0x8); /* Mode Register Write */
        bdk_wait_usec_noyield(100); // FIXME???
    }
}

static void
write_RC06_clear_parity_cmd(bdk_node_t node, int lmc, int rank_mask)
{
    int rank, dimm;

    ddr_print("N%d.LMC%d: PARITY: DIMM RCD: Clear Parity Error (RC06=6)\n",
              node, lmc);

    for (rank = 0; rank < 4; rank += 2) {
        bdk_lmcx_dimmx_params_t lmc_dimmx_params;

        if (! (rank_mask & (1 << rank))) continue;
        dimm = rank >> 1;

        lmc_dimmx_params.u = BDK_CSR_READ(node, BDK_LMCX_DIMMX_PARAMS(lmc, dimm));
        lmc_dimmx_params.s.rc6 = 6; // clear CA parity error
        VB_PRT(VBL_DEV2, "N%d.LMC%d: PARITY: DIMM%d Register Control Word RC06: %x\n",
               node, lmc, dimm, lmc_dimmx_params.s.rc6);
        DRAM_CSR_WRITE(node, BDK_LMCX_DIMMX_PARAMS(lmc, dimm), lmc_dimmx_params.u);
    }

    // set mask for write to only RC06
    bdk_lmcx_dimm_ctl_t lmc_dimm_ctl;
    lmc_dimm_ctl.u = BDK_CSR_READ(node, BDK_LMCX_DIMM_CTL(lmc));
    lmc_dimm_ctl.s.dimm0_wmask = (1 << 6);
    lmc_dimm_ctl.s.dimm1_wmask = (rank_mask & 0x0C) ? (1 << 6) : 0;
    VB_PRT(VBL_DEV2, "N%d.LMC%d: PARITY: DIMM_CTL: 0x%016lx\n",
           node, lmc, lmc_dimm_ctl.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_DIMM_CTL(lmc), lmc_dimm_ctl.u);

    /* Don't write any extended registers */
    DRAM_CSR_WRITE(node, BDK_LMCX_DDR4_DIMM_CTL(lmc), 0);

    BDK_CSR_READ(node, BDK_LMCX_DIMM_CTL(lmc));

    perform_octeontx_ddr_sequence(node, rank_mask, lmc, 0x7); /* Init RCW */
}

// func: clear_parity_error
// clear appropriate bits for an LMC parity error (DDR_ERR)
void
clear_parity_error(bdk_node_t node, int lmc)
{
    BDK_CSR_INIT(config, node, BDK_LMCX_CONFIG(lmc));
    BDK_CSR_INIT(control, node, BDK_LMCX_CONTROL(lmc));

    // FIXME: regardless of active parity mode on RCD, if it is an RDIMM,
    //        we will need to clear the register's parity latch...
    if (control.s.rdimm_ena)
        write_RC06_clear_parity_cmd(node, lmc, config.s.init_status);

    write_MR5_with_defaults(node, lmc, config.s.init_status);
}

// func: print_parity_error
// print appropriate MPR bits for an LMC parity error (DDR_ERR)
void
print_parity_error(bdk_node_t node, int lmc)
{
    BDK_CSR_INIT(config, node, BDK_LMCX_CONFIG(lmc));

    Display_Full_MPR_Page_Location(node, lmc, config.s.init_status,
                                   /*page*/1, /*location*/3);
}

// func: set_dram_parity_mode
// write to the DRAM to turn ON or OFF its PARITY mode
static int
set_dram_parity_mode(bdk_node_t node, int lmc, int rank_mask, int dimm_count, int on)
{
    /*****
      To turn on parity checking in the DRAM, set the following CSRs:

      1. EXT_CONFIG:
         - GEN_PAR = 1.
         - Unless we're using 16Gb x4 DRAMs (where address A17 pin is used), set PAR_INCLUDE_A17 = 0.

      2. MODEREG_PARAMS3[PAR_LAT_MODE] = X
         Where X = 1 for DDR4-1600, 1866, 2133
                 = 2 for DDR4-2400, 2666
                 = 3 for DDR4-2933, 3200

      3. MR_MPR_CTL:
         - MR_WR_BG1 = 0
         - MR_WR_USE_DEFAULT_VALUE = 1
         - MR_WR_RANK = rank of interest
         - MR_WR_SEL = 5 (this is to target DRAM's MR5).

      4. Run MRW sequence.

      5. Repeat 3-4 for different ranks.

      6. Set PHY_CTL[DDR_ERROR_N_ENA] = 1.

*****/

    ddr_print("N%d.LMC%d: PARITY: set_dram_parity_mode: rank_mask 0x%x, on %d\n",
              node, lmc, rank_mask, on);

    // PAR_LAT_MODE setting depends on speed - use MODEREG_PARAMS0[cwl]
    BDK_CSR_INIT(params0, node, BDK_LMCX_MODEREG_PARAMS0(lmc));
    int speed_bin = (params0.s.cwl < 3) ? 1 : ((params0.s.cwl < 5) ? 2 : 3) ;

    DRAM_CSR_MODIFY(params3, node, BDK_LMCX_MODEREG_PARAMS3(lmc),
                    params3.s.par_lat_mode = (on) ? speed_bin : 0);
    ddr_print("N%d.LMC%d: PARITY: LMCX_MODEREG_PARAMS0[par_lat_mode]: set to %d\n",
              node, lmc, ((on) ? speed_bin : 0));

    { // Use the RETRY_CONFIG CSR to make handling cleaner, esp. for injection
        int do_enable = (on);
        const char *s;
        if ((s = lookup_env_parameter("ddr_retry_enable")) != NULL) {
            do_enable = !!strtoul(s, NULL, 0);
        }
        // must set RETRY_CONFIG[retry_enable] to ON
        DRAM_CSR_MODIFY(retry_cfg, node, BDK_LMCX_RETRY_CONFIG(lmc),
                        retry_cfg.s.retry_enable = do_enable;
                        retry_cfg.s.auto_error_continue = 1);
        ddr_print("N%d.LMC%d: PARITY: LMCX_RETRY_CONFIG[retry_enable]: set to %d\n",
                  node, lmc, do_enable);
    }

    if (on) {
        // now SET the N_ENABLE bit
        DRAM_CSR_MODIFY(phy, node, BDK_LMCX_PHY_CTL(lmc),
                        phy.s.ddr_error_n_ena = 1);
        ddr_print("N%d.LMC%d: PARITY: LMCX_PHY_CTL[ddr_error_n_ena]: set to %d\n",
                  node, lmc, on);
        BDK_CSR_READ(node, BDK_LMCX_PHY_CTL(lmc));
    }

    // this also runs the MRW sequence
    clear_parity_error(node, lmc);

    if (!on) {
        // now RESET the N_ENABLE bit
        DRAM_CSR_MODIFY(phy, node, BDK_LMCX_PHY_CTL(lmc),
                        phy.s.ddr_error_n_ena = 0);
        ddr_print("N%d.LMC%d: PARITY: LMCX_PHY_CTL[ddr_error_n_ena]: set to %d\n",
                  node, lmc, on);
        BDK_CSR_READ(node, BDK_LMCX_PHY_CTL(lmc));
    }

    return 0;
}

// func: set_register_parity_mode
// write to the RDIMM register to turn ON or OFF its PARITY mode
static int
set_register_parity_mode(bdk_node_t node, int lmc, int rank_mask, int dimm_count, int on)
{
    int dimm;

    BDK_CSR_INIT(control, node, BDK_LMCX_CONTROL(lmc));
    if (!control.s.rdimm_ena) // ignore non-RDIMMs...
        return 0;

    ddr_print("N%d.LMC%d: PARITY: set_register_parity_mode: rank_mask 0x%x, on %d\n",
              node, lmc, rank_mask, on);

    // when turning ON, this must be set *before* RC0E=1
    DRAM_CSR_MODIFY(ext, node, BDK_LMCX_EXT_CONFIG(lmc),
                    ext.s.rcd_parity_check = !!on);

    write_MR5_with_defaults(node, lmc, rank_mask); // FIXME? do we need this?

    for (dimm = 0; dimm < 2; dimm += 1) {
        bdk_lmcx_dimmx_params_t lmc_dimmx_params;

        lmc_dimmx_params.u = BDK_CSR_READ(node, BDK_LMCX_DIMMX_PARAMS(lmc, dimm));
        lmc_dimmx_params.s.rc14 &= 0x06; // turn off both enable and re-enable
        lmc_dimmx_params.s.rc14 |= (!!on) | ((!!on) << 3); // parity checking enable and re-enable
        ddr_print("N%d.LMC%d: LRDIMM: DIMM%d Register Control Word RC0E: %x\n",
                  node, lmc, dimm, lmc_dimmx_params.s.rc14);
        DRAM_CSR_WRITE(node, BDK_LMCX_DIMMX_PARAMS(lmc, dimm), lmc_dimmx_params.u);
    }

    // set mask for write to only RC0E
    bdk_lmcx_dimm_ctl_t lmc_dimm_ctl;
    lmc_dimm_ctl.u = BDK_CSR_READ(node, BDK_LMCX_DIMM_CTL(lmc));
    lmc_dimm_ctl.s.dimm0_wmask = (1 << 14);
    lmc_dimm_ctl.s.dimm1_wmask = (dimm_count > 1) ? (1 << 14) : 0;
    ddr_print("N%d.LMC%d: LRDIMM: DIMM_CTL: 0x%016lx\n",
              node, lmc, lmc_dimm_ctl.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_DIMM_CTL(lmc), lmc_dimm_ctl.u);

    /* Don't write any extended registers */
    DRAM_CSR_WRITE(node, BDK_LMCX_DDR4_DIMM_CTL(lmc), 0);

    BDK_CSR_READ(node, BDK_LMCX_DIMM_CTL(lmc));

    perform_octeontx_ddr_sequence(node, rank_mask, lmc, 0x7); /* Init RCW */


    // now set or reset the n_enable bit
    DRAM_CSR_MODIFY(phy, node, BDK_LMCX_PHY_CTL(lmc),
                    phy.s.ddr_error_n_ena = !!on);

    return 0;
}

#if 0
// func: set_databuffer_parity_mode
// write to the Data Buffers to turn ON or OFF their PARITY mode
/*static*/ int
set_databuffer_parity_mode(bdk_node_t node, int lmc, int rank_mask, int dimm_count, int on)
{
    ddr_print("N%d.LMC%d: PARITY: IMPDEL: set_databuffer_parity_mode: rank_mask 0x%x, on %d\n",
              node, lmc, rank_mask, on);

    return 0;
}
#endif

// func: set_parity_mode
// write to the appropriate devices to turn ON or OFF their PARITY mode
int
Set_Parity_Mode(bdk_node_t node, int lmc,
                dram_init_data_t *init_data,
                dram_overrides_t *overrides,
                int on)
{
    int dimm_count =        init_data->refs.dimm_count;
    int rank_mask =         init_data->refs.rank_mask;
    int parity_mode =       overrides->init.parity_mode;

    // if PARITY mode has not been configured, do nothing...
    if (!parity_mode)
        return 0;

    ddr_print("N%d.LMC%d: PARITY: %sabling...\n",
              node, lmc, (!!on) ? "en" : "dis" );

    // always do the DRAMs
    set_dram_parity_mode(node, lmc, rank_mask, dimm_count, !!on);

    // FIXME: this is not yet fully implemented or tested
    // this is for the RCD of an (L)RDIMM
    set_register_parity_mode(node, lmc, rank_mask, dimm_count, !!on);

    // this is for the Data Buffers of an LRDIMM if/when actually implemented
    //set_databuffer_parity_mode(node, lmc, rank_mask, dimm_count, !!on);

    if (bdk_is_model(OCTEONTX_CN8XXX)) {

        // NOTE: this must be done for pass 2.x
        // must enable ECC interrupts to get ECC/DDR error info in LMCX_INT
        DRAM_CSR_WRITE(node, BDK_LMCX_INT(lmc), -1ULL); // clear first
        DRAM_CSR_WRITE(node, BDK_LMCX_INT_ENA_W1S(lmc), -1ULL); // now enable
        BDK_CSR_INIT(lmc_int_ena_w1s, node, BDK_LMCX_INT_ENA_W1S(lmc));
        ddr_print("%-45s : 0x%08lx\n", "LMC_INT_ENA_W1S", lmc_int_ena_w1s.u);

    } else { // CN9XXX
#if 0
        /* Set LMC_INT_ENA[ddr_err] which is CRC/Parity */
        BDK_CSR_INIT(int_ena_w1s, node, BDK_LMCX_INT_ENA_W1S(lmc));
        int_ena_w1s.s.ddr_err = !!on;
        DRAM_CSR_WRITE(node, BDK_LMCX_INT_ENA_W1S(lmc), int_ena_w1s.u);
        ddr_print("N%d.LMC%d: PARITY: %-28s : 0x%08lx\n",
                  node, lmc, "LMC_INT_ENA_W1S", int_ena_w1s.u);
#endif
        /* Set LMC_RAS ERR00 which is CRC/Parity */
        DRAM_CSR_WRITE(node, BDK_LMCX_RAS_INT_ENA_W1S(lmc), !!on);
        BDK_CSR_INIT(lmc_ras_int_ena_w1s, node, BDK_LMCX_RAS_INT_ENA_W1S(lmc));
        ddr_print("N%d.LMC%d: PARITY: %-28s : 0x%08lx\n",
                  node, lmc, "LMC_RAS_INT_ENA_W1S", lmc_ras_int_ena_w1s.u);

        // Set the fault handling interrupts in the controller CSR
        BDK_CSR_INIT(err_ctlr, node, BDK_LMCX_RAS_ERR00CTLR(lmc));
        err_ctlr.s.cfi = !!on;
        err_ctlr.s.fi = !!on;
        DRAM_CSR_WRITE(node, BDK_LMCX_RAS_ERR00CTLR(lmc), err_ctlr.u);
        ddr_print("N%d.LMC%d: PARITY: %-28s : 0x%08lx\n",
                  node, lmc, "LMC_RAS_ERR00CTLR[cfi,fi]", err_ctlr.u);

        // MUST set the counter CSR to overflow on next to force reporting
        BDK_CSR_INIT(misc0, node, BDK_LMCX_RAS_ERR00MISC0(lmc));
        misc0.s.cec = 0x7FFF; // set Corrected_Error_Counter FULL
        misc0.s.of = 0; // set OVERFLOW clear
        DRAM_CSR_WRITE(node, BDK_LMCX_RAS_ERR00MISC0(lmc), misc0.u);
        ddr_print("N%d.LMC%d: PARITY: %-28s : 0x%08lx\n",
                  node, lmc, "LMC_RAS_ERR00MISC0[of,cec]", misc0.u);
    }

    return 0;
}

// called from: bdk-early-lmc-init.c:Setup_LMCX_EXT_CONFIG()
void
Setup_EXT_CONFIG_for_parity_mode(bdk_node_t node, int ddr_interface_num, 
                                 dram_init_data_t *init_data,
                                 dram_overrides_t *overrides,
                                 bdk_lmcx_ext_config_t *ext_config)
{
    int die_capacity =      init_data->spd.die_capacity;
    int dram_width =        init_data->refs.dram_width;
    int parity_mode =       overrides->init.parity_mode;
    const char *s;

    // for parity checking purposes
    if (parity_mode) {

        ext_config->s.gen_par = 1;
        ext_config->s.par_include_a17 = (((die_capacity >> 10) >= 16) && (dram_width == 4)) ? 1 : 0;
        ext_config->s.par_include_bg1 = (dram_width != 16) ? 1 : 0;

        ext_config->s.ea_int_polarity = 0; // this is the default/RESET value
        if ((s = lookup_env_parameter("ddr_ea_int_polarity")) != NULL) {
            ext_config->s.ea_int_polarity = !!strtoul(s, NULL, 0);
        }

        ext_config->s.par_addr_mask = 0x07; // this is the default/RESET value
        if ((s = lookup_env_parameter("ddr_par_addr_mask")) != NULL) {
            ext_config->s.par_addr_mask = strtoul(s, NULL, 0);
        }

        ddr_print("N%d.LMC%d: PARITY: EXT_CONFIG[gen_par=%d, inc_a17=%d, inc_bg1=%d, polarity=%d, addr_mask=%x]\n",
                  node, ddr_interface_num, ext_config->s.gen_par,
                  ext_config->s.par_include_a17, ext_config->s.par_include_bg1,
                  ext_config->s.ea_int_polarity, ext_config->s.par_addr_mask);
    }
}

// func: Change_Parity_Generation
void
Change_Parity_Generation(bdk_node_t node, int lmc,
                         dram_init_data_t *init_data,
                         dram_overrides_t *overrides,
                         int gen_par)
{
    int parity_mode = overrides->init.parity_mode;
    if (parity_mode) {
        DRAM_CSR_MODIFY(ext, node, BDK_LMCX_EXT_CONFIG(lmc), 
                        ext.s.gen_par = gen_par);
    }
    return;
}

