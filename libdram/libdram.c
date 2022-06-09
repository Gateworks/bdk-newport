/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-ccs.h"
#include "libbdk-arch/bdk-csrs-mio_fus.h"
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libbdk-arch/bdk-csrs-mcc.h"
#include "libbdk-arch/bdk-csrs-rst.h"
#include "libdram.h"
#include "dram-internal.h"
#include "bdk-dram-init.h"

// Set this to 1 to cause all of memory to be destructively written
// when RESET is initiated, and then a test of all of memory contents
// will be done during recovery.
#define TEST_PRESERVE_MEM  0

// allows direct checking for ECC errors, not polled
//extern void bdk_check_ecc_errors_cn9xxx(bdk_node_t node);

/* This global variable is accessed through dram_is_verbose() to determine
   the verbosity level. Use that function instead of setting it directly */
dram_verbosity_t dram_verbosity = VBL_OFF; /* init this here so we could set a non-zero default */

static uint32_t measured_ddr_hertz[BDK_NUMA_MAX_NODES];

/* The various DRAM configs in the libdram/configs directory need space
   to store the DRAM config. Since only one config is ever in active use
   at a time, store the configs in __libdram_global_cfg. In a multi-node
   setup, independent calls to get the DRAM config will load first node 0's
   config, then node 1's */
dram_config_t __libdram_global_cfg;

void bdk_dram_rewrite_bdk(bdk_node_t node, uint64_t skip)
{
    /* All memory below skip may contain valid data, so we can't clear
     * it. We still need to make sure all cache lines in this area are
     * fully dirty so that ECC bits will be updated on store. A single
     * write to the cache line isn't good enough because partial LMC
     * writes may be enabled.
     */
    volatile uint64_t *ptr = bdk_phys_to_ptr(bdk_numa_get_address(node, 8));
    /* The above pointer got address 8 to avoid NULL pointer checking
       in bdk_phys_to_ptr(). Correct it here */
    ptr--;

    uint64_t *end = bdk_phys_to_ptr(bdk_numa_get_address(node, skip));
    while (ptr < end) {
        *ptr = *ptr;
        ptr++;
    }
}

static void bdk_dram_clear_mem(bdk_node_t node)
{
    if (!bdk_is_platform(BDK_PLATFORM_ASIM)) {
        uint64_t mbytes = bdk_dram_get_size_mbytes(node);
        uint64_t skip = (node == bdk_numa_master()) ? bdk_dram_get_top_of_bdk() : 0;
        uint64_t len =  (mbytes << 20) - skip;

        //VB_PRT(VBL_DEV, "N%d: Before clearing DRAM: Waiting for a sec...\n", node);
        //bdk_wait_usec(1000000); // wait a sec...

        if (ddr_memory_preserved(node)) {
            ddr_print("N%d: Preserve DRAM contents: start 0x%lx length 0x%lx\n",
                      node, skip, len);
#if TEST_PRESERVE_MEM
            ddr_print("N%d: Preserve DRAM: TESTING contents...\n", node);
            // check memory contents as part of testing preservation
            int ecount = 0;
            for (uint64_t i = 0; i < len; i += 128) { // FIXME? skip by cacheblock size?
                uint64_t temp = __bdk_dram_read64(skip + i); 
                if (temp != 0xbaadf00ddeadbeefUL) {
                    uint64_t first = skip + i;
                    while ((i < len) && (__bdk_dram_read64(skip + i) != 0xbaadf00ddeadbeefUL)) i += 128;
                    bdk_error("N%d: Preserve Memory FAILED!! contents at [0x%lx:0x%lx] incorrect\n",
                              node, first, skip + i);
                    ecount++;
                    //if (ecount >= 10) break;
                }
            }
#endif /* TEST_PRESERVE_MEM */
        } else {
            ddr_print("N%d: Clearing DRAM: start 0x%lx length 0x%lx\n", node, skip, len);
            BDK_TRACE(DRAM, "N%d: Clearing DRAM\n", node);
            bdk_zero_memory(bdk_phys_to_ptr(bdk_numa_get_address(node, skip)), len);
            BDK_TRACE(DRAM, "N%d: DRAM clear complete\n", node);
        }
    }
}

static void bdk_dram_clear_ecc(bdk_node_t node)
{
    /* Clear any DRAM errors set during init */
    int num_lmc = __bdk_dram_get_num_lmc(node);
    int lmc_mask = __bdk_dram_get_lmc_mask(node);
    BDK_TRACE(DRAM, "N%d: Clearing LMC ECC errors\n", node);
    for (int lmc = 0; lmc < num_lmc; lmc++) {
        if (!(lmc_mask & (1 << lmc)))
            continue;
        Clear_LMC_ECC_Errors(node, lmc);
    }
}

static void bdk_dram_enable_ecc_reporting(bdk_node_t node)
{
    /* Enable LMC ECC error HW reporting */
    int num_lmc = __bdk_dram_get_num_lmc(node);
    int lmc_mask = __bdk_dram_get_lmc_mask(node);
    BDK_TRACE(DRAM, "N%d: Enable LMC ECC error reporting\n", node);
    for (int lmc = 0; lmc < num_lmc; lmc++) {
        if (!(lmc_mask & (1 << lmc)))
            continue;
        Setup_ECC_Error_Reporting(node, lmc, 1/*enable*/);
    }
}

static void bdk_dram_disable_ecc_reporting(bdk_node_t node)
{
    /* Disable LMC ECC error HW reporting */
    int num_lmc = __bdk_dram_get_num_lmc(node);
    int lmc_mask = __bdk_dram_get_lmc_mask(node);
    BDK_TRACE(DRAM, "N%d: Disable LMC ECC error reporting\n", node);
    for (int lmc = 0; lmc < num_lmc; lmc++) {
        if (!(lmc_mask & (1 << lmc)))
            continue;
        Setup_ECC_Error_Reporting(node, lmc, 0/*disable*/);
    }
}

// this routine simply makes the calls to the tuning routines and returns any errors
static int bdk_libdram_tune_node(int node)
{
    int errs, tot_errs;
    int do_dllro_hw = 0; // default to NO
    int do_dllwo = 0; // default to NO
    int do_eccdll = 0; // default to NO
    const char *str;
    BDK_CSR_INIT(lmc_config, node, BDK_LMCX_CONFIG(0)); // FIXME: probe LMC0
    do_eccdll = (lmc_config.s.ecc_ena != 0); // change to ON if ECC enabled

    // FIXME!!! make 81xx and 9xxx always use HW-assist tuning
    if (bdk_is_model(OCTEONTX_CN81XX) || bdk_is_model(OCTEONTX_CN9XXX))
        do_dllro_hw = 1;

    // Automatically tune the data byte DLL read offsets
    // always done by default, but allow use of HW-assist
    // NOTE: HW-assist will also tune the ECC byte
    str = getenv("ddr_tune_hw_offsets");
    if (str)
        do_dllro_hw = !!strtoul(str, NULL, 0);
    BDK_TRACE(DRAM, "N%d: Starting DLL Read Offset Tuning for LMCs\n", node);
    if (!do_dllro_hw) {
        errs = perform_dll_offset_tuning(node, /*read*/2, /*tune*/1);
    } else {
        errs = perform_HW_dll_offset_tuning(node, /*read*/2, 0x0A/* all bytelanes */);
    }
    BDK_TRACE(DRAM, "N%d: Finished DLL Read Offset Tuning for LMCs, %d errors)\n",
              node, errs);
    tot_errs = errs;

    // disabled by default for now, does not seem to be needed?
    // Automatically tune the data byte DLL write offsets
    // allow override of default setting
    str = getenv("ddr_tune_write_offsets");
    if (str)
        do_dllwo = !!strtoul(str, NULL, 0);
    if (do_dllwo) {
        BDK_TRACE(DRAM, "N%d: Starting DLL Write Offset Tuning for LMCs\n", node);
        if (!do_dllro_hw) {
            errs = perform_dll_offset_tuning(node, /*write*/1, /*tune*/1);
        } else {
            errs = perform_HW_dll_offset_tuning(node, /*write*/1, 0x0A/* all bytelanes */);
        }
        BDK_TRACE(DRAM, "N%d: Finished DLL Write Offset Tuning for LMCs, %d errors)\n",
                  node, errs);
        tot_errs += errs;
    }

    // disabled by default for now, does not seem to be needed much?
    // Automatically tune the ECC byte DLL read offsets
    // FIXME? allow override of the filtering
    // FIXME? allow programmatic override, not via envvar?
    str = getenv("ddr_tune_ecc_enable");
    if (str)
        do_eccdll = !!strtoul(str, NULL, 10);
    if (do_eccdll && !do_dllro_hw && (lmc_config.s.mode32b == 0)) { // do not do HW-assist twice for ECC
        BDK_TRACE(DRAM, "N%d: Starting ECC DLL Read Offset Tuning for LMCs\n", node);
        errs = perform_HW_dll_offset_tuning(node, 2, 8/* ECC bytelane */);
        BDK_TRACE(DRAM, "N%d: Finished ECC DLL Read Offset Tuning for LMCs, %d errors\n",
                  node, errs);
        tot_errs += errs;
    }

    return tot_errs;
}

// this routine makes the calls to the tuning routines when criteria are met
// intended to be called for automated tuning, to apply filtering...

#define IS_RDIMM 1
#define IS_UDIMM 0
#define IS_1SLOT 1
#define IS_2SLOT 0

static const uint32_t ddr_speed_filter[2][2] = {
    [IS_RDIMM] = {
        [IS_1SLOT] =  940,
        [IS_2SLOT] =  800
    },
    [IS_UDIMM] = {
        [IS_1SLOT] = 1050,
        [IS_2SLOT] =  940
    }
};

static int bdk_libdram_maybe_tune_node(int node)
{
    const char *str;
    int ret = 0;

    if (ddr_memory_preserved(node)) {
        ddr_print("N%d: Tuning disabled to preserve memory.\n", node);
        return 0;
    }

    // FIXME: allow an override here so that all configs can be tuned or none
    // If the envvar is defined, always either force it or avoid it accordingly
    if ((str = getenv("ddr_tune_all_configs")) != NULL) {
        int tune_it = !!strtoul(str, NULL, 0);
        printf("N%d: DRAM auto-tuning %s.\n", node, (tune_it) ? "forced" : "avoided");
        if (tune_it)
            ret = bdk_libdram_tune_node(node);
        return ret;
    }

    // FIXME: disable tuning for CN9XXX for now, if we did not already force it above...
    if (bdk_is_model(OCTEONTX_CN9XXX)) {
        VB_PRT(VBL_DEV, "N%d: CN9XXX: DRAM DLL tuning disabled temporarily.\n", node);
        return ret;
    }

    // filter the tuning calls here...
    // determine if we should/can run automatically for this configuration
    //
    // FIXME: tune only when the configuration indicates it will help:
    //        RDIMM or UDIMM, 1-slot or 2-slot, and speed
    //
    uint32_t ddr_speed = divide_nint(libdram_get_freq_from_pll(node, 0), 1000000); // sample LMC0
    BDK_CSR_INIT(lmc_config, node, BDK_LMCX_CONFIG(0)); // sample LMC0

    int is_rdimm = !!__bdk_dram_is_rdimm(node, 0);
    int is_1slot = !!(lmc_config.s.init_status < 4); // HACK, should do better
    int do_tune = 0;

    uint32_t ddr_min_speed = ddr_speed_filter[is_rdimm][is_1slot];
    do_tune = (ddr_min_speed && (ddr_speed > ddr_min_speed));

    ddr_print("N%d: DDR4 %cDIMM %d-slot at %d MHz %s eligible for auto-tuning.\n",
              node, (is_rdimm)?'R':'U', (is_1slot)?1:2, ddr_speed, (do_tune)?"is":"is not");

    // call the tuning routines, done filtering...
    if (do_tune)
        ret = bdk_libdram_tune_node(node);

    return ret;
}

static void bdk_dram_disable_all_pll(bdk_node_t node)
{
    int num_lmc = __bdk_dram_get_num_lmc(node);
    int lmc_mask = __bdk_dram_get_lmc_mask(node);

    BDK_TRACE(DRAM, "N%d: Disable DRAM \n", node);

    for (int lmc = 0; lmc < num_lmc; lmc++) {

        if (!(lmc_mask & (1 << lmc)))
            continue;

        BDK_CSR_INIT(ddr_pll_ctl, node, BDK_LMCX_DDR_PLL_CTL(lmc));
        if (bdk_is_model(OCTEONTX_CN8XXX)) {
            /* Disable DRAM by setting all DDR_PLL_CTL[reset_n] = 0 */
            ddr_pll_ctl.cn83xx.reset_n = 0;
        } else {
            /* Disable DRAM by setting all DDR_PLL_CTL[pll_reset] = 1
               and DDR_PLL_CTL[pll_sel] = 0 */
            ddr_pll_ctl.cn9.pll_reset = 1;
            ddr_pll_ctl.cn9.pll_sel   = 0;
        }
        DRAM_CSR_WRITE(node, BDK_LMCX_DDR_PLL_CTL(lmc), ddr_pll_ctl.u);
    }
}

/**
 * Set a bit in LMCX_RESET_CTL to indicate that DRAM training has already happened
 * so DRAM is not currupted by training when it returns after being held in DRAM
 * preserve mode (self-refresh).
 *
 * @param node              Node to save LMC training state on
 * @param interface_mask    Mask of memory channels enabled on this node
 */
static void
bdk_dram_set_training_complete(bdk_node_t node, int interface_mask)
{
    int lmc;

    if (bdk_is_model(OCTEONTX_CN8XXX)) // nothing to do
        return;

    for (lmc = 0; lmc < 3; lmc++) {
        if (interface_mask & (1 << lmc)) {
            ddr_print("N%d.LMC%d: DRAM init: Mark training complete.\n",
                      node, lmc);
            BDK_CSR_MODIFY(c, node, BDK_LMCX_RESET_CTL(lmc),
                           c.cn9.training_completed = 1);
        }
    }
}

/**
 * Enable the ECC Checker to generate and check ECC on memory transactions. 
 *
 * @param node              Node to enable ECC checking on
 * @param interface_mask    Mask of memory channels enabled on this node
 */
static void
bdk_dram_enable_ECC_checker(bdk_node_t node, int interface_mask)
{
    int lmc;

    if (bdk_is_model(OCTEONTX_CN8XXX))
        return;

    for (lmc = 0; lmc < 3; lmc++) {
        bdk_dram_lmc_map_t lmc_map = bdk_dram_get_lmc_map(node, lmc);
        if (interface_mask & (1 << lmc)) {
            ddr_print("N%d.LMC%d: DRAM init: Enable ECC checker.\n",
                      node, lmc);

            // enable the "ECC Checker" if we are doing ECC
            BDK_CSR_INIT(config, node, BDK_LMCX_CONFIG(lmc));
            BDK_CSR_MODIFY(d, node, BDK_MCCX_LMCOEX_CFG(lmc_map.mcc, lmc_map.lmcoe),
                           d.s.dram_ecc_ena = config.s.ecc_ena);
        }
    }
}

// most useful for debug
static void
bdk_dram_dump_ASC_table(bdk_node_t node, char *title, int verb)
{
    int i, empties;
    const char *mode_str[4] = {"FLAT_1", "UNDEF", "STRIPE_2", "STRIPE_3"};
    const char *mask_str[8] = {"EMPTY", "LMC0", "LMC1", "LMC0/LMC1",
                                "LMC2", "LMC0/LMC2", "LMC1/LMC2", "LMC0/LMC1/LMC2"};
    if (!dram_is_verbose(verb))
        return;

    printf("N%d: Dumping CCS_ASC Table \'%s\'.\n", node, title);
    empties = 0;
    for (i = 0; i < 16; i++) {
        BDK_CSR_INIT(attr,   node, BDK_CCS_ASC_REGIONX_ATTR(i));
        if (!attr.s.s_en && !attr.s.ns_en) {
            empties++;
        } else {
            BDK_CSR_INIT(start,  node, BDK_CCS_ASC_REGIONX_START(i));
            BDK_CSR_INIT(end,    node, BDK_CCS_ASC_REGIONX_END(i));
            BDK_CSR_INIT(offset, node, BDK_CCS_ASC_REGIONX_OFFSET(i));
            printf("ASC[%x]: %s, %s, ", i, mode_str[attr.s.lmc_mode & 3], mask_str[attr.s.lmc_mask]);
            if (attr.s.write_through) printf("WRT, ");
            if (attr.s.s_en)  printf("S_EN, ");
            if (attr.s.ns_en) printf("NS_EN, ");
            printf("<0x%x/0x%x/0x%x>\n", start.s.addr, end.s.addr, offset.s.offset);
        }
    }
    if (empties)
        printf("There are %d EMPTY entries\n", empties);
    return;
}

static void
bdk_dram_setup_mapping(int node, int interface_mask, int mbytes)
{
    int lmc_mode = -1;
    int entry = 0; /* ASC region 0 is used for secure memory in the BDK */
    uint64_t end = ((uint64_t)mbytes << 20) - 1;

    switch (bdk_pop(interface_mask)) {
        case 1:
            lmc_mode = BDK_CCS_LMC_MODE_E_FLAT_1;
            break;
        case 2:
            lmc_mode = BDK_CCS_LMC_MODE_E_STRIPE_2;
            break;
        case 3:
            lmc_mode = BDK_CCS_LMC_MODE_E_STRIPE_3;
            break;
        default:
            bdk_error("N%d: Entry is EMPTY!\n", node);
            return;
    }

    /* Read the ASC setting into locals so all writes to the ASC region can be
       grouped and completed quickly */
    BDK_CSR_INIT(asc_end, node, BDK_CCS_ASC_REGIONX_END(entry));
    BDK_CSR_INIT(asc_attr, node, BDK_CCS_ASC_REGIONX_ATTR(entry));

    /* ASC end is at the top of DRAM */
    asc_end.s.addr = (end >> 24);

    /* ASC ATTR use the LMCs in the correct mode */
    asc_attr.s.lmc_mode = lmc_mode;
    asc_attr.s.lmc_mask = interface_mask;
    asc_attr.s.ns_en = 0;
    asc_attr.s.s_en = 1;

    /* Complete all pending core accesses before changing the ASC region */
    BDK_ISB;
    BDK_MB;
    BDK_DSB;

    BDK_CSR_WRITE(node, BDK_CCS_ASC_REGIONX_END(entry), asc_end.u);
    BDK_CSR_WRITE(node, BDK_CCS_ASC_REGIONX_ATTR(entry), asc_attr.u);

    /* Complete all pending core accesses after changing the ASC region */
    BDK_ISB;
    BDK_MB;
    BDK_DSB;

    ddr_print("N%d: Setting ASC[%d]: mode %d mask %d end 0x%lx\n",
              node, entry, lmc_mode, interface_mask, (end >> 24));
}

/**
 * This is the main DRAM init function. Users of libdram should call this function,
 * avoiding the other internal function. As a rule, functions starting with
 * "libdram_*" are part of the external API and should be used.
 *
 * @param node   Node to initialize. This may not be the same node as the one running the code
 * @param dram_config
 *               DRAM configuration to use
 * @param ddr_clock_override
 *               If non-zeo, this overrides the DRAM clock speed in the config structure. This
 *               allows quickly testing of different DRAM speeds without modifying the basic
 *               config. If zero, the DRAM speed in the config is used.
 *
 * @return Amount of memory in MB. Zero or negative is a failure.
 */
int libdram_config(int node, const dram_config_t *dram_config, int ddr_clock_override)
{
    const char *str;

    if (bdk_is_platform(BDK_PLATFORM_ASIM))
        return bdk_dram_get_size_mbytes(node);

    int lmc;
    int lmc_limit = CN8_OR_CN9( 2, 3);
    int lmc_allow_mask = CN8_OR_CN9(3, 7);

    str = lookup_env_parameter("ddr_lmc_allow_mask");
    if (str) { // if the envvar was found, force the var to that setting
        lmc_allow_mask = strtoul(str, NULL, 0);
    }

    /* Boards may need to mux the TWSI connection between THUNDERX and the BMC.
       This allows the BMC to monitor DIMM temeratures and health */
    int gpio_select = -1;
    bdk_device_t *gpio_device = bdk_device_gpio_lookup(&gpio_select, BDK_CONFIG_DRAM_CONFIG_GPIO);
    if (gpio_select != -1)
        bdk_device_gpio_setup(gpio_device, gpio_select, true, 1, true, false);

    /* Read all the SPDs and store them in the device tree. They are needed by
       later software to populate SMBIOS information */
    for (lmc = 0; lmc < lmc_limit; lmc++) {
        if (!(lmc_allow_mask & (1 << lmc))) // bypass if not allowed
            continue;
        for (int dimm = 0; dimm < DDR_CFG_T_MAX_DIMMS; dimm++)
            read_entire_spd(node, (dram_config_t *)dram_config, lmc, dimm);
    }

    const ddr_configuration_t *ddr_config = dram_config->config;
    int ddr_clock_hertz = (ddr_clock_override) ? ddr_clock_override : dram_config->ddr_clock_hertz;
    if (ddr_clock_hertz == 0)  // 0 == AUTO
    {
        ddr_clock_hertz = dram_get_default_spd_speed(node, ddr_config);
        if (ddr_clock_hertz < 0) {
            printf("N%d: DRAM init: AUTO clock ILLEGAL configuration\n", node);
            return -1;
        }
    }
    int errs;

    // At this point, we only know the desired clock rate (ddr_clock_hertz).
    // We do not know whether we are configuring RDIMMs.
    // We also do not yet know if 100MHz alternate refclk is actually available.
    // so, if we are being asked for 2133MT/s or better, we still need to do:
    // 1. probe for RDIMMs (if not, 50MHz refclk is good enough)
    // 2. determine if 100MHz refclk is there, and switch to it before starting any configuration
    //
    // NOTES:
    // 1. dclk_alt_refclk_sel need only be set on LMC0 (see above disabled code)
    // 2. I think we need to first probe to see if we need it, and configure it then if dictated use
    // 3. then go on to configure at the selected refclk
    int ddr_refclk_hertz = bdk_clock_get_rate(node, BDK_CLOCK_MAIN_REF);
    int alt_refclk = bdk_config_get_int(BDK_CONFIG_DDR_ALT_REFCLK, node);

    str = lookup_env_parameter("ddr_100mhz_refclk");
    if (str) { // if the envvar was found, force it to that setting
        int do_100mhz = !!strtoul(str, NULL, 0);
        alt_refclk = (do_100mhz) ? 100 : 50;
    }

    dram_verbosity = bdk_config_get_int(BDK_CONFIG_DRAM_VERBOSE);

    // anything special for CN9 at the beginning of time?
    if (bdk_is_model(OCTEONTX_CN9XXX)) {

        // look at the ASC region table default setting
        bdk_dram_dump_ASC_table(node, "Before INIT", VBL_DEV);

        VB_PRT(VBL_DEV, "N%d: Disable ECC Checker.\n", node);
        for (lmc = 0; lmc < lmc_limit; lmc++) {
            if (!(lmc_allow_mask & (1 << lmc))) // bypass if not allowed
                continue;
            bdk_dram_lmc_map_t lmc_map = bdk_dram_get_lmc_map(node, lmc);
            DRAM_CSR_MODIFY(c, node, BDK_MCCX_LMCOEX_CFG(lmc_map.mcc, lmc_map.lmcoe),
                            c.s.dram_ecc_ena = 0);
        }
    } /* if (bdk_is_model(OCTEONTX_CN9XXX)) */

    // Here we check for fuses that limit the number of LMCs we can configure,
    //  but only on 83XX
    if (bdk_is_model(OCTEONTX_CN83XX)) {
        BDK_CSR_INIT(mio_fus_dat2, node, BDK_MIO_FUS_DAT2);
        if (mio_fus_dat2.s.lmc_half) {
            lmc_limit = 1; // limit LMCs to half present
            error_print("Only %d LMC(s)s supported for this Thunder model\n", lmc_limit);
        }
    }

    /* We need to calculate the interface mask based on the provided SPD
       addresses/contents */
    uint32_t interface_mask = 0;
    for (lmc = 0; lmc < lmc_limit; lmc++) {
        if (!(lmc_allow_mask & (1 << lmc))) // bypass if not allowed
            continue;
        // We need to check only DIMM 0 of each LMC for possible presence of the LMC.
        // This trusts that the board database is correctly configured.
        // Empty DIMM slots in present LMCs will be detected later.
        if (ddr_config[lmc].dimm_config_table[0].spd_addr ||
            ddr_config[lmc].dimm_config_table[0].spd_ptr)
            interface_mask |= 1 << lmc;

        // we know whether alternate refclk is always wanted
        // we also know already if we want 2133 MT/s
        // if alt refclk not always wanted, then probe DDR and DIMM type
        // if DDR4 and RDIMMs, then set desired refclk to 100MHz, otherwise to default (50MHz)
        // depend on ddr_initialize() to do the refclk selection and validation
        if ((bdk_is_model(OCTEONTX_CN8XXX)) && (lmc == 0)) { // only check for LMC0 on 8XXX
            if (alt_refclk) { // if alternate refclk was specified, let it override everything
                ddr_refclk_hertz = alt_refclk * 1000000;
                ddr_print("N%d: DRAM init: %d MHz refclk is REQUESTED ALWAYS\n", node, alt_refclk);
            } else if (ddr_clock_hertz > 1000000000) { // if more than 2000 MT/s
                int spd_dimm_type = get_dimm_module_type(node, &ddr_config[0].dimm_config_table[0]);
                // is RDIMM just to be sure
                if (((spd_dimm_type == 1) || (spd_dimm_type == 5) || (spd_dimm_type == 8))) {
                    ddr_refclk_hertz = 100000000; // yes, we require 100MHz refclk, so set it
                    ddr_print("N%d: DRAM init: 100 MHz refclk is REQUIRED\n", node);
                }
            } // if (ddr_clock_hertz > 1000000000)
        } // if (lmc == 0)
    } /* for (lmc = 0; lmc < lmc_limit; lmc++) */

    BDK_TRACE(DRAM, "N%d: DRAM init started (hertz=%d, refclk=%d, config=%p)\n",
              node, ddr_clock_hertz, ddr_refclk_hertz, dram_config);
    debug_print("N%d: DRAM init started (hertz=%d, refclk=%d, config=%p)\n",
                node, ddr_clock_hertz, ddr_refclk_hertz, dram_config);

    BDK_TRACE(DRAM, "N%d: Calling DRAM init\n", node);
    measured_ddr_hertz[node] = 0;
    int mbytes = octeon_ddr_initialize(node,
                                       bdk_clock_get_rate(node, BDK_CLOCK_RCLK),
                                       ddr_clock_hertz, ddr_refclk_hertz,
                                       interface_mask, ddr_config,
                                       &measured_ddr_hertz[node],
                                       0, 0, 0);
    BDK_TRACE(DRAM, "N%d: DRAM init returned %d, measured %u Hz\n",
              node, mbytes, measured_ddr_hertz[node]);

    // do not tune or mess with memory if there was an init problem...
    if (mbytes > 0) {

        if (bdk_is_model(OCTEONTX_CN9XXX)) {

            // configure a single ASC region with all memory
            ddr_print("N%d: Setting up ASC region mapping\n", node);
            bdk_dram_setup_mapping(node, interface_mask, mbytes);

            // enable the ECC checker before any memory traffic can occur
            ddr_print("N%d: Enable ECC Checker.\n", node);
            bdk_dram_enable_ECC_checker(node, interface_mask);

            // make the cache/BDK image completely dirty to try to write full cacheblocks 
            uint64_t skip = (node == (int)bdk_numa_master()) ? bdk_dram_get_top_of_bdk() : 0;
            ddr_print("N%d: Rewriting DRAM: start 0 length 0x%lx\n", node, skip);
            bdk_dram_rewrite_bdk(node, skip);

            // dump the new setting of the ASC regions table
            bdk_dram_dump_ASC_table(node, "After INIT", VBL_DEV);
        }

        // disable ECC reporting before we might run tuning
        bdk_dram_disable_ecc_reporting(node);

        // call the tuning routines, with filtering...
        BDK_TRACE(DRAM, "N%d: Calling DRAM tuning\n", node);
        errs = bdk_libdram_maybe_tune_node(node);
        BDK_TRACE(DRAM, "N%d: DRAM tuning returned %d errors\n",
                  node, errs);
#if 0 // We don't need to clear memory, this just wastes time
        // finally, clear memory and any left-over ECC errors
        bdk_dram_clear_mem(node);
#endif
        bdk_dram_clear_ecc(node);

        // re-enable ECC reporting after we are ready for public use
        bdk_dram_enable_ecc_reporting(node);

        // indicate training is complete
        bdk_dram_set_training_complete(node, interface_mask);

    } else {
        // no memory, or problems configuring, disable it all...
        BDK_TRACE(DRAM, "N%d: Disabling DRAM\n", node);
        bdk_error("N%d: Disabling DRAM, configuration issue\n", node);
        bdk_dram_disable_all_pll(node);
    }

    /* Boards may need to mux the TWSI connection between THUNDERX and the BMC.
       This allows the BMC to monitor DIMM temperatures and health */
    if (gpio_select != -1)
        bdk_device_gpio_setup(gpio_device, gpio_select, true, 0, true, false);

    return mbytes;
}

/**
 * This is the main DRAM tuning function. Users of libdram should call this function,
 * avoiding the other internal function. As a rule, functions starting with
 * "libdram_*" are part of the external API and should be used.
 *
 * @param node   Node to tune. This may not be the same node as the one running the code
 *
 * @return Success or Fail
 */
int libdram_tune(int node)
{
    int tot_errs;
    int l2c_is_locked = bdk_l2c_is_locked(node);

    dram_verbosity = bdk_config_get_int(BDK_CONFIG_DRAM_VERBOSE);

    // the only way this entry point should be called is from a MENU item,
    // so, enable any non-running cores on this node, and leave them
    // running at the end...
    ddr_print("N%d: %s: Starting cores (mask was 0x%lx)\n",
              node, __FUNCTION__, bdk_get_running_coremask(node));
    bdk_init_cores(node, ~0ULL);

    // must test for L2C locked here, cannot go on with it unlocked
    // FIXME: but we only need to worry about Node 0???
    if (node == 0) {
        if (!l2c_is_locked) { // is unlocked, must lock it now
            ddr_print("N%d: %s: L2C was unlocked - locking it now\n", node, __FUNCTION__);
            bdk_l2c_lock_mem_region(node, 0, bdk_dram_get_top_of_cache());
        } else {
            ddr_print("N%d: %s: L2C was already locked - continuing\n", node, __FUNCTION__);
        }
    } else {
        ddr_print("N%d: %s: non-zero node, not worrying about L2C lock status\n", node, __FUNCTION__);
    }

    // call the tuning routines, no filtering...
    tot_errs = bdk_libdram_tune_node(node);

    // FIXME: only for node 0, unlock L2C if it was unlocked before...
    if (node == 0) {
        if (!l2c_is_locked) { // it was Node 0 and unlocked, must re-unlock it now
            ddr_print("N%d: Node 0 L2C was unlocked before - unlocking it now\n", node);
            bdk_l2c_unlock_mem_region(node, 0, bdk_dram_get_top_of_cache());
        } else {
            ddr_print("N%d: %s: L2C was already locked - leaving it locked\n", node, __FUNCTION__);
        }
    } else {
        ddr_print("N%d: %s: non-zero node, not worrying about L2C lock status\n", node, __FUNCTION__);
    }

    // make sure to clear memory and any ECC errs when done...
    bdk_dram_clear_mem(node);
    bdk_dram_clear_ecc(node);

    return tot_errs;
}

/**
 * This is the main function for DRAM margining of Write Voltage.
 * Users of libdram should call this function,
 * avoiding the other internal function. As a rule, functions starting with
 * "libdram_*" are part of the external API and should be used.
 *
 * @param node   Node to test. This may not be the same node as the one running the code
 *
 * @return Success or Fail
 */
static
int libdram_margin_write_voltage(int node)
{
    int tot_errs;

    // call the margining routine
    tot_errs = perform_margin_write_voltage(node);

    // make sure to clear memory and any ECC errs when done...
    bdk_dram_clear_mem(node);
    bdk_dram_clear_ecc(node);

    return tot_errs;
}

/**
 * This is the main function for DRAM margining of Read Voltage.
 * Users of libdram should call this function,
 * avoiding the other internal function. As a rule, functions starting with
 * "libdram_*" are part of the external API and should be used.
 *
 * @param node   Node to test. This may not be the same node as the one running the code
 *
 * @return Success or Fail
 */
static
int libdram_margin_read_voltage(int node)
{
    int tot_errs;

    // call the margining routine
    tot_errs = perform_margin_read_voltage(node);

    // make sure to clear memory and any ECC errs when done...
    bdk_dram_clear_mem(node);
    bdk_dram_clear_ecc(node);

    return tot_errs;
}

/**
 * This is the main function for DRAM margining of Write Timing.
 * Users of libdram should call this function,
 * avoiding the other internal function. As a rule, functions starting with
 * "libdram_*" are part of the external API and should be used.
 *
 * @param node   Node to test. This may not be the same node as the one running the code
 *
 * @return Success or Fail
 */
static
int libdram_margin_write_timing(int node)
{
    int tot_errs;

    // call the tuning routine, tell it we are margining not tuning...
    tot_errs = perform_dll_offset_tuning(node, /* write offsets */1, /* margin */0);

    // make sure to clear memory and any ECC errs when done...
    bdk_dram_clear_mem(node);
    bdk_dram_clear_ecc(node);

    return tot_errs;
}

/**
 * This is the main function for DRAM margining of Read Timing.
 * Users of libdram should call this function,
 * avoiding the other internal function. As a rule, functions starting with
 * "libdram_*" are part of the external API and should be used.
 *
 * @param node   Node to test. This may not be the same node as the one running the code
 *
 * @return Success or Fail
 */
static
int libdram_margin_read_timing(int node)
{
    int tot_errs;

    // call the tuning routine, tell it we are margining not tuning...
    tot_errs = perform_dll_offset_tuning(node, /* read offsets */2, /* margin */0);

    // make sure to clear memory and any ECC errs when done...
    bdk_dram_clear_mem(node);
    bdk_dram_clear_ecc(node);

    return tot_errs;
}

/**
 * This is the main function for all DRAM margining.
 * Users of libdram should call this function,
 * avoiding the other internal function. As a rule, functions starting with
 * "libdram_*" are part of the external API and should be used.
 *
 * @param node   Node to test. This may not be the same node as the one running the code
 *
 * @return Success or Fail
 */
int use_margin_settings = 0; // default to not use margin settings

int libdram_margin(int node)
{
    int ret_rt = -1, ret_wt = -1, ret_rv = -1, ret_wv = -1; // set them all to un-run
    char *risk[2] = { "Low Risk", "Needs Review" };
    int l2c_is_locked = bdk_l2c_is_locked(node);
    int loops, margin_loops = 1;
    int margin_mask = 0x0F; // default to run them all
    const char *s;

    // for now, no margining on 81xx, until we can reduce the dynamic runtime size...
    // also for now, no margining on CN9XXX until we have time to port it...
    if (bdk_is_model(OCTEONTX_CN81XX) /*|| bdk_is_model(OCTEONTX_CN9XXX)*/) {
        printf("Sorry, margining is not available on this SoC yet...\n");
        return 0;
    }

    // override control of which margin tests to run
    if ((s = lookup_env_parameter("ddr_margin_mask")) != NULL) {
        margin_mask = strtoul(s, NULL, 0);
    }

    // allow use of final best margin settings
    if ((s = lookup_env_parameter("ddr_use_margin_settings")) != NULL) {
        use_margin_settings = !!strtoul(s, NULL, 10);
        if (use_margin_settings)
            margin_loops = 2; // FIXME?
    }

    dram_verbosity = bdk_config_get_int(BDK_CONFIG_DRAM_VERBOSE);

    // the only way this entry point should be called is from a MENU item,
    // so, enable any non-running cores on this node, and leave them
    // running at the end...
    ddr_print("N%d: %s: Starting cores (mask was 0x%lx)\n",
              node, __FUNCTION__, bdk_get_running_coremask(node));
    bdk_init_cores(node, ~0ULL);

    // must test for L2C locked here, cannot go on with it unlocked
    // FIXME: but we only need to worry about Node 0???
    if  (node == 0) {
        if (!l2c_is_locked) { // is unlocked, must lock it now
            ddr_print("N%d: %s: L2C was unlocked - locking it now\n", node, __FUNCTION__);
            bdk_l2c_lock_mem_region(node, 0, bdk_dram_get_top_of_cache());
        } else {
            ddr_print("N%d: %s: L2C was already locked - continuing\n", node, __FUNCTION__);
        }
    } else {
        ddr_print("N%d: %s: non-zero node, not worrying about L2C lock status\n", node, __FUNCTION__);
    }

    for (loops = 0; loops < margin_loops; loops++) {

        debug_print("N%d: Starting DRAM Margin ALL\n", node);
        if (margin_mask & 1) ret_rv = libdram_margin_read_voltage(node);
        if (margin_mask & 2) ret_wv = libdram_margin_write_voltage(node);
        if (margin_mask & 4) ret_rt = libdram_margin_read_timing(node);
        if (margin_mask & 8) ret_wt = libdram_margin_write_timing(node);
        debug_print("N%d: DRAM Margin ALL finished\n", node);

        /*
          >>> Summary from DDR Margining tool:
          >>> N0: Read Voltage Margin  : Low Risk
          >>> N0: Write Voltage Margin : Low Risk
          >>> N0: Read Timing Margin   : Low Risk
          >>> N0: Write Timing Margin  : Low Risk
        */
        printf("  \n");
        printf("-------------------------------------\n");
        printf("  \n");
        printf("Summary from DDR Margining tool\n");

        // these may not have been done due to THUNDER pass 1.x
        // FIXME? would it be better to print an appropriate message here?
        if (ret_rv != -1) printf("N%d: Read Voltage Margin  : %s\n", node, risk[!!ret_rv]);
        if (ret_wv != -1) printf("N%d: Write Voltage Margin : %s\n", node, risk[!!ret_wv]);

        printf("N%d: Read Timing Margin   : %s\n", node, risk[!!ret_rt]);
        printf("N%d: Write Timing Margin  : %s\n", node, risk[!!ret_wt]);

        printf("  \n");
        printf("-------------------------------------\n");
        printf("  \n");

    } /* for (loops = 0; loops < margin_loops; loops++) */

    // FIXME: only for node 0, unlock L2C if it was unlocked before...
    if (node == 0) {
        if (!l2c_is_locked) { // it was Node 0 and unlocked, must re-unlock it now
            ddr_print("N%d: Node 0 L2C was unlocked before - unlocking it now\n", node);
            bdk_l2c_unlock_mem_region(node, 0, bdk_dram_get_top_of_cache());
        } else {
            ddr_print("N%d: %s: L2C was already locked - leaving it locked\n", node, __FUNCTION__);
        }
    } else {
        ddr_print("N%d: %s: non-zero node, not worrying about L2C lock status\n", node, __FUNCTION__);
    }

    return 0;
}

/**
 * Test the preserve memory operation
 *
 * @param node   Node to test
 *
 * @return None
 */
void libdram_test_memory_preserve(int node)
{
    int num_lmc = __bdk_dram_get_num_lmc((bdk_node_t)node);
    int lmc_mask = __bdk_dram_get_lmc_mask((bdk_node_t)node);
    int lmc;

    BDK_TRACE(DRAM, "N%d: Preserve memory, then core domain reset\n", node);

    for (lmc = 0; lmc < num_lmc; lmc++) {
        if (!(lmc_mask & (1 << lmc)))
            continue;
        BDK_CSR_INIT(reset_ctl, (bdk_node_t)node, BDK_LMCX_RESET_CTL(lmc));
        if (bdk_is_model(OCTEONTX_CN9XXX))
            reset_ctl.cn9.ddr4pdomain = 1; // force enabled
        else
            reset_ctl.cn8.ddr3psoft = 1; // force enabled

        BDK_CSR_WRITE((bdk_node_t)node, BDK_LMCX_RESET_CTL(lmc), reset_ctl.u);
        printf("N%d.LMC%d: Preserve: Setting RESET_CTL[%s] to 1\n", node, lmc,
               (bdk_is_model(OCTEONTX_CN9XXX)) ? "ddr4pdomain" : "ddr3psoft");
        BDK_CSR_INIT(gp0, (bdk_node_t)node, BDK_LMCX_GENERAL_PURPOSE0(lmc));
        BDK_CSR_INIT(gp1, (bdk_node_t)node, BDK_LMCX_GENERAL_PURPOSE1(lmc));
        BDK_CSR_INIT(gp2, (bdk_node_t)node, BDK_LMCX_GENERAL_PURPOSE2(lmc));
        printf("N%d.LMC%d: Preserve: GP0 0x%016lx, GP1 0x%016lx, GP2 0x%04lx\n",
               node, lmc, gp0.u, gp1.u, gp2.u);
    }

#if TEST_PRESERVE_MEM
    // FIXME: for now, do no memory seeding for recovery testing, LMCs may not be fully trained
    uint64_t mbytes = bdk_dram_get_size_mbytes(node);
    uint64_t skip = ((bdk_node_t)node == bdk_numa_master()) ? bdk_dram_get_top_of_bdk() : 0;
    uint64_t len =  (mbytes << 20) - skip;

    printf("N%d: Preserve DRAM: WRITING contents...\n", node);
    for (uint64_t i = 0; i < len; i += 128) // FIXME? jump by cacheblock size?
        __bdk_dram_write64((skip + i), 0xbaadf00ddeadbeefUL);
    __bdk_dram_flush_to_mem_range(skip, skip + len);
#endif /* TEST_PRESERVE_MEM */

    printf("N%d: Waiting 5 secs before issuing a %s RESET\n", node,
           (bdk_is_model(OCTEONTX_CN9XXX)) ? "CORE DOMAIN" : "SOFT");
    bdk_wait_usec(5 * 1000000);
    if (bdk_is_model(OCTEONTX_CN9XXX)) {
        BDK_CSR_WRITE(node, BDK_RST_CORE_DOMAIN_W1S, 1);
        BDK_CSR_READ(node, BDK_RST_CORE_DOMAIN_W1S);
    } else {
        BDK_CSR_WRITE(node, BDK_RST_SOFT_RST, 1);
        BDK_CSR_READ(node, BDK_RST_SOFT_RST);
    }
    bdk_wait_usec(1 * 1000000);
    // bye-bye...
}

/**
 * Get the measured DRAM frequency after a call to libdram_config
 *
 * @param node   Node to get frequency for
 *
 * @return Frequency in Hz
 */
uint32_t libdram_get_freq(int node)
{
    return measured_ddr_hertz[node];
}

/**
 * Get the measured DRAM frequency from the DDR_PLL_CTL CSR
 *
 * @param node   Node to get frequency for
 *
 * @return Frequency in Hz
 */
uint32_t libdram_get_freq_from_pll(int node, int lmc)
{
    uint64_t calculated_ddr_hertz;
    BDK_CSR_INIT(c, node, BDK_LMCX_DDR_PLL_CTL(0));
    if (bdk_is_model(OCTEONTX_CN8XXX)) {
        static const uint8_t _en[] = {1, 2, 3, 4, 5, 6, 7, 8, 10, 12};
        // we check the alternate refclk select bit in LMC0 to indicate 100MHz use
        // assumption: the alternate refclk is setup for 100MHz
        uint64_t ddr_ref_hertz = (c.s.dclk_alt_refclk_sel) ? 100000000 : bdk_clock_get_rate(node, BDK_CLOCK_MAIN_REF);
        uint64_t en = _en[c.cn83xx.ddr_ps_en];
        calculated_ddr_hertz = ddr_ref_hertz * (c.cn83xx.clkf + 1) / ((c.cn83xx.clkr + 1) * en);
    } else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */ {
        uint64_t prediv = (c.cn9.prediv > 0) ? c.cn9.prediv : 1;
        uint64_t postdiv = 2UL << c.cn9.postdiv;
        calculated_ddr_hertz = (c.cn9.clkf * 100000000UL) / prediv / postdiv;
    }
    return calculated_ddr_hertz;
}

#ifndef DRAM_CSR_WRITE_INLINE
void dram_csr_write(bdk_node_t node, const char *csr_name, bdk_csr_type_t type,
                    int busnum, int size, uint64_t address, uint64_t value)
{
    VB_PRT(VBL_CSRS, "N%d: DDR Config %s[%016lx] => %016lx\n", node, csr_name, address, value);
    bdk_csr_write(node, type, busnum, size, address, value);
}
#endif
